/* bipeds.c — biped-specific unit functions.
 *
 * Corresponds to bipeds.obj. Functions sorted by XBE address.
 * Debug assertion path: c:\halo\SOURCE\units\bipeds.c
 */

#include "../../common.h"
#include "../../x87_math.h"

/* FUN_001a01d0 (0x1a01d0)
 *
 * Builds an orthonormal forward/left/up basis (biped_limp_noodle.c:0x217).
 * Each supplied vector is normalized; a zero-length vector is replaced by the
 * matching global world axis. The left and up vectors are then rebuilt via
 * cross products to enforce orthogonality, renormalizing (with axis fallback)
 * after each rebuild.
 *
 * Confirmed: CALL 0x13010 (normalize3d) returns the length; length 0.0 selects
 * the fallback axis. Globals: 0x31fc3c forward, 0x31fc40 left, 0x31fc44 up.
 * Cross products: left = up x forward, up = forward x left, left = up x forward
 * (operand order transcribed from disassembly).
 */
void FUN_001a01d0(float *forward, float *left, float *up)
{
  float lc0;
  float lc1;
  float lc2;

  if (forward == NULL) {
    display_assert("forward", "c:\\halo\\SOURCE\\units\\biped_limp_noodle.c",
                   0x217, true);
    system_exit(-1);
  }
  if (left == NULL) {
    display_assert("left", "c:\\halo\\SOURCE\\units\\biped_limp_noodle.c",
                   0x217, true);
    system_exit(-1);
  }
  if (up == NULL) {
    display_assert("up", "c:\\halo\\SOURCE\\units\\biped_limp_noodle.c", 0x217,
                   true);
    system_exit(-1);
  }

  if (normalize3d(forward) == 0.0f) {
    forward[0] = global_forward_vector_ptr[0];
    forward[1] = global_forward_vector_ptr[1];
    forward[2] = global_forward_vector_ptr[2];
  }
  if (normalize3d(up) == 0.0f) {
    up[0] = global_up_vector_ptr[0];
    up[1] = global_up_vector_ptr[1];
    up[2] = global_up_vector_ptr[2];
  }

  /* left = up x forward. All three components are computed before any store
   * (the original cannot assume left[] doesn't alias forward[]/up[], so it
   * batches the cross product onto the x87 stack, then stores [0],[1],[2]). */
  lc2 = forward[1] * up[0] - up[1] * forward[0];
  lc1 = up[2] * forward[0] - forward[2] * up[0];
  lc0 = up[1] * forward[2] - up[2] * forward[1];
  left[0] = lc0;
  left[1] = lc1;
  left[2] = lc2;
  if (normalize3d(left) == 0.0f) {
    left[0] = global_left_vector_ptr[0];
    left[1] = global_left_vector_ptr[1];
    left[2] = global_left_vector_ptr[2];
  }

  /* up = forward x left */
  lc2 = left[1] * forward[0] - forward[1] * left[0];
  lc1 = forward[2] * left[0] - forward[0] * left[2];
  lc0 = forward[1] * left[2] - left[1] * forward[2];
  up[0] = lc0;
  up[1] = lc1;
  up[2] = lc2;
  if (normalize3d(up) == 0.0f) {
    up[0] = global_up_vector_ptr[0];
    up[1] = global_up_vector_ptr[1];
    up[2] = global_up_vector_ptr[2];
  }

  /* left = up x forward */
  lc2 = forward[1] * up[0] - up[1] * forward[0];
  lc1 = up[2] * forward[0] - forward[2] * up[0];
  lc0 = up[1] * forward[2] - up[2] * forward[1];
  left[0] = lc0;
  left[1] = lc1;
  left[2] = lc2;
  if (normalize3d(left) == 0.0f) {
    left[0] = global_left_vector_ptr[0];
    left[1] = global_left_vector_ptr[1];
    left[2] = global_left_vector_ptr[2];
  }
}

/* FUN_001a03c0 (0x1a03c0) — XBE naked draft (batch 51). */
#if defined(__clang__)
static void *(*const b1a03c0_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a03c0_tag)(int, int) = tag_get;
static void *(*const b1a03c0_elem)(void *, int, int) = tag_block_get_element;
static float (*const b1a03c0_norm)(float *) = normalize3d;
static void (*const b1a03c0_c1d94f0)(void) = FUN_001d94f0;
static char (*const b1a03c0_cf6c40)(float *a, float *b, float *c) = valid_real_vector3d_axes3;
static void (*const b1a03c0_c1a01d0)(float *forward, float *left, float *up) = FUN_001a01d0;
static void (*const b1a03c0_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;
static void (*const b1a03c0_cross)(float *, float *, float *) = cross_product3d;
static void * (*const b1a03c0_c13dfc0)(int object_handle, void *reference) = object_header_block_reference_get;
static void (*const b1a03c0_c19fa20)(int unit_handle, void *node_block) = FUN_0019fa20;
static void (*const b1a03c0_c1a03c0)(int unit_handle, int node_count, float *positions, void *nodes) = FUN_001a03c0;
static void (*const b1a03c0_c1b24d0)(int unit_handle, void *placement) = unit_place;
static void (*const b1a03c0_c13d870)(int unit_handle, void *data) = FUN_0013d870;
static void *(*const b1a03c0_memset)(void *, int, unsigned int) = csmemset;

__attribute__((naked, noinline))
void FUN_001a03c0(int unit_handle __attribute__((unused)), int node_count __attribute__((unused)), float *positions __attribute__((unused)), void *nodes __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x44, %%esp\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movl 0x44(%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x616e7472\n\t"
      "call *%[tag]\n\t"
      "movl 0x68(%%eax), %%edx\n\t"
      "addl $0x68, %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%edx, %%edx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "jle .LFUN_001a03c0_5\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "addl $8, %%ebx\n\t"
      "leal 0x30(%%edi), %%edx\n\t"
      "pushl %%esi\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      ".LFUN_001a03c0_1:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_001a03c0_4\n\t"
      "pushl $0x40\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl 0x24(%%esi), %%eax\n\t"
      "pushl $0x40\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movb 0x28(%%eax), %%cl\n\t"
      "addl $0x18, %%esp\n\t"
      "testb $4, %%cl\n\t"
      "jne .LFUN_001a03c0_4\n\t"
      "movswl 0x24(%%esi), %%eax\n\t"
      "flds -0x8(%%ebx)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "imull $0x34, %%eax, %%eax\n\t"
      "fsubs (%%ecx,%%edx,4)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds -0x4(%%ebx)\n\t"
      "fsubs 0x4(%%ecx,%%edx,4)\n\t"
      "leal (%%ecx,%%edx,4), %%ecx\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds (%%ebx)\n\t"
      "leal 0x28(%%eax,%%edi,1), %%eax\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "fsubs 0x8(%%ecx)\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds -0x8(%%ecx)\n\t"
      "fsubs (%%eax)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds -0x4(%%ecx)\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds (%%ecx)\n\t"
      "fsubs 0x8(%%eax)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "leal -0x44(%%ebp), %%ecx\n\t"
      "fmuls -0x34(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x34(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fsubs 0x2533c8\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001a03c0_4\n\t"
      "flds -0x4(%%ebp)\n\t"
      "call *%[c1d94f0]\n\t"
      "fsts -0x14(%%ebp)\n\t"
      "fabs\n\t"
      "fcoml 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001a03c0_6\n\t"
      "fcompl 0x25b3f0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a03c0_4\n\t"
      "movswl 0x24(%%esi), %%edx\n\t"
      "imull $0x34, %%edx, %%edx\n\t"
      "leal (%%edx,%%edi,1), %%eax\n\t"
      "leal 0x1c(%%eax), %%ebx\n\t"
      "leal 0x10(%%eax), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[cf6c40]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a03c0_2\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1a01d0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001a03c0_2:\n\t"
      "flds -0x14(%%ebp)\n\t"
      "movswl 0x24(%%esi), %%ecx\n\t"
      "fsin\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "imull $0x34, %%ecx, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "leal -0x44(%%ebp), %%eax\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x4(%%ecx,%%edi,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[rots]\n\t"
      "movswl 0x24(%%esi), %%edx\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "imull $0x34, %%edx, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "leal -0x44(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x1c(%%edx,%%edi,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[rots]\n\t"
      "movswl 0x24(%%esi), %%ecx\n\t"
      "imull $0x34, %%ecx, %%ecx\n\t"
      "leal 0x4(%%ecx,%%edi,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[norm]\n\t"
      "movswl 0x24(%%esi), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "imull $0x34, %%eax, %%eax\n\t"
      "leal 0x1c(%%eax,%%edi,1), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[norm]\n\t"
      "movswl 0x24(%%esi), %%edx\n\t"
      "fstp %%st(0)\n\t"
      "imull $0x34, %%edx, %%edx\n\t"
      "leal (%%edx,%%edi,1), %%eax\n\t"
      "leal 0x10(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x4(%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl $0x1c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[cross]\n\t"
      "movswl 0x24(%%esi), %%eax\n\t"
      "imull $0x34, %%eax, %%eax\n\t"
      "leal 0x10(%%eax,%%edi,1), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[norm]\n\t"
      "movswl 0x24(%%esi), %%edx\n\t"
      "fstp %%st(0)\n\t"
      "imull $0x34, %%edx, %%edx\n\t"
      "leal (%%edx,%%edi,1), %%eax\n\t"
      "leal 0x1c(%%eax), %%esi\n\t"
      "leal 0x10(%%eax), %%ebx\n\t"
      "pushl %%esi\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[cf6c40]\n\t"
      "addl $0x44, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a03c0_3\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a01d0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001a03c0_3:\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      ".LFUN_001a03c0_4:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "incl %%ecx\n\t"
      "addl $0xc, %%ebx\n\t"
      "addl $0x34, %%esi\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "jl .LFUN_001a03c0_1\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001a03c0_5:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a03c0_6:\n\t"
      "fstp %%st(0)\n\t"
      "jmp .LFUN_001a03c0_4\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movl 0x44(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x616e7472\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "call *%[get]\n\t"
      "addl $0x1a0, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c13dfc0]\n\t"
      "movb 0x47d(%%esi), %%cl\n\t"
      "movb 0x47c(%%esi), %%dl\n\t"
      "addl $0x28, %%esp\n\t"
      "cmpb %%cl, %%dl\n\t"
      "sbbb %%cl, %%cl\n\t"
      "incb %%cl\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movb %%cl, -0x1(%%ebp)\n\t"
      "jne .LFUN_001a03c0_10\n\t"
      "movl 0x68(%%edi), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "jle .LFUN_001a03c0_8\n\t"
      "movl $0x4e49f0, %%ecx\n\t"
      "addl $0x28, %%eax\n\t"
      ".LFUN_001a03c0_7:\n\t"
      "movl %%eax, %%edx\n\t"
      "movl (%%edx), %%ebx\n\t"
      "movl %%ecx, %%edi\n\t"
      "movl %%ebx, (%%edi)\n\t"
      "movl 0x4(%%edx), %%ebx\n\t"
      "movl %%ebx, 0x4(%%edi)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl 0x68(%%edi), %%ebx\n\t"
      "incl %%edx\n\t"
      "addl $0x34, %%eax\n\t"
      "addl $0xc, %%ecx\n\t"
      "cmpl %%ebx, %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jl .LFUN_001a03c0_7\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      ".LFUN_001a03c0_8:\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c19fa20]\n\t"
      "movl 0x68(%%edi), %%eax\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      "pushl $0x4e49f0\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c1a03c0]\n\t"
      "movb 0x47c(%%esi), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpb $0x7f, %%al\n\t"
      "jae .LFUN_001a03c0_9\n\t"
      "incb %%al\n\t"
      "movb %%al, 0x47c(%%esi)\n\t"
      ".LFUN_001a03c0_9:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a03c0_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%cl, %%al\n\t"
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
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "leal 0x48(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c1b24d0]\n\t"
      "addl $0x28, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c13d870]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
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
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl $0x5c\n\t"
      "leal 0x424(%%esi), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "movl 0x32513c, %%eax\n\t"
      "leal 0x46c(%%esi), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x325140, %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x325144, %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl 0x325148, %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $0xffffffff, 0x450(%%esi)\n\t"
      "movl %%ecx, 0xc(%%edx)\n\t"
      "popl %%esi\n\t"
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
      :
      : [get] "m"(b1a03c0_get), [tag] "m"(b1a03c0_tag), [elem] "m"(b1a03c0_elem), [norm] "m"(b1a03c0_norm), [c1d94f0] "m"(b1a03c0_c1d94f0), [cf6c40] "m"(b1a03c0_cf6c40), [c1a01d0] "m"(b1a03c0_c1a01d0), [rots] "m"(b1a03c0_rots), [cross] "m"(b1a03c0_cross), [c13dfc0] "m"(b1a03c0_c13dfc0), [c19fa20] "m"(b1a03c0_c19fa20), [c1a03c0] "m"(b1a03c0_c1a03c0), [c1b24d0] "m"(b1a03c0_c1b24d0), [c13d870] "m"(b1a03c0_c13d870), [memset] "m"(b1a03c0_memset)
      : "memory");
}
#else
#error "FUN_001a03c0: clang naked draft required"
#endif


/* FUN_001a0680 (0x1a0680)
 *
 * Updates biped limp-noodle (ragdoll/physics) node positions. Gets the biped
 * object and its 'bipd' tag, then looks up the 'antr' animation tag via the
 * tag reference at bipd+0x44. Fetches the object header block reference at
 * offset object+0x1a0 (the node transform block). Returns 1 if the current
 * node step count (byte at biped_obj+0x47c) >= the maximum step count (byte
 * at biped_obj+0x47d); otherwise copies node positions into the scratch buffer
 * at 0x4e49f0, calls FUN_0019fa20 to process limp-noodle physics, calls
 * FUN_001a03c0 to apply the updated positions back, increments the step
 * counter (capped at 0x7f), and returns 0.
 *
 * Confirmed: CALL 0x13d680 (object_get_and_verify_type) type 1 (biped).
 * Confirmed: CALL 0x1ba140 (tag_get) 'bipd' (0x62697064) then 'antr'
 * (0x616e7472). Confirmed: CALL 0x13dfc0 (object_header_block_reference_get)
 * offset +0x1a0. Confirmed: comparison [ESI+0x47c] vs [ESI+0x47d] (CMP/SBB/INC
 * pattern). Confirmed: node stride 0x34 (13 floats), position offset +0x28
 * within node. Confirmed: scratch buffer at 0x4e49f0 (DAT_004e49f0). Confirmed:
 * antr node count at antr+0x68. Confirmed: step counter cap at 0x7f (JNC =
 * unsigned compare). Inferred: FUN_001a03c0 @<eax>=unit_handle,
 * @<edi>=node_block_ptr.
 */
char FUN_001a0680(int unit_handle)
{
  char *biped_obj;
  char *bipd_tag;
  char *antr_tag;
  void *node_block;
  char *obj_base;
  int count;
  int i;
  int *src_node;
  int *scratch;
  char result;

  biped_obj = (char *)object_get_and_verify_type(unit_handle, 1);
  bipd_tag = (char *)tag_get(0x62697064, *(int *)biped_obj);
  antr_tag = (char *)tag_get(0x616e7472, *(int *)(bipd_tag + 0x44));
  obj_base = (char *)object_get_and_verify_type(unit_handle, -1);
  node_block = object_header_block_reference_get(unit_handle, obj_base + 0x1a0);

  /* CMP [ESI+0x47c],[ESI+0x47d]; SBB CL,CL; INC CL */
  result = (char)(*(unsigned char *)(biped_obj + 0x47c) >=
                  *(unsigned char *)(biped_obj + 0x47d));
  if (result != '\0') {
    return result;
  }

  count = *(int *)((char *)antr_tag + 0x68);
  if (count > 0) {
    scratch = (int *)0x4e49f0;
    src_node = (int *)((char *)node_block + 0x28);
    i = 0;
    do {
      scratch[0] = src_node[0];
      scratch[1] = src_node[1];
      scratch[2] = src_node[2];
      i++;
      src_node += (0x34 / 4); /* advance by 0x34 bytes (13 ints) */
      scratch += 3;
    } while (i < count);
  }

  FUN_0019fa20(unit_handle, node_block);
  /* @<eax>=unit_handle, node_count, positions=scratch buf, @<edi>=node_block */
  FUN_001a03c0(unit_handle, *(int *)((char *)antr_tag + 0x68),
               (float *)0x4e49f0, node_block);

  if (*(unsigned char *)(biped_obj + 0x47c) < 0x7f) {
    *(unsigned char *)(biped_obj + 0x47c) =
      *(unsigned char *)(biped_obj + 0x47c) + 1;
  }
  return result;
}

/* biped_place (0x1a07c0)
 *
 * Places a biped unit at a placement location. Calls unit_place with the
 * placement data at offset +0x48 (the unit-level placement struct), then
 * calls FUN_0013d870 (no-op stub) with the placement data at offset +0x28.
 *
 * Confirmed: param_2+0x48 passed to unit_place (PUSH ESI+0x48 via LEA).
 * Confirmed: param_2+0x28 passed to FUN_0013d870 (ADD ESI,0x28; PUSH ESI).
 * Confirmed: FUN_0013d870 is a no-op (single RET).
 * Inferred: param_2 is a biped placement struct (unit placement at +0x48,
 *   biped-specific data at +0x28).
 */
void biped_place(int unit_handle, void *placement)
{
  unit_place(unit_handle, (char *)placement + 0x48);
  FUN_0013d870(unit_handle, (char *)placement + 0x28);
}

/* biped_reset (0x1a0800)
 *
 * Resets biped physics/state fields to default values. Clears 0x5c bytes
 * starting at obj+0x424, then restores four default float constants from
 * 0x32513c..0x325148 into obj+0x46c..0x478, and sets obj+0x450 = -1.
 *
 * Confirmed: csmemset(obj+0x424, 0, 0x5c) clears the full state block.
 * Confirmed: store offsets from disasm: obj+0x46c, +0x470, +0x474, +0x478
 *   loaded from globals 0x32513c, 0x325140, 0x325144, 0x325148.
 * Confirmed: obj+0x450 = 0xffffffff (OR ECX,-1 pattern; int -1).
 * Confirmed: MSVC schedules obj+0x450 between the 3rd and 4th const stores;
 *   written naturally here, VC71 reschedules.
 * Inferred: the four constants are default float values (0.0, 0.0, 1.0,
 *   -256.0 from memory at 0x32513c).
 */
void biped_reset(int unit_handle)
{
  char *obj;
  int *dst;
  int tmp0;
  int tmp1;
  int tmp2;
  int tmp3;

  obj = (char *)object_get_and_verify_type(unit_handle, 1);
  csmemset(obj + 0x424, 0, 0x5c);
  tmp0 = *(int *)0x32513c;
  dst = (int *)(obj + 0x46c);
  tmp1 = *(int *)0x325140;
  dst[0] = tmp0;
  tmp2 = *(int *)0x325144;
  dst[1] = tmp1;
  tmp3 = *(int *)0x325148;
  *(int *)(obj + 0x450) = -1;
  dst[2] = tmp2;
  dst[3] = tmp3;
}

/* biped_disconnect_from_structure_bsp (0x1a0860)
 *
 * Clears the biped's BSP leaf/cluster/surface datum handle fields to -1,
 * disconnecting the unit from the current structure BSP.
 *
 * Confirmed: obj+0x430 = -1, obj+0x434 = -1, obj+0x448 = -1 (OR ECX,-1
 * pattern). Confirmed: uses same ECX=-1 value for all three stores (single OR
 * ECX,-1). Uncertain: exact field names at 0x430, 0x434, 0x448.
 */
void biped_disconnect_from_structure_bsp(int unit_handle)
{
  char *obj;

  obj = (char *)object_get_and_verify_type(unit_handle, 1);
  *(int *)(obj + 0x430) = -1;
  *(int *)(obj + 0x434) = -1;
  *(int *)(obj + 0x448) = -1;
}

/* biped_get_camera_height_and_offset (0x1a0890)
 *
 * Computes camera height parameters for a biped unit. Gets the world position
 * into out_pos, optionally adds the biped tag's camera height to the Z
 * coordinate, then calculates a height offset based on the biped's crouch
 * state and tag parameters.
 *
 * Confirmed: CALL 0x13d680 (object_get_and_verify_type) with type 1 (biped
 * only). Confirmed: CALL 0x1ba140 (tag_get) with 'bipd' signature (0x62697064).
 * Confirmed: CALL 0x1412f0 (object_get_world_position).
 * Confirmed: Tag offsets 0x2f4 (flags), 0x424 (crouch height), 0x428 (stand
 * height), 0x42c (camera height). Confirmed: Unit offset 0x1c8 (unk_456 datum
 * handle), 0x4 (object flags), 0x464 (crouch fraction).
 */
void biped_get_camera_height_and_offset(int unit_handle, vector3_t *out_pos,
                                        float *out_height_offset,
                                        float *out_camera_height)
{
  char *unit_obj;
  char *biped_tag;
  float camera_height;

  unit_obj = (char *)object_get_and_verify_type(unit_handle, 1);
  biped_tag = (char *)tag_get(0x62697064, *(int *)unit_obj);

  object_get_world_position(unit_handle, out_pos);

  /* Add camera height to Z position unless flag bit 3 is set */
  if ((*(uint8_t *)(biped_tag + 0x2f4) & 0x8) == 0) {
    out_pos->z = *(float *)(biped_tag + 0x42c) + out_pos->z;
  }

  /* Calculate height offset based on crouch state */
  if ((*(uint8_t *)(biped_tag + 0x2f4) & 0x10) == 0 &&
      (*(int *)(unit_obj + 0x1c8) != -1 ||
       (*(uint32_t *)(unit_obj + 0x4) & 0x400000) != 0)) {
    /* Unit has actor or is player-controlled: interpolate based on crouch.
     * Memory-access order matches the original: standing/crouching heights and
     * crouch fraction are read inline; camera_height is cached once so the
     * doubling compiles to FADD ST0,ST0; out_camera_height re-reads [0x42c]. */
    camera_height = *(float *)(biped_tag + 0x42c);
    *out_height_offset =
      (*(float *)(biped_tag + 0x428) - *(float *)(biped_tag + 0x424)) *
        *(float *)(unit_obj + 0x464) +
      *(float *)(biped_tag + 0x424) - (camera_height + camera_height);
    *out_camera_height = *(float *)(biped_tag + 0x42c);
  } else {
    /* No actor and not player-controlled: zero offset */
    *out_height_offset = 0.0f;
    *out_camera_height = *(float *)(biped_tag + 0x42c);
  }
}

