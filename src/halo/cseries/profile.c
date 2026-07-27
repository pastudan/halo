#include <stdint.h>
/* Profile timing infrastructure. Uses RDTSC to measure CPU cycles and
 * converts to milliseconds using the stored CPU frequency at 0x3361a0.
 * All timing data is accumulated into global profiling structures. */

/* Read the x86 timestamp counter (RDTSC) into a low/high dword pair.
   Use GCC-style asm for clang (even targeting MSVC) because MSVC-style
   __asm doesn't properly communicate register clobbers to the optimizer. */
#if defined(_MSC_VER) && !defined(__clang__)
#define RDTSC(lo, hi)   \
  do {                  \
    uint32_t _lo, _hi;  \
    __asm { rdtsc }      \
    __asm               \
    {                   \
      mov _lo, eax      \
    }                   \
    __asm { mov _hi, edx } \
    (lo) = _lo;         \
    (hi) = _hi;         \
  } while (0)
#else
#define RDTSC(lo, hi)                     \
  do {                                    \
    uint32_t _lo, _hi;                    \
    asm volatile("rdtsc\n\t"              \
                 "movl %%eax, %0\n\t"     \
                 "movl %%edx, %1"         \
                 : "=rm"(_lo), "=rm"(_hi) \
                 :                        \
                 : "eax", "edx");         \
    (lo) = _lo;                           \
    (hi) = _hi;                           \
  } while (0)
#endif

/* Compute elapsed milliseconds from a 64-bit cycle difference.
 * Formula: (float)(int64_t)cycles * scale / (float)cpu_freq */
static float cycles_to_msec(uint32_t lo, uint32_t hi)
{
  int64_t diff;
  uint32_t *p = (uint32_t *)&diff;
  p[0] = lo;
  p[1] = hi;
  return (float)diff * *(float *)0x254cb8 / (float)*(int64_t *)0x3361a0;
}

/* Enter a profiling section. Records the current timestamp and pushes
 * the section onto the profiling stack. */
void profile_enter_private(void *section)
{
  char *s = (char *)section;
  uint32_t lo, hi;

  ((void (*)(void *))0x8f8e0)(section);

  if (*(int16_t *)(s + 0xa) != -1) {
    display_assert("section->stack_depth==NONE",
                   "c:\\halo\\SOURCE\\cseries\\profile.c", 0x255, 1);
    system_exit(-1);
  }

  *(int16_t *)0x3361a8 += 1;
  *(int16_t *)(s + 0xa) = *(int16_t *)0x3361a8;

  RDTSC(lo, hi);
  *(uint32_t *)(s + 0x10) = lo;
  *(uint32_t *)(s + 0x14) = hi;
  *(int *)(s + 0x5cc) += 1;
}

/* Exit a profiling section. Computes elapsed cycles and accumulates
 * them into the section's 64-bit total. */
void profile_exit_private(void *section)
{
  char *s = (char *)section;

  if (*(uint8_t *)0x3361aa != 0) {
    *(int16_t *)(s + 0xa) = -1;
    return;
  }

  ((void (*)(void *))0x8f8e0)(section);

  if (*(int16_t *)(s + 0xa) != *(int16_t *)0x3361a8) {
    display_assert("section->stack_depth==profile_globals.stack_depth",
                   "c:\\halo\\SOURCE\\cseries\\profile.c", 0x267, 1);
    system_exit(-1);
  }

  *(int16_t *)0x3361a8 -= 1;

  {
    uint32_t lo, hi;
    uint32_t diff_lo, diff_hi;
    uint32_t old_lo;

    RDTSC(lo, hi);
    diff_lo = lo - *(uint32_t *)(s + 0x10);
    diff_hi = hi - *(uint32_t *)(s + 0x14) - (lo < *(uint32_t *)(s + 0x10));

    old_lo = *(uint32_t *)(s + 0x5d0);
    *(uint32_t *)(s + 0x5d0) = old_lo + diff_lo;
    *(uint32_t *)(s + 0x5d4) += diff_hi + (*(uint32_t *)(s + 0x5d0) < old_lo);
  }

  *(int16_t *)(s + 0xa) = -1;
}

/* Start timing a game tick. Increments the tick counter and records
 * the start timestamp in the tick timing array. */
void profile_tick_start(void)
{
  int idx;
  uint32_t lo, hi;

  if (*(uint8_t *)0x449ef0 != 0)
    ((void (*)(void))0x8f6b0)();

  if (*(int16_t *)0x448dd8 < 0x96)
    *(int16_t *)0x448dd8 += 1;

  if (*(int16_t *)0x448dd8 < 1 || *(int16_t *)0x448dd8 > 0x96) {
    display_assert("(profile_globals.current_frame.game_tick_count > 0) && "
                   "(profile_globals.current_frame.game_tick_count <= "
                   "MAXIMUM_GAME_TICKS_PER_FRAME)",
                   "c:\\halo\\SOURCE\\cseries\\profile.c", 0x137, 1);
    system_exit(-1);
  }

  idx = (int)*(int16_t *)0x448dd8;
  RDTSC(lo, hi);
  *(uint32_t *)(0x448de0 + idx * 0x18) = lo;
  *(uint32_t *)(0x448de4 + idx * 0x18) = hi;
}

/* End timing a game tick. Computes elapsed msec and accumulates. */
void profile_tick_end(void)
{
  int idx;
  uint32_t lo, hi, start_lo, start_hi, diff_lo, diff_hi;
  float elapsed;

  if (*(int16_t *)0x448dd8 < 1 || *(int16_t *)0x448dd8 > 0x96) {
    display_assert("(profile_globals.current_frame.game_tick_count > 0) && "
                   "(profile_globals.current_frame.game_tick_count <= "
                   "MAXIMUM_GAME_TICKS_PER_FRAME)",
                   "c:\\halo\\SOURCE\\cseries\\profile.c", 0x140, 1);
    system_exit(-1);
  }

  idx = (int)*(int16_t *)0x448dd8;
  RDTSC(lo, hi);

  start_lo = *(uint32_t *)(0x448de0 + idx * 0x18);
  start_hi = *(uint32_t *)(0x448de4 + idx * 0x18);
  *(uint32_t *)(0x448de8 + idx * 0x18) = lo;
  *(uint32_t *)(0x448dec + idx * 0x18) = hi;

  diff_lo = lo - start_lo;
  diff_hi = hi - start_hi - (lo < start_lo);
  elapsed = cycles_to_msec(diff_lo, diff_hi);

  *(float *)(0x448df0 + idx * 0x18) += elapsed;
  *(float *)(0x448df4 + idx * 0x18) += elapsed;
}

/* Start timing the render phase. Resets window count and records
 * the render start timestamp. */
void profile_render_start(void)
{
  uint32_t lo, hi;
  *(int16_t *)0x448dda = 0;
  RDTSC(lo, hi);
  *(uint32_t *)0x449c68 = lo;
  *(uint32_t *)0x449c6c = hi;
}

/* End timing the render phase. Computes elapsed msec. */
void profile_render_end(void)
{
  uint32_t lo, hi, diff_lo, diff_hi;
  float elapsed;

  RDTSC(lo, hi);
  *(uint32_t *)0x449c70 = lo;
  *(uint32_t *)0x449c74 = hi;

  diff_lo = lo - *(uint32_t *)0x449c68;
  diff_hi = hi - *(uint32_t *)0x449c6c - (lo < *(uint32_t *)0x449c68);
  elapsed = cycles_to_msec(diff_lo, diff_hi);

  *(float *)0x449c78 += elapsed;
  *(float *)0x449c7c += elapsed;
}

/* Start timing a render window. Increments window count, stores the
 * window parameter, and records the start timestamp. */
void profile_render_window_start(char window_param)
{
  int16_t count;
  int idx;
  uint32_t lo, hi;

  count = *(int16_t *)0x448dda;
  if (count < 4) {
    count++;
    *(int16_t *)0x448dda = count;
    *(uint8_t *)(0x448ddb + (int)count) = (uint8_t)window_param;
  }

  if (*(int16_t *)0x448dda < 1 || *(int16_t *)0x448dda > 4) {
    display_assert(
      "(profile_globals.current_frame.window_count > 0) && "
      "(profile_globals.current_frame.window_count <= MAXIMUM_WINDOWS)",
      "c:\\halo\\SOURCE\\cseries\\profile.c", 0x161, 1);
    system_exit(-1);
  }

  idx = (int)*(int16_t *)0x448dda;
  RDTSC(lo, hi);
  *(uint32_t *)(0x449bf0 + idx * 0x18) = lo;
  *(uint32_t *)(0x449bf4 + idx * 0x18) = hi;
}

/* End timing a render window. Computes elapsed msec. */
void profile_render_window_end(void)
{
  int idx;
  uint32_t lo, hi, start_lo, diff_lo, diff_hi;
  float elapsed;

  if (*(int16_t *)0x448dda < 1 || *(int16_t *)0x448dda > 4) {
    display_assert(
      "(profile_globals.current_frame.window_count > 0) && "
      "(profile_globals.current_frame.window_count <= MAXIMUM_WINDOWS)",
      "c:\\halo\\SOURCE\\cseries\\profile.c", 0x16a, 1);
    system_exit(-1);
  }

  idx = (int)*(int16_t *)0x448dda;
  RDTSC(lo, hi);

  start_lo = *(uint32_t *)(0x449bf0 + idx * 0x18);
  *(uint32_t *)(0x449bf8 + idx * 0x18) = lo;
  *(uint32_t *)(0x449bfc + idx * 0x18) = hi;

  diff_lo = lo - start_lo;
  diff_hi = hi - *(uint32_t *)(0x449bf4 + idx * 0x18) - (lo < start_lo);
  elapsed = cycles_to_msec(diff_lo, diff_hi);

  *(float *)(0x449c00 + idx * 0x18) += elapsed;
  *(float *)(0x449c04 + idx * 0x18) += elapsed;
}

/* Snapshot the current TSC into a dedicated low/high global pair at
 * 0x449c98/0x449c9c (used to mark a reference timestamp). */
void profile_texture_start(void)
{
  uint32_t lo, hi;
  RDTSC(lo, hi);
  *(uint32_t *)0x449c98 = lo;
  *(uint32_t *)0x449c9c = hi;
}

/* End a custom profiling section. Computes elapsed msec since the
 * reference timestamp at 0x449c98/0x449c9c (set by profile_texture_start)
 * and accumulates into the two custom accumulators at 0x449ca8/0x449cac. */
void profile_texture_end(void)
{
  uint32_t lo, hi, diff_lo, diff_hi;
  float elapsed;

  RDTSC(lo, hi);
  *(uint32_t *)0x449ca0 = lo;
  *(uint32_t *)0x449ca4 = hi;

  diff_lo = lo - *(uint32_t *)0x449c98;
  diff_hi = hi - *(uint32_t *)0x449c9c - (lo < *(uint32_t *)0x449c98);
  elapsed = cycles_to_msec(diff_lo, diff_hi);

  *(float *)0x449ca8 += elapsed;
  *(float *)0x449cac += elapsed;
}

/* Start a new profiling frame. Clears the current frame data, records
 * the render count and timing state, and timestamps the frame start. */
