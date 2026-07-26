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

_EBP_OFF = r"(0x[0-9a-f]+|\d+)"
_EBP_PARAM_RE = re.compile(rf"\[ebp \+ {_EBP_OFF}\]", re.I)
_EBP_LOCAL_RE = re.compile(rf"\[ebp - {_EBP_OFF}\]", re.I)


def load_gen_utils():
    spec_path = ROOT / "tools" / "gen_module_draft_batch.py"
    spec = importlib.util.spec_from_file_location("gen_module_draft_batch", spec_path)
    mod = importlib.util.module_from_spec(spec)
    sys.modules["gen_module_draft_batch"] = mod
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
    raw = body
    stripped = strip_c_comments(body).strip()
    if re.search(r"relift:", raw) and (
        not stripped
        or stripped in ("return 0;", "return NULL;", "(void)0;")
        or re.fullmatch(r"return 0;\s*", stripped)
    ):
        return False
    body = stripped
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


def is_relift_draft(body: str) -> bool:
    if is_stub_body(body):
        return True
    if re.search(r"\(void\)(eax|ebx|ecx|edx|esi|edi|ebp)\s*;", body):
        return True
    markers = (
        "/* cmp",
        "/* test",
        "/* mem[",
        "relift:",
        "(uintptr_t)",
        "no calls detected",
    )
    return any(m in body for m in markers)


def fn_name_from_decl(decl: str, addr: str) -> str:
    return GEN.fn_name(decl, addr)


def addr_in_prefix(prefix: str, addr: str) -> bool:
    va = int(addr, 16)
    forms = {
        addr.lower(),
        f"0x{va:x}",
        f"0x{va:08x}",
        f"0x{va:08x}".lstrip("0").replace("x", "x0", 1) if va else addr.lower(),
    }
    pl = prefix.lower()
    return any(fm in pl for fm in forms)


def find_function_def(src: str, name: str) -> tuple[int, int, int] | None:
    """Return (sig_start, body_start, body_end) for named function."""
    return GEN.find_function_def(src, name)


def addr_marker_forms(addr: str) -> list[str]:
    va = int(addr, 16)
    raw = [
        addr.lower(),
        f"0x{va:x}",
        f"0x{va:08x}",
    ]
    out: list[str] = []
    for a in raw:
        out.append(f"/* {a} */")
        out.append(f"/* orphan {a} */")
    return out


def find_function_def_by_addr(src: str, name: str, addr: str) -> tuple[int, int, int] | None:
    """Locate function in original source via addr comment marker + name."""
    va = int(addr, 16)
    for marker in addr_marker_forms(addr):
        pos = 0
        while True:
            idx = src.find(marker, pos)
            if idx < 0:
                break
            pos = idx + len(marker)
            window = src[idx : idx + 800]
            m = re.search(
                rf"(?m)^(?!\s)(?:static\s+)?(?:inline\s+)?"
                rf"(?:__declspec\s*\([^)]*\)\s+)?"
                rf"(?:[\w\s*]+?(?:\*|\s+)|[\w\s]+\*\s*)"
                rf"(?:__stdcall\s+|__cdecl\s+|__fastcall\s+)?"
                rf"{re.escape(name)}\s*\(",
                window,
            )
            if not m:
                continue
            sig_start = idx + m.start()
            paren_open = idx + m.end() - 1
            paren_close = GEN.scan_balanced(src, paren_open, "(", ")")
            if paren_close is None:
                continue
            i = paren_close + 1
            while i < len(src) and src[i].isspace():
                i += 1
            if i >= len(src) or src[i] != "{":
                continue
            body_start = i + 1
            body_end = GEN.scan_balanced(src, i, "{", "}")
            if body_end is None:
                continue
            return sig_start, body_start, body_end
    return None


def find_function_def_for_addr(src: str, name: str, addr: str) -> tuple[int, int, int] | None:
    span = find_function_def_by_addr(src, name, addr)
    if span is not None:
        return span
    stripped, idx_map = GEN.strip_c_comments_indexed(src)
    hits: list[tuple[int, int, int]] = []
    for fn, sig_s, body_s, body_e in GEN.iter_fn_defs(stripped):
        if fn != name:
            continue
        sig_o, _ = GEN.map_stripped_span(sig_s, sig_s + 1, idx_map)
        _, body_eo = GEN.map_stripped_span(body_s, body_e, idx_map)
        _, body_so = GEN.map_stripped_span(body_s, body_s + 1, idx_map)
        hits.append((sig_o, body_so, body_eo))
    if len(hits) == 1:
        return hits[0]
    return None