/* biped_stop_melee_attack (0x1a0950)
 *
 * Clears the melee-attack active flag (obj+0x45d = 0) on the biped's unit
 * object, if the object exists. Uses object_try_and_get_and_verify_type (does
 * not assert on missing object).
 *
 * Confirmed: CALL 0x13d640 (object_try_and_get_and_verify_type) with type 1.
 * Confirmed: MOV byte ptr [EAX+0x45d],0x0 if result != NULL.
 * Inferred: "stop melee" semantics from flag offset matching biped_start_limp
 *   sequence and the clear-vs-set pattern.
 */
void biped_stop_melee_attack(int unit_handle)
{
  char *obj;

  obj = (char *)object_try_and_get_and_verify_type(unit_handle, 1);
  if (obj != NULL) {
    *(uint8_t *)(obj + 0x45d) = 0;
  }
}

/* biped_start_limp_body_physics (0x1a0970)
 *
 * Begins limp-body (ragdoll-like) physics simulation for a biped. Checks
 * several preconditions against the tag flags and object state before
 * activating: requires the limp-body tag flag (tag+0x2f4 bit 9 set), the
 * biped must have a velocity (obj+0x4 bit 5), must not already be in ragdoll
 * (obj+0x424 bits 0x21), and the global freeze flag must be clear.
 * On entry it clears obj+0x47c (sub-step counter) and stores the unit
 * definition type constant (0x14) in obj+0x47d, then ORs obj+0x4 with
 * 0x800000 and obj+0x424 with 0x20.
 *
 * Confirmed: CALL 0x13d680 (object_get_and_verify_type) type 1.
 * Confirmed: CALL 0x1ba140 (tag_get) 'bipd'.
 * Confirmed: DAT_004e4cf3 = global freeze flag (byte).
 * Confirmed: tag+0x2f4 >> 9 & 1 = limp-body enabled flag.
 * Confirmed: obj+0x4 bit 0x20 = has-velocity; obj+0x424 bits 0x21 = already
 * ragdoll. Confirmed: CALL 0x19f530 with unit_handle arg → returns 0x14 (unit
 * def type const). Confirmed: stores return value (0x14) in obj+0x47d.
 * Inferred: obj+0x47c is a ragdoll sub-frame counter, cleared on start.
 */
void biped_start_limp_body_physics(int unit_handle)
{
  char *obj;
  char *biped_tag;
  uint8_t type_const;
  uint32_t flags4;
  uint32_t flags424;

  obj = (char *)object_get_and_verify_type(unit_handle, 1);
  biped_tag = (char *)tag_get(0x62697064, *(int *)obj);
  if (*(uint8_t *)0x4e4cf3 != 0) {
    return;
  }
  if ((*(uint32_t *)(biped_tag + 0x2f4) >> 9 & 1) == 0) {
    return;
  }
  if ((*(uint8_t *)(obj + 0x4) & 0x20) == 0) {
    return;
  }
  if ((*(uint8_t *)(obj + 0x424) & 0x21) != 0) {
    return;
  }
  *(uint8_t *)(obj + 0x47c) = 0;
  type_const = (uint8_t)FUN_0019f530(unit_handle);
  *(uint8_t *)(obj + 0x47d) = type_const;
  flags4 = *(uint32_t *)(obj + 0x4);
  flags424 = *(uint32_t *)(obj + 0x424);
  flags4 |= 0x800000;
  flags424 |= 0x20;
  *(uint32_t *)(obj + 0x4) = flags4;
  *(uint32_t *)(obj + 0x424) = flags424;
}

/* biped_stop_limp_body_physics (0x1a09f0)
 *
 * Ends limp-body physics simulation if preconditions are met: the tag must
 * have the limp-body flag (tag+0x2f4 bit 9 = CH bit), and the ragdoll-active
 * flag (obj+0x424 bit 5 = 0x20) must be set. On success, clears both flags.
 *
 * Confirmed: TEST CH,0x2 checks bit 9 of the dword at tag+0x2f4 (CH = byte 1
 *   of dword; bit 1 of CH = bit 9 of dword).
 * Confirmed: AND [ESI+4],0xff7fffff clears obj+0x4 bit 23 (0x800000).
 * Confirmed: AND [ESI+0x424],0xffffffdf clears bit 5 (0x20).
 * Inferred: mirror of biped_start_limp_body_physics.
 */
void biped_stop_limp_body_physics(int unit_handle)
{
  char *obj;
  char *biped_tag;
  uint32_t tag_flags;
  uint32_t flags4;
  uint32_t flags424;

  obj = (char *)object_get_and_verify_type(unit_handle, 1);
  biped_tag = (char *)tag_get(0x62697064, *(int *)obj);
  tag_flags = *(uint32_t *)(biped_tag + 0x2f4);
  if ((tag_flags & 0x200) == 0) {
    return;
  }
  flags424 = *(uint32_t *)(obj + 0x424);
  if ((flags424 & 0x20) == 0) {
    return;
  }
  flags4 = *(uint32_t *)(obj + 0x4) & 0xff7fffff;
  flags424 = flags424 & 0xffffffdf;
  *(uint32_t *)(obj + 0x4) = flags4;
  *(uint32_t *)(obj + 0x424) = flags424;
}

/* FUN_001a0a40 (0x1a0a40)
 *
 * Per-frame melee-contact/bump handler for bipeds. Tracks a timer (obj+0x458)
 * and triggers AI bump notification and optional player-unit reassignment.
 *
 * Register args (confirmed from caller FUN_001a5300 at 0x1a61ba/0x1a61c4):
 *   @edi  unit_handle  — biped datum handle
 *   @ebx  biped_obj    — pointer to biped object data (pre-fetched by caller)
 * Stack arg:
 *   velocity_ptr  [EBP+0x8]  — pointer to the biped's velocity vector (3
 * floats)
 *
 * Logic:
 *   If timer (obj+0x458) is negative (counting up through negatives):
 *     - If no new contact (EDI == -1): just increment timer and return.
 *     - Else: fall through to common exit (set timer to 0xf1).
 *   If timer >= 0 and no new contact (EDI == -1): early return (nothing to do).
 *   Otherwise:
 *     - Get the contact object (EDI, type -1).
 *     - Call ai_handle_bump(biped_handle, contact_handle, velocity_ptr).
 *     - If vehicle slot (obj+0x1c8) != -1 OR recorded-animation controlling:
 *         If obj+0x454 (last contact) != new contact: store new contact, clear
 * timer, return. Else: increment timer; if timer reaches 4 (> 3): If in
 * multiplayer + has local player: set obj+0x458=0xf1, call
 * players_set_local_player_unit. Fall-through/exit: set obj+0x458 = 0xf1.
 *
 * Confirmed: obj+0x458 = bump_timer (int8_t); obj+0x1c8 = vehicle_datum handle.
 * Confirmed: obj+0x454 = last_contact handle; obj+0x1c8 = vehicle slot.
 * Confirmed: DAT_005aa893 = multiplayer flag.
 * Confirmed: CALL 0x94ff0 (recorded_animation_controlling_unit).
 * Confirmed: CALL 0xb6990 (unit_get_local_player_index), returns int16_t (-1 =
 * none). Confirmed: CALL 0xba5f0 (players_set_local_player_unit(player_idx,
 * unit_handle)). Confirmed: [EDX+0x64] word = some vehicle-seat type field
 * checked == 0. Inferred: 0xf1 timer value = "reset/cleared" sentinel.
 */
void FUN_001a0a40(int contact_handle /* @edi */, int unit_handle /* @ebx */,
                  float *velocity_ptr)
{
  char *obj;
  char *contact_obj;
  int8_t timer;
  int16_t player_idx;

  obj = (char *)object_get_and_verify_type(unit_handle, 1);
  tag_get(0x62697064, *(int *)obj);

  timer = *(int8_t *)(obj + 0x458);
  if (timer < 0) {
    if (contact_handle == -1) {
      *(int8_t *)(obj + 0x458) = timer + 1;
      return;
    }
  } else {
    if (contact_handle == -1) {
      return;
    }
    contact_obj = (char *)object_get_and_verify_type(contact_handle, -1);
    ai_handle_bump(unit_handle, contact_handle, velocity_ptr);
    if ((*(int *)(obj + 0x1c8) == -1) &&
        (recorded_animation_controlling_unit(unit_handle) == 0)) {
      return;
    }
    if (*(int *)(obj + 0x454) != contact_handle) {
      *(int *)(obj + 0x454) = contact_handle;
      *(int8_t *)(obj + 0x458) = 0;
      return;
    }
    timer = *(int8_t *)(obj + 0x458);
    timer++;
    *(int8_t *)(obj + 0x458) = timer;
    if (timer <= 3) {
      return;
    }
    if ((*(int16_t *)(contact_obj + 0x64) == 0) &&
        (*(uint8_t *)0x5aa893 != 0)) {
      player_idx = unit_get_local_player_index(unit_handle);
      if (player_idx != -1) {
        *(uint8_t *)(contact_obj + 0x458) = 0xf1;
        players_set_local_player_unit(player_idx, unit_handle);
      }
    }
  }
  *(uint8_t *)(obj + 0x458) = 0xf1;
}

/* FUN_001a0b30 (0x1a0b30)
 *
 * Checks whether a biped is stuck in an unreachable (bad) position and erases
 * it if so. Triggered once per update frame from the biped update loop.
 *
 * Register arg (confirmed from caller FUN_001a6350 at 0x1a6727):
 *   @edi  unit_handle  — biped datum handle
 *
 * Conditions to erase (all must hold):
 *   1. game_engine_running() == false (not in a game engine / network game)
 *   2. Either obj+0x4 bit 0x200000 set (flying/physics flag) OR obj+0x4c == -1
 *      (no parent handle)
 *   3. obj+0x14 (velocity Z / speed float) < DAT_002b4d1c (negative-infinity or
 *      very-small threshold — biped is sinking/below world)
 *
 * On erase:
 *   Looks up actor (obj+0x1a8 or fallback obj+0x1a4), calls
 *   ai_debug_describe_actor for the warning string, prints WARNING via error(),
 *   then calls object_delete(unit_handle).
 *
 * Confirmed: FCOMP [0x2b4d1c], TEST AH,0x5, JP = "< with NaN" check.
 * Confirmed: PUSH 0x100 / PUSH 0x5ab100 / PUSH 0x1 / PUSH EDI / PUSH EAX =
 *   ai_debug_describe_actor(actor_handle, unit_handle, 1, buf@0x5ab100, 0x100).
 * Confirmed: PUSH EAX / PUSH ECX / CALL 0x1ba1f0 = tag_get_name(tag_index).
 * Confirmed: warning format string at 0x2b4cd8.
 * Returns 0 (char) always.
 * Inferred: function name from warning message "biped %s (%s) is in a bad
 * place".
 */
char FUN_001a0b30(int unit_handle /* @edi */)
{
  char *obj;
  int actor_handle;
  const char *tag_name;
  const char *actor_desc;

  obj = (char *)object_get_and_verify_type(unit_handle, 1);
  if (game_engine_running() != 0) {
    return 0;
  }
  if ((*(uint32_t *)(obj + 0x4) & 0x200000) == 0 &&
      *(int16_t *)(obj + 0x4c) != -1) {
    return 0;
  }
  if (!(*(float *)(obj + 0x14) < *(float *)0x2b4d1c)) {
    return 0;
  }
  actor_handle = *(int *)(obj + 0x1a8);
  if (actor_handle == -1) {
    actor_handle = *(int *)(obj + 0x1a4);
  }
  actor_desc = ai_debug_describe_actor(actor_handle, unit_handle, 1,
                                       (char *)0x5ab100, 0x100);
  tag_name = tag_get_name(*(int *)obj);
  tag_name = tag_name_strip_path(tag_name);
  error(2, "WARNING: biped %s (%s) is in a bad place (%.1f %.1f %.1f), erasing",
        tag_name, actor_desc, (double)*(float *)(obj + 0xc),
        (double)*(float *)(obj + 0x10), (double)*(float *)(obj + 0x14));
  object_delete(unit_handle);
  return 0;
}

/* FUN_001a0be0 (0x1a0be0)
 *
 * Per-frame biped world-boundary check. If the biped falls outside the world
 * or below the kill-volume threshold, applies damage and/or erases the biped.
 *
 * Register arg (confirmed from caller FUN_001a5300 at 0x1a61d1):
 *   @edi  unit_handle  — biped datum handle
 * Stack arg:
 *   vertical_speed  [EBP+0x8]  — current vertical speed (float, from local_24
 *     in caller = camera Z delta or velocity component)
 *
 * Logic summary:
 *   1. Get biped object and tag. Get game_globals physics block element [0].
 *   2. Compute bVar1 (= "is_protected"): set true if obj+0x1b4 bit 0x1000 set
 *      OR tag+0x2f4 bit 7 (0x80) set.
 *   3. If multiplayer-engine running (DAT_5aa891) AND obj+0x1c8 != -1: skip.
 *   4. If vertical_speed > physics[0x90] (kill-height threshold):
 *      - If not protected: build damage params from physics[0x1c] tag ref,
 *        call damage_data_new + object_cause_damage.
 *      - Compute t = clamp01((speed - low) / (high - low)) and return.
 *   5. Else (below threshold):
 *      - Check tag flag bit 2 (0x4) at tag+0x2f4 and vertical speed.
 *      - If not flying and falling fast: possibly apply damage, then erase.
 *
 * Confirmed: tag_block_get_element(game_globals+0x188, 0, 0x98).
 * Confirmed: TEST AH,0x10 checks obj+0x1b4 bit 0x1000.
 * Confirmed: physics block offsets 0x8c (fall speed), 0x90 (jump height),
 *   0x94 (climb height), 0x38/0x1c (damage tag refs).
 * Confirmed: damage_data_new, object_cause_damage call arg counts from disasm.
 * Confirmed: clamp01 via FCOMP+FNSTSW+TEST pattern.
 * Confirmed: erasing path = player_index_from_unit_index +
 * ai_debug_describe_actor
 *   + error("fell outside world") + object_delete.
 * Inferred: vertical_speed param meaning (from call site local_24 in 0x1a5300).
 * Uncertain: exact semantics of obj+0x1b4 bit 0x1000 (possibly "in vehicle" or
 *   "has shield").
 */
void FUN_001a0be0(float vertical_speed, int unit_handle /* @edi */)
{
  char *obj;
  char *biped_tag;
  char *physics;
  char damage_params[0x54]; /* damage_data_new clears through +0x53. */
  float t;
  int actor_handle;
  int player_idx;
  const char *tag_name;
  const char *actor_desc;
  char is_protected;

  obj = (char *)object_get_and_verify_type(unit_handle, 1);
  biped_tag = (char *)tag_get(0x62697064, *(int *)obj);
  physics =
    (char *)tag_block_get_element((char *)game_globals_get() + 0x188, 0, 0x98);

  /* is_protected = obj has special flag OR tag marks it protected */
  if ((*(uint32_t *)(obj + 0x1b4) & 0x1000) != 0 ||
      *(int8_t *)(biped_tag + 0x2f4) < 0) {
    is_protected = 1;
  } else {
    is_protected = 0;
  }

  /* In multiplayer with a vehicle: skip all checks */
  if (*(uint8_t *)0x5aa891 != 0 && *(int *)(obj + 0x1c8) != -1) {
    return;
  }

  if (vertical_speed > *(float *)(physics + 0x90)) {
    /* Above jump-height threshold: if protected return early, else damage +
     * return */
    if (is_protected) {
      return;
    }
    damage_data_new(damage_params, *(int *)(physics + 0x1c));
    /* Compute lerp t = clamp01((speed - low) / (high - low)) */
    t = (vertical_speed - *(float *)(physics + 0x90)) /
        (*(float *)(physics + 0x94) - *(float *)(physics + 0x90));
    if (t < *(float *)0x2533c0) {
      t = 0.0f;
    } else if (!(t <= *(float *)0x2533c8)) {
      t = 1.0f;
    }
    object_cause_damage(damage_params, unit_handle, -1, -1, -1, 0);
    return;
  }

  /* Below threshold — check for fall/erase conditions */
  if ((*(uint8_t *)(biped_tag + 0x2f4) & 0x4) != 0) {
    return;
  }
  if (!(*(float *)(obj + 0x20) < -(*(float *)(physics + 0x8c)))) {
    return;
  }
  if (!is_protected && (*(uint8_t *)(obj + 0xb6) & 0x4) == 0) {
    damage_data_new(damage_params, *(int *)(physics + 0x38));
    object_cause_damage(damage_params, unit_handle, -1, -1, -1, 0);
  }
  if (game_engine_running() != 0) {
    return;
  }
  if ((*(uint32_t *)(obj + 0x4) & 0x200000) == 0) {
    return;
  }
  player_idx = player_index_from_unit_index(unit_handle);
  if (player_idx != -1) {
    return;
  }
  actor_handle = *(int *)(obj + 0x1a8);
  if (actor_handle == -1) {
    actor_handle = *(int *)(obj + 0x1a4);
  }
  actor_desc = ai_debug_describe_actor(actor_handle, unit_handle, 1,
                                       (char *)0x5ab100, 0x100);
  tag_name = tag_get_name(*(int *)obj);
  tag_name = tag_name_strip_path(tag_name);
  error(2, "WARNING: biped %s (%s) fell outside world and was erased", tag_name,
        actor_desc);
  object_delete(unit_handle);
}

/* biped_flying_through_air (0x1a0db0)
 *
 * Predicate: returns 1 if the biped is considered airborne (flying through the
 * air) and should run air physics. True when the airborne-frame counter
 * (unit+0x459) exceeds 3 AND either the biped tag does not have the "no
 * airborne" flag (tag+0x2f4 bit 2) or the unit has the override flag
 * (unit+0xb6 bit 2).
 *
 * Confirmed: object_get_and_verify_type(unit_handle, 1); tag_get('bipd', ...).
 * unit+0x459 signed-char counter compared > 3; tag+0x2f4 bit2; unit+0xb6 bit2.
 */
int biped_flying_through_air(int unit_handle)
{
  char *unit_obj;
  char *biped_tag;

  unit_obj = (char *)object_get_and_verify_type(unit_handle, 1);
  biped_tag = (char *)tag_get(0x62697064, *(int *)unit_obj);


  if (*(char *)(unit_obj + 0x459) > 3 &&
      (((*(unsigned char *)(biped_tag + 0x2f4) & 4) == 0) ||
       ((*(unsigned char *)(unit_obj + 0xb6) & 4) != 0))) {
    return 1;
  }
  return 0;
}

/* FUN_001a0e00 (0x1a0e00)
 *
 * Advances a biped animation/transition phase based on an elapsed-time
 * threshold. The biped tag stores three phase boundaries (in ticks) at
 * tag+0x3dc/0x3e0/0x3e4, converted to seconds via *(1/30). Given the elapsed
 * time `threshold`, selects which phase the biped is in, computes a normalized
 * progress t (clamped to [0,1]) across that phase, and writes:
 *   unit+0x460 (uint16) = phase flag (0 = first phase, 1 = second phase)
 *   unit+0x428 (byte)   = 0
 *   unit+0x429 (byte)   = (char)(int)(phase_rate * t)
 * where phase_rate = tag[0x3d4 or 0x3d8] * TICKS_PER_SECOND.
 *
 * unit_handle is passed in EAX (register arg); `threshold` is the cdecl stack
 * arg. _ftol2 (0x1d9068) is the MSVC float->int intrinsic — written as (int).
 * Constant 0x2546a4 = seconds-per-tick (1/30); 0x253394 = TICKS_PER_SECOND.
 */
void FUN_001a0e00(float threshold, int unit_handle)
{
  char *unit_obj;
  char *biped_tag;
  float fVar1;
  float fVar2;
  float range;
  float offset;
  float base;
  float scaled;
  float t;
  int flag;

  unit_obj = (char *)object_get_and_verify_type(unit_handle, 1);
  biped_tag = (char *)tag_get(0x62697064, *(int *)unit_obj);

  fVar1 = *(float *)(biped_tag + 0x3dc) * *(float *)0x2546a4;
  fVar2 = *(float *)(biped_tag + 0x3e0) * *(float *)0x2546a4;

  /* Branch primitives transcribed from the disassembly: the original tests with
   * `<` (FCOMP; TEST AH,0x5) and inverts the jump, so mirror those `<` forms
   * and the early-exit shape rather than the algebraically-equivalent `<=`
   * nesting. */
  if (threshold < fVar1) {
    return;
  }
  if (threshold < fVar2) {
    offset = threshold - fVar1;
    range = fVar2 - fVar1;
    base = *(float *)(biped_tag + 0x3d4);
    flag = 0;
  } else {
    range = *(float *)(biped_tag + 0x3e4) * *(float *)0x2546a4 - fVar2;
    offset = threshold;
    base = *(float *)(biped_tag + 0x3d8);
    flag = 1;
  }
  scaled = base * TICKS_PER_SECOND;
  if (range <= 0.0f) {
    return;
  }
  t = offset / range;
  if (t < 0.0f) {
    t = 0.0f;
  } else if (1.0f < t) {
    t = 1.0f;
  }
  *(uint16_t *)(unit_obj + 0x460) = (uint16_t)flag;
  *(unsigned char *)(unit_obj + 0x428) = 0;
  *(unsigned char *)(unit_obj + 0x429) = (unsigned char)(int)(scaled * t);
}

/* FUN_001a0f10 (0x1a0f10)
 *
 * Spawns a biped contact/footstep effect from one entry of the biped tag's
 * contact-point block. Looks up the biped tag ('bipd') from the unit, brackets
 * the work in the collision-user-depth stack (global 0x4761d8 / stack 0x5a8c80,
 * marker 7), asserting depth < 0x20 on entry (line 0xf4f) and > 1 on exit
 * (line 0xf60). If the requested contact index (register BX) is in range of the
 * tag's contact-point block at tag+0x4e8 AND the effect tag reference at
 * tag+0x398 is valid (!= -1), and the object's animation/contact gate
 * FUN_0009f3b0(object+0x50) passes, it fetches contact-point element BX
 * (element size 0x40), resolves the named marker (name at element+0x20) on the
 * object via object_get_markers_by_string_id (one marker, into a 108-byte
 * result buffer), and on success spawns the effect (tag+0x398) at the marker's
 * world position (buffer+0x60) via FUN_0009f570.
 *
 * Confirmed (disasm): cdecl, 2 stack params [EBP+8]=unit_handle, [EBP+0xc];
 *   index is register-passed in BX (MOVSX EBX,BX at 0x1a0f73 reads BX before
 *   any write; callers 0x1a2440 load EBX immediately before each CALL). void
 *   return. The marker-result buffer is one contiguous region: Ghidra split it
 *   into local_74[96]+local_14[12], but object_get_markers_by_string_id writes
 *   to offset 0x6c (108 bytes) and FUN_0009f570 reads the position at +0x60
 *   (LEA [EBP-0x70] vs LEA [EBP-0x10] differ by exactly 0x60).
 * Inferred: 'bipd' contact-point footstep-effect spawn semantics from the
 *   tag-block index + effect-tag + marker-position spawn shape.
 * Uncertain: precise meaning of param_2 (forwarded unchanged to FUN_0009f570);
 *   callers pass 3 or 4 (region/permutation selector). Layout of the 108-byte
 *   marker-result buffer beyond "transform copy at +0x38..0x6c, position at
 *   +0x60" is opaque (no named struct in headers yet).
 */
