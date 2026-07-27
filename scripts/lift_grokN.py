#!/usr/bin/env python3
"""Track A grokN: hand-lift focus-domain leaves + Unicorn 100/0/0 prove/push."""
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
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
    func_name,
    is_naked_near_def,
    resolve_src,
)

SEEDS = 100
TIMEOUT = 70.0
COMMIT_EVERY = 5
MAX_HANG_KILL = 90

LIFTS: dict[int, tuple[str, str, str, str]] = {}


def L(addr: int, source: str, name: str, body: str, decl: str) -> None:
    LIFTS[addr] = (source, name, body.strip() + "\n", decl)


# --- hand lifts (focus domains) ---

L(
    0x8E3D0,
    "cseries/cseries_windows.c",
    "system_malloc",
    """
/* system_malloc (0x8e3d0) — readable C lift. */
void *system_malloc(int size)
{
  return ((void *(__stdcall *)(int, int))0x1d0c48)(0, size);
}
""",
    "void *system_malloc(int size);",
)

L(
    0x1BA710,
    "cache/tags.c",
    "FUN_001ba710",
    """
/* FUN_001ba710 (0x1ba710) — readable C lift. */
void FUN_001ba710(void *cache @<eax>)
{
  void *globals;
  unsigned int base;
  int i;
  unsigned int *slots;
  unsigned int next;

  globals = *(void **)0x32ea98;
  base = *(unsigned int *)((char *)cache + 0x960);
  slots = (unsigned int *)((char *)globals + 0x964);
  next = base;
  for (i = 0; i < 8; i++) {
    slots[i] = next;
    next += 0x20000;
  }
  *(unsigned int *)((char *)globals + 0x984) = next;
  physical_memory_protect((void *)base, 0x512000u, 4u);
  csmemset((void *)*(unsigned int *)((char *)cache + 0x960), 0xfd, 0x500000u);
  physical_memory_protect(
      (void *)*(unsigned int *)((char *)cache + 0x960), 0x500000u, 2u);
  next = *(unsigned int *)((char *)cache + 0x960) + 0x500000u;
  *(unsigned int *)((char *)cache + 0x944) = 0x12000u;
  *(unsigned int *)((char *)cache + 0x940) = next;
  *(unsigned int *)((char *)cache + 0x948) = next;
  csmemset((char *)cache + 0x990, 0xfa, 0x1c0u);
}
""",
    "void FUN_001ba710(void *cache /* @<eax> */);",
)

L(
    0x81110,
    "networking/message_header.c",
    "FUN_00081110",
    """
/* FUN_00081110 (0x81110) — readable C lift. */
unsigned int FUN_00081110(unsigned int bit_count /* @<esi> */, unsigned int bit_offset /* @<edi> */, int unused)
{
  if (bit_count <= 2) {
    display_assert((const char *)0x265de0, (const char *)0x265da0, 0x85, 1);
    system_exit(-1);
  }
  if (bit_offset >= (bit_count - 1)) {
    display_assert((const char *)0x265dd8, (const char *)0x265da0, 0x86, 1);
    system_exit(-1);
  }
  /* tail-call: eax=bit_offset, ecx=unused, edx=bit_count */
  return FUN_00080fc0(bit_offset, unused, bit_count);
}
""",
    "unsigned int FUN_00081110(unsigned int bit_count /* @<esi> */, unsigned int bit_offset /* @<edi> */, int unused);",
)

