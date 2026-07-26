#!/usr/bin/env python3
"""Append hs remaining drafts and update kb/allowlist."""
from __future__ import annotations

import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OBJECT = "hs.obj"

DECLS: dict[str, str] = {
    "0xc1f80": "void FUN_000c1f80(int16_t function_index, int thread_datum, char init);",
    "0xc2100": "void FUN_000c2100(int16_t function_index, int thread_datum, char init);",
    "0xc2120": "void FUN_000c2120(int16_t function_index, int thread_datum, char init);",
    "0xc2140": "void FUN_000c2140(int16_t function_index, int thread_datum, char init);",
    "0xc3a50": "char hs_scenario_merge(void *dst_scenario, void *src_scenario);",
    "0xc3db0": "int16_t hs_find_tag_reference_by_index(int tag_index);",
    "0xc4010": "int FUN_000c4010(const char **a, const char **b);",
    "0xc4030": "void FUN_000c4030(const char *token@<esi>);",
    "0xc40b0": "void FUN_000c40b0(const char **tokens, int16_t start@<ecx>, int16_t end@<eax>);",
    "0xc40f0": "void FUN_000c40f0(int16_t name_offset, int element_size, void *block@<ebx>);",
    "0xc4130": "void FUN_000c4130(int16_t block_offset, int16_t name_offset, int element_size);",
    "0xc4160": "void FUN_000c4160(void);",
    "0xc4180": "void FUN_000c4180(void);",
    "0xc41b0": "void FUN_000c41b0(void);",
    "0xc41e0": "void FUN_000c41e0(void);",
    "0xc4240": "void FUN_000c4240(void);",
    "0xc4270": "void FUN_000c4270(void);",
    "0xc4320": "void FUN_000c4320(void);",
    "0xc4350": "void FUN_000c4350(void);",
    "0xc4380": "void FUN_000c4380(void);",
    "0xc43b0": "void FUN_000c43b0(void);",
    "0xc43e0": "void FUN_000c43e0(void);",
    "0xc4410": "void FUN_000c4410(void);",
    "0xc4440": "void FUN_000c4440(void);",
    "0xc4470": "void FUN_000c4470(void);",
    "0xc44a0": "void FUN_000c44a0(void);",
    "0xc44d0": "void FUN_000c44d0(void);",
    "0xc4500": "void FUN_000c4500(void);",
    "0xc4540": "void FUN_000c4540(void);",
    "0xc4580": "int16_t hs_tokens_enumerate(const char *prefix, uint32_t type_mask, char **tokens, int16_t max_tokens);",
    "0xc4770": "int FUN_000c4770(void *file_a, void *file_b);",
    "0xc4a40": "void FUN_000c4a40(int16_t function_index@<eax>, char *buffer@<esi>);",
    "0xc4ae0": "void FUN_000c4ae0(int16_t function_index@<eax>, char *dest);",
    "0xc4b00": "char hs_evaluate_by_name(const char *name);",
    "0xc4bb0": "void FUN_000c4bb0(int16_t function_index, int thread_datum, char init);",
    "0xc4e20": "void hs_help(const char *name);",
    "0xc4e90": "void hs_doc(void);",
    "0xc4f90": "void FUN_000c4f90(void);",
    "0xc5310": "int FUN_000c5310(int parent_handle, int sibling_handle);",
    "0xc55d0": "char FUN_000c55d0(const char *name, int *out_handles, int16_t max_count@<ebx>, int root_handle@<edi>);",
}

NEW_ADDRS = [
    "0xc4240",
    "0xc4270",
    "0xc4320",
    "0xc4350",
    "0xc4380",
    "0xc43b0",
    "0xc43e0",
    "0xc4410",
    "0xc4440",
    "0xc4470",
    "0xc44a0",
    "0xc44d0",
    "0xc4500",
    "0xc4540",
    "0xc4f90",
]


def main() -> None:
    hs_c = ROOT / "src/halo/hs/hs.c"
    draft = (ROOT / "artifacts/hs_remaining_draft.c").read_text()
    # drop the include/comment preamble from draft for append
    body = draft.split("/* Draft lifts", 1)[-1]
    body = "/* Draft lifts" + body if body.startswith(" for") else draft
    # Remove the #include line if present
    lines = []
    for line in draft.splitlines():
        if line.startswith("#include"):
            continue
        lines.append(line)
    draft_body = "\n".join(lines).strip() + "\n"

    text = hs_c.read_text()
    existing = set(re.findall(r"^(?:void|char|int|int16_t|bool|float)\s+([A-Za-z0-9_]+)\s*\(", text, re.M))
    # split draft into functions
    parts = re.split(r"\n(?=(?:void|char|int|int16_t)\s+)", draft_body)
    new_parts = []
    for part in parts:
        m = re.match(r"(?:void|char|int|int16_t)\s+([A-Za-z0-9_]+)\s*\(", part)
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
    for addr in NEW_ADDRS:
        if addr in have:
            continue
        hs["functions"].append(
            {"addr": addr, "decl": DECLS[addr], "ported": False}
        )
        have.add(addr)
        print("added kb", addr)

    # sort hs functions by addr
    hs["functions"].sort(key=lambda f: int(f["addr"], 16))

    for f in hs["functions"]:
        addr = f["addr"]
        if addr in DECLS:
            f["decl"] = DECLS[addr]
            if f.get("ported") not in (True,):
                f["ported"] = False

    # fix __strnicmp decl
    for o in kb["objects"]:
        for f in o.get("functions", []):
            if f.get("addr") == "0x1e6596":
                f["decl"] = (
                    "int __strnicmp(const char *a, const char *b, size_t n);"
                )

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
