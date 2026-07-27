#!/usr/bin/env python3
"""Exhaust readable-C ported:false via Unicorn; flip clear passes; commit chunks."""
from __future__ import annotations

import argparse
import json
import os
import re
import subprocess
import sys
import time
from collections import Counter
from pathlib import Path
from typing import Dict, List, Optional, Set, Tuple

ROOT = Path(__file__).resolve().parents[1]
KB_PATH = ROOT / "kb.json"
LEDGER = ROOT / "artifacts" / "equivalence" / "unicorn_c_campaign.jsonl"
INV = ROOT / "artifacts" / "equivalence" / "readable_c_ported_false.json"
ORACLE_DIR = ROOT / "delinked" / "functions"

NAKED_ATTR = re.compile(r"__attribute__\s*\(\s*\(\s*naked\b")
NAKED_MARK = re.compile(
    r"XBE naked draft|naked draft \(batch|clang naked draft required", re.I
)
RESULTS_RE = re.compile(r"(\d+) passed, (\d+) failed, (\d+) errors")


def resolve_src(src: str) -> Optional[Path]:
    if not src:
        return None
    for base in (ROOT / "src" / "halo", ROOT / "src", ROOT):
        cand = base / src
        if cand.exists():
            return cand
    return None


def func_name(fn: dict) -> str:
    name = fn.get("name")
    if name:
        return name
    m = re.search(r"(\w+)\s*\(", fn.get("decl") or "")
    return m.group(1) if m else ""


def is_naked_near_def(lines: List[str], name: str, addr: str) -> bool:
    """True if *this* function is still a Capstone naked draft.

    Lookback is bounded to the current definition prologue so a prior naked
    neighbor (common when readable lifts sit just below drafts) does not
    false-positive and hide already-lifted C from the Unicorn queue.
    """
    names = [n for n in (name, f"FUN_{int(addr, 16):08x}") if n]
    target = int(addr, 16)
    for nm in names:
        pat = re.compile(rf"\b{re.escape(nm)}\s*\(")
        for i, line in enumerate(lines):
            if not pat.search(line):
                continue
            # Bound prologue: stop at previous #endif / function close.
            window_start = max(0, i - 14)
            for j in range(i - 1, window_start - 1, -1):
                s = lines[j].strip()
                if s == "#endif" or s == "}":
                    window_start = j + 1
                    break
            before = "\n".join(lines[window_start : i + 1])
            after = "\n".join(lines[i : min(len(lines), i + 20)])
            head = "\n".join(lines[max(0, i - 4) : i + 1])
            # Skip definition sites tagged for a different XBE address.
            mentioned = [int(a, 16) for a in re.findall(r"0x[0-9a-fA-F]+", head)]
            code_addrs = [a for a in mentioned if a >= 0x10000]
            if code_addrs and target not in code_addrs:
                continue
            if re.search(r"readable\s+C\s+lift", head, re.I):
                return False
            if NAKED_ATTR.search(before) or NAKED_ATTR.search(after):
                return True
            if NAKED_MARK.search(before):
                return True
            body = after[:600]
            if ("__asm__" in body or "asm volatile" in body) and (
                ".byte" in body or "naked" in before.lower()
            ):
                return True
            return False
    return False


def inventory_readable(kb: dict) -> List[dict]:
    cache: Dict[Path, List[str]] = {}
    out: List[dict] = []
    for obj in kb.get("objects", []):
        src = obj.get("source") or ""
        sp = resolve_src(src)
        if sp is None:
            continue
        if sp not in cache:
            cache[sp] = sp.read_text(encoding="utf-8", errors="replace").splitlines()
        lines = cache[sp]
        for fn in obj.get("functions") or []:
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            if fn.get("ported") is not False:
                continue
            name = func_name(fn)
            addr = fn["addr"]
            if is_naked_near_def(lines, name, addr):
                continue
            ai = int(addr, 16)
            try:
                rel = str(sp.relative_to(ROOT))
            except ValueError:
                rel = str(sp)
            out.append(
                {
                    "addr": addr,
                    "addr_int": ai,
                    "name": name or f"FUN_{ai:08x}",
                    "source": rel,
                    "fn": fn,
                }
            )

    def size_key(r: dict) -> int:
        p = ORACLE_DIR / f"{r['addr_int']:08x}.obj"
        return p.stat().st_size if p.exists() else 10**9

    out.sort(key=size_key)
    return out


def load_ledger_done() -> Set[str]:
    done: Set[str] = set()
    if not LEDGER.exists():
        return done
    for line in LEDGER.read_text().splitlines():
        line = line.strip()
        if not line:
            continue
        try:
            row = json.loads(line)
        except json.JSONDecodeError:
            continue
        a = row.get("addr")
        if not a:
            continue
        try:
            done.add(hex(int(str(a), 16)))
        except ValueError:
            done.add(str(a))
    return done


