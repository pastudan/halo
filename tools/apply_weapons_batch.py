#!/usr/bin/env python3
"""Mark all remaining weapons.obj drafts; update kb + deactivation allowlist."""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from gen_weapons_unset_impl import DECLS  # noqa: E402

OBJECT = "weapons.obj"


def main() -> None:
    kb = json.loads((ROOT / "kb.json").read_text())
    obj = next(o for o in kb["objects"] if o["name"] == OBJECT)
    for addr, decl in DECLS.items():
        for f in obj["functions"]:
            if f["addr"] == addr:
                f["decl"] = decl
                f["ported"] = False
                break

    for addr, decl in {
        "0x1d9e70": "float FUN_001d9e70(float base, float exponent);",
        "0x220c0": "void actor_aim_projectile(float *origin, float *direction, int unit_handle);",
    }.items():
        for o in kb["objects"]:
            for f in o["functions"]:
                if f["addr"] == addr:
                    f["decl"] = decl
                    break

    al_path = ROOT / "tools/audit/deactivation_allowlist.json"
    al = json.loads(al_path.read_text())
    have_al = {e["addr"] for e in al if isinstance(e, dict)}
    for addr, decl in DECLS.items():
        if addr in have_al:
            continue
        name = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", decl).group(1)
        al.append(
            {
                "addr": addr,
                "name": name,
                "object": OBJECT,
                "reason": "draft lift pending VC71/equivalence — keep inactive until scored",
                "since": "2026-07-25",
            }
        )
    al_path.write_text(json.dumps(al, indent=2) + "\n")

    (ROOT / "kb.json").write_text(json.dumps(kb, indent=2) + "\n")
    print("kb+allowlist updated for", len(DECLS), "weapons drafts")


if __name__ == "__main__":
    main()
