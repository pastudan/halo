#!/usr/bin/env python3
"""Track A domain lifts: networking/hs/interface/game — honest Unicorn >=100/0/0 only."""
from __future__ import annotations

import json
import os
import re
import subprocess
import sys
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
    0x80C20,
    "networking/message_header.c",
    "byte_swap_message_header",
    """
/* byte_swap_message_header (0x80c20) — readable C lift. */
void byte_swap_message_header(unsigned short *header, int byte_order)
{
  unsigned short v;
  unsigned short swapped;

  if (header == 0) {
    display_assert((const char *)0x265d1c, (const char *)0x265ccc, 0x50, 1);
    system_exit(-1);
  }
  if (byte_order == 1 || byte_order == 0) {
    v = *header;
    swapped = (unsigned short)(((v & 0xff) << 8) | (v >> 8));
    *header = swapped;
    return;
  }
  display_assert((const char *)0x265d00, (const char *)0x265ccc, 0x5e, 1);
  system_exit(-1);
}
""",
    "void byte_swap_message_header(unsigned short *header, int byte_order);",
)

L(
    0xE3DA0,
    "interface/ui_widget.c",
    "ui_widgets_active_for_local_player",
    """
/* ui_widgets_active_for_local_player (0xe3da0) — readable C lift. */
char ui_widgets_active_for_local_player(int16_t local_player_index)
{
  int *slot;
  void *widget;

  if (local_player_index < 0 || local_player_index >= 4) {
    display_assert((const char *)0x2832b0, (const char *)0x283280, 0x456, 1);
    system_exit(-1);
  }
  if (*(unsigned char *)0x46cc82 == 0)
    return 0;
  for (slot = (int *)0x46cc20; (unsigned)slot < 0x46cc30u; slot++) {
    widget = (void *)*slot;
    if (widget != 0 && *(int16_t *)((char *)widget + 8) == local_player_index)
      return 1;
  }
  return 0;
}
""",
    "char ui_widgets_active_for_local_player(int16_t local_player_index);",
)

L(
    0xE5A40,
    "interface/ui_widget.c",
    "main_screen_shell_begin_fade",
    """
/* main_screen_shell_begin_fade (0xe5a40) — readable C lift. */
void main_screen_shell_begin_fade(int fade_duration)
{
  int *slot;
  char *widget;
  void *rec;
  void *next;

  ui_widget_stop_attract_mode();
  for (slot = (int *)0x46cc20; (unsigned)slot < 0x46cc30u; slot++) {
    widget = (char *)*slot;
    if (widget == 0)
      continue;
    if (widget[0x15] != 0)
      continue;
    *(int *)(widget + 0x20) = fade_duration;
    *(int *)(widget + 0x1c) = *(int *)0x46cc40 - *(int *)(widget + 0x18) + 0x64;
    rec = (void *)slot[4];
    while (rec != 0) {
      next = *(void **)((char *)rec + 0xc);
      slot[4] = (int)next;
      stack_memory_pool_deallocate(*(void **)0x31e04c, rec);
      rec = (void *)slot[4];
    }
  }
}
""",
    "void main_screen_shell_begin_fade(int fade_duration);",
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
  int game;

  server = *(void **)0x46e8bc;
  if (server == 0)
    return (int)FUN_0012a890();
  game = network_game_server_get_game(server);
  if (game == 0) {
    display_assert((const char *)0x2861a8, (const char *)0x2955e0, 0x73, 1);
    system_exit(-1);
  }
  return *(int *)((char *)game + 0x428);
}
""",
    "int network_game_get_number_of_games_played(void);",
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
  int next;
  char *p;

  if (state == 0 || state[0] == 0 || state[1] < 0 || state[1] > state[2]) {
    display_assert((const char *)0x28f058, (const char *)0x28eef8, 0x100, 1);
    system_exit(-1);
  }
  cursor = state[1];
  next = cursor + 1;
  if (next > state[2] || *((unsigned char *)state + 0xc) != 0) {
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
  char *p;

  if (state == 0 || state[0] == 0 || state[1] < 0 || state[1] > state[2]) {
    display_assert((const char *)0x28f058, (const char *)0x28eef8, 0x100, 1);
    system_exit(-1);
  }
  cursor = state[1];
  if (cursor + 2 > state[2] || *((unsigned char *)state + 0xc) != 0) {
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
  char *p;

  if (state == 0 || state[0] == 0 || state[1] < 0 || state[1] > state[2]) {
    display_assert((const char *)0x28f058, (const char *)0x28eef8, 0x100, 1);
    system_exit(-1);
  }
  cursor = state[1];
  if (cursor + 4 > state[2] || *((unsigned char *)state + 0xc) != 0) {
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
    i = (short)(i + 1);
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
    0xD4D90,
    "interface/hud_messaging.c",
    "hud_set_state_message",
    """
