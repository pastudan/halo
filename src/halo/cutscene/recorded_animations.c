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

/* FUN_00094020 (0x94020) — readable C lift: stream helper + read vec3. */
void FUN_00094020(int *out, int a, int *cursor, int c)
{
  int *p;

  FUN_00093780(a, cursor, c);
  p = (int *)*cursor;
  out[0] = p[0];
  out[1] = p[1];
  out[2] = p[2];
  *cursor = (int)(p + 3);
}

/* FUN_00094060 (0x94060) — readable C lift: copy 64-byte block + vec3 from stream. */
void FUN_00094060(int *out, void *dest64, int *cursor)
{
  int *src;
  int *p;
  int i;

  src = (int *)*cursor;
  for (i = 0; i < 16; i++)
    ((int *)dest64)[i] = src[i];
  *cursor = (int)(src + 16);
  p = (int *)*cursor;
  out[0] = p[0];
  out[1] = p[1];
  out[2] = p[2];
  *cursor = (int)(p + 3);
}

void FUN_00094290(void *a, void *b, int c)
{
  (void)a;
  (void)b;
  (void)c;
  /* relift: no calls detected — manual review */
}

/* FUN_00094a70 (0x94a70) — readable C lift (thin wrapper). */
void FUN_00094a70(int a, int *cursor, int c)
{
  FUN_00093780(a, cursor, c);
}

void FUN_00094ba0(void *a, void *b, int c)
{
  (void)a;
  (void)b;
  (void)c;
  /* relift: no calls detected — manual review */
}

/* recorded_animations_clear_debug_storage (0x94c70) — readable C lift. */
void recorded_animations_clear_debug_storage(void)
{
  if (!*(void **)0x44df0c) {
    display_assert((const char *)0x269738, (const char *)0x269764, 0x99, 1);
    system_exit(-1);
  }
  csmemset(*(void **)0x44df0c, 0, 0x400);
}

/* recorded_animation_controlling_unit (0x94ff0) — readable C lift from XBE leaf. */
char recorded_animation_controlling_unit(int unit_handle)
{
  data_iter_t iter;
  char *rec;

  data_iterator_new(&iter, *(data_t **)0x44df04);
  for (rec = (char *)data_iterator_next(&iter); rec;
       rec = (char *)data_iterator_next(&iter)) {
    if (*(int *)(rec + 4) != unit_handle)
      continue;
    if ((*(unsigned char *)(rec + 0xa) & 1) == 0)
      return 1;
  }
  return 0;
}

/* FUN_00095050 (0x95050) — readable C lift from XBE leaf. */
void FUN_00095050(int unit, int *out)
{
  data_iter_t iter;
  void *entry;
  int handle;

  handle = -1;
  data_iterator_new(&iter, *(data_t **)0x44df04);
  for (entry = data_iterator_next(&iter); entry != 0;
       entry = data_iterator_next(&iter)) {
    if (*(int *)((char *)entry + 4) == unit) {
      handle = *(int *)((char *)&iter + 8);
      break;
    }
  }
  if (out != 0) {
    *out = handle;
  }
}




/* recorded_animation_kill (0x952d0) — readable C lift from XBE leaf. */
void recorded_animation_kill(int unit_handle)
{
  data_iter_t iter;
  void *entry;

  data_iterator_new(&iter, *(data_t **)0x44df04);
  for (entry = data_iterator_next(&iter); entry != 0;
       entry = data_iterator_next(&iter)) {
    if (*(int *)((char *)entry + 4) == unit_handle) {
      *(unsigned char *)((char *)entry + 0xa) |= 3;
      return;
    }
  }
}




/* recorded_animation_get_time_left (0x955b0) — XBE naked draft (batch 283). */
#if defined(__clang__)
static void (*const b955b0_c1197b0)(data_iter_t *iter, data_t *data) = data_iterator_new;
static void * (*const b955b0_c119810)(data_iter_t *iterator) = data_iterator_next;
static void (*const b955b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b955b0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
int recorded_animation_get_time_left(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x44df04, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "call *%[c1197b0]\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c119810]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lrecorded_animation_get_time_left_2\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "nop\n\t"
      ".Lrecorded_animation_get_time_left_1:\n\t"
      "cmpl %%edi, 0x4(%%esi)\n\t"
      "je .Lrecorded_animation_get_time_left_3\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119810]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lrecorded_animation_get_time_left_1\n\t"
      ".Lrecorded_animation_get_time_left_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrecorded_animation_get_time_left_3:\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lrecorded_animation_get_time_left_2\n\t"
      "cmpl %%edi, 0x4(%%esi)\n\t"
      "je .Lrecorded_animation_get_time_left_4\n\t"
      "pushl $1\n\t"
      "pushl $0x138\n\t"
      "pushl $0x269764\n\t"
      "pushl $0x269a5c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jne .Lrecorded_animation_get_time_left_2\n\t"
      ".Lrecorded_animation_get_time_left_4:\n\t"
      "movzwl 0x8(%%esi), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1197b0] "m"(b955b0_c1197b0), [c119810] "m"(b955b0_c119810), [assert] "m"(b955b0_assert), [exitfn] "m"(b955b0_exitfn)
      : "memory");
}
#else
#error "recorded_animation_get_time_left: clang naked draft required"
#endif


