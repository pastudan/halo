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


/* FUN_00190380 (0x190380) — XBE naked draft (batch 245). */
#if defined(__clang__)
static int *(*const b190380_gseed)(void) = get_global_random_seed_address;
static void (*const b190380_c10b380)(unsigned int *seed, float *out) = random_seed_get_direction3d;
static void (*const b190380_c89a20)(void) = FUN_00089a20;

__attribute__((naked, noinline))
void FUN_00190380(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x38, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $0x5057c4, %%ebx\n\t"
      "movl $8, -0x10(%%ebp)\n\t"
      ".LFUN_00190380_1:\n\t"
      "movl %%ebx, %%esi\n\t"
      "movl $3, %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00190380_2:\n\t"
      "pushl %%esi\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[c10b380]\n\t"
      "addl $8, %%esp\n\t"
      "addl $0x300, %%esi\n\t"
      "decl %%edi\n\t"
      "jne .LFUN_00190380_2\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $0x60, %%ebx\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jne .LFUN_00190380_1\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "movl $1, %%eax\n\t"
      "movl $0x5057d0, -0x8(%%ebp)\n\t"
      "movl $8, -0x1c(%%ebp)\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00190380_3:\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb %%al, %%cl\n\t"
      "xorl %%edx, %%edx\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "movb %%al, %%dl\n\t"
      "subb $2, %%cl\n\t"
      "movl $1, -0xc(%%ebp)\n\t"
      "andl $7, %%edx\n\t"
      "andl $7, %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "andl $7, %%eax\n\t"
      "movzwl %%ax, %%eax\n\t"
      "decl %%esi\n\t"
      "movl %%esi, -0x18(%%ebp)\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movzwl %%cx, %%eax\n\t"
      "fildl -0x18(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movzwl %%dx, %%edx\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl $7, -0x18(%%ebp)\n\t"
      ".LFUN_00190380_4:\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "xorl %%esi, %%esi\n\t"
      "fmuls 0x268ed0\n\t"
      "addl $-0xc, %%edi\n\t"
      "movl $3, -0x14(%%ebp)\n\t"
      "fadds -0x20(%%ebp)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      ".LFUN_00190380_5:\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movl -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%eax\n\t"
      "leal (%%esi,%%ecx,1), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "shll $5, %%edx\n\t"
      "addl %%esi, %%eax\n\t"
      "addl $0x5057c4, %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0x34(%%ebp), %%edx\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "shll $5, %%ecx\n\t"
      "leal (%%esi,%%edx,1), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "addl $0x5057c4, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "shll $5, %%eax\n\t"
      "pushl %%edi\n\t"
      "addl $0x5057c4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c89a20]\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "addl $0x20, %%esp\n\t"
      "addl $8, %%esi\n\t"
      "addl $0x300, %%edi\n\t"
      "addl $0x300, %%ebx\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jne .LFUN_00190380_5\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "incl %%edx\n\t"
      "addl $0xc, %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "jne .LFUN_00190380_4\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "incl %%esi\n\t"
      "addl $0x60, %%edx\n\t"
      "decl %%ecx\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "jne .LFUN_00190380_3\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [gseed] "m"(b190380_gseed), [c10b380] "m"(b190380_c10b380), [c89a20] "m"(b190380_c89a20)
      : "memory");
}
#else
#error "FUN_00190380: clang naked draft required"
#endif


/* wind_initialize_for_new_map (0x190500) — readable C lift. */
void wind_initialize_for_new_map(void)
{
  scenario_get();
  if (*(unsigned char *)0x5057c0 != 0) {
    display_assert((const char *)0x2b22e0, (const char *)0x2b22c0, 0x41, 1);
    system_exit(-1);
  }
  csmemset((void *)0x5057c0, 0, 0xd0c);
  *(unsigned char *)0x5057c0 = 1;
  FUN_00190380();
}
/* FUN_00190550 (0x190550) — XBE naked draft (batch 253). */
#if defined(__clang__)
static void * (*const b190550_c18e3c0)(void) = scenario_get;
static int16_t (*const b190550_c18f2d0)(void *location, void *position) = FUN_0018f2d0;
static void *(*const b190550_elem)(void *, int, int) = tag_block_get_element;
static void *(*const b190550_tag)(int, int) = tag_get;
static char (*const b190550_c190240)(float *position, float *wind_out, int wind_flags, int object_handle) = FUN_00190240;

