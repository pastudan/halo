#!/usr/bin/env python3
"""Relift every module with empty stubs; build after each."""
from __future__ import annotations

import json
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def load_modules():
    import importlib.util

    spec = importlib.util.spec_from_file_location(
        "gen_module_draft_batch", ROOT / "tools" / "gen_module_draft_batch.py"
    )
    gen = importlib.util.module_from_spec(spec)
    sys.modules["gen_module_draft_batch"] = gen
    assert spec.loader is not None
    spec.loader.exec_module(gen)

    spec2 = importlib.util.spec_from_file_location(
        "relift_stubs_from_xbe", ROOT / "tools" / "relift_stubs_from_xbe.py"
    )
    relift = importlib.util.module_from_spec(spec2)
    sys.modules["relift_stubs_from_xbe"] = relift
    assert spec2.loader is not None
    spec2.loader.exec_module(relift)
    return gen, relift


def stub_count_obj(obj: dict, gen, relift) -> int:
    src_rel = obj.get("source")
    if not src_rel:
        return 0
    src_path = ROOT / "src" / "halo" / src_rel
    if not src_path.is_file():
        return 0
    text = src_path.read_text()
    n = 0
    for f in obj.get("functions", []):
        if f.get("ported") is not False:
            continue
        addr = f["addr"].lower()
        name = gen.fn_name(f.get("decl") or "", addr)
        span = relift.find_function_def_for_addr(text, name, addr)
        if span is None:
            span = relift.find_function_def(text, name)
        if span is None:
            n += 1
            continue
        _, bs, be = span
        if relift.is_stub_body(text[bs:be]):
            n += 1
    return n


def main() -> None:
    gen, relift = load_modules()
    kb = json.loads((ROOT / "kb.json").read_text())
    jobs: list[tuple[str, int, int]] = []
    for occ, obj in enumerate(kb["objects"]):
        n = stub_count_obj(obj, gen, relift)
        if n:
            jobs.append((obj["name"], sum(1 for o in kb["objects"][: occ + 1] if o["name"] == obj["name"]) - 1, n))
    # fix occurrence index properly
    seen: dict[str, int] = {}
    jobs = []
    for obj in kb["objects"]:
        on = obj["name"]
        occ = seen.get(on, 0)
        seen[on] = occ + 1
        n = stub_count_obj(obj, gen, relift)
        if n:
            jobs.append((on, occ, n))
    jobs.sort(key=lambda x: x[2])

    for on, occ, n in jobs:
        label = on if occ == 0 else f"{on}[{occ}]"
        print(f"\n=== {label} ({n} stubs) ===")
        proc = subprocess.run(
            [
                sys.executable,
                "tools/relift_module_build.py",
                "--object",
                on,
                "--occurrence",
                str(occ),
            ],
            cwd=ROOT,
        )
        if proc.returncode != 0:
            raise SystemExit(f"failed on {label}")

    proc = subprocess.run(
        [sys.executable, "tools/audit_empty_stubs.py"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    left = len([ln for ln in proc.stdout.splitlines() if "\tSTUB\t" in ln or "\tNO_DEF\t" in ln])
    print(f"\nFINAL empty stubs: {left}")


if __name__ == "__main__":
    main()
