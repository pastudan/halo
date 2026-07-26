#!/usr/bin/env python3
"""Lifter J: naked→C + Unicorn in sound/ tag_files/ saved_games/ devices/ models/.

Avoids hs/. Pull-before-push; union remote ported:true; raw-cast≤359.
"""
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
sys.path.insert(0, str(ROOT / "tools" / "equivalence"))

from capstone import CS_ARCH_X86, CS_MODE_32, Cs  # noqa: E402
from xbe import Xbe  # noqa: E402
from xbe_to_coff import load_kb, xbe_bytes  # noqa: E402
from lift_inventory_batch4 import find_naked_block  # noqa: E402
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
    func_name,
    git_push,
    inventory_readable,
    is_naked_near_def,
    resolve_src,
    run_unicorn,
)
import lift_assert_wrappers as law  # noqa: E402
import lift_thin_wrappers as ltw  # noqa: E402

PREF = (
    "sound/",
    "tag_files/",
    "saved_games/",
    "devices/",
    "models/",
)
LEDGER_TAG = "lifter_j"
COMMIT_EVERY = 10
MAX_SIZE = 256

# addr -> (src, name, body)
HAND: dict[int, tuple[str, str, str, str | None]] = {}


def H(addr: int, src: str, name: str, body: str, decl: str | None = None) -> None:
    HAND[addr] = (src, name, body.strip() + "\n", decl)


# --- devices ---
H(
    0x966B0,
    "devices/devices.c",
    "device_group_get_value",
    """
/* device_group_get_value (0x966b0) — readable C lift. */
float device_group_get_value(int a0)
{
  void *d = datum_get(*(void **)0x5aa8c8, a0);
  return *(float *)((char *)d + 4);
}
""",
)
H(
    0x96470,
    "devices/devices.c",
    "device_get_position",
    """
/* device_get_position (0x96470) — readable C lift. */
float device_get_position(int a0)
{
  if (a0 == -1)
    return 0.0f;
  void *obj = object_get_and_verify_type(a0, 0x380);
  return *(float *)((char *)obj + 0x1b8);
}
""",
)
H(
    0x964A0,
    "devices/devices.c",
    "device_get_power",
    """
/* device_get_power (0x964a0) — readable C lift. */
float device_get_power(int a0)
{
  if (a0 == -1)
    return 0.0f;
  void *obj = object_get_and_verify_type(a0, 0x380);
  return *(float *)((char *)obj + 0x1ac);
}
""",
)
H(
    0x96670,
    "devices/devices.c",
    "device_group_change_only_once_more_set",
    """
/* device_group_change_only_once_more_set (0x96670) — readable C lift. */
void device_group_change_only_once_more_set(int a0, int a1)
{
  if (a0 == -1)
    return;
  unsigned char *d = (unsigned char *)datum_get(*(void **)0x5aa8c8, a0);
  if (a1) {
    d[2] |= 1;
    d[2] &= (unsigned char)0xfd;
  } else {
    d[2] &= (unsigned char)0xfe;
    d[2] &= (unsigned char)0xfd;
  }
}
""",
)
H(
    0x960C0,
    "devices/devices.c",
    "device_new",
    """
/* device_new (0x960c0) — readable C lift. */
char device_new(int object_handle)
{
  char *obj = (char *)object_get_and_verify_type(object_handle, 0x380);
  tag_get(0x64657669, *(int *)obj);
  *(unsigned short *)(obj + 0x1b4) = 0xffff;
  *(unsigned short *)(obj + 0x1a8) = 0xffff;
  *(unsigned int *)(obj + 4) |= 0x40000u;
  return 1;
}
""",
)