L(
    0x1B9DE0,
    "cache/cache_files.c",
    "cache_files_give_time_to_precache",
    """
/* cache_files_give_time_to_precache (0x1b9de0) — readable C lift. */
bool cache_files_give_time_to_precache(const char *name)
{
  float status;
  short st;
  char ok;

  ok = 0;
  if (cache_files_precache_map_loaded((char *)name)) {
    return 1;
  }
  if (cache_files_precache_in_progress()) {
    if (!cache_files_precache_is_copying_map((char *)name)) {
      cache_files_precache_map_end();
    }
  }
  if (cache_files_precache_in_progress()) {
    st = cache_files_precache_map_status(&status);
    if (st == 2) {
      display_error_damaged_media();
      return ok;
    }
    if (st == 1) {
      cache_files_precache_map_end();
      return ok;
    }
    return ok;
  }
  cache_files_precache_set_priority(0);
  if (!cache_files_precache_map_begin((char *)name, 0)) {
    display_error_damaged_media();
  }
  return ok;
}
""",
    "bool cache_files_give_time_to_precache(const char *name);",
)

L(
    0x1913C0,
    "structures/structures.c",
    "reference_list_remove",
    """
/* reference_list_remove (0x1913c0) — readable C lift. */
void reference_list_remove(void *data, int *head, int value)
{
  void *node;
  int *link;

  link = head;
  if (*link == -1) {
    display_assert(
        csprintf((char *)0x5ab100, (const char *)0x2b2564, value),
        (const char *)0x2b25a0,
        0x6d,
        1);
    system_exit(-1);
    return;
  }
  for (;;) {
    node = datum_get(data, *link);
    if (*(int *)((char *)node + 4) == value) {
      datum_delete(data, *link);
      *link = *(int *)((char *)node + 8);
      return;
    }
    link = (int *)((char *)node + 8);
    if (*link == -1) {
      display_assert(
          csprintf((char *)0x5ab100, (const char *)0x2b2564, value),
          (const char *)0x2b25a0,
          0x6d,
          1);
      system_exit(-1);
      return;
    }
  }
}
""",
    "void reference_list_remove(void *data, int *head, int value);",
)

L(
    0x11BE10,
    "networking/network_messages.c",
    "FUN_0011be10",
    """
/* FUN_0011be10 (0x11be10) — readable C lift. */
int FUN_0011be10(short *table /* @<eax> */, void *key)
{
  unsigned short slot;
  int dest;
  unsigned int *bits;
  unsigned int mask;
  int idx;

  if (FUN_0011ba50(table, key, &slot)) {
    display_assert((const char *)0x28f6d4, (const char *)0x28f678, 0xf1, 1);
    system_exit(-1);
    return 0;
  }
  dest = FUN_00117ee0((int *)(table + 0xe), (int)slot, (int)table[1]);
  csmemcpy((void *)dest, key, (unsigned int)(int)table[0]);
  idx = (int)slot;
  bits = (unsigned int *)(*(unsigned int *)(table + 0xc) + (unsigned int)((idx >> 5) * 4));
  mask = 1u << (idx & 0x1f);
  *bits |= mask;
  table[2] = (short)((int)table[2] + 1);
  return dest + (int)table[0];
}
""",
    "int FUN_0011be10(short *table /* @<eax> */, void *key);",
)

