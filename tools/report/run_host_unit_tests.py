#!/usr/bin/env python3
"""Run host-side unit tests that do not require Xbox/XBE/self-hosted hardware."""
from __future__ import annotations

import argparse
import os
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

# Modules that are pure host contracts (no cachebeta.xbe / xemu / RXDK).
DEFAULT_MODULES = [
    "tools.xbox.test_symbolize_exception",
    "tools.xbox.test_verify_toggles_live",
    "tools.verify.test_persistent_storage_crc",
    "tools.verify.test_inventory",
    "tools.verify.test_periodic_tables",
    "tools.audit.test_patch",
    "tools.memory.test_skill_router_hook",
    "tools.equivalence.test_game_state_diff",
    "tools.equivalence.test_stub_arg_trace",
    "tools.equivalence.test_value_corpus",
    "tools.equivalence.test_ab_check",
]


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument(
        "--with-pytest-modules",
        action="store_true",
        help="Also load pytest-style modules (requires pytest installed)",
    )
    ap.add_argument("-v", "--verbose", action="store_true")
    args = ap.parse_args()

    os.chdir(ROOT)
    if str(ROOT) not in sys.path:
        sys.path.insert(0, str(ROOT))

    modules = list(DEFAULT_MODULES)
    if args.with_pytest_modules:
        modules.append("tools.test_llm_auto_lift_enrichment")

    loader = unittest.TestLoader()
    suite = unittest.TestSuite()
    for name in modules:
        suite.addTests(loader.loadTestsFromName(name))

    # Optional discover under tools/audit/tests (skips if empty/missing).
    audit_tests = ROOT / "tools" / "audit" / "tests"
    if audit_tests.is_dir():
        suite.addTests(loader.discover(str(audit_tests), pattern="test_*.py"))

    result = unittest.TextTestRunner(verbosity=2 if args.verbose else 1).run(suite)
    print(
        f"\nHost unit tests: ran={result.testsRun} "
        f"failures={len(result.failures)} errors={len(result.errors)} "
        f"skipped={len(result.skipped)}"
    )
    return 0 if result.wasSuccessful() else 1


if __name__ == "__main__":
    raise SystemExit(main())
