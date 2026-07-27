#!/usr/bin/env python3
"""grokM-solo: exclusive remaining saved_game_files.obj falses → Unicorn 100/0/0."""
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

from lift_inventory_batch4 import L, LIFTS, apply_lifts, find_naked_block  # noqa: E402

LIFTS.clear()


def apply_lifts_local(addrs=None):
    """Like apply_lifts but skip global cast_fnptrs (avoids cross-TU churn)."""
    selected = addrs if addrs else sorted(LIFTS.keys())
    by_source: dict[str, list[int]] = {}
    for a in selected:
        if a not in LIFTS:
            print(f"skip unknown {hex(a)}", file=sys.stderr)
            continue
        by_source.setdefault(LIFTS[a][0], []).append(a)

    results = []
    for src, alist in by_source.items():
        path = ROOT / "src" / "halo" / src
        if not path.exists():
            print(f"FAIL missing source {src}", file=sys.stderr)
            for a in alist:
                results.append({"addr": hex(a), "ok": False, "err": "missing_src"})
            continue
        text = path.read_text(encoding="utf-8", errors="replace")
        before = text
        for a in sorted(alist, reverse=True):
            _source, name, body, decl = LIFTS[a]
            span = find_naked_block(text, name, a)
            if span is None:
                print(f"FAIL locate {hex(a)} {name} in {src}", file=sys.stderr)
                results.append({"addr": hex(a), "ok": False, "err": "locate"})
                continue
            start, end = span
            chunk = text[start:end]
            if f"0x{a:x}" not in chunk.lower() and f"0x{a:X}" not in chunk:
                print(f"FAIL addr-guard {hex(a)} {name} in {src}", file=sys.stderr)
                results.append({"addr": hex(a), "ok": False, "err": "addr_guard"})
                continue
            text = text[:start] + body + "\n" + text[end:]
            print(f"lifted {hex(a)} {name}")
            results.append({"addr": hex(a), "name": name, "ok": True, "decl": decl})
        if text != before:
            if ("uint8_t" in text or "uint16_t" in text or "uint32_t" in text) and (
                "#include <stdint.h>" not in text
            ):
                text = "#include <stdint.h>\n" + text
            path.write_text(text, encoding="utf-8")

    decl_map = {a: LIFTS[a][3] for a in selected if a in LIFTS and LIFTS[a][3]}
    if decl_map:
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        n = 0
        for obj in kb.get("objects", []):
            for fn in obj.get("functions") or []:
                if not isinstance(fn, dict) or not fn.get("addr"):
                    continue
                ai = int(fn["addr"], 16)
                if ai in decl_map:
                    fn["decl"] = decl_map[ai]
                    if LIFTS[ai][1] and not fn.get("name"):
                        fn["name"] = LIFTS[ai][1]
                    n += 1
        KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        print(f"updated {n} kb decls")
    return results

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
SRC = "saved games/saved_game_files.c"

# --- lifts (skip already-true: FUN_001c1cc0, saved_game_perform_file_system_checks) ---

L(
    0x1C1FA0,
    SRC,
    "playlist_profile_get",
    """
/* playlist_profile_get (0x1c1fa0) — readable C lift. */
char playlist_profile_get(const char *path, void *out_variant)
{
  file_ref_t ref;
  unsigned char buf[0x200];
  unsigned char sig[0x14];
  char ok;

  ok = 0;
  if (!path || !out_variant) {
    display_assert((const char *)0x2ba584, (const char *)0x2ba59c, 0xf3, 1);
    system_exit(-1);
  }
  if (!file_reference_create_from_path(&ref, path, 0)) {
    error(2, (const char *)0x2ba510);
    return 0;
  }
  if (!file_open(&ref, 1)) {
    error(2, (const char *)0x2ba510);
    return 0;
  }
  if (!file_read(&ref, 0x200, buf)) {
    error(2, (const char *)0x2ba538);
    file_close(&ref);
    return 0;
  }
  saved_game_file_generate_checksum(buf, 0x68, sig);
  if (csmemcmp(sig, buf + 0x68, 0x14) != 0) {
    error(2, (const char *)0x2ba558);
    file_close(&ref);
    return 0;
  }
  csmemcpy(out_variant, buf, 0x68);
  ok = 1;
  file_close(&ref);
  return ok;
}
""",
    "char playlist_profile_get(const char *path, void *out_variant);",
)

