/* Recorded animation thread system — plays back scripted unit animations
 * for cinematics and AI scripted sequences. */

/* Allocate animation thread data array and debug tracking buffer. */
void recorded_animations_initialize(void)
{
  *(void **)0x44df04 = game_state_data_new("recorded animations", 0x40, 100);
  if (!*(void **)0x44df04) {
    display_assert("animation_threads",
                   "c:\\halo\\SOURCE\\cutscene\\recorded_animations.c", 0x6c,
                   1);
    system_exit(-1);
  }

  *(void **)0x44df0c = ((void *(*)(int, int, const char *, int))0x8ee60)(
    0x400, 0, "c:\\halo\\SOURCE\\cutscene\\recorded_animations.c", 0x6f);
  if (!*(void **)0x44df0c) {
    display_assert("animation_threads_debug",
                   "c:\\halo\\SOURCE\\cutscene\\recorded_animations.c", 0x70,
                   1);
    system_exit(-1);
  }
}

/* Free the debug tracking buffer. */
void recorded_animations_dispose(void)
{
  if (*(void **)0x44df0c != 0) {
    ((void (*)(void *, const char *, int))0x8ef70)(
      *(void **)0x44df0c, "c:\\halo\\SOURCE\\cutscene\\recorded_animations.c",
      0x7b);
    *(void **)0x44df0c = 0;
  }
}

/* Mark animation thread data as invalid for old map disposal. */
void recorded_animations_dispose_from_old_map(void)
{
  data_make_invalid(*(void **)0x44df04);
}

/* Advance all active recorded animation threads by one tick.
 *
 * For each allocated thread, either:
 *   - dispose it (object gone, or finished flag set) by clearing debug slot,
 *     restoring the unit's animation-driven flags, and deleting the datum;
 *   - otherwise, tick its per-type event stream via vtable dispatch, sanity
 *     check against the recorded debug state, and apply the resulting frame
 *     to the unit. The vtable returns "still has events" — the finished bit
 *     is set when the vtable reports zero (stream exhausted).
 */
void recorded_animations_update(void)
{
  data_iter_t iter;
  char *thread;
  char *dbg_slot;
  char stream_active;
  int *relative_ticks;
  uint16_t flags;
  int dbg_index;
  void **vtable;
  int stream_delta;
  scenario_t *scenario;
  char *anim_def;
  char *msg;

  data_iterator_new(&iter, *(data_t **)0x44df04);
  thread = (char *)data_iterator_next(&iter);
  while (thread != NULL) {
    if (object_try_and_get_and_verify_type(*(int *)(thread + 4), 3) == NULL) {
      datum_delete(*(data_t **)0x44df04, iter.datum_handle);
    } else {
      flags = *(uint16_t *)(thread + 0xa);
      if ((flags & 1) == 0) {
        /* Active thread: tick the per-type event stream via vtable. The
         * callback returns nonzero while events remain in the stream and
         * zero once the stream is exhausted. */
        *(int16_t *)(thread + 8) = *(int16_t *)(thread + 8) - 1;
        relative_ticks = (int *)(thread + 0xc);
        vtable = (void **)((void **)0x2eebb0)[*(int16_t *)(thread + 0x60)];
        stream_active = ((char (*)(char *, char *, int *, int *))vtable[1])(
                          thread + 0x54, thread + 0x14, relative_ticks,
                          (int *)(thread + 0x10)) ?
                          1 :
                          0;
        if (*relative_ticks < 0) {
          display_assert("thread->relative_ticks>=0",
                         "c:\\halo\\SOURCE\\cutscene\\recorded_animations.c",
                         0x15b, 1);
          system_exit(-1);
        }
        dbg_index = (iter.datum_handle & 0xffff) * 0x10;
        dbg_slot = (char *)(dbg_index + *(int *)0x44df0c);
        if (*dbg_slot != 0) {
          stream_delta = *(int *)(thread + 0x10) - *(int *)(dbg_slot + 4);
          /* Assert holds when stream_delta is below the recorded length, or
           * exactly at the end while events are still being produced. */
          if (!(stream_delta < *(int *)(dbg_slot + 8) ||
                (stream_delta == *(int *)(dbg_slot + 8) &&
                 stream_active != 0))) {
            display_assert(
              "thread->event_stream-thread_debug->event_stream_start<"
              "thread_debug->stream_length||(thread->event_stream-thread_debug"
              "->event_stream_start==thread_debug->stream_length&&finished)",
              "c:\\halo\\SOURCE\\cutscene\\recorded_animations.c", 0x162, 1);
            system_exit(-1);
          }
        }
        *relative_ticks = *relative_ticks + 1;
        ((void (*)(int, char *))0x1af990)(*(int *)(thread + 4), thread + 0x14);
        /* Stream exhausted → set finished bit so next tick takes the
         * cleanup path. Stream still active → keep the thread alive. */
        if (stream_active != 0)
          *(uint8_t *)(thread + 0xa) = *(uint8_t *)(thread + 0xa) & 0xfe;
        else
          *(uint8_t *)(thread + 0xa) = *(uint8_t *)(thread + 0xa) | 1;
      } else {
        /* Finished thread: clean up and delete. */
        dbg_index = (iter.datum_handle & 0xffff) * 0x10;
        dbg_slot = (char *)(dbg_index + *(int *)0x44df0c);
        if (*dbg_slot != 0 && (flags & 2) == 0 &&
            *(int16_t *)(thread + 8) != 0) {
          scenario = global_scenario_get();
          anim_def = (char *)tag_block_get_element(
            (char *)scenario + 0x36c, *(int16_t *)(dbg_slot + 0xc), 0x40);
          msg = csprintf((char *)0x5ab100, "animation %s appears corrupt",
                         anim_def);
          display_assert(
            msg, "c:\\halo\\SOURCE\\cutscene\\recorded_animations.c", 0x175, 1);
          system_exit(-1);
        }
        *dbg_slot = 0;
        ((void (*)(int, int))0x1a9a50)(*(int *)(thread + 4),
                                       (*(uint8_t *)(thread + 0xa) >> 2) & 1);
        ((void (*)(int, int))0x1a9a90)(*(int *)(thread + 4), 0);
        ((void (*)(int, int))0x1adf10)(*(int *)(thread + 4), 0);
        ((void (*)(int, int))0x13ff50)(*(int *)(thread + 4), 1);
        if ((*(uint8_t *)(thread + 0xa) & 8) != 0)
          ((void (*)(int))0xc99e0)(*(int *)(thread + 4));
        if ((*(uint8_t *)(thread + 0xa) & 0x10) != 0)
          ((void (*)(int, int))0x1b5610)(*(int *)(thread + 4), 1);
        datum_delete(*(data_t **)0x44df04, iter.datum_handle);
      }
    }
    thread = (char *)data_iterator_next(&iter);
  }
}

