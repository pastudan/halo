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


/* 0x60ea0 — initialize avoidance record and seed first step */
void FUN_00060ea0(void *avoidance_record, float *end_point, void *param_2, void *scenario, unsigned char param_4, float radius, float *start_point, int param_7, float param_8, unsigned char param_9, unsigned char param_10)
{
  int16_t disc_index;
  int16_t link_index;
  void *obstacles;

  (void)param_7;
  (void)param_8;

  *(float *)avoidance_record = end_point[0];
  *(unsigned char *)((char *)avoidance_record + 4) = param_4;
  *(void **)((char *)avoidance_record + 8) = param_2;
  *(void **)((char *)avoidance_record + 0xc) = scenario;
  *(float *)((char *)avoidance_record + 0x10) = start_point[0];
  *(float *)((char *)avoidance_record + 0x14) = start_point[1];
  *(void **)((char *)avoidance_record + 0x18) = end_point;
  *(int16_t *)((char *)avoidance_record + 0x1c) = -1;
  *(int16_t *)((char *)avoidance_record + 0x1e) = -1;
  *(int16_t *)((char *)avoidance_record + 0x20) = -1;
  *(uint32_t *)((char *)avoidance_record + 0x24) = 0x7f7fffffU;
  *(unsigned char *)((char *)avoidance_record + 0x28) = 0;
  *(unsigned char *)((char *)avoidance_record + 0x29) = param_9;
  *(unsigned char *)((char *)avoidance_record + 0x2a) = param_10;
  *(int16_t *)((char *)avoidance_record + 0x2c) = 0;
  *(int16_t *)((char *)avoidance_record + 0x1430) = 0;

  obstacles = *(void **)((char *)avoidance_record + 8);
  disc_index =
      FUN_00062410(obstacles, -1, end_point, radius);
  if (disc_index == -1)
    link_index = -1;
  else
    link_index = FUN_000600c0(obstacles, disc_index);
  *(int16_t *)((char *)avoidance_record + 0x1c) = link_index;

  path_add_step(avoidance_record, end_point, link_index, 0, 0.0f, -1);
}

/* FUN_00061080 (0x61080) — XBE naked draft (batch 221). */
#if defined(__clang__)
static char (*const b61080_c63710)(void *structure_bsp, char ignore_breakable, float *point, int surface_index, float *direction, float t, void *out_result) = structure_test_ray2d;
static void (*const b61080_c10b600)(float *in, float *out) = perpendicular2d;
static char (*const b61080_c624b0)(void *obstacles, short skip_index, float *pt0, float *vec_a, float radius_base, float max_distance, char check_extant, void *result) = FUN_000624b0;

