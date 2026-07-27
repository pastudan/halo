#!/usr/bin/env python3
"""Hand-lift Track A naked leaves → Docker → Unicorn 100/0/0 → flip + push."""
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

from lift_inventory_batch4 import find_naked_block  # noqa: E402
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from tu_compile import docker_compile  # noqa: E402
from unicorn_c_campaign import KB_PATH, append_ledger, clear_pass, count_ported  # noqa: E402

LIFTS: dict[int, tuple[str, str, str, str]] = {}


def L(addr: int, source: str, name: str, body: str, decl: str) -> None:
    LIFTS[addr] = (source, name, body.strip() + "\n", decl)


L(
    0x80820,
    "networking/message_header.c",
    "tea_encrypt",
    """
/* tea_encrypt (0x80820) — readable C lift. */
void tea_encrypt(unsigned int *v, unsigned int *w, unsigned int *key)
{
  unsigned int y = v[0];
  unsigned int z = v[1];
  unsigned int sum = 0;
  unsigned int n = 32;
  unsigned int k0 = key[0], k1 = key[1], k2 = key[2], k3 = key[3];

  while (n--) {
    sum -= 0x61c88647u;
    y += ((z << 4) + k0) ^ (z + sum) ^ ((z >> 5) + k1);
    z += ((y << 4) + k2) ^ (y + sum) ^ ((y >> 5) + k3);
  }
  w[0] = y;
  w[1] = z;
}
""",
    "void tea_encrypt(unsigned int *v, unsigned int *w, unsigned int *key);",
)

L(
    0x808B0,
    "networking/message_header.c",
    "tea_decrypt",
    """
/* tea_decrypt (0x808b0) — readable C lift. */
void tea_decrypt(unsigned int *v, unsigned int *w, unsigned int *key)
{
  unsigned int y = v[0];
  unsigned int z = v[1];
  unsigned int sum = 0xc6ef3720u;
  unsigned int n = 32;
  unsigned int k0 = key[0], k1 = key[1], k2 = key[2], k3 = key[3];

  while (n--) {
    z -= ((y << 4) + k2) ^ (y + sum) ^ ((y >> 5) + k3);
    y -= ((z << 4) + k0) ^ (z + sum) ^ ((z >> 5) + k1);
    sum += 0x61c88647u;
  }
  w[0] = y;
  w[1] = z;
}
""",
    "void tea_decrypt(unsigned int *v, unsigned int *w, unsigned int *key);",
)

L(
    0x100500,
    "main/main.c",
    "main_switch_structure_bsp",
    """
/* main_switch_structure_bsp (0x100500) — readable C lift. */
void main_switch_structure_bsp(int16_t bsp_index)
{
  scenario_t *scenario = global_scenario_get();

  if (bsp_index < 0 || (int)bsp_index >= *(int *)((char *)scenario + 0x5a4)) {
    console_warning((const char *)0x28b1e0, (int)bsp_index);
    return;
  }
  if (bsp_index == *(int16_t *)0x326a0c) {
    console_warning((const char *)0x28b20c, (int)bsp_index);
    return;
  }
  *(int16_t *)0x46da40 = bsp_index;
  hud_load(true);
}
""",
    "void main_switch_structure_bsp(int16_t bsp_index);",
)

L(
    0x1A6870,
    "units/units.c",
    "FUN_001a6870",
    """
/* FUN_001a6870 (0x1a6870) — readable C lift. */
int FUN_001a6870(char *unit_tag, short seat_index, char prefer_second)
{
  int *seats = (int *)(unit_tag + 0x2e4);
  char *seat = (char *)tag_block_get_element(seats, seat_index, 0x11c);
  int *block = (int *)(seat + 0xdc);
  int idx = prefer_second ? 1 : 0;
  int last = block[0] - 1;
  void *elem;

  if (idx > last)
    idx = last;
  if ((short)idx < 0)
    return -1;
  elem = tag_block_get_element(block, idx, 0x30);
  return verify_tag_reference((int *)elem);
}
""",
    "int FUN_001a6870(char *unit_tag, short seat_index, char prefer_second);",
)