void profile_frame_start(void)
{
  uint32_t lo, hi;

  if (*(uint8_t *)0x449ef0 == 0)
    ((void (*)(void))0x8f6b0)();

  csmemset((void *)0x448dc8, 0, 0x1128);
  *(int *)(0x448dcc) = *(int *)0x506540;
  *(int *)(0x448dd0) = *(int *)0x325678;
  *(int *)(0x448dd4) = *(int *)0x32567c;
  *(int16_t *)0x448dd8 = 0;

  RDTSC(lo, hi);
  *(uint32_t *)0x448de0 = lo;
  *(uint32_t *)0x448de4 = hi;
}

/* End a profiling frame. Computes total frame time, validates and
 * subtracts child section times, copies frame data to the ring buffer,
 * and conditionally outputs profiling information. */
void profile_frame_end(void)
{
  uint32_t lo, hi, diff_lo, diff_hi;
  float frame_elapsed;
  int16_t i;
  int16_t tick_count;
  int16_t window_count;
  uint32_t ring_idx;

  /* compute total frame time */
  RDTSC(lo, hi);
  *(uint32_t *)0x448de8 = lo;
  *(uint32_t *)0x448dec = hi;

  diff_lo = lo - *(uint32_t *)0x448de0;
  diff_hi = hi - *(uint32_t *)0x448de4 - (lo < *(uint32_t *)0x448de0);
  frame_elapsed = cycles_to_msec(diff_lo, diff_hi);
  *(float *)0x448df0 += frame_elapsed;
  *(float *)0x448df4 += frame_elapsed;

  /* validate tick count and subtract child tick times */
  if (*(int16_t *)0x448dd8 < 0 || *(int16_t *)0x448dd8 > 0x96) {
    display_assert("(profile_globals.current_frame.game_tick_count >= 0) && "
                   "(profile_globals.current_frame.game_tick_count <= "
                   "MAXIMUM_GAME_TICKS_PER_FRAME)",
                   "c:\\halo\\SOURCE\\cseries\\profile.c", 0x1c0, 1);
    system_exit(-1);
  }

  tick_count = *(int16_t *)0x448dd8;
  for (i = 0; i < tick_count; i++) {
    float child = *(float *)(0x448e08 + (int)i * 0x18);
    if (*(float *)0x448df4 < child) {
      display_assert(
        "parent_timesection->self_msec >= child_timesection->elapsed_msec",
        "c:\\halo\\SOURCE\\cseries\\profile.c", 0x1b2, 1);
      system_exit(-1);
      tick_count = *(int16_t *)0x448dd8;
    }
    *(float *)0x448df4 -= child;
  }

  /* validate window count */
  if (*(int16_t *)0x448dda < 0 || *(int16_t *)0x448dda > 4) {
    display_assert(
      "(profile_globals.current_frame.window_count >= 0) && "
      "(profile_globals.current_frame.window_count <= MAXIMUM_WINDOWS)",
      "c:\\halo\\SOURCE\\cseries\\profile.c", 0x1c6, 1);
    system_exit(-1);
  }

  /* subtract render time from frame self_msec */
  if (*(float *)0x448df4 < *(float *)0x449c78) {
    display_assert(
      "parent_timesection->self_msec >= child_timesection->elapsed_msec",
      "c:\\halo\\SOURCE\\cseries\\profile.c", 0x1b2, 1);
    system_exit(-1);
  }
  *(float *)0x448df4 -= *(float *)0x449c78;

  /* subtract window child times from render self_msec */
  window_count = *(int16_t *)0x448dda;
  for (i = 0; i < window_count; i++) {
    float child = *(float *)(0x449c18 + (int)i * 0x18);
    if (*(float *)0x449c7c < child) {
      display_assert(
        "parent_timesection->self_msec >= child_timesection->elapsed_msec",
        "c:\\halo\\SOURCE\\cseries\\profile.c", 0x1b2, 1);
      system_exit(-1);
    }
    *(float *)0x449c7c -= child;
  }

  /* subtract custom profile time */
  if (*(float *)0x448df4 < *(float *)0x449cc0) {
    display_assert(
      "parent_timesection->self_msec >= child_timesection->elapsed_msec",
      "c:\\halo\\SOURCE\\cseries\\profile.c", 0x1b2, 1);
    system_exit(-1);
  }
  *(float *)0x448df4 -= *(float *)0x449cc0;

  /* copy current frame data to ring buffer */
  qmemcpy((void *)(0x3365c8 + (int)*(int16_t *)0x3365c4 * 0x1128),
          (void *)0x448dc8, 0x1128);

  ring_idx = (uint32_t)((int)*(int16_t *)0x3365c4 + 1);
  if (*(int16_t *)0x3365c2 <= (int16_t)ring_idx)
    *(int16_t *)0x3365c2 = (int16_t)ring_idx;

  /* wrap ring index to 0-255 */
  ring_idx &= 0xff;
  *(int16_t *)0x3365c4 = (int16_t)ring_idx;

  /* handle profile output */
  if (*(uint8_t *)0x449cd4 == 0) {
    *(int16_t *)0x3365bc += 1;
    if (*(uint8_t *)0x449ef3 == 0)
      goto check_output;
    if (*(uint8_t *)0x449ef2 != 0)
      goto do_output;
    if (*(int16_t *)0x3365bc > 3 && *(uint8_t *)0x3365c0 != 0) {
      if (*(void **)0x3365b4 != 0) {
        ((void (*)(void *, const void *))0x1da685)(*(void **)0x3365b4, L"\r\n");
        ((void (*)(void *))0x1d8f31)(*(void **)0x3365b4);
      }
      *(uint8_t *)0x3365c0 = 0;
      goto check_output;
    }
  } else {
    *(int16_t *)0x3365bc = 0;
  check_output:
    if (*(uint8_t *)0x449ef2 != 0)
      goto do_output;
  }
  if (*(uint8_t *)0x449ef3 == 0)
    return;
  if (*(int16_t *)0x3365bc > 3)
    return;

do_output: {
  uint32_t idx = ((int)*(int16_t *)0x3365c4 + 0xfd) & 0xff;
  do {
    if ((int16_t)idx < *(int16_t *)0x3365c2)
      ((void (*)(void))0x906d0)();
    idx = ((int)(int16_t)idx + 1) & 0xff;
  } while ((int16_t)idx != *(int16_t *)0x3365c4);
}
}
/* symbol_table_dispose (0x92090) — readable C lift. */
void symbol_table_dispose(int32_t *symtab)
{
  extern char DAT_00268b04[];
  extern char DAT_00268b14[];
  if (!symtab) {
    display_assert(DAT_00268b04, DAT_00268b14, 0x225, 1);
    system_exit(-1);
  }
  if (symtab[1])
    debug_free((void *)symtab[1], DAT_00268b14, 0x227);
  if (symtab[2])
    debug_free((void *)symtab[2], DAT_00268b14, 0x228);
  symtab[0] = 0;
  symtab[1] = 0;
  symtab[2] = 0;
}


/* --- profile.obj batch drafts (2026-07-26) --- */

/* profile_seconds_elapsed (0x8f870) — readable C lift. */
void profile_seconds_elapsed(int v)
{
  *(int *)0x449cc8 = v;
}

/* profile_lapsed_msec (0x8f8c0) — readable C lift. */
void profile_lapsed_msec(int value)
{
  *(int *)0x449cd0 = value;
  *(char *)0x449cd4 = value > 0;
}

/* find_profile_section (0x8f8e0) — XBE naked draft (batch 252). */
#if defined(__clang__)
static void (*const b8f8e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b8f8e0_exitfn)(int) = system_exit;
static void *(*const b8f8e0_memset)(void *, int, unsigned int) = csmemset;

__attribute__((naked, noinline))
void find_profile_section(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .Lfind_profile_section_1\n\t"
      "pushl $1\n\t"
      "pushl $0x22f\n\t"
      "pushl $0x2683fc\n\t"
      "pushl $0x2684a4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lfind_profile_section_1:\n\t"
      "cmpb %%bl, 0x8(%%esi)\n\t"
      "jne .Lfind_profile_section_2\n\t"
      "pushl $1\n\t"
      "pushl $0x230\n\t"
      "pushl $0x2683fc\n\t"
      "pushl $0x268494\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lfind_profile_section_2:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lfind_profile_section_4\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jl .Lfind_profile_section_3\n\t"
      "movswl 0x3361b0, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .Lfind_profile_section_3\n\t"
      "cmpl %%esi, 0x3361b4(,%%eax,4)\n\t"
      "je .Lfind_profile_section_6\n\t"
      ".Lfind_profile_section_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x236\n\t"
      "pushl $0x2683fc\n\t"
      "pushl $0x268458\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lfind_profile_section_4:\n\t"
      "cmpw $0x100, 0x3361b0\n\t"
      "jl .Lfind_profile_section_5\n\t"
      "pushl $1\n\t"
      "pushl $0x23a\n\t"
      "pushl $0x2683fc\n\t"
      "pushl $0x268420\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lfind_profile_section_5:\n\t"
      "movswl 0x3361b0, %%edx\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "incw 0x3361b0\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "pushl $0x3c0\n\t"
      "leal 0x208(%%esi), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "movl %%esi, 0x3361b4(,%%eax,4)\n\t"
      "call *%[memset]\n\t"
      "pushl $0x1e0\n\t"
      "leal 0x28(%%esi), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "addl $0x18, %%esp\n\t"
      "movl %%ebx, 0x18(%%esi)\n\t"
      "movl %%ebx, 0x20(%%esi)\n\t"
      "movl %%ebx, 0x24(%%esi)\n\t"
      "movw $0xffff, 0xa(%%esi)\n\t"
      "movl %%ebx, 0x5c8(%%esi)\n\t"
      "movl %%ebx, 0x5d0(%%esi)\n\t"
      "movl %%ebx, 0x5d4(%%esi)\n\t"
      "movl %%ebx, 0x5cc(%%esi)\n\t"
      "movl %%ebx, 0x5e0(%%esi)\n\t"
      "movl %%ebx, 0x5e4(%%esi)\n\t"
      "movl %%ebx, 0x5d8(%%esi)\n\t"
      "movl %%ebx, 0x5f0(%%esi)\n\t"
      "movl %%ebx, 0x5f4(%%esi)\n\t"
      "movl %%ebx, 0x5e8(%%esi)\n\t"
      ".Lfind_profile_section_6:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b8f8e0_assert), [exitfn] "m"(b8f8e0_exitfn), [memset] "m"(b8f8e0_memset)
      : "memory");
}
#else
#error "find_profile_section: clang naked draft required"
#endif


/* FUN_0008fb60 (0x8fb60) — XBE naked draft (batch 265). */
#if defined(__clang__)
static char * (*const b8fb60_c8dff0)(char *destination, const char *source) = csstrcpy;
static int (*const b8fb60_c8df60)(const char *s1) = csstrlen;
static int (*const b8fb60_c1d9179)(char *str, size_t size, const char *format, ...) = snprintf;
static __int16 (*const b8fb60_cba4b0)(void) = local_player_count;
static char * (*const b8fb60_c8dd30)(char *destination, const char *source, size_t max_size) = csstrcat;

