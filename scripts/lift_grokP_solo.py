#!/usr/bin/env python3
"""grokP-solo: exclusive rasterizer + smallest dynavobgeom falses → Unicorn 100/0/0."""
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

from lift_inventory_batch4 import L, LIFTS, apply_lifts  # noqa: E402

LIFTS.clear()

from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from tu_compile import docker_compile  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
)

SEEDS = 100
TIMEOUT = 90.0

# --- smallest dynavobgeom by span ---

L(
    0x15E650,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_0015e650",
    """
/* FUN_0015e650 (0x15e650) — readable C lift. */
void FUN_0015e650(void *a, int a_idx, int b, int c, void *d, int d_idx)
{
  if (!a) {
    if (a_idx != -1) {
      display_assert((const char *)0x2a10b4, (const char *)0x2a0110, 0x479, 1);
      system_exit(-1);
    }
  } else if (a_idx != -1) {
    display_assert((const char *)0x2a107c, (const char *)0x2a0110, 0x47a, 1);
    system_exit(-1);
  }

  if (!d) {
    if (d_idx != -1) {
      display_assert((const char *)0x2a1048, (const char *)0x2a0110, 0x47d, 1);
      system_exit(-1);
    }
  } else if (d_idx != -1) {
    display_assert((const char *)0x2a1014, (const char *)0x2a0110, 0x47e, 1);
    system_exit(-1);
  }

  if (a) {
    if (d)
      ((void (*)(void *, int, int, void *))FUN_0015e430)(a, b, c, d);
    else
      ((void (*)(void *, int, int, int))FUN_0015e0f0)(a, b, c, d_idx);
  } else if (d) {
    ((void (*)(int, int, int, void *))FUN_0015dc10)(a_idx, b, c, d);
  } else {
    ((void (*)(int, int, int, int))FUN_0015d8b0)(a_idx, b, c, d_idx);
  }
}
""",
    "void FUN_0015e650(void *a, int a_idx, int b, int c, void *d, int d_idx);",
)

L(
    0x160C30,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_00160c30",
    """
/* FUN_00160c30 (0x160c30) — readable C lift. */
void FUN_00160c30(void)
{
  short mode;
  int bitmap;

  if (!*(int *)0x476ab0) {
    display_assert((const char *)0x29dc40, (const char *)0x2a18c0, 0x11, 1);
    system_exit(-1);
  }
  FUN_0016f910(3);
  mode = *(short *)0x3256bc;
  if (mode != 0 && mode != 2 && mode != 6 && mode != 3 && mode != 4 &&
      mode != 7 && mode != 5 && mode != 8)
    return;
  if (!*(unsigned char *)0x3256c9)
    return;

  bitmap = *(int *)(*(int *)0x476204 + 0x1c);
  rasterizer_set_texture_direct(3, bitmap, 0);

  D3DDevice_SetTextureStageState(3, 0xa, 3);
  D3DDevice_SetTextureStageState(3, 0xb, 3);
  D3DDevice_SetTextureStageState(3, 0xc, 3);
  D3DDevice_SetTextureStageState(3, 0xd, 2);
  D3DDevice_SetTextureStageState(3, 0xe, 2);
  D3DDevice_SetTextureStageState(3, 0xf, 2);

  D3DDevice_SetRenderState_CullMode(0x901);
  D3DDevice_SetRenderState_Simple(0x40358, 0x1010101);
  *(unsigned int *)0x1fb7a4 = 0x1010101;
  D3DDevice_SetRenderState_Simple(0x40304, 0);
  *(unsigned int *)0x1fb784 = 0;
  D3DDevice_SetRenderState_Simple(0x40340, 0x7f);
  *(unsigned int *)0x1fb78c = 0x7f;
  D3DDevice_SetRenderState_ZEnable(1);
  D3DDevice_SetRenderState_Simple(0x40354, 0x203);
  *(unsigned int *)0x1fb77c = 0x203;
  D3DDevice_SetRenderState_Simple(0x4035c, 1);
  *(unsigned int *)0x1fb798 = 1;
  D3DDevice_SetRenderState_ZBias(0);
}
""",
    "void FUN_00160c30(void);",
)

