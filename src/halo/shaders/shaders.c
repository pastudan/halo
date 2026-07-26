void numeric_countdown_timer_update(void)
{
  int current_time;

  current_time = *(int *)0x4d8a80;
  if (*(char *)0x4d8a7c) {
    current_time = (game_time_get() * 1000) / 30;
    if (*(int *)0x4d8a80 <= current_time) {
      *(int *)0x4d8a78 += *(int *)0x4d8a80 - current_time;
      if (*(int *)0x4d8a78 < 0)
        *(int *)0x4d8a78 = 0;
    }
  }
  *(int *)0x4d8a80 = current_time;
}
/* --- shaders.obj batch drafts (2026-07-26) --- */

/* 0x190240 */
void FUN_00190240(void)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;

  /* relift: cmp (int16_t)eax, word ptr [0x5060c4] -> jge 0x190358 */
  /* relift: cmp byte ptr [esi], 0 -> je 0x19033a */
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_get('dniw', 0);
  FUN_0018ff00((float *)(uintptr_t)edx, (float *)0, 0.0f, 0.0f);

  (void)eax;
  (void)edx;
  (void)esi;
}

/* 0x190380 */
void FUN_00190380(void)
{
  int eax = 0;

  get_global_random_seed_address();
  random_seed_get_direction3d((void *)(uintptr_t)eax, (float *)0);
  FUN_00089a20();

  (void)eax;
}

/* 0x190500 */
void wind_initialize_for_new_map(void)
{
  int eax = 0;

  scenario_get();
  /* test (char)eax, (char)eax -> je 0x19052b */
  display_assert((char *)0x002b22e0, (char *)0x002b22c0, 65, 0);
  system_exit(0);
  csmemset((void *)0x005057c0, 0, 3340);

  (void)eax;
}

/* 0x190550 */
void FUN_00190550(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  scenario_get();
  FUN_0018f2d0((void *)(uintptr_t)edi, (void *)(uintptr_t)eax);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 104);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 40);
  /* cmp (int16_t)eax, 0xffff -> je 0x19063f */
  /* relift: cmp word ptr [edi + 0x26], -1 -> je 0x19063f */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 0);
  /* cmp eax, -1 -> je 0x19063f */
  tag_get(' gof', 0);
  /* test (char)ecx, 1 -> je 0x190630 */
  /* relift: test byte ptr [ebp + 0x14], 8 -> jne 0x19063f */
  /* test eax, eax -> jne 0x19063f */
  FUN_00190240();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x190670 */
void FUN_00190670(void)
{
  FUN_00190550();
}

/* 0x190690 */
void FUN_00190690(void)
{
  FUN_00190550();
}

