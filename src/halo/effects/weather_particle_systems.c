void weather_particle_systems_initialize(void)
{
  weather_particle_system_data = data_new("weather particles", 0x200, 0x54);
  if (weather_particle_system_data == 0)
    error(0, "couldn't allocate weather particle system globals.");
}

void weather_particle_systems_initialize_for_new_map(void)
{
  int16_t i;
  int *entry;

  i = 0;
  entry = (int *)0x4557f4;
  do {
    assert_halt(i >= 0 && i < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
    *entry = NONE;
    i++;
    entry = (int *)((char *)entry + 0x9c);
  } while (i < 4);
  *(int16_t *)0x4557f0 = 0;
  data_delete_all(weather_particle_system_data);
}

void weather_particle_systems_dispose_from_old_map(void)
{
  if (weather_particle_system_data && weather_particle_system_data->valid)
    data_make_invalid(weather_particle_system_data);
}

void weather_particle_systems_dispose(void)
{
  if (weather_particle_system_data) {
    data_dispose(weather_particle_system_data);
    weather_particle_system_data = 0;
  }
}
/* --- weather_particle_systems.obj batch drafts (2026-07-26) --- */

/* 0xa3e60 */
void FUN_000a3e60(void)
{
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0xa3e6b */
  /* cmp (int16_t)esi, 4 -> jl 0xa3e88 */
  display_assert((char *)0x00266fc0, (char *)0x0026af50, 91, 0);
  system_exit(0);

  (void)esi;
}

/* 0xa3ea0 */
void FUN_000a3ea0(void)
{
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  tag_get('niar', 0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0xa3ebf */
  /* cmp ecx, edx -> jl 0xa3edc */
  display_assert((char *)0x0026af84, (char *)0x0026af50, 102, 0);
  system_exit(0);

  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0xa4000 */
void FUN_000a4000(void)
{
  FUN_001daf7e();
  FUN_001daf7e();
  FUN_001daf7e();
}

/* 0xa40a0 */
void weather_particle_system_new(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int ebp = 0;

  /* cmp (int16_t)esi, 4 -> jl 0xa40d3 */
  display_assert((char *)0x00266fc0, (char *)0x0026af50, 91, 0);
  system_exit(0);
  tag_get(0, 0);
  /* cmp eax, -1 -> je 0xa411c */
  display_assert((char *)0x0026b00c, (char *)0x0026af50, 177, 0);
  system_exit(0);
  tag_get('niar', 0);
  /* relift: cmp word ptr [ebp + 8], 0 -> jl 0xa416c */
  /* relift: cmp ebx, dword ptr [eax + 0x24] -> jl 0xa4189 */
  display_assert((char *)0x0026af84, (char *)0x0026af50, 102, 0);
  system_exit(0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  /* relift: cmp ebx, dword ptr [eax] -> jl 0xa4150 */

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)ebp;
}

/* 0xa4200 */
void weather_particle_system_delete(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;

  /* cmp (int16_t)esi, 4 -> jl 0xa4233 */
  display_assert((char *)0x00266fc0, (char *)0x0026af50, 91, 0);
  system_exit(0);
  tag_get('niar', 0);
  tag_get('niar', 0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0xa4281 */
  /* relift: cmp esi, dword ptr [eax + 0x24] -> jl 0xa429e */
  display_assert((char *)0x0026af84, (char *)0x0026af50, 102, 0);
  system_exit(0);
  datum_get((void *)(uintptr_t)eax, 0);
  datum_delete((void *)(uintptr_t)edx, 0);

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
}

/* 0xa4310 */
void FUN_000a4310(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  data_new_at_index((void *)(uintptr_t)eax);
  /* test (int16_t)edi, (int16_t)edi -> jl 0xa4342 */
  /* cmp (int16_t)edi, 4 -> jl 0xa435f */
  display_assert((char *)0x00266fc0, (char *)0x0026af50, 91, 0);
  system_exit(0);
  tag_get(0x7261696e, 0);
  FUN_000a3ea0();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  datum_get((void *)(uintptr_t)edx, 0);
  tag_get('mtib', 0);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_seed_get_direction3d((void *)(uintptr_t)eax, (float *)0);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  /* test (char)eax, 4 -> je 0xa450f */
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_range((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 64);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  FUN_0007c270((float *)(uintptr_t)edx, ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, 0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0xa45d0 */
void FUN_000a45d0(void)
{
  FUN_000a4000();
}

/* 0xa4610 */
void FUN_000a4610(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp (int16_t)edi, 4 -> jl 0xa4647 */
  display_assert((char *)0x00266fc0, (char *)0x0026af50, 91, 0);
  system_exit(0);
  tag_get('niar', 0);
  tag_get('niar', 0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0xa4684 */
  /* cmp edx, ecx -> jl 0xa46a1 */
  display_assert((char *)0x0026af84, (char *)0x0026af50, 102, 0);
  system_exit(0);
  tag_block_get_element((void *)(uintptr_t)edi, 0, 0);
  datum_get((void *)(uintptr_t)eax, 0);
  normalize3d((float *)(uintptr_t)esi);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  /* test (char)eax, 0x41 -> jne 0xa4787 */
  random_math_get_local_seed_address();
  random_seed_get_direction3d((void *)(uintptr_t)eax, (float *)0);
  tag_get(0x70706879, 0);
  FUN_00154a50(0, 0, (void *)0, 0, (float *)0, (float *)0, (float *)0, (float *)0, (void *)0, 0.0f, 0.0f);
  random_seed_get_direction3d((void *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  FUN_000a4000();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0xa48c0 */
void FUN_000a48c0(void)
{
  /* relift: no calls detected — manual review */
}

/* 0xa4a00 */
void FUN_000a4a00(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  scenario_get();
  /* test eax, eax -> jle 0xa4a9e */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 32);
  /* cmp (int16_t)ebx, 8 -> jge 0xa4a85 */
  error(0, (char *)0x0026b02c);
  /* cmp eax, ecx -> jl 0xa4a21 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}

/* 0xa4ab0 */
void FUN_000a4ab0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp (int16_t)esi, 4 -> jl 0xa4ae3 */
  display_assert((char *)0x00266fc0, (char *)0x0026af50, 91, 0);
  system_exit(0);
  tag_get('niar', 0);
  tag_get('niar', 0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0xa4b1e */
  /* cmp edx, ecx -> jl 0xa4b3b */
  display_assert((char *)0x0026af84, (char *)0x0026af50, 102, 0);
  system_exit(0);
  FUN_001d9068();
  /* cmp eax, edi -> jge 0xa4b97 */
  FUN_000a4310();
  /* cmp eax, -1 -> je 0xa4b97 */
  /* cmp ecx, edi -> jl 0xa4b80 */
  /* cmp edx, edi -> jle 0xa4bd4 */
  datum_get((void *)(uintptr_t)ecx, 0);
  datum_delete((void *)(uintptr_t)eax, 0);
  /* cmp ecx, edi -> jg 0xa4ba0 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0xa4be0 */
void FUN_000a4be0(void)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0xa4bf6 */
  /* cmp (int16_t)esi, 4 -> jl 0xa4c13 */
  display_assert((char *)0x00266fc0, (char *)0x0026af50, 91, 0);
  system_exit(0);
  tag_get('niar', 0);
  tag_get(0x7261696e, 0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0xa4c7a */
  /* relift: cmp edi, dword ptr [eax + 0x24] -> jl 0xa4c97 */
  display_assert((char *)0x0026af84, (char *)0x0026af50, 102, 0);
  system_exit(0);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  tag_get('mtib', 0);
  /* test (char)eax, 0x41 -> jne 0xa4d11 */
  /* test (char)eax, 0x41 -> jne 0xa4d4d */
  FUN_000a4ab0();
  /* cmp edi, -1 -> je 0xa4dfa */
  datum_get((void *)(uintptr_t)edx, 0);
  tag_block_get_element((void *)0, 0, 0);
  FUN_001daf7e();
  FUN_000a4610();
  /* cmp edi, -1 -> jne 0xa4d85 */

  (void)eax;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0xa4e20 */
void weather_particle_system_render(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp (int16_t)esi, 4 -> jl 0xa4e56 */
  display_assert((char *)0x00266fc0, (char *)0x0026af50, 91, 0);
  system_exit(0);
  tag_get('niar', 0);
  scenario_get();
  FUN_000a4be0();
  tag_block_get_element((void *)(uintptr_t)edi, 0, 0);
  FUN_000a4a00();
  FUN_000a48c0();
  FUN_000a4000();
  /* cmp (int16_t)eax, 1 -> jne 0xa5004 */
  /* cmp (int16_t)esi, (int16_t)eax -> jne 0xa5004 */
  /* cmp (int16_t)ecx, (int16_t)eax -> je 0xa50ef */
  render_frustum_cube_visible((void *)0, 0, 0);
  /* test (int16_t)eax, (int16_t)eax -> je 0xa50ec */
  /* cmp (int16_t)ebx, 0x1a -> jl 0xa5089 */
  display_assert((char *)0x0026b050, (char *)0x0026af50, 673, 0);
  system_exit(0);
  FUN_0018d2c0((void *)(uintptr_t)edx, ecx, edx, 0, 0);
  /* cmp eax, -1 -> je 0xa5471 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* relift: cmp word ptr [ebp - 0xc], (int16_t)esi -> jle 0xa5465 */
  /* test (char)eax, (char)eax -> je 0xa51f3 */
  /* cmp (int16_t)edx, 5 -> jl 0xa51b8 */
  /* test (char)eax, (char)eax -> jne 0xa51ff */
  /* relift: cmp (int16_t)esi, word ptr [ebp - 0xc] -> jl 0xa51b4 */
  /* test ecx, ecx -> je 0xa5465 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
