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

/* FUN_000e0620 (0xe0620) — XBE naked draft (batch 144). */
#if defined(__clang__)
static void (*const be0620_ftol)(void) = FUN_001d9068;
static int (*const be0620_cb5b20)(void) = local_time_get;

__attribute__((naked, noinline))
void FUN_000e0620(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movb 0x46beb0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000e0620_2\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, 0x46bec4\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x46bec8\n\t"
      "flds (%%edi)\n\t"
      "call *%[ftol]\n\t"
      "flds 0x4(%%edi)\n\t"
      "movl 0x46bed8, %%ebx\n\t"
      "movw %%ax, %%si\n\t"
      "sarw $1, %%si\n\t"
      "subw 0x10(%%ebx), %%si\n\t"
      "movw %%si, -0x6(%%ebp)\n\t"
      "call *%[ftol]\n\t"
      "movl -0x6(%%ebp), %%edx\n\t"
      "movl 0x46beb8, %%ecx\n\t"
      "sarw $1, %%ax\n\t"
      "subw 0x12(%%ebx), %%ax\n\t"
      "addl %%edx, %%ecx\n\t"
      "movw 0x46beb6, %%dx\n\t"
      "addw %%ax, %%dx\n\t"
      "movw %%ax, 0x46bece\n\t"
      "addw 0x46beb2, %%ax\n\t"
      "movw %%si, 0x46becc\n\t"
      "addw 0x46beb4, %%si\n\t"
      "popl %%edi\n\t"
      "movw %%ax, -0x8(%%ebp)\n\t"
      "movb 0x46beba, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movw %%si, -0x6(%%ebp)\n\t"
      "popl %%esi\n\t"
      "movw %%cx, -0x2(%%ebp)\n\t"
      "movw %%dx, -0x4(%%ebp)\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_000e0620_1\n\t"
      "call *%[cb5b20]\n\t"
      "subl 0x46bed0, %%eax\n\t"
      "cmpl $7, %%eax\n\t"
      "jle .LFUN_000e0620_2\n\t"
      ".LFUN_000e0620_1:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x46bebc\n\t"
      "movl %%ecx, 0x46bec0\n\t"
      "call *%[cb5b20]\n\t"
      "movl %%eax, 0x46bed0\n\t"
      "movb $0, 0x46bebb\n\t"
      ".LFUN_000e0620_2:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [ftol] "m"(be0620_ftol), [cb5b20] "m"(be0620_cb5b20)
      : "memory");
}
#else
#error "FUN_000e0620: clang naked draft required"
#endif


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

/* player_ui_fast_setup_network_server (0xe0cd0) — XBE naked draft (batch 240). */
#if defined(__clang__)
static void (*const be0cd0_ce58c0)(void) = ui_widgets_close_all;
static void (*const be0cd0_c12a1e0)(void) = dispose_global_network_game_client;
static void (*const be0cd0_c12a2a0)(void) = dispose_global_network_game_server;
static void (*const be0cd0_cfff70)(short param) = set_game_connection;
static void (*const be0cd0_c100010)(const char *name) = main_set_multiplayer_map_name;
static void * (*const be0cd0_ce84e0)(const char *name, int tag_index, int is_child, int widget_stack, int parent_tag_index, int a6, int a7) = ui_widget_load_by_name_or_tag;
static void (*const be0cd0_cae750)(void) = game_engine_playlist_initialize;
static void (*const be0cd0_c12a150)(char accept) = network_game_set_accept_remote_connections;
static bool (*const be0cd0_c12a890)(void) = FUN_0012a890;
static bool (*const be0cd0_c12a250)(void) = FUN_0012a250;
static void (*const be0cd0_ca8a70)(void) = game_engine_playlist_begin;
static void (*const be0cd0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const be0cd0_c100620)(void) = main_goto_main_menu;