__attribute__((naked, noinline))
void FUN_00061080(void *structure_bsp __attribute__((unused)), unsigned char path_surface_flag __attribute__((unused)), void *obstacles __attribute__((unused)), int16_t disc_index __attribute__((unused)), int surface_hint __attribute__((unused)), float max_cost __attribute__((unused)), float ray_t __attribute__((unused)), unsigned char skip_ray_march __attribute__((unused)), unsigned char use_cost_delta __attribute__((unused)), char check_extant __attribute__((unused)), void *out_result __attribute__((unused)), float *step_data __attribute__((unused)), float *direction __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x3c, %%esp\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x30(%%ebp), %%esi\n\t"
      "movl %%eax, (%%esi)\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "movw %%ax, 0xc(%%esi)\n\t"
      "movw %%ax, 0xe(%%esi)\n\t"
      "movb 0x28(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00061080_1\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fsubs 0x1c(%%ebp)\n\t"
      "fstps (%%esi)\n\t"
      ".LFUN_00061080_1:\n\t"
      "movb 0x24(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00061080_4\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "leal -0x3c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c63710]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00061080_2\n\t"
      "flds (%%esi)\n\t"
      "fcomps -0x3c(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00061080_2\n\t"
      "movl -0x3c(%%ebp), %%eax\n\t"
      "movl -0x34(%%ebp), %%ecx\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl %%ecx, 0x8(%%esi)\n\t"
      ".LFUN_00061080_2:\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c10b600]\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x1c(%%ebp)\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fadds (%%edi)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "flds -0x4(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "fmuls 0x1c(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "fadds 0x4(%%edi)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "call *%[c63710]\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c63710]\n\t"
      "addl $0x40, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00061080_3\n\t"
      "flds (%%esi)\n\t"
      "fcomps -0x24(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00061080_3\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl %%ecx, 0x8(%%esi)\n\t"
      ".LFUN_00061080_3:\n\t"
      "flds 0x1c(%%ebp)\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "fchs\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "flds -0x8(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "fadds (%%edi)\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "flds -0x4(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "fadds 0x4(%%edi)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[c63710]\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl -0x2c(%%ebp), %%ecx\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c63710]\n\t"
      "addl $0x38, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00061080_4\n\t"
      "flds (%%esi)\n\t"
      "fcomps -0x30(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00061080_4\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movl %%edx, (%%esi)\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      ".LFUN_00061080_4:\n\t"
      "movl 0x2c(%%ebp), %%edx\n\t"
      "movl (%%esi), %%eax\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c624b0]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00061080_5\n\t"
      "flds (%%esi)\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00061080_5\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movw -0x4(%%ebp), %%dx\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movw -0x2(%%ebp), %%cx\n\t"
      "movl $0xffffffff, %%eax\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "movw %%dx, 0xc(%%esi)\n\t"
      "movw %%cx, 0xe(%%esi)\n\t"
      "jmp .LFUN_00061080_6\n\t"
      ".LFUN_00061080_5:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      ".LFUN_00061080_6:\n\t"
      "cmpl %%eax, 0x8(%%esi)\n\t"
      "jne .LFUN_00061080_7\n\t"
      "cmpw %%ax, 0xc(%%esi)\n\t"
      "jne .LFUN_00061080_7\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "movb $0, 0x2b(%%ebp)\n\t"
      "movl %%edx, (%%esi)\n\t"
      "jmp .LFUN_00061080_8\n\t"
      ".LFUN_00061080_7:\n\t"
      "movb $1, 0x2b(%%ebp)\n\t"
      ".LFUN_00061080_8:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c63710]\n\t"
      "movl -0x38(%%ebp), %%edx\n\t"
      "movb 0x2b(%%ebp), %%al\n\t"
      "addl $0x1c, %%esp\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "popl %%esi\n\t"
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
      :
      : [c63710] "m"(b61080_c63710), [c10b600] "m"(b61080_c10b600), [c624b0] "m"(b61080_c624b0)
      : "memory");
}
#else
#error "FUN_00061080: clang naked draft required"
#endif


/* path_add_steps (0x61280) — XBE naked draft (batch 221). */
#if defined(__clang__)
static void (*const b61280_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b61280_exitfn)(int) = system_exit;
static void *(*const b61280_memset)(void *, int, unsigned int) = csmemset;
static void (*const b61280_c625a0)(void *obstacles, short disc_index, float *point, float base_value, float *out_b, float *out_a, float *out_scalar) = FUN_000625a0;
static void (*const b61280_c61080)(void *structure_bsp, unsigned char path_surface_flag, void *obstacles, int16_t disc_index, int surface_hint, float max_cost, float ray_t, unsigned char skip_ray_march, unsigned char use_cost_delta, char check_extant, void *out_result, float *step_data, float *direction) = FUN_00061080;
static char (*const b61280_c63710)(void *structure_bsp, char ignore_breakable, float *point, int surface_index, float *direction, float t, void *out_result) = structure_test_ray2d;
static int16_t (*const b61280_c60c80)(void *path, float *delta, int16_t zone_index, char surface_flag, float step_cost, int16_t parent_step) = path_add_step;

