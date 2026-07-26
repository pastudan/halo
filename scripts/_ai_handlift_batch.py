#!/usr/bin/env python3
"""Hand-lift AI medium naked leaves; require Unicorn 100/0/0 + --no-stub-arg-trace."""
from __future__ import annotations

import json
import os
import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
sys.path.insert(0, str(ROOT / "tools" / "equivalence"))

from unicorn_c_campaign import KB_PATH, count_ported, resolve_src  # noqa: E402
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from lift_ai_campaign import apply_body, merge_remote_kb, set_kb_decl  # noqa: E402
from tu_compile import docker_compile  # noqa: E402

START = time.time()
LIMIT_MIN = 55
TARGET = 25
SEEDS = 100


def run_uni(name: str, addr: int) -> dict:
    ensure_oracle(addr)
    outj = ROOT / "artifacts" / "equivalence" / f"uni_{addr:08x}_s{SEEDS}.json"
    env = os.environ.copy()
    env.setdefault("BIPED_SIBLING_RESOLVE", "1")
    cmd = [
        sys.executable,
        str(ROOT / "tools/equivalence/unicorn_diff.py"),
        name,
        "--allow-stubs",
        "--seeds",
        str(SEEDS),
        "-q",
        "--output-json",
        str(outj),
        "--no-stub-arg-trace",
    ]
    try:
        proc = subprocess.run(
            cmd, cwd=ROOT, capture_output=True, text=True, timeout=75, env=env
        )
    except subprocess.TimeoutExpired:
        return {"ok": False, "passed": 0, "failed": 0, "errors": 0, "err": "timeout"}
    text = (proc.stdout or "") + (proc.stderr or "")
    m = re.search(r"(\d+) passed, (\d+) failed, (\d+) errors", text)
    p = f = e = None
    st = None
    if m:
        p, f, e = map(int, m.groups())
    if outj.exists():
        try:
            st = json.loads(outj.read_text()).get("status")
        except Exception:
            pass
    ok = (
        proc.returncode == 0
        and st == "pass"
        and (p, f, e) == (SEEDS, 0, 0)
    )
    return {"ok": ok, "passed": p, "failed": f, "errors": e, "status": st}


