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
/* symbol_table_dispose (0x92090) — XBE naked draft (batch 94). */
#if defined(__clang__)
static void (*const b92090_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b92090_exitfn)(int) = system_exit;
static void (*const b92090_c8ef70)(void *ptr, const char *file, int line) = debug_free;

__attribute__((naked, noinline))
void symbol_table_dispose(int32_t *symtab __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lsymbol_table_dispose_1\n\t"
      "pushl $1\n\t"
      "pushl $0x225\n\t"
      "pushl $0x268b14\n\t"
      "pushl $0x268b04\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsymbol_table_dispose_1:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsymbol_table_dispose_2\n\t"
      "pushl $0x227\n\t"
      "pushl $0x268b14\n\t"
      "pushl %%eax\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lsymbol_table_dispose_2:\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsymbol_table_dispose_3\n\t"
      "pushl $0x228\n\t"
      "pushl $0x268b14\n\t"
      "pushl %%eax\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lsymbol_table_dispose_3:\n\t"
      "movl $0, (%%esi)\n\t"
      "movl $0, 0x4(%%esi)\n\t"
      "movl $0, 0x8(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b92090_assert), [exitfn] "m"(b92090_exitfn), [c8ef70] "m"(b92090_c8ef70)
      : "memory");
}
#else
#error "symbol_table_dispose: clang naked draft required"
#endif

/* --- profile.obj batch drafts (2026-07-26) --- */