/* recorded_animation_play_and_delete (0x95660) — readable C lift. */
int recorded_animation_play_and_delete(int unit, int anim)
{
  return recorded_animation_play_internal(unit, anim, 8);
}

/* FUN_00095680 (0x95680) — readable C lift. */
int FUN_00095680(int unit, int anim)
{
  return recorded_animation_play_internal(unit, anim, 0x10);
}

/* FUN_000956e0 (0x956e0) — readable C lift from XBE leaf. */
void FUN_000956e0(int object, void *ctrl)
{
  void *obj;
  void *ctrl_tag;

  obj = object_get_and_verify_type(object, 0x100);
  ctrl_tag = tag_get(0x6374726c, *(int *)obj);
  (void)ctrl_tag;
  FUN_00097080(object, (char *)ctrl + 0x28);
  if ((*(unsigned char *)((char *)ctrl + 0x30) & 1) != 0) {
    *(int *)((char *)obj + 0x1c4) |= 1;
  }
  if ((*(unsigned char *)((char *)ctrl + 0x30) & 0x10) != 0) {
    *(int *)((char *)obj + 0x1c4) |= 2;
  }
  *(short *)((char *)obj + 0x1c8) =
      (short)(*(short *)((char *)ctrl + 0x34) - 1);
}




/* FUN_00095750 (0x95750) — readable C lift. */
char FUN_00095750(int object)
{
  void *obj = object_get_and_verify_type(object, 0x100);
  tag_get(0x6374726c, *(int *)obj);
  return 1;
}

/* FUN_00095790 (0x95790) — readable C lift. */
char FUN_00095790(int object)
{
  void *obj = object_get_and_verify_type(object, 0x100);
  tag_get(0x6374726c, *(int *)obj);
  return 1;
}

/* FUN_000958f0 (0x958f0) — readable C lift. */
void FUN_000958f0(int object, int arg)
{
  void *obj = object_get_and_verify_type(object, 0x100);
  void *tag = tag_get(0x6374726c, *(int *)obj);
  (void)arg;
  if (*(uint16_t *)((char *)tag + 0x292) == (uint16_t)0)
    control_toggle(object);
}

/* FUN_00095930 (0x95930) — readable C lift. */
void FUN_00095930(int object)
{
  void *obj = object_get_and_verify_type(object, 0x100);
  void *tag = tag_get(0x6374726c, *(int *)obj);
  if (*(uint16_t *)((char *)tag + 0x292) == (uint16_t)1)
    control_toggle(object);
}

/* FUN_000959b0 (0x959b0) — readable C lift from XBE leaf. */
void FUN_000959b0(int object, void *ctrl)
{
  void *obj;
  void *life_tag;
  int *src;
  int *dst;

  obj = object_get_and_verify_type(object, 0x200);
  life_tag = tag_get(0x6c696669, *(int *)obj);
  (void)life_tag;
  FUN_00097080(object, (char *)ctrl + 0x28);
  src = (int *)((char *)ctrl + 0x30);
  dst = (int *)((char *)obj + 0x1c4);
  dst[0] = src[0];
  dst[1] = src[1];
  dst[2] = src[2];
  *(int *)((char *)obj + 0x1d0) = *(int *)((char *)ctrl + 0x3c);
  *(int *)((char *)obj + 0x1d4) = *(int *)((char *)ctrl + 0x40);
  *(int *)((char *)obj + 0x1d8) = *(int *)((char *)ctrl + 0x44);
}




/* FUN_00095a20 (0x95a20) — readable C lift. */
char FUN_00095a20(int object)
{
  void *obj = object_get_and_verify_type(object, 0x200);
  tag_get(0x6c696669, *(int *)obj);
  return 1;
}

/* FUN_00095a60 (0x95a60) — readable C lift. */
char FUN_00095a60(int object)
{
  void *obj = object_get_and_verify_type(object, 0x200);
  tag_get(0x6c696669, *(int *)obj);
  return 1;
}

/* FUN_00095ad0 (0x95ad0) — readable C lift from XBE leaf. */
void FUN_00095ad0(int object, void *ctrl)
{
  void *obj;
  unsigned char flags;

  obj = object_get_and_verify_type(object, 0x80);
  FUN_00097080(object, (char *)ctrl + 0x28);
  flags = *(unsigned char *)((char *)ctrl + 0x30);
  if (flags & 1) {
    *(int *)((char *)obj + 0x1c4) |= 1;
  }
  if (flags & 2) {
    *(int *)((char *)obj + 0x1c4) |= 2;
  }
  if (flags & 4) {
    *(int *)((char *)obj + 0x1c4) |= 4;
  }
  if (flags & 8) {
    *(int *)((char *)obj + 0x1c4) |= 8;
  }
}




