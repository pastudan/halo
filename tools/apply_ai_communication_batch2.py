#!/usr/bin/env python3
"""Apply ai_communication.obj batch2 drafts to kb + allowlist."""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from gen_ai_communication_batch2 import DECLS  # noqa: E402

OBJECT = "ai_communication.obj"

HELPER_DECLS = {
    "0x3b120": "char FUN_0003b120(int actor);",
    "0x3a770": "int16_t FUN_0003a770(int16_t actor_type);",
    "0x64b40": "int FUN_00064b40(int a, int b, int c, int d);",
    "0x3b150": "char actor_is_fighting(int actor);",
    "0x27a60": "int FUN_00027a60(int actor_handle, short look_type, short priority, short *look_buf);",
    "0x1a6ca0": "char *FUN_001a6ca0(short param_1);",
    "0x1a6ef0": "void FUN_001a6ef0(int actor, short count, void *comm_buf);",
    "0x1a67b0": "char *FUN_001a67b0(short param_1, unsigned char param_2);",
    "0x1a9200": "void unit_get_head_position(int object_handle, float *out_position);",
    "0x64ab0": "int prop_get_active_by_unit_index(int actor_handle, int object_handle);",
    "0x13d640": "void *object_try_and_get_and_verify_type(int datum_handle, int type_mask);",
    "0x1c7f80": "void scripted_sound_new(int a0, int a1, float a2);",
    "0x1c7500": "int scripted_sound_time(int a0);",
    "0x1cb990": "char sound_scripted_dialog_is_playing(void);",
    "0x121a0": "float distance_squared3d(const float *a, const float *b);",
    "0x1ba1f0": "const char *tag_get_name(int tag_index);",
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

    for addr, decl in HELPER_DECLS.items():
        for o in kb["objects"]:
            for f in o.get("functions", []):
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
                "since": "2026-07-26",
            }
        )
    al_path.write_text(json.dumps(al, indent=2) + "\n")
    (ROOT / "kb.json").write_text(json.dumps(kb, indent=2) + "\n")
    print("kb+allowlist updated for", len(DECLS), "ai_communication batch2 drafts")


if __name__ == "__main__":
    main()