def _span_from_sig_start(src: str, sig_start: int, name: str) -> tuple[int, int, int] | None:
    m = re.search(rf"{re.escape(name)}\s*\(", src[sig_start:])
    if not m:
        return None
    paren_open = sig_start + m.end() - 1
    paren_close = GEN.scan_balanced(src, paren_open, "(", ")")
    if paren_close is None:
        return None
    i = paren_close + 1
    while i < len(src) and src[i].isspace():
        i += 1
    if i >= len(src) or src[i] != "{":
        return None
    body_start = i + 1
    body_end = GEN.scan_balanced(src, i, "{", "}")
    if body_end is None:
        return None
    return sig_start, body_start, body_end


ARG_REGS = frozenset({"eax", "ebx", "ecx", "edx", "esi", "edi", "ebp"})


def normalize_reg(name: str) -> str:
    name = name.strip()
    if len(name) == 2 and name[1] in "xlh":
        return name[0] + "x"
    return name


def parse_reg_params(decl: str) -> dict[str, str]:
    """Map register name -> C parameter name from @<reg> kb decl annotations."""
    out: dict[str, str] = {}
    for p in GEN.split_param_strings(decl):
        m = re.search(r"@<(\w+)>", p)
        if not m:
            continue
        reg = normalize_reg(m.group(1).lower())
        tok = re.split(r"\s+", strip_c_comments(re.sub(r"\[[^\]]*\]", "", p)).strip())
        cand = tok[-1] if tok else ""
        if cand and cand not in ("...",) and re.match(r"^[A-Za-z_]", cand):
            out[reg] = GEN.clean_param_name(cand)
    return out


def ebp_param_expr(off: int, caller_params: list[str]) -> str:
    if off >= 8:
        idx = (off - 8) // 4
        if idx < len(caller_params):
            return caller_params[idx]
        return f"lift_a{idx}"
    return f"stack_{off:x}"


def _parse_ebp_offset(text: str, sign: str = "+") -> int | None:
    m = re.search(rf"\[ebp\s*{re.escape(sign)}\s*(0x[0-9a-f]+|\d+)\]", text, re.I)
    if not m:
        return None
    val = m.group(1)
    return int(val, 16) if val.lower().startswith("0x") else int(val)


def infer_stack_params(insns) -> list[tuple[int, str]]:
    """Return [(offset, type_hint), ...] for dword [ebp+N] reads, N>=8."""
    seen: list[int] = []
    for ins in insns:
        if ins.mnemonic in ("ret", "call"):
            break
        off = _parse_ebp_offset(ins.op_str, "+")
        if off is not None and ins.mnemonic in ("mov", "cmp", "push", "lea", "test", "xor"):
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
    caller_name: str = ""
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


def expr_from_operand(op: str, reg_state: dict[str, str], caller_params: list[str]) -> str:
    op = op.strip()
    if op.startswith("0x"):
        val = int(op, 16)
        if 0x2000000 < val < 0x7FFFFFFF and val.to_bytes(4, "little").isascii():
            return tag_fourcc(val)
        return fmt_imm(val)
    m = re.match(rf"(?:byte|word|dword|float) ptr \[ebp \+ {_EBP_OFF}\]", op, re.I)
    if m:
        val = m.group(1)
        off = int(val, 16) if val.lower().startswith("0x") else int(val)
        return ebp_param_expr(off, caller_params)
    m = re.match(rf"(?:byte|word|dword|float) ptr \[ebp - {_EBP_OFF}\]", op, re.I)
    if m:
        val = m.group(1)
        off = int(val, 16) if val.lower().startswith("0x") else int(val)
        return f"local_{off:x}"
    m = re.match(r"(?:byte|word|dword|float) ptr \[(\w+) \+ (0x[0-9a-f]+)\]", op)
    if m:
        base = reg_state.get(m.group(1), m.group(1))
        return mem_read_expr(base, int(m.group(2), 16), "dword")
    m = re.match(r"(?:byte|word|dword|float) ptr \[(\w+)\]", op)
    if m:
        base = reg_state.get(m.group(1), m.group(1))
        return f"*({cast_for_size('dword')} *)({base})"
    if re.fullmatch(r"-?\d+", op):
        return op
    reg = normalize_reg(op)
    if reg in reg_state:
        return reg_state[reg]
    if reg in ARG_REGS:
        return reg
    return f"/* {op} */"