__attribute__((naked, noinline))
void path_add_steps(void *path __attribute__((unused)), int16_t seed_disc_index __attribute__((unused)), int16_t step_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x160, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testw %%di, %%di\n\t"
      "movw %%ax, %%bx\n\t"
      "jl .Lpath_add_steps_1\n\t"
      "movw 0x2c(%%esi), %%ax\n\t"
      "cmpw %%ax, %%di\n\t"
      "jge .Lpath_add_steps_1\n\t"
      "cmpw $0x80, %%ax\n\t"
      "jle .Lpath_add_steps_2\n\t"
      ".Lpath_add_steps_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x28\n\t"
      "pushl $0x25ea14\n\t"
      "pushl $0x25e9b0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpath_add_steps_2:\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movswl %%di, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%eax\n\t"
      "leal 0x30(%%esi,%%eax,8), %%ecx\n\t"
      "movw 0x2(%%edx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "jl .Lpath_add_steps_3\n\t"
      "cmpw $0x80, %%ax\n\t"
      "jle .Lpath_add_steps_4\n\t"
      ".Lpath_add_steps_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x252\n\t"
      "pushl $0x25ea14\n\t"
      "pushl $0x25ec60\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpath_add_steps_4:\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movswl 0x2(%%eax), %%ecx\n\t"
      "addl $0x1f, %%ecx\n\t"
      "sarl $5, %%ecx\n\t"
      "shll $2, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x54(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .Lpath_add_steps_5\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "cmpw 0x2(%%eax), %%bx\n\t"
      "jl .Lpath_add_steps_6\n\t"
      ".Lpath_add_steps_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x255\n\t"
      "pushl $0x25ea14\n\t"
      "pushl $0x25ec18\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpath_add_steps_6:\n\t"
      "movswl %%bx, %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "sarl $5, %%edx\n\t"
      "leal -0x54(%%ebp,%%edx,4), %%eax\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movw %%bx, -0x160(%%ebp)\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl $1, %%eax\n\t"
      "jmp .Lpath_add_steps_8\n\t"
      ".Lpath_add_steps_7:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "jmp .Lpath_add_steps_8\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lpath_add_steps_8:\n\t"
      "movl 0x8(%%esi), %%ebx\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "movw -0x160(%%ebp,%%eax,2), %%di\n\t"
      "cmpw $-1, %%di\n\t"
      "movl %%edi, -0x1c(%%ebp)\n\t"
      "je .Lpath_add_steps_11\n\t"
      "testw %%di, %%di\n\t"
      "jl .Lpath_add_steps_9\n\t"
      "movw 0x2(%%ebx), %%ax\n\t"
      "cmpw %%ax, %%di\n\t"
      "jge .Lpath_add_steps_9\n\t"
      "cmpw $0x80, %%ax\n\t"
      "jle .Lpath_add_steps_10\n\t"
      ".Lpath_add_steps_9:\n\t"
      "pushl $1\n\t"
      "pushl $0x18c\n\t"
      "pushl $0x25e990\n\t"
      "pushl $0x25e930\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpath_add_steps_10:\n\t"
      "movswl %%di, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "movw 0xa(%%ebx,%%ecx,8), %%dx\n\t"
      "movw %%dx, -0x10(%%ebp)\n\t"
      "jmp .Lpath_add_steps_12\n\t"
      ".Lpath_add_steps_11:\n\t"
      "movl $0xffffffff, -0x10(%%ebp)\n\t"
      ".Lpath_add_steps_12:\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl (%%esi), %%eax\n\t"
      "leal -0x3c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "leal -0x44(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c625a0]\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps (%%esi)\n\t"
      "addl $0x1c, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lpath_add_steps_13\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".Lpath_add_steps_13:\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "leal -0x44(%%ebp), %%ebx\n\t"
      "jmp .Lpath_add_steps_15\n\t"
      ".Lpath_add_steps_14:\n\t"
      "movl -0x1c(%%ebp), %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lpath_add_steps_15:\n\t"
      "flds (%%esi)\n\t"
      "movl (%%esi), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "movb 0x2a(%%esi), %%dl\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x4(%%esi), %%cl\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c61080]\n\t"
      "movl -0x28(%%ebp), %%edi\n\t"
      "addl $0x2c, %%esp\n\t"
      "cmpw $-1, %%di\n\t"
      "je .Lpath_add_steps_19\n\t"
      "testw %%di, %%di\n\t"
      "jl .Lpath_add_steps_16\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "cmpw 0x2(%%eax), %%di\n\t"
      "jl .Lpath_add_steps_17\n\t"
      ".Lpath_add_steps_16:\n\t"
      "pushl $1\n\t"
      "pushl $0x271\n\t"
      "pushl $0x25ea14\n\t"
      "pushl $0x25ebd0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpath_add_steps_17:\n\t"
      "movswl %%di, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "sarl $5, %%eax\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "leal -0x54(%%ebp,%%eax,4), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "testl %%eax, %%edx\n\t"
      "jne .Lpath_add_steps_19\n\t"
      "orl %%edx, %%eax\n\t"
      "cmpw $0x80, -0x8(%%ebp)\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "jl .Lpath_add_steps_18\n\t"
      "pushl $1\n\t"
      "pushl $0x277\n\t"
      "pushl $0x25ea14\n\t"
      "pushl $0x25ebb0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpath_add_steps_18:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "incl %%eax\n\t"
      "movw %%di, -0x160(%%ebp,%%ecx,2)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".Lpath_add_steps_19:\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fcomps -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lpath_add_steps_20\n\t"
      "movw -0x10(%%ebp), %%dx\n\t"
      "cmpw %%dx, -0x26(%%ebp)\n\t"
      "je .Lpath_add_steps_20\n\t"
      "flds -0x34(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "leal -0x60(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fmuls 0x253398\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x4(%%esi), %%al\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c63710]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls (%%ebx)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "addl $0x1c, %%esp\n\t"
      "fadds (%%edi)\n\t"
      "pushl %%edx\n\t"
      "movl -0x5c(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      "fadds 0x4(%%edi)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds 0x20(%%edi)\n\t"
      "fsubs 0x14(%%edi)\n\t"
      "movl %%esi, %%edi\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c60c80]\n\t"
      "addl $0x18, %%esp\n\t"
      ".Lpath_add_steps_20:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "addl $8, %%ebx\n\t"
      "cmpw $2, %%ax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "jl .Lpath_add_steps_14\n\t"
      "cmpw $0, -0x8(%%ebp)\n\t"
      "jg .Lpath_add_steps_7\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b61280_assert), [exitfn] "m"(b61280_exitfn), [memset] "m"(b61280_memset), [c625a0] "m"(b61280_c625a0), [c61080] "m"(b61280_c61080), [c63710] "m"(b61280_c63710), [c60c80] "m"(b61280_c60c80)
      : "memory");
}
#else
#error "path_add_steps: clang naked draft required"
#endif


