#include <stdint.h>
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

/* FUN_001c1b00 (0x1c1b00) — readable C lift (esi=out). */
void FUN_001c1b00(int profile_handle, void *out /* @<esi> */)
{
  extern char DAT_002829b0[];
  extern char DAT_002b9f70[];
  extern char DAT_002ba0f8[];
  void *thr;

  __asm__ volatile("movl %%esi, %0" : "=r"(out));
  if (out == 0) {
    display_assert(DAT_002829b0, DAT_002b9f70, 0x2c0, 1);
    system_exit(-1);
  }
  thr = *(void **)0x4eaa2c;
  if (thr != 0) {
    error(2, DAT_002ba0f8);
    while (!thread_is_done(thr))
      ;
    thread_close(*(void **)0x4eaa2c);
    *(void **)0x4eaa2c = 0;
  }
  *(int *)0x4ea9f8 = profile_handle;
  csmemcpy((void *)0x4ea9fc, out, 0x30);
  thread_new(0, (void *)0x1c15c0, (int)0x4ea9f8, (void **)0x4eaa2c);
}
/* FUN_001c1ba0 (0x1c1ba0) — readable C lift. */
void FUN_001c1ba0(void)
{
  extern char DAT_004ea9c8[];
  char *base = (char *)csmemset(DAT_004ea9c8, 0, 0x6c);
  base[0x68] = 1; /* DAT_004eaa30 */
  FUN_001c19e0();
}

/* player_profile_get_from_path (0x1c1bc0) — readable C lift. */
void player_profile_get_from_path(int profile_handle, void *out)
{
  extern char DAT_002829b0[];
  extern char DAT_002b9f70[];

  if (!out) {
    display_assert(DAT_002829b0, DAT_002b9f70, 0x100, 1);
    system_exit(-1);
  }
  if (profile_handle != -1) {
    __asm__ volatile("movl %0, %%esi" : : "r"(out) : "esi");
    FUN_001c1b00(profile_handle, out);
  }
}

/* FUN_001c1c00 (0x1c1c00) — readable C lift. */
void FUN_001c1c00(int16_t local_player_index)
{
  int16_t solo_level;
  int profile_handle;
  char profile[0x30];

  solo_level = (int16_t)main_get_current_solo_level();
  if (local_player_index < 0 || local_player_index >= 4) {
    display_assert((const char *)0x282750, (const char *)0x2b9f70, 0x17a, 1);
    system_exit(-1);
  }
  if (solo_level == -1)
    return;
  if (solo_level < 0 || solo_level >= 10) {
    display_assert((const char *)0x2ba30c, (const char *)0x2b9f70, 0x17d, 1);
    system_exit(-1);
  }
  profile_handle = player_ui_get_active_player_profile_index(local_player_index);
  if (profile_handle == -1)
    return;
  player_ui_get_active_player_profile(local_player_index, profile);
  if (*(int16_t *)(profile + 0x26) != solo_level) {
    *(int16_t *)(profile + 0x26) = solo_level;
    player_profile_get_from_path(profile_handle, profile);
  }
  player_ui_set_active_player_profile(local_player_index, profile_handle, profile);
}



/* FUN_001c1cc0 (0x1c1cc0) - readable C lift. */
void FUN_001c1cc0(int16_t local_player_index)
{
  int16_t solo_level;
  int16_t difficulty;
  int profile_handle;
  char profile[0x30];
  unsigned char mask;

  if (local_player_index < 0 || local_player_index >= 4) {
    display_assert((const char *)0x282750, (const char *)0x2b9f70, 0x197, 1);
    system_exit(-1);
  }
  solo_level = (int16_t)main_get_current_solo_level();
  difficulty = game_difficulty_level_get();
  if (solo_level < 0 || solo_level >= 10 || difficulty < 0 || difficulty >= 4) {
    display_assert((const char *)0x2ba3b0, (const char *)0x2b9f70, 0x19d, 1);
    system_exit(-1);
  }
  profile_handle = player_ui_get_active_player_profile_index(local_player_index);
  if (profile_handle == -1) {
    error(2, (const char *)0x2ba348);
    return;
  }
  player_ui_get_active_player_profile(local_player_index, profile);
  mask = (unsigned char)(1u << (unsigned char)difficulty);
  profile[0x1c + solo_level] = (char)((unsigned char)profile[0x1c + solo_level] | mask);
  __asm__ volatile("movl %0, %%esi" : : "r"((void *)profile) : "esi");
  FUN_001c1b00(profile_handle, profile);
  player_ui_set_active_player_profile(local_player_index, profile_handle, profile);
}


/* FUN_001c1da0 (0x1c1da0) — readable C lift. */
void FUN_001c1da0(void)
{
  extern char DAT_004eaa38[];
  char *base = (char *)csmemset(DAT_004eaa38, 0, 0x74);
  base[0x72] = 1; /* DAT_004eaaaa */
}

/* FUN_001c1dc0 (0x1c1dc0) — readable C lift from XBE leaf. */
void FUN_001c1dc0(void)
{
  extern char DAT_002ba430[];

  if (*(void **)0x4eaaa4 != 0) {
    error(2, DAT_002ba430);
    while (!thread_is_done(*(void **)0x4eaaa4)) {
    }
    thread_close(*(void **)0x4eaaa4);
    *(void **)0x4eaaa4 = 0;
  }
  csmemset((void *)0x4eaa38, 0, 0x74);
}




/* FUN_001c1e20 (0x1c1e20) — readable C lift. */
int FUN_001c1e20(int a0, wchar_t *name)
{
  int handle;
  file_ref_t ref;
  game_variant_t tmp;
  unsigned char variant[0x200];
  game_variant_t *def;
  char ok;

  handle = ((int (*)(int, int, int))(void *)FUN_001c5560)(1, a0, (int)name);
  if (handle == -1)
    return -1;
  if (!FUN_001c4850(&ref, handle)) {
    error(2, (const char *)0x2ba470);
    delete_enumerated_saved_game_file(handle);
    return -1;
  }

  csmemset(variant, 0, 0x200);
  def = game_engine_slayer_default(&tmp);
  csmemcpy(variant, def, 0x68);
  variant[0x64] = (unsigned char)(variant[0x64] & 0xfe);
  game_engine_variant_cleanup((game_variant_t *)variant);
  ustrncpy((wchar_t *)variant, name, 0xb);
  ((wchar_t *)variant)[0xb] = 0;
  saved_game_file_generate_checksum(variant, 0x68, variant + 0x68);

  ok = file_set_position(&ref, 0);
  if (ok)
    ok = file_write(&ref, 0x200, variant);
  if (!ok) {
    error(2, (const char *)0x2ba4a0);
    delete_enumerated_saved_game_file(handle);
    handle = -1;
  }
  saved_game_file_close(&ref, handle);
  return handle;
}

