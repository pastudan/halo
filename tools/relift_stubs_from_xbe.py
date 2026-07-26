#!/usr/bin/env python3
"""Relift ported:false stub C bodies from XBE disassembly.

Replaces empty / (void)arg; return 0; stubs in module source with XBE-backed
draft implementations. Does not modify kb.json decls or ported flags.
"""
from __future__ import annotations

import argparse
import importlib.util
import json
import re
import sys
from dataclasses import dataclass, field
from pathlib import Path

from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe

ROOT = Path(__file__).resolve().parents[1]
XBE_PATH = ROOT / "halo-patched" / "cachebeta.xbe"

SMALL_MAX = 96
MEDIUM_MAX = 256

JCC_MNEM = {
    "je": "==",
    "jz": "==",
    "jne": "!=",
    "jnz": "!=",
    "ja": ">",
    "jae": ">=",
    "jb": "<",
    "jbe": "<=",
    "jg": ">",
    "jge": ">=",
    "jl": "<",
    "jle": "<=",
}


def load_gen_utils():
    spec_path = ROOT / "tools" / "gen_module_draft_batch.py"
    spec = importlib.util.spec_from_file_location("gen_module_draft_batch", spec_path)
    mod = importlib.util.module_from_spec(spec)
    assert spec.loader is not None
    spec.loader.exec_module(mod)
    return mod


GEN = load_gen_utils()


def build_addr_name(kb: dict) -> dict[int, str]:
    out: dict[int, str] = {}
    for obj in kb.get("objects", []):
        for fn in obj.get("functions", []):
            decl = fn.get("decl") or ""
            m = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", decl)
            if m:
                out[int(fn["addr"], 16)] = m.group(1)
    return out


def strip_c_comments(s: str) -> str:
    return re.sub(r"/\*.*?\*/", "", s, flags=re.DOTALL)


def is_stub_body(body: str) -> bool:
    body = strip_c_comments(body).strip()
    if not body:
        return True
    lines = [ln.strip() for ln in body.splitlines() if ln.strip()]
    if not lines:
        return True
    trivial = 0
    for ln in lines:
        if re.fullmatch(r"\(void\)\s*[A-Za-z_][A-Za-z0-9_]*\s*;", ln):
            trivial += 1
        elif ln in ("return 0;", "return NULL;", "return;", "return 0x0;"):
            trivial += 1
        elif re.fullmatch(r"return\s+\(void\s*\*\)\s*0\s*;", ln):
            trivial += 1
        else:
            return False
    return True


def fn_name_from_decl(decl: str, addr: str) -> str:
    return GEN.fn_name(decl, addr)


def find_function_def(src: str, name: str) -> tuple[int, int, int] | None:
    """Return (sig_start, body_start, body_end) for named function."""
    text = strip_c_comments(src)
    pat = (
        rf"(?m)^(?:static\s+)?(?:inline\s+)?"
        rf"(?:[\w\s*]+?(?:\*|\s+)){re.escape(name)}\s*\([^;{{]*\)\s*\{{"
    )
    m = re.search(pat, text)
    if not m:
        return None
    # Map stripped offset back to original — re-search on original with same span
    m2 = re.search(pat, src)
    if not m2:
        return None
    body_start = m2.end()
    depth = 1
    i = body_start
    while i < len(src) and depth:
        if src[i] == "{":
            depth += 1
        elif src[i] == "}":
            depth -= 1
        i += 1
    return m2.start(), body_start, i - 1


def infer_stack_params(insns) -> list[tuple[int, str]]:
    """Return [(offset, type_hint), ...] for dword [ebp+N] reads, N>=8."""
    seen: list[int] = []
    for ins in insns:
        if ins.mnemonic in ("ret", "call"):
            break
        m = re.search(r"\[ebp \+ (0x[0-9a-f]+)\]", ins.op_str)
        if m and ins.mnemonic in ("mov", "cmp", "push", "lea", "test", "xor"):
            off = int(m.group(1), 16)
            if off >= 8 and off not in seen:
                seen.append(off)
    seen.sort()
    return [(off, "int") for off in seen]