void FUN_001a0f10(int unit_handle, int param_2, short index /* @bx */)
{
  unsigned int *object;
  int biped_tag;
  int depth;
  void *contact_elem;
  /* One contiguous marker-result buffer. object_get_markers_by_string_id
   * writes up to offset 0x6c (108 bytes); FUN_0009f570 reads the marker
   * world position at +0x60. Sized so the MSVC frame totals 0x70 with the
   * 4-byte object pointer (do not split into separate locals). */
  char marker_buf[0x6c];

  object = (unsigned int *)object_get_and_verify_type(unit_handle, 1);
  biped_tag = (int)tag_get(0x62697064, *object); /* 'bipd' */

  if (*(int16_t *)0x4761d8 >= 0x20) {
    display_assert("global_current_collision_user_depth < "
                   "MAXIMUM_COLLISION_USER_STACK_DEPTH",
                   "c:\\halo\\SOURCE\\units\\bipeds.c", 0xf4f, true);
    system_exit(-1);
  }
  depth = *(int16_t *)0x4761d8;
  *(int16_t *)0x4761d8 = (int16_t)(depth + 1);
  *(int16_t *)(0x5a8c80 + depth * 2) = 7;

  if (((int)index < *(int *)(biped_tag + 0x4e8)) &&
      (*(int *)(biped_tag + 0x398) != -1)) {
    if (FUN_0009f3b0((char *)object + 0x50) != false) {
      contact_elem =
        tag_block_get_element((void *)(biped_tag + 0x4e8), (int)index, 0x40);
      if (object_get_markers_by_string_id(
            unit_handle, (char *)contact_elem + 0x20, marker_buf, 1) != 0) {
        FUN_0009f570(*(int *)(biped_tag + 0x398), param_2, marker_buf + 0x60,
                     0);
      }
    }
  }

  if (*(int16_t *)0x4761d8 <= 1) {
    display_assert("global_current_collision_user_depth > 1",
                   "c:\\halo\\SOURCE\\units\\bipeds.c", 0xf60, true);
    system_exit(-1);
  }
  *(int16_t *)0x4761d8 = (int16_t)(*(int16_t *)0x4761d8 - 1);
}

/* biped_adjust_placement (0x1a1020)
 *
 * If the biped tag has the "camera offset placement" flag (tag+0x2f4 bit 3)
 * set and NOT the suppress flag (bit 2), shifts the placement's position
 * (placement+0x18..0x20) along the placement's forward axis (placement+0x40..
 * 0x48) by the biped's camera height (tag+0x42c).
 *
 * Confirmed: object_get_and_verify_type(unit_handle, 1); tag_get('bipd', ...).
 * camera_height (tag+0x42c) loaded once and reused for all three axes.
 */
void biped_adjust_placement(int unit_handle, char *placement)
{
  char *unit_obj;
  char *biped_tag;
  float camera_height;

  unit_obj = (char *)object_get_and_verify_type(unit_handle, 1);
  biped_tag = (char *)tag_get(0x62697064, *(int *)unit_obj);

  if ((*(unsigned int *)(biped_tag + 0x2f4) & 8) != 0 &&
      (*(unsigned int *)(biped_tag + 0x2f4) & 4) == 0) {
    camera_height = *(float *)(biped_tag + 0x42c);
    *(float *)(placement + 0x18) =
      camera_height * *(float *)(placement + 0x40) +
      *(float *)(placement + 0x18);
    *(float *)(placement + 0x1c) =
      camera_height * *(float *)(placement + 0x44) +
      *(float *)(placement + 0x1c);
    *(float *)(placement + 0x20) =
      camera_height * *(float *)(placement + 0x48) +
      *(float *)(placement + 0x20);
  }
}

/* biped_export_function_values (0x1a1080)
 *
 * Exports up to 4 animation "function" input values (unit+0xd4..0xe0) from the
 * biped tag's function-input table (tag+0x30c, 4 int16 type codes). For each
 * slot whose type is 1 ("speed"), the value is the unit's velocity magnitude
 * normalized by the biped's max speed (tag+0x334 ticks/sec * seconds-per-tick),
 * clamped to [0,1]. Type 0 slots are skipped (left unchanged). Other types
 * export 0.
 *
 * Confirmed: object_get_and_verify_type(unit_handle, 1); tag_get('bipd', ...).
 * Velocity at unit+0x18..0x20; output at unit+0xd4 (stride 4); types at
 * tag+0x30c (stride 2); max-speed denom = tag+0x334 * (1/30).
 */
void biped_export_function_values(int unit_handle)
{
  char *unit_obj;
  char *biped_tag;
  short *type_ptr;
  float *out_ptr;
  float *vel;
  float ratio;
  float val;
  int count;

  unit_obj = (char *)object_get_and_verify_type(unit_handle, 1);
  biped_tag = (char *)tag_get(0x62697064, *(int *)unit_obj);

  type_ptr = (short *)(biped_tag + 0x30c);
  out_ptr = (float *)(unit_obj + 0xd4);
  count = 4;
  do {
    if (*type_ptr != 0) {
      val = 0.0f;
      if (*type_ptr == 1) {
        vel = (float *)(unit_obj + 0x18);
        ratio = sqrtf(vel[0] * vel[0] + vel[1] * vel[1] + vel[2] * vel[2]) /
                (*(float *)(biped_tag + 0x334) * *(float *)0x2546a4);
        if (0.0f <= ratio) {
          val = ratio;
          if (1.0f < ratio) {
            val = 1.0f;
          }
        }
      }
      *out_ptr = val;
    }
    type_ptr = type_ptr + 1;
    out_ptr = out_ptr + 1;
    count = count + -1;
  } while (count != 0);
}

/* biped_estimate_position (0x1a1140)
 *
 * Estimates the position of a biped based on the estimate mode. Used for
 * camera targeting, AI perception, and gun positioning. Different modes
 * control whether the position is computed from scratch or transformed.
 *
 * Estimate modes:
 *   0 = none: just get world position + height adjustment
 *   1 = crouching: use 0.0 crouch factor for height
 *   2 = standing: use 1.0 crouch factor for height
 *   3 = gun position: apply facing/offset transform, then height
 *   else: use actual unit crouch fraction
 *
 * Confirmed: CALL 0x13d680 (object_get_and_verify_type) with type 1.
 * Confirmed: CALL 0x1ba140 (tag_get) with 'bipd' signature.
 * Confirmed: CALL 0x1412f0 (object_get_world_position) for mode 0.
 * Confirmed: CALL 0x8d9f0 (display_assert) with bipeds.c path.
 * Confirmed: Tag offsets 0x400 (crouching height), 0x404 (standing height).
 * Confirmed: Unit offset 0x464 (crouch fraction).
 * Confirmed: Globals 0x2533c0 (0.0f), 0x2533c8 (1.0f).
 */
void biped_estimate_position(int unit_handle, int16_t estimate_mode,
                             vector3_t *estimated_body_position,
                             vector3_t *desired_facing,
                             vector3_t *desired_gun_offset,
                             vector3_t *out_position)
{
  char *unit_obj;
  char *biped_tag;
  float crouch_value;
  float neg_facing_y;
  float facing_x;
  float gun_y;

  unit_obj = (char *)object_get_and_verify_type(unit_handle, 1);
  biped_tag = (char *)tag_get(0x62697064, *(int *)unit_obj);

  /* Assert: if estimate_mode != 0, must have estimated_body_position */
  if (estimate_mode != 0 && estimated_body_position == NULL) {
    display_assert("(estimate_mode == _unit_estimate_none) || "
                   "(estimated_body_position != NULL)",
                   "c:\\halo\\SOURCE\\units\\bipeds.c", 0x2f7, true);
    system_exit(-1);
  }

  /* Assert: if estimate_mode == 3, must have desired_facing */
  if (estimate_mode == 3) {
    if (desired_facing == NULL) {
      display_assert("(estimate_mode != _unit_estimate_gun_position) || "
                     "(desired_facing != NULL)",
                     "c:\\halo\\SOURCE\\units\\bipeds.c", 0x2f8, true);
      system_exit(-1);
    }
  } else if (estimate_mode == 0) {
    /* Mode 0: just get world position and apply height */
    object_get_world_position(unit_handle, out_position);
    goto height_adjustment;
  }

  /* Copy estimated body position to output */
  out_position->x = estimated_body_position->x;
  out_position->y = estimated_body_position->y;
  out_position->z = estimated_body_position->z;

  if (estimate_mode == 3) {
    /* Gun position mode: apply facing rotation and gun offset */
    if (desired_facing == NULL || desired_gun_offset == NULL) {
      display_assert("desired_facing && desired_gun_offset",
                     "c:\\halo\\SOURCE\\units\\bipeds.c", 0x307, true);
      system_exit(-1);
    }

    /* Transform position by facing direction and gun offset.
     * This applies a 2D rotation in XY plane using the facing vector,
     * then adds the Z component of the gun offset. */
    neg_facing_y = -desired_facing->y;
    facing_x = desired_facing->x;

    /* Apply gun offset X component along facing direction */
    out_position->x =
      desired_gun_offset->x * desired_facing->x + out_position->x;
    out_position->y =
      desired_gun_offset->x * desired_facing->y + out_position->y;
    out_position->z =
      desired_gun_offset->x * desired_facing->z + out_position->z;

    /* Apply gun offset Y component perpendicular to facing (rotated 90 deg) */
    gun_y = desired_gun_offset->y;
    out_position->x = gun_y * neg_facing_y + out_position->x;
    out_position->y = gun_y * facing_x + out_position->y;
    /* Note: gun_y * 0.0 for Z is optimized out, just add gun offset Z */
    out_position->z = gun_y * 0.0f + out_position->z;
    out_position->z = out_position->z + desired_gun_offset->z;
    return;
  }

height_adjustment:
  /* Calculate crouch value based on estimate mode. The switch matches the
   * original's MOVSX/DEC/JZ dispatch (mode 1 -> 0.0, mode 2 -> 1.0, else the
   * unit's actual crouch fraction). */
  switch (estimate_mode) {
  case 1:
    crouch_value = 0.0f; /* Crouching */
    break;
  case 2:
    crouch_value = 1.0f; /* Standing */
    break;
  default:
    crouch_value = *(float *)(unit_obj + 0x464); /* Actual crouch fraction */
    break;
  }

  /* Interpolate height between crouching and standing based on crouch value.
   * Order matches the original FPU sequence: (1-cv)*crouching + cv*standing. */
  out_position->z = (1.0f - crouch_value) * *(float *)(biped_tag + 0x400) +
                    crouch_value * *(float *)(biped_tag + 0x404) +
                    out_position->z;
}

/* biped_get_autoaim_pill (0x1a12e0)
 *
 * Computes the auto-aim capsule (pill) for a biped: base position (out_pos),
 * axis/extent (out_axis), and the biped's autoaim flags value
 * (*out_value = tag+0x458). Three cases by the tag's autoaim marker node
 * indices (tag+0x4e4, +0x4e6):
 *   - Both valid + tag flag bit4 (tag+0x2f4 & 0x10): base = midpoint of the
 *     two marker node positions; axis = zero vector.
 *   - Both valid, no flag: base = marker0 position; axis = marker1 - marker0.
 *   - Either invalid: base/height from biped_get_camera_height_and_offset;
 *     base.z += half the height offset; axis = half-offset along world up.
 *
 * Confirmed: object_get_and_verify_type(unit_handle, 1); tag_get('bipd', ...);
 * object_get_node_matrix (node matrix +0x28 = position); midpoint3d (0x2a540);
 * 0.5f = *(float*)0x253398; axis = marker1 - marker0 (FSUB order from disasm).
 */
void biped_get_autoaim_pill(int unit_handle, float *out_pos, float *out_axis,
                            int *out_value)
{
  char *unit_obj;
  char *biped_tag;
  char *marker0;
  char *marker1;
  float height_offset;
  float camera_height;
  float half;

  unit_obj = (char *)object_get_and_verify_type(unit_handle, 1);
  biped_tag = (char *)tag_get(0x62697064, *(int *)unit_obj);

  if (*(short *)(biped_tag + 0x4e4) != -1 &&
      *(short *)(biped_tag + 0x4e6) != -1) {
    marker0 = (char *)object_get_node_matrix(unit_handle,
                                             *(short *)(biped_tag + 0x4e4));
    marker1 = (char *)object_get_node_matrix(unit_handle,
                                             *(short *)(biped_tag + 0x4e6));
    if ((*(unsigned char *)(biped_tag + 0x2f4) & 0x10) != 0) {
      midpoint3d((float *)(marker0 + 0x28), (float *)(marker1 + 0x28), out_pos);
      out_axis[0] = global_zero_vector_ptr[0];
      out_axis[1] = global_zero_vector_ptr[1];
      out_axis[2] = global_zero_vector_ptr[2];
      *out_value = *(int *)(biped_tag + 0x458);
      return;
    }
    out_pos[0] = *(float *)(marker0 + 0x28);
    out_pos[1] = *(float *)(marker0 + 0x2c);
    out_pos[2] = *(float *)(marker0 + 0x30);
    out_axis[0] = *(float *)(marker1 + 0x28) - *(float *)(marker0 + 0x28);
    out_axis[1] = *(float *)(marker1 + 0x2c) - *(float *)(marker0 + 0x2c);
    out_axis[2] = *(float *)(marker1 + 0x30) - *(float *)(marker0 + 0x30);
    *out_value = *(int *)(biped_tag + 0x458);
    return;
  }

  biped_get_camera_height_and_offset(unit_handle, (vector3_t *)out_pos,
                                     &height_offset, &camera_height);
  half = height_offset * *(float *)0x253398;
  out_pos[2] = half + out_pos[2];
  out_axis[0] = half * global_up_vector_ptr[0];
  out_axis[1] = half * global_up_vector_ptr[1];
  out_axis[2] = half * global_up_vector_ptr[2];
  *out_value = *(int *)(biped_tag + 0x458);
}

/* biped_fix_position (0x1a1430)
 *
 * Tries to find a collision-free world position for a biped (used when
 * teleporting it out of a vehicle seat, respawning, etc.). Starting from an
 * initial position (either supplied via initial_position, or the biped's
 * estimated camera/standing position when NULL), it walks a fixed table of
 * displacement directions at 0x2b4b80 (stride 3 floats), scaling each by
 * `scale`. For each candidate it (1) finds the BSP3D leaf, rejecting points
 * outside the BSP; (2) runs a battery of collision tests (FUN_0014f020 sphere
 * fit, FUN_0014e7d0 vector-to-surface, and when a seat is involved the
 * FUN_0014cc80 / FUN_000130d0 line-of-sight checks against both objects). The
 * first candidate that passes all gates becomes the fixed location: the biped
 * object's position (obj+0xc) is updated, children are re-parented, and the
 * object is translated to the new location (unless dont_teleport). The final
 * world point is optionally written to final_position. Returns 1 on success.
 *
 * The whole search runs inside the collision-user-depth stack (global
 * 0x4761d8 / stack 0x5a8c80, marker 7), asserting depth < 0x20 on entry
 * (line 0x37f) and > 1 on exit (line 0x438).
 *
 * Confirmed (disasm): cdecl, 8 stack params, char return. param_4 is float*
 *   (3-float out-write at 0x1a1891). param_6/7/8 are byte flags (TEST AL,AL).
 *   collision_flags = (biped_tag+0x2f4 & 0x20) ? 0x20c3a0 : (0x20c3a0 +
 *   0xffdfff00) via NEG/SBB/AND/ADD. The direction-search count is branchless:
 *   loop_limit = 0x1b - ((p6!=0)-1 & 9) -> 0x1b when p6, 0x12 when !p6.
 *   The cross product cross = normalize3d(forward_axis x up_axis) is built from
 *   the biped's basis rows at obj+0x24 (right) and obj+0x30 (up); FSUBP order
 *   preserved from disasm. final candidate stored at local_14/10/c.
 * Inferred: the 0x2b4b80 table is a spiral/expanding set of search offsets;
 *   collision_flags low bits select the collision material/group mask.
 * Uncertain: exact field meanings inside the 130d0 collision result buffer
 *   beyond the hit-object-handle word at +0x38 (compared to the two unit
 *   handles to skip self/seat hits).
 */
char biped_fix_position(int unit_handle, int seat_handle,
                        float *initial_position, float *final_position,
                        float scale, char keep_basis, char dont_teleport,
                        char scale_by_height)
{
  unsigned int *biped_obj;
  int biped_tag;
  int depth;
  unsigned char success;
  short i;
  short loop_limit;
  int from_seat;
  int collision_flags;
  int leaf_index;
  int bsp;
  int leaf_elem;
  float *src_pos;
  float *basis; /* biped_obj as float[] — basis-matrix rows at +0x24..0x38 */
  float position[3]; /* local_2c/28/24 */
  float camera_height; /* local_18 ([EBP-0x18], 1a0890 arg4) */
  float height_offset; /* local_1c ([EBP-0x1c], 1a0890 arg3) */
  float offset_vec[3]; /* local_4c/48/44 */
  float cross[3]; /* local_40/3c/38 */
  float fx, fy;
  float candidate[3]; /* local_14: candidate.x; local_10/c/8 below */
  float cand[3]; /* local_10/c/8 — the BSP query point */
  /* Out buffers passed to collision callees. Sized per each callee's writes;
   * preserve sizes to keep the original 0x538 frame layout. */
  char center[12]; /* local_64 — 1aae0 sphere center / 130d0 args */
  char box[16]; /* local_74 — 14c8e0 out, reused as 14cc80 arg1 */
  char location[16]; /* local_58/54/50 — scenario_location_from_point */
  char surf_result[80]; /* local_114 — 14e7d0 result */
  char los_result[80]; /* local_c4 — 130d0 result; +0x38 = hit handle.
                        * 130d0 delegates to 14df70, which writes an 0x50-byte
                        * result (units.c:9404, projectiles.c collision_result
                        * [0x50]); original frame gap local_c4..local_74 is
                        * exactly 0x50. At 56 bytes it overflowed into box[],
                        * corrupting the 14cc80 context (tag_groups.c:3086
                        * element_size assert on seat exit). */
  static char obstruction[1064]; /* local_53c — 14cc80 working buffer */

  success = 0;
  if ((final_position == (float *)0) && (dont_teleport != '\0')) {
    display_assert("final_position || !dont_teleport",
                   "c:\\halo\\SOURCE\\units\\bipeds.c", 0x37d, true);
    system_exit(-1);
  }
  if (*(int16_t *)0x4761d8 >= 0x20) {
    display_assert("global_current_collision_user_depth < "
                   "MAXIMUM_COLLISION_USER_STACK_DEPTH",
                   "c:\\halo\\SOURCE\\units\\bipeds.c", 0x37f, true);
    system_exit(-1);
  }
  depth = *(int16_t *)0x4761d8;
  *(int16_t *)0x4761d8 = (int16_t)(depth + 1);
  *(int16_t *)(0x5a8c80 + depth * 2) = 7;

  /* Branch structure preserved from disasm (0x1a14aa): call FUN_0001aae0 only
   * when a seat is involved, jumping straight to the epilogue when both handles
   * are NONE. */
  if (unit_handle == -1) {
    if (seat_handle == -1) {
      goto epilogue;
    }
    goto call_aae0;
  }
  if (seat_handle != -1) {
  call_aae0:
    FUN_0001aae0(seat_handle, (float *)center, (float *)&from_seat);
  }
  {
    from_seat = (unit_handle == -1);
    if (from_seat) {
      unit_handle = seat_handle;
    }
    biped_obj = (unsigned int *)object_get_and_verify_type(unit_handle, 1);
    biped_tag = (int)tag_get(0x62697064, *biped_obj); /* 'bipd' */
    collision_flags =
      (-(int)((*(unsigned int *)(biped_tag + 0x2f4) & 0x20) != 0) &
       0xffdfff00) +
      0x20c3a0;

    if (initial_position == (float *)0) {
      src_pos = &position[0];
    } else {
      position[0] = initial_position[0];
      position[1] = initial_position[1];
      position[2] = initial_position[2];
      src_pos = &offset_vec[0];
    }
    biped_get_camera_height_and_offset(unit_handle, (vector3_t *)src_pos,
                                       &height_offset, &camera_height);
    if (from_seat) {
      unit_handle = -1;
    }
    loop_limit = (short)(0x1b - ((keep_basis != '\0') - 1 & 9));
    if (seat_handle != -1) {
      FUN_0014c8e0((int *)box, seat_handle);
    }
    /* cross = right_axis(obj+0x24) x up_axis(obj+0x30); normalize. The basis
     * rows at obj+0x24..0x38 are floats; load them as floats (FLD), not via
     * int->float conversion. FSUBP order preserved exactly from disasm. */
    basis = (float *)biped_obj;
    cross[0] = basis[0xe] * basis[0xa] - basis[0xb] * basis[0xd];
    cross[1] = basis[0xb] * basis[0xc] - basis[9] * basis[0xe];
    cross[2] = basis[9] * basis[0xd] - basis[0xc] * basis[0xa];
    normalize3d(&cross[0]);
    offset_vec[0] = height_offset * global_up_vector_ptr[0];
    offset_vec[1] = height_offset * global_up_vector_ptr[1];
    offset_vec[2] = height_offset * global_up_vector_ptr[2];
    if (scale_by_height != '\0') {
      scale = camera_height * scale;
    }

    i = 0;
    while ((short)i < loop_limit) {
      leaf_index = (int)(short)i;
      if (keep_basis == '\0') {
        cand[0] = scale * ((float *)0x2b4b80)[leaf_index * 3] + position[0];
        cand[1] = scale * ((float *)0x2b4b84)[leaf_index * 3] + position[1];
        cand[2] = scale * ((float *)0x2b4b88)[leaf_index * 3] + position[2];
      } else {
        fx = scale * ((float *)0x2b4b80)[leaf_index * 3];
        fy = scale * ((float *)0x2b4b84)[leaf_index * 3];
        candidate[2] = scale * ((float *)0x2b4b88)[leaf_index * 3];
        cand[0] = candidate[2] * basis[0xc] + cross[0] * fy + fx * basis[9] +
                  position[0];
        cand[1] = candidate[2] * basis[0xd] + cross[1] * fy + fx * basis[0xa] +
                  position[1];
        cand[2] = candidate[2] * basis[0xe] + cross[2] * fy + fx * basis[0xb] +
                  position[2];
      }

      if (FUN_0018e720((int)&cand[0]) != -1) {
        leaf_index = FUN_0018e720((int)&cand[0]) & 0x7fffffff;
        bsp = (int)scenario_get();
        leaf_elem =
          (int)tag_block_get_element((void *)(bsp + 0xe0), leaf_index, 0x10);
        if ((*(short *)(leaf_elem + 8) != -1) &&
            (FUN_0014f020((uint32_t)collision_flags, &cand[0],
                          camera_height + camera_height, height_offset,
                          camera_height, unit_handle, &cand[0]) != '\0') &&
            (FUN_0014e7d0((uint32_t)collision_flags, &cand[0], &offset_vec[0],
                          camera_height, unit_handle, surf_result) == '\0') &&
            ((seat_handle == -1) ||
             ((FUN_0014cc80((int)box, (int)&cand[0], (int)&offset_vec[0],
                            camera_height, (int16_t *)obstruction) == '\0') &&
              ((FUN_000130d0((uint32_t)collision_flags, &cand[0],
                             (float *)center, unit_handle,
                             (int16_t *)los_result) == 0) ||
               (*(int *)(los_result + 0x38) == seat_handle)) &&
              ((FUN_000130d0((uint32_t)collision_flags, (float *)center,
                             &cand[0], seat_handle,
                             (int16_t *)los_result) == 0) ||
               (*(int *)(los_result + 0x38) == unit_handle))))) {
          biped_tag = (int)tag_get(0x62697064, *biped_obj);
          scenario_location_from_point(location, &cand[0]);
          if (*(short *)(location + 4) == -1) {
            display_assert("fixed_location.cluster_index!=NONE",
                           "c:\\halo\\SOURCE\\units\\bipeds.c", 0x41e, true);
            system_exit(-1);
          }
          if ((*(unsigned char *)(biped_tag + 0x2f4) & 8) == 0) {
            cand[2] = cand[2] - *(float *)(biped_tag + 0x42c);
          }
          if ((unit_handle != -1) && (dont_teleport == '\0')) {
            biped_obj[3] = *(unsigned int *)&cand[0];
            biped_obj[4] = *(unsigned int *)&cand[1];
            biped_obj[5] = *(unsigned int *)&cand[2];
            object_update_children_recursive(unit_handle);
            object_translate(unit_handle, &cand[0], location);
          }
          if (final_position != (float *)0) {
            final_position[0] = cand[0];
            final_position[1] = cand[1];
            final_position[2] = cand[2];
          }
          success = 1;
        }
      }
      i = (short)(i + 1);
      if (success != 0) {
        break;
      }
    }
  }

epilogue:
  if (*(int16_t *)0x4761d8 < 2) {
    display_assert("global_current_collision_user_depth > 1",
                   "c:\\halo\\SOURCE\\units\\bipeds.c", 0x438, true);
    system_exit(-1);
  }
  *(int16_t *)0x4761d8 = (int16_t)(*(int16_t *)0x4761d8 - 1);
  return (char)success;
}

