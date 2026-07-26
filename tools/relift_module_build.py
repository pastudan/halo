#!/usr/bin/env python3
"""Relift one kb module entry and verify docker build + raw-cast baseline."""
from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def docker_build() -> tuple[bool, str]:
    cmd = [
        "docker",
        "run",
        "--rm",
        "-u",
        f"{__import__('os').getuid()}:{__import__('os').getgid()}",
        "-v",
        f"{ROOT}:/work",
        "-w",
        "/work",
        "halo-re-build:latest",
        "bash",
        "-c",
        "cmake --build build --target halo --parallel 2>&1",
    ]
    proc = subprocess.run(cmd, capture_output=True, text=True)
    out = proc.stdout + proc.stderr
    ok = proc.returncode == 0
    m = re.search(r"raw-cast count: (\d+)", out)
    raw = int(m.group(1)) if m else None
    if ok and raw != 403:
        ok = False
        out += f"\nFAIL: raw-cast {raw} != 403\n"
    return ok, out


def relift(object_name: str, occurrence: int = 0) -> int:
    cmd = [
        sys.executable,
        "tools/relift_stubs_from_xbe.py",
        "--object",
        object_name,
        "--occurrence",
        str(occurrence),
    ]
    proc = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
    print(proc.stdout, end="")
    if proc.returncode != 0:
        print(proc.stderr, file=sys.stderr)
        raise SystemExit(proc.returncode)
    m = re.search(r"relifted (\d+)", proc.stdout)
    return int(m.group(1)) if m else 0


def stub_count() -> int:
    proc = subprocess.run(
        [sys.executable, "tools/audit_empty_stubs.py", "--count"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    return int(proc.stdout.strip() or "0")


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--object", required=True)
    ap.add_argument("--occurrence", type=int, default=0)
    ap.add_argument("--skip-build", action="store_true")
    args = ap.parse_args()

    label = args.object
    if args.occurrence:
        label = f"{label}[{args.occurrence}]"
    before = stub_count()
    n = relift(args.object, args.occurrence)
    after = stub_count()
    print(f"{label}: relifted {n}, stubs {before} -> {after}")
    if n == 0 or args.skip_build:
        return
    ok, out = docker_build()
    if not ok:
        print(out[-4000:], file=sys.stderr)
        raise SystemExit("build failed")
    tail = "\n".join(out.strip().splitlines()[-4:])
    print(tail)


if __name__ == "__main__":
    main()
