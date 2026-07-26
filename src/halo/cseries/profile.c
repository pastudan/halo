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
/* -----------------------------------------------------------------------
 * symbol_table_dispose (0x92090) — free name_pool and entries buffers and
 * zero the symtab struct.
 *
 * symtab layout: int32_t[3] = { count, name_pool_ptr, entries_ptr }
 * Called from the error path of load_symbol_table to clean up a partially
 * filled symtab when loading fails.
 * ----------------------------------------------------------------------- */
void symbol_table_dispose(int32_t *symtab)
{
  if (symtab == NULL) {
    display_assert("symbol_table",
                   "c:\\halo\\SOURCE\\cseries\\stack_walk_windows.c", 0x225, 1);
    system_exit(-1);
  }
  if (symtab[1] != 0) {
    debug_free((void *)symtab[1],
               "c:\\halo\\SOURCE\\cseries\\stack_walk_windows.c", 0x227);
  }
  if (symtab[2] != 0) {
    debug_free((void *)symtab[2],
               "c:\\halo\\SOURCE\\cseries\\stack_walk_windows.c", 0x228);
  }
  symtab[0] = 0;
  symtab[1] = 0;
  symtab[2] = 0;
}
/* --- profile.obj batch drafts (2026-07-26) --- */

/* 0x8f870 */
void profile_seconds_elapsed(void)
{
  /* relift: no calls detected — manual review */
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
}

/* 0x90180 */
void FUN_00090180(void)
{
  /* relift: no calls detected — manual review */
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

/* 0x902f0 */
void profile_dump(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp (int16_t)ebx, 3 -> jl 0x90332 */
  display_assert((char *)0x0026868c, (char *)0x002683fc, 879, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x90341 */
  /* cmp (int16_t)edi, 2 -> jl 0x90361 */
  display_assert((char *)0x00268648, (char *)0x002683fc, 880, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp + 0x14], 0 -> jg 0x90388 */
  display_assert((char *)0x00268630, (char *)0x002683fc, 881, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x903af */
  display_assert((char *)0x00267900, (char *)0x002683fc, 882, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)ecx, (void *)0x003361b4, eax);
  qsort((void *)(uintptr_t)eax, edx, 0, (void *)0x000901d0);
  /* relift: cmp word ptr [0x3361b0], 0 -> je 0x90649 */
  /* test (char)eax, (char)eax -> je 0x90649 */
  crt_sprintf((char *)(uintptr_t)esi, (char *)(uintptr_t)edx);
  /* relift: cmp word ptr [0x3361b0], (int16_t)ebx -> jle 0x90649 */
  /* relift: cmp word ptr [ebp - 0x18], (int16_t)eax -> jge 0x90649 */
  /* test eax, eax -> je 0x904a2 */
  crt_strstr((char *)(uintptr_t)ecx, (char *)(uintptr_t)eax);
  /* test eax, eax -> je 0x9063b */
  csstrcmp((char *)(uintptr_t)ecx, (char *)(uintptr_t)edx);
  /* test eax, eax -> je 0x9049f */
  FUN_001d9068();
  csstrlen((char *)(uintptr_t)esi);
  crt_sprintf((char *)(uintptr_t)eax, (char *)0);
  csstrlen((char *)(uintptr_t)esi);
  crt_sprintf((char *)(uintptr_t)eax, (char *)0);
  /* relift: cmp (int16_t)ebx, word ptr [0x3361b0] -> jl 0x90440 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

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

/* 0x908a0 */
void profile_find_frame_value(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  /* test esi, esi -> je 0x908b7 */
  /* test ebx, ebx -> jne 0x908d7 */
  display_assert((char *)0x002687e4, (char *)0x002683fc, 1094, 0);
  system_exit(0);
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x002687dc);
  /* test eax, eax -> jne 0x908fb */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x002687d4);
  /* test eax, eax -> jne 0x9091f */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x002687cc);
  /* test eax, eax -> jne 0x90943 */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x002687c4);
  /* test eax, eax -> jne 0x90967 */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x002687bc);
  /* test eax, eax -> jne 0x9098b */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x002687b4);
  /* test eax, eax -> jne 0x909af */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x002687ac);
  /* test eax, eax -> jne 0x909d3 */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x002687a4);
  /* test eax, eax -> jne 0x909f7 */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x0026879c);
  /* test eax, eax -> jne 0x90a1b */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x00268794);
  /* test eax, eax -> jne 0x90a3f */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x0026878c);
  /* test eax, eax -> jne 0x90a63 */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x00268784);
  /* test eax, eax -> jne 0x90a87 */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x0026877c);
  /* test eax, eax -> jne 0x90aab */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x00268774);
  /* test eax, eax -> jne 0x90acf */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x00268768);
  /* test eax, eax -> jne 0x90af3 */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x00268760);
  /* test eax, eax -> jne 0x90b17 */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x00268758);
  /* test eax, eax -> jne 0x90b3b */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x0026874c);
  /* test eax, eax -> jne 0x90b5f */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x00268740);
  /* test eax, eax -> jne 0x90b83 */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x00268734);
  /* test eax, eax -> jne 0x90ba7 */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x00268728);
  /* test eax, eax -> jne 0x90bcb */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x0026871c);
  /* test eax, eax -> jne 0x90bef */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x00268714);
  /* test eax, eax -> jne 0x90c13 */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x0026870c);
  /* test eax, eax -> jne 0x90c37 */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x0025ae30);
  /* test eax, eax -> jne 0x90c5b */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x00268708);
  /* test eax, eax -> jne 0x90c7f */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x00268704);
  /* test eax, eax -> jne 0x90ca3 */
  crt_stricmp((char *)(uintptr_t)esi, (char *)0x002686f8);
  /* test eax, eax -> jne 0x90cba */

  (void)eax;
  (void)ebx;
  (void)esi;
}