/* FUN_00095b50 (0x95b50) — readable C lift from XBE leaf. */
char FUN_00095b50(int object)
{
  void *obj;
  void *mach_tag;
  int flags;

  obj = object_get_and_verify_type(object, 0x80);
  mach_tag = tag_get(0x6d616368, *(int *)obj);
  flags = *(int *)((char *)obj + 4) | 0x2000;
  *(int *)((char *)obj + 4) = flags;
  if ((*(unsigned char *)((char *)mach_tag + 0x292) & 4) != 0) {
    flags |= 0x4000;
  } else {
    flags &= ~0x4000;
  }
  *(int *)((char *)obj + 4) = flags;
  flags = *(int *)((char *)obj + 4);
  if ((*(unsigned char *)((char *)mach_tag + 0x292) & 4) != 0) {
    flags |= 0x8000;
  } else {
    flags &= ~0x8000;
  }
  *(int *)((char *)obj + 4) = flags;
  return 1;
}




/* FUN_00095be0 (0x95be0) — readable C lift: resolve object hcam tag. */
void FUN_00095be0(int object)
{
  void *obj;

  obj = object_get_and_verify_type(object, 0x80);
  tag_get(0x6d616368, *(int *)obj);
}

/* FUN_00095c10 (0x95c10) — readable C lift: hcam tag + optional scale. */
void FUN_00095c10(int object)
{
  unsigned char *obj;

  obj = (unsigned char *)object_get_and_verify_type(object, 0x80);
  tag_get(0x6d616368, *(int *)obj);
  if (obj[0x1c4] & 8)
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

static void __attribute__((unused)) ra_check_ptr(void *p, int line, void *msg)
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


/* FUN_00094560 (0x94560) — XBE naked draft (batch 269). */
#if defined(__clang__)
static void (*const b94560_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b94560_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_00094560(char *out __attribute__((unused)), void *event __attribute__((unused)), int **stream __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00094560_1\n\t"
      "pushl $1\n\t"
      "pushl $0x21\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x2690a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00094560_1:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .LFUN_00094560_2\n\t"
      "pushl $1\n\t"
      "pushl $0x22\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269480\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00094560_2:\n\t"
      "cmpw $6, (%%ebx)\n\t"
      "je .LFUN_00094560_3\n\t"
      "pushl $1\n\t"
      "pushl $0x23\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269568\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00094560_3:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00094560_4\n\t"
      "pushl $1\n\t"
      "pushl $0x24\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269358\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00094560_4:\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "movl %%eax, 0xc(%%edi)\n\t"
      "movl 0x8(%%ebx), %%ecx\n\t"
      "movl %%ecx, 0x10(%%edi)\n\t"
      "movl $0, 0x14(%%edi)\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0xc, %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b94560_assert), [exitfn] "m"(b94560_exitfn)
      : "memory");
}
#else
#error "FUN_00094560: clang naked draft required"
#endif


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


/* recorded_animation_apply_event_stream_v1 (0x94a90) — XBE naked draft (batch 270). */
#if defined(__clang__)
static void (*const b94a90_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b94a90_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
char recorded_animation_apply_event_stream_v1(char *thread __attribute__((unused)), void *event __attribute__((unused)), int *ticks __attribute__((unused)), int **cursor __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lrecorded_animation_apply_event_stream_v1_1\n\t"
      "pushl $1\n\t"
      "pushl $0xa2\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x2690a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrecorded_animation_apply_event_stream_v1_1:\n\t"
      "pushl %%ebx\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .Lrecorded_animation_apply_event_stream_v1_2\n\t"
      "pushl $1\n\t"
      "pushl $0xa3\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269368\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrecorded_animation_apply_event_stream_v1_2:\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lrecorded_animation_apply_event_stream_v1_3\n\t"
      "pushl $1\n\t"
      "pushl $0xa4\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269358\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrecorded_animation_apply_event_stream_v1_3:\n\t"
      "cmpl $0, (%%edi)\n\t"
      "jne .Lrecorded_animation_apply_event_stream_v1_4\n\t"
      "pushl $1\n\t"
      "pushl $0xa5\n\t"
      "pushl $0x269490\n\t"
      "pushl $0x269344\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrecorded_animation_apply_event_stream_v1_4:\n\t"
      "movl (%%edi), %%esi\n\t"
      "movzwl 0x2(%%esi), %%eax\n\t"
      "cmpl %%eax, (%%ebx)\n\t"
      "jl .Lrecorded_animation_apply_event_stream_v1_8\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lrecorded_animation_apply_event_stream_v1_5:\n\t"
      "movw (%%esi), %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "je .Lrecorded_animation_apply_event_stream_v1_9\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movl 0x2eea70(,%%ecx,4), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrecorded_animation_apply_event_stream_v1_6\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Lrecorded_animation_apply_event_stream_v1_7\n\t"
      ".Lrecorded_animation_apply_event_stream_v1_6:\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "movl %%eax, (%%edi)\n\t"
      ".Lrecorded_animation_apply_event_stream_v1_7:\n\t"
      "movzwl 0x2(%%esi), %%ecx\n\t"
      "subl %%ecx, (%%ebx)\n\t"
      "movl (%%edi), %%esi\n\t"
      "movzwl 0x2(%%esi), %%edx\n\t"
      "cmpl %%edx, (%%ebx)\n\t"
      "jge .Lrecorded_animation_apply_event_stream_v1_5\n\t"
      ".Lrecorded_animation_apply_event_stream_v1_8:\n\t"
      "cmpw $1, (%%esi)\n\t"
      "jne .Lrecorded_animation_apply_event_stream_v1_10\n\t"
      ".Lrecorded_animation_apply_event_stream_v1_9:\n\t"
      "movzwl 0x2(%%esi), %%eax\n\t"
      "cmpl %%eax, (%%ebx)\n\t"
      "jne .Lrecorded_animation_apply_event_stream_v1_10\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrecorded_animation_apply_event_stream_v1_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b94a90_assert), [exitfn] "m"(b94a90_exitfn)
      : "memory");
}
#else
#error "recorded_animation_apply_event_stream_v1: clang naked draft required"
#endif


/* recorded_animation_verify (0x94ee0) — XBE naked draft (batch 272). */
#if defined(__clang__)
static void (*const b94ee0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b94ee0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void recorded_animation_verify(char *anim __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x58, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0x38(%%esi), %%eax\n\t"
      "movzbl 0x20(%%esi), %%ecx\n\t"
      "movl 0x2eebac(,%%ecx,4), %%edx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x22(%%esi), %%al\n\t"
      "pushl %%edi\n\t"
      "movzwl 0x24(%%esi), %%edi\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "movl $0, 0x8(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *(%%edx)\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .Lrecorded_animation_verify_1\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lrecorded_animation_verify_1:\n\t"
      "movzbl 0x20(%%esi), %%edx\n\t"
      "movl 0x2eebac(,%%edx,4), %%eax\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "decl %%edi\n\t"
      "call *0x4(%%eax)\n\t"
      "addl $0x10, %%esp\n\t"
      "movb %%al, %%bl\n\t"
      "negb %%bl\n\t"
      "sbbb %%bl, %%bl\n\t"
      "incb %%bl\n\t"
      "testl %%edi, %%edi\n\t"
      "jge .Lrecorded_animation_verify_2\n\t"
      "pushl $1\n\t"
      "pushl $0x1ac\n\t"
      "pushl $0x269764\n\t"
      "pushl $0x2698f4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrecorded_animation_verify_2:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .Lrecorded_animation_verify_3\n\t"
      "pushl $1\n\t"
      "pushl $0x1ad\n\t"
      "pushl $0x269764\n\t"
      "pushl $0x2698e0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrecorded_animation_verify_3:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lrecorded_animation_verify_5\n\t"
      "jne .Lrecorded_animation_verify_4\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lrecorded_animation_verify_5\n\t"
      ".Lrecorded_animation_verify_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x1ae\n\t"
      "pushl $0x269764\n\t"
      "pushl $0x269898\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrecorded_animation_verify_5:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "incl %%ecx\n\t"
      "testb %%bl, %%bl\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "je .Lrecorded_animation_verify_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b94ee0_assert), [exitfn] "m"(b94ee0_exitfn)
      : "memory");
}
#else
#error "recorded_animation_verify: clang naked draft required"
#endif


#undef RA_EVENT_ASSERT
/* --- recorded_animations.obj batch3 drafts (2026-07-26) --- */

#define RA3_EVENT_ASSERT(line, msg) \
  do { \
    display_assert((char *)(msg), \
                   "c:\\halo\\SOURCE\\cutscene\\recorded_animations.c", (line), 1); \
    system_exit(-1); \
  } while (0)

static void __attribute__((unused)) ra3_check_ptr(void *p, int line, void *msg)
{
  if (!p)
    RA3_EVENT_ASSERT(line, msg);
}

/* FUN_000940a0 (0x940a0) — XBE naked draft (batch 265). */
#if defined(__clang__)
static void (*const b940a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b940a0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
char FUN_000940a0(char *thread __attribute__((unused)), void *event __attribute__((unused)), int *ticks __attribute__((unused)), int **cursor __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000940a0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x113\n\t"
      "pushl $0x2690a8\n\t"
      "pushl $0x2690a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000940a0_1:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000940a0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x114\n\t"
      "pushl $0x2690a8\n\t"
      "pushl $0x269368\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000940a0_2:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000940a0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x115\n\t"
      "pushl $0x2690a8\n\t"
      "pushl $0x269358\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000940a0_3:\n\t"
      "cmpl $0, (%%esi)\n\t"
      "jne .LFUN_000940a0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x116\n\t"
      "pushl $0x2690a8\n\t"
      "pushl $0x269344\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000940a0_4:\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "pushl %%edi\n\t"
      ".LFUN_000940a0_5:\n\t"
      "movl (%%esi), %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb (%%esi), %%al\n\t"
      "xorl %%edi, %%edi\n\t"
      "andl $3, %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LFUN_000940a0_11\n\t"
      "jmp *.LFUN_000940a0_jt(,%%eax,4)\n\t"
      ".LFUN_000940a0_6:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl $1, %%edi\n\t"
      "jmp .LFUN_000940a0_13\n\t"
      ".LFUN_000940a0_7:\n\t"
      "movl $1, %%ebx\n\t"
      "movl %%ebx, %%edi\n\t"
      "jmp .LFUN_000940a0_13\n\t"
      ".LFUN_000940a0_8:\n\t"
      "movzbw 0x1(%%esi), %%bx\n\t"
      "cmpw $1, %%bx\n\t"
      "movl $2, %%edi\n\t"
      "jbe .LFUN_000940a0_9\n\t"
      "cmpw $0xff, %%bx\n\t"
      "jbe .LFUN_000940a0_13\n\t"
      ".LFUN_000940a0_9:\n\t"
      "pushl $1\n\t"
      "pushl $0x12d\n\t"
      "pushl $0x2690a8\n\t"
      "pushl $0x269318\n\t"
      "jmp .LFUN_000940a0_12\n\t"
      ".LFUN_000940a0_10:\n\t"
      "movw 0x1(%%esi), %%bx\n\t"
      "cmpw $0xff, %%bx\n\t"
      "movl $3, %%edi\n\t"
      "ja .LFUN_000940a0_13\n\t"
      "pushl $1\n\t"
      "pushl $0x132\n\t"
      "pushl $0x2690a8\n\t"
      "pushl $0x2692f8\n\t"
      "jmp .LFUN_000940a0_12\n\t"
      ".LFUN_000940a0_11:\n\t"
      "pushl $1\n\t"
      "pushl $0x135\n\t"
      "pushl $0x2690a8\n\t"
      "pushl $0x255ee8\n\t"
      ".LFUN_000940a0_12:\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000940a0_13:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movzwl %%bx, %%eax\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jl .LFUN_000940a0_16\n\t"
      "movb (%%esi), %%al\n\t"
      "andb $0xfc, %%al\n\t"
      "cmpb $4, %%al\n\t"
      "je .LFUN_000940a0_16\n\t"
      "movzwl %%di, %%edx\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "addl %%edx, (%%edi)\n\t"
      "movb (%%esi), %%al\n\t"
      "andb $0xfc, %%al\n\t"
      "cmpb $0x5c, %%al\n\t"
      "jb .LFUN_000940a0_14\n\t"
      "pushl $1\n\t"
      "pushl $0x13b\n\t"
      "pushl $0x2690a8\n\t"
      "pushl $0x2692cc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000940a0_14:\n\t"
      "movzbl (%%esi), %%edx\n\t"
      "shrl $2, %%edx\n\t"
      "movl 0x2ee960(,%%edx,4), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000940a0_15\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_000940a0_15:\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "movzwl %%bx, %%eax\n\t"
      "subl %%eax, %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "jmp .LFUN_000940a0_5\n\t"
      ".LFUN_000940a0_16:\n\t"
      "movb (%%esi), %%al\n\t"
      "andb $0xfc, %%al\n\t"
      "cmpb $4, %%al\n\t"
      "popl %%edi\n\t"
      "jne .LFUN_000940a0_17\n\t"
      "movl (%%ecx), %%eax\n\t"
      "movzwl %%bx, %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jne .LFUN_000940a0_17\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000940a0_17:\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "movl %%edi, %%edi\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000940a0_jt:\n\t"
      ".long .LFUN_000940a0_6\n\t"
      ".long .LFUN_000940a0_7\n\t"
      ".long .LFUN_000940a0_8\n\t"
      ".long .LFUN_000940a0_10\n\t"
      ".text\n\t"
      :
      : [assert] "m"(b940a0_assert), [exitfn] "m"(b940a0_exitfn)
      : "memory");
}
#else
#error "FUN_000940a0: clang naked draft required"
#endif


/* render_debug_recording (0x950b0) — XBE naked draft (batch 265). */
#if defined(__clang__)
static void (*const b950b0_chkstk)(void) = FUN_001d90e0;
static int (*const b950b0_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static void (*const b950b0_c1197b0)(data_iter_t *iter, data_t *data) = data_iterator_new;
static void * (*const b950b0_c119810)(data_iter_t *iterator) = data_iterator_next;
static void *(*const b950b0_tryget)(int, int) = object_try_and_get_and_verify_type;
static scenario_t * (*const b950b0_c18e380)(void) = global_scenario_get;
static void *(*const b950b0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b950b0_c19b560)(void *stops, short count) = draw_string_set_tab_stops;
static void (*const b950b0_c189c40)(char flag, const char *string) = FUN_00189c40;

__attribute__((naked, noinline))
void render_debug_recording(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x2818, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "movb 0x44df08, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrender_debug_recording_7\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpw %%si, 0x2eebc0\n\t"
      "movw $0xc8, -0x4(%%ebp)\n\t"
      "movw $0x12c, -0x2(%%ebp)\n\t"
      "jle .Lrender_debug_recording_2\n\t"
      "jmp .Lrender_debug_recording_1\n\t"
      "leal (%%esp), %%esp\n\t"
      "nop\n\t"
      ".Lrender_debug_recording_1:\n\t"
      "movswl %%di, %%eax\n\t"
      "leal -0x2818(%%ebp,%%eax,1), %%ecx\n\t"
      "pushl $0x26993c\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $8, %%esp\n\t"
      "addl %%eax, %%edi\n\t"
      "incl %%esi\n\t"
      "cmpw 0x2eebc0, %%si\n\t"
      "jl .Lrender_debug_recording_1\n\t"
      ".Lrender_debug_recording_2:\n\t"
      "movswl %%di, %%edx\n\t"
      "leal -0x2818(%%ebp,%%edx,1), %%eax\n\t"
      "pushl $0x269914\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "movl 0x44df04, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl %%eax, %%edi\n\t"
      "call *%[c1197b0]\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119810]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .Lrender_debug_recording_6\n\t"
      ".Lrender_debug_recording_3:\n\t"
      "movl 0x4(%%ebx), %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "call *%[tryget]\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "movl 0x44df0c, %%edx\n\t"
      "movb 0xa(%%ebx), %%cl\n\t"
      "andl $0xffff, %%esi\n\t"
      "shll $4, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "addl %%edx, %%esi\n\t"
      "testb $1, %%cl\n\t"
      "jne .Lrender_debug_recording_5\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrender_debug_recording_5\n\t"
      "movw 0x6a(%%eax), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lrender_debug_recording_5\n\t"
      "movswl %%ax, %%edx\n\t"
      "pushl $0x24\n\t"
      "pushl %%edx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x204, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movb (%%esi), %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl $0x25b724, %%eax\n\t"
      "je .Lrender_debug_recording_4\n\t"
      "movswl 0xc(%%esi), %%eax\n\t"
      "pushl $0x40\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x36c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lrender_debug_recording_4:\n\t"
      "movswl %%di, %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal -0x2818(%%ebp,%%ecx,1), %%edx\n\t"
      "pushl $0x26990c\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl %%eax, %%edi\n\t"
      "movzwl 0x8(%%ebx), %%eax\n\t"
      "movswl %%di, %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal -0x2818(%%ebp,%%ecx,1), %%edx\n\t"
      "pushl $0x269904\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl %%eax, %%edi\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movswl %%di, %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal -0x2818(%%ebp,%%ecx,1), %%edx\n\t"
      "pushl $0x257984\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x24, %%esp\n\t"
      "addl %%eax, %%edi\n\t"
      ".Lrender_debug_recording_5:\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119810]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $4, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .Lrender_debug_recording_3\n\t"
      ".Lrender_debug_recording_6:\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl $2\n\t"
      "pushl %%ecx\n\t"
      "movb $0, -0x2418(%%ebp)\n\t"
      "call *%[c19b560]\n\t"
      "leal -0x2818(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189c40]\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b560]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".Lrender_debug_recording_7:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(b950b0_chkstk), [c1d90f0] "m"(b950b0_c1d90f0), [c1197b0] "m"(b950b0_c1197b0), [c119810] "m"(b950b0_c119810), [tryget] "m"(b950b0_tryget), [c18e380] "m"(b950b0_c18e380), [elem] "m"(b950b0_elem), [c19b560] "m"(b950b0_c19b560), [c189c40] "m"(b950b0_c189c40)
      : "memory");
}
#else
#error "render_debug_recording: clang naked draft required"
#endif


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


/* control_toggle (0x957c0) — XBE naked draft (batch 264). */
#if defined(__clang__)
static void *(*const b957c0_get)(int, int) = object_get_and_verify_type;
static void *(*const b957c0_tag)(int, int) = tag_get;
static void *(*const b957c0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b957c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b957c0_exitfn)(int) = system_exit;
static int (*const b957c0_c96f20)(int a0, float a1) = FUN_00096f20;
static void (*const b957c0_c967a0)(void *rec, int object) = FUN_000967a0;

__attribute__((naked, noinline))
void control_toggle(int object __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x100\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6374726c\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "movw 0x1b4(%%edi), %%ax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lcontrol_toggle_9\n\t"
      "movl 0x5aa8c8, %%edx\n\t"
      "movswl %%ax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movswl 0x290(%%esi), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $3, %%ecx\n\t"
      "ja .Lcontrol_toggle_5\n\t"
      "jmp *.Lcontrol_toggle_jt(,%%ecx,4)\n\t"
      ".Lcontrol_toggle_1:\n\t"
      "flds 0x4(%%eax)\n\t"
      "fcomps 0x253398\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lcontrol_toggle_3\n\t"
      ".Lcontrol_toggle_2:\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jmp .Lcontrol_toggle_6\n\t"
      ".Lcontrol_toggle_3:\n\t"
      "movl $0x3f800000, -0x4(%%ebp)\n\t"
      "jmp .Lcontrol_toggle_6\n\t"
      ".Lcontrol_toggle_4:\n\t"
      "movl 0x294(%%esi), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .Lcontrol_toggle_6\n\t"
      ".Lcontrol_toggle_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x8a\n\t"
      "pushl $0x269a84\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lcontrol_toggle_6:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x1b4(%%edi), %%dx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c96f20]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lcontrol_toggle_8\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x253398\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lcontrol_toggle_7\n\t"
      "movl 0x2f4(%%esi), %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c967a0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcontrol_toggle_7:\n\t"
      "movl 0x304(%%esi), %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c967a0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcontrol_toggle_8:\n\t"
      "movl 0x314(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c967a0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lcontrol_toggle_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "movl %%edi, %%edi\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lcontrol_toggle_jt:\n\t"
      ".long .Lcontrol_toggle_1\n\t"
      ".long .Lcontrol_toggle_3\n\t"
      ".long .Lcontrol_toggle_2\n\t"
      ".long .Lcontrol_toggle_4\n\t"
      ".text\n\t"
      :
      : [get] "m"(b957c0_get), [tag] "m"(b957c0_tag), [dget] "m"(b957c0_dget), [assert] "m"(b957c0_assert), [exitfn] "m"(b957c0_exitfn), [c96f20] "m"(b957c0_c96f20), [c967a0] "m"(b957c0_c967a0)
      : "memory");
}
#else
#error "control_toggle: clang naked draft required"
#endif


