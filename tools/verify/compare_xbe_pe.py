#!/usr/bin/env python3
"""Interim structural compare: original XBE function vs clang PE export.

Not a VC71 score — use when RXDK/Ghidra delinker are unavailable.
"""
from __future__ import annotations

import argparse
import json
import sys
from difflib import SequenceMatcher
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe

ROOT = Path(__file__).resolve().parents[2]


def mnemonics(data: bytes, va: int) -> list[str]:
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    return [insn.mnemonic for insn in md.disasm(data, va)]


def xbe_bytes(xbe: Xbe, va: int, end: int) -> bytes:
    for sec in xbe.sections.values():
        start = sec.header.virtual_addr
        if start <= va < start + sec.header.virtual_size:
            return bytes(sec.data[va - start : end - start])
    raise SystemExit(f"va {va:#x} not in XBE")


def pe_fn_bytes(pe: pefile.PE, name: str) -> tuple[bytes, int]:
    base = pe.OPTIONAL_HEADER.ImageBase
    addr = None
    for exp in pe.DIRECTORY_ENTRY_EXPORT.symbols:
        if exp.name and exp.name.decode() == name:
            addr = base + exp.address
            break
    if addr is None:
        raise SystemExit(f"export {name} missing from PE")

    exports = sorted(
        base + exp.address
        for exp in pe.DIRECTORY_ENTRY_EXPORT.symbols
        if exp.address
    )
    nxt = next((a for a in exports if a > addr), None)
    size = min((nxt - addr) if nxt else 0x800, 0x1000)
    off = pe.get_offset_from_rva(addr - base)
    data = pe.__data__[off : off + size]
    while len(data) > 16 and data[-1] in (0x90, 0xCC, 0x00):
        data = data[:-1]
    return data, addr


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--xbe", default=str(ROOT / "halo-patched/cachebeta.xbe"))
    ap.add_argument("--pe", default=str(ROOT / "build/halo"))
    ap.add_argument(
        "--json-out",
        default=str(ROOT / "artifacts/verify_collision_structural.json"),
    )
    args = ap.parse_args()

    targets = [
        ("FUN_00147380", 0x147380, 0x1473b0),
        ("collision_surface_project_point2d", 0x147990, 0x1479d8),
        ("collision_surface_test_point2d", 0x1479e0, 0x147ad7),
        ("collision_surface_find_closest_point2d", 0x147ae0, 0x147d10),
        ("collision_bsp_test_vector", 0x149480, 0x149570),
        ("collision_bsp_test_sphere", 0x1493b0, 0x149480),
        ("collision_bsp_test_pill_new", 0x148b20, 0x148b90),
        ("bsp3d_test_sphere_recursive", 0x148b90, 0x148eb0),
        # refined hs_runtime / units / bipeds (2026-07-26 wave)
        ("FUN_000c9f90", 0xc9f90, 0xca010),
        ("hs_wake_by_name", 0xcb9a0, 0xcba00),
        ("FUN_001a8770", 0x1a8770, 0x1a8810),
        ("FUN_001a8890", 0x1a8890, 0x1a8910),
        ("FUN_001a8910", 0x1a8910, 0x1a8950),
        ("FUN_001a8950", 0x1a8950, 0x1a89b0),
        ("FUN_001a0db0", 0x1a0db0, 0x1a0e00),
        # collision_bsp extended
        ("FUN_00147ed0", 0x147ed0, 0x148240),
        ("FUN_00148240", 0x148240, 0x148365),
        ("FUN_00148440", 0x148440, 0x1486e0),
        ("FUN_00148370", 0x148370, 0x148440),
        ("FUN_001486e0", 0x1486e0, 0x148780),
        ("FUN_00148780", 0x148780, 0x148910),
        ("FUN_00148910", 0x148910, 0x148b20),
        ("FUN_00148eb0", 0x148eb0, 0x1491d0),
        ("FUN_001491d0", 0x1491d0, 0x1493b0),
        ("FUN_00149570", 0x149570, 0x149680),
        ("FUN_00149680", 0x149680, 0x149c60),
        ("FUN_0014dc30", 0x14dc30, 0x14dce0),
        ("FUN_0014dce0", 0x14dce0, 0x14df70),
        ("FUN_0014ea10", 0x14ea10, 0x14ec30),
        ("FUN_0014e640", 0x14e640, 0x14e7d0),
        ("FUN_0014e7d0", 0x14e7d0, 0x14e940),
        ("FUN_0014e940", 0x14e940, 0x14ea10),
    ]

    xbe = Xbe.from_file(args.xbe)
    pe = pefile.PE(args.pe)
    rows = []

    print("=== Structural mnemonic match (XBE orig vs clang lift) ===")
    print("(Interim — VC71 needs RXDK CL.Exe; equivalence needs delinked .obj)\n")

    for name, va, end in targets:
        orig = xbe_bytes(xbe, va, end)
        cand, cand_va = pe_fn_bytes(pe, name)
        o_m = mnemonics(orig, va)
        c_m = mnemonics(cand, cand_va)
        ratio = SequenceMatcher(None, o_m, c_m, autojunk=False).ratio() * 100.0
        o_calls = sum(1 for m in o_m if m == "call")
        c_calls = sum(1 for m in c_m if m == "call")
        print(
            f"{name}: {ratio:5.1f}%  "
            f"orig_insns={len(o_m)} cand_insns={len(c_m)} "
            f"calls {o_calls}->{c_calls}  "
            f"orig_bytes={len(orig)} cand_bytes={len(cand)}"
        )
        rows.append(
            {
                "name": name,
                "addr": hex(va),
                "match_pct": round(ratio, 2),
                "orig_insns": len(o_m),
                "cand_insns": len(c_m),
                "orig_calls": o_calls,
                "cand_calls": c_calls,
                "note": "clang-vs-xbe interim; not VC71",
            }
        )

    out = Path(args.json_out)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(rows, indent=2) + "\n")
    print(f"\nwrote {out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
