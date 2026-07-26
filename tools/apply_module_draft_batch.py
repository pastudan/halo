#!/usr/bin/env python3
"""Apply module draft batch to kb + deactivation allowlist."""
from __future__ import annotations

import argparse
import importlib.util
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def slug(name: str) -> str:
    return re.sub(r"[^a-z0-9]+", "_", name.replace(".obj", "").lower()).strip("_")


def load_decls(object_name: str) -> dict[str, str]:
    spec_path = ROOT / "tools" / "gen_module_draft_batch.py"
    spec = importlib.util.spec_from_file_location("gen_module_draft_batch", spec_path)
    mod = importlib.util.module_from_spec(spec)
    assert spec.loader is not None
    spec.loader.exec_module(mod)
    return mod.load_decls(object_name)  # type: ignore[attr-defined]


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--object", required=True)
    args = ap.parse_args()
    object_name = args.object
    decls = load_decls(object_name)

    kb = json.loads((ROOT / "kb.json").read_text())
    obj = next(o for o in kb["objects"] if o["name"] == object_name)
    for addr, decl in decls.items():
        for f in obj["functions"]:
            if f["addr"].lower() == addr:
                f["decl"] = decl
                f["ported"] = False
                break

    al_path = ROOT / "tools/audit/deactivation_allowlist.json"
    al = json.loads(al_path.read_text())
    have_al = {e["addr"].lower() for e in al if isinstance(e, dict)}
    for addr, decl in decls.items():
        if addr.lower() in have_al:
            continue
        name = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", decl).group(1)
        al.append(
            {
                "addr": addr,
                "name": name,
                "object": object_name,
                "reason": "draft lift pending VC71/equivalence — keep inactive until scored",
                "since": "2026-07-26",
            }
        )
    al_path.write_text(json.dumps(al, indent=2) + "\n")
    (ROOT / "kb.json").write_text(json.dumps(kb, indent=2) + "\n")
    print(f"kb+allowlist updated for {len(decls)} {object_name} drafts")


if __name__ == "__main__":
    main()
