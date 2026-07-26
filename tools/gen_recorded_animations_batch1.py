#!/usr/bin/env python3
"""Generate recorded_animations.obj batch1 draft fragment + disassembly artifact."""
from __future__ import annotations

import json
import re
from pathlib import Path

from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe

ROOT = Path(__file__).resolve().parents[1]
FRAG = ROOT / "tools" / "recorded_animations_batch1_fragment.c"
DISASM_OUT = ROOT / "artifacts" / "recorded_animations_batch1_disasm.txt"
OBJECT = "recorded_animations.obj"
MAX_SIZE = 144

DECLS = {
    "0x94020": "void FUN_00094020(int *out, int *cursor_ptr, int a, int c);",
    "0x94060": "void FUN_00094060(int *out, int **stream, int *dest);",
    "0x94290": "void FUN_00094290(void);",
    "0x94a70": "void FUN_00094a70(int a, int *cursor, int c);",
    "0x94ba0": "void FUN_00094ba0(void);",
    "0x94c70": "void recorded_animations_clear_debug_storage(void);",
    "0x94ff0": "char recorded_animation_controlling_unit(int unit_handle);",
    "0x95050": "void FUN_00095050(int unit@<edi>, int *out@<ebx>);",
    "0x952d0": "void recorded_animation_kill(int unit_handle);",
    "0x955b0": "int recorded_animation_get_time_left(int unit_handle);",
    "0x95660": "int recorded_animation_play_and_delete(int unit, int anim);",
    "0x95680": "int FUN_00095680(int unit, int anim);",
    "0x956e0": "void FUN_000956e0(int object, void *ctrl);",
    "0x95750": "char FUN_00095750(int object);",
    "0x95790": "char FUN_00095790(int object);",
    "0x958f0": "void FUN_000958f0(int object);",
    "0x95930": "void FUN_00095930(int object);",
    "0x959b0": "void FUN_000959b0(int object, void *ctrl);",
    "0x95a20": "char FUN_00095a20(int object);",
    "0x95a60": "char FUN_00095a60(int object);",
    "0x95ad0": "void FUN_00095ad0(int object, void *ctrl);",
    "0x95b50": "char FUN_00095b50(int object);",
    "0x95be0": "void FUN_00095be0(int object);",
    "0x95c10": "void FUN_00095c10(int object);",
}


def load_targets() -> list[tuple[str, str, int]]:
    kb = json.loads((ROOT / "kb.json").read_text())
    obj = next(o for o in kb["objects"] if o["name"] == OBJECT)
    out = []
    for f in obj["functions"]:
        if f.get("ported") is not None:
            continue
        addr = f["addr"]
        end = int(f.get("end", f["addr"]), 16) if f.get("end") else int(addr, 16) + 0x40
        size = end - int(addr, 16)
        if size > MAX_SIZE:
            continue
        name = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", f.get("decl", ""))
        out.append((addr, name.group(1) if name else addr, size))
    return sorted(out, key=lambda t: int(t[0], 16))


def disassemble(xbe_path: Path, targets: list[tuple[str, str, int]]) -> None:
    xbe = Xbe.from_file(str(xbe_path))
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    md.detail = True
    lines = []
    for addr, name, _size in targets:
        if addr not in DECLS:
            continue
        start = int(addr, 16)
        end = start + _size
        insns = list(md.disasm(xbe.image[start:end], start))
        lines.append(f"\n=== {name} @ {addr} end~{end:08x} insns={len(insns)} ===")
        for ins in insns:
            comment = ""
            if ins.mnemonic == "call" and ins.op_str.startswith("0x"):
                target = ins.op_str.split()[0]
                lines.append(f"  {ins.address:08x}: {ins.mnemonic:<8} {ins.op_str}  ; {target}")
                continue
            lines.append(f"  {ins.address:08x}: {ins.mnemonic:<8} {ins.op_str}")
    DISASM_OUT.parent.mkdir(parents=True, exist_ok=True)
    DISASM_OUT.write_text("\n".join(lines) + "\n")
    print(f"wrote {DISASM_OUT} ({len(lines)} lines)")


def main() -> None:
    targets = load_targets()
    xbe = ROOT.parent / "halo-patched" / "cachebeta.xbe"
    if not xbe.exists():
        xbe = Path("/work/halo-patched/cachebeta.xbe")
    if xbe.exists():
        disassemble(xbe, targets)
    print(f"batch1 targets in DECLS: {len(DECLS)}")


if __name__ == "__main__":
    main()
