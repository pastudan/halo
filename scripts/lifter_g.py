#!/usr/bin/env python3
"""Lifter G: preferred-domain naked→C (clang/#else promote + thin lifts) + Unicorn prove."""
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
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
    git_push,
    inventory_readable,
    run_unicorn,
)

PREF = (
    "objects/",
    "units/",
    "items/",
    "physics/",
    "structures/",
    "collision",
    "scenario/",
    "sound/",
    "tag_files/",
    "network",
    "saved games",
    "saved_games",
    "devices/",
    "camera/",
    "game/",
    "interface/",
    "effects/",
    "ai/",
    "cutscene/",
    "cseries/",
    "main/",
    "text/",
    "bungie_net/",
    "input/",
    "models/",
    "memory/",
    "cache/",
    "math/",
    "render/",
    "hs/",
)
LEDGER_TAG = "lifter_g"

# Readonly float pools → literals (Unicorn does not always seed absolute .rdata).
FLOAT_LIT: dict[int, str] = {
    0x25337C: "0.25f",
    0x253394: "30.0f",
    0x253398: "0.5f",
    0x2533C0: "0.0f",
    0x2533C8: "1.0f",
    0x2533D8: "4.0f",
    0x2533E4: "0.3f",
    0x2533E8: "0.05f",
    0x2533EC: "1.5f",
    0x2533F0: "0.8f",
    0x253524: "0.4f",
    0x253F3C: "0.6f",
    0x253F40: "2.0f",
    0x253F44: "0.0001f",
    0x254640: "6.0f",
    0x2546A4: "0.033333335f",
    0x25496C: "0.1f",
    0x2549D4: "0.2f",
    0x254A58: "0.7853982f",
    0x254CC0: "15.0f",
    0x254E04: "2.5f",
    0x254E6C: "3.3333333f",
    0x255A54: "6.2831855f",
    0x255B9C: "1.3f",
    0x255BA4: "-0.2f",
    0x255CA0: "0.02f",
    0x255D90: "0.0625f",
    0x255E94: "-1.0f",
    0x255EF8: "0.001f",
    0x25686C: "-1.4f",
    0x256870: "1.4f",
    0x2568BC: "1.5707964f",
    0x256980: "3.1415927f",
    0x259EC0: "0.33333334f",
    0x25ACF0: "50.0f",
    0x25AFCC: "0.75f",
    0x25BB10: "0.01f",
    0x25E884: "-0.1f",
    0x2602C8: "255.0f",
}


def rewrite_float_abs(body: str) -> str:
    def repl(m: re.Match) -> str:
        addr = int(m.group(1), 16)
        lit = FLOAT_LIT.get(addr)
        return lit if lit is not None else m.group(0)

    return re.sub(r"\*\(\s*float\s*\*\s*\)\s*0x([0-9a-fA-F]+)", repl, body)


def safe_flip(addr: int) -> bool:
    """Flip one addr True without rewriting unrelated kb state."""
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    if not flip_kb(kb, addr):
        return False
    KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
    return True


def resolve_src(src: str) -> Path | None:
    src = src.replace("\\", "/")
    if src.startswith("src/"):
        p = ROOT / src
        if p.exists():
            return p
        src = src.split("src/halo/", 1)[-1] if "src/halo/" in src else src
    for base in (ROOT / "src" / "halo", ROOT / "src", ROOT):
        p = base / src
        if p.exists():
            return p
    return None


def in_pref(src: str) -> bool:
    s = src.replace("\\", "/")
    return any(p in s for p in PREF)