/* biped_render_debug (0x1a1900)
 *
 * Debug-visualization for a biped's camera/aim geometry, gated by two debug
 * globals. When 0x5054fe is set, draws the camera height/offset: if the height
 * offset is at/below the small threshold (0x2533c0), renders a point
 * (FUN_00189540); otherwise scales the world-up vector by the height offset and
 * renders a vector arrow (FUN_00189860). When 0x5054fd is set, fetches the
 * autoaim pill (biped_get_autoaim_pill) and renders the axis as an arrow if its
 * squared length exceeds the threshold, else a point. Render context pointers
 * come from [0x2ee6c4] (camera) and [0x2ee6d0] (autoaim).
 *
 * Confirmed: out_pos vec3 at EBP-0x20, scaled vec3 at EBP-0x14, height_offset
 * at EBP-0x8, camera_height/val at EBP-0x4; camera call arg order; up vector
 * from [0x31fc44]; squared-length FPU order is z,y,x; threshold [0x2533c0].
 * Inferred: "render debug" semantics from the two render_debug.c helpers and
 * the debug-global gating.
 */
void biped_render_debug(int unit_handle)
{
  vector3_t out_pos;
  float scaled[3];
  float height_offset;
  float camera_height;

  if (*(char *)0x5054fe != '\0') {
    biped_get_camera_height_and_offset(unit_handle, &out_pos, &height_offset,
                                       &camera_height);
    if (*(float *)0x2533c0 < height_offset) {
      scaled[0] = height_offset * global_up_vector_ptr[0];
      scaled[1] = height_offset * global_up_vector_ptr[1];
      scaled[2] = height_offset * global_up_vector_ptr[2];
      FUN_00189860(1, &out_pos, scaled, camera_height, *(void **)0x2ee6c4);
    } else {
      FUN_00189540(1, &out_pos, camera_height, *(void **)0x2ee6c4);
    }
  }
  if (*(char *)0x5054fd != '\0') {
    biped_get_autoaim_pill(unit_handle, (float *)&out_pos, scaled,
                           (int *)&camera_height);
    if (*(float *)0x2533c0 <
        scaled[2] * scaled[2] + scaled[1] * scaled[1] + scaled[0] * scaled[0]) {
      FUN_00189860(1, &out_pos, scaled, camera_height, *(void **)0x2ee6d0);
      return;
    }
    FUN_00189540(1, &out_pos, camera_height, *(void **)0x2ee6d0);
  }
}

/* FUN_001a1a10 (0x1a1a10)
 *
 * Casts a collision ray (vector) from the unit's world position along a caller-
 * supplied direction (scaled) and reports the hit. Computes the ray origin as
 * the unit's world position nudged by a global offset vector ([0x31fc44]) times
 * a global scale ([0x253524]); the ray direction is the caller's direction
 * vector (@eax) times the caller-supplied scale ([EBP+8]). Brackets the work in
 * the collision-user-depth stack (global 0x4761d8 / stack 0x5a8c80, marker 7),
 * asserting depth < 0x20 on entry (line 0x47a) and > 1 on exit (line 0x490).
 * Runs collision_bsp_test_vector against the global collision BSP. On a hit and
 * if out_point != NULL, writes the world-space hit point
 * (out_point[i] = scaled_dir[i] * t + origin[i]); if out_vec != NULL, copies
 * the 3-float surface record pointed to by result+4 into out_vec. Returns the
 * hit surface/leaf index (result+8) on hit, or -1 on miss.
 *
 * Confirmed (disasm): cdecl, returns int in EAX (MOV EAX,ESI; ESI = -1 default
 *   / result+8 on hit). Register args: @eax = direction vector pointer
 *   (MOV ESI,EAX; FMUL [ESI]/[ESI+4]/[ESI+8]); @edi = unit_handle (PUSH EDI ->
 *   object_get_and_verify_type(.,1)). Stack args [EBP+8]=float scale,
 *   [EBP+0xc]=float *out_point, [EBP+0x10]=void *out_vec (caller 0x1a1b90:
 *   PUSH 0x40000000 (2.0f), PUSH out_point, PUSH 0x0; EAX=[0x31fc50],
 *   EDI=unit_handle). collision_bsp_test_vector takes 8 args; its 0x20 cleanup
 *   is combined with object_get_world_position's deferred 8-byte cleanup
 *   (ADD ESP,0x28 = 0x20 + 8). The collision-result buffer is ONE contiguous
 *   region at EBP-0x434: result+0=t (float), result+4=surface-record pointer
 *   (3 floats copied to out_vec), result+8=hit index (return). Ghidra's
 *   local_438/local_434/local_430 are this single buffer, not separate locals.
 * Inferred: origin offset/scale semantics from the FADD-into-world-position
 *   shape; "supporting/forward ray" usage from the 2.0f scale and out params.
 * Uncertain: exact meaning of globals [0x31fc44] (offset vector) and [0x253524]
 *   (scale); full layout of the 0x414-byte collision-result buffer beyond the
 *   three fields read here.
 */
int FUN_001a1a10(float scale, float *out_point, void *out_vec,
                 float *direction /* @eax */, int unit_handle /* @edi */)
{
  /* One contiguous collision-result buffer (frame base EBP-0x434). Sized to
   * cover collision_bsp_test_vector's full record (mirrors path.c's
   * local_438[264]); we read t at +0, a surface-record pointer at +4, and the
   * hit index at +8. Do NOT split into separate locals. */
  float collision_result[264];
  int result_index;
  int depth;
  void *bsp;
  float *offset_vec;
  float *surface_record;
  float t;
  float origin[3];
  float scaled_dir[3];
  float dir0;

  object_get_and_verify_type(unit_handle, 1);
  bsp = global_collision_bsp_get();
  result_index = -1;
  dir0 = direction[0];

  if (*(int16_t *)0x4761d8 >= 0x20) {
    display_assert("global_current_collision_user_depth < "
                   "MAXIMUM_COLLISION_USER_STACK_DEPTH",
                   "c:\\halo\\SOURCE\\units\\bipeds.c", 0x47a, true);
    system_exit(-1);
  }
  depth = *(int16_t *)0x4761d8;
  *(int16_t *)0x4761d8 = (int16_t)(depth + 1);
  *(int16_t *)(0x5a8c80 + depth * 2) = 7;

  object_get_world_position(unit_handle, (vector3_t *)origin);

  offset_vec = *(float **)0x31fc44;
  origin[0] = offset_vec[0] * *(float *)0x253524 + origin[0];
  origin[1] = offset_vec[1] * *(float *)0x253524 + origin[1];
  origin[2] = offset_vec[2] * *(float *)0x253524 + origin[2];

  scaled_dir[0] = scale * dir0;
  scaled_dir[1] = scale * direction[1];
  scaled_dir[2] = scale * direction[2];

  if ((char)collision_bsp_test_vector(1, (int)bsp, 0, 0, (int)origin,
                                      (int)scaled_dir, 3.4028235e+38f,
                                      collision_result) != 0) {
    t = collision_result[0];
    if (out_point != (float *)0) {
      out_point[0] = scaled_dir[0] * t + origin[0];
      out_point[1] = scaled_dir[1] * t + origin[1];
      out_point[2] = scaled_dir[2] * t + origin[2];
    }
    result_index = *(int *)((char *)collision_result + 8);
    if (out_vec != (void *)0) {
      surface_record = *(float **)((char *)collision_result + 4);
      ((int *)out_vec)[0] = ((int *)surface_record)[0];
      ((int *)out_vec)[1] = ((int *)surface_record)[1];
      ((int *)out_vec)[2] = ((int *)surface_record)[2];
    }
  }

  if (*(int16_t *)0x4761d8 <= 1) {
    display_assert("global_current_collision_user_depth > 1",
                   "c:\\halo\\SOURCE\\units\\bipeds.c", 0x490, true);
    system_exit(-1);
  }
  *(int16_t *)0x4761d8 = (int16_t)(*(int16_t *)0x4761d8 - 1);
  return result_index;
}

/* biped_approximate_surface_index (0x1a1b90)
 *
 * Thin wrapper over the biped collision probe (FUN_001a1a10): casts a ray of
 * length 2.0 from the biped's world position along the global direction vector
 * at [0x31fc50], with no surface-vector output. The keystone's collision-result
 * index is returned unchanged in EAX (-1 = no hit). out_point, when non-NULL,
 * receives the hit point.
 *
 * Confirmed (disasm 0x1a1b90): keystone direction@<eax> = *(float**)0x31fc50;
 * unit_handle@<edi> = param_1; cdecl pushes scale=2.0f (0x40000000),
 * out_point=param_2, out_vec=NULL; ADD ESP,0xc. No MOV EAX after CALL, so the
 * keystone return flows through (caller 0x56c60 tests the result == -1).
 */
#if defined(__clang__)
static int (*const biped_approx_probe)(float, float *, void *, float *, int) =
    FUN_001a1a10;

__attribute__((naked, noinline))
int biped_approximate_surface_index(int unit_handle __attribute__((unused)),
                                    float *out_point __attribute__((unused)))
{
  /* XBE: direction@eax from 0x31fc50, unit@edi, scale=2.0f on stack. */
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "movl 8(%%ebp), %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl 0x31fc50, %%eax\n\t"
      "pushl $0x40000000\n\t"
      "call *%[probe]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [probe] "m"(biped_approx_probe)
      : "memory");
}
#else
int biped_approximate_surface_index(int unit_handle, float *out_point)
{
  return FUN_001a1a10(2.0f, out_point, (void *)0, *(float **)0x31fc50,
                      unit_handle);
}
#endif

/* biped_find_pathfinding_surface_index (0x1a1bc0)
 *
 * Resolves the BSP surface index the biped is standing on for pathfinding,
 * caching it on the unit object. If the biped's tag wants the simple path
 * (tag+0x2f4 bit 2 set and unit+0xb6 bit 2 clear) it just clears the cached
 * index and calls object_get_world_position. Otherwise it lazily recomputes:
 * when the cache is stale (unit+0x434 == -1 and game_time advanced past
 * unit+0x444), it snapshots the cached position (unit+0x438..0x440), and tries
 * to re-project onto the previous surface (unit+0x430 last-good, else
 * unit+0x448 last-result) via the collision_surface_* helpers; if that fails it
 * falls back to a fresh 2.0-length collision probe. On success it stores the
 * new position and surface index. Finally it always copies the cached position
 * (unit+0x438) into *pos and returns the cached index (unit+0x434).
 *
 * Confirmed (disasm 0x1a1bc0): object_get_and_verify_type(unit_handle,1);
 * tag_get('bipd', obj[0]); game_time_get; global_collision_bsp_get; keystone
 * direction@<eax>=*(float**)0x31fc50, unit_handle@<edi>=unit_handle, push
 * scale=2.0f,&pos_buf,NULL. collision_surface helper arg counts from disasm
 * (test_point2d=5 args ret char, find_closest/project=6 args). Position vec3 at
 * EBP-0x14, 2D scratch at EBP-0x8. display_assert at :0x4e7 if pos==NULL.
 *
 * Unit field offsets (dword index in the disasm): 0x430=last_good_surface
 * (0x10c), 0x434=cached_surface_index (0x10d), 0x438=cached_position[3]
 * (0x10e/0x10f/0x110), 0x444=cache_timestamp (0x111), 0x448=last_result_surface
 * (0x112).
 */
int biped_find_pathfinding_surface_index(int unit_handle, vector3_t *pos)
{
  int *unit_obj;
  int tag;
  int game_time;
  void *bsp;
  float position[3]; /* EBP-0x14: snapshot/output position vec3 */
  float proj2d[2]; /* EBP-0x8: 2D projected scratch point */
  char projected;

  unit_obj = (int *)object_get_and_verify_type(unit_handle, 1);
  tag = (int)tag_get(0x62697064, *unit_obj);
  if (((*(unsigned char *)(tag + 0x2f4) & 4) != 0) &&
      ((*(unsigned char *)((char *)unit_obj + 0xb6) & 4) == 0)) {
    unit_obj[0x10d] = -1;
    object_get_world_position(unit_handle, pos);
  } else if ((unit_obj[0x10d] == -1) &&
             (game_time = game_time_get(), game_time > unit_obj[0x111])) {
    bsp = global_collision_bsp_get();
    position[0] = ((float *)(unit_obj + 0x10e))[0];
    position[1] = ((float *)(unit_obj + 0x10e))[1];
    position[2] = ((float *)(unit_obj + 0x10e))[2];
    unit_obj[0x111] = game_time;
    if (unit_obj[0x10c] != -1) {
      collision_surface_find_closest_point2d(
        (int)bsp, unit_obj[0x10c], 2, 1, (float *)(unit_obj + 0x10e), proj2d);
      collision_surface_project_point2d((int)bsp, unit_obj[0x10c], 2, 1, proj2d,
                                        position);
      unit_obj[0x10d] = unit_obj[0x10c];
    } else if ((unit_obj[0x112] != -1) &&
               (projected = (char)collision_surface_test_point2d(
                  (int)bsp, unit_obj[0x112], 2, 1, (float *)(unit_obj + 0x10e)),
                projected != 0)) {
      unit_obj[0x10d] = unit_obj[0x112];
      collision_surface_project_point2d((int)bsp, unit_obj[0x112], 2, 1,
                                        (float *)(unit_obj + 0x10e), position);
      unit_obj[0x10d] = unit_obj[0x112];
    }
    if (unit_obj[0x10d] == -1) {
      unit_obj[0x10d] = FUN_001a1a10(2.0f, position, (void *)0,
                                     *(float **)0x31fc50, unit_handle);
    }
    if (unit_obj[0x10d] != -1) {
      ((float *)(unit_obj + 0x10e))[0] = position[0];
      ((float *)(unit_obj + 0x10e))[1] = position[1];
      ((float *)(unit_obj + 0x10e))[2] = position[2];
      unit_obj[0x112] = unit_obj[0x10d];
    }
  }

  if (pos == (vector3_t *)0) {
    display_assert("pathfinding_point", "c:\\halo\\SOURCE\\units\\bipeds.c",
                   0x4e7, true);
    system_exit(-1);
  }
  ((int *)pos)[0] = unit_obj[0x10e];
  ((int *)pos)[1] = unit_obj[0x10f];
  ((int *)pos)[2] = unit_obj[0x110];
  return unit_obj[0x10d];
}

/* biped_exit_seat_end (0x1a1d80)
 *
 * Finishes a biped exiting a vehicle seat. Flattens the biped's exit forward
 * vector (unit+0x24) to horizontal (zeroes z at unit+0x2c) and renormalizes,
 * falling back to the world forward axis if degenerate; sets the exit up
 * vector (unit+0x30) to world up; sets unit+0x424 bit0. Then tries to fix the
 * biped's position out of the vehicle: first with a fixed 2.0 distance, and if
 * that fails, using the vehicle's bounding sphere; logs a warning if still
 * unable.
 *
 * Confirmed: object_get_and_verify_type(unit_handle, 1); tag_get('bipd', ...)
 * (result discarded). normalize3d(unit+0x24); fallback = global forward axis;
 * unit+0x30 = global up axis. FUN_0001aae0 gets vehicle center+radius.
 * 2.0f arg pushed as 0x40000000.
 */
void biped_exit_seat_end(int unit_handle, int seat_handle)
{
  char *unit_obj;
  float center[3];
  float radius;
  char fixed;

  unit_obj = (char *)object_get_and_verify_type(unit_handle, 1);
  tag_get(0x62697064, *(int *)unit_obj);

  *(int *)(unit_obj + 0x2c) = 0;
  if (normalize3d((float *)(unit_obj + 0x24)) == 0.0f) {
    *(float *)(unit_obj + 0x24) = global_forward_vector_ptr[0];
    *(float *)(unit_obj + 0x28) = global_forward_vector_ptr[1];
    *(float *)(unit_obj + 0x2c) = global_forward_vector_ptr[2];
  }
  *(float *)(unit_obj + 0x30) = global_up_vector_ptr[0];
  *(float *)(unit_obj + 0x34) = global_up_vector_ptr[1];
  *(float *)(unit_obj + 0x38) = global_up_vector_ptr[2];
  *(int *)(unit_obj + 0x424) |= 1;

  fixed =
    biped_fix_position(unit_handle, seat_handle, (float *)0, 0, 2.0f, 1, 0, 1);
  if (fixed == 0) {
    FUN_0001aae0(seat_handle, center, &radius);
    fixed =
      biped_fix_position(unit_handle, seat_handle, center, 0, radius, 1, 0, 0);
    if (fixed == 0) {
      error(2, "couldn't teleport the biped out far enough from the vehicle"
               "...");
    }
  }
}

/* FUN_001a1e70 (0x1a1e70)
 *
 * Per-tick "is this biped stuck falling / off a ledge?" check for AI bipeds.
 * After a battery of eligibility gates (not in a vehicle, tag flags clear,
 * not flying, has a valid path leader, not in scream state 0x1d, settle timer
 * past 0x1e, and a throttled recheck interval of game_time+0xf), it casts a
 * 6.0-length probe from the biped along the global direction at [0x31fc50].
 * If the probe misses, OR (after fetching the biped's world position) the
 * biped's clearance field (obj+0x20) is small and the vertical drop to the
 * probe point exceeds the physics fall threshold (physics+0x94 squared), it
 * triggers the recovery path FUN_001a74d0(unit_handle, 0).
 *
 * Confirmed (disasm 0x1a1e70): cdecl unit_handle at [EBP+8] (caller 0x1a6350
 * PUSH EDI; ADD ESP,4); object_get_and_verify_type(unit,1); tag_get('bipd');
 * game_time_get; tag_block_get_element(game_globals_get()+0x188, 0, 0x98);
 * keystone direction@<eax>=*(float**)0x31fc50, unit@<edi>, scale=6.0f
 * (0x40c00000); object_get_world_position; FUN_001a74d0(unit,0). Return
 * discarded (void).
 *
 * Inferred: obj+0x20 = clearance/height float; physics+0x94 = fall-distance
 * threshold; DAT_0032512c gravity-related scalar. Probe hit point and world
 * position are separate 3-float stack buffers.
 */
#if defined(__clang__)
static void *(*const a1e70_get)(int, int) = object_get_and_verify_type;
static void *(*const a1e70_tag)(int, int) = tag_get;
static int (*const a1e70_gtime)(void) = game_time_get;
static void *(*const a1e70_gg)(void) = game_globals_get;
static void *(*const a1e70_elem)(void *, int, int) = tag_block_get_element;
static int (*const a1e70_probe)(float, float *, void *, float *, int) = FUN_001a1a10;
static vector3_t *(*const a1e70_wpos)(int, vector3_t *) = object_get_world_position;
static char (*const a1e70_recover)(int, int) = FUN_001a74d0;

