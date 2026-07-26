#!/usr/bin/env python3
"""Lifter INTERFACE: naked→C + Unicorn prove exclusively under interface/.

Owns src/halo/interface/**. Pull/rebase before push; union remote ported:true.
Avoids colliding with Lifter J/G on other domains.
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

PREF = ("interface/",)
LEDGER_TAG = "lifter_interface"
COMMIT_EVERY = 8
MAX_SIZE = 320
CLAIM = ROOT / "artifacts" / "claims" / "interface.json"

# addr -> (src, name, body, optional_decl)
HAND: dict[int, tuple[str, str, str, str | None]] = {}


def H(addr: int, src: str, name: str, body: str, decl: str | None = None) -> None:
    HAND[addr] = (src, name, body.strip() + "\n", decl)


# --- thin / leaves ---
H(
    0xDFF70,
    "interface/interface.c",
    "interface_draw_fullscreen_overlays",
    """
/* interface_draw_fullscreen_overlays (0xdff70) — readable C lift. */
void interface_draw_fullscreen_overlays(void)
{
  cinematic_render();
  interface_draw_splitscreen_dividers();
  hud_render_timer();
  terminal_draw();
  main_framerate_render();
  FUN_000df4e0();
}
""",
)
H(
    0xE0960,
    "interface/player_ui.c",
    "player_ui_clear_multiplayer_variant",
    """
/* player_ui_clear_multiplayer_variant (0xe0960) — readable C lift. */
void player_ui_clear_multiplayer_variant(void)
{
  *(unsigned char *)0x46c034 = 0;
  set_game_connection(0);
  game_engine_dispose();
  game_set_game_variant(0);
}
""",
)
H(
    0xE0EA0,
    "interface/player_ui.c",
    "player_ui_get_edit_player_profile",
    """
/* player_ui_get_edit_player_profile (0xe0ea0) — readable C lift. */
void *player_ui_get_edit_player_profile(void)
{
  short t = (short)saved_game_file_get_type(*(int *)0x46c038);
  /* neg/sbb/not/and: return buffer iff type == 0 */
  return t == 0 ? (void *)0x46c03c : (void *)0;
}
""",
    "void *player_ui_get_edit_player_profile(void);",
)
H(
    0xE0EC0,
    "interface/player_ui.c",
    "player_ui_get_edit_playlist_profile",
    """
/* player_ui_get_edit_playlist_profile (0xe0ec0) — readable C lift. */
void *player_ui_get_edit_playlist_profile(void)
{
  short t = (short)saved_game_file_get_type(*(int *)0x46c038);
  /* return buffer iff type == 1 */
  return t == 1 ? (void *)0x46c03c : (void *)0;
}
""",
    "void *player_ui_get_edit_playlist_profile(void);",
)
H(
    0xF0620,
    "interface/ui_widget_game_data_input_functions.c",
    "FUN_000f0620",
    """
/* FUN_000f0620 (0xf0620) — readable C lift. */
char FUN_000f0620(void *widget)
{
  ui_widgets_pop_stack(*(unsigned short *)((char *)widget + 8));
  return 1;
}
""",
    "char FUN_000f0620(void *widget);",
)
H(
    0xF0070,
    "interface/ui_widget_game_data_input_functions.c",
    "FUN_000f0070",
    """
/* FUN_000f0070 (0xf0070) — readable C lift. */
char FUN_000f0070(void *widget)
{
  if (!xbox_demos_available()) {
    ((unsigned char *)widget)[0x12] = 1;
    ((unsigned char *)widget)[0x10] = 0;
  }
  return 1;
}
""",
    "char FUN_000f0070(void *widget);",
)
H(
    0xE0FD0,
    "interface/player_ui.c",
    "player_ui_activate_all_solo_levels",
    """
