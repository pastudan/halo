/* path_obstacle_avoidance.c — AI path obstacle-avoidance helpers.
 *
 * Corresponds to path_obstacle_avoidance.obj.
 *
 * Recovered by lifting from cachebeta.xbe (v01.10.12.2276).
 */
#include "../../common.h"

/*
 * FUN_00060c40 -- valid_real_point2d: returns true when both components of a
 * real_point2d (x, y) are finite (neither NaN nor +/-Inf).
 *
 * A float is non-finite iff its IEEE-754 exponent field is all ones, i.e.
 * (bits & 0x7f800000) == 0x7f800000. The original materializes the boolean
 * in full EAX (MOV EAX,1 / XOR EAX,EAX); Ghidra collapsed the two returns to
 * void because callers discarded the result. Same 0x7f800000 mask idiom as
 * valid_real_rgb_color.
 *
 * ABI: cdecl, one stack pointer arg (real_point2d*), pure integer leaf.
 *
 * Shape (delinked 00060c40.obj): each component is copied into a float local
 * first, then bit-tested through the local — VC71 spills the local into the
 * dead param home slot ([EBP+8], MOV [EBP+8],ECX / MOV [EBP+8],EAX), keeping
 * the frame at zero locals. Testing point[N]'s bits directly loses those
 * stores (59.5%); the local recovers them. The tests are spelled as a nested
 * valid-chain (`!= mask` guarding inward, shared `return 0` tail) so both
 * branches compile to JE into the trailing XOR EAX block — goto/early-return
 * spellings made VC71 flip the second branch (85.7%). 100.0% VC71.
 */
int valid_real_point2d(float *point)
{
  float v;

  v = point[0];
  if ((*(uint32_t *)&v & 0x7f800000) != 0x7f800000) {
    v = point[1];
    if ((*(uint32_t *)&v & 0x7f800000) != 0x7f800000)
      return 1;
  }
  return 0;
}
/* --- path_obstacle_avoidance.obj batch drafts (2026-07-26) --- */

/* path_add_step (0x60c80) — XBE naked draft (batch 221). */
#if defined(__clang__)
static void (*const b60c80_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b60c80_exitfn)(int) = system_exit;
static void * (*const b60c80_c600f0)(void *path, int16_t step_index) = FUN_000600f0;
static float (*const b60c80_mag)(float *) = magnitude3d;
static void *(*const b60c80_memset)(void *, int, unsigned int) = csmemset;
static char (*const b60c80_c60910)(void *path, int16_t step_index) = FUN_00060910;

