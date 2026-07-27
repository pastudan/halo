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

/* weather_particle_system_new (0xa40a0) — XBE naked draft (batch 125). */
#if defined(__clang__)
static void (*const ba40a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const ba40a0_exitfn)(int) = system_exit;
static void *(*const ba40a0_tag)(int, int) = tag_get;
static void *(*const ba40a0_elem)(void *, int, int) = tag_block_get_element;
static unsigned int *(*const ba40a0_lseed)(void) = random_math_get_local_seed_address;
static float (*const ba40a0_rrange)(int *, float, float) = random_real_range;

__attribute__((naked, noinline))
void weather_particle_system_new(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movw 0x8(%%ebp), %%si\n\t"
      "testw %%si, %%si\n\t"
      "pushl %%edi\n\t"
      "jl .Lweather_particle_system_new_1\n\t"
      "cmpw $4, %%si\n\t"
      "jl .Lweather_particle_system_new_2\n\t"
      ".Lweather_particle_system_new_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x5b\n\t"
      "pushl $0x26af50\n\t"
      "pushl $0x266fc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lweather_particle_system_new_2:\n\t"
      "movswl %%si, %%edi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "imull $0x9c, %%edi, %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl $0x7261696e\n\t"
      "addl $0x4557f4, %%edi\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%edi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lweather_particle_system_new_3\n\t"
      "pushl $1\n\t"
      "pushl $0xb1\n\t"
      "pushl $0x26af50\n\t"
      "pushl $0x26b00c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lweather_particle_system_new_3:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%eax, 0xc(%%edi)\n\t"
      "movl %%esi, (%%edi)\n\t"
      "movl %%ecx, 0x4(%%edi)\n\t"
      "movl %%ecx, 0x8(%%edi)\n\t"
      "incw 0x4557f0\n\t"
      "movl 0x24(%%ebx), %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "leal 0x24(%%ebx), %%eax\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "jle .Lweather_particle_system_new_7\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lweather_particle_system_new_4:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x7261696e\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, 0x8(%%ebp)\n\t"
      "jl .Lweather_particle_system_new_5\n\t"
      "cmpl 0x24(%%eax), %%ebx\n\t"
      "jl .Lweather_particle_system_new_6\n\t"
      ".Lweather_particle_system_new_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x66\n\t"
      "pushl $0x26af50\n\t"
      "pushl $0x26af84\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lweather_particle_system_new_6:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl $0x25c\n\t"
      "movl %%ebx, %%edx\n\t"
      "shll $4, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "leal 0x1c(%%edx,%%edi,1), %%esi\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl $0xffffffff, 0xc(%%esi)\n\t"
      "movw $0, 0x8(%%esi)\n\t"
      "movl 0xa8(%%ebx), %%ecx\n\t"
      "movl 0xa4(%%ebx), %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps (%%esi)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x30(%%ebx), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "incl %%eax\n\t"
      "movswl %%ax, %%ebx\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "cmpl (%%eax), %%ebx\n\t"
      "jl .Lweather_particle_system_new_4\n\t"
      ".Lweather_particle_system_new_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(ba40a0_assert), [exitfn] "m"(ba40a0_exitfn), [tag] "m"(ba40a0_tag), [elem] "m"(ba40a0_elem), [lseed] "m"(ba40a0_lseed), [rrange] "m"(ba40a0_rrange)
      : "memory");
}
#else
#error "weather_particle_system_new: clang naked draft required"
#endif


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
static void (*const ba4610_ca4000)(float *dst, float *src, float scale) = (void *)FUN_000a4000;

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

/* FUN_000a4ab0 (0xa4ab0) — XBE naked draft (batch 127). */
#if defined(__clang__)
static void (*const ba4ab0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const ba4ab0_exitfn)(int) = system_exit;
static void *(*const ba4ab0_tag)(int, int) = tag_get;
static void (*const ba4ab0_ftol)(void) = FUN_001d9068;
static void (*const ba4ab0_ca4310)(void) = (void *)FUN_000a4310;
static void *(*const ba4ab0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const ba4ab0_c1196d0)(data_t *data, int datum_handle) = datum_delete;

