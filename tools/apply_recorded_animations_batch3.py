#!/usr/bin/env python3
"""Apply recorded_animations.obj batch3 drafts to kb + allowlist."""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

OBJECT = "recorded_animations.obj"

DECLS = {
    "0x940a0": "char FUN_000940a0(char *thread, void *event, int *ticks, int **cursor);",
    "0x950b0": "void render_debug_recording(void);",
    "0x95330": "char recorded_animation_play_internal(int unit@<eax>, int anim, int flags);",
    "0x957c0": "void control_toggle(int object@<ebx>);",
    "0x95c60": "char FUN_00095c60(int object);",
}


HELPER_DECLS = {
    "0x967a0": "void FUN_000967a0(void *rec, int object);",
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
    print("kb+allowlist updated for", len(DECLS), "recorded_animations batch3 drafts")


if __name__ == "__main__":
    main()