L(
    0x165CB0,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_00165cb0",
    """
/* FUN_00165cb0 (0x165cb0) — readable C lift. */
void FUN_00165cb0(void *shader, int unused, int a2, int a3, int a4, unsigned short *block)
{
  int perm;
  int count;

  (void)unused;
  if (!*(int *)0x476ab0) {
    display_assert((const char *)0x29dc40, (const char *)0x2a1cc8, 0x1a7, 1);
    system_exit(-1);
  }
  if (*(short *)0x3256bc != 0)
    return;
  if (!*(unsigned char *)0x3256d4)
    return;
  if (!shader) {
    display_assert((const char *)0x2a18b8, (const char *)0x2a1cc8, 0x1ae, 1);
    system_exit(-1);
  }
  FUN_001906b0(shader, 3);
  if (!block) {
    display_assert((const char *)0x2a19cc, (const char *)0x2a1cc8, 0x1b3, 1);
    system_exit(-1);
  }
  perm = shader_get_vertex_shader_permutation(shader);
  FUN_00178b40(6, (int)*block, perm);
  ((void (*)(int, int, int, void *))FUN_0015dc10)(a2, a3, a4, block);
  if (*(short *)0x3256ba == 2) {
    count = a4;
    *(int *)0x5a54b4 = *(int *)0x5a54b4 + 1;
    *(int *)0x5a54b0 = *(int *)0x5a54b0 + count;
    *(int *)0x5a54ac =
        *(int *)0x5a54ac +
        ((int (*)(int, int, int))rasterizer_frame_statistics_count_static_vertices)(a2, a3, count);
  }
}
""",
    "void FUN_00165cb0(void *shader, int unused, int a2, int a3, int a4, unsigned short *block);",
)

L(
    0x1677D0,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_001677d0",
    """
/* FUN_001677d0 (0x1677d0) — readable C lift. */
void FUN_001677d0(void *shader, int unused, int a2, int a3, int a4, unsigned short *block)
{
  short slot;
  int perm;
  int count;

  (void)unused;
  if (!*(int *)0x476ab0) {
    display_assert((const char *)0x29dc40, (const char *)0x2a1cc8, 0x3dc, 1);
    system_exit(-1);
  }
  if (!((char (*)(void))FUN_00166010)())
    return;
  slot = *(short *)0x47ddc8;
  if (slot != 0 && slot != 1) {
    display_assert((const char *)0x2a2180, (const char *)0x2a1cc8, 0x3e0, 1);
    system_exit(-1);
  }
  if (!*(unsigned char *)0x47dd89)
    return;
  if (!*(int *)0x5a5df0) {
    display_assert((const char *)0x2a215c, (const char *)0x2a1cc8, 0x3e4, 1);
    system_exit(-1);
  }
  if (*(short *)0x5a5bc2 < 0 || *(short *)0x5a5bc2 >= 4) {
    display_assert((const char *)0x2a20f8, (const char *)0x2a1cc8, 0x3e5, 1);
    system_exit(-1);
  }
  perm = shader_get_vertex_shader_permutation(shader);
  FUN_00178b40(8, (int)*block, perm);
  ((void (*)(int, int, int, void *))FUN_0015dc10)(a2, a3, a4, block);
  if (*(short *)0x3256ba == 2) {
    count = a4;
    *(int *)0x5a54c0 = *(int *)0x5a54c0 + 1;
    *(int *)0x5a54bc = *(int *)0x5a54bc + count;
    *(int *)0x5a54b8 =
        *(int *)0x5a54b8 +
        ((int (*)(int, int, int))rasterizer_frame_statistics_count_static_vertices)(a2, a3, count);
  }
}
""",
    "void FUN_001677d0(void *shader, int unused, int a2, int a3, int a4, unsigned short *block);",
)

# --- exclusive remaining naked ---

