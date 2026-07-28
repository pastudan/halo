#include <stdint.h>
/* --- devices.obj batch drafts (2026-07-26) --- */

/* device_new (0x960c0) — readable C lift. */
char device_new(int object_handle)
{
  char *obj = (char *)object_get_and_verify_type(object_handle, 0x380);
  tag_get(0x64657669, *(int *)obj);
  *(unsigned short *)(obj + 0x1b4) = 0xffff;
  *(unsigned short *)(obj + 0x1a8) = 0xffff;
  *(unsigned int *)(obj + 4) |= 0x40000u;
  return 1;
}

/* device_export_function_values (0x96110) — readable C lift (restored pre-naked). */
void device_export_function_values(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  object_get_and_verify_type(0, 896);
  tag_get('ived', 0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x96292 */
  /* cmp eax, 5 -> ja 0x9628d */
  /* relift: cmp word ptr [edi + 0x64], 7 -> jne 0x9628d */
  /* relift: cmp word ptr [edi + 0x1b4], -1 -> je 0x9628d */
  object_get_and_verify_type(0, 128);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)ecx, 3 -> je 0x9625d */
  /* test (char)eax, 1 -> je 0x96274 */
  /* test (char)eax, 2 -> je 0x96274 */
  /* relift: cmp dword ptr [esi + 0x1b8], 0x3f800000 -> je 0x96285 */
  /* test (char)ecx, 4 -> je 0x9628d */

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}