# --- models ---
H(
    0x120930,
    "models/model_animations.c",
    "quaternion_decompress_6byte_renormalized",
    """
/* quaternion_decompress_6byte_renormalized (0x120930) — readable C lift. */
void quaternion_decompress_6byte_renormalized(void *compressed, float *out)
{
  quaternion_decompress_6byte(compressed, out);
  sphere_intersects_rectangle3d(out);
}
""",
)
H(
    0x120470,
    "models/model_animations.c",
    "FUN_00120470",
    """
/* FUN_00120470 (0x120470) — readable C lift. */
void FUN_00120470(void *ctrl, int datum_handle)
{
  char *c = (char *)ctrl;
  FUN_0011fd50();
  datum_delete(*(void **)(c + 0x18), datum_handle);
  FUN_0011ff70(c);
}
""",
)
H(
    0x123E20,
    "models/model_animations.c",
    "animation_get_root_matrix",
    """
/* animation_get_root_matrix (0x123e20) — readable C lift. */
void *animation_get_root_matrix(void *anim_graph, int index)
{
  void *el = tag_block_get_element((char *)anim_graph + 0xb8, index, 0x9c);
  return (char *)el + 0x68;
}
""",
)

# --- tag_files ---
H(
    0x1996D0,
    "tag_files/files.c",
    "file_reference_copy",
    """
/* file_reference_copy (0x1996d0) — readable C lift. */
void *file_reference_copy(void *dst, void *src)
{
  file_reference_verify(src);
  csmemcpy(dst, src, 0x108);
  return dst;
}
""",
)
H(
    0x19ACF0,
    "tag_files/files.c",
    "file_write_to_position",
    """
/* file_write_to_position (0x19acf0) — readable C lift. */
char file_write_to_position(void *info, int offset, void *buffer, int size)
{
  if (!file_set_position(info, offset))
    return 0;
  if (!(char)file_write(info, buffer, size))
    return 0;
  return 1;
}
""",
)

# --- saved_games ---
H(
    0x1C0D50,
    "saved_games/game_state_xbox.c",
    "FUN_001c0d50",
    """
/* FUN_001c0d50 (0x1c0d50) — readable C lift. */
void FUN_001c0d50(int a0, int a1, int a2, int a3)
{
  FUN_001c53f0(a0, 0, a1, a2, a3);
}
""",
)
H(
    0x1C19A0,
    "saved_games/game_state_xbox.c",
    "FUN_001c19a0",
    """
/* FUN_001c19a0 (0x1c19a0) — readable C lift. */
int FUN_001c19a0(void)
{
  return (int)(short)random_range(random_math_get_local_seed_address(), 0, 3);
}
""",
)
H(
    0x1C19C0,
    "saved_games/game_state_xbox.c",
    "FUN_001c19c0",
    """
/* FUN_001c19c0 (0x1c19c0) — readable C lift. */
int FUN_001c19c0(void)
{
  return (int)(short)random_range(random_math_get_local_seed_address(), 0, 0x11);
}
""",
)