__attribute__((naked, noinline))
void FUN_000a4ab0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testw %%si, %%si\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "jl .LFUN_000a4ab0_1\n\t"
      "cmpw $4, %%si\n\t"
      "jl .LFUN_000a4ab0_2\n\t"
      ".LFUN_000a4ab0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x5b\n\t"
      "pushl $0x26af50\n\t"
      "pushl $0x266fc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000a4ab0_2:\n\t"
      "movswl %%si, %%esi\n\t"
      "imull $0x9c, %%esi, %%esi\n\t"
      "addl $0x4557f4, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x7261696e\n\t"
      "call *%[tag]\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x7261696e\n\t"
      "call *%[tag]\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .LFUN_000a4ab0_3\n\t"
      "movl 0x24(%%eax), %%ecx\n\t"
      "movswl %%bx, %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jl .LFUN_000a4ab0_4\n\t"
      ".LFUN_000a4ab0_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x66\n\t"
      "pushl $0x26af50\n\t"
      "pushl $0x26af84\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000a4ab0_4:\n\t"
      "movswl 0x4557f0, %%ecx\n\t"
      "movswl %%bx, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "leal 0x1c(%%eax,%%esi,1), %%esi\n\t"
      "flds 0x4(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "fidivl 0xc(%%ebp)\n\t"
      "call *%[ftol]\n\t"
      "fstp %%st(0)\n\t"
      "xorl %%edx, %%edx\n\t"
      "testl %%eax, %%eax\n\t"
      "setl %%dl\n\t"
      "decl %%edx\n\t"
      "andl %%eax, %%edx\n\t"
      "movswl 0x8(%%esi), %%eax\n\t"
      "movl %%edx, %%edi\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jge .LFUN_000a4ab0_6\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000a4ab0_5:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[ca4310]\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000a4ab0_6\n\t"
      "movswl 0x8(%%esi), %%ecx\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "jl .LFUN_000a4ab0_5\n\t"
      ".LFUN_000a4ab0_6:\n\t"
      "movswl 0x8(%%esi), %%edx\n\t"
      "cmpl %%edi, %%edx\n\t"
      "jle .LFUN_000a4ab0_8\n\t"
      "nop\n\t"
      ".LFUN_000a4ab0_7:\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "movl 0x5aa89c, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "movl 0x50(%%eax), %%ebx\n\t"
      "movl 0x5aa89c, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1196d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "decw 0x8(%%esi)\n\t"
      "movl %%ebx, 0xc(%%esi)\n\t"
      "movswl 0x8(%%esi), %%ecx\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "jg .LFUN_000a4ab0_7\n\t"
      ".LFUN_000a4ab0_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(ba4ab0_assert), [exitfn] "m"(ba4ab0_exitfn), [tag] "m"(ba4ab0_tag), [ftol] "m"(ba4ab0_ftol), [ca4310] "m"(ba4ab0_ca4310), [dget] "m"(ba4ab0_dget), [c1196d0] "m"(ba4ab0_c1196d0)
      : "memory");
}
#else
#error "FUN_000a4ab0: clang naked draft required"
#endif


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


/* weather_particle_system_render (0xa4e20) — XBE naked draft (batch 223). */
#if defined(__clang__)
static void (*const ba4e20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const ba4e20_exitfn)(int) = system_exit;
static void *(*const ba4e20_tag)(int, int) = tag_get;
static void * (*const ba4e20_c18e3c0)(void) = scenario_get;
static void (*const ba4e20_ca4be0)(int16_t weather_index) = FUN_000a4be0;
static void *(*const ba4e20_elem)(void *, int, int) = tag_block_get_element;
static int (*const ba4e20_ca4a00)(void *out_buf, int particle_handle) = (void *)FUN_000a4a00;
static void (*const ba4e20_ca48c0)(float *out, float scale) = (void *)FUN_000a48c0;
static void (*const ba4e20_ca4000)(float *dst, float *src, float scale) = (void *)FUN_000a4000;
static short (*const ba4e20_c1867f0)(void *param_1, int param_2, int param_3) = render_frustum_cube_visible;
static void (*const ba4e20_c18d2c0)(uint32_t *param_1, int16_t param_2, uint32_t param_3, int param_4, uint32_t param_5) = FUN_0018d2c0;
static void *(*const ba4e20_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const ba4e20_ftol)(void) = FUN_001d9068;
static void (*const ba4e20_c18d6e0)(void *data, int16_t mode, int16_t sequence_index, int16_t sprite_index, float *untransformed_origin, float *untransformed_direction, float angle, float scale, float *color, float intensity, uint32_t flags) = FUN_0018d6e0;
static void (*const ba4e20_c18d360)(void *sprite_build_data) = FUN_0018d360;

