#!/usr/bin/env python3
"""Mark encounters.obj batch1 drafts; update kb + deactivation allowlist."""
from __future__ import annotations

import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OBJECT = "encounters.obj"

DECLS: dict[str, str] = {
    "0x57330": "int FUN_00057330(int16_t command_index, char *state);",
    "0x5c630": "void encounter_set_respawn(int encounter_handle, char flag);",
    "0x53bf0": "void FUN_00053bf0(void);",
    "0x53b80": "void FUN_00053b80(void);",
    "0x53e80": "int FUN_00053e80(void *ai_profile_element, const char *name);",
    "0x53ee0": "int FUN_00053ee0(void *encounter_def, const char *name);",
    "0x57b40": "int FUN_00057b40(int actor_handle);",
    "0x5ac60": "char FUN_0005ac60(int *samples, int score, float y, float x, float z);",
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
