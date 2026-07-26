/* --- devices.obj batch drafts (2026-07-26) --- */

/* 0x960c0 */
void device_new(void)
{
  object_get_and_verify_type(0, 896);
  tag_get('ived', 0);
}

/* 0x96110 */
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

/* 0x96310 */
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
  overlay_animation_apply();
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

/* 0x96470 */
int device_get_position(int a0)
{
  int eax = 0;

  /* cmp eax, -1 -> je 0x96491 */
  object_get_and_verify_type(0, 896);
  return 0;

  (void)eax;
}

/* 0x964a0 */
int device_get_power(int a0)
{
  int eax = 0;

  /* cmp eax, -1 -> je 0x964c1 */
  object_get_and_verify_type(0, 896);
  return 0;

  (void)eax;
}

/* 0x964d0 */
void device_set_never_appears_locked(int a0, int a1)
{
  int eax = 0;

  /* cmp eax, -1 -> je 0x9650e */
  object_try_and_get_and_verify_type(0, 128);
  /* test eax, eax -> je 0x9650e */

  (void)eax;
}

/* 0x96510 */
void device_group_set_actual_value(int a0, float a1)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test (char)eax, 0x41 -> jne 0x96546 */
  datum_get((void *)(uintptr_t)ecx, 0);
  object_iterator_new((void *)(uintptr_t)eax, 896, 0);
  object_iterator_next((void *)(uintptr_t)ecx);
  /* cmp eax, edi -> je 0x965e5 */
  /* relift: cmp word ptr [eax + 0x1a8], (int16_t)esi -> jne 0x965b6 */
  /* relift: cmp word ptr [eax + 0x1b4], (int16_t)esi -> jne 0x965d4 */
  object_iterator_next((void *)(uintptr_t)edx);
  /* cmp eax, edi -> jne 0x96590 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x965f0 */
void device_one_sided_set(int a0, int a1)
{
  int eax = 0;

  object_try_and_get_and_verify_type(0, 128);
  /* test eax, eax -> je 0x96629 */

  (void)eax;
}

/* 0x96630 */
void device_operates_automatically_set(int a0, int a1)
{
  int eax = 0;

  object_try_and_get_and_verify_type(0, 128);
  /* test eax, eax -> je 0x96669 */

  (void)eax;
}

/* 0x96670 */
void device_group_change_only_once_more_set(int a0, int a1)
{
  int eax = 0;
  int ecx = 0;

  /* cmp eax, -1 -> je 0x966a3 */
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)ecx, (char)ecx -> je 0x9669b */

  (void)eax;
  (void)ecx;
}

/* 0x966b0 */
int device_group_get_value(int a0)
{
  int ecx = 0;

  datum_get((void *)(uintptr_t)ecx, 0);
  return 0;

  (void)ecx;
}

/* 0x966d0 */
void device_group_set_real(int device_group_handle, int unit_handle)
{
  object_get_and_verify_type(0, 896);
  FUN_000958f0(0);
  FUN_00095be0(0);
}

/* 0x96720 */
bool device_can_change_position(int object_handle)
{
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  object_get_and_verify_type(0, 896);
  /* cmp (int16_t)ecx, -1 -> je 0x9679a */
  datum_get((void *)(uintptr_t)edx, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)ecx, 2 -> je 0x96784 */
  /* relift: test byte ptr [edi + 0x1a4], 2 -> je 0x9678f */
  /* relift: cmp dword ptr [edx + 4], 0x3f800000 -> je 0x9679a */
  return 0;

  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x967a0 */
void FUN_000967a0(void *rec, int object)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;

  /* cmp ebx, -1 -> je 0x9683f */
  object_get_and_verify_type(0, 896);
  tag_get_group_tag(0);
  /* cmp eax, 0x65666665 -> je 0x9681e */
  /* cmp eax, 0x736e6421 -> je 0x967fb */
  display_assert((char *)0, (char *)0x00269ac4, 761, 0);
  system_exit(0);
  object_impulse_sound_new(0, 0, 0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0.0f);
  FUN_0009ec30(0, 0, 0, 0, 0.0f, 0.0f, 0, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
}

/* 0x96850 */
void device_effect_new(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  data_new_at_index((void *)(uintptr_t)eax);
  /* cmp (int16_t)esi, -1 -> je 0x96891 */
  datum_get((void *)(uintptr_t)edx, 0);
  display_assert((char *)0x00269af8, (char *)0x00269ac4, 785, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 0xffff -> je 0x968f2 */
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)ecx, 4 -> je 0x968f1 */
  datum_delete((void *)(uintptr_t)ecx, 0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x96900 */
void create_initial_device_groups(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 52);
  /* test (char)ecx, 1 -> je 0x96941 */
  data_new_at_index((void *)(uintptr_t)ecx);
  /* cmp (int16_t)edi, -1 -> je 0x9697c */
  datum_get((void *)(uintptr_t)eax, 0);
  display_assert((char *)0x00269af8, (char *)0x00269ac4, 785, 0);
  system_exit(0);
  /* cmp (int16_t)edi, (int16_t)esi -> je 0x969c4 */
  display_assert((char *)0x00269b14, (char *)0x00269ac4, 825, 0);
  system_exit(0);
  data_delete_all((void *)(uintptr_t)eax);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x96a00 */
void device_delete(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  object_get_and_verify_type(0, 896);
  /* cmp (int16_t)eax, 0xffff -> je 0x96a50 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)ecx, 4 -> je 0x96a50 */
  datum_delete((void *)(uintptr_t)edx, 0);
  /* cmp (int16_t)eax, 0xffff -> je 0x96a87 */
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)ecx, 4 -> je 0x96a87 */
  datum_delete((void *)(uintptr_t)ecx, 0);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x96a90 */
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