/* Clear animation threads and zero the debug buffer for a new map. */
void recorded_animations_initialize_for_new_map(void)
{
  ((void (*)(void *))0x119b20)(*(void **)0x44df04);
  if (!*(void **)0x44df0c) {
    display_assert("animation_threads_debug",
                   "c:\\halo\\SOURCE\\cutscene\\recorded_animations.c", 0x99,
                   1);
    system_exit(-1);
  }
  csmemset(*(void **)0x44df0c, 0, 0x400);
}
/* --- recorded_animations.obj batch1 drafts (2026-07-26) --- */

void FUN_00093780(int a, int *cursor, int c);
void FUN_00097080(int object, void *ctrl_block);
void FUN_00097040(int object, float value);
void control_toggle(int object);

void FUN_00094020(int *out, int *cursor_ptr, int a, int c)
{
  FUN_00093780(a, cursor_ptr, c);
  {
    int *p = *(int **)cursor_ptr;
    out[0] = p[0];
    out[1] = p[1];
    out[2] = p[2];
    *(int **)cursor_ptr = (int *)((char *)p + 0xc);
  }
}

void FUN_00094060(int *out, int **stream, int *dest)
{
  int *src = *stream;
  int i;

  for (i = 0; i < 0x10; i++)
    dest[i] = src[i];
  *stream = (int *)((char *)src + 0x40);
  {
    int *p = *stream;
    out[0] = p[0];
    out[1] = p[1];
    out[2] = p[2];
    *stream = (int *)((char *)p + 0xc);
  }
}
void FUN_00094290(void)
{
  /* relift: no calls detected — manual review */
}

void FUN_00094a70(int a, int *cursor, int c)
{
  FUN_00093780(a, cursor, c);
}
void FUN_00094ba0(void)
{
  /* relift: no calls detected — manual review */
}

void recorded_animations_clear_debug_storage(void)
{
  if (!*(void **)0x44df0c) {
    display_assert("animation_threads_debug",
                   "c:\\halo\\SOURCE\\cutscene\\recorded_animations.c", 0x99,
                   1);
    system_exit(-1);
  }
  csmemset(*(void **)0x44df0c, 0, 0x400);
}

char recorded_animation_controlling_unit(int unit_handle)
{
  data_iter_t iter;
  char *thread;

  data_iterator_new(&iter, *(data_t **)0x44df04);
  thread = (char *)data_iterator_next(&iter);
  while (thread != NULL) {
    if (*(int *)(thread + 4) == unit_handle &&
        (*(uint8_t *)(thread + 0xa) & 1) != 0)
      return 1;
    thread = (char *)data_iterator_next(&iter);
  }
  return 0;
}

void FUN_00095050(int unit_handle /* @<edi> */, int *out /* @<ebx> */)
{
  data_iter_t iter;
  char *thread;
  int handle = -1;

  data_iterator_new(&iter, *(data_t **)0x44df04);
  thread = (char *)data_iterator_next(&iter);
  while (thread != NULL) {
    if (*(int *)(thread + 4) == unit_handle) {
      handle = iter.datum_handle;
      break;
    }
    thread = (char *)data_iterator_next(&iter);
  }
  if (out != NULL)
    *out = handle;
}

void recorded_animation_kill(int unit_handle)
{
  data_iter_t iter;
  char *thread;

  data_iterator_new(&iter, *(data_t **)0x44df04);
  thread = (char *)data_iterator_next(&iter);
  while (thread != NULL) {
    if (*(int *)(thread + 4) == unit_handle) {
      if (thread != NULL)
        *(uint8_t *)(thread + 0xa) |= 3;
      return;
    }
    thread = (char *)data_iterator_next(&iter);
  }
}

int recorded_animation_get_time_left(int unit_handle)
{
  data_iter_t iter;
  char *thread;

  data_iterator_new(&iter, *(data_t **)0x44df04);
  thread = (char *)data_iterator_next(&iter);
  while (thread != NULL) {
    if (*(int *)(thread + 4) == unit_handle) {
      if (*(int *)(thread + 4) != unit_handle) {
        display_assert((char *)0x269a5c,
                       "c:\\halo\\SOURCE\\cutscene\\recorded_animations.c",
                       0x138, 1);
        system_exit(-1);
      }
      return *(uint16_t *)(thread + 8);
    }
    thread = (char *)data_iterator_next(&iter);
  }
  return 0;
}

int recorded_animation_play_and_delete(int unit, int anim)
{
  recorded_animation_play_internal(unit, anim, 8);
  return 0;
}

int FUN_00095680(int unit, int anim)
{
  recorded_animation_play_internal(unit, anim, 0x10);
  return 0;
}

void FUN_000956e0(int object, void *ctrl)
{
  char *dev = (char *)object_get_and_verify_type(object, 0x100);

  tag_get(*(int *)dev, 0x6374726c);
  FUN_00097080(object, (char *)ctrl + 0x28);
  if ((*(uint8_t *)((char *)ctrl + 0x30) & 1) != 0)
    *(int *)(dev + 0x1c4) |= 1;
  if ((*(uint8_t *)((char *)ctrl + 0x30) & 0x10) != 0)
    *(int *)(dev + 0x1c4) |= 2;
  *(int16_t *)(dev + 0x1c8) = (int16_t)(*(int16_t *)((char *)ctrl + 0x34) - 1);
}

char FUN_00095750(int object)
{
  char *dev = (char *)object_get_and_verify_type(object, 0x100);

  tag_get(*(int *)dev, 0x6374726c);
  return 1;
}

char FUN_00095790(int object)
{
  char *dev = (char *)object_get_and_verify_type(object, 0x100);

  tag_get(*(int *)dev, 0x6374726c);
  return 1;
}

void FUN_000958f0(int object)
{
  char *dev = (char *)object_get_and_verify_type(object, 0x100);
  char *tag = (char *)tag_get(*(int *)dev, 0x6374726c);

  if (*(int16_t *)(tag + 0x292) == 0)
    control_toggle(object);
}

void FUN_00095930(int object)
{
  char *dev = (char *)object_get_and_verify_type(object, 0x100);
  char *tag = (char *)tag_get(*(int *)dev, 0x6374726c);

  if (*(int16_t *)(tag + 0x292) == 1)
    control_toggle(object);
}

