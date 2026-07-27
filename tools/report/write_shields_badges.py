#!/usr/bin/env python3
"""Write shields.io endpoint JSON badges from a decomp progress report."""
from __future__ import annotations

import argparse
import json
import os
from pathlib import Path


def _color(pct: float) -> str:
    if pct >= 90:
        return "brightgreen"
    if pct >= 75:
        return "green"
    if pct >= 50:
        return "yellowgreen"
    if pct >= 25:
        return "yellow"
    if pct >= 10:
        return "orange"
    return "red"


def write_badges(report: dict, out_dir: Path) -> dict:
    out_dir.mkdir(parents=True, exist_ok=True)
    funcs = report.get("summary", {}).get("functions", {})
    ported = int(funcs.get("ported", 0))
    total = int(funcs.get("total", 0)) or 1
    pct = float(funcs.get("percent", 100.0 * ported / total))

    badges = {
        "badge.json": {
            "schemaVersion": 1,
            "label": "decompilation",
            "message": f"{pct:.1f}%",
            "color": _color(pct),
        },
        "functions-badge.json": {
            "schemaVersion": 1,
            "label": "functions",
            "message": f"{ported:,}/{total:,}",
            "color": "blue",
        },
    }
    for name, payload in badges.items():
        (out_dir / name).write_text(json.dumps(payload, separators=(",", ":")) + "\n")
    return {"percent": pct, "ported": ported, "total": total, "files": list(badges)}


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument(
        "--report",
        default="artifacts/progress/report.json",
        help="Path to generate_decomp_report JSON",
    )
    ap.add_argument(
        "--output-dir",
        default="artifacts/progress",
        help="Directory for badge.json / functions-badge.json",
    )
    args = ap.parse_args()
    report = json.loads(Path(args.report).read_text())
    info = write_badges(report, Path(args.output_dir))
    print(
        f"Wrote shields badges: {info['ported']:,}/{info['total']:,} "
        f"({info['percent']:.1f}%) → {args.output_dir}"
    )
    # Export for GitHub Actions step summaries / env.
    if gh_env := os.environ.get("GITHUB_ENV"):
        with open(gh_env, "a", encoding="utf-8") as fh:
            fh.write(f"PROGRESS_PERCENT={info['percent']:.1f}\n")
            fh.write(f"PROGRESS_PORTED={info['ported']}\n")
            fh.write(f"PROGRESS_TOTAL={info['total']}\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
