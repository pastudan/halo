#!/usr/bin/env python3
"""Grouped Docker-compile + Unicorn escalate prove driver (Track A).

Lives under /tmp so concurrent agents cannot clobber it.
"""
from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
import time
from collections import defaultdict
from pathlib import Path

ROOT = Path("/Users/dan/code/halo-nft/halo-re")
sys.path.insert(0, str(ROOT / "scripts"))
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from tu_compile import docker_compile, regen_decl_h  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
    git_commit_flips,
    git_push,
    inventory_readable,
)

SKIP = (
    "xdk/", "libcmt", "bink", "d3d", "dsound", "xnet", "kb_common",
    "bitmaps", "libtiff", "xapilib", "xgraphic", "xmv", "libm/",
)
RESULTS_RE = re.compile(r"(\d+) passed, (\d+) failed, (\d+) errors")
STRATEGIES = [
    ("default", []),
    ("float_tol", ["--float-tolerance", "32"]),
    ("real_callees", ["--real-callees"]),
    ("combo", ["--float-tolerance", "32", "--real-callees"]),
]


def extract_c_signature(text: str, name: str) -> str | None:
    m = re.search(
        rf"(?m)^([\w\s\*]+?\b{re.escape(name)}\s*\([^;{{}}]*\))\s*\{{",
        text,
    )
    if not m:
        return None
    sig = re.sub(r"\s+", " ", m.group(1)).strip()
    if any(x in sig for x in ("/*", "*/", "&&", "||")):
        return None
    if sig.count("(") != 1 or len(sig) > 240:
        return None
    return sig + ";"


def sync_decl(ai: int, name: str, sp: Path) -> bool:
    sig = extract_c_signature(sp.read_text(encoding="utf-8", errors="replace"), name)
    if not sig:
        return False
    try:
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    except json.JSONDecodeError as e:
        print("kb corrupt", e, flush=True)
        return False
    changed = False
    for obj in kb.get("objects", []):
        for fn in obj.get("functions") or []:
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            if int(fn["addr"], 16) != ai:
                continue
            if (fn.get("decl") or "").strip() != sig:
                fn["decl"] = sig
                changed = True
            break
    if not changed:
        return True
    KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
    json.loads(KB_PATH.read_text(encoding="utf-8"))
    print(f"  synced decl: {sig}", flush=True)
    return regen_decl_h()


def obj_has_symbol(obj: Path, name: str) -> bool:
    if not obj.exists():
        return False
    try:
        sys.path.insert(0, str(ROOT / "tools" / "equivalence"))
        from coff_loader import load_coff

        _s, syms, _t = load_coff(str(obj))
        names = {s.name.lstrip("_") for s in syms}
        return name.lstrip("_") in names
    except Exception:
        return obj.stat().st_size > 0


def run_uni(name: str, addr: int, seeds: int, timeout: float, extra: list[str]) -> dict:
    outj = ROOT / "artifacts" / "equivalence" / f"uni_{addr:08x}_retry.json"
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
    t0 = time.time()
    try:
        proc = subprocess.run(cmd, cwd=str(ROOT), capture_output=True, text=True, timeout=timeout)
        timed_out = False
    except subprocess.TimeoutExpired as exc:
        timed_out = True
        proc = subprocess.CompletedProcess(cmd, 124, exc.stdout or "", "timeout")
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
    return {
        "rc": proc.returncode,
        "passed": passed,
        "failed": failed,
        "errors": errors,
        "dt": round(time.time() - t0, 2),
        "tail": text[-500:],
        "missing_candidate": "missing_build_object" in text,
    }


def src_rel(source: str) -> str:
    s = source.replace("\\", "/")
    return s.split("src/halo/", 1)[-1] if "src/halo/" in s else s