__attribute__((naked, noinline))
char FUN_00190550(int *collision_location __attribute__((unused)), float *position __attribute__((unused)), float *wind_out __attribute__((unused)), int flags __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "cmpw %%ax, 0x4(%%edi)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "je .LFUN_00190550_3\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c18e3c0]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "andl $4, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl $0, %%eax\n\t"
      "setne %%al\n\t"
      "decl %%eax\n\t"
      "andl %%edx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c18f2d0]\n\t"
      "movswl 0x4(%%edi), %%ecx\n\t"
      "pushl $0x68\n\t"
      "pushl %%ecx\n\t"
      "leal 0x134(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[elem]\n\t"
      "movw 0x8(%%eax), %%ax\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw $-1, %%bx\n\t"
      "movw %%ax, -0x8(%%ebp)\n\t"
      "je .LFUN_00190550_2\n\t"
      "movswl %%bx, %%ecx\n\t"
      "pushl $0x28\n\t"
      "pushl %%ecx\n\t"
      "leal 0x184(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movw 0x24(%%edi), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00190550_2\n\t"
      "cmpw $-1, 0x26(%%edi)\n\t"
      "je .LFUN_00190550_2\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl $0x88\n\t"
      "pushl %%eax\n\t"
      "addl $0x190, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "movl 0x2c(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00190550_2\n\t"
      "pushl %%eax\n\t"
      "pushl $0x666f6720\n\t"
      "call *%[tag]\n\t"
      "movb (%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $1, %%cl\n\t"
      "je .LFUN_00190550_1\n\t"
      "testb $8, 0x14(%%ebp)\n\t"
      "jne .LFUN_00190550_2\n\t"
      "movw 0x26(%%edi), %%cx\n\t"
      "movw %%cx, -0x8(%%ebp)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_00190550_2\n\t"
      ".LFUN_00190550_1:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00190550_2\n\t"
      "movw 0x26(%%edi), %%dx\n\t"
      "movw %%dx, -0x8(%%ebp)\n\t"
      ".LFUN_00190550_2:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00190550_3:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c190240]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e3c0] "m"(b190550_c18e3c0), [c18f2d0] "m"(b190550_c18f2d0), [elem] "m"(b190550_elem), [tag] "m"(b190550_tag), [c190240] "m"(b190550_c190240)
      : "memory");
}
#else
#error "FUN_00190550: clang naked draft required"
#endif


/* FUN_00190670 (0x190670) — readable C lift. */
void FUN_00190670(int a0, int a1, int a2, int a3)
{
  FUN_00190550(a0, a1, a2, a3 | 8);
}

/* FUN_00190690 (0x190690) — readable C lift. */
void FUN_00190690(int a0, int a1, int a2, int a3)
{
  FUN_00190550(a0, a1, a2, a3 | 4);
}

/* FUN_001906b0 (0x1906b0) — readable C lift. */
void *FUN_001906b0(void *shader, int shader_type)
{
  extern char DAT_002a18b8[];
  extern char DAT_002b231c[];
  extern char DAT_002b22fc[];

  if (!shader) {
    display_assert(DAT_002a18b8, DAT_002b231c, 0x85c, 1);
    system_exit(-1);
  }
  if (*(int16_t *)((char *)shader + 0x24) != (int16_t)shader_type) {
    display_assert(DAT_002b22fc, DAT_002b231c, 0x85d, 1);
    system_exit(-1);
  }
  return shader;
}

