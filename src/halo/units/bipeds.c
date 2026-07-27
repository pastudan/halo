/* bipeds.c — biped-specific unit functions.
 *
 * Corresponds to bipeds.obj. Functions sorted by XBE address.
 * Debug assertion path: c:\halo\SOURCE\units\bipeds.c
 */

#include "../../common.h"
#include "../../x87_math.h"

/* FUN_001a01d0 (0x1a01d0) — XBE naked draft (batch 55). */
#if defined(__clang__)
static void (*const b1a01d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1a01d0_exitfn)(int) = system_exit;
static float (*const b1a01d0_norm)(float *) = normalize3d;

__attribute__((naked, noinline))
void FUN_001a01d0(float *forward __attribute__((unused)), float *left __attribute__((unused)), float *up __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_001a01d0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x217\n\t"
      "pushl $0x2b4b48\n\t"
      "pushl $0x28cb2c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a01d0_1:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .LFUN_001a01d0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x217\n\t"
      "pushl $0x2b4b48\n\t"
      "pushl $0x253c4c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a01d0_2:\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_001a01d0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x217\n\t"
      "pushl $0x2b4b48\n\t"
      "pushl $0x28cb28\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a01d0_3:\n\t"
      "pushl %%esi\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001a01d0_4\n\t"
      "movl 0x31fc3c, %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      ".LFUN_001a01d0_4:\n\t"
      "pushl %%edi\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001a01d0_5\n\t"
      "movl 0x31fc44, %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "movl %%edi, %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      ".LFUN_001a01d0_5:\n\t"
      "flds 0x4(%%esi)\n\t"
      "pushl %%ebx\n\t"
      "fmuls (%%edi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls (%%esi)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps (%%ebx)\n\t"
      "fstps 0x4(%%ebx)\n\t"
      "fstps 0x8(%%ebx)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001a01d0_6\n\t"
      "movl 0x31fc40, %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      ".LFUN_001a01d0_6:\n\t"
      "flds 0x4(%%ebx)\n\t"
      "pushl %%edi\n\t"
      "fmuls (%%esi)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fmuls (%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x8(%%esi)\n\t"
      "fmuls (%%ebx)\n\t"
      "flds (%%esi)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x4(%%esi)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps (%%edi)\n\t"
      "fstps 0x4(%%edi)\n\t"
      "fstps 0x8(%%edi)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001a01d0_7\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      ".LFUN_001a01d0_7:\n\t"
      "flds 0x4(%%esi)\n\t"
      "pushl %%ebx\n\t"
      "fmuls (%%edi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls (%%esi)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps (%%ebx)\n\t"
      "fstps 0x4(%%ebx)\n\t"
      "fstps 0x8(%%ebx)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001a01d0_8\n\t"
      "movl 0x31fc40, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, (%%ebx)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, 0x4(%%ebx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%ebx)\n\t"
      ".LFUN_001a01d0_8:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [assert] "m"(b1a01d0_assert), [exitfn] "m"(b1a01d0_exitfn), [norm] "m"(b1a01d0_norm)
      : "memory");
}
#else
#error "FUN_001a01d0: clang naked draft required"
#endif


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


/* FUN_001a0680 (0x1a0680) — XBE naked draft (batch 60). */
#if defined(__clang__)
static void *(*const b1a0680_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a0680_tag)(int, int) = tag_get;
static void * (*const b1a0680_c13dfc0)(int object_handle, void *reference) = object_header_block_reference_get;
static void (*const b1a0680_c19fa20)(int unit_handle, void *node_block) = FUN_0019fa20;
static void (*const b1a0680_c1a03c0)(int unit_handle, int node_count, float *positions, void *nodes) = FUN_001a03c0;

__attribute__((naked, noinline))
char FUN_001a0680(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
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
      "jne .LFUN_001a0680_4\n\t"
      "movl 0x68(%%edi), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "jle .LFUN_001a0680_2\n\t"
      "movl $0x4e49f0, %%ecx\n\t"
      "addl $0x28, %%eax\n\t"
      ".LFUN_001a0680_1:\n\t"
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
      "jl .LFUN_001a0680_1\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      ".LFUN_001a0680_2:\n\t"
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
      "jae .LFUN_001a0680_3\n\t"
      "incb %%al\n\t"
      "movb %%al, 0x47c(%%esi)\n\t"
      ".LFUN_001a0680_3:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a0680_4:\n\t"
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
      :
      : [get] "m"(b1a0680_get), [tag] "m"(b1a0680_tag), [c13dfc0] "m"(b1a0680_c13dfc0), [c19fa20] "m"(b1a0680_c19fa20), [c1a03c0] "m"(b1a0680_c1a03c0)
      : "memory");
}
#else
#error "FUN_001a0680: clang naked draft required"
#endif


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

/* FUN_001a0a40 (0x1a0a40) — XBE naked draft (batch 63). */
#if defined(__clang__)
static void *(*const b1a0a40_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a0a40_tag)(int, int) = tag_get;
static void (*const b1a0a40_c40360)(int param_1, int param_2, float *velocity_ptr) = ai_handle_bump;
static char (*const b1a0a40_c94ff0)(int unit_handle) = recorded_animation_controlling_unit;
static int16_t (*const b1a0a40_cb6990)(int unit_handle) = unit_get_local_player_index;
static void (*const b1a0a40_cba5f0)(int16_t local_player_index, int unit_handle) = players_set_local_player_unit;

__attribute__((naked, noinline))
void FUN_001a0a40(int contact_handle __attribute__((unused)), int unit_handle __attribute__((unused)), float *velocity_ptr __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movb 0x458(%%esi), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jge .LFUN_001a0a40_1\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .LFUN_001a0a40_4\n\t"
      "incb %%al\n\t"
      "movb %%al, 0x458(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a0a40_1:\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_001a0a40_5\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[c40360]\n\t"
      "movl 0x1c8(%%esi), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_001a0a40_2\n\t"
      "pushl %%ebx\n\t"
      "call *%[c94ff0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a0a40_5\n\t"
      ".LFUN_001a0a40_2:\n\t"
      "cmpl %%edi, 0x454(%%esi)\n\t"
      "je .LFUN_001a0a40_3\n\t"
      "movl %%edi, 0x454(%%esi)\n\t"
      "movb $0, 0x458(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a0a40_3:\n\t"
      "movb 0x458(%%esi), %%cl\n\t"
      "incb %%cl\n\t"
      "movb %%cl, %%al\n\t"
      "cmpb $3, %%al\n\t"
      "movb %%cl, 0x458(%%esi)\n\t"
      "jle .LFUN_001a0a40_5\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "cmpw $0, 0x64(%%edx)\n\t"
      "jne .LFUN_001a0a40_4\n\t"
      "movb 0x5aa893, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a0a40_4\n\t"
      "pushl %%ebx\n\t"
      "call *%[cb6990]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001a0a40_4\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movb $0xf1, 0x458(%%ecx)\n\t"
      "call *%[cba5f0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001a0a40_4:\n\t"
      "movb $0xf1, 0x458(%%esi)\n\t"
      ".LFUN_001a0a40_5:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a0a40_get), [tag] "m"(b1a0a40_tag), [c40360] "m"(b1a0a40_c40360), [c94ff0] "m"(b1a0a40_c94ff0), [cb6990] "m"(b1a0a40_cb6990), [cba5f0] "m"(b1a0a40_cba5f0)
      : "memory");
}
#else
#error "FUN_001a0a40: clang naked draft required"
#endif