void FUN_000959b0(int object, void *ctrl)
{
  char *dev = (char *)object_get_and_verify_type(object, 0x200);

  tag_get(*(int *)dev, 0x6c696669);
  FUN_00097080(object, (char *)ctrl + 0x28);
  *(int *)(dev + 0x1c4) = *(int *)((char *)ctrl + 0x30);
  *(int *)(dev + 0x1c8) = *(int *)((char *)ctrl + 0x34);
  *(int *)(dev + 0x1cc) = *(int *)((char *)ctrl + 0x38);
  *(int *)(dev + 0x1d0) = *(int *)((char *)ctrl + 0x3c);
  *(int *)(dev + 0x1d4) = *(int *)((char *)ctrl + 0x40);
  *(int *)(dev + 0x1d8) = *(int *)((char *)ctrl + 0x44);
}

char FUN_00095a20(int object)
{
  char *dev = (char *)object_get_and_verify_type(object, 0x200);

  tag_get(*(int *)dev, 0x6c696669);
  return 1;
}

char FUN_00095a60(int object)
{
  char *dev = (char *)object_get_and_verify_type(object, 0x200);

  tag_get(*(int *)dev, 0x6c696669);
  return 1;
}

void FUN_00095ad0(int object, void *ctrl)
{
  char *dev = (char *)object_get_and_verify_type(object, 0x80);

  FUN_00097080(object, (char *)ctrl + 0x28);
  if ((*(uint8_t *)((char *)ctrl + 0x30) & 1) != 0)
    *(int *)(dev + 0x1c4) |= 1;
  if ((*(uint8_t *)((char *)ctrl + 0x30) & 2) != 0)
    *(int *)(dev + 0x1c4) |= 2;
  if ((*(uint8_t *)((char *)ctrl + 0x30) & 4) != 0)
    *(int *)(dev + 0x1c4) |= 4;
  if ((*(uint8_t *)((char *)ctrl + 0x30) & 8) != 0)
    *(int *)(dev + 0x1c4) |= 8;
}

char FUN_00095b50(int object)
{
  char *dev = (char *)object_get_and_verify_type(object, 0x80);
  char *tag = (char *)tag_get(*(int *)dev, 0x6d616368);
  int flags = *(int *)(dev + 4);

  flags |= 0x2000;
  if ((*(uint8_t *)(tag + 0x292) & 4) != 0)
    flags |= 0x4000;
  else
    flags &= ~0x4000;
  *(int *)(dev + 4) = flags;
  if ((*(uint8_t *)(tag + 0x292) & 4) != 0)
    *(int *)(dev + 4) |= 0x8000;
  else
    *(int *)(dev + 4) &= ~0x8000;
  return 1;
}

void FUN_00095be0(int object)
{
  char *dev = (char *)object_get_and_verify_type(object, 0x80);

  tag_get(*(int *)dev, 0x6d616368);
}

void FUN_00095c10(int object)
{
  char *dev = (char *)object_get_and_verify_type(object, 0x80);

  tag_get(*(int *)dev, 0x6d616368);
  if ((*(uint8_t *)(dev + 0x1c4) & 8) != 0)
    FUN_00097040(object, 1.0f);
}
/* --- recorded_animations.obj batch2 drafts (2026-07-26) --- */

void angles_to_vector(float *out, float *angles);

#define RA_EVENT_ASSERT(line, msg) \
  do { \
    display_assert((char *)(msg), \
                   "c:\\halo\\SOURCE\\cutscene\\recorded_animations.c", (line), 1); \
    system_exit(-1); \
  } while (0)

static void ra_check_ptr(void *p, int line, void *msg)
{
  if (!p)
    RA_EVENT_ASSERT(line, msg);
}

/* FUN_000942a0 (0x942a0) — XBE naked draft (batch 259). */
#if defined(__clang__)
static void (*const b942a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b942a0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_000942a0(char *out __attribute__((unused)), void *event __attribute__((unused)), int **stream __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_000942a0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x19\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x2690a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000942a0_1:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000942a0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x19\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269480\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000942a0_2:\n\t"
      "cmpw $2, (%%edi)\n\t"
      "je .LFUN_000942a0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x19\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269448\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000942a0_3:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000942a0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x19\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269358\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000942a0_4:\n\t"
      "movb 0x4(%%edi), %%al\n\t"
      "movb %%al, (%%ebx)\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $6, %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b942a0_assert), [exitfn] "m"(b942a0_exitfn)
      : "memory");
}
#else
#error "FUN_000942a0: clang naked draft required"
#endif


/* FUN_00094350 (0x94350) — XBE naked draft (batch 259). */
#if defined(__clang__)
static void (*const b94350_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b94350_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_00094350(char *out __attribute__((unused)), void *event __attribute__((unused)), int **stream __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_00094350_1\n\t"
      "pushl $1\n\t"
      "pushl $0x1a\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x2690a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00094350_1:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00094350_2\n\t"
      "pushl $1\n\t"
      "pushl $0x1a\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269480\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00094350_2:\n\t"
      "cmpw $3, (%%edi)\n\t"
      "je .LFUN_00094350_3\n\t"
      "pushl $1\n\t"
      "pushl $0x1a\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x2694cc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00094350_3:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00094350_4\n\t"
      "pushl $1\n\t"
      "pushl $0x1a\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269358\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00094350_4:\n\t"
      "movb 0x4(%%edi), %%al\n\t"
      "movb %%al, 0x1(%%ebx)\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $6, %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b94350_assert), [exitfn] "m"(b94350_exitfn)
      : "memory");
}
#else
#error "FUN_00094350: clang naked draft required"
#endif


/* FUN_00094400 (0x94400) — XBE naked draft (batch 259). */
#if defined(__clang__)
static void (*const b94400_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b94400_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_00094400(char *out __attribute__((unused)), void *event __attribute__((unused)), int **stream __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_00094400_1\n\t"
      "pushl $1\n\t"
      "pushl $0x1b\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x2690a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00094400_1:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00094400_2\n\t"
      "pushl $1\n\t"
      "pushl $0x1b\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269480\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00094400_2:\n\t"
      "cmpw $4, (%%edi)\n\t"
      "je .LFUN_00094400_3\n\t"
      "pushl $1\n\t"
      "pushl $0x1b\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269500\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00094400_3:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00094400_4\n\t"
      "pushl $1\n\t"
      "pushl $0x1b\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269358\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00094400_4:\n\t"
      "movw 0x4(%%edi), %%ax\n\t"
      "movw %%ax, 0x2(%%ebx)\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $6, %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b94400_assert), [exitfn] "m"(b94400_exitfn)
      : "memory");
}
#else
#error "FUN_00094400: clang naked draft required"
#endif


