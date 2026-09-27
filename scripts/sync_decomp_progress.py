#!/usr/bin/env python3
"""Refresh docs/DECOMP_PROGRESS.md from local halo-re/kb.json (+ stian origin/main)."""
from __future__ import annotations

import json
import subprocess
import sys
from datetime import datetime
from pathlib import Path
from zoneinfo import ZoneInfo

ROOT = Path(__file__).resolve().parents[1]
HALO_RE = ROOT / "halo-re"
OUT = ROOT / "docs" / "DECOMP_PROGRESS.md"


def count_ported(kb: dict) -> tuple[int, int, int]:
    true = false = 0

    def walk(node):
        nonlocal true, false
        if isinstance(node, dict):
            if "ported" in node and "addr" in node:
                if node["ported"] is True:
                    true += 1
                elif node["ported"] is False:
                    false += 1
            for value in node.values():
                walk(value)
        elif isinstance(node, list):
            for value in node:
                walk(value)

    walk(kb)
    return true, false, true + false


def main() -> int:
    if not (HALO_RE / "kb.json").is_file():
        print("halo-re/kb.json missing", file=sys.stderr)
        return 1

    track = json.loads((HALO_RE / "kb.json").read_text())
    t, f, tot = count_ported(track)
    rev = subprocess.check_output(
        ["git", "rev-parse", "--short", "HEAD"], cwd=HALO_RE, text=True
    ).strip()
    as_of = datetime.now(ZoneInfo("America/Los_Angeles")).strftime(
        "%Y-%m-%d (~%H:%M %Z)"
    )

    stian_true = stian_false = 0
    try:
        stian = json.loads(
            subprocess.check_output(
                ["git", "show", "origin/main:kb.json"], cwd=HALO_RE
            )
        )
        stian_true, stian_false, _ = count_ported(stian)
    except subprocess.CalledProcessError:
        pass

    lead = t - stian_true if stian_true else 0
    pct = 100.0 * t / tot if tot else 0.0
    body = f"""# Halo CE decompilation progress

**As of:** {as_of} — Track A @ `{rev}`

| Metric | stianeklund | Track A |
|--------|------------:|--------:|
| ported:true | {stian_true:,} | **{t}** / {tot:,} (**{pct:.1f}%**) |
| ported:false | {stian_false} | **{f}** |
| Lead | — | **+{lead}** |

Course: naked→C + Unicorn `100/0/0` until false≈0.

Remaining ~{f}: XDK/LIBCMT/tif + remaining game leaves (see worktrees).

> Auto-updated on [pastudan/halo](https://github.com/pastudan/halo) by the **Unit Tests & Progress** GitHub Action
> ([badge](https://img.shields.io/endpoint?url=https://pastudan.github.io/halo/badge.json) · [dashboard](https://pastudan.github.io/halo/)).
"""
    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text(body)
    print(f"Wrote {OUT} ({t}/{tot} = {pct:.1f}%)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