/* player_ui_activate_all_solo_levels (0xe0fd0) — readable C lift. */
void player_ui_activate_all_solo_levels(void)
{
  int i;
  for (i = 0; i < 10; i++)
    *(unsigned char *)(0x46befc + i) |= 0xf;
  if (*(int *)0x46bf10 != -1)
    player_profile_get_from_path(*(int *)0x46bf10, (void *)0x46bee0);
}
""",
)
H(
    0xE9A60,
    "interface/ui_widget.c",
    "FUN_000e9a60",
    """
/* FUN_000e9a60 (0xe9a60) — readable C lift. */
char FUN_000e9a60(void *widget)
{
  csmemset((void *)0x46cce8, 0, 0x50);
  *(int *)((char *)widget + 0x40) = 0;
  *(unsigned short *)((char *)widget + 0x44) = 0;
  return 1;
}
""",
)
H(
    0xEA540,
    "interface/ui_widget.c",
    "FUN_000ea540",
    """
/* FUN_000ea540 (0xea540) — readable C lift. */
char FUN_000ea540(void *widget)
{
  void *p = *(void **)((char *)widget + 0x40);
  if (p) {
    widget_free(p);
    *(void **)((char *)widget + 0x40) = 0;
  }
  *(unsigned short *)((char *)widget + 0x44) = 0;
  return 1;
}
""",
)
H(
    0xEAB70,
    "interface/ui_widget.c",
    "FUN_000eab70",
    """
/* FUN_000eab70 (0xeab70) — readable C lift. */
char FUN_000eab70(void *widget)
{
  void *p = *(void **)((char *)widget + 0x40);
  if (p) {
    widget_free(p);
    *(void **)((char *)widget + 0x40) = 0;
  }
  *(unsigned short *)((char *)widget + 0x44) = 0;
  return 1;
}
""",
)
H(
    0xEEBE0,
    "interface/ui_widget_game_data_input_functions.c",
    "FUN_000eebe0",
    """
/* FUN_000eebe0 (0xeebe0) — readable C lift. */
char FUN_000eebe0(void *widget)
{
  void *p = *(void **)((char *)widget + 0x40);
  if (p) {
    widget_free(p);
    *(void **)((char *)widget + 0x40) = 0;
  }
  return 1;
}
""",
    "char FUN_000eebe0(void *widget);",
)
H(
    0xE33E0,
    "interface/progress_bar.c",
    "FUN_000e33e0",
    """
/* FUN_000e33e0 (0xe33e0) — readable C lift. */
void FUN_000e33e0(void)
{
  void *d = *(void **)0x46c408;
  if (d) {
    if (*((unsigned char *)d + 0x24))
      data_make_invalid(d);
    data_dispose(*(void **)0x46c408);
  }
  *(unsigned char *)0x46c404 = 0;
}
""",
)
H(
    0xE33A0,
    "interface/progress_bar.c",
    "FUN_000e33a0",
    """
/* FUN_000e33a0 (0xe33a0) — readable C lift. */
void FUN_000e33a0(void)
{
  void *d = data_new((void *)0x282db4, 0x20, 0x124);
  *(void **)0x46c408 = d;
  *(unsigned char *)0x46c404 = 1;
  data_delete_all(d);
  *(int *)0x46c414 = 0;
  *(int *)0x46c40c = -1;
  *(int *)0x46c410 = -1;
}
""",
)
H(
    0xE1060,
    "interface/player_ui.c",
    "FUN_000e1060",
    """
/* FUN_000e1060 (0xe1060) — readable C lift. */
int FUN_000e1060(void)
{
  unsigned char v = *(unsigned char *)0x46bf09;
  if (v == 0 || v == 1)
    return 1;
  return 0;
}
""",
)
H(
    0xE0840,
    "interface/player_ui.c",
    "player_ui_local_player_joined_multiplayer_game",
    """
