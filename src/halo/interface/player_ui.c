#include <stdint.h>
void player_ui_dispose(void)
{
  csmemset(player_ui_globals, 0, sizeof(player_ui_globals));
}

__int16
player_ui_get_single_player_local_player_controller(__int16 local_player_index)
{
  assert_halt_msg(local_player_index >= 0 && local_player_index < 4,
                  "invalid local player index");
  return word_46BFC4[(__int16)local_player_index];
}

void player_ui_remember_player1_profile(bool save)
{
  if (*(int *)0x30f02c != *(int *)0x46bf10) {
    if (*(int *)0x46bf10 == -1) {
      error(2, "player 1 has no active player profile assigned");
    } else {
      if (!((bool (*)(int, void *))0x1c1280)(*(int *)0x46bf10,
                                             (void *)0x46c110))
        error(2, "player 1 has no active player profile assigned");
    }
    *(int *)0x30f02c = *(int *)0x46bf10;
  }
  if (save && *(char *)0x46c110)
    ((void (*)(void *))0x1c2c50)((void *)0x46c110);
}

void player_ui_initialize(void)
{
  int i;
  char *profile;

  csmemset(player_ui_globals, 0, 0x230);
  for (i = 0; i < 4; i++) {
    profile = player_ui_globals + i * 0x38;
    assert_halt(profile != NULL);
    csmemset(profile, 0, 0x30);
    *(int16_t *)(profile + 0x18) = -1;
    *(char *)(profile + 0x28) = 0;
    *(char *)(profile + 0x29) = 0;
    *(int *)(profile + 0x30) = -1;
    word_46BFC4[i] = -1;
  }
  *(int *)0x46c038 = -1;
  *(char *)0x46c10c = 1;
}
/* --- player_ui.obj batch drafts (2026-07-26) --- */

/* FUN_000e0620 (0xe0620) — readable C lift from XBE leaf. */
void FUN_000e0620(int a0, int a1, float *cursor_xy)
{
  char *sprite;
  int16_t si, ax, cx, dx;
  int16_t rect[4];
  (void)a0;
  (void)a1;

  if (*(unsigned char *)0x46beb0 == 0)
    return;

  *(int *)0x46bec4 = *(int *)cursor_xy;
  *(int *)0x46bec8 = *(int *)(cursor_xy + 1);
  sprite = *(char **)0x46bed8;
  si = (int16_t)((int)cursor_xy[0] >> 1);
  si = (int16_t)(si - *(int16_t *)(sprite + 0x10));
  ax = (int16_t)((int)cursor_xy[1] >> 1);
  ax = (int16_t)(ax - *(int16_t *)(sprite + 0x12));
  cx = (int16_t)(*(int16_t *)0x46beb8 + si);
  dx = (int16_t)(*(int16_t *)0x46beb6 + ax);
  *(int16_t *)0x46bece = ax;
  ax = (int16_t)(ax + *(int16_t *)0x46beb2);
  *(int16_t *)0x46becc = si;
  si = (int16_t)(si + *(int16_t *)0x46beb4);
  rect[0] = ax;          /* ebp-8 */
  rect[1] = si;          /* ebp-6 */
  rect[2] = cx;          /* ebp-2 — NOTE packing: word layout */
  rect[3] = dx;          /* ebp-4 */

  /* Match MSVC stack layout: [ebp-8]=ax, [ebp-6]=si, [ebp-4]=dx, [ebp-2]=cx as two dwords */
  {
    int dword_lo = (uint16_t)ax | ((uint16_t)si << 16);
    int dword_hi = (uint16_t)dx | ((uint16_t)cx << 16);
    if (*(unsigned char *)0x46beba != 0) {
      if (local_time_get() - *(int *)0x46bed0 <= 7)
        return;
    }
    *(int *)0x46bebc = dword_lo;
    *(int *)0x46bec0 = dword_hi;
    *(int *)0x46bed0 = local_time_get();
    *(unsigned char *)0x46bebb = 0;
  }
}

/* player_ui_reset_single_player_local_player_controllers (0xe0720) — readable C lift. */
void player_ui_reset_single_player_local_player_controllers(void)
{
  csmemset((void *)0x46bfc4, -1, 8);
}