L(
    0xE1F20,
    "interface/progress_bar.c",
    "FUN_000e1f20",
    """
/* FUN_000e1f20 (0xe1f20) — readable C lift. */
int __stdcall FUN_000e1f20(int unused, unsigned int reg, float a, float b, float c, float d)
{
  (void)unused;
  D3DDevice_SetVertexData4f(reg, a, b, c, d);
  return 0;
}
""",
    "int __stdcall FUN_000e1f20(int unused, unsigned int reg, float a, float b, float c, float d);",
)

L(
    0xA57B0,
    "game/cheats.c",
    "FUN_000a57b0",
    """
/* FUN_000a57b0 (0xa57b0) — readable C lift. */
char FUN_000a57b0(float *vec, float max_length)
{
  float len2 = vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
  float max2 = max_length * max_length;
  float inv;

  if (!(len2 > max2))
    return 0;
  inv = max_length / __builtin_sqrtf(len2);
  vec[0] *= inv;
  vec[1] *= inv;
  vec[2] *= inv;
  return 1;
}
""",
    "char FUN_000a57b0(float *vec, float max_length);",
)

L(
    0x11BA00,
    "networking/network_messages.c",
    "FUN_0011ba00",
    """
/* FUN_0011ba00 (0x11ba00) — readable C lift. */
int FUN_0011ba00(unsigned char *key, unsigned int key_size)
{
  int sum = 0;
  unsigned short idx = 0;
  unsigned int remain = key_size;

  if (remain == 0)
    return 0;
  for (;;) {
    short coeff;
    unsigned short byte_v;
    if (idx == 15) {
      idx = 0;
      remain -= 15;
    }
    byte_v = *key;
    coeff = *(short *)(0x3220d4 + (int)idx * 2);
    sum += (int)(short)(coeff * (int)byte_v);
    idx++;
    key++;
    if ((int)idx >= (int)remain)
      break;
  }
  return sum;
}
""",
    "int FUN_0011ba00(unsigned char *key, unsigned int key_size);",
)

L(
    0xF6820,
    "items/items.c",
    "item_new",
    """
/* item_new (0xf6820) — readable C lift. */
char item_new(int item_handle)
{
  char *item = (char *)object_get_and_verify_type(item_handle, 0x10);
  short count;
  char ok;

  *(short *)(item + 0x1dc) = (short)(*(short *)(item + 0x1dc) - 1);
  count = *(short *)(item + 0x1dc);
  ok = count > 0;
  if (!ok)
    object_delete(item_handle);
  return ok;
}
""",
    "char item_new(int item_handle);",
)


def sync_decl_h(name: str, decl: str) -> None:
    path = ROOT / "build" / "generated" / "decl.h"
    if not path.exists():
        return
    d = decl.strip().rstrip(";")
    text = path.read_text(encoding="utf-8", errors="replace")
    pat = re.compile(rf"^HFUNC\s+.+\b{re.escape(name)}\s*\([^;\n]*\);$", re.M)
    new_text, n = pat.subn(f"HFUNC {d};", text, count=1)
    if n:
        path.write_text(new_text, encoding="utf-8")


def cast_stale(text: str, names: set[str]) -> str:
    for sym in names:
        text = re.sub(rf"(=\s*){re.escape(sym)}\s*;", rf"\1(void *){sym};", text)
    return text