/* hud_set_state_message (0xd4d90) — readable C lift. */
void hud_set_state_message(short param_1, short param_2)
{
  char *base;
  char *slot;
  int tag_handle;
  void *tag;
  void *elem;
  short msg;

  if (*(unsigned char *)(*(int *)0x46bd10 + 1) != 0)
    return;
  tag_handle = *(int *)(*(int *)0x46bd0c + 0xfc);
  if (tag_handle == -1)
    return;
  slot = (char *)(*(int *)0x46bd18 + (int)param_1 * 0x460);
  msg = param_2;
  if (msg != -1) {
    tag = tag_get(0x686d7420, tag_handle);
    if ((int)msg >= *(int *)((char *)tag + 0x20))
      msg = -1;
    else {
      elem = tag_block_get_element((char *)tag + 0x20, (int)msg, 0x40);
      *(void **)(slot + 0x454) = elem;
      slot[0x459] = 0;
      slot[0x458] = (msg != -1);
      return;
    }
  }
  slot[0x458] = (msg != -1);
}
""",
    "void hud_set_state_message(short param_1, short param_2);",
)

L(
    0xE59E0,
    "interface/ui_widget.c",
    "ui_widgets_pop_stack",
    """
/* ui_widgets_pop_stack (0xe59e0) — readable C lift. */
void ui_widgets_pop_stack(int16_t player_index)
{
  int idx;
  int *head;
  char record[12];

  idx = (int)player_index;
  if (player_index == -1)
    idx = 0;
  else if (player_index < 0 || player_index >= 4) {
    display_assert((const char *)0x282750, (const char *)0x283280, 0x4b4, 1);
    system_exit(-1);
  }
  head = (int *)(0x46cc30 + idx * 4);
  if (*head != 0)
    ui_widget_pending_load_pop(head, record);
}
""",
    "void ui_widgets_pop_stack(int16_t player_index);",
)


L(
    0x126700,
    "networking/network_client_manager.c",
    "network_game_client_new_advertised_game",
    """
/* network_game_client_new_advertised_game (0x126700) — readable C lift. */
void network_game_client_new_advertised_game(void *client, void *message)
{
  if (client == 0 || message == 0) {
    display_assert((const char *)0x291cd8, (const char *)0x291774, 0x2fc, 1);
    system_exit(-1);
  }
  FUN_00125ce0((char *)client + 4, message);
}
""",
    "void network_game_client_new_advertised_game(void *client, void *message);",
)

L(
    0xBBB80,
    "game/players.c",
    "player_teleport",
    """
/* player_teleport (0xbbb80) — readable C lift. */
char player_teleport(int player_handle, void *a, void *b)
{
  void *player;
  int unit_handle;
  void *unit;

  player = datum_get(*(void **)0x5aa6d4, player_handle);
  unit_handle = *(int *)((char *)player + 0x34);
  unit = object_try_and_get_and_verify_type(unit_handle, 1);
  if (unit == 0)
    return 0;
  if (*(int *)((char *)unit + 0xcc) != -1)
    unit_exit_seat_end(unit_handle);
  return FUN_000bb670(player_handle, a, b);
}
""",
    "char player_teleport(int player_handle, void *a, void *b);",
)

L(
    0xE4770,
    "interface/ui_widget.c",
    "ui_widget_pending_load_pop",
    """
