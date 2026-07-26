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

/* FUN_001c1e20 (0x1c1e20) — XBE naked draft (batch 251). */
#if defined(__clang__)
static void (*const b1c1e20_c1c5560)(void) = FUN_001c5560;
static void (*const b1c1e20_c1c4850)(void) = FUN_001c4850;
static game_variant_t * (*const b1c1e20_caa190)(game_variant_t *out) = game_engine_slayer_default;
static void * (*const b1c1e20_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b1c1e20_cab570)(game_variant_t *variant) = game_engine_variant_cleanup;
static wchar_t * (*const b1c1e20_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;
static void (*const b1c1e20_c1c3160)(void) = saved_game_file_generate_checksum;
static bool (*const b1c1e20_c19aa00)(file_ref_t *info, int offset) = file_set_position;
static void (*const b1c1e20_c19ac00)(void) = file_write;
static void (*const b1c1e20_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static char (*const b1c1e20_c1c46c0)(int param_1) = delete_enumerated_saved_game_file;
static void (*const b1c1e20_c1c2890)(void) = saved_game_file_close;

__attribute__((naked, noinline))
void FUN_001c1e20(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x3dc, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c1c5560]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .LFUN_001c1e20_3\n\t"
      "leal -0x374(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1c4850]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c1e20_4\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb $0, -0x200(%%ebp)\n\t"
      "movl $0x7f, %%ecx\n\t"
      "leal -0x1ff(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "stosw\n\t"
      ".byte 0xaa\n\t"
      "leal -0x3dc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[caa190]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl $0x1a, %%ecx\n\t"
      "leal -0x268(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      "pushl $0x68\n\t"
      "leal -0x268(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x200(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8e0b0]\n\t"
      "andb $0xfe, -0x19c(%%ebp)\n\t"
      "leal -0x200(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[cab570]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl $0xb\n\t"
      "pushl %%ecx\n\t"
      "leal -0x200(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19dc90]\n\t"
      "leal -0x198(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x200(%%ebp), %%ecx\n\t"
      "pushl $0x68\n\t"
      "pushl %%ecx\n\t"
      "movw $0, -0x1ea(%%ebp)\n\t"
      "call *%[c1c3160]\n\t"
      "leal -0x374(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c19aa00]\n\t"
      "addl $0x34, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LFUN_001c1e20_1\n\t"
      "leal -0x200(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x374(%%ebp), %%ecx\n\t"
      "pushl $0x200\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19ac00]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001c1e20_2\n\t"
      ".LFUN_001c1e20_1:\n\t"
      "pushl $0x2ba4a0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1c46c0]\n\t"
      "addl $0xc, %%esp\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      ".LFUN_001c1e20_2:\n\t"
      "leal -0x374(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1c2890]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c1e20_3:\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c1e20_4:\n\t"
      "pushl $0x2ba470\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1c46c0]\n\t"
      "addl $0xc, %%esp\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1c5560] "m"(b1c1e20_c1c5560), [c1c4850] "m"(b1c1e20_c1c4850), [caa190] "m"(b1c1e20_caa190), [c8e0b0] "m"(b1c1e20_c8e0b0), [cab570] "m"(b1c1e20_cab570), [c19dc90] "m"(b1c1e20_c19dc90), [c1c3160] "m"(b1c1e20_c1c3160), [c19aa00] "m"(b1c1e20_c19aa00), [c19ac00] "m"(b1c1e20_c19ac00), [c8f390] "m"(b1c1e20_c8f390), [c1c46c0] "m"(b1c1e20_c1c46c0), [c1c2890] "m"(b1c1e20_c1c2890)
      : "memory");
}
#else
#error "FUN_001c1e20: clang naked draft required"
#endif


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