/* player_ui_local_player_joined_multiplayer_game (0xe0840) — readable C lift. */
void player_ui_local_player_joined_multiplayer_game(int16_t local_player_index)
{
  if ((int16_t)local_player_index < 0 || (int16_t)local_player_index >= 4) {
    display_assert((const char *)0x282750, (const char *)0x282724, 0x9d, 1);
    system_exit(-1);
  }
  *(unsigned char *)(0x46bf14 + (int16_t)local_player_index * 0x38) = 1;
  *(unsigned char *)(0x46bfc0 + (int16_t)local_player_index) = 1;
}
""",
    "void player_ui_local_player_joined_multiplayer_game(int16_t local_player_index);",
)
H(
    0xE0890,
    "interface/player_ui.c",
    "player_ui_local_player_wants_to_play_multiplayer",
    """
/* player_ui_local_player_wants_to_play_multiplayer (0xe0890) — readable C lift. */
uint8_t player_ui_local_player_wants_to_play_multiplayer(int16_t local_player_index)
{
  if ((int16_t)local_player_index < 0 || (int16_t)local_player_index >= 4) {
    display_assert((const char *)0x282750, (const char *)0x282724, 0xa7, 1);
    system_exit(-1);
  }
  return *(uint8_t *)(0x46bf14 + (int16_t)local_player_index * 0x38);
}
""",
    "uint8_t player_ui_local_player_wants_to_play_multiplayer(int16_t local_player_index);",
)
H(
    0xE08E0,
    "interface/player_ui.c",
    "player_ui_clear_multiplayer_autojoin_for_local_player",
    """
/* player_ui_clear_multiplayer_autojoin_for_local_player (0xe08e0) — readable C lift. */
void player_ui_clear_multiplayer_autojoin_for_local_player(int16_t local_player_index)
{
  if ((int16_t)local_player_index < 0 || (int16_t)local_player_index >= 4) {
    display_assert((const char *)0x282750, (const char *)0x282724, 0xaf, 1);
    system_exit(-1);
  }
  *(unsigned char *)(0x46bf14 + (int16_t)local_player_index * 0x38) = 0;
}
""",
    "void player_ui_clear_multiplayer_autojoin_for_local_player(int16_t local_player_index);",
)
H(
    0xE0A10,
    "interface/player_ui.c",
    "player_ui_get_last_single_player_level_played",
    """
/* player_ui_get_last_single_player_level_played (0xe0a10) — readable C lift. */
int16_t player_ui_get_last_single_player_level_played(int16_t local_player_index)
{
  if ((int16_t)local_player_index < 0 || (int16_t)local_player_index >= 4) {
    display_assert((const char *)0x282750, (const char *)0x282724, 0x109, 1);
    system_exit(-1);
  }
  return *(int16_t *)(0x46bf06 + (int16_t)local_player_index * 0x38);
}
""",
    "int16_t player_ui_get_last_single_player_level_played(int16_t local_player_index);",
)
H(
    0xE0A60,
    "interface/player_ui.c",
    "player_ui_set_game_variant",
    """
/* player_ui_set_game_variant (0xe0a60) — readable C lift. */
void player_ui_set_game_variant(void *variant)
{
  if (!variant) {
    display_assert((const char *)0x282808, (const char *)0x282724, 0x111, 1);
    system_exit(-1);
  }
  csmemcpy((void *)0x46bfcc, variant, 0x68);
  *(unsigned char *)0x46c034 = 1;
}
""",
    "void player_ui_set_game_variant(void *variant);",
)
H(
    0xE0AB0,
    "interface/player_ui.c",
    "player_ui_game_variant_specified",
    """
/* player_ui_game_variant_specified (0xe0ab0) — readable C lift. */
char player_ui_game_variant_specified(void *out_variant)
{
  if (!out_variant) {
    display_assert((const char *)0x282808, (const char *)0x282724, 0x11c, 1);
    system_exit(-1);
  }
  if (*(unsigned char *)0x46c034) {
    csmemcpy(out_variant, (void *)0x46bfcc, 0x68);
    return *(unsigned char *)0x46c034;
  }
  return 0;
}
""",
    "char player_ui_game_variant_specified(void *out_variant);",
)
H(
    0xE0B00,
    "interface/player_ui.c",
    "player_ui_rumble_disabled",
    """