L(
    0x17BCA0,
    "rasterizer/rasterizer.c",
    "FUN_0017bca0",
    """
/* FUN_0017bca0 (0x17bca0) — readable C lift. */
char FUN_0017bca0(void *shader, void *state)
{
  void *sh;
  int *block;
  int count;
  int flags;
  int i;
  char ok;
  void *elem;
  int w;
  int w2;
  int bit;
  int idx;
  int v;
  int v2;

  ok = 1;
  if (!shader) {
    display_assert((const char *)0x2a18b8, (const char *)0x2ae9d0, 0x64, 1);
    system_exit(-1);
  }
  if (!state) {
    display_assert((const char *)0x29e09c, (const char *)0x2ae9d0, 0x65, 1);
    system_exit(-1);
  }
  sh = FUN_001906b0(shader, 6);
  csmemset(state, 0, 0xf0);
  block = (int *)((char *)sh + 0x54);
  *(int *)((char *)state + 0xd4) = (block[0] + 1) | 0x11000;
  count = block[0];
  if (count <= 0) {
    error(2, (const char *)0x2ae9a8);
    ok = 0;
  } else {
    flags = 0;
    if (count > 3)
      flags = 1;
    flags <<= 5;
    if (count > 2)
      flags |= 1;
    flags <<= 5;
    if (count > 1)
      flags |= 1;
    flags <<= 5;
    bit = (*(short *)((char *)sh + 0x2a) != 0) ? 1 : 0;
    flags |= bit + bit + 1;
    *(int *)((char *)state + 0xd8) = flags;

    if (block[0] > 0) {
      for (i = 0; i < block[0]; i++) {
        elem = tag_block_get_element(block, i, 0xdc);
        if (i != block[0] - 1) {
          w = *(short *)((char *)elem + 0x2e);
          v = ((int *)0x2ae974)[w] * (i + 1) + ((int *)0x2ae940)[w];
          ((int *)state)[i + 1] = v;
          w2 = *(short *)((char *)elem + 0x2c);
          idx = (((*(unsigned char *)elem) >> 1) & 1) * 0xd + w2;
          v2 = ((int *)0x2ae974)[w2] * (i + 1) + ((int *)0x2ae8d8)[idx];
          ((int *)((char *)state + 0x8c))[i] = v2;
        } else {
          *(int *)state = 0x18200000;
          *(int *)((char *)state + 0x88) = 0x8200000;
        }
        ((int *)((char *)state + 0x68))[i] = 0xc00;
        ((int *)((char *)state + 0xb4))[i] = 0xc00;
      }
      ok = 1;
    }
  }
  *(int *)((char *)state + 0x20) = 0xc;
  *(int *)((char *)state + 0x24) = 0x1c00;
  return ok;
}
""",
    "char FUN_0017bca0(void *shader, void *state);",
)

