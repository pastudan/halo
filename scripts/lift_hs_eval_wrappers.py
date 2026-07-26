#!/usr/bin/env python3
"""Lift HS eval/return wrappers + unicode case; Unicorn-prove; commit often; push."""
from __future__ import annotations

import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
from lift_inventory_batch4 import find_naked_block  # noqa: E402
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
    git_push,
    run_unicorn,
)

# (addr, source, name, body, decl)
LIFTS: list[tuple[int, str, str, str, str]] = []


def add(addr, source, name, body, decl):
    LIFTS.append((addr, source, name, body.strip() + "\n", decl))


# unicode case — typed callee casts (no raw 0x casts)
add(
    0x19E5C0,
    "text/unicode.c",
    "utoupper",
    """
/* utoupper (0x19e5c0) — readable C lift. */
int utoupper(int c)
{
  typedef unsigned short (*towupper_fn)(unsigned short);
  return (int)((towupper_fn)FUN_001dc27c)((unsigned short)c);
}
""",
    "int utoupper(int c);",
)
add(
    0x19E5E0,
    "text/unicode.c",
    "utolower",
    """
/* utolower (0x19e5e0) — readable C lift. */
int utolower(int c)
{
  typedef unsigned short (*towlower_fn)(unsigned short);
  return (int)((towlower_fn)FUN_001da8e3)((unsigned short)c);
}
""",
    "int utolower(int c);",
)

# hs stricmp helper
add(
    0xC4010,
    "hs/hs.c",
    "FUN_000c4010",
    """
/* FUN_000c4010 (0xc4010) — readable C lift. */
int FUN_000c4010(const char **a, const char **b)
{
  return crt_stricmp(*a, *b);
}
""",
    "int FUN_000c4010(const char **a, const char **b);",
)

# hs_runtime thin
add(
    0xCA0F0,
    "hs/hs_runtime.c",
    "FUN_000ca0f0",
    """
/* FUN_000ca0f0 (0xca0f0) — readable C lift. */
char FUN_000ca0f0(int16_t game_flag, int list_handle)
{
  return FUN_000c9650(game_flag, list_handle, 0);
}
""",
    "char FUN_000ca0f0(int16_t game_flag, int list_handle);",
)
add(
    0xCA3F0,
    "hs/hs_runtime.c",
    "FUN_000ca3f0",
    """
/* FUN_000ca3f0 (0xca3f0) — readable C lift. */
void FUN_000ca3f0(int16_t scenario_index, int object_handle)
{
  FUN_000ca160(scenario_index, 1, 1, object_handle);
}
""",
    "void FUN_000ca3f0(int16_t scenario_index, int object_handle);",
)
add(
    0xCA410,
    "hs/hs_runtime.c",
    "FUN_000ca410",
    """
/* FUN_000ca410 (0xca410) — readable C lift. */
void FUN_000ca410(int16_t scenario_index, int object_handle)
{
  FUN_000ca160(scenario_index, 1, 0, object_handle);
}
""",
    "void FUN_000ca410(int16_t scenario_index, int object_handle);",
)

HS_SIG = "void {name}(int16_t function_index, int thread_datum, char init)"


def hs_eval_void(name: str, addr: int, action: str) -> None:
    """action is C statements using `args` (int*) when non-NULL."""
    body = f"""
/* {name} (0x{addr:x}) — readable C lift (HS eval wrapper). */
{HS_SIG.format(name=name)}
{{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {{
    {action}
  }}
  hs_return(thread_datum, 0);
}}
"""
    add(addr, "game/players.c", name, body, HS_SIG.format(name=name) + ";")


# word[0] callbacks
hs_eval_void("FUN_000be0d0", 0xBE0D0, "FUN_000c9990((int16_t)(uint16_t)args[0]);")
hs_eval_void("FUN_000be150", 0xBE150, "FUN_000ca110((int16_t)(uint16_t)args[0]);")
# dword[0]
hs_eval_void("FUN_000be110", 0xBE110, "FUN_000c99e0(args[0]);")
hs_eval_void("FUN_000be190", 0xBE190, "FUN_000c9b90((const char *)args[0]);")
hs_eval_void("FUN_000be860", 0xBE860, "FUN_000952d0(args[0]);")
hs_eval_void("FUN_000bef00", 0xBEF00, "FUN_001a7f80(args[0]);")
hs_eval_void("FUN_000bfef0", 0xBFEF0, "FUN_000575d0(args[0]);")
hs_eval_void("FUN_000bff30", 0xBFF30, "FUN_000576a0(args[0]);")
# byte[0]
hs_eval_void("FUN_000bfeb0", 0xBFEB0, "FUN_0003f800((char)(uint8_t)args[0]);")
# (dword, byte)
hs_eval_void(
    "FUN_000be660",
    0xBE660,
    "FUN_00190be0(args[0], (char)(uint8_t)args[1]);",
)
hs_eval_void(
    "FUN_000be930",
    0xBE930,
    "FUN_001369b0(args[0], (char)(uint8_t)args[1]);",
)
hs_eval_void(
    "FUN_000be990",
    0xBE990,
    "FUN_0013eb30(args[0], (char)(uint8_t)args[1]);",
)
hs_eval_void(
    "FUN_000bf9f0",
    0xBF9F0,
    "FUN_000964d0(args[0], (char)(uint8_t)args[1]);",
)
# (dword, dword)
hs_eval_void("FUN_000bea50", 0xBEA50, "FUN_00143510(args[0], args[1]);")
hs_eval_void("FUN_000bffb0", 0xBFFB0, "FUN_00054a80(args[0], args[1]);")
# float store
hs_eval_void(
    "FUN_000be5e0",
    0xBE5E0,
    "FUN_000ca030(args[0], *(float *)&args[1]);",
)
# (dword, float, word)
hs_eval_void(
    "FUN_000be9d0",
    0xBE9D0,
    "FUN_00140b80(args[0], *(float *)&args[1], (int16_t)(uint16_t)args[2]);",
)


