#!/usr/bin/env python3
"""Apply ai_communication.obj batch1 drafts to kb + allowlist."""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OBJECT = "ai_communication.obj"

DECLS = {
    "0x42cb0": "const char *ai_communication_get_type_name(int16_t type);",
    "0x42ce0": "int16_t ai_communication_get_type_by_name(const char *name);",
    "0x42d20": "void ai_communication_packet_new(void *packet);",
    "0x42d80": "char FUN_00042d80(int actor, int unit, int prop);",
    "0x42df0": "char FUN_00042df0(int actor, int unit, int prop);",
    "0x42e60": "char FUN_00042e60(int actor, int unit, int prop);",
    "0x42eb0": "char FUN_00042eb0(int actor, int unit, int prop);",
    "0x42f40": "char FUN_00042f40(int a, int b, int actor);",
    "0x42f60": "char FUN_00042f60(int actor, int unit, int prop);",
    "0x42fa0": "char FUN_00042fa0(int actor, int unit, int prop);",
    "0x43050": "char FUN_00043050(int actor, int unit, int prop);",
    "0x43090": "char FUN_00043090(int actor, int unit, int prop);",
    "0x43270": "int actor_communication_team(int actor);",
    "0x434c0": "int16_t ai_conversation_line(int conversation_index);",
    "0x44500": "void ai_conversation_stop(int conversation_index);",
    "0x44590": "void ai_conversation_actor_deleted(int actor_handle);",
}

HELPER_DECLS = {
    "0x3b120": "char FUN_0003b120(int actor);",
    "0x435b0": "void ai_conversation_finish(int handle, int a, int b);",
    "0x3b150": "char actor_is_fighting(int actor);",
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
                "since": "2026-07-26",
            }
        )
    al_path.write_text(json.dumps(al, indent=2) + "\n")
    (ROOT / "kb.json").write_text(json.dumps(kb, indent=2) + "\n")
    print("kb+allowlist updated for", len(DECLS), "ai_communication batch1 drafts")


if __name__ == "__main__":
    main()
