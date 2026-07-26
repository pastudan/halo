#!/usr/bin/env python3
"""Relift all modules with empty stubs, then verify docker build + raw-cast 403."""
from __future__ import annotations

import importlib.util
import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def load(name: str, path: Path):
    spec = importlib.util.spec_from_file_location(name, path)
    mod = importlib.util.module_from_spec(spec)
    sys.modules[name] = mod
    assert spec.loader is not None
    spec.loader.exec_module(mod)
    return mod


def stub_count() -> int:
    proc = subprocess.run(
        [sys.executable, "tools/audit_empty_stubs.py", "--count"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    return int(proc.stdout.strip() or "0")


def modules_with_stubs() -> list[tuple[int, str, int]]:
    gen = load("gen", ROOT / "tools/gen_module_draft_batch.py")
    relift = load("rel", ROOT / "tools/relift_stubs_from_xbe.py")
    kb = json.loads((ROOT / "kb.json").read_text())
    out: list[tuple[int, str, int]] = []
    for idx, obj in enumerate(kb["objects"]):
        on = obj.get("name") or ""
        src_rel = obj.get("source")
        if not src_rel:
            continue
        src_path = ROOT / "src" / "halo" / src_rel
        if not src_path.is_file():
            continue
        text = src_path.read_text()
        n = 0
        for f in obj.get("functions", []):
            if f.get("ported") is not False:
                continue
            addr = f["addr"].lower()
            name = gen.fn_name(f.get("decl") or "", addr)
            span = relift.find_function_def_for_addr(text, name, addr)
            if span is None:
                n += 1
                continue
            if relift.is_stub_body(text[span[1] : span[2]]):
                n += 1
        if n:
            same = [i for i, o in enumerate(kb["objects"]) if o.get("name") == on]
            occ = same.index(idx)
            out.append((n, on, occ))
    return sorted(out)


def relift_module(on: str, occ: int) -> int:
    cmd = [sys.executable, "tools/relift_stubs_from_xbe.py", "--object", on]
    if occ:
        cmd.extend(["--occurrence", str(occ)])
    proc = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
    if proc.returncode != 0:
        print(proc.stdout, proc.stderr, file=sys.stderr)
        raise SystemExit(f"relift failed: {on}[{occ}]")
    m = re.search(r"relifted (\d+)", proc.stdout)
    return int(m.group(1)) if m else 0


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
    m = re.search(r"raw-cast count: (\d+)", out)
    raw = int(m.group(1)) if m else None
    ok = proc.returncode == 0 and raw == 403
    return ok, out


def main() -> None:
    before = stub_count()
    print(f"wave start: {before} stubs")
    total = 0
    for n, on, occ in modules_with_stubs():
        label = f"{on}[{occ}]" if occ else on
        lifted = relift_module(on, occ)
        if lifted:
            print(f"  {label}: relifted {lifted}/{n}")
            total += lifted
    after = stub_count()
    print(f"relifted {total}, stubs {before} -> {after}")
    ok, out = docker_build()
    if not ok:
        print(out[-6000:], file=sys.stderr)
        raise SystemExit("build failed")
    print("\n".join(out.strip().splitlines()[-3:]))


if __name__ == "__main__":
    main()
