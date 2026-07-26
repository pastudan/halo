#!/usr/bin/env python3
"""Apply recorded_animations.obj batch2 drafts to kb + allowlist."""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

OBJECT = "recorded_animations.obj"

DECLS = {
    "0x942a0": "void FUN_000942a0(char *out, void *event, int **stream);",
    "0x94350": "void FUN_00094350(char *out, void *event, int **stream);",
    "0x94400": "void FUN_00094400(char *out, void *event, int **stream);",
    "0x944b0": "void FUN_000944b0(char *out, void *event, int **stream);",
    "0x94560": "void FUN_00094560(char *out, void *event, int **stream);",
    "0x94620": "void apply_facing_vector(char *thread, void *event, int **stream);",
    "0x946e0": "void apply_aiming_vector(char *thread, void *event, int **stream);",
    "0x947a0": "void apply_looking_vector(char *thread, void *event, int **stream);",
    "0x94860": "void apply_angle_vector(char *thread, void *event, int **stream);",
    "0x94970": "void apply_multi_vector(char *thread, void *event, int **stream);",
    "0x94a90": "char recorded_animation_apply_event_stream_v1(char *thread, void *event, int *ticks, int **cursor);",
    "0x94ee0": "void recorded_animation_verify(char *anim);",
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
    print("kb+allowlist updated for", len(DECLS), "recorded_animations batch2 drafts")


if __name__ == "__main__":
    main()
