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
void FUN_00154270(int object_handle, void *buffer_a, void *buffer_b,
                  float *force_vec, float *aux_vec)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  object_get_and_verify_type(object_handle, -1);
  tag_get('ejbo', *(int *)(eax));
  tag_get('syhp', 0);
  /* test (char)eax, 0x41 -> jne 0x1542d4 */
  FUN_00152e40();
  FUN_001509c0((void *)(uintptr_t)eax, object_handle);
  /* cmp eax, edi -> je 0x154323 */
  /* relift: cmp dword ptr [ebx + 0x68], edi -> jle 0x154323 */
  FUN_001093b0((float *)(uintptr_t)esi, (float *)(uintptr_t)eax);
  FUN_00109120((float *)(uintptr_t)esi);
  /* cmp eax, ecx -> jl 0x1542f2 */
  FUN_00150ed0();
  object_get_and_verify_type(object_handle, 2);
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

  (void)buffer_a;
  (void)buffer_b;
  (void)force_vec;
  (void)aux_vec;
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

/* 0x1548c0 — lerp point_physics_definition fields by t in [0,1]. */
void point_physics_definition_interpolate(float *definition_a, float *definition_b, float t,
                                          float *definition_out)
{
  float one_minus_t;

  one_minus_t = *(float *)0x2533c8 - t;
  if (!definition_a) {
    display_assert((char *)0x0029d978, (char *)0x0029d984, 0x14c, 1);
    system_exit(-1);
  }
  if (!definition_b) {
    display_assert((char *)0x0029d96c, (char *)0x0029d984, 0x14d, 1);
    system_exit(-1);
  }
  if (t < *(float *)0x2533c0 || t > *(float *)0x2533c8) {
    display_assert((char *)0x0029d958, (char *)0x0029d984, 0x14e, 1);
    system_exit(-1);
  }
  if (!definition_out) {
    display_assert((char *)0x0025f120, (char *)0x0029d984, 0x14f, 1);
    system_exit(-1);
  }

  *(int *)definition_out = *(int *)definition_a;
  definition_out[0x20 / 4] = one_minus_t * definition_a[0x20 / 4] + t * definition_b[0x20 / 4];
  definition_out[0x8 / 4] = one_minus_t * definition_a[0x8 / 4] + t * definition_b[0x8 / 4];
  definition_out[0xc / 4] = one_minus_t * definition_a[0xc / 4] + t * definition_b[0xc / 4];
  definition_out[0x4 / 4] = one_minus_t * definition_a[0x4 / 4] + t * definition_b[0x4 / 4];
  definition_out[0x24 / 4] = one_minus_t * definition_a[0x24 / 4] + t * definition_b[0x24 / 4];
  definition_out[0x28 / 4] = one_minus_t * definition_a[0x28 / 4] + t * definition_b[0x28 / 4];
  definition_out[0x2c / 4] = one_minus_t * definition_a[0x2c / 4] + t * definition_b[0x2c / 4];
  definition_out[0x30 / 4] = one_minus_t * definition_a[0x30 / 4] + t * definition_b[0x30 / 4];
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
  char *pphys = (char *)physics_tag_data;
  float wind[3];
  float air;
  float media_density;
  float mass;
  float radius_sq;
  float radius_cu;
  float dt_over_mass;
  float drag;
  float blend;
  int coll_flags;
  int result_flags = 0;
  char in_media;
  char hit[0x80];
  float parallel[3];
  float perpendicular[3];
  int iter;
  float step_dt;
  unsigned int tiny = 0x3ba3d70au; /* 0.005f */

  if (!valid_real_point3d(position)) {
    csprintf((char *)0x5ab100, (char *)0x267114, (char *)0x26ae04,
             (double)position[0], (double)position[1], (double)position[2]);
    display_assert((char *)0x5ab100, (char *)0x29d984, 0xb9, 1);
    system_exit(-1);
  }
  if (!real_vector3d_valid(velocity)) {
    csprintf((char *)0x5ab100, (char *)0x29da04, (char *)0x26ae40,
             (double)velocity[0], (double)velocity[1], (double)velocity[2]);
    display_assert((char *)0x5ab100, (char *)0x29d984, 0xba, 1);
    system_exit(-1);
  }
  if (force && !real_vector3d_valid(force)) {
    display_assert((char *)0x29d9c0, (char *)0x29d984, 0xbb, 1);
    system_exit(-1);
  }
  if (radius < 0.0f) {
    display_assert((char *)0x29d9b0, (char *)0x29d984, 0xbc, 1);
    system_exit(-1);
  }
  if (delta_time == 0.0f)
    goto debug_draw;

  radius_sq = radius * radius;
  radius_cu = radius_sq * radius;
  {
    unsigned char media = (unsigned char)pphys[0];
    int wind_bits = (media >> 3) & 1;
    if (media & 0x10)
      wind_bits |= 2;
    else
      wind_bits &= ~2;
    if (flags & 1)
      in_media = FUN_00190240(position, wind, wind_bits, object_handle);
    else
      in_media = FUN_00190550(collision_location, position, wind, wind_bits);
  }

  if (in_media) {
    result_flags = 2;
    air = *(float *)0x4761fc + *(float *)(pphys + 4);
    media_density = *(float *)(pphys + 8);
    drag = radius_sq * *(float *)(pphys + 0x28);
  } else {
    result_flags = 1;
    air = *(float *)0x476200 + *(float *)(pphys + 4);
    media_density = *(float *)(pphys + 0xc);
    drag = radius_sq * *(float *)(pphys + 0x24);
  }
  mass = air * radius_cu;
  if ((pphys[0] & 0x20) != 0)
    media_density = 0.0f;
  dt_over_mass = (mass == 0.0f) ? 0.0f : (delta_time / mass);

  if (force && mass != 0.0f) {
    velocity[0] += dt_over_mass * force[0];
    velocity[1] += dt_over_mass * force[1];
    velocity[2] += dt_over_mass * force[2];
  }
  /* gravity scales with media density */
  velocity[2] += *(float *)0x32512c * *(float *)0x253394 * *(float *)0x253394 *
                 media_density * delta_time;

  if (mass == 0.0f && drag == 0.0f) {
    blend = 0.0f;
  } else {
    blend = dt_over_mass * drag;
    if (blend < 0.0f)
      blend = 0.0f;
    else if (blend > 1.0f)
      blend = 1.0f;
  }
  velocity[0] += (wind[0] - velocity[0]) * blend;
  velocity[1] += (wind[1] - velocity[1]) * blend;
  velocity[2] += (wind[2] - velocity[2]) * blend;

  coll_flags = (*(unsigned char *)pphys & 4) ? ((flags & 4) ? 0x41 : 1) : 1;
  if ((*(unsigned char *)pphys & 2) != 0 && (flags & 4) == 0)
    coll_flags |= 0x20;
  else
    coll_flags &= ~0x20;

  if (*(int16_t *)0x4761d8 >= 3) {
    display_assert((char *)0x253440, (char *)0x29d984, 0x10d, 1);
    system_exit(-1);
  }
  {
    int16_t depth = *(int16_t *)0x4761d8;
    *(int16_t *)(0x5a8c80 + (int)depth * 2) = 0xd;
    *(int16_t *)0x4761d8 = (int16_t)(depth + 1);
  }

  step_dt = delta_time;
  for (iter = 0; iter < 3; iter++) {
    float dir[3];
    dir[0] = step_dt * velocity[0];
    dir[1] = step_dt * velocity[1];
    dir[2] = step_dt * velocity[2];
    if (!FUN_0014df70((unsigned int)coll_flags, position, dir, -1,
                      (int16_t *)hit)) {
      if (*(int *)((char *)hit + 0xc) != -1 && collision_location) {
        collision_location[0] = *(int *)((char *)hit + 0xc);
        collision_location[1] = *(int *)((char *)hit + 0x10);
      }
      position[0] = *(float *)((char *)hit + 0x18);
      position[1] = *(float *)((char *)hit + 0x1c);
      position[2] = *(float *)((char *)hit + 0x20);
      break;
    }
    {
      float pad = radius;
      if (!(pad <= *(float *)0x29d9ac)) {
        unsigned int bits = tiny;
        pad = *(float *)&bits;
      }
      if (*(int16_t *)hit == 0)
        result_flags |= 8;
      else if (*(int16_t *)hit == 2)
        result_flags |= 4;
      if (collision_normal_out) {
        collision_normal_out[0] = *(float *)((char *)hit + 0x24);
        collision_normal_out[1] = *(float *)((char *)hit + 0x28);
        collision_normal_out[2] = *(float *)((char *)hit + 0x2c);
      }
      if (surface_index_out)
        *surface_index_out = *(int16_t *)((char *)hit + 0x34);
      FUN_0010b8a0(velocity, (float *)((char *)hit + 0x24), parallel,
                   perpendicular);
      {
        float rest = 1.0f - *(float *)(pphys + 0x2c);
        float fric = *(float *)(pphys + 0x30);
        velocity[0] = rest * perpendicular[0] - parallel[0] * fric;
        velocity[1] = rest * perpendicular[1] - parallel[1] * fric;
        velocity[2] = rest * perpendicular[2] - parallel[2] * fric;
      }
      if (*(int *)((char *)hit + 0xc) != -1 && collision_location) {
        collision_location[0] = *(int *)((char *)hit + 0xc);
        collision_location[1] = *(int *)((char *)hit + 0x10);
      }
      position[0] = *(float *)((char *)hit + 0x24) * pad +
                    *(float *)((char *)hit + 0x18);
      position[1] = *(float *)((char *)hit + 0x28) * pad +
                    *(float *)((char *)hit + 0x1c);
      position[2] = *(float *)((char *)hit + 0x2c) * pad +
                    *(float *)((char *)hit + 0x20);
      step_dt = step_dt - *(float *)((char *)hit + 0x14) * step_dt;
      if (step_dt == 0.0f)
        break;
    }
  }

  if (*(int16_t *)0x4761d8 <= 1) {
    display_assert((char *)0x253418, (char *)0x29d984, 0x138, 1);
    system_exit(-1);
  }
  (*(int16_t *)0x4761d8)--;

debug_draw:
  if (*(char *)0x5a5e20) {
    void *color = (void *)(((*(unsigned char *)pphys & 2) != 0)
                            ? *(unsigned int *)0x2ee6d0
                            : *(unsigned int *)0x2ee6d4);
    FUN_00189150(1, position, radius, color);
  }
  return result_flags;
}

