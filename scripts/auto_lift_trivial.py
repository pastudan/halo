#!/usr/bin/env python3
"""Auto-lift tiny naked Capstone bodies (getters/setters) to C and Unicorn-prove."""
from __future__ import annotations

import json
import re
import subprocess
import sys
import time
from pathlib import Path

from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools" / "equivalence"))
from xbe_to_coff import load_kb, xbe_bytes  # noqa: E402

KB_PATH = ROOT / "kb.json"
LEDGER = ROOT / "artifacts" / "equivalence" / "trivial_auto_lift.jsonl"


def resolve_src(src: str) -> Path | None:
    for base in (ROOT / "src" / "halo", ROOT / "src", ROOT):
        p = base / src
        if p.exists():
            return p
    return None


def find_naked_def(text: str, name: str, addr: int) -> tuple[int, int] | None:
    """Return (start, end) of naked function definition (incl. #if wrapper)."""
    fun = f"FUN_{addr:08x}"
    for nm in (name, fun):
        # Prefer replacing the whole clang/#else/#endif block when present.
        block = re.compile(
            rf"/\*[^*]*\b{re.escape(nm)}\b[\s\S]*?"
            rf"#if\s+defined\s*\(\s*__clang__\s*\)\s*"
            rf"[\s\S]*?#else\s*[\s\S]*?#endif",
            re.M,
        )
        m = block.search(text)
        if m:
            return m.start(), m.end()

        pat = re.compile(
            rf"__attribute__\s*\(\s*\(\s*naked(?:\s*,\s*noinline)?\s*\)\s*\)\s*"
            rf"([\w\s\*]+?\b{re.escape(nm)}\s*\([^;]*\))\s*\{{",
            re.M,
        )
        m = pat.search(text)
        if not m:
            continue
        brace = text.find("{", m.end() - 1)
        depth = 0
        for i in range(brace, len(text)):
            if text[i] == "{":
                depth += 1
            elif text[i] == "}":
                depth -= 1
                if depth == 0:
                    return m.start(), i + 1
    return None


def cdecl_sig(decl: str, name: str) -> str:
    """Build a cdecl C signature from kb decl (strip @reg)."""
    d = re.sub(r"\s*@<\w+>", "", decl)
    d = re.sub(r"/\*\s*@<\w+>\s*\*/", "", d)
    d = re.sub(r"\s+", " ", d).strip()
    if not d.endswith(";"):
        d += ";"
    # ensure name matches
    if name not in d:
        return f"int {name}(void);"
    return d[:-1]  # drop ;


