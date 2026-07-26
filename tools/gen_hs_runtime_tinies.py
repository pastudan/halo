#!/usr/bin/env python3
"""Draft small hs_runtime.obj wrappers from XBE disassembly patterns."""
from __future__ import annotations

import json
import re
from collections import Counter
from pathlib import Path

from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe

ROOT = Path(__file__).resolve().parents[1]
OBJECT = "hs_runtime.obj"
MAX_SIZE = 96


def main() -> None:
    xbe = Xbe.from_file(str(ROOT / "halo-patched/cachebeta.xbe"))
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    kb = json.loads((ROOT / "kb.json").read_text())
    obj = next(o for o in kb["objects"] if o["name"] == OBJECT)
    fns = sorted(obj["functions"], key=lambda f: int(f["addr"], 16))
    addrs = [(int(f["addr"], 16), f) for f in fns]

    addr_name: dict[int, str] = {}
    addr_decl: dict[int, str] = {}
    for o in kb["objects"]:
        for f in o.get("functions", []):
            m = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", f.get("decl") or "")
            if m:
                addr_name[int(f["addr"], 16)] = m.group(1)
                addr_decl[int(f["addr"], 16)] = f.get("decl") or ""

    def get_bytes(va: int, end: int) -> bytes:
        for sec in xbe.sections.values():
            s = sec.header.virtual_addr
            if s <= va < s + sec.header.virtual_size:
                return bytes(sec.data[va - s : end - s])
        raise RuntimeError(hex(va))

    gen: list[tuple[str, str, str]] = []
    kinds = Counter()
    asm_dump: list[str] = []

    for i, (va, f) in enumerate(addrs):
        if f.get("ported") in (True, False):
            continue
        end = addrs[i + 1][0] if i + 1 < len(addrs) else va + 0x80
        size = end - va
        if size > MAX_SIZE:
            continue
        data = get_bytes(va, end)
        insns = list(md.disasm(data, va))
        name = re.search(
            r"([A-Za-z_][A-Za-z0-9_]*)\s*\(",
            f.get("decl", "void FUN(void);"),
        ).group(1)
        lines = []
        calls: list[int] = []
        for x in insns:
            if x.address >= end:
                break
            line = f"  {x.address:08x}: {x.mnemonic:8} {x.op_str}"
            if x.mnemonic == "call" and x.op_str.startswith("0x"):
                t = int(x.op_str, 16)
                calls.append(t)
                nm = addr_name.get(t, "")
                if nm:
                    line += f"  ; {nm}"
            lines.append(line)
        asm_dump.append(
            f"\n=== {name} @ {f['addr']} size={size} ===\n" + "\n".join(lines)
        )

        # Pattern: return constant / simple field load — leave for hand draft via asm
        # Pattern: single call passthrough with stack args
        if len(calls) == 1:
            cal = calls[0]
            cal_name = addr_name.get(cal, f"FUN_{cal:08x}")
            # detect stack arg count from pushes before call (rough)
            pushes = []
            for x in insns:
                if x.address >= end:
                    break
                if x.mnemonic == "call":
                    break
                if x.mnemonic == "push":
                    pushes.append(x.op_str)
            # common: push arg; call; — 1 stack arg, maybe reg args
            # For reliability, emit a TODO-shaped body only for known simple forms

            # form A: push ebp; mov ebp,esp; mov eax,[ebp+8]; push eax; call; leave; ret
            # form B: register wrappers — detect mov/push of ebp+N

            stack_args = []
            for x in insns:
                if x.mnemonic == "call":
                    break
                m = re.match(r"dword ptr \[ebp \+ (0x[0-9a-f]+)\]", x.op_str)
                if x.mnemonic == "push" and m:
                    off = int(m.group(1), 16)
                    stack_args.append(off)
                elif x.mnemonic == "mov" and "ebp +" in x.op_str:
                    m2 = re.search(r"\[ebp \+ (0x[0-9a-f]+)\]", x.op_str)
                    if m2 and x.op_str.split(",")[0].strip() in (
                        "eax",
                        "ecx",
                        "edx",
                    ):
                        # loaded for later push
                        pass

            # Very specific known patterns from scan:
            # terminal_output / hs_object_iterate / FUN wrappers with 1-2 stack args
            body = None
            decl = f.get("decl") or f"void {name}(void);"

            # Pattern: void f(a) { g(a); } or return g(a)
            if size <= 32 and len(pushes) >= 1:
                # Inspect whether result is returned
                returns_eax = any(
                    x.mnemonic == "ret"
                    for x in insns
                )
                # Build by reading ebp offsets pushed
                pushed_ebp = []
                for x in insns:
                    if x.mnemonic == "call":
                        break
                    if x.mnemonic == "push":
                        m = re.match(
                            r"dword ptr \[ebp \+ (0x[0-9a-f]+)\]", x.op_str
                        )
                        if m:
                            pushed_ebp.append(int(m.group(1), 16))
                        elif x.op_str in ("0", "0x0", "1", "0x1", "2", "0x2", "3", "0x3", "4", "0x4", "8", "0x8"):
                            pushed_ebp.append(("imm", int(x.op_str, 0)))
                        elif re.match(r"0x[0-9a-f]+", x.op_str):
                            pushed_ebp.append(("imm", int(x.op_str, 16)))

            # Fall through: emit annotated stub with disasm comment for hand fill
            # Actually for tinies, emit C from a whitelist of exact patterns below.

        # Hand-pattern match on full mnemonic stream
        text = "\n".join(f"{x.mnemonic} {x.op_str}" for x in insns if x.address < end)

        def stack_params(n: int) -> str:
            names = ["a0", "a1", "a2", "a3", "a4"]
            types = ["int"] * n
            return ", ".join(f"{types[i]} {names[i]}" for i in range(n))

        body = None
        new_decl = None

        # empty / ret-only
        if re.fullmatch(r"(nop )*(ret ?)?(nop )*", text.replace("\n", " ").strip()) or text.strip() in (
            "ret",
            "push ebp\nmov ebp, esp\npop ebp\nret",
        ):
            body = f"void {name}(void)\n{{\n}}"
            new_decl = f"void {name}(void);"
            kinds["empty"] += 1

        # single call, 1 stack arg: f(x) { g(x); }
        m = re.match(
            r"push ebp\nmov ebp, esp\n(?:push \w+\n)*"
            r"mov \w+, dword ptr \[ebp \+ 8\]\n"
            r"push \w+\n"
            r"call 0x([0-9a-f]+)\n"
            r"add esp, [0-9x]+\n"
            r"(?:pop \w+\n)*pop ebp\nret",
            text,
        )
        if body is None and m:
            cal = int(m.group(1), 16)
            cal_name = addr_name.get(cal, f"FUN_{cal:08x}")
            body = (
                f"void {name}(int a0)\n{{\n"
                f"  {cal_name}(a0);\n"
                f"}}"
            )
            new_decl = f"void {name}(int a0);"
            kinds["call1"] += 1

        # return call with 1 arg
        m = re.match(
            r"push ebp\nmov ebp, esp\n"
            r"mov \w+, dword ptr \[ebp \+ 8\]\n"
            r"push \w+\n"
            r"call 0x([0-9a-f]+)\n"
            r"add esp, [0-9x]+\n"
            r"pop ebp\nret",
            text,
        )
        if body is None and m:
            cal = int(m.group(1), 16)
            cal_name = addr_name.get(cal, f"FUN_{cal:08x}")
            # if next insn after call uses eax as return - always for this shape
            body = (
                f"int {name}(int a0)\n{{\n"
                f"  return {cal_name}(a0);\n"
                f"}}"
            )
            new_decl = f"int {name}(int a0);"
            kinds["ret_call1"] += 1

        if body is None:
            kinds["skip"] += 1
            continue

        gen.append((f["addr"], name, body))
        if new_decl:
            f["decl"] = new_decl
            f["ported"] = False

    out = ROOT / "artifacts/hs_runtime_tinies_gen.c"
    out.write_text("\n\n".join(g[2] for g in gen) + "\n")
    (ROOT / "artifacts/hs_runtime_tinies_asm.txt").write_text("\n".join(asm_dump))
    print("generated", len(gen), kinds, "->", out)

    # update kb for generated
    for ah, wname, _ in gen:
        for f in obj["functions"]:
            if f["addr"] == ah:
                f["ported"] = False
    (ROOT / "kb.json").write_text(json.dumps(kb, indent=2) + "\n")

    al_path = ROOT / "tools/audit/deactivation_allowlist.json"
    al = json.loads(al_path.read_text())
    have = {e["addr"] for e in al if isinstance(e, dict)}
    for ah, wname, _ in gen:
        if ah in have:
            continue
        al.append(
            {
                "addr": ah,
                "name": wname,
                "object": OBJECT,
                "reason": "draft lift pending VC71/equivalence — keep inactive until scored",
                "since": "2026-07-25",
            }
        )
    al_path.write_text(json.dumps(al, indent=2) + "\n")


if __name__ == "__main__":
    main()