__attribute__((naked, noinline))
int16_t path_add_step(void *path __attribute__((unused)), float *delta __attribute__((unused)), int16_t zone_index __attribute__((unused)), char surface_flag __attribute__((unused)), float step_cost __attribute__((unused)), int16_t parent_step __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "cmpw $0x80, 0x2c(%%edi)\n\t"
      "jge .Lpath_add_step_12\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "flds 0x10(%%edi)\n\t"
      "fsubs (%%eax)\n\t"
      "pushl %%ebx\n\t"
      "movl 0x1c(%%ebp), %%ebx\n\t"
      "cmpw $-1, %%bx\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "flds 0x14(%%edi)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "movl %%ebx, %%esi\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "je .Lpath_add_step_8\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lpath_add_step_1:\n\t"
      "testw %%si, %%si\n\t"
      "jl .Lpath_add_step_2\n\t"
      "movw 0x2c(%%edi), %%ax\n\t"
      "cmpw %%ax, %%si\n\t"
      "jge .Lpath_add_step_2\n\t"
      "cmpw $0x80, %%ax\n\t"
      "jle .Lpath_add_step_3\n\t"
      ".Lpath_add_step_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x28\n\t"
      "pushl $0x25ea14\n\t"
      "pushl $0x25e9b0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpath_add_step_3:\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%eax\n\t"
      "leal 0x30(%%edi,%%eax,8), %%esi\n\t"
      "movw 0x10(%%ebp), %%ax\n\t"
      "cmpw %%ax, 0x18(%%esi)\n\t"
      "jne .Lpath_add_step_4\n\t"
      "movb 0x14(%%ebp), %%cl\n\t"
      "cmpb %%cl, 0x1a(%%esi)\n\t"
      "jne .Lpath_add_step_11\n\t"
      "movw 0x24(%%esi), %%si\n\t"
      "cmpw $-1, %%si\n\t"
      "jne .Lpath_add_step_1\n\t"
      "jmp .Lpath_add_step_8\n\t"
      ".Lpath_add_step_4:\n\t"
      "movw 0x1c(%%edi), %%cx\n\t"
      "cmpw %%cx, %%ax\n\t"
      "jne .Lpath_add_step_8\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .Lpath_add_step_8\n\t"
      "movb 0x14(%%ebp), %%al\n\t"
      "xorl %%edx, %%edx\n\t"
      "testb %%al, %%al\n\t"
      "sete %%dl\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movw 0x1c(%%esi,%%edx,2), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lpath_add_step_6\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c600f0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c600f0]\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x10(%%ebx)\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds -0xc(%%ebp)\n\t"
      "addl $0x10, %%esp\n\t"
      "fmuls 0xc(%%ebx)\n\t"
      "faddp %%st(1)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lpath_add_step_5\n\t"
      "flds 0x10(%%ecx)\n\t"
      "fmuls 0xc(%%ebx)\n\t"
      "flds 0x10(%%ebx)\n\t"
      "fmuls 0xc(%%ecx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0xc(%%ebx)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x10(%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fmulp %%st(1)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lpath_add_step_11\n\t"
      ".Lpath_add_step_5:\n\t"
      "movl 0x1c(%%ebp), %%ebx\n\t"
      ".Lpath_add_step_6:\n\t"
      "movzbl 0x14(%%ebp), %%ecx\n\t"
      "movw 0x1c(%%esi,%%ecx,2), %%ax\n\t"
      "cmpw %%bx, %%ax\n\t"
      "leal 0x1c(%%esi,%%ecx,2), %%esi\n\t"
      "je .Lpath_add_step_7\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .Lpath_add_step_8\n\t"
      ".Lpath_add_step_7:\n\t"
      "movw 0x2c(%%edi), %%dx\n\t"
      "movw %%dx, (%%esi)\n\t"
      ".Lpath_add_step_8:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movw 0x2c(%%edi), %%bx\n\t"
      "leal 0x1(%%ebx), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movw %%ax, 0x2c(%%edi)\n\t"
      "call *%[c600f0]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "leal 0xc(%%esi), %%eax\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "call *%[mag]\n\t"
      "fsts 0x14(%%esi)\n\t"
      "movw 0x10(%%ebp), %%ax\n\t"
      "fadds 0x18(%%ebp)\n\t"
      "movb 0x14(%%ebp), %%cl\n\t"
      "movw 0x1c(%%ebp), %%dx\n\t"
      "pushl $4\n\t"
      "fstps 0x20(%%esi)\n\t"
      "movw %%ax, 0x18(%%esi)\n\t"
      "leal 0x1c(%%esi), %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "movb %%cl, 0x1a(%%esi)\n\t"
      "movw %%dx, 0x24(%%esi)\n\t"
      "call *%[memset]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lpath_add_step_9\n\t"
      "flds 0x14(%%esi)\n\t"
      "fcomps 0x24(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lpath_add_step_9\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x24(%%edi)\n\t"
      "movw %%bx, 0x20(%%edi)\n\t"
      ".Lpath_add_step_9:\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c60910]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lpath_add_step_10\n\t"
      "pushl $1\n\t"
      "pushl $0x1a4\n\t"
      "pushl $0x25ea14\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpath_add_step_10:\n\t"
      "popl %%esi\n\t"
      "movw %%bx, %%ax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lpath_add_step_11:\n\t"
      "popl %%esi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      ".Lpath_add_step_12:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [assert] "m"(b60c80_assert), [exitfn] "m"(b60c80_exitfn), [c600f0] "m"(b60c80_c600f0), [mag] "m"(b60c80_mag), [memset] "m"(b60c80_memset), [c60910] "m"(b60c80_c60910)
      : "memory");
}
#else
#error "path_add_step: clang naked draft required"
#endif


/* FUN_00060ea0 (0x60ea0) — XBE naked draft (batch 233). */
#if defined(__clang__)
static char * (*const b60ea0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b60ea0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b60ea0_exitfn)(int) = system_exit;
static short (*const b60ea0_c62410)(void *obstacles, short disc_index_skip, float *position_xy, float radius) = FUN_00062410;
static void * (*const b60ea0_c60070)(void *obstacles, int16_t disc_index) = FUN_00060070;
static int16_t (*const b60ea0_c60c80)(void *path, float *delta, int16_t zone_index, char surface_flag, float step_cost, int16_t parent_step) = path_add_step;