L(
    0x17AE90,
    "rasterizer/rasterizer.c",
    "FUN_0017ae90",
    """
/* FUN_0017ae90 (0x17ae90) — readable C lift. */
void FUN_0017ae90(int object_handle, int datum, float *position, int callback)
{
  void *group;
  float dx;
  float dy;
  float dz;
  float *dst;
  float *q;

  if (!callback)
    return;
  group = rasterizer_transparent_geometry_group_new();
  if (!position) {
    display_assert((const char *)0x2a1774, (const char *)0x2ae7f0, 0x58, 1);
    system_exit(-1);
  }
  if (!group) {
    if (!*(unsigned char *)0x47e4ca) {
      error(2, (const char *)0x2a1744);
      *(unsigned char *)0x47e4ca = 1;
    }
    return;
  }

  dx = position[0] - *(float *)0x5a5bc8;
  dy = position[1] - *(float *)0x5a5bcc;
  dz = position[2] - *(float *)0x5a5bd0;

  *(int *)((char *)group + 0x48) = callback;
  *(int *)((char *)group + 0x4c) = object_handle;
  *(int *)((char *)group + 0x50) = datum;
  *(int *)((char *)group + 0) = 0;
  *(int *)((char *)group + 4) = 0;
  *(int *)((char *)group + 8) = 0;
  *(int *)((char *)group + 0xc) = 0;
  *(short *)((char *)group + 0x10) = 0;
  *(short *)((char *)group + 0x14) = 0;
  *(int *)((char *)group + 0x58) = 0;
  *(int *)((char *)group + 0x5c) = 0;
  *(int *)((char *)group + 0x44) = -1;
  *(int *)((char *)group + 0x54) = -1;

  *(float *)((char *)group + 0x70) =
      -(*(float *)0x5a5bd4 * dx + *(float *)0x5a5bd8 * dy + *(float *)0x5a5bdc * dz);

  dst = (float *)((char *)group + 0x74);
  dst[0] = position[0];
  dst[1] = position[1];
  dst[2] = position[2];

  q = (float *)((char *)group + 0x80);
  q[0] = 0.0f;
  q[1] = 0.0f;
  q[2] = 0.0f;
  q[3] = 0.0f;

  *(int *)((char *)group + 0x98) = 0;
  *(unsigned char *)((char *)group + 0x9d) = 0;
  *(int *)((char *)group + 0x60) = 0;
  *(short *)((char *)group + 0x64) = 0;
  *(int *)((char *)group + 0x68) = 0;
  *(int *)((char *)group + 0x6c) = 0;
  *(float *)((char *)group + 0x40) = 1.0f;
  *(float *)((char *)group + 0x3c) = 1.0f;
  *(short *)((char *)group + 0x94) = -1;
  *(short *)((char *)group + 0x96) = -1;
}
""",
    "void FUN_0017ae90(int object_handle, int datum, float *position, int callback);",
)


def run_uni(name: str, addr: int) -> dict:
    outj = ROOT / "artifacts" / "equivalence" / f"uni_{addr:08x}_s{SEEDS}.json"
    outj.parent.mkdir(parents=True, exist_ok=True)
    logp = ROOT / "artifacts" / "equivalence" / f"{name}_smoke.log"
    cmd = [
        sys.executable,
        str(ROOT / "tools/equivalence/unicorn_diff.py"),
        name,
        "--allow-stubs",
        "--no-stub-arg-trace",
        "--seeds",
        str(SEEDS),
        "-q",
        "--output-json",
        str(outj),
    ]
    env = os.environ.copy()
    env.setdefault("BIPED_SIBLING_RESOLVE", "1")
    t0 = time.time()
    try:
        proc = subprocess.run(
            cmd,
            cwd=str(ROOT),
            capture_output=True,
            text=True,
            timeout=TIMEOUT,
            env=env,
        )
        timed_out = False
    except subprocess.TimeoutExpired as exc:
        timed_out = True
        proc = subprocess.CompletedProcess(cmd, 124, exc.stdout or "", "timeout")
    text = (proc.stdout or "") + (proc.stderr or "")
    logp.write_text(text, encoding="utf-8", errors="replace")
    m = re.search(r"(\d+) passed, (\d+) failed, (\d+) errors", text)
    passed = failed = errors = None
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
        "timeout": timed_out,
        "tail": text[-600:],
    }


