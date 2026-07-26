#!/usr/bin/env python3
"""Batch-4: lift small naked inventory leaves (no-call + thin wrappers) to readable C."""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
KB_PATH = ROOT / "kb.json"

LIFTS: dict[int, tuple[str, str, str, str | None]] = {}


def L(addr: int, source: str, name: str, body: str, decl: str | None = None):
    LIFTS[addr] = (source, name, body.strip() + "\n", decl)


# --- no-call / global-store / getters ---

L(
    0x8F8C0,
    "cseries/profile.c",
    "profile_lapsed_msec",
    """
/* profile_lapsed_msec (0x8f8c0) — readable C lift. */
void profile_lapsed_msec(int value)
{
  *(int *)0x449cd0 = value;
  *(char *)0x449cd4 = value > 0;
}
""",
    "void profile_lapsed_msec(int value);",
)

L(
    0x92050,
    "cseries/profile.c",
    "FUN_00092050",
    """
/* FUN_00092050 (0x92050) — readable C lift. */
void FUN_00092050(char value)
{
  *(char *)0x2ee784 = value;
}
""",
    "void FUN_00092050(char value);",
)

L(
    0x93030,
    "cutscene/cinematics.c",
    "cinematic_suppress_bsp_object_creation",
    """
/* cinematic_suppress_bsp_object_creation (0x93030) — readable C lift. */
void cinematic_suppress_bsp_object_creation(char suppress)
{
  char *g = *(char **)0x44df00;
  g[0xb] = suppress;
}
""",
    "void cinematic_suppress_bsp_object_creation(char suppress);",
)

L(
    0x82060,
    "bungie_net/network/transport_endpoint_set_winsock.c",
    "transport_get_xnaddr",
    """
/* transport_get_xnaddr (0x82060) — readable C lift. */
void *transport_get_xnaddr(void *dst)
{
  int *out = (int *)dst;
  out[0] = *(int *)0x5ab230;
  out[1] = *(int *)0x5ab234;
  out[2] = *(int *)0x5ab238;
  return dst;
}
""",
    "void *transport_get_xnaddr(void *dst);",
)

L(
    0xE0930,
    "interface/player_ui.c",
    "player_ui_autojoin_players_to_next_multiplayer_game",
    """
/* player_ui_autojoin_players_to_next_multiplayer_game (0xe0930) — readable C lift. */
void player_ui_autojoin_players_to_next_multiplayer_game(void)
{
  *(char *)0x46bf14 = *(char *)0x46bfc0;
  *(char *)0x46bf4c = *(char *)0x46bfc1;
  *(char *)0x46bf84 = *(char *)0x46bfc2;
  *(char *)0x46bfbc = *(char *)0x46bfc3;
}
""",
)

L(
    0xE09E0,
    "interface/player_ui.c",
    "player_ui_get_active_player_profile_index",
    """
/* player_ui_get_active_player_profile_index (0xe09e0) — readable C lift. */
int player_ui_get_active_player_profile_index(short index)
{
  if (index < 0 || index >= 4) {
    return -1;
  }
  return *(int *)(0x46bf10 + (int)index * 0x38);
}
""",
    "int player_ui_get_active_player_profile_index(short index);",
)

L(
    0xE3D70,
    "interface/ui_widget.c",
    "ui_widgets_active",
    """
/* ui_widgets_active (0xe3d70) — readable C lift. */
char ui_widgets_active(void)
{
  int *slot;

  if (!*(char *)0x46cc82) {
    return 0;
  }
  for (slot = (int *)0x46cc20; slot < (int *)0x46cc30; slot++) {
    if (*slot != 0) {
      return 1;
    }
  }
  return 0;
}
""",
    "char ui_widgets_active(void);",
)

