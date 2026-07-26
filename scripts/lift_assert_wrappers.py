#!/usr/bin/env python3
"""Lift assert-guarded thin wrappers (network/sound/saved/devices/…) → Unicorn-prove.

Prefer untapped clusters: scenario, sound, tag_files, network, saved_games, devices.
Pull-before-push; union ported:true on kb conflict.
"""
from __future__ import annotations

import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
sys.path.insert(0, str(ROOT / "tools" / "equivalence"))

from capstone import CS_ARCH_X86, CS_MODE_32, Cs  # noqa: E402
from xbe import Xbe  # noqa: E402
from xbe_to_coff import load_kb, xbe_bytes  # noqa: E402
from lift_inventory_batch4 import find_naked_block  # noqa: E402
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
    func_name,
    is_naked_near_def,
    resolve_src,
    run_unicorn,
)

DISPLAY_ASSERT = 0x8D9F0
SYSTEM_EXIT = 0x8E2F0
OBJECT_GET = 0x13D680
OBJECT_TRY = 0x13D640
DATUM_GET = 0x119320
COMMIT_EVERY = 10
SKIP_SRC = ("xdk/", "d3d", "dsound", "libcmt", "bink", "xnet", "xapilib", "kb_common")
PREF = (
    "scenario/",
    "sound/",
    "tag_files/",
    "network",
    "saved games",
    "saved_games",
    "devices/",
    "camera/",
    "game/",
    "interface/",
    "effects/",
    "ai/",
    "objects/",
    "units/",
    "items/",
    "physics/",
    "structures/",
    "cutscene/",
    "cseries/",
    "main/",
    "text/",
    "bungie_net/",
    "input/",
    "models/",
    "memory/",
    "cache/",
    "hs/",
    "math/",
)


def load_kb_names():
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    name_by, decl_by, src_by, ported = {}, {}, {}, {}
    for o in kb.get("objects", []):
        src = o.get("source") or ""
        for fn in o.get("functions") or []:
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            ai = int(fn["addr"], 16)
            nm = func_name(fn) or f"FUN_{ai:08x}"
            name_by[ai] = nm
            decl_by[ai] = fn.get("decl") or ""
            src_by[ai] = src
            ported[ai] = fn.get("ported")
    return kb, name_by, decl_by, src_by, ported


def cdecl_sig(decl: str, name: str) -> str:
    d = re.sub(r"\s*@<\w+>", "", decl or "")
    d = re.sub(r"/\*\s*@<\w+>\s*\*/", "", d)
    d = re.sub(r"\s+", " ", d).strip()
    if not d.endswith(";"):
        d += ";"
    if name not in d:
        return f"void {name}(void)"
    return d[:-1]


def params(sig: str) -> list[str]:
    m = re.search(r"\(([^)]*)\)", sig)
    if not m:
        return []
    raw = m.group(1).strip()
    if not raw or raw == "void":
        return []
    return [p.strip().split()[-1].strip("*") for p in raw.split(",") if p.strip()]


def is_void(sig: str) -> bool:
    return "void" in sig.split("(")[0]


def parse_assert(ops: list[tuple[str, str]], i: int) -> dict | None:
    """Parse display_assert+system_exit; add esp may be delayed after other ops."""
    if i + 6 >= len(ops):
        return None
    if not (
        ops[i] == ("push", "1")
        and ops[i + 1][0] == "push"
        and ops[i + 2][0] == "push"
        and ops[i + 3][0] == "push"
        and ops[i + 4][0] == "call"
        and f"{DISPLAY_ASSERT:x}" in ops[i + 4][1]
        and ops[i + 5] == ("push", "-1")
        and ops[i + 6][0] == "call"
        and f"{SYSTEM_EXIT:x}" in ops[i + 6][1]
    ):
        return None
    j = i + 7
    if j < len(ops) and ops[j][0] == "add" and "esp" in ops[j][1]:
        j += 1
    return {
        "line": ops[i + 1][1],
        "file": ops[i + 2][1],
        "msg": ops[i + 3][1],
        "next": j,
    }


def assert_c(ab: dict, indent: str = "  ") -> str:
    return (
        f"{indent}display_assert((const char *){ab['msg']}, "
        f"(const char *){ab['file']}, {ab['line']}, 1);\n"
        f"{indent}system_exit(-1);\n"
    )


def callee(op: str, name_by: dict) -> str | None:
    m = re.search(r"0x([0-9a-fA-F]+)", op)
    if not m:
        return None
    return name_by.get(int(m.group(1), 16))


def ensure_params(sig: str, ps: list[str], n: int, kinds: list[str] | None = None) -> tuple[str, list[str]]:
    """Synthesize missing cdecl params when kb decl is `void foo(void)` but stack args exist."""
    if len(ps) >= n:
        return sig, ps
    kinds = kinds or ["void *"] * n
    names = [f"a{i}" for i in range(n)]
    # reuse existing names
    for i, p in enumerate(ps):
        names[i] = p
    plist = ", ".join(f"{kinds[i]} {names[i]}" for i in range(n))
    # rebuild sig
    ret_t = sig.split("(")[0].strip()
    if ret_t.endswith(sig.split("(")[0].split()[-1] if False else ""):
        pass
    # extract return type + name
    m = re.match(r"^(.*\b)(\w+)\s*$", ret_t)
    if not m:
        return sig, ps
    new_sig = f"{m.group(1)}{m.group(2)}({plist})"
    return new_sig, names