/* FUN_000944b0 (0x944b0) — XBE naked draft (batch 259). */
#if defined(__clang__)
static void (*const b944b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b944b0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_000944b0(char *out __attribute__((unused)), void *event __attribute__((unused)), int **stream __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_000944b0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x1c\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x2690a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000944b0_1:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000944b0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x1c\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269480\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000944b0_2:\n\t"
      "cmpw $5, (%%edi)\n\t"
      "je .LFUN_000944b0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x1c\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269534\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000944b0_3:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000944b0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x1c\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269358\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000944b0_4:\n\t"
      "movw 0x4(%%edi), %%ax\n\t"
      "movw %%ax, 0x4(%%ebx)\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $6, %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b944b0_assert), [exitfn] "m"(b944b0_exitfn)
      : "memory");
}
#else
#error "FUN_000944b0: clang naked draft required"
#endif


void FUN_00094560(char *out, void *event, int **stream)
{
  ra_check_ptr(out, 0x21, (void *)0x2690a0);
  ra_check_ptr(event, 0x22, (void *)0x269480);
  if (*(int16_t *)event != 6)
    RA_EVENT_ASSERT(0x23, (void *)0x269568);
  ra_check_ptr(stream, 0x24, (void *)0x269358);
  *(int *)(out + 0xc) = *(int *)((char *)event + 4);
  *(int *)(out + 0x10) = *(int *)((char *)event + 8);
  *(int *)(out + 0x14) = 0;
  **stream += 0xc;
}

/* apply_facing_vector (0x94620) — XBE naked draft (batch 257). */
#if defined(__clang__)
static void (*const b94620_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b94620_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void apply_facing_vector(char *thread __attribute__((unused)), void *event __attribute__((unused)), int **stream __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .Lapply_facing_vector_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2c\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x2690a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lapply_facing_vector_1:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lapply_facing_vector_2\n\t"
      "pushl $1\n\t"
      "pushl $0x2c\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269480\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lapply_facing_vector_2:\n\t"
      "cmpw $9, (%%edi)\n\t"
      "je .Lapply_facing_vector_3\n\t"
      "pushl $1\n\t"
      "pushl $0x2c\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269598\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lapply_facing_vector_3:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lapply_facing_vector_4\n\t"
      "pushl $1\n\t"
      "pushl $0x2c\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269358\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lapply_facing_vector_4:\n\t"
      "addl $4, %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "addl $0x1c, %%ebx\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x4(%%ebx)\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl %%edx, 0x8(%%ebx)\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0x10, %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b94620_assert), [exitfn] "m"(b94620_exitfn)
      : "memory");
}
#else
#error "apply_facing_vector: clang naked draft required"
#endif


/* apply_aiming_vector (0x946e0) — XBE naked draft (batch 257). */
#if defined(__clang__)
static void (*const b946e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b946e0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void apply_aiming_vector(char *thread __attribute__((unused)), void *event __attribute__((unused)), int **stream __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .Lapply_aiming_vector_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2d\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x2690a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lapply_aiming_vector_1:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lapply_aiming_vector_2\n\t"
      "pushl $1\n\t"
      "pushl $0x2d\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269480\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lapply_aiming_vector_2:\n\t"
      "cmpw $0xa, (%%edi)\n\t"
      "je .Lapply_aiming_vector_3\n\t"
      "pushl $1\n\t"
      "pushl $0x2d\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x2695cc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lapply_aiming_vector_3:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lapply_aiming_vector_4\n\t"
      "pushl $1\n\t"
      "pushl $0x2d\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269358\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lapply_aiming_vector_4:\n\t"
      "addl $4, %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "addl $0x28, %%ebx\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x4(%%ebx)\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl %%edx, 0x8(%%ebx)\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0x10, %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b946e0_assert), [exitfn] "m"(b946e0_exitfn)
      : "memory");
}
#else
#error "apply_aiming_vector: clang naked draft required"
#endif


/* apply_looking_vector (0x947a0) — XBE naked draft (batch 257). */
#if defined(__clang__)
static void (*const b947a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b947a0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void apply_looking_vector(char *thread __attribute__((unused)), void *event __attribute__((unused)), int **stream __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .Lapply_looking_vector_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2e\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x2690a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lapply_looking_vector_1:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lapply_looking_vector_2\n\t"
      "pushl $1\n\t"
      "pushl $0x2e\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269480\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lapply_looking_vector_2:\n\t"
      "cmpw $0xb, (%%edi)\n\t"
      "je .Lapply_looking_vector_3\n\t"
      "pushl $1\n\t"
      "pushl $0x2e\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269600\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lapply_looking_vector_3:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lapply_looking_vector_4\n\t"
      "pushl $1\n\t"
      "pushl $0x2e\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269358\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lapply_looking_vector_4:\n\t"
      "addl $4, %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "addl $0x34, %%ebx\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x4(%%ebx)\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl %%edx, 0x8(%%ebx)\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0x10, %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b947a0_assert), [exitfn] "m"(b947a0_exitfn)
      : "memory");
}
#else
#error "apply_looking_vector: clang naked draft required"
#endif


/* apply_angle_vector (0x94860) — XBE naked draft (batch 249). */
#if defined(__clang__)
static void (*const b94860_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b94860_exitfn)(int) = system_exit;
static void (*const b94860_c10cc40)(float *out, float *angles) = angles_to_vector;