/* FUN_001a0b30 (0x1a0b30) — XBE naked draft (batch 65). */
#if defined(__clang__)
static void *(*const b1a0b30_get)(int, int) = object_get_and_verify_type;
static bool (*const b1a0b30_gerun)(void) = game_engine_running;
static char * (*const b1a0b30_c49ac0)(int actor_handle, int object_handle, char with_actor, char *buf, int buf_size) = ai_debug_describe_actor;
static const char * (*const b1a0b30_c1ba1f0)(int tag_index) = tag_get_name;
static const char * (*const b1a0b30_c19b0d0)(const char *tag_name) = tag_name_strip_path;
static void (*const b1a0b30_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b1a0b30_odel)(int) = object_delete;

__attribute__((naked, noinline))
char FUN_001a0b30(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[gerun]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a0b30_3\n\t"
      "testl $0x200000, 0x4(%%esi)\n\t"
      "jne .LFUN_001a0b30_1\n\t"
      "cmpw $-1, 0x4c(%%esi)\n\t"
      "jne .LFUN_001a0b30_3\n\t"
      ".LFUN_001a0b30_1:\n\t"
      "flds 0x14(%%esi)\n\t"
      "fcomps 0x2b4d1c\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a0b30_3\n\t"
      "movl 0x1a8(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_001a0b30_2\n\t"
      "movl 0x1a4(%%esi), %%eax\n\t"
      ".LFUN_001a0b30_2:\n\t"
      "pushl $0x100\n\t"
      "pushl $0x5ab100\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c49ac0]\n\t"
      "flds 0x14(%%esi)\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%eax\n\t"
      "movl (%%esi), %%eax\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x10(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ba1f0]\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b0d0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b4cd8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "pushl %%edi\n\t"
      "call *%[odel]\n\t"
      "addl $0x2c, %%esp\n\t"
      ".LFUN_001a0b30_3:\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a0b30_get), [gerun] "m"(b1a0b30_gerun), [c49ac0] "m"(b1a0b30_c49ac0), [c1ba1f0] "m"(b1a0b30_c1ba1f0), [c19b0d0] "m"(b1a0b30_c19b0d0), [c8f390] "m"(b1a0b30_c8f390), [odel] "m"(b1a0b30_odel)
      : "memory");
}
#else
#error "FUN_001a0b30: clang naked draft required"
#endif


/* FUN_001a0be0 (0x1a0be0) — XBE naked draft (batch 56). */
#if defined(__clang__)
static void *(*const b1a0be0_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a0be0_tag)(int, int) = tag_get;
static void * (*const b1a0be0_c18e450)(void) = game_globals_get;
static void *(*const b1a0be0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1a0be0_c136750)(void *damage_params, int tag_index) = damage_data_new;
static void (*const b1a0be0_c137d20)(void *damage_params, int object_handle, short node_index, short region_index, short permutation_index, unsigned int flags) = object_cause_damage;
static bool (*const b1a0be0_gerun)(void) = game_engine_running;
static int (*const b1a0be0_cba500)(int) = player_index_from_unit_index;
static char * (*const b1a0be0_c49ac0)(int actor_handle, int object_handle, char with_actor, char *buf, int buf_size) = ai_debug_describe_actor;
static const char * (*const b1a0be0_c1ba1f0)(int tag_index) = tag_get_name;
static const char * (*const b1a0be0_c19b0d0)(const char *tag_name) = tag_name_strip_path;
static void (*const b1a0be0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b1a0be0_odel)(int) = object_delete;

__attribute__((naked, noinline))
void FUN_001a0be0(float vertical_speed __attribute__((unused)), int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x58, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl $0x98\n\t"
      "pushl $0\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[c18e450]\n\t"
      "addl $0x188, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x1b4(%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $0x10, %%ah\n\t"
      "jne .LFUN_001a0be0_1\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movb 0x2f4(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "js .LFUN_001a0be0_1\n\t"
      "xorb %%cl, %%cl\n\t"
      "jmp .LFUN_001a0be0_2\n\t"
      ".LFUN_001a0be0_1:\n\t"
      "movb $1, %%cl\n\t"
      ".LFUN_001a0be0_2:\n\t"
      "movb 0x5aa891, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a0be0_3\n\t"
      "cmpl $-1, 0x1c8(%%esi)\n\t"
      "jne .LFUN_001a0be0_9\n\t"
      ".LFUN_001a0be0_3:\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x90(%%ebx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a0be0_6\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_001a0be0_9\n\t"
      "movl 0x1c(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c136750]\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fsubs 0x90(%%ebx)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x94(%%ebx)\n\t"
      "fsubs 0x90(%%ebx)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fsts -0x18(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a0be0_4\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "jmp .LFUN_001a0be0_5\n\t"
      ".LFUN_001a0be0_4:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a0be0_5\n\t"
      "movl $0x3f800000, -0x18(%%ebp)\n\t"
      ".LFUN_001a0be0_5:\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c137d20]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a0be0_6:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movb $4, %%dl\n\t"
      "testb %%dl, 0x2f4(%%eax)\n\t"
      "jne .LFUN_001a0be0_9\n\t"
      "flds 0x8c(%%ebx)\n\t"
      "fchs\n\t"
      "fcomps 0x20(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a0be0_9\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_001a0be0_7\n\t"
      "testb %%dl, 0xb6(%%esi)\n\t"
      "jne .LFUN_001a0be0_7\n\t"
      "movl 0x38(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x58(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c136750]\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c137d20]\n\t"
      "addl $0x20, %%esp\n\t"
      ".LFUN_001a0be0_7:\n\t"
      "call *%[gerun]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a0be0_9\n\t"
      "testl $0x200000, 0x4(%%esi)\n\t"
      "je .LFUN_001a0be0_9\n\t"
      "pushl %%edi\n\t"
      "call *%[cba500]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_001a0be0_9\n\t"
      "movl 0x1a8(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_001a0be0_8\n\t"
      "movl 0x1a4(%%esi), %%eax\n\t"
      ".LFUN_001a0be0_8:\n\t"
      "pushl $0x100\n\t"
      "pushl $0x5ab100\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c49ac0]\n\t"
      "movl (%%esi), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ba1f0]\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b0d0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b4d20\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "pushl %%edi\n\t"
      "call *%[odel]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a0be0_9:\n\t"
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
      :
      : [get] "m"(b1a0be0_get), [tag] "m"(b1a0be0_tag), [c18e450] "m"(b1a0be0_c18e450), [elem] "m"(b1a0be0_elem), [c136750] "m"(b1a0be0_c136750), [c137d20] "m"(b1a0be0_c137d20), [gerun] "m"(b1a0be0_gerun), [cba500] "m"(b1a0be0_cba500), [c49ac0] "m"(b1a0be0_c49ac0), [c1ba1f0] "m"(b1a0be0_c1ba1f0), [c19b0d0] "m"(b1a0be0_c19b0d0), [c8f390] "m"(b1a0be0_c8f390), [odel] "m"(b1a0be0_odel)
      : "memory");
}
#else
#error "FUN_001a0be0: clang naked draft required"
#endif


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