L(
    0xE4960,
    "interface/ui_widget.c",
    "widget_instance_get_opacity_product",
    """
/* widget_instance_get_opacity_product (0xe4960) — readable C lift. */
float widget_instance_get_opacity_product(void *widget)
{
  float product;
  char *node;

  node = (char *)widget;
  product = *(float *)(node + 0x24);
  node = *(char **)(node + 0x30);
  while (node) {
    product *= *(float *)(node + 0x24);
    node = *(char **)(node + 0x30);
  }
  return product;
}
""",
    "float widget_instance_get_opacity_product(void *widget);",
)

L(
    0x100560,
    "main/main.c",
    "main_skip",
    """
/* main_skip (0x100560) — readable C lift. */
void main_skip(short level)
{
  if (level > 0xf) {
    error(2, (const char *)0x28b238);
    return;
  }
  *(short *)0x46da4a = level;
  *(char *)0x46da49 = 1;
}
""",
    "void main_skip(short level);",
)

L(
    0x139300,
    "objects/object_lights.c",
    "lights_enable",
    """
/* lights_enable (0x139300) — readable C lift. */
char lights_enable(char active)
{
  char *g = *(char **)0x46f074;
  *g = active;
  return active;
}
""",
    "char lights_enable(char active);",
)

L(
    0x190A10,
    "shaders/shaders.c",
    "shader_type_is_vertex_lit",
    """
/* shader_type_is_vertex_lit (0x190a10) — readable C lift. */
char shader_type_is_vertex_lit(short shader_type)
{
  return shader_type == 4 || shader_type == 8;
}
""",
    "char shader_type_is_vertex_lit(short shader_type);",
)

L(
    0x190A50,
    "shaders/shaders.c",
    "shader_type_is_valid_for_model",
    """
/* shader_type_is_valid_for_model (0x190a50) — readable C lift. */
char shader_type_is_valid_for_model(short shader_type)
{
  return shader_type >= 3 && shader_type <= 10;
}
""",
    "char shader_type_is_valid_for_model(short shader_type);",
)

L(
    0x190BE0,
    "shaders/shaders.c",
    "numeric_countdown_timer_set",
    """
/* numeric_countdown_timer_set (0x190be0) — readable C lift. */
void numeric_countdown_timer_set(int value, char flag)
{
  *(int *)0x4d8a78 = value;
  *(char *)0x4d8a7c = flag;
}
""",
    "void numeric_countdown_timer_set(int value, char flag);",
)

L(
    0x19B8F0,
    "text/draw_string.c",
    "draw_string_set_highlight",
    """
/* draw_string_set_highlight (0x19b8f0) — readable C lift. */
void draw_string_set_highlight(short a, short b)
{
  *(short *)0x4d9b4a = a;
  *(short *)0x4d9b4c = b;
}
""",
    "void draw_string_set_highlight(short a, short b);",
)

L(
    0x19D060,
    "text/international_strings.c",
    "set_language_code",
    """
/* set_language_code (0x19d060) — readable C lift. */
void set_language_code(short code)
{
  if (code < 0 || code >= 6) {
    code = 0;
  }
  *(short *)0x4d9be0 = code;
}
""",
    "void set_language_code(short code);",
)

L(
    0x1C29A0,
    "saved games/saved_game_files.c",
    "saved_game_file_get_type",
    """
/* saved_game_file_get_type (0x1c29a0) — readable C lift. */
int saved_game_file_get_type(int handle)
{
  return handle & 0xf;
}
""",
    "int saved_game_file_get_type(int handle);",
)

L(
    0x1CB9B0,
    "sound/sound_manager.c",
    "sound_manager_set_sound_environment",
    """
/* sound_manager_set_sound_environment (0x1cb9b0) — readable C lift. */
void sound_manager_set_sound_environment(void *environment)
{
  int i;
  int *src = (int *)environment;
  int *dst = (int *)0x4eb068;
  for (i = 0; i < 0x12; i++) {
    dst[i] = src[i];
  }
}
""",
    "void sound_manager_set_sound_environment(void *environment);",
)

