/* --- object_lights.obj batch drafts (2026-07-26) --- */

/* 0x1391e0 */
void lights_initialize(void)
{
  int eax = 0;

  game_state_data_new((char *)0x0029b444, 896, 124);
  /* mem[0x005a90bc] = eax */
  game_state_malloc((char *)0x0029b434, (char *)0, 0);
  /* mem[0x0046f074] = eax */
  /* test eax, eax -> jne 0x139235 */
  display_assert((char *)0x0029b428, (char *)0x0029b324, 194, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x13925e */
  display_assert((char *)0x0029b414, (char *)0x0029b324, 195, 0);
  system_exit(0);
  /* test eax, eax -> je 0x139282 */
  cluster_partition_globals_new((void *)0x005a90b0, (char *)0x0025b590);
  error(0, (char *)0x0029b3e8);

  (void)eax;
}

/* 0x1392a0 */
void lights_dispose(void)
{
  cluster_partition_null_references((void *)0x005a90b0);
}

/* 0x1392b0 */
void lights_initialize_for_new_map(void)
{
  int eax = 0;

  data_delete_all((void *)(uintptr_t)eax);
  cluster_partition_clear((void *)0x005a90b0);

  (void)eax;
}

/* 0x1392e0 */
void lights_dispose_from_old_map(void)
{
  int eax = 0;

  data_make_invalid((void *)(uintptr_t)eax);
  cluster_partition_dispose((void *)0x005a90b0);

  (void)eax;
}

/* 0x139300 */
int lights_enable(int a0)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x139310 */
void light_delete(int light_handle)
{
  int eax = 0;
  int ecx = 0;

  datum_get((void *)(uintptr_t)eax, 0);
  cluster_partition_remove_object((void *)0x005a90b0, 0, (void *)(uintptr_t)eax);
  datum_delete((void *)(uintptr_t)ecx, 0);

  (void)eax;
  (void)ecx;
}

/* 0x139350 */
int16_t FUN_00139350(int light_handle, int16_t *out_buffer, int16_t max_count)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  datum_get((void *)(uintptr_t)ecx, 0);
  FUN_00191690((void *)0x005a90b0, (void *)(uintptr_t)eax, 0);
  /* test (int16_t)edi, (int16_t)edi -> jle 0x1393a4 */
  /* cmp (int16_t)eax, 0xffff -> je 0x1393a4 */
  FUN_001916d0(0, (void *)0);
  /* cmp (int16_t)esi, (int16_t)edi -> jl 0x139380 */
  return 0;

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x1393b0 */
float object_get_self_illumination(int object_handle)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  object_get_and_verify_type(0, 0);
  tag_get('ejbo', 0);
  /* test (char)ecx, (char)ecx -> jne 0x139426 */
  /* cmp eax, -1 -> je 0x139426 */
  datum_get((void *)(uintptr_t)edx, 0);
  real_rgb_color_brightness((float *)(uintptr_t)eax);
  /* cmp eax, ecx -> jl 0x1393f0 */
  /* cmp eax, -1 -> je 0x13944e */
  /* relift: tail-call object_get_self_illumination(); */
  /* cmp esi, -1 -> je 0x13946c */
  /* relift: tail-call object_get_self_illumination(); */
  return 0;

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x139480 */
void FUN_00139480(void *position, void *tint_color, void *out_color, char use_lightmap)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  structure_test_vector((float *)(uintptr_t)edx, (void *)0x0029b204, (float *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x1396d8 */
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 32);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_get('rdhs', 0);
  /* relift: cmp word ptr [eax + 0x24], 3 -> jne 0x1396d5 */
  FUN_001906b0((void *)(uintptr_t)eax, 0);
  /* cmp eax, -1 -> je 0x1396d5 */
  /* relift: cmp dword ptr [edi + 0x94], -1 -> je 0x1396d5 */
  /* cmp (int16_t)ecx, -1 -> je 0x1396d5 */
  FUN_00076ff0(0, 0);
  tag_get('mtib', 0);
  FUN_00076ff0(0, 0);
  /* test (char)eax, (char)eax -> je 0x1395c7 */
  FUN_00138ee0(0);
  /* test eax, eax -> jne 0x1395dc */
  xbox_texture_cache_get_hardware_format((void *)(uintptr_t)esi, 0, 0);
  /* test eax, eax -> je 0x13966e */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  FUN_00138fd0(0, 0, (void *)(uintptr_t)edi, 0.0f, 0.0f, 0);
  /* test (char)eax, 0x41 -> jne 0x13962a */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x13964a */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x13966b */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* test eax, eax -> je 0x1396d5 */
  /* test (char)ecx, (char)ecx -> je 0x139689 */
  FUN_00138ee0(0);
  /* test eax, eax -> jne 0x13969d */
  xbox_texture_cache_get_hardware_format((void *)(uintptr_t)edx, 0, 0);
  /* test eax, eax -> je 0x1396d5 */
  /* test edi, edi -> jne 0x1396bb */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  FUN_001390d0(0, 0, (void *)(uintptr_t)edi, 0.0f, 0.0f, (float *)(uintptr_t)edx);
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)eax, 2 -> je 0x13973b */
  /* test (char)eax, 4 -> jne 0x139725 */
  display_assert((char *)0x0029b44c, (char *)0x0029b324, 1232, 0);
  system_exit(0);
  cluster_partition_remove_object((void *)0x005a90b0, 0, (void *)(uintptr_t)ecx);
  data_next_index((void *)(uintptr_t)eax, 0);
  /* cmp edi, -1 -> je 0x1397ee */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, 4 -> je 0x1397d1 */
  datum_get((void *)(uintptr_t)edx, 0);
  /* test (char)eax, 2 -> je 0x1397cd */
  /* test (char)eax, 4 -> jne 0x1397b7 */
  display_assert((char *)0x0029b44c, (char *)0x0029b324, 1232, 0);
  system_exit(0);
  cluster_partition_remove_object((void *)0x005a90b0, 0, (void *)(uintptr_t)eax);
  data_next_index((void *)(uintptr_t)ecx, 0);
  /* cmp edi, -1 -> jne 0x139760 */
  /* test (char)eax, 0x41 -> jne 0x139826 */
  /* test (char)eax, 0x41 -> jne 0x139848 */
  /* test (char)eax, 0x41 -> jne 0x139870 */
  /* relift: relift: fld dword ptr [0x2533c8] */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
