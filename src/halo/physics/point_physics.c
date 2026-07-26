/* 0x1544d0 - accumulate float by delta and clamp/wrap within bounds. */
void FUN_001544d0(float *param_1, float *param_2, char param_3, float param_4)
{
  param_4 = param_4 + *param_1;
  *param_1 = param_4;
  if (param_4 < param_2[1]) {
    if (param_3 != '\0') {
      *param_1 = (param_2[0] - param_2[1]) + param_4;
      return;
    }
    *param_1 = param_2[1];
    return;
  }
  if (param_4 > *param_2) {
    if (param_3 != '\0') {
      *param_1 = param_4 - (*param_2 - param_2[1]);
      return;
    }
    *param_1 = *param_2;
  }
}

void point_physics_initialize_for_new_map(void)
{
  *(float *)0x476200 = *(float *)0x325134 * *(float *)0x29d954;
  *(float *)0x4761fc = *(float *)0x325130 * *(float *)0x29d954;
}

void point_physics_dispose_from_old_map(void)
{
}

/* Scale a point-physics density value by volume (scale^3). */
float point_physics_definition_get_mass(int tag_data, float scale)
{
  return scale * *(float *)(tag_data + 4) * scale * scale;
}
/* --- point_physics.obj batch drafts (2026-07-26) --- */

/* 0x154270 */
void FUN_00154270(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  object_get_and_verify_type(0, 0);
  tag_get('ejbo', 0);
  tag_get('syhp', 0);
  /* test (char)eax, 0x41 -> jne 0x1542d4 */
  FUN_00152e40();
  FUN_001509c0((void *)(uintptr_t)eax, 0);
  /* cmp eax, edi -> je 0x154323 */
  /* relift: cmp dword ptr [ebx + 0x68], edi -> jle 0x154323 */
  FUN_001093b0((float *)(uintptr_t)esi, (float *)(uintptr_t)eax);
  FUN_00109120((float *)(uintptr_t)esi);
  /* cmp eax, ecx -> jl 0x1542f2 */
  FUN_00150ed0();
  object_get_and_verify_type(0, 0);
  real_vector3d_valid((float *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> jne 0x154411 */
  csprintf((char *)0x005ab100, (char *)0x0026ae40);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* test esi, esi -> je 0x1544a2 */
  real_vector3d_valid((float *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> jne 0x154488 */
  csprintf((char *)0x005ab100, (char *)0x0026ae40);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  FUN_00152680();
  physics_compute_unit_collisions();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x154540 */
void FUN_00154540(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x154630 */
void FUN_00154630(void)
{
  int eax = 0;

  /* test (char)eax, 0x41 -> jne 0x154673 */
  FUN_00154540();
  FUN_00154540();
  /* test (char)eax, 1 -> je 0x154668 */

  (void)eax;
}

/* 0x1546b0 */
void FUN_001546b0(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  FUN_00154540();
  FUN_001544d0((float *)(uintptr_t)ecx, (float *)(uintptr_t)esi, eax, 0.0f);

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x1546f0 */
void FUN_001546f0(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x154750 */
void FUN_00154750(void)
{
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  FUN_001546f0();
  FUN_001544d0((float *)(uintptr_t)esi, (float *)(uintptr_t)ebx, edi, 0.0f);
  FUN_001546f0();

  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x1547d0 */
void FUN_001547d0(void)
{
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  FUN_001546f0();
  FUN_00154540();
  FUN_001544d0((float *)(uintptr_t)edi, (float *)(uintptr_t)esi, ebx, 0.0f);
  FUN_001546f0();

  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x1548c0 */
void point_physics_definition_interpolate(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  display_assert((char *)0x0029d978, (char *)0x0029d984, 332, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x154921 */
  display_assert((char *)0x0029d96c, (char *)0x0029d984, 333, 0);
  system_exit(0);
  /* test (char)eax, 1 -> jne 0x154941 */
  display_assert((char *)0x0029d958, (char *)0x0029d984, 334, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x154988 */
  display_assert((char *)0x0025f120, (char *)0x0029d984, 335, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)esi;
}

/* 0x154a20 */
void FUN_00154a20(void)
{
  int eax = 0;
  int edx = 0;

  FUN_00189150(0, (float *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)eax);

  (void)eax;
  (void)edx;
}

/* 0x154a50 */
int FUN_00154a50(int flags, int physics_tag_data, int *collision_location, int object_handle, float *position, float *velocity, float *force, float *collision_normal_out, int16_t *surface_index_out, float radius, float delta_time)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int ebp = 0;

  valid_real_point3d((float *)(uintptr_t)ebx);
  /* test (char)eax, (char)eax -> jne 0x154abb */
  csprintf((char *)0x005ab100, (char *)0x0026ae04);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  real_vector3d_valid((float *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> jne 0x154b15 */
  csprintf((char *)0x005ab100, (char *)0x0026ae40);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* test eax, eax -> je 0x154b49 */
  real_vector3d_valid((float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0x154b49 */
  display_assert((char *)0x0029d9c0, (char *)0x0029d984, 187, 0);
  system_exit(0);
  /* test (char)eax, 1 -> je 0x154b79 */
  display_assert((char *)0x0029d9b0, (char *)0x0029d984, 188, 0);
  system_exit(0);
  /* test (char)ecx, 1 -> je 0x154be0 */
  FUN_00190240();
  FUN_00190550();
  /* test (char)ebx, (char)ebx -> je 0x154c16 */
  /* test ecx, ecx -> je 0x154c92 */
  /* test (char)eax, 0x41 -> jne 0x154d0b */
  /* test (char)eax, 2 -> je 0x154d5f */
  /* relift: test byte ptr [ebp + 8], 4 -> jne 0x154d5f */
  display_assert((char *)0x00253440, (char *)0x0029d984, 269, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp - 0x10], 3 -> jge 0x154f4d */
  FUN_0014df70(0, (float *)0, (float *)0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x154f23 */
  /* test (char)eax, 0x41 -> jne 0x154e16 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x154e30 */
  /* cmp (int16_t)eax, 2 -> jne 0x154e3f */
  /* test eax, eax -> je 0x154e57 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)ebp;
}
