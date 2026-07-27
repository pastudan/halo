/* units.c — unit lifecycle and query helpers.
 *
 * Corresponds to units.obj. Functions sorted by XBE address.
 */

#include "../../common.h"
#include "../../x87_math.h"

#define NUMBER_OF_UNIT_BASE_SEATS 6
#define NUMBER_OF_UNIT_BASE_WEAPONS 1
#define MAXIMUM_WEAPONS_PER_UNIT 4
#define MAXIMUM_COLLISION_USER_STACK_DEPTH 32

/* FUN_0008dc30 (0x8dc30) — XBE naked draft (batch 66). */
#if defined(__clang__)
static char (*const b8dc30_c92d60)(int16_t a1) = stack_walk;
static void (*const b8dc30_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b8dc30_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
char * FUN_0008dc30(char *destination __attribute__((unused)), const char *source __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_0008dc30_1\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_0008dc30_2\n\t"
      ".LFUN_0008dc30_1:\n\t"
      "pushl $0\n\t"
      "call *%[c92d60]\n\t"
      "pushl $0x267908\n\t"
      "pushl $0x122\n\t"
      "pushl $0x267878\n\t"
      "pushl $0x267834\n\t"
      "pushl $0x267810\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x20, %%esp\n\t"
      ".LFUN_0008dc30_2:\n\t"
      "movl %%esi, %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      ".LFUN_0008dc30_3:\n\t"
      "movb (%%eax), %%dl\n\t"
      "incl %%eax\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .LFUN_0008dc30_3\n\t"
      "subl %%ecx, %%eax\n\t"
      "decl %%edi\n\t"
      "movl %%ecx, %%esi\n\t"
      "leal 0x1(%%edi), %%edx\n\t"
      ".LFUN_0008dc30_4:\n\t"
      "movb 0x1(%%edi), %%cl\n\t"
      "incl %%edi\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_0008dc30_4\n\t"
      "movl %%eax, %%ecx\n\t"
      "shrl $2, %%ecx\n\t"
      "rep movsl\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep movsb\n\t"
      "popl %%edi\n\t"
      "movl %%edx, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c92d60] "m"(b8dc30_c92d60), [c8f390] "m"(b8dc30_c8f390), [exitfn] "m"(b8dc30_exitfn)
      : "memory");
}
#else
#error "FUN_0008dc30: clang naked draft required"
#endif


void FUN_00123470(void *mode_tag, void *animation, int animation_index,
                  void *out_matrix)
{
  uint8_t node_data[0x800];

  FUN_00121d60(mode_tag, animation, animation_index, node_data);
  component_vectors_from_normal3d(out_matrix, (float *)(node_data + 0x10),
                                  (float *)node_data);
}

/* FUN_001234b0 (0x1234b0) — XBE naked draft (batch 51). */
#if defined(__clang__)
static void (*const b1234b0_chkstk)(void) = FUN_001d90e0;
static void (*const b1234b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1234b0_exitfn)(int) = system_exit;
static void (*const b1234b0_c121d60)(void *mode_tag, void *animation, int animation_index, void *out_node_data) = FUN_00121d60;
static void *(*const b1234b0_elem)(void *, int, int) = tag_block_get_element;
static void *(*const b1234b0_tag)(int, int) = tag_get;
static void (*const b1234b0_c190a50)(void) = (void *)shader_type_is_valid_for_model;
static char (*const b1234b0_c1909d0)(int16_t shader_type) = shader_type_is_transparent;
static void (*const b1234b0_xfrmpt)(float *, float *, float *) = matrix_transform_point;
static void (*const b1234b0_c17cbd0)(int shader, int p2, int p3, int widget_handle, int p5, int p6, int zbuf_handle, float *position, int p9) = FUN_0017cbd0;
static void * (*const b1234b0_c1906b0)(void *shader, int shader_type) = FUN_001906b0;
static void (*const b1234b0_c17cbc0)(int shader, int p2, int p3, int widget_handle, int p5, int p6, int zbuf_handle) = FUN_0017cbc0;
static void (*const b1234b0_c17ccd0)(void *decal, int param_2, void *param_3, void *param_4) = FUN_0017ccd0;
static void (*const b1234b0_c17d2b0)(void) = FUN_0017d2b0;

__attribute__((naked, noinline))
void FUN_001234b0(void *mode_tag __attribute__((unused)), void *animation __attribute__((unused)), int frame_index __attribute__((unused)), float *out_delta __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x1000, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "cmpw $1, 0x22(%%ebx)\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jg .LFUN_001234b0_1\n\t"
      "pushl $1\n\t"
      "pushl $0xdd\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x291440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001234b0_1:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testw %%si, %%si\n\t"
      "jne .LFUN_001234b0_2\n\t"
      "movl $1, %%esi\n\t"
      ".LFUN_001234b0_2:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "leal -0x800(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c121d60]\n\t"
      "leal -0x1000(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "decl %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c121d60]\n\t"
      "flds -0x7f0(%%ebp)\n\t"
      "fsubs -0xff0(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "addl $0x20, %%esp\n\t"
      "popl %%edi\n\t"
      "fstps (%%eax)\n\t"
      "popl %%esi\n\t"
      "flds -0x7ec(%%ebp)\n\t"
      "popl %%ebx\n\t"
      "fsubs -0xfec(%%ebp)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "flds -0x7e8(%%ebp)\n\t"
      "fsubs -0xfe8(%%ebp)\n\t"
      "fstps 0x8(%%eax)\n\t"
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
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x228, %%esp\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x20(%%ebp), %%cl\n\t"
      "movb %%cl, %%al\n\t"
      "notb %%cl\n\t"
      "andb $1, %%al\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "andl $2, %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "jl .LFUN_001234b0_29\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jmp .LFUN_001234b0_3\n\t"
      "leal (%%esp), %%esp\n\t"
      "jmp .LFUN_001234b0_3\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_001234b0_3:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl 0xc4(%%edi), %%ecx\n\t"
      "leal 0xc4(%%edi), %%eax\n\t"
      "xorl %%esi, %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movl %%esi, -0x18(%%ebp)\n\t"
      "jle .LFUN_001234b0_28\n\t"
      ".LFUN_001234b0_4:\n\t"
      "pushl $0x4c\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movb (%%esi,%%ecx,1), %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpb $0xff, %%cl\n\t"
      "je .LFUN_001234b0_22\n\t"
      "movsbl %%cl, %%edx\n\t"
      "pushl $0x58\n\t"
      "pushl %%edx\n\t"
      "addl $0x40, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl 0x18(%%ebp), %%ecx\n\t"
      "movw 0x40(%%eax,%%ecx,2), %%ax\n\t"
      "movb 0x5aa250, %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_001234b0_22\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001234b0_22\n\t"
      "movswl %%ax, %%edx\n\t"
      "pushl $0x30\n\t"
      "pushl %%edx\n\t"
      "leal 0xd0(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "leal 0x24(%%eax), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "jle .LFUN_001234b0_22\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001234b0_6\n\t"
      ".LFUN_001234b0_5:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      ".LFUN_001234b0_6:\n\t"
      "pushl $0x68\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl 0x4(%%esi), %%ecx\n\t"
      "pushl $0x20\n\t"
      "pushl %%ecx\n\t"
      "leal 0xdc(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0xc(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x73686472\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x24(%%ebx), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c190a50]\n\t"
      "addl $0x24, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001234b0_21\n\t"
      "testb $1, (%%esi)\n\t"
      "jne .LFUN_001234b0_21\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x24(%%ebx), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1909d0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001234b0_14\n\t"
      "cmpw $2, -0xc(%%ebp)\n\t"
      "jne .LFUN_001234b0_21\n\t"
      "testb $2, 0x20(%%ebp)\n\t"
      "je .LFUN_001234b0_7\n\t"
      "pushl $1\n\t"
      "pushl $0x1ba\n\t"
      "pushl $0x291564\n\t"
      "pushl $0x291538\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001234b0_7:\n\t"
      "movw 0x8(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_001234b0_8\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl 0xb8(%%eax), %%edx\n\t"
      "jl .LFUN_001234b0_9\n\t"
      ".LFUN_001234b0_8:\n\t"
      "pushl $1\n\t"
      "pushl $0x1bd\n\t"
      "pushl $0x291564\n\t"
      "pushl $0x2914d8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001234b0_9:\n\t"
      "movw 0xa(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_001234b0_10\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movswl %%ax, %%ecx\n\t"
      "cmpl 0xb8(%%edx), %%ecx\n\t"
      "jl .LFUN_001234b0_11\n\t"
      ".LFUN_001234b0_10:\n\t"
      "pushl $1\n\t"
      "pushl $0x1be\n\t"
      "pushl $0x291564\n\t"
      "pushl $0x291470\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001234b0_11:\n\t"
      "movswl 0x8(%%esi), %%edx\n\t"
      "imull $0x34, %%edx, %%edx\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "leal 0x14(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl (%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[xfrmpt]\n\t"
      "movw 0x1c(%%ebp), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "movswl %%ax, %%eax\n\t"
      "jne .LFUN_001234b0_12\n\t"
      "movswl 0x10(%%edi), %%eax\n\t"
      ".LFUN_001234b0_12:\n\t"
      "movswl -0x8(%%ebp), %%edi\n\t"
      "shll $4, %%edi\n\t"
      "leal -0x228(%%ebp,%%edi,1), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x48(%%esi), %%edx\n\t"
      "pushl $-1\n\t"
      "leal 0x54(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $-1\n\t"
      "leal 0x44(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c17cbd0]\n\t"
      "addl $0x24, %%esp\n\t"
      "cmpw $0x20, -0x8(%%ebp)\n\t"
      "jge .LFUN_001234b0_21\n\t"
      "cmpw $-1, -0x220(%%ebp,%%edi,1)\n\t"
      "je .LFUN_001234b0_21\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001234b0_21\n\t"
      "movb 0x7(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jg .LFUN_001234b0_13\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jle .LFUN_001234b0_21\n\t"
      ".LFUN_001234b0_13:\n\t"
      "movw -0x10(%%ebp), %%dx\n\t"
      "movw %%dx, -0x21c(%%ebp,%%edi,1)\n\t"
      "movsbw 0x7(%%esi), %%ax\n\t"
      "movw %%ax, -0x21e(%%ebp,%%edi,1)\n\t"
      "incl -0x8(%%ebp)\n\t"
      "jmp .LFUN_001234b0_21\n\t"
      ".LFUN_001234b0_14:\n\t"
      "cmpw $4, 0x24(%%ebx)\n\t"
      "jne .LFUN_001234b0_17\n\t"
      "pushl $4\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1906b0]\n\t"
      "movb 0x28(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $8, %%cl\n\t"
      "je .LFUN_001234b0_17\n\t"
      "cmpw $1, -0xc(%%ebp)\n\t"
      "jne .LFUN_001234b0_21\n\t"
      "testb $2, 0x20(%%ebp)\n\t"
      "je .LFUN_001234b0_15\n\t"
      "pushl $1\n\t"
      "pushl $0x1eb\n\t"
      "pushl $0x291564\n\t"
      "pushl $0x291538\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001234b0_15:\n\t"
      "movw 0x1c(%%ebp), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "movswl %%ax, %%eax\n\t"
      "jne .LFUN_001234b0_16\n\t"
      "movswl 0x10(%%edi), %%eax\n\t"
      ".LFUN_001234b0_16:\n\t"
      "movl 0x48(%%esi), %%edx\n\t"
      "pushl $-1\n\t"
      "leal 0x54(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $-1\n\t"
      "addl $0x44, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c17cbc0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "jmp .LFUN_001234b0_21\n\t"
      ".LFUN_001234b0_17:\n\t"
      "cmpw $0, -0xc(%%ebp)\n\t"
      "jne .LFUN_001234b0_21\n\t"
      "testb $2, 0x20(%%ebp)\n\t"
      "movw 0x1c(%%ebp), %%ax\n\t"
      "je .LFUN_001234b0_19\n\t"
      "testw %%ax, %%ax\n\t"
      "movswl %%ax, %%eax\n\t"
      "jne .LFUN_001234b0_18\n\t"
      "movswl 0x10(%%edi), %%eax\n\t"
      ".LFUN_001234b0_18:\n\t"
      "leal 0x54(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $0x44, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c17ccd0]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_001234b0_21\n\t"
      ".LFUN_001234b0_19:\n\t"
      "testw %%ax, %%ax\n\t"
      "movswl %%ax, %%eax\n\t"
      "jne .LFUN_001234b0_20\n\t"
      "movswl 0x10(%%edi), %%eax\n\t"
      ".LFUN_001234b0_20:\n\t"
      "movl 0x48(%%esi), %%ecx\n\t"
      "pushl $-1\n\t"
      "leal 0x54(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "leal 0x44(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c17cbc0]\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17d2b0]\n\t"
      "addl $0x28, %%esp\n\t"
      ".LFUN_001234b0_21:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_001234b0_5\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      ".LFUN_001234b0_22:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl 0xc4(%%edi), %%ecx\n\t"
      "incl %%eax\n\t"
      "movswl %%ax, %%esi\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "leal 0xc4(%%edi), %%eax\n\t"
      "jl .LFUN_001234b0_4\n\t"
      "testw %%bx, %%bx\n\t"
      "jle .LFUN_001234b0_28\n\t"
      "leal -0x224(%%ebp), %%edx\n\t"
      "movzwl %%bx, %%esi\n\t"
      "nop\n\t"
      ".LFUN_001234b0_23:\n\t"
      "movw 0x6(%%edx), %%cx\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001234b0_24\n\t"
      "leal (%%esp), %%esp\n\t"
      "nop\n\t"
      ".LFUN_001234b0_24:\n\t"
      "movswl %%ax, %%edi\n\t"
      "shll $4, %%edi\n\t"
      "cmpw -0x21c(%%ebp,%%edi,1), %%cx\n\t"
      "jne .LFUN_001234b0_25\n\t"
      "testw %%cx, %%cx\n\t"
      "jg .LFUN_001234b0_26\n\t"
      ".LFUN_001234b0_25:\n\t"
      "incl %%eax\n\t"
      "cmpw %%bx, %%ax\n\t"
      "jl .LFUN_001234b0_24\n\t"
      "jmp .LFUN_001234b0_27\n\t"
      ".LFUN_001234b0_26:\n\t"
      "movl (%%edx), %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "movw -0x220(%%ebp,%%eax,1), %%di\n\t"
      "movw %%di, (%%ecx)\n\t"
      "movl -0x228(%%ebp,%%eax,1), %%eax\n\t"
      "movw 0x4(%%edx), %%cx\n\t"
      "movw %%cx, (%%eax)\n\t"
      ".LFUN_001234b0_27:\n\t"
      "addl $0x10, %%edx\n\t"
      "decl %%esi\n\t"
      "jne .LFUN_001234b0_23\n\t"
      ".LFUN_001234b0_28:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw -0x1c(%%ebp), %%ax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jle .LFUN_001234b0_3\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001234b0_29:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [chkstk] "m"(b1234b0_chkstk), [assert] "m"(b1234b0_assert), [exitfn] "m"(b1234b0_exitfn), [c121d60] "m"(b1234b0_c121d60), [elem] "m"(b1234b0_elem), [tag] "m"(b1234b0_tag), [c190a50] "m"(b1234b0_c190a50), [c1909d0] "m"(b1234b0_c1909d0), [xfrmpt] "m"(b1234b0_xfrmpt), [c17cbd0] "m"(b1234b0_c17cbd0), [c1906b0] "m"(b1234b0_c1906b0), [c17cbc0] "m"(b1234b0_c17cbc0), [c17ccd0] "m"(b1234b0_c17ccd0), [c17d2b0] "m"(b1234b0_c17d2b0)
      : "memory");
}
#else
#error "FUN_001234b0: clang naked draft required"
#endif


/* FUN_001a67b0 (0x1a67b0)
 *
 * Returns the animation state string for the given animation index (param_1)
 * and column (param_2, 0 or 1) from the global animation-name table at
 * 0x32d7c8. The table has 0xd1 rows of 2 char* pointers each.
 * Returns "<error>" if param_1 is out of range [0, 0xd0].
 *
 * Confirmed: MOVSX EAX,CX (sign-extends param_1); MOVZX ECX (zero-extends
 * param_2); LEA EDX,[ECX + EAX*2]; MOV EAX,[EDX*4 + 0x32d7c8].
 */
char *FUN_001a67b0(short param_1, unsigned char param_2)
{
  char *result;

  result = "<error>";
  if (param_1 >= 0 && param_1 < 0xd1) {
    result = ((char **)0x32d7c8)[(unsigned int)param_2 +
                                 (unsigned int)(short)param_1 * 2];
  }
  return result;
}


/* FUN_001a67e0 (0x1a67e0) — XBE naked draft (batch 69). */
#if defined(__clang__)
static int (*const b1a67e0_c8dcb0)(const char *s1, const char *s2) = csstrcmp;

__attribute__((naked, noinline))
short FUN_001a67e0(const char *param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_001a67e0_1:\n\t"
      "movswl %%si, %%eax\n\t"
      "movl 0x32d7c8(,%%eax,8), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8dcb0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001a67e0_2\n\t"
      "incl %%esi\n\t"
      "cmpw $0xd1, %%si\n\t"
      "jl .LFUN_001a67e0_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%bx, %%ax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a67e0_2:\n\t"
      "popl %%edi\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8dcb0] "m"(b1a67e0_c8dcb0)
      : "memory");
}
#else
#error "FUN_001a67e0: clang naked draft required"
#endif



/* FUN_001a6820 (0x1a6820) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b1a6820_elem)(void *, int, int) = tag_block_get_element;
static int (*const b1a6820_c19b120)(int *tag_ref) = verify_tag_reference;

__attribute__((naked, noinline))
int FUN_001a6820(int param_1 __attribute__((unused)), char param_2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x2a8(%%edx), %%eax\n\t"
      "setne %%cl\n\t"
      "addl $0x2a8, %%edx\n\t"
      "decl %%eax\n\t"
      "movswl %%cx, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jg .LFUN_001a6820_1\n\t"
      "movl %%ecx, %%eax\n\t"
      ".LFUN_001a6820_1:\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .LFUN_001a6820_2\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a6820_2:\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl $0x30\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b120]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b1a6820_elem), [c19b120] "m"(b1a6820_c19b120)
      : "memory");
}
#else
#error "FUN_001a6820: clang naked draft required"
#endif


/* FUN_001a6870 (0x1a6870) — XBE naked draft (batch 68). */
#if defined(__clang__)
static void *(*const b1a6870_elem)(void *, int, int) = tag_block_get_element;
static int (*const b1a6870_c19b120)(int *tag_ref) = verify_tag_reference;

__attribute__((naked, noinline))
int FUN_001a6870(int param_1 __attribute__((unused)), short param_2 __attribute__((unused)), char param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movswl 0xc(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0x11c\n\t"
      "pushl %%eax\n\t"
      "addl $0x2e4, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movb 0x10(%%ebp), %%dl\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%dl, %%dl\n\t"
      "setne %%cl\n\t"
      "leal 0xdc(%%eax), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "decl %%eax\n\t"
      "movswl %%cx, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jg .LFUN_001a6870_1\n\t"
      "movl %%ecx, %%eax\n\t"
      ".LFUN_001a6870_1:\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .LFUN_001a6870_2\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a6870_2:\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl $0x30\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b120]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b1a6870_elem), [c19b120] "m"(b1a6870_c19b120)
      : "memory");
}
#else
#error "FUN_001a6870: clang naked draft required"
#endif


/* FUN_001a6bc0 (0x1a6bc0)
 *
 * Returns non-zero if the unit's animation count field at offset 0x338
 * (a signed short) is greater than zero. Uses object_get_and_verify_type
 * with type_mask=3 (biped|vehicle).
 *
 * Confirmed: CALL 0x13d680 (object_get_and_verify_type) with type_mask=3;
 * CMP word ptr [EAX+0x338],CX (CX=0); SETG CL; MOV AL,CL.
 */
int FUN_001a6bc0(int param_1)
{
  char *unit;

  unit = (char *)object_get_and_verify_type(param_1, 3);
  return *(short *)(unit + 0x338) > 0;
}

/* FUN_001a6ca0 (0x1a6ca0)
 *
 * Returns the dialogue-category string for the given index (param_1) from the
 * global pointer table at 0x32de50. The table has 0xb entries (indices 0-10).
 * Returns "<error>" if param_1 is out of range.
 *
 * Confirmed: MOVSX EAX,CX (sign-extends param_1); MOV EAX,[EAX*4 + 0x32de50].
 */
char *FUN_001a6ca0(short param_1)
{
  char *result;

  result = "<error>";
  if (param_1 >= 0 && param_1 < 0xb) {
    result = ((char **)0x32de50)[(short)param_1];
  }
  return result;
}

/* FUN_001a6cd0 (0x1a6cd0) — readable C lift. */
int16_t FUN_001a6cd0(const char *name)
{
  int16_t i;

  for (i = 0; i < 0xb; i++) {
    if (csstrcmp(*(const char **)(0x32de50 + (int)i * 4), name) == 0)
      return i;
  }
  return 0;
}

/* FUN_001a6d10 (0x1a6d10) — XBE naked draft (batch 61). */
#if defined(__clang__)
static void *(*const b1a6d10_get)(int, int) = object_get_and_verify_type;
static int (*const b1a6d10_c1d9179)(char *str, size_t size, const char *format, ...) = snprintf;
static const char * (*const b1a6d10_c1ba1f0)(int tag_index) = tag_get_name;
static char * (*const b1a6d10_c1d95d0)(const char *str, int c) = crt_strchr;
static char * (*const b1a6d10_c1d9710)(const char *str, int c) = strrchr;
static char * (*const b1a6d10_c1a67b0)(short param_1, unsigned char param_2) = FUN_001a67b0;

__attribute__((naked, noinline))
char * FUN_001a6d10(int unit_handle __attribute__((unused)), char full_path __attribute__((unused)), int16_t max_len __attribute__((unused)), char *output __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, 0x338(%%edi)\n\t"
      "jne .LFUN_001a6d10_1\n\t"
      "movswl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "pushl $0x25ad08\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a6d10_1:\n\t"
      "movl 0x33c(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl $0x25ad08, %%esi\n\t"
      "je .LFUN_001a6d10_2\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ba1f0]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      ".LFUN_001a6d10_2:\n\t"
      "pushl %%ebx\n\t"
      "movb 0xc(%%ebp), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_001a6d10_4\n\t"
      "movl %%esi, %%eax\n\t"
      ".LFUN_001a6d10_3:\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001a6d10_5\n\t"
      "pushl $0x5c\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d95d0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001a6d10_5\n\t"
      "incl %%eax\n\t"
      "movl %%eax, %%esi\n\t"
      "jmp .LFUN_001a6d10_3\n\t"
      ".LFUN_001a6d10_4:\n\t"
      "pushl $0x5c\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9710]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001a6d10_5\n\t"
      "leal 0x1(%%eax), %%esi\n\t"
      ".LFUN_001a6d10_5:\n\t"
      "movw 0x33a(%%edi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .LFUN_001a6d10_6\n\t"
      "movswl 0x10(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "pushl $0x257984\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a6d10_6:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_001a6d10_7\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a67b0]\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "movswl 0x10(%%ebp), %%eax\n\t"
      "pushl $0x259f40\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a6d10_7:\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a67b0]\n\t"
      "movswl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x257984\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9179]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a6d10_get), [c1d9179] "m"(b1a6d10_c1d9179), [c1ba1f0] "m"(b1a6d10_c1ba1f0), [c1d95d0] "m"(b1a6d10_c1d95d0), [c1d9710] "m"(b1a6d10_c1d9710), [c1a67b0] "m"(b1a6d10_c1a67b0)
      : "memory");
}
#else
#error "FUN_001a6d10: clang naked draft required"
#endif


/* FUN_001a6e20 (0x1a6e20) — XBE naked draft (batch 57). */
#if defined(__clang__)
static void *(*const b1a6e20_get)(int, int) = object_get_and_verify_type;
static void (*const b1a6e20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1a6e20_exitfn)(int) = system_exit;
static void *(*const b1a6e20_tag)(int, int) = tag_get;
static char * (*const b1a6e20_c1a67b0)(short param_1, unsigned char param_2) = FUN_001a67b0;
static const char * (*const b1a6e20_c1ba1f0)(int tag_index) = tag_get_name;
static char * (*const b1a6e20_c1d9710)(const char *str, int c) = strrchr;
static void (*const b1a6e20_cff4d0)(int channel, const char *format, ...) = console_printf;

__attribute__((naked, noinline))
void FUN_001a6e20(int unit_handle __attribute__((unused)), void *speech_item __attribute__((unused)), short priority __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, %%esi\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "jne .LFUN_001a6e20_1\n\t"
      "pushl $1\n\t"
      "pushl $0x415\n\t"
      "pushl $0x2b66ec\n\t"
      "pushl $0x2b6778\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a6e20_1:\n\t"
      "movb 0x5aca56, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a6e20_6\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001a6e20_2\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a67b0]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "jmp .LFUN_001a6e20_4\n\t"
      ".LFUN_001a6e20_2:\n\t"
      "movl 0x4(%%esi), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_001a6e20_3\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ba1f0]\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl $0x5c\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9710]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001a6e20_4\n\t"
      "leal 0x1(%%eax), %%esi\n\t"
      "jmp .LFUN_001a6e20_4\n\t"
      ".LFUN_001a6e20_3:\n\t"
      "movl $0x25b724, %%esi\n\t"
      ".LFUN_001a6e20_4:\n\t"
      "cmpw $2, 0x8(%%ebp)\n\t"
      "movl $0x2b6770, %%eax\n\t"
      "je .LFUN_001a6e20_5\n\t"
      "movl $0x2b6768, %%eax\n\t"
      ".LFUN_001a6e20_5:\n\t"
      "movl 0x2c(%%edi), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl $0x2b6750\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a6e20_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a6e20_get), [assert] "m"(b1a6e20_assert), [exitfn] "m"(b1a6e20_exitfn), [tag] "m"(b1a6e20_tag), [c1a67b0] "m"(b1a6e20_c1a67b0), [c1ba1f0] "m"(b1a6e20_c1ba1f0), [c1d9710] "m"(b1a6e20_c1d9710), [cff4d0] "m"(b1a6e20_cff4d0)
      : "memory");
}
#else
#error "FUN_001a6e20: clang naked draft required"
#endif


/* FUN_001a6ef0 (0x1a6ef0) — XBE naked draft (batch 57). */
#if defined(__clang__)
static void *(*const b1a6ef0_get)(int, int) = object_get_and_verify_type;
static void (*const b1a6ef0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1a6ef0_exitfn)(int) = system_exit;
static void (*const b1a6ef0_c1a6e20)(int unit_handle, void *speech_item, short priority) = FUN_001a6e20;
static void *(*const b1a6ef0_tag)(int, int) = tag_get;
static short (*const b1a6ef0_cfff80)(void) = game_connection;

__attribute__((naked, noinline))
void FUN_001a6ef0(int actor __attribute__((unused)), short count __attribute__((unused)), void *comm_buf __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "jne .LFUN_001a6ef0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x12e\n\t"
      "pushl $0x2b66ec\n\t"
      "pushl $0x2b6778\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a6ef0_1:\n\t"
      "testb $4, 0xb6(%%ebx)\n\t"
      "je .LFUN_001a6ef0_2\n\t"
      "cmpw $0xa, (%%edi)\n\t"
      "jne .LFUN_001a6ef0_11\n\t"
      ".LFUN_001a6ef0_2:\n\t"
      "movw 0xc(%%ebp), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .LFUN_001a6ef0_9\n\t"
      "cmpw $0, 0x338(%%ebx)\n\t"
      "leal 0x338(%%ebx), %%edi\n\t"
      "jle .LFUN_001a6ef0_3\n\t"
      "movb 0x3a4(%%ebx), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_001a6ef0_3\n\t"
      "pushl $2\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c1a6e20]\n\t"
      "movw 0xc(%%ebp), %%ax\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001a6ef0_3:\n\t"
      "cmpw $3, %%ax\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl $0xc, %%ecx\n\t"
      "rep movsl\n\t"
      "jne .LFUN_001a6ef0_5\n\t"
      "cmpw $0, 0x368(%%ebx)\n\t"
      "leal 0x368(%%ebx), %%esi\n\t"
      "jle .LFUN_001a6ef0_5\n\t"
      "cmpl %%esi, 0x10(%%ebp)\n\t"
      "je .LFUN_001a6ef0_4\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $1\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c1a6e20]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001a6ef0_4:\n\t"
      "movw $0, (%%esi)\n\t"
      ".LFUN_001a6ef0_5:\n\t"
      "movw 0x340(%%ebx), %%ax\n\t"
      "movw 0x344(%%ebx), %%cx\n\t"
      "movw 0x342(%%ebx), %%dx\n\t"
      "movw %%ax, 0x3a8(%%ebx)\n\t"
      "movl 0x33c(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movb $0, 0x3a4(%%ebx)\n\t"
      "movb $0, 0x3a5(%%ebx)\n\t"
      "movb $0, 0x3a6(%%ebx)\n\t"
      "movl $0xffffffff, 0x3b0(%%ebx)\n\t"
      "movw %%cx, 0x3ae(%%ebx)\n\t"
      "movw %%dx, 0x3ac(%%ebx)\n\t"
      "je .LFUN_001a6ef0_6\n\t"
      "pushl %%eax\n\t"
      "pushl $0x736e6421\n\t"
      "call *%[tag]\n\t"
      "movl 0x84(%%eax), %%ecx\n\t"
      "imull $0x1e, %%ecx, %%ecx\n\t"
      "movl $0x10624dd3, %%eax\n\t"
      "imull %%ecx\n\t"
      "sarl $6, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "popl %%edi\n\t"
      "addl %%eax, %%edx\n\t"
      "popl %%esi\n\t"
      "movw %%dx, 0x3aa(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a6ef0_6:\n\t"
      "call *%[cfff80]\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_001a6ef0_7\n\t"
      "movb 0x5ac9cd, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a6ef0_8\n\t"
      ".LFUN_001a6ef0_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x168\n\t"
      "pushl $0x2b66ec\n\t"
      "pushl $0x2b67bc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a6ef0_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0x2d, 0x3aa(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a6ef0_9:\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .LFUN_001a6ef0_11\n\t"
      "cmpw $0, 0x338(%%ebx)\n\t"
      "jg .LFUN_001a6ef0_10\n\t"
      "pushl $1\n\t"
      "pushl $0x16e\n\t"
      "pushl $0x2b66ec\n\t"
      "pushl $0x2b6784\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a6ef0_10:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "leal 0x368(%%ebx), %%edi\n\t"
      "movl $0xc, %%ecx\n\t"
      "rep movsl\n\t"
      ".LFUN_001a6ef0_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a6ef0_get), [assert] "m"(b1a6ef0_assert), [exitfn] "m"(b1a6ef0_exitfn), [c1a6e20] "m"(b1a6ef0_c1a6e20), [tag] "m"(b1a6ef0_tag), [cfff80] "m"(b1a6ef0_cfff80)
      : "memory");
}
#else
#error "FUN_001a6ef0: clang naked draft required"
#endif


/* FUN_001a71c0 (0x1a71c0) — XBE naked draft (batch 52). */
#if defined(__clang__)
static void *(*const b1a71c0_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a71c0_tag)(int, int) = tag_get;
static void *(*const b1a71c0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int *(*const b1a71c0_gseed)(void) = get_global_random_seed_address;
static float (*const b1a71c0_rmreal)(unsigned int *) = random_math_real;
static short (*const b1a71c0_c1a68d0)(int unit_handle, short priority, char param_3, char param_4, int *param_5, short *vocalization_type_ref, int *sound_definition_index_ref) = FUN_001a68d0;
static void *(*const b1a71c0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b1a71c0_c42d20)(void *packet) = ai_communication_packet_new;
static void (*const b1a71c0_c1a6ef0)(int actor, short count, void *comm_buf) = FUN_001a6ef0;
static void (*const b1a71c0_c40860)(int unit_handle, int effect_type, int priority) = ai_handle_unit_effect;

__attribute__((naked, noinline))
char FUN_001a71c0(int unit_handle __attribute__((unused)), int *param_2 __attribute__((unused)), char param_3 __attribute__((unused)), char param_4 __attribute__((unused)), float param_5 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x44, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x334(%%edi), %%ecx\n\t"
      "xorb %%al, %%al\n\t"
      "orl $0xffffffff, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "je .LFUN_001a71c0_25\n\t"
      "flds 0xa8(%%edi)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "fcomps 0x2533c0\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001a71c0_1\n\t"
      "movb %%cl, -0x2(%%ebp)\n\t"
      ".LFUN_001a71c0_1:\n\t"
      "flds 0xa8(%%edi)\n\t"
      "movb $1, -0x3(%%ebp)\n\t"
      "fcomps 0x253f3c\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_001a71c0_2\n\t"
      "movb $0, -0x3(%%ebp)\n\t"
      ".LFUN_001a71c0_2:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "je .LFUN_001a71c0_3\n\t"
      "movl (%%esi), %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "je .LFUN_001a71c0_3\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6a707421\n\t"
      "call *%[tag]\n\t"
      "movw 0x1c6(%%eax), %%cx\n\t"
      "addl $8, %%esp\n\t"
      "movw %%cx, -0x8(%%ebp)\n\t"
      ".LFUN_001a71c0_3:\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a71c0_14\n\t"
      "movl 0x1a8(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001a71c0_4\n\t"
      "movl %%eax, %%edi\n\t"
      "jmp .LFUN_001a71c0_5\n\t"
      ".LFUN_001a71c0_4:\n\t"
      "movl 0x1a4(%%edi), %%edi\n\t"
      ".LFUN_001a71c0_5:\n\t"
      "movl (%%esi), %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpl $-1, %%eax\n\t"
      "movb %%bl, -0x2(%%ebp)\n\t"
      "je .LFUN_001a71c0_6\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6a707421\n\t"
      "call *%[tag]\n\t"
      "flds 0x1f4(%%eax)\n\t"
      "fcomps 0x253f40\n\t"
      "addl $8, %%esp\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_001a71c0_6\n\t"
      "movb %%bl, -0x2(%%ebp)\n\t"
      ".LFUN_001a71c0_6:\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_001a71c0_7\n\t"
      "movl 0x6325a4, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $3, 0x6e(%%eax)\n\t"
      "setge %%bl\n\t"
      "jmp .LFUN_001a71c0_8\n\t"
      ".LFUN_001a71c0_7:\n\t"
      "flds 0x18(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "fadds 0x2549d4\n\t"
      "fcomps 0xa8(%%eax)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a71c0_8\n\t"
      "movb $1, %%bl\n\t"
      ".LFUN_001a71c0_8:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .LFUN_001a71c0_9\n\t"
      "movl $0x10, %%eax\n\t"
      "jmp .LFUN_001a71c0_13\n\t"
      ".LFUN_001a71c0_9:\n\t"
      "cmpw $7, %%ax\n\t"
      "jne .LFUN_001a71c0_10\n\t"
      "movl $0x11, %%eax\n\t"
      "jmp .LFUN_001a71c0_13\n\t"
      ".LFUN_001a71c0_10:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a71c0_11\n\t"
      "movl $0x13, %%eax\n\t"
      "jmp .LFUN_001a71c0_13\n\t"
      ".LFUN_001a71c0_11:\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_001a71c0_12\n\t"
      "movl $0xe, %%eax\n\t"
      "jmp .LFUN_001a71c0_13\n\t"
      ".LFUN_001a71c0_12:\n\t"
      "movb 0x14(%%ebp), %%al\n\t"
      "negb %%al\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $3, %%eax\n\t"
      "addl $0xf, %%eax\n\t"
      ".LFUN_001a71c0_13:\n\t"
      "cmpw $0xe, %%ax\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movb $1, %%bl\n\t"
      "je .LFUN_001a71c0_18\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw $0x12, %%ax\n\t"
      "setne %%cl\n\t"
      "movl $2, -0x10(%%ebp)\n\t"
      "decl %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "jmp .LFUN_001a71c0_18\n\t"
      ".LFUN_001a71c0_14:\n\t"
      "cmpw $0, 0x39e(%%edi)\n\t"
      "jne .LFUN_001a71c0_24\n\t"
      "cmpw $1, -0x8(%%ebp)\n\t"
      "jne .LFUN_001a71c0_15\n\t"
      "movb $1, %%bl\n\t"
      "movl $9, -0x8(%%ebp)\n\t"
      "jmp .LFUN_001a71c0_19\n\t"
      ".LFUN_001a71c0_15:\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a71c0_16\n\t"
      "movb $1, %%bl\n\t"
      "movl $7, -0x8(%%ebp)\n\t"
      "jmp .LFUN_001a71c0_19\n\t"
      ".LFUN_001a71c0_16:\n\t"
      "cmpw $0, 0x39c(%%edi)\n\t"
      "jne .LFUN_001a71c0_24\n\t"
      "cmpw $3, 0x39a(%%edi)\n\t"
      "jge .LFUN_001a71c0_24\n\t"
      "cmpw $0, 0x338(%%edi)\n\t"
      "je .LFUN_001a71c0_17\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fcomps 0x253524\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a71c0_24\n\t"
      ".LFUN_001a71c0_17:\n\t"
      "movb -0x2(%%ebp), %%cl\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "sete %%al\n\t"
      "leal 0x6(%%eax,%%eax,1), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".LFUN_001a71c0_18:\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001a71c0_23\n\t"
      ".LFUN_001a71c0_19:\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl $0xffffffff, -0xc(%%ebp)\n\t"
      "je .LFUN_001a71c0_20\n\t"
      "movl $0xa, %%ebx\n\t"
      "jmp .LFUN_001a71c0_21\n\t"
      ".LFUN_001a71c0_20:\n\t"
      "negb %%bl\n\t"
      "sbbl %%ebx, %%ebx\n\t"
      "andl $5, %%ebx\n\t"
      "addl $2, %%ebx\n\t"
      ".LFUN_001a71c0_21:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1a68d0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x5ac9ca, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a71c0_23\n\t"
      "testw %%si, %%si\n\t"
      "jle .LFUN_001a71c0_23\n\t"
      "pushl $0x30\n\t"
      "leal -0x44(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "movw -0x8(%%ebp), %%ax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movw %%bx, -0x44(%%ebp)\n\t"
      "movw %%ax, -0x42(%%ebp)\n\t"
      "movl %%ecx, -0x40(%%ebp)\n\t"
      "movw $7, -0x38(%%ebp)\n\t"
      "call *%[c42d20]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x44(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1a6ef0]\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "je .LFUN_001a71c0_22\n\t"
      "movw $0x3c, 0x39e(%%edi)\n\t"
      "jmp .LFUN_001a71c0_23\n\t"
      ".LFUN_001a71c0_22:\n\t"
      "incw 0x39a(%%edi)\n\t"
      "movw $0x1e, 0x39c(%%edi)\n\t"
      "movw $0x16, 0x398(%%edi)\n\t"
      ".LFUN_001a71c0_23:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001a71c0_24\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c40860]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001a71c0_24:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001a71c0_25:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [get] "m"(b1a71c0_get), [tag] "m"(b1a71c0_tag), [dget] "m"(b1a71c0_dget), [gseed] "m"(b1a71c0_gseed), [rmreal] "m"(b1a71c0_rmreal), [c1a68d0] "m"(b1a71c0_c1a68d0), [memset] "m"(b1a71c0_memset), [c42d20] "m"(b1a71c0_c42d20), [c1a6ef0] "m"(b1a71c0_c1a6ef0), [c40860] "m"(b1a71c0_c40860)
      : "memory");
}
#else
#error "FUN_001a71c0: clang naked draft required"
#endif


/* FUN_001a74d0 (0x1a74d0) — XBE naked draft (batch 59). */
#if defined(__clang__)
static void *(*const b1a74d0_get)(int, int) = object_get_and_verify_type;
static void (*const b1a74d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1a74d0_exitfn)(int) = system_exit;
static int *(*const b1a74d0_gseed)(void) = get_global_random_seed_address;
static float (*const b1a74d0_rmreal)(unsigned int *) = random_math_real;
static void *(*const b1a74d0_tag)(int, int) = tag_get;
static short (*const b1a74d0_c1a68d0)(int unit_handle, short priority, char param_3, char param_4, int *param_5, short *vocalization_type_ref, int *sound_definition_index_ref) = FUN_001a68d0;
static void *(*const b1a74d0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b1a74d0_c42d20)(void *packet) = ai_communication_packet_new;
static void (*const b1a74d0_c1a6ef0)(int actor, short count, void *comm_buf) = FUN_001a6ef0;

__attribute__((naked, noinline))
char FUN_001a74d0(int unit_handle __attribute__((unused)), int scream_type __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x34, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movw 0xc(%%ebp), %%si\n\t"
      "addl $8, %%esp\n\t"
      "testw %%si, %%si\n\t"
      "movl %%eax, %%ebx\n\t"
      "jl .LFUN_001a74d0_1\n\t"
      "cmpw $6, %%si\n\t"
      "jl .LFUN_001a74d0_2\n\t"
      ".LFUN_001a74d0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x257\n\t"
      "pushl $0x2b66ec\n\t"
      "pushl $0x2b6830\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a74d0_2:\n\t"
      "movswl %%si, %%eax\n\t"
      "cmpl $5, %%eax\n\t"
      "ja .LFUN_001a74d0_9\n\t"
      "jmp *.LFUN_001a74d0_jt(,%%eax,4)\n\t"
      ".LFUN_001a74d0_3:\n\t"
      "movl $0xa, 0xc(%%ebp)\n\t"
      "jmp .LFUN_001a74d0_10\n\t"
      ".LFUN_001a74d0_4:\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fcomps 0x253398\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a74d0_5\n\t"
      "movl $0x27, 0xc(%%ebp)\n\t"
      "jmp .LFUN_001a74d0_10\n\t"
      ".LFUN_001a74d0_5:\n\t"
      "movl $0xb, 0xc(%%ebp)\n\t"
      "jmp .LFUN_001a74d0_10\n\t"
      ".LFUN_001a74d0_6:\n\t"
      "movl $0xc, 0xc(%%ebp)\n\t"
      "jmp .LFUN_001a74d0_10\n\t"
      ".LFUN_001a74d0_7:\n\t"
      "movl $0xd, 0xc(%%ebp)\n\t"
      "jmp .LFUN_001a74d0_10\n\t"
      ".LFUN_001a74d0_8:\n\t"
      "movl $0xb7, 0xc(%%ebp)\n\t"
      "jmp .LFUN_001a74d0_10\n\t"
      ".LFUN_001a74d0_9:\n\t"
      "pushl $1\n\t"
      "pushl $0x27b\n\t"
      "pushl $0x2b66ec\n\t"
      "pushl $0x255ee8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a74d0_10:\n\t"
      "movl 0x334(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001a74d0_11\n\t"
      "pushl %%eax\n\t"
      "pushl $0x75646c67\n\t"
      "call *%[tag]\n\t"
      "movswl 0xc(%%ebp), %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "movl 0x1c(%%ecx,%%eax,1), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LFUN_001a74d0_11\n\t"
      "leal -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $9\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a68d0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "testw %%si, %%si\n\t"
      "jle .LFUN_001a74d0_11\n\t"
      "pushl $0x30\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "movw 0xc(%%ebp), %%dx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movw $9, -0x34(%%ebp)\n\t"
      "movw %%dx, -0x32(%%ebp)\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movw $7, -0x28(%%ebp)\n\t"
      "call *%[c42d20]\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a6ef0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a74d0_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_001a74d0_jt:\n\t"
      ".long .LFUN_001a74d0_3\n\t"
      ".long .LFUN_001a74d0_4\n\t"
      ".long .LFUN_001a74d0_5\n\t"
      ".long .LFUN_001a74d0_6\n\t"
      ".long .LFUN_001a74d0_7\n\t"
      ".long .LFUN_001a74d0_8\n\t"
      ".text\n\t"
      :
      : [get] "m"(b1a74d0_get), [assert] "m"(b1a74d0_assert), [exitfn] "m"(b1a74d0_exitfn), [gseed] "m"(b1a74d0_gseed), [rmreal] "m"(b1a74d0_rmreal), [tag] "m"(b1a74d0_tag), [c1a68d0] "m"(b1a74d0_c1a68d0), [memset] "m"(b1a74d0_memset), [c42d20] "m"(b1a74d0_c42d20), [c1a6ef0] "m"(b1a74d0_c1a6ef0)
      : "memory");
}
#else
#error "FUN_001a74d0: clang naked draft required"
#endif


/* FUN_001a7650 (0x1a7650) — XBE naked draft (batch 62). */
#if defined(__clang__)
static void *(*const b1a7650_elem)(void *, int, int) = tag_block_get_element;
static int *(*const b1a7650_gseed)(void) = get_global_random_seed_address;
static int16_t (*const b1a7650_c10b2d0)(unsigned int *seed, int16_t min, int16_t max) = random_range;
static void *(*const b1a7650_tag)(int, int) = tag_get;
static void (*const b1a7650_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1a7650_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
int FUN_001a7650(void *tag_data __attribute__((unused)), int dialogue_type __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl 0x2b4(%%esi), %%ecx\n\t"
      "addl $0x2b4, %%esi\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .LFUN_001a7650_8\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001a7650_1:\n\t"
      "pushl $0x18\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "movw 0x8(%%ebp), %%cx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .LFUN_001a7650_2\n\t"
      "cmpw %%cx, (%%eax)\n\t"
      "jne .LFUN_001a7650_3\n\t"
      ".LFUN_001a7650_2:\n\t"
      "movswl %%bx, %%eax\n\t"
      "movw %%di, -0x20(%%ebp,%%eax,2)\n\t"
      "incl %%ebx\n\t"
      ".LFUN_001a7650_3:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_001a7650_1\n\t"
      "testw %%bx, %%bx\n\t"
      "jle .LFUN_001a7650_7\n\t"
      "cmpw $1, %%bx\n\t"
      "jne .LFUN_001a7650_4\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "jmp .LFUN_001a7650_5\n\t"
      ".LFUN_001a7650_4:\n\t"
      "pushl %%ebx\n\t"
      "pushl $0\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[c10b2d0]\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movw -0x20(%%ebp,%%ecx,2), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001a7650_5:\n\t"
      "movswl %%ax, %%edx\n\t"
      "pushl $0x18\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "movl 0x14(%%eax), %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0x75646c67\n\t"
      "call *%[tag]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001a7650_6\n\t"
      "pushl $1\n\t"
      "pushl $0x408\n\t"
      "pushl $0x2b66ec\n\t"
      "pushl $0x2b6874\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a7650_6:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a7650_7:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      ".LFUN_001a7650_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b1a7650_elem), [gseed] "m"(b1a7650_gseed), [c10b2d0] "m"(b1a7650_c10b2d0), [tag] "m"(b1a7650_tag), [assert] "m"(b1a7650_assert), [exitfn] "m"(b1a7650_exitfn)
      : "memory");
}
#else
#error "FUN_001a7650: clang naked draft required"
#endif


/* FUN_001a7730 (0x1a7730) — XBE naked draft (batch 68). */
#if defined(__clang__)
static void *(*const b1a7730_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a7730_tag)(int, int) = tag_get;
static int (*const b1a7730_c1a7650)(void *tag_data, int dialogue_type) = FUN_001a7650;

__attribute__((naked, noinline))
void FUN_001a7730(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6e(%%esi), %%ax\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_001a7730_1\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c1a7650]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_001a7730_2\n\t"
      ".LFUN_001a7730_1:\n\t"
      "pushl $0\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c1a7650]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_001a7730_2\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c1a7650]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001a7730_2:\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x334(%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a7730_get), [tag] "m"(b1a7730_tag), [c1a7650] "m"(b1a7730_c1a7650)
      : "memory");
}
#else
#error "FUN_001a7730: clang naked draft required"
#endif


/* unit_set_actively_controlled_flag (0x1a7f80)
 *
 * Sets bit 5 (0x20) of the byte at object_data_t+0xb6 (offset 182,
 * the byte just before unk_183) on the resolved unit object.
 * Distinct from unit_delete (0x1a7fc0) which sets the same bit at
 * offset 0xb7 (unk_183).
 *
 * Confirmed: CALL 0x13d680 with type_mask=3 (biped|vehicle).
 * Confirmed: OR byte ptr [EAX+0xb6],0x20.
 */
void unit_set_actively_controlled_flag(int unit_handle)
{
  object_data_t *obj;

  obj = (object_data_t *)object_get_and_verify_type(unit_handle, 3);
  *(uint8_t *)((char *)obj + 0xb6) |= 0x20;
}

/* unit_delete (0x1a7fc0)
 *
 * Marks a unit object for deletion by setting bit 5 (0x20) of the
 * object flags byte at object_data_t.unk_183 (offset 0xB7). The
 * actual object destruction happens later during the object system's
 * garbage-collection pass. Resolves handle via
 * object_get_and_verify_type with type mask 3 (biped | vehicle).
 */
void unit_delete(int datum_handle)
{
  object_data_t *obj;

  obj = (object_data_t *)object_get_and_verify_type(datum_handle, 3);
  obj->unk_183 |= 0x20;
}

/* units_update (0x1a7ff0)
 *
 * Per-tick global update for the units subsystem. Reads the units globals
 * pointer at 0x4e4cf8 (a small {int16_t, int16_t, uint8_t} struct) and
 * rotates: copies the "max ticks this frame" (offset +2) into "current
 * ticks" (offset +0), then zeroes the max-ticks field (+2) and the
 * ready-flag byte (+4). Called once per game tick from the main update loop.
 */
void units_update(void)
{
  int16_t *p = *(int16_t **)0x4e4cf8;

  p[0] = p[1];
  p[1] = 0;
  *(uint8_t *)&p[2] = 0;
}

/* unit_persistent_control (0x1a8190)
 *
 * Sets persistent control state on a unit. Stores animation_ticks at offset
 * 0x1c0 and control_flags at offset 0x1c4. Asserts if control_flags has any
 * bits set beyond position 14 (NUMBER_OF_UNIT_CONTROL_FLAGS = 15).
 */
void unit_persistent_control(int unit_handle, int animation_ticks,
                             int control_flags)
{
  char *unit = (char *)object_get_and_verify_type(unit_handle, 3);

  if ((control_flags & 0xffff8000) != 0) {
    display_assert(
      "VALID_FLAGS(persistent_control_flags, NUMBER_OF_UNIT_CONTROL_FLAGS)",
      "c:\\halo\\SOURCE\\units\\units.c", 0x605, 1);
    system_exit(-1);
  }

  *(int *)(unit + 0x1c4) = control_flags;
  *(int *)(unit + 0x1c0) = animation_ticks;
}

int unit_get_seat_enter_position(int unit_handle, int target_unit_handle,
                                 int16_t seat_index, float *out_pos_a,
                                 float *out_pos_b, float *out_pos_c)
{
  char marker_name[256];
  uint8_t hint_marker_data[0x6c];
  uint8_t mode_matrix[0x34];
  uint8_t enter_position_matrix[0x34];
  uint8_t seat_marker_data[0xa0];
  char *unit = (char *)object_get_and_verify_type(unit_handle, 3);
  char *unit_tag = (char *)tag_get(0x756e6974, *(int *)unit);
  void *mode_tag = (void *)tag_get(0x6d6f6465, *(int *)(unit_tag + 0x34));
  char *antr_tag = (char *)tag_get(0x616e7472, *(int *)(unit_tag + 0x44));
  char *target_unit = (char *)object_get_and_verify_type(target_unit_handle, 3);
  char *target_unit_tag = (char *)tag_get(0x756e6974, *(int *)target_unit);
  char *seat = (char *)tag_block_get_element(target_unit_tag + 0x2e4,
                                             (int)seat_index, 0x11c);
  int *mode_block = (int *)(antr_tag + 0xc);
  int16_t mode_index = 0;

  while ((int)mode_index < *mode_block) {
    char *mode =
      (char *)tag_block_get_element(mode_block, (int)mode_index, 0x64);

    if (crt_stricmp(mode, seat + 4) == 0) {
      if (*(int *)(mode + 0x40) < 8) {
        return 0;
      }

      mode_index = *(int16_t *)(*(int *)(mode + 0x44) + 0xe);
      if (mode_index == -1) {
        return 0;
      }

      mode =
        (char *)tag_block_get_element(antr_tag + 0x74, (int)mode_index, 0xb4);
      object_get_markers_by_string_id(target_unit_handle, seat + 0x24,
                                      seat_marker_data, 1);
      FUN_00123470(mode_tag, mode, 0, mode_matrix);
      matrix4x3_multiply((float *)(seat_marker_data + 0x38),
                         (float *)mode_matrix, (float *)enter_position_matrix);
      csstrcpy(marker_name, seat + 0x24);
      FUN_0008dc30(marker_name, " enter-hint");
      object_get_markers_by_string_id(target_unit_handle, marker_name,
                                      hint_marker_data, 1);

      if (out_pos_b != NULL) {
        out_pos_b[0] = *(float *)(seat_marker_data + 0x60);
        out_pos_b[1] = *(float *)(seat_marker_data + 0x64);
        out_pos_b[2] = *(float *)(seat_marker_data + 0x68);
      }

      if (out_pos_a != NULL) {
        out_pos_a[0] = *(float *)(enter_position_matrix + 0x28);
        out_pos_a[1] = *(float *)(enter_position_matrix + 0x2c);
        out_pos_a[2] = *(float *)(enter_position_matrix + 0x30);
      }

      if (out_pos_c != NULL) {
        out_pos_c[0] = *(float *)(hint_marker_data + 0x60);
        out_pos_c[1] = *(float *)(hint_marker_data + 0x64);
        out_pos_c[2] = *(float *)(hint_marker_data + 0x68);
      }

      return 1;
    }

    mode_index += 1;
  }

  return 0;
}

/* FUN_001a8550 (0x1a8550) — XBE naked draft (batch 61). */
#if defined(__clang__)


__attribute__((naked, noinline))
char FUN_001a8550(void *plan __attribute__((unused)), float delta_time __attribute__((unused)), float position __attribute__((unused)), float *out_position __attribute__((unused)), float velocity __attribute__((unused)), float *out_velocity __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movb (%%ecx), %%dl\n\t"
      "flds 0xc(%%ebp)\n\t"
      "testb %%dl, %%dl\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .LFUN_001a8550_11\n\t"
      "flds 0x8(%%ebp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a8550_10\n\t"
      "flds 0x10(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a8550_3\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x10(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a8550_1\n\t"
      "movl 0x10(%%ecx), %%eax\n\t"
      "jmp .LFUN_001a8550_2\n\t"
      ".LFUN_001a8550_1:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      ".LFUN_001a8550_2:\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0xc(%%ecx)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fadds 0x14(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fadds 0xc(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fadds 0x14(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fsubs -0x8(%%ebp)\n\t"
      ".LFUN_001a8550_3:\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a8550_10\n\t"
      "flds 0x14(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a8550_6\n\t"
      "fcoms 0x14(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a8550_4\n\t"
      "flds 0x14(%%ecx)\n\t"
      "jmp .LFUN_001a8550_5\n\t"
      ".LFUN_001a8550_4:\n\t"
      "fld %%st(0)\n\t"
      ".LFUN_001a8550_5:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "faddp %%st(3)\n\t"
      ".byte 0xde, 0xe9\n\t"
      ".LFUN_001a8550_6:\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a8550_10\n\t"
      "flds 0x1c(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a8550_9\n\t"
      "fcoms 0x1c(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a8550_7\n\t"
      "flds 0x1c(%%ecx)\n\t"
      "jmp .LFUN_001a8550_8\n\t"
      ".LFUN_001a8550_7:\n\t"
      "fld %%st(0)\n\t"
      ".LFUN_001a8550_8:\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x18(%%ecx)\n\t"
      "flds 0x253398\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "faddp %%st(4)\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      ".LFUN_001a8550_9:\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a8550_11\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "fstps (%%ecx)\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "movb $1, %%dl\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movb %%dl, %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a8550_10:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_001a8550_11:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "fstps (%%ecx)\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movb %%dl, %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_001a8550: clang naked draft required"
#endif


/* unit_animation_start_action (0x1a8990) — XBE naked draft (batch 56). */
#if defined(__clang__)
static void *(*const b1a8990_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a8990_tag)(int, int) = tag_get;
static void *(*const b1a8990_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1a8990_c140160)(int object_handle, int16_t region_count) = object_set_region_count;
static int (*const b1a8990_c120f20)(int update_kind, int animation_graph_tag_index, int16_t animation_index) = model_animation_choose_random;

__attribute__((naked, noinline))
void unit_animation_start_action(int object_handle __attribute__((unused)), int16_t state __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, 0xc(%%ebp)\n\t"
      "movl %%eax, %%esi\n\t"
      "jne .Lunit_animation_start_action_1\n\t"
      "movb $0, 0x254(%%esi)\n\t"
      "movw $0xffff, 0x25a(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lunit_animation_start_action_1:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0x44(%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x616e7472\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movsbl 0x250(%%esi), %%ecx\n\t"
      "pushl $0x64\n\t"
      "pushl %%ecx\n\t"
      "addl $0xc, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movsbl 0x251(%%esi), %%edx\n\t"
      "pushl $0xbc\n\t"
      "pushl %%edx\n\t"
      "addl $0x58, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movsbl 0x252(%%esi), %%eax\n\t"
      "pushl $0x3c\n\t"
      "pushl %%eax\n\t"
      "leal 0xb0(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movswl 0xc(%%ebp), %%edx\n\t"
      "leal -0x1(%%edx), %%ecx\n\t"
      "addl $0x34, %%esp\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "cmpl $8, %%ecx\n\t"
      "ja .Lunit_animation_start_action_14\n\t"
      "jmp *.Lunit_animation_start_action_jt(,%%ecx,4)\n\t"
      ".Lunit_animation_start_action_2:\n\t"
      "movl $0x15, %%eax\n\t"
      ".Lunit_animation_start_action_3:\n\t"
      "movl 0x98(%%ebx), %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .Lunit_animation_start_action_13\n\t"
      "movl 0x9c(%%ebx), %%ecx\n\t"
      "movw (%%ecx,%%eax,2), %%di\n\t"
      "jmp .Lunit_animation_start_action_14\n\t"
      ".Lunit_animation_start_action_4:\n\t"
      "movl $0x16, %%eax\n\t"
      "jmp .Lunit_animation_start_action_3\n\t"
      ".Lunit_animation_start_action_5:\n\t"
      "movl $0x17, %%eax\n\t"
      "jmp .Lunit_animation_start_action_3\n\t"
      ".Lunit_animation_start_action_6:\n\t"
      "movl $0x18, %%eax\n\t"
      "jmp .Lunit_animation_start_action_3\n\t"
      ".Lunit_animation_start_action_7:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "jmp .Lunit_animation_start_action_12\n\t"
      ".Lunit_animation_start_action_8:\n\t"
      "movl $1, %%ecx\n\t"
      "jmp .Lunit_animation_start_action_12\n\t"
      ".Lunit_animation_start_action_9:\n\t"
      "movl $8, %%ecx\n\t"
      "jmp .Lunit_animation_start_action_12\n\t"
      ".Lunit_animation_start_action_10:\n\t"
      "movl $0x14, %%eax\n\t"
      "jmp .Lunit_animation_start_action_3\n\t"
      ".Lunit_animation_start_action_11:\n\t"
      "movl $9, %%ecx\n\t"
      ".Lunit_animation_start_action_12:\n\t"
      "movl 0x30(%%eax), %%edi\n\t"
      "movswl %%cx, %%ecx\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "jge .Lunit_animation_start_action_13\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "movw (%%eax,%%ecx,2), %%di\n\t"
      "jmp .Lunit_animation_start_action_14\n\t"
      ".Lunit_animation_start_action_13:\n\t"
      "orl $0xffffffff, %%edi\n\t"
      ".Lunit_animation_start_action_14:\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl $7, %%edx\n\t"
      "sete %%al\n\t"
      "decl %%eax\n\t"
      "andl $6, %%eax\n\t"
      "cmpw $-1, %%di\n\t"
      "je .Lunit_animation_start_action_16\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lunit_animation_start_action_15\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c140160]\n\t"
      "addl $8, %%esp\n\t"
      ".Lunit_animation_start_action_15:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x44(%%eax), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c120f20]\n\t"
      "movb 0xc(%%ebp), %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "movw %%ax, 0x25a(%%esi)\n\t"
      "movw $0, 0x25c(%%esi)\n\t"
      "movb %%cl, 0x254(%%esi)\n\t"
      ".Lunit_animation_start_action_16:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lunit_animation_start_action_jt:\n\t"
      ".long .Lunit_animation_start_action_2\n\t"
      ".long .Lunit_animation_start_action_4\n\t"
      ".long .Lunit_animation_start_action_5\n\t"
      ".long .Lunit_animation_start_action_6\n\t"
      ".long .Lunit_animation_start_action_7\n\t"
      ".long .Lunit_animation_start_action_8\n\t"
      ".long .Lunit_animation_start_action_9\n\t"
      ".long .Lunit_animation_start_action_10\n\t"
      ".long .Lunit_animation_start_action_11\n\t"
      ".text\n\t"
      :
      : [get] "m"(b1a8990_get), [tag] "m"(b1a8990_tag), [elem] "m"(b1a8990_elem), [c140160] "m"(b1a8990_c140160), [c120f20] "m"(b1a8990_c120f20)
      : "memory");
}
#else
#error "unit_animation_start_action: clang naked draft required"
#endif


/* FUN_001a8b20 (0x1a8b20) — XBE naked draft (batch 60). */
#if defined(__clang__)
static void *(*const b1a8b20_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a8b20_tag)(int, int) = tag_get;
static void *(*const b1a8b20_elem)(void *, int, int) = tag_block_get_element;
static int (*const b1a8b20_c120f20)(int update_kind, int animation_graph_tag_index, int16_t animation_index) = model_animation_choose_random;
static const char * (*const b1a8b20_c1205f0)(void *string_table, int16_t index) = FUN_001205f0;
static const char * (*const b1a8b20_c19b0d0)(const char *tag_name) = tag_name_strip_path;
static void (*const b1a8b20_cff550)(const char* format, ...) = console_warning;

__attribute__((naked, noinline))
void FUN_001a8b20(int object_handle __attribute__((unused)), int16_t state __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movsbw 0x255(%%esi), %%cx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%cx, 0x8(%%ebp)\n\t"
      "jl .LFUN_001a8b20_11\n\t"
      "movsbl 0x253(%%esi), %%eax\n\t"
      "addl $-0x17, %%eax\n\t"
      "cmpl $0x12, %%eax\n\t"
      "ja .LFUN_001a8b20_1\n\t"
      "movzbl 0x1a8ca8(%%eax), %%edx\n\t"
      "jmp *.LFUN_001a8b20_jt0(,%%edx,4)\n\t"
      ".LFUN_001a8b20_1:\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x44(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x616e7472\n\t"
      "call *%[tag]\n\t"
      "movsbl 0x250(%%esi), %%edx\n\t"
      "pushl $0x64\n\t"
      "pushl %%edx\n\t"
      "addl $0xc, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movsbl 0x251(%%esi), %%eax\n\t"
      "pushl $0xbc\n\t"
      "pushl %%eax\n\t"
      "leal 0x58(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movsbl 0x252(%%esi), %%edx\n\t"
      "pushl $0x3c\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "addl $0xb0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edx\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "addl $0x34, %%esp\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "decl %%eax\n\t"
      "cmpl $5, %%eax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "ja .LFUN_001a8b20_9\n\t"
      "jmp *.LFUN_001a8b20_jt1(,%%eax,4)\n\t"
      ".LFUN_001a8b20_2:\n\t"
      "movl $4, %%ecx\n\t"
      "jmp .LFUN_001a8b20_8\n\t"
      ".LFUN_001a8b20_3:\n\t"
      "movl $5, %%ecx\n\t"
      "jmp .LFUN_001a8b20_8\n\t"
      ".LFUN_001a8b20_4:\n\t"
      "movl $6, %%ecx\n\t"
      "jmp .LFUN_001a8b20_8\n\t"
      ".LFUN_001a8b20_5:\n\t"
      "movl $7, %%ecx\n\t"
      "jmp .LFUN_001a8b20_8\n\t"
      ".LFUN_001a8b20_6:\n\t"
      "movl $2, %%ecx\n\t"
      "jmp .LFUN_001a8b20_8\n\t"
      ".LFUN_001a8b20_7:\n\t"
      "movl $3, %%ecx\n\t"
      ".LFUN_001a8b20_8:\n\t"
      "movswl %%cx, %%eax\n\t"
      "cmpl 0x30(%%edx), %%eax\n\t"
      "jge .LFUN_001a8b20_9\n\t"
      "movl 0x34(%%edx), %%edx\n\t"
      "movswl (%%edx,%%eax,2), %%eax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001a8b20_9\n\t"
      "movl 0x44(%%edi), %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "call *%[c120f20]\n\t"
      "addl $0xc, %%esp\n\t"
      "movw %%ax, 0x25e(%%esi)\n\t"
      "movb 0x8(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movw $0, 0x260(%%esi)\n\t"
      "movb %%al, 0x255(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a8b20_9:\n\t"
      "movb 0x5054fb, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a8b20_10\n\t"
      "cmpw $0, 0x64(%%esi)\n\t"
      "jne .LFUN_001a8b20_10\n\t"
      "cmpw $-1, 0x24a(%%esi)\n\t"
      "jne .LFUN_001a8b20_10\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x322148\n\t"
      "call *%[c1205f0]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "movl 0x3c(%%edi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b0d0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b6950\n\t"
      "call *%[cff550]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_001a8b20_10:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001a8b20_11:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "addb %%al, (%%eax)\n\t"
      "addb %%al, (%%eax)\n\t"
      "addb %%al, (%%ecx)\n\t"
      "addb %%al, (%%eax)\n\t"
      "addb %%al, (%%eax)\n\t"
      "addb %%al, (%%eax)\n\t"
      "addb %%al, (%%ecx)\n\t"
      "addl %%eax, (%%ecx)\n\t"
      "addb %%al, (%%ecx)\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_001a8b20_jt0:\n\t"
      ".long .LFUN_001a8b20_11\n\t"
      ".long .LFUN_001a8b20_1\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_001a8b20_jt1:\n\t"
      ".long .LFUN_001a8b20_2\n\t"
      ".long .LFUN_001a8b20_3\n\t"
      ".long .LFUN_001a8b20_4\n\t"
      ".long .LFUN_001a8b20_5\n\t"
      ".long .LFUN_001a8b20_6\n\t"
      ".long .LFUN_001a8b20_7\n\t"
      ".text\n\t"
      :
      : [get] "m"(b1a8b20_get), [tag] "m"(b1a8b20_tag), [elem] "m"(b1a8b20_elem), [c120f20] "m"(b1a8b20_c120f20), [c1205f0] "m"(b1a8b20_c1205f0), [c19b0d0] "m"(b1a8b20_c19b0d0), [cff550] "m"(b1a8b20_cff550)
      : "memory");
}
#else
#error "FUN_001a8b20: clang naked draft required"
#endif


/* unit_find_nearby_seat (0x1a8ce0)
 *
 * Searches the child object chain of target_unit for a unit that occupies the
 * given seat_index, or that belongs to a friendly team (via game_allegiance).
 *
 * Walks the linked list starting at target_unit's first_child_object (offset
 * 0xC8). For each child that is a biped or vehicle (type 0 or 1):
 *   - If the child unit's seat tag index (offset 0x2A0) matches seat_index,
 *     records the child's handle in *out_unit_handle.
 *   - Otherwise, if the searching unit has an active rider/owner (offset 0x1C8
 *     != NONE) and the child's team is friendly with the searching unit's team,
 *     clears the "empty" flag but does not update the output handle.
 *
 * Returns true only if unit_handle != target_unit_handle AND no matching/
 * friendly child was found. If out_unit_handle is non-NULL, writes the handle
 * of the last seat-matching child found (or NONE if none matched).
 */
bool unit_find_nearby_seat(int unit_handle, int target_unit_handle,
                           int16_t seat_index, int *out_unit_handle)
{
  unit_data_t *unit_data;
  object_data_t *target_obj;
  object_data_t *child_obj;
  unit_data_t *child_unit;
  int child_handle;
  int result_handle;
  bool not_found;

  unit_data = (unit_data_t *)object_get_and_verify_type(unit_handle, 3);
  target_obj =
    (object_data_t *)object_get_and_verify_type(target_unit_handle, 3);

  not_found = (unit_handle != target_unit_handle);
  result_handle = -1;

  child_handle = target_obj->unk_200.value;
  while (child_handle != -1) {
    child_obj = (object_data_t *)object_get_and_verify_type(child_handle, -1);

    /* check if child is biped (type 0) or vehicle (type 1) */
    if ((1 << (*(uint8_t *)&child_obj->type & 0x1f)) & 3) {
      child_unit = (unit_data_t *)object_get_and_verify_type(child_handle, 3);

      if (child_unit->unk_672 == seat_index) {
        /* child occupies the requested seat */
        result_handle = child_handle;
        not_found = false;
      } else if (unit_data->unk_456.value != -1 &&
                 game_allegiance_get_team_is_friendly(
                   (int16_t)unit_data->object.unk_104,
                   (uint16_t)child_obj->unk_104)) {
        /* child is on a friendly team; seat is occupied/blocked */
        not_found = false;
      }
    }

    child_handle = child_obj->next_object_index.value;
  }

  if (out_unit_handle != NULL) {
    *out_unit_handle = result_handle;
  }
  return not_found;
}

/* unit_handle_weapon_state_change (0x1a8e10)
 *
 * Dispatches a unit animation state transition based on an incoming state code.
 * Maps input state values 1-8 to either FUN_001a8b20 (which sets a unit
 * animation transition state with a remapped index) or
 * unit_animation_start_action (which initiates a seat-based animation
 * sequence). The state remapping is: state 1 -> FUN_001a8b20 with index 1 state
 * 2 -> FUN_001a8b20 with index 2 state 3 -> FUN_001a8b20 with index 5 state 4
 * -> FUN_001a8b20 with index 6 state 5 -> unit_animation_start_action with
 * index 5 state 6 -> unit_animation_start_action with index 6 state 7 ->
 * FUN_001a8b20 with index 3 state 8 -> FUN_001a8b20 with index 4
 */
void unit_handle_weapon_state_change(int object_handle, int16_t state)
{
  switch (state) {
  case 1:
    FUN_001a8b20(object_handle, 1);
    return;
  case 2:
    FUN_001a8b20(object_handle, 2);
    return;
  case 3:
    FUN_001a8b20(object_handle, 5);
    return;
  case 4:
    FUN_001a8b20(object_handle, 6);
    return;
  case 5:
    unit_animation_start_action(object_handle, 5);
    return;
  case 6:
    unit_animation_start_action(object_handle, 6);
    return;
  case 7:
    FUN_001a8b20(object_handle, 3);
    return;
  case 8:
    FUN_001a8b20(object_handle, 4);
    return;
  }
}

/* unit_record_damage (0x1a8ee0) — XBE naked draft (batch 54). */
#if defined(__clang__)
static void *(*const b1a8ee0_get)(int, int) = object_get_and_verify_type;
static int (*const b1a8ee0_gtime)(void) = game_time_get;
static void (*const b1a8ee0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1a8ee0_exitfn)(int) = system_exit;
static bool (*const b1a8ee0_ca7a30)(int16_t team_a, int16_t team_b) = game_allegiance_get_team_is_friendly;
static void *(*const b1a8ee0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1a8ee0_tryget)(int, int) = object_try_and_get_and_verify_type;
static char (*const b1a8ee0_c3ff40)(int unit_handle, short killing_spree_count) = ai_handle_killing_spree;

__attribute__((naked, noinline))
void unit_record_damage(int unit_handle __attribute__((unused)), float damage_amount __attribute__((unused)), int16_t damage_type __attribute__((unused)), char notify_ai __attribute__((unused)), int attacker_object __attribute__((unused)), int16_t attacker_team __attribute__((unused)), int killing_object __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "leal 0x3e4(%%edi), %%eax\n\t"
      "movl $4, %%esi\n\t"
      ".Lunit_record_damage_1:\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lunit_record_damage_2\n\t"
      "cmpl %%ecx, 0x8(%%eax)\n\t"
      "je .Lunit_record_damage_3\n\t"
      ".Lunit_record_damage_2:\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "cmpl %%ecx, 0x4(%%eax)\n\t"
      "jne .Lunit_record_damage_4\n\t"
      ".Lunit_record_damage_3:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "movl %%edx, -0x4(%%eax)\n\t"
      "fadds (%%eax)\n\t"
      "movb $1, %%bl\n\t"
      "fstps (%%eax)\n\t"
      ".Lunit_record_damage_4:\n\t"
      "addl $0x10, %%eax\n\t"
      "decl %%esi\n\t"
      "jne .Lunit_record_damage_1\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lunit_record_damage_15\n\t"
      "xorl %%esi, %%esi\n\t"
      ".Lunit_record_damage_5:\n\t"
      "movswl %%si, %%eax\n\t"
      "addl $0x3e, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "cmpl $-1, (%%eax,%%edi,1)\n\t"
      "je .Lunit_record_damage_6\n\t"
      "incl %%esi\n\t"
      "cmpw $4, %%si\n\t"
      "jl .Lunit_record_damage_5\n\t"
      "jmp .Lunit_record_damage_7\n\t"
      ".Lunit_record_damage_6:\n\t"
      "cmpw $-1, %%si\n\t"
      "jne .Lunit_record_damage_14\n\t"
      ".Lunit_record_damage_7:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "movl $1, %%ecx\n\t"
      "leal 0x3f4(%%edi), %%edx\n\t"
      ".Lunit_record_damage_8:\n\t"
      "flds (%%edx)\n\t"
      "movswl %%bx, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "fcomps 0x3e4(%%eax,%%edi,1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_record_damage_9\n\t"
      "movl %%ecx, %%ebx\n\t"
      ".Lunit_record_damage_9:\n\t"
      "incl %%ecx\n\t"
      "addl $0x10, %%edx\n\t"
      "cmpw $4, %%cx\n\t"
      "jl .Lunit_record_damage_8\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal 0x3e0(%%edi), %%ecx\n\t"
      ".Lunit_record_damage_10:\n\t"
      "cmpw %%bx, %%ax\n\t"
      "je .Lunit_record_damage_12\n\t"
      "cmpw $-1, %%si\n\t"
      "je .Lunit_record_damage_11\n\t"
      "movl (%%ecx), %%ebx\n\t"
      "movswl %%si, %%edx\n\t"
      "addl $0x3e, %%edx\n\t"
      "shll $4, %%edx\n\t"
      "cmpl (%%edx,%%edi,1), %%ebx\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "jae .Lunit_record_damage_12\n\t"
      ".Lunit_record_damage_11:\n\t"
      "movl %%eax, %%esi\n\t"
      ".Lunit_record_damage_12:\n\t"
      "incl %%eax\n\t"
      "addl $0x10, %%ecx\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .Lunit_record_damage_10\n\t"
      "cmpw $-1, %%si\n\t"
      "jne .Lunit_record_damage_13\n\t"
      "pushl $1\n\t"
      "pushl $0x136c\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b6964\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_record_damage_13:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      ".Lunit_record_damage_14:\n\t"
      "movl 0x20(%%ebp), %%ebx\n\t"
      "movswl %%si, %%ecx\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "movl %%ecx, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "addl %%edi, %%eax\n\t"
      "addl $0x3e, %%ecx\n\t"
      "movl %%esi, 0x3ec(%%eax)\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "shll $4, %%ecx\n\t"
      "movl %%ebx, 0x3e8(%%eax)\n\t"
      "movl %%esi, 0x3e4(%%eax)\n\t"
      "movl %%edx, (%%ecx,%%edi,1)\n\t"
      "jmp .Lunit_record_damage_16\n\t"
      ".Lunit_record_damage_15:\n\t"
      "movl 0x20(%%ebp), %%ebx\n\t"
      ".Lunit_record_damage_16:\n\t"
      "movb 0x14(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_record_damage_24\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lunit_record_damage_24\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x68(%%edi), %%cx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[ca7a30]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_record_damage_24\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lunit_record_damage_17\n\t"
      "movl 0x5aa6d4, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lunit_record_damage_17\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lunit_record_damage_18\n\t"
      ".Lunit_record_damage_17:\n\t"
      "pushl $3\n\t"
      "pushl %%ebx\n\t"
      "movl %%ebx, %%edi\n\t"
      "call *%[tryget]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lunit_record_damage_24\n\t"
      ".Lunit_record_damage_18:\n\t"
      "cmpw $9, 0x10(%%ebp)\n\t"
      "jne .Lunit_record_damage_19\n\t"
      "movl 0x2d4(%%esi), %%eax\n\t"
      "jmp .Lunit_record_damage_20\n\t"
      ".Lunit_record_damage_19:\n\t"
      "movl 0x2d8(%%esi), %%eax\n\t"
      ".Lunit_record_damage_20:\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lunit_record_damage_21\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      ".Lunit_record_damage_21:\n\t"
      "testb $4, 0xb6(%%esi)\n\t"
      "jne .Lunit_record_damage_24\n\t"
      "call *%[gtime]\n\t"
      "movl 0x3dc(%%esi), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lunit_record_damage_22\n\t"
      "addl $0x78, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jge .Lunit_record_damage_23\n\t"
      ".Lunit_record_damage_22:\n\t"
      "movw $0, 0x3da(%%esi)\n\t"
      ".Lunit_record_damage_23:\n\t"
      "incw 0x3da(%%esi)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x3da(%%esi), %%cx\n\t"
      "movl %%eax, 0x3dc(%%esi)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c3ff40]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_record_damage_24\n\t"
      "movw $0, 0x3da(%%esi)\n\t"
      ".Lunit_record_damage_24:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [get] "m"(b1a8ee0_get), [gtime] "m"(b1a8ee0_gtime), [assert] "m"(b1a8ee0_assert), [exitfn] "m"(b1a8ee0_exitfn), [ca7a30] "m"(b1a8ee0_ca7a30), [dget] "m"(b1a8ee0_dget), [tryget] "m"(b1a8ee0_tryget), [c3ff40] "m"(b1a8ee0_c3ff40)
      : "memory");
}
#else
#error "unit_record_damage: clang naked draft required"
#endif


/* 0x1a9200 — get world-space position of the "head" marker on a unit.
 * Thin wrapper: calls object_get_markers_by_string_id for the string at
 * 0x2909e4 ("head"), then extracts XYZ from offset 0x60 in the marker
 * output record. Identical pattern to FUN_001a9520 ("body" marker). */
void unit_get_head_position(int object_handle, float *out_position)
{
  char marker_buf[0x6c];
  object_get_markers_by_string_id(object_handle, (void *)0x2909e4, marker_buf,
                                  1);
  out_position[0] = *(float *)(marker_buf + 0x60);
  out_position[1] = *(float *)(marker_buf + 0x64);
  out_position[2] = *(float *)(marker_buf + 0x68);
}

/* unit_set_seat_state (0x1a9240) — XBE naked draft (batch 59). */
#if defined(__clang__)
static void *(*const b1a9240_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a9240_tag)(int, int) = tag_get;
static void (*const b1a9240_c1a1140)(int unit_handle, int16_t estimate_mode, vector3_t *estimated_body_position, vector3_t *desired_facing, vector3_t *desired_gun_offset, vector3_t *out_position) = biped_estimate_position;
static short (*const b1a9240_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static void *(*const b1a9240_elem)(void *, int, int) = tag_block_get_element;

__attribute__((naked, noinline))
void unit_set_seat_state(int unit_handle __attribute__((unused)), float *position __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x6c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lunit_set_seat_state_3\n\t"
      "testb $4, 0xb6(%%esi)\n\t"
      "jne .Lunit_set_seat_state_1\n\t"
      "cmpw $0, 0x64(%%esi)\n\t"
      "jne .Lunit_set_seat_state_1\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a1140]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lunit_set_seat_state_1:\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lunit_set_seat_state_3\n\t"
      "movl 0x2d8(%%esi), %%esi\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jne .Lunit_set_seat_state_2\n\t"
      "pushl $1\n\t"
      "leal -0x6c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x2909e4\n\t"
      "pushl %%edi\n\t"
      "call *%[markers]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "popl %%edi\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lunit_set_seat_state_2:\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movswl 0x2a0(%%eax), %%edx\n\t"
      "pushl $0x11c\n\t"
      "pushl %%edx\n\t"
      "addl $0x2e4, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "pushl $1\n\t"
      "leal -0x6c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $0x24, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[markers]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "addl $0x24, %%esp\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "popl %%esi\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lunit_set_seat_state_3:\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "leal 0xc(%%edi), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "movl %%ebx, %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "movb 0x64(%%edi), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "testb $3, %%dl\n\t"
      "je .Lunit_set_seat_state_5\n\t"
      "cmpw $-1, 0x2a0(%%esi)\n\t"
      "je .Lunit_set_seat_state_5\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movswl 0x2a0(%%esi), %%ecx\n\t"
      "pushl $0x11c\n\t"
      "pushl %%ecx\n\t"
      "addl $0x2e4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw $1, 0x64(%%edi)\n\t"
      "jne .Lunit_set_seat_state_4\n\t"
      "movb 0x84(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lunit_set_seat_state_5\n\t"
      ".Lunit_set_seat_state_4:\n\t"
      "pushl $1\n\t"
      "leal -0x6c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl $0x84, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[markers]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl %%ecx, (%%ebx)\n\t"
      "movl %%edx, 0x4(%%ebx)\n\t"
      "movl %%eax, 0x8(%%ebx)\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lunit_set_seat_state_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a9240_get), [tag] "m"(b1a9240_tag), [c1a1140] "m"(b1a9240_c1a1140), [markers] "m"(b1a9240_markers), [elem] "m"(b1a9240_elem)
      : "memory");
}
#else
#error "unit_set_seat_state: clang naked draft required"
#endif


/* unit_estimate_position (0x1a93e0)
 *
 * Estimates the world-space position for a unit given a desired estimation mode
 * and optional predicted body position. Handles three major paths:
 *
 * 1. Unit has no parent AND flag byte (unit+0xb6) bit 2 is clear AND type==0
 *    (biped): delegate entirely to biped_estimate_position and return.
 *
 * 2. Unit type==0 (biped) AND has a parent AND parent type==1 (vehicle): call
 *    vehicle_get_estimated_position to get the vehicle's predicted position
 * into a local vector, and use that as the local_body_pos for the delta. If
 * vehicle_get_estimated_position returns -1 (failed), fall through to path 3.
 *
 * 3. Fallback: call object_get_world_position to get unit's world position as
 *    local_body_pos.
 *
 * After path 2/3: call unit_set_seat_state to compute the unit's current
 * estimated position into out_position, then add the delta
 * (body_position - local_body_pos) to out_position.
 *
 * Confirmed: assert strings "body_position && estimated_position" and
 * "(estimate_mode >= 0) && (estimate_mode <
 * NUMBER_OF_UNIT_ESTIMATE_POSITION_MODES)" reference
 * "c:\halo\SOURCE\units\units.c", lines 0x14b1 and 0x14b2. Confirmed: CMP
 * EAX,-0x1 / JNZ pattern for parent_object_index checks. Confirmed: TEST byte
 * ptr [EDI+0xb6],0x4 for flags check. Confirmed: CMP word ptr [EDI+0x64],0x0
 * and CMP word ptr [EAX+0x64],0x1 for type checks. Confirmed: FPU tail sequence
 * — FXCH after three FLD/FSUB pairs to reorder x/y.
 */
void unit_estimate_position(int unit_handle, int16_t estimate_mode,
                            vector3_t *body_position, vector3_t *desired_facing,
                            vector3_t *desired_gun_offset,
                            vector3_t *out_position)
{
  char *unit;
  char *parent_obj;
  int parent_handle;
  int result;
  vector3_t local_body_pos;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);

  if (body_position == NULL || out_position == NULL) {
    display_assert("body_position && estimated_position",
                   "c:\\halo\\SOURCE\\units\\units.c", 0x14b1, true);
    system_exit(-1);
  }
  if (estimate_mode < 0 || estimate_mode >= 4) {
    display_assert("(estimate_mode >= 0) && (estimate_mode < "
                   "NUMBER_OF_UNIT_ESTIMATE_POSITION_MODES)",
                   "c:\\halo\\SOURCE\\units\\units.c", 0x14b2, true);
    system_exit(-1);
  }

  parent_handle = *(int *)(unit + 0xcc);

  if (parent_handle == -1 && !(*(uint8_t *)(unit + 0xb6) & 0x4)) {
    /* No parent, no flag: if biped, fully delegate to biped_estimate_position
     */
    if (*(int16_t *)(unit + 0x64) == 0) {
      biped_estimate_position(unit_handle, estimate_mode, body_position,
                              desired_facing, desired_gun_offset, out_position);
      return;
    }
  } else if (*(int16_t *)(unit + 0x64) == 0 && parent_handle != -1) {
    /* Biped with a parent: if parent is a vehicle, try vehicle position */
    parent_obj = (char *)object_get_and_verify_type(parent_handle, -1);
    if (*(int16_t *)(parent_obj + 0x64) == 1) {
      result =
        vehicle_get_estimated_position(*(int *)(unit + 0xcc), &local_body_pos);
      if (result != -1)
        goto apply_delta;
    }
  }

  /* Fallback: use world position as local_body_pos reference */
  object_get_world_position(unit_handle, &local_body_pos);

apply_delta:
  /* Get the unit's current estimated seat position into out_position */
  unit_set_seat_state(unit_handle, (float *)out_position);

  /* Add (body_position - local_body_pos) delta to out_position */
  out_position->x += body_position->x - local_body_pos.x;
  out_position->y += body_position->y - local_body_pos.y;
  out_position->z += body_position->z - local_body_pos.z;
}

/* unit_impulse_to_animation_kind (0x1a9560) — XBE naked draft (batch 56). */
#if defined(__clang__)
static void (*const b1a9560_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1a9560_exitfn)(int) = system_exit;
static void *(*const b1a9560_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a9560_tryget)(int, int) = object_try_and_get_and_verify_type;
static void *(*const b1a9560_tag)(int, int) = tag_get;
static void *(*const b1a9560_elem)(void *, int, int) = tag_block_get_element;

__attribute__((naked, noinline))
int16_t unit_impulse_to_animation_kind(int16_t impulse_index __attribute__((unused)), int16_t *out_update_kind __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movw %%ax, %%di\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "testw %%di, %%di\n\t"
      "jl .Lunit_impulse_to_animation_kind_1\n\t"
      "cmpw $0xe, %%di\n\t"
      "jl .Lunit_impulse_to_animation_kind_2\n\t"
      ".Lunit_impulse_to_animation_kind_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x14f4\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b6a08\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_impulse_to_animation_kind_2:\n\t"
      "movswl %%di, %%edi\n\t"
      "cmpl $0xd, %%edi\n\t"
      "ja .Lunit_impulse_to_animation_kind_17\n\t"
      "jmp *.Lunit_impulse_to_animation_kind_jt0(,%%edi,4)\n\t"
      ".Lunit_impulse_to_animation_kind_3:\n\t"
      "movl $0x1d, %%esi\n\t"
      "jmp .Lunit_impulse_to_animation_kind_18\n\t"
      ".Lunit_impulse_to_animation_kind_4:\n\t"
      "movl $0x20, %%esi\n\t"
      "jmp .Lunit_impulse_to_animation_kind_18\n\t"
      ".Lunit_impulse_to_animation_kind_5:\n\t"
      "movl $0x21, %%esi\n\t"
      "jmp .Lunit_impulse_to_animation_kind_18\n\t"
      ".Lunit_impulse_to_animation_kind_6:\n\t"
      "movl $0x22, %%esi\n\t"
      "jmp .Lunit_impulse_to_animation_kind_18\n\t"
      ".Lunit_impulse_to_animation_kind_7:\n\t"
      "movl $0x1b, %%esi\n\t"
      "jmp .Lunit_impulse_to_animation_kind_18\n\t"
      ".Lunit_impulse_to_animation_kind_8:\n\t"
      "movl $0x1c, %%esi\n\t"
      "jmp .Lunit_impulse_to_animation_kind_18\n\t"
      ".Lunit_impulse_to_animation_kind_9:\n\t"
      "movl $0x1e, %%esi\n\t"
      "jmp .Lunit_impulse_to_animation_kind_18\n\t"
      ".Lunit_impulse_to_animation_kind_10:\n\t"
      "movl $0x1f, %%esi\n\t"
      "jmp .Lunit_impulse_to_animation_kind_18\n\t"
      ".Lunit_impulse_to_animation_kind_11:\n\t"
      "movl $4, %%esi\n\t"
      "jmp .Lunit_impulse_to_animation_kind_18\n\t"
      ".Lunit_impulse_to_animation_kind_12:\n\t"
      "movl $5, %%esi\n\t"
      "jmp .Lunit_impulse_to_animation_kind_18\n\t"
      ".Lunit_impulse_to_animation_kind_13:\n\t"
      "movl $6, %%esi\n\t"
      "jmp .Lunit_impulse_to_animation_kind_18\n\t"
      ".Lunit_impulse_to_animation_kind_14:\n\t"
      "movl $7, %%esi\n\t"
      "jmp .Lunit_impulse_to_animation_kind_18\n\t"
      ".Lunit_impulse_to_animation_kind_15:\n\t"
      "movl $0x28, %%esi\n\t"
      "jmp .Lunit_impulse_to_animation_kind_18\n\t"
      ".Lunit_impulse_to_animation_kind_16:\n\t"
      "movl $0x29, %%esi\n\t"
      "jmp .Lunit_impulse_to_animation_kind_18\n\t"
      ".Lunit_impulse_to_animation_kind_17:\n\t"
      "pushl $1\n\t"
      "pushl $0x1507\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "pushl $1\n\t"
      "pushl $0x1509\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x28058c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x28, %%esp\n\t"
      ".Lunit_impulse_to_animation_kind_18:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .Lunit_impulse_to_animation_kind_22\n\t"
      "cmpl $0xd, %%edi\n\t"
      "ja .Lunit_impulse_to_animation_kind_21\n\t"
      "movzbl 0x1a96dc(%%edi), %%eax\n\t"
      "jmp *.Lunit_impulse_to_animation_kind_jt1(,%%eax,4)\n\t"
      ".Lunit_impulse_to_animation_kind_19:\n\t"
      "popl %%edi\n\t"
      "movw %%si, %%ax\n\t"
      "movw $3, (%%ebx)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".Lunit_impulse_to_animation_kind_20:\n\t"
      "popl %%edi\n\t"
      "movw %%si, %%ax\n\t"
      "movw $6, (%%ebx)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".Lunit_impulse_to_animation_kind_21:\n\t"
      "pushl $1\n\t"
      "pushl $0x1524\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_impulse_to_animation_kind_22:\n\t"
      "popl %%edi\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "movl %%edi, %%edi\n\t"
      "addb %%al, (%%eax)\n\t"
      "addb %%al, (%%eax)\n\t"
      "addl %%eax, (%%ecx)\n\t"
      "addb %%al, (%%eax)\n\t"
      "addl %%eax, (%%ecx)\n\t"
      "addl %%eax, (%%ecx)\n\t"
      "addb %%al, (%%eax)\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movsbl 0x253(%%esi), %%eax\n\t"
      "addl $-0x17, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpl $0x12, %%eax\n\t"
      "ja .Lunit_impulse_to_animation_kind_24\n\t"
      "movzbl 0x1a97a8(%%eax), %%ecx\n\t"
      "jmp *.Lunit_impulse_to_animation_kind_jt2(,%%ecx,4)\n\t"
      ".Lunit_impulse_to_animation_kind_23:\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".Lunit_impulse_to_animation_kind_24:\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lunit_impulse_to_animation_kind_25\n\t"
      "cmpw $-1, 0x2a0(%%esi)\n\t"
      "je .Lunit_impulse_to_animation_kind_27\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lunit_impulse_to_animation_kind_27\n\t"
      "movl (%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movswl 0x2a0(%%esi), %%ecx\n\t"
      "pushl $0x11c\n\t"
      "pushl %%ecx\n\t"
      "addl $0x2e4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl %%di, %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl $0xc, %%ecx\n\t"
      "jl .Lunit_impulse_to_animation_kind_27\n\t"
      "cmpl $0xd, %%ecx\n\t"
      "jg .Lunit_impulse_to_animation_kind_27\n\t"
      "movl (%%eax), %%eax\n\t"
      "shrl $8, %%eax\n\t"
      "popl %%esi\n\t"
      "andb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".Lunit_impulse_to_animation_kind_25:\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl $0xc, %%eax\n\t"
      "jl .Lunit_impulse_to_animation_kind_26\n\t"
      "cmpl $0xd, %%eax\n\t"
      "jle .Lunit_impulse_to_animation_kind_23\n\t"
      ".Lunit_impulse_to_animation_kind_26:\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".Lunit_impulse_to_animation_kind_27:\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      "addb %%al, (%%eax)\n\t"
      "addb %%al, (%%eax)\n\t"
      "addb %%al, (%%ecx)\n\t"
      "addb %%al, (%%eax)\n\t"
      "addb %%al, (%%eax)\n\t"
      "addb %%al, (%%eax)\n\t"
      "addb %%al, (%%ecx)\n\t"
      "addl %%eax, (%%ecx)\n\t"
      "addb %%al, (%%ecx)\n\t"
      "addb %%dl, -0x6f6f6f70(%%eax)\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lunit_impulse_to_animation_kind_jt0:\n\t"
      ".long .Lunit_impulse_to_animation_kind_3\n\t"
      ".long .Lunit_impulse_to_animation_kind_4\n\t"
      ".long .Lunit_impulse_to_animation_kind_5\n\t"
      ".long .Lunit_impulse_to_animation_kind_6\n\t"
      ".long .Lunit_impulse_to_animation_kind_7\n\t"
      ".long .Lunit_impulse_to_animation_kind_8\n\t"
      ".long .Lunit_impulse_to_animation_kind_9\n\t"
      ".long .Lunit_impulse_to_animation_kind_10\n\t"
      ".long .Lunit_impulse_to_animation_kind_11\n\t"
      ".long .Lunit_impulse_to_animation_kind_12\n\t"
      ".long .Lunit_impulse_to_animation_kind_13\n\t"
      ".long .Lunit_impulse_to_animation_kind_14\n\t"
      ".long .Lunit_impulse_to_animation_kind_15\n\t"
      ".long .Lunit_impulse_to_animation_kind_16\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lunit_impulse_to_animation_kind_jt1:\n\t"
      ".long .Lunit_impulse_to_animation_kind_20\n\t"
      ".long .Lunit_impulse_to_animation_kind_19\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lunit_impulse_to_animation_kind_jt2:\n\t"
      ".long .Lunit_impulse_to_animation_kind_23\n\t"
      ".long .Lunit_impulse_to_animation_kind_24\n\t"
      ".text\n\t"
      :
      : [assert] "m"(b1a9560_assert), [exitfn] "m"(b1a9560_exitfn), [get] "m"(b1a9560_get), [tryget] "m"(b1a9560_tryget), [tag] "m"(b1a9560_tag), [elem] "m"(b1a9560_elem)
      : "memory");
}
#else
#error "unit_impulse_to_animation_kind: clang naked draft required"
#endif


/* unit_animation_state_allows_impulse (0x1a96f0)
 *
 * Returns true if the unit's current animation state (unk_595 at +0x253)
 * is one that permits an animation impulse to be applied.
 *
 * States in [0x17..0x29] that block impulses (switch table 0x1a97a8):
 *   0x17-0x1b, 0x1d-0x1f, 0x20-0x23, 0x27, 0x29 -> return false.
 * States outside [0x17..0x29] -> fall to parent check.
 *
 * If parent_object_index != -1 (unit is seated/mounted):
 *   - If unk_672 (seat-anim index) is -1 -> return false.
 *   - Resolves parent via object_try_and_get_and_verify_type (0x13d640).
 *   - Looks up the seat-anim entry at parent_unit_tag+0x2e4, indexed by
 *     unk_672, element size 0x11c.
 *   - If impulse_index is in [0xc, 0xd]: returns bit 8 of seat_anim[0].
 *   - If impulse_index is outside [0xc, 0xd]: returns false.
 *
 * If parent_object_index == -1 (no parent):
 *   - If impulse_index NOT in [0xc, 0xd] -> return true.
 *   - If impulse_index in [0xc, 0xd] -> return false.
 *
 * Register args: unit_handle @<eax>, impulse_index @<edi> (leaked from caller).
 * Returns bool in AL.
 *
 * Confirmed: PUSH 0x3 / PUSH EAX -> object_get_and_verify_type.
 * Confirmed: MOVSX EAX,byte[ESI+0x253]; ADD -0x17; CMP 0x12; jump table
 * 0x1a97a8. Confirmed: MOVSX ECX,DI at 0x1a976c and 0x1a9786 (DI = caller's EDI
 * = anim_index). Confirmed: CMP [ESI+0x2a0],-1 -> unk_672 check. Confirmed:
 * object_try_and_get_and_verify_type at 0x13d640 / tag_get /
 * tag_block_get_element. Confirmed: MOV EAX,[EAX]; SHR EAX,8; AND AL,1 -> bit 8
 * gate.
 */
bool unit_animation_state_allows_impulse(int unit_handle, int impulse_index)
{
  unit_data_t *unit;
  int state;

  unit = (unit_data_t *)object_get_and_verify_type(unit_handle, 3);
  state = (int)(int8_t)unit->unk_595;

  /* Switch on state - 0x17 for values in [0x17, 0x29] */
  if ((unsigned)(state - 0x17) <= 0x12) {
    switch (state) {
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1d:
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x27:
    case 0x29:
      return false;
    default:
      break;
    }
  }

  /* Check parent (mounted) case */
  if (unit->object.parent_object_index.value != -1) {
    unit_data_t *parent;
    char *parent_tag;
    int *seat_anim;

    if ((int16_t)unit->unk_672 == -1)
      return false;

    parent = (unit_data_t *)object_try_and_get_and_verify_type(
      (int)unit->object.parent_object_index.value, 3);
    if (parent == NULL)
      return false;

    parent_tag = (char *)tag_get(0x756e6974, *(int *)parent);
    seat_anim = (int *)tag_block_get_element(
      parent_tag + 0x2e4, (int)(int16_t)unit->unk_672, 0x11c);

    /* Only impulses 0xc and 0xd can fire when mounted */
    if ((int16_t)impulse_index < 0xc || (int16_t)impulse_index > 0xd)
      return false;

    return (bool)((seat_anim[0] >> 8) & 1);
  }

  /* No parent: impulses 0xc and 0xd are blocked */
  if ((int16_t)impulse_index >= 0xc && (int16_t)impulse_index <= 0xd)
    return false;

  return true;
}

/* unit_test_animation_impulse (0x1a97c0)
 *
 * Tests whether a specific animation impulse can be applied to a unit.
 * First checks if the current animation state allows the impulse, then
 * looks up the unit's animation tag block to verify the impulse has a
 * valid animation entry.
 *
 * Returns true (AL=1) if the animation impulse is available and mapped
 * to a non-NONE animation index; false otherwise.
 *
 * Tag lookup chain:
 *   unit tag (0x756e6974) -> animations tag ref at +0x44 ->
 *   animation tag (0x616e7472) -> block at +0xC, elem size 100 ->
 *   sub-block at result+0x58, elem size 0xBC ->
 *   count at +0x98, data pointer at +0x9C, indexed by animation kind.
 *
 * Confirmed: PUSH [EBP+0x8] / PUSH 0x3 -> cdecl, 2 stack params.
 * Confirmed: MOV EAX,EBX -> @eax for unit_animation_state_allows_impulse.
 * Confirmed: LEA EBX,[EBP-0x4] / MOV EAX,EDI -> @ebx, @ax for
 *            unit_impulse_to_animation_kind.
 * Confirmed: MOVSX EDX,byte[ESI+0x250] and byte[ESI+0x251] for anim indices.
 * Confirmed: CMP AX,0xffff / SETNZ AL for return logic.
 */
uint32_t unit_test_animation_impulse(int unit_handle, int impulse_index)
{
  char *unit;
  char *anim_tag;
  char *anim_block;
  int16_t anim_kind;
  int16_t update_kind;
  int16_t *data;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);

  if (!unit_animation_state_allows_impulse(unit_handle, impulse_index)) {
    return 0;
  }

  /* Look up unit tag -> animations tag -> animation block elements */
  {
    char *unit_tag;
    int anim_tag_index;

    unit_tag = (char *)tag_get(0x756e6974, *(int *)unit);
    anim_tag_index = *(int *)(unit_tag + 0x44);
    anim_tag = (char *)tag_get(0x616e7472, anim_tag_index);
  }

  anim_block = (char *)tag_block_get_element(
      anim_tag + 0xc, (int)*(int8_t *)(unit + 0x250), 100);
  anim_block = (char *)tag_block_get_element(
      anim_block + 0x58, (int)*(int8_t *)(unit + 0x251), 0xbc);

  /* Map impulse to animation kind */
  anim_kind = unit_impulse_to_animation_kind((int16_t)impulse_index,
                                             &update_kind);

  if (anim_kind < 0 || (int)anim_kind >= *(int *)(anim_block + 0x98)) {
    /* Out of range — return false (matches OR EAX,-1; CMP AX,0xffff; SETNZ) */
    return (uint32_t)(int16_t)-1 != (int16_t)-1;
  }

  data = *(int16_t **)(anim_block + 0x9c);
  return (uint32_t)(data[anim_kind] != (int16_t)-1);
}

/* unit_scripting_unit_driver (0x1a9900)
 *
 * Copies the unit's aiming vector (unk_492, offset 0x1EC) into the output
 * buffer. Resolves the unit via object_get_and_verify_type with type mask
 * 0x3 (biped | vehicle).
 */
void unit_scripting_unit_driver(int unit_handle, void *out_aiming)
{
  char *unit;
  float *out = (float *)out_aiming;

  unit = object_get_and_verify_type(unit_handle, 3);
  out[0] = *(float *)(unit + 0x1ec);
  out[1] = *(float *)(unit + 0x1f0);
  out[2] = *(float *)(unit + 0x1f4);
}

/* unit_scripting_unit_gunner (0x1a9930)
 *
 * Copies the unit's looking vector (unk_528, offset 0x210) into the output
 * buffer. Resolves the unit via object_get_and_verify_type with type mask
 * 0x3 (biped | vehicle).
 */
void unit_scripting_unit_gunner(int unit_handle, void *out_looking)
{
  char *unit;
  float *out = (float *)out_looking;

  unit = object_get_and_verify_type(unit_handle, 3);
  out[0] = *(float *)(unit + 0x210);
  out[1] = *(float *)(unit + 0x214);
  out[2] = *(float *)(unit + 0x218);
}

/* units_debug_get_closest_unit (0x1a9960)
 *
 * Gets the unit's facing vector by delegating to object_get_orientation (an
 * object-level orientation getter in objects.c). Passes NULL for the up-vector
 * output, requesting only the forward direction.
 */
void units_debug_get_closest_unit(int unit_handle, void *out_facing)
{
  object_get_orientation(unit_handle, (float *)out_facing, 0);
}

/* unit_is_alive (0x1a9a30)
 *
 * Returns whether the given unit handle refers to a unit that is currently
 * alive. Resolves the handle via object_get_and_verify_type with type mask
 * 0x3 (bit 0 = biped, bit 1 = vehicle — accepts any unit object; asserts
 * otherwise) and tests bit 6 of the unit's flag word at offset 0x1B4
 * (unit_data_t.unk_436).
 */
bool unit_is_alive(int unit_handle)
{
  unit_data_t *unit;

  unit = (unit_data_t *)object_get_and_verify_type(unit_handle, 3);
  return (unit->unk_436 >> 6) & 1;
}

/* Check if a unit is in a vehicle seat based on seat state byte at +0x253. */
bool unit_is_busy(int unit_handle)
{
  char *unit = (char *)object_get_and_verify_type(unit_handle, 3);
  int seat_state = *(signed char *)(unit + 0x253);
  switch (seat_state) {
  case 0x17:
  case 0x18:
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x1d:
  case 0x1e:
  case 0x1f:
  case 0x20:
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x27:
  case 0x29:
    return true;
  default:
    return false;
  }
}

/* FUN_001AA170 (0x1aa170) — find nearest biped
 *
 * Iterates all biped objects (type_mask=1) to find the nearest biped
 * to the given unit, excluding the unit itself and any biped with
 * bit 2 of byte +0xb6 set. Uses 3D Euclidean distance (SQRT).
 * If unit_handle is -1, uses FLT_MAX (0x7f7fffff) as distance for all
 * candidates, effectively selecting the first valid biped.
 *
 * Returns the nearest biped's datum handle, or -1 if none found.
 *
 * Confirmed: cdecl, 1 stack param (unit_handle).
 * Confirmed: object_iterator_new(iter, 1, 0) — biped type only.
 * Confirmed: FLOAT_002533c0 = 0.0f (used when unit_handle == -1).
 * Confirmed: initial best_dist = FLT_MAX (0x7f7fffff).
 */
int FUN_001AA170(int unit_handle)
{
  int best_handle;
  float best_dist;
  int iter[4];
  char *obj;
  float pos_a[3];
  float pos_b[3];
  float dx, dy, dz, dist;

  best_handle = -1;
  best_dist = 3.4028235e+38f;

  object_iterator_new(iter, 1, 0);
  obj = (char *)object_iterator_next(iter);
  while (obj != NULL) {
    if (iter[2] != unit_handle &&
        (*(uint8_t *)(obj + 0xb6) & 4) == 0) {
      if (unit_handle == -1) {
        dist = *(float *)0x2533c0;
      } else {
        object_get_world_position(unit_handle, (vector3_t *)pos_a);
        object_get_world_position(iter[2], (vector3_t *)pos_b);
        dx = pos_b[0] - pos_a[0];
        dy = pos_b[1] - pos_a[1];
        dz = pos_b[2] - pos_a[2];
        dist = sqrtf(dx * dx + dy * dy + dz * dz);
      }
      if (dist < best_dist) {
        best_handle = iter[2];
        best_dist = dist;
      }
    }
    obj = (char *)object_iterator_next(iter);
  }
  return best_handle;
}

/* unit_debug_ninja_rope (0x1aa240)
 * Collision-based ninja rope debug function.
 * Casts a ray from the unit's aim position along a scaled facing direction.
 * If the ray hits geometry with a fraction above 0.95, translates the unit
 * to the hit point offset upward by 0.25.
 * Uses the collision stack depth guard to prevent reentrant collision. */
void unit_debug_ninja_rope(int unit_handle)
{
  char *unit;
  float origin[3];
  float direction[3];
  char collision_result[80];
  int16_t depth;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  unit_set_seat_state(unit_handle, origin);

  direction[0] = *(float *)(unit + 0x1ec) * 25.0f;
  direction[1] = *(float *)(unit + 0x1f0) * 25.0f;
  direction[2] = *(float *)(unit + 0x1f4) * 25.0f;

  if (global_current_collision_user_depth >= MAXIMUM_COLLISION_USER_STACK_DEPTH) {
    display_assert(
        "global_current_collision_user_depth < "
        "MAXIMUM_COLLISION_USER_STACK_DEPTH",
        "c:\\halo\\SOURCE\\units\\units.c", 0x19f8, 1);
    system_exit(-1);
  }

  depth = global_current_collision_user_depth;
  global_current_collision_user_depth = depth + 1;
  collision_user_stack[depth] = 0x15;

  if (FUN_0014df70(0x22, origin, direction, unit_handle,
                   (int16_t *)collision_result)) {
    /* collision_result + 0x2c = fraction, compare > 0.95 */
    if (*(float *)(collision_result + 0x2c) > 0.95f) {
      /* collision_result + 0x20 = hit y-coordinate, add 0.25 */
      *(float *)(collision_result + 0x20) += 0.25f;
      /* collision_result + 0x18 = hit position */
      object_translate(unit_handle,
                       (float *)(collision_result + 0x18), 0);
    }
  }

  if (global_current_collision_user_depth < 2) {
    display_assert("global_current_collision_user_depth > 1",
                   "c:\\halo\\SOURCE\\units\\units.c", 0x1a01, 1);
    system_exit(-1);
  }
  global_current_collision_user_depth -= 1;
}

/* FUN_001aa360 (0x1aa360) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b1aa360_get)(int, int) = object_get_and_verify_type;
static void *(*const b1aa360_tag)(int, int) = tag_get;
static void (*const b1aa360_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1aa360_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
char FUN_001aa360(int unit_handle __attribute__((unused)), int param_2 __attribute__((unused)), int16_t index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0x44(%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x616e7472\n\t"
      "call *%[tag]\n\t"
      "movw 0x10(%%ebp), %%ax\n\t"
      "addl $0x18, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_001aa360_1\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .LFUN_001aa360_2\n\t"
      ".LFUN_001aa360_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x1a21\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b6ac0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001aa360_2:\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1aa360_get), [tag] "m"(b1aa360_tag), [assert] "m"(b1aa360_assert), [exitfn] "m"(b1aa360_exitfn)
      : "memory");
}
#else
#error "FUN_001aa360: clang naked draft required"
#endif


/* FUN_001aa430 (0x1aa430) — XBE naked draft (batch 64). */
#if defined(__clang__)
static void *(*const b1aa430_get)(int, int) = object_get_and_verify_type;
static short (*const b1aa430_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static float (*const b1aa430_norm)(float *) = normalize3d;

__attribute__((naked, noinline))
char FUN_001aa430(int unit_handle __attribute__((unused)), float *point __attribute__((unused)), float half_angle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x78, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_001aa430_1\n\t"
      "pushl %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl $1\n\t"
      "leal -0x78(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2909e4\n\t"
      "pushl %%edi\n\t"
      "call *%[markers]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "flds (%%eax)\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "fsubs -0x18(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs -0x14(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs -0x10(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $0x1c, %%esp\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x218(%%esi)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x214(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x210(%%esi)\n\t"
      "popl %%esi\n\t"
      "faddp %%st(1)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fcos\n\t"
      "fxch %%st(1)\n\t"
      "fxch %%st(1)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "movb $1, %%al\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001aa430_2\n\t"
      ".LFUN_001aa430_1:\n\t"
      "movb %%bl, %%al\n\t"
      ".LFUN_001aa430_2:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1aa430_get), [markers] "m"(b1aa430_markers), [norm] "m"(b1aa430_norm)
      : "memory");
}
#else
#error "FUN_001aa430: clang naked draft required"
#endif


/* any_unit_is_dangerous (0x1aa3c0)
 *
 * Iterates all unit objects (type_mask=3: bipeds + vehicles) and returns true
 * if any unit is considered "dangerous" — i.e. in a combat-relevant state
 * that should block saving or other safe-state transitions.
 *
 * A unit is dangerous when:
 *   - unk_595 (offset 0x253) == 0x21 and unk_573 (offset 0x23D) != 3
 *     (unit in some active/aggressive state, not in state 3)
 *   - unk_595 == 0x19 or 0x18, and bit 2 of unk_584 (offset 0x248) is clear
 *     (unit in alert/combat stance without a particular suppression flag)
 *
 * Called by game_all_quiet, game_safe_to_save, and players_respawn_coop.
 */
bool any_unit_is_dangerous(void)
{
  int iter_buf[4];
  unit_data_t *unit;
  uint8_t state;

  object_iterator_new(iter_buf, 3, 1);
  unit = (unit_data_t *)object_iterator_next(iter_buf);

  while (unit != NULL) {
    state = unit->unk_595;
    if (state == 0x21 && unit->unk_573 != 3)
      return true;
    if ((state == 0x19 || state == 0x18) && (unit->unk_584 & 4) == 0)
      return true;
    unit = (unit_data_t *)object_iterator_next(iter_buf);
  }

  return false;
}

/* unit_detach_from_parent (0x1aa5c0)
 *
 * Detaches a unit from its parent vehicle. Computes a direction vector
 * from parent to child position, normalizes it, and scales by 0.02f
 * (the eject velocity factor at 0x2b6af4). Detaches the object from
 * its parent, finds a safe spawn location (scenario_location_underwater),
 * sets the new position, clears flags, adds the ejection velocity, and
 * recomputes node matrices.
 *
 * Confirmed: cdecl, 1 stack param (object_handle).
 * Confirmed: calls object_get_and_verify_type twice (child and parent).
 * Confirmed: normalize3d returns 0.0 when vector is zero.
 * Confirmed: 0x2b6af4 = 0.02f (ejection velocity scale).
 * Confirmed: clears bit 5 (0x20) of flags at +0x4.
 * Confirmed: clears bit 15 (0x8000) of flags at +0x1b4.
 */
void unit_detach_from_parent(int object_handle)
{
  char *unit;
  int parent_handle;
  float parent_pos[3];
  float child_pos[3];
  float dir[3];
  float len;

  unit = (char *)object_get_and_verify_type(object_handle, 3);
  parent_handle = *(int *)(unit + 0xcc);
  if (parent_handle == -1)
    return;

  object_get_and_verify_type(parent_handle, 3);
  object_get_world_position(parent_handle, (vector3_t *)parent_pos);
  object_get_world_position(object_handle, (vector3_t *)child_pos);

  dir[0] = child_pos[0] - parent_pos[0];
  dir[1] = child_pos[1] - parent_pos[1];
  dir[2] = child_pos[2] - parent_pos[2];

  len = normalize3d(dir);
  if (len == *(float *)0x2533c0) {
    dir[0] = *(float *)(unit + 0x24);
    dir[1] = *(float *)(unit + 0x28);
    dir[2] = *(float *)(unit + 0x2c);
  }

  dir[0] = dir[0] * *(float *)0x2b6af4;
  dir[1] = dir[1] * *(float *)0x2b6af4;
  dir[2] = dir[2] * *(float *)0x2b6af4;

  object_detach_from_parent(object_handle);

  child_pos[0] = *(float *)(unit + 0xc);
  child_pos[1] = *(float *)(unit + 0x10);
  child_pos[2] = *(float *)(unit + 0x14);
  scenario_location_underwater(child_pos);
  object_set_position(object_handle, child_pos, NULL, NULL);

  *(uint32_t *)(unit + 0x4) &= ~0x20u;
  *(uint32_t *)(unit + 0x1b4) &= ~0x8000u;

  *(float *)(unit + 0x18) += dir[0];
  *(float *)(unit + 0x1c) += dir[1];
  *(float *)(unit + 0x20) += dir[2];

  object_set_garbage(object_handle, 1);
  object_compute_node_matrices(object_handle);
}

/* unit_update_seat_occupancy (0x1aa890)
 *
 * Walks the child object chain of a unit (starting at unk_200, offset 0xC8)
 * and updates two seat-occupancy handles: unk_724 (offset 0x2D4) for seats
 * with flag bit 2 (0x4) set, and unk_728 (offset 0x2D8) for seats with flag
 * bit 3 (0x8) set. For each child that is a biped or vehicle with a valid
 * seat tag index, retrieves the seat definition flags from the unit tag.
 *
 * Bit 2 (0x4): writes child handle to unk_724, but only if the unit's
 * unk_436 bit 0 is clear AND unk_724 is currently NONE.
 * Bit 3 (0x8): writes child handle to unk_728, but only if unk_728 is
 * currently NONE or equals unk_724.
 *
 * Register arg: unit_handle passed in EAX (vehicle_handle).
 *
 * Confirmed: PUSH 0x3 / PUSH EAX -> object_get_and_verify_type.
 * Confirmed: child chain via [ESI+0xC8] -> [EBX+0xC4].
 * Confirmed: seat flags from tag_block_get_element(tag+0x2e4, index, 0x11c).
 * Confirmed: TEST CL,0x4 and TEST CL,0x8 for seat flag bits.
 * Confirmed: stores to [ESI+0x2D4] and [ESI+0x2D8].
 */
void unit_update_seat_occupancy(int vehicle_handle)
{
  char *unit;
  char *unit_tag;
  int child_handle;
  char *child_obj;
  int *seat_element;
  int seat_flags;

  unit = (char *)object_get_and_verify_type(vehicle_handle, 3);
  unit_tag = (char *)tag_get(0x756e6974, *(int *)unit);
  child_handle = *(int *)(unit + 0xc8);

  while (child_handle != -1) {
    child_obj = (char *)object_get_and_verify_type(child_handle, -1);

    if (((1 << (*(uint8_t *)(child_obj + 0x64) & 0x1f)) & 3) &&
        *(int16_t *)(child_obj + 0x2a0) != -1) {
      seat_element = (int *)tag_block_get_element(
        unit_tag + 0x2e4, (int)*(int16_t *)(child_obj + 0x2a0), 0x11c);
      seat_flags = *seat_element;

      if ((seat_flags & 4) == 0 || (*(uint8_t *)(unit + 0x1b4) & 1) ||
          *(int *)(unit + 0x2d4) != -1) {
        /* bit 2 not set, or unit already has unk_724 occupied —
         * check bit 3 only */
        if (seat_flags & 8) {
          if (*(int *)(unit + 0x2d8) == -1 ||
              *(int *)(unit + 0x2d8) == *(int *)(unit + 0x2d4)) {
            *(int *)(unit + 0x2d8) = child_handle;
          }
        }
      } else {
        /* bit 2 set and unk_724 is NONE and unk_436 bit 0 clear */
        *(int *)(unit + 0x2d4) = child_handle;
        if (seat_flags & 8) {
          if (*(int *)(unit + 0x2d8) == -1) {
            *(int *)(unit + 0x2d8) = child_handle;
          }
        }
      }
    }

    child_handle = *(int *)(child_obj + 0xc4);
  }
}

/* unit_get_equipment (0x1aa970)
 *
 * Returns the equipment datum handle stored in the unit's equipment slot
 * (unit_data_t.unk_712, offset 0x2C8). Resolves the unit via
 * object_get_and_verify_type with type mask 3 (biped | vehicle).
 */
int unit_get_equipment(int unit_handle)
{
  unit_data_t *unit;

  unit = (unit_data_t *)object_get_and_verify_type(unit_handle, 3);
  return unit->unk_712.value;
}

/* unit_try_add_grenade (0x1aa990)
 *
 * Attempts to add a grenade to the unit's inventory. The equipment object
 * must be of powerup_type _equipment_powerup_grenade (6). Looks up the
 * grenade type's maximum count from the game globals tag block at offset
 * 0x128, then checks the unit's current grenade count array at offset 0x2CE.
 * If there is room, increments the count, plays an effect if a local player
 * is carrying the unit, and deletes the equipment object.
 *
 * Returns: true if the grenade was added, false if the unit is already at
 * maximum capacity for that grenade type.
 */
bool unit_try_add_grenade(int unit_handle, int equipment_handle)
{
  int *equipment_obj;
  char *equipment_tag;
  char *unit;
  int16_t grenade_type;
  int16_t max_count;
  char *game_globals;
  char current_count;
  int player_index;
  char *player;

  equipment_obj = (int *)object_get_and_verify_type(equipment_handle, 8);
  equipment_tag = (char *)tag_get(0x65716970, *equipment_obj);
  unit = (char *)object_get_and_verify_type(unit_handle, 3);

  if (*(int16_t *)(equipment_tag + 0x308) != 6) {
    display_assert("equipment_definition->equipment.powerup_type==_equipment_"
                   "powerup_grenade",
                   "c:\\halo\\SOURCE\\units\\units.c", 0x1c72, 1);
    system_exit(-1);
  }

  grenade_type = *(int16_t *)(equipment_tag + 0x30a);
  game_globals = (char *)game_globals_get();
  max_count =
    *(int16_t *)tag_block_get_element(game_globals + 0x128, grenade_type, 0x44);

  if (max_count == 0)
    return false;

  current_count = *(char *)(unit + grenade_type + 0x2ce);
  if ((int16_t)current_count >= max_count)
    return false;

  *(char *)(unit + grenade_type + 0x2ce) = current_count + 1;

  player_index = player_index_from_unit_index(unit_handle);
  if (player_index != -1) {
    player = (char *)datum_get(player_data, player_index);
    if (*(int16_t *)(player + 2) != -1)
      item_activate_equipment_effect(equipment_handle);
  }

  object_delete(equipment_handle);
  return true;
}

/* unit_set_grenade_count (0x1aaa90)
 *
 * Adds count to the unit's grenade count for the given grenade_type, then
 * records grenade_type as the "last active" grenade type in two byte fields.
 * The grenade count array lives at unit+0x2CE (one byte per grenade type).
 * Offsets 0x2CC and 0x2CD both receive the low byte of grenade_type; these
 * are the last-used-grenade-type fields (two copies, presumably for different
 * subsystems).
 *
 * Asserts: grenade_count >= 0; 0 <= grenade_type <
 * NUMBER_OF_UNIT_GRENADE_TYPES. Returns: updated grenade count (int16_t,
 * sign-extended from byte).
 *
 * Confirmed: CMP word ptr [EBP+0x10],0x0 -> grenade_count is short at +0x10.
 * Confirmed: MOV BX,[EBP+0xC] -> grenade_type is short at +0xC.
 * Confirmed: MOV DL,byte ptr [EBP+0x10]; ADD byte ptr [EAX],DL -> byte add.
 * Confirmed: MOV byte ptr [ESI+0x2cd],BL / MOV byte ptr [ESI+0x2cc],BL.
 * Confirmed: MOVSX AX,byte ptr [EAX] -> return is sign-extended byte (short).
 */
int16_t unit_set_grenade_count(int unit_handle, int16_t grenade_type,
                               int16_t grenade_count)
{
  char *unit;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);

  if (grenade_count < 0) {
    display_assert("grenade_count>=0", "c:\\halo\\SOURCE\\units\\units.c",
                   0x1c8d, 1);
    system_exit(-1);
  }

  if ((grenade_type < 0) || (grenade_type > 1)) {
    display_assert(
      "(grenade_type >= 0) && (grenade_type < NUMBER_OF_UNIT_GRENADE_TYPES)",
      "c:\\halo\\SOURCE\\units\\units.c", 0x1c8e, 1);
    system_exit(-1);
  }

  unit[grenade_type + 0x2ce] += (char)grenade_count;
  unit[0x2cd] = (char)grenade_type;
  unit[0x2cc] = (char)grenade_type;

  return (int16_t)unit[grenade_type + 0x2ce];
}

/* unit_pickup_equipment (0x1aab20)
 *
 * Attempts to pick up an equipment object for a unit. Validates that the
 * equipment's powerup_type is neither _equipment_powerup_none (0) nor
 * _equipment_powerup_grenade (6). If the unit already holds equipment
 * (unit+0x2C8 != NONE) and flag==1, deletes the existing equipment first.
 * If the equipment slot is free, detaches the equipment from the map,
 * hides it, attaches it to the unit, and triggers any pickup sound effect
 * if the unit has a controlling player. Returns true on success. */
bool unit_pickup_equipment(int unit_handle, int equipment_handle, short flag)
{
  int *equipment_obj;
  int equipment_def;
  char *unit_obj;
  int player_handle;
  char *player;

  equipment_obj = (int *)object_get_and_verify_type(equipment_handle, 8);
  equipment_def = (int)tag_get(0x65716970, *equipment_obj);
  unit_obj = (char *)object_get_and_verify_type(unit_handle, 3);

  if (*(short *)(equipment_def + 0x308) == 0) {
    display_assert(
      "equipment_definition->equipment.powerup_type!=_equipment_powerup_none",
      "c:\\halo\\SOURCE\\units\\units.c", 0x1ca1, 1);
    system_exit(NONE);
  }
  if (*(short *)(equipment_def + 0x308) == 6) {
    display_assert("equipment_definition->equipment.powerup_type!=_equipment_"
                   "powerup_grenade",
                   "c:\\halo\\SOURCE\\units\\units.c", 0x1ca2, 1);
    system_exit(NONE);
  }

  if (*(int *)(unit_obj + 0x2c8) != NONE && flag == 1) {
    object_delete(*(int *)(unit_obj + 0x2c8));
    *(int *)(unit_obj + 0x2c8) = NONE;
  }

  if (*(int *)(unit_obj + 0x2c8) == NONE) {
    /* detach equipment from map and hide it */
    object_disconnect_from_map(equipment_handle);
    object_set_garbage(equipment_handle, 0);

    /* if the unit has a controlling player, trigger the pickup sound */
    player_handle = player_index_from_unit_index(unit_handle);
    if (player_handle != NONE) {
      player_handle = player_index_from_unit_index(unit_handle);
      player = (char *)datum_get(player_data, player_handle);
      if (*(short *)(player + 0x2) != NONE) {
        item_activate_equipment_effect(equipment_handle);
      }
    }

    /* attach equipment to unit */
    item_attach_to_unit(equipment_handle, unit_handle);
    *(int *)(unit_obj + 0x2c8) = equipment_handle;
    return true;
  }

  return false;
}

/* unit_clear_seat_tag (0x1aac40)
 *
 * Clears the unit's equipment/seat tag handle at offset 0x2C8
 * (unit_data_t.unk_712). If the current value is not NONE (-1), it calls
 * object_delete (0x140cc0) on that handle to destroy the associated object,
 * then sets the field to NONE. Resolves the unit via
 * object_get_and_verify_type with type mask 3 (biped | vehicle).
 */
void unit_clear_seat_tag(int unit_handle)
{
  unit_data_t *unit;

  unit = (unit_data_t *)object_get_and_verify_type(unit_handle, 3);
  if (unit->unk_712.value != -1) {
    object_delete(unit->unk_712.value);
    unit->unk_712.value = -1;
  }
}

/* unit_clear_weapons (0x1aac80)
 *
 * Deletes all weapons from a unit's weapon slots EXCEPT the one at the
 * current weapon index (unk_674, offset 0x2A2). For each of the 4 weapon
 * slots: if the slot is occupied (handle != NONE) and the slot index does
 * not match the current weapon index, deletes the weapon object and clears
 * the slot handle to NONE. Also resets the next-weapon index (unk_676,
 * offset 0x2A4) or current-weapon index (unk_674) to NONE if they matched
 * the cleared slot. Called by unit_enter_seat when flag==2 to strip all
 * secondary weapons before seating.
 */
void unit_clear_weapons(int unit_handle)
{
  unit_data_t *unit;
  int16_t i;

  unit = (unit_data_t *)object_get_and_verify_type(unit_handle, 3);

  for (i = 0; i < MAXIMUM_WEAPONS_PER_UNIT; i++) {
    if (unit->unk_680[i].value != -1 && i != (int16_t)unit->unk_674) {
      object_delete(unit->unk_680[i].value);
      unit->unk_680[i].value = -1;
      if (i == (int16_t)unit->unk_676) {
        unit->unk_676 = (uint16_t)-1;
      }
      if (i == (int16_t)unit->unk_674) {
        unit->unk_674 = (uint16_t)-1;
      }
    }
  }
}

/* unit_find_empty_weapon_slot (0x1aad60)
 *
 * Scans the unit's 4 weapon slots (unit_data_t.unk_680, offset 0x2A8)
 * for the first slot containing NONE (-1) and returns its index (0-3).
 * Returns -1 if all slots are occupied.
 *
 * Register arg: unit_handle passed in EAX.
 *
 * Confirmed: PUSH 0x3 / PUSH EAX -> object_get_and_verify_type(handle, 3).
 * Confirmed: CMP dword ptr [EAX + ESI*4 + 0x2a8], -1 — weapon slot check.
 * Confirmed: CMP CX, 0x4 — loop bound is 4 (MAXIMUM_WEAPONS_PER_UNIT).
 * Confirmed: Returns int16_t (MOV AX,CX / MOV AX,DX).
 */
int16_t unit_find_empty_weapon_slot(int unit_handle)
{
  unit_data_t *unit;
  int16_t i;

  unit = (unit_data_t *)object_get_and_verify_type(unit_handle, 3);

  for (i = 0; i < MAXIMUM_WEAPONS_PER_UNIT; i++) {
    if (unit->unk_680[i].value == -1)
      return i;
  }
  return -1;
}

/* unit_count_weapons (0x1aad90)
 *
 * Counts the number of "countable" weapons held by a unit. Iterates all 4
 * weapon slots (unit_data_t.unk_680, offset 0x2A8). For each non-NONE slot,
 * resolves the weapon object, looks up its weapon tag via tag_get("weap"),
 * and checks byte at tag+0x308 bit 0x10. Weapons without that bit set are
 * counted. Returns the count as int16_t.
 */
int16_t unit_count_weapons(int unit_handle)
{
  unit_data_t *unit;
  int count;
  int weapon_handle;
  int *weapon_obj;
  char *weapon_tag;
  int i;

  unit = (unit_data_t *)object_get_and_verify_type(unit_handle, 3);
  count = 0;

  for (i = 0; i < MAXIMUM_WEAPONS_PER_UNIT; i++) {
    weapon_handle = unit->unk_680[i].value;
    if (weapon_handle != -1) {
      weapon_obj = (int *)object_get_and_verify_type(weapon_handle, 4);
      weapon_tag = (char *)tag_get(0x77656170, *weapon_obj);
      if ((*(uint8_t *)(weapon_tag + 0x308) & 0x10) == 0) {
        count++;
      }
    }
  }

  return (int16_t)count;
}

/* unit_weapon_is_new (0x1aae00)
 *
 * Returns true if the given weapon is "new" to the unit — i.e. no existing
 * weapon in the unit's 4 weapon slots shares the same tag definition (first
 * dword of the weapon object data, the tag_index). Resolves the target weapon
 * via object_get_and_verify_type with type mask 4 (weapon), then iterates all
 * weapon slots comparing tag indices. If any match is found, returns false;
 * otherwise returns true.
 */
bool unit_weapon_is_new(int unit_handle, int weapon_unit_handle)
{
  unit_data_t *unit;
  int *target_weapon_obj;
  int *slot_weapon_obj;
  bool is_new;
  int weapon_handle;
  int i;

  unit = (unit_data_t *)object_get_and_verify_type(unit_handle, 3);
  target_weapon_obj = (int *)object_get_and_verify_type(weapon_unit_handle, 4);
  tag_get(0x77656170, *target_weapon_obj);
  is_new = true;

  for (i = 0; i < MAXIMUM_WEAPONS_PER_UNIT; i++) {
    weapon_handle = unit->unk_680[i].value;
    if (weapon_handle != -1) {
      slot_weapon_obj = (int *)object_get_and_verify_type(weapon_handle, 4);
      if (*target_weapon_obj == *slot_weapon_obj) {
        is_new = false;
      }
    }
  }

  return is_new;
}

/* unit_get_grenade_count (0x1aae70)
 *
 * Returns the current grenade count for the given grenade_type from the
 * unit's grenade count array at unit+0x2CE. If grenade_type is NONE (-1),
 * returns 0 without reading the array. The count byte is sign-extended to
 * int16_t before return.
 *
 * Asserts: grenade_type == NONE || (0 <= grenade_type <
 * NUMBER_OF_UNIT_GRENADE_TYPES).
 *
 * Confirmed: MOV SI,[EBP+0xC] -> grenade_type is short at +0xC.
 * Confirmed: CMP SI,-0x1 / JZ -> NONE check precedes range assert.
 * Confirmed: MOVSX AX,byte ptr [ECX+EDI+0x2CE] -> sign-extended byte return.
 * Confirmed: XOR AX,AX in NONE branch -> return 0.
 */
int16_t unit_get_grenade_count(int unit_handle, int16_t grenade_type)
{
  char *unit;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);

  if (grenade_type == -1)
    return 0;

  if ((grenade_type < 0) || (grenade_type > 1)) {
    display_assert("grenade_type==NONE || (grenade_type>=0 && "
                   "grenade_type<NUMBER_OF_UNIT_GRENADE_TYPES)",
                   "c:\\halo\\SOURCE\\units\\units.c", 0x1ea7, 1);
    system_exit(-1);
  }

  return (int16_t)unit[grenade_type + 0x2ce];
}

/* unit_get_current_grenade_type (0x1aaee0)
 *
 * Returns the current grenade type index for the given unit. Validates
 * that the stored index at unit+0x2cc is NONE (-1) or in [0, 2).
 * Returns -1 (NONE) or 0/1 as a sign-extended int16_t.
 *
 * Confirmed: cdecl, 1 stack param (unit_handle).
 * Confirmed: object_get_and_verify_type(param_1, 3).
 * Confirmed: assert string at 0x2b6c98, line 0x1eb8.
 * Confirmed: sign-extends byte at +0x2cc to int16_t return.
 */
int16_t unit_get_current_grenade_type(int unit_handle)
{
  char *unit;
  char grenade_index;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  grenade_index = *(char *)(unit + 0x2cc);

  if (grenade_index != -1 && (grenade_index < 0 || grenade_index > 1)) {
    display_assert(
        "unit->unit.current_grenade_index==NONE || "
        "(unit->unit.current_grenade_index>=0 && "
        "unit->unit.current_grenade_index<NUMBER_OF_UNIT_GRENADE_TYPES)",
        "c:\\halo\\SOURCE\\units\\units.c", 0x1eb8, 1);
    system_exit(-1);
  }

  return (int16_t)(signed char)*(char *)(unit + 0x2cc);
}

/* FUN_001ab6e0 (0x1ab6e0)
 * Returns a pointer to the base seat name string given a base_seat_index.
 * Asserts that the index is in [0, NUMBER_OF_UNIT_BASE_SEATS).
 * The seat name table at 0x32e484 contains: asleep, alert, stand, crouch, flee, flaming. */
const char *FUN_001ab6e0(int16_t base_seat_index)
{
  if (base_seat_index < 0 || base_seat_index >= NUMBER_OF_UNIT_BASE_SEATS) {
    display_assert(
        "base_seat_index>=0 && base_seat_index<NUMBER_OF_UNIT_BASE_SEATS",
        "c:\\halo\\SOURCE\\units\\units.c", 0x200f, 1);
    system_exit(-1);
  }
  return *(const char **)(0x32e484 + (int)base_seat_index * 4);
}

/* FUN_001ab730 (0x1ab730)
 * Searches the base seat name table for a matching name (case-insensitive).
 * Returns the index [0..5] if found, or -1 if no match.
 * @edi = seat_name string to search for. */
int16_t FUN_001ab730(const char *seat_name)
{
  int16_t i;

  for (i = 0; i < NUMBER_OF_UNIT_BASE_SEATS; i++) {
    if (crt_stricmp(seat_name,
                    *(const char **)(0x32e484 + (int)i * 4)) == 0) {
      return i;
    }
  }
  return -1;
}

/* FUN_001ab770 (0x1ab770)
 * Returns a pointer to the base weapon name string given a base_weapon_index.
 * Asserts that the index is in [0, NUMBER_OF_UNIT_BASE_WEAPONS).
 * The weapon name table is a local array containing just "unarmed". */
const char *FUN_001ab770(int16_t base_weapon_index)
{
  const char *weapon_names[1];

  weapon_names[0] = "unarmed";

  if (base_weapon_index < 0 || base_weapon_index >= NUMBER_OF_UNIT_BASE_WEAPONS) {
    display_assert(
        "base_weapon_index>=0 && "
        "base_weapon_index<NUMBER_OF_UNIT_BASE_WEAPONS",
        "c:\\halo\\SOURCE\\units\\units.c", 0x2043, 1);
    system_exit(-1);
  }
  return weapon_names[base_weapon_index];
}

/* unit_set_animation (0x1ab7c0)
 *
 * Sets the current animation on a unit object. Writes the animation graph
 * tag index to offset 0x7c, the animation index (int16_t) to offset 0x80,
 * and zeroes the animation frame counter at offset 0x82. When the debug
 * flag at 0x5054fc is set, logs the unit name and animation name to the
 * console via console_printf, optionally filtered by the debug unit handle
 * at 0x5ac9f8.
 */
void unit_set_animation(int unit_handle, int anim_graph_tag_index,
                        int16_t animation_index)
{
  int *unit;
  const char *anim_name;
  int debug_filter;
  void *tag_data;

  unit = (int *)object_get_and_verify_type(unit_handle, 3);

  /* Set animation graph tag index, animation index, and zero frame counter */
  *(int *)((char *)unit + 0x7c) = anim_graph_tag_index;
  *(int16_t *)((char *)unit + 0x80) = animation_index;
  *(int16_t *)((char *)unit + 0x82) = 0;

  /* Debug logging path */
  if (*(char *)0x5054fc != 0) {
    anim_name = "<none>";
    if (anim_graph_tag_index != -1) {
      tag_data = tag_get(0x616e7472, anim_graph_tag_index);
      if (animation_index != -1) {
        anim_name = (const char *)tag_block_get_element(
          (char *)tag_data + 0x74, (int)animation_index, 0xb4);
      }
    }

    debug_filter = *(int *)0x5ac9f8;
    if (debug_filter == -1 || *(int *)((char *)unit + 0x1a4) == debug_filter ||
        *(int *)((char *)unit + 0x1a8) == debug_filter) {
      console_printf(0, "%s: animation %s",
                     tag_name_strip_path(tag_get_name(*(int *)unit)),
                     anim_name);
    }
  }
}

/* FUN_001ab870 (0x1ab870) — XBE naked draft (batch 69). */
#if defined(__clang__)
static int (*const b1ab870_c121c30)(int update_kind, int animation_graph_tag_index, short *state, int *out_sound) = animation_update_internal;
static int (*const b1ab870_c1c7e70)(int object_handle, int tag_index, int16_t marker, float *position, float *forward, float scale) = object_impulse_sound_new;

__attribute__((naked, noinline))
int16_t FUN_001ab870(void *animation_state __attribute__((unused)), int animation_graph_tag_index __attribute__((unused)), int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c121c30]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001ab870_1\n\t"
      "movl 0x31fc3c, %%ecx\n\t"
      "movl 0x31fc1c, %%edx\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c7e70]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_001ab870_1:\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c121c30] "m"(b1ab870_c121c30), [c1c7e70] "m"(b1ab870_c1c7e70)
      : "memory");
}
#else
#error "FUN_001ab870: clang naked draft required"
#endif


/* FUN_001ab8c0 (0x1ab8c0) — XBE naked draft (batch 67). */
#if defined(__clang__)
static void *(*const b1ab8c0_get)(int, int) = object_get_and_verify_type;
static void *(*const b1ab8c0_tryget)(int, int) = object_try_and_get_and_verify_type;
static void (*const b1ab8c0_c13a740)(int param_1, int param_2, float *param_3) = FUN_0013a740;
static float (*const b1ab8c0_c7a750)(float *color) = real_rgb_color_brightness;
static float (*const b1ab8c0_c1393b0)(int object_handle) = object_get_self_illumination;

__attribute__((naked, noinline))
void FUN_001ab8c0(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001ab8c0_1\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x48(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0xc(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13a740]\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7a750]\n\t"
      "fstps 0x290(%%esi)\n\t"
      "pushl %%edi\n\t"
      "call *%[c1393b0]\n\t"
      "fstps 0x294(%%esi)\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001ab8c0_1:\n\t"
      "movl 0x290(%%eax), %%edx\n\t"
      "movl %%edx, 0x290(%%esi)\n\t"
      "movl 0x294(%%eax), %%eax\n\t"
      "movl %%eax, 0x294(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1ab8c0_get), [tryget] "m"(b1ab8c0_tryget), [c13a740] "m"(b1ab8c0_c13a740), [c7a750] "m"(b1ab8c0_c7a750), [c1393b0] "m"(b1ab8c0_c1393b0)
      : "memory");
}
#else
#error "FUN_001ab8c0: clang naked draft required"
#endif


/* FUN_001ab940 (0x1ab940)
 * Returns the weapon handle at the given weapon slot index for a unit.
 * The index is validated against [0, MAXIMUM_WEAPONS_PER_UNIT).
 * Returns -1 (NONE) if the index is -1. */
int FUN_001ab940(int16_t weapon_index, char *unit_data)
{
  if (weapon_index == -1) {
    return -1;
  }
  if (weapon_index < 0 || weapon_index >= MAXIMUM_WEAPONS_PER_UNIT) {
    display_assert("index>=0 && index<MAXIMUM_WEAPONS_PER_UNIT",
                   "c:\\halo\\SOURCE\\units\\units.c", 0x20ac, 1);
    system_exit(-1);
  }
  return *(int *)(unit_data + 0x2a8 + (int)weapon_index * 4);
}

/* unit_detach_weapon (0x1ab990)
 *
 * Detaches a weapon/item from a unit. If the item has no parent, connects it
 * to the map and attaches it at the unit's "left hand" marker. If it has a
 * parent, asserts that the parent is the unit. Then detaches the item from
 * the unit, clears its velocity, generates a random direction offset based on
 * the unit's unk_492 facing vector with a small random angle and scale, adds
 * that to the root position, and attempts to place the item at the new
 * position. If placement fails and the game engine is not running, deletes
 * the item. Also deletes if the unit has flag bit 0x100000 set in unk_436.
 *
 * Register args: unit_handle in EDI, weapon_handle in ESI.
 *
 * Confirmed: PUSH 0x3 / PUSH EDI -> object_get_and_verify_type(unit, 3).
 * Confirmed: PUSH 0x1c / PUSH ESI -> object_get_and_verify_type(weapon, 0x1c).
 * Confirmed: parent check at [EBX+0xCC] against -1 and EDI.
 * Confirmed: object_attach_to_marker(edi, "left hand", esi, "").
 * Confirmed: item_attach_to_unit(esi, -1) to detach.
 * Confirmed: global zero vector copied from [0x31fc38].
 * Confirmed: assert "item->object.parent_object_index==unit_index" at 0x20c5.
 * Confirmed: random_direction3d with angle 0x3ec90fdb, scale range [0x3cda740e,
 * 0x3d23d70b]. Confirmed: [EBX+0x1b0] = EDI (weapon remembers its detaching
 * unit). Confirmed: flag check at unit+0x1b4 bit 0x100000.
 */
void unit_detach_weapon(int unit_handle, int weapon_handle)
{
  char *unit;
  char *weapon;
  int parent;
  float *global_origin;
  float direction[3];
  float position[3];
  int *seed;
  float scale;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  weapon = (char *)object_get_and_verify_type(weapon_handle, 0x1c);
  parent = *(int *)(weapon + 0xcc);

  if (parent == -1) {
    /* Weapon has no parent — connect to map and attach at marker */
    object_connect_to_map(weapon_handle, 0);
    object_set_garbage(weapon_handle, 1);
    object_attach_to_marker(unit_handle, (void *)0x2b6d2c, weapon_handle,
                            (void *)0x25386f);
  } else if (parent != unit_handle) {
    display_assert("item->object.parent_object_index==unit_index",
                   "c:\\halo\\SOURCE\\units\\units.c", 0x20c5, 1);
    system_exit(-1);
  }

  /* Detach weapon from unit and parent */
  item_attach_to_unit(weapon_handle, -1);
  object_detach_from_parent(weapon_handle);

  /* Zero the weapon's velocity fields at +0x18 and +0x3c */
  global_origin = *(float **)0x31fc38;
  *(float *)(weapon + 0x18) = global_origin[0];
  *(float *)(weapon + 0x1c) = global_origin[1];
  *(float *)(weapon + 0x20) = global_origin[2];

  global_origin = *(float **)0x31fc38;
  *(float *)(weapon + 0x3c) = global_origin[0];
  *(float *)(weapon + 0x40) = global_origin[1];
  *(float *)(weapon + 0x44) = global_origin[2];

  /* Generate random throw direction from unit's facing vector (unk_492) */
  seed = get_global_random_seed_address();
  random_direction3d(seed, (float *)(unit + 0x1ec), 0.0f, 0.39269909f,
                     direction);

  /* Scale direction by random amount */
  seed = get_global_random_seed_address();
  scale = random_real_range(seed, 0.02666667f, 0.04f);
  direction[0] *= scale;
  direction[1] *= scale;
  direction[2] *= scale;

  /* Get root parent position and offset by scaled direction */
  object_get_root_location(unit_handle, position, 0);
  direction[0] = position[0] + direction[0];
  direction[1] = position[1] + direction[1];
  direction[2] = position[2] + direction[2];

  /* Record the detaching unit on the weapon */
  *(int *)(weapon + 0x1b0) = unit_handle;

  /* Set weapon position and try to place it */
  item_set_position(weapon_handle, direction, 0);
  unit_set_seat_state(unit_handle, position);

  if (!object_try_place(weapon_handle, position)) {
    if (!game_engine_running()) {
      object_delete(weapon_handle);
    }
  }

  /* If unit has death/despawn flag, force-delete the weapon */
  if (*(uint32_t *)(unit + 0x1b4) & 0x100000) {
    object_delete(weapon_handle);
  }
}

/* unit_has_weapon_with_flag (0x1ac3f0)
 *
 * Returns true if any of the unit's equipped weapons has the given flag
 * bit set in its flags field (weapon_data+0x1dc).
 *
 * Walks the 4-slot weapon handle array at unit+0x2a8; for each slot that
 * is not NONE (-1), resolves the weapon object with type_mask=4 and tests
 * bit (1 << flag_index) against the 32-bit flags at weapon_data+0x1dc.
 *
 * Confirmed: LEA ESI,[EAX+0x2a8] — weapon slot array at unit+0x2a8.
 * Confirmed: PUSH 0x4 for weapon type_mask in inner object_get_and_verify_type.
 * Confirmed: MOV ECX,BX; SHL EDX,CL — flag_index used as shift count (byte).
 * Confirmed: CMP EAX,-0x1 / JZ skip — slot NONE guard.
 * Confirmed: TEST EDX,ECX at [EAX+0x1dc] — flags field at +0x1dc.
 */
bool unit_has_weapon_with_flag(int unit_handle, int flag_index)
{
  int *unit;
  int *weapon_slots;
  int i;

  unit = (int *)object_get_and_verify_type(unit_handle, 3);
  weapon_slots = (int *)((char *)unit + 0x2a8);

  for (i = 0; i < 4; i++) {
    if (weapon_slots[i] != NONE) {
      int *weapon = (int *)object_get_and_verify_type(weapon_slots[i], 4);
      if ((1 << (flag_index & 0x1f)) & *(uint32_t *)((char *)weapon + 0x1dc))
        return 1;
    }
  }
  return 0;
}

/* unit_try_animation_state (0x1acd70)
 *
 * Searches the unit's animation graph for a matching animation mode and
 * weapon label. The animation graph is resolved via: unit tag -> antr tag
 * at offset +0x44. The antr tag's animation modes block starts at tag+0xc.
 *
 * For each mode:
 *   - If seat_label is non-NULL, compares it (case-insensitive) against the
 *     mode's name string; skips non-matching modes.
 *   - Within the mode, iterates sub-animations at mode+0x58 (size 0xBC each).
 *   - Within each sub-animation, iterates weapon labels at sub_anim+0xB0
 *     (size 0x3C each).
 *   - Matches weapon_label: NULL matches anything; "unarmed" matches empty
 *     strings; otherwise case-insensitive compare.
 *
 * If reset_flag is 0, returns true on first match without updating state.
 * If reset_flag is non-zero, updates the unit's animation state fields:
 *   - unk_592 (0x250) = mode index
 *   - unk_593 (0x251) = sub-animation index
 *   - unk_594 (0x252) = weapon label index
 *   - base_seat_index (0x257) = matched base seat label index (-1 if none)
 *   - unk_595 (0x253) = 0xff if previously != 0x1c
 *   - unk_584 (0x248) bit 1: set if mode has multi-weapon animation channels
 *
 * Register arg: unit_handle passed in EAX.
 *
 * Confirmed: PUSH 0x3 / PUSH EAX -> object_get_and_verify_type.
 * Confirmed: tag_get('unit', *unit) then tag_get('antr', unit_tag+0x44).
 * Confirmed: stricmp via CALL 0x1dd801.
 * Confirmed: csstrcmp via CALL 0x8dcb0 for "unarmed" check.
 * Confirmed: stores to offsets 0x250, 0x251, 0x252, 0x253, 0x257, 0x248.
 * Confirmed: base_seat_labels table at 0x32e484, 6 entries.
 */
bool unit_try_animation_state(int unit_handle, int seat_label, int weapon_label,
                              int reset_flag)
{
  char *unit;
  char *unit_tag;
  char *antr_tag;
  int *anim_block;
  int mode_count;
  int mode_index;
  char *mode;
  int sub_count;
  int16_t sub_index;
  char *sub_anim;
  int *weapon_block;
  int weapon_count;
  int16_t weapon_index;
  char *weapon_name;
  bool found;
  bool has_multi_weapon;
  int16_t base_seat;
  int16_t si;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (char *)tag_get(0x756e6974, *(int *)unit);
  antr_tag = (char *)tag_get(0x616e7472, *(int *)(unit_tag + 0x44));
  anim_block = (int *)(antr_tag + 0xc);
  mode_count = *anim_block;
  found = false;

  if (mode_count < 1)
    return false;

  mode_index = 0;
  while (1) {
    mode = (char *)tag_block_get_element(anim_block, mode_index, 0x64);

    if (seat_label != 0 && crt_stricmp((const char *)seat_label, mode) != 0) {
      goto next_mode;
    }

    sub_count = *(int *)(mode + 0x58);
    sub_index = 0;
    if (sub_count < 1)
      goto next_mode;

    while (1) {
      sub_anim =
        (char *)tag_block_get_element(mode + 0x58, (int)sub_index, 0xbc);
      weapon_block = (int *)(sub_anim + 0xb0);
      weapon_count = *weapon_block;
      weapon_index = 0;

      if (weapon_count < 1)
        goto next_sub;

      while (1) {
        weapon_name =
          (char *)tag_block_get_element(weapon_block, (int)weapon_index, 0x3c);

        if (weapon_label == 0)
          goto matched;
        if (csstrcmp((const char *)weapon_label, "unarmed") == 0 &&
            *weapon_name == '\0')
          goto matched;
        if (crt_stricmp((const char *)weapon_label, weapon_name) == 0)
          goto matched;

        weapon_index++;
        if ((int)(int16_t)weapon_index >= weapon_count)
          goto next_sub;
        continue;

      matched:
        if (reset_flag == 0)
          goto found_match;

        /* Check if mode has multi-weapon animation channels */
        {
          int num_key_types = *(int *)(mode + 0x40);
          int *key_data = *(int **)(mode + 0x44);
          has_multi_weapon = false;

          if ((num_key_types >= 3 && *(int16_t *)(key_data + 1) != -1) ||
              (num_key_types >= 4 &&
               *(int16_t *)((char *)key_data + 6) != -1) ||
              (num_key_types >= 5 &&
               *(int16_t *)((char *)key_data + 8) != -1)) {
            has_multi_weapon = true;
          }
        }

        if (*(uint8_t *)(unit + 0x253) != 0x1c)
          *(uint8_t *)(unit + 0x253) = 0xff;

        *(uint8_t *)(unit + 0x250) = (uint8_t)mode_index;

        /* Find base_seat_index by matching seat_label against table */
        base_seat = -1;
        for (si = 0; si < NUMBER_OF_UNIT_BASE_SEATS; si++) {
          if (crt_stricmp((const char *)seat_label,
                          *(const char **)(0x32e484 + si * 4)) == 0) {
            base_seat = si;
            break;
          }
        }

        *(uint8_t *)(unit + 0x252) = (uint8_t)weapon_index;
        *(int8_t *)(unit + 0x257) = (int8_t)base_seat;
        *(uint8_t *)(unit + 0x251) = (uint8_t)sub_index;

        if (has_multi_weapon) {
          *(uint8_t *)(unit + 0x248) |= 0x2;
        } else {
          *(uint8_t *)(unit + 0x248) &= ~0x2;
        }

      found_match:
        found = true;
        goto next_sub;
      }

    next_sub:
      sub_index++;
      if ((int)(int16_t)sub_index >= *(int *)(mode + 0x58))
        goto next_mode;
    }

  next_mode:
    mode_index++;
    if ((int)(int16_t)mode_index >= *anim_block)
      break;
  }

  return found;
}

/* FUN_001ad260 (0x1ad260) — XBE naked draft (batch 56). */
#if defined(__clang__)
static void *(*const b1ad260_get)(int, int) = object_get_and_verify_type;
static void *(*const b1ad260_tag)(int, int) = tag_get;
static void *(*const b1ad260_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1ad260_c1ab110)(int unit_handle, char flag) = FUN_001ab110;
static const char * (*const b1ad260_c1205f0)(void *string_table, int16_t index) = FUN_001205f0;
static const char * (*const b1ad260_c19b0d0)(const char *tag_name) = tag_name_strip_path;
static void (*const b1ad260_cff550)(const char* format, ...) = console_warning;
static int (*const b1ad260_c120f20)(int update_kind, int animation_graph_tag_index, int16_t animation_index) = model_animation_choose_random;
static void (*const b1ad260_c1ab7c0)(int unit_handle, int anim_graph_tag_index, int16_t animation_index) = unit_set_animation;
static int (*const b1ad260_c1a88b0)(int16_t anim_state) = FUN_001a88b0;
static void (*const b1ad260_c140160)(int object_handle, int16_t region_count) = object_set_region_count;

__attribute__((naked, noinline))
char FUN_001ad260(int unit_handle __attribute__((unused)), int16_t anim_state __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0x44(%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x616e7472\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movsbl 0x250(%%esi), %%ecx\n\t"
      "pushl $0x64\n\t"
      "pushl %%ecx\n\t"
      "addl $0xc, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movsbl 0x251(%%esi), %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $0xbc\n\t"
      "pushl %%edx\n\t"
      "leal 0x58(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, -0x1c(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movsbl 0x252(%%esi), %%ecx\n\t"
      "pushl $0x3c\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "addl $0xb0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movb 0x253(%%esi), %%al\n\t"
      "addl $0x3c, %%esp\n\t"
      "cmpb $0xff, %%al\n\t"
      "sete %%bl\n\t"
      "xorb %%dl, %%dl\n\t"
      "testb %%bl, %%bl\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "jne .LFUN_001ad260_1\n\t"
      "movsbw %%al, %%cx\n\t"
      "cmpw %%cx, 0xc(%%ebp)\n\t"
      "movw %%cx, -0x14(%%ebp)\n\t"
      "je .LFUN_001ad260_58\n\t"
      ".LFUN_001ad260_1:\n\t"
      "orl $0xffffffff, %%edx\n\t"
      "cmpb $0x21, %%al\n\t"
      "movl %%edx, %%ebx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jne .LFUN_001ad260_2\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "call *%[c1ab110]\n\t"
      "addl $8, %%esp\n\t"
      "orl $0xffffffff, %%edx\n\t"
      ".LFUN_001ad260_2:\n\t"
      "movswl 0xc(%%ebp), %%eax\n\t"
      "cmpl $0x2b, %%eax\n\t"
      "ja .LFUN_001ad260_43\n\t"
      "jmp *.LFUN_001ad260_jt0(,%%eax,4)\n\t"
      ".LFUN_001ad260_3:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      ".LFUN_001ad260_4:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movswl %%bx, %%eax\n\t"
      "cmpl 0x98(%%ecx), %%eax\n\t"
      "jge .LFUN_001ad260_43\n\t"
      "movl 0x9c(%%ecx), %%ecx\n\t"
      "movw (%%ecx,%%eax,2), %%ax\n\t"
      "movw %%ax, -0xc(%%ebp)\n\t"
      "jmp .LFUN_001ad260_44\n\t"
      ".LFUN_001ad260_5:\n\t"
      "movl $1, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_6:\n\t"
      "movl $2, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_7:\n\t"
      "movl $3, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_8:\n\t"
      "movl $8, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_9:\n\t"
      "movl $9, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_10:\n\t"
      "movl $0xa, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_11:\n\t"
      "movl $0xb, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_12:\n\t"
      "movl $0x23, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_13:\n\t"
      "movl $0x24, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_14:\n\t"
      "movl $0x25, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_15:\n\t"
      "movl $0x26, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_16:\n\t"
      "movl $0xc, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_17:\n\t"
      "movl $0xd, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_18:\n\t"
      "movl $0xe, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_19:\n\t"
      "movl $0xf, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_20:\n\t"
      "movl $0x10, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_21:\n\t"
      "movl $0x11, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_22:\n\t"
      "movl $0x12, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_23:\n\t"
      "movl $0x14, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_24:\n\t"
      "movl $0x27, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_25:\n\t"
      "movl $0x2a, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_26:\n\t"
      "movl $0x2e, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_27:\n\t"
      "movl $0x2c, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_28:\n\t"
      "movl $0x2d, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_29:\n\t"
      "movl $0x2f, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_30:\n\t"
      "movl $0x30, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_31:\n\t"
      "movl $0x31, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_32:\n\t"
      "movl $0x32, %%ebx\n\t"
      "jmp .LFUN_001ad260_4\n\t"
      ".LFUN_001ad260_33:\n\t"
      "movl $0x17, %%eax\n\t"
      ".LFUN_001ad260_34:\n\t"
      "movl 0x40(%%edi), %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .LFUN_001ad260_43\n\t"
      "movl 0x44(%%edi), %%ecx\n\t"
      "movw (%%ecx,%%eax,2), %%ax\n\t"
      "movw %%ax, -0xc(%%ebp)\n\t"
      "jmp .LFUN_001ad260_44\n\t"
      ".LFUN_001ad260_35:\n\t"
      "movl $0x18, %%eax\n\t"
      "jmp .LFUN_001ad260_34\n\t"
      ".LFUN_001ad260_36:\n\t"
      "movl $0x19, %%eax\n\t"
      "jmp .LFUN_001ad260_34\n\t"
      ".LFUN_001ad260_37:\n\t"
      "movl $0x1a, %%eax\n\t"
      "jmp .LFUN_001ad260_34\n\t"
      ".LFUN_001ad260_38:\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001ad260_34\n\t"
      ".LFUN_001ad260_39:\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_001ad260_34\n\t"
      ".LFUN_001ad260_40:\n\t"
      "movl $0x1b, %%eax\n\t"
      "jmp .LFUN_001ad260_34\n\t"
      ".LFUN_001ad260_41:\n\t"
      "movl $0x1c, %%eax\n\t"
      "jmp .LFUN_001ad260_34\n\t"
      ".LFUN_001ad260_42:\n\t"
      "movl $0x1d, %%eax\n\t"
      "jmp .LFUN_001ad260_34\n\t"
      ".LFUN_001ad260_43:\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      ".LFUN_001ad260_44:\n\t"
      "movb 0x5054fb, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001ad260_49\n\t"
      "cmpw $0, 0x64(%%esi)\n\t"
      "jne .LFUN_001ad260_49\n\t"
      "cmpw %%dx, -0xc(%%ebp)\n\t"
      "jne .LFUN_001ad260_52\n\t"
      "cmpw %%dx, %%bx\n\t"
      "je .LFUN_001ad260_45\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x322308\n\t"
      "call *%[c1205f0]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "orl $0xffffffff, %%edx\n\t"
      "jmp .LFUN_001ad260_46\n\t"
      ".LFUN_001ad260_45:\n\t"
      "movl $0x25386f, %%ebx\n\t"
      ".LFUN_001ad260_46:\n\t"
      "cmpw %%dx, -0x8(%%ebp)\n\t"
      "je .LFUN_001ad260_47\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x322450\n\t"
      "call *%[c1205f0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_001ad260_48\n\t"
      ".LFUN_001ad260_47:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      ".LFUN_001ad260_48:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "movl 0x3c(%%edx), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b0d0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b70bc\n\t"
      "call *%[cff550]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_001ad260_50\n\t"
      ".LFUN_001ad260_49:\n\t"
      "cmpw %%dx, -0xc(%%ebp)\n\t"
      "jne .LFUN_001ad260_52\n\t"
      ".LFUN_001ad260_50:\n\t"
      "movswl 0xc(%%ebp), %%eax\n\t"
      "addl $-0x1e, %%eax\n\t"
      "cmpl $0xb, %%eax\n\t"
      "ja .LFUN_001ad260_52\n\t"
      "movzbl 0x1ad7cc(%%eax), %%ecx\n\t"
      "jmp *.LFUN_001ad260_jt1(,%%ecx,4)\n\t"
      ".LFUN_001ad260_51:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001ad260_52:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl 0x44(%%edi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c120f20]\n\t"
      "movl 0x44(%%edi), %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "call *%[c1ab7c0]\n\t"
      "movsbw 0x253(%%esi), %%ax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "testw %%cx, %%cx\n\t"
      "movw %%ax, -0x14(%%ebp)\n\t"
      "movl $6, %%eax\n\t"
      "je .LFUN_001ad260_53\n\t"
      "cmpw $2, %%cx\n\t"
      "je .LFUN_001ad260_53\n\t"
      "cmpw $3, %%cx\n\t"
      "jne .LFUN_001ad260_55\n\t"
      ".LFUN_001ad260_53:\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "testw %%dx, %%dx\n\t"
      "je .LFUN_001ad260_54\n\t"
      "cmpw $2, %%dx\n\t"
      "je .LFUN_001ad260_54\n\t"
      "cmpw $3, %%dx\n\t"
      "jne .LFUN_001ad260_55\n\t"
      ".LFUN_001ad260_54:\n\t"
      "movl $1, %%eax\n\t"
      ".LFUN_001ad260_55:\n\t"
      "cmpw $0x16, %%cx\n\t"
      "je .LFUN_001ad260_56\n\t"
      "cmpw $0x15, %%cx\n\t"
      "jne .LFUN_001ad260_57\n\t"
      ".LFUN_001ad260_56:\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_001ad260_57:\n\t"
      "movb -0x1(%%ebp), %%bl\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movb $1, %%dl\n\t"
      ".LFUN_001ad260_58:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "call *%[c1a88b0]\n\t"
      "testb %%bl, %%bl\n\t"
      "movl %%eax, %%edi\n\t"
      "jne .LFUN_001ad260_59\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "call *%[c1a88b0]\n\t"
      "cmpw %%ax, %%di\n\t"
      "je .LFUN_001ad260_65\n\t"
      ".LFUN_001ad260_59:\n\t"
      "testw %%di, %%di\n\t"
      "jl .LFUN_001ad260_60\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl 0x98(%%ecx), %%edx\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jge .LFUN_001ad260_60\n\t"
      "movl 0x9c(%%ecx), %%ecx\n\t"
      "movswl (%%ecx,%%eax,2), %%ecx\n\t"
      "jmp .LFUN_001ad260_61\n\t"
      ".LFUN_001ad260_60:\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      ".LFUN_001ad260_61:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl 0x44(%%edx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c120f20]\n\t"
      "movw %%ax, 0x24a(%%esi)\n\t"
      "movb 0x5054fb, %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_001ad260_62\n\t"
      "cmpw $0, 0x64(%%esi)\n\t"
      "jne .LFUN_001ad260_62\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .LFUN_001ad260_62\n\t"
      "cmpw %%ax, %%di\n\t"
      "je .LFUN_001ad260_62\n\t"
      "pushl %%edi\n\t"
      "pushl $0x322308\n\t"
      "call *%[c1205f0]\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x3c(%%edx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b0d0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b70bc\n\t"
      "call *%[cff550]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ad260_62:\n\t"
      "testb %%bl, %%bl\n\t"
      "movl $6, -0xc(%%ebp)\n\t"
      "je .LFUN_001ad260_66\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "cmpl $9, 0x40(%%eax)\n\t"
      "jle .LFUN_001ad260_63\n\t"
      "movl 0x44(%%eax), %%ecx\n\t"
      "movswl 0x12(%%ecx), %%ecx\n\t"
      "jmp .LFUN_001ad260_64\n\t"
      ".LFUN_001ad260_63:\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      ".LFUN_001ad260_64:\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl 0x44(%%edi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c120f20]\n\t"
      "movw %%ax, 0x24c(%%esi)\n\t"
      "movb 0x5054fb, %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_001ad260_66\n\t"
      "cmpw $0, 0x64(%%esi)\n\t"
      "jne .LFUN_001ad260_66\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .LFUN_001ad260_66\n\t"
      "pushl $9\n\t"
      "pushl $0x322450\n\t"
      "call *%[c1205f0]\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "movl 0x3c(%%edi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b0d0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b6950\n\t"
      "call *%[cff550]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_001ad260_66\n\t"
      ".LFUN_001ad260_65:\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_001ad260_67\n\t"
      ".LFUN_001ad260_66:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c140160]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001ad260_67:\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "movb %%al, 0x253(%%esi)\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "addb %%al, (%%eax)\n\t"
      "addb %%al, (%%eax)\n\t"
      "addl %%eax, (%%ecx)\n\t"
      "addl %%eax, (%%ecx)\n\t"
      "addl %%eax, (%%eax)\n\t"
      "addl %%eax, (%%eax)\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_001ad260_jt0:\n\t"
      ".long .LFUN_001ad260_3\n\t"
      ".long .LFUN_001ad260_5\n\t"
      ".long .LFUN_001ad260_6\n\t"
      ".long .LFUN_001ad260_7\n\t"
      ".long .LFUN_001ad260_8\n\t"
      ".long .LFUN_001ad260_9\n\t"
      ".long .LFUN_001ad260_10\n\t"
      ".long .LFUN_001ad260_11\n\t"
      ".long .LFUN_001ad260_12\n\t"
      ".long .LFUN_001ad260_13\n\t"
      ".long .LFUN_001ad260_14\n\t"
      ".long .LFUN_001ad260_15\n\t"
      ".long .LFUN_001ad260_16\n\t"
      ".long .LFUN_001ad260_17\n\t"
      ".long .LFUN_001ad260_18\n\t"
      ".long .LFUN_001ad260_19\n\t"
      ".long .LFUN_001ad260_33\n\t"
      ".long .LFUN_001ad260_35\n\t"
      ".long .LFUN_001ad260_36\n\t"
      ".long .LFUN_001ad260_37\n\t"
      ".long .LFUN_001ad260_20\n\t"
      ".long .LFUN_001ad260_21\n\t"
      ".long .LFUN_001ad260_22\n\t"
      ".long .LFUN_001ad260_43\n\t"
      ".long .LFUN_001ad260_38\n\t"
      ".long .LFUN_001ad260_39\n\t"
      ".long .LFUN_001ad260_43\n\t"
      ".long .LFUN_001ad260_43\n\t"
      ".long .LFUN_001ad260_43\n\t"
      ".long .LFUN_001ad260_43\n\t"
      ".long .LFUN_001ad260_24\n\t"
      ".long .LFUN_001ad260_25\n\t"
      ".long .LFUN_001ad260_26\n\t"
      ".long .LFUN_001ad260_23\n\t"
      ".long .LFUN_001ad260_27\n\t"
      ".long .LFUN_001ad260_28\n\t"
      ".long .LFUN_001ad260_29\n\t"
      ".long .LFUN_001ad260_40\n\t"
      ".long .LFUN_001ad260_41\n\t"
      ".long .LFUN_001ad260_30\n\t"
      ".long .LFUN_001ad260_31\n\t"
      ".long .LFUN_001ad260_32\n\t"
      ".long .LFUN_001ad260_43\n\t"
      ".long .LFUN_001ad260_42\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_001ad260_jt1:\n\t"
      ".long .LFUN_001ad260_51\n\t"
      ".long .LFUN_001ad260_52\n\t"
      ".text\n\t"
      :
      : [get] "m"(b1ad260_get), [tag] "m"(b1ad260_tag), [elem] "m"(b1ad260_elem), [c1ab110] "m"(b1ad260_c1ab110), [c1205f0] "m"(b1ad260_c1205f0), [c19b0d0] "m"(b1ad260_c19b0d0), [cff550] "m"(b1ad260_cff550), [c120f20] "m"(b1ad260_c120f20), [c1ab7c0] "m"(b1ad260_c1ab7c0), [c1a88b0] "m"(b1ad260_c1a88b0), [c140160] "m"(b1ad260_c140160)
      : "memory");
}
#else
#error "FUN_001ad260: clang naked draft required"
#endif


/* unit_find_best_enter_seat (0x1ad800) — XBE naked draft (batch 52). */
#if defined(__clang__)
static void *(*const b1ad800_get)(int, int) = object_get_and_verify_type;
static void *(*const b1ad800_tag)(int, int) = tag_get;
static void *(*const b1ad800_elem)(void *, int, int) = tag_block_get_element;
static int (*const b1ad800_c1a8200)(int unit_handle, int target_unit_handle, int16_t seat_index, float *out_pos_a, float *out_pos_b, float *out_pos_c) = unit_get_seat_enter_position;
static char (*const b1ad800_c1acd70)(int unit_handle, const char *seat_label, const char *weapon_name, char apply_state) = FUN_001acd70;
static bool (*const b1ad800_c1a8ce0)(int unit_handle, int target_unit_handle, int16_t seat_index, int *out_unit_handle) = unit_find_nearby_seat;
static bool (*const b1ad800_c3fdc0)(int ai_handle, int unit_handle, bool flag) = ai_handle_unit_approach;
static void (*const b1ad800_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1ad800_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
uint16_t unit_find_best_enter_seat(int unit_handle __attribute__((unused)), int target_unit_handle __attribute__((unused)), int16_t *out_seat_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x3c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "movl %%esi, -0x24(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movb 0xb6(%%esi), %%cl\n\t"
      "xorl %%edi, %%edi\n\t"
      "addl $0x18, %%esp\n\t"
      "testb $4, %%cl\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "movl $0xffffffff, -0xc(%%ebp)\n\t"
      "jne .Lunit_find_best_enter_seat_12\n\t"
      "testl $0x10000, 0x1b4(%%esi)\n\t"
      "jne .Lunit_find_best_enter_seat_12\n\t"
      "leal 0x2e4(%%eax), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0x7f7fffff, -0x18(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "jle .Lunit_find_best_enter_seat_12\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lunit_find_best_enter_seat_2\n\t"
      ".Lunit_find_best_enter_seat_1:\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lunit_find_best_enter_seat_2:\n\t"
      "pushl $0x11c\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1a8200]\n\t"
      "addl $0x24, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_find_best_enter_seat_11\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "flds 0x50(%%eax)\n\t"
      "fsubs -0x30(%%ebp)\n\t"
      "flds 0x54(%%eax)\n\t"
      "fsubs -0x2c(%%ebp)\n\t"
      "flds 0x58(%%eax)\n\t"
      "fsubs -0x28(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x50(%%eax)\n\t"
      "fsubs -0x3c(%%ebp)\n\t"
      "flds 0x54(%%eax)\n\t"
      "fsubs -0x38(%%ebp)\n\t"
      "flds 0x58(%%eax)\n\t"
      "fsubs -0x34(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fsqrt\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fcoms -0x14(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_find_best_enter_seat_3\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "fstp %%st(0)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jmp .Lunit_find_best_enter_seat_4\n\t"
      ".Lunit_find_best_enter_seat_3:\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".Lunit_find_best_enter_seat_4:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lunit_find_best_enter_seat_11\n\t"
      "movl (%%edi), %%eax\n\t"
      "testb $2, %%ah\n\t"
      "je .Lunit_find_best_enter_seat_5\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "cmpl $-1, 0x2d4(%%eax)\n\t"
      "je .Lunit_find_best_enter_seat_11\n\t"
      ".Lunit_find_best_enter_seat_5:\n\t"
      "movb 0x4(%%edi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "leal 0x4(%%edi), %%eax\n\t"
      "je .Lunit_find_best_enter_seat_11\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c1acd70]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_find_best_enter_seat_11\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl $0xffffffff, -0x14(%%ebp)\n\t"
      "call *%[c1a8ce0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_find_best_enter_seat_6\n\t"
      "movl $2, %%edx\n\t"
      "jmp .Lunit_find_best_enter_seat_7\n\t"
      ".Lunit_find_best_enter_seat_6:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lunit_find_best_enter_seat_11\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0x1a4(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lunit_find_best_enter_seat_11\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c3fdc0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_find_best_enter_seat_11\n\t"
      "movl $1, %%edx\n\t"
      ".Lunit_find_best_enter_seat_7:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "flds 0x2533c8\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "shrl $2, %%ecx\n\t"
      "andb $1, %%cl\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_find_best_enter_seat_8\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lunit_find_best_enter_seat_8\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533ec\n\t"
      ".Lunit_find_best_enter_seat_8:\n\t"
      "cmpw $-1, -0xc(%%ebp)\n\t"
      "je .Lunit_find_best_enter_seat_9\n\t"
      "cmpw -0x10(%%ebp), %%dx\n\t"
      "jg .Lunit_find_best_enter_seat_9\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fcomps -0x18(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lunit_find_best_enter_seat_11\n\t"
      "jmp .Lunit_find_best_enter_seat_10\n\t"
      ".Lunit_find_best_enter_seat_9:\n\t"
      "fstp %%st(0)\n\t"
      ".Lunit_find_best_enter_seat_10:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "movb %%cl, -0x1(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      ".Lunit_find_best_enter_seat_11:\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .Lunit_find_best_enter_seat_1\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      ".Lunit_find_best_enter_seat_12:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lunit_find_best_enter_seat_13\n\t"
      "pushl $1\n\t"
      "pushl $0xff8\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b70d4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movw -0xc(%%ebp), %%dx\n\t"
      "addl $0x14, %%esp\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "movw %%dx, (%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lunit_find_best_enter_seat_13:\n\t"
      "movw -0xc(%%ebp), %%ax\n\t"
      "movw %%ax, (%%esi)\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [get] "m"(b1ad800_get), [tag] "m"(b1ad800_tag), [elem] "m"(b1ad800_elem), [c1a8200] "m"(b1ad800_c1a8200), [c1acd70] "m"(b1ad800_c1acd70), [c1a8ce0] "m"(b1ad800_c1a8ce0), [c3fdc0] "m"(b1ad800_c3fdc0), [assert] "m"(b1ad800_assert), [exitfn] "m"(b1ad800_exitfn)
      : "memory");
}
#else
#error "unit_find_best_enter_seat: clang naked draft required"
#endif


/* unit_clip_to_aiming_bounds (0x1ada90) — XBE naked draft (batch 52). */
#if defined(__clang__)
static void *(*const b1ada90_get)(int, int) = object_get_and_verify_type;
static bool (*const b1ada90_c21fb0)(float *v) = valid_real_normal3d;
static char * (*const b1ada90_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b1ada90_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1ada90_exitfn)(int) = system_exit;
static void (*const b1ada90_c141360)(int object_handle, float *out_forward, float *out_up) = object_get_orientation;
static void (*const b1ada90_c1097f0)(void *matrix, void *point, void *out) = real_matrix4x3_transform_point;
static int (*const b1ada90_c84a10)(float *vector) = real_vector3d_valid;
static void (*const b1ada90_c10cc00)(float *out_angles, float *in_vector) = vector_to_angles;
static void (*const b1ada90_c10cc40)(float *out, float *angles) = angles_to_vector;
static void (*const b1ada90_c109680)(float *matrix, float *in, float *out) = matrix_transform_vector;

__attribute__((naked, noinline))
char unit_clip_to_aiming_bounds(int unit_handle __attribute__((unused)), float *vector __attribute__((unused)), char flag __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x4c, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movb 0x10(%%ebp), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "je .Lunit_clip_to_aiming_bounds_1\n\t"
      "movb 0x266(%%eax), %%bl\n\t"
      "leal 0x268(%%eax), %%edi\n\t"
      "jmp .Lunit_clip_to_aiming_bounds_2\n\t"
      ".Lunit_clip_to_aiming_bounds_1:\n\t"
      "movb 0x267(%%eax), %%bl\n\t"
      "leal 0x278(%%eax), %%edi\n\t"
      ".Lunit_clip_to_aiming_bounds_2:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunit_clip_to_aiming_bounds_3\n\t"
      "flds 0x8(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x15e8\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x254a50\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_clip_to_aiming_bounds_3:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lunit_clip_to_aiming_bounds_17\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl $0x3f800000, -0x4c(%%ebp)\n\t"
      "call *%[c141360]\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "movl 0x31fc1c, %%ecx\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x44(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x48(%%ebp)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x48(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "leal -0x4c(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "call *%[c1097f0]\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c84a10]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunit_clip_to_aiming_bounds_4\n\t"
      "flds -0x10(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x15fa\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b712c\n\t"
      "pushl $0x26ae40\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_clip_to_aiming_bounds_4:\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c10cc00]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "jne .Lunit_clip_to_aiming_bounds_5\n\t"
      "flds -0x8(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x15fd\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b710c\n\t"
      "pushl $0x25eb8c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x18, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_clip_to_aiming_bounds_5:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "jne .Lunit_clip_to_aiming_bounds_6\n\t"
      "flds -0xc(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x15fe\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b70f0\n\t"
      "pushl $0x25eb8c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x18, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_clip_to_aiming_bounds_6:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps (%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lunit_clip_to_aiming_bounds_7\n\t"
      "movl (%%edi), %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lunit_clip_to_aiming_bounds_9\n\t"
      ".Lunit_clip_to_aiming_bounds_7:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x4(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_clip_to_aiming_bounds_8\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".Lunit_clip_to_aiming_bounds_8:\n\t"
      "movb -0x1(%%ebp), %%bl\n\t"
      ".Lunit_clip_to_aiming_bounds_9:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x8(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lunit_clip_to_aiming_bounds_10\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%bl\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jmp .Lunit_clip_to_aiming_bounds_12\n\t"
      ".Lunit_clip_to_aiming_bounds_10:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0xc(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_clip_to_aiming_bounds_11\n\t"
      "movl 0xc(%%edi), %%ecx\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%bl\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jmp .Lunit_clip_to_aiming_bounds_12\n\t"
      ".Lunit_clip_to_aiming_bounds_11:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lunit_clip_to_aiming_bounds_16\n\t"
      ".Lunit_clip_to_aiming_bounds_12:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "jne .Lunit_clip_to_aiming_bounds_13\n\t"
      "flds -0x8(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x161d\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "movl %%edx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2b710c\n\t"
      "pushl $0x25eb8c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x18, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_clip_to_aiming_bounds_13:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "jne .Lunit_clip_to_aiming_bounds_14\n\t"
      "flds -0xc(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x161e\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "movl %%edx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2b70f0\n\t"
      "pushl $0x25eb8c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x18, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_clip_to_aiming_bounds_14:\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c10cc40]\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c84a10]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunit_clip_to_aiming_bounds_15\n\t"
      "flds -0x10(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x1621\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b712c\n\t"
      "pushl $0x26ae40\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_clip_to_aiming_bounds_15:\n\t"
      "pushl %%esi\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x4c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c109680]\n\t"
      "pushl %%esi\n\t"
      "call *%[c84a10]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunit_clip_to_aiming_bounds_16\n\t"
      "flds 0x8(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x1623\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x254a50\n\t"
      "pushl $0x26ae40\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_clip_to_aiming_bounds_16:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lunit_clip_to_aiming_bounds_17:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [get] "m"(b1ada90_get), [c21fb0] "m"(b1ada90_c21fb0), [c8d9d0] "m"(b1ada90_c8d9d0), [assert] "m"(b1ada90_assert), [exitfn] "m"(b1ada90_exitfn), [c141360] "m"(b1ada90_c141360), [c1097f0] "m"(b1ada90_c1097f0), [c84a10] "m"(b1ada90_c84a10), [c10cc00] "m"(b1ada90_c10cc00), [c10cc40] "m"(b1ada90_c10cc40), [c109680] "m"(b1ada90_c109680)
      : "memory");
}
#else
#error "unit_clip_to_aiming_bounds: clang naked draft required"
#endif


/* unit_get_weapon (0x1adeb0)
 *
 * Returns the weapon datum handle stored in the unit's weapon slot array
 * (unit_data_t.unk_680, offset 0x2A8) at the given weapon_index. If
 * weapon_index is NONE (-1), returns NONE. Asserts that the index is in
 * range [0, MAXIMUM_WEAPONS_PER_UNIT=4). Resolves the unit via
 * object_get_and_verify_type with type mask 3 (biped | vehicle).
 */
int unit_get_weapon(int unit_handle, int16_t weapon_index)
{
  unit_data_t *unit;
  int result;

  unit = (unit_data_t *)object_get_and_verify_type(unit_handle, 3);
  result = -1;
  if (weapon_index != -1) {
    if (weapon_index < 0 || weapon_index >= MAXIMUM_WEAPONS_PER_UNIT) {
      display_assert("index>=0 && index<MAXIMUM_WEAPONS_PER_UNIT",
                     "c:\\halo\\SOURCE\\units\\units.c", 0x20ac, 1);
      system_exit(-1);
    }
    result = unit->unk_680[weapon_index].value;
  }
  return result;
}

/* unit_set_actively_controlled (0x1adf10)
 *
 * Reattaches all weapons in the unit's weapon slots (unk_680, offset 0x2A8,
 * 4 entries) and updates the unit's alive/active flags (unk_436, offset 0x1B4).
 *
 * If the unit has an actor (offset 0x1A4), swarm actor (0x1A8), or unk_456
 * (0x1C8), param_2 is forced to 1 (the unit is always considered active).
 *
 * When the unit is active and object flag bit 2 at offset 0xB6 is clear:
 *   - Sets bit 0 (alive) and bit 6 in unk_436
 * Otherwise:
 *   - Clears bit 0 and bit 6 in unk_436
 *
 * Then iterates all 4 weapon slots and calls item_attach_to_unit for each
 * valid weapon handle, and finally tail-calls unit_update_seat_occupancy.
 */
void unit_set_actively_controlled(int unit_handle, char param_2)
{
  char *unit;
  uint32_t flags;
  int *weapon_slots;
  int i;

  unit = object_get_and_verify_type(unit_handle, 3);

  /* Force active if the unit has an actor, swarm actor, or unk_456 */
  if (*(int *)(unit + 0x1a4) != -1 || *(int *)(unit + 0x1a8) != -1 ||
      *(int *)(unit + 0x1c8) != -1) {
    param_2 = 1;
  }

  if ((*(uint8_t *)(unit + 0xb6) & 4) == 0 && param_2 != 0) {
    flags = *(uint32_t *)(unit + 0x1b4);
    *(uint32_t *)(unit + 0x1b4) = flags | 1;
    flags = flags | 0x41;
  } else {
    flags = *(uint32_t *)(unit + 0x1b4);
    *(uint32_t *)(unit + 0x1b4) = flags & 0xfffffffe;
    flags = flags & 0xffffffbe;
  }
  *(uint32_t *)(unit + 0x1b4) = flags;

  /* Reattach all weapons in the unit's weapon slots */
  weapon_slots = (int *)(unit + 0x2a8);
  for (i = 4; i != 0; i--) {
    if (*weapon_slots != -1) {
      item_attach_to_unit(*weapon_slots, unit_handle);
    }
    weapon_slots++;
  }

  unit_update_seat_occupancy(unit_handle);
}

/* unit_current_weapon_is_busy (0x1ae1a0)
 *
 * Gets the weapon handle in the unit's current seat (via unit_get_weapon
 * with the seat's weapon_index at offset 0x2A2), then checks whether the
 * weapon object is in state 2 or 3 at offset 0x211. Returns true if the
 * weapon is in one of those states, false otherwise (including when there
 * is no current weapon).
 */
bool unit_current_weapon_is_busy(int unit_handle)
{
  char *unit;
  int weapon_handle;
  char *weapon;

  unit = object_get_and_verify_type(unit_handle, 3);
  weapon_handle = unit_get_weapon(unit_handle, *(int16_t *)(unit + 0x2a2));
  if (weapon_handle == -1)
    return false;

  weapon = object_get_and_verify_type(weapon_handle, 4);
  if (*(char *)(weapon + 0x211) == 2 || *(char *)(weapon + 0x211) == 3)
    return true;

  return false;
}

/* unit_get_seat_label (0x1ae290)
 *
 * Returns the seat label string for a unit. If the unit has a parent object
 * (offset 0xCC != NONE) and a valid seat tag index (offset 0x2A0 != -1),
 * retrieves the label from the parent's unit tag seat block at offset +4
 * within the 0x11C-sized seat element. Otherwise falls back to a base seat
 * label from the global table at 0x32e484 indexed by base_seat_index
 * (offset 0x257), asserting it is in range [0, 6).
 *
 * Register arg: unit_handle passed in EAX.
 *
 * Confirmed: PUSH 0x3 / PUSH EAX -> object_get_and_verify_type.
 * Confirmed: parent_object_index at [ESI + 0xCC].
 * Confirmed: seat tag index at [ESI + 0x2A0].
 * Confirmed: tag_get(0x756e6974, ...) for 'unit' tag.
 * Confirmed: tag_block_get_element(tag+0x2e4, seat_index, 0x11c).
 * Confirmed: assert "base_seat_index>=0 &&
 * base_seat_index<NUMBER_OF_UNIT_BASE_SEATS" at line 0x200f. Confirmed: global
 * table at 0x32e484, indexed by MOVSX of byte at +0x257.
 */
int unit_get_seat_label(int unit_handle)
{
  char *unit;
  int parent_handle;
  int16_t seat_tag_index;
  int *parent_obj;
  char *unit_tag;
  char *seat_element;
  int16_t base_seat;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);

  parent_handle = *(int *)(unit + 0xcc);
  if (parent_handle != -1 && *(int16_t *)(unit + 0x2a0) != -1) {
    parent_obj = (int *)object_get_and_verify_type(parent_handle, 3);
    unit_tag = (char *)tag_get(0x756e6974, *parent_obj);
    seat_tag_index = *(int16_t *)(unit + 0x2a0);
    seat_element = (char *)tag_block_get_element(unit_tag + 0x2e4,
                                                 (int)seat_tag_index, 0x11c);
    return (int)(seat_element + 4);
  }

  base_seat = (int16_t) * (int8_t *)(unit + 0x257);
  if (base_seat < 0 || base_seat >= NUMBER_OF_UNIT_BASE_SEATS) {
    display_assert(
      "base_seat_index>=0 && base_seat_index<NUMBER_OF_UNIT_BASE_SEATS",
      "c:\\halo\\SOURCE\\units\\units.c", 0x200f, 1);
    system_exit(-1);
  }
  return *(int *)(0x32e484 + base_seat * 4);
}

/* unit_clear_seat_equipment (0x1ae330)
 *
 * Clears the unit's seat equipment handle at offset 0x2C8
 * (unit_data_t.unk_712). If the current value is not NONE (-1), calls the
 * dual-register function at 0x1ab990 (EDI=unit_handle, ESI=equipment_handle)
 * to detach/remove the equipment, then sets the field to NONE.
 */
void unit_clear_seat_equipment(int unit_handle)
{
  unit_data_t *unit;
  int equipment_handle;

  unit = (unit_data_t *)object_get_and_verify_type(unit_handle, 3);
  equipment_handle = unit->unk_712.value;
  if (equipment_handle != -1) {
    unit_detach_weapon(unit_handle, equipment_handle);
    unit->unk_712.value = -1;
  }
}

/* unit_can_enter_seat (0x1ae370)
 *
 * Checks whether a unit can enter a given seat object. Verifies both object
 * types (unit=3, seat=4), retrieves the unit's seat label string via 0x1ae290
 * and the seat object's weapon label string via 0xfae80, then calls 0x1acd70
 * to attempt seat matching. If the match succeeds, dispatches through the game
 * engine vtable (current_game_engine->vtable[0x58]) for engine-specific
 * validation.
 *
 * Returns: true if the seat can be entered, false otherwise.
 */
bool unit_can_enter_seat(int unit_handle, int seat_object_handle)
{
  int seat_label;
  int weapon_label;
  char can_enter;

  object_get_and_verify_type(unit_handle, 3);
  object_get_and_verify_type(seat_object_handle, 4);

  seat_label = unit_get_seat_label(unit_handle);
  weapon_label = (int)weapon_get_label(seat_object_handle);
  can_enter =
    (char)unit_try_animation_state(unit_handle, seat_label, weapon_label, 0);

  if (can_enter != 0) {
    /* 0xa8b30: game engine vtable dispatch */
    can_enter =
      (char)game_engine_allow_weapon_pick_up(unit_handle, seat_object_handle);
  }
  return can_enter != 0;
}

/* unit_should_swap_weapon (0x1ae3c0)
 *
 * Checks whether a unit should swap one of its current weapons for the given
 * weapon object. Iterates the unit's 4 weapon slots (offset 0x2A8). If any
 * non-current slot already holds the same weapon tag, returns false. If the
 * current slot holds the same weapon tag, returns true only when the current
 * weapon's ammo is above the threshold at 0x2533c0 AND the new weapon has
 * equal or greater ammo. Otherwise returns true (new weapon type is not
 * already held).
 */
bool unit_should_swap_weapon(int unit_handle, int weapon_handle)
{
  char *unit;
  int *weapon_obj;
  int weapon_tag;
  int current_weapon;
  int seat_index;
  int *weapon_slot;
  bool should_swap;

  unit = object_get_and_verify_type(unit_handle, 3);
  weapon_obj = (int *)object_get_and_verify_type(weapon_handle, 4);
  weapon_tag = *weapon_obj;

  tag_get(0x77656170, weapon_tag);

  current_weapon = unit_get_weapon(unit_handle, *(int16_t *)(unit + 0x2a2));
  if (current_weapon == -1)
    return false;

  should_swap = true;
  seat_index = 0;
  weapon_slot = (int *)(unit + 0x2a8);

  do {
    int slot_weapon = *weapon_slot;
    if (slot_weapon != -1) {
      int *slot_weapon_obj = (int *)object_get_and_verify_type(slot_weapon, 4);
      if (weapon_tag == *slot_weapon_obj) {
        if (seat_index == *(int16_t *)(unit + 0x2a2)) {
          float slot_ammo = *(float *)((char *)slot_weapon_obj + 0x1f0);
          if (slot_ammo > *(float *)0x2533c0) {
            float new_ammo = *(float *)((char *)weapon_obj + 0x1f0);
            if (new_ammo < slot_ammo)
              goto next_seat;
          }
        }
        should_swap = false;
      }
    }
  next_seat:
    seat_index++;
    weapon_slot++;
  } while (seat_index < 4);

  return should_swap;
}

/* unit_next_weapon_index (0x1ae490)
 *
 * Scans the unit's weapon slots circularly in the given direction to find the
 * next valid/usable weapon. Uses unit->unk_680[] (offset 0x2A8) as the weapon
 * handle array and unit->unk_696[] (offset 0x2B8) as a priority/ordering array.
 *
 * If weapon_index is NONE (-1), starts scanning from slot 0. If direction is 0,
 * picks the weapon with the lowest priority value; if direction is nonzero,
 * picks the first valid weapon found. Returns the index of the best weapon
 * found, or NONE (-1) if no valid weapon exists.
 *
 * Callees (by address, not in kb.json):
 *   0x1ae290 — get unit animation tag pointer (EAX=unit_handle@<eax>)
 *   0xfae80  — get weapon tag info pointer (1 stack arg: weapon_handle)
 *   0x1acd70 — check unit can use weapon (EAX=unit_handle@<eax>, 3 stack args)
 *   0xa8b30  — weapon usability callback (2 stack args)
 *   0xfb090  — weapon has must-be-readied flag (1 stack arg)
 */
int16_t unit_next_weapon_index(int unit_handle, int16_t weapon_index,
                               int16_t direction)
{
  unit_data_t *unit;
  int current_index;
  int best_index;
  int iter_index;
  int weapon_handle;
  int anim_tag;
  int weapon_tag;
  char can_use;
  char usable;
  char must_be_readied;

  unit = (unit_data_t *)object_get_and_verify_type(unit_handle, 3);
  best_index = -1;

  if (weapon_index == (int16_t)-1) {
    weapon_index = 0;
  } else if (weapon_index < 0 || weapon_index >= MAXIMUM_WEAPONS_PER_UNIT) {
    display_assert("current_index>=0 && current_index<MAXIMUM_WEAPONS_PER_UNIT",
                   "c:\\halo\\SOURCE\\units\\units.c", 0x1e40, 1);
    system_exit(-1);
  }

  current_index = weapon_index;

  do {
    iter_index = (int)(int16_t)current_index;
    weapon_handle = unit->unk_680[iter_index].value;

    if (weapon_handle != -1) {
      /* Validate both the unit and weapon objects */
      object_get_and_verify_type(unit_handle, 3);
      object_get_and_verify_type(weapon_handle, 4);

      anim_tag = unit_get_seat_label(unit_handle);
      weapon_tag = (int)weapon_get_label(weapon_handle);
      can_use =
        (char)unit_try_animation_state(unit_handle, anim_tag, weapon_tag, 0);

      if (can_use != 0) {
        /* 0xa8b30: weapon usability callback */
        usable =
          (char)game_engine_allow_weapon_pick_up(unit_handle, weapon_handle);
        if (usable != 0) {
          /* direction != 0: pick first valid; direction == 0: pick lowest
           * priority */
          if (direction != 0) {
            best_index = current_index;
          } else {
            if ((int16_t)best_index == (int16_t)-1 ||
                unit->unk_696[(int)(int16_t)best_index].value <
                  unit->unk_696[iter_index].value) {
              best_index = current_index;
            }
          }

          /* 0xfb090: check weapon must-be-readied flag */
          must_be_readied =
            (char)((int (*)(int))0xfb090)(unit->unk_680[iter_index].value);
          if (must_be_readied != 0)
            return (int16_t)best_index;

          if ((int16_t)current_index != weapon_index)
            return (int16_t)best_index;
        }
      }
    }

    /* Advance to next slot, wrapping around */
    if (direction < 0) {
      if ((int16_t)current_index == 0)
        current_index = 3;
      else
        current_index = iter_index - 1;
    } else {
      if ((int16_t)current_index == 3)
        current_index = 0;
      else
        current_index = iter_index + 1;
    }
  } while ((int16_t)current_index != weapon_index);

  return (int16_t)best_index;
}

/* unit_set_in_vehicle (0x1ae600)
 *
 * Attempts to stow/put the unit's current weapon into a vehicle slot.
 * Returns true (1) if the weapon was successfully placed, false (0) otherwise.
 *
 * Steps:
 * 1. Gets the unit tag definition via tag_get("unit", unit->tag_index).
 * 2. Looks up the current weapon handle via unit_get_weapon.
 * 3. Calls FUN_001ae490 to compute the next weapon index.
 * 4. Skips if weapon is NONE, or if next index equals current and flag is
 * false.
 * 5. Checks the weapon object's flags byte (bit 0 must be clear).
 * 6. Calls weapon_try_place(weapon_handle, flag) to attempt the placement.
 * 7. On success: fires unit event 0xd, calls unit_detach_weapon, clears the weapon
 *    slot, resets current/next weapon indices, and optionally deletes the
 *    weapon object if weapon_can_be_fired returns false.
 */
bool unit_set_in_vehicle(int unit_handle, bool flag)
{
  unit_data_t *unit;
  int weapon_handle;
  int16_t new_index;
  object_data_t *weapon_obj;
  int16_t cur_index;

  unit = (unit_data_t *)object_get_and_verify_type(unit_handle, 3);
  tag_get(0x756e6974, *(int *)unit);
  (void)object_get_and_verify_type(unit_handle, 3);
  weapon_handle = unit_get_weapon(unit_handle, unit->unk_674);
  new_index = unit_next_weapon_index(unit_handle, unit->unk_674, 1);

  if (weapon_handle == -1)
    return false;
  if (new_index == unit->unk_674 && !flag)
    return false;

  weapon_obj = (object_data_t *)object_get_and_verify_type(weapon_handle, -1);
  if (weapon_obj->flags & 1)
    return false;

  if (!((bool (*)(int, bool))0xfd360)(weapon_handle, flag))
    return false;

  ((void (*)(int, int))0xde360)(unit_handle, 0xd);

  unit_detach_weapon(unit_handle, weapon_handle);

  cur_index = (int16_t)unit->unk_674;
  unit->unk_680[cur_index].value = -1;
  unit->unk_674 = (uint16_t)-1;
  new_index = unit_next_weapon_index(unit_handle, -1, 0);
  unit->unk_676 = (uint16_t)new_index;

  if (!((bool (*)(int))0xfaf50)(weapon_handle))
    object_delete(weapon_handle);

  return true;
}

/* unit_apply_alignment_vector (0x1af180)
 *
 * Sets the unit object's facing direction (forward and up vectors) from a
 * 2D alignment vector (x, y) representing a direction in the ground plane,
 * but only if the unit has no parent (is not seated/mounted).
 *
 * Steps:
 *   1. Resolves unit via object_get_and_verify_type (type_mask=3, @<eax>).
 *   2. If parent_object_index != -1 (unit is mounted), returns immediately.
 *   3. Asserts alignment_vector is a valid 2D normal via valid_real_normal2d.
 *   4. Copies alignment_vector[0] -> unit+0x24 (object forward x),
 *      alignment_vector[1] -> unit+0x28 (object forward y),
 *      0.0f               -> unit+0x2c (object forward z).
 *   5. Loads the canonical "up" vector from the pointer at 0x31fc44 and
 *      writes it to unit+0x30, +0x34, +0x38.
 *   6. Asserts the forward/up pair are valid axes via valid_real_normal3d_perpendicular.
 *
 * Register args: unit_handle @<eax>, alignment_vector @<ecx>.
 *
 * Confirmed: PUSH 0x3 / PUSH EAX -> object_get_and_verify_type (0x13d680).
 * Confirmed: MOV EBX,ECX at entry; CMP [ESI+0xcc],-1 -> parent gate.
 * Confirmed: CALL 0x28610 (valid_real_normal2d check on EBX=alignment_vector).
 * Confirmed: MOV ECX,[EBX]; FSTP [ESI+0x28]; MOV [ESI+0x24],ECX; MOV
 * [ESI+0x2c],0. Confirmed: MOV EDX,[0x31fc44]; copies 3 floats to
 * [ESI+0x30..0x38]. Confirmed: assert string "alignment_vector" at 0x2b7234.
 * Confirmed: CALL 0x84a70 (valid_real_vector3d_axes2 check).
 */
void unit_apply_alignment_vector(int unit_handle, float *alignment_vector)
{
  unit_data_t *unit;
  float *up_vector;

  unit = (unit_data_t *)object_get_and_verify_type(unit_handle, 3);

  /* Only apply if the unit is a top-level object (no parent). */
  if (unit->object.parent_object_index.value != -1)
    return;

  /* Assert the 2D alignment vector is a valid normal (valid_real_normal2d). */
  if (!valid_real_normal2d(alignment_vector)) {
    display_assert("assert_valid_real_normal2d(alignment_vector)",
                   "c:\\halo\\SOURCE\\units\\units.c", 0x2482, 1);
    system_exit(-1);
  }

  /* Copy 2D alignment direction into object forward vector (zero z).
   * Confirmed: MOV ECX,[EBX]; FSTP [ESI+0x28]; MOV [ESI+0x24],ECX; MOV
   * [ESI+0x2c],0. Note: store order in binary is y first (FSTP [ESI+0x28]) then
   * x (MOV [ESI+0x24]). Both reads from [EBX] are sourced before any store, so
   * no aliasing concern. */
  *(float *)((char *)unit + 0x24) = alignment_vector[0];
  *(float *)((char *)unit + 0x28) = alignment_vector[1];
  *(float *)((char *)unit + 0x2c) = 0.0f;

  /* Copy the canonical up vector (world up) from the global at 0x31fc44.
   * Confirmed: MOV EDX,[0x31fc44]; copies 3 dwords to [ESI+0x30,+0x34,+0x38].
   */
  up_vector = *(float **)0x31fc44;
  *(float *)((char *)unit + 0x30) = up_vector[0];
  *(float *)((char *)unit + 0x34) = up_vector[1];
  *(float *)((char *)unit + 0x38) = up_vector[2];

  /* Assert forward/up are valid orthogonal axes
   * (valid_real_normal3d_perpendicular). */
  if (!valid_real_normal3d_perpendicular((float *)((char *)unit + 0x24),
                                         (float *)((char *)unit + 0x30))) {
    display_assert("assert_valid_real_vector3d_axes2(forward, up)",
                   "c:\\halo\\SOURCE\\units\\units.c", 0x2486, 1);
    system_exit(-1);
  }
}

/* unit_verify_vectors (0x1af620)
 *
 * Validates 6 directional vectors stored on a unit object:
 *   - unk_468 (offset 0x1D4) — facing vector
 *   - unk_480 (offset 0x1E0) — aiming vector
 *   - unk_516 (offset 0x204) — looking vector
 *   - unk_36/unk_48 (offsets 0x24/0x30) — forward/up from object_data_t
 *   - unk_492 (offset 0x1EC) — additional vector
 *   - unk_528 (offset 0x210) — additional vector
 *
 * Each vector is checked via valid_real_normal3d; additionally the
 * forward/up pair at 0x24/0x30 is checked for perpendicularity via
 * valid_real_normal3d_perpendicular. Returns true only if all checks pass.
 *
 * Register arg: unit_handle passed in EAX.
 *
 * Confirmed: PUSH 0x3 / PUSH EAX -> object_get_and_verify_type.
 * Confirmed: LEA offsets 0x1d4, 0x1e0, 0x204, 0x24, 0x30, 0x1ec, 0x210.
 * Confirmed: CALL 0x21fb0 (valid_real_normal3d) and 0x84a70 (perpendicular
 * check). Confirmed: returns bool (MOV AL,1 / XOR AL,AL).
 */
bool unit_verify_vectors(int unit_handle)
{
  char *obj;

  obj = (char *)object_get_and_verify_type(unit_handle, 3);

  /* Single short-circuit && chain matches the original's one-setne exit
   * structure (0x1af6a2). The validators return bool (byte contract:
   * original callers testb %al), and the (bool) cast on the chain result
   * yields the original's movb $1,%al / xorb %al,%al return. Residual 5-insn
   * gap is the @<eax> register-arg prologue VC71 cannot express (permanent
   * ceiling). Runtime-identical: && short-circuits like the early returns. */
  return (bool)(valid_real_normal3d((float *)(obj + 0x1d4)) &&
                valid_real_normal3d((float *)(obj + 0x1e0)) &&
                valid_real_normal3d((float *)(obj + 0x204)) &&
                valid_real_normal3d_perpendicular((float *)(obj + 0x24),
                                                  (float *)(obj + 0x30)) &&
                valid_real_normal3d((float *)(obj + 0x1ec)) &&
                valid_real_normal3d((float *)(obj + 0x210)));
}

/* unit_control_trace (0x1af6b0) — XBE naked draft (batch 53). */
#if defined(__clang__)
static bool (*const b1af6b0_c1af620)(int unit_handle) = unit_verify_vectors;
static void *(*const b1af6b0_get)(int, int) = object_get_and_verify_type;
static char * (*const b1af6b0_c49ac0)(int actor_handle, int object_handle, char with_actor, char *buf, int buf_size) = ai_debug_describe_actor;
static void (*const b1af6b0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b1af6b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1af6b0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void unit_control_trace(int unit_handle __attribute__((unused)), const char *label __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x200, %%esp\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1af620]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunit_control_trace_2\n\t"
      "pushl %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x1a4(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lunit_control_trace_1\n\t"
      "movl 0x1a8(%%esi), %%eax\n\t"
      ".Lunit_control_trace_1:\n\t"
      "pushl $0x200\n\t"
      "leal -0x200(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c49ac0]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x200(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b744c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "flds 0x38(%%esi)\n\t"
      "subl $0x24, %%esp\n\t"
      "fstpl 0x40(%%esp)\n\t"
      "flds 0x34(%%esi)\n\t"
      "fstpl 0x38(%%esp)\n\t"
      "flds 0x30(%%esi)\n\t"
      "fstpl 0x30(%%esp)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds 0x24(%%esi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x14(%%esi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x10(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x29c318\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "flds 0x20c(%%esi)\n\t"
      "fstpl 0x48(%%esp)\n\t"
      "addl $0x48, %%esp\n\t"
      "flds 0x208(%%esi)\n\t"
      "subl $0x40, %%esp\n\t"
      "fstpl 0x38(%%esp)\n\t"
      "flds 0x204(%%esi)\n\t"
      "fstpl 0x30(%%esp)\n\t"
      "flds 0x1e8(%%esi)\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x1e4(%%esi)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds 0x1e0(%%esi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x1dc(%%esi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x1d8(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x1d4(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b740c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "flds 0x200(%%esi)\n\t"
      "fstpl 0x48(%%esp)\n\t"
      "addl $0x48, %%esp\n\t"
      "flds 0x1fc(%%esi)\n\t"
      "subl $0x28, %%esp\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds 0x1f8(%%esi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x1f4(%%esi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x1f0(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x1ec(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b73e0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "flds 0x224(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x220(%%esi)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds 0x21c(%%esi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x218(%%esi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x214(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x210(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b73b4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "pushl $0x2b7394\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movl 0x38(%%esi), %%ecx\n\t"
      "movl 0x34(%%esi), %%edx\n\t"
      "movl 0x30(%%esi), %%eax\n\t"
      "addl $0x40, %%esp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x2c(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x28(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x24(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x10(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b7350\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movl 0x20c(%%esi), %%ecx\n\t"
      "movl 0x208(%%esi), %%edx\n\t"
      "movl 0x204(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x1e8(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x1e4(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x1e0(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x1dc(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x1d8(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x1d4(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b7300\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movl 0x200(%%esi), %%ecx\n\t"
      "movl 0x1fc(%%esi), %%edx\n\t"
      "movl 0x1f8(%%esi), %%eax\n\t"
      "addl $0x58, %%esp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x1f4(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x1f0(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x1ec(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b72c8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movl 0x224(%%esi), %%ecx\n\t"
      "movl 0x220(%%esi), %%edx\n\t"
      "movl 0x21c(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x218(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x214(%%esi), %%edx\n\t"
      "movl 0x210(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b7290\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x40, %%esp\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1af620]\n\t"
      "testb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "jne .Lunit_control_trace_2\n\t"
      "pushl $1\n\t"
      "pushl $0x252\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b725c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_control_trace_2:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [c1af620] "m"(b1af6b0_c1af620), [get] "m"(b1af6b0_get), [c49ac0] "m"(b1af6b0_c49ac0), [c8f390] "m"(b1af6b0_c8f390), [assert] "m"(b1af6b0_assert), [exitfn] "m"(b1af6b0_exitfn)
      : "memory");
}
#else
#error "unit_control_trace: clang naked draft required"
#endif


/* unit_set_control (0x1af990) — XBE naked draft (batch 52). */
#if defined(__clang__)
static void *(*const b1af990_get)(int, int) = object_get_and_verify_type;
static void (*const b1af990_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1af990_exitfn)(int) = system_exit;
static bool (*const b1af990_c21fb0)(float *v) = valid_real_normal3d;
static char * (*const b1af990_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b1af990_c1af6b0)(int unit_handle, const char *label) = unit_control_trace;

__attribute__((naked, noinline))
void unit_set_control(int unit_handle __attribute__((unused)), void *unit_control __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "flds 0x14(%%esi)\n\t"
      "movl %%eax, %%ebx\n\t"
      "flds 0x10(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0xc(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fcomps 0x254644\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lunit_set_control_1\n\t"
      "pushl $1\n\t"
      "pushl $0x5e1\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b776c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_set_control_1:\n\t"
      "movb (%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jl .Lunit_set_control_2\n\t"
      "cmpb $7, %%al\n\t"
      "jl .Lunit_set_control_3\n\t"
      ".Lunit_set_control_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x5e2\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b7708\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_set_control_3:\n\t"
      "movb 0x1(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jl .Lunit_set_control_4\n\t"
      "cmpb $2, %%al\n\t"
      "jl .Lunit_set_control_5\n\t"
      ".Lunit_set_control_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x5e3\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b76a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_set_control_5:\n\t"
      "testb $0x80, 0x3(%%esi)\n\t"
      "je .Lunit_set_control_6\n\t"
      "pushl $1\n\t"
      "pushl $0x5e4\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b7660\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_set_control_6:\n\t"
      "leal 0x1c(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunit_set_control_7\n\t"
      "flds 0x24(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x5e5\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x20(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b763c\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_set_control_7:\n\t"
      "leal 0x28(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunit_set_control_8\n\t"
      "flds 0x30(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x5e6\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b761c\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_set_control_8:\n\t"
      "leal 0x34(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunit_set_control_9\n\t"
      "flds 0x3c(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x5e7\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x38(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b75fc\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_set_control_9:\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lunit_set_control_11\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lunit_set_control_10\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .Lunit_set_control_11\n\t"
      ".Lunit_set_control_10:\n\t"
      "pushl $1\n\t"
      "pushl $0x5e8\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b7580\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_set_control_11:\n\t"
      "movw 0x6(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lunit_set_control_13\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lunit_set_control_12\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .Lunit_set_control_13\n\t"
      ".Lunit_set_control_12:\n\t"
      "pushl $1\n\t"
      "pushl $0x5e9\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b74f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_set_control_13:\n\t"
      "movw 0x8(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lunit_set_control_14\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .Lunit_set_control_14\n\t"
      "pushl $1\n\t"
      "pushl $0x5ea\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b74b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_set_control_14:\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "jne .Lunit_set_control_15\n\t"
      "flds 0x18(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x5eb\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b7498\n\t"
      "pushl $0x25eb8c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x18, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_set_control_15:\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "leal 0x228(%%ebx), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x14(%%esi), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "movl %%eax, 0x234(%%ebx)\n\t"
      "movb 0x1(%%esi), %%cl\n\t"
      "movb %%cl, 0x238(%%ebx)\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lunit_set_control_16\n\t"
      "movw %%ax, 0x2a4(%%ebx)\n\t"
      ".Lunit_set_control_16:\n\t"
      "cmpw $-1, 0x6(%%esi)\n\t"
      "je .Lunit_set_control_17\n\t"
      "movb 0x6(%%esi), %%dl\n\t"
      "movb %%dl, 0x2cd(%%ebx)\n\t"
      ".Lunit_set_control_17:\n\t"
      "movb 0x8(%%esi), %%al\n\t"
      "movb %%al, 0x2d1(%%ebx)\n\t"
      "movzwl 0x2(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x1b8(%%ebx)\n\t"
      "movl (%%edi), %%eax\n\t"
      "leal 0x204(%%ebx), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl 0x28(%%esi), %%edx\n\t"
      "leal 0x1e0(%%ebx), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x30(%%esi), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "leal 0x1d4(%%ebx), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x20(%%esi), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x24(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movb (%%esi), %%dl\n\t"
      "pushl $0x2b7488\n\t"
      "movb %%dl, 0x256(%%ebx)\n\t"
      "call *%[c1af6b0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [get] "m"(b1af990_get), [assert] "m"(b1af990_assert), [exitfn] "m"(b1af990_exitfn), [c21fb0] "m"(b1af990_c21fb0), [c8d9d0] "m"(b1af990_c8d9d0), [c1af6b0] "m"(b1af990_c1af6b0)
      : "memory");
}
#else
#error "unit_set_control: clang naked draft required"
#endif


/* unit_reset_weapon_state (0x1b1290)
 *
 * Resets the unit's weapon zoom/ready state. If the unit has an associated
 * player and that player is valid, and the unit's zoom_level is not 0xFF,
 * retrieves the unit's current weapon and plays its zoom-deactivation sound
 * (weapon tag +0x4bc) at scale 1.0. Then clears zoom_level and unk_721 to
 * 0xFF and zeroes unk_760. Finally calls player_clear_aim_assist.
 */
void unit_reset_weapon_state(int unit_handle)
{
  unit_data_t *unit;
  int player_index;
  char *player;
  int weapon_handle;
  weapon_data_t *weapon;
  void *weapon_tag;
  int sound_tag_index;

  unit = (unit_data_t *)object_get_and_verify_type(unit_handle, 3);
  player_index = player_index_from_unit_index(unit_handle);
  if (player_index != -1) {
    player =
      (char *)datum_get(player_data, player_index_from_unit_index(unit_handle));
    if (*(short *)(player + 2) != -1 && unit->zoom_level != 0xFF) {
      unit_data_t *unit2 =
        (unit_data_t *)object_get_and_verify_type(unit_handle, 3);
      weapon_handle = unit_get_weapon(unit_handle, unit2->unk_674);
      if (weapon_handle != -1) {
        weapon = (weapon_data_t *)object_get_and_verify_type(weapon_handle, 4);
        weapon_tag = tag_get(0x77656170, weapon->item.object.tag_index);
        sound_tag_index = *(int *)((char *)weapon_tag + 0x4bc);
        if (sound_tag_index != -1) {
          sound_impulse_start(sound_tag_index, 1.0f);
        }
      }
    }
  }
  unit->zoom_level = 0xFF;
  unit->unk_721 = 0xFF;
  unit->unk_760 = 0;
  player_clear_aim_assist(unit_handle);
}

/* unit_apply_animation_impulse (0x1b1a20)
 *
 * Attempts to apply an animation impulse to a unit. The impulse is an index
 * in [0, NUMBER_OF_UNIT_ANIMATION_IMPULSES) that maps to an animation kind
 * index and an update_kind via unit_impulse_to_animation_kind. The function:
 *
 *   1. Checks whether the unit's current animation state allows impulses
 *      (unit_animation_state_allows_impulse @<eax>=unit_handle). Returns false immediately if not.
 *   2. Resolves unit tag -> antr tag at unit_tag+0x44. Uses the unit's
 *      current mode (unk_592 at +0x250) and sub-anim (unk_593 at +0x251)
 *      to reach the sub-animation block at mode+0x58 (element size 0xbc).
 *   3. Maps the impulse index to an animation kind index (AX) and an
 *      update_kind (written to *out_update_kind) via unit_impulse_to_animation_kind.
 *   4. Looks up the animation kind index in the sub-anim's kind table at
 *      sub_anim+0x98 (count) / sub_anim+0x9c (int16[] ptr). Returns false
 *      if out of range or the slot is -1.
 *   5. Calls object_set_region_count(unit_handle, update_kind) to set
 *      the interpolation mode.
 *   6. Calls model_animation_choose_random(1, antr_tag_idx, kind_anim_idx)
 *      to choose an animation.
 *   7. Calls unit_set_animation(@<eax>=unit_handle, @<edi>=antr_tag_idx,
 *      @<bx>=chosen_anim).
 *   8. Sets unk_584 (0x248) bit 0 and unk_595 (0x253) = 0x1d.
 *   9. If anim_data is non-NULL, the unit type is 0 (biped), and the unit
 *      has no parent, calls unit_apply_alignment_vector(@<eax>=unit_handle, @<ecx>=anim_data)
 *      to apply an alignment vector.
 *   10. Returns true on success.
 *
 * Register args: unit_animation_state_allows_impulse takes unit_handle @<eax>.
 *                unit_impulse_to_animation_kind takes impulse_index @<ax>, out_update_kind
 * @<ebx>. unit_apply_alignment_vector takes unit_handle @<eax>, anim_data @<ecx>.
 *
 * Confirmed: PUSH EBX (unit_handle) / PUSH 0x3 -> object_get_and_verify_type.
 * Confirmed: MOV EAX,EBX -> CALL 0x1a96f0 (register arg).
 * Confirmed: tag_get(0x756e6974, *unit) then tag_get(0x616e7472,
 * unit_tag+0x44). Confirmed: MOVSX EDX,byte ptr [ESI+0x250] (unk_592 mode
 * index). Confirmed: tag_block_get_element(antr+0xc, unk_592, 0x64). Confirmed:
 * MOVSX ECX,byte ptr [ESI+0x251] (unk_593 sub-anim index). Confirmed:
 * tag_block_get_element(mode+0x58, unk_593, 0xbc). Confirmed: MOV
 * EAX,[EBP+0xc]; LEA EBX,[EBP-0xc]; CALL 0x1a9560 (reg args). Confirmed: CMP
 * [local_c+0x98] / ptr at [local_c+0x9c] / word table indexed by AX. Confirmed:
 * object_set_region_count(unit_handle, update_kind). Confirmed: MOV
 * EAX,[EDI+0x44]; PUSH EBX; PUSH EAX; PUSH 0x1 ->
 * model_animation_choose_random. Confirmed: MOV EDI,[EDI+0x44]; CALL 0x1ab7c0
 * (unit_set_animation @<eax>,@<edi>,@<bx>). Confirmed: OR byte ptr
 * [ESI+0x248],0x1; MOV byte ptr [ESI+0x253],0x1d. Confirmed: CMP word ptr
 * [ESI+0x64],0x0 (type field == 0); CMP [ESI+0xcc],-1 (parent_object_index).
 * Confirmed: MOV EAX,[EBP+0x8]; CALL 0x1af180 (unit_apply_alignment_vector @<eax>,@<ecx>).
 */
bool unit_apply_animation_impulse(int unit_handle, int anim_index,
                                  void *anim_data)
{
  unit_data_t *unit;
  char *unit_tag;
  char *antr_tag;
  char *mode_elem;
  char *sub_anim;
  int16_t kind_anim_index;
  int16_t update_kind;
  int16_t chosen_anim;
  int antr_tag_index;

  unit = (unit_data_t *)object_get_and_verify_type(unit_handle, 3);

  /* Check if the unit's animation state allows applying an impulse.
   * unit_animation_state_allows_impulse takes @<eax>=unit_handle, @<edi>=impulse_index (leaked).
   * Confirmed disassembly: MOV EDI,[EBP+0xc] at 0x1a34, MOV EAX,EBX at 0x1a3c,
   * CALL 0x1a96f0 at 0x1a42 — EDI = anim_index at call time.
   */
  if (!unit_animation_state_allows_impulse(unit_handle, anim_index))
    return false;

  unit_tag = (char *)tag_get(0x756e6974, *(int *)unit);
  antr_tag = (char *)tag_get(0x616e7472, *(int *)(unit_tag + 0x44));

  /* Locate the animation mode element for the unit's current mode (unk_592).
   * antr_tag+0x0c is the mode block; element size 0x64. */
  mode_elem = (char *)tag_block_get_element(antr_tag + 0xc,
                                            (int)(int8_t)unit->unk_592, 0x64);

  /* Locate the sub-animation element for the unit's current sub-anim (unk_593).
   * mode+0x58 is the sub-anim block; element size 0xbc. */
  sub_anim = (char *)tag_block_get_element(mode_elem + 0x58,
                                           (int)(int8_t)unit->unk_593, 0xbc);

  /* Map the impulse index to an animation kind index.
   * unit_impulse_to_animation_kind takes impulse_index @<ax> and &update_kind @<ebx>;
   * writes update_kind (3 or 6) through the pointer, returns kind index in AX.
   * Confirmed: LEA EBX,[EBP-0xc]; MOV EAX,[EBP+0xc]; CALL 0x1a9560.
   */
  kind_anim_index =
    unit_impulse_to_animation_kind((int16_t)anim_index, &update_kind);

  /* Bounds-check the kind index against the sub-anim's kind table. */
  if (kind_anim_index < 0)
    return false;
  if ((int)kind_anim_index >= *(int *)(sub_anim + 0x98))
    return false;

  /* Index the kind->animation table (int16[] at sub_anim+0x9c). */
  kind_anim_index =
    *(int16_t *)(*(int *)(sub_anim + 0x9c) + (int)kind_anim_index * 2);
  if (kind_anim_index == -1)
    return false;

  /* Set interpolation mode and choose a random animation variant. */
  object_set_region_count(unit_handle, update_kind);

  antr_tag_index = *(int *)(unit_tag + 0x44);
  chosen_anim =
    (int16_t)model_animation_choose_random(1, antr_tag_index, kind_anim_index);

  /* Apply the chosen animation to the unit.
   * unit_set_animation: @<eax>=unit_handle, @<edi>=antr_tag_index,
   * @<bx>=chosen_anim. Confirmed: MOV EDI,[EDI+0x44]; MOV EAX,[EBP+0x8]; CALL
   * 0x1ab7c0.
   */
  unit_set_animation(unit_handle, antr_tag_index, chosen_anim);

  /* Mark animation impulse as active and set state to 0x1d. */
  unit->unk_584 |= 0x1;
  unit->unk_595 = 0x1d;

  /* If anim_data is provided and this is a top-level biped (type==0, no
   * parent), apply the facing alignment vector. unit_apply_alignment_vector takes unit_handle
   * @<eax>, anim_data @<ecx>. Confirmed: TEST ECX,ECX (param_3); CMP
   * [ESI+0x64],0; CMP [ESI+0xcc],-1.
   */
  if (anim_data != NULL && unit->object.type == 0 &&
      unit->object.parent_object_index.value == -1) {
    unit_apply_alignment_vector(unit_handle, (float *)anim_data);
  }

  return true;
}

/* unit_can_melee_attack (0x1b1d00)
 *
 * Returns true if the unit at object_handle can be hit by a melee attack
 * originating from position *position (a float[3]). The check is:
 *
 *   1. Object must be a biped (type == 0) via
 * object_try_and_get_and_verify_type with mask=3 (units).
 *   2. Unit tag flags dword at +0x17c must NOT have bit 0x10000 set.
 *   3. Dot product of (unit.pos - position) with unit.unk_528 must be <= 0.0f
 *      (i.e., the attacker is not in front of the victim along the victim's
 *      forward vector); OR the unit's seat label must be "asleep".
 *
 * Confirmed: PUSH 0x3 / PUSH EDI -> object_try_and_get_and_verify_type.
 * Confirmed: CMP word ptr [ESI+0x64],0x0; JNZ -> type == 0 check.
 * Confirmed: MOV EAX,[ESI]; PUSH EAX; PUSH 0x756e6974 ->
 * tag_get('unit',tag_index). Confirmed: MOV ECX,[EAX+0x17c]; TEST ECX,0x10000;
 * JNZ -> flag check. Confirmed: FLD [ESI+0x50]; FSUB [EAX]; ... -> dot product
 * over unk_528. Confirmed: FCOMP [0x2533c0](0.0f); FNSTSW AX; TEST AH,0x41; JZ
 * -> > 0.0f early return true. Confirmed: MOV ESI,[0x32e484] ("asleep" str
 * ptr); MOV EAX,EDI; CALL unit_get_seat_label. Confirmed: PUSH EAX; PUSH ESI;
 * CALL csstrcmp; TEST EAX,EAX; JNZ -> return false on mismatch.
 */
char unit_unsuspecting(int object_handle, void *position)
{
  unit_data_t *unit;
  char *unit_tag;
  float dx;
  float dy;
  float dz;
  float dot;
  int seat_label;
  float *pos;

  unit = (unit_data_t *)object_try_and_get_and_verify_type(object_handle, 3);
  if (unit == NULL)
    return 0;
  if (unit->object.type != 0)
    return 0;

  unit_tag = (char *)tag_get(0x756e6974, *(int *)unit);
  if (*(int *)(unit_tag + 0x17c) & 0x10000)
    return 0;

  pos = (float *)position;
  dx = unit->object.unk_80 - pos[0];
  dy = unit->object.unk_84 - pos[1];
  dz = unit->object.unk_88 - pos[2];

  dot = dx * unit->unk_528.x + dy * unit->unk_528.y + dz * unit->unk_528.z;

  if (dot > *(float *)0x2533c0)
    return 1;

  /* Dot product <= 0: only allow if unit is asleep */
  seat_label = unit_get_seat_label(object_handle);
  if (csstrcmp(*(const char **)0x32e484, (const char *)seat_label) != 0)
    return 0;

  return 1;
}

/* unit_enter_seat (0x1b1db0)
 *
 * Attempts to place a unit into a weapon/item seat. Validates that the seat
 * object (type 4) has flag bit 0x800 set and has no parent (parent_object_index
 * == -1). Then checks unit_can_enter_seat and game_engine_unit_can_enter_seat.
 *
 * If flag == 2, clears all existing weapons first. Finds an empty weapon slot
 * via an internal helper (0x1aad60, EAX reg-arg). If a slot is found:
 *   - disconnects the seat object from the map
 *   - disables garbage collection on it
 *   - attaches it to the unit
 *   - stores the seat object handle in unk_680[slot]
 *   - clears unk_696[slot]
 *
 * Based on the flag value:
 *   flag 0: sets unk_676 via unit_next_weapon_index(unit, unk_674, 0)
 *   flag 1: if control_flags bit 0x800 is clear, calls
 *           player_control_set_unit_seat, then sets unk_676 = slot
 *   flag 2: sets unk_676 = slot
 *   default: returns true without changing unk_676
 *
 * Returns true if the seat was entered, false otherwise.
 */
bool unit_enter_seat(int unit_handle, int seat_object_handle, int16_t flag)
{
  object_data_t *seat_obj;
  unit_data_t *unit;
  int16_t seat_index;

  seat_obj = (object_data_t *)object_get_and_verify_type(seat_object_handle, 4);
  unit = (unit_data_t *)object_get_and_verify_type(unit_handle, 3);

  if (!(seat_obj->flags & 0x800))
    return false;
  if (seat_obj->parent_object_index.value != -1)
    return false;
  if (!unit_can_enter_seat(unit_handle, seat_object_handle))
    return false;
  if (!game_engine_unit_can_enter_seat(unit_handle, seat_object_handle))
    return false;

  if (flag == 2)
    unit_clear_weapons(unit_handle);

  seat_index = unit_find_empty_weapon_slot(unit_handle);

  if (seat_index == -1)
    return false;

  object_disconnect_from_map(seat_object_handle);
  object_set_garbage(seat_object_handle, 0);
  item_attach_to_unit(seat_object_handle, unit_handle);

  unit->unk_680[(int16_t)seat_index].value = seat_object_handle;
  unit->unk_696[(int16_t)seat_index].value = 0;

  switch (flag) {
  case 0:
    unit->unk_676 = unit_next_weapon_index(unit_handle, unit->unk_674, 0);
    return true;
  case 1:
    if (!(unit->unk_440 & 0x800))
      player_control_set_unit_seat(unit_handle, seat_index);
    /* fall through */
  case 2:
    unit->unk_676 = seat_index;
    return true;
  default:
    return true;
  }
}

/* unit_update_weapon_readiness (0x1b1ee0)
 *
 * Transitions the unit's active weapon based on its "next weapon" index
 * (unk_676, offset 0x2A4). If the unit currently holds a weapon (unk_674,
 * offset 0x2A2), attempts to place/stow it via weapon_try_place. On
 * success, detaches the current weapon from the parent, disconnects it
 * from the map, marks it as garbage, re-attaches it to the unit via
 * item_attach_to_unit, and clears unk_674.
 *
 * When unk_674 becomes -1 (no active weapon), looks up the "next" weapon
 * (EBX). If a next weapon exists, resolves its label, looks up the
 * animation state, connects the weapon to the map, attaches it at the
 * appropriate marker, copies unk_676 to unk_674, records game_time in
 * unk_696[weapon_index], and activates the weapon. If no next weapon,
 * uses the "unarmed" animation state and sets unk_674 to -1.
 *
 * Always calls unit_reset_weapon_state at the end.
 *
 * Register arg: unit_handle passed in ESI.
 *
 * Confirmed: PUSH 0x3 / PUSH ESI -> object_get_and_verify_type.
 * Confirmed: XOR ECX,ECX; MOV CX,[EAX+0x2a4] — unk_676.
 * Confirmed: XOR EDX,EDX; MOV DX,[EAX+0x2a2] — unk_674.
 * Confirmed: weapon_try_place at 0xfd360, object_detach_from_parent at
 * 0x1411c0. Confirmed: object_disconnect_from_map at 0x13fd00, FUN_0x13fb30 at
 * 0x13fb30. Confirmed: object_set_garbage at 0x13ffc0, item_attach_to_unit at
 * 0xf69c0. Confirmed: weapon_get_label at 0xfae80, unit_get_seat_label at
 * 0x1ae290. Confirmed: unit_try_animation_state at 0x1acd70. Confirmed:
 * object_connect_to_map at 0x140ce0, object_attach_to_marker at 0x144860.
 * Confirmed: weapon_activate at 0xfd2e0, unit_reset_weapon_state at 0x1b1290.
 * Confirmed: game_time_get at 0xb5aa0.
 * Confirmed: "unarmed" string at 0x2b6e68.
 */
void unit_update_weapon_readiness(int unit_handle, int flag)
{
  char *unit;
  char *unit_tag;
  int next_weapon_handle;
  int cur_weapon_handle;
  int seat_label;
  int weapon_label;
  char *antr_tag;
  char *mode_element;
  char *sub_anim;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (char *)tag_get(0x756e6974, *(int *)unit);

  /* Resolve next weapon from unk_676 */
  {
    char *u2 = (char *)object_get_and_verify_type(unit_handle, 3);
    uint16_t next_idx = *(uint16_t *)(u2 + 0x2a4);
    next_weapon_handle = unit_get_weapon(unit_handle, (int16_t)next_idx);
  }

  /* Resolve current weapon from unk_674 */
  {
    char *u3 = (char *)object_get_and_verify_type(unit_handle, 3);
    uint16_t cur_idx = *(uint16_t *)(u3 + 0x2a2);
    cur_weapon_handle = unit_get_weapon(unit_handle, (int16_t)cur_idx);
  }

  /* Try to place/stow the current weapon */
  if (cur_weapon_handle != -1) {
    if (weapon_try_place(cur_weapon_handle, flag)) {
      object_detach_from_parent(cur_weapon_handle);
      object_disconnect_from_map(cur_weapon_handle);
      object_activate(cur_weapon_handle);
      object_set_garbage(cur_weapon_handle, 0);
      item_attach_to_unit(cur_weapon_handle, unit_handle);
      *(uint16_t *)(unit + 0x2a2) = (uint16_t)-1;
    }
  }

  /* If no active weapon, transition to next or unarmed */
  if (*(int16_t *)(unit + 0x2a2) == -1) {
    if (next_weapon_handle != -1) {
      weapon_label = (int)weapon_get_label(next_weapon_handle);
      seat_label = unit_get_seat_label(unit_handle);
      unit_try_animation_state(unit_handle, seat_label, weapon_label, 1);

      /* Look up animation sub-element for weapon attachment markers */
      antr_tag = (char *)tag_get(0x616e7472, *(int *)(unit_tag + 0x44));
      mode_element = (char *)tag_block_get_element(
        antr_tag + 0xc, (int)*(int8_t *)(unit + 0x250), 0x64);
      sub_anim = (char *)tag_block_get_element(
        mode_element + 0x58, (int)*(int8_t *)(unit + 0x251), 0xbc);

      /* Connect weapon to map and attach at markers */
      object_connect_to_map(next_weapon_handle, 0);
      object_set_garbage(next_weapon_handle, 1);
      object_attach_to_marker(unit_handle, sub_anim + 0x40, next_weapon_handle,
                              sub_anim + 0x20);

      /* Copy next weapon index to current */
      {
        uint16_t next_idx = *(uint16_t *)(unit + 0x2a4);
        *(uint16_t *)(unit + 0x2a2) = next_idx;
        if (next_idx != (uint16_t)-1) {
          int16_t cur = *(int16_t *)(unit + 0x2a2);
          ((int *)(unit + 0x2b8))[(int)cur] = game_time_get();
        }
      }

      weapon_activate(next_weapon_handle);
      unit_reset_weapon_state(unit_handle);
      return;
    }

    /* No next weapon — use "unarmed" animation */
    seat_label = unit_get_seat_label(unit_handle);
    unit_try_animation_state(unit_handle, seat_label, (int)"unarmed", 1);
    *(uint16_t *)(unit + 0x2a2) = (uint16_t)-1;
  }

  unit_reset_weapon_state(unit_handle);
}

/* FUN_001b2780 (0x1b2780) — XBE naked draft (batch 57). */
#if defined(__clang__)
static void *(*const b1b2780_get)(int, int) = object_get_and_verify_type;
static void *(*const b1b2780_tag)(int, int) = tag_get;
static void *(*const b1b2780_memset)(void *, int, unsigned int) = csmemset;
static bool (*const b1b2780_c21fb0)(float *v) = valid_real_normal3d;
static char * (*const b1b2780_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b1b2780_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1b2780_exitfn)(int) = system_exit;
static void (*const b1b2780_c1a6bf0)(int unit_handle) = FUN_001a6bf0;
static int *(*const b1b2780_gseed)(void) = get_global_random_seed_address;
static float (*const b1b2780_rmreal)(unsigned int *) = random_math_real;
static bool (*const b1b2780_gerun)(void) = game_engine_running;
static char (*const b1b2780_c1acd70)(int unit_handle, const char *seat_label, const char *weapon_name, char apply_state) = FUN_001acd70;
static void (*const b1b2780_c1b2660)(int unit_handle) = unit_create_initial_weapons;
static void *(*const b1b2780_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1b2780_c40690)(int param_1) = ai_create_mounted_weapons_for_unit;

__attribute__((naked, noinline))
char FUN_001b2780(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0x44(%%eax), %%edx\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "xorb %%cl, %%cl\n\t"
      "cmpl %%ebx, %%edx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LFUN_001b2780_11\n\t"
      "pushl %%edi\n\t"
      "pushl $0x10\n\t"
      "leal 0x2a8(%%esi), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "movl %%ebx, 0x2c8(%%esi)\n\t"
      "call *%[memset]\n\t"
      "pushl $0x10\n\t"
      "leal 0x268(%%esi), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movw %%bx, 0x2a2(%%esi)\n\t"
      "movw %%bx, 0x2a4(%%esi)\n\t"
      "movb %%bl, 0x2cc(%%esi)\n\t"
      "movb %%bl, 0x2cd(%%esi)\n\t"
      "movb %%bl, 0x2d0(%%esi)\n\t"
      "movb %%bl, 0x2d1(%%esi)\n\t"
      "movl %%ebx, 0x1c8(%%esi)\n\t"
      "movl %%ebx, 0x1a4(%%esi)\n\t"
      "movl %%ebx, 0x1a8(%%esi)\n\t"
      "movl %%ebx, 0x1ac(%%esi)\n\t"
      "movl %%ebx, 0x1b0(%%esi)\n\t"
      "movw %%bx, 0x2a0(%%esi)\n\t"
      "movl %%ebx, 0x2d4(%%esi)\n\t"
      "movl %%ebx, 0x2d8(%%esi)\n\t"
      "movw $0, 0x248(%%esi)\n\t"
      "movb %%bl, 0x250(%%esi)\n\t"
      "movb %%bl, 0x251(%%esi)\n\t"
      "movb %%bl, 0x252(%%esi)\n\t"
      "movb %%bl, 0x253(%%esi)\n\t"
      "movb $0, 0x254(%%esi)\n\t"
      "movb $0, 0x255(%%esi)\n\t"
      "movw %%bx, 0x24a(%%esi)\n\t"
      "movw %%bx, 0x24c(%%esi)\n\t"
      "movw %%bx, 0x25a(%%esi)\n\t"
      "movw %%bx, 0x25e(%%esi)\n\t"
      "movw %%bx, 0x262(%%esi)\n\t"
      "movb $2, 0x257(%%esi)\n\t"
      "movw %%bx, 0x24e(%%esi)\n\t"
      "movb %%bl, 0x258(%%esi)\n\t"
      "movw %%bx, 0x1ce(%%esi)\n\t"
      "movb %%bl, 0x1bf(%%esi)\n\t"
      "movb $0, 0x266(%%esi)\n\t"
      "call *%[memset]\n\t"
      "pushl $0x10\n\t"
      "leal 0x278(%%esi), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "movb $0, 0x267(%%esi)\n\t"
      "call *%[memset]\n\t"
      "leal 0x24(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $0x28, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b2780_1\n\t"
      "flds 0x2c(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x189\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b7208\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl %%ebx\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b2780_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal 0x210(%%esi), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl %%edi, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "leal 0x204(%%esi), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "leal 0x1ec(%%esi), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl %%edi, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal 0x1e0(%%esi), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl (%%edi), %%edx\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "leal 0x1d4(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl 0x1b4(%%esi), %%ecx\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl $0x7c\n\t"
      "leal 0x338(%%esi), %%eax\n\t"
      "orl $0x100, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, 0x1c0(%%esi)\n\t"
      "movl %%ebx, 0x334(%%esi)\n\t"
      "movl %%ecx, 0x1b4(%%esi)\n\t"
      "call *%[memset]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%ebx, 0x3a0(%%esi)\n\t"
      "call *%[c1a6bf0]\n\t"
      "pushl $0x40\n\t"
      "leal 0x3e0(%%esi), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "movw %%di, 0x3b4(%%esi)\n\t"
      "movw %%di, 0x3b6(%%esi)\n\t"
      "movl %%edi, 0x3b8(%%esi)\n\t"
      "movw %%di, 0x3da(%%esi)\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "movl %%ebx, 0x3bc(%%esi)\n\t"
      "movl %%ebx, 0x3cc(%%esi)\n\t"
      "movw %%bx, 0x2e4(%%esi)\n\t"
      "movw %%bx, 0x2e6(%%esi)\n\t"
      "movl $0x3f800000, 0x2f4(%%esi)\n\t"
      "movb $0, 0x23b(%%esi)\n\t"
      "movl %%ebx, 0x3c0(%%esi)\n\t"
      "movl %%ebx, 0x3dc(%%esi)\n\t"
      "movw 0x2c4(%%edi), %%ax\n\t"
      "addl $0x1c, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_001b2780_2\n\t"
      "cmpw $2, %%ax\n\t"
      "jge .LFUN_001b2780_2\n\t"
      "cmpw $0, 0x2c6(%%edi)\n\t"
      "jl .LFUN_001b2780_2\n\t"
      "movb 0x2c6(%%edi), %%cl\n\t"
      "movswl %%ax, %%eax\n\t"
      "movb %%cl, 0x2ce(%%eax,%%esi,1)\n\t"
      ".LFUN_001b2780_2:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "orl $0x6000, %%eax\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "flds 0x22c(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b2780_5\n\t"
      "flds 0x230(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b2780_5\n\t"
      "flds 0x244(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b2780_5\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fcomps 0x244(%%edi)\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "movl 0x1b4(%%esi), %%eax\n\t"
      "jp .LFUN_001b2780_3\n\t"
      "orl $0x2000, %%eax\n\t"
      "jmp .LFUN_001b2780_4\n\t"
      ".LFUN_001b2780_3:\n\t"
      "andl $0xffffdfff, %%eax\n\t"
      ".LFUN_001b2780_4:\n\t"
      "movl %%eax, 0x1b4(%%esi)\n\t"
      ".LFUN_001b2780_5:\n\t"
      "call *%[gerun]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b2780_7\n\t"
      "movw 0x68(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_001b2780_6\n\t"
      "cmpw %%bx, %%ax\n\t"
      "jne .LFUN_001b2780_7\n\t"
      ".LFUN_001b2780_6:\n\t"
      "movw 0x180(%%edi), %%dx\n\t"
      "movw %%dx, 0x68(%%esi)\n\t"
      ".LFUN_001b2780_7:\n\t"
      "movl 0x32e48c, %%eax\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c1acd70]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1b2660]\n\t"
      "movl 0x2e4(%%edi), %%ecx\n\t"
      "leal 0x2e4(%%edi), %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "popl %%edi\n\t"
      "jle .LFUN_001b2780_10\n\t"
      "nop\n\t"
      ".LFUN_001b2780_8:\n\t"
      "pushl $0x11c\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "movl 0x104(%%eax), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "jne .LFUN_001b2780_9\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl (%%esi), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_001b2780_8\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001b2780_9:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c40690]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001b2780_10:\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001b2780_11:\n\t"
      "popl %%esi\n\t"
      "movb %%cl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1b2780_get), [tag] "m"(b1b2780_tag), [memset] "m"(b1b2780_memset), [c21fb0] "m"(b1b2780_c21fb0), [c8d9d0] "m"(b1b2780_c8d9d0), [assert] "m"(b1b2780_assert), [exitfn] "m"(b1b2780_exitfn), [c1a6bf0] "m"(b1b2780_c1a6bf0), [gseed] "m"(b1b2780_gseed), [rmreal] "m"(b1b2780_rmreal), [gerun] "m"(b1b2780_gerun), [c1acd70] "m"(b1b2780_c1acd70), [c1b2660] "m"(b1b2780_c1b2660), [elem] "m"(b1b2780_elem), [c40690] "m"(b1b2780_c40690)
      : "memory");
}
#else
#error "FUN_001b2780: clang naked draft required"
#endif


/* unit_board_vehicle (0x1b2b80) — XBE naked draft (batch 53). */
#if defined(__clang__)
static bool (*const b1b2b80_c1a8ce0)(int unit_handle, int target_unit_handle, int16_t seat_index, int *out_unit_handle) = unit_find_nearby_seat;
static void *(*const b1b2b80_get)(int, int) = object_get_and_verify_type;
static void *(*const b1b2b80_tag)(int, int) = tag_get;
static void *(*const b1b2b80_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1b2b80_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1b2b80_exitfn)(int) = system_exit;
static vector3_t * (*const b1b2b80_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static short (*const b1b2b80_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static void (*const b1b2b80_m3x3v)(void *, float *, float *) = (void (*)(void *, float *, float *))real_matrix3x3_transform_vector;
static void (*const b1b2b80_c144860)(int parent_handle, void *marker_name, int child_handle, void *child_marker_name) = object_attach_to_marker;
static void (*const b1b2b80_c1aa890)(int vehicle_handle) = unit_update_seat_occupancy;
static int16_t (*const b1b2b80_c1ae490)(int unit_handle, int16_t current_index, int16_t direction) = FUN_001ae490;
static void (*const b1b2b80_c1b1ee0)(int unit_handle, int flag) = unit_update_weapon_readiness;
static int (*const b1b2b80_c1adeb0)(int unit_handle, int16_t weapon_index) = unit_get_weapon;
static char * (*const b1b2b80_cfae80)(int weapon_handle) = weapon_get_label;
static char (*const b1b2b80_c1acd70)(int unit_handle, const char *seat_label, const char *weapon_name, char apply_state) = FUN_001acd70;
static void (*const b1b2b80_c140160)(int object_handle, int16_t region_count) = object_set_region_count;
static int (*const b1b2b80_c120f20)(int update_kind, int animation_graph_tag_index, int16_t animation_index) = model_animation_choose_random;
static void (*const b1b2b80_c1ab7c0)(int unit_handle, int anim_graph_tag_index, int16_t animation_index) = unit_set_animation;
static void (*const b1b2b80_c140230)(int object_handle, vector3_t *delta) = object_adjust_interpolation_position;
static void (*const b1b2b80_c1446a0)(int object_handle) = object_update_children_recursive;
static void (*const b1b2b80_c409a0)(int unit_handle, int vehicle_handle) = unit_vehicle_board_notify;
static void (*const b1b2b80_c1b1290)(int unit_handle) = unit_reset_weapon_state;

__attribute__((naked, noinline))
bool unit_board_vehicle(int unit_handle __attribute__((unused)), int vehicle_handle __attribute__((unused)), int16_t seat_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x90, %%esp\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c1a8ce0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_board_vehicle_6\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movswl 0x10(%%ebp), %%edx\n\t"
      "pushl $0x11c\n\t"
      "pushl %%edx\n\t"
      "addl $0x2e4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0xcc(%%ebx), %%eax\n\t"
      "addl $0x24, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lunit_board_vehicle_1\n\t"
      "pushl $1\n\t"
      "pushl $0x1095\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b7aa0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_board_vehicle_1:\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1412f0]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl $1\n\t"
      "leal -0x90(%%ebp), %%ecx\n\t"
      "addl $0x24, %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[markers]\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fsubs -0x30(%%ebp)\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "flds -0x20(%%ebp)\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "fsubs -0x2c(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fsubs -0x28(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "call *%[m3x3v]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl $0x25386f\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c144860]\n\t"
      "movw 0x10(%%ebp), %%ax\n\t"
      "movw %%ax, 0x2a0(%%ebx)\n\t"
      "movl %%edi, %%eax\n\t"
      "movl %%edi, 0xcc(%%ebx)\n\t"
      "call *%[c1aa890]\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x2a2(%%eax), %%cx\n\t"
      "pushl $0\n\t"
      "movl %%esi, %%ebx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ae490]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "addl $0x44, %%esp\n\t"
      "pushl $1\n\t"
      "movw %%ax, 0x2a4(%%edx)\n\t"
      "call *%[c1b1ee0]\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movswl 0x2a2(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1adeb0]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lunit_board_vehicle_2\n\t"
      "movl $0x2b6e68, %%eax\n\t"
      "jmp .Lunit_board_vehicle_3\n\t"
      ".Lunit_board_vehicle_2:\n\t"
      "pushl %%eax\n\t"
      "call *%[cfae80]\n\t"
      "addl $4, %%esp\n\t"
      ".Lunit_board_vehicle_3:\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "addl $4, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c1acd70]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunit_board_vehicle_4\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c1acd70]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lunit_board_vehicle_4:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x44(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x616e7472\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movsbl 0x250(%%ecx), %%edx\n\t"
      "pushl $0x64\n\t"
      "pushl %%edx\n\t"
      "addl $0xc, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x40(%%eax), %%ecx\n\t"
      "addl $0x1c, %%esp\n\t"
      "cmpl $7, %%ecx\n\t"
      "jle .Lunit_board_vehicle_5\n\t"
      "movl 0x44(%%eax), %%eax\n\t"
      "movswl 0xe(%%eax), %%eax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .Lunit_board_vehicle_5\n\t"
      "pushl $6\n\t"
      "pushl %%esi\n\t"
      "call *%[c140160]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x44(%%ebx), %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl $1\n\t"
      "call *%[c120f20]\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0x44(%%edx), %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c1ab7c0]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movb $0x1a, 0x253(%%eax)\n\t"
      "call *%[c140230]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1446a0]\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "addl $0x20, %%esp\n\t"
      ".Lunit_board_vehicle_5:\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c409a0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1b1290]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lunit_board_vehicle_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [c1a8ce0] "m"(b1b2b80_c1a8ce0), [get] "m"(b1b2b80_get), [tag] "m"(b1b2b80_tag), [elem] "m"(b1b2b80_elem), [assert] "m"(b1b2b80_assert), [exitfn] "m"(b1b2b80_exitfn), [c1412f0] "m"(b1b2b80_c1412f0), [markers] "m"(b1b2b80_markers), [m3x3v] "m"(b1b2b80_m3x3v), [c144860] "m"(b1b2b80_c144860), [c1aa890] "m"(b1b2b80_c1aa890), [c1ae490] "m"(b1b2b80_c1ae490), [c1b1ee0] "m"(b1b2b80_c1b1ee0), [c1adeb0] "m"(b1b2b80_c1adeb0), [cfae80] "m"(b1b2b80_cfae80), [c1acd70] "m"(b1b2b80_c1acd70), [c140160] "m"(b1b2b80_c140160), [c120f20] "m"(b1b2b80_c120f20), [c1ab7c0] "m"(b1b2b80_c1ab7c0), [c140230] "m"(b1b2b80_c140230), [c1446a0] "m"(b1b2b80_c1446a0), [c409a0] "m"(b1b2b80_c409a0), [c1b1290] "m"(b1b2b80_c1b1290)
      : "memory");
}
#else
#error "unit_board_vehicle: clang naked draft required"
#endif


/* unit_get_zoom_level (0x1a8690)
 * Returns the unit's current zoom level from byte at unit+0x2D0. */
int16_t unit_get_zoom_level(int unit_handle)
{
  char *unit;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  return (int16_t)*(int8_t *)(unit + 0x2D0);
}

/* unit_kill (0x1a7fa0)
 * Marks a unit for killing by setting bit 0x40 on object flags at +0xB6. */
void unit_kill(int unit_handle)
{
  char *obj;

  obj = (char *)object_get_and_verify_type(unit_handle, 3);
  *(uint8_t *)(obj + 0xB6) |= 0x40;
}

/* unit_set_controllable (0x1a9a50)
 * Sets or clears bit 6 (0x40) of unit flags dword at +0x1B4. */
void unit_set_controllable(int unit_handle, char controllable)
{
  char *unit;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  if (controllable) {
    *(uint32_t *)(unit + 0x1B4) |= 0x40;
  } else {
    *(uint32_t *)(unit + 0x1B4) &= ~0x40u;
  }
}

/* unit_set_possessed (0x1a9a90)
 * Sets or clears bit 27 (0x8000000) of unit flags dword at +0x1B4. */
void unit_set_possessed(int unit_handle, char possessed)
{
  char *unit;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  if (possessed) {
    *(uint32_t *)(unit + 0x1B4) |= 0x8000000;
  } else {
    *(uint32_t *)(unit + 0x1B4) &= ~0x8000000u;
  }
}

/* FUN_001a9ec0 (0x1a9ec0)
 * Returns datum handle at unit+0x2D4, or NONE if object lookup fails. */
int FUN_001a9ec0(int unit_handle)
{
  char *unit;

  unit = (char *)object_try_and_get_and_verify_type(unit_handle, 3);
  if (unit != NULL) {
    return *(int *)(unit + 0x2D4);
  }
  return -1;
}

/* FUN_001a9ef0 (0x1a9ef0)
 * Returns datum handle at unit+0x2D8, or NONE if object lookup fails. */
int FUN_001a9ef0(int unit_handle)
{
  char *unit;

  unit = (char *)object_try_and_get_and_verify_type(unit_handle, 3);
  if (unit != NULL) {
    return *(int *)(unit + 0x2D8);
  }
  return -1;
}

/* FUN_001a9f20 (0x1a9f20) — XBE naked draft (batch 60). */
#if defined(__clang__)
static void *(*const b1a9f20_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a9f20_tag)(int, int) = tag_get;
static void *(*const b1a9f20_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1a9f20_c1197b0)(data_iter_t *iter, data_t *data) = data_iterator_new;
static void * (*const b1a9f20_c119810)(data_iter_t *iterator) = data_iterator_next;
static void (*const b1a9f20_c136750)(void *damage_params, int tag_index) = damage_data_new;
static void (*const b1a9f20_c137d20)(void *damage_params, int object_handle, short node_index, short region_index, short permutation_index, unsigned int flags) = object_cause_damage;

__attribute__((naked, noinline))
void FUN_001a9f20(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x68, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movb 0x253(%%esi), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpb $0x2a, %%al\n\t"
      "jne .LFUN_001a9f20_5\n\t"
      "movl 0x7c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x616e7472\n\t"
      "call *%[tag]\n\t"
      "movswl 0x80(%%esi), %%ecx\n\t"
      "pushl $0xb4\n\t"
      "pushl %%ecx\n\t"
      "addl $0x74, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movw 0x80(%%esi), %%dx\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw 0x2e(%%eax), %%dx\n\t"
      "jl .LFUN_001a9f20_5\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c1197b0]\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c119810]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_001a9f20_3\n\t"
      ".LFUN_001a9f20_1:\n\t"
      "movl 0x34(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001a9f20_2\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "flds 0x50(%%esi)\n\t"
      "fsubs 0x50(%%eax)\n\t"
      "addl $0x50, %%eax\n\t"
      "flds 0x54(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "flds 0x58(%%esi)\n\t"
      "fsubs 0x8(%%eax)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fcomps 0x254e74\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jp .LFUN_001a9f20_2\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x294(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x68(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c136750]\n\t"
      "movl 0x34(%%edi), %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "leal -0x68(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x5c(%%ebp)\n\t"
      "call *%[c137d20]\n\t"
      "addl $0x20, %%esp\n\t"
      "movb $1, %%bl\n\t"
      ".LFUN_001a9f20_2:\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119810]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_001a9f20_1\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_001a9f20_4\n\t"
      ".LFUN_001a9f20_3:\n\t"
      "movb 0x1be(%%esi), %%al\n\t"
      "popl %%edi\n\t"
      "incb %%al\n\t"
      "popl %%ebx\n\t"
      "movb %%al, 0x1be(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a9f20_4:\n\t"
      "popl %%edi\n\t"
      "movb $0, 0x1be(%%esi)\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001a9f20_5:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a9f20_get), [tag] "m"(b1a9f20_tag), [elem] "m"(b1a9f20_elem), [c1197b0] "m"(b1a9f20_c1197b0), [c119810] "m"(b1a9f20_c119810), [c136750] "m"(b1a9f20_c136750), [c137d20] "m"(b1a9f20_c137d20)
      : "memory");
}
#else
#error "FUN_001a9f20: clang naked draft required"
#endif


/* FUN_001a7e70 (0x1a7e70)
 * Guard wrapper around unit_has_weapon_definition_index.
 * Returns false if either handle is NONE. */
char FUN_001a7e70(int unit_handle, int definition_index)
{
  char result;

  result = 0;
  if (unit_handle != -1 && definition_index != -1) {
    result = unit_has_weapon_definition_index(unit_handle, definition_index);
  }
  return result;
}

/* unit_destroy (0x1a91e0)
 * Destroys a unit: runs object_destroy then unit_test_spawning. */
void unit_destroy(int unit_handle)
{
  object_destroy(unit_handle);
  unit_test_spawning(unit_handle);
}

/* unit_scripting_can_blink (0x1a9c00)
 * Sets whether a unit can blink. Inverted: bit 22 (0x400000) at +0x1B4
 * means "cannot blink", so can_blink=false sets the bit. */
void unit_scripting_can_blink(int unit_handle, char can_blink)
{
  char *unit;

  if (unit_handle != -1) {
    unit = (char *)object_get_and_verify_type(unit_handle, 3);
    if (can_blink == '\0') {
      *(uint32_t *)(unit + 0x1B4) |= 0x400000;
    } else {
      *(uint32_t *)(unit + 0x1B4) &= ~0x400000u;
    }
  }
}

/* unit_scripting_doesnt_drop_items (0x1a9c40)
 * Iterates child objects and sets bit 20 (0x100000) on each unit's flags. */
void unit_scripting_doesnt_drop_items(int object_list)
{
  int iter_state;
  int child;
  char *unit;

  child = FUN_000ce450(object_list, &iter_state);
  while (child != -1) {
    unit = (char *)object_try_and_get_and_verify_type(child, 3);
    if (unit != NULL) {
      *(uint32_t *)(unit + 0x1B4) |= 0x100000;
    }
    child = FUN_000ce320(object_list, &iter_state);
  }
}

/* FUN_001a7d40 (0x1a7d40)
 * Sums grenade counts for all grenade types (2 types). */
int FUN_001a7d40(int datum_handle)
{
  int i;
  int sum;
  char *ptr;
  char *unit;

  unit = (char *)object_try_and_get_and_verify_type(datum_handle, 3);
  sum = 0;
  if (unit != NULL) {
    ptr = unit + 0x2ce;
    i = 2;
    do {
      sum += (int16_t)*(int8_t *)ptr;
      ptr++;
      i--;
    } while (i != 0);
  }
  return sum;
}

/* FUN_001a7d80 (0x1a7d80) — XBE naked draft (batch 67). */
#if defined(__clang__)
static int (*const b1a7d80_cce450)(int parent_handle, int *iter_state) = FUN_000ce450;
static void *(*const b1a7d80_tryget)(int, int) = object_try_and_get_and_verify_type;
static int (*const b1a7d80_cce320)(int parent_handle, int *iter_state) = FUN_000ce320;

__attribute__((naked, noinline))
void FUN_001a7d80(int datum_handle __attribute__((unused)), char flag __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[cce450]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001a7d80_5\n\t"
      "pushl %%ebx\n\t"
      "movb 0xc(%%ebp), %%bl\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_001a7d80_1:\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001a7d80_4\n\t"
      "testb %%bl, %%bl\n\t"
      "movl 0x1b4(%%eax), %%ecx\n\t"
      "je .LFUN_001a7d80_2\n\t"
      "orl $0x800000, %%ecx\n\t"
      "jmp .LFUN_001a7d80_3\n\t"
      ".LFUN_001a7d80_2:\n\t"
      "andl $0xff7fffff, %%ecx\n\t"
      ".LFUN_001a7d80_3:\n\t"
      "movl %%ecx, 0x1b4(%%eax)\n\t"
      ".LFUN_001a7d80_4:\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[cce320]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_001a7d80_1\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001a7d80_5:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cce450] "m"(b1a7d80_cce450), [tryget] "m"(b1a7d80_tryget), [cce320] "m"(b1a7d80_cce320)
      : "memory");
}
#else
#error "FUN_001a7d80: clang naked draft required"
#endif


/* FUN_001a7df0 (0x1a7df0) — XBE naked draft (batch 65). */
#if defined(__clang__)
static int (*const b1a7df0_cce450)(int parent_handle, int *iter_state) = FUN_000ce450;
static void *(*const b1a7df0_tryget)(int, int) = object_try_and_get_and_verify_type;
static char (*const b1a7df0_c1ac180)(int actor, int anim_tag, void *entry, int do_flag) = FUN_001ac180;
static int (*const b1a7df0_cce320)(int parent_handle, int *iter_state) = FUN_000ce320;

__attribute__((naked, noinline))
char FUN_001a7df0(int datum_handle __attribute__((unused)), int param_2 __attribute__((unused)), int param_3 __attribute__((unused)), int param_4 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movb $1, %%bl\n\t"
      "call *%[cce450]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_001a7df0_4\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      ".LFUN_001a7df0_1:\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001a7df0_3\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_001a7df0_2\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ac180]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a7df0_2\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_001a7df0_3\n\t"
      ".LFUN_001a7df0_2:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_001a7df0_3:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[cce320]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "jne .LFUN_001a7df0_1\n\t"
      "popl %%edi\n\t"
      ".LFUN_001a7df0_4:\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cce450] "m"(b1a7df0_cce450), [tryget] "m"(b1a7df0_tryget), [c1ac180] "m"(b1a7df0_c1ac180), [cce320] "m"(b1a7df0_cce320)
      : "memory");
}
#else
#error "FUN_001a7df0: clang naked draft required"
#endif


/* FUN_001a7ea0 (0x1a7ea0) — XBE naked draft (batch 61). */
#if defined(__clang__)
static void *(*const b1a7ea0_get)(int, int) = object_get_and_verify_type;
static int (*const b1a7ea0_c1adeb0)(int unit_handle, int16_t weapon_index) = unit_get_weapon;
static void * (*const b1a7ea0_c1bfbf0)(const char *name, const char *a2, int size) = game_state_malloc;
static void (*const b1a7ea0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1a7ea0_exitfn)(int) = system_exit;
static void *(*const b1a7ea0_memset)(void *, int, unsigned int) = csmemset;

__attribute__((naked, noinline))
char FUN_001a7ea0(int unit_handle __attribute__((unused)), int weapon_def_tag __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpl $-1, %%esi\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_001a7ea0_1\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_001a7ea0_1\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movswl 0x2a2(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1adeb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001a7ea0_1\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "sete %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a7ea0_1:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
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
      "pushl $8\n\t"
      "pushl $0\n\t"
      "pushl $0x2b68e0\n\t"
      "call *%[c1bfbf0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x4e4cf8\n\t"
      "jne .LFUN_001a7ea0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x108\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b68b0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a7ea0_2:\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "movl 0x4e4cf8, %%eax\n\t"
      "pushl $4\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
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
      : [get] "m"(b1a7ea0_get), [c1adeb0] "m"(b1a7ea0_c1adeb0), [c1bfbf0] "m"(b1a7ea0_c1bfbf0), [assert] "m"(b1a7ea0_assert), [exitfn] "m"(b1a7ea0_exitfn), [memset] "m"(b1a7ea0_memset)
      : "memory");
}
#else
#error "FUN_001a7ea0: clang naked draft required"
#endif


/* unit_get_animation_frames_remaining (0x1a84c0)
 * Returns the number of animation frames remaining.
 * Outputs the current animation state byte to *animation_state_out. */
int unit_get_animation_frames_remaining(int unit_handle, int16_t *animation_state_out)
{
  char *unit;
  char *anim_tag;
  char *anim_entry;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  anim_tag = (char *)tag_get(0x616e7472, *(int *)(unit + 0x7c));
  anim_entry = (char *)tag_block_get_element(
      (int *)(anim_tag + 0x74),
      (int)*(int16_t *)(unit + 0x80),
      0xb4);
  if (animation_state_out == NULL) {
    display_assert("animation_state",
                   "c:\\halo\\SOURCE\\units\\units.c", 0x738, 1);
    system_exit(-1);
  }
  *animation_state_out = (int16_t)*(int8_t *)(unit + 0x253);
  return (int)*(uint16_t *)(anim_entry + 0x22) -
         (int)*(uint16_t *)(unit + 0x82);
}

/* FUN_001a8730 (0x1a8730)
 * Returns 1 for vehicle-related animation states. @ecx = anim state ptr. */
char FUN_001a8730(void *anim_state)
{
  char result;

  result = 0;
  switch (*(int8_t *)((char *)anim_state + 0xb)) {
  case 0x17: case 0x18: case 0x19: case 0x1a: case 0x1b:
  case 0x1d: case 0x1e: case 0x1f: case 0x20: case 0x21:
  case 0x22: case 0x23: case 0x27: case 0x29:
    result = 1;
  }
  return result;
}

/* FUN_001a8790 (0x1a8790)
 * Returns 0 for vehicle/combat animation states. @ecx = anim state ptr. */
char FUN_001a8790(void *anim_state)
{
  char result;

  result = 1;
  switch (*(int8_t *)((char *)anim_state + 0xb)) {
  case 1: case 2: case 3:
  case 0x17: case 0x1a: case 0x1b: case 0x1c:
  case 0x1d: case 0x1e: case 0x1f:
  case 0x21: case 0x22: case 0x23:
  case 0x27: case 0x29:
    result = 0;
  }
  return result;
}

/* FUN_001a87f0 (0x1a87f0)
 * Boolean: idle and free, unless overridden by certain anim states.
 * @ecx = anim state ptr. Switch table verified from binary. */
char FUN_001a87f0(void *anim_state)
{
  char result;

  result = *(int16_t *)((char *)anim_state + 0x1a) == -1;
  if (*(char *)((char *)anim_state + 0xc) != '\0') {
    result = 0;
  }
  switch (*(int8_t *)((char *)anim_state + 0xb)) {
  case 0x14: case 0x15: case 0x16:
  case 0x24: case 0x25: case 0x26:
    result = 0;
  }
  return result;
}

/* FUN_001a8850 (0x1a8850)
 * Returns 0 for specific vehicle/boarding animation states.
 * @ecx = anim state ptr. */
char FUN_001a8850(void *anim_state)
{
  char result;

  result = 1;
  switch (*(int8_t *)((char *)anim_state + 0xb)) {
  case 0x17: case 0x18: case 0x19: case 0x1a: case 0x1b:
  case 0x1d: case 0x22: case 0x23:
    result = 0;
  }
  return result;
}

/* FUN_001a88b0 (0x1a88b0)
 * Maps animation state to animation index. @ecx = anim state value. */
int FUN_001a88b0(int16_t anim_state)
{
  int result;

  result = -1;
  switch ((int)anim_state) {
  case 0x0: case 0x2: case 0x3:
  case 0x10: case 0x11: case 0x12: case 0x13:
  case 0x14: case 0x15: case 0x16:
  case 0x25: case 0x26:
    result = 0x19;
    break;
  case 0x4: case 0x5: case 0x6: case 0x7:
  case 0x8: case 0x9: case 0xa: case 0xb:
  case 0xc: case 0xd: case 0xe: case 0xf:
    result = 0x1a;
    break;
  }
  return result;
}

/* FUN_001a86b0 (0x1a86b0)
 * Animation state transition check. @ecx = anim state ptr, @edx = target state. */
char FUN_001a86b0(void *anim_state, int16_t target_state)
{
  char result;

  result = 1;
  switch (*(int8_t *)((char *)anim_state + 0xb)) {
  case 0x1d: case 0x1e: case 0x1f:
  case 0x21: case 0x22: case 0x23:
  case 0x27: case 0x29:
    if (target_state == 0x17) {
      break;
    }
    return 0;
  case 0x18: case 0x19: {
    int target;

    target = target_state;
    if (target < 0x18 || target > 0x19) {
      goto not_allowed;
    }
    return 1;
  }
  case 0x2: case 0x3: case 0x25: case 0x26:
    if (target_state != 0) {
      break;
    }
    /* FALLTHROUGH */
  case 0x17: case 0x1a: case 0x1b: case 0x1c:
  not_allowed:
    result = 0;
    break;
  }
  return result;
}

/* unit_impulse (0x1a8da0)
 * Applies scaled impulse to unit's transitional velocity (unit+0x18). */
void unit_impulse(int unit_index, int unused, float *impulse_vector, float scale)
{
  uint32_t *unit;
  char *unit_tag;
  char *phys_tag;
  (void)unused;

  unit = (uint32_t *)object_get_and_verify_type(unit_index, 3);
  unit_tag = (char *)tag_get(0x756e6974, *unit);
  if (*(int *)(unit_tag + 0x8c) != -1) {
    phys_tag = (char *)tag_get(0x70687973, *(int *)(unit_tag + 0x8c));
    scale = scale / *(float *)(phys_tag + 8);
    *(float *)((char *)unit + 0x18) = scale * impulse_vector[0] + *(float *)((char *)unit + 0x18);
    *(float *)((char *)unit + 0x1c) = scale * impulse_vector[1] + *(float *)((char *)unit + 0x1c);
    *(float *)((char *)unit + 0x20) = scale * impulse_vector[2] + *(float *)((char *)unit + 0x20);
  }
}

/* unit_get_aiming_unit_index (0x1a9880)
 * Returns the datum index of the unit that controls aiming.
 * If the unit is in a seat with the aiming flag, returns the parent. */
int unit_get_aiming_unit_index(int unit_index)
{
  char *unit;
  uint32_t *parent;
  char *parent_tag;
  uint8_t *seat;

  if (unit_index == -1) {
    return -1;
  }
  unit = (char *)object_get_and_verify_type(unit_index, 3);
  if (*(int *)(unit + 0xcc) != -1 && *(int16_t *)(unit + 0x2a0) != -1) {
    parent = (uint32_t *)object_get_and_verify_type(*(int *)(unit + 0xcc), 3);
    parent_tag = (char *)tag_get(0x756e6974, *parent);
    seat = (uint8_t *)tag_block_get_element(
        (int *)(parent_tag + 0x2e4),
        (int)*(int16_t *)(unit + 0x2a0), 0x11c);
    if ((*seat & 9) != 0) {
      return *(int *)(unit + 0xcc);
    }
  }
  return unit_index;
}

/* unit_scripting_set_emotion_animation (0x1a9b30)
 * Looks up an animation by name and sets it as the unit's emotion animation. */
void unit_scripting_set_emotion_animation(int unit_index, const char *animation_name)
{
  char *unit;
  int16_t anim;

  if (unit_index != -1) {
    unit = (char *)object_get_and_verify_type(unit_index, 3);
    anim = FUN_00120cb0(*(int *)(unit + 0x7c), animation_name);
    if (anim != -1) {
      *(int16_t *)(unit + 0x1ce) = anim;
      return;
    }
    console_warning("couldn\'t find the emotion animation \'%s\'", animation_name);
  }
}

/* unit_scripting_suspended (0x1a9b80)
 * Suspends or unsuspends a unit. Sets/clears bit 24 (0x1000000) at +0x1B4,
 * zeros the velocity from global origin, and clears biped bit if type==0. */
void unit_scripting_suspended(int unit_index, char suspended)
{
  char *unit;
  uint32_t flags;
  char *global_origin;
  char *biped;

  if (unit_index != -1) {
    unit = (char *)object_get_and_verify_type(unit_index, 3);
    if (suspended != '\0') {
      flags = *(uint32_t *)(unit + 0x1b4) | 0x1000000;
    } else {
      flags = *(uint32_t *)(unit + 0x1b4) & 0xfeffffff;
    }
    *(uint32_t *)(unit + 0x1b4) = flags;
    global_origin = *(char **)0x31fc38;
    *(uint32_t *)(unit + 0x18) = *(uint32_t *)global_origin;
    *(uint32_t *)(unit + 0x1c) = *(uint32_t *)(global_origin + 4);
    *(uint32_t *)(unit + 0x20) = *(uint32_t *)(global_origin + 8);
    if (*(int16_t *)(unit + 0x64) == 0) {
      biped = (char *)object_get_and_verify_type(unit_index, 1);
      *(uint32_t *)(biped + 0x424) &= 0xfffffffe;
    }
  }
}

/* FUN_001a9c90 (0x1a9c90) — XBE naked draft (batch 61). */
#if defined(__clang__)
static void *(*const b1a9c90_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a9c90_tag)(int, int) = tag_get;
static void *(*const b1a9c90_elem)(void *, int, int) = tag_block_get_element;
static int (*const b1a9c90_c1dd801)(const char *a, const char *b) = crt_stricmp;
static void (*const b1a9c90_c13d6f0)(void *iter, int type_mask, int flags) = object_iterator_new;
static void * (*const b1a9c90_c13d730)(void *iter) = object_iterator_next;
static int (*const b1a9c90_cce450)(int parent_handle, int *iter_state) = FUN_000ce450;
static int (*const b1a9c90_cce320)(int parent_handle, int *iter_state) = FUN_000ce320;

__attribute__((naked, noinline))
char FUN_001a9c90(int unit_handle __attribute__((unused)), const char *seat_name __attribute__((unused)), int object_list __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpl $-1, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "je .LFUN_001a9c90_9\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "leal 0x2e4(%%eax), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_001a9c90_9\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_001a9c90_1:\n\t"
      "pushl $0x11c\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1dd801]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001a9c90_8\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "call *%[c13d6f0]\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13d730]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001a9c90_8\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_001a9c90_2:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "cmpl %%ecx, 0xcc(%%eax)\n\t"
      "jne .LFUN_001a9c90_3\n\t"
      "cmpw %%di, 0x2a0(%%eax)\n\t"
      "je .LFUN_001a9c90_4\n\t"
      ".LFUN_001a9c90_3:\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c13d730]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001a9c90_2\n\t"
      "jmp .LFUN_001a9c90_8\n\t"
      ".LFUN_001a9c90_4:\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[cce450]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001a9c90_6\n\t"
      ".LFUN_001a9c90_5:\n\t"
      "cmpl %%eax, -0x10(%%ebp)\n\t"
      "je .LFUN_001a9c90_7\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[cce320]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_001a9c90_5\n\t"
      ".LFUN_001a9c90_6:\n\t"
      "cmpl %%eax, -0x10(%%ebp)\n\t"
      "jne .LFUN_001a9c90_8\n\t"
      ".LFUN_001a9c90_7:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_001a9c90_8:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_001a9c90_1\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001a9c90_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a9c90_get), [tag] "m"(b1a9c90_tag), [elem] "m"(b1a9c90_elem), [c1dd801] "m"(b1a9c90_c1dd801), [c13d6f0] "m"(b1a9c90_c13d6f0), [c13d730] "m"(b1a9c90_c13d730), [cce450] "m"(b1a9c90_cce450), [cce320] "m"(b1a9c90_cce320)
      : "memory");
}
#else
#error "FUN_001a9c90: clang naked draft required"
#endif


/* unit_scripting_vehicle_test_seat (0x1a9da0)
 * Returns true if unit_index is sitting in the named seat of vehicle_index. */
char unit_scripting_vehicle_test_seat(int vehicle_index, const char *seat_name, int unit_index)
{
  uint32_t *vehicle;
  char *vehicle_tag;
  int *seats_block;
  char *seat_element;
  char *unit_data;
  int16_t i;

  if (vehicle_index != -1 && unit_index != -1) {
    vehicle = (uint32_t *)object_get_and_verify_type(vehicle_index, 3);
    vehicle_tag = (char *)tag_get(0x756e6974, *vehicle);
    seats_block = (int *)(vehicle_tag + 0x2e4);
    if (0 < *seats_block) {
      i = 0;
      do {
        seat_element = (char *)tag_block_get_element(seats_block, (int)i, 0x11c);
        if (crt_stricmp(seat_name, seat_element + 4) == 0) {
          unit_data = (char *)object_get_and_verify_type(unit_index, 3);
          if (*(int *)(unit_data + 0xcc) == vehicle_index &&
              *(int16_t *)(unit_data + 0x2a0) == i) {
            return 1;
          }
        }
        i++;
      } while ((int)i < *seats_block);
    }
  }
  return 0;
}

/* FUN_001aa4d0 (0x1aa4d0) — unit_driven_by_ai
 * Returns true if the unit (or its driver) has an AI actor. */
char FUN_001aa4d0(int unit_handle)
{
  char *unit;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  if (*(int *)(unit + 0x2d4) != -1) {
    unit = (char *)object_get_and_verify_type(*(int *)(unit + 0x2d4), 3);
  }
  return *(int *)(unit + 0x1a4) != -1;
}

/* FUN_001aa510 (0x1aa510) — unit_gunned_by_ai
 * Returns true if the unit (or its gunner) has an AI actor. */
char FUN_001aa510(int unit_handle)
{
  char *unit;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  if (*(int *)(unit + 0x2d8) != -1) {
    unit = (char *)object_get_and_verify_type(*(int *)(unit + 0x2d8), 3);
  }
  return *(int *)(unit + 0x1a4) != -1;
}

/* FUN_001a7cc0 (0x1a7cc0)
 * Returns the body vitality (0x90) or 0.0 if dead, default if invalid. */
float FUN_001a7cc0(int datum_handle)
{
  char *obj;
  float result;

  obj = (char *)object_try_and_get_and_verify_type(datum_handle, -1);
  result = *(float *)0x255e94;
  if (obj != NULL) {
    if ((*(uint8_t *)(obj + 0xb6) & 4) != 0) {
      return 0.0f;
    }
    result = *(float *)(obj + 0x90);
  }
  return result;
}

/* FUN_001a7d00 (0x1a7d00)
 * Returns the shield vitality (0x94) or 0.0 if dead, default if invalid. */
float FUN_001a7d00(int datum_handle)
{
  char *obj;
  float result;

  obj = (char *)object_try_and_get_and_verify_type(datum_handle, -1);
  result = *(float *)0x255e94;
  if (obj != NULL) {
    if ((*(uint8_t *)(obj + 0xb6) & 4) != 0) {
      return 0.0f;
    }
    result = *(float *)(obj + 0x94);
  }
  return result;
}

/* FUN_001a7c70 (0x1a7c70) — XBE naked draft (batch 69). */
#if defined(__clang__)
static int (*const b1a7c70_cce450)(int parent_handle, int *iter_state) = FUN_000ce450;
static void (*const b1a7c70_c1a7b50)(int datum_handle, float body_damage, float shield_damage) = FUN_001a7b50;
static int (*const b1a7c70_cce320)(int parent_handle, int *iter_state) = FUN_000ce320;

__attribute__((naked, noinline))
void FUN_001a7c70(int parent_handle __attribute__((unused)), int param_2 __attribute__((unused)), int param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[cce450]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001a7c70_2\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      ".LFUN_001a7c70_1:\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a7b50]\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[cce320]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_001a7c70_1\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001a7c70_2:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cce450] "m"(b1a7c70_cce450), [c1a7b50] "m"(b1a7c70_c1a7b50), [cce320] "m"(b1a7c70_cce320)
      : "memory");
}
#else
#error "FUN_001a7c70: clang naked draft required"
#endif


/* unit_inventory_next_grenade (0x1a9980)
 * Cycles through grenade types to find the next available one. */
int16_t unit_inventory_next_grenade(int unit_handle, int current_index, int16_t direction)
{
  char *unit;
  int16_t start;
  int16_t saved;
  int idx;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  saved = -1;
  start = (int16_t)current_index;
  if (start == -1) {
    current_index = 0;
    idx = current_index;
  } else {
    idx = current_index;
    if (start < 0 || 1 < start) {
      display_assert("current_index>=0 && current_index<NUMBER_OF_UNIT_GRENADE_TYPES",
                     "c:\\halo\\SOURCE\\units\\units.c", 0x163e, 1);
      system_exit(-1);
    }
  }
  do {
    start = (int16_t)current_index;
    if (*(char *)((int)start + 0x2ce + (int)unit) > '\0') {
      if (start != (int16_t)idx) {
        return start;
      }
      saved = (int16_t)current_index;
      if (direction == 0) {
        return start;
      }
    }
    if (direction < 0) {
      if (start == 0) {
        current_index = 1;
      } else {
        current_index = (int)start - 1;
      }
    } else if (start == 1) {
      current_index = 0;
    } else {
      current_index = (int)start + 1;
    }
    if ((int16_t)current_index == (int16_t)idx) {
      return saved;
    }
  } while (1);
}

/* unit_scripting_unit_riders (0x1a9e40)
 * Creates a list of all child units that have a seat assignment. */
int unit_scripting_unit_riders(int unit_handle)
{
  char *unit;
  int list;
  int child;
  char *child_obj;

  list = -1;
  if (unit_handle != -1) {
    unit = (char *)object_get_and_verify_type(unit_handle, 3);
    list = FUN_000ce200();
    if (list != -1) {
      child = *(int *)(unit + 0xc8);
      while (child != -1) {
        child_obj = (char *)object_get_and_verify_type(child, -1);
        if (((1 << (*(uint8_t *)(child_obj + 0x64) & 0x1f)) & 3u) != 0 &&
            *(int16_t *)(child_obj + 0x2a0) != -1) {
          FUN_000ce2b0(list, child);
        }
        child = *(int *)(child_obj + 0xc4);
      }
    }
  }
  return list;
}

/* units_debug_get_next_unit (0x1aa080)
 * Finds the next debug-selectable unit after current_unit. */
int units_debug_get_next_unit(int current_unit)
{
  int result;
  char *iVar1;
  char local_14[8];
  int local_c = 0;

  result = -1;
  if (current_unit != -1) {
    object_iterator_new(local_14, 3, 0);
    iVar1 = (char *)object_iterator_next(local_14);
    while (iVar1 != NULL && local_c != current_unit) {
      iVar1 = (char *)object_iterator_next(local_14);
    }
    iVar1 = (char *)object_iterator_next(local_14);
    while (iVar1 != NULL) {
      if (*(int *)(iVar1 + 0x1a4) == -1 &&
          *(int *)(iVar1 + 0x1a8) == -1 &&
          (*(uint8_t *)(iVar1 + 0xb6) & 4) == 0) {
        result = local_c;
        if (local_c != -1) {
          return local_c;
        }
        break;
      }
      iVar1 = (char *)object_iterator_next(local_14);
    }
  }
  object_iterator_new(local_14, 3, 0);
  iVar1 = (char *)object_iterator_next(local_14);
  while (1) {
    if (iVar1 == NULL) {
      return result;
    }
    if (*(int *)(iVar1 + 0x1a4) == -1 &&
        *(int *)(iVar1 + 0x1a8) == -1 &&
        (*(uint8_t *)(iVar1 + 0xb6) & 4) == 0) {
      break;
    }
    iVar1 = (char *)object_iterator_next(local_14);
  }
  return local_c;
}

/* unit_set_desired_flashlight_state (0x1aa550)
 * Sets the desired flashlight state. Bit 28=on, bit 29=off at +0x1B4. */
void unit_set_desired_flashlight_state(int unit_handle, char desired)
{
  char *unit;

  if (unit_handle != -1) {
    unit = (char *)object_get_and_verify_type(unit_handle, 3);
    if (desired != '\0') {
      *(uint32_t *)(unit + 0x1b4) |= 0x10000000;
    } else {
      *(uint32_t *)(unit + 0x1b4) |= 0x20000000;
    }
  }
}

/* unit_get_current_flashlight_state (0x1aa590)
 * Returns whether the flashlight is currently on. Bit 19 of +0x1B4. */
char unit_get_current_flashlight_state(int unit_handle)
{
  char *unit;

  if (unit_handle != -1) {
    unit = (char *)object_get_and_verify_type(unit_handle, 3);
    return (*(uint32_t *)(unit + 0x1b4) >> 0x13) & 1;
  }
  return 0;
}

/* unit_seat_filled (0x1aa700)
 * Returns true if any unit is sitting in the specified seat. */
char unit_seat_filled(int unit_handle, int16_t seat_index)
{
  char *iVar1;
  char local_14[16];

  object_iterator_new(local_14, 3, 0);
  iVar1 = (char *)object_iterator_next(local_14);
  while (1) {
    if (iVar1 == NULL) {
      return 0;
    }
    if (*(int *)(iVar1 + 0xcc) == unit_handle &&
        *(int16_t *)(iVar1 + 0x2a0) == seat_index) {
      break;
    }
    iVar1 = (char *)object_iterator_next(local_14);
  }
  return 1;
}

/* unit_seat_is_driver (0x1aa770)
 * Returns true if the seat at seat_index has the driver flag (bit 2). */
char unit_seat_is_driver(int unit_handle, int16_t seat_index)
{
  uint32_t *unit;
  char *unit_tag;
  uint32_t *seat;

  unit = (uint32_t *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (char *)tag_get(0x756e6974, *unit);
  if (seat_index >= 0) {
    if ((int)seat_index < *(int *)(unit_tag + 0x2e4)) {
      seat = (uint32_t *)tag_block_get_element(
          (int *)(unit_tag + 0x2e4), (int)seat_index, 0x11c);
      return (*seat >> 2) & 1;
    }
  }
  return 0;
}

/* unit_seat_is_gunner (0x1aa7d0)
 * Returns true if the seat at seat_index has the gunner flag (bit 3). */
char unit_seat_is_gunner(int unit_handle, int16_t seat_index)
{
  uint32_t *unit;
  char *unit_tag;
  uint32_t *seat;

  unit = (uint32_t *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (char *)tag_get(0x756e6974, *unit);
  if (seat_index >= 0) {
    if ((int)seat_index < *(int *)(unit_tag + 0x2e4)) {
      seat = (uint32_t *)tag_block_get_element(
          (int *)(unit_tag + 0x2e4), (int)seat_index, 0x11c);
      return (*seat >> 3) & 1;
    }
  }
  return 0;
}

/* unit_seat_allow_noncombatants (0x1aa830)
 * Returns true if the seat at seat_index allows noncombatants (bit 10). */
char unit_seat_allow_noncombatants(int unit_handle, int16_t seat_index)
{
  uint32_t *unit;
  char *unit_tag;
  uint32_t *seat;

  unit = (uint32_t *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (char *)tag_get(0x756e6974, *unit);
  if (seat_index >= 0) {
    if ((int)seat_index < *(int *)(unit_tag + 0x2e4)) {
      seat = (uint32_t *)tag_block_get_element(
          (int *)(unit_tag + 0x2e4), (int)seat_index, 0x11c);
      return (*seat >> 10) & 1;
    }
  }
  return 0;
}

/* unit_has_weapon_definition_index (0x1aad00)
 * Checks whether a unit is carrying a weapon with the given tag definition. */
char unit_has_weapon_definition_index(int unit_handle, int definition_index)
{
  char *unit;
  int weapon_handle;
  int *weapon;
  int16_t i;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  i = 0;
  do {
    weapon_handle = *(int *)(unit + 0x2a8 + i * 4);
    if (weapon_handle != -1) {
      weapon = (int *)object_get_and_verify_type(weapon_handle, 4);
      if (*weapon == definition_index) {
        return 1;
      }
    }
    i++;
  } while (i < 4);
  return 0;
}

/* unit_start_running_blindly (0x1ac450)
 *
 * Sets bit 25 (0x2000000) of unit flags at +0x1B4 and computes a random
 * blind-running direction stored at unit+0x3C4.
 *
 * If the unit has an actor (unit+0x1A4 != -1), tries to get a running blind
 * vector via actor_get_running_blind_vector. On success, stores 0 at +0x3C4
 * and uses a 25-degree random spread. On failure (or no actor), computes the
 * unit's facing yaw via vector_to_angles, wraps it to [0, pi), and uses a
 * 100-degree random spread.
 *
 * The final direction is: base_angle + random_real_range(seed, -spread, spread).
 *
 * Confirmed: PUSH [EBP+0x8] / PUSH 0x3 -> cdecl, 1 stack param.
 * Confirmed: TEST EAX,0x2000000 -> early exit if already running blindly.
 * Confirmed: OR EAX,0x2000000 -> set flag.
 * Confirmed: CALL 0x3ce40 = actor_get_running_blind_vector.
 * Confirmed: CALL 0x10cc00 = vector_to_angles.
 * Confirmed: FCOM [0x256980] (pi); FSUB [0x255a54] (2*pi) -> wrap to [0,pi).
 * Confirmed: 0x3edf66f3 = 0.4363f (25 deg), 0x3fdf66f3 = 1.7453f (100 deg).
 * Confirmed: push-then-fstp pattern for random_real_range float args.
 * Confirmed: FADD [ESI+0x3c4]; FSTP [ESI+0x3c4] -> accumulate into direction.
 */
void unit_start_running_blindly(int unit_handle)
{
  char *unit;
  uint32_t flags;
  int actor_handle;
  char has_blind_vector;
  float base_angle;
  float spread;
  int *seed;
  float angles[2];
  char blind_vector[12];

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  flags = *(uint32_t *)(unit + 0x1b4);
  if ((flags & 0x2000000) != 0) {
    return;
  }
  *(uint32_t *)(unit + 0x1b4) = flags | 0x2000000;

  actor_handle = *(int *)(unit + 0x1a4);
  if (actor_handle != -1) {
    has_blind_vector = actor_get_running_blind_vector(actor_handle, (float *)blind_vector);
  } else {
    has_blind_vector = 0;
  }

  if (has_blind_vector) {
    *(float *)(unit + 0x3c4) = 0.0f;
    spread = 0.4363323f;
  } else {
    vector_to_angles(angles, (float *)(unit + 0x24));
    base_angle = angles[0];
    if (base_angle > 3.1415927f) {
      base_angle = base_angle - 6.2831855f;
    }
    *(float *)(unit + 0x3c4) = base_angle;
    spread = 1.7453293f;
  }

  seed = get_global_random_seed_address();
  *(float *)(unit + 0x3c4) =
      random_real_range(seed, -spread, spread) + *(float *)(unit + 0x3c4);
}

/* unit_stop_running_blindly (0x1ac520)
 * Clears bit 25 (0x2000000) of unit flags at +0x1B4. */
void unit_stop_running_blindly(int unit_handle)
{
  char *unit;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  *(uint32_t *)(unit + 0x1b4) &= ~0x2000000u;
}

/* unit_flying_through_air (0x1ac650)
 * Returns true if this is a biped (type==0) and it's flying through air. */
char unit_flying_through_air(int unit_handle)
{
  char *unit;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  if (*(int16_t *)(unit + 0x64) == 0) {
    return FUN_001a0db0(unit_handle);
  }
  return 0;
}

/* unit_abort_animation (0x1ad7e0)
 * Aborts the current animation by calling FUN_001ad260 with state 0. */
void unit_abort_animation(int unit_handle)
{
  FUN_001ad260(unit_handle, 0);
}

/* unit_open (0x1ae160)
 * Opens a unit by transitioning to animation state 0x25. */
void unit_open(int unit_handle)
{
  if (unit_handle != -1) {
    FUN_001ad260(unit_handle, 0x25);
  }
}

/* unit_close (0x1ae180)
 * Closes a unit by transitioning to animation state 0x26. */
void unit_close(int unit_handle)
{
  if (unit_handle != -1) {
    FUN_001ad260(unit_handle, 0x26);
  }
}

/* units_set_desired_flashlight_state (0x1ae210)
 * Iterates child objects and sets flashlight state for each unit. */
void units_set_desired_flashlight_state(int object_list, char desired)
{
  int iter_state;
  int child;
  char *unit;
  uint32_t flags;

  child = FUN_000ce450(object_list, &iter_state);
  while (child != -1) {
    unit = (char *)object_try_and_get_and_verify_type(child, 3);
    if (unit != NULL && child != -1) {
      unit = (char *)object_get_and_verify_type(child, 3);
      if (desired == '\0') {
        flags = *(uint32_t *)(unit + 0x1b4) | 0x20000000;
      } else {
        flags = *(uint32_t *)(unit + 0x1b4) | 0x10000000;
      }
      *(uint32_t *)(unit + 0x1b4) = flags;
    }
    child = FUN_000ce320(object_list, &iter_state);
  }
}

/* unit_scripting_set_seat (0x1ae750)
 * Sets the unit's seat override from a seat name string. */
void unit_scripting_set_seat(int unit_handle, const char *seat_name)
{
  char *unit;
  char seat;

  if (unit_handle != -1) {
    unit = (char *)object_get_and_verify_type(unit_handle, 3);
    seat = (char)FUN_001ab730(seat_name);
    *(char *)(unit + 0x1bf) = seat;
  }
}

/* unit_handle_deleted_object (0x1ae780)
 * Cleans up references to a deleted object in all unit fields. */
void unit_handle_deleted_object(int unit_handle, int deleted_handle)
{
  char *unit;
  int16_t i;
  int *weapon_slot;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  if (*(int *)(unit + 0x244) == deleted_handle) {
    *(int *)(unit + 0x244) = -1;
  }
  if (*(int *)(unit + 0x2d4) == deleted_handle) {
    *(int *)(unit + 0x2d4) = -1;
  }
  if (*(int *)(unit + 0x2d8) == deleted_handle) {
    *(int *)(unit + 0x2d8) = -1;
  }
  i = 0;
  weapon_slot = (int *)(unit + 0x2a8);
  do {
    if (*weapon_slot == deleted_handle) {
      *weapon_slot = -1;
      if (i == *(int16_t *)(unit + 0x2a4)) {
        *(int16_t *)(unit + 0x2a4) = -1;
      }
      if (i == *(int16_t *)(unit + 0x2a2)) {
        *(int16_t *)(unit + 0x2a2) = -1;
      }
    }
    i++;
    weapon_slot++;
  } while (i < 4);
  if (*(int16_t *)(unit + 0x2a2) == -1) {
    *(int16_t *)(unit + 0x2a4) = FUN_001ae490(unit_handle, -1, 0);
  }
  if (*(int *)(unit + 0x2c8) == deleted_handle) {
    *(int *)(unit + 0x2c8) = -1;
  }
  if (*(int *)(unit + 0x3bc) == deleted_handle) {
    *(int *)(unit + 0x3bc) = -1;
  }
}

/* unit_stop_custom_animation (0x1af0d0)
 * Stops a custom animation if the current state is 0x1c. */
void unit_stop_custom_animation(int unit_handle)
{
  char *unit;

  if (unit_handle != -1) {
    unit = (char *)object_get_and_verify_type(unit_handle, 3);
    if (*(char *)(unit + 0x253) == '\x1c') {
      FUN_001ad260(unit_handle, 0);
    }
  }
}

/* unit_custom_animation_at_frame (0x1af100)
 * Starts a custom animation and sets it to a specific frame. */
char unit_custom_animation_at_frame(int unit_handle, int param_2, int param_3, int param_4,
                                    int16_t frame)
{
  char *unit;
  char *anim_tag;
  char *anim_entry;

  if (!FUN_001ac180(unit_handle, param_2, (void *)param_3, param_4)) {
    return 0;
  }
  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  anim_tag = (char *)tag_get(0x616e7472, *(int *)(unit + 0x7c));
  anim_entry = (char *)tag_block_get_element(
      (int *)(anim_tag + 0x74),
      (int)*(int16_t *)(unit + 0x80), 0xb4);
  if (frame >= 0 && frame < *(int16_t *)(anim_entry + 0x22)) {
    *(int16_t *)(unit + 0x82) = frame;
    return 1;
  }
  return 0;
}

/* unit_has_animation_to_enter_seat (0x1b0d00)
 * Returns true if the unit has an animation to enter the given seat. */
char unit_has_animation_to_enter_seat(int unit_handle, int vehicle_handle, int16_t seat_index)
{
  uint32_t *vehicle;
  char *unit_tag;
  char *unit_data;
  char *seat_entry;

  vehicle = (uint32_t *)object_get_and_verify_type(vehicle_handle, 3);
  unit_tag = (char *)tag_get(0x756e6974, *vehicle);
  if (seat_index >= 0) {
    if ((int)seat_index < *(int *)(unit_tag + 0x2e4)) {
      unit_data = (char *)object_get_and_verify_type(unit_handle, 3);
      if (*(int16_t *)(unit_data + 0x64) != 1) {
        seat_entry = (char *)tag_block_get_element(
            (int *)(unit_tag + 0x2e4), (int)seat_index, 0x11c);
        if (!FUN_001acd70(unit_handle, (const char *)(seat_entry + 4), 0, 0)) {
          return 0;
        }
      }
      return 1;
    }
  }
  return 0;
}

/* unit_get_zoom_magnification (0x1b1350)
 * Returns the zoom magnification for the current weapon. */
float unit_get_zoom_magnification(int unit_handle, int zoom_level)
{
  char *unit;
  int weapon;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  weapon = unit_get_weapon(unit_handle, (int)*(int16_t *)(unit + 0x2a2));
  if (weapon != -1) {
    return weapon_get_zoom_magnification(weapon, zoom_level);
  }
  return 1.0f;
}

/* unit_inventory_next_weapon (0x1b1b40)
 * Advances to the next weapon in the inventory. */
int unit_inventory_next_weapon(int unit_handle, int slot, int direction)
{
  return FUN_001ae490(unit_handle, slot, direction);
}

/* FUN_001a7a90 (0x1a7a90)
 * Applies damage to an object if it's not dead (bit 2 of +0xB6 clear).
 *
 * body_dmg/shield_dmg are passed BY VALUE. The original (delinked) takes three
 * 4-byte stack args at [ebp+8]/[ebp+0xc]/[ebp+0x10] and does
 *   lea ecx,[ebp+0xc]  (&body_dmg) / lea eax,[ebp+0x10] (&shield_dmg)
 * to box the by-value floats into the pointers FUN_001365d0 expects (1365d0
 * dereferences arg2/arg3). Declaring them as float* and forwarding the pointers
 * reinterprets the float bit-pattern (1.0f == 0x3f800000) as an address and
 * dereferences it — an infinite page-fault storm that froze PoA after the intro
 * (FUN_000bf380 calls this with floats pushed by value). */
void FUN_001a7a90(int param_1, float body_dmg, float shield_dmg)
{
  char *obj;

  if (param_1 != -1) {
    obj = (char *)object_get_and_verify_type(param_1, -1);
    if ((*(uint8_t *)(obj + 0xb6) & 4) == 0) {
      FUN_001365d0(param_1, &body_dmg, &shield_dmg);
    }
  }
}

/* FUN_001a7ad0 (0x1a7ad0) — XBE naked draft (batch 66). */
#if defined(__clang__)
static int (*const b1a7ad0_cce450)(int parent_handle, int *iter_state) = FUN_000ce450;
static void *(*const b1a7ad0_get)(int, int) = object_get_and_verify_type;
static void (*const b1a7ad0_c1365d0)(int object_handle, float *body_vitality_override, float *shield_vitality_override) = FUN_001365d0;
static int (*const b1a7ad0_cce320)(int parent_handle, int *iter_state) = FUN_000ce320;

__attribute__((naked, noinline))
void FUN_001a7ad0(int parent_handle __attribute__((unused)), int param_2 __attribute__((unused)), int param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[cce450]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_001a7ad0_3\n\t"
      "nop\n\t"
      ".LFUN_001a7ad0_1:\n\t"
      "cmpl $-1, %%esi\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "je .LFUN_001a7ad0_2\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movb 0xb6(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $4, %%cl\n\t"
      "jne .LFUN_001a7ad0_2\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1365d0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001a7ad0_2:\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[cce320]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "jne .LFUN_001a7ad0_1\n\t"
      ".LFUN_001a7ad0_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cce450] "m"(b1a7ad0_cce450), [get] "m"(b1a7ad0_get), [c1365d0] "m"(b1a7ad0_c1365d0), [cce320] "m"(b1a7ad0_cce320)
      : "memory");
}
#else
#error "FUN_001a7ad0: clang naked draft required"
#endif


/* FUN_001a7b50 (0x1a7b50) — XBE naked draft (batch 62). */
#if defined(__clang__)
static void *(*const b1a7b50_get)(int, int) = object_get_and_verify_type;
static void (*const b1a7b50_c136b40)(int object_handle) = FUN_00136b40;
static void (*const b1a7b50_c137540)(int object_handle) = object_deplete_body;

__attribute__((naked, noinline))
void FUN_001a7b50(int datum_handle __attribute__((unused)), float body_damage __attribute__((unused)), float shield_damage __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_001a7b50_10\n\t"
      "pushl %%esi\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0xb6(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb $4, %%al\n\t"
      "jne .LFUN_001a7b50_9\n\t"
      "flds 0x8c(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_001a7b50_1\n\t"
      "movl $0, 0x8(%%ebp)\n\t"
      "jmp .LFUN_001a7b50_3\n\t"
      ".LFUN_001a7b50_1:\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fcomps 0x8c(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001a7b50_2\n\t"
      "movl $0x3f800000, 0x8(%%ebp)\n\t"
      "jmp .LFUN_001a7b50_3\n\t"
      ".LFUN_001a7b50_2:\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fdivs 0x8c(%%esi)\n\t"
      "fstps 0x8(%%ebp)\n\t"
      ".LFUN_001a7b50_3:\n\t"
      "flds 0x88(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_001a7b50_4\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001a7b50_6\n\t"
      ".LFUN_001a7b50_4:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x88(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001a7b50_5\n\t"
      "movl $0x3f800000, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001a7b50_6\n\t"
      ".LFUN_001a7b50_5:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fdivs 0x88(%%esi)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".LFUN_001a7b50_6:\n\t"
      "flds 0x94(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a7b50_7\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_001a7b50_7\n\t"
      "pushl %%edi\n\t"
      "call *%[c136b40]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001a7b50_7:\n\t"
      "flds 0x90(%%esi)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "fcomps 0x2533c0\n\t"
      "movl %%eax, 0x94(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001a7b50_8\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_001a7b50_8\n\t"
      "pushl %%edi\n\t"
      "call *%[c137540]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001a7b50_8:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x90(%%esi)\n\t"
      ".LFUN_001a7b50_9:\n\t"
      "popl %%esi\n\t"
      ".LFUN_001a7b50_10:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a7b50_get), [c136b40] "m"(b1a7b50_c136b40), [c137540] "m"(b1a7b50_c137540)
      : "memory");
}
#else
#error "FUN_001a7b50: clang naked draft required"
#endif


/* unit_test_spawning (0x1a9130)
 * Tests if unit should spawn attached objects on death. */
uint32_t unit_test_spawning(int unit_handle)
{
  uint32_t *unit;
  char *unit_tag;
  uint32_t flags;
  int *seed;
  int16_t count;

  unit = (uint32_t *)object_get_and_verify_type(unit_handle, 3);
  flags = unit[0x6d];
  if ((flags & 0x20000) == 0) {
    unit_tag = (char *)tag_get(0x756e6974, *unit);
    if (*(int *)(unit_tag + 0x258) != -1) {
      seed = get_global_random_seed_address();
      count = random_range((unsigned int *)seed,
          *(int16_t *)(unit_tag + 0x25c),
          (int16_t)(*(int16_t *)(unit_tag + 0x25e) + 1));
      if (count > 0) {
        FUN_0003f350(unit_handle, *(int *)(unit_tag + 0x258), count,
                     *(float *)(unit_tag + 0x260) * *(float *)0x2546a4);
      }
      unit[0x6d] = unit[0x6d] | 0x20000;
      return flags;
    }
  }
  return flags & 0xffff0000;
}

/* scripting_set_magic_base_seat (0x1ae730)
 * Sets the global magic base seat from a seat name string. */
void scripting_set_magic_base_seat(const char *param_1)
{
  *(int16_t *)0x32de80 = FUN_001ab730(param_1);
}

/* FUN_001a7790 (0x1a7790) — XBE naked draft (batch 53). */
#if defined(__clang__)
static void *(*const b1a7790_get)(int, int) = object_get_and_verify_type;
static void (*const b1a7790_c1a7730)(int unit_handle) = FUN_001a7730;
static short (*const b1a7790_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static int (*const b1a7790_c1c7e70)(int object_handle, int tag_index, int16_t marker, float *position, float *forward, float scale) = object_impulse_sound_new;
static void (*const b1a7790_c44fd0)(int unit_handle, uint16_t priority, uint16_t type, void *comm_data) = FUN_00044fd0;
static void (*const b1a7790_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1a7790_exitfn)(int) = system_exit;
static void (*const b1a7790_c46530)(int unit_handle, uint16_t priority, uint16_t type, int unk, int unk2, void *comm_data) = FUN_00046530;
static void (*const b1a7790_c45290)(int unit_handle, uint16_t priority, uint16_t type, void *comm_data) = FUN_00045290;
static void (*const b1a7790_c1a6ef0)(int actor, short count, void *comm_buf) = FUN_001a6ef0;

__attribute__((naked, noinline))
void FUN_001a7790(int param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x84, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x1b4(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_001a7790_1\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1a7730]\n\t"
      "andl $0xfffffeff, 0x1b4(%%esi)\n\t"
      ".LFUN_001a7790_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x398(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_001a7790_2\n\t"
      "decl %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "movw %%ax, 0x398(%%esi)\n\t"
      "jne .LFUN_001a7790_2\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x39a(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_001a7790_2\n\t"
      "decl %%eax\n\t"
      "movw %%ax, 0x39a(%%esi)\n\t"
      "movw $0x16, 0x398(%%esi)\n\t"
      ".LFUN_001a7790_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x39c(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_001a7790_3\n\t"
      "decl %%eax\n\t"
      "movw %%ax, 0x39c(%%esi)\n\t"
      ".LFUN_001a7790_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x39c(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_001a7790_4\n\t"
      "decl %%eax\n\t"
      "movw %%ax, 0x39c(%%esi)\n\t"
      ".LFUN_001a7790_4:\n\t"
      "cmpw $0, 0x338(%%esi)\n\t"
      "jle .LFUN_001a7790_15\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x3a8(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_001a7790_5\n\t"
      "decl %%eax\n\t"
      "movw %%ax, 0x3a8(%%esi)\n\t"
      "jmp .LFUN_001a7790_15\n\t"
      ".LFUN_001a7790_5:\n\t"
      "movb 0x3a4(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a7790_9\n\t"
      "pushl $1\n\t"
      "leal -0x84(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2909e4\n\t"
      "pushl %%edi\n\t"
      "call *%[markers]\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_001a7790_6\n\t"
      "movl -0x58(%%ebp), %%edx\n\t"
      "movl -0x54(%%ebp), %%eax\n\t"
      "movl -0x84(%%ebp), %%ecx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl -0x50(%%ebp), %%edx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl -0x7c(%%ebp), %%eax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl -0x78(%%ebp), %%edx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl -0x74(%%ebp), %%eax\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "jmp .LFUN_001a7790_7\n\t"
      ".LFUN_001a7790_6:\n\t"
      "movl 0x31fc1c, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl 0x31fc3c, %%eax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".LFUN_001a7790_7:\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl 0x33c(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001a7790_8\n\t"
      "pushl $0x3f800000\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c1c7e70]\n\t"
      "addl $0x18, %%esp\n\t"
      "movl %%eax, 0x3b0(%%esi)\n\t"
      ".LFUN_001a7790_8:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x33a(%%esi), %%cx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x338(%%esi), %%dx\n\t"
      "leal 0x348(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c44fd0]\n\t"
      "addl $0x10, %%esp\n\t"
      "movb $1, 0x3a4(%%esi)\n\t"
      ".LFUN_001a7790_9:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x3ac(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_001a7790_10\n\t"
      "decl %%eax\n\t"
      "movw %%ax, 0x3ac(%%esi)\n\t"
      ".LFUN_001a7790_10:\n\t"
      "cmpw $0, 0x3aa(%%esi)\n\t"
      "jle .LFUN_001a7790_12\n\t"
      "cmpw $0, 0x338(%%esi)\n\t"
      "jg .LFUN_001a7790_11\n\t"
      "pushl $1\n\t"
      "pushl $0x2f5\n\t"
      "pushl $0x2b66ec\n\t"
      "pushl $0x2b6784\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a7790_11:\n\t"
      "decw 0x3aa(%%esi)\n\t"
      "cmpw $0, 0x3aa(%%esi)\n\t"
      "jne .LFUN_001a7790_15\n\t"
      "movl $0xffffffff, 0x3b0(%%esi)\n\t"
      "jmp .LFUN_001a7790_15\n\t"
      ".LFUN_001a7790_12:\n\t"
      "movb 0x3a6(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a7790_13\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x33a(%%esi), %%cx\n\t"
      "leal 0x348(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x338(%%esi), %%dx\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c46530]\n\t"
      "addl $0x18, %%esp\n\t"
      "movb $1, 0x3a6(%%esi)\n\t"
      ".LFUN_001a7790_13:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x3ae(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_001a7790_14\n\t"
      "decl %%eax\n\t"
      "movw %%ax, 0x3ae(%%esi)\n\t"
      ".LFUN_001a7790_14:\n\t"
      "cmpw $0, 0x3ae(%%esi)\n\t"
      "jne .LFUN_001a7790_15\n\t"
      "movw $0, 0x3ac(%%esi)\n\t"
      ".LFUN_001a7790_15:\n\t"
      "cmpw $0, 0x3ac(%%esi)\n\t"
      "jne .LFUN_001a7790_16\n\t"
      "movb 0x3a5(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a7790_16\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x33a(%%esi), %%cx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x338(%%esi), %%dx\n\t"
      "leal 0x348(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c45290]\n\t"
      "addl $0x10, %%esp\n\t"
      "movb $1, 0x3a5(%%esi)\n\t"
      ".LFUN_001a7790_16:\n\t"
      "cmpw $0, 0x338(%%esi)\n\t"
      "jle .LFUN_001a7790_18\n\t"
      "cmpw $0, 0x3aa(%%esi)\n\t"
      "jne .LFUN_001a7790_17\n\t"
      "cmpw $0, 0x3ae(%%esi)\n\t"
      "jne .LFUN_001a7790_17\n\t"
      "movw $0, 0x338(%%esi)\n\t"
      ".LFUN_001a7790_17:\n\t"
      "cmpw $0, 0x338(%%esi)\n\t"
      ".LFUN_001a7790_18:\n\t"
      "jne .LFUN_001a7790_19\n\t"
      "cmpw $0, 0x368(%%esi)\n\t"
      "leal 0x368(%%esi), %%eax\n\t"
      "jle .LFUN_001a7790_19\n\t"
      "pushl %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a6ef0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001a7790_19:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [get] "m"(b1a7790_get), [c1a7730] "m"(b1a7790_c1a7730), [markers] "m"(b1a7790_markers), [c1c7e70] "m"(b1a7790_c1c7e70), [c44fd0] "m"(b1a7790_c44fd0), [assert] "m"(b1a7790_assert), [exitfn] "m"(b1a7790_exitfn), [c46530] "m"(b1a7790_c46530), [c45290] "m"(b1a7790_c45290), [c1a6ef0] "m"(b1a7790_c1a6ef0)
      : "memory");
}
#else
#error "FUN_001a7790: clang naked draft required"
#endif


/* FUN_001a6bf0 (0x1a6bf0) — XBE naked draft (batch 64). */
#if defined(__clang__)
static void *(*const b1a6bf0_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a6bf0_tag)(int, int) = tag_get;
static void *(*const b1a6bf0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1a6bf0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_001a6bf0(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $0, 0x6e(%%esi)\n\t"
      "jne .LFUN_001a6bf0_6\n\t"
      "pushl %%ebx\n\t"
      "leal 0x2b4(%%eax), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_001a6bf0_5\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001a6bf0_1:\n\t"
      "pushl $0x18\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "movw (%%eax), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0x64, %%ax\n\t"
      "jge .LFUN_001a6bf0_2\n\t"
      "cmpw $0x10, %%di\n\t"
      "jae .LFUN_001a6bf0_3\n\t"
      "movswl %%di, %%edx\n\t"
      "movw %%ax, -0x24(%%ebp,%%edx,2)\n\t"
      "incl %%edi\n\t"
      ".LFUN_001a6bf0_2:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_001a6bf0_1\n\t"
      "jmp .LFUN_001a6bf0_4\n\t"
      ".LFUN_001a6bf0_3:\n\t"
      "pushl $0x2b6714\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001a6bf0_4:\n\t"
      "testw %%di, %%di\n\t"
      "jle .LFUN_001a6bf0_5\n\t"
      "movl 0x4e4cf4, %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "movswl %%di, %%esi\n\t"
      "cdq\n\t"
      "idivl %%esi\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, 0x4e4cf4\n\t"
      "movw -0x24(%%ebp,%%edx,2), %%ax\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movw %%ax, 0x6e(%%edx)\n\t"
      ".LFUN_001a6bf0_5:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001a6bf0_6:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a6bf0_get), [tag] "m"(b1a6bf0_tag), [elem] "m"(b1a6bf0_elem), [c8f390] "m"(b1a6bf0_c8f390)
      : "memory");
}
#else
#error "FUN_001a6bf0: clang naked draft required"
#endif


/* FUN_001a70d0 (0x1a70d0) — XBE naked draft (batch 63). */
#if defined(__clang__)
static void *(*const b1a70d0_get)(int, int) = object_get_and_verify_type;
static short (*const b1a70d0_c1a68d0)(int unit_handle, short priority, char param_3, char param_4, int *param_5, short *vocalization_type_ref, int *sound_definition_index_ref) = FUN_001a68d0;
static void *(*const b1a70d0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b1a70d0_c42d20)(void *packet) = ai_communication_packet_new;
static void (*const b1a70d0_c1a6ef0)(int actor, short count, void *comm_buf) = FUN_001a6ef0;
static void (*const b1a70d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1a70d0_exitfn)(int) = system_exit;
static void (*const b1a70d0_c44fd0)(int unit_handle, uint16_t priority, uint16_t type, void *comm_data) = FUN_00044fd0;

__attribute__((naked, noinline))
void FUN_001a70d0(int unit_handle __attribute__((unused)), int sound_tag __attribute__((unused)), int sound_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x34, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl %%eax, %%esi\n\t"
      "leal 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $6\n\t"
      "pushl %%edi\n\t"
      "movl $0xffffffff, -0x4(%%ebp)\n\t"
      "movl %%ebx, 0xc(%%ebp)\n\t"
      "call *%[c1a68d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "jg .LFUN_001a70d0_1\n\t"
      "movl $2, 0xc(%%ebp)\n\t"
      ".LFUN_001a70d0_1:\n\t"
      "pushl $0x30\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movw $6, -0x34(%%ebp)\n\t"
      "movw $0xffff, -0x32(%%ebp)\n\t"
      "movl %%ebx, -0x30(%%ebp)\n\t"
      "movw $0x18, -0x28(%%ebp)\n\t"
      "call *%[c42d20]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a6ef0]\n\t"
      "movl 0x33c(%%esi), %%eax\n\t"
      "addl $0x1c, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .LFUN_001a70d0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x196\n\t"
      "pushl $0x2b66ec\n\t"
      "pushl $0x2b67e0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a70d0_2:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%eax, 0x3b0(%%esi)\n\t"
      "movb $1, 0x3a4(%%esi)\n\t"
      "movw $0, 0x3a8(%%esi)\n\t"
      "addl $0x348, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $-1\n\t"
      "pushl $6\n\t"
      "pushl %%edi\n\t"
      "call *%[c44fd0]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a70d0_get), [c1a68d0] "m"(b1a70d0_c1a68d0), [memset] "m"(b1a70d0_memset), [c42d20] "m"(b1a70d0_c42d20), [c1a6ef0] "m"(b1a70d0_c1a6ef0), [assert] "m"(b1a70d0_assert), [exitfn] "m"(b1a70d0_exitfn), [c44fd0] "m"(b1a70d0_c44fd0)
      : "memory");
}
#else
#error "FUN_001a70d0: clang naked draft required"
#endif


/* unit_export_function_values (0x1a8010)
 * Exports 4 animation function values from unit tag to unit+0xD4. */
void unit_export_function_values(int unit_handle)
{
  uint32_t *unit;
  char *unit_tag;
  float fVar1;
  float *pfVar4;
  int16_t *psVar5;
  char *anim_tag;
  char *anim_entry;
  int local_8;

  unit = (uint32_t *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (char *)tag_get(0x756e6974, *unit);
  pfVar4 = (float *)(unit + 0x35);
  psVar5 = (int16_t *)(unit_tag + 0x198);
  local_8 = 4;
  do {
    if (*psVar5 != 0) {
      fVar1 = 0.0f;
      switch (*psVar5) {
      case 1:
        fVar1 = *(float *)(unit + 0xba);
        break;
      case 2:
        fVar1 = *(float *)(unit + 0xbb);
        break;
      case 3:
        fVar1 = (float)*(uint8_t *)((char *)unit + 0x2d3) * *(float *)0x261518;
        break;
      case 4:
        fVar1 = *(float *)(unit + 0xa6);
        break;
      case 5:
        fVar1 = *(float *)(unit + 0xbc);
        break;
      case 6:
        if ((*(uint8_t *)((char *)unit + 0xb6) & 4) == 0 &&
            (unit[0x6d] & 0x400000) == 0) {
          fVar1 = *(float *)0x2533c8;
        }
        break;
      case 7:
        anim_tag = (char *)tag_get(0x616e7472, unit[0x1f]);
        anim_entry = (char *)tag_block_get_element(
            (int *)(anim_tag + 0x74),
            (int)*(int16_t *)(unit + 0x20), 0xb4);
        if (*(int16_t *)(unit + 0x20) < *(int16_t *)(anim_entry + 0x2e)) {
          fVar1 = (float)(int)*(int16_t *)(unit + 0x20) /
                  (float)(int)*(int16_t *)(anim_entry + 0x2e);
        } else {
          fVar1 = *(float *)0x2533c8 -
                  (float)(int)*(int8_t *)((char *)unit + 0x1be) * *(float *)0x26f2e0;
        }
        break;
      }
      *pfVar4 = fVar1;
    }
    psVar5++;
    pfVar4++;
    local_8--;
  } while (local_8 != 0);
}

/* unit_get_melee_range_and_ticks (0x1a83e0)
 * Gets melee attack animation timing data. */
char unit_get_melee_range_and_ticks(int unit_handle, char is_secondary,
    int *out_tick_count, float *out_attack_time, int16_t *out_frame_count,
    float *out_damage_time)
{
  uint32_t *unit;
  char *unit_tag;
  char *anim_tag;
  char *anim_set;
  char *anim_mode;
  int anim_index;
  int16_t anim_id;

  unit = (uint32_t *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (char *)tag_get(0x756e6974, *unit);
  tag_get(0x6d6f6465, *(int *)(unit_tag + 0x34));
  anim_tag = (char *)tag_get(0x616e7472, *(int *)(unit_tag + 0x44));
  anim_set = (char *)tag_block_get_element(
      (int *)(anim_tag + 0xc), (int)*(int8_t *)(unit + 0x94), 100);
  anim_mode = (char *)tag_block_get_element(
      (int *)(anim_set + 0x58), (int)*(int8_t *)((char *)unit + 0x251), 0xbc);
  anim_index = (-(uint32_t)(is_secondary != '\0') & 3) + 0x27;
  if (anim_index < *(int *)(anim_mode + 0x98)) {
    anim_id = *(int16_t *)(*(int *)(anim_mode + 0x9c) + anim_index * 2);
  } else {
    anim_id = -1;
  }
  if (anim_id == -1) {
    return 0;
  }
  anim_tag = (char *)tag_block_get_element(
      (int *)(anim_tag + 0x74), (int)anim_id, 0xb4);
  FUN_00120710((int)anim_tag, (int)out_attack_time, (int)out_damage_time);
  if (out_tick_count != NULL) {
    *out_tick_count = (int)*(int16_t *)(anim_tag + 0x34);
  }
  if (out_frame_count != NULL) {
    *out_frame_count = *(int16_t *)(anim_tag + 0x22);
  }
  return 1;
}

/* unit_set_seat (0x1ae1e0)
 * Attempts to set the unit's seat via animation lookup. */
char unit_set_seat(int unit_handle, int seat_name)
{
  /* `!!` triggers VC71's branchless neg/sbb/neg bool-normalize (matching the
   * original at 0x1ae1f8) rather than a test/setne branch. Runtime-identical. */
  return (char)!!FUN_001acd70(unit_handle, (const char *)seat_name, 0, 1);
}

/* unit_start_flaming_to_death (0x1af2a0)
 * Initiates the flaming-to-death state for a unit. */
void unit_start_flaming_to_death(int unit_handle, int param_2)
{
  char *unit;
  int *seed;
  int16_t ticks;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  unit_set_in_vehicle(unit_handle, 1);
  *(uint32_t *)(unit + 0x1b4) |= 0x80;
  *(uint16_t *)(unit + 0xb6) = (*(uint16_t *)(unit + 0xb6) & ~0x4u) | 0x800;
  if (*(char *)(unit + 0x23b) == '\0') {
    seed = get_global_random_seed_address();
    ticks = random_range((unsigned int *)seed, 0x3c, 0x96);
    if (ticks < 1) {
      ticks = 1;
    } else if (ticks > 0xff) {
      ticks = 0xff;
    }
    *(char *)(unit + 0x23b) = (char)ticks;
    *(int *)(unit + 0x3c0) = param_2;
    unit_start_running_blindly(unit_handle);
  }
}

/* unit_handle_region_destroyed (0x1abcd0)
 * Triggers scream when a body region is destroyed. */
void unit_handle_region_destroyed(int unit_handle, int param_2, uint32_t flags)
{
  char *unit;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  if ((*(uint8_t *)(unit + 0xb6) & 4) == 0) {
    FUN_001a74d0(unit_handle, ((flags & 0x200) != 0) + 3);
  }
}


/* unit_aiming_vector (0x1ab410) — XBE naked draft (batch 49). */
#if defined(__clang__)
static void *(*const b1ab410_get)(int, int) = object_get_and_verify_type;
static void *(*const b1ab410_tag)(int, int) = tag_get;
static void *(*const b1ab410_elem)(void *, int, int) = tag_block_get_element;
static short (*const b1ab410_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static vector3_t * (*const b1ab410_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static void (*const b1ab410_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1ab410_exitfn)(int) = system_exit;
static int (*const b1ab410_c1dd801)(const char *a, const char *b) = crt_stricmp;

__attribute__((naked, noinline))
void unit_aiming_vector(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x78, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lunit_aiming_vector_1\n\t"
      "cmpw $-1, 0x2a0(%%esi)\n\t"
      "je .Lunit_aiming_vector_1\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movswl 0x2a0(%%esi), %%edx\n\t"
      "pushl $0x11c\n\t"
      "pushl %%edx\n\t"
      "addl $0x2e4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0xcc(%%esi), %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $1\n\t"
      "leal -0x78(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x24(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[markers]\n\t"
      "addl $0x2c, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Lunit_aiming_vector_12\n\t"
      "movl 0xcc(%%esi), %%ecx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1412f0]\n\t"
      "addl $8, %%esp\n\t"
      "leal 0x64(%%edi), %%eax\n\t"
      "jmp .Lunit_aiming_vector_2\n\t"
      ".Lunit_aiming_vector_1:\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "leal 0xc(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "leal 0x24(%%esi), %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "movl %%ecx, -0x3c(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "leal 0x30(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "addl $0x200, %%eax\n\t"
      ".Lunit_aiming_vector_2:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "leal 0x2fc(%%esi), %%ecx\n\t"
      "fsubs (%%ecx)\n\t"
      "leal 0x308(%%esi), %%edx\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fsubs 0x300(%%esi)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fsubs 0x304(%%esi)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsubs (%%edx)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fsubs 0x30c(%%esi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fsubs 0x310(%%esi)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmul %%st(7), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmul %%st(6), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fmuls (%%eax)\n\t"
      "fadds 0x253398\n\t"
      "fstps 0x320(%%esi)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "fxch %%st(1)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fxch %%st(1)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fadds 0x253398\n\t"
      "fstps 0x324(%%esi)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "fadds 0x253398\n\t"
      "fstps 0x328(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x320(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lunit_aiming_vector_3\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lunit_aiming_vector_5\n\t"
      ".Lunit_aiming_vector_3:\n\t"
      "flds 0x320(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_aiming_vector_4\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Lunit_aiming_vector_5\n\t"
      ".Lunit_aiming_vector_4:\n\t"
      "flds 0x320(%%esi)\n\t"
      ".Lunit_aiming_vector_5:\n\t"
      "fstps 0x320(%%esi)\n\t"
      "flds 0x324(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lunit_aiming_vector_6\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lunit_aiming_vector_8\n\t"
      ".Lunit_aiming_vector_6:\n\t"
      "flds 0x324(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_aiming_vector_7\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Lunit_aiming_vector_8\n\t"
      ".Lunit_aiming_vector_7:\n\t"
      "flds 0x324(%%esi)\n\t"
      ".Lunit_aiming_vector_8:\n\t"
      "fstps 0x324(%%esi)\n\t"
      "flds 0x328(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lunit_aiming_vector_9\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lunit_aiming_vector_11\n\t"
      ".Lunit_aiming_vector_9:\n\t"
      "flds 0x328(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_aiming_vector_10\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Lunit_aiming_vector_11\n\t"
      ".Lunit_aiming_vector_10:\n\t"
      "flds 0x328(%%esi)\n\t"
      ".Lunit_aiming_vector_11:\n\t"
      "fstps 0x328(%%esi)\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lunit_aiming_vector_12:\n\t"
      "movl $0x3f000000, %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x328(%%esi)\n\t"
      "movl %%eax, 0x324(%%esi)\n\t"
      "movl %%eax, 0x320(%%esi)\n\t"
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
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "testw %%si, %%si\n\t"
      "jl .Lunit_aiming_vector_13\n\t"
      "cmpw $6, %%si\n\t"
      "jl .Lunit_aiming_vector_14\n\t"
      ".Lunit_aiming_vector_13:\n\t"
      "pushl $1\n\t"
      "pushl $0x200f\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b6de0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movswl %%si, %%eax\n\t"
      "movl 0x32e484(,%%eax,4), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "ret\n\t"
      ".Lunit_aiming_vector_14:\n\t"
      "movswl %%si, %%ecx\n\t"
      "movl 0x32e484(,%%ecx,4), %%eax\n\t"
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
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "xorl %%esi, %%esi\n\t"
      "jmp .Lunit_aiming_vector_15\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lunit_aiming_vector_15:\n\t"
      "movswl %%si, %%eax\n\t"
      "movl 0x32e484(,%%eax,4), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lunit_aiming_vector_16\n\t"
      "incl %%esi\n\t"
      "cmpw $6, %%si\n\t"
      "jl .Lunit_aiming_vector_15\n\t"
      "popl %%esi\n\t"
      "movw %%bx, %%ax\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      ".Lunit_aiming_vector_16:\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1ab410_get), [tag] "m"(b1ab410_tag), [elem] "m"(b1ab410_elem), [markers] "m"(b1ab410_markers), [c1412f0] "m"(b1ab410_c1412f0), [assert] "m"(b1ab410_assert), [exitfn] "m"(b1ab410_exitfn), [c1dd801] "m"(b1ab410_c1dd801)
      : "memory");
}
#else
#error "unit_aiming_vector: clang naked draft required"
#endif


/* unit_drop_grenades_on_death (0x1abb20) — XBE naked draft (batch 89). */
#if defined(__clang__)
static void *(*const b1abb20_get)(int, int) = object_get_and_verify_type;
static void * (*const b1abb20_c18e450)(void) = game_globals_get;
static void *(*const b1abb20_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1abb20_opnew)(void *, int, int) = object_placement_data_new;
static int (*const b1abb20_onew)(void *) = object_new;
static void (*const b1abb20_c13fd00)(int object_handle) = object_disconnect_from_map;
static void (*const b1abb20_c1ab990)(int unit_handle, int weapon_handle) = unit_detach_weapon;

__attribute__((naked, noinline))
void unit_drop_grenades_on_death(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x94, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl $0xfffffd32, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "subl %%eax, %%esi\n\t"
      "leal 0x2ce(%%eax), %%ebx\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "movl $2, -0x4(%%ebp)\n\t"
      ".Lunit_drop_grenades_on_death_1:\n\t"
      "leal (%%esi,%%ebx,1), %%eax\n\t"
      "pushl $0x44\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e450]\n\t"
      "addl $0x128, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movb (%%ebx), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jle .Lunit_drop_grenades_on_death_4\n\t"
      ".Lunit_drop_grenades_on_death_2:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x30(%%ecx), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "leal -0x94(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[opnew]\n\t"
      "leal -0x94(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[onew]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lunit_drop_grenades_on_death_3\n\t"
      "pushl %%esi\n\t"
      "call *%[c13fd00]\n\t"
      "addl $4, %%esp\n\t"
      "call *%[c1ab990]\n\t"
      ".Lunit_drop_grenades_on_death_3:\n\t"
      "movb (%%ebx), %%cl\n\t"
      "decb %%cl\n\t"
      "movb %%cl, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb %%cl, (%%ebx)\n\t"
      "jg .Lunit_drop_grenades_on_death_2\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      ".Lunit_drop_grenades_on_death_4:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "incl %%ebx\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .Lunit_drop_grenades_on_death_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1abb20_get), [c18e450] "m"(b1abb20_c18e450), [elem] "m"(b1abb20_elem), [opnew] "m"(b1abb20_opnew), [onew] "m"(b1abb20_onew), [c13fd00] "m"(b1abb20_c13fd00), [c1ab990] "m"(b1abb20_c1ab990)
      : "memory");
}
#else
#error "unit_drop_grenades_on_death: clang naked draft required"
#endif


/* unit_drop_weapons_on_death (0x1abbd0) — XBE naked draft (batch 58). */
#if defined(__clang__)
static void *(*const b1abbd0_get)(int, int) = object_get_and_verify_type;
static const char * (*const b1abbd0_c1ba1f0)(int tag_index) = tag_get_name;
static char * (*const b1abbd0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b1abbd0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1abbd0_exitfn)(int) = system_exit;
static void (*const b1abbd0_c1ab990)(int unit_handle, int weapon_handle) = unit_detach_weapon;
static char (*const b1abbd0_cfaf50)(int weapon_handle) = weapon_can_be_fired;
static void (*const b1abbd0_odel)(int) = object_delete;

__attribute__((naked, noinline))
void unit_drop_weapons_on_death(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal 0x2a8(%%ebx), %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      ".Lunit_drop_weapons_on_death_1:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl (%%edx), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lunit_drop_weapons_on_death_4\n\t"
      "cmpw 0x2a2(%%ebx), %%ax\n\t"
      "je .Lunit_drop_weapons_on_death_4\n\t"
      "pushl $4\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testb $8, %%ch\n\t"
      "je .Lunit_drop_weapons_on_death_2\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl $1\n\t"
      "pushl $0x2132\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ba1f0]\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ba1f0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b6ee0\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_drop_weapons_on_death_2:\n\t"
      "call *%[c1ab990]\n\t"
      "movw -0x8(%%ebp), %%dx\n\t"
      "cmpw 0x2a4(%%ebx), %%dx\n\t"
      "jne .Lunit_drop_weapons_on_death_3\n\t"
      "movw 0x2a2(%%ebx), %%ax\n\t"
      "movw %%ax, 0x2a4(%%ebx)\n\t"
      ".Lunit_drop_weapons_on_death_3:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl $0xffffffff, (%%ecx)\n\t"
      "call *%[cfaf50]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunit_drop_weapons_on_death_4\n\t"
      "pushl %%esi\n\t"
      "call *%[odel]\n\t"
      "addl $4, %%esp\n\t"
      ".Lunit_drop_weapons_on_death_4:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "incl %%eax\n\t"
      "addl $4, %%edx\n\t"
      "cmpw $4, %%ax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jl .Lunit_drop_weapons_on_death_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1abbd0_get), [c1ba1f0] "m"(b1abbd0_c1ba1f0), [c8d9d0] "m"(b1abbd0_c8d9d0), [assert] "m"(b1abbd0_assert), [exitfn] "m"(b1abbd0_exitfn), [c1ab990] "m"(b1abbd0_c1ab990), [cfaf50] "m"(b1abbd0_cfaf50), [odel] "m"(b1abbd0_odel)
      : "memory");
}
#else
#error "unit_drop_weapons_on_death: clang naked draft required"
#endif


/* unit_get_weapon_name (0x1ae700) — readable C lift. */
extern char DAT_002b6e68[];
char *unit_get_weapon_name(int unit_handle /* @<esi> */)
{
  char *unit;
  int weapon_handle;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  weapon_handle = unit_get_weapon(unit_handle, *(int16_t *)(unit + 0x2a2));
  if (weapon_handle == -1)
    return DAT_002b6e68;
  return weapon_get_label(weapon_handle);
}

/* unit_has_night_vision_weapon (0x1b13a0) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b1b13a0_get)(int, int) = object_get_and_verify_type;
static int (*const b1b13a0_c1adeb0)(int unit_handle, int16_t weapon_index) = unit_get_weapon;
static void *(*const b1b13a0_tag)(int, int) = tag_get;

__attribute__((naked, noinline))
char unit_has_night_vision_weapon(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[get]\n\t"
      "movb 0x2d0(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "cmpb $0xff, %%cl\n\t"
      "je .Lunit_has_night_vision_weapon_1\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movswl 0x2a2(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1adeb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lunit_has_night_vision_weapon_1\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x77656170\n\t"
      "call *%[tag]\n\t"
      "movl 0x308(%%eax), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $0x40, %%ch\n\t"
      "movb $1, %%al\n\t"
      "jne .Lunit_has_night_vision_weapon_2\n\t"
      ".Lunit_has_night_vision_weapon_1:\n\t"
      "movb %%bl, %%al\n\t"
      ".Lunit_has_night_vision_weapon_2:\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1b13a0_get), [c1adeb0] "m"(b1b13a0_c1adeb0), [tag] "m"(b1b13a0_tag)
      : "memory");
}
#else
#error "unit_has_night_vision_weapon: clang naked draft required"
#endif


/* unit_solo_player_integrated_night_vision_is_active (0x1b2610)
 * Returns true if there is exactly one local player, that player has a
 * valid unit, and that unit's current weapon has the night-vision flag. */
char unit_solo_player_integrated_night_vision_is_active(void)
{
  int16_t count;
  int16_t local_idx;
  int player_index;
  char *player;
  int unit_handle;
  char result;

  result = 0;
  count = local_player_count();
  if (count != 1) {
    return result;
  }
  local_idx = local_player_get_next(-1);
  player_index = local_player_get_player_index(local_idx);
  if (player_index == -1) {
    return result;
  }
  player = (char *)datum_get(player_data, player_index);
  unit_handle = *(int *)(player + 0x34);
  if (unit_handle == -1) {
    return result;
  }
  return unit_has_night_vision_weapon(unit_handle);
}

/* scripting_magic_melee_attack (0x1b2260) — readable C lift. */
void scripting_magic_melee_attack(void)
{
  char *player;

  player = (char *)datum_get(*(void **)0x5aa6d4, 0);
  unit_melee_attack_begin(*(int *)(player + 0x34), 0, 0);
}

/* unit_select_weapon_after_vehicle_exit (0x1b2740) — XBE naked draft (batch 98). */
#if defined(__clang__)
static void *(*const b1b2740_get)(int, int) = object_get_and_verify_type;
static int16_t (*const b1b2740_c1ae490)(int unit_handle, int16_t current_index, int16_t direction) = FUN_001ae490;
static void (*const b1b2740_c1b1ee0)(int unit_handle, int flag) = unit_update_weapon_readiness;

__attribute__((naked, noinline))
void unit_select_weapon_after_vehicle_exit(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2a2(%%edi), %%ax\n\t"
      "pushl $0\n\t"
      "movl %%esi, %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ae490]\n\t"
      "pushl $1\n\t"
      "movw %%ax, 0x2a4(%%edi)\n\t"
      "call *%[c1b1ee0]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1b2740_get), [c1ae490] "m"(b1b2740_c1ae490), [c1b1ee0] "m"(b1b2740_c1b1ee0)
      : "memory");
}
#else
#error "unit_select_weapon_after_vehicle_exit: clang naked draft required"
#endif


/* FUN_001abd10 (0x1abd10) — XBE naked draft (batch 68). */
#if defined(__clang__)
static void * (*const b1abd10_c18e500)(int16_t material_type) = FUN_0018e500;
static int (*const b1abd10_c1c7e70)(int object_handle, int tag_index, int16_t marker, float *position, float *forward, float scale) = object_impulse_sound_new;
static void *(*const b1abd10_tag)(int, int) = tag_get;

__attribute__((naked, noinline))
void FUN_001abd10(int16_t material_type __attribute__((unused)), int unit_handle __attribute__((unused)), int weapon_tag_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%eax\n\t"
      "call *%[c18e500]\n\t"
      "movl 0x370(%%eax), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001abd10_1\n\t"
      "movl 0x31fc3c, %%ecx\n\t"
      "movl 0x31fc1c, %%edx\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c7e70]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_001abd10_1:\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_001abd10_2\n\t"
      "pushl %%edi\n\t"
      "pushl $0x6a707421\n\t"
      "call *%[tag]\n\t"
      "movl 0x120(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001abd10_2\n\t"
      "movl 0x31fc3c, %%ecx\n\t"
      "movl 0x31fc1c, %%edx\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1c7e70]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_001abd10_2:\n\t"
      "ret\n\t"
      :
      : [c18e500] "m"(b1abd10_c18e500), [c1c7e70] "m"(b1abd10_c1c7e70), [tag] "m"(b1abd10_tag)
      : "memory");
}
#else
#error "FUN_001abd10: clang naked draft required"
#endif


/* unit_flame_to_death (0x1ac550)
 * Handles the flame-to-death damage effect when a unit's flame-death
 * timer expires. Clears flame flags on the unit, looks up the flame damage
 * effect tag from game globals, and applies it. If the unit doesn't die,
 * logs a warning and sets a fallback flag.
 * cdecl: 1 stack param (unit_handle). */
void unit_flame_to_death(int unit_handle)
{
  char *unit;
  char *globals;
  char *element;
  char *object_data;
  char damage_params[0x54];
  char *parent_obj;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);

  globals = (char *)game_globals_get();
  element = (char *)tag_block_get_element(globals + 0x188, 0, 0x98);

  object_data = (char *)object_get_and_verify_type(unit_handle, 3);
  *(uint32_t *)(object_data + 0x1b4) &= ~0x02000000u;

  *(uint8_t *)(unit + 0xb7) &= ~0x08;
  *(uint32_t *)(unit + 0x1b4) &= ~0x80u;

  if (element != NULL && *(int *)(element + 0x78) != -1) {
    parent_obj = (char *)object_try_and_get_and_verify_type(
        *(int *)(unit + 0x3c0), -1);

    damage_data_new(damage_params, *(int *)(element + 0x78));

    if (parent_obj != NULL) {
      *(int *)(damage_params + 0x08) = *(int *)(parent_obj + 0x70);
      {
        int cause_player = *(int *)(parent_obj + 0x74);
        if (cause_player == -1) {
          cause_player = *(int *)(unit + 0x3c0);
        }
        *(int *)(damage_params + 0x0c) = cause_player;
      }
      *(int16_t *)(damage_params + 0x10) = *(int16_t *)(parent_obj + 0x68);
    }

    object_cause_damage(damage_params, unit_handle, -1, -1, -1, 0);
  }

  if ((*(uint8_t *)(unit + 0xb6) & 0x4) == 0) {
    const char *tag_name;
    const char *stripped;
    tag_name = tag_get_name(*(int *)unit);
    stripped = tag_name_strip_path(tag_name);
    error(2, "WARNING: %s tried to die from flaming to death but couldn't",
          stripped);
    *(uint8_t *)(unit + 0xb6) |= 0x20;
  }
}

/* FUN_001ab110 (0x1ab110) — XBE naked draft (batch 53). */
#if defined(__clang__)
static void *(*const b1ab110_get)(int, int) = object_get_and_verify_type;
static void *(*const b1ab110_tag)(int, int) = tag_get;
static void (*const b1ab110_c1411c0)(int object_handle) = object_detach_from_parent;
static vector3_t * (*const b1ab110_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static int (*const b1ab110_c22ba0)(int actor_handle, void *aim_params, float *out_aim_vector) = actor_aim_grenade;
static void * (*const b1ab110_c18e450)(void) = game_globals_get;
static void *(*const b1ab110_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1ab110_cross)(float *, float *, float *) = cross_product3d;
static float (*const b1ab110_norm)(float *) = normalize3d;
static void (*const b1ab110_useat)(int, float *) = unit_set_seat_state;
static void (*const b1ab110_otrans)(int, float *, void *) = object_translate;
static int *(*const b1ab110_gseed)(void) = get_global_random_seed_address;
static float (*const b1ab110_rrange)(int *, float, float) = random_real_range;
static void (*const b1ab110_cf8ee0)(int projectile_handle, float *acceleration) = projectile_accelerate;
static bool (*const b1ab110_oplace)(int, float *) = object_try_place;
static void (*const b1ab110_odel)(int) = object_delete;

__attribute__((naked, noinline))
void FUN_001ab110(int unit_handle __attribute__((unused)), char flag __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x40, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movb 0x23d(%%esi), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpb $2, %%al\n\t"
      "jne .LFUN_001ab110_7\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl 0x244(%%esi), %%edi\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "je .LFUN_001ab110_6\n\t"
      "pushl %%edi\n\t"
      "call *%[c1411c0]\n\t"
      "movl 0x1a4(%%esi), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .LFUN_001ab110_1\n\t"
      "movl 0x244(%%esi), %%eax\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1412f0]\n\t"
      "movl 0x1a4(%%esi), %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c22ba0]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_001ab110_4\n\t"
      ".LFUN_001ab110_1:\n\t"
      "cmpl %%ebx, 0x1c8(%%esi)\n\t"
      "je .LFUN_001ab110_3\n\t"
      "pushl $0xf4\n\t"
      "pushl $0\n\t"
      "call *%[c18e450]\n\t"
      "addl $0x170, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "leal 0x1ec(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "movl 0x31fc44, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[cross]\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x1c, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001ab110_2\n\t"
      "movl 0x31fc44, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      ".LFUN_001ab110_2:\n\t"
      "leal -0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[cross]\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[useat]\n\t"
      "flds 0x68(%%ebx)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "pushl $0\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x6c(%%ebx)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x70(%%ebx)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[otrans]\n\t"
      "addl $0x24, %%esp\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      ".LFUN_001ab110_3:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "flds 0x2c0(%%eax)\n\t"
      "fmuls 0x2546a4\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x1ec(%%esi)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x1f0(%%esi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fmuls 0x1f4(%%esi)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".LFUN_001ab110_4:\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001ab110_5\n\t"
      "movswl 0x23e(%%esi), %%ecx\n\t"
      "movswl 0x240(%%esi), %%edx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "fidivl -0x4(%%ebp)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001ab110_5\n\t"
      "pushl $0x3d3f258c\n\t"
      "pushl $0x3ca3d70b\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x1ec(%%esi)\n\t"
      "addl $0xc, %%esp\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x1f0(%%esi)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x1f4(%%esi)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".LFUN_001ab110_5:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fsubs 0x18(%%eax)\n\t"
      "addl $0x18, %%eax\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fsubs 0x8(%%eax)\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "call *%[cf8ee0]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "leal -0x40(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movb $3, 0x23d(%%esi)\n\t"
      "movl %%ebx, 0x244(%%esi)\n\t"
      "call *%[useat]\n\t"
      "leal -0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[oplace]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001ab110_6\n\t"
      "pushl %%edi\n\t"
      "call *%[odel]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001ab110_6:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001ab110_7:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [get] "m"(b1ab110_get), [tag] "m"(b1ab110_tag), [c1411c0] "m"(b1ab110_c1411c0), [c1412f0] "m"(b1ab110_c1412f0), [c22ba0] "m"(b1ab110_c22ba0), [c18e450] "m"(b1ab110_c18e450), [elem] "m"(b1ab110_elem), [cross] "m"(b1ab110_cross), [norm] "m"(b1ab110_norm), [useat] "m"(b1ab110_useat), [otrans] "m"(b1ab110_otrans), [gseed] "m"(b1ab110_gseed), [rrange] "m"(b1ab110_rrange), [cf8ee0] "m"(b1ab110_cf8ee0), [oplace] "m"(b1ab110_oplace), [odel] "m"(b1ab110_odel)
      : "memory");
}
#else
#error "FUN_001ab110: clang naked draft required"
#endif


/* FUN_001a6280 (0x1a6280) — XBE naked draft (batch 64). */
#if defined(__clang__)
static void *(*const b1a6280_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a6280_tag)(int, int) = tag_get;
static char (*const b1a6280_c1a0680)(int unit_handle) = FUN_001a0680;
static void (*const b1a6280_c1a2800)(int unit_handle, const char *failure_kind) = FUN_001a2800;
static void (*const b1a6280_c1a2160)(int unit_handle) = FUN_001a2160;
static void (*const b1a6280_c1a4440)(int unit_handle) = FUN_001a4440;

__attribute__((naked, noinline))
void FUN_001a6280(int unit_handle __attribute__((unused)), char *state_out __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movb 0x424(%%esi), %%cl\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $0x20, %%cl\n\t"
      "je .LFUN_001a6280_2\n\t"
      "movb 0x47c(%%esi), %%cl\n\t"
      "cmpb 0x47d(%%esi), %%cl\n\t"
      "jae .LFUN_001a6280_2\n\t"
      "movb 0x4e4cf3, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a6280_1\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a0680]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001a6280_1:\n\t"
      "pushl $0x2b51ec\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1a2800]\n\t"
      "addl $4, %%esp\n\t"
      "movb $0, 0x1(%%ebx)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LFUN_001a6280_2:\n\t"
      "cmpb $3, 0x459(%%esi)\n\t"
      "jl .LFUN_001a6280_4\n\t"
      "movl 0x2f4(%%eax), %%ecx\n\t"
      "testb $4, %%ch\n\t"
      "jne .LFUN_001a6280_4\n\t"
      "cmpb $0x18, 0x253(%%esi)\n\t"
      "jne .LFUN_001a6280_3\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1a2160]\n\t"
      ".LFUN_001a6280_3:\n\t"
      "pushl $0x2b51d8\n\t"
      "movl %%edi, %%eax\n\t"
      "movb $0x18, (%%ebx)\n\t"
      "call *%[c1a2800]\n\t"
      "addl $4, %%esp\n\t"
      "movb $0, 0x1(%%ebx)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LFUN_001a6280_4:\n\t"
      "cmpb $0x18, 0x253(%%esi)\n\t"
      "jne .LFUN_001a6280_5\n\t"
      "pushl %%edi\n\t"
      "movl $0, 0x468(%%esi)\n\t"
      "call *%[c1a4440]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001a6280_5:\n\t"
      "pushl $0x2b51cc\n\t"
      "movl %%edi, %%eax\n\t"
      "movb $0x19, (%%ebx)\n\t"
      "call *%[c1a2800]\n\t"
      "addl $4, %%esp\n\t"
      "movb $0, 0x1(%%ebx)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a6280_get), [tag] "m"(b1a6280_tag), [c1a0680] "m"(b1a6280_c1a0680), [c1a2800] "m"(b1a6280_c1a2800), [c1a2160] "m"(b1a6280_c1a2160), [c1a4440] "m"(b1a6280_c1a4440)
      : "memory");
}
#else
#error "FUN_001a6280: clang naked draft required"
#endif


/* FUN_001a68d0 (0x1a68d0) — XBE naked draft (batch 52). */
#if defined(__clang__)
static void *(*const b1a68d0_get)(int, int) = object_get_and_verify_type;
static int (*const b1a68d0_gtime)(void) = game_time_get;
static void (*const b1a68d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1a68d0_exitfn)(int) = system_exit;
static void *(*const b1a68d0_tag)(int, int) = tag_get;
static short (*const b1a68d0_cfff80)(void) = game_connection;
static void (*const b1a68d0_ftol)(void) = FUN_001d9068;
static void *(*const b1a68d0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1a68d0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
short FUN_001a68d0(int unit_handle __attribute__((unused)), short priority __attribute__((unused)), char param_3 __attribute__((unused)), char param_4 __attribute__((unused)), int *param_5 __attribute__((unused)), short *vocalization_type_ref __attribute__((unused)), int *sound_definition_index_ref __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[gtime]\n\t"
      "movl 0x1c(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jne .LFUN_001a68d0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x80\n\t"
      "pushl $0x2b66ec\n\t"
      "pushl $0x2b66d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a68d0_1:\n\t"
      "movl 0x20(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_001a68d0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x81\n\t"
      "pushl $0x2b66ec\n\t"
      "pushl $0x2b66ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a68d0_2:\n\t"
      "movw 0xc(%%ebp), %%si\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_001a68d0_3\n\t"
      "cmpw $0xb, %%si\n\t"
      "jl .LFUN_001a68d0_4\n\t"
      ".LFUN_001a68d0_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x82\n\t"
      "pushl $0x2b66ec\n\t"
      "pushl $0x2b6668\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a68d0_4:\n\t"
      "movswl (%%ebx), %%ebx\n\t"
      "movl (%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jne .LFUN_001a68d0_10\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x334(%%ecx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001a68d0_10\n\t"
      "cmpw $-1, %%bx\n\t"
      "je .LFUN_001a68d0_10\n\t"
      "pushl %%eax\n\t"
      "pushl $0x75646c67\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      ".LFUN_001a68d0_5:\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .LFUN_001a68d0_6\n\t"
      "cmpw $0xd1, %%bx\n\t"
      "jl .LFUN_001a68d0_7\n\t"
      ".LFUN_001a68d0_6:\n\t"
      "pushl $1\n\t"
      "pushl $0x90\n\t"
      "pushl $0x2b66ec\n\t"
      "pushl $0x2b6618\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001a68d0_7:\n\t"
      "movswl %%bx, %%esi\n\t"
      "movl %%esi, %%edx\n\t"
      "shll $4, %%edx\n\t"
      "movl 0x1c(%%edx,%%edi,1), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a68d0_9\n\t"
      "cmpl $-1, -0x10(%%ebp)\n\t"
      "jne .LFUN_001a68d0_9\n\t"
      "call *%[cfff80]\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_001a68d0_8\n\t"
      "movb 0x5ac9cd, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a68d0_9\n\t"
      ".LFUN_001a68d0_8:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movw 0x2b6420(,%%esi,2), %%bx\n\t"
      "cmpw $-1, %%bx\n\t"
      "jne .LFUN_001a68d0_5\n\t"
      ".LFUN_001a68d0_9:\n\t"
      "movw 0xc(%%ebp), %%si\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      ".LFUN_001a68d0_10:\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "testb $4, 0xb6(%%edi)\n\t"
      "je .LFUN_001a68d0_11\n\t"
      "cmpw $0xa, %%si\n\t"
      "jne .LFUN_001a68d0_25\n\t"
      ".LFUN_001a68d0_11:\n\t"
      "call *%[cfff80]\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_001a68d0_12\n\t"
      "movb 0x5ac9cd, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a68d0_13\n\t"
      ".LFUN_001a68d0_12:\n\t"
      "cmpl $-1, -0x10(%%ebp)\n\t"
      "je .LFUN_001a68d0_25\n\t"
      ".LFUN_001a68d0_13:\n\t"
      "movw 0x338(%%edi), %%si\n\t"
      "testw %%si, %%si\n\t"
      "jne .LFUN_001a68d0_14\n\t"
      "movl $2, -0xc(%%ebp)\n\t"
      "jmp .LFUN_001a68d0_25\n\t"
      ".LFUN_001a68d0_14:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movw 0x368(%%ecx), %%dx\n\t"
      "cmpw %%dx, %%si\n\t"
      "movl %%esi, %%edi\n\t"
      "jg .LFUN_001a68d0_15\n\t"
      "movl %%edx, %%edi\n\t"
      ".LFUN_001a68d0_15:\n\t"
      "movswl 0xc(%%ebp), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "subl $2, %%eax\n\t"
      "je .LFUN_001a68d0_16\n\t"
      "subl $5, %%eax\n\t"
      "je .LFUN_001a68d0_16\n\t"
      "subl $3, %%eax\n\t"
      "jne .LFUN_001a68d0_17\n\t"
      ".LFUN_001a68d0_16:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "cmpb $0, 0x3a4(%%eax)\n\t"
      "je .LFUN_001a68d0_17\n\t"
      "cmpw $0, 0x3aa(%%eax)\n\t"
      "jne .LFUN_001a68d0_17\n\t"
      "cmpw %%di, 0xc(%%ebp)\n\t"
      "jle .LFUN_001a68d0_17\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%edx, %%edi\n\t"
      ".LFUN_001a68d0_17:\n\t"
      "movw 0x2b65c4(,%%ecx,2), %%ax\n\t"
      "cmpw %%di, %%ax\n\t"
      "jl .LFUN_001a68d0_18\n\t"
      "movl $3, -0xc(%%ebp)\n\t"
      "jmp .LFUN_001a68d0_25\n\t"
      ".LFUN_001a68d0_18:\n\t"
      "movw 0xc(%%ebp), %%dx\n\t"
      "cmpw $7, %%dx\n\t"
      "jl .LFUN_001a68d0_19\n\t"
      "cmpw %%si, %%ax\n\t"
      "jl .LFUN_001a68d0_19\n\t"
      "movl $2, -0xc(%%ebp)\n\t"
      "jmp .LFUN_001a68d0_25\n\t"
      ".LFUN_001a68d0_19:\n\t"
      "movb 0x14(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a68d0_25\n\t"
      "flds 0x2b65dc(,%%ecx,4)\n\t"
      "fsts -0x14(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_001a68d0_25\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fcomps 0x2548fc\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001a68d0_20\n\t"
      "movb $1, %%cl\n\t"
      "jmp .LFUN_001a68d0_21\n\t"
      ".LFUN_001a68d0_20:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "flds -0x14(%%ebp)\n\t"
      "movswl 0x3ae(%%eax), %%ebx\n\t"
      "fmuls 0x253394\n\t"
      "movswl 0x3aa(%%eax), %%edx\n\t"
      "addl %%edx, %%ebx\n\t"
      "call *%[ftol]\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "setl %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_001a68d0_25\n\t"
      "movw 0xc(%%ebp), %%dx\n\t"
      ".LFUN_001a68d0_21:\n\t"
      "cmpw %%di, %%dx\n\t"
      "jg .LFUN_001a68d0_24\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "cmpw 0x368(%%eax), %%dx\n\t"
      "jle .LFUN_001a68d0_25\n\t"
      "movswl %%si, %%eax\n\t"
      "subl $2, %%eax\n\t"
      "je .LFUN_001a68d0_22\n\t"
      "subl $5, %%eax\n\t"
      "jne .LFUN_001a68d0_23\n\t"
      ".LFUN_001a68d0_22:\n\t"
      "movb $1, %%cl\n\t"
      ".LFUN_001a68d0_23:\n\t"
      "cmpw $6, %%dx\n\t"
      "je .LFUN_001a68d0_24\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_001a68d0_25\n\t"
      ".LFUN_001a68d0_24:\n\t"
      "movl $1, -0xc(%%ebp)\n\t"
      ".LFUN_001a68d0_25:\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movw %%bx, (%%ecx)\n\t"
      "popl %%edi\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_001a68d0_26\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x3a0(%%ecx), %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      ".LFUN_001a68d0_26:\n\t"
      "movw -0xc(%%ebp), %%ax\n\t"
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
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%cx, 0x338(%%eax)\n\t"
      "setg %%cl\n\t"
      "movb %%cl, %%al\n\t"
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
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $0, 0x6e(%%esi)\n\t"
      "jne .LFUN_001a68d0_32\n\t"
      "pushl %%ebx\n\t"
      "leal 0x2b4(%%eax), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_001a68d0_31\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001a68d0_27:\n\t"
      "pushl $0x18\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "movw (%%eax), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0x64, %%ax\n\t"
      "jge .LFUN_001a68d0_28\n\t"
      "cmpw $0x10, %%di\n\t"
      "jae .LFUN_001a68d0_29\n\t"
      "movswl %%di, %%edx\n\t"
      "movw %%ax, -0x24(%%ebp,%%edx,2)\n\t"
      "incl %%edi\n\t"
      ".LFUN_001a68d0_28:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_001a68d0_27\n\t"
      "jmp .LFUN_001a68d0_30\n\t"
      ".LFUN_001a68d0_29:\n\t"
      "pushl $0x2b6714\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001a68d0_30:\n\t"
      "testw %%di, %%di\n\t"
      "jle .LFUN_001a68d0_31\n\t"
      "movl 0x4e4cf4, %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "movswl %%di, %%esi\n\t"
      "cdq\n\t"
      "idivl %%esi\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, 0x4e4cf4\n\t"
      "movw -0x24(%%ebp,%%edx,2), %%ax\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movw %%ax, 0x6e(%%edx)\n\t"
      ".LFUN_001a68d0_31:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001a68d0_32:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1a68d0_get), [gtime] "m"(b1a68d0_gtime), [assert] "m"(b1a68d0_assert), [exitfn] "m"(b1a68d0_exitfn), [tag] "m"(b1a68d0_tag), [cfff80] "m"(b1a68d0_cfff80), [ftol] "m"(b1a68d0_ftol), [elem] "m"(b1a68d0_elem), [c8f390] "m"(b1a68d0_c8f390)
      : "memory");
}
#else
#error "FUN_001a68d0: clang naked draft required"
#endif


/* FUN_001ac680 (0x1ac680) — XBE naked draft (batch 50). */
#if defined(__clang__)
static void (*const b1ac680_c1ac680)(float initial_p, float initial_v, float max_v, float max_a, int plan) = FUN_001ac680;
static void (*const b1ac680_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1ac680_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_001ac680(float initial_p __attribute__((unused)), float initial_v __attribute__((unused)), float max_v __attribute__((unused)), float max_a __attribute__((unused)), int plan __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "flds 0x8(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl $0x7f7fffff, %%eax\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "pushl %%esi\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "movl %%eax, 0x10(%%esi)\n\t"
      "movl %%eax, 0x14(%%esi)\n\t"
      "movl %%eax, 0x18(%%esi)\n\t"
      "movl %%eax, 0x1c(%%esi)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "pushl %%edi\n\t"
      "testb $5, %%ah\n\t"
      "movl %%ecx, 0x8(%%esi)\n\t"
      "jp .LFUN_001ac680_1\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001ac680_1\n\t"
      "movl $1, %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "jmp .LFUN_001ac680_2\n\t"
      ".LFUN_001ac680_1:\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001ac680_2:\n\t"
      "testb %%al, %%al\n\t"
      "movb %%al, (%%esi)\n\t"
      "je .LFUN_001ac680_3\n\t"
      "movl %%edi, 0xc(%%esi)\n\t"
      "movl %%edi, 0x10(%%esi)\n\t"
      "movl %%edi, 0x14(%%esi)\n\t"
      "movl %%edi, 0x18(%%esi)\n\t"
      "movl %%edi, 0x1c(%%esi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001ac680_3:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "fabs\n\t"
      "fdivs 0x14(%%ebp)\n\t"
      "fstps 0x18(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001ac680_4\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_001ac680_5\n\t"
      ".LFUN_001ac680_4:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_001ac680_5:\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fadds 0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001ac680_6\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "fchs\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "subl $8, %%esp\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fchs\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c1ac680]\n\t"
      "flds 0x4(%%esi)\n\t"
      "addl $0x14, %%esp\n\t"
      "fmuls 0x255e94\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fmuls 0x255e94\n\t"
      "fstps 0x8(%%esi)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fmuls 0x255e94\n\t"
      "fstps 0xc(%%esi)\n\t"
      "flds 0x18(%%esi)\n\t"
      "fmuls 0x255e94\n\t"
      "fstps 0x18(%%esi)\n\t"
      "jmp .LFUN_001ac680_10\n\t"
      ".LFUN_001ac680_6:\n\t"
      "fmuls 0x253398\n\t"
      "fmuls 0x18(%%ebp)\n\t"
      "fadds 0x8(%%ebp)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001ac680_16\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x2b706c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001ac680_7\n\t"
      "pushl $1\n\t"
      "pushl $0x7b7\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b7050\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ac680_7:\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001ac680_8\n\t"
      "pushl $1\n\t"
      "pushl $0x7b8\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b703c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ac680_8:\n\t"
      "flds 0x8(%%esi)\n\t"
      "movl %%edi, 0xc(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "movl %%edi, 0x10(%%esi)\n\t"
      "fmulp %%st(1)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fsts 0x18(%%esi)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fchs\n\t"
      "fstps 0x1c(%%esi)\n\t"
      ".LFUN_001ac680_9:\n\t"
      "fstp %%st(0)\n\t"
      "movl %%edi, 0x14(%%esi)\n\t"
      ".LFUN_001ac680_10:\n\t"
      "cmpl $0x7f7fffff, 0xc(%%esi)\n\t"
      "popl %%ebx\n\t"
      "jne .LFUN_001ac680_11\n\t"
      "pushl $1\n\t"
      "pushl $0x85c\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b7020\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ac680_11:\n\t"
      "cmpl $0x7f7fffff, 0x10(%%esi)\n\t"
      "jne .LFUN_001ac680_12\n\t"
      "pushl $1\n\t"
      "pushl $0x85d\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b7004\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ac680_12:\n\t"
      "cmpl $0x7f7fffff, 0x14(%%esi)\n\t"
      "jne .LFUN_001ac680_13\n\t"
      "pushl $1\n\t"
      "pushl $0x85e\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b6fe8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ac680_13:\n\t"
      "cmpl $0x7f7fffff, 0x18(%%esi)\n\t"
      "jne .LFUN_001ac680_14\n\t"
      "pushl $1\n\t"
      "pushl $0x85f\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b6fcc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ac680_14:\n\t"
      "cmpl $0x7f7fffff, 0x1c(%%esi)\n\t"
      "jne .LFUN_001ac680_15\n\t"
      "pushl $1\n\t"
      "pushl $0x860\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b6fb0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ac680_15:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001ac680_16:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_001ac680_17\n\t"
      "fdivs 0x14(%%ebp)\n\t"
      "fsqrt\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "jmp .LFUN_001ac680_22\n\t"
      ".LFUN_001ac680_17:\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "fsts 0xc(%%ebp)\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fmuls 0x2533d8\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_001ac680_18\n\t"
      "pushl $1\n\t"
      "pushl $0x7eb\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b6fa4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ac680_18:\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fsqrt\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fchs\n\t"
      "fsub %%st(2), %%st(0)\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fsubs 0xc(%%ebp)\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001ac680_20\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001ac680_19\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001ac680_20\n\t"
      ".LFUN_001ac680_19:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "jmp .LFUN_001ac680_22\n\t"
      ".LFUN_001ac680_20:\n\t"
      "flds 0x2533c0\n\t"
      "fcomps 0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001ac680_21\n\t"
      "movl $0, 0xc(%%ebp)\n\t"
      "jmp .LFUN_001ac680_23\n\t"
      ".LFUN_001ac680_21:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      ".LFUN_001ac680_22:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_001ac680_23\n\t"
      "pushl $1\n\t"
      "pushl $0x7fa\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b6f9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ac680_23:\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001ac680_27\n\t"
      "testb %%bl, %%bl\n\t"
      "flds 0x10(%%ebp)\n\t"
      "jne .LFUN_001ac680_24\n\t"
      "fadds 0x8(%%esi)\n\t"
      ".LFUN_001ac680_24:\n\t"
      "fdivs 0x14(%%ebp)\n\t"
      "flds 0x2533c0\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001ac680_25\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      ".LFUN_001ac680_25:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001ac680_26\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "jmp .LFUN_001ac680_28\n\t"
      ".LFUN_001ac680_26:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "jmp .LFUN_001ac680_28\n\t"
      ".LFUN_001ac680_27:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      ".LFUN_001ac680_28:\n\t"
      "testb %%bl, %%bl\n\t"
      "flds 0x14(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "fchs\n\t"
      "fsts 0xc(%%esi)\n\t"
      "movl %%edx, 0x18(%%esi)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fadds 0x18(%%ebp)\n\t"
      "je .LFUN_001ac680_29\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "fstps 0x10(%%esi)\n\t"
      "movl %%eax, 0x1c(%%esi)\n\t"
      "jmp .LFUN_001ac680_30\n\t"
      ".LFUN_001ac680_29:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "fstps 0x1c(%%esi)\n\t"
      "movl %%ecx, 0x10(%%esi)\n\t"
      ".LFUN_001ac680_30:\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001ac680_9\n\t"
      "fmuls 0x10(%%esi)\n\t"
      "fadds 0x8(%%esi)\n\t"
      "fstps 0x18(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fsubs 0x8(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x18(%%ebp)\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "fld %%st(1)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fmuls 0x14(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001ac680_31\n\t"
      "pushl $1\n\t"
      "pushl $0x850\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b6f88\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ac680_31:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fdivs 0x18(%%ebp)\n\t"
      "fsts 0x14(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_001ac680_32\n\t"
      "pushl $1\n\t"
      "pushl $0x852\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b6f74\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ac680_32:\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fadds 0x14(%%esi)\n\t"
      "fcomps 0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_001ac680_10\n\t"
      "pushl $1\n\t"
      "pushl $0x853\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b6f54\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_001ac680_10\n\t"
      "nop\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpb $0, (%%ecx)\n\t"
      "jne .LFUN_001ac680_43\n\t"
      "cmpb $0, (%%esi)\n\t"
      "jne .LFUN_001ac680_43\n\t"
      "flds 0x1c(%%ecx)\n\t"
      "fadds 0x14(%%ecx)\n\t"
      "fadds 0x10(%%ecx)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fadds 0x14(%%esi)\n\t"
      "fadds 0x10(%%esi)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x10(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001ac680_33\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001ac680_33\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl %%ecx, %%esi\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "jmp .LFUN_001ac680_34\n\t"
      ".LFUN_001ac680_33:\n\t"
      "flds 0x10(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001ac680_43\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001ac680_43\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fsubs -0x8(%%ebp)\n\t"
      ".LFUN_001ac680_34:\n\t"
      "testl %%esi, %%esi\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "je .LFUN_001ac680_43\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001ac680_35\n\t"
      "pushl $1\n\t"
      "pushl $0x8ae\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b70ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ac680_35:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fadds 0x14(%%esi)\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "flds 0x10(%%esi)\n\t"
      "fmuls 0xc(%%esi)\n\t"
      "fadds 0x8(%%esi)\n\t"
      "fabs\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fchs\n\t"
      "fmulp %%st(1)\n\t"
      "fxch %%st(1)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fmuls 0x2533d8\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_001ac680_36\n\t"
      "pushl $1\n\t"
      "pushl $0x8c4\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b6fa4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ac680_36:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fsqrt\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "flds 0x10(%%esi)\n\t"
      "fcomps 0x1c(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001ac680_37\n\t"
      "flds 0x1c(%%esi)\n\t"
      "jmp .LFUN_001ac680_38\n\t"
      ".LFUN_001ac680_37:\n\t"
      "flds 0x10(%%esi)\n\t"
      ".LFUN_001ac680_38:\n\t"
      "fld %%st(1)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001ac680_40\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x10(%%esi)\n\t"
      "fcomps 0x1c(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001ac680_39\n\t"
      "flds 0x1c(%%esi)\n\t"
      "jmp .LFUN_001ac680_40\n\t"
      ".LFUN_001ac680_39:\n\t"
      "flds 0x10(%%esi)\n\t"
      ".LFUN_001ac680_40:\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001ac680_42\n\t"
      "flds 0x10(%%esi)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fmuls 0xc(%%esi)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%eax, 0x10(%%esi)\n\t"
      "fadds 0x8(%%esi)\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fsub %%st(2), %%st(0)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fstps 0x1c(%%esi)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0xc(%%esi)\n\t"
      "fld %%st(1)\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fstps 0x14(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001ac680_41\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_001ac680_43\n\t"
      ".LFUN_001ac680_41:\n\t"
      "pushl $1\n\t"
      "pushl $0x8d8\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b7070\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001ac680_42:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_001ac680_43:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1ac680] "m"(b1ac680_c1ac680), [assert] "m"(b1ac680_assert), [exitfn] "m"(b1ac680_exitfn)
      : "memory");
}
#else
#error "FUN_001ac680: clang naked draft required"
#endif



/* unit_adjust_projectile_ray (0x1acf90) — XBE naked draft (batch 57). */
#if defined(__clang__)
static void *(*const b1acf90_get)(int, int) = object_get_and_verify_type;
static void (*const b1acf90_useat)(int, float *) = unit_set_seat_state;
static void (*const b1acf90_c140070)(int object_handle, float *position_out, float *direction_out) = object_get_root_location;

__attribute__((naked, noinline))
void unit_adjust_projectile_ray(int unit_handle __attribute__((unused)), float *origin __attribute__((unused)), float *direction __attribute__((unused)), float *velocity_out __attribute__((unused)), char adjust_origin __attribute__((unused)), char use_unit_forward __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movb 0x1c(%%ebp), %%cl\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lunit_adjust_projectile_ray_1\n\t"
      "addl $0x1ec, %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      ".Lunit_adjust_projectile_ray_1:\n\t"
      "movb 0x18(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_adjust_projectile_ray_2\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[useat]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "flds (%%eax)\n\t"
      "addl $8, %%esp\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs -0x8(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "fxch %%st(2)\n\t"
      "fmuls (%%esi)\n\t"
      "fld %%st(2)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fxch %%st(1)\n\t"
      "fstp %%st(0)\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%esi)\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps (%%eax)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fstps 0x8(%%eax)\n\t"
      ".Lunit_adjust_projectile_ray_2:\n\t"
      "pushl $0\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c140070]\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "flds -0x4(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "popl %%edi\n\t"
      "faddp %%st(1)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "popl %%esi\n\t"
      "faddp %%st(1)\n\t"
      "fstps (%%eax)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1acf90_get), [useat] "m"(b1acf90_useat), [c140070] "m"(b1acf90_c140070)
      : "memory");
}
#else
#error "unit_adjust_projectile_ray: clang naked draft required"
#endif


/* unit_render_debug (0x1ad060) — XBE naked draft (batch 55). */
#if defined(__clang__)
static void *(*const b1ad060_get)(int, int) = object_get_and_verify_type;
static void *(*const b1ad060_tag)(int, int) = tag_get;
static void (*const b1ad060_useat)(int, float *) = unit_set_seat_state;
static vector3_t * (*const b1ad060_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static void (*const b1ad060_c189320)(int flag, float *point, float *vector, float scale, void *color) = FUN_00189320;
static int (*const b1ad060_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void *(*const b1ad060_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const b1ad060_c1a8200)(int unit_handle, int target_unit_handle, int16_t seat_index, float *out_pos_a, float *out_pos_b, float *out_pos_c) = unit_get_seat_enter_position;
static void (*const b1ad060_c189150)(char flag, float *position, float scale, void *color) = FUN_00189150;
static short (*const b1ad060_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static char * (*const b1ad060_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b1ad060_c189cb0)(char flag, void *position, void *string, int color) = FUN_00189cb0;

__attribute__((naked, noinline))
void unit_render_debug(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x98, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movb 0x5054f7, %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_render_debug_1\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[useat]\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1412f0]\n\t"
      "flds -0x4(%%ebp)\n\t"
      "movl 0x2ee6c4, %%eax\n\t"
      "fadds 0x25496c\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3f800000\n\t"
      "leal 0x1ec(%%esi), %%ecx\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189320]\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3f000000\n\t"
      "leal 0x1e0(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189320]\n\t"
      "movl 0x2ee6c4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3f800000\n\t"
      "leal 0x24(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189320]\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "addl $0x4c, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3f000000\n\t"
      "leal 0x1d4(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189320]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_render_debug_1:\n\t"
      "movb 0x5054f6, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_render_debug_6\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x506548, %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[cba3c0]\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "je .Lunit_render_debug_6\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl 0x2e4(%%edx), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .Lunit_render_debug_5\n\t"
      "jmp .Lunit_render_debug_3\n\t"
      ".Lunit_render_debug_2:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lunit_render_debug_3:\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a8200]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_render_debug_4\n\t"
      "movl 0x2ee6d0, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x3e800000\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "movl 0x2ee6d8, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3e800000\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "movl 0x2ee6e0, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3e800000\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "addl $0x30, %%esp\n\t"
      ".Lunit_render_debug_4:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl 0x2e4(%%eax), %%ecx\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jl .Lunit_render_debug_2\n\t"
      ".Lunit_render_debug_5:\n\t"
      "popl %%ebx\n\t"
      ".Lunit_render_debug_6:\n\t"
      "movb 0x5054f5, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_render_debug_7\n\t"
      "pushl $1\n\t"
      "leal -0x98(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2909e4\n\t"
      "pushl %%edi\n\t"
      "call *%[markers]\n\t"
      "flds 0x298(%%esi)\n\t"
      "movl -0x38(%%ebp), %%edx\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl 0x2ee6f0, %%edx\n\t"
      "pushl %%edx\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25aec8\n\t"
      "pushl $0x5ab100\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c189cb0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lunit_render_debug_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1ad060_get), [tag] "m"(b1ad060_tag), [useat] "m"(b1ad060_useat), [c1412f0] "m"(b1ad060_c1412f0), [c189320] "m"(b1ad060_c189320), [cba3c0] "m"(b1ad060_cba3c0), [dget] "m"(b1ad060_dget), [c1a8200] "m"(b1ad060_c1a8200), [c189150] "m"(b1ad060_c189150), [markers] "m"(b1ad060_markers), [c8d9d0] "m"(b1ad060_c8d9d0), [c189cb0] "m"(b1ad060_c189cb0)
      : "memory");
}
#else
#error "unit_render_debug: clang naked draft required"
#endif


/* vehicle_scripting_find_available_seats (0x1adfc0) — XBE naked draft (batch 58). */
#if defined(__clang__)
static void *(*const b1adfc0_get)(int, int) = object_get_and_verify_type;
static void *(*const b1adfc0_tag)(int, int) = tag_get;
static void (*const b1adfc0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1adfc0_exitfn)(int) = system_exit;
static int (*const b1adfc0_c8df60)(const char *s1) = csstrlen;
static void *(*const b1adfc0_elem)(void *, int, int) = tag_block_get_element;
static char * (*const b1adfc0_c8dff0)(char *destination, const char *source) = csstrcpy;
static char * (*const b1adfc0_c8d9a0)(char *s) = csstr_tolower;
static char * (*const b1adfc0_c1d9690)(const char *haystack, const char *needle) = crt_strstr;
static char (*const b1adfc0_c1aa700)(int unit_handle, int16_t seat_index) = unit_seat_filled;

__attribute__((naked, noinline))
int16_t vehicle_scripting_find_available_seats(int unit_handle __attribute__((unused)), int seat_substring __attribute__((unused)), int16_t seat_desire_type __attribute__((unused)), int16_t *seat_indices __attribute__((unused)), int16_t max_seats __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x108, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "jne .Lvehicle_scripting_find_available_seats_1\n\t"
      "pushl $1\n\t"
      "pushl $0x178f\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b71b4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lvehicle_scripting_find_available_seats_1:\n\t"
      "movw 0x10(%%ebp), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lvehicle_scripting_find_available_seats_3\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lvehicle_scripting_find_available_seats_2\n\t"
      "cmpw $5, %%ax\n\t"
      "jl .Lvehicle_scripting_find_available_seats_3\n\t"
      ".Lvehicle_scripting_find_available_seats_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x1790\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b7140\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lvehicle_scripting_find_available_seats_3:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lvehicle_scripting_find_available_seats_4\n\t"
      "pushl %%edi\n\t"
      "call *%[c8df60]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jne .Lvehicle_scripting_find_available_seats_5\n\t"
      ".Lvehicle_scripting_find_available_seats_4:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".Lvehicle_scripting_find_available_seats_5:\n\t"
      "movl 0x2e4(%%esi), %%eax\n\t"
      "leal 0x2e4(%%esi), %%ebx\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "jle .Lvehicle_scripting_find_available_seats_15\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lvehicle_scripting_find_available_seats_6:\n\t"
      "pushl $0x11c\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw 0x18(%%ebp), %%di\n\t"
      "movl %%eax, %%esi\n\t"
      "jge .Lvehicle_scripting_find_available_seats_15\n\t"
      "leal 0x4(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x108(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dff0]\n\t"
      "leal -0x108(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8d9a0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lvehicle_scripting_find_available_seats_7\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x108(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9690]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lvehicle_scripting_find_available_seats_14\n\t"
      ".Lvehicle_scripting_find_available_seats_7:\n\t"
      "movswl 0x10(%%ebp), %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .Lvehicle_scripting_find_available_seats_13\n\t"
      "jmp *.Lvehicle_scripting_find_available_seats_jt(,%%eax,4)\n\t"
      ".Lvehicle_scripting_find_available_seats_8:\n\t"
      "movl (%%esi), %%eax\n\t"
      "shrl $2, %%eax\n\t"
      "notb %%al\n\t"
      "jmp .Lvehicle_scripting_find_available_seats_12\n\t"
      ".Lvehicle_scripting_find_available_seats_9:\n\t"
      "movl (%%esi), %%eax\n\t"
      "shrl $3, %%eax\n\t"
      "jmp .Lvehicle_scripting_find_available_seats_12\n\t"
      ".Lvehicle_scripting_find_available_seats_10:\n\t"
      "movl (%%esi), %%eax\n\t"
      "testb $4, %%al\n\t"
      "jne .Lvehicle_scripting_find_available_seats_14\n\t"
      "testb $8, %%al\n\t"
      "je .Lvehicle_scripting_find_available_seats_13\n\t"
      "jmp .Lvehicle_scripting_find_available_seats_14\n\t"
      ".Lvehicle_scripting_find_available_seats_11:\n\t"
      "movl (%%esi), %%eax\n\t"
      "shrl $2, %%eax\n\t"
      ".Lvehicle_scripting_find_available_seats_12:\n\t"
      "andb $1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lvehicle_scripting_find_available_seats_14\n\t"
      ".Lvehicle_scripting_find_available_seats_13:\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1aa700]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lvehicle_scripting_find_available_seats_14\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movswl %%di, %%edx\n\t"
      "movw %%si, (%%eax,%%edx,2)\n\t"
      "incl %%edi\n\t"
      ".Lvehicle_scripting_find_available_seats_14:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lvehicle_scripting_find_available_seats_6\n\t"
      ".Lvehicle_scripting_find_available_seats_15:\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lvehicle_scripting_find_available_seats_jt:\n\t"
      ".long .Lvehicle_scripting_find_available_seats_8\n\t"
      ".long .Lvehicle_scripting_find_available_seats_9\n\t"
      ".long .Lvehicle_scripting_find_available_seats_10\n\t"
      ".long .Lvehicle_scripting_find_available_seats_11\n\t"
      ".text\n\t"
      :
      : [get] "m"(b1adfc0_get), [tag] "m"(b1adfc0_tag), [assert] "m"(b1adfc0_assert), [exitfn] "m"(b1adfc0_exitfn), [c8df60] "m"(b1adfc0_c8df60), [elem] "m"(b1adfc0_elem), [c8dff0] "m"(b1adfc0_c8dff0), [c8d9a0] "m"(b1adfc0_c8d9a0), [c1d9690] "m"(b1adfc0_c1d9690), [c1aa700] "m"(b1adfc0_c1aa700)
      : "memory");
}
#else
#error "vehicle_scripting_find_available_seats: clang naked draft required"
#endif


/* unit_leap_begin (0x1b1c70) — XBE naked draft (batch 67). */
#if defined(__clang__)
static void *(*const b1b1c70_get)(int, int) = object_get_and_verify_type;
static char (*const b1b1c70_c1ad260)(int unit_handle, int16_t anim_state) = FUN_001ad260;
static void (*const b1b1c70_c1af180)(int unit_handle, float *alignment_vector) = unit_apply_alignment_vector;

__attribute__((naked, noinline))
char unit_leap_begin(int unit_handle __attribute__((unused)), float *forward __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movsbl 0x253(%%eax), %%ecx\n\t"
      "addl $-0x17, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpl $0x12, %%ecx\n\t"
      "ja .Lunit_leap_begin_1\n\t"
      "movzbl 0x1b1ce8(%%ecx), %%ecx\n\t"
      "jmp *.Lunit_leap_begin_jt(,%%ecx,4)\n\t"
      ".Lunit_leap_begin_1:\n\t"
      "cmpw $0, 0x64(%%eax)\n\t"
      "jne .Lunit_leap_begin_2\n\t"
      "movb 0x424(%%eax), %%dl\n\t"
      "andb $1, %%dl\n\t"
      "movb %%dl, -0x1(%%ebp)\n\t"
      "jne .Lunit_leap_begin_4\n\t"
      ".Lunit_leap_begin_2:\n\t"
      "pushl $0x27\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ad260]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_leap_begin_4\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Lunit_leap_begin_3\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c1af180]\n\t"
      ".Lunit_leap_begin_3:\n\t"
      "movb $1, %%bl\n\t"
      ".Lunit_leap_begin_4:\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lunit_leap_begin_jt:\n\t"
      ".long .Lunit_leap_begin_4\n\t"
      ".long .Lunit_leap_begin_1\n\t"
      ".text\n\t"
      :
      : [get] "m"(b1b1c70_get), [c1ad260] "m"(b1b1c70_c1ad260), [c1af180] "m"(b1b1c70_c1af180)
      : "memory");
}
#else
#error "unit_leap_begin: clang naked draft required"
#endif


/* unit_throw_grenade_begin (0x1b2090) — XBE naked draft (batch 51). */
#if defined(__clang__)
static void *(*const b1b2090_get)(int, int) = object_get_and_verify_type;
static void *(*const b1b2090_tag)(int, int) = tag_get;
static int (*const b1b2090_c1adeb0)(int unit_handle, int16_t weapon_index) = unit_get_weapon;
static int16_t (*const b1b2090_c1aaee0)(int unit_handle) = unit_get_current_grenade_type;
static int16_t (*const b1b2090_c1aae70)(int unit_handle, int16_t grenade_type) = unit_get_grenade_count;
static int (*const b1b2090_cfb0f0)(int weapon_handle) = weapon_prevents_grenade_throwing;
static void (*const b1b2090_cfd510)(int weapon_handle) = weapon_stop_reload;
static void (*const b1b2090_c1a0950)(int unit_handle) = biped_stop_melee_attack;
static char (*const b1b2090_c1ad260)(int unit_handle, int16_t anim_state) = FUN_001ad260;
static void *(*const b1b2090_elem)(void *, int, int) = tag_block_get_element;
static float (*const b1b2090_mag)(float *) = magnitude3d;
static void (*const b1b2090_c1af180)(int unit_handle, float *alignment_vector) = unit_apply_alignment_vector;
static void (*const b1b2090_cde360)(int unit_handle, int message_type) = first_person_weapon_message_from_unit;
static void (*const b1b2090_cb6a20)(int unit_handle) = player_clear_aim_assist;
static void * (*const b1b2090_c18e450)(void) = game_globals_get;
static int (*const b1b2090_o9ec30)(int, int, int, short, float, float, int, int) = FUN_0009ec30;

__attribute__((naked, noinline))
char unit_throw_grenade_begin(int unit_handle __attribute__((unused)), float *alignment_vector __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[get]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x2a2(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1adeb0]\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c1aaee0]\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c1aae70]\n\t"
      "addl $0x2c, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lunit_throw_grenade_begin_6\n\t"
      "movsbl 0x253(%%esi), %%eax\n\t"
      "addl $-0x17, %%eax\n\t"
      "cmpl $0x12, %%eax\n\t"
      "ja .Lunit_throw_grenade_begin_1\n\t"
      "movzbl 0x1b2244(%%eax), %%edx\n\t"
      "jmp *.Lunit_throw_grenade_begin_jt(,%%edx,4)\n\t"
      ".Lunit_throw_grenade_begin_1:\n\t"
      "pushl %%ebx\n\t"
      "call *%[cfb0f0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunit_throw_grenade_begin_6\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .Lunit_throw_grenade_begin_2\n\t"
      "pushl %%ebx\n\t"
      "call *%[cfd510]\n\t"
      "addl $4, %%esp\n\t"
      ".Lunit_throw_grenade_begin_2:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a0950]\n\t"
      "pushl $0x21\n\t"
      "pushl %%edi\n\t"
      "movb $0, 0x254(%%esi)\n\t"
      "movw $0xffff, 0x25a(%%esi)\n\t"
      "call *%[c1ad260]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_throw_grenade_begin_6\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movb $1, 0x23d(%%esi)\n\t"
      "movw $0, 0x23e(%%esi)\n\t"
      "movl 0x44(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x616e7472\n\t"
      "call *%[tag]\n\t"
      "movswl 0x80(%%esi), %%edx\n\t"
      "pushl $0xb4\n\t"
      "pushl %%edx\n\t"
      "addl $0x74, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl 0x34(%%eax), %%eax\n\t"
      "subw 0x82(%%esi), %%ax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "incl %%eax\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movw %%ax, 0x240(%%esi)\n\t"
      "jne .Lunit_throw_grenade_begin_3\n\t"
      "movl 0x1ec(%%esi), %%ecx\n\t"
      "movl 0x1f0(%%esi), %%edx\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_throw_grenade_begin_4\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      ".Lunit_throw_grenade_begin_3:\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1af180]\n\t"
      ".Lunit_throw_grenade_begin_4:\n\t"
      "pushl $0x11\n\t"
      "pushl %%edi\n\t"
      "call *%[cde360]\n\t"
      "pushl %%edi\n\t"
      "call *%[cb6a20]\n\t"
      "movsbl 0x2cc(%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x44\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18e450]\n\t"
      "addl $0x128, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x10(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lunit_throw_grenade_begin_5\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[o9ec30]\n\t"
      "addl $0x20, %%esp\n\t"
      ".Lunit_throw_grenade_begin_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lunit_throw_grenade_begin_6:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lunit_throw_grenade_begin_jt:\n\t"
      ".long .Lunit_throw_grenade_begin_6\n\t"
      ".long .Lunit_throw_grenade_begin_1\n\t"
      ".text\n\t"
      :
      : [get] "m"(b1b2090_get), [tag] "m"(b1b2090_tag), [c1adeb0] "m"(b1b2090_c1adeb0), [c1aaee0] "m"(b1b2090_c1aaee0), [c1aae70] "m"(b1b2090_c1aae70), [cfb0f0] "m"(b1b2090_cfb0f0), [cfd510] "m"(b1b2090_cfd510), [c1a0950] "m"(b1b2090_c1a0950), [c1ad260] "m"(b1b2090_c1ad260), [elem] "m"(b1b2090_elem), [mag] "m"(b1b2090_mag), [c1af180] "m"(b1b2090_c1af180), [cde360] "m"(b1b2090_cde360), [cb6a20] "m"(b1b2090_cb6a20), [c18e450] "m"(b1b2090_c18e450), [o9ec30] "m"(b1b2090_o9ec30)
      : "memory");
}
#else
#error "unit_throw_grenade_begin: clang naked draft required"
#endif


/* unit_melee_attack_begin (0x1b1b60) — XBE naked draft (batch 62). */
#if defined(__clang__)
static void *(*const b1b1b60_get)(int, int) = object_get_and_verify_type;
static void *(*const b1b1b60_tag)(int, int) = tag_get;
static char (*const b1b1b60_c1ad260)(int unit_handle, int16_t anim_state) = FUN_001ad260;
static void (*const b1b1b60_c1af180)(int unit_handle, float *alignment_vector) = unit_apply_alignment_vector;

__attribute__((naked, noinline))
char unit_melee_attack_begin(int unit_handle __attribute__((unused)), char param_2 __attribute__((unused)), int param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movb 0x253(%%esi), %%cl\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movsbl %%cl, %%eax\n\t"
      "addl $-0x17, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpl $0x12, %%eax\n\t"
      "ja .Lunit_melee_attack_begin_1\n\t"
      "movzbl 0x1b1c54(%%eax), %%edx\n\t"
      "jmp *.Lunit_melee_attack_begin_jt(,%%edx,4)\n\t"
      ".Lunit_melee_attack_begin_1:\n\t"
      "xorb %%al, %%al\n\t"
      "cmpw $0, 0x64(%%esi)\n\t"
      "jne .Lunit_melee_attack_begin_2\n\t"
      "movb 0x424(%%esi), %%al\n\t"
      "andb $1, %%al\n\t"
      ".Lunit_melee_attack_begin_2:\n\t"
      "movb 0xc(%%ebp), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .Lunit_melee_attack_begin_3\n\t"
      "movl $0x20, %%eax\n\t"
      "jmp .Lunit_melee_attack_begin_5\n\t"
      ".Lunit_melee_attack_begin_3:\n\t"
      "cmpb $0x28, %%cl\n\t"
      "jne .Lunit_melee_attack_begin_4\n\t"
      "movl $0x29, %%eax\n\t"
      "jmp .Lunit_melee_attack_begin_5\n\t"
      ".Lunit_melee_attack_begin_4:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testb %%al, %%al\n\t"
      "setne %%cl\n\t"
      "addl $0x1e, %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      ".Lunit_melee_attack_begin_5:\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ad260]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunit_melee_attack_begin_6\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_melee_attack_begin_10\n\t"
      ".Lunit_melee_attack_begin_6:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x17c(%%edx), %%eax\n\t"
      "testb $1, %%ah\n\t"
      "je .Lunit_melee_attack_begin_7\n\t"
      "movb $0x19, 0x253(%%esi)\n\t"
      ".Lunit_melee_attack_begin_7:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Lunit_melee_attack_begin_8\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1af180]\n\t"
      ".Lunit_melee_attack_begin_8:\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_melee_attack_begin_9\n\t"
      "popl %%edi\n\t"
      "movb $1, %%bl\n\t"
      "movb $4, 0x239(%%esi)\n\t"
      "movb $0, 0x23a(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lunit_melee_attack_begin_9:\n\t"
      "movb $1, 0x239(%%esi)\n\t"
      "movb $1, %%bl\n\t"
      ".Lunit_melee_attack_begin_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lunit_melee_attack_begin_jt:\n\t"
      ".long .Lunit_melee_attack_begin_10\n\t"
      ".long .Lunit_melee_attack_begin_1\n\t"
      ".text\n\t"
      :
      : [get] "m"(b1b1b60_get), [tag] "m"(b1b1b60_tag), [c1ad260] "m"(b1b1b60_c1ad260), [c1af180] "m"(b1b1b60_c1af180)
      : "memory");
}
#else
#error "unit_melee_attack_begin: clang naked draft required"
#endif


/* unit_place (0x1b24d0) — XBE naked draft (batch 61). */
#if defined(__clang__)
static void *(*const b1b24d0_get)(int, int) = object_get_and_verify_type;
static void *(*const b1b24d0_tag)(int, int) = tag_get;
static void (*const b1b24d0_c1b1400)(int unit_handle, char is_melee, char is_throw, char is_airborne, char is_ground, char is_ping, float throttle_magnitude, int weapon_class, int alignment_vector) = FUN_001b1400;
static void (*const b1b24d0_c1aac80)(int unit_handle) = unit_clear_weapons;
static void *(*const b1b24d0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b1b24d0_odel)(int) = object_delete;
static void *(*const b1b24d0_elem)(void *, int, int) = tag_block_get_element;
static int (*const b1b24d0_gtime)(void) = game_time_get;
static void (*const b1b24d0_c136b40)(int object_handle) = FUN_00136b40;
static void (*const b1b24d0_c1446a0)(int object_handle) = object_update_children_recursive;

__attribute__((naked, noinline))
void unit_place(int unit_handle __attribute__((unused)), void *placement __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x10, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_place_1\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, 0x90(%%esi)\n\t"
      ".Lunit_place_1:\n\t"
      "testb $1, 0x4(%%ecx)\n\t"
      "je .Lunit_place_3\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[c1b1400]\n\t"
      "movb 0x253(%%esi), %%al\n\t"
      "addl $0x24, %%esp\n\t"
      "cmpb $0x19, %%al\n\t"
      "jne .Lunit_place_3\n\t"
      "pushl %%edi\n\t"
      "call *%[c1aac80]\n\t"
      "pushl $2\n\t"
      "leal 0x2ce(%%esi), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl 0x2c8(%%esi), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lunit_place_2\n\t"
      "pushl %%eax\n\t"
      "call *%[odel]\n\t"
      "addl $4, %%esp\n\t"
      "movl $0xffffffff, 0x2c8(%%esi)\n\t"
      ".Lunit_place_2:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x44(%%ecx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x616e7472\n\t"
      "call *%[tag]\n\t"
      "movswl 0x80(%%esi), %%ecx\n\t"
      "pushl $0xb4\n\t"
      "pushl %%ecx\n\t"
      "addl $0x74, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl 0x22(%%eax), %%eax\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "addl $-4, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "setl %%dl\n\t"
      "orb $4, 0xb6(%%esi)\n\t"
      "orl $0x20000, %%ecx\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      "decl %%edx\n\t"
      "andl %%edx, %%eax\n\t"
      "movl 0x1b4(%%esi), %%edx\n\t"
      "orl $0x200, %%edx\n\t"
      "movw %%ax, 0x82(%%esi)\n\t"
      "movl %%edx, 0x1b4(%%esi)\n\t"
      "call *%[gtime]\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, 0x3cc(%%esi)\n\t"
      "movl $0, 0x90(%%esi)\n\t"
      "movl $0, 0x94(%%esi)\n\t"
      "call *%[c136b40]\n\t"
      "pushl %%edi\n\t"
      "call *%[c1446a0]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".Lunit_place_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1b24d0_get), [tag] "m"(b1b24d0_tag), [c1b1400] "m"(b1b24d0_c1b1400), [c1aac80] "m"(b1b24d0_c1aac80), [memset] "m"(b1b24d0_memset), [odel] "m"(b1b24d0_odel), [elem] "m"(b1b24d0_elem), [gtime] "m"(b1b24d0_gtime), [c136b40] "m"(b1b24d0_c136b40), [c1446a0] "m"(b1b24d0_c1446a0)
      : "memory");
}
#else
#error "unit_place: clang naked draft required"
#endif


/* unit_create_initial_weapons (0x1b2660) — XBE naked draft (batch 62). */
#if defined(__clang__)
static void *(*const b1b2660_get)(int, int) = object_get_and_verify_type;
static void *(*const b1b2660_tag)(int, int) = tag_get;
static void *(*const b1b2660_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1b2660_opnew)(void *, int, int) = object_placement_data_new;
static int (*const b1b2660_onew)(void *) = object_new;
static bool (*const b1b2660_gerun)(void) = game_engine_running;
static char (*const b1b2660_c1aad00)(int unit_handle, int definition_index) = unit_has_weapon_definition_index;
static bool (*const b1b2660_c1b1db0)(int unit_handle, int seat_object_handle, int16_t flag) = unit_enter_seat;
static void (*const b1b2660_odel)(int) = object_delete;

__attribute__((naked, noinline))
void unit_create_initial_weapons(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x8c, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "leal 0x2d8(%%eax), %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jle .Lunit_create_initial_weapons_5\n\t"
      "pushl %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "pushl %%esi\n\t"
      ".Lunit_create_initial_weapons_1:\n\t"
      "pushl $0x24\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lunit_create_initial_weapons_4\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x8c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[opnew]\n\t"
      "leal -0x8c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[onew]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lunit_create_initial_weapons_4\n\t"
      "pushl $4\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[gerun]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_create_initial_weapons_2\n\t"
      "movl (%%ebx), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1aad00]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunit_create_initial_weapons_3\n\t"
      ".Lunit_create_initial_weapons_2:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1b1db0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunit_create_initial_weapons_4\n\t"
      ".Lunit_create_initial_weapons_3:\n\t"
      "pushl %%esi\n\t"
      "call *%[odel]\n\t"
      "addl $4, %%esp\n\t"
      ".Lunit_create_initial_weapons_4:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl (%%edi), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lunit_create_initial_weapons_1\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".Lunit_create_initial_weapons_5:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1b2660_get), [tag] "m"(b1b2660_tag), [elem] "m"(b1b2660_elem), [opnew] "m"(b1b2660_opnew), [onew] "m"(b1b2660_onew), [gerun] "m"(b1b2660_gerun), [c1aad00] "m"(b1b2660_c1aad00), [c1b1db0] "m"(b1b2660_c1b1db0), [odel] "m"(b1b2660_odel)
      : "memory");
}
#else
#error "unit_create_initial_weapons: clang naked draft required"
#endif


/* unit_scripting_enter_vehicle (0x1b32d0) — XBE naked draft (batch 59). */
#if defined(__clang__)
static int (*const b1b32d0_c8df60)(const char *s1) = csstrlen;
static void *(*const b1b32d0_get)(int, int) = object_get_and_verify_type;
static void (*const b1b32d0_c1b2dd0)(int unit_handle) = unit_exit_seat_end;
static void *(*const b1b32d0_tag)(int, int) = tag_get;
static void *(*const b1b32d0_elem)(void *, int, int) = tag_block_get_element;
static int (*const b1b32d0_c1dd801)(const char *a, const char *b) = crt_stricmp;
static char (*const b1b32d0_c1aa700)(int unit_handle, int16_t seat_index) = unit_seat_filled;
static char (*const b1b32d0_c1acd70)(int unit_handle, const char *seat_label, const char *weapon_name, char apply_state) = FUN_001acd70;
static bool (*const b1b32d0_c1b2b80)(int unit_handle, int vehicle_handle, int16_t seat_index) = unit_board_vehicle;

__attribute__((naked, noinline))
void unit_scripting_enter_vehicle(int unit_handle __attribute__((unused)), int vehicle_handle __attribute__((unused)), char *seat_name __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .Lunit_scripting_enter_vehicle_7\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lunit_scripting_enter_vehicle_6\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8df60]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jbe .Lunit_scripting_enter_vehicle_6\n\t"
      "pushl $3\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0xb6(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb $4, %%al\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "jne .Lunit_scripting_enter_vehicle_6\n\t"
      "movl 0xcc(%%esi), %%ecx\n\t"
      "movl $0xffffffff, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .Lunit_scripting_enter_vehicle_2\n\t"
      "cmpw %%ax, 0x2a0(%%esi)\n\t"
      "je .Lunit_scripting_enter_vehicle_1\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1b2dd0]\n\t"
      "addl $4, %%esp\n\t"
      "orl $0xffffffff, %%eax\n\t"
      ".Lunit_scripting_enter_vehicle_1:\n\t"
      "cmpl %%eax, 0xcc(%%esi)\n\t"
      "jne .Lunit_scripting_enter_vehicle_6\n\t"
      ".Lunit_scripting_enter_vehicle_2:\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "leal 0x2e4(%%eax), %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .Lunit_scripting_enter_vehicle_6\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lunit_scripting_enter_vehicle_3:\n\t"
      "pushl $0x11c\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "leal 0x4(%%eax), %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c1dd801]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lunit_scripting_enter_vehicle_4\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1aa700]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunit_scripting_enter_vehicle_4\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "cmpw $1, 0x64(%%ecx)\n\t"
      "je .Lunit_scripting_enter_vehicle_5\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c1acd70]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunit_scripting_enter_vehicle_5\n\t"
      ".Lunit_scripting_enter_vehicle_4:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lunit_scripting_enter_vehicle_3\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lunit_scripting_enter_vehicle_5:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1b2b80]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lunit_scripting_enter_vehicle_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".Lunit_scripting_enter_vehicle_7:\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8df60] "m"(b1b32d0_c8df60), [get] "m"(b1b32d0_get), [c1b2dd0] "m"(b1b32d0_c1b2dd0), [tag] "m"(b1b32d0_tag), [elem] "m"(b1b32d0_elem), [c1dd801] "m"(b1b32d0_c1dd801), [c1aa700] "m"(b1b32d0_c1aa700), [c1acd70] "m"(b1b32d0_c1acd70), [c1b2b80] "m"(b1b32d0_c1b2b80)
      : "memory");
}
#else
#error "unit_scripting_enter_vehicle: clang naked draft required"
#endif


/* vehicle_scripting_load_magic (0x1b3400) — XBE naked draft (batch 58). */
#if defined(__clang__)
static void *(*const b1b3400_get)(int, int) = object_get_and_verify_type;
static void *(*const b1b3400_tag)(int, int) = tag_get;
static int16_t (*const b1b3400_c1adfc0)(int unit_handle, int seat_substring, int16_t seat_desire_type, int16_t *seat_indices, int16_t max_seats) = vehicle_scripting_find_available_seats;
static int (*const b1b3400_cce450)(int parent_handle, int *iter_state) = FUN_000ce450;
static void *(*const b1b3400_elem)(void *, int, int) = tag_block_get_element;
static char (*const b1b3400_c1acd70)(int unit_handle, const char *seat_label, const char *weapon_name, char apply_state) = FUN_001acd70;
static void (*const b1b3400_c1b2dd0)(int unit_handle) = unit_exit_seat_end;
static bool (*const b1b3400_c1b2b80)(int unit_handle, int vehicle_handle, int16_t seat_index) = unit_board_vehicle;
static int (*const b1b3400_cce320)(int parent_handle, int *iter_state) = FUN_000ce320;

__attribute__((naked, noinline))
uint16_t vehicle_scripting_load_magic(int vehicle_handle __attribute__((unused)), int seat_substring __attribute__((unused)), int group_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x38, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpl $-1, %%esi\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "je .Lvehicle_scripting_load_magic_10\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl $0x10\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "call *%[c1adfc0]\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[cce450]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0x2c, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .Lvehicle_scripting_load_magic_10\n\t"
      ".Lvehicle_scripting_load_magic_1:\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movb 0x64(%%edi), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "testb $3, %%dl\n\t"
      "je .Lvehicle_scripting_load_magic_9\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "testb $4, 0xb6(%%eax)\n\t"
      "jne .Lvehicle_scripting_load_magic_9\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw %%ax, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jle .Lvehicle_scripting_load_magic_9\n\t"
      ".Lvehicle_scripting_load_magic_2:\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movw -0x38(%%ebp,%%ecx,2), %%si\n\t"
      "cmpw $-1, %%si\n\t"
      "je .Lvehicle_scripting_load_magic_7\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movswl %%si, %%edx\n\t"
      "pushl $0x11c\n\t"
      "pushl %%edx\n\t"
      "addl $0x2e4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $1, 0x64(%%edi)\n\t"
      "je .Lvehicle_scripting_load_magic_3\n\t"
      "pushl $0\n\t"
      "addl $4, %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c1acd70]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lvehicle_scripting_load_magic_6\n\t"
      ".Lvehicle_scripting_load_magic_3:\n\t"
      "movl 0xcc(%%edi), %%ecx\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .Lvehicle_scripting_load_magic_5\n\t"
      "cmpw %%ax, 0x2a0(%%edi)\n\t"
      "je .Lvehicle_scripting_load_magic_4\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1b2dd0]\n\t"
      "addl $4, %%esp\n\t"
      "orl $0xffffffff, %%eax\n\t"
      ".Lvehicle_scripting_load_magic_4:\n\t"
      "cmpl %%eax, 0xcc(%%edi)\n\t"
      "jne .Lvehicle_scripting_load_magic_6\n\t"
      ".Lvehicle_scripting_load_magic_5:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1b2b80]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lvehicle_scripting_load_magic_8\n\t"
      ".Lvehicle_scripting_load_magic_6:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      ".Lvehicle_scripting_load_magic_7:\n\t"
      "incl %%eax\n\t"
      "cmpw -0xc(%%ebp), %%ax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jl .Lvehicle_scripting_load_magic_2\n\t"
      "jmp .Lvehicle_scripting_load_magic_9\n\t"
      ".Lvehicle_scripting_load_magic_8:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movswl -0x4(%%ebp), %%edx\n\t"
      "incl %%eax\n\t"
      "movw $0xffff, -0x38(%%ebp,%%edx,2)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".Lvehicle_scripting_load_magic_9:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[cce320]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "jne .Lvehicle_scripting_load_magic_1\n\t"
      "movw -0x8(%%ebp), %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lvehicle_scripting_load_magic_10:\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1b3400_get), [tag] "m"(b1b3400_tag), [c1adfc0] "m"(b1b3400_c1adfc0), [cce450] "m"(b1b3400_cce450), [elem] "m"(b1b3400_elem), [c1acd70] "m"(b1b3400_c1acd70), [c1b2dd0] "m"(b1b3400_c1b2dd0), [c1b2b80] "m"(b1b3400_c1b2b80), [cce320] "m"(b1b3400_cce320)
      : "memory");
}
#else
#error "vehicle_scripting_load_magic: clang naked draft required"
#endif


/* unit_try_and_exit_seat (0x1b3580) — XBE naked draft (batch 61). */
#if defined(__clang__)
static void *(*const b1b3580_get)(int, int) = object_get_and_verify_type;
static void (*const b1b3580_c1b2dd0)(int unit_handle) = unit_exit_seat_end;
static char (*const b1b3580_c1a8730)(void *anim_state) = FUN_001a8730;
static void *(*const b1b3580_tag)(int, int) = tag_get;
static void *(*const b1b3580_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1b3580_c1ae160)(int unit_handle) = unit_open;
static int16_t (*const b1b3580_cfad00)(int animation_graph_tag_index, int16_t animation_index) = FUN_000fad00;
static void (*const b1b3580_c1ab7c0)(int unit_handle, int anim_graph_tag_index, int16_t animation_index) = unit_set_animation;
static void (*const b1b3580_c13ffc0)(int object_handle, int flag) = object_set_garbage;
static void (*const b1b3580_c409e0)(int param_1) = ai_handle_exit_vehicle;

__attribute__((naked, noinline))
char unit_try_and_exit_seat(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xcc(%%esi), %%ecx\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .Lunit_try_and_exit_seat_1\n\t"
      "cmpw %%ax, 0x2a0(%%esi)\n\t"
      "je .Lunit_try_and_exit_seat_1\n\t"
      "cmpw $1, 0x64(%%esi)\n\t"
      "jne .Lunit_try_and_exit_seat_2\n\t"
      "pushl %%edi\n\t"
      "call *%[c1b2dd0]\n\t"
      "addl $4, %%esp\n\t"
      ".Lunit_try_and_exit_seat_1:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lunit_try_and_exit_seat_2:\n\t"
      "leal 0x248(%%esi), %%ecx\n\t"
      "call *%[c1a8730]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunit_try_and_exit_seat_1\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x44(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x616e7472\n\t"
      "call *%[tag]\n\t"
      "movsbl 0x250(%%esi), %%edx\n\t"
      "pushl $0x64\n\t"
      "pushl %%edx\n\t"
      "addl $0xc, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x40(%%eax), %%ecx\n\t"
      "addl $0x1c, %%esp\n\t"
      "cmpl $8, %%ecx\n\t"
      "jle .Lunit_try_and_exit_seat_1\n\t"
      "movl 0x44(%%eax), %%eax\n\t"
      "movw 0x10(%%eax), %%bx\n\t"
      "cmpw $-1, %%bx\n\t"
      "je .Lunit_try_and_exit_seat_4\n\t"
      "movl 0xcc(%%esi), %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl 0x2d4(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jne .Lunit_try_and_exit_seat_3\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ae160]\n\t"
      "addl $4, %%esp\n\t"
      ".Lunit_try_and_exit_seat_3:\n\t"
      "movl 0x44(%%edi), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cfad00]\n\t"
      "movl 0x44(%%edi), %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "call *%[c1ab7c0]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[c13ffc0]\n\t"
      "movl 0xcc(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "movb $0x1b, 0x253(%%esi)\n\t"
      "call *%[c409e0]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lunit_try_and_exit_seat_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1b3580_get), [c1b2dd0] "m"(b1b3580_c1b2dd0), [c1a8730] "m"(b1b3580_c1a8730), [tag] "m"(b1b3580_tag), [elem] "m"(b1b3580_elem), [c1ae160] "m"(b1b3580_c1ae160), [cfad00] "m"(b1b3580_cfad00), [c1ab7c0] "m"(b1b3580_c1ab7c0), [c13ffc0] "m"(b1b3580_c13ffc0), [c409e0] "m"(b1b3580_c409e0)
      : "memory");
}
#else
#error "unit_try_and_exit_seat: clang naked draft required"
#endif


/* unit_impact_melee_damage (0x1b2290) — XBE naked draft (batch 53). */
#if defined(__clang__)
static void *(*const b1b2290_get)(int, int) = object_get_and_verify_type;
static void *(*const b1b2290_tag)(int, int) = tag_get;
static void (*const b1b2290_c1ae840)(int unit_handle, char melee_hit, int target_handle, int param_4, int param_5, int param_6, int param_7) = unit_cause_melee_damage;
static void (*const b1b2290_c137540)(int object_handle) = object_deplete_body;
static void (*const b1b2290_odel)(int) = object_delete;
static void (*const b1b2290_cross)(float *, float *, float *) = cross_product3d;
static float (*const b1b2290_norm)(float *) = normalize3d;
static void (*const b1b2290_otrans)(int, float *, void *) = object_translate;
static void (*const b1b2290_c144240)(int parent_handle, int child_handle, int parent_node_index) = object_attach_to_parent;
static char (*const b1b2290_c1b1b60)(int unit_handle, char param_2, int param_3) = unit_melee_attack_begin;

__attribute__((naked, noinline))
void unit_impact_melee_damage(int unit_handle __attribute__((unused)), int param_2 __attribute__((unused)), int param_3 __attribute__((unused)), int param_4 __attribute__((unused)), int param_5 __attribute__((unused)), int param_6 __attribute__((unused)), float *param_7 __attribute__((unused)), int param_8 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[get]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x17c(%%edx), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "testb $0x20, %%ah\n\t"
      "je .Lunit_impact_melee_damage_1\n\t"
      "cmpw $0, 0x64(%%edi)\n\t"
      "jne .Lunit_impact_melee_damage_1\n\t"
      "flds 0x94(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_impact_melee_damage_1\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0x17c(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testl $0x400000, %%ecx\n\t"
      "je .Lunit_impact_melee_damage_1\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1ae840]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c137540]\n\t"
      "pushl %%ebx\n\t"
      "call *%[odel]\n\t"
      "addl $0x24, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lunit_impact_melee_damage_1:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x17c(%%eax), %%ecx\n\t"
      "testb $0x10, %%ch\n\t"
      "je .Lunit_impact_melee_damage_5\n\t"
      "movb 0x64(%%edi), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testb $3, %%dl\n\t"
      "je .Lunit_impact_melee_damage_5\n\t"
      "testb $4, 0xb6(%%edi)\n\t"
      "jne .Lunit_impact_melee_damage_5\n\t"
      "movl 0xcc(%%edi), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lunit_impact_melee_damage_3\n\t"
      "jmp .Lunit_impact_melee_damage_2\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lunit_impact_melee_damage_2:\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "je .Lunit_impact_melee_damage_5\n\t"
      "cmpw $1, 0x64(%%eax)\n\t"
      "jne .Lunit_impact_melee_damage_5\n\t"
      "movl 0xcc(%%eax), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .Lunit_impact_melee_damage_2\n\t"
      ".Lunit_impact_melee_damage_3:\n\t"
      "movl 0x31fc38, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "leal 0x18(%%esi), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl 0x31fc38, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal 0x3c(%%esi), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl (%%ecx), %%eax\n\t"
      "leal 0x24(%%esi), %%edi\n\t"
      "movl %%edi, %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "flds (%%edi)\n\t"
      "fchs\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "fstps (%%edi)\n\t"
      "pushl %%edx\n\t"
      "flds 0x4(%%edi)\n\t"
      "leal 0x30(%%esi), %%eax\n\t"
      "fchs\n\t"
      "pushl %%edi\n\t"
      "fstps 0x4(%%edi)\n\t"
      "pushl %%eax\n\t"
      "flds 0x8(%%edi)\n\t"
      "fchs\n\t"
      "fstps 0x8(%%edi)\n\t"
      "call *%[cross]\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x10, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lunit_impact_melee_damage_4\n\t"
      "movl 0x31fc44, %%edx\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[cross]\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x10, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lunit_impact_melee_damage_4\n\t"
      "movl 0x31fc3c, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      ".Lunit_impact_melee_damage_4:\n\t"
      "leal 0x30(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[cross]\n\t"
      "movl 0x24(%%ebp), %%eax\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[otrans]\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c144240]\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl 0x1b4(%%esi), %%edi\n\t"
      "pushl $0\n\t"
      "orl $0x20, %%eax\n\t"
      "pushl $1\n\t"
      "orl $0x8000, %%edi\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "movl %%edi, 0x1b4(%%esi)\n\t"
      "call *%[c1b1b60]\n\t"
      "addl $0x30, %%esp\n\t"
      ".Lunit_impact_melee_damage_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [get] "m"(b1b2290_get), [tag] "m"(b1b2290_tag), [c1ae840] "m"(b1b2290_c1ae840), [c137540] "m"(b1b2290_c137540), [odel] "m"(b1b2290_odel), [cross] "m"(b1b2290_cross), [norm] "m"(b1b2290_norm), [otrans] "m"(b1b2290_otrans), [c144240] "m"(b1b2290_c144240), [c1b1b60] "m"(b1b2290_c1b1b60)
      : "memory");
}
#else
#error "unit_impact_melee_damage: clang naked draft required"
#endif


/* unit_cause_melee_damage (0x1ae840) — XBE naked draft (batch 54). */
#if defined(__clang__)
static void *(*const b1ae840_get)(int, int) = object_get_and_verify_type;
static void *(*const b1ae840_tag)(int, int) = tag_get;
static short (*const b1ae840_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static void (*const b1ae840_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1ae840_exitfn)(int) = system_exit;
static bool (*const b1ae840_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;
static int (*const b1ae840_c1adeb0)(int unit_handle, int16_t weapon_index) = unit_get_weapon;
static void (*const b1ae840_c136750)(void *damage_params, int tag_index) = damage_data_new;
static void (*const b1ae840_c138e30)(void *damage_params, int target_index) = FUN_00138e30;
static void (*const b1ae840_c137d20)(void *damage_params, int object_handle, short node_index, short region_index, short permutation_index, unsigned int flags) = object_cause_damage;
static void (*const b1ae840_c1abd10)(int16_t material_type, int unit_handle, int weapon_tag_index) = FUN_001abd10;

__attribute__((naked, noinline))
void unit_cause_melee_damage(int unit_handle __attribute__((unused)), char melee_hit __attribute__((unused)), int target_handle __attribute__((unused)), int param_4 __attribute__((unused)), int param_5 __attribute__((unused)), int param_6 __attribute__((unused)), int param_7 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xd8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x294(%%edi), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lunit_cause_melee_damage_9\n\t"
      "pushl $1\n\t"
      "leal -0xd8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x25961c\n\t"
      "pushl %%esi\n\t"
      "call *%[markers]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .Lunit_cause_melee_damage_4\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "movl -0x78(%%ebp), %%edx\n\t"
      "movl -0x74(%%ebp), %%eax\n\t"
      "movl -0x70(%%ebp), %%ecx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jl .Lunit_cause_melee_damage_1\n\t"
      "pushl $1\n\t"
      "pushl $0x21b9\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_cause_melee_damage_1:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "flds -0xc(%%ebp)\n\t"
      "movswl %%ax, %%edx\n\t"
      "incw %%ax\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "leal 0x50(%%ebx), %%esi\n\t"
      "movw $7, 0x5a8c80(,%%edx,2)\n\t"
      "leal -0x68(%%ebp), %%eax\n\t"
      "fsubs (%%esi)\n\t"
      "pushl %%eax\n\t"
      "pushl $-1\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "flds -0x8(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "pushl $0x1000e9\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fsubs 0x8(%%esi)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_cause_melee_damage_2\n\t"
      "movl %%esi, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".Lunit_cause_melee_damage_2:\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "jg .Lunit_cause_melee_damage_3\n\t"
      "pushl $1\n\t"
      "pushl $0x21c1\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_cause_melee_damage_3:\n\t"
      "decw 0x4761d8\n\t"
      "jmp .Lunit_cause_melee_damage_5\n\t"
      ".Lunit_cause_melee_damage_4:\n\t"
      "leal 0x50(%%ebx), %%esi\n\t"
      "movl %%esi, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".Lunit_cause_melee_damage_5:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x294(%%edi), %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2a2(%%eax), %%dx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1adeb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lunit_cause_melee_damage_6\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x77656170\n\t"
      "call *%[tag]\n\t"
      "movl 0x308(%%eax), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%ch, %%ch\n\t"
      "jns .Lunit_cause_melee_damage_6\n\t"
      "movl 0x3a0(%%eax), %%edi\n\t"
      ".Lunit_cause_melee_damage_6:\n\t"
      "leal -0x6c(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c136750]\n\t"
      "movl 0x48(%%ebx), %%eax\n\t"
      "movl 0x4c(%%ebx), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%eax, -0x58(%%ebp)\n\t"
      "movw 0x68(%%ebx), %%ax\n\t"
      "movw %%ax, -0x5c(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x54(%%ebp)\n\t"
      "movl 0x1c8(%%ebx), %%ecx\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl %%edx, -0x60(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%ecx, -0x64(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl %%ecx, -0x48(%%ebp)\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%edx, -0x44(%%ebp)\n\t"
      "movl %%ecx, -0x3c(%%ebp)\n\t"
      "jne .Lunit_cause_melee_damage_7\n\t"
      "pushl %%eax\n\t"
      "leal -0x6c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c138e30]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Lunit_cause_melee_damage_8\n\t"
      ".Lunit_cause_melee_damage_7:\n\t"
      "movl 0x20(%%ebp), %%ecx\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x6c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c137d20]\n\t"
      "addl $0x18, %%esp\n\t"
      ".Lunit_cause_melee_damage_8:\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunit_cause_melee_damage_9\n\t"
      "cmpw $-1, -0x20(%%ebp)\n\t"
      "je .Lunit_cause_melee_damage_9\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "call *%[c1abd10]\n\t"
      ".Lunit_cause_melee_damage_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $0, 0x239(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [get] "m"(b1ae840_get), [tag] "m"(b1ae840_tag), [markers] "m"(b1ae840_markers), [assert] "m"(b1ae840_assert), [exitfn] "m"(b1ae840_exitfn), [ray] "m"(b1ae840_ray), [c1adeb0] "m"(b1ae840_c1adeb0), [c136750] "m"(b1ae840_c136750), [c138e30] "m"(b1ae840_c138e30), [c137d20] "m"(b1ae840_c137d20), [c1abd10] "m"(b1ae840_c1abd10)
      : "memory");
}
#else
#error "unit_cause_melee_damage: clang naked draft required"
#endif


/* unit_died (0x1b3060) — XBE naked draft (batch 55). */
#if defined(__clang__)
static void *(*const b1b3060_get)(int, int) = object_get_and_verify_type;
static void (*const b1b3060_garb)(int, int) = object_set_garbage_flag;
static void (*const b1b3060_cba550)(int) = player_died;
static void *(*const b1b3060_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b1b3060_c3cff0)(int actor_handle) = actor_died;
static void (*const b1b3060_c3d330)(int actor_handle, int unit_handle) = actor_swarm_unit_died;
static int (*const b1b3060_gtime)(void) = game_time_get;
static int (*const b1b3060_c1adeb0)(int unit_handle, int16_t weapon_index) = unit_get_weapon;
static void (*const b1b3060_cfc4b0)(int weapon_handle, int16_t owner_state, float t) = weapon_owner_update;
static void (*const b1b3060_c1b2dd0)(int unit_handle) = unit_exit_seat_end;
static void (*const b1b3060_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1b3060_exitfn)(int) = system_exit;
static void *(*const b1b3060_tag)(int, int) = tag_get;
static int *(*const b1b3060_gseed)(void) = get_global_random_seed_address;
static float (*const b1b3060_rmreal)(unsigned int *) = random_math_real;
static void (*const b1b3060_c1aa5c0)(int object_handle) = unit_detach_from_parent;
static void (*const b1b3060_c1abbd0)(int unit_handle) = unit_drop_weapons_on_death;
static void (*const b1b3060_c1ab990)(int unit_handle, int weapon_handle) = unit_detach_weapon;
static void (*const b1b3060_c1abb20)(int unit_handle) = unit_drop_grenades_on_death;
static bool (*const b1b3060_c1ae600)(int unit_handle, bool flag) = unit_set_in_vehicle;

__attribute__((naked, noinline))
void unit_died(int unit_handle __attribute__((unused)), char param_2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunit_died_6\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "movw $0, 0x3d0(%%ebx)\n\t"
      "call *%[garb]\n\t"
      "movl 0x1c8(%%ebx), %%eax\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%esi, %%eax\n\t"
      "je .Lunit_died_1\n\t"
      "pushl %%eax\n\t"
      "call *%[cba550]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%esi, 0x1c8(%%ebx)\n\t"
      ".Lunit_died_1:\n\t"
      "movl 0x1a4(%%ebx), %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "je .Lunit_died_2\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movw 0x34(%%eax), %%dx\n\t"
      "movl 0x1a4(%%ebx), %%ecx\n\t"
      "movw %%dx, 0x2e4(%%ebx)\n\t"
      "movw 0x3a(%%eax), %%ax\n\t"
      "pushl %%ecx\n\t"
      "movw %%ax, 0x2e6(%%ebx)\n\t"
      "call *%[c3cff0]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%esi, 0x1a4(%%ebx)\n\t"
      ".Lunit_died_2:\n\t"
      "movl 0x1a8(%%ebx), %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "je .Lunit_died_3\n\t"
      "movl 0x6325a4, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movw 0x34(%%eax), %%cx\n\t"
      "movw %%cx, 0x2e4(%%ebx)\n\t"
      "movw 0x3a(%%eax), %%dx\n\t"
      "movl 0x1a8(%%ebx), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movw %%dx, 0x2e6(%%ebx)\n\t"
      "call *%[c3d330]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%esi, 0x1a8(%%ebx)\n\t"
      ".Lunit_died_3:\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, 0x3cc(%%ebx)\n\t"
      ".Lunit_died_4:\n\t"
      "movl 0x1b4(%%ebx), %%ecx\n\t"
      "andl $0xffffffee, %%ecx\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "cmpw %%si, 0x2a2(%%ebx)\n\t"
      "movl %%ecx, 0x1b4(%%ebx)\n\t"
      "movl $0, 0x1b8(%%ebx)\n\t"
      "je .Lunit_died_5\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x2a2(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1adeb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[cfc4b0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lunit_died_5:\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "andl $0xfdffffff, 0x1b4(%%eax)\n\t"
      "movl 0xcc(%%ebx), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%esi, %%eax\n\t"
      "je .Lunit_died_11\n\t"
      "cmpw %%si, 0x2a0(%%ebx)\n\t"
      "pushl %%edi\n\t"
      "je .Lunit_died_9\n\t"
      "call *%[c1b2dd0]\n\t"
      "jmp .Lunit_died_10\n\t"
      ".Lunit_died_6:\n\t"
      "cmpw $0, 0x3d0(%%ebx)\n\t"
      "jg .Lunit_died_7\n\t"
      "pushl $1\n\t"
      "pushl $0x13eb\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b7ac8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_died_7:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fcomps 0x248(%%esi)\n\t"
      "addl $0xc, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "movl 0x1b4(%%ebx), %%eax\n\t"
      "jp .Lunit_died_8\n\t"
      "orl $0x2000, %%eax\n\t"
      "movl %%eax, 0x1b4(%%ebx)\n\t"
      "jmp .Lunit_died_4\n\t"
      ".Lunit_died_8:\n\t"
      "andl $0xffffdfff, %%eax\n\t"
      "movl %%eax, 0x1b4(%%ebx)\n\t"
      "jmp .Lunit_died_4\n\t"
      ".Lunit_died_9:\n\t"
      "call *%[c1aa5c0]\n\t"
      ".Lunit_died_10:\n\t"
      "addl $4, %%esp\n\t"
      ".Lunit_died_11:\n\t"
      "movl %%edi, %%eax\n\t"
      "movw $0, 0x368(%%ebx)\n\t"
      "call *%[c1abbd0]\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "movl 0x2c8(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%esi, %%eax\n\t"
      "je .Lunit_died_12\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1ab990]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl $0xffffffff, 0x2c8(%%edx)\n\t"
      "orl $0xffffffff, %%esi\n\t"
      ".Lunit_died_12:\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1abb20]\n\t"
      "movb 0x23c(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunit_died_13\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ae600]\n\t"
      "addl $8, %%esp\n\t"
      ".Lunit_died_13:\n\t"
      "cmpb $1, 0x23d(%%ebx)\n\t"
      "movw %%si, 0x25e(%%ebx)\n\t"
      "movw %%si, 0x25a(%%ebx)\n\t"
      "movb $0, 0x239(%%ebx)\n\t"
      "jne .Lunit_died_14\n\t"
      "movb $0, 0x23d(%%ebx)\n\t"
      ".Lunit_died_14:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [get] "m"(b1b3060_get), [garb] "m"(b1b3060_garb), [cba550] "m"(b1b3060_cba550), [dget] "m"(b1b3060_dget), [c3cff0] "m"(b1b3060_c3cff0), [c3d330] "m"(b1b3060_c3d330), [gtime] "m"(b1b3060_gtime), [c1adeb0] "m"(b1b3060_c1adeb0), [cfc4b0] "m"(b1b3060_cfc4b0), [c1b2dd0] "m"(b1b3060_c1b2dd0), [assert] "m"(b1b3060_assert), [exitfn] "m"(b1b3060_exitfn), [tag] "m"(b1b3060_tag), [gseed] "m"(b1b3060_gseed), [rmreal] "m"(b1b3060_rmreal), [c1aa5c0] "m"(b1b3060_c1aa5c0), [c1abbd0] "m"(b1b3060_c1abbd0), [c1ab990] "m"(b1b3060_c1ab990), [c1abb20] "m"(b1b3060_c1abb20), [c1ae600] "m"(b1b3060_c1ae600)
      : "memory");
}
#else
#error "unit_died: clang naked draft required"
#endif


/* unit_exit_seat_end (0x1b2dd0) — XBE naked draft (batch 52). */
#if defined(__clang__)
static void *(*const b1b2dd0_get)(int, int) = object_get_and_verify_type;
static void *(*const b1b2dd0_tag)(int, int) = tag_get;
static void *(*const b1b2dd0_elem)(void *, int, int) = tag_block_get_element;
static void *(*const b1b2dd0_onode)(int, short) = object_get_node_matrix;
static short (*const b1b2dd0_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static void (*const b1b2dd0_m3x3v)(void *, float *, float *) = (void (*)(void *, float *, float *))real_matrix3x3_transform_vector;
static char (*const b1b2dd0_c1ad260)(int unit_handle, int16_t anim_state) = FUN_001ad260;
static int (*const b1b2dd0_gtime)(void) = game_time_get;
static void (*const b1b2dd0_c1411c0)(int object_handle) = object_detach_from_parent;
static void (*const b1b2dd0_c143ae0)(int object_handle, float *position, float *forward, float *up) = object_set_position;
static void (*const b1b2dd0_c109850)(float *a, float *b, float *out) = matrix4x3_multiply;
static void (*const b1b2dd0_c13ffc0)(int object_handle, int flag) = object_set_garbage;
static void (*const b1b2dd0_c1aa890)(int vehicle_handle) = unit_update_seat_occupancy;
static void (*const b1b2dd0_c1b2740)(int unit_handle) = unit_select_weapon_after_vehicle_exit;
static short (*const b1b2dd0_c1b0d90)(int unit_handle, char *anim_state) = FUN_001b0d90;
static void * (*const b1b2dd0_c13dfc0)(int object_handle, void *reference) = object_header_block_reference_get;
static void (*const b1b2dd0_c1a1d80)(int unit_handle, int seat_handle) = biped_exit_seat_end;
static void (*const b1b2dd0_c1446a0)(int object_handle) = object_update_children_recursive;

__attribute__((naked, noinline))
void unit_exit_seat_end(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xdc, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .Lunit_exit_seat_end_7\n\t"
      "cmpw $-1, 0x2a0(%%esi)\n\t"
      "je .Lunit_exit_seat_end_7\n\t"
      "pushl %%ebx\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movswl 0x2a0(%%esi), %%ecx\n\t"
      "pushl $0x11c\n\t"
      "pushl %%ecx\n\t"
      "addl $0x2e4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[onode]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl $1\n\t"
      "leal -0xdc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl $0x24, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[markers]\n\t"
      "flds 0x28(%%ebx)\n\t"
      "fsubs -0x7c(%%ebp)\n\t"
      "leal -0x70(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "flds 0x2c(%%ebx)\n\t"
      "leal -0xa4(%%ebp), %%ecx\n\t"
      "fsubs -0x78(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x30(%%ebx)\n\t"
      "fsubs -0x74(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "call *%[m3x3v]\n\t"
      "movl (%%esi), %%edx\n\t"
      "addl $0x40, %%esp\n\t"
      "pushl %%edx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6d6f6465\n\t"
      "call *%[tag]\n\t"
      "pushl $0x9c\n\t"
      "addl $0xb8, %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl -0x24(%%ebp), %%ebx\n\t"
      "leal 0x68(%%eax), %%ecx\n\t"
      "addl $0x28, %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl 0x2d4(%%ebx), %%eax\n\t"
      "addl $0x1c, %%esp\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "jne .Lunit_exit_seat_end_1\n\t"
      "cmpb $0x25, 0x253(%%ebx)\n\t"
      "je .Lunit_exit_seat_end_1\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lunit_exit_seat_end_1\n\t"
      "pushl $0x25\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ad260]\n\t"
      "addl $8, %%esp\n\t"
      ".Lunit_exit_seat_end_1:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl %%eax, 0x2dc(%%esi)\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, 0x2e0(%%esi)\n\t"
      "cmpl %%edi, 0x2d4(%%esi)\n\t"
      "jne .Lunit_exit_seat_end_2\n\t"
      "movl $0xffffffff, 0x2d4(%%esi)\n\t"
      ".Lunit_exit_seat_end_2:\n\t"
      "cmpl %%edi, 0x2d8(%%esi)\n\t"
      "jne .Lunit_exit_seat_end_3\n\t"
      "movl $0xffffffff, 0x2d8(%%esi)\n\t"
      ".Lunit_exit_seat_end_3:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1411c0]\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fadds 0xc(%%esi)\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "fadds 0x10(%%esi)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fadds 0x14(%%esi)\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "call *%[c143ae0]\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[onode]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "leal -0x64(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c109850]\n\t"
      "movl -0x60(%%ebp), %%eax\n\t"
      "movl -0x5c(%%ebp), %%ecx\n\t"
      "leal 0x24(%%esi), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl -0x58(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl -0x48(%%ebp), %%edx\n\t"
      "movl -0x44(%%ebp), %%eax\n\t"
      "leal 0x30(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0x40(%%ebp), %%edx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "call *%[c13ffc0]\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "movw %%ax, 0x2a0(%%esi)\n\t"
      "movb $2, 0x257(%%esi)\n\t"
      "movl 0x2d4(%%ebx), %%ecx\n\t"
      "addl $0x30, %%esp\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "jne .Lunit_exit_seat_end_4\n\t"
      "movl %%eax, 0x2d4(%%ebx)\n\t"
      ".Lunit_exit_seat_end_4:\n\t"
      "cmpl %%edi, 0x2d8(%%ebx)\n\t"
      "jne .Lunit_exit_seat_end_5\n\t"
      "movl %%eax, 0x2d8(%%ebx)\n\t"
      ".Lunit_exit_seat_end_5:\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c1aa890]\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1b2740]\n\t"
      "leal -0x2(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "movb $0x14, -0x2(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c1b0d90]\n\t"
      "leal 0x198(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c13dfc0]\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "addl $0x10, %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "cmpw $0, 0x64(%%esi)\n\t"
      "jne .Lunit_exit_seat_end_6\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a1d80]\n\t"
      "addl $8, %%esp\n\t"
      ".Lunit_exit_seat_end_6:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1446a0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%ebx\n\t"
      ".Lunit_exit_seat_end_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [get] "m"(b1b2dd0_get), [tag] "m"(b1b2dd0_tag), [elem] "m"(b1b2dd0_elem), [onode] "m"(b1b2dd0_onode), [markers] "m"(b1b2dd0_markers), [m3x3v] "m"(b1b2dd0_m3x3v), [c1ad260] "m"(b1b2dd0_c1ad260), [gtime] "m"(b1b2dd0_gtime), [c1411c0] "m"(b1b2dd0_c1411c0), [c143ae0] "m"(b1b2dd0_c143ae0), [c109850] "m"(b1b2dd0_c109850), [c13ffc0] "m"(b1b2dd0_c13ffc0), [c1aa890] "m"(b1b2dd0_c1aa890), [c1b2740] "m"(b1b2dd0_c1b2740), [c1b0d90] "m"(b1b2dd0_c1b0d90), [c13dfc0] "m"(b1b2dd0_c13dfc0), [c1a1d80] "m"(b1b2dd0_c1a1d80), [c1446a0] "m"(b1b2dd0_c1446a0)
      : "memory");
}
#else
#error "unit_exit_seat_end: clang naked draft required"
#endif


/* FUN_001aaf40 (0x1aaf40) — XBE naked draft (batch 59). */
#if defined(__clang__)
static void *(*const b1aaf40_get)(int, int) = object_get_and_verify_type;
static void *(*const b1aaf40_tag)(int, int) = tag_get;
static void * (*const b1aaf40_c18e450)(void) = game_globals_get;
static void *(*const b1aaf40_elem)(void *, int, int) = tag_block_get_element;
static char (*const b1aaf40_ca9570)(int param_1) = FUN_000a9570;
static bool (*const b1aaf40_c3b6f0)(void) = actor_has_unlimited_grenades;
static void (*const b1aaf40_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1aaf40_exitfn)(int) = system_exit;
static short (*const b1aaf40_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static void (*const b1aaf40_opnew)(void *, int, int) = object_placement_data_new;
static void (*const b1aaf40_perp)(float *, float *) = perpendicular3d;
static float (*const b1aaf40_norm)(float *) = normalize3d;
static int (*const b1aaf40_onew)(void *) = object_new;
static void (*const b1aaf40_c144240)(int parent_handle, int child_handle, int parent_node_index) = object_attach_to_parent;

__attribute__((naked, noinline))
void FUN_001aaf40(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xf4, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movsbl 0x2cc(%%esi), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl $0x44\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18e450]\n\t"
      "addl $0x128, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x1c8(%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001aaf40_1\n\t"
      "movb 0x5aa892, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_001aaf40_6\n\t"
      "pushl %%eax\n\t"
      "call *%[ca9570]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001aaf40_6\n\t"
      ".LFUN_001aaf40_1:\n\t"
      "movl 0x1a4(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001aaf40_2\n\t"
      "pushl %%eax\n\t"
      "call *%[c3b6f0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001aaf40_6\n\t"
      ".LFUN_001aaf40_2:\n\t"
      "movb 0x2cc(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jl .LFUN_001aaf40_3\n\t"
      "cmpb $2, %%al\n\t"
      "jl .LFUN_001aaf40_4\n\t"
      ".LFUN_001aaf40_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x1f1e\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b6d78\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001aaf40_4:\n\t"
      "movsbl 0x2cc(%%esi), %%edx\n\t"
      "movb 0x2ce(%%edx,%%esi,1), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jg .LFUN_001aaf40_5\n\t"
      "pushl $1\n\t"
      "pushl $0x1f1f\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b6d38\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001aaf40_5:\n\t"
      "movsbl 0x2cc(%%esi), %%eax\n\t"
      "movb 0x2ce(%%eax,%%esi,1), %%cl\n\t"
      "leal 0x2ce(%%eax,%%esi,1), %%eax\n\t"
      "decb %%cl\n\t"
      "movb %%cl, (%%eax)\n\t"
      ".LFUN_001aaf40_6:\n\t"
      "pushl $1\n\t"
      "leal -0xf4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2b6d2c\n\t"
      "pushl %%edi\n\t"
      "call *%[markers]\n\t"
      "movl 0x40(%%ebx), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "leal -0x88(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[opnew]\n\t"
      "movl -0x84(%%ebp), %%ecx\n\t"
      "orl $2, %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, -0x84(%%ebp)\n\t"
      "call *%[get]\n\t"
      "addl $0x1ec, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x54(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x54(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "call *%[perp]\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "movl -0x94(%%ebp), %%eax\n\t"
      "movl -0x90(%%ebp), %%ecx\n\t"
      "movl -0x8c(%%ebp), %%edx\n\t"
      "movl %%eax, -0x70(%%ebp)\n\t"
      "leal -0x88(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x6c(%%ebp)\n\t"
      "movl %%edx, -0x68(%%ebp)\n\t"
      "call *%[onew]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0x34, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .LFUN_001aaf40_7\n\t"
      "movl -0xf4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c144240]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%ebx, 0x244(%%esi)\n\t"
      "movb $2, 0x23d(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001aaf40_7:\n\t"
      "movb $3, 0x23d(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1aaf40_get), [tag] "m"(b1aaf40_tag), [c18e450] "m"(b1aaf40_c18e450), [elem] "m"(b1aaf40_elem), [ca9570] "m"(b1aaf40_ca9570), [c3b6f0] "m"(b1aaf40_c3b6f0), [assert] "m"(b1aaf40_assert), [exitfn] "m"(b1aaf40_exitfn), [markers] "m"(b1aaf40_markers), [opnew] "m"(b1aaf40_opnew), [perp] "m"(b1aaf40_perp), [norm] "m"(b1aaf40_norm), [onew] "m"(b1aaf40_onew), [c144240] "m"(b1aaf40_c144240)
      : "memory");
}
#else
#error "FUN_001aaf40: clang naked draft required"
#endif


/* FUN_001abd90 (0x1abd90) — XBE naked draft (batch 54). */
#if defined(__clang__)
static void *(*const b1abd90_get)(int, int) = object_get_and_verify_type;
static void *(*const b1abd90_tag)(int, int) = tag_get;
static void (*const b1abd90_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1abd90_exitfn)(int) = system_exit;
static int (*const b1abd90_c14c8e0)(int *out, int object_handle) = FUN_0014c8e0;
static vector3_t * (*const b1abd90_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static float *(*const b1abd90_vsca)(float *, float *, float, float *) = vector3d_scale_add;
static char (*const b1abd90_c14cb00)(int param_1, void *param_2, void *param_3, void *param_4, int16_t *param_5) = FUN_0014cb00;
static void (*const b1abd90_c10a1c0)(float *matrix, float *in_plane, float *out_plane) = FUN_0010a1c0;
static void (*const b1abd90_c994d0)(float *plane_in, float *plane_out) = plane_negate;
static void (*const b1abd90_c136750)(void *damage_params, int tag_index) = damage_data_new;
static void (*const b1abd90_c137d20)(void *damage_params, int object_handle, short node_index, short region_index, short permutation_index, unsigned int flags) = object_cause_damage;

__attribute__((naked, noinline))
void FUN_001abd90(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x4bc, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movb 0x239(%%esi), %%cl\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpb $4, %%cl\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jne .LFUN_001abd90_8\n\t"
      "movl 0xcc(%%esi), %%edx\n\t"
      "movl $0xffffffff, %%ecx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "je .LFUN_001abd90_8\n\t"
      "cmpl %%ecx, 0x294(%%eax)\n\t"
      "je .LFUN_001abd90_8\n\t"
      "movb 0x23a(%%esi), %%cl\n\t"
      "pushl %%ebx\n\t"
      "xorb %%bl, %%bl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_001abd90_5\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "jl .LFUN_001abd90_1\n\t"
      "pushl $1\n\t"
      "pushl $0x22e6\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001abd90_1:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "incw %%ax\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "movw $8, 0x5a8c80(,%%ecx,2)\n\t"
      "movl 0xcc(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x9c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c14c8e0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001abd90_3\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1412f0]\n\t"
      "flds 0x24(%%esi)\n\t"
      "fmuls 0x2549d4\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0xbf000000\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "flds 0x28(%%esi)\n\t"
      "pushl %%eax\n\t"
      "fmuls 0x2549d4\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fmuls 0x2549d4\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[vsca]\n\t"
      "leal -0x4bc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x9c(%%ebp), %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "call *%[c14cb00]\n\t"
      "addl $0x2c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001abd90_3\n\t"
      "movl -0x4b4(%%ebp), %%ecx\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[vsca]\n\t"
      "movswl -0x4bc(%%ebp), %%eax\n\t"
      "movl -0x4b0(%%ebp), %%edx\n\t"
      "imull $0x34, %%eax, %%eax\n\t"
      "movl -0x90(%%ebp), %%ebx\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "addl %%ebx, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c10a1c0]\n\t"
      "movl -0x4a8(%%ebp), %%eax\n\t"
      "addl $0x1c, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jns .LFUN_001abd90_2\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c994d0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001abd90_2:\n\t"
      "movb $1, %%bl\n\t"
      ".LFUN_001abd90_3:\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "jg .LFUN_001abd90_4\n\t"
      "pushl $1\n\t"
      "pushl $0x22fe\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001abd90_4:\n\t"
      "decw 0x4761d8\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      ".LFUN_001abd90_5:\n\t"
      "movl 0x294(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x8c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c136750]\n\t"
      "movw 0x68(%%esi), %%dx\n\t"
      "movl 0x1c8(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "movl %%edi, -0x80(%%ebp)\n\t"
      "movw %%dx, -0x7c(%%ebp)\n\t"
      "movl %%eax, -0x84(%%ebp)\n\t"
      "movl $0x3d088889, -0x4c(%%ebp)\n\t"
      "je .LFUN_001abd90_6\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movl -0x88(%%ebp), %%ebx\n\t"
      "movl %%ecx, -0x60(%%ebp)\n\t"
      "movl %%ecx, -0x6c(%%ebp)\n\t"
      "movl %%edx, -0x5c(%%ebp)\n\t"
      "movl %%edx, -0x68(%%ebp)\n\t"
      "leal 0x24(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%eax, -0x64(%%ebp)\n\t"
      "movl %%eax, -0x70(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x58(%%ebp)\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0x4bc(%%ebp), %%edx\n\t"
      "movl %%eax, -0x54(%%ebp)\n\t"
      "movl -0x4a2(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "movl %%ecx, -0x50(%%ebp)\n\t"
      "movl -0x4ba(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "orl $2, %%ebx\n\t"
      "pushl %%eax\n\t"
      "leal -0x8c(%%ebp), %%ecx\n\t"
      "movl %%ebx, -0x88(%%ebp)\n\t"
      "movb $0xa, 0x23a(%%esi)\n\t"
      "pushl %%ecx\n\t"
      "jmp .LFUN_001abd90_7\n\t"
      ".LFUN_001abd90_6:\n\t"
      "movl 0xcc(%%esi), %%edx\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "leal -0x8c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      ".LFUN_001abd90_7:\n\t"
      "call *%[c137d20]\n\t"
      "movb 0x23a(%%esi), %%al\n\t"
      "addl $0x18, %%esp\n\t"
      "decb %%al\n\t"
      "movb %%al, 0x23a(%%esi)\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001abd90_8:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [get] "m"(b1abd90_get), [tag] "m"(b1abd90_tag), [assert] "m"(b1abd90_assert), [exitfn] "m"(b1abd90_exitfn), [c14c8e0] "m"(b1abd90_c14c8e0), [c1412f0] "m"(b1abd90_c1412f0), [vsca] "m"(b1abd90_vsca), [c14cb00] "m"(b1abd90_c14cb00), [c10a1c0] "m"(b1abd90_c10a1c0), [c994d0] "m"(b1abd90_c994d0), [c136750] "m"(b1abd90_c136750), [c137d20] "m"(b1abd90_c137d20)
      : "memory");
}
#else
#error "FUN_001abd90: clang naked draft required"
#endif


/* unit_adjust_plan_overlap (0x1acb70) — XBE naked draft (batch 55). */
#if defined(__clang__)
static void (*const b1acb70_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1acb70_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void unit_adjust_plan_overlap(void *plan_a_ptr __attribute__((unused)), void *plan_b_ptr __attribute__((unused)), int dummy __attribute__((unused)), float delta_time __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpb $0, (%%ecx)\n\t"
      "jne .Lunit_adjust_plan_overlap_11\n\t"
      "cmpb $0, (%%esi)\n\t"
      "jne .Lunit_adjust_plan_overlap_11\n\t"
      "flds 0x1c(%%ecx)\n\t"
      "fadds 0x14(%%ecx)\n\t"
      "fadds 0x10(%%ecx)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fadds 0x14(%%esi)\n\t"
      "fadds 0x10(%%esi)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x10(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_adjust_plan_overlap_1\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lunit_adjust_plan_overlap_1\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl %%ecx, %%esi\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "jmp .Lunit_adjust_plan_overlap_2\n\t"
      ".Lunit_adjust_plan_overlap_1:\n\t"
      "flds 0x10(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_adjust_plan_overlap_11\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lunit_adjust_plan_overlap_11\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fsubs -0x8(%%ebp)\n\t"
      ".Lunit_adjust_plan_overlap_2:\n\t"
      "testl %%esi, %%esi\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "je .Lunit_adjust_plan_overlap_11\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lunit_adjust_plan_overlap_3\n\t"
      "pushl $1\n\t"
      "pushl $0x8ae\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b70ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_adjust_plan_overlap_3:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fadds 0x14(%%esi)\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "flds 0x10(%%esi)\n\t"
      "fmuls 0xc(%%esi)\n\t"
      "fadds 0x8(%%esi)\n\t"
      "fabs\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fchs\n\t"
      "fmulp %%st(1)\n\t"
      "fxch %%st(1)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fmuls 0x2533d8\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .Lunit_adjust_plan_overlap_4\n\t"
      "pushl $1\n\t"
      "pushl $0x8c4\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b6fa4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_adjust_plan_overlap_4:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fsqrt\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "flds 0x10(%%esi)\n\t"
      "fcomps 0x1c(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_adjust_plan_overlap_5\n\t"
      "flds 0x1c(%%esi)\n\t"
      "jmp .Lunit_adjust_plan_overlap_6\n\t"
      ".Lunit_adjust_plan_overlap_5:\n\t"
      "flds 0x10(%%esi)\n\t"
      ".Lunit_adjust_plan_overlap_6:\n\t"
      "fld %%st(1)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_adjust_plan_overlap_8\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x10(%%esi)\n\t"
      "fcomps 0x1c(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_adjust_plan_overlap_7\n\t"
      "flds 0x1c(%%esi)\n\t"
      "jmp .Lunit_adjust_plan_overlap_8\n\t"
      ".Lunit_adjust_plan_overlap_7:\n\t"
      "flds 0x10(%%esi)\n\t"
      ".Lunit_adjust_plan_overlap_8:\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_adjust_plan_overlap_10\n\t"
      "flds 0x10(%%esi)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fmuls 0xc(%%esi)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%eax, 0x10(%%esi)\n\t"
      "fadds 0x8(%%esi)\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fsub %%st(2), %%st(0)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fstps 0x1c(%%esi)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0xc(%%esi)\n\t"
      "fld %%st(1)\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fstps 0x14(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lunit_adjust_plan_overlap_9\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .Lunit_adjust_plan_overlap_11\n\t"
      ".Lunit_adjust_plan_overlap_9:\n\t"
      "pushl $1\n\t"
      "pushl $0x8d8\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b7070\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lunit_adjust_plan_overlap_10:\n\t"
      "fstp %%st(0)\n\t"
      ".Lunit_adjust_plan_overlap_11:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [assert] "m"(b1acb70_assert), [exitfn] "m"(b1acb70_exitfn)
      : "memory");
}
#else
#error "unit_adjust_plan_overlap: clang naked draft required"
#endif


/* unit_update_running_blind (0x1af340) — XBE naked draft (batch 52). */
#if defined(__clang__)
static void *(*const b1af340_get)(int, int) = object_get_and_verify_type;
static char (*const b1af340_c3ce40)(int actor_handle, float *vector_out) = actor_get_running_blind_vector;
static bool (*const b1af340_c21fb0)(float *v) = valid_real_normal3d;
static char * (*const b1af340_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b1af340_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1af340_exitfn)(int) = system_exit;
static int *(*const b1af340_gseed)(void) = get_global_random_seed_address;
static float (*const b1af340_rrange)(int *, float, float) = random_real_range;
static void (*const b1af340_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;
static bool (*const b1af340_c84a70)(float *a, float *b) = valid_real_normal3d_perpendicular;

__attribute__((naked, noinline))
void unit_update_running_blind(int unit_handle __attribute__((unused)), float *run_vector __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x1a4(%%edi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lunit_update_running_blind_1\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c3ce40]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_update_running_blind_1\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lunit_update_running_blind_2\n\t"
      ".Lunit_update_running_blind_1:\n\t"
      "movl 0x31fc3c, %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "movl %%esi, %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      ".Lunit_update_running_blind_2:\n\t"
      "pushl %%esi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunit_update_running_blind_3\n\t"
      "flds 0x8(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x253e\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x257064\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_update_running_blind_3:\n\t"
      "testb %%bl, %%bl\n\t"
      "flds 0x2533c8\n\t"
      "movl $0x3f800000, -0x4(%%ebp)\n\t"
      "je .Lunit_update_running_blind_6\n\t"
      "flds 0x254a58\n\t"
      "fsubs 0x3c4(%%edi)\n\t"
      "flds 0x3c4(%%edi)\n\t"
      "fadds 0x254a58\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fmuls 0x2b7258\n\t"
      "flds 0x2533c8\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_update_running_blind_4\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jmp .Lunit_update_running_blind_5\n\t"
      ".Lunit_update_running_blind_4:\n\t"
      "fstp %%st(0)\n\t"
      ".Lunit_update_running_blind_5:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x2b7258\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_update_running_blind_6\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x8(%%ebp)\n\t"
      ".Lunit_update_running_blind_6:\n\t"
      "flds 0x2b7254\n\t"
      "fsubs 0x3c8(%%edi)\n\t"
      "flds 0x3c8(%%edi)\n\t"
      "fadds 0x2b7254\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fmuls 0x2b7250\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_update_running_blind_7\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jmp .Lunit_update_running_blind_8\n\t"
      ".Lunit_update_running_blind_7:\n\t"
      "fstp %%st(0)\n\t"
      ".Lunit_update_running_blind_8:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x2b7250\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fcoms -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_update_running_blind_9\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x8(%%ebp)\n\t"
      ".Lunit_update_running_blind_9:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lunit_update_running_blind_12\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lunit_update_running_blind_10\n\t"
      "flds 0x2b724c\n\t"
      "jmp .Lunit_update_running_blind_16\n\t"
      ".Lunit_update_running_blind_10:\n\t"
      "flds 0x2533c8\n\t"
      "fcomps -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_update_running_blind_11\n\t"
      "flds -0x4(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x2b7248\n\t"
      "fstps (%%esp)\n\t"
      "pushl $0xbcab92a6\n\t"
      "jmp .Lunit_update_running_blind_15\n\t"
      ".Lunit_update_running_blind_11:\n\t"
      "flds 0x2533c8\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x2b7248\n\t"
      "fstps (%%esp)\n\t"
      "pushl $0xbcab92a6\n\t"
      "jmp .Lunit_update_running_blind_15\n\t"
      ".Lunit_update_running_blind_12:\n\t"
      "fcoms 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lunit_update_running_blind_13\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2b7248\n\t"
      "jmp .Lunit_update_running_blind_16\n\t"
      ".Lunit_update_running_blind_13:\n\t"
      "flds 0x2533c8\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lunit_update_running_blind_14\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".Lunit_update_running_blind_14:\n\t"
      "fmuls 0x2b724c\n\t"
      "pushl $0x3cab92a6\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      ".Lunit_update_running_blind_15:\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lunit_update_running_blind_16:\n\t"
      "fadds 0x3c8(%%edi)\n\t"
      "fsts 0x3c8(%%edi)\n\t"
      "fadds 0x3c4(%%edi)\n\t"
      "fcoms 0x26e280\n\t"
      "fsts 0x3c4(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lunit_update_running_blind_17\n\t"
      "fadds 0x255a54\n\t"
      "fstps 0x3c4(%%edi)\n\t"
      "jmp .Lunit_update_running_blind_19\n\t"
      ".Lunit_update_running_blind_17:\n\t"
      "fcoms 0x256980\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_update_running_blind_18\n\t"
      "fsubs 0x255a54\n\t"
      "fstps 0x3c4(%%edi)\n\t"
      "jmp .Lunit_update_running_blind_19\n\t"
      ".Lunit_update_running_blind_18:\n\t"
      "fstp %%st(0)\n\t"
      ".Lunit_update_running_blind_19:\n\t"
      "flds 0x3c4(%%edi)\n\t"
      "subl $8, %%esp\n\t"
      "fcos\n\t"
      "movl 0x31fc44, %%edx\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0x3c4(%%edi)\n\t"
      "fsin\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[rots]\n\t"
      "pushl %%esi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "jne .Lunit_update_running_blind_20\n\t"
      "flds 0x8(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x2585\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x257064\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_update_running_blind_20:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "pushl %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "leal 0x1d4(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c21fb0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_update_running_blind_21\n\t"
      "leal 0x1e0(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_update_running_blind_21\n\t"
      "leal 0x204(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_update_running_blind_21\n\t"
      "leal 0x30(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x24(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c84a70]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_update_running_blind_21\n\t"
      "leal 0x1ec(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_update_running_blind_21\n\t"
      "addl $0x210, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_update_running_blind_21\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".Lunit_update_running_blind_21:\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [get] "m"(b1af340_get), [c3ce40] "m"(b1af340_c3ce40), [c21fb0] "m"(b1af340_c21fb0), [c8d9d0] "m"(b1af340_c8d9d0), [assert] "m"(b1af340_assert), [exitfn] "m"(b1af340_exitfn), [gseed] "m"(b1af340_gseed), [rrange] "m"(b1af340_rrange), [rots] "m"(b1af340_rots), [c84a70] "m"(b1af340_c84a70)
      : "memory");
}
#else
#error "unit_update_running_blind: clang naked draft required"
#endif


/* FUN_001acd70 (0x1acd70) — XBE naked draft (batch 55). */
#if defined(__clang__)
static void *(*const b1acd70_get)(int, int) = object_get_and_verify_type;
static void *(*const b1acd70_tag)(int, int) = tag_get;
static void *(*const b1acd70_elem)(void *, int, int) = tag_block_get_element;
static int (*const b1acd70_c1dd801)(const char *a, const char *b) = crt_stricmp;
static int (*const b1acd70_c8dcb0)(const char *s1, const char *s2) = csstrcmp;

__attribute__((naked, noinline))
char FUN_001acd70(int unit_handle __attribute__((unused)), const char *seat_label __attribute__((unused)), const char *weapon_name __attribute__((unused)), char apply_state __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl 0x44(%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x616e7472\n\t"
      "call *%[tag]\n\t"
      "leal 0xc(%%eax), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "xorb %%cl, %%cl\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movb %%cl, -0x1(%%ebp)\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "movl %%esi, -0x1c(%%ebp)\n\t"
      "jle .LFUN_001acd70_20\n\t"
      "pushl %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "pushl %%edi\n\t"
      ".LFUN_001acd70_1:\n\t"
      "pushl $0x64\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%edi, -0x18(%%ebp)\n\t"
      "je .LFUN_001acd70_2\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001acd70_19\n\t"
      ".LFUN_001acd70_2:\n\t"
      "movl 0x58(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "leal 0x58(%%edi), %%ecx\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jle .LFUN_001acd70_19\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001acd70_3:\n\t"
      "pushl $0xbc\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "leal 0xb0(%%eax), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "jle .LFUN_001acd70_18\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_001acd70_4:\n\t"
      "pushl $0x3c\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "je .LFUN_001acd70_6\n\t"
      "pushl $0x2b6e68\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8dcb0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001acd70_5\n\t"
      "cmpb $0, (%%edi)\n\t"
      "je .LFUN_001acd70_6\n\t"
      ".LFUN_001acd70_5:\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001acd70_6\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl (%%esi), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_001acd70_4\n\t"
      "jmp .LFUN_001acd70_18\n\t"
      ".LFUN_001acd70_6:\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001acd70_17\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl 0x40(%%eax), %%ecx\n\t"
      "cmpl $2, %%ecx\n\t"
      "jle .LFUN_001acd70_7\n\t"
      "movl 0x44(%%eax), %%edx\n\t"
      "movswl 0x4(%%edx), %%edx\n\t"
      "cmpl $-1, %%edx\n\t"
      "jne .LFUN_001acd70_10\n\t"
      ".LFUN_001acd70_7:\n\t"
      "cmpl $3, %%ecx\n\t"
      "jle .LFUN_001acd70_8\n\t"
      "movl 0x44(%%eax), %%edx\n\t"
      "movswl 0x6(%%edx), %%edx\n\t"
      "cmpl $-1, %%edx\n\t"
      "jne .LFUN_001acd70_10\n\t"
      ".LFUN_001acd70_8:\n\t"
      "cmpl $4, %%ecx\n\t"
      "jle .LFUN_001acd70_9\n\t"
      "movl 0x44(%%eax), %%eax\n\t"
      "movswl 0x8(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_001acd70_10\n\t"
      ".LFUN_001acd70_9:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jmp .LFUN_001acd70_11\n\t"
      ".LFUN_001acd70_10:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_001acd70_11:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "cmpb $0x1c, 0x253(%%eax)\n\t"
      "je .LFUN_001acd70_12\n\t"
      "movb $0xff, 0x253(%%eax)\n\t"
      ".LFUN_001acd70_12:\n\t"
      "movb -0x10(%%ebp), %%cl\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "movb %%cl, 0x250(%%eax)\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_001acd70_13:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movswl %%si, %%edx\n\t"
      "movl 0x32e484(,%%edx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1dd801]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001acd70_14\n\t"
      "incl %%esi\n\t"
      "cmpw $6, %%si\n\t"
      "jl .LFUN_001acd70_13\n\t"
      "jmp .LFUN_001acd70_15\n\t"
      ".LFUN_001acd70_14:\n\t"
      "movl %%esi, %%ebx\n\t"
      ".LFUN_001acd70_15:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movb -0x8(%%ebp), %%cl\n\t"
      "movb -0xc(%%ebp), %%dl\n\t"
      "movb %%cl, 0x252(%%eax)\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "movb %%bl, 0x257(%%eax)\n\t"
      "movb %%dl, 0x251(%%eax)\n\t"
      "je .LFUN_001acd70_16\n\t"
      "orb $2, 0x248(%%eax)\n\t"
      "jmp .LFUN_001acd70_17\n\t"
      ".LFUN_001acd70_16:\n\t"
      "andb $0xfd, 0x248(%%eax)\n\t"
      ".LFUN_001acd70_17:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_001acd70_18:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl 0x58(%%ecx), %%edx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "addl $0x58, %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .LFUN_001acd70_3\n\t"
      "movl -0x1c(%%ebp), %%esi\n\t"
      ".LFUN_001acd70_19:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl (%%esi), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_001acd70_1\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001acd70_20:\n\t"
      "movb %%cl, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [get] "m"(b1acd70_get), [tag] "m"(b1acd70_tag), [elem] "m"(b1acd70_elem), [c1dd801] "m"(b1acd70_c1dd801), [c8dcb0] "m"(b1acd70_c8dcb0)
      : "memory");
}
#else
#error "FUN_001acd70: clang naked draft required"
#endif


/* FUN_001ae490 (0x1ae490) — XBE naked draft (batch 59). */
#if defined(__clang__)
static void *(*const b1ae490_get)(int, int) = object_get_and_verify_type;
static void (*const b1ae490_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1ae490_exitfn)(int) = system_exit;
static int (*const b1ae490_c1ae290)(int unit_handle) = unit_get_seat_label;
static char * (*const b1ae490_cfae80)(int weapon_handle) = weapon_get_label;
static char (*const b1ae490_c1acd70)(int unit_handle, const char *seat_label, const char *weapon_name, char apply_state) = FUN_001acd70;
static bool (*const b1ae490_ca8b30)(int unit_handle, int weapon_handle) = game_engine_allow_weapon_pick_up;
static int (*const b1ae490_cfb090)(int weapon_handle) = weapon_must_be_readied;

__attribute__((naked, noinline))
int16_t FUN_001ae490(int unit_handle __attribute__((unused)), int16_t current_index __attribute__((unused)), int16_t direction __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl $3\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movl $0xffffffff, -0x8(%%ebp)\n\t"
      "jne .LFUN_001ae490_1\n\t"
      "movl $0, 0x8(%%ebp)\n\t"
      "jmp .LFUN_001ae490_3\n\t"
      ".LFUN_001ae490_1:\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_001ae490_2\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .LFUN_001ae490_3\n\t"
      ".LFUN_001ae490_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x1e40\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b71c8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ae490_3:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "pushl %%edi\n\t"
      ".LFUN_001ae490_4:\n\t"
      "movswl -0x4(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl 0x2a8(%%ecx,%%eax,4), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "je .LFUN_001ae490_8\n\t"
      "pushl $3\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "pushl $4\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c1ae290]\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[cfae80]\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c1acd70]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001ae490_8\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[ca8b30]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001ae490_8\n\t"
      "cmpw $0, 0xc(%%ebp)\n\t"
      "jne .LFUN_001ae490_5\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "cmpw $-1, %%si\n\t"
      "je .LFUN_001ae490_5\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movswl %%si, %%edx\n\t"
      "movl 0x2b8(%%eax,%%edx,4), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "cmpl 0x2b8(%%eax,%%edx,4), %%ecx\n\t"
      "jge .LFUN_001ae490_7\n\t"
      "jmp .LFUN_001ae490_6\n\t"
      ".LFUN_001ae490_5:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      ".LFUN_001ae490_6:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%ecx, %%esi\n\t"
      ".LFUN_001ae490_7:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl 0x2a8(%%eax,%%edx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[cfb090]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001ae490_14\n\t"
      "movw -0x4(%%ebp), %%cx\n\t"
      "cmpw 0x8(%%ebp), %%cx\n\t"
      "jne .LFUN_001ae490_13\n\t"
      ".LFUN_001ae490_8:\n\t"
      "cmpw $0, 0xc(%%ebp)\n\t"
      "jge .LFUN_001ae490_10\n\t"
      "cmpw $0, -0x4(%%ebp)\n\t"
      "jne .LFUN_001ae490_9\n\t"
      "movl $3, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001ae490_12\n\t"
      ".LFUN_001ae490_9:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "decl %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001ae490_12\n\t"
      ".LFUN_001ae490_10:\n\t"
      "cmpw $3, -0x4(%%ebp)\n\t"
      "jne .LFUN_001ae490_11\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001ae490_12\n\t"
      ".LFUN_001ae490_11:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".LFUN_001ae490_12:\n\t"
      "movw 0x8(%%ebp), %%cx\n\t"
      "cmpw %%cx, -0x4(%%ebp)\n\t"
      "jne .LFUN_001ae490_4\n\t"
      ".LFUN_001ae490_13:\n\t"
      "movw -0x8(%%ebp), %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001ae490_14:\n\t"
      "popl %%edi\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1ae490_get), [assert] "m"(b1ae490_assert), [exitfn] "m"(b1ae490_exitfn), [c1ae290] "m"(b1ae490_c1ae290), [cfae80] "m"(b1ae490_cfae80), [c1acd70] "m"(b1ae490_c1acd70), [ca8b30] "m"(b1ae490_ca8b30), [cfb090] "m"(b1ae490_cfb090)
      : "memory");
}
#else
#error "FUN_001ae490: clang naked draft required"
#endif


/* FUN_001b04b0 (0x1b04b0) — XBE naked draft (batch 60). */
#if defined(__clang__)
static void *(*const b1b04b0_get)(int, int) = object_get_and_verify_type;
static void *(*const b1b04b0_tag)(int, int) = tag_get;
static void *(*const b1b04b0_elem)(void *, int, int) = tag_block_get_element;
static char (*const b1b04b0_c1a8850)(void *anim_state) = FUN_001a8850;
static void (*const b1b04b0_c1414e0)(int param_1, int param_2, int param_3, int param_4, int param_5) = FUN_001414e0;
static char (*const b1b04b0_c1a87f0)(void *anim_state) = FUN_001a87f0;
static int (*const b1b04b0_c1adeb0)(int unit_handle, int16_t weapon_index) = unit_get_weapon;

__attribute__((naked, noinline))
void FUN_001b04b0(int unit_handle __attribute__((unused)), int node_matrices __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0x17c(%%eax), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $8, %%ch\n\t"
      "jne .LFUN_001b04b0_6\n\t"
      "cmpb $0xff, 0x250(%%esi)\n\t"
      "je .LFUN_001b04b0_6\n\t"
      "movl 0x44(%%eax), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x616e7472\n\t"
      "call *%[tag]\n\t"
      "movsbl 0x250(%%esi), %%edx\n\t"
      "pushl $0x64\n\t"
      "pushl %%edx\n\t"
      "addl $0xc, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movsbl 0x251(%%esi), %%eax\n\t"
      "pushl $0xbc\n\t"
      "pushl %%eax\n\t"
      "leal 0x58(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "addl $0x20, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001b04b0_2\n\t"
      "leal 0x248(%%esi), %%ecx\n\t"
      "call *%[c1a8850]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b04b0_2\n\t"
      "movl 0x4c(%%ebx), %%ecx\n\t"
      "addl $0x4c, %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jle .LFUN_001b04b0_2\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_001b04b0_1:\n\t"
      "pushl $0x40\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0xcc(%%esi), %%edx\n\t"
      "leal 0x20(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c1414e0]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "addl $0x20, %%esp\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_001b04b0_1\n\t"
      ".LFUN_001b04b0_2:\n\t"
      "cmpw $-1, 0x2a2(%%esi)\n\t"
      "je .LFUN_001b04b0_5\n\t"
      "addl $0x248, %%esi\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "call *%[c1a87f0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b04b0_5\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "movl 0xa4(%%ebx), %%eax\n\t"
      "addl $0xa4, %%ebx\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jle .LFUN_001b04b0_4\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001b04b0_3:\n\t"
      "pushl $0x40\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x20(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2a2(%%eax), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1adeb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1414e0]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_001b04b0_3\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      ".LFUN_001b04b0_4:\n\t"
      "andb $0xfe, (%%esi)\n\t"
      ".LFUN_001b04b0_5:\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001b04b0_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1b04b0_get), [tag] "m"(b1b04b0_tag), [elem] "m"(b1b04b0_elem), [c1a8850] "m"(b1b04b0_c1a8850), [c1414e0] "m"(b1b04b0_c1414e0), [c1a87f0] "m"(b1b04b0_c1a87f0), [c1adeb0] "m"(b1b04b0_c1adeb0)
      : "memory");
}
#else
#error "FUN_001b04b0: clang naked draft required"
#endif


/* -----------------------------------------------------------------------
 * FUN_00122a50 — animation 1D overlay frame apply
 *
 * For animation type 1 (overlay), interpolates rotation, translation, and
 * scale between the current frame and next frame for each node.  The result
 * is blended into the node output buffer using blend_weight.
 *
 * Disassembly range: 0x122a50 – 0x122e43.
 * Source: c:\halo\SOURCE\models\model_animations.c
 * ----------------------------------------------------------------------- */
void FUN_00122a50(int animation, float frame_pos, float blend_weight,
                  int node_output)
{
  short *data;
  short *next_data;
  unsigned short frame_count_u;
  int compressed;
  short *data_cursor;
  short *next_cursor;
  int frame_index;
  int next_frame_index;
  int node_output_ptr;
  float weight_complement;
  float frac;
  float floor_val;
  int frame_idx_int;
  int rotation_counter;
  int translation_counter;
  int scale_counter;
  unsigned int node_idx;
  unsigned int has_translation;
  unsigned int has_rotation;
  unsigned int has_scale;
  float rot_a[4];
  float rot_b[4];
  float interp_rot[4];
  float interp_trans[3];
  float interp_scale;
  int temp_scale_a;
  int temp_scale_b;

  weight_complement = *(float *)0x2533c8 - blend_weight;
  frac = (float)x87_fmod(frame_pos, 1.0);
  floor_val = (float)floor((double)frame_pos);
  frame_idx_int = (int)floor_val;

  if (frame_pos < *(float *)0x2533c0 ||
      frame_pos > (float)(int)*(short *)(animation + 0x22)) {
    error(2,
      "### ERROR animation frame index out of bounds B(%f,%x) -- tell Bernie!!",
      (double)frame_pos, *(int *)&frame_pos);
  }

  frame_count_u = *(unsigned short *)(animation + 0x22);
  if ((short)frame_idx_int >= (short)frame_count_u) {
    frame_idx_int = (int)(unsigned short)(frame_count_u - 1);
    frac = 1.0f;
    frame_pos = (float)(int)(short)frame_idx_int;
  }

  if (*(short *)(animation + 0x20) == 1) {
    if ((*(unsigned char *)(animation + 0x3a) & 1) == 0 ||
        (*(char *)0x322600 == '\0' &&
         *(int *)(animation + 0x88) != 0)) {
      compressed = 0;
    } else {
      compressed = 1;
    }

    frame_index = (int)(short)frame_idx_int;
    if (frame_index == (int)(short)frame_count_u - 1) {
      next_frame_index = 0;
    } else {
      next_frame_index = frame_index + 1;
    }

    data = (short *)FUN_00120500((void *)animation, (short)frame_idx_int);
    next_data = (short *)FUN_00120500((void *)animation,
                                      (short)next_frame_index);

    rotation_counter = 0;
    translation_counter = 0;
    scale_counter = 0;
    node_idx = 0;
    if (0 < *(short *)(animation + 0x2c)) {
      do {
        node_output_ptr = (short)node_idx * 0x20 + node_output;
        if ((node_idx & 0x1f) == 0) {
          int bit_idx = (int)(short)((short)node_idx >> 5);
          has_translation = *(unsigned int *)(animation + 0x5c + bit_idx * 4);
          has_rotation = *(unsigned int *)(animation + 0x6c + bit_idx * 4);
          has_scale = *(unsigned int *)(animation + 0x7c + bit_idx * 4);
        }

        data_cursor = data;
        next_cursor = next_data;

        if ((has_rotation & 1) != 0) {
          if (compressed) {
            FUN_00121330((void *)animation, (float)frame_index,
                         (unsigned short)rotation_counter,
                         (short)node_idx, interp_rot);
            rotation_counter = rotation_counter + 1;
          } else {
            rot_a[0] = (float)(int)data[0] * *(float *)0x290dd8;
            rot_a[1] = (float)(int)data[1] * *(float *)0x290dd8;
            rot_a[2] = (float)(int)data[2] * *(float *)0x290dd8;
            rot_a[3] = (float)(int)data[3] * *(float *)0x290dd8;
            rot_b[0] = (float)(int)next_data[0] * *(float *)0x290dd8;
            rot_b[1] = (float)(int)next_data[1] * *(float *)0x290dd8;
            rot_b[2] = (float)(int)next_data[2] * *(float *)0x290dd8;
            rot_b[3] = (float)(int)next_data[3] * *(float *)0x290dd8;
            data = data + 4;
            next_data = next_data + 4;
            quaternions_interpolate_and_normalize(rot_a, rot_b, frac,
                                                  interp_rot);
          }
          quaternions_interpolate_and_normalize(*(float **)0x31fc5c,
                                                interp_rot, blend_weight,
                                                interp_rot);
          FUN_0010b9c0(interp_rot, (float *)node_output_ptr,
                       (float *)node_output_ptr);
          data_cursor = data;
        }
        has_rotation = has_rotation >> 1;
        next_cursor = next_data;
        data = data_cursor;

        if ((has_translation & 1) != 0) {
          if (compressed) {
            animation_get_node_orientations(
              (void *)animation, frame_pos,
              (unsigned short)translation_counter,
              (short)node_idx, interp_trans);
            translation_counter = translation_counter + 1;
          } else {
            points_interpolate((float *)data_cursor, (float *)next_cursor,
                               frac, interp_trans);
            data = data_cursor + 6;
            next_data = next_cursor + 6;
          }
          *(float *)(node_output_ptr + 0x10) =
            interp_trans[0] * blend_weight +
            *(float *)(node_output_ptr + 0x10);
          *(float *)(node_output_ptr + 0x14) =
            interp_trans[1] * blend_weight +
            *(float *)(node_output_ptr + 0x14);
          *(float *)(node_output_ptr + 0x18) =
            interp_trans[2] * blend_weight +
            *(float *)(node_output_ptr + 0x18);
        }
        has_translation = has_translation >> 1;

        if ((has_scale & 1) != 0) {
          if (compressed) {
            overlay_animation_apply_continuous_scaled(
              (void *)animation, frame_pos,
              (unsigned short)scale_counter,
              (short)node_idx, &interp_scale);
            scale_counter = scale_counter + 1;
          } else {
            temp_scale_a = *(int *)data;
            temp_scale_b = *(int *)next_data;
            data = data + 2;
            next_data = next_data + 2;
            scalars_interpolate(*(float *)&temp_scale_a,
                                *(float *)&temp_scale_b,
                                frac, &interp_scale);
          }
          *(float *)(node_output_ptr + 0x1c) =
            (interp_scale * blend_weight + weight_complement) *
            *(float *)(node_output_ptr + 0x1c);
        }
        has_scale = has_scale >> 1;
        node_idx = node_idx + 1;
      } while ((short)node_idx < *(short *)(animation + 0x2c));
    }

    if (!compressed) {
      int check_base;
      check_base = (int)FUN_00120500((void *)animation,
                                      (short)frame_idx_int);
      if ((int)data - check_base !=
          (int)*(short *)(animation + 0x24)) {
        display_assert(
          "compressed || ((byte *)data-(byte *)animation_get_frame_data"
          "(animation, frame_index)==animation->frame_size)",
          "c:\\halo\\SOURCE\\models\\model_animations.c", 0x334, 1);
        system_exit(-1);
      }
      check_base = (int)FUN_00120500((void *)animation,
                                      (short)next_frame_index);
      if ((int)next_data - check_base !=
          (int)*(short *)(animation + 0x24)) {
        display_assert(
          "compressed || ((byte *)next_data-(byte *)"
          "animation_get_frame_data(animation, next_frame_index)"
          "==animation->frame_size)",
          "c:\\halo\\SOURCE\\models\\model_animations.c", 0x335, 1);
        system_exit(-1);
      }
    }
  }
}

/* FUN_00122e50 (0x122e50) — XBE naked draft (batch 48). */
#if defined(__clang__)
static char (*const b122e50_c120620)(int animation) = FUN_00120620;
static void (*const b122e50_ftol)(void) = FUN_001d9068;
static void (*const b122e50_c1daf7e)(void) = FUN_001daf7e;
static char * (*const b122e50_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b122e50_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b122e50_exitfn)(int) = system_exit;
static void * (*const b122e50_c120500)(void *animation, short frame_index) = FUN_00120500;
static void (*const b122e50_c121330)(void *animation, float frame, unsigned short rotation_count, short node_index, void *out_rotation) = FUN_00121330;
static void (*const b122e50_c120810)(short *src, float *dest) = quaternion_decompress_8byte;
static void (*const b122e50_c10cb60)(float *q1, float *q2, float t, float *out) = quaternions_interpolate_and_normalize;
static void (*const b122e50_c10b9c0)(float *q1, float *q2, float *out) = FUN_0010b9c0;
static void (*const b122e50_c121640)(void *animation, float frame, unsigned short translation_count, short node_index, void *out_translation) = animation_get_node_orientations;

__attribute__((naked, noinline))
void FUN_00122e50(int animation __attribute__((unused)), float *blend_params __attribute__((unused)), float direction __attribute__((unused)), float throttle __attribute__((unused)), int node_output __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xe0, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "movw 0x8(%%ebx), %%di\n\t"
      "addw 0xa(%%ebx), %%di\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x14(%%ebx), %%ax\n\t"
      "addw 0x16(%%ebx), %%ax\n\t"
      "incl %%edi\n\t"
      "incl %%eax\n\t"
      "cmpw $1, 0x20(%%esi)\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "jne .LFUN_00122e50_27\n\t"
      "movswl %%ax, %%eax\n\t"
      "movswl %%di, %%ecx\n\t"
      "imull %%eax, %%ecx\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movswl 0x22(%%esi), %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_00122e50_27\n\t"
      "call *%[c120620]\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "movb %%al, 0xb(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00122e50_1\n\t"
      "flds (%%ebx)\n\t"
      "jmp .LFUN_00122e50_2\n\t"
      ".LFUN_00122e50_1:\n\t"
      "flds 0x4(%%ebx)\n\t"
      ".LFUN_00122e50_2:\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00122e50_3\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00122e50_4\n\t"
      ".LFUN_00122e50_3:\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      ".LFUN_00122e50_4:\n\t"
      "fstp %%st(0)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "call *%[ftol]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fldl 0x2573d8\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c1daf7e]\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00122e50_5\n\t"
      "flds -0x4(%%ebp)\n\t"
      "decl %%ebx\n\t"
      "fadds 0x2533c8\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".LFUN_00122e50_5:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0xa(%%ecx), %%ax\n\t"
      "cmpw %%ax, %%bx\n\t"
      "jl .LFUN_00122e50_6\n\t"
      "leal -0x1(%%eax), %%ebx\n\t"
      "movl $0x3f800000, -0x4(%%ebp)\n\t"
      ".LFUN_00122e50_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x8(%%ecx), %%ax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movswl %%bx, %%edx\n\t"
      "negl %%ecx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jge .LFUN_00122e50_7\n\t"
      "movl %%eax, %%ebx\n\t"
      "negl %%ebx\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      ".LFUN_00122e50_7:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "addl %%eax, %%ebx\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00122e50_8\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_00122e50_9\n\t"
      ".LFUN_00122e50_8:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "flds 0x4(%%eax)\n\t"
      "pushl $1\n\t"
      "pushl $0x365\n\t"
      "pushl $0x290ce4\n\t"
      "subl $0x20, %%esp\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds (%%eax)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x291418\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x28, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00122e50_9:\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00122e50_10\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "flds 0xc(%%eax)\n\t"
      "jmp .LFUN_00122e50_11\n\t"
      ".LFUN_00122e50_10:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "flds 0x10(%%ecx)\n\t"
      ".LFUN_00122e50_11:\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00122e50_12\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00122e50_13\n\t"
      ".LFUN_00122e50_12:\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      ".LFUN_00122e50_13:\n\t"
      "fstp %%st(0)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "call *%[ftol]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fldl 0x2573d8\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[c1daf7e]\n\t"
      "fsts -0x14(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "jp .LFUN_00122e50_14\n\t"
      "flds -0x14(%%ebp)\n\t"
      "decl %%eax\n\t"
      "fadds 0x2533c8\n\t"
      "fstps -0x14(%%ebp)\n\t"
      ".LFUN_00122e50_14:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x16(%%edx), %%cx\n\t"
      "cmpw %%cx, %%ax\n\t"
      "jl .LFUN_00122e50_15\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl $0x3f800000, -0x14(%%ebp)\n\t"
      "movl %%ecx, %%eax\n\t"
      ".LFUN_00122e50_15:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x14(%%edx), %%cx\n\t"
      "movswl %%cx, %%edx\n\t"
      "negl %%edx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "movswl %%ax, %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jge .LFUN_00122e50_16\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "negl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      ".LFUN_00122e50_16:\n\t"
      "addl 0xc(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00122e50_27\n\t"
      "cmpw -0x2c(%%ebp), %%ax\n\t"
      "jge .LFUN_00122e50_27\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .LFUN_00122e50_27\n\t"
      "cmpw %%di, %%bx\n\t"
      "jge .LFUN_00122e50_27\n\t"
      "movswl %%bx, %%ecx\n\t"
      "leal 0x1(%%ecx), %%edx\n\t"
      "movswl %%di, %%ecx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jne .LFUN_00122e50_17\n\t"
      "movswl %%bx, %%edx\n\t"
      ".LFUN_00122e50_17:\n\t"
      "movswl %%ax, %%ecx\n\t"
      "incl %%ecx\n\t"
      "cmpl -0x28(%%ebp), %%ecx\n\t"
      "jne .LFUN_00122e50_18\n\t"
      "movswl %%ax, %%ecx\n\t"
      ".LFUN_00122e50_18:\n\t"
      "imull %%edi, %%eax\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "leal (%%eax,%%ebx,1), %%ecx\n\t"
      "addl %%edx, %%eax\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "imull %%edi, %%eax\n\t"
      "pushl %%ecx\n\t"
      "addl %%eax, %%ebx\n\t"
      "leal (%%eax,%%edx,1), %%edi\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, -0x40(%%ebp)\n\t"
      "movl %%ebx, -0x28(%%ebp)\n\t"
      "movl %%edi, -0x2c(%%ebp)\n\t"
      "call *%[c120500]\n\t"
      "movl -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "call *%[c120500]\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "call *%[c120500]\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "call *%[c120500]\n\t"
      "xorl %%edi, %%edi\n\t"
      "addl $0x20, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpw %%di, 0x2c(%%esi)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%edi, 0xc(%%ebp)\n\t"
      "jle .LFUN_00122e50_27\n\t"
      ".LFUN_00122e50_19:\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "movswl %%bx, %%eax\n\t"
      "shll $5, %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "testb $0x1f, %%bl\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "jne .LFUN_00122e50_20\n\t"
      "movw %%bx, %%ax\n\t"
      "sarw $5, %%ax\n\t"
      "movswl %%ax, %%eax\n\t"
      "movl 0x5c(%%esi,%%eax,4), %%ecx\n\t"
      "movl 0x6c(%%esi,%%eax,4), %%edx\n\t"
      "movl %%ecx, -0x3c(%%ebp)\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      ".LFUN_00122e50_20:\n\t"
      "testb $1, -0x30(%%ebp)\n\t"
      "je .LFUN_00122e50_23\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "leal -0x80(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "je .LFUN_00122e50_21\n\t"
      "movswl -0x40(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%esi\n\t"
      "call *%[c121330]\n\t"
      "movswl -0x34(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "leal -0xb0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%esi\n\t"
      "call *%[c121330]\n\t"
      "movswl -0x28(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "leal -0x90(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%esi\n\t"
      "call *%[c121330]\n\t"
      "movswl -0x2c(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "leal -0xa0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%esi\n\t"
      "call *%[c121330]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "incl %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "jmp .LFUN_00122e50_22\n\t"
      ".LFUN_00122e50_21:\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c120810]\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "leal -0xb0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl $8, %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "call *%[c120810]\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "leal -0x90(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $8, %%eax\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "call *%[c120810]\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "leal -0xa0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "addl $8, %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "call *%[c120810]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $0x20, %%esp\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      ".LFUN_00122e50_22:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "leal -0xd0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0xb0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x80(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c10cb60]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "leal -0xc0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0xa0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x90(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c10cb60]\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "leal -0xe0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0xc0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xd0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10cb60]\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xe0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c10b9c0]\n\t"
      "addl $0x3c, %%esp\n\t"
      ".LFUN_00122e50_23:\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "movb -0x3c(%%ebp), %%al\n\t"
      "shrl $1, %%ecx\n\t"
      "testb $1, %%al\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "je .LFUN_00122e50_26\n\t"
      "flds 0x2533c8\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fsubs -0x14(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "je .LFUN_00122e50_24\n\t"
      "movswl -0x40(%%ebp), %%ecx\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "fildl -0x18(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%esi\n\t"
      "call *%[c121640]\n\t"
      "movswl -0x34(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "leal -0x64(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "fildl -0x18(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%esi\n\t"
      "call *%[c121640]\n\t"
      "movswl -0x28(%%ebp), %%edx\n\t"
      "addl $0x14, %%esp\n\t"
      "leal -0x4c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "fildl -0x18(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%esi\n\t"
      "call *%[c121640]\n\t"
      "movswl -0x2c(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "leal -0x70(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "fildl -0x18(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%esi\n\t"
      "call *%[c121640]\n\t"
      "addl $0x14, %%esp\n\t"
      "incl %%edi\n\t"
      "jmp .LFUN_00122e50_25\n\t"
      ".LFUN_00122e50_24:\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "movl %%ecx, -0x58(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "addl $0xc, %%eax\n\t"
      "movl %%ecx, -0x54(%%ebp)\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x64(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "addl $0xc, %%eax\n\t"
      "movl %%edx, -0x60(%%ebp)\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x5c(%%ebp)\n\t"
      "movl %%eax, %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "movl %%ecx, -0x4c(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "addl $0xc, %%eax\n\t"
      "movl %%ecx, -0x48(%%ebp)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl %%edx, -0x44(%%ebp)\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x70(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "addl $0xc, %%eax\n\t"
      "movl %%edx, -0x6c(%%ebp)\n\t"
      "movl %%ecx, -0x68(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      ".LFUN_00122e50_25:\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0x70(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0x64(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fadds 0x10(%%eax)\n\t"
      "fstps 0x10(%%eax)\n\t"
      "flds -0x48(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0x6c(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0x60(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fadds 0x14(%%eax)\n\t"
      "fstps 0x14(%%eax)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0x68(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fadds 0x18(%%eax)\n\t"
      "fstps 0x18(%%eax)\n\t"
      ".LFUN_00122e50_26:\n\t"
      "movl -0x3c(%%ebp), %%edx\n\t"
      "shrl $1, %%edx\n\t"
      "incl %%ebx\n\t"
      "cmpw 0x2c(%%esi), %%bx\n\t"
      "movl %%edx, -0x3c(%%ebp)\n\t"
      "jl .LFUN_00122e50_19\n\t"
      ".LFUN_00122e50_27:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c120620] "m"(b122e50_c120620), [ftol] "m"(b122e50_ftol), [c1daf7e] "m"(b122e50_c1daf7e), [c8d9d0] "m"(b122e50_c8d9d0), [assert] "m"(b122e50_assert), [exitfn] "m"(b122e50_exitfn), [c120500] "m"(b122e50_c120500), [c121330] "m"(b122e50_c121330), [c120810] "m"(b122e50_c120810), [c10cb60] "m"(b122e50_c10cb60), [c10b9c0] "m"(b122e50_c10b9c0), [c121640] "m"(b122e50_c121640)
      : "memory");
}
#else
#error "FUN_00122e50: clang naked draft required"
#endif

/* -----------------------------------------------------------------------
 * FUN_00123560 — model render geometry (multi-pass)
 *
 * Iterates over model geometry groups and parts, performing up to 3
 * rendering passes (opaque, environment-mapped, transparent).  For each
 * shader part, dispatches to the appropriate render function based on
 * shader type and pass index.
 *
 * Disassembly range: 0x123560 – 0x12398b.
 * Source: c:\halo\SOURCE\models\models.c
 * ----------------------------------------------------------------------- */
void FUN_00123560(int model_tag, int permutation_data, int *node_matrices,
                  int render_data, short shader_permutation,
                  short detail_level, unsigned char flags)
{
  char shader_valid;
  char shader_transparent;
  short shader_perm_idx;
  int geometry;
  unsigned char *part;
  int shader_ref;
  int shader_tag;
  int pass;
  unsigned int pass_limit;
  int geom_idx;
  int part_idx;
  int *parts_block;
  int typed_shader;
  short actual_detail;
  unsigned int env_count;
  int env_slot;
  /* Local array for environment map cross-referencing.
   * Each entry is 16 bytes: [0]=ptr(2b), [2]=short, [4]=short, [6]=short.
   * Max 32 entries. */
  unsigned char env_data[32 * 16];
  float transformed_centroid[3];

  pass = 0;
  pass_limit = (unsigned int)((unsigned char)~flags & 2);

  do {
    geom_idx = 0;
    env_count = 0;

    if (0 < *(int *)(model_tag + 0xc4)) {
      do {
        geometry = (int)tag_block_get_element(
          (void *)(model_tag + 0xc4), geom_idx, 0x4c);

        if (*(char *)(geom_idx + permutation_data) != -1) {
          int perm_block;
          perm_block = (int)tag_block_get_element(
            (void *)(geometry + 0x40),
            (int)*(char *)(geom_idx + permutation_data), 0x58);
          shader_perm_idx =
            *(short *)(perm_block + 0x40 + shader_permutation * 2);

          if (*(char *)0x5aa250 == '\0' && shader_perm_idx != -1) {
            int section;
            section = (int)tag_block_get_element(
              (void *)(model_tag + 0xd0),
              (int)shader_perm_idx, 0x30);
            part_idx = 0;
            parts_block = (int *)(section + 0x24);

            if (0 < *(int *)(section + 0x24)) {
              int pi;
              pi = 0;
              do {
                part = (unsigned char *)tag_block_get_element(
                  (void *)parts_block, pi, 0x68);
                shader_ref = (int)tag_block_get_element(
                  (void *)(model_tag + 0xdc),
                  (int)*(short *)(part + 4), 0x20);
                shader_tag = (int)tag_get(0x73686472,
                  *(int *)(shader_ref + 0xc));

                shader_valid = ((char (*)(int))shader_type_is_valid_for_model)(
                  (int)*(unsigned short *)(shader_tag + 0x24));

                if (shader_valid != '\0' && (part[0] & 1) == 0) {
                  shader_transparent = shader_type_is_transparent(
                    *(short *)(shader_tag + 0x24));

                  if (shader_transparent != '\0') {
                    /* Transparent shader — pass 2 */
                    if ((short)pass == 2) {
                      if ((flags & 2) != 0) {
                        display_assert(
                          "!TEST_FLAG(flags, _render_model_shadow_bit)",
                          "c:\\halo\\SOURCE\\models\\models.c", 0x1ba, 1);
                        system_exit(-1);
                      }
                      if (*(short *)(part + 8) < 0 ||
                          (int)*(short *)(part + 8) >=
                            *(int *)(model_tag + 0xb8)) {
                        display_assert(
                          "part->centroid_primary_node_index>=0 && "
                          "part->centroid_primary_node_index<"
                          "model->nodes.count",
                          "c:\\halo\\SOURCE\\models\\models.c", 0x1bd, 1);
                        system_exit(-1);
                      }
                      if (*(short *)(part + 10) < 0 ||
                          (int)*(short *)(part + 10) >=
                            *(int *)(model_tag + 0xb8)) {
                        display_assert(
                          "part->centroid_secondary_node_index>=0 && "
                          "part->centroid_secondary_node_index<"
                          "model->nodes.count",
                          "c:\\halo\\SOURCE\\models\\models.c", 0x1be, 1);
                        system_exit(-1);
                      }
                      matrix_transform_point(
                        (float *)((int)*(short *)(part + 8) * 0x34 +
                                  *node_matrices),
                        (float *)(part + 0x14),
                        transformed_centroid);
                      actual_detail = detail_level;
                      if (detail_level == 0) {
                        actual_detail = *(short *)(shader_ref + 0x10);
                      }

                      env_slot = (int)(short)env_count;
                      FUN_0017cbd0(shader_tag, (int)actual_detail,
                                   (int)(part + 0x44), -1,
                                   *(int *)(part + 0x48),
                                   (int)(part + 0x54), -1,
                                   transformed_centroid,
                                   (int)&env_data[env_slot * 16]);

                      if ((short)env_count < 0x20 &&
                          *(short *)&env_data[env_slot * 16 + 8] != -1 &&
                          (flags & 1) == 0 &&
                          ((char)part[7] > '\0' || (char)part[6] > '\0')) {
                        *(short *)&env_data[env_slot * 16 + 12] =
                          (short)part_idx;
                        *(short *)&env_data[env_slot * 16 + 10] =
                          (short)(char)part[7];
                        env_count = env_count + 1;
                      }
                    }
                  } else {
                    /* Non-transparent shader */
                    if (*(short *)(shader_tag + 0x24) == 4) {
                      typed_shader = ((int (*)(int, int))FUN_001906b0)(
                        shader_tag, 4);
                      if ((*(unsigned char *)(typed_shader + 0x28) & 8) != 0) {
                        /* Environment-mapped shader — pass 1 */
                        if ((short)pass == 1) {
                          if ((flags & 2) != 0) {
                            display_assert(
                              "!TEST_FLAG(flags, _render_model_shadow_bit)",
                              "c:\\halo\\SOURCE\\models\\models.c",
                              0x1eb, 1);
                            system_exit(-1);
                          }
                          actual_detail = detail_level;
                          if (detail_level == 0) {
                            actual_detail = *(short *)(shader_ref + 0x10);
                          }
                          FUN_0017cbc0(shader_tag, (int)actual_detail,
                                       (int)(part + 0x44), -1,
                                       *(int *)(part + 0x48),
                                       (int)(part + 0x54), -1);
                        }
                        goto next_part;
                      }
                    }

                    /* Opaque shader — pass 0 */
                    if ((short)pass == 0) {
                      if ((flags & 2) == 0) {
                        actual_detail = detail_level;
                        if (detail_level == 0) {
                          actual_detail = *(short *)(shader_ref + 0x10);
                        }
                        FUN_0017cbc0(shader_tag, (int)actual_detail,
                                     (int)(part + 0x44), -1,
                                     *(int *)(part + 0x48),
                                     (int)(part + 0x54), -1);
                        ((void (*)(int, int *, unsigned char *))FUN_0017d2b0)(
                          render_data, node_matrices, part);
                      } else {
                        actual_detail = detail_level;
                        if (detail_level == 0) {
                          actual_detail = *(short *)(shader_ref + 0x10);
                        }
                        FUN_0017ccd0((void *)shader_tag, (int)actual_detail,
                                     (void *)(part + 0x44),
                                     (void *)(part + 0x54));
                      }
                    }
                  }
                }
next_part:
                part_idx = part_idx + 1;
                pi = (int)(short)part_idx;
              } while (pi < *parts_block);
            }
          }
        }

        geom_idx = (int)(short)((short)geom_idx + 1);
      } while (geom_idx < *(int *)(model_tag + 0xc4));

      /* Post-pass: cross-reference environment map entries.
       * Each 16-byte entry:
       *   [0..3] = ptr_a (int), [4..7] = ptr_b (int),
       *   [8..9] = short val, [10..11] = (short)(char)part[7],
       *   [12..13] = (short)part_idx */
      if (0 < (short)env_count) {
        unsigned int i;
        unsigned int env_total;
        env_total = env_count & 0xffff;
        for (i = 0; i < env_total; i++) {
          short j;
          short match_field = *(short *)&env_data[i * 16 + 10];
          for (j = 0; j < (short)env_count; j++) {
            if (match_field == *(short *)&env_data[j * 16 + 12] &&
                0 < match_field) {
              *(short *)(*(int *)&env_data[i * 16 + 4]) =
                *(short *)&env_data[j * 16 + 8];
              *(short *)(*(int *)&env_data[j * 16]) =
                *(short *)&env_data[i * 16 + 8];
              break;
            }
          }
        }
      }
    }

    pass = pass + 1;
    if ((short)pass_limit < (short)pass) {
      return;
    }
  } while (1);
}

/* unit_cause_player_melee_damage (0x1aea90) — XBE naked draft (batch 51). */
#if defined(__clang__)
static void *(*const b1aea90_get)(int, int) = object_get_and_verify_type;
static void *(*const b1aea90_tag)(int, int) = tag_get;
static short (*const b1aea90_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static void (*const b1aea90_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1aea90_exitfn)(int) = system_exit;
static void (*const b1aea90_perp)(float *, float *) = perpendicular3d;
static float (*const b1aea90_norm)(float *) = normalize3d;
static bool (*const b1aea90_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;
static void (*const b1aea90_c1b5c90)(int handle, float *velocity) = vehicle_accelerate;
static void (*const b1aea90_c136750)(void *damage_params, int tag_index) = damage_data_new;
static void (*const b1aea90_c146a90)(int surface_id, void *damage_params, int unknown) = FUN_00146a90;
static void (*const b1aea90_c95c10)(int object) = FUN_00095c10;
static void * (*const b1aea90_c18e450)(void) = game_globals_get;
static void *(*const b1aea90_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1aea90_c137d20)(void *damage_params, int object_handle, short node_index, short region_index, short permutation_index, unsigned int flags) = object_cause_damage;
static void (*const b1aea90_c1abd10)(int16_t material_type, int unit_handle, int weapon_tag_index) = FUN_001abd10;

__attribute__((naked, noinline))
void unit_cause_player_melee_damage(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xd0, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "pushl $1\n\t"
      "leal -0xd0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "pushl $0x2909e4\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x60(%%ebp)\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "movl %%edi, -0x24(%%ebp)\n\t"
      "movl %%edi, -0x28(%%ebp)\n\t"
      "call *%[markers]\n\t"
      "movl -0x70(%%ebp), %%edx\n\t"
      "movl -0x6c(%%ebp), %%eax\n\t"
      "movl -0x68(%%ebp), %%ecx\n\t"
      "addl $0x20, %%esp\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "movl %%edx, -0x4c(%%ebp)\n\t"
      "movl %%eax, -0x48(%%ebp)\n\t"
      "movl %%ecx, -0x44(%%ebp)\n\t"
      "jl .Lunit_cause_player_melee_damage_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2212\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_cause_player_melee_damage_1:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "movswl %%ax, %%edx\n\t"
      "incw %%ax\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x1ec(%%ebx), %%esi\n\t"
      "pushl %%esi\n\t"
      "movw $8, 0x5a8c80(,%%edx,2)\n\t"
      "call *%[perp]\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $0xc, %%esp\n\t"
      "flds -0x18(%%ebp)\n\t"
      "movl $0xfffffffe, -0x10(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "movl $5, -0x2c(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x5c(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "jmp .Lunit_cause_player_melee_damage_3\n\t"
      ".Lunit_cause_player_melee_damage_2:\n\t"
      "orl $0xffffffff, %%edi\n\t"
      ".Lunit_cause_player_melee_damage_3:\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "movl $0xfffffffe, -0x14(%%ebp)\n\t"
      "movl $5, -0x34(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "jmp .Lunit_cause_player_melee_damage_5\n\t"
      ".Lunit_cause_player_melee_damage_4:\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lunit_cause_player_melee_damage_5:\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "leal -0xb4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "pushl %%edx\n\t"
      "flds -0xc(%%ebp)\n\t"
      "leal -0x40(%%ebp), %%eax\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "leal -0x4c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "faddp %%st(1)\n\t"
      "pushl $0x1000e9\n\t"
      "fmuls 0x25496c\n\t"
      "flds (%%esi)\n\t"
      "fmuls 0x2533f0\n\t"
      "faddp %%st(1)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fmuls 0x25496c\n\t"
      "flds 0x1f0(%%ebx)\n\t"
      "fmuls 0x2533f0\n\t"
      "faddp %%st(1)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "fmuls -0x54(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fmuls 0x25496c\n\t"
      "flds 0x1f4(%%ebx)\n\t"
      "fmuls 0x2533f0\n\t"
      "faddp %%st(1)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lunit_cause_player_melee_damage_10\n\t"
      "movswl -0xb4(%%ebp), %%eax\n\t"
      "subl $2, %%eax\n\t"
      "je .Lunit_cause_player_melee_damage_9\n\t"
      "decl %%eax\n\t"
      "jne .Lunit_cause_player_melee_damage_10\n\t"
      "movl -0x7c(%%ebp), %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, 0x64(%%ecx)\n\t"
      "je .Lunit_cause_player_melee_damage_6\n\t"
      "movl 0xcc(%%ecx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lunit_cause_player_melee_damage_6\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%ecx\n\t"
      ".Lunit_cause_player_melee_damage_6:\n\t"
      "cmpl $-1, -0x4(%%ebp)\n\t"
      "je .Lunit_cause_player_melee_damage_8\n\t"
      "movw 0x64(%%ecx), %%dx\n\t"
      "testw %%dx, %%dx\n\t"
      "jne .Lunit_cause_player_melee_damage_10\n\t"
      "cmpw %%dx, -0x30(%%ebp)\n\t"
      "jne .Lunit_cause_player_melee_damage_7\n\t"
      "flds -0x64(%%ebp)\n\t"
      "fcomps -0xa0(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lunit_cause_player_melee_damage_8\n\t"
      ".Lunit_cause_player_melee_damage_7:\n\t"
      "testw %%dx, %%dx\n\t"
      "jne .Lunit_cause_player_melee_damage_10\n\t"
      "cmpw %%dx, -0x30(%%ebp)\n\t"
      "je .Lunit_cause_player_melee_damage_10\n\t"
      ".Lunit_cause_player_melee_damage_8:\n\t"
      "movw 0x64(%%ecx), %%dx\n\t"
      "movl -0x80(%%ebp), %%eax\n\t"
      "movl -0xa0(%%ebp), %%ecx\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movw %%dx, -0x30(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x64(%%ebp)\n\t"
      "jmp .Lunit_cause_player_melee_damage_10\n\t"
      ".Lunit_cause_player_melee_damage_9:\n\t"
      "cmpl %%edi, -0x4(%%ebp)\n\t"
      "jne .Lunit_cause_player_melee_damage_10\n\t"
      "movl -0x68(%%ebp), %%eax\n\t"
      "testb $8, %%al\n\t"
      "movl -0x80(%%ebp), %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "je .Lunit_cause_player_melee_damage_10\n\t"
      "movl -0x70(%%ebp), %%ecx\n\t"
      "movzbw %%ah, %%ax\n\t"
      "movw %%ax, -0x24(%%ebp)\n\t"
      "movl %%ecx, -0x50(%%ebp)\n\t"
      ".Lunit_cause_player_melee_damage_10:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "incl %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "jne .Lunit_cause_player_melee_damage_4\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "incl %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "jne .Lunit_cause_player_melee_damage_2\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "jg .Lunit_cause_player_melee_damage_11\n\t"
      "pushl $1\n\t"
      "pushl $0x2256\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_cause_player_melee_damage_11:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "decw 0x4761d8\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "movw 0x2a2(%%eax), %%di\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $-1, %%di\n\t"
      "movl %%eax, %%esi\n\t"
      "je .Lunit_cause_player_melee_damage_14\n\t"
      "testw %%di, %%di\n\t"
      "jl .Lunit_cause_player_melee_damage_12\n\t"
      "cmpw $4, %%di\n\t"
      "jl .Lunit_cause_player_melee_damage_13\n\t"
      ".Lunit_cause_player_melee_damage_12:\n\t"
      "pushl $1\n\t"
      "pushl $0x20ac\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b6e84\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunit_cause_player_melee_damage_13:\n\t"
      "movswl %%di, %%ecx\n\t"
      "movl 0x2a8(%%esi,%%ecx,4), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lunit_cause_player_melee_damage_14\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x77656170\n\t"
      "call *%[tag]\n\t"
      "movl 0x3a0(%%eax), %%edi\n\t"
      "movl 0x3b0(%%eax), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "jne .Lunit_cause_player_melee_damage_15\n\t"
      ".Lunit_cause_player_melee_damage_14:\n\t"
      "movl -0x60(%%ebp), %%ecx\n\t"
      "movl 0x294(%%ecx), %%edi\n\t"
      ".Lunit_cause_player_melee_damage_15:\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lunit_cause_player_melee_damage_16\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $1, 0x64(%%eax)\n\t"
      "jne .Lunit_cause_player_melee_damage_16\n\t"
      "movl (%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "flds 0x20(%%eax)\n\t"
      "fmuls 0x2b7204\n\t"
      "leal -0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x1ec(%%ebx)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x1f0(%%ebx)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "fmuls 0x1f4(%%ebx)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "call *%[c1b5c90]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lunit_cause_player_melee_damage_16:\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lunit_cause_player_melee_damage_22\n\t"
      "leal -0xb8(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c136750]\n\t"
      "movl -0xb4(%%ebp), %%ecx\n\t"
      "movl 0x48(%%ebx), %%edx\n\t"
      "movl 0x4c(%%ebx), %%eax\n\t"
      "orl $1, %%ecx\n\t"
      "movl %%ecx, -0xb4(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%edx, -0xa4(%%ebp)\n\t"
      "movw 0x68(%%ebx), %%dx\n\t"
      "movl %%eax, -0xa0(%%ebp)\n\t"
      "movl 0x1c8(%%ebx), %%eax\n\t"
      "movl %%ecx, -0xac(%%ebp)\n\t"
      "movl -0x4c(%%ebp), %%ecx\n\t"
      "movw %%dx, -0xa8(%%ebp)\n\t"
      "movl -0x48(%%ebp), %%edx\n\t"
      "movl %%eax, -0xb0(%%ebp)\n\t"
      "movl -0x44(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x9c(%%ebp)\n\t"
      "movl %%edx, -0x98(%%ebp)\n\t"
      "movl %%eax, -0x94(%%ebp)\n\t"
      "leal 0x50(%%ebx), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%eax, -0x8c(%%ebp)\n\t"
      "leal 0x1ec(%%ebx), %%eax\n\t"
      "movl %%edx, -0x90(%%ebp)\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%ecx, -0x88(%%ebp)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%edx, -0x84(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movw -0x8(%%ebp), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "movl %%ecx, -0x80(%%ebp)\n\t"
      "movl %%edx, -0x7c(%%ebp)\n\t"
      "movw %%ax, -0x6c(%%ebp)\n\t"
      "jne .Lunit_cause_player_melee_damage_17\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "cmpw %%si, %%ax\n\t"
      "je .Lunit_cause_player_melee_damage_22\n\t"
      "movl -0x50(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xb8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c146a90]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Lunit_cause_player_melee_damage_22\n\t"
      ".Lunit_cause_player_melee_damage_17:\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $7, 0x64(%%eax)\n\t"
      "jne .Lunit_cause_player_melee_damage_18\n\t"
      "pushl %%esi\n\t"
      "call *%[c95c10]\n\t"
      "addl $4, %%esp\n\t"
      ".Lunit_cause_player_melee_damage_18:\n\t"
      "pushl $0xf4\n\t"
      "pushl $0\n\t"
      "call *%[c18e450]\n\t"
      "addl $0x170, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x34(%%ecx)\n\t"
      "addl $0xc, %%esp\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_cause_player_melee_damage_20\n\t"
      "flds 0x2c(%%ebx)\n\t"
      "fmuls 0x20(%%ebx)\n\t"
      "flds 0x28(%%ebx)\n\t"
      "fmuls 0x1c(%%ebx)\n\t"
      "faddp %%st(1)\n\t"
      "flds 0x24(%%ebx)\n\t"
      "fmuls 0x18(%%ebx)\n\t"
      "faddp %%st(1)\n\t"
      "fmuls 0x253394\n\t"
      "fdivs 0x34(%%ecx)\n\t"
      "fsts -0x78(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lunit_cause_player_melee_damage_19\n\t"
      "movl $0, -0x78(%%ebp)\n\t"
      "jmp .Lunit_cause_player_melee_damage_20\n\t"
      ".Lunit_cause_player_melee_damage_19:\n\t"
      "flds -0x78(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lunit_cause_player_melee_damage_20\n\t"
      "movl $0x3f800000, -0x78(%%ebp)\n\t"
      ".Lunit_cause_player_melee_damage_20:\n\t"
      "cmpw $0, 0x64(%%ebx)\n\t"
      "jne .Lunit_cause_player_melee_damage_21\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movb 0x459(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "cmpb $0xf, %%cl\n\t"
      "jle .Lunit_cause_player_melee_damage_21\n\t"
      "movl $0x3fc00000, -0x78(%%ebp)\n\t"
      ".Lunit_cause_player_melee_damage_21:\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, 0x64(%%eax)\n\t"
      "jne .Lunit_cause_player_melee_damage_22\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "leal -0xb8(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c137d20]\n\t"
      "addl $0x18, %%esp\n\t"
      ".Lunit_cause_player_melee_damage_22:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lunit_cause_player_melee_damage_23\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "call *%[c1abd10]\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lunit_cause_player_melee_damage_23\n\t"
      "pushl %%eax\n\t"
      "leal -0xb8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c136750]\n\t"
      "flds 0x1ec(%%ebx)\n\t"
      "movl -0xb4(%%ebp), %%esi\n\t"
      "fchs\n\t"
      "leal 0x50(%%ebx), %%eax\n\t"
      "fstps -0x84(%%ebp)\n\t"
      "flds 0x1f0(%%ebx)\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "fchs\n\t"
      "movl %%edx, -0x90(%%ebp)\n\t"
      "fstps -0x80(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "flds 0x1f4(%%ebx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "fchs\n\t"
      "pushl $0\n\t"
      "fstps -0x7c(%%ebp)\n\t"
      "movl %%edx, -0x8c(%%ebp)\n\t"
      "movl (%%eax), %%edx\n\t"
      "pushl $-1\n\t"
      "movl %%ecx, -0x88(%%ebp)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "pushl $-1\n\t"
      "movl %%edx, -0x9c(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $-1\n\t"
      "movl %%ecx, -0x98(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "leal -0xb8(%%ebp), %%ecx\n\t"
      "orl $8, %%esi\n\t"
      "pushl %%ecx\n\t"
      "movl %%esi, -0xb4(%%ebp)\n\t"
      "movl %%edx, -0x94(%%ebp)\n\t"
      "call *%[c137d20]\n\t"
      "addl $0x20, %%esp\n\t"
      ".Lunit_cause_player_melee_damage_23:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $0, 0x239(%%ebx)\n\t"
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
      : [get] "m"(b1aea90_get), [tag] "m"(b1aea90_tag), [markers] "m"(b1aea90_markers), [assert] "m"(b1aea90_assert), [exitfn] "m"(b1aea90_exitfn), [perp] "m"(b1aea90_perp), [norm] "m"(b1aea90_norm), [ray] "m"(b1aea90_ray), [c1b5c90] "m"(b1aea90_c1b5c90), [c136750] "m"(b1aea90_c136750), [c146a90] "m"(b1aea90_c146a90), [c95c10] "m"(b1aea90_c95c10), [c18e450] "m"(b1aea90_c18e450), [elem] "m"(b1aea90_elem), [c137d20] "m"(b1aea90_c137d20), [c1abd10] "m"(b1aea90_c1abd10)
      : "memory");
}
#else
#error "unit_cause_player_melee_damage: clang naked draft required"
#endif


/* FUN_001afd30 (0x1afd30) — XBE naked draft (batch 48). */
#if defined(__clang__)
static void *(*const b1afd30_get)(int, int) = object_get_and_verify_type;
static void *(*const b1afd30_tag)(int, int) = tag_get;
static void *(*const b1afd30_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1afd30_c122060)(void) = replacement_animation_apply;
static void (*const b1afd30_c122240)(void *animation, int frame, void *node_output) = overlay_animation_apply;
static void (*const b1afd30_c1af6b0)(int unit_handle, const char *label) = unit_control_trace;
static void (*const b1afd30_c122450)(void *animation, int frame, float scale, void *node_output) = overlay_animation_apply_scaled;
static void (*const b1afd30_c122690)(void *animation, float frame, void *node_data) = FUN_00122690;
static bool (*const b1afd30_c21fb0)(float *v) = valid_real_normal3d;
static char * (*const b1afd30_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b1afd30_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1afd30_exitfn)(int) = system_exit;
static void (*const b1afd30_c141360)(int object_handle, float *out_forward, float *out_up) = object_get_orientation;
static void (*const b1afd30_cross)(float *, float *, float *) = cross_product3d;
static void (*const b1afd30_c1097f0)(void *matrix, void *point, void *out) = real_matrix4x3_transform_point;
static int (*const b1afd30_c84a10)(float *vector) = real_vector3d_valid;
static void (*const b1afd30_c10cc00)(float *out_angles, float *in_vector) = vector_to_angles;
static void (*const b1afd30_c122e50)(int animation, float *blend_params, float direction, float throttle, int node_output) = FUN_00122e50;

__attribute__((naked, noinline))
void FUN_001afd30(int unit_handle __attribute__((unused)), int node_output __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x64, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0x44(%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x616e7472\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "movw 0x25a(%%esi), %%ax\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "je .LFUN_001afd30_1\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x25c(%%esi), %%cx\n\t"
      "pushl %%edi\n\t"
      "movswl %%ax, %%edx\n\t"
      "leal 0x74(%%ebx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xb4\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c122060]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001afd30_1:\n\t"
      "movw 0x25e(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001afd30_2\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x260(%%esi), %%cx\n\t"
      "pushl %%edi\n\t"
      "movswl %%ax, %%edx\n\t"
      "leal 0x74(%%ebx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xb4\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c122240]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001afd30_2:\n\t"
      "movw 0x262(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001afd30_3\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x264(%%esi), %%cx\n\t"
      "pushl %%edi\n\t"
      "movswl %%ax, %%edx\n\t"
      "leal 0x74(%%ebx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xb4\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c122240]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001afd30_3:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $0x2b7824\n\t"
      "call *%[c1af6b0]\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movb $0, 0x266(%%esi)\n\t"
      "movb $0, 0x267(%%esi)\n\t"
      "movl 0x17c(%%ecx), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "testb $8, %%ah\n\t"
      "jne .LFUN_001afd30_23\n\t"
      "movb 0x250(%%esi), %%al\n\t"
      "cmpb $0xff, %%al\n\t"
      "je .LFUN_001afd30_23\n\t"
      "movsbl %%al, %%edx\n\t"
      "pushl $0x64\n\t"
      "pushl %%edx\n\t"
      "leal 0xc(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edx\n\t"
      "movb 0x258(%%esi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpb $0xff, %%al\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "je .LFUN_001afd30_8\n\t"
      "cmpl $0xb, 0x40(%%edx)\n\t"
      "jle .LFUN_001afd30_4\n\t"
      "movl 0x44(%%edx), %%ecx\n\t"
      "movw 0x16(%%ecx), %%ax\n\t"
      "jmp .LFUN_001afd30_5\n\t"
      ".LFUN_001afd30_4:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      ".LFUN_001afd30_5:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x1ce(%%esi), %%cx\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .LFUN_001afd30_6\n\t"
      "movl %%ecx, %%eax\n\t"
      ".LFUN_001afd30_6:\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001afd30_8\n\t"
      "movswl %%ax, %%edx\n\t"
      "pushl $0xb4\n\t"
      "pushl %%edx\n\t"
      "leal 0x74(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movb 0x258(%%esi), %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "jl .LFUN_001afd30_7\n\t"
      "movsbw %%cl, %%cx\n\t"
      "cmpw 0x22(%%eax), %%cx\n\t"
      "jge .LFUN_001afd30_7\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c122240]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001afd30_7:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      ".LFUN_001afd30_8:\n\t"
      "flds 0x298(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001afd30_9\n\t"
      "cmpl $0xa, 0x40(%%edx)\n\t"
      "jle .LFUN_001afd30_9\n\t"
      "movl 0x44(%%edx), %%eax\n\t"
      "movw 0x14(%%eax), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001afd30_9\n\t"
      "movswl %%ax, %%ecx\n\t"
      "pushl $0xb4\n\t"
      "pushl %%ecx\n\t"
      "leal 0x74(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x298(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c122450]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_001afd30_9:\n\t"
      "testb $2, 0x248(%%esi)\n\t"
      "je .LFUN_001afd30_12\n\t"
      "movl $2, %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl $4, %%ebx\n\t"
      "leal 0x314(%%esi), %%edi\n\t"
      "movl $3, -0x10(%%ebp)\n\t"
      "jmp .LFUN_001afd30_10\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_001afd30_10:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jl .LFUN_001afd30_11\n\t"
      "cmpl 0x40(%%edx), %%ecx\n\t"
      "jge .LFUN_001afd30_11\n\t"
      "movl 0x44(%%edx), %%eax\n\t"
      "movw (%%ebx,%%eax,1), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001afd30_11\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movswl %%ax, %%ecx\n\t"
      "pushl $0xb4\n\t"
      "pushl %%ecx\n\t"
      "addl $0x74, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movswl 0x22(%%eax), %%edx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "decl %%edx\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fildl -0x24(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c122690]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001afd30_11:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $2, %%ebx\n\t"
      "addl $4, %%edi\n\t"
      "incl %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jne .LFUN_001afd30_10\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      ".LFUN_001afd30_12:\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl 0x17c(%%eax), %%ecx\n\t"
      "testb $4, %%ch\n\t"
      "jne .LFUN_001afd30_23\n\t"
      "movb 0x254(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb 0x253(%%esi), %%al\n\t"
      "sete %%cl\n\t"
      "cmpb $0x17, %%al\n\t"
      "jl .LFUN_001afd30_13\n\t"
      "cmpb $0x23, %%al\n\t"
      "jle .LFUN_001afd30_23\n\t"
      "cmpb $0x29, %%al\n\t"
      "je .LFUN_001afd30_23\n\t"
      ".LFUN_001afd30_13:\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_001afd30_23\n\t"
      "movsbl 0x251(%%esi), %%ecx\n\t"
      "pushl $0xbc\n\t"
      "pushl %%ecx\n\t"
      "addl $0x58, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl 0x31fc54, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $-1, 0x24a(%%esi)\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "je .LFUN_001afd30_18\n\t"
      "leal 0x1ec(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "leal 0x60(%%eax), %%edi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001afd30_14\n\t"
      "flds 0x1f4(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x670\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x1f0(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b7808\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001afd30_14:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x60(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl $0x3f800000, -0x64(%%ebp)\n\t"
      "call *%[c141360]\n\t"
      "leal -0x54(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x60(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cross]\n\t"
      "movl 0x31fc1c, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "leal -0x64(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "call *%[c1097f0]\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c84a10]\n\t"
      "addl $0x28, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001afd30_15\n\t"
      "flds -0x10(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x67d\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b77f0\n\t"
      "pushl $0x26ae40\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001afd30_15:\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10cc00]\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "jne .LFUN_001afd30_16\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x680\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "movl %%edx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2b710c\n\t"
      "pushl $0x25eb8c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x18, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001afd30_16:\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "jne .LFUN_001afd30_17\n\t"
      "flds -0x20(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x681\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "movl %%edx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2b70f0\n\t"
      "pushl $0x25eb8c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x18, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001afd30_17:\n\t"
      "movb $1, 0x266(%%esi)\n\t"
      "movswl 0x8(%%edi), %%edx\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "fildl -0x24(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "fchs\n\t"
      "fstps 0x268(%%esi)\n\t"
      "movswl 0xa(%%edi), %%eax\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fildl -0x24(%%ebp)\n\t"
      "movswl 0x24a(%%esi), %%eax\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "fstps 0x26c(%%esi)\n\t"
      "movswl 0x14(%%edi), %%ecx\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fildl -0x24(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "addl $0x74, %%ecx\n\t"
      "fmuls 0xc(%%edi)\n\t"
      "fchs\n\t"
      "fstps 0x270(%%esi)\n\t"
      "movswl 0x16(%%edi), %%edx\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fildl -0x24(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "pushl $0xb4\n\t"
      "pushl %%eax\n\t"
      "fmuls 0x10(%%edi)\n\t"
      "pushl %%ecx\n\t"
      "fstps 0x274(%%esi)\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c122e50]\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001afd30_18:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "cmpw %%ax, 0x2a2(%%esi)\n\t"
      "jne .LFUN_001afd30_19\n\t"
      "cmpl %%eax, 0x1c8(%%esi)\n\t"
      "je .LFUN_001afd30_23\n\t"
      ".LFUN_001afd30_19:\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "addl $0x20, %%edi\n\t"
      "cmpw $-1, 0x24c(%%esi)\n\t"
      "je .LFUN_001afd30_23\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x60(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl $0x3f800000, -0x64(%%ebp)\n\t"
      "call *%[c141360]\n\t"
      "leal -0x54(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x60(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cross]\n\t"
      "movl 0x31fc1c, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x210(%%esi), %%ecx\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "leal -0x64(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1097f0]\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c84a10]\n\t"
      "addl $0x28, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001afd30_20\n\t"
      "flds -0x28(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x6a7\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b77d4\n\t"
      "pushl $0x26ae40\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001afd30_20:\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c10cc00]\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fsubs -0x20(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fsubs -0x1c(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "jne .LFUN_001afd30_21\n\t"
      "flds -0x10(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x6ae\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "movl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x2b77b4\n\t"
      "pushl $0x25eb8c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x18, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001afd30_21:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "jne .LFUN_001afd30_22\n\t"
      "flds -0x14(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x6af\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "movl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x2b7798\n\t"
      "pushl $0x25eb8c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x18, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001afd30_22:\n\t"
      "movb $1, 0x267(%%esi)\n\t"
      "movswl 0x8(%%edi), %%eax\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "addl $0x74, %%ebx\n\t"
      "fildl -0x24(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "fchs\n\t"
      "fstps 0x278(%%esi)\n\t"
      "movswl 0xa(%%edi), %%ecx\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fildl -0x24(%%ebp)\n\t"
      "movswl 0x24c(%%esi), %%ecx\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "fstps 0x27c(%%esi)\n\t"
      "movswl 0x14(%%edi), %%edx\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fildl -0x24(%%ebp)\n\t"
      "fmuls 0xc(%%edi)\n\t"
      "fchs\n\t"
      "fstps 0x280(%%esi)\n\t"
      "movswl 0x16(%%edi), %%eax\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fildl -0x24(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "pushl $0xb4\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x10(%%edi)\n\t"
      "pushl %%ebx\n\t"
      "fstps 0x284(%%esi)\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c122e50]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001afd30_23:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1afd30_get), [tag] "m"(b1afd30_tag), [elem] "m"(b1afd30_elem), [c122060] "m"(b1afd30_c122060), [c122240] "m"(b1afd30_c122240), [c1af6b0] "m"(b1afd30_c1af6b0), [c122450] "m"(b1afd30_c122450), [c122690] "m"(b1afd30_c122690), [c21fb0] "m"(b1afd30_c21fb0), [c8d9d0] "m"(b1afd30_c8d9d0), [assert] "m"(b1afd30_assert), [exitfn] "m"(b1afd30_exitfn), [c141360] "m"(b1afd30_c141360), [cross] "m"(b1afd30_cross), [c1097f0] "m"(b1afd30_c1097f0), [c84a10] "m"(b1afd30_c84a10), [c10cc00] "m"(b1afd30_c10cc00), [c122e50] "m"(b1afd30_c122e50)
      : "memory");
}
#else
#error "FUN_001afd30: clang naked draft required"
#endif

/* FUN_001b0630 (0x1b0630) — XBE naked draft (batch 48). */
#if defined(__clang__)
static void (*const b1b0630_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1b0630_exitfn)(int) = system_exit;
static void (*const b1b0630_c1097f0)(void *matrix, void *point, void *out) = real_matrix4x3_transform_point;
static void (*const b1b0630_c10cc00)(float *out_angles, float *in_vector) = vector_to_angles;
static void (*const b1b0630_c10cc40)(float *out, float *angles) = angles_to_vector;
static void (*const b1b0630_c109680)(float *matrix, float *in, float *out) = matrix_transform_vector;
static float (*const b1b0630_norm)(float *) = normalize3d;
static void (*const b1b0630_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;
static void (*const b1b0630_c1ac680)(float initial_p, float initial_v, float max_v, float max_a, int plan) = FUN_001ac680;
static void (*const b1b0630_c1acb70)(void *plan_a, void *plan_b, int dummy, float delta_time) = unit_adjust_plan_overlap;
static char (*const b1b0630_c1a8550)(void *plan, float delta_time, float position, float *out_position, float velocity, float *out_velocity) = FUN_001a8550;
static void (*const b1b0630_c1d94f0)(void) = FUN_001d94f0;
static bool (*const b1b0630_c21fb0)(float *v) = valid_real_normal3d;
static char * (*const b1b0630_c8d9d0)(char *buffer, const char *format, ...) = csprintf;

__attribute__((naked, noinline))
void FUN_001b0630(int transform_matrix __attribute__((unused)), float *aiming_vector __attribute__((unused)), float *desired_vector __attribute__((unused)), float *angular_velocity __attribute__((unused)), float *aiming_bounds __attribute__((unused)), float angular_velocity_limit __attribute__((unused)), float angular_acceleration_limit __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xb0, %%esp\n\t"
      "flds 0x1c(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_001b0630_1\n\t"
      "pushl $1\n\t"
      "pushl $0x962\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b7a20\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b0630_1:\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b0630_2\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fcomps 0x2af240\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001b0630_3\n\t"
      ".LFUN_001b0630_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x963\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b79d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b0630_3:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_001b0630_4\n\t"
      "leal -0x5c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1097f0]\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "leal -0x70(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c1097f0]\n\t"
      "addl $0x18, %%esp\n\t"
      "jmp .LFUN_001b0630_5\n\t"
      ".LFUN_001b0630_4:\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x5c(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl %%eax, -0x58(%%ebp)\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%ecx, -0x54(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x70(%%ebp)\n\t"
      "movl %%ecx, -0x6c(%%ebp)\n\t"
      "movl %%edx, -0x68(%%ebp)\n\t"
      ".LFUN_001b0630_5:\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "flds 0x4(%%esi)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "fsubs (%%esi)\n\t"
      "fsubs 0x255a54\n\t"
      "fcomps 0x26a810\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001b0630_6\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_001b0630_6:\n\t"
      "pushl %%ebx\n\t"
      "leal -0x5c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x64(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10cc00]\n\t"
      "leal -0x70(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c10cc00]\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fcomps (%%esi)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movb $1, %%bl\n\t"
      "fnstsw %%ax\n\t"
      "je .LFUN_001b0630_8\n\t"
      "testb $5, %%ah\n\t"
      "flds -0x14(%%ebp)\n\t"
      "jp .LFUN_001b0630_7\n\t"
      "fadds 0x255a54\n\t"
      "fsts -0x14(%%ebp)\n\t"
      "fcomps 0x4(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_001b0630_11\n\t"
      "pushl $1\n\t"
      "pushl $0x981\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b79a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_001b0630_11\n\t"
      ".LFUN_001b0630_7:\n\t"
      "fcomps 0x4(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b0630_11\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fsubs 0x255a54\n\t"
      "fsts -0x14(%%ebp)\n\t"
      "fcomps (%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_001b0630_11\n\t"
      "pushl $1\n\t"
      "pushl $0x986\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b7970\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_001b0630_11\n\t"
      ".LFUN_001b0630_8:\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b0630_9\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "jmp .LFUN_001b0630_10\n\t"
      ".LFUN_001b0630_9:\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fcomps 0x4(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b0630_11\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      ".LFUN_001b0630_10:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_001b0630_11:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x8(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b0630_14\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      ".LFUN_001b0630_12:\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x50(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10cc40]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_001b0630_13\n\t"
      "leal -0x50(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x50(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c109680]\n\t"
      "leal -0x50(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_001b0630_13:\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcoms 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_001b0630_16\n\t"
      "fld %%st(0)\n\t"
      "subl $8, %%esp\n\t"
      "fcos\n\t"
      "movl -0x5c(%%ebp), %%ecx\n\t"
      "movl -0x58(%%ebp), %%edx\n\t"
      "movl -0x54(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "fsin\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[rots]\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10cc00]\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fsubs -0x64(%%ebp)\n\t"
      "addl $0x18, %%esp\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fsubs -0x60(%%ebp)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "jmp .LFUN_001b0630_17\n\t"
      ".LFUN_001b0630_14:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0xc(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b0630_15\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "jmp .LFUN_001b0630_12\n\t"
      ".LFUN_001b0630_15:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_001b0630_12\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl %%ecx, -0x4c(%%ebp)\n\t"
      "movl %%edx, -0x48(%%ebp)\n\t"
      "jmp .LFUN_001b0630_13\n\t"
      ".LFUN_001b0630_16:\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x34(%%ebp)\n\t"
      "movl $0, -0x30(%%ebp)\n\t"
      ".LFUN_001b0630_17:\n\t"
      "flds -0x64(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "fsubs -0x14(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x60(%%ebp)\n\t"
      "fsubs -0x10(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "je .LFUN_001b0630_20\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fcomps 0x256980\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b0630_18\n\t"
      "fsubs 0x255a54\n\t"
      "jmp .LFUN_001b0630_19\n\t"
      ".LFUN_001b0630_18:\n\t"
      "fcomps 0x26e280\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b0630_20\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fadds 0x255a54\n\t"
      ".LFUN_001b0630_19:\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      ".LFUN_001b0630_20:\n\t"
      "movl 0x20(%%ebp), %%esi\n\t"
      "movl 0x1c(%%ebp), %%edi\n\t"
      "movl -0x34(%%ebp), %%ebx\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "leal -0x90(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ac680]\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "leal -0xb0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ac680]\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "leal -0xb0(%%ebp), %%eax\n\t"
      "leal -0x90(%%ebp), %%ecx\n\t"
      "call *%[c1acb70]\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3f800000\n\t"
      "leal -0x90(%%ebp), %%ecx\n\t"
      "call *%[c1a8550]\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "addl $0x44, %%esp\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movb %%al, %%bl\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3f800000\n\t"
      "leal -0xb0(%%ebp), %%ecx\n\t"
      "call *%[c1a8550]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_001b0630_21\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b0630_21\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movl -0x50(%%ebp), %%eax\n\t"
      "movl -0x4c(%%ebp), %%ecx\n\t"
      "movl %%esi, %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl -0x48(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl 0x31fc38, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "jmp .LFUN_001b0630_37\n\t"
      ".LFUN_001b0630_21:\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "je .LFUN_001b0630_23\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "fcomps (%%esi)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b0630_22\n\t"
      "fadds 0x255a54\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "fcomps 0x4(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_001b0630_26\n\t"
      "pushl $1\n\t"
      "pushl $0xaa5\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b7944\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_001b0630_26\n\t"
      ".LFUN_001b0630_22:\n\t"
      "fcomps 0x4(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b0630_26\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsubs 0x255a54\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "fcomps (%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_001b0630_26\n\t"
      "pushl $1\n\t"
      "pushl $0xaaa\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b7918\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_001b0630_26\n\t"
      ".LFUN_001b0630_23:\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "fcomps (%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b0630_24\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "jmp .LFUN_001b0630_25\n\t"
      ".LFUN_001b0630_24:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x4(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b0630_25\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      ".LFUN_001b0630_25:\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      ".LFUN_001b0630_26:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x8(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b0630_27\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_001b0630_28\n\t"
      ".LFUN_001b0630_27:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0xc(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b0630_28\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".LFUN_001b0630_28:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps (%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001b0630_29\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x4(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_001b0630_30\n\t"
      ".LFUN_001b0630_29:\n\t"
      "pushl $1\n\t"
      "pushl $0xab3\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b78b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b0630_30:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x8(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001b0630_31\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0xc(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_001b0630_32\n\t"
      ".LFUN_001b0630_31:\n\t"
      "pushl $1\n\t"
      "pushl $0xab4\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b7850\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b0630_32:\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x44(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c10cc40]\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "call *%[c10cc40]\n\t"
      "flds -0x24(%%ebp)\n\t"
      "addl $0x10, %%esp\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x40(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x44(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fsts 0x18(%%ebp)\n\t"
      "fcomps 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b0630_33\n\t"
      "movl $0xbf800000, 0x18(%%ebp)\n\t"
      "jmp .LFUN_001b0630_34\n\t"
      ".LFUN_001b0630_33:\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b0630_34\n\t"
      "movl $0x3f800000, 0x18(%%ebp)\n\t"
      ".LFUN_001b0630_34:\n\t"
      "flds -0x24(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "fmuls -0x40(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps (%%esi)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x44(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x44(%%ebp)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x8(%%esi)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x18(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "call *%[c1d94f0]\n\t"
      "fcoms 0x1c(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b0630_35\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x1c(%%ebp)\n\t"
      ".LFUN_001b0630_35:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "fld %%st(0)\n\t"
      "testl %%eax, %%eax\n\t"
      "fmuls (%%esi)\n\t"
      "fstps (%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "fstps 0x8(%%esi)\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "je .LFUN_001b0630_36\n\t"
      "pushl %%esi\n\t"
      "leal -0x44(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c109680]\n\t"
      "pushl %%esi\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_001b0630_38\n\t"
      ".LFUN_001b0630_36:\n\t"
      "movl -0x44(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl -0x40(%%ebp), %%edx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x3c(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      ".LFUN_001b0630_37:\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      ".LFUN_001b0630_38:\n\t"
      "pushl %%esi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b0630_39\n\t"
      "flds 0x8(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0xae9\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b783c\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b0630_39:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1b0630_assert), [exitfn] "m"(b1b0630_exitfn), [c1097f0] "m"(b1b0630_c1097f0), [c10cc00] "m"(b1b0630_c10cc00), [c10cc40] "m"(b1b0630_c10cc40), [c109680] "m"(b1b0630_c109680), [norm] "m"(b1b0630_norm), [rots] "m"(b1b0630_rots), [c1ac680] "m"(b1b0630_c1ac680), [c1acb70] "m"(b1b0630_c1acb70), [c1a8550] "m"(b1b0630_c1a8550), [c1d94f0] "m"(b1b0630_c1d94f0), [c21fb0] "m"(b1b0630_c21fb0), [c8d9d0] "m"(b1b0630_c8d9d0)
      : "memory");
}
#else
#error "FUN_001b0630: clang naked draft required"
#endif

/* FUN_001b0d90 (0x1b0d90) — XBE naked draft (batch 56). */
#if defined(__clang__)
static void *(*const b1b0d90_get)(int, int) = object_get_and_verify_type;
static void *(*const b1b0d90_tag)(int, int) = tag_get;
static void (*const b1b0d90_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1b0d90_exitfn)(int) = system_exit;
static char (*const b1b0d90_c1a86b0)(void *anim_state, int16_t target_state) = FUN_001a86b0;
static char * (*const b1b0d90_c1ae700)(int unit_handle, int unused) = unit_get_weapon_name;
static const char * (*const b1b0d90_c1ab6e0)(int16_t base_seat_index) = FUN_001ab6e0;
static char (*const b1b0d90_c1acd70)(int unit_handle, const char *seat_label, const char *weapon_name, char apply_state) = FUN_001acd70;
static int16_t (*const b1b0d90_c1ab870)(void *animation_state, int animation_graph_tag_index, int unit_handle) = FUN_001ab870;
static void (*const b1b0d90_c1ab110)(int unit_handle, char flag) = FUN_001ab110;
static void (*const b1b0d90_c1ae840)(int unit_handle, char melee_hit, int target_handle, int param_4, int param_5, int param_6, int param_7) = unit_cause_melee_damage;
static void (*const b1b0d90_c1a91e0)(int unit_handle) = unit_destroy;
static void (*const b1b0d90_c1a0970)(int unit_handle) = biped_start_limp_body_physics;
static void *(*const b1b0d90_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1b0d90_c1234b0)(void *mode_tag, void *animation, int frame_index, float *out_delta) = FUN_001234b0;
static void * (*const b1b0d90_c141480)(int object_handle, void *out_matrix) = object_get_world_matrix;
static void (*const b1b0d90_mscale)(float *, float *, float *) = matrix_scale_transform_vector;
static void (*const b1b0d90_c1b2dd0)(int unit_handle) = unit_exit_seat_end;
static void (*const b1b0d90_c213c0)(float *a, float *b, float *out) = vector3d_add;
static void (*const b1b0d90_c13ffc0)(int object_handle, int flag) = object_set_garbage;
static void (*const b1b0d90_c1ae180)(int unit_handle) = unit_close;
static char (*const b1b0d90_c1a8790)(void *anim_state) = FUN_001a8790;
static void (*const b1b0d90_c140160)(int object_handle, int16_t region_count) = object_set_region_count;
static char (*const b1b0d90_c1ad260)(int unit_handle, int16_t anim_state) = FUN_001ad260;

__attribute__((naked, noinline))
short FUN_001b0d90(int unit_handle __attribute__((unused)), char *anim_state __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x50, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movsbw (%%ecx), %%ax\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jl .LFUN_001b0d90_1\n\t"
      "cmpw $0x2c, %%ax\n\t"
      "jl .LFUN_001b0d90_2\n\t"
      ".LFUN_001b0d90_1:\n\t"
      "pushl $1\n\t"
      "pushl $0xb61\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b7a60\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b0d90_2:\n\t"
      "movl 0xcc(%%edi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jne .LFUN_001b0d90_16\n\t"
      "testb $4, 0xb6(%%edi)\n\t"
      "jne .LFUN_001b0d90_16\n\t"
      "movsbl 0x256(%%edi), %%eax\n\t"
      "cmpl $6, %%eax\n\t"
      "ja .LFUN_001b0d90_6\n\t"
      "jmp *.LFUN_001b0d90_jt0(,%%eax,4)\n\t"
      ".LFUN_001b0d90_3:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "jmp .LFUN_001b0d90_7\n\t"
      ".LFUN_001b0d90_4:\n\t"
      "movl $1, %%ebx\n\t"
      "jmp .LFUN_001b0d90_7\n\t"
      ".LFUN_001b0d90_5:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movb 0x1(%%edx), %%cl\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testb %%cl, %%cl\n\t"
      "setne %%bl\n\t"
      "addl $2, %%ebx\n\t"
      "cmpw $-1, %%bx\n\t"
      "jne .LFUN_001b0d90_7\n\t"
      ".LFUN_001b0d90_6:\n\t"
      "pushl $1\n\t"
      "pushl $0xb73\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b7a40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b0d90_7:\n\t"
      "cmpl $-1, 0x1c8(%%edi)\n\t"
      "je .LFUN_001b0d90_12\n\t"
      "movl 0x32de80, %%eax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001b0d90_12\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .LFUN_001b0d90_11\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "jmp .LFUN_001b0d90_12\n\t"
      ".LFUN_001b0d90_8:\n\t"
      "movl $2, %%ebx\n\t"
      "jmp .LFUN_001b0d90_7\n\t"
      ".LFUN_001b0d90_9:\n\t"
      "movl $4, %%ebx\n\t"
      "jmp .LFUN_001b0d90_7\n\t"
      ".LFUN_001b0d90_10:\n\t"
      "movl $5, %%ebx\n\t"
      "jmp .LFUN_001b0d90_7\n\t"
      ".LFUN_001b0d90_11:\n\t"
      "cmpw $6, %%ax\n\t"
      "movl $6, %%ebx\n\t"
      "jg .LFUN_001b0d90_12\n\t"
      "movl %%eax, %%ebx\n\t"
      ".LFUN_001b0d90_12:\n\t"
      "movb 0x1bf(%%edi), %%al\n\t"
      "cmpb $0xff, %%al\n\t"
      "je .LFUN_001b0d90_13\n\t"
      "movsbw %%al, %%bx\n\t"
      ".LFUN_001b0d90_13:\n\t"
      "movl 0x1b8(%%edi), %%eax\n\t"
      "testb $2, %%ah\n\t"
      "je .LFUN_001b0d90_14\n\t"
      "movl $1, %%ebx\n\t"
      ".LFUN_001b0d90_14:\n\t"
      "movb 0x23b(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jbe .LFUN_001b0d90_15\n\t"
      "movl $5, %%ebx\n\t"
      ".LFUN_001b0d90_15:\n\t"
      "movsbw 0x257(%%edi), %%ax\n\t"
      "cmpw %%bx, %%ax\n\t"
      "je .LFUN_001b0d90_16\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "leal 0x248(%%edi), %%ecx\n\t"
      "call *%[c1a86b0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b0d90_16\n\t"
      "pushl $1\n\t"
      "call *%[c1ae700]\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, %%esi\n\t"
      "call *%[c1ab6e0]\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "call *%[c1acd70]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001b0d90_16:\n\t"
      "cmpw $-1, 0x262(%%edi)\n\t"
      "leal 0x262(%%edi), %%ebx\n\t"
      "je .LFUN_001b0d90_17\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0x44(%%edx), %%edx\n\t"
      "pushl %%esi\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[c1ab870]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .LFUN_001b0d90_17\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      ".LFUN_001b0d90_17:\n\t"
      "cmpw $-1, 0x80(%%edi)\n\t"
      "leal 0x80(%%edi), %%ecx\n\t"
      "je .LFUN_001b0d90_31\n\t"
      "movl 0x7c(%%edi), %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ab870]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .LFUN_001b0d90_20\n\t"
      "movsbl 0x253(%%edi), %%eax\n\t"
      "addl $-0x1e, %%eax\n\t"
      "cmpl $0xb, %%eax\n\t"
      "ja .LFUN_001b0d90_31\n\t"
      "movzbl 0x1b1254(%%eax), %%eax\n\t"
      "jmp *.LFUN_001b0d90_jt1(,%%eax,4)\n\t"
      ".LFUN_001b0d90_18:\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ab110]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_001b0d90_31\n\t"
      ".LFUN_001b0d90_19:\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ae840]\n\t"
      "addl $0x1c, %%esp\n\t"
      "jmp .LFUN_001b0d90_31\n\t"
      ".LFUN_001b0d90_20:\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .LFUN_001b0d90_31\n\t"
      "movsbl 0x253(%%edi), %%eax\n\t"
      "addl $-0x19, %%eax\n\t"
      "cmpl $0xe, %%eax\n\t"
      "ja .LFUN_001b0d90_30\n\t"
      "movzbl 0x1b1278(%%eax), %%ecx\n\t"
      "jmp *.LFUN_001b0d90_jt2(,%%ecx,4)\n\t"
      ".LFUN_001b0d90_21:\n\t"
      "movl $1, -0x10(%%ebp)\n\t"
      "movl $0x28, -0xc(%%ebp)\n\t"
      "jmp .LFUN_001b0d90_30\n\t"
      ".LFUN_001b0d90_22:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "testb $2, 0x17c(%%edx)\n\t"
      "je .LFUN_001b0d90_24\n\t"
      "testb $0x20, 0x4(%%edi)\n\t"
      "jne .LFUN_001b0d90_23\n\t"
      "cmpw $0, 0x64(%%edi)\n\t"
      "jne .LFUN_001b0d90_25\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movb 0x424(%%ebx), %%cl\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $1, %%cl\n\t"
      "je .LFUN_001b0d90_23\n\t"
      "movl 0x2f4(%%eax), %%ecx\n\t"
      "testb $4, %%ch\n\t"
      "je .LFUN_001b0d90_24\n\t"
      ".LFUN_001b0d90_23:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1a91e0]\n\t"
      "jmp .LFUN_001b0d90_29\n\t"
      ".LFUN_001b0d90_24:\n\t"
      "cmpw $0, 0x64(%%edi)\n\t"
      "jne .LFUN_001b0d90_25\n\t"
      "pushl %%esi\n\t"
      "call *%[c1a0970]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001b0d90_25:\n\t"
      "orb $4, 0x248(%%edi)\n\t"
      ".LFUN_001b0d90_26:\n\t"
      "decw 0x82(%%edi)\n\t"
      "jmp .LFUN_001b0d90_30\n\t"
      ".LFUN_001b0d90_27:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x34(%%ecx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x6d6f6465\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x7c(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x616e7472\n\t"
      "call *%[tag]\n\t"
      "movswl 0x80(%%edi), %%ecx\n\t"
      "pushl $0xb4\n\t"
      "pushl %%ecx\n\t"
      "addl $0x74, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x82(%%edi), %%cx\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1234b0]\n\t"
      "addl $0x2c, %%esp\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x50(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c141480]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[mscale]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1b2dd0]\n\t"
      "leal 0x18(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c213c0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "jmp .LFUN_001b0d90_30\n\t"
      ".LFUN_001b0d90_28:\n\t"
      "movl 0xcc(%%edi), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movswl 0x2a0(%%edi), %%edx\n\t"
      "pushl $0x11c\n\t"
      "pushl %%edx\n\t"
      "addl $0x2e4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movzbl (%%eax), %%eax\n\t"
      "notb %%al\n\t"
      "andl $0xffffff01, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c13ffc0]\n\t"
      "movl 0x2d4(%%ebx), %%eax\n\t"
      "addl $0x24, %%esp\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jne .LFUN_001b0d90_30\n\t"
      "movl 0xcc(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ae180]\n\t"
      ".LFUN_001b0d90_29:\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001b0d90_30:\n\t"
      "leal 0x248(%%edi), %%ecx\n\t"
      "call *%[c1a8790]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b0d90_31\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_001b0d90_31:\n\t"
      "cmpw $-1, 0x25a(%%edi)\n\t"
      "leal 0x25a(%%edi), %%ecx\n\t"
      "je .LFUN_001b0d90_32\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0x44(%%edx), %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ab870]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .LFUN_001b0d90_32\n\t"
      "pushl $6\n\t"
      "pushl %%esi\n\t"
      "call *%[c140160]\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "addl $0x10, %%esp\n\t"
      "movb $0, 0x254(%%eax)\n\t"
      "movw $0xffff, 0x25a(%%eax)\n\t"
      ".LFUN_001b0d90_32:\n\t"
      "cmpw $-1, 0x25e(%%edi)\n\t"
      "leal 0x25e(%%edi), %%ebx\n\t"
      "je .LFUN_001b0d90_35\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x44(%%eax), %%edx\n\t"
      "pushl %%esi\n\t"
      "movl %%ebx, %%ecx\n\t"
      "call *%[c1ab870]\n\t"
      "movswl %%ax, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "subl $2, %%eax\n\t"
      "je .LFUN_001b0d90_33\n\t"
      "subl $2, %%eax\n\t"
      "jne .LFUN_001b0d90_35\n\t"
      ".LFUN_001b0d90_33:\n\t"
      "movb 0x253(%%edi), %%al\n\t"
      "cmpb $3, %%al\n\t"
      "jl .LFUN_001b0d90_34\n\t"
      "cmpb $4, %%al\n\t"
      "jle .LFUN_001b0d90_35\n\t"
      ".LFUN_001b0d90_34:\n\t"
      "movb $0, 0x255(%%edi)\n\t"
      "movw $0xffff, (%%ebx)\n\t"
      ".LFUN_001b0d90_35:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "popl %%ebx\n\t"
      "jne .LFUN_001b0d90_36\n\t"
      "movsbw 0x253(%%edi), %%cx\n\t"
      "cmpw %%cx, %%dx\n\t"
      "je .LFUN_001b0d90_37\n\t"
      "leal 0x248(%%edi), %%ecx\n\t"
      "call *%[c1a86b0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b0d90_37\n\t"
      ".LFUN_001b0d90_36:\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ad260]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001b0d90_37:\n\t"
      "movw -0x10(%%ebp), %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      "addb %%al, (%%eax)\n\t"
      "addb (%%ecx), %%al\n\t"
      "addb (%%edx), %%al\n\t"
      "addb (%%edx), %%al\n\t"
      "addb (%%edx), %%al\n\t"
      "addb (%%eax), %%al\n\t"
      "addb %%al, (%%ecx)\n\t"
      "addb 0x5050505, %%al\n\t"
      "addl $0x3050505, %%eax\n\t"
      "addl (%%eax,%%edx,4), %%eax\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_001b0d90_jt0:\n\t"
      ".long .LFUN_001b0d90_3\n\t"
      ".long .LFUN_001b0d90_4\n\t"
      ".long .LFUN_001b0d90_4\n\t"
      ".long .LFUN_001b0d90_5\n\t"
      ".long .LFUN_001b0d90_8\n\t"
      ".long .LFUN_001b0d90_9\n\t"
      ".long .LFUN_001b0d90_10\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_001b0d90_jt1:\n\t"
      ".long .LFUN_001b0d90_19\n\t"
      ".long .LFUN_001b0d90_18\n\t"
      ".long .LFUN_001b0d90_31\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_001b0d90_jt2:\n\t"
      ".long .LFUN_001b0d90_22\n\t"
      ".long .LFUN_001b0d90_28\n\t"
      ".long .LFUN_001b0d90_27\n\t"
      ".long .LFUN_001b0d90_26\n\t"
      ".long .LFUN_001b0d90_21\n\t"
      ".long .LFUN_001b0d90_30\n\t"
      ".text\n\t"
      :
      : [get] "m"(b1b0d90_get), [tag] "m"(b1b0d90_tag), [assert] "m"(b1b0d90_assert), [exitfn] "m"(b1b0d90_exitfn), [c1a86b0] "m"(b1b0d90_c1a86b0), [c1ae700] "m"(b1b0d90_c1ae700), [c1ab6e0] "m"(b1b0d90_c1ab6e0), [c1acd70] "m"(b1b0d90_c1acd70), [c1ab870] "m"(b1b0d90_c1ab870), [c1ab110] "m"(b1b0d90_c1ab110), [c1ae840] "m"(b1b0d90_c1ae840), [c1a91e0] "m"(b1b0d90_c1a91e0), [c1a0970] "m"(b1b0d90_c1a0970), [elem] "m"(b1b0d90_elem), [c1234b0] "m"(b1b0d90_c1234b0), [c141480] "m"(b1b0d90_c141480), [mscale] "m"(b1b0d90_mscale), [c1b2dd0] "m"(b1b0d90_c1b2dd0), [c213c0] "m"(b1b0d90_c213c0), [c13ffc0] "m"(b1b0d90_c13ffc0), [c1ae180] "m"(b1b0d90_c1ae180), [c1a8790] "m"(b1b0d90_c1a8790), [c140160] "m"(b1b0d90_c140160), [c1ad260] "m"(b1b0d90_c1ad260)
      : "memory");
}
#else
#error "FUN_001b0d90: clang naked draft required"
#endif


/* FUN_001b1400 (0x1b1400) — XBE naked draft (batch 48). */
#if defined(__clang__)
static void *(*const b1b1400_get)(int, int) = object_get_and_verify_type;
static void *(*const b1b1400_tag)(int, int) = tag_get;
static bool (*const b1b1400_gerun)(void) = game_engine_running;
static void (*const b1b1400_c120670)(void) = build_damage_animation_index;
static int (*const b1b1400_c120f20)(int update_kind, int animation_graph_tag_index, int16_t animation_index) = model_animation_choose_random;
static char * (*const b1b1400_c1ae700)(int unit_handle, int unused) = unit_get_weapon_name;
static char (*const b1b1400_c1acd70)(int unit_handle, const char *seat_label, const char *weapon_name, char apply_state) = FUN_001acd70;
static char (*const b1b1400_c1ad260)(int unit_handle, int16_t anim_state) = FUN_001ad260;
static char (*const b1b1400_c1a86b0)(void *anim_state, int16_t target_state) = FUN_001a86b0;
static void (*const b1b1400_c1ab110)(int unit_handle, char flag) = FUN_001ab110;
static void (*const b1b1400_c140160)(int object_handle, int16_t region_count) = object_set_region_count;
static void (*const b1b1400_c1ab7c0)(int unit_handle, int anim_graph_tag_index, int16_t animation_index) = unit_set_animation;
static void *(*const b1b1400_elem)(void *, int, int) = tag_block_get_element;
static int16_t (*const b1b1400_c17940)(int16_t min, int16_t max) = FUN_00017940;
static void (*const b1b1400_c1a91e0)(int unit_handle) = unit_destroy;
static void (*const b1b1400_c1af180)(int unit_handle, float *alignment_vector) = unit_apply_alignment_vector;
static void (*const b1b1400_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1b1400_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_001b1400(int unit_handle __attribute__((unused)), char is_melee __attribute__((unused)), char is_throw __attribute__((unused)), char is_airborne __attribute__((unused)), char is_ground __attribute__((unused)), char is_ping __attribute__((unused)), float throttle_magnitude __attribute__((unused)), int weapon_class __attribute__((unused)), int alignment_vector __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "xorl %%edx, %%edx\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b1400_1\n\t"
      "flds 0x228(%%ecx)\n\t"
      "movb %%dl, 0x10(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b1400_6\n\t"
      "flds 0x9c(%%ebx)\n\t"
      "fcomps 0x228(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b1400_6\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_001b1400_7\n\t"
      ".LFUN_001b1400_1:\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b1400_2\n\t"
      "movb $1, %%al\n\t"
      "movb %%al, 0xc(%%ebp)\n\t"
      "movb %%al, -0x2(%%ebp)\n\t"
      "jmp .LFUN_001b1400_6\n\t"
      ".LFUN_001b1400_2:\n\t"
      "flds 0x9c(%%ebx)\n\t"
      "fcomps 0x218(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001b1400_3\n\t"
      "flds 0x98(%%ebx)\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "fcomps 0x218(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b1400_4\n\t"
      ".LFUN_001b1400_3:\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      ".LFUN_001b1400_4:\n\t"
      "flds 0x9c(%%ebx)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "fcomps 0x220(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001b1400_5\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_001b1400_5:\n\t"
      "movb 0x18(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b1400_6\n\t"
      "movb 0x1b4(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jns .LFUN_001b1400_7\n\t"
      ".LFUN_001b1400_6:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_001b1400_7:\n\t"
      "movb 0x1c(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b1400_8\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      ".LFUN_001b1400_8:\n\t"
      "cmpw $-1, 0x24(%%ebp)\n\t"
      "jne .LFUN_001b1400_9\n\t"
      "movl %%edx, 0x24(%%ebp)\n\t"
      ".LFUN_001b1400_9:\n\t"
      "flds 0x20(%%ebp)\n\t"
      "movl $2, %%esi\n\t"
      "fabs\n\t"
      "fcoml 0x25b3f0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b1400_10\n\t"
      "fstp %%st(0)\n\t"
      "movl $3, 0x1c(%%ebp)\n\t"
      "jmp .LFUN_001b1400_12\n\t"
      ".LFUN_001b1400_10:\n\t"
      "fcompl 0x2b7a98\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b1400_11\n\t"
      "movl %%edx, 0x1c(%%ebp)\n\t"
      "jmp .LFUN_001b1400_12\n\t"
      ".LFUN_001b1400_11:\n\t"
      "flds 0x20(%%ebp)\n\t"
      "movl $1, 0x1c(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001b1400_12\n\t"
      "movl %%esi, 0x1c(%%ebp)\n\t"
      ".LFUN_001b1400_12:\n\t"
      "call *%[gerun]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b1400_13\n\t"
      "cmpw %%si, 0x24(%%ebp)\n\t"
      "jne .LFUN_001b1400_13\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b1400_13\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b1400_13\n\t"
      "movl $1, 0x1c(%%ebp)\n\t"
      ".LFUN_001b1400_13:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b1400_14\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b1400_47\n\t"
      ".LFUN_001b1400_14:\n\t"
      "movl (%%ebx), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x44(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x616e7472\n\t"
      "movl %%edi, 0x20(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movb 0xc(%%ebp), %%cl\n\t"
      "movl %%eax, %%esi\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "jne .LFUN_001b1400_18\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_001b1400_18\n\t"
      "cmpw $-1, 0x262(%%ebx)\n\t"
      "je .LFUN_001b1400_15\n\t"
      "movw 0x264(%%ebx), %%cx\n\t"
      "cmpw 0x2c8(%%edi), %%cx\n\t"
      "jle .LFUN_001b1400_46\n\t"
      ".LFUN_001b1400_15:\n\t"
      "movl 0x24(%%ebp), %%edx\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c120670]\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_001b1400_16\n\t"
      "movl 0x3c(%%esi), %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .LFUN_001b1400_16\n\t"
      "movl 0x40(%%esi), %%ecx\n\t"
      "movswl (%%ecx,%%eax,2), %%ecx\n\t"
      "jmp .LFUN_001b1400_17\n\t"
      ".LFUN_001b1400_16:\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      ".LFUN_001b1400_17:\n\t"
      "movl 0x44(%%edi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c120f20]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001b1400_46\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x262(%%ebx)\n\t"
      "movw $0, 0x264(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001b1400_18:\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "setne %%al\n\t"
      "testb %%cl, %%cl\n\t"
      "leal 0x17(%%eax,%%eax,1), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "je .LFUN_001b1400_26\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "xorl %%edx, %%edx\n\t"
      "testb %%cl, %%cl\n\t"
      "setne %%dl\n\t"
      "addl $2, %%edx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      ".LFUN_001b1400_19:\n\t"
      "movb $1, %%al\n\t"
      ".LFUN_001b1400_20:\n\t"
      "cmpb $0x17, 0x253(%%ebx)\n\t"
      "jne .LFUN_001b1400_21\n\t"
      "movw 0x82(%%ebx), %%cx\n\t"
      "cmpw 0x2ca(%%edi), %%cx\n\t"
      "jle .LFUN_001b1400_21\n\t"
      "movb $1, %%al\n\t"
      ".LFUN_001b1400_21:\n\t"
      "movb 0xc(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_001b1400_23\n\t"
      "testb $4, 0xb6(%%ebx)\n\t"
      "je .LFUN_001b1400_22\n\t"
      "xorb %%al, %%al\n\t"
      ".LFUN_001b1400_22:\n\t"
      "cmpl $-1, 0xcc(%%ebx)\n\t"
      "jne .LFUN_001b1400_46\n\t"
      ".LFUN_001b1400_23:\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b1400_46\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_001b1400_24\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0x32e48c, %%edi\n\t"
      "pushl $1\n\t"
      "call *%[c1ae700]\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c1acd70]\n\t"
      "movl 0x20(%%ebp), %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001b1400_24:\n\t"
      "cmpw $0x19, -0xc(%%ebp)\n\t"
      "jne .LFUN_001b1400_25\n\t"
      "cmpw $0, 0x64(%%ebx)\n\t"
      "jne .LFUN_001b1400_25\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movb 0x424(%%esi), %%cl\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $1, %%cl\n\t"
      "je .LFUN_001b1400_25\n\t"
      "movl 0x2f4(%%eax), %%ecx\n\t"
      "testb $4, %%ch\n\t"
      "jne .LFUN_001b1400_25\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0x18\n\t"
      "pushl %%ecx\n\t"
      "movl $0x18, -0xc(%%ebp)\n\t"
      "call *%[c1ad260]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b1400_39\n\t"
      "movl 0x20(%%ebp), %%edi\n\t"
      ".LFUN_001b1400_25:\n\t"
      "movl 0x24(%%ebp), %%edx\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c120670]\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_001b1400_27\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl 0x3c(%%ecx), %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jge .LFUN_001b1400_27\n\t"
      "movl 0x40(%%ecx), %%edx\n\t"
      "movswl (%%edx,%%eax,2), %%ecx\n\t"
      "jmp .LFUN_001b1400_28\n\t"
      ".LFUN_001b1400_26:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "leal 0x248(%%ebx), %%ecx\n\t"
      "movl $1, -0x14(%%ebp)\n\t"
      "call *%[c1a86b0]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b1400_19\n\t"
      "jmp .LFUN_001b1400_20\n\t"
      ".LFUN_001b1400_27:\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      ".LFUN_001b1400_28:\n\t"
      "movl 0x44(%%edi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c120f20]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpw $-1, %%si\n\t"
      "je .LFUN_001b1400_38\n\t"
      "cmpb $0x21, 0x253(%%ebx)\n\t"
      "jne .LFUN_001b1400_29\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ab110]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001b1400_29:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "call *%[c140160]\n\t"
      "movb -0xc(%%ebp), %%dl\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "movb %%dl, 0x253(%%ebx)\n\t"
      "movl 0x44(%%eax), %%edi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "movl %%esi, %%ebx\n\t"
      "call *%[c1ab7c0]\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "orb $1, 0x248(%%edi)\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b1400_32\n\t"
      "movb 0x14(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b1400_31\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b1400_31\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "movswl %%si, %%ecx\n\t"
      "pushl $0xb4\n\t"
      "pushl %%ecx\n\t"
      "leal 0x74(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movswl 0x22(%%eax), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw %%ax, %%cx\n\t"
      "sarw $2, %%cx\n\t"
      "sarw $1, %%ax\n\t"
      "addl %%ecx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17940]\n\t"
      "addl $0x14, %%esp\n\t"
      "movb %%al, 0x23c(%%edi)\n\t"
      "cmpb $1, %%al\n\t"
      "movsbl %%al, %%eax\n\t"
      "jg .LFUN_001b1400_30\n\t"
      "movl $1, %%eax\n\t"
      ".LFUN_001b1400_30:\n\t"
      "movb %%al, 0x23c(%%edi)\n\t"
      "jmp .LFUN_001b1400_33\n\t"
      ".LFUN_001b1400_31:\n\t"
      "movb $0, 0x23c(%%edi)\n\t"
      ".LFUN_001b1400_32:\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      ".LFUN_001b1400_33:\n\t"
      "cmpw $0, 0x1c(%%ebp)\n\t"
      "je .LFUN_001b1400_36\n\t"
      "movswl %%si, %%eax\n\t"
      "pushl $0xb4\n\t"
      "pushl %%eax\n\t"
      "leal 0x74(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0x24(%%ebp), %%edi\n\t"
      "movl -0x14(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "call *%[c120670]\n\t"
      "addl $0x18, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_001b1400_34\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c120670]\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl 0x3c(%%ebx), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jge .LFUN_001b1400_34\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c120670]\n\t"
      "movl 0x40(%%ebx), %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "movswl (%%ecx,%%eax,2), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_001b1400_35\n\t"
      ".LFUN_001b1400_34:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      ".LFUN_001b1400_35:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movswl 0x42(%%edx), %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jne .LFUN_001b1400_36\n\t"
      "movl $0, 0x1c(%%ebp)\n\t"
      ".LFUN_001b1400_36:\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "je .LFUN_001b1400_39\n\t"
      "cmpw $3, 0x1c(%%ebp)\n\t"
      "movl %%ebx, %%eax\n\t"
      "jne .LFUN_001b1400_37\n\t"
      "orb $8, 0x248(%%eax)\n\t"
      "jmp .LFUN_001b1400_39\n\t"
      ".LFUN_001b1400_37:\n\t"
      "andb $0xf7, 0x248(%%eax)\n\t"
      "jmp .LFUN_001b1400_39\n\t"
      ".LFUN_001b1400_38:\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b1400_39\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x248(%%ebx), %%dx\n\t"
      "andl $0xfff7, %%edx\n\t"
      "orl $4, %%edx\n\t"
      "movw %%dx, 0x248(%%ebx)\n\t"
      "testb $2, 0x17c(%%eax)\n\t"
      "je .LFUN_001b1400_39\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1a91e0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001b1400_39:\n\t"
      "movl 0x28(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_001b1400_46\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "movl 0x17c(%%edx), %%eax\n\t"
      "testb $2, %%ah\n\t"
      "jne .LFUN_001b1400_46\n\t"
      "cmpw $0, 0x64(%%ebx)\n\t"
      "jne .LFUN_001b1400_46\n\t"
      "cmpl $-1, 0xcc(%%ebx)\n\t"
      "jne .LFUN_001b1400_46\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b1400_40\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b1400_46\n\t"
      ".LFUN_001b1400_40:\n\t"
      "movswl 0x1c(%%ebp), %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LFUN_001b1400_45\n\t"
      "jmp *.LFUN_001b1400_jt(,%%eax,4)\n\t"
      ".LFUN_001b1400_41:\n\t"
      "movl (%%ecx), %%eax\n\t"
      "movl 0x4(%%ecx), %%ecx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "call *%[c1af180]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001b1400_42:\n\t"
      "flds (%%ecx)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "fchs\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "fchs\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "call *%[c1af180]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001b1400_43:\n\t"
      "flds 0x4(%%ecx)\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "fchs\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "call *%[c1af180]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001b1400_44:\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "flds (%%ecx)\n\t"
      "fchs\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "call *%[c1af180]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001b1400_45:\n\t"
      "pushl $1\n\t"
      "pushl $0x11d2\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "call *%[c1af180]\n\t"
      ".LFUN_001b1400_46:\n\t"
      "popl %%edi\n\t"
      ".LFUN_001b1400_47:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_001b1400_jt:\n\t"
      ".long .LFUN_001b1400_42\n\t"
      ".long .LFUN_001b1400_43\n\t"
      ".long .LFUN_001b1400_44\n\t"
      ".long .LFUN_001b1400_41\n\t"
      ".text\n\t"
      :
      : [get] "m"(b1b1400_get), [tag] "m"(b1b1400_tag), [gerun] "m"(b1b1400_gerun), [c120670] "m"(b1b1400_c120670), [c120f20] "m"(b1b1400_c120f20), [c1ae700] "m"(b1b1400_c1ae700), [c1acd70] "m"(b1b1400_c1acd70), [c1ad260] "m"(b1b1400_c1ad260), [c1a86b0] "m"(b1b1400_c1a86b0), [c1ab110] "m"(b1b1400_c1ab110), [c140160] "m"(b1b1400_c140160), [c1ab7c0] "m"(b1b1400_c1ab7c0), [elem] "m"(b1b1400_elem), [c17940] "m"(b1b1400_c17940), [c1a91e0] "m"(b1b1400_c1a91e0), [c1af180] "m"(b1b1400_c1af180), [assert] "m"(b1b1400_assert), [exitfn] "m"(b1b1400_exitfn)
      : "memory");
}
#else
#error "FUN_001b1400: clang naked draft required"
#endif

/* FUN_001b3690 (0x1b3690) — XBE naked draft (batch 50). */
#if defined(__clang__)
static void *(*const b1b3690_get)(int, int) = object_get_and_verify_type;
static void *(*const b1b3690_tag)(int, int) = tag_get;
static char (*const b1b3690_cab9e0)(void) = FUN_000ab9e0;
static void (*const b1b3690_penter)(void *) = profile_enter_private;
static void (*const b1b3690_c1af6b0)(int unit_handle, const char *label) = unit_control_trace;
static void (*const b1b3690_c1af340)(int unit_handle, float *run_vector) = unit_update_running_blind;
static bool (*const b1b3690_c21fb0)(float *v) = valid_real_normal3d;
static char * (*const b1b3690_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b1b3690_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1b3690_exitfn)(int) = system_exit;
static bool (*const b1b3690_gerun)(void) = game_engine_running;
static int (*const b1b3690_c1adeb0)(int unit_handle, int16_t weapon_index) = unit_get_weapon;
static bool (*const b1b3690_c1ae600)(int unit_handle, bool flag) = unit_set_in_vehicle;
static void (*const b1b3690_c1adf10)(int unit_handle, char param_2) = unit_set_actively_controlled;
static char (*const b1b3690_c1acd70)(int unit_handle, const char *seat_label, const char *weapon_name, char apply_state) = FUN_001acd70;
static char (*const b1b3690_c1ad260)(int unit_handle, int16_t anim_state) = FUN_001ad260;
static void (*const b1b3690_c1a09f0)(int unit_handle) = biped_stop_limp_body_physics;
static char (*const b1b3690_c1a74d0)(int unit_handle, int scream_type) = FUN_001a74d0;
static void (*const b1b3690_c1b3060)(int unit_handle, char feign_death) = unit_died;
static char (*const b1b3690_c1a8730)(void *anim_state) = FUN_001a8730;
static bool (*const b1b3690_c1ae370)(int unit_handle, int seat_object_handle) = unit_can_enter_seat;
static void (*const b1b3690_c1b1ee0)(int unit_handle, int flag) = unit_update_weapon_readiness;
static int16_t (*const b1b3690_c1a9980)(int unit_handle, int current_index, int16_t direction) = unit_inventory_next_grenade;
static int (*const b1b3690_cba500)(int) = player_index_from_unit_index;
static void *(*const b1b3690_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const b1b3690_c1c7480)(int sound_tag_index, float scale) = sound_impulse_start;
static char (*const b1b3690_c1ada90)(int unit_handle, float *vector, char flag) = unit_clip_to_aiming_bounds;
static void (*const b1b3690_c141360)(int object_handle, float *out_forward, float *out_up) = object_get_orientation;
static void (*const b1b3690_c1b0630)(int transform_matrix, float *aiming_vector, float *desired_vector, float *angular_velocity, float *aiming_bounds, float angular_velocity_limit, float angular_acceleration_limit) = FUN_001b0630;
static void (*const b1b3690_c10f770)(float *facing, float *target_facing, float *ang_vel, float max_ang_speed, float ang_accel) = angular_accelerate_to_position;
static float (*const b1b3690_c10c510)(float *v1, float *v2) = FUN_0010c510;
static void (*const b1b3690_ftol)(void) = FUN_001d9068;
static char (*const b1b3690_c1b2090)(int unit_handle, float *alignment_vector) = unit_throw_grenade_begin;
static void (*const b1b3690_c1aaf40)(int unit_handle) = FUN_001aaf40;
static void (*const b1b3690_c1ab110)(int unit_handle, char flag) = FUN_001ab110;
static void (*const b1b3690_cfaeb0)(int weapon_handle, int light_power) = weapon_set_integrated_light_power;
static void (*const b1b3690_cfc4b0)(int weapon_handle, int16_t owner_state, float t) = weapon_owner_update;
static bool (*const b1b3690_c84a70)(float *a, float *b) = valid_real_normal3d_perpendicular;
static void (*const b1b3690_c1ab410)(int unit_handle) = unit_aiming_vector;
static void *(*const b1b3690_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1b3690_c40460)(int victim_handle, int source_handle, int16_t damage_type, float damage_amount, int param_4, char skip_provoke) = ai_handle_damage;
static void (*const b1b3690_c1abd90)(int unit_handle) = FUN_001abd90;
static void (*const b1b3690_c1a7790)(int unit_handle) = FUN_001a7790;
static void (*const b1b3690_c1ab8c0)(int unit_handle) = FUN_001ab8c0;
static int (*const b1b3690_gtime)(void) = game_time_get;
static void (*const b1b3690_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b1b3690_c1ac550)(int unit_handle) = unit_flame_to_death;
static void * (*const b1b3690_c18e450)(void) = game_globals_get;
static int (*const b1b3690_o9ec30)(int, int, int, short, float, float, int, int) = FUN_0009ec30;
static void (*const b1b3690_pexit)(void *) = profile_exit_private;

__attribute__((naked, noinline))
char FUN_001b3690(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x58, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "xorl %%esi, %%esi\n\t"
      "movb $0, -0x3(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movb $0, -0x4(%%ebp)\n\t"
      "call *%[cab9e0]\n\t"
      "movb %%al, -0x5(%%ebp)\n\t"
      "movb 0x449ef1, %%al\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b3690_1\n\t"
      "movb 0x32de90, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b3690_1\n\t"
      "pushl $0x32de88\n\t"
      "call *%[penter]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001b3690_1:\n\t"
      "pushl $0x2b7c98\n\t"
      "call *%[c1af6b0]\n\t"
      "movl 0x4e4cf8, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "incw 0x1bc(%%ebx)\n\t"
      "movb 0x4(%%eax), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "movw 0x1bc(%%ebx), %%cx\n\t"
      "jne .LFUN_001b3690_2\n\t"
      "cmpw (%%eax), %%cx\n\t"
      "jle .LFUN_001b3690_2\n\t"
      "movb $1, 0x4(%%eax)\n\t"
      "movb $1, -0x3(%%ebp)\n\t"
      "movw %%si, 0x1bc(%%ebx)\n\t"
      "jmp .LFUN_001b3690_5\n\t"
      ".LFUN_001b3690_2:\n\t"
      "movw 0x2(%%eax), %%dx\n\t"
      "cmpw %%cx, %%dx\n\t"
      "jle .LFUN_001b3690_3\n\t"
      "movswl %%dx, %%ecx\n\t"
      "jmp .LFUN_001b3690_4\n\t"
      ".LFUN_001b3690_3:\n\t"
      "movswl %%cx, %%ecx\n\t"
      ".LFUN_001b3690_4:\n\t"
      "movw %%cx, 0x2(%%eax)\n\t"
      ".LFUN_001b3690_5:\n\t"
      "movl 0x1b4(%%ebx), %%eax\n\t"
      "testl $0x2000000, %%eax\n\t"
      "je .LFUN_001b3690_6\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal 0x1d4(%%ebx), %%esi\n\t"
      "call *%[c1af340]\n\t"
      "movl %%esi, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "leal 0x1e0(%%ebx), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "leal 0x204(%%ebx), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl 0x31fc3c, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal 0x228(%%ebx), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl $0, 0x1b8(%%ebx)\n\t"
      "jmp .LFUN_001b3690_7\n\t"
      ".LFUN_001b3690_6:\n\t"
      "testb $1, %%al\n\t"
      "jne .LFUN_001b3690_7\n\t"
      "leal 0x24(%%ebx), %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "movl (%%edx), %%edi\n\t"
      "leal 0x204(%%ebx), %%ecx\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%edi\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edi, 0x4(%%ecx)\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl %%eax, %%edx\n\t"
      "movl (%%edx), %%edi\n\t"
      "leal 0x1e0(%%ebx), %%ecx\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%edi\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edi, 0x4(%%ecx)\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0x1d4(%%ebx), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movl 0x31fc38, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "leal 0x228(%%ebx), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl %%esi, 0x1b8(%%ebx)\n\t"
      ".LFUN_001b3690_7:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl 0x17c(%%eax), %%ecx\n\t"
      "testb $8, %%ch\n\t"
      "jne .LFUN_001b3690_35\n\t"
      "movl 0x1c0(%%ebx), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "jle .LFUN_001b3690_12\n\t"
      "movl 0x1c4(%%ebx), %%eax\n\t"
      "movl 0x1b8(%%ebx), %%edi\n\t"
      "orl %%eax, %%edi\n\t"
      "testb $8, %%ah\n\t"
      "movl %%edi, 0x1b8(%%ebx)\n\t"
      "movl %%edi, %%ecx\n\t"
      "je .LFUN_001b3690_10\n\t"
      "movl %%esi, %%eax\n\t"
      "cdq\n\t"
      "movl $7, %%edi\n\t"
      "idivl %%edi\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .LFUN_001b3690_8\n\t"
      "orl $0x800, %%ecx\n\t"
      "jmp .LFUN_001b3690_9\n\t"
      ".LFUN_001b3690_8:\n\t"
      "andl $0xfffff7ff, %%ecx\n\t"
      ".LFUN_001b3690_9:\n\t"
      "movl %%ecx, 0x1b8(%%ebx)\n\t"
      "movl $0x3f800000, 0x234(%%ebx)\n\t"
      "jmp .LFUN_001b3690_11\n\t"
      ".LFUN_001b3690_10:\n\t"
      "movl $0, 0x234(%%ebx)\n\t"
      ".LFUN_001b3690_11:\n\t"
      "leal -0x1(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x1c0(%%ebx)\n\t"
      "jne .LFUN_001b3690_12\n\t"
      "movl %%eax, 0x1c4(%%ebx)\n\t"
      ".LFUN_001b3690_12:\n\t"
      "testl $0x8000000, 0x1b4(%%ebx)\n\t"
      "jne .LFUN_001b3690_21\n\t"
      "movl 0x2d4(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001b3690_15\n\t"
      "testb $4, 0xb6(%%ebx)\n\t"
      "jne .LFUN_001b3690_15\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movw 0x68(%%esi), %%cx\n\t"
      "movw %%cx, 0x68(%%ebx)\n\t"
      "movl 0x1c8(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "jne .LFUN_001b3690_13\n\t"
      "movb 0x253(%%esi), %%al\n\t"
      "cmpb $0x1b, %%al\n\t"
      "je .LFUN_001b3690_15\n\t"
      "cmpb $0x1a, %%al\n\t"
      "je .LFUN_001b3690_15\n\t"
      ".LFUN_001b3690_13:\n\t"
      "leal 0x1d4(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b3690_14\n\t"
      "flds 0x1dc(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x2b8\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x1d8(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b7c6c\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b3690_14:\n\t"
      "movl 0x1b8(%%esi), %%edx\n\t"
      "movl 0x1b8(%%ebx), %%eax\n\t"
      "andl $0x3f, %%edx\n\t"
      "orl %%edx, %%eax\n\t"
      "movl %%eax, 0x1b8(%%ebx)\n\t"
      "movl (%%edi), %%ecx\n\t"
      "leal 0x1d4(%%ebx), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "addl $0x228, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "leal 0x228(%%ebx), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      ".LFUN_001b3690_15:\n\t"
      "movl 0x2d8(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001b3690_19\n\t"
      "testb $4, 0xb6(%%ebx)\n\t"
      "jne .LFUN_001b3690_19\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b3690_16\n\t"
      "movw 0x68(%%esi), %%cx\n\t"
      "movw %%cx, 0x68(%%ebx)\n\t"
      ".LFUN_001b3690_16:\n\t"
      "cmpl $-1, 0x1c8(%%esi)\n\t"
      "jne .LFUN_001b3690_17\n\t"
      "movb 0x253(%%esi), %%al\n\t"
      "cmpb $0x1b, %%al\n\t"
      "je .LFUN_001b3690_19\n\t"
      "cmpb $0x1a, %%al\n\t"
      "je .LFUN_001b3690_19\n\t"
      ".LFUN_001b3690_17:\n\t"
      "leal 0x1e0(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b3690_18\n\t"
      "flds 0x1e8(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x2d0\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x1e4(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b7c40\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b3690_18:\n\t"
      "movl %%edi, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal 0x1e0(%%ebx), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl (%%edi), %%edx\n\t"
      "leal 0x204(%%ebx), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl 0x1b8(%%esi), %%eax\n\t"
      "movl 0x1b8(%%ebx), %%ecx\n\t"
      "andl $0x7c00, %%eax\n\t"
      "orl %%eax, %%ecx\n\t"
      "movl %%ecx, 0x1b8(%%ebx)\n\t"
      "movl 0x234(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x234(%%ebx)\n\t"
      ".LFUN_001b3690_19:\n\t"
      "movl 0x1b8(%%ebx), %%eax\n\t"
      "testb $0x7c, %%ah\n\t"
      "je .LFUN_001b3690_20\n\t"
      "movb $0, 0x2d2(%%ebx)\n\t"
      "jmp .LFUN_001b3690_21\n\t"
      ".LFUN_001b3690_20:\n\t"
      "movb 0x2d2(%%ebx), %%al\n\t"
      "cmpb $0x7f, %%al\n\t"
      "jge .LFUN_001b3690_21\n\t"
      "incb %%al\n\t"
      "movb %%al, 0x2d2(%%ebx)\n\t"
      ".LFUN_001b3690_21:\n\t"
      "movb 0x5aa891, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b3690_22\n\t"
      "movl 0x1b8(%%ebx), %%eax\n\t"
      "testb $8, %%ah\n\t"
      "je .LFUN_001b3690_22\n\t"
      "testb $0x20, %%ah\n\t"
      "je .LFUN_001b3690_22\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_001b3690_22:\n\t"
      "testb $0x10, 0x1b4(%%ebx)\n\t"
      "je .LFUN_001b3690_26\n\t"
      "call *%[gerun]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b3690_23\n\t"
      "movw 0x3d2(%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_001b3690_23\n\t"
      "cmpw $1, %%ax\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "jne .LFUN_001b3690_24\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2a2(%%eax), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1adeb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001b3690_24\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x77656170\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x4d0(%%ecx)\n\t"
      "addl $0x10, %%esp\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_001b3690_24\n\t"
      "flds 0x4d0(%%ecx)\n\t"
      "jmp .LFUN_001b3690_25\n\t"
      ".LFUN_001b3690_23:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      ".LFUN_001b3690_24:\n\t"
      "flds 0x28ac20\n\t"
      ".LFUN_001b3690_25:\n\t"
      "fadds 0x32c(%%ebx)\n\t"
      "fsts 0x32c(%%ebx)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b3690_27\n\t"
      "movl $0x3f800000, 0x32c(%%ebx)\n\t"
      "movw $0, 0x3d2(%%ebx)\n\t"
      "jmp .LFUN_001b3690_27\n\t"
      ".LFUN_001b3690_26:\n\t"
      "flds 0x32c(%%ebx)\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "fsubs 0x28ac20\n\t"
      "fsts 0x32c(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b3690_27\n\t"
      "movl $0, 0x32c(%%ebx)\n\t"
      ".LFUN_001b3690_27:\n\t"
      "movb 0x1b4(%%ebx), %%al\n\t"
      "flds 0x330(%%ebx)\n\t"
      "testb $0x20, %%al\n\t"
      "je .LFUN_001b3690_28\n\t"
      "fadds 0x26f2e0\n\t"
      "fsts 0x330(%%ebx)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b3690_29\n\t"
      "movl $0x3f800000, 0x330(%%ebx)\n\t"
      "jmp .LFUN_001b3690_29\n\t"
      ".LFUN_001b3690_28:\n\t"
      "fsubs 0x26f2e0\n\t"
      "fsts 0x330(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b3690_29\n\t"
      "movl $0, 0x330(%%ebx)\n\t"
      ".LFUN_001b3690_29:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x3d8(%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_001b3690_30\n\t"
      "decl %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "movw %%ax, 0x3d8(%%ebx)\n\t"
      "jne .LFUN_001b3690_30\n\t"
      "movl $0, 0x3d4(%%ebx)\n\t"
      ".LFUN_001b3690_30:\n\t"
      "movb 0x23c(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jle .LFUN_001b3690_31\n\t"
      "decb %%al\n\t"
      "movb %%al, 0x23c(%%ebx)\n\t"
      "jne .LFUN_001b3690_31\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ae600]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001b3690_31:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x3d0(%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_001b3690_35\n\t"
      "testb $0x20, 0x4(%%ebx)\n\t"
      "je .LFUN_001b3690_35\n\t"
      "decl %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "movw %%ax, 0x3d0(%%ebx)\n\t"
      "jne .LFUN_001b3690_35\n\t"
      "flds 0x90(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b3690_33\n\t"
      "andb $0xfb, 0xb6(%%ebx)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x248(%%ebx), %%cl\n\t"
      "shrb $3, %%cl\n\t"
      "notb %%cl\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "andl $1, %%ecx\n\t"
      "orl $0x22, %%ecx\n\t"
      "movl %%ecx, %%esi\n\t"
      "call *%[c1adf10]\n\t"
      "movl 0x32e48c, %%edx\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1acd70]\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ad260]\n\t"
      "andb $0xfb, 0x248(%%ebx)\n\t"
      "addl $0x1c, %%esp\n\t"
      "cmpw $0, 0x64(%%ebx)\n\t"
      "jne .LFUN_001b3690_32\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a09f0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001b3690_32:\n\t"
      "pushl $5\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a74d0]\n\t"
      "jmp .LFUN_001b3690_34\n\t"
      ".LFUN_001b3690_33:\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c1b3060]\n\t"
      ".LFUN_001b3690_34:\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001b3690_35:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl 0x17c(%%eax), %%ecx\n\t"
      "testb $4, %%ch\n\t"
      "jne .LFUN_001b3690_78\n\t"
      "movw 0xb6(%%ebx), %%ax\n\t"
      "testb $4, %%al\n\t"
      "jne .LFUN_001b3690_47\n\t"
      "testb $4, %%ah\n\t"
      "je .LFUN_001b3690_36\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ae600]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_001b3690_38\n\t"
      ".LFUN_001b3690_36:\n\t"
      "movw 0x2a4(%%ebx), %%cx\n\t"
      "cmpw 0x2a2(%%ebx), %%cx\n\t"
      "je .LFUN_001b3690_37\n\t"
      "leal 0x248(%%ebx), %%ecx\n\t"
      "call *%[c1a8730]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b3690_37\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2a4(%%eax), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1adeb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001b3690_38\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ae370]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b3690_38\n\t"
      "pushl $1\n\t"
      "call *%[c1b1ee0]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_001b3690_38\n\t"
      ".LFUN_001b3690_37:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      ".LFUN_001b3690_38:\n\t"
      "movb 0x2cd(%%ebx), %%al\n\t"
      "cmpb 0x2cc(%%ebx), %%al\n\t"
      "je .LFUN_001b3690_39\n\t"
      "leal 0x248(%%ebx), %%ecx\n\t"
      "call *%[c1a8730]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b3690_39\n\t"
      "movsbw 0x2cd(%%ebx), %%ax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1a9980]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001b3690_39\n\t"
      "movb %%al, 0x2cc(%%ebx)\n\t"
      ".LFUN_001b3690_39:\n\t"
      "movb 0x5aa892, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b3690_42\n\t"
      "cmpl $-1, 0x1c8(%%ebx)\n\t"
      "je .LFUN_001b3690_42\n\t"
      "leal 0x2ce(%%ebx), %%eax\n\t"
      "movl $2, %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_001b3690_40:\n\t"
      "movb (%%eax), %%cl\n\t"
      "cmpb $1, %%cl\n\t"
      "movsbl %%cl, %%ecx\n\t"
      "jg .LFUN_001b3690_41\n\t"
      "movl $1, %%ecx\n\t"
      ".LFUN_001b3690_41:\n\t"
      "movb %%cl, (%%eax)\n\t"
      "incl %%eax\n\t"
      "decl %%edi\n\t"
      "jne .LFUN_001b3690_40\n\t"
      "cmpb $0xff, 0x2cd(%%ebx)\n\t"
      "jne .LFUN_001b3690_42\n\t"
      "movb $0, 0x2cd(%%ebx)\n\t"
      ".LFUN_001b3690_42:\n\t"
      "movb 0x2d1(%%ebx), %%al\n\t"
      "cmpb 0x2d0(%%ebx), %%al\n\t"
      "je .LFUN_001b3690_47\n\t"
      "cmpb $0xff, %%al\n\t"
      "movb %%al, 0x2d0(%%ebx)\n\t"
      "jne .LFUN_001b3690_43\n\t"
      "movl $0, 0x2f8(%%ebx)\n\t"
      ".LFUN_001b3690_43:\n\t"
      "pushl %%esi\n\t"
      "call *%[cba500]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001b3690_47\n\t"
      "pushl %%esi\n\t"
      "call *%[cba500]\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movswl 0x2(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001b3690_47\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2a2(%%eax), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1adeb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001b3690_47\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x77656170\n\t"
      "call *%[tag]\n\t"
      "movb 0x2d0(%%ebx), %%cl\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpb $0xff, %%cl\n\t"
      "jne .LFUN_001b3690_44\n\t"
      "movl 0x4bc(%%eax), %%edx\n\t"
      "jmp .LFUN_001b3690_45\n\t"
      ".LFUN_001b3690_44:\n\t"
      "movl 0x4ac(%%eax), %%edx\n\t"
      ".LFUN_001b3690_45:\n\t"
      "cmpb $0xff, %%cl\n\t"
      "movl $0x3f800000, -0x14(%%ebp)\n\t"
      "je .LFUN_001b3690_46\n\t"
      "movw 0x3da(%%eax), %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "jle .LFUN_001b3690_46\n\t"
      "movsbl %%cl, %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "decl %%eax\n\t"
      "fildl -0x18(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "fidivl -0x18(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      ".LFUN_001b3690_46:\n\t"
      "cmpl $-1, %%edx\n\t"
      "je .LFUN_001b3690_47\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1c7480]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001b3690_47:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $0x2b7c28\n\t"
      "call *%[c1af6b0]\n\t"
      "movb 0x238(%%ebx), %%al\n\t"
      "addl $4, %%esp\n\t"
      "cmpb $1, %%al\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "jne .LFUN_001b3690_48\n\t"
      "movl 0x26c(%%eax), %%edx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "jmp .LFUN_001b3690_49\n\t"
      ".LFUN_001b3690_48:\n\t"
      "movl $0x3f800000, -0x10(%%ebp)\n\t"
      ".LFUN_001b3690_49:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "leal 0x1ec(%%ebx), %%esi\n\t"
      "fmuls 0x264(%%eax)\n\t"
      "fmuls 0x2546a4\n\t"
      "fsts -0x18(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x268(%%eax)\n\t"
      "movl %%esi, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "fmuls 0x25620c\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001b3690_51\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001b3690_51\n\t"
      "leal 0x1e0(%%ebx), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b3690_50\n\t"
      "flds 0x1e8(%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0x3e1\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x1e4(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b7c04\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b3690_50:\n\t"
      "movl (%%edi), %%edx\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $1\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "call *%[c1ada90]\n\t"
      "movl 0x31fc38, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "leal 0x1f8(%%ebx), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "pushl $0x2b7bf0\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "call *%[c1af6b0]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_001b3690_53\n\t"
      ".LFUN_001b3690_51:\n\t"
      "movb 0x266(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b3690_52\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x54(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "movl $0x3f800000, -0x58(%%ebp)\n\t"
      "call *%[c141360]\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      "movl 0x31fc1c, %%ecx\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls -0x50(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls -0x54(%%ebp)\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls -0x54(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      "leal 0x268(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x1f8(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x1e0(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1b0630]\n\t"
      "pushl $0x2b7bd8\n\t"
      "call *%[c1af6b0]\n\t"
      "addl $0x2c, %%esp\n\t"
      "jmp .LFUN_001b3690_53\n\t"
      ".LFUN_001b3690_52:\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x1f8(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x1e0(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c10f770]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $0x2b7bc4\n\t"
      "call *%[c1af6b0]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_001b3690_53:\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c10c510]\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      "flds 0x264(%%edi)\n\t"
      "addl $8, %%esp\n\t"
      "fmuls 0x2546a4\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b3690_54\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_001b3690_55\n\t"
      ".LFUN_001b3690_54:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b3690_55\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_001b3690_55:\n\t"
      "fmuls 0x2602c8\n\t"
      "call *%[ftol]\n\t"
      "pushl %%esi\n\t"
      "movb %%al, 0x2d3(%%ebx)\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b3690_56\n\t"
      "flds 0x1f4(%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0x408\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x1f0(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b7808\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b3690_56:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x270(%%edi)\n\t"
      "fmuls 0x2546a4\n\t"
      "fsts -0x18(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x274(%%edi)\n\t"
      "fmuls 0x25620c\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001b3690_57\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001b3690_57\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "leal 0x210(%%ebx), %%esi\n\t"
      "leal 0x204(%%ebx), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "movl %%esi, %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "pushl $0\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "call *%[c1ada90]\n\t"
      "movl 0x31fc38, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal 0x21c(%%ebx), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "pushl $0x2b7bac\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "call *%[c1af6b0]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_001b3690_59\n\t"
      ".LFUN_001b3690_57:\n\t"
      "movb 0x267(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b3690_58\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "leal -0x3c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x54(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "movl $0x3f800000, -0x58(%%ebp)\n\t"
      "call *%[c141360]\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      "movl 0x31fc1c, %%eax\n\t"
      "flds -0x34(%%ebp)\n\t"
      "leal 0x210(%%ebx), %%esi\n\t"
      "fmuls -0x50(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls -0x54(%%ebp)\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls -0x54(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "leal 0x278(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x21c(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x204(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1b0630]\n\t"
      "pushl $0x2b7b94\n\t"
      "call *%[c1af6b0]\n\t"
      "addl $0x2c, %%esp\n\t"
      "jmp .LFUN_001b3690_59\n\t"
      ".LFUN_001b3690_58:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal 0x21c(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x204(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x210(%%ebx), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c10f770]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $0x2b7b80\n\t"
      "call *%[c1af6b0]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_001b3690_59:\n\t"
      "pushl %%esi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b3690_60\n\t"
      "flds 0x218(%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0x434\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x214(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b7b64\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b3690_60:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $0x2b7b4c\n\t"
      "call *%[c1af6b0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b3690_66\n\t"
      "movl 0x1b8(%%ebx), %%eax\n\t"
      "movsbl 0x23d(%%ebx), %%ecx\n\t"
      "shrl $0xd, %%eax\n\t"
      "andb $1, %%al\n\t"
      "cmpl $3, %%ecx\n\t"
      "ja .LFUN_001b3690_66\n\t"
      "jmp *.LFUN_001b3690_jt(,%%ecx,4)\n\t"
      ".LFUN_001b3690_61:\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b3690_66\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c1b2090]\n\t"
      "jmp .LFUN_001b3690_65\n\t"
      ".LFUN_001b3690_62:\n\t"
      "cmpw $2, 0x82(%%ebx)\n\t"
      "jl .LFUN_001b3690_66\n\t"
      "call *%[c1aaf40]\n\t"
      "jmp .LFUN_001b3690_66\n\t"
      ".LFUN_001b3690_63:\n\t"
      "cmpb $0x21, 0x253(%%ebx)\n\t"
      "je .LFUN_001b3690_66\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b3690_66\n\t"
      "movb %%al, 0x23d(%%ebx)\n\t"
      "jmp .LFUN_001b3690_66\n\t"
      ".LFUN_001b3690_64:\n\t"
      "movb 0x253(%%ebx), %%al\n\t"
      "incw 0x23e(%%ebx)\n\t"
      "cmpb $0x21, %%al\n\t"
      "je .LFUN_001b3690_66\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ab110]\n\t"
      ".LFUN_001b3690_65:\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001b3690_66:\n\t"
      "movw 0x2a2(%%ebx), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001b3690_78\n\t"
      "movl 0x234(%%ebx), %%edx\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpw 0x2a4(%%ebx), %%ax\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "jne .LFUN_001b3690_76\n\t"
      "movl 0x1c0(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_001b3690_67\n\t"
      "movl 0x1c4(%%ebx), %%eax\n\t"
      "testb $8, %%ah\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "jne .LFUN_001b3690_68\n\t"
      ".LFUN_001b3690_67:\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      ".LFUN_001b3690_68:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b3690_71\n\t"
      "movb -0x5(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b3690_69\n\t"
      "testb $0x10, 0x1b8(%%ebx)\n\t"
      "je .LFUN_001b3690_69\n\t"
      "movl $1, %%esi\n\t"
      ".LFUN_001b3690_69:\n\t"
      "movl 0x1b8(%%ebx), %%eax\n\t"
      "testb $8, %%ah\n\t"
      "je .LFUN_001b3690_70\n\t"
      "orl $2, %%esi\n\t"
      ".LFUN_001b3690_70:\n\t"
      "testb $0x10, %%ah\n\t"
      "je .LFUN_001b3690_71\n\t"
      "orl $4, %%esi\n\t"
      ".LFUN_001b3690_71:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0x17c(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testl $0x800000, %%ecx\n\t"
      "je .LFUN_001b3690_72\n\t"
      "movl 0x2f0(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2a2(%%eax), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1adeb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[cfaeb0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001b3690_72:\n\t"
      "movl 0x1b8(%%ebx), %%eax\n\t"
      "testb $4, %%ah\n\t"
      "je .LFUN_001b3690_73\n\t"
      "orl $8, %%esi\n\t"
      ".LFUN_001b3690_73:\n\t"
      "leal 0x248(%%ebx), %%ecx\n\t"
      "call *%[c1a8730]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b3690_74\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b3690_74\n\t"
      "orl $0x10, %%esi\n\t"
      ".LFUN_001b3690_74:\n\t"
      "cmpw $0, 0x64(%%ebx)\n\t"
      "jne .LFUN_001b3690_75\n\t"
      "movb 0x45d(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jle .LFUN_001b3690_75\n\t"
      "orl $0x10, %%esi\n\t"
      ".LFUN_001b3690_75:\n\t"
      "cmpb $0xff, 0x2d0(%%ebx)\n\t"
      "je .LFUN_001b3690_77\n\t"
      "orl $0x40, %%esi\n\t"
      "jmp .LFUN_001b3690_77\n\t"
      ".LFUN_001b3690_76:\n\t"
      "movl $0x20, %%esi\n\t"
      ".LFUN_001b3690_77:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x2a2(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1adeb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[cfc4b0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001b3690_78:\n\t"
      "leal 0x30(%%ebx), %%esi\n\t"
      "leal 0x24(%%ebx), %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c84a70]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b3690_79\n\t"
      "flds 0x38(%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0x483\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x30, %%esp\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x34(%%ebx)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x2c(%%ebx)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x28(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b7220\n\t"
      "pushl $0x2b7208\n\t"
      "pushl $0x267490\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x40, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b3690_79:\n\t"
      "leal 0x1ec(%%ebx), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b3690_80\n\t"
      "flds 0x1f4(%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0x484\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x1f0(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b7808\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b3690_80:\n\t"
      "leal 0x210(%%ebx), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b3690_81\n\t"
      "flds 0x218(%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0x485\n\t"
      "pushl $0x2b68c0\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x214(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b7b64\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b3690_81:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl 0x17c(%%edx), %%eax\n\t"
      "testb $8, %%ah\n\t"
      "jne .LFUN_001b3690_90\n\t"
      "testb $2, 0x248(%%ebx)\n\t"
      "je .LFUN_001b3690_82\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "call *%[c1ab410]\n\t"
      "flds 0x320(%%ebx)\n\t"
      "fmuls 0x2533e4\n\t"
      "flds 0x314(%%ebx)\n\t"
      "fmuls 0x2533c4\n\t"
      "faddp %%st(1)\n\t"
      "fstps 0x314(%%ebx)\n\t"
      "flds 0x324(%%ebx)\n\t"
      "fmuls 0x2533e4\n\t"
      "flds 0x318(%%ebx)\n\t"
      "fmuls 0x2533c4\n\t"
      "faddp %%st(1)\n\t"
      "fstps 0x318(%%ebx)\n\t"
      "flds 0x328(%%ebx)\n\t"
      "fmuls 0x2533e4\n\t"
      "flds 0x31c(%%ebx)\n\t"
      "fmuls 0x2533c4\n\t"
      "faddp %%st(1)\n\t"
      "fstps 0x31c(%%ebx)\n\t"
      ".LFUN_001b3690_82:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl 0x2cc(%%eax), %%ecx\n\t"
      "addl $0x2cc, %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "jle .LFUN_001b3690_90\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LFUN_001b3690_83:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "pushl $0x44\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%di, %%di\n\t"
      "movl %%eax, %%ecx\n\t"
      "jne .LFUN_001b3690_85\n\t"
      "cmpl $-1, 0x2d4(%%ebx)\n\t"
      "jne .LFUN_001b3690_84\n\t"
      "testb $1, 0x1b4(%%ebx)\n\t"
      "je .LFUN_001b3690_86\n\t"
      ".LFUN_001b3690_84:\n\t"
      "movb $1, %%al\n\t"
      "jmp .LFUN_001b3690_87\n\t"
      ".LFUN_001b3690_85:\n\t"
      "movl 0x2d8(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001b3690_86\n\t"
      "cmpl 0x2d4(%%ebx), %%eax\n\t"
      "je .LFUN_001b3690_86\n\t"
      "movb $1, %%al\n\t"
      "jmp .LFUN_001b3690_87\n\t"
      ".LFUN_001b3690_86:\n\t"
      "xorb %%al, %%al\n\t"
      ".LFUN_001b3690_87:\n\t"
      "testb $4, 0xb6(%%ebx)\n\t"
      "jne .LFUN_001b3690_88\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b3690_88\n\t"
      "movl 0x2e8(%%ebx,%%esi,4), %%eax\n\t"
      "movl $0x3f800000, %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "je .LFUN_001b3690_89\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fmuls 0x253394\n\t"
      "fdivrs 0x2533c8\n\t"
      "fadds 0x2e8(%%ebx,%%esi,4)\n\t"
      "fsts 0x2e8(%%ebx,%%esi,4)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b3690_89\n\t"
      "movl %%edx, 0x2e8(%%ebx,%%esi,4)\n\t"
      "jmp .LFUN_001b3690_89\n\t"
      ".LFUN_001b3690_88:\n\t"
      "flds 0x2e8(%%ebx,%%esi,4)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_001b3690_89\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fmuls 0x253394\n\t"
      "fdivrs 0x2533c8\n\t"
      "fsubrs 0x2e8(%%ebx,%%esi,4)\n\t"
      "fsts 0x2e8(%%ebx,%%esi,4)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b3690_89\n\t"
      "movl $0, 0x2e8(%%ebx,%%esi,4)\n\t"
      ".LFUN_001b3690_89:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%esi\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jl .LFUN_001b3690_83\n\t"
      ".LFUN_001b3690_90:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x3b6(%%ebx), %%ax\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpw %%si, %%ax\n\t"
      "jle .LFUN_001b3690_91\n\t"
      "decl %%eax\n\t"
      "cmpw %%si, %%ax\n\t"
      "movw %%ax, 0x3b6(%%ebx)\n\t"
      "jne .LFUN_001b3690_91\n\t"
      "movl 0x3b8(%%ebx), %%edx\n\t"
      "movl 0x3bc(%%ebx), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x3b4(%%ebx), %%ax\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c40460]\n\t"
      "addl $0x18, %%esp\n\t"
      "movw %%si, 0x3b4(%%ebx)\n\t"
      "movl $0xffffffff, 0x3bc(%%ebx)\n\t"
      "movl %%esi, 0x3b8(%%ebx)\n\t"
      ".LFUN_001b3690_91:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%esi, %%edi\n\t"
      "call *%[c1abd90]\n\t"
      "pushl %%esi\n\t"
      "call *%[c1a7790]\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001b3690_92\n\t"
      "cmpl $-1, 0x1c8(%%ebx)\n\t"
      "je .LFUN_001b3690_93\n\t"
      ".LFUN_001b3690_92:\n\t"
      "movl %%esi, %%edi\n\t"
      "call *%[c1ab8c0]\n\t"
      "movb 0x5054fa, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b3690_93\n\t"
      "cmpl $-1, 0x1c8(%%ebx)\n\t"
      "je .LFUN_001b3690_93\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x32e480, %%eax\n\t"
      "addl $0x1e, %%eax\n\t"
      "cmpl %%eax, %%edi\n\t"
      "jl .LFUN_001b3690_93\n\t"
      "flds 0x290(%%ebx)\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x294(%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b7b20\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x18, %%esp\n\t"
      "movl %%edi, 0x32e480\n\t"
      ".LFUN_001b3690_93:\n\t"
      "movb 0x23b(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jbe .LFUN_001b3690_94\n\t"
      "decb %%al\n\t"
      "movb %%al, 0x23b(%%ebx)\n\t"
      "jne .LFUN_001b3690_94\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ac550]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001b3690_94:\n\t"
      "flds 0x298(%%ebx)\n\t"
      "fchs\n\t"
      "fcoms 0x25e884\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b3690_95\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x25e884\n\t"
      "jmp .LFUN_001b3690_96\n\t"
      ".LFUN_001b3690_95:\n\t"
      "fcoms 0x25496c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b3690_96\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x25496c\n\t"
      ".LFUN_001b3690_96:\n\t"
      "fadds 0x298(%%ebx)\n\t"
      "fstps 0x298(%%ebx)\n\t"
      "movl 0x1b4(%%ebx), %%eax\n\t"
      "testl $0x10000000, %%eax\n\t"
      "je .LFUN_001b3690_98\n\t"
      "testl $0x80000, %%eax\n\t"
      "movb $1, %%cl\n\t"
      "je .LFUN_001b3690_97\n\t"
      "movb -0x4(%%ebp), %%cl\n\t"
      ".LFUN_001b3690_97:\n\t"
      "andl $0xefffffff, %%eax\n\t"
      "movl %%eax, 0x1b4(%%ebx)\n\t"
      "jmp .LFUN_001b3690_99\n\t"
      ".LFUN_001b3690_98:\n\t"
      "movb -0x4(%%ebp), %%cl\n\t"
      ".LFUN_001b3690_99:\n\t"
      "movl 0x1b4(%%ebx), %%eax\n\t"
      "testl $0x20000000, %%eax\n\t"
      "je .LFUN_001b3690_101\n\t"
      "testl $0x80000, %%eax\n\t"
      "je .LFUN_001b3690_100\n\t"
      "movb $1, %%cl\n\t"
      ".LFUN_001b3690_100:\n\t"
      "andl $0xdfffffff, %%eax\n\t"
      "movl %%eax, 0x1b4(%%ebx)\n\t"
      ".LFUN_001b3690_101:\n\t"
      "movb -0x5(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b3690_102\n\t"
      "testb $0x10, 0x1b8(%%ebx)\n\t"
      "jne .LFUN_001b3690_103\n\t"
      ".LFUN_001b3690_102:\n\t"
      "flds 0x2f4(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_001b3690_103\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_001b3690_111\n\t"
      ".LFUN_001b3690_103:\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movb 0x2d0(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "cmpb $0xff, %%cl\n\t"
      "je .LFUN_001b3690_109\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x2a2(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1adeb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001b3690_109\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x77656170\n\t"
      "call *%[tag]\n\t"
      "movl 0x308(%%eax), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $0x40, %%ch\n\t"
      "je .LFUN_001b3690_109\n\t"
      "testb $0x10, 0x1b8(%%ebx)\n\t"
      "je .LFUN_001b3690_109\n\t"
      "call *%[c18e450]\n\t"
      "movl %%eax, %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_001b3690_104\n\t"
      "pushl $1\n\t"
      "pushl $0x516\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x29da34\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b3690_104:\n\t"
      "pushl $0xc0\n\t"
      "pushl $0\n\t"
      "addl $0x17c, %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_001b3690_105\n\t"
      "pushl $1\n\t"
      "pushl $0x518\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b7afc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b3690_105:\n\t"
      "testl $0x4000000, 0x1b4(%%ebx)\n\t"
      "je .LFUN_001b3690_106\n\t"
      "movl 0x64(%%edi), %%eax\n\t"
      "jmp .LFUN_001b3690_107\n\t"
      ".LFUN_001b3690_106:\n\t"
      "movl 0x54(%%edi), %%eax\n\t"
      ".LFUN_001b3690_107:\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001b3690_108\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[o9ec30]\n\t"
      "addl $0x20, %%esp\n\t"
      ".LFUN_001b3690_108:\n\t"
      "xorl $0x4000000, 0x1b4(%%ebx)\n\t"
      "testb $0x10, 0x1b8(%%ebx)\n\t"
      "jne .LFUN_001b3690_111\n\t"
      ".LFUN_001b3690_109:\n\t"
      "movl 0x1b4(%%ebx), %%eax\n\t"
      "movl $0x80000, %%edi\n\t"
      "testl %%eax, %%edi\n\t"
      "jne .LFUN_001b3690_110\n\t"
      "flds 0x2f4(%%ebx)\n\t"
      "fcomps 0x2549d4\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b3690_111\n\t"
      ".LFUN_001b3690_110:\n\t"
      "cmpl $-1, 0xcc(%%ebx)\n\t"
      "jne .LFUN_001b3690_111\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl 0x194(%%eax), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[o9ec30]\n\t"
      "movl 0x1b4(%%ebx), %%eax\n\t"
      "addl $0x20, %%esp\n\t"
      "xorl %%edi, %%eax\n\t"
      "movl %%eax, 0x1b4(%%ebx)\n\t"
      ".LFUN_001b3690_111:\n\t"
      "movl 0x1b4(%%ebx), %%eax\n\t"
      "testl $0x80000, %%eax\n\t"
      "je .LFUN_001b3690_115\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "testl $0x1000000, 0x17c(%%edx)\n\t"
      "jne .LFUN_001b3690_112\n\t"
      "flds 0x2f4(%%ebx)\n\t"
      "fsubs 0x253f2c\n\t"
      "fstps 0x2f4(%%ebx)\n\t"
      ".LFUN_001b3690_112:\n\t"
      "cmpl $-1, 0xcc(%%ebx)\n\t"
      "jne .LFUN_001b3690_113\n\t"
      "testb $4, 0xb6(%%ebx)\n\t"
      "je .LFUN_001b3690_114\n\t"
      ".LFUN_001b3690_113:\n\t"
      "andl $0xfff7ffff, %%eax\n\t"
      "movl %%eax, 0x1b4(%%ebx)\n\t"
      ".LFUN_001b3690_114:\n\t"
      "movl 0x2f0(%%ebx), %%eax\n\t"
      "movl $0x3f800000, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_001b3690_117\n\t"
      "flds 0x2f0(%%ebx)\n\t"
      "fadds 0x2647d4\n\t"
      "fsts 0x2f0(%%ebx)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b3690_117\n\t"
      "movl %%ecx, 0x2f0(%%ebx)\n\t"
      "jmp .LFUN_001b3690_117\n\t"
      ".LFUN_001b3690_115:\n\t"
      "flds 0x2f4(%%ebx)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b3690_116\n\t"
      "flds 0x2f4(%%ebx)\n\t"
      "fadds 0x25620c\n\t"
      "fstps 0x2f4(%%ebx)\n\t"
      ".LFUN_001b3690_116:\n\t"
      "flds 0x2f0(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_001b3690_117\n\t"
      "flds 0x2f0(%%ebx)\n\t"
      "fsubs 0x28af18\n\t"
      "fsts 0x2f0(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b3690_117\n\t"
      "movl $0, 0x2f0(%%ebx)\n\t"
      ".LFUN_001b3690_117:\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movb 0x2d0(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "cmpb $0xff, %%cl\n\t"
      "je .LFUN_001b3690_121\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movw 0x2a2(%%eax), %%di\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $-1, %%di\n\t"
      "movl %%eax, %%esi\n\t"
      "je .LFUN_001b3690_121\n\t"
      "testw %%di, %%di\n\t"
      "jl .LFUN_001b3690_118\n\t"
      "cmpw $4, %%di\n\t"
      "jl .LFUN_001b3690_119\n\t"
      ".LFUN_001b3690_118:\n\t"
      "pushl $1\n\t"
      "pushl $0x20ac\n\t"
      "pushl $0x2b68c0\n\t"
      "pushl $0x2b6e84\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001b3690_119:\n\t"
      "movswl %%di, %%eax\n\t"
      "movl 0x2a8(%%esi,%%eax,4), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001b3690_121\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x77656170\n\t"
      "call *%[tag]\n\t"
      "movl 0x308(%%eax), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $0x40, %%ch\n\t"
      "je .LFUN_001b3690_121\n\t"
      "testl $0x4000000, 0x1b4(%%ebx)\n\t"
      "je .LFUN_001b3690_120\n\t"
      "movl 0x2f8(%%ebx), %%eax\n\t"
      "movl $0x3f800000, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_001b3690_121\n\t"
      "flds 0x2f8(%%ebx)\n\t"
      "fadds 0x255960\n\t"
      "fsts 0x2f8(%%ebx)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b3690_121\n\t"
      "movl %%ecx, 0x2f8(%%ebx)\n\t"
      "jmp .LFUN_001b3690_121\n\t"
      ".LFUN_001b3690_120:\n\t"
      "flds 0x2f8(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_001b3690_121\n\t"
      "flds 0x2f8(%%ebx)\n\t"
      "fsubs 0x28af18\n\t"
      "fsts 0x2f8(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b3690_121\n\t"
      "movl $0, 0x2f8(%%ebx)\n\t"
      ".LFUN_001b3690_121:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $0x2b7aec\n\t"
      "call *%[c1af6b0]\n\t"
      "movb 0x449ef1, %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_001b3690_122\n\t"
      "movb 0x32de90, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001b3690_122\n\t"
      "pushl $0x32de88\n\t"
      "call *%[pexit]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001b3690_122:\n\t"
      "movb $1, %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_001b3690_jt:\n\t"
      ".long .LFUN_001b3690_61\n\t"
      ".long .LFUN_001b3690_62\n\t"
      ".long .LFUN_001b3690_64\n\t"
      ".long .LFUN_001b3690_63\n\t"
      ".text\n\t"
      :
      : [get] "m"(b1b3690_get), [tag] "m"(b1b3690_tag), [cab9e0] "m"(b1b3690_cab9e0), [penter] "m"(b1b3690_penter), [c1af6b0] "m"(b1b3690_c1af6b0), [c1af340] "m"(b1b3690_c1af340), [c21fb0] "m"(b1b3690_c21fb0), [c8d9d0] "m"(b1b3690_c8d9d0), [assert] "m"(b1b3690_assert), [exitfn] "m"(b1b3690_exitfn), [gerun] "m"(b1b3690_gerun), [c1adeb0] "m"(b1b3690_c1adeb0), [c1ae600] "m"(b1b3690_c1ae600), [c1adf10] "m"(b1b3690_c1adf10), [c1acd70] "m"(b1b3690_c1acd70), [c1ad260] "m"(b1b3690_c1ad260), [c1a09f0] "m"(b1b3690_c1a09f0), [c1a74d0] "m"(b1b3690_c1a74d0), [c1b3060] "m"(b1b3690_c1b3060), [c1a8730] "m"(b1b3690_c1a8730), [c1ae370] "m"(b1b3690_c1ae370), [c1b1ee0] "m"(b1b3690_c1b1ee0), [c1a9980] "m"(b1b3690_c1a9980), [cba500] "m"(b1b3690_cba500), [dget] "m"(b1b3690_dget), [c1c7480] "m"(b1b3690_c1c7480), [c1ada90] "m"(b1b3690_c1ada90), [c141360] "m"(b1b3690_c141360), [c1b0630] "m"(b1b3690_c1b0630), [c10f770] "m"(b1b3690_c10f770), [c10c510] "m"(b1b3690_c10c510), [ftol] "m"(b1b3690_ftol), [c1b2090] "m"(b1b3690_c1b2090), [c1aaf40] "m"(b1b3690_c1aaf40), [c1ab110] "m"(b1b3690_c1ab110), [cfaeb0] "m"(b1b3690_cfaeb0), [cfc4b0] "m"(b1b3690_cfc4b0), [c84a70] "m"(b1b3690_c84a70), [c1ab410] "m"(b1b3690_c1ab410), [elem] "m"(b1b3690_elem), [c40460] "m"(b1b3690_c40460), [c1abd90] "m"(b1b3690_c1abd90), [c1a7790] "m"(b1b3690_c1a7790), [c1ab8c0] "m"(b1b3690_c1ab8c0), [gtime] "m"(b1b3690_gtime), [c8f390] "m"(b1b3690_c8f390), [c1ac550] "m"(b1b3690_c1ac550), [c18e450] "m"(b1b3690_c18e450), [o9ec30] "m"(b1b3690_o9ec30), [pexit] "m"(b1b3690_pexit)
      : "memory");
}
#else
#error "FUN_001b3690: clang naked draft required"
#endif


/* FUN_001a6350 (0x1a6350) — XBE naked draft (batch 53). */
#if defined(__clang__)
static void *(*const b1a6350_get)(int, int) = object_get_and_verify_type;
static void *(*const b1a6350_tag)(int, int) = tag_get;
static void (*const b1a6350_penter)(void *) = profile_enter_private;
static void (*const b1a6350_c1a2800)(int unit_handle, const char *failure_kind) = FUN_001a2800;
static void (*const b1a6350_c1a1fb0)(int unit_handle) = FUN_001a1fb0;
static char (*const b1a6350_c1b3580)(int unit_handle) = unit_try_and_exit_seat;
static void (*const b1a6350_c1b2dd0)(int unit_handle) = unit_exit_seat_end;
static void (*const b1a6350_c1a4440)(int unit_handle) = FUN_001a4440;
static float (*const b1a6350_norm)(float *) = normalize3d;
static void (*const b1a6350_c1a4c50)(int unit_handle, unsigned char *state) = FUN_001a4c50;
static void (*const b1a6350_c1a5300)(int unit_handle, unsigned char *state) = FUN_001a5300;
static void (*const b1a6350_c1a6280)(int unit_handle, char *state_out) = FUN_001a6280;
static void (*const b1a6350_c1a2900)(int unit_handle, char *state) = FUN_001a2900;
static void (*const b1a6350_c1a2a60)(int unit_handle, char *state) = FUN_001a2a60;
static void (*const b1a6350_c1a2b10)(int unit_handle) = FUN_001a2b10;
static int (*const b1a6350_c1adeb0)(int unit_handle, int16_t weapon_index) = unit_get_weapon;
static char (*const b1a6350_cfc930)(int weapon_handle) = weapon_prevents_melee_attack;
static void (*const b1a6350_c1a8990)(int object_handle, int16_t state) = unit_animation_start_action;
static void (*const b1a6350_cfd510)(int weapon_handle) = weapon_stop_reload;
static void (*const b1a6350_cde360)(int unit_handle, int message_type) = first_person_weapon_message_from_unit;
static int16_t (*const b1a6350_cfb140)(int weapon_handle, int16_t param_2, int16_t param_3, int16_t param_4) = weapon_get_animation_frame;
static void (*const b1a6350_c1aea90)(int unit_handle) = unit_cause_player_melee_damage;
static void (*const b1a6350_c1a2440)(int unit_handle) = FUN_001a2440;
static void (*const b1a6350_c1a1e70)(int unit_handle) = FUN_001a1e70;
static char (*const b1a6350_c1a0b30)(int unit_handle) = FUN_001a0b30;
static short (*const b1a6350_c1b0d90)(int unit_handle, char *anim_state) = FUN_001b0d90;
static char (*const b1a6350_c1a2290)(int unit_handle) = FUN_001a2290;
static void (*const b1a6350_pexit)(void *) = profile_exit_private;

__attribute__((naked, noinline))
char FUN_001a6350(int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movb 0x4e4cf1, %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a6350_29\n\t"
      "movb 0x449ef1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a6350_1\n\t"
      "movb 0x32d1d8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a6350_1\n\t"
      "pushl $0x32d1d0\n\t"
      "call *%[penter]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001a6350_1:\n\t"
      "pushl $0x2b524c\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1a2800]\n\t"
      "movb $0, -0x4(%%ebp)\n\t"
      "movb $0, -0x3(%%ebp)\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001a6350_4\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movw 0x64(%%eax), %%cx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $1, %%cx\n\t"
      "jne .LFUN_001a6350_3\n\t"
      "movl 0xcc(%%esi), %%ecx\n\t"
      "pushl $2\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1a1fb0]\n\t"
      "testb $0x40, 0x1b8(%%esi)\n\t"
      "je .LFUN_001a6350_2\n\t"
      "pushl %%edi\n\t"
      "call *%[c1b3580]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001a6350_2:\n\t"
      "movb 0x32d1c8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a6350_25\n\t"
      "flds 0x38(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001a6350_25\n\t"
      "testb $2, 0x4(%%ebx)\n\t"
      "je .LFUN_001a6350_25\n\t"
      "pushl %%edi\n\t"
      "call *%[c1b2dd0]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_001a6350_25\n\t"
      ".LFUN_001a6350_3:\n\t"
      "testw %%cx, %%cx\n\t"
      "jne .LFUN_001a6350_25\n\t"
      "movb 0xb6(%%eax), %%dl\n\t"
      "andb $4, %%dl\n\t"
      "orb $0x20, %%dl\n\t"
      "movb %%dl, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001a6350_25\n\t"
      ".LFUN_001a6350_4:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a4440]\n\t"
      "movb 0xb6(%%esi), %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb $4, %%al\n\t"
      "jne .LFUN_001a6350_5\n\t"
      "testb $0x44, 0x2f4(%%ebx)\n\t"
      "jne .LFUN_001a6350_6\n\t"
      ".LFUN_001a6350_5:\n\t"
      "leal 0x1d4(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "movl $0, 0x1dc(%%esi)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001a6350_6\n\t"
      "movl 0x31fc3c, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, (%%ebx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ebx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ebx)\n\t"
      ".LFUN_001a6350_6:\n\t"
      "movsbl 0x253(%%esi), %%eax\n\t"
      "cmpl $7, %%eax\n\t"
      "ja .LFUN_001a6350_9\n\t"
      "movzbl 0x1a67a4(%%eax), %%ecx\n\t"
      "jmp *.LFUN_001a6350_jt(,%%ecx,4)\n\t"
      ".LFUN_001a6350_7:\n\t"
      "movb $1, 0x42a(%%esi)\n\t"
      "jmp .LFUN_001a6350_10\n\t"
      ".LFUN_001a6350_8:\n\t"
      "movb $0, 0x42a(%%esi)\n\t"
      "jmp .LFUN_001a6350_10\n\t"
      ".LFUN_001a6350_9:\n\t"
      "movb $2, 0x42a(%%esi)\n\t"
      ".LFUN_001a6350_10:\n\t"
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
      "fcomps 0x255d1c\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jp .LFUN_001a6350_11\n\t"
      "movl 0x31fc38, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, 0x228(%%esi)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x22c(%%esi)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x230(%%esi)\n\t"
      ".LFUN_001a6350_11:\n\t"
      "movl 0x424(%%esi), %%ecx\n\t"
      "testb $1, %%cl\n\t"
      "je .LFUN_001a6350_12\n\t"
      "movb 0x459(%%esi), %%al\n\t"
      "cmpb $0x7f, %%al\n\t"
      "jge .LFUN_001a6350_13\n\t"
      "incb %%al\n\t"
      "movb %%al, 0x459(%%esi)\n\t"
      "jmp .LFUN_001a6350_13\n\t"
      ".LFUN_001a6350_12:\n\t"
      "movb $0, 0x459(%%esi)\n\t"
      ".LFUN_001a6350_13:\n\t"
      "testb $2, %%cl\n\t"
      "je .LFUN_001a6350_14\n\t"
      "movb 0x45a(%%esi), %%al\n\t"
      "cmpb $0x7f, %%al\n\t"
      "jge .LFUN_001a6350_15\n\t"
      "incb %%al\n\t"
      "movb %%al, 0x45a(%%esi)\n\t"
      "jmp .LFUN_001a6350_15\n\t"
      ".LFUN_001a6350_14:\n\t"
      "movb $0, 0x45a(%%esi)\n\t"
      ".LFUN_001a6350_15:\n\t"
      "movb $0, -0x4(%%ebp)\n\t"
      "movb 0x1b8(%%esi), %%al\n\t"
      "andb $1, %%al\n\t"
      "movb %%al, -0x3(%%ebp)\n\t"
      "pushl $0x2b5240\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1a2800]\n\t"
      "movb 0xb6(%%esi), %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb $4, %%al\n\t"
      "jne .LFUN_001a6350_16\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a4c50]\n\t"
      "pushl $0x2b5230\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1a2800]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001a6350_16:\n\t"
      "leal -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a5300]\n\t"
      "pushl $0x2b5224\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1a2800]\n\t"
      "movb 0xb6(%%esi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $4, %%al\n\t"
      "je .LFUN_001a6350_17\n\t"
      "leal -0x4(%%ebp), %%ebx\n\t"
      "call *%[c1a6280]\n\t"
      "jmp .LFUN_001a6350_21\n\t"
      ".LFUN_001a6350_17:\n\t"
      "movl 0x424(%%esi), %%eax\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_001a6350_18\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a2900]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_001a6350_21\n\t"
      ".LFUN_001a6350_18:\n\t"
      "cmpw $-1, 0x460(%%esi)\n\t"
      "je .LFUN_001a6350_19\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1a2a60]\n\t"
      "jmp .LFUN_001a6350_20\n\t"
      ".LFUN_001a6350_19:\n\t"
      "testb $2, %%al\n\t"
      "je .LFUN_001a6350_21\n\t"
      "leal -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1a2b10]\n\t"
      ".LFUN_001a6350_20:\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001a6350_21:\n\t"
      "pushl $0x2b520c\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1a2800]\n\t"
      "movb 0x45d(%%esi), %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a6350_22\n\t"
      "cmpl $-1, 0x1c8(%%esi)\n\t"
      "je .LFUN_001a6350_24\n\t"
      "movb 0x1b8(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jns .LFUN_001a6350_24\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movswl 0x2a2(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c1adeb0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "call *%[cfc930]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001a6350_24\n\t"
      "cmpb $0xff, 0x2d0(%%esi)\n\t"
      "jne .LFUN_001a6350_24\n\t"
      "pushl $7\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a8990]\n\t"
      "pushl %%ebx\n\t"
      "call *%[cfd510]\n\t"
      "pushl $4\n\t"
      "pushl %%edi\n\t"
      "call *%[cde360]\n\t"
      "pushl $-1\n\t"
      "pushl $0xd\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[cfb140]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl $0xd\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "movb %%al, 0x45d(%%esi)\n\t"
      "movb %%al, %%bl\n\t"
      "call *%[cfb140]\n\t"
      "movb %%bl, %%dl\n\t"
      "subb %%al, %%dl\n\t"
      "movb %%bl, %%al\n\t"
      "sarb $2, %%al\n\t"
      "movsbw %%al, %%ax\n\t"
      "subb %%al, %%bl\n\t"
      "movb %%dl, %%cl\n\t"
      "addl $0x34, %%esp\n\t"
      "subb %%al, %%cl\n\t"
      "movb %%dl, 0x45e(%%esi)\n\t"
      "movb %%bl, 0x45d(%%esi)\n\t"
      "movb %%cl, 0x45e(%%esi)\n\t"
      "jmp .LFUN_001a6350_24\n\t"
      ".LFUN_001a6350_22:\n\t"
      "cmpb 0x45e(%%esi), %%al\n\t"
      "jne .LFUN_001a6350_23\n\t"
      "pushl %%edi\n\t"
      "call *%[c1aea90]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001a6350_23:\n\t"
      "decb 0x45d(%%esi)\n\t"
      ".LFUN_001a6350_24:\n\t"
      "call *%[c1a2440]\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a1e70]\n\t"
      "addl $4, %%esp\n\t"
      "call *%[c1a0b30]\n\t"
      ".LFUN_001a6350_25:\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1b0d90]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .LFUN_001a6350_26\n\t"
      "call *%[c1a2290]\n\t"
      ".LFUN_001a6350_26:\n\t"
      "testb $4, 0xb6(%%esi)\n\t"
      "je .LFUN_001a6350_27\n\t"
      "testb $0x20, 0x4(%%esi)\n\t"
      "je .LFUN_001a6350_27\n\t"
      "incw 0x6c(%%esi)\n\t"
      "jmp .LFUN_001a6350_28\n\t"
      ".LFUN_001a6350_27:\n\t"
      "movw $0, 0x6c(%%esi)\n\t"
      ".LFUN_001a6350_28:\n\t"
      "pushl $0x2b5200\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1a2800]\n\t"
      "movb 0x449ef1, %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a6350_29\n\t"
      "movb 0x32d1d8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001a6350_29\n\t"
      "pushl $0x32d1d0\n\t"
      "call *%[pexit]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001a6350_29:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "movl %%edi, %%edi\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_001a6350_jt:\n\t"
      ".long .LFUN_001a6350_8\n\t"
      ".long .LFUN_001a6350_7\n\t"
      ".long .LFUN_001a6350_9\n\t"
      ".text\n\t"
      :
      : [get] "m"(b1a6350_get), [tag] "m"(b1a6350_tag), [penter] "m"(b1a6350_penter), [c1a2800] "m"(b1a6350_c1a2800), [c1a1fb0] "m"(b1a6350_c1a1fb0), [c1b3580] "m"(b1a6350_c1b3580), [c1b2dd0] "m"(b1a6350_c1b2dd0), [c1a4440] "m"(b1a6350_c1a4440), [norm] "m"(b1a6350_norm), [c1a4c50] "m"(b1a6350_c1a4c50), [c1a5300] "m"(b1a6350_c1a5300), [c1a6280] "m"(b1a6350_c1a6280), [c1a2900] "m"(b1a6350_c1a2900), [c1a2a60] "m"(b1a6350_c1a2a60), [c1a2b10] "m"(b1a6350_c1a2b10), [c1adeb0] "m"(b1a6350_c1adeb0), [cfc930] "m"(b1a6350_cfc930), [c1a8990] "m"(b1a6350_c1a8990), [cfd510] "m"(b1a6350_cfd510), [cde360] "m"(b1a6350_cde360), [cfb140] "m"(b1a6350_cfb140), [c1aea90] "m"(b1a6350_c1aea90), [c1a2440] "m"(b1a6350_c1a2440), [c1a1e70] "m"(b1a6350_c1a1e70), [c1a0b30] "m"(b1a6350_c1a0b30), [c1b0d90] "m"(b1a6350_c1b0d90), [c1a2290] "m"(b1a6350_c1a2290), [pexit] "m"(b1a6350_pexit)
      : "memory");
}
#else
#error "FUN_001a6350: clang naked draft required"
#endif

/* --- units.obj orphan shells (2026-07-26) --- */

/* FUN_001a8770 (0x1a8770) — readable C lift. */
char FUN_001a8770(void *anim_state)
{
  unsigned char state = *((unsigned char *)anim_state + 0xb);

  return state >= 3 && state <= 4;
}

/* FUN_001a8890 (0x1a8890) — readable C lift. */
char FUN_001a8890(void *anim_state)
{
  unsigned char flag = *((unsigned char *)anim_state + 0xc);
  unsigned char state = *((unsigned char *)anim_state + 0xb);
  char result = (flag == 0);

  if (state >= 0x17 && state <= 0x23) {
    result = 0;
  } else if (state == 0x29) {
    result = 0;
  }
  return result;
}

/* 0x1a8910 — table lookup on anim_state@cx for states 0x1e..0x29.
 * XBE uses an in-function jump table; slot table is in .rodata so the PE
 * export ends at ret (same return polarity: 0 for slots marked 0). */
#if defined(__clang__)
__attribute__((unused))
static const unsigned char FUN_001a8910_slots[12] = {
    0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0,
};

/* 0x1a8910 — table lookup on anim_state@cx for states 0x1e..0x29.
 * XBE uses an in-function jump table; slot table is in .rodata so the PE
 * export ends at ret (same return polarity: 0 for slots marked 0). */
char FUN_001a8910(int16_t anim_state)
{
  static const unsigned char k_slot[] = {
      0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0,
  };
  int idx;

  idx = (int)anim_state - 0x1e;
  if ((unsigned int)idx > 0xb)
    return 1;
  return (char)k_slot[idx];
}


#else
char FUN_001a8910(int16_t anim_state)
{
  static const unsigned char k_slot[] = {
      0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0,
  };
  int idx;

  idx = (int)anim_state - 0x1e;
  if ((unsigned int)idx > 0xb)
    return 1;
  return (char)k_slot[idx];
}
#endif

/* 0x1a8950 — map (anim_state@cx, target_state@dx) pair to action id. */
int FUN_001a8950(int16_t anim_state, int16_t target_state)
{
  int result = 6;

  if (anim_state == 0 || anim_state == 2 || anim_state == 3) {
    if (target_state == 0 || target_state == 2 || target_state == 3)
      result = 1;
  }
  if (anim_state == 0x16 || anim_state == 0x15)
    result = 2;
  return result;
}