__attribute__((naked, noinline))
void FUN_00060ea0(void *avoidance_record __attribute__((unused)), float *end_point __attribute__((unused)), void *param_2 __attribute__((unused)), void *scenario __attribute__((unused)), unsigned char param_4 __attribute__((unused)), float radius __attribute__((unused)), float *start_point __attribute__((unused)), int param_7 __attribute__((unused)), float param_8 __attribute__((unused)), unsigned char param_9 __attribute__((unused)), unsigned char param_10 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%edi\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .LFUN_00060ea0_1\n\t"
      "flds 0x14(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x1b8\n\t"
      "pushl $0x25ea14\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "movl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x253f04\n\t"
      "pushl $0x25eb8c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x18, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00060ea0_1:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "je .LFUN_00060ea0_2\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jne .LFUN_00060ea0_3\n\t"
      ".LFUN_00060ea0_2:\n\t"
      "flds 0x4(%%eax)\n\t"
      "pushl $1\n\t"
      "pushl $0x1b9\n\t"
      "pushl $0x25ea14\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%eax)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25eb84\n\t"
      "pushl $0x25eb5c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00060ea0_3:\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LFUN_00060ea0_4\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jne .LFUN_00060ea0_5\n\t"
      ".LFUN_00060ea0_4:\n\t"
      "flds 0x4(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x1ba\n\t"
      "pushl $0x25ea14\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25eb54\n\t"
      "pushl $0x25eb5c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00060ea0_5:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "movb 0x10(%%ebp), %%cl\n\t"
      "movl %%edx, 0xc(%%edi)\n\t"
      "movb %%cl, 0x4(%%edi)\n\t"
      "movl %%eax, 0x8(%%edi)\n\t"
      "movb $0, 0x28(%%edi)\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl %%edx, 0x10(%%edi)\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "movl %%ecx, 0x14(%%edi)\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, 0x18(%%edi)\n\t"
      "call *%[c62410]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw %%si, %%ax\n\t"
      "je .LFUN_00060ea0_6\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c60070]\n\t"
      "movswl 0x2(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_00060ea0_7\n\t"
      ".LFUN_00060ea0_6:\n\t"
      "movl %%esi, %%eax\n\t"
      ".LFUN_00060ea0_7:\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "movb 0x28(%%ebp), %%cl\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "movw %%ax, 0x1c(%%edi)\n\t"
      "movb 0x24(%%ebp), %%al\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "movb %%al, 0x29(%%edi)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movw %%si, 0x1e(%%edi)\n\t"
      "movl $0x7f7fffff, 0x24(%%edi)\n\t"
      "movw %%si, 0x20(%%edi)\n\t"
      "movb %%cl, 0x2a(%%edi)\n\t"
      "movw $0, 0x2c(%%edi)\n\t"
      "movw $0, 0x1430(%%edi)\n\t"
      "call *%[c60c80]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8d9d0] "m"(b60ea0_c8d9d0), [assert] "m"(b60ea0_assert), [exitfn] "m"(b60ea0_exitfn), [c62410] "m"(b60ea0_c62410), [c60070] "m"(b60ea0_c60070), [c60c80] "m"(b60ea0_c60c80)
      : "memory");
}
#else
#error "FUN_00060ea0: clang naked draft required"
#endif


/* FUN_00061080 (0x61080) — readable C lift (restored pre-naked). */
void FUN_00061080(void *structure_bsp, unsigned char path_surface_flag,
                  void *obstacles, int16_t disc_index, int surface_hint,
                  float max_cost, float ray_t, unsigned char skip_ray_march,
                  unsigned char use_cost_delta, char check_extant,
                  void *out_result, float *step_data, float *direction)
{
  int ray_hit[3];
  float perp[2];
  float pt_off[2];
  float pt_neg[2];
  char disc_buf[8];
  char kept_hit;
  int hit_surface;

  *(float *)out_result = ray_t;
  *(int *)((char *)out_result + 4) = -1;
  *(int *)((char *)out_result + 8) = -1;
  *(int16_t *)((char *)out_result + 0xc) = -1;
  *(int16_t *)((char *)out_result + 0xe) = -1;

  if (use_cost_delta)
    *(float *)out_result = ray_t - max_cost;

  if (!skip_ray_march) {
    if (structure_test_ray2d(structure_bsp, path_surface_flag, step_data,
                             surface_hint, direction, *(float *)out_result,
                             ray_hit) &&
        *(float *)out_result >= *(float *)ray_hit) {
      *(float *)out_result = *(float *)ray_hit;
      *(int *)((char *)out_result + 8) = ray_hit[2];
    }

    perpendicular2d(direction, perp);

    pt_off[0] = perp[0] * max_cost + step_data[0];
    pt_off[1] = perp[1] * max_cost + step_data[1];
    if (structure_test_ray2d(structure_bsp, path_surface_flag, step_data,
                             surface_hint, perp, *(float *)out_result,
                             ray_hit) &&
        *(float *)out_result >= *(float *)ray_hit) {
      *(float *)out_result = *(float *)ray_hit;
      *(int *)((char *)out_result + 8) = ray_hit[2];
    }

    hit_surface = ray_hit[1];
    if (structure_test_ray2d(structure_bsp, path_surface_flag, pt_off,
                             hit_surface, direction, *(float *)out_result,
                             ray_hit) &&
        *(float *)out_result >= *(float *)ray_hit) {
      *(float *)out_result = *(float *)ray_hit;
      *(int *)((char *)out_result + 8) = ray_hit[2];
    }

    pt_neg[0] = -perp[0] * max_cost + step_data[0];
    pt_neg[1] = -perp[1] * max_cost + step_data[1];
    if (structure_test_ray2d(structure_bsp, path_surface_flag, step_data,
                             surface_hint, perp, *(float *)out_result,
                             ray_hit) &&
        *(float *)out_result >= *(float *)ray_hit) {
      *(float *)out_result = *(float *)ray_hit;
      *(int *)((char *)out_result + 8) = ray_hit[2];
    }

    hit_surface = ray_hit[1];
    if (structure_test_ray2d(structure_bsp, path_surface_flag, pt_neg,
                             hit_surface, direction, *(float *)out_result,
                             ray_hit) &&
        *(float *)out_result >= *(float *)ray_hit) {
      *(float *)out_result = *(float *)ray_hit;
      *(int *)((char *)out_result + 8) = ray_hit[2];
    }
  }

  if (FUN_000624b0(obstacles, disc_index, step_data, direction, max_cost,
                   *(float *)out_result, check_extant, disc_buf)) {
    if (*(float *)out_result >= *(float *)disc_buf) {
      *(float *)out_result = *(float *)disc_buf;
      *(int *)((char *)out_result + 8) = -1;
      *(int16_t *)((char *)out_result + 0xc) =
          *(int16_t *)((char *)disc_buf + 4);
      *(int16_t *)((char *)out_result + 0xe) =
          *(int16_t *)((char *)disc_buf + 6);
      kept_hit = 1;
    } else {
      kept_hit = 0;
    }
  } else {
    kept_hit = 0;
  }

  if (*(int *)((char *)out_result + 8) == -1 &&
      *(int16_t *)((char *)out_result + 0xc) == -1) {
    *(float *)out_result = ray_t;
    kept_hit = 0;
  }

  structure_test_ray2d(structure_bsp, path_surface_flag, step_data,
                       surface_hint, direction, *(float *)out_result, ray_hit);
  *(int *)((char *)out_result + 4) = ray_hit[1];
  (void)kept_hit;
}