/* 0x90cd0 */
void profile_find_game_value(void)
{
  int esi = 0;

  /* test esi, esi -> jne 0x90d02 */
  display_assert((char *)0x002687e4, (char *)0x002683fc, 1224, 0);
  system_exit(0);

  (void)esi;
}

/* 0x90d10 */
void profile_frame_get_value(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test (int16_t)eax, (int16_t)eax -> jl 0x90d41 */
  /* relift: cmp (int16_t)eax, word ptr [0x3365c2] -> jl 0x90d66 */
  display_assert((char *)0x00268860, (char *)0x002683fc, 1239, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [0x3365c4] -> jne 0x90d97 */
  display_assert((char *)0x00268810, (char *)0x002683fc, 1240, 0);
  system_exit(0);
  /* cmp eax, 0x1b -> ja 0x91039 */
  /* relift: cmp word ptr [esi + 0x10], 0 -> jle 0x91038 */
  /* relift: cmp word ptr [esi + 0x12], 0 -> jle 0x91038 */
  /* test (int16_t)ecx, (int16_t)ecx -> jle 0x91038 */
  /* test (char)ebx, (char)ebx -> je 0x90e19 */
  /* cmp (int16_t)eax, (int16_t)ecx -> jl 0x90e03 */
  /* test (int16_t)edi, (int16_t)edi -> jle 0x91038 */
  /* cmp (int16_t)edx, 1 -> jge 0x91038 */
  /* test (char)ebx, (char)ebx -> je 0x90e73 */
  /* cmp (int16_t)ecx, (int16_t)edi -> jl 0x90e53 */
  /* test (int16_t)edi, (int16_t)edi -> jle 0x91038 */
  /* cmp (int16_t)edx, 2 -> jge 0x91038 */
  /* test (char)ebx, (char)ebx -> je 0x90ec0 */
  /* cmp (int16_t)ecx, (int16_t)edi -> jl 0x90ea0 */
  /* test (int16_t)edi, (int16_t)edi -> jle 0x91038 */
  /* cmp (int16_t)edx, 3 -> jge 0x91038 */
  /* test (char)ebx, (char)ebx -> je 0x90f04 */
  /* cmp (int16_t)ecx, (int16_t)edi -> jl 0x90ee4 */
  /* test (int16_t)edi, (int16_t)edi -> jle 0x91038 */
  /* cmp (int16_t)edx, 4 -> jge 0x91038 */
  /* test (char)ebx, (char)ebx -> je 0x90f50 */
  /* cmp (int16_t)ecx, (int16_t)edi -> jl 0x90f30 */
  /* test (int16_t)edi, (int16_t)edi -> jle 0x91038 */
  /* cmp (int16_t)edx, 4 -> jge 0x91038 */
  /* cmp (int16_t)ecx, (int16_t)edi -> jl 0x90f74 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

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
}

/* 0x91350 */
void FUN_00091350(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x91380 */
void FUN_00091380(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x91b70 */
void FUN_00091b70(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x91ba0 */
void FUN_00091ba0(void)
{
  /* relift: no calls detected — manual review */
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
}

/* 0x91d50 */
void FUN_00091d50(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x91da0 */
void FUN_00091da0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp eax, 2 -> jb 0x91ee7 */
  /* cmp eax, 8 -> ja 0x91e0b */
  FUN_00091cf0();
  /* cmp ebx, eax -> ja 0x91e42 */
  /* test (char)eax, (char)eax -> je 0x91e22 */
  /* cmp edi, esi -> jbe 0x91e5f */
  /* test (char)eax, (char)eax -> jne 0x91e42 */
  /* cmp edi, ebx -> jb 0x91e71 */
  /* cmp eax, edx -> jl 0x91eb8 */
  /* cmp eax, edi -> jae 0x91ea9 */
  /* cmp ebx, ecx -> jae 0x91dee */
  /* cmp ebx, ecx -> jae 0x91ece */
  /* cmp ecx, edi -> jae 0x91dee */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x91ef0 */
void FUN_00091ef0(int *keys, int count, int (*cmp)(int, int))
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp eax, 2 -> jb 0x92027 */
  /* cmp eax, 8 -> ja 0x91f5c */
  FUN_00091d50();
  /* cmp ebx, eax -> ja 0x91f90 */
  /* test (char)eax, (char)eax -> je 0x91f70 */
  /* cmp edi, esi -> jbe 0x91fa7 */
  /* test (char)eax, (char)eax -> jne 0x91f90 */
  /* cmp edi, ebx -> jb 0x91fb5 */
  /* cmp eax, edx -> jl 0x91ff8 */
  /* cmp eax, edi -> jae 0x91fe9 */
  /* cmp ebx, ecx -> jae 0x91f3f */
  /* cmp ebx, ecx -> jae 0x9200e */
  /* cmp ecx, edi -> jae 0x91f3f */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x92050 */
void FUN_00092050(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x92060 */
void profile_idle_start(void)
{
  /* relift: no calls detected — manual review */
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