L(
    0x1C29C0,
    SRC,
    "saved_game_file_get_useable_untitled_profile_name",
    """
/* saved_game_file_get_useable_untitled_profile_name (0x1c29c0) — readable C lift. */
void saved_game_file_get_useable_untitled_profile_name(wchar_t *out_name)
{
  int tag;
  char prefix[8];
  char path[0x100];
  int n;
  wchar_t *fmt;

  if (!out_name) {
    display_assert((const char *)0x2ba974, (const char *)0x2ba8e8, 0x2c1, 1);
    system_exit(-1);
  }
  out_name[0] = 0;
  tag = tag_loaded(0x75737472, (const char *)0x28a528);
  if (tag == -1) {
    error(2, (const char *)0x2ba918, (const char *)0x28a528);
    return;
  }
  csmemset(path, 0, 0x100);
  csmemset(prefix, 0, 8);
  wide_to_ascii((const wchar_t *)*(void **)0x32eb94, prefix, 8);
  for (n = 0; n < 0x3e7; n++) {
    fmt = (wchar_t *)FUN_0019d420(tag, 2);
    unicode_sprintf(out_name, 0x7f, fmt, n + 1);
    out_name[0x7f] = 0;
    if (FUN_001d2f22(prefix, out_name, 3, 0, path, 0x100) != 0)
      return;
  }
  error(2, (const char *)0x2ba940, 0x3e7);
  out_name[0] = 0;
}
""",
    "void saved_game_file_get_useable_untitled_profile_name(wchar_t *out_name);",
)

L(
    0x1C4850,
    SRC,
    "FUN_001c4850",
    """
/* FUN_001c4850 (0x1c4850) — readable C lift. */
char FUN_001c4850(file_ref_t *info, int packed)
{
  int slot;
  int idx;
  int kind;
  unsigned char record[0x208];
  char ok;

  kind = packed & 0xf;
  slot = (packed >> 8) & 0xff;
  idx = (packed >> 16) & 0xfff;

  if (slot != 0) {
    display_assert((const char *)0x2ba8c0, (const char *)0x2ba8e8, 0x241, 1);
    system_exit(-1);
  }
  if (!info) {
    display_assert((const char *)0x2ba8b0, (const char *)0x2ba8e8, 0x244, 1);
    system_exit(-1);
  }
  if (kind < 0 || kind >= 2) {
    display_assert((const char *)0x2ba878, (const char *)0x2ba8e8, 0x245, 1);
    system_exit(-1);
  }
  if (slot < 0 || slot >= 9) {
    display_assert((const char *)0x2ba838, (const char *)0x2ba8e8, 0x246, 1);
    system_exit(-1);
  }
  if (idx < 0 || idx >= 0x64) {
    display_assert((const char *)0x2ba7e8, (const char *)0x2ba8e8, 0x247, 1);
    system_exit(-1);
  }

  __asm__ volatile(
      "pushl %[buf]\\n\\t"
      "call FUN_001c3e40\\n\\t"
      "addl $4, %%esp\\n\\t"
      : "=a"(ok)
      : "a"(slot), "D"(idx), [buf] "r"(record)
      : "ecx", "edx", "memory", "cc");
  if (!ok)
    return 0;
  if (!file_reference_create_from_path(info, (const char *)record, 0))
    return 0;
  if (slot != 0)
    return 0;
  if (!file_open(info, 3))
    return 0;
  return 1;
}
""",
    "char FUN_001c4850(file_ref_t *info, int packed);",
)

