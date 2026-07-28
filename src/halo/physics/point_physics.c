/* 0x1544d0 - accumulate float by delta and clamp/wrap within bounds. */
__declspec(noinline) void FUN_001544d0(float *param_1, float *param_2, char param_3,
                                       float param_4)
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

/* FUN_00154270 (0x154270) — readable C lift (restored pre-naked). */
void FUN_00154270(int object_handle, void *buffer_a, void *buffer_b,
                  float *force_vec, float *aux_vec)
{
  char *obj;
  char *obj_tag;
  char *phys_tag;
  char phys_state[0x54];
  float force_acc[3] = {0.0f, 0.0f, 0.0f};
  float aux_acc[3] = {0.0f, 0.0f, 0.0f};
  int16_t i;
  int mass_point_count;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  obj_tag = (char *)tag_get(0x6f626a65, *(int *)obj); /* 'obje' */
  phys_tag = (char *)tag_get(0x70687973, *(int *)(obj_tag + 0x8c)); /* 'phys' */

  if (*(float *)phys_tag > *(float *)0x2533c0) {
    FUN_00152e40(object_handle, buffer_a, buffer_b, force_vec, aux_vec);
    return;
  }

  FUN_001509c0((int *)phys_state, object_handle);
  if (buffer_a != 0 && *(int *)(phys_tag + 0x68) > 0) {
    mass_point_count = *(int *)(phys_tag + 0x68);
    for (i = 0; i < mass_point_count; i++) {
      char *entry = (char *)buffer_a + (int)i * 0x60;
      FUN_001093b0((float *)(entry + 0x2c), (float *)(entry + 0x1c));
      FUN_00109120((float *)(entry + 0x2c));
    }
  }

  FUN_00150ed0(phys_state, buffer_a, buffer_b, force_acc, aux_acc);
  obj = (char *)object_get_and_verify_type(object_handle, 2);
  force_acc[0] += *(float *)(obj + 0x460);
  force_acc[1] += *(float *)(obj + 0x464);
  force_acc[2] += *(float *)(obj + 0x468);
  aux_acc[0] += *(float *)(obj + 0x46c);
  aux_acc[1] += *(float *)(obj + 0x470);
  aux_acc[2] += *(float *)(obj + 0x474);
  *(float *)(obj + 0x460) = 0.0f;
  *(float *)(obj + 0x464) = 0.0f;
  *(float *)(obj + 0x468) = 0.0f;
  *(float *)(obj + 0x46c) = 0.0f;
  *(float *)(obj + 0x470) = 0.0f;
  *(float *)(obj + 0x474) = 0.0f;

  if (force_vec != 0) {
    if (!real_vector3d_valid(force_vec)) {
      csprintf((char *)0x5ab100, (char *)0x26ae40, (char *)0x29d948,
               (double)force_vec[0], (double)force_vec[1],
               (double)force_vec[2]);
      display_assert((char *)0x5ab100, (char *)0x29d780, 0x10e, 1);
      system_exit(-1);
    }
    force_acc[0] += force_vec[0];
    force_acc[1] += force_vec[1];
    force_acc[2] += force_vec[2];
  }
  if (aux_vec != 0) {
    if (!real_vector3d_valid(aux_vec)) {
      csprintf((char *)0x5ab100, (char *)0x26ae40, (char *)0x29d938,
               (double)aux_vec[0], (double)aux_vec[1], (double)aux_vec[2]);
      display_assert((char *)0x5ab100, (char *)0x29d780, 0x114, 1);
      system_exit(-1);
    }
    aux_acc[0] += aux_vec[0];
    aux_acc[1] += aux_vec[1];
    aux_acc[2] += aux_vec[2];
  }

  FUN_00152680(phys_state, buffer_a, buffer_b, force_acc, aux_acc);
  physics_compute_unit_collisions();
}


/* FUN_00154540 (0x154540) — readable C lift from XBE leaf.
 * Asymmetric 1D rate integrate/dampen using coeffs[0..3] and signed scale. */
void FUN_00154540(float *accum, float *coeffs, float scale)
{
  float abs_scale;
  float a;
  float b;
  float lim;

  abs_scale = scale < 0.0f ? -scale : scale;
  a = abs_scale * coeffs[2];
  b = abs_scale * coeffs[3];

  if (scale > 0.0f) {
    if (*accum <= -b) {
      *accum = *accum + b;
    } else if (*accum >= 0.0f) {
      *accum = *accum + a;
    } else {
      *accum = (*accum / b + 1.0f) * a;
    }
    lim = abs_scale * coeffs[0];
    if (lim < *accum) {
      *accum = lim;
    }
  } else if (scale < 0.0f) {
    if (*accum >= b) {
      *accum = *accum - b;
    } else if (*accum <= 0.0f) {
      *accum = *accum - a;
    } else {
      *accum = (*accum / b - 1.0f) * a;
    }
    lim = -(abs_scale * coeffs[1]);
    if (lim > *accum) {
      *accum = lim;
    }
  }
}


/* FUN_00154630 (0x154630) — readable C lift from XBE leaf.
 * Integrate accum toward target by +/- scale; clamp and report hit. */
char FUN_00154630(float *accum, float *coeffs, float target, float scale)
{
  if (*accum > target) {
    FUN_00154540(accum, coeffs, -scale);
    if (*accum > target)
      return 0;
    *accum = target;
    return 1;
  }
  if (*accum < target) {
    FUN_00154540(accum, coeffs, scale);
    if (*accum < target)
      return 0;
    *accum = target;
    return 1;
  }
  return 1;
}

