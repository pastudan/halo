#!/usr/bin/env python3
"""Restore pre-naked readable C from git history for Track A focus symbols, then Unicorn-prove."""
from __future__ import annotations

import json
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))

from lift_inventory_batch4 import find_naked_block  # noqa: E402
from prove_inventory_batch4 import ensure_oracle, prove_one, flip_kb  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    count_ported,
    is_naked_near_def,
)

os.environ.setdefault("BIPED_SIBLING_RESOLVE", "1")

# name -> (addr, source relative to src/halo, restore commit)
TARGETS = [
    ("unit_leap_begin", 0x1B1C70, "units/units.c", "f1eb154e0d03"),
    ("actor_perception_acknowledge", 0x2F2B0, "ai/actor_perception.c", "7dbc024205a4"),
    ("unit_adjust_projectile_ray", 0x1ACF90, "units/units.c", "f1eb154e0d03"),
    ("actor_action_allow_cover_seeking", 0x1CCC0, "ai/actions.c", "9539ec17365d"),
    ("actor_get_best_damaging_prop", 0x2FA70, "ai/actor_perception.c", "7dbc024205a4"),
    ("actor_aim_jump", 0x2ACE0, "ai/actor_moving.c", "8cccbdd096c9"),
    ("actor_update_prop_desire", 0x14360, "ai/actor_looking.c", "a2808e6b77c0"),
    ("ai_debug_get_path_storage", 0x49120, "ai/ai_debug.c", "58d9c90d2fc0"),
    ("actor_path_3d_available", 0x2B720, "ai/actor_moving.c", "c5f7471742b3"),
    ("actor_get_stopping_distances", 0x2A610, "ai/actor_moving.c", "c5f7471742b3"),
    ("actor_look_compute_prop_interest", 0x16D40, "ai/actor_looking.c", "f69e6f4aaaf8"),
    ("actor_move_get_avoidance_vector", 0x2B490, "ai/actor_moving.c", "c7cd95e79a9c"),
    ("actor_move_get_avoidance_direction", 0x2B5D0, "ai/actor_moving.c", "1cac75ea28ca"),
    ("actor_action_try_to_throw_grenade", 0x1FA60, "ai/actions.c", "d2535c6b451a"),
    ("actor_move_try_evasion_direction", 0x2AB40, "ai/actor_moving.c", "c7cd95e79a9c"),
    ("actor_move_try_evasion_vector", 0x2A8F0, "ai/actor_moving.c", "c7cd95e79a9c"),
    ("actor_pursuit_find_nearby_actors", 0x20280, "ai/actions.c", "b5350bf74478"),
    ("actor_perception_unit_from_swarm", 0x31C00, "ai/actor_perception.c", "f1c75b1cb0b6"),
    ("unit_set_seat_state", 0x1A9240, "units/units.c", "8fd1bd27cf86"),
    ("unit_throw_grenade_begin", 0x1B2090, "units/units.c", "d90f2c5ad05a"),
    ("unit_scripting_enter_vehicle", 0x1B32D0, "units/units.c", "200cf8d26762"),
    ("unit_adjust_plan_overlap", 0x1ACB70, "units/units.c", "d90f2c5ad05a"),
    ("rasterizer_text_draw_cached_char", 0x183C00, "rasterizer/rasterizer_text.c", "00fc64fcb867"),
    ("rasterizer_text_draw_cached_chars", 0x183CF0, "rasterizer/rasterizer_text.c", "91af09417e07"),
    ("ai_communication_initialize", 0x42A30, "ai/ai_communication.c", None),  # already C
    ("vehicle_scripting_load_magic", 0x1B3400, "units/units.c", None),  # already C
]


def extract_func(old: str, name: str, addr: int) -> str | None:
    addr_hex = f"0x{addr:x}"
    # Prefer comment-tagged definition
    pats = [
        rf"(?ms)/\*[^\n]*\b{re.escape(name)}\b[\s\S]*?\*/\s*"
        rf"(?:__attribute__\s*\(\([^\)]*\)\)\s*)*"
        rf"(?:static\s+)?[\w\s\*]+\b{re.escape(name)}\s*\([^{{]*\)\s*\{{[\s\S]*?^\}}\s*\n",
        rf"(?ms)/\*[^\n]*\b{re.escape(addr_hex)}\b[\s\S]*?\*/\s*"
        rf"(?:__attribute__\s*\(\([^\)]*\)\)\s*)*"
        rf"(?:static\s+)?[\w\s\*]+\b{re.escape(name)}\s*\([^{{]*\)\s*\{{[\s\S]*?^\}}\s*\n",
        rf"(?ms)(?:__attribute__\s*\(\([^\)]*\)\)\s*)*"
        rf"(?:static\s+)?[\w\s\*]+\b{re.escape(name)}\s*\([^{{]*\)\s*\{{[\s\S]*?^\}}\s*\n",
    ]
    for pat in pats:
        m = re.search(pat, old)
        if not m:
            continue
        body = m.group(0)
        if "naked" in body[:500]:
            continue
        if body.count("__asm__") > 2 or "XBE naked" in body:
            continue
        # Normalize header comment to mark readable lift
        if "readable C lift" not in body[:200]:
            body = re.sub(
                rf"/\*\s*{re.escape(name)}\s*\({re.escape(addr_hex)}\)",
                f"/* {name} ({addr_hex}) — readable C lift (restored pre-naked)",
                body,
                count=1,
            )
            if "readable C lift" not in body[:240]:
                body = (
                    f"/* {name} ({addr_hex}) — readable C lift (restored pre-naked). */\n"
                    + re.sub(r"(?s)^/\*.*?\*/\s*", "", body, count=1)
                )
        return body if body.endswith("\n") else body + "\n"
    return None