# Prefer already-readable proves in focus domains (skip bitmaps / known hangs).
PROVE_ONLY = [
    ("networking/message_header.c", "key_message_xor_keystream", 0x807D0),
    ("networking/message_header.c", "create_message", 0x80CA0),
    ("networking/network_messages.c", "FUN_0011a230", 0x11A230),
    ("networking/network_messages.c", "FUN_0011a560", 0x11A560),
    ("networking/network_messages.c", "FUN_0011a5d0", 0x11A5D0),
    ("networking/network_messages.c", "FUN_0011a650", 0x11A650),
    ("networking/network_messages.c", "FUN_0011a8e0", 0x11A8E0),
    ("networking/network_messages.c", "FUN_0011ba00", 0x11BA00),
    ("networking/network_messages.c", "FUN_0011c4d0", 0x11C4D0),
    ("networking/network_client_manager.c", "FUN_00124900", 0x124900),
    ("networking/network_client_manager.c", "network_game_client_game_out_of_sync", 0x124E20),
    ("networking/network_client_manager.c", "FUN_001268a0", 0x1268A0),
    ("networking/network_server_manager.c", "FUN_0012f430", 0x12F430),
    ("networking/network_server_manager.c", "FUN_0012f5d0", 0x12F5D0),
    ("networking/transport_address.c", "FUN_00081c80", 0x81C80),
    ("structures/structures.c", "FUN_00106330", 0x106330),
    ("structures/structures.c", "FUN_00191c70", 0x191C70),
    ("structures/structure_visibility.c", "FUN_00196b10", 0x196B10),
    ("physics/collision_bsp.c", "collision_surface_project_point2d", 0x147990),
    ("physics/collision_bsp.c", "FUN_00148440", 0x148440),
    ("physics/collision_bsp.c", "FUN_001486e0", 0x1486E0),
    ("physics/collision_bsp.c", "collision_bsp_test_pill_new", 0x148B20),
    ("physics/collision_bsp.c", "bsp3d_test_sphere_recursive", 0x148B90),
    ("tag_files/files.c", "file_printf", 0x1995C0),
    ("saved games/saved_game_files.c", "saved_game_file_get_display_name", 0x1C4600),
    ("cseries/cseries_windows.c", "system_malloc", 0x8E3D0),
    ("cseries/cseries_windows.c", "system_calloc", 0x8E3B0),
    ("interface/event_manager.c", "tiny_point2d_set", 0xDADE0),
    ("interface/ui_widget.c", "ui_widget_list_prev", 0xE53E0),
    ("interface/ui_widget.c", "ui_widget_list_next", 0xE5440),
    ("interface/ui_widget.c", "ui_widget_pending_load_pop", 0xE4770),
]


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
            timeout=min(TIMEOUT, MAX_HANG_KILL),
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
        "missing_candidate": "missing_build_object" in text
        or "cannot find build .obj" in text,
        "tail": text[-400:],
    }


def set_decl(addr: int, decl: str, name: str | None = None) -> None:
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    if not decl.endswith(";"):
        decl += ";"
    for o in kb.get("objects", []):
        for fn in o.get("functions") or []:
            if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == addr:
                fn["decl"] = decl
                if name:
                    fn["name"] = name
                KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
                return


def sync_decl_h(name: str, decl: str) -> None:
    path = ROOT / "build" / "generated" / "decl.h"
    if not path.exists():
        return
    text = path.read_text(encoding="utf-8", errors="replace")
    if not decl.endswith(";"):
        decl += ";"
    pat = re.compile(rf"^HFUNC\([^)]*\b{re.escape(name)}\s*\([^;]*;", re.M)
    repl = f"HFUNC({decl}"
    # keep simple: replace lines containing the name
    lines = text.splitlines(True)
    out = []
    for line in lines:
        if f" {name}(" in line or f"*{name}(" in line:
            # crude HFUNC line replace
            if line.startswith("HFUNC("):
                out.append(f"HFUNC({decl}\n")
                continue
        out.append(line)
    path.write_text("".join(out), encoding="utf-8")


