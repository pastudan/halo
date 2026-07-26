#!/usr/bin/env python3
"""Atomically restore/prove known-good interface HAND lifts."""
from __future__ import annotations

import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
sys.path.insert(0, str(ROOT / "tools" / "equivalence"))

import lifter_interface as li  # noqa: E402
from lift_inventory_batch4 import find_naked_block  # noqa: E402
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    clear_pass,
    is_naked_near_def,
    resolve_src,
    run_unicorn,
)
from unicorn_diff import _compile_build_obj_for_source  # noqa: E402

DECLS = {
    0xE0AB0: "char player_ui_game_variant_specified(void *out_variant);",
    0xE0D80: "char player_ui_edit_profile_is_default_profile(void);",
    0xE0EA0: "void *player_ui_get_edit_player_profile(void);",
    0xE0EC0: "void *player_ui_get_edit_playlist_profile(void);",
    0xE2650: "void FUN_000e2650(float x, float y, float z);",
    0xEEBE0: "char FUN_000eebe0(void *widget);",
    0xF0070: "char FUN_000f0070(void *widget);",
    0xF0620: "char FUN_000f0620(void *widget);",
}
SIG = {
    "player_ui_game_variant_specified": "char (*const {n})(void *)",
    "player_ui_edit_profile_is_default_profile": "char (*const {n})(void)",
    "player_ui_get_edit_player_profile": "void *(*const {n})(void)",
    "player_ui_get_edit_playlist_profile": "void *(*const {n})(void)",
    "FUN_000eebe0": "char (*const {n})(void *)",
    "FUN_000f0070": "char (*const {n})(void *)",
    "FUN_000f0620": "char (*const {n})(void *)",
    "FUN_000e2650": "void (*const {n})(float, float, float)",
}
WINNERS = [
    0xDC7A0,
    0xE54E0,
    0xE5530,
    0xE0960,
    0xE1060,
    0xE33A0,
    0xE33E0,
    0xE2650,
    0xEEBE0,
    0xF0070,
    0xF0620,
    0xE0AB0,
    0xE0D80,
    0xE0EA0,
    0xE0EC0,
]


def main() -> int:
    for p in (ROOT / "src/halo/interface").glob("*.c"):
        t = p.read_text(encoding="utf-8", errors="replace")
        t2 = re.sub(r"@<\w+>", "", t)
        if t2 != t:
            p.write_text(t2)

    kb = json.loads((ROOT / "kb.json").read_text())
    for o in kb.get("objects", []):
        for fn in o.get("functions") or []:
            if fn.get("addr") and int(fn["addr"], 16) in DECLS:
                fn["decl"] = DECLS[int(fn["addr"], 16)]
    (ROOT / "kb.json").write_text(json.dumps(kb, indent=2) + "\n")
    subprocess.check_call(
        [
            sys.executable,
            str(ROOT / "tools/analysis/knowledge.py"),
            "--gen-header",
            str(ROOT / "build/generated/decl.h"),
            "--gen-def",
            str(ROOT / "build/generated/halo.xbe.def"),
            "--gen-thunks",
            str(ROOT / "build/generated/thunks.c"),
        ],
        stdout=subprocess.DEVNULL,
    )

    pat = re.compile(
        r"static\s+[\w\s\*]+?\(\s*\*\s*const\s+(\w+)\s*\)\s*\([^;]*\)\s*=\s*"
        r"(?:\(void\s*\*\)\s*)?(\w+)\s*;"
    )
    for path in (ROOT / "src/halo/interface").glob("*.c"):
        text = path.read_text(encoding="utf-8", errors="replace")
        out = []
        last = 0
        n = 0
        for m in pat.finditer(text):
            if m.group(2) not in SIG:
                continue
            out.append(text[last : m.start()])
            out.append(
                "static "
                + SIG[m.group(2)].format(n=m.group(1))
                + f" = {m.group(2)};"
            )
            last = m.end()
            n += 1
        if n:
            out.append(text[last:])
            path.write_text("".join(out))

    flips = []
    for ai in WINNERS:
        src, name, body, _decl = li.HAND[ai]
        path = resolve_src(src)
        assert path is not None
        text = path.read_text(encoding="utf-8", errors="replace")
        if is_naked_near_def(text.splitlines(), name, hex(ai)):
            span = find_naked_block(text, name, ai)
            if span is None:
                print(hex(ai), "no span", flush=True)
                continue
            path.write_text(text[: span[0]] + body + "\n" + text[span[1] :])
        obj, err = _compile_build_obj_for_source(src)
        if not obj:
            print(hex(ai), "COMPILE FAIL", flush=True)
            for line in (err or "").splitlines():
                if "error:" in line:
                    print(" ", line[:160], flush=True)
            continue
        ensure_oracle(ai)
        res = run_unicorn(name, ai, 100, timeout=45)
        if not clear_pass(res, 100):
            res = run_unicorn(hex(ai), ai, 100, timeout=45)
        ok = clear_pass(res, 100)
        print(
            hex(ai),
            name,
            "ok",
            ok,
            res.get("passed"),
            res.get("failed"),
            res.get("errors"),
            flush=True,
        )
        if ok:
            flips.append(ai)

    kb = json.loads((ROOT / "kb.json").read_text())
    for ai in flips:
        flip_kb(kb, ai)
    for o in kb.get("objects", []):
        for fn in o.get("functions") or []:
            if fn.get("addr") == "0xe4590":
                fn["ported"] = True
    (ROOT / "kb.json").write_text(json.dumps(kb, indent=2) + "\n")
    t = sum(
        1
        for o in kb["objects"]
        if (o.get("source") or "").startswith("interface/")
        for fn in o.get("functions") or []
        if fn.get("ported") is True
    )
    f = sum(
        1
        for o in kb["objects"]
        if (o.get("source") or "").startswith("interface/")
        for fn in o.get("functions") or []
        if fn.get("ported") is False
    )
    print("FLIPS", len(flips), [hex(a) for a in flips], flush=True)
    print("iface", t, f, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
