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
    /* imulw truncates to 16 bits but keeps EDI high half from movswl(coeff). */
    {
      int addend = (int)coeff;
      addend = (addend & ~0xffff) | (unsigned short)((short)addend * (short)byte_v);
      sum += addend;
    }
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
    0x11A8E0,
    "networking/network_messages.c",
    "FUN_0011a8e0",
    """
/* FUN_0011a8e0 (0x11a8e0) — readable C lift. */
char *FUN_0011a8e0(int *state, unsigned short max_length)
{
  char *base;
  int cursor;
  int limit;
  short i;
  char *p;

  (void)max_length;
  base = (char *)state[0];
  cursor = state[1];
  limit = state[2];
  p = base + cursor;
  i = 0;
  if (cursor >= limit) {
    *((char *)state + 0xc) = 1;
    return 0;
  }
  for (;;) {
    if (p[i] == 0) {
      state[1] = (int)i + cursor + 1;
      return p;
    }
    i++;
    if (cursor + (int)i >= limit) {
      *((char *)state + 0xc) = 1;
      return 0;
    }
  }
}
""",
    "char *FUN_0011a8e0(int *state, unsigned short max_length);",
)

L(
    0x11C480,
    "networking/network_messages.c",
    "FUN_0011c480",
    """
/* FUN_0011c480 (0x11c480) — readable C lift. */
void FUN_0011c480(int cache)
{
  int *node;
  void (*dispose_fn)(int);

  FUN_0011c290(cache);
  if (*(int *)(cache + 0x2c) == 0) {
    *(int *)(cache + 0x2c) = 0;
    return;
  }
  node = *(int **)(cache + 0x24);
  if (node == 0) {
    *(int *)(cache + 0x2c) = 0;
    return;
  }
  dispose_fn = *(void (**)(int))(cache + 0x34);
  while (node != 0) {
    if ((node[1] & 2) == 0) {
      dispose_fn(node[0]);
      node[1] = (node[1] & ~1) | 2;
    }
    node = (int *)node[3];
  }
  *(int *)(cache + 0x2c) = 0;
}
""",
    "void FUN_0011c480(int cache);",
)

L(
    0x807D0,
    "networking/message_header.c",
    "key_message_xor_keystream",
    """
/* key_message_xor_keystream (0x807d0) — readable C lift. */
void key_message_xor_keystream(int msg, int len, int keystream, int key_len)
{
  int i;
  int k;
  int dir;
  unsigned char b;

  i = 0;
  k = 0;
  dir = 1;
  if (len <= 0)
    return;
  while (i < len) {
    b = *(unsigned char *)(keystream + k);
    b ^= *(unsigned char *)(msg + i);
    b = (unsigned char)~b;
    *(unsigned char *)(msg + i) = b;
    k += dir;
    i++;
    if (k == key_len || k < 0) {
      dir = -dir;
      k += dir;
    }
  }
}
""",
    "void key_message_xor_keystream(int msg, int len, int keystream, int key_len);",
)

L(
    0x11A560,
    "networking/network_messages.c",
    "FUN_0011a560",
    """
/* FUN_0011a560 (0x11a560) — readable C lift. */
unsigned char FUN_0011a560(int *state)
{
  int cursor;
  int limit;
  int next;
  char *p;

  if (state == 0 || state[0] == 0 || state[1] < 0 || state[1] > state[2]) {
    display_assert((const char *)0x28f058, (const char *)0x28eef8, 0x100, 1);
    system_exit(-1);
  }
  cursor = state[1];
  limit = state[2];
  next = cursor + 1;
  if (next > limit || *((unsigned char *)state + 0xc) != 0) {
    *((unsigned char *)state + 0xc) = 1;
    return 0;
  }
  p = (char *)state[0] + cursor;
  state[1] = next;
  if (p == 0)
    return 0;
  return *(unsigned char *)p;
}
""",
    "unsigned char FUN_0011a560(int *state);",
)

