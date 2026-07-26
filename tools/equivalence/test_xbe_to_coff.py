#!/usr/bin/env python3
"""Smoke tests for xbe_to_coff synthesizer (requires halo-patched/cachebeta.xbe)."""
from __future__ import annotations

import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
_EQ = Path(__file__).resolve().parent
if str(_EQ) not in sys.path:
    sys.path.insert(0, str(_EQ))

from xbe import Xbe  # noqa: E402

from coff_loader import extract_function, list_functions, load_coff  # noqa: E402
from xbe_to_coff import (  # noqa: E402
    DEFAULT_KB,
    DEFAULT_XBE,
    load_kb,
    synthesize_function,
    write_obj,
)

REF_LEAF = ROOT / "delinked" / "functions" / "00193a80.obj"


@unittest.skipUnless(DEFAULT_XBE.exists(), "cachebeta.xbe not present")
@unittest.skipUnless(DEFAULT_KB.exists(), "kb.json not present")
class TestXbeToCoff(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.xbe = Xbe.from_file(str(DEFAULT_XBE))
        cls.by_addr, cls.sorted_addrs = load_kb(DEFAULT_KB)

    def test_leaf_193a80_matches_existing_oracle(self) -> None:
        self.assertTrue(REF_LEAF.exists(), "reference delinked obj missing")
        result = synthesize_function(
            self.xbe, 0x193A80, self.by_addr, self.sorted_addrs
        )
        self.assertEqual(result.name, "FUN_00193a80")
        self.assertEqual(len(result.code), 119)
        self.assertEqual(result.relocs, [])

        out = ROOT / "delinked" / "functions" / "_test_00193a80.obj"
        try:
            write_obj(result, out)
            load_coff(str(out))
            sl = extract_function(str(out), "FUN_00193a80")
            self.assertEqual(len(sl.code), 119)
            ref = extract_function(str(REF_LEAF), "FUN_00193a80")
            self.assertEqual(sl.code, ref.code)
        finally:
            if out.exists():
                out.unlink()

    def test_reloc_rich_18e3c0_roundtrip(self) -> None:
        result = synthesize_function(
            self.xbe, 0x18E3C0, self.by_addr, self.sorted_addrs
        )
        self.assertEqual(result.name, "scenario_get")
        self.assertEqual(len(result.code), 47)
        self.assertEqual(len(result.relocs), 6)

        out = ROOT / "delinked" / "functions" / "_test_0018e3c0.obj"
        try:
            write_obj(result, out)
            funcs = list_functions(str(out))
            self.assertEqual(funcs, ["scenario_get"])
            sl = extract_function(str(out), "scenario_get")
            self.assertEqual(len(sl.code), 47)
            self.assertEqual(len(sl.relocs), 6)
            ref = extract_function(
                str(ROOT / "delinked" / "functions" / "0018e3c0.obj"),
                "scenario_get",
            )
            self.assertEqual(sl.code, ref.code)
            self.assertEqual(
                [r.virtual_address for r in sl.relocs],
                [r.virtual_address for r in ref.relocs],
            )
        finally:
            if out.exists():
                out.unlink()


if __name__ == "__main__":
    unittest.main()