L(
    0x1CBA00,
    "sound/sound_manager.c",
    "FUN_001cba00",
    """
/* FUN_001cba00 (0x1cba00) — readable C lift: scale * lerp(a,b,t). */
float FUN_001cba00(float scale, float a, float b, float t)
{
  return ((b - a) * t + a) * scale;
}
""",
    "float FUN_001cba00(float scale, float a, float b, float t);",
)

L(
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
    "void FUN_001cf820(void **out);",
)

# Fix already-readable broken bodies
L(
    0xA57A0,
    "game/cheats.c",
    "FUN_000a57a0",
    """
/* FUN_000a57a0 (0xa57a0) — readable C lift: 1/sqrt(x). */
float FUN_000a57a0(float x)
{
  return *(float *)0x2533c8 / __builtin_sqrtf(x);
}
""",
    "float FUN_000a57a0(float x);",
)

L(
    0xA5810,
    "game/cheats.c",
    "FUN_000a5810",
    """
/* FUN_000a5810 (0xa5810) — readable C lift. */
void FUN_000a5810(float *out, float value, int field0)
{
  out[1] = value;
  *(int *)out = field0;
}
""",
    "void FUN_000a5810(float *out, float value, int field0);",
)

L(
    0xA2DC0,
    "effects/player_effects.c",
    "scripted_player_effect_set_translation",
    """
/* scripted_player_effect_set_translation (0xa2dc0) — readable C lift. */
void scripted_player_effect_set_translation(int a0, int a1, int a2)
{
  char *g = *(char **)0x4557ec;
  *(int *)(g + 0x3c4) = a0;
  *(int *)(g + 0x3c8) = a1;
  *(int *)(g + 0x3cc) = a2;
}
""",
    "void scripted_player_effect_set_translation(int a0, int a1, int a2);",
)

L(
    0x1B9920,
    "cache/cache_files.c",
    "FUN_001b9920",
    """
/* FUN_001b9920 (0x1b9920) — readable C lift. */
int FUN_001b9920(void)
{
  return *(int *)0x4e4d68;
}
""",
    "int FUN_001b9920(void);",
)

L(
    0xB6430,
    "game/player_control.c",
    "scripted_player_control_set_camera_control",
    """
/* scripted_player_control_set_camera_control (0xb6430) — readable C lift. */
void scripted_player_control_set_camera_control(char enable)
{
  unsigned int *flags = (unsigned int *)(*(char **)0x457090 + 0xc);
  if (enable) {
    *flags &= ~1u;
  } else {
    *flags |= 1u;
  }
}
""",
    "void scripted_player_control_set_camera_control(char enable);",
)

# --- thin wrappers (one known FUN_*/named callee) ---

L(
    0x42F40,
    "ai/ai_communication.c",
    "FUN_00042f40",
    """
/* FUN_00042f40 (0x42f40) — readable C lift: thin wrapper. */
char FUN_00042f40(int a, int b, int actor)
{
  (void)a;
  (void)b;
  return actor_is_fighting(actor);
}
""",
    "char FUN_00042f40(int a, int b, int actor);",
)

L(
    0x53650,
    "ai/ai_debug.c",
    "FUN_00053650",
    """
/* FUN_00053650 (0x53650) — readable C lift: memset helper. */
void FUN_00053650(void)
{
  csmemset((void *)0x5abaac, 0, 0xee0);
}
""",
    "void FUN_00053650(void);",
)

L(
    0xC1F80,
    "hs/hs.c",
    "FUN_000c1f80",
    """
/* FUN_000c1f80 (0xc1f80) — readable C lift: hs_return(thread, 0). */
void FUN_000c1f80(short function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  hs_return(thread_datum, 0);
}
""",
    "void FUN_000c1f80(short function_index, int thread_datum, char init);",
)

L(
    0xC2100,
    "hs/hs.c",
    "FUN_000c2100",
    """
/* FUN_000c2100 (0xc2100) — readable C lift: hs_return(thread, 0). */
void FUN_000c2100(short function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  hs_return(thread_datum, 0);
}
""",
    "void FUN_000c2100(short function_index, int thread_datum, char init);",
)