__attribute__((naked, noinline))
void apply_angle_vector(char *thread __attribute__((unused)), void *event __attribute__((unused)), int **stream __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lapply_angle_vector_1\n\t"
      "pushl $1\n\t"
      "pushl $0x38\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x2690a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lapply_angle_vector_1:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .Lapply_angle_vector_2\n\t"
      "pushl $1\n\t"
      "pushl $0x39\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269480\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lapply_angle_vector_2:\n\t"
      "movw (%%ebx), %%ax\n\t"
      "cmpw $0x10, %%ax\n\t"
      "jl .Lapply_angle_vector_3\n\t"
      "cmpw $0x16, %%ax\n\t"
      "jle .Lapply_angle_vector_4\n\t"
      ".Lapply_angle_vector_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x3a\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269638\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lapply_angle_vector_4:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lapply_angle_vector_5\n\t"
      "pushl $1\n\t"
      "pushl $0x3b\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269358\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lapply_angle_vector_5:\n\t"
      "leal 0x4(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10cc40]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0x15, (%%ebx)\n\t"
      "je .Lapply_angle_vector_6\n\t"
      "leal 0x1c(%%edi), %%ebx\n\t"
      "movl %%edx, (%%ebx)\n\t"
      "movl %%ecx, 0x4(%%ebx)\n\t"
      "movl %%eax, 0x8(%%ebx)\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      ".Lapply_angle_vector_6:\n\t"
      "cmpw $0x14, (%%ebx)\n\t"
      "je .Lapply_angle_vector_7\n\t"
      "leal 0x28(%%edi), %%ebx\n\t"
      "movl %%edx, (%%ebx)\n\t"
      "movl %%ecx, 0x4(%%ebx)\n\t"
      "movl %%eax, 0x8(%%ebx)\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      ".Lapply_angle_vector_7:\n\t"
      "cmpw $0x13, (%%ebx)\n\t"
      "je .Lapply_angle_vector_8\n\t"
      "addl $0x34, %%edi\n\t"
      "movl %%edx, (%%edi)\n\t"
      "movl %%ecx, 0x4(%%edi)\n\t"
      "movl %%eax, 0x8(%%edi)\n\t"
      ".Lapply_angle_vector_8:\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0xc, %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b94860_assert), [exitfn] "m"(b94860_exitfn), [c10cc40] "m"(b94860_c10cc40)
      : "memory");
}
#else
#error "apply_angle_vector: clang naked draft required"
#endif


/* apply_multi_vector (0x94970) — XBE naked draft (batch 251). */
#if defined(__clang__)
static void (*const b94970_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b94970_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void apply_multi_vector(char *thread __attribute__((unused)), void *event __attribute__((unused)), int **stream __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .Lapply_multi_vector_1\n\t"
      "pushl $1\n\t"
      "pushl $0x56\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x2690a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lapply_multi_vector_1:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lapply_multi_vector_2\n\t"
      "pushl $1\n\t"
      "pushl $0x57\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269480\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lapply_multi_vector_2:\n\t"
      "movw (%%esi), %%ax\n\t"
      "cmpw $0xc, %%ax\n\t"
      "jl .Lapply_multi_vector_3\n\t"
      "cmpw $0xf, %%ax\n\t"
      "jle .Lapply_multi_vector_4\n\t"
      ".Lapply_multi_vector_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x58\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x2696b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lapply_multi_vector_4:\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lapply_multi_vector_5\n\t"
      "pushl $1\n\t"
      "pushl $0x59\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269358\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lapply_multi_vector_5:\n\t"
      "cmpw $0xe, (%%esi)\n\t"
      "je .Lapply_multi_vector_6\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0x1c(%%ebx), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      ".Lapply_multi_vector_6:\n\t"
      "cmpw $0xd, (%%esi)\n\t"
      "je .Lapply_multi_vector_7\n\t"
      "leal 0x4(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "leal 0x28(%%ebx), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      ".Lapply_multi_vector_7:\n\t"
      "cmpw $0xc, (%%esi)\n\t"
      "je .Lapply_multi_vector_8\n\t"
      "addl $4, %%esi\n\t"
      "movl (%%esi), %%edx\n\t"
      "addl $0x34, %%ebx\n\t"
      "movl %%edx, (%%ebx)\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl %%eax, 0x4(%%ebx)\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x8(%%ebx)\n\t"
      ".Lapply_multi_vector_8:\n\t"
      "addl $0x10, (%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b94970_assert), [exitfn] "m"(b94970_exitfn)
      : "memory");
}
#else
#error "apply_multi_vector: clang naked draft required"
#endif


char recorded_animation_apply_event_stream_v1(char *thread, void *event, int *ticks,
                                            int **cursor)
{
  ra_check_ptr(thread, 0xa2, (void *)0x2690a0);
  ra_check_ptr(ticks, 0xa3, (void *)0x269368);
  ra_check_ptr(cursor, 0xa4, (void *)0x269358);
  if (**cursor == 0)
    RA_EVENT_ASSERT(0xa5, (void *)0x269344);
  {
    char *evt = *(char **)*cursor;
    while (*ticks >= *(int16_t *)(evt + 2)) {
      int16_t type = *(int16_t *)evt;
      if (type == 1) {
        if (*ticks == *(int16_t *)(evt + 2))
          return 0;
        return 1;
      }
      {
        void *handler =
            *(void **)((char *)0x2eea70 + (int)type * 4);
        if (handler != NULL)
          ((void (*)(void *, char *, int **))handler)(event, evt, cursor);
        else
          **cursor = (int)((char *)evt + 4);
      }
      *ticks -= *(int16_t *)(evt + 2);
      evt = *(char **)*cursor;
    }
    if (*(int16_t *)evt == 1 && *ticks == *(int16_t *)(evt + 2))
      return 0;
  }
  return 1;
}

void recorded_animation_verify(char *anim)
{
  char buf[0x58];
  char scratch[0x18];
  int stream_end;
  int stream_pos;
  int stream_len;
  int index;
  int16_t count;
  char ok;
  void **vtable;
  int type;

  stream_end = *(int *)(anim + 0x38);
  stream_pos = stream_end;
  stream_len = *(int *)(anim + 0x2c);
  type = *(uint8_t *)(anim + 0x20);
  vtable = *(void ***)((char *)0x2eebac + type * 4);
  count = *(int16_t *)(anim + 0x24);
  index = 0;
  ((void (*)(char *, char *, int *, int *))vtable[0])(
      buf, scratch, &stream_pos, &stream_end);
  for (;;) {
    ok = ((char (*)(char *, int *, char *, char *))vtable[1])(
        buf, &index, scratch, anim + 0x18);
    if (count < 0) {
      display_assert((char *)0x2698f4,
                     "c:\\halo\\SOURCE\\cutscene\\recorded_animations.c", 0x1ac,
                     1);
      system_exit(-1);
    }
    if (index < 0) {
      display_assert((char *)0x2698e0,
                     "c:\\halo\\SOURCE\\cutscene\\recorded_animations.c", 0x1ad,
                     1);
      system_exit(-1);
    }
    if (stream_pos - stream_end < stream_len || (stream_pos - stream_end == stream_len && !ok)) {
      display_assert((char *)0x269898,
                     "c:\\halo\\SOURCE\\cutscene\\recorded_animations.c", 0x1ae,
                     1);
      system_exit(-1);
    }
    index++;
    if (!ok)
      break;
  }
}

#undef RA_EVENT_ASSERT
/* --- recorded_animations.obj batch3 drafts (2026-07-26) --- */

#define RA3_EVENT_ASSERT(line, msg) \
  do { \
    display_assert((char *)(msg), \
                   "c:\\halo\\SOURCE\\cutscene\\recorded_animations.c", (line), 1); \
    system_exit(-1); \
  } while (0)

