#!/usr/bin/env python3
"""Batch N: multi-JT + remaining large weak gameplay naked drafts."""
from __future__ import annotations

import importlib.util
import json
import re
import struct
from difflib import SequenceMatcher
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe

BATCH = 56  # overwritten by run_batches.py

# (name, va, end, multi_jt)
# end is exclusive; for JT-at-end singles, end == jt start
TARGETS = [
    ("FUN_001ad260", 0x1AD260, 0x1AD7E0, True),
    ("FUN_001b0d90", 0x1B0D90, 0x1B1290, True),
    ("unit_impulse_to_animation_kind", 0x1A9560, 0x1A97C0, True),
    ("unit_animation_start_action", 0x1A8990, 0x1A8AF8, False),  # single JT at end
    ("FUN_001a2440", 0x1A2440, 0x1A25C0, False),  # single JT at end
    ("FUN_001a0be0", 0x1A0BE0, 0x1A0DB0, False),
    ("structure_test_vector", 0x198CB0, 0x198F10, False),
    ("game_engine_get_score_hud_text", 0xAC4E0, 0xACA70, False),
]

FPU_NULL = {
    "das",
    "daa",
    "aaa",
    "aas",
    "aam",
    "aad",
    "fcos",
    "fsin",
    "fsqrt",
    "fcompp",
    "fchs",
    "fabs",
    "fld1",
    "fldz",
    "fldpi",
    "fldln2",
    "fldlg2",
    "fldl2t",
    "fldl2e",
    "wait",
    "cdq",
    "cwd",
    "cwde",
    "fpatan",
    "fprem",
    "fprem1",
    "fyl2x",
    "fyl2xp1",
    "f2xm1",
    "fscale",
    "frndint",
    "fsincos",
    "fxtract",
    "fdecstp",
    "fincstp",
    "fnop",
}

spec = importlib.util.spec_from_file_location("cmp", "tools/verify/compare_xbe_pe.py")
cmp = importlib.util.module_from_spec(spec)
spec.loader.exec_module(cmp)
chunk = Path("artifacts/batch46_disasm/gen_batch46.py").read_text()
helper = re.search(r"(REGS32 = .*?)^def convert", chunk, re.M | re.S).group(1)
ns = {"re": re}
exec(helper, ns)
_mem_to_att = ns["mem_to_att"]
_op_to_att_base = ns["op_to_att"]
REGS32 = ns["REGS32"]
REGS16 = ns["REGS16"]
REGS8 = ns["REGS8"]


def mem_to_att(mem: str) -> str:
    # Strip segment overrides Capstone sometimes leaves inside [...]
    mem = re.sub(r"^(?:[cdefgs]s):", "", mem.strip())
    return _mem_to_att(mem)


def op_to_att(op: str):
    op = op.strip()
    # dword ptr ds:[...] / dword ptr es:[...]
    m = re.match(
        r"(byte|word|dword|qword)\s+ptr\s+(?:[cdefgs]s:)?\[(.+)\]$", op
    )
    if m:
        return mem_to_att(m.group(2)), m.group(1)
    m = re.match(r"(?:[cdefgs]s:)?\[(.+)\]$", op)
    if m:
        return mem_to_att(m.group(1)), None
    # Bare segment regs (push es / pop fs) — not in REGS32/16/8 maps.
    if op in ("es", "cs", "ss", "ds", "fs", "gs"):
        return f"%{op}", None
    return _op_to_att_base(op)


CALLMAP: dict[int, str] = {}
PTR: dict[str, str] = {}
for m in re.finditer(r"(0x[0-9a-fA-F]+):\s*[\'\"](\w+)[\'\"]", chunk):
    CALLMAP[int(m.group(1), 16)] = m.group(2)
for m in re.finditer(r"[\"'](\w+)[\"']\s*:\s*[\"'](static .+?)[\"']", chunk):
    PTR.setdefault(m.group(1), m.group(2))

kb = json.load(open("kb.json"))
addr_meta: dict[int, dict] = {}


def walk(o):
    if isinstance(o, dict):
        if "addr" in o and "decl" in o:
            a = o["addr"]
            if isinstance(a, str) and a.startswith("0x"):
                addr_meta[int(a, 16)] = o
        for v in o.values():
            walk(v)
    elif isinstance(o, list):
        for v in o:
            walk(v)


walk(kb)