# --- sound ---
H(
    0x1C88A0,
    "sound/sound_manager.c",
    "sound_is_active",
    """
/* sound_is_active (0x1c88a0) — readable C lift. */
void sound_is_active(int sound_index)
{
  FUN_00118be0((void *)0x32ecf4, (void *)(intptr_t)sound_index, 1);
}
""",
)
H(
    0x1C9250,
    "sound/sound_dsound_xbox.c",
    "dsound_occlusion_from_occlusion",
    """
/* dsound_occlusion_from_occlusion (0x1c9250) — readable C lift. */
int dsound_occlusion_from_occlusion(float occlusion)
{
  return sound_dsound_gain_to_volume(1.0f - occlusion, 0);
}
""",
)
H(
    0x1C9270,
    "sound/sound_dsound_xbox.c",
    "dsound_obstruction_from_obstruction",
    """
/* dsound_obstruction_from_obstruction (0x1c9270) — readable C lift. */
int dsound_obstruction_from_obstruction(float obstruction)
{
  return sound_dsound_gain_to_volume(1.0f - obstruction, 0);
}
""",
)
H(
    0x1CB960,
    "sound/sound_manager.c",
    "sound_try_and_get",
    """
/* sound_try_and_get (0x1cb960) — readable C lift. */
char sound_try_and_get(int sound_index)
{
  return datum_absolute_index_to_index(*(void **)0x4fdba4, sound_index) != 0;
}
""",
)
H(
    0x1CF820,
    "sound/sound_manager.c",
    "FUN_001cf820",
    """
/* FUN_001cf820 (0x1cf820) — readable C lift. */
void FUN_001cf820(void **out)
{
  *out = (void *)0x32fce4;
}
""",
)
H(
    0x1C7770,
    "sound/game_sound.c",
    "unattached_looping_sound_stop",
    """
/* unattached_looping_sound_stop (0x1c7770) — readable C lift. */
void unattached_looping_sound_stop(int sound_index)
{
  unsigned int *d = (unsigned int *)datum_get(*(void **)0x5054e4, sound_index);
  d[1] |= 2u;
}
""",
)
H(
    0x1AC150,
    "sound/sound_manager.c",
    "FUN_001ac150",
    """
/* FUN_001ac150 (0x1ac150) — readable C lift. */
char FUN_001ac150(int unit_handle)
{
  if (unit_handle == -1)
    return 0;
  unsigned char *obj = (unsigned char *)object_get_and_verify_type(unit_handle, 3);
  return obj[0x253] == 0x1c;
}
""",
)
H(
    0x1BE140,
    "sound/sound_manager.c",
    "FUN_001be140",
    """
/* FUN_001be140 (0x1be140) — readable C lift. */
void FUN_001be140(void *cache_entry)
{
  int handle = *(int *)((char *)cache_entry + 0x2c);
  unsigned char *d = (unsigned char *)datum_get(*(void **)0x4e9368, handle);
  if (d[5])
    d[5] = (unsigned char)(d[5] - 1);
  else
    *(unsigned short *)0x5054ea = (unsigned short)(*(unsigned short *)0x5054ea + 1);
}
""",
)
H(
    0x1BE100,
    "sound/sound_manager.c",
    "FUN_001be100",
    """
/* FUN_001be100 (0x1be100) — readable C lift. */
void FUN_001be100(void *cache_entry)
{
  int handle = *(int *)((char *)cache_entry + 0x2c);
  unsigned char *d = (unsigned char *)datum_get(*(void **)0x4e9368, handle);
  if (d[5] < 0xff)
    d[5] = (unsigned char)(d[5] + 1);
  else
    *(unsigned short *)0x5054ea = (unsigned short)(*(unsigned short *)0x5054ea + 1);
}
""",
)
H(
    0x1AC070,
    "sound/sound_manager.c",
    "FUN_001ac070",
    """
/* FUN_001ac070 (0x1ac070) — readable C lift. */
void FUN_001ac070(int unit_handle, char flag)
{
  if (unit_handle == -1)
    return;
  unsigned char *obj = (unsigned char *)object_get_and_verify_type(unit_handle, 3);
  obj[0x258] = (unsigned char)flag;
  object_set_region_count(unit_handle, 6);
}
""",
)
H(
    0x1AC030,
    "sound/sound_manager.c",
    "FUN_001ac030",
    """
/* FUN_001ac030 (0x1ac030) — readable C lift. */
void FUN_001ac030(int unit_handle, char flag)
{
  if (unit_handle == -1)
    return;
  unsigned char *obj = (unsigned char *)object_get_and_verify_type(unit_handle, 3);
  unsigned int *flags = (unsigned int *)(obj + 0x1b4);
  if (!flag)
    *flags |= 0x10000u;
  else
    *flags &= ~0x10000u;
}
""",
)
H(
    0x1AC0A0,
    "sound/sound_manager.c",
    "FUN_001ac0a0",
    """
/* FUN_001ac0a0 (0x1ac0a0) — readable C lift. */
void FUN_001ac0a0(int unit_handle, char flag)
{
  if (unit_handle == -1)
    return;
  unsigned char *obj = (unsigned char *)object_get_and_verify_type(unit_handle, 3);
  unsigned int *flags = (unsigned int *)(obj + 0x1b4);
  if (flag)
    *flags |= 0x4000u;
  else
    *flags &= ~0x4000u;
}
""",
)
H(
    0x1AC3B0,
    "sound/sound_manager.c",
    "FUN_001ac3b0",
    """
/* FUN_001ac3b0 (0x1ac3b0) — readable C lift. */
char FUN_001ac3b0(int unit_handle, int weapon_handle)
{
  unsigned char *obj = (unsigned char *)object_get_and_verify_type(unit_handle, 3);
  int *slots = (int *)(obj + 0x2a8);
  for (int i = 0; i < 4; i++) {
    if (slots[i] == weapon_handle)
      return 1;
  }
  return 0;
}
""",
)
H(
    0x1BE170,
    "sound/sound_manager.c",
    "FUN_001be170",
    """
/* FUN_001be170 (0x1be170) — readable C lift. */
char FUN_001be170(int cache_handle)
{
  unsigned char *d = (unsigned char *)datum_get(*(void **)0x4e9368, cache_handle);
  if (!d[2])
    return 1;
  if (d[4])
    return 1;
  if (d[5])
    return 1;
  return 0;
}
""",
)
H(
    0x1BE270,
    "sound/sound_manager.c",
    "FUN_001be270",
    """
/* FUN_001be270 (0x1be270) — readable C lift. */
void *FUN_001be270(int cache_handle)
{
  unsigned char *d = (unsigned char *)datum_get(*(void **)0x4e9368, cache_handle);
  void *tag = *(void **)(d + 8);
  const char *name = tag_get_name(*(int *)((char *)tag + 0x3c));
  crt_sprintf((char *)0x4e9268, (const char *)0x2b9424, name);
  return (void *)0x4e9268;
}
""",
)
H(
    0x1CB9D0,
    "sound/sound_manager.c",
    "FUN_001cb9d0",
    """
/* FUN_001cb9d0 (0x1cb9d0) — readable C lift. */
void FUN_001cb9d0(void)
{
  int now = (int)system_milliseconds();
  float dt = (float)(now - *(int *)0x4eaf4c) * *(float *)0x25bc08;
  *(int *)0x4eaf4c = now;
  *(float *)0x4eaf50 = dt;
}
""",
)
H(
    0x120EE0,
    "models/model_animations.c",
    "animation_frame_get_xy_translation",
    """
/* animation_frame_get_xy_translation (0x120ee0) — readable C lift. */
void animation_frame_get_xy_translation(void *animation, short frame_index, float *out_xy)
{
  if (*(short *)((char *)animation + 0x26) != 1) {
    out_xy[0] = 0.0f;
    out_xy[1] = 0.0f;
    return;
  }
  float *frame = (float *)FUN_00120590(animation, frame_index, 8);
  out_xy[0] = frame[0];
  out_xy[1] = frame[1];
}
""",
)
H(
    0x1C9230,
    "sound/sound_dsound_xbox.c",
    "dsound_angle_from_angle",
    """
/* dsound_angle_from_angle (0x1c9230) — readable C lift. */
int dsound_angle_from_angle(float angle)
{
  return (int)(angle * *(float *)0x2b073c);
}
""",
)
H(
    0x1CBC20,
    "sound/sound_manager.c",
    "FUN_001cbc20",
    """
/* FUN_001cbc20 (0x1cbc20) — readable C lift. */
int FUN_001cbc20(float t)
{
  return (int)(t * *(float *)0x2c1288);
}
""",
)
H(
    0x1C1280,
    "saved_games/game_state_xbox.c",
    "FUN_001c1280",
    """
/* FUN_001c1280 (0x1c1280) — readable C lift (tail jump). */
void FUN_001c1280(void)
{
  FUN_001c4da0();
}
""",
)
H(
    0x1C8EE0,
    "sound/sound_manager.c",
    "FUN_001c8ee0",
    """
/* FUN_001c8ee0 (0x1c8ee0) — readable C lift. */
void FUN_001c8ee0(void *pitch_range)
{
  unsigned char *p = (unsigned char *)pitch_range;
  unsigned short dx = *(unsigned short *)(p + 0x2c);
  unsigned int mask = (1u << (dx & 0xff)) - 1u;
  unsigned int bits = ~*(unsigned int *)(p + 0x34);
  if (bits & mask)
    return;
  *(unsigned int *)(p + 0x34) = 0;
  if ((short)dx > 1)
    *(unsigned int *)(p + 0x34) = 1u << p[0x38];
}
""",
)
H(
    0x1CB990,
    "sound/sound_manager.c",
    "sound_scripted_dialog_is_playing",
    """
/* sound_scripted_dialog_is_playing (0x1cb990) — readable C lift. */
char sound_scripted_dialog_is_playing(void)
{
  return game_time_get() < *(int *)0x4eaf44;
}
""",
)
H(
    0x20F069,
    "sound/sound_dsound_xbox.c",
    "dsound_stream_is_active",
    """
/* dsound_stream_is_active (0x20f069) — readable C lift. */
int dsound_stream_is_active(void *stream)
{
  unsigned int flags = *(unsigned int *)(*(unsigned char **)((unsigned char *)stream + 0x24) + 8);
  return (flags & 0x10000002u) != 0;
}
""",
)