/* 0x8f870 */
void profile_seconds_elapsed(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x8f880 */
void profile_lapsed_frames(void)
{
  int eax = 0;

  /* test eax, eax -> je 0x8f8bc */
  csstrcpy((char *)0x00449cd5, (char *)(uintptr_t)eax);

  (void)eax;
}

/* 0x8f8c0 */
void profile_lapsed_msec(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x8f8e0 */
void find_profile_section(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* cmp esi, ebx -> jne 0x8f90e */
  display_assert((char *)0x002684a4, (char *)0x002683fc, 559, 0);
  system_exit(0);
  /* relift: cmp byte ptr [esi + 8], (char)ebx -> jne 0x8f933 */
  display_assert((char *)0x00268494, (char *)0x002683fc, 560, 0);
  system_exit(0);
  /* cmp eax, -1 -> je 0x8f97b */
  /* cmp eax, ebx -> jl 0x8f957 */
  /* cmp eax, ecx -> jge 0x8f957 */
  /* relift: cmp dword ptr [eax*4 + 0x3361b4], esi -> je 0x8fa30 */
  display_assert((char *)0x00268458, (char *)0x002683fc, 566, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3361b0], 0x100 -> jl 0x8f9a6 */
  display_assert((char *)0x00268420, (char *)0x002683fc, 570, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)ecx, 0, 960);
  csmemset((void *)(uintptr_t)edx, 0, 480);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x8fb60 */
void FUN_0008fb60(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  csstrcpy((char *)(uintptr_t)esi, (char *)0x0025386f);
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  snprintf((char *)(uintptr_t)eax, 0, (char *)0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x8fc24 */
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  snprintf((char *)(uintptr_t)eax, 0, (char *)0);
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  snprintf((char *)(uintptr_t)eax, 0, (char *)0);
  /* test eax, eax -> jle 0x8fc8b */
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  snprintf((char *)(uintptr_t)eax, 0, (char *)0);
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  snprintf((char *)(uintptr_t)eax, 0, (char *)0);
  /* test (char)eax, (char)eax -> je 0x8fcaa */
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  snprintf((char *)(uintptr_t)eax, 0, (char *)0);
  /* test (char)eax, 0x41 -> jne 0x8fd05 */
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  snprintf((char *)(uintptr_t)eax, 0, (char *)0);
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  snprintf((char *)(uintptr_t)eax, 0, (char *)0);
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  snprintf((char *)(uintptr_t)eax, 0, (char *)0);
  /* relift: cmp (int16_t)edx, word ptr [ebx + 0x10] -> jge 0x8fe10 */
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  snprintf((char *)(uintptr_t)eax, 0, (char *)0);
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  snprintf((char *)(uintptr_t)eax, 0, (char *)0);
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  snprintf((char *)(uintptr_t)eax, 0, (char *)0);
  local_player_count();
  /* cmp eax, ecx -> jg 0x8feab */
  local_player_count();
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  snprintf((char *)(uintptr_t)eax, 0, (char *)0);
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  snprintf((char *)(uintptr_t)eax, 0, (char *)0);
  /* relift: cmp (int16_t)edx, word ptr [ebx + 0x12] -> jge 0x8ffa0 */
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  snprintf((char *)(uintptr_t)eax, 0, (char *)0);
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  snprintf((char *)(uintptr_t)eax, 0, (char *)0);
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  snprintf((char *)(uintptr_t)eax, 0, (char *)0);
  /* test (char)eax, 0x41 -> jne 0x90059 */
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  snprintf((char *)(uintptr_t)eax, 0, (char *)0);
  /* test (char)eax, 0x41 -> jne 0x900b4 */
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  snprintf((char *)(uintptr_t)eax, 0, (char *)0);
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  snprintf((char *)(uintptr_t)eax, 0, (char *)0);
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  snprintf((char *)(uintptr_t)eax, 0, (char *)0);
  csstrlen((char *)(uintptr_t)esi);
  csstrlen((char *)(uintptr_t)esi);
  csstrcat((char *)(uintptr_t)eax, (char *)0, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x90170 */
void FUN_00090170(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x90180 */
void FUN_00090180(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x901d0 */
void compare_profile_sections(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test (char)ebx, (char)ebx -> je 0x90251 */
  /* test (char)ebx, (char)ebx -> je 0x901fe */
  /* test dl, dl -> je 0x902c9 */
  display_assert((char *)0x00255ee8, (char *)0x002683fc, 844, 0);
  system_exit(0);
  /* cmp eax, ecx -> jl 0x902c9 */
  /* cmp edx, esi -> jbe 0x90258 */
  /* cmp eax, ecx -> jg 0x90262 */
  /* cmp edx, esi -> jb 0x902c9 */
  /* test (char)eax, 0x41 -> jne 0x902bc */
  csstrcmp((char *)(uintptr_t)edx, (char *)(uintptr_t)ecx);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* profile_dump (0x902f0) — XBE naked draft (batch 243). */
#if defined(__clang__)
static void (*const b902f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b902f0_exitfn)(int) = system_exit;
static void * (*const b902f0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void __cdecl (*const b902f0_c1d9260)(void *base, size_t nmemb, size_t size, int (__cdecl *compar)(const void *, const void *)) = qsort;
static int (*const b902f0_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static char * (*const b902f0_c1d9690)(const char *haystack, const char *needle) = crt_strstr;
static int (*const b902f0_c8dcb0)(const char *s1, const char *s2) = csstrcmp;
static void (*const b902f0_ftol)(void) = FUN_001d9068;
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


/* 0x90650 */
void profile_dump_to_file(int a0)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  FUN_001d90e0();
  csstrlen((char *)(uintptr_t)ebx);
  /* test eax, eax -> je 0x9067b */
  crt_fopen((char *)0x002686cc, (char *)0x00267f84);
  /* test esi, esi -> je 0x906bf */
  profile_dump();
  crt_fprintf((void *)(uintptr_t)esi, (char *)0x002686c4);
  crt_fclose((void *)(uintptr_t)esi);

  (void)eax;
  (void)ebx;
  (void)esi;
}

/* 0x906d0 */
void FUN_000906d0(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x906fd */
  crt_fopen((char *)0x002686dc, (char *)0x002686f0);
  /* mem[0x003365b4] = eax */
  /* relift: cmp byte ptr [edi], 0 -> jne 0x90737 */
  FUN_0008fb60();
  crt_fprintf((void *)(uintptr_t)ecx, (char *)0x002686c4);
  /* test (char)eax, (char)eax -> je 0x90782 */
  /* test eax, eax -> je 0x9077b */
  crt_fprintf((void *)(uintptr_t)eax, (char *)0x00261f2c);
  crt_fflush((void *)(uintptr_t)eax);
  /* relift: cmp (char)ecx, byte ptr [esi] -> jne 0x907af */
  /* test (char)ecx, (char)ecx -> jne 0x907a0 */

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x907c0 */
void FUN_000907c0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  csstrcmp((char *)(uintptr_t)edi, (char *)0x002686f4);
  /* test (char)eax, (char)eax -> je 0x90832 */
  /* relift: cmp (char)ecx, byte ptr [edx + eax] -> jne 0x90848 */
  /* test (char)ecx, (char)ecx -> jne 0x90823 */
  crt_strstr((char *)(uintptr_t)ecx, (char *)(uintptr_t)edi);
  /* test eax, eax -> je 0x90848 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x90860 */
void profile_sections_activate(int a0)
{
  FUN_000907c0();
}

/* 0x90880 */
void profile_sections_deactivate(int a0)
{
  FUN_000907c0();
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


/* 0x90cd0 */
void profile_find_game_value(void)
{
  int esi = 0;

  /* test esi, esi -> jne 0x90d02 */
  display_assert((char *)0x002687e4, (char *)0x002683fc, 1224, 0);
  system_exit(0);

  (void)esi;
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


/* 0x910b0 */
void profile_frame_iterator_new(void)
{
  int esi = 0;

  /* test esi, esi -> jne 0x910db */
  display_assert((char *)0x0025c3b4, (char *)0x002683fc, 1419, 0);
  system_exit(0);

  (void)esi;
}

/* 0x91110 */
void profile_frame_iterator_next(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x91190 */
void profile_frame_get_messages(void)
{
  int esi = 0;

  /* test esi, esi -> jne 0x911bb */
  display_assert((char *)0x0025c3b4, (char *)0x002683fc, 1463, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x911cc */
  /* relift: cmp (int16_t)eax, word ptr [0x3365c2] -> jl 0x911ec */
  display_assert((char *)0x00268860, (char *)0x002683fc, 1464, 0);
  system_exit(0);
  display_assert((char *)0x00268810, (char *)0x002683fc, 1465, 0);
  system_exit(0);

  (void)esi;
}

/* 0x91220 */
void profile_frame_get_stalls(void)
{
  /* test (int16_t)eax, (int16_t)eax -> jl 0x91248 */
  /* relift: cmp (int16_t)eax, word ptr [0x3365c2] -> jl 0x91268 */
  display_assert((char *)0x00268860, (char *)0x002683fc, 1480, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [0x3365c4] -> jne 0x91294 */
  display_assert((char *)0x00268810, (char *)0x002683fc, 1481, 0);
  system_exit(0);
}

/* 0x912c0 */
void profile_rasterizer_stalls(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x91350 */
void FUN_00091350(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x91380 */
void FUN_00091380(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x91b70 */
void FUN_00091b70(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x91ba0 */
void FUN_00091ba0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x91c10 */
void FUN_00091c10(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  csmemset((void *)(uintptr_t)esi, 0, 272);
  /* test ecx, ecx -> je 0x91c5e */
  /* test eax, eax -> je 0x91c5e */
  /* test eax, eax -> je 0x91c55 */
  csstrncpy((char *)(uintptr_t)ecx, (char *)(uintptr_t)eax, 255);

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x91c70 */
void FUN_00091c70(void)
{
  int eax = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x91c98 */
  display_assert((char *)0x00268ad8, (char *)0x00268ae0, 35, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi], 0 -> je 0x91ce9 */
  /* test eax, eax -> je 0x91ce9 */
  system_milliseconds();
  /* cmp eax, 0x7d -> ja 0x91cc3 */
  /* test (char)eax, (char)eax -> je 0x91ce8 */

  (void)eax;
  (void)esi;
}

/* 0x91cf0 */
void FUN_00091cf0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x91d50 */
void FUN_00091d50(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_00091da0 (0x91da0) — XBE naked draft (batch 242). */
#if defined(__clang__)
static void (*const b91da0_c91cf0)(void) = FUN_00091cf0;

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
static void (*const b91ef0_c91d50)(void) = FUN_00091d50;

__attribute__((naked, noinline))
void FUN_00091ef0(int *keys __attribute__((unused)), int count __attribute__((unused)), int (*cmp)(int __attribute__((unused)), int))
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


/* 0x92050 */
void FUN_00092050(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x92060 */
void profile_idle_start(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
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

/* 0x921c0 */
void FUN_000921c0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;

  csstrcmp((char *)(uintptr_t)ecx, (char *)(uintptr_t)eax);
  /* test eax, eax -> jne 0x92207 */
  /* cmp ebx, eax -> jl 0x921e0 */
  /* test (char)ecx, (char)ecx -> jne 0x9223c */
  /* relift: cmp eax, dword ptr [0x449efc] -> jb 0x9223c */
  /* test ecx, ecx -> je 0x92276 */
  /* mem[0x00449ef8] = ecx */
  /* relift: cmp ecx, dword ptr [0x449efc] -> jae 0x92270 */
  /* mem[0x00449ef8] = ecx */
  /* mem[0x00449efc] = ecx */
  /* mem[0x00449efc] = ecx */
  /* mem[0x00449ef8] = edx */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
}

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