L(
    0x1C46C0,
    SRC,
    "delete_enumerated_saved_game_file",
    """
/* delete_enumerated_saved_game_file (0x1c46c0) — readable C lift. */
char delete_enumerated_saved_game_file(int packed)
{
  int slot;
  int idx;
  int kind;
  unsigned char record[0x208];
  char prefix[8];
  char ok;
  char *ascii;

  ok = 0;
  if (*(unsigned char *)0x4eacc7 != 0) {
    error(2, (const char *)0x2bb590);
    ui_widget_clear_last_error_index();
    return 0;
  }

  kind = packed & 0xf;
  slot = (packed >> 8) & 0xff;
  idx = (int)((unsigned)packed >> 16) & 0xfff;

  if (slot != 0) {
    display_assert((const char *)0x2ba8c0, (const char *)0x2ba8e8, 0x1ef, 1);
    system_exit(-1);
  }
  if (kind < 0 || kind >= 2 || slot < 0 || slot >= 9 || idx < 0 || idx >= 0x64) {
    error(2, (const char *)0x2bb450);
    ui_widget_clear_last_error_index();
    return 0;
  }

  __asm__ volatile(
      "pushl %[buf]\\n\\t"
      "call FUN_001c3e40\\n\\t"
      "addl $4, %%esp\\n\\t"
      : "=a"(ok)
      : "a"(slot), "D"(idx), [buf] "r"(record)
      : "ecx", "edx", "memory", "cc");
  if (!ok) {
    error(2, (const char *)0x2bb4a8);
    ui_widget_clear_last_error_index();
    return 0;
  }

  ok = (char)(slot == 0);
  if (!ok) {
    error(2, (const char *)0x2bb4f4, slot);
    ui_widget_clear_last_error_index();
    return 0;
  }

  if ((packed & 0x40000000) == 0) {
    csmemset(prefix, 0, 8);
    ascii = wide_to_ascii((const wchar_t *)*(void **)(0x32eb94 + 4 * slot), prefix, 8);
    if (FUN_001d3185(ascii, (wchar_t *)(record + 0x100))) {
      error(2, (const char *)0x2bb55c);
      ok = 0;
    }
  }

  {
    char del_ok;
    __asm__ volatile(
        "call FUN_001c43f0\\n\\t"
        : "=a"(del_ok)
        : "a"(slot), "c"(idx)
        : "edx", "memory", "cc");
    if (!del_ok) {
      error(2, (const char *)0x2bb534);
      ok = 0;
    }
  }

  if (slot != 0)
    error(2, (const char *)0x2bb514);

  ui_widget_clear_last_error_index();
  return ok;
}
""",
    "char delete_enumerated_saved_game_file(int packed);",
)

L(
    0x1C38D0,
    SRC,
    "saved_game_file_find_profile_index_for_directory_path",
    """
/* saved_game_file_find_profile_index_for_directory_path (0x1c38d0) — readable C lift. */
int saved_game_file_find_profile_index_for_directory_path(const char *path, int16_t expect_type)
{
  int result;
  int path_len;
  unsigned int count;
  int i;
  unsigned char record[0x206];

  result = -1;
  if (!path) {
    display_assert((const char *)0x2ba9d4, (const char *)0x2ba8e8, 0x486, 1);
    system_exit(-1);
  }
  path_len = csstrlen(path);
  if (!take_mutex(*(int **)0x4eacbc, 0x36ee80)) {
    error(2, (const char *)0x2bae64);
    return -1;
  }
  if (!take_mutex(*(int **)0x4eacc0, 0x36ee80)) {
    error(2, (const char *)0x2bae8c);
    release_mutex(*(int **)0x4eacbc);
    return -1;
  }

  count = FUN_001c3610(0);
  if (FUN_001c3430(0)) {
    for (i = 0; i < (int)count; i++) {
      if (!FUN_001c35a0(record))
        break;
      if (*(int16_t *)(record + 0x200) != expect_type)
        continue;
      if (__strnicmp(path, (const char *)record, (size_t)path_len) == 0) {
        result = (int)FUN_001c3710(
            (unsigned int)i, 0, (unsigned int)expect_type,
            record[0x204], record[0x205]);
        break;
      }
    }
    FUN_001c3500(0);
  }

  release_mutex(*(int **)0x4eacc0);
  release_mutex(*(int **)0x4eacbc);
  return result;
}
""",
    "int saved_game_file_find_profile_index_for_directory_path(const char *path, int16_t expect_type);",
)

