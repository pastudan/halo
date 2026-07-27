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

/* FUN_001c1b00 (0x1c1b00) — XBE naked draft (batch 262). */
#if defined(__clang__)
static void (*const b1c1b00_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c1b00_exitfn)(int) = system_exit;
static void (*const b1c1b00_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static bool (*const b1c1b00_c81720)(void *thread_reference) = thread_is_done;
static void (*const b1c1b00_c81770)(void *thread_reference) = thread_close;
static void * (*const b1c1b00_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static bool (*const b1c1b00_c81630)(int priority_flags, void *function, int param, void **thread_reference) = thread_new;

__attribute__((naked, noinline))
void FUN_001c1b00(int profile_handle __attribute__((unused)), void *out __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_001c1b00_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2c0\n\t"
      "pushl $0x2b9f70\n\t"
      "pushl $0x2829b0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c1b00_1:\n\t"
      "movl 0x4eaa2c, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c1b00_3\n\t"
      "pushl $0x2ba0f8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "nop\n\t"
      ".LFUN_001c1b00_2:\n\t"
      "movl 0x4eaa2c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c81720]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c1b00_2\n\t"
      "movl 0x4eaa2c, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c81770]\n\t"
      "addl $4, %%esp\n\t"
      "movl $0, 0x4eaa2c\n\t"
      ".LFUN_001c1b00_3:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $0x30\n\t"
      "pushl %%esi\n\t"
      "pushl $0x4ea9fc\n\t"
      "movl %%edx, 0x4ea9f8\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0x4eaa2c\n\t"
      "pushl $0x4ea9f8\n\t"
      "pushl $0x1c15c0\n\t"
      "pushl $0\n\t"
      "call *%[c81630]\n\t"
      "addl $0x1c, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c1b00_assert), [exitfn] "m"(b1c1b00_exitfn), [c8f390] "m"(b1c1b00_c8f390), [c81720] "m"(b1c1b00_c81720), [c81770] "m"(b1c1b00_c81770), [c8e0b0] "m"(b1c1b00_c8e0b0), [c81630] "m"(b1c1b00_c81630)
      : "memory");
}
#else
#error "FUN_001c1b00: clang naked draft required"
#endif


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

/* FUN_001c1c00 (0x1c1c00) — XBE naked draft (batch 259). */
#if defined(__clang__)
static int (*const b1c1c00_c100860)(void) = main_get_current_solo_level;
static void (*const b1c1c00_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c1c00_exitfn)(int) = system_exit;
static void (*const b1c1c00_ce09e0)(void) = (void *)player_ui_get_active_player_profile_index;
static void (*const b1c1c00_ce0980)(void) = (void (*)(void))player_ui_get_active_player_profile;
static void (*const b1c1c00_c1c1bc0)(void) = (void (*)(void))player_profile_get_from_path;
static void (*const b1c1c00_ce1490)(void) = (void (*)(void))player_ui_set_active_player_profile;

__attribute__((naked, noinline))
void FUN_001c1c00(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c100860]\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "movl %%eax, %%esi\n\t"
      "jl .LFUN_001c1c00_1\n\t"
      "cmpw $4, %%bx\n\t"
      "jl .LFUN_001c1c00_2\n\t"
      ".LFUN_001c1c00_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x17a\n\t"
      "pushl $0x2b9f70\n\t"
      "pushl $0x282750\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c1c00_2:\n\t"
      "cmpw $-1, %%si\n\t"
      "je .LFUN_001c1c00_7\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_001c1c00_3\n\t"
      "cmpw $0xa, %%si\n\t"
      "jl .LFUN_001c1c00_4\n\t"
      ".LFUN_001c1c00_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x17d\n\t"
      "pushl $0x2b9f70\n\t"
      "pushl $0x2ba30c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c1c00_4:\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[ce09e0]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_001c1c00_6\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[ce0980]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%si, -0xa(%%ebp)\n\t"
      "je .LFUN_001c1c00_5\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "movw %%si, -0xa(%%ebp)\n\t"
      "call *%[c1c1bc0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c1c00_5:\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[ce1490]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001c1c00_6:\n\t"
      "popl %%edi\n\t"
      ".LFUN_001c1c00_7:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c100860] "m"(b1c1c00_c100860), [assert] "m"(b1c1c00_assert), [exitfn] "m"(b1c1c00_exitfn), [ce09e0] "m"(b1c1c00_ce09e0), [ce0980] "m"(b1c1c00_ce0980), [c1c1bc0] "m"(b1c1c00_c1c1bc0), [ce1490] "m"(b1c1c00_ce1490)
      : "memory");
}
#else
#error "FUN_001c1c00: clang naked draft required"
#endif


/* FUN_001c1cc0 (0x1c1cc0) — XBE naked draft (batch 255). */
#if defined(__clang__)
static void (*const b1c1cc0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c1cc0_exitfn)(int) = system_exit;
static int (*const b1c1cc0_c100860)(void) = main_get_current_solo_level;
static int16_t (*const b1c1cc0_ca7460)(void) = game_difficulty_level_get;
static void (*const b1c1cc0_ce09e0)(void) = (void *)player_ui_get_active_player_profile_index;
static void (*const b1c1cc0_ce0980)(void) = (void (*)(void))player_ui_get_active_player_profile;
static void (*const b1c1cc0_c1c1b00)(void) = (void (*)(void))FUN_001c1b00;
static void (*const b1c1cc0_ce1490)(void) = (void (*)(void))player_ui_set_active_player_profile;
static void (*const b1c1cc0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_001c1cc0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jl .LFUN_001c1cc0_1\n\t"
      "cmpw $4, %%bx\n\t"
      "jl .LFUN_001c1cc0_2\n\t"
      ".LFUN_001c1cc0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x197\n\t"
      "pushl $0x2b9f70\n\t"
      "pushl $0x282750\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c1cc0_2:\n\t"
      "call *%[c100860]\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[ca7460]\n\t"
      "testw %%si, %%si\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "jl .LFUN_001c1cc0_3\n\t"
      "cmpw $0xa, %%si\n\t"
      "jge .LFUN_001c1cc0_3\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_001c1cc0_3\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .LFUN_001c1cc0_4\n\t"
      ".LFUN_001c1cc0_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x19d\n\t"
      "pushl $0x2b9f70\n\t"
      "pushl $0x2ba3b0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c1cc0_4:\n\t"
      "pushl %%ebx\n\t"
      "call *%[ce09e0]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_001c1cc0_5\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[ce0980]\n\t"
      "movb 0x8(%%ebp), %%cl\n\t"
      "movswl %%si, %%eax\n\t"
      "movb $1, %%dl\n\t"
      "shlb %%cl, %%dl\n\t"
      "movb -0x14(%%ebp,%%eax,1), %%cl\n\t"
      "leal -0x14(%%ebp,%%eax,1), %%eax\n\t"
      "pushl %%edi\n\t"
      "orb %%dl, %%cl\n\t"
      "leal -0x30(%%ebp), %%esi\n\t"
      "movb %%cl, (%%eax)\n\t"
      "call *%[c1c1b00]\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[ce1490]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c1cc0_5:\n\t"
      "pushl $0x2ba348\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c1cc0_assert), [exitfn] "m"(b1c1cc0_exitfn), [c100860] "m"(b1c1cc0_c100860), [ca7460] "m"(b1c1cc0_ca7460), [ce09e0] "m"(b1c1cc0_ce09e0), [ce0980] "m"(b1c1cc0_ce0980), [c1c1b00] "m"(b1c1cc0_c1c1b00), [ce1490] "m"(b1c1cc0_ce1490), [c8f390] "m"(b1c1cc0_c8f390)
      : "memory");
}
#else
#error "FUN_001c1cc0: clang naked draft required"
#endif


/* FUN_001c1da0 (0x1c1da0) — readable C lift. */
void FUN_001c1da0(void)
{
  extern char DAT_004eaa38[];
  char *base = (char *)csmemset(DAT_004eaa38, 0, 0x74);
  base[0x72] = 1; /* DAT_004eaaaa */
}