__attribute__((naked, noinline))
void FUN_0008fb60(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl $0x25386f\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c8dff0]\n\t"
      "flds 0x28(%%ebx)\n\t"
      "movl 0xc(%%ebx), %%eax\n\t"
      "fstpl (%%esp)\n\t"
      "movl 0x8(%%ebx), %%ecx\n\t"
      "movl 0x4(%%ebx), %%edx\n\t"
      "movswl 0x8(%%ebp), %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x268608\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "movl %%edi, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "movw 0xf04(%%ebx), %%ax\n\t"
      "addl $0x20, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_0008fb60_2\n\t"
      "movb 0x31fa96, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "movswl %%ax, %%edx\n\t"
      "pushl %%edx\n\t"
      "je .LFUN_0008fb60_1\n\t"
      "pushl $0x2685fc\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "movl %%edi, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_0008fb60_7\n\t"
      ".LFUN_0008fb60_1:\n\t"
      "pushl $0x2685f0\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "movl %%edi, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_0008fb60_7\n\t"
      ".LFUN_0008fb60_2:\n\t"
      "movl 0xf08(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_0008fb60_4\n\t"
      "movb 0x31fa96, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "pushl %%eax\n\t"
      "je .LFUN_0008fb60_3\n\t"
      "pushl $0x2685e4\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "movl %%edi, %%edx\n\t"
      "addl $4, %%esp\n\t"
      "subl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_0008fb60_7\n\t"
      ".LFUN_0008fb60_3:\n\t"
      "pushl $0x2685d8\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "movl %%edi, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_0008fb60_7\n\t"
      ".LFUN_0008fb60_4:\n\t"
      "movb 0xf0c(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0008fb60_5\n\t"
      "pushl $0x2685cc\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%edi, %%edx\n\t"
      "subl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "jmp .LFUN_0008fb60_6\n\t"
      ".LFUN_0008fb60_5:\n\t"
      "pushl $0x2685c0\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%edi, %%ecx\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      ".LFUN_0008fb60_6:\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0008fb60_7:\n\t"
      "flds 0xefc(%%ebx)\n\t"
      "subl $8, %%esp\n\t"
      "fcomps 0x2533c0\n\t"
      "flds 0xefc(%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0008fb60_8\n\t"
      "pushl $0x2685b4\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%edi, %%edx\n\t"
      "subl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "jmp .LFUN_0008fb60_9\n\t"
      ".LFUN_0008fb60_8:\n\t"
      "pushl $0x2685a8\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%edi, %%ecx\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      ".LFUN_0008fb60_9:\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x10(%%ebx), %%ax\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw $8, %%ax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jg .LFUN_0008fb60_10\n\t"
      "movl $8, -0xc(%%ebp)\n\t"
      ".LFUN_0008fb60_10:\n\t"
      "movswl %%ax, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x26859c\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "movl %%edi, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl $0x268598\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "movl %%edi, %%edx\n\t"
      "addl $4, %%esp\n\t"
      "subl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "movl $0, 0x8(%%ebp)\n\t"
      "jle .LFUN_0008fb60_17\n\t"
      "movswl %%ax, %%eax\n\t"
      "leal -0x1(%%eax), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal 0x44(%%ebx), %%edx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_0008fb60_12\n\t"
      ".LFUN_0008fb60_11:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      ".LFUN_0008fb60_12:\n\t"
      "movw 0x8(%%ebp), %%dx\n\t"
      "cmpw 0x10(%%ebx), %%dx\n\t"
      "jge .LFUN_0008fb60_14\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl $0x25b06c, %%eax\n\t"
      "jl .LFUN_0008fb60_13\n\t"
      "movl $0x25386f, %%eax\n\t"
      ".LFUN_0008fb60_13:\n\t"
      "pushl %%eax\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "flds (%%eax)\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x268590\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "movl %%edi, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x18, %%esp\n\t"
      "jmp .LFUN_0008fb60_16\n\t"
      ".LFUN_0008fb60_14:\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl $0x25b06c, %%eax\n\t"
      "jl .LFUN_0008fb60_15\n\t"
      "movl $0x25386f, %%eax\n\t"
      ".LFUN_0008fb60_15:\n\t"
      "pushl %%eax\n\t"
      "pushl $0x268584\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "movl %%edi, %%edx\n\t"
      "addl $4, %%esp\n\t"
      "subl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0008fb60_16:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "incl %%eax\n\t"
      "incl %%ecx\n\t"
      "addl $0x18, %%edx\n\t"
      "cmpw -0xc(%%ebp), %%ax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jl .LFUN_0008fb60_11\n\t"
      ".LFUN_0008fb60_17:\n\t"
      "pushl $0x268580\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "movl %%edi, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "movswl 0x12(%%ebx), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "call *%[cba4b0]\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "incl %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jg .LFUN_0008fb60_18\n\t"
      "call *%[cba4b0]\n\t"
      "incl %%eax\n\t"
      ".LFUN_0008fb60_18:\n\t"
      "flds 0xeb0(%%ebx)\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x268570\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "call *%[c8df60]\n\t"
      "movl %%edi, %%edx\n\t"
      "addl $4, %%esp\n\t"
      "subl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl $0x268598\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "movl %%edi, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "movl $0, 0x8(%%ebp)\n\t"
      "jle .LFUN_0008fb60_26\n\t"
      "movswl %%ax, %%eax\n\t"
      "leal 0x14(%%ebx), %%edx\n\t"
      "leal -0x1(%%eax), %%ecx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal 0xe54(%%ebx), %%edx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jmp .LFUN_0008fb60_20\n\t"
      ".LFUN_0008fb60_19:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      ".LFUN_0008fb60_20:\n\t"
      "movw 0x8(%%ebp), %%dx\n\t"
      "cmpw 0x12(%%ebx), %%dx\n\t"
      "jge .LFUN_0008fb60_23\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl $0x25b06c, %%ecx\n\t"
      "jl .LFUN_0008fb60_21\n\t"
      "movl $0x25386f, %%ecx\n\t"
      ".LFUN_0008fb60_21:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpb $0, (%%eax)\n\t"
      "movl $0x26856c, %%eax\n\t"
      "jne .LFUN_0008fb60_22\n\t"
      "movl $0x268568, %%eax\n\t"
      ".LFUN_0008fb60_22:\n\t"
      "pushl %%ecx\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl $0x26855c\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "movl %%edi, %%edx\n\t"
      "addl $4, %%esp\n\t"
      "subl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x1c, %%esp\n\t"
      "jmp .LFUN_0008fb60_25\n\t"
      ".LFUN_0008fb60_23:\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl $0x25b06c, %%eax\n\t"
      "jl .LFUN_0008fb60_24\n\t"
      "movl $0x25386f, %%eax\n\t"
      ".LFUN_0008fb60_24:\n\t"
      "pushl %%eax\n\t"
      "pushl $0x268550\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "movl %%edi, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0008fb60_25:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "incl %%eax\n\t"
      "incl %%edx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "incl %%ecx\n\t"
      "addl $0x18, %%edx\n\t"
      "cmpw -0x10(%%ebp), %%ax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jl .LFUN_0008fb60_19\n\t"
      ".LFUN_0008fb60_26:\n\t"
      "pushl $0x268580\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "movl %%edi, %%edx\n\t"
      "addl $4, %%esp\n\t"
      "subl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "flds 0xecc(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0xc, %%esp\n\t"
      "flds 0xecc(%%ebx)\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0008fb60_27\n\t"
      "pushl $0x268544\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%edi, %%ecx\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "jmp .LFUN_0008fb60_28\n\t"
      ".LFUN_0008fb60_27:\n\t"
      "pushl $0x268534\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%edi, %%edx\n\t"
      "subl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      ".LFUN_0008fb60_28:\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "flds 0xee4(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x14, %%esp\n\t"
      "flds 0xee4(%%ebx)\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0008fb60_29\n\t"
      "pushl $0x268528\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%edi, %%ecx\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "jmp .LFUN_0008fb60_30\n\t"
      ".LFUN_0008fb60_29:\n\t"
      "pushl $0x26851c\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%edi, %%edx\n\t"
      "subl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      ".LFUN_0008fb60_30:\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "flds 0xeb4(%%ebx)\n\t"
      "addl $0x14, %%esp\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x26850c\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "movl %%edi, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "flds 0x2c(%%ebx)\n\t"
      "addl $0xc, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2684fc\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "movl %%edi, %%edx\n\t"
      "addl $4, %%esp\n\t"
      "subl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl $0x18, %%esp\n\t"
      "subl %%eax, %%edi\n\t"
      "pushl %%edi\n\t"
      "addl $0xf0d, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dd30]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8dff0] "m"(b8fb60_c8dff0), [c8df60] "m"(b8fb60_c8df60), [c1d9179] "m"(b8fb60_c1d9179), [cba4b0] "m"(b8fb60_cba4b0), [c8dd30] "m"(b8fb60_c8dd30)
      : "memory");
}
#else
#error "FUN_0008fb60: clang naked draft required"
#endif


/* FUN_00090170 (0x90170) — readable C lift. */
void FUN_00090170(int *out, int a, int b)
{
  out[0] = a;
  out[1] = b;
}

/* FUN_00090180 (0x90180) — XBE naked draft (batch 260). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_00090180(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "movl (%%eax), %%esi\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "subl %%esi, %%ecx\n\t"
      "movl 0x4(%%eax), %%esi\n\t"
      "movl %%edx, 0xc(%%eax)\n\t"
      "sbbl %%esi, %%edx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "popl %%esi\n\t"
      "fmuls 0x254cb8\n\t"
      "fildl 0x3361a0\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fld %%st(0)\n\t"
      "fadds 0x10(%%eax)\n\t"
      "fstps 0x10(%%eax)\n\t"
      "fadds 0x14(%%eax)\n\t"
      "fstps 0x14(%%eax)\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_00090180: clang naked draft required"
#endif


/* compare_profile_sections (0x901d0) — XBE naked draft (batch 249). */
#if defined(__clang__)
static void (*const b901d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b901d0_exitfn)(int) = system_exit;
static int (*const b901d0_c8dcb0)(const char *s1, const char *s2) = csstrcmp;

__attribute__((naked, noinline))
void compare_profile_sections(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%eax\n\t"
      "movb 0x8(%%eax), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "je .Lcompare_profile_sections_1\n\t"
      "movl (%%ecx), %%esi\n\t"
      "movb 0x8(%%esi), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lcompare_profile_sections_4\n\t"
      ".Lcompare_profile_sections_1:\n\t"
      "movl (%%ecx), %%ecx\n\t"
      "movb 0x8(%%ecx), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lcompare_profile_sections_2\n\t"
      "testb %%dl, %%dl\n\t"
      "je .Lcompare_profile_sections_13\n\t"
      ".Lcompare_profile_sections_2:\n\t"
      "movswl 0x3365b8, %%edx\n\t"
      "subl $0, %%edx\n\t"
      "je .Lcompare_profile_sections_14\n\t"
      "decl %%edx\n\t"
      "je .Lcompare_profile_sections_7\n\t"
      "decl %%edx\n\t"
      "je .Lcompare_profile_sections_3\n\t"
      "pushl $1\n\t"
      "pushl $0x34c\n\t"
      "pushl $0x2683fc\n\t"
      "pushl $0x255ee8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcompare_profile_sections_3:\n\t"
      "movl 0x20(%%eax), %%edx\n\t"
      "movl 0x20(%%ecx), %%esi\n\t"
      "movl 0x24(%%eax), %%eax\n\t"
      "movl 0x24(%%ecx), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lcompare_profile_sections_13\n\t"
      "jg .Lcompare_profile_sections_4\n\t"
      "cmpl %%esi, %%edx\n\t"
      "jbe .Lcompare_profile_sections_5\n\t"
      ".Lcompare_profile_sections_4:\n\t"
      "popl %%esi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcompare_profile_sections_5:\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jg .Lcompare_profile_sections_6\n\t"
      "jl .Lcompare_profile_sections_13\n\t"
      "cmpl %%esi, %%edx\n\t"
      "jb .Lcompare_profile_sections_13\n\t"
      ".Lcompare_profile_sections_6:\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcompare_profile_sections_7:\n\t"
      "movl 0x5c8(%%eax), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "jne .Lcompare_profile_sections_8\n\t"
      "fldl 0x2602c0\n\t"
      "jmp .Lcompare_profile_sections_9\n\t"
      ".Lcompare_profile_sections_8:\n\t"
      "fildl 0x5e0(%%eax)\n\t"
      "fidivl 0x8(%%ebp)\n\t"
      ".Lcompare_profile_sections_9:\n\t"
      "movl 0x5c8(%%ecx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "jne .Lcompare_profile_sections_10\n\t"
      "fldl 0x2602c0\n\t"
      "jmp .Lcompare_profile_sections_11\n\t"
      ".Lcompare_profile_sections_10:\n\t"
      "fildl 0x5e0(%%ecx)\n\t"
      "fidivl 0x8(%%ebp)\n\t"
      ".Lcompare_profile_sections_11:\n\t"
      "fld %%st(1)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lcompare_profile_sections_12\n\t"
      "fstp %%st(0)\n\t"
      "popl %%esi\n\t"
      "fstp %%st(0)\n\t"
      "movl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcompare_profile_sections_12:\n\t"
      "fxch %%st(1)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lcompare_profile_sections_6\n\t"
      ".Lcompare_profile_sections_13:\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcompare_profile_sections_14:\n\t"
      "movl (%%ecx), %%ecx\n\t"
      "movl (%%eax), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8dcb0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b901d0_assert), [exitfn] "m"(b901d0_exitfn), [c8dcb0] "m"(b901d0_c8dcb0)
      : "memory");
}
#else
#error "compare_profile_sections: clang naked draft required"
#endif