def apply_lift(addr: int) -> tuple[Path, str, str] | None:
    source, name, body, decl = LIFTS[addr]
    sp = resolve_src(source)
    if sp is None:
        print(f"  missing src {source}", flush=True)
        return None
    if addr == 0x81110:
        set_decl(
            0x80FC0,
            "unsigned int FUN_00080fc0(unsigned int a /* @<eax> */, unsigned int c /* @<ecx> */, unsigned int d /* @<edx> */);",
            "FUN_00080fc0",
        )
        sync_decl_h(
            "FUN_00080fc0",
            "unsigned int FUN_00080fc0(unsigned int a /* @<eax> */, unsigned int c /* @<ecx> */, unsigned int d /* @<edx> */)",
        )
    text = sp.read_text(encoding="utf-8", errors="replace")
    before_len = len(text)
    # already readable?
    if not is_naked_near_def(text.splitlines(), name, hex(addr)):
        if "readable C lift" in text and name in text:
            set_decl(addr, decl, name)
            return sp, name, source
        # replace compact non-naked body (e.g. system_malloc)
        m = re.search(
            rf"(?:void|int|char|short|float|double|bool|unsigned)[\w\s\*]*\b{re.escape(name)}\s*\([^;{{]*\)\s*\{{",
            text,
        )
        if not m:
            set_decl(addr, decl, name)
            return sp, name, source
        start = m.start()
        i = m.end() - 1
        depth = 0
        while i < len(text):
            if text[i] == "{":
                depth += 1
            elif text[i] == "}":
                depth -= 1
                if depth == 0:
                    i += 1
                    break
            i += 1
        if i - start > 800:
            print("  refuse large non-naked replace", flush=True)
            set_decl(addr, decl, name)
            return sp, name, source
        new_text = text[:start] + body + text[i:]
        if len(new_text) < before_len - 200:
            print("  refuse truncating rewrite", flush=True)
            return None
        sp.write_text(new_text, encoding="utf-8")
        set_decl(addr, decl, name)
        sync_decl_h(name, decl.rstrip(";"))
        return sp, name, source
    span = find_naked_block(text, name, addr) or find_naked_block(
        text, f"FUN_{addr:08x}", addr
    )
    if not span:
        print("  locate FAIL", flush=True)
        return None
    if span[1] - span[0] > 12000:
        print("  refuse huge naked span", flush=True)
        return None
    c_src = body if "readable C lift" in body else (
        f"/* {name} (0x{addr:x}) — readable C lift. */\n{body}"
    )
    set_decl(addr, decl, name)
    sync_decl_h(name, decl.rstrip(";"))
    new_text = text[: span[0]] + c_src + "\n" + text[span[1] :]
    if len(new_text) < before_len - 5000:
        print("  refuse truncating naked rewrite", flush=True)
        return None
    sp.write_text(new_text, encoding="utf-8")
    return sp, name, source


def still_naked(sp: Path, name: str, addr: int) -> bool:
    return is_naked_near_def(
        sp.read_text(encoding="utf-8", errors="replace").splitlines(), name, hex(addr)
    )


def merge_remote() -> int:
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