static void ra3_check_ptr(void *p, int line, void *msg)
{
  if (!p)
    RA3_EVENT_ASSERT(line, msg);
}

char FUN_000940a0(char *thread, void *event, int *ticks, int **cursor)
{
  uint8_t *evt;
  uint16_t tick_amount;
  int cursor_advance;
  void *handler;

  ra3_check_ptr(thread, 0x113, (void *)0x2690a0);
  ra3_check_ptr(event, 0x114, (void *)0x269368);
  ra3_check_ptr(ticks, 0x115, (void *)0x269358);
  ra3_check_ptr(cursor, 0x115, (void *)0x269358);
  if (**cursor == 0)
    RA3_EVENT_ASSERT(0x116, (void *)0x269344);

  evt = (uint8_t *)**cursor;
  for (;;) {
    uint8_t header = evt[0];
    uint8_t type_low = header & 3;

    switch (type_low) {
    case 0:
      tick_amount = 0;
      cursor_advance = 1;
      break;
    case 1:
      tick_amount = 1;
      cursor_advance = 1;
      break;
    case 2:
      tick_amount = evt[1];
      cursor_advance = 2;
      if (tick_amount <= 1)
        RA3_EVENT_ASSERT(0x12d, (void *)0x269318);
      break;
    case 3:
      tick_amount = *(uint16_t *)(evt + 1);
      cursor_advance = 3;
      if (tick_amount <= 0xff)
        RA3_EVENT_ASSERT(0x132, (void *)0x2692f8);
      break;
    default:
      RA3_EVENT_ASSERT(0x135, (void *)0x255ee8);
    }

    if (*ticks < tick_amount)
      goto stream_done;
    if ((header & 0xfc) == 4)
      goto stream_done;

    **cursor = (int)((char *)**cursor + cursor_advance);

    if ((header & 0xfc) >= 0x5c)
      RA3_EVENT_ASSERT(0x13b, (void *)0x2692cc);

    handler = *(void **)((char *)0x2ee960 + (header >> 2) * 4);
    if (handler != NULL)
      ((void (*)(char *, void *, int **))handler)(thread, evt, cursor);

    *ticks -= tick_amount;
    evt = (uint8_t *)**cursor;
  }

stream_done:
  if ((evt[0] & 0xfc) == 4 && *ticks == tick_amount)
    return 0;
  return 1;
}

void render_debug_recording(void)
{
  char buffer[0x2818];
  int16_t tab_stops[2];
  data_iter_t iter;
  char *thread;
  int out_len;
  int16_t line;
  char *dbg_slot;
  void *unit;
  scenario_t *scenario;
  char *anim_name;
  char *default_name;

  if (*(uint8_t *)0x44df08 == 0)
    return;

  out_len = 0;
  tab_stops[0] = 0xc8;
  tab_stops[1] = 0x12c;

  for (line = 0; line < *(int16_t *)0x2eebc0; line++) {
    out_len += crt_sprintf(buffer + out_len, (char *)0x26993c, line);
  }
  out_len += crt_sprintf(buffer + out_len, (char *)0x269914);

  data_iterator_new(&iter, *(data_t **)0x44df04);
  thread = (char *)data_iterator_next(&iter);
  while (thread != NULL) {
    unit = object_try_and_get_and_verify_type(*(int *)(thread + 4), -1);
    dbg_slot = (char *)((iter.datum_handle & 0xffff) * 0x10 + *(int *)0x44df0c);
    if ((*(uint8_t *)(thread + 0xa) & 1) == 0 && unit != NULL &&
        *(int16_t *)((char *)unit + 0x6a) != -1) {
      scenario = global_scenario_get();
      anim_name = (char *)tag_block_get_element((char *)scenario + 0x204,
                                                *(int16_t *)((char *)unit + 0x6a),
                                                0x24);
      default_name = (char *)0x25b724;
      if (*dbg_slot != 0) {
        default_name = (char *)tag_block_get_element((char *)scenario + 0x36c,
                                                     *(int16_t *)(dbg_slot + 0xc),
                                                     0x40);
      }
      out_len += crt_sprintf(buffer + out_len, (char *)0x26990c, default_name);
      out_len += crt_sprintf(buffer + out_len, (char *)0x269904,
                             *(uint16_t *)(thread + 8));
      out_len += crt_sprintf(buffer + out_len, (char *)0x257984, anim_name);
    }
    thread = (char *)data_iterator_next(&iter);
  }

  buffer[out_len] = 0;
  draw_string_set_tab_stops(tab_stops, 2);
  FUN_00189c40(1, buffer);
  draw_string_set_tab_stops(tab_stops, 0);
}

/* recorded_animation_play_internal (0x95330) — XBE naked draft (batch 259). */
#if defined(__clang__)
static scenario_t * (*const b95330_c18e380)(void) = global_scenario_get;
static void *(*const b95330_get)(int, int) = object_get_and_verify_type;
static int (*const b95330_cba500)(int) = player_index_from_unit_index;
static void (*const b95330_c95050)(int unit, int *out) = FUN_00095050;
static void *(*const b95330_elem)(void *, int, int) = tag_block_get_element;
static char (*const b95330_c94ff0)(int unit_handle) = recorded_animation_controlling_unit;
static int (*const b95330_c119610)(data_t *data) = data_new_at_index;
static void *(*const b95330_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b95330_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b95330_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b95330_exitfn)(int) = system_exit;
static void * (*const b95330_c19b1a0)(void *tag_data, int offset, int size) = tag_data_get_pointer;
static void (*const b95330_c1adf10)(int unit_handle, char param_2) = unit_set_actively_controlled;
static bool (*const b95330_c1a9a30)(int unit_handle) = unit_is_alive;
static void (*const b95330_c1a9a50)(int unit_handle, char controllable) = unit_set_controllable;
static void (*const b95330_c1a9a90)(int unit_handle, char possessed) = unit_set_possessed;
static void (*const b95330_c13ff50)(int object_handle, char param_2) = object_set_automatic_deactivation;