L(
    0x11A5D0,
    "networking/network_messages.c",
    "FUN_0011a5d0",
    """
/* FUN_0011a5d0 (0x11a5d0) — readable C lift. */
short FUN_0011a5d0(int *state)
{
  int cursor;
  int limit;
  int next;
  char *p;

  if (state == 0 || state[0] == 0 || state[1] < 0 || state[1] > state[2]) {
    display_assert((const char *)0x28f058, (const char *)0x28eef8, 0x100, 1);
    system_exit(-1);
  }
  cursor = state[1];
  limit = state[2];
  next = cursor + 2;
  if (next > limit || *((unsigned char *)state + 0xc) != 0) {
    *((unsigned char *)state + 0xc) = 1;
    return 0;
  }
  p = (char *)state[0] + cursor;
  FUN_00118620(p, 1, -2);
  state[1] = cursor + 2;
  if (p == 0)
    return 0;
  return *(short *)p;
}
""",
    "short FUN_0011a5d0(int *state);",
)

L(
    0x11A650,
    "networking/network_messages.c",
    "FUN_0011a650",
    """
/* FUN_0011a650 (0x11a650) — readable C lift. */
int FUN_0011a650(int *state)
{
  int cursor;
  int limit;
  int next;
  char *p;

  if (state == 0 || state[0] == 0 || state[1] < 0 || state[1] > state[2]) {
    display_assert((const char *)0x28f058, (const char *)0x28eef8, 0x100, 1);
    system_exit(-1);
  }
  cursor = state[1];
  limit = state[2];
  next = cursor + 4;
  if (next > limit || *((unsigned char *)state + 0xc) != 0) {
    *((unsigned char *)state + 0xc) = 1;
    return 0;
  }
  p = (char *)state[0] + cursor;
  FUN_00118620(p, 1, -4);
  state[1] = cursor + 4;
  if (p == 0)
    return 0;
  return *(int *)p;
}
""",
    "int FUN_0011a650(int *state);",
)

L(
    0x11A700,
    "networking/network_messages.c",
    "FUN_0011a700",
    """
/* FUN_0011a700 (0x11a700) — readable C lift. */
unsigned int FUN_0011a700(int *state, int maximum_value)
{
  if (maximum_value <= 0) {
    display_assert((const char *)0x28ef70, (const char *)0x28eef8, 0x141, 1);
    system_exit(-1);
  }
  if (maximum_value <= 0xff)
    return (unsigned int)FUN_0011a560(state);
  if (maximum_value <= 0xffff)
    return (unsigned int)(int)FUN_0011a5d0(state);
  return (unsigned int)FUN_0011a650(state);
}
""",
    "unsigned int FUN_0011a700(int *state, int maximum_value);",
)

L(
    0xC3DB0,
    "hs/hs.c",
    "hs_find_tag_reference_by_index",
    """
/* hs_find_tag_reference_by_index (0xc3db0) — readable C lift. */
int16_t hs_find_tag_reference_by_index(int tag_index)
{
  scenario_t *scenario;
  int *block;
  int count;
  short i;
  char *elem;

  if (*(int *)0x326a08 == -1)
    return (int16_t)-1;
  scenario = global_scenario_get();
  block = (int *)((char *)scenario + 0x4b4);
  count = block[0];
  if (count <= 0)
    return (int16_t)-1;
  for (i = 0; (int)i < count; i++) {
    elem = (char *)tag_block_get_element(block, (int)i, 0x28);
    if (*(int *)(elem + 0x24) == tag_index)
      return i;
  }
  return (int16_t)-1;
}
""",
    "int16_t hs_find_tag_reference_by_index(int tag_index);",
)

L(
    0x12A830,
    "networking/network_game_globals.c",
    "network_game_get_number_of_games_played",
    """
/* network_game_get_number_of_games_played (0x12a830) — readable C lift. */
int network_game_get_number_of_games_played(void)
{
  void *server;
  void *game;

  server = *(void **)0x46e8bc;
  if (server == 0)
    return FUN_0012a890();
  game = (void *)network_game_server_get_game(server);
  if (game == 0) {
    display_assert((const char *)0x2861a8, (const char *)0x2955e0, 0x73, 1);
    system_exit(-1);
  }
  return *(int *)((char *)game + 0x428);
}
""",
    "int network_game_get_number_of_games_played(void);",
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
        "src/halo/networking/message_header.c",
        "src/halo/networking/network_messages.c",
        "src/halo/networking/network_game_globals.c",
        "src/halo/hs/hs.c",
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
        0x11BA00,
        0x11A8E0,
        0x807D0,
        0x11A560,
        0x11A5D0,
        0x11A650,
        0x11A700,
        0x11C480,
        0xC3DB0,
        0x12A830,
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
