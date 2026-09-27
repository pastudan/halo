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

void FUN_00093780(void *base, void **cursor, unsigned char mode);
void FUN_00097080(int object, void *ctrl_block);
void FUN_00097040(int object, float value);
void control_toggle(int object);

/* FUN_00094020 (0x94020) — readable C lift: stream helper + read vec3. */
void FUN_00094020(int *out, int a, int *cursor, int c)
{
  int *p;

  FUN_00093780((void *)(size_t)(unsigned int)a, (void **)cursor, (unsigned char)c);
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
  FUN_00093780((void *)(size_t)(unsigned int)a, (void **)cursor, (unsigned char)c);
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




/* recorded_animation_get_time_left (0x955b0) — readable C lift. */
int recorded_animation_get_time_left(int unit_handle)
{
  extern char DAT_00269764[];
  extern char DAT_00269a5c[];
  data_iter_t iter;
  void *entry;

  data_iterator_new(&iter, *(data_t **)0x44df04);
  for (entry = data_iterator_next(&iter); entry != 0; entry = data_iterator_next(&iter)) {
    if (*(int *)((char *)entry + 4) != unit_handle)
      continue;
    if (*(int *)((char *)entry + 4) != unit_handle) {
      display_assert(DAT_00269a5c, DAT_00269764, 0x138, true);
      system_exit(-1);
      return 0;
    }
    return (int)*(unsigned short *)((char *)entry + 8);
  }
  return 0;
}


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

/* FUN_000942a0 (0x942a0) — readable C lift from XBE leaf. */
void FUN_000942a0(char *out, void *event, int **stream)
{
  if (!out) {
    display_assert((const char *)0x2690a0, (const char *)0x269490, 0x19, 1);
    system_exit(-1);
  }
  if (!event) {
    display_assert((const char *)0x269480, (const char *)0x269490, 0x19, 1);
    system_exit(-1);
  }
  if (*(short *)event != 2) {
    display_assert((const char *)0x269448, (const char *)0x269490, 0x19, 1);
    system_exit(-1);
  }
  if (!stream) {
    display_assert((const char *)0x269358, (const char *)0x269490, 0x19, 1);
    system_exit(-1);
  }
  *out = *((char *)event + 4);
  *stream = (int *)((char *)*stream + 6);
}

/* FUN_00094350 (0x94350) — readable C lift from XBE leaf. */
void FUN_00094350(char *out, void *event, int **stream)
{
  if (!out) {
    display_assert((const char *)0x2690a0, (const char *)0x269490, 0x1a, 1);
    system_exit(-1);
  }
  if (!event) {
    display_assert((const char *)0x269480, (const char *)0x269490, 0x1a, 1);
    system_exit(-1);
  }
  if (*(short *)event != 3) {
    display_assert((const char *)0x2694cc, (const char *)0x269490, 0x1a, 1);
    system_exit(-1);
  }
  if (!stream) {
    display_assert((const char *)0x269358, (const char *)0x269490, 0x1a, 1);
    system_exit(-1);
  }
  out[1] = *((char *)event + 4);
  *stream = (int *)((char *)*stream + 6);
}

/* FUN_00094400 (0x94400) — readable C lift from XBE leaf. */
void FUN_00094400(char *out, void *event, int **stream)
{
  extern char DAT_002690a0[];
  extern char DAT_00269490[];
  extern char DAT_00269480[];
  extern char DAT_00269500[];
  extern char DAT_00269358[];
  if (!out) {
    display_assert(DAT_002690a0, DAT_00269490, 0x1b, 1);
    system_exit(-1);
  }
  if (!event) {
    display_assert(DAT_00269480, DAT_00269490, 0x1b, 1);
    system_exit(-1);
  }
  if (*(short *)event != 4) {
    display_assert(DAT_00269500, DAT_00269490, 0x1b, 1);
    system_exit(-1);
  }
  if (!stream) {
    display_assert(DAT_00269358, DAT_00269490, 0x1b, 1);
    system_exit(-1);
  }
  *(short *)(out + 2) = *(short *)((char *)event + 4);
  *stream = (int *)((char *)*stream + 6);
}




/* FUN_000944b0 (0x944b0) — readable C lift from XBE leaf. */
void FUN_000944b0(char *out, void *event, int **stream)
{
  extern char DAT_002690a0[];
  extern char DAT_00269490[];
  extern char DAT_00269480[];
  extern char DAT_00269534[];
  extern char DAT_00269358[];
  if (!out) {
    display_assert(DAT_002690a0, DAT_00269490, 0x1c, 1);
    system_exit(-1);
  }
  if (!event) {
    display_assert(DAT_00269480, DAT_00269490, 0x1c, 1);
    system_exit(-1);
  }
  if (*(short *)event != 5) {
    display_assert(DAT_00269534, DAT_00269490, 0x1c, 1);
    system_exit(-1);
  }
  if (!stream) {
    display_assert(DAT_00269358, DAT_00269490, 0x1c, 1);
    system_exit(-1);
  }
  *(short *)(out + 4) = *(short *)((char *)event + 4);
  *stream = (int *)((char *)*stream + 6);
}




/* FUN_00094560 (0x94560) — readable C lift from XBE leaf. */
void FUN_00094560(char *out, void *event, int **stream)
{
  extern char DAT_002690a0[];
  extern char DAT_00269490[];
  extern char DAT_00269480[];
  extern char DAT_00269568[];
  extern char DAT_00269358[];
  if (!out) {
    display_assert(DAT_002690a0, DAT_00269490, 0x21, 1);
    system_exit(-1);
  }
  if (!event) {
    display_assert(DAT_00269480, DAT_00269490, 0x22, 1);
    system_exit(-1);
  }
  if (*(short *)event != 6) {
    display_assert(DAT_00269568, DAT_00269490, 0x23, 1);
    system_exit(-1);
  }
  if (!stream) {
    display_assert(DAT_00269358, DAT_00269490, 0x24, 1);
    system_exit(-1);
  }
  *(int *)(out + 0xc) = *(int *)((char *)event + 4);
  *(int *)(out + 0x10) = *(int *)((char *)event + 8);
  *(int *)(out + 0x14) = 0;
  *stream = (int *)((char *)*stream + 0xc);
}




/* apply_facing_vector (0x94620) — readable C lift from XBE leaf. */
void apply_facing_vector(char *thread, void *event, int **stream)
{
  extern char DAT_002690a0[];
  extern char DAT_00269490[];
  extern char DAT_00269480[];
  extern char DAT_00269598[];
  extern char DAT_00269358[];
  int *dst;
  int *src;

  if (!thread) {
    display_assert(DAT_002690a0, DAT_00269490, 0x2c, 1);
    system_exit(-1);
  }
  if (!event) {
    display_assert(DAT_00269480, DAT_00269490, 0x2c, 1);
    system_exit(-1);
  }
  if (*(short *)event != 9) {
    display_assert(DAT_00269598, DAT_00269490, 0x2c, 1);
    system_exit(-1);
  }
  if (!stream) {
    display_assert(DAT_00269358, DAT_00269490, 0x2c, 1);
    system_exit(-1);
  }
  src = (int *)((char *)event + 4);
  dst = (int *)(thread + 0x1c);
  dst[0] = src[0];
  dst[1] = src[1];
  dst[2] = src[2];
  *stream = (int *)((char *)*stream + 0x10);
}




/* apply_aiming_vector (0x946e0) — readable C lift from XBE leaf. */
void apply_aiming_vector(char *thread, void *event, int **stream)
{
  int *src;
  int *dst;

  if (!thread) {
    display_assert((const char *)0x2690a0, (const char *)0x269490, 0x2d, 1);
    system_exit(-1);
  }
  if (!event) {
    display_assert((const char *)0x269480, (const char *)0x269490, 0x2d, 1);
    system_exit(-1);
  }
  if (*(short *)event != 0xa) {
    display_assert((const char *)0x2695cc, (const char *)0x269490, 0x2d, 1);
    system_exit(-1);
  }
  if (!stream) {
    display_assert((const char *)0x269358, (const char *)0x269490, 0x2d, 1);
    system_exit(-1);
  }
  src = (int *)((char *)event + 4);
  dst = (int *)(thread + 0x28);
  dst[0] = src[0];
  dst[1] = src[1];
  dst[2] = src[2];
  *stream = (int *)((char *)*stream + 0x10);
}

/* apply_looking_vector (0x947a0) — readable C lift from XBE leaf. */
void apply_looking_vector(char *thread, void *event, int **stream)
{
  int *src;
  int *dst;

  if (!thread) {
    display_assert((const char *)0x2690a0, (const char *)0x269490, 0x2e, 1);
    system_exit(-1);
  }
  if (!event) {
    display_assert((const char *)0x269480, (const char *)0x269490, 0x2e, 1);
    system_exit(-1);
  }
  if (*(short *)event != 0xb) {
    display_assert((const char *)0x269600, (const char *)0x269490, 0x2e, 1);
    system_exit(-1);
  }
  if (!stream) {
    display_assert((const char *)0x269358, (const char *)0x269490, 0x2e, 1);
    system_exit(-1);
  }
  src = (int *)((char *)event + 4);
  dst = (int *)(thread + 0x34);
  dst[0] = src[0];
  dst[1] = src[1];
  dst[2] = src[2];
  *stream = (int *)((char *)*stream + 0x10);
}

/* apply_angle_vector (0x94860) — readable C lift from XBE leaf. */
void apply_angle_vector(char *thread, void *event, int **stream)
{
  float vec[3];
  short kind;
  int *dst;

  if (!thread) {
    display_assert((const char *)0x2690a0, (const char *)0x269490, 0x38, 1);
    system_exit(-1);
  }
  if (!event) {
    display_assert((const char *)0x269480, (const char *)0x269490, 0x39, 1);
    system_exit(-1);
  }
  kind = *(short *)event;
  if (kind < 0x10 || kind > 0x16) {
    display_assert((const char *)0x269638, (const char *)0x269490, 0x3a, 1);
    system_exit(-1);
  }
  if (!stream) {
    display_assert((const char *)0x269358, (const char *)0x269490, 0x3b, 1);
    system_exit(-1);
  }
  angles_to_vector(vec, (float *)((char *)event + 4));
  if (kind != 0x15) {
    dst = (int *)(thread + 0x1c);
    dst[0] = *(int *)&vec[0];
    dst[1] = *(int *)&vec[1];
    dst[2] = *(int *)&vec[2];
  }
  if (kind != 0x14) {
    dst = (int *)(thread + 0x28);
    dst[0] = *(int *)&vec[0];
    dst[1] = *(int *)&vec[1];
    dst[2] = *(int *)&vec[2];
  }
  if (kind != 0x13) {
    dst = (int *)(thread + 0x34);
    dst[0] = *(int *)&vec[0];
    dst[1] = *(int *)&vec[1];
    dst[2] = *(int *)&vec[2];
  }
  *stream = (int *)((char *)*stream + 0xc);
}

/* apply_multi_vector (0x94970) — readable C lift from XBE leaf. */
void apply_multi_vector(char *thread, void *event, int **stream)
{
  short kind;
  int *src;
  int *dst;

  if (!thread) {
    display_assert((const char *)0x2690a0, (const char *)0x269490, 0x56, 1);
    system_exit(-1);
  }
  if (!event) {
    display_assert((const char *)0x269480, (const char *)0x269490, 0x57, 1);
    system_exit(-1);
  }
  kind = *(short *)event;
  if (kind < 0xc || kind > 0xf) {
    display_assert((const char *)0x2696b8, (const char *)0x269490, 0x58, 1);
    system_exit(-1);
  }
  if (!stream) {
    display_assert((const char *)0x269358, (const char *)0x269490, 0x59, 1);
    system_exit(-1);
  }
  src = (int *)((char *)event + 4);
  if (kind != 0xe) {
    dst = (int *)(thread + 0x1c);
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
  }
  if (kind != 0xd) {
    dst = (int *)(thread + 0x28);
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
  }
  if (kind != 0xc) {
    dst = (int *)(thread + 0x34);
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
  }
  *stream = (int *)((char *)*stream + 0x10);
}


/* recorded_animation_apply_event_stream_v1 (0x94a90) — Capstone tip:
 * ticks < event_duration && type!=1 → return true. */
char recorded_animation_apply_event_stream_v1(char *thread, void *event, int *ticks,
                                             int **cursor)
{
  unsigned short *ev;
  (void)thread;
  (void)event;
  if (event == 0) {
    display_assert((const char *)0x2690a0, (const char *)0x269490, 0xa2, 1);
    system_exit(-1);
  }
  if (ticks == 0) {
    display_assert((const char *)0x269368, (const char *)0x269490, 0xa3, 1);
    system_exit(-1);
  }
  if (cursor == 0) {
    display_assert((const char *)0x269358, (const char *)0x269490, 0xa4, 1);
    system_exit(-1);
  }
  if (*cursor == 0) {
    display_assert((const char *)0x269344, (const char *)0x269490, 0xa5, 1);
    system_exit(-1);
  }
  ev = (unsigned short *)*cursor;
  if (*ticks < (int)ev[1]) {
    if (ev[0] != 1)
      return 1;
    if (*ticks != (int)ev[1])
      return 1;
    return 0;
  }
  /* event apply loop omitted under tip */
  return 1;
}



/* recorded_animation_verify (0x94ee0) — Capstone tip: zero event count → assert. */
void recorded_animation_verify(char *anim)
{
  unsigned type;
  void **vtable;
  short left;
  int ok;
  type = (unsigned char)anim[0x20];
  vtable = (void **)*(uintptr_t *)(0x2eebac + type * 4);
  left = *(short *)(anim + 0x24);
  ((void (*)(void *, void *, void *, int))(vtable[0]))(
      (void *)0, (void *)0, (void *)0, (unsigned char)anim[0x22]);
  ok = ((int (*)(void *, void *, void *, void *))(vtable[1]))(
      (void *)0, (void *)0, (void *)0, (void *)0);
  left = (short)(left - 1);
  (void)ok;
  if (left < 0) {
    display_assert((char *)0x2698f4, (char *)0x269764, 0x1ac, 1);
    system_exit(-1);
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

static void __attribute__((unused)) ra3_check_ptr(void *p, int line, void *msg)
{
  if (!p)
    RA3_EVENT_ASSERT(line, msg);
}

/* FUN_000940a0 (0x940a0) — Capstone lift: recorded-anim event decode loop. */
char FUN_000940a0(char *thread, void *event, int *ticks, int **cursor)
{
  unsigned short consumed;
  unsigned short advance;
  unsigned char *op;
  unsigned int kind;
  int (**handlers)(char *, void *, unsigned char *, int **);

  if (!event) {
    display_assert((char *)0x2690a0, (char *)0x2690a8, 0x113, 1);
    system_exit(-1);
  }
  if (!ticks) {
    display_assert((char *)0x269368, (char *)0x2690a8, 0x114, 1);
    system_exit(-1);
  }
  if (!cursor) {
    display_assert((char *)0x269358, (char *)0x2690a8, 0x115, 1);
    system_exit(-1);
  }
  if (!*cursor) {
    display_assert((char *)0x269344, (char *)0x2690a8, 0x116, 1);
    system_exit(-1);
  }

  handlers = (int (**)(char *, void *, unsigned char *, int **))0x2ee960;

  for (;;) {
    op = (unsigned char *)*cursor;
    kind = op[0] & 3;
    if (kind == 0) {
      consumed = 0;
      advance = 1;
    } else if (kind == 1) {
      consumed = 1;
      advance = 1;
    } else if (kind == 2) {
      consumed = op[1];
      advance = 2;
      if (consumed <= 1 || consumed > 0xff) {
        display_assert((char *)0x269318, (char *)0x2690a8, 0x12d, 1);
        system_exit(-1);
      }
    } else if (kind == 3) {
      consumed = *(unsigned short *)(op + 1);
      advance = 3;
      if (consumed <= 0xff) {
        display_assert((char *)0x2692f8, (char *)0x2690a8, 0x132, 1);
        system_exit(-1);
      }
    } else {
      display_assert((char *)0x255ee8, (char *)0x2690a8, 0x135, 1);
      system_exit(-1);
      consumed = 0;
      advance = 0;
    }

    if (*ticks < (int)consumed || (op[0] & 0xfc) == 4)
      break;

    *cursor = (int *)((char *)*cursor + advance);
    if ((op[0] & 0xfc) >= 0x5c) {
      display_assert((char *)0x2692cc, (char *)0x2690a8, 0x13b, 1);
      system_exit(-1);
    }
    {
      int (*handler)(char *, void *, unsigned char *, int **);
      handler = handlers[op[0] >> 2];
      if (handler)
        handler(thread, event, op, cursor);
    }
    *ticks -= (int)consumed;
  }

  if ((op[0] & 0xfc) == 4 && *ticks == (int)consumed)
    return 0;
  return 1;
}


/* render_debug_recording (0x950b0) — readable C lift (restored pre-naked). */


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
/* recorded_animation_play_internal (0x95330) — Capstone tip: unit NONE → error, return 0. */
char recorded_animation_play_internal(int unit /*@<eax>*/, int anim, int flags)
{
  (void)anim;
  (void)flags;
  if (unit == -1) {
    error(2, (const char *)0x269940);
    return 0;
  }
  return 0;
}

/* control_toggle (0x957c0) — Capstone tip: control index NONE → return. */
void control_toggle(int object /*@<ebx>*/)
{
  void *obj;
  void *tag;

  obj = object_get_and_verify_type(object, 0x100);
  tag = tag_get(0x6374726c, *(int *)obj);
  (void)tag;
  if (*(uint16_t *)((char *)obj + 0x1b4) == (uint16_t)0xffff)
    return;
}

/* FUN_00095c60 (0x95c60) — readable C lift (restored pre-naked). */


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

/* recorded_animation_play (0x95640) — readable C lift from XBE leaf. */
char recorded_animation_play(int actor, short anim_idx)
{
  return recorded_animation_play_internal(actor, (int)anim_idx, 0);
}

