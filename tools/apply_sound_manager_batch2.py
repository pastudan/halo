#!/usr/bin/env python3
"""Apply sound_manager.obj batch2 drafts to kb + allowlist."""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from gen_sound_manager_batch2 import DECLS  # noqa: E402

OBJECT = "sound_manager.obj"

HELPER_DECLS = {
    "0x1cb0c0": "void FUN_001cb0c0(int channel);",
    "0x1cadd0": "void FUN_001cadd0(int a, int b, int c, int d, int e, int f);",
    "0x1ca2b0": "void FUN_001ca2b0(void *buf);",
}

XDK_STUB_DECLS = {
    "0x2038df": "void FUN_002038df(void);",
    "0x204c79": "void FUN_00204c79(int *caps, void *driver);",
    "0x204c5d": "int FUN_00204c5d(void *driver, int *wf);",
    "0x204c95": "int FUN_00204c95(void *driver, void *guid, int a, int *b, int *c);",
    "0x204d41": "void FUN_00204d41(void *driver, int a, int b);",
    "0x204d81": "int FUN_00204d81(void *driver, int pri);",
    "0x204e48": "int FUN_00204e48(void *driver, float vol);",
    "0x2052de": "void FUN_002052de(void *channel, int a, void *data);",
    "0x205bd8": "void FUN_00205bd8(void *channel, int a, void *data);",
    "0x2060f8": "int FUN_002060f8(int a, void *b, void *c, void *d);",
    "0x206232": "int FUN_00206232(void *driver, int a, int b);",
}


def main() -> None:
    kb = json.loads((ROOT / "kb.json").read_text())
    obj = next(o for o in kb["objects"] if o["name"] == OBJECT)
    for addr, decl in DECLS.items():
        for f in obj["functions"]:
            if f["addr"] == addr:
                f["decl"] = decl
                if addr not in ("0x1ccbe0", "0x1ccca0"):
                    f["ported"] = False
                break

    for addr, decl in HELPER_DECLS.items():
        for o in kb["objects"]:
            for f in o["functions"]:
                if f["addr"] == addr:
                    f["decl"] = decl
                    break

    xdk = next(o for o in kb["objects"] if o["name"] == "<xdk_stubs>")
    have_xdk = {f["addr"] for f in xdk["functions"]}
    for addr, decl in XDK_STUB_DECLS.items():
        if addr in have_xdk:
            for f in xdk["functions"]:
                if f["addr"] == addr:
                    f["decl"] = decl
                    break
        else:
            xdk["functions"].append({"addr": addr, "decl": decl, "ported": True})

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
    print("kb+allowlist updated for", len(DECLS), "sound_manager batch2 drafts")


if __name__ == "__main__":
    main()