__attribute__((naked, noinline))
char recorded_animation_play_internal(int unit __attribute__((unused)), int anim __attribute__((unused)), int flags __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpl $-1, %%edi\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "je .Lrecorded_animation_play_internal_12\n\t"
      "movw 0x8(%%ebp), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lrecorded_animation_play_internal_11\n\t"
      "movswl %%ax, %%esi\n\t"
      "call *%[c18e380]\n\t"
      "cmpl 0x36c(%%eax), %%esi\n\t"
      "jge .Lrecorded_animation_play_internal_11\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "pushl %%edi\n\t"
      "call *%[cba500]\n\t"
      "addl $0xc, %%esp\n\t"
      "leal -0xc(%%ebp), %%ebx\n\t"
      "call *%[c95050]\n\t"
      "pushl $0x40\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x36c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "call *%[c94ff0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrecorded_animation_play_internal_8\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .Lrecorded_animation_play_internal_2\n\t"
      "movl 0x44df04, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119610]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lrecorded_animation_play_internal_1\n\t"
      "movl 0x44df04, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .Lrecorded_animation_play_internal_3\n\t"
      ".Lrecorded_animation_play_internal_1:\n\t"
      "pushl $0x269a2c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrecorded_animation_play_internal_2:\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      ".Lrecorded_animation_play_internal_3:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movb 0x20(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jbe .Lrecorded_animation_play_internal_4\n\t"
      "cmpb $4, %%cl\n\t"
      "ja .Lrecorded_animation_play_internal_4\n\t"
      "movzbl %%cl, %%edx\n\t"
      "movl 0x2eebac(,%%edx,4), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .Lrecorded_animation_play_internal_5\n\t"
      ".Lrecorded_animation_play_internal_4:\n\t"
      "pushl $1\n\t"
      "pushl $0xe9\n\t"
      "pushl $0x269764\n\t"
      "pushl $0x2699c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrecorded_animation_play_internal_5:\n\t"
      "movl %%edi, 0x4(%%ebx)\n\t"
      "movl $0, 0xc(%%ebx)\n\t"
      "movw 0x24(%%eax), %%cx\n\t"
      "addl $0x2c, %%eax\n\t"
      "movw %%cx, 0x8(%%ebx)\n\t"
      "movl (%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b1a0]\n\t"
      "movl 0x44df0c, %%edx\n\t"
      "movl %%eax, 0x10(%%ebx)\n\t"
      "andl $0xffff, %%esi\n\t"
      "leal 0x10(%%ebx), %%ecx\n\t"
      "shll $4, %%esi\n\t"
      "addl %%edx, %%esi\n\t"
      "movb $1, (%%esi)\n\t"
      "movl (%%ecx), %%eax\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x2c(%%eax), %%edx\n\t"
      "addl $0x2c, %%eax\n\t"
      "movw 0x8(%%ebp), %%ax\n\t"
      "movw %%ax, 0xc(%%esi)\n\t"
      "movl %%edx, 0x8(%%esi)\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movzbw 0x20(%%esi), %%dx\n\t"
      "andb $0xfe, 0xa(%%ebx)\n\t"
      "decl %%edx\n\t"
      "movswl %%dx, %%eax\n\t"
      "movw %%dx, 0x60(%%ebx)\n\t"
      "movl 0x2eebb0(,%%eax,4), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x22(%%esi), %%al\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal 0x14(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x54(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *(%%edx)\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[c1adf10]\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a9a30]\n\t"
      "addl $0x28, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrecorded_animation_play_internal_6\n\t"
      "orb $4, 0xa(%%ebx)\n\t"
      "jmp .Lrecorded_animation_play_internal_7\n\t"
      ".Lrecorded_animation_play_internal_6:\n\t"
      "andb $0xfb, 0xa(%%ebx)\n\t"
      ".Lrecorded_animation_play_internal_7:\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a9a50]\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a9a90]\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c13ff50]\n\t"
      "movw 0xc(%%ebp), %%cx\n\t"
      "addl $0x18, %%esp\n\t"
      "orw %%cx, 0xa(%%ebx)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrecorded_animation_play_internal_8:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .Lrecorded_animation_play_internal_10\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl 0x44df0c, %%edi\n\t"
      "andl $0xffff, %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "movb (%%ecx,%%edi,1), %%dl\n\t"
      "addl %%edi, %%ecx\n\t"
      "testb %%dl, %%dl\n\t"
      "movl $0x25b724, %%eax\n\t"
      "je .Lrecorded_animation_play_internal_9\n\t"
      "movswl 0xc(%%ecx), %%edx\n\t"
      "pushl $0x40\n\t"
      "pushl %%edx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x36c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lrecorded_animation_play_internal_9:\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $0x269994\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrecorded_animation_play_internal_10:\n\t"
      "pushl $0x269974\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrecorded_animation_play_internal_11:\n\t"
      "pushl $0x269954\n\t"
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
      ".Lrecorded_animation_play_internal_12:\n\t"
      "pushl $0x269940\n\t"
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
      : [c18e380] "m"(b95330_c18e380), [get] "m"(b95330_get), [cba500] "m"(b95330_cba500), [c95050] "m"(b95330_c95050), [elem] "m"(b95330_elem), [c94ff0] "m"(b95330_c94ff0), [c119610] "m"(b95330_c119610), [dget] "m"(b95330_dget), [c8f390] "m"(b95330_c8f390), [assert] "m"(b95330_assert), [exitfn] "m"(b95330_exitfn), [c19b1a0] "m"(b95330_c19b1a0), [c1adf10] "m"(b95330_c1adf10), [c1a9a30] "m"(b95330_c1a9a30), [c1a9a50] "m"(b95330_c1a9a50), [c1a9a90] "m"(b95330_c1a9a90), [c13ff50] "m"(b95330_c13ff50)
      : "memory");
}
#else
#error "recorded_animation_play_internal: clang naked draft required"
#endif


void control_toggle(int object)
{
  char *dev;
  char *tag;
  void *recording;
  float value;
  int16_t control_type;
  int16_t recording_index;

  dev = (char *)object_get_and_verify_type(object, 0x100);
  tag = (char *)tag_get(0x6374726c, *(int *)dev);
  recording_index = *(int16_t *)(dev + 0x1b4);
  if (recording_index == -1)
    return;

  recording = datum_get(*(data_t **)0x5aa8c8, recording_index);
  control_type = *(int16_t *)(tag + 0x290);
  if (control_type > 3) {
    display_assert((char *)0,
                   "c:\\halo\\SOURCE\\cutscene\\recorded_animations.c", 0x8a,
                   1);
    system_exit(-1);
  }

  switch (control_type) {
  case 0:
    if (*(float *)((char *)recording + 4) == *(float *)0x253398)
      value = 0.0f;
    else
      value = 1.0f;
    break;
  case 1:
    value = 1.0f;
    break;
  case 2:
    value = 0.0f;
    break;
  default:
    value = *(float *)(tag + 0x294);
    break;
  }

  if (FUN_00096f20(recording_index, value) == 0) {
    FUN_000967a0(*(void **)(tag + 0x314), object);
    return;
  }

  if (value == *(float *)0x253398)
    FUN_000967a0(*(void **)(tag + 0x2f4), object);
  else
    FUN_000967a0(*(void **)(tag + 0x304), object);
}

char FUN_00095c60(int object)
{
  int handles[0x10];
  int *big_handles;
  char *dev;
  char *tag;
  float radius;
  int16_t count;
  int i;
  char triggered;
  char *other;
  char *other_tag;
  char valid_target;
  void *node_matrix;
  float delta[3];
  float pos[3];

  dev = (char *)object_get_and_verify_type(object, 0x80);
  tag = (char *)tag_get(0x6d616368, *(int *)dev);

  if (*(int16_t *)(tag + 0x290) == 2) {
    float mix;
    float new_val;

    mix = *(float *)0x2533c8 - *(float *)(dev + 0x1ac);
    new_val = *(float *)(tag + 0x288) * *(float *)(dev + 0x1ac) +
              *(float *)(tag + 0x280) * mix + *(float *)(dev + 0x1b8);
    *(float *)(dev + 0x1b8) = new_val;
    if (new_val >= *(float *)0x2533c8)
      *(float *)(dev + 0x1b8) -= *(float *)0x2533c8;

    *(int *)(dev + 4) |= 4;
    *(int *)(dev + 0x1bc) = 0;
    if (*(int16_t *)(dev + 0x1b4) != -1) {
      void *recording =
          datum_get(*(data_t **)0x5aa8c8, *(int16_t *)(dev + 0x1b4));
      *(float *)((char *)recording + 4) = *(float *)(dev + 0x1b8);
    }
  }

  if ((*(uint8_t *)(dev + 0x1c4) & 1) != 0)
    goto finish;

  if (*(int16_t *)(tag + 0x290) == 0) {
    if (((game_time_get() + object) & 3) == 0) {
      if (*(float *)(tag + 0x21c) >= *(float *)0x253f44)
        radius = *(float *)(dev + 0x5c);
      else
        radius = *(float *)(tag + 0x21c);

      triggered = 0;
      count = object_find_in_radius(1, 1, dev + 0x48, (float *)(dev + 0x50),
                                    radius, handles, 0x10);
      if (count > 0) {
        for (i = 0; i < count; i++) {
          other = (char *)object_get_and_verify_type(handles[i], 3);
          other_tag = (char *)tag_get(0x756e6974, *(int *)other);
          valid_target = 1;
          if ((*(uint8_t *)(other + 0xb6) & 4) != 0 ||
              (*(uint8_t *)(other_tag + 0x17c) & 0x40) == 0)
            valid_target = 0;

          if ((*(uint8_t *)(dev + 0x1c4) & 2) != 0 &&
              *(float *)(dev + 0x1b8) > *(float *)0x2533c0 &&
              game_allegiance_get_team_is_friendly(1, *(int16_t *)(other + 0x68)) ==
                  0) {
            float facing;

            facing = (*(float *)(other + 0x50) - *(float *)(dev + 0x50)) *
                         *(float *)(dev + 0x28) +
                     (*(float *)(other + 0x54) - *(float *)(dev + 0x54)) *
                         *(float *)(dev + 0x2c) +
                     (*(float *)(other + 0x58) - *(float *)(dev + 0x58)) *
                         *(float *)(dev + 0x24);
            if (facing <= *(float *)0x2533c0)
              valid_target = 0;
          }

          if (valid_target != 0)
            triggered = 1;
        }
      }

      if (triggered != 0) {
        if (*(int16_t *)(dev + 0x1b4) != -1)
          FUN_00096f20(*(int16_t *)(dev + 0x1b4), 1.0f);
        *(int *)(dev + 0x1c8) = -3;
      }
    }

    if (*(float *)(dev + 0x1b8) == 1.0f) {
      *(int *)(dev + 0x1c8) = *(int *)(dev + 0x1c8) + 1;
      if (*(int *)(dev + 0x1c8) > *(int *)(tag + 0x320) &&
          *(int16_t *)(dev + 0x1b4) != -1)
        FUN_00096f20(*(int16_t *)(dev + 0x1b4), 0.0f);
    } else {
      *(int *)(dev + 0x1c8) = 0;
    }
  }

  if ((*(uint8_t *)(tag + 0x292) & 4) != 0 &&
      *(int16_t *)(tag + 0x2ea) != -1) {
    int j;
    int16_t attached_count;
    char scratch[0x2068];

    node_matrix = object_get_node_matrix(object, *(int16_t *)(tag + 0x2ea));
    delta[0] = *(float *)((char *)node_matrix + 0x28) - *(float *)(dev + 0x1cc);
    delta[1] = *(float *)((char *)node_matrix + 0x2c) - *(float *)(dev + 0x1d0);
    delta[2] = *(float *)((char *)node_matrix + 0x30) - *(float *)(dev + 0x1d4);
    if (!(delta[0] == 0.0f && delta[1] == 0.0f && delta[2] == 0.0f)) {
      big_handles = (int *)scratch;
      attached_count = object_find_in_radius(
          1, 1, dev + 0x48, (float *)(dev + 0x50), *(float *)(dev + 0x5c),
          big_handles, 0x800);
      if (attached_count > 0) {
        for (j = 0; j < attached_count; j++) {
          other = (char *)object_get_and_verify_type(big_handles[j], 1);
          if (*(int *)(other + 0x42c) == object) {
            pos[0] = delta[0] + *(float *)(other + 0xc);
            pos[1] = delta[1] + *(float *)(other + 0x10);
            pos[2] = delta[2] + *(float *)(other + 0x14);
            object_translate(big_handles[j], pos, NULL);
          }
        }
      }
    }

    *(float *)(dev + 0x1cc) = *(float *)((char *)node_matrix + 0x28);
    *(float *)(dev + 0x1d0) = *(float *)((char *)node_matrix + 0x2c);
    *(float *)(dev + 0x1d4) = *(float *)((char *)node_matrix + 0x30);
  }

  if ((*(uint8_t *)(dev + 0x1a4) & 4) != 0) {
    object_translate(object, (float *)(dev + 0xc), NULL);
    *(int *)(dev + 0x1a4) &= ~4;
  }

finish:
  return 1;
}

#undef RA3_EVENT_ASSERT
/* --- recorded_animations.obj orphan shells (2026-07-26) --- */

/* orphan 0x95640 */
char recorded_animation_play(int actor, short anim_idx)
{
  recorded_animation_play_internal(0, 0, 0);
  return 0;
}