def try_emit_c(insns: list, decl: str, name: str) -> str | None:
    """Pattern-match a tiny function into C. Return full function text or None."""
    # normalize
    ops = [(i.mnemonic, i.op_str) for i in insns]
    # strip trailing ret
    if not ops or ops[-1][0] not in ("ret", "retn"):
        return None
    body_ops = ops[:-1]
    sig = cdecl_sig(decl, name)

    # bare ret / xor eax,eax ; ret
    if not body_ops:
        if "void" in sig.split("(")[0]:
            return f"{sig} {{\n}}\n"
        return f"{sig} {{\n  return 0;\n}}\n"
    if body_ops == [("xor", "eax, eax")] or body_ops == [("xor", "eax, eax"), ("nop", "")]:
        return f"{sig} {{\n  return 0;\n}}\n"

    # mov al/ax/eax, [imm]; ret  — load global scalar
    if len(body_ops) == 1 and body_ops[0][0] == "mov":
        m = re.match(
            r"(al|ax|eax), (byte|word|dword) ptr \[0x([0-9a-f]+)\]",
            body_ops[0][1],
        )
        if m:
            g = int(m.group(3), 16)
            ctype = {"byte": "uint8_t", "word": "uint16_t", "dword": "uint32_t"}[m.group(2)]
            return f"{sig} {{\n  return *({ctype} *)0x{g:x};\n}}\n"
        m = re.match(r"eax, (0x[0-9a-f]+|\d+)", body_ops[0][1])
        if m:
            return f"{sig} {{\n  return ({m.group(1)});\n}}\n"
        m = re.match(
            r"(byte|word|dword) ptr \[0x([0-9a-f]+)\], (0x[0-9a-f]+|\d+)",
            body_ops[0][1],
        )
        if m:
            ctype = {"byte": "uint8_t", "word": "uint16_t", "dword": "uint32_t"}[m.group(1)]
            g = int(m.group(2), 16)
            return (
                f"{sig} {{\n"
                f"  *({ctype} *)0x{g:x} = ({ctype}){m.group(3)};\n"
                f"}}\n"
            )

    # push imm; call rel; pop ecx; ret  — stdcall thunk (one stack arg)
    if (
        len(body_ops) == 3
        and body_ops[0][0] == "push"
        and body_ops[1][0] == "call"
        and body_ops[2] == ("pop", "ecx")
    ):
        mimm = re.match(r"(-?0x[0-9a-f]+|-?\d+)", body_ops[0][1])
        mcall = re.match(r"0x([0-9a-f]+)", body_ops[1][1])
        if mimm and mcall:
            targ = int(mcall.group(1), 16)
            return (
                f"{sig} {{\n"
                f"  ((void (*)(int))0x{targ:x})({mimm.group(1)});\n"
                f"}}\n"
            )

    # push ebp; mov ebp,esp; fld [ebp+8]; fld [ebp+0xc]; fpatan; pop ebp; ret
    if body_ops == [
        ("push", "ebp"),
        ("mov", "ebp, esp"),
        ("fld", "dword ptr [ebp + 8]"),
        ("fld", "dword ptr [ebp + 0xc]"),
        ("fpatan", ""),
        ("pop", "ebp"),
    ]:
        m = re.search(r"\(([^)]*)\)", sig)
        params = [p.strip() for p in (m.group(1) if m else "").split(",") if p.strip()]
        if len(params) >= 2:
            a0 = params[0].split()[-1].strip("*")
            a1 = params[1].split()[-1].strip("*")
            return (
                f"{sig} {{\n"
                f"  return x87_fatan2f({a0}, {a1});\n"
                f"}}\n"
            )

    # push ebp; mov ebp,esp; mov eax,[ebp+8]; fld [ebp+0xc]; mov ecx,[ebp+0x10];
    # fstp [eax]; mov edx,[ebp+0x14]; mov [eax+4],ecx; mov [eax+8],edx; pop ebp; ret
    if (
        len(body_ops) >= 8
        and body_ops[0] == ("push", "ebp")
        and body_ops[1] == ("mov", "ebp, esp")
        and body_ops[-1] == ("pop", "ebp")
    ):
        mid = body_ops[2:-1]
        if (
            len(mid) == 7
            and mid[0][1] == "eax, dword ptr [ebp + 8]"
            and mid[1][0] == "fld"
            and mid[2][1] == "ecx, dword ptr [ebp + 0x10]"
            and mid[3][0] == "fstp"
            and mid[4][1] == "edx, dword ptr [ebp + 0x14]"
            and mid[5][1] == "dword ptr [eax + 4], ecx"
            and mid[6][1] == "dword ptr [eax + 8], edx"
        ):
            m = re.search(r"\(([^)]*)\)", sig)
            params = [p.strip() for p in (m.group(1) if m else "").split(",") if p.strip()]
            if len(params) >= 4:
                out = params[0].split()[-1].strip("*")
                val = params[1].split()[-1].strip("*")
                f4 = params[2].split()[-1].strip("*")
                f8 = params[3].split()[-1].strip("*")
                return (
                    f"{sig} {{\n"
                    f"  {out}[0] = {val};\n"
                    f"  *(int *)({out} + 1) = {f4};\n"
                    f"  *(int *)({out} + 2) = {f8};\n"
                    f"}}\n"
                )

    # mov eax, [imm]; mov byte/word/dword [eax+off], imm; ret  (store via global ptr)
    # cinematic_skip_start style: mov eax,[g]; mov byte ptr [eax+off], imm; ret
    if len(body_ops) == 2 and body_ops[0][0] == "mov" and body_ops[1][0] == "mov":
        m0 = re.match(r"eax, dword ptr \[0x([0-9a-f]+)\]", body_ops[0][1])
        m1 = re.match(
            r"(byte|word|dword) ptr \[eax \+ 0x([0-9a-f]+)\], (0x[0-9a-f]+|\d+)",
            body_ops[1][1],
        )
        if m0 and m1:
            g = int(m0.group(1), 16)
            width, off, val = m1.group(1), int(m1.group(2), 16), m1.group(3)
            ctype = {"byte": "uint8_t", "word": "uint16_t", "dword": "uint32_t"}[width]
            return (
                f"{sig} {{\n"
                f"  uint8_t *base = *(uint8_t **)0x{g:x};\n"
                f"  *({ctype} *)(base + 0x{off:x}) = ({ctype}){val};\n"
                f"}}\n"
            )

    # mov eax, [imm]; mov ax/eax, [eax+off]; ret  — load field via global
    if len(body_ops) == 2 and body_ops[0][0] == "mov" and body_ops[1][0] == "mov":
        m0 = re.match(r"eax, dword ptr \[0x([0-9a-f]+)\]", body_ops[0][1])
        m1 = re.match(
            r"(e?ax|eax), (byte|word|dword) ptr \[eax \+ 0x([0-9a-f]+)\]",
            body_ops[1][1],
        ) or re.match(
            r"(ax), word ptr \[eax \+ 0x([0-9a-f]+)\]",
            body_ops[1][1],
        )
        if m0 and m1:
            g = int(m0.group(1), 16)
            if len(m1.groups()) == 3:
                width = m1.group(2)
                off = int(m1.group(3), 16)
            else:
                width = "word"
                off = int(m1.group(2), 16)
            ctype = {"byte": "uint8_t", "word": "uint16_t", "dword": "uint32_t", "ax": "uint16_t"}.get(
                width, "uint32_t"
            )
            return (
                f"{sig} {{\n"
                f"  uint8_t *base = *(uint8_t **)0x{g:x};\n"
                f"  return *({ctype} *)(base + 0x{off:x});\n"
                f"}}\n"
            )

    # TIFF-style: push ebp; mov ebp,esp; mov eax,[ebp+8]; mov eax,[eax+off]; pop ebp; ret
    if (
        len(body_ops) >= 4
        and body_ops[0] == ("push", "ebp")
        and body_ops[1] == ("mov", "ebp, esp")
        and body_ops[-1] == ("pop", "ebp")
    ):
        mid = body_ops[2:-1]
        if len(mid) == 2 and mid[0][0] == "mov" and mid[1][0] in ("mov", "movsx", "movzx"):
            if mid[0][1] == "eax, dword ptr [ebp + 8]":
                m = re.match(
                    r"eax, (byte|word|dword) ptr \[eax \+ 0x([0-9a-f]+)\]",
                    mid[1][1],
                ) or re.match(r"eax, dword ptr \[eax\]", mid[1][1])
                if mid[1][1] == "eax, dword ptr [eax]":
                    return (
                        f"{sig} {{\n"
                        f"  void **p = (void **)(uintptr_t)/*arg0*/0;\n"
                        f"  /* rewritten */\n"
                        f"  uint32_t *obj = (uint32_t *)(uintptr_t)*(uint32_t *)((char *)&obj + 0);\n"
                        f"}}\n"
                    )
                # simpler: use param from decl
                m = re.search(r"\(([^)]*)\)", sig)
                params = (m.group(1) if m else "").strip()
                if params and params != "void":
                    pname = params.split(",")[0].strip().split()[-1].strip("*")
                    if mid[1][1] == "eax, dword ptr [eax]":
                        return f"{sig} {{\n  return *(uint32_t *){pname};\n}}\n"
                    mm = re.match(
                        r"eax, (byte|word|dword) ptr \[eax \+ 0x([0-9a-f]+)\]",
                        mid[1][1],
                    )
                    if mm:
                        ctype = {"byte": "uint8_t", "word": "uint16_t", "dword": "uint32_t"}[
                            mm.group(1)
                        ]
                        off = int(mm.group(2), 16)
                        return (
                            f"{sig} {{\n"
                            f"  return *({ctype} *)((uint8_t *){pname} + 0x{off:x});\n"
                            f"}}\n"
                        )
                    mm = re.match(
                        r"eax, (byte|word|dword) ptr \[eax \+ 0x([0-9a-f]+)\]",
                        mid[1][1].replace("movsx ", "").replace("movzx ", ""),
                    )
        # movsx/movzx variants
        if len(mid) == 2 and mid[0][1] == "eax, dword ptr [ebp + 8]":
            mm = re.match(
                r"eax, (byte|word) ptr \[eax \+ 0x([0-9a-f]+)\]",
                mid[1][1],
            )
            if mid[1][0] in ("movsx", "movzx") and mm:
                m = re.search(r"\(([^)]*)\)", sig)
                params = (m.group(1) if m else "").strip()
                pname = params.split(",")[0].strip().split()[-1].strip("*") if params else "arg0"
                ctype = {"byte": "int8_t" if mid[1][0] == "movsx" else "uint8_t",
                         "word": "int16_t" if mid[1][0] == "movsx" else "uint16_t"}[mm.group(1)]
                # use signed/unsigned properly via cast
                off = int(mm.group(2), 16)
                base_t = "int16_t" if mm.group(1) == "word" and mid[1][0] == "movsx" else (
                    "uint16_t" if mm.group(1) == "word" else (
                        "int8_t" if mid[1][0] == "movsx" else "uint8_t"
                    )
                )
                return (
                    f"{sig} {{\n"
                    f"  return *({base_t} *)((uint8_t *){pname} + 0x{off:x});\n"
                    f"}}\n"
                )


    # zero two dwords via global pointer
    if len(body_ops) == 3 and body_ops[0][0] == "mov":
        m0 = re.match(r"eax, dword ptr \[0x([0-9a-f]+)\]", body_ops[0][1])
        m1 = re.match(r"dword ptr \[eax\], 0", body_ops[1][1])
        m2 = re.match(r"dword ptr \[eax \+ 4\], 0", body_ops[2][1]) or re.match(
            r"dword ptr \[eax \+ 0x4\], 0", body_ops[2][1]
        )
        if m0 and m1 and m2:
            g = int(m0.group(1), 16)
            return (
                f"{sig} {{\n"
                f"  uint32_t *base = *(uint32_t **)0x{g:x};\n"
                f"  base[0] = 0;\n"
                f"  base[1] = 0;\n"
                f"}}\n"
            )


    # Frame global store: mov eax/al, [ebp+8]; mov [imm], eax/al
    if (
        len(body_ops) >= 4
        and body_ops[0] == ("push", "ebp")
        and body_ops[1] == ("mov", "ebp, esp")
        and body_ops[-1] == ("pop", "ebp")
    ):
        mid = body_ops[2:-1]
        if len(mid) == 2 and mid[0][0] == "mov" and mid[1][0] == "mov":
            load_ok = mid[0][1] in (
                "eax, dword ptr [ebp + 8]",
                "eax, dword ptr [ebp + 0x8]",
                "al, byte ptr [ebp + 8]",
                "al, byte ptr [ebp + 0x8]",
            )
            m1 = re.match(
                r"(byte|dword) ptr \[0x([0-9a-f]+)\], (eax|al)",
                mid[1][1],
            )
            if load_ok and m1:
                width, g = m1.group(1), int(m1.group(2), 16)
                m = re.search(r"\(([^)]*)\)", sig)
                params = (m.group(1) if m else "").strip()
                pname = "value"
                if params and params != "void":
                    pname = params.split(",")[0].strip().split()[-1].strip("*")
                ctype = "uint8_t" if width == "byte" else "uint32_t"
                return (
                    f"{sig} {{\n"
                    f"  *({ctype} *)0x{g:x} = ({ctype}){pname};\n"
                    f"}}\n"
                )

    # mov dword/byte ptr [imm], imm; ret
    if len(body_ops) == 1 and body_ops[0][0] == "mov":
        m = re.match(
            r"(byte|word|dword) ptr \[0x([0-9a-f]+)\], (0x[0-9a-f]+|\d+)",
            body_ops[0][1],
        )
        if m:
            width, g, val = m.group(1), int(m.group(2), 16), m.group(3)
            ctype = {"byte": "uint8_t", "word": "uint16_t", "dword": "uint32_t"}[width]
            return (
                f"{sig} {{\n"
                f"  *({ctype} *)0x{g:x} = ({ctype}){val};\n"
                f"}}\n"
            )
        m = re.match(r"eax, (0x[0-9a-f]+|\d+)", body_ops[0][1])
        if m:
            return f"{sig} {{\n  return {m.group(1)};\n}}\n"
        m = re.match(r"eax, dword ptr \[0x([0-9a-f]+)\]", body_ops[0][1])
        if m:
            g = int(m.group(1), 16)
            return f"{sig} {{\n  return *(uint32_t *)0x{g:x};\n}}\n"

    # store imm through pointer arg: push ebp; mov ebp,esp; mov eax,[ebp+8]; mov [eax(+off)], IMM; pop ebp; ret
    if (
        len(body_ops) >= 4
        and body_ops[0] == ("push", "ebp")
        and body_ops[1] == ("mov", "ebp, esp")
        and body_ops[-1] == ("pop", "ebp")
    ):
        mid = body_ops[2:-1]
        if (
            len(mid) == 2
            and mid[0] == ("mov", "eax, dword ptr [ebp + 8]")
            and mid[1][0] == "mov"
        ):
            m = re.match(
                r"(byte|word|dword) ptr \[eax(?: \+ (0x[0-9a-f]+|\d+))?\]"
                r", (0x[0-9a-f]+|-?\d+)$",
                mid[1][1],
            )
            if m:
                width, off, val = m.group(1), m.group(2), m.group(3)
                o = int(off, 0) if off else 0
                ctype = {"byte": "uint8_t", "word": "uint16_t", "dword": "uint32_t"}[width]
                pname = "arg0"
                pm = re.search(r"\(([^)]*)\)", sig)
                params = (pm.group(1) if pm else "").strip()
                if params and params != "void":
                    pname = params.split(",")[0].strip().split()[-1].strip("*")
                if o == 0:
                    return (
                        f"{sig} {{\n"
                        f"  *({ctype} *){pname} = ({ctype}){val};\n"
                        f"}}\n"
                    )
                return (
                    f"{sig} {{\n"
                    f"  *({ctype} *)((uint8_t *){pname} + 0x{o:x}) = ({ctype}){val};\n"
                    f"}}\n"
                )

    return None