/* profile_dump (0x902f0) — XBE naked draft (batch 243). */
#if defined(__clang__)
static void (*const b902f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b902f0_exitfn)(int) = system_exit;
static void * (*const b902f0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void __cdecl (*const b902f0_c1d9260)(void *base, size_t nmemb, size_t size, int (__cdecl *compar)(const void *, const void *)) = qsort;
static int (*const b902f0_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static char * (*const b902f0_c1d9690)(const char *haystack, const char *needle) = crt_strstr;
static int (*const b902f0_c8dcb0)(const char *s1, const char *s2) = csstrcmp;
static void (*const b902f0_ftol)(void) = (void (*)(void))FUN_001d9068;
static int (*const b902f0_c8df60)(const char *s1) = csstrlen;

__attribute__((naked, noinline))
void profile_dump(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x430, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movw 0xc(%%ebp), %%bx\n\t"
      "testw %%bx, %%bx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "jl .Lprofile_dump_1\n\t"
      "cmpw $3, %%bx\n\t"
      "jl .Lprofile_dump_2\n\t"
      ".Lprofile_dump_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x36f\n\t"
      "pushl $0x2683fc\n\t"
      "pushl $0x26868c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lprofile_dump_2:\n\t"
      "movw 0x10(%%ebp), %%di\n\t"
      "testw %%di, %%di\n\t"
      "jl .Lprofile_dump_3\n\t"
      "cmpw $2, %%di\n\t"
      "jl .Lprofile_dump_4\n\t"
      ".Lprofile_dump_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x370\n\t"
      "pushl $0x2683fc\n\t"
      "pushl $0x268648\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lprofile_dump_4:\n\t"
      "cmpw $0, 0x14(%%ebp)\n\t"
      "jg .Lprofile_dump_5\n\t"
      "pushl $1\n\t"
      "pushl $0x371\n\t"
      "pushl $0x2683fc\n\t"
      "pushl $0x268630\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lprofile_dump_5:\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lprofile_dump_6\n\t"
      "pushl $1\n\t"
      "pushl $0x372\n\t"
      "pushl $0x2683fc\n\t"
      "pushl $0x267900\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lprofile_dump_6:\n\t"
      "movswl 0x3361b0, %%eax\n\t"
      "shll $2, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x430(%%ebp), %%ecx\n\t"
      "pushl $0x3361b4\n\t"
      "pushl %%ecx\n\t"
      "movw %%bx, 0x3365b8\n\t"
      "call *%[c8e0b0]\n\t"
      "movswl 0x3361b0, %%edx\n\t"
      "pushl $0x901d0\n\t"
      "pushl $4\n\t"
      "pushl %%edx\n\t"
      "leal -0x430(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9260]\n\t"
      "addl $0x1c, %%esp\n\t"
      "cmpw $0, 0x3361b0\n\t"
      "je .Lprofile_dump_16\n\t"
      "movl -0x430(%%ebp), %%ecx\n\t"
      "movb 0x8(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprofile_dump_16\n\t"
      "movswl %%di, %%eax\n\t"
      "movl 0x2ee770(,%%eax,4), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "call *%[c1d90f0]\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%bx, 0x3361b0\n\t"
      "jle .Lprofile_dump_16\n\t"
      "jmp .Lprofile_dump_7\n\t"
      "leal (%%esp), %%esp\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lprofile_dump_7:\n\t"
      "movw 0x14(%%ebp), %%ax\n\t"
      "cmpw %%ax, -0x18(%%ebp)\n\t"
      "jge .Lprofile_dump_16\n\t"
      "movswl %%bx, %%esi\n\t"
      "movl -0x430(%%ebp,%%esi,4), %%edx\n\t"
      "movb 0x8(%%edx), %%al\n\t"
      "xorl %%edi, %%edi\n\t"
      "testb %%al, %%al\n\t"
      "leal -0x430(%%ebp,%%esi,4), %%esi\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "movl %%edi, 0x10(%%ebp)\n\t"
      "movl %%edi, -0x1c(%%ebp)\n\t"
      "movl %%edi, -0x14(%%ebp)\n\t"
      "je .Lprofile_dump_15\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lprofile_dump_9\n\t"
      "movl (%%edx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lprofile_dump_15\n\t"
      ".Lprofile_dump_8:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      ".Lprofile_dump_9:\n\t"
      "movl (%%esi), %%eax\n\t"
      "fildl 0x5e0(%%eax)\n\t"
      "movl 0x5d8(%%eax), %%ecx\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "fstpl -0x30(%%ebp)\n\t"
      "addl %%ecx, %%esi\n\t"
      "fildl 0x3361a0\n\t"
      "movl 0x5c8(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "fldl -0x30(%%ebp)\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fildl -0x24(%%ebp)\n\t"
      "fidivl -0x20(%%ebp)\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jne .Lprofile_dump_10\n\t"
      "fldl 0x2602c0\n\t"
      "jmp .Lprofile_dump_11\n\t"
      ".Lprofile_dump_10:\n\t"
      "fildl -0x20(%%ebp)\n\t"
      "fdivrl -0x30(%%ebp)\n\t"
      ".Lprofile_dump_11:\n\t"
      "fmull 0x268628\n\t"
      "movl 0x5e8(%%eax), %%ecx\n\t"
      "movl -0x1c(%%ebp), %%esi\n\t"
      "addl %%ecx, %%edi\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "movl 0x5cc(%%eax), %%ecx\n\t"
      "addl %%ecx, %%esi\n\t"
      "incl %%ebx\n\t"
      "cmpw 0x3361b0, %%bx\n\t"
      "movl %%esi, -0x1c(%%ebp)\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fildl 0x5f0(%%eax)\n\t"
      "fmull 0x268628\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fadds 0x10(%%ebp)\n\t"
      "fstps 0x10(%%ebp)\n\t"
      "fildl 0x5d0(%%eax)\n\t"
      "fmull 0x268628\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "jge .Lprofile_dump_12\n\t"
      "movl (%%edx), %%edx\n\t"
      "movswl %%bx, %%esi\n\t"
      "movl -0x430(%%ebp,%%esi,4), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal -0x430(%%ebp,%%esi,4), %%esi\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8dcb0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lprofile_dump_8\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      ".Lprofile_dump_12:\n\t"
      "movl -0x28(%%ebp), %%esi\n\t"
      "movl %%esi, %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .Lprofile_dump_13\n\t"
      "decl %%eax\n\t"
      "jne .Lprofile_dump_14\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "flds -0x8(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%edi\n\t"
      "flds 0x10(%%ebp)\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fadds 0x253398\n\t"
      "call *%[ftol]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%eax\n\t"
      "flds -0x14(%%ebp)\n\t"
      "movl 0x2ee778(,%%esi,4), %%eax\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x3c, %%esp\n\t"
      "jmp .Lprofile_dump_14\n\t"
      ".Lprofile_dump_13:\n\t"
      "flds 0x10(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl (%%edx), %%edx\n\t"
      "movl 0x2ee778(,%%esi,4), %%eax\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%edi\n\t"
      "flds -0xc(%%ebp)\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x34, %%esp\n\t"
      ".Lprofile_dump_14:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "decl %%ebx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      ".Lprofile_dump_15:\n\t"
      "incl %%ebx\n\t"
      "cmpw 0x3361b0, %%bx\n\t"
      "jl .Lprofile_dump_7\n\t"
      ".Lprofile_dump_16:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b902f0_assert), [exitfn] "m"(b902f0_exitfn), [c8e0b0] "m"(b902f0_c8e0b0), [c1d9260] "m"(b902f0_c1d9260), [c1d90f0] "m"(b902f0_c1d90f0), [c1d9690] "m"(b902f0_c1d9690), [c8dcb0] "m"(b902f0_c8dcb0), [ftol] "m"(b902f0_ftol), [c8df60] "m"(b902f0_c8df60)
      : "memory");
}
#else
#error "profile_dump: clang naked draft required"
#endif


/* profile_dump_to_file (0x90650) — XBE naked draft (batch 280). */
#if defined(__clang__)
static void (*const b90650_chkstk)(void) = (void (*)(void))FUN_001d90e0;
static int (*const b90650_c8df60)(const char *s1) = csstrlen;
static void * (*const b90650_c1d9e59)(const char *filename, const char *mode) = crt_fopen;
static void (*const b90650_c902f0)(void) = (void (*)(void))profile_dump;
static int (*const b90650_c1d98ad)(void *stream, const char *format, ...) = crt_fprintf;
static int (*const b90650_c1d9dac)(void *stream) = crt_fclose;

__attribute__((naked, noinline))
void profile_dump_to_file(int a0 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x2000, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "je .Lprofile_dump_to_file_1\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8df60]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lprofile_dump_to_file_1\n\t"
      "movl $1, %%edi\n\t"
      "jmp .Lprofile_dump_to_file_2\n\t"
      ".Lprofile_dump_to_file_1:\n\t"
      "xorl %%edi, %%edi\n\t"
      ".Lprofile_dump_to_file_2:\n\t"
      "pushl $0x267f84\n\t"
      "pushl $0x2686cc\n\t"
      "call *%[c1d9e59]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lprofile_dump_to_file_3\n\t"
      "leal -0x2000(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x100\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c902f0]\n\t"
      "leal -0x2000(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2686c4\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x20, %%esp\n\t"
      ".Lprofile_dump_to_file_3:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9dac]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(b90650_chkstk), [c8df60] "m"(b90650_c8df60), [c1d9e59] "m"(b90650_c1d9e59), [c902f0] "m"(b90650_c902f0), [c1d98ad] "m"(b90650_c1d98ad), [c1d9dac] "m"(b90650_c1d9dac)
      : "memory");
}
#else
#error "profile_dump_to_file: clang naked draft required"
#endif


/* FUN_000906d0 (0x906d0) — XBE naked draft (batch 277). */
#if defined(__clang__)
static void * (*const b906d0_c1d9e59)(const char *filename, const char *mode) = crt_fopen;
static void (*const b906d0_c8fb60)(void) = (void (*)(void))FUN_0008fb60;
static int (*const b906d0_c1d98ad)(void *stream, const char *format, ...) = crt_fprintf;

__attribute__((naked, noinline))
void FUN_000906d0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x200, %%esp\n\t"
      "movl 0x3365b4, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000906d0_1\n\t"
      "pushl $0x2686f0\n\t"
      "pushl $0x2686dc\n\t"
      "call *%[c1d9e59]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x3365b4\n\t"
      "je .LFUN_000906d0_2\n\t"
      ".LFUN_000906d0_1:\n\t"
      "cmpb $0, (%%edi)\n\t"
      "jne .LFUN_000906d0_2\n\t"
      "pushl %%esi\n\t"
      "pushl $0x200\n\t"
      "leal -0x200(%%ebp), %%esi\n\t"
      "movl %%edi, %%eax\n\t"
      "movb $1, (%%edi)\n\t"
      "call *%[c8fb60]\n\t"
      "movl 0x3365b4, %%ecx\n\t"
      "leal -0x200(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2686c4\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d98ad]\n\t"
      "addl $0x10, %%esp\n\t"
      "movb $1, (%%edi)\n\t"
      "popl %%esi\n\t"
      ".LFUN_000906d0_2:\n\t"
      "movb $1, 0x3365c0\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d9e59] "m"(b906d0_c1d9e59), [c8fb60] "m"(b906d0_c8fb60), [c1d98ad] "m"(b906d0_c1d98ad)
      : "memory");
}
#else
#error "FUN_000906d0: clang naked draft required"
#endif


