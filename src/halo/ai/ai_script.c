/* --- ai_script.obj batch drafts (2026-07-26) --- */

/* ai_scripting_follow_distance (0x58cc0) — readable C lift. */
void ai_scripting_follow_distance(int encounter_handle, int actor_handle, int seat_list)
{
  char buf[0x100];

  if (*(char *)0x5aca59) {
    FUN_00054220(encounter_handle, global_scenario_get(), buf, 0x100);
    error(2, (const char *)0x25d1d0, hs_runtime_get_executing_thread_name());
    (void)actor_handle;
  }
  ((void (*)(int, int, int))(void *)&FUN_00058af0)(seat_list, 1, encounter_handle);
}

/* FUN_00058d40 (0x58d40) — readable C lift (restored pre-naked). */
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


/* FUN_00058eb0 (0x58eb0) — readable C lift. */
void FUN_00058eb0(void)
{
  void *p;

  p = game_state_data_new((char *)0x254868, 0x80, 0x6c);
  *(void **)0x5ab270 = p;
  if (p == 0) {
    display_assert((const char *)0x25d26c, (const char *)0x25d27c, 0x6e, 1);
    system_exit(-1);
  }
  p = game_state_malloc((const char *)0x25d264, (const char *)0x25d264, 0x8000);
  *(void **)0x5ab278 = p;
  if (p == 0) {
    display_assert((const char *)0x25d258, (const char *)0x25d27c, 0x71, 1);
    system_exit(-1);
  }
  p = game_state_malloc((const char *)0x25d250, (const char *)0x25d250, 0x1000);
  *(void **)0x5ab274 = p;
  if (p == 0) {
    display_assert((const char *)0x25d240, (const char *)0x25d27c, 0x74, 1);
    system_exit(-1);
  }
  p = game_state_data_new((char *)0x25d234, 0x100, 0x28);
  *(void **)0x5ab26c = p;
  if (p == 0) {
    display_assert((const char *)0x25d224, (const char *)0x25d27c, 0x77, 1);
    system_exit(-1);
  }
}