/* FUN_001c1f70 (0x1c1f70) — readable C lift. */
void FUN_001c1f70(int profile_index)
{
  extern char DAT_002ba4d4[];

  if (profile_index == -1)
    return;
  if (!delete_enumerated_saved_game_file(profile_index))
    error(2, DAT_002ba4d4, profile_index);
}

/* playlist_profile_get (0x1c1fa0) — readable C lift. */
char playlist_profile_get(const char *path, void *out_variant)
{
  file_ref_t ref;
  unsigned char buf[0x200];
  unsigned char sig[0x14];
  char ok;

  ok = 0;
  if (!path || !out_variant) {
    display_assert((const char *)0x2ba584, (const char *)0x2ba59c, 0xf3, 1);
    system_exit(-1);
  }
  if (!file_reference_create_from_path(&ref, path, 0)) {
    error(2, (const char *)0x2ba510);
    return 0;
  }
  if (!file_open(&ref, 1)) {
    error(2, (const char *)0x2ba510);
    return 0;
  }
  if (!file_read(&ref, 0x200, buf)) {
    error(2, (const char *)0x2ba538);
    file_close(&ref);
    return 0;
  }
  saved_game_file_generate_checksum(buf, 0x68, sig);
  if (csmemcmp(sig, buf + 0x68, 0x14) != 0) {
    error(2, (const char *)0x2ba558);
    file_close(&ref);
    return 0;
  }
  csmemcpy(out_variant, buf, 0x68);
  ok = 1;
  file_close(&ref);
  return ok;
}

/* FUN_001c20d0 (0x1c20d0) — readable C lift. */
char FUN_001c20d0(int file_index, wchar_t *out_name)
{
  wchar_t *name;

  name = saved_game_file_get_display_name(file_index);
  if (!name)
    return 0;
  ustrncpy(out_name, name, 0x7f);
  out_name[0x7f] = 0;
  return 1;
}

/* 0x1c2110 */
void FUN_001c2110(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_001c2120 (0x1c2120) — readable C lift. */
void FUN_001c2120(void)
{
  int tag;
  int i;
  game_variant_t tmp;
  game_variant_t *def;
  char path[0xff];
  file_ref_t ref;
  unsigned char variant[0x200];
  wchar_t *disp;
  char wrote;

  tag = tag_loaded(0x75737472, (const char *)0x28a4bc);
  if (tag == -1) {
    error(2, (const char *)0x2ba5d0);
    return;
  }
  for (i = 0; i < 0x1a; i++) {
    def = ((game_variant_t * (*)(game_variant_t *))(void *)(*(void **)(0x32eb28 + 4 * i)))(&tmp);
    csmemcpy(&tmp, def, 0x68);
    snprintf(path, 0xff, (const char *)0x2ba67c, i);
    path[0xfe] = 0;
    directory_create_or_delete_contents(path);
    csstrcat(path, (const char *)0x2ba670, 0xff);
    path[0xfe] = 0;
    disp = (wchar_t *)FUN_0019d420(tag, i);
    csmemcpy(variant, &tmp, 0x68);
    ustrncpy((wchar_t *)variant, disp, 0xb);
    ((wchar_t *)variant)[0xb] = 0;
    *(uint16_t *)(variant + 0x64) =
        (uint16_t)(*(uint16_t *)(variant + 0x64) | (uint16_t)(i << 8));
    saved_game_file_generate_checksum(variant, 0x68, variant + 0x68);

    wrote = 0;
    if (file_reference_create_from_path(&ref, path, 0) &&
        FUN_0019a490(&ref) && file_open(&ref, 2) && file_set_position(&ref, 0)) {
      wrote = file_write(&ref, 0x200, variant);
      file_close(&ref);
      if (wrote == 1) {
        *(uint16_t *)0x4eaaa8 = (uint16_t)(*(uint16_t *)0x4eaaa8 + 1);
        continue;
      }
    }
    error(2, (const char *)0x2ba634, path);
  }
  saved_game_files_notify_memory_units_changed();
}

/* playlist_profile_create_default_profiles_on_disk (0x1c22e0) — readable C lift (restored pre-naked). */
char playlist_profile_create_default_profiles_on_disk(int profile_index)
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
  ((void(*)(void))FUN_001c4850)();
  /* test (char)eax, (char)eax -> je 0x1c24b9 */
  file_read((void *)(uintptr_t)ecx, 512, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c248c */
  ((void(*)(void))saved_game_file_generate_checksum)();
  csmemcmp((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, 20);
  /* test eax, eax -> jne 0x1c240f */
  csmemcpy((void *)(uintptr_t)ebx, (void *)(uintptr_t)eax, 104);
  ((void(*)(void))saved_game_file_close)();
  saved_game_files_release_mutex();
  game_engine_slayer_default((void *)(uintptr_t)ecx);
  error(0, (char *)0);
  ((void(*)(void))saved_game_file_get_display_name)();
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)eax, 0);
  csmemcpy((void *)(uintptr_t)ebx, (void *)(uintptr_t)ecx, 104);
  ((void(*)(void))saved_game_file_close)();
  saved_game_files_release_mutex();
  error(0, (char *)0x002ba6a8);
  ((void(*)(void))saved_game_file_close)();
  saved_game_files_release_mutex();
  error(0, (char *)0x002ba510);
  saved_game_files_release_mutex();
  error(0, (char *)0x002ba030);
  game_engine_slayer_default((void *)(uintptr_t)eax);
  error(0, (char *)0);
  ((void(*)(void))saved_game_file_get_display_name)();
  ustrncpy((wchar_t *)(uintptr_t)edx, (wchar_t *)(uintptr_t)eax, 0);
  csmemcpy((void *)(uintptr_t)ebx, (void *)(uintptr_t)eax, 104);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
}