/* path_add_steps (0x61280) — readable C lift (restored pre-naked). */
void path_add_steps(void *path, int16_t seed_disc_index, int16_t step_index)
{
  char *path_rec;
  char *obstacles;
  int16_t disc_count;
  char *step;
  uint32_t visited[(0x80 + 31) / 32];
  int16_t disc_stack[0x80];
  int16_t stack_top;
  int16_t disc_index;
  int16_t zone_link;
  float scalar;
  float cone_b[2];
  float cone_a[2];
  float direction[2];
  float ray_result[4];
  float target[2];
  float t;
  float step_cost;
  int16_t result_surface;
  int direction_pass;
  int16_t parent_step;

  path_rec = (char *)path;
  if (step_index < 0 || step_index >= *(int16_t *)(path_rec + 0x2c) ||
      *(int16_t *)(path_rec + 0x2c) > 0x80) {
    display_assert("step_index>=0 && step_index<path->step_count && "
                   "path->step_count<=MAXIMUM_OBSTACLE_AVOIDANCE_STEPS",
                   "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 40, 1);
    system_exit(-1);
  }

  obstacles = *(char **)(path_rec + 8);
  disc_count = *(int16_t *)(obstacles + 2);
  if (disc_count < 0 || disc_count > 0x80) {
    display_assert("path->obstacles->disc_count>=0 && "
                   "path->obstacles->disc_count<=MAXIMUM_DISC_COUNT",
                   "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 594, 1);
    system_exit(-1);
  }

  step = (char *)FUN_000600f0(path, step_index);

  csmemset(visited, 0, ((disc_count + 31) >> 5) << 2);

  if (seed_disc_index < 0 || seed_disc_index >= disc_count) {
    display_assert("seed_disc_index>=0 && "
                   "seed_disc_index<path->obstacles->disc_count",
                   "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 597, 1);
    system_exit(-1);
  }

  visited[(unsigned int)seed_disc_index >> 5] |=
      1U << (seed_disc_index & 31);
  disc_stack[0] = seed_disc_index;
  stack_top = 1;

  while (stack_top > 0) {
    stack_top--;
    disc_index = disc_stack[stack_top];

    if (disc_index < 0 || disc_index >= disc_count || disc_count > 0x80) {
      display_assert("disc_index>=0 && disc_index<obstacles->disc_count && "
                     "obstacles->disc_count<=MAXIMUM_DISC_COUNT",
                     "c:\\halo\\source\\ai\\path.h", 0x18c, 1);
      system_exit(-1);
    }

    if (disc_index == -1)
      zone_link = -1;
    else
      zone_link =
          *(int16_t *)(obstacles + 8 + (int)disc_index * 0x18 + 0xa);

    FUN_000625a0(obstacles, disc_index, (float *)step, *(float *)path_rec,
                 cone_b, cone_a, &scalar);
    if (scalar > *(float *)path_rec)
      scalar = *(float *)path_rec;

    direction[0] = cone_b[0];
    direction[1] = cone_b[1];
    for (direction_pass = 0; direction_pass < 2; direction_pass++) {
      FUN_00061080(*(void **)(path_rec + 0xc), *(unsigned char *)(path_rec + 4),
                   obstacles, disc_index, *(int *)(step + 8), *(float *)path_rec,
                   *(float *)path_rec * 2.0f + scalar, 0,
                   *(unsigned char *)(path_rec + 0x2a), 0, ray_result,
                   (float *)step, direction);

      disc_index = (int16_t)*(int32_t *)(ray_result + 2);
      result_surface = *(int16_t *)((char *)ray_result + 0xc);

      if (disc_index != -1) {
        if (disc_index < 0 || disc_index >= disc_count) {
          display_assert("result.disc_index>=0 && "
                         "result.disc_index<path->obstacles->disc_count",
                         "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 625,
                         1);
          system_exit(-1);
        }
        if (!(visited[(unsigned int)disc_index >> 5] &
              (1U << (disc_index & 31)))) {
          visited[(unsigned int)disc_index >> 5] |=
              1U << (disc_index & 31);
          if (stack_top >= 0x80) {
            display_assert("stack_top<MAXIMUM_DISC_COUNT",
                           "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c",
                           631, 1);
            system_exit(-1);
          }
          disc_stack[stack_top] = disc_index;
          stack_top++;
        }
      }

      if (*(float *)ray_result <= scalar && result_surface != zone_link) {
        float ray_test_out[6];

        t = (*(float *)ray_result + scalar) * *(float *)0x253398;
        target[0] = *(float *)step + direction[0] * t;
        target[1] = *(float *)(step + 4) + direction[1] * t;
        structure_test_ray2d(
            *(void **)(path_rec + 0xc), *(unsigned char *)(path_rec + 4),
            (float *)step, *(int *)(step + 8), direction, t, ray_test_out);
        step_cost =
            *(float *)(step + 0x20) - *(float *)(step + 0x14) + t;
        parent_step = -1;
        path_add_step(path, target, zone_link, 0, step_cost, parent_step);
      }

      direction[0] = cone_a[0];
      direction[1] = cone_a[1];
    }
  }
}


/* FUN_000615b0 (0x615b0) — XBE naked draft (batch 226). */
#if defined(__clang__)
static int16_t (*const b615b0_c60970)(void *path) = FUN_00060970;
static void * (*const b615b0_c600f0)(void *path, int16_t step_index) = FUN_000600f0;
static void (*const b615b0_c61080)(void *structure_bsp, unsigned char path_surface_flag, void *obstacles, int16_t disc_index, int surface_hint, float max_cost, float ray_t, unsigned char skip_ray_march, unsigned char use_cost_delta, char check_extant, void *out_result, float *step_data, float *direction) = FUN_00061080;
static bool (*const b615b0_c638f0)(int def, float *point, int surf_a, int surf_b) = FUN_000638f0;
static int16_t (*const b615b0_c60c80)(void *path, float *delta, int16_t zone_index, char surface_flag, float step_cost, int16_t parent_step) = path_add_step;
static void (*const b615b0_c61280)(void *path, int16_t seed_disc_index, int16_t step_index) = path_add_steps;

__attribute__((naked, noinline))
int FUN_000615b0(void *avoidance_record __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c60970]\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LFUN_000615b0_5\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c600f0]\n\t"
      "movl %%eax, %%edi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x2a(%%esi), %%cl\n\t"
      "cmpw $-1, 0x24(%%edi)\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x14(%%edi), %%eax\n\t"
      "sete %%dl\n\t"
      "leal 0xc(%%edi), %%ebx\n\t"
      "pushl %%ecx\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x4(%%esi), %%cl\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c61080]\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "addl $0x34, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000615b0_4\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "cmpw $-1, %%cx\n\t"
      "jne .LFUN_000615b0_2\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_000615b0_1\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "leal 0x10(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c638f0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000615b0_4\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      ".LFUN_000615b0_1:\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "fmuls (%%ebx)\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "fadds (%%edi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      "fadds 0x4(%%edi)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x20(%%edi)\n\t"
      "fsubs 0x14(%%edi)\n\t"
      "movl %%esi, %%edi\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c60c80]\n\t"
      "addl $0x18, %%esp\n\t"
      "movw %%ax, 0x1e(%%esi)\n\t"
      "jmp .LFUN_000615b0_4\n\t"
      ".LFUN_000615b0_2:\n\t"
      "movw -0xe(%%ebp), %%dx\n\t"
      "cmpw 0x1c(%%esi), %%dx\n\t"
      "jne .LFUN_000615b0_3\n\t"
      "flds 0x14(%%edi)\n\t"
      "fcomps 0x24(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000615b0_3\n\t"
      "movl 0x14(%%edi), %%eax\n\t"
      "movw -0x4(%%ebp), %%dx\n\t"
      "movl %%eax, 0x24(%%esi)\n\t"
      "movw %%dx, 0x20(%%esi)\n\t"
      ".LFUN_000615b0_3:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, %%eax\n\t"
      "call *%[c61280]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000615b0_4:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_000615b0_5:\n\t"
      "cmpw $-1, 0x1e(%%esi)\n\t"
      "jne .LFUN_000615b0_6\n\t"
      "cmpw $0, 0x1430(%%esi)\n\t"
      "jle .LFUN_000615b0_6\n\t"
      "movl $1, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000615b0_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c60970] "m"(b615b0_c60970), [c600f0] "m"(b615b0_c600f0), [c61080] "m"(b615b0_c61080), [c638f0] "m"(b615b0_c638f0), [c60c80] "m"(b615b0_c60c80), [c61280] "m"(b615b0_c61280)
      : "memory");
}
#else
#error "FUN_000615b0: clang naked draft required"
#endif


/* FUN_000616e0 (0x616e0) — readable C lift. */
char FUN_000616e0(void *rec, void *p0, void *p1, void *p2, void *p3, void *p4, float *end_point)
{
  void *scenario;
  short neg1;

  scenario = scenario_get();
  FUN_00060ea0(rec, end_point, p1, scenario, (unsigned char)(unsigned int)p0, 0.0f, (float *)p2, (int)p3, 0.0f, (unsigned char)(unsigned int)p4, 0);
  while (FUN_000615b0(rec))
    ;
  neg1 = (short)-1;
  if (*(short *)((char *)rec + 0x1e) != neg1) {
    *((unsigned char *)rec + 0x28) = 1;
    return (char)(*(short *)((char *)rec + 0x1e) != neg1);
  }
  if (*(short *)((char *)rec + 0x20) != neg1)
    *(short *)((char *)rec + 0x1e) = *(short *)((char *)rec + 0x20);
  return (char)(*(short *)((char *)rec + 0x1e) != neg1);
}

/* FUN_00061750 (0x61750) — XBE naked draft (batch 224). */
#if defined(__clang__)
static void (*const b61750_chkstk)(void) = FUN_001d90e0;
static void *(*const b61750_gbsp)(void) = global_collision_bsp_get;
static void (*const b61750_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b61750_exitfn)(int) = system_exit;
static void (*const b61750_c61d80)(int16_t *out) = FUN_00061d80;
static void (*const b61750_c620f0)(int16_t *partition, float *ref_point, float radius, float *vector, void *obstacles, void *scenario) = obstacles_get_discs_in_sphere;
static bool (*const b61750_c62020)(int16_t *obstacle_set, uint32_t datum, uint16_t flags, float *vector, uint32_t param_5) = FUN_00062020;
static void (*const b61750_c628b0)(int16_t *partition, uint32_t arg2) = FUN_000628b0;
static void * (*const b61750_c18e3c0)(void) = scenario_get;
static void (*const b61750_c60ea0)(void *avoidance_record, float *end_point, void *param_2, void *scenario, unsigned char param_4, float radius, float *start_point, int param_7, float param_8, unsigned char param_9, unsigned char param_10) = FUN_00060ea0;
static int (*const b61750_c615b0)(void *avoidance_record) = FUN_000615b0;
static char (*const b61750_c616e0)(void *avoidance_record, unsigned char path_flag, void *param_3, void *param_4, void *param_5, void *param_6, float *end_point, unsigned char param_8) = FUN_000616e0;
static int (*const b61750_c147990)(int bsp, int surface_index, int projection, int sign, float *point, float *out_point) = collision_surface_project_point2d;
static void (*const b61750_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
char FUN_00061750(unsigned int param_1 __attribute__((unused)), int param_2 __attribute__((unused)), void *param_3 __attribute__((unused)), int *param_4 __attribute__((unused)), void *param_5 __attribute__((unused)), char *param_6 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x2980, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[gbsp]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "flds (%%esi)\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "fcomps 0x2549d4\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00061750_1\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jmp .LFUN_00061750_2\n\t"
      ".LFUN_00061750_1:\n\t"
      "movl $0x3e4ccccd, -0x10(%%ebp)\n\t"
      ".LFUN_00061750_2:\n\t"
      "movl 0x48(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movb $1, %%bl\n\t"
      "je .LFUN_00061750_3\n\t"
      "movb 0x14588(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00061750_3\n\t"
      "movw 0xc(%%ebp), %%di\n\t"
      "cmpw $4, %%di\n\t"
      "movw $0, 0x1458a(%%eax)\n\t"
      "jle .LFUN_00061750_4\n\t"
      "pushl $1\n\t"
      "pushl $0x2f9\n\t"
      "pushl $0x25ea14\n\t"
      "pushl $0x25ed20\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00061750_4\n\t"
      ".LFUN_00061750_3:\n\t"
      "movw 0xc(%%ebp), %%di\n\t"
      ".LFUN_00061750_4:\n\t"
      "xorl %%edx, %%edx\n\t"
      "testw %%di, %%di\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "jle .LFUN_00061750_36\n\t"
      "movswl %%di, %%eax\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "jmp .LFUN_00061750_6\n\t"
      ".LFUN_00061750_5:\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      ".LFUN_00061750_6:\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "leal -0xc4c(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movswl %%dx, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "leal -0x2980(%%ebp), %%ebx\n\t"
      "jne .LFUN_00061750_7\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "cmpb $0, (%%eax)\n\t"
      "movb $1, -0x24(%%ebp)\n\t"
      "jne .LFUN_00061750_8\n\t"
      ".LFUN_00061750_7:\n\t"
      "movb $0, -0x24(%%ebp)\n\t"
      ".LFUN_00061750_8:\n\t"
      "testw %%dx, %%dx\n\t"
      "jle .LFUN_00061750_9\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "leal -0x44(%%ebp), %%edi\n\t"
      "jmp .LFUN_00061750_10\n\t"
      ".LFUN_00061750_9:\n\t"
      "movl 0x20(%%esi), %%eax\n\t"
      "leal 0x14(%%esi), %%edi\n\t"
      ".LFUN_00061750_10:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl %%ecx, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "addl %%esi, %%eax\n\t"
      "flds 0x4(%%eax)\n\t"
      "leal 0x4(%%eax), %%esi\n\t"
      "fsubs (%%edi)\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%esi, -0x30(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00061750_11\n\t"
      "fdivrs 0x2533c8\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      ".LFUN_00061750_11:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "movl 0x48(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00061750_12\n\t"
      "movl %%ecx, %%ebx\n\t"
      "imull $0x1534, %%ecx, %%ecx\n\t"
      "imull $0xc08, %%ebx, %%ebx\n\t"
      "leal 0x1458c(%%ebx,%%eax,1), %%ebx\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "leal 0x175ac(%%ecx,%%eax,1), %%ebx\n\t"
      "movb 0x14588(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00061750_12\n\t"
      "cmpw 0x1458a(%%eax), %%dx\n\t"
      "jl .LFUN_00061750_14\n\t"
      ".LFUN_00061750_12:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c61d80]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "pushl %%edx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x40800000\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c620f0]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movb 0x24(%%eax), %%cl\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00061750_13\n\t"
      "movl 0x38(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "leal 0x28(%%eax), %%edx\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c62020]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00061750_13:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c628b0]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x48(%%ecx), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00061750_14\n\t"
      "movb 0x14588(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00061750_14\n\t"
      "incw 0x1458a(%%eax)\n\t"
      ".LFUN_00061750_14:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movb 0x4(%%edx), %%al\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movb %%al, -0x34(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl -0x34(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c18e3c0]\n\t"
      "pushl %%eax\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[c60ea0]\n\t"
      "addl $0x24, %%esp\n\t"
      ".LFUN_00061750_15:\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c615b0]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00061750_15\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "cmpw %%cx, 0x1e(%%ebx)\n\t"
      "je .LFUN_00061750_16\n\t"
      "movb $1, 0x28(%%ebx)\n\t"
      "jmp .LFUN_00061750_17\n\t"
      ".LFUN_00061750_16:\n\t"
      "movw 0x20(%%ebx), %%ax\n\t"
      "cmpw %%cx, %%ax\n\t"
      "je .LFUN_00061750_17\n\t"
      "movw %%ax, 0x1e(%%ebx)\n\t"
      ".LFUN_00061750_17:\n\t"
      "cmpw %%cx, 0x1e(%%ebx)\n\t"
      "setne %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00061750_18\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpw $0, 0x4(%%eax)\n\t"
      "jle .LFUN_00061750_34\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x4(%%eax), %%cl\n\t"
      "movb $1, %%al\n\t"
      "movl %%ebx, %%esi\n\t"
      "pushl %%ecx\n\t"
      "movb -0x24(%%ebp), %%cl\n\t"
      "call *%[c616e0]\n\t"
      "movl -0x30(%%ebp), %%esi\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00061750_34\n\t"
      ".LFUN_00061750_18:\n\t"
      "movb 0x28(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "je .LFUN_00061750_19\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl %%edx, -0x44(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "movl %%ecx, -0x3c(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00061750_22\n\t"
      ".LFUN_00061750_19:\n\t"
      "movw 0x1e(%%ebx), %%si\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_00061750_20\n\t"
      "movw 0x2c(%%ebx), %%ax\n\t"
      "cmpw %%ax, %%si\n\t"
      "jge .LFUN_00061750_20\n\t"
      "cmpw $0x80, %%ax\n\t"
      "jle .LFUN_00061750_21\n\t"
      ".LFUN_00061750_20:\n\t"
      "pushl $1\n\t"
      "pushl $0x28\n\t"
      "pushl $0x25ea14\n\t"
      "pushl $0x25e9b0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00061750_21:\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%eax\n\t"
      "movl 0x38(%%ebx,%%eax,8), %%ecx\n\t"
      "leal 0x30(%%ebx,%%eax,8), %%eax\n\t"
      "leal -0x44(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "pushl $1\n\t"
      "pushl $2\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "call *%[c147990]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_00061750_22:\n\t"
      "movw 0x1e(%%ebx), %%si\n\t"
      "testw %%si, %%si\n\t"
      "je .LFUN_00061750_29\n\t"
      "jmp .LFUN_00061750_23\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00061750_23:\n\t"
      "movswl -0x8(%%ebp), %%edi\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "shll $4, %%edi\n\t"
      "incl %%ecx\n\t"
      "testw %%si, %%si\n\t"
      "leal -0x144c(%%ebp,%%edi,1), %%edi\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jl .LFUN_00061750_24\n\t"
      "movw 0x2c(%%ebx), %%ax\n\t"
      "cmpw %%ax, %%si\n\t"
      "jge .LFUN_00061750_24\n\t"
      "cmpw $0x80, %%ax\n\t"
      "jle .LFUN_00061750_25\n\t"
      ".LFUN_00061750_24:\n\t"
      "pushl $1\n\t"
      "pushl $0x28\n\t"
      "pushl $0x25ea14\n\t"
      "pushl $0x25e9b0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00061750_25:\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%ecx\n\t"
      "movl 0x38(%%ebx,%%ecx,8), %%edx\n\t"
      "leal 0x30(%%ebx,%%ecx,8), %%esi\n\t"
      "movl -0x2c(%%ebp), %%ecx\n\t"
      "movl %%edx, (%%edi)\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "addl $4, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c147990]\n\t"
      "movswl 0x24(%%esi), %%esi\n\t"
      "addl $0x18, %%esp\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_00061750_26\n\t"
      "cmpw 0x2c(%%ebx), %%si\n\t"
      "jl .LFUN_00061750_27\n\t"
      ".LFUN_00061750_26:\n\t"
      "pushl $1\n\t"
      "pushl $0x36b\n\t"
      "pushl $0x25ea14\n\t"
      "pushl $0x25ecd0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00061750_27:\n\t"
      "cmpw $0x80, -0x8(%%ebp)\n\t"
      "jge .LFUN_00061750_28\n\t"
      "testw %%si, %%si\n\t"
      "jne .LFUN_00061750_23\n\t"
      "jmp .LFUN_00061750_29\n\t"
      ".LFUN_00061750_28:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_00061750_29:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movw (%%edx), %%cx\n\t"
      "decl %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00061750_32\n\t"
      ".LFUN_00061750_30:\n\t"
      "cmpw $4, %%cx\n\t"
      "jge .LFUN_00061750_31\n\t"
      "movl 0x18(%%ebp), %%ebx\n\t"
      "movswl %%ax, %%esi\n\t"
      "shll $4, %%esi\n\t"
      "movswl %%cx, %%edi\n\t"
      "shll $4, %%edi\n\t"
      "addl %%ebx, %%edi\n\t"
      "leal -0x144c(%%ebp,%%esi,1), %%esi\n\t"
      "movl (%%esi), %%ebx\n\t"
      "movl %%ebx, (%%edi)\n\t"
      "movl 0x4(%%esi), %%ebx\n\t"
      "movl %%ebx, 0x4(%%edi)\n\t"
      "movl 0x8(%%esi), %%ebx\n\t"
      "incl %%ecx\n\t"
      "movl %%ebx, 0x8(%%edi)\n\t"
      "movl 0xc(%%esi), %%esi\n\t"
      "decl %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%esi, 0xc(%%edi)\n\t"
      "jge .LFUN_00061750_30\n\t"
      "jmp .LFUN_00061750_32\n\t"
      ".LFUN_00061750_31:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_00061750_32:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movw %%cx, (%%edx)\n\t"
      "jne .LFUN_00061750_33\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw 0xc(%%ebp), %%ax\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "jl .LFUN_00061750_5\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00061750_33:\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $0, (%%edx)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00061750_34:\n\t"
      "movb 0x3340a8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00061750_35\n\t"
      "pushl $0x25ecb4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movb $0, 0x3340a8\n\t"
      "movb $1, 0x3340a9\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, 0x5ab260\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x5ab264\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl %%edx, 0x5ab268\n\t"
      "movl %%eax, 0x5ab25c\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl %%ecx, 0x5ab250\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x5ab254\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movl %%ecx, 0x5ab248\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x5ab258\n\t"
      "movb -0x24(%%ebp), %%al\n\t"
      "movl %%edx, 0x5ab240\n\t"
      "movb %%al, 0x5ab245\n\t"
      "movb 0x4(%%ecx), %%dl\n\t"
      "movb %%dl, 0x5ab244\n\t"
      "movl $0x302, %%ecx\n\t"
      "movl $0x3334a0, %%edi\n\t"
      "rep movsl\n\t"
      "movl $0x54d, %%ecx\n\t"
      "movl %%ebx, %%esi\n\t"
      "movl $0x331f68, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "rep movsl\n\t"
      ".LFUN_00061750_35:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00061750_36:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(b61750_chkstk), [gbsp] "m"(b61750_gbsp), [assert] "m"(b61750_assert), [exitfn] "m"(b61750_exitfn), [c61d80] "m"(b61750_c61d80), [c620f0] "m"(b61750_c620f0), [c62020] "m"(b61750_c62020), [c628b0] "m"(b61750_c628b0), [c18e3c0] "m"(b61750_c18e3c0), [c60ea0] "m"(b61750_c60ea0), [c615b0] "m"(b61750_c615b0), [c616e0] "m"(b61750_c616e0), [c147990] "m"(b61750_c147990), [c8f390] "m"(b61750_c8f390)
      : "memory");
}
#else
#error "FUN_00061750: clang naked draft required"
#endif