def restore_one(name: str, addr: int, source: str, commit: str | None) -> dict:
    path = ROOT / "src" / "halo" / source
    text = path.read_text(encoding="utf-8", errors="replace")
    lines = text.splitlines()
    if not is_naked_near_def(lines, name, hex(addr)):
        return {"name": name, "addr": hex(addr), "phase": "already_c"}
    if not commit:
        return {"name": name, "addr": hex(addr), "phase": "no_commit", "ok": False}
    old = subprocess.check_output(
        ["git", "show", f"{commit}:src/halo/{source}"],
        cwd=ROOT,
        text=True,
    )
    body = extract_func(old, name, addr)
    if not body:
        return {"name": name, "addr": hex(addr), "phase": "extract_fail", "ok": False}
    span = find_naked_block(text, name, addr)
    if span is None:
        # broader locate: comment + #if clang naked block by addr
        pat = re.compile(
            rf"/\*[^\n]*\b0x{addr:x}\b[\s\S]*?#if defined\(__clang__\)[\s\S]*?#endif\s*\n",
            re.I,
        )
        m = pat.search(text)
        if not m:
            return {"name": name, "addr": hex(addr), "phase": "locate_fail", "ok": False}
        span = (m.start(), m.end())
    start, end = span
    chunk = text[start:end]
    if f"0x{addr:x}" not in chunk.lower():
        return {"name": name, "addr": hex(addr), "phase": "addr_guard", "ok": False}
    new = text[:start] + body + "\n" + text[end:]
    path.write_text(new, encoding="utf-8")
    lines2 = new.splitlines()
    if is_naked_near_def(lines2, name, hex(addr)):
        return {"name": name, "addr": hex(addr), "phase": "still_naked", "ok": False}
    return {"name": name, "addr": hex(addr), "phase": "restored", "ok": True}


def main() -> int:
    kb0 = json.loads(KB_PATH.read_text(encoding="utf-8"))
    true0, false0 = count_ported(kb0)
    print(f"start ported true={true0} false={false0}", flush=True)

    restored = []
    for name, addr, source, commit in TARGETS:
        r = restore_one(name, addr, source, commit)
        print(f"restore {r}", flush=True)
        if r.get("phase") in ("restored", "already_c"):
            restored.append((name, addr, source))

    proven = []
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    for name, addr, source in restored:
        path = ROOT / "src" / "halo" / source
        lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
        if is_naked_near_def(lines, name, hex(addr)):
            print(f"SKIP naked {name}", flush=True)
            append_ledger(
                {
                    "addr": hex(addr),
                    "name": name,
                    "phase": "naked_blocked",
                    "ok": False,
                }
            )
            continue
        print(f"oracle {name} {ensure_oracle(addr)}", flush=True)
        res = prove_one(name, addr, seeds=100, timeout=90.0)
        print(f"prove {res}", flush=True)
        append_ledger({**res, "phase": "unicorn"})
        if not res.get("ok"):
            continue
        # hard rule: never flip if naked remains
        lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
        if is_naked_near_def(lines, name, hex(addr)):
            print(f"BLOCK flip naked {name}", flush=True)
            continue
        if flip_kb(kb, addr):
            proven.append(name)
            print(f"FLIP {name}", flush=True)
        else:
            print(f"flip miss {name}", flush=True)

    if proven:
        KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        # knowledge normalize
        subprocess.run(
            [sys.executable, "tools/analysis/knowledge.py", "--update"],
            cwd=ROOT,
            check=False,
        )

    kb_final = json.loads(KB_PATH.read_text(encoding="utf-8"))
    true1, false1 = count_ported(kb_final)
    print(
        f"DONE proven={len(proven)} names={proven} true={true1} false={false1} "
        f"delta_true=+{true1 - true0}",
        flush=True,
    )
    return 0 if proven else 1


if __name__ == "__main__":
    raise SystemExit(main())