def run_unicorn(name: str, addr: int) -> bool:
    cmd = [
        sys.executable,
        str(ROOT / "tools/equivalence/unicorn_diff.py"),
        name,
        "--allow-stubs",
        "--seeds",
        "100",
        "-q",
    ]
    # ensure oracle
    oracle = ROOT / "delinked" / "functions" / f"{addr:08x}.obj"
    if not oracle.exists():
        subprocess.run(
            [
                sys.executable,
                str(ROOT / "tools/equivalence/xbe_to_coff.py"),
                "--addr",
                hex(addr),
                "--out",
                str(oracle),
            ],
            cwd=ROOT,
            check=False,
        )
    proc = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, timeout=30)
    text = (proc.stdout or "") + (proc.stderr or "")
    m = re.search(r"(\d+) passed, (\d+) failed, (\d+) errors", text)
    if not m:
        print(f"  unicorn no-parse {name}: {text[-200:]}")
        return False
    p, f, e = map(int, m.groups())
    ok = proc.returncode == 0 and f == 0 and e == 0 and p >= 90
    print(f"  unicorn {name}: {p}/{f}/{e} ok={ok}")
    return ok


def main() -> int:
    from typing import List

    kb = json.loads(KB_PATH.read_text())
    by_addr, starts = load_kb(KB_PATH)
    xbe = Xbe((ROOT / "halo-patched" / "cachebeta.xbe").read_bytes())
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    flips = []
    LEDGER.parent.mkdir(parents=True, exist_ok=True)

    for i, ai in enumerate(starts):
        meta = by_addr[ai]
        if meta.get("ported") is not False:
            continue
        end = starts[i + 1] if i + 1 < len(starts) else ai + 40
        size = end - ai
        if size > 48:
            continue
        src = meta.get("source") or ""
        if any(
            x in src.lower()
            for x in ("xdk", "d3d", "dsound", "libcmt", "bink", "xnet", "xapilib")
        ):
            continue
        try:
            raw = xbe_bytes(xbe, ai, end)
        except Exception:
            continue
        insns = list(md.disasm(raw, ai))
        if not insns:
            continue
        # truncate at ret
        cut = []
        for insn in insns:
            cut.append(insn)
            if insn.mnemonic in ("ret", "retn"):
                break
        else:
            continue
        c_src = try_emit_c(cut, meta.get("decl") or "", meta["name"])
        if not c_src:
            continue
        # skip broken emitters
        if "rewritten" in c_src and "uintptr_t)*(uint32_t" in c_src:
            continue
        sp = resolve_src(src)
        if sp is None:
            print(f"skip no source {hex(ai)} {src}")
            continue
        text = sp.read_text(encoding="utf-8", errors="replace")
        span = find_naked_def(text, meta["name"], ai)
        if not span:
            # Already readable C — still try to prove.
            if "readable C lift" in text[
                max(0, text.find(meta["name"]) - 80) : text.find(meta["name"]) + 40
            ] or f"FUN_{ai:08x}" in text and "naked" not in text[
                max(0, text.find(f"FUN_{ai:08x}") - 120) : text.find(f"FUN_{ai:08x}") + 20
            ]:
                print(f"PROVE-ONLY {hex(ai)} {meta['name']}")
                if run_unicorn(meta["name"], ai):
                    for obj in kb.get("objects", []):
                        for fn in obj.get("functions") or []:
                            if fn.get("addr") and int(fn["addr"], 16) == ai:
                                fn["ported"] = True
                                flips.append(hex(ai))
                                break
                    with LEDGER.open("a") as f:
                        f.write(
                            json.dumps({"addr": hex(ai), "name": meta["name"], "ok": True})
                            + "\n"
                        )
                continue
            print(f"skip no naked def {hex(ai)} {meta['name']} in {sp}")
            continue
        # ensure includes
        needs = []
        if "uint8_t" in c_src or "uint16_t" in c_src or "uint32_t" in c_src:
            if "#include <stdint.h>" not in text and '#include "stdint.h"' not in text:
                needs.append("#include <stdint.h>\n")
        new_text = text[: span[0]] + c_src + text[span[1] :]
        if needs:
            new_text = "".join(needs) + new_text
        sp.write_text(new_text)
        print(f"LIFTED {hex(ai)} {meta['name']} -> {sp}")
        # build TU lightly? rely on on-demand compile in unicorn
        if run_unicorn(meta["name"], ai):
            # flip in kb objects
            for obj in kb.get("objects", []):
                for fn in obj.get("functions") or []:
                    if fn.get("addr") == meta.get("addr") or (
                        fn.get("addr") and int(fn["addr"], 16) == ai
                    ):
                        fn["ported"] = True
                        flips.append(hex(ai))
                        break
            with LEDGER.open("a") as f:
                f.write(json.dumps({"addr": hex(ai), "name": meta["name"], "ok": True}) + "\n")
        else:
            # revert file change on fail
            sp.write_text(text)
            with LEDGER.open("a") as f:
                f.write(json.dumps({"addr": hex(ai), "name": meta["name"], "ok": False}) + "\n")
            print(f"  REVERT {hex(ai)}")

        if len(flips) and len(flips) % 20 == 0:
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n")
            print(f"checkpoint flips={len(flips)}")

    if flips:
        KB_PATH.write_text(json.dumps(kb, indent=2) + "\n")
    print(f"done flips={len(flips)} {flips}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