L(
    0xC2120,
    "hs/hs.c",
    "FUN_000c2120",
    """
/* FUN_000c2120 (0xc2120) — readable C lift: hs_return(thread, 0). */
void FUN_000c2120(short function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  hs_return(thread_datum, 0);
}
""",
    "void FUN_000c2120(short function_index, int thread_datum, char init);",
)

L(
    0xC2140,
    "hs/hs.c",
    "FUN_000c2140",
    """
/* FUN_000c2140 (0xc2140) — readable C lift: hs_return(thread, 0). */
void FUN_000c2140(short function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  hs_return(thread_datum, 0);
}
""",
    "void FUN_000c2140(short function_index, int thread_datum, char init);",
)

L(
    0xE0720,
    "interface/player_ui.c",
    "player_ui_reset_single_player_local_player_controllers",
    """
/* player_ui_reset_single_player_local_player_controllers (0xe0720) — readable C lift. */
void player_ui_reset_single_player_local_player_controllers(void)
{
  csmemset((void *)0x46bfc4, -1, 8);
}
""",
)

L(
    0xE3D50,
    "interface/ui_widget.c",
    "widget_free",
    """
/* widget_free (0xe3d50) — readable C lift. */
void widget_free(void *block)
{
  stack_memory_pool_deallocate(*(void **)0x31e04c, block);
}
""",
    "void widget_free(void *block);",
)

L(
    0x1003B0,
    "main/main.c",
    "main_save_core",
    """
/* main_save_core (0x1003b0) — readable C lift. */
void main_save_core(void)
{
  *(char *)0x46da3d = 1;
  csstrcpy((char *)0x46dd55, (const char *)0x28b198);
}
""",
)

L(
    0x100420,
    "main/main.c",
    "main_load_core",
    """
/* main_load_core (0x100420) — readable C lift. */
void main_load_core(void)
{
  *(char *)0x46da3e = 1;
  csstrcpy((char *)0x46dd55, (const char *)0x28b198);
}
""",
)

L(
    0x100440,
    "main/main.c",
    "main_load_core_at_startup",
    """
/* main_load_core_at_startup (0x100440) — readable C lift. */
void main_load_core_at_startup(void)
{
  *(char *)0x46da3f = 1;
  csstrcpy((char *)0x46dd55, (const char *)0x28b198);
}
""",
)

L(
    0x101CC0,
    "main/main.c",
    "main_print_version",
    """
/* main_print_version (0x101cc0) — readable C lift. */
void main_print_version(void)
{
  console_printf(0, (const char *)0x28b5d4);
}
""",
)

L(
    0x124A10,
    "networking/network_client_manager.c",
    "network_game_client_keep_alive",
    """
/* network_game_client_keep_alive (0x124a10) — readable C lift. */
void network_game_client_keep_alive(void *client)
{
  network_connection_keep_alive(*(int *)((char *)client + 0x82c));
}
""",
    "void network_game_client_keep_alive(void *client);",
)

L(
    0x130EF0,
    "main/telnet_console.c",
    "FUN_00130ef0",
    """
/* FUN_00130ef0 (0x130ef0) — readable C lift. */
void FUN_00130ef0(void)
{
  data_delete_all(*(data_t **)0x5a90d4);
}
""",
    "void FUN_00130ef0(void);",
)

L(
    0x130F00,
    "main/telnet_console.c",
    "FUN_00130f00",
    """
/* FUN_00130f00 (0x130f00) — readable C lift. */
void FUN_00130f00(void)
{
  data_make_invalid(*(data_t **)0x5a90d4);
}
""",
    "void FUN_00130f00(void);",
)

L(
    0x131130,
    "main/telnet_console.c",
    "FUN_00131130",
    """
/* FUN_00131130 (0x131130) — readable C lift. */
void FUN_00131130(int handle)
{
  datum_delete(*(data_t **)0x5a90d4, handle);
}
""",
    "void FUN_00131130(int handle);",
)