def build_reg_state(insns, end_idx: int, caller_params: list[str]) -> dict[str, str]:
    """Track register expressions from prologue through instruction before end_idx."""
    state: dict[str, str] = {}
    for i in range(min(end_idx, len(insns))):
        ins = insns[i]
        if ins.mnemonic == "mov":
            parts = [p.strip() for p in ins.op_str.split(",", 1)]
            if len(parts) != 2:
                continue
            dst_raw, src = parts
            dst = normalize_reg(dst_raw.split()[-1] if "ptr" in dst_raw else dst_raw)
            if dst not in ARG_REGS:
                continue
            state[dst] = expr_from_operand(src, state, caller_params)
        elif ins.mnemonic == "lea":
            parts = [p.strip() for p in ins.op_str.split(",", 1)]
            if len(parts) != 2:
                continue
            dst = normalize_reg(parts[0])
            if dst not in ARG_REGS:
                continue
            src = parts[1]
            m = re.match(
                rf"(?:(?:byte|word|dword|float)\s+)?(?:ptr\s+)?\[(\w+)\s*\+\s*(0x[0-9a-f]+|\d+)\]",
                src,
                re.I,
            )
            if m:
                base = state.get(m.group(1), m.group(1))
                off_val = m.group(2)
                off = int(off_val, 16) if off_val.lower().startswith("0x") else int(off_val)
                state[dst] = f"(char *){base} + 0x{off:x}"
            elif re.match(
                rf"(?:(?:byte|word|dword|float)\s+)?(?:ptr\s+)?\[(\w+)\s*-\s*(0x[0-9a-f]+|\d+)\]",
                src,
                re.I,
            ):
                m2 = re.match(
                    rf"(?:(?:byte|word|dword|float)\s+)?(?:ptr\s+)?\[(\w+)\s*-\s*(0x[0-9a-f]+|\d+)\]",
                    src,
                    re.I,
                )
                base = state.get(m2.group(1), m2.group(1))
                off_val = m2.group(2)
                off = int(off_val, 16) if off_val.lower().startswith("0x") else int(off_val)
                state[dst] = f"(char *){base} - 0x{off:x}"
            else:
                state[dst] = expr_from_operand(src, state, caller_params)
        elif ins.mnemonic == "xor":
            parts = [normalize_reg(p.strip()) for p in ins.op_str.split(",")]
            if len(parts) == 2 and parts[0] == parts[1]:
                state[parts[0]] = "0"
        elif ins.mnemonic == "call" and i < end_idx - 1:
            state["eax"] = "eax"
    return state


def collect_call_args(
    insns,
    idx: int,
    caller_params: list[str] | None = None,
    reg_state: dict[str, str] | None = None,
) -> tuple[list[str], int]:
    """Walk backward from call at idx collecting push args (cdecl order)."""
    caller_params = caller_params or []
    reg_state = reg_state or build_reg_state(insns, idx, caller_params)
    args: list[str] = []
    j = idx - 1
    while j >= 0 and len(args) < 12:
        ins = insns[j]
        if ins.mnemonic == "push":
            op = ins.op_str.strip()
            push_state = build_reg_state(insns, j, caller_params)
            if op.startswith("0x"):
                args.append(expr_from_operand(op, push_state, caller_params))
            elif re.match(rf"dword ptr \[ebp \+ {_EBP_OFF}\]", op, re.I):
                off = _parse_ebp_offset(op, "+") or 0
                args.append(ebp_param_expr(off, caller_params))
            elif re.match(r"dword ptr \[(\w+) \+ (0x[0-9a-f]+)\]", op):
                m = re.match(r"dword ptr \[(\w+) \+ (0x[0-9a-f]+)\]", op)
                base = push_state.get(m.group(1), m.group(1))
                args.append(mem_read_expr(base, int(m.group(2), 16), "dword"))
            elif re.fullmatch(r"[a-z]+", op):
                reg = normalize_reg(op)
                args.append(push_state.get(reg, reg))
            else:
                args.append(expr_from_operand(op, push_state, caller_params))
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


