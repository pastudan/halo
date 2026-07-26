/* --- ai_script.obj batch drafts (2026-07-26) --- */

/* 0x58cc0 */
void ai_scripting_follow_distance(int a0, int a1, int a2)
{
  int eax = 0;
  int edi = 0;

  global_scenario_get();
  FUN_00054220(edi, (void *)(uintptr_t)eax, (char *)0, 0);
  hs_runtime_get_executing_thread_name();
  error(0, (char *)0x0025d1d0);
  FUN_00058af0(0, 0, (void *)0, 0);

  (void)eax;
  (void)edi;
}

/* 0x58d40 */
void FUN_00058d40(int a0)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  global_scenario_get();
  FUN_00054220(esi, (void *)(uintptr_t)eax, (char *)0, 0);
  hs_runtime_get_executing_thread_name();
  error(0, (char *)0x0025d1fc);
  FUN_00054680(esi, (void *)(uintptr_t)edx);
  FUN_00054750((void *)(uintptr_t)eax);
  /* test esi, esi -> je 0x58ea4 */
  /* cmp eax, edi -> je 0x58e8c */
  tag_get('vtca', 0);
  object_get_and_verify_type(0, 0);
  /* test (char)eax, 0x41 -> jne 0x58df9 */
  /* test (char)eax, 0x41 -> jne 0x58e20 */
  /* relift: cmp word ptr [ebx + 0x180], (int16_t)edi -> je 0x58e8c */
  get_global_random_seed_address();
  random_range((void *)(uintptr_t)eax, 0, 0);
  unit_get_current_grenade_type(0);
  unit_get_grenade_count(0, eax);
  /* cmp (int16_t)eax, (int16_t)edi -> jge 0x58e8c */
  unit_set_grenade_count(0, edx, edi);
  FUN_00054750((void *)(uintptr_t)ecx);
  /* test esi, esi -> jne 0x58db0 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x58eb0 */
void FUN_00058eb0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  game_state_data_new((char *)0x00254868, 128, 108);
  /* mem[0x005ab270] = eax */
  display_assert((char *)0x0025d26c, (char *)0x0025d27c, 110, 0);
  system_exit(0);
  game_state_malloc((char *)0x0025d264, (char *)0x0025d264, 32768);
  /* mem[0x005ab278] = eax */
  display_assert((char *)0x0025d258, (char *)0x0025d27c, 113, 0);
  system_exit(0);
  game_state_malloc((char *)0x0025d250, (char *)0x0025d250, 4096);
  /* mem[0x005ab274] = eax */
  display_assert((char *)0x0025d240, (char *)0x0025d27c, 116, 0);
  system_exit(0);
  game_state_data_new((char *)0x0025d234, 256, 40);
  /* mem[0x005ab26c] = eax */
  display_assert((char *)0x0025d224, (char *)0x0025d27c, 119, 0);
  system_exit(0);
  data_make_invalid((void *)(uintptr_t)eax);
  data_make_invalid((void *)(uintptr_t)ecx);
  scenario_get();
  datum_get((void *)(uintptr_t)eax, 0);
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  display_assert((char *)0x0025d390, (char *)0x0025d27c, 355, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)ebx, 0, edx);
  /* cmp edi, -1 -> je 0x59477 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp esi, -1 -> je 0x592b8 */
  object_get_and_verify_type(0, 0);
  object_get_root_parent(0);
  object_get_and_verify_type(0, 0);
  /* cmp (int16_t)esi, -1 -> je 0x59122 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x590da */
  /* cmp edx, eax -> jl 0x590fa */
  display_assert((char *)0x0025d354, (char *)0x0025d27c, 382, 0);
  system_exit(0);
  /* test ecx, ecx -> je 0x59122 */
  /* relift: test dword ptr [eax + ecx], edx -> je 0x59122 */
  /* cmp esi, -1 -> jne 0x590a6 */
  object_get_and_verify_type(0, 0);
  object_get_root_parent(0);
  object_get_and_verify_type(0, 0);
  /* cmp (int16_t)esi, -1 -> je 0x591b9 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x59171 */
  /* cmp eax, ecx -> jl 0x59191 */
  display_assert((char *)0x0025d354, (char *)0x0025d27c, 408, 0);
  system_exit(0);
  /* test ecx, ecx -> je 0x591b9 */
  /* relift: test dword ptr [eax + ecx], edx -> je 0x591b9 */
  /* test (char)eax, (char)eax -> je 0x592b8 */
  /* cmp (int16_t)eax, 3 -> jne 0x59229 */
  /* relift: cmp word ptr [esi + 0x6e], 2 -> jl 0x591f0 */
  actor_get_firing_position_group(0, 0, 0);
  /* cmp (int16_t)eax, 6 -> je 0x59223 */
  /* cmp (int16_t)eax, 4 -> je 0x59223 */
  /* cmp (int16_t)eax, 3 -> je 0x5920c */
  /* cmp (int16_t)eax, 5 -> jne 0x5924b */
  actor_get_firing_position_group(0, 0, 0);
  /* cmp (int16_t)eax, 2 -> jne 0x5924b */
  /* relift: cmp word ptr [esi + 0x9c], 0 -> je 0x5924b */
  /* cmp eax, -1 -> je 0x592b8 */
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp (int16_t)esi, -1 -> je 0x592b8 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x59281 */
  /* cmp ecx, eax -> jl 0x592a1 */
  display_assert((char *)0x0025d354, (char *)0x0025d27c, 448, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
