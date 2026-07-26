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