def reg_store_lhs(reg: str) -> str:
    reg = normalize_reg(reg)
    if reg.endswith("x"):
        return reg
    return reg


def _fmt_string_arg(arg: str, cname: str) -> str:
    if re.match(r"0x00[23][0-9a-f]{5}", arg):
        if cname in ("csstrcpy", "csstrncpy"):
            return f"(char *){arg}"
        return f"(const char *){arg}"
    return arg


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
        ln = re.sub(r"\*\([^)]+\)\(\(char \*\)esp \+ [^)]+\)", "0", ln)
        ln = re.sub(r"\(\(char \*\)esp \+ [^)]+\)", "0", ln)
        if "/* relift:" in ln and ln.strip().startswith("/* relift:") and ln.count("/*") > 1:
            ln = "  /* relift: esp/stack op — manual review */"
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
                _fmt_string_arg(a.strip(), m.group(1))
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


def _type_only(param_type: str) -> str:
    pt = re.sub(r"/\*.*?\*/", "", param_type).strip()
    pt = re.sub(r"\*\s*[A-Za-z_][A-Za-z0-9_]*\s*$", "*", pt)
    pt = re.sub(r"\s+[A-Za-z_][A-Za-z0-9_]*\s*$", "", pt)
    return pt.strip()


def _coerce_pointer_arg(arg: str, param_type: str) -> str:
    pt = _type_only(param_type)
    if "*" not in pt:
        if "(char *)" in arg or arg.startswith("("):
            return "0"
        return arg
    if "/* esp" in arg or "esp */" in arg:
        if "**" in pt.replace(" ", ""):
            return "(void **)0"
        return "(void *)0"
    if re.match(r"\*\(int", arg):
        if pt != "int" and pt != "int16_t" and pt != "char" and pt != "short":
            return f"({pt})(uintptr_t){arg}"
    if re.match(r"\*\(\w+ \*\)", arg) and "data_t" in pt:
        return f"({pt})(uintptr_t){arg}"
    if "(char *)" in arg or arg.startswith("(char *)"):
        if re.fullmatch(r"char \*", pt.replace("const ", "").strip()) or pt.strip() == "const char *":
            return arg
        return f"({pt})({arg})"
    if arg.startswith("*(float *)") and "float" in pt and "*" not in pt.replace("float", ""):
        return f"*({arg})"
    if arg.startswith("(void *)(uintptr_t)"):
        inner = arg[len("(void *)(uintptr_t)") :]
        if re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", inner):
            return f"({_type_only(param_type)})(uintptr_t){inner}"
    return arg


