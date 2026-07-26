void ui_widget_game_data_function_invoke(
  void *widget, unsigned __int16 game_data_input_reference_function)
{
  assert_halt(widget);

  if (game_data_input_reference_function > 40u) {
    error(2, "invalid game_data_input_reference_function");
  } else {
    ui_widget_game_data_function_table[game_data_input_reference_function](
      widget);
  }
}

void ui_widget_game_data_build_version(int widget)
{
  wchar_t *v1, *v2; // eax

  if (!ui_widget_game_data_build_version_wide_str[0]) {
    ascii_to_wide(
#if DECOMP_CUSTOM
      build_ui_widget_text,
#else
      "01.10.12.2276",
#endif
      ui_widget_game_data_build_version_wide_str,
      sizeof(ui_widget_game_data_build_version_wide_str));
  }

  if (!*(uint32_t *)(widget + 60)) {
    v1 =
      ui_widget_realloc(0, sizeof(ui_widget_game_data_build_version_wide_str),
                        __FILE__, __LINE__);
    *(uint32_t *)(widget + 60) = (uint32_t)v1;
    if (v1) {
      csmemset(v1, 0, sizeof(ui_widget_game_data_build_version_wide_str));
    }
  }
  v2 = *(wchar_t **)(widget + 60);
  if (v2) {
    ustrncpy(v2, ui_widget_game_data_build_version_wide_str, 0x3Fu);
    *(wchar_t *)(*(uint32_t *)(widget + 60) + 126) = 0;
  }
}
/* --- ui_widget_game_data_input_functions.obj batch (2026-07-26) --- */