def param_name(i: int, off: int) -> str:
    return f"lift_a{i}"


def fmt_imm(val: int) -> str:
    if val >= 0x10000 or val < 0:
        return f"0x{val & 0xFFFFFFFF:08x}"
    return str(val)


def tag_fourcc(val: int) -> str:
    b = val.to_bytes(4, "little")
    if all(32 <= c < 127 for c in b):
        return repr(b.decode("ascii"))
    return fmt_imm(val)


@dataclass
class LiftCtx:
    insns: list
    addr_name: dict[int, str]
    params: list[str]
    lines: list[str] = field(default_factory=list)
    locals: dict[str, str] = field(default_factory=dict)  # reg/off -> c expr
    ebp_locals: dict[int, str] = field(default_factory=dict)
    emitted_calls: set[int] = field(default_factory=set)


def reg_expr(ctx: LiftCtx, reg: str) -> str:
    reg = reg.strip()
    if reg in ctx.locals:
        return ctx.locals[reg]
    if reg in ("eax", "ebx", "ecx", "edx", "esi", "edi"):
        return reg
    return reg


def parse_mem(op: str) -> tuple[str | None, int | None, str | None]:
    """Parse op_str like 'dword ptr [esi + 0x48]' -> (base, off, size)."""
    m = re.match(
        r"(byte|word|dword|float) ptr \[(0x[0-9a-f]+)\]",
        op.strip(),
    )
    if m:
        return None, int(m.group(2), 16), m.group(1)
    m = re.match(
        r"(byte|word|dword|float) ptr \[(\w+) - (0x[0-9a-f]+)\]",
        op.strip(),
    )
    if m:
        return m.group(2), int(m.group(3), 16) | 0x80, m.group(1)
    m = re.match(
        r"(byte|word|dword|float) ptr \[(\w+) \+ (0x[0-9a-f]+)\]",
        op.strip(),
    )
    if m:
        return m.group(2), int(m.group(3), 16), m.group(1)
    m = re.match(r"(byte|word|dword|float) ptr \[(\w+)\]", op.strip())
    if m:
        return m.group(2), 0, m.group(1)
    return None, None, None


def cast_for_size(size: str | None) -> str:
    if size == "byte":
        return "char"
    if size == "word":
        return "int16_t"
    if size == "float":
        return "float"
    return "int"


def ebp_slot_expr(off: int, positive: bool) -> str:
    if not positive or off >= 0x80:
        return f"local_{(off & 0x7f):x}"
    if off >= 8:
        return f"lift_a{(off - 8) // 4}"
    return f"stack_{off:x}"


def mem_read_expr(base: str, off: int, size: str | None) -> str:
    cast = cast_for_size(size)
    if base == "ebp":
        slot = ebp_slot_expr(off if not (off and off >= 0x80) else (off & 0x7f), not (off and off >= 0x80))
        return slot
    if base.startswith("0x"):
        addr = int(base, 16) + off
        return f"*({cast} *)0x{addr:08x}"
    if off:
        return f"*({cast} *)((char *){base} + 0x{off:x})"
    return f"*({cast} *){base}"


def mem_write_lhs(base: str, off: int, size: str | None) -> str:
    cast = cast_for_size(size)
    if base == "ebp":
        slot = ebp_slot_expr(off if not (off and off >= 0x80) else (off & 0x7f), not (off and off >= 0x80))
        return slot
    if base.startswith("0x"):
        addr = int(base, 16) + off
        return f"*({cast} *)0x{addr:08x}"
    if off:
        return f"*({cast} *)((char *){base} + 0x{off:x})"
    return f"*({cast} *){base}"


