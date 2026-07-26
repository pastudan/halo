/* Saved game file management — create directories and manage file handles. */

/* Helper: call ensure_directory at 0x1c31f0 which takes EAX as the path. */
static char ensure_dir(const char *path)
{
  int _eax = (int)path;
  asm volatile("movl $0x1c31f0, %%edx\n\t"
               "call *%%edx"
               : "+a"(_eax)
               :
               : "ecx", "edx", "memory", "cc");
  return (char)_eax;
}

/* Dispose saved game file handles and clean up. */
void saved_game_files_dispose(void)
{
  if (*(int *)0x4eacbc != 0) {
    ((void (*)(int))0x81910)(*(int *)0x4eacbc);
    *(int *)0x4eacbc = 0;
  }
  if (*(int *)0x4eacc0 != 0) {
    ((void (*)(int))0x81910)(*(int *)0x4eacc0);
    *(int *)0x4eacc0 = 0;
  }
  ((void (*)(void))0x1c0cf0)();
  ((void (*)(void))0x1c1dc0)();
  *(uint8_t *)0x4eacc6 = 0;
}

/* Initialize saved game files: create directory structure on the
 * Xbox hard drive, allocate file handles, and load profile data. */
void saved_game_files_initialize(void)
{
  if (!ensure_dir((const char *)0x2bae58))
    error(2, "failed to find/create '%s' directory", "z:\\saved");
  if (!ensure_dir((const char *)0x2bae14))
    error(2, "failed to find/create '%s' directory",
          "z:\\saved\\player_profiles");
  if (!ensure_dir((const char *)0x2bade8))
    error(2, "failed to find/create '%s' directory",
          "z:\\saved\\player_profiles\\default_profile");
  if (!ensure_dir((const char *)0x2badd4))
    error(2, "failed to find/create '%s' directory", "z:\\saved\\playlists");
  if (!ensure_dir((const char *)0x2badb0))
    error(2, "failed to find/create '%s' directory",
          "z:\\saved\\playlists\\default_playlist");
  if (!ensure_dir((const char *)0x2bad9c))
    error(2, "failed to find/create '%s' directory", "z:\\saved\\recordings");
  if (!ensure_dir((const char *)0x2bad78))
    error(2, "failed to find/create '%s' directory",
          "z:\\saved\\recordings\\last_recording");

  csmemset((void *)0x4eabb0, 0, 0x11c);
  *(uint8_t *)0x4eacc7 = 1;
  *(int *)0x4eacbc = 0;
  *(int *)0x4eacc0 = 0;

  if (((char (*)(void *))0x817e0)((void *)0x4eacbc)) {
    if (((char (*)(void *))0x817e0)((void *)0x4eacc0)) {
      *(uint8_t *)0x4eacc6 = 1;
      ((void (*)(void))0x1c1ba0)();
      ((void (*)(void))0x1c1da0)();
      return;
    }
  }

  *(uint8_t *)0x4eacc6 = 0;
  display_assert("failed to initialize saved game files",
                 "c:\\halo\\SOURCE\\saved games\\saved_game_files.c", 0xbf, 1);
  system_exit(-1);
  ((void (*)(void))0x1c1ba0)();
  ((void (*)(void))0x1c1da0)();
}
/* --- saved_game_files.obj batch drafts (2026-07-26) --- */