/* FUN_001a0e00 (0x1a0e00) — XBE naked draft (batch 63). */
#if defined(__clang__)
static void *(*const b1a0e00_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a0e00_tag)(int, int) = tag_get;
static void (*const b1a0e00_ftol)(void) = FUN_001d9068;

__attribute__((naked, noinline))
void FUN_001a0e00(float threshold __attribute__((unused)), int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x3dc(%%ecx)\n\t"
      "addl $0x10, %%esp\n\t"
      "fmuls 0x2546a4\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds 0x3e0(%%ecx)\n\t"
      "fmuls 0x2546a4\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001a0e00_6\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a0e00_1\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "flds 0x3d4(%%ecx)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "jmp .LFUN_001a0e00_2\n\t"
      ".LFUN_001a0e00_1:\n\t"
      "flds 0x3e4(%%ecx)\n\t"
      "fmuls 0x2546a4\n\t"
      "fsubs -0x8(%%ebp)\n\t"
      "flds 0x3d8(%%ecx)\n\t"
      "movl $1, %%ecx\n\t"
      ".LFUN_001a0e00_2:\n\t"
      "fmuls 0x253394\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a0e00_5\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a0e00_3\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_001a0e00_4\n\t"
      ".LFUN_001a0e00_3:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a0e00_4\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_001a0e00_4:\n\t"
      "flds 0x8(%%ebp)\n\t"
      "movw %%cx, 0x460(%%esi)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movb $0, 0x428(%%esi)\n\t"
      "call *%[ftol]\n\t"
      "fstp %%st(0)\n\t"
      "movb %%al, 0x429(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a0e00_5:\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_001a0e00_6:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a0e00_get), [tag] "m"(b1a0e00_tag), [ftol] "m"(b1a0e00_ftol)
      : "memory");
}
#else
#error "FUN_001a0e00: clang naked draft required"
#endif