/* ui_widget_pending_load_pop (0xe4770) — readable C lift. */
void ui_widget_pending_load_pop(int *head, void *record)
{
  int *node;
  int *dst;

  if (head == 0 || record == 0) {
    display_assert((const char *)0x283560, (const char *)0x283280, 0x9fc, 1);
    system_exit(-1);
  }
  node = (int *)*head;
  dst = (int *)record;
  dst[0] = node[0];
  dst[1] = node[1];
  dst[2] = node[2];
  *head = node[3];
  stack_memory_pool_deallocate(*(void **)0x31e04c, node);
}
""",
    "void ui_widget_pending_load_pop(int *head@<edi>, void *record@<esi>);",
)


L(
    0x126750,
    "networking/network_client_manager.c",
    "network_game_client_game_shutdown",
    """
/* network_game_client_game_shutdown (0x126750) — readable C lift. */
void network_game_client_game_shutdown(void *client)
{
  if (client == 0) {
    display_assert((const char *)0x2917a8, (const char *)0x291774, 0x3fc, 1);
    system_exit(-1);
    display_assert((const char *)0x2917a8, (const char *)0x291774, 0x662, 1);
    system_exit(-1);
  }
  if (*(short *)((char *)client + 0xca8) == 0)
    *(short *)((char *)client + 0xca8) = 8;
  network_game_log((const char *)0x292ad0);
  network_game_client_all_local_players_have_quit();
}
""",
    "void network_game_client_game_shutdown(void *client);",
)


L(
    0x124BA0,
    "networking/network_client_manager.c",
    "network_game_client_set_machine",
    """
/* network_game_client_set_machine (0x124ba0) — readable C lift. */
char network_game_client_set_machine(void *client, void *machine)
{
  unsigned short idx;
  char *dst;

  if (client == 0 || *(unsigned short *)client >= 4 || machine == 0) {
    display_assert((const char *)0x2918f8, (const char *)0x291774, 0x1e1, 1);
    system_exit(-1);
  }
  if (*(signed char *)((char *)machine + 0x40) < 0 ||
      *(signed char *)((char *)machine + 0x40) >= 4) {
    display_assert((const char *)0x2918f8, (const char *)0x291774, 0x1e1, 1);
    system_exit(-1);
  }
  idx = *(unsigned short *)client;
  dst = (char *)client + 0x970 + (int)idx * 0x44;
  csmemcpy(dst, machine, 0x44);
  return 1;
}
""",
    "char network_game_client_set_machine(void *client, void *machine);",
)

L(
    0xE4370,
    "interface/ui_widget.c",
    "widget_instance_set_visibility_recursive",
    """
/* widget_instance_set_visibility_recursive (0xe4370) — readable C lift. */
void widget_instance_set_visibility_recursive(void *widget, char visible)
{
  void *child;

  if (widget == 0) {
    display_assert((const char *)0x2832a8, (const char *)0x283280, 0x743, 1);
    system_exit(-1);
  }
  *((char *)widget + 0x10) = visible;
  child = *(void **)((char *)widget + 0x34);
  while (child != 0) {
    widget_instance_set_visibility_recursive(child, visible);
    child = *(void **)((char *)child + 0x2c);
  }
}
""",
    "void widget_instance_set_visibility_recursive(void *widget, char visible);",
)

L(
    0x11C4D0,
    "networking/network_messages.c",
    "FUN_0011c4d0",
    """