/* playlist_profile_write (0x1c2550) — readable C lift. */
char playlist_profile_write(void *args)
{
  int profile_index;
  void *variant;
  file_ref_t ref;
  unsigned char buf[0x200];
  char failed_io;
  char ok_close;

  if (!args) {
    display_assert((const char *)0x266c9c, (const char *)0x2ba59c, 0x202, 1);
    system_exit(-1);
  }
  error(2, (const char *)0x2ba7ac);
  if (!take_mutex(*(int **)0x4eacbc, 0x36ee80)) {
    error(2, (const char *)0x2ba030);
    error(2, (const char *)0x2ba764);
    return 0;
  }

  profile_index = *(int *)args;
  variant = (char *)args + 4;
  failed_io = 0;
  if (!FUN_001c4850(&ref, profile_index)) {
    error(2, (const char *)0x2ba510);
    saved_game_files_release_mutex();
    error(2, (const char *)0x2ba764);
    return 0;
  }

  csmemcpy(buf, variant, 0x68);
  saved_game_file_generate_checksum(buf, 0x68, buf + 0x68);
  if (!file_set_position(&ref, 0) || !file_write(&ref, 0x200, buf)) {
    error(2, (const char *)0x2ba780);
    failed_io = 1;
  }
  ok_close = saved_game_file_close(&ref, profile_index);
  if (ok_close) {
    if (!((char (*)(int, void *))(void *)FUN_001c4990)(profile_index, variant))
      error(2, (const char *)0x2ba14c);
  }
  if (failed_io)
    delete_enumerated_saved_game_file(profile_index);
  saved_game_files_release_mutex();
  error(2, (const char *)0x2ba764);
  return 0;
}

/* FUN_001c26b0 (0x1c26b0) — readable C lift. */
void FUN_001c26b0(int a0, int a1, int a2)
{
  if (*(char *)0x32eb90 == 1) {
    FUN_001c2120();
    *(char *)0x32eb90 = 0;
  }
  FUN_001c53f0(a0, 1, a1, a2, 1);
}

/* playlist_profile_delete (0x1c26f0) — readable C lift from XBE leaf. */
char playlist_profile_delete(int profile_index, void *variant)
{
  extern char DAT_00282808[];
  extern char DAT_002ba59c[];

  if (variant == 0) {
    display_assert(DAT_00282808, DAT_002ba59c, 0xd9, true);
    system_exit(-1);
  }
  if (profile_index == -1) {
    game_engine_playlist_next(0, 0, 4);
    return 0;
  }
  return playlist_profile_create_default_profiles_on_disk(profile_index);
}






/* playlist_profile_read (0x1c2750) — readable C lift (esi=out). */
void playlist_profile_read(int profile_index)
{
  extern char DAT_00282808[];
  extern char DAT_002ba59c[];
  extern char DAT_002ba728[];
  void *out;
  void *thr;

  __asm__ volatile("movl %%esi, %0" : "=r"(out));
  if (out == 0) {
    display_assert(DAT_00282808, DAT_002ba59c, 0x1ea, 1);
    system_exit(-1);
  }
  thr = *(void **)0x4eaaa4;
  if (thr != 0) {
    error(2, DAT_002ba728);
    while (!thread_is_done(thr))
      ;
    thread_close(*(void **)0x4eaaa4);
    *(void **)0x4eaaa4 = 0;
  }
  *(int *)0x4eaa38 = profile_index;
  csmemcpy((void *)0x4eaa3c, out, 0x68);
  thread_new(0, (void *)0x1c2550, (int)0x4eaa38, (void **)0x4eaaa4);
}
/* playlist_profile_get_display_name (0x1c27f0) — readable C lift from XBE leaf. */
void playlist_profile_get_display_name(int profile_index, game_variant_t *variant)
{
  extern char DAT_00282808[];
  extern char DAT_002ba59c[];

  if (variant == 0) {
    display_assert(DAT_00282808, DAT_002ba59c, 0x131, true);
    system_exit(-1);
  }
  if (profile_index != -1) {
    game_engine_variant_cleanup(variant);
    playlist_profile_read(profile_index);
  }
}




/* saved_game_file_close (0x1c2890) - readable C lift. */
char saved_game_file_close(void *info, int packed)
{
  int slot, idx, kind;
  kind = packed & 0xf;
  slot = (packed >> 8) & 0xff;
  idx = (packed >> 16) & 0xfff;
  if (slot != 0) {
    display_assert((const char *)0x2ba8c0, (const char *)0x2ba8e8, 0x25b, true);
    system_exit(-1);
  }
  if (!info) {
    display_assert((const char *)0x2ba8b0, (const char *)0x2ba8e8, 0x25e, true);
    system_exit(-1);
  }
  if (kind < 0 || kind >= 2) {
    display_assert((const char *)0x2ba878, (const char *)0x2ba8e8, 0x25f, true);
    system_exit(-1);
  }
  if (slot < 0 || slot >= 9) {
    display_assert((const char *)0x2ba838, (const char *)0x2ba8e8, 0x260, true);
    system_exit(-1);
  }
  if (idx < 0 || idx >= 0x64) {
    display_assert((const char *)0x2ba7e8, (const char *)0x2ba8e8, 0x261, true);
    system_exit(-1);
  }
  if (file_close(info) && slot == 0)
    return 1;
  return 0;
}

/* saved_game_file_get_type (0x1c29a0) — readable C lift. */
int saved_game_file_get_type(int handle)
{
  return handle & 0xf;
}