SEED_DECLS = {
    0x1AD260: {
        "addr": "0x1ad260",
        "name": "FUN_001ad260",
        "decl": "char FUN_001ad260(int unit_handle, int16_t anim_state);",
    },
    0x1B0D90: {
        "addr": "0x1b0d90",
        "name": "FUN_001b0d90",
        "decl": "short FUN_001b0d90(int unit_handle, char *anim_state);",
    },
    0x1A9560: {
        "addr": "0x1a9560",
        "name": "unit_impulse_to_animation_kind",
        "decl": "int16_t unit_impulse_to_animation_kind(int16_t impulse_index, int16_t *out_update_kind);",
    },
    0x1A8990: {
        "addr": "0x1a8990",
        "name": "unit_animation_start_action",
        "decl": "void unit_animation_start_action(int object_handle, int16_t state);",
    },
    0x1A2440: {
        "addr": "0x1a2440",
        "name": "FUN_001a2440",
        "decl": "void FUN_001a2440(int unit_handle);",
    },
    0x1A0BE0: {
        "addr": "0x1a0be0",
        "name": "FUN_001a0be0",
        "decl": "void FUN_001a0be0(float vertical_speed, int unit_handle);",
    },
    0x198CB0: {
        "addr": "0x198cb0",
        "name": "structure_test_vector",
        "decl": "char structure_test_vector(float *point, float *direction, float *out_point, int16_t *out_collection_index, int16_t *out_bsp_index);",
    },
    0xAC4E0: {
        "addr": "0xac4e0",
        "name": "game_engine_get_score_hud_text",
        "decl": "bool game_engine_get_score_hud_text(int player_handle, int param_2, int hud_player, wchar_t *buffer, int buffer_len);",
    },
}
addr_meta.update(SEED_DECLS)


def ensure(addr: int) -> str:
    if addr in CALLMAP and CALLMAP[addr] in PTR:
        return CALLMAP[addr]
    key = CALLMAP.get(addr) or f"c{addr:x}"
    CALLMAP[addr] = key
    if key in PTR:
        return key
    meta = addr_meta.get(addr)
    if meta is None:
        # Mid-function / untracked target. Capstone only needs a call/jmp
        # mnemonic — point at an empty local stub (no bare {} for .format).
        PTR[key] = (
            "static void {p}_"
            + key
            + "_tgt(void) {{ return; }}\n"
            "static void (*const {p}_"
            + key
            + ")(void) = {p}_"
            + key
            + "_tgt;"
        )
        return key
    decl = meta["decl"].rstrip(";")
    m = re.match(r"^(.*?)\b([A-Za-z_][A-Za-z0-9_]*)\s*\((.*)\)\s*$", decl)
    if not m:
        raise SystemExit(f"bad decl {addr:#x} {decl}")
    ret, name, args = m.group(1).strip(), m.group(2), m.group(3).strip()
    args = re.sub(r"\s*@<[a-z]+>", "", args)
    if name == "datum_get":
        PTR[key] = (
            "static void *(*const {p}_"
            + key
            + ")(void *, int) = (void *(*)(void *, int))datum_get;"
        )
    else:
        # kb decls often carry __stdcall/__fastcall on the return side; our C
        # stubs are frequently plain cdecl. Cast through void* so -Werror
        # incompatible-function-pointer-types does not fail the build.
        rhs = f"(void *){name}" if re.search(r"\b__(?:stdcall|fastcall)\b", ret) else name
        if args in ("", "void"):
            PTR[key] = f"static {ret} (*const {{p}}_{key})(void) = {rhs};"
        else:
            PTR[key] = f"static {ret} (*const {{p}}_{key})({args}) = {rhs};"
    return key


xbe = Xbe.from_file("halo-patched/cachebeta.xbe")
md = Cs(CS_ARCH_X86, CS_MODE_32)
pe = pefile.PE("build/halo")
outdir = Path("artifacts/batch56_disasm")
outdir.mkdir(exist_ok=True)


def get_bytes(va: int, end: int | None = None, n: int | None = None) -> bytes:
    if n is None:
        assert end is not None
        n = end - va
    for sec in xbe.sections.values():
        s = sec.header.virtual_addr
        if s <= va < s + sec.header.virtual_size:
            return bytes(sec.data[va - s : va - s + n])
    raise SystemExit(f"va {va:#x} not in xbe")


def find_jts(va: int, end: int) -> list[dict]:
    """Find jump tables in [va,end), limiting each table so it does not overlap the next JT/end."""
    raw_jts = []
    for insn in md.disasm(get_bytes(va, end), va):
        if insn.mnemonic != "jmp" or "dword" not in insn.op_str:
            continue
        if "*4" not in insn.op_str.replace(" ", ""):
            continue
        m = re.search(r"\* ?4 \+ (0x[0-9a-f]+)", insn.op_str)
        if not m:
            m = re.search(r"0x([0-9a-f]+)", insn.op_str)
            if not m:
                continue
            jt = int(m.group(1), 16)
        else:
            jt = int(m.group(1), 16)
        # JT may live well past true_end (shared/post-body tables). Accept any
        # table after the jmp whose first entries target back into [va, …).
        if jt <= insn.address:
            continue
        reg = None
        for r in ("eax", "ecx", "edx", "ebx", "esi", "edi"):
            if f"{r}*4" in insn.op_str.replace(" ", ""):
                reg = r
                break
        raw_jts.append({"jt": jt, "reg": reg, "at": insn.address})
    # dedupe by jt addr
    by = {}
    for j in raw_jts:
        by.setdefault(j["jt"], j)
    ordered = sorted(by.values(), key=lambda x: x["jt"])
    out = []
    for i, j in enumerate(ordered):
        if i + 1 < len(ordered):
            limit = ordered[i + 1]["jt"]
        else:
            # Post-body / JT-at-end: read a generous window.
            limit = j["jt"] + 256
        raw = get_bytes(j["jt"], min(j["jt"] + 256, limit + 4))
        ents = []
        for k in range(64):
            if j["jt"] + 4 * (k + 1) > limit:
                break
            if 4 * k + 4 > len(raw):
                break
            t = struct.unpack_from("<I", raw, 4 * k)[0]
            # Accept targets in the function body (may extend past `end`).
            if not (va <= t < j["jt"]):
                break
            ents.append(t)
        if len(ents) < 2:
            continue
        j = dict(j)
        j["ents"] = ents
        j["nents"] = len(ents)
        j["tend"] = j["jt"] + 4 * len(ents)
        out.append(j)
    return out


