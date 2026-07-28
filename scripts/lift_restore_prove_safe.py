#!/usr/bin/env python3
"""Safe history-restore → Unicorn prove factory.

Restores pre-naked C from naked-intro^, force-rebuilds the TU, proves with
Unicorn 100/0/0, and ALWAYS reverts the file on compile/locate/extract failure
or non-perfect Unicorn. Never flips naked.
"""
from __future__ import annotations

import argparse
import json
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))

from lift_grok_tracka_restore_prove import extract_func  # noqa: E402
from lift_inventory_batch4 import find_naked_block  # noqa: E402
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from tu_compile import docker_compile  # noqa: E402
from unicorn_c_campaign import count_ported, is_naked_near_def  # noqa: E402

os.environ.setdefault("BIPED_SIBLING_RESOLVE", "1")

NAKED_RE = re.compile(r"__attribute__\s*\(\s*\(\s*naked\b")
RESULTS_RE = re.compile(r"(\d+) passed, (\d+) failed, (\d+) errors")
ZERO_ARG_CALL = re.compile(r"\b([A-Za-z_][A-Za-z0-9_]*)\s*\(\s*\)\s*;")
FAIL_LEDGER = ROOT / "artifacts" / "grind" / "restore_fail_ledger.json"
# Skip recently-failed restores so waves don't burn 90s×N on known near-misses.
FAIL_SKIP_HOURS = 2


def load_fail_ledger() -> dict:
    if not FAIL_LEDGER.exists():
        return {}
    try:
        return json.loads(FAIL_LEDGER.read_text())
    except Exception:
        return {}


def note_fail(ledger: dict, name: str, kind: str) -> None:
    import time

    ledger[name] = {"kind": kind, "ts": time.time()}
    FAIL_LEDGER.parent.mkdir(parents=True, exist_ok=True)
    FAIL_LEDGER.write_text(json.dumps(ledger, indent=2) + "\n")


def should_skip_failed(ledger: dict, name: str) -> bool:
    import time

    ent = ledger.get(name)
    if not ent:
        return False
    age_h = (time.time() - float(ent.get("ts") or 0)) / 3600.0
    return age_h < FAIL_SKIP_HOURS


def patch_zero_arg_calls(text: str) -> str:
    """Cast register-arg callees invoked with empty parens so TU compile succeeds."""
    decl_h = (ROOT / "build/generated/decl.h").read_text(errors="ignore")
    decls = {}
    for m in re.finditer(r"HFUNC\s+(.+?\))\s*;", decl_h):
        sig = m.group(1).strip()
        p0 = sig.find("(")
        if p0 < 0:
            continue
        # Name is the last token of the declarator *before* '(', not the
        # trailing "(params)" chunk from rsplit — that bug left decls empty
        # for almost every symbol and disabled zero-arg casts.
        nm = sig[:p0].rsplit(" ", 1)[-1].strip()
        nm = nm.lstrip("*").strip()
        if not nm or nm.startswith("("):
            continue
        params = sig[p0 + 1 : sig.rfind(")")].strip()
        decls[nm] = params

    def repl(mm: re.Match[str]) -> str:
        name = mm.group(1)
        if name in ("if", "while", "for", "switch", "return"):
            return mm.group(0)
        params = decls.get(name)
        if params is None or not params or params == "void":
            return mm.group(0)
        return f"((void(*)(void)){name})();"

    return ZERO_ARG_CALL.sub(repl, text)


def align_sig_to_decl_h(body: str, name: str) -> str:
    """Rewrite restored function signature to match decl.h (unlock arity conflicts)."""
    decl_h = (ROOT / "build/generated/decl.h").read_text(errors="ignore")
    m = re.search(rf"HFUNC\s+(.+?\b{re.escape(name)}\s*\([^;]*\))\s*;", decl_h)
    if not m:
        return body
    good_sig = m.group(1).strip()
    # Drop calling-convention keywords that confuse some restored bodies
    good_sig = re.sub(r"\b__stdcall\b\s*", "", good_sig)
    # Replace first definition signature for this name
    pat = re.compile(
        rf"(?m)^([\w\s\*]*?\b{re.escape(name)}\s*\([^;{{]*\))",
    )
    mm = pat.search(body)
    if not mm:
        return body
    old = mm.group(1)
    if old.replace(" ", "") == good_sig.replace(" ", ""):
        return body
    # Keep unused attributes on params if body had them — prefer decl.h clean
    return body[: mm.start(1)] + good_sig + body[mm.end(1) :]