/* saved_game_files_notify_memory_units_changed (0x1c29b0) — readable C lift. */
void saved_game_files_notify_memory_units_changed(void)
{
  *(unsigned char *)0x4eacc7 = 1;
}
/* saved_game_file_get_useable_untitled_profile_name (0x1c29c0) — readable C lift. */
void saved_game_file_get_useable_untitled_profile_name(wchar_t *out_name)
{
  int tag;
  char prefix[8];
  char path[0x100];
  int n;
  wchar_t *fmt;

  if (!out_name) {
    display_assert((const char *)0x2ba974, (const char *)0x2ba8e8, 0x2c1, 1);
    system_exit(-1);
  }
  out_name[0] = 0;
  tag = tag_loaded(0x75737472, (const char *)0x28a528);
  if (tag == -1) {
    error(2, (const char *)0x2ba918, (const char *)0x28a528);
    return;
  }
  csmemset(path, 0, 0x100);
  csmemset(prefix, 0, 8);
  wide_to_ascii((const wchar_t *)*(void **)0x32eb94, prefix, 8);
  for (n = 0; n < 0x3e7; n++) {
    fmt = (wchar_t *)FUN_0019d420(tag, 2);
    unicode_sprintf(out_name, 0x7f, fmt, n + 1);
    out_name[0x7f] = 0;
    if (FUN_001d2f22(prefix, out_name, 3, 0, path, 0x100) != 0)
      return;
  }
  error(2, (const char *)0x2ba940, 0x3e7);
  out_name[0] = 0;
}

/* saved_game_files_take_mutex (0x1c2af0) — readable C lift. */
void saved_game_files_take_mutex(void)
{
  take_mutex(*(int **)0x4eacbc, 0x36ee80);
}

/* saved_game_files_release_mutex (0x1c2b10) — readable C lift. */
void saved_game_files_release_mutex(void)
{
  release_mutex(*(int **)0x4eacbc);
}

/* saved_game_perform_file_system_checks (0x1c2b20) - readable C lift. */
int saved_game_perform_file_system_checks(void)
{
  char ascii[8];
  unsigned int avail[2];
  unsigned int total[2];
  unsigned int free_bytes[2];
  unsigned char find_data[0x340];
  char *path;
  int handle;
  unsigned int count;
  int __attribute__((stdcall)) (*const get_free)(char *, void *, void *, void *) =
      (int __attribute__((stdcall)) (*)(char *, void *, void *, void *))FUN_001d3739;
  int __attribute__((stdcall)) (*const find_first)(char *, void *) =
      (int __attribute__((stdcall)) (*)(char *, void *))FUN_001d3254;
  char __attribute__((stdcall)) (*const find_next)(int, void *) =
      (char __attribute__((stdcall)) (*)(int, void *))FUN_001d335b;
  int __attribute__((stdcall)) (*const find_close)(int) =
      (int __attribute__((stdcall)) (*)(int))FUN_001d33a2;

  path = wide_to_ascii((const wchar_t *)*(void **)0x32eb94, ascii, 8);
  if (get_free(path, avail, total, free_bytes)) {
    if (avail[1] == 0 && avail[0] < 0x2800000u)
      return 1;
  }

  path = wide_to_ascii((const wchar_t *)*(void **)0x32eb94, ascii, 8);
  handle = find_first(path, find_data);
  count = 1;
  if (handle == -1)
    return 0;
  while (count < 100u) {
    count++;
    if (find_next(handle, find_data) != 1)
      break;
  }
  if (!find_close(handle))
    error(2, (const char *)0x2ba984);
  if (count >= 100u)
    return 2;
  return 0;
}



/* saved_game_file_name_unique (0x1c2bf0) — readable C lift. */
char saved_game_file_name_unique(wchar_t *name)
{
  char tmp[8];
  char buf[0x100];
  char *prefix;

  if (name == 0 || name[0] == 0)
    return 0;
  prefix = wide_to_ascii((const wchar_t *)*(void **)0x32eb94, tmp, 8);
  if (FUN_001d2f22(prefix, name, 3, 0, buf, 0x100) != 0)
    return 1;
  return 0;
}

/* saved_game_file_remember_player1_last_used_profile_directory (0x1c2c50) — readable C lift. */
void saved_game_file_remember_player1_last_used_profile_directory(const char *path)
{
  char ref[0x10c];
  if (path == 0) {
    display_assert((const char *)0x2ba9d4, (const char *)0x2ba8e8, 0x41a, 1);
    system_exit(-1);
  }
  if (file_reference_create_from_path((file_ref_t *)ref, (const char *)0x2ba9c4, 0) == 0)
    goto fail;
  if (!FUN_0019a490((file_ref_t *)ref))
    goto fail;
  if (!file_open((file_ref_t *)ref, 2))
    goto fail;
  if (!file_write((file_ref_t *)ref, 0x100, (void *)path))
    error(2, (const char *)0x2ba9ac, (const char *)0x2ba9c4);
  file_close((file_ref_t *)ref);
  return;
fail:
  error(2, (const char *)0x2ba998, (const char *)0x2ba9c4);
}

/* saved_game_file_retrieve_player1_last_used_profile_directory (0x1c2d20) — readable C lift. */
char saved_game_file_retrieve_player1_last_used_profile_directory(char *out_name)
{
  file_ref_t ref;
  char ok;

  ok = 0;
  if (!out_name) {
    display_assert((const char *)0x2ba9d4, (const char *)0x2ba8e8, 0x434, true);
    system_exit(-1);
  }

  if (!file_reference_create_from_path(&ref, (const char *)0x2ba9c4, 0)) {
    error(2, (const char *)0x2ba998, (const char *)0x2ba9c4);
    out_name[0xff] = 0;
    return 0;
  }
  if (!file_open(&ref, 1)) {
    error(2, (const char *)0x2ba998, (const char *)0x2ba9c4);
    out_name[0xff] = 0;
    return 0;
  }
  ok = file_read(&ref, 0x100, out_name);
  if (!ok)
    error(2, (const char *)0x2ba9e4, (const char *)0x2ba9c4);
  file_close(&ref);
  out_name[0xff] = 0;
  return ok;
}

/* saved_game_file_remember_last_used_multiplayer_variant_directory (0x1c2e00) — readable C lift. */
void saved_game_file_remember_last_used_multiplayer_variant_directory(const char *path)
{
  char ref[0x10c];
  if (path == 0) {
    display_assert((const char *)0x2ba9d4, (const char *)0x2ba8e8, 0x44e, 1);
    system_exit(-1);
  }
  if (file_reference_create_from_path((file_ref_t *)ref, (const char *)0x2baa00, 0) == 0)
    goto fail;
  if (!FUN_0019a490((file_ref_t *)ref))
    goto fail;
  if (!file_open((file_ref_t *)ref, 2))
    goto fail;
  if (!file_write((file_ref_t *)ref, 0x100, (void *)path))
    error(2, (const char *)0x2ba9ac, (const char *)0x2baa00);
  file_close((file_ref_t *)ref);
  return;
fail:
  error(2, (const char *)0x2ba998, (const char *)0x2baa00);
}