__attribute__((naked, noinline))
void player_ui_fast_setup_network_server(void)
{
  __asm__ volatile(
      "call *%[ce58c0]\n\t"
      "call *%[c12a1e0]\n\t"
      "call *%[c12a2a0]\n\t"
      "pushl $0\n\t"
      "call *%[cfff70]\n\t"
      "pushl $0x25386f\n\t"
      "call *%[c100010]\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $0x2828e0\n\t"
      "movb $0, 0x46c034\n\t"
      "call *%[ce84e0]\n\t"
      "addl $0x24, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lplayer_ui_fast_setup_network_server_2\n\t"
      "call *%[cae750]\n\t"
      "pushl $1\n\t"
      "call *%[c12a150]\n\t"
      "addl $4, %%esp\n\t"
      "call *%[c12a890]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_ui_fast_setup_network_server_1\n\t"
      "call *%[c12a250]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_ui_fast_setup_network_server_1\n\t"
      "call *%[ca8a70]\n\t"
      "pushl $2\n\t"
      "call *%[cfff70]\n\t"
      "addl $4, %%esp\n\t"
      "ret\n\t"
      ".Lplayer_ui_fast_setup_network_server_1:\n\t"
      "call *%[c12a1e0]\n\t"
      "call *%[c12a2a0]\n\t"
      "pushl $0\n\t"
      "call *%[c12a150]\n\t"
      "pushl $0x2828ac\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp *%[c100620]\n\t"
      ".Lplayer_ui_fast_setup_network_server_2:\n\t"
      "pushl $0x282840\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp *%[c100620]\n\t"
      :
      : [ce58c0] "m"(be0cd0_ce58c0), [c12a1e0] "m"(be0cd0_c12a1e0), [c12a2a0] "m"(be0cd0_c12a2a0), [cfff70] "m"(be0cd0_cfff70), [c100010] "m"(be0cd0_c100010), [ce84e0] "m"(be0cd0_ce84e0), [cae750] "m"(be0cd0_cae750), [c12a150] "m"(be0cd0_c12a150), [c12a890] "m"(be0cd0_c12a890), [c12a250] "m"(be0cd0_c12a250), [ca8a70] "m"(be0cd0_ca8a70), [c8f390] "m"(be0cd0_c8f390), [c100620] "m"(be0cd0_c100620)
      : "memory");
}
#else
#error "player_ui_fast_setup_network_server: clang naked draft required"
#endif


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

/* player_ui_edit_profile_is_dirty (0xe0ee0) — XBE naked draft (batch 137). */
#if defined(__clang__)
static void (*const be0ee0_c1c29a0)(void) = (void *)saved_game_file_get_type;
static void (*const be0ee0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static int (*const be0ee0_c8da40)(const void *a, const void *b, int size) = csmemcmp;

__attribute__((naked, noinline))
void player_ui_edit_profile_is_dirty(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x46c038, %%eax\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lplayer_ui_edit_profile_is_dirty_5\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c29a0]\n\t"
      "movzwl %%ax, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "subl %%ebx, %%eax\n\t"
      "je .Lplayer_ui_edit_profile_is_dirty_3\n\t"
      "decl %%eax\n\t"
      "je .Lplayer_ui_edit_profile_is_dirty_1\n\t"
      "pushl $0x28298c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_ui_edit_profile_is_dirty_1:\n\t"
      "movl 0x46c108, %%eax\n\t"
      "movl 0x46c0a0, %%ecx\n\t"
      "pushl $0x68\n\t"
      "pushl $0x46c03c\n\t"
      "pushl $0x46c0a4\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movw %%bx, 0x46c108\n\t"
      "movw %%bx, 0x46c0a0\n\t"
      "call *%[c8da40]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lplayer_ui_edit_profile_is_dirty_2\n\t"
      "movb $1, %%bl\n\t"
      ".Lplayer_ui_edit_profile_is_dirty_2:\n\t"
      "movw -0x8(%%ebp), %%ax\n\t"
      "movw -0x4(%%ebp), %%dx\n\t"
      "movw %%ax, 0x46c0a0\n\t"
      "movb %%bl, %%al\n\t"
      "movw %%dx, 0x46c108\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_ui_edit_profile_is_dirty_3:\n\t"
      "pushl %%esi\n\t"
      "movw 0x46c0be, %%si\n\t"
      "pushl %%edi\n\t"
      "movw 0x46c056, %%di\n\t"
      "pushl $0x30\n\t"
      "pushl $0x46c03c\n\t"
      "pushl $0x46c0a4\n\t"
      "movw %%bx, 0x46c0be\n\t"
      "movw %%bx, 0x46c056\n\t"
      "call *%[c8da40]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lplayer_ui_edit_profile_is_dirty_4\n\t"
      "movb $1, %%bl\n\t"
      ".Lplayer_ui_edit_profile_is_dirty_4:\n\t"
      "movw %%di, 0x46c056\n\t"
      "popl %%edi\n\t"
      "movw %%si, 0x46c0be\n\t"
      "popl %%esi\n\t"
      ".Lplayer_ui_edit_profile_is_dirty_5:\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1c29a0] "m"(be0ee0_c1c29a0), [c8f390] "m"(be0ee0_c8f390), [c8da40] "m"(be0ee0_c8da40)
      : "memory");
}
#else
#error "player_ui_edit_profile_is_dirty: clang naked draft required"
#endif


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

