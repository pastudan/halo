#!/usr/bin/env python3
"""Domain grind: bitmaps/ai/interface/sound/cache/text/game + Unicorn."""
from __future__ import annotations
import argparse, json, re, subprocess, sys, time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
sys.path.insert(0, str(ROOT / "tools" / "equivalence"))

from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe
from xbe_to_coff import load_kb, xbe_bytes
from lift_inventory_batch4 import find_naked_block
from prove_inventory_batch4 import ensure_oracle, flip_kb
from unicorn_c_campaign import (
    KB_PATH, append_ledger, clear_pass, count_ported, func_name,
    git_push, is_naked_near_def, resolve_src, run_unicorn,
)
from tu_compile import docker_compile, regen_decl_h
import lift_assert_wrappers as law
import lift_thin_wrappers as ltw
import lift_jmp_thunks as jt
import lift_ai_campaign as lac
import lifter_interface as iface
import lifter_j as lj

DOMS = ("bitmaps/", "ai/", "interface/", "sound/", "cache/", "text/", "game/")
SKIP = ("xdk/", "libcmt", "bink", "d3d", "dsound", "xnet", "xapilib", "kb_common")
COMMIT_EVERY = 8


def in_dom(src: str) -> bool:
    s = (src or "").replace("\\", "/")
    if any(x in s.lower() for x in SKIP):
        return False
    return any(d in s for d in DOMS)


def set_decl(addr: int, decl: str) -> None:
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    if not decl.endswith(";"):
        decl += ";"
    for o in kb.get("objects", []):
        for fn in o.get("functions") or []:
            if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == addr:
                fn["decl"] = decl
                KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
                return


def merge_remote() -> None:
    subprocess.run(["git", "fetch", "pastudan", "track-a-collision-bsp"], cwd=ROOT, capture_output=True)
    r = subprocess.run(["git", "show", "pastudan/track-a-collision-bsp:kb.json"], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0 or not r.stdout:
        return
    theirs = json.loads(r.stdout)
    ours = json.loads(KB_PATH.read_text(encoding="utf-8"))
    tmap = {int(fn["addr"], 16) for o in theirs.get("objects", []) for fn in o.get("functions") or [] if isinstance(fn, dict) and fn.get("addr") and fn.get("ported") is True}
    n = 0
    for o in ours.get("objects", []):
        for fn in o.get("functions") or []:
            if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) in tmap and fn.get("ported") is not True:
                fn["ported"] = True
                n += 1
    if n:
        KB_PATH.write_text(json.dumps(ours, indent=2) + "\n", encoding="utf-8")
        print(f"merged {n} remote ported:true", flush=True)


