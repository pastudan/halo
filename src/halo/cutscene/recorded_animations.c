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

void FUN_000942a0(char *out, void *event, int **stream)
{
  ra_check_ptr(out, 0x19, (void *)0x2690a0);
  ra_check_ptr(event, 0x19, (void *)0x269480);
  if (*(int16_t *)event != 2)
    RA_EVENT_ASSERT(0x19, (void *)0x269448);
  ra_check_ptr(stream, 0x19, (void *)0x269358);
  *out = *(char *)((char *)event + 4);
  **stream += 6;
}

void FUN_00094350(char *out, void *event, int **stream)
{
  ra_check_ptr(out, 0x1a, (void *)0x2690a0);
  ra_check_ptr(event, 0x1a, (void *)0x269480);
  if (*(int16_t *)event != 3)
    RA_EVENT_ASSERT(0x1a, (void *)0x2694cc);
  ra_check_ptr(stream, 0x1a, (void *)0x269358);
  out[1] = *(char *)((char *)event + 4);
  **stream += 6;
}

void FUN_00094400(char *out, void *event, int **stream)
{
  ra_check_ptr(out, 0x1b, (void *)0x2690a0);
  ra_check_ptr(event, 0x1b, (void *)0x269480);
  if (*(int16_t *)event != 4)
    RA_EVENT_ASSERT(0x1b, (void *)0x269500);
  ra_check_ptr(stream, 0x1b, (void *)0x269358);
  *(int16_t *)(out + 2) = *(int16_t *)((char *)event + 4);
  **stream += 6;
}

void FUN_000944b0(char *out, void *event, int **stream)
{
  ra_check_ptr(out, 0x1c, (void *)0x2690a0);
  ra_check_ptr(event, 0x1c, (void *)0x269480);
  if (*(int16_t *)event != 5)
    RA_EVENT_ASSERT(0x1c, (void *)0x269534);
  ra_check_ptr(stream, 0x1c, (void *)0x269358);
  *(int16_t *)(out + 4) = *(int16_t *)((char *)event + 4);
  **stream += 6;
}

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

void apply_facing_vector(char *thread, void *event, int **stream)
{
  ra_check_ptr(thread, 0x2c, (void *)0x2690a0);
  ra_check_ptr(event, 0x2c, (void *)0x269480);
  if (*(int16_t *)event != 9)
    RA_EVENT_ASSERT(0x2c, (void *)0x269598);
  ra_check_ptr(stream, 0x2c, (void *)0x269358);
  {
    float *src = (float *)((char *)event + 4);
    float *dst = (float *)(thread + 0x1c);
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
  }
  **stream += 0x10;
}

void apply_aiming_vector(char *thread, void *event, int **stream)
{
  ra_check_ptr(thread, 0x2d, (void *)0x2690a0);
  ra_check_ptr(event, 0x2d, (void *)0x269480);
  if (*(int16_t *)event != 0xa)
    RA_EVENT_ASSERT(0x2d, (void *)0x2695cc);
  ra_check_ptr(stream, 0x2d, (void *)0x269358);
  {
    float *src = (float *)((char *)event + 4);
    float *dst = (float *)(thread + 0x28);
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
  }
  **stream += 0x10;
}

void apply_looking_vector(char *thread, void *event, int **stream)
{
  ra_check_ptr(thread, 0x2e, (void *)0x2690a0);
  ra_check_ptr(event, 0x2e, (void *)0x269480);
  if (*(int16_t *)event != 0xb)
    RA_EVENT_ASSERT(0x2e, (void *)0x269600);
  ra_check_ptr(stream, 0x2e, (void *)0x269358);
  {
    float *src = (float *)((char *)event + 4);
    float *dst = (float *)(thread + 0x34);
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
  }
  **stream += 0x10;
}

void apply_angle_vector(char *thread, void *event, int **stream)
{
  float vec[3];

  ra_check_ptr(thread, 0x38, (void *)0x2690a0);
  ra_check_ptr(event, 0x39, (void *)0x269480);
  {
    int16_t t = *(int16_t *)event;
    if (t < 0x10 || t > 0x16)
      RA_EVENT_ASSERT(0x3a, (void *)0x269638);
  }
  ra_check_ptr(stream, 0x3b, (void *)0x269358);
  angles_to_vector(vec, (float *)((char *)event + 4));
  if (*(int16_t *)event != 0x15) {
    float *dst = (float *)(thread + 0x1c);
    dst[0] = vec[0];
    dst[1] = vec[1];
    dst[2] = vec[2];
  }
  if (*(int16_t *)event != 0x14) {
    float *dst = (float *)(thread + 0x28);
    dst[0] = vec[0];
    dst[1] = vec[1];
    dst[2] = vec[2];
  }
  if (*(int16_t *)event != 0x13) {
    float *dst = (float *)(thread + 0x34);
    dst[0] = vec[0];
    dst[1] = vec[1];
    dst[2] = vec[2];
  }
  **stream += 0xc;
}

