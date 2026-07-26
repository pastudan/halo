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
void control_toggle(void);

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

void FUN_00094290(void) {}

void FUN_00094a70(int a, int *cursor, int c)
{
  FUN_00093780(a, cursor, c);
}

void FUN_00094ba0(void) {}

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
    control_toggle();
}

void FUN_00095930(int object)
{
  char *dev = (char *)object_get_and_verify_type(object, 0x100);
  char *tag = (char *)tag_get(*(int *)dev, 0x6374726c);

  if (*(int16_t *)(tag + 0x292) == 1)
    control_toggle();
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