/* player_ui_rumble_disabled (0xe0b00) — readable C lift. */
bool player_ui_rumble_disabled(int controller_index)
{
  int16_t si = (int16_t)controller_index;
  if (si == -1)
    return 0;
  if (si < 0 || si >= 4) {
    display_assert((const char *)0x282750, (const char *)0x282724, 0x131, 1);
    system_exit(-1);
  }
  return *(unsigned char *)(0x46bf0c + si * 0x38) != 0;
}
""",
)
H(
    0xE0C90,
    "interface/player_ui.c",
    "player_ui_get_player1_last_used_profile_index",
    """
/* player_ui_get_player1_last_used_profile_index (0xe0c90) — readable C lift. */
int player_ui_get_player1_last_used_profile_index(void)
{
  if (!*(unsigned char *)0x46c110) {
    if (saved_game_file_retrieve_player1_last_used_profile_directory((void *)0x46c110)) {
      *(int *)0x30f02c = saved_game_file_find_profile_index_for_directory_path((void *)0x46c110, 0);
      return *(int *)0x30f02c;
    }
  }
  return *(int *)0x30f02c;
}
""",
    "int player_ui_get_player1_last_used_profile_index(void);",
)
H(
    0xE0BF0,
    "interface/player_ui.c",
    "player_ui_get_path_to_local_player_profile_directory",
    """
/* player_ui_get_path_to_local_player_profile_directory (0xe0bf0) — readable C lift. */
char player_ui_get_path_to_local_player_profile_directory(int16_t local_player_index, void *out_path)
{
  if ((int16_t)local_player_index < 0 || (int16_t)local_player_index >= 4)
    return 0;
  return (char)FUN_001c1280(*(int *)(0x46bf10 + (int16_t)local_player_index * 0x38), out_path);
}
""",
    "char player_ui_get_path_to_local_player_profile_directory(int16_t local_player_index, void *out_path);",
)
H(
    0xE0D80,
    "interface/player_ui.c",
    "player_ui_edit_profile_is_default_profile",
    """
/* player_ui_edit_profile_is_default_profile (0xe0d80) — readable C lift. */
char player_ui_edit_profile_is_default_profile(void)
{
  int idx = *(int *)0x46c038;
  if (idx == -1)
    return 0;
  {
    int t = (unsigned short)saved_game_file_get_type(idx);
    if (t < 0 || t > 1) {
      error(2, (const char *)0x282938);
      return 0;
    }
    return (char)((*(unsigned int *)0x46c038 >> 30) & 1);
  }
}
""",
    "char player_ui_edit_profile_is_default_profile(void);",
)
H(
    0xE4330,
    "interface/ui_widget.c",
    "widget_instance_get_child_index_from_parent",
    """
/* widget_instance_get_child_index_from_parent (0xe4330) — readable C lift. */
int widget_instance_get_child_index_from_parent(void *widget)
{
  void *parent = *(void **)((char *)widget + 0x30);
  void *child;
  int i;
  if (!parent)
    return -1;
  child = *(void **)((char *)parent + 0x34);
  for (i = 0; child; child = *(void **)((char *)child + 0x2c), i++) {
    if (child == widget)
      return i;
  }
  return -1;
}
""",
)
H(
    0xE55E0,
    "interface/ui_widget.c",
    "modulate_pixel32_by_real_alpha",
    """
/* modulate_pixel32_by_real_alpha (0xe55e0) — readable C lift. */
unsigned int modulate_pixel32_by_real_alpha(unsigned int pixel, float alpha)
{
  unsigned int a = pixel >> 24;
  float fa = (float)a * alpha;
  unsigned int na = (unsigned int)(int)fa;
  return (pixel & 0xffffffu) | (na << 24);
}
""",
)
H(
    0xE3E60,
    "interface/ui_widget.c",
    "FUN_000e3e60",
    """
/* FUN_000e3e60 (0xe3e60) — readable C lift. */
float FUN_000e3e60(int a, float b)
{
  return (float)((double)(b * 0.001f * (float)a) + 1.0);
}
""",
)
H(
    0xDDB90,
    "interface/first_person_weapons.c",
    "first_person_weapon_get_marker_by_name_render",
    """