/* FUN_001c1dc0 (0x1c1dc0) — XBE naked draft (batch 288). */
#if defined(__clang__)
static void (*const b1c1dc0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static bool (*const b1c1dc0_c81720)(void *thread_reference) = thread_is_done;
static void (*const b1c1dc0_c81770)(void *thread_reference) = thread_close;
static void *(*const b1c1dc0_memset)(void *, int, unsigned int) = csmemset;

__attribute__((naked, noinline))
void FUN_001c1dc0(void)
{
  __asm__ volatile(
      "movl 0x4eaaa4, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c1dc0_2\n\t"
      "pushl $0x2ba430\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_001c1dc0_1\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_001c1dc0_1:\n\t"
      "movl 0x4eaaa4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c81720]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c1dc0_1\n\t"
      "movl 0x4eaaa4, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c81770]\n\t"
      "addl $4, %%esp\n\t"
      "movl $0, 0x4eaaa4\n\t"
      ".LFUN_001c1dc0_2:\n\t"
      "pushl $0x74\n\t"
      "pushl $0\n\t"
      "pushl $0x4eaa38\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "ret\n\t"
      :
      : [c8f390] "m"(b1c1dc0_c8f390), [c81720] "m"(b1c1dc0_c81720), [c81770] "m"(b1c1dc0_c81770), [memset] "m"(b1c1dc0_memset)
      : "memory");
}
#else
#error "FUN_001c1dc0: clang naked draft required"
#endif


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


/* FUN_001c1f70 (0x1c1f70) — readable C lift. */
void FUN_001c1f70(int profile_index)
{
  extern char DAT_002ba4d4[];

  if (profile_index == -1)
    return;
  if (!delete_enumerated_saved_game_file(profile_index))
    error(2, DAT_002ba4d4, profile_index);
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

/* FUN_001c2120 (0x1c2120) — XBE naked draft (batch 253). */
#if defined(__clang__)
static int (*const b1c2120_c1b9930)(int group_tag, const char *name, ...) = tag_loaded;
static int (*const b1c2120_c1d9179)(char *str, size_t size, const char *format, ...) = snprintf;
static void (*const b1c2120_c199a60)(void) = directory_create_or_delete_contents;
static char * (*const b1c2120_c8dd30)(char *destination, const char *source, size_t max_size) = csstrcat;
static int (*const b1c2120_c19d420)(int param_1, int param_2) = FUN_0019d420;
static void * (*const b1c2120_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static wchar_t * (*const b1c2120_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;
static void (*const b1c2120_c1c3160)(void) = saved_game_file_generate_checksum;
static file_ref_t * (*const b1c2120_c1999f0)(file_ref_t *info, const char *directory, bool a4) = file_reference_create_from_path;
static bool (*const b1c2120_c19a490)(file_ref_t *info) = FUN_0019a490;
static bool (*const b1c2120_c19a7a0)(file_ref_t *info, int flags) = file_open;
static bool (*const b1c2120_c19aa00)(file_ref_t *info, int offset) = file_set_position;
static void (*const b1c2120_c19ac00)(void) = file_write;
static bool (*const b1c2120_c19a930)(file_ref_t *info) = file_close;
static void (*const b1c2120_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b1c2120_c1c29b0)(void) = saved_game_files_notify_memory_units_changed;

__attribute__((naked, noinline))
void FUN_001c2120(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x4e4, %%esp\n\t"
      "pushl $0x28a4bc\n\t"
      "pushl $0x75737472\n\t"
      "call *%[c1b9930]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "je .LFUN_001c2120_4\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_001c2120_1:\n\t"
      "leal -0x4e4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x32eb28(,%%ebx,4)\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl $0x1a, %%ecx\n\t"
      "leal -0x27c(%%ebp), %%edi\n\t"
      "pushl $0x2ba67c\n\t"
      "rep movsl\n\t"
      "leal -0x108(%%ebp), %%ecx\n\t"
      "pushl $0xff\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9179]\n\t"
      "leal -0x108(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movb $0, -0x9(%%ebp)\n\t"
      "call *%[c199a60]\n\t"
      "pushl $0xff\n\t"
      "leal -0x108(%%ebp), %%eax\n\t"
      "pushl $0x2ba670\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dd30]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "movb $0, -0x9(%%ebp)\n\t"
      "call *%[c19d420]\n\t"
      "pushl $0x68\n\t"
      "leal -0x27c(%%ebp), %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl %%edx\n\t"
      "leal -0x47c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0xb\n\t"
      "leal -0x47c(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19dc90]\n\t"
      "xorl %%edx, %%edx\n\t"
      "addl $0x44, %%esp\n\t"
      "movb %%bl, %%dh\n\t"
      "leal -0x414(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x47c(%%ebp), %%ecx\n\t"
      "pushl $0x68\n\t"
      "pushl %%ecx\n\t"
      "movw $0, -0x466(%%ebp)\n\t"
      "orw %%dx, -0x418(%%ebp)\n\t"
      "call *%[c1c3160]\n\t"
      "pushl $0\n\t"
      "leal -0x108(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x214(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c2120_2\n\t"
      "leal -0x214(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19a490]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c2120_2\n\t"
      "leal -0x214(%%ebp), %%edx\n\t"
      "pushl $2\n\t"
      "pushl %%edx\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c2120_2\n\t"
      "leal -0x214(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c19aa00]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c2120_2\n\t"
      "leal -0x47c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x214(%%ebp), %%edx\n\t"
      "pushl $0x200\n\t"
      "pushl %%edx\n\t"
      "call *%[c19ac00]\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "leal -0x214(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19a930]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpb $1, %%al\n\t"
      "jne .LFUN_001c2120_2\n\t"
      "incw 0x4eaaa8\n\t"
      "jmp .LFUN_001c2120_3\n\t"
      ".LFUN_001c2120_2:\n\t"
      "leal -0x108(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2ba634\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001c2120_3:\n\t"
      "incl %%ebx\n\t"
      "cmpl $0x1a, %%ebx\n\t"
      "jl .LFUN_001c2120_1\n\t"
      "call *%[c1c29b0]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c2120_4:\n\t"
      "pushl $0x2ba5d0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1b9930] "m"(b1c2120_c1b9930), [c1d9179] "m"(b1c2120_c1d9179), [c199a60] "m"(b1c2120_c199a60), [c8dd30] "m"(b1c2120_c8dd30), [c19d420] "m"(b1c2120_c19d420), [c8e0b0] "m"(b1c2120_c8e0b0), [c19dc90] "m"(b1c2120_c19dc90), [c1c3160] "m"(b1c2120_c1c3160), [c1999f0] "m"(b1c2120_c1999f0), [c19a490] "m"(b1c2120_c19a490), [c19a7a0] "m"(b1c2120_c19a7a0), [c19aa00] "m"(b1c2120_c19aa00), [c19ac00] "m"(b1c2120_c19ac00), [c19a930] "m"(b1c2120_c19a930), [c8f390] "m"(b1c2120_c8f390), [c1c29b0] "m"(b1c2120_c1c29b0)
      : "memory");
}
#else
#error "FUN_001c2120: clang naked draft required"
#endif


/* playlist_profile_create_default_profiles_on_disk (0x1c22e0) — XBE naked draft (batch 244). */
#if defined(__clang__)
static void (*const b1c22e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c22e0_exitfn)(int) = system_exit;
static void (*const b1c22e0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static bool (*const b1c22e0_c81720)(void *thread_reference) = thread_is_done;
static void (*const b1c22e0_c81770)(void *thread_reference) = thread_close;
static void (*const b1c22e0_c1c2af0)(void) = (void *)saved_game_files_take_mutex;
static void (*const b1c22e0_c1c4850)(void) = FUN_001c4850;
static bool (*const b1c22e0_c19ab50)(file_ref_t *info, int size, void *buffer) = file_read;
static void (*const b1c22e0_c1c3160)(void) = saved_game_file_generate_checksum;
static int (*const b1c22e0_c8da40)(const void *a, const void *b, int size) = csmemcmp;
static void * (*const b1c22e0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b1c22e0_c1c2890)(void) = saved_game_file_close;
static void (*const b1c22e0_c1c2b10)(void) = (void *)saved_game_files_release_mutex;
static game_variant_t * (*const b1c22e0_caa190)(game_variant_t *out) = game_engine_slayer_default;
static void (*const b1c22e0_c1c4600)(void) = (void (*)(void))saved_game_file_get_display_name;
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
static void (*const b1c2550_c1c2af0)(void) = (void *)saved_game_files_take_mutex;
static void (*const b1c2550_c1c4850)(void) = FUN_001c4850;
static void * (*const b1c2550_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b1c2550_c1c3160)(void) = saved_game_file_generate_checksum;
static bool (*const b1c2550_c19aa00)(file_ref_t *info, int offset) = file_set_position;
static void (*const b1c2550_c19ac00)(void) = file_write;
static void (*const b1c2550_c1c2890)(void) = saved_game_file_close;
static void (*const b1c2550_c1c4990)(void) = FUN_001c4990;
static char (*const b1c2550_c1c46c0)(int param_1) = delete_enumerated_saved_game_file;
static void (*const b1c2550_c1c2b10)(void) = (void *)saved_game_files_release_mutex;

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


/* FUN_001c26b0 (0x1c26b0) — readable C lift. */
void FUN_001c26b0(int a0, int a1, int a2)
{
  if (*(char *)0x32eb90 == 1) {
    FUN_001c2120();
    *(char *)0x32eb90 = 0;
  }
  FUN_001c53f0(a0, 1, a1, a2, 1);
}

/* playlist_profile_delete (0x1c26f0) — XBE naked draft (batch 270). */
#if defined(__clang__)
static void (*const b1c26f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c26f0_exitfn)(int) = system_exit;
static void (*const b1c26f0_caa120)(int game_variant_type, int param_2, int param_3) = game_engine_playlist_next;
static void (*const b1c26f0_c1c22e0)(void) = playlist_profile_create_default_profiles_on_disk;

__attribute__((naked, noinline))
void playlist_profile_delete(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lplaylist_profile_delete_1\n\t"
      "pushl $1\n\t"
      "pushl $0xd9\n\t"
      "pushl $0x2ba59c\n\t"
      "pushl $0x282808\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplaylist_profile_delete_1:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lplaylist_profile_delete_2\n\t"
      "pushl $4\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[caa120]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplaylist_profile_delete_2:\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%ebx\n\t"
      "call *%[c1c22e0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c26f0_assert), [exitfn] "m"(b1c26f0_exitfn), [caa120] "m"(b1c26f0_caa120), [c1c22e0] "m"(b1c26f0_c1c22e0)
      : "memory");
}
#else
#error "playlist_profile_delete: clang naked draft required"
#endif


/* playlist_profile_read (0x1c2750) — XBE naked draft (batch 262). */
#if defined(__clang__)
static void (*const b1c2750_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c2750_exitfn)(int) = system_exit;
static void (*const b1c2750_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static bool (*const b1c2750_c81720)(void *thread_reference) = thread_is_done;
static void (*const b1c2750_c81770)(void *thread_reference) = thread_close;
static void * (*const b1c2750_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static bool (*const b1c2750_c81630)(int priority_flags, void *function, int param, void **thread_reference) = thread_new;

__attribute__((naked, noinline))
void playlist_profile_read(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lplaylist_profile_read_1\n\t"
      "pushl $1\n\t"
      "pushl $0x1ea\n\t"
      "pushl $0x2ba59c\n\t"
      "pushl $0x282808\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplaylist_profile_read_1:\n\t"
      "movl 0x4eaaa4, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lplaylist_profile_read_3\n\t"
      "pushl $0x2ba728\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "nop\n\t"
      ".Lplaylist_profile_read_2:\n\t"
      "movl 0x4eaaa4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c81720]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplaylist_profile_read_2\n\t"
      "movl 0x4eaaa4, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c81770]\n\t"
      "addl $4, %%esp\n\t"
      "movl $0, 0x4eaaa4\n\t"
      ".Lplaylist_profile_read_3:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $0x68\n\t"
      "pushl %%esi\n\t"
      "pushl $0x4eaa3c\n\t"
      "movl %%edx, 0x4eaa38\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0x4eaaa4\n\t"
      "pushl $0x4eaa38\n\t"
      "pushl $0x1c2550\n\t"
      "pushl $0\n\t"
      "call *%[c81630]\n\t"
      "addl $0x1c, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c2750_assert), [exitfn] "m"(b1c2750_exitfn), [c8f390] "m"(b1c2750_c8f390), [c81720] "m"(b1c2750_c81720), [c81770] "m"(b1c2750_c81770), [c8e0b0] "m"(b1c2750_c8e0b0), [c81630] "m"(b1c2750_c81630)
      : "memory");
}
#else
#error "playlist_profile_read: clang naked draft required"
#endif


/* playlist_profile_get_display_name (0x1c27f0) — XBE naked draft (batch 277). */
#if defined(__clang__)
static void (*const b1c27f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c27f0_exitfn)(int) = system_exit;
static void (*const b1c27f0_cab570)(game_variant_t *variant) = game_engine_variant_cleanup;
static void (*const b1c27f0_c1c2750)(void) = playlist_profile_read;

__attribute__((naked, noinline))
void playlist_profile_get_display_name(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .Lplaylist_profile_get_display_name_1\n\t"
      "pushl $1\n\t"
      "pushl $0x131\n\t"
      "pushl $0x2ba59c\n\t"
      "pushl $0x282808\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplaylist_profile_get_display_name_1:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lplaylist_profile_get_display_name_2\n\t"
      "pushl %%esi\n\t"
      "call *%[cab570]\n\t"
      "pushl %%edi\n\t"
      "call *%[c1c2750]\n\t"
      "addl $8, %%esp\n\t"
      ".Lplaylist_profile_get_display_name_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c27f0_assert), [exitfn] "m"(b1c27f0_exitfn), [cab570] "m"(b1c27f0_cab570), [c1c2750] "m"(b1c27f0_c1c2750)
      : "memory");
}
#else
#error "playlist_profile_get_display_name: clang naked draft required"
#endif


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
/* saved_game_file_get_useable_untitled_profile_name (0x1c29c0) — XBE naked draft (batch 253). */
#if defined(__clang__)
static void (*const b1c29c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c29c0_exitfn)(int) = system_exit;
static int (*const b1c29c0_c1b9930)(int group_tag, const char *name, ...) = tag_loaded;
static char * (*const b1c29c0_c19f3a0)(const wchar_t *unicode, char *ascii, int size) = wide_to_ascii;
static int (*const b1c29c0_c19d420)(int param_1, int param_2) = FUN_0019d420;
static void (*const b1c29c0_c19e9f0)(wchar_t *buffer, int buffer_size, const wchar_t *format, ...) = unicode_sprintf;
static void (*const b1c29c0_c1d2f22)(void) = FUN_001d2f22;
static void (*const b1c29c0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void saved_game_file_get_useable_untitled_profile_name(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x108, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lsaved_game_file_get_useable_untitled_profile_name_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2c1\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba974\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsaved_game_file_get_useable_untitled_profile_name_1:\n\t"
      "pushl $0x28a528\n\t"
      "pushl $0x75737472\n\t"
      "movw $0, (%%esi)\n\t"
      "call *%[c1b9930]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "je .Lsaved_game_file_get_useable_untitled_profile_name_4\n\t"
      "movl 0x32eb94, %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0x7(%%ebp)\n\t"
      "movw %%ax, -0x3(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movb %%al, -0x108(%%ebp)\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "movl $0x3f, %%ecx\n\t"
      "leal -0x107(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "pushl $8\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "stosw\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movb $0, -0x8(%%ebp)\n\t"
      ".byte 0xaa\n\t"
      "call *%[c19f3a0]\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      ".Lsaved_game_file_get_useable_untitled_profile_name_2:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal 0x1(%%ebx), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "call *%[c19d420]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x7f\n\t"
      "pushl %%esi\n\t"
      "call *%[c19e9f0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl $0x100\n\t"
      "leal -0x108(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movw $0, 0xfe(%%esi)\n\t"
      "call *%[c1d2f22]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lsaved_game_file_get_useable_untitled_profile_name_3\n\t"
      "movl %%edi, %%ebx\n\t"
      "cmpl $0x3e7, %%ebx\n\t"
      "jl .Lsaved_game_file_get_useable_untitled_profile_name_2\n\t"
      ".Lsaved_game_file_get_useable_untitled_profile_name_3:\n\t"
      "popl %%edi\n\t"
      "cmpl $0x3e7, %%ebx\n\t"
      "popl %%ebx\n\t"
      "jne .Lsaved_game_file_get_useable_untitled_profile_name_5\n\t"
      "pushl $0x3e7\n\t"
      "pushl $0x2ba940\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "movw $0, (%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsaved_game_file_get_useable_untitled_profile_name_4:\n\t"
      "pushl $0x28a528\n\t"
      "pushl $0x2ba918\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lsaved_game_file_get_useable_untitled_profile_name_5:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c29c0_assert), [exitfn] "m"(b1c29c0_exitfn), [c1b9930] "m"(b1c29c0_c1b9930), [c19f3a0] "m"(b1c29c0_c19f3a0), [c19d420] "m"(b1c29c0_c19d420), [c19e9f0] "m"(b1c29c0_c19e9f0), [c1d2f22] "m"(b1c29c0_c1d2f22), [c8f390] "m"(b1c29c0_c8f390)
      : "memory");
}
#else
#error "saved_game_file_get_useable_untitled_profile_name: clang naked draft required"
#endif


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

/* saved_game_perform_file_system_checks (0x1c2b20) — XBE naked draft (batch 259). */
#if defined(__clang__)
static char * (*const b1c2b20_c19f3a0)(const wchar_t *unicode, char *ascii, int size) = wide_to_ascii;
static void (*const b1c2b20_c1d3739)(void) = FUN_001d3739;
static void (*const b1c2b20_c1d3254)(void) = FUN_001d3254;
static void (*const b1c2b20_c1d335b)(void) = FUN_001d335b;
static void __stdcall (*const b1c2b20_c1d33a2)(int param_1) = FUN_001d33a2;
static void (*const b1c2b20_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void saved_game_perform_file_system_checks(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x364, %%esp\n\t"
      "pushl %%ebx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x32eb94, %%ecx\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $8\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "call *%[c19f3a0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d3739]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsaved_game_perform_file_system_checks_2\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "ja .Lsaved_game_perform_file_system_checks_2\n\t"
      "jb .Lsaved_game_perform_file_system_checks_1\n\t"
      "cmpl $0x2800000, -0x8(%%ebp)\n\t"
      "jae .Lsaved_game_perform_file_system_checks_2\n\t"
      ".Lsaved_game_perform_file_system_checks_1:\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsaved_game_perform_file_system_checks_2:\n\t"
      "movl 0x32eb94, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "leal -0x364(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $8\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19f3a0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d3254]\n\t"
      "movl %%eax, %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl $1, %%esi\n\t"
      "je .Lsaved_game_perform_file_system_checks_6\n\t"
      ".Lsaved_game_perform_file_system_checks_3:\n\t"
      "cmpl $0x64, %%esi\n\t"
      "jae .Lsaved_game_perform_file_system_checks_4\n\t"
      "leal -0x364(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "incl %%esi\n\t"
      "call *%[c1d335b]\n\t"
      "cmpb $1, %%al\n\t"
      "je .Lsaved_game_perform_file_system_checks_3\n\t"
      ".Lsaved_game_perform_file_system_checks_4:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d33a2]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lsaved_game_perform_file_system_checks_5\n\t"
      "pushl $0x2ba984\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lsaved_game_perform_file_system_checks_5:\n\t"
      "cmpl $0x64, %%esi\n\t"
      "jb .Lsaved_game_perform_file_system_checks_6\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $2, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsaved_game_perform_file_system_checks_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%bx, %%ax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c19f3a0] "m"(b1c2b20_c19f3a0), [c1d3739] "m"(b1c2b20_c1d3739), [c1d3254] "m"(b1c2b20_c1d3254), [c1d335b] "m"(b1c2b20_c1d335b), [c1d33a2] "m"(b1c2b20_c1d33a2), [c8f390] "m"(b1c2b20_c8f390)
      : "memory");
}
#else
#error "saved_game_perform_file_system_checks: clang naked draft required"
#endif


/* saved_game_file_name_unique (0x1c2bf0) — XBE naked draft (batch 285). */
#if defined(__clang__)
static char * (*const b1c2bf0_c19f3a0)(const wchar_t *unicode, char *ascii, int size) = wide_to_ascii;
static void (*const b1c2bf0_c1d2f22)(void) = FUN_001d2f22;

__attribute__((naked, noinline))
char saved_game_file_name_unique(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x108, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "xorb %%bl, %%bl\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsaved_game_file_name_unique_1\n\t"
      "cmpw $0, (%%eax)\n\t"
      "je .Lsaved_game_file_name_unique_1\n\t"
      "pushl $0x100\n\t"
      "leal -0x108(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "movl 0x32eb94, %%eax\n\t"
      "pushl $8\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c19f3a0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2f22]\n\t"
      "testl %%eax, %%eax\n\t"
      "movb $1, %%al\n\t"
      "jne .Lsaved_game_file_name_unique_2\n\t"
      ".Lsaved_game_file_name_unique_1:\n\t"
      "movb %%bl, %%al\n\t"
      ".Lsaved_game_file_name_unique_2:\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c19f3a0] "m"(b1c2bf0_c19f3a0), [c1d2f22] "m"(b1c2bf0_c1d2f22)
      : "memory");
}
#else
#error "saved_game_file_name_unique: clang naked draft required"
#endif


/* saved_game_file_remember_player1_last_used_profile_directory (0x1c2c50) — XBE naked draft (batch 257). */
#if defined(__clang__)
static void (*const b1c2c50_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c2c50_exitfn)(int) = system_exit;
static file_ref_t * (*const b1c2c50_c1999f0)(file_ref_t *info, const char *directory, bool a4) = file_reference_create_from_path;
static bool (*const b1c2c50_c19a490)(file_ref_t *info) = FUN_0019a490;
static bool (*const b1c2c50_c19a7a0)(file_ref_t *info, int flags) = file_open;
static void (*const b1c2c50_c19ac00)(void) = file_write;
static void (*const b1c2c50_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static bool (*const b1c2c50_c19a930)(file_ref_t *info) = file_close;

__attribute__((naked, noinline))
void saved_game_file_remember_player1_last_used_profile_directory(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10c, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lsaved_game_file_remember_player1_last_used_profile_directory_1\n\t"
      "pushl $1\n\t"
      "pushl $0x41a\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba9d4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsaved_game_file_remember_player1_last_used_profile_directory_1:\n\t"
      "pushl $0\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl $0x2ba9c4\n\t"
      "pushl %%eax\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsaved_game_file_remember_player1_last_used_profile_directory_3\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19a490]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsaved_game_file_remember_player1_last_used_profile_directory_3\n\t"
      "leal -0x10c(%%ebp), %%edx\n\t"
      "pushl $2\n\t"
      "pushl %%edx\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsaved_game_file_remember_player1_last_used_profile_directory_3\n\t"
      "pushl %%esi\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl $0x100\n\t"
      "pushl %%eax\n\t"
      "call *%[c19ac00]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lsaved_game_file_remember_player1_last_used_profile_directory_2\n\t"
      "pushl $0x2ba9c4\n\t"
      "pushl $0x2ba9ac\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lsaved_game_file_remember_player1_last_used_profile_directory_2:\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsaved_game_file_remember_player1_last_used_profile_directory_3:\n\t"
      "pushl $0x2ba9c4\n\t"
      "pushl $0x2ba998\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c2c50_assert), [exitfn] "m"(b1c2c50_exitfn), [c1999f0] "m"(b1c2c50_c1999f0), [c19a490] "m"(b1c2c50_c19a490), [c19a7a0] "m"(b1c2c50_c19a7a0), [c19ac00] "m"(b1c2c50_c19ac00), [c8f390] "m"(b1c2c50_c8f390), [c19a930] "m"(b1c2c50_c19a930)
      : "memory");
}
#else
#error "saved_game_file_remember_player1_last_used_profile_directory: clang naked draft required"
#endif


/* saved_game_file_retrieve_player1_last_used_profile_directory (0x1c2d20) — XBE naked draft (batch 256). */
#if defined(__clang__)
static void (*const b1c2d20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c2d20_exitfn)(int) = system_exit;
static file_ref_t * (*const b1c2d20_c1999f0)(file_ref_t *info, const char *directory, bool a4) = file_reference_create_from_path;
static bool (*const b1c2d20_c19a7a0)(file_ref_t *info, int flags) = file_open;
static bool (*const b1c2d20_c19ab50)(file_ref_t *info, int size, void *buffer) = file_read;
static void (*const b1c2d20_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static bool (*const b1c2d20_c19a930)(file_ref_t *info) = file_close;

__attribute__((naked, noinline))
char saved_game_file_retrieve_player1_last_used_profile_directory(void *out_path __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lsaved_game_file_retrieve_player1_last_used_profile_directory_1\n\t"
      "pushl $1\n\t"
      "pushl $0x434\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba9d4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsaved_game_file_retrieve_player1_last_used_profile_directory_1:\n\t"
      "pushl $0\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl $0x2ba9c4\n\t"
      "pushl %%eax\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsaved_game_file_retrieve_player1_last_used_profile_directory_3\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsaved_game_file_retrieve_player1_last_used_profile_directory_3\n\t"
      "pushl %%esi\n\t"
      "leal -0x10c(%%ebp), %%edx\n\t"
      "pushl $0x100\n\t"
      "pushl %%edx\n\t"
      "call *%[c19ab50]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lsaved_game_file_retrieve_player1_last_used_profile_directory_2\n\t"
      "pushl $0x2ba9c4\n\t"
      "pushl $0x2ba9e4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lsaved_game_file_retrieve_player1_last_used_profile_directory_2:\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "movb $0, 0xff(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsaved_game_file_retrieve_player1_last_used_profile_directory_3:\n\t"
      "pushl $0x2ba9c4\n\t"
      "pushl $0x2ba998\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "movb $0, 0xff(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c2d20_assert), [exitfn] "m"(b1c2d20_exitfn), [c1999f0] "m"(b1c2d20_c1999f0), [c19a7a0] "m"(b1c2d20_c19a7a0), [c19ab50] "m"(b1c2d20_c19ab50), [c8f390] "m"(b1c2d20_c8f390), [c19a930] "m"(b1c2d20_c19a930)
      : "memory");
}
#else
#error "saved_game_file_retrieve_player1_last_used_profile_directory: clang naked draft required"
#endif


/* saved_game_file_remember_last_used_multiplayer_variant_directory (0x1c2e00) — XBE naked draft (batch 257). */
#if defined(__clang__)
static void (*const b1c2e00_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c2e00_exitfn)(int) = system_exit;
static file_ref_t * (*const b1c2e00_c1999f0)(file_ref_t *info, const char *directory, bool a4) = file_reference_create_from_path;
static bool (*const b1c2e00_c19a490)(file_ref_t *info) = FUN_0019a490;
static bool (*const b1c2e00_c19a7a0)(file_ref_t *info, int flags) = file_open;
static void (*const b1c2e00_c19ac00)(void) = file_write;
static void (*const b1c2e00_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static bool (*const b1c2e00_c19a930)(file_ref_t *info) = file_close;

__attribute__((naked, noinline))
void saved_game_file_remember_last_used_multiplayer_variant_directory(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10c, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lsaved_game_file_remember_last_used_multiplayer_variant_directory_1\n\t"
      "pushl $1\n\t"
      "pushl $0x44e\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba9d4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsaved_game_file_remember_last_used_multiplayer_variant_directory_1:\n\t"
      "pushl $0\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl $0x2baa00\n\t"
      "pushl %%eax\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsaved_game_file_remember_last_used_multiplayer_variant_directory_3\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19a490]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsaved_game_file_remember_last_used_multiplayer_variant_directory_3\n\t"
      "leal -0x10c(%%ebp), %%edx\n\t"
      "pushl $2\n\t"
      "pushl %%edx\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsaved_game_file_remember_last_used_multiplayer_variant_directory_3\n\t"
      "pushl %%esi\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl $0x100\n\t"
      "pushl %%eax\n\t"
      "call *%[c19ac00]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lsaved_game_file_remember_last_used_multiplayer_variant_directory_2\n\t"
      "pushl $0x2baa00\n\t"
      "pushl $0x2ba9ac\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lsaved_game_file_remember_last_used_multiplayer_variant_directory_2:\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsaved_game_file_remember_last_used_multiplayer_variant_directory_3:\n\t"
      "pushl $0x2baa00\n\t"
      "pushl $0x2ba998\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c2e00_assert), [exitfn] "m"(b1c2e00_exitfn), [c1999f0] "m"(b1c2e00_c1999f0), [c19a490] "m"(b1c2e00_c19a490), [c19a7a0] "m"(b1c2e00_c19a7a0), [c19ac00] "m"(b1c2e00_c19ac00), [c8f390] "m"(b1c2e00_c8f390), [c19a930] "m"(b1c2e00_c19a930)
      : "memory");
}
#else
#error "saved_game_file_remember_last_used_multiplayer_variant_directory: clang naked draft required"
#endif


/* saved_game_file_retrieve_last_used_multiplayer_variant_directory (0x1c2ed0) — XBE naked draft (batch 256). */
#if defined(__clang__)
static void (*const b1c2ed0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c2ed0_exitfn)(int) = system_exit;
static file_ref_t * (*const b1c2ed0_c1999f0)(file_ref_t *info, const char *directory, bool a4) = file_reference_create_from_path;
static bool (*const b1c2ed0_c19a7a0)(file_ref_t *info, int flags) = file_open;
static bool (*const b1c2ed0_c19ab50)(file_ref_t *info, int size, void *buffer) = file_read;
static void (*const b1c2ed0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static bool (*const b1c2ed0_c19a930)(file_ref_t *info) = file_close;

__attribute__((naked, noinline))
void saved_game_file_retrieve_last_used_multiplayer_variant_directory(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lsaved_game_file_retrieve_last_used_multiplayer_variant_directory_1\n\t"
      "pushl $1\n\t"
      "pushl $0x468\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba9d4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsaved_game_file_retrieve_last_used_multiplayer_variant_directory_1:\n\t"
      "pushl $0\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl $0x2baa00\n\t"
      "pushl %%eax\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsaved_game_file_retrieve_last_used_multiplayer_variant_directory_3\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsaved_game_file_retrieve_last_used_multiplayer_variant_directory_3\n\t"
      "pushl %%esi\n\t"
      "leal -0x10c(%%ebp), %%edx\n\t"
      "pushl $0x100\n\t"
      "pushl %%edx\n\t"
      "call *%[c19ab50]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lsaved_game_file_retrieve_last_used_multiplayer_variant_directory_2\n\t"
      "pushl $0x2baa00\n\t"
      "pushl $0x2ba9e4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lsaved_game_file_retrieve_last_used_multiplayer_variant_directory_2:\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "movb $0, 0xff(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsaved_game_file_retrieve_last_used_multiplayer_variant_directory_3:\n\t"
      "pushl $0x2baa00\n\t"
      "pushl $0x2ba998\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "movb $0, 0xff(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c2ed0_assert), [exitfn] "m"(b1c2ed0_exitfn), [c1999f0] "m"(b1c2ed0_c1999f0), [c19a7a0] "m"(b1c2ed0_c19a7a0), [c19ab50] "m"(b1c2ed0_c19ab50), [c8f390] "m"(b1c2ed0_c8f390), [c19a930] "m"(b1c2ed0_c19a930)
      : "memory");
}
#else
#error "saved_game_file_retrieve_last_used_multiplayer_variant_directory: clang naked draft required"
#endif


/* saved_game_file_remember_last_used_multiplayer_map (0x1c2fb0) — XBE naked draft (batch 257). */
#if defined(__clang__)
static void (*const b1c2fb0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c2fb0_exitfn)(int) = system_exit;
static file_ref_t * (*const b1c2fb0_c1999f0)(file_ref_t *info, const char *directory, bool a4) = file_reference_create_from_path;
static bool (*const b1c2fb0_c19a490)(file_ref_t *info) = FUN_0019a490;
static bool (*const b1c2fb0_c19a7a0)(file_ref_t *info, int flags) = file_open;
static void (*const b1c2fb0_c19ac00)(void) = file_write;
static void (*const b1c2fb0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static bool (*const b1c2fb0_c19a930)(file_ref_t *info) = file_close;

__attribute__((naked, noinline))
void saved_game_file_remember_last_used_multiplayer_map(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10c, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lsaved_game_file_remember_last_used_multiplayer_map_1\n\t"
      "pushl $1\n\t"
      "pushl $0x4b7\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x274e68\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsaved_game_file_remember_last_used_multiplayer_map_1:\n\t"
      "pushl $0\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl $0x2baa10\n\t"
      "pushl %%eax\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsaved_game_file_remember_last_used_multiplayer_map_3\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19a490]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsaved_game_file_remember_last_used_multiplayer_map_3\n\t"
      "leal -0x10c(%%ebp), %%edx\n\t"
      "pushl $2\n\t"
      "pushl %%edx\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsaved_game_file_remember_last_used_multiplayer_map_3\n\t"
      "pushl %%esi\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl $0x100\n\t"
      "pushl %%eax\n\t"
      "call *%[c19ac00]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lsaved_game_file_remember_last_used_multiplayer_map_2\n\t"
      "pushl $0x2baa10\n\t"
      "pushl $0x2ba9ac\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lsaved_game_file_remember_last_used_multiplayer_map_2:\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsaved_game_file_remember_last_used_multiplayer_map_3:\n\t"
      "pushl $0x2baa10\n\t"
      "pushl $0x2ba998\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c2fb0_assert), [exitfn] "m"(b1c2fb0_exitfn), [c1999f0] "m"(b1c2fb0_c1999f0), [c19a490] "m"(b1c2fb0_c19a490), [c19a7a0] "m"(b1c2fb0_c19a7a0), [c19ac00] "m"(b1c2fb0_c19ac00), [c8f390] "m"(b1c2fb0_c8f390), [c19a930] "m"(b1c2fb0_c19a930)
      : "memory");
}
#else
#error "saved_game_file_remember_last_used_multiplayer_map: clang naked draft required"
#endif


/* saved_game_file_retrieve_last_used_multiplayer_map (0x1c3080) — XBE naked draft (batch 256). */
#if defined(__clang__)
static void (*const b1c3080_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c3080_exitfn)(int) = system_exit;
static file_ref_t * (*const b1c3080_c1999f0)(file_ref_t *info, const char *directory, bool a4) = file_reference_create_from_path;
static bool (*const b1c3080_c19a7a0)(file_ref_t *info, int flags) = file_open;
static bool (*const b1c3080_c19ab50)(file_ref_t *info, int size, void *buffer) = file_read;
static void (*const b1c3080_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static bool (*const b1c3080_c19a930)(file_ref_t *info) = file_close;

__attribute__((naked, noinline))
void saved_game_file_retrieve_last_used_multiplayer_map(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lsaved_game_file_retrieve_last_used_multiplayer_map_1\n\t"
      "pushl $1\n\t"
      "pushl $0x4d1\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x274e68\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsaved_game_file_retrieve_last_used_multiplayer_map_1:\n\t"
      "pushl $0\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl $0x2baa10\n\t"
      "pushl %%eax\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsaved_game_file_retrieve_last_used_multiplayer_map_3\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsaved_game_file_retrieve_last_used_multiplayer_map_3\n\t"
      "pushl %%esi\n\t"
      "leal -0x10c(%%ebp), %%edx\n\t"
      "pushl $0x100\n\t"
      "pushl %%edx\n\t"
      "call *%[c19ab50]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lsaved_game_file_retrieve_last_used_multiplayer_map_2\n\t"
      "pushl $0x2baa10\n\t"
      "pushl $0x2ba9e4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lsaved_game_file_retrieve_last_used_multiplayer_map_2:\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "movb $0, 0xff(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsaved_game_file_retrieve_last_used_multiplayer_map_3:\n\t"
      "pushl $0x2baa10\n\t"
      "pushl $0x2ba998\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "movb $0, 0xff(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c3080_assert), [exitfn] "m"(b1c3080_exitfn), [c1999f0] "m"(b1c3080_c1999f0), [c19a7a0] "m"(b1c3080_c19a7a0), [c19ab50] "m"(b1c3080_c19ab50), [c8f390] "m"(b1c3080_c8f390), [c19a930] "m"(b1c3080_c19a930)
      : "memory");
}
#else
#error "saved_game_file_retrieve_last_used_multiplayer_map: clang naked draft required"
#endif


/* saved_game_file_generate_checksum (0x1c3160) — XBE naked draft (batch 264). */
#if defined(__clang__)
static void (*const b1c3160_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c3160_exitfn)(int) = system_exit;
static void (*const b1c3160_c1d426b)(void) = XCalculateSignatureBegin;
static void (*const b1c3160_c1d42a9)(void) = FUN_001d42a9;
static void (*const b1c3160_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b1c3160_c1d42c3)(void) = FUN_001d42c3;

__attribute__((naked, noinline))
void saved_game_file_generate_checksum(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lsaved_game_file_generate_checksum_1\n\t"
      "pushl $1\n\t"
      "pushl $0x4eb\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x267900\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsaved_game_file_generate_checksum_1:\n\t"
      "pushl $0\n\t"
      "call *%[c1d426b]\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lsaved_game_file_generate_checksum_3\n\t"
      "movzwl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d42a9]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsaved_game_file_generate_checksum_2\n\t"
      "pushl $0x2baa64\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lsaved_game_file_generate_checksum_2:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d42c3]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsaved_game_file_generate_checksum_4\n\t"
      "pushl $0x2baa44\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsaved_game_file_generate_checksum_3:\n\t"
      "pushl $0x2baa20\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lsaved_game_file_generate_checksum_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c3160_assert), [exitfn] "m"(b1c3160_exitfn), [c1d426b] "m"(b1c3160_c1d426b), [c1d42a9] "m"(b1c3160_c1d42a9), [c8f390] "m"(b1c3160_c8f390), [c1d42c3] "m"(b1c3160_c1d42c3)
      : "memory");
}
#else
#error "saved_game_file_generate_checksum: clang naked draft required"
#endif


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




/* FUN_001c3250 (0x1c3250) — XBE naked draft (batch 260). */
#if defined(__clang__)
static void (*const b1c3250_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c3250_exitfn)(int) = system_exit;
static file_ref_t * (*const b1c3250_c1999f0)(file_ref_t *info, const char *directory, bool a4) = file_reference_create_from_path;
static bool (*const b1c3250_c19a490)(file_ref_t *info) = FUN_0019a490;
static bool (*const b1c3250_c19a7a0)(file_ref_t *info, int flags) = file_open;
static void (*const b1c3250_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_001c3250(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movw %%ax, %%si\n\t"
      "testw %%si, %%si\n\t"
      "je .LFUN_001c3250_1\n\t"
      "pushl $1\n\t"
      "pushl $0x66b\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba8c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c3250_1:\n\t"
      "movb 0x4eacc8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c3250_2\n\t"
      "pushl $1\n\t"
      "pushl $0x66f\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2baac8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c3250_2:\n\t"
      "movzwl %%si, %%esi\n\t"
      "movl 0x32eb98(,%%esi,4), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c3250_3\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19a490]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c3250_3\n\t"
      "pushl $2\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c3250_3\n\t"
      "movb $1, %%al\n\t"
      "movw $0, 0x4eacc4\n\t"
      "movb %%al, 0x4eacc8\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LFUN_001c3250_3:\n\t"
      "pushl %%esi\n\t"
      "pushl $0x2baa88\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movb 0x4eacc8, %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "movw $0xffff, 0x4eacc4\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c3250_assert), [exitfn] "m"(b1c3250_exitfn), [c1999f0] "m"(b1c3250_c1999f0), [c19a490] "m"(b1c3250_c19a490), [c19a7a0] "m"(b1c3250_c19a7a0), [c8f390] "m"(b1c3250_c8f390)
      : "memory");
}
#else
#error "FUN_001c3250: clang naked draft required"
#endif


/* FUN_001c3320 (0x1c3320) — XBE naked draft (batch 267). */
#if defined(__clang__)
static void (*const b1c3320_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c3320_exitfn)(int) = system_exit;
static bool (*const b1c3320_c19a930)(file_ref_t *info) = file_close;
static void (*const b1c3320_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_001c3320(void)
{
  __asm__ volatile(
      "testw %%si, %%si\n\t"
      "je .LFUN_001c3320_1\n\t"
      "pushl $1\n\t"
      "pushl $0x685\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba8c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c3320_1:\n\t"
      "movb 0x4eacc8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001c3320_2\n\t"
      "pushl $1\n\t"
      "pushl $0x687\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2bab34\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c3320_2:\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001c3320_3\n\t"
      "movzwl %%si, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2baafc\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001c3320_3:\n\t"
      "movw $0xffff, 0x4eacc4\n\t"
      "movb $0, 0x4eacc8\n\t"
      "movb $1, %%al\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c3320_assert), [exitfn] "m"(b1c3320_exitfn), [c19a930] "m"(b1c3320_c19a930), [c8f390] "m"(b1c3320_c8f390)
      : "memory");
}
#else
#error "FUN_001c3320: clang naked draft required"
#endif


/* FUN_001c33b0 (0x1c33b0) — XBE naked draft (batch 271). */
#if defined(__clang__)
static void (*const b1c33b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c33b0_exitfn)(int) = system_exit;
static void (*const b1c33b0_c19ac00)(void) = file_write;
static void (*const b1c33b0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_001c33b0(void)
{
  __asm__ volatile(
      "movb 0x4eacc8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c33b0_1\n\t"
      "movw 0x4eacc4, %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .LFUN_001c33b0_2\n\t"
      ".LFUN_001c33b0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x741\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2babe0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movw 0x4eacc4, %%ax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c33b0_2:\n\t"
      "cmpw $0x64, %%ax\n\t"
      "jge .LFUN_001c33b0_3\n\t"
      "pushl %%esi\n\t"
      "pushl $0x206\n\t"
      "movw %%ax, 0x202(%%esi)\n\t"
      "incw 0x4eacc4\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19ac00]\n\t"
      "addl $0xc, %%esp\n\t"
      "ret\n\t"
      ".LFUN_001c33b0_3:\n\t"
      "pushl $0x2bab68\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%al, %%al\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c33b0_assert), [exitfn] "m"(b1c33b0_exitfn), [c19ac00] "m"(b1c33b0_c19ac00), [c8f390] "m"(b1c33b0_c8f390)
      : "memory");
}
#else
#error "FUN_001c33b0: clang naked draft required"
#endif


/* FUN_001c3430 (0x1c3430) — XBE naked draft (batch 258). */
#if defined(__clang__)
static void (*const b1c3430_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c3430_exitfn)(int) = system_exit;
static file_ref_t * (*const b1c3430_c1999f0)(file_ref_t *info, const char *directory, bool a4) = file_reference_create_from_path;
static bool (*const b1c3430_c19a7a0)(file_ref_t *info, int flags) = file_open;
static int (*const b1c3430_c19aa70)(file_ref_t *info) = file_get_eof;
static void (*const b1c3430_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_001c3430(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "movw %%ax, %%si\n\t"
      "testw %%si, %%si\n\t"
      "je .LFUN_001c3430_1\n\t"
      "pushl $1\n\t"
      "pushl $0x75b\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2bacc8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c3430_1:\n\t"
      "movb 0x4eacc8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c3430_2\n\t"
      "pushl $1\n\t"
      "pushl $0x75f\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2baac8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c3430_2:\n\t"
      "movzwl %%si, %%esi\n\t"
      "movl 0x32eb98(,%%esi,4), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c3430_4\n\t"
      "pushl $1\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c3430_4\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19aa70]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x206, %%ecx\n\t"
      "divl %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LFUN_001c3430_3\n\t"
      "pushl %%esi\n\t"
      "pushl $0x2bac8c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001c3430_3:\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LFUN_001c3430_4:\n\t"
      "pushl %%esi\n\t"
      "pushl $0x2bac54\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c3430_assert), [exitfn] "m"(b1c3430_exitfn), [c1999f0] "m"(b1c3430_c1999f0), [c19a7a0] "m"(b1c3430_c19a7a0), [c19aa70] "m"(b1c3430_c19aa70), [c8f390] "m"(b1c3430_c8f390)
      : "memory");
}
#else
#error "FUN_001c3430: clang naked draft required"
#endif


/* FUN_001c3500 (0x1c3500) — XBE naked draft (batch 258). */
#if defined(__clang__)
static void (*const b1c3500_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c3500_exitfn)(int) = system_exit;
static bool (*const b1c3500_c19a930)(file_ref_t *info) = file_close;
static void (*const b1c3500_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_001c3500(void)
{
  __asm__ volatile(
      "testw %%si, %%si\n\t"
      "je .LFUN_001c3500_1\n\t"
      "pushl $1\n\t"
      "pushl $0x77c\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2bacc8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c3500_1:\n\t"
      "movb 0x4eacc8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c3500_2\n\t"
      "pushl $1\n\t"
      "pushl $0x77e\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2baac8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c3500_2:\n\t"
      "cmpw $9, %%si\n\t"
      "jb .LFUN_001c3500_3\n\t"
      "pushl $1\n\t"
      "pushl $0x77f\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2bad24\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c3500_3:\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19a930]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $4, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_001c3500_4\n\t"
      "movzwl %%si, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2bacf4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001c3500_4:\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c3500_assert), [exitfn] "m"(b1c3500_exitfn), [c19a930] "m"(b1c3500_c19a930), [c8f390] "m"(b1c3500_c8f390)
      : "memory");
}
#else
#error "FUN_001c3500: clang naked draft required"
#endif


/* FUN_001c35a0 (0x1c35a0) — XBE naked draft (batch 274). */
#if defined(__clang__)
static void (*const b1c35a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c35a0_exitfn)(int) = system_exit;
static bool (*const b1c35a0_c19ab50)(file_ref_t *info, int size, void *buffer) = file_read;

__attribute__((naked, noinline))
void FUN_001c35a0(void)
{
  __asm__ volatile(
      "movb 0x4eacc8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c35a0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x793\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2baac8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c35a0_1:\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_001c35a0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x794\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x265878\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c35a0_2:\n\t"
      "pushl %%esi\n\t"
      "pushl $0x206\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19ab50]\n\t"
      "addl $0xc, %%esp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c35a0_assert), [exitfn] "m"(b1c35a0_exitfn), [c19ab50] "m"(b1c35a0_c19ab50)
      : "memory");
}
#else
#error "FUN_001c35a0: clang naked draft required"
#endif


/* FUN_001c3610 (0x1c3610) — XBE naked draft (batch 258). */
#if defined(__clang__)
static void (*const b1c3610_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c3610_exitfn)(int) = system_exit;
static file_ref_t * (*const b1c3610_c1999f0)(file_ref_t *info, const char *directory, bool a4) = file_reference_create_from_path;
static void (*const b1c3610_c19adf0)(void) = file_get_size;

__attribute__((naked, noinline))
void FUN_001c3610(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "testw %%si, %%si\n\t"
      "je .LFUN_001c3610_1\n\t"
      "pushl $1\n\t"
      "pushl $0x860\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2bacc8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c3610_1:\n\t"
      "movb 0x4eacc8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c3610_2\n\t"
      "pushl $1\n\t"
      "pushl $0x862\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2baac8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c3610_2:\n\t"
      "cmpw $9, %%si\n\t"
      "jb .LFUN_001c3610_3\n\t"
      "pushl $1\n\t"
      "pushl $0x863\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2bad24\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c3610_3:\n\t"
      "movzwl %%si, %%eax\n\t"
      "movl 0x32eb98(,%%eax,4), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c3610_4\n\t"
      "leal -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x4eabb0\n\t"
      "call *%[c19adf0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c3610_4\n\t"
      "movl $0xfd08e551, %%eax\n\t"
      "mull -0x4(%%ebp)\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $9, %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c3610_4:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c3610_assert), [exitfn] "m"(b1c3610_exitfn), [c1999f0] "m"(b1c3610_c1999f0), [c19adf0] "m"(b1c3610_c19adf0)
      : "memory");
}
#else
#error "FUN_001c3610: clang naked draft required"
#endif


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
int saved_game_file_find_profile_index_for_directory_path(void *path __attribute__((unused)), int unused __attribute__((unused)))
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


/* FUN_001c3a30 (0x1c3a30) — XBE naked draft (batch 256). */
#if defined(__clang__)
static void (*const b1c3a30_c1c2110)(void) = FUN_001c2110;
static int (*const b1c3a30_c1b9930)(int group_tag, const char *name, ...) = tag_loaded;
static int (*const b1c3a30_c19d420)(int param_1, int param_2) = FUN_0019d420;
static int (*const b1c3a30_c1d9179)(char *str, size_t size, const char *format, ...) = snprintf;
static file_ref_t * (*const b1c3a30_c1999f0)(file_ref_t *info, const char *directory, bool a4) = file_reference_create_from_path;
static bool (*const b1c3a30_c19a640)(file_ref_t *info) = file_exists;
static void * (*const b1c3a30_c8de70)(char *destination, const char *source, size_t size) = csstrncpy;
static wchar_t * (*const b1c3a30_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;
static bool (*const b1c3a30_c19a7a0)(file_ref_t *info, int flags) = file_open;
static bool (*const b1c3a30_c19ab50)(file_ref_t *info, int size, void *buffer) = file_read;
static void (*const b1c3a30_c1c3160)(void) = saved_game_file_generate_checksum;
static int (*const b1c3a30_c8da40)(const void *a, const void *b, int size) = csmemcmp;
static void (*const b1c3a30_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static bool (*const b1c3a30_c19a930)(file_ref_t *info) = file_close;
static void (*const b1c3a30_c1c33b0)(void) = FUN_001c33b0;

__attribute__((naked, noinline))
void FUN_001c3a30(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x630, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1c2110]\n\t"
      "pushl $0x28a4bc\n\t"
      "pushl $0x75737472\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "call *%[c1b9930]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "je .LFUN_001c3a30_10\n\t"
      "testw %%si, %%si\n\t"
      "jle .LFUN_001c3a30_11\n\t"
      ".LFUN_001c3a30_1:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c19d420]\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl %%bx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2bb024\n\t"
      "leal -0x430(%%ebp), %%ecx\n\t"
      "pushl $0xff\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9179]\n\t"
      "pushl $0\n\t"
      "leal -0x430(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x330(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0x24, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c3a30_8\n\t"
      "leal -0x330(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19a640]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c3a30_8\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb $0, -0x224(%%ebp)\n\t"
      "movl $0x81, %%ecx\n\t"
      "leal -0x223(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "pushl $0xff\n\t"
      "leal -0x430(%%ebp), %%edx\n\t"
      ".byte 0xaa\n\t"
      "pushl %%edx\n\t"
      "leal -0x224(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8de70]\n\t"
      "pushl $0x7f\n\t"
      "leal -0x124(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "movb $0, -0x125(%%ebp)\n\t"
      "call *%[c19dc90]\n\t"
      "leal -0x330(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "movw $0, -0x26(%%ebp)\n\t"
      "movw $1, -0x24(%%ebp)\n\t"
      "movb $1, -0x20(%%ebp)\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c3a30_5\n\t"
      "leal -0x630(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x330(%%ebp), %%ecx\n\t"
      "pushl $0x200\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19ab50]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c3a30_3\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x630(%%ebp), %%eax\n\t"
      "pushl $0x68\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c3160]\n\t"
      "pushl $0x14\n\t"
      "leal -0x5c8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8da40]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001c3a30_2\n\t"
      "movb $1, -0x1f(%%ebp)\n\t"
      "jmp .LFUN_001c3a30_4\n\t"
      ".LFUN_001c3a30_2:\n\t"
      "leal -0x224(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2bb000\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_001c3a30_4\n\t"
      ".LFUN_001c3a30_3:\n\t"
      "pushl $0x2bafc4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c3a30_4:\n\t"
      "leal -0x330(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001c3a30_7\n\t"
      "pushl $0x2baf80\n\t"
      "jmp .LFUN_001c3a30_6\n\t"
      ".LFUN_001c3a30_5:\n\t"
      "pushl $0x2baf40\n\t"
      ".LFUN_001c3a30_6:\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c3a30_7:\n\t"
      "leal -0x224(%%ebp), %%esi\n\t"
      "call *%[c1c33b0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c3a30_9\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      ".LFUN_001c3a30_8:\n\t"
      "incl %%ebx\n\t"
      "cmpw -0x8(%%ebp), %%bx\n\t"
      "jl .LFUN_001c3a30_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%bx, %%ax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001c3a30_9:\n\t"
      "leal -0x430(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x2baf10\n\t"
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
      ".LFUN_001c3a30_10:\n\t"
      "pushl $0x2baeb0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c3a30_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%bx, %%ax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1c2110] "m"(b1c3a30_c1c2110), [c1b9930] "m"(b1c3a30_c1b9930), [c19d420] "m"(b1c3a30_c19d420), [c1d9179] "m"(b1c3a30_c1d9179), [c1999f0] "m"(b1c3a30_c1999f0), [c19a640] "m"(b1c3a30_c19a640), [c8de70] "m"(b1c3a30_c8de70), [c19dc90] "m"(b1c3a30_c19dc90), [c19a7a0] "m"(b1c3a30_c19a7a0), [c19ab50] "m"(b1c3a30_c19ab50), [c1c3160] "m"(b1c3a30_c1c3160), [c8da40] "m"(b1c3a30_c8da40), [c8f390] "m"(b1c3a30_c8f390), [c19a930] "m"(b1c3a30_c19a930), [c1c33b0] "m"(b1c3a30_c1c33b0)
      : "memory");
}
#else
#error "FUN_001c3a30: clang naked draft required"
#endif


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


/* saved_game_file_get_display_name (0x1c4600) — XBE naked draft (batch 259). */
#if defined(__clang__)
static void (*const b1c4600_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c4600_exitfn)(int) = system_exit;
static void (*const b1c4600_c1c3e40)(void) = FUN_001c3e40;
static wchar_t * (*const b1c4600_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;
static void (*const b1c4600_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
wchar_t *saved_game_file_get_display_name(int file_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x208, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "movzbl %%ah, %%esi\n\t"
      "sarl $0x10, %%eax\n\t"
      "andl $0xfff, %%eax\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "je .Lsaved_game_file_get_display_name_1\n\t"
      "pushl $1\n\t"
      "pushl $0x12b\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba8c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsaved_game_file_get_display_name_1:\n\t"
      "testl %%esi, %%esi\n\t"
      "movw $0, 0x4eaab0\n\t"
      "jl .Lsaved_game_file_get_display_name_2\n\t"
      "cmpl $9, %%esi\n\t"
      "jge .Lsaved_game_file_get_display_name_2\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .Lsaved_game_file_get_display_name_2\n\t"
      "cmpl $0x64, %%edi\n\t"
      "jge .Lsaved_game_file_get_display_name_2\n\t"
      "leal -0x208(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c1c3e40]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsaved_game_file_get_display_name_3\n\t"
      "pushl $0x7f\n\t"
      "leal -0x108(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x4eaab0\n\t"
      "call *%[c19dc90]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "movw $0, 0x4eabae\n\t"
      "movl $0x4eaab0, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsaved_game_file_get_display_name_2:\n\t"
      "pushl $0x2bb430\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lsaved_game_file_get_display_name_3:\n\t"
      "popl %%edi\n\t"
      "movl $0x4eaab0, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c4600_assert), [exitfn] "m"(b1c4600_exitfn), [c1c3e40] "m"(b1c4600_c1c3e40), [c19dc90] "m"(b1c4600_c19dc90), [c8f390] "m"(b1c4600_c8f390)
      : "memory");
}
#else
#error "saved_game_file_get_display_name: clang naked draft required"
#endif


/* delete_enumerated_saved_game_file (0x1c46c0) — XBE naked draft (batch 255). */
#if defined(__clang__)
static void (*const b1c46c0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b1c46c0_ce98b0)(void) = ui_widget_clear_last_error_index;
static void (*const b1c46c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c46c0_exitfn)(int) = system_exit;
static void (*const b1c46c0_c1c3e40)(void) = FUN_001c3e40;
static char * (*const b1c46c0_c19f3a0)(const wchar_t *unicode, char *ascii, int size) = wide_to_ascii;
static void (*const b1c46c0_c1d3185)(void) = FUN_001d3185;
static void (*const b1c46c0_c1c43f0)(void) = FUN_001c43f0;

__attribute__((naked, noinline))
char delete_enumerated_saved_game_file(int param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x214, %%esp\n\t"
      "movb 0x4eacc7, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "je .Ldelete_enumerated_saved_game_file_1\n\t"
      "pushl $0x2bb590\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[ce98b0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Ldelete_enumerated_saved_game_file_1:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "movzbl %%ah, %%ebx\n\t"
      "sarl $0x10, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "andl $0xf, %%esi\n\t"
      "andl $0xfff, %%edi\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .Ldelete_enumerated_saved_game_file_2\n\t"
      "pushl $1\n\t"
      "pushl $0x1ef\n\t"
      "pushl $0x2ba8e8\n\t"
      "pushl $0x2ba8c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ldelete_enumerated_saved_game_file_2:\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .Ldelete_enumerated_saved_game_file_7\n\t"
      "cmpl $2, %%esi\n\t"
      "jge .Ldelete_enumerated_saved_game_file_7\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jl .Ldelete_enumerated_saved_game_file_7\n\t"
      "cmpl $9, %%ebx\n\t"
      "jge .Ldelete_enumerated_saved_game_file_7\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .Ldelete_enumerated_saved_game_file_7\n\t"
      "cmpl $0x64, %%edi\n\t"
      "jge .Ldelete_enumerated_saved_game_file_7\n\t"
      "leal -0x214(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c1c3e40]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Ldelete_enumerated_saved_game_file_6\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movl %%ecx, -0xb(%%ebp)\n\t"
      "sete %%al\n\t"
      "testb %%al, %%al\n\t"
      "movw %%cx, -0x7(%%ebp)\n\t"
      "movb $0, -0xc(%%ebp)\n\t"
      "movb %%cl, -0x5(%%ebp)\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "je .Ldelete_enumerated_saved_game_file_5\n\t"
      "testl $0x40000000, 0x8(%%ebp)\n\t"
      "jne .Ldelete_enumerated_saved_game_file_3\n\t"
      "movl 0x32eb94(,%%ebx,4), %%ecx\n\t"
      "leal -0x114(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $8\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19f3a0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d3185]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Ldelete_enumerated_saved_game_file_3\n\t"
      "pushl $0x2bb55c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".Ldelete_enumerated_saved_game_file_3:\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c1c43f0]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Ldelete_enumerated_saved_game_file_4\n\t"
      "pushl $0x2bb534\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".Ldelete_enumerated_saved_game_file_4:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .Ldelete_enumerated_saved_game_file_9\n\t"
      "pushl $0x2bb514\n\t"
      "jmp .Ldelete_enumerated_saved_game_file_8\n\t"
      ".Ldelete_enumerated_saved_game_file_5:\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x2bb4f4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "call *%[ce98b0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Ldelete_enumerated_saved_game_file_6:\n\t"
      "pushl $0x2bb4a8\n\t"
      "jmp .Ldelete_enumerated_saved_game_file_8\n\t"
      ".Ldelete_enumerated_saved_game_file_7:\n\t"
      "pushl $0x2bb450\n\t"
      ".Ldelete_enumerated_saved_game_file_8:\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Ldelete_enumerated_saved_game_file_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "call *%[ce98b0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8f390] "m"(b1c46c0_c8f390), [ce98b0] "m"(b1c46c0_ce98b0), [assert] "m"(b1c46c0_assert), [exitfn] "m"(b1c46c0_exitfn), [c1c3e40] "m"(b1c46c0_c1c3e40), [c19f3a0] "m"(b1c46c0_c19f3a0), [c1d3185] "m"(b1c46c0_c1d3185), [c1c43f0] "m"(b1c46c0_c1c43f0)
      : "memory");
}
#else
#error "delete_enumerated_saved_game_file: clang naked draft required"
#endif


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

