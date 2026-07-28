#include <stdint.h>
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

/* FUN_000a3e60 (0xa3e60) — readable C lift. */
void *FUN_000a3e60(int16_t index)
{
  if (index < 0 || index >= 4) {
    display_assert((const char *)0x266fc0, (const char *)0x26af50, 0x5b, 1);
    system_exit(-1);
  }
  return (void *)(0x4557f4 + (int)index * 0x9c);
}

/* FUN_000a3ea0 (0xa3ea0) — readable C lift: particle type entry from rain tag. */
void *FUN_000a3ea0(void *particle, int16_t type_index)
{
  extern char DAT_0026af50[];
  extern char DAT_0026af84[];
  void *tag;
  int count;

  tag = tag_get(0x7261696e, *(int *)particle);
  count = *(int *)((char *)tag + 0x24);
  if (type_index < 0 || (int)type_index >= count) {
    display_assert(DAT_0026af84, DAT_0026af50, 0x66, true);
    system_exit(-1);
  }
  return (char *)particle + 0x1c + ((int)type_index << 4);
}


/* FUN_000a4000 (0xa4000) — readable C lift.
 * Oracle: dst@<edi>, src@<esi>, scale cdecl. fmod via FUN_001daf7e. */
void FUN_000a4000(float *dst, float *src, float scale)
{
  int i;
  float local;
  float v;

  for (i = 0; i < 3; i++) {
    v = src[i];
    if (!(v >= 0.0f))
      local = scale;
    else
      local = 0.0f;
    dst[i] = __builtin_fmodf(v, scale) + local;
  }
}

/* weather_particle_system_new (0xa40a0) — readable C lift (restored pre-naked). */
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


/* weather_particle_system_delete (0xa4200) — readable C lift. */
void weather_particle_system_delete(short index)
{
  char *slot;
  void *tag;
  int i;
  int count;
  char *part;
  int handle;
  char *datum;
  int next;

  if (index < 0 || index >= 4) {
    display_assert((const char *)0x266fc0, (const char *)0x26af50, 0x5b, 1);
    system_exit(-1);
  }
  slot = (char *)(0x4557f4 + (int)index * 0x9c);
  tag = tag_get(0x7261696e, *(int *)slot);
  count = *(int *)((char *)tag + 0x24);
  for (i = 0; i < count; i++) {
    tag = tag_get(0x7261696e, *(int *)slot);
    if (i < 0 || i >= *(int *)((char *)tag + 0x24)) {
      display_assert((const char *)0x26af84, (const char *)0x26af50, 0x66, 1);
      system_exit(-1);
    }
    part = slot + 0x1c + i * 0x10;
    handle = *(int *)(part + 0xc);
    while (handle != -1) {
      datum = (char *)datum_get(*(data_t **)0x5aa89c, handle);
      next = *(int *)(datum + 0x50);
      datum_delete(*(data_t **)0x5aa89c, handle);
      *(int16_t *)(part + 8) = (int16_t)(*(int16_t *)(part + 8) - 1);
      handle = next;
      *(int *)(part + 0xc) = handle;
    }
  }
  *(int16_t *)0x4557f0 = (int16_t)(*(int16_t *)0x4557f0 - 1);
  *(int *)slot = -1;
}
/* FUN_000a4310 (0xa4310) — XBE naked draft (batch 111). */
#if defined(__clang__)
static int (*const ba4310_c119610)(data_t *data) = data_new_at_index;
static void (*const ba4310_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const ba4310_exitfn)(int) = system_exit;
static void *(*const ba4310_tag)(int, int) = tag_get;
static void (*const ba4310_ca3ea0)(void) = (void *)FUN_000a3ea0;
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


/* FUN_000a45d0 (0xa45d0) — readable C lift. */
void FUN_000a45d0(float *dst, float *src, float scale)
{
  FUN_000a4000(dst, src, scale);
  dst[0] = src[0] - dst[0];
  dst[1] = src[1] - dst[1];
  dst[2] = src[2] - dst[2];
}


/* FUN_000a4610 (0xa4610) — readable C lift (restored pre-naked). */
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


/* FUN_000a48c0 (0xa48c0) — readable C lift.
 * mat@<ecx>, scale cdecl. Fill mat from globals + scaled offset vector. */
void FUN_000a48c0(float *mat, float scale)
{
  float *v;
  float a, b, c;
  float *src;
  int i;

  v = mat + 16; /* +0x40 */
  v[0] = *(float *)0x50655c;
  v[1] = *(float *)0x506560;
  v[2] = *(float *)0x506564;
  a = v[0] * scale + *(float *)0x506550;
  b = v[1] * scale + *(float *)0x506554;
  c = v[2] * scale + *(float *)0x506558;
  v[3] = a * v[0] + b * v[1] + c * v[2];

  src = (float *)0x50661c;
  for (i = 0; i < 16; i++)
    mat[i] = src[i];
}

/* FUN_000a4a00 (0xa4a00) — readable C lift. */
int16_t FUN_000a4a00(int16_t *out_buf, float radius)
{
  char *scenario;
  char *block;
  int16_t found;
  int16_t i;
  int n;
  char *elem;
  float dx, dy, dz, r, d2, r2;

  scenario = (char *)scenario_get();
  block = scenario + 0x1c0;
  found = 0;
  n = *(int *)block;
  for (i = 0; i < n; i++) {
    elem = (char *)tag_block_get_element(block, (int)i, 0x20);
    dx = *(float *)elem - *(float *)0x506550;
    dy = *(float *)(elem + 4) - *(float *)0x506554;
    dz = *(float *)(elem + 8) - *(float *)0x506558;
    r = radius + *(float *)(elem + 0xc);
    d2 = dx * dx + dy * dy + dz * dz;
    r2 = r * r;
    if (d2 > r2) {
      if (found >= 8)
        error(2, (const char *)0x26b02c);
      else {
        out_buf[found] = i;
        found++;
      }
    }
  }
  return found;
}

/* FUN_000a4ab0 (0xa4ab0) — readable C lift (restored pre-naked). */
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


/* FUN_000a4be0 (0xa4be0) — readable C lift (restored pre-naked). */
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


/* weather_particle_system_render (0xa4e20) — readable C lift (restored pre-naked). */
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