def collect_call_args(insns, idx: int) -> tuple[list[str], int]:
    """Walk backward from call at idx collecting push args (cdecl order)."""
    args: list[str] = []
    j = idx - 1
    while j >= 0 and len(args) < 8:
        ins = insns[j]
        if ins.mnemonic == "push":
            op = ins.op_str.strip()
            if op.startswith("0x"):
                args.append(fmt_imm(int(op, 16)))
            elif re.match(r"dword ptr \[ebp \+ (0x[0-9a-f]+)\]", op):
                off = int(re.search(r"0x[0-9a-f]+", op).group(0), 16)
                idx_p = (off - 8) // 4
                args.append(f"lift_a{idx_p}" if idx_p >= 0 else f"stack_{off:x}")
            elif re.match(r"dword ptr \[(\w+) \+ (0x[0-9a-f]+)\]", op):
                m = re.match(r"dword ptr \[(\w+) \+ (0x[0-9a-f]+)\]", op)
                args.append(mem_read_expr(m.group(1), int(m.group(2), 16), "dword"))
            elif re.fullmatch(r"[a-z]+", op):
                args.append(op)
            else:
                args.append(f"/* {op} */")
            j -= 1
            continue
        if ins.mnemonic in ("mov", "lea", "xor", "fld", "fcomp", "fnstsw", "test", "cmp"):
            j -= 1
            continue
        if ins.mnemonic in ("push", "pop") and ins.op_str in ("ebp", "ebx", "esi", "edi"):
            break
        if ins.mnemonic == "sub" and ins.op_str.startswith("esp"):
            break
        break
    return args, j


def normalize_reg(name: str) -> str:
    name = name.strip()
    if len(name) == 2 and name[1] in "xlh":
        return name[0] + "x"
    return name


def reg_store_lhs(reg: str) -> str:
    reg = normalize_reg(reg)
    if reg.endswith("x"):
        return reg
    return reg


