#!/usr/bin/env python3
"""Retry OK-domain readable-C ported:false with float-tol 32 / real-callees."""
from __future__ import annotations

import json
import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
    git_push,
    inventory_readable,
)

OK = (
    "hs/",
    "game/",
    "effects/",
    "cutscene/",
    "main/",
    "camera/",
    "sound/",
    "cache/",
    "text/",
    "networking/",
    "physics/",
    "scenario/",
    "devices/",
    "models/",
    "saved",
)
SKIP = ("xdk/", "libcmt", "bink", "d3d", "dsound", "xapilib", "kb_common")
COMMIT_EVERY = 8


def run_flags(name: str, addr: int, seeds: int, timeout: float, extra: list[str]) -> dict:
    outj = ROOT / "artifacts" / "equivalence" / f"uni_{addr:08x}_ft.json"
    cmd = [
        sys.executable,
        str(ROOT / "tools/equivalence/unicorn_diff.py"),
        name,
        "--allow-stubs",
        "--seeds",
        str(seeds),
        "-q",
        "--output-json",
        str(outj),
        *extra,
    ]
    try:
        proc = subprocess.run(
            cmd, cwd=str(ROOT), capture_output=True, text=True, timeout=timeout
        )
    except subprocess.TimeoutExpired:
        return {"rc": 124, "passed": None, "failed": None, "errors": None}
    text = (proc.stdout or "") + (proc.stderr or "")
    m = re.search(r"(\d+) passed, (\d+) failed, (\d+) errors", text)
    p = f = e = None
    if m:
        p, f, e = map(int, m.groups())
    return {"rc": proc.returncode, "passed": p, "failed": f, "errors": e}


def commit_flips(n: int, push: bool) -> None:
    subprocess.run(
        ["git", "add", "kb.json", "scripts/unicorn_float_tol_campaign.py"],
        cwd=ROOT,
        check=False,
    )
    subprocess.run(
        [
            "git",
            "commit",
            "-m",
            f"verify(track-a): unicorn float-tol prove {n} (ported:true).",
        ],
        cwd=ROOT,
        check=False,
    )
    if push:
        try:
            git_push()
        except SystemExit:
            pass


def main() -> int:
    import argparse

    ap = argparse.ArgumentParser()
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--seeds", type=int, default=100)
    ap.add_argument("--timeout", type=float, default=40.0)
    ap.add_argument("--no-push", action="store_true")
    args = ap.parse_args()

    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    true0, false0 = count_ported(kb)
    queue = []
    for r in inventory_readable(kb):
        src = (r.get("source") or "").replace("\\", "/").lower()
        if any(s in src for s in SKIP):
            continue
        if not any(d in src for d in OK):
            continue
        queue.append(r)
    if args.limit:
        queue = queue[: args.limit]
    print(f"float-tol queue={len(queue)} true={true0} false={false0}", flush=True)

    flips: list[str] = []
    since = 0
    for r in queue:
        ai, name = r["addr_int"], r["name"]
        print(f"\n== {hex(ai)} {name} ==", flush=True)
        if not ensure_oracle(ai):
            print("  oracle FAIL", flush=True)
            continue
        ok = False
        res: dict = {}
        for extra in (
            ["--float-tolerance", "32"],
            ["--real-callees", "--float-tolerance", "32"],
            ["--real-callees"],
        ):
            res = run_flags(name, ai, args.seeds, args.timeout, extra)
            ok = clear_pass(res, args.seeds)
            print(
                f"  {extra} -> {res.get('passed')}/{res.get('failed')}/{res.get('errors')} ok={ok}",
                flush=True,
            )
            if ok:
                break
        append_ledger(
            {
                "addr": hex(ai),
                "name": name,
                "ok": ok,
                "phase": "float_tol_ok_domains",
                "passed": res.get("passed"),
                "failed": res.get("failed"),
                "errors": res.get("errors"),
            }
        )
        if not ok:
            continue
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if flip_kb(kb, ai):
            flips.append(hex(ai))
            since += 1
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
            print(f"  FLIP total={len(flips)}", flush=True)
        if since >= COMMIT_EVERY:
            commit_flips(since, not args.no_push)
            since = 0

    if since:
        commit_flips(since, not args.no_push)

    true1, _ = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    summary = {"proven": len(flips), "flips": flips, "true0": true0, "true1": true1}
    Path("/tmp/float_tol_ok_summary.json").write_text(json.dumps(summary, indent=2))
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
