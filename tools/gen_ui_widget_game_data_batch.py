#!/usr/bin/env python3
"""Generate ui_widget_game_data_input_functions.obj batch drafts."""
from __future__ import annotations

import json
import re
from pathlib import Path

from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe

ROOT = Path(__file__).resolve().parents[1]
IMPL = ROOT / "tools" / "ui_widget_game_data_batch_impl.c"
FRAG = ROOT / "tools" / "ui_widget_game_data_batch_fragment.c"
DISASM_OUT = ROOT / "artifacts" / "ui_widget_game_data_batch_disasm.txt"
OBJECT = "ui_widget_game_data_input_functions.obj"


def load_decls() -> dict[str, str]:
    kb = json.loads((ROOT / "kb.json").read_text())
    obj = next(o for o in kb["objects"] if o["name"] == OBJECT)
    decls: dict[str, str] = {}
    for f in obj["functions"]:
        if f.get("ported") is not None:
            continue
        addr = f["addr"].lower()
        m = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", f.get("decl") or "")
        name = m.group(1) if m else f"FUN_{int(addr, 16):08x}"
        decls[addr] = f"void {name}(void *widget);"
    return decls


DECLS = load_decls()


def write_disasm() -> None:
    xbe = Xbe.from_file(str(ROOT / "halo-patched/cachebeta.xbe"))
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    kb = json.loads((ROOT / "kb.json").read_text())
    obj = next(o for o in kb["objects"] if o["name"] == OBJECT)
    fns = sorted(obj["functions"], key=lambda f: int(f["addr"], 16))
    addrs = [(int(f["addr"], 16), f) for f in fns]

    def get_bytes(va: int, end: int) -> bytes:
        for sec in xbe.sections.values():
            s = sec.header.virtual_addr
            if s <= va < s + sec.header.virtual_size:
                return bytes(sec.data[va - s : end - s])
        raise RuntimeError(hex(va))

    lines: list[str] = []
    for i, (va, f) in enumerate(addrs):
        if f.get("ported") is not None:
            continue
        end = addrs[i + 1][0] if i + 1 < len(addrs) else va + 0x200
        data = get_bytes(va, min(end, va + 0x2000))
        insns = list(md.disasm(data, va))
        name = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", DECLS.get(f["addr"].lower(), ""))
        label = name.group(1) if name else f["addr"]
        lines.append(f"\n=== {label} @ {f['addr']} end~{end:08x} ===")
        for ins in insns[:150]:
            if ins.address >= end:
                break
            lines.append(f"  {ins.address:08x}: {ins.mnemonic:<8} {ins.op_str}")
    DISASM_OUT.parent.mkdir(parents=True, exist_ok=True)
    DISASM_OUT.write_text("\n".join(lines) + "\n")
    print(f"wrote {DISASM_OUT} ({len(lines)} lines)")


def gen_impl() -> str:
    parts = ["/* --- ui_widget_game_data_input_functions.obj batch (2026-07-26) --- */\n"]
    for addr in sorted(DECLS.keys(), key=lambda x: int(x, 16)):
        decl = DECLS[addr]
        name = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", decl).group(1)
        parts.append(
            f"/* {addr} */\n{decl.split(';')[0]}\n{{\n  (void)widget;\n}}\n"
        )
    return "\n".join(parts)


def main() -> None:
    write_disasm()
    text = gen_impl()
    IMPL.write_text(text)
    FRAG.write_text(text)
    print(f"wrote {IMPL} ({len(DECLS)} drafts)")


if __name__ == "__main__":
    main()
