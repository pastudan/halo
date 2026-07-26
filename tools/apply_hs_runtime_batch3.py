#!/usr/bin/env python3
"""Append final hs_runtime unset drafts; update kb + allowlist."""
from __future__ import annotations

import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OBJECT = "hs_runtime.obj"
DRAFT = ROOT / "artifacts/hs_runtime_batch3_draft.c"

DECLS: dict[str, str] = {
    "0xc8720": "char FUN_000c8720(int16_t function_index, int root_datum);",
    "0xc88b0": "char FUN_000c88b0(int16_t function_index, int root_datum);",
    "0xc89c0": "char FUN_000c89c0(int16_t function_index, int root_datum);",
    "0xc8c50": "char FUN_000c8c50(int16_t function_index, int root_datum);",
    "0xc8d30": "char FUN_000c8d30(int16_t function_index, int root_datum);",
    "0xc8f40": "char FUN_000c8f40(int16_t function_index, int root_datum);",
    "0xcb9c0": "void render_debug_scripting(void);",
    "0xcbb40": "void render_debug_trigger_volumes(void);",
    "0xcc0e0": "void hs_evaluate_wake(int16_t function_index, int thread_datum, char init);",
    "0xcdf70": "void FUN_000cdf70(void *header, void *src, int size);",
    "0xce4a0": "void FUN_000ce4a0(void);",
}


def main() -> None:
    hs_c = ROOT / "src/halo/hs/hs_runtime.c"
    draft_body = DRAFT.read_text()
    if draft_body.startswith("#include"):
        draft_body = "\n".join(
            line for line in draft_body.splitlines() if not line.startswith("#include")
        )

    text = hs_c.read_text()
    existing = set(
        re.findall(
            r"^(?:void|char|int|int16_t|bool|float|const char \*)\s+([A-Za-z0-9_]+)\s*\(",
            text,
            re.M,
        )
    )
    parts = re.split(
        r"\n(?=(?:void|char|int|int16_t|float|const char \*)\s+)", draft_body.strip()
    )
    new_parts = []
    for part in parts:
        m = re.match(
            r"(?:void|char|int|int16_t|float|const char \*)\s+([A-Za-z0-9_]+)\s*\(", part
        )
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
    for addr, decl in DECLS.items():
        for f in hs["functions"]:
            if f["addr"] == addr:
                f["decl"] = decl
                if f.get("ported") is not True:
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
    print("kb+allowlist updated")


if __name__ == "__main__":
    main()