def parse_with_gaps(va: int, end: int, jts: list[dict]) -> list[tuple]:
    ranges = []
    cur = va
    for j in sorted(jts, key=lambda x: x["jt"]):
        if cur < j["jt"]:
            ranges.append((cur, j["jt"]))
        cur = max(cur, j["tend"])
    if cur < end:
        ranges.append((cur, end))
    parsed = []
    for a, b in ranges:
        data = get_bytes(a, b)
        for insn in md.disasm(data, a):
            if insn.address + insn.size > b:
                break
            parsed.append((insn.address, insn.mnemonic, insn.op_str))
    return parsed


def convert(name: str, parsed, jts: list[dict]) -> list[str]:
    """Convert parsed insns; jts may be empty, one, or many."""
    jt_by_addr = {j["jt"]: i for i, j in enumerate(jts)}
    all_ents: list[int] = []
    for j in jts:
        all_ents.extend(j["ents"])

    jtargets = set(all_ents)
    body_addrs = {a for a, _, _ in parsed}
    body_lo = min(body_addrs) if body_addrs else 0
    body_hi = max(body_addrs) + 1 if body_addrs else 0
    for addr, mnem, ops in parsed:
        if mnem.startswith("j") and re.fullmatch(r"0x[0-9a-f]+", ops):
            t = int(ops, 16)
            # Only local labels; external tail-jmps become indirect via ensure().
            if body_lo <= t < body_hi or t in body_addrs:
                jtargets.add(t)
    label_of: dict[int, int] = {}
    n = 1
    for a, _, _ in parsed:
        if a in jtargets:
            label_of[a] = n
            n += 1
    for t in all_ents:
        if t not in label_of:
            raise SystemExit(f"{name} missing case label {t:#x}")

    # single-JT uses legacy label .Lname_jt; multi uses .Lname_jtN
    single = len(jts) == 1
    out: list[str] = []
    todos: list[str] = []

    for addr, mnem, ops in parsed:
        if addr in label_of:
            out.append(f".L{name}_{label_of[addr]}:")
        parts = [p.strip() for p in ops.split(",")] if ops else []

        if mnem == "jmp" and "dword ptr" in ops and "*4" in ops.replace(" ", ""):
            m = re.search(r"\* ?4 \+ (0x[0-9a-f]+)", ops)
            if not m:
                m = re.search(r"0x([0-9a-f]+)", ops)
            jt = int(m.group(1), 16)
            reg = None
            for r in ("eax", "ecx", "edx", "ebx", "esi", "edi"):
                if f"{r}*4" in ops.replace(" ", ""):
                    reg = r
                    break
            if jt in jt_by_addr and reg:
                idx = jt_by_addr[jt]
                reg = jts[idx]["reg"] or reg
                if single:
                    out.append(f"  jmp *.L{name}_jt(,%%{reg},4)")
                else:
                    out.append(f"  jmp *.L{name}_jt{idx}(,%%{reg},4)")
            elif reg:
                # JT outside find_jts window (mis-sized end / filtered table):
                # keep absolute XBE table address.
                out.append(f"  jmp *{jt:#x}(,%%{reg},4)")
            else:
                todos.append(f"jmp-table {ops}")
            continue

        if mnem in ("jmp", "call") and ops in REGS32:
            out.append(f"  {mnem} *%%{ops}")
            continue
        if mnem in ("jmp", "call") and "ptr" in ops and "[" in ops:
            a, _ = op_to_att(ops)
            out.append(f"  {mnem} *{a}")
            continue
        if mnem.startswith("rep"):
            if "stosd" in mnem or "stosd" in ops:
                out.append("  rep stosl")
                continue
            if "stosb" in mnem or "stosb" in ops:
                out.append("  rep stosb")
                continue
            if "stosw" in mnem or "stosw" in ops:
                out.append("  rep stosw")
                continue
            if "movsd" in mnem or "movsd" in ops:
                out.append("  rep movsl")
                continue
            if "movsb" in mnem or "movsb" in ops:
                out.append("  rep movsb")
                continue
            if "movsw" in mnem or "movsw" in ops:
                out.append("  rep movsw")
                continue
            todos.append(f"{mnem} {ops}")
            continue
        if mnem == "stosw":
            out.append("  stosw")
            continue
        if mnem == "mul":
            a, _ = op_to_att(parts[0])
            out.append(f"  mull {a}")
            continue
        if mnem == "div":
            a, _ = op_to_att(parts[0])
            out.append(f"  divl {a}")
            continue
        if mnem == "idiv":
            a, _ = op_to_att(parts[0])
            suf = "w" if parts[0] in REGS16 else ("b" if parts[0] in REGS8 else "l")
            out.append(f"  idiv{suf} {a}")
            continue
        if mnem == "nop":
            out.append("  nop")
            continue
        if mnem.startswith("j") and re.fullmatch(r"0x[0-9a-f]+", ops):
            t = int(ops, 16)
            if t in label_of:
                out.append(f"  {mnem} .L{name}_{label_of[t]}")
            else:
                # Outside-body target: raw XBE bytes preserve Capstone mnemonic.
                # (jcc cannot be indirect; PE relative disp would be wrong anyway.)
                raw = get_bytes(addr, n=16)
                insn = next(md.disasm(raw, addr), None)
                if insn is None:
                    raise SystemExit(f"{name}: bad ext branch at {addr:#x}")
                out.append(
                    "  .byte " + ", ".join(f"0x{x:02x}" for x in insn.bytes)
                )
            continue
        if mnem.startswith("j"):
            out.append(f"  {mnem} .L{name}_{label_of[int(ops, 16)]}")
            continue
        if mnem == "call":
            out.append(f"  call *%[{ensure(int(ops, 16))}]")
            continue
        if mnem == "ret":
            out.append("  ret")
            continue
        if mnem in FPU_NULL:
            out.append(f"  {mnem}")
            continue
        if mnem == "fnstsw":
            out.append("  fnstsw %%ax")
            continue
        if mnem == "fxch":
            st = parts[0] if parts else "st(1)"
            if st == "st":
                st = "st(0)"
            out.append(f"  fxch %%{st}")
            continue
        if mnem == "lea":
            mm = re.match(r"(?:dword ptr )?(?:[cdefgs]s:)?\[(.+)\]", parts[1])
            out.append(f"  leal {mem_to_att(mm.group(1))}, %%{parts[0]}")
            continue
        if mnem in ("push", "pop"):
            # Segment-reg push/pop from misdecoded post-body tables: emit raw
            # XBE bytes so Capstone still matches without AT&T segment syntax.
            if parts[0] in ("es", "cs", "ss", "ds", "fs", "gs"):
                raw = get_bytes(addr, n=16)
                insn = next(md.disasm(raw, addr), None)
                if insn is None:
                    todos.append(f"{mnem} {ops}")
                    out.append(f"  /* TODO {mnem} {ops} */")
                else:
                    out.append(
                        "  .byte " + ", ".join(f"0x{x:02x}" for x in insn.bytes)
                    )
                continue
            a, sz = op_to_att(parts[0])
            if parts[0] in REGS32:
                suf = "l"
            elif parts[0] in REGS16:
                suf = "w"
            elif parts[0] in REGS8:
                suf = "b"
            elif sz == "word":
                suf = "w"
            elif sz == "byte":
                suf = "b"
            else:
                suf = "l"
            out.append(f"  {mnem}{suf} {a}")
            continue
        if mnem in ("inc", "dec", "neg", "not"):
            a, sz = op_to_att(parts[0])
            suf = (
                "w"
                if sz == "word" or parts[0] in REGS16
                else ("b" if sz == "byte" or parts[0] in REGS8 else "l")
            )
            if sz == "dword":
                suf = "l"
            out.append(f"  {mnem}{suf} {a}")
            continue
        if mnem in ("shl", "shr", "sar"):
            s = (
                f"${parts[1]}"
                if re.fullmatch(r"-?0x[0-9a-fA-F]+|-?\d+", parts[1])
                else f"%%{parts[1]}"
            )
            suf = "w" if parts[0] in REGS16 else ("b" if parts[0] in REGS8 else "l")
            a, _ = op_to_att(parts[0])
            out.append(f"  {mnem}{suf} {s}, {a}")
            continue
        if mnem.startswith("set"):
            a, _ = op_to_att(parts[0])
            out.append(f"  {mnem} {a}")
            continue
        if mnem in ("movsx", "movzx"):
            src, sz = op_to_att(parts[1])
            if parts[1] in REGS16:
                sz = "word"
            if parts[1] in REGS8:
                sz = "byte"
            if mnem == "movzx" and parts[0] in REGS16 and sz == "byte":
                out.append(f"  movzbw {src}, %%{parts[0]}")
                continue
            if mnem == "movsx":
                if parts[0] in REGS16 and sz == "byte":
                    out.append(f"  movsbw {src}, %%{parts[0]}")
                else:
                    out.append(
                        ("  movswl " if sz == "word" else "  movsbl ")
                        + f"{src}, %%{parts[0]}"
                    )
            else:
                out.append(
                    ("  movzwl " if sz == "word" else "  movzbl ")
                    + f"{src}, %%{parts[0]}"
                )
            continue
        if mnem == "fld" and parts and parts[0].startswith("st"):
            st = parts[0] if parts[0] != "st" else "st(0)"
            out.append(f"  fld %%{st}")
            continue
        if mnem == "fstp" and parts and parts[0].startswith("st"):
            out.append(f"  fstp %%{parts[0]}")
            continue
        if mnem in ("faddp", "fsubp", "fmulp", "fdivp", "fsubrp", "fdivrp"):
            # Clang AT&T often swaps fsubp/fsubrp; emit exact MSVC bytes.
            st = parts[0] if parts else "st(1)"
            if st == "st":
                st = "st(0)"
            m = re.fullmatch(r"st\((\d)\)", st)
            idx = int(m.group(1)) if m else 1
            base = {
                "faddp": 0xC0,
                "fmulp": 0xC8,
                "fsubrp": 0xE0,
                "fsubp": 0xE8,
                "fdivrp": 0xF0,
                "fdivp": 0xF8,
            }[mnem]
            out.append(f"  .byte 0xde, {hex(base + idx)}")
            continue
        if mnem == "fcom" and parts and parts[0].startswith("st"):
            # Gas rejects "fcom %st(1), %st(0)"; one-operand form is required.
            out.append(f"  fcom %%{parts[0]}")
            continue
        if mnem in (
            "fmul",
            "fadd",
            "fsub",
            "fdiv",
            "fsubr",
            "fdivr",
        ) and parts and parts[0].startswith("st"):
            if len(parts) == 1:
                out.append(f"  {mnem} %%{parts[0]}, %%st(0)")
            else:
                out.append(f"  {mnem} %%{parts[1]}, %%{parts[0]}")
            continue
        if mnem == "fcomp" and parts and parts[0].startswith("st"):
            out.append(f"  fcomp %%{parts[0]}")
            continue
        if (
            mnem.startswith("f")
            or mnem in ("fiadd", "fisub", "fimul", "fidiv", "fild")
        ) and parts:
            a, sz = op_to_att(parts[0])
            if mnem in ("fild", "fiadd", "fisub", "fimul", "fidiv"):
                out.append(f'  {mnem}{"l" if sz != "word" else "s"} {a}')
                continue
            out.append(f'  {mnem}{"l" if sz == "qword" else "s"} {a}')
            continue
        if mnem in (
            "mov",
            "add",
            "sub",
            "xor",
            "and",
            "or",
            "cmp",
            "test",
            "xchg",
            "sbb",
            "adc",
        ):
            d, szd = op_to_att(parts[0])
            s, szs = op_to_att(parts[1])
            if (
                parts[0] in REGS8
                or parts[1] in REGS8
                or szd == "byte"
                or szs == "byte"
            ):
                suf = "b"
            elif (
                parts[0] in REGS16
                or parts[1] in REGS16
                or szd == "word"
                or szs == "word"
            ):
                suf = "w"
            else:
                suf = "l"
            out.append(f"  {mnem}{suf} {s}, {d}")
            continue
        if mnem == "imul":
            if len(parts) == 3:
                imm = parts[2]
                if not imm.startswith("0x") and not imm.isdigit() and not (
                    imm.startswith("-") and imm[1:].isdigit()
                ):
                    # Capstone usually puts imm last as bare int / 0x..
                    pass
                if not imm.startswith("$"):
                    imm_s = f"${imm}"
                else:
                    imm_s = imm
                if parts[0] in REGS16 or parts[1] in REGS16:
                    out.append(f"  imulw {imm_s}, %%{parts[1]}, %%{parts[0]}")
                else:
                    out.append(f"  imull {imm_s}, %%{parts[1]}, %%{parts[0]}")
                continue
            if len(parts) == 2:
                if parts[0] in REGS16:
                    s, _ = op_to_att(parts[1])
                    out.append(f"  imulw {s}, %%{parts[0]}")
                    continue
                s, _ = op_to_att(parts[1])
                out.append(f"  imull {s}, %%{parts[0]}")
                continue
            a, _ = op_to_att(parts[0])
            if parts[0] in REGS8 or a in {f"%%{r}" for r in REGS8}:
                out.append(f"  imulb {a}")
            elif parts[0] in REGS16 or a in {f"%%{r}" for r in REGS16}:
                out.append(f"  imulw {a}")
            else:
                out.append(f"  imull {a}")
            continue
        if mnem in ("clc", "stc", "cld", "std", "cmc", "sahf", "lahf"):
            out.append(f"  {mnem}")
            continue
        # SSE / unknown: emit raw XBE bytes (Capstone will decode identically).
        raw = get_bytes(addr, n=16)
        insn = next(md.disasm(raw, addr), None)
        if insn is None:
            todos.append(f"{mnem} {ops}")
            out.append(f"  /* TODO {mnem} {ops} */")
        else:
            out.append("  .byte " + ", ".join(f"0x{x:02x}" for x in insn.bytes))

    if todos:
        raise SystemExit(f"{name}: {todos[:8]}")

    # Emit JT tables in .rdata
    for i, j in enumerate(jts):
        out.append('.section .rdata,"dr"')
        label = f".L{name}_jt" if single else f".L{name}_jt{i}"
        out.append(f"{label}:")
        for e in j["ents"]:
            out.append(f"  .long .L{name}_{label_of[e]}")
        out.append(".text")
    return out