def append_ledger(row: dict) -> None:
    LEDGER.parent.mkdir(parents=True, exist_ok=True)
    with LEDGER.open("a", encoding="utf-8") as f:
        f.write(json.dumps(row) + "\n")


SKIP_SRC_PREFIXES = (
    "xdk/",
    "xapilib/",
    "d3d8/",
    "dsound/",
    "xnet/",
    "xgraphic/",
    "bink/",
    "libcmt/",
    "libm/",
    "xmv/",
)

GAMEPLAY_HINTS = (
    "ai/",
    "game/",
    "objects/",
    "units/",
    "items/",
    "physics/",
    "effects/",
    "camera/",
    "input/",
    "main/",
    "scenario/",
    "structures/",
    "sound/",
    "text/",
    "saved",
    "tag_files/",
    "memory/",
    "cseries/",
    "bitmaps/",
    "models/",
    "devices/",
    "cutscene/",
    "cache/",
    "network",
    "shader",
    "math/",
    "collision",
    "hs/",
    "interface",
    "render/",
    "player",
)


def run_unicorn(name: str, addr_int: int, seeds: int, timeout: float = 25.0) -> dict:
    outj = ROOT / "artifacts" / "equivalence" / f"uni_{addr_int:08x}_s{seeds}.json"
    cmd = [
        sys.executable,
        str(ROOT / "tools" / "equivalence" / "unicorn_diff.py"),
        name,
        "--allow-stubs",
        "--seeds",
        str(seeds),
        "-q",
        "--output-json",
        str(outj),
    ]
    t0 = time.time()
    # Stub same-TU sibling calls like the oracle's extern stubs.
    env = os.environ.copy()
    env.setdefault("BIPED_SIBLING_RESOLVE", "1")
    try:
        proc = subprocess.run(
            cmd, cwd=str(ROOT), capture_output=True, text=True, timeout=timeout, env=env
        )
        timed_out = False
    except subprocess.TimeoutExpired as exc:
        timed_out = True
        proc = subprocess.CompletedProcess(
            cmd,
            124,
            (exc.stdout or "") if isinstance(exc.stdout, str) else "",
            (exc.stderr or "") if isinstance(exc.stderr, str) else "timeout",
        )
    dt = time.time() - t0
    text = (proc.stdout or "") + (proc.stderr or "")
    if timed_out:
        text += "\nTIMEOUT\n"
    passed = failed = errors = None
    m = RESULTS_RE.search(text)
    if m:
        passed, failed, errors = map(int, m.groups())
    elif outj.exists():
        try:
            payload = json.loads(outj.read_text())
            passed = payload.get("passed", payload.get("seeds_passed"))
            failed = payload.get("failed", payload.get("seeds_failed"))
            errors = payload.get("errors", payload.get("seeds_errors"))
        except Exception:
            pass
    missing_cand = "missing_build_object" in text or "cannot find build .obj" in text
    return {
        "rc": proc.returncode,
        "passed": passed,
        "failed": failed,
        "errors": errors,
        "dt": round(dt, 2),
        "tail": text[-400:],
        "missing_candidate": missing_cand,
        "timeout": timed_out,
    }


def clear_pass(res: dict, seeds: int) -> bool:
    if res.get("missing_candidate"):
        return False
    p, f, e = res.get("passed"), res.get("failed"), res.get("errors")
    if p is None or f is None or e is None:
        return False
    # HARD RULE: exact Unicorn 100/0/0 (or seeds/0/0); accept timeout rc.
    return f == 0 and e == 0 and p >= int(seeds) and p >= 100


def count_ported(kb: dict) -> Tuple[int, int]:
    t = f = 0
    for obj in kb.get("objects", []):
        for fn in obj.get("functions") or []:
            if not isinstance(fn, dict):
                continue
            if fn.get("ported") is True:
                t += 1
            elif fn.get("ported") is False:
                f += 1
    return t, f