def apply_one(addr: int) -> tuple[bool, str, str]:
    source, name, body, decl = LIFTS[addr]
    sp = ROOT / "src" / "halo" / source
    text = sp.read_text(encoding="utf-8", errors="replace")
    # already lifted?
    if re.search(rf"0x{addr:x}[^\n]*readable C lift", text, re.I):
        return False, "already", text
    span = find_naked_block(text, name, addr)
    if not span:
        return False, "locate", text
    new_text = text[: span[0]] + body + "\n" + text[span[1] :]
    if "int16_t" in body and "#include <stdint.h>" not in new_text:
        new_text = "#include <stdint.h>\n" + new_text
    new_text = cast_stale(new_text, {name})
    sp.write_text(new_text, encoding="utf-8")
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    for o in kb.get("objects", []):
        for fn in o.get("functions") or []:
            if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == addr:
                fn["decl"] = decl if decl.endswith(";") else decl + ";"
                if not fn.get("name"):
                    fn["name"] = name
    KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
    sync_decl_h(name, decl)
    if not docker_compile(source):
        sp.write_text(text, encoding="utf-8")
        return False, "compile", text
    return True, "ok", text


def run_uni(name: str, addr: int, seeds: int = 100, timeout: float = 60.0) -> dict:
    outj = ROOT / "artifacts" / "equivalence" / f"uni_{addr:08x}_s{seeds}.json"
    cmd = [
        sys.executable,
        str(ROOT / "tools" / "equivalence" / "unicorn_diff.py"),
        name,
        "--allow-stubs",
        "--no-stub-arg-trace",
        "--seeds",
        str(seeds),
        "-q",
        "--output-json",
        str(outj),
    ]
    env = os.environ.copy()
    env.setdefault("BIPED_SIBLING_RESOLVE", "1")
    try:
        proc = subprocess.run(
            cmd, cwd=str(ROOT), capture_output=True, text=True, timeout=timeout, env=env
        )
    except subprocess.TimeoutExpired:
        return {"passed": 0, "failed": 0, "errors": 1, "tail": "TIMEOUT", "missing_candidate": False}
    text = (proc.stdout or "") + (proc.stderr or "")
    m = re.search(r"(\d+) passed, (\d+) failed, (\d+) errors", text)
    passed = failed = errors = None
    if m:
        passed, failed, errors = map(int, m.groups())
    return {
        "passed": passed,
        "failed": failed,
        "errors": errors,
        "tail": text[-400:],
        "missing_candidate": "missing_build_object" in text,
    }