def cast_arg_for_param(arg: str, param_type: str, cname: str) -> str:
    pt = re.sub(r"/\*.*?\*/", "", param_type).replace("const ", "").strip()
    if re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", arg):
        if arg.startswith(("local_", "stack_", "lift_a", "param_")):
            if "*" in pt:
                return f"({_type_only(param_type)})(uintptr_t){arg}"
            return arg
    reg_m = re.fullmatch(r"(eax|ebx|ecx|edx|esi|edi|ebp)", arg)
    if reg_m:
        reg = reg_m.group(1)
        if "*" not in pt and ("short" in pt or pt == "int" or pt.startswith("int ")):
            return reg
        if "*" in pt or pt == "void" or pt.startswith("void "):
            if "**" in pt.replace(" ", ""):
                if "char" in pt:
                    return f"(char **)(uintptr_t){reg}"
            if "unsigned char" in pt:
                return f"(unsigned char *)(uintptr_t){reg}"
            if "wchar" in pt:
                return f"(wchar_t *)(uintptr_t){reg}"
            if "float" in pt:
                return f"(float *)(uintptr_t){reg}"
            if "char" in pt:
                if "const" not in pt:
                    return f"(char *)(uintptr_t){reg}"
                return f"(const char *)(uintptr_t){reg}"
            return f"(void *)(uintptr_t){reg}"
        if "float" in pt or "double" in pt:
            return "0.0f"
        return reg
    if arg == "0":
        if "*" in pt or pt == "void" or pt.startswith("void "):
            if "wchar" in pt:
                return "(wchar_t *)0"
            if "float" in pt:
                return "(float *)0"
            if "**" in pt.replace(" ", ""):
                if "char" in pt:
                    return "(char **)0"
            if "unsigned char" in pt:
                return "(unsigned char *)0"
            if "char" in pt:
                return "(char *)0"
            return "(void *)0"
        if "float" in pt or "double" in pt:
            return "0.0f"
        return "0"
    if re.match(r"0x[0-9a-f]+", arg):
        if "float" in pt and "*" not in pt.replace(" ", ""):
            return "0.0f"
        if "wchar" in pt:
            return f"(wchar_t *){arg}"
        if "*" in pt:
            if "**" in pt.replace(" ", ""):
                if "char" in pt:
                    return f"(char **){arg}"
            if "char" in pt:
                cast = "(char *)" if "const" not in pt else "(const char *)"
                return f"{cast}{arg}"
            return f"(void *){arg}"
        return arg
    if "**" in pt.replace(" ", ""):
        if "char" in pt:
            if re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", arg):
                return f"(char **)(uintptr_t){arg}"
            if arg in ("0", "(char *)0", "(void *)0"):
                return "(char **)0"
            return f"(char **){arg}" if arg.startswith("(") else f"(char **)(uintptr_t){arg}"
    if "unsigned char *" in pt:
        if re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", arg):
            return f"(unsigned char *)(uintptr_t){arg}"
        if arg.startswith("(char *)"):
            return arg.replace("(char *)", "(unsigned char *)", 1)
    if "*" in pt and re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", arg):
        if "wchar" in pt:
            return f"(wchar_t *)(uintptr_t){arg}"
        if "float" in pt:
            return f"(float *)(uintptr_t){arg}"
        if "char" in pt:
            cast = "(char *)(uintptr_t)" if "const" not in pt else "(const char *)(uintptr_t)"
            return f"{cast}{arg}"
        if "data_t" in pt:
            return f"(data_t *)(uintptr_t){arg}"
        return f"(void *)(uintptr_t){arg}"
    if re.fullmatch(r"0\.0f|[0-9]+\.[0-9]+f", arg):
        if "float *" in pt.replace(" ", ""):
            return "(float *)0"
        return arg
    if arg.startswith("(const char *)") and "*" in pt:
        if "wchar" in pt:
            return arg.replace("(const char *)", "(wchar_t *)", 1)
        if "**" in pt.replace(" ", ""):
            return arg.replace("(const char *)", "(char **)", 1)
        return arg.replace("(const char *)", "(void *)", 1)
    if arg.startswith("(char *)(uintptr_t)") and "unsigned char *" in pt:
        return arg.replace("(char *)(uintptr_t)", "(unsigned char *)(uintptr_t)", 1)
    if arg.startswith("(char *)") and "unsigned char *" in pt:
        return arg.replace("(char *)", "(unsigned char *)", 1)
    if arg == "(char *)0" and "unsigned char" in pt:
        return "(unsigned char *)0"
    return _coerce_pointer_arg(arg, param_type)


def resolve_caller_arg(arg: str, caller_params: list[str]) -> str:
    """Map lift_aN / stack args to declared C parameter names when possible."""
    arg = arg.strip()
    m = re.fullmatch(r"lift_a(\d+)", arg)
    if m:
        idx = int(m.group(1))
        if idx < len(caller_params):
            return caller_params[idx]
        return arg
    m = re.fullmatch(r"stack_([0-9a-f]+)", arg)
    if m:
        off = int(m.group(1), 16)
        if off >= 8:
            idx = (off - 8) // 4
            if idx < len(caller_params):
                return caller_params[idx]
    return arg