/* playlist_profile_get (0x1c1fa0) — XBE naked draft (batch 251). */
#if defined(__clang__)
static void (*const b1c1fa0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c1fa0_exitfn)(int) = system_exit;
static file_ref_t * (*const b1c1fa0_c1999f0)(file_ref_t *info, const char *directory, bool a4) = file_reference_create_from_path;
static bool (*const b1c1fa0_c19a7a0)(file_ref_t *info, int flags) = file_open;
static bool (*const b1c1fa0_c19ab50)(file_ref_t *info, int size, void *buffer) = file_read;
static void (*const b1c1fa0_c1c3160)(void) = saved_game_file_generate_checksum;
static int (*const b1c1fa0_c8da40)(const void *a, const void *b, int size) = csmemcmp;
static void * (*const b1c1fa0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static bool (*const b1c1fa0_c19a930)(file_ref_t *info) = file_close;
static void (*const b1c1fa0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void playlist_profile_get(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x320, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "je .Lplaylist_profile_get_1\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lplaylist_profile_get_2\n\t"
      ".Lplaylist_profile_get_1:\n\t"
      "pushl $1\n\t"
      "pushl $0xf3\n\t"
      "pushl $0x2ba59c\n\t"
      "pushl $0x2ba584\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplaylist_profile_get_2:\n\t"
      "pushl $0\n\t"
      "leal -0x120(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lplaylist_profile_get_6\n\t"
      "leal -0x120(%%ebp), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplaylist_profile_get_6\n\t"
      "leal -0x320(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x120(%%ebp), %%eax\n\t"
      "pushl $0x200\n\t"
      "pushl %%eax\n\t"
      "call *%[c19ab50]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplaylist_profile_get_4\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x320(%%ebp), %%edx\n\t"
      "pushl $0x68\n\t"
      "pushl %%edx\n\t"
      "call *%[c1c3160]\n\t"
      "pushl $0x14\n\t"
      "leal -0x2b8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8da40]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lplaylist_profile_get_3\n\t"
      "pushl $0x68\n\t"
      "leal -0x320(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c8e0b0]\n\t"
      "leal -0x120(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "movb $1, %%bl\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplaylist_profile_get_3:\n\t"
      "pushl $0x2ba558\n\t"
      "jmp .Lplaylist_profile_get_5\n\t"
      ".Lplaylist_profile_get_4:\n\t"
      "pushl $0x2ba538\n\t"
      ".Lplaylist_profile_get_5:\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "leal -0x120(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplaylist_profile_get_6:\n\t"
      "pushl $0x2ba510\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c1fa0_assert), [exitfn] "m"(b1c1fa0_exitfn), [c1999f0] "m"(b1c1fa0_c1999f0), [c19a7a0] "m"(b1c1fa0_c19a7a0), [c19ab50] "m"(b1c1fa0_c19ab50), [c1c3160] "m"(b1c1fa0_c1c3160), [c8da40] "m"(b1c1fa0_c8da40), [c8e0b0] "m"(b1c1fa0_c8e0b0), [c19a930] "m"(b1c1fa0_c19a930), [c8f390] "m"(b1c1fa0_c8f390)
      : "memory");
}
#else
#error "playlist_profile_get: clang naked draft required"
#endif


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

/* playlist_profile_create_default_profiles_on_disk (0x1c22e0) — XBE naked draft (batch 244). */
#if defined(__clang__)
static void (*const b1c22e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c22e0_exitfn)(int) = system_exit;
static void (*const b1c22e0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static bool (*const b1c22e0_c81720)(void *thread_reference) = thread_is_done;
static void (*const b1c22e0_c81770)(void *thread_reference) = thread_close;
static void (*const b1c22e0_c1c2af0)(void) = saved_game_files_take_mutex;
static void (*const b1c22e0_c1c4850)(void) = FUN_001c4850;
static bool (*const b1c22e0_c19ab50)(file_ref_t *info, int size, void *buffer) = file_read;
static void (*const b1c22e0_c1c3160)(void) = saved_game_file_generate_checksum;
static int (*const b1c22e0_c8da40)(const void *a, const void *b, int size) = csmemcmp;
static void * (*const b1c22e0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b1c22e0_c1c2890)(void) = saved_game_file_close;
static void (*const b1c22e0_c1c2b10)(void) = saved_game_files_release_mutex;
static game_variant_t * (*const b1c22e0_caa190)(game_variant_t *out) = game_engine_slayer_default;
static void (*const b1c22e0_c1c4600)(void) = saved_game_file_get_display_name;
static wchar_t * (*const b1c22e0_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;

__attribute__((naked, noinline))
void playlist_profile_create_default_profiles_on_disk(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x3f4, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jne .Lplaylist_profile_create_default_profiles_on_disk_1\n\t"
      "pushl $1\n\t"
      "pushl $0x18c\n\t"
      "pushl $0x2ba59c\n\t"
      "pushl $0x282808\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplaylist_profile_create_default_profiles_on_disk_1:\n\t"
      "movl 0x4eaaa4, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lplaylist_profile_create_default_profiles_on_disk_3\n\t"
      "pushl $0x2ba728\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lplaylist_profile_create_default_profiles_on_disk_2:\n\t"
      "movl 0x4eaaa4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c81720]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplaylist_profile_create_default_profiles_on_disk_2\n\t"
      "movl 0x4eaaa4, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c81770]\n\t"
      "addl $4, %%esp\n\t"
      "movl $0, 0x4eaaa4\n\t"
      ".Lplaylist_profile_create_default_profiles_on_disk_3:\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jns .Lplaylist_profile_create_default_profiles_on_disk_8\n\t"
      "call *%[c1c2af0]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplaylist_profile_create_default_profiles_on_disk_7\n\t"
      "leal -0x1f4(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c1c4850]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplaylist_profile_create_default_profiles_on_disk_6\n\t"
      "leal -0x3f4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1f4(%%ebp), %%ecx\n\t"
      "pushl $0x200\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19ab50]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplaylist_profile_create_default_profiles_on_disk_5\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x3f4(%%ebp), %%eax\n\t"
      "pushl $0x68\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c3160]\n\t"
      "pushl $0x14\n\t"
      "leal -0x38c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8da40]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lplaylist_profile_create_default_profiles_on_disk_4\n\t"
      "pushl $0x68\n\t"
      "leal -0x3f4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "leal -0x1f4(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "call *%[c1c2890]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[c1c2b10]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplaylist_profile_create_default_profiles_on_disk_4:\n\t"
      "leal -0xe8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[caa190]\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl $0x2ba6d8\n\t"
      "movl $0x1a, %%ecx\n\t"
      "leal -0x80(%%ebp), %%edi\n\t"
      "pushl $2\n\t"
      "rep movsl\n\t"
      "call *%[c8f390]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0xb\n\t"
      "xorl %%esi, %%esi\n\t"
      "pushl %%edx\n\t"
      "movw %%si, -0x1c(%%ebp)\n\t"
      "call *%[c1c4600]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "leal -0x80(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19dc90]\n\t"
      "pushl $0x68\n\t"
      "leal -0x80(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movw %%si, -0x6a(%%ebp)\n\t"
      "call *%[c8e0b0]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "addl $0x18, %%esp\n\t"
      "leal -0x1f4(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "call *%[c1c2890]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[c1c2b10]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplaylist_profile_create_default_profiles_on_disk_5:\n\t"
      "pushl $0x2ba6a8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "leal -0x1f4(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c1c2890]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[c1c2b10]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplaylist_profile_create_default_profiles_on_disk_6:\n\t"
      "pushl $0x2ba510\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[c1c2b10]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplaylist_profile_create_default_profiles_on_disk_7:\n\t"
      "pushl $0x2ba030\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplaylist_profile_create_default_profiles_on_disk_8:\n\t"
      "leal -0xe8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[caa190]\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl $0x2ba6d8\n\t"
      "movl $0x1a, %%ecx\n\t"
      "leal -0x80(%%ebp), %%edi\n\t"
      "pushl $2\n\t"
      "rep movsl\n\t"
      "call *%[c8f390]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0xb\n\t"
      "xorl %%esi, %%esi\n\t"
      "pushl %%ecx\n\t"
      "movw %%si, -0x1c(%%ebp)\n\t"
      "call *%[c1c4600]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "leal -0x80(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19dc90]\n\t"
      "pushl $0x68\n\t"
      "leal -0x80(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "movw %%si, -0x6a(%%ebp)\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c22e0_assert), [exitfn] "m"(b1c22e0_exitfn), [c8f390] "m"(b1c22e0_c8f390), [c81720] "m"(b1c22e0_c81720), [c81770] "m"(b1c22e0_c81770), [c1c2af0] "m"(b1c22e0_c1c2af0), [c1c4850] "m"(b1c22e0_c1c4850), [c19ab50] "m"(b1c22e0_c19ab50), [c1c3160] "m"(b1c22e0_c1c3160), [c8da40] "m"(b1c22e0_c8da40), [c8e0b0] "m"(b1c22e0_c8e0b0), [c1c2890] "m"(b1c22e0_c1c2890), [c1c2b10] "m"(b1c22e0_c1c2b10), [caa190] "m"(b1c22e0_caa190), [c1c4600] "m"(b1c22e0_c1c4600), [c19dc90] "m"(b1c22e0_c19dc90)
      : "memory");
}
#else
#error "playlist_profile_create_default_profiles_on_disk: clang naked draft required"
#endif


/* playlist_profile_write (0x1c2550) — XBE naked draft (batch 249). */
#if defined(__clang__)
static void (*const b1c2550_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c2550_exitfn)(int) = system_exit;
static void (*const b1c2550_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b1c2550_c1c2af0)(void) = saved_game_files_take_mutex;
static void (*const b1c2550_c1c4850)(void) = FUN_001c4850;
static void * (*const b1c2550_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b1c2550_c1c3160)(void) = saved_game_file_generate_checksum;
static bool (*const b1c2550_c19aa00)(file_ref_t *info, int offset) = file_set_position;
static void (*const b1c2550_c19ac00)(void) = file_write;
static void (*const b1c2550_c1c2890)(void) = saved_game_file_close;
static void (*const b1c2550_c1c4990)(void) = FUN_001c4990;
static char (*const b1c2550_c1c46c0)(int param_1) = delete_enumerated_saved_game_file;
static void (*const b1c2550_c1c2b10)(void) = saved_game_files_release_mutex;

__attribute__((naked, noinline))
void playlist_profile_write(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30c, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lplaylist_profile_write_1\n\t"
      "pushl $1\n\t"
      "pushl $0x202\n\t"
      "pushl $0x2ba59c\n\t"
      "pushl $0x266c9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplaylist_profile_write_1:\n\t"
      "pushl $0x2ba7ac\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[c1c2af0]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplaylist_profile_write_7\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl (%%esi), %%edi\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "addl $4, %%esi\n\t"
      "call *%[c1c4850]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplaylist_profile_write_6\n\t"
      "pushl $0x68\n\t"
      "leal -0x30c(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8e0b0]\n\t"
      "leal -0x2a4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x30c(%%ebp), %%eax\n\t"
      "pushl $0x68\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c3160]\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19aa00]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplaylist_profile_write_2\n\t"
      "leal -0x30c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl $0x200\n\t"
      "pushl %%eax\n\t"
      "call *%[c19ac00]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lplaylist_profile_write_3\n\t"
      ".Lplaylist_profile_write_2:\n\t"
      "pushl $0x2ba780\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movb $1, %%bl\n\t"
      ".Lplaylist_profile_write_3:\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c2890]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplaylist_profile_write_4\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1c4990]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lplaylist_profile_write_4\n\t"
      "pushl $0x2ba14c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lplaylist_profile_write_4:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lplaylist_profile_write_5\n\t"
      "pushl %%edi\n\t"
      "call *%[c1c46c0]\n\t"
      "addl $4, %%esp\n\t"
      ".Lplaylist_profile_write_5:\n\t"
      "call *%[c1c2b10]\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "jmp .Lplaylist_profile_write_8\n\t"
      ".Lplaylist_profile_write_6:\n\t"
      "pushl $0x2ba510\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[c1c2b10]\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "jmp .Lplaylist_profile_write_8\n\t"
      ".Lplaylist_profile_write_7:\n\t"
      "pushl $0x2ba030\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lplaylist_profile_write_8:\n\t"
      "pushl $0x2ba764\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c2550_assert), [exitfn] "m"(b1c2550_exitfn), [c8f390] "m"(b1c2550_c8f390), [c1c2af0] "m"(b1c2550_c1c2af0), [c1c4850] "m"(b1c2550_c1c4850), [c8e0b0] "m"(b1c2550_c8e0b0), [c1c3160] "m"(b1c2550_c1c3160), [c19aa00] "m"(b1c2550_c19aa00), [c19ac00] "m"(b1c2550_c19ac00), [c1c2890] "m"(b1c2550_c1c2890), [c1c4990] "m"(b1c2550_c1c4990), [c1c46c0] "m"(b1c2550_c1c46c0), [c1c2b10] "m"(b1c2550_c1c2b10)
      : "memory");
}
#else
#error "playlist_profile_write: clang naked draft required"
#endif


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

/* saved_game_file_close (0x1c2890) — XBE naked draft (batch 252). */
#if defined(__clang__)
static void (*const b1c2890_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c2890_exitfn)(int) = system_exit;
static bool (*const b1c2890_c19a930)(file_ref_t *info) = file_close;

__attribute__((naked, noinline))
void saved_game_file_close(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl %%edi\n\t"
      "movzbl %%ah, %%edi\n\t"
      "sarl $0x10, %%eax\n\t"
      "andl $0xfff, %%eax\n\t"
      "andl $0xf, %%esi\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "je .Lsaved_game_file_close_1\n\t"
      "pushl $1\n\t"
      "pushl $0x25b\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba8c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsaved_game_file_close_1:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lsaved_game_file_close_2\n\t"
      "pushl $1\n\t"
      "pushl $0x25e\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba8b0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsaved_game_file_close_2:\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .Lsaved_game_file_close_3\n\t"
      "cmpl $2, %%esi\n\t"
      "jl .Lsaved_game_file_close_4\n\t"
      ".Lsaved_game_file_close_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x25f\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba878\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsaved_game_file_close_4:\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .Lsaved_game_file_close_5\n\t"
      "cmpl $9, %%edi\n\t"
      "jl .Lsaved_game_file_close_6\n\t"
      ".Lsaved_game_file_close_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x260\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba838\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsaved_game_file_close_6:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jl .Lsaved_game_file_close_7\n\t"
      "cmpl $0x64, %%ebx\n\t"
      "jl .Lsaved_game_file_close_8\n\t"
      ".Lsaved_game_file_close_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x261\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba7e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsaved_game_file_close_8:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsaved_game_file_close_9\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lsaved_game_file_close_9\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsaved_game_file_close_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c2890_assert), [exitfn] "m"(b1c2890_exitfn), [c19a930] "m"(b1c2890_c19a930)
      : "memory");
}
#else
#error "saved_game_file_close: clang naked draft required"
#endif


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

/* 0x1c2bf0 — return non-zero if current profile name is unique. */
char saved_game_file_name_unique(void)
{
  wchar_t *name = *(wchar_t **)0x46cf08;
  char ascii[256];

  if (name == 0 || name[0] == 0)
    return 0;
  wide_to_ascii(name, ascii, 255);
  FUN_001d2f22();
  return 1;
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

/* saved_game_file_find_profile_index_for_directory_path (0x1c38d0) — XBE naked draft (batch 249). */
#if defined(__clang__)
static void (*const b1c38d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c38d0_exitfn)(int) = system_exit;
static int (*const b1c38d0_c8df60)(const char *s1) = csstrlen;
static bool (*const b1c38d0_c81870)(int *mutex_reference, int timeout_ms) = take_mutex;
static void (*const b1c38d0_c1c3610)(void) = FUN_001c3610;
static void (*const b1c38d0_c1c3430)(void) = FUN_001c3430;
static void (*const b1c38d0_c1c35a0)(void) = FUN_001c35a0;
static int (*const b1c38d0_c1e6596)(const char *a, const char *b, size_t n) = __strnicmp;
static void (*const b1c38d0_c1c3710)(void) = FUN_001c3710;
static void (*const b1c38d0_c1c3500)(void) = FUN_001c3500;
static void (*const b1c38d0_c818d0)(int *mutex_reference) = release_mutex;
static void (*const b1c38d0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void saved_game_file_find_profile_index_for_directory_path(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x214, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "jne .Lsaved_game_file_find_profile_index_for_directory_path_1\n\t"
      "pushl $1\n\t"
      "pushl $0x486\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba9d4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsaved_game_file_find_profile_index_for_directory_path_1:\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x4eacbc, %%eax\n\t"
      "pushl $0x36ee80\n\t"
      "pushl %%eax\n\t"
      "call *%[c81870]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsaved_game_file_find_profile_index_for_directory_path_8\n\t"
      "movl 0x4eacc0, %%ecx\n\t"
      "pushl $0x36ee80\n\t"
      "pushl %%ecx\n\t"
      "call *%[c81870]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsaved_game_file_find_profile_index_for_directory_path_7\n\t"
      "pushl %%ebx\n\t"
      "xorl %%esi, %%esi\n\t"
      "call *%[c1c3610]\n\t"
      "movl %%eax, %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "call *%[c1c3430]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsaved_game_file_find_profile_index_for_directory_path_6\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .Lsaved_game_file_find_profile_index_for_directory_path_5\n\t"
      ".Lsaved_game_file_find_profile_index_for_directory_path_2:\n\t"
      "leal -0x214(%%ebp), %%esi\n\t"
      "call *%[c1c35a0]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsaved_game_file_find_profile_index_for_directory_path_5\n\t"
      "movw 0xc(%%ebp), %%si\n\t"
      "cmpw %%si, -0x14(%%ebp)\n\t"
      "jne .Lsaved_game_file_find_profile_index_for_directory_path_3\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x214(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1e6596]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsaved_game_file_find_profile_index_for_directory_path_4\n\t"
      ".Lsaved_game_file_find_profile_index_for_directory_path_3:\n\t"
      "incl %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jl .Lsaved_game_file_find_profile_index_for_directory_path_2\n\t"
      "jmp .Lsaved_game_file_find_profile_index_for_directory_path_5\n\t"
      ".Lsaved_game_file_find_profile_index_for_directory_path_4:\n\t"
      "movl -0xf(%%ebp), %%edx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movswl %%si, %%edx\n\t"
      "movl %%edi, %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1c3710]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".Lsaved_game_file_find_profile_index_for_directory_path_5:\n\t"
      "xorl %%esi, %%esi\n\t"
      "call *%[c1c3500]\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      ".Lsaved_game_file_find_profile_index_for_directory_path_6:\n\t"
      "movl 0x4eacc0, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c818d0]\n\t"
      "movl 0x4eacbc, %%edx\n\t"
      "addl $4, %%esp\n\t"
      "popl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[c818d0]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsaved_game_file_find_profile_index_for_directory_path_7:\n\t"
      "pushl $0x2bae8c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movl 0x4eacbc, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%edx\n\t"
      "call *%[c818d0]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsaved_game_file_find_profile_index_for_directory_path_8:\n\t"
      "pushl $0x2bae64\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c38d0_assert), [exitfn] "m"(b1c38d0_exitfn), [c8df60] "m"(b1c38d0_c8df60), [c81870] "m"(b1c38d0_c81870), [c1c3610] "m"(b1c38d0_c1c3610), [c1c3430] "m"(b1c38d0_c1c3430), [c1c35a0] "m"(b1c38d0_c1c35a0), [c1e6596] "m"(b1c38d0_c1e6596), [c1c3710] "m"(b1c38d0_c1c3710), [c1c3500] "m"(b1c38d0_c1c3500), [c818d0] "m"(b1c38d0_c818d0), [c8f390] "m"(b1c38d0_c8f390)
      : "memory");
}
#else
#error "saved_game_file_find_profile_index_for_directory_path: clang naked draft required"
#endif


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

/* FUN_001c3c40 (0x1c3c40) — XBE naked draft (batch 245). */
#if defined(__clang__)
static int (*const b1c3c40_c1b9930)(int group_tag, const char *name, ...) = tag_loaded;
static int (*const b1c3c40_c19d420)(int param_1, int param_2) = FUN_0019d420;
static int (*const b1c3c40_c1d9179)(char *str, size_t size, const char *format, ...) = snprintf;
static file_ref_t * (*const b1c3c40_c1999f0)(file_ref_t *info, const char *directory, bool a4) = file_reference_create_from_path;
static bool (*const b1c3c40_c19a640)(file_ref_t *info) = file_exists;
static void * (*const b1c3c40_c8de70)(char *destination, const char *source, size_t size) = csstrncpy;
static wchar_t * (*const b1c3c40_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;
static bool (*const b1c3c40_c19a7a0)(file_ref_t *info, int flags) = file_open;
static bool (*const b1c3c40_c19ab50)(file_ref_t *info, int size, void *buffer) = file_read;
static void (*const b1c3c40_c1c3160)(void) = saved_game_file_generate_checksum;
static int (*const b1c3c40_c8da40)(const void *a, const void *b, int size) = csmemcmp;
static void (*const b1c3c40_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static bool (*const b1c3c40_c19a930)(file_ref_t *info) = file_close;
static void (*const b1c3c40_c1c33b0)(void) = FUN_001c33b0;

__attribute__((naked, noinline))
void FUN_001c3c40(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x62c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x2898d0\n\t"
      "pushl $0x75737472\n\t"
      "call *%[c1b9930]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "je .LFUN_001c3c40_10\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_001c3c40_1:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c19d420]\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl %%bx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2ba2d8\n\t"
      "leal -0x42c(%%ebp), %%ecx\n\t"
      "pushl $0xff\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9179]\n\t"
      "pushl $0\n\t"
      "leal -0x42c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x32c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0x24, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c3c40_8\n\t"
      "leal -0x32c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19a640]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c3c40_8\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb $0, -0x220(%%ebp)\n\t"
      "movl $0x81, %%ecx\n\t"
      "leal -0x21f(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "pushl $0xff\n\t"
      "leal -0x42c(%%ebp), %%edx\n\t"
      ".byte 0xaa\n\t"
      "pushl %%edx\n\t"
      "leal -0x220(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8de70]\n\t"
      "pushl $0x7f\n\t"
      "leal -0x120(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "movb $0, -0x121(%%ebp)\n\t"
      "call *%[c19dc90]\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal -0x32c(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "movw %%ax, -0x22(%%ebp)\n\t"
      "movw %%ax, -0x20(%%ebp)\n\t"
      "movb $1, -0x1c(%%ebp)\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c3c40_5\n\t"
      "leal -0x62c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x32c(%%ebp), %%ecx\n\t"
      "pushl $0x200\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19ab50]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c3c40_3\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x62c(%%ebp), %%eax\n\t"
      "pushl $0x30\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c3160]\n\t"
      "pushl $0x14\n\t"
      "leal -0x5fc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8da40]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001c3c40_2\n\t"
      "movb $1, -0x1b(%%ebp)\n\t"
      "jmp .LFUN_001c3c40_4\n\t"
      ".LFUN_001c3c40_2:\n\t"
      "leal -0x220(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2bb000\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_001c3c40_4\n\t"
      ".LFUN_001c3c40_3:\n\t"
      "pushl $0x2bb188\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c3c40_4:\n\t"
      "leal -0x32c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001c3c40_7\n\t"
      "pushl $0x2bb140\n\t"
      "jmp .LFUN_001c3c40_6\n\t"
      ".LFUN_001c3c40_5:\n\t"
      "pushl $0x2bb0f8\n\t"
      ".LFUN_001c3c40_6:\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c3c40_7:\n\t"
      "leal -0x220(%%ebp), %%esi\n\t"
      "call *%[c1c33b0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c3c40_9\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      ".LFUN_001c3c40_8:\n\t"
      "incl %%ebx\n\t"
      "cmpw $2, %%bx\n\t"
      "jl .LFUN_001c3c40_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%bx, %%ax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c3c40_9:\n\t"
      "leal -0x42c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x2bb0bc\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%bx, %%ax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c3c40_10:\n\t"
      "pushl $0x2bb058\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%bx, %%ax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1b9930] "m"(b1c3c40_c1b9930), [c19d420] "m"(b1c3c40_c19d420), [c1d9179] "m"(b1c3c40_c1d9179), [c1999f0] "m"(b1c3c40_c1999f0), [c19a640] "m"(b1c3c40_c19a640), [c8de70] "m"(b1c3c40_c8de70), [c19dc90] "m"(b1c3c40_c19dc90), [c19a7a0] "m"(b1c3c40_c19a7a0), [c19ab50] "m"(b1c3c40_c19ab50), [c1c3160] "m"(b1c3c40_c1c3160), [c8da40] "m"(b1c3c40_c8da40), [c8f390] "m"(b1c3c40_c8f390), [c19a930] "m"(b1c3c40_c19a930), [c1c33b0] "m"(b1c3c40_c1c33b0)
      : "memory");
}
#else
#error "FUN_001c3c40: clang naked draft required"
#endif


/* FUN_001c3e40 (0x1c3e40) — XBE naked draft (batch 247). */
#if defined(__clang__)
static void (*const b1c3e40_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c3e40_exitfn)(int) = system_exit;
static bool (*const b1c3e40_c81870)(int *mutex_reference, int timeout_ms) = take_mutex;
static file_ref_t * (*const b1c3e40_c1999f0)(file_ref_t *info, const char *directory, bool a4) = file_reference_create_from_path;
static bool (*const b1c3e40_c19a7a0)(file_ref_t *info, int flags) = file_open;
static int (*const b1c3e40_c19aa70)(file_ref_t *info) = file_get_eof;
static void (*const b1c3e40_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static bool (*const b1c3e40_c19aa00)(file_ref_t *info, int offset) = file_set_position;
static bool (*const b1c3e40_c19ab50)(file_ref_t *info, int size, void *buffer) = file_read;
static bool (*const b1c3e40_c19a930)(file_ref_t *info) = file_close;
static void (*const b1c3e40_c818d0)(int *mutex_reference) = release_mutex;

__attribute__((naked, noinline))
void FUN_001c3e40(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movw %%ax, %%si\n\t"
      "xorb %%bl, %%bl\n\t"
      "testw %%si, %%si\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "je .LFUN_001c3e40_1\n\t"
      "pushl $1\n\t"
      "pushl $0x7a7\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2bacc8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c3e40_1:\n\t"
      "movb 0x4eacc8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c3e40_2\n\t"
      "pushl $1\n\t"
      "pushl $0x7a9\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2baac8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c3e40_2:\n\t"
      "cmpw $9, %%si\n\t"
      "jae .LFUN_001c3e40_3\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001c3e40_4\n\t"
      ".LFUN_001c3e40_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x7aa\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2bb244\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c3e40_4:\n\t"
      "movl 0x4eacc0, %%eax\n\t"
      "pushl $0x36ee80\n\t"
      "pushl %%eax\n\t"
      "call *%[c81870]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c3e40_13\n\t"
      "movzwl %%si, %%esi\n\t"
      "movl 0x32eb98(,%%esi,4), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x4eabb0\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c3e40_10\n\t"
      "pushl $1\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c3e40_10\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19aa70]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x206, %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "divl %%ecx\n\t"
      "movzwl %%di, %%edi\n\t"
      "movl %%edi, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "imull $0x206, %%esi, %%esi\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LFUN_001c3e40_5\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x2bac8c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001c3e40_5:\n\t"
      "leal 0x206(%%esi), %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "ja .LFUN_001c3e40_7\n\t"
      "pushl %%esi\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19aa00]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c3e40_6\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x206\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19ab50]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c3e40_6\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_001c3e40_9\n\t"
      ".LFUN_001c3e40_6:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "pushl $0x2bb208\n\t"
      "jmp .LFUN_001c3e40_8\n\t"
      ".LFUN_001c3e40_7:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $0x2bb1cc\n\t"
      ".LFUN_001c3e40_8:\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_001c3e40_9:\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001c3e40_12\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2baafc\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jmp .LFUN_001c3e40_11\n\t"
      ".LFUN_001c3e40_10:\n\t"
      "pushl %%esi\n\t"
      "pushl $0x2bac54\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      ".LFUN_001c3e40_11:\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001c3e40_12:\n\t"
      "movl 0x4eacc0, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c818d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c3e40_13:\n\t"
      "pushl $0x2bae8c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c3e40_assert), [exitfn] "m"(b1c3e40_exitfn), [c81870] "m"(b1c3e40_c81870), [c1999f0] "m"(b1c3e40_c1999f0), [c19a7a0] "m"(b1c3e40_c19a7a0), [c19aa70] "m"(b1c3e40_c19aa70), [c8f390] "m"(b1c3e40_c8f390), [c19aa00] "m"(b1c3e40_c19aa00), [c19ab50] "m"(b1c3e40_c19ab50), [c19a930] "m"(b1c3e40_c19a930), [c818d0] "m"(b1c3e40_c818d0)
      : "memory");
}
#else
#error "FUN_001c3e40: clang naked draft required"
#endif


/* FUN_001c4030 (0x1c4030) — XBE naked draft (batch 247). */
#if defined(__clang__)
static void (*const b1c4030_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c4030_exitfn)(int) = system_exit;
static bool (*const b1c4030_c81870)(int *mutex_reference, int timeout_ms) = take_mutex;
static file_ref_t * (*const b1c4030_c1999f0)(file_ref_t *info, const char *directory, bool a4) = file_reference_create_from_path;
static bool (*const b1c4030_c19a7a0)(file_ref_t *info, int flags) = file_open;
static int (*const b1c4030_c19aa70)(file_ref_t *info) = file_get_eof;
static void (*const b1c4030_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static bool (*const b1c4030_c19aa00)(file_ref_t *info, int offset) = file_set_position;
static void (*const b1c4030_c19ac00)(void) = file_write;
static bool (*const b1c4030_c19a930)(file_ref_t *info) = file_close;
static void (*const b1c4030_c818d0)(int *mutex_reference) = release_mutex;

__attribute__((naked, noinline))
void FUN_001c4030(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movw %%ax, %%si\n\t"
      "xorb %%bl, %%bl\n\t"
      "testw %%si, %%si\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "je .LFUN_001c4030_1\n\t"
      "pushl $1\n\t"
      "pushl $0x7e2\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2bacc8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c4030_1:\n\t"
      "movb 0x4eacc8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c4030_2\n\t"
      "pushl $1\n\t"
      "pushl $0x7e4\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2baac8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c4030_2:\n\t"
      "cmpw $9, %%si\n\t"
      "jae .LFUN_001c4030_3\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001c4030_4\n\t"
      ".LFUN_001c4030_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x7e5\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2bb244\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c4030_4:\n\t"
      "movl 0x4eacc0, %%eax\n\t"
      "pushl $0x36ee80\n\t"
      "pushl %%eax\n\t"
      "call *%[c81870]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c4030_13\n\t"
      "pushl %%edi\n\t"
      "movzwl %%si, %%edi\n\t"
      "movl 0x32eb98(,%%edi,4), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c4030_10\n\t"
      "pushl $2\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c4030_10\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19aa70]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x206, %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "divl %%ecx\n\t"
      "movzwl 0x8(%%ebp), %%ebx\n\t"
      "movl %%ebx, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "imull $0x206, %%esi, %%esi\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LFUN_001c4030_5\n\t"
      "pushl %%edi\n\t"
      "pushl $0x2bac8c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001c4030_5:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "leal 0x206(%%esi), %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "ja .LFUN_001c4030_7\n\t"
      "pushl %%esi\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19aa00]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c4030_6\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x206\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19ac00]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c4030_6\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_001c4030_9\n\t"
      ".LFUN_001c4030_6:\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "pushl $0x2bb284\n\t"
      "jmp .LFUN_001c4030_8\n\t"
      ".LFUN_001c4030_7:\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x2bb1cc\n\t"
      ".LFUN_001c4030_8:\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_001c4030_9:\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001c4030_12\n\t"
      "pushl %%edi\n\t"
      "pushl $0x2baafc\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jmp .LFUN_001c4030_11\n\t"
      ".LFUN_001c4030_10:\n\t"
      "pushl %%edi\n\t"
      "pushl $0x2bac54\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      ".LFUN_001c4030_11:\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001c4030_12:\n\t"
      "movl 0x4eacc0, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c818d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c4030_13:\n\t"
      "pushl $0x2bae8c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c4030_assert), [exitfn] "m"(b1c4030_exitfn), [c81870] "m"(b1c4030_c81870), [c1999f0] "m"(b1c4030_c1999f0), [c19a7a0] "m"(b1c4030_c19a7a0), [c19aa70] "m"(b1c4030_c19aa70), [c8f390] "m"(b1c4030_c8f390), [c19aa00] "m"(b1c4030_c19aa00), [c19ac00] "m"(b1c4030_c19ac00), [c19a930] "m"(b1c4030_c19a930), [c818d0] "m"(b1c4030_c818d0)
      : "memory");
}
#else
#error "FUN_001c4030: clang naked draft required"
#endif


/* FUN_001c4210 (0x1c4210) — XBE naked draft (batch 247). */
#if defined(__clang__)
static void (*const b1c4210_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c4210_exitfn)(int) = system_exit;
static bool (*const b1c4210_c81870)(int *mutex_reference, int timeout_ms) = take_mutex;
static file_ref_t * (*const b1c4210_c1999f0)(file_ref_t *info, const char *directory, bool a4) = file_reference_create_from_path;
static bool (*const b1c4210_c19a7a0)(file_ref_t *info, int flags) = file_open;
static int (*const b1c4210_c19aa70)(file_ref_t *info) = file_get_eof;
static void (*const b1c4210_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static bool (*const b1c4210_c19aa00)(file_ref_t *info, int offset) = file_set_position;
static void (*const b1c4210_c19ac00)(void) = file_write;
static bool (*const b1c4210_c19a930)(file_ref_t *info) = file_close;
static void (*const b1c4210_c818d0)(int *mutex_reference) = release_mutex;

__attribute__((naked, noinline))
void FUN_001c4210(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movw %%ax, %%si\n\t"
      "xorb %%bl, %%bl\n\t"
      "testw %%si, %%si\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "je .LFUN_001c4210_1\n\t"
      "pushl $1\n\t"
      "pushl $0x821\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2bacc8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c4210_1:\n\t"
      "movb 0x4eacc8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c4210_2\n\t"
      "pushl $1\n\t"
      "pushl $0x823\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2baac8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c4210_2:\n\t"
      "cmpw $9, %%si\n\t"
      "jae .LFUN_001c4210_3\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c4210_3\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001c4210_4\n\t"
      ".LFUN_001c4210_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x824\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2bb360\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c4210_4:\n\t"
      "movl 0x4eacc0, %%eax\n\t"
      "pushl $0x36ee80\n\t"
      "pushl %%eax\n\t"
      "call *%[c81870]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c4210_12\n\t"
      "movzwl %%si, %%ebx\n\t"
      "movl 0x32eb98(,%%ebx,4), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c4210_9\n\t"
      "pushl $2\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c4210_9\n\t"
      "pushl %%edi\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19aa70]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x206, %%ecx\n\t"
      "divl %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "imull $0x206, %%esi, %%esi\n\t"
      "cmpl $0x64, %%edi\n\t"
      "jge .LFUN_001c4210_7\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LFUN_001c4210_5\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x2bac8c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001c4210_5:\n\t"
      "pushl %%esi\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19aa00]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c4210_6\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x206\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19ac00]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c4210_6\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movl %%edi, (%%eax)\n\t"
      "jmp .LFUN_001c4210_8\n\t"
      ".LFUN_001c4210_6:\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x2bb32c\n\t"
      "pushl $2\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_001c4210_8\n\t"
      ".LFUN_001c4210_7:\n\t"
      "pushl $0x2bb2c0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c4210_8:\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "jne .LFUN_001c4210_11\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x2baafc\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jmp .LFUN_001c4210_10\n\t"
      ".LFUN_001c4210_9:\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x2bac54\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      ".LFUN_001c4210_10:\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001c4210_11:\n\t"
      "movl 0x4eacc0, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c818d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c4210_12:\n\t"
      "pushl $0x2bae8c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c4210_assert), [exitfn] "m"(b1c4210_exitfn), [c81870] "m"(b1c4210_c81870), [c1999f0] "m"(b1c4210_c1999f0), [c19a7a0] "m"(b1c4210_c19a7a0), [c19aa70] "m"(b1c4210_c19aa70), [c8f390] "m"(b1c4210_c8f390), [c19aa00] "m"(b1c4210_c19aa00), [c19ac00] "m"(b1c4210_c19ac00), [c19a930] "m"(b1c4210_c19a930), [c818d0] "m"(b1c4210_c818d0)
      : "memory");
}
#else
#error "FUN_001c4210: clang naked draft required"
#endif


/* FUN_001c43f0 (0x1c43f0) — XBE naked draft (batch 246). */
#if defined(__clang__)
static void (*const b1c43f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c43f0_exitfn)(int) = system_exit;
static bool (*const b1c43f0_c81870)(int *mutex_reference, int timeout_ms) = take_mutex;
static file_ref_t * (*const b1c43f0_c1999f0)(file_ref_t *info, const char *directory, bool a4) = file_reference_create_from_path;
static void (*const b1c43f0_c19adf0)(void) = file_get_size;
static bool (*const b1c43f0_c19a7a0)(file_ref_t *info, int flags) = file_open;
static bool (*const b1c43f0_c19aa00)(file_ref_t *info, int offset) = file_set_position;
static bool (*const b1c43f0_c19acb0)(file_ref_t *info, int offset, int size, void *buffer) = file_read_from_position;
static void (*const b1c43f0_c19acf0)(void) = file_write_to_position;
static void (*const b1c43f0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b1c43f0_c19aad0)(void) = file_set_eof;
static bool (*const b1c43f0_c19a930)(file_ref_t *info) = file_close;
static void (*const b1c43f0_c818d0)(int *mutex_reference) = release_mutex;

__attribute__((naked, noinline))
void FUN_001c43f0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movzwl %%cx, %%esi\n\t"
      "pushl %%edi\n\t"
      "imull $0x206, %%esi, %%esi\n\t"
      "movw %%ax, %%di\n\t"
      "xorb %%bl, %%bl\n\t"
      "testw %%di, %%di\n\t"
      "je .LFUN_001c43f0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x87a\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2bacc8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c43f0_1:\n\t"
      "movb 0x4eacc8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c43f0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x87c\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2baac8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c43f0_2:\n\t"
      "cmpw $9, %%di\n\t"
      "jb .LFUN_001c43f0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x87d\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2bad24\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c43f0_3:\n\t"
      "movl 0x4eacc0, %%eax\n\t"
      "pushl $0x36ee80\n\t"
      "pushl %%eax\n\t"
      "call *%[c81870]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c43f0_10\n\t"
      "movzwl %%di, %%ecx\n\t"
      "movl 0x32eb98(,%%ecx,4), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c43f0_9\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19adf0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c43f0_9\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "leal 0x206(%%esi), %%edi\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jb .LFUN_001c43f0_9\n\t"
      "pushl $3\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c43f0_9\n\t"
      "pushl %%esi\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19aa00]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $8, %%esp\n\t"
      "cmpb $1, %%bl\n\t"
      "jne .LFUN_001c43f0_6\n\t"
      "cmpl -0x4(%%ebp), %%edi\n\t"
      "jae .LFUN_001c43f0_7\n\t"
      "jmp .LFUN_001c43f0_4\n\t"
      "leal (%%esp), %%esp\n\t"
      "nop\n\t"
      ".LFUN_001c43f0_4:\n\t"
      "leal -0x20c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x206\n\t"
      "pushl %%edi\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19acb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c43f0_5\n\t"
      "leal -0x20c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x206\n\t"
      "pushl %%esi\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19acf0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c43f0_5\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $0x206, %%edi\n\t"
      "addl $0x206, %%esi\n\t"
      "cmpl %%eax, %%edi\n\t"
      "jb .LFUN_001c43f0_4\n\t"
      "jmp .LFUN_001c43f0_7\n\t"
      ".LFUN_001c43f0_5:\n\t"
      "pushl $0x2bb3e8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .LFUN_001c43f0_8\n\t"
      ".LFUN_001c43f0_6:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_001c43f0_8\n\t"
      ".LFUN_001c43f0_7:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $0xfffffdfa, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19aad0]\n\t"
      "addl $8, %%esp\n\t"
      "movb %%al, %%bl\n\t"
      ".LFUN_001c43f0_8:\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001c43f0_9\n\t"
      "pushl $0x2bb3bc\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_001c43f0_9:\n\t"
      "movl 0x4eacc0, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c818d0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c43f0_10:\n\t"
      "pushl $0x2bae8c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c43f0_assert), [exitfn] "m"(b1c43f0_exitfn), [c81870] "m"(b1c43f0_c81870), [c1999f0] "m"(b1c43f0_c1999f0), [c19adf0] "m"(b1c43f0_c19adf0), [c19a7a0] "m"(b1c43f0_c19a7a0), [c19aa00] "m"(b1c43f0_c19aa00), [c19acb0] "m"(b1c43f0_c19acb0), [c19acf0] "m"(b1c43f0_c19acf0), [c8f390] "m"(b1c43f0_c8f390), [c19aad0] "m"(b1c43f0_c19aad0), [c19a930] "m"(b1c43f0_c19a930), [c818d0] "m"(b1c43f0_c818d0)
      : "memory");
}
#else
#error "FUN_001c43f0: clang naked draft required"
#endif


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