def finalize_body(lines: list[str], decl_params: list[str], sig: str = "") -> list[str]:
    """Prepend C89 declarations and sanitize relifted body lines."""
    decl_set = set(decl_params)
    void_fn = bool(re.search(r"\(\s*void\s*\)\s*$", sig.replace(" ", "")))
    if void_fn:
        lines = [re.sub(r"\blift_a\d+\b", "0", ln) for ln in lines]
    elif decl_params:
        for i, p in enumerate(decl_params):
            lines = [re.sub(rf"\blift_a{i}\b", p, ln) for ln in lines]
    body_text = "\n".join(lines)

    used_regs = set()
    for reg in ("eax", "ebx", "ecx", "edx", "esi", "edi", "ebp"):
        if re.search(rf"\b{reg}\b", body_text):
            used_regs.add(reg)
    # also pick up register names inside call comments
    for reg in re.findall(r"/\*\s*\w+\([^)]*\b(eax|ebx|ecx|edx|esi|edi)\b", body_text):
        used_regs.add(reg)

    stack_locals = sorted(set(re.findall(r"\bstack_([0-9a-f]+)\b", body_text)))
    local_slots = sorted(set(re.findall(r"\blocal_([0-9a-f]+)\b", body_text)))
    arg_locals = sorted(set(re.findall(r"lift_a(\d+)", body_text)))
    partial_regs = sorted(set(re.findall(r"\b(al|bl|cl|dl|ah|bh|ch|dh|di|si|bx|cx|dx)\b", body_text)))
    for pr in list(partial_regs):
        if pr in ("di", "si", "bx", "cx", "dx"):
            used_regs.add({"di": "edi", "si": "esi", "bx": "ebx", "cx": "ecx", "dx": "edx"}[pr])
        elif pr in ("al", "bl", "cl", "dl", "ah", "bh", "ch", "dh"):
            used_regs.add({"al": "eax", "bl": "ebx", "cl": "ecx", "dl": "edx", "ah": "eax", "bh": "ebx", "ch": "ecx", "dh": "edx"}[pr])

    pre: list[str] = []
    for reg in ("eax", "ebx", "ecx", "edx", "esi", "edi", "ebp"):
        if reg in used_regs and reg not in decl_set:
            pre.append(f"  int {reg} = 0;")
    for off in stack_locals:
        pre.append(f"  int stack_{off} = 0;")
    for off in local_slots:
        pre.append(f"  int local_{off} = 0;")
    for an in arg_locals:
        pname = f"lift_a{an}"
        if pname not in decl_set:
            pre.append(f"  int {pname} = 0;")

    invalid = re.compile(
        r"\b(dword|word|byte|float) ptr\b|\bgoto L_|\bfnstsw\b|\bfcomp\b|\bfld\b"
    )
    out: list[str] = []
    for ln in lines:
        if invalid.search(ln):
            ln = "  /* relift: " + ln.strip().lstrip("/").strip("* ").strip() + " */"
        ln = re.sub(r"/\*\s*(-?\d+|0x[0-9a-f]+)\s*\*/", lambda m: m.group(1), ln)
        ln = re.sub(r"/\*\s*(-?\d+|0x[0-9a-f]+)\s*\*/", lambda m: m.group(1), ln)
        ln = re.sub(r"\*/\s*\*/", "*/", ln)
        ln = re.sub(r"\*\(\w+ \*\)&(lift_a\d+) =", r"\1 =", ln)
        ln = re.sub(r"\*\(\w+ \*\)&(arg\d+) =", lambda m: f"lift_a{m.group(1)[-1]} =", ln)
        ln = re.sub(
            r"\barg_([0-9a-f]+)\b",
            lambda m: f"lift_a{(int(m.group(1), 16) - 8) // 4}"
            if int(m.group(1), 16) >= 8
            else f"stack_{m.group(1)}",
            ln,
        )
        ln = re.sub(r"\barg_c\b", "lift_a1", ln)
        ln = re.sub(r"\barg(\d+)\b", r"lift_a\1", ln)
        ln = re.sub(r"\bbl\b", "(char)ebx", ln)
        ln = re.sub(r"\bcl\b", "(char)ecx", ln)
        ln = re.sub(r"\bal\b", "(char)eax", ln)
        ln = re.sub(r"\bbh\b", "(char)ebx", ln)
        ln = re.sub(r"\bch\b", "(char)ecx", ln)
        ln = re.sub(r"\bah\b", "(char)eax", ln)
        ln = re.sub(r"\bdh\b", "(char)edx", ln)
        ln = re.sub(r" = d;$", " = (char)edx;", ln)
        ln = re.sub(r" = a;$", " = (char)eax;", ln)
        ln = re.sub(r" = c;$", " = (char)ecx;", ln)
        ln = re.sub(r"\*\(\w+ \*\)&0\b", "0", ln)
        ln = re.sub(r"\*\(\w+ \*\)0\b", "((void *)0)", ln)
        ln = re.sub(r"\bax\b", "(int16_t)eax", ln)
        ln = re.sub(r"\bdx\b", "(int16_t)edx", ln)
        ln = re.sub(r"\bcx\b", "(int16_t)ecx", ln)
        ln = re.sub(r"\bbx\b", "(int16_t)ebx", ln)
        ln = re.sub(r"\bsi\b", "(int16_t)esi", ln)
        ln = re.sub(r"\bdi\b", "(int16_t)edi", ln)
        ln = re.sub(r"\bdx\b", "(int16_t)edx", ln)
        ln = re.sub(r"\bcx\b", "(int16_t)ecx", ln)
        ln = re.sub(r"\bbx\b", "(int16_t)ebx", ln)
        ln = re.sub(r"\bsi\b", "(int16_t)esi", ln)
        ln = re.sub(r"\bdi\b", "(int16_t)edi", ln)
        ln = re.sub(
            r"(lift_a\d+) = (0x[0-9a-f]+);",
            lambda m: f"{m.group(1)} = (int){m.group(2)};",
            ln,
        )
        # string literal globals for Halo .rdata addresses
        ln = re.sub(
            r"(display_assert|console_printf|console_warning|csstrcpy|csstrncpy|csstrlen)\(([^)]*)\)",
            lambda m: m.group(1) + "(" + ", ".join(
                f"(const char *){a.strip()}" if re.match(r"0x00[23][0-9a-f]{5}", a.strip()) else a.strip()
                for a in m.group(2).split(",") if a.strip()
            ) + ")",
            ln,
        )
        ln = ln.replace(" = b;", " = (char)ebx;")
        ln = ln.replace(" = bl;", " = (char)ebx;")
        ln = ln.replace(" = cl;", " = (char)ecx;")
        ln = ln.replace(" = al;", " = (char)eax;")
        ln = ln.replace(" = bx;", " = (int16_t)ebx;")
        ln = ln.replace(" = cx;", " = (int16_t)ecx;")
        ln = ln.replace(" = di;", " = (int16_t)edi;")
        ln = ln.replace(" = si;", " = (int16_t)esi;")
        ln = ln.replace(" = dx;", " = (int16_t)edx;")
        ln = re.sub(
            r"\*\(int \*\)\(\(char \*\)ebp \+ (0x[0-9a-f]+)\)",
            lambda m: f"*(int *)&arg{(int(m.group(1),16)-8)//4}"
            if int(m.group(1), 16) >= 8
            else f"*(int *)&stack_{int(m.group(1),16):x}",
            ln,
        )
        ln = re.sub(
            r"\*\(int \*\)\(\(char \*\)ebp - (0x[0-9a-f]+)\)",
            lambda m: f"*(int *)&local_{int(m.group(1),16):x}",
            ln,
        )
        out.append(ln)
    if not pre:
        return out
    silence: list[str] = []
    for d in pre:
        m = re.search(r"\b(\w+)\s*=", d)
        if m:
            silence.append(f"  (void){m.group(1)};")
    return pre + [""] + out + ([""] + silence if silence else [])