def fmt_call_line(
    target: int,
    cname: str,
    args: list[str],
    caller_params: list[str] | None = None,
    caller_name: str = "",
) -> str:
    caller_params = caller_params or []
    if caller_name and cname == caller_name:
        return f"  /* relift: tail-call {cname}(); */"
    casted: list[str] = []
    for a in args[:12]:
        a = a.strip()
        if a.startswith("/*"):
            casted.append("0")
        elif re.fullmatch(r"lift_a\d+|stack_[0-9a-f]+", a):
            casted.append(resolve_caller_arg(a, caller_params))
        elif re.fullmatch(r"local_[0-9a-f]+", a):
            casted.append(a)
        elif re.fullmatch(r"(eax|ebx|ecx|edx|esi|edi|ebp|esp)", a):
            casted.append("0" if a == "esp" else a)
        elif re.match(r"0x00[23][0-9a-f]{5}", a):
            casted.append(a)
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
    if cname == "FUN_00091ef0":
        arity = 3
    casted = casted[:arity]
    while len(casted) < arity:
        casted.append("0")
    ptypes = param_map.get(cname, [])
    casted = [
        cast_arg_for_param(a, ptypes[i] if i < len(ptypes) else "int", cname)
        for i, a in enumerate(casted)
    ]
    if cname.startswith("FUN_") and cname not in arity_map:
        return f"  /* relift: {cname}({', '.join(casted)}); */"
    if cname in ("MmQueryAddressProtect", "MmFreeContiguousMemory", "MmAllocateContiguousMemory"):
        return f"  /* relift: {cname}(); */"
    if cname in ("csmemset", "csmemcpy", "csmemmove"):
        casted = [a.replace("(const char *)", "(void *)") for a in casted]
    if cname in ("strncpy", "strncat", "strcpy", "strcat"):
        casted = [a.replace("(void *)", "(char *)") for a in casted]
    if cname in ("csstrcpy", "csstrncpy", "csstrlen"):
        pass
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
    caller_params = ctx.params

    i = 0
    while i < len(insns):
        ins = insns[i]
        if ins.mnemonic == "call" and ins.op_str.startswith("0x"):
            target = int(ins.op_str, 16)
            cname = ctx.addr_name.get(target, f"FUN_{target:08x}")
            reg_state = build_reg_state(insns, i, caller_params)
            args, _ = collect_call_args(insns, i, caller_params, reg_state)
            if len(args) >= 2 and args[-2].startswith("'"):
                pass
            elif len(args) >= 2 and args[-2].startswith("0x") and len(args[-2]) == 10:
                v = int(args[-2], 16)
                if 0x2000000 < v < 0x7FFFFFFF:
                    args[-2] = tag_fourcc(v)
            lines.append(fmt_call_line(target, cname, args, caller_params, ctx.caller_name))
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
                if "esp" in src:
                    src = "0"
                lines.append(f"  /* mem[0x{off:08x}] = {src} */")
        elif ins.mnemonic in ("mov", "fld", "fcomp", "fstp") and "ptr [0x" in ins.op_str:
            lines.append(f"  /* relift: {ins.mnemonic} {ins.op_str} */")
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
    caller_name: str = "",
) -> list[str]:
    ctx = LiftCtx(insns=insns, addr_name=addr_name, params=params, caller_name=caller_name)
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
                    reg_state = build_reg_state(insns, i, params)
                    args, _ = collect_call_args(insns, i, params, reg_state)
                    cast_calls.append(fmt_call_line(t, cname, args, params, ctx.caller_name))
            lines = cast_calls[:24] if cast_calls else [
                f"  /* relift calls: {', '.join(calls[:8])} */"
            ]
        else:
            lines = [
                "  /* relift: no calls detected — manual review */",
                "  (void)0;",
            ]

    sig_ret = ret_kind_from_sig(sig)
    if sig_ret == "void":
        lines = [ln for ln in lines if not re.match(r"\s*return\b", ln)]
    elif sig_ret == "ptr":
        fixed: list[str] = []
        for ln in lines:
            if re.match(r"\s*return 0;\s*$", ln):
                fixed.append("  return NULL;")
            elif re.match(r"\s*return 1;\s*$", ln):
                fixed.append("  return (char *)(uintptr_t)1;")
            else:
                fixed.append(ln)
        lines = fixed
        if not any("return" in ln for ln in lines):
            lines.append("  return NULL;")
    elif sig_ret == "char":
        fixed = []
        for ln in lines:
            if re.match(r"\s*return NULL;\s*$", ln):
                fixed.append("  return 0;")
            else:
                fixed.append(ln)
        lines = fixed
        if not any("return" in ln for ln in lines):
            lines.append("  return 0;")
    elif sig_ret == "scalar" and not any("return" in ln for ln in lines):
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