/* FUN_001a0f10 (0x1a0f10) — XBE naked draft (batch 62). */
#if defined(__clang__)
static void *(*const b1a0f10_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a0f10_tag)(int, int) = tag_get;
static void (*const b1a0f10_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1a0f10_exitfn)(int) = system_exit;
static bool (*const b1a0f10_o9f3b0)(void *) = FUN_0009f3b0;
static void *(*const b1a0f10_elem)(void *, int, int) = tag_block_get_element;
static short (*const b1a0f10_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static void (*const b1a0f10_c9f570)(int effect_tag_index, int param_2, void *position, int param_4) = (void *)FUN_0009f570;

__attribute__((naked, noinline))
void FUN_001a0f10(int unit_handle __attribute__((unused)), int param_2 __attribute__((unused)), short index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x70, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x62697064\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "movl %%eax, %%esi\n\t"
      "jl .LFUN_001a0f10_1\n\t"
      "pushl $1\n\t"
      "pushl $0xf4f\n\t"
      "pushl $0x2b4d5c\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a0f10_1:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "movswl %%ax, %%edx\n\t"
      "incw %%ax\n\t"
      "leal 0x4e8(%%esi), %%edi\n\t"
      "movswl %%bx, %%ebx\n\t"
      "movw $7, 0x5a8c80(,%%edx,2)\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "cmpl (%%edi), %%ebx\n\t"
      "jge .LFUN_001a0f10_2\n\t"
      "cmpl $-1, 0x398(%%esi)\n\t"
      "je .LFUN_001a0f10_2\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $0x50, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[o9f3b0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a0f10_2\n\t"
      "pushl $0x40\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "leal -0x70(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $0x20, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[markers]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_001a0f10_2\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x398(%%esi), %%edx\n\t"
      "pushl $0\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c9f570]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_001a0f10_2:\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "jg .LFUN_001a0f10_3\n\t"
      "pushl $1\n\t"
      "pushl $0xf60\n\t"
      "pushl $0x2b4d5c\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a0f10_3:\n\t"
      "decw 0x4761d8\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a0f10_get), [tag] "m"(b1a0f10_tag), [assert] "m"(b1a0f10_assert), [exitfn] "m"(b1a0f10_exitfn), [o9f3b0] "m"(b1a0f10_o9f3b0), [elem] "m"(b1a0f10_elem), [markers] "m"(b1a0f10_markers), [c9f570] "m"(b1a0f10_c9f570)
      : "memory");
}
#else
#error "FUN_001a0f10: clang naked draft required"
#endif


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

/* biped_fix_position (0x1a1430) — XBE naked draft (batch 55). */
#if defined(__clang__)
static void (*const b1a1430_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1a1430_exitfn)(int) = system_exit;
static void (*const b1a1430_c1aae0)(int object_handle, float *center, float *radius) = FUN_0001aae0;
static void *(*const b1a1430_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a1430_tag)(int, int) = tag_get;
static void (*const b1a1430_c1a0890)(int unit_handle, vector3_t *out_pos, float *out_height_offset, float *out_camera_height) = biped_get_camera_height_and_offset;
static int (*const b1a1430_c14c8e0)(int *out, int object_handle) = FUN_0014c8e0;
static float (*const b1a1430_norm)(float *) = normalize3d;
static int (*const b1a1430_c18e720)(int point) = FUN_0018e720;
static void * (*const b1a1430_c18e3c0)(void) = scenario_get;
static void *(*const b1a1430_elem)(void *, int, int) = tag_block_get_element;
static char (*const b1a1430_c14f020)(uint32_t collision_flags, float *point, float vertical_extent, float p4, float p5, int unit_handle, float *point_out) = FUN_0014f020;
static char (*const b1a1430_c14e7d0)(uint32_t collision_flags, float *point, float *offset_vec, float p4, int unit_handle, void *result) = FUN_0014e7d0;
static bool (*const b1a1430_c14cc80)(int param_1, int param_2, int param_3, float param_4, int16_t *param_5) = FUN_0014cc80;
static bool (*const b1a1430_v30d0)(unsigned int, float *, float *, int, short *) = FUN_000130d0;
static void (*const b1a1430_c18f180)(void *location_out, void *point) = scenario_location_from_point;
static void (*const b1a1430_c1446a0)(int object_handle) = object_update_children_recursive;
static void (*const b1a1430_otrans)(int, float *, void *) = object_translate;

__attribute__((naked, noinline))
char biped_fix_position(int unit_handle __attribute__((unused)), int seat_handle __attribute__((unused)), float *initial_position __attribute__((unused)), float *final_position __attribute__((unused)), float scale __attribute__((unused)), char keep_basis __attribute__((unused)), char dont_teleport __attribute__((unused)), char scale_by_height __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x538, %%esp\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "xorb %%bl, %%bl\n\t"
      "testl %%eax, %%eax\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "jne .Lbiped_fix_position_1\n\t"
      "movb 0x20(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lbiped_fix_position_1\n\t"
      "pushl $1\n\t"
      "pushl $0x37d\n\t"
      "pushl $0x2b4d5c\n\t"
      "pushl $0x2b4e68\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbiped_fix_position_1:\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "jl .Lbiped_fix_position_2\n\t"
      "pushl $1\n\t"
      "pushl $0x37f\n\t"
      "pushl $0x2b4d5c\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbiped_fix_position_2:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "pushl %%esi\n\t"
      "movswl %%ax, %%ecx\n\t"
      "incw %%ax\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "cmpl %%esi, %%edi\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movw $7, 0x5a8c80(,%%ecx,2)\n\t"
      "jne .Lbiped_fix_position_3\n\t"
      "cmpl %%esi, %%eax\n\t"
      "je .Lbiped_fix_position_24\n\t"
      "jmp .Lbiped_fix_position_4\n\t"
      ".Lbiped_fix_position_3:\n\t"
      "cmpl %%esi, %%eax\n\t"
      "je .Lbiped_fix_position_5\n\t"
      ".Lbiped_fix_position_4:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x60(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1aae0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lbiped_fix_position_5:\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpl %%esi, %%edi\n\t"
      "jne .Lbiped_fix_position_6\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "movb $1, %%bl\n\t"
      "movl %%edx, %%edi\n\t"
      ".Lbiped_fix_position_6:\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movl 0x2f4(%%eax), %%ecx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "andb $0x20, %%cl\n\t"
      "addl $0x10, %%esp\n\t"
      "negb %%cl\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl $0xffdfff00, %%ecx\n\t"
      "addl $0x20c3a0, %%ecx\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "je .Lbiped_fix_position_7\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      "jmp .Lbiped_fix_position_8\n\t"
      ".Lbiped_fix_position_7:\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      ".Lbiped_fix_position_8:\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a0890]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lbiped_fix_position_9\n\t"
      "movl $0xffffffff, 0x8(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      ".Lbiped_fix_position_9:\n\t"
      "movb 0x1c(%%ebp), %%dl\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testb %%dl, %%dl\n\t"
      "setne %%cl\n\t"
      "movl $0x1b, %%eax\n\t"
      "decl %%ecx\n\t"
      "andl $9, %%ecx\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lbiped_fix_position_10\n\t"
      "pushl %%eax\n\t"
      "leal -0x70(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c14c8e0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lbiped_fix_position_10:\n\t"
      "flds 0x38(%%esi)\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "fmuls 0x28(%%esi)\n\t"
      "pushl %%eax\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fmuls 0x34(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fmuls 0x30(%%esi)\n\t"
      "flds 0x24(%%esi)\n\t"
      "fmuls 0x38(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds 0x24(%%esi)\n\t"
      "fmuls 0x34(%%esi)\n\t"
      "flds 0x30(%%esi)\n\t"
      "fmuls 0x28(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      "addl $4, %%esp\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "movb 0x24(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "je .Lbiped_fix_position_11\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x18(%%ebp)\n\t"
      "fstps 0x18(%%ebp)\n\t"
      ".Lbiped_fix_position_11:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%ebx, -0x20(%%ebp)\n\t"
      "jmp .Lbiped_fix_position_12\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lbiped_fix_position_12:\n\t"
      "cmpw -0x4c(%%ebp), %%bx\n\t"
      "jge .Lbiped_fix_position_23\n\t"
      "movb 0x1c(%%ebp), %%al\n\t"
      "flds 0x18(%%ebp)\n\t"
      "testb %%al, %%al\n\t"
      "movswl %%bx, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "je .Lbiped_fix_position_13\n\t"
      "shll $2, %%eax\n\t"
      "fmuls 0x2b4b80(%%eax)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x24(%%esi)\n\t"
      "fadds -0x2c(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x28(%%esi)\n\t"
      "fadds -0x28(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x2c(%%esi)\n\t"
      "fadds -0x24(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fmuls 0x2b4b84(%%eax)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fmuls 0x2b4b88(%%eax)\n\t"
      "fsts -0x14(%%ebp)\n\t"
      "fmuls 0x30(%%esi)\n\t"
      "fadd %%st(2), %%st(0)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x34(%%esi)\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x38(%%esi)\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "jmp .Lbiped_fix_position_14\n\t"
      ".Lbiped_fix_position_13:\n\t"
      "fmuls 0x2b4b80(,%%eax,4)\n\t"
      "leal 0x2b4b80(,%%eax,4), %%eax\n\t"
      "fadds -0x2c(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fadds -0x28(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "fadds -0x24(%%ebp)\n\t"
      ".Lbiped_fix_position_14:\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18e720]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lbiped_fix_position_22\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl $0x10\n\t"
      "pushl %%edx\n\t"
      "call *%[c18e720]\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e3c0]\n\t"
      "addl $0xe0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl 0x8(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lbiped_fix_position_22\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "flds -0x18(%%ebp)\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "movl -0x30(%%ebp), %%ebx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c14f020]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lbiped_fix_position_21\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "leal -0x110(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "leal -0x48(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c14e7d0]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lbiped_fix_position_21\n\t"
      "cmpl $-1, 0xc(%%ebp)\n\t"
      "je .Lbiped_fix_position_16\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "leal -0x538(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x70(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c14cc80]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lbiped_fix_position_21\n\t"
      "leal -0xc0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "leal -0x60(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[v30d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lbiped_fix_position_15\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "cmpl %%ecx, -0x88(%%ebp)\n\t"
      "jne .Lbiped_fix_position_21\n\t"
      ".Lbiped_fix_position_15:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "leal -0xc0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x60(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[v30d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lbiped_fix_position_16\n\t"
      "cmpl %%edi, -0x88(%%ebp)\n\t"
      "jne .Lbiped_fix_position_21\n\t"
      ".Lbiped_fix_position_16:\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x54(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c18f180]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $-1, -0x50(%%ebp)\n\t"
      "jne .Lbiped_fix_position_17\n\t"
      "pushl $1\n\t"
      "pushl $0x41e\n\t"
      "pushl $0x2b4d5c\n\t"
      "pushl $0x2b4e44\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbiped_fix_position_17:\n\t"
      "testb $8, 0x2f4(%%edi)\n\t"
      "jne .Lbiped_fix_position_18\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fsubs 0x42c(%%edi)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".Lbiped_fix_position_18:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lbiped_fix_position_19\n\t"
      "movb 0x20(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lbiped_fix_position_19\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "leal 0xc(%%esi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "call *%[c1446a0]\n\t"
      "leal -0x54(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[otrans]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lbiped_fix_position_19:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lbiped_fix_position_20\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      ".Lbiped_fix_position_20:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".Lbiped_fix_position_21:\n\t"
      "movl -0x20(%%ebp), %%ebx\n\t"
      ".Lbiped_fix_position_22:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "incl %%ebx\n\t"
      "testb %%al, %%al\n\t"
      "movl %%ebx, -0x20(%%ebp)\n\t"
      "je .Lbiped_fix_position_12\n\t"
      ".Lbiped_fix_position_23:\n\t"
      "movb -0x1(%%ebp), %%bl\n\t"
      ".Lbiped_fix_position_24:\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "jg .Lbiped_fix_position_25\n\t"
      "pushl $1\n\t"
      "pushl $0x438\n\t"
      "pushl $0x2b4d5c\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbiped_fix_position_25:\n\t"
      "decw 0x4761d8\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [assert] "m"(b1a1430_assert), [exitfn] "m"(b1a1430_exitfn), [c1aae0] "m"(b1a1430_c1aae0), [get] "m"(b1a1430_get), [tag] "m"(b1a1430_tag), [c1a0890] "m"(b1a1430_c1a0890), [c14c8e0] "m"(b1a1430_c14c8e0), [norm] "m"(b1a1430_norm), [c18e720] "m"(b1a1430_c18e720), [c18e3c0] "m"(b1a1430_c18e3c0), [elem] "m"(b1a1430_elem), [c14f020] "m"(b1a1430_c14f020), [c14e7d0] "m"(b1a1430_c14e7d0), [c14cc80] "m"(b1a1430_c14cc80), [v30d0] "m"(b1a1430_v30d0), [c18f180] "m"(b1a1430_c18f180), [c1446a0] "m"(b1a1430_c1446a0), [otrans] "m"(b1a1430_otrans)
      : "memory");
}
#else
#error "biped_fix_position: clang naked draft required"
#endif


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

/* FUN_001a1a10 (0x1a1a10) — XBE naked draft (batch 60). */
#if defined(__clang__)
static void *(*const b1a1a10_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a1a10_gbsp)(void) = global_collision_bsp_get;
static void (*const b1a1a10_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1a1a10_exitfn)(int) = system_exit;
static vector3_t * (*const b1a1a10_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static char (*const b1a1a10_c149480)(int collision_flags, int bsp, short flags, int breakable_surfaces, int origin, int direction, float max_t, float *result) = collision_bsp_test_vector;

__attribute__((naked, noinline))
int FUN_001a1a10(float scale __attribute__((unused)), float *out_point __attribute__((unused)), void *out_vec __attribute__((unused)), float *direction __attribute__((unused)), int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x434, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[gbsp]\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl $0xffffffff, -0x1c(%%ebp)\n\t"
      "jl .LFUN_001a1a10_1\n\t"
      "pushl $1\n\t"
      "pushl $0x47a\n\t"
      "pushl $0x2b4d5c\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a1a10_1:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "incw %%ax\n\t"
      "pushl %%edi\n\t"
      "movw $7, 0x5a8c80(,%%ecx,2)\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "call *%[c1412f0]\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "flds (%%eax)\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "fmuls 0x253524\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x253524\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "leal -0x434(%%ebp), %%eax\n\t"
      "fmuls 0x253524\n\t"
      "pushl %%eax\n\t"
      "pushl $0x7f7fffff\n\t"
      "pushl %%ecx\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "flds 0x8(%%ebp)\n\t"
      "pushl $1\n\t"
      "fmuls (%%esi)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "call *%[c149480]\n\t"
      "addl $0x28, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a1a10_3\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl -0x42c(%%ebp), %%esi\n\t"
      "je .LFUN_001a1a10_2\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls -0x434(%%ebp)\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps (%%eax)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x434(%%ebp)\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x434(%%ebp)\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fstps 0x8(%%eax)\n\t"
      ".LFUN_001a1a10_2:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001a1a10_4\n\t"
      "movl -0x430(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "jmp .LFUN_001a1a10_4\n\t"
      ".LFUN_001a1a10_3:\n\t"
      "movl -0x1c(%%ebp), %%esi\n\t"
      ".LFUN_001a1a10_4:\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "jg .LFUN_001a1a10_5\n\t"
      "pushl $1\n\t"
      "pushl $0x490\n\t"
      "pushl $0x2b4d5c\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a1a10_5:\n\t"
      "decw 0x4761d8\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a1a10_get), [gbsp] "m"(b1a1a10_gbsp), [assert] "m"(b1a1a10_assert), [exitfn] "m"(b1a1a10_exitfn), [c1412f0] "m"(b1a1a10_c1412f0), [c149480] "m"(b1a1a10_c149480)
      : "memory");
}
#else
#error "FUN_001a1a10: clang naked draft required"
#endif


/* biped_approximate_surface_index (0x1a1b90) — readable C lift. */
int biped_approximate_surface_index(int unit_handle, float *out_point)
{
  return FUN_001a1a10(2.0f, out_point, (void *)0, *(float **)0x31fc50, unit_handle);
}

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


/* FUN_001a2160 (0x1a2160) — XBE naked draft (batch 59). */
#if defined(__clang__)
static void *(*const b1a2160_get)(int, int) = object_get_and_verify_type;
static float (*const b1a2160_norm)(float *) = normalize3d;
static void (*const b1a2160_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;

__attribute__((naked, noinline))
void FUN_001a2160(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x2c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "leal 0x3c(%%edi), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fld %%st(0)\n\t"
      "fcos\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "leal 0x24(%%edi), %%esi\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "fsin\n\t"
      "pushl %%ebx\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[rots]\n\t"
      "pushl %%esi\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $0x30, %%edi\n\t"
      "movl %%edi, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[rots]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "pushl %%edi\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps (%%edi)\n\t"
      "fstps 0x4(%%edi)\n\t"
      "fstps 0x8(%%edi)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x34, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001a2160_1\n\t"
      "movl 0x31fc3c, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "movl 0x31fc44, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, (%%edi)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edi)\n\t"
      ".LFUN_001a2160_1:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a2160_get), [norm] "m"(b1a2160_norm), [rots] "m"(b1a2160_rots)
      : "memory");
}
#else
#error "FUN_001a2160: clang naked draft required"
#endif


/* FUN_001a2290 (0x1a2290) — XBE naked draft (batch 60). */
#if defined(__clang__)
static void *(*const b1a2290_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a2290_tag)(int, int) = tag_get;
static void * (*const b1a2290_c18e450)(void) = game_globals_get;
static void *(*const b1a2290_elem)(void *, int, int) = tag_block_get_element;
static int (*const b1a2290_c2ace0)(int actor_handle, int a2, char param_3, float param_4, float *param_5) = actor_aim_jump;
static void (*const b1a2290_c1a0f10)(int unit_handle, int param_2, short index) = FUN_001a0f10;

__attribute__((naked, noinline))
char FUN_001a2290(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movb 0x424(%%esi), %%dl\n\t"
      "addl $0x10, %%esp\n\t"
      "xorb %%cl, %%cl\n\t"
      "testb $1, %%dl\n\t"
      "jne .LFUN_001a2290_9\n\t"
      "cmpw $1, 0x460(%%esi)\n\t"
      "je .LFUN_001a2290_9\n\t"
      "movl 0x3b4(%%eax), %%ecx\n\t"
      "movl 0x1c8(%%esi), %%eax\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "je .LFUN_001a2290_1\n\t"
      "pushl $0xf4\n\t"
      "pushl $0\n\t"
      "call *%[c18e450]\n\t"
      "addl $0x170, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "flds 0x3d4(%%esi)\n\t"
      "fmuls 0x84(%%eax)\n\t"
      "addl $0xc, %%esp\n\t"
      "fsubrs 0x2533c8\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".LFUN_001a2290_1:\n\t"
      "movb 0x5aa894, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a2290_2\n\t"
      "cmpl %%ebx, 0x1c8(%%esi)\n\t"
      "je .LFUN_001a2290_2\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x2533d8\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".LFUN_001a2290_2:\n\t"
      "leal 0x18(%%esi), %%ebx\n\t"
      "movl %%ebx, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x34(%%esi)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "fmuls 0x38(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x30(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fcoms -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a2290_3\n\t"
      "fsubrs -0x8(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x30(%%esi)\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x34(%%esi)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fmuls 0x38(%%esi)\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "jmp .LFUN_001a2290_4\n\t"
      ".LFUN_001a2290_3:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_001a2290_4:\n\t"
      "movl 0x1a8(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_001a2290_5\n\t"
      "movl 0x1a4(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001a2290_8\n\t"
      ".LFUN_001a2290_5:\n\t"
      "movb 0x253(%%esi), %%cl\n\t"
      "cmpb $0x27, %%cl\n\t"
      "je .LFUN_001a2290_6\n\t"
      "cmpb $0x28, %%cl\n\t"
      "movb $0, -0xc(%%ebp)\n\t"
      "jne .LFUN_001a2290_7\n\t"
      ".LFUN_001a2290_6:\n\t"
      "movb $1, -0xc(%%ebp)\n\t"
      ".LFUN_001a2290_7:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c2ace0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "je .LFUN_001a2290_10\n\t"
      ".LFUN_001a2290_8:\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl %%edx, (%%ebx)\n\t"
      "movl %%eax, 0x4(%%ebx)\n\t"
      "movl %%ecx, 0x8(%%ebx)\n\t"
      "movl 0x424(%%esi), %%ecx\n\t"
      "orl $1, %%ecx\n\t"
      "pushl $4\n\t"
      "pushl %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%ecx, 0x424(%%esi)\n\t"
      "movb $0, 0x45c(%%esi)\n\t"
      "movl $0xffffffff, 0x430(%%esi)\n\t"
      "call *%[c1a0f10]\n\t"
      "pushl $4\n\t"
      "pushl %%edi\n\t"
      "movl $1, %%ebx\n\t"
      "call *%[c1a0f10]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a2290_9:\n\t"
      "movb %%cl, %%al\n\t"
      ".LFUN_001a2290_10:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a2290_get), [tag] "m"(b1a2290_tag), [c18e450] "m"(b1a2290_c18e450), [elem] "m"(b1a2290_elem), [c2ace0] "m"(b1a2290_c2ace0), [c1a0f10] "m"(b1a2290_c1a0f10)
      : "memory");
}
#else
#error "FUN_001a2290: clang naked draft required"
#endif


/* FUN_001a2440 (0x1a2440) — XBE naked draft (batch 56). */
#if defined(__clang__)
static void *(*const b1a2440_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a2440_tag)(int, int) = tag_get;
static void *(*const b1a2440_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1a2440_c1a0f10)(int unit_handle, int param_2, short index) = FUN_001a0f10;

__attribute__((naked, noinline))
void FUN_001a2440(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movsbl 0x253(%%esi), %%eax\n\t"
      "addl $-2, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpl $5, %%eax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "ja .LFUN_001a2440_3\n\t"
      "jmp *.LFUN_001a2440_jt(,%%eax,4)\n\t"
      ".LFUN_001a2440_1:\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_001a2440_3\n\t"
      ".LFUN_001a2440_2:\n\t"
      "flds 0x230(%%esi)\n\t"
      "flds 0x22c(%%esi)\n\t"
      "flds 0x228(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fcomps 0x25337c\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jne .LFUN_001a2440_3\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_001a2440_3:\n\t"
      "cmpw $-1, 0x80(%%esi)\n\t"
      "je .LFUN_001a2440_8\n\t"
      "movl 0x7c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x616e7472\n\t"
      "call *%[tag]\n\t"
      "movswl 0x80(%%esi), %%edx\n\t"
      "pushl $0xb4\n\t"
      "pushl %%edx\n\t"
      "addl $0x74, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_001a2440_4\n\t"
      "cmpw $0, 0x82(%%esi)\n\t"
      "jne .LFUN_001a2440_8\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "call *%[c1a0f10]\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "movl $1, %%ebx\n\t"
      "call *%[c1a0f10]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_001a2440_8\n\t"
      ".LFUN_001a2440_4:\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_001a2440_8\n\t"
      "movb 0x40(%%eax), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .LFUN_001a2440_5\n\t"
      "movb 0x41(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_001a2440_8\n\t"
      ".LFUN_001a2440_5:\n\t"
      "movswl 0x82(%%esi), %%ecx\n\t"
      "movzbl %%dl, %%edx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jne .LFUN_001a2440_6\n\t"
      "xorb %%al, %%al\n\t"
      "jmp .LFUN_001a2440_7\n\t"
      ".LFUN_001a2440_6:\n\t"
      "movzbl 0x41(%%eax), %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jne .LFUN_001a2440_8\n\t"
      "movb $1, %%al\n\t"
      ".LFUN_001a2440_7:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testb %%al, %%al\n\t"
      "movb 0x257(%%esi), %%al\n\t"
      "setne %%bl\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpb $2, %%al\n\t"
      "sete %%cl\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a0f10]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001a2440_8:\n\t"
      "movsbl 0x42a(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_001a2440_9\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_001a2440_10\n\t"
      "movb $1, 0x45b(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a2440_9:\n\t"
      "movb 0x45b(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jle .LFUN_001a2440_11\n\t"
      "incb %%al\n\t"
      "cmpb $3, %%al\n\t"
      "movb %%al, 0x45b(%%esi)\n\t"
      "jle .LFUN_001a2440_11\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "call *%[c1a0f10]\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "movl $1, %%ebx\n\t"
      "call *%[c1a0f10]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_001a2440_10:\n\t"
      "movb $0, 0x45b(%%esi)\n\t"
      ".LFUN_001a2440_11:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_001a2440_jt:\n\t"
      ".long .LFUN_001a2440_1\n\t"
      ".long .LFUN_001a2440_1\n\t"
      ".long .LFUN_001a2440_2\n\t"
      ".long .LFUN_001a2440_2\n\t"
      ".long .LFUN_001a2440_2\n\t"
      ".long .LFUN_001a2440_2\n\t"
      ".text\n\t"
      :
      : [get] "m"(b1a2440_get), [tag] "m"(b1a2440_tag), [elem] "m"(b1a2440_elem), [c1a0f10] "m"(b1a2440_c1a0f10)
      : "memory");
}
#else
#error "FUN_001a2440: clang naked draft required"
#endif


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


/* FUN_001a2800 (0x1a2800) — XBE naked draft (batch 62). */
#if defined(__clang__)
static void *(*const b1a2800_get)(int, int) = object_get_and_verify_type;
static bool (*const b1a2800_c84a70)(float *a, float *b) = valid_real_normal3d_perpendicular;
static void *(*const b1a2800_tag)(int, int) = tag_get;
static const char * (*const b1a2800_c1ba1f0)(int tag_index) = tag_get_name;
static const char * (*const b1a2800_c19b0d0)(const char *tag_name) = tag_name_strip_path;
static char * (*const b1a2800_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b1a2800_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1a2800_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_001a2800(int unit_handle __attribute__((unused)), const char *failure_kind __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "leal 0x30(%%esi), %%edi\n\t"
      "leal 0x24(%%esi), %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c84a70]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a2800_6\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movb 0x424(%%esi), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $0x20, %%cl\n\t"
      "movl $0x2b4f4c, %%edx\n\t"
      "jne .LFUN_001a2800_1\n\t"
      "movl $0x25386f, %%edx\n\t"
      ".LFUN_001a2800_1:\n\t"
      "testb $4, 0xb6(%%esi)\n\t"
      "movl $0x2b4f44, %%ecx\n\t"
      "jne .LFUN_001a2800_2\n\t"
      "movl $0x25386f, %%ecx\n\t"
      ".LFUN_001a2800_2:\n\t"
      "movl 0x2f4(%%eax), %%eax\n\t"
      "testb $4, %%al\n\t"
      "je .LFUN_001a2800_3\n\t"
      "movl $0x266fa0, %%eax\n\t"
      "jmp .LFUN_001a2800_5\n\t"
      ".LFUN_001a2800_3:\n\t"
      "testb $2, %%al\n\t"
      "je .LFUN_001a2800_4\n\t"
      "movl $0x2b4f34, %%eax\n\t"
      "jmp .LFUN_001a2800_5\n\t"
      ".LFUN_001a2800_4:\n\t"
      "testb $0x40, %%al\n\t"
      "movl $0x2b4f2c, %%eax\n\t"
      "jne .LFUN_001a2800_5\n\t"
      "movl $0x26b188, %%eax\n\t"
      ".LFUN_001a2800_5:\n\t"
      "flds 0x38(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x55d\n\t"
      "pushl $0x2b4d5c\n\t"
      "subl $0x30, %%esp\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x34(%%esi)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c1ba1f0]\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b0d0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b4ee8\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x4c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a2800_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a2800_get), [c84a70] "m"(b1a2800_c84a70), [tag] "m"(b1a2800_tag), [c1ba1f0] "m"(b1a2800_c1ba1f0), [c19b0d0] "m"(b1a2800_c19b0d0), [c8d9d0] "m"(b1a2800_c8d9d0), [assert] "m"(b1a2800_assert), [exitfn] "m"(b1a2800_exitfn)
      : "memory");
}
#else
#error "FUN_001a2800: clang naked draft required"
#endif


/* FUN_001a2900 (0x1a2900) — XBE naked draft (batch 58). */
#if defined(__clang__)
static void *(*const b1a2900_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a2900_tag)(int, int) = tag_get;
static char (*const b1a2900_c1a0db0)(int biped_handle) = FUN_001a0db0;
static int *(*const b1a2900_gseed)(void) = get_global_random_seed_address;
static float (*const b1a2900_rrange)(int *, float, float) = random_real_range;
static void (*const b1a2900_cross)(float *, float *, float *) = cross_product3d;
static float (*const b1a2900_norm)(float *) = normalize3d;
static float (*const b1a2900_c121e0)(float min, float max) = FUN_000121e0;
static void (*const b1a2900_c10cc70)(float *output, float angle) = vector3d_from_angle;
static float *(*const b1a2900_vsca)(float *, float *, float, float *) = vector3d_scale_add;
static void (*const b1a2900_c1a2160)(int unit_handle) = FUN_001a2160;
static void (*const b1a2900_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1a2900_exitfn)(int) = system_exit;
static void (*const b1a2900_c1a2800)(int unit_handle, const char *failure_kind) = FUN_001a2800;

__attribute__((naked, noinline))
void FUN_001a2900(int unit_handle __attribute__((unused)), char *state __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c1a0db0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a2900_4\n\t"
      "movl 0x2f4(%%edi), %%eax\n\t"
      "movb $1, %%bl\n\t"
      "testb %%ah, %%bl\n\t"
      "je .LFUN_001a2900_4\n\t"
      "movb 0x253(%%esi), %%al\n\t"
      "cmpb $0x1f, %%al\n\t"
      "je .LFUN_001a2900_3\n\t"
      "cmpb $0x29, %%al\n\t"
      "je .LFUN_001a2900_3\n\t"
      "pushl $0x3db2b8c2\n\t"
      "pushl $0x3d567750\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds 0x38(%%esi)\n\t"
      "addl $0xc, %%esp\n\t"
      "fcomps 0x2533f0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a2900_1\n\t"
      "movl 0x31fc44, %%ecx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal 0x30(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[cross]\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x10, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001a2900_2\n\t"
      ".LFUN_001a2900_1:\n\t"
      "pushl $0x40c90fdb\n\t"
      "pushl $0\n\t"
      "call *%[c121e0]\n\t"
      "fstps 0x4(%%esp)\n\t"
      "addl $4, %%esp\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10cc70]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001a2900_2:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "leal 0x3c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[vsca]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_001a2900_3:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "call *%[c1a2160]\n\t"
      ".LFUN_001a2900_4:\n\t"
      "testb $1, 0x424(%%esi)\n\t"
      "jne .LFUN_001a2900_5\n\t"
      "pushl $1\n\t"
      "pushl $0xa61\n\t"
      "pushl $0x2b4d5c\n\t"
      "pushl $0x2b4f68\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a2900_5:\n\t"
      "movb 0x253(%%esi), %%al\n\t"
      "cmpb $0x27, %%al\n\t"
      "je .LFUN_001a2900_7\n\t"
      "cmpb $0x28, %%al\n\t"
      "je .LFUN_001a2900_7\n\t"
      "cmpb $0x14, %%al\n\t"
      "je .LFUN_001a2900_6\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_001a2900_8\n\t"
      ".LFUN_001a2900_6:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movb $0x14, (%%edx)\n\t"
      "jmp .LFUN_001a2900_8\n\t"
      ".LFUN_001a2900_7:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movb $0x28, (%%eax)\n\t"
      ".LFUN_001a2900_8:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x2b4f58\n\t"
      "call *%[c1a2800]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a2900_get), [tag] "m"(b1a2900_tag), [c1a0db0] "m"(b1a2900_c1a0db0), [gseed] "m"(b1a2900_gseed), [rrange] "m"(b1a2900_rrange), [cross] "m"(b1a2900_cross), [norm] "m"(b1a2900_norm), [c121e0] "m"(b1a2900_c121e0), [c10cc70] "m"(b1a2900_c10cc70), [vsca] "m"(b1a2900_vsca), [c1a2160] "m"(b1a2900_c1a2160), [assert] "m"(b1a2900_assert), [exitfn] "m"(b1a2900_exitfn), [c1a2800] "m"(b1a2900_c1a2800)
      : "memory");
}
#else
#error "FUN_001a2900: clang naked draft required"
#endif


/* FUN_001a2a60 (0x1a2a60) — readable C lift. */
void FUN_001a2a60(int unit_handle, char *state)
{
  extern char DAT_002b4f9c[];
  char *unit;
  unsigned char counter;
  unsigned char limit;

  unit = (char *)object_get_and_verify_type(unit_handle, 1);
  (void)tag_get(0x62697064, *(int *)unit); /* 'bipd' */
  counter = (unsigned char)(unit[0x428] + 1);
  limit = (unsigned char)unit[0x429];
  unit[0x428] = (char)counter;
  if (counter >= limit)
    *(int16_t *)(unit + 0x460) = -1;

  if (!cinematic_in_progress()) {
    if ((unsigned char)unit[0x428] == 2 ||
        (*(int16_t *)(unit + 0x460) == -1 &&
         (unsigned char)unit[0x429] < 2)) {
      FUN_001a0f10(unit_handle, 5, 0);
      FUN_001a0f10(unit_handle, 5, 1);
    }
  }

  *state = (char)((*(int16_t *)(unit + 0x460) == 1) ? 0x16 : 0x15);
  FUN_001a2800(unit_handle, DAT_002b4f9c);
}


/* FUN_001a2b10 (0x1a2b10) — readable C lift. */
void FUN_001a2b10(int unit_handle)
{
  extern char DAT_002b4fac[];
  char *unit;
  float x, y, z;

  unit = (char *)object_get_and_verify_type(unit_handle, 1);
  (void)tag_get(0x62697064, *(int *)unit); /* 'bipd' */
  if ((signed char)unit[0x45a] > 3) {
    x = *(float *)(unit + 0x18);
    y = *(float *)(unit + 0x1c);
    z = *(float *)(unit + 0x20);
    if (x * x + y * y + z * z > *(float *)0x25620c) {
      FUN_001a0f10(unit_handle, 2, 0);
      FUN_001a0f10(unit_handle, 2, 1);
    }
  }
  FUN_001a2800(unit_handle, DAT_002b4fac);
}


/* FUN_001a2b90 (0x1a2b90) — XBE naked draft (batch 55). */
#if defined(__clang__)
static void *(*const b1a2b90_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a2b90_tag)(int, int) = tag_get;
static char (*const b1a2b90_c1a2290)(int unit_handle) = (void *)FUN_001a2290;
static void *(*const b1a2b90_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static float (*const b1a2b90_c13070)(float *a, float *b) = FUN_00013070;
static float *(*const b1a2b90_vsca)(float *, float *, float, float *) = vector3d_scale_add;
static void (*const b1a2b90_v2fb0)(float *, float, float *) = FUN_00012fb0;
static void *(*const b1a2b90_memset)(void *, int, unsigned int) = csmemset;
static void (*const b1a2b90_cb9bc0)(short unit_index, float *rumble_def, float damage_amount, float scale) = rumble_player_impulse;

__attribute__((naked, noinline))
void FUN_001a2b90(int unit_handle /* @eax */ __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x50, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movb 0x424(%%esi), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $1, %%al\n\t"
      "jne .LFUN_001a2b90_2\n\t"
      "cmpw $1, 0x460(%%esi)\n\t"
      "je .LFUN_001a2b90_2\n\t"
      "movb 0x45c(%%esi), %%al\n\t"
      "cmpb $0x7f, %%al\n\t"
      "jge .LFUN_001a2b90_1\n\t"
      "incb %%al\n\t"
      "movb %%al, 0x45c(%%esi)\n\t"
      ".LFUN_001a2b90_1:\n\t"
      "testb $2, 0x1b8(%%esi)\n\t"
      "je .LFUN_001a2b90_2\n\t"
      "cmpb $5, 0x45c(%%esi)\n\t"
      "jle .LFUN_001a2b90_2\n\t"
      "call *%[c1a2290]\n\t"
      ".LFUN_001a2b90_2:\n\t"
      "movb 0x5aa891, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a2b90_11\n\t"
      "movl 0x1c8(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001a2b90_11\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x1b8(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "testb $8, %%ah\n\t"
      "je .LFUN_001a2b90_8\n\t"
      "testb $0x20, %%ah\n\t"
      "je .LFUN_001a2b90_8\n\t"
      "flds 0x20(%%esi)\n\t"
      "leal 0x18(%%esi), %%edi\n\t"
      "fmuls 0x1f4(%%esi)\n\t"
      "leal 0x1ec(%%esi), %%ebx\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      "faddp %%st(1)\n\t"
      "flds (%%edi)\n\t"
      "fmuls (%%ebx)\n\t"
      "faddp %%st(1)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a2b90_3\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_001a2b90_4\n\t"
      ".LFUN_001a2b90_3:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c13070]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001a2b90_4:\n\t"
      "flds 0x2b4fbc\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a2b90_5\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001a2b90_7\n\t"
      ".LFUN_001a2b90_5:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a2b90_6\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001a2b90_7\n\t"
      ".LFUN_001a2b90_6:\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".LFUN_001a2b90_7:\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "fchs\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[vsca]\n\t"
      "pushl %%edi\n\t"
      "pushl $0xbe4ccccc\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[vsca]\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x25bb0c\n\t"
      "addl $0x20, %%esp\n\t"
      "flds -0x4(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x2533e8\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fadds 0x25bb10\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[vsca]\n\t"
      "movl 0x424(%%esi), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "orl $1, %%eax\n\t"
      "movl %%eax, 0x424(%%esi)\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_001a2b90_9\n\t"
      ".LFUN_001a2b90_8:\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_001a2b90_9\n\t"
      "testb $1, 0x424(%%esi)\n\t"
      "je .LFUN_001a2b90_9\n\t"
      "addl $0x18, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0xbe4ccccc\n\t"
      "pushl %%esi\n\t"
      "call *%[v2fb0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001a2b90_9:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "cmpw $-1, 0x2(%%ecx)\n\t"
      "je .LFUN_001a2b90_10\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_001a2b90_10\n\t"
      "pushl $0x3c\n\t"
      "leal -0x50(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2(%%ecx), %%dx\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0x3f800000\n\t"
      "leal -0x50(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0x3f800000, -0x50(%%ebp)\n\t"
      "movl $0x3e99999a, -0x4c(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "movw $3, -0x48(%%ebp)\n\t"
      "call *%[cb9bc0]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_001a2b90_10:\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001a2b90_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [get] "m"(b1a2b90_get), [tag] "m"(b1a2b90_tag), [c1a2290] "m"(b1a2b90_c1a2290), [dget] "m"(b1a2b90_dget), [c13070] "m"(b1a2b90_c13070), [vsca] "m"(b1a2b90_vsca), [v2fb0] "m"(b1a2b90_v2fb0), [memset] "m"(b1a2b90_memset), [cb9bc0] "m"(b1a2b90_cb9bc0)
      : "memory");
}
#else
#error "FUN_001a2b90: clang naked draft required"
#endif


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

/* FUN_001a0db0 (0x1a0db0) — readable C lift. */
char FUN_001a0db0(int unit_handle)
{
  char *unit_obj; char *biped_tag;
  unit_obj = (char *)object_get_and_verify_type(unit_handle, 1);
  biped_tag = (char *)tag_get(0x62697064, *(int *)unit_obj);
  if (*(unsigned char *)(unit_obj + 0x459) > 3) {
    if ((*(unsigned char *)(biped_tag + 0x2f4) & 4) == 0 ||
        (*(unsigned char *)(unit_obj + 0xb6) & 4) != 0)
      return 1;
  }
  return 0;
}

/* FUN_001a4a50 (0x1a4a50) — readable C lift from XBE leaf. */
void FUN_001a4a50(int unit_handle)
{
  FUN_001a2800(unit_handle, (const char *)0x2b5160);
}