__attribute__((naked, noinline))
void FUN_001a1e70(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "movl 8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movb 182(%%esi), %%cl\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $4, %%cl\n\t"
      "jne .LFUN_001a1e70_4\n\t"
      "testb $0x84, 756(%%eax)\n\t"
      "jne .LFUN_001a1e70_4\n\t"
      "movl 436(%%esi), %%eax\n\t"
      "testb $0x10, %%ah\n\t"
      "jne .LFUN_001a1e70_4\n\t"
      "cmpl $-1, 420(%%esi)\n\t"
      "je .LFUN_001a1e70_4\n\t"
      "cmpb $0x1d, 595(%%esi)\n\t"
      "je .LFUN_001a1e70_4\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, %%edi\n\t"
      "cmpb $0x1e, 1113(%%esi)\n\t"
      "jle .LFUN_001a1e70_3\n\t"
      "movl 1104(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001a1e70_1\n\t"
      "addl $0xf, %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jge .LFUN_001a1e70_3\n\t"
      ".LFUN_001a1e70_1:\n\t"
      "pushl $0x98\n\t"
      "pushl $0\n\t"
      "call *%[gg]\n\t"
      "addl $0x188, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "pushl $0\n\t"
      "leal -24(%%ebp), %%edx\n\t"
      "movl %%edi, 1104(%%esi)\n\t"
      "movl 8(%%ebp), %%edi\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x31fc50, %%eax\n\t"
      "pushl $0x40c00000\n\t"
      "call *%[probe]\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001a1e70_2\n\t"
      "leal -12(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[wpos]\n\t"
      "flds 32(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001a1e70_3\n\t"
      "flds 32(%%esi)\n\t"
      "flds 148(%%ebx)\n\t"
      "flds -4(%%ebp)\n\t"
      "fsubs -16(%%ebp)\n\t"
      "fmuls 0x32512c\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(1)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "je .LFUN_001a1e70_3\n\t"
      ".LFUN_001a1e70_2:\n\t"
      "movl 8(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[recover]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001a1e70_3:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001a1e70_4:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(a1e70_get), [tag] "m"(a1e70_tag), [gtime] "m"(a1e70_gtime), [gg] "m"(a1e70_gg), [elem] "m"(a1e70_elem), [probe] "m"(a1e70_probe), [wpos] "m"(a1e70_wpos), [recover] "m"(a1e70_recover)
      : "memory");
}
#else
void FUN_001a1e70(int unit_handle)
{
  int *unit_obj;
  int tag;
  int game_time;
  int physics;
  float fall_term;
  float probe_hit[3];
  float world_pos[3];
  float *dir_ptr;

  unit_obj = (int *)object_get_and_verify_type(unit_handle, 1);
  tag = (int)tag_get(0x62697064, *unit_obj);
  if (((*(unsigned char *)((char *)unit_obj + 0xb6) & 4) == 0) &&
      ((*(unsigned char *)(tag + 0x2f4) & 0x84) == 0) &&
      ((unit_obj[0x6d] & 0x1000) == 0) && (unit_obj[0x69] != -1) &&
      (*(char *)((char *)unit_obj + 0x253) != 0x1d)) {
    game_time = game_time_get();
    if ((*(char *)((char *)unit_obj + 0x459) > 0x1e) &&
        ((unit_obj[0x114] == -1) || (unit_obj[0x114] + 0xf < game_time))) {
      physics =
        (int)tag_block_get_element((char *)game_globals_get() + 0x188, 0, 0x98);
      unit_obj[0x114] = game_time;
      dir_ptr = *(float **)0x31fc50;
      if ((FUN_001a1a10(6.0f, probe_hit, (void *)0, dir_ptr, unit_handle) ==
           -1) ||
          (object_get_world_position(unit_handle, (vector3_t *)world_pos),
           *(float *)((char *)unit_obj + 0x20) <= *(float *)0x2533c0 &&
             (fall_term = (world_pos[2] - probe_hit[2]) * *(float *)0x32512c,
              *(float *)(physics + 0x94) * *(float *)(physics + 0x94) <=
                *(float *)((char *)unit_obj + 0x20) *
                    *(float *)((char *)unit_obj + 0x20) +
                  fall_term + fall_term))) {
        FUN_001a74d0(unit_handle, 0);
      }
    }
  }
}
#endif


/* FUN_001a1fb0 (0x1a1fb0)
 *
 * Vehicle-rider variant of the stuck/ejection check (mirrors FUN_001a1e70 for a
 * biped riding a vehicle seat). Gates on the vehicle tag flag (vehi+0x17c bit
 * 6), the biped having a seat (obj+0x1a4 != -1), not in scream state 0x1d, a
 * recheck throttle field (obj+0x2d2 > 'x'), the vehicle settle counter
 * (vehi+0x428 > 0x1e), and a game_time+0xf interval on obj+0x450. It first
 * probes straight (8.0 length) along [0x31fc50]; if that misses it computes a
 * scaled velocity vector from the vehicle physics (phys+0x18/0x1c/0x20 times
 * DAT_2b4ee4, with a gravity bias on z), and if that vector's length is large
 * enough re-probes along it. Depending on which probe/threshold fails it logs
 * one of three eject reasons (0x26/0x27/0x28) via FUN_00046f10(reason,
 * unit_handle, -1,-1,-1,-1, 0).
 *
 * Confirmed (disasm 0x1a1fb0): register arg unit_handle@<eax> (MOV EDI,EAX at
 * 0x1a1fb9; caller 0x1a6350 MOV EAX,EDI; CALL with no stack arg). vehi =
 * object_get_and_verify_type(object_get_and_verify_type(unit,1)->[0xcc], 2);
 * tag_get('vehi'). keystone: 1st call direction@<eax>=*(float**)0x31fc50,
 * scale=8.0f, out_point=0, out_vec=0; 2nd call direction@<eax>=&scaled_vel,
 * scale=8.0f, out_point=0, out_vec=&probe_vec. unit@<edi> on both.
 * FUN_00046f10 args: 7 pushes (reason, EDI=unit, -1,-1,-1,-1, 0). Void.
 *
 * Inferred: DAT_2b4ee4 velocity scalar, DAT_2b4ee0/DAT_32512c gravity bias;
 * obj fields 0x1a4 seat, 0x253 scream, 0x2d2 throttle byte; vehi+0x428 settle;
 * obj+0x450 recheck timestamp. phys[6..8] = obj+0x18/0x1c/0x20 vehicle
 * velocity.
 */
#if defined(__clang__)
static void *(*const a1fb0_get)(int, int) = object_get_and_verify_type;
static void *(*const a1fb0_tag)(int, int) = tag_get;
static int (*const a1fb0_gtime)(void) = game_time_get;
static int (*const a1fb0_probe)(float, float *, void *, float *, int) = FUN_001a1a10;
static float (*const a1fb0_norm)(float *) = normalize3d;
static void (*const a1fb0_logevt)(int16_t, int, int, int, int16_t, int16_t, int16_t) = FUN_00046f10;
static float (*const a1fb0_mag)(float *) = FUN_00012fe0;

__attribute__((naked, noinline))
void FUN_001a1fb0(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 204(%%esi), %%eax\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x76656869\n\t"
      "call *%[tag]\n\t"
      "movb 380(%%eax), %%cl\n\t"
      "addl $0x18, %%esp\n\t"
      "testb $0x40, %%cl\n\t"
      "je .LFUN_001a1fb0_5\n\t"
      "cmpl $-1, 420(%%esi)\n\t"
      "je .LFUN_001a1fb0_5\n\t"
      "cmpb $0x1d, 595(%%esi)\n\t"
      "je .LFUN_001a1fb0_5\n\t"
      "cmpb $0x78, 722(%%esi)\n\t"
      "jle .LFUN_001a1fb0_5\n\t"
      "call *%[gtime]\n\t"
      "cmpb $0x1e, 1064(%%ebx)\n\t"
      "jbe .LFUN_001a1fb0_5\n\t"
      "movl 1104(%%esi), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_001a1fb0_1\n\t"
      "addl $0xf, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jge .LFUN_001a1fb0_5\n\t"
      ".LFUN_001a1fb0_1:\n\t"
      "pushl $0\n\t"
      "movl %%eax, 1104(%%esi)\n\t"
      "movl 0x31fc50, %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0x41000000\n\t"
      "call *%[probe]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_001a1fb0_3\n\t"
      "flds 24(%%ebx)\n\t"
      "leal -12(%%ebp), %%edx\n\t"
      "fmuls 0x2b4ee4\n\t"
      "pushl %%edx\n\t"
      "fstps -12(%%ebp)\n\t"
      "flds 28(%%ebx)\n\t"
      "fmuls 0x2b4ee4\n\t"
      "fstps -8(%%ebp)\n\t"
      "flds 32(%%ebx)\n\t"
      "fmuls 0x2b4ee4\n\t"
      "flds 0x32512c\n\t"
      "fmuls 0x2b4ee0\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -4(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a1fb0_2\n\t"
      "leal -24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0x41000000\n\t"
      "leal -12(%%ebp), %%eax\n\t"
      "call *%[probe]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001a1fb0_2\n\t"
      "flds -16(%%ebp)\n\t"
      "fcomps 0x2533e4\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001a1fb0_3\n\t"
      ".LFUN_001a1fb0_2:\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "pushl $0x28\n\t"
      "call *%[logevt]\n\t"
      "addl $0x1c, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a1fb0_3:\n\t"
      "flds 56(%%ebx)\n\t"
      "fcomps 0x253f3c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a1fb0_4\n\t"
      "addl $0x3c, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x26e2ec\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a1fb0_4\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "pushl $0x26\n\t"
      "call *%[logevt]\n\t"
      "addl $0x1c, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a1fb0_4:\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "pushl $0x27\n\t"
      "call *%[logevt]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_001a1fb0_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(a1fb0_get), [tag] "m"(a1fb0_tag), [gtime] "m"(a1fb0_gtime), [probe] "m"(a1fb0_probe), [norm] "m"(a1fb0_norm), [logevt] "m"(a1fb0_logevt), [mag] "m"(a1fb0_mag)
      : "memory");
}
#else
void FUN_001a1fb0(int unit_handle /* @eax */)
{
  int *unit_obj;
  int *vehi_obj;
  int tag;
  int game_time;
  int probe_vec[3]; /* EBP-0x18: 2nd keystone out_vec */
  float scaled_vel[3]; /* EBP-0xc: scaled vehicle velocity */

  unit_obj = (int *)object_get_and_verify_type(unit_handle, 1);
  vehi_obj = (int *)object_get_and_verify_type(unit_obj[0x33], 2);
  tag = (int)tag_get(0x76656869, *vehi_obj);
  if (((*(unsigned char *)(tag + 0x17c) & 0x40) != 0) &&
      (unit_obj[0x69] != -1) && (*(char *)((char *)unit_obj + 0x253) != 0x1d) &&
      (*(char *)((char *)unit_obj + 0x2d2) > 0x78)) {
    game_time = game_time_get();
    if ((*(unsigned char *)((char *)vehi_obj + 0x428) > 0x1e) &&
        ((unit_obj[0x114] == -1) || (unit_obj[0x114] + 0xf < game_time))) {
      unit_obj[0x114] = game_time;
      if (FUN_001a1a10(8.0f, (float *)0, (void *)0, *(float **)0x31fc50,
                       unit_handle) == -1) {
        scaled_vel[0] =
          *(float *)((char *)vehi_obj + 0x18) * *(float *)0x2b4ee4;
        scaled_vel[1] =
          *(float *)((char *)vehi_obj + 0x1c) * *(float *)0x2b4ee4;
        scaled_vel[2] =
          *(float *)((char *)vehi_obj + 0x20) * *(float *)0x2b4ee4 -
          *(float *)0x32512c * *(float *)0x2b4ee0;
        if (normalize3d(scaled_vel) <= *(float *)0x2533c0) {
          FUN_00046f10(0x28, unit_handle, -1, -1, -1, -1, 0);
          return;
        }
        if ((FUN_001a1a10(8.0f, (float *)0, probe_vec, scaled_vel,
                          unit_handle) == -1) ||
            (*(float *)&probe_vec[2] <= *(float *)0x2533e4)) {
          FUN_00046f10(0x28, unit_handle, -1, -1, -1, -1, 0);
          return;
        }
      }
      if (*(float *)0x253f3c < *(float *)((char *)vehi_obj + 0x38)) {
        if (FUN_00012fe0((float *)(vehi_obj + 0xf)) < *(float *)0x26e2ec) {
          FUN_00046f10(0x26, unit_handle, -1, -1, -1, -1, 0);
          return;
        }
      }
      FUN_00046f10(0x27, unit_handle, -1, -1, -1, -1, 0);
    }
  }
}
#endif


/* FUN_001a2160 (0x1a2160)
 *
 * Rotates a biped's forward/up axes (unit+0x24 fwd, unit+0x30 up) about the
 * axis stored at unit+0x3c by the angle equal to that axis vector's length.
 * Normalizes the axis (angle = |axis|), rotates the forward vector by
 * (sin,cos) of the angle and renormalizes it, then rebuilds an orthogonal up
 * vector via two cross products (cross(up_rot, fwd) then cross(temp, fwd)) and
 * renormalizes; on degenerate result, resets to world forward/up.
 *
 * Register arg: unit_handle in EAX. Confirmed: normalize3d (0x13010);
 * rotate_vector3d_by_sincos (0x10b6e0); x87 FCOS/FSIN; globals 0x31fc3c fwd,
 * 0x31fc44 up. Cross operand order transcribed from disassembly.
 */
void FUN_001a2160(int unit_handle)
{
  char *unit_obj;
  float axis[3];
  float up_rot[3];
  float t0;
  float t1;
  float t2;
  float angle;
  float cos_a;
  float sin_a;
  float *fwd;
  float *up_ptr;

  unit_obj = (char *)object_get_and_verify_type(unit_handle, 1);

  axis[0] = *(float *)(unit_obj + 0x3c);
  axis[1] = *(float *)(unit_obj + 0x40);
  axis[2] = *(float *)(unit_obj + 0x44);
  angle = normalize3d(axis);
  fwd = (float *)(unit_obj + 0x24);
#if defined(_MSC_VER) && !defined(__clang__)
  cos_a = (float)cos((double)angle);
  sin_a = (float)sin((double)angle);
#else
  cos_a = x87_fcos(angle);
  sin_a = x87_fsin(angle);
#endif
  rotate_vector3d_by_sincos(fwd, axis, sin_a, cos_a);
  normalize3d(fwd);

  up_ptr = (float *)(unit_obj + 0x30);
  up_rot[0] = up_ptr[0];
  up_rot[1] = up_ptr[1];
  up_rot[2] = up_ptr[2];
  rotate_vector3d_by_sincos(up_rot, axis, sin_a, cos_a);

  t0 = up_rot[2] * fwd[1] - up_rot[1] * fwd[2];
  t1 = up_rot[0] * fwd[2] - up_rot[2] * fwd[0];
  t2 = up_rot[1] * fwd[0] - up_rot[0] * fwd[1];
  /* up = cross(temp, fwd) — FPU LIFO: computed z,y,x, stored x,y,z */
  up_ptr[0] = t1 * fwd[2] - t2 * fwd[1];
  up_ptr[1] = t2 * fwd[0] - t0 * fwd[2];
  up_ptr[2] = t0 * fwd[1] - t1 * fwd[0];
  if (normalize3d(up_ptr) == 0.0f) {
    fwd[0] = global_forward_vector_ptr[0];
    fwd[1] = global_forward_vector_ptr[1];
    fwd[2] = global_forward_vector_ptr[2];
    up_ptr[0] = global_up_vector_ptr[0];
    up_ptr[1] = global_up_vector_ptr[1];
    up_ptr[2] = global_up_vector_ptr[2];
  }
}

/* FUN_001a2290 (0x1a2290)
 *
 * Attempts to make a biped "jump"/launch along its up axis. Skips if already
 * launched (unit+0x424 bit0) or in a blocking state (unit+0x460 == 1). Computes
 * a launch speed from the biped tag (tag+0x3b4), scaled down by the actor's
 * physics block and (if a global flag is set) a further factor. If the biped's
 * current velocity along up is below the launch speed, boosts it to the launch
 * speed. If actor-controlled, defers to actor_aim_jump (which can veto). On
 * success, writes back the velocity, marks launched (unit+0x424 bit0), clears
 * unit+0x45c, resets unit+0x430, and disconnects two structure-BSP markers.
 *
 * Register arg: unit_handle in EDI. Returns the success flag (char).
 * Confirmed offsets/calls from disassembly; max-speed denom uses arg reuse
 * (game_globals_get(0,0xf4) shares its 0/0xf4 with tag_block_get_element).
 */
char FUN_001a2290(int unit_handle)
{
  char *unit_obj;
  char *biped_tag;
  char *physics;
  float *vel_ptr;
  int actor_handle;
  int zero_idx;
  float max_speed;
  float vel[3];
  float *vel0_ptr;
  float dot;
  char success;
  char aim_flag;

  unit_obj = (char *)object_get_and_verify_type(unit_handle, 1);
  biped_tag = (char *)tag_get(0x62697064, *(int *)unit_obj);

  if ((*(unsigned char *)(unit_obj + 0x424) & 1) != 0) {
    return 0;
  }
  zero_idx = 0;
  if (*(short *)(unit_obj + 0x460) == 1) {
    return 0;
  }

  max_speed = *(float *)(biped_tag + 0x3b4);
  vel0_ptr = &vel[0];
  success = 1;
  if (*(int *)(unit_obj + 0x1c8) != -1) {
    physics = (char *)tag_block_get_element((char *)game_globals_get() + 0x170,
                                            0, 0xf4);
    max_speed = (*(float *)0x2533c8 -
                 *(float *)(unit_obj + 0x3d4) * *(float *)(physics + 0x84)) *
                max_speed;
  }
  if (*(char *)0x5aa894 != '\0' && *(int *)(unit_obj + 0x1c8) != -1) {
    max_speed = max_speed * *(float *)0x2533d8;
  }

  vel_ptr = (float *)(unit_obj + 0x18);
  vel[0] = vel_ptr[0];
  vel[1] = vel_ptr[1];
  vel[2] = vel_ptr[2];
  dot = vel[1] * *(float *)(unit_obj + 0x34) +
        vel[2] * *(float *)(unit_obj + 0x38) +
        vel[zero_idx] * *(float *)(unit_obj + 0x30);
  if (dot < max_speed) {
    dot = max_speed - dot;
    vel[zero_idx] = dot * *(float *)(unit_obj + 0x30) + *vel0_ptr;
    vel[1] = dot * *(float *)(unit_obj + 0x34) + vel[1];
    vel[2] = dot * *(float *)(unit_obj + 0x38) + vel[2];
  }

  actor_handle = *(int *)(unit_obj + 0x1a8);
  if (actor_handle == -1) {
    actor_handle = *(int *)(unit_obj + 0x1a4);
  }
  if (actor_handle != -1) {
    aim_flag = (*(char *)(unit_obj + 0x253) == 0x27 ||
                *(char *)(unit_obj + 0x253) == 0x28) ?
                 1 :
                 0;
    success =
      (char)actor_aim_jump(actor_handle, unit_handle, aim_flag, max_speed, vel);
    if (success == zero_idx) {
      return success;
    }
  }

  vel_ptr[0] = vel[0];
  vel_ptr[1] = vel[1];
  vel_ptr[2] = vel[2];
  *(int *)(unit_obj + 0x424) |= 1;
  *(unsigned char *)(unit_obj + 0x45c) = zero_idx;
  *(int *)(unit_obj + 0x430) = -1;
  FUN_001a0f10(unit_handle, 4, 0);
  FUN_001a0f10(unit_handle, 4, 1);
  return success;
}

/* FUN_001a2440 (0x1a2440) — per-tick footstep / animation-marker event step
 *
 * Step in the biped update dispatcher (FUN_001a6350). Classifies the biped's
 * movement state (object+0x253):
 *   - states 2,3  -> walking (is_walking)
 *   - states 4..7 -> moving fast enough if horizontal velocity squared
 *     (object+0x228..0x230) exceeds threshold 0x25337c (is_fast)
 * If the biped has an active animation (object+0x80 != NONE), looks up the
 * 'antr' animation graph (via object+0x7c) and the current animation element
 * (object+0x80, stride 0xb4 in antr+0x74):
 *   - walking and on the animation's first frame (object+0x82 == 0): fires two
 *     collision-user events (param_2 = 3, indices 0 then 1).
 *   - fast and the current frame matches one of the element's two footstep
 *     marker frames (element+0x40 / element+0x41): fires one event with
 *     index = which marker matched (0 = +0x40, 1 = +0x41) and param_2 = whether
 *     the biped is crouched (object+0x257 == 2).
 * Then runs the slip/recovery counter at object+0x45b based on object+0x42a:
 *   - 0x42a == 0: increment the counter; once it reaches 4 fire two events
 *     (param_2 = 3, indices 0,1) and reset the counter to 0.
 *   - 0x42a == 1: latch the counter to 1 and return.
 *   - otherwise:  reset the counter to 0.
 *
 * unit_handle arrives in EDI (register parameter); no stack arguments.
 *
 * Confirmed: object_get_and_verify_type(unit_handle, 1); tag_get('bipd',...)
 * and tag_get('antr', object+0x7c); tag_block_get_element(antr+0x74, idx,
 * 0xb4); jump table at 0x1a25c0 (states 2..7); velocity sum-of-squares vs
 * 0x25337c; FUN_001a0f10(unit, param_2, idx) idx routed to BX.
 */
void FUN_001a2440(int unit_handle /* @edi */)
{
  unsigned int *object;
  char *anim_elem;
  char is_walking;
  char is_fast;
  char matched_second;
  char counter;

  object = (unsigned int *)object_get_and_verify_type(unit_handle, 1);
  tag_get(0x62697064, (int)object[0]); /* 'bipd' */

  is_walking = 0;
  is_fast = 0;
  switch (*(char *)((int)object + 0x253)) {
  case 2:
  case 3:
    is_walking = 1;
    break;
  case 4:
  case 5:
  case 6:
  case 7:
    if (*(float *)(object + 0x8a) * *(float *)(object + 0x8a) +
          *(float *)(object + 0x8b) * *(float *)(object + 0x8b) +
          *(float *)(object + 0x8c) * *(float *)(object + 0x8c) >
        *(float *)0x25337c) {
      is_fast = 1;
    }
    break;
  default:
    break;
  }

  if (*(short *)((int)object + 0x80) != -1) {
    anim_elem = (char *)tag_get(0x616e7472, (int)object[0x1f]); /* 'antr' */
    anim_elem = (char *)tag_block_get_element(
      anim_elem + 0x74, (int)*(short *)((int)object + 0x80), 0xb4);
    if (is_walking) {
      if (*(short *)((int)object + 0x82) == 0) {
        FUN_001a0f10(unit_handle, 3, 0);
        FUN_001a0f10(unit_handle, 3, 1);
      }
    } else if (is_fast && ((anim_elem[0x40] != 0) || (anim_elem[0x41] != 0)) &&
               ((*(short *)((int)object + 0x82) ==
                 (unsigned char)anim_elem[0x40]) ||
                (*(short *)((int)object + 0x82) ==
                 (unsigned char)anim_elem[0x41]))) {
      matched_second =
        (*(short *)((int)object + 0x82) != (unsigned char)anim_elem[0x40]);
      FUN_001a0f10(unit_handle, (*(char *)((int)object + 0x257) == 2),
                   matched_second);
    }
  }

  switch (*(char *)((int)object + 0x42a)) {
  case 0:
    if (*(char *)((int)object + 0x45b) < 1) {
      return;
    }
    counter = (char)(*(char *)((int)object + 0x45b) + 1);
    *(char *)((int)object + 0x45b) = counter;
    if (counter < 4) {
      return;
    }
    FUN_001a0f10(unit_handle, 3, 0);
    FUN_001a0f10(unit_handle, 3, 1);
    break;
  case 1:
    *(char *)((int)object + 0x45b) = 1;
    return;
  }
  *(char *)((int)object + 0x45b) = 0;
}

