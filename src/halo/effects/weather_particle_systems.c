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

/* FUN_000a4310 (0xa4310) — XBE naked draft (batch 111). */
#if defined(__clang__)
static int (*const ba4310_c119610)(data_t *data) = data_new_at_index;
static void (*const ba4310_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const ba4310_exitfn)(int) = system_exit;
static void *(*const ba4310_tag)(int, int) = tag_get;
static void (*const ba4310_ca3ea0)(void) = FUN_000a3ea0;
static void *(*const ba4310_elem)(void *, int, int) = tag_block_get_element;
static void *(*const ba4310_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static unsigned int *(*const ba4310_lseed)(void) = random_math_get_local_seed_address;
static float (*const ba4310_rrange)(int *, float, float) = random_real_range;
static void (*const ba4310_c10b380)(unsigned int *seed, float *out) = random_seed_get_direction3d;
static int16_t (*const ba4310_c10b2d0)(unsigned int *seed, int16_t min, int16_t max) = random_range;
static float (*const ba4310_rmreal)(unsigned int *) = random_math_real;
static float * (*const ba4310_c7c270)(float *out_color, uint32_t flags, float *rgb_lower_bound, float *rgb_upper_bound, float blend) = FUN_0007c270;

__attribute__((naked, noinline))
void FUN_000a4310(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x5aa89c, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movw %%cx, %%di\n\t"
      "call *%[c119610]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LFUN_000a4310_5\n\t"
      "testw %%di, %%di\n\t"
      "jl .LFUN_000a4310_1\n\t"
      "cmpw $4, %%di\n\t"
      "jl .LFUN_000a4310_2\n\t"
      ".LFUN_000a4310_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x5b\n\t"
      "pushl $0x26af50\n\t"
      "pushl $0x266fc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000a4310_2:\n\t"
      "movswl %%di, %%edi\n\t"
      "imull $0x9c, %%edi, %%edi\n\t"
      "addl $0x4557f4, %%edi\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x7261696e\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[ca3ea0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movswl %%si, %%edx\n\t"
      "pushl $0x25c\n\t"
      "pushl %%edx\n\t"
      "addl $0x24, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x5aa89c, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x1a0(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6269746d\n\t"
      "call *%[tag]\n\t"
      "movl 0x4(%%ebx), %%ecx\n\t"
      "addl $0x24, %%esp\n\t"
      "movl %%ecx, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps 0x4(%%esi)\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps 0x8(%%esi)\n\t"
      "movl 0x4(%%ebx), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%edx, %%eax\n\t"
      "pushl %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "movl %%ebx, 0x18(%%esi)\n\t"
      "movl %%ebx, 0x14(%%esi)\n\t"
      "movl %%ebx, 0x10(%%esi)\n\t"
      "addl $0xc, %%esp\n\t"
      "leal 0x1c(%%esi), %%ebx\n\t"
      "fstps 0xc(%%esi)\n\t"
      "pushl %%ebx\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[c10b380]\n\t"
      "movl 0xd0(%%edi), %%ecx\n\t"
      "movl 0xcc(%%edi), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%ebx)\n\t"
      "addl $0xc, %%esp\n\t"
      "fstps (%%ebx)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      "fstps 0x4(%%ebx)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "fstps 0x8(%%ebx)\n\t"
      "movl 0x100(%%edi), %%edx\n\t"
      "movl 0xfc(%%edi), %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps 0x44(%%esi)\n\t"
      "movl 0x108(%%edi), %%eax\n\t"
      "movl 0x104(%%edi), %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps 0x4c(%%esi)\n\t"
      "movl 0x110(%%edi), %%ecx\n\t"
      "movl 0x10c(%%edi), %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps 0x48(%%esi)\n\t"
      "movb 0x20(%%edi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $4, %%al\n\t"
      "je .LFUN_000a4310_3\n\t"
      "pushl $0x40c90fdb\n\t"
      "pushl $0\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps 0x30(%%esi)\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_000a4310_4\n\t"
      ".LFUN_000a4310_3:\n\t"
      "movl $0, 0x30(%%esi)\n\t"
      ".LFUN_000a4310_4:\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x54(%%ebx), %%ax\n\t"
      "addl $0x54, %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[c10b2d0]\n\t"
      "movswl %%ax, %%edx\n\t"
      "pushl $0x40\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "movw %%ax, 0x28(%%esi)\n\t"
      "call *%[elem]\n\t"
      "addl $0x18, %%esp\n\t"
      "fildl 0x34(%%eax)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps 0x2c(%%esi)\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x20(%%edi), %%ecx\n\t"
      "leal 0x148(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x138(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal 0x38(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c7c270]\n\t"
      "movl 0x144(%%edi), %%eax\n\t"
      "movl 0x134(%%edi), %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "addl $0x24, %%esp\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "fstps 0x34(%%esi)\n\t"
      "movl 0xc(%%ecx), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%edx, 0x50(%%esi)\n\t"
      "incw 0x8(%%ecx)\n\t"
      "movl %%eax, 0xc(%%ecx)\n\t"
      "popl %%ebx\n\t"
      ".LFUN_000a4310_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c119610] "m"(ba4310_c119610), [assert] "m"(ba4310_assert), [exitfn] "m"(ba4310_exitfn), [tag] "m"(ba4310_tag), [ca3ea0] "m"(ba4310_ca3ea0), [elem] "m"(ba4310_elem), [dget] "m"(ba4310_dget), [lseed] "m"(ba4310_lseed), [rrange] "m"(ba4310_rrange), [c10b380] "m"(ba4310_c10b380), [c10b2d0] "m"(ba4310_c10b2d0), [rmreal] "m"(ba4310_rmreal), [c7c270] "m"(ba4310_c7c270)
      : "memory");
}
#else
#error "FUN_000a4310: clang naked draft required"
#endif