/* shader_get_vertex_shader_permutation (0x190710) — XBE naked draft (batch 250). */
#if defined(__clang__)
static void (*const b190710_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b190710_exitfn)(int) = system_exit;
static void * (*const b190710_c1906b0)(void *shader, int shader_type) = FUN_001906b0;

__attribute__((naked, noinline))
int shader_get_vertex_shader_permutation(void *shader __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lshader_get_vertex_shader_permutation_1\n\t"
      "pushl $1\n\t"
      "pushl $0x14\n\t"
      "pushl $0x2b2348\n\t"
      "pushl $0x2a18b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lshader_get_vertex_shader_permutation_2\n\t"
      ".Lshader_get_vertex_shader_permutation_1:\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lshader_get_vertex_shader_permutation_9\n\t"
      ".Lshader_get_vertex_shader_permutation_2:\n\t"
      "movswl 0x24(%%edi), %%eax\n\t"
      "decl %%eax\n\t"
      "cmpl $5, %%eax\n\t"
      "ja .Lshader_get_vertex_shader_permutation_9\n\t"
      "jmp *.Lshader_get_vertex_shader_permutation_jt(,%%eax,4)\n\t"
      ".Lshader_get_vertex_shader_permutation_3:\n\t"
      "pushl $4\n\t"
      "pushl %%edi\n\t"
      "call *%[c1906b0]\n\t"
      "flds 0x38(%%eax)\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lshader_get_vertex_shader_permutation_9\n\t"
      "movl $1, %%esi\n\t"
      "popl %%edi\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lshader_get_vertex_shader_permutation_4:\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[c1906b0]\n\t"
      "movl 0x58(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lshader_get_vertex_shader_permutation_9\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[c1906b0]\n\t"
      "movw 0x5c(%%eax), %%si\n\t"
      "addl $8, %%esp\n\t"
      "incw %%si\n\t"
      "popl %%edi\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lshader_get_vertex_shader_permutation_5:\n\t"
      "pushl $5\n\t"
      "pushl %%edi\n\t"
      "call *%[c1906b0]\n\t"
      "movw 0x2a(%%eax), %%si\n\t"
      "addl $8, %%esp\n\t"
      "incw %%si\n\t"
      "cmpw $1, %%si\n\t"
      "jne .Lshader_get_vertex_shader_permutation_8\n\t"
      "pushl $5\n\t"
      "jmp .Lshader_get_vertex_shader_permutation_7\n\t"
      ".Lshader_get_vertex_shader_permutation_6:\n\t"
      "pushl $6\n\t"
      "pushl %%edi\n\t"
      "call *%[c1906b0]\n\t"
      "movw 0x2a(%%eax), %%si\n\t"
      "addl $8, %%esp\n\t"
      "incw %%si\n\t"
      "cmpw $1, %%si\n\t"
      "jne .Lshader_get_vertex_shader_permutation_8\n\t"
      "pushl $6\n\t"
      ".Lshader_get_vertex_shader_permutation_7:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1906b0]\n\t"
      "movb 0x29(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $8, %%cl\n\t"
      "jne .Lshader_get_vertex_shader_permutation_8\n\t"
      "xorl %%esi, %%esi\n\t"
      ".Lshader_get_vertex_shader_permutation_8:\n\t"
      "testb $4, (%%edi)\n\t"
      "je .Lshader_get_vertex_shader_permutation_10\n\t"
      "movl $5, %%esi\n\t"
      "popl %%edi\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lshader_get_vertex_shader_permutation_9:\n\t"
      "xorl %%esi, %%esi\n\t"
      ".Lshader_get_vertex_shader_permutation_10:\n\t"
      "popl %%edi\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lshader_get_vertex_shader_permutation_jt:\n\t"
      ".long .Lshader_get_vertex_shader_permutation_4\n\t"
      ".long .Lshader_get_vertex_shader_permutation_9\n\t"
      ".long .Lshader_get_vertex_shader_permutation_9\n\t"
      ".long .Lshader_get_vertex_shader_permutation_3\n\t"
      ".long .Lshader_get_vertex_shader_permutation_5\n\t"
      ".long .Lshader_get_vertex_shader_permutation_6\n\t"
      ".text\n\t"
      :
      : [assert] "m"(b190710_assert), [exitfn] "m"(b190710_exitfn), [c1906b0] "m"(b190710_c1906b0)
      : "memory");
}
#else
#error "shader_get_vertex_shader_permutation: clang naked draft required"
#endif