/* first_person_weapon_get_marker_by_name_render (0xddb90) — readable C lift. */
int16_t first_person_weapon_get_marker_by_name_render(
    int object_handle, const char *marker_name, void *out_markers, int16_t max_markers)
{
  if (*(int16_t *)0x506548 != (int16_t)FUN_000dcd60())
    return 0;
  return first_person_weapon_get_marker_by_name(
      object_handle, marker_name, out_markers, max_markers);
}
""",
)
H(
    0xE54E0,
    "interface/ui_widget.c",
    "get_ui_rgb_white",
    """
/* get_ui_rgb_white (0xe54e0) — readable C lift. */
void get_ui_rgb_white(float *out)
{
  out[0] = *(float *)0x31e148;
  out[1] = *(float *)0x31e14c;
  out[2] = *(float *)0x31e150;
}
""",
)
H(
    0xF00B0,
    "interface/ui_widget_game_data_input_functions.c",
    "FUN_000f00b0",
    """
/* FUN_000f00b0 (0xf00b0) — readable C lift. */
char FUN_000f00b0(void *widget, void *event)
{
  (void)widget;
  if (!event) {
    display_assert((const char *)0x288670, (const char *)0x2859a4, 0x11b9, 1);
    system_exit(-1);
  }
  player_ui_set_single_player_local_player_controller(0, *(int16_t *)((char *)event + 2));
  return 1;
}
""",
    "char FUN_000f00b0(void *widget, void *event);",
)
H(
    0xE4420,
    "interface/ui_widget.c",
    "ui_set_next_level",
    """
/* ui_set_next_level (0xe4420) — readable C lift. */
void ui_set_next_level(int16_t level_index)
{
  int idx = (int16_t)level_index;
  if (idx == -1) {
    main_roll_credits();
    return;
  }
  if (idx < 0 || idx > 9) {
    error(2, (const char *)0x283318);
    main_goto_main_menu();
    return;
  }
  main_set_map_name(main_get_solo_level_name(level_index));
  main_disallow_persistent_storage();
}
""",
)
H(
    0xDC7A0,
    "interface/first_person_weapons.c",
    "FUN_000dc7a0",
    """
/* FUN_000dc7a0 (0xdc7a0) — readable C lift. */
void FUN_000dc7a0(void)
{
  int i;
  for (i = 0; i < 4; i++) {
    int off = i * 0x1ea0;
    char *base = *(char **)0x46bea8;
    csmemset(base + off, 0, 0x1ea0);
    *(int *)(base + off + 4) = -1;
    *(int *)(base + off + 0x1e98) = -1;
    *(int16_t *)(base + off + 0x1e9c) = -1;
  }
}
""",
)
H(
    0xE2650,
    "interface/progress_bar.c",
    "FUN_000e2650",
    """
/* FUN_000e2650 (0xe2650) — readable C lift. */
void FUN_000e2650(float x, float y, float z)
{
  D3DDevice_SetVertexData2f(0xa, x * 32.0f + z, y * 20.0f);
}
""",
    "void FUN_000e2650(float x, float y, float z);",
)
H(
    0xE5530,
    "interface/ui_widget.c",
    "get_ui_argb_white",
    """