/* player_ui_set_single_player_local_player_controller (0xe0740) — readable C lift. */
void player_ui_set_single_player_local_player_controller(
    int16_t local_player_index, int16_t controller_index)
{
  extern char DAT_00282708[];
  extern char DAT_00282724[];
  extern char DAT_002826ec[];
  if ((int16_t)local_player_index < 0 || (int16_t)local_player_index >= 4) {
    display_assert(DAT_00282708, DAT_00282724, 0x77, 1);
    system_exit(-1);
  }
  if ((int16_t)controller_index < 0 || (int16_t)controller_index >= 4) {
    display_assert(DAT_002826ec, DAT_00282724, 0x79, 1);
    system_exit(-1);
  }
  *(int16_t *)(0x46bfc4 + (int16_t)local_player_index * 2) = controller_index;
}

/* player_ui_get_single_player_local_player_from_controller (0xe0810) — readable C lift. */
int player_ui_get_single_player_local_player_from_controller(short local_player_index)
{
  short i;
  for (i = 0; i < 4; i++) {
    if (*(short *)(0x46bfc4 + (int)i * 2) == local_player_index) return i;
  }
  return -1;
}

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

uint8_t player_ui_local_player_wants_to_play_multiplayer(int16_t local_player_index)
{
  if ((int16_t)local_player_index < 0 || (int16_t)local_player_index >= 4) {
    display_assert((const char *)0x282750, (const char *)0x282724, 0xa7, 1);
    system_exit(-1);
  }
  return *(uint8_t *)(0x46bf14 + (int)(int16_t)local_player_index * 0x38);
}

void player_ui_clear_multiplayer_autojoin_for_local_player(int16_t local_player_index)
{
  if ((int16_t)local_player_index < 0 || (int16_t)local_player_index >= 4) {
    display_assert((const char *)0x282750, (const char *)0x282724, 0xaf, 1);
    system_exit(-1);
  }
  *(uint8_t *)(0x46bf14 + (int)(int16_t)local_player_index * 0x38) = (uint8_t)0;
}

/* player_ui_autojoin_players_to_next_multiplayer_game (0xe0930) — readable C lift. */
void player_ui_autojoin_players_to_next_multiplayer_game(void)
{
  *(char *)0x46bf14 = *(char *)0x46bfc0;
  *(char *)0x46bf4c = *(char *)0x46bfc1;
  *(char *)0x46bf84 = *(char *)0x46bfc2;
  *(char *)0x46bfbc = *(char *)0x46bfc3;
}

/* player_ui_clear_multiplayer_variant (0xe0960) — readable C lift. */
void player_ui_clear_multiplayer_variant(void)
{
  *(unsigned char *)0x46c034 = 0;
  set_game_connection(0);
  game_engine_dispose();
  game_set_game_variant(0);
}

/* player_ui_get_active_player_profile (0xe0980) — readable C lift. */
void player_ui_get_active_player_profile(int16_t local_player_index, void *out_profile)
{
  extern char DAT_002827a0[];
  extern char DAT_00282724[];
  if ((int16_t)local_player_index < 0 || (int16_t)local_player_index >= 4 || !out_profile) {
    display_assert(DAT_002827a0, DAT_00282724, 0xee, 1);
    system_exit(-1);
  }
  csmemcpy(out_profile, (void *)(0x46bee0 + (int16_t)local_player_index * 0x38), 0x30);
}

/* player_ui_get_active_player_profile_index (0xe09e0) — readable C lift. */
int player_ui_get_active_player_profile_index(short local_player_index)
{
  if (local_player_index < 0 || local_player_index >= 4) return 0;
  return *(int *)(0x46bf10 + (int)local_player_index * 0x38);
}

/* player_ui_get_last_single_player_level_played (0xe0a10) — readable C lift. */
int16_t player_ui_get_last_single_player_level_played(int16_t local_player_index)
{
  if ((int16_t)local_player_index < 0 || (int16_t)local_player_index >= 4) {
    display_assert((const char *)0x282750, (const char *)0x282724, 0x109, 1);
    system_exit(-1);
  }
  return *(int16_t *)(0x46bf06 + (int16_t)local_player_index * 0x38);
}

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