/* 0x615b0 */
int FUN_000615b0(void *avoidance_record)
{
  int16_t step_index;
  char *step;
  float target_point[2];
  float step_cost;
  float scale;

  step_index = FUN_00060970(avoidance_record);
  if (step_index == -1)
    return 0;

  step = (char *)FUN_000600f0(avoidance_record, step_index);
  if (*(int16_t *)(step + 0x24) == -1)
    scale = *(float *)((char *)avoidance_record + 0x18);
  else
    scale = *(float *)(step + 0x20) - *(float *)(step + 0x14) +
            *(float *)((char *)avoidance_record + 0x18);

  target_point[0] = *(float *)(step + 0xc) * scale + *(float *)step;
  target_point[1] = *(float *)(step + 0x10) * scale + *(float *)(step + 4);
  step_cost = *(float *)(step + 0x20) - *(float *)(step + 0x14) + scale;

  path_add_step(avoidance_record, target_point,
                *(int16_t *)((char *)avoidance_record + 0x1c), 0, step_cost,
                -1);
  *(int16_t *)((char *)avoidance_record + 0x1e) = step_index;

  if (*(int16_t *)((char *)avoidance_record + 0x1e) == -1 &&
      *(int16_t *)((char *)avoidance_record + 0x1430) > 0)
    return 1;
  return 0;
}

/* 0x616e0 — Seed avoidance search then drain heap via FUN_000615b0. */
char FUN_000616e0(void *avoidance_record, unsigned char path_flag,
                  void *param_3, void *param_4, void *param_5, void *param_6,
                  float *end_point, unsigned char param_8)
{
  void *scenario;

  (void)param_3;
  (void)param_4;
  (void)param_5;
  (void)param_6;

  scenario = scenario_get();
  FUN_00060ea0(avoidance_record, end_point, param_5, scenario, path_flag,
               *(float *)((char *)avoidance_record + 0x18),
               (float *)((char *)avoidance_record + 0x10), 0, 0.0f,
               *(unsigned char *)((char *)avoidance_record + 0x29), param_8);

  while (FUN_000615b0(avoidance_record))
    ;

  if (*(int16_t *)((char *)avoidance_record + 0x1e) == -1) {
    if (*(int16_t *)((char *)avoidance_record + 0x20) != -1)
      *(int16_t *)((char *)avoidance_record + 0x1e) =
          *(int16_t *)((char *)avoidance_record + 0x20);
    return (char)(*(int16_t *)((char *)avoidance_record + 0x1e) != -1);
  }

  *(char *)((char *)avoidance_record + 0x28) = 1;
  return 1;
}