/* FUN_000907c0 (0x907c0) — XBE naked draft (batch 255). */
#if defined(__clang__)
static int (*const b907c0_c8dcb0)(const char *s1, const char *s2) = csstrcmp;
static char * (*const b907c0_c1d9690)(const char *haystack, const char *needle) = crt_strstr;

__attribute__((naked, noinline))
void FUN_000907c0(int a0)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x2686f4\n\t"
      "pushl %%edi\n\t"
      "call *%[c8dcb0]\n\t"
      "movb (%%edi), %%dl\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "negl %%ebx\n\t"
      "sbbb %%bl, %%bl\n\t"
      "incb %%bl\n\t"
      "cmpb $0x5f, %%dl\n\t"
      "sete -0x1(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw %%ax, 0x3361b0\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jle .LFUN_000907c0_6\n\t"
      "pushl %%esi\n\t"
      "jmp .LFUN_000907c0_1\n\t"
      "leal (%%esp), %%esp\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_000907c0_1:\n\t"
      "testb %%bl, %%bl\n\t"
      "movswl %%ax, %%eax\n\t"
      "movl 0x3361b4(,%%eax,4), %%esi\n\t"
      "jne .LFUN_000907c0_4\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000907c0_3\n\t"
      "movb 0x1(%%edi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "leal 0x1(%%edi), %%eax\n\t"
      "je .LFUN_000907c0_4\n\t"
      "movl (%%esi), %%edx\n\t"
      "subl %%eax, %%edx\n\t"
      ".LFUN_000907c0_2:\n\t"
      "cmpb (%%edx,%%eax,1), %%cl\n\t"
      "jne .LFUN_000907c0_5\n\t"
      "movb 0x1(%%eax), %%cl\n\t"
      "incl %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_000907c0_2\n\t"
      "jmp .LFUN_000907c0_4\n\t"
      ".LFUN_000907c0_3:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000907c0_5\n\t"
      ".LFUN_000907c0_4:\n\t"
      "movb 0x8(%%ebp), %%dl\n\t"
      "movb %%dl, 0x8(%%esi)\n\t"
      ".LFUN_000907c0_5:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw 0x3361b0, %%ax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jl .LFUN_000907c0_1\n\t"
      "popl %%esi\n\t"
      ".LFUN_000907c0_6:\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8dcb0] "m"(b907c0_c8dcb0), [c1d9690] "m"(b907c0_c1d9690)
      : "memory");
}
#else
#error "FUN_000907c0: clang naked draft required"
#endif


/* profile_sections_activate (0x90860) — readable C lift. */
void profile_sections_activate(int a0)
{
  (void)a0;
  FUN_000907c0(1);
}

/* profile_sections_deactivate (0x90880) — readable C lift. */
void profile_sections_deactivate(int a0)
{
  (void)a0;
  FUN_000907c0(0);
}

/* profile_find_frame_value (0x908a0) — XBE naked draft (batch 241). */
#if defined(__clang__)
static void (*const b908a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b908a0_exitfn)(int) = system_exit;
static int (*const b908a0_c1dd801)(const char *a, const char *b) = crt_stricmp;

__attribute__((naked, noinline))
void profile_find_frame_value(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lprofile_find_frame_value_1\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .Lprofile_find_frame_value_2\n\t"
      ".Lprofile_find_frame_value_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x446\n\t"
      "pushl $0x2683fc\n\t"
      "pushl $0x2687e4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lprofile_find_frame_value_2:\n\t"
      "pushl $0x2687dc\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_3\n\t"
      "movl $1, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_3:\n\t"
      "pushl $0x2687d4\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_4\n\t"
      "movl $2, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_4:\n\t"
      "pushl $0x2687cc\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_5\n\t"
      "movl $3, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_5:\n\t"
      "pushl $0x2687c4\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_6\n\t"
      "movl $4, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_6:\n\t"
      "pushl $0x2687bc\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_7\n\t"
      "movl $5, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_7:\n\t"
      "pushl $0x2687b4\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_8\n\t"
      "movl $6, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_8:\n\t"
      "pushl $0x2687ac\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_9\n\t"
      "movl $7, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_9:\n\t"
      "pushl $0x2687a4\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_10\n\t"
      "movl $8, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_10:\n\t"
      "pushl $0x26879c\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_11\n\t"
      "movl $9, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_11:\n\t"
      "pushl $0x268794\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_12\n\t"
      "movl $0xa, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_12:\n\t"
      "pushl $0x26878c\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_13\n\t"
      "movl $0xb, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_13:\n\t"
      "pushl $0x268784\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_14\n\t"
      "movl $0xc, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_14:\n\t"
      "pushl $0x26877c\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_15\n\t"
      "movl $0xd, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_15:\n\t"
      "pushl $0x268774\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_16\n\t"
      "movl $0xe, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_16:\n\t"
      "pushl $0x268768\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_17\n\t"
      "movl $0xf, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_17:\n\t"
      "pushl $0x268760\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_18\n\t"
      "movl $0x15, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_18:\n\t"
      "pushl $0x268758\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_19\n\t"
      "movl $0x10, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_19:\n\t"
      "pushl $0x26874c\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_20\n\t"
      "movl $0x11, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_20:\n\t"
      "pushl $0x268740\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_21\n\t"
      "movl $0x12, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_21:\n\t"
      "pushl $0x268734\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_22\n\t"
      "movl $0x13, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_22:\n\t"
      "pushl $0x268728\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_23\n\t"
      "movl $0x14, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_23:\n\t"
      "pushl $0x26871c\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_24\n\t"
      "movl $0x16, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_24:\n\t"
      "pushl $0x268714\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_25\n\t"
      "movl $0x17, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_25:\n\t"
      "pushl $0x26870c\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_26\n\t"
      "movl $0x18, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_26:\n\t"
      "pushl $0x25ae30\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_27\n\t"
      "movl $0x19, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_27:\n\t"
      "pushl $0x268708\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_28\n\t"
      "movl $0x1a, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_28:\n\t"
      "pushl $0x268704\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_29\n\t"
      "movl $0x1b, %%edi\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_find_frame_value_29:\n\t"
      "pushl $0x2686f8\n\t"
      "pushl %%esi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lprofile_find_frame_value_30\n\t"
      "movl $0x1c, %%edi\n\t"
      ".Lprofile_find_frame_value_30:\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b908a0_assert), [exitfn] "m"(b908a0_exitfn), [c1dd801] "m"(b908a0_c1dd801)
      : "memory");
}
#else
#error "profile_find_frame_value: clang naked draft required"
#endif


/* profile_find_game_value (0x90cd0) — readable C lift. */
int profile_find_game_value(void *section, int16_t *out_index)
{
  extern char DAT_002687e4[];
  extern char DAT_002683fc[];
  if (!section || !out_index) {
    display_assert(DAT_002687e4, DAT_002683fc, 0x4c8, 1);
    system_exit(-1);
  }
  *out_index = (int16_t)0xffff;
  return ((int)(uintptr_t)section | 0xffff);
}