/* FUN_0011c4d0 (0x11c4d0) — readable C lift. */
void FUN_0011c4d0(int cache, void *pointer)
{
  int *block;
  void (*dispose_fn)(int);

  if (pointer == 0) {
    display_assert((const char *)0x267eec, (const char *)0x28f768, 0x11a, 1);
    system_exit(-1);
  }
  block = (int *)((char *)pointer - 0x10);
  FUN_0011c290(cache);
  FUN_0011c210(cache, (int)block);
  if ((block[1] & 2) == 0) {
    dispose_fn = *(void (**)(int))(cache + 0x34);
    dispose_fn(block[0]);
    block[1] = (block[1] & ~1) | 2;
  }
}
""",
    "void FUN_0011c4d0(int cache, void *pointer);",
)

L(
    0x124E20,
    "networking/network_client_manager.c",
    "network_game_client_game_out_of_sync",
    """
/* network_game_client_game_out_of_sync (0x124e20) — readable C lift. */
void network_game_client_game_out_of_sync(void *client)
{
  short player;

  if (*(unsigned char *)0x46e8b8 != 0)
    return;
  network_game_log((const char *)0x2919b4);
  if (*((unsigned char *)client + 0xcac) == 0) {
    player = local_player_get_next(-1);
    while (player != -1) {
      ui_widget_display_error(8, player, 1, 0);
      player = local_player_get_next(player);
    }
  }
  *((unsigned char *)client + 0xcac) = 1;
}
""",
    "void network_game_client_game_out_of_sync(void *client);",
)

L(
    0xE5AB0,
    "interface/ui_widget.c",
    "ui_play_audio_feedback_sound",
    """
/* ui_play_audio_feedback_sound (0xe5ab0) — readable C lift. */
void ui_play_audio_feedback_sound(int16_t sound_selector)
{
  int sel;
  const char *name;
  int tag;

  sel = (int)sound_selector - 1;
  if ((unsigned)sel > 3)
    return;
  if (sel == 0)
    name = (const char *)0x28380c;
  else if (sel == 1)
    name = (const char *)0x2837f4;
  else if (sel == 2)
    name = (const char *)0x2837e0;
  else
    name = (const char *)0x2837c4;
  tag = tag_loaded(0x736e6421, name);
  if (tag == -1)
    return;
  sound_impulse_start(tag, 1.0f);
}
""",
    "void ui_play_audio_feedback_sound(int16_t sound_selector);",
)


L(
    0xE9BD0,
    "interface/ui_widget.c",
    "ui_widget_event_handler_set_difficulty",
    """
/* ui_widget_event_handler_set_difficulty (0xe9bd0) — readable C lift. */
char ui_widget_event_handler_set_difficulty(void *widget, void *event_data, bool *widget_deleted)
{
  short difficulty;

  (void)event_data;
  (void)widget_deleted;
  difficulty = *(short *)((char *)widget + 0x3c);
  if (difficulty < 0 || difficulty >= 4) {
    display_assert((const char *)0x285ad8, (const char *)0x2859a4, 0x313, 1);
    system_exit(-1);
  }
  main_set_difficulty(difficulty);
  ui_play_audio_feedback_sound(2);
  return 1;
}
""",
    "char ui_widget_event_handler_set_difficulty(void *widget, void *event_data, bool *widget_deleted);",
)

L(
    0xF5290,
    "interface/ui_widget_text_search_and_replace_functions.c",
    "ui_widget_text_search_and_replace_function_invoke",
    """
/* ui_widget_text_search_and_replace_function_invoke (0xf5290) — readable C lift. */
wchar_t *ui_widget_text_search_and_replace_function_invoke(void *widget, unsigned short function_index)
{
  wchar_t *(*fn)(void *);

  if (widget == 0) {
    display_assert((const char *)0x2832a8, (const char *)0x28a748, 0x2d, 1);
    system_exit(-1);
  }
  if ((short)function_index < 0 || function_index >= 2)
    return (wchar_t *)0x28a730;
  fn = *(wchar_t *(**)(void *))(0x31e5a4 + (int)(short)function_index * 4);
  return fn(widget);
}
""",
    "wchar_t *ui_widget_text_search_and_replace_function_invoke(void *widget, unsigned short function_index);",
)

L(
    0x11C4D0,
    "networking/network_messages.c",
    "FUN_0011c4d0",
    """