L(
    0x1C4030,
    SRC,
    "FUN_001c4030",
    """
/* FUN_001c4030 (0x1c4030) — readable C lift. */
char FUN_001c4030(int16_t slot_index, uint16_t record_index, void *buffer)
{
  char ok;
  unsigned path;
  unsigned eof;
  unsigned offset;

  ok = 0;
  if (slot_index != 0) {
    display_assert((const char *)0x2bacc8, (const char *)0x2ba8e8, 0x7e2, 1);
    system_exit(-1);
  }
  if (*(unsigned char *)0x4eacc8 != 0) {
    display_assert((const char *)0x2baac8, (const char *)0x2ba8e8, 0x7e4, 1);
    system_exit(-1);
  }
  if ((uint16_t)slot_index >= 9 || !buffer) {
    display_assert((const char *)0x2bb244, (const char *)0x2ba8e8, 0x7e5, 1);
    system_exit(-1);
  }
  if (!take_mutex(*(int **)0x4eacc0, 0x36ee80)) {
    error(2, (const char *)0x2bae8c);
    return 0;
  }

  path = *(unsigned *)(0x32eb98 + 4 * (unsigned)(uint16_t)slot_index);
  if (!file_reference_create_from_path((file_ref_t *)0x4eabb0, (char *)path, 0) ||
      !file_open((file_ref_t *)0x4eabb0, 2)) {
    error(2, (const char *)0x2bac54, (unsigned)(uint16_t)slot_index);
    release_mutex(*(int **)0x4eacc0);
    return 0;
  }

  eof = (unsigned)file_get_eof((file_ref_t *)0x4eabb0);
  offset = (unsigned)record_index * 0x206u;
  if ((eof % 0x206u) != 0)
    error(2, (const char *)0x2bac8c, (unsigned)(uint16_t)slot_index);

  if (offset + 0x206u > eof) {
    error(2, (const char *)0x2bb1cc, (unsigned)record_index,
          (unsigned)(uint16_t)slot_index);
  } else if (!file_set_position((file_ref_t *)0x4eabb0, (int)offset) ||
             !file_write((file_ref_t *)0x4eabb0, 0x206, buffer)) {
    ok = 0;
    error(2, (const char *)0x2bb284, (unsigned)record_index,
          (unsigned)(uint16_t)slot_index);
  } else {
    ok = 1;
  }

  if (!file_close((file_ref_t *)0x4eabb0)) {
    error(2, (const char *)0x2baafc, (unsigned)(uint16_t)slot_index);
    ok = 0;
  }
  release_mutex(*(int **)0x4eacc0);
  return ok;
}
""",
    "char FUN_001c4030(int16_t slot_index /* @<eax> */, uint16_t record_index, void *buffer);",
)