/* 0x1c1b00 */
void FUN_001c1b00(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x1c1b27 */
  display_assert((char *)0x002829b0, (char *)0x002b9f70, 704, 0);
  system_exit(0);
  /* test eax, eax -> je 0x1c1b6b */
  error(0, (char *)0x002ba0f8);
  thread_is_done((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c1b40 */
  thread_close((void *)(uintptr_t)ecx);
  /* mem[0x004eaa2c] = 0 */
  /* mem[0x004ea9f8] = edx */
  csmemcpy((void *)0x004ea9fc, (void *)(uintptr_t)esi, 48);
  thread_new(0, (void *)0x001c15c0, 0x004ea9f8, (void *)0x004eaa2c);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1c1ba0 */
void FUN_001c1ba0(void)
{
  csmemset((void *)0x004ea9c8, 0, 108);
}

/* 0x1c1bc0 */
void player_profile_get_from_path(void)
{
  int eax = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x1c1beb */
  display_assert((char *)0x002829b0, (char *)0x002b9f70, 256, 0);
  system_exit(0);
  /* cmp eax, -1 -> je 0x1c1bfc */
  FUN_001c1b00();

  (void)eax;
  (void)esi;
}

/* 0x1c1c00 */
void FUN_001c1c00(void)
{
  int ebx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  main_get_current_solo_level();
  /* cmp (int16_t)ebx, 4 -> jl 0x1c1c3d */
  display_assert((char *)0x00282750, (char *)0x002b9f70, 378, 0);
  system_exit(0);
  /* cmp (int16_t)esi, -1 -> je 0x1c1cb2 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1c1c4e */
  /* cmp (int16_t)esi, 0xa -> jl 0x1c1c6e */
  display_assert((char *)0x002ba30c, (char *)0x002b9f70, 381, 0);
  system_exit(0);
  player_ui_get_active_player_profile_index();
  /* cmp edi, -1 -> je 0x1c1cb1 */
  player_ui_get_active_player_profile();
  /* relift: cmp word ptr [ebp - 0xa], (int16_t)esi -> je 0x1c1ca3 */
  player_profile_get_from_path();
  player_ui_set_active_player_profile();

  (void)ebx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1c1cc0 */
void FUN_001c1cc0(void)
{
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp (int16_t)ebx, 4 -> jl 0x1c1cf7 */
  display_assert((char *)0x00282750, (char *)0x002b9f70, 407, 0);
  system_exit(0);
  main_get_current_solo_level();
  game_difficulty_level_get();
  /* cmp (int16_t)esi, 0xa -> jge 0x1c1d1c */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1c1d1c */
  /* cmp (int16_t)eax, 4 -> jl 0x1c1d3c */
  display_assert((char *)0x002ba3b0, (char *)0x002b9f70, 413, 0);
  system_exit(0);
  player_ui_get_active_player_profile_index();
  /* cmp edi, -1 -> je 0x1c1d8a */
  player_ui_get_active_player_profile();
  FUN_001c1b00();
  player_ui_set_active_player_profile();
  error(0, (char *)0x002ba348);

  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x1c1da0 */
void FUN_001c1da0(void)
{
  csmemset((void *)0x004eaa38, 0, 116);
}

/* 0x1c1dc0 */
void FUN_001c1dc0(void)
{
  int eax = 0;
  int ecx = 0;

  /* test eax, eax -> je 0x1c1e0b */
  error(0, (char *)0x002ba430);
  thread_is_done((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c1de0 */
  thread_close((void *)(uintptr_t)ecx);
  /* mem[0x004eaaa4] = 0 */
  csmemset((void *)0x004eaa38, 0, 116);

  (void)eax;
  (void)ecx;
}

/* 0x1c1e20 */
void FUN_001c1e20(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;

  FUN_001c5560();
  /* cmp ebx, -1 -> je 0x1c1f4b */
  FUN_001c4850();
  /* test (char)eax, (char)eax -> je 0x1c1f52 */
  game_engine_slayer_default((void *)(uintptr_t)eax);
  csmemcpy((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, 104);
  game_engine_variant_cleanup((void *)(uintptr_t)eax);
  ustrncpy((wchar_t *)(uintptr_t)edx, (wchar_t *)(uintptr_t)ecx, 11);
  saved_game_file_generate_checksum();
  file_set_position((void *)(uintptr_t)edx, 0);
  file_write();
  /* test (char)eax, (char)eax -> jne 0x1c1f3b */
  error(0, (char *)0x002ba4a0);
  delete_enumerated_saved_game_file(0);
  saved_game_file_close();
  error(0, (char *)0x002ba470);
  delete_enumerated_saved_game_file(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
}

/* 0x1c1f70 */
void FUN_001c1f70(void)
{
  int eax = 0;
  int esi = 0;

  /* cmp esi, -1 -> je 0x1c1f99 */
  delete_enumerated_saved_game_file(0);
  /* test (char)eax, (char)eax -> jne 0x1c1f99 */
  error(0, (char *)0x002ba4d4);

  (void)eax;
  (void)esi;
}

/* 0x1c1fa0 */
void playlist_profile_get(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x1c1fdc */
  display_assert((char *)0x002ba584, (char *)0x002ba59c, 243, 0);
  system_exit(0);
  file_reference_create_from_path((void *)(uintptr_t)eax, (char *)(uintptr_t)esi, 0);
  /* test eax, eax -> je 0x1c20b3 */
  file_open((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> je 0x1c20b3 */
  file_read((void *)(uintptr_t)eax, 512, (void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x1c208c */
  saved_game_file_generate_checksum();
  csmemcmp((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, 20);
  /* test eax, eax -> jne 0x1c2085 */
  csmemcpy((void *)(uintptr_t)edi, (void *)(uintptr_t)edx, 104);
  file_close((void *)(uintptr_t)eax);
  error(0, (char *)0x002ba538);
  file_close((void *)(uintptr_t)eax);
  error(0, (char *)0x002ba510);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1c20d0 */
void FUN_001c20d0(void)
{
  int eax = 0;
  int esi = 0;

  saved_game_file_get_display_name();
  /* test eax, eax -> je 0x1c2101 */
  ustrncpy((wchar_t *)(uintptr_t)esi, (wchar_t *)(uintptr_t)eax, 127);

  (void)eax;
  (void)esi;
}

/* 0x1c2110 */
void FUN_001c2110(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1c2120 */
void FUN_001c2120(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  tag_loaded('rtsu', (char *)0x0028a4bc);
  snprintf((char *)(uintptr_t)ecx, 255, (char *)0);
  directory_create_or_delete_contents();
  csstrcat((char *)(uintptr_t)eax, (char *)0x002ba670, 255);
  FUN_0019d420(0, 0);
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)edx, 104);
  ustrncpy((wchar_t *)(uintptr_t)ecx, (wchar_t *)(uintptr_t)esi, 11);
  saved_game_file_generate_checksum();
  file_reference_create_from_path((void *)(uintptr_t)eax, (char *)(uintptr_t)edx, 0);
  /* test eax, eax -> je 0x1c229d */
  FUN_0019a490((void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x1c229d */
  file_open((void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> je 0x1c229d */
  file_set_position((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x1c229d */
  file_write();
  file_close((void *)(uintptr_t)eax);
  /* cmp (char)eax, 1 -> jne 0x1c229d */
  error(0, (char *)0x002ba634);
  /* cmp ebx, 0x1a -> jl 0x1c2150 */
  saved_game_files_notify_memory_units_changed();
  error(0, (char *)0x002ba5d0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1c22e0 */
void playlist_profile_create_default_profiles_on_disk(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;

  display_assert((char *)0x00282808, (char *)0x002ba59c, 396, 0);
  system_exit(0);
  /* test eax, eax -> je 0x1c235b */
  error(0, (char *)0x002ba728);
  thread_is_done((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c2330 */
  thread_close((void *)(uintptr_t)ecx);
  /* mem[0x004eaaa4] = 0 */
  saved_game_files_take_mutex();
  /* test (char)eax, (char)eax -> je 0x1c24d6 */
  FUN_001c4850();
  /* test (char)eax, (char)eax -> je 0x1c24b9 */
  file_read((void *)(uintptr_t)ecx, 512, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c248c */
  saved_game_file_generate_checksum();
  csmemcmp((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, 20);
  /* test eax, eax -> jne 0x1c240f */
  csmemcpy((void *)(uintptr_t)ebx, (void *)(uintptr_t)eax, 104);
  saved_game_file_close();
  saved_game_files_release_mutex();
  game_engine_slayer_default((void *)(uintptr_t)ecx);
  error(0, (char *)0);
  saved_game_file_get_display_name();
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)eax, 0);
  csmemcpy((void *)(uintptr_t)ebx, (void *)(uintptr_t)ecx, 104);
  saved_game_file_close();
  saved_game_files_release_mutex();
  error(0, (char *)0x002ba6a8);
  saved_game_file_close();
  saved_game_files_release_mutex();
  error(0, (char *)0x002ba510);
  saved_game_files_release_mutex();
  error(0, (char *)0x002ba030);
  game_engine_slayer_default((void *)(uintptr_t)eax);
  error(0, (char *)0);
  saved_game_file_get_display_name();
  ustrncpy((wchar_t *)(uintptr_t)edx, (wchar_t *)(uintptr_t)eax, 0);
  csmemcpy((void *)(uintptr_t)ebx, (void *)(uintptr_t)eax, 104);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
}

/* 0x1c2550 */
void playlist_profile_write(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x1c2581 */
  display_assert((char *)0x00266c9c, (char *)0x002ba59c, 514, 0);
  system_exit(0);
  error(0, (char *)0x002ba7ac);
  saved_game_files_take_mutex();
  /* test (char)eax, (char)eax -> je 0x1c2686 */
  FUN_001c4850();
  /* test (char)eax, (char)eax -> je 0x1c266e */
  csmemcpy((void *)(uintptr_t)ecx, (void *)(uintptr_t)esi, 104);
  saved_game_file_generate_checksum();
  file_set_position((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> je 0x1c2616 */
  file_write();
  /* test (char)eax, (char)eax -> jne 0x1c2627 */
  error(0, (char *)0x002ba780);
  saved_game_file_close();
  /* test (char)eax, (char)eax -> je 0x1c2658 */
  FUN_001c4990();
  /* test (char)eax, (char)eax -> jne 0x1c2658 */
  error(0, (char *)0x002ba14c);
  /* test (char)ebx, (char)ebx -> je 0x1c2665 */
  delete_enumerated_saved_game_file(0);
  saved_game_files_release_mutex();
  error(0, (char *)0x002ba510);
  saved_game_files_release_mutex();
  error(0, (char *)0x002ba030);
  error(0, (char *)0x002ba764);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}

/* 0x1c26b0 */
void FUN_001c26b0(void)
{
  /* relift: cmp byte ptr [0x32eb90], 1 -> jne 0x1c26c8 */
  FUN_001c2120();
  FUN_001c53f0();
}

/* 0x1c26f0 */
void playlist_profile_delete(void)
{
  int eax = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x1c271e */
  display_assert((char *)0x00282808, (char *)0x002ba59c, 217, 0);
  system_exit(0);
  /* cmp eax, -1 -> jne 0x1c273a */
  game_engine_playlist_next(0, 0, 0);
  playlist_profile_create_default_profiles_on_disk();

  (void)eax;
  (void)esi;
}

/* 0x1c2750 */
void playlist_profile_read(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x1c2777 */
  display_assert((char *)0x00282808, (char *)0x002ba59c, 490, 0);
  system_exit(0);
  /* test eax, eax -> je 0x1c27bb */
  error(0, (char *)0x002ba728);
  thread_is_done((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c2790 */
  thread_close((void *)(uintptr_t)ecx);
  /* mem[0x004eaaa4] = 0 */
  /* mem[0x004eaa38] = edx */
  csmemcpy((void *)0x004eaa3c, (void *)(uintptr_t)esi, 104);
  thread_new(0, (void *)0x001c2550, 0x004eaa38, (void *)0x004eaaa4);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1c27f0 */
void playlist_profile_get_display_name(void)
{
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x00282808, (char *)0x002ba59c, 305, 0);
  system_exit(0);
  /* cmp edi, -1 -> je 0x1c2833 */
  game_engine_variant_cleanup((void *)(uintptr_t)esi);
  playlist_profile_read();

  (void)esi;
  (void)edi;
}

/* 0x1c2890 */
void saved_game_file_close(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x002ba8c0, (char *)0x002ba8e8, 603, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1c28f6 */
  display_assert((char *)0x002ba8b0, (char *)0x002ba8e8, 606, 0);
  system_exit(0);
  /* test esi, esi -> jl 0x1c28ff */
  /* cmp esi, 2 -> jl 0x1c291f */
  display_assert((char *)0x002ba878, (char *)0x002ba8e8, 607, 0);
  system_exit(0);
  /* test edi, edi -> jl 0x1c2928 */
  /* cmp edi, 9 -> jl 0x1c2948 */
  display_assert((char *)0x002ba838, (char *)0x002ba8e8, 608, 0);
  system_exit(0);
  /* test ebx, ebx -> jl 0x1c2951 */
  /* cmp ebx, 0x64 -> jl 0x1c2971 */
  display_assert((char *)0x002ba7e8, (char *)0x002ba8e8, 609, 0);
  system_exit(0);
  file_close((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c298c */
  /* test edi, edi -> jne 0x1c298c */

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x1c29a0 */
void saved_game_file_get_type(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1c29b0 */
void saved_game_files_notify_memory_units_changed(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1c29c0 */
void saved_game_file_get_useable_untitled_profile_name(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x1c29f1 */
  display_assert((char *)0x002ba974, (char *)0x002ba8e8, 705, 0);
  system_exit(0);
  tag_loaded('rtsu', (char *)0x0028a528);
  wide_to_ascii((wchar_t *)0, (char *)0, 0);
  FUN_0019d420(0, 0);
  unicode_sprintf((wchar_t *)(uintptr_t)esi, 127, (wchar_t *)(uintptr_t)eax);
  FUN_001d2f22();
  /* test eax, eax -> jne 0x1c2aa2 */
  /* cmp ebx, 0x3e7 -> jl 0x1c2a53 */
  error(0, (char *)0x002ba940);
  error(0, (char *)0x002ba918);

  (void)eax;
  (void)ebx;
  (void)esi;
}

/* 0x1c2af0 */
void saved_game_files_take_mutex(void)
{
  int eax = 0;

  take_mutex((void *)(uintptr_t)eax, 0x0036ee80);

  (void)eax;
}

/* 0x1c2b10 */
void saved_game_files_release_mutex(void)
{
  int eax = 0;

  release_mutex((void *)(uintptr_t)eax);

  (void)eax;
}

/* 0x1c2b20 */
void saved_game_perform_file_system_checks(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int ebp = 0;

  wide_to_ascii((wchar_t *)(uintptr_t)ecx, (char *)(uintptr_t)eax, 0);
  FUN_001d3739();
  /* test eax, eax -> je 0x1c2b73 */
  /* test eax, eax -> ja 0x1c2b73 */
  /* relift: cmp dword ptr [ebp - 8], 0x2800000 -> jae 0x1c2b73 */
  wide_to_ascii((wchar_t *)(uintptr_t)ecx, (char *)(uintptr_t)eax, 0);
  FUN_001d3254();
  /* cmp esi, 0x64 -> jae 0x1c2bba */
  FUN_001d335b();
  /* cmp (char)eax, 1 -> je 0x1c2ba3 */
  FUN_001d33a2(0);
  /* test eax, eax -> jne 0x1c2bd3 */
  error(0, (char *)0x002ba984);
  /* cmp esi, 0x64 -> jb 0x1c2be4 */

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)ebp;
}

/* 0x1c2bf0 */
void saved_game_file_name_unique(void)
{
  int eax = 0;
  int edx = 0;

  /* test eax, eax -> je 0x1c2c3a */
  /* relift: cmp word ptr [eax], 0 -> je 0x1c2c3a */
  wide_to_ascii((wchar_t *)(uintptr_t)eax, (char *)(uintptr_t)edx, 0);
  FUN_001d2f22();

  (void)eax;
  (void)edx;
}

/* 0x1c2c50 */
void saved_game_file_remember_player1_last_used_profile_directory(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x1c2c81 */
  display_assert((char *)0x002ba9d4, (char *)0x002ba8e8, 1050, 0);
  system_exit(0);
  file_reference_create_from_path((void *)(uintptr_t)eax, (char *)0x002ba9c4, 0);
  /* test eax, eax -> je 0x1c2d04 */
  FUN_0019a490((void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x1c2d04 */
  file_open((void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> je 0x1c2d04 */
  file_write();
  /* test (char)eax, (char)eax -> jne 0x1c2cf0 */
  error(0, (char *)0x002ba9ac);
  file_close((void *)(uintptr_t)ecx);
  error(0, (char *)0x002ba998);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1c2d20 */
void saved_game_file_retrieve_player1_last_used_profile_directory(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x1c2d54 */
  display_assert((char *)0x002ba9d4, (char *)0x002ba8e8, 1076, 0);
  system_exit(0);
  file_reference_create_from_path((void *)(uintptr_t)eax, (char *)0x002ba9c4, 0);
  /* test eax, eax -> je 0x1c2dd0 */
  file_open((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> je 0x1c2dd0 */
  file_read((void *)(uintptr_t)edx, 256, (void *)(uintptr_t)esi);
  /* test (char)ebx, (char)ebx -> jne 0x1c2db2 */
  error(0, (char *)0x002ba9e4);
  file_close((void *)(uintptr_t)eax);
  error(0, (char *)0x002ba998);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1c2e00 */
void saved_game_file_remember_last_used_multiplayer_variant_directory(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x1c2e31 */
  display_assert((char *)0x002ba9d4, (char *)0x002ba8e8, 1102, 0);
  system_exit(0);
  file_reference_create_from_path((void *)(uintptr_t)eax, (char *)0x002baa00, 0);
  /* test eax, eax -> je 0x1c2eb4 */
  FUN_0019a490((void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x1c2eb4 */
  file_open((void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> je 0x1c2eb4 */
  file_write();
  /* test (char)eax, (char)eax -> jne 0x1c2ea0 */
  error(0, (char *)0x002ba9ac);
  file_close((void *)(uintptr_t)ecx);
  error(0, (char *)0x002ba998);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1c2ed0 */
void saved_game_file_retrieve_last_used_multiplayer_variant_directory(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x1c2f04 */
  display_assert((char *)0x002ba9d4, (char *)0x002ba8e8, 1128, 0);
  system_exit(0);
  file_reference_create_from_path((void *)(uintptr_t)eax, (char *)0x002baa00, 0);
  /* test eax, eax -> je 0x1c2f80 */
  file_open((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> je 0x1c2f80 */
  file_read((void *)(uintptr_t)edx, 256, (void *)(uintptr_t)esi);
  /* test (char)ebx, (char)ebx -> jne 0x1c2f62 */
  error(0, (char *)0x002ba9e4);
  file_close((void *)(uintptr_t)eax);
  error(0, (char *)0x002ba998);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1c2fb0 */
void saved_game_file_remember_last_used_multiplayer_map(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x1c2fe1 */
  display_assert((char *)0x00274e68, (char *)0x002ba8e8, 1207, 0);
  system_exit(0);
  file_reference_create_from_path((void *)(uintptr_t)eax, (char *)0x002baa10, 0);
  /* test eax, eax -> je 0x1c3064 */
  FUN_0019a490((void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x1c3064 */
  file_open((void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> je 0x1c3064 */
  file_write();
  /* test (char)eax, (char)eax -> jne 0x1c3050 */
  error(0, (char *)0x002ba9ac);
  file_close((void *)(uintptr_t)ecx);
  error(0, (char *)0x002ba998);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1c3080 */
void saved_game_file_retrieve_last_used_multiplayer_map(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x1c30b4 */
  display_assert((char *)0x00274e68, (char *)0x002ba8e8, 1233, 0);
  system_exit(0);
  file_reference_create_from_path((void *)(uintptr_t)eax, (char *)0x002baa10, 0);
  /* test eax, eax -> je 0x1c3130 */
  file_open((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> je 0x1c3130 */
  file_read((void *)(uintptr_t)edx, 256, (void *)(uintptr_t)esi);
  /* test (char)ebx, (char)ebx -> jne 0x1c3112 */
  error(0, (char *)0x002ba9e4);
  file_close((void *)(uintptr_t)eax);
  error(0, (char *)0x002ba998);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1c3160 */
void saved_game_file_generate_checksum(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x1c318c */
  display_assert((char *)0x00267900, (char *)0x002ba8e8, 1259, 0);
  system_exit(0);
  XCalculateSignatureBegin();
  /* cmp esi, -1 -> je 0x1c31da */
  FUN_001d42a9();
  /* test eax, eax -> je 0x1c31b9 */
  error(0, (char *)0x002baa64);
  FUN_001d42c3();
  /* test eax, eax -> je 0x1c31e9 */
  error(0, (char *)0x002baa44);
  error(0, (char *)0x002baa20);

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x1c31f0 */
void FUN_001c31f0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  file_reference_create_from_path((void *)(uintptr_t)ecx, (char *)(uintptr_t)eax, 0);
  /* test eax, eax -> je 0x1c3238 */
  file_exists((void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> jne 0x1c323f */
  FUN_0019a490((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0x1c323f */

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x1c3250 */
void FUN_001c3250(void)
{
  int eax = 0;
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> je 0x1c3279 */
  display_assert((char *)0x002ba8c0, (char *)0x002ba8e8, 1643, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1c32a2 */
  display_assert((char *)0x002baac8, (char *)0x002ba8e8, 1647, 0);
  system_exit(0);
  file_reference_create_from_path((void *)0x004eabb0, (char *)(uintptr_t)eax, 0);
  /* test eax, eax -> je 0x1c32f6 */
  FUN_0019a490((void *)0x004eabb0);
  /* test (char)eax, (char)eax -> je 0x1c32f6 */
  file_open((void *)0x004eabb0, 0);
  /* test (char)eax, (char)eax -> je 0x1c32f6 */
  error(0, (char *)0x002baa88);

  (void)eax;
  (void)esi;
}

/* 0x1c3320 */
void FUN_001c3320(void)
{
  int eax = 0;
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> je 0x1c3345 */
  display_assert((char *)0x002ba8c0, (char *)0x002ba8e8, 1669, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x1c336e */
  display_assert((char *)0x002bab34, (char *)0x002ba8e8, 1671, 0);
  system_exit(0);
  file_close((void *)0x004eabb0);
  /* test (char)eax, (char)eax -> jne 0x1c3392 */
  error(0, (char *)0x002baafc);

  (void)eax;
  (void)esi;
}

/* 0x1c33b0 */
void FUN_001c33b0(void)
{
  int eax = 0;

  /* test (char)eax, (char)eax -> je 0x1c33c4 */
  /* test (int16_t)eax, (int16_t)eax -> jge 0x1c33ea */
  display_assert((char *)0x002babe0, (char *)0x002ba8e8, 1857, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 0x64 -> jge 0x1c3412 */
  file_write();
  error(0, (char *)0x002bab68);

  (void)eax;
}

/* 0x1c3430 */
void FUN_001c3430(void)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> je 0x1c3459 */
  display_assert((char *)0x002bacc8, (char *)0x002ba8e8, 1883, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1c3482 */
  display_assert((char *)0x002baac8, (char *)0x002ba8e8, 1887, 0);
  system_exit(0);
  file_reference_create_from_path((void *)0x004eabb0, (char *)(uintptr_t)eax, 0);
  /* test eax, eax -> je 0x1c34e1 */
  file_open((void *)0x004eabb0, 0);
  /* test (char)eax, (char)eax -> je 0x1c34e1 */
  file_get_eof((void *)0x004eabb0);
  /* test edx, edx -> je 0x1c34dd */
  error(0, (char *)0x002bac8c);
  error(0, (char *)0x002bac54);

  (void)eax;
  (void)edx;
  (void)esi;
}

/* 0x1c3500 */
void FUN_001c3500(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> je 0x1c3525 */
  display_assert((char *)0x002bacc8, (char *)0x002ba8e8, 1916, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1c354e */
  display_assert((char *)0x002baac8, (char *)0x002ba8e8, 1918, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 9 -> jb 0x1c3574 */
  display_assert((char *)0x002bad24, (char *)0x002ba8e8, 1919, 0);
  system_exit(0);
  file_close((void *)0x004eabb0);
  /* test (char)ebx, (char)ebx -> jne 0x1c359b */
  error(0, (char *)0x002bacf4);

  (void)eax;
  (void)ebx;
  (void)esi;
}

/* 0x1c35a0 */
void FUN_001c35a0(void)
{
  int eax = 0;
  int esi = 0;

  /* test (char)eax, (char)eax -> je 0x1c35c9 */
  display_assert((char *)0x002baac8, (char *)0x002ba8e8, 1939, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x1c35ed */
  display_assert((char *)0x00265878, (char *)0x002ba8e8, 1940, 0);
  system_exit(0);
  file_read((void *)0x004eabb0, 518, (void *)(uintptr_t)esi);

  (void)eax;
  (void)esi;
}

/* 0x1c3610 */
void FUN_001c3610(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> je 0x1c3639 */
  display_assert((char *)0x002bacc8, (char *)0x002ba8e8, 2144, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1c3662 */
  display_assert((char *)0x002baac8, (char *)0x002ba8e8, 2146, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 9 -> jb 0x1c3688 */
  display_assert((char *)0x002bad24, (char *)0x002ba8e8, 2147, 0);
  system_exit(0);
  file_reference_create_from_path((void *)0x004eabb0, (char *)(uintptr_t)ecx, 0);
  /* test eax, eax -> je 0x1c36cc */
  file_get_size();
  /* test (char)eax, (char)eax -> je 0x1c36cc */
  take_mutex((void *)(uintptr_t)eax, 0x0036ee80);
  release_mutex((void *)(uintptr_t)eax);

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x1c3710 */
void FUN_001c3710(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1c38d0 */
void saved_game_file_find_profile_index_for_directory_path(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x002ba9d4, (char *)0x002ba8e8, 1158, 0);
  system_exit(0);
  csstrlen((char *)(uintptr_t)esi);
  take_mutex((void *)(uintptr_t)eax, 0x0036ee80);
  /* test (char)eax, (char)eax -> je 0x1c3a0f */
  take_mutex((void *)(uintptr_t)ecx, 0x0036ee80);
  /* test (char)eax, (char)eax -> je 0x1c39e9 */
  FUN_001c3610();
  FUN_001c3430();
  /* test (char)eax, (char)eax -> je 0x1c39c2 */
  /* test ebx, ebx -> jle 0x1c39b8 */
  FUN_001c35a0();
  /* test (char)eax, (char)eax -> je 0x1c39b8 */
  /* relift: cmp word ptr [ebp - 0x14], (int16_t)esi -> jne 0x1c3997 */
  __strnicmp((char *)(uintptr_t)ecx, (char *)(uintptr_t)eax, edx);
  /* test eax, eax -> je 0x1c399e */
  /* cmp edi, ebx -> jl 0x1c3963 */
  FUN_001c3710();
  FUN_001c3500();
  release_mutex((void *)(uintptr_t)ecx);
  release_mutex((void *)(uintptr_t)edx);
  error(0, (char *)0x002bae8c);
  release_mutex((void *)(uintptr_t)edx);
  error(0, (char *)0x002bae64);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1c3a30 */
void FUN_001c3a30(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

  FUN_001c2110();
  tag_loaded('rtsu', (char *)0x0028a4bc);
  /* test (int16_t)esi, (int16_t)esi -> jle 0x1c3c2f */
  FUN_0019d420(0, 0);
  snprintf((char *)(uintptr_t)ecx, 255, (char *)0x002bb024);
  file_reference_create_from_path((void *)(uintptr_t)eax, (char *)(uintptr_t)edx, 0);
  /* test eax, eax -> je 0x1c3beb */
  file_exists((void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x1c3beb */
  csstrncpy((char *)(uintptr_t)eax, (char *)(uintptr_t)edx, 0);
  ustrncpy((wchar_t *)(uintptr_t)ecx, (wchar_t *)(uintptr_t)esi, 127);
  file_open((void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> je 0x1c3bca */
  file_read((void *)(uintptr_t)ecx, 512, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c3ba1 */
  saved_game_file_generate_checksum();
  csmemcmp((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, 20);
  /* test eax, eax -> jne 0x1c3b89 */
  error(0, (char *)0x002bb000);
  error(0, (char *)0x002bafc4);
  file_close((void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> jne 0x1c3bd9 */
  error(0, (char *)0x002baf40);
  FUN_001c33b0();
  /* test (char)eax, (char)eax -> je 0x1c3c00 */
  /* relift: cmp (int16_t)ebx, word ptr [ebp - 8] -> jl 0x1c3a71 */
  error(0, (char *)0x002baf10);
  error(0, (char *)0x002baeb0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)ebp;
}

/* 0x1c3c40 */
void FUN_001c3c40(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  tag_loaded(0x75737472, (char *)0x002898d0);
  FUN_0019d420(0, 0);
  snprintf((char *)(uintptr_t)ecx, 255, (char *)0x002ba2d8);
  file_reference_create_from_path((void *)(uintptr_t)eax, (char *)(uintptr_t)edx, 0);
  /* test eax, eax -> je 0x1c3de8 */
  file_exists((void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x1c3de8 */
  csstrncpy((char *)(uintptr_t)eax, (char *)(uintptr_t)edx, 0);
  ustrncpy((wchar_t *)(uintptr_t)ecx, (wchar_t *)(uintptr_t)esi, 127);
  file_open((void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> je 0x1c3dc7 */
  file_read((void *)(uintptr_t)ecx, 512, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c3d9e */
  saved_game_file_generate_checksum();
  csmemcmp((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, 20);
  /* test eax, eax -> jne 0x1c3d86 */
  error(0, (char *)0x002bb000);
  error(0, (char *)0x002bb188);
  file_close((void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> jne 0x1c3dd6 */
  error(0, (char *)0x002bb0f8);
  FUN_001c33b0();
  /* test (char)eax, (char)eax -> je 0x1c3dfd */
  /* cmp (int16_t)ebx, 2 -> jl 0x1c3c70 */
  error(0, (char *)0x002bb0bc);
  error(0, (char *)0x002bb058);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1c3e40 */
void FUN_001c3e40(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  display_assert((char *)0x002bacc8, (char *)0x002ba8e8, 1959, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1c3e9e */
  display_assert((char *)0x002baac8, (char *)0x002ba8e8, 1961, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 9 -> jae 0x1c3eab */
  /* test eax, eax -> jne 0x1c3ecb */
  display_assert((char *)0x002bb244, (char *)0x002ba8e8, 1962, 0);
  system_exit(0);
  take_mutex((void *)(uintptr_t)eax, 0x0036ee80);
  /* test (char)eax, (char)eax -> je 0x1c400b */
  file_reference_create_from_path((void *)0x004eabb0, (char *)(uintptr_t)ecx, 0);
  /* test eax, eax -> je 0x1c3fe3 */
  file_open((void *)0x004eabb0, 0);
  /* test (char)eax, (char)eax -> je 0x1c3fe3 */
  file_get_eof((void *)0x004eabb0);
  /* test edx, edx -> je 0x1c3f5c */
  error(0, (char *)0x002bac8c);
  /* cmp eax, ebx -> ja 0x1c3fa8 */
  file_set_position((void *)0x004eabb0, 0);
  /* test (char)eax, (char)eax -> je 0x1c3f98 */
  file_read((void *)0x004eabb0, 518, (void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x1c3f98 */
  error(0, (char *)0x002bb1cc);
  file_close((void *)0x004eabb0);
  /* test (char)eax, (char)eax -> jne 0x1c3ff3 */
  error(0, (char *)0x002baafc);
  error(0, (char *)0x002bac54);
  release_mutex((void *)(uintptr_t)edx);
  error(0, (char *)0x002bae8c);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1c4030 */
void FUN_001c4030(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  display_assert((char *)0x002bacc8, (char *)0x002ba8e8, 2018, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1c408e */
  display_assert((char *)0x002baac8, (char *)0x002ba8e8, 2020, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 9 -> jae 0x1c409b */
  /* test eax, eax -> jne 0x1c40bb */
  display_assert((char *)0x002bb244, (char *)0x002ba8e8, 2021, 0);
  system_exit(0);
  take_mutex((void *)(uintptr_t)eax, 0x0036ee80);
  /* test (char)eax, (char)eax -> je 0x1c41f3 */
  file_reference_create_from_path((void *)0x004eabb0, (char *)(uintptr_t)ecx, 0);
  /* test eax, eax -> je 0x1c41ca */
  file_open((void *)0x004eabb0, 0);
  /* test (char)eax, (char)eax -> je 0x1c41ca */
  file_get_eof((void *)0x004eabb0);
  /* test edx, edx -> je 0x1c4149 */
  error(0, (char *)0x002bac8c);
  /* cmp edx, eax -> ja 0x1c4195 */
  file_set_position((void *)0x004eabb0, 0);
  /* test (char)eax, (char)eax -> je 0x1c4188 */
  file_write();
  /* test (char)eax, (char)eax -> je 0x1c4188 */
  error(0, (char *)0x002bb1cc);
  file_close((void *)0x004eabb0);
  /* test (char)eax, (char)eax -> jne 0x1c41da */
  error(0, (char *)0x002baafc);
  error(0, (char *)0x002bac54);
  release_mutex((void *)(uintptr_t)ecx);
  error(0, (char *)0x002bae8c);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1c4210 */
void FUN_001c4210(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x002bacc8, (char *)0x002ba8e8, 2081, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1c426c */
  display_assert((char *)0x002baac8, (char *)0x002ba8e8, 2083, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 9 -> jae 0x1c4280 */
  /* test eax, eax -> je 0x1c4280 */
  /* test eax, eax -> jne 0x1c42a0 */
  display_assert((char *)0x002bb360, (char *)0x002ba8e8, 2084, 0);
  system_exit(0);
  take_mutex((void *)(uintptr_t)eax, 0x0036ee80);
  /* test (char)eax, (char)eax -> je 0x1c43d7 */
  file_reference_create_from_path((void *)0x004eabb0, (char *)(uintptr_t)ecx, 0);
  /* test eax, eax -> je 0x1c43af */
  file_open((void *)0x004eabb0, 0);
  /* test (char)eax, (char)eax -> je 0x1c43af */
  file_get_eof((void *)0x004eabb0);
  /* cmp edi, 0x64 -> jge 0x1c437b */
  /* test edx, edx -> je 0x1c432e */
  error(0, (char *)0x002bac8c);
  file_set_position((void *)0x004eabb0, 0);
  /* test (char)eax, (char)eax -> je 0x1c4365 */
  file_write();
  /* test (char)eax, (char)eax -> je 0x1c4365 */
  error(0, (char *)0x002bb32c);
  error(0, (char *)0x002bb2c0);
  file_close((void *)0x004eabb0);
  error(0, (char *)0x002baafc);
  error(0, (char *)0x002bac54);
  release_mutex((void *)(uintptr_t)ecx);
  error(0, (char *)0x002bae8c);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1c43f0 */
void FUN_001c43f0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;
  int ebp = 0;

  /* test (int16_t)edi, (int16_t)edi -> je 0x1c442f */
  display_assert((char *)0x002bacc8, (char *)0x002ba8e8, 2170, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1c4458 */
  display_assert((char *)0x002baac8, (char *)0x002ba8e8, 2172, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 9 -> jb 0x1c447e */
  display_assert((char *)0x002bad24, (char *)0x002ba8e8, 2173, 0);
  system_exit(0);
  take_mutex((void *)(uintptr_t)eax, 0x0036ee80);
  /* test (char)eax, (char)eax -> je 0x1c45da */
  file_reference_create_from_path((void *)0x004eabb0, (char *)(uintptr_t)edx, 0);
  /* test eax, eax -> je 0x1c45c2 */
  file_get_size();
  /* test (char)eax, (char)eax -> je 0x1c45c2 */
  /* cmp eax, edi -> jb 0x1c45c2 */
  file_open((void *)0x004eabb0, 0);
  /* test (char)eax, (char)eax -> je 0x1c45c2 */
  file_set_position((void *)0x004eabb0, 0);
  /* cmp (char)ebx, 1 -> jne 0x1c4584 */
  /* relift: cmp edi, dword ptr [ebp - 4] -> jae 0x1c4588 */
  file_read_from_position((void *)0x004eabb0, 0, 518, (void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x1c4571 */
  file_write_to_position();
  /* test (char)eax, (char)eax -> je 0x1c4571 */
  /* cmp edi, eax -> jb 0x1c4520 */
  error(0, (char *)0x002bb3e8);
  /* test (char)ebx, (char)ebx -> je 0x1c45a0 */
  file_set_eof();
  file_close((void *)0x004eabb0);
  /* test (char)eax, (char)eax -> jne 0x1c45c2 */
  error(0, (char *)0x002bb3bc);
  release_mutex((void *)(uintptr_t)ecx);
  error(0, (char *)0x002bae8c);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)ebp;
}

/* 0x1c4600 */
void saved_game_file_get_display_name(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x002ba8c0, (char *)0x002ba8e8, 299, 0);
  system_exit(0);
  /* cmp esi, 9 -> jge 0x1c4699 */
  /* test edi, edi -> jl 0x1c4699 */
  /* cmp edi, 0x64 -> jge 0x1c4699 */
  FUN_001c3e40();
  /* test (char)eax, (char)eax -> je 0x1c46a8 */
  ustrncpy((wchar_t *)0x004eaab0, (wchar_t *)(uintptr_t)ecx, 127);
  error(0, (char *)0x002bb430);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x1c46c0 */
char delete_enumerated_saved_game_file(int param_1)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  error(0, (char *)0x002bb590);
  ui_widget_clear_last_error_index();
  /* test ebx, ebx -> je 0x1c472e */
  display_assert((char *)0x002ba8c0, (char *)0x002ba8e8, 495, 0);
  system_exit(0);
  /* test esi, esi -> jl 0x1c482a */
  /* cmp esi, 2 -> jge 0x1c482a */
  /* test ebx, ebx -> jl 0x1c482a */
  /* cmp ebx, 9 -> jge 0x1c482a */
  /* test edi, edi -> jl 0x1c482a */
  /* cmp edi, 0x64 -> jge 0x1c482a */
  FUN_001c3e40();
  /* test (char)eax, (char)eax -> je 0x1c4823 */
  /* relift: test dword ptr [ebp + 8], 0x40000000 -> jne 0x1c47d9 */
  wide_to_ascii((wchar_t *)(uintptr_t)ecx, (char *)(uintptr_t)eax, 0);
  FUN_001d3185();
  /* test eax, eax -> je 0x1c47d9 */
  error(0, (char *)0x002bb55c);
  FUN_001c43f0();
  /* test (char)eax, (char)eax -> jne 0x1c47f9 */
  error(0, (char *)0x002bb534);
  /* test ebx, ebx -> je 0x1c4839 */
  error(0, (char *)0x002bb4f4);
  ui_widget_clear_last_error_index();
  error(0, (char *)0x002bb450);
  ui_widget_clear_last_error_index();
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1c4850 */
void FUN_001c4850(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x002ba8c0, (char *)0x002ba8e8, 577, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1c48bc */
  display_assert((char *)0x002ba8b0, (char *)0x002ba8e8, 580, 0);
  system_exit(0);
  /* test esi, esi -> jl 0x1c48c5 */
  /* cmp esi, 2 -> jl 0x1c48e5 */
  display_assert((char *)0x002ba878, (char *)0x002ba8e8, 581, 0);
  system_exit(0);
  /* test ebx, ebx -> jl 0x1c48ee */
  /* cmp ebx, 9 -> jl 0x1c490e */
  display_assert((char *)0x002ba838, (char *)0x002ba8e8, 582, 0);
  system_exit(0);
  /* test edi, edi -> jl 0x1c4917 */
  /* cmp edi, 0x64 -> jl 0x1c4937 */
  display_assert((char *)0x002ba7e8, (char *)0x002ba8e8, 583, 0);
  system_exit(0);
  FUN_001c3e40();
  /* test (char)eax, (char)eax -> je 0x1c4981 */
  file_reference_create_from_path((void *)(uintptr_t)esi, (char *)(uintptr_t)ecx, 0);
  /* test eax, eax -> je 0x1c4981 */
  /* test ebx, ebx -> jne 0x1c4981 */
  file_open((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> je 0x1c4981 */
  display_assert((char *)0x002ba8c0, (char *)0x002ba8e8, 774, 0);
  system_exit(0);
  /* test esi, esi -> jl 0x1c49e4 */
  /* cmp esi, 2 -> jl 0x1c4a04 */
  display_assert((char *)0x002ba878, (char *)0x002ba8e8, 777, 0);
  system_exit(0);
  /* test edi, edi -> jl 0x1c4a0d */
  /* cmp edi, 9 -> jl 0x1c4a2d */
  display_assert((char *)0x002ba838, (char *)0x002ba8e8, 778, 0);
  system_exit(0);
  /* test eax, eax -> jl 0x1c4a39 */
  /* cmp eax, 0x64 -> jl 0x1c4a59 */
  display_assert((char *)0x002ba7e8, (char *)0x002ba8e8, 779, 0);
  system_exit(0);
  ustrlen((void *)(uintptr_t)eax);
  /* cmp eax, 0x80 -> jb 0x1c4a8c */
  display_assert((char *)0x002bb7c0, (char *)0x002ba8e8, 781, 0);
  system_exit(0);
  FUN_001c3e40();
  /* test (char)eax, (char)eax -> je 0x1c4d80 */
  /* test eax, eax -> je 0x1c4d8f */
  /* relift: cmp word ptr [eax], 0 -> je 0x1c4d8f */
  ustrcmp((wchar_t *)(uintptr_t)edx, (wchar_t *)(uintptr_t)eax);
  /* test eax, eax -> je 0x1c4d8f */
  /* test esi, esi -> jne 0x1c4d67 */
  wide_to_ascii((wchar_t *)(uintptr_t)eax, (char *)(uintptr_t)edx, 0);
  FUN_001d2f22();
  /* test eax, eax -> jne 0x1c4d4f */
  display_assert((char *)0x002bb7a0, (char *)0x002ba8e8, 835, 0);
  system_exit(0);
  snprintf((char *)(uintptr_t)edx, 255, (char *)0x0025bf84);
  snprintf((char *)(uintptr_t)eax, 255, (char *)0x0025bf84);
  FUN_001d21f2();
  /* cmp (char)ebx, 1 -> jne 0x1c4d25 */
  csstrncpy((char *)(uintptr_t)ecx, (char *)(uintptr_t)eax, 255);
  crt_strstr((char *)(uintptr_t)edx, (char *)0x002bb788);
  /* test eax, eax -> je 0x1c4b6a */
  FUN_001c0720();
  csstrcat((char *)(uintptr_t)eax, (char *)(uintptr_t)eax, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