/* 0x1906b0 */
void *FUN_001906b0(void *shader, int shader_type)
{
  int esi = 0;
  int ebp = 0;

  /* test esi, esi -> jne 0x1906db */
  display_assert((char *)0x002a18b8, (char *)0x002b231c, 2140, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [ebp + 0xc] -> je 0x190705 */
  display_assert((char *)0x002b22fc, (char *)0x002b231c, 2141, 0);
  system_exit(0);
  return NULL;

  (void)esi;
  (void)ebp;
}

/* 0x190710 */
int shader_get_vertex_shader_permutation(void *shader)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x19073b */
  display_assert((char *)0x002a18b8, (char *)0x002b2348, 20, 0);
  system_exit(0);
  /* cmp edi, -1 -> je 0x190807 */
  /* cmp eax, 5 -> ja 0x190807 */
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  /* test (char)eax, 0x41 -> jne 0x190807 */
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  /* cmp ecx, -1 -> je 0x190807 */
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  /* cmp (int16_t)esi, 1 -> jne 0x1907f6 */
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  /* cmp (int16_t)esi, 1 -> jne 0x1907f6 */
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  /* test (char)ecx, 8 -> jne 0x1907f6 */
  /* relift: test byte ptr [edi], 4 -> je 0x190809 */
  return 0;

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x190830 */
void shader_is_mirror(void)
{
  int ecx = 0;
  int edx = 0;

  /* test ecx, ecx -> je 0x190874 */
  /* cmp edx, 3 -> je 0x190861 */
  /* cmp edx, 8 -> jne 0x190874 */
  FUN_001906b0((void *)(uintptr_t)ecx, 0);
  FUN_001906b0((void *)(uintptr_t)ecx, 0);

  (void)ecx;
  (void)edx;
}

/* 0x1908a0 */
char shader_is_decal(void *shader)
{
  int ecx = 0;
  int edx = 0;

  /* test ecx, ecx -> je 0x19090b */
  /* cmp edx, 4 -> ja 0x19090b */
  FUN_001906b0((void *)(uintptr_t)ecx, 0);
  FUN_001906b0((void *)(uintptr_t)ecx, 0);
  FUN_001906b0((void *)(uintptr_t)ecx, 0);
  FUN_001906b0((void *)(uintptr_t)ecx, 0);
  return 0;

  (void)ecx;
  (void)edx;
}

/* 0x190930 */
char shader_is_water_decal(void *shader)
{
  int ecx = 0;

  /* test ecx, ecx -> je 0x190970 */
  FUN_001906b0((void *)(uintptr_t)ecx, 0);
  FUN_001906b0((void *)(uintptr_t)ecx, 0);
  return 0;

  (void)ecx;
}

/* 0x190980 */
char shader_ignores_effect(void *shader)
{
  int ecx = 0;

  /* test ecx, ecx -> je 0x1909c0 */
  FUN_001906b0((void *)(uintptr_t)ecx, 0);
  FUN_001906b0((void *)(uintptr_t)ecx, 0);
  return 0;

  (void)ecx;
}

/* 0x1909d0 */
char shader_type_is_transparent(int16_t shader_type)
{
  /* relift: no calls detected — manual review */
  return 0;
}

/* 0x1909f0 */
void shader_type_is_lightmapped(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x190a10 */
void shader_type_is_vertex_lit(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x190a30 */
void shader_type_is_valid_for_environment(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x190a50 */
void shader_type_is_valid_for_model(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x190a70 */
char shader_type_is_valid_for_modifier(int16_t shader_type)
{
  /* relift: no calls detected — manual review */
  return 0;
}

/* 0x190a90 */
void shader_environment_texture_animation_evaluate(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x002a18b8, (char *)0x002b2348, 345, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x190ae4 */
  display_assert((char *)0x002b23c0, (char *)0x002b2348, 346, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x190b0b */
  display_assert((char *)0x002b23b4, (char *)0x002b2348, 347, 0);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)esi, 0);
  display_assert((char *)0x002b2390, (char *)0x002b2348, 352, 0);
  system_exit(0);
  display_assert((char *)0x002b236c, (char *)0x002b2348, 353, 0);
  system_exit(0);
  FUN_0010a5e0(eax, 0.0f);
  FUN_0010a5e0(ecx, 0.0f);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x190be0 */
void numeric_countdown_timer_set(int a0, int a1)
{
  /* relift: no calls detected — manual review */
}

/* 0x190c00 */
int numeric_countdown_timer_get(int a0)
{
  /* relift: no calls detected — manual review */
  return 0;
}

/* 0x190d90 */
void numeric_countdown_timer_stop(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x190da0 */
void numeric_countdown_timer_restart(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x190e10 */
void FUN_00190e10(void *map_animation, void *external_animation, float u_scale, float v_scale, float u_offset, float v_offset, float rotation, float time, float *out_u, float *out_v)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  display_assert((char *)0x002b2534, (char *)0x002b2348, 275, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x190e4e */
  /* cmp (int16_t)eax, 5 -> jl 0x190e6e */
  display_assert((char *)0x002b24d0, (char *)0x002b2348, 276, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x190e7d */
  /* cmp (int16_t)eax, 5 -> jl 0x190e9d */
  display_assert((char *)0x002b2468, (char *)0x002b2348, 277, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x190eac */
  /* cmp (int16_t)eax, 5 -> jl 0x190ecc */
  display_assert((char *)0x002b2400, (char *)0x002b2348, 278, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x190ef3 */
  display_assert((char *)0x002b23e4, (char *)0x002b2348, 279, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x190f1a */
  display_assert((char *)0x002b23cc, (char *)0x002b2348, 280, 0);
  system_exit(0);
  /* test eax, eax -> je 0x190fc9 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x190f8e */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x190faa */
  /* test (int16_t)eax, (int16_t)eax -> je 0x190fd7 */
  FUN_0010a5e0(0, 0.0f);
  FUN_0010a5e0(ecx, 0.0f);
  FUN_0010a5e0(edx, 0.0f);
  cseries_initialize();
  FUN_001911b0();
  /* test (char)eax, (char)eax -> je 0x19112f */
  errors_initialize();
  tag_files_close();
  real_math_initialize();
  game_state_lruv_cache_new();
  rasterizer_window_set_fog();
  /* test (char)eax, (char)eax -> je 0x19112a */
  input_initialize();
  sound_initialize((void *)0);
  FUN_00191210();
  FUN_001cb820();
  FUN_000cf490();
  rasterizer_dynamic_screen_geometry_draw();
  real_math_dispose();
  tag_groups_checksum();
  errors_dispose();
  FUN_00191220();
  /* relift: cmp byte ptr [0x4d8a84], (char)eax -> je 0x19119c */
  FUN_00191230(0);
  XGetLaunchInfo();
  /* test eax, eax -> jne 0x191207 */
  /* test eax, eax -> jne 0x191207 */
  csstrcmp((char *)(uintptr_t)edx, (char *)0x002b2550);
  /* test eax, eax -> jne 0x191207 */
  csstrcat((char *)0x004d8a88, (char *)0x002b2548, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}
