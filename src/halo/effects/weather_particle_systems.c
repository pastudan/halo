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

/* FUN_000a3e60 (0xa3e60) — XBE naked draft (batch 173). */
#if defined(__clang__)
static void (*const ba3e60_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const ba3e60_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_000a3e60(void)
{
  __asm__ volatile(
      "testw %%si, %%si\n\t"
      "jl .LFUN_000a3e60_1\n\t"
      "cmpw $4, %%si\n\t"
      "jl .LFUN_000a3e60_2\n\t"
      ".LFUN_000a3e60_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x5b\n\t"
      "pushl $0x26af50\n\t"
      "pushl $0x266fc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000a3e60_2:\n\t"
      "movswl %%si, %%eax\n\t"
      "imull $0x9c, %%eax, %%eax\n\t"
      "addl $0x4557f4, %%eax\n\t"
      "ret\n\t"
      :
      : [assert] "m"(ba3e60_assert), [exitfn] "m"(ba3e60_exitfn)
      : "memory");
}
#else
#error "FUN_000a3e60: clang naked draft required"
#endif


/* FUN_000a3ea0 (0xa3ea0) — XBE naked draft (batch 177). */
#if defined(__clang__)
static void *(*const ba3ea0_tag)(int, int) = tag_get;
static void (*const ba3ea0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const ba3ea0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_000a3ea0(void)
{
  __asm__ volatile(
      "movl (%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x7261696e\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_000a3ea0_1\n\t"
      "movl 0x24(%%eax), %%edx\n\t"
      "movswl %%si, %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jl .LFUN_000a3ea0_2\n\t"
      ".LFUN_000a3ea0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x66\n\t"
      "pushl $0x26af50\n\t"
      "pushl $0x26af84\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000a3ea0_2:\n\t"
      "movswl %%si, %%edx\n\t"
      "shll $4, %%edx\n\t"
      "leal 0x1c(%%edx,%%edi,1), %%eax\n\t"
      "ret\n\t"
      :
      : [tag] "m"(ba3ea0_tag), [assert] "m"(ba3ea0_assert), [exitfn] "m"(ba3ea0_exitfn)
      : "memory");
}
#else
#error "FUN_000a3ea0: clang naked draft required"
#endif


/* FUN_000a4000 (0xa4000) — XBE naked draft (batch 149). */
#if defined(__clang__)
static void (*const ba4000_c1daf7e)(void) = FUN_001daf7e;

__attribute__((naked, noinline))
void FUN_000a4000(float *dst __attribute__((unused)), float *src __attribute__((unused)), float scale __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000a4000_1\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .LFUN_000a4000_2\n\t"
      ".LFUN_000a4000_1:\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      ".LFUN_000a4000_2:\n\t"
      "flds (%%esi)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "call *%[c1daf7e]\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fstps (%%edi)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000a4000_3\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jmp .LFUN_000a4000_4\n\t"
      ".LFUN_000a4000_3:\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      ".LFUN_000a4000_4:\n\t"
      "flds 0x4(%%esi)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "call *%[c1daf7e]\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fstps 0x4(%%edi)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000a4000_5\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jmp .LFUN_000a4000_6\n\t"
      ".LFUN_000a4000_5:\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      ".LFUN_000a4000_6:\n\t"
      "flds 0x8(%%esi)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "call *%[c1daf7e]\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fstps 0x8(%%edi)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1daf7e] "m"(ba4000_c1daf7e)
      : "memory");
}
#else
#error "FUN_000a4000: clang naked draft required"
#endif


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


/* weather_particle_system_delete (0xa4200) — XBE naked draft (batch 131). */
#if defined(__clang__)
static void (*const ba4200_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const ba4200_exitfn)(int) = system_exit;
static void *(*const ba4200_tag)(int, int) = tag_get;
static void *(*const ba4200_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const ba4200_c1196d0)(data_t *data, int datum_handle) = datum_delete;

__attribute__((naked, noinline))
void weather_particle_system_delete(void)
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
      "jl .Lweather_particle_system_delete_1\n\t"
      "cmpw $4, %%si\n\t"
      "jl .Lweather_particle_system_delete_2\n\t"
      ".Lweather_particle_system_delete_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x5b\n\t"
      "pushl $0x26af50\n\t"
      "pushl $0x266fc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lweather_particle_system_delete_2:\n\t"
      "movswl %%si, %%edi\n\t"
      "imull $0x9c, %%edi, %%edi\n\t"
      "addl $0x4557f4, %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x7261696e\n\t"
      "call *%[tag]\n\t"
      "movl 0x24(%%eax), %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%ebx, 0x8(%%ebp)\n\t"
      "jle .Lweather_particle_system_delete_8\n\t"
      "xorl %%esi, %%esi\n\t"
      ".Lweather_particle_system_delete_3:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x7261696e\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .Lweather_particle_system_delete_4\n\t"
      "cmpl 0x24(%%eax), %%esi\n\t"
      "jl .Lweather_particle_system_delete_5\n\t"
      ".Lweather_particle_system_delete_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x66\n\t"
      "pushl $0x26af50\n\t"
      "pushl $0x26af84\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lweather_particle_system_delete_5:\n\t"
      "shll $4, %%esi\n\t"
      "movl 0x28(%%esi,%%edi,1), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "leal 0x1c(%%esi,%%edi,1), %%esi\n\t"
      "je .Lweather_particle_system_delete_7\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lweather_particle_system_delete_6:\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "movl 0x5aa89c, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "movl 0x5aa89c, %%edx\n\t"
      "movl 0x50(%%eax), %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1196d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "decw 0x8(%%esi)\n\t"
      "movl %%ebx, %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%ebx, 0xc(%%esi)\n\t"
      "jne .Lweather_particle_system_delete_6\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      ".Lweather_particle_system_delete_7:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x24(%%eax), %%ecx\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%esi\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "movl %%ebx, 0x8(%%ebp)\n\t"
      "jl .Lweather_particle_system_delete_3\n\t"
      ".Lweather_particle_system_delete_8:\n\t"
      "decw 0x4557f0\n\t"
      "movl $0xffffffff, (%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(ba4200_assert), [exitfn] "m"(ba4200_exitfn), [tag] "m"(ba4200_tag), [dget] "m"(ba4200_dget), [c1196d0] "m"(ba4200_c1196d0)
      : "memory");
}
#else
#error "weather_particle_system_delete: clang naked draft required"
#endif


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


