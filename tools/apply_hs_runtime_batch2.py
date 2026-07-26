#!/usr/bin/env python3
"""Append hs_runtime batch2 drafts; update kb decls + deactivation allowlist."""
from __future__ import annotations

import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OBJECT = "hs_runtime.obj"
DRAFT = ROOT / "artifacts/hs_runtime_batch2_draft.c"

DECLS: dict[str, str] = {
    "0xc8b90": "char FUN_000c8b90(int16_t node_type, int datum_index);",
    "0xc8e00": "char FUN_000c8e00(int16_t function_index, int root_datum);",
    "0xc8ec0": "char FUN_000c8ec0(int16_t function_index, int root_datum);",
    "0xc95f0": "int FUN_000c95f0(void);",
    "0xc9650": "char FUN_000c9650(int16_t game_flag, int list_handle, char set_flag);",
    "0xc9700": "char FUN_000c9700(int object_handle, int unused, float distance);",
    "0xc9770": "char FUN_000c9770(int list_handle, int param, float distance);",
    "0xc97f0": "void FUN_000c97f0(int object_handle, int16_t scenario_index, float distance);",
    "0xc9840": "char FUN_000c9840(int list_handle, int16_t scenario_index, float distance);",
    "0xc9a50": "void FUN_000c9a50(void);",
    "0xc9bd0": "int FUN_000c9bd0(int list_handle, int16_t skip_count);",
    "0xc9c10": "void FUN_000c9c10(int object_handle, float value);",
    "0xc9c80": "void FUN_000c9c80(int object_handle, int region_name, int variant);",
    "0xc9d40": "void FUN_000c9d40(int list_handle);",
    "0xc9d80": "void FUN_000c9d80(int object_type);",
    "0xc9de0": "void FUN_000c9de0(int effect_tag, int16_t scenario_index);",
    "0xc9e50": "void FUN_000c9e50(int object_handle, int attach_object, int marker_id);",
    "0xc9ec0": "void FUN_000c9ec0(int damage_type, int16_t scenario_index);",
    "0xc9f30": "void FUN_000c9f30(int damage_type, int object_handle);",
    "0xc9f90": "float *FUN_000c9f90(void);",
    "0xca010": "float FUN_000ca010(int object_handle);",
    "0xca030": "void FUN_000ca030(int object_handle, float value);",
    "0xca050": "char FUN_000ca050(int16_t game_flag, int list_handle);",
    "0xca0f0": "char FUN_000ca0f0(int16_t game_flag, int list_handle);",
    "0xca160": "void FUN_000ca160(int16_t scenario_index, char teleport_flag, char facing_flag, int object_handle@<ebx>);",
    "0xca3f0": "void FUN_000ca3f0(int object_handle, int16_t scenario_index);",
    "0xca410": "void FUN_000ca410(int object_handle, int16_t scenario_index);",
    "0xca430": "void FUN_000ca430(int16_t game_flag, int16_t scenario_index);",
    "0xca670": "void FUN_000ca670(int16_t type, int16_t enum_index, char *buffer);",
    "0xca700": "void FUN_000ca700(void);",
    "0xca890": "const char *FUN_000ca890(int datum_index@<eax>);",
    "0xcacf0": "void FUN_000cacf0(int thread_index@<edi>);",
    "0xcae00": "int FUN_000cae00(const char *script_name@<edi>);",
    "0xcaf80": "int FUN_000caf80(int16_t name_index);",
    "0xcb940": "char FUN_000cb940(int16_t param, int thread_index@<eax>, const char *detail@<edi>);",
    "0xcde00": "void hs_runtime_update(void);",
    "0xce050": "void FUN_000ce050(int save_type, int slot);",
    "0xce0c0": "void FUN_000ce0c0(data_t *data, int *head, int object_handle);",
    "0xce110": "void FUN_000ce110(data_t *data, int link);",
    "0xce150": "void FUN_000ce150(void);",
    "0xce240": "void object_list_delete(int list_handle);",
    "0xce3c0": "void FUN_000ce3c0(void);",
}

NEW_ADDRS = list(DECLS.keys())


def main() -> None:
    hs_c = ROOT / "src/halo/hs/hs_runtime.c"
    draft_body = DRAFT.read_text()
    if draft_body.startswith("#include"):
        draft_body = "\n".join(
            line for line in draft_body.splitlines() if not line.startswith("#include")
        )

    text = hs_c.read_text()
    existing = set(re.findall(r"^(?:void|char|int|int16_t|bool|float|const char \*)\s+([A-Za-z0-9_]+)\s*\(", text, re.M))
    parts = re.split(r"\n(?=(?:void|char|int|int16_t|float|const char \*)\s+)", draft_body.strip())
    new_parts = []
    for part in parts:
        m = re.match(r"(?:void|char|int|int16_t|float|const char \*)\s+([A-Za-z0-9_]+)\s*\(", part)
        if not m:
            continue
        if m.group(1) in existing:
            print("skip existing", m.group(1))
            continue
        new_parts.append(part.rstrip())

    if new_parts:
        hs_c.write_text(text.rstrip() + "\n\n" + "\n\n".join(new_parts) + "\n")
    print("appended", len(new_parts), "functions")

    kb = json.loads((ROOT / "kb.json").read_text())
    hs = next(o for o in kb["objects"] if o["name"] == OBJECT)
    have = {f["addr"] for f in hs["functions"]}
    for addr, decl in DECLS.items():
        if addr not in have:
            hs["functions"].append({"addr": addr, "decl": decl, "ported": False})
            have.add(addr)
            print("added kb", addr)
    hs["functions"].sort(key=lambda f: int(f["addr"], 16))
    for f in hs["functions"]:
        addr = f["addr"]
        if addr in DECLS:
            f["decl"] = DECLS[addr]
            if f.get("ported") is not True:
                f["ported"] = False
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
    print("kb+allowlist updated")


if __name__ == "__main__":
    main()