/* FUN_001c4850 (0x1c4850) — XBE naked draft (batch 249). */
#if defined(__clang__)
static void (*const b1c4850_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c4850_exitfn)(int) = system_exit;
static void (*const b1c4850_c1c3e40)(void) = FUN_001c3e40;
static file_ref_t * (*const b1c4850_c1999f0)(file_ref_t *info, const char *directory, bool a4) = file_reference_create_from_path;
static bool (*const b1c4850_c19a7a0)(file_ref_t *info, int flags) = file_open;

__attribute__((naked, noinline))
void FUN_001c4850(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x208, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "movzbl %%ah, %%ebx\n\t"
      "sarl $0x10, %%eax\n\t"
      "andl $0xfff, %%eax\n\t"
      "andl $0xf, %%esi\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LFUN_001c4850_1\n\t"
      "pushl $1\n\t"
      "pushl $0x241\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba8c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c4850_1:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001c4850_2\n\t"
      "pushl $1\n\t"
      "pushl $0x244\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba8b0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c4850_2:\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LFUN_001c4850_3\n\t"
      "cmpl $2, %%esi\n\t"
      "jl .LFUN_001c4850_4\n\t"
      ".LFUN_001c4850_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x245\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba878\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c4850_4:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jl .LFUN_001c4850_5\n\t"
      "cmpl $9, %%ebx\n\t"
      "jl .LFUN_001c4850_6\n\t"
      ".LFUN_001c4850_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x246\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba838\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c4850_6:\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .LFUN_001c4850_7\n\t"
      "cmpl $0x64, %%edi\n\t"
      "jl .LFUN_001c4850_8\n\t"
      ".LFUN_001c4850_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x247\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba7e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c4850_8:\n\t"
      "leal -0x208(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c1c3e40]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c4850_9\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl $0\n\t"
      "leal -0x208(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c4850_9\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .LFUN_001c4850_9\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c4850_9\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c4850_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c4850_assert), [exitfn] "m"(b1c4850_exitfn), [c1c3e40] "m"(b1c4850_c1c3e40), [c1999f0] "m"(b1c4850_c1999f0), [c19a7a0] "m"(b1c4850_c19a7a0)
      : "memory");
}
#else
#error "FUN_001c4850: clang naked draft required"
#endif