/* saved_game_file_retrieve_last_used_multiplayer_variant_directory (0x1c2ed0) — readable C lift. */
char saved_game_file_retrieve_last_used_multiplayer_variant_directory(char *out_name)
{
  file_ref_t ref;
  char ok;

  ok = 0;
  if (!out_name) {
    display_assert((const char *)0x2ba9d4, (const char *)0x2ba8e8, 0x468, true);
    system_exit(-1);
  }

  if (!file_reference_create_from_path(&ref, (const char *)0x2baa00, 0)) {
    error(2, (const char *)0x2ba998, (const char *)0x2baa00);
    out_name[0xff] = 0;
    return 0;
  }
  if (!file_open(&ref, 1)) {
    error(2, (const char *)0x2ba998, (const char *)0x2baa00);
    out_name[0xff] = 0;
    return 0;
  }
  ok = file_read(&ref, 0x100, out_name);
  if (!ok)
    error(2, (const char *)0x2ba9e4, (const char *)0x2baa00);
  file_close(&ref);
  out_name[0xff] = 0;
  return ok;
}

/* saved_game_file_remember_last_used_multiplayer_map (0x1c2fb0) — readable C lift. */
void saved_game_file_remember_last_used_multiplayer_map(const char *path)
{
  char ref[0x10c];
  if (path == 0) {
    display_assert((const char *)0x274e68, (const char *)0x2ba8e8, 0x4b7, 1);
    system_exit(-1);
  }
  if (file_reference_create_from_path((file_ref_t *)ref, (const char *)0x2baa10, 0) == 0)
    goto fail;
  if (!FUN_0019a490((file_ref_t *)ref))
    goto fail;
  if (!file_open((file_ref_t *)ref, 2))
    goto fail;
  if (!file_write((file_ref_t *)ref, 0x100, (void *)path))
    error(2, (const char *)0x2ba9ac, (const char *)0x2baa10);
  file_close((file_ref_t *)ref);
  return;
fail:
  error(2, (const char *)0x2ba998, (const char *)0x2baa10);
}

/* saved_game_file_retrieve_last_used_multiplayer_map (0x1c3080) — readable C lift. */
char saved_game_file_retrieve_last_used_multiplayer_map(char *out_name)
{
  file_ref_t ref;
  char ok;

  ok = 0;
  if (!out_name) {
    display_assert((const char *)0x274e68, (const char *)0x2ba8e8, 0x4d1, true);
    system_exit(-1);
  }

  if (!file_reference_create_from_path(&ref, (const char *)0x2baa10, 0)) {
    error(2, (const char *)0x2ba998, (const char *)0x2baa10);
    out_name[0xff] = 0;
    return 0;
  }
  if (!file_open(&ref, 1)) {
    error(2, (const char *)0x2ba998, (const char *)0x2baa10);
    out_name[0xff] = 0;
    return 0;
  }
  ok = file_read(&ref, 0x100, out_name);
  if (!ok)
    error(2, (const char *)0x2ba9e4, (const char *)0x2baa10);
  file_close(&ref);
  out_name[0xff] = 0;
  return ok;
}

/* saved_game_file_generate_checksum (0x1c3160) — Capstone/readable tip lift.
 * Direct CALLs so Unicorn stubs can hook XCalculateSignature* (no fptrs).
 * Tip: stub_returns begin=-1 → error+return. */
void saved_game_file_generate_checksum(void *buffer, unsigned short size, void *out_sig)
{
  int handle;

  if (buffer == 0) {
    display_assert((const char *)0x267900, (const char *)0x2ba8e8, 0x4eb, 1);
    system_exit(-1);
  }
  handle = XCalculateSignatureBegin(0);
  if (handle == -1) {
    error(2, (const char *)0x2baa20);
    return;
  }
  if (FUN_001d42a9(handle, buffer, (unsigned int)size) != 0)
    error(2, (const char *)0x2baa64);
  if (FUN_001d42c3(handle, out_sig) != 0)
    error(2, (const char *)0x2baa44);
}


/* FUN_001c31f0 (0x1c31f0) — readable C lift from XBE leaf. */
char FUN_001c31f0(const char *path)
{
  unsigned char ref[0x10c];
  file_ref_t *created;

  created = file_reference_create_from_path((file_ref_t *)ref, path, true);
  if (created == 0) {
    return 0;
  }
  if (file_exists((file_ref_t *)ref)) {
    return 1;
  }
  if (FUN_0019a490((file_ref_t *)ref)) {
    return 1;
  }
  return 0;
}




/* FUN_001c3250 (0x1c3250) — readable C lift from XBE leaf. */
char FUN_001c3250(int16_t slot_index)
{
  unsigned path;
  int opened;
  extern char DAT_002ba8e8[];
  extern char DAT_002ba8c0[];
  extern char DAT_002baac8[];
  extern char DAT_002baa88[];

  if (slot_index != 0) {
    display_assert(DAT_002ba8c0, DAT_002ba8e8, 0x66b, 1);
    system_exit(-1);
  }
  if (*(char *)0x4eacc8 != 0) {
    display_assert(DAT_002baac8, DAT_002ba8e8, 0x66f, 1);
    system_exit(-1);
  }
  path = *(unsigned *)(0x32eb98 + 4 * (unsigned)(uint16_t)slot_index);
  opened = file_reference_create_from_path((file_ref_t *)0x4eabb0, (char *)path, 0);
  if (opened != 0) {
    if (FUN_0019a490((file_ref_t *)0x4eabb0)) {
      if (file_open((file_ref_t *)0x4eabb0, 2)) {
        *(uint16_t *)0x4eacc4 = 0;
        *(char *)0x4eacc8 = 1;
        return 1;
      }
    }
  }
  error(2, DAT_002baa88, (unsigned)(uint16_t)slot_index);
  *(uint16_t *)0x4eacc4 = 0xffff;
  return *(char *)0x4eacc8;
}