_DECL_ARITY: dict[str, int] | None = None
_DECL_PARAMS: dict[str, list[str]] | None = None


def load_decl_sigs() -> tuple[dict[str, int], dict[str, list[str]]]:
    global _DECL_ARITY, _DECL_PARAMS
    if _DECL_ARITY is not None and _DECL_PARAMS is not None:
        return _DECL_ARITY, _DECL_PARAMS
    arity: dict[str, int] = {}
    params: dict[str, list[str]] = {}
    decl_path = ROOT / "build" / "generated" / "decl.h"
    if decl_path.is_file():
        for line in decl_path.read_text().splitlines():
            m = re.search(
                r"HFUNC\s+(?:[\w\s\*]+?)\b([A-Za-z_][A-Za-z0-9_]*)\s*\(([^;]*)\)",
                line,
            )
            if not m:
                continue
            name = m.group(1)
            ps = m.group(2).strip()
            if not ps or ps == "void":
                arity[name] = 0
                params[name] = []
            else:
                parts = [p.strip() for p in ps.split(",") if p.strip() and "..." not in p]
                arity[name] = len(parts)
                params[name] = parts
    _DECL_ARITY = arity
    _DECL_PARAMS = params
    return arity, params


def load_decl_arity() -> dict[str, int]:
    return load_decl_sigs()[0]


def cast_arg_for_param(arg: str, param_type: str, cname: str) -> str:
    pt = param_type.replace("const ", "")
    if arg == "0":
        if "*" in param_type or "void" in pt:
            if "wchar" in param_type:
                return "(wchar_t *)0"
            if "char" in param_type:
                return "(char *)0"
            return "(void *)0"
        if "float" in param_type or "double" in param_type:
            return "0.0f"
        return "0"
    if arg.startswith("(const char *)") and "*" in param_type:
        return arg.replace("(const char *)", "(void *)", 1)
    if re.match(r"0x[0-9a-f]+", arg):
        if "float" in param_type:
            return "0.0f"
        if "*" in param_type:
            return f"(void *){arg}"
        if "char" in param_type:
            return f"(const char *){arg}"
    return arg