/* FUN_000a45d0 (0xa45d0) — XBE naked draft (batch 174). */
#if defined(__clang__)
static void (*const ba45d0_ca4000)(float *dst, float *src, float scale) = FUN_000a4000;

__attribute__((naked, noinline))
void FUN_000a45d0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%ecx, %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[ca4000]\n\t"
      "flds (%%esi)\n\t"
      "fsubs (%%edi)\n\t"
      "addl $4, %%esp\n\t"
      "fstps (%%edi)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "fstps 0x4(%%edi)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "fstps 0x8(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [ca4000] "m"(ba45d0_ca4000)
      : "memory");
}
#else
#error "FUN_000a45d0: clang naked draft required"
#endif


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


/* FUN_000a48c0 (0xa48c0) — XBE naked draft (batch 130). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_000a48c0(float *out __attribute__((unused)), float scale __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "flds 0x50655c\n\t"
      "leal 0x40(%%ecx), %%eax\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "movl %%eax, %%edx\n\t"
      "pushl %%esi\n\t"
      "movl 0x50655c, %%esi\n\t"
      "fadds 0x506550\n\t"
      "flds 0x506560\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fadds 0x506554\n\t"
      "flds 0x506564\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fadds 0x506558\n\t"
      "movl %%esi, (%%edx)\n\t"
      "movl 0x506560, %%esi\n\t"
      "movl %%esi, 0x4(%%edx)\n\t"
      "movl 0x506564, %%esi\n\t"
      "movl %%esi, 0x8(%%edx)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "fxch %%st(1)\n\t"
      "popl %%esi\n\t"
      "fmuls 0x4(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fxch %%st(1)\n\t"
      "fmuls (%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps 0xc(%%eax)\n\t"
      "movl 0x50661c, %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x506620, %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x506624, %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movl 0x506628, %%edx\n\t"
      "movl %%edx, 0xc(%%eax)\n\t"
      "movl 0x50662c, %%edx\n\t"
      "leal 0x10(%%ecx), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x506630, %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x506634, %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movl 0x506638, %%edx\n\t"
      "movl %%edx, 0xc(%%eax)\n\t"
      "movl 0x50663c, %%edx\n\t"
      "leal 0x20(%%ecx), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x506640, %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x506644, %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movl 0x506648, %%edx\n\t"
      "movl %%edx, 0xc(%%eax)\n\t"
      "movl 0x50664c, %%eax\n\t"
      "addl $0x30, %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x506650, %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x506654, %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movl 0x506658, %%edx\n\t"
      "movl %%edx, 0xc(%%ecx)\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_000a48c0: clang naked draft required"
#endif


/* FUN_000a4a00 (0xa4a00) — XBE naked draft (batch 140). */
#if defined(__clang__)
static void * (*const ba4a00_c18e3c0)(void) = scenario_get;
static void *(*const ba4a00_elem)(void *, int, int) = tag_block_get_element;
static void (*const ba4a00_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
int FUN_000a4a00(void *out_buf __attribute__((unused)), int particle_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c18e3c0]\n\t"
      "leal 0x1c0(%%eax), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_000a4a00_4\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_000a4a00_1:\n\t"
      "pushl $0x20\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "flds (%%eax)\n\t"
      "fsubs 0x506550\n\t"
      "addl $0xc, %%esp\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x506554\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs 0x506558\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fadds 0xc(%%eax)\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fcompp\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jne .LFUN_000a4a00_3\n\t"
      "cmpw $8, %%bx\n\t"
      "jge .LFUN_000a4a00_2\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movswl %%bx, %%eax\n\t"
      "movw %%di, (%%ecx,%%eax,2)\n\t"
      "incl %%ebx\n\t"
      "jmp .LFUN_000a4a00_3\n\t"
      ".LFUN_000a4a00_2:\n\t"
      "pushl $0x26b02c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000a4a00_3:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_000a4a00_1\n\t"
      ".LFUN_000a4a00_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%bx, %%ax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e3c0] "m"(ba4a00_c18e3c0), [elem] "m"(ba4a00_elem), [c8f390] "m"(ba4a00_c8f390)
      : "memory");
}
#else
#error "FUN_000a4a00: clang naked draft required"
#endif


/* FUN_000a4ab0 (0xa4ab0) — XBE naked draft (batch 127). */
#if defined(__clang__)
static void (*const ba4ab0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const ba4ab0_exitfn)(int) = system_exit;
static void *(*const ba4ab0_tag)(int, int) = tag_get;
static void (*const ba4ab0_ftol)(void) = FUN_001d9068;
static void (*const ba4ab0_ca4310)(void) = FUN_000a4310;
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