def disasm_function(md, get_bytes, va: int, end: int) -> list:
    """Disassemble function bytes, following leading jmp thunks."""
    data = get_bytes(va, min(end, va + 0x4000))
    insns = [ins for ins in md.disasm(data, va) if ins.address < end]
    if not insns:
        return insns
    lead = insns[0]
    if lead.mnemonic == "jmp" and lead.op_str.startswith("0x"):
        target = int(lead.op_str, 16)
        if target != va:
            span = min(512, max(end - va, 96))
            try:
                tdata = get_bytes(target, target + span)
            except RuntimeError:
                return insns
            tinsns = list(md.disasm(tdata, target))
            if tinsns and any(ins.mnemonic == "call" for ins in tinsns):
                return tinsns
    return insns


def relift_object(
    object_name: str,
    *,
    occurrence: int = 0,
    dry_run: bool = False,
    force: bool = False,
) -> dict:
    kb = json.loads((ROOT / "kb.json").read_text())
    matches = [o for o in kb["objects"] if o["name"] == object_name]
    if not matches:
        raise SystemExit(f"unknown object {object_name!r}")
    if occurrence >= len(matches):
        raise SystemExit(
            f"occurrence {occurrence} out of range for {object_name!r} "
            f"({len(matches)} entries)"
        )
    obj = matches[occurrence]
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
        span = find_function_def_for_addr(src, name, addr)
        if span is None:
            skipped += 1
            continue
        sig_start, body_start, body_end = span
        body = src[body_start:body_end]
        if not is_stub_body(body) and not force:
            skipped += 1
            continue
        if force and not is_relift_draft(body):
            skipped += 1
            continue
        stub_before += 1

        end = addrs[i + 1][0] if i + 1 < len(addrs) else va + 0x400
        size = end - va
        insns = disasm_function(md, get_bytes, va, end)

        stack_params = infer_stack_params(insns)
        decl_san = GEN.sanitize_decl_for_c(decl)
        params = GEN.parse_params(decl_san)
        if not params or params[0].startswith("unused_arg"):
            params = [param_name(i, off) for i, (off, _) in enumerate(stack_params)]
        if stack_params:
            for i, (off, _) in enumerate(stack_params):
                if i < len(params):
                    continue
                params.append(param_name(i, off))

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
            caller_name=name,
        )
        new_body = "\n" + "\n".join(body_lines) + "\n"
        work.append((body_start, body_end, new_body))

    for body_start, body_end, new_body in sorted(work, key=lambda x: x[0], reverse=True):
        src = src[:body_start] + new_body + src[body_end:]
        relifted += 1

    if relifted and not dry_run:
        src_path.write_text(src)

    disasm_out = ROOT / "artifacts" / f"{GEN.slug(object_name)}_relift_disasm.txt"
    disasm_out.parent.mkdir(parents=True, exist_ok=True)

    return {
        "object": object_name,
        "occurrence": occurrence,
        "source_file": src_rel,
        "relifted": relifted,
        "skipped": skipped,
        "stub_before": stub_before,
        "source": str(src_path),
    }


def main() -> None:
    ap = argparse.ArgumentParser(description="Relift stub bodies from XBE")
    ap.add_argument("--object", action="append", required=True)
    ap.add_argument("--occurrence", type=int, default=0)
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--force", action="store_true", help="Re-relift prior relift drafts")
    args = ap.parse_args()

    total = 0
    results = []
    for obj in args.object:
        r = relift_object(
            obj, occurrence=args.occurrence, dry_run=args.dry_run, force=args.force
        )
        results.append(r)
        total += r["relifted"]
        label = r["object"]
        if r.get("occurrence"):
            label = f"{label}[{r['occurrence']}]"
        print(
            f"{label}: relifted {r['relifted']} "
            f"(skipped {r['skipped']}, stubs {r['stub_before']})"
        )

    print(f"TOTAL relifted: {total}")


if __name__ == "__main__":
    main()
