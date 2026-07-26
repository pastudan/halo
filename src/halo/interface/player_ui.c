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

/* 0xe0ee0 */
void player_ui_edit_profile_is_dirty(void)
{
  int eax = 0;

  /* cmp eax, -1 -> je 0xe0fbd */
  saved_game_file_get_type();
  error(0, (char *)0x0028298c);
  csmemcmp((void *)0x0046c0a4, (void *)0x0046c03c, 104);
  /* test eax, eax -> je 0xe0f59 */
  csmemcmp((void *)0x0046c0a4, (void *)0x0046c03c, 48);
  /* test eax, eax -> je 0xe0fad */

  (void)eax;
}

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

/* 0xe10c0 */
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
  input_abstraction_update_local_player_preferences();
  input_abstraction_update_local_player_preferences();

  (void)ebx;
  (void)ecx;
  (void)edi;
}

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

/* 0xe15b0 */
void player_ui_save_profile(void)
{
  int eax = 0;
  int esi = 0;

  saved_game_file_get_type();
  error(0, (char *)0x00282b40);
  player_ui_edit_profile_is_dirty();
  /* test (char)eax, (char)eax -> jne 0xe1603 */
  error(0, (char *)0x00282af8);
  /* test eax, 0x40000000 -> je 0xe16b2 */
  ustrncmp((wchar_t *)0x0046c03c, (wchar_t *)0x0046c0a4, 12);
  /* test eax, eax -> je 0xe16a1 */
  FUN_001c1e20();
  /* cmp esi, -1 -> je 0xe1690 */
  playlist_profile_get_display_name();
  /* mem[0x0046c038] = esi */
  FUN_001c4da0();
  /* test (char)eax, (char)eax -> je 0xe167c */
  saved_game_file_remember_last_used_multiplayer_variant_directory();
  /* mem[0x0046c038] = 0xffffffff */
  error(0, (char *)0x00282acc);
  error(0, (char *)0x00282a80);
  playlist_profile_get_display_name();
  FUN_001c4da0();
  /* test (char)eax, (char)eax -> je 0xe167c */
  saved_game_file_remember_last_used_multiplayer_variant_directory();
  /* mem[0x0046c038] = 0xffffffff */
  /* relift: test dword ptr [0x46c038], 0x40000000 -> je 0xe1715 */
  error(0, (char *)0x00282a48);
  player_ui_edit_profile_is_dirty();
  /* test (char)eax, (char)eax -> jne 0xe172d */
  error(0, (char *)0x00282af8);
  player_profile_get_from_path();
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

/* 0xe1770 */
void FUN_000e1770(int a0)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp dword ptr [0x46bf10], -1 -> je 0xe17a4 */
  FUN_000e1000();
  player_profile_get_from_path();
  FUN_000e10c0();
  /* cmp esi, 0x52 -> jge 0xe17cb */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0xe17d9 */
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0xe17ee */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0xe17fa */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0xe1806 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0xe1812 */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0xe181e */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0xe182a */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0xe1836 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0xe1842 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0xe184e */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0xe185a */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0xe1866 */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0xe1875 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0xe1884 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0xe1893 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0xe18a2 */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0xe18b1 */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0xe18c0 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0xe18cf */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0xe18de */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0xe18ed */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0xe18fc */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0xe190b */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0xe191a */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0xe1929 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0xe1938 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0xe1947 */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0xe1955 */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0xe196c */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0xe1979 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0xe1986 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0xe1993 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0xe19a0 */
  D3DDevice_SetTextureState_BumpEnv();
  D3DDevice_GetBackBuffer(0, ecx, (void *)(uintptr_t)eax);
  D3DDevice_CreateTexture(eax, edx, ecx, eax, edx, ecx, (void *)(uintptr_t)eax);
  D3DDevice_SetRenderTarget((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  D3DDevice_GetDepthStencilSurface((void *)(uintptr_t)eax);
  D3DDevice_Clear(edx, (void *)(uintptr_t)ecx, eax, edx, 0.0f, eax);
  D3DDevice_SetTransform(ecx, (void *)(uintptr_t)eax);
  D3DDevice_GetTransform(ecx, (void *)(uintptr_t)eax);
  /* cmp esi, 0x52 -> jge 0xe1a6f */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0xe1a82 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0xe1a9f */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0xe1aaf */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0xe1abf */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0xe1acf */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0xe1adf */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0xe1aef */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0xe1aff */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0xe1b0f */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0xe1b1f */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0xe1b2f */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0xe1b3f */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0xe1b52 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0xe1b65 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0xe1b78 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
