#!/usr/bin/env python3
"""Relift empty ported:false stubs across all kb objects."""
from __future__ import annotations

import argparse
import importlib.util
import json
import re
import subprocess
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def load_gen():
    spec = importlib.util.spec_from_file_location(
        "gen_module_draft_batch", ROOT / "tools" / "gen_module_draft_batch.py"
    )
    gen = importlib.util.module_from_spec(spec)
    sys.modules["gen_module_draft_batch"] = gen
    assert spec.loader is not None
    spec.loader.exec_module(gen)
    return gen


def relift_module():
    spec = importlib.util.spec_from_file_location(
        "relift_stubs_from_xbe", ROOT / "tools" / "relift_stubs_from_xbe.py"
    )
    relift = importlib.util.module_from_spec(spec)
    sys.modules["relift_stubs_from_xbe"] = relift
    assert spec.loader is not None
    spec.loader.exec_module(relift)
    return relift


def load_modules():
    return load_gen(), relift_module()


def empty_stub_objects(force: bool = False) -> list[str]:
    gen, relift = load_modules()
    kb = json.loads((ROOT / "kb.json").read_text())
    counts: Counter[str] = Counter()
    for obj in kb["objects"]:
        on = obj.get("name") or ""
        src_rel = obj.get("source")
        if not src_rel:
            continue
        src_path = ROOT / "src" / "halo" / src_rel
        if not src_path.is_file():
            continue
        text = src_path.read_text()
        for f in obj.get("functions", []):
            if f.get("ported") is not False:
                continue
            addr = f["addr"].lower()
            name = gen.fn_name(f.get("decl") or "", addr)
            span = relift.find_function_def(text, name)
            if span is None:
                counts[on] += 1
                continue
            _, bs, be = span
            body = text[bs:be]
            if relift.is_stub_body(body) or (force and relift.is_relift_draft(body)):
                counts[on] += 1
    return [o for o, _ in counts.most_common()]


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--force", action="store_true")
    ap.add_argument("--object", action="append")
    args = ap.parse_args()

    objects = args.object if args.object else empty_stub_objects(force=args.force)
    if args.list:
        gen, relift = load_modules()
        kb = json.loads((ROOT / "kb.json").read_text())
        total = 0
        rows = []
        for on in objects:
            obj = next(o for o in kb["objects"] if o.get("name") == on)
            src_path = ROOT / "src" / "halo" / obj["source"]
            text = src_path.read_text() if src_path.is_file() else ""
            n = 0
            for f in obj.get("functions", []):
                if f.get("ported") is not False:
                    continue
                name = gen.fn_name(f.get("decl") or "", f["addr"].lower())
                span = relift.find_function_def(text, name) if text else None
                if span is None:
                    n += 1
                    continue
                _, bs, be = span
                body = text[bs:be]
                if relift.is_stub_body(body) or (
                    args.force and relift.is_relift_draft(body)
                ):
                    n += 1
            if n:
                rows.append((on, n))
                total += n
        for on, n in sorted(rows, key=lambda x: -x[1])[:40]:
            print(f"  {on}: {n}")
        print(f"TOTAL empty: {total} across {len(rows)} objects")
        return

    total = 0
    for on in objects:
        cmd = [sys.executable, "tools/relift_stubs_from_xbe.py", "--object", on]
        if args.force:
            cmd.append("--force")
        proc = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
        if proc.returncode != 0:
            print(proc.stdout, proc.stderr, file=sys.stderr)
            raise SystemExit(proc.returncode)
        m = re.search(r"relifted (\d+)", proc.stdout)
        n = int(m.group(1)) if m else 0
        if n:
            print(proc.stdout.strip())
        total += n
    print(f"TOTAL relifted: {total}")


if __name__ == "__main__":
    main()