def commit_chunk(n: int, touched: set, do_push: bool):
    merge_remote()
    files = ["kb.json", "scripts/lift_domains_campaign.py", "tools/equivalence/leaf_cache.json"]
    for p in touched:
        try:
            files.append(str(p.relative_to(ROOT)))
        except ValueError:
            files.append(str(p))
    subprocess.run(["git", "add"] + files, cwd=ROOT, check=False)
    subprocess.run(["git", "add", "-u", "src/halo"], cwd=ROOT, check=False)
    msg = f"lift(track-a): domains naked→C + Unicorn-prove {n} (ported:true)."
    r = subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print("commit failed", r.stdout, r.stderr, flush=True)
        return None
    sha = subprocess.run(["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True).stdout.strip()
    if do_push:
        # push this branch tip to pastudan track-a-collision-bsp via rebase merge
        subprocess.run(["git", "fetch", "pastudan", "track-a-collision-bsp"], cwd=ROOT, capture_output=True)
        subprocess.run(["git", "pull", "--rebase", "pastudan", "track-a-collision-bsp"], cwd=ROOT, capture_output=True)
        r = subprocess.run(["git", "push", "pastudan", "HEAD:track-a-collision-bsp"], cwd=ROOT, capture_output=True, text=True)
        print(r.stdout, r.stderr, flush=True)
    print(f"COMMIT+PUSH {sha}", flush=True)
    return sha


def emit_body(ops, decl, name, name_by, src):
    if ops[-1][0] in ("ret", "retn"):
        for fn, tag in (
            (lambda: law.try_emit(ops, decl, name, name_by), "assert"),
            (lambda: ltw.try_emit([f"{m} {o}".strip() for m, o in ops], decl, name, name_by), "thin"),
            (lambda: iface.try_pattern_emit(ops, decl, name, name_by), "ipat"),
            (lambda: lj.try_pattern_emit(ops, decl, name, name_by), "jpat"),
        ):
            b = fn()
            if b:
                return b, tag
    got = jt.try_emit_thunk(ops, decl, name, name_by)
    if got:
        return got[0], "jmp"
    if (src or "").startswith("ai/"):
        if ops[-1][0] == "jmp":
            b, d = lac._emit_encounter_force_ops(ops, decl, name, name_by)
            if b:
                return b, "ai-jmp"
        b, d = lac.try_emit_ai(ops, decl, name, name_by)
        if b:
            return b, "ai"
    return None, None


def collect(max_size, prove_readable, prefer_ported_jmp):
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    name_by, decl_by, src_by, ported = {}, {}, {}, {}
    for o in kb.get("objects", []):
        src = o.get("source") or ""
        for fn in o.get("functions") or []:
            if isinstance(fn, dict) and fn.get("addr"):
                ai = int(fn["addr"], 16)
                name_by[ai] = func_name(fn) or f"FUN_{ai:08x}"
                decl_by[ai] = fn.get("decl") or ""
                src_by[ai] = src
                ported[ai] = fn.get("ported")
    _, starts = load_kb(KB_PATH)
    xbe = Xbe((ROOT / "halo-patched" / "cachebeta.xbe").read_bytes())
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    jobs, seen = [], set()

    for HAND, tag in ((iface.HAND, "iface"), (lj.HAND, "jhand")):
        for ai, tup in HAND.items():
            if ai in seen or ported.get(ai) is not False:
                continue
            src, name, body = tup[0], tup[1], tup[2]
            decl = tup[3] if len(tup) > 3 else None
            if not in_dom(src):
                continue
            jobs.append(dict(addr=ai, name=name, src=src, kind=tag, body=body, decl=decl))
            seen.add(ai)

    for i, ai in enumerate(starts):
        if ai in seen or ported.get(ai) is not False:
            continue
        src = src_by.get(ai) or ""
        if not in_dom(src):
            continue
        end = starts[i + 1] if i + 1 < len(starts) else ai + max_size
        if end - ai > max_size:
            continue
        sp = resolve_src(src)
        if not sp:
            continue
        name = name_by[ai]
        text = sp.read_text(encoding="utf-8", errors="replace")
        naked = is_naked_near_def(text.splitlines(), name, hex(ai))
        if not naked:
            if prove_readable:
                jobs.append(dict(addr=ai, name=name, src=src, kind="prove", body=None, decl=None))
                seen.add(ai)
            continue
        try:
            raw = xbe_bytes(xbe, ai, min(end, ai + max_size) - ai)
        except Exception:
            continue
        ops, term = [], False
        for insn in md.disasm(raw, ai):
            ops.append((insn.mnemonic, insn.op_str))
            if insn.mnemonic in ("ret", "retn") or (insn.mnemonic == "jmp" and len(ops) <= 14):
                term = True
                break
        if not term:
            continue
        decl = decl_by.get(ai) or f"void {name}(void);"
        body, kind = emit_body(ops, decl, name, name_by, src)
        if not body:
            continue
        if prefer_ported_jmp and kind == "jmp":
            got = jt.try_emit_thunk(ops, decl, name, name_by)
            if got and ported.get(got[1]) is not True:
                continue
        if re.search(r"\(\s*(void|int|char|[^*)]+)\s*\(\s*\*", body):
            continue
        jobs.append(dict(addr=ai, name=name, src=src, kind=kind or "pat", body=body, decl=body.split("{", 1)[0].strip() + ";"))
        seen.add(ai)

    rank = {"iface": 0, "jhand": 0, "jmp": 1, "ai-jmp": 1, "ai": 1, "assert": 1, "thin": 1, "ipat": 1, "jpat": 1, "prove": 2}
    jobs.sort(key=lambda j: (rank.get(j["kind"], 1), j["addr"]))
    return jobs


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--target", type=int, default=80)
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--commit-every", type=int, default=COMMIT_EVERY)
    ap.add_argument("--seeds", type=int, default=100)
    ap.add_argument("--timeout", type=float, default=55.0)
    ap.add_argument("--max-size", type=int, default=200)
    ap.add_argument("--no-push", action="store_true")
    ap.add_argument("--no-prove-readable", action="store_true")
    ap.add_argument("--prefer-ported-jmp", action="store_true", default=True)
    args = ap.parse_args()

    merge_remote()
    true0, false0 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    jobs = collect(args.max_size, not args.no_prove_readable, args.prefer_ported_jmp)
    if args.limit:
        jobs = jobs[: args.limit]
    print(
        f"domains jobs={len(jobs)} "
        f"hand={sum(1 for j in jobs if j['kind'] in ('iface','jhand'))} "
        f"lift={sum(1 for j in jobs if j['kind'] not in ('iface','jhand','prove'))} "
        f"prove={sum(1 for j in jobs if j['kind']=='prove')} "
        f"true={true0} false={false0} target={args.target}",
        flush=True,
    )

    flips, shas, touched, since = [], [], set(), 0
    for job in jobs:
        if len(flips) >= args.target:
            break
        ai, name, kind, src = job["addr"], job["name"], job["kind"], job["src"]
        print(f"\n== {hex(ai)} {name} [{kind}] ({src}) ==", flush=True)
        path = resolve_src(src)
        if path is None:
            continue
        orig = path.read_text(encoding="utf-8", errors="replace")
        wrote = False
        if job.get("body") and is_naked_near_def(orig.splitlines(), name, hex(ai)):
            if job.get("decl"):
                set_decl(ai, job["decl"])
                regen_decl_h()
            span = find_naked_block(orig, name, ai) or find_naked_block(orig, f"FUN_{ai:08x}", ai)
            if not span:
                print("  locate FAIL", flush=True)
                continue
            body = job["body"]
            if "readable C lift" not in body:
                body = f"/* {name} (0x{ai:x}) — readable C lift. */\n{body}"
            new = orig[: span[0]] + body + "\n" + orig[span[1] :]
            if any(t in body for t in ("uint8_t", "uint16_t", "int8_t", "int16_t")) and "#include <stdint.h>" not in new:
                new = "#include <stdint.h>\n" + new
            path.write_text(new, encoding="utf-8")
            wrote = True
            touched.add(path)
            for stale in (ROOT / "build").rglob(path.name + ".obj"):
                try:
                    stale.unlink()
                except OSError:
                    pass

        rel = src.replace("\\", "/")
        if "src/halo/" in rel:
            rel = rel.split("src/halo/", 1)[1]
        if not docker_compile(rel):
            print("  compile WARN", flush=True)

        if not ensure_oracle(ai):
            if wrote:
                path.write_text(orig, encoding="utf-8")
            print("  oracle FAIL", flush=True)
            continue

        t0 = time.time()
        res = run_unicorn(hex(ai), ai, args.seeds, timeout=args.timeout)
        ok = clear_pass(res, args.seeds)
        if not ok:
            res2 = run_unicorn(name, ai, args.seeds, timeout=args.timeout)
            if clear_pass(res2, args.seeds) or (res2.get("passed") or 0) > (res.get("passed") or 0):
                res = res2
                ok = clear_pass(res, args.seeds)
        print(
            f"  unicorn {res.get('passed')}/{res.get('failed')}/{res.get('errors')} ok={ok} dt={time.time()-t0:.1f}",
            flush=True,
        )
        append_ledger({"addr": hex(ai), "name": name, "ok": ok, "phase": f"{kind}_{args.seeds}", "lifter": "lift_domains",
                       "passed": res.get("passed"), "failed": res.get("failed"), "errors": res.get("errors")})
        if not ok:
            if wrote:
                path.write_text(orig, encoding="utf-8")
                print("  REVERT", flush=True)
            continue
        rc = subprocess.run([sys.executable, str(ROOT / "tools/audit/check_raw_casts.py")], cwd=ROOT, capture_output=True, text=True)
        if rc.returncode != 0:
            if wrote:
                path.write_text(orig, encoding="utf-8")
            print("  REVERT raw-cast", flush=True)
            continue
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if flip_kb(kb, ai):
            flips.append(hex(ai))
            since += 1
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
            print(f"  FLIP {hex(ai)} total={len(flips)}", flush=True)
        if args.commit_every and since >= args.commit_every:
            sha = commit_chunk(since, touched, not args.no_push)
            if sha:
                shas.append(sha)
            since = 0
            touched.clear()

    if since:
        sha = commit_chunk(since, touched, not args.no_push)
        if sha:
            shas.append(sha)

    true1, false1 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    summary = dict(proven=len(flips), flips=flips, shas=shas, true0=true0, true1=true1, false0=false0, false1=false1, delta=true1 - true0)
    Path("/tmp/lift_domains_summary.json").write_text(json.dumps(summary, indent=2))
    print("DONE", summary, flush=True)
    return 0 if summary["delta"] >= args.target or len(flips) >= args.target else 1


if __name__ == "__main__":
    raise SystemExit(main())