L(
    0x1319E0,
    "main/telnet_console.c",
    "FUN_001319e0",
    """
/* FUN_001319e0 (0x1319e0) — readable C lift. */
void FUN_001319e0(void)
{
  data_delete_all(*(data_t **)0x5a90d0);
}
""",
    "void FUN_001319e0(void);",
)

L(
    0x1319F0,
    "main/telnet_console.c",
    "FUN_001319f0",
    """
/* FUN_001319f0 (0x1319f0) — readable C lift. */
void FUN_001319f0(void)
{
  data_make_invalid(*(data_t **)0x5a90d0);
}
""",
    "void FUN_001319f0(void);",
)

L(
    0x131B40,
    "main/telnet_console.c",
    "FUN_00131b40",
    """
/* FUN_00131b40 (0x131b40) — readable C lift. */
void FUN_00131b40(int handle)
{
  datum_delete(*(data_t **)0x5a90d0, handle);
}
""",
    "void FUN_00131b40(int handle);",
)

L(
    0x1392A0,
    "objects/object_lights.c",
    "lights_dispose",
    """
/* lights_dispose (0x1392a0) — readable C lift. */
void lights_dispose(void)
{
  cluster_partition_null_references((int *)0x5a90b0);
}
""",
)

L(
    0x145560,
    "physics/breakable_surfaces.c",
    "FUN_00145560",
    """
/* FUN_00145560 (0x145560) — readable C lift. */
void FUN_00145560(int object_handle, char *placement)
{
  FUN_0013d870(object_handle, placement + 0x28);
}
""",
    "void FUN_00145560(int object_handle, char *placement);",
)

L(
    0x15F1F0,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_0015f1f0",
    """
/* FUN_0015f1f0 (0x15f1f0) — readable C lift. */
void FUN_0015f1f0(void)
{
  FUN_0016f910(0x1b);
}
""",
    "void FUN_0015f1f0(void);",
)

L(
    0x15F200,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_0015f200",
    """
/* FUN_0015f200 (0x15f200) — readable C lift. */
void FUN_0015f200(void)
{
  FUN_0016fa40(0x1b);
}
""",
    "void FUN_0015f200(void);",
)

L(
    0x160920,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_00160920",
    """
/* FUN_00160920 (0x160920) — readable C lift. */
void FUN_00160920(void)
{
  FUN_0016fa40(3);
}
""",
    "void FUN_00160920(void);",
)

L(
    0x160940,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "_rasterizer_hud_begin",
    """
/* _rasterizer_hud_begin (0x160940) — readable C lift. */
void _rasterizer_hud_begin(void)
{
  FUN_0016fa40(5);
}
""",
    "void _rasterizer_hud_begin(void);",
)

L(
    0x160980,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_00160980",
    """
/* FUN_00160980 (0x160980) — readable C lift. */
void FUN_00160980(void)
{
  FUN_0016fa40(0xb);
}
""",
    "void FUN_00160980(void);",
)

L(
    0x1609A0,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "_rasterizer_dynamic_lit_geometry_draw",
    """
/* _rasterizer_dynamic_lit_geometry_draw (0x1609a0) — readable C lift. */
void _rasterizer_dynamic_lit_geometry_draw(void)
{
  FUN_0016fa40(0xc);
}
""",
    "void _rasterizer_dynamic_lit_geometry_draw(void);",
)

L(
    0x160BC0,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_00160bc0",
    """
/* FUN_00160bc0 (0x160bc0) — readable C lift. */
void FUN_00160bc0(void)
{
  FUN_0016fa40(0xd);
}
""",
    "void FUN_00160bc0(void);",
)

L(
    0x160BD0,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_00160bd0",
    """
/* FUN_00160bd0 (0x160bd0) — readable C lift. */
void FUN_00160bd0(void)
{
  FUN_0016f910(0xe);
}
""",
    "void FUN_00160bd0(void);",
)

