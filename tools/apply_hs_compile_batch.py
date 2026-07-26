#!/usr/bin/env python3
"""Mark hs_compile.obj final 10 drafts; update kb decls + deactivation allowlist."""
from __future__ import annotations

import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OBJECT = "hs_compile.obj"

DECLS: dict[str, str] = {
    "0xc5f60": "bool hs_parse_enum(int datum_index);",
    "0xc66d0": "bool FUN_000c66d0(int datum_index);",
    "0xc6940": "bool FUN_000c6940(int datum_index);",
    "0xc6a30": "int16_t FUN_000c6a30(const char *str, const char **names, int16_t count);",
    "0xc7e50": "char hs_macro_function_parse(int16_t function_index, int root_datum);",
    "0xc7f70": "char hs_parse_begin(int16_t function_index, int root_datum);",
    "0xc8120": "char hs_parse_if(int16_t function_index, int root_datum);",
    "0xc82e0": "char hs_parse_cond(int16_t function_index, int root_datum);",
    "0xc8380": "char hs_parse_set(int16_t function_index, int root_datum);",
    "0xc85b0": "char FUN_000c85b0(int16_t function_index, int root_datum);",
}


def main() -> None:
    kb = json.loads((ROOT / "kb.json").read_text())
    hs = next(o for o in kb["objects"] if o["name"] == OBJECT)
    for addr, decl in DECLS.items():
        for f in hs["functions"]:
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
    print("kb+allowlist updated for", len(DECLS), "hs_compile drafts")


if __name__ == "__main__":
    main()