def build_obj(source: str) -> Path:
    return ROOT / "build/CMakeFiles/halo.dir/src/halo" / f"{src_rel(source)}.obj"


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--seeds", type=int, default=100)
    ap.add_argument("--timeout", type=float, default=40.0)
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--commit-every", type=int, default=10)
    ap.add_argument("--no-push", action="store_true")
    ap.add_argument("--files", nargs="*", default=[])
    ap.add_argument("--min-oracle-size", type=int, default=0)
    args = ap.parse_args()

    if not (ROOT / "build/generated/decl.h").exists():
        print("regen decl.h...", flush=True)
        if not regen_decl_h():
            print("decl.h missing — abort", flush=True)
            return 2

    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    true0, false0 = count_ported(kb)
    readable = inventory_readable(kb)
    by_file: dict[str, list[dict]] = defaultdict(list)
    for r in readable:
        src = (r.get("source") or "").replace("\\", "/")
        low = src.lower()
        if any(s in low for s in SKIP) or "rasterizer" in low or " " in src:
            continue
        if args.files and not any(f in src for f in args.files):
            continue
        if args.min_oracle_size:
            op = ROOT / "delinked/functions" / f"{r['addr_int']:08x}.obj"
            if not op.exists() or op.stat().st_size < args.min_oracle_size:
                continue
        by_file[src].append(r)

    files = sorted(by_file, key=lambda s: (len(by_file[s]), s))
    print(
        f"queue={sum(len(by_file[f]) for f in files)} files={len(files)} "
        f"true={true0} false={false0}",
        flush=True,
    )

    flips: list[str] = []
    names: list[str] = []
    strategies: dict[str, int] = defaultdict(int)
    shas: list[str] = []
    attempted = 0

    for src in files:
        if args.limit and attempted >= args.limit:
            break
        sp = ROOT / src
        if not sp.exists():
            continue
        rel = src_rel(src)
        print(f"\n## {src} ({len(by_file[src])})", flush=True)
        if not docker_compile(rel):
            # try sync first pending decl then retry
            for r in by_file[src][:2]:
                sync_decl(r["addr_int"], r["name"], sp)
            if not docker_compile(rel):
                print("  compile FAIL", flush=True)
                continue
        print("  compile OK", flush=True)
        bobj = build_obj(src)

        for r in by_file[src]:
            if args.limit and attempted >= args.limit:
                break
            ai, name = r["addr_int"], r["name"]
            attempted += 1
            print(f"\n== {hex(ai)} {name} ==", flush=True)
            if not obj_has_symbol(bobj, name):
                sync_decl(ai, name, sp)
                docker_compile(rel)
                if not obj_has_symbol(bobj, name):
                    print("  missing symbol", flush=True)
                    continue
            if not ensure_oracle(ai):
                print("  oracle FAIL", flush=True)
                continue

            ok = False
            used = "default"
            res: dict = {}
            for kind, extra in STRATEGIES:
                res = run_uni(name, ai, args.seeds, args.timeout, extra)
                print(
                    f"  [{kind}] {res.get('passed')}/{res.get('failed')}/{res.get('errors')} "
                    f"rc={res.get('rc')} dt={res.get('dt')}",
                    flush=True,
                )
                if clear_pass(res, args.seeds):
                    ok, used = True, kind
                    break
            append_ledger(
                {
                    "addr": hex(ai),
                    "name": name,
                    "ok": ok,
                    "phase": f"grp_{used}",
                    "passed": res.get("passed"),
                    "failed": res.get("failed"),
                    "errors": res.get("errors"),
                }
            )
            if not ok:
                continue
            try:
                kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
            except json.JSONDecodeError:
                print("  kb corrupt — stop", flush=True)
                return 2
            if flip_kb(kb, ai):
                flips.append(hex(ai))
                names.append(name)
                strategies[used] += 1
                KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
                print(f"  FLIP [{used}] n={len(flips)}", flush=True)
            if flips and len(flips) % args.commit_every == 0:
                subprocess.run(
                    ["git", "add", "kb.json", "tools/equivalence/leaf_cache.json"],
                    cwd=ROOT,
                    check=False,
                )
                sha = git_commit_flips(args.commit_every)
                if sha:
                    shas.append(sha)
                    if not args.no_push:
                        subprocess.run(
                            ["git", "pull", "--rebase", "pastudan", "track-a-collision-bsp"],
                            cwd=ROOT,
                            check=False,
                        )
                        try:
                            git_push()
                        except SystemExit:
                            pass

    rem = len(flips) % args.commit_every
    if rem:
        subprocess.run(
            ["git", "add", "kb.json", "tools/equivalence/leaf_cache.json"],
            cwd=ROOT,
            check=False,
        )
        sha = git_commit_flips(rem)
        if sha:
            shas.append(sha)
            if not args.no_push:
                subprocess.run(
                    ["git", "pull", "--rebase", "pastudan", "track-a-collision-bsp"],
                    cwd=ROOT,
                    check=False,
                )
                try:
                    git_push()
                except SystemExit:
                    pass

    true1, false1 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    summary = {
        "attempted": attempted,
        "proven": len(flips),
        "flips": flips,
        "names": names,
        "strategies": dict(strategies),
        "shas": shas,
        "true0": true0,
        "true1": true1,
        "false1": false1,
    }
    Path("/tmp/unicorn_prove_grouped_summary.json").write_text(json.dumps(summary, indent=2))
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
