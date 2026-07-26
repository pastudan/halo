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