/* FUN_001a25e0 (0x1a25e0) — XBE naked draft (batch 54). */
#if defined(__clang__)
static void (*const b1a25e0_chkstk)(void) = FUN_001d90e0;
static void *(*const b1a25e0_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a25e0_gbsp)(void) = global_collision_bsp_get;
static void (*const b1a25e0_c1a0890)(int unit_handle, vector3_t *out_pos, float *out_height_offset, float *out_camera_height) = biped_get_camera_height_and_offset;
static void (*const b1a25e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1a25e0_exitfn)(int) = system_exit;
static char * (*const b1a25e0_c1459e0)(void) = breakable_surfaces_get_bsp_surface_data;
static int (*const b1a25e0_c1493b0)(int bsp, short flags, int breakable_surfaces, int origin, float radius, int *results) = collision_bsp_test_sphere;
static void *(*const b1a25e0_elem)(void *, int, int) = tag_block_get_element;

__attribute__((naked, noinline))
void FUN_001a25e0(int unit_handle /* @ecx */ __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x1054, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "call *%[gbsp]\n\t"
      "movl %%eax, %%esi\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x44(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a0890]\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "jl .LFUN_001a25e0_1\n\t"
      "pushl $1\n\t"
      "pushl $0xf71\n\t"
      "pushl $0x2b4d5c\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a25e0_1:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fadds 0x2533e8\n\t"
      "movswl %%ax, %%ecx\n\t"
      "leal -0x1054(%%ebp), %%edx\n\t"
      "incw %%ax\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "leal -0x44(%%ebp), %%eax\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "movw $7, 0x5a8c80(,%%ecx,2)\n\t"
      "call *%[c1459e0]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x100\n\t"
      "pushl %%esi\n\t"
      "call *%[c1493b0]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a25e0_8\n\t"
      "movl -0x1054(%%ebp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "movl $0xffffffff, -0x4(%%ebp)\n\t"
      "movl $0x7f7fffff, -0x20(%%ebp)\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "jle .LFUN_001a25e0_8\n\t"
      "leal 0x3c(%%esi), %%ecx\n\t"
      "addl $0xc, %%esi\n\t"
      "pushl %%ebx\n\t"
      "movl -0x38(%%ebp), %%ebx\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      "movl %%esi, -0x18(%%ebp)\n\t"
      ".LFUN_001a25e0_2:\n\t"
      "movl -0x1050(%%ebp,%%eax,4), %%edx\n\t"
      "leal -0x1050(%%ebp,%%eax,4), %%edi\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "pushl $0xc\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl (%%eax), %%esi\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "pushl $0x10\n\t"
      "andl $0x7fffffff, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jns .LFUN_001a25e0_3\n\t"
      "flds (%%eax)\n\t"
      "fchs\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fchs\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fchs\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0xc(%%eax)\n\t"
      "fchs\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "jmp .LFUN_001a25e0_4\n\t"
      ".LFUN_001a25e0_3:\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      ".LFUN_001a25e0_4:\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x44(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fsubs -0x8(%%ebp)\n\t"
      "fcoms -0x20(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a25e0_5\n\t"
      "movl (%%edi), %%eax\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x14(%%ebp), %%ebx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "jmp .LFUN_001a25e0_6\n\t"
      ".LFUN_001a25e0_5:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_001a25e0_6:\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl -0x1054(%%ebp), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_001a25e0_2\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_001a25e0_7\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "movl -0x2c(%%ebp), %%edi\n\t"
      "movl %%ecx, 0x430(%%eax)\n\t"
      "leal 0x46c(%%eax), %%ecx\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl -0x34(%%ebp), %%ecx\n\t"
      "movl %%ebx, (%%esi)\n\t"
      "addl $0x30, %%eax\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      "movl %%ebx, (%%eax)\n\t"
      "movl %%edx, 0x8(%%esi)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl %%edi, 0xc(%%esi)\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      ".LFUN_001a25e0_7:\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001a25e0_8:\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "jg .LFUN_001a25e0_9\n\t"
      "pushl $1\n\t"
      "pushl $0xf94\n\t"
      "pushl $0x2b4d5c\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a25e0_9:\n\t"
      "decw 0x4761d8\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [chkstk] "m"(b1a25e0_chkstk), [get] "m"(b1a25e0_get), [gbsp] "m"(b1a25e0_gbsp), [c1a0890] "m"(b1a25e0_c1a0890), [assert] "m"(b1a25e0_assert), [exitfn] "m"(b1a25e0_exitfn), [c1459e0] "m"(b1a25e0_c1459e0), [c1493b0] "m"(b1a25e0_c1493b0), [elem] "m"(b1a25e0_elem)
      : "memory");
}
#else
#error "FUN_001a25e0: clang naked draft required"
#endif


/* FUN_001a2800 (0x1a2800)
 *
 * Biped vector-failure assert: validates that the biped's forward axis
 * (unit+0x24) and up axis (unit+0x30) are perpendicular unit vectors
 * (valid_real_normal3d_perpendicular). If not, formats a diagnostic naming the
 * biped tag, its physics mode (flying / player-physics / climb / normal from
 * tag flags at +0x2f4), its dead/limping state, the supplied failure-kind
 * string, and the two offending vectors, then asserts and exits.
 *
 * Confirmed: @eax = unit_handle (caller MOV EAX,[EBP+8] then PUSH str; ADD
 * ESP,4); perpendicular check on (unit+0x24, unit+0x30); six floats
 * unit+0x24..+0x38 promoted to double for csprintf; dead bit =
 * byte[unit+0xb6]&4, limp bit = byte[unit+0x424]&0x20; tag flags at tag+0x2f4
 * (&4 flying, &2 player-physics, &0x40 climb); display_assert at
 * bipeds.c:0x55d. Inferred: "vector failure" / mode-string semantics from the
 * format string.
 */
void FUN_001a2800(int unit_handle /* @eax */, const char *failure_kind)
{
  char *unit_obj;
  char *biped_tag;
  const char *limp_str;
  const char *dead_str;
  const char *mode_str;
  uint32_t flags;

  unit_obj = (char *)object_get_and_verify_type(unit_handle, 1);
  if (valid_real_normal3d_perpendicular((float *)(unit_obj + 0x24),
                                        (float *)(unit_obj + 0x30)) == 0) {
    biped_tag = (char *)tag_get(0x62697064, *(int *)unit_obj);

    limp_str = "/limping";
    if ((*(unsigned char *)(unit_obj + 0x424) & 0x20) == 0) {
      limp_str = "";
    }
    dead_str = "/dead";
    if ((*(unsigned char *)(unit_obj + 0xb6) & 4) == 0) {
      dead_str = "";
    }
    flags = *(uint32_t *)(biped_tag + 0x2f4);
    if ((flags & 4) != 0) {
      mode_str = "flying";
    } else if ((flags & 2) != 0) {
      mode_str = "player-physics";
    } else if ((flags & 0x40) != 0) {
      mode_str = "climb";
    } else {
      mode_str = "normal";
    }

    csprintf(
      (char *)0x5ab100,
      "biped %s (%s%s%s): %s vector failure: (%f, %f, %f) / (%f, %f, %f)",
      tag_name_strip_path(tag_get_name(*(int *)unit_obj)), mode_str, dead_str,
      limp_str, failure_kind, (double)*(float *)(unit_obj + 0x24),
      (double)*(float *)(unit_obj + 0x28), (double)*(float *)(unit_obj + 0x2c),
      (double)*(float *)(unit_obj + 0x30), (double)*(float *)(unit_obj + 0x34),
      (double)*(float *)(unit_obj + 0x38));
    display_assert((const char *)0x5ab100, "c:\\halo\\SOURCE\\units\\bipeds.c",
                   0x55d, true);
    system_exit(-1);
  }
}

/* FUN_001a2900 (0x1a2900) — post-airborne update step
 *
 * Step in the biped update dispatcher (FUN_001a6350), reached when the biped
 * is airborne (object+0x424 bit 0). When the biped is flying through the air
 * (biped_flying_through_air) and the tag allows airborne aiming control
 * (tag+0x2f4 bit 8 / 0x100), and the movement state (object+0x253) is neither
 * 0x1f nor 0x29, perturbs the biped's aim/facing:
 *   - Picks a small random pitch in [3deg, 5deg] (random_real_range).
 *   - If the biped's airborne timer (object+0x38) is below threshold 0x2533f0,
 *     OR the horizontal facing (cross of object+0x30 with world up 0x31fc44)
 *     is degenerate (length <= 0x2533c0), uses a fully random yaw in [0, 2pi)
 *     to build the facing axis; otherwise uses the computed horizontal facing.
 *   - Scales the facing by the random pitch and adds it into object+0x3c
 *     (vector3d_scale_add), then runs the airborne aim helper FUN_001a2160.
 * Asserts the biped is airborne (object+0x424 bit 0). Writes the airborne
 * landing-prep state into *state (0x28 for states 0x27/0x28, 0x14 for state
 * 0x14 or when aiming control was active) and emits the "post-airborne" marker.
 *
 * unit_handle and state are both cdecl stack arguments (caller pushes
 * &update_state then unit_handle).
 *
 * Confirmed: object_get_and_verify_type(unit_handle, 1); tag_get('bipd',...);
 * biped_flying_through_air (0x1a0db0); random_real_range over global seed
 * (0x10b0d0) with min/max 0x3d567750/0x3db2b8c2; cross_product3d(object+0x30,
 * world_up, tmp); normalize3d (0x13010); FUN_000121e0(0, 2pi) random yaw;
 * vector3d_from_angle (0x10cc70); vector3d_scale_add (0x12f80) into
 * object+0x3c.
 */
void FUN_001a2900(int unit_handle, char *state)
{
  unsigned int *object;
  int biped_tag;
  char aim_control;
  char move_state;
  float pitch;
  float facing[3];

  object = (unsigned int *)object_get_and_verify_type(unit_handle, 1);
  biped_tag = (int)tag_get(0x62697064, (int)object[0]); /* 'bipd' */

  aim_control = 0;
  if ((biped_flying_through_air(unit_handle) != 0) &&
      (aim_control = 1, (*(unsigned int *)(biped_tag + 0x2f4) & 0x100) != 0)) {
    move_state = *(char *)((int)object + 0x253);
    if ((move_state != 0x1f) && (move_state != 0x29)) {
      pitch = random_real_range(get_global_random_seed_address(), 0.05235988f,
                                0.08726646f);
      if (*(float *)(object + 0xe) /* +0x38 */ >= *(float *)0x2533f0) {
        cross_product3d((float *)(object + 0xc) /* +0x30 */,
                        *(float **)0x31fc44 /* world up */, facing);
        if (normalize3d(facing) > *(float *)0x2533c0) {
          goto have_facing;
        }
      }
      vector3d_from_angle(facing, FUN_000121e0(0.0f, 6.2831855f));
    have_facing:
      vector3d_scale_add((float *)(object + 0xf) /* +0x3c */, facing, pitch,
                         (float *)(object + 0xf));
    }
    FUN_001a2160(unit_handle);
  }

  if ((*(unsigned char *)(object + 0x109) /* +0x424 */ & 1) == 0) {
    display_assert("TEST_FLAG(biped->biped.flags, _biped_airborne_bit)",
                   "c:\\halo\\SOURCE\\units\\bipeds.c", 0xa61, true);
    system_exit(-1);
  }

  move_state = *(char *)((int)object + 0x253);
  if ((move_state == 0x27) || (move_state == 0x28)) {
    *state = 0x28;
  } else if ((move_state == 0x14) || (aim_control)) {
    *state = 0x14;
  }

  FUN_001a2800(unit_handle, "post-airborne");
}

/* FUN_001a2a60 (0x1a2a60) — post-landing update step
 *
 * Step in the biped update dispatcher (FUN_001a6350), reached when the biped
 * has a landing-animation index (object+0x460 != NONE). Increments the
 * landing-frame counter (object+0x428); once it reaches the landing frame
 * count (object+0x429) the landing animation index (object+0x460) is cleared
 * to NONE (0xffff). When no cinematic is running and the landing has just
 * begun (counter == 2) or is effectively a one-frame landing (index already
 * cleared and frame count < 2), fires two collision-user events via
 * FUN_001a0f10 with selector indices 0 then 1 (param_2 = 5). Writes the
 * resulting landing-sound id into *state (0x16 if index == 1, else 0x15) and
 * emits the "post-landing" timing marker via FUN_001a2800.
 *
 * unit_handle arrives in EDI (register parameter); state is the only stack
 * argument (caller pushes &update_state byte).
 *
 * Confirmed: object_get_and_verify_type(unit_handle, 1); tag_get('bipd',...);
 * cinematic_in_progress (0x930a0); FUN_001a0f10(unit, 5, idx) idx->BX (0,1).
 */
void FUN_001a2a60(int unit_handle /* @edi */, char *state)
{
  unsigned char *object;
  char counter;

  object = (unsigned char *)object_get_and_verify_type(unit_handle, 1);
  tag_get(0x62697064, *(int *)object); /* 'bipd' */

  counter = (char)(object[0x428] + 1);
  object[0x428] = (unsigned char)counter;
  if (counter >= (char)object[0x429]) {
    *(short *)(object + 0x460) = -1;
  }

  if ((cinematic_in_progress() == 0) &&
      (((char)object[0x428] == 2) ||
       ((*(short *)(object + 0x460) == -1) && ((char)object[0x429] < 2)))) {
    FUN_001a0f10(unit_handle, 5, 0);
    FUN_001a0f10(unit_handle, 5, 1);
  }

  *state = (char)((*(short *)(object + 0x460) == 1) + 0x15);
  FUN_001a2800(unit_handle, "post-landing");
}

/* FUN_001a2b10 (0x1a2b10) — post-slipping update step
 *
 * Step in the biped update dispatcher (FUN_001a6350). If the biped's slipping
 * counter (object+0x45a) has exceeded 3 ticks AND the object's linear velocity
 * magnitude squared (object+0x18..0x20) exceeds the "moving" threshold at
 * 0x25620c (== 1/900), fires two collision-user events via FUN_001a0f10 with
 * selector indices 0 then 1 (param_2 = 2). Always emits the "post-slipping"
 * timing marker via FUN_001a2800.
 *
 * unit_handle arrives in EDI (register parameter). The caller (FUN_001a6350)
 * also pushes a pointer to its update-state byte buffer, but this function
 * never reads it; it is not declared as a parameter because the original is
 * frameless (no EBP frame, no stack-arg load) — the caller's cdecl push and
 * matching ESP cleanup are unaffected.
 *
 * Confirmed: object_get_and_verify_type(unit_handle, 1); tag_get('bipd',...);
 * velocity sum-of-squares at +0x18/+0x1c/+0x20 vs threshold 0x25620c;
 * FUN_001a0f10(unit, 2, idx) with idx routed to BX (0 then 1).
 */
void FUN_001a2b10(int unit_handle /* @edi */)
{
  unsigned int *object;
  float *velocity;

  object = (unsigned int *)object_get_and_verify_type(unit_handle, 1);
  tag_get(0x62697064, (int)object[0]); /* 'bipd' */

  velocity = (float *)(object + 6); /* +0x18: linear velocity vec3 */
  if ((*(char *)((int)object + 0x45a) > 3) &&
      (velocity[2] * velocity[2] + velocity[1] * velocity[1] +
         velocity[0] * velocity[0] >
       *(float *)0x25620c)) {
    FUN_001a0f10(unit_handle, 2, 0);
    FUN_001a0f10(unit_handle, 2, 1);
  }

  FUN_001a2800(unit_handle, "post-slipping");
}

/* FUN_001a2b90 (0x1a2b90) — airborne aim / landing-rumble update step
 *
 * Step in the biped update dispatcher (FUN_001a5300). When the biped is not
 * yet airborne (object+0x424 bit 0 clear) and its landing index (object+0x460)
 * isn't 1, advances the airborne-frame counter (object+0x45c, capped at 0x7f);
 * if the biped has the relevant control flag (object+0x1b8 bit 1) and the
 * counter exceeds 5, runs FUN_001a2290.
 *
 * If a controlling unit (player) is bound (global 0x5aa891 set, object+0x1c8 is
 * a valid datum) it fetches the player record (datum_get) and, depending on
 * object+0x1b8 flags:
 *   - bits 0x800 AND 0x2000 set: re-orients the biped's aim vector
 *     (object+0x18). Computes the dot of the aim (object+0x18) with the desired
 *     aim (object+0x1ec); when that dot is below epsilon (0x2533c0) it derives
 *     an angle via FUN_00013070, otherwise uses epsilon. A blend weight is
 *     formed (0x2b4fbc * angle) and saturated to [0,1]. The aim is rotated
 *     toward the desired aim via three vector3d_scale_add steps and the
 *     airborne flag (object+0x424 bit 0) is set.
 *   - only bit 1 (and already airborne): damps the aim vector by -0.2
 *     (FUN_00012fb0).
 * Finally, if the aim was re-oriented this tick and the player has a valid
 * controller index (player+2), triggers a landing rumble (rumble_player_impulse
 * with a 0x3c-byte rumble definition: scale 1.0, 0.3, type 3).
 *
 * unit_handle arrives in EAX (register parameter). The caller also pushes its
 * update-state pointer, but this function never reads it.
 *
 * Confirmed: object_get_and_verify_type(unit_handle, 1); tag_get('bipd',...);
 * FUN_001a2290 (@edi=unit_handle); datum_get(0x5aa6d4, object+0x1c8);
 * FUN_00013070 dot/angle of object+0x18 and object+0x1ec; vector3d_scale_add
 * (0x12f80) x3; FUN_00012fb0 damp; csmemset+rumble_player_impulse (0xb9bc0).
 */
void FUN_001a2b90(int unit_handle /* @eax */)
{
  unsigned int *object;
  int player;
  unsigned int flags;
  char aim_reoriented;
  float angle;
  float weight;
  float scale;
  float tmp[3];
  float rumble_def[15]; /* 0x3c bytes */

  object = (unsigned int *)object_get_and_verify_type(unit_handle, 1);
  tag_get(0x62697064, (int)object[0]); /* 'bipd' */

  if (((*(unsigned char *)((int)object + 0x424) & 1) == 0) &&
      (*(short *)((int)object + 0x460) != 1)) {
    if (*(char *)((int)object + 0x45c) < 0x7f) {
      *(char *)((int)object + 0x45c) =
        (char)(*(char *)((int)object + 0x45c) + 1);
    }
    if (((*(unsigned char *)((int)object + 0x1b8) & 2) != 0) &&
        (*(char *)((int)object + 0x45c) > 5)) {
      FUN_001a2290(unit_handle);
    }
  }

  if ((*(char *)0x5aa891 != 0) && ((int)object[0x72] != -1)) {
    player = (int)datum_get(*(void **)0x5aa6d4, (int)object[0x72]);
    flags = object[0x6e]; /* +0x1b8 */
    aim_reoriented = 0;
    if (((flags & 0x800) == 0) || ((flags & 0x2000) == 0)) {
      if (((flags & 1) != 0) &&
          ((*(unsigned char *)((int)object + 0x424) & 1) != 0)) {
        FUN_00012fb0((float *)(object + 6), -0.2f, (float *)(object + 6));
      }
    } else {
      /* Dot of aim (object+0x18) with desired aim (object+0x1ec); z,y,x order
       * matches the original FLD sequence. The FLD/FMUL operand assignment for
       * each commutative product is an MSVC scheduling choice (a*b == b*a, so
       * bit-identical); vc71 flags it as an FPU operand-order diff but the
       * value is provably the same. */
      if (*(float *)(object + 8) * *(float *)(object + 0x7d) +
            *(float *)(object + 7) * *(float *)(object + 0x7c) +
            *(float *)(object + 6) * *(float *)(object + 0x7b) <
          *(float *)0x2533c0) {
        angle = FUN_00013070((float *)(object + 6), (float *)(object + 0x7b));
      } else {
        angle = *(float *)0x2533c0;
      }
      weight = *(float *)0x2b4fbc * angle;
      if (weight < *(float *)0x2533c0) {
        scale = 0.0f; /* clamp below epsilon -> 0 */
      } else if (weight > *(float *)0x2533c8) {
        scale = 1.0f; /* clamp above 1.0 -> 1.0 */
      } else {
        scale = weight;
      }
      vector3d_scale_add((float *)(object + 6), (float *)(object + 0x7b),
                         -angle, tmp);
      vector3d_scale_add((float *)(object + 6), tmp, -0.2f,
                         (float *)(object + 6));
      vector3d_scale_add((float *)(object + 6), (float *)(object + 0x7b),
                         scale * *(float *)0x25bb0c -
                           scale * scale * *(float *)0x2533e8 +
                           *(float *)0x25bb10,
                         (float *)(object + 6));
      object[0x109] |= 1; /* +0x424 bit 0 */
      aim_reoriented = 1;
    }
    if ((*(short *)(player + 2) != -1) && (aim_reoriented)) {
      csmemset(rumble_def, 0, 0x3c);
      *(unsigned int *)&rumble_def[0] = 0x3f800000; /* 1.0 */
      *(unsigned int *)&rumble_def[1] = 0x3e99999a; /* 0.3 */
      *(short *)&rumble_def[2] = 3;
      rumble_player_impulse(*(short *)(player + 2), rumble_def, 1.0f, 1.0f);
    }
  }
}

/* biped_build_flying_axes (0x1a2d90)
 *
 * Builds an orthonormal forward/left/up basis for a flying biped from a given
 * forward vector. Sets up = world up, left = up x forward (renormalized; if
 * degenerate, retries with up = world forward), then up = forward x left
 * (renormalized). Asserts the result is a valid axis triple.
 *
 * Confirmed: normalize3d (0x13010); global up = 0x31fc44, forward = 0x31fc3c;
 * valid_real_vector3d_axes3 (0xf6c40); cross operand order from disassembly.
 * Asserts at bipeds.c:0xb93 (null args) and :0xba2 (invalid axes).
 */