L(
    0x160BE0,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_00160be0",
    """
/* FUN_00160be0 (0x160be0) — readable C lift. */
void FUN_00160be0(void)
{
  FUN_0016fa40(0xe);
}
""",
    "void FUN_00160be0(void);",
)

L(
    0x160BF0,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_00160bf0",
    """
/* FUN_00160bf0 (0x160bf0) — readable C lift. */
void FUN_00160bf0(void)
{
  FUN_0016f910(0xf);
}
""",
    "void FUN_00160bf0(void);",
)

L(
    0x160C00,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_00160c00",
    """
/* FUN_00160c00 (0x160c00) — readable C lift. */
void FUN_00160c00(void)
{
  FUN_0016fa40(0xf);
}
""",
    "void FUN_00160c00(void);",
)

L(
    0x165DD0,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_00165dd0",
    """
/* FUN_00165dd0 (0x165dd0) — readable C lift. */
void FUN_00165dd0(void)
{
  FUN_0016fa40(0x11);
}
""",
    "void FUN_00165dd0(void);",
)

L(
    0x172720,
    "rasterizer/rasterizer.c",
    "rasterizer_window_get_fog",
    """
/* rasterizer_window_get_fog (0x172720) — readable C lift. */
void rasterizer_window_get_fog(void)
{
  FUN_0016fa40(4);
}
""",
    "void rasterizer_window_get_fog(void);",
)

L(
    0x17EB90,
    "rasterizer/rasterizer_sprites.c",
    "FUN_0017eb90",
    """
/* FUN_0017eb90 (0x17eb90) — readable C lift. */
void FUN_0017eb90(void)
{
  csmemset((void *)0x5a5400, 0, 0x170);
}
""",
    "void FUN_0017eb90(void);",
)

L(
    0x185810,
    "render/render_cameras.c",
    "render_camera_new",
    """
/* render_camera_new (0x185810) — readable C lift. */
void render_camera_new(void *camera)
{
  csmemset(camera, 0, 0x54);
}
""",
    "void render_camera_new(void *camera);",
)

L(
    0x19A020,
    "tag_files/files.c",
    "file_compare_last_modification_dates",
    """
/* file_compare_last_modification_dates (0x19a020) — readable C lift. */
int file_compare_last_modification_dates(const void *a, const void *b)
{
  return csmemcmp(a, b, 8);
}
""",
    "int file_compare_last_modification_dates(const void *a, const void *b);",
)

L(
    0x1BE940,
    "cache/xbox_texture_cache.c",
    "texture_cache_open",
    """
/* texture_cache_open (0x1be940) — readable C lift. */
void texture_cache_open(void)
{
  data_delete_all(*(data_t **)0x4ea978);
}
""",
)

L(
    0x1BE950,
    "cache/xbox_texture_cache.c",
    "texture_cache_idle",
    """
/* texture_cache_idle (0x1be950) — readable C lift. */
void texture_cache_idle(void)
{
  lruv_idle(*(void **)0x4ea980);
}
""",
)

L(
    0x1C1DA0,
    "saved games/saved_game_files.c",
    "FUN_001c1da0",
    """
/* FUN_001c1da0 (0x1c1da0) — readable C lift. */
void FUN_001c1da0(void)
{
  csmemset((void *)0x4eaa38, 0, 0x74);
  *(char *)0x4eaaaa = 1;
}
""",
    "void FUN_001c1da0(void);",
)

L(
    0x1C2AF0,
    "saved games/saved_game_files.c",
    "saved_game_files_take_mutex",
    """
/* saved_game_files_take_mutex (0x1c2af0) — readable C lift. */
void saved_game_files_take_mutex(void)
{
  take_mutex(*(int **)0x4eacbc, 0x36ee80);
}
""",
)