void apply_multi_vector(char *thread, void *event, int **stream)
{
  ra_check_ptr(thread, 0x56, (void *)0x2690a0);
  ra_check_ptr(event, 0x57, (void *)0x269480);
  {
    int16_t t = *(int16_t *)event;
    if (t < 0xc || t > 0xf)
      RA_EVENT_ASSERT(0x58, (void *)0x2696b8);
  }
  ra_check_ptr(stream, 0x59, (void *)0x269358);
  if (*(int16_t *)event != 0xe) {
    float *src = (float *)((char *)event + 4);
    float *dst = (float *)(thread + 0x1c);
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
  }
  if (*(int16_t *)event != 0xd) {
    float *src = (float *)((char *)event + 4);
    float *dst = (float *)(thread + 0x28);
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
  }
  if (*(int16_t *)event != 0xc) {
    float *src = (float *)((char *)event + 4);
    float *dst = (float *)(thread + 0x34);
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
  }
  **stream += 0x10;
}

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

char recorded_animation_play_internal(int unit, int anim, int flags)
{
  scenario_t *scenario;
  char *anim_def;
  char *thread;
  int thread_handle;
  void **vtable;
  int anim_type;
  char *dbg_slot;
  char result;
  uint16_t extra_flags;

  result = 0;
  if (unit == -1) {
    error(2, (char *)0x269940);
    return result;
  }
  if ((int16_t)anim == -1) {
    error(2, (char *)0x269954);
    return result;
  }

  scenario = global_scenario_get();
  if ((int)anim >= *(int *)((char *)scenario + 0x36c)) {
    error(2, (char *)0x269954);
    return result;
  }

  object_get_and_verify_type(unit, 3);
  player_index_from_unit_index(unit);
  FUN_00095050(unit, &thread_handle);

  anim_def = (char *)tag_block_get_element((char *)scenario + 0x36c, anim, 0x40);
  if (recorded_animation_controlling_unit(unit) != 0) {
    if (thread_handle != -1) {
      dbg_slot = (char *)((thread_handle & 0xffff) * 0x10 + *(int *)0x44df0c);
      error(2, (char *)0x269994,
            (char *)tag_block_get_element((char *)scenario + 0x36c,
                                          *(int16_t *)(dbg_slot + 0xc), 0x40));
    } else {
      error(2, (char *)0x269974);
    }
    return result;
  }

  thread = NULL;
  if (thread_handle == -1) {
    thread_handle = data_new_at_index(*(data_t **)0x44df04);
    if (thread_handle == -1) {
      error(2, (char *)0x269a2c);
      return result;
    }
    thread = (char *)datum_get(*(data_t **)0x44df04, thread_handle);
    if (thread == NULL) {
      error(2, (char *)0x269a2c);
      return result;
    }
  } else {
    thread = (char *)datum_get(*(data_t **)0x44df04, thread_handle);
  }

  anim_type = *(uint8_t *)(anim_def + 0x20);
  if (anim_type == 0 || anim_type > 4 ||
      *(void **)((char *)0x2eebac + anim_type * 4) == NULL) {
    display_assert((char *)0x2699c0,
                   "c:\\halo\\SOURCE\\cutscene\\recorded_animations.c", 0xe9,
                   1);
    system_exit(-1);
  }

  *(int *)(thread + 4) = unit;
  *(int *)(thread + 0xc) = 0;
  *(int16_t *)(thread + 8) = *(int16_t *)(anim_def + 0x24);
  *(void **)(thread + 0x10) =
      tag_data_get_pointer(anim_def + 0x2c, 0, *(int *)(anim_def + 0x2c));

  dbg_slot = (char *)((thread_handle & 0xffff) * 0x10 + *(int *)0x44df0c);
  *dbg_slot = 1;
  *(void **)(dbg_slot + 4) = *(void **)(thread + 0x10);
  *(int16_t *)(dbg_slot + 0xc) = (int16_t)anim;
  *(int *)(dbg_slot + 8) = *(int *)(anim_def + 0x2c);

  *(uint8_t *)(thread + 0xa) &= 0xfe;
  *(int16_t *)(thread + 0x60) = (int16_t)(anim_type - 1);
  vtable = *(void ***)((char *)0x2eebb0 + (anim_type - 1) * 4);
  ((void (*)(char *, char *, int *, char *))vtable[0])(
      thread + 0x54, thread + 0x14, (int *)(thread + 0x10),
      anim_def + 0x18);

  unit_set_actively_controlled(unit, 1);
  if (unit_is_alive(unit) != 0)
    *(uint8_t *)(thread + 0xa) |= 4;
  else
    *(uint8_t *)(thread + 0xa) &= 0xfb;

  unit_set_controllable(unit, 0);
  unit_set_possessed(unit, 1);
  object_set_automatic_deactivation(unit, 0);
  extra_flags = (uint16_t)flags;
  *(uint16_t *)(thread + 0xa) |= extra_flags;
  return 1;
}

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
  (void)actor;
  (void)anim_idx;
  return 0;
}
