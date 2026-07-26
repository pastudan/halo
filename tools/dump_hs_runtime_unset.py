#!/usr/bin/env python3
"""Dump remaining unset hs_runtime.obj symbols (size-capped)."""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe

ROOT = Path(__file__).resolve().parents[1]
MAX_SIZE = int(sys.argv[1]) if len(sys.argv) > 1 else 220


def main() -> None:
    xbe = Xbe.from_file(str(ROOT / "halo-patched/cachebeta.xbe"))
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    kb = json.loads((ROOT / "kb.json").read_text())
    obj = next(o for o in kb["objects"] if o["name"] == "hs_runtime.obj")
    fns = sorted(obj["functions"], key=lambda f: int(f["addr"], 16))
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
        end = addrs[i + 1][0] if i + 1 < len(addrs) else va + 0x100
        size = end - va
        if size > MAX_SIZE:
            print(f"{f['addr']} SKIP size={size}")
            continue
        data = get_bytes(va, min(end, va + 0x300))
        lines: list[str] = []
        for x in md.disasm(data, va):
            if x.address >= end:
                break
            line = f"  {x.address:08x}: {x.mnemonic:8} {x.op_str}"
            if x.mnemonic == "call" and x.op_str.startswith("0x"):
                t = int(x.op_str, 16)
                nm = addr_name.get(t, "")
                if nm:
                    line += f"  ; {nm}"
            lines.append(line)
        name = re.search(
            r"([A-Za-z_][A-Za-z0-9_]*)\s*\(",
            f.get("decl", "void FUN(void);"),
        ).group(1)
        chunks.append(f"\n=== {name} @ {f['addr']} size={size} ===\n" + "\n".join(lines))
        print(f"{f['addr']} {name:35} size={size:4}")

    out = ROOT / "artifacts/hs_runtime_batch2_asm.txt"
    out.write_text("\n".join(chunks))
    print(f"wrote {len(chunks)} -> {out}")


if __name__ == "__main__":
    main()
