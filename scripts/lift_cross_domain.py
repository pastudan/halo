#!/usr/bin/env python3
"""Cross-domain wrapper grind (OK domains) via lift_emit_prove.

Patterns extended in lift_thin_wrappers / lift_assert_wrappers:
  - game_malloc-style global init (telnet_console)
  - HS ebx-context + imm stack wrappers
  - object_get+tag_get+cmp+call (recorded_animations)
  - player_effect global field stores
  - soft/fatal display_assert parse
  - uputs/uvprintf strlen-bound assert forwards
  - main_save_core_name soft-assert + copy
"""
from __future__ import annotations
import subprocess, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
OK = [
    "hs/", "game/", "effects/", "cutscene/", "main/", "camera/", "sound/",
    "cache/", "text/", "networking/", "physics/", "scenario/", "devices/",
    "models/", "saved",
]
cmd = [sys.executable, str(ROOT / "scripts/lift_emit_prove.py"), "--commit-every", "5", "--timeout", "50", "--max-size", "160"]
for d in OK:
    cmd += ["--prefer", d]
cmd += sys.argv[1:]
raise SystemExit(subprocess.call(cmd, cwd=ROOT))