void biped_build_flying_axes(float *forward, float *left, float *up)
{
  float lc0;
  float lc1;
  float lc2;

  if (forward == NULL || left == NULL || up == NULL) {
    display_assert("forward_vector && left_vector && up_vector",
                   "c:\\halo\\SOURCE\\units\\bipeds.c", 0xb93, true);
    system_exit(-1);
  }

  up[0] = global_up_vector_ptr[0];
  up[1] = global_up_vector_ptr[1];
  up[2] = global_up_vector_ptr[2];

  /* left = up x forward (batched: all components before any store) */
  lc2 = forward[1] * up[0] - up[1] * forward[0];
  lc1 = up[2] * forward[0] - forward[2] * up[0];
  lc0 = up[1] * forward[2] - up[2] * forward[1];
  left[0] = lc0;
  left[1] = lc1;
  left[2] = lc2;
  if (normalize3d(left) == 0.0f) {
    up[0] = global_forward_vector_ptr[0];
    up[1] = global_forward_vector_ptr[1];
    up[2] = global_forward_vector_ptr[2];
    lc2 = forward[1] * up[0] - up[1] * forward[0];
    lc1 = up[2] * forward[0] - forward[2] * up[0];
    lc0 = up[1] * forward[2] - up[2] * forward[1];
    left[0] = lc0;
    left[1] = lc1;
    left[2] = lc2;
    normalize3d(left);
  }

  /* up = forward x left */
  lc2 = left[1] * forward[0] - forward[1] * left[0];
  lc1 = forward[2] * left[0] - forward[0] * left[2];
  lc0 = forward[1] * left[2] - left[1] * forward[2];
  up[0] = lc0;
  up[1] = lc1;
  up[2] = lc2;
  normalize3d(up);

  if (valid_real_vector3d_axes3(forward, left, up) == 0) {
    display_assert(
      csprintf(error_string_buffer,
               "%s, %s, %s: assert_valid_real_vector3d_axes3(%f, %f, %f / %f, "
               "%f, %f / %f, %f, %f)",
               "forward_vector", "left_vector", "up_vector", (double)forward[0],
               (double)forward[1], (double)forward[2], (double)up[0],
               (double)up[1], (double)up[2], (double)left[0], (double)left[1],
               (double)left[2]),
      "c:\\halo\\SOURCE\\units\\bipeds.c", 0xba2, true);
    system_exit(-1);
  }
}

/* Collision/line-of-sight query result entry (0x2c bytes), as filled by
 * FUN_00150550 into a 16-element local array. Offsets confirmed from the
 * back-half access patterns (EDI walks the array at stride 0x2c):
 *   +0x00 point[3] (also used as plane normal source)
 *   +0x04 normal.y (EDI+0x4, used in the ground-plane height test)
 *   +0x0c object datum handle (EDI+0xc, compared to -1, fed to datum_get)
 *   +0x14 flags byte (EDI+0x14, tested &8 / &4) and +0x28 plane reference.
 * The decompiler models the array as scattered local_358/local_35c/local_36c
 * char* locals at stride 0xb; this struct preserves the same 0x2c layout. */
typedef struct biped_collision_result {
  float point[4]; /* +0x00 .. +0x0c */
  float normal[3]; /* +0x10 .. +0x18 */
  float plane_d; /* +0x1c */
  int object_handle; /* +0x20 */
  int surface_handle; /* +0x24 */
  int flags; /* +0x28 */
} biped_collision_result;