def fmt_call_line(target: int, cname: str, args: list[str]) -> str:
    casted: list[str] = []
    for a in args[:8]:
        a = a.strip()
        if a.startswith("/*"):
            casted.append("0")
        elif re.fullmatch(r"(eax|ebx|ecx|edx|esi|edi|ebp|lift_a\d+|local_[0-9a-f]+|stack_[0-9a-f]+)", a):
            casted.append("0")
        elif re.match(r"0x00[23][0-9a-f]{5}", a):
            casted.append(f"(const char *){a}")
        elif re.match(r"0x[0-9a-f]+", a):
            casted.append(a)
        elif a.startswith("'") or a.startswith('"'):
            casted.append(a)
        else:
            casted.append(a)
    arity_map, param_map = load_decl_sigs()
    arity = arity_map.get(cname)
    if arity is None:
        arity = min(len(casted), 4) if casted else (2 if cname.startswith("FUN_") else 0)
    if cname == "qsort":
        arity = 4
    casted = casted[:arity]
    while len(casted) < arity:
        casted.append("0")
    ptypes = param_map.get(cname, [])
    casted = [
        cast_arg_for_param(a, ptypes[i] if i < len(ptypes) else "int", cname)
        for i, a in enumerate(casted)
    ]
    if cname in ("csmemset", "csmemcpy", "csmemmove"):
        casted = [a.replace("(const char *)", "(void *)") for a in casted]
    if arity == 0:
        return f"  {cname}();"
    return f"  {cname}({', '.join(casted)});"


def quality_ok(lines: list[str]) -> bool:
    text = "\n".join(lines)
    if re.search(r"\b(?:return\s+)?[A-Za-z_][A-Za-z0-9_]*\s*\(", text):
        return True
    if re.search(r"\*\(\w+\s*\*\)", text):
        return True
    if re.search(r"\bif\s*\(", text):
        return True
    if re.search(r"\bwhile\s*\(", text):
        return True
    if re.search(r"\bgoto\b", text):
        return True
    if re.search(r"\bfor\s*\(", text):
        return True
    if re.search(r"\(\(void \(\*\)", text):
        return True
    return False


def lift_small(ctx: LiftCtx) -> list[str]:
    return lift_large(ctx)


def lift_medium(ctx: LiftCtx) -> list[str]:
    return lift_large(ctx)


def lift_large(ctx: LiftCtx) -> list[str]:
    insns = ctx.insns
    lines: list[str] = []
    returns_eax = False
    return_expr = "0"

    i = 0
    while i < len(insns):
        ins = insns[i]
        if ins.mnemonic == "call" and ins.op_str.startswith("0x"):
            target = int(ins.op_str, 16)
            cname = ctx.addr_name.get(target, f"FUN_{target:08x}")
            args, _ = collect_call_args(insns, i)
            if len(args) >= 2 and args[-2].startswith("0x") and len(args[-2]) == 10:
                v = int(args[-2], 16)
                if 0x2000000 < v < 0x7FFFFFFF:
                    args[-2] = tag_fourcc(v)
            lines.append(fmt_call_line(target, cname, args))
            ctx.emitted_calls.add(target)
        elif ins.mnemonic in ("cmp", "test") and i + 1 < len(insns) and insns[i + 1].mnemonic in JCC_MNEM:
            lines.append(
                f"  /* {ins.mnemonic} {ins.op_str} -> {insns[i+1].mnemonic} {insns[i+1].op_str} */"
            )
            i += 1
        elif ins.mnemonic == "mov" and "dword ptr [0x" in ins.op_str and "," in ins.op_str:
            dst, src = [p.strip() for p in ins.op_str.split(",", 1)]
            _, off, _ = parse_mem(dst)
            if off is not None:
                lines.append(f"  /* mem[0x{off:08x}] = {src} */")
        elif ins.mnemonic == "xor" and ins.op_str.strip() in ("eax, eax", "eax,eax"):
            returns_eax = True
            return_expr = "0"
        elif ins.mnemonic == "mov" and ins.op_str in ("eax, 1", "eax,1"):
            returns_eax = True
            return_expr = "1"
        i += 1

    if returns_eax:
        lines.append(f"  return {return_expr};")
    if not lines:
        lines.append("  /* relift: empty body */")
    return lines


