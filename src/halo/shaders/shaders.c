void numeric_countdown_timer_update(void)
{
  int current_time;

  current_time = *(int *)0x4d8a80;
  if (*(char *)0x4d8a7c) {
    current_time = (game_time_get() * 1000) / 30;
    if (*(int *)0x4d8a80 <= current_time) {
      *(int *)0x4d8a78 += *(int *)0x4d8a80 - current_time;
      if (*(int *)0x4d8a78 < 0)
        *(int *)0x4d8a78 = 0;
    }
  }
  *(int *)0x4d8a80 = current_time;
}
/* --- shaders.obj batch drafts (2026-07-26) --- */

/* 0x190240 */
char FUN_00190240(float *position, float *wind_out, int wind_flags, int object_handle)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;

  (void)position;
  (void)wind_out;
  (void)wind_flags;
  (void)object_handle;
  /* relift: cmp (int16_t)eax, word ptr [0x5060c4] -> jge 0x190358 */
  /* relift: cmp byte ptr [esi], 0 -> je 0x19033a */
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_get('dniw', 0);
  FUN_0018ff00((float *)(uintptr_t)edx, (float *)0, 0.0f, 0.0f);

  (void)eax;
  (void)edx;
  (void)esi;
  return 0;

}

/* 0x190380 */
void FUN_00190380(void)
{
  int eax = 0;

  get_global_random_seed_address();
  random_seed_get_direction3d((void *)(uintptr_t)eax, (float *)0);
  FUN_00089a20();

  (void)eax;
}

/* 0x190500 */
void wind_initialize_for_new_map(void)
{
  int eax = 0;

  scenario_get();
  /* test (char)eax, (char)eax -> je 0x19052b */
  display_assert((char *)0x002b22e0, (char *)0x002b22c0, 65, 0);
  system_exit(0);
  csmemset((void *)0x005057c0, 0, 3340);

  (void)eax;
}

/* 0x190550 */
char FUN_00190550(int *collision_location, float *position, float *wind_out, int flags)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  (void)collision_location;
  (void)position;
  (void)wind_out;
  (void)flags;
  scenario_get();
  FUN_0018f2d0((void *)(uintptr_t)edi, (void *)(uintptr_t)eax);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 104);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 40);
  /* cmp (int16_t)eax, 0xffff -> je 0x19063f */
  /* relift: cmp word ptr [edi + 0x26], -1 -> je 0x19063f */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 0);
  /* cmp eax, -1 -> je 0x19063f */
  tag_get(' gof', 0);
  /* test (char)ecx, 1 -> je 0x190630 */
  /* relift: test byte ptr [ebp + 0x14], 8 -> jne 0x19063f */
  /* test eax, eax -> jne 0x19063f */
  FUN_00190240((float *)0, (float *)0, 0, 0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
  return 0;
}

/* 0x190670 */
void FUN_00190670(void)
{
  FUN_00190550((int *)0, (float *)0, (float *)0, 0);
}

/* 0x190690 */
void FUN_00190690(void)
{
  FUN_00190550((int *)0, (float *)0, (float *)0, 0);
}