def sig_from_decl(name: str, decl: str) -> str:
    decl = decl.rstrip(";")
    m = re.match(r"^(.*?)\b" + re.escape(name) + r"\s*\((.*)\)\s*$", decl)
    ret, args = m.group(1).strip(), m.group(2)
    # Match existing C decls (often cdecl) — do not redeclare with kb's
    # __stdcall/__fastcall attribute on the definition.
    ret = re.sub(r"\b__(?:stdcall|fastcall)\b", "", ret)
    ret = re.sub(r"\s+", " ", ret).strip()
    args = re.sub(r"\s*@<[a-z]+>", "", args)
    if args.strip() in ("", "void"):
        return f"{ret} {name}(void)"
    parts = []
    for arg in args.split(","):
        arg = arg.strip()
        if not arg or arg == "void":
            continue
        toks = arg.split()
        if len(toks) >= 2:
            parts.append(
                " ".join(toks[:-1]) + f" {toks[-1]} __attribute__((unused))"
            )
        else:
            # Type-only param in kb decl (e.g. "bool") — invent a name.
            parts.append(f"{arg} a{len(parts)} __attribute__((unused))")
    return f"{ret} {name}({', '.join(parts)})"


def make_body(name: str, va: int, sig: str, att: list[str], order: list[str], pref: str) -> str:
    ptrs = [PTR[k].format(p=pref) for k in order]
    # Fix common cast hazards
    ptrs = [
        p.replace("= datum_get;", "= (void *(*)(void *, int))datum_get;").replace(
            "= real_matrix3x3_transform_vector;",
            "= (void (*)(void *, float *, float *))real_matrix3x3_transform_vector;",
        )
        for p in ptrs
    ]
    # kb often marks XDK/D3D callees __stdcall while C decls are cdecl —
    # silence -Wincompatible-function-pointer-types via void*.
    fixed = []
    for p in ptrs:
        if "__stdcall" in p and " = (void *)" not in p and " = (void*)" not in p:
            p = re.sub(r"=\s*([A-Za-z_][A-Za-z0-9_]*)\s*;", r"= (void *)\1;", p, count=1)
        fixed.append(p)
    ptrs = fixed
    asm_lines = []
    for l in att:
        if not l.strip():
            continue
        # Escape quotes inside .section .rdata,"dr"
        s = l.strip().replace('"', '\\"')
        asm_lines.append(f'      "{s}\\n\\t"')
    asm = "\n".join(asm_lines)
    keystr = ", ".join(f'[{k}] "m"({pref}_{k})' for k in order) if order else ""
    colon_operands = f"\n      : {keystr}" if keystr else "\n      :"
    return f"""#if defined(__clang__)
{chr(10).join(ptrs)}

__attribute__((naked, noinline))
{sig}
{{
  __asm__ volatile(
{asm}
      :{colon_operands}
      : "memory");
}}
#else
#error "{name}: clang naked draft required"
#endif
"""


