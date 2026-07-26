#!/usr/bin/env python3
"""Lifter C: Unicorn-prove readable-C drafts in preferred dirs/ranges."""
from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    clear_pass,
    count_ported,
    func_name,
    git_commit_flips,
    git_push,
    inventory_readable,
    load_ledger_done,
    append_ledger,
    run_unicorn,
)

PREF_DIRS = (
    "interface/",
    "main/",
    "scenario/",
    "sound/",
    "tag_files/",
    "memory/",
    "models/",
)
# Also allow in-range gameplay leaves Lifter C owns with other lifters.
ADDR_LO, ADDR_HI = 0x00090000, 0x00120000
EXTRA_OK = (
    "math/",
    "hs/",
    "cseries/",
    "cutscene/",
    "game/",
    "items/",
    "effects/",
    "devices/",
    "dialogs/",
    "camera/",
)


def in_scope(source: str, addr: int) -> bool:
    src = source.replace("\\", "/")
    if any(d in src for d in PREF_DIRS):
        return True
    if ADDR_LO <= addr < ADDR_HI and any(d in src for d in EXTRA_OK + PREF_DIRS):
        return True
    return False


def ensure_oracle(addr: int) -> bool:
    oracle = ROOT / "delinked" / "functions" / f"{addr:08x}.obj"
    if oracle.exists() and oracle.stat().st_size > 0:
        return True
    oracle.parent.mkdir(parents=True, exist_ok=True)
    r = subprocess.run(
        [
            sys.executable,
            str(ROOT / "tools/equivalence/xbe_to_coff.py"),
            "--addr",
            hex(addr),
            "--out",
            str(oracle),
        ],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    return r.returncode == 0 and oracle.exists()


def flip_kb(kb: dict, addr: int) -> bool:
    for obj in kb.get("objects", []):
        for fn in obj.get("functions") or []:
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            if int(fn["addr"], 16) == addr and fn.get("ported") is False:
                fn["ported"] = True
                return True
    return False


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--commit-every", type=int, default=20)
    ap.add_argument("--no-push", action="store_true")
    ap.add_argument("--timeout", type=float, default=30.0)
    ap.add_argument("--seeds", type=int, default=100)
    args = ap.parse_args()

    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    readable = inventory_readable(kb)
    done = load_ledger_done()
    queue = [
        r
        for r in readable
        if in_scope(r["source"], r["addr_int"]) and r["addr"] not in done
    ]
    # Prefer smaller / already-lifted comment tags first (stable order by addr).
    queue.sort(key=lambda r: r["addr_int"])
    if args.limit:
        queue = queue[: args.limit]

    true0, false0 = count_ported(kb)
    print(f"lifter-c queue={len(queue)} kb true={true0} false={false0}")

    flips = []
    shas = []
    tested = 0
    for r in queue:
        ai = r["addr_int"]
        name = r["name"]
        print(f"\n== {hex(ai)} {name} ({r['source']}) ==")
        if not ensure_oracle(ai):
            print("  oracle FAIL")
            append_ledger(
                {
                    "addr": hex(ai),
                    "name": name,
                    "ok": False,
                    "phase": "oracle",
                    "lifter": "C",
                }
            )
            continue
        # unicorn_diff resolves oracle by kb addr via name; pass symbol name.
        res = run_unicorn(name, ai, args.seeds, timeout=args.timeout)
        tested += 1
        ok = clear_pass(res, args.seeds)
        append_ledger(
            {
                "addr": hex(ai),
                "name": name,
                "ok": ok,
                "phase": f"confirm{args.seeds}",
                "lifter": "C",
                "rc": res.get("rc"),
                "passed": res.get("passed"),
                "failed": res.get("failed"),
                "errors": res.get("errors"),
                "dt": res.get("dt"),
                "tail": (res.get("tail") or "")[-240:],
            }
        )
        print(
            f"  unicorn {res.get('passed')}/{res.get('failed')}/{res.get('errors')} "
            f"ok={ok} dt={res.get('dt')}"
        )
        if ok and flip_kb(kb, ai):
            flips.append(hex(ai))
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
            if args.commit_every and len(flips) % args.commit_every == 0:
                sha = git_commit_flips(args.commit_every)
                if sha:
                    shas.append(sha)
                    if not args.no_push:
                        git_push()

    rem = len(flips) % args.commit_every if args.commit_every else 0
    if flips and rem:
        sha = git_commit_flips(rem)
        if sha:
            shas.append(sha)
            if not args.no_push:
                git_push()
    elif flips and not args.commit_every:
        sha = git_commit_flips(len(flips))
        if sha:
            shas.append(sha)
            if not args.no_push:
                git_push()

    true1, false1 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    print(
        f"\ndone tested={tested} flips={len(flips)} "
        f"true {true0}->{true1} shas={shas}"
    )
    print("FLIPS", flips)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
