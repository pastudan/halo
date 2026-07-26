#!/usr/bin/env python3
"""Disassemble remaining unset hs.obj symbols."""
from __future__ import annotations

import json
import re
from pathlib import Path

from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe

ROOT = Path(__file__).resolve().parents[1]


def main() -> None:
    xbe = Xbe.from_file(str(ROOT / "halo-patched/cachebeta.xbe"))
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    kb = json.loads((ROOT / "kb.json").read_text())
    hs = next(o for o in kb["objects"] if o["name"] == "hs.obj")
    fns = sorted(hs["functions"], key=lambda f: int(f["addr"], 16))
    addrs = [(int(f["addr"], 16), f) for f in fns]

    addr_name: dict[int, str] = {}
    for o in kb["objects"]:
        for f in o.get("functions", []):
            m = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", f.get("decl") or "")
            if m:
                addr_name[int(f["addr"], 16)] = m.group(1)

    def get_bytes(va: int, end: int) -> bytes:
        for sec in xbe.sections.values():
            s = sec.header.virtual_addr
            if s <= va < s + sec.header.virtual_size:
                return bytes(sec.data[va - s : end - s])
        raise RuntimeError(hex(va))

    chunks: list[str] = []
    for i, (va, f) in enumerate(addrs):
        if f.get("ported") in (True, False):
            continue
        end = addrs[i + 1][0] if i + 1 < len(addrs) else va + 0x200
        size = end - va
        data = get_bytes(va, min(end, va + 0x800))
        insns = list(md.disasm(data, va))
        calls: list[tuple[int, str]] = []
        lines: list[str] = []
        for x in insns:
            if x.address >= end:
                break
            line = f"  {x.address:08x}: {x.mnemonic:8} {x.op_str}"
            if x.mnemonic == "call" and x.op_str.startswith("0x"):
                t = int(x.op_str, 16)
                nm = addr_name.get(t, "")
                if nm:
                    line += f"  ; {nm}"
                calls.append((t, nm))
            lines.append(line)
        name = re.search(
            r"([A-Za-z_][A-Za-z0-9_]*)\s*\(",
            f.get("decl", "void FUN(void);"),
        ).group(1)
        header = (
            f"\n=== {name} @ {f['addr']} size~{size} "
            f"insns={len(lines)} calls={len(calls)} ===\n"
        )
        body = "\n".join(lines[:160])
        if len(lines) > 160:
            body += f"\n  ... ({len(lines) - 160} more insns)"
        chunks.append(header + body)
        print(f"{f['addr']} {name:35} size={size:5} insns={len(lines):4} calls={len(calls)}")

    out = ROOT / "artifacts/hs_remaining_disasm.txt"
    out.write_text("\n".join(chunks))
    print(f"wrote {out}")


if __name__ == "__main__":
    main()