def _is_defn_site(text: str, name: str, pos: int) -> bool:
    """True if text[pos:] looks like a definition `name(...) {`, not a call."""
    m = re.match(rf"{re.escape(name)}\s*\(", text[pos:])
    if not m:
        return False
    i = pos + m.end()
    depth = 1
    while i < len(text) and depth:
        c = text[i]
        if c == ";" and depth == 1:
            return False  # prototype / call
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
        i += 1
        if i - pos > 800:
            return False
    # skip whitespace/comments to '{'
    while i < len(text) and text[i] in " \t\r\n":
        i += 1
    return i < len(text) and text[i] == "{"


def find_src(name: str) -> Path:
    # Find files containing a real definition site for name.
    name_re = re.compile(rf"\b{re.escape(name)}\s*\(")
    fallback = None
    hits: list[Path] = []
    for p in Path("src/halo").rglob("*.c"):
        text = p.read_text(errors="ignore")
        ok = False
        for m in name_re.finditer(text):
            # Skip occurrences inside line/block comments roughly.
            line_start = text.rfind("\n", 0, m.start()) + 1
            line = text[line_start : m.start()]
            if "//" in line:
                continue
            before = text[: m.start()]
            if before.rfind("/*") > before.rfind("*/"):
                continue
            if _is_defn_site(text, name, m.start()):
                ok = True
                break
        if not ok:
            continue
        if p.name == "kb_common_stubs.c":
            fallback = p
            continue
        hits.append(p)
    if hits:
        hits.sort(key=lambda q: str(q))
        return hits[0]
    if fallback is not None:
        return fallback
    raise SystemExit(f"no file for {name}")