/* shader_is_mirror (0x190830) — readable C lift. */
char shader_is_mirror(void *shader)
{
  int shader_type;
  void *typed;

  if (!shader)
    return 0;
  shader_type = *(int16_t *)((char *)shader + 0x24);
  if (shader_type == 3) {
    typed = FUN_001906b0(shader, 3);
    return (char)(*(unsigned char *)((char *)typed + 0x2d0) & 1);
  }
  if (shader_type == 8) {
    typed = FUN_001906b0(shader, 8);
    return (char)(*(int16_t *)((char *)typed + 0x8a) == 2);
  }
  return 0;
}


/* shader_is_decal (0x1908a0) — readable C lift. */
char shader_is_decal(void *shader)
{
  short kind;
  void *sub;
  unsigned char bit;

  if (!shader)
    return 0;
  kind = (short)(*(short *)((char *)shader + 0x24) - 5);
  if ((unsigned short)kind > 4u)
    return 0;
  switch (kind) {
  case 0:
    sub = FUN_001906b0(shader, 5);
    bit = *(unsigned char *)((char *)sub + 0x29);
    return (char)((bit >> 1) & 1);
  case 1:
    sub = FUN_001906b0(shader, 6);
    bit = *(unsigned char *)((char *)sub + 0x29);
    return (char)((bit >> 1) & 1);
  case 2:
    return 0;
  case 3:
    sub = FUN_001906b0(shader, 8);
    bit = *(unsigned char *)((char *)sub + 0x28);
    return (char)((bit >> 1) & 1);
  case 4:
    sub = FUN_001906b0(shader, 9);
    bit = *(unsigned char *)((char *)sub + 0x28);
    return (char)(bit & 1);
  default:
    return 0;
  }
}
/* shader_is_water_decal (0x190930) — readable C lift. */
char shader_is_water_decal(void *shader)
{
  int shader_type;
  void *typed;

  if (!shader)
    return 0;
  shader_type = *(int16_t *)((char *)shader + 0x24);
  if (shader_type == 5) {
    typed = FUN_001906b0(shader, 5);
    return (char)((*(unsigned char *)((char *)typed + 0x29) >> 4) & 1);
  }
  if (shader_type == 6) {
    typed = FUN_001906b0(shader, 6);
    return (char)((*(unsigned char *)((char *)typed + 0x29) >> 4) & 1);
  }
  return 0;
}

/* shader_ignores_effect (0x190980) — readable C lift. */
char shader_ignores_effect(void *shader)
{
  int shader_type;
  void *typed;

  if (!shader)
    return 0;
  shader_type = *(int16_t *)((char *)shader + 0x24);
  if (shader_type == 5) {
    typed = FUN_001906b0(shader, 5);
    return (char)((*(unsigned char *)((char *)typed + 0x29) >> 5) & 1);
  }
  if (shader_type == 6) {
    typed = FUN_001906b0(shader, 6);
    return (char)((*(unsigned char *)((char *)typed + 0x29) >> 5) & 1);
  }
  return 0;
}


/* shader_type_is_transparent (0x1909d0) — readable C lift. */
char shader_type_is_transparent(short shader_type)
{
  int t = (int)shader_type;
  if (t == 1) return 1;
  if (t <= 4) return 0;
  if (t > 10) return 0;
  return 1;
}