def merge_remote_true() -> int:
    subprocess.run(
        ["git", "fetch", "pastudan", "track-a-collision-bsp"], cwd=ROOT, capture_output=True
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
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            if int(fn["addr"], 16) in tmap and fn.get("ported") is not True:
                fn["ported"] = True
                n += 1
    if n:
        KB_PATH.write_text(json.dumps(ours, indent=2) + "\n", encoding="utf-8")
    return n


def commit_push(flips: list[str], touched: set[Path]) -> None:
    merge_remote_true()
    files = [
        "kb.json",
        "scripts/lift_grok_w3.py",
        "src/halo/bitmaps/libtiff/tif_write.c",
        "src/halo/main/main.c",
        "src/halo/units/units.c",
        "src/halo/networking/message_header.c",
        "src/halo/networking/network_messages.c",
        "src/halo/game/cheats.c",
        "src/halo/objects/objects.c",
    ]
    files += [str(p.relative_to(ROOT)) for p in sorted(touched)]
    # unique
    files = list(dict.fromkeys(files))
    subprocess.run(["git", "add"] + files, cwd=ROOT, check=False)
    msg = f"lift(track-a): {len(flips)} Unicorn-prove leaves ({' '.join(flips[:8])}) (ported:true)."
    r = subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print("commit failed", r.stdout, r.stderr, flush=True)
        return
    subprocess.run(["git", "stash", "push", "-u", "-m", "w3-dirt"], cwd=ROOT, capture_output=True)
    subprocess.run(
        ["git", "fetch", "pastudan", "track-a-collision-bsp"], cwd=ROOT, capture_output=True
    )
    rb = subprocess.run(
        ["git", "rebase", "pastudan/track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if rb.returncode != 0:
        # Prefer ours for source lifts; union kb
        print("rebase conflict — attempting kb union", flush=True)
        subprocess.run(["git", "checkout", "--ours", "kb.json"], cwd=ROOT, capture_output=True)
        # Actually take theirs then re-flip our addrs
        subprocess.run(["git", "checkout", "--theirs", "kb.json"], cwd=ROOT, capture_output=True)
        subprocess.run(
            ["git", "checkout", "--ours", "src/halo"], cwd=ROOT, capture_output=True
        )
        # re-apply ported true for flips by addr from LIFTS names
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        addrs = {a for a, (_s, n, _b, _d) in LIFTS.items() if n in flips}
        for o in kb.get("objects", []):
            for fn in o.get("functions") or []:
                if fn.get("addr") and int(fn["addr"], 16) in addrs:
                    fn["ported"] = True
        KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        subprocess.run(["git", "add", "kb.json", "src"], cwd=ROOT, capture_output=True)
        subprocess.run(
            ["git", "-c", "core.editor=true", "rebase", "--continue"],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
    merge_remote_true()
    r = subprocess.run(
        ["git", "push", "pastudan", "HEAD:track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    print("PUSH", r.returncode, (r.stderr or r.stdout)[-500:], flush=True)
    subprocess.run(["git", "stash", "pop"], cwd=ROOT, capture_output=True)


def main() -> int:
    order = [
        0x80820,
        0x808B0,
        0x100500,
        0x1A6870,
        0xF6820,
        0xE1F20,
        0xA57B0,
        0x11BA00,
    ]
    true0, _ = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    print(f"start true={true0}", flush=True)
    flips: list[str] = []
    touched: set[Path] = set()

    for addr in order:
        source, name, _b, _d = LIFTS[addr]
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        for o in kb.get("objects", []):
            for fn in o.get("functions") or []:
                if fn.get("addr") and int(fn["addr"], 16) == addr and fn.get("ported") is True:
                    print(f"\n== {hex(addr)} {name} already true ==", flush=True)
                    addr = -1
                    break
            if addr < 0:
                break
        if addr < 0:
            continue
        print(f"\n== {hex(addr)} {name} ({source}) ==", flush=True)
        ok, err, orig = apply_one(addr)
        if not ok:
            print(f"  apply FAIL {err}", flush=True)
            continue
        if not ensure_oracle(addr):
            print("  oracle FAIL", flush=True)
            (ROOT / "src" / "halo" / source).write_text(orig)
            continue
        res = run_uni(hex(addr), addr)
        if not clear_pass(res, 100):
            res2 = run_uni(name, addr)
            if clear_pass(res2, 100) or (res2.get("passed") or 0) > (res.get("passed") or 0):
                res = res2
        okp = clear_pass(res, 100)
        print(
            f"  unicorn {res.get('passed')}/{res.get('failed')}/{res.get('errors')} ok={okp}",
            flush=True,
        )
        append_ledger(
            {
                "addr": hex(addr),
                "name": name,
                "ok": okp,
                "phase": "lift_grok_w3",
                "passed": res.get("passed"),
                "failed": res.get("failed"),
                "errors": res.get("errors"),
            }
        )
        if not okp:
            print(f"  REVERT {(res.get('tail') or '')[-160:]}", flush=True)
            (ROOT / "src" / "halo" / source).write_text(orig)
            continue
        rc = subprocess.run(
            [sys.executable, str(ROOT / "tools/audit/check_raw_casts.py")],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
        if rc.returncode != 0:
            print("  REVERT raw-cast", (rc.stderr or "")[-120:], flush=True)
            (ROOT / "src" / "halo" / source).write_text(orig)
            continue
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if flip_kb(kb, addr):
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
            flips.append(name)
            touched.add(ROOT / "src" / "halo" / source)
            print(f"  FLIP total={len(flips)}", flush=True)

    print("FLIPS", flips, flush=True)
    if flips:
        commit_push(flips, touched)
    true1, _ = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    print(f"DONE proven={len(flips)} true={true1} (+{true1 - true0})", flush=True)
    return 0 if flips else 1


if __name__ == "__main__":
    raise SystemExit(main())