SKIP_SUB = (
    "xdk",
    "libcmt",
    "tiff",
    "tif_",
    "bink",
    "d3d",
    "xapilib",
    "xboxkrnl",
    "xgraphic",
    "xmv",
    "xnet",
    "libm",
)


def find_intro_parent(name: str, addr: int, path: str) -> str | None:
    # Cap history walk — full `git log -S` across deep tip history was
    # stalling tip waves for 10–20+ minutes before any RESTORED line.
    for needle in (f"/* {name} (0x", f"{name} (0x{addr:x})"):
        r = subprocess.run(
            ["git", "log", "-S", needle, "--format=%H", "-n", "8", "--", path],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
        commits = [c for c in r.stdout.splitlines() if c]
        for c in commits:
            parent = f"{c}^"
            # Skip orphan/root commits where `{sha}^` is not a valid object.
            chk = subprocess.run(
                ["git", "rev-parse", "--verify", parent],
                cwd=ROOT,
                capture_output=True,
                text=True,
            )
            if chk.returncode == 0:
                return parent
    return None


def domain_rank(src: str, body_len: int, addr: int) -> tuple:
    s = 0
    if src.startswith("ai/"):
        s += 5
    if src.startswith("units/"):
        s += 5
    if src.startswith("math/"):
        s += 4
    if src.startswith("networking/") or "bungie_net" in src:
        s += 3
    if src.startswith("objects/") or src.startswith("structures/"):
        s += 3
    if src.startswith("interface/") or src.startswith("game/"):
        s += 2
    if "kb_common" in src:
        s -= 10
    if "rasterizer" in src:
        s -= 1
    return (-s, body_len, addr)


def uni(name: str, addr: int, seeds: int, timeout: float) -> tuple[int, int, int] | None:
    ensure_oracle(addr)
    env = {**os.environ, "BIPED_SIBLING_RESOLVE": "1"}
    try:
        r = subprocess.run(
            [
                sys.executable,
                "tools/equivalence/unicorn_diff.py",
                name,
                "--allow-stubs",
                "--no-stub-arg-trace",
                "--seeds",
                str(seeds),
                "-q",
            ],
            cwd=ROOT,
            capture_output=True,
            text=True,
            timeout=timeout,
            env=env,
        )
    except subprocess.TimeoutExpired:
        return None
    m = RESULTS_RE.search((r.stdout or "") + (r.stderr or ""))
    if not m:
        return None
    return tuple(map(int, m.groups()))  # type: ignore[return-value]


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--limit", type=int, default=40)
    ap.add_argument("--seeds", type=int, default=100)
    ap.add_argument("--timeout", type=float, default=90.0)
    ap.add_argument("--commit-every", type=int, default=3)
    ap.add_argument("--prefer", default="ai,units,math,networking,objects,structures,game,interface")
    args = ap.parse_args()
    prefer = [p.strip() for p in args.prefer.split(",") if p.strip()]

    kb = json.loads((ROOT / "kb.json").read_text())
    true0, false0 = count_ported(kb)
    print(f"start true={true0} false={false0}", flush=True)

    cands = []
    for o in kb["objects"]:
        src = o.get("source") or ""
        if any(x in src for x in SKIP_SUB):
            continue
        path = f"src/halo/{src}" if src.endswith(".c") else None
        if not path or not (ROOT / path).exists():
            continue
        text = (ROOT / path).read_text(errors="ignore")
        for fn in o.get("functions") or []:
            if not isinstance(fn, dict) or fn.get("ported") is not False:
                continue
            name = fn.get("name")
            addr_s = fn.get("addr")
            if not name or not addr_s:
                continue
            addr = int(addr_s, 16)
            naked = False
            for mm in re.finditer(rf"(?m)^[^\n]*\b{re.escape(name)}\s*\(", text):
                win = text[max(0, mm.start() - 220) : mm.start() + 40]
                if NAKED_RE.search(win) or "XBE naked" in win:
                    naked = True
                    break
            if not naked:
                continue
            cands.append((name, addr, src, path))

    # Prefer-filter BEFORE expensive git log -S parent search. Previously we
    # walked parents for every naked false (~1k+) then sorted — tip waves
    # stalled for 10–20+ minutes with no RESTORED output.
    if prefer:
        pref_cands = []
        for name, addr, src, path in cands:
            if any(src.startswith(p + "/") or src.startswith(p) for p in prefer):
                pref_cands.append((name, addr, src, path))
        print(
            f"cands={len(cands)} prefer_filtered={len(pref_cands)} prefer={prefer}",
            flush=True,
        )
        cands = pref_cands
    else:
        print(f"cands={len(cands)}", flush=True)

    # Build restorable with extractable parent bodies
    restorable = []
    for name, addr, src, path in cands:
        parent = find_intro_parent(name, addr, path)
        if not parent:
            continue
        try:
            old = subprocess.check_output(
                ["git", "show", f"{parent}:{path}"], cwd=ROOT, text=True
            )
        except subprocess.CalledProcessError:
            continue
        parent_naked = False
        for mm in re.finditer(rf"(?m)^[^\n]*\b{re.escape(name)}\s*\(", old):
            win = old[max(0, mm.start() - 220) : mm.start() + 40]
            if NAKED_RE.search(win) or "XBE naked" in win:
                parent_naked = True
                break
        if parent_naked:
            continue
        body = extract_func(old, name, addr)
        if not body:
            continue
        body = patch_zero_arg_calls(body)
        body = align_sig_to_decl_h(body, name)
        restorable.append((name, addr, src, path, parent, body))

    def pref_rank(t):
        name, addr, src, path, parent, body = t
        pref_i = 99
        for i, p in enumerate(prefer):
            if src.startswith(p + "/") or src.startswith(p):
                pref_i = i
                break
        base = domain_rank(src, len(body), addr)
        return (pref_i, *base)

    fail_ledger = load_fail_ledger()
    skipped_recent = sum(1 for t in restorable if should_skip_failed(fail_ledger, t[0]))
    restorable = [t for t in restorable if not should_skip_failed(fail_ledger, t[0])]
    restorable = sorted(restorable, key=pref_rank)
    print(
        f"restorable={len(restorable)} (skipped_recent_fail={skipped_recent}; "
        f"processing up to {args.limit})",
        flush=True,
    )

    proven: list[str] = []
    proven_addrs: list[int] = []
    skipped_tus: set[str] = set()
    processed = 0

    for name, addr, src, path, parent, body in restorable:
        if processed >= args.limit:
            break
        if src in skipped_tus:
            continue
        full = ROOT / path
        backup = full.read_text(encoding="utf-8", errors="replace")
        if not is_naked_near_def(backup.splitlines(), name, hex(addr)):
            continue
        processed += 1
        span = find_naked_block(backup, name, addr)
        if span is None:
            pat = re.compile(
                rf"/\*[^\n]*\b0x{addr:x}\b[\s\S]*?#if defined\(__clang__\)[\s\S]*?#endif\s*\n",
                re.I,
            )
            m = pat.search(backup)
            if not m:
                print(f"LOCATE_FAIL {name}", flush=True)
                continue
            span = (m.start(), m.end())
        start, end = span
        span_len = end - start
        if span_len > max(len(body) * 10, 80000):
            print(f"SPAN_GUARD {name} span={span_len} body={len(body)}", flush=True)
            continue
        new = backup[:start] + body + "\n" + backup[end:]
        if is_naked_near_def(new.splitlines(), name, hex(addr)):
            print(f"STILL_NAKED {name}", flush=True)
            continue
        full.write_text(new, encoding="utf-8")
        print(f"RESTORED {name} from {parent}", flush=True)

        for obj in (
            ROOT / "build/CMakeFiles/halo.dir/src/halo" / f"{src}.obj",
            ROOT / "build/CMakeFiles/halo.dir" / path.replace(".c", ".c.obj"),
        ):
            if obj.exists():
                obj.unlink()
        if not docker_compile(src):
            # Revert and keep trying other symbols in this TU. A single bad
            # extract must not blacklist the whole file for the rest of the run.
            print(f"COMPILE_FAIL revert {name} ({src})", flush=True)
            note_fail(fail_ledger, name, "compile")
            full.write_text(backup, encoding="utf-8")
            continue

        res = uni(name, addr, args.seeds, args.timeout)
        if res is None:
            print(f"UNI_FAIL/timeout revert {name}", flush=True)
            note_fail(fail_ledger, name, "timeout")
            full.write_text(backup, encoding="utf-8")
            continue
        p, f, e = res
        print(f"UNI {name} {p}/{f}/{e}", flush=True)
        if p >= args.seeds and f == 0 and e == 0:
            if is_naked_near_def(full.read_text(errors="ignore").splitlines(), name, hex(addr)):
                print(f"BLOCK_NAKED_FLIP revert {name}", flush=True)
                full.write_text(backup, encoding="utf-8")
                continue
            # Re-load kb before flip so concurrent tip commits are not clobbered
            # by a stale in-memory snapshot from wave start.
            kb = json.loads((ROOT / "kb.json").read_text())
            if flip_kb(kb, addr):
                proven.append(name)
                proven_addrs.append(addr)
                (ROOT / "kb.json").write_text(json.dumps(kb, indent=2) + "\n")
                print(f"FLIP {name} n={len(proven)}", flush=True)
                if args.commit_every and len(proven) % args.commit_every == 0:
                    subprocess.run(["git", "add", "kb.json", path], cwd=ROOT, check=False)
                    msg = f"lift(track-a): {args.commit_every} Unicorn-prove restore batch (ported:true)."
                    # commit only if staged changes exist
                    st = subprocess.run(
                        ["git", "diff", "--cached", "--quiet"], cwd=ROOT
                    )
                    if st.returncode != 0:
                        subprocess.run(
                            ["git", "commit", "-m", msg],
                            cwd=ROOT,
                            check=False,
                        )
        else:
            # Revert non-perfect to keep tree healthy for next candidates
            print(f"REVERT nonperfect {name}", flush=True)
            note_fail(fail_ledger, name, f"uni_{p}_{f}_{e}")
            full.write_text(backup, encoding="utf-8")

    # Never rewrite kb from a stale snapshot when nothing proven — that race
    # wiped concurrent tip-reprove flips (e.g. structures + volume_name).
    if proven:
        kb = json.loads((ROOT / "kb.json").read_text())
        for a in proven_addrs:
            flip_kb(kb, a)
        (ROOT / "kb.json").write_text(json.dumps(kb, indent=2) + "\n")
        # stage any remaining modified sources for proven names
        subprocess.run(["git", "add", "-u", "src/halo", "kb.json"], cwd=ROOT, check=False)
        st = subprocess.run(["git", "diff", "--cached", "--quiet"], cwd=ROOT)
        if st.returncode != 0:
            subprocess.run(
                [
                    "git",
                    "commit",
                    "-m",
                    f"lift(track-a): {len(proven)} Unicorn-prove history-restore (ported:true).",
                ],
                cwd=ROOT,
                check=False,
            )

    true1, false1 = count_ported(json.loads((ROOT / "kb.json").read_text()))
    print(
        {
            "proven": proven,
            "n": len(proven),
            "processed": processed,
            "skipped_tus": sorted(skipped_tus),
            "true": true1,
            "false": false1,
            "delta": true1 - true0,
        },
        flush=True,
    )
    return 0 if proven else 1


if __name__ == "__main__":
    raise SystemExit(main())
