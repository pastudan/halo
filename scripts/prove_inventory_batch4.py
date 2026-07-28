#!/usr/bin/env python3
"""Unicorn-prove batch4 inventory lifts; flip ported:true on clear PASS; commit chunks."""
from __future__ import annotations

import json
import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
from lift_inventory_batch4 import LIFTS  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
    func_name,
    git_commit_flips,
    run_unicorn,
)

RESULTS_RE = re.compile(r"(\d+) passed, (\d+) failed, (\d+) errors")


def ensure_oracle(addr: int) -> bool:
    """Always regenerate per-function COFF from the XBE.

    Stale/partial oracles in delinked/functions/ have caused false
    ORACLE-CRASH Unicorn failures (e.g. 0x1f770: 14 vs 19 relocs).
    """
    oracle = ROOT / "delinked" / "functions" / f"{addr:08x}.obj"
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
    return r.returncode == 0 and oracle.exists() and oracle.stat().st_size > 0


def flip_kb(kb: dict, addr: int) -> bool:
    for obj in kb.get("objects", []):
        for fn in obj.get("functions") or []:
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            if int(fn["addr"], 16) == addr and fn.get("ported") is False:
                fn["ported"] = True
                return True
    return False


def prove_one(name: str, addr: int, seeds: int = 100, timeout: float = 40.0) -> dict:
    if not ensure_oracle(addr):
        return {"addr": hex(addr), "name": name, "ok": False, "err": "oracle"}
    # Prefer hex addr to avoid duplicate-name collisions; unicorn_diff accepts 0x…
    res = run_unicorn(hex(addr), addr, seeds, timeout=timeout)
    if not clear_pass(res, seeds):
        # retry with symbol name (some objs export named symbols only)
        res2 = run_unicorn(name, addr, seeds, timeout=timeout)
        if clear_pass(res2, seeds):
            res = res2
    ok = clear_pass(res, seeds)
    return {
        "addr": hex(addr),
        "name": name,
        "ok": ok,
        "passed": res.get("passed"),
        "failed": res.get("failed"),
        "errors": res.get("errors"),
        "rc": res.get("rc"),
        "detail": (res.get("tail") or "")[-240:],
    }


def main() -> int:
    import argparse

    ap = argparse.ArgumentParser()
    ap.add_argument("--commit-every", type=int, default=15)
    ap.add_argument("--seeds", type=int, default=100)
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--no-push", action="store_true")
    args = ap.parse_args()

    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    by = {}
    for obj in kb.get("objects", []):
        for fn in obj.get("functions") or []:
            if fn.get("addr"):
                by[int(fn["addr"], 16)] = fn

    queue = []
    for addr, (src, name, _body, _decl) in sorted(LIFTS.items()):
        fn = by.get(addr)
        if not fn or fn.get("ported") is not False:
            continue
        queue.append((addr, name or func_name(fn)))

    # Also include a few ready inventory fixes outside LIFTS
    extras = [
        (0x4A6E0, "ai_debug_idle_look_clear"),
        (0x100060, "main_set_difficulty"),
        (0x100370, "main_won_map"),
        (0x17ED70, "FUN_0017ed70"),
        (0x1937A0, "vertex_type_from_shader_tag"),
        (0x68A50, "FUN_00068a50"),
    ]
    for addr, name in extras:
        fn = by.get(addr)
        if fn and fn.get("ported") is False:
            if (addr, name) not in queue:
                queue.append((addr, name))

    if args.limit:
        queue = queue[: args.limit]

    true0, false0 = count_ported(kb)
    print(f"prove queue={len(queue)} kb true={true0} false={false0}")

    flips = []
    shas = []
    for addr, name in queue:
        print(f"\n== {hex(addr)} {name} ==")
        res = prove_one(name, addr, seeds=args.seeds)
        print(
            f"  ok={res['ok']} p/f/e={res.get('passed')}/{res.get('failed')}/{res.get('errors')} "
            f"rc={res.get('rc')}"
        )
        if not res["ok"] and res.get("detail"):
            print("  ", res["detail"].replace("\n", " ")[-200:])
        append_ledger(
            {
                "addr": hex(addr),
                "name": name,
                "ok": res["ok"],
                "phase": f"confirm{args.seeds}",
                "lifter": "batch4",
                "passed": res.get("passed"),
                "failed": res.get("failed"),
                "errors": res.get("errors"),
            }
        )
        if res["ok"]:
            if flip_kb(kb, addr):
                flips.append(hex(addr))
                KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        if len(flips) and len(flips) % args.commit_every == 0:
            # First commit includes source lifts alongside kb flips.
            subprocess.run(
                [
                    "git",
                    "add",
                    "-A",
                    "src/halo",
                    "scripts/lift_inventory_batch4.py",
                    "scripts/prove_inventory_batch4.py",
                    "tools/equivalence/unicorn_diff.py",
                    "kb.json",
                    "tools/equivalence/leaf_cache.json",
                ],
                cwd=ROOT,
                check=False,
            )
            sha = git_commit_flips(args.commit_every)
            if sha:
                shas.append(sha)
                print(f"  COMMIT {sha}")

    rem = len(flips) % args.commit_every
    if rem or flips:
        subprocess.run(
            [
                "git",
                "add",
                "-A",
                "src/halo",
                "scripts/lift_inventory_batch4.py",
                "scripts/prove_inventory_batch4.py",
                "tools/equivalence/unicorn_diff.py",
                "kb.json",
                "tools/equivalence/leaf_cache.json",
            ],
            cwd=ROOT,
            check=False,
        )
        if rem:
            sha = git_commit_flips(rem)
            if sha:
                shas.append(sha)
                print(f"  COMMIT {sha}")
        else:
            # source-only leftover
            diff = subprocess.run(["git", "diff", "--cached", "--quiet"], cwd=ROOT)
            if diff.returncode != 0:
                subprocess.run(
                    [
                        "git",
                        "commit",
                        "-m",
                        "lift(track-a): batch4 naked inventory leaves to readable C + unicorn extract fix.",
                    ],
                    cwd=ROOT,
                    check=False,
                )
                shas.append(
                    subprocess.check_output(
                        ["git", "rev-parse", "HEAD"], cwd=ROOT, text=True
                    ).strip()
                )

    true1, false1 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    print(
        f"\nDONE proven_this_run={len(flips)} kb true {true0}->{true1} false {false0}->{false1}"
    )
    print("flips", flips)
    print("shas", shas)
    Path("/tmp/batch4_prove_summary.json").write_text(
        json.dumps({"proven": len(flips), "flips": flips, "shas": shas}, indent=2)
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
