#!/usr/bin/env python3
"""List empty ported:false stubs with reason."""
from __future__ import annotations

import importlib.util
import json
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


def audit_stubs(*, count_only: bool = False) -> int | None:
    gen = load("gen_module_draft_batch", ROOT / "tools" / "gen_module_draft_batch.py")
    relift = load("relift_stubs_from_xbe", ROOT / "tools" / "relift_stubs_from_xbe.py")
    kb = json.loads((ROOT / "kb.json").read_text())
    cache: dict[Path, str] = {}
    count = 0
    for obj in kb["objects"]:
        on = obj.get("name") or ""
        src_rel = obj.get("source")
        if not src_rel:
            continue
        src_path = ROOT / "src" / "halo" / src_rel
        if not src_path.is_file():
            continue
        if src_path not in cache:
            cache[src_path] = src_path.read_text()
        text = cache[src_path]
        for f in obj.get("functions", []):
            if f.get("ported") is not False:
                continue
            addr = f["addr"].lower()
            name = gen.fn_name(f.get("decl") or "", addr)
            span = relift.find_function_def_for_addr(text, name, addr)
            if span is None:
                if not count_only:
                    print(f"{on}\t{name}\t{addr}\tNO_DEF")
                else:
                    count += 1
                continue
            _, bs, be = span
            body = text[bs:be]
            if relift.is_stub_body(body):
                if count_only:
                    count += 1
                else:
                    print(f"{on}\t{name}\t{addr}\tSTUB\t{body.strip()[:60]!r}")
            elif not count_only and relift.is_relift_draft(body):
                print(f"{on}\t{name}\t{addr}\tDRAFT")
    return count if count_only else None


def main() -> None:
    import argparse

    ap = argparse.ArgumentParser()
    ap.add_argument("--count", action="store_true", help="Print stub+NO_DEF count only")
    args = ap.parse_args()
    if args.count:
        print(audit_stubs(count_only=True))
        return
    audit_stubs(count_only=False)


if __name__ == "__main__":
    main()