def try_emit(ops: list[tuple[str, str]], decl: str, name: str, name_by: dict) -> str | None:
    if not ops or ops[-1][0] not in ("ret", "retn"):
        return None
    body = ops[:-1]
    sig = cdecl_sig(decl, name)
    ps = params(sig)
    ret = "" if is_void(sig) else "return "

    # --- Pattern: null-check arg0 (esi), one assert, simple field load ---
    # push ebp; mov ebp,esp; push esi; mov esi,[ebp+8]; test esi,esi; jne L; ASSERT; TAIL; pop*; ret
    if (
        len(body) >= 12
        and body[0] == ("push", "ebp")
        and body[1] == ("mov", "ebp, esp")
        and body[2] == ("push", "esi")
        and body[3] == ("mov", "esi, dword ptr [ebp + 8]")
        and body[4] == ("test", "esi, esi")
        and body[5][0] == "jne"
    ):
        ab = parse_assert(body, 6)
        if ab:
            sig1, ps1 = ensure_params(sig, ps, 1, ["void *"])
            mid = body[ab["next"] :]
            while mid and mid[-1][0] == "pop" and mid[-1][1] in ("ebp", "esi", "ebx", "edi"):
                mid = mid[:-1]
            mid = [
                x
                for x in mid
                if not (x[0] == "pop" and x[1] == "esi")
                and not (x[0] == "add" and "esp" in x[1])
            ]

            # mov ax/eax/al, [esi(+off)]
            if len(mid) == 1 and mid[0][0] == "mov":
                m = re.match(
                    r"(al|ax|eax), (byte|word|dword) ptr \[esi(?: \+ (0x[0-9a-f]+|\d+))?\]$",
                    mid[0][1],
                )
                if m:
                    width, off = m.group(2), m.group(3)
                    o = int(off, 0) if off else 0
                    ctype = {"byte": "uint8_t", "word": "uint16_t", "dword": "uint32_t"}[
                        width
                    ]
                    # promote void return to integer
                    if is_void(sig1):
                        sig1 = sig1.replace("void ", f"{ctype} ", 1)
                    return (
                        f"{sig1}\n{{\n"
                        f"  if ({ps1[0]} == NULL) {{\n"
                        f"{assert_c(ab, '    ')}"
                        f"  }}\n"
                        f"  return *({ctype} *)((char *){ps1[0]} + 0x{o:x});\n"
                        f"}}\n"
                    )

            # movsx eax, byte/word ptr [esi+off]
            if len(mid) == 1 and mid[0][0] == "movsx":
                m = re.match(
                    r"eax, (byte|word) ptr \[esi(?: \+ (0x[0-9a-f]+|\d+))?\]$",
                    mid[0][1],
                )
                if m:
                    width, off = m.group(1), m.group(2)
                    o = int(off, 0) if off else 0
                    ctype = "int8_t" if width == "byte" else "int16_t"
                    if is_void(sig1):
                        sig1 = sig1.replace("void ", "int ", 1)
                    return (
                        f"{sig1}\n{{\n"
                        f"  if ({ps1[0]} == NULL) {{\n"
                        f"{assert_c(ab, '    ')}"
                        f"  }}\n"
                        f"  return ({ctype})*({ctype} *)((char *){ps1[0]} + 0x{o:x});\n"
                        f"}}\n"
                    )

            # bit extract
            if (
                len(mid) >= 2
                and mid[0] == ("xor", "eax, eax")
                and mid[1][0] == "mov"
                and mid[1][1].startswith("al, byte ptr [esi")
            ):
                m = re.match(
                    r"al, byte ptr \[esi(?: \+ (0x[0-9a-f]+|\d+))?\]$", mid[1][1]
                )
                if m:
                    o = int(m.group(1), 0) if m.group(1) else 0
                    rest = mid[2:]
                    expr = f"(uint32_t)*(uint8_t *)((char *){ps1[0]} + 0x{o:x})"
                    ok = True
                    for mnem, op in rest:
                        if mnem == "and" and op.startswith("eax,"):
                            expr = f"({expr} & {op.split(',', 1)[1].strip()})"
                        elif mnem == "shr" and op.startswith("eax,"):
                            expr = f"({expr} >> {op.split(',', 1)[1].strip()})"
                        elif mnem == "not" and op == "eax":
                            expr = f"(~{expr})"
                        else:
                            ok = False
                            break
                    if ok:
                        if is_void(sig1):
                            sig1 = sig1.replace("void ", "int ", 1)
                        return (
                            f"{sig1}\n{{\n"
                            f"  if ({ps1[0]} == NULL) {{\n"
                            f"{assert_c(ab, '    ')}"
                            f"  }}\n"
                            f"  return (int){expr};\n"
                            f"}}\n"
                        )

            # store word from arg1
            if (
                len(mid) == 2
                and mid[0] == ("mov", "ax, word ptr [ebp + 0xc]")
                and mid[1][0] == "mov"
            ):
                m = re.match(
                    r"word ptr \[esi(?: \+ (0x[0-9a-f]+|\d+))?\]"
                    r", ax$",
                    mid[1][1],
                )
                sig2, ps2 = ensure_params(sig, ps, 2, ["void *", "int16_t"])
                if m and len(ps2) >= 2:
                    o = int(m.group(1), 0) if m.group(1) else 0
                    return (
                        f"{sig2}\n{{\n"
                        f"  if ({ps2[0]} == NULL) {{\n"
                        f"{assert_c(ab, '    ')}"
                        f"  }}\n"
                        f"  *(uint16_t *)((char *){ps2[0]} + 0x{o:x}) = (uint16_t){ps2[1]};\n"
                        f"}}\n"
                    )

            # forward call: push esi; call F
            if len(mid) == 2 and mid[0] == ("push", "esi") and mid[1][0] == "call":
                fn = callee(mid[1][1], name_by)
                if fn:
                    if is_void(sig1):
                        r = ""
                    else:
                        r = "return "
                    return (
                        f"{sig1}\n{{\n"
                        f"  if ({ps1[0]} == NULL) {{\n"
                        f"{assert_c(ab, '    ')}"
                        f"  }}\n"
                        f"  {r}{fn}({ps1[0]});\n"
                        f"}}\n"
                    )

            # 2-arg forward after null-check on arg1 (esi from ebp+0xc)
            if (
                len(mid) == 3
                and mid[0] == ("mov", "eax, dword ptr [ebp + 8]")
                and mid[1] == ("push", "esi")
                and mid[2][0] == "call"
            ):
                fn = callee(mid[2][1], name_by)
                # esi was loaded from ebp+0xc
                sig2, ps2 = ensure_params(sig, ps, 2, ["int", "void *"])
                if fn:
                    r = "" if is_void(sig2) else "return "
                    return (
                        f"{sig2}\n{{\n"
                        f"  if ({ps2[1]} == NULL) {{\n"
                        f"{assert_c(ab, '    ')}"
                        f"  }}\n"
                        f"  {r}{fn}({ps2[0]}, {ps2[1]});\n"
                        f"}}\n"
                    )

            # dual assert path — restore mid before add-strip for second assert parse
            mid_raw = body[ab["next"] :]
            while mid_raw and mid_raw[-1][0] == "pop" and mid_raw[-1][1] in ("ebp", "esi"):
                mid_raw = mid_raw[:-1]
            if (
                len(mid_raw) >= 5
                and mid_raw[0][0] == "mov"
                and "al, byte ptr [0x" in mid_raw[0][1]
                and mid_raw[1] == ("test", "al, al")
                and mid_raw[2][0] == "jne"
            ):
                ab2 = parse_assert(mid_raw, 3)
                if ab2:
                    mid2 = mid_raw[ab2["next"] :]
                    mid2 = [
                        x
                        for x in mid2
                        if not (x[0] == "pop" and x[1] in ("esi", "ebp"))
                        and not (x[0] == "add" and "esp" in x[1])
                    ]
                    g = re.search(r"\[0x([0-9a-fA-F]+)\]", mid_raw[0][1])
                    if g and len(mid2) == 1 and mid2[0][0] == "movsx":
                        m = re.match(
                            r"eax, byte ptr \[esi(?: \+ (0x[0-9a-f]+|\d+))?\]$",
                            mid2[0][1],
                        )
                        if m:
                            o = int(m.group(1), 0) if m.group(1) else 0
                            if is_void(sig1):
                                sig1 = sig1.replace("void ", "int ", 1)
                            return (
                                f"{sig1}\n{{\n"
                                f"  if ({ps1[0]} == NULL) {{\n"
                                f"{assert_c(ab, '    ')}"
                                f"  }}\n"
                                f"  if (*(uint8_t *)0x{g.group(1)} == 0) {{\n"
                                f"{assert_c(ab2, '    ')}"
                                f"  }}\n"
                                f"  return (int8_t)*(int8_t *)((char *){ps1[0]} + 0x{o:x});\n"
                                f"}}\n"
                            )
                    if (
                        g
                        and len(mid2) == 2
                        and mid2[0][0] == "mov"
                        and mid2[1] == ("inc", "eax")
                    ):
                        m = re.match(
                            r"eax, dword ptr \[esi(?: \+ (0x[0-9a-f]+|\d+))?\]$",
                            mid2[0][1],
                        )
                        if m:
                            o = int(m.group(1), 0) if m.group(1) else 0
                            if is_void(sig1):
                                sig1 = sig1.replace("void ", "int ", 1)
                            return (
                                f"{sig1}\n{{\n"
                                f"  if ({ps1[0]} == NULL) {{\n"
                                f"{assert_c(ab, '    ')}"
                                f"  }}\n"
                                f"  if (*(uint8_t *)0x{g.group(1)} == 0) {{\n"
                                f"{assert_c(ab2, '    ')}"
                                f"  }}\n"
                                f"  return *(uint32_t *)((char *){ps1[0]} + 0x{o:x}) + 1;\n"
                                f"}}\n"
                            )

            # dual assert (null + global byte), then simple load
            # after first assert: mov al,[imm]; test al,al; jne; ASSERT2; load
            if (
                len(mid) >= 5
                and mid[0][0] == "mov"
                and "al, byte ptr [0x" in mid[0][1]
                and mid[1] == ("test", "al, al")
                and mid[2][0] == "jne"
            ):
                ab2 = parse_assert(mid, 3)
                if ab2:
                    mid2 = mid[ab2["next"] :]
                    while mid2 and mid2[-1][0] == "pop":
                        mid2 = mid2[:-1]
                    if len(mid2) == 1 and mid2[0][0] in ("mov", "movsx"):
                        m = re.match(
                            r"(?:eax|ax|al), (?:byte|word|dword) ptr \[esi(?: \+ (0x[0-9a-f]+|\d+))?\]$",
                            mid2[0][1],
                        )
                        m2 = re.match(
                            r"eax, (byte|word) ptr \[esi(?: \+ (0x[0-9a-f]+|\d+))?\]$",
                            mid2[0][1],
                        )
                        if mid2[0][0] == "movsx" and m2:
                            width, off = m2.group(1), m2.group(2)
                            o = int(off, 0) if off else 0
                            ctype = "int8_t" if width == "byte" else "int16_t"
                            g = re.search(r"\[0x([0-9a-fA-F]+)\]", mid[0][1])
                            if g:
                                return (
                                    f"{sig}\n{{\n"
                                    f"  if ({ps[0]} == NULL) {{\n"
                                    f"{assert_c(ab, '    ')}"
                                    f"  }}\n"
                                    f"  if (*(uint8_t *)0x{g.group(1)} == 0) {{\n"
                                    f"{assert_c(ab2, '    ')}"
                                    f"  }}\n"
                                    f"  {ret}({ctype})*({ctype} *)((char *){ps[0]} + 0x{o:x});\n"
                                    f"}}\n"
                                )
                        if mid2[0][0] == "mov" and m:
                            o = int(m.group(1), 0) if m.group(1) else 0
                            # infer width from opcode text
                            if "byte ptr" in mid2[0][1]:
                                ctype = "uint8_t"
                            elif "word ptr" in mid2[0][1]:
                                ctype = "uint16_t"
                            else:
                                ctype = "uint32_t"
                            g = re.search(r"\[0x([0-9a-fA-F]+)\]", mid[0][1])
                            if g:
                                # special: mov eax,[esi+off]; inc eax
                                pass
                    if (
                        len(mid2) == 2
                        and mid2[0][0] == "mov"
                        and "dword ptr [esi" in mid2[0][1]
                        and mid2[1] == ("inc", "eax")
                    ):
                        m = re.match(
                            r"eax, dword ptr \[esi(?: \+ (0x[0-9a-f]+|\d+))?\]$",
                            mid2[0][1],
                        )
                        g = re.search(r"\[0x([0-9a-fA-F]+)\]", mid[0][1])
                        if m and g:
                            o = int(m.group(1), 0) if m.group(1) else 0
                            return (
                                f"{sig}\n{{\n"
                                f"  if ({ps[0]} == NULL) {{\n"
                                f"{assert_c(ab, '    ')}"
                                f"  }}\n"
                                f"  if (*(uint8_t *)0x{g.group(1)} == 0) {{\n"
                                f"{assert_c(ab2, '    ')}"
                                f"  }}\n"
                                f"  {ret}*(uint32_t *)((char *){ps[0]} + 0x{o:x}) + 1;\n"
                                f"}}\n"
                            )
                    if len(mid2) == 1 and mid2[0][0] == "movsx":
                        m = re.match(
                            r"eax, byte ptr \[esi(?: \+ (0x[0-9a-f]+|\d+))?\]$",
                            mid2[0][1],
                        )
                        g = re.search(r"\[0x([0-9a-fA-F]+)\]", mid[0][1])
                        if m and g:
                            o = int(m.group(1), 0) if m.group(1) else 0
                            return (
                                f"{sig}\n{{\n"
                                f"  if ({ps[0]} == NULL) {{\n"
                                f"{assert_c(ab, '    ')}"
                                f"  }}\n"
                                f"  if (*(uint8_t *)0x{g.group(1)} == 0) {{\n"
                                f"{assert_c(ab2, '    ')}"
                                f"  }}\n"
                                f"  {ret}(int8_t)*(int8_t *)((char *){ps[0]} + 0x{o:x});\n"
                                f"}}\n"
                            )

    # --- Pattern: index bounds 0..4, assert, table byte load/store ---
    if (
        len(body) >= 14
        and body[0] == ("push", "ebp")
        and body[1] == ("mov", "ebp, esp")
        and body[2] == ("push", "esi")
        and body[3] == ("mov", "si, word ptr [ebp + 8]")
        and body[4] == ("test", "si, si")
        and body[5][0] == "jl"
        and body[6] == ("cmp", "si, 4")
        and body[7][0] == "jl"
    ):
        ab = parse_assert(body, 8)
        if ab:
            sigi, psi = ensure_params(sig, ps, 1, ["int16_t"])
            mid = body[ab["next"] :]
            while mid and mid[-1][0] == "pop" and mid[-1][1] in ("ebp", "esi"):
                mid = mid[:-1]
            if (
                len(mid) == 3
                and mid[0] == ("movsx", "eax, si")
                and mid[1][0] == "imul"
                and mid[2][0] == "mov"
            ):
                im = re.match(r"eax, eax, (0x[0-9a-f]+|\d+)$", mid[1][1])
                ms = re.match(
                    r"byte ptr \[eax \+ (0x[0-9a-f]+)\]"
                    r", (0x[0-9a-f]+|\d+)$",
                    mid[2][1],
                )
                ml = re.match(
                    r"al, byte ptr \[eax \+ (0x[0-9a-f]+)\]$",
                    mid[2][1],
                )
                if im and ms:
                    stride, base, val = im.group(1), ms.group(1), ms.group(2)
                    return (
                        f"{sigi}\n{{\n"
                        f"  if ((int16_t){psi[0]} < 0 || (int16_t){psi[0]} >= 4) {{\n"
                        f"{assert_c(ab, '    ')}"
                        f"  }}\n"
                        f"  *(uint8_t *)(0x{int(base, 16):x} + (int)(int16_t){psi[0]} * {stride}) = "
                        f"(uint8_t){val};\n"
                        f"}}\n"
                    )
                if im and ml:
                    stride, base = im.group(1), ml.group(1)
                    if is_void(sigi):
                        sigi = sigi.replace("void ", "uint8_t ", 1)
                    return (
                        f"{sigi}\n{{\n"
                        f"  if ((int16_t){psi[0]} < 0 || (int16_t){psi[0]} >= 4) {{\n"
                        f"{assert_c(ab, '    ')}"
                        f"  }}\n"
                        f"  return *(uint8_t *)(0x{int(base, 16):x} + (int)(int16_t){psi[0]} * {stride});\n"
                        f"}}\n"
                    )

    # --- Pattern: global counter > 0 assert, return two dwords as int64-ish ---
    if (
        len(body) >= 10
        and body[0][0] == "mov"
        and body[0][1].startswith("eax, dword ptr [0x")
        and body[1] == ("test", "eax, eax")
        and body[2][0] == "jg"
    ):
        ab = parse_assert(body, 3)
        if ab:
            mid = body[ab["next"] :]
            if (
                len(mid) == 2
                and mid[0][0] == "mov"
                and mid[0][1].startswith("eax, dword ptr [0x")
                and mid[1][0] == "mov"
                and mid[1][1].startswith("edx, dword ptr [0x")
            ):
                g0 = re.search(r"\[0x([0-9a-fA-F]+)\]", body[0][1])
                a0 = re.search(r"\[0x([0-9a-fA-F]+)\]", mid[0][1])
                a1 = re.search(r"\[0x([0-9a-fA-F]+)\]", mid[1][1])
                if g0 and a0 and a1:
                    return (
                        f"{sig}\n{{\n"
                        f"  if (*(int *)0x{g0.group(1)} <= 0) {{\n"
                        f"{assert_c(ab, '    ')}"
                        f"  }}\n"
                        f"  /* edx:eax */\n"
                        f"  (void)*(uint32_t *)0x{a1.group(1)};\n"
                        f"  {ret}*(uint32_t *)0x{a0.group(1)};\n"
                        f"}}\n"
                    )

    # --- Pattern: device_get_position style ---
    # push ebp; mov ebp,esp; mov eax,[ebp+8]; cmp eax,-1; je; push TYPE; push eax; call object_get;
    # fld [eax+off]; add esp,8; pop ebp
    if (
        len(body) >= 9
        and body[0] == ("push", "ebp")
        and body[1] == ("mov", "ebp, esp")
        and body[2] == ("mov", "eax, dword ptr [ebp + 8]")
        and body[3] == ("cmp", "eax, -1")
        and body[4][0] == "je"
        and body[5][0] == "push"
        and body[6] == ("push", "eax")
        and body[7][0] == "call"
        and f"{OBJECT_GET:x}" in body[7][1]
    ):
        mid = body[8:]
        # optional add esp before fld or after
        if mid and mid[0][0] == "fld":
            fld, rest = mid[0], mid[1:]
        elif len(mid) >= 2 and mid[0][0] == "add" and mid[1][0] == "fld":
            fld, rest = mid[1], mid[2:]
        else:
            fld = None
            rest = mid
        if fld:
            m = re.match(
                r"dword ptr \[eax(?: \+ (0x[0-9a-f]+|\d+))?\]$", fld[1]
            )
            fn = callee(body[7][1], name_by) or "object_get_and_verify_type"
            if m and ps:
                o = int(m.group(1), 0) if m.group(1) else 0
                # cdecl: last push is first arg → object_get(handle, type)
                # Skip -1 early-return modeling (XBE leaves ST0 untouched).
                return (
                    f"{sig}\n{{\n"
                    f"  if ({ps[0]} != -1) {{\n"
                    f"    void *obj = {fn}({ps[0]}, {body[5][1]});\n"
                    f"    {ret}*(float *)((char *)obj + 0x{o:x});\n"
                    f"  }}\n"
                    f"  {ret}0.0f;\n"
                    f"}}\n"
                )

    # --- Pattern: object_try + flag bit set/clear ---
    # push ebp; mov ebp,esp; mov eax,[ebp+8]; [cmp -1 je]; push MASK; push eax; call object_try;
    # add; test eax,eax; je; mov cl,[ebp+0xc]; test cl,cl; mov ecx,[eax+off]; je/jne; or/and; mov
    if (
        len(body) >= 14
        and body[0] == ("push", "ebp")
        and body[1] == ("mov", "ebp, esp")
        and body[2] == ("mov", "eax, dword ptr [ebp + 8]")
    ):
        i = 3
        has_cmp = False
        if body[i] == ("cmp", "eax, -1") and body[i + 1][0] == "je":
            has_cmp = True
            i += 2
        if (
            i + 8 < len(body)
            and body[i][0] == "push"
            and body[i + 1] == ("push", "eax")
            and body[i + 2][0] == "call"
            and f"{OBJECT_TRY:x}" in body[i + 2][1]
            and body[i + 3][0] == "add"
            and body[i + 4] == ("test", "eax, eax")
            and body[i + 5][0] == "je"
            and body[i + 6] == ("mov", "cl, byte ptr [ebp + 0xc]")
            and body[i + 7] == ("test", "cl, cl")
        ):
            # mov ecx, [eax+off]; je/jne L; or/and ecx, IMM; mov [eax+off], ecx  OR similar
            rest = body[i + 8 :]
            while rest and rest[-1][0] == "pop":
                rest = rest[:-1]
            fn = callee(body[i + 2][1], name_by) or "object_try_and_get_and_verify_type"
            # Common: mov ecx, dword ptr [eax + OFF]; je X; or ecx, MASK / and ecx, ~MASK; mov [eax+OFF], ecx
            if (
                len(rest) >= 3
                and rest[0][0] == "mov"
                and "ecx, dword ptr [eax" in rest[0][1]
                and rest[1][0] in ("je", "jne")
                and rest[2][0] in ("or", "and")
                and rest[2][1].startswith("ecx,")
            ):
                off_m = re.search(r"\[eax \+ (0x[0-9a-f]+)\]", rest[0][1])
                # find final store
                store = None
                for r in rest:
                    if r[0] == "mov" and "dword ptr [eax" in r[1] and r[1].endswith(", ecx"):
                        store = r
                if off_m and store and len(ps) >= 2:
                    o = int(off_m.group(1), 16)
                    mask = rest[2][1].split(",", 1)[1].strip()
                    op = rest[2][0]
                    # je after test cl → skip when cl==0 → apply when true
                    # jne after test cl → skip when cl!=0 → apply when false
                    cond = f"if ({ps[1]})" if rest[1][0] == "je" else f"if (!{ps[1]})"
                    early = ""
                    if has_cmp:
                        early = f"  if ({ps[0]} == -1) {{\n    return;\n  }}\n"
                    assign = f"flags |= {mask}" if op == "or" else f"flags &= {mask}"
                    return (
                        f"{sig}\n{{\n"
                        f"{early}"
                        f"  {{\n"
                        f"    void *obj = {fn}({ps[0]}, {body[i][1]});\n"
                        f"    if (!obj) {{\n"
                        f"      return;\n"
                        f"    }}\n"
                        f"    uint32_t flags = *(uint32_t *)((char *)obj + 0x{o:x});\n"
                        f"    {cond} {{\n"
                        f"      {assign};\n"
                        f"    }}\n"
                        f"    *(uint32_t *)((char *)obj + 0x{o:x}) = flags;\n"
                        f"  }}\n"
                        f"}}\n"
                    )

    # --- Pattern: null-check + memset init (csmemset) ---
    if (
        len(body) >= 14
        and body[0] == ("push", "ebp")
        and body[1] == ("mov", "ebp, esp")
        and body[2] == ("push", "esi")
        and body[3] == ("mov", "esi, dword ptr [ebp + 8]")
        and body[4] == ("test", "esi, esi")
        and body[5][0] == "jne"
    ):
        ab = parse_assert(body, 6)
        if ab and ps:
            mid = body[ab["next"] :]
            while mid and mid[-1][0] == "pop":
                mid = mid[:-1]
            # push SIZE; push 0; push esi; call csmemset; add; then stores
            if (
                len(mid) >= 5
                and mid[0][0] == "push"
                and mid[1] == ("push", "0")
                and mid[2] == ("push", "esi")
                and mid[3][0] == "call"
            ):
                fn = callee(mid[3][1], name_by)
                if fn in ("csmemset", "memset") or (
                    fn and "memset" in fn
                ):
                    # only handle pure memset + return 1 / void with no extra stores
                    rest = mid[4:]
                    if rest and rest[0][0] == "add":
                        rest = rest[1:]
                    if not rest:
                        return (
                            f"{sig}\n{{\n"
                            f"  if ({ps[0]} == NULL) {{\n"
                            f"{assert_c(ab, '    ')}"
                            f"  }}\n"
                            f"  {fn}({ps[0]}, 0, {mid[0][1]});\n"
                            f"}}\n"
                        )
                    if rest == [("mov", "al, 1")]:
                        return (
                            f"{sig}\n{{\n"
                            f"  if ({ps[0]} == NULL) {{\n"
                            f"{assert_c(ab, '    ')}"
                            f"  }}\n"
                            f"  {fn}({ps[0]}, 0, {mid[0][1]});\n"
                            f"  {ret}1;\n"
                            f"}}\n"
                        )


    # --- Pattern: index 0..4 → return table pointer (movsx/imul/add) ---
    if (
        len(body) >= 14
        and body[0] == ("push", "ebp")
        and body[1] == ("mov", "ebp, esp")
        and body[2] == ("push", "esi")
        and body[3] == ("mov", "si, word ptr [ebp + 8]")
        and body[4] == ("test", "si, si")
        and body[5][0] == "jl"
        and body[6] == ("cmp", "si, 4")
        and body[7][0] == "jl"
    ):
        ab = parse_assert(body, 8)
        if ab:
            sigi, psi = ensure_params(sig, ps, 1, ["int16_t"])
            mid = body[ab["next"] :]
            while mid and mid[-1][0] == "pop" and mid[-1][1] in ("ebp", "esi"):
                mid = mid[:-1]
            if (
                len(mid) == 3
                and mid[0] == ("movsx", "eax, si")
                and mid[1][0] == "imul"
                and mid[2][0] == "add"
                and mid[2][1].startswith("eax,")
            ):
                im = re.match(r"eax, eax, (0x[0-9a-f]+|\d+)$", mid[1][1])
                am = re.match(r"eax, (0x[0-9a-f]+)$", mid[2][1])
                if im and am:
                    if is_void(sigi):
                        sigi = sigi.replace("void ", "void *", 1)
                    return (
                        f"{sigi}\n{{\n"
                        f"  if ((int16_t){psi[0]} < 0 || (int16_t){psi[0]} >= 4) {{\n"
                        f"{assert_c(ab, '    ')}"
                        f"  }}\n"
                        f"  return (void *)(0x{int(am.group(1), 16):x} + (int)(int16_t){psi[0]} * {im.group(1)});\n"
                        f"}}\n"
                    )
            if (
                len(mid) == 4
                and mid[0][0] == "mov"
                and "dword ptr [0x" in mid[0][1]
                and mid[1] == ("movsx", "eax, si")
                and mid[2][0] == "imul"
                and mid[3] == ("add", "eax, ecx")
            ):
                g = re.search(r"\[0x([0-9a-fA-F]+)\]", mid[0][1])
                im = re.match(r"eax, eax, (0x[0-9a-f]+|\d+)$", mid[2][1])
                if g and im:
                    if is_void(sigi):
                        sigi = sigi.replace("void ", "void *", 1)
                    return (
                        f"{sigi}\n{{\n"
                        f"  if ((int16_t){psi[0]} < 0 || (int16_t){psi[0]} >= 4) {{\n"
                        f"{assert_c(ab, '    ')}"
                        f"  }}\n"
                        f"  return (void *)((char *)*(void **)0x{g.group(1)} + "
                        f"(int)(int16_t){psi[0]} * {im.group(1)});\n"
                        f"}}\n"
                    )

    # --- Pattern: null-check any ebp arg + memset + optional imm stores / return 1 ---
    if (
        len(body) >= 14
        and body[0] == ("push", "ebp")
        and body[1] == ("mov", "ebp, esp")
        and body[2] == ("push", "esi")
        and body[3][0] == "mov"
        and body[4] == ("test", "esi, esi")
        and body[5][0] == "jne"
    ):
        em = re.match(r"esi, dword ptr \[ebp \+ (0x[0-9a-f]+|8)\]$", body[3][1])
        ab = parse_assert(body, 6)
        if em and ab:
            eoff = int(em.group(1), 0)
            ai = (eoff - 8) // 4
            sigm, psm = ensure_params(sig, ps, ai + 1, ["void *"] * (ai + 1))
            mid = body[ab["next"] :]
            while mid and mid[-1][0] == "pop":
                mid = mid[:-1]
            if (
                len(mid) >= 5
                and mid[0][0] == "push"
                and mid[1] == ("push", "0")
                and mid[2] == ("push", "esi")
                and mid[3][0] == "call"
            ):
                fn = callee(mid[3][1], name_by)
                if fn in ("csmemset", "memset") or (fn and "memset" in (fn or "")):
                    rest = mid[4:]
                    if rest and rest[0][0] == "add":
                        rest = rest[1:]
                    stores = []
                    ok = True
                    ret1 = False
                    for mnem, op in rest:
                        if mnem == "mov" and op == "al, 1":
                            ret1 = True
                            continue
                        sm = re.match(
                            r"(byte|word|dword) ptr \[esi(?: \+ (0x[0-9a-f]+|\d+))?\], "
                            r"(0x[0-9a-f]+|-?\d+)$",
                            op,
                        )
                        if mnem == "mov" and sm:
                            width, off, val = sm.group(1), sm.group(2), sm.group(3)
                            o = int(off, 0) if off else 0
                            ctype = {"byte": "uint8_t", "word": "uint16_t", "dword": "uint32_t"}[width]
                            stores.append(
                                f"  *({ctype} *)((char *){psm[ai]} + 0x{o:x}) = ({ctype}){val};"
                            )
                        else:
                            ok = False
                            break
                    if ok:
                        if ret1 and is_void(sigm):
                            sigm = sigm.replace("void ", "int ", 1)
                        out = (
                            f"{sigm}\n{{\n"
                            f"  if ({psm[ai]} == NULL) {{\n"
                            f"{assert_c(ab, '    ')}"
                            f"  }}\n"
                            f"  {fn}({psm[ai]}, 0, {mid[0][1]});\n"
                        )
                        if stores:
                            out += "\n".join(stores) + "\n"
                        if ret1:
                            out += "  return 1;\n"
                        out += "}\n"
                        return out

    # --- Pattern: global nonzero assert + memset ---
    if (
        len(body) >= 10
        and body[0][0] == "mov"
        and body[0][1].startswith("eax, dword ptr [0x")
        and body[1] == ("test", "eax, eax")
        and body[2][0] == "jne"
    ):
        ab = parse_assert(body, 3)
        if ab:
            g = re.search(r"\[0x([0-9a-fA-F]+)\]", body[0][1])
            mid = body[ab["next"] :]
            if (
                g
                and len(mid) >= 5
                and mid[0][0] == "mov"
                and "dword ptr [0x" in mid[0][1]
                and mid[1][0] == "push"
                and mid[2] == ("push", "0")
                and mid[3] == ("push", "eax")
                and mid[4][0] == "call"
            ):
                fn = callee(mid[4][1], name_by)
                g2 = re.search(r"\[0x([0-9a-fA-F]+)\]", mid[0][1])
                if g2 and fn and (fn in ("csmemset", "memset") or "memset" in fn):
                    return (
                        f"{sig}\n{{\n"
                        f"  if (!*(void **)0x{g.group(1)}) {{\n"
                        f"{assert_c(ab, '    ')}"
                        f"  }}\n"
                        f"  {fn}(*(void **)0x{g2.group(1)}, 0, {mid[1][1]});\n"
                        f"}}\n"
                    )

    # --- Pattern: global ptr/byte assert then return (void) ---
    if (
        len(body) >= 8
        and body[0][0] == "mov"
        and ("dword ptr [0x" in body[0][1] or "byte ptr [0x" in body[0][1])
        and body[1][0] == "test"
        and body[2][0] in ("jne", "je")
    ):
        ab = parse_assert(body, 3)
        if ab:
            mid = body[ab["next"] :]
            while mid and mid[-1][0] == "pop":
                mid = mid[:-1]
            g = re.search(r"\[0x([0-9a-fA-F]+)\]", body[0][1])
            if g and not mid:
                ctype = "uint8_t" if "byte" in body[0][1] else "uint32_t"
                # jne L_ok → assert when zero; je L_ok → assert when nonzero
                if body[2][0] == "jne":
                    cond = "!*(%s *)0x%s" % (ctype, g.group(1))
                else:
                    cond = "*(%s *)0x%s" % (ctype, g.group(1))
                return (
                    f"{sig}\n{{\n"
                    f"  if ({cond}) {{\n"
                    f"{assert_c(ab, '    ')}"
                    f"  }}\n"
                    f"}}\n"
                )

    # --- Pattern: null-check arg + memset(+stores) + optional return 1 ---
    if (
        len(body) >= 12
        and body[0] == ("push", "ebp")
        and body[1] == ("mov", "ebp, esp")
        and body[2] == ("push", "esi")
        and body[3][0] == "mov"
        and "esi, dword ptr [ebp" in body[3][1]
        and body[4] == ("test", "esi, esi")
        and body[5][0] == "jne"
    ):
        ab = parse_assert(body, 6)
        if ab:
            mid = body[ab["next"] :]
            while mid and mid[-1][0] == "pop":
                mid = mid[:-1]
            if (
                len(mid) >= 4
                and mid[0][0] == "push"
                and mid[1] == ("push", "0")
                and mid[2] == ("push", "esi")
                and mid[3][0] == "call"
                and f"{0x8DB80:x}" in mid[3][1]
            ):
                em = re.search(r"\[ebp \+ (0x[0-9a-f]+|8)\]", body[3][1])
                argi = (int(em.group(1), 0) - 8) // 4 if em else 0
                sig1, ps1 = ensure_params(sig, ps, argi + 1, ["void *"] * (argi + 1))
                p = ps1[argi]
                rest = mid[4:]
                if rest and rest[0][0] == "add":
                    rest = rest[1:]
                stores = []
                ret1 = False
                ok = True
                for mnem, op in rest:
                    if mnem == "mov" and op.strip() in ("al, 1", "eax, 1"):
                        ret1 = True
                        continue
                    mm = re.match(
                        r"(byte|word|dword) ptr \[esi(?: \+ (0x[0-9a-f]+|\d+))?\]"
                        r", (.+)$",
                        op,
                    )
                    if mnem == "mov" and mm:
                        stores.append(
                            (
                                mm.group(1),
                                int(mm.group(2), 0) if mm.group(2) else 0,
                                mm.group(3),
                            )
                        )
                        continue
                    ok = False
                    break
                if ok:
                    fn = callee(mid[3][1], name_by) or "csmemset"
                    lines = [
                        f"  if ({p} == NULL) {{\n{assert_c(ab, '    ')}  }}",
                        f"  {fn}({p}, 0, {mid[0][1]});",
                    ]
                    for w, off, val in stores:
                        ctype = {"byte": "uint8_t", "word": "uint16_t", "dword": "uint32_t"}[
                            w
                        ]
                        lines.append(
                            f"  *({ctype} *)((char *){p} + 0x{off:x}) = ({ctype}){val};"
                        )
                    if ret1:
                        if is_void(sig1):
                            sig1 = sig1.replace("void ", "int ", 1)
                        lines.append("  return 1;")
                    return sig1 + "\n{\n" + "\n".join(lines) + "\n}\n"

            # ufputc-style: mov eax,[ebp+8]; push esi; push eax; call; [add]
            if (
                len(mid) in (4, 5)
                and mid[0][0] == "mov"
                and "ebp + 8" in mid[0][1]
                and mid[1] == ("push", "esi")
                and mid[2] == ("push", "eax")
                and mid[3][0] == "call"
            ):
                if len(mid) == 5 and mid[4][0] != "add":
                    pass
                else:
                    fn = callee(mid[3][1], name_by)
                    if fn:
                        sig2, ps2 = ensure_params(sig, ps, 2, ["int", "void *"])
                        r = "" if is_void(sig2) else "return "
                        return (
                            f"{sig2}\n{{\n"
                            f"  if ({ps2[1]} == NULL) {{\n"
                            f"{assert_c(ab, '    ')}"
                            f"  }}\n"
                            f"  {r}{fn}({ps2[0]}, {ps2[1]});\n"
                            f"}}\n"
                        )

    # --- Pattern: 0..4 index + (base[global] + (i<<6) + off) dword load ---
    if (
        len(body) >= 14
        and body[0] == ("push", "ebp")
        and body[1] == ("mov", "ebp, esp")
        and body[2] == ("push", "esi")
        and body[3] == ("mov", "si, word ptr [ebp + 8]")
        and body[4] == ("test", "si, si")
        and body[5][0] == "jl"
        and body[6] == ("cmp", "si, 4")
        and body[7][0] == "jl"
    ):
        ab = parse_assert(body, 8)
        if ab:
            mid = body[ab["next"] :]
            while mid and mid[-1][0] == "pop":
                mid = mid[:-1]
            if (
                len(mid) == 4
                and mid[0][0] == "mov"
                and "dword ptr [0x" in mid[0][1]
                and mid[1] == ("movsx", "eax, si")
                and mid[2] == ("shl", "eax, 6")
                and mid[3][0] == "mov"
                and "eax, dword ptr [eax + ecx +" in mid[3][1]
            ):
                g = re.search(r"\[0x([0-9a-fA-F]+)\]", mid[0][1])
                off = re.search(r"\[eax \+ ecx \+ (0x[0-9a-f]+|\d+)\]", mid[3][1])
                if g and off:
                    sig1, ps1 = ensure_params(sig, ps, 1, ["int16_t"])
                    if is_void(sig1):
                        sig1 = sig1.replace("void ", "int ", 1)
                    return (
                        f"{sig1}\n{{\n"
                        f"  if ((int16_t){ps1[0]} < 0 || (int16_t){ps1[0]} >= 4) {{\n"
                        f"{assert_c(ab, '    ')}"
                        f"  }}\n"
                        f"  void *base = *(void **)0x{g.group(1)};\n"
                        f"  return *(int *)((char *)base + ((int)(int16_t){ps1[0]} << 6)"
                        f" + {off.group(1)});\n"
                        f"}}\n"
                    )

    return None