/* profile_frame_get_value (0x90d10) — XBE naked draft (batch 242). */
#if defined(__clang__)
static void (*const b90d10_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b90d10_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void profile_frame_get_value(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "flds 0x2533c0\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "fsts 0x8(%%ebp)\n\t"
      "movw (%%edi), %%ax\n\t"
      "movswl %%ax, %%esi\n\t"
      "imull $0x1128, %%esi, %%esi\n\t"
      "addl $0x3365c8, %%esi\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lprofile_frame_get_value_1\n\t"
      "cmpw 0x3365c2, %%ax\n\t"
      "jl .Lprofile_frame_get_value_2\n\t"
      ".Lprofile_frame_get_value_1:\n\t"
      "pushl $1\n\t"
      "fstp %%st(0)\n\t"
      "pushl $0x4d7\n\t"
      "pushl $0x2683fc\n\t"
      "pushl $0x268860\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "flds 0x8(%%ebp)\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lprofile_frame_get_value_2:\n\t"
      "movw (%%edi), %%ax\n\t"
      "cmpw 0x3365c4, %%ax\n\t"
      "jne .Lprofile_frame_get_value_3\n\t"
      "pushl $1\n\t"
      "fstp %%st(0)\n\t"
      "pushl $0x4d8\n\t"
      "pushl $0x2683fc\n\t"
      "pushl $0x268810\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "flds 0x8(%%ebp)\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lprofile_frame_get_value_3:\n\t"
      "movswl 0xc(%%ebp), %%eax\n\t"
      "decl %%eax\n\t"
      "cmpl $0x1b, %%eax\n\t"
      "ja .Lprofile_frame_get_value_37\n\t"
      "pushl %%ebx\n\t"
      "jmp *.Lprofile_frame_get_value_jt(,%%eax,4)\n\t"
      ".Lprofile_frame_get_value_4:\n\t"
      "popl %%ebx\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x28(%%esi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_frame_get_value_5:\n\t"
      "fstp %%st(0)\n\t"
      "popl %%ebx\n\t"
      "flds 0x28(%%esi)\n\t"
      "popl %%edi\n\t"
      "fsubs 0xef8(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_frame_get_value_6:\n\t"
      "cmpw $0, 0x10(%%esi)\n\t"
      "jle .Lprofile_frame_get_value_36\n\t"
      "popl %%ebx\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x40(%%esi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_frame_get_value_7:\n\t"
      "cmpw $0, 0x12(%%esi)\n\t"
      "jle .Lprofile_frame_get_value_36\n\t"
      "popl %%ebx\n\t"
      "fstp %%st(0)\n\t"
      "flds 0xe50(%%esi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_frame_get_value_8:\n\t"
      "movw 0x12(%%esi), %%cx\n\t"
      "xorl %%eax, %%eax\n\t"
      "testw %%cx, %%cx\n\t"
      "jle .Lprofile_frame_get_value_36\n\t"
      ".Lprofile_frame_get_value_9:\n\t"
      "movswl %%ax, %%edx\n\t"
      "movb 0x14(%%edx,%%esi,1), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lprofile_frame_get_value_10\n\t"
      "incl %%eax\n\t"
      "cmpw %%cx, %%ax\n\t"
      "jl .Lprofile_frame_get_value_9\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_frame_get_value_10:\n\t"
      "movswl %%ax, %%eax\n\t"
      "fstp %%st(0)\n\t"
      "popl %%ebx\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "popl %%edi\n\t"
      "flds 0xe50(%%esi,%%eax,8)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_frame_get_value_11:\n\t"
      "popl %%ebx\n\t"
      "fstp %%st(0)\n\t"
      "flds 0xeb0(%%esi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_frame_get_value_12:\n\t"
      "movw 0x12(%%esi), %%di\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "xorl %%edx, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testw %%di, %%di\n\t"
      "jle .Lprofile_frame_get_value_36\n\t"
      ".Lprofile_frame_get_value_13:\n\t"
      "cmpw $1, %%dx\n\t"
      "jge .Lprofile_frame_get_value_36\n\t"
      "movswl %%cx, %%eax\n\t"
      "movb 0x14(%%eax,%%esi,1), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lprofile_frame_get_value_14\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "fadds 0xe50(%%esi,%%eax,8)\n\t"
      "incl %%edx\n\t"
      ".Lprofile_frame_get_value_14:\n\t"
      "incl %%ecx\n\t"
      "cmpw %%di, %%cx\n\t"
      "jl .Lprofile_frame_get_value_13\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_frame_get_value_15:\n\t"
      "movw 0x12(%%esi), %%di\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "xorl %%edx, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testw %%di, %%di\n\t"
      "jle .Lprofile_frame_get_value_36\n\t"
      "jmp .Lprofile_frame_get_value_16\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lprofile_frame_get_value_16:\n\t"
      "cmpw $2, %%dx\n\t"
      "jge .Lprofile_frame_get_value_36\n\t"
      "movswl %%cx, %%eax\n\t"
      "movb 0x14(%%eax,%%esi,1), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lprofile_frame_get_value_17\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "fadds 0xe50(%%esi,%%eax,8)\n\t"
      "incl %%edx\n\t"
      ".Lprofile_frame_get_value_17:\n\t"
      "incl %%ecx\n\t"
      "cmpw %%di, %%cx\n\t"
      "jl .Lprofile_frame_get_value_16\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_frame_get_value_18:\n\t"
      "movw 0x12(%%esi), %%di\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "xorl %%edx, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testw %%di, %%di\n\t"
      "jle .Lprofile_frame_get_value_36\n\t"
      ".Lprofile_frame_get_value_19:\n\t"
      "cmpw $3, %%dx\n\t"
      "jge .Lprofile_frame_get_value_36\n\t"
      "movswl %%cx, %%eax\n\t"
      "movb 0x14(%%eax,%%esi,1), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lprofile_frame_get_value_20\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "fadds 0xe50(%%esi,%%eax,8)\n\t"
      "incl %%edx\n\t"
      ".Lprofile_frame_get_value_20:\n\t"
      "incl %%ecx\n\t"
      "cmpw %%di, %%cx\n\t"
      "jl .Lprofile_frame_get_value_19\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_frame_get_value_21:\n\t"
      "movw 0x12(%%esi), %%di\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "xorl %%edx, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testw %%di, %%di\n\t"
      "jle .Lprofile_frame_get_value_36\n\t"
      "jmp .Lprofile_frame_get_value_22\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lprofile_frame_get_value_22:\n\t"
      "cmpw $4, %%dx\n\t"
      "jge .Lprofile_frame_get_value_36\n\t"
      "movswl %%cx, %%eax\n\t"
      "movb 0x14(%%eax,%%esi,1), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lprofile_frame_get_value_23\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "fadds 0xe50(%%esi,%%eax,8)\n\t"
      "incl %%edx\n\t"
      ".Lprofile_frame_get_value_23:\n\t"
      "incl %%ecx\n\t"
      "cmpw %%di, %%cx\n\t"
      "jl .Lprofile_frame_get_value_22\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_frame_get_value_24:\n\t"
      "movw 0x12(%%esi), %%di\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "xorl %%edx, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testw %%di, %%di\n\t"
      "jle .Lprofile_frame_get_value_36\n\t"
      ".Lprofile_frame_get_value_25:\n\t"
      "cmpw $4, %%dx\n\t"
      "jge .Lprofile_frame_get_value_36\n\t"
      "movswl %%cx, %%eax\n\t"
      "movb 0x14(%%eax,%%esi,1), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "fadds 0xe50(%%esi,%%eax,8)\n\t"
      "je .Lprofile_frame_get_value_26\n\t"
      "incl %%edx\n\t"
      ".Lprofile_frame_get_value_26:\n\t"
      "incl %%ecx\n\t"
      "cmpw %%di, %%cx\n\t"
      "jl .Lprofile_frame_get_value_25\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_frame_get_value_27:\n\t"
      "movw 0x10(%%esi), %%cx\n\t"
      "fstp %%st(0)\n\t"
      "testw %%cx, %%cx\n\t"
      "flds 0xeb0(%%esi)\n\t"
      "jle .Lprofile_frame_get_value_36\n\t"
      "leal 0x40(%%esi), %%eax\n\t"
      "movzwl %%cx, %%ecx\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lprofile_frame_get_value_28:\n\t"
      "fadds (%%eax)\n\t"
      "addl $0x18, %%eax\n\t"
      "decl %%ecx\n\t"
      "jne .Lprofile_frame_get_value_28\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_frame_get_value_29:\n\t"
      "popl %%ebx\n\t"
      "fstp %%st(0)\n\t"
      "flds 0xec8(%%esi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_frame_get_value_30:\n\t"
      "popl %%ebx\n\t"
      "fstp %%st(0)\n\t"
      "flds 0xee0(%%esi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_frame_get_value_31:\n\t"
      "popl %%ebx\n\t"
      "fstp %%st(0)\n\t"
      "flds 0xef8(%%esi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_frame_get_value_32:\n\t"
      "popl %%ebx\n\t"
      "fstp %%st(0)\n\t"
      "flds 0xf00(%%esi)\n\t"
      "popl %%edi\n\t"
      "fmuls 0x254cb8\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_frame_get_value_33:\n\t"
      "popl %%ebx\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x1110(%%esi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprofile_frame_get_value_34:\n\t"
      "movl 0x1114(%%esi), %%ecx\n\t"
      "fstp %%st(0)\n\t"
      "testl %%ecx, %%ecx\n\t"
      "fildl 0x1114(%%esi)\n\t"
      "jge .Lprofile_frame_get_value_35\n\t"
      "fadds 0x25fb8c\n\t"
      ".Lprofile_frame_get_value_35:\n\t"
      "fmuls 0x268808\n\t"
      "fmuls 0x268804\n\t"
      ".Lprofile_frame_get_value_36:\n\t"
      "popl %%ebx\n\t"
      ".Lprofile_frame_get_value_37:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lprofile_frame_get_value_jt:\n\t"
      ".long .Lprofile_frame_get_value_4\n\t"
      ".long .Lprofile_frame_get_value_5\n\t"
      ".long .Lprofile_frame_get_value_6\n\t"
      ".long .Lprofile_frame_get_value_36\n\t"
      ".long .Lprofile_frame_get_value_36\n\t"
      ".long .Lprofile_frame_get_value_36\n\t"
      ".long .Lprofile_frame_get_value_36\n\t"
      ".long .Lprofile_frame_get_value_36\n\t"
      ".long .Lprofile_frame_get_value_36\n\t"
      ".long .Lprofile_frame_get_value_36\n\t"
      ".long .Lprofile_frame_get_value_7\n\t"
      ".long .Lprofile_frame_get_value_36\n\t"
      ".long .Lprofile_frame_get_value_36\n\t"
      ".long .Lprofile_frame_get_value_36\n\t"
      ".long .Lprofile_frame_get_value_8\n\t"
      ".long .Lprofile_frame_get_value_12\n\t"
      ".long .Lprofile_frame_get_value_15\n\t"
      ".long .Lprofile_frame_get_value_18\n\t"
      ".long .Lprofile_frame_get_value_21\n\t"
      ".long .Lprofile_frame_get_value_24\n\t"
      ".long .Lprofile_frame_get_value_11\n\t"
      ".long .Lprofile_frame_get_value_27\n\t"
      ".long .Lprofile_frame_get_value_29\n\t"
      ".long .Lprofile_frame_get_value_30\n\t"
      ".long .Lprofile_frame_get_value_31\n\t"
      ".long .Lprofile_frame_get_value_32\n\t"
      ".long .Lprofile_frame_get_value_33\n\t"
      ".long .Lprofile_frame_get_value_34\n\t"
      ".text\n\t"
      :
      : [assert] "m"(b90d10_assert), [exitfn] "m"(b90d10_exitfn)
      : "memory");
}
#else
#error "profile_frame_get_value: clang naked draft required"
#endif


/* profile_frame_iterator_new (0x910b0) — readable C lift. */
void profile_frame_iterator_new(int16_t *iter)
{
  extern char DAT_0025c3b4[];
  extern char DAT_002683fc[];
  int v;
  if (!iter) {
    display_assert(DAT_0025c3b4, DAT_002683fc, 0x58b, 1);
    system_exit(-1);
  }
  iter[0] = -1;
  v = (int)*(int16_t *)0x3365c4 + 0xff;
  v &= 0x800000ff;
  if (v < 0) {
    v = ((v - 1) | 0xffffff00) + 1;
  }
  iter[1] = (int16_t)v;
}

/* profile_frame_iterator_next (0x91110) — readable C lift. */
char profile_frame_iterator_next(int16_t *iter, uint32_t *out_cycles)
{
  int16_t cx = iter[1];
  char ok = 0;
  iter[0] = cx;
  if (cx == -1 || cx >= *(int16_t *)0x3365c2) {
    return 0;
  }
  ok = 1;
  if (out_cycles) {
    int off = (int)cx * 0x1128;
    out_cycles[0] = *(uint32_t *)(0x3365d0 + off);
    out_cycles[1] = *(uint32_t *)(0x3365d4 + off);
  }
  {
    int v = (int)iter[0] + 0xff;
    v &= 0x800000ff;
    if (v < 0) {
      v = ((v - 1) | 0xffffff00) + 1;
    }
    iter[1] = (int16_t)v;
    if (iter[1] == *(int16_t *)0x3365c4) {
      iter[1] = -1;
    }
  }
  return ok;
}

/* profile_frame_get_messages (0x91190) — XBE naked draft (batch 268). */
#if defined(__clang__)
static void (*const b91190_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b91190_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void profile_frame_get_messages(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lprofile_frame_get_messages_1\n\t"
      "pushl $1\n\t"
      "pushl $0x5b7\n\t"
      "pushl $0x2683fc\n\t"
      "pushl $0x25c3b4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lprofile_frame_get_messages_1:\n\t"
      "movw (%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lprofile_frame_get_messages_2\n\t"
      "cmpw 0x3365c2, %%ax\n\t"
      "jl .Lprofile_frame_get_messages_3\n\t"
      ".Lprofile_frame_get_messages_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x5b8\n\t"
      "pushl $0x2683fc\n\t"
      "pushl $0x268860\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lprofile_frame_get_messages_3:\n\t"
      "movw (%%esi), %%ax\n\t"
      "cmpw 0x3365c4, %%ax\n\t"
      "popl %%esi\n\t"
      "jne .Lprofile_frame_get_messages_4\n\t"
      "pushl $1\n\t"
      "pushl $0x5b9\n\t"
      "pushl $0x2683fc\n\t"
      "pushl $0x268810\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lprofile_frame_get_messages_4:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b91190_assert), [exitfn] "m"(b91190_exitfn)
      : "memory");
}
#else
#error "profile_frame_get_messages: clang naked draft required"
#endif