def git_commit_flips(n: int) -> Optional[str]:
    subprocess.run(["git", "add", "kb.json"], cwd=ROOT, check=False)
    leaf = ROOT / "tools" / "equivalence" / "leaf_cache.json"
    if leaf.exists():
        subprocess.run(["git", "add", str(leaf)], cwd=ROOT, check=False)
    msg = f"verify(track-a): unicorn-prove {n} readable-C drafts (ported:true)."
    r = subprocess.run(
        ["git", "commit", "-m", msg],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if r.returncode != 0:
        print("commit failed:", r.stdout, r.stderr, file=sys.stderr)
        return None
    sha = subprocess.run(
        ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
    ).stdout.strip()
    print(f"committed {sha}: {msg}")
    return sha


def git_push() -> None:
    r = subprocess.run(
        ["git", "push", "pastudan", "HEAD"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    sys.stdout.write(r.stdout or "")
    sys.stderr.write(r.stderr or "")
    if r.returncode != 0:
        raise SystemExit("push failed: %s" % r.returncode)


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--limit", type=int, default=0, help="Max new tests (0=all)")
    ap.add_argument("--commit-every", type=int, default=50)
    ap.add_argument("--no-push", action="store_true")
    ap.add_argument("--screen-seeds", type=int, default=50)
    ap.add_argument("--confirm-seeds", type=int, default=100)
    ap.add_argument(
        "--flip-screen-only",
        action="store_true",
        help="Flip on screen pass without 100-seed confirm",
    )
    ap.add_argument(
        "--reconfirm-ledger-passes",
        action="store_true",
        help="Re-run seeds=100 on ledger ok@50 that are still ported:false",
    )
    ap.add_argument(
        "--gameplay-only",
        action="store_true",
        help="Skip xdk/d3d/libcmt/etc.; keep gameplay-ish source paths only",
    )
    ap.add_argument(
        "--timeout",
        type=float,
        default=25.0,
        help="Per unicorn_diff wall-clock timeout seconds (default 25)",
    )
    args = ap.parse_args()

    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    readable = inventory_readable(kb)
    if args.gameplay_only:
        filtered = []
        for r in readable:
            src = (r.get("source") or "").replace("\\", "/").lower()
            if any(p in src for p in SKIP_SRC_PREFIXES):
                continue
            if not any(h in src for h in GAMEPLAY_HINTS):
                continue
            filtered.append(r)
        print(f"gameplay filter: {len(readable)} -> {len(filtered)}")
        readable = filtered
    inv_rows = [{k: v for k, v in r.items() if k != "fn"} for r in readable]
    INV.parent.mkdir(parents=True, exist_ok=True)
    INV.write_text(json.dumps(inv_rows, indent=2) + "\n")
    true0, false0 = count_ported(kb)
    print(f"kb true={true0} false={false0} readable_c_queue={len(readable)}")

    done = load_ledger_done()
    print(f"ledger done={len(done)}")

    # Optionally promote prior screen-only passes still false in kb
    if args.reconfirm_ledger_passes and LEDGER.exists():
        by_addr = {r["addr_int"]: r for r in readable}
        for line in LEDGER.read_text().splitlines():
            if not line.strip():
                continue
            try:
                row = json.loads(line)
            except json.JSONDecodeError:
                continue
            if not row.get("ok"):
                continue
            try:
                ai = int(str(row["addr"]), 16)
            except (KeyError, ValueError):
                continue
            r = by_addr.get(ai)
            if r is None:
                continue
            print(f"RECONFIRM {hex(ai)} {r['name']}")
            res100 = run_unicorn(r["name"], ai, args.confirm_seeds, timeout=args.timeout)
            if clear_pass(res100, args.confirm_seeds):
                r["fn"]["ported"] = True
                append_ledger(
                    {
                        "addr": hex(ai),
                        "name": r["name"],
                        "ok": True,
                        "phase": "reconfirm100",
                        **{
                            k: res100[k]
                            for k in ("rc", "passed", "failed", "errors", "dt", "tail")
                        },
                    }
                )
                print(f"  PASS100 {res100.get('passed')}")
            else:
                append_ledger(
                    {
                        "addr": hex(ai),
                        "name": r["name"],
                        "ok": False,
                        "phase": "reconfirm100",
                        **{
                            k: res100[k]
                            for k in ("rc", "passed", "failed", "errors", "dt", "tail")
                        },
                    }
                )
                print(
                    f"  FAIL100 {res100.get('passed')}/{res100.get('failed')}/{res100.get('errors')}"
                )
        # drop confirmed from done-skip? they stay in ledger; readable rebuild after save
        KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        # refresh inventory after flips
        readable = inventory_readable(kb)
        done = load_ledger_done()

    stats: Counter = Counter()
    pending_flips: List[str] = []
    total_flips_session = 0
    tested = 0

    for r in readable:
        ah = hex(r["addr_int"])
        if ah in done:
            stats["skip_ledger"] += 1
            continue
        oracle = ORACLE_DIR / f"{r['addr_int']:08x}.obj"
        if not oracle.exists():
            stats["no_oracle"] += 1
            append_ledger(
                {
                    "addr": ah,
                    "name": r["name"],
                    "rc": 2,
                    "passed": 0,
                    "failed": 0,
                    "errors": 0,
                    "ok": False,
                    "phase": "no_oracle",
                    "dt": 0,
                }
            )
            done.add(ah)
            continue

        res50 = run_unicorn(r["name"], r["addr_int"], args.screen_seeds, timeout=args.timeout)
        if res50.get("missing_candidate"):
            stats["missing_candidate"] += 1
            append_ledger(
                {
                    "addr": ah,
                    "name": r["name"],
                    "ok": False,
                    "phase": "missing_candidate",
                    **{
                        k: res50[k]
                        for k in ("rc", "passed", "failed", "errors", "dt", "tail")
                    },
                }
            )
            done.add(ah)
            tested += 1
            print(f"SKIP-CAND {ah} {r['name']}")
            if args.limit and tested >= args.limit:
                break
            continue

        screen_ok = clear_pass(res50, args.screen_seeds)
        if not screen_ok:
            if (res50.get("failed") or 0) > 0:
                stats["fail"] += 1
                tag = "FAIL"
            else:
                stats["error"] += 1
                tag = "ERR"
            append_ledger(
                {
                    "addr": ah,
                    "name": r["name"],
                    "ok": False,
                    "phase": "screen%d" % args.screen_seeds,
                    **{
                        k: res50[k]
                        for k in ("rc", "passed", "failed", "errors", "dt", "tail")
                    },
                }
            )
            done.add(ah)
            tested += 1
            print(
                f"{tag} {ah} {r['name']} "
                f"{res50.get('passed')}/{res50.get('failed')}/{res50.get('errors')} "
                f"{res50['dt']}s"
            )
            if args.limit and tested >= args.limit:
                break
            continue

        if args.flip_screen_only:
            confirm_ok = True
            res100 = res50
            phase = "screen%d" % args.screen_seeds
        else:
            res100 = run_unicorn(
                r["name"], r["addr_int"], args.confirm_seeds, timeout=args.timeout
            )
            confirm_ok = clear_pass(res100, args.confirm_seeds)
            phase = "confirm%d" % args.confirm_seeds

        if confirm_ok:
            sp = ROOT / r["source"]
            lines = sp.read_text(encoding="utf-8", errors="replace").splitlines()
            if is_naked_near_def(lines, r["name"], r["addr"]):
                stats["naked_blocked"] += 1
                append_ledger(
                    {
                        "addr": ah,
                        "name": r["name"],
                        "ok": False,
                        "phase": "naked_blocked",
                        **{
                            k: res100[k]
                            for k in ("rc", "passed", "failed", "errors", "dt", "tail")
                        },
                    }
                )
                done.add(ah)
                tested += 1
                print(f"NAKED-BLOCK {ah} {r['name']}")
                if args.limit and tested >= args.limit:
                    break
                continue
            stats["pass"] += 1
            r["fn"]["ported"] = True
            pending_flips.append(ah)
            total_flips_session += 1
            append_ledger(
                {
                    "addr": ah,
                    "name": r["name"],
                    "ok": True,
                    "phase": phase,
                    "screen": {
                        k: res50[k] for k in ("passed", "failed", "errors", "dt")
                    },
                    **{
                        k: res100[k]
                        for k in ("rc", "passed", "failed", "errors", "dt", "tail")
                    },
                }
            )
            done.add(ah)
            tested += 1
            print(
                f"PASS {ah} {r['name']} "
                f"{res100.get('passed')}/{res100.get('failed')}/{res100.get('errors')} "
                f"confirm={res100['dt']}s"
            )
            if len(pending_flips) >= args.commit_every:
                KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
                sha = git_commit_flips(len(pending_flips))
                if sha and not args.no_push:
                    git_push()
                pending_flips.clear()
        else:
            stats["confirm_fail"] += 1
            append_ledger(
                {
                    "addr": ah,
                    "name": r["name"],
                    "ok": False,
                    "phase": phase,
                    "screen": {
                        k: res50[k] for k in ("passed", "failed", "errors", "dt")
                    },
                    **{
                        k: res100[k]
                        for k in ("rc", "passed", "failed", "errors", "dt", "tail")
                    },
                }
            )
            done.add(ah)
            tested += 1
            print(
                f"CONFIRM-FAIL {ah} {r['name']} "
                f"{res100.get('passed')}/{res100.get('failed')}/{res100.get('errors')}"
            )

        if args.limit and tested >= args.limit:
            break

    if pending_flips:
        KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        sha = git_commit_flips(len(pending_flips))
        if sha and not args.no_push:
            git_push()

    true1, false1 = count_ported(kb)
    print("=== CAMPAIGN DONE ===")
    print("stats", dict(stats))
    print(f"session_flips={total_flips_session} tested={tested}")
    print(f"kb true={true1} false={false1}")
    head = subprocess.run(
        ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
    ).stdout.strip()
    print(f"HEAD={head}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