/* 0x1906b0 */
void *FUN_001906b0(void *shader, int shader_type)
{
  int esi = 0;
  int ebp = 0;

  /* test esi, esi -> jne 0x1906db */
  display_assert((char *)0x002a18b8, (char *)0x002b231c, 2140, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [ebp + 0xc] -> je 0x190705 */
  display_assert((char *)0x002b22fc, (char *)0x002b231c, 2141, 0);
  system_exit(0);
  return NULL;

  (void)esi;
  (void)ebp;
}

/* 0x190710 */
int shader_get_vertex_shader_permutation(void *shader)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x19073b */
  display_assert((char *)0x002a18b8, (char *)0x002b2348, 20, 0);
  system_exit(0);
  /* cmp edi, -1 -> je 0x190807 */
  /* cmp eax, 5 -> ja 0x190807 */
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  /* test (char)eax, 0x41 -> jne 0x190807 */
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  /* cmp ecx, -1 -> je 0x190807 */
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  /* cmp (int16_t)esi, 1 -> jne 0x1907f6 */
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  /* cmp (int16_t)esi, 1 -> jne 0x1907f6 */
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  /* test (char)ecx, 8 -> jne 0x1907f6 */
  /* relift: test byte ptr [edi], 4 -> je 0x190809 */
  return 0;

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x190830 */
void shader_is_mirror(void)
{
  int ecx = 0;
  int edx = 0;

  /* test ecx, ecx -> je 0x190874 */
  /* cmp edx, 3 -> je 0x190861 */
  /* cmp edx, 8 -> jne 0x190874 */
  FUN_001906b0((void *)(uintptr_t)ecx, 0);
  FUN_001906b0((void *)(uintptr_t)ecx, 0);

  (void)ecx;
  (void)edx;
}

/* 0x1908a0 */
char shader_is_decal(void *shader)
{
  int ecx = 0;
  int edx = 0;

  /* test ecx, ecx -> je 0x19090b */
  /* cmp edx, 4 -> ja 0x19090b */
  FUN_001906b0((void *)(uintptr_t)ecx, 0);
  FUN_001906b0((void *)(uintptr_t)ecx, 0);
  FUN_001906b0((void *)(uintptr_t)ecx, 0);
  FUN_001906b0((void *)(uintptr_t)ecx, 0);
  return 0;

  (void)ecx;
  (void)edx;
}

/* 0x190930 */
char shader_is_water_decal(void *shader)
{
  int ecx = 0;

  /* test ecx, ecx -> je 0x190970 */
  FUN_001906b0((void *)(uintptr_t)ecx, 0);
  FUN_001906b0((void *)(uintptr_t)ecx, 0);
  return 0;

  (void)ecx;
}

/* 0x190980 */
char shader_ignores_effect(void *shader)
{
  int ecx = 0;

  /* test ecx, ecx -> je 0x1909c0 */
  FUN_001906b0((void *)(uintptr_t)ecx, 0);
  FUN_001906b0((void *)(uintptr_t)ecx, 0);
  return 0;

  (void)ecx;
}

/* 0x1909d0 */
char shader_type_is_transparent(int16_t shader_type)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x1909f0 */
void shader_type_is_lightmapped(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x190a10 */
void shader_type_is_vertex_lit(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x190a30 */
void shader_type_is_valid_for_environment(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x190a50 */
void shader_type_is_valid_for_model(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x190a70 */
char shader_type_is_valid_for_modifier(int16_t shader_type)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x190a90 */
void shader_environment_texture_animation_evaluate(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x002a18b8, (char *)0x002b2348, 345, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x190ae4 */
  display_assert((char *)0x002b23c0, (char *)0x002b2348, 346, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x190b0b */
  display_assert((char *)0x002b23b4, (char *)0x002b2348, 347, 0);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)esi, 0);
  display_assert((char *)0x002b2390, (char *)0x002b2348, 352, 0);
  system_exit(0);
  display_assert((char *)0x002b236c, (char *)0x002b2348, 353, 0);
  system_exit(0);
  FUN_0010a5e0(eax, 0.0f);
  FUN_0010a5e0(ecx, 0.0f);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x190be0 */
void numeric_countdown_timer_set(int a0, int a1)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* numeric_countdown_timer_get (0x190c00) — XBE naked draft (batch 243). */
#if defined(__clang__)


__attribute__((naked, noinline))
int numeric_countdown_timer_get(int a0 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "incl %%eax\n\t"
      "cmpl $9, %%eax\n\t"
      "ja .Lnumeric_countdown_timer_get_11\n\t"
      "jmp *.Lnumeric_countdown_timer_get_jt(,%%eax,4)\n\t"
      ".Lnumeric_countdown_timer_get_1:\n\t"
      "movl 0x4d8a78, %%edx\n\t"
      "movw %%dx, %%ax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnumeric_countdown_timer_get_2:\n\t"
      "movl 0x4d8a78, %%eax\n\t"
      "cdq\n\t"
      "movl $0xa, %%ecx\n\t"
      "idivl %%ecx\n\t"
      "movw %%dx, %%ax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnumeric_countdown_timer_get_3:\n\t"
      "movl 0x4d8a78, %%ecx\n\t"
      "movl $0x66666667, %%eax\n\t"
      "imull %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "sarl $2, %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "shrl $0x1f, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "cdq\n\t"
      "movl $0xa, %%ecx\n\t"
      "idivl %%ecx\n\t"
      "movw %%dx, %%ax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnumeric_countdown_timer_get_4:\n\t"
      "movl 0x4d8a78, %%ecx\n\t"
      "movl $0x51eb851f, %%eax\n\t"
      "imull %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "sarl $5, %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "shrl $0x1f, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "cdq\n\t"
      "movl $0xa, %%ecx\n\t"
      "idivl %%ecx\n\t"
      "movw %%dx, %%ax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnumeric_countdown_timer_get_5:\n\t"
      "movl 0x4d8a78, %%ecx\n\t"
      "movl $0x10624dd3, %%eax\n\t"
      "imull %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "sarl $6, %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "shrl $0x1f, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "cdq\n\t"
      "movl $0xa, %%ecx\n\t"
      "idivl %%ecx\n\t"
      "movw %%dx, %%ax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnumeric_countdown_timer_get_6:\n\t"
      "movl 0x4d8a78, %%ecx\n\t"
      "movl $0x68db8bad, %%eax\n\t"
      "imull %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "sarl $0xc, %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "shrl $0x1f, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "cdq\n\t"
      "movl $6, %%ecx\n\t"
      "idivl %%ecx\n\t"
      "movw %%dx, %%ax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnumeric_countdown_timer_get_7:\n\t"
      "movl 0x4d8a78, %%ecx\n\t"
      "movl $0x45e7b273, %%eax\n\t"
      "imull %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "sarl $0xe, %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "shrl $0x1f, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "cdq\n\t"
      "movl $0xa, %%ecx\n\t"
      "idivl %%ecx\n\t"
      "movw %%dx, %%ax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnumeric_countdown_timer_get_8:\n\t"
      "movl 0x4d8a78, %%ecx\n\t"
      "movl $0x6fd91d85, %%eax\n\t"
      "imull %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "sarl $0x12, %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "shrl $0x1f, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "cdq\n\t"
      "movl $6, %%ecx\n\t"
      "idivl %%ecx\n\t"
      "movw %%dx, %%ax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnumeric_countdown_timer_get_9:\n\t"
      "movl 0x4d8a78, %%ecx\n\t"
      "movl $0x4a90be59, %%eax\n\t"
      "imull %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "sarl $0x14, %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "shrl $0x1f, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "cdq\n\t"
      "movl $0xa, %%ecx\n\t"
      "idivl %%ecx\n\t"
      "movw %%dx, %%ax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnumeric_countdown_timer_get_10:\n\t"
      "movl 0x4d8a78, %%ecx\n\t"
      "movl $0x774dfd5b, %%eax\n\t"
      "imull %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "sarl $0x18, %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "shrl $0x1f, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "cdq\n\t"
      "movl $0xa, %%ecx\n\t"
      "idivl %%ecx\n\t"
      ".Lnumeric_countdown_timer_get_11:\n\t"
      "movw %%dx, %%ax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lnumeric_countdown_timer_get_jt:\n\t"
      ".long .Lnumeric_countdown_timer_get_1\n\t"
      ".long .Lnumeric_countdown_timer_get_2\n\t"
      ".long .Lnumeric_countdown_timer_get_3\n\t"
      ".long .Lnumeric_countdown_timer_get_4\n\t"
      ".long .Lnumeric_countdown_timer_get_5\n\t"
      ".long .Lnumeric_countdown_timer_get_6\n\t"
      ".long .Lnumeric_countdown_timer_get_7\n\t"
      ".long .Lnumeric_countdown_timer_get_8\n\t"
      ".long .Lnumeric_countdown_timer_get_9\n\t"
      ".long .Lnumeric_countdown_timer_get_10\n\t"
      ".text\n\t"
      :
      :
      : "memory");
}
#else
#error "numeric_countdown_timer_get: clang naked draft required"
#endif


/* 0x190d90 */
void numeric_countdown_timer_stop(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x190da0 */
void numeric_countdown_timer_restart(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_00190e10 (0x190e10) — XBE naked draft (batch 243). */
#if defined(__clang__)
static void (*const b190e10_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b190e10_exitfn)(int) = system_exit;
static float (*const b190e10_c10a5e0)(int16_t function_type, float input) = FUN_0010a5e0;

__attribute__((naked, noinline))
void FUN_00190e10(void *map_animation __attribute__((unused)), void *external_animation __attribute__((unused)), float u_scale __attribute__((unused)), float v_scale __attribute__((unused)), float u_offset __attribute__((unused)), float v_offset __attribute__((unused)), float rotation __attribute__((unused)), float time __attribute__((unused)), float *out_u __attribute__((unused)), float *out_v __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_00190e10_1\n\t"
      "pushl $1\n\t"
      "pushl $0x113\n\t"
      "pushl $0x2b2348\n\t"
      "pushl $0x2b2534\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00190e10_1:\n\t"
      "movw (%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00190e10_2\n\t"
      "cmpw $5, %%ax\n\t"
      "jl .LFUN_00190e10_3\n\t"
      ".LFUN_00190e10_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x114\n\t"
      "pushl $0x2b2348\n\t"
      "pushl $0x2b24d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00190e10_3:\n\t"
      "movw 0x10(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00190e10_4\n\t"
      "cmpw $5, %%ax\n\t"
      "jl .LFUN_00190e10_5\n\t"
      ".LFUN_00190e10_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x115\n\t"
      "pushl $0x2b2348\n\t"
      "pushl $0x2b2468\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00190e10_5:\n\t"
      "movw 0x20(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00190e10_6\n\t"
      "cmpw $5, %%ax\n\t"
      "jl .LFUN_00190e10_7\n\t"
      ".LFUN_00190e10_6:\n\t"
      "pushl $1\n\t"
      "pushl $0x116\n\t"
      "pushl $0x2b2348\n\t"
      "pushl $0x2b2400\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00190e10_7:\n\t"
      "movl 0x28(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .LFUN_00190e10_8\n\t"
      "pushl $1\n\t"
      "pushl $0x117\n\t"
      "pushl $0x2b2348\n\t"
      "pushl $0x2b23e4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00190e10_8:\n\t"
      "movl 0x2c(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00190e10_9\n\t"
      "pushl $1\n\t"
      "pushl $0x118\n\t"
      "pushl $0x2b2348\n\t"
      "pushl $0x2b23cc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00190e10_9:\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00190e10_10\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LFUN_00190e10_11\n\t"
      ".LFUN_00190e10_10:\n\t"
      "flds 0x4(%%esi)\n\t"
      ".LFUN_00190e10_11:\n\t"
      "flds 0x14(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00190e10_12\n\t"
      "movl $0x3f800000, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00190e10_13\n\t"
      ".LFUN_00190e10_12:\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".LFUN_00190e10_13:\n\t"
      "flds 0x24(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00190e10_14\n\t"
      "movl $0x3f800000, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00190e10_15\n\t"
      ".LFUN_00190e10_14:\n\t"
      "movl 0x24(%%esi), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      ".LFUN_00190e10_15:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00190e10_20\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movw (%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_00190e10_16\n\t"
      "movl $0x3f800000, 0x28(%%ebp)\n\t"
      "jmp .LFUN_00190e10_17\n\t"
      ".LFUN_00190e10_16:\n\t"
      "movswl %%ax, %%edx\n\t"
      "flds -0x4(%%ecx,%%edx,4)\n\t"
      "fstps 0x28(%%ebp)\n\t"
      ".LFUN_00190e10_17:\n\t"
      "movw 0x10(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_00190e10_18\n\t"
      "movl $0x3f800000, 0x8(%%ebp)\n\t"
      "jmp .LFUN_00190e10_19\n\t"
      ".LFUN_00190e10_18:\n\t"
      "movswl %%ax, %%eax\n\t"
      "flds -0x4(%%ecx,%%eax,4)\n\t"
      "fstps 0x8(%%ebp)\n\t"
      ".LFUN_00190e10_19:\n\t"
      "movw 0x20(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_00190e10_21\n\t"
      "movswl %%ax, %%edx\n\t"
      "flds -0x4(%%ecx,%%edx,4)\n\t"
      "fstps 0x2c(%%ebp)\n\t"
      "jmp .LFUN_00190e10_22\n\t"
      ".LFUN_00190e10_20:\n\t"
      "movl $0x3f800000, 0x8(%%ebp)\n\t"
      "movl $0x3f800000, 0x28(%%ebp)\n\t"
      ".LFUN_00190e10_21:\n\t"
      "movl $0x3f800000, 0x2c(%%ebp)\n\t"
      ".LFUN_00190e10_22:\n\t"
      "flds 0x24(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "fadds 0x8(%%esi)\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "pushl %%ecx\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "fstp %%st(0)\n\t"
      "call *%[c10a5e0]\n\t"
      "fmuls 0xc(%%esi)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x12(%%esi), %%cx\n\t"
      "addl $4, %%esp\n\t"
      "fmuls 0x28(%%ebp)\n\t"
      "fstps 0x28(%%ebp)\n\t"
      "flds 0x24(%%ebp)\n\t"
      "fadds 0x18(%%esi)\n\t"
      "fdivs -0x4(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10a5e0]\n\t"
      "fmuls 0x1c(%%esi)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x22(%%esi), %%dx\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "flds 0x24(%%ebp)\n\t"
      "fadds 0x28(%%esi)\n\t"
      "fdivs -0x8(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edx\n\t"
      "call *%[c10a5e0]\n\t"
      "fmuls 0x2c(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "fmuls 0x2c(%%ebp)\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fsubs 0x30(%%esi)\n\t"
      "fadds 0x28(%%ebp)\n\t"
      "fstps 0x28(%%ebp)\n\t"
      "flds 0x1c(%%ebp)\n\t"
      "fsubs 0x34(%%esi)\n\t"
      "fadds 0x8(%%ebp)\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "fadds 0x20(%%ebp)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00190e10_23\n\t"
      "fmuls 0x253d4c\n\t"
      "fsts 0x24(%%ebp)\n\t"
      "fcos\n\t"
      "flds 0x24(%%ebp)\n\t"
      "fsin\n\t"
      "jmp .LFUN_00190e10_24\n\t"
      ".LFUN_00190e10_23:\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      "flds 0x2533c0\n\t"
      ".LFUN_00190e10_24:\n\t"
      "fld %%st(1)\n\t"
      "xorl %%eax, %%eax\n\t"
      "fmuls 0x10(%%ebp)\n\t"
      "movl %%eax, 0x8(%%ebx)\n\t"
      "fstps (%%ebx)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fchs\n\t"
      "fstps 0x4(%%ebx)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x28(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fadds 0x30(%%esi)\n\t"
      "fstps 0xc(%%ebx)\n\t"
      "movl %%eax, 0x8(%%edi)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps (%%edi)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x14(%%ebp)\n\t"
      "fstps 0x4(%%edi)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x28(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds 0x34(%%esi)\n\t"
      "fstps 0xc(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b190e10_assert), [exitfn] "m"(b190e10_exitfn), [c10a5e0] "m"(b190e10_c10a5e0)
      : "memory");
}
#else
#error "FUN_00190e10: clang naked draft required"
#endif