L(
    0x1C2B10,
    "saved games/saved_game_files.c",
    "saved_game_files_release_mutex",
    """
/* saved_game_files_release_mutex (0x1c2b10) — readable C lift. */
void saved_game_files_release_mutex(void)
{
  release_mutex(*(int **)0x4eacbc);
}
""",
)

L(
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
    "char sound_scripted_dialog_is_playing(void);",
)

L(
    0xB63D0,
    "game/player_control.c",
    "player_control_initialize",
    """
/* player_control_initialize (0xb63d0) — readable C lift. */
void player_control_initialize(void)
{
  *(void **)0x457090 = game_state_malloc((const char *)0x26e210, 0, 0x110);
}
""",
    "void player_control_initialize(void);",
)


def find_naked_block(text: str, name: str, addr: int):
    addr_hex = f"0x{addr:x}"
    alt_names = {name, f"FUN_{addr:08x}", f"FUN_{addr:08X}"}
    for nm in alt_names:
        pat = re.compile(
            rf"/\*[^*]*\b{re.escape(addr_hex)}\b[^*]*(?:XBE naked draft|naked draft \(batch)?[^*]*\*/\s*"
            rf"#if defined\(__clang__\)\s*"
            rf"(?:static[\s\S]*?)?"
            rf"__attribute__\(\(naked[^\)]*\)\)\s*"
            rf"[\w\s\*]+?\b{re.escape(nm)}\s*\([\s\S]*?#endif\s*\n",
            re.M | re.I,
        )
        m = pat.search(text)
        if m:
            return m.start(), m.end()
        # already-readable replacement target
        pat2 = re.compile(
            rf"/\*[^*]*\b{re.escape(addr_hex)}\b[^*]*readable C lift[^*]*\*/\s*"
            rf"[\w\s\*]+?\b{re.escape(nm)}\s*\([^{{]*\)\s*\{{[\s\S]*?\n\}}\s*\n",
            re.M | re.I,
        )
        m = pat2.search(text)
        if m:
            return m.start(), m.end()
    return None


def cast_stale_fnptrs(text: str, names: set[str]) -> str:
    def repl(m: re.Match) -> str:
        sym = m.group(2)
        if sym not in names:
            return m.group(0)
        if "(void *)" in m.group(0) or "(void*)" in m.group(0):
            return m.group(0)
        return f"{m.group(1)}(void *){sym};"

    return re.sub(
        r"(static\s+[\w\s\*]+?\(\s*\*\s*const\s+b[0-9a-fA-F]+_[cC][0-9a-fA-F]+\s*\)\s*\([^;]*?\)\s*=\s*)(?:\([^)]*\)\s*)?([A-Za-z_][\w]*)\s*;",
        repl,
        text,
    )


def apply_lifts(addrs=None):
    selected = addrs if addrs else sorted(LIFTS.keys())
    by_source: dict[str, list[int]] = {}
    names: set[str] = set()
    for a in selected:
        if a not in LIFTS:
            print(f"skip unknown {hex(a)}", file=sys.stderr)
            continue
        by_source.setdefault(LIFTS[a][0], []).append(a)
        names.add(LIFTS[a][1])

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
            # ensure stdint if needed
            if ("uint8_t" in text or "uint16_t" in text or "uint32_t" in text) and (
                "#include <stdint.h>" not in text
            ):
                text = "#include <stdint.h>\n" + text
            path.write_text(text, encoding="utf-8")

    for path in (ROOT / "src" / "halo").rglob("*.c"):
        text = path.read_text(encoding="utf-8", errors="replace")
        text2 = cast_stale_fnptrs(text, names)
        if text2 != text:
            path.write_text(text2, encoding="utf-8")
            print(f"cast-fnptrs {path.relative_to(ROOT)}")

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
                    n += 1
        KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        print(f"updated {n} kb decls")
    return results


def main() -> int:
    results = apply_lifts()
    ok = sum(1 for r in results if r.get("ok"))
    print(f"done: {ok}/{len(results)}")
    return 0 if ok else 1


if __name__ == "__main__":
    raise SystemExit(main())
