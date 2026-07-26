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
void FUN_000a4000(float *dst, float *src, float scale)
{
  int i;
  for (i = 0; i < 3; i++) {
    float base = (src[i] < 0.0f) ? scale : 0.0f;
    dst[i] = base + (src[i] < 0.0f ? 0.0f : src[i]);
  }
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
  FUN_000a4000((float *)0, (float *)0, 0.0f);
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
  FUN_000a4000((float *)0, (float *)0, 0.0f);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0xa48c0 */
void FUN_000a48c0(float *out, float scale)
{
  float *cam = (float *)0x50655c;
  float *eye = (float *)0x506550;
  *(unsigned int *)((char *)out + 0x40) = *(unsigned int *)0x50655c;
  out[0] = cam[0] * scale + eye[0];
  out[1] = cam[1] * scale + eye[1];
  out[2] = cam[2] * scale + eye[2];
}

/* 0xa4a00 */
int FUN_000a4a00(void *out_buf, int particle_handle)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  (void)out_buf;
  (void)particle_handle;
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
  return 0;
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

/* 0xa4be0 — validate weather particle particles for a weather slot. */
void FUN_000a4be0(int16_t weather_index)
{
  char *weather;
  char *rain;
  int type_i;
  int type_count;
  char *type_state;
  char *type_def;

  if (weather_index < 0 || weather_index >= 4) {
    display_assert((char *)0x266fc0, (char *)0x26af50, 91, 1);
    system_exit(-1);
  }
  weather = (char *)(0x4557f4 + (int)weather_index * 0x9c);
  rain = (char *)tag_get(0x7261696e, *(int *)weather);
  type_count = *(int *)(rain + 0x24);
  for (type_i = 0; type_i < type_count; type_i++) {
    type_state = weather + 0x1c + type_i * 0x10;
    type_def = (char *)tag_block_get_element(rain + 0x24, type_i, 0x25c);
    if (*(int *)(type_def + 0x54) != -1)
      (void)tag_get(0x6269746d, *(int *)(type_def + 0x54));
    if (*(int16_t *)(type_state + 8) != 0)
      FUN_000a4ab0();
  }
}

/* 0xa4e20 */
void weather_particle_system_render(int16_t weather_index)
{
  char *weather;
  char *rain;
  int type_i;
  int type_count;
  char *type_state;
  char *type_def;
  int particle_handle;
  int nearest;
  float local_offset[3];
  float extents[16];
  float cube[6];
  char build[0x100];
  int i;

  if (weather_index < 0 || weather_index >= 4) {
    display_assert((char *)0x266fc0, (char *)0x26af50, 0x5b, 1);
    system_exit(-1);
  }
  weather = (char *)(0x4557f4 + (int)weather_index * 0x9c);
  rain = (char *)tag_get(0x7261696e, *(int *)weather); /* 'rain' */
  (void)scenario_get();
  FUN_000a4be0(weather_index);
  type_count = *(int *)(rain + 0x24);

  for (type_i = 0; type_i < type_count; type_i++) {
    type_def = (char *)tag_block_get_element(rain + 0x24, type_i, 0x25c);
    type_state = weather + 0x1c + type_i * 0x10;
    if (*(int16_t *)(type_state + 8) == 0)
      continue;

    particle_handle = *(int *)(type_state + 4);
    nearest = FUN_000a4a00(extents, particle_handle);
    FUN_000a48c0(extents, *(float *)(type_state + 4));
    FUN_000a4000(local_offset, (float *)0x506550, *(float *)(type_state + 4));
    local_offset[0] = *(float *)0x506550 - local_offset[0];
    local_offset[1] = *(float *)0x506554 - local_offset[1];
    local_offset[2] = *(float *)0x506558 - local_offset[2];

    for (i = 0; i < 5; i++) {
      float *row = (float *)(extents + 0x10 + i * 0x10);
      cube[i] = local_offset[2] * row[2] + local_offset[0] * row[0] +
                local_offset[1] * row[1];
    }
    cube[0] = local_offset[0];
    cube[1] = local_offset[1] + *(float *)(type_state + 4);
    cube[2] = local_offset[2];
    cube[3] = local_offset[0] + *(float *)(type_state + 4);
    cube[4] = local_offset[1];
    cube[5] = local_offset[2] + *(float *)(type_state + 4);

    if (render_frustum_cube_visible((void *)0x5065a4, (int)(uintptr_t)cube, 1) ==
        0)
      continue;
    if (nearest >= 0x1a) {
      display_assert((char *)0x26b050, (char *)0x26af50, 0x2a1, 1);
      system_exit(-1);
    }

    FUN_0018d2c0((uint32_t *)build, 2, *(unsigned int *)(type_def + 0x54),
                 (int)(uintptr_t)type_def, 0);
    if (*(int *)type_def != -1) {
      datum_get(*(data_t **)0x5aa8a4, particle_handle);
      (void)tag_block_get_element(type_def + 0x68, 0, 0x40);
      (void)tag_block_get_element(type_def + 0x68, 0, 0x40);
      FUN_001d9068();
      FUN_0018d6e0(build, 1, 0, 0, local_offset, cube, 0.0f, 1.0f, local_offset,
                   1.0f, 0);
      FUN_0018d360(build);
    }
  }
}