def commit_chunk(n: int, paths: set[Path], do_push: bool = True) -> str | None:
    # Re-merge any concurrent ported:true before committing.
    try:
        subprocess.run(
            ["git", "fetch", "pastudan", "track-a-collision-bsp"],
            cwd=ROOT,
            capture_output=True,
            check=False,
        )
        remote_kb = subprocess.run(
            ["git", "show", "FETCH_HEAD:kb.json"],
            cwd=ROOT,
            capture_output=True,
            text=True,
            check=False,
        )
        if remote_kb.returncode == 0 and remote_kb.stdout:
            remote = json.loads(remote_kb.stdout)
            local = json.loads(KB_PATH.read_text(encoding="utf-8"))
            rmap = {}
            for o in remote.get("objects", []):
                for fn in o.get("functions") or []:
                    if isinstance(fn, dict) and fn.get("addr") and fn.get("ported") is True:
                        rmap[int(fn["addr"], 16)] = True
            for o in local.get("objects", []):
                for fn in o.get("functions") or []:
                    if not isinstance(fn, dict) or not fn.get("addr"):
                        continue
                    ai = int(fn["addr"], 16)
                    if fn.get("ported") is not True and rmap.get(ai):
                        fn["ported"] = True
            KB_PATH.write_text(json.dumps(local, indent=2) + "\n", encoding="utf-8")
    except Exception as exc:
        print(f"kb merge skip: {exc}", flush=True)

    for p in paths:
        subprocess.run(["git", "add", str(p)], cwd=ROOT, check=False)
    subprocess.run(
        ["git", "add", "kb.json", "tools/equivalence/leaf_cache.json"],
        cwd=ROOT,
        check=False,
    )
    subprocess.run(["git", "add", "-u", "src/halo"], cwd=ROOT, check=False)
    msg = f"lift(track-a): Lifter G naked→C + Unicorn-prove {n} (ported:true)."
    r = subprocess.run(
        ["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True
    )
    if r.returncode != 0:
        print("commit failed:", r.stdout, r.stderr, file=sys.stderr)
        return None
    sha = subprocess.run(
        ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
    ).stdout.strip()
    if do_push:
        # pull --rebase then push to reduce stale overwrites
        subprocess.run(
            ["git", "pull", "--rebase", "pastudan", "track-a-collision-bsp"],
            cwd=ROOT,
            capture_output=True,
            check=False,
        )
        git_push()
        print(f"COMMIT+PUSH {sha}", flush=True)
    else:
        print(f"COMMIT {sha}", flush=True)
    return sha


def collect_promotes(kb: dict) -> list[dict]:
    meta = {}
    for o in kb.get("objects", []):
        src = (o.get("source") or "").replace("\\", "/")
        if not in_pref(src):
            continue
        for fn in o.get("functions") or []:
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            if fn.get("ported") is not False:
                continue
            ai = int(fn["addr"], 16)
            nm = fn.get("name")
            if not nm:
                m = re.search(r"(\w+)\s*\(", fn.get("decl") or "")
                nm = m.group(1) if m else f"FUN_{ai:08x}"
            meta[ai] = {"name": nm, "src": src}

    out: list[dict] = []
    for src in sorted({m["src"] for m in meta.values()}):
        path = resolve_src(src)
        if path is None:
            continue
        lines = path.read_text(encoding="utf-8", errors="replace").splitlines(True)
        i = 0
        while i < len(lines):
            if re.match(r"#if\s+defined\s*\(\s*__clang__\s*\)", lines[i]):
                start_i = i
                c0 = i
                j = i - 1
                while j >= 0 and lines[j].strip() == "":
                    j -= 1
                if j >= 0 and "*/" in lines[j]:
                    k = j
                    while k >= 0 and "/*" not in lines[k]:
                        k -= 1
                    if k >= 0:
                        c0 = k
                depth = 1
                else_i = None
                i += 1
                while i < len(lines) and depth:
                    ln = lines[i]
                    if re.match(r"#if", ln):
                        depth += 1
                    elif re.match(r"#else\b", ln) and depth == 1:
                        else_i = i
                    elif re.match(r"#endif\b", ln):
                        depth -= 1
                        if depth == 0 and else_i is not None:
                            else_body = "".join(lines[else_i + 1 : i])
                            pre = "".join(lines[c0:start_i])
                            am = re.search(r"0x([0-9a-fA-F]+)", pre) or re.search(
                                r"0x([0-9a-fA-F]+)", "".join(lines[start_i:else_i])
                            )
                            ai = int(am.group(1), 16) if am else None
                            if ai is None:
                                mm = re.search(
                                    r"\b([A-Za-z_]\w*)\s*\([^;]*\)\s*\{", else_body
                                )
                                if mm:
                                    for a, info in meta.items():
                                        if info["name"] == mm.group(1):
                                            ai = a
                                            break
                            if (
                                ai is not None
                                and ai in meta
                                and "naked" not in else_body
                                and else_body.count("{") >= 1
                                and len(else_body.strip()) >= 30
                            ):
                                comment = pre.strip() or (
                                    f"/* {meta[ai]['name']} ({hex(ai)}) — "
                                    f"readable C lift. */"
                                )
                                body = rewrite_float_abs(else_body.strip())
                                replacement = comment + "\n" + body + "\n"
                                start_b = len("".join(lines[:c0]))
                                end_b = len("".join(lines[: i + 1]))
                                out.append(
                                    {
                                        "addr": hex(ai),
                                        "addr_int": ai,
                                        "name": meta[ai]["name"],
                                        "src": src,
                                        "path": str(path),
                                        "start": start_b,
                                        "end": end_b,
                                        "replacement": replacement,
                                        "else_len": len(else_body),
                                        "kind": "promote",
                                    }
                                )
                            break
                    i += 1
            i += 1

    # dedupe by addr, prefer shorter else first
    seen = set()
    uniq = []
    for p in sorted(out, key=lambda r: (r["else_len"], r["addr_int"])):
        if p["addr"] in seen:
            continue
        seen.add(p["addr"])
        uniq.append(p)
    return uniq


# Thin wrappers with no usable #else (hand-lifted from XBE).
THIN_LIFTS: list[tuple[int, str, str, str]] = [
    (
        0x1457D0,
        "physics/breakable_surfaces.c",
        "FUN_001457d0",
        """
/* FUN_001457d0 (0x1457d0) — readable C lift (thin wrapper). */
void FUN_001457d0(int a0, int a1, int a2, int a3)
{
  FUN_00145660(a0, a1, a2, a3);
}
""",
    ),

    (
        0x1392E0,
        "objects/object_lights.c",
        "lights_dispose_from_old_map",
        """
/* lights_dispose_from_old_map (0x1392e0) — readable C lift. */
void lights_dispose_from_old_map(void)
{
  data_make_invalid(*(void **)0x5a90bc);
  cluster_partition_dispose((void *)0x5a90b0);
}
""",
    ),
    (
        0x1392B0,
        "objects/object_lights.c",
        "lights_initialize_for_new_map",
        """
/* lights_initialize_for_new_map (0x1392b0) — readable C lift. */
void lights_initialize_for_new_map(void)
{
  data_delete_all(*(void **)0x5a90bc);
  **(unsigned char **)0x46f074 = 1;
  cluster_partition_clear((void *)0x5a90b0);
}
""",
    ),
    (
        0xF5FA0,
        "items/items.c",
        "items_initialize_for_new_map",
        """
/* items_initialize_for_new_map (0xf5fa0) — readable C lift. */
void items_initialize_for_new_map(void)
{
  if (*(unsigned char *)0x46cef0)
    FUN_000f5900();
}
""",
    ),
    (
        0x14AD80,
        "physics/collision_features.c",
        "render_debug_collision_cylinder",
        """
/* render_debug_collision_cylinder (0x14ad80) — readable C lift. */
void render_debug_collision_cylinder(void *cylinder, void *color)
{
  unsigned char *c = (unsigned char *)cylinder;
  FUN_001896d0(1, c + 0xc, c + 0x18, *(float *)(c + 0x24), color);
}
""",
    ),
    (
        0x1B5680,
        "units/vehicles.c",
        "vehicle_is_flipped",
        """
/* vehicle_is_flipped (0x1b5680) — readable C lift. */
char vehicle_is_flipped(int vehicle_handle)
{
  char *vehicle_obj = (char *)object_get_and_verify_type(vehicle_handle, 2);
  if (*(float *)(vehicle_obj + 0x38) > 0.2f)
    return 1;
  return 0;
}
""",
    ),
    (
        0x1457B0,
        "physics/breakable_surfaces.c",
        "FUN_001457b0",
        """
/* FUN_001457b0 (0x1457b0) — readable C lift. */
void FUN_001457b0(int object_handle, int animation_graph_tag, const char *anim_name)
{
  FUN_00145660(object_handle, animation_graph_tag, anim_name, 0);
}
""",
    ),
]


def find_naked_block(text: str, name: str, addr: int) -> tuple[int, int] | None:
    fun = f"FUN_{addr:08x}"
    for nm in (name, fun):
        block = re.compile(
            rf"/\*[^*]*\b{re.escape(nm)}\b[\s\S]*?"
            rf"#if\s+defined\s*\(\s*__clang__\s*\)\s*"
            rf"[\s\S]*?#endif",
            re.M,
        )
        m = block.search(text)
        if m:
            return m.start(), m.end()
        block2 = re.compile(
            rf"/\*[^*]*0x{addr:x}[^*]*\*/\s*"
            rf"#if\s+defined\s*\(\s*__clang__\s*\)[\s\S]*?#endif",
            re.M,
        )
        m = block2.search(text)
        if m:
            return m.start(), m.end()
        pat = re.compile(
            rf"__attribute__\s*\(\s*\(\s*naked(?:\s*,\s*noinline)?\s*\)\s*\)\s*"
            rf"([\w\s\*]+?\b{re.escape(nm)}\s*\([^;]*\))\s*\{{",
            re.M,
        )
        m = pat.search(text)
        if not m:
            continue
        brace = text.find("{", m.end() - 1)
        depth = 0
        for i in range(brace, len(text)):
            if text[i] == "{":
                depth += 1
            elif text[i] == "}":
                depth -= 1
                if depth == 0:
                    start = m.start()
                    # include preceding comment
                    j = start
                    while j > 0 and text[j - 1] in " \t\n\r":
                        j -= 1
                    if text[:j].rstrip().endswith("*/"):
                        k = text[:j].rfind("/*")
                        if k >= 0:
                            start = k
                    return start, i + 1
    return None


def apply_thin(kb: dict) -> list[dict]:
    jobs = []
    for addr, src, name, body in THIN_LIFTS:
        # skip if already true
        ported = None
        for o in kb.get("objects", []):
            for fn in o.get("functions") or []:
                if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == addr:
                    ported = fn.get("ported")
                    break
        if ported is not False:
            continue
        path = resolve_src(src)
        if path is None:
            continue
        text = path.read_text(encoding="utf-8", errors="replace")
        span = find_naked_block(text, name, addr)
        if span is None:
            print(f"thin skip locate {hex(addr)} {name}", flush=True)
            continue
        jobs.append(
            {
                "addr": hex(addr),
                "addr_int": addr,
                "name": name,
                "src": src,
                "path": str(path),
                "start": span[0],
                "end": span[1],
                "replacement": body.strip() + "\n",
                "else_len": len(body),
                "kind": "thin",
            }
        )
    return jobs


def prove_addr(name: str, addr: int, seeds: int, timeout: float) -> dict:
    if not ensure_oracle(addr):
        return {"ok": False, "err": "oracle", "passed": 0, "failed": 0, "errors": 0}
    # Prefer symbol name — hex lookup can miss clang-exported underscores.
    res = run_unicorn(name, addr, seeds, timeout=timeout)
    if not clear_pass(res, seeds):
        res2 = run_unicorn(hex(addr), addr, seeds, timeout=timeout)
        if clear_pass(res2, seeds) or (
            (res2.get("passed") or 0) > (res.get("passed") or 0)
        ):
            res = res2
    ok = clear_pass(res, seeds)
    return {
        "ok": ok,
        "passed": res.get("passed"),
        "failed": res.get("failed"),
        "errors": res.get("errors"),
        "rc": res.get("rc"),
        "tail": (res.get("tail") or "")[-200:],
    }


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--commit-every", type=int, default=10)
    ap.add_argument("--seeds", type=int, default=100)
    ap.add_argument("--timeout", type=float, default=45.0)
    ap.add_argument("--no-push", action="store_true")
    ap.add_argument("--prove-only", action="store_true")
    ap.add_argument(
        "--no-readable-prove",
        action="store_true",
        help="Skip already-readable prove-only queue",
    )
    ap.add_argument(
        "--max-else",
        type=int,
        default=2500,
        help="Skip #else bodies larger than this",
    )
    args = ap.parse_args()

    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    true0, false0 = count_ported(kb)
    flips: list[str] = []
    shas: list[str] = []
    touched: set[Path] = set()
    since = 0

    jobs: list[dict] = []
    if not args.prove_only:
        jobs.extend(collect_promotes(kb))
        jobs.extend(apply_thin(kb))
        # unique by addr
        seen = set()
        uniq = []
        for j in sorted(jobs, key=lambda r: (r.get("else_len", 0), r["addr_int"])):
            if j["addr"] in seen:
                continue
            if j.get("else_len", 0) > args.max_else:
                continue
            seen.add(j["addr"])
            uniq.append(j)
        jobs = uniq

    if not args.no_readable_prove:
        readable = [
            r
            for r in inventory_readable(kb)
            if in_pref(r["source"])
            and hex(r["addr_int"]) not in {j["addr"] for j in jobs}
        ]
        for r in readable:
            jobs.append(
                {
                    "addr": hex(r["addr_int"]),
                    "addr_int": r["addr_int"],
                    "name": r["name"],
                    "src": r["source"],
                    "path": None,
                    "kind": "prove",
                }
            )

    if args.limit:
        jobs = jobs[: args.limit]

    print(
        f"lifter-g jobs={len(jobs)} kb true={true0} false={false0} "
        f"promote/thin/prove mix",
        flush=True,
    )

    for job in jobs:
        ai = job["addr_int"]
        name = job["name"]
        kind = job["kind"]
        print(f"\n== {hex(ai)} {name} [{kind}] ==", flush=True)
        orig_text = None
        path = Path(job["path"]) if job.get("path") else None

        if kind in ("promote", "thin") and path is not None:
            text = path.read_text(encoding="utf-8", errors="replace")
            # re-find span (file may have shifted)
            if kind == "promote":
                # use stored replacement against current clang block
                span = find_naked_block(text, name, ai)
                if span is None:
                    print("  locate FAIL", flush=True)
                    append_ledger(
                        {
                            "addr": hex(ai),
                            "name": name,
                            "ok": False,
                            "phase": "locate",
                            "lifter": LEDGER_TAG,
                        }
                    )
                    continue
                orig_text = text
                path.write_text(
                    text[: span[0]] + job["replacement"] + text[span[1] :],
                    encoding="utf-8",
                )
            else:
                span = find_naked_block(text, name, ai)
                if span is None:
                    print("  locate FAIL", flush=True)
                    continue
                orig_text = text
                path.write_text(
                    text[: span[0]] + job["replacement"] + text[span[1] :],
                    encoding="utf-8",
                )
            for stale in (ROOT / "build").rglob(path.name + ".obj"):
                try:
                    stale.unlink()
                except OSError:
                    pass

        t0 = time.time()
        res = prove_addr(name, ai, args.seeds, args.timeout)
        print(
            f"  unicorn {res.get('passed')}/{res.get('failed')}/{res.get('errors')} "
            f"ok={res.get('ok')} dt={time.time()-t0:.1f}",
            flush=True,
        )
        append_ledger(
            {
                "addr": hex(ai),
                "name": name,
                "ok": bool(res.get("ok")),
                "phase": f"{kind}_{args.seeds}",
                "lifter": LEDGER_TAG,
                "passed": res.get("passed"),
                "failed": res.get("failed"),
                "errors": res.get("errors"),
            }
        )

        if not res.get("ok"):
            if orig_text is not None and path is not None:
                path.write_text(orig_text, encoding="utf-8")
                print("  REVERT", flush=True)
            continue

        # raw-cast guard
        rc = subprocess.run(
            [sys.executable, str(ROOT / "tools/audit/check_raw_casts.py")],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
        if rc.returncode != 0:
            if orig_text is not None and path is not None:
                path.write_text(orig_text, encoding="utf-8")
            print("  REVERT raw-cast", flush=True)
            continue

        if safe_flip(ai):
            flips.append(hex(ai))
            since += 1
            if path is not None:
                touched.add(path)
            print(f"  FLIP {hex(ai)} total={len(flips)}", flush=True)

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
    Path("/tmp/lifter_g_summary.json").write_text(json.dumps(summary, indent=2))
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