/* FUN_001a2f40 (0x1a2f40) — XBE naked draft (batch 50). */
#if defined(__clang__)
static void (*const b1a2f40_chkstk)(void) = FUN_001d90e0;
static bool (*const b1a2f40_ca16b0)(float *point) = valid_real_point3d;
static char * (*const b1a2f40_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b1a2f40_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1a2f40_exitfn)(int) = system_exit;
static int (*const b1a2f40_c84a10)(float *vector) = real_vector3d_valid;
static void (*const b1a2f40_c1a2d90)(float *forward, float *left, float *up) = biped_build_flying_axes;
static float (*const b1a2f40_norm)(float *) = normalize3d;
static float (*const b1a2f40_mag)(float *) = magnitude3d;
static void (*const b1a2f40_cross)(float *, float *, float *) = cross_product3d;
static float *(*const b1a2f40_vsca)(float *, float *, float, float *) = vector3d_scale_add;
static int (*const b1a2f40_c150550)(void *out_point, float *direction, float *origin, int arg4, int arg5, int arg6, float *out_point2, void *out_arg8, int max_results, void *results) = FUN_00150550;
static void *(*const b1a2f40_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a2f40_gbsp)(void) = global_collision_bsp_get;
static void *(*const b1a2f40_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1a2f40_c99640)(int structure_bsp, uint32_t plane_reference, float *out_plane) = bsp3d_get_plane_from_designator;
static float (*const b1a2f40_c121a0)(const float *a, const float *b) = distance_squared3d;
static void *(*const b1a2f40_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static float (*const b1a2f40_c12170)(float *vector) = FUN_00012170;
static float (*const b1a2f40_v2fe0)(float *) = FUN_00012fe0;
static void *(*const b1a2f40_tryget)(int, int) = object_try_and_get_and_verify_type;
static void *(*const b1a2f40_tag)(int, int) = tag_get;
static bool (*const b1a2f40_c4ec30)(int, float *, float, float, float, int, void *) = FUN_0014ec30;
static char (*const b1a2f40_c14c4b0)(void *features, float *position, float *velocity, void *out_result) = FUN_0014c4b0;

__attribute__((naked, noinline))
void FUN_001a2f40(void *physics __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0xafac, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "pushl %%edi\n\t"
      "leal 0x8(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "movl $0, -0x58(%%ebp)\n\t"
      "movl $0, -0x5c(%%ebp)\n\t"
      "shrl $9, %%eax\n\t"
      "andb $1, %%al\n\t"
      "movb %%al, -0x31(%%ebp)\n\t"
      "call *%[ca16b0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a2f40_1\n\t"
      "flds 0x10(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0xbae\n\t"
      "pushl $0x2b4d5c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b50b4\n\t"
      "pushl $0x26ae04\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a2f40_1:\n\t"
      "pushl %%ebx\n\t"
      "leal 0x2c(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a2f40_2\n\t"
      "flds 0x34(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0xbaf\n\t"
      "pushl $0x2b4d5c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x30(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b50a0\n\t"
      "pushl $0x26ae40\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a2f40_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "testb $0x10, %%al\n\t"
      "movw $0, 0xa0(%%esi)\n\t"
      "movl %%eax, -0x48(%%ebp)\n\t"
      "je .LFUN_001a2f40_5\n\t"
      "leal -0x54(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x6c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x14(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a2d90]\n\t"
      "flds -0x6c(%%ebp)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      "leal -0x54(%%ebp), %%ecx\n\t"
      "flds -0x54(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x44(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "flds 0x3c(%%esi)\n\t"
      "fmuls (%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "flds 0x18(%%esi)\n\t"
      "fmuls 0x3c(%%esi)\n\t"
      "flds -0x68(%%ebp)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fmuls 0x44(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fmuls 0x3c(%%esi)\n\t"
      "flds -0x64(%%ebp)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "fmuls 0x44(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fstps -0x64(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x48(%%esi)\n\t"
      "fsts -0x60(%%ebp)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fstps -0x6c(%%ebp)\n\t"
      "flds -0x60(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstp %%st(2)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x60(%%ebp)\n\t"
      "fmuls -0x64(%%ebp)\n\t"
      "flds -0x6c(%%ebp)\n\t"
      "fsubs (%%ebx)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "movl -0x30(%%ebp), %%edi\n\t"
      "fxch %%st(1)\n\t"
      "movl %%edi, -0x54(%%ebp)\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "movl -0x2c(%%ebp), %%edx\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x4c(%%esi)\n\t"
      "addl $0x10, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a2f40_3\n\t"
      "flds 0x4c(%%esi)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "fmuls -0x4c(%%ebp)\n\t"
      "jmp .LFUN_001a2f40_4\n\t"
      ".LFUN_001a2f40_3:\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movl -0x2c(%%ebp), %%edx\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "movl %%edi, -0x24(%%ebp)\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      ".LFUN_001a2f40_4:\n\t"
      "flds -0x24(%%ebp)\n\t"
      "leal 0xb8(%%esi), %%eax\n\t"
      "fadds (%%ebx)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "fstps (%%eax)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fadds 0x4(%%ebx)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "fadds 0x8(%%ebx)\n\t"
      "fstps 0x8(%%eax)\n\t"
      "movw 0xa0(%%esi), %%cx\n\t"
      "andl $0xfffd, %%ecx\n\t"
      "orl $1, %%ecx\n\t"
      "movw %%cx, 0xa0(%%esi)\n\t"
      "jmp .LFUN_001a2f40_26\n\t"
      ".LFUN_001a2f40_5:\n\t"
      "testb $0x20, %%al\n\t"
      "je .LFUN_001a2f40_6\n\t"
      "flds 0x3c(%%esi)\n\t"
      "movl 0x44(%%esi), %%edx\n\t"
      "fmuls 0x14(%%esi)\n\t"
      "leal 0xb8(%%esi), %%eax\n\t"
      "flds 0x18(%%esi)\n\t"
      "movl %%edx, 0xc0(%%esi)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fsts (%%eax)\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "flds 0x40(%%esi)\n\t"
      "fmuls 0x14(%%esi)\n\t"
      "flds 0x3c(%%esi)\n\t"
      "fmuls 0x18(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fsts 0xbc(%%esi)\n\t"
      "fstps -0x5c(%%ebp)\n\t"
      "jmp .LFUN_001a2f40_26\n\t"
      ".LFUN_001a2f40_6:\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_001a2f40_9\n\t"
      "flds 0x3c(%%esi)\n\t"
      "leal -0x44(%%ebp), %%ecx\n\t"
      "fmuls 0x14(%%esi)\n\t"
      "pushl %%ecx\n\t"
      "flds 0x18(%%esi)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x40(%%esi)\n\t"
      "fmuls 0x14(%%esi)\n\t"
      "flds 0x3c(%%esi)\n\t"
      "fmuls 0x18(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x48(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstp %%st(2)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fsubs (%%ebx)\n\t"
      "fstps -0xb0(%%ebp)\n\t"
      "movl -0xb0(%%ebp), %%edi\n\t"
      "movl %%edi, -0x44(%%ebp)\n\t"
      "fsubs 0x30(%%esi)\n\t"
      "fstps -0xac(%%ebp)\n\t"
      "movl -0xac(%%ebp), %%eax\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x50(%%esi)\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a2f40_7\n\t"
      "flds 0x50(%%esi)\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0xb8(%%ebp)\n\t"
      "fmuls -0x40(%%ebp)\n\t"
      "jmp .LFUN_001a2f40_8\n\t"
      ".LFUN_001a2f40_7:\n\t"
      "movl -0xac(%%ebp), %%edx\n\t"
      "movl %%edx, -0xb4(%%ebp)\n\t"
      "flds -0xb4(%%ebp)\n\t"
      "movl %%edi, -0xb8(%%ebp)\n\t"
      ".LFUN_001a2f40_8:\n\t"
      "flds -0xb8(%%ebp)\n\t"
      "movb -0x48(%%ebp), %%cl\n\t"
      "fadds (%%ebx)\n\t"
      "leal 0xb8(%%esi), %%eax\n\t"
      "andb $2, %%cl\n\t"
      "movzbw %%cl, %%cx\n\t"
      "fstps (%%eax)\n\t"
      "fadds 0x30(%%esi)\n\t"
      "fstps 0xbc(%%esi)\n\t"
      "flds 0x34(%%esi)\n\t"
      "fsubs 0x32512c\n\t"
      "movw %%cx, 0xa0(%%esi)\n\t"
      "jmp .LFUN_001a2f40_25\n\t"
      ".LFUN_001a2f40_9:\n\t"
      "flds 0x44(%%esi)\n\t"
      "andl $0x200, %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "flds 0x40(%%esi)\n\t"
      "flds 0x3c(%%esi)\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fsqrt\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "je .LFUN_001a2f40_11\n\t"
      "leal 0x20(%%esi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x80(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "call *%[cross]\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x10, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001a2f40_10\n\t"
      "movl 0x31fc44, %%ecx\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[cross]\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x10, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001a2f40_10\n\t"
      "movl 0x31fc3c, %%ecx\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[cross]\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_001a2f40_10:\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[cross]\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "fmuls 0x3c(%%esi)\n\t"
      "pushl %%eax\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x3c(%%esi)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x3c(%%esi)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fadds 0x44(%%esi)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_001a2f40_15\n\t"
      ".LFUN_001a2f40_11:\n\t"
      "flds 0x88(%%esi)\n\t"
      "fcomps 0x253f44\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a2f40_12\n\t"
      "flds 0x3c(%%esi)\n\t"
      "leal 0x80(%%esi), %%edi\n\t"
      "fmuls 0x14(%%esi)\n\t"
      "flds 0x18(%%esi)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "flds 0x40(%%esi)\n\t"
      "movl %%ecx, -0x58(%%ebp)\n\t"
      "fmuls 0x14(%%esi)\n\t"
      "flds 0x3c(%%esi)\n\t"
      "fmuls 0x18(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "flds -0x14(%%ebp)\n\t"
      "movl %%edx, -0x5c(%%ebp)\n\t"
      "fmuls 0x84(%%esi)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "fdivs 0x88(%%esi)\n\t"
      "fsubrs 0x44(%%esi)\n\t"
      "jmp .LFUN_001a2f40_13\n\t"
      ".LFUN_001a2f40_12:\n\t"
      "leal 0x20(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "call *%[cross]\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "leal 0x80(%%esi), %%edi\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "addl $0x10, %%esp\n\t"
      "flds -0x20(%%ebp)\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "fchs\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[vsca]\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "addl $0x10, %%esp\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "fchs\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[vsca]\n\t"
      "flds 0x3c(%%esi)\n\t"
      "fmuls 0x14(%%esi)\n\t"
      "addl $0x10, %%esp\n\t"
      "flds 0x18(%%esi)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "flds 0x40(%%esi)\n\t"
      "fmuls 0x14(%%esi)\n\t"
      "flds 0x3c(%%esi)\n\t"
      "fmuls 0x18(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fstps -0x5c(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x3c(%%esi)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x3c(%%esi)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "movb -0x31(%%ebp), %%al\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "testb %%al, %%al\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x3c(%%esi)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fadds 0x44(%%esi)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "jne .LFUN_001a2f40_14\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x254cc4\n\t"
      ".LFUN_001a2f40_13:\n\t"
      "fstps -0x10(%%ebp)\n\t"
      ".LFUN_001a2f40_14:\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001a2f40_15:\n\t"
      "cmpw $0, -0x38(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "jne .LFUN_001a2f40_19\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x6c(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_001a2f40_16\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls 0x70(%%esi)\n\t"
      "jmp .LFUN_001a2f40_20\n\t"
      ".LFUN_001a2f40_16:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x68(%%esi)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a2f40_17\n\t"
      "fsubs 0x68(%%esi)\n\t"
      "flds 0x70(%%esi)\n\t"
      "fsubs 0x2533c8\n\t"
      "fmulp %%st(1)\n\t"
      "flds 0x6c(%%esi)\n\t"
      "fsubs 0x68(%%esi)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fadds 0x2533c8\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      "jmp .LFUN_001a2f40_20\n\t"
      ".LFUN_001a2f40_17:\n\t"
      "fcomps 0x78(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001a2f40_18\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls 0x7c(%%esi)\n\t"
      "jmp .LFUN_001a2f40_20\n\t"
      ".LFUN_001a2f40_18:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x74(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a2f40_19\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fsubs 0x74(%%esi)\n\t"
      "flds 0x7c(%%esi)\n\t"
      "fsubs 0x2533c8\n\t"
      "fmulp %%st(1)\n\t"
      "flds 0x78(%%esi)\n\t"
      "fsubs 0x74(%%esi)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fadds 0x2533c8\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      "jmp .LFUN_001a2f40_20\n\t"
      ".LFUN_001a2f40_19:\n\t"
      "flds -0x3c(%%ebp)\n\t"
      ".LFUN_001a2f40_20:\n\t"
      "flds 0x2533c8\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "fsubs 0x48(%%esi)\n\t"
      "fmulp %%st(1)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fstps -0x68(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fstps -0x64(%%ebp)\n\t"
      "fsubs (%%ebx)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x54(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "leal -0x54(%%ebp), %%ecx\n\t"
      "flds -0x68(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fsubs 0x30(%%esi)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "flds -0x64(%%ebp)\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      "fsubs 0x34(%%esi)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x4c(%%esi)\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a2f40_23\n\t"
      "cmpw $0, -0x38(%%ebp)\n\t"
      "jne .LFUN_001a2f40_21\n\t"
      "movb -0x48(%%ebp), %%al\n\t"
      "shrb $1, %%al\n\t"
      "andb $1, %%al\n\t"
      "jmp .LFUN_001a2f40_22\n\t"
      ".LFUN_001a2f40_21:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      ".LFUN_001a2f40_22:\n\t"
      "flds 0x4c(%%esi)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "fmuls -0x4c(%%ebp)\n\t"
      "jmp .LFUN_001a2f40_24\n\t"
      ".LFUN_001a2f40_23:\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      ".LFUN_001a2f40_24:\n\t"
      "flds (%%edi)\n\t"
      "negb %%al\n\t"
      "fmuls 0x25f0d0\n\t"
      "fsubrs -0x30(%%ebp)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls 0x25f0d0\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $2, %%eax\n\t"
      "fsubrs -0x2c(%%ebp)\n\t"
      "flds 0x8(%%edi)\n\t"
      "movw %%ax, 0xa0(%%esi)\n\t"
      "fmuls 0x25f0d0\n\t"
      "leal 0xb8(%%esi), %%eax\n\t"
      "fsubr %%st(3), %%st(0)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fadds (%%ebx)\n\t"
      "fstps (%%eax)\n\t"
      "fadds 0x4(%%ebx)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fadds 0x8(%%ebx)\n\t"
      "fstps 0x8(%%eax)\n\t"
      "movb 0xa0(%%esi), %%cl\n\t"
      "testb $2, %%cl\n\t"
      "je .LFUN_001a2f40_26\n\t"
      "flds 0xc0(%%esi)\n\t"
      "fsubs 0x32512c\n\t"
      ".LFUN_001a2f40_25:\n\t"
      "fstps 0xc0(%%esi)\n\t"
      ".LFUN_001a2f40_26:\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "testb $0x40, %%cl\n\t"
      "je .LFUN_001a2f40_27\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "jmp .LFUN_001a2f40_29\n\t"
      ".LFUN_001a2f40_27:\n\t"
      "testb %%cl, %%cl\n\t"
      "jns .LFUN_001a2f40_28\n\t"
      "movl $0xc0a0, %%ecx\n\t"
      "jmp .LFUN_001a2f40_29\n\t"
      ".LFUN_001a2f40_28:\n\t"
      "andl $0x100, %%ecx\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl $0xffdfff00, %%ecx\n\t"
      "addl $0x20c3a0, %%ecx\n\t"
      ".LFUN_001a2f40_29:\n\t"
      "leal 0x8(%%esi), %%edx\n\t"
      "movl %%edx, %%edi\n\t"
      "movl (%%edi), %%ebx\n\t"
      "movl %%ebx, -0x30(%%ebp)\n\t"
      "movl 0x4(%%edi), %%ebx\n\t"
      "movl 0x8(%%edi), %%edi\n\t"
      "movl %%ebx, -0x2c(%%ebp)\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl %%edi, -0x28(%%ebp)\n\t"
      "movl 0x4(%%ebx), %%edi\n\t"
      "movl 0x8(%%ebx), %%ebx\n\t"
      "movl %%ebx, -0x90(%%ebp)\n\t"
      "flds -0x90(%%ebp)\n\t"
      "fadds 0x38(%%esi)\n\t"
      "movb 0x4e4cf2, %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "movl %%eax, -0x98(%%ebp)\n\t"
      "fstps -0x90(%%ebp)\n\t"
      "movl %%edi, -0x94(%%ebp)\n\t"
      "je .LFUN_001a2f40_30\n\t"
      "movl (%%edx), %%ecx\n\t"
      "flds -0x28(%%ebp)\n\t"
      "movl %%ecx, -0x374(%%ebp)\n\t"
      "fchs\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%ecx, -0x370(%%ebp)\n\t"
      "movl 0x31fc44, %%ecx\n\t"
      "movl %%edx, -0x36c(%%ebp)\n\t"
      "movl $0, -0x378(%%ebp)\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x368(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, -0x364(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "fstps -0x35c(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl %%eax, -0x78(%%ebp)\n\t"
      "fadds -0x78(%%ebp)\n\t"
      "movl -0x90(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x360(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "movl %%edi, -0x74(%%ebp)\n\t"
      "fadds -0x74(%%ebp)\n\t"
      "movl %%ecx, -0x354(%%ebp)\n\t"
      "movw %%cx, -0x34e(%%ebp)\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "movl $1, %%ebx\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "movl %%eax, -0x70(%%ebp)\n\t"
      "movl %%ebx, -0x3c(%%ebp)\n\t"
      "movl %%edx, -0x358(%%ebp)\n\t"
      "movb $0, -0x350(%%ebp)\n\t"
      "movb $0, -0x34f(%%ebp)\n\t"
      "movl $0, -0x70(%%ebp)\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "jmp .LFUN_001a2f40_31\n\t"
      ".LFUN_001a2f40_30:\n\t"
      "leal -0x378(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x10\n\t"
      "leal -0x78(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl (%%esi), %%eax\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x58(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x54(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x98(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c150550]\n\t"
      "addl $0x28, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl %%ebx, -0x3c(%%ebp)\n\t"
      ".LFUN_001a2f40_31:\n\t"
      "movb 0x4e4cf0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a2f40_32\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "movl 0x70(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_001a2f40_32\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x5a8d00\n\t"
      "movl -0x98(%%ebp), %%edx\n\t"
      "movl %%eax, 0x5a8d04\n\t"
      "movl -0x94(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x5a8d08\n\t"
      "movl -0x90(%%ebp), %%ecx\n\t"
      "movb $1, 0x5a8d1c\n\t"
      "movl %%edx, 0x5a8cf0\n\t"
      "movl %%eax, 0x5a8cf4\n\t"
      "movl %%ecx, 0x5a8cf8\n\t"
      "movl $0x3f800000, 0x324fc4\n\t"
      "movl 0x58(%%esi), %%edx\n\t"
      "movl %%edx, 0x4761b8\n\t"
      "movl 0x54(%%esi), %%eax\n\t"
      "movl %%eax, 0x4761bc\n\t"
      ".LFUN_001a2f40_32:\n\t"
      "cmpw $0x10, %%bx\n\t"
      "jl .LFUN_001a2f40_33\n\t"
      "orb $8, 0xa0(%%esi)\n\t"
      "jmp .LFUN_001a2f40_34\n\t"
      ".LFUN_001a2f40_33:\n\t"
      "andb $0xf7, 0xa0(%%esi)\n\t"
      ".LFUN_001a2f40_34:\n\t"
      "testw %%bx, %%bx\n\t"
      "movl $0xffffffff, 0xa8(%%esi)\n\t"
      "jne .LFUN_001a2f40_44\n\t"
      "cmpl $-1, 0x90(%%esi)\n\t"
      "je .LFUN_001a2f40_44\n\t"
      "call *%[gbsp]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x90(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%edi, -0x60(%%ebp)\n\t"
      "movl $0xffffffff, -0x38(%%ebp)\n\t"
      "movl $0x7f7fffff, -0x48(%%ebp)\n\t"
      "jl .LFUN_001a2f40_44\n\t"
      "movl 0x3c(%%edi), %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "leal 0x3c(%%edi), %%ecx\n\t"
      "jge .LFUN_001a2f40_44\n\t"
      "pushl $0xc\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl 0x4(%%eax), %%ebx\n\t"
      "leal -0x88(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0xac(%%ebp)\n\t"
      "call *%[c99640]\n\t"
      "flds -0x80(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "addl $0x18, %%esp\n\t"
      "flds -0x84(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls -0x88(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fsubs -0x7c(%%ebp)\n\t"
      "fchs\n\t"
      "flds -0x88(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "fstps -0x6c(%%ebp)\n\t"
      "flds -0x84(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x68(%%ebp)\n\t"
      "flds -0x80(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "fstps -0x64(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_001a2f40_35:\n\t"
      "pushl $0x18\n\t"
      "leal 0x48(%%edi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x90(%%esi), %%eax\n\t"
      "movl 0x14(%%ebx), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "sete %%al\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testb %%al, %%al\n\t"
      "sete %%cl\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "movl 0x10(%%ebx,%%ecx,4), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0xb4(%%ebp)\n\t"
      "je .LFUN_001a2f40_41\n\t"
      "pushl $0xc\n\t"
      "pushl %%eax\n\t"
      "leal 0x3c(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $2, 0x5(%%esi)\n\t"
      "jne .LFUN_001a2f40_36\n\t"
      "testb $4, 0x8(%%eax)\n\t"
      "je .LFUN_001a2f40_41\n\t"
      ".LFUN_001a2f40_36:\n\t"
      "movl (%%eax), %%eax\n\t"
      "leal -0x88(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c99640]\n\t"
      "flds -0x84(%%ebp)\n\t"
      "fmuls -0x74(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "flds -0x80(%%ebp)\n\t"
      "fmuls -0x70(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x78(%%ebp)\n\t"
      "fmuls -0x88(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a2f40_41\n\t"
      "flds -0x80(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds -0x84(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls -0x88(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fsubs -0x7c(%%ebp)\n\t"
      "flds 0x58(%%esi)\n\t"
      "fmuls 0x255964\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a2f40_41\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "movl -0x60(%%ebp), %%eax\n\t"
      "pushl $0x10\n\t"
      "addl $0x54, %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x4(%%ebx), %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl -0x60(%%ebp), %%eax\n\t"
      "pushl $0x10\n\t"
      "pushl %%edx\n\t"
      "addl $0x54, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "addl $0x18, %%esp\n\t"
      "fsubs (%%edi)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x6c(%%ebp)\n\t"
      "fsubs (%%edi)\n\t"
      "flds -0x68(%%ebp)\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "flds -0x64(%%ebp)\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fsts -0x8c(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a2f40_37\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl %%eax, -0x54(%%ebp)\n\t"
      "movl %%ecx, -0x50(%%ebp)\n\t"
      "movl %%edx, -0x4c(%%ebp)\n\t"
      "jmp .LFUN_001a2f40_39\n\t"
      ".LFUN_001a2f40_37:\n\t"
      "flds -0x8c(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a2f40_38\n\t"
      "movl (%%ecx), %%eax\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%eax, -0x54(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%eax\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "jmp .LFUN_001a2f40_39\n\t"
      ".LFUN_001a2f40_38:\n\t"
      "movl -0x8c(%%ebp), %%edx\n\t"
      "leal -0x54(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[vsca]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_001a2f40_39:\n\t"
      "leal -0x54(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x6c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c121a0]\n\t"
      "fcoms -0x48(%%ebp)\n\t"
      "movl -0x60(%%ebp), %%edi\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a2f40_40\n\t"
      "movl -0xb4(%%ebp), %%eax\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "movl -0x88(%%ebp), %%ecx\n\t"
      "movl -0x84(%%ebp), %%edx\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "movl -0x80(%%ebp), %%eax\n\t"
      "movl %%ecx, -0xa8(%%ebp)\n\t"
      "movl -0x7c(%%ebp), %%ecx\n\t"
      "movl %%edx, -0xa4(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl %%eax, -0xa0(%%ebp)\n\t"
      "movl %%ecx, -0x9c(%%ebp)\n\t"
      "movl %%edx, -0x40(%%ebp)\n\t"
      "jmp .LFUN_001a2f40_41\n\t"
      ".LFUN_001a2f40_40:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_001a2f40_41:\n\t"
      "movzbl -0x1(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebx,%%eax,4), %%ebx\n\t"
      "movl -0xac(%%ebp), %%ecx\n\t"
      "cmpl 0x4(%%ecx), %%ebx\n\t"
      "jne .LFUN_001a2f40_35\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_001a2f40_44\n\t"
      "flds 0x58(%%esi)\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "flds -0x48(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001a2f40_44\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fcomps 0x2b509c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001a2f40_44\n\t"
      "flds -0xa0(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds -0xa4(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0xa8(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x9c(%%ebp)\n\t"
      "fadds 0x58(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fabs\n\t"
      "flds 0x58(%%esi)\n\t"
      "fmuls 0x253398\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001a2f40_44\n\t"
      "flds -0xa4(%%ebp)\n\t"
      "fmuls -0x74(%%ebp)\n\t"
      "flds -0xa0(%%ebp)\n\t"
      "fmuls -0x70(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0xa8(%%ebp)\n\t"
      "fmuls -0x78(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fchs\n\t"
      "flds -0xa8(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0xa4(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0xa0(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fcoms 0x256348\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a2f40_42\n\t"
      "fadds 0x2546a4\n\t"
      "leal -0x78(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "fchs\n\t"
      "leal -0xa8(%%ebp), %%eax\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "leal -0x78(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[vsca]\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_001a2f40_43\n\t"
      ".LFUN_001a2f40_42:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_001a2f40_43:\n\t"
      "flds 0x58(%%esi)\n\t"
      "movl -0xa4(%%ebp), %%eax\n\t"
      "fchs\n\t"
      "movl -0xa8(%%ebp), %%edx\n\t"
      "flds -0xa8(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movl %%eax, -0x364(%%ebp)\n\t"
      "movl -0x9c(%%ebp), %%eax\n\t"
      "movl %%edx, -0x368(%%ebp)\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "movl -0xa0(%%ebp), %%edx\n\t"
      "movl %%eax, -0x35c(%%ebp)\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "fstps -0x374(%%ebp)\n\t"
      "movl $1, -0x3c(%%ebp)\n\t"
      "flds -0xa4(%%ebp)\n\t"
      "movl $0, -0x378(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movl %%edx, -0x360(%%ebp)\n\t"
      "movl %%eax, -0x358(%%ebp)\n\t"
      "movl %%ecx, -0x354(%%ebp)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "movb $0, -0x350(%%ebp)\n\t"
      "movb $0, -0x34f(%%ebp)\n\t"
      "movw %%ax, -0x34e(%%ebp)\n\t"
      "fstps -0x370(%%ebp)\n\t"
      "movl %%ecx, 0xa8(%%esi)\n\t"
      "flds -0xa0(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "fstps -0x36c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_001a2f40_44:\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "fmuls -0x5c(%%ebp)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fmuls -0x58(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fcoms 0x2b5098\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a2f40_45\n\t"
      "fsqrt\n\t"
      "fdivrl 0x2573d8\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "fmuls -0x5c(%%ebp)\n\t"
      "fstps -0x5c(%%ebp)\n\t"
      "jmp .LFUN_001a2f40_46\n\t"
      ".LFUN_001a2f40_45:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_001a2f40_46:\n\t"
      "testb $0x10, 0x4(%%esi)\n\t"
      "movl $0xffffffff, -0x38(%%ebp)\n\t"
      "movb $0, -0x9(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movl $0xff7fffff, -0x48(%%ebp)\n\t"
      "movl $0xff7fffff, -0x8c(%%ebp)\n\t"
      "jne .LFUN_001a2f40_61\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpw %%bx, -0x3c(%%ebp)\n\t"
      "jle .LFUN_001a2f40_61\n\t"
      "leal -0x364(%%ebp), %%edi\n\t"
      ".LFUN_001a2f40_47:\n\t"
      "movb 0x4(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "js .LFUN_001a2f40_49\n\t"
      "movb -0x31(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a2f40_48\n\t"
      "testb $4, 0x14(%%edi)\n\t"
      "je .LFUN_001a2f40_49\n\t"
      ".LFUN_001a2f40_48:\n\t"
      "movb $1, %%dl\n\t"
      "jmp .LFUN_001a2f40_50\n\t"
      ".LFUN_001a2f40_49:\n\t"
      "xorb %%dl, %%dl\n\t"
      ".LFUN_001a2f40_50:\n\t"
      "movl 0xa8(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001a2f40_51\n\t"
      "movswl -0x38(%%ebp), %%ecx\n\t"
      "imull $0x2c, %%ecx, %%ecx\n\t"
      "cmpl %%eax, -0x354(%%ebp,%%ecx,1)\n\t"
      "jne .LFUN_001a2f40_51\n\t"
      "movb $1, %%cl\n\t"
      "jmp .LFUN_001a2f40_52\n\t"
      ".LFUN_001a2f40_51:\n\t"
      "xorb %%cl, %%cl\n\t"
      ".LFUN_001a2f40_52:\n\t"
      "testb %%dl, %%dl\n\t"
      "flds 0xbc(%%esi)\n\t"
      "fmuls (%%edi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls 0xc0(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "flds 0xb8(%%esi)\n\t"
      "fmuls -0x4(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "fchs\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "je .LFUN_001a2f40_54\n\t"
      "movb -0x31(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a2f40_53\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fmuls -0x4(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "fcomps 0x253398\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001a2f40_56\n\t"
      ".LFUN_001a2f40_53:\n\t"
      "movb -0x9(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a2f40_55\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_001a2f40_55\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a2f40_56\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps -0x8c(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001a2f40_55\n\t"
      "jmp .LFUN_001a2f40_56\n\t"
      ".LFUN_001a2f40_54:\n\t"
      "movb -0x9(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a2f40_56\n\t"
      "flds 0x4(%%edi)\n\t"
      "fcomps -0x48(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a2f40_56\n\t"
      ".LFUN_001a2f40_55:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movb %%dl, -0x9(%%ebp)\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "movl %%ebx, -0x38(%%ebp)\n\t"
      "movb %%cl, -0x1(%%ebp)\n\t"
      "movl %%edx, -0x48(%%ebp)\n\t"
      "movl %%eax, -0x8c(%%ebp)\n\t"
      ".LFUN_001a2f40_56:\n\t"
      "testb $0x10, 0xa0(%%esi)\n\t"
      "jne .LFUN_001a2f40_58\n\t"
      "testb $8, 0x14(%%edi)\n\t"
      "jne .LFUN_001a2f40_57\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001a2f40_58\n\t"
      "movl 0x5a8d50, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movb 0x3(%%eax), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "testb $0x40, %%dl\n\t"
      "jne .LFUN_001a2f40_58\n\t"
      ".LFUN_001a2f40_57:\n\t"
      "orb $0x10, 0xa0(%%esi)\n\t"
      ".LFUN_001a2f40_58:\n\t"
      "incl %%ebx\n\t"
      "addl $0x2c, %%edi\n\t"
      "cmpw -0x3c(%%ebp), %%bx\n\t"
      "jl .LFUN_001a2f40_47\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001a2f40_61\n\t"
      "movswl %%ax, %%ebx\n\t"
      "imull $0x2c, %%ebx, %%ebx\n\t"
      "leal -0x368(%%ebp,%%ebx,1), %%edi\n\t"
      "movl %%edi, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%ecx, -0x88(%%ebp)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%edx, -0x84(%%ebp)\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "flds -0x84(%%ebp)\n\t"
      "movb -0x9(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "fmuls -0x94(%%ebp)\n\t"
      "movl %%ecx, -0x80(%%ebp)\n\t"
      "movl %%edx, -0x7c(%%ebp)\n\t"
      "flds -0x80(%%ebp)\n\t"
      "fmuls -0x90(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x88(%%ebp)\n\t"
      "fmuls -0x98(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fchs\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "jne .LFUN_001a2f40_59\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a2f40_59\n\t"
      "flds -0x48(%%ebp)\n\t"
      "fcomps 0x64(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001a2f40_61\n\t"
      "testb $1, 0x4(%%esi)\n\t"
      "je .LFUN_001a2f40_59\n\t"
      "flds 0x5c(%%esi)\n\t"
      "fcomps 0x2548fc\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a2f40_59\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "leal -0x6c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x88(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x98(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[vsca]\n\t"
      "movl 0x5c(%%esi), %%ecx\n\t"
      "leal -0x6c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "call *%[c12170]\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "addl $0x14, %%esp\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a2f40_59\n\t"
      "leal -0x98(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[v2fe0]\n\t"
      "fdivrs -0x38(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "fcomps 0x60(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001a2f40_61\n\t"
      ".LFUN_001a2f40_59:\n\t"
      "movl (%%edi), %%edx\n\t"
      "movl -0x354(%%ebp,%%ebx,1), %%ebx\n\t"
      "andb $0xfe, 0xa0(%%esi)\n\t"
      "cmpl $-1, %%ebx\n\t"
      "leal 0x80(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl 0xc(%%edi), %%edx\n\t"
      "movl %%edx, 0xc(%%ecx)\n\t"
      "movl %%ebx, 0xa4(%%esi)\n\t"
      "je .LFUN_001a2f40_60\n\t"
      "cmpl 0xa8(%%esi), %%ebx\n\t"
      "je .LFUN_001a2f40_62\n\t"
      ".LFUN_001a2f40_60:\n\t"
      "flds -0x94(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "flds -0x90(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x98(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      "faddp %%st(1)\n\t"
      "fchs\n\t"
      "fstps 0xc4(%%esi)\n\t"
      "jmp .LFUN_001a2f40_63\n\t"
      ".LFUN_001a2f40_61:\n\t"
      "orb $1, 0xa0(%%esi)\n\t"
      "movl 0x32513c, %%ecx\n\t"
      "leal 0x80(%%esi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x325140, %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x325144, %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl 0x325148, %%edx\n\t"
      "movl %%edx, 0xc(%%eax)\n\t"
      "movl $0xffffffff, 0xa4(%%esi)\n\t"
      ".LFUN_001a2f40_62:\n\t"
      "movl $0, 0xc4(%%esi)\n\t"
      ".LFUN_001a2f40_63:\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "cmpw $0, -0x3c(%%ebp)\n\t"
      "jle .LFUN_001a2f40_67\n\t"
      "movzwl -0x3c(%%ebp), %%eax\n\t"
      "leal -0x358(%%ebp), %%edi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_001a2f40_64:\n\t"
      "movl (%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001a2f40_66\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x18(%%ecx)\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "fsubs -0x78(%%ebp)\n\t"
      "flds 0x1c(%%ecx)\n\t"
      "fsubs -0x74(%%ebp)\n\t"
      "flds 0x20(%%ecx)\n\t"
      "fsubs -0x70(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "je .LFUN_001a2f40_78\n\t"
      "movl $1, %%eax\n\t"
      "cmpw %%ax, -0x40(%%ebp)\n\t"
      "jne .LFUN_001a2f40_76\n\t"
      "cmpw %%ax, 0x64(%%ecx)\n\t"
      "je .LFUN_001a2f40_77\n\t"
      ".LFUN_001a2f40_65:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_001a2f40_66:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0x2c, %%edi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jne .LFUN_001a2f40_64\n\t"
      ".LFUN_001a2f40_67:\n\t"
      "movl -0x3c(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%ebx, 0x98(%%esi)\n\t"
      "movl $0xffffffff, 0x9c(%%esi)\n\t"
      "jle .LFUN_001a2f40_70\n\t"
      "movzwl %%ax, %%edx\n\t"
      "leal -0x358(%%ebp), %%ebx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      ".LFUN_001a2f40_68:\n\t"
      "movl (%%ebx), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_001a2f40_69\n\t"
      "pushl $0x80\n\t"
      "pushl %%edi\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001a2f40_69\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6d616368\n\t"
      "call *%[tag]\n\t"
      "movb 0x292(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $4, %%cl\n\t"
      "je .LFUN_001a2f40_69\n\t"
      "cmpw $-1, 0x2ea(%%eax)\n\t"
      "je .LFUN_001a2f40_69\n\t"
      "movl %%edi, 0x9c(%%esi)\n\t"
      ".LFUN_001a2f40_69:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0x2c, %%ebx\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jne .LFUN_001a2f40_68\n\t"
      ".LFUN_001a2f40_70:\n\t"
      "flds -0x78(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "fsubs -0x98(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "flds -0x74(%%ebp)\n\t"
      "leal 0xac(%%esi), %%edi\n\t"
      "fsubs -0x94(%%ebp)\n\t"
      "movl %%edi, %%ecx\n\t"
      "flds -0x70(%%ebp)\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "fsubs -0x90(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "fld %%st(0)\n\t"
      "movl -0x78(%%ebp), %%ecx\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movl -0x74(%%ebp), %%edx\n\t"
      "fld %%st(2)\n\t"
      "leal 0xb8(%%esi), %%eax\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x70(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "faddp %%st(1)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "fld %%st(3)\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "testb $4, %%al\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fsqrt\n\t"
      "fstps 0xc8(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0xc0(%%esi)\n\t"
      "fsubs 0x38(%%esi)\n\t"
      "fstps 0xc0(%%esi)\n\t"
      "je .LFUN_001a2f40_71\n\t"
      "testb $8, %%al\n\t"
      "je .LFUN_001a2f40_71\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "movl 0x1c8(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_001a2f40_71\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movb 0x2f4(%%ebx), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb $0x18, %%al\n\t"
      "jne .LFUN_001a2f40_71\n\t"
      "movb 0x4(%%esi), %%al\n\t"
      "flds 0x424(%%ebx)\n\t"
      "fmuls 0x253398\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x6c(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "andb $0x80, %%al\n\t"
      "movl %%edx, -0x68(%%ebp)\n\t"
      "negb %%al\n\t"
      "movl %%ecx, -0x64(%%ebp)\n\t"
      "flds -0x64(%%ebp)\n\t"
      "movl (%%esi), %%ecx\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "leal -0xafac(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x42c(%%ebx), %%edx\n\t"
      "fstps -0x64(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "sbbl %%eax, %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "andl $0xffdffd00, %%eax\n\t"
      "leal -0x6c(%%ebp), %%edx\n\t"
      "addl $0x20c3a0, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c4ec30]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a2f40_71\n\t"
      "flds 0x42c(%%ebx)\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "leal -0x54(%%ebp), %%ecx\n\t"
      "leal -0xafac(%%ebp), %%edx\n\t"
      "fsubrs 0x424(%%ebx)\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%eax)\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "leal -0x3a4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "call *%[c14c4b0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a2f40_71\n\t"
      "orb $4, 0xa0(%%esi)\n\t"
      ".LFUN_001a2f40_71:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_001a2f40_72\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, -0x40(%%ebp)\n\t"
      "je .LFUN_001a2f40_72\n\t"
      "movl 0x8(%%edi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, -0x40(%%ebp)\n\t"
      "jne .LFUN_001a2f40_73\n\t"
      ".LFUN_001a2f40_72:\n\t"
      "flds 0xb4(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0xee2\n\t"
      "pushl $0x2b4d5c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0xb0(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b5080\n\t"
      "pushl $0x26ae04\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a2f40_73:\n\t"
      "movl 0xb8(%%esi), %%ecx\n\t"
      "leal 0xb8(%%esi), %%eax\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, -0x40(%%ebp)\n\t"
      "popl %%edi\n\t"
      "je .LFUN_001a2f40_74\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, -0x40(%%ebp)\n\t"
      "je .LFUN_001a2f40_74\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, -0x40(%%ebp)\n\t"
      "jne .LFUN_001a2f40_75\n\t"
      ".LFUN_001a2f40_74:\n\t"
      "flds 0xc0(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0xee3\n\t"
      "pushl $0x2b4d5c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0xbc(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%eax)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b5068\n\t"
      "pushl $0x26ae40\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a2f40_75:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a2f40_76:\n\t"
      "cmpw %%ax, 0x64(%%ecx)\n\t"
      "je .LFUN_001a2f40_78\n\t"
      ".LFUN_001a2f40_77:\n\t"
      "fcoms -0xac(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a2f40_65\n\t"
      ".LFUN_001a2f40_78:\n\t"
      "movw 0x64(%%ecx), %%cx\n\t"
      "fstps -0xac(%%ebp)\n\t"
      "movl (%%edi), %%ebx\n\t"
      "movw %%cx, -0x40(%%ebp)\n\t"
      "jmp .LFUN_001a2f40_66\n\t"
      :
      : [chkstk] "m"(b1a2f40_chkstk), [ca16b0] "m"(b1a2f40_ca16b0), [c8d9d0] "m"(b1a2f40_c8d9d0), [assert] "m"(b1a2f40_assert), [exitfn] "m"(b1a2f40_exitfn), [c84a10] "m"(b1a2f40_c84a10), [c1a2d90] "m"(b1a2f40_c1a2d90), [norm] "m"(b1a2f40_norm), [mag] "m"(b1a2f40_mag), [cross] "m"(b1a2f40_cross), [vsca] "m"(b1a2f40_vsca), [c150550] "m"(b1a2f40_c150550), [get] "m"(b1a2f40_get), [gbsp] "m"(b1a2f40_gbsp), [elem] "m"(b1a2f40_elem), [c99640] "m"(b1a2f40_c99640), [c121a0] "m"(b1a2f40_c121a0), [dget] "m"(b1a2f40_dget), [c12170] "m"(b1a2f40_c12170), [v2fe0] "m"(b1a2f40_v2fe0), [tryget] "m"(b1a2f40_tryget), [tag] "m"(b1a2f40_tag), [c4ec30] "m"(b1a2f40_c4ec30), [c14c4b0] "m"(b1a2f40_c14c4b0)
      : "memory");
}
#else
#error "FUN_001a2f40: clang naked draft required"
#endif

/* --- bipeds.obj orphan shells (2026-07-26) --- */

/* kb export alias @ 0x1a0db0 */
char FUN_001a0db0(int biped_handle)
{
  char *unit_obj = (char *)object_get_and_verify_type(biped_handle, 1);
  char *biped_tag = (char *)tag_get(0x62697064, *(int *)unit_obj);

  if (*(char *)(unit_obj + 0x459) > 3 &&
      (((*(unsigned char *)(biped_tag + 0x2f4) & 4) == 0) ||
       ((*(unsigned char *)(unit_obj + 0xb6) & 4) != 0))) {
    return 1;
  }
  return 0;
}