/* player_ui_autolevel_enabled (0xe0b50) — readable C lift. */
char player_ui_autolevel_enabled(int16_t controller_index)
{
  int16_t idx;
  int16_t i;
  int found;
  idx = controller_index;
  if (idx < 0 || idx >= 4) {
    display_assert((const char *)0x281054, (const char *)0x282724, 0x140, 1);
    system_exit(-1);
  }
  if (!network_game_in_progress()) {
    found = -1;
    for (i = 0; i < 4; i++) {
      if (*(int16_t *)(0x46bfc4 + i * 2) == idx) {
        found = i;
        break;
      }
    }
    idx = (int16_t)found;
  }
  if (idx == -1)
    return 0;
  if (idx < 0 || idx >= 4) {
    display_assert((const char *)0x282750, (const char *)0x282724, 0x154, 1);
    system_exit(-1);
  }
  return *(char *)(0x46bf0e + (int)idx * 0x38);
}

/* player_ui_get_path_to_local_player_profile_directory (0xe0bf0) — readable C lift. */
char player_ui_get_path_to_local_player_profile_directory(int16_t local_player_index, void *out_path)
{
  if ((int16_t)local_player_index < 0 || (int16_t)local_player_index >= 4)
    return 0;
  return (char)FUN_001c1280(*(int *)(0x46bf10 + (int16_t)local_player_index * 0x38), out_path);
}

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

/* player_ui_fast_setup_network_server (0xe0cd0) — readable C lift. */
void player_ui_fast_setup_network_server(void)
{
  void *widget;

  ui_widgets_close_all();
  dispose_global_network_game_client();
  dispose_global_network_game_server();
  set_game_connection(0);
  main_set_multiplayer_map_name((const char *)0x25386f);
  *(char *)0x46c034 = 0;
  widget = ui_widget_load_by_name_or_tag(
      (const char *)0x2828e0, -1, 0, -1, -1, -1, -1);
  if (widget == 0) {
    return;
  }
  game_engine_playlist_initialize();
  network_game_set_accept_remote_connections(1);
  if (!FUN_0012a890()) {
    return;
  }
  if (!FUN_0012a250()) {
    return;
  }
  game_engine_playlist_begin();
  set_game_connection(2);
}
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

/* player_ui_edit_profile_name_is_dirty (0xe0dd0) — readable C lift. */
char player_ui_edit_profile_name_is_dirty(void)
{
  int idx;
  unsigned int t;
  idx = *(int *)0x46c038;
  if (idx == -1) {
    error(2, (const char *)0x282964);
    return 0;
  }
  t = (unsigned short)saved_game_file_get_type(idx);
  if (t != 0 && t != 1) {
    error(2, (const char *)0x282938);
    return 0;
  }
  if (ustrncmp((const wchar_t *)0x46c03c, (const wchar_t *)0x46c0a4, 0xc) == 0)
    return 0;
  return 1;
}

/* player_ui_prompt_user_to_rename_edit_profile (0xe0e40) — readable C lift. */
char player_ui_prompt_user_to_rename_edit_profile(void)
{
  int idx;
  unsigned int t;
  idx = *(int *)0x46c038;
  if (idx == -1) {
    error(2, (const char *)0x282964);
    return 0;
  }
  t = (unsigned short)saved_game_file_get_type(idx);
  if (t != 0 && t != 1) {
    error(2, (const char *)0x282938);
    return 0;
  }
  return (char)virtual_keyboard_set_validation((wchar_t *)0x46c03c, 0x18, 0xa);
}

/* player_ui_get_edit_player_profile (0xe0ea0) — readable C lift. */
void *player_ui_get_edit_player_profile(void)
{
  short t = (short)saved_game_file_get_type(*(int *)0x46c038);
  /* neg/sbb/not/and: return buffer iff type == 0 */
  return t == 0 ? (void *)0x46c03c : (void *)0;
}

/* player_ui_get_edit_playlist_profile (0xe0ec0) — readable C lift. */
void *player_ui_get_edit_playlist_profile(void)
{
  short t = (short)saved_game_file_get_type(*(int *)0x46c038);
  /* return buffer iff type == 1 */
  return t == 1 ? (void *)0x46c03c : (void *)0;
}