/* FUN_001546b0 (0x1546b0) — readable C lift. */
void FUN_001546b0(float *accum, float *rate, float *coeffs, char wrap_flag, float scale)
{
  FUN_00154540(rate, coeffs + 2, scale);
  FUN_001544d0(accum, coeffs, wrap_flag, rate[0]);
}

/* FUN_001546f0 (0x1546f0) — readable C lift: wrapped delta sign helper. */
float FUN_001546f0(float *bounds, float from, char wrap_flag, float to)
{
  float delta;
  float span;
  float abs_delta;

  delta = to - from;
  if (delta == *(float *)0x2533c0) {
    return delta;
  }
  if (wrap_flag) {
    abs_delta = delta < 0.0f ? -delta : delta;
    span = (bounds[0] - bounds[1]) * *(float *)0x253398;
    if (abs_delta > span) {
      delta = -delta;
    }
  }
  if (delta > *(float *)0x2533c0) {
    return *(float *)0x2533c8;
  }
  return *(float *)0x255e94;
}

/* FUN_00154750 (0x154750) — step accum toward target by signed scale; snap on hit. */
__attribute__((noinline, used)) char FUN_00154750(float *accum, float *bounds,
                                                  char wrap_flag, float target,
                                                  float scale)
{
  float sign0;
  float sign1;

  sign0 = FUN_001546f0(bounds, *accum, wrap_flag, target);
  if (sign0 == *(float *)0x2533c0) {
    *accum = target;
    return 1;
  }

  FUN_001544d0(accum, bounds, wrap_flag, sign0 * scale);
  sign1 = FUN_001546f0(bounds, *accum, wrap_flag, target);
  if (sign1 != sign0) {
    *accum = target;
    return 1;
  }
  return 0;
}

/* FUN_001547d0 (0x1547d0) — rate+accum step toward target; clear rate on hit. */
__attribute__((noinline, used)) char FUN_001547d0(float *accum, float *rate,
                                                  float *bounds, char wrap_flag,
                                                  float target, float scale)
{
  float sign0;
  float sign1;

  sign0 = FUN_001546f0(bounds, *accum, wrap_flag, target);
  if (sign0 == *(float *)0x2533c0) {
    *accum = target;
    *rate = 0.0f;
    return 1;
  }

  FUN_00154540(rate, bounds + 2, sign0 * scale);
  FUN_001544d0(accum, bounds, wrap_flag, *rate);
  sign1 = FUN_001546f0(bounds, *accum, wrap_flag, target);
  if (sign1 != sign0) {
    *accum = target;
    *rate = 0.0f;
    return 1;
  }
  return 0;
}


/* point_physics_definition_interpolate (0x1548c0) — readable C lift from XBE leaf.
 * Lerp selected point-physics definition fields; assert on null/out-of-range t. */
void point_physics_definition_interpolate(float *definition_a, float *definition_b,
                                          float t, float *definition_out)
{
  float s;

  s = 1.0f - t;
  if (!definition_a) {
    display_assert((const char *)0x29d978, (const char *)0x29d984, 0x14c, 1);
    system_exit(-1);
  }
  if (!definition_b) {
    display_assert((const char *)0x29d96c, (const char *)0x29d984, 0x14d, 1);
    system_exit(-1);
  }
  /* NaN fails both compares → treat as out of range (matches XBE). */
  if (!(t >= 0.0f && t <= 1.0f)) {
    display_assert((const char *)0x29d958, (const char *)0x29d984, 0x14e, 1);
    system_exit(-1);
  }
  if (!definition_out) {
    display_assert((const char *)0x25f120, (const char *)0x29d984, 0x14f, 1);
    system_exit(-1);
  }

  *(int *)definition_out = *(int *)definition_a;
  definition_out[8] = s * definition_a[8] + t * definition_b[8];
  definition_out[2] = s * definition_a[2] + t * definition_b[2];
  definition_out[3] = s * definition_a[3] + t * definition_b[3];
  definition_out[1] = s * definition_a[1] + t * definition_b[1];
  definition_out[9] = s * definition_a[9] + t * definition_b[9];
  definition_out[10] = s * definition_a[10] + t * definition_b[10];
  definition_out[11] = s * definition_a[11] + t * definition_b[11];
  definition_out[12] = s * definition_a[12] + t * definition_b[12];
}

/* FUN_00154a20 (0x154a20) — readable C lift: debug-draw particle by media flag.
 * XBE: particle@eax, position@edx, scale on stack. */
void FUN_00154a20(void *particle, float *position, float scale)
{
  void *color;

  color = *(void **)0x2ee6d0;
  if ((*(unsigned char *)particle & 2) == 0)
    color = *(void **)0x2ee6d4;
  FUN_00189150(1, position, scale, color);
}

/* FUN_00154a50 (0x154a50) — readable C lift (restored pre-naked). */
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
  /* XBE fcomp+test ah,1: assert when radius < 0 OR unordered (NaN). */
  if (!(radius >= 0.0f)) {
    display_assert((char *)0x29d9b0, (char *)0x29d984, 0xbc, 1);
    system_exit(-1);
  }
  /* XBE fcomp+test ah,0x44: treat equal OR unordered (NaN) as zero-dt early out. */
  if (!(delta_time > 0.0f) && !(delta_time < 0.0f))
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
    if (flags & 1) {
      /* XBE: call for wind side-effects; in_media comes from (flags>>1)&1 in BL. */
      FUN_00190240(position, wind, wind_bits, object_handle);
      in_media = (char)((flags >> 1) & 1);
    } else
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