/* 0xa45d0 */
void FUN_000a45d0(void)
{
  FUN_000a4000((float *)0, (float *)0, 0.0f);
}

/* FUN_000a4610 (0xa4610) — XBE naked draft (batch 112). */
#if defined(__clang__)
static void (*const ba4610_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const ba4610_exitfn)(int) = system_exit;
static void *(*const ba4610_tag)(int, int) = tag_get;
static void *(*const ba4610_elem)(void *, int, int) = tag_block_get_element;
static void *(*const ba4610_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static float (*const ba4610_norm)(float *) = normalize3d;
static unsigned int *(*const ba4610_lseed)(void) = random_math_get_local_seed_address;
static float (*const ba4610_rrange)(int *, float, float) = random_real_range;
static void (*const ba4610_c10b380)(unsigned int *seed, float *out) = random_seed_get_direction3d;
static int (*const ba4610_c154a50)(int flags, int physics_tag_data, int *collision_location, int object_handle, float *position, float *velocity, float *force, float *collision_normal_out, int16_t *surface_index_out, float radius, float delta_time) = FUN_00154a50;
static void (*const ba4610_ca4000)(float *dst, float *src, float scale) = FUN_000a4000;

__attribute__((naked, noinline))
void FUN_000a4610(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movw %%cx, %%di\n\t"
      "testw %%di, %%di\n\t"
      "movw %%ax, %%si\n\t"
      "jl .LFUN_000a4610_1\n\t"
      "cmpw $4, %%di\n\t"
      "jl .LFUN_000a4610_2\n\t"
      ".LFUN_000a4610_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x5b\n\t"
      "pushl $0x26af50\n\t"
      "pushl $0x266fc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000a4610_2:\n\t"
      "movswl %%di, %%ebx\n\t"
      "imull $0x9c, %%ebx, %%ebx\n\t"
      "addl $0x4557f4, %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x7261696e\n\t"
      "call *%[tag]\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x7261696e\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[tag]\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_000a4610_3\n\t"
      "movl 0x24(%%eax), %%ecx\n\t"
      "movswl %%si, %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jl .LFUN_000a4610_4\n\t"
      ".LFUN_000a4610_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x66\n\t"
      "pushl $0x26af50\n\t"
      "pushl $0x26af84\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000a4610_4:\n\t"
      "movswl %%si, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl $0x25c\n\t"
      "shll $4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal 0x1c(%%ecx,%%ebx,1), %%edx\n\t"
      "addl $0x24, %%edi\n\t"
      "pushl %%edi\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x5aa89c, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "flds 0xcc(%%esi)\n\t"
      "addl $0x14, %%esp\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000a4610_5\n\t"
      "flds 0xd0(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000a4610_8\n\t"
      ".LFUN_000a4610_5:\n\t"
      "leal 0x1c(%%edi), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[norm]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0xd4(%%eax)\n\t"
      "movl 0xd8(%%eax), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "movl %%ecx, %%edx\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "flds 0xd8(%%eax)\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fcomps 0xcc(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000a4610_6\n\t"
      "movl 0xcc(%%ecx), %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jmp .LFUN_000a4610_7\n\t"
      ".LFUN_000a4610_6:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0xd0(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a4610_7\n\t"
      "movl 0xd0(%%ecx), %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".LFUN_000a4610_7:\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[c10b380]\n\t"
      "flds -0x24(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "fmuls 0xd4(%%eax)\n\t"
      "addl $8, %%esp\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps (%%esi)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0xd4(%%eax)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x20(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps 0x20(%%edi)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0xd4(%%eax)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x24(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps 0x24(%%edi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "fstps (%%esi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "fstps 0x8(%%esi)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%esi)\n\t"
      "fadds 0x10(%%edi)\n\t"
      "fstps 0x10(%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "fadds 0x14(%%edi)\n\t"
      "fstps 0x14(%%edi)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "fadds 0x18(%%edi)\n\t"
      "fstps 0x18(%%edi)\n\t"
      ".LFUN_000a4610_8:\n\t"
      "movb 0x1a(%%ebx), %%dl\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testb %%dl, %%dl\n\t"
      "movl 0x8(%%ebx), %%edx\n\t"
      "setne %%cl\n\t"
      "pushl %%edx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl 0x44(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0xb8(%%edx), %%eax\n\t"
      "pushl $0\n\t"
      "leal 0x5(%%ecx,%%ecx,1), %%ecx\n\t"
      "pushl $0\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "pushl $0\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x18(%%ebx), %%cx\n\t"
      "leal 0x4(%%edi), %%esi\n\t"
      "addl $0x10, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "addl $0x10, %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x70706879\n\t"
      "call *%[tag]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c154a50]\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c10b380]\n\t"
      "flds (%%eax)\n\t"
      "fmuls 0x255ef8\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl %%esi, %%edi\n\t"
      "fadds (%%esi)\n\t"
      "fstps (%%esi)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x255ef8\n\t"
      "fadds 0x4(%%esi)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x255ef8\n\t"
      "fadds 0x8(%%esi)\n\t"
      "fstps 0x8(%%esi)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[ca4000]\n\t"
      "addl $0x38, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(ba4610_assert), [exitfn] "m"(ba4610_exitfn), [tag] "m"(ba4610_tag), [elem] "m"(ba4610_elem), [dget] "m"(ba4610_dget), [norm] "m"(ba4610_norm), [lseed] "m"(ba4610_lseed), [rrange] "m"(ba4610_rrange), [c10b380] "m"(ba4610_c10b380), [c154a50] "m"(ba4610_c154a50), [ca4000] "m"(ba4610_ca4000)
      : "memory");
}
#else
#error "FUN_000a4610: clang naked draft required"
#endif


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

/* FUN_000a4be0 (0xa4be0) — XBE naked draft (batch 114). */
#if defined(__clang__)
static void (*const ba4be0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const ba4be0_exitfn)(int) = system_exit;
static void *(*const ba4be0_tag)(int, int) = tag_get;
static void *(*const ba4be0_elem)(void *, int, int) = tag_block_get_element;
static void (*const ba4be0_ca4ab0)(void) = FUN_000a4ab0;
static void *(*const ba4be0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const ba4be0_c1daf7e)(void) = FUN_001daf7e;
static void (*const ba4be0_ca4610)(void) = FUN_000a4610;

__attribute__((naked, noinline))
void FUN_000a4be0(int16_t weather_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_000a4be0_1\n\t"
      "cmpw $4, %%si\n\t"
      "jl .LFUN_000a4be0_2\n\t"
      ".LFUN_000a4be0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x5b\n\t"
      "pushl $0x26af50\n\t"
      "pushl $0x266fc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000a4be0_2:\n\t"
      "movswl %%si, %%ebx\n\t"
      "imull $0x9c, %%ebx, %%ebx\n\t"
      "addl $0x4557f4, %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x7261696e\n\t"
      "call *%[tag]\n\t"
      "movl 0x50654c, %%ecx\n\t"
      "movl %%ecx, 0x8(%%ebx)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "addl $0x24, %%eax\n\t"
      "fadds 0x4(%%ebx)\n\t"
      "xorl %%esi, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "fstps 0x4(%%ebx)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jle .LFUN_000a4be0_12\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000a4be0_3:\n\t"
      "movl (%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x7261696e\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_000a4be0_4\n\t"
      "cmpl 0x24(%%eax), %%edi\n\t"
      "jl .LFUN_000a4be0_5\n\t"
      ".LFUN_000a4be0_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x66\n\t"
      "pushl $0x26af50\n\t"
      "pushl $0x26af84\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000a4be0_5:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%edi, %%eax\n\t"
      "pushl $0x25c\n\t"
      "shll $4, %%eax\n\t"
      "leal 0x1c(%%eax,%%ebx,1), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x1a0(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6269746d\n\t"
      "call *%[tag]\n\t"
      "flds 0xc(%%ebx)\n\t"
      "movl 0x506558, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "fsubs 0x34(%%edi)\n\t"
      "addl $0x14, %%esp\n\t"
      "flds 0x38(%%edi)\n\t"
      "fsubs 0x34(%%edi)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000a4be0_6\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_000a4be0_7\n\t"
      ".LFUN_000a4be0_6:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a4be0_7\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_000a4be0_7:\n\t"
      ".byte 0xde, 0xc9\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fsubs 0x3c(%%edi)\n\t"
      "flds 0x40(%%edi)\n\t"
      "fsubs 0x3c(%%edi)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000a4be0_8\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_000a4be0_9\n\t"
      ".LFUN_000a4be0_8:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a4be0_9\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_000a4be0_9:\n\t"
      "flds 0x2533c8\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "pushl %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edx\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[ca4ab0]\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl 0xc(%%eax), %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_000a4be0_11\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "addl $0x54, %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      ".LFUN_000a4be0_10:\n\t"
      "movl 0x5aa89c, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "flds 0x4c(%%esi)\n\t"
      "movswl 0x28(%%esi), %%eax\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "pushl $0x40\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "fadds 0x2c(%%esi)\n\t"
      "fsts 0x2c(%%esi)\n\t"
      "fstpl -0x14(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "fldl -0x14(%%ebp)\n\t"
      "fildl 0x34(%%eax)\n\t"
      "call *%[c1daf7e]\n\t"
      "fstps 0x2c(%%esi)\n\t"
      "movl %%edi, %%edx\n\t"
      "andb $1, %%dl\n\t"
      "negb %%dl\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "sbbl %%edx, %%edx\n\t"
      "andl $0xfffffffe, %%edx\n\t"
      "incl %%edx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "fmuls 0x48(%%esi)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "fadds 0x30(%%esi)\n\t"
      "fstps 0x30(%%esi)\n\t"
      "call *%[ca4610]\n\t"
      "movl 0x50(%%esi), %%edi\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .LFUN_000a4be0_10\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      ".LFUN_000a4be0_11:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%edi\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "jl .LFUN_000a4be0_3\n\t"
      "popl %%edi\n\t"
      ".LFUN_000a4be0_12:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(ba4be0_assert), [exitfn] "m"(ba4be0_exitfn), [tag] "m"(ba4be0_tag), [elem] "m"(ba4be0_elem), [ca4ab0] "m"(ba4be0_ca4ab0), [dget] "m"(ba4be0_dget), [c1daf7e] "m"(ba4be0_c1daf7e), [ca4610] "m"(ba4be0_ca4610)
      : "memory");
}
#else
#error "FUN_000a4be0: clang naked draft required"
#endif


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