/* player_ui_edit_profile_is_dirty (0xe0ee0) — readable C lift. */
char player_ui_edit_profile_is_dirty(void)
{
  int handle;
  int type;
  char dirty;
  int16_t save_a;
  int16_t save_b;
  int16_t save_c;
  int16_t save_d;

  dirty = 0;
  handle = *(int *)0x46c038;
  if (handle == -1) {
    return dirty;
  }
  type = (int)(uint16_t)saved_game_file_get_type(handle);
  if (type == 0) {
    save_c = *(int16_t *)0x46c0be;
    save_d = *(int16_t *)0x46c056;
    *(int16_t *)0x46c0be = 0;
    *(int16_t *)0x46c056 = 0;
    if (csmemcmp((void *)0x46c0a4, (void *)0x46c03c, 0x30) != 0) {
      dirty = 1;
    }
    *(int16_t *)0x46c056 = save_d;
    *(int16_t *)0x46c0be = save_c;
    return dirty;
  }
  if (type == 1) {
    save_a = *(int16_t *)0x46c108;
    save_b = *(int16_t *)0x46c0a0;
    *(int16_t *)0x46c108 = 0;
    *(int16_t *)0x46c0a0 = 0;
    if (csmemcmp((void *)0x46c0a4, (void *)0x46c03c, 0x68) != 0) {
      dirty = 1;
    }
    *(int16_t *)0x46c0a0 = save_b;
    *(int16_t *)0x46c108 = save_a;
    return dirty;
  }
  error(2, (const char *)0x28298c);
  return 0;
}
/* player_ui_activate_all_solo_levels (0xe0fd0) — readable C lift. */
void player_ui_activate_all_solo_levels(void)
{
  int i;
  for (i = 0; i < 10; i++)
    *(unsigned char *)(0x46befc + i) |= 0xf;
  if (*(int *)0x46bf10 != -1)
    player_profile_get_from_path(*(int *)0x46bf10, (void *)0x46bee0);
}

/* FUN_000e1000 (0xe1000) — readable C lift. */
void FUN_000e1000(void)
{
  data_iter_t iter;
  void *entry;
  short idx;
  data_iterator_new(&iter, *(data_t **)0x5aa6d4);
  for (entry = data_iterator_next(&iter); entry; entry = data_iterator_next(&iter)) {
    idx = *(short *)((char *)entry + 2);
    if (idx != -1)
      hud_print_message(idx, 0);
  }
}