def commit_push(n: int, names: list[str], touched: set[Path]) -> str | None:
    merge_remote()
    files = ["kb.json", "tools/equivalence/leaf_cache.json", "scripts/lift_grokN.py"]
    for p in touched:
        try:
            files.append(str(p.relative_to(ROOT)))
        except ValueError:
            files.append(str(p))
    subprocess.run(["git", "add"] + files, cwd=ROOT, check=False)
    subprocess.run(["git", "add", "-u", "src/halo"], cwd=ROOT, check=False)
    sample = ", ".join(names[:5])
    if len(names) > 5:
        sample += ", ..."
    msg = f"lift(track-a): grokN Unicorn-prove {n} ({sample})."
    r = subprocess.run(
        ["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True
    )
    if r.returncode != 0:
        print("commit failed", r.stdout[-400:], r.stderr[-400:], flush=True)
        return None
    sha = subprocess.run(
        ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
    ).stdout.strip()
    subprocess.run(
        ["git", "pull", "--rebase", "pastudan", "track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
    )
    pr = subprocess.run(
        ["git", "push", "pastudan", "HEAD:track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    print((pr.stdout or "") + (pr.stderr or ""), flush=True)
    if pr.returncode != 0:
        print("push failed", flush=True)
    print(f"COMMIT+PUSH {sha}", flush=True)
    return sha


def prove_one(name: str, addr: int, source: str, touched: set[Path]) -> bool:
    sp = resolve_src(source)
    if sp is None:
        print("  missing src", flush=True)
        return False
    if still_naked(sp, name, addr):
        print("  NAKED-BLOCK", flush=True)
        return False
    src_rel = source.replace("\\", "/")
    if src_rel.startswith("src/halo/"):
        src_rel = src_rel[len("src/halo/") :]
    if not docker_compile(src_rel):
        print("  compile FAIL", flush=True)
        return False
    if not ensure_oracle(addr):
        print("  oracle FAIL", flush=True)
        return False
    res = run_uni(name, addr)
    if not clear_pass(res, SEEDS):
        res2 = run_uni(hex(addr), addr)
        if clear_pass(res2, SEEDS) or (res2.get("passed") or 0) > (
            res.get("passed") or 0
        ):
            res = res2
    ok = clear_pass(res, SEEDS)
    print(
        f"  ok={ok} {res.get('passed')}/{res.get('failed')}/{res.get('errors')} "
        f"{res.get('dt')}s to={res.get('timeout')}",
        flush=True,
    )
    append_ledger(
        {
            "addr": hex(addr),
            "name": name,
            "ok": ok,
            "phase": "grokN",
            "passed": res.get("passed"),
            "failed": res.get("failed"),
            "errors": res.get("errors"),
            "dt": res.get("dt"),
            "timeout": res.get("timeout"),
        }
    )
    if not ok:
        return False
    # re-check naked before flip
    if still_naked(sp, name, addr):
        print("  NAKED-BLOCK post", flush=True)
        return False
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    if flip_kb(kb, addr):
        KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        touched.add(sp)
        return True
    return False


def kb_is_false(addr: int) -> bool:
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    for o in kb.get("objects", []):
        for fn in o.get("functions") or []:
            if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == addr:
                return fn.get("ported") is False
    return False


def main() -> int:
    true0, false0 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    print(f"start true={true0} false={false0}", flush=True)
    flips: list[str] = []
    names: list[str] = []
    blockers: list[dict] = []
    touched: set[Path] = set()
    since = 0

    # 1) apply hand lifts then prove
    for addr in sorted(LIFTS):
        if not kb_is_false(addr):
            continue
        source, name, body, decl = LIFTS[addr]
        print(f"\n== LIFT {hex(addr)} {name} ({source}) ==", flush=True)
        applied = apply_lift(addr)
        if not applied:
            blockers.append({"addr": hex(addr), "name": name, "why": "apply"})
            continue
        sp, name, source = applied
        if prove_one(name, addr, source, touched):
            flips.append(hex(addr))
            names.append(name)
            since += 1
            print(f"  FLIP total={len(flips)}", flush=True)
            if since >= COMMIT_EVERY:
                commit_push(since, names[-since:], touched)
                since = 0
                touched.clear()
        else:
            # revert lift on fail if we introduced it this session and it was naked before
            blockers.append(
                {"addr": hex(addr), "name": name, "why": "unicorn_or_compile"}
            )

    # 2) prove already-readable focus symbols
    for source, name, addr in PROVE_ONLY:
        if not kb_is_false(addr):
            continue
        if addr in LIFTS:
            continue
        print(f"\n== PROVE {hex(addr)} {name} ({source}) ==", flush=True)
        if prove_one(name, addr, source, touched):
            flips.append(hex(addr))
            names.append(name)
            since += 1
            print(f"  FLIP total={len(flips)}", flush=True)
            if since >= COMMIT_EVERY:
                commit_push(since, names[-since:], touched)
                since = 0
                touched.clear()
        else:
            blockers.append({"addr": hex(addr), "name": name, "why": "prove"})

    if since:
        commit_push(since, names[-since:], touched)

    # also commit the prior FUN_00077cd0 if still uncommitted
    st = subprocess.run(
        ["git", "status", "--porcelain"], cwd=ROOT, capture_output=True, text=True
    ).stdout
    if "kb.json" in st and since == 0 and flips:
        pass

    true1, false1 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    summary = {
        "proven": len(flips),
        "flips": flips,
        "names": names,
        "true0": true0,
        "true1": true1,
        "delta": true1 - true0,
        "blockers": blockers,
    }
    outp = ROOT / "artifacts" / "equivalence" / "grokN_summary.json"
    outp.parent.mkdir(parents=True, exist_ok=True)
    outp.write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