def in_pref(src: str) -> bool:
    s = src.replace("\\", "/")
    return any(p in s for p in PREF)


def safe_flip(addr: int) -> bool:
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    if not flip_kb(kb, addr):
        return False
    KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
    return True


def merge_remote_kb() -> None:
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
        if remote_kb.returncode != 0 or not remote_kb.stdout:
            return
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


def commit_chunk(n: int, paths: set[Path], do_push: bool = True) -> str | None:
    merge_remote_kb()
    for p in paths:
        subprocess.run(["git", "add", str(p)], cwd=ROOT, check=False)
    subprocess.run(
        ["git", "add", "kb.json", "tools/equivalence/leaf_cache.json", "scripts/lifter_j.py"],
        cwd=ROOT,
        check=False,
    )
    subprocess.run(["git", "add", "-u", "src/halo"], cwd=ROOT, check=False)
    msg = f"lift(track-a): Lifter J naked→C + Unicorn-prove {n} (ported:true)."
    r = subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print("commit failed:", r.stdout, r.stderr, file=sys.stderr)
        return None
    sha = subprocess.run(
        ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
    ).stdout.strip()
    if do_push:
        subprocess.run(
            ["git", "pull", "--rebase", "pastudan", "track-a-collision-bsp"],
            cwd=ROOT,
            capture_output=True,
            check=False,
        )
        merge_remote_kb()
        st = subprocess.run(
            ["git", "status", "--porcelain", "kb.json"],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
        if st.stdout.strip():
            subprocess.run(["git", "add", "kb.json"], cwd=ROOT, check=False)
            subprocess.run(
                [
                    "git",
                    "commit",
                    "-m",
                    "fix(track-a): union concurrent ported:true into Lifter J kb.",
                ],
                cwd=ROOT,
                capture_output=True,
                check=False,
            )
            sha = subprocess.run(
                ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
            ).stdout.strip()
        git_push()
        print(f"COMMIT+PUSH {sha}", flush=True)
    else:
        print(f"COMMIT {sha}", flush=True)
    return sha


def prove_addr(name: str, addr: int, seeds: int, timeout: float) -> dict:
    if not ensure_oracle(addr):
        return {"ok": False, "err": "oracle", "passed": 0, "failed": 0, "errors": 0}
    res = run_unicorn(name, addr, seeds, timeout=timeout)
    if not clear_pass(res, seeds):
        res2 = run_unicorn(hex(addr), addr, seeds, timeout=timeout)
        if clear_pass(res2, seeds) or (
            (res2.get("passed") or 0) > (res.get("passed") or 0)
        ):
            res = res2
    return {
        "ok": clear_pass(res, seeds),
        "passed": res.get("passed"),
        "failed": res.get("failed"),
        "errors": res.get("errors"),
        "rc": res.get("rc"),
        "tail": (res.get("tail") or "")[-200:],
    }


def load_names():
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    name_by, decl_by, src_by, ported = {}, {}, {}, {}
    for o in kb.get("objects", []):
        src = o.get("source") or ""
        for fn in o.get("functions") or []:
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            ai = int(fn["addr"], 16)
            nm = func_name(fn) or f"FUN_{ai:08x}"
            name_by[ai] = nm
            decl_by[ai] = fn.get("decl") or ""
            src_by[ai] = src
            ported[ai] = fn.get("ported")
    return kb, name_by, decl_by, src_by, ported


def try_pattern_emit(ops, decl, name, name_by) -> str | None:
    body = law.try_emit(ops, decl, name, name_by)
    if body:
        return body
    lines = [f"{m} {o}".strip() for m, o in ops]
    body = ltw.try_emit(lines, decl, name, name_by)
    if body:
        return body
    # Extra J patterns
    if not ops or ops[-1][0] not in ("ret", "retn"):
        return None
    mid = ops[:-1]
    sig = law.cdecl_sig(decl, name)
    ps = law.params(sig)
    ret = "" if law.is_void(sig) else "return "

    # datum_get(global, arg0) ; fld [eax+off]
    if (
        len(mid) >= 8
        and mid[0] == ("push", "ebp")
        and mid[1] == ("mov", "ebp, esp")
        and mid[2][0] in ("mov", "movsx")
        and "ebp + 8" in mid[2][1]
        and mid[3][0] == "mov"
        and "dword ptr [0x" in mid[3][1]
        and mid[4] == ("push", "eax")
        and mid[5] == ("push", "ecx")
        and mid[6][0] == "call"
        and "0x119320" in mid[6][1]
    ):
        g = re.search(r"\[0x([0-9a-fA-F]+)\]", mid[3][1])
        rest = mid[7:]
        while rest and rest[0][0] == "add" and "esp" in rest[0][1]:
            rest = rest[1:]
        if g and rest and rest[0][0] == "fld":
            om = re.search(r"\[eax(?: \+ (0x[0-9a-f]+|\d+))?\]", rest[0][1])
            o = int(om.group(1), 0) if om and om.group(1) else 0
            sig1, ps1 = law.ensure_params(sig, ps, 1, ["int"])
            if "void" in sig1.split("(")[0]:
                sig1 = sig1.replace("void ", "float ", 1)
            return (
                f"{sig1}\n{{\n"
                f"  void *d = datum_get(*(void **)0x{g.group(1)}, {ps1[0]});\n"
                f"  return *(float *)((char *)d + 0x{o:x});\n"
                f"}}\n"
            )

    # object_get; fld [eax+off] with -1 → 0.0f
    if (
        len(mid) >= 10
        and mid[0] == ("push", "ebp")
        and mid[1] == ("mov", "ebp, esp")
        and mid[2] == ("mov", "eax, dword ptr [ebp + 8]")
        and mid[3] == ("cmp", "eax, -1")
        and mid[4][0] == "je"
        and mid[5][0] == "push"
        and mid[6] == ("push", "eax")
        and mid[7][0] == "call"
        and "0x13d680" in mid[7][1]
        and mid[8][0] == "fld"
    ):
        typ = mid[5][1]
        om = re.search(r"\[eax(?: \+ (0x[0-9a-f]+|\d+))?\]", mid[8][1])
        o = int(om.group(1), 0) if om and om.group(1) else 0
        sig1, ps1 = law.ensure_params(sig, ps, 1, ["int"])
        if "void" in sig1.split("(")[0] or "int " in sig1.split("(")[0]:
            sig1 = re.sub(r"^(?:void|int)\s+", "float ", sig1, count=1)
        return (
            f"{sig1}\n{{\n"
            f"  if ({ps1[0]} == -1)\n"
            f"    return 0.0f;\n"
            f"  void *obj = object_get_and_verify_type({ps1[0]}, {typ});\n"
            f"  return *(float *)((char *)obj + 0x{o:x});\n"
            f"}}\n"
        )

    # store imm pointer: mov [arg0], imm
    if (
        len(mid) == 4
        and mid[0] == ("push", "ebp")
        and mid[1] == ("mov", "ebp, esp")
        and mid[2] == ("mov", "eax, dword ptr [ebp + 8]")
        and mid[3][0] == "mov"
        and mid[3][1].startswith("dword ptr [eax],")
    ):
        imm = mid[3][1].split(",", 1)[1].strip()
        sig1, ps1 = law.ensure_params(sig, ps, 1, ["void **"])
        return f"{sig1}\n{{\n  *(uint32_t *){ps1[0]} = (uint32_t){imm};\n}}\n"

    # 1.0f - arg ; sound_dsound_gain_to_volume
    if (
        len(mid) >= 8
        and mid[0] == ("push", "ebp")
        and mid[1] == ("mov", "ebp, esp")
        and mid[2][0] == "fld"
        and "0x2533c8" in mid[2][1]
        and mid[3] == ("push", "0")
        and mid[4][0] == "fsub"
        and "ebp + 8" in mid[4][1]
        and mid[7][0] == "call"
        and "0x1c9130" in mid[7][1]
    ):
        sig1, ps1 = law.ensure_params(sig, ps, 1, ["float"])
        if "void" in sig1.split("(")[0]:
            sig1 = sig1.replace("void ", "int ", 1)
        return (
            f"{sig1}\n{{\n"
            f"  return sound_dsound_gain_to_volume(1.0f - {ps1[0]}, 0);\n"
            f"}}\n"
        )

    # datum_absolute_index_to_index != 0
    if (
        len(mid) >= 9
        and mid[0] == ("push", "ebp")
        and mid[1] == ("mov", "ebp, esp")
        and mid[2] == ("mov", "eax, dword ptr [ebp + 8]")
        and mid[3][0] == "mov"
        and "dword ptr [0x" in mid[3][1]
        and mid[6][0] == "call"
        and "0x119270" in mid[6][1]
        and any(x == ("neg", "eax") for x in mid)
    ):
        g = re.search(r"\[0x([0-9a-fA-F]+)\]", mid[3][1])
        sig1, ps1 = law.ensure_params(sig, ps, 1, ["int"])
        if g:
            return (
                f"{sig1}\n{{\n"
                f"  return datum_absolute_index_to_index(*(void **)0x{g.group(1)}, {ps1[0]}) != 0;\n"
                f"}}\n"
            )

    # random_range(local_seed(), 0, N)
    if (
        len(mid) >= 6
        and mid[0][0] == "push"
        and mid[1] == ("push", "0")
        and mid[2][0] == "call"
        and "0x10b120" in mid[2][1]
        and mid[3] == ("push", "eax")
        and mid[4][0] == "call"
        and "0x10b2d0" in mid[4][1]
    ):
        n = mid[0][1]
        if "void" in sig.split("(")[0]:
            sig = sig.replace("void ", "int ", 1)
        return (
            f"{sig}\n{{\n"
            f"  return (int)(short)random_range(random_math_get_local_seed_address(), 0, {n});\n"
            f"}}\n"
        )

    return None


def apply_body(path: Path, name: str, addr: int, c_src: str) -> tuple[str | None, str | None]:
    text = path.read_text(encoding="utf-8", errors="replace")
    span = find_naked_block(text, name, addr)
    if span is None:
        span = find_naked_block(text, f"FUN_{addr:08x}", addr)
    if span is None:
        return None, "locate"
    needs_stdint = any(
        t in c_src for t in ("uint8_t", "uint16_t", "uint32_t", "uintptr_t", "int8_t", "int16_t")
    )
    new_text = text[: span[0]] + c_src + "\n" + text[span[1] :]
    if needs_stdint and "#include <stdint.h>" not in new_text:
        new_text = "#include <stdint.h>\n" + new_text
    path.write_text(new_text, encoding="utf-8")
    for stale in (ROOT / "build").rglob(path.name + ".obj"):
        try:
            stale.unlink()
        except OSError:
            pass
    return text, None


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--commit-every", type=int, default=COMMIT_EVERY)
    ap.add_argument("--seeds", type=int, default=100)
    ap.add_argument("--timeout", type=float, default=45.0)
    ap.add_argument("--no-push", action="store_true")
    ap.add_argument("--max-size", type=int, default=MAX_SIZE)
    args = ap.parse_args()

    merge_remote_kb()
    kb, name_by, decl_by, src_by, ported = load_names()
    by_addr, starts = load_kb(KB_PATH)
    xbe = Xbe((ROOT / "halo-patched" / "cachebeta.xbe").read_bytes())
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    true0, false0 = count_ported(kb)

    jobs: list[dict] = []
    seen = set()

    # 1) Hand lifts
    for ai, (src, name, body, new_decl) in sorted(HAND.items()):
        if ported.get(ai) is not False:
            continue
        if not in_pref(src_by.get(ai, src)):
            continue
        jobs.append(
            {
                "addr": ai,
                "name": name_by.get(ai, name),
                "src": src_by.get(ai, src),
                "kind": "hand",
                "decl": new_decl,
                "body": f"/* {name} (0x{ai:x}) — readable C lift. */\n" + body
                if not body.lstrip().startswith("/*")
                else body,
            }
        )
        seen.add(ai)

    # 2) Pattern / assert / thin for remaining naked ≤ max-size
    for i, ai in enumerate(starts):
        if ai in seen or ported.get(ai) is not False:
            continue
        src = src_by.get(ai) or ""
        if not in_pref(src):
            continue
        end = starts[i + 1] if i + 1 < len(starts) else ai + args.max_size
        size = end - ai
        if size > args.max_size:
            continue
        try:
            raw = xbe_bytes(xbe, ai, min(end, ai + args.max_size))
        except Exception:
            continue
        ops: list[tuple[str, str]] = []
        for insn in md.disasm(raw, ai):
            ops.append((insn.mnemonic, insn.op_str))
            if insn.mnemonic in ("ret", "retn") and insn.address + insn.size >= end - 8:
                # keep scanning within symbol; only stop at last ret near end
                pass
        # Rebuild ops cutting at final ret in range
        ops = []
        for insn in md.disasm(raw, ai):
            ops.append((insn.mnemonic, insn.op_str))
        # trim trailing nops after last ret
        last_ret = max((i for i, o in enumerate(ops) if o[0] in ("ret", "retn")), default=-1)
        if last_ret < 0:
            continue
        ops = ops[: last_ret + 1]
        # Drop trailing nops already excluded; if multiple rets keep full
        name = name_by[ai]
        decl = decl_by.get(ai) or f"void {name}(void);"
        # Prefer first-ret cut for pattern matchers that expect linear
        cut = []
        for o in ops:
            cut.append(o)
            if o[0] in ("ret", "retn"):
                break
        body = try_pattern_emit(cut, decl, name, name_by)
        if not body and len(ops) != len(cut):
            body = try_pattern_emit(ops, decl, name, name_by)
        if not body:
            continue
        jobs.append(
            {
                "addr": ai,
                "name": name,
                "src": src,
                "kind": "pattern",
                "body": f"/* {name} (0x{ai:x}) — readable C lift. */\n{body}",
            }
        )
        seen.add(ai)

    # 3) Prove-only readable leftovers
    for r in inventory_readable(kb):
        if r["addr_int"] in seen:
            continue
        if not in_pref(r["source"]):
            continue
        jobs.append(
            {
                "addr": r["addr_int"],
                "name": r["name"],
                "src": r["source"],
                "kind": "prove",
                "body": None,
            }
        )
        seen.add(r["addr_int"])

    jobs.sort(key=lambda j: (0 if j["kind"] == "hand" else 1 if j["kind"] == "pattern" else 2, j["addr"]))
    if args.limit:
        jobs = jobs[: args.limit]

    print(
        f"lifter-j jobs={len(jobs)} kb true={true0} false={false0} "
        f"hand={sum(1 for j in jobs if j['kind']=='hand')} "
        f"pattern={sum(1 for j in jobs if j['kind']=='pattern')} "
        f"prove={sum(1 for j in jobs if j['kind']=='prove')}",
        flush=True,
    )

    flips: list[str] = []
    shas: list[str] = []
    touched: set[Path] = set()
    since = 0

    for job in jobs:
        ai = job["addr"]
        name = job["name"]
        kind = job["kind"]
        src = job["src"]
        print(f"\n== {hex(ai)} {name} [{kind}] ({src}) ==", flush=True)
        path = resolve_src(src)
        orig = None

        if kind in ("hand", "pattern"):
            if path is None:
                print("  no source", flush=True)
                continue
            if job.get("decl"):
                set_kb_decl(ai, job["decl"])
                for stale in (ROOT / "build" / "generated").glob("decl.h"):
                    try:
                        stale.unlink()
                    except OSError:
                        pass
            # skip if not naked anymore
            text0 = path.read_text(encoding="utf-8", errors="replace")
            if not is_naked_near_def(text0.splitlines(), name, hex(ai)):
                # try prove-only
                kind = "prove"
            else:
                orig, err = apply_body(path, name, ai, job["body"])
                if err:
                    print(f"  {err} FAIL", flush=True)
                    continue

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
            if orig is not None and path is not None:
                path.write_text(orig, encoding="utf-8")
                print("  REVERT", flush=True)
            continue

        rc = subprocess.run(
            [sys.executable, str(ROOT / "tools/audit/check_raw_casts.py")],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
        if rc.returncode != 0:
            if orig is not None and path is not None:
                path.write_text(orig, encoding="utf-8")
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
    Path("/tmp/lifter_j_summary.json").write_text(json.dumps(summary, indent=2))
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