def merge_kb_ported(ours_path: Path, theirs_text: str) -> str:
    """Union ported:true from ours into theirs (remote wins structure)."""
    ours = json.loads(ours_path.read_text(encoding="utf-8"))
    theirs = json.loads(theirs_text)
    true_addrs = set()
    for o in ours.get("objects", []):
        for fn in o.get("functions") or []:
            if isinstance(fn, dict) and fn.get("ported") is True and fn.get("addr"):
                true_addrs.add(int(fn["addr"], 16))
    for o in theirs.get("objects", []):
        for fn in o.get("functions") or []:
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            if int(fn["addr"], 16) in true_addrs:
                fn["ported"] = True
    return json.dumps(theirs, indent=2) + "\n"


def git_pull_rebase() -> None:
    r = subprocess.run(
        ["git", "pull", "--rebase", "pastudan", "track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    sys.stdout.write(r.stdout or "")
    sys.stderr.write(r.stderr or "")
    if r.returncode == 0:
        return
    # try kb union merge
    conflict = subprocess.run(
        ["git", "diff", "--name-only", "--diff-filter=U"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    ).stdout
    if "kb.json" in conflict:
        # during rebase conflict, ours=HEAD (remote), theirs=our commit — actually
        # rebase: HEAD is upstream, WORKING TREE has our changes.
        # stages: :2 = upstream (onto), :3 = ours (commit being replayed)
        up = subprocess.run(
            ["git", "show", ":2:kb.json"], cwd=ROOT, capture_output=True, text=True
        )
        our = subprocess.run(
            ["git", "show", ":3:kb.json"], cwd=ROOT, capture_output=True, text=True
        )
        if up.returncode == 0 and our.returncode == 0:
            # union: start from upstream, apply our ported:true
            tmp = ROOT / "kb.json"
            tmp.write_text(our.stdout, encoding="utf-8")
            merged = merge_kb_ported(tmp, up.stdout)
            tmp.write_text(merged, encoding="utf-8")
            subprocess.run(["git", "add", "kb.json"], cwd=ROOT, check=False)
            # for other conflicts, prefer ours for src we touched
            for f in conflict.splitlines():
                if f and f != "kb.json":
                    subprocess.run(
                        ["git", "checkout", "--ours", f], cwd=ROOT, check=False
                    )
                    subprocess.run(["git", "add", f], cwd=ROOT, check=False)
            rr = subprocess.run(
                ["git", "rebase", "--continue"],
                cwd=ROOT,
                capture_output=True,
                text=True,
                env={**dict(**{k: v for k, v in __import__("os").environ.items()}), "GIT_EDITOR": "true"},
            )
            sys.stdout.write(rr.stdout or "")
            sys.stderr.write(rr.stderr or "")
            if rr.returncode == 0:
                return
    raise SystemExit(f"pull --rebase failed: {r.returncode}")


def git_push() -> None:
    git_pull_rebase()
    r = subprocess.run(
        ["git", "push", "pastudan", "HEAD"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    sys.stdout.write(r.stdout or "")
    sys.stderr.write(r.stderr or "")
    if r.returncode != 0:
        raise SystemExit(f"push failed: {r.returncode}")


def commit_chunk(n: int, label: str = "assert wrappers") -> str | None:
    subprocess.run(["git", "add", "-u", "src/halo", "kb.json"], cwd=ROOT, check=False)
    subprocess.run(
        [
            "git",
            "add",
            "kb.json",
            "tools/equivalence/leaf_cache.json",
            "scripts/lift_assert_wrappers.py",
            "scripts/auto_lift_trivial.py",
            "scripts/lift_thin_wrappers.py",
        ],
        cwd=ROOT,
        check=False,
    )
    msg = f"lift(track-a): {label} + Unicorn-prove {n} (ported:true)."
    r = subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print("commit failed:", r.stdout, r.stderr, file=sys.stderr)
        return None
    sha = subprocess.run(
        ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
    ).stdout.strip()
    git_push()
    print(f"COMMIT+PUSH {sha}", flush=True)
    return sha


def prefer_key(src: str) -> int:
    return 0 if any(p in src for p in PREF) else 1


def main() -> int:
    kb, name_by, decl_by, src_by, ported = load_kb_names()
    by_addr, starts = load_kb(KB_PATH)
    xbe = Xbe((ROOT / "halo-patched" / "cachebeta.xbe").read_bytes())
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    true0, _ = count_ported(kb)
    flips: list[str] = []
    shas: list[str] = []
    since = 0

    addrs = []
    for i, ai in enumerate(starts):
        if ported.get(ai) is not False:
            continue
        src = src_by.get(ai) or ""
        if any(s in src.lower() for s in SKIP_SRC):
            continue
        end = starts[i + 1] if i + 1 < len(starts) else ai + 128
        if end - ai > 128:
            continue
        addrs.append((prefer_key(src), ai, end, src))
    addrs.sort()

    for _, ai, end, src in addrs:
        sp = resolve_src(src)
        if not sp:
            continue
        name = name_by[ai]
        text0 = sp.read_text(encoding="utf-8", errors="replace")
        if not is_naked_near_def(text0.splitlines(), name, hex(ai)):
            continue
        try:
            raw = xbe_bytes(xbe, ai, min(end, ai + 128))
        except Exception:
            continue
        ops: list[tuple[str, str]] = []
        for insn in md.disasm(raw, ai):
            ops.append((insn.mnemonic, insn.op_str))
            if insn.mnemonic in ("ret", "retn"):
                break
        else:
            continue
        decl = decl_by.get(ai) or f"void {name}(void);"
        body = try_emit(ops, decl, name, name_by)
        if not body:
            continue
        if re.search(r"\(\s*(void|int|char|[^*)]+)\s*\(\s*\*", body):
            continue
        needs_stdint = any(t in body for t in ("uint8_t", "uint16_t", "uint32_t", "int8_t", "int16_t"))
        c_src = f"/* {name} (0x{ai:x}) — readable C lift (assert wrapper). */\n{body}"
        text = sp.read_text(encoding="utf-8", errors="replace")
        span = find_naked_block(text, name, ai)
        if span is None:
            span = find_naked_block(text, f"FUN_{ai:08x}", ai)
        if span is None:
            print(f"skip locate {hex(ai)} {name}", flush=True)
            continue
        new_text = text[: span[0]] + c_src + "\n" + text[span[1] :]
        if needs_stdint and "#include <stdint.h>" not in new_text and '#include "stdint.h"' not in new_text:
            new_text = '#include <stdint.h>\n' + new_text
        sp.write_text(new_text, encoding="utf-8")
        print(f"LIFTED {hex(ai)} {name} ({src})", flush=True)
        for stale in (ROOT / "build").rglob(sp.name + ".obj"):
            try:
                stale.unlink()
            except OSError:
                pass
        if not ensure_oracle(ai):
            sp.write_text(text, encoding="utf-8")
            print("  oracle FAIL", flush=True)
            continue
        res = run_unicorn(hex(ai), ai, 100, timeout=45.0)
        ok = clear_pass(res, 100)
        if not ok:
            res2 = run_unicorn(name, ai, 100, timeout=45.0)
            if clear_pass(res2, 100):
                res, ok = res2, True
        print(f"  ok={ok} {res.get('passed')}/{res.get('failed')}/{res.get('errors')}", flush=True)
        append_ledger(
            {
                "addr": hex(ai),
                "name": name,
                "ok": ok,
                "phase": "assert_wrap",
                "passed": res.get("passed"),
                "failed": res.get("failed"),
                "errors": res.get("errors"),
            }
        )
        if not ok:
            sp.write_text(text, encoding="utf-8")
            print("  REVERT", flush=True)
            continue
        rc = subprocess.run(
            [sys.executable, str(ROOT / "tools/audit/check_raw_casts.py")],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
        if rc.returncode != 0:
            sp.write_text(text, encoding="utf-8")
            print("  REVERT raw-cast", flush=True)
            continue
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if flip_kb(kb, ai):
            flips.append(hex(ai))
            since += 1
            ported[ai] = True
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        if since >= COMMIT_EVERY:
            sha = commit_chunk(since)
            if sha:
                shas.append(sha)
            since = 0

    if since:
        sha = commit_chunk(since)
        if sha:
            shas.append(sha)

    true1, false1 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    summary = {
        "proven": len(flips),
        "flips": flips,
        "shas": shas,
        "true0": true0,
        "true1": true1,
        "false1": false1,
    }
    Path("/tmp/assert_lift_summary.json").write_text(json.dumps(summary, indent=2))
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