def ret_kind_from_sig(sig: str) -> str:
    return GEN.ret_kind(sig + ";")


def lift_function(
    insns,
    *,
    size: int,
    addr_name: dict[int, str],
    params: list[str],
    ret_kind: str,
    sig: str,
) -> list[str]:
    ctx = LiftCtx(insns=insns, addr_name=addr_name, params=params)
    if size <= SMALL_MAX:
        lines = lift_small(ctx)
    elif size <= MEDIUM_MAX:
        lines = lift_medium(ctx)
    else:
        lines = lift_large(ctx)

    if not lines:
        lines = lift_large(ctx)

    if not quality_ok(lines):
        # last resort: at least emit call list
        calls = []
        for ins in insns:
            if ins.mnemonic == "call" and ins.op_str.startswith("0x"):
                t = int(ins.op_str, 16)
                calls.append(ctx.addr_name.get(t, f"FUN_{t:08x}"))
        if calls:
            cast_calls = []
            for i, ins in enumerate(insns):
                if ins.mnemonic == "call" and ins.op_str.startswith("0x"):
                    t = int(ins.op_str, 16)
                    cname = ctx.addr_name.get(t, f"FUN_{t:08x}")
                    args, _ = collect_call_args(insns, i)
                    cast_calls.append(fmt_call_line(t, cname, args))
            lines = cast_calls[:24] if cast_calls else [
                f"  /* relift calls: {', '.join(calls[:8])} */"
            ]
        else:
            lines = ["  /* relift: no calls detected — manual review */"]

    sig_ret = ret_kind_from_sig(sig)
    if sig_ret == "void":
        lines = [ln for ln in lines if not re.match(r"\s*return\b", ln)]
    elif sig_ret == "ptr" and not any("return" in ln for ln in lines):
        lines.append("  return NULL;")
    elif sig_ret in ("scalar", "char") and not any("return" in ln for ln in lines):
        lines.append("  return 0;")

    decl_params = GEN.parse_params(GEN.sanitize_decl_for_c(sig + ";"))
    return finalize_body(lines, decl_params, sig)


def signature_from_source(src: str, name: str) -> str | None:
    m = re.search(
        rf"(?m)^(?:static\s+)?(?:inline\s+)?((?:[\w\s*]+?(?:\*|\s+)){re.escape(name)}\s*\([^;{{]*\))\s*\{{",
        src,
    )
    if m:
        return m.group(1).strip()
    return None


def build_signature(decl: str, params: list[str], addr: str) -> str:
    c_decl = GEN.sanitize_decl_for_c(decl)
    if "??" in c_decl or re.search(r"@\w", c_decl.split("(", 1)[0]):
        c_decl = f"void FUN_{int(addr, 16):08x}(void);"
    parsed = GEN.parse_params(c_decl)
    if len(parsed) < len(params):
        # extend with inferred params
        head = c_decl.split("(", 1)[0].strip()
        extra = params[len(parsed) :]
        if not parsed and extra:
            typed = ", ".join(f"int {p}" for p in extra)
            return f"{head}({typed})"
        if extra:
            typed = ", ".join(f"int {p}" for p in extra)
            base = GEN.format_fn_signature(c_decl.rstrip(";"), parsed)
            return base[:-1] + ", " + typed + ")"
    return GEN.format_fn_signature(c_decl.rstrip(";"), parsed or params)