def resolve(src: str) -> Path | None:
    for base in (ROOT / "src" / "halo", ROOT / "src"):
        p = base / src
        if p.exists():
            return p
    return None


def commit_chunk(n: int) -> str | None:
    subprocess.run(["git", "add", "-u", "src/halo", "kb.json"], cwd=ROOT, check=False)
    subprocess.run(
        [
            "git",
            "add",
            "kb.json",
            "tools/equivalence/leaf_cache.json",
            "scripts/lift_hs_eval_wrappers.py",
        ],
        cwd=ROOT,
        check=False,
    )
    msg = f"lift(track-a): HS eval/unicode wrappers + Unicorn-prove {n} (ported:true)."
    r = subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print("commit fail", r.stdout, r.stderr, file=sys.stderr)
        return None
    sha = subprocess.run(
        ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
    ).stdout.strip()
    git_push()
    print(f"COMMIT+PUSH {sha}", flush=True)
    return sha


def main() -> int:
    true0, _ = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    flips = []
    shas = []
    since = 0

    for ai, src, name, body, decl in LIFTS:
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        ported = None
        for o in kb["objects"]:
            for fn in o.get("functions") or []:
                if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == ai:
                    ported = fn.get("ported")
                    fn["decl"] = decl
        if ported is not False:
            print(f"skip {hex(ai)} ported={ported}", flush=True)
            continue
        # write decl only after success to avoid kb races; keep in memory for now
        sp = resolve(src)
        if not sp:
            print(f"skip no src {hex(ai)}", flush=True)
            continue
        text = sp.read_text(encoding="utf-8", errors="replace")
        span = find_naked_block(text, name, ai)
        if span is None:
            print(f"skip locate {hex(ai)} {name}", flush=True)
            continue
        sp.write_text(text[: span[0]] + body + "\n" + text[span[1] :], encoding="utf-8")
        print(f"LIFTED {hex(ai)} {name}", flush=True)
        for stale in (ROOT / "build").rglob(sp.name + ".obj"):
            try:
                stale.unlink()
            except OSError:
                pass
        if not ensure_oracle(ai):
            sp.write_text(text, encoding="utf-8")
            print("  oracle FAIL", flush=True)
            continue
        res = run_unicorn(name, ai, 100, timeout=45.0)
        ok = clear_pass(res, 100)
        if not ok:
            res2 = run_unicorn(hex(ai), ai, 100, timeout=45.0)
            if clear_pass(res2, 100):
                res, ok = res2, True
        print(f"  ok={ok} {res.get('passed')}/{res.get('failed')}/{res.get('errors')}", flush=True)
        append_ledger(
            {
                "addr": hex(ai),
                "name": name,
                "ok": ok,
                "phase": "hs_eval",
                "passed": res.get("passed"),
                "failed": res.get("failed"),
                "errors": res.get("errors"),
            }
        )
        if not ok:
            sp.write_text(text, encoding="utf-8")
            print("  REVERT", flush=True)
            continue
        rc = subprocess.run(
            [sys.executable, str(ROOT / "tools/audit/check_raw_casts.py")],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
        if rc.returncode != 0:
            sp.write_text(text, encoding="utf-8")
            print("  REVERT raw-cast", flush=True)
            continue
        # reload kb fresh before flip (avoid stale overwrite)
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        for o in kb["objects"]:
            for fn in o.get("functions") or []:
                if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == ai:
                    fn["decl"] = decl
        if flip_kb(kb, ai):
            flips.append(hex(ai))
            since += 1
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        if since >= 10:
            sha = commit_chunk(since)
            if sha:
                shas.append(sha)
            since = 0

    if since:
        sha = commit_chunk(since)
        if sha:
            shas.append(sha)

    true1, _ = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    summary = {"proven": len(flips), "flips": flips, "shas": shas, "true0": true0, "true1": true1}
    Path("/tmp/hs_eval_summary.json").write_text(json.dumps(summary, indent=2))
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