L(
    0x1C2550,
    SRC,
    "playlist_profile_write",
    """
/* playlist_profile_write (0x1c2550) — readable C lift. */
char playlist_profile_write(void *args)
{
  int profile_index;
  void *variant;
  file_ref_t ref;
  unsigned char buf[0x200];
  char failed_io;
  char ok_close;

  if (!args) {
    display_assert((const char *)0x266c9c, (const char *)0x2ba59c, 0x202, 1);
    system_exit(-1);
  }
  error(2, (const char *)0x2ba7ac);
  if (!take_mutex(*(int **)0x4eacbc, 0x36ee80)) {
    error(2, (const char *)0x2ba030);
    error(2, (const char *)0x2ba764);
    return 0;
  }

  profile_index = *(int *)args;
  variant = (char *)args + 4;
  failed_io = 0;
  if (!FUN_001c4850(&ref, profile_index)) {
    error(2, (const char *)0x2ba510);
    release_mutex(*(int **)0x4eacbc);
    error(2, (const char *)0x2ba764);
    return 0;
  }

  csmemcpy(buf, variant, 0x68);
  saved_game_file_generate_checksum(buf, 0x68, buf + 0x68);
  if (!file_set_position(&ref, 0) || !file_write(&ref, 0x200, buf)) {
    error(2, (const char *)0x2ba780);
    failed_io = 1;
  }
  ok_close = saved_game_file_close(&ref, profile_index);
  if (ok_close) {
    if (!((char (*)(int, void *))(void *)FUN_001c4990)(profile_index, variant))
      error(2, (const char *)0x2ba14c);
  }
  if (failed_io)
    delete_enumerated_saved_game_file(profile_index);
  release_mutex(*(int **)0x4eacbc);
  error(2, (const char *)0x2ba764);
  return 0;
}
""",
    "char playlist_profile_write(void *args);",
)

L(
    0x1C1E20,
    SRC,
    "FUN_001c1e20",
    """
/* FUN_001c1e20 (0x1c1e20) — readable C lift. */
int FUN_001c1e20(int a0, wchar_t *name)
{
  int handle;
  file_ref_t ref;
  game_variant_t tmp;
  unsigned char variant[0x200];
  game_variant_t *def;
  char ok;

  handle = ((int (*)(int, int, int))(void *)FUN_001c5560)(1, a0, (int)name);
  if (handle == -1)
    return -1;
  if (!FUN_001c4850(&ref, handle)) {
    error(2, (const char *)0x2ba470);
    delete_enumerated_saved_game_file(handle);
    return -1;
  }

  csmemset(variant, 0, 0x200);
  def = game_engine_slayer_default(&tmp);
  csmemcpy(variant, def, 0x68);
  variant[0x64] = (unsigned char)(variant[0x64] & 0xfe);
  game_engine_variant_cleanup((game_variant_t *)variant);
  ustrncpy((wchar_t *)variant, name, 0xb);
  ((wchar_t *)variant)[0xb] = 0;
  saved_game_file_generate_checksum(variant, 0x68, variant + 0x68);

  ok = file_set_position(&ref, 0);
  if (ok)
    ok = file_write(&ref, 0x200, variant);
  if (!ok) {
    error(2, (const char *)0x2ba4a0);
    delete_enumerated_saved_game_file(handle);
    handle = -1;
  }
  saved_game_file_close(&ref, handle);
  return handle;
}
""",
    "int FUN_001c1e20(int a0, wchar_t *name);",
)