def relift_object(object_name: str, *, dry_run: bool = False) -> dict:
    kb = json.loads((ROOT / "kb.json").read_text())
    obj = next(o for o in kb["objects"] if o["name"] == object_name)
    src_rel = obj.get("source")
    if not src_rel:
        raise SystemExit(f"no source for {object_name}")
    src_path = ROOT / "src" / "halo" / src_rel
    if not src_path.is_file():
        raise SystemExit(f"missing source {src_path}")

    xbe = Xbe.from_file(str(XBE_PATH))
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    addr_name = build_addr_name(kb)

    fns = sorted(obj["functions"], key=lambda f: int(f["addr"], 16))
    addrs = [(int(f["addr"], 16), f) for f in fns]

    def get_bytes(va: int, end: int) -> bytes:
        for sec in xbe.sections.values():
            s = sec.header.virtual_addr
            if s <= va < s + sec.header.virtual_size:
                return bytes(sec.data[va - s : end - s])
        raise RuntimeError(hex(va))

    src = src_path.read_text()
    relifted = 0
    skipped = 0
    stub_before = 0

    work: list[tuple[int, int, str]] = []

    for i, (va, fn) in enumerate(addrs):
        if fn.get("ported") is not False:
            continue
        addr = fn["addr"].lower()
        decl = fn.get("decl") or f"void FUN_{int(addr, 16):08x}(void);"
        name = fn_name_from_decl(decl, addr)
        span = find_function_def(src, name)
        if span is None:
            skipped += 1
            continue
        sig_start, body_start, body_end = span
        body = src[body_start:body_end]
        if not is_stub_body(body):
            skipped += 1
            continue
        stub_before += 1

        end = addrs[i + 1][0] if i + 1 < len(addrs) else va + 0x400
        size = end - va
        data = get_bytes(va, min(end, va + 0x4000))
        insns = [ins for ins in md.disasm(data, va) if ins.address < end]

        stack_params = infer_stack_params(insns)
        params = [param_name(i, off) for i, (off, _) in enumerate(stack_params)]
        if not params:
            params = GEN.parse_params(GEN.sanitize_decl_for_c(decl))

        sig = signature_from_source(src, name) or build_signature(decl, params, addr)
        params = GEN.parse_params(GEN.sanitize_decl_for_c(sig + ";")) or params
        ret_kind = GEN.ret_kind(sig + ";")
        body_lines = lift_function(
            insns,
            size=size,
            addr_name=addr_name,
            params=params,
            ret_kind=ret_kind,
            sig=sig,
        )
        new_fn = f"{sig}\n{{\n" + "\n".join(body_lines) + "\n}"
        work.append((sig_start, body_end, new_fn))

    for sig_start, body_end, new_fn in sorted(work, key=lambda x: x[0], reverse=True):
        src = src[:sig_start] + new_fn + src[body_end + 1 :]
        relifted += 1

    if relifted and not dry_run:
        src_path.write_text(src)

    disasm_out = ROOT / "artifacts" / f"{GEN.slug(object_name)}_relift_disasm.txt"
    disasm_out.parent.mkdir(parents=True, exist_ok=True)

    return {
        "object": object_name,
        "relifted": relifted,
        "skipped": skipped,
        "stub_before": stub_before,
        "source": str(src_path),
    }


def main() -> None:
    ap = argparse.ArgumentParser(description="Relift stub bodies from XBE")
    ap.add_argument("--object", action="append", required=True)
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    total = 0
    results = []
    for obj in args.object:
        r = relift_object(obj, dry_run=args.dry_run)
        results.append(r)
        total += r["relifted"]
        print(
            f"{r['object']}: relifted {r['relifted']} "
            f"(skipped {r['skipped']}, stubs {r['stub_before']})"
        )

    print(f"TOTAL relifted: {total}")


if __name__ == "__main__":
    main()