/* FUN_000e10c0 (0xe10c0) — XBE naked draft (batch 118). */
#if defined(__clang__)
static void (*const be10c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const be10c0_exitfn)(int) = system_exit;
static void (*const be10c0_cce740)(void) = (void *)0xce740;

__attribute__((naked, noinline))
void FUN_000e10c0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x68, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpw %%bx, %%di\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl $0x42200000, -0x40(%%ebp)\n\t"
      "movl $0x42480000, -0x3c(%%ebp)\n\t"
      "movl $0x42700000, -0x38(%%ebp)\n\t"
      "movl $0x428c0000, -0x34(%%ebp)\n\t"
      "movl $0x42a00000, -0x30(%%ebp)\n\t"
      "movl $0x42b40000, -0x2c(%%ebp)\n\t"
      "movl $0x42c80000, -0x28(%%ebp)\n\t"
      "movl $0x42dc0000, -0x24(%%ebp)\n\t"
      "movl $0x42f00000, -0x20(%%ebp)\n\t"
      "movl $0x43020000, -0x1c(%%ebp)\n\t"
      "movl $0x42a00000, -0x68(%%ebp)\n\t"
      "movl $0x42c80000, -0x64(%%ebp)\n\t"
      "movl $0x42f00000, -0x60(%%ebp)\n\t"
      "movl $0x430c0000, -0x5c(%%ebp)\n\t"
      "movl $0x43200000, -0x58(%%ebp)\n\t"
      "movl $0x43340000, -0x54(%%ebp)\n\t"
      "movl $0x43480000, -0x50(%%ebp)\n\t"
      "movl $0x435c0000, -0x4c(%%ebp)\n\t"
      "movl $0x43700000, -0x48(%%ebp)\n\t"
      "movl $0x43820000, -0x44(%%ebp)\n\t"
      "jl .LFUN_000e10c0_1\n\t"
      "cmpw $4, %%di\n\t"
      "jl .LFUN_000e10c0_2\n\t"
      ".LFUN_000e10c0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x392\n\t"
      "pushl $0x282724\n\t"
      "pushl $0x282750\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000e10c0_2:\n\t"
      "movswl %%di, %%esi\n\t"
      "movl %%esi, %%eax\n\t"
      "imull $0x38, %%eax, %%eax\n\t"
      "addl $0x46bf08, %%eax\n\t"
      "movzbl 0x2(%%eax), %%ecx\n\t"
      "decl %%ecx\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "jge .LFUN_000e10c0_3\n\t"
      "xorl %%edx, %%edx\n\t"
      "jmp .LFUN_000e10c0_4\n\t"
      ".LFUN_000e10c0_3:\n\t"
      "cmpl $9, %%ecx\n\t"
      "movl $9, %%edx\n\t"
      "jg .LFUN_000e10c0_4\n\t"
      "movl %%ecx, %%edx\n\t"
      ".LFUN_000e10c0_4:\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "jge .LFUN_000e10c0_5\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "jmp .LFUN_000e10c0_6\n\t"
      ".LFUN_000e10c0_5:\n\t"
      "cmpl $9, %%ecx\n\t"
      "jle .LFUN_000e10c0_6\n\t"
      "movl $9, %%ecx\n\t"
      ".LFUN_000e10c0_6:\n\t"
      "movswl %%dx, %%edx\n\t"
      "movswl %%cx, %%ecx\n\t"
      "flds -0x40(%%ebp,%%edx,4)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "movl $3, %%edx\n\t"
      "flds -0x68(%%ebp,%%ecx,4)\n\t"
      "movb 0x1(%%eax), %%cl\n\t"
      "cmpb %%dl, %%cl\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "jbe .LFUN_000e10c0_7\n\t"
      "movw %%dx, -0x4(%%ebp)\n\t"
      "jmp .LFUN_000e10c0_8\n\t"
      ".LFUN_000e10c0_7:\n\t"
      "movzbw %%cl, %%cx\n\t"
      "movw %%cx, -0x4(%%ebp)\n\t"
      ".LFUN_000e10c0_8:\n\t"
      "movzbl (%%eax), %%ecx\n\t"
      "cmpl $4, %%ecx\n\t"
      "ja .LFUN_000e10c0_18\n\t"
      "jmp *.LFUN_000e10c0_jt(,%%ecx,4)\n\t"
      ".LFUN_000e10c0_9:\n\t"
      "movb $1, -0xc(%%ebp)\n\t"
      "movb $0xf, -0x5(%%ebp)\n\t"
      "jmp .LFUN_000e10c0_14\n\t"
      ".LFUN_000e10c0_10:\n\t"
      "movb $1, -0xc(%%ebp)\n\t"
      "movb $7, -0xa(%%ebp)\n\t"
      "movb $6, -0x9(%%ebp)\n\t"
      "movb $0xf, -0x5(%%ebp)\n\t"
      "jmp .LFUN_000e10c0_16\n\t"
      ".LFUN_000e10c0_11:\n\t"
      "movb $6, -0x10(%%ebp)\n\t"
      "movb $1, -0xc(%%ebp)\n\t"
      "movb %%bl, -0xa(%%ebp)\n\t"
      "movb $7, -0x9(%%ebp)\n\t"
      "movb $0xf, -0x5(%%ebp)\n\t"
      "jmp .LFUN_000e10c0_17\n\t"
      ".LFUN_000e10c0_12:\n\t"
      "movb $6, -0xc(%%ebp)\n\t"
      "movb $1, -0xa(%%ebp)\n\t"
      "movb $0xf, -0x5(%%ebp)\n\t"
      "jmp .LFUN_000e10c0_15\n\t"
      ".LFUN_000e10c0_13:\n\t"
      "movb $0xf, -0xc(%%ebp)\n\t"
      "movb $1, -0x5(%%ebp)\n\t"
      ".LFUN_000e10c0_14:\n\t"
      "movb $6, -0xa(%%ebp)\n\t"
      ".LFUN_000e10c0_15:\n\t"
      "movb $7, -0x9(%%ebp)\n\t"
      ".LFUN_000e10c0_16:\n\t"
      "movb %%bl, -0x10(%%ebp)\n\t"
      ".LFUN_000e10c0_17:\n\t"
      "movb $4, -0xf(%%ebp)\n\t"
      "movb $2, -0xe(%%ebp)\n\t"
      "movb %%dl, -0xd(%%ebp)\n\t"
      "movb $5, -0xb(%%ebp)\n\t"
      "movb $0xc, -0x8(%%ebp)\n\t"
      "movb $0xd, -0x7(%%ebp)\n\t"
      "movb $0xe, -0x6(%%ebp)\n\t"
      ".LFUN_000e10c0_18:\n\t"
      "movb 0x3(%%eax), %%dl\n\t"
      "movb 0x5(%%eax), %%al\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x46bfc4(,%%esi,2), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "popl %%esi\n\t"
      "movb %%dl, -0x2(%%ebp)\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_000e10c0_19\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[cce740]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000e10c0_19:\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[cce740]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000e10c0_jt:\n\t"
      ".long .LFUN_000e10c0_9\n\t"
      ".long .LFUN_000e10c0_10\n\t"
      ".long .LFUN_000e10c0_11\n\t"
      ".long .LFUN_000e10c0_12\n\t"
      ".long .LFUN_000e10c0_13\n\t"
      ".text\n\t"
      :
      : [assert] "m"(be10c0_assert), [exitfn] "m"(be10c0_exitfn), [cce740] "m"(be10c0_cce740)
      : "memory");
}
#else
#error "FUN_000e10c0: clang naked draft required"
#endif


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