/* get_ui_argb_white (0xe5530) — readable C lift. */
void get_ui_argb_white(float *out)
{
  float *src = *(float **)0x2ee6c4;
  out[0] = src[0];
  out[1] = *(float *)0x31e148;
  out[2] = *(float *)0x31e14c;
  out[3] = *(float *)0x31e150;
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
        changed = False
        for o in local.get("objects", []):
            for fn in o.get("functions") or []:
                if not isinstance(fn, dict) or not fn.get("addr"):
                    continue
                ai = int(fn["addr"], 16)
                if fn.get("ported") is not True and rmap.get(ai):
                    fn["ported"] = True
                    changed = True
        if changed:
            KB_PATH.write_text(json.dumps(local, indent=2) + "\n", encoding="utf-8")
    except Exception as exc:
        print(f"kb merge skip: {exc}", flush=True)


def set_kb_decl(addr: int, decl: str) -> None:
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    for o in kb.get("objects", []):
        for fn in o.get("functions") or []:
            if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == addr:
                if fn.get("decl") == decl:
                    return
                fn["decl"] = decl
                KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
                subprocess.run(
                    [
                        sys.executable,
                        str(ROOT / "tools/analysis/knowledge.py"),
                        "--gen-header",
                        str(ROOT / "build/generated/decl.h"),
                        "--gen-def",
                        str(ROOT / "build/generated/halo.xbe.def"),
                        "--gen-thunks",
                        str(ROOT / "build/generated/thunks.c"),
                    ],
                    cwd=ROOT,
                    capture_output=True,
                    check=False,
                )
                return


def commit_chunk(n: int, paths: set[Path], do_push: bool = True) -> str | None:
    merge_remote_kb()
    for p in paths:
        subprocess.run(["git", "add", str(p)], cwd=ROOT, check=False)
    subprocess.run(
        [
            "git",
            "add",
            "kb.json",
            "scripts/lifter_interface.py",
            "artifacts/claims/interface.json",
            "tools/equivalence/leaf_cache.json",
        ],
        cwd=ROOT,
        check=False,
    )
    subprocess.run(["git", "add", "-u", "src/halo/interface"], cwd=ROOT, check=False)
    msg = f"lift(track-a): interface naked→C + Unicorn-prove {n} (ported:true)."
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
                    "fix(track-a): union concurrent ported:true into interface kb.",
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
    if not ops or ops[-1][0] not in ("ret", "retn"):
        return None
    mid = ops[:-1]
    sig = law.cdecl_sig(decl, name)
    ps = law.params(sig)

    # widget free-at-+0x40 (+ optional clear +0x44)
    if (
        len(mid) >= 10
        and mid[0] == ("push", "ebp")
        and mid[1] == ("mov", "ebp, esp")
        and mid[2] == ("push", "esi")
        and mid[3] == ("mov", "esi, dword ptr [ebp + 8]")
        and mid[4] == ("mov", "eax, dword ptr [esi + 0x40]")
        and mid[5] == ("test", "eax, eax")
        and mid[6][0] == "je"
        and mid[7] == ("push", "eax")
        and mid[8][0] == "call"
        and "0xe3d50" in mid[8][1]
    ):
        clears_word = any(
            m == "mov" and "word ptr [esi + 0x44]" in o for m, o in mid
        )
        ret_one = any(m == "mov" and o == "al, 1" for m, o in mid)
        if ret_one:
            extra = (
                "  *(unsigned short *)((char *)widget + 0x44) = 0;\n" if clears_word else ""
            )
            return (
                f"char {name}(void *widget)\n{{\n"
                f"  void *p = *(void **)((char *)widget + 0x40);\n"
                f"  if (p) {{\n"
                f"    widget_free(p);\n"
                f"    *(void **)((char *)widget + 0x40) = 0;\n"
                f"  }}\n"
                f"{extra}"
                f"  return 1;\n}}\n"
            )

    # assert 0..3 index; load byte/word at base+index*0x38
    if (
        len(mid) >= 18
        and mid[0] == ("push", "ebp")
        and mid[1] == ("mov", "ebp, esp")
        and mid[2] == ("push", "esi")
        and "word ptr [ebp + 8]" in mid[3][1]
        and mid[4] == ("test", "si, si")
    ):
        # find imul * 0x38 and subsequent load/store
        imul_i = next(
            (i for i, (m, o) in enumerate(mid) if m == "imul" and "0x38" in o), -1
        )
        if imul_i > 0:
            rest = mid[imul_i + 1 :]
            # load byte
            mbyte = re.match(
                r"(al|ax), (byte|word) ptr \[eax \+ 0x([0-9a-f]+)\]",
                rest[0][1] if rest else "",
            ) or (
                re.match(
                    r"(byte|word) ptr \[eax \+ 0x([0-9a-f]+)\], (0x[0-9a-f]+|\d+)",
                    rest[0][1],
                )
                if rest and rest[0][0] == "mov"
                else None
            )
            # assert line from push immediates
            ab = None
            for i in range(len(mid)):
                ab = law.parse_assert(mid, i)
                if ab:
                    break
            if ab and rest:
                # store imm to byte
                ms = re.match(
                    r"byte ptr \[eax \+ 0x([0-9a-f]+)\], (0x[0-9a-f]+|\d+)",
                    rest[0][1],
                )
                if ms:
                    off, val = int(ms.group(1), 16), ms.group(2)
                    base = off  # absolute uses eax+off where eax=index*0x38; need base from encoding
                    # actually [eax + 0x46bf14] style
                ms = re.match(
                    r"byte ptr \[eax \+ 0x([0-9a-f]+)\], (0x[0-9a-f]+|\d+)",
                    rest[0][1],
                ) or re.match(
                    r"byte ptr \[eax \+ ([0-9a-f]+)\], (0x[0-9a-f]+|\d+)",
                    rest[0][1],
                )
                # Capstone: byte ptr [eax + 0x46bf14]
                ms = re.match(
                    r"byte ptr \[eax \+ 0x([0-9a-f]+)\], (.+)$",
                    rest[0][1],
                )
                ml = re.match(
                    r"(al|ax), (byte|word) ptr \[eax \+ 0x([0-9a-f]+)\]$",
                    rest[0][1],
                )
                # also: mov byte ptr [ecx + 0x46bf14], 1 with ecx=index*0x38
                # handled in HAND; skip complex here

    # call chain then jmp tailcall
    if (
        len(mid) >= 5
        and all(m == "call" for m, _ in mid[:-1])
        and mid[-1][0] == "jmp"
    ):
        calls = []
        ok = True
        for m, o in mid[:-1]:
            cm = re.search(r"0x([0-9a-f]+)", o)
            if not cm:
                ok = False
                break
            ca = int(cm.group(1), 16)
            nm = name_by.get(ca)
            if not nm:
                ok = False
                break
            calls.append(nm)
        jm = re.search(r"0x([0-9a-f]+)", mid[-1][1])
        if ok and jm:
            ja = int(jm.group(1), 16)
            jn = name_by.get(ja)
            if jn:
                body_lines = "".join(f"  {c}();\n" for c in calls)
                return f"void {name}(void)\n{{\n{body_lines}  {jn}();\n}}\n"

    return None


def apply_body(path: Path, name: str, addr: int, c_src: str) -> tuple[str | None, str | None]:
    text = path.read_text(encoding="utf-8", errors="replace")
    span = find_naked_block(text, name, addr)
    if span is None:
        span = find_naked_block(text, f"FUN_{addr:08x}", addr)
    if span is None:
        return None, "locate"
    # If a prior bad relift stub sits above the naked block, replace from stub if present.
    stub = re.search(
        rf"(?:/\*[^*]*relift[^*]*\*/\s*)?(?:[\w\s\*]+?\b{re.escape(name)}\s*\([^;]*\)\s*\{{[\s\S]*?\n\}})\s*"
        rf"(?=/\*[^*]*\(0x{addr:x}\))",
        text[: span[0] + 1],
        re.I,
    )
    start = stub.start() if stub else span[0]
    needs_stdint = any(
        t in c_src for t in ("uint8_t", "uint16_t", "uint32_t", "uintptr_t", "int8_t", "int16_t", "bool")
    )
    new_text = text[:start] + c_src + "\n" + text[span[1] :]
    if needs_stdint and "#include <stdint.h>" not in new_text:
        new_text = "#include <stdint.h>\n" + new_text
    if "bool" in c_src and "#include <stdbool.h>" not in new_text and "typedef" not in new_text[:500]:
        # halo often has bool via common.h; skip forcing
        pass
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
    ap.add_argument("--prove-only", action="store_true")
    ap.add_argument(
        "--addrs",
        default="",
        help="Comma/space separated hex addrs to include (optional filter)",
    )
    args = ap.parse_args()
    addr_filter: set[int] | None = None
    if args.addrs.strip():
        addr_filter = set()
        for tok in re.split(r"[\s,]+", args.addrs.strip()):
            if tok:
                addr_filter.add(int(tok, 16))

    CLAIM.parent.mkdir(parents=True, exist_ok=True)
    CLAIM.write_text(
        json.dumps(
            {
                "domain": "src/halo/interface/**",
                "agent": "lifter_interface",
                "started": time.time(),
            },
            indent=2,
        )
        + "\n"
    )

    merge_remote_kb()
    kb, name_by, decl_by, src_by, ported = load_names()
    by_addr, starts = load_kb(KB_PATH)
    xbe = Xbe((ROOT / "halo-patched" / "cachebeta.xbe").read_bytes())
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    true0, false0 = count_ported(kb)

    jobs: list[dict] = []
    seen = set()

    if not args.prove_only:
        for ai, (src, name, body, new_decl) in sorted(HAND.items()):
            if addr_filter is not None and ai not in addr_filter:
                continue
            if ported.get(ai) is not False:
                continue
            if not in_pref(src_by.get(ai, src)):
                continue
            # Skip lifts that require decl changes unless explicitly filtered in.
            if new_decl and (addr_filter is None):
                kb_decl = decl_by.get(ai) or ""
                if re.sub(r"\s+", "", new_decl.rstrip(";")) != re.sub(
                    r"\s+", "", re.sub(r"\s*@<\w+>", "", kb_decl).rstrip(";")
                ):
                    continue
            jobs.append(
                {
                    "addr": ai,
                    "name": name_by.get(ai, name),
                    "src": src_by.get(ai, src),
                    "kind": "hand",
                    "decl": new_decl,
                    "body": body if body.lstrip().startswith("/*") else f"/* {name} */\n{body}",
                }
            )
            seen.add(ai)

        for i, ai in enumerate(starts):
            if addr_filter is not None and ai not in addr_filter:
                continue
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
            ops = []
            for insn in md.disasm(raw, ai):
                ops.append((insn.mnemonic, insn.op_str))
            last_ret = max((i for i, o in enumerate(ops) if o[0] in ("ret", "retn")), default=-1)
            if last_ret < 0:
                continue
            # Prefer first-ret cut for linear matchers; also try full-to-last-ret
            cut = []
            for o in ops:
                cut.append(o)
                if o[0] in ("ret", "retn"):
                    break
            name = name_by[ai]
            decl = decl_by.get(ai) or f"void {name}(void);"
            body = try_pattern_emit(cut, decl, name, name_by)
            if not body:
                body = try_pattern_emit(ops[: last_ret + 1], decl, name, name_by)
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

    for r in inventory_readable(kb):
        if addr_filter is not None and r["addr_int"] not in addr_filter:
            continue
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
        f"lifter-interface jobs={len(jobs)} kb true={true0} false={false0} "
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
            text0 = path.read_text(encoding="utf-8", errors="replace")
            if not is_naked_near_def(text0.splitlines(), name, hex(ai)):
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
    # interface-specific counts
    iface_true = iface_false = 0
    kb2 = json.loads(KB_PATH.read_text(encoding="utf-8"))
    for o in kb2.get("objects", []):
        if not in_pref(o.get("source") or ""):
            continue
        for fn in o.get("functions") or []:
            if not isinstance(fn, dict):
                continue
            if fn.get("ported") is True:
                iface_true += 1
            elif fn.get("ported") is False:
                iface_false += 1

    summary = {
        "proven": len(flips),
        "flips": flips,
        "shas": shas,
        "true0": true0,
        "true1": true1,
        "false0": false0,
        "false1": false1,
        "interface_true": iface_true,
        "interface_false": iface_false,
        "head": subprocess.run(
            ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
        ).stdout.strip(),
    }
    Path("/tmp/lifter_interface_summary.json").write_text(json.dumps(summary, indent=2))
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
