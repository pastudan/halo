#!/usr/bin/env python3
"""Mark all remaining encounters.obj drafts; update kb + deactivation allowlist."""
from __future__ import annotations

import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OBJECT = "encounters.obj"

DECLS: dict[str, str] = {
    "0x53c50": "void FUN_00053c50(void);",
    "0x53f40": "short FUN_00053f40(float *weights, short stride, short count, short weight_offset, int *bitvector);",
    "0x564b0": "void FUN_000564b0(int encounter_handle, int team_index);",
    "0x565c0": "void FUN_000565c0(int encounter_handle, int team_index, int side_name);",
    "0x57380": "short FUN_00057380(int unit_handle);",
    "0x57d00": "void FUN_00057d00(int unit_handle, int encounter_index, int16_t profile_index);",
    "0x58af0": "void FUN_00058af0(int actor_handle, int vehicle_handle, void *seat_list, char require_pilot);",
    "0x58c40": "void FUN_00058c40(int encounter_handle, int actor_handle, int seat_list);",
    "0x58fd0": "void FUN_00058fd0(int encounter_handle, char update_actor_visibility, int cluster_count, int pvs, char *out_cluster_bv);",
    "0x59dd0": "void encounter_determine_pursuit_availability(int encounter_handle, int actor_handle, int16_t *mode, char flag, char *out_guard, char *out_active, char *out_limit_a, char *out_limit_b, char *out_nearby, char *out_has_target, char *out_summary);",
    "0x5b370": "void encounter_verify_firing_position_owner_actor_indices(int encounter_handle);",
    "0x5b4b0": "void encounter_build_firing_position_owner_actor_indices(int encounter_handle, int *firing_position_owner_actor_indices);",
    "0x5b790": "char FUN_0005B790(int encounter_handle, int16_t squad_index, int flag);",
    "0x5bad0": "int16_t encounter_post_combat_select_random_behavior(void *samples, int *out);",
    "0x5bbe0": "void FUN_0005bbe0(int encounter_handle);",
    "0x5c3a0": "char encounter_get_actor_starting_location(int16_t profile_index, int delay, int flag, int encounter_handle);",
    "0x5c510": "char encounter_spawn_actor(int encounter_handle, int16_t squad_index);",
    "0x5c680": "void FUN_0005c680(int encounter_handle);",
    "0x5ca80": "void FUN_0005ca80(int encounter_handle);",
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