/* FUN_0011c4d0 (0x11c4d0) — readable C lift. */
void FUN_0011c4d0(int cache, void *pointer)
{
  int *block;
  void (*dispose_fn)(int);

  if (pointer == 0) {
    display_assert((const char *)0x267eec, (const char *)0x28f768, 0x11a, 1);
    system_exit(-1);
  }
  block = (int *)((char *)pointer - 0x10);
  FUN_0011c290(cache);
  FUN_0011c210(cache, (int)block);
  if ((block[1] & 2) == 0) {
    dispose_fn = *(void (**)(int))(cache + 0x34);
    dispose_fn(block[0]);
    block[1] = (block[1] & ~1) | 2;
  }
}
""",
    "void FUN_0011c4d0(int cache, void *pointer);",
)


def audit_naked_true() -> list[tuple[str, str, str]]:
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    bad = []
    for o in kb.get("objects", []):
        src = o.get("source") or ""
        if not src:
            continue
        sp = ROOT / "src" / "halo" / src
        if not sp.exists():
            continue
        text = sp.read_text(encoding="utf-8", errors="ignore")
        for f in o.get("functions") or []:
            if f.get("ported") is not True:
                continue
            name = f.get("name") or ""
            addr = (f.get("addr") or "").lower()
            if not addr:
                continue
            pat = re.compile(
                rf"/\*[^*]*\b{re.escape(addr)}\b[^*]*\*/\s*#if defined\(__clang__\)\s*"
                rf"(?:static[\s\S]*?)?__attribute__\(\(naked[\s\S]*?#endif",
                re.I,
            )
            if pat.search(text):
                bad.append((name or "?", addr, src))
    return bad


def cast_stale(text: str, names: set[str]) -> str:
    for sym in names:
        text = re.sub(rf"(=\s*){re.escape(sym)}\s*;", rf"\1(void *){sym};", text)
    return text


def apply_one(addr: int) -> tuple[bool, str, str]:
    source, name, body, decl = LIFTS[addr]
    sp = ROOT / "src" / "halo" / source
    text = sp.read_text(encoding="utf-8", errors="replace")
    if re.search(rf"0x{addr:x}[^\n]*readable C lift", text, re.I):
        return False, "already", text
    span = find_naked_block(text, name, addr)
    if not span:
        return False, "locate", text
    chunk = text[span[0] : span[1]]
    if len(chunk.encode()) > 2500:
        return False, "too_big", text
    new_text = text[: span[0]] + body + "\n" + text[span[1] :]
    if "int16_t" in body and "#include <stdint.h>" not in new_text:
        new_text = "#include <stdint.h>\n" + new_text
    new_text = cast_stale(new_text, {name})
    # compile fix for network_game_globals pre-existing conflict
    if source.endswith("network_game_globals.c"):
        new_text = new_text.replace(
            "void network_player_reset(char *player)",
            "void network_player_reset(uint8_t *player)",
        )
    sp.write_text(new_text, encoding="utf-8")
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    for o in kb.get("objects", []):
        for fn in o.get("functions") or []:
            if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == addr:
                fn["decl"] = decl if decl.endswith(";") else decl + ";"
                if not fn.get("name"):
                    fn["name"] = name
    KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
    if not docker_compile(source):
        sp.write_text(text, encoding="utf-8")
        return False, "compile", text
    return True, "ok", text


def run_uni(name: str, addr: int, seeds: int = 100, timeout: float = 120.0) -> dict:
    outj = ROOT / "artifacts" / "equivalence" / f"uni_{addr:08x}_s{seeds}.json"
    outj.parent.mkdir(parents=True, exist_ok=True)
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
    env["BIPED_SIBLING_RESOLVE"] = "1"
    try:
        proc = subprocess.run(
            cmd, cwd=str(ROOT), capture_output=True, text=True, timeout=timeout, env=env
        )
    except subprocess.TimeoutExpired:
        return {"passed": 0, "failed": 0, "errors": 1, "tail": "TIMEOUT"}
    text = (proc.stdout or "") + (proc.stderr or "")
    m = re.search(r"(\d+) passed, (\d+) failed, (\d+) errors", text)
    passed = failed = errors = None
    if m:
        passed, failed, errors = map(int, m.groups())
    return {
        "passed": passed,
        "failed": failed,
        "errors": errors,
        "tail": text[-500:],
        "missing_candidate": "missing_build_object" in text,
    }


def commit_push(flips: list[str], touched: set[Path]) -> None:
    files = ["kb.json", "scripts/lift_grok_w4.py", "scripts/unicorn_c_campaign.py"]
    files += [str(p.relative_to(ROOT)) for p in sorted(touched)]
    files = list(dict.fromkeys(files))
    subprocess.run(["git", "add"] + files, cwd=ROOT, check=False)
    msg = f"lift(track-a): {len(flips)} Unicorn-prove leaves ({' '.join(flips[:8])}) (ported:true)."
    r = subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print("commit failed", r.stdout, r.stderr, flush=True)
        return
    subprocess.run(["git", "fetch", "pastudan", "track-a-collision-bsp"], cwd=ROOT, capture_output=True)
    rb = subprocess.run(
        ["git", "rebase", "pastudan/track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if rb.returncode != 0:
        print("rebase conflict", rb.stdout, rb.stderr, flush=True)
        subprocess.run(["git", "rebase", "--abort"], cwd=ROOT, capture_output=True)
        return
    bad = audit_naked_true()
    if bad:
        print("ABORT push naked-true", bad[:10], flush=True)
        return
    r = subprocess.run(
        ["git", "push", "pastudan", "HEAD:track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    print("PUSH", r.returncode, (r.stderr or r.stdout)[-400:], flush=True)


def main() -> int:
    order = [0xE9BD0]
    true0, _ = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    print(f"start true={true0} naked_true={len(audit_naked_true())}", flush=True)
    flips: list[str] = []
    touched: set[Path] = set()

    for addr in order:
        source, name, _b, _d = LIFTS[addr]
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        already = False
        for o in kb.get("objects", []):
            for fn in o.get("functions") or []:
                if fn.get("addr") and int(fn["addr"], 16) == addr and fn.get("ported") is True:
                    already = True
        if already:
            print(f"\n== {hex(addr)} {name} already true ==", flush=True)
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
        res = run_uni(name, addr)
        if not clear_pass(res, 100):
            res2 = run_uni(hex(addr), addr)
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
                "phase": "lift_grok_w4",
                "passed": res.get("passed"),
                "failed": res.get("failed"),
                "errors": res.get("errors"),
            }
        )
        if not okp:
            print(f"  REVERT {(res.get('tail') or '')[-180:]}", flush=True)
            (ROOT / "src" / "halo" / source).write_text(orig)
            continue
        # refuse if body still naked
        cur = (ROOT / "src" / "halo" / source).read_text(encoding="utf-8", errors="ignore")
        if re.search(
            rf"0x{addr:x}[^\n]*\*/\s*#if defined\(__clang__\)\s*(?:static[\s\S]*?)?__attribute__\(\(naked",
            cur,
            re.I,
        ):
            print("  REVERT still naked", flush=True)
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
        bad = audit_naked_true()
        print("pre-push naked_true", len(bad), bad[:5], flush=True)
        if bad:
            print("REFUSING commit: naked-true != 0", flush=True)
            return 2
        commit_push(flips, touched)
    true1, _ = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    print(
        f"DONE proven={len(flips)} true={true1} (+{true1 - true0}) naked_true={len(audit_naked_true())}",
        flush=True,
    )
    return 0 if len(flips) >= 1 else 1


if __name__ == "__main__":
    raise SystemExit(main())