/* profile_frame_get_stalls (0x91220) — XBE naked draft (batch 266). */
#if defined(__clang__)
static void (*const b91220_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b91220_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void profile_frame_get_stalls(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movw (%%edi), %%ax\n\t"
      "movswl %%ax, %%esi\n\t"
      "imull $0x1128, %%esi, %%esi\n\t"
      "addl $0x3365c8, %%esi\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lprofile_frame_get_stalls_1\n\t"
      "cmpw 0x3365c2, %%ax\n\t"
      "jl .Lprofile_frame_get_stalls_2\n\t"
      ".Lprofile_frame_get_stalls_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x5c8\n\t"
      "pushl $0x2683fc\n\t"
      "pushl $0x268860\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lprofile_frame_get_stalls_2:\n\t"
      "movw (%%edi), %%ax\n\t"
      "cmpw 0x3365c4, %%ax\n\t"
      "jne .Lprofile_frame_get_stalls_3\n\t"
      "pushl $1\n\t"
      "pushl $0x5c9\n\t"
      "pushl $0x2683fc\n\t"
      "pushl $0x268810\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lprofile_frame_get_stalls_3:\n\t"
      "movw 0x111c(%%esi), %%cx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movw %%cx, (%%edx)\n\t"
      "movl 0x1120(%%esi), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x1118(%%esi), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b91220_assert), [exitfn] "m"(b91220_exitfn)
      : "memory");
}
#else
#error "profile_frame_get_stalls: clang naked draft required"
#endif


/* profile_rasterizer_stalls (0x912c0) — XBE naked draft (batch 254). */
#if defined(__clang__)


__attribute__((naked, noinline))
void profile_rasterizer_stalls(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "fildl 0x3361a0\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "fildl 0x18(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, 0x449c80\n\t"
      "fmuls 0x254cb8\n\t"
      "movl %%eax, 0x449c84\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x449c8c\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, 0x449c88\n\t"
      "movw 0xc(%%ebp), %%ax\n\t"
      "movl %%edx, 0x449ee0\n\t"
      "movw %%ax, 0x449ee4\n\t"
      "flds 0x449c90\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps 0x449c90\n\t"
      "flds 0x449c94\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps 0x449c94\n\t"
      "fstp %%st(0)\n\t"
      "fildl 0x10(%%ebp)\n\t"
      "jge .Lprofile_rasterizer_stalls_1\n\t"
      "fadds 0x25fb8c\n\t"
      ".Lprofile_rasterizer_stalls_1:\n\t"
      "fmuls 0x254cb8\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fstps 0x449ee8\n\t"
      "fstp %%st(0)\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "profile_rasterizer_stalls: clang naked draft required"
#endif


/* FUN_00091350 (0x91350) — readable C lift. */
void FUN_00091350(uint32_t *out)
{
  uint32_t lo, hi;
  RDTSC(lo, hi);
  out[0] = lo;
  out[1] = hi;
}

/* FUN_00091380 (0x91380) — XBE naked draft (batch 255). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_00091380(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      ".byte 0x0f, 0x31\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "popl %%edx\n\t"
      "popl %%eax\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl (%%ecx), %%esi\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "subl %%esi, %%eax\n\t"
      "movl 0x4(%%ecx), %%esi\n\t"
      "movl %%edx, 0xc(%%ecx)\n\t"
      "sbbl %%esi, %%edx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "popl %%esi\n\t"
      "fmuls 0x254cb8\n\t"
      "fildl 0x3361a0\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fld %%st(0)\n\t"
      "fadds 0x10(%%ecx)\n\t"
      "fstps 0x10(%%ecx)\n\t"
      "fadds 0x14(%%ecx)\n\t"
      "fstps 0x14(%%ecx)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_00091380: clang naked draft required"
#endif


/* FUN_00091b70 (0x91b70) — readable C lift. */
void FUN_00091b70(void)
{
  uint32_t lo, hi;
  RDTSC(lo, hi);
  *(uint32_t *)0x449cb0 = lo;
  *(uint32_t *)0x449cb4 = hi;
}

/* FUN_00091ba0 (0x91ba0) — XBE naked draft (batch 255). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_00091ba0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      ".byte 0x0f, 0x31\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "popl %%edx\n\t"
      "popl %%eax\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x449cb0, %%edx\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x449cb8\n\t"
      "subl %%edx, %%eax\n\t"
      "movl 0x449cb4, %%edx\n\t"
      "movl %%ecx, 0x449cbc\n\t"
      "sbbl %%edx, %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "fmuls 0x254cb8\n\t"
      "fildl 0x3361a0\n\t"
      ".byte 0xde, 0xf9\n\t"
      "flds 0x449cc0\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps 0x449cc0\n\t"
      "flds 0x449cc4\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps 0x449cc4\n\t"
      "fstp %%st(0)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_00091ba0: clang naked draft required"
#endif


/* FUN_00091c10 (0x91c10) — readable C lift. */
void FUN_00091c10(void *dst, void *src, const char *name, int field)
{
  csmemset(dst, 0, 0x110);
  if (src && *(int *)src) {
    *(int *)dst = *(int *)src;
    *((int *)dst + 1) = *((int *)src + 1);
    if (name)
      csstrncpy((char *)dst + 8, name, 0xff);
    *(int *)((char *)dst + 0x108) = field;
  }
}

/* FUN_00091c70 (0x91c70) — readable C lift. */
void FUN_00091c70(void *rec, int a1, int a2, char force)
{
  extern char DAT_00268ad8[];
  extern char DAT_00268ae0[];
  unsigned int now;
  int elapsed;
  int pct;
  void (*cb)(int, char *, int, int);

  if (!rec) {
    display_assert(DAT_00268ad8, DAT_00268ae0, 0x23, 1);
    system_exit(-1);
  }
  if (*(int *)rec == 0)
    return;
  if (*(int *)((char *)rec + 0x108) == 0)
    return;
  now = system_milliseconds();
  elapsed = (int)now - *(int *)((char *)rec + 0x10c);
  if ((unsigned int)elapsed <= 0x7d && !force)
    return;
  pct = a2 * 0x64;
  pct = pct / *(int *)((char *)rec + 0x108);
  cb = *(void (**)(int, char *, int, int))rec;
  cb(*(int *)((char *)rec + 4), (char *)rec + 8, a1, pct);
  *(int *)((char *)rec + 0x10c) = (int)now;
}

/* FUN_00091cf0 (0x91cf0) — XBE naked draft (batch 251). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_00091cf0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl %%eax, %%edi\n\t"
      "jbe .LFUN_00091cf0_5\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "nop\n\t"
      ".LFUN_00091cf0_1:\n\t"
      "leal 0x2(%%eax), %%esi\n\t"
      "cmpl %%edi, %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "ja .LFUN_00091cf0_4\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00091cf0_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%ebx), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%esi), %%cx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *0xc(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00091cf0_3\n\t"
      "movl %%esi, %%ebx\n\t"
      ".LFUN_00091cf0_3:\n\t"
      "addl $2, %%esi\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jbe .LFUN_00091cf0_2\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      ".LFUN_00091cf0_4:\n\t"
      "movw (%%edi), %%dx\n\t"
      "movw (%%ebx), %%cx\n\t"
      "movw %%dx, (%%ebx)\n\t"
      "movw %%cx, (%%edi)\n\t"
      "subl $2, %%edi\n\t"
      "cmpl %%eax, %%edi\n\t"
      "ja .LFUN_00091cf0_1\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00091cf0_5:\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_00091cf0: clang naked draft required"
#endif


/* FUN_00091d50 (0x91d50) — XBE naked draft (batch 252). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_00091d50(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl %%eax, %%edi\n\t"
      "jbe .LFUN_00091d50_5\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "nop\n\t"
      ".LFUN_00091d50_1:\n\t"
      "leal 0x4(%%eax), %%esi\n\t"
      "cmpl %%edi, %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "ja .LFUN_00091d50_4\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00091d50_2:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *0xc(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00091d50_3\n\t"
      "movl %%esi, %%ebx\n\t"
      ".LFUN_00091d50_3:\n\t"
      "addl $4, %%esi\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jbe .LFUN_00091d50_2\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      ".LFUN_00091d50_4:\n\t"
      "movl (%%edi), %%edx\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "movl %%edx, (%%ebx)\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "subl $4, %%edi\n\t"
      "cmpl %%eax, %%edi\n\t"
      "ja .LFUN_00091d50_1\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00091d50_5:\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_00091d50: clang naked draft required"
#endif


/* FUN_00091da0 (0x91da0) — XBE naked draft (batch 242). */
#if defined(__clang__)
static void (*const b91da0_c91cf0)(void) = (void (*)(void))FUN_00091cf0;

__attribute__((naked, noinline))
void FUN_00091da0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xf4, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cmpl $2, %%eax\n\t"
      "jb .LFUN_00091da0_12\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "leal -0x2(%%esi,%%eax,2), %%eax\n\t"
      "pushl %%edi\n\t"
      "movl $0, 0xc(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00091da0_1:\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "movl %%edi, %%eax\n\t"
      "subl %%esi, %%eax\n\t"
      "sarl $1, %%eax\n\t"
      "incl %%eax\n\t"
      "cmpl $8, %%eax\n\t"
      "ja .LFUN_00091da0_3\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c91cf0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00091da0_2:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "decl %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "js .LFUN_00091da0_11\n\t"
      "movl -0xf4(%%ebp,%%eax,4), %%edx\n\t"
      "movl -0x7c(%%ebp,%%eax,4), %%esi\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00091da0_1\n\t"
      ".LFUN_00091da0_3:\n\t"
      "movw (%%esi), %%dx\n\t"
      "shrl $1, %%eax\n\t"
      "movw (%%esi,%%eax,2), %%cx\n\t"
      "leal (%%esi,%%eax,2), %%eax\n\t"
      "movw %%dx, (%%eax)\n\t"
      "movw %%cx, (%%esi)\n\t"
      "movl %%esi, %%ebx\n\t"
      "addl $2, %%edi\n\t"
      ".LFUN_00091da0_4:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $2, %%ebx\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "ja .LFUN_00091da0_5\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%esi), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%ebx), %%cx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *0x10(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00091da0_4\n\t"
      ".LFUN_00091da0_5:\n\t"
      "subl $2, %%edi\n\t"
      "cmpl %%esi, %%edi\n\t"
      "jbe .LFUN_00091da0_6\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw (%%esi), %%dx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%edi), %%ax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *0x10(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00091da0_5\n\t"
      ".LFUN_00091da0_6:\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jb .LFUN_00091da0_7\n\t"
      "movw (%%edi), %%cx\n\t"
      "movw (%%ebx), %%ax\n\t"
      "movw %%cx, (%%ebx)\n\t"
      "movw %%ax, (%%edi)\n\t"
      "jmp .LFUN_00091da0_4\n\t"
      ".LFUN_00091da0_7:\n\t"
      "movw (%%edi), %%dx\n\t"
      "movw (%%esi), %%ax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movw %%dx, (%%esi)\n\t"
      "movw %%ax, (%%edi)\n\t"
      "movl %%edi, %%eax\n\t"
      "subl %%esi, %%eax\n\t"
      "movl %%ecx, %%edx\n\t"
      "decl %%eax\n\t"
      "subl %%ebx, %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .LFUN_00091da0_9\n\t"
      "leal 0x2(%%esi), %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jae .LFUN_00091da0_8\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $-2, %%edi\n\t"
      "movl %%esi, -0x7c(%%ebp,%%eax,4)\n\t"
      "movl %%edi, -0xf4(%%ebp,%%eax,4)\n\t"
      "incl %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      ".LFUN_00091da0_8:\n\t"
      "cmpl %%ecx, %%ebx\n\t"
      "jae .LFUN_00091da0_2\n\t"
      "movl %%ebx, %%esi\n\t"
      "jmp .LFUN_00091da0_1\n\t"
      ".LFUN_00091da0_9:\n\t"
      "cmpl %%ecx, %%ebx\n\t"
      "jae .LFUN_00091da0_10\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%ebx, -0x7c(%%ebp,%%eax,4)\n\t"
      "movl %%ecx, -0xf4(%%ebp,%%eax,4)\n\t"
      "incl %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      ".LFUN_00091da0_10:\n\t"
      "leal 0x2(%%esi), %%ecx\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "jae .LFUN_00091da0_2\n\t"
      "addl $-2, %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00091da0_1\n\t"
      ".LFUN_00091da0_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00091da0_12:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c91cf0] "m"(b91da0_c91cf0)
      : "memory");
}
#else
#error "FUN_00091da0: clang naked draft required"
#endif