/* device_preprocess_node_orientations (0x96310) — readable C lift (restored pre-naked). */
void device_preprocess_node_orientations(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  object_get_and_verify_type(0, 896);
  tag_get('ived', 0);
  tag_get('rtna', 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 96);
  /* test esi, esi -> je 0x96465 */
  /* test eax, eax -> jle 0x9641c */
  /* cmp (int16_t)eax, 0xffff -> je 0x9641c */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  /* test (char)eax, 1 -> je 0x963be */
  /* test (char)eax, 1 -> je 0x963dd */
  FUN_001d9068();
  overlay_animation_apply(0, 0, 0);
  FUN_00122690((void *)(uintptr_t)ebx, 0.0f, (void *)(uintptr_t)ecx);
  /* relift: cmp dword ptr [esi + 0x54], 1 -> jle 0x96465 */
  /* cmp (int16_t)eax, 0xffff -> je 0x96465 */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  FUN_00122690((void *)(uintptr_t)eax, 0.0f, (void *)0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}


/* device_get_position (0x96470) — readable C lift. */
float device_get_position(int a0)
{
  if (a0 == -1)
    return 0.0f;
  void *obj = object_get_and_verify_type(a0, 0x380);
  return *(float *)((char *)obj + 0x1b8);
}

/* device_get_power (0x964a0) — readable C lift. */
float device_get_power(int a0)
{
  if (a0 == -1)
    return 0.0f;
  void *obj = object_get_and_verify_type(a0, 0x380);
  return *(float *)((char *)obj + 0x1ac);
}

/* device_set_never_appears_locked (0x964d0) — readable C lift (assert wrapper). */
void device_set_never_appears_locked(int a0, int a1)
{
  if (a0 == -1) {
    return;
  }
  {
    void *obj = object_try_and_get_and_verify_type(a0, 0x80);
    if (!obj) {
      return;
    }
    uint32_t flags = *(uint32_t *)((char *)obj + 0x1c4);
    if (a1) {
      flags |= 4;
    }
    *(uint32_t *)((char *)obj + 0x1c4) = flags;
  }
}

/* device_group_set_actual_value (0x96510) — readable C lift. */
void device_group_set_actual_value(int a0, float a1)
{
  int16_t group_index;
  char *group;
  unsigned char iter[0x10];
  char *obj;
  float value;

  value = a1;
  if (!(value >= 0.0f))
    value = 0.0f;
  else if (value > 1.0f)
    value = 1.0f;
  group_index = (int16_t)a0;
  group = (char *)datum_get(*(data_t **)0x5aa8c8, (int)group_index);
  *(float *)(group + 4) = value;
  object_iterator_new(iter, 0x380, 0);
  for (obj = (char *)object_iterator_next(iter); obj != NULL;
       obj = (char *)object_iterator_next(iter)) {
    if (*(int16_t *)(obj + 0x1a8) == group_index) {
      *(int *)(obj + 0x1a4) |= 4;
      *(float *)(obj + 0x1ac) = value;
      *(int *)(obj + 0x1b0) = 0;
    }
    if (*(int16_t *)(obj + 0x1b4) == group_index) {
      *(int *)(obj + 0x1a4) |= 4;
      *(float *)(obj + 0x1b8) = value;
      *(int *)(obj + 0x1bc) = 0;
    }
  }
}

/* device_one_sided_set (0x965f0) — readable C lift (assert wrapper). */
void device_one_sided_set(int a0, int a1)
{
  {
    void *obj = object_try_and_get_and_verify_type(a0, 0x80);
    if (!obj) {
      return;
    }
    uint32_t flags = *(uint32_t *)((char *)obj + 0x1c4);
    if (a1) {
      flags |= 2;
    }
    *(uint32_t *)((char *)obj + 0x1c4) = flags;
  }
}

/* device_operates_automatically_set (0x96630) — readable C lift (assert wrapper). */
void device_operates_automatically_set(int a0, int a1)
{
  {
    void *obj = object_try_and_get_and_verify_type(a0, 0x80);
    if (!obj) {
      return;
    }
    uint32_t flags = *(uint32_t *)((char *)obj + 0x1c4);
    if (!a1) {
      flags |= 1;
    }
    *(uint32_t *)((char *)obj + 0x1c4) = flags;
  }
}

/* device_group_change_only_once_more_set (0x96670) — readable C lift. */
void device_group_change_only_once_more_set(int a0, int a1)
{
  if (a0 == -1)
    return;
  unsigned char *d = (unsigned char *)datum_get(*(void **)0x5aa8c8, a0);
  if (a1) {
    d[2] |= 1;
    d[2] &= (unsigned char)0xfd;
  } else {
    d[2] &= (unsigned char)0xfe;
    d[2] &= (unsigned char)0xfd;
  }
}

/* device_group_get_value (0x966b0) — readable C lift. */
float device_group_get_value(int a0)
{
  extern data_t *DAT_005aa8c8;
  char *g = (char *)datum_get(DAT_005aa8c8, (int)(int16_t)a0);
  return *(float *)(g + 4);
}

/* device_can_change_position (0x96720) — readable C lift. */
bool device_can_change_position(int object_handle)
{
  extern data_t *DAT_005aa8c8;
  char *obj;
  char *group_a;
  char *group_b;
  int16_t group_index;
  unsigned char flags;
  char ok;

  obj = (char *)object_get_and_verify_type(object_handle, 0x380);
  group_index = *(int16_t *)(obj + 0x1b4);
  ok = 0;
  if (group_index == -1)
    return (bool)ok;

  group_a = (char *)datum_get(DAT_005aa8c8, (int)group_index);
  group_b = (char *)datum_get(DAT_005aa8c8, (int)*(int16_t *)(obj + 0x1a8));
  flags = (unsigned char)*(uint16_t *)(group_a + 2);
  ok = 1;
  if ((flags & 1) && (flags & 2))
    ok = 0;
  if ((*(unsigned char *)(obj + 0x1a4) & 2) != 0)
    ok = 0;
  if (*(int *)(group_b + 4) != 0x3f800000)
    ok = 0;
  return (bool)ok;
}

/* FUN_000967a0 (0x967a0) — readable C lift. */
void FUN_000967a0(void *rec, int object)
{
  char *device;
  int group;
  extern char DAT_00269ac4[];

  if (object == -1)
    return;
  device = (char *)object_get_and_verify_type((int)rec, 0x380);
  group = tag_get_group_tag(object);
  if (group == 0x65666665) { /* 'effe' */
    FUN_0009ec30(object, (int)rec, (int)rec, -1,
                 *(float *)(device + 0x1b8), *(float *)(device + 0x1ac), 0, 0);
    return;
  }
  if (group == 0x736e6421) { /* 'snd!' */
    object_impulse_sound_new((int)rec, object, (int16_t)-1, (float *)0x31fc1c,
                             (float *)0x31fc3c, 1.0f);
    return;
  }
  display_assert((const char *)0, DAT_00269ac4, 0x2f9, 1);
  system_exit(-1);
}



/* device_effect_new (0x96850) — readable C lift. */
int16_t device_effect_new(int a, int16_t b)
{
  extern char DAT_00269af8[];
  extern char DAT_00269ac4[];
  int16_t idx = (int16_t)data_new_at_index(*(data_t **)0x5aa8c8);
  char *d;
  if (idx == -1) {
    display_assert(DAT_00269af8, DAT_00269ac4, 0x311, 1);
    system_exit(-1);
    return idx;
  }
  d = (char *)datum_get(*(data_t **)0x5aa8c8, idx);
  *(int *)(d + 4) = a;
  *(int16_t *)(d + 2) = b;
  return idx;
}

/* create_initial_device_groups (0x96900) — readable C lift. */
void create_initial_device_groups(void)
{
  extern char DAT_00269ac4[];
  extern char DAT_00269af8[];
  extern char DAT_00269b14[];
  char *scenario;
  char *block;
  int i;
  int count;
  char *elem;
  int name_index;
  short flags;
  short handle;
  char *rec;

  scenario = (char *)global_scenario_get();
  block = scenario + 0x288;
  count = *(int *)block;
  for (i = 0; i < count; i++) {
    elem = (char *)tag_block_get_element(block, i, 0x34);
    flags = 0;
    if ((elem[0x24] & 1) != 0)
      flags = 1;
    name_index = *(int *)(elem + 0x20);
    handle = (short)data_new_at_index(*(data_t **)0x5aa8c8);
    if (handle == (short)0xffff) {
      display_assert(DAT_00269af8, DAT_00269ac4, 0x311, 1);
      system_exit(-1);
    } else {
      rec = (char *)datum_get(*(data_t **)0x5aa8c8, (int)handle);
      *(int *)(rec + 4) = name_index;
      *(short *)(rec + 2) = flags;
    }
    if (handle != (short)i) {
      display_assert(DAT_00269b14, DAT_00269ac4, 0x339, 1);
      system_exit(-1);
    }
  }
}
/* device_delete (0x96a00) — readable C lift. */
void device_delete(int object_handle)
{
  char *device;
  short idx;
  char *rec;

  device = (char *)object_get_and_verify_type(object_handle, 0x380);
  idx = *(short *)(device + 0x1a8);
  if (idx != (short)0xffff) {
    rec = (char *)datum_get(*(void **)0x5aa8c8, (int)idx);
    if ((*(unsigned char *)(rec + 2) & 4) != 0)
      datum_delete(*(data_t **)0x5aa8c8, (int)idx);
  }
  idx = *(short *)(device + 0x1b4);
  if (idx != (short)0xffff) {
    rec = (char *)datum_get(*(void **)0x5aa8c8, (int)idx);
    if ((*(unsigned char *)(rec + 2) & 4) != 0)
      datum_delete(*(data_t **)0x5aa8c8, (int)idx);
  }
}


/* FUN_00096a90 (0x96a90) — readable C lift (restored pre-naked). */
void FUN_00096a90(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;

  object_get_and_verify_type(0, 896);
  tag_get('ived', 0);
  datum_get((void *)(uintptr_t)eax, 0);
  accelerate_to_position((float *)(uintptr_t)ebx, (float *)(uintptr_t)ecx, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0);
  /* test (char)eax, (char)eax -> jne 0x96b41 */
  /* cmp (int16_t)eax, 0xffff -> je 0x96d65 */
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)eax, 0x41 -> je 0x96c0b */
  /* test (char)eax, 1 -> je 0x96c77 */
  FUN_000967a0((void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> jne 0x96c9d */
  accelerate_to_position((float *)(uintptr_t)ecx, (float *)(uintptr_t)ebx, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, eax);
  /* test (char)eax, (char)eax -> je 0x96d02 */
  /* test (char)eax, (char)eax -> je 0x96ced */
  FUN_000967a0((void *)(uintptr_t)ecx, 0);
  FUN_000967a0((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, 0x41 -> jne 0x96d37 */
  FUN_000967a0((void *)(uintptr_t)edx, 0);
  object_get_and_verify_type(0, 896);
  /* test (char)eax, (char)eax -> je 0x96f14 */
  csstrcpy((char *)(uintptr_t)eax, (char *)0x0025386f);
  csstrlen((char *)(uintptr_t)ecx);
  crt_sprintf((char *)(uintptr_t)edx, (char *)0);
  /* cmp (int16_t)eax, 0xffff -> je 0x96e34 */
  datum_get((void *)(uintptr_t)ecx, 0);
  csstrlen((char *)(uintptr_t)eax);
  crt_sprintf((char *)(uintptr_t)ecx, (char *)0);
  csstrlen((char *)(uintptr_t)edx);
  crt_sprintf((char *)(uintptr_t)eax, (char *)0);
  /* cmp (int16_t)eax, 0xffff -> je 0x96ebd */
  datum_get((void *)(uintptr_t)edx, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
}