/* FUN_001c3320 (0x1c3320) — readable C lift from XBE leaf. */
char FUN_001c3320(int16_t expect_zero)
{
  extern char DAT_002ba8c0[];
  extern char DAT_002ba8e8[];
  extern char DAT_002bab34[];
  extern char DAT_002baafc[];

  if (expect_zero != 0) {
    display_assert(DAT_002ba8c0, DAT_002ba8e8, 0x685, true);
    system_exit(-1);
  }
  if (*(unsigned char *)0x4eacc8 == 0) {
    display_assert(DAT_002bab34, DAT_002ba8e8, 0x687, true);
    system_exit(-1);
  }
  if (!file_close((file_ref_t *)0x4eabb0)) {
    error(2, DAT_002baafc, (unsigned int)(uint16_t)expect_zero);
  }
  *(uint16_t *)0x4eacc4 = 0xffff;
  *(unsigned char *)0x4eacc8 = 0;
  return 1;
}




/* FUN_001c33b0 (0x1c33b0) — readable C lift from XBE leaf. */
char FUN_001c33b0(void *buffer)
{
  extern char DAT_002babe0[];
  extern char DAT_002ba8e8[];
  extern char DAT_002bab68[];
  short count;
  bool (*write3)(file_ref_t *, int, void *) =
      (bool (*)(file_ref_t *, int, void *))file_write;

  if (*(unsigned char *)0x4eacc8 == 0 || (count = *(short *)0x4eacc4) < 0) {
    display_assert(DAT_002babe0, DAT_002ba8e8, 0x741, true);
    system_exit(-1);
    count = *(short *)0x4eacc4;
  }
  if (count >= 0x64) {
    error(2, DAT_002bab68);
    return 0;
  }
  *(short *)((char *)buffer + 0x202) = count;
  *(short *)0x4eacc4 = (short)(count + 1);
  return (char)write3((file_ref_t *)0x4eabb0, 0x206, buffer);
}




/* FUN_001c3430 (0x1c3430) — readable C lift from XBE leaf. */
char FUN_001c3430(int16_t slot_index)
{
  unsigned path;
  int opened;
  char ok;
  unsigned size;
  extern char DAT_002ba8e8[];
  extern char DAT_002bacc8[];
  extern char DAT_002baac8[];
  extern char DAT_002bac8c[];
  extern char DAT_002bac54[];

  if (slot_index != 0) {
    display_assert(DAT_002bacc8, DAT_002ba8e8, 0x75b, 1);
    system_exit(-1);
  }
  if (*(char *)0x4eacc8 != 0) {
    display_assert(DAT_002baac8, DAT_002ba8e8, 0x75f, 1);
    system_exit(-1);
  }
  path = *(unsigned *)(0x32eb98 + 4 * (unsigned)(uint16_t)slot_index);
  opened = file_reference_create_from_path((file_ref_t *)0x4eabb0, (char *)path, 0);
  if (opened == 0) {
    error(2, DAT_002bac54, (unsigned)(uint16_t)slot_index);
    return 0;
  }
  ok = (char)file_open((file_ref_t *)0x4eabb0, 1);
  if (!ok) {
    error(2, DAT_002bac54, (unsigned)(uint16_t)slot_index);
    return 0;
  }
  size = (unsigned)file_get_eof((file_ref_t *)0x4eabb0);
  if ((size % 0x206u) != 0) {
    error(2, DAT_002bac8c, (unsigned)(uint16_t)slot_index);
  }
  return 1;
}



/* FUN_001c3500 (0x1c3500) — readable C lift from XBE leaf. */
char FUN_001c3500(int16_t slot_index)
{
  char ok;
  extern char DAT_002ba8e8[];
  extern char DAT_002bacc8[];
  extern char DAT_002baac8[];
  extern char DAT_002bad24[];
  extern char DAT_002bacf4[];

  if (slot_index != 0) {
    display_assert(DAT_002bacc8, DAT_002ba8e8, 0x77c, 1);
    system_exit(-1);
  }
  if (*(char *)0x4eacc8 != 0) {
    display_assert(DAT_002baac8, DAT_002ba8e8, 0x77e, 1);
    system_exit(-1);
  }
  if ((uint16_t)slot_index >= 9) {
    display_assert(DAT_002bad24, DAT_002ba8e8, 0x77f, 1);
    system_exit(-1);
  }
  ok = (char)file_close((file_ref_t *)0x4eabb0);
  if (!ok) {
    error(2, DAT_002bacf4, (unsigned)(uint16_t)slot_index);
  }
  return ok;
}



/* FUN_001c35a0 (0x1c35a0) — readable C lift from XBE leaf. */
bool FUN_001c35a0(void *buffer)
{
  extern char DAT_002baac8[];
  extern char DAT_002ba8e8[];
  extern char DAT_00265878[];

  if (*(unsigned char *)0x4eacc8 != 0) {
    display_assert(DAT_002baac8, DAT_002ba8e8, 0x793, true);
    system_exit(-1);
  }
  if (buffer == 0) {
    display_assert(DAT_00265878, DAT_002ba8e8, 0x794, true);
    system_exit(-1);
  }
  return file_read((file_ref_t *)0x4eabb0, 0x206, buffer);
}




/* FUN_001c3610 (0x1c3610) — readable C lift from XBE leaf. */
unsigned int FUN_001c3610(int16_t slot_index)
{
  unsigned path;
  file_ref_t *opened;
  unsigned size;
  extern char DAT_002ba8e8[];
  extern char DAT_002bacc8[];
  extern char DAT_002baac8[];
  extern char DAT_002bad24[];

  if (slot_index != 0) {
    display_assert(DAT_002bacc8, DAT_002ba8e8, 0x860, 1);
    system_exit(-1);
  }
  if (*(char *)0x4eacc8 != 0) {
    display_assert(DAT_002baac8, DAT_002ba8e8, 0x862, 1);
    system_exit(-1);
  }
  if ((uint16_t)slot_index >= 9) {
    display_assert(DAT_002bad24, DAT_002ba8e8, 0x863, 1);
    system_exit(-1);
  }
  path = *(unsigned *)(0x32eb98 + 4 * (unsigned)(uint16_t)slot_index);
  opened = file_reference_create_from_path((file_ref_t *)0x4eabb0, (char *)path, 0);
  if (opened == 0)
    return 0;
  if (!file_get_size((file_ref_t *)0x4eabb0, &size))
    return 0;
  return (unsigned)(((unsigned long long)size * 0xfd08e551ull) >> 41);
}