/* player_ui_save_profile (0xe15b0) — XBE naked draft (batch 123). */
#if defined(__clang__)
static void (*const be15b0_c1c29a0)(void) = (void *)saved_game_file_get_type;
static void (*const be15b0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const be15b0_ce0ee0)(void) = player_ui_edit_profile_is_dirty;
static int (*const be15b0_c19dc20)(const wchar_t *s1, const wchar_t *s2, size_t count) = ustrncmp;
static void (*const be15b0_c1c1e20)(void) = FUN_001c1e20;
static void (*const be15b0_c1c27f0)(void) = playlist_profile_get_display_name;
static void (*const be15b0_c1c4da0)(void) = FUN_001c4da0;
static void (*const be15b0_c1c2e00)(void) = saved_game_file_remember_last_used_multiplayer_variant_directory;
static void (*const be15b0_c1c1bc0)(int, void *) = player_profile_get_from_path;

__attribute__((naked, noinline))
void player_ui_save_profile(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x100, %%esp\n\t"
      "movl 0x46c038, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c1c29a0]\n\t"
      "movzwl %%ax, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "subl $0, %%eax\n\t"
      "je .Lplayer_ui_save_profile_7\n\t"
      "decl %%eax\n\t"
      "je .Lplayer_ui_save_profile_1\n\t"
      "pushl $0x282b40\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "jmp .Lplayer_ui_save_profile_10\n\t"
      ".Lplayer_ui_save_profile_1:\n\t"
      "call *%[ce0ee0]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lplayer_ui_save_profile_2\n\t"
      "pushl $0x282af8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lplayer_ui_save_profile_2:\n\t"
      "movl 0x46c038, %%eax\n\t"
      "testl $0x40000000, %%eax\n\t"
      "je .Lplayer_ui_save_profile_6\n\t"
      "pushl $0xc\n\t"
      "pushl $0x46c0a4\n\t"
      "pushl $0x46c03c\n\t"
      "call *%[c19dc20]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lplayer_ui_save_profile_5\n\t"
      "andb $0xfe, 0x46c0a0\n\t"
      "pushl $0x46c03c\n\t"
      "pushl $0\n\t"
      "call *%[c1c1e20]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lplayer_ui_save_profile_4\n\t"
      "pushl $0x46c03c\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c27f0]\n\t"
      "leal -0x100(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%esi, 0x46c038\n\t"
      "call *%[c1c4da0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_ui_save_profile_3\n\t"
      "leal -0x100(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1c2e00]\n\t"
      "addl $4, %%esp\n\t"
      ".Lplayer_ui_save_profile_3:\n\t"
      "movb $1, %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "movl $0xffffffff, 0x46c038\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_ui_save_profile_4:\n\t"
      "pushl $0x282acc\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "jmp .Lplayer_ui_save_profile_10\n\t"
      ".Lplayer_ui_save_profile_5:\n\t"
      "pushl $0x282a80\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "jmp .Lplayer_ui_save_profile_10\n\t"
      ".Lplayer_ui_save_profile_6:\n\t"
      "pushl $0x46c03c\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c27f0]\n\t"
      "movl 0x46c038, %%ecx\n\t"
      "leal -0x100(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c4da0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_ui_save_profile_3\n\t"
      "leal -0x100(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1c2e00]\n\t"
      "addl $4, %%esp\n\t"
      "movb $1, %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "movl $0xffffffff, 0x46c038\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_ui_save_profile_7:\n\t"
      "testl $0x40000000, 0x46c038\n\t"
      "je .Lplayer_ui_save_profile_8\n\t"
      "pushl $0x282a48\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lplayer_ui_save_profile_8:\n\t"
      "call *%[ce0ee0]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lplayer_ui_save_profile_9\n\t"
      "pushl $0x282af8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lplayer_ui_save_profile_9:\n\t"
      "movl 0x46c038, %%eax\n\t"
      "pushl $0x46c03c\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c1bc0]\n\t"
      "movb $1, %%bl\n\t"
      ".Lplayer_ui_save_profile_10:\n\t"
      "addl $8, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "movl $0xffffffff, 0x46c038\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1c29a0] "m"(be15b0_c1c29a0), [c8f390] "m"(be15b0_c8f390), [ce0ee0] "m"(be15b0_ce0ee0), [c19dc20] "m"(be15b0_c19dc20), [c1c1e20] "m"(be15b0_c1c1e20), [c1c27f0] "m"(be15b0_c1c27f0), [c1c4da0] "m"(be15b0_c1c4da0), [c1c2e00] "m"(be15b0_c1c2e00), [c1c1bc0] "m"(be15b0_c1c1bc0)
      : "memory");
}
#else
#error "player_ui_save_profile: clang naked draft required"
#endif


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