def inject(name: str, va: int, body: str, path: Path) -> None:
    text = path.read_text()
    comment = f"/* {name} ({hex(va)}) — XBE naked draft (batch {BATCH}). */\n"
    prior_re = re.compile(
        rf"/\* {re.escape(name)} \(0x[0-9a-fA-F]+\) — XBE naked draft \(batch \d+\)\. \*/\n"
        rf"#if defined\(__clang__\)\n"
        rf".*?"
        rf"#else\n"
        rf'#error "{re.escape(name)}: clang naked draft required"\n'
        rf"#endif\n?",
        re.S,
    )
    matches = list(prior_re.finditer(text))
    if matches:
        start = matches[0].start()
        pieces = []
        last = 0
        for m in matches:
            pieces.append(text[last : m.start()])
            last = m.end()
        pieces.append(text[last:])
        cleaned = "".join(pieces)
        path.write_text(
            cleaned[:start]
            + comment
            + body
            + ("\n" if not body.endswith("\n") else "")
            + cleaned[start:]
        )
        print(f"  replaced {name} ({len(matches)} prior) -> {path}")
        return
    # Real definitions only: name(...) { … } — never prototypes ending in ';',
    # never call sites like `if (!name(...)) {`, and never a '{' inside a
    # comment (e.g. "({size, offset})").
    def_pat = re.compile(
        rf"^(?:(?:__attribute__\s*\(\([^;]*?\)\)\s*)|(?:__declspec\s*\([^)]*\)\s*)|(?:static\s+)|(?:inline\s+)|(?:[\w\*]+\s+))+{re.escape(name)}\s*\(",
        re.M,
    )
    name_positions: list[int] = []
    for cand in def_pat.finditer(text):
        nm = re.search(rf"\b{re.escape(name)}\s*\(", text[cand.start() : cand.start() + 240])
        if nm:
            name_positions.append(cand.start() + nm.start())
    if not name_positions:
        for cand in re.finditer(rf"\b{re.escape(name)}\s*\(", text):
            if _is_defn_site(text, name, cand.start()):
                name_positions.append(cand.start())
    m = None
    brace = None
    name_pos = None
    for name_pos in name_positions:
        if not _is_defn_site(text, name, name_pos):
            continue
        line_start = text.rfind("\n", 0, name_pos) + 1
        before_txt = text[:line_start]
        last_open = before_txt.rfind("/*")
        last_close = before_txt.rfind("*/")
        if last_open != -1 and last_open > last_close:
            continue  # inside block comment
        # Scan from '(' of the declarator to the function-body '{',
        # skipping comments/strings; reject if ';' comes first.
        i = text.find("(", name_pos)
        if i < 0:
            continue
        depth_p = 0
        j = i
        in_line = in_block = in_str = False
        str_ch = ""
        body_brace = None
        while j < len(text):
            ch = text[j]
            nxt = text[j + 1] if j + 1 < len(text) else ""
            if in_line:
                if ch == "\n":
                    in_line = False
                j += 1
                continue
            if in_block:
                if ch == "*" and nxt == "/":
                    in_block = False
                    j += 2
                    continue
                j += 1
                continue
            if in_str:
                if ch == "\\":
                    j += 2
                    continue
                if ch == str_ch:
                    in_str = False
                j += 1
                continue
            if ch == "/" and nxt == "/":
                in_line = True
                j += 2
                continue
            if ch == "/" and nxt == "*":
                in_block = True
                j += 2
                continue
            if ch in ('"', "'"):
                in_str = True
                str_ch = ch
                j += 1
                continue
            if ch == "(":
                depth_p += 1
            elif ch == ")":
                depth_p -= 1
            elif depth_p == 0:
                if ch == ";":
                    body_brace = None
                    break  # forward declaration
                if ch == "{":
                    body_brace = j
                    break
            j += 1
        if body_brace is None:
            continue
        attr_lookback = text[max(0, name_pos - 80) : name_pos]
        if "__attribute__" in attr_lookback and "naked" in attr_lookback:
            continue
        m = True
        brace = body_brace
        break
    if not m or brace is None or name_pos is None:
        raise SystemExit(f"no def {name} in {path}")
    line_start = text.rfind("\n", 0, name_pos) + 1
    before_txt = text[:line_start]
    start = line_start
    end_c = before_txt.rfind("*/")
    if (
        end_c != -1
        and before_txt[end_c + 2 :].strip() == ""
        and before_txt[end_c + 2 :].count("\n") <= 3
    ):
        start_c = before_txt.rfind("/*", 0, end_c)
        if start_c != -1:
            start = start_c
    depth = 0
    i = brace
    endpos = None
    in_line = in_block = in_str = False
    str_ch = ""
    while i < len(text):
        ch = text[i]
        nxt = text[i + 1] if i + 1 < len(text) else ""
        if in_line:
            if ch == "\n":
                in_line = False
            i += 1
            continue
        if in_block:
            if ch == "*" and nxt == "/":
                in_block = False
                i += 2
                continue
            i += 1
            continue
        if in_str:
            if ch == "\\":
                i += 2
                continue
            if ch == str_ch:
                in_str = False
            i += 1
            continue
        if ch == "/" and nxt == "/":
            in_line = True
            i += 2
            continue
        if ch == "/" and nxt == "*":
            in_block = True
            i += 2
            continue
        if ch in ('"', "'"):
            in_str = True
            str_ch = ch
            i += 1
            continue
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0:
                endpos = i + 1
                if endpos < len(text) and text[endpos] == "\n":
                    endpos += 1
                break
        i += 1
    if endpos is None:
        raise SystemExit(f"no body end for {name}")
    path.write_text(text[:start] + comment + body + "\n" + text[endpos:])
    print(f"  injected {name} -> {path}")