/* 0x61750 — run obstacle avoidance over smoothed path segments. */
char FUN_00061750(unsigned int param_1, int param_2, void *param_3,
                  int *param_4, void *param_5, char *param_6)
{
  char *path;
  char *smooth_steps;
  char *out_bytes;
  char *debug_state;
  void *collision_bsp;
  float search_radius;
  int16_t smooth_count;
  int16_t segment_index;
  char all_nodes;
  char avoidance_record[0x1440];
  int16_t obstacle_partition[0x628];
  float delta[3];
  float ref_point[3];
  float cur_point[3];
  float segment_length;
  float inv_length;
  int16_t obstacle_step;
  int16_t out_slot;
  void *obstacles;
  void *scenario;
  char try_all_nodes;
  char found_segment;
  uint8_t temp_steps[0x80 * 16];

  path = (char *)(uintptr_t)param_1;
  smooth_steps = (char *)param_3;
  out_bytes = (char *)param_5;
  smooth_count = (int16_t)param_2;

  collision_bsp = global_collision_bsp_get();

  if ((*(uint32_t *)path & 0x7f800000U) != 0x7f800000U &&
      *(float *)path <= *(float *)0x2549d4)
    search_radius = *(float *)path;
  else
    search_radius = 0.2f;

  debug_state = *(char **)(path + 0x48);
  if (debug_state != NULL && *(char *)(debug_state + 0x14588) == 0) {
    if (smooth_count > 4) {
      display_assert("input_step_count <= MAXIMUM_SMOOTHED_PATH_STEPS",
                     "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 761, 1);
      system_exit(-1);
    }
    *(int16_t *)(debug_state + 0x1458a) = 0;
  }

  if (smooth_count <= 0)
    return 0;

  segment_index = 0;
  all_nodes = 0;

  while (segment_index < smooth_count) {
    float *prev_pt;
    float *cur_pt_ptr;

    try_all_nodes = 0;
    if (segment_index == smooth_count - 1 && *param_6 != 0)
      try_all_nodes = 1;

    if (segment_index > 0) {
      prev_pt = ref_point;
    } else {
      prev_pt = *(float **)(path + 0x20);
      if (prev_pt == NULL)
        prev_pt = (float *)(path + 0x10);
    }

    cur_pt_ptr =
        (float *)(smooth_steps + (int)segment_index * 16);
    cur_point[0] = cur_pt_ptr[0];
    cur_point[1] = cur_pt_ptr[1];
    cur_point[2] = cur_pt_ptr[2];

    delta[0] = cur_point[0] - prev_pt[0];
    delta[1] = cur_point[1] - prev_pt[1];
    delta[2] = cur_point[2] - prev_pt[2];
    segment_length =
        sqrtf(delta[1] * delta[1] + delta[2] * delta[2] + delta[0] * delta[0]);

    if (fabs(segment_length) >= *(double *)0x2533d0) {
      inv_length = *(float *)0x2533c8 / segment_length;
      delta[0] = delta[0] * inv_length;
      delta[1] = delta[1] * inv_length;
      delta[2] = delta[2] * inv_length;
    }

    if (debug_state != NULL && *(char *)(debug_state + 0x14588) != 0 &&
        segment_index < *(int16_t *)(debug_state + 0x1458a))
      goto next_segment;

    obstacles = *(void **)(path + 8);
    scenario = *(void **)(path + 0xc);
    FUN_00061d80(obstacle_partition);
    obstacles_get_discs_in_sphere(obstacle_partition, prev_pt, 4.0f, delta,
                                  obstacles, scenario);

    if (*(char *)(path + 0x24) != 0) {
      FUN_00062020(obstacle_partition, *(uint32_t *)(path + 0x34),
                     *(uint16_t *)(path + 0x38),
                     (float *)(path + 0x28), 0);
    }

    FUN_000628b0(obstacle_partition, *(uint32_t *)&search_radius);

    if (debug_state != NULL && *(char *)(debug_state + 0x14588) == 0)
      *(int16_t *)(debug_state + 0x1458a) = segment_index + 1;

    csmemset(avoidance_record, 0, sizeof(avoidance_record));
    scenario = scenario_get();
    FUN_00060ea0(avoidance_record, cur_point, obstacles, scenario,
                 *(unsigned char *)(path + 4), search_radius, prev_pt, 0, 0.0f,
                 try_all_nodes, 0);

    while (FUN_000615b0(avoidance_record))
      ;

    found_segment = 0;
    if (*(int16_t *)(avoidance_record + 0x1e) != -1)
      found_segment = 1;
    else if (*(int16_t *)(avoidance_record + 0x20) != -1) {
      *(int16_t *)(avoidance_record + 0x1e) =
          *(int16_t *)(avoidance_record + 0x20);
      found_segment = 1;
    }

    if (!found_segment && obstacle_partition[2] > 0) {
      found_segment = FUN_000616e0(
          avoidance_record, 1, prev_pt, ref_point, obstacles, obstacle_partition,
          cur_point, try_all_nodes);
    }

    if (!found_segment)
      return 0;

    if (*(char *)(avoidance_record + 0x28) != 0) {
      ref_point[0] = cur_point[0];
      ref_point[1] = cur_point[1];
      ref_point[2] = cur_point[2];
    } else {
      obstacle_step = *(int16_t *)(avoidance_record + 0x1e);
      if (obstacle_step < 0 ||
          obstacle_step >= *(int16_t *)(avoidance_record + 0x2c) ||
          *(int16_t *)(avoidance_record + 0x2c) > 0x80) {
        display_assert("step_index>=0 && step_index<path->step_count && "
                       "path->step_count<=MAXIMUM_OBSTACLE_AVOIDANCE_STEPS",
                       "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 40, 1);
        system_exit(-1);
      }
      {
        char *step =
            (char *)FUN_000600f0(avoidance_record, obstacle_step);
        collision_surface_project_point2d((int)collision_bsp,
                                          *(int *)(step + 8), 2, 1,
                                          (float *)step, ref_point);
      }
    }

    out_slot = 0;
    obstacle_step = *(int16_t *)(avoidance_record + 0x1e);
    if (obstacle_step != 0) {
      for (;;) {
        char *step;

        if (obstacle_step < 0 ||
            obstacle_step >= *(int16_t *)(avoidance_record + 0x2c) ||
            *(int16_t *)(avoidance_record + 0x2c) > 0x80) {
          display_assert("step_index>=0 && step_index<path->step_count && "
                         "path->step_count<=MAXIMUM_OBSTACLE_AVOIDANCE_STEPS",
                         "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 40,
                         1);
          system_exit(-1);
        }

        step = (char *)FUN_000600f0(avoidance_record, obstacle_step);
        collision_surface_project_point2d((int)collision_bsp, *(int *)(step + 8),
                                          2, 1, (float *)step,
                                          (float *)(temp_steps + out_slot * 16 + 4));

        *(uint32_t *)(temp_steps + out_slot * 16) =
            *(uint32_t *)(step + 0xc);
        *(uint32_t *)(temp_steps + out_slot * 16 + 8) =
            *(uint32_t *)(step + 0x10);
        *(uint32_t *)(temp_steps + out_slot * 16 + 12) =
            *(uint32_t *)(step + 0x14);

        out_slot++;
        if (out_slot >= 0x80) {
          all_nodes = 1;
          break;
        }

        obstacle_step = *(int16_t *)(step + 0x24);
        if (obstacle_step < 0 ||
            obstacle_step >= *(int16_t *)(avoidance_record + 0x2c)) {
          display_assert("(obstacle_step_index >= 0) && "
                         "(obstacle_step_index < obstacle_path->step_count)",
                         "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 875,
                         1);
          system_exit(-1);
        }
        if (obstacle_step == 0)
          break;
      }
    }

    if (!all_nodes) {
      int16_t copy_index;
      int16_t out_index;

      out_index = *(int16_t *)param_4;
      copy_index = (int16_t)(out_slot - 1);
      while (copy_index >= 0 && out_index < 4) {
        csmemcpy(out_bytes + (int)out_index * 16,
                 temp_steps + (int)copy_index * 16, 16);
        out_index++;
        copy_index--;
      }
      *(int16_t *)param_4 = out_index;
    } else {
      all_nodes = 1;
    }

  next_segment:
    segment_index++;
  }

  if (all_nodes) {
    *param_6 = 0;
    return 1;
  }

  return 1;
}