/* 0xedcd0 */
void FUN_000edcd0(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  player_ui_get_edit_playlist_profile();
  display_assert((char *)0x00287b1c, (char *)0x002859a4, 3162, 0);
  system_exit(0);
  /* cmp edi, ebx -> je 0xedf55 */
  /* cmp edi, ebx -> jne 0xedd3c */
  display_assert((char *)0x002871d8, (char *)0x002859a4, 3170, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xedd55 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xedd7a */
  /* cmp esi, ebx -> jne 0xedd43 */
  display_assert((char *)0x002871ac, (char *)0x002859a4, 3172, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0xeddc8 */
  display_assert((char *)0x0028714c, (char *)0x002859a4, 3182, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xedddd */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xede02 */
  /* cmp esi, ebx -> jne 0xeddd0 */
  display_assert((char *)0x00287120, (char *)0x002859a4, 3184, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0xede50 */
  display_assert((char *)0x002870c8, (char *)0x002859a4, 3194, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xede64 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xede89 */
  /* cmp esi, ebx -> jne 0xede57 */
  display_assert((char *)0x0028709c, (char *)0x002859a4, 3196, 0);
  system_exit(0);
  /* cmp eax, 0x18 -> ja 0xedec9 */
  /* cmp esi, ebx -> jne 0xedef9 */
  display_assert((char *)0x00286950, (char *)0x002859a4, 3209, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xedf0d */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xedf2d */
  /* cmp esi, ebx -> jne 0xedf00 */
  display_assert((char *)0x00286928, (char *)0x002859a4, 3211, 0);
  system_exit(0);
  error(0, (char *)0x00286550);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0xedfb0 */
void FUN_000edfb0(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  player_ui_get_edit_playlist_profile();
  display_assert((char *)0x00287b1c, (char *)0x002859a4, 3237, 0);
  system_exit(0);
  /* cmp edi, ebx -> je 0xee48c */
  /* cmp edi, ebx -> jne 0xee01c */
  display_assert((char *)0x00287654, (char *)0x002859a4, 3245, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xee05a */
  /* cmp esi, ebx -> jne 0xee028 */
  display_assert((char *)0x00287624, (char *)0x002859a4, 3247, 0);
  system_exit(0);
  /* cmp eax, 5 -> ja 0xee082 */
  /* cmp edi, ebx -> jne 0xee0b2 */
  display_assert((char *)0x002875b8, (char *)0x002859a4, 3258, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xee0cd */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xee0ed */
  /* cmp esi, ebx -> jne 0xee0c0 */
  display_assert((char *)0x00287588, (char *)0x002859a4, 3260, 0);
  system_exit(0);
  FUN_001d9068();
  /* cmp ecx, 0x23 -> ja 0xee140 */
  /* cmp edi, ebx -> jne 0xee16b */
  display_assert((char *)0x00287530, (char *)0x002859a4, 3273, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xee184 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)eax -> je 0xee1a4 */
  /* cmp esi, ebx -> jne 0xee177 */
  display_assert((char *)0x00287508, (char *)0x002859a4, 3275, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0xee1ea */
  display_assert((char *)0x002874ac, (char *)0x002859a4, 3285, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xee203 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)eax -> je 0xee223 */
  /* cmp esi, ebx -> jne 0xee1f6 */
  display_assert((char *)0x00287480, (char *)0x002859a4, 3287, 0);
  system_exit(0);
  /* cmp eax, 0x12c -> jg 0xee24d */
  /* cmp eax, ebx -> je 0xee254 */
  /* cmp eax, 0x96 -> jne 0xee254 */
  /* cmp eax, 0x1c2 -> je 0xee25a */
  /* cmp edi, ebx -> jne 0xee287 */
  display_assert((char *)0x0028741c, (char *)0x002859a4, 3298, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xee2a0 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)eax -> je 0xee2c0 */
  /* cmp esi, ebx -> jne 0xee293 */
  display_assert((char *)0x002873e8, (char *)0x002859a4, 3300, 0);
  system_exit(0);
  /* cmp eax, 0x12c -> jg 0xee2ea */
  /* cmp eax, ebx -> je 0xee2f1 */
  /* cmp eax, 0x96 -> jne 0xee2f1 */
  /* cmp eax, 0x1c2 -> je 0xee2f7 */
  /* cmp edi, ebx -> jne 0xee324 */
  display_assert((char *)0x00287380, (char *)0x002859a4, 3311, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xee33d */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)eax -> je 0xee35d */
  /* cmp esi, ebx -> jne 0xee330 */
  display_assert((char *)0x00287354, (char *)0x002859a4, 3313, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0xee39b */
  display_assert((char *)0x002872f0, (char *)0x002859a4, 3322, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xee3b4 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)eax -> je 0xee3d4 */
  /* cmp esi, ebx -> jne 0xee3a7 */
  display_assert((char *)0x002872bc, (char *)0x002859a4, 3324, 0);
  system_exit(0);
  /* cmp esi, ebx -> jne 0xee417 */
  display_assert((char *)0x00287b58, (char *)0x002859a4, 3335, 0);
  system_exit(0);
  /* relift: cmp word ptr [eax + 0xe], (int16_t)edx -> je 0xee430 */
  /* cmp eax, ebx -> jne 0xee423 */
  /* cmp ecx, 0x12c -> jg 0xee475 */
  /* cmp ecx, ebx -> je 0xee45b */
  /* cmp ecx, 0x96 -> jne 0xee45b */
  /* cmp ecx, 0x1c2 -> jne 0xee45b */
  error(0, (char *)0x00286550);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0xee500 */
void FUN_000ee500(void *widget)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  player_ui_get_edit_playlist_profile();
  display_assert((char *)0x00287b1c, (char *)0x002859a4, 3366, 0);
  system_exit(0);
  /* test edi, edi -> je 0xee7b6 */
  /* test edi, edi -> jne 0xee569 */
  display_assert((char *)0x002878a8, (char *)0x002859a4, 3374, 0);
  system_exit(0);
  /* test esi, esi -> je 0xee57e */
  /* relift: cmp word ptr [esi + 0xe], 2 -> je 0xee59e */
  /* test esi, esi -> jne 0xee570 */
  display_assert((char *)0x00287874, (char *)0x002859a4, 3376, 0);
  system_exit(0);
  /* test edi, edi -> jne 0xee5e4 */
  display_assert((char *)0x0028780c, (char *)0x002859a4, 3386, 0);
  system_exit(0);
  /* test esi, esi -> je 0xee5fd */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)eax -> je 0xee61d */
  /* test esi, esi -> jne 0xee5f0 */
  display_assert((char *)0x002877e0, (char *)0x002859a4, 3388, 0);
  system_exit(0);
  /* cmp eax, 4 -> ja 0xee64f */
  /* test edi, edi -> jne 0xee67c */
  display_assert((char *)0x00287784, (char *)0x002859a4, 3400, 0);
  system_exit(0);
  /* test esi, esi -> je 0xee695 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)eax -> je 0xee6b5 */
  /* test esi, esi -> jne 0xee688 */
  display_assert((char *)0x00287758, (char *)0x002859a4, 3402, 0);
  system_exit(0);
  /* cmp eax, 0xa -> ja 0xee717 */
  /* test esi, esi -> jne 0xee744 */
  display_assert((char *)0x002876f8, (char *)0x002859a4, 3421, 0);
  system_exit(0);
  /* test esi, esi -> je 0xee75d */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)eax -> je 0xee77d */
  /* test esi, esi -> jne 0xee750 */
  display_assert((char *)0x00287b7c, (char *)0x002859a4, 3423, 0);
  system_exit(0);
  error(0, (char *)0x00286550);

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0xee810 */
void FUN_000ee810(void *widget)
{
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  player_ui_get_edit_playlist_profile();
  display_assert((char *)0x00287b1c, (char *)0x002859a4, 3450, 0);
  system_exit(0);
  /* cmp edi, ebx -> je 0xee9e9 */
  /* cmp edi, ebx -> jne 0xee87c */
  display_assert((char *)0x00287a8c, (char *)0x002859a4, 3458, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xee895 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xee8ba */
  /* cmp esi, ebx -> jne 0xee883 */
  display_assert((char *)0x00287a5c, (char *)0x002859a4, 3460, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0xee908 */
  display_assert((char *)0x002879f0, (char *)0x002859a4, 3470, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xee91d */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xee942 */
  /* cmp esi, ebx -> jne 0xee910 */
  display_assert((char *)0x002879b8, (char *)0x002859a4, 3472, 0);
  system_exit(0);
  /* cmp esi, ebx -> jne 0xee987 */
  display_assert((char *)0x00287948, (char *)0x002859a4, 3482, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xee99d */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xee9bd */
  /* cmp esi, ebx -> jne 0xee990 */
  display_assert((char *)0x00287914, (char *)0x002859a4, 3484, 0);
  system_exit(0);
  error(0, (char *)0x00286550);

  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0xeea10 */
void playlist_profile_initialize_name(void *widget)
{
  int eax = 0;
  int ebx = 0;

  /* test eax, eax -> jne 0xeea3d */
  display_assert((char *)0x00286184, (char *)0x002859a4, 3510, 0);
  system_exit(0);
  player_ui_edit_profile_is_dirty();
  /* test (char)eax, (char)eax -> je 0xeea94 */
  player_ui_edit_profile_is_default_profile();
  /* test (char)eax, (char)eax -> je 0xeea75 */
  player_ui_edit_profile_name_is_dirty();
  /* test (char)eax, (char)eax -> jne 0xeea75 */
  player_ui_prompt_user_to_rename_edit_profile();
  /* test (char)eax, (char)eax -> jne 0xeeabd */
  error(0, (char *)0x00287c24);
  player_ui_save_profile();
  /* test (char)ebx, (char)ebx -> jne 0xeeabd */
  error(0, (char *)0x00287bec);
  error(0, (char *)0x00287bb0);
  player_ui_end_editing_profile();
  ui_widget_get_last_child((void *)(uintptr_t)eax);
  ui_widget_close((void *)(uintptr_t)eax);

  (void)eax;
  (void)ebx;
}

/* 0xeead0 */
void playlist_profile_initialize_ctf_rules(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  FUN_001c0ed0();
  player_ui_get_edit_player_profile();
  tag_get('aLeD', 0);
  /* relift: cmp word ptr [edi], 2 -> je 0xeeb21 */
  display_assert((char *)0x00287cb0, (char *)0x002859a4, 3576, 0);
  system_exit(0);
  /* relift: cmp dword ptr [edi + 0x3e0], 3 -> je 0xeeb4a */
  display_assert((char *)0x00287c74, (char *)0x002859a4, 3577, 0);
  system_exit(0);
  ui_widget_realloc(0, 0, (char *)0x002859a4, 3581);
  /* test ecx, ecx -> jle 0xeeb7c */
  /* cmp eax, ecx -> jl 0xeeb71 */
  /* test edx, edx -> je 0xeebc1 */
  /* test (int16_t)eax, (int16_t)eax -> jge 0xeeba3 */
  /* cmp eax, ecx -> jle 0xeebb0 */
  error(0, (char *)0x00287c4c);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0xeebe0 */
void FUN_000eebe0(void *widget)
{
  int eax = 0;

  /* test eax, eax -> je 0xeebfe */
  widget_free((void *)(uintptr_t)eax);

  (void)eax;
}

/* 0xeec10 */
void FUN_000eec10(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  player_ui_get_edit_player_profile();
  /* relift: cmp word ptr [esi + 0xe], 2 -> je 0xeec4d */
  display_assert((char *)0x00287d78, (char *)0x002859a4, 3630, 0);
  system_exit(0);
  tag_get(0x44654c61, 0);
  /* relift: cmp word ptr [edi], 2 -> je 0xeec86 */
  display_assert((char *)0x00287cb0, (char *)0x002859a4, 3637, 0);
  system_exit(0);
  display_assert((char *)0x00287c74, (char *)0x002859a4, 3638, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x3c], 0 -> jl 0xeecc7 */
  FUN_001c0ed0();
  /* cmp eax, edx -> jl 0xeece7 */
  display_assert((char *)0x00287d48, (char *)0x002859a4, 3644, 0);
  system_exit(0);
  /* test ebx, ebx -> je 0xeecf9 */
  error(0, (char *)0x00287cf8);

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0xeed10 */
void FUN_000eed10(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp word ptr [esi + 0xe], 0 -> je 0xeed41 */
  display_assert((char *)0x00287e10, (char *)0x002859a4, 3667, 0);
  system_exit(0);
  /* mem[0x0031e494] = 0xffffffff */
  tag_get(0x44654c61, 0);
  /* relift: cmp word ptr [edi], 2 -> je 0xeed87 */
  display_assert((char *)0x00286320, (char *)0x002859a4, 3677, 0);
  system_exit(0);
  display_assert((char *)0x002862e8, (char *)0x002859a4, 3678, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xeedc8 */
  /* cmp edx, ecx -> jl 0xeede8 */
  display_assert((char *)0x00287dc8, (char *)0x002859a4, 3687, 0);
  system_exit(0);
  /* cmp eax, -1 -> je 0xeee27 */
  player_ui_begin_editing_profile();
  display_error_deferred(31, 0, 0, 0);
  ui_play_audio_feedback_sound(0);
  ui_play_audio_feedback_sound(0);
  /* mem[0x0031e494] = 0xffffffff */
  player_ui_end_editing_profile();
  player_ui_get_edit_player_profile();
  virtual_keyboard_set_validation((wchar_t *)(uintptr_t)eax, 24, 0);
  /* test (char)eax, (char)eax -> jne 0xeeea3 */
  error(0, (char *)0x00287e80);
  error(0, (char *)0x00287e54);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0xeeeb0 */
void FUN_000eeeb0(void *widget)
{
  int eax = 0;
  int ebx = 0;

  /* test eax, eax -> jne 0xeeedd */
  display_assert((char *)0x00286184, (char *)0x002859a4, 3759, 0);
  system_exit(0);
  player_ui_edit_profile_is_dirty();
  /* test (char)eax, (char)eax -> je 0xeeef8 */
  player_ui_save_profile();
  /* test (char)ebx, (char)ebx -> jne 0xeef24 */
  error(0, (char *)0x00287ebc);
  player_ui_end_editing_profile();
  ui_widget_get_last_child((void *)(uintptr_t)eax);
  ui_widget_close((void *)(uintptr_t)eax);

  (void)eax;
  (void)ebx;
}

/* 0xeef30 */
void FUN_000eef30(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  player_ui_get_edit_player_profile();
  display_assert((char *)0x00287fd0, (char *)0x002859a4, 3793, 0);
  system_exit(0);
  /* test edi, edi -> je 0xef0ce */
  /* test edi, edi -> jne 0xeef9c */
  display_assert((char *)0x00287fa8, (char *)0x002859a4, 3801, 0);
  system_exit(0);
  /* test esi, esi -> je 0xeefb5 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xeefda */
  /* test esi, esi -> jne 0xeefa3 */
  display_assert((char *)0x00287f78, (char *)0x002859a4, 3803, 0);
  system_exit(0);
  /* cmp eax, 3 -> ja 0xef003 */
  /* test esi, esi -> jne 0xef035 */
  display_assert((char *)0x00287f54, (char *)0x002859a4, 3814, 0);
  system_exit(0);
  /* test esi, esi -> je 0xef04d */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)ecx -> je 0xef072 */
  /* test esi, esi -> jne 0xef040 */
  display_assert((char *)0x00287f24, (char *)0x002859a4, 3816, 0);
  system_exit(0);
  /* cmp eax, 4 -> ja 0xef085 */
  error(0, (char *)0x00287e54);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0xef110 */
void FUN_000ef110(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  player_ui_get_edit_player_profile();
  display_assert((char *)0x002881c4, (char *)0x002859a4, 3844, 0);
  system_exit(0);
  /* cmp edi, ebx -> je 0xef3cc */
  /* cmp edi, ebx -> jne 0xef17c */
  display_assert((char *)0x0028819c, (char *)0x002859a4, 3852, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xef191 */
  /* relift: cmp word ptr [esi + 0xe], 2 -> je 0xef1b1 */
  /* cmp esi, ebx -> jne 0xef183 */
  display_assert((char *)0x0028816c, (char *)0x002859a4, 3854, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0xef1ef */
  display_assert((char *)0x00288144, (char *)0x002859a4, 3863, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xef20d */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)eax -> je 0xef22d */
  /* cmp esi, ebx -> jne 0xef200 */
  display_assert((char *)0x00288114, (char *)0x002859a4, 3865, 0);
  system_exit(0);
  /* cmp (char)eax, (char)ebx -> jbe 0xef246 */
  /* cmp (char)eax, 0xa -> ja 0xef246 */
  /* cmp edi, ebx -> jne 0xef271 */
  display_assert((char *)0x002880e8, (char *)0x002859a4, 3884, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xef28d */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)eax -> je 0xef2ad */
  /* cmp esi, ebx -> jne 0xef280 */
  display_assert((char *)0x002880b4, (char *)0x002859a4, 3886, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0xef2ee */
  display_assert((char *)0x00288088, (char *)0x002859a4, 3895, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xef30d */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)eax -> je 0xef32d */
  /* cmp esi, ebx -> jne 0xef300 */
  display_assert((char *)0x00288050, (char *)0x002859a4, 3897, 0);
  system_exit(0);
  /* cmp esi, ebx -> jne 0xef36b */
  display_assert((char *)0x00288030, (char *)0x002859a4, 3906, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xef384 */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)eax -> je 0xef3a4 */
  /* cmp esi, ebx -> jne 0xef377 */
  display_assert((char *)0x00288004, (char *)0x002859a4, 3908, 0);
  system_exit(0);
  error(0, (char *)0x00287e54);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0xef3f0 */
void FUN_000ef3f0(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  player_ui_get_edit_player_profile();
  display_assert((char *)0x00287fd0, (char *)0x002859a4, 3933, 0);
  system_exit(0);
  /* test edi, edi -> je 0xef584 */
  /* test ebx, ebx -> jne 0xef456 */
  display_assert((char *)0x00287fa8, (char *)0x002859a4, 3941, 0);
  system_exit(0);
  /* test esi, esi -> je 0xef46e */
  /* relift: cmp word ptr [esi + 0xe], 2 -> je 0xef48e */
  /* test esi, esi -> jne 0xef460 */
  display_assert((char *)0x00287f78, (char *)0x002859a4, 3943, 0);
  system_exit(0);
  /* cmp eax, 3 -> ja 0xef4b6 */
  error(0, (char *)0x0028822c);
  display_assert((char *)0x00287f54, (char *)0x002859a4, 3954, 0);
  system_exit(0);
  /* test esi, esi -> je 0xef50d */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)eax -> je 0xef52d */
  /* test esi, esi -> jne 0xef500 */
  display_assert((char *)0x00287f24, (char *)0x002859a4, 3956, 0);
  system_exit(0);
  /* cmp eax, 4 -> ja 0xef56f */
  error(0, (char *)0x00288204);
  error(0, (char *)0x00287e54);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0xef5c0 */
void playlist_profile_initialize_racing_rules(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  player_ui_get_edit_player_profile();
  display_assert((char *)0x002881c4, (char *)0x002859a4, 3984, 0);
  system_exit(0);
  /* cmp edi, ebx -> je 0xef8df */
  /* cmp edi, ebx -> jne 0xef62c */
  display_assert((char *)0x0028819c, (char *)0x002859a4, 3992, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xef641 */
  /* relift: cmp word ptr [esi + 0xe], 2 -> je 0xef661 */
  /* cmp esi, ebx -> jne 0xef633 */
  display_assert((char *)0x0028816c, (char *)0x002859a4, 3994, 0);
  system_exit(0);
  error(0, (char *)0x0028833c);
  /* cmp edi, ebx -> jne 0xef6b3 */
  display_assert((char *)0x00288144, (char *)0x002859a4, 4003, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xef6cd */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)eax -> je 0xef6ed */
  /* cmp esi, ebx -> jne 0xef6c0 */
  display_assert((char *)0x00288114, (char *)0x002859a4, 4005, 0);
  system_exit(0);
  /* cmp eax, ebx -> jl 0xef707 */
  /* cmp eax, 9 -> jg 0xef707 */
  error(0, (char *)0x0028830c);
  /* cmp edi, ebx -> jne 0xef73d */
  display_assert((char *)0x002880e8, (char *)0x002859a4, 4024, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xef75d */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)eax -> je 0xef77d */
  /* cmp esi, ebx -> jne 0xef750 */
  display_assert((char *)0x002880b4, (char *)0x002859a4, 4026, 0);
  system_exit(0);
  error(0, (char *)0x002882d8);
  /* cmp edi, ebx -> jne 0xef7cf */
  display_assert((char *)0x00288088, (char *)0x002859a4, 4035, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xef7ed */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)eax -> je 0xef80d */
  /* cmp esi, ebx -> jne 0xef7e0 */
  display_assert((char *)0x00288050, (char *)0x002859a4, 4037, 0);
  system_exit(0);
  error(0, (char *)0x00288290);
  /* cmp esi, ebx -> jne 0xef85f */
  display_assert((char *)0x00288030, (char *)0x002859a4, 4046, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0xef87d */
  /* relift: cmp word ptr [esi + 0xe], (int16_t)eax -> je 0xef89d */
  /* cmp esi, ebx -> jne 0xef870 */
  display_assert((char *)0x00288004, (char *)0x002859a4, 4048, 0);
  system_exit(0);
  error(0, (char *)0x00288258);
  error(0, (char *)0x00287e54);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0xef900 */
void FUN_000ef900(void *widget)
{
  int esi = 0;

  /* test esi, esi -> je 0xef91a */
  /* test (int16_t)eax, (int16_t)eax -> jl 0xef91a */
  /* cmp (int16_t)eax, 4 -> jl 0xef93a */
  display_assert((char *)0x00288368, (char *)0x002859a4, 4073, 0);
  system_exit(0);
  network_game_client_local_player_quit(0);
  set_game_connection(0);
  main_menu_switch_to_single_player();
  player_ui_remember_player1_profile(0);

  (void)esi;
}

/* 0xef970 */
void FUN_000ef970(void *widget)
{
  int eax = 0;
  int edx = 0;
  int edi = 0;

  tag_get(0x44654c61, 0);
  /* relift: cmp word ptr [eax], 0 -> jne 0xef996 */
  /* relift: cmp dword ptr [eax + 0x3e0], 3 -> jge 0xef9b6 */
  display_assert((char *)0x00286500, (char *)0x002859a4, 4111, 0);
  system_exit(0);
  tag_get(0x44654c61, 0);
  /* relift: cmp word ptr [edi], 2 -> je 0xef9f2 */
  display_assert((char *)0x00286070, (char *)0x002859a4, 4114, 0);
  system_exit(0);
  display_assert((char *)0x00286034, (char *)0x002859a4, 4115, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xefa33 */
  /* cmp eax, edx -> jl 0xefa53 */
  display_assert((char *)0x00285fe0, (char *)0x002859a4, 4124, 0);
  system_exit(0);
  /* mem[0x0031e494] = eax */
  ui_play_audio_feedback_sound(0);

  (void)eax;
  (void)edx;
  (void)edi;
}

/* 0xefa80 */
void FUN_000efa80(void *widget)
{
  int eax = 0;
  int edx = 0;
  int edi = 0;

  tag_get(0x44654c61, 0);
  /* relift: cmp word ptr [eax], 0 -> jne 0xefaa9 */
  /* relift: cmp dword ptr [eax + 0x3e0], 3 -> jge 0xefac9 */
  display_assert((char *)0x00288430, (char *)0x002859a4, 4157, 0);
  system_exit(0);
  tag_get(0x44654c61, 0);
  /* relift: cmp word ptr [edi], 2 -> je 0xefb05 */
  display_assert((char *)0x002883e8, (char *)0x002859a4, 4160, 0);
  system_exit(0);
  display_assert((char *)0x002883ac, (char *)0x002859a4, 4161, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xefb46 */
  /* cmp eax, edx -> jl 0xefb66 */
  display_assert((char *)0x00285fe0, (char *)0x002859a4, 4169, 0);
  system_exit(0);
  /* mem[0x0031e494] = eax */
  /* test eax, 0x40000000 -> je 0xefb9e */
  display_error_deferred(26, 0, 0, 0);
  ui_play_audio_feedback_sound(0);
  ui_play_audio_feedback_sound(0);
  /* test eax, 0x40000000 -> jne 0xefbf3 */
  FUN_001c0d70(0);
  error(0, (char *)0x002884c0);
  error(0, (char *)0x00288480);
  FUN_001c1f70();
  error(0, (char *)0x002884e8);
  /* mem[0x0031e494] = 0xffffffff */

  (void)eax;
  (void)edx;
  (void)edi;
}

/* 0xefc60 */
void FUN_000efc60(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int ebp = 0;

  /* cmp (int16_t)eax, 4 -> jl 0xefc9f */
  display_assert((char *)0x002885a8, (char *)0x002859a4, 4272, 0);
  system_exit(0);
  saved_game_file_get_useable_untitled_profile_name();
  /* relift: cmp word ptr [ebp - 0x16c], 0 -> je 0xefda6 */
  FUN_001c1e20();
  player_ui_begin_editing_profile();
  player_ui_get_edit_playlist_profile();
  /* test ebx, ebx -> je 0xefd7f */
  game_engine_slayer_default((void *)(uintptr_t)edx);
  csmemcpy((void *)0, (void *)0, 0);
  ustrncpy((wchar_t *)(uintptr_t)ebx, (wchar_t *)(uintptr_t)ecx, 11);
  virtual_keyboard_set_validation((wchar_t *)(uintptr_t)ebx, 24, 0);
  FUN_001c4da0();
  /* test (char)eax, (char)eax -> je 0xefd78 */
  saved_game_file_remember_last_used_multiplayer_variant_directory();
  error(0, (char *)0x00288574);
  player_ui_end_editing_profile();
  error(0, (char *)0x0028853c);
  error(0, (char *)0x00288514);
  /* test (char)ebx, (char)ebx -> jne 0xefdd2 */
  display_error_deferred(38, 0, 0, 0);
  ui_play_audio_feedback_sound(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)ebp;
}

/* 0xefde0 */
void FUN_000efde0(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int ebp = 0;

  /* cmp (int16_t)esi, -1 -> jne 0xefdfc */
  saved_game_file_get_useable_untitled_profile_name();
  /* relift: cmp word ptr [ebp - 0x100], 0 -> je 0xefeb0 */
  FUN_001c1720();
  /* cmp eax, -1 -> je 0xefe9f */
  player_ui_begin_editing_profile();
  player_ui_get_edit_player_profile();
  /* test esi, esi -> je 0xefe89 */
  ustrncpy((wchar_t *)(uintptr_t)esi, (wchar_t *)(uintptr_t)eax, 11);
  virtual_keyboard_set_validation((wchar_t *)(uintptr_t)esi, 24, 0);
  /* test (char)ebx, (char)ebx -> jne 0xefe81 */
  display_error_deferred(37, 0, 0, 0);
  ui_play_audio_feedback_sound(0);
  error(0, (char *)0x0028860c);
  player_ui_end_editing_profile();
  error(0, (char *)0x002885e4);
  error(0, (char *)0x00288514);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)ebp;
}

/* 0xefed0 */
void FUN_000efed0(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;
  int ebp = 0;

  network_game_client_get();
  /* test ebx, ebx -> je 0xeff58 */
  network_game_client_get_machine_index((void *)(uintptr_t)ebx);
  FUN_00124c40((void *)(uintptr_t)ebx);
  network_player_is_valid((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0xeff28 */
  /* relift: cmp (int16_t)ecx, word ptr [ebp - 4] -> jne 0xeff28 */
  /* relift: cmp (int16_t)edx, word ptr [eax + 2] -> je 0xeff3a */
  /* cmp edi, 0x10 -> jl 0xeff00 */
  FUN_00125b90((void *)(uintptr_t)ebx, 0);
  /* test (char)eax, (char)eax -> jne 0xeff58 */
  error(0, (char *)0x00288638);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)ebp;
}

/* 0xeff70 */
void FUN_000eff70(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;
  int ebp = 0;

  network_game_client_get();
  /* test ebx, ebx -> je 0xefff8 */
  network_game_client_get_machine_index((void *)(uintptr_t)ebx);
  FUN_00124c40((void *)(uintptr_t)ebx);
  network_player_is_valid((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0xeffc8 */
  /* relift: cmp (int16_t)ecx, word ptr [ebp - 4] -> jne 0xeffc8 */
  /* relift: cmp (int16_t)edx, word ptr [eax + 2] -> je 0xeffda */
  /* cmp edi, 0x10 -> jl 0xeffa0 */
  FUN_00125b90((void *)(uintptr_t)ebx, 0);
  /* test (char)eax, (char)eax -> jne 0xefff8 */
  error(0, (char *)0x00288638);
  network_game_server_get();
  /* test eax, eax -> je 0xf0022 */
  network_game_server_open_game((void *)(uintptr_t)eax);
  network_game_server_get();
  /* test eax, eax -> je 0xf0044 */
  network_game_server_pause_countdown((void *)(uintptr_t)eax, 0);
  network_game_server_get();
  /* test eax, eax -> je 0xf0064 */
  network_game_server_pause_countdown((void *)(uintptr_t)eax, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)ebp;
}

/* 0xf0070 */
void FUN_000f0070(void *widget)
{
  int eax = 0;

  xbox_demos_available();
  /* test (char)eax, (char)eax -> jne 0xf0087 */
  main_run_demos();
  player_ui_reset_single_player_local_player_controllers();

  (void)eax;
}

/* 0xf00b0 */
void FUN_000f00b0(void *widget)
{
  int esi = 0;

  /* test esi, esi -> jne 0xf00db */
  display_assert((char *)0x00288670, (char *)0x002859a4, 4537, 0);
  system_exit(0);
  player_ui_set_single_player_local_player_controller();

  (void)esi;
}

/* 0xf0100 */
void FUN_000f0100(void *widget)
{
  int esi = 0;

  /* test esi, esi -> jne 0xf012b */
  display_assert((char *)0x00288670, (char *)0x002859a4, 4551, 0);
  system_exit(0);
  player_ui_get_single_player_local_player_controller(0);
  /* cmp (int16_t)esi, (int16_t)eax -> jne 0xf0159 */
  ui_widget_display_error(18, 0, 0, 0);
  player_ui_set_single_player_local_player_controller();

  (void)esi;
}

/* 0xf0170 */
void FUN_000f0170(void *widget)
{
  int ebx = 0;

  transport_network_available();
  display_assert((char *)0x00286184, (char *)0x002859a4, 4575, 0);
  system_exit(0);
  /* test (char)ebx, (char)ebx -> jne 0xf01bc */
  ui_widget_display_error(0, 0, 0, 0);

  (void)ebx;
}

/* 0xf01d0 */
void player_profile_end_editing(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* relift: cmp word ptr [esi + 0xe], 3 -> je 0xf0201 */
  display_assert((char *)0x002886c8, (char *)0x002859a4, 4593, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x44], 0 -> jne 0xf0238 */
  network_game_client_get();
  /* test eax, eax -> je 0xf0247 */
  network_game_client_get_state((void *)(uintptr_t)eax, (void *)(uintptr_t)ecx);
  /* test (int16_t)eax, (int16_t)eax -> jne 0xf0247 */
  FUN_000E9D40();
  error(0, (char *)0x00288680);

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0xf0250 */
void player_profile_save_changes(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  network_game_client_get();
  network_game_client_get_state((void *)(uintptr_t)esi, (void *)(uintptr_t)eax);
  /* cmp (int16_t)eax, 2 -> jne 0xf03aa */
  network_game_client_get_machine_index((void *)(uintptr_t)esi);
  network_game_client_get_local_machine_index();
  /* cmp (int16_t)ebx, -1 -> je 0xf03c1 */
  network_player_is_valid((void *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> je 0xf0304 */
  /* cmp (int16_t)ecx, (int16_t)ebx -> jne 0xf0304 */
  /* relift: cmp (int16_t)edx, word ptr [eax + 2] -> jne 0xf0304 */
  /* test edi, edi -> je 0xf0302 */
  display_assert((char *)0x00288768, (char *)0x002859a4, 4646, 0);
  system_exit(0);
  /* test esi, esi -> jle 0xf03c1 */
  /* test edi, edi -> je 0xf034d */
  network_game_client_request_remove_player((void *)(uintptr_t)ecx, (void *)(uintptr_t)edi);
  /* test (char)eax, (char)eax -> jne 0xf033f */
  error(0, (char *)0x00288744);
  player_ui_clear_multiplayer_autojoin_for_local_player();
  /* cmp esi, 1 -> jne 0xf03a1 */
  network_game_server_get();
  /* test eax, eax -> je 0xf0387 */
  network_game_accept_remote_connections();
  /* cmp (char)eax, 1 -> jne 0xf0387 */
  network_game_server_get();
  /* test eax, eax -> je 0xf0391 */
  network_game_server_pause_countdown((void *)(uintptr_t)eax, esi);
  player_ui_autojoin_players_to_next_multiplayer_game();
  dispose_global_network_game_server();
  dispose_global_network_game_client();
  player_ui_autojoin_players_to_next_multiplayer_game();
  error(0, (char *)0x002886f0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0xf03d0 */
void FUN_000F03D0(void *widget)
{
  int eax = 0;

  player_ui_get_edit_player_profile();
  /* test eax, eax -> jne 0xf0413 */
  player_ui_get_edit_playlist_profile();
  /* test eax, eax -> jne 0xf0413 */
  ui_widget_get_last_child((void *)(uintptr_t)eax);
  error(0, (char *)0x0028878c);
  FUN_000e0570();

  (void)eax;
}

/* 0xf0430 */
void player_profile_initialize_advanced_controller_settings(void *widget)
{
  int ecx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0xf0461 */
  display_assert((char *)0x00286184, (char *)0x002859a4, 4741, 0);
  system_exit(0);
  saved_game_file_get_useable_untitled_profile_name();
  ustrncpy((wchar_t *)0x0046ccd0, (wchar_t *)(uintptr_t)ecx, 11);
  virtual_keyboard_set_validation((wchar_t *)0x0046ccd0, 24, 0);
  error(0, (char *)0x002887d0);

  (void)ecx;
  (void)esi;
}

/* 0xf04c0 */
void FUN_000f04c0(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  /* relift: cmp word ptr [0x31e4fc], -1 -> je 0xf0612 */
  FUN_000f5650();
  /* test (char)eax, (char)eax -> je 0xf0608 */
  /* relift: cmp word ptr [0x46ccd0], (int16_t)ebx -> je 0xf05f2 */
  player_ui_set_single_player_local_player_controller();
  FUN_001c1720();
  /* cmp esi, -1 -> jne 0xf056a */
  saved_game_file_get_useable_untitled_profile_name();
  ustrncpy((wchar_t *)0x0046ccd0, (wchar_t *)(uintptr_t)eax, 11);
  FUN_001c1720();
  /* cmp esi, -1 -> je 0xf05eb */
  player_profile_new();
  /* test (char)eax, (char)eax -> je 0xf05b0 */
  player_ui_set_active_player_profile();
  main_set_map_name((char *)(uintptr_t)ecx);
  main_defer_map_map_change();
  error(0, (char *)0x0028886c);
  main_goto_main_menu();
  display_error_deferred(37, 0, 0, ebx);
  ui_play_audio_feedback_sound(0);
  error(0, (char *)0x00288818);
  ui_play_audio_feedback_sound(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}

/* 0xf0620 */
void FUN_000f0620(void *widget)
{
  ui_widgets_pop_stack(0);
}

/* 0xf0640 */
void FUN_000f0640(void *widget)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x002888c4, (char *)0x002859a4, 4860, 0);
  system_exit(0);
  /* relift: cmp byte ptr [0x46ce3b], 1 -> jne 0xf06da */
  main_get_map_name();
  crt_stricmp((char *)0x0046cd38, (char *)(uintptr_t)eax);
  /* test eax, eax -> jne 0xf06da */
  widget_instance_get_nth_child((void *)(uintptr_t)esi, 0);
  /* test edi, edi -> jne 0xf06c6 */
  display_assert((char *)0x0028889c, (char *)0x002859a4, 4865, 0);
  system_exit(0);
  widget_instance_get_nth_child((void *)(uintptr_t)esi, 0);
  /* test edi, edi -> jne 0xf070b */
  display_assert((char *)0x0028889c, (char *)0x002859a4, 4871, 0);
  system_exit(0);
  ui_widget_get_attract_mode_flag();
  /* test (char)eax, (char)eax -> je 0xf072e */
  ui_widget_stop_attract_mode();

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0xf0740 */
void FUN_000f0740(void *widget)
{
  int ecx = 0;
  int ebp = 0;

  FUN_001c0d50();
  /* relift: cmp word ptr [ebp - 4], 0 -> jle 0xf076e */
  player_profile_initialize_advanced_controller_settings((void *)(uintptr_t)ecx);

  (void)ecx;
  (void)ebp;
}

/* 0xf0790 */
void FUN_000f0790(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* relift: cmp word ptr [0x31fa94], 2 -> jl 0xf07cb */
  csmemset((void *)0x0046cd38, 0, 262);
  FUN_000e98c0((void *)(uintptr_t)edx);
  player_ui_get_active_player_profile_index();
  csmemset((void *)0x0046cce8, 0, 80);
  /* cmp esi, eax -> je 0xf0823 */
  csmemset((void *)0x0046cd38, 0, 262);
  game_state_test_persistent_storage((char *)0x0046cd38, (void *)0x0046ce38, 0x0046ce3c);
  /* mem[0x0031e4c0] = esi */
  player_ui_get_active_player_profile();
  player_profile_save_last_level_played(0, 0, 0);
  /* test (char)ecx, (char)ecx -> jne 0xf0872 */
  /* cmp eax, edx -> je 0xf0872 */
  /* test eax, eax -> jne 0xf08a7 */
  /* cmp eax, 0xa -> jl 0xf0850 */
  tag_get('aLeD', 0);
  /* relift: cmp word ptr [esi], 2 -> je 0xf08e8 */
  display_assert((char *)0x00285a18, (char *)0x002859a4, 603, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0x3e0], 3 -> je 0xf0911 */
  display_assert((char *)0x002859e4, (char *)0x002859a4, 604, 0);
  system_exit(0);
  player_ui_get_last_single_player_level_played();
  /* test (int16_t)eax, (int16_t)eax -> jge 0xf0931 */
  player_ui_get_last_single_player_level_played();
  /* cmp (int16_t)eax, 9 -> jle 0xf0948 */
  player_ui_get_last_single_player_level_played();
  /* relift: cmp byte ptr [0x46ce3b], 1 -> jne 0xf09d6 */
  crt_stricmp((char *)0x0046cd38, (char *)(uintptr_t)ecx);
  /* test eax, eax -> je 0xf0991 */
  /* cmp ebx, 0xa -> jl 0xf0970 */
  /* relift: cmp byte ptr [0x46ce3c], 1 -> jne 0xf0a21 */
  player_ui_get_active_player_profile_index();
  /* cmp esi, -1 -> je 0xf0a21 */
  /* relift: cmp dword ptr [0x31e4c4], -1 -> jne 0xf0a17 */
  display_error_deferred(39, 0, 0, 0);
  /* mem[0x0031e4c4] = esi */
  /* mem[0x0031e4c4] = 0xffffffff */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0xf0aa0 */
void FUN_000f0aa0(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  tag_get(0x44654c61, 0);
  /* test eax, eax -> je 0xf0acc */
  /* test eax, eax -> jne 0xf0aec */
  display_assert((char *)0x00288a5c, (char *)0x00288938, 300, 0);
  system_exit(0);
  /* relift: cmp dword ptr [edi + 0x3e0], 2 -> je 0xf0b15 */
  display_assert((char *)0x00288a24, (char *)0x00288938, 301, 0);
  system_exit(0);
  /* test eax, eax -> je 0xf0b42 */
  /* cmp eax, esi -> je 0xf0b3c */
  /* test eax, eax -> jne 0xf0b30 */
  /* cmp (int16_t)edi, -1 -> je 0xf0b9e */
  /* relift: cmp word ptr [ebx + 0xe], 0 -> je 0xf0b69 */
  display_assert((char *)0x002889d0, (char *)0x00288938, 312, 0);
  system_exit(0);
  /* relift: cmp word ptr [ecx + 0xe], 1 -> je 0xf0b93 */
  display_assert((char *)0x00288978, (char *)0x00288938, 313, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0xf0bb0 */
void FUN_000f0bb0(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> je 0xf0bca */
  /* test eax, eax -> je 0xf0bca */
  /* test eax, eax -> jne 0xf0bea */
  display_assert((char *)0x00288a5c, (char *)0x00288938, 333, 0);
  system_exit(0);
  /* test eax, eax -> je 0xf0c08 */
  /* cmp eax, ecx -> je 0xf0c02 */
  /* test eax, eax -> jne 0xf0bf6 */
  /* cmp (int16_t)esi, -1 -> je 0xf0c57 */
  tag_get('aLeD', 0);
  /* cmp ecx, 2 -> je 0xf0c46 */
  display_assert((char *)0x00288aa0, (char *)0x00288938, 347, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0xf0c60 */
void FUN_000f0c60(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> je 0xf0c7a */
  /* test eax, eax -> je 0xf0c7a */
  /* test eax, eax -> jne 0xf0c9a */
  display_assert((char *)0x00288a5c, (char *)0x00288938, 371, 0);
  system_exit(0);
  /* test eax, eax -> je 0xf0cb8 */
  /* cmp eax, ecx -> je 0xf0cb2 */
  /* test eax, eax -> jne 0xf0ca6 */
  /* cmp (int16_t)esi, -1 -> je 0xf0d07 */
  tag_get('aLeD', 0);
  /* cmp ecx, 2 -> je 0xf0cf6 */
  display_assert((char *)0x00288aa0, (char *)0x00288938, 385, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0xf0d10 */
void playlist_settings_menu_update_extended_description(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test esi, esi -> je 0xf0d37 */
  /* test eax, eax -> je 0xf0d37 */
  /* test eax, eax -> je 0xf0d37 */
  /* test eax, eax -> je 0xf0d37 */
  /* test ecx, ecx -> jne 0xf0d57 */
  display_assert((char *)0x00288a5c, (char *)0x00288938, 422, 0);
  system_exit(0);
  /* test eax, eax -> je 0xf0d75 */
  /* cmp eax, edx -> je 0xf0d6f */
  /* test eax, eax -> jne 0xf0d63 */
  /* cmp (int16_t)ecx, -1 -> je 0xf0d8c */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0xf0d90 */
void FUN_000f0d90(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  tag_get(0x44654c61, 0);
  /* test eax, eax -> je 0xf0dbc */
  /* test eax, eax -> jne 0xf0ddc */
  display_assert((char *)0x00288a5c, (char *)0x00288938, 567, 0);
  system_exit(0);
  /* relift: cmp dword ptr [edi + 0x3e0], 2 -> je 0xf0e05 */
  display_assert((char *)0x00288ba0, (char *)0x00288938, 568, 0);
  system_exit(0);
  /* test eax, eax -> je 0xf0e32 */
  /* cmp eax, esi -> je 0xf0e2c */
  /* test eax, eax -> jne 0xf0e20 */
  /* cmp (int16_t)edi, -1 -> je 0xf0e8e */
  /* relift: cmp word ptr [ebx + 0xe], 0 -> je 0xf0e59 */
  display_assert((char *)0x00288b50, (char *)0x00288938, 579, 0);
  system_exit(0);
  /* relift: cmp word ptr [ecx + 0xe], 1 -> je 0xf0e83 */
  display_assert((char *)0x00288b00, (char *)0x00288938, 580, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* FUN_000f0f30 (0xf0f30) — XBE naked draft (batch 105). */
#if defined(__clang__)
static void * (*const bf0f30_c12a240)(void) = network_game_client_get;
static void *(*const bf0f30_memset)(void *, int, unsigned int) = csmemset;
static void *(*const bf0f30_tag)(int, int) = tag_get;
static void * (*const bf0f30_c124c80)(void *client) = FUN_00124c80;
static void (*const bf0f30_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf0f30_exitfn)(int) = system_exit;
static char (*const bf0f30_c125cb0)(void *game) = network_game_client_advertised_game_is_valid;
static void * (*const bf0f30_ce3d20)(int a1, unsigned short a2, const char *a3, unsigned int a4) = ui_widget_realloc;
static wchar_t * (*const bf0f30_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;
static int (*const bf0f30_c1b9930)(int group_tag, const char *name, ...) = tag_loaded;
static int (*const bf0f30_c19d420)(int param_1, int param_2) = FUN_0019d420;
static void (*const bf0f30_c19e9f0)(wchar_t *buffer, int buffer_size, const wchar_t *format, ...) = unicode_sprintf;
static unsigned int (*const bf0f30_c8e370)(void) = system_milliseconds;
static char * (*const bf0f30_c1d9690)(const char *haystack, const char *needle) = crt_strstr;

__attribute__((naked, noinline))
void FUN_000f0f30(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x28, %%esp\n\t"
      "pushl %%esi\n\t"
      "call *%[c12a240]\n\t"
      "pushl $0x24\n\t"
      "pushl $0\n\t"
      "pushl $0x46ce40\n\t"
      "movl %%eax, %%esi\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000f0f30_70\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c124c80]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $3, (%%edi)\n\t"
      "movl %%eax, %%esi\n\t"
      "jne .LFUN_000f0f30_1\n\t"
      "cmpl $9, 0x3e0(%%edi)\n\t"
      "je .LFUN_000f0f30_2\n\t"
      ".LFUN_000f0f30_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x297\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288dd4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f0f30_2:\n\t"
      "movl %%esi, %%edi\n\t"
      "movl $9, %%ebx\n\t"
      ".LFUN_000f0f30_3:\n\t"
      "pushl %%edi\n\t"
      "call *%[c125cb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f0f30_4\n\t"
      "cmpw $0, 0xde(%%edi)\n\t"
      "jne .LFUN_000f0f30_4\n\t"
      "movb 0xe0(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f0f30_4\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl %%edi, 0x46ce40(,%%eax,4)\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".LFUN_000f0f30_4:\n\t"
      "addl $0xe4, %%edi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_000f0f30_3\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "movl $9, %%edi\n\t"
      ".LFUN_000f0f30_5:\n\t"
      "pushl %%esi\n\t"
      "call *%[c125cb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f0f30_6\n\t"
      "cmpw $0, 0xde(%%esi)\n\t"
      "jne .LFUN_000f0f30_6\n\t"
      "movb 0xe0(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f0f30_6\n\t"
      "movl %%esi, 0x46ce40(,%%ebx,4)\n\t"
      "incl %%ebx\n\t"
      ".LFUN_000f0f30_6:\n\t"
      "addl $0xe4, %%esi\n\t"
      "decl %%edi\n\t"
      "jne .LFUN_000f0f30_5\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movswl 0x3c(%%ebx), %%eax\n\t"
      "leal -0x1(%%edx), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl $0x46ce40, 0x40(%%ebx)\n\t"
      "movw %%dx, 0x44(%%ebx)\n\t"
      "jle .LFUN_000f0f30_7\n\t"
      "movl %%ecx, %%eax\n\t"
      ".LFUN_000f0f30_7:\n\t"
      "movl 0x34(%%ebx), %%esi\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%esi, %%esi\n\t"
      "movw %%ax, 0x3c(%%ebx)\n\t"
      "je .LFUN_000f0f30_12\n\t"
      ".LFUN_000f0f30_8:\n\t"
      "cmpl %%edx, %%edi\n\t"
      "jge .LFUN_000f0f30_12\n\t"
      "movl 0x3c(%%esi), %%edx\n\t"
      "pushl $0x2c5\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x40\n\t"
      "pushl %%edx\n\t"
      "call *%[ce3d20]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "je .LFUN_000f0f30_11\n\t"
      "movl 0x46ce40(,%%edi,4), %%ecx\n\t"
      "cmpb $1, 0xe0(%%ecx)\n\t"
      "jne .LFUN_000f0f30_9\n\t"
      "pushl $0x1f\n\t"
      "addl $0x30, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c19dc90]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_000f0f30_10\n\t"
      ".LFUN_000f0f30_9:\n\t"
      "pushl $0x288db8\n\t"
      "pushl $0x75737472\n\t"
      "call *%[c1b9930]\n\t"
      "pushl $0x13\n\t"
      "pushl %%eax\n\t"
      "call *%[c19d420]\n\t"
      "movl 0x46ce40(,%%edi,4), %%ecx\n\t"
      "movl 0x3c(%%esi), %%edx\n\t"
      "addl $0x30, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x288dac\n\t"
      "pushl $0x1f\n\t"
      "pushl %%edx\n\t"
      "call *%[c19e9f0]\n\t"
      "addl $0x24, %%esp\n\t"
      ".LFUN_000f0f30_10:\n\t"
      "movl 0x3c(%%esi), %%eax\n\t"
      "movw $0, 0x3e(%%eax)\n\t"
      ".LFUN_000f0f30_11:\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "incl %%edi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000f0f30_8\n\t"
      ".LFUN_000f0f30_12:\n\t"
      "testl %%edx, %%edx\n\t"
      "jle .LFUN_000f0f30_13\n\t"
      "cmpw $0, 0x3c(%%ebx)\n\t"
      "jge .LFUN_000f0f30_13\n\t"
      "movw $0, 0x3c(%%ebx)\n\t"
      ".LFUN_000f0f30_13:\n\t"
      "call *%[c8e370]\n\t"
      "subl 0x18(%%ebx), %%eax\n\t"
      "movl 0x48(%%ebx), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x44654c61\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $5, %%ecx\n\t"
      "je .LFUN_000f0f30_14\n\t"
      "pushl $1\n\t"
      "pushl $0x2f7\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288d68\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f0f30_14:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x48(%%eax), %%ecx\n\t"
      "movl 0x34(%%ecx), %%eax\n\t"
      "movl 0x2c(%%eax), %%ebx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x2c(%%ebx), %%eax\n\t"
      "movl 0x34(%%eax), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "movl 0x2c(%%eax), %%edx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl %%edi, -0x14(%%ebp)\n\t"
      "movl $1, %%esi\n\t"
      "je .LFUN_000f0f30_15\n\t"
      "cmpw %%si, 0xe(%%edi)\n\t"
      "je .LFUN_000f0f30_16\n\t"
      ".LFUN_000f0f30_15:\n\t"
      "pushl %%esi\n\t"
      "pushl $0x2ff\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288d40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f0f30_16:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%edi, -0x18(%%ebp)\n\t"
      "je .LFUN_000f0f30_17\n\t"
      "cmpw %%si, 0xe(%%edi)\n\t"
      "je .LFUN_000f0f30_18\n\t"
      ".LFUN_000f0f30_17:\n\t"
      "pushl %%esi\n\t"
      "pushl $0x301\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288d24\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f0f30_18:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "je .LFUN_000f0f30_19\n\t"
      "cmpw %%si, 0xe(%%edi)\n\t"
      "je .LFUN_000f0f30_20\n\t"
      ".LFUN_000f0f30_19:\n\t"
      "pushl %%esi\n\t"
      "pushl $0x303\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288d08\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f0f30_20:\n\t"
      "movl 0x2c(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%edi, -0x20(%%ebp)\n\t"
      "je .LFUN_000f0f30_21\n\t"
      "cmpw %%si, 0xe(%%edi)\n\t"
      "je .LFUN_000f0f30_22\n\t"
      ".LFUN_000f0f30_21:\n\t"
      "pushl %%esi\n\t"
      "pushl $0x305\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288ce8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f0f30_22:\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, -0x24(%%ebp)\n\t"
      "je .LFUN_000f0f30_23\n\t"
      "cmpw $1, 0xe(%%esi)\n\t"
      "je .LFUN_000f0f30_24\n\t"
      ".LFUN_000f0f30_23:\n\t"
      "pushl $1\n\t"
      "pushl $0x307\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288cc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f0f30_24:\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "je .LFUN_000f0f30_25\n\t"
      "cmpw $1, 0xe(%%eax)\n\t"
      "je .LFUN_000f0f30_26\n\t"
      ".LFUN_000f0f30_25:\n\t"
      "pushl $1\n\t"
      "pushl $0x309\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288ca0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f0f30_26:\n\t"
      "movl 0x2c(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "je .LFUN_000f0f30_27\n\t"
      "cmpw $1, 0xe(%%eax)\n\t"
      "je .LFUN_000f0f30_28\n\t"
      ".LFUN_000f0f30_27:\n\t"
      "pushl $1\n\t"
      "pushl $0x30b\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288c7c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f0f30_28:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movw 0x3c(%%eax), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_000f0f30_66\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movl 0x46ce40(,%%ecx,4), %%esi\n\t"
      "movswl 0xd4(%%esi), %%eax\n\t"
      "decl %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .LFUN_000f0f30_34\n\t"
      "jmp *.LFUN_000f0f30_jt0(,%%eax,4)\n\t"
      ".LFUN_000f0f30_29:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movw $0, 0x50(%%edx)\n\t"
      "jmp .LFUN_000f0f30_35\n\t"
      ".LFUN_000f0f30_30:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movw $2, 0x50(%%eax)\n\t"
      "jmp .LFUN_000f0f30_35\n\t"
      ".LFUN_000f0f30_31:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movw $3, 0x50(%%ecx)\n\t"
      "jmp .LFUN_000f0f30_35\n\t"
      ".LFUN_000f0f30_32:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movw $1, 0x50(%%edx)\n\t"
      "jmp .LFUN_000f0f30_35\n\t"
      ".LFUN_000f0f30_33:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movw $4, 0x50(%%eax)\n\t"
      "jmp .LFUN_000f0f30_35\n\t"
      ".LFUN_000f0f30_34:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movw $5, 0x50(%%ecx)\n\t"
      ".LFUN_000f0f30_35:\n\t"
      "leal 0x54(%%esi), %%edi\n\t"
      "pushl $0x288c70\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_36\n\t"
      "movw $0, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_36:\n\t"
      "pushl $0x288c64\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_37\n\t"
      "movw $1, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_37:\n\t"
      "pushl $0x288c58\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_38\n\t"
      "movw $2, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_38:\n\t"
      "pushl $0x288c50\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_39\n\t"
      "movw $3, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_39:\n\t"
      "pushl $0x288c44\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_40\n\t"
      "movw $4, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_40:\n\t"
      "pushl $0x288c38\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_41\n\t"
      "movw $5, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_41:\n\t"
      "pushl $0x288c2c\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_42\n\t"
      "movw $6, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_42:\n\t"
      "pushl $0x288c20\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_43\n\t"
      "movw $7, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_43:\n\t"
      "pushl $0x288c10\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_44\n\t"
      "movw $8, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_44:\n\t"
      "pushl $0x288c04\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_45\n\t"
      "movw $9, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_45:\n\t"
      "pushl $0x288bfc\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_46\n\t"
      "movw $0xa, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_46:\n\t"
      "pushl $0x288bf4\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_47\n\t"
      "movw $0xb, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_47:\n\t"
      "pushl $0x288bec\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f0f30_48\n\t"
      "movw $0xc, 0x50(%%ebx)\n\t"
      "jmp .LFUN_000f0f30_49\n\t"
      ".LFUN_000f0f30_48:\n\t"
      "movw $0xd, 0x50(%%ebx)\n\t"
      ".LFUN_000f0f30_49:\n\t"
      "movb 0xe0(%%esi), %%al\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpb $1, %%al\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "setne %%dl\n\t"
      "addl $0x14, %%edx\n\t"
      "movw %%dx, 0x40(%%eax)\n\t"
      "movw 0x50(%%ebx), %%cx\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movw %%cx, 0x40(%%edx)\n\t"
      "movswl 0xd4(%%esi), %%eax\n\t"
      "decl %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .LFUN_000f0f30_55\n\t"
      "jmp *.LFUN_000f0f30_jt1(,%%eax,4)\n\t"
      ".LFUN_000f0f30_50:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movw $3, 0x40(%%eax)\n\t"
      "jmp .LFUN_000f0f30_56\n\t"
      ".LFUN_000f0f30_51:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movw $4, 0x40(%%ecx)\n\t"
      "jmp .LFUN_000f0f30_56\n\t"
      ".LFUN_000f0f30_52:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movw $5, 0x40(%%edx)\n\t"
      "jmp .LFUN_000f0f30_56\n\t"
      ".LFUN_000f0f30_53:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movw $6, 0x40(%%eax)\n\t"
      "jmp .LFUN_000f0f30_56\n\t"
      ".LFUN_000f0f30_54:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movw $7, 0x40(%%ecx)\n\t"
      "jmp .LFUN_000f0f30_56\n\t"
      ".LFUN_000f0f30_55:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movw $8, 0x40(%%edx)\n\t"
      ".LFUN_000f0f30_56:\n\t"
      "movb 0xe2(%%esi), %%bl\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl -0x24(%%ebp), %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpb $1, %%bl\n\t"
      "setne %%al\n\t"
      "pushl $0x364\n\t"
      "pushl $0x288938\n\t"
      "pushl $8\n\t"
      "addl $0xc, %%eax\n\t"
      "movw %%ax, 0x40(%%ecx)\n\t"
      "movl 0x3c(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[ce3d20]\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "movl %%eax, 0x3c(%%edi)\n\t"
      "je .LFUN_000f0f30_57\n\t"
      "movzwl 0xd8(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x26c118\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[c19e9f0]\n\t"
      "movl 0x3c(%%edi), %%edx\n\t"
      "addl $0x10, %%esp\n\t"
      "movw %%bx, 0x6(%%edx)\n\t"
      ".LFUN_000f0f30_57:\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl 0x3c(%%edi), %%eax\n\t"
      "pushl $0x369\n\t"
      "pushl $0x288938\n\t"
      "pushl $8\n\t"
      "pushl %%eax\n\t"
      "call *%[ce3d20]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "movl %%eax, 0x3c(%%edi)\n\t"
      "je .LFUN_000f0f30_58\n\t"
      "movswl 0xdc(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x26c118\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[c19e9f0]\n\t"
      "movl 0x3c(%%edi), %%edx\n\t"
      "addl $0x10, %%esp\n\t"
      "movw %%bx, 0x6(%%edx)\n\t"
      ".LFUN_000f0f30_58:\n\t"
      "movswl 0xd4(%%esi), %%eax\n\t"
      "decl %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .LFUN_000f0f30_64\n\t"
      "jmp *.LFUN_000f0f30_jt2(,%%eax,4)\n\t"
      ".LFUN_000f0f30_59:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movw $0x16, 0x40(%%eax)\n\t"
      "jmp .LFUN_000f0f30_65\n\t"
      ".LFUN_000f0f30_60:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movw $0x18, 0x40(%%ecx)\n\t"
      "jmp .LFUN_000f0f30_65\n\t"
      ".LFUN_000f0f30_61:\n\t"
      "movb 0xe3(%%esi), %%dl\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "decb %%dl\n\t"
      "negb %%dl\n\t"
      "sbbl %%edx, %%edx\n\t"
      "addl $0x18, %%edx\n\t"
      "movw %%dx, 0x40(%%eax)\n\t"
      "jmp .LFUN_000f0f30_65\n\t"
      ".LFUN_000f0f30_62:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movw $0x17, 0x40(%%ecx)\n\t"
      "jmp .LFUN_000f0f30_65\n\t"
      ".LFUN_000f0f30_63:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movw $0x19, 0x40(%%edx)\n\t"
      "jmp .LFUN_000f0f30_65\n\t"
      ".LFUN_000f0f30_64:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movw $1, 0x40(%%eax)\n\t"
      ".LFUN_000f0f30_65:\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movw $2, 0x40(%%eax)\n\t"
      "movb $0, 0x10(%%eax)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl %%ebx, 0x38(%%eax)\n\t"
      "jne .LFUN_000f0f30_69\n\t"
      "movl 0x34(%%eax), %%ecx\n\t"
      "popl %%edi\n\t"
      "movw %%bx, 0x3c(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ecx, 0x38(%%eax)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f0f30_66:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movw $5, 0x50(%%edx)\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movw $0xd, 0x50(%%ebx)\n\t"
      "movl $1, %%eax\n\t"
      "movw %%ax, 0x40(%%ecx)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movw $0xe, 0x40(%%edx)\n\t"
      "pushl $0x3a3\n\t"
      "movw %%ax, 0x40(%%ecx)\n\t"
      "pushl $0x288938\n\t"
      "movw %%ax, 0x40(%%edi)\n\t"
      "movl 0x3c(%%esi), %%edx\n\t"
      "pushl $8\n\t"
      "pushl %%edx\n\t"
      "call *%[ce3d20]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "je .LFUN_000f0f30_67\n\t"
      "movw $0, (%%eax)\n\t"
      ".LFUN_000f0f30_67:\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "movl 0x3c(%%esi), %%eax\n\t"
      "pushl $0x3a7\n\t"
      "pushl $0x288938\n\t"
      "pushl $8\n\t"
      "pushl %%eax\n\t"
      "call *%[ce3d20]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "je .LFUN_000f0f30_68\n\t"
      "movw $0, (%%eax)\n\t"
      ".LFUN_000f0f30_68:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movw $1, 0x40(%%ecx)\n\t"
      "cmpl $0x3e8, -0x28(%%ebp)\n\t"
      "sbbl %%edx, %%edx\n\t"
      "incl %%edx\n\t"
      "movw %%dx, 0x40(%%eax)\n\t"
      "movb $1, 0x10(%%eax)\n\t"
      ".LFUN_000f0f30_69:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_000f0f30_70:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000f0f30_jt0:\n\t"
      ".long .LFUN_000f0f30_29\n\t"
      ".long .LFUN_000f0f30_30\n\t"
      ".long .LFUN_000f0f30_31\n\t"
      ".long .LFUN_000f0f30_32\n\t"
      ".long .LFUN_000f0f30_33\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000f0f30_jt1:\n\t"
      ".long .LFUN_000f0f30_50\n\t"
      ".long .LFUN_000f0f30_51\n\t"
      ".long .LFUN_000f0f30_52\n\t"
      ".long .LFUN_000f0f30_53\n\t"
      ".long .LFUN_000f0f30_54\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000f0f30_jt2:\n\t"
      ".long .LFUN_000f0f30_59\n\t"
      ".long .LFUN_000f0f30_60\n\t"
      ".long .LFUN_000f0f30_61\n\t"
      ".long .LFUN_000f0f30_62\n\t"
      ".long .LFUN_000f0f30_63\n\t"
      ".text\n\t"
      :
      : [c12a240] "m"(bf0f30_c12a240), [memset] "m"(bf0f30_memset), [tag] "m"(bf0f30_tag), [c124c80] "m"(bf0f30_c124c80), [assert] "m"(bf0f30_assert), [exitfn] "m"(bf0f30_exitfn), [c125cb0] "m"(bf0f30_c125cb0), [ce3d20] "m"(bf0f30_ce3d20), [c19dc90] "m"(bf0f30_c19dc90), [c1b9930] "m"(bf0f30_c1b9930), [c19d420] "m"(bf0f30_c19d420), [c19e9f0] "m"(bf0f30_c19e9f0), [c8e370] "m"(bf0f30_c8e370), [c1d9690] "m"(bf0f30_c1d9690)
      : "memory");
}
#else
#error "FUN_000f0f30: clang naked draft required"
#endif


/* FUN_000f1710 (0xf1710) — update network pregame/status item widget texts and visibility. */
#if defined(__clang__)
static int (*const f1710_n2a0a0)(void) = FUN_0012a0a0;
static void *(*const f1710_tag)(int, int) = tag_get;
static void (*const f1710_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const f1710_exitfn)(int) = system_exit;
static void *(*const f1710_ngcli)(void) = network_game_client_get;
static unsigned short (*const f1710_n24c40)(void *) = FUN_00124c40;
static void *(*const f1710_uirealloc)(int, unsigned short, const char *, unsigned int) = ui_widget_realloc;
static short (*const f1710_n24d00)(void *) = FUN_00124d00;
static void *(*const f1710_ngsrv)(void) = network_game_server_get;
static wchar_t *(*const f1710_xucpy)(wchar_t *, wchar_t *, unsigned int) = ustrncpy;
static void (*const f1710_usprintf)(wchar_t *, int, const wchar_t *, ...) = unicode_sprintf;
static void *(*const f1710_ngmach)(void *) = network_game_client_get_machine;
static void *(*const f1710_memset)(void *, int, unsigned int) = csmemset;
static bool (*const f1710_npval)(void *) = network_player_is_valid;
static int (*const f1710_xulen)(const unsigned short *) = ustrlen;
static void (*const f1710_wvis)(void *, char) = widget_instance_set_visibility_recursive;

__attribute__((naked, noinline))
void FUN_000f1710(void *widget __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x54, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[n2a0a0]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $6, %%ecx\n\t"
      "je .LFUN_000f1710_1\n\t"
      "pushl $1\n\t"
      "pushl $0x3fc\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288f28\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f1710_1:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_000f1710_57\n\t"
      "pushl %%ebx\n\t"
      "call *%[ngcli]\n\t"
      "pushl %%eax\n\t"
      "call *%[n24c40]\n\t"
      "movl 0x34(%%esi), %%ebx\n\t"
      "pushl $0x40b\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x20\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl 0x2c(%%ebx), %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl 0x2c(%%eax), %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl 0x2c(%%eax), %%eax\n\t"
      "movl 0x2c(%%eax), %%edi\n\t"
      "movl 0x2c(%%edi), %%esi\n\t"
      "movl 0x3c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "call *%[uirealloc]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "je .LFUN_000f1710_11\n\t"
      "call *%[ngcli]\n\t"
      "pushl %%eax\n\t"
      "call *%[n24d00]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[ngsrv]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f1710_2\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "cmpw $2, 0x112(%%edx)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jl .LFUN_000f1710_3\n\t"
      ".LFUN_000f1710_2:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_000f1710_3:\n\t"
      "movl 0x3c(%%esi), %%eax\n\t"
      "pushl $0xf\n\t"
      "pushl $0x288f1c\n\t"
      "pushl %%eax\n\t"
      "call *%[xucpy]\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%bx, %%bx\n\t"
      "movb $1, 0x10(%%edi)\n\t"
      "movw $0, 0x40(%%edi)\n\t"
      "movb $1, 0x10(%%esi)\n\t"
      "jne .LFUN_000f1710_4\n\t"
      "movw $1, 0x40(%%edi)\n\t"
      "jmp .LFUN_000f1710_9\n\t"
      ".LFUN_000f1710_4:\n\t"
      "jle .LFUN_000f1710_7\n\t"
      "cmpw $0x3c, %%bx\n\t"
      "movswl %%bx, %%ecx\n\t"
      "jge .LFUN_000f1710_5\n\t"
      "movl 0x3c(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x288f0c\n\t"
      "pushl $0xf\n\t"
      "pushl %%edx\n\t"
      "call *%[usprintf]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_000f1710_10\n\t"
      ".LFUN_000f1710_5:\n\t"
      "cmpw $0xe10, %%bx\n\t"
      "jge .LFUN_000f1710_6\n\t"
      "movl $0x88888889, %%eax\n\t"
      "imull %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "sarl $5, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "imull $0x3c, %%eax, %%eax\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x3c(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x288ef8\n\t"
      "pushl $0xf\n\t"
      "pushl %%ecx\n\t"
      "call *%[usprintf]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_000f1710_10\n\t"
      ".LFUN_000f1710_6:\n\t"
      "movl $0x91a2b3c5, %%eax\n\t"
      "imull %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "sarl $0xb, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "movl %%edx, %%ebx\n\t"
      "imull $0xe10, %%edx, %%edx\n\t"
      "movl %%ecx, %%edi\n\t"
      "subl %%edx, %%edi\n\t"
      "movl $0x88888889, %%eax\n\t"
      "imull %%edi\n\t"
      "addl %%edi, %%edx\n\t"
      "sarl $5, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "movl %%ebx, %%eax\n\t"
      "imull $0x3c, %%eax, %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "imull $0x3c, %%eax, %%eax\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x3c(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x288edc\n\t"
      "pushl $0xf\n\t"
      "pushl %%ecx\n\t"
      "call *%[usprintf]\n\t"
      "addl $0x18, %%esp\n\t"
      "jmp .LFUN_000f1710_10\n\t"
      ".LFUN_000f1710_7:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f1710_8\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "cmpb $1, 0xc0(%%edx)\n\t"
      "jne .LFUN_000f1710_10\n\t"
      ".LFUN_000f1710_8:\n\t"
      "movb $0, 0x10(%%edi)\n\t"
      ".LFUN_000f1710_9:\n\t"
      "movb $0, 0x10(%%esi)\n\t"
      ".LFUN_000f1710_10:\n\t"
      "movl 0x3c(%%esi), %%eax\n\t"
      "movl -0x14(%%ebp), %%ebx\n\t"
      "movw $0, 0x1e(%%eax)\n\t"
      ".LFUN_000f1710_11:\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $6, %%ecx\n\t"
      "je .LFUN_000f1710_12\n\t"
      "pushl $1\n\t"
      "pushl $0x44c\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288f28\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f1710_12:\n\t"
      "movl 0x34(%%ebx), %%ebx\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "movl 0x2c(%%ebx), %%ebx\n\t"
      "movl 0x2c(%%ebx), %%eax\n\t"
      "movl %%eax, -0x44(%%ebp)\n\t"
      "movl 0x2c(%%eax), %%eax\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "movl 0x2c(%%eax), %%eax\n\t"
      "movl 0x2c(%%eax), %%edx\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0x154, %%eax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movl $0x288ed8, -0x14(%%ebp)\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl $4, %%edi\n\t"
      ".LFUN_000f1710_13:\n\t"
      "leal -0x40(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f1710_15\n\t"
      "movb (%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jl .LFUN_000f1710_15\n\t"
      "cmpb $4, %%al\n\t"
      "jge .LFUN_000f1710_15\n\t"
      "movsbw %%al, %%cx\n\t"
      "cmpw -0x18(%%ebp), %%cx\n\t"
      "jne .LFUN_000f1710_15\n\t"
      "call *%[ngcli]\n\t"
      "pushl %%eax\n\t"
      "call *%[ngmach]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f1710_14\n\t"
      "cmpw $0, (%%eax)\n\t"
      "je .LFUN_000f1710_14\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      ".LFUN_000f1710_14:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_000f1710_15:\n\t"
      "addl $0x44, %%esi\n\t"
      "decl %%edi\n\t"
      "jne .LFUN_000f1710_13\n\t"
      "pushl $0x10\n\t"
      "leal -0x54(%%ebp), %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "xorl %%edi, %%edi\n\t"
      "addl $0x242, %%esi\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_000f1710_16:\n\t"
      "leal -0x1c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[npval]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f1710_17\n\t"
      "movsbw (%%esi), %%cx\n\t"
      "cmpw -0x18(%%ebp), %%cx\n\t"
      "jne .LFUN_000f1710_17\n\t"
      "movsbl 0x1(%%esi), %%edx\n\t"
      "incl %%ebx\n\t"
      "cmpl $4, %%ebx\n\t"
      "movl %%edi, -0x54(%%ebp,%%edx,4)\n\t"
      "je .LFUN_000f1710_18\n\t"
      ".LFUN_000f1710_17:\n\t"
      "incl %%edi\n\t"
      "addl $0x20, %%esi\n\t"
      "cmpl $0x10, %%edi\n\t"
      "jl .LFUN_000f1710_16\n\t"
      ".LFUN_000f1710_18:\n\t"
      "movl -0x14(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[xulen]\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl 0x3c(%%edi), %%ecx\n\t"
      "pushl $0x47b\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl $0x288938\n\t"
      "leal 0x2(%%esi,%%esi,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[uirealloc]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%edi)\n\t"
      "je .LFUN_000f1710_19\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[xucpy]\n\t"
      "movl 0x3c(%%edi), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "movw $0, (%%edx,%%esi,2)\n\t"
      ".LFUN_000f1710_19:\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "setne %%al\n\t"
      "movl $0x2888f5, -0x14(%%ebp)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "movw %%ax, 0x50(%%ecx)\n\t"
      ".LFUN_000f1710_20:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x44(%%ebp,%%edx,1), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $3, %%ecx\n\t"
      "je .LFUN_000f1710_21\n\t"
      "pushl $1\n\t"
      "pushl $0x485\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288f28\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f1710_21:\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "je .LFUN_000f1710_22\n\t"
      "cmpw $0, 0xe(%%esi)\n\t"
      "je .LFUN_000f1710_23\n\t"
      ".LFUN_000f1710_22:\n\t"
      "pushl $1\n\t"
      "pushl $0x48b\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288e98\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f1710_23:\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000f1710_24\n\t"
      "cmpw $1, 0xe(%%esi)\n\t"
      "je .LFUN_000f1710_25\n\t"
      ".LFUN_000f1710_24:\n\t"
      "pushl $1\n\t"
      "pushl $0x48d\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288e68\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f1710_25:\n\t"
      "movl 0x2c(%%esi), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_000f1710_26\n\t"
      "cmpw $2, 0xe(%%ebx)\n\t"
      "je .LFUN_000f1710_27\n\t"
      ".LFUN_000f1710_26:\n\t"
      "pushl $1\n\t"
      "pushl $0x48f\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288e30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f1710_27:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb 0xc0(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f1710_28\n\t"
      "pushl $0\n\t"
      "jmp .LFUN_000f1710_29\n\t"
      ".LFUN_000f1710_28:\n\t"
      "pushl $1\n\t"
      ".LFUN_000f1710_29:\n\t"
      "pushl %%ebx\n\t"
      "call *%[wvis]\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x54(%%ebp,%%edx,1), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000f1710_31\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "pushl $0x49d\n\t"
      "pushl $0x288938\n\t"
      "movw $0, 0x50(%%eax)\n\t"
      "movl 0x3c(%%esi), %%ecx\n\t"
      "pushl $2\n\t"
      "pushl %%ecx\n\t"
      "call *%[uirealloc]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "je .LFUN_000f1710_30\n\t"
      "movw $0, (%%eax)\n\t"
      ".LFUN_000f1710_30:\n\t"
      "movw $2, 0x3c(%%ebx)\n\t"
      "jmp .LFUN_000f1710_36\n\t"
      ".LFUN_000f1710_31:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "shll $5, %%eax\n\t"
      "leal 0x226(%%eax,%%edx,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[xulen]\n\t"
      "movl 0x3c(%%esi), %%edx\n\t"
      "pushl $0x4a6\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $0x288938\n\t"
      "leal 0x2(%%edi,%%edi,1), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[uirealloc]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "je .LFUN_000f1710_32\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x54(%%ebp,%%ecx,1), %%edx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "shll $5, %%edx\n\t"
      "pushl %%edi\n\t"
      "leal 0x226(%%edx,%%ecx,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[xucpy]\n\t"
      "movl 0x3c(%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "movw $0, (%%eax,%%edi,2)\n\t"
      ".LFUN_000f1710_32:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movb 0xc0(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_000f1710_33\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movw $1, 0x50(%%ecx)\n\t"
      "jmp .LFUN_000f1710_36\n\t"
      ".LFUN_000f1710_33:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x54(%%ebp,%%edx,1), %%ecx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "shll $5, %%ecx\n\t"
      "movsbl 0x244(%%ecx,%%eax,1), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "je .LFUN_000f1710_35\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000f1710_34\n\t"
      "movzbw -0x1(%%edx), %%ax\n\t"
      "movw %%ax, 0x50(%%ecx)\n\t"
      "movw $2, 0x3c(%%ebx)\n\t"
      "jmp .LFUN_000f1710_36\n\t"
      ".LFUN_000f1710_34:\n\t"
      "movzbw (%%edx), %%ax\n\t"
      "movw %%ax, 0x50(%%ecx)\n\t"
      "movw $1, 0x3c(%%ebx)\n\t"
      "jmp .LFUN_000f1710_36\n\t"
      ".LFUN_000f1710_35:\n\t"
      "movzbw 0x1(%%edx), %%ax\n\t"
      "movw %%ax, 0x50(%%ecx)\n\t"
      "movw $0, 0x3c(%%ebx)\n\t"
      ".LFUN_000f1710_36:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "addl $3, %%eax\n\t"
      "addl $4, %%esi\n\t"
      "cmpl $0x288901, %%eax\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jl .LFUN_000f1710_20\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "pushl $0xc\n\t"
      "movl %%edx, -0x40(%%ebp)\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "call *%[memset]\n\t"
      "movl -0x28(%%ebp), %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      ".LFUN_000f1710_37:\n\t"
      "leal -0x40(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f1710_39\n\t"
      "movb (%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jl .LFUN_000f1710_39\n\t"
      "cmpb $4, %%al\n\t"
      "jge .LFUN_000f1710_39\n\t"
      "movsbw %%al, %%cx\n\t"
      "cmpw -0x18(%%ebp), %%cx\n\t"
      "je .LFUN_000f1710_39\n\t"
      "cmpl $3, %%ebx\n\t"
      "jl .LFUN_000f1710_38\n\t"
      "pushl $1\n\t"
      "pushl $0x4d4\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288e0c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f1710_38:\n\t"
      "movl %%esi, -0x34(%%ebp,%%ebx,4)\n\t"
      "incl %%ebx\n\t"
      ".LFUN_000f1710_39:\n\t"
      "incl %%esi\n\t"
      "addl $0x44, %%edi\n\t"
      "cmpl $4, %%esi\n\t"
      "jl .LFUN_000f1710_37\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "jmp .LFUN_000f1710_41\n\t"
      ".LFUN_000f1710_40:\n\t"
      "movl -0x14(%%ebp), %%ebx\n\t"
      ".LFUN_000f1710_41:\n\t"
      "movl -0x40(%%ebp,%%ebx,1), %%esi\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x44654c61\n\t"
      "call *%[tag]\n\t"
      "movl 0x3e0(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $6, %%ecx\n\t"
      "je .LFUN_000f1710_42\n\t"
      "pushl $1\n\t"
      "pushl $0x4dd\n\t"
      "pushl $0x288938\n\t"
      "pushl $0x288f28\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f1710_42:\n\t"
      "cmpl $-1, -0x34(%%ebp,%%ebx,1)\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "movl 0x2c(%%eax), %%esi\n\t"
      "jne .LFUN_000f1710_45\n\t"
      "pushl $0x4e7\n\t"
      "pushl $0x288938\n\t"
      "movw $0, 0x50(%%eax)\n\t"
      "movl 0x3c(%%esi), %%eax\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "call *%[uirealloc]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "je .LFUN_000f1710_43\n\t"
      "movw $0, (%%eax)\n\t"
      ".LFUN_000f1710_43:\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_000f1710_44:\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000f1710_56\n\t"
      "incl %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "movw $2, 0x50(%%esi)\n\t"
      "movl 0x2c(%%esi), %%esi\n\t"
      "jl .LFUN_000f1710_44\n\t"
      "jmp .LFUN_000f1710_56\n\t"
      ".LFUN_000f1710_45:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movw $1, 0x50(%%eax)\n\t"
      "movl -0x34(%%ebp,%%ebx,1), %%ecx\n\t"
      "imull $0x44, %%ecx, %%ecx\n\t"
      "leal 0x114(%%ecx,%%edx,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[xulen]\n\t"
      "movl 0x3c(%%esi), %%edx\n\t"
      "pushl $0x4f4\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $0x288938\n\t"
      "leal 0x2(%%edi,%%edi,1), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[uirealloc]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "je .LFUN_000f1710_46\n\t"
      "movl -0x34(%%ebp,%%ebx,1), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "imull $0x44, %%ecx, %%ecx\n\t"
      "pushl %%edi\n\t"
      "leal 0x114(%%ecx,%%edx,1), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[xucpy]\n\t"
      "movl 0x3c(%%esi), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "movw $0, (%%edx,%%edi,2)\n\t"
      ".LFUN_000f1710_46:\n\t"
      "pushl $0x10\n\t"
      "leal -0x54(%%ebp), %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "addl $0x242, %%edi\n\t"
      ".LFUN_000f1710_47:\n\t"
      "leal -0x1c(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[npval]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f1710_48\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl -0x34(%%ebp,%%edx,1), %%eax\n\t"
      "movb (%%edi), %%cl\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "addl $5, %%eax\n\t"
      "imull $0x44, %%eax, %%eax\n\t"
      "cmpb (%%eax,%%edx,1), %%cl\n\t"
      "jne .LFUN_000f1710_48\n\t"
      "movsbl 0x1(%%edi), %%eax\n\t"
      "movl %%ebx, -0x54(%%ebp,%%eax,4)\n\t"
      ".LFUN_000f1710_48:\n\t"
      "incl %%ebx\n\t"
      "addl $0x20, %%edi\n\t"
      "cmpl $0x10, %%ebx\n\t"
      "jl .LFUN_000f1710_47\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "movl $0x2888f4, %%edx\n\t"
      "leal -0x54(%%ebp), %%edi\n\t"
      ".LFUN_000f1710_49:\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f1710_56\n\t"
      "movl (%%edi), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "jne .LFUN_000f1710_50\n\t"
      "movw $2, 0x50(%%eax)\n\t"
      "jmp .LFUN_000f1710_55\n\t"
      ".LFUN_000f1710_50:\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movb 0xc0(%%esi), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_000f1710_51\n\t"
      "movzbw (%%edx), %%cx\n\t"
      "jmp .LFUN_000f1710_54\n\t"
      ".LFUN_000f1710_51:\n\t"
      "shll $5, %%ecx\n\t"
      "movsbl 0x244(%%ecx,%%esi,1), %%ecx\n\t"
      "subl $0, %%ecx\n\t"
      "je .LFUN_000f1710_53\n\t"
      "decl %%ecx\n\t"
      "je .LFUN_000f1710_52\n\t"
      "movzbw (%%edx), %%cx\n\t"
      "jmp .LFUN_000f1710_54\n\t"
      ".LFUN_000f1710_52:\n\t"
      "movzbw 0x1(%%edx), %%cx\n\t"
      "jmp .LFUN_000f1710_54\n\t"
      ".LFUN_000f1710_53:\n\t"
      "movzbw 0x2(%%edx), %%cx\n\t"
      ".LFUN_000f1710_54:\n\t"
      "movw %%cx, 0x50(%%eax)\n\t"
      ".LFUN_000f1710_55:\n\t"
      "movl 0x2c(%%eax), %%eax\n\t"
      "addl $3, %%edx\n\t"
      "addl $4, %%edi\n\t"
      "cmpl $0x288900, %%edx\n\t"
      "jl .LFUN_000f1710_49\n\t"
      ".LFUN_000f1710_56:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "cmpl $0xc, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jl .LFUN_000f1710_40\n\t"
      "popl %%ebx\n\t"
      ".LFUN_000f1710_57:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [n2a0a0] "m"(f1710_n2a0a0), [tag] "m"(f1710_tag), [assert] "m"(f1710_assert), [exitfn] "m"(f1710_exitfn), [ngcli] "m"(f1710_ngcli), [n24c40] "m"(f1710_n24c40), [uirealloc] "m"(f1710_uirealloc), [n24d00] "m"(f1710_n24d00), [ngsrv] "m"(f1710_ngsrv), [xucpy] "m"(f1710_xucpy), [usprintf] "m"(f1710_usprintf), [ngmach] "m"(f1710_ngmach), [memset] "m"(f1710_memset), [npval] "m"(f1710_npval), [xulen] "m"(f1710_xulen), [wvis] "m"(f1710_wvis)
      : "memory");
}
#else
#error "FUN_000f1710: clang naked draft required"
#endif

/* 0xf1ed0 */
void network_pregame_status_screen_update(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_0012a0a0();
  tag_get('aLeD', 0);
  /* cmp ecx, 3 -> je 0xf1f20 */
  display_assert((char *)0x00288f28, (char *)0x00288938, 1360, 0);
  system_exit(0);
  /* test edi, edi -> je 0xf2382 */
  network_game_client_get();
  FUN_00124c40((void *)(uintptr_t)eax);
  ui_widget_realloc(0, 32, (char *)0x00288938, 1372);
  network_game_client_get();
  FUN_00124d00((void *)(uintptr_t)eax);
  ustrncpy((wchar_t *)(uintptr_t)edx, (wchar_t *)0x00288f1c, 15);
  /* cmp (int16_t)ebx, 0x3c -> jge 0xf1fcc */
  unicode_sprintf((wchar_t *)(uintptr_t)ecx, 15, (wchar_t *)0x00288f0c);
  unicode_sprintf((wchar_t *)(uintptr_t)ecx, 15, (wchar_t *)0x00288ef8);
  unicode_sprintf((wchar_t *)(uintptr_t)ecx, 15, (wchar_t *)0x00288edc);
  /* relift: cmp word ptr [eax + 0x224], 2 -> jl 0xf2073 */
  /* relift: cmp byte ptr [eax + 0xc0], 1 -> jne 0xf207b */
  tag_get('aLeD', 0);
  /* cmp ecx, 6 -> je 0xf20c2 */
  display_assert((char *)0x00288f28, (char *)0x00288938, 1426, 0);
  system_exit(0);
  /* test ecx, ecx -> je 0xf211c */
  /* test (char)ecx, (char)ecx -> jl 0xf211c */
  /* cmp (char)ecx, 4 -> jge 0xf211c */
  /* relift: cmp (int16_t)ecx, word ptr [ebp - 0x14] -> je 0xf2127 */
  /* cmp edx, 4 -> jl 0xf2100 */
  network_game_client_get();
  network_game_client_get_machine((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0xf2142 */
  /* relift: cmp word ptr [eax], 0 -> je 0xf2142 */
  csmemset((void *)(uintptr_t)edx, 0, 16);
  network_player_is_valid((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0xf2188 */
  /* relift: cmp (int16_t)ecx, word ptr [ebp - 0x14] -> jne 0xf2188 */
  /* cmp ebx, 0x10 -> jl 0xf2160 */
  ustrlen((void *)(uintptr_t)ebx);
  ui_widget_realloc(0, 0, (char *)0x00288938, 1474);
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)ebx, esi);
  tag_get('aLeD', 0);
  /* cmp ecx, 3 -> je 0xf2236 */
  display_assert((char *)0x00288f28, (char *)0x00288938, 1484, 0);
  system_exit(0);
  widget_instance_set_visibility_recursive((void *)(uintptr_t)eax, 0);
  /* cmp eax, -1 -> jne 0xf229a */
  ui_widget_realloc(0, 0, (char *)0x00288938, 1499);
  ustrlen((void *)(uintptr_t)ecx);
  ui_widget_realloc(0, 0, (char *)0x00288938, 1508);
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)edx, edi);
  /* test (char)ecx, (char)ecx -> jne 0xf230b */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0xf2390 */
void FUN_000f2390(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  network_game_client_get();
  /* test edi, edi -> je 0xf24a5 */
  network_game_client_get_state((void *)(uintptr_t)edi, (void *)(uintptr_t)eax);
  /* cmp (int16_t)eax, 2 -> jne 0xf24a5 */
  FUN_0012a0a0();
  /* test esi, esi -> jne 0xf23e9 */
  display_assert((char *)0x002861a8, (char *)0x00288938, 1556, 0);
  system_exit(0);
  player_ui_local_player_wants_to_play_multiplayer();
  network_player_is_valid((void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0xf245f */
  network_game_player_is_local((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0xf245f */
  /* test dl, dl -> je 0xf249b */
  network_game_client_add_player((void *)(uintptr_t)edi, eax);
  /* test (char)eax, (char)eax -> jne 0xf2498 */
  network_game_log((char *)0x0028618c);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0xf24b0 */
void mutliplayer_settings_select_list_update_displayed_items(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> je 0xf24ca */
  /* test eax, eax -> je 0xf24ca */
  /* test eax, eax -> jne 0xf24ea */
  display_assert((char *)0x00288a5c, (char *)0x00288938, 2102, 0);
  system_exit(0);
  /* test eax, eax -> je 0xf2508 */
  /* cmp eax, ecx -> je 0xf2502 */
  /* test eax, eax -> jne 0xf24f6 */
  /* cmp (int16_t)esi, -1 -> je 0xf2557 */
  tag_get('aLeD', 0);
  /* cmp ecx, 2 -> je 0xf2546 */
  display_assert((char *)0x00288f68, (char *)0x00288938, 2116, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0xf2560 */
void FUN_000f2560(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x002890bc, (char *)0x00288938, 2293, 0);
  system_exit(0);
  /* test eax, eax -> je 0xf259f */
  /* relift: cmp word ptr [eax + 0xe], 1 -> je 0xf25bf */
  display_assert((char *)0x00289070, (char *)0x00288938, 2296, 0);
  system_exit(0);
  tag_get('aLeD', 0);
  /* test ecx, ecx -> jg 0xf25f9 */
  display_assert((char *)0x00289034, (char *)0x00288938, 2302, 0);
  system_exit(0);
  /* test edi, edi -> je 0xf266e */
  /* test esi, esi -> je 0xf2625 */
  /* relift: cmp word ptr [esi + 0xe], 2 -> je 0xf2648 */
  /* test esi, esi -> jne 0xf2617 */
  display_assert((char *)0x00288fd8, (char *)0x00288938, 2316, 0);
  system_exit(0);
  /* relift: cmp edi, dword ptr [ecx + 0x38] -> je 0xf2668 */
  /* test edi, edi -> jne 0xf2610 */

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0xf2690 */
void FUN_000f2690(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  hud_messaging_get_objective();
  /* test ebx, ebx -> je 0xf26b4 */
  /* relift: cmp word ptr [ebx], 0 -> je 0xf26b4 */
  ustrlen((void *)(uintptr_t)ebx);
  /* relift: cmp word ptr [edi + 0xe], 1 -> je 0xf26e0 */
  display_assert((char *)0x002890f4, (char *)0x00288938, 2340, 0);
  system_exit(0);
  /* test esi, esi -> jle 0xf271a */
  ui_widget_realloc(0, 0, (char *)0x00288938, 2344);
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)ebx, esi);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0xf2720 */
void FUN_000f2720(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x0028919c, (char *)0x00288938, 2432, 0);
  system_exit(0);
  /* test eax, eax -> je 0xf275f */
  /* relift: cmp word ptr [eax + 0xe], 0 -> je 0xf277f */
  display_assert((char *)0x00289150, (char *)0x00288938, 2435, 0);
  system_exit(0);
  tag_get('aLeD', 0);
  /* test ecx, ecx -> jg 0xf27b9 */
  display_assert((char *)0x0028911c, (char *)0x00288938, 2440, 0);
  system_exit(0);
  /* test edi, edi -> je 0xf282e */
  /* test esi, esi -> je 0xf27e5 */
  /* relift: cmp word ptr [esi + 0xe], 2 -> je 0xf2808 */
  /* test esi, esi -> jne 0xf27d7 */
  display_assert((char *)0x00288fd8, (char *)0x00288938, 2454, 0);
  system_exit(0);
  /* relift: cmp edi, dword ptr [ecx + 0x38] -> je 0xf2828 */
  /* test edi, edi -> jne 0xf27d0 */

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0xf2850 */
void FUN_000f2850(void *widget)
{
  int eax = 0;
  int esi = 0;

  /* relift: cmp word ptr [esi + 0xe], 3 -> je 0xf287e */
  display_assert((char *)0x00289218, (char *)0x00288938, 2475, 0);
  system_exit(0);
  /* test eax, eax -> je 0xf288c */
  /* relift: cmp word ptr [eax + 0xe], 0 -> je 0xf28ac */
  display_assert((char *)0x002891c8, (char *)0x00288938, 2478, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jge 0xf28cc */

  (void)eax;
  (void)esi;
}

/* 0xf28e0 */
void FUN_000f28e0(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* relift: cmp word ptr [esi + 0xe], 1 -> je 0xf2911 */
  display_assert((char *)0x00289284, (char *)0x00288938, 2540, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xf2920 */
  /* cmp (int16_t)eax, 4 -> jl 0xf2940 */
  display_assert((char *)0x00289248, (char *)0x00288938, 2542, 0);
  system_exit(0);
  player_ui_get_active_player_profile();
  ui_widget_realloc(0, 24, (char *)0x00288938, 2544);
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)ecx, 11);

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0xf2990 */
void FUN_000f2990(void *widget)
{
  int eax = 0;
  int edi = 0;

  display_assert((char *)0x00289284, (char *)0x00288938, 2558, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xf29ce */
  /* cmp (int16_t)eax, 4 -> jl 0xf29ee */
  display_assert((char *)0x00289248, (char *)0x00288938, 2560, 0);
  system_exit(0);
  player_ui_get_edit_player_profile();
  /* test edi, edi -> je 0xf2a2d */
  ui_widget_realloc(0, 24, (char *)0x00288938, 2564);
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)edi, 11);

  (void)eax;
  (void)edi;
}

/* 0xf2a40 */
void FUN_000f2a40(void *widget)
{
  int eax = 0;
  int edi = 0;

  display_assert((char *)0x00289284, (char *)0x00288938, 2579, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0xf2a7e */
  /* cmp (int16_t)eax, 4 -> jl 0xf2a9e */
  display_assert((char *)0x00289248, (char *)0x00288938, 2581, 0);
  system_exit(0);
  player_ui_get_edit_playlist_profile();
  /* test edi, edi -> je 0xf2ae1 */
  ui_widget_realloc(0, 24, (char *)0x00288938, 2585);
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)edi, 11);
  error(0, (char *)0x002892b8);

  (void)eax;
  (void)edi;
}

/* 0xf2b00 */
void FUN_000f2b00(void *widget)
{
  int edx = 0;
  int edi = 0;

  /* test (int16_t)eax, (int16_t)eax -> jl 0xf2b19 */
  /* cmp (int16_t)eax, 4 -> jl 0xf2b39 */
  display_assert((char *)0x002892e0, (char *)0x00288938, 2605, 0);
  system_exit(0);
  player_ui_get_active_player_profile();
  /* test (int16_t)eax, (int16_t)eax -> jge 0xf2b60 */
  FUN_001c0ed0();
  /* cmp edi, edx -> jle 0xf2b84 */
  FUN_001c0ed0();

  (void)edx;
  (void)edi;
}

/* 0xf2b90 */
void FUN_000f2b90(void *widget)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp word ptr [edi + 0xe], 1 -> je 0xf2bbf */
  display_assert((char *)0x0028932c, (char *)0x00288938, 2617, 0);
  system_exit(0);
  FUN_0012a0a0();
  /* test eax, eax -> je 0xf2d3c */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288c70);
  /* test eax, eax -> je 0xf2beb */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288c64);
  /* test eax, eax -> je 0xf2c07 */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288c58);
  /* test eax, eax -> je 0xf2c23 */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288c50);
  /* test eax, eax -> je 0xf2c3f */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288c44);
  /* test eax, eax -> je 0xf2c5b */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288c38);
  /* test eax, eax -> je 0xf2c77 */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288c2c);
  /* test eax, eax -> je 0xf2c93 */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288c20);
  /* test eax, eax -> je 0xf2caf */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288c10);
  /* test eax, eax -> je 0xf2ccb */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288c04);
  /* test eax, eax -> je 0xf2ce7 */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288bfc);
  /* test eax, eax -> je 0xf2d03 */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288bf4);
  /* test eax, eax -> je 0xf2d1f */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288bec);
  error(0, (char *)0x0028931c);

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0xf2d50 */
void FUN_000f2d50(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* relift: cmp word ptr [esi + 0xe], 1 -> je 0xf2d7e */
  display_assert((char *)0x0028932c, (char *)0x00288938, 2649, 0);
  system_exit(0);
  FUN_0012a0a0();
  /* test eax, eax -> je 0xf2e35 */
  /* cmp ecx, 4 -> ja 0xf2e2c */
  /* relift: cmp byte ptr [eax + 0xf0], 1 -> jne 0xf2dbf */
  error(0, (char *)0x0028931c);

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0xf2e60 */
void FUN_000f2e60(void *widget)
{
  int eax = 0;
  int esi = 0;

  /* relift: cmp word ptr [esi + 0xe], 1 -> je 0xf2e8e */
  display_assert((char *)0x0028932c, (char *)0x00288938, 2730, 0);
  system_exit(0);
  FUN_0012a0a0();
  /* test eax, eax -> je 0xf2eaf */
  error(0, (char *)0x0028931c);

  (void)eax;
  (void)esi;
}

/* 0xf2ed0 */
void FUN_000f2ed0(void *widget)
{
  int eax = 0;
  int edi = 0;

  display_assert((char *)0x0028932c, (char *)0x00288938, 2755, 0);
  system_exit(0);
  FUN_0012a0a0();
  /* test edi, edi -> je 0xf2f4d */
  ui_widget_realloc(0, 16, (char *)0x00288938, 2760);
  unicode_sprintf((wchar_t *)(uintptr_t)eax, 0, (wchar_t *)0x0026c118);
  error(0, (char *)0x0028931c);

  (void)eax;
  (void)edi;
}

/* 0xf2f60 */
void FUN_000f2f60(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* relift: cmp word ptr [esi + 0xe], 1 -> je 0xf2f8e */
  display_assert((char *)0x0028932c, (char *)0x00288938, 2780, 0);
  system_exit(0);
  FUN_0012a0a0();
  /* test eax, eax -> je 0xf2fe6 */
  /* cmp ecx, 4 -> ja 0xf2fb3 */
  error(0, (char *)0x0028931c);

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0xf3010 */
void solo_game_objective_text(void *widget)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp word ptr [edi + 0xe], 0 -> je 0xf303f */
  display_assert((char *)0x00289360, (char *)0x00288938, 2825, 0);
  system_exit(0);
  FUN_0012a0a0();
  /* test eax, eax -> je 0xf31bc */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288c70);
  /* test eax, eax -> je 0xf306b */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288c64);
  /* test eax, eax -> je 0xf3087 */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288c58);
  /* test eax, eax -> je 0xf30a3 */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288c50);
  /* test eax, eax -> je 0xf30bf */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288c44);
  /* test eax, eax -> je 0xf30db */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288c38);
  /* test eax, eax -> je 0xf30f7 */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288c2c);
  /* test eax, eax -> je 0xf3113 */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288c20);
  /* test eax, eax -> je 0xf312f */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288c10);
  /* test eax, eax -> je 0xf314b */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288c04);
  /* test eax, eax -> je 0xf3167 */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288bfc);
  /* test eax, eax -> je 0xf3183 */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288bf4);
  /* test eax, eax -> je 0xf319f */
  crt_strstr((char *)(uintptr_t)esi, (char *)0x00288bec);
  error(0, (char *)0x0028931c);

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0xf31d0 */
void color_picker_get_string(void *widget)
{
  int eax = 0;
  int esi = 0;

  /* relift: cmp word ptr [esi + 0xe], 0 -> je 0xf31fe */
  display_assert((char *)0x00289360, (char *)0x00288938, 2856, 0);
  system_exit(0);
  FUN_0012a0a0();
  /* test eax, eax -> je 0xf3250 */
  /* cmp eax, 4 -> ja 0xf3247 */
  error(0, (char *)0x0028931c);

  (void)eax;
  (void)esi;
}

/* 0xf3280 */
void FUN_000f3280(void *widget)
{
  int eax = 0;
  int edi = 0;

  display_assert((char *)0x0028932c, (char *)0x00288938, 2894, 0);
  system_exit(0);
  FUN_0012a0a0();
  /* test edi, edi -> je 0xf32fe */
  ui_widget_realloc(0, 0, (char *)0x00288938, 2902);
  unicode_sprintf((wchar_t *)(uintptr_t)eax, 0, (wchar_t *)0x0026c118);
  error(0, (char *)0x0028931c);

  (void)eax;
  (void)edi;
}

/* 0xf3320 */
void FUN_000f3320(void *widget)
{
  int eax = 0;
  int esi = 0;

  /* relift: cmp word ptr [esi + 0xe], 1 -> je 0xf334e */
  display_assert((char *)0x00289398, (char *)0x00288938, 2921, 0);
  system_exit(0);
  player_ui_get_edit_playlist_profile();
  /* test eax, eax -> je 0xf339d */
  /* cmp eax, 4 -> ja 0xf3394 */
  error(0, (char *)0x002892b8);

  (void)eax;
  (void)esi;
}

/* 0xf3400 */
void game_options_menu_update_pic_desc(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  FUN_0012a0a0();
  network_game_server_get();
  display_assert((char *)0x002893fc, (char *)0x00288938, 2989, 0);
  system_exit(0);
  /* test edi, edi -> je 0xf349a */
  network_game_is_splitscreen_local();
  /* test esi, esi -> je 0xf345e */
  /* relift: cmp word ptr [esi + 0x112], (int16_t)edi -> jl 0xf3489 */
  network_game_is_splitscreen_local();
  /* test (char)eax, (char)eax -> je 0xf349a */
  /* test esi, esi -> je 0xf3530 */
  /* relift: cmp word ptr [esi + 0x224], (int16_t)edi -> jge 0xf349a */
  /* test esi, esi -> je 0xf3530 */
  /* relift: cmp byte ptr [esi + 0xc0], 1 -> jne 0xf3530 */
  network_game_client_get();
  FUN_00124d00((void *)(uintptr_t)eax);
  /* test (int16_t)eax, (int16_t)eax -> jge 0xf3530 */
  network_player_is_valid((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0xf34f3 */
  /* test ebx, ebx -> je 0xf351a */
  /* test eax, eax -> je 0xf351a */

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0xf3540 */
void mp_level_select_list_update_displayed_items(void *widget)
{
  int esi = 0;

  FUN_0012a0a0();
  display_assert((char *)0x00289430, (char *)0x00288938, 3068, 0);
  system_exit(0);
  /* test esi, esi -> je 0xf358c */

  (void)esi;
}

/* 0xf3590 */
void get_editable_player_profile_display_name(void *widget)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp word ptr [esi + 0xe], 3 -> je 0xf35c6 */
  display_assert((char *)0x002894c0, (char *)0x00288938, 3103, 0);
  system_exit(0);
  /* test edi, edi -> je 0xf35d4 */
  /* relift: cmp word ptr [edi + 0xe], 1 -> je 0xf35f4 */
  display_assert((char *)0x00289470, (char *)0x00288938, 3107, 0);
  system_exit(0);
  /* relift: cmp byte ptr [0x46ce3b], 1 -> jne 0xf3629 */
  main_get_map_name();
  crt_stricmp((char *)0x0046cd38, (char *)(uintptr_t)eax);
  /* test eax, eax -> jne 0xf3629 */

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0xf3640 */
void get_editable_playlist_profile_display_name(void *widget)
{
  int eax = 0;
  int esi = 0;

  /* relift: cmp word ptr [esi + 0xe], 1 -> je 0xf366e */
  display_assert((char *)0x002894f4, (char *)0x00288938, 3132, 0);
  system_exit(0);
  transport_network_available();
  /* test (char)eax, (char)eax -> je 0xf3681 */

  (void)eax;
  (void)esi;
}

/* 0xf3690 — collect up to 3 child widget text handles for item UI sync. */
/* 0xf3690 — resolve three neighboring list indices for a widget spinner. */
void FUN_000f3690(int *out_handles /* @<eax> */, void *widget /* @<ecx> */)
{
  char *w = (char *)widget;
  char *related;
  int count;
  int a;
  int b;
  int c;

  related = *(char **)(w + 0x34);
  if (*(int *)(w + 0x38) == (int)related) {
    a = (int)*(int16_t *)(w + 0x3c);
    b = a + 1;
    count = (int)*(uint16_t *)(w + 0x44);
    if (b == count)
      b = 0;
    c = b + 1;
    if (c == count)
      c = 0;
  } else if (*(int *)(w + 0x38) == *(int *)(related + 0x2c)) {
    b = (int)*(int16_t *)(w + 0x3c);
    a = b - 1;
    if (a < 0)
      a = (int)*(uint16_t *)(w + 0x44) - 1;
    c = b + 1;
    count = (int)*(uint16_t *)(w + 0x44);
    if (c == count)
      c = 0;
  } else {
    c = (int)*(int16_t *)(w + 0x3c);
    b = c - 1;
    if (b < 0)
      b = (int)*(uint16_t *)(w + 0x44) - 1;
    a = b - 1;
    if (a < 0)
      a = (int)*(uint16_t *)(w + 0x44) - 1;
  }

  count = (int)*(uint16_t *)(w + 0x44);
  out_handles[0] = (a < count) ? a : -1;
  out_handles[1] = (b < count) ? b : -1;
  out_handles[2] = (c < count) ? c : -1;
}

/* 0xf3740 */
void multiplayer_game_set_text_box_for_game_ruleset(int *handles, int count)
{
  (void)handles;
  (void)count;
}

/* 0xf3850 */
void multiplayer_game_set_text_box_for_teams_noteams(void *widget)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp ecx, -1 -> je 0xf388a */
  /* test edi, edi -> jle 0xf388a */
  /* relift: cmp ecx, dword ptr [ebx + eax*4] -> je 0xf3885 */
  /* cmp eax, edi -> jl 0xf3876 */
  /* cmp edx, 0x5aa3a4 -> jl 0xf3866 */
  /* test eax, eax -> jle 0xf3955 */
  /* cmp edx, -1 -> je 0xf3949 */
  /* relift: cmp edx, dword ptr [eax] -> je 0xf38cf */
  /* cmp eax, 0x5aa3a4 -> jl 0xf38c0 */
  /* cmp ecx, 3 -> jne 0xf3949 */
  /* relift: cmp byte ptr [ebp + esi - 4], 1 -> jne 0xf3908 */
  /* cmp esi, 3 -> jl 0xf3902 */
  display_assert((char *)0x00289550, (char *)0x00288938, 3285, 0);
  system_exit(0);
  /* cmp esi, 3 -> jl 0xf38d6 */
  playlist_profile_delete();
  /* test (char)eax, (char)eax -> je 0xf393a */
  error(0, (char *)0x0028956c);
  /* cmp ebx, eax -> jl 0xf38a3 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0xf3960 */
void FUN_000f3960(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp eax, ecx -> je 0xf3986 */
  /* cmp eax, -1 -> jne 0xf3986 */
  qsort((void *)(uintptr_t)edi, esi, 0, (void *)0x000f3960);
  /* test esi, esi -> jle 0xf39b2 */
  /* relift: cmp dword ptr [edi + eax*4], -1 -> je 0xf39b2 */
  /* cmp eax, esi -> jl 0xf39a7 */

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0xf39c0 */
void FUN_000f39c0(void *widget)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  player_ui_get_active_player_profile();
  player_profile_save_last_level_played(0, 0, 0);
  tag_get('aLeD', 0);
  /* relift: cmp word ptr [esi], 2 -> je 0xf3a20 */
  display_assert((char *)0x0028974c, (char *)0x00288938, 480, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0x3e0], 3 -> je 0xf3a49 */
  display_assert((char *)0x00289710, (char *)0x00288938, 481, 0);
  system_exit(0);
  FUN_000f3690(0, 0);
  /* relift: cmp dword ptr [ebp + eax*4 - 0x24], -1 -> je 0xf3c6e */
  widget_instance_get_nth_child((void *)(uintptr_t)edi, 0);
  tag_get('aLeD', 0);
  /* test ecx, ecx -> jne 0xf3ac7 */
  display_assert((char *)0x002896d0, (char *)0x00288938, 502, 0);
  system_exit(0);
  tag_get('aLeD', 0);
  /* relift: cmp word ptr [eax], 1 -> je 0xf3afd */
  display_assert((char *)0x00289688, (char *)0x00288938, 504, 0);
  system_exit(0);
  tag_get('aLeD', 0);
  /* relift: cmp word ptr [eax], 0 -> je 0xf3b33 */
  display_assert((char *)0x00289640, (char *)0x00288938, 506, 0);
  system_exit(0);
  tag_get('aLeD', 0);
  /* relift: cmp word ptr [eax], 1 -> je 0xf3b69 */
  display_assert((char *)0x002895f0, (char *)0x00288938, 508, 0);
  system_exit(0);
  /* test eax, eax -> jl 0xf3b94 */
  /* cmp eax, 0xa -> jl 0xf3bb7 */
  display_assert((char *)0x00289590, (char *)0x00288938, 516, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0xf3c0f */
  /* test (char)eax, (char)eax -> jne 0xf3c0f */
  /* test (char)eax, (char)eax -> jne 0xf3c0f */
  /* test (char)eax, (char)eax -> jne 0xf3c0f */
  /* cmp (char)eax, 1 -> jne 0xf3c3a */
  /* cmp ecx, eax -> jne 0xf3c3a */
  tag_loaded(0x75737472, (char *)0x002898a4);
  tag_get('aLeD', 0);
  /* relift: cmp word ptr [esi], 2 -> je 0xf3cd6 */
  display_assert((char *)0x00289860, (char *)0x00288938, 1661, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0x3e0], 3 -> je 0xf3cff */
  display_assert((char *)0x00289810, (char *)0x00288938, 1662, 0);
  system_exit(0);
  FUN_000f3690(0, 0);
  /* cmp ecx, edx -> je 0xf3d24 */
  /* cmp eax, 0xc -> jl 0xf3d10 */
  multiplayer_game_set_text_box_for_teams_noteams((void *)(uintptr_t)edx);
  /* relift: cmp dword ptr [ebp + eax*4 - 0x1c], -1 -> je 0xf41d8 */
  widget_instance_get_nth_child((void *)(uintptr_t)edi, 0);
  tag_get('aLeD', 0);
  /* test ecx, ecx -> jne 0xf3db2 */
  display_assert((char *)0x002897c8, (char *)0x00288938, 1694, 0);
  system_exit(0);
  tag_get('aLeD', 0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