L(
    0x1C2120,
    SRC,
    "FUN_001c2120",
    """
/* FUN_001c2120 (0x1c2120) — readable C lift. */
void FUN_001c2120(void)
{
  int tag;
  int i;
  game_variant_t tmp;
  game_variant_t *def;
  char path[0xff];
  file_ref_t ref;
  unsigned char variant[0x200];
  wchar_t *disp;
  char wrote;

  tag = tag_loaded(0x75737472, (const char *)0x28a4bc);
  if (tag == -1) {
    error(2, (const char *)0x2ba5d0);
    return;
  }
  for (i = 0; i < 0x1a; i++) {
    def = ((game_variant_t * (*)(game_variant_t *))(void *)(*(void **)(0x32eb28 + 4 * i)))(&tmp);
    csmemcpy(&tmp, def, 0x68);
    snprintf(path, 0xff, (const char *)0x2ba67c, i);
    path[0xfe] = 0;
    directory_create_or_delete_contents(path);
    csstrcat(path, (const char *)0x2ba670, 0xff);
    path[0xfe] = 0;
    disp = (wchar_t *)FUN_0019d420(tag, i);
    csmemcpy(variant, &tmp, 0x68);
    ustrncpy((wchar_t *)variant, disp, 0xb);
    ((wchar_t *)variant)[0xb] = 0;
    *(uint16_t *)(variant + 0x64) =
        (uint16_t)(*(uint16_t *)(variant + 0x64) | (uint16_t)(i << 8));
    saved_game_file_generate_checksum(variant, 0x68, variant + 0x68);

    wrote = 0;
    if (file_reference_create_from_path(&ref, path, 0) &&
        FUN_0019a490(&ref) && file_open(&ref, 2) && file_set_position(&ref, 0)) {
      wrote = file_write(&ref, 0x200, variant);
      file_close(&ref);
      if (wrote == 1) {
        *(uint16_t *)0x4eaaa8 = (uint16_t)(*(uint16_t *)0x4eaaa8 + 1);
        continue;
      }
    }
    error(2, (const char *)0x2ba634, path);
  }
  saved_game_files_notify_memory_units_changed();
}
""",
    "void FUN_001c2120(void);",
)


def run_uni(name: str, addr: int) -> dict:
    outj = ROOT / "artifacts" / "equivalence" / f"uni_{addr:08x}_s{SEEDS}.json"
    outj.parent.mkdir(parents=True, exist_ok=True)
    logp = ROOT / "artifacts" / "equivalence" / f"uni_{addr:08x}.log"
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
        "tail": text[-800:],
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
    subprocess.run(
        ["git", "commit", "-m", msg],
        cwd=ROOT,
        capture_output=True,
    )
    subprocess.run(
        ["git", "push", "pastudan", "HEAD:track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
    )
    print(f"pushed: {msg}", flush=True)


def main() -> int:
    # Drop already-proven from queue
    kb0 = json.loads(KB_PATH.read_text(encoding="utf-8"))
    proven = set()
    for o in kb0.get("objects", []):
        for fn in o.get("functions") or []:
            if (
                isinstance(fn, dict)
                and fn.get("addr")
                and fn.get("ported") is True
            ):
                proven.add(int(fn["addr"], 16))
    for a in list(LIFTS.keys()):
        if a in proven:
            print(f"skip already-true {hex(a)} {LIFTS[a][1]}", flush=True)
            del LIFTS[a]

    print("apply lifts...", flush=True)
    results = apply_lifts_local(sorted(LIFTS.keys()))
    ok_lift = [r for r in results if r.get("ok")]
    print(f"lifted {len(ok_lift)}/{len(results)}", flush=True)
    for r in results:
        if not r.get("ok"):
            print(" lift-fail", r, flush=True)

    print("regen decl.h...", flush=True)
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

    print("compile", SRC, flush=True)
    if not docker_compile(SRC):
        print("COMPILE FAIL", flush=True)
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
            # retry by hex addr
            res2 = run_uni(hex(addr), addr)
            print(
                f" retry {res2.get('passed')}/{res2.get('failed')}/{res2.get('errors')}",
                flush=True,
            )
            if clear_pass(res2, SEEDS):
                res = res2
            else:
                print(" FAIL", (res.get("tail") or "")[-400:], flush=True)
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
                "phase": "grokM-saved",
            }
        )
        lands.append(name)
        print(" FLIP", name, flush=True)

    t, f = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    print(f"\nLANDS ({len(lands)}): {lands}", flush=True)
    print(f"FAILS ({len(fails)}): {fails}", flush=True)
    print(f"kb true={t} false={f}", flush=True)
    if lands:
        commit_push(lands)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