/* FUN_00091ef0 (0x91ef0) — XBE naked draft (batch 242). */
#if defined(__clang__)
static void (*const b91ef0_c91d50)(void) = (void (*)(void))FUN_00091d50;

__attribute__((naked, noinline))
void FUN_00091ef0(int *keys __attribute__((unused)), int count __attribute__((unused)), void *cmp)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xf4, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cmpl $2, %%eax\n\t"
      "jb .LFUN_00091ef0_12\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "leal -0x4(%%esi,%%eax,4), %%eax\n\t"
      "pushl %%edi\n\t"
      "movl $0, 0xc(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00091ef0_1:\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "movl %%edi, %%eax\n\t"
      "subl %%esi, %%eax\n\t"
      "sarl $2, %%eax\n\t"
      "incl %%eax\n\t"
      "cmpl $8, %%eax\n\t"
      "ja .LFUN_00091ef0_3\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c91d50]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00091ef0_2:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "decl %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "js .LFUN_00091ef0_11\n\t"
      "movl -0xf4(%%ebp,%%eax,4), %%edx\n\t"
      "movl -0x7c(%%ebp,%%eax,4), %%esi\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00091ef0_1\n\t"
      ".LFUN_00091ef0_3:\n\t"
      "movl (%%esi), %%edx\n\t"
      "shrl $1, %%eax\n\t"
      "movl (%%esi,%%eax,4), %%ecx\n\t"
      "leal (%%esi,%%eax,4), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movl %%esi, %%ebx\n\t"
      "addl $4, %%edi\n\t"
      "nop\n\t"
      ".LFUN_00091ef0_4:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $4, %%ebx\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "ja .LFUN_00091ef0_5\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *0x10(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00091ef0_4\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00091ef0_5:\n\t"
      "subl $4, %%edi\n\t"
      "cmpl %%esi, %%edi\n\t"
      "jbe .LFUN_00091ef0_6\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *0x10(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00091ef0_5\n\t"
      ".LFUN_00091ef0_6:\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jb .LFUN_00091ef0_7\n\t"
      "movl (%%edi), %%ecx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl %%ecx, (%%ebx)\n\t"
      "movl %%eax, (%%edi)\n\t"
      "jmp .LFUN_00091ef0_4\n\t"
      ".LFUN_00091ef0_7:\n\t"
      "movl (%%edi), %%edx\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%edx, (%%esi)\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl %%edi, %%eax\n\t"
      "subl %%esi, %%eax\n\t"
      "movl %%ecx, %%edx\n\t"
      "decl %%eax\n\t"
      "subl %%ebx, %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .LFUN_00091ef0_9\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jae .LFUN_00091ef0_8\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $-4, %%edi\n\t"
      "movl %%esi, -0x7c(%%ebp,%%eax,4)\n\t"
      "movl %%edi, -0xf4(%%ebp,%%eax,4)\n\t"
      "incl %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      ".LFUN_00091ef0_8:\n\t"
      "cmpl %%ecx, %%ebx\n\t"
      "jae .LFUN_00091ef0_2\n\t"
      "movl %%ebx, %%esi\n\t"
      "jmp .LFUN_00091ef0_1\n\t"
      ".LFUN_00091ef0_9:\n\t"
      "cmpl %%ecx, %%ebx\n\t"
      "jae .LFUN_00091ef0_10\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%ebx, -0x7c(%%ebp,%%eax,4)\n\t"
      "movl %%ecx, -0xf4(%%ebp,%%eax,4)\n\t"
      "incl %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      ".LFUN_00091ef0_10:\n\t"
      "leal 0x4(%%esi), %%ecx\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "jae .LFUN_00091ef0_2\n\t"
      "addl $-4, %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00091ef0_1\n\t"
      ".LFUN_00091ef0_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00091ef0_12:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c91d50] "m"(b91ef0_c91d50)
      : "memory");
}
#else
#error "FUN_00091ef0: clang naked draft required"
#endif


/* FUN_00092050 (0x92050) — readable C lift. */
void FUN_00092050(char value)
{
  *(char *)0x2ee784 = value;
}

/* profile_idle_start (0x92060) — readable C lift. */
int profile_idle_start(uint32_t *a, uint32_t *b)
{
  uint32_t left;
  uint32_t right;

  left = a[1];
  if (left == 0)
    return 1;
  right = b[1];
  if (left > right)
    return 1;
  if (right == 0)
    return -1;
  if (left < right)
    return -1;
  return 0;
}

/* 0x92110 */
char *FUN_00092110(int32_t addr, int32_t *symtab)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  csstrcpy((char *)0x00449f00, (char *)0x0025b724);
  /* test ecx, ecx -> jle 0x921af */
  /* relift: cmp esi, dword ptr [edi + 4] -> jb 0x921af */
  /* cmp esi, eax -> jae 0x921af */
  /* cmp ecx, eax -> jle 0x921af */
  /* relift: cmp dword ptr [edx - 0x10], esi -> ja 0x9216b */
  /* relift: cmp esi, dword ptr [edx] -> jb 0x9217d */
  /* cmp eax, ecx -> jl 0x92162 */
  snprintf((char *)0x00449f00, 16383, (char *)0x00268b40);
  return (char *)(uintptr_t)1;

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* FUN_000921c0 (0x921c0) — XBE naked draft (batch 265). */
#if defined(__clang__)
static int (*const b921c0_c8dcb0)(const char *s1, const char *s2) = csstrcmp;

__attribute__((naked, noinline))
void FUN_000921c0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "movl $1, %%ebx\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jle .LFUN_000921c0_3\n\t"
      "pushl %%edi\n\t"
      "movl $0x10, %%edi\n\t"
      ".LFUN_000921c0_1:\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl 0x8(%%edi,%%eax,1), %%eax\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "addl %%edx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8dcb0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000921c0_2\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movl 0x4(%%edi,%%edx,1), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".LFUN_000921c0_2:\n\t"
      "movl (%%esi), %%eax\n\t"
      "incl %%ebx\n\t"
      "addl $0x10, %%edi\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "jl .LFUN_000921c0_1\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      ".LFUN_000921c0_3:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8dcb0] "m"(b921c0_c8dcb0)
      : "memory");
}
#else
#error "FUN_000921c0: clang naked draft required"
#endif


/* 0x922a0 */
void __fastcall FUN_000922a0(int skip, int32_t *frames, uint32_t max, uint32_t *count)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp eax, edi -> jae 0x922c5 */
  /* mem[0x00449ef8] = eax */
  /* test ecx, ecx -> je 0x922fa */
  /* test eax, eax -> je 0x922f7 */
  /* mem[0x00449ef8] = eax */
  /* cmp eax, edi -> jae 0x922ef */
  /* mem[0x00449ef8] = eax */
  /* mem[0x00449efc] = edi */
  /* test ecx, ecx -> ja 0x92318 */
  /* test eax, eax -> je 0x92341 */
  /* mem[0x00449ef8] = eax */
  /* cmp eax, edi -> jae 0x9233c */
  /* mem[0x00449ef8] = eax */
  /* mem[0x00449efc] = eax */
  /* cmp esi, eax -> jb 0x9230d */
  /* mem[0x00449ef8] = ebp */
  /* mem[0x00449efc] = 0 */
  /* test (char)ebx, (char)ebx -> jne 0x9239a */
  /* cmp eax, edi -> jae 0x923a1 */
  /* mem[0x00449ef8] = eax */
  /* test ecx, ecx -> je 0x923d2 */
  /* test eax, eax -> je 0x923cf */
  /* mem[0x00449ef8] = eax */
  /* cmp eax, edi -> jae 0x923c7 */
  /* mem[0x00449ef8] = eax */
  /* mem[0x00449efc] = edi */
  /* test ecx, ecx -> ja 0x923f0 */
  /* test eax, eax -> je 0x92419 */
  /* mem[0x00449ef8] = eax */
  /* cmp eax, edi -> jae 0x92414 */
  /* mem[0x00449ef8] = eax */
  /* mem[0x00449efc] = eax */
  /* cmp esi, eax -> jb 0x923e5 */
  /* mem[0x002ee780] = 0xffffffff */
  symbol_table_dispose((void *)0x002ee788);
  /* mem[0x00449efc] = eax */
  /* mem[0x00449ef8] = ecx */
  /* relift: tail-call FUN_000922a0(); */
  FUN_00092370(64, (void *)(uintptr_t)eax, 0, (void *)0);
  /* test edi, edi -> jne 0x92544 */
  error(0, (char *)0x00268c1c);
  /* cmp ebx, eax -> jl 0x92544 */
  /* test eax, eax -> je 0x92522 */
  /* test (char)eax, (char)eax -> jne 0x92522 */
  FUN_00092110(edi, (void *)0x002ee788);
  error(0, (char *)0x00268c08);
  /* cmp ebx, eax -> jge 0x924f4 */
  /* test esi, esi -> je 0x92658 */
  error(0, (char *)0);
  error(0, (char *)0x00268be8);
  error(0, (char *)0x00268bd8);
  error(0, (char *)0x00268bc8);
  error(0, (char *)0x00268bb8);
  error(0, (char *)0x00268ba8);
  error(0, (char *)0x00268b98);
  error(0, (char *)0x00268b88);
  /* test eax, eax -> je 0x9262e */
  /* test (char)eax, (char)eax -> jne 0x9262e */
  FUN_00092110(ecx, (void *)0x002ee788);
  error(0, (char *)0x00268b5c);
  /* cmp esi, ebx -> jl 0x92702 */
  /* test eax, eax -> je 0x9269d */
  /* test (char)eax, (char)eax -> jne 0x9269d */
  FUN_00092110(ecx, (void *)0x002ee788);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