/* FUN_001c3710 (0x1c3710) — readable C lift. */
unsigned int FUN_001c3710(unsigned int a, unsigned int c, unsigned int d, unsigned char flag0, unsigned char flag1)
{
  unsigned int r;
  r = ((a & 0xfff) << 8) | (c & 0xff);
  r = (r << 8) | (d & 0xf);
  if (flag0 == 1)
    r |= 0x40000000u;
  if (flag1 == 1)
    r |= 0x80000000u;
  return r;
}

/* saved_game_file_find_profile_index_for_directory_path (0x1c38d0) — readable C lift. */
int saved_game_file_find_profile_index_for_directory_path(const char *path, int16_t expect_type)
{
  int result;
  int path_len;
  unsigned int count;
  int i;
  unsigned char record[0x206];

  result = -1;
  if (!path) {
    display_assert((const char *)0x2ba9d4, (const char *)0x2ba8e8, 0x486, 1);
    system_exit(-1);
  }
  path_len = csstrlen(path);
  if (!take_mutex(*(int **)0x4eacbc, 0x36ee80)) {
    error(2, (const char *)0x2bae64);
    return -1;
  }
  if (!take_mutex(*(int **)0x4eacc0, 0x36ee80)) {
    error(2, (const char *)0x2bae8c);
    release_mutex(*(int **)0x4eacbc);
    return -1;
  }

  count = FUN_001c3610(0);
  if (FUN_001c3430(0)) {
    for (i = 0; i < (int)count; i++) {
      if (!FUN_001c35a0(record))
        break;
      if (*(int16_t *)(record + 0x200) != expect_type)
        continue;
      if (__strnicmp(path, (const char *)record, (size_t)path_len) == 0) {
        result = (int)FUN_001c3710(
            (unsigned int)i, 0, (unsigned int)expect_type,
            record[0x204], record[0x205]);
        break;
      }
    }
    FUN_001c3500(0);
  }

  release_mutex(*(int **)0x4eacc0);
  release_mutex(*(int **)0x4eacbc);
  return result;
}

