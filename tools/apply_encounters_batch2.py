#!/usr/bin/env python3
"""Mark encounters.obj batch2 drafts; update kb + deactivation allowlist."""
from __future__ import annotations

import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OBJECT = "encounters.obj"

DECLS: dict[str, str] = {
    "0x59c40": "int FUN_00059c40(int encounter_handle, int16_t pursuit_index, int min_time, char create);",
    "0x59d30": "void encounter_modify_pursuit_desires(int encounter_handle, int16_t profile_index, char *flag, int16_t *a, int16_t *b, int16_t *c, int16_t *d, char *e);",
    "0x566a0": "void encounters_initialize(int16_t team_a, int16_t team_b);",
    "0x5b6e0": "char encounter_pursuit_position_already_examined(int encounter_handle, int position_hash, int16_t pursuit_index, int min_time, int16_t *out_count, int *out_time);",
    "0x5b5e0": "char encounter_mark_examined_pursuit_position(int encounter_handle, int position_hash, int16_t pursuit_index, int min_time);",
}


def main() -> None:
    kb = json.loads((ROOT / "kb.json").read_text())
    obj = next(o for o in kb["objects"] if o["name"] == OBJECT)
    for addr, decl in DECLS.items():
        for f in obj["functions"]:
            if f["addr"] == addr:
                f["decl"] = decl
                f["ported"] = False
                break
    (ROOT / "kb.json").write_text(json.dumps(kb, indent=2) + "\n")

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
    print("kb+allowlist updated for", len(DECLS), "encounters drafts")


if __name__ == "__main__":
    main()