/* FUN_00095c60 (0x95c60) — XBE naked draft (batch 263). */
#if defined(__clang__)
static void (*const b95c60_chkstk)(void) = FUN_001d90e0;
static void *(*const b95c60_get)(int, int) = object_get_and_verify_type;
static void *(*const b95c60_tag)(int, int) = tag_get;
static void *(*const b95c60_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const b95c60_gtime)(void) = game_time_get;
static int16_t (*const b95c60_c1415f0)(int flags, unsigned int type_mask, void *cluster_info, float *position, float radius, int *out_handles, int16_t max_count) = object_find_in_radius;
static bool (*const b95c60_ca7a30)(int16_t team_a, int16_t team_b) = game_allegiance_get_team_is_friendly;
static int (*const b95c60_c96f20)(int a0, float a1) = FUN_00096f20;
static void *(*const b95c60_onode)(int, short) = object_get_node_matrix;
static void (*const b95c60_otrans)(int, float *, void *) = object_translate;

__attribute__((naked, noinline))
char FUN_00095c60(int object __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x2068, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x80\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6d616368\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $2, 0x290(%%edi)\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "jne .LFUN_00095c60_3\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x1ac(%%esi)\n\t"
      "fmuls 0x280(%%edi)\n\t"
      "flds 0x288(%%edi)\n\t"
      "fmuls 0x1ac(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds 0x1b8(%%esi)\n\t"
      "fcoms 0x2533c8\n\t"
      "fsts 0x1b8(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00095c60_1\n\t"
      "fsubs 0x2533c8\n\t"
      "fstps 0x1b8(%%esi)\n\t"
      "jmp .LFUN_00095c60_2\n\t"
      ".LFUN_00095c60_1:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00095c60_2:\n\t"
      "movl 0x1a4(%%esi), %%edx\n\t"
      "movw 0x1b4(%%esi), %%ax\n\t"
      "orl $4, %%edx\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movl $0, 0x1bc(%%esi)\n\t"
      "movl %%edx, 0x1a4(%%esi)\n\t"
      "je .LFUN_00095c60_3\n\t"
      "movl 0x5aa8c8, %%edx\n\t"
      "movswl %%ax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x1b8(%%esi), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      ".LFUN_00095c60_3:\n\t"
      "testb $1, 0x1c4(%%esi)\n\t"
      "jne .LFUN_00095c60_13\n\t"
      "cmpw $0, 0x290(%%edi)\n\t"
      "jne .LFUN_00095c60_15\n\t"
      "call *%[gtime]\n\t"
      "addl %%ebx, %%eax\n\t"
      "testb $3, %%al\n\t"
      "jne .LFUN_00095c60_13\n\t"
      "flds 0x21c(%%edi)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "fcomps 0x253f44\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00095c60_4\n\t"
      "movl 0x5c(%%esi), %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00095c60_5\n\t"
      ".LFUN_00095c60_4:\n\t"
      "movl 0x21c(%%edi), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".LFUN_00095c60_5:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl $0x10\n\t"
      "leal -0x68(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal 0x50(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x48(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "call *%[c1415f0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00095c60_13\n\t"
      "movzwl %%ax, %%edx\n\t"
      "leal -0x68(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      ".LFUN_00095c60_6:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movb 0xb6(%%edi), %%cl\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $4, %%cl\n\t"
      "movb $1, %%bl\n\t"
      "jne .LFUN_00095c60_7\n\t"
      "movl 0x17c(%%eax), %%ecx\n\t"
      "testb $0x40, %%ch\n\t"
      "je .LFUN_00095c60_8\n\t"
      ".LFUN_00095c60_7:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_00095c60_8:\n\t"
      "testb $2, 0x1c4(%%esi)\n\t"
      "je .LFUN_00095c60_9\n\t"
      "flds 0x1b8(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00095c60_9\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x68(%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[ca7a30]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00095c60_9\n\t"
      "flds 0x50(%%edi)\n\t"
      "fsubs 0x50(%%esi)\n\t"
      "flds 0x54(%%edi)\n\t"
      "fsubs 0x54(%%esi)\n\t"
      "flds 0x58(%%edi)\n\t"
      "fsubs 0x58(%%esi)\n\t"
      "fmuls 0x2c(%%esi)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x28(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x24(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00095c60_10\n\t"
      ".LFUN_00095c60_9:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00095c60_10\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_00095c60_10:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jne .LFUN_00095c60_6\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00095c60_12\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x1b4(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00095c60_11\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%eax\n\t"
      "call *%[c96f20]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00095c60_11:\n\t"
      "movl $0xfffffffd, 0x1c8(%%esi)\n\t"
      ".LFUN_00095c60_12:\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      ".LFUN_00095c60_13:\n\t"
      "cmpw $0, 0x290(%%edi)\n\t"
      "jne .LFUN_00095c60_15\n\t"
      "cmpl $0x3f800000, 0x1b8(%%esi)\n\t"
      "jne .LFUN_00095c60_14\n\t"
      "movl 0x1c8(%%esi), %%edx\n\t"
      "incl %%edx\n\t"
      "movl %%edx, 0x1c8(%%esi)\n\t"
      "movl 0x320(%%edi), %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jle .LFUN_00095c60_15\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x1b4(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00095c60_15\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c96f20]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_00095c60_15\n\t"
      ".LFUN_00095c60_14:\n\t"
      "movl $0, 0x1c8(%%esi)\n\t"
      ".LFUN_00095c60_15:\n\t"
      "testb $4, 0x292(%%edi)\n\t"
      "je .LFUN_00095c60_20\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2ea(%%edi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00095c60_20\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[onode]\n\t"
      "flds 0x28(%%eax)\n\t"
      "fsubs 0x1cc(%%esi)\n\t"
      "leal 0x28(%%eax), %%edi\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs 0x1d0(%%esi)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsubs 0x1d4(%%esi)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00095c60_16\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00095c60_16\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00095c60_19\n\t"
      ".LFUN_00095c60_16:\n\t"
      "movl 0x5c(%%esi), %%eax\n\t"
      "pushl $0x800\n\t"
      "leal -0x2068(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x50(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x48(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "call *%[c1415f0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00095c60_19\n\t"
      "movzwl %%ax, %%eax\n\t"
      "leal -0x2068(%%ebp), %%ebx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      ".LFUN_00095c60_17:\n\t"
      "movl (%%ebx), %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x42c(%%eax), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jne .LFUN_00095c60_18\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "pushl $0\n\t"
      "fadds 0xc(%%eax)\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fadds 0x10(%%eax)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fadds 0x14(%%eax)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "call *%[otrans]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00095c60_18:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $4, %%ebx\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jne .LFUN_00095c60_17\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      ".LFUN_00095c60_19:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, 0x1cc(%%esi)\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x1d0(%%esi)\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl %%edx, 0x1d4(%%esi)\n\t"
      ".LFUN_00095c60_20:\n\t"
      "testb $4, 0x1a4(%%esi)\n\t"
      "je .LFUN_00095c60_21\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "leal 0xc(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[otrans]\n\t"
      "movl 0x1a4(%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "andl $0xfffffffb, %%eax\n\t"
      "movl %%eax, 0x1a4(%%esi)\n\t"
      ".LFUN_00095c60_21:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(b95c60_chkstk), [get] "m"(b95c60_get), [tag] "m"(b95c60_tag), [dget] "m"(b95c60_dget), [gtime] "m"(b95c60_gtime), [c1415f0] "m"(b95c60_c1415f0), [ca7a30] "m"(b95c60_ca7a30), [c96f20] "m"(b95c60_c96f20), [onode] "m"(b95c60_onode), [otrans] "m"(b95c60_otrans)
      : "memory");
}
#else
#error "FUN_00095c60: clang naked draft required"
#endif


#undef RA3_EVENT_ASSERT
/* --- recorded_animations.obj orphan shells (2026-07-26) --- */

/* recorded_animation_play (0x95640) — readable C lift from XBE leaf. */
char recorded_animation_play(int actor, short anim_idx)
{
  return recorded_animation_play_internal(actor, (int)anim_idx, 0);
}