/* 0xe1050 */
int player0_look_pitch_is_inverted(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* FUN_000e1060 (0xe1060) — readable C lift. */
int FUN_000e1060(void)
{
  unsigned char v = *(unsigned char *)0x46bf09;
  if (v == 0 || v == 1)
    return 1;
  return 0;
}

/* FUN_000e10c0 (0xe10c0) — readable C lift (restored pre-naked). */
void FUN_000e10c0(void)
{
  int ebx = 0;
  int ecx = 0;
  int edi = 0;

  /* cmp (int16_t)edi, 4 -> jl 0xe1199 */
  display_assert((char *)0x00282750, (char *)0x00282724, 914, 0);
  system_exit(0);
  /* cmp ecx, ebx -> jge 0xe11b3 */
  /* cmp ecx, ebx -> jge 0xe11c7 */
  /* cmp ecx, 9 -> jle 0xe11d1 */
  /* cmp ecx, 4 -> ja 0xe127b */
  ((void(*)(void))input_abstraction_update_local_player_preferences)();
  ((void(*)(void))input_abstraction_update_local_player_preferences)();

  (void)ebx;
  (void)ecx;
  (void)edi;
}



/* player_ui_clear_multiplayer_joins (0xe13f0) — readable C lift. */
void player_ui_clear_multiplayer_joins(void)
{
  int i;
  char *slot;
  char *joined;
  joined = (char *)0x46bf14;
  for (i = 0; i < 4; i++) {
    slot = (char *)0x46bee0 + i * 0x38;
    if (!slot) {
      display_assert((const char *)0x2829b0, (const char *)0x282724, 0x365, 1);
      system_exit(-1);
    }
    csmemset(slot, 0, 0x30);
    *(short *)(slot + 0x18) = -1;
    slot[0x28] = 0;
    slot[0x29] = 0;
    *(short *)(0x46bfc4 + i * 2) = -1;
    *(int *)(0x46bf10 + i * 0x38) = -1;
    joined[i * 0x38] = 0;
    *(char *)(0x46bfc0 + i) = 0;
  }
}

/* player_ui_set_active_player_profile (0xe1490) — readable C lift. */
void player_ui_set_active_player_profile(int16_t local_player_index, int profile_handle, void *profile)
{
  extern char DAT_002827a0[];
  extern char DAT_00282724[];
  if ((int16_t)local_player_index < 0 || (int16_t)local_player_index >= 4 || !profile) {
    display_assert(DAT_002827a0, DAT_00282724, 0xe2, 1);
    system_exit(-1);
  }
  *(int *)(0x46bf10 + (int16_t)local_player_index * 0x38) = profile_handle;
  csmemcpy((void *)(0x46bee0 + (int16_t)local_player_index * 0x38), profile, 0x30);
  FUN_000e10c0();
}

/* player_ui_begin_editing_profile (0xe1500) — readable C lift. */
void player_ui_begin_editing_profile(int profile_index)
{
  unsigned short typ;
  char ok;

  *(int *)0x46c038 = -1;
  typ = (unsigned short)saved_game_file_get_type(profile_index);
  if (typ == 0) {
    ok = player_profile_new(profile_index, (void *)0x46c0a4);
    if (ok) {
      csmemcpy((void *)0x46c03c, (void *)0x46c0a4, 0x30u);
      *(int *)0x46c038 = profile_index;
    } else {
      error(2, (const char *)0x2829b8, profile_index);
    }
  } else if (typ == 1) {
    ok = playlist_profile_delete(profile_index, (void *)0x46c0a4);
    if (ok) {
      csmemcpy((void *)0x46c03c, (void *)0x46c0a4, 0x68u);
      *(int *)0x46c038 = profile_index;
    } else {
      error(2, (const char *)0x2829f0, profile_index);
    }
  } else {
    error(2, (const char *)0x282a28, profile_index);
  }
}

/* player_ui_save_profile (0xe15b0) — readable C lift (restored pre-naked). */
void player_ui_save_profile(void)
{
  int eax = 0;
  int esi = 0;

  ((void(*)(void))saved_game_file_get_type)();
  error(0, (char *)0x00282b40);
  player_ui_edit_profile_is_dirty();
  /* test (char)eax, (char)eax -> jne 0xe1603 */
  error(0, (char *)0x00282af8);
  /* test eax, 0x40000000 -> je 0xe16b2 */
  ustrncmp((wchar_t *)0x0046c03c, (wchar_t *)0x0046c0a4, 12);
  /* test eax, eax -> je 0xe16a1 */
  ((void(*)(void))FUN_001c1e20)();
  /* cmp esi, -1 -> je 0xe1690 */
  ((void(*)(void))playlist_profile_get_display_name)();
  /* mem[0x0046c038] = esi */
  ((void(*)(void))FUN_001c4da0)();
  /* test (char)eax, (char)eax -> je 0xe167c */
  ((void(*)(void))saved_game_file_remember_last_used_multiplayer_variant_directory)();
  /* mem[0x0046c038] = 0xffffffff */
  error(0, (char *)0x00282acc);
  error(0, (char *)0x00282a80);
  ((void(*)(void))playlist_profile_get_display_name)();
  ((void(*)(void))FUN_001c4da0)();
  /* test (char)eax, (char)eax -> je 0xe167c */
  ((void(*)(void))saved_game_file_remember_last_used_multiplayer_variant_directory)();
  /* mem[0x0046c038] = 0xffffffff */
  /* relift: test dword ptr [0x46c038], 0x40000000 -> je 0xe1715 */
  error(0, (char *)0x00282a48);
  player_ui_edit_profile_is_dirty();
  /* test (char)eax, (char)eax -> jne 0xe172d */
  error(0, (char *)0x00282af8);
  ((void(*)(void))player_profile_get_from_path)();
  /* mem[0x0046c038] = 0xffffffff */

  (void)eax;
  (void)esi;
}



/* 0xe1760 */
void player_ui_end_editing_profile(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_000e1770 (0xe1770) — readable C lift. */
void FUN_000e1770(int flag)
{
  *(unsigned char *)0x46bf0b = (unsigned char)flag;
  if (*(int *)0x46bf10 != -1) {
    FUN_000e1000();
    player_profile_get_from_path(*(int *)0x46bf10, (void *)0x46bee0);
  }
  FUN_000e10c0();
}