def merge_remote_ported() -> int:
    subprocess.run(
        ["git", "fetch", "pastudan", "track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
    )
    r = subprocess.run(
        ["git", "show", "pastudan/track-a-collision-bsp:kb.json"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if r.returncode != 0 or not r.stdout:
        return 0
    theirs = json.loads(r.stdout)
    ours = json.loads(KB_PATH.read_text(encoding="utf-8"))
    tmap = {
        int(fn["addr"], 16)
        for o in theirs.get("objects", [])
        for fn in o.get("functions") or []
        if isinstance(fn, dict) and fn.get("addr") and fn.get("ported") is True
    }
    n = 0
    for o in ours.get("objects", []):
        for fn in o.get("functions") or []:
            if (
                isinstance(fn, dict)
                and fn.get("addr")
                and int(fn["addr"], 16) in tmap
                and fn.get("ported") is not True
            ):
                fn["ported"] = True
                n += 1
    if n:
        KB_PATH.write_text(json.dumps(ours, indent=2) + "\n", encoding="utf-8")
        print(f"merged {n} remote ported:true", flush=True)
    return n


def commit_push(names: list[str]) -> None:
    merge_remote_ported()
    subprocess.run(
        ["git", "add", "kb.json", "src/halo", "tools/equivalence/leaf_cache.json"],
        cwd=ROOT,
        capture_output=True,
    )
    msg = f"lift(track-a): {', '.join(names[:6])} Unicorn-prove {len(names)}."
    subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True)
    subprocess.run(
        ["git", "push", "pastudan", "HEAD:track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
    )
    print(f"pushed: {msg}", flush=True)


def main() -> int:
    print("apply lifts...", flush=True)
    results = apply_lifts(sorted(LIFTS.keys()))
    ok_lift = [r for r in results if r.get("ok")]
    print(f"lifted {len(ok_lift)}/{len(results)}", flush=True)
    for r in results:
        if not r.get("ok"):
            print(" lift-fail", r, flush=True)

    print("regen decl.h (local knowledge.py)...", flush=True)
    r = subprocess.run(
        [
            sys.executable,
            str(ROOT / "tools/analysis/knowledge.py"),
            "--gen-header",
            str(ROOT / "build/generated/decl.h"),
        ],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if r.returncode != 0:
        print("regen FAIL", (r.stderr or r.stdout)[-400:], flush=True)
        return 1

    tus = sorted({LIFTS[a][0] for a in LIFTS})
    for src in tus:
        print("compile", src, flush=True)
        if not docker_compile(src):
            print("COMPILE FAIL", src, flush=True)
            return 1

    lands: list[str] = []
    fails: list[dict] = []
    for addr in sorted(LIFTS.keys()):
        src, name, _body, _decl = LIFTS[addr]
        print(f"\n== prove {hex(addr)} {name} ==", flush=True)
        kb0 = json.loads(KB_PATH.read_text(encoding="utf-8"))
        already = False
        for o in kb0.get("objects", []):
            for fn in o.get("functions") or []:
                if (
                    isinstance(fn, dict)
                    and fn.get("addr")
                    and int(fn["addr"], 16) == addr
                    and fn.get("ported") is True
                ):
                    already = True
        if already:
            print(" already ported:true", flush=True)
            lands.append(name)
            continue
        if not ensure_oracle(addr):
            print(" oracle FAIL", flush=True)
            fails.append({"addr": hex(addr), "name": name, "err": "oracle"})
            continue
        res = run_uni(name, addr)
        print(
            f" {res.get('passed')}/{res.get('failed')}/{res.get('errors')} "
            f"dt={res['dt']} to={res['timeout']}",
            flush=True,
        )
        if not clear_pass(res, SEEDS):
            print(" FAIL", (res.get("tail") or "")[-300:], flush=True)
            fails.append(
                {
                    "addr": hex(addr),
                    "name": name,
                    "passed": res.get("passed"),
                    "failed": res.get("failed"),
                    "errors": res.get("errors"),
                    "timeout": res.get("timeout"),
                }
            )
            continue
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if not flip_kb(kb, addr):
            print(" flip miss", flush=True)
            fails.append({"addr": hex(addr), "name": name, "err": "flip"})
            continue
        KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        append_ledger(
            {
                "addr": hex(addr),
                "name": name,
                "source": src,
                "ok": True,
                "passed": res["passed"],
                "failed": 0,
                "errors": 0,
                "seeds": SEEDS,
                "phase": "grokP-solo",
            }
        )
        lands.append(name)
        print(" FLIP", name, flush=True)

    t, f = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    print(f"\nLANDS ({len(lands)}): {lands}", flush=True)
    print(f"FAILS ({len(fails)}): {fails}", flush=True)
    print(f"TIP {t}/{t+f} ({100 * t / (t + f):.2f}%)", flush=True)
    if lands:
        commit_push(lands)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