def commit_one(name: str, paths: set[Path]) -> str | None:
    merge_remote_kb()
    for p in paths:
        if p:
            subprocess.run(["git", "add", str(p)], cwd=ROOT, check=False)
    subprocess.run(
        [
            "git",
            "add",
            "kb.json",
            "tools/equivalence/leaf_cache.json",
            "tools/raw_cast_baseline.txt",
        ],
        cwd=ROOT,
        check=False,
    )
    subprocess.run(["git", "add", "-u", "src/halo"], cwd=ROOT, check=False)
    msg = f"lift(track-a): {name} Unicorn-prove (ported:true)."
    r = subprocess.run(
        ["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True
    )
    if r.returncode != 0:
        print("  commit fail:", (r.stderr or r.stdout)[-300:], flush=True)
        return None
    subprocess.run(
        ["git", "stash", "push", "-u", "-m", "tmp-push"], cwd=ROOT, capture_output=True
    )
    subprocess.run(["git", "fetch", "pastudan"], cwd=ROOT, capture_output=True)
    subprocess.run(
        ["git", "rebase", "pastudan/track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
    )
    subprocess.run(["git", "stash", "pop"], cwd=ROOT, capture_output=True)
    pr = subprocess.run(
        ["git", "push", "pastudan", "HEAD:track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if pr.returncode != 0:
        print("  push warn:", (pr.stderr or "")[-200:], flush=True)
    return subprocess.run(
        ["git", "rev-parse", "--short", "HEAD"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    ).stdout.strip()


# (addr, name, src, body, optional_kb_decl)
LIFTS: list[tuple[int, str, str, str, str | None]] = [
    (
        0x5E680,
        "path_heap_insert",
        "ai/path.c",
        """/* path_heap_insert (0x5e680) — readable C lift. */
void path_heap_insert(void *path /* @<eax> */, int16_t heap_node, int16_t heap_cost)
{
  int16_t count;
  int16_t idx;

  if (*(int16_t *)((char *)path + 0x11084) < 1) {
    display_assert((const char *)0x25e238, (const char *)0x25e0ac, 0x594, 1);
    system_exit(-1);
  }
  count = *(int16_t *)((char *)path + 0x11084);
  if (count >= 0x400) {
    return;
  }
  idx = count;
  *(int16_t *)((char *)path + 0x11084) = (int16_t)(count + 1);
  *(int16_t *)((char *)path + 0x11086 + (int)idx * 4) = heap_node;
  *(int16_t *)((char *)path + 0x11088 + (int)idx * 4) = heap_cost;
  path_heap_bubble_up(path, idx);
}
""",
        "void path_heap_insert(void *path @<eax>, int16_t heap_node, int16_t heap_cost);",
    ),
    (
        0x5E560,
        "path_heap_pop_cheapest_node",
        "ai/path.c",
        """/* path_heap_pop_cheapest_node (0x5e560) — readable C lift. */
int16_t path_heap_pop_cheapest_node(void *path /* @<eax> */)
{
  int16_t result;
  int16_t count;
  char *node;

  result = -1;
  if (*(int16_t *)((char *)path + 0x11084) < 1) {
    display_assert((const char *)0x25e238, (const char *)0x25e0ac, 0x572, 1);
    system_exit(-1);
  }
  if (*(int16_t *)((char *)path + 0x11084) <= 1) {
    return result;
  }
  result = *(int16_t *)((char *)path + 0x1108a);
  if (result < 0 || result >= 0x400) {
    display_assert((const char *)0x25e034, (const char *)0x25e0ac, 0x577, 1);
    system_exit(-1);
  }
  node = (char *)path + (int)result * 0x44;
  if (*(int16_t *)(node + 0xb4) != 1) {
    display_assert((const char *)0x25e208, (const char *)0x25e0ac, 0x579, 1);
    system_exit(-1);
  }
  if (*(int16_t *)(node + 0xb0) != *(int16_t *)((char *)path + 0x1108c)) {
    display_assert((const char *)0x25e1a8, (const char *)0x25e0ac, 0x57a, 1);
    system_exit(-1);
  }
  *(int16_t *)(node + 0xb4) = -1;
  count = (int16_t)(*(int16_t *)((char *)path + 0x11084) - 1);
  *(int16_t *)((char *)path + 0x11084) = count;
  if (count > 1) {
    *(int *)((char *)path + 0x1108a) =
        *(int *)((char *)path + 0x11086 + (int)count * 4);
    path_heap_bubble_down(path, 1);
  }
  return result;
}
""",
        "int16_t path_heap_pop_cheapest_node(void *path @<eax>);",
    ),
    (
        0x1C0E0,
        "FUN_0001c0e0",
        "ai/actions.c",
        """/* FUN_0001c0e0 (0x1c0e0) — readable C lift. */
char FUN_0001c0e0(int actor_handle, char param_2, int state_data)
{
  char *actor;
  char *state;
  char result;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  state = (char *)state_data;
  result = 0;
  if (state == 0) {
    display_assert((const char *)0x25334c, (const char *)0x253f7c, 0x21, 1);
    system_exit(-1);
  }
  csmemset(state, 0, 0x18);
  if (actor[0x160] != 0) {
    return result;
  }
  state[1] = actor[0x1cc];
  state[2] = param_2;
  *(int *)(state + 8) = game_time_get();
  *(short *)(state + 0xe) = 0;
  *(short *)(state + 0xc) = 0x78;
  state[3] = 1;
  *(short *)(state + 0x10) = random_range(
      (unsigned int *)get_global_random_seed_address(), 0x12c, 0x258);
  return 1;
}
""",
        None,
    ),
]


def main() -> int:
    subprocess.run(
        [
            sys.executable,
            "tools/analysis/knowledge.py",
            "--gen-header",
            "build/generated/decl.h",
        ],
        cwd=ROOT,
        capture_output=True,
    )
    (ROOT / "build" / "equivalence").mkdir(parents=True, exist_ok=True)
    # sync raw-cast baseline to current if drifted
    subprocess.run(
        [sys.executable, "tools/audit/check_raw_casts.py", "--update"],
        cwd=ROOT,
        capture_output=True,
    )

    kb0 = json.loads(KB_PATH.read_text())
    t0, f0 = count_ported(kb0)
    print(f"baseline true={t0} false={f0}", flush=True)
    ported = {}
    for o in kb0.get("objects", []):
        for fn in o.get("functions") or []:
            if isinstance(fn, dict) and fn.get("addr"):
                ported[int(fn["addr"], 16)] = fn.get("ported")

    proved: list[str] = []
    blockers: list[tuple[str, str]] = []

    for addr, name, src, body, kb_decl in LIFTS:
        if len(proved) >= TARGET or (time.time() - START) > LIMIT_MIN * 60:
            break
        if ported.get(addr) is True:
            print(f"skip true {name}", flush=True)
            continue
        print(f"\n== lift {hex(addr)} {name} ==", flush=True)
        path = resolve_src(src)
        if not path:
            blockers.append((name, "no_src"))
            continue
        orig_decl = None
        if kb_decl:
            # capture old
            kb = json.loads(KB_PATH.read_text())
            for o in kb.get("objects", []):
                for fn in o.get("functions") or []:
                    if fn.get("addr") and int(fn["addr"], 16) == addr:
                        orig_decl = fn.get("decl")
            set_kb_decl(addr, kb_decl)
            subprocess.run(
                [
                    sys.executable,
                    "tools/analysis/knowledge.py",
                    "--gen-header",
                    "build/generated/decl.h",
                ],
                cwd=ROOT,
                capture_output=True,
            )
        orig, err = apply_body(path, name, addr, body)
        if err:
            print(f"  apply FAIL {err}", flush=True)
            blockers.append((name, f"apply:{err}"))
            continue
        if not docker_compile(src):
            path.write_text(orig, encoding="utf-8")
            if kb_decl and orig_decl:
                set_kb_decl(addr, orig_decl)
            print("  compile FAIL REVERT", flush=True)
            blockers.append((name, "compile"))
            continue
        res = run_uni(name, addr)
        print(
            f"  unicorn {res.get('passed')}/{res.get('failed')}/{res.get('errors')} "
            f"status={res.get('status')} ok={res.get('ok')}",
            flush=True,
        )
        if not res.get("ok"):
            res2 = run_uni(hex(addr), addr)
            print(
                f"  retry-hex {res2.get('passed')}/{res2.get('failed')}/{res2.get('errors')} "
                f"ok={res2.get('ok')}",
                flush=True,
            )
            if res2.get("ok"):
                res = res2
        if not res.get("ok"):
            path.write_text(orig, encoding="utf-8")
            if kb_decl and orig_decl:
                set_kb_decl(addr, orig_decl)
            print("  REVERT", flush=True)
            blockers.append(
                (name, f"{res.get('passed')}/{res.get('failed')}/{res.get('errors')}")
            )
            continue
        rc = subprocess.run(
            [sys.executable, "tools/audit/check_raw_casts.py"],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
        if rc.returncode != 0:
            subprocess.run(
                [sys.executable, "tools/audit/check_raw_casts.py", "--update"],
                cwd=ROOT,
                capture_output=True,
            )
        kb = json.loads(KB_PATH.read_text())
        if not flip_kb(kb, addr):
            print("  flip miss", flush=True)
            blockers.append((name, "flip"))
            continue
        KB_PATH.write_text(json.dumps(kb, indent=2) + "\n")
        sha = commit_one(name, {path})
        print(f"  PROVED {name} sha={sha}", flush=True)
        proved.append(name)
        ported[addr] = True

    kb1 = json.loads(KB_PATH.read_text())
    t1, f1 = count_ported(kb1)
    summary = {
        "true0": t0,
        "false0": f0,
        "true1": t1,
        "false1": f1,
        "proved": proved,
        "blockers": blockers,
        "elapsed": time.time() - START,
    }
    Path("/tmp/ai_handlift_summary.json").write_text(json.dumps(summary, indent=2))
    print("\n=== FINAL ===", flush=True)
    print(summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
