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

/* FUN_00154a50 (0x154a50) — XBE naked draft (batch 224). */
#if defined(__clang__)
static bool (*const b154a50_ca16b0)(float *point) = valid_real_point3d;
static char * (*const b154a50_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b154a50_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b154a50_exitfn)(int) = system_exit;
static int (*const b154a50_c84a10)(float *vector) = real_vector3d_valid;
static char (*const b154a50_c190240)(float *position, float *wind_out, int wind_flags, int object_handle) = FUN_00190240;
static char (*const b154a50_c190550)(int *collision_location, float *position, float *wind_out, int flags) = FUN_00190550;
static bool (*const b154a50_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;
static void (*const b154a50_c10b8a0)(float *v, float *axis, float *parallel, float *perpendicular) = FUN_0010b8a0;
static void (*const b154a50_c189150)(char flag, float *position, float scale, void *color) = FUN_00189150;

__attribute__((naked, noinline))
int FUN_00154a50(int flags __attribute__((unused)), int physics_tag_data __attribute__((unused)), int *collision_location __attribute__((unused)), int object_handle __attribute__((unused)), float *position __attribute__((unused)), float *velocity __attribute__((unused)), float *force __attribute__((unused)), float *collision_normal_out __attribute__((unused)), int16_t *surface_index_out __attribute__((unused)), float radius __attribute__((unused)), float delta_time __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x94, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x18(%%ebp), %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "call *%[ca16b0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00154a50_1\n\t"
      "flds 0x8(%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0xb9\n\t"
      "pushl $0x29d984\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x267114\n\t"
      "pushl $0x26ae04\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00154a50_1:\n\t"
      "pushl %%esi\n\t"
      "movl 0x1c(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00154a50_2\n\t"
      "flds 0x8(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0xba\n\t"
      "pushl $0x29d984\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29da04\n\t"
      "pushl $0x26ae40\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00154a50_2:\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00154a50_3\n\t"
      "pushl %%eax\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00154a50_3\n\t"
      "pushl $1\n\t"
      "pushl $0xbb\n\t"
      "pushl $0x29d984\n\t"
      "pushl $0x29d9c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00154a50_3:\n\t"
      "flds 0x2c(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_00154a50_4\n\t"
      "pushl $1\n\t"
      "pushl $0xbc\n\t"
      "pushl $0x29d984\n\t"
      "pushl $0x29d9b0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00154a50_4:\n\t"
      "flds 0x30(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00154a50_35\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "flds 0x2c(%%ebp)\n\t"
      "fmuls 0x2c(%%ebp)\n\t"
      "movl (%%edi), %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movzbl %%cl, %%eax\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "shrl $3, %%eax\n\t"
      "fmuls 0x2c(%%ebp)\n\t"
      "andl $1, %%eax\n\t"
      "testb $0x10, %%cl\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "je .LFUN_00154a50_5\n\t"
      "orl $2, %%eax\n\t"
      "jmp .LFUN_00154a50_6\n\t"
      ".LFUN_00154a50_5:\n\t"
      "andl $0xfffffffd, %%eax\n\t"
      ".LFUN_00154a50_6:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "testb $1, %%cl\n\t"
      "je .LFUN_00154a50_7\n\t"
      "movl %%ecx, %%ebx\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "shrl $1, %%ebx\n\t"
      "pushl %%eax\n\t"
      "andb $1, %%bl\n\t"
      "call *%[c190240]\n\t"
      "jmp .LFUN_00154a50_8\n\t"
      ".LFUN_00154a50_7:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[c190550]\n\t"
      "movb %%al, %%bl\n\t"
      ".LFUN_00154a50_8:\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00154a50_9\n\t"
      "flds 0x4761fc\n\t"
      "movl $2, -0xc(%%ebp)\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x8(%%edi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x28(%%edi)\n\t"
      "jmp .LFUN_00154a50_10\n\t"
      ".LFUN_00154a50_9:\n\t"
      "flds 0x476200\n\t"
      "movl $1, -0xc(%%ebp)\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0xc(%%edi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x24(%%edi)\n\t"
      ".LFUN_00154a50_10:\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "movb (%%edi), %%al\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl $0x20, %%edx\n\t"
      "testb %%al, %%dl\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x30(%%ebp)\n\t"
      "fdivs -0x8(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "je .LFUN_00154a50_11\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      ".LFUN_00154a50_11:\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00154a50_12\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00154a50_12\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls (%%ecx)\n\t"
      "fadds (%%esi)\n\t"
      "fstps (%%esi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "fadds 0x4(%%esi)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      "fadds 0x8(%%esi)\n\t"
      "fstps 0x8(%%esi)\n\t"
      ".LFUN_00154a50_12:\n\t"
      "flds 0x32512c\n\t"
      "fmuls 0x253394\n\t"
      "fmuls 0x253394\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fmuls 0x30(%%ebp)\n\t"
      "fadds 0x8(%%esi)\n\t"
      "fstps 0x8(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00154a50_13\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00154a50_15\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_00154a50_16\n\t"
      ".LFUN_00154a50_13:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00154a50_14\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_00154a50_16\n\t"
      ".LFUN_00154a50_14:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00154a50_16\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00154a50_15:\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_00154a50_16:\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fsubs (%%esi)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds (%%esi)\n\t"
      "fstps (%%esi)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x4(%%esi)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fsubs 0x8(%%esi)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x8(%%esi)\n\t"
      "fstps 0x8(%%esi)\n\t"
      "movl (%%edi), %%eax\n\t"
      "testb $4, %%al\n\t"
      "fstp %%st(0)\n\t"
      "je .LFUN_00154a50_17\n\t"
      "testb $4, 0x8(%%ebp)\n\t"
      "movl $0x41, 0x20(%%ebp)\n\t"
      "je .LFUN_00154a50_18\n\t"
      ".LFUN_00154a50_17:\n\t"
      "movl $1, 0x20(%%ebp)\n\t"
      ".LFUN_00154a50_18:\n\t"
      "testb $2, %%al\n\t"
      "je .LFUN_00154a50_19\n\t"
      "testb $4, 0x8(%%ebp)\n\t"
      "jne .LFUN_00154a50_19\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "orl %%edx, %%eax\n\t"
      "jmp .LFUN_00154a50_20\n\t"
      ".LFUN_00154a50_19:\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "andl $0xffffffdf, %%eax\n\t"
      ".LFUN_00154a50_20:\n\t"
      "cmpw %%dx, 0x4761d8\n\t"
      "movl %%eax, 0x20(%%ebp)\n\t"
      "jl .LFUN_00154a50_21\n\t"
      "pushl $1\n\t"
      "pushl $0x10d\n\t"
      "pushl $0x29d984\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00154a50_21:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "incw %%ax\n\t"
      "movw $0xd, 0x5a8c80(,%%ecx,2)\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      ".LFUN_00154a50_22:\n\t"
      "cmpw $3, -0x10(%%ebp)\n\t"
      "jge .LFUN_00154a50_33\n\t"
      "flds 0x30(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%ebx\n\t"
      "fmuls (%%esi)\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "leal -0x94(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "pushl $-1\n\t"
      "flds 0x30(%%ebp)\n\t"
      "leal -0x44(%%ebp), %%eax\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds 0x30(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00154a50_31\n\t"
      "flds 0x2c(%%ebp)\n\t"
      "fcomps 0x29d9ac\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00154a50_23\n\t"
      "movl $0x3ba3d70a, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00154a50_24\n\t"
      ".LFUN_00154a50_23:\n\t"
      "movl 0x2c(%%ebp), %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".LFUN_00154a50_24:\n\t"
      "movw -0x94(%%ebp), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_00154a50_25\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "orl $8, %%eax\n\t"
      "jmp .LFUN_00154a50_26\n\t"
      ".LFUN_00154a50_25:\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .LFUN_00154a50_27\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "orl $4, %%eax\n\t"
      ".LFUN_00154a50_26:\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      ".LFUN_00154a50_27:\n\t"
      "movl 0x24(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00154a50_28\n\t"
      "movl -0x70(%%ebp), %%ecx\n\t"
      "movl -0x6c(%%ebp), %%edx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x68(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      ".LFUN_00154a50_28:\n\t"
      "movl 0x28(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00154a50_29\n\t"
      "movw -0x60(%%ebp), %%dx\n\t"
      "movw %%dx, (%%eax)\n\t"
      ".LFUN_00154a50_29:\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x70(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c10b8a0]\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x2c(%%edi)\n\t"
      "movl -0x88(%%ebp), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls 0x30(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps (%%esi)\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x2c(%%edi)\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls 0x30(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x2c(%%edi)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls 0x30(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x8(%%esi)\n\t"
      "je .LFUN_00154a50_30\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl -0x84(%%ebp), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      ".LFUN_00154a50_30:\n\t"
      "flds -0x70(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "fadds -0x7c(%%ebp)\n\t"
      "fstps (%%ebx)\n\t"
      "flds -0x6c(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fadds -0x78(%%ebp)\n\t"
      "fstps 0x4(%%ebx)\n\t"
      "flds -0x68(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fadds -0x74(%%ebp)\n\t"
      "fstps 0x8(%%ebx)\n\t"
      "flds -0x80(%%ebp)\n\t"
      "fmuls 0x30(%%ebp)\n\t"
      "fsubrs 0x30(%%ebp)\n\t"
      "fstps 0x30(%%ebp)\n\t"
      "flds 0x30(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00154a50_22\n\t"
      "jmp .LFUN_00154a50_33\n\t"
      ".LFUN_00154a50_31:\n\t"
      "movl -0x88(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00154a50_32\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl -0x84(%%ebp), %%edx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      ".LFUN_00154a50_32:\n\t"
      "movl -0x7c(%%ebp), %%eax\n\t"
      "movl -0x78(%%ebp), %%ecx\n\t"
      "movl -0x74(%%ebp), %%edx\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "movl %%ecx, 0x4(%%ebx)\n\t"
      "movl %%edx, 0x8(%%ebx)\n\t"
      ".LFUN_00154a50_33:\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "jg .LFUN_00154a50_34\n\t"
      "pushl $1\n\t"
      "pushl $0x138\n\t"
      "pushl $0x29d984\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00154a50_34:\n\t"
      "decw 0x4761d8\n\t"
      "movl 0x18(%%ebp), %%ebx\n\t"
      ".LFUN_00154a50_35:\n\t"
      "movb 0x5a5e20, %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "je .LFUN_00154a50_37\n\t"
      "testb $2, (%%edi)\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "jne .LFUN_00154a50_36\n\t"
      "movl 0x2ee6d4, %%eax\n\t"
      ".LFUN_00154a50_36:\n\t"
      "pushl %%eax\n\t"
      "movl 0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00154a50_37:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [ca16b0] "m"(b154a50_ca16b0), [c8d9d0] "m"(b154a50_c8d9d0), [assert] "m"(b154a50_assert), [exitfn] "m"(b154a50_exitfn), [c84a10] "m"(b154a50_c84a10), [c190240] "m"(b154a50_c190240), [c190550] "m"(b154a50_c190550), [ray] "m"(b154a50_ray), [c10b8a0] "m"(b154a50_c10b8a0), [c189150] "m"(b154a50_c189150)
      : "memory");
}
#else
#error "FUN_00154a50: clang naked draft required"
#endif


