/* --- actor_firing_position.obj batch drafts (2026-07-26) --- */

/* 0x24000 */
void FUN_00024000(void *ctx, float score, int type, void *position)
{
  int eax = 0;

  /* test (char)eax, 1 -> jne 0x24023 */
  display_assert((char *)0x00254c5c, (char *)0x00254c8c, 129, 0);
  system_exit(0);

  (void)eax;
}

/* 0x24060 */
void FUN_00024060(void)
{
  int eax = 0;

  /* test (int16_t)eax, (int16_t)eax -> jle 0x2412b */
  /* test (char)eax, (char)eax -> je 0x2411e */
  /* test (char)eax, 1 -> jne 0x240f5 */
  display_assert((char *)0x00254c5c, (char *)0x00254c8c, 129, 0);
  system_exit(0);

  (void)eax;
}

/* 0x24130 */
void FUN_00024130(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  datum_get((void *)(uintptr_t)eax, 0);
  actor_combat_get_firing_variant_definition(0);
  /* test (char)eax, 0x41 -> je 0x2424e */
  /* test (char)eax, 0x41 -> jne 0x2424e */
  /* test (int16_t)ebx, (int16_t)ebx -> jle 0x2424e */
  /* test (char)eax, (char)eax -> je 0x24244 */
  /* test (char)eax, 0x41 -> jne 0x241f5 */
  /* test (char)eax, 1 -> jne 0x24218 */
  display_assert((char *)0x00254c5c, (char *)0x00254c8c, 129, 0);
  system_exit(0);
  /* relift: cmp word ptr [edx + 0x256], 0 -> jle 0x24360 */
  /* test (int16_t)ebx, (int16_t)ebx -> jle 0x24360 */
  /* relift: cmp word ptr [edx + 0x254], (int16_t)edi -> jle 0x24340 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x242ae */
  /* cmp (int16_t)eax, 1 -> jne 0x242f8 */
  actor_perception_aiming_vector_test_blockage();
  /* test (int16_t)esi, (int16_t)esi -> jne 0x242eb */
  /* cmp (int16_t)ecx, (int16_t)eax -> jle 0x242e6 */
  /* cmp (int16_t)esi, 1 -> jne 0x242f8 */
  /* cmp (int16_t)ebx, (int16_t)eax -> jg 0x242f8 */
  /* relift: cmp (int16_t)edi, word ptr [edx + 0x254] -> jl 0x24293 */
  /* cmp (int16_t)ebx, 2 -> jl 0x24313 */
  /* cmp (int16_t)ebx, 1 -> jl 0x24321 */
  /* cmp (int16_t)eax, 2 -> jl 0x24332 */
  /* cmp (int16_t)eax, 1 -> jl 0x24340 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x24370 */
void FUN_00024370(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  datum_get((void *)(uintptr_t)eax, 0);
  tag_get('rtca', 0);
  /* test (char)ecx, (char)ecx -> je 0x2442f */
  /* test esi, esi -> jne 0x243c9 */
  actor_path_3d_available(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x2441d */
  scenario_get();
  path_3d_available(0, (void *)0, 0, (void *)0, (unsigned char *)0, (float *)0);
  /* test (char)eax, (char)eax -> je 0x2441d */
  FUN_00024000((void *)(uintptr_t)eax, 0.0f, 25, (void *)0);
  /* test (char)eax, (char)eax -> jne 0x2442f */
  /* test esi, esi -> jne 0x2443d */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x24450 */
void FUN_00024450(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  datum_get((void *)(uintptr_t)ecx, 0);
  game_time_get();
  encounter_mark_examined_pursuit_position(0, 0, eax, 0);
  encounter_pursuit_position_already_examined(0, 0, ecx, 0, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx);
  /* test dl, dl -> je 0x24530 */
  /* test (char)ebx, (char)ebx -> je 0x24542 */
  FUN_00024000((void *)(uintptr_t)edi, 0.0f, 0, (void *)0);
  /* test (char)ebx, (char)ebx -> jne 0x24542 */
  /* test dl, dl -> jne 0x24542 */
  /* test dl, dl -> je 0x245c4 */
  /* cmp edx, eax -> jl 0x24576 */
  /* cmp ecx, eax -> jge 0x2457d */
  FUN_00024000((void *)(uintptr_t)edi, 0.0f, 0, (void *)0);
  FUN_00024000((void *)(uintptr_t)edi, 0.0f, 0, (void *)0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x245d0 */
void post_evaluator_hide(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* test (char)eax, (char)eax -> je 0x24687 */
  /* test esi, esi -> jne 0x24608 */
  /* test (char)eax, (char)eax -> je 0x2464a */
  /* test (char)eax, (char)eax -> jne 0x24678 */
  display_assert((char *)0, (char *)0x00254c8c, 1117, 0);
  system_exit(0);
  FUN_00024000((void *)(uintptr_t)edi, 0.0f, 18, (void *)0);
  /* test esi, esi -> jne 0x24694 */

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x246b0 */
void FUN_000246b0(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x246e6 */
  /* test (char)eax, 0x41 -> jne 0x24749 */
  /* test (char)eax, (char)eax -> jne 0x24749 */
  FUN_00024000((void *)(uintptr_t)ecx, 0.0f, 20, (void *)0);
  /* test esi, esi -> jne 0x24764 */

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x24770 */
void FUN_00024770(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x247ca */
  /* test (char)ecx, (char)ecx -> je 0x247b0 */
  /* test (char)ecx, (char)ecx -> jne 0x24826 */
  /* test (char)ecx, (char)ecx -> jne 0x24826 */
  /* test (char)ecx, (char)ecx -> je 0x24805 */
  FUN_00024000((void *)(uintptr_t)eax, 0.0f, 14, (void *)0);
  /* test esi, esi -> jne 0x24841 */

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x24850 */
void FUN_00024850(int actor_handle, int flag, char *actor, void *state)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x24890 */
char FUN_00024890(int actor_handle, void *state, char *actor)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;

  /* test eax, eax -> je 0x248cf */
  /* test ecx, edx -> je 0x248c8 */
  /* test (char)ebx, (char)ebx -> jne 0x248a0 */
  /* relift: cmp byte ptr [edx + 0x30], (char)ebx -> je 0x248f7 */
  display_assert((char *)0x00254cd4, (char *)0x00254c8c, 1262, 0);
  system_exit(0);
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
}

/* 0x24900 */
char FUN_00024900(int actor_handle, void *query_buf)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x24950 */
int FUN_00024950(int index1, int index2)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x24991 */
  display_assert((char *)0x00254d88, (char *)0x00254c8c, 1295, 0);
  system_exit(0);
  /* test ebx, ebx -> jl 0x249a0 */
  /* cmp ebx, eax -> jl 0x249c0 */
  display_assert((char *)0x00254d40, (char *)0x00254c8c, 1296, 0);
  system_exit(0);
  /* test eax, eax -> jl 0x249d2 */
  /* cmp eax, ecx -> jl 0x249f2 */
  display_assert((char *)0x00254cf8, (char *)0x00254c8c, 1297, 0);
  system_exit(0);
  /* relift: cmp (char)eax, byte ptr [edi + 0x30] -> je 0x24a11 */
  /* relift: cmp (char)eax, byte ptr [edi + 0x31] -> je 0x24a30 */
  /* test (char)eax, 0x41 -> je 0x24a51 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edi;
}

/* 0x24a60 */
int actor_get_firing_position_group(int actor_handle, short param_2, int param_3)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp ecx, -1 -> je 0x24b70 */
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* cmp (int16_t)eax, 1 -> jne 0x24aee */
  /* cmp (int16_t)eax, 4 -> jne 0x24b06 */
  /* cmp (int16_t)eax, 5 -> jne 0x24b1c */
  /* test (char)eax, (char)eax -> je 0x24b34 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x24b48 */
  /* cmp (int16_t)esi, 7 -> jl 0x24b68 */
  display_assert((char *)0x00254db4, (char *)0x00254c8c, 1412, 0);
  system_exit(0);
  return 0;

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x24b80 */
void actor_clear_discarded_firing_positions(int actor_handle, int param2)
{
  int ecx = 0;

  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)ecx, (char)ecx -> je 0x24bdd */
  /* test (char)ecx, (char)ecx -> je 0x24bd6 */
  /* test (char)ecx, (char)ecx -> je 0x24bdd */

  (void)ecx;
}

/* 0x24be0 */
void FUN_00024be0(int actor_handle, short param_2, char param_3)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp (int16_t)edi, -1 -> je 0x24c9d */
  datum_get((void *)(uintptr_t)ecx, 0);
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp (int16_t)esi, -1 -> je 0x24cea */
  /* relift: cmp (int16_t)esi, word ptr [edx + edi*4 + 0x3ca] -> je 0x24ce8 */
  /* cmp (int16_t)ecx, 4 -> jl 0x24cd0 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x25148 */
  /* test (char)eax, (char)eax -> je 0x25135 */
  FUN_00024ca0(0, 0);
  /* test (char)eax, (char)eax -> je 0x24d69 */
  /* test (char)eax, (char)eax -> jne 0x24d69 */
  /* test (char)eax, (char)eax -> je 0x24ff3 */
  /* relift: cmp word ptr [edi + 0x280], 0 -> jle 0x24d88 */
  /* test (char)eax, (char)eax -> jne 0x24da8 */
  display_assert((char *)0x00254e08, (char *)0x00254c8c, 186, 0);
  system_exit(0);
  FUN_0010cd40((float *)(uintptr_t)ecx, (float *)(uintptr_t)ebx, (float *)(uintptr_t)edx);
  /* test (char)ecx, (char)ecx -> jne 0x24eaf */
  FUN_00024000((void *)(uintptr_t)edx, 0.0f, 23, (void *)0);
  /* test (char)eax, 0x41 -> jne 0x24fed */
  FUN_0010cd40((float *)(uintptr_t)esi, (float *)(uintptr_t)ebx, (float *)(uintptr_t)eax);
  /* test (char)eax, 0x41 -> jne 0x24fed */
  /* test (char)eax, 0x41 -> jne 0x24fed */
  vector_to_line_distance_squared3d((float *)(uintptr_t)esi, (float *)(uintptr_t)eax, (float *)(uintptr_t)ebx, (float *)(uintptr_t)edx);
  /* test (char)eax, 0x41 -> jne 0x24fed */
  /* test (char)eax, (char)eax -> jne 0x24fed */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