/* FUN_001c3a30 (0x1c3a30) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))saved_game_file_generate_checksum)();
  csmemcmp((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, 20);
  /* test eax, eax -> jne 0x1c3b89 */
  error(0, (char *)0x002bb000);
  error(0, (char *)0x002bafc4);
  file_close((void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> jne 0x1c3bd9 */
  error(0, (char *)0x002baf40);
  ((void(*)(void))FUN_001c33b0)();
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


/* FUN_001c3c40 (0x1c3c40) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))saved_game_file_generate_checksum)();
  csmemcmp((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, 20);
  /* test eax, eax -> jne 0x1c3d86 */
  error(0, (char *)0x002bb000);
  error(0, (char *)0x002bb188);
  file_close((void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> jne 0x1c3dd6 */
  error(0, (char *)0x002bb0f8);
  ((void(*)(void))FUN_001c33b0)();
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


/* FUN_001c3e40 (0x1c3e40) — readable C lift (restored pre-naked). */
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


/* FUN_001c4030 (0x1c4030) — readable C lift. */
char FUN_001c4030(int16_t slot_index, uint16_t record_index, void *buffer)
{
  char ok;
  unsigned path;
  unsigned eof;
  unsigned offset;

  ok = 0;
  if (slot_index != 0) {
    display_assert((const char *)0x2bacc8, (const char *)0x2ba8e8, 0x7e2, 1);
    system_exit(-1);
  }
  if (*(unsigned char *)0x4eacc8 != 0) {
    display_assert((const char *)0x2baac8, (const char *)0x2ba8e8, 0x7e4, 1);
    system_exit(-1);
  }
  if ((uint16_t)slot_index >= 9 || !buffer) {
    display_assert((const char *)0x2bb244, (const char *)0x2ba8e8, 0x7e5, 1);
    system_exit(-1);
  }
  if (!take_mutex(*(int **)0x4eacc0, 0x36ee80)) {
    error(2, (const char *)0x2bae8c);
    return 0;
  }

  path = *(unsigned *)(0x32eb98 + 4 * (unsigned)(uint16_t)slot_index);
  if (!file_reference_create_from_path((file_ref_t *)0x4eabb0, (char *)path, 0) ||
      !file_open((file_ref_t *)0x4eabb0, 2)) {
    error(2, (const char *)0x2bac54, (unsigned)(uint16_t)slot_index);
    release_mutex(*(int **)0x4eacc0);
    return 0;
  }

  eof = (unsigned)file_get_eof((file_ref_t *)0x4eabb0);
  offset = (unsigned)record_index * 0x206u;
  if ((eof % 0x206u) != 0)
    error(2, (const char *)0x2bac8c, (unsigned)(uint16_t)slot_index);

  if (offset + 0x206u > eof) {
    error(2, (const char *)0x2bb1cc, (unsigned)record_index,
          (unsigned)(uint16_t)slot_index);
  } else if (!file_set_position((file_ref_t *)0x4eabb0, (int)offset) ||
             !file_write((file_ref_t *)0x4eabb0, 0x206, buffer)) {
    ok = 0;
    error(2, (const char *)0x2bb284, (unsigned)record_index,
          (unsigned)(uint16_t)slot_index);
  } else {
    ok = 1;
  }

  if (!file_close((file_ref_t *)0x4eabb0)) {
    error(2, (const char *)0x2baafc, (unsigned)(uint16_t)slot_index);
    ok = 0;
  }
  release_mutex(*(int **)0x4eacc0);
  return ok;
}

/* FUN_001c4210 (0x1c4210) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))file_write)();
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


/* FUN_001c43f0 (0x1c43f0) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))file_get_size)();
  /* test (char)eax, (char)eax -> je 0x1c45c2 */
  /* cmp eax, edi -> jb 0x1c45c2 */
  file_open((void *)0x004eabb0, 0);
  /* test (char)eax, (char)eax -> je 0x1c45c2 */
  file_set_position((void *)0x004eabb0, 0);
  /* cmp (char)ebx, 1 -> jne 0x1c4584 */
  /* relift: cmp edi, dword ptr [ebp - 4] -> jae 0x1c4588 */
  file_read_from_position((void *)0x004eabb0, 0, 518, (void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x1c4571 */
  ((void(*)(void))file_write_to_position)();
  /* test (char)eax, (char)eax -> je 0x1c4571 */
  /* cmp edi, eax -> jb 0x1c4520 */
  error(0, (char *)0x002bb3e8);
  /* test (char)ebx, (char)ebx -> je 0x1c45a0 */
  ((void(*)(void))file_set_eof)();
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



/* saved_game_file_get_display_name (0x1c4600) — readable C lift. */
wchar_t *saved_game_file_get_display_name(int file_index)
{
  unsigned int slot;
  unsigned int idx;
  unsigned char record[0x208];
  char ok;
  slot = (unsigned int)((file_index >> 8) & 0xff);
  idx = (unsigned int)((file_index >> 16) & 0xfff);
  if (slot != 0) {
    display_assert((const char *)0x2ba8c0, (const char *)0x2ba8e8, 0x12b, 1);
    system_exit(-1);
  }
  *(uint16_t *)0x4eaab0 = 0;
  if ((int)slot < 0 || slot >= 9 || (int)idx < 0 || idx >= 100) {
    error(2, (const char *)0x2bb430);
    return (wchar_t *)0x4eaab0;
  }
  __asm__ volatile(
      "pushl %[buf]\n\t"
      "call FUN_001c3e40\n\t"
      "addl $4, %%esp\n\t"
      : "=a"(ok)
      : "a"(slot), "D"(idx), [buf] "r"(record)
      : "ecx", "edx", "memory", "cc");
  if (!ok)
    return (wchar_t *)0x4eaab0;
  ustrncpy((wchar_t *)0x4eaab0, (wchar_t *)(record + 0x100), 0x7f);
  *(uint16_t *)0x4eabae = 0;
  return (wchar_t *)0x4eaab0;
}



/* delete_enumerated_saved_game_file (0x1c46c0) — readable C lift. */
char delete_enumerated_saved_game_file(int packed)
{
  int slot;
  int idx;
  int kind;
  unsigned char record[0x208];
  char prefix[8];
  char ok;
  char *ascii;

  ok = 0;
  if (*(unsigned char *)0x4eacc7 != 0) {
    error(2, (const char *)0x2bb590);
    ui_widget_clear_last_error_index();
    return 0;
  }

  kind = packed & 0xf;
  slot = (packed >> 8) & 0xff;
  idx = (int)((unsigned)packed >> 16) & 0xfff;

  if (slot != 0) {
    display_assert((const char *)0x2ba8c0, (const char *)0x2ba8e8, 0x1ef, 1);
    system_exit(-1);
  }
  if (kind < 0 || kind >= 2 || slot < 0 || slot >= 9 || idx < 0 || idx >= 0x64) {
    error(2, (const char *)0x2bb450);
    ui_widget_clear_last_error_index();
    return 0;
  }

  __asm__ volatile(
      "pushl %[buf]\n\t"
      "call FUN_001c3e40\n\t"
      "addl $4, %%esp\n\t"
      : "=a"(ok)
      : "a"(slot), "D"(idx), [buf] "r"(record)
      : "ecx", "edx", "memory", "cc");
  if (!ok) {
    error(2, (const char *)0x2bb4a8);
    ui_widget_clear_last_error_index();
    return 0;
  }

  ok = (char)(slot == 0);
  if (!ok) {
    error(2, (const char *)0x2bb4f4, slot);
    ui_widget_clear_last_error_index();
    return 0;
  }

  if ((packed & 0x40000000) == 0) {
    csmemset(prefix, 0, 8);
    ascii = wide_to_ascii((const wchar_t *)*(void **)(0x32eb94 + 4 * slot), prefix, 8);
    if (FUN_001d3185(ascii, (wchar_t *)(record + 0x100))) {
      error(2, (const char *)0x2bb55c);
      ok = 0;
    }
  }

  {
    char del_ok;
    __asm__ volatile(
        "call FUN_001c43f0\n\t"
        : "=a"(del_ok)
        : "a"(slot), "c"(idx)
        : "edx", "memory", "cc");
    if (!del_ok) {
      error(2, (const char *)0x2bb534);
      ok = 0;
    }
  }

  if (slot != 0)
    error(2, (const char *)0x2bb514);

  ui_widget_clear_last_error_index();
  return ok;
}

/* FUN_001c4850 (0x1c4850) — readable C lift. */
char FUN_001c4850(file_ref_t *info, int packed)
{
  int slot;
  int idx;
  int kind;
  unsigned char record[0x208];
  char ok;

  kind = packed & 0xf;
  slot = (packed >> 8) & 0xff;
  idx = (packed >> 16) & 0xfff;

  if (slot != 0) {
    display_assert((const char *)0x2ba8c0, (const char *)0x2ba8e8, 0x241, 1);
    system_exit(-1);
  }
  if (!info) {
    display_assert((const char *)0x2ba8b0, (const char *)0x2ba8e8, 0x244, 1);
    system_exit(-1);
  }
  if (kind < 0 || kind >= 2) {
    display_assert((const char *)0x2ba878, (const char *)0x2ba8e8, 0x245, 1);
    system_exit(-1);
  }
  if (slot < 0 || slot >= 9) {
    display_assert((const char *)0x2ba838, (const char *)0x2ba8e8, 0x246, 1);
    system_exit(-1);
  }
  if (idx < 0 || idx >= 0x64) {
    display_assert((const char *)0x2ba7e8, (const char *)0x2ba8e8, 0x247, 1);
    system_exit(-1);
  }

  __asm__ volatile(
      "pushl %[buf]\n\t"
      "call FUN_001c3e40\n\t"
      "addl $4, %%esp\n\t"
      : "=a"(ok)
      : "a"(slot), "D"(idx), [buf] "r"(record)
      : "ecx", "edx", "memory", "cc");
  if (!ok)
    return 0;
  if (!file_reference_create_from_path(info, (const char *)record, 0))
    return 0;
  if (slot != 0)
    return 0;
  if (!file_open(info, 3))
    return 0;
  return 1;
}