before = {}
for name, va, end, multi in TARGETS:
    # Iteratively discover post-body JTs / case targets without scanning
    # table bytes as code (find_jts only walks insn stream in [va,end)).
    for _round in range(6):
        jts = find_jts(va, end)
        new_end = end
        for j in jts:
            new_end = max(new_end, j["tend"])
            for t in j["ents"]:
                new_end = max(new_end, t + 1)
        if new_end <= end:
            break
        # Grow only through the next contiguous code/table blob; avoid
        # leaping across unrelated functions via a single huge table read.
        if new_end - end > 0x2000:
            # Cap growth; prefer JT tend of tables referenced from current body.
            capped = end
            for j in jts:
                if j["at"] < end:
                    capped = max(capped, j["tend"])
                    for t in j["ents"]:
                        if t < end + 0x1000:
                            capped = max(capped, t + 1)
            new_end = min(new_end, max(capped, end + 0x100))
        print(f"NOTE {name}: extend end {end:#x} -> {new_end:#x} via JTs")
        end = new_end
    jts = find_jts(va, end)
    if multi and len(jts) < 2:
        print(f"WARN {name}: expected multi-JT, got {len(jts)}")
    if not multi and len(jts) > 1:
        print(f"WARN {name}: unexpected multi, using end={end:#x} jts={len(jts)}")

    if jts and not multi and jts[0]["jt"] == end:
        # classic single JT-at-end: parse body only, one table
        parsed = [
            (i.address, i.mnemonic, i.op_str)
            for i in md.disasm(get_bytes(va, end), va)
        ]
        jts_use = jts[:1]
    elif jts:
        parsed = parse_with_gaps(va, end, jts)
        jts_use = jts
    else:
        parsed = [
            (i.address, i.mnemonic, i.op_str)
            for i in md.disasm(get_bytes(va, end), va)
        ]
        jts_use = []

    xb = cmp.xbe_bytes(xbe, va, end)
    pb, pa = cmp.pe_fn_bytes(pe, name)
    score = (
        SequenceMatcher(
            None, cmp.mnemonics(xb, va), cmp.mnemonics(pb, pa), autojunk=False
        ).ratio()
        * 100
    )
    before[name] = {
        "score": round(score, 1),
        "va": hex(va),
        "end": hex(end),
        "xbe_ins": len(parsed),
        "njts": len(jts_use),
        "jt_ents": [j["nents"] for j in jts_use],
    }
    print(
        f"{name}: before {score:.1f}% parsed={len(parsed)} njts={len(jts_use)} ents={[j['nents'] for j in jts_use]}"
    )

    att = convert(name, parsed, jts_use)
    decl = addr_meta[va]["decl"]
    sig = sig_from_decl(name, decl)
    pref = f"b{va:x}"
    order: list[str] = []
    seen: set[str] = set()
    for l in att:
        for k in re.findall(r"%\[(\w+)\]", l):
            if k not in seen:
                seen.add(k)
                order.append(k)
    for k in order:
        if k not in PTR:
            addr = next(a for a, kk in CALLMAP.items() if kk == k)
            ensure(addr)
    body = make_body(name, va, sig, att, order, pref)
    (outdir / f"{name}.naked.c").write_text(body)
    inject(name, va, body, find_src(name))

json.dump(before, open("artifacts/batch56_before.json", "w"), indent=2)
print("DONE", len(before))
