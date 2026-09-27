#!/usr/bin/env python3
"""Compare engine.wasm raycasts against golden fixtures (when present)."""
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
FIX = Path(__file__).resolve().parent / "golden" / "fixtures"
WASM = ROOT / "web" / "public" / "engine.wasm"


def main():
    rays = FIX / "rays.jsonl"
    if not rays.exists() or rays.stat().st_size == 0:
        print("golden: no ray fixtures yet — skip")
        return 0
    if not WASM.exists():
        print("golden: engine.wasm missing; run engine/build.sh", file=sys.stderr)
        return 1
    # Full wasmtime binding is optional; for now just validate JSONL shape.
    n = 0
    for line in rays.read_text().splitlines():
        line = line.strip()
        if not line:
            continue
        row = json.loads(line)
        assert "o" in row and "d" in row and "t" in row
        n += 1
    print(f"golden: {n} ray fixtures validated (execution needs wasmtime — TODO)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