/* shader_type_is_lightmapped (0x1909f0) — readable C lift. */
char shader_type_is_lightmapped(short shader_type)
{
  int t = (int)shader_type;
  if (t < 3) return 0;
  if (t <= 4) return 1;
  return t == 8;
}

/* shader_type_is_vertex_lit (0x190a10) — readable C lift. */
char shader_type_is_vertex_lit(short shader_type)
{
  int t = (int)shader_type;
  return t == 4 || t == 8;
}

/* shader_type_is_valid_for_environment (0x190a30) — readable C lift. */
char shader_type_is_valid_for_environment(short shader_type)
{
  int t = (int)shader_type;
  if (t == 3) return 1;
  if (t <= 4) return 0;
  if (t > 9) return 0;
  return 1;
}

/* shader_type_is_valid_for_model (0x190a50) — readable C lift. */
char shader_type_is_valid_for_model(short shader_type)
{
  int t = (int)shader_type;
  return t >= 3 && t <= 10;
}

/* shader_type_is_valid_for_modifier (0x190a70) — readable C lift. */
char shader_type_is_valid_for_modifier(short shader_type)
{
  int t = (int)shader_type;
  if (t == 1) return 1;
  if (t <= 4) return 0;
  if (t > 10) return 0;
  return 1;
}

/* shader_environment_texture_animation_evaluate (0x190a90) — readable C lift (restored pre-naked). */
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


/* numeric_countdown_timer_set (0x190be0) — readable C lift. */
void numeric_countdown_timer_set(int value, char flag)
{
  *(int *)0x4d8a78 = value;
  *(char *)0x4d8a7c = flag;
}

/* numeric_countdown_timer_get (0x190c00) — readable C lift. */
int numeric_countdown_timer_get(int a0)
{
  int v;
  int idx;
  int q;
  int r;

  v = *(int *)0x4d8a78;
  idx = (int)(short)a0 + 1;
  /* Match XBE: `mov ax, dx` leaves high 16 bits of EAX from the prior quotient. */
  if ((unsigned int)idx > 9u)
    return idx & ~0xFFFF;
  switch (idx) {
  case 0:
    return v & 0xFFFF;
  case 1:
    q = v / 10;
    r = v % 10;
    return (q & ~0xFFFF) | (r & 0xFFFF);
  case 2:
    q = (v / 10) / 10;
    r = (v / 10) % 10;
    return (q & ~0xFFFF) | (r & 0xFFFF);
  case 3:
    q = (v / 100) / 10;
    r = (v / 100) % 10;
    return (q & ~0xFFFF) | (r & 0xFFFF);
  case 4:
    q = (v / 1000) / 10;
    r = (v / 1000) % 10;
    return (q & ~0xFFFF) | (r & 0xFFFF);
  case 5:
    q = (v / 10000) / 6;
    r = (v / 10000) % 6;
    return (q & ~0xFFFF) | (r & 0xFFFF);
  case 6:
    q = (v / 60000) / 10;
    r = (v / 60000) % 10;
    return (q & ~0xFFFF) | (r & 0xFFFF);
  case 7:
    q = (v / 360000) / 6;
    r = (v / 360000) % 6;
    return (q & ~0xFFFF) | (r & 0xFFFF);
  case 8:
    q = (v / 3600000) / 10;
    r = (v / 3600000) % 10;
    return (q & ~0xFFFF) | (r & 0xFFFF);
  case 9:
    q = (v / 36000000) / 10;
    r = (v / 36000000) % 10;
    return (q & ~0xFFFF) | (r & 0xFFFF);
  default:
    return idx & ~0xFFFF;
  }
}

/* numeric_countdown_timer_stop (0x190d90) — readable C lift. */
void numeric_countdown_timer_stop(void)
{
  *(unsigned char *)0x4d8a7c = 0;
}

/* numeric_countdown_timer_restart (0x190da0) — readable C lift. */
void numeric_countdown_timer_restart(void)
{
  *(unsigned char *)0x4d8a7c = 1;
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

