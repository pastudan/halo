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

/* 0xe0620 */
void FUN_000e0620(void)
{
  int eax = 0;
  int ecx = 0;

  /* test (char)eax, (char)eax -> je 0xe06f1 */
  /* mem[0x0046bec4] = eax */
  /* mem[0x0046bec8] = ecx */
  FUN_001d9068();
  FUN_001d9068();
  local_time_get();
  /* cmp eax, 7 -> jle 0xe06f1 */
  /* mem[0x0046bebc] = eax */
  /* mem[0x0046bec0] = ecx */
  local_time_get();
  /* mem[0x0046bed0] = eax */

  (void)eax;
  (void)ecx;
}

/* 0xe0720 */
void player_ui_reset_single_player_local_player_controllers(void)
{
  csmemset((void *)0x0046bfc4, 0, 0);
}

/* 0xe0740 */
void player_ui_set_single_player_local_player_controller(void)
{
  int esi = 0;
  int edi = 0;

  /* cmp (int16_t)esi, 4 -> jl 0xe0771 */
  display_assert((char *)0x00282708, (char *)0x00282724, 119, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0xe0780 */
  /* cmp (int16_t)edi, 4 -> jl 0xe07ac */
  display_assert((char *)0x002826ec, (char *)0x00282724, 121, 0);
  system_exit(0);

  (void)esi;
  (void)edi;
}

/* 0xe0810 */
int player_ui_get_single_player_local_player_from_controller(short local_player_index)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0xe0840 */
void player_ui_local_player_joined_multiplayer_game(void)
{
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0xe0853 */
  /* cmp (int16_t)esi, 4 -> jl 0xe0873 */
  display_assert((char *)0x00282750, (char *)0x00282724, 157, 0);
  system_exit(0);

  (void)esi;
}

/* 0xe0890 */
void player_ui_local_player_wants_to_play_multiplayer(void)
{
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0xe08a3 */
  /* cmp (int16_t)esi, 4 -> jl 0xe08c3 */
  display_assert((char *)0x00282750, (char *)0x00282724, 167, 0);
  system_exit(0);

  (void)esi;
}

/* 0xe08e0 */
void player_ui_clear_multiplayer_autojoin_for_local_player(void)
{
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0xe08f3 */
  /* cmp (int16_t)esi, 4 -> jl 0xe0913 */
  display_assert((char *)0x00282750, (char *)0x00282724, 175, 0);
  system_exit(0);

  (void)esi;
}

/* 0xe0930 */
void player_ui_autojoin_players_to_next_multiplayer_game(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0xe0960 */
void player_ui_clear_multiplayer_variant(void)
{
  set_game_connection(0);
  game_engine_dispose();
  game_set_game_variant((void *)0);
}

/* 0xe0980 */
void player_ui_get_active_player_profile(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* cmp (int16_t)esi, 4 -> jge 0xe099b */
  /* test edi, edi -> jne 0xe09bb */
  display_assert((char *)0x002827a0, (char *)0x00282724, 238, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)edi, (void *)(uintptr_t)eax, 0);

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0xe09e0 */
void player_ui_get_active_player_profile_index(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0xe0a10 */
void player_ui_get_last_single_player_level_played(void)
{
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0xe0a23 */
  /* cmp (int16_t)esi, 4 -> jl 0xe0a43 */
  display_assert((char *)0x00282750, (char *)0x00282724, 265, 0);
  system_exit(0);

  (void)esi;
}

/* 0xe0a60 */
void player_ui_set_game_variant(void)
{
  int esi = 0;

  /* test esi, esi -> jne 0xe0a8b */
  display_assert((char *)0x00282808, (char *)0x00282724, 273, 0);
  system_exit(0);
  csmemcpy((void *)0x0046bfcc, (void *)(uintptr_t)esi, 104);

  (void)esi;
}

/* 0xe0ab0 */
void player_ui_game_variant_specified(void)
{
  int eax = 0;
  int esi = 0;

  /* test esi, esi -> jne 0xe0adb */
  display_assert((char *)0x00282808, (char *)0x00282724, 284, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0xe0af9 */
  csmemcpy((void *)(uintptr_t)esi, (void *)0x0046bfcc, 104);

  (void)eax;
  (void)esi;
}

/* 0xe0b00 */
bool player_ui_rumble_disabled(int controller_index)
{
  int esi = 0;

  /* cmp (int16_t)esi, -1 -> jne 0xe0b13 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0xe0b1e */
  /* cmp (int16_t)esi, 4 -> jl 0xe0b3e */
  display_assert((char *)0x00282750, (char *)0x00282724, 305, 0);
  system_exit(0);
  return 0;

  (void)esi;
}

/* 0xe0b50 */
void player_ui_autolevel_enabled(void)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0xe0b62 */
  /* cmp (int16_t)esi, 4 -> jl 0xe0b82 */
  display_assert((char *)0x00281054, (char *)0x00282724, 320, 0);
  system_exit(0);
  network_game_in_progress();
  /* test (char)eax, (char)eax -> jne 0xe0baa */
  /* relift: cmp word ptr [edx*2 + 0x46bfc4], (int16_t)esi -> je 0xe0ba6 */
  /* cmp (int16_t)eax, 4 -> jl 0xe0b90 */
  /* cmp (int16_t)esi, -1 -> jne 0xe0bb5 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0xe0bc0 */
  /* cmp (int16_t)esi, 4 -> jl 0xe0be0 */
  display_assert((char *)0x00282750, (char *)0x00282724, 340, 0);
  system_exit(0);

  (void)eax;
  (void)edx;
  (void)esi;
}

/* 0xe0bf0 */
void player_ui_get_path_to_local_player_profile_directory(void)
{
  /* test (int16_t)eax, (int16_t)eax -> jl 0xe0c1d */
  /* cmp (int16_t)eax, 4 -> jge 0xe0c1d */
  FUN_001c1280();
}

/* 0xe0c90 */
void player_ui_get_player1_last_used_profile_index(void)
{
  int eax = 0;

  /* test (char)eax, (char)eax -> jne 0xe0cbf */
  saved_game_file_retrieve_player1_last_used_profile_directory();
  /* test (char)eax, (char)eax -> je 0xe0cbf */
  saved_game_file_find_profile_index_for_directory_path();
  /* mem[0x0030f02c] = eax */

  (void)eax;
}

/* 0xe0cd0 */
void player_ui_fast_setup_network_server(void)
{
  int eax = 0;

  ui_widgets_close_all();
  dispose_global_network_game_client();
  dispose_global_network_game_server();
  set_game_connection(0);
  main_set_multiplayer_map_name((char *)0x0025386f);
  ui_widget_load_by_name_or_tag((char *)0x002828e0, 0, 0, 0, 0, 0, 0);
  /* test eax, eax -> je 0xe0d6a */
  game_engine_playlist_initialize();
  network_game_set_accept_remote_connections(0);
  FUN_0012a890();
  /* test (char)eax, (char)eax -> je 0xe0d45 */
  FUN_0012a250();
  /* test (char)eax, (char)eax -> je 0xe0d45 */
  game_engine_playlist_begin();
  set_game_connection(0);
  dispose_global_network_game_client();
  dispose_global_network_game_server();
  network_game_set_accept_remote_connections(0);
  error(0, (char *)0x002828ac);
  error(0, (char *)0x00282840);

  (void)eax;
}

/* 0xe0d80 */
void player_ui_edit_profile_is_default_profile(void)
{
  int eax = 0;

  /* cmp eax, -1 -> je 0xe0dbd */
  saved_game_file_get_type();
  /* test eax, eax -> jl 0xe0dae */
  /* cmp eax, 1 -> jg 0xe0dae */
  error(0, (char *)0x00282938);

  (void)eax;
}

/* 0xe0dd0 */
void player_ui_edit_profile_name_is_dirty(void)
{
  int eax = 0;

  /* cmp eax, -1 -> je 0xe0e20 */
  saved_game_file_get_type();
  error(0, (char *)0x00282938);
  ustrncmp((wchar_t *)0x0046c03c, (wchar_t *)0x0046c0a4, 12);
  /* test eax, eax -> je 0xe0e2f */
  error(0, (char *)0x00282964);

  (void)eax;
}

/* 0xe0e40 */
void player_ui_prompt_user_to_rename_edit_profile(void)
{
  int eax = 0;

  /* cmp eax, -1 -> je 0xe0e87 */
  saved_game_file_get_type();
  error(0, (char *)0x00282938);
  virtual_keyboard_set_validation((wchar_t *)0x0046c03c, 24, 10);
  error(0, (char *)0x00282964);

  (void)eax;
}

/* 0xe0ea0 */
void player_ui_get_edit_player_profile(void)
{
  saved_game_file_get_type();
}

/* 0xe0ec0 */
void player_ui_get_edit_playlist_profile(void)
{
  saved_game_file_get_type();
}

/* player_ui_edit_profile_is_dirty (0xe0ee0) — XBE naked draft (batch 137). */
#if defined(__clang__)
static void (*const be0ee0_c1c29a0)(void) = saved_game_file_get_type;
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


/* 0xe0fd0 */
void player_ui_activate_all_solo_levels(void)
{
  int eax = 0;

  /* cmp eax, 0xa -> jl 0xe0fd4 */
  /* cmp eax, -1 -> je 0xe0ff8 */
  player_profile_get_from_path();

  (void)eax;
}

/* 0xe1000 */
void FUN_000e1000(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  data_iterator_new((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  data_iterator_next((void *)(uintptr_t)edx);
  /* test eax, eax -> je 0xe1049 */
  /* cmp (int16_t)eax, 0xffff -> je 0xe1039 */
  hud_print_message(eax, (wchar_t *)(uintptr_t)esi);
  data_iterator_next((void *)(uintptr_t)eax);
  /* test eax, eax -> jne 0xe1025 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0xe1050 */
int player0_look_pitch_is_inverted(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0xe1060 */
int FUN_000e1060(void)
{
  int eax = 0;
  int esi = 0;

  /* test (char)eax, (char)eax -> je 0xe1070 */
  /* cmp (char)eax, 1 -> je 0xe1070 */
  /* test esi, esi -> jne 0xe10a4 */
  display_assert((char *)0x002829b0, (char *)0x00282724, 869, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)esi, 0, 48);
  return 1;

  (void)eax;
  (void)esi;
}

/* FUN_000e10c0 (0xe10c0) — XBE naked draft (batch 118). */
#if defined(__clang__)
static void (*const be10c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const be10c0_exitfn)(int) = system_exit;
static void (*const be10c0_cce740)(void) = input_abstraction_update_local_player_preferences;

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


/* 0xe13f0 */
void player_ui_clear_multiplayer_joins(void)
{
  int esi = 0;

  /* test esi, esi -> jne 0xe1434 */
  display_assert((char *)0x002829b0, (char *)0x00282724, 869, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)esi, 0, 48);

  (void)esi;
}

/* 0xe1490 */
void player_ui_set_active_player_profile(void)
{
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test (int16_t)edi, (int16_t)edi -> jl 0xe14aa */
  /* cmp (int16_t)edi, 4 -> jge 0xe14aa */
  /* test esi, esi -> jne 0xe14ca */
  display_assert((char *)0x002827a0, (char *)0x00282724, 226, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)edx, (void *)(uintptr_t)esi, 48);
  FUN_000e10c0();

  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0xe1500 */
void player_ui_begin_editing_profile(void)
{
  int eax = 0;
  int esi = 0;

  /* mem[0x0046c038] = 0xffffffff */
  saved_game_file_get_type();
  error(0, (char *)0x00282a28);
  playlist_profile_delete();
  /* test (char)eax, (char)eax -> je 0xe154e */
  error(0, (char *)0x002829f0);
  player_profile_new();
  /* test (char)eax, (char)eax -> je 0xe1590 */
  csmemcpy((void *)0x0046c03c, (void *)0x0046c0a4, 48);
  /* mem[0x0046c038] = esi */
  error(0, (char *)0x002829b8);

  (void)eax;
  (void)esi;
}

/* player_ui_save_profile (0xe15b0) — XBE naked draft (batch 123). */
#if defined(__clang__)
static void (*const be15b0_c1c29a0)(void) = saved_game_file_get_type;
static void (*const be15b0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const be15b0_ce0ee0)(void) = player_ui_edit_profile_is_dirty;
static int (*const be15b0_c19dc20)(const wchar_t *s1, const wchar_t *s2, size_t count) = ustrncmp;
static void (*const be15b0_c1c1e20)(void) = FUN_001c1e20;
static void (*const be15b0_c1c27f0)(void) = playlist_profile_get_display_name;
static void (*const be15b0_c1c4da0)(void) = FUN_001c4da0;
static void (*const be15b0_c1c2e00)(void) = saved_game_file_remember_last_used_multiplayer_variant_directory;
static void (*const be15b0_c1c1bc0)(void) = player_profile_get_from_path;

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

/* FUN_000e1770 (0xe1770) — XBE naked draft (batch 130). */
#if defined(__clang__)
static void (*const be1770_ce1000)(void) = FUN_000e1000;
static void (*const be1770_c1c1bc0)(void) = player_profile_get_from_path;
static void (*const be1770_ce10c0)(void) = FUN_000e10c0;
static void (*const be1770_c1e9350)(uint32_t reg, uint32_t value) = D3DDevice_SetRenderState_Simple;
static void (*const be1770_c1e9320)(void) = D3DDevice_SetRenderState_PSTextureModes;
static void (*const be1770_c1e9aa0)(void) = D3DDevice_SetRenderState_VertexBlend;
static void (*const be1770_c1e9680)(void) = D3DDevice_SetRenderState_FogColor;
static void __stdcall (*const be1770_c1e99b0)(uint32_t value) = D3DDevice_SetRenderState_FillMode;
static void (*const be1770_c1e99f0)(void) = D3DDevice_SetRenderState_BackFillMode;
static void (*const be1770_c1e9a40)(void) = D3DDevice_SetRenderState_TwoSidedLighting;
static void (*const be1770_c1e9780)(void) = D3DDevice_SetRenderState_NormalizeNormals;
static void __stdcall (*const be1770_c1ea290)(uint32_t enable) = D3DDevice_SetRenderState_ZEnable;
static void __stdcall (*const be1770_c1ea300)(uint32_t value) = D3DDevice_SetRenderState_StencilEnable;
static void __stdcall (*const be1770_c1ea380)(uint32_t value) = D3DDevice_SetRenderState_StencilFail;
static void __stdcall (*const be1770_c1e96d0)(uint32_t mode) = D3DDevice_SetRenderState_CullMode;
static void (*const be1770_c1e9740)(void) = D3DDevice_SetRenderState_FrontFace;
static void (*const be1770_c1e97b0)(void) = D3DDevice_SetRenderState_TextureFactor;
static void __stdcall (*const be1770_c1e98e0)(uint32_t value) = D3DDevice_SetRenderState_ZBias;
static void (*const be1770_c1e9960)(void) = D3DDevice_SetRenderState_LogicOp;
static void (*const be1770_c1e9620)(void) = D3DDevice_SetRenderState_EdgeAntiAlias;
static void (*const be1770_c1ea540)(void) = D3DDevice_SetRenderState_MultiSampleAntiAlias;
static void (*const be1770_c1ea590)(void) = D3DDevice_SetRenderState_MultiSampleMask;
static void (*const be1770_c1e92f0)(void) = D3DDevice_SetRenderState_MultiSampleType;
static void (*const be1770_c1e9650)(void) = D3DDevice_SetRenderState_ShadowFunc;
static void (*const be1770_c1e9800)(void) = D3DDevice_SetRenderState_LineWidth;
static void (*const be1770_c1e9860)(void) = D3DDevice_SetRenderState_Dxt1NoiseEnable;
static void (*const be1770_c1ea3f0)(void) = D3DDevice_SetRenderState_YuvEnable;
static void (*const be1770_c1ea420)(void) = D3DDevice_SetRenderState_OcclusionCullEnable;
static void (*const be1770_c1ea480)(void) = D3DDevice_SetRenderState_StencilCullEnable;
static void (*const be1770_c1ea4e0)(void) = D3DDevice_SetRenderState_RopZCmpAlwaysRead;
static void (*const be1770_c1ea500)(void) = D3DDevice_SetRenderState_RopZRead;
static void (*const be1770_c1ea520)(void) = D3DDevice_SetRenderState_DoNotCullUncompressed;
static void (*const be1770_c1e9410)(uint32_t stage, uint32_t state, uint32_t value) = D3DDevice_SetTextureStageState;
static void (*const be1770_c1e9ae0)(void) = D3DDevice_SetTextureState_TexCoordIndex;
static void __stdcall (*const be1770_c1e9c20)(uint32_t stage, uint32_t color) = D3DDevice_SetTextureState_BorderColor;
static void (*const be1770_c1e9c60)(void) = D3DDevice_SetTextureState_ColorKeyColor;
static void (*const be1770_c1e9bc0)(void) = D3DDevice_SetTextureState_BumpEnv;
static int __stdcall (*const be1770_c1e7d50)(int back_buffer, uint32_t type, void **out_surface) = D3DDevice_GetBackBuffer;
static void (*const be1770_c1e9380)(uint32_t reg_index, uint32_t value) = D3DDevice_SetRenderState_Deferred;

__attribute__((naked, noinline))
void FUN_000e1770(int a0 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movb 0x8(%%ebp), %%al\n\t"
      "movb %%al, 0x46bf0b\n\t"
      "cmpl $-1, 0x46bf10\n\t"
      "je .LFUN_000e1770_1\n\t"
      "pushl %%esi\n\t"
      "movl $0x282b78, %%esi\n\t"
      "call *%[ce1000]\n\t"
      "movl 0x46bf10, %%ecx\n\t"
      "pushl $0x46bee0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c1bc0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%esi\n\t"
      ".LFUN_000e1770_1:\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "call *%[ce10c0]\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "cmpl $0x52, %%esi\n\t"
      "jge .LFUN_000e1770_2\n\t"
      "movl 0x282b90(,%%esi,4), %%ecx\n\t"
      "movl %%edi, %%edx\n\t"
      "call *%[c1e9350]\n\t"
      "movl %%edi, 0x1fb698(,%%esi,4)\n\t"
      "ret\n\t"
      ".LFUN_000e1770_2:\n\t"
      "cmpl $0x74, %%esi\n\t"
      "jge .LFUN_000e1770_3\n\t"
      "movl %%edi, %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "jmp .LFUN_000e1770_10000\n\t"
      ".LFUN_000e1770_3:\n\t"
      "jne .LFUN_000e1770_4\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e9320]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_4:\n\t"
      "cmpl $0x75, %%esi\n\t"
      "jne .LFUN_000e1770_5\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e9aa0]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_5:\n\t"
      "cmpl $0x76, %%esi\n\t"
      "jne .LFUN_000e1770_6\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e9680]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_6:\n\t"
      "cmpl $0x77, %%esi\n\t"
      "jne .LFUN_000e1770_7\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e99b0]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_7:\n\t"
      "cmpl $0x78, %%esi\n\t"
      "jne .LFUN_000e1770_8\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e99f0]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_8:\n\t"
      "cmpl $0x79, %%esi\n\t"
      "jne .LFUN_000e1770_9\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e9a40]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_9:\n\t"
      "cmpl $0x7a, %%esi\n\t"
      "jne .LFUN_000e1770_10\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e9780]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_10:\n\t"
      "cmpl $0x7b, %%esi\n\t"
      "jne .LFUN_000e1770_11\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ea290]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_11:\n\t"
      "cmpl $0x7c, %%esi\n\t"
      "jne .LFUN_000e1770_12\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ea300]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_12:\n\t"
      "cmpl $0x7d, %%esi\n\t"
      "jne .LFUN_000e1770_13\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ea380]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_13:\n\t"
      "cmpl $0x7f, %%esi\n\t"
      "jne .LFUN_000e1770_14\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e96d0]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_14:\n\t"
      "cmpl $0x7e, %%esi\n\t"
      "jne .LFUN_000e1770_15\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e9740]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_15:\n\t"
      "cmpl $0x80, %%esi\n\t"
      "jne .LFUN_000e1770_16\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e97b0]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_16:\n\t"
      "cmpl $0x81, %%esi\n\t"
      "jne .LFUN_000e1770_17\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e98e0]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_17:\n\t"
      "cmpl $0x82, %%esi\n\t"
      "jne .LFUN_000e1770_18\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e9960]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_18:\n\t"
      "cmpl $0x83, %%esi\n\t"
      "jne .LFUN_000e1770_19\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e9620]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_19:\n\t"
      "cmpl $0x84, %%esi\n\t"
      "jne .LFUN_000e1770_20\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ea540]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_20:\n\t"
      "cmpl $0x85, %%esi\n\t"
      "jne .LFUN_000e1770_21\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ea590]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_21:\n\t"
      "cmpl $0x86, %%esi\n\t"
      "jne .LFUN_000e1770_22\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e92f0]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_22:\n\t"
      "cmpl $0x87, %%esi\n\t"
      "jne .LFUN_000e1770_23\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e9650]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_23:\n\t"
      "cmpl $0x88, %%esi\n\t"
      "jne .LFUN_000e1770_24\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e9800]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_24:\n\t"
      "cmpl $0x89, %%esi\n\t"
      "jne .LFUN_000e1770_25\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e9860]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_25:\n\t"
      "cmpl $0x8a, %%esi\n\t"
      "jne .LFUN_000e1770_26\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ea3f0]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_26:\n\t"
      "cmpl $0x8b, %%esi\n\t"
      "jne .LFUN_000e1770_27\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ea420]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_27:\n\t"
      "cmpl $0x8c, %%esi\n\t"
      "jne .LFUN_000e1770_28\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ea480]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_28:\n\t"
      "cmpl $0x8d, %%esi\n\t"
      "jne .LFUN_000e1770_29\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ea4e0]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_29:\n\t"
      "cmpl $0x8e, %%esi\n\t"
      "jne .LFUN_000e1770_30\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ea500]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_30:\n\t"
      "cmpl $0x8f, %%esi\n\t"
      "jne .LFUN_000e1770_31\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ea520]\n\t"
      ".LFUN_000e1770_31:\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "cmpl $0x16, %%edx\n\t"
      "jge .LFUN_000e1770_32\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e9410]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_32:\n\t"
      "cmpl $0x1c, %%edx\n\t"
      "jne .LFUN_000e1770_33\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1e9ae0]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_33:\n\t"
      "cmpl $0x1d, %%edx\n\t"
      "jne .LFUN_000e1770_34\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1e9c20]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_34:\n\t"
      "cmpl $0x1e, %%edx\n\t"
      "jne .LFUN_000e1770_35\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1e9c60]\n\t"
      "ret\n\t"
      ".LFUN_000e1770_35:\n\t"
      "cmpl $0x1b, %%edx\n\t"
      "jg .LFUN_000e1770_36\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1e9bc0]\n\t"
      ".LFUN_000e1770_36:\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1e7d50]\n\t"
      "xorl %%eax, %%eax\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      ".LFUN_000e1770_10000:\n\t"
      "jmp *%[c1e9380]\n\t"
      :
      : [ce1000] "m"(be1770_ce1000), [c1c1bc0] "m"(be1770_c1c1bc0), [ce10c0] "m"(be1770_ce10c0), [c1e9350] "m"(be1770_c1e9350), [c1e9320] "m"(be1770_c1e9320), [c1e9aa0] "m"(be1770_c1e9aa0), [c1e9680] "m"(be1770_c1e9680), [c1e99b0] "m"(be1770_c1e99b0), [c1e99f0] "m"(be1770_c1e99f0), [c1e9a40] "m"(be1770_c1e9a40), [c1e9780] "m"(be1770_c1e9780), [c1ea290] "m"(be1770_c1ea290), [c1ea300] "m"(be1770_c1ea300), [c1ea380] "m"(be1770_c1ea380), [c1e96d0] "m"(be1770_c1e96d0), [c1e9740] "m"(be1770_c1e9740), [c1e97b0] "m"(be1770_c1e97b0), [c1e98e0] "m"(be1770_c1e98e0), [c1e9960] "m"(be1770_c1e9960), [c1e9620] "m"(be1770_c1e9620), [c1ea540] "m"(be1770_c1ea540), [c1ea590] "m"(be1770_c1ea590), [c1e92f0] "m"(be1770_c1e92f0), [c1e9650] "m"(be1770_c1e9650), [c1e9800] "m"(be1770_c1e9800), [c1e9860] "m"(be1770_c1e9860), [c1ea3f0] "m"(be1770_c1ea3f0), [c1ea420] "m"(be1770_c1ea420), [c1ea480] "m"(be1770_c1ea480), [c1ea4e0] "m"(be1770_c1ea4e0), [c1ea500] "m"(be1770_c1ea500), [c1ea520] "m"(be1770_c1ea520), [c1e9410] "m"(be1770_c1e9410), [c1e9ae0] "m"(be1770_c1e9ae0), [c1e9c20] "m"(be1770_c1e9c20), [c1e9c60] "m"(be1770_c1e9c60), [c1e9bc0] "m"(be1770_c1e9bc0), [c1e7d50] "m"(be1770_c1e7d50), [c1e9380] "m"(be1770_c1e9380)
      : "memory");
}
#else
#error "FUN_000e1770: clang naked draft required"
#endif