__attribute__((naked, noinline))
void weather_particle_system_render(int16_t weather_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x4dc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "testw %%si, %%si\n\t"
      "pushl %%edi\n\t"
      "jl .Lweather_particle_system_render_1\n\t"
      "cmpw $4, %%si\n\t"
      "jl .Lweather_particle_system_render_2\n\t"
      ".Lweather_particle_system_render_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x5b\n\t"
      "pushl $0x26af50\n\t"
      "pushl $0x266fc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lweather_particle_system_render_2:\n\t"
      "movswl %%si, %%ebx\n\t"
      "imull $0x9c, %%ebx, %%ebx\n\t"
      "addl $0x4557f4, %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x7261696e\n\t"
      "movl %%ebx, -0x60(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c18e3c0]\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x5c(%%ebp)\n\t"
      "call *%[ca4be0]\n\t"
      "movl 0x24(%%edi), %%ecx\n\t"
      "addl $0x24, %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movl %%edi, -0x34(%%ebp)\n\t"
      "jle .Lweather_particle_system_render_38\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lweather_particle_system_render_3:\n\t"
      "movl %%eax, %%ecx\n\t"
      "pushl $0x25c\n\t"
      "shll $4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal 0x1c(%%ecx,%%ebx,1), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0, 0x8(%%esi)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "je .Lweather_particle_system_render_37\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x94(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[ca4a00]\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "leal -0x230(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "call *%[ca48c0]\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1e0(%%ebp), %%edi\n\t"
      "movl $0x506550, %%esi\n\t"
      "call *%[ca4000]\n\t"
      "flds 0x506550\n\t"
      "fsubs -0x1e0(%%ebp)\n\t"
      "addl $0x10, %%esp\n\t"
      "leal -0x4dc(%%ebp), %%ecx\n\t"
      "leal -0x22c(%%ebp), %%eax\n\t"
      "fstps -0x1e0(%%ebp)\n\t"
      "movl $5, %%edx\n\t"
      "flds 0x506554\n\t"
      "fsubs -0x1dc(%%ebp)\n\t"
      "fstps -0x1dc(%%ebp)\n\t"
      "flds 0x506558\n\t"
      "fsubs -0x1d8(%%ebp)\n\t"
      "fstps -0x1d8(%%ebp)\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lweather_particle_system_render_4:\n\t"
      "flds -0x1d8(%%ebp)\n\t"
      "addl $0x10, %%eax\n\t"
      "fmuls -0xc(%%eax)\n\t"
      "addl $4, %%ecx\n\t"
      "decl %%edx\n\t"
      "flds -0x1e0(%%ebp)\n\t"
      "fmuls -0x14(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x1dc(%%ebp)\n\t"
      "fmuls -0x10(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x4(%%ecx)\n\t"
      "jne .Lweather_particle_system_render_4\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "flds 0x4(%%eax)\n\t"
      "movl -0x1dc(%%ebp), %%edx\n\t"
      "flds -0x1e0(%%ebp)\n\t"
      "movl -0x1e0(%%ebp), %%ecx\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%ecx, -0x58(%%ebp)\n\t"
      "movl -0x1d8(%%ebp), %%ecx\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "flds -0x1dc(%%ebp)\n\t"
      "movl $1, %%ebx\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "movl %%ecx, -0x48(%%ebp)\n\t"
      "movl $0, -0x3c(%%ebp)\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "flds -0x1d8(%%ebp)\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x4(%%eax)\n\t"
      "xorl %%eax, %%eax\n\t"
      "fchs\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      ".Lweather_particle_system_render_5:\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      ".Lweather_particle_system_render_6:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "leal -0x40(%%ebp), %%edi\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lweather_particle_system_render_7:\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .Lweather_particle_system_render_8\n\t"
      "cmpw %%ax, %%si\n\t"
      "jne .Lweather_particle_system_render_8\n\t"
      "cmpw %%ax, %%cx\n\t"
      "je .Lweather_particle_system_render_12\n\t"
      ".Lweather_particle_system_render_8:\n\t"
      "movl (%%edi), %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "movswl %%si, %%ecx\n\t"
      "flds -0x40(%%ebp,%%eax,4)\n\t"
      "movl %%edx, -0x7c(%%ebp)\n\t"
      "pushl $1\n\t"
      "flds -0x40(%%ebp,%%ecx,4)\n\t"
      "leal -0x78(%%ebp), %%eax\n\t"
      "fld %%st(1)\n\t"
      "pushl %%eax\n\t"
      "fadds -0x58(%%ebp)\n\t"
      "pushl $0x5065a4\n\t"
      "fstps -0x78(%%ebp)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps -0x70(%%ebp)\n\t"
      "flds -0x7c(%%ebp)\n\t"
      "fadds -0x48(%%ebp)\n\t"
      "fstps -0x68(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fadds -0x54(%%ebp)\n\t"
      "fstps -0x74(%%ebp)\n\t"
      "fadds -0x4c(%%ebp)\n\t"
      "fstps -0x6c(%%ebp)\n\t"
      "flds -0x7c(%%ebp)\n\t"
      "fadds -0x44(%%ebp)\n\t"
      "fstps -0x64(%%ebp)\n\t"
      "call *%[c1867f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Lweather_particle_system_render_11\n\t"
      "cmpw $0x1a, %%bx\n\t"
      "jl .Lweather_particle_system_render_9\n\t"
      "pushl $1\n\t"
      "pushl $0x2a1\n\t"
      "pushl $0x26af50\n\t"
      "pushl $0x26b050\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lweather_particle_system_render_9:\n\t"
      "flds -0x70(%%ebp)\n\t"
      "movl -0x78(%%ebp), %%esi\n\t"
      "movswl %%bx, %%edx\n\t"
      "leal (%%edx,%%edx,2), %%eax\n\t"
      "shll $2, %%eax\n\t"
      "leal -0x1e0(%%ebp,%%eax,1), %%ecx\n\t"
      "leal (%%edx,%%edx,4), %%edx\n\t"
      "fstps -0x1dc(%%ebp,%%eax,1)\n\t"
      "movl %%esi, (%%ecx)\n\t"
      "flds -0x68(%%ebp)\n\t"
      "leal -0x4dc(%%ebp,%%edx,4), %%edx\n\t"
      "fstps -0x1d8(%%ebp,%%eax,1)\n\t"
      "leal -0x22c(%%ebp), %%eax\n\t"
      "movl $5, %%esi\n\t"
      ".Lweather_particle_system_render_10:\n\t"
      "flds 0x4(%%eax)\n\t"
      "addl $4, %%edx\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      "addl $0x10, %%eax\n\t"
      "decl %%esi\n\t"
      "flds -0x14(%%eax)\n\t"
      "fmuls (%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fmuls -0x10(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x4(%%edx)\n\t"
      "jne .Lweather_particle_system_render_10\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "incl %%ebx\n\t"
      ".Lweather_particle_system_render_11:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      ".Lweather_particle_system_render_12:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "incl %%ecx\n\t"
      "addl $4, %%edi\n\t"
      "cmpw $3, %%cx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jl .Lweather_particle_system_render_7\n\t"
      "incl %%esi\n\t"
      "cmpw $3, %%si\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "jl .Lweather_particle_system_render_6\n\t"
      "incl %%eax\n\t"
      "cmpw $3, %%ax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jl .Lweather_particle_system_render_5\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl 0x1a0(%%eax), %%edx\n\t"
      "pushl $0\n\t"
      "leal 0x1a8(%%eax), %%ecx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x8(%%eax), %%cx\n\t"
      "pushl %%edx\n\t"
      "leal -0x2d4(%%ebp), %%edx\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c18d2c0]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lweather_particle_system_render_36\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lweather_particle_system_render_13:\n\t"
      "movl 0x5aa89c, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "leal -0xa8(%%ebp), %%ecx\n\t"
      "leal -0x22c(%%ebp), %%eax\n\t"
      "movl $5, %%edx\n\t"
      ".Lweather_particle_system_render_14:\n\t"
      "flds -0x4(%%eax)\n\t"
      "addl $0x10, %%eax\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      "addl $4, %%ecx\n\t"
      "decl %%edx\n\t"
      "flds -0xc(%%eax)\n\t"
      "fmuls 0xc(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x10(%%eax)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs -0x8(%%eax)\n\t"
      "fstps -0x4(%%ecx)\n\t"
      "jne .Lweather_particle_system_render_14\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpw %%si, -0xc(%%ebp)\n\t"
      "jle .Lweather_particle_system_render_35\n\t"
      ".Lweather_particle_system_render_15:\n\t"
      "movb $1, %%al\n\t"
      "xorl %%edx, %%edx\n\t"
      ".Lweather_particle_system_render_16:\n\t"
      "testb %%al, %%al\n\t"
      "je .Lweather_particle_system_render_19\n\t"
      "movswl %%dx, %%ecx\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%ecx,%%eax,4), %%edi\n\t"
      "addl %%edi, %%eax\n\t"
      "flds -0x4dc(%%ebp,%%eax,4)\n\t"
      "fadds -0xa8(%%ebp,%%ecx,4)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lweather_particle_system_render_17\n\t"
      "movb $1, %%al\n\t"
      "jmp .Lweather_particle_system_render_18\n\t"
      ".Lweather_particle_system_render_17:\n\t"
      "xorb %%al, %%al\n\t"
      ".Lweather_particle_system_render_18:\n\t"
      "incl %%edx\n\t"
      "cmpw $5, %%dx\n\t"
      "jl .Lweather_particle_system_render_16\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lweather_particle_system_render_20\n\t"
      ".Lweather_particle_system_render_19:\n\t"
      "incl %%esi\n\t"
      "cmpw -0xc(%%ebp), %%si\n\t"
      "jl .Lweather_particle_system_render_15\n\t"
      "jmp .Lweather_particle_system_render_35\n\t"
      ".Lweather_particle_system_render_20:\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "leal -0x1e0(%%ebp,%%ecx,4), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Lweather_particle_system_render_35\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "flds 0x30(%%edx)\n\t"
      "fcomps -0x18(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lweather_particle_system_render_21\n\t"
      "flds -0x18(%%ebp)\n\t"
      "jmp .Lweather_particle_system_render_22\n\t"
      ".Lweather_particle_system_render_21:\n\t"
      "flds 0x30(%%edx)\n\t"
      ".Lweather_particle_system_render_22:\n\t"
      "flds (%%ecx)\n\t"
      "fadds 0x4(%%ebx)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fadds 0x8(%%ebx)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fadds 0xc(%%ebx)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fsubs 0x506550\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fsubs 0x506554\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fsubs 0x506558\n\t"
      "fmuls 0x506564\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x506560\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x50655c\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fcomps 0x24(%%edx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lweather_particle_system_render_34\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lweather_particle_system_render_34\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fsubs 0x24(%%edx)\n\t"
      "flds 0x28(%%edx)\n\t"
      "fsubs 0x24(%%edx)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lweather_particle_system_render_23\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      "jmp .Lweather_particle_system_render_25\n\t"
      ".Lweather_particle_system_render_23:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lweather_particle_system_render_24\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, -0x1c(%%ebp)\n\t"
      "jmp .Lweather_particle_system_render_25\n\t"
      ".Lweather_particle_system_render_24:\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      ".Lweather_particle_system_render_25:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fsubs 0x2c(%%edx)\n\t"
      "fxch %%st(1)\n\t"
      "fsubs 0x2c(%%edx)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lweather_particle_system_render_26\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lweather_particle_system_render_27\n\t"
      ".Lweather_particle_system_render_26:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lweather_particle_system_render_27\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".Lweather_particle_system_render_27:\n\t"
      "cmpw $0, -0x2c(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "jle .Lweather_particle_system_render_31\n\t"
      "jmp .Lweather_particle_system_render_28\n\t"
      "leal (%%esp), %%esp\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lweather_particle_system_render_28:\n\t"
      "movswl -0x8(%%ebp), %%edx\n\t"
      "movswl -0x94(%%ebp,%%edx,2), %%eax\n\t"
      "pushl $0x20\n\t"
      "pushl %%eax\n\t"
      "movl -0x5c(%%ebp), %%eax\n\t"
      "addl $0x1c0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "leal 0x14(%%eax), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .Lweather_particle_system_render_30\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lweather_particle_system_render_29:\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "addl $0xc, %%esp\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0xc(%%eax)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lweather_particle_system_render_30\n\t"
      "movl (%%esi), %%ecx\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lweather_particle_system_render_29\n\t"
      ".Lweather_particle_system_render_30:\n\t"
      "movl (%%esi), %%eax\n\t"
      "movswl %%di, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .Lweather_particle_system_render_35\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw -0x2c(%%ebp), %%ax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jl .Lweather_particle_system_render_28\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      ".Lweather_particle_system_render_31:\n\t"
      "cmpw $1, 0x1a6(%%edx)\n\t"
      "leal 0x1c(%%ebx), %%ecx\n\t"
      "je .Lweather_particle_system_render_32\n\t"
      "leal 0x10(%%ebx), %%ecx\n\t"
      ".Lweather_particle_system_render_32:\n\t"
      "movw 0x1a4(%%edx), %%si\n\t"
      "testw %%si, %%si\n\t"
      "je .Lweather_particle_system_render_33\n\t"
      "flds 0x8(%%ecx)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "flds (%%ecx)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x2533c0\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x44, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jp .Lweather_particle_system_render_33\n\t"
      "movl 0x31fc44, %%ecx\n\t"
      ".Lweather_particle_system_render_33:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "pushl $0\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "leal 0x34(%%ebx), %%eax\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "flds 0x44(%%ebx)\n\t"
      "pushl %%ecx\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "fmuls 0x154(%%edx)\n\t"
      "movl 0x30(%%ebx), %%edx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edx\n\t"
      "flds 0x2c(%%ebx)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[ftol]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x28(%%ebx), %%cx\n\t"
      "leal -0x2d4(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c18d6e0]\n\t"
      "addl $0x2c, %%esp\n\t"
      "jmp .Lweather_particle_system_render_35\n\t"
      ".Lweather_particle_system_render_34:\n\t"
      "fstp %%st(0)\n\t"
      ".Lweather_particle_system_render_35:\n\t"
      "movl 0x50(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lweather_particle_system_render_13\n\t"
      ".Lweather_particle_system_render_36:\n\t"
      "leal -0x2d4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c18d360]\n\t"
      "movl -0x60(%%ebp), %%ebx\n\t"
      "movl -0x34(%%ebp), %%edi\n\t"
      "addl $4, %%esp\n\t"
      ".Lweather_particle_system_render_37:\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "movl (%%edi), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lweather_particle_system_render_3\n\t"
      ".Lweather_particle_system_render_38:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
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
      "nop\n\t"
      "nop\n\t"
      :
      : [assert] "m"(ba4e20_assert), [exitfn] "m"(ba4e20_exitfn), [tag] "m"(ba4e20_tag), [c18e3c0] "m"(ba4e20_c18e3c0), [ca4be0] "m"(ba4e20_ca4be0), [elem] "m"(ba4e20_elem), [ca4a00] "m"(ba4e20_ca4a00), [ca48c0] "m"(ba4e20_ca48c0), [ca4000] "m"(ba4e20_ca4000), [c1867f0] "m"(ba4e20_c1867f0), [c18d2c0] "m"(ba4e20_c18d2c0), [dget] "m"(ba4e20_dget), [ftol] "m"(ba4e20_ftol), [c18d6e0] "m"(ba4e20_c18d6e0), [c18d360] "m"(ba4e20_c18d360)
      : "memory");
}
#else
#error "weather_particle_system_render: clang naked draft required"
#endif



