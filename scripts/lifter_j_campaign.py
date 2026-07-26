#!/usr/bin/env python3
"""Lifter J focused campaign: sound/ tag_files/ saved_games/ devices/ models/ only."""
from __future__ import annotations

import argparse
import json
import os
import subprocess
import sys
import time
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
sys.path.insert(0, str(ROOT / "tools" / "equivalence"))

from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
    func_name,
    git_push,
    is_naked_near_def,
    resolve_src,
    run_unicorn,
)
from lift_inventory_batch4 import find_naked_block  # noqa: E402
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
import importlib.util

PREF = ("sound/", "tag_files/", "saved_games/", "devices/", "models/")
UID, GID = os.getuid(), os.getgid()

spec = importlib.util.spec_from_file_location("lifter_j", ROOT / "scripts" / "lifter_j.py")
lj = importlib.util.module_from_spec(spec)
spec.loader.exec_module(lj)


def in_pref(src: str) -> bool:
    s = (src or "").replace("\\", "/")
    return any(p in s for p in PREF)


def set_kb_decl(addr: int, decl: str) -> None:
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    for o in kb.get("objects", []):
        for fn in o.get("functions") or []:
            if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == addr:
                fn["decl"] = decl
                KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
                return


def regen_decl_h() -> bool:
    r = subprocess.run(
        [
            "docker",
            "run",
            "--rm",
            "-u",
            f"{UID}:{GID}",
            "-v",
            f"{ROOT}:/work",
            "-w",
            "/work",
            "halo-re-build:latest",
            "bash",
            "-c",
            "cmake --build build --target import_libs_target --parallel 1 >/tmp/imp.log 2>&1; tail -3 /tmp/imp.log",
        ],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    return (ROOT / "build" / "generated" / "decl.h").exists() and r.returncode == 0


def docker_compile(src: str) -> bool:
    src = src.replace("\\", "/")
    if src.startswith("src/halo/"):
        src = src[len("src/halo/") :]
    cmake_obj = ROOT / "build" / "CMakeFiles" / "halo.dir" / "src" / "halo" / f"{src}.obj"
    cmake_obj.parent.mkdir(parents=True, exist_ok=True)
    (ROOT / "build" / "equivalence").mkdir(parents=True, exist_ok=True)
    base = Path(src).name
    cmd = f"""
set -e
clang -Wall -Wno-unused-function -Wno-unused-variable -Wno-unused-parameter \
  -target i386-pc-win32 -march=pentium3 -mno-sse -nostdlib -ffreestanding \
  -fno-builtin -fno-exceptions -mstack-probe-size=65536 \
  -I/work/src -I/work/third_party/xbox -I/work/build/generated \
  -include /work/src/common.h \
  -c /work/src/halo/{src} -o /work/build/equivalence/{base}.obj
mkdir -p $(dirname /work/build/CMakeFiles/halo.dir/src/halo/{src}.obj)
cp /work/build/equivalence/{base}.obj /work/build/CMakeFiles/halo.dir/src/halo/{src}.obj
"""
    r = subprocess.run(
        [
            "docker",
            "run",
            "--rm",
            "-u",
            f"{UID}:{GID}",
            "-v",
            f"{ROOT}:/work",
            "-w",
            "/work",
            "halo-re-build:latest",
            "bash",
            "-c",
            cmd,
        ],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if r.returncode != 0:
        print("compile FAIL", src, (r.stderr or r.stdout)[-600:], flush=True)
        return False
    return True


def raw_ok() -> bool:
    r = subprocess.run(
        [sys.executable, str(ROOT / "tools/audit/check_raw_casts.py")],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if r.returncode != 0:
        print(r.stderr or r.stdout, flush=True)
    return r.returncode == 0


def merge_remote_kb() -> None:
    lj.merge_remote_kb()


def commit_chunk(n: int, paths: set[Path], do_push: bool) -> str | None:
    merge_remote_kb()
    for p in paths:
        subprocess.run(["git", "add", str(p)], cwd=ROOT, check=False)
    subprocess.run(
        [
            "git",
            "add",
            "kb.json",
            "tools/equivalence/leaf_cache.json",
            "scripts/lifter_j.py",
            "scripts/lifter_j_campaign.py",
        ],
        cwd=ROOT,
        check=False,
    )
    subprocess.run(["git", "add", "-u", "src/halo"], cwd=ROOT, check=False)
    msg = f"lift(track-a): Lifter J naked→C + Unicorn-prove {n} (ported:true)."
    r = subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print("commit failed", r.stdout, r.stderr, flush=True)
        return None
    sha = subprocess.run(
        ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
    ).stdout.strip()
    if do_push:
        subprocess.run(
            ["git", "pull", "--rebase", "pastudan", "track-a-collision-bsp"],
            cwd=ROOT,
            capture_output=True,
            check=False,
        )
        merge_remote_kb()
        st = subprocess.run(
            ["git", "status", "--porcelain", "kb.json"],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
        if st.stdout.strip():
            subprocess.run(["git", "add", "kb.json"], cwd=ROOT, check=False)
            subprocess.run(
                [
                    "git",
                    "commit",
                    "-m",
                    "fix(track-a): union concurrent ported:true into Lifter J kb.",
                ],
                cwd=ROOT,
                capture_output=True,
                check=False,
            )
            sha = subprocess.run(
                ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
            ).stdout.strip()
        git_push()
        print(f"COMMIT+PUSH {sha}", flush=True)
    return sha


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--seeds", type=int, default=100)
    ap.add_argument("--timeout", type=float, default=50.0)
    ap.add_argument("--commit-every", type=int, default=5)
    ap.add_argument("--no-push", action="store_true")
    args = ap.parse_args()

    merge_remote_kb()
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    true0, false0 = count_ported(kb)
    ported, src_by, name_by = {}, {}, {}
    for o in kb.get("objects", []):
        src = o.get("source") or ""
        for fn in o.get("functions") or []:
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            ai = int(fn["addr"], 16)
            ported[ai] = fn.get("ported")
            src_by[ai] = src
            name_by[ai] = func_name(fn) or f"FUN_{ai:08x}"

    by_src: dict[str, list[dict]] = defaultdict(list)
    for ai, tup in sorted(lj.HAND.items()):
        src, name, body = tup[0], tup[1], tup[2]
        decl = tup[3] if len(tup) > 3 else None
        if ported.get(ai) is not False:
            continue
        if not in_pref(src_by.get(ai, src)):
            continue
        # skip known-bad
        if ai == 0x96850:
            continue
        by_src[src_by.get(ai, src)].append(
            {
                "addr": ai,
                "name": name_by.get(ai, name),
                "body": body,
                "decl": decl,
            }
        )

    # prove-only leftovers in focus that are already readable
    from unicorn_c_campaign import inventory_readable

    for r in inventory_readable(kb):
        if not in_pref(r["source"]):
            continue
        src = r["source"].replace("\\", "/")
        if "src/halo/" in src:
            src = src.split("src/halo/", 1)[1]
        if any(j["addr"] == r["addr_int"] for j in by_src.get(src, [])):
            continue
        by_src[src].append(
            {"addr": r["addr_int"], "name": r["name"], "body": None, "decl": None}
        )

    print(
        f"j-focus jobs={sum(len(v) for v in by_src.values())} files={len(by_src)} "
        f"true={true0} false={false0}",
        flush=True,
    )

    flips: list[str] = []
    shas: list[str] = []
    touched: set[Path] = set()
    since = 0

    for src, jobs in sorted(by_src.items()):
        path = resolve_src(src)
        if path is None:
            continue
        backup = path.read_text(encoding="utf-8", errors="replace")
        decl_changed = False
        applied = []
        for job in jobs:
            ai, name, body, decl = job["addr"], job["name"], job["body"], job["decl"]
            if decl:
                set_kb_decl(ai, decl)
                decl_changed = True
            if body is None:
                applied.append(job)
                continue
            text = path.read_text(encoding="utf-8", errors="replace")
            if not is_naked_near_def(text.splitlines(), name, hex(ai)):
                applied.append({**job, "body": None})
                continue
            span = find_naked_block(text, name, ai) or find_naked_block(
                text, f"FUN_{ai:08x}", ai
            )
            if not span:
                print(f"locate FAIL {hex(ai)} {name}", flush=True)
                continue
            path.write_text(
                text[: span[0]] + body + "\n" + text[span[1] :], encoding="utf-8"
            )
            applied.append(job)
            print(f"applied {hex(ai)} {name}", flush=True)

        if not applied:
            continue
        # Sync decls from applied C bodies so decl.h matches lift signatures.
        import re as _re
        for job in applied:
            body = job.get("body")
            if not body:
                continue
            m = _re.search(
                rf"^([\w\s\*]+?\b{_re.escape(job['name'])}\s*\([^{{]*\))",
                body,
                _re.M,
            )
            if m:
                set_kb_decl(job["addr"], m.group(1).strip() + ";")
                decl_changed = True
        if decl_changed and not regen_decl_h():
            path.write_text(backup, encoding="utf-8")
            continue
        if not docker_compile(src):
            path.write_text(backup, encoding="utf-8")
            continue
        if not raw_ok():
            path.write_text(backup, encoding="utf-8")
            continue

        for job in applied:
            ai, name = job["addr"], job["name"]
            print(f"\n== {hex(ai)} {name} ({src}) ==", flush=True)
            if not ensure_oracle(ai):
                print("oracle FAIL", flush=True)
                continue
            t0 = time.time()
            res = run_unicorn(name, ai, args.seeds, timeout=args.timeout)
            if not clear_pass(res, args.seeds):
                res2 = run_unicorn(hex(ai), ai, args.seeds, timeout=args.timeout)
                if clear_pass(res2, args.seeds) or (res2.get("passed") or 0) > (
                    res.get("passed") or 0
                ):
                    res = res2
            ok = clear_pass(res, args.seeds)
            print(
                f"  unicorn {res.get('passed')}/{res.get('failed')}/{res.get('errors')} "
                f"ok={ok} dt={time.time()-t0:.1f}",
                flush=True,
            )
            append_ledger(
                {
                    "addr": hex(ai),
                    "name": name,
                    "ok": ok,
                    "lifter": "lifter_j",
                    "passed": res.get("passed"),
                    "failed": res.get("failed"),
                    "errors": res.get("errors"),
                }
            )
            if not ok:
                continue
            if not raw_ok():
                continue
            kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
            if flip_kb(kb, ai):
                KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
                flips.append(hex(ai))
                since += 1
                touched.add(path)
                print(f"  FLIP total={len(flips)}", flush=True)
            if args.commit_every and since >= args.commit_every:
                sha = commit_chunk(since, touched, do_push=not args.no_push)
                if sha:
                    shas.append(sha)
                since = 0
                touched.clear()

    if since:
        sha = commit_chunk(since, touched, do_push=not args.no_push)
        if sha:
            shas.append(sha)

    true1, false1 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    summary = {
        "proven": len(flips),
        "flips": flips,
        "shas": shas,
        "true0": true0,
        "true1": true1,
        "false0": false0,
        "false1": false1,
        "head": subprocess.run(
            ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
        ).stdout.strip(),
    }
    Path("/tmp/lifter_j_summary.json").write_text(json.dumps(summary, indent=2))
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
