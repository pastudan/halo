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

char *FUN_0008dc30(char *destination, const char *source)
{
  const char *source_cursor;
  char *destination_cursor;
  unsigned int source_size;

  if (destination == NULL || source == NULL) {
    display_assert("s1 && s2", "c:\\halo\\SOURCE\\cseries\\cseries.c", 0x122,
                   true);
    system_exit(-1);
  }

  source_cursor = source;
  while (*source_cursor != '\0') {
    source_cursor += 1;
  }
  source_size = (unsigned int)(source_cursor - source) + 1;

  destination_cursor = destination - 1;
  do {
    destination_cursor += 1;
  } while (*destination_cursor != '\0');

  {
    unsigned int i;
    for (i = source_size >> 2; i != 0; i -= 1) {
      *(uint32_t *)destination_cursor = *(const uint32_t *)source;
      source += 4;
      destination_cursor += 4;
    }
  }

  {
    unsigned int i;
    for (i = source_size & 3; i != 0; i -= 1) {
      *destination_cursor = *source;
      source += 1;
      destination_cursor += 1;
    }
  }

  return destination;
}

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
static void (*const b1234b0_c190a50)(void) = shader_type_is_valid_for_model;
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


/* FUN_001a67e0 (0x1a67e0)
 *
 * Searches the global animation-name table at 0x32d7c8 for an entry whose
 * first string (column 0) matches param_1. The table has 0xd1 rows of 2
 * char* pointers each (stride = 8 bytes). Returns the row index [0, 0xd0]
 * on match, or -1 if not found.
 *
 * Confirmed: MOVSX EAX,SI; MOV ECX,[EAX*8 + 0x32d7c8]; PUSH EDI (param_1);
 * PUSH ECX; CALL csstrcmp; TEST EAX,EAX; JZ found; INC ESI; CMP SI,0xd1;
 * JL loop. Found: MOV AX,SI; Not-found: MOV AX,BX (BX = -1 via OR EBX,-1).
 */
short FUN_001a67e0(const char *param_1)
{
  short sVar2;
  int iVar1;

  sVar2 = 0;
  do {
    iVar1 = csstrcmp(((const char **)0x32d7c8)[(int)sVar2 * 2], param_1);
    if (iVar1 == 0) {
      return sVar2;
    }
    sVar2 = sVar2 + 1;
  } while (sVar2 < 0xd1);
  return -1;
}


/* FUN_001a6820 (0x1a6820)
 *
 * Returns verify_tag_reference result for the animation at index bool(param_2)
 * (0 or 1, clamped to count-1) from the tag block at param_1+0x2a8.
 * Returns -1 if clamped index is negative (count == 0).
 *
 * Confirmed: MOV AL,[ebp+0xc]; XOR ECX,ECX; TEST AL,AL; MOV EAX,[edx+0x2a8];
 * SETNE CL; ADD EDX,0x2a8; DEC EAX; MOVSX ECX,CX; CMP ECX,EAX; JG skip;
 * MOV EAX,ECX; TEST AX,AX; JGE proceed; OR EAX,-1; RET.
 */
int FUN_001a6820(int param_1, char param_2)
{
  int iVar1;
  int *block;
  int bVal;

  bVal = (int)(short)(unsigned short)(param_2 != '\0');
  iVar1 = *(int *)(param_1 + 0x2a8) - 1;
  block = (int *)(param_1 + 0x2a8);
  if (bVal <= iVar1) {
    iVar1 = bVal;
  }
  if ((short)iVar1 < 0) {
    return -1;
  }
  return (int)verify_tag_reference(
    (int *)tag_block_get_element(block, (int)(short)iVar1, 0x30));
}

/* FUN_001a6870 (0x1a6870)
 *
 * Returns verify_tag_reference result for the animation at index bool(param_3)
 * (0 or 1, clamped) from a nested tag block. First gets element param_2 from
 * the block at param_1+0x2e4 (stride 0x11c), then reads sub-block at +0xdc.
 * Returns -1 if clamped index is negative.
 *
 * Confirmed: MOVSX EAX,CX (param_2); ADD ECX,0x2e4; CALL tag_block_get_element;
 * MOV DL,[ebp+0x10] (param_3); XOR ECX,ECX; TEST DL,DL; SETNE CL;
 * LEA EDX,[EAX+0xdc]; MOV EAX,[EDX]; DEC EAX; MOVSX ECX,CX; ...
 */
int FUN_001a6870(int param_1, short param_2, char param_3)
{
  int iVar1;
  int iVar2;
  int *block;
  int bVal;

  iVar1 =
    (int)tag_block_get_element((void *)(param_1 + 0x2e4), (int)param_2, 0x11c);
  bVal = (int)(short)(unsigned short)(param_3 != '\0');
  iVar2 = *(int *)(iVar1 + 0xdc) - 1;
  block = (int *)(iVar1 + 0xdc);
  if (bVal <= iVar2) {
    iVar2 = bVal;
  }
  if ((short)iVar2 < 0) {
    return -1;
  }
  return (int)verify_tag_reference(
    (int *)tag_block_get_element(block, (int)(short)iVar2, 0x30));
}

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

/* FUN_001a6cd0 (0x1a6cd0)
 *
 * Searches the 11-entry dialogue-category pointer table at 0x32de50 for a
 * case-sensitive match with param_1 using csstrcmp. Returns the index (0–10)
 * on success. On no match, returns 0 (BX register held zero throughout).
 *
 * Confirmed: XOR EBX,EBX; XOR ESI,ESI; MOVSX EAX,SI; MOV ECX,[EAX*4+table];
 * PUSH EDI; PUSH ECX; CALL csstrcmp; TEST EAX,EAX; JE found;
 * INC ESI; CMP SI,0xb; JL loop; MOV AX,BX; RET.
 * found: MOV AX,SI; RET.
 */
short FUN_001a6cd0(const char *param_1)
{
  unsigned short result;
  unsigned short i;

  result = 0;
  i = 0;
  do {
    if (csstrcmp(((char **)0x32de50)[(short)i], param_1) == 0) {
      return (short)i;
    }
    i++;
  } while ((short)i < 0xb);
  return (short)result;
}

/* FUN_001a6d10 (0x1a6d10) — unit_dialogue_format_speech_name
 *
 * Formats the current speech sound name for the given unit.
 * If the unit has no active speech (speech_count at +0x338 is 0),
 * outputs "<none>". Otherwise looks up the sound tag name via
 * tag_get_name(+0x33c), strips path components based on full_path flag,
 * and optionally prepends the dialogue variant name from FUN_001a67b0.
 *
 * full_path=0: uses strrchr to find last backslash (show filename only)
 * full_path!=0: uses strchr loop to strip all path prefix (show leaf)
 *
 * Returns the output buffer pointer.
 *
 * Confirmed: cdecl, 4 stack params (ADD ESP cleanup at callers).
 * Confirmed: snprintf = snprintf, tag_get_name = tag_get_name.
 * Confirmed: 0x257984 = "%s", 0x259f40 = "%s %s", 0x25ad08 = "<none>".
 */
char *FUN_001a6d10(int unit_handle, char full_path, int16_t max_len,
                   char *output)
{
  char *unit;
  char *current_name;
  char *found;
  char *variant_name;
  int16_t dialogue_index;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);

  if (*(int16_t *)(unit + 0x338) == 0) {
    snprintf(output, (int)max_len, "<none>");
    return output;
  }

  current_name = "<none>";
  if (*(int *)(unit + 0x33c) != -1) {
    current_name = (char *)tag_get_name(*(int *)(unit + 0x33c));
  }

  if (full_path == '\0') {
    found = strrchr(current_name, '\\');
    if (found != NULL) {
      current_name = found + 1;
    }
  } else {
    while (current_name != NULL) {
      found = crt_strchr(current_name, '\\');
      if (found == NULL) {
        break;
      }
      current_name = found + 1;
    }
  }

  dialogue_index = *(int16_t *)(unit + 0x33a);
  if (dialogue_index != -1) {
    if (full_path == '\0') {
      variant_name = FUN_001a67b0(dialogue_index, 0);
      snprintf(output, (int)max_len, "%s", variant_name);
      return output;
    }
    variant_name = FUN_001a67b0(dialogue_index, 0);
    snprintf(output, (int)max_len, "%s %s", variant_name, current_name);
    return output;
  }

  snprintf(output, (int)max_len, "%s", current_name);
  return output;
}

/* FUN_001a6e20 (0x1a6e20) — unit_dialogue_log_lost_speech
 *
 * Logs a "lost speech" debug message when a speech item is being replaced.
 * Only produces output when the debug flag at 0x5aca56 is nonzero.
 *
 * Looks up the unit's tag name via tag_get('unit'), then resolves the speech
 * item's dialogue name either via FUN_001a67b0 (if speech_item+2 != -1) or
 * via tag_get_name (if speech_item+4 != -1), falling back to "<unknown>".
 * Logs "lost <waiting|queued> speech <name>" via console_printf.
 *
 * Register args: unit_handle @<eax>, speech_item @<ecx>.
 * Stack arg: priority (short) — 2 = "waiting", otherwise "queued".
 *
 * Confirmed: PUSH EAX (unit_handle) / MOV ESI,ECX (speech_item) at entry.
 * Confirmed: PUSH 0x3 for object_get_and_verify_type.
 * Confirmed: CMP word [EBP+0x8],0x2 for priority check.
 * Confirmed: tag_get(0x756e6974, *unit) for unit tag name.
 * Confirmed: console_printf(0, "%s: lost %s speech %s", ...) at 0xff4d0.
 */
void FUN_001a6e20(int unit_handle, void *speech_item, short priority)
{
  char *unit;
  char *unit_tag;
  char *speech_name;
  char *lost_type;
  int16_t dialogue_index;
  int tag_index;
  char *found;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  if (speech_item == NULL) {
    display_assert("speech_item",
                   "c:\\halo\\SOURCE\\units\\unit_dialogue.c", 0x415, 1);
    system_exit(-1);
  }
  if (*(char *)0x5aca56 != '\0') {
    unit_tag = (char *)tag_get(0x756e6974, *(int *)unit);
    dialogue_index = *(int16_t *)((char *)speech_item + 2);
    if (dialogue_index != (int16_t)-1) {
      speech_name = (char *)FUN_001a67b0(dialogue_index, 0);
    } else {
      tag_index = *(int *)((char *)speech_item + 4);
      if (tag_index != -1) {
        speech_name = (char *)tag_get_name(tag_index);
        found = strrchr(speech_name, '\\');
        if (found != NULL) {
          speech_name = found + 1;
        }
      } else {
        speech_name = "<unknown>";
      }
    }
    if (priority == 2) {
      lost_type = "waiting";
    } else {
      lost_type = "queued";
    }
    console_printf(0, "%s: lost %s speech %s",
                   *(char **)(unit_tag + 0x2c), lost_type, speech_name);
  }
}

/* FUN_001a6ef0 (0x1a6ef0) — unit_dialogue_queue_speech_item
 *
 * Queues or promotes a speech item for the unit's dialogue system.
 * Three priority levels (param_2):
 *   1 = queue into backup slot (unit+0x368)
 *   2 = promote to current slot (unit+0x338), evicting existing if present
 *   3 = promote to current and clear backup if identical
 *
 * Copies 0x30 bytes (12 dwords, REP MOVSD with ECX=0xC) of speech data.
 * After promotion, copies timing fields from the speech item and computes
 * a vocalization timer from the sound tag's duration:
 *   timer = (duration_ms * 30) / 1000  (converting ms to 30Hz ticks).
 * If no sound tag is set, asserts unless it's a standalone server
 * or force_vocalizations is off.
 *
 * Confirmed: ADD ESP,0x8 after object_get_and_verify_type (cdecl, 2 args).
 * Confirmed: REP MOVSD with ECX=0xC for 0x30-byte copy.
 * Confirmed: IMUL ECX,0x1e / MUL 0x10624dd3 / SAR 0x6 = divide by 1000.
 * Confirmed: assert "speech_item" at line 0x12E, file unit_dialogue.c.
 * Confirmed: assert "AI_BEHAVIOR(force_vocalizations)" at line 0x168.
 * Confirmed: assert "unit->unit.speech.current.priority > _unit_speech_none"
 *            at line 0x16E.
 */
void FUN_001a6ef0(int unit_handle, short priority, void *speech_item)
{
  char *unit;
  int sound_tag_index;
  char *sound_tag;
  int duration_ticks;
  short game_conn;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  if (speech_item == NULL) {
    display_assert("speech_item",
                   "c:\\halo\\SOURCE\\units\\unit_dialogue.c", 0x12e, 1);
    system_exit(-1);
  }

  /* If unit has AI-controlled speech bit set, only allow priority 10 (override) */
  if ((*(uint8_t *)(unit + 0xb6) & 4) != 0 &&
      *(int16_t *)speech_item != 10) {
    return;
  }

  if (priority >= 2) {
    /* Promoting to current slot — log existing speech being evicted */
    if (*(int16_t *)(unit + 0x338) > 0 &&
        *(char *)(unit + 0x3a4) == '\0') {
      FUN_001a6e20(unit_handle, unit + 0x338, 2);
    }

    /* Copy 0x30 bytes of speech data to current slot (unit+0x338) */
    memcpy(unit + 0x338, speech_item, 0x30);

    /* If priority == 3, clear backup slot if it exists and isn't the same */
    if (priority == 3 && *(int16_t *)(unit + 0x368) > 0) {
      if (speech_item != (void *)(unit + 0x368)) {
        FUN_001a6e20(unit_handle, unit + 0x368, 1);
      }
      *(int16_t *)(unit + 0x368) = 0;
    }

    /* Copy timing/state fields from the speech item */
    *(uint16_t *)(unit + 0x3a8) = *(uint16_t *)(unit + 0x340);
    *(uint8_t *)(unit + 0x3a4) = 0;
    *(uint8_t *)(unit + 0x3a5) = 0;
    *(uint8_t *)(unit + 0x3a6) = 0;
    *(uint32_t *)(unit + 0x3b0) = 0xffffffff;
    *(uint16_t *)(unit + 0x3ae) = *(uint16_t *)(unit + 0x344);
    *(uint16_t *)(unit + 0x3ac) = *(uint16_t *)(unit + 0x342);

    /* Compute vocalization timer from sound tag duration */
    sound_tag_index = *(int *)(unit + 0x33c);
    if (sound_tag_index != -1) {
      sound_tag = (char *)tag_get(0x736e6421, sound_tag_index);
      duration_ticks = *(int *)(sound_tag + 0x84) * 30;
      *(int16_t *)(unit + 0x3aa) = (int16_t)(duration_ticks / 1000);
      return;
    }
    game_conn = game_connection();
    if (game_conn == 0 && *(char *)0x5ac9cd != '\0') {
      /* Standalone with force_vocalizations off — use default 45 ticks */
    } else {
      display_assert("AI_BEHAVIOR(force_vocalizations)",
                     "c:\\halo\\SOURCE\\units\\unit_dialogue.c", 0x168, 1);
      system_exit(-1);
    }
    *(int16_t *)(unit + 0x3aa) = 0x2d;
    return;
  }

  if (priority == 1) {
    /* Queue to backup slot */
    if (*(int16_t *)(unit + 0x338) < 1) {
      display_assert(
          "unit->unit.speech.current.priority > _unit_speech_none",
          "c:\\halo\\SOURCE\\units\\unit_dialogue.c", 0x16e, 1);
      system_exit(-1);
    }
    memcpy(unit + 0x368, speech_item, 0x30);
  }
}

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


/* FUN_001a74d0 (0x1a74d0) — unit_dialogue_scream
 *
 * Triggers a unit scream dialogue event. Maps scream_type [0..5] to a
 * dialogue index via switch:
 *   0 → 10 (pain_body_minor)
 *   1 → random 50/50: 0x27 (scream) or fall through to case 2
 *   2 → 11 (pain_body_major)
 *   3 → 12 (pain_shield)
 *   4 → 13 (pain_falling)
 *   5 → 0xb7 (183, death)
 * Then looks up the dialogue tag at unit+0x334, fetches the sound reference
 * at dialogue_index*0x10+0x1c, and calls FUN_001a68d0 to allocate a speech
 * slot. On success, builds a speech item struct (0x30 bytes) and queues it
 * via FUN_001a6ef0.
 *
 * Returns 1 on success, 0 if no dialogue tag or sound not available.
 *
 * Confirmed: cdecl, 2 stack params.
 * Confirmed: switch table at 0x1a7638 (6 entries).
 * Confirmed: 0x253398 = 0.5f for random threshold.
 * Confirmed: ai_communication_packet_new = ai_communication_packet_new.
 * Confirmed: merged ADD ESP,0x1c cleans csmemset(3)+packet_new(1)+6ef0(3).
 */
char FUN_001a74d0(int unit_handle, int scream_type)
{
  char *unit;
  int16_t dialogue_index;
  int dialogue_tag_index;
  char *dialogue_tag;
  uint32_t sound_ref;
  short result;
  char speech_buf[0x30];

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  dialogue_index = (int16_t)scream_type;

  if ((int16_t)scream_type < 0 || (int16_t)scream_type >= 6) {
    display_assert(
        "(scream_type >= 0) && (scream_type < NUMBER_OF_UNIT_SCREAM_TYPES)",
        "c:\\halo\\SOURCE\\units\\unit_dialogue.c", 599, 1);
    system_exit(-1);
  }

  switch ((int16_t)scream_type) {
  case 0:
    dialogue_index = 10;
    break;
  case 1:
    if (random_math_real((unsigned int *)get_global_random_seed_address()) < 0.5f) {
      dialogue_index = 0x27;
      break;
    }
    /* fall through */
  case 2:
    dialogue_index = 0xb;
    break;
  case 3:
    dialogue_index = 0xc;
    break;
  case 4:
    dialogue_index = 0xd;
    break;
  case 5:
    dialogue_index = 0xb7;
    break;
  default:
    display_assert("!\"unreachable\"",
                   "c:\\halo\\SOURCE\\units\\unit_dialogue.c", 0x27b, 1);
    system_exit(-1);
  }

  dialogue_tag_index = *(int *)(unit + 0x334);
  if (dialogue_tag_index != -1) {
    dialogue_tag = (char *)tag_get(0x75646c67, dialogue_tag_index);
    sound_ref = *(uint32_t *)(dialogue_tag + (int)dialogue_index * 0x10 + 0x1c);
    if (sound_ref != 0xffffffff) {
      result = FUN_001a68d0(unit_handle, 9, 1, 0, 0, &dialogue_index,
                            (int *)&sound_ref);
      if (result > 0) {
        csmemset(speech_buf, 0, 0x30);
        *(int16_t *)(speech_buf + 0x00) = 9;
        *(int16_t *)(speech_buf + 0x02) = dialogue_index;
        *(uint32_t *)(speech_buf + 0x04) = sound_ref;
        *(int16_t *)(speech_buf + 0x0c) = 7;
        ai_communication_packet_new(speech_buf + 0x10);
        FUN_001a6ef0(unit_handle, result, speech_buf);
        return 1;
      }
    }
  }
  return 0;
}

/* FUN_001a7650 (0x1a7650) — dialogue_definition_get_variant
 *
 * Searches the dialogue variants tag block at tag_data+0x2b4 for entries
 * matching the given dialogue_type. Collects up to 16 matching variant
 * indices into a local array. If exactly one match, returns that variant's
 * dialogue tag index. If multiple matches, picks one at random using
 * get_global_random_seed_address. Asserts if the chosen variant's dialogue
 * tag (0x75646c67 = "udlg") fails to load.
 *
 * Returns the dialogue tag index, or -1 if no matching variant found.
 *
 * Confirmed: thiscall — @ecx = tag_data pointer (MOV ESI,ECX at 0x1a7658).
 * Confirmed: 1 stack param = dialogue_type (int16_t).
 * Confirmed: tag_block at tag_data+0x2b4, element_size=0x18.
 * Confirmed: variant dialogue ref at element+0x14.
 * Confirmed: assert string "dialogue_definition_get(dialogue_index)" at 0x2b6874.
 * Confirmed: line 0x408 in unit_dialogue.c.
 */
int FUN_001a7650(void *tag_data, int dialogue_type)
{
  int *block;
  int count;
  int match_count;
  int16_t match_indices[16];
  int i;
  short *element;
  int16_t chosen;
  int chosen_element;
  int dialogue_tag_index;

  block = (int *)((char *)tag_data + 0x2b4);
  count = *block;
  match_count = 0;

  if (count > 0) {
    for (i = 0; i < count; i++) {
      element = (short *)tag_block_get_element(block, i, 0x18);
      if ((int16_t)dialogue_type == -1 || *element == (int16_t)dialogue_type) {
        match_indices[match_count] = (int16_t)i;
        match_count++;
      }
    }

    if ((int16_t)match_count > 0) {
      if ((int16_t)match_count == 1) {
        chosen = match_indices[0];
      } else {
        chosen = random_range(
            (unsigned int *)get_global_random_seed_address(),
            0, (int16_t)match_count);
        chosen = match_indices[chosen];
      }

      chosen_element = (int)tag_block_get_element(block, (int)chosen, 0x18);
      dialogue_tag_index = *(int *)(chosen_element + 0x14);

      if (tag_get(0x75646c67, dialogue_tag_index) == NULL) {
        display_assert("dialogue_definition_get(dialogue_index)",
                       "c:\\halo\\SOURCE\\units\\unit_dialogue.c", 0x408, 1);
        system_exit(-1);
      }

      return dialogue_tag_index;
    }
  }

  return -1;
}

/* FUN_001a7730 (0x1a7730) — unit_dialogue_select_variant
 *
 * Selects a dialogue variant for the unit. Queries FUN_001a7650 with the
 * unit's current dialogue type (+0x6e). If that fails (returns -1), tries
 * type 0 (default). If that also fails, tries type -1 (wildcard).
 * Stores the resulting dialogue tag index at unit+0x334.
 *
 * Confirmed: @eax = unit_handle (PUSH EAX at 001a7734).
 * Confirmed: FUN_001a7650 takes @ecx = tag data pointer, stack param = type.
 * Confirmed: three fallback calls in sequence.
 * Confirmed: result stored at [ESI + 0x334].
 */
void FUN_001a7730(int unit_handle)
{
  char *unit;
  char *tag_data;
  int result;
  int16_t dialogue_type;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  tag_data = (char *)tag_get(0x756e6974, *(int *)unit);

  dialogue_type = *(int16_t *)(unit + 0x6e);
  if (dialogue_type > 0) {
    result = FUN_001a7650(tag_data, (int)dialogue_type);
    if (result != -1) {
      *(int *)(unit + 0x334) = result;
      return;
    }
  }

  result = FUN_001a7650(tag_data, 0);
  if (result == -1) {
    result = FUN_001a7650(tag_data, -1);
  }
  *(int *)(unit + 0x334) = result;
}

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

/* FUN_001a8550 (0x1a8550) — acceleration plan evaluator
 *
 * Evaluates a 3-phase acceleration plan (accelerate, coast, decelerate)
 * over a given time delta. Each phase consumes time from delta_time and
 * updates position and velocity accordingly:
 *   Phase 1 (acceleration): v += accel*t, pos += (0.5*accel*t + vel)*t
 *   Phase 2 (coast):        pos += vel*t
 *   Phase 3 (deceleration): v += accel*t, pos += (0.5*accel*t + vel)*t
 *
 * Returns 1 if all time was consumed (plan still active), 0 if plan
 * complete or flag was already set.
 *
 * Confirmed: thiscall — @ecx = plan struct pointer.
 * Confirmed: 5 stack params: delta_time, position, out_pos*, velocity, out_vel*.
 * Confirmed: 0x253398 = 0.5f, 0x2533c0 = 0.0f.
 * Confirmed: plan+0x0c = accel1, +0x10 = dur1, +0x14 = dur2.
 * Confirmed: plan+0x18 = accel3, +0x1c = dur3.
 */
char FUN_001a8550(void *plan, float delta_time, float position, float *out_position,
                  float velocity, float *out_velocity)
{
  char done;
  float t;
  float vel;

  done = *(char *)plan;
  vel = velocity;

  if (done != 0 || !(*(float *)0x2533c0 < delta_time))
    goto store_out;

  /* Phase 1: acceleration */
  if (*(float *)0x2533c0 < *(float *)((char *)plan + 0x10)) {
    t = delta_time;
    if (*(float *)((char *)plan + 0x10) < delta_time)
      t = *(float *)((char *)plan + 0x10);
    position = (t * *(float *)((char *)plan + 0xc) * 0.5f + vel) * t + position;
    vel = t * *(float *)((char *)plan + 0xc) + vel;
    delta_time = delta_time - t;
  }

  if (!(*(float *)0x2533c0 < delta_time))
    goto store_out;

  /* Phase 2: coast */
  if (*(float *)0x2533c0 < *(float *)((char *)plan + 0x14)) {
    t = delta_time;
    if (*(float *)((char *)plan + 0x14) < delta_time)
      t = *(float *)((char *)plan + 0x14);
    position = vel * t + position;
    delta_time = delta_time - t;
  }

  if (!(*(float *)0x2533c0 < delta_time))
    goto store_out;

  /* Phase 3: deceleration */
  if (*(float *)0x2533c0 < *(float *)((char *)plan + 0x1c)) {
    t = delta_time;
    if (*(float *)((char *)plan + 0x1c) < delta_time)
      t = *(float *)((char *)plan + 0x1c);
    position = (0.5f * t * *(float *)((char *)plan + 0x18) + vel) * t + position;
    vel = t * *(float *)((char *)plan + 0x18) + vel;
    delta_time = delta_time - t;
  }

  if (*(float *)0x2533c0 < delta_time) {
    *out_position = position;
    *out_velocity = vel;
    return 1;
  }

store_out:
  *out_position = position;
  *out_velocity = vel;
  return done;
}

/* unit_animation_start_action (0x1a8990)
 *
 * Sets the unit's seated animation state by looking up an animation index from
 * the unit's animation tag hierarchy and calling model_animation_choose_random.
 *
 * When state == 0: clears unk_596 (animation state byte at 0x254) and sets
 * unk_602 (0x25a) to 0xffff (NONE), then returns.
 *
 * For state 1-9: walks the unit tag -> antr tag -> mode element -> sub-element
 * -> weapon-element hierarchy using unk_592/593/594 as indices. Then:
 *
 *   States 1-4, 8: index the animation kind table in the sub-element block
 *     (sub_element+0x98/0x9c). Kind indices: 0x15, 0x16, 0x17, 0x18, 0x14.
 *   States 5-7, 9: index the animation kind table in the weapon-element block
 *     (weapon_element+0x30/0x34). Sub-indices: 0, 1, 8, 9.
 *
 * If a valid animation index is found (DI != -1):
 *   - Calls object_set_region_count(object_handle, 6) unless state == 7.
 *   - Calls model_animation_choose_random(1, antr_tag_index, animation_index).
 *   - Stores result in unk_602 (0x25a), clears unk_604 (0x25c), sets
 *     unk_596 (0x254) to (uint8_t)state.
 *
 * Confirmed: switch jump table at 0x1a8af8 (9 entries for ECX=0-8).
 * Confirmed: MOVSX ECX,byte ptr [ESI+0x250/0x251/0x252] for tag block indices.
 * Confirmed: MOV byte ptr [ESI+0x254],CL; MOV word ptr [ESI+0x25a],AX.
 */
void unit_animation_start_action(int object_handle, int16_t state)
{
  unit_data_t *unit;
  char *unit_tag;
  char *antr_tag;
  char *mode_element;
  char *sub_element;
  char *weapon_element;
  int16_t animation_index;
  int anim_kind_idx;
  int anim_sub_idx;

  unit = (unit_data_t *)object_get_and_verify_type(object_handle, 3);

  if (state == 0) {
    unit->unk_596 = 0;
    unit->unk_602 = (uint16_t)0xffff;
    return;
  }

  unit_tag = (char *)tag_get(0x756e6974, unit->object.tag_index);
  antr_tag = (char *)tag_get(0x616e7472, *(int *)(unit_tag + 0x44));
  mode_element = (char *)tag_block_get_element(
    antr_tag + 0xc, (int)(int8_t)unit->unk_592, 0x64);
  sub_element = (char *)tag_block_get_element(mode_element + 0x58,
                                              (int)(int8_t)unit->unk_593, 0xbc);
  weapon_element = (char *)tag_block_get_element(
    sub_element + 0xb0, (int)(int8_t)unit->unk_594, 0x3c);

  animation_index = (int16_t)-1;

  switch (state) {
  case 1:
    anim_kind_idx = 0x15;
    goto lookup_sub;
  case 2:
    anim_kind_idx = 0x16;
    goto lookup_sub;
  case 3:
    anim_kind_idx = 0x17;
    goto lookup_sub;
  case 4:
    anim_kind_idx = 0x18;
    goto lookup_sub;
  case 8:
    anim_kind_idx = 0x14;
    goto lookup_sub;
  lookup_sub:
    if (anim_kind_idx < *(int *)(sub_element + 0x98))
      animation_index =
        *(int16_t *)(*(int *)(sub_element + 0x9c) + anim_kind_idx * 2);
    break;

  case 5:
    anim_sub_idx = 0;
    goto lookup_weapon;
  case 6:
    anim_sub_idx = 1;
    goto lookup_weapon;
  case 7:
    anim_sub_idx = 8;
    goto lookup_weapon;
  case 9:
    anim_sub_idx = 9;
    goto lookup_weapon;
  lookup_weapon:
    if (anim_sub_idx < *(int *)(weapon_element + 0x30))
      animation_index =
        *(int16_t *)(*(int *)(weapon_element + 0x34) + anim_sub_idx * 2);
    break;
  }

  if (animation_index != (int16_t)-1) {
    if (state != 7)
      object_set_region_count(object_handle, 6);
    unit->unk_602 = (int16_t)model_animation_choose_random(
      1, *(int *)(unit_tag + 0x44), animation_index);
    unit->unk_604 = 0;
    unit->unk_596 = (uint8_t)state;
  }
}

/* FUN_001a8b20 (0x1a8b20)
 *
 * Attempts to set the current weapon animation state on a unit by looking up
 * the appropriate animation index from the unit's animation tag data and
 * calling model_animation_choose_random to select the sequence.
 *
 * Resolves the animation graph via the unit tag (group 'unit') and its nested
 * animation data (group 'antr'). Navigates through the weapon's animation mode
 * and weapon-type blocks using per-unit indices (unk_592, unk_593, unk_594).
 *
 * The incoming state code is remapped to an animation table index:
 *   1 -> 4 (fire-1), 2 -> 5 (fire-2), 3 -> 6 (charged-1), 4 -> 7 (charged-2),
 *   5 -> 2 (chamber-1), 6 -> 3 (chamber-2)
 *
 * Early-outs:
 *   - state < unit->unk_597 (already at or past this state)
 *   - unk_595 is in the set of "active" animation states (0x17–0x23, 0x27,
 * 0x29)
 *   - table index out of range or entry == -1 (animation not defined)
 *
 * On success, writes the chosen random animation index into unk_606 (0x25e),
 * clears unk_608 (0x260), and sets unk_597 (0x255) = state.
 *
 * On failure, if developer mode is enabled (DAT_005054fb != 0) and this is a
 * biped (object.type == 0) with no seat (unk_586 == -1), prints a warning:
 *   MISSING: <tag_path> '<state_name> <mode_name>'
 */
void FUN_001a8b20(int object_handle, int16_t state)
{
  unit_data_t *unit;
  int16_t current_state;
  char *unit_tag;
  char *antr_tag;
  void *mode_block;
  void *type_block;
  void *dest_block;
  int anim_table_index;
  int16_t anim_index;
  int16_t chosen;

  unit = (unit_data_t *)object_get_and_verify_type(object_handle, 3);

  /* bail if already at or past this state */
  current_state = (int16_t)(int8_t)unit->unk_597;
  if (state < current_state) {
    return;
  }

  /* bail for specific animation states that are already active
   * (original sign-extends the state byte: movsbl 0x253(%esi)) */
  switch ((int8_t)unit->unk_595) {
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
    return;
  default:
    break;
  }

  /* navigate to the animation destination block for this unit's weapon type */
  unit_tag = tag_get(0x756e6974, *(int *)unit);
  antr_tag = tag_get(0x616e7472, *(int *)((char *)unit_tag + 0x44));
  mode_block = tag_block_get_element((char *)antr_tag + 0xc,
                                     (int)(int8_t)unit->unk_592, 0x64);
  type_block = tag_block_get_element((char *)mode_block + 0x58,
                                     (int)(int8_t)unit->unk_593, 0xbc);
  dest_block = tag_block_get_element((char *)type_block + 0xb0,
                                     (int)(int8_t)unit->unk_594, 0x3c);

  /* remap state code to animation table index */
  anim_table_index = -1;
  switch (state) {
  case 1:
    anim_table_index = 4;
    break;
  case 2:
    anim_table_index = 5;
    break;
  case 3:
    anim_table_index = 6;
    break;
  case 4:
    anim_table_index = 7;
    break;
  case 5:
    anim_table_index = 2;
    break;
  case 6:
    anim_table_index = 3;
    break;
  default:
    goto missing;
  }

  /* look up animation index in the destination block's array */
  if (anim_table_index < *(int *)((char *)dest_block + 0x30)) {
    anim_index =
      *(int16_t *)(*(int *)((char *)dest_block + 0x34) + anim_table_index * 2);
    if (anim_index != -1) {
      chosen = (int16_t)model_animation_choose_random(
        1, *(int *)((char *)unit_tag + 0x44), anim_index);
      unit->unk_606 = chosen;
      unit->unk_608 = 0;
      unit->unk_597 = (uint8_t)state;
      return;
    }
  }

missing:
  /* developer-mode warning: animation not defined */
  if (*(uint8_t *)0x5054fb != 0 && unit->object.type == 0 &&
      (int16_t)unit->unk_586 == -1) {
    const char *state_name = FUN_001205f0((void *)0x322148, anim_table_index);
    const char *tag_path =
      tag_name_strip_path(*(char **)((char *)unit_tag + 0x3c));
    console_warning("MISSING: %s '%s %s'", tag_path, state_name, type_block);
  }
}

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

/* unit_record_damage (0x1a8ee0)
 *
 * Records damage in the unit's 4-slot damage tracking array at +0x3E0.
 * Each slot is 16 bytes: [timestamp, damage_amount, killing_object, attacker_object].
 *
 * First scans existing slots for a matching attacker or killing object handle;
 * if found, accumulates damage and updates the timestamp. Otherwise, finds an
 * empty slot (timestamp == -1) or evicts the oldest slot with the smallest
 * accumulated damage.
 *
 * If notify_ai is true and attacker_team != NONE, checks team allegiance
 * and notifies the AI system about killing sprees. Resolves the actual
 * attacker unit by following the player->unit chain and seat hierarchy.
 *
 * Confirmed: SUB ESP,0x8; 4 callee-saved regs; 7 stack params.
 * Confirmed: LEA EAX,[EDI+0x3E4] — damage array starts at +0x3E4 (per-slot +0x4).
 * Confirmed: IMUL/FCOMP loop with 4 iterations.
 * Confirmed: assert "best_new_attacker_index!=NONE" at line 0x136C, file units.c.
 * Confirmed: game_time_get = game_time_get, game_allegiance_get_team_is_friendly = game_allegiance check.
 * Confirmed: ai_handle_killing_spree = ai_handle_killing_spree.
 */
void unit_record_damage(int unit_handle, float damage_amount, int16_t damage_type,
                        char notify_ai, int attacker_object, int16_t attacker_team,
                        int killing_object)
{
  char *unit;
  char found_existing;
  int timestamp;
  float *slot_damage;
  int i;
  int16_t empty_slot;
  int16_t best_damage_slot;
  int16_t best_oldest_slot;
  int16_t s;
  char *attacker_unit;
  int attacker_unit_handle;
  int seated_handle;
  int killing_spree_count;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  found_existing = 0;
  timestamp = game_time_get();

  /* Scan existing 4 slots for matching attacker or killing object */
  slot_damage = (float *)(unit + 0x3e4);
  i = 4;
  do {
    if ((attacker_object != -1 && *(int *)(((char *)slot_damage) + 8) == attacker_object) ||
        *(int *)(((char *)slot_damage) + 4) == killing_object) {
      *(int *)(((char *)slot_damage) - 4) = timestamp;
      found_existing = 1;
      *slot_damage = damage_amount + *slot_damage;
    }
    slot_damage = (float *)((char *)slot_damage + 0x10);
    i = i - 1;
  } while (i != 0);

  if (!found_existing) {
    /* Find an empty slot (timestamp == -1) */
    empty_slot = 0;
    do {
      if (*(int *)(unit + ((int)empty_slot + 0x3e) * 0x10) == -1) {
        goto write_slot;
      }
      empty_slot = empty_slot + 1;
    } while (empty_slot < 4);

    /* No empty slot — find the slot with the smallest damage (to evict) */
    best_damage_slot = 0;
    s = 1;
    do {
      if (*(float *)(unit + 0x3e4 + (int)best_damage_slot * 0x10) <
          *(float *)(unit + 0x3f4 + ((int)s - 1) * 0x10)) {
        best_damage_slot = s;
      }
      s = s + 1;
    } while (s < 4);

    /* Among remaining slots (excluding best_damage_slot), find the oldest */
    best_oldest_slot = -1;
    s = 0;
    do {
      if (s != best_damage_slot) {
        if (best_oldest_slot == -1 ||
            *(uint32_t *)(unit + 0x3e0 + (int)s * 0x10) <
                *(uint32_t *)(unit + ((int)best_oldest_slot + 0x3e) * 0x10)) {
          best_oldest_slot = s;
        }
      }
      s = s + 1;
    } while (s < 4);

    if (best_oldest_slot == -1) {
      display_assert("best_new_attacker_index!=NONE",
                     "c:\\halo\\SOURCE\\units\\units.c", 0x136c, 1);
      system_exit(-1);
    }

    empty_slot = best_oldest_slot;

  write_slot:
    {
      int slot_base;
      slot_base = (int)empty_slot * 0x10;
      *(int *)(unit + slot_base + 0x3ec) = attacker_object;
      *(int *)(unit + slot_base + 0x3e8) = killing_object;
      /* Store damage as raw float bits via int assignment matches original MOV */
      *(float *)(unit + slot_base + 0x3e4) = damage_amount;
      *(int *)(unit + ((int)empty_slot + 0x3e) * 0x10) = timestamp;
    }
  }

  /* AI notification section */
  if (notify_ai == '\0') {
    return;
  }
  if ((int16_t)attacker_team == -1) {
    return;
  }
  if (!game_allegiance_get_team_is_friendly(
          *(int16_t *)(unit + 0x68), attacker_team)) {
    return;
  }

  /* Resolve the actual attacking unit */
  attacker_unit = NULL;
  attacker_unit_handle = killing_object;
  if (attacker_object != -1) {
    {
      char *player_entry;
      player_entry = (char *)datum_get(*(void **)0x5aa6d4, attacker_object);
      seated_handle = *(int *)(player_entry + 0x34);
      if (seated_handle != -1) {
        attacker_unit = (char *)object_get_and_verify_type(seated_handle, 3);
        attacker_unit_handle = seated_handle;
        if (attacker_unit != NULL) {
          goto have_attacker;
        }
      }
    }
  }
  attacker_unit = (char *)object_try_and_get_and_verify_type(killing_object, 3);
  attacker_unit_handle = killing_object;
  if (attacker_unit == NULL) {
    return;
  }

have_attacker:
  /* Follow seat hierarchy (driver/gunner) to the controlling unit */
  if (damage_type == 9) {
    seated_handle = *(int *)(attacker_unit + 0x2d4);
  } else {
    seated_handle = *(int *)(attacker_unit + 0x2d8);
  }
  if (seated_handle != -1) {
    attacker_unit = (char *)object_get_and_verify_type(seated_handle, 3);
    attacker_unit_handle = seated_handle;
  }

  /* Skip AI-controlled units */
  if ((*(uint8_t *)(attacker_unit + 0xb6) & 4) != 0) {
    return;
  }

  /* Update killing spree counter */
  {
    int last_damage_time;
    last_damage_time = *(int *)(attacker_unit + 0x3dc);
    if (last_damage_time == -1 || last_damage_time + 0x78 < timestamp) {
      *(int16_t *)(attacker_unit + 0x3da) = 0;
    }
    *(int16_t *)(attacker_unit + 0x3da) =
        *(int16_t *)(attacker_unit + 0x3da) + 1;
    killing_spree_count = (int)(uint16_t) *(int16_t *)(attacker_unit + 0x3da);
    *(int *)(attacker_unit + 0x3dc) = timestamp;

    if (ai_handle_killing_spree(attacker_unit_handle,
                                (short)killing_spree_count) != '\0') {
      *(int16_t *)(attacker_unit + 0x3da) = 0;
    }
  }
}

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

/* unit_set_seat_state (0x1a9240)
 *
 * Computes a 3D position representing the unit's current seat state and writes
 * it into the caller-supplied float[3].
 *
 * Three major paths:
 *
 * 1. Unit has a parent (parent_object_index != -1):
 *    Copies the parent object's world position (offset 0x0C). If the parent's
 *    object type is 0 or 1 (biped/vehicle) and the unit has a valid seat
 *    definition index (unk_672 != -1), looks up the seat's marker name (at
 *    seat_def + 0x84) and resolves it on the parent via
 *    object_get_markers_by_string_id. For seat type 1, skips if the marker
 *    name byte at seat_def + 0x84 is zero.
 *
 * 2. Unit has no parent and no special flags:
 *    If unit flags byte (0xB6) bit 2 is clear AND object type is 0 (biped),
 *    delegates to biped_estimate_position with zeroed optional parameters.
 *
 * 3. Unit has no parent but has flags/non-zero type:
 *    If unk_728 is NONE, gets the "head" marker on the unit itself. Otherwise,
 *    resolves unk_728 as a unit, reads its seat index (unk_672), looks up the
 *    seat definition's marker name (seat_def + 0x24) from the original unit's
 *    tag, and resolves it on the original unit via
 * object_get_markers_by_string_id.
 */
void unit_set_seat_state(int unit_handle, float *position)
{
  char *unit;
  char *unit_tag;
  int seat_index;
  char *seat_object;
  char *parent_unit;
  char *seat_def;
  int16_t seat_def_index;
  uint8_t seat_type;
  uint32_t type_mask;
  char marker_buf[0x6c];

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (char *)tag_get(0x756e6974, *(int *)unit);
  seat_index = *(int *)(unit + 0xcc);

  if (seat_index == -1) {
    /* Unit is not in a seat */
    if (!(*(uint8_t *)(unit + 0xb6) & 0x04) && *(int16_t *)(unit + 0x64) == 0) {
      /* Simple biped with no special flags — delegate to
       * biped_estimate_position */
      biped_estimate_position(unit_handle, 0, (vector3_t *)0,
                              (vector3_t *)0, /* dup-args-ok */
                              (vector3_t *)0, (vector3_t *)position);
      return;
    }

    /* Has flags or non-zero type: check unk_728 */
    if (*(int *)(unit + 0x2d8) == -1) {
      /* No related unit — find "head" marker on this unit */
      object_get_markers_by_string_id(unit_handle, (void *)0x2909e4, marker_buf,
                                      1);
      position[0] = *(float *)(marker_buf + 0x60);
      position[1] = *(float *)(marker_buf + 0x64);
      position[2] = *(float *)(marker_buf + 0x68);
      return;
    }

    /* Related unit exists — get its seat definition */
    parent_unit = (char *)object_get_and_verify_type(*(int *)(unit + 0x2d8), 3);
    seat_def_index = *(int16_t *)(parent_unit + 0x2a0);
    seat_def = (char *)tag_block_get_element(unit_tag + 0x2e4,
                                             (int)seat_def_index, 0x11c);
    object_get_markers_by_string_id(unit_handle, seat_def + 0x24, marker_buf,
                                    1);
    position[0] = *(float *)(marker_buf + 0x60);
    position[1] = *(float *)(marker_buf + 0x64);
    position[2] = *(float *)(marker_buf + 0x68);
    return;
  }

  /* Unit IS in a seat — seat_index is the parent object handle */
  seat_object = (char *)object_get_and_verify_type(seat_index, -1);

  /* Copy seat object's world position */
  position[0] = *(float *)(seat_object + 0x0c);
  position[1] = *(float *)(seat_object + 0x10);
  position[2] = *(float *)(seat_object + 0x14);

  /* Check if seat type is biped (0) or vehicle (1) */
  seat_type = *(uint8_t *)(seat_object + 0x64);
  type_mask = 1 << seat_type;
  if (!(type_mask & 0x03))
    return;

  /* Seat type is 0 or 1 — refine position from seat marker */
  if (*(int16_t *)(unit + 0x2a0) == -1)
    return;

  /* Get the seat definition from the parent's unit tag */
  unit_tag = (char *)tag_get(0x756e6974, *(int *)seat_object);
  seat_def_index = *(int16_t *)(unit + 0x2a0);
  seat_def =
    (char *)tag_block_get_element(unit_tag + 0x2e4, (int)seat_def_index, 0x11c);

  /* For seat type 1 (vehicle), skip if marker name at +0x84 is empty */
  if (*(int16_t *)(seat_object + 0x64) == 1) {
    if (*(uint8_t *)(seat_def + 0x84) == 0)
      return;
  }

  /* Look up the seat marker on the parent object */
  object_get_markers_by_string_id(*(int *)(unit + 0xcc), seat_def + 0x84,
                                  marker_buf, 1);
  position[0] = *(float *)(marker_buf + 0x60);
  position[1] = *(float *)(marker_buf + 0x64);
  position[2] = *(float *)(marker_buf + 0x68);
}

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

/* unit_impulse_to_animation_kind (0x1a9560)
 *
 * Maps an animation impulse index (0-13) to an animation kind index and an
 * update_kind value. The impulse index selects an animation kind (e.g. 0x1d
 * for "impulse", 0x20 for "melee_attack_long_step", etc.) and writes 3 or 6
 * to *out_update_kind depending on whether the impulse uses a ranged or melee
 * update mode.
 *
 * If impulse_index is out of [0, 13] the function asserts and terminates.
 * If out_update_kind is NULL the write is skipped (TEST EBX,EBX gate).
 *
 * Impulse-to-kind mapping (jump table at 0x1a969c):
 *   0  -> 0x1d  (update 6)   8  -> 0x04  (update 3)
 *   1  -> 0x20  (update 6)   9  -> 0x05  (update 3)
 *   2  -> 0x21  (update 6)   10 -> 0x06  (update 3)
 *   3  -> 0x22  (update 6)   11 -> 0x07  (update 3)
 *   4  -> 0x1b  (update 3)   12 -> 0x28  (update 6)
 *   5  -> 0x1c  (update 3)   13 -> 0x29  (update 6)
 *   6  -> 0x1e  (update 6)
 *   7  -> 0x1f  (update 6)
 *
 * Register args: impulse_index @<ax>, out_update_kind @<ebx>.
 * Returns kind index in AX (int16_t).
 *
 * Confirmed: MOV DI,AX at entry; switch dispatch from 0x1a969c.
 * Confirmed: MOV word ptr [EBX],0x3 or 0x6; MOV AX,SI; RET.
 * Confirmed: assert "animation_impulse>=0 &&
 * animation_impulse<NUMBER_OF_UNIT_ANIMATION_IMPULSES" file
 * "c:\\halo\\SOURCE\\units\\units.c", line 0x14f4.
 * Confirmed: kind init to -1 at entry (OR ESI,-1); two jump-table switches
 * (0x1a969c kind, 0x1a96d4/0x1a96dc update) each with a NULL-message assert
 * default (lines 0x1507, 0x1524).
 */
int16_t unit_impulse_to_animation_kind(int16_t impulse_index,
                                       int16_t *out_update_kind)
{
  int idx;
  int16_t kind = -1;

  if (impulse_index < 0 || impulse_index >= 14) {
    display_assert("animation_impulse>=0 && "
                   "animation_impulse<NUMBER_OF_UNIT_ANIMATION_IMPULSES",
                   "c:\\halo\\SOURCE\\units\\units.c", 0x14f4, 1);
    system_exit(-1);
  }

  idx = impulse_index;
  switch (idx) {
  case 0:  kind = 0x1d; break;
  case 1:  kind = 0x20; break;
  case 2:  kind = 0x21; break;
  case 3:  kind = 0x22; break;
  case 4:  kind = 0x1b; break;
  case 5:  kind = 0x1c; break;
  case 6:  kind = 0x1e; break;
  case 7:  kind = 0x1f; break;
  case 8:  kind = 0x04; break;
  case 9:  kind = 0x05; break;
  case 10: kind = 0x06; break;
  case 11: kind = 0x07; break;
  case 12: kind = 0x28; break;
  case 13: kind = 0x29; break;
  default:
    display_assert(NULL, "c:\\halo\\SOURCE\\units\\units.c", 0x1507, 1);
    system_exit(-1);
    break;
  }

  if (out_update_kind != NULL) {
    switch (idx) {
    case 4:
    case 5:
    case 8:
    case 9:
    case 10:
    case 11:
      *out_update_kind = 3;
      break;
    case 0:
    case 1:
    case 2:
    case 3:
    case 6:
    case 7:
    case 12:
    case 13:
      *out_update_kind = 6;
      break;
    default:
      display_assert(NULL, "c:\\halo\\SOURCE\\units\\units.c", 0x1524, 1);
      system_exit(-1);
      break;
    }
  }

  return kind;
}

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

/* FUN_001aa360 (0x1aa360) — unit_set_user_animation
 *
 * Validates a user animation index against the range
 * [0, NUMBER_OF_UNIT_USER_ANIMATIONS). The function resolves the unit tag
 * and its animation tag (antr) but does not use them beyond validation.
 * Asserts if the index is out of range. Returns 0 (AL cleared to 0).
 *
 * Confirmed: cdecl, 3 stack params (unit_handle, param_2, index).
 * Confirmed: assert "index>=0 && index<NUMBER_OF_UNIT_USER_ANIMATIONS"
 *   at line 0x1a21 in units.c.
 * Confirmed: NUMBER_OF_UNIT_USER_ANIMATIONS == 2 (CMP AX,0x2).
 * Confirmed: returns AL=0 (XOR AL,AL at 001aa3bb).
 */
char FUN_001aa360(int unit_handle, int param_2, int16_t index)
{
  char *unit;
  int unit_tag_index;
  char *unit_tag;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  unit_tag_index = *(int *)unit;
  unit_tag = (char *)tag_get(0x756e6974, unit_tag_index);
  tag_get(0x616e7472, *(int *)(unit_tag + 0x44));

  if (index < 0 || index >= 2) {
    display_assert("index>=0 && index<NUMBER_OF_UNIT_USER_ANIMATIONS",
                   "c:\\halo\\SOURCE\\units\\units.c", 0x1a21, 1);
    system_exit(-1);
  }

  return 0;
}

/* FUN_001aa430 (0x1aa430) — unit_can_see_point
 *
 * Returns true if the given point is within the unit's field of view.
 * Computes a direction vector from the unit's head marker to the target
 * point, normalizes it, then takes the dot product with the unit's
 * facing/aiming vector at +0x210. Compares against cos(param_3) where
 * param_3 is the half-angle of the vision cone.
 *
 * Returns false if unit_handle is NONE (-1).
 *
 * Confirmed: cdecl, 3 stack params (unit_handle, point, half_angle).
 * Confirmed: "head" marker name at 0x2909e4.
 * Confirmed: marker buffer 0x78 bytes, position at buffer+0x60.
 * Confirmed: FPU dot product order: z*fz + y*fy + x*fx.
 * Confirmed: FCOS + FCOMPP comparison: dot > cos(angle) → return 1.
 * Confirmed: normalize3d return (magnitude) discarded via FSTP ST0.
 */
char FUN_001aa430(int unit_handle, float *point, float half_angle)
{
  char *unit;
  char marker_buf[0x78];
  float *marker_pos;
  float dir[3];
  float dot;

  if (unit_handle == -1) {
    return 0;
  }

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  object_get_markers_by_string_id(unit_handle, (void *)0x2909e4,
                                  marker_buf, 1);

  /* dir = point - head_marker_position. The original keeps dir as a single
   * contiguous 3-float vector ([ebp-0xc/-0x8/-0x4]) and passes its base to
   * normalize3d, which reads all three components in place. dir MUST be an
   * array, not three separate float locals: clang scatters separate locals
   * across non-adjacent (and reordered) stack slots, so normalize3d(&dir_x)
   * would read uninitialized stack for components [1] and [2] -> huge garbage
   * -> normalize collapse -> assert_valid_real_normal3d crash (PoA marines). */
  marker_pos = (float *)(marker_buf + 0x60);
  dir[0] = point[0] - marker_pos[0];
  dir[1] = point[1] - marker_pos[1];
  dir[2] = point[2] - marker_pos[2];

  normalize3d(dir);

  dot = dir[0] * *(float *)(unit + 0x210) +
        dir[1] * *(float *)(unit + 0x214) +
        dir[2] * *(float *)(unit + 0x218);

  if (dot > x87_fcos(half_angle)) {
    return 1;
  }

  return 0;
}

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

/* FUN_001ab870 (0x1ab870)
 * Updates an animation state and optionally triggers an impulse sound.
 * Calls animation_update_internal with update_kind=1, using the animation
 * graph tag index and state pointer passed via @ecx/@edx.
 * If the update produces a sound index (!= -1), plays it via
 * object_impulse_sound_new with scale 1.0. Returns the animation result. */
int16_t FUN_001ab870(void *animation_state, int animation_graph_tag_index,
                     int unit_handle)
{
  int16_t result;
  int sound_index;

  result = (int16_t)animation_update_internal(
      1, animation_graph_tag_index, (short *)animation_state, &sound_index);
  if (sound_index != -1) {
    object_impulse_sound_new(unit_handle, sound_index, 0,
                             *(float **)0x31fc1c,
                             *(float **)0x31fc3c, 1.0f);
  }
  return result;
}

/* FUN_001ab8c0 (0x1ab8c0)
 * Computes or copies lighting data for a unit.
 * If the unit has a parent unit (at +0xcc), copies the parent's lighting
 * values from +0x290 and +0x294. Otherwise, computes an ambient RGB color
 * brightness and self-illumination value from the unit's position and
 * orientation. */
void FUN_001ab8c0(int unit_handle)
{
  char *unit;
  void *parent;
  float color[3];

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  parent = object_try_and_get_and_verify_type(
      *(int *)(unit + 0xcc), 3);
  if (parent == NULL) {
    FUN_0013a740((int)(unit + 0xc), (int)(unit + 0x48), color);
    *(float *)(unit + 0x290) = real_rgb_color_brightness(color);
    *(float *)(unit + 0x294) = object_get_self_illumination(unit_handle);
    return;
  }
  *(float *)(unit + 0x290) = *(float *)((char *)parent + 0x290);
  *(float *)(unit + 0x294) = *(float *)((char *)parent + 0x294);
}

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

/* FUN_001ad260 (0x1ad260) — unit animation state transition
 *
 * Sets the unit's animation state (unk_595 at offset 0x253). Looks up the
 * correct animation from the unit tag's animation graph hierarchy based on
 * the desired state (param_2). There are two lookup paths:
 *
 *   1. Mode-relative: looks up in the mode's animation block at mode+0x98/0x9c
 *      using a "mode animation index" (EBX path).
 *   2. Overlay-relative: looks up in the unit mode's overlay block at
 *      unit_mode+0x40/0x44 using an "overlay index" (local_c path).
 *
 * After lookup, calls model_animation_choose_random (model_animation_choose_random) and
 * unit_set_animation to apply. Handles developer-mode missing-animation
 * warnings. Also resolves the "weapon idle" overlay and stores it.
 *
 * Called by unit_abort_animation, unit_open, unit_close, and others.
 *
 * Returns 1 on success, 0 on failure (animation not found for certain states).
 *
 * Confirmed: cdecl, 2 stack params (unit_handle, anim_state as int16_t).
 * Confirmed: jump table at 0x1ad714 (44 entries for states 0..0x2b).
 * Confirmed: calls unit_set_animation(@eax,@edi,@bx).
 * Confirmed: calls FUN_001a88b0(@ecx = anim_state).
 * Confirmed: DAT_005054fb = developer mode flag.
 * Confirmed: 0x322308 = mode anim name table, 0x322450 = overlay anim name table.
 */
char FUN_001ad260(int unit_handle, int16_t anim_state)
{
  int *unit;
  char *unit_tag;
  char *antr_tag;
  char *unit_mode;
  char *mode_block;
  int anim_graph_tag_index;
  int16_t mode_anim_index;
  int16_t overlay_index;
  int16_t anim_index;
  char old_state_byte;
  int16_t old_state;
  char was_none;
  char did_change;
  int16_t weapon_idle_anim;
  int16_t transition_speed;

  unit = (int *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (char *)tag_get(0x756e6974, *unit);
  anim_graph_tag_index = *(int *)(unit_tag + 0x44);
  antr_tag = (char *)tag_get(0x616e7472, anim_graph_tag_index);

  unit_mode = (char *)tag_block_get_element(antr_tag + 0xc,
      (int)*(signed char *)((char *)unit + 0x250), 100);
  mode_block = (char *)tag_block_get_element(unit_mode + 0x58,
      (int)*(signed char *)((char *)unit + 0x251), 0xbc);
  tag_block_get_element(mode_block + 0xb0,
      (int)*(signed char *)((char *)unit + 0x252), 0x3c);

  old_state_byte = *((char *)unit + 0x253);
  old_state = (int16_t)old_state_byte;
  was_none = (old_state_byte == -1);
  did_change = 0;

  if (!was_none && anim_state == old_state)
    goto resolve_weapon_idle;

  mode_anim_index = -1;
  overlay_index = -1;

  if (old_state_byte == 0x21) {
    FUN_001ab110(unit_handle, 1);
  }

  if ((int)anim_state > 0x2b)
    goto set_not_found;

  /* Map anim_state to either a mode animation index or overlay index.
   *
   * NOTE: the original (0x1ad331) lowers this as a jump table whose per-case
   * bodies are "MOV <index>,imm; JMP <shared lookup>". VC71 /O2 instead lowers
   * this "switch selects a constant" pattern as a value-lookup array (compact
   * data table) regardless of whether the cases use break OR goto to a shared
   * label (confirmed 2026-07-08: rewriting all 29 mode cases as `goto mode_path`
   * produced byte-identical 160-insn codegen). The original's jump-table shape
   * came from different build flags, not source structure; it is unreachable
   * from C here. This is a codegen selection difference, not a semantic one:
   * the case->index mapping below is byte-verified against the jump-table
   * bodies at 0x1ad338-0x1ad4a2. */
  switch ((int)anim_state) {
  case 0:  mode_anim_index = 0; break;
  case 1:  mode_anim_index = 1; break;
  case 2:  mode_anim_index = 2; break;
  case 3:  mode_anim_index = 3; break;
  case 4:  mode_anim_index = 8; break;
  case 5:  mode_anim_index = 9; break;
  case 6:  mode_anim_index = 10; break;
  case 7:  mode_anim_index = 11; break;
  case 8:  mode_anim_index = 0x23; break;
  case 9:  mode_anim_index = 0x24; break;
  case 10: mode_anim_index = 0x25; break;
  case 11: mode_anim_index = 0x26; break;
  case 12: mode_anim_index = 12; break;
  case 13: mode_anim_index = 13; break;
  case 14: mode_anim_index = 14; break;
  case 15: mode_anim_index = 15; break;
  case 0x14: mode_anim_index = 0x10; break;
  case 0x15: mode_anim_index = 0x11; break;
  case 0x16: mode_anim_index = 0x12; break;
  case 0x1e: mode_anim_index = 0x27; break;
  case 0x1f: mode_anim_index = 0x2a; break;
  case 0x20: mode_anim_index = 0x2e; break;
  case 0x21: mode_anim_index = 0x14; break;
  case 0x22: mode_anim_index = 0x2c; break;
  case 0x23: mode_anim_index = 0x2d; break;
  case 0x24: mode_anim_index = 0x2f; break;
  case 0x27: mode_anim_index = 0x30; break;
  case 0x28: mode_anim_index = 0x31; break;
  case 0x29: mode_anim_index = 0x32; break;
  case 0x10: overlay_index = 0x17; goto overlay_path;
  case 0x11: overlay_index = 0x18; goto overlay_path;
  case 0x12: overlay_index = 0x19; goto overlay_path;
  case 0x13: overlay_index = 0x1a; goto overlay_path;
  case 0x18: overlay_index = 0; goto overlay_path;
  case 0x19: overlay_index = 1; goto overlay_path;
  case 0x25: overlay_index = 0x1b; goto overlay_path;
  case 0x26: overlay_index = 0x1c; goto overlay_path;
  case 0x2b: overlay_index = 0x1d; goto overlay_path;
  default:
    goto set_not_found;
  }

  /* Mode animation lookup path */
  if ((int)mode_anim_index < *(int *)(mode_block + 0x98)) {
    anim_index = *(int16_t *)(*(int *)(mode_block + 0x9c) +
                              (int)mode_anim_index * 2);
  } else {
    goto set_not_found;
  }
  goto check_found;

overlay_path:
  /* Overlay animation lookup path */
  if ((int)overlay_index >= *(int *)(unit_mode + 0x40))
    goto set_not_found;
  anim_index = *(int16_t *)(*(int *)(unit_mode + 0x44) +
                            (int)overlay_index * 2);
  goto check_found;

set_not_found:
  anim_index = -1;

check_found:
  /* Check if animation was found */
  if (*(uint8_t *)0x5054fb != 0 && *(int16_t *)((char *)unit + 0x64) == 0) {
    /* Developer mode: warn about missing animations */
    if (anim_index == -1) {
      const char *mn;
      const char *on;
      if (mode_anim_index != -1) {
        mn = FUN_001205f0((void *)0x322308, mode_anim_index);
      } else {
        mn = (const char *)0x25386f;
      }
      if (overlay_index != -1) {
        on = (const char *)FUN_001205f0((void *)0x322450, overlay_index);
      } else {
        on = (const char *)mode_block;
      }
      console_warning("MISSING: %s \'%s %s %s\'",
          tag_name_strip_path(*(const char **)(unit_tag + 0x3c)),
          unit_mode, on, mn);
      goto check_early_return;
    }
  } else {
    if (anim_index == -1)
      goto check_early_return;
  }
  goto apply_animation;

check_early_return:
  /* For certain states, return 0 if animation not found */
  switch ((int)anim_state) {
  case 0x1e:
  case 0x1f:
  case 0x20:
  case 0x21:
  case 0x27:
  case 0x29:
    return 0;
  }

apply_animation:
  anim_index = (int16_t)model_animation_choose_random(1, anim_graph_tag_index,
                                                       anim_index);
  unit_set_animation(unit_handle, anim_graph_tag_index, anim_index);

  old_state = (int16_t)(signed char)*((char *)unit + 0x253);

  /* Determine transition speed */
  transition_speed = 6;
  if ((anim_state == 0 || anim_state == 2 || anim_state == 3) &&
      (old_state == 0 || old_state == 2 || old_state == 3)) {
    transition_speed = 1;
  }
  if (anim_state == 0x16 || anim_state == 0x15) {
    transition_speed = 2;
  }

  did_change = 1;

resolve_weapon_idle:
  {
    int16_t new_weapon_idle;

    new_weapon_idle = FUN_001a88b0(anim_state);

    if (was_none || new_weapon_idle != FUN_001a88b0(old_state)) {
      /* Resolve weapon idle animation */
      if (new_weapon_idle >= 0 &&
          (int)new_weapon_idle < *(int *)(mode_block + 0x98)) {
        weapon_idle_anim = *(int16_t *)(*(int *)(mode_block + 0x9c) +
                                        (int)new_weapon_idle * 2);
      } else {
        weapon_idle_anim = -1;
      }

      weapon_idle_anim = (int16_t)model_animation_choose_random(
          1, anim_graph_tag_index, weapon_idle_anim);
      *(int16_t *)((char *)unit + 0x24a) = weapon_idle_anim;

      if (*(uint8_t *)0x5054fb != 0 &&
          *(int16_t *)((char *)unit + 0x64) == 0 &&
          weapon_idle_anim == -1 && new_weapon_idle != -1) {
        const char *wn = FUN_001205f0((void *)0x322308, (int16_t)new_weapon_idle);
        console_warning("MISSING: %s \'%s %s %s\'",
            tag_name_strip_path(*(const char **)(unit_tag + 0x3c)),
            unit_mode, mode_block, wn);
      }

      if (was_none) {
        /* Resolve base weapon overlay (index 9) */
        if (*(int *)(unit_mode + 0x40) > 9) {
          weapon_idle_anim = *(int16_t *)(*(int *)(unit_mode + 0x44) + 0x12);
        } else {
          weapon_idle_anim = -1;
        }
        weapon_idle_anim = (int16_t)model_animation_choose_random(
            1, anim_graph_tag_index, weapon_idle_anim);
        *(int16_t *)((char *)unit + 0x24c) = weapon_idle_anim;

        if (*(uint8_t *)0x5054fb != 0 &&
            *(int16_t *)((char *)unit + 0x64) == 0 &&
            weapon_idle_anim == -1) {
          const char *oln = FUN_001205f0((void *)0x322450, 9);
          console_warning("MISSING: %s \'%s %s\'",
              tag_name_strip_path(*(const char **)(unit_tag + 0x3c)),
              unit_mode, oln);
        }

        transition_speed = 6;
      }
    } else if (did_change == 0) {
      goto skip_transition;
    }

    object_set_region_count(unit_handle, transition_speed);
  }

skip_transition:
  *((char *)unit + 0x253) = (char)anim_state;
  return 1;
}

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

/* FUN_001b2780 / unit_new (0x1b2780)
 *
 * Unit creation/initialization. Called when a new unit object is created.
 * Sets default values for all unit-specific fields: weapons, seats,
 * animation state, aiming vectors, control flags, etc.
 * Copies the object's forward vector to all 5 directional vector slots.
 * If the unit tag has initial seat occupancy data and a valid dialog
 * entry, assigns equipment creation. Returns 1 on success, 0 if the
 * unit tag's animation graph index is -1.
 *
 * Confirmed: 1 cdecl param (unit_handle), returns char (0 or 1).
 */
char FUN_001b2780(int unit_handle)
{
  char *unit;
  char *unit_tag;
  float *forward;
  char valid;
  int i;
  short seat_idx;
  char *seat_entry;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (char *)tag_get(0x756e6974, *(int *)unit);

  if (*(int *)(unit_tag + 0x44) == -1) { /* animation graph index */
    return 0;
  }

  /* Initialize weapon slots to -1 */
  *(int *)(unit + 0x2c8) = -1;
  csmemset((void *)(unit + 0x2a8), 0xff, 0x10);

  /* Initialize animation/seat tracking fields */
  *(int16_t *)(unit + 0x2a2) = -1;
  *(int16_t *)(unit + 0x2a4) = -1;
  *(uint8_t *)(unit + 0x2cc) = 0xff;
  *(uint8_t *)(unit + 0x2cd) = 0xff;
  *(uint8_t *)(unit + 0x2d0) = 0xff;
  *(uint8_t *)(unit + 0x2d1) = 0xff;
  *(int *)(unit + 0x1c8) = -1;
  *(int *)(unit + 0x1a4) = -1;
  *(int *)(unit + 0x1a8) = -1;
  *(int *)(unit + 0x1ac) = -1;
  *(int *)(unit + 0x1b0) = -1;
  *(int16_t *)(unit + 0x2a0) = -1;
  *(int *)(unit + 0x2d4) = -1;
  *(int *)(unit + 0x2d8) = -1;

  /* Clear base seat/weapon fields */
  *(int16_t *)(unit + 0x248) = 0;
  *(uint8_t *)(unit + 0x250) = 0xff;
  *(uint8_t *)(unit + 0x251) = 0xff;
  *(uint8_t *)(unit + 0x252) = 0xff;
  *(uint8_t *)(unit + 0x253) = 0xff;
  *(uint8_t *)(unit + 0x254) = 0;
  *(uint8_t *)(unit + 0x255) = 0;
  *(int16_t *)(unit + 0x24a) = -1;
  *(int16_t *)(unit + 0x24c) = -1;
  *(int16_t *)(unit + 0x25a) = -1;
  *(int16_t *)(unit + 0x25e) = -1;
  *(int16_t *)(unit + 0x262) = -1;
  *(uint8_t *)(unit + 0x257) = 2;
  *(int16_t *)(unit + 0x24e) = -1;
  *(uint8_t *)(unit + 0x258) = 0xff;
  *(int16_t *)(unit + 0x1ce) = -1;
  *(uint8_t *)(unit + 0x1bf) = 0xff;
  *(uint8_t *)(unit + 0x266) = 0;

  /* Zero-fill aiming/looking orientation buffers */
  csmemset((void *)(unit + 0x268), 0, 0x10);
  *(uint8_t *)(unit + 0x267) = 0;
  csmemset((void *)(unit + 0x278), 0, 0x10);

  /* Validate forward vector */
  forward = (float *)(unit + 0x24);
  valid = (char)valid_real_normal3d(forward);
  if (valid == 0) {
    csprintf((char *)0x5ab100,
             "%s: assert_valid_real_normal3d(%f, %f, %f)",
             "&unit->object.forward", (double)forward[0],
             (double)*(float *)(unit + 0x28),
             (double)*(float *)(unit + 0x2c),
             "c:\\halo\\SOURCE\\units\\units.c", 0x189, true);
    display_assert((char *)0x5ab100, "c:\\halo\\SOURCE\\units\\units.c",
                   0x189, true);
    system_exit(-1);
  }

  /* Copy forward vector to all 5 direction vector slots */
  *(float *)(unit + 0x210) = forward[0];
  *(float *)(unit + 0x214) = *(float *)(unit + 0x28);
  *(float *)(unit + 0x218) = *(float *)(unit + 0x2c);
  *(float *)(unit + 0x204) = forward[0];
  *(float *)(unit + 0x208) = *(float *)(unit + 0x28);
  *(float *)(unit + 0x20c) = *(float *)(unit + 0x2c);
  *(float *)(unit + 0x1ec) = forward[0];
  *(float *)(unit + 0x1f0) = *(float *)(unit + 0x28);
  *(float *)(unit + 0x1f4) = *(float *)(unit + 0x2c);
  *(float *)(unit + 0x1e0) = forward[0];
  *(float *)(unit + 0x1e4) = *(float *)(unit + 0x28);
  *(float *)(unit + 0x1e8) = *(float *)(unit + 0x2c);
  *(float *)(unit + 0x1d4) = forward[0];
  *(float *)(unit + 0x1d8) = *(float *)(unit + 0x28);
  *(float *)(unit + 0x1dc) = *(float *)(unit + 0x2c);

  /* Initialize control/animation state */
  *(int *)(unit + 0x1c0) = 0;
  *(int *)(unit + 0x334) = -1;
  *(int *)(unit + 0x1b4) = *(int *)(unit + 0x1b4) | 0x100;

  csmemset((void *)(unit + 0x338), 0, 0x7c);
  *(int *)(unit + 0x3a0) = -1;

  FUN_001a6bf0(unit_handle);

  csmemset((void *)(unit + 0x3e0), 0xff, 0x40);

  *(int16_t *)(unit + 0x3b4) = 0;
  *(int16_t *)(unit + 0x3b6) = 0;
  *(int *)(unit + 0x3b8) = 0;
  *(int16_t *)(unit + 0x3da) = 0;
  *(int *)(unit + 0x3bc) = -1;
  *(int *)(unit + 0x3cc) = -1;
  *(int16_t *)(unit + 0x2e4) = -1;
  *(int16_t *)(unit + 0x2e6) = -1;
  *(int *)(unit + 0x2f4) = 0x3f800000; /* 1.0f */
  *(uint8_t *)(unit + 0x23b) = 0;
  *(int *)(unit + 0x3c0) = -1;
  *(int *)(unit + 0x3dc) = -1;

  /* Assign initial grenade count from tag */
  {
    short grenade_type;
    grenade_type = *(short *)(unit_tag + 0x2c4);
    if (grenade_type >= 0 && grenade_type < 2 &&
        *(short *)(unit_tag + 0x2c6) >= 0) {
      *(uint8_t *)(unit + 0x2ce + (int)grenade_type) =
          *(uint8_t *)(unit_tag + 0x2c6);
    }
  }

  /* Set flags */
  *(int *)(unit + 0x4) = *(int *)(unit + 0x4) | 0x6000;

  /* Check powered melee probability */
  if (*(float *)(unit_tag + 0x22c) > *(float *)0x2533c0 &&
      *(float *)(unit_tag + 0x230) > *(float *)0x2533c0 &&
      *(float *)(unit_tag + 0x244) > *(float *)0x2533c0) {
    float random_val;

    random_val = random_math_real(
        (unsigned int *)get_global_random_seed_address());
    if (random_val < *(float *)(unit_tag + 0x244)) {
      *(int *)(unit + 0x1b4) = *(int *)(unit + 0x1b4) | 0x2000;
    } else {
      *(int *)(unit + 0x1b4) = *(int *)(unit + 0x1b4) & ~0x2000;
    }
  }

  /* Set initial health region permutation from tag */
  valid = (char)game_engine_running();
  if (valid == 0 &&
      (*(short *)(unit + 0x68) == 0 || *(short *)(unit + 0x68) == -1)) {
    *(int16_t *)(unit + 0x68) = *(int16_t *)(unit_tag + 0x180);
  }

  /* Apply initial animation state */
  unit_try_animation_state(unit_handle, *(int *)0x32e48c, 0, 1);

  /* Create initial weapons */
  unit_create_initial_weapons(unit_handle);

  /* Check for power-up equipment in seats */
  i = 0;
  seat_idx = 0;
  if (*(int *)(unit_tag + 0x2e4) > 0) {
    for (;;) {
      seat_entry = (char *)
          tag_block_get_element((int *)(unit_tag + 0x2e4), i, 0x11c);
      if (*(int *)(seat_entry + 0x104) != -1) {
        break;
      }
      seat_idx = seat_idx + 1;
      i = (int)seat_idx;
      if (i >= *(int *)(unit_tag + 0x2e4)) {
        return 1;
      }
    }
    ai_create_mounted_weapons_for_unit(unit_handle);
  }

  return 1;
}

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

/* FUN_001a9f20 (0x1a9f20) — unit_shield_sapping_update
 *
 * Called each tick for units in the shield-sapping state (unit+0x253 == 0x2a
 * = '*'). Checks whether the unit's current seat index (+0x80) exceeds the
 * seat's max-shield-sapping threshold (+0x2e in the animation seat entry).
 * If so, iterates all players via the player_data table (0x5aa6d4) and for
 * each player whose unit (+0x34) is not NONE, computes the squared distance
 * between the sapping unit's position (+0x50) and the player's unit position
 * (+0x50). If within range (squared distance < 16.0f at 0x254e74), applies
 * damage from the unit tag's shield-sapping damage effect at +0x294.
 *
 * If any damage was dealt, resets the cooldown counter at unit+0x1be to 0.
 * Otherwise, increments it.
 *
 * Confirmed: cdecl, 1 stack param (unit_handle).
 * Confirmed: player iteration via data_iterator_new/next (0x1197b0/0x119810).
 * Confirmed: damage_data_new (0x136750) + object_cause_damage (0x137d20).
 * Confirmed: attacker handle stored at damage_params+0x0c = [EBP-0x5c].
 * Confirmed: 0x254e74 = 16.0f (squared distance threshold).
 */
void FUN_001a9f20(int unit_handle)
{
  char *unit;
  char *unit_tag;
  char *antr_tag;
  char *seat_entry;
  char *player_entry;
  int player_unit_handle;
  char *player_unit;
  float dx;
  float dy;
  float dz;
  char damage_params[0x60];
  data_iter_t player_iter;
  char did_damage;
  int damage_effect_index;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (char *)tag_get(0x756e6974, *(int *)unit);

  if (*(char *)(unit + 0x253) != '*') {
    return;
  }

  antr_tag = (char *)tag_get(0x616e7472, *(int *)(unit + 0x7c));
  seat_entry = (char *)tag_block_get_element(
      antr_tag + 0x74, (int)*(int16_t *)(unit + 0x80), 0xb4);

  if (*(int16_t *)(unit + 0x80) < *(int16_t *)(seat_entry + 0x2e)) {
    return;
  }

  did_damage = 0;
  data_iterator_new(&player_iter, *(data_t **)0x5aa6d4);
  player_entry = (char *)data_iterator_next(&player_iter);

  while (player_entry != NULL) {
    player_unit_handle = *(int *)(player_entry + 0x34);
    if (player_unit_handle != -1) {
      player_unit =
          (char *)object_get_and_verify_type(player_unit_handle, 3);

      dx = *(float *)(unit + 0x50) - *(float *)(player_unit + 0x50);
      dy = *(float *)(unit + 0x54) - *(float *)(player_unit + 0x54);
      dz = *(float *)(unit + 0x58) - *(float *)(player_unit + 0x58);

      if (dx * dx + dy * dy + dz * dz < 16.0f) {
        damage_effect_index = *(int *)(unit_tag + 0x294);
        damage_data_new(damage_params, damage_effect_index);
        *(int *)(damage_params + 0x0c) = unit_handle;
        object_cause_damage(damage_params, player_unit_handle,
                            (short)-1, (short)-1, (short)-1, 0);
        did_damage = 1;
      }
    }
    player_entry = (char *)data_iterator_next(&player_iter);
  }

  if (did_damage) {
    *(uint8_t *)(unit + 0x1be) = 0;
  } else {
    *(uint8_t *)(unit + 0x1be) += 1;
  }
}

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

/* FUN_001a7d80 (0x1a7d80)
 * Sets or clears bit 23 (0x800000) in unit flags for all child units. */
void FUN_001a7d80(int datum_handle, char flag)
{
  int iter_state;
  int child;
  char *unit;
  uint32_t flags;

  child = FUN_000ce450(datum_handle, &iter_state);
  while (child != -1) {
    unit = (char *)object_try_and_get_and_verify_type(child, 3);
    if (unit != NULL) {
      if (flag == '\0') {
        flags = *(uint32_t *)(unit + 0x1b4) & 0xff7fffff;
      } else {
        flags = *(uint32_t *)(unit + 0x1b4) | 0x800000;
      }
      *(uint32_t *)(unit + 0x1b4) = flags;
    }
    child = FUN_000ce320(datum_handle, &iter_state);
  }
}

/* FUN_001a7df0 (0x1a7df0)
 * Returns true only if FUN_001ac180 returns true for ALL child units. */
char FUN_001a7df0(int datum_handle, int param_2, int param_3, int param_4)
{
  char result;
  char cVar2;
  int child;
  char *unit;
  int iter_state;

  result = 1;
  child = FUN_000ce450(datum_handle, &iter_state);
  while (child != -1) {
    unit = (char *)object_try_and_get_and_verify_type(child, 3);
    if (unit != NULL) {
      if (result && (cVar2 = FUN_001ac180(child, param_2, (void *)param_3, param_4), cVar2 != '\0')) {
        result = 1;
      } else {
        result = 0;
      }
    }
    child = FUN_000ce320(datum_handle, &iter_state);
  }
  return result;
}

/* FUN_001a7ea0 (0x1a7ea0)
 * Checks if the unit's current weapon has the given tag definition. */
char FUN_001a7ea0(int unit_handle, int weapon_def_tag)
{
  char *unit;
  int weapon;
  int *weapon_data;

  if (unit_handle != -1 && weapon_def_tag != -1) {
    unit = (char *)object_get_and_verify_type(unit_handle, 3);
    weapon = unit_get_weapon(unit_handle, (int)*(int16_t *)(unit + 0x2a2));
    if (weapon != -1) {
      weapon_data = (int *)object_get_and_verify_type(weapon, 4);
      return *weapon_data == weapon_def_tag;
    }
  }
  return 0;
}

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

/* FUN_001a9c90 (0x1a9c90) — unit_scripting_vehicle_test_seat_list
 *
 * Checks whether any unit occupying a named seat in the given vehicle
 * (unit_handle) is present in the object_list. Iterates seats from the
 * unit tag block at +0x2e4 (element size 0x11c), compares seat_name at
 * element+4 via crt_stricmp. For each matching seat, scans all unit objects
 * (type mask 3) to find one whose parent at +0xcc is this unit and whose
 * seat index at +0x2a0 matches. Then checks if that seated unit is in the
 * child list via FUN_000ce450/FUN_000ce320.
 *
 * Returns true (1) if any seated occupant was found in the object_list.
 *
 * Confirmed: cdecl, 3 stack params.
 * Confirmed: seat element size 0x11c, name at element+4.
 * Confirmed: object iterator at EBP-0x18 (16 bytes), datum handle at iter+0x08.
 * Confirmed: child iter state at EBP-0x8 (single int).
 */
char FUN_001a9c90(int unit_handle, const char *seat_name, int object_list)
{
  char *unit_data;
  char *unit_tag;
  int *seats_block;
  char *seat_element;
  int obj_iter[4];
  int child_iter_state;
  int child_handle;
  int seated_handle;
  char *seated_unit;
  char result;
  int16_t seat_index;
  int seat_count;

  result = 0;

  if (unit_handle == -1) {
    return 0;
  }

  unit_data = (char *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (char *)tag_get(0x756e6974, *(int *)unit_data);
  seats_block = (int *)(unit_tag + 0x2e4);
  seat_count = *seats_block;
  seat_index = 0;

  if (seat_count <= 0) {
    return 0;
  }

  while ((int)seat_index < seat_count) {
    seat_element =
        (char *)tag_block_get_element(seats_block, (int)seat_index, 0x11c);

    if (crt_stricmp(seat_name, seat_element + 4) == 0) {
      /* Seat name matches — find the occupant */
      object_iterator_new(obj_iter, 3, 0);
      seated_unit = (char *)object_iterator_next(obj_iter);

      while (seated_unit != NULL) {
        if (*(int *)(seated_unit + 0xcc) == unit_handle &&
            *(int16_t *)(seated_unit + 0x2a0) == seat_index) {
          /* Found the unit sitting in this seat — check object list */
          seated_handle = obj_iter[2];
          child_handle = FUN_000ce450(object_list, &child_iter_state);
          while (child_handle != -1) {
            if (seated_handle == child_handle) {
              goto found;
            }
            child_handle = FUN_000ce320(object_list, &child_iter_state);
          }
          /* child_handle == -1 here; check if seated_handle also -1 */
          if (seated_handle == child_handle) {
            goto found;
          }
          break;
        }
        seated_unit = (char *)object_iterator_next(obj_iter);
      }
    }

    seat_index++;
    seat_count = *seats_block;
    continue;
found:
    result = 1;
    seat_index++;
    seat_count = *seats_block;
  }

  return result;
}

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

/* FUN_001a7c70 (0x1a7c70)
 * Iterates child objects and calls FUN_001a7b50 on each. */
void FUN_001a7c70(int parent_handle, int param_2, int param_3)
{
  int iter_state;
  int child;

  child = FUN_000ce450(parent_handle, &iter_state);
  while (child != -1) {
    FUN_001a7b50(child, param_2, param_3);
    child = FUN_000ce320(parent_handle, &iter_state);
  }
}

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

/* FUN_001a7ad0 (0x1a7ad0)
 * Iterates child objects and applies damage to each alive object. */
void FUN_001a7ad0(int parent_handle, int param_2, int param_3)
{
  int iter_state;
  int child;
  char *obj;
  int local_c;
  int local_8;

  child = FUN_000ce450(parent_handle, &iter_state);
  while (child != -1) {
    local_8 = param_3;
    local_c = param_2;
    if (child != -1) {
      obj = (char *)object_get_and_verify_type(child, -1);
      if ((*(uint8_t *)(obj + 0xb6) & 4) == 0) {
        FUN_001365d0(child, (float *)&local_c, (float *)&local_8);
      }
    }
    child = FUN_000ce320(parent_handle, &iter_state);
  }
}

/* FUN_001a7b50 (0x1a7b50)
 * Computes and stores body/shield vitality ratios. Triggers events when
 * vitality transitions from nonzero to zero. */
void FUN_001a7b50(int datum_handle, float body_damage, float shield_damage)
{
  float shield_ratio;
  char *obj;
  float body_ratio;

  if (datum_handle == -1) {
    return;
  }
  obj = (char *)object_get_and_verify_type(datum_handle, -1);
  if ((*(uint8_t *)(obj + 0xb6) & 4) != 0) {
    return;
  }
  if (*(float *)(obj + 0x8c) <= 0.0f) {
    body_ratio = 0.0f;
  } else if (shield_damage < *(float *)(obj + 0x8c)) {
    body_ratio = shield_damage / *(float *)(obj + 0x8c);
  } else {
    body_ratio = 1.0f;
  }
  if (*(float *)(obj + 0x88) <= 0.0f) {
    shield_ratio = 0.0f;
  } else if (body_damage < *(float *)(obj + 0x88)) {
    shield_ratio = body_damage / *(float *)(obj + 0x88);
  } else {
    shield_ratio = 1.0f;
  }
  if (0.0f < *(float *)(obj + 0x94) && body_ratio <= 0.0f) {
    FUN_00136b40(datum_handle);
  }
  *(float *)(obj + 0x94) = body_ratio;
  if (0.0f < *(float *)(obj + 0x90) && shield_ratio <= 0.0f) {
    object_deplete_body(datum_handle);
  }
  *(float *)(obj + 0x90) = shield_ratio;
}

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


/* FUN_001a6bf0 (0x1a6bf0)
 * Selects dialogue variant for the unit if none is set. */
void FUN_001a6bf0(int unit_handle)
{
  uint32_t *unit;
  char *unit_tag;
  int *dialogue_block;
  int16_t *variant;
  uint16_t count;
  int16_t i;
  int16_t variants[16];

  unit = (uint32_t *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (char *)tag_get(0x756e6974, *unit);
  if (*(int16_t *)((char *)unit + 0x6e) == 0) {
    dialogue_block = (int *)(unit_tag + 0x2b4);
    count = 0;
    i = 0;
    if (0 < *dialogue_block) {
      do {
        variant = (int16_t *)tag_block_get_element(dialogue_block, (int)i, 0x18);
        if (*variant < 100) {
          if (count >= 0xf) {
            error(2, "unit_dialogue_determine_variant overflowed variant array");
            break;
          }
          variants[(int16_t)count] = *variant;
          count++;
        }
        i++;
      } while ((int)i < *dialogue_block);
      if ((int16_t)count > 0) {
        *(int16_t *)((char *)unit + 0x6e) =
            variants[*(int *)0x4e4cf4 % (int)(int16_t)count];
        *(int *)0x4e4cf4 = *(int *)0x4e4cf4 + 1;
      }
    }
  }
}

/* FUN_001a70d0 (0x1a70d0)
 * Initiates direct sound speech on a unit (used for scripted dialogue). */
void FUN_001a70d0(int unit_handle, int sound_tag, int sound_handle)
{
  char *unit;
  int result;
  char speech_buf[0x30];
  int local_8;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  local_8 = -1;
  result = FUN_001a68d0(unit_handle, 6, 0, 0, 0, (int16_t *)&local_8, &result);
  if ((int16_t)result < 3) {
    result = 2;
  }
  csmemset(speech_buf, 0, 0x30);
  *(int16_t *)(speech_buf + 0x00) = 6;
  *(int16_t *)(speech_buf + 0x02) = -1;
  *(int *)(speech_buf + 0x04) = sound_tag;
  *(int16_t *)(speech_buf + 0x0c) = 0x18;
  ai_communication_packet_new(speech_buf + 0x10);
  FUN_001a6ef0(unit_handle, (int16_t)result, speech_buf);
  if (*(int *)(unit + 0x33c) != sound_tag) {
    display_assert(
        "unit->unit.speech.current.sound_definition_index == sound_definition_index",
        "c:\\halo\\SOURCE\\units\\unit_dialogue.c", 0x196, 1);
    system_exit(-1);
  }
  *(int *)(unit + 0x3b0) = sound_handle;
  *(uint8_t *)(unit + 0x3a4) = 1;
  *(int16_t *)(unit + 0x3a8) = 0;
  FUN_00044fd0(unit_handle, 6, 0xffff, unit + 0x348);
}

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


/* unit_drop_grenades_on_death (0x1abb20)
 * Creates grenade weapon objects for each grenade the unit carries and drops
 * them. Iterates over 2 grenade types. For each, looks up the grenade tag
 * from game globals, creates weapon objects, disconnects from map, then
 * detaches (drops physically). Register arg: unit_handle in EAX. */
void unit_drop_grenades_on_death(int unit_handle)
{
  char *unit;
  char *grenade_count_ptr;
  int grenade_type;
  int globals;
  int grenade_tag;
  int new_handle;
  char placement[136];

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  grenade_count_ptr = unit + 0x2ce;

  /* The binary uses a negative-offset trick to compute the grenade type index:
   * ESI = 0xFFFFFD32 - unit_addr; index = ESI + grenade_count_ptr
   * Since 0xFFFFFD32 + 0x2CE = 0 (mod 2^32), this yields index = type (0 or 1).
   * We compute the type directly. */
  for (grenade_type = 0; grenade_type < NUMBER_OF_UNIT_GRENADE_TYPES; grenade_type++) {
    globals = (int)game_globals_get();
    grenade_tag = (int)tag_block_get_element(
        (void *)(globals + 0x128), grenade_type, 0x44);

    while (*grenade_count_ptr > 0) {
      object_placement_data_new(placement, *(int *)(grenade_tag + 0x30), unit_handle);
      new_handle = object_new(placement);
      if (new_handle != -1) {
        object_disconnect_from_map(new_handle);
        unit_detach_weapon(unit_handle, new_handle);
      }
      *grenade_count_ptr = *grenade_count_ptr - 1;
    }
    grenade_count_ptr++;
  }
}

/* unit_drop_weapons_on_death (0x1abbd0)
 * Iterates over all 4 weapon slots and drops weapons not connected to the
 * map. For map-connected weapons, asserts with an error message. Updates
 * the next-weapon index if needed, clears the slot, and deletes the weapon
 * if it cannot be fired. Register arg: unit_handle in EAX. */
void unit_drop_weapons_on_death(int unit_handle)
{
  char *unit;
  int weapon_handle;
  char *weapon_data;
  int slot;
  int *weapon_slot_ptr;
  const char *unit_name;
  const char *weapon_name;
  const char *msg;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  slot = 0;
  weapon_slot_ptr = (int *)(unit + 0x2a8);

  do {
    weapon_handle = *weapon_slot_ptr;
    if (weapon_handle != -1 &&
        (int16_t)slot != *(int16_t *)(unit + 0x2a2)) {
      weapon_data = (char *)object_get_and_verify_type(weapon_handle, 4);
      if ((*(uint32_t *)(weapon_data + 4) & 0x800) != 0) {
        weapon_name = tag_get_name(*(int *)weapon_data);
        unit_name = tag_get_name(*(int *)unit);
        msg = csprintf(error_string_buffer,
            "a %s tried to drop a %s which was connected to the map.",
            unit_name, weapon_name);
        display_assert(msg, "c:\\halo\\SOURCE\\units\\units.c", 0x2132, 1);
        system_exit(-1);
      }
      unit_detach_weapon(unit_handle, weapon_handle);
      if ((int16_t)slot == *(int16_t *)(unit + 0x2a4)) {
        *(int16_t *)(unit + 0x2a4) = *(int16_t *)(unit + 0x2a2);
      }
      *weapon_slot_ptr = -1;
      if (!weapon_can_be_fired(weapon_handle)) {
        object_delete(weapon_handle);
      }
    }
    slot++;
    weapon_slot_ptr++;
  } while ((int16_t)slot < 4);
}

/* unit_get_weapon_name (0x1ae700)
 * Returns the name string of the unit's currently selected weapon.
 * If no weapon is equipped, returns "unarmed".
 * Register arg: unit_handle in ESI.
 * Stack arg: 1 cdecl param (unused in function body, always 1 from callers). */
char *unit_get_weapon_name(int unit_handle, int unused)
{
  char *unit;
  int weapon_handle;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  weapon_handle = unit_get_weapon(unit_handle,
      *(int16_t *)(unit + 0x2a2));
  if (weapon_handle == -1) {
    return "unarmed";
  }
  return weapon_get_label(weapon_handle);
}

/* unit_has_night_vision_weapon (0x1b13a0)
 * Checks whether the unit's current weapon has the night-vision flag
 * (bit 0x4000 at weapon tag offset 0x308). Returns true if zoom_level
 * is not 0xFF, a weapon exists, and the flag is set.
 * Register arg: unit_handle in ESI. */
char unit_has_night_vision_weapon(int unit_handle)
{
  char *unit;
  int weapon_handle;
  char *weapon_data;
  int tag_data;
  char result;

  result = 0;
  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  if (*(uint8_t *)(unit + 0x2d0) == 0xff) {
    return result;
  }
  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  weapon_handle = unit_get_weapon(unit_handle,
      *(int16_t *)(unit + 0x2a2));
  if (weapon_handle == -1) {
    return result;
  }
  weapon_data = (char *)object_get_and_verify_type(weapon_handle, 4);
  tag_data = (int)tag_get(0x77656170, *(int *)weapon_data);
  if (*(uint32_t *)(tag_data + 0x308) & 0x4000) {
    return 1;
  }
  return result;
}

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

/* scripting_magic_melee_attack (0x1b2260)
 * Triggers a melee attack on the first player's unit. Gets player 0's
 * unit handle from player_data, then calls unit_melee_attack_begin. */
void scripting_magic_melee_attack(void)
{
  char *player;
  int unit_handle;

  player = (char *)datum_get(player_data, 0);
  unit_handle = *(int *)(player + 0x34);
  unit_melee_attack_begin(unit_handle, 0, 0);
}

/* unit_select_weapon_after_vehicle_exit (0x1b2740)
 * After exiting a vehicle, selects the next available weapon and updates
 * weapon readiness. Reads current weapon index, finds the next weapon,
 * stores it as the next weapon index, then calls unit_update_weapon_readiness.
 * Register arg: unit_handle in EAX. */
void unit_select_weapon_after_vehicle_exit(int unit_handle)
{
  char *unit;
  uint16_t current_idx;
  int16_t next_idx;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  current_idx = *(uint16_t *)(unit + 0x2a2);
  next_idx = unit_next_weapon_index(unit_handle, (int16_t)current_idx, 0);
  *(int16_t *)(unit + 0x2a4) = next_idx;
  unit_update_weapon_readiness(unit_handle, 1);
}

/* FUN_001abd10 (0x1abd10)
 * Plays impact sounds for melee damage. Looks up the unit's material type
 * sound via FUN_0018e500 and plays it on the unit. If a damage effect tag is
 * provided, also plays the effect's melee impact sound (tag 'jpt!'+0x120).
 * Register args: @eax = material_type, @esi = unit_handle,
 *                @edi = damage_effect_tag (or -1).
 * Confirmed from callers 0x1ae840 @001aea76, 0x1aea90 @001af016. */
void FUN_001abd10(int16_t material_type, int unit_handle, int weapon_tag_index)
{
  char *material_effects;
  int sound_tag;
  char *weapon_tag;
  float *position;
  float *forward;

  position = *(float **)0x31fc1c;
  forward = *(float **)0x31fc3c;

  material_effects = (char *)FUN_0018e500(material_type);
  sound_tag = *(int *)(material_effects + 0x370);
  if (sound_tag != -1) {
    object_impulse_sound_new(unit_handle, sound_tag, -1, position, forward,
                             1.0f);
  }

  if (weapon_tag_index != -1) {
    weapon_tag = (char *)tag_get(0x6a707421, weapon_tag_index);
    sound_tag = *(int *)(weapon_tag + 0x120);
    if (sound_tag != -1) {
      object_impulse_sound_new(unit_handle, sound_tag, -1, position, forward,
                               1.0f);
    }
  }
}

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


/* FUN_001a6280 (0x1a6280)
 * Biped death state handler. After a biped is killed, decides which
 * post-death sub-state to enter: limp-noodle (ragdoll-like), dying-airborne
 * (fell while dying), or normal dying. Checks limp-noodle counter, airborne
 * ticks, and animation state.
 * Register args: @edi = unit_handle, @ebx = pointer to state byte pair.
 * Confirmed from caller 0x1a6350 @001a65ed. */
void FUN_001a6280(int unit_handle, char *state_out)
{
  char *biped;
  char *biped_tag;

  biped = (char *)object_get_and_verify_type(unit_handle, 1);
  biped_tag = (char *)tag_get(0x62697064, *(int *)biped);

  /* Check limp-noodle state */
  if ((*(uint8_t *)(biped + 0x424) & 0x20) != 0 &&
      *(uint8_t *)(biped + 0x47c) < *(uint8_t *)(biped + 0x47d)) {
    if (*(char *)0x4e4cf3 == 0) {
      FUN_001a0680(unit_handle);
    }
    FUN_001a2800(unit_handle, "post-limp-noodle");
    state_out[1] = 0;
    return;
  }

  /* Check dying-airborne state */
  if (*(int8_t *)(biped + 0x459) > 2 &&
      (*(uint32_t *)(biped_tag + 0x2f4) & 0x400) == 0) {
    if (*(uint8_t *)(biped + 0x253) == 0x18) {
      FUN_001a2160(unit_handle);
    }
    *state_out = 0x18;
    FUN_001a2800(unit_handle, "post-dying-airborne");
    state_out[1] = 0;
    return;
  }

  /* Normal dying state */
  if (*(uint8_t *)(biped + 0x253) == 0x18) {
    *(int *)(biped + 0x468) = 0;
    FUN_001a4440(unit_handle);
  }
  *state_out = 0x19;
  FUN_001a2800(unit_handle, "post-dying");
  state_out[1] = 0;
}

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



/* unit_adjust_projectile_ray (0x1acf90) — adjust projectile ray origin
 * and direction based on unit state.
 *
 * If use_unit_forward is true, copies the unit's forward vector (+0x1ec)
 * into direction. If adjust_origin is true, projects the origin onto the
 * unit's aim position along the direction vector. Finally computes
 * velocity_out as the dot product of the root location's direction with
 * the forward direction.
 *
 * Source: units.c
 */
void unit_adjust_projectile_ray(int unit_handle, float *origin,
                                float *direction, float *velocity_out,
                                char adjust_origin, char use_unit_forward)
{
  char *unit;
  float aim_pos[3];
  float dot;
  float root_dir[3];

  unit = (char *)object_get_and_verify_type(unit_handle, 3);

  /* Copy unit forward vector as direction if requested */
  if (use_unit_forward != '\0') {
    direction[0] = *(float *)(unit + 0x1ec);
    direction[1] = *(float *)(unit + 0x1f0);
    direction[2] = *(float *)(unit + 0x1f4);
  }

  /* Project origin onto aim position along direction */
  if (adjust_origin != '\0') {
    unit_set_seat_state(unit_handle, aim_pos);
    dot = (origin[0] - aim_pos[0]) * direction[0] +
          (origin[1] - aim_pos[1]) * direction[1] +
          (origin[2] - aim_pos[2]) * direction[2];
    origin[0] = dot * direction[0] + aim_pos[0];
    origin[1] = dot * direction[1] + aim_pos[1];
    origin[2] = dot * direction[2] + aim_pos[2];
  }

  /* Compute velocity as dot(root_direction, direction) */
  object_get_root_location(unit_handle, root_dir, 0);
  *velocity_out = root_dir[0] * direction[0] +
                  root_dir[2] * direction[2] +
                  root_dir[1] * direction[1];
}

/* unit_render_debug (0x1ad060) — debug rendering for unit state.
 *
 * Draws debug visualization for unit aim vectors, seat positions, and
 * animation throttle when the corresponding debug flags (0x5054f5-f7)
 * are enabled. Conditional on global debug toggles.
 *
 * Source: units.c
 */
void unit_render_debug(int unit_handle)
{
  char *unit;
  int unit_tag;
  float eye_pos[3];
  float head_pos[3];
  char marker_data[0x6c];       /* marker output; position at +0x60 */
  int seat_idx;
  float seat_a[3], seat_b[3], seat_c[3];
  int seat_count;
  int local_player;
  char result;
  char *text;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (int)tag_get(0x756e6974, *(int *)unit);

  /* Debug aim/look vectors */
  if (*(char *)0x5054f7 != '\0') {
    unit_set_seat_state(unit_handle, eye_pos);
    object_get_world_position(unit_handle, (vector3_t *)head_pos);
    head_pos[2] = head_pos[2] + 0.1f;
    /* Draw aim direction line (scale 1.0, yellow) */
    FUN_00189320(1, eye_pos, (void *)(unit + 0x1ec), 1.0f, *(void **)0x2ee6c4);
    /* Draw aim direction line (scale 0.5, green) */
    FUN_00189320(1, eye_pos, (void *)(unit + 0x1e0), 0.5f, *(void **)0x2ee6d0);
    /* Draw head position (scale 1.0, yellow) */
    FUN_00189320(1, head_pos, (void *)(unit + 0x24), 1.0f, *(void **)0x2ee6c4);
    /* Draw body direction (scale 0.5, green) */
    FUN_00189320(1, head_pos, (void *)(unit + 0x1d4), 0.5f, *(void **)0x2ee6d0);
  }

  /* Debug seat positions */
  if (*(char *)0x5054f6 != '\0') {
    {
      int player_idx;
      player_idx = local_player_get_player_index(*(int16_t *)0x506548);
      local_player = (int)datum_get(*(data_t **)0x5aa6d4, player_idx);
    }
    seat_count = *(int *)(local_player + 0x34);
    if (seat_count != NONE) {
      seat_idx = 0;
      if (seat_idx < *(int *)(unit_tag + 0x2e4)) {
        do {
          result = (char)unit_get_seat_enter_position(
            seat_count, unit_handle, (int16_t)seat_idx,
            seat_a, seat_b, seat_c);
          if (result != '\0') {
            FUN_00189150(1, seat_a, 0.25f, *(void **)0x2ee6d0);
            FUN_00189150(1, seat_b, 0.25f, *(void **)0x2ee6d8);
            FUN_00189150(1, seat_c, 0.25f, *(void **)0x2ee6e0);
          }
          seat_idx += 1;
        } while ((int)(short)seat_idx < *(int *)(unit_tag + 0x2e4));
      }
    }
  }

  /* Debug animation throttle */
  if (*(char *)0x5054f5 != '\0') {
    object_get_markers_by_string_id(unit_handle, (void *)0x2909e4,
                                    marker_data, 1);
    /* Position is at offset 0x60 within the marker output struct.
     * marker_data base is EBP-0x98; position at EBP-0x38 = base+0x60. */
    head_pos[0] = *(float *)((char *)marker_data + 0x60);
    head_pos[1] = *(float *)((char *)marker_data + 0x64);
    head_pos[2] = *(float *)((char *)marker_data + 0x68);
    text = csprintf((char *)0x5ab100, "%.2f",
                     (double)*(float *)(unit + 0x298));
    FUN_00189cb0(0, head_pos, text, *(int *)0x2ee6f0);
  }
}

/* vehicle_scripting_find_available_seats (0x1adfc0) — find available seats
 * in a unit matching a substring filter and seat desire type.
 *
 * Iterates unit seats from the unit tag (0x756e6974), checks the seat name
 * against the substring filter, applies the seat desire type filter, and
 * stores matching seat indices in seat_indices up to max_seats.
 *
 * seat_desire_type values:
 *   -1 = NONE (no filter, accept all)
 *   0 = NOT driver (bit 2 clear)
 *   1 = gunner (bit 3 set)
 *   2 = neither driver nor gunner
 *   3 = driver (bit 2 set)
 *   default = accept
 *
 * Source: units.c line 0x178f-0x1790 asserts.
 */
int16_t vehicle_scripting_find_available_seats(int unit_handle,
                                               int seat_substring_addr,
                                               int16_t seat_desire_type,
                                               int16_t *seat_indices,
                                               int16_t max_seats)
{
  const char *seat_substring;
  char *unit;
  int unit_tag;
  char match_all;
  short found_count;
  int loop_idx;
  uint32_t *seat_entry;
  char seat_name_buf[256];
  uint8_t bit_val;
  char seat_filled;

  seat_substring = (const char *)seat_substring_addr;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (int)tag_get(0x756e6974, *(int *)unit);

  if (seat_substring == NULL) {
    display_assert("seat_substring_name",
                   "c:\\halo\\SOURCE\\units\\units.c", 0x178f, 1);
    system_exit(-1);
  }
  if (seat_desire_type != -1 &&
      (seat_desire_type < 0 || seat_desire_type >= 5)) {
    display_assert("(seat_desire_type == NONE) || "
                   "((seat_desire_type >= 0) && "
                   "(seat_desire_type < NUMBER_OF_VEHICLE_SEAT_DESIRE_TYPES))",
                   "c:\\halo\\SOURCE\\units\\units.c", 0x1790, 1);
    system_exit(-1);
  }

  /* Determine if we should match all seats or filter by substring */
  if (seat_substring != NULL && csstrlen(seat_substring) != 0) {
    match_all = 0;
  } else {
    match_all = 1;
  }

  found_count = 0;
  loop_idx = 0;
  while ((short)loop_idx < *(int *)(unit_tag + 0x2e4)) {
    seat_entry = (uint32_t *)tag_block_get_element(
      (void *)(unit_tag + 0x2e4), loop_idx, 0x11c);

    if (found_count >= max_seats) {
      return found_count;
    }

    /* Copy and lowercase the seat name for comparison */
    csstrcpy(seat_name_buf, (const char *)(seat_entry + 1));
    csstr_tolower(seat_name_buf);

    /* Check substring match */
    if (!match_all && crt_strstr(seat_name_buf, seat_substring) == NULL) {
      goto next_seat;
    }

    /* Check seat desire type filter */
    switch ((int)seat_desire_type) {
    case 0:
      bit_val = ~(uint8_t)(*seat_entry >> 2);
      break;
    case 1:
      bit_val = (uint8_t)(*seat_entry >> 3);
      break;
    case 2:
      if ((*seat_entry & 4) != 0 || (*seat_entry & 8) != 0)
        goto next_seat;
      goto accept_seat;
    case 3:
      bit_val = (uint8_t)(*seat_entry >> 2);
      break;
    default:
      goto accept_seat;
    }
    if ((bit_val & 1) == 0)
      goto next_seat;

  accept_seat:
    seat_filled = unit_seat_filled(unit_handle, (int16_t)loop_idx);
    if (seat_filled == '\0') {
      seat_indices[found_count] = (int16_t)loop_idx;
      found_count = found_count + 1;
    }

  next_seat:
    loop_idx += 1;
  }
  return found_count;
}

/* unit_leap_begin (0x1b1c70) — start a leap animation.
 *
 * Checks the unit's animation state via a switch; if the state is not one
 * of the dying/dead/special states, and either the unit has a vehicle
 * or melee is not active, requests animation state 0x27 (leap). If the
 * forward vector is non-NULL, applies it as the unit's alignment vector.
 *
 * Returns 1 on success, 0 if the state blocks leaping.
 *
 * Source: units.c
 */
char unit_leap_begin(int unit_handle, float *forward)
{
  char *unit;
  char result;
  char anim_ok;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  result = 0;

  switch (*(uint8_t *)(unit + 0x253)) {
  case 0x17: case 0x18: case 0x19: case 0x1a: case 0x1b:
  case 0x1d: case 0x1e: case 0x1f: case 0x20: case 0x21:
  case 0x22: case 0x23: case 0x27: case 0x29:
    /* These states block leaping */
    break;
  default:
    if (*(short *)(unit + 0x64) != 0 ||
        (*(uint8_t *)(unit + 0x424) & 1) == 0) {
      anim_ok = FUN_001ad260(unit_handle, 0x27);
      if (anim_ok != '\0') {
        if (forward != 0) {
          unit_apply_alignment_vector(unit_handle, forward);
        }
        result = 1;
      }
    }
    break;
  }
  return result;
}

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


/* unit_melee_attack_begin (0x1b1b60) — begin a melee attack animation.
 *
 * Checks the unit's animation state via a switch table; if the state is one
 * of the dying/dead/special states (0x17-0x23,0x27,0x29), the attack is
 * blocked. Otherwise, determines the target animation state based on
 * param_2 (forced hit), melee readiness, and unit flags. Requests the
 * animation via FUN_001ad260. On success (or forced), sets melee flags
 * and optionally applies alignment vector.
 *
 * param_2: if non-zero, force melee hit (animation state 0x20, type=4).
 * param_3: if non-zero, pointer to float[3] alignment vector.
 *
 * Returns 1 on success, 0 if blocked.
 */
char unit_melee_attack_begin(int unit_handle, char param_2, int param_3)
{
  char *unit;
  int unit_tag;
  char anim_state;
  char result;
  uint8_t melee_ready;
  char anim_ok;
  int16_t new_state;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (int)tag_get(0x756e6974, *(int *)unit);
  result = 0;

  switch (*(uint8_t *)(unit + 0x253)) {
  case 0x17: case 0x18: case 0x19: case 0x1a: case 0x1b:
  case 0x1d: case 0x1e: case 0x1f: case 0x20: case 0x21:
  case 0x22: case 0x23: case 0x27: case 0x29:
    /* These animation states block melee attacks */
    break;
  default:
    /* Check if melee is ready: either unit is in a vehicle (seat != 0)
     * or the melee-ready bit (unit+0x424, bit 0) is set */
    melee_ready = 0;
    if (*(short *)(unit + 0x64) == 0) {
      melee_ready = *(uint8_t *)(unit + 0x424) & 1;
    }

    if (param_2 != '\0') {
      new_state = 0x20;  /* forced melee hit */
    } else {
      anim_state = *(char *)(unit + 0x253);
      if (anim_state == 0x28) {
        new_state = 0x29;  /* melee continuation */
      } else {
        new_state = (int16_t)((melee_ready != 0) + 0x1e);
      }
    }

    anim_ok = FUN_001ad260(unit_handle, new_state);

    if (anim_ok != '\0' || param_2 != '\0') {
      /* Check unit tag flag bit 8 at offset 0x17c */
      if ((*(uint32_t *)(unit_tag + 0x17c) & 0x100) != 0) {
        *(uint8_t *)(unit + 0x253) = 0x19;
      }
      /* Apply alignment vector if provided */
      if (param_3 != 0) {
        unit_apply_alignment_vector(unit_handle, (float *)param_3);
      }
      if (param_2 != '\0') {
        *(uint8_t *)(unit + 0x239) = 4;
        *(uint8_t *)(unit + 0x23a) = 0;
        return 1;
      }
      *(uint8_t *)(unit + 0x239) = 1;
      result = 1;
    }
    break;
  }
  return result;
}

/* unit_place (0x1b24d0) — place a unit with placement data.
 *
 * Applies placement body vitality if > 0.0f, and if the "dead" flag
 * (placement+4, bit 0) is set, kills the unit: sets animation state,
 * clears weapons, clears grenade state, deletes weapon object,
 * marks as dead, and sets up the death animation frame.
 *
 * Source: units.c
 */
void unit_place(int unit_handle, void *placement)
{
  char *unit;
  int unit_tag;
  int antr_tag;
  int anim_element;
  int death_frame;
  int flags;
  int obj_flags;
  float *place;

  place = (float *)placement;
  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (int)tag_get(0x756e6974, *(int *)unit);

  /* Apply body vitality from placement if positive */
  if (place[0] > 0.0f) {
    *(float *)(unit + 0x90) = place[0];
  }

  /* Check the "dead" flag: bit 0 of the second dword (placement+4) */
  if ((*(int *)((char *)placement + 4) & 1) != 0) {
    /* Kill: set animation state and make dead */
    FUN_001b1400(unit_handle, 1, 0, 0, 0, 0, 0, -1, 0);

    if (*(char *)(unit + 0x253) == 0x19) {
      /* Clear weapons and grenade state */
      unit_clear_weapons(unit_handle);
      csmemset((void *)(unit + 0x2ce), 0, 2);

      /* Delete weapon object if one exists */
      if (*(int *)(unit + 0x2c8) != NONE) {
        object_delete(*(int *)(unit + 0x2c8));
        *(int *)(unit + 0x2c8) = NONE;
      }

      /* Look up the death animation frame count */
      antr_tag = (int)tag_get(0x616e7472, *(int *)(unit_tag + 0x44));
      anim_element = (int)tag_block_get_element(
        (void *)(antr_tag + 0x74),
        (int)*(short *)(unit + 0x80),
        0xb4);
      death_frame = (int)*(short *)(anim_element + 0x22) - 4;

      /* Mark as dead: set object flag bits */
      *(uint8_t *)(unit + 0xb6) = *(uint8_t *)(unit + 0xb6) | 4;
      obj_flags = *(int *)(unit + 0x4);
      *(int *)(unit + 0x4) = obj_flags | 0x20000;

      /* Clamp death frame to >= 0 (branchless: mask with sign) */
      *(uint16_t *)(unit + 0x82) = (uint16_t)(death_frame & ((death_frame < 0) - 1));

      /* Set additional unit flags */
      flags = *(int *)(unit + 0x1b4);
      *(int *)(unit + 0x1b4) = flags | 0x200;

      /* Record game time and clear body vitality */
      *(int *)(unit + 0x3cc) = game_time_get();
      *(float *)(unit + 0x90) = 0.0f;
      *(float *)(unit + 0x94) = 0.0f;

      /* Update position and children */
      FUN_00136b40(unit_handle);
      object_update_children_recursive(unit_handle);
    }
  }
}

/* unit_create_initial_weapons (0x1b2660) — create initial weapons for a unit.
 *
 * Iterates the unit tag's initial weapons tag block (at tag+0x2d8, element
 * size 0x24), and for each weapon tag index that is not NONE, creates an
 * object via object_placement_data_new + object_new. Then tries to pick
 * it up: if the game engine is running and the unit already has that weapon
 * definition, delete the duplicate; otherwise attempt unit_enter_seat and
 * delete on failure.
 *
 * Source: units.c
 */
void unit_create_initial_weapons(int unit_handle)
{
  char *unit;
  int unit_tag;
  int *initial_weapons_block;
  int loop_counter;
  int element;
  int weapon_tag_index;
  int weapon_handle;
  char *weapon_data;
  char engine_running;
  char has_weapon;
  char enter_ok;
  uint8_t placement[136]; /* 0x88 bytes for object_placement_data */

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (int)tag_get(0x756e6974, *(int *)unit);
  initial_weapons_block = (int *)(unit_tag + 0x2d8);
  loop_counter = 0;

  if (*initial_weapons_block > 0) {
    element = 0;
    do {
      element = (int)tag_block_get_element(initial_weapons_block, element, 0x24);
      weapon_tag_index = *(int *)(element + 0xc);
      if (weapon_tag_index != NONE) {
        object_placement_data_new(placement, weapon_tag_index, unit_handle);
        weapon_handle = object_new(placement);
        if (weapon_handle != NONE) {
          weapon_data = (char *)object_get_and_verify_type(weapon_handle, 4);
          engine_running = game_engine_running();
          if (engine_running != '\0') {
            has_weapon = unit_has_weapon_definition_index(unit_handle, *(int *)weapon_data);
            if (has_weapon != '\0') {
              goto delete_weapon;
            }
          }
          enter_ok = unit_enter_seat(unit_handle, weapon_handle, 0);
          if (enter_ok != '\0') {
            goto next_weapon;
          }
delete_weapon:
          object_delete(weapon_handle);
        }
      }
next_weapon:
      loop_counter = loop_counter + 1;
      element = (int)(short)loop_counter;
    } while (element < *initial_weapons_block);
  }
}

/* unit_scripting_enter_vehicle (0x1b32d0) — scripted vehicle entry.
 *
 * Makes a unit enter a specific seat of a vehicle by seat name.
 * Validates both handles, checks the seat name length, verifies the
 * unit is not dying/dead, handles existing vehicle occupancy by
 * calling unit_exit_seat_end, then iterates the vehicle's seats
 * tag block looking for a matching seat name. Checks seat availability
 * and type compatibility before calling unit_board_vehicle.
 *
 * Source: units.c
 */
void unit_scripting_enter_vehicle(int unit_handle, int vehicle_handle,
                                  char *seat_name)
{
  char *unit_data;
  char *vehicle_unit;
  int vehicle_tag;
  int *seats_block;
  int seat_idx;
  int seat_element;
  int stricmp_result;
  char seat_filled;

  if (unit_handle == NONE) {
    return;
  }
  if (vehicle_handle == NONE) {
    return;
  }
  /* Validate seat name is a non-empty string */
  if (csstrlen(seat_name) == 0) {
    return;
  }

  unit_data = (char *)object_get_and_verify_type(unit_handle, 3);
  /* Check if unit is dying/dead (bit 2 of byte at +0xb6) */
  if ((*(uint8_t *)(unit_data + 0xb6) & 4) != 0) {
    return;
  }

  /* If unit is already in a vehicle, try to exit first */
  if (*(int *)(unit_data + 0xcc) != NONE) {
    if (*(short *)(unit_data + 0x2a0) != -1) {
      unit_exit_seat_end(unit_handle);
    }
    /* If still in a vehicle after attempting exit, abort */
    if (*(int *)(unit_data + 0xcc) != NONE) {
      return;
    }
  }

  /* Get the vehicle's unit tag and iterate seats */
  vehicle_unit = (char *)object_get_and_verify_type(vehicle_handle, 3);
  vehicle_tag = (int)tag_get(0x756e6974, *(int *)vehicle_unit);
  seats_block = (int *)(vehicle_tag + 0x2e4);
  seat_idx = 0;

  if (*seats_block > 0) {
    seat_element = 0;
    while (1) {
      seat_element = (int)tag_block_get_element(seats_block, seat_element, 0x11c);
      stricmp_result = csstricmp(seat_name, (char *)(seat_element + 4));

      if (stricmp_result == 0) {
        /* Seat name matches - check availability */
        seat_filled = unit_seat_filled(vehicle_handle, (int16_t)seat_idx);
        if (seat_filled == '\0') {
          /* Seat is available - check type compatibility */
          if (*(short *)(unit_data + 0x64) == 1 ||
              FUN_001acd70(unit_handle, (const char *)(seat_element + 4), 0, 0) != '\0') {
            /* Compatible - board the vehicle */
            unit_board_vehicle(unit_handle, vehicle_handle, (int16_t)seat_idx);
            return;
          }
        }
      }

      seat_idx = seat_idx + 1;
      seat_element = (int)(short)seat_idx;
      if (seat_element >= *seats_block) {
        return;
      }
    }
  }
}

/* vehicle_scripting_load_magic (0x1b3400) — load units into vehicle seats.
 *
 * Iterates child objects of the given group_handle. For each child that is
 * a biped/vehicle type and not dying/dead, tries to seat it in the vehicle.
 * Finds available seats via vehicle_scripting_find_available_seats, checks
 * seat type compatibility, handles existing vehicle occupancy, and calls
 * unit_board_vehicle. Returns the count of successfully seated units.
 *
 * Source: units.c
 */
uint16_t vehicle_scripting_load_magic(int vehicle_handle, int seat_substring,
                                      int group_handle)
{
  char *vehicle_unit;
  int vehicle_tag;
  int child_handle;
  char *child_data;
  int16_t seat_count;
  short seat_indices[16];
  int iter_state[1];
  int inner_idx;
  int16_t seat_idx;
  int seat_element;
  char seat_type_ok;
  char board_ok;
  uint16_t loaded_count;

  loaded_count = 0;
  if (vehicle_handle == NONE) {
    return 0;
  }

  vehicle_unit = (char *)object_get_and_verify_type(vehicle_handle, 3);
  vehicle_tag = (int)tag_get(0x756e6974, *(int *)vehicle_unit);

  /* Find available seats matching the seat substring */
  seat_count = vehicle_scripting_find_available_seats(
    vehicle_handle, seat_substring, -1, seat_indices, 0x10);

  /* Get first child of group */
  child_handle = FUN_000ce450(group_handle, iter_state);
  if (child_handle == NONE) {
    return 0;
  }

  do {
    child_data = (char *)object_get_and_verify_type(child_handle, -1);

    /* Check if child is a biped or vehicle type (bit 0 or 1 of object_type) */
    if (((1 << (*(uint8_t *)(child_data + 0x64) & 0x1f)) & 3) != 0 &&
        (*(uint8_t *)(vehicle_unit + 0xb6) & 4) == 0) {
      inner_idx = 0;
      if ((short)seat_count > 0) {
        do {
          seat_idx = seat_indices[(short)inner_idx];
          if (seat_idx != -1) {
            seat_element = (int)tag_block_get_element(
              (void *)(vehicle_tag + 0x2e4), (int)seat_idx, 0x11c);

            /* Check seat type compatibility */
            if (*(short *)(child_data + 0x64) != 1) {
              seat_type_ok = FUN_001acd70(child_handle, (const char *)(seat_element + 4), 0, 0);
              if (seat_type_ok == '\0') {
                goto next_seat;
              }
            }

            /* Handle existing vehicle occupancy */
            if (*(int *)(child_data + 0xcc) != NONE) {
              if (*(short *)(child_data + 0x2a0) != -1) {
                unit_exit_seat_end(child_handle);
              }
              if (*(int *)(child_data + 0xcc) != NONE) {
                goto next_seat;
              }
            }

            /* Board the vehicle */
            board_ok = unit_board_vehicle(child_handle, vehicle_handle, seat_idx);
            if (board_ok != '\0') {
              seat_indices[(short)inner_idx] = -1;
              loaded_count = loaded_count + 1;
              break;
            }
          }
next_seat:
          inner_idx = inner_idx + 1;
        } while ((short)inner_idx < (short)seat_count);
      }
    }

    /* Get next child */
    child_handle = FUN_000ce320(group_handle, iter_state);
  } while (child_handle != NONE);

  return loaded_count;
}

/* unit_try_and_exit_seat (0x1b3580) — attempt to exit the current seat.
 *
 * Checks if the unit is in a vehicle seat and meets the conditions to exit:
 * not a player type (seat type != 1), animation state allows exit, and
 * the seat has exit animation data. If the vehicle's driver matches this
 * unit, opens the vehicle. Sets garbage flag, updates animation state to
 * 0x1b (exiting), and notifies AI.
 *
 * Returns 1 on success, 0 if exit is blocked.
 *
 * Source: units.c
 */
char unit_try_and_exit_seat(int unit_handle)
{
  char *unit;
  int vehicle_handle;
  int unit_tag;
  int antr_tag;
  int mode_element;
  int anim_block_count;
  int16_t exit_anim;
  char *vehicle_data;
  int anim_graph_tag_index;
  int16_t animation_index;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);

  /* Must be in a vehicle and have a powered seat */
  if (*(int *)(unit + 0xcc) == NONE || *(short *)(unit + 0x2a0) == -1) {
    return 0;
  }

  /* Player-type units (seat type 1) use a direct exit */
  if (*(short *)(unit + 0x64) == 1) {
    unit_exit_seat_end(unit_handle);
    return 0;
  }

  /* Check if animation state blocks exit */
  if (FUN_001a8730((void *)(unit + 0x248)) != '\0') {
    return 0;
  }

  /* Look up unit and animation tags */
  unit_tag = (int)tag_get(0x756e6974, *(int *)unit);
  antr_tag = (int)tag_get(0x616e7472, *(int *)(unit_tag + 0x44));

  /* Get the mode element for this unit's current seat */
  mode_element = (int)tag_block_get_element(
    (void *)(antr_tag + 0xc),
    (int)*(int8_t *)(unit + 0x250),
    100);

  /* Check if the mode has exit animations (block count > 8) */
  anim_block_count = *(int *)(mode_element + 0x40);
  if (anim_block_count <= 8) {
    return 0;
  }

  /* Get the exit animation index from sub-block element 0, offset 0x10 */
  exit_anim = *(short *)(*(int *)(mode_element + 0x44) + 0x10);
  if (exit_anim == -1) {
    return 0;
  }

  /* If this unit is the vehicle's driver, open the vehicle */
  vehicle_handle = *(int *)(unit + 0xcc);
  vehicle_data = (char *)object_get_and_verify_type(vehicle_handle, 3);
  if (*(int *)(vehicle_data + 0x2d4) == unit_handle) {
    unit_open(vehicle_handle);
  }

  /* Start exit animation: look up via FUN_000fad00, then set */
  anim_graph_tag_index = *(int *)(unit_tag + 0x44);
  animation_index = FUN_000fad00(anim_graph_tag_index, exit_anim);
  unit_set_animation(unit_handle, anim_graph_tag_index, animation_index);

  /* Mark unit as garbage and set exit animation state */
  object_set_garbage(unit_handle, 1);
  *(uint8_t *)(unit + 0x253) = 0x1b;

  /* Notify AI subsystem of vehicle exit */
  ai_handle_exit_vehicle(unit_handle);

  return 1;
}

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


/* unit_cause_melee_damage (0x1ae840)
 * Applies melee damage from a unit to a target. Resolves the melee marker
 * position, optionally performs a collision test to adjust the damage origin,
 * then builds damage params and applies via object_cause_damage.
 * cdecl, 7 stack params.
 * If melee_hit is false and the collision result has a valid material type,
 * plays the melee clang sound via FUN_001abd10. */
void unit_cause_melee_damage(int unit_handle, char melee_hit, int target_handle,
                             int param_4, int param_5, int param_6,
                             int param_7)
{
  char *unit;
  char *unit_tag;
  int16_t marker_count;
  /* FUN_0014df70 (collision raycast) writes an 80-byte result struct through
   * this pointer (stores at +0..+0x4e, derived from disasm). The original
   * allocates 0x50 bytes (lea [ebp-0x68], direction at [ebp-0x18]); a 4-byte
   * buffer here overflowed the saved EBX/EDI/ESI/EBP slots, corrupting the
   * caller's `unit` pointer to NONE (0xffffffff) -> [unit+0x25a] page fault
   * (CR2=0x259) when an elite melees in PoA. Matches the correct siblings at
   * units.c:2233 and units.c:11326. */
  char collision_result[80];
  float *position;
  float melee_pos[3];
  float direction[3];
  char coll_hit;
  int16_t coll_depth;
  int weapon_handle;
  char *weapon_obj;
  char *weapon_tag;
  int damage_effect_index;
  char marker_buf[96];
  char damage_params[0x54];

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (char *)tag_get(0x756e6974, *(int *)unit);

  if (*(int *)(unit_tag + 0x294) == -1) {
    goto cleanup;
  }

  marker_count = object_get_markers_by_string_id(
      unit_handle, (void *)0x25961c, marker_buf, 1);

  if (marker_count == 1) {
    /* marker found — use marker position as melee origin */
    melee_pos[0] = *(float *)(marker_buf + 0x60);
    melee_pos[1] = *(float *)(marker_buf + 0x64);
    melee_pos[2] = *(float *)(marker_buf + 0x68);

    /* collision user stack depth check */
    if (*(int16_t *)0x4761d8 >= MAXIMUM_COLLISION_USER_STACK_DEPTH) {
      display_assert(
          "global_current_collision_user_depth < "
          "MAXIMUM_COLLISION_USER_STACK_DEPTH",
          "c:\\halo\\SOURCE\\units\\units.c", 0x21b9, true);
      system_exit(-1);
    }

    coll_depth = *(int16_t *)0x4761d8;
    *(int16_t *)0x4761d8 = coll_depth + 1;

    position = (float *)(unit + 0x50);
    *(int16_t *)(0x5a8c80 + coll_depth * 2) = 7;

    /* direction = melee_pos - unit position */
    direction[0] = melee_pos[0] - position[0];
    direction[1] = melee_pos[1] - position[1];
    direction[2] = melee_pos[2] - position[2];

    coll_hit = (char)FUN_0014df70(0x1000e9, position, direction, -1,
                                  (int16_t *)collision_result);
    if (coll_hit != 0) {
      /* collision hit — snap melee position to unit center */
      melee_pos[0] = position[0];
      melee_pos[1] = position[1];
      melee_pos[2] = position[2];
    }

    if (*(int16_t *)0x4761d8 < 2) {
      display_assert("global_current_collision_user_depth > 1",
                     "c:\\halo\\SOURCE\\units\\units.c", 0x21c1, true);
      system_exit(-1);
    }
    *(int16_t *)0x4761d8 = *(int16_t *)0x4761d8 - 1;
  } else {
    /* no marker — use unit position directly */
    position = (float *)(unit + 0x50);
    melee_pos[0] = position[0];
    melee_pos[1] = position[1];
    melee_pos[2] = position[2];
  }

  /* Determine the damage effect tag index */
  damage_effect_index = *(int *)(unit_tag + 0x294);

  /* Check if the current weapon has an override melee damage effect */
  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  weapon_handle =
      unit_get_weapon(unit_handle, *(int16_t *)(unit + 0x2a2));

  if (weapon_handle != -1) {
    weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
    weapon_tag = (char *)tag_get(0x77656170, *(int *)weapon_obj);
    /* Check weapon flags bit 15 (byte at +0x309, high bit) for melee override */
    if ((char)(*(uint32_t *)(weapon_tag + 0x308) >> 8) < 0) {
      damage_effect_index = *(int *)(weapon_tag + 0x3a0);
    }
  }

  /* Build damage params */
  damage_data_new(damage_params, damage_effect_index);

  *(int *)(damage_params + 0x14) = *(int *)(unit + 0x48);
  *(int *)(damage_params + 0x18) = *(int *)(unit + 0x4c);
  *(int16_t *)(damage_params + 0x10) = *(int16_t *)(unit + 0x68);
  *(int *)(damage_params + 0x08) = *(int *)(unit + 0x1c8);
  *(float *)(damage_params + 0x20) = melee_pos[1];
  *(int *)(damage_params + 0x2c) = *(int *)(unit + 0x54);
  *(int *)(damage_params + 0x0c) = unit_handle;
  *(float *)(damage_params + 0x1c) = melee_pos[0];
  *(int *)(damage_params + 0x28) = *(int *)(unit + 0x50);
  *(float *)(damage_params + 0x24) = melee_pos[2];
  *(int *)(damage_params + 0x30) = *(int *)(unit + 0x58);

  if (target_handle == -1) {
    FUN_00138e30(damage_params, -1);
  } else {
    object_cause_damage(damage_params, target_handle, (short)param_4,
                        (short)param_5, (short)param_6, (unsigned int)param_7);
  }

  if (melee_hit == 0 && *(int16_t *)(damage_params + 0x4c) != -1) {
    FUN_001abd10(*(int16_t *)(damage_params + 0x4c), unit_handle,
                 damage_effect_index);
  }

cleanup:
  *(uint8_t *)(unit + 0x239) = 0;
}

/* unit_died (0x1b3060)
 * Handles unit death or feign-death. On real death (param_2=0): sets garbage,
 * releases player/actor refs, clears seats, drops weapons and grenades.
 * On feign death (param_2!=0): checks feign_death_timer and random chance
 * to decide living/feigning.
 * cdecl, 2 stack params. */
void unit_died(int unit_handle, char param_2)
{
  char *unit;
  char *unit_tag;
  char *actor_data;
  int weapon_handle;
  int temp_unit;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);

  if (param_2 == 0) {
    /* Real death */
    *(int16_t *)(unit + 0x3d0) = 0;
    object_set_garbage_flag(unit_handle, 1);

    /* Release player reference */
    if (*(int *)(unit + 0x1c8) != -1) {
      player_died(*(int *)(unit + 0x1c8));
      *(int *)(unit + 0x1c8) = -1;
    }

    /* Release actor reference (first slot) */
    if (*(int *)(unit + 0x1a4) != -1) {
      actor_data =
          (char *)datum_get(*(data_t **)0x6325a4, *(int *)(unit + 0x1a4));
      *(int16_t *)(unit + 0x2e4) = *(int16_t *)(actor_data + 0x34);
      *(int16_t *)(unit + 0x2e6) = *(int16_t *)(actor_data + 0x3a);
      actor_died(*(int *)(unit + 0x1a4));
      *(int *)(unit + 0x1a4) = -1;
    }

    /* Release actor reference (second slot) */
    if (*(int *)(unit + 0x1a8) != -1) {
      actor_data =
          (char *)datum_get(*(data_t **)0x6325a4, *(int *)(unit + 0x1a8));
      *(int16_t *)(unit + 0x2e4) = *(int16_t *)(actor_data + 0x34);
      *(int16_t *)(unit + 0x2e6) = *(int16_t *)(actor_data + 0x3a);
      actor_swarm_unit_died(*(int *)(unit + 0x1a8), unit_handle);
      *(int *)(unit + 0x1a8) = -1;
    }

    /* Record time of death */
    *(int *)(unit + 0x3cc) = game_time_get();
  } else {
    /* Feign death */
    if (*(int16_t *)(unit + 0x3d0) < 1) {
      display_assert("unit->unit.feign_death_timer > 0",
                     "c:\\halo\\SOURCE\\units\\units.c", 0x13eb, true);
      system_exit(-1);
    }

    unit_tag = (char *)tag_get(0x756e6974, *(int *)unit);

    {
      int *seed;
      float rnd;
      seed = get_global_random_seed_address();
      rnd = random_math_real((unsigned int *)seed);
      if (rnd < *(float *)(unit_tag + 0x248)) {
        *(uint32_t *)(unit + 0x1b4) |= 0x2000;
      } else {
        *(uint32_t *)(unit + 0x1b4) &= ~0x2000u;
      }
    }
  }

  /* Common death cleanup */
  *(uint32_t *)(unit + 0x1b4) &= 0xffffffee;
  *(int *)(unit + 0x1b8) = 0;

  /* Notify current weapon */
  if (*(int16_t *)(unit + 0x2a2) != -1) {
    temp_unit = (int)object_get_and_verify_type(unit_handle, 3);
    weapon_handle =
        unit_get_weapon(unit_handle, *(int16_t *)(temp_unit + 0x2a2));
    weapon_owner_update(weapon_handle, 0, 0.0f);
  }

  /* Clear integrated light bit */
  temp_unit = (int)object_get_and_verify_type(unit_handle, 3);
  *(uint32_t *)(temp_unit + 0x1b4) &= ~0x02000000u;

  /* Detach from parent (vehicle seat exit) */
  if (*(int *)(unit + 0xcc) != -1) {
    if (*(int16_t *)(unit + 0x2a0) == -1) {
      unit_detach_from_parent(unit_handle);
    } else {
      unit_exit_seat_end(unit_handle);
    }
  }

  /* Drop weapons and grenades */
  *(int16_t *)(unit + 0x368) = 0;
  unit_drop_weapons_on_death(unit_handle);

  /* Clean up secondary weapon reference */
  temp_unit = (int)object_get_and_verify_type(unit_handle, 3);
  if (*(int *)(temp_unit + 0x2c8) != -1) {
    weapon_handle = *(int *)(temp_unit + 0x2c8);
    unit_detach_weapon(unit_handle, weapon_handle);
    *(int *)(temp_unit + 0x2c8) = -1;
  }

  unit_drop_grenades_on_death(unit_handle);

  /* Hide in vehicle if not flagged */
  if (*(char *)(unit + 0x23c) == 0) {
    unit_set_in_vehicle(unit_handle, 1);
  }

  /* Final cleanup */
  *(int16_t *)(unit + 0x25e) = -1;
  *(int16_t *)(unit + 0x25a) = -1;
  *(uint8_t *)(unit + 0x239) = 0;
  if (*(char *)(unit + 0x23d) == 1) {
    *(uint8_t *)(unit + 0x23d) = 0;
  }
}

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


/* FUN_001aaf40 (0x1aaf40) — grenade throw initiation
 * Decrements grenade count (unless infinite), creates a grenade placement
 * from the unit's forward vector and marker position, spawns the grenade
 * object, and attaches it to the unit.
 * Register args: @edi = unit_handle. No stack params.
 * Called from the grenade throw state (state=1) in the unit update switch. */
void FUN_001aaf40(int unit_handle)
{
  char *unit;
  char *globals_entry;
  int grenade_index;
  char marker_buf[0x6c]; /* marker output buffer at EBP-0xf4 */
  char placement[0x88];  /* object placement data at EBP-0x88 */
  float forward[3];      /* at EBP-0x54 */
  float perp_out[12];    /* at EBP-0x48 */
  int new_handle;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  tag_get(0x756e6974, *(int *)unit);

  grenade_index = (int)*(int8_t *)(unit + 0x2cc);
  {
    char *game_globals;
    game_globals = (char *)game_globals_get();
    globals_entry =
        (char *)tag_block_get_element(game_globals + 0x128, grenade_index, 0x44);
  }

  /* Check if we should consume a grenade (skip if infinite) */
  if (*(int *)(unit + 0x1c8) != -1) {
    if (*(char *)0x5aa892 != 0) {
      goto skip_decrement;
    }
    if (FUN_000a9570(*(int *)(unit + 0x1c8)) != 0) {
      goto skip_decrement;
    }
  }

  if (*(int *)(unit + 0x1a4) != -1) {
    if (actor_has_unlimited_grenades() != 0) {
      goto skip_decrement;
    }
  }

  /* Validate grenade index */
  if (*(int8_t *)(unit + 0x2cc) < 0 || *(int8_t *)(unit + 0x2cc) > 1) {
    display_assert(
        "unit->unit.current_grenade_index>=0 && "
        "unit->unit.current_grenade_index<NUMBER_OF_UNIT_GRENADE_TYPES",
        "c:\\halo\\SOURCE\\units\\units.c", 0x1f1e, true);
    system_exit(-1);
  }

  /* Validate grenade count > 0 */
  if (*(int8_t *)(unit + 0x2ce + *(int8_t *)(unit + 0x2cc)) < 1) {
    display_assert(
        "unit->unit.grenade_counts[unit->unit.current_grenade_index]>0",
        "c:\\halo\\SOURCE\\units\\units.c", 0x1f1f, true);
    system_exit(-1);
  }

  /* Decrement grenade count */
  *(int8_t *)(unit + 0x2ce + *(int8_t *)(unit + 0x2cc)) -= 1;

skip_decrement:
  /* Get grenade marker position */
  object_get_markers_by_string_id(
      unit_handle, (void *)0x2b6d2c, marker_buf, 1);

  /* Build object placement data for the grenade */
  object_placement_data_new(placement, *(int *)(globals_entry + 0x40),
                            unit_handle);
  *(uint32_t *)(placement + 0x04) |= 2;

  /* Copy unit's aim forward vector */
  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  forward[0] = *(float *)(unit + 0x1ec);
  forward[1] = *(float *)(unit + 0x1f0);
  forward[2] = *(float *)(unit + 0x1f4);

  /* Compute perpendicular vector for orientation */
  perpendicular3d(forward, perp_out);
  normalize3d(perp_out);

  /* Copy marker position into placement position (offset 0x18) */
  *(int *)(placement + 0x18) = *(int *)(marker_buf + 0x60);
  *(int *)(placement + 0x1c) = *(int *)(marker_buf + 0x64);
  *(int *)(placement + 0x20) = *(int *)(marker_buf + 0x68);

  /* Spawn the grenade object */
  new_handle = object_new(placement);
  if (new_handle != -1) {
    /* Attach grenade to the unit at the marker node */
    object_attach_to_parent(unit_handle, new_handle,
                            *(int *)marker_buf);
    *(int *)(unit + 0x244) = new_handle;
    *(uint8_t *)(unit + 0x23d) = 2;
    return;
  }

  *(uint8_t *)(unit + 0x23d) = 3;
}

/* FUN_001abd90 (0x1abd90) — melee lunge collision damage
 * Tests for melee collision against the unit's parent (seat occupant target),
 * and applies damage using the unit's melee damage effect tag. When collision
 * hits, computes a surface normal and applies damage with collision context.
 * Otherwise applies damage with no-target params.
 * Register args: @edi = unit_handle. No stack params.
 * Called at the melee lunge phase (state 4) in unit_update. */
void FUN_001abd90(int unit_handle)
{
  char *unit;
  char *unit_tag_data;
  int parent_handle;
  char collision_buf[0x4c0 - 0x64]; /* large collision buffer */
  char collision_result[0x60];
  char damage_params[0x54];
  float direction[3];
  float point_out[3];
  float surface_out[16];
  float normal_out[16];
  char hit_found;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  unit_tag_data = (char *)tag_get(0x756e6974, *(int *)unit);

  /* Only proceed if in melee lunge state 4, has parent, and has damage effect */
  if (*(char *)(unit + 0x239) != 4) {
    return;
  }
  parent_handle = *(int *)(unit + 0xcc);
  if (parent_handle == -1) {
    return;
  }
  if (*(int *)(unit_tag_data + 0x294) == -1) {
    return;
  }

  hit_found = 0;

  if (*(char *)(unit + 0x23a) == 0) {
    /* First attempt — perform collision test */
    if (*(int16_t *)0x4761d8 >= MAXIMUM_COLLISION_USER_STACK_DEPTH) {
      display_assert(
          "global_current_collision_user_depth < "
          "MAXIMUM_COLLISION_USER_STACK_DEPTH",
          "c:\\halo\\SOURCE\\units\\units.c", 0x22e6, true);
      system_exit(-1);
    }

    {
      int16_t coll_depth;
      char coll_result;

      coll_depth = *(int16_t *)0x4761d8;
      *(int16_t *)0x4761d8 = coll_depth + 1;
      *(int16_t *)(0x5a8c80 + coll_depth * 2) = 8;

      /* Set up collision test against parent */
      coll_result = FUN_0014c8e0((int *)collision_buf, parent_handle);

      if (coll_result != 0) {
        /* Get world position and compute melee direction */
        object_get_world_position(unit_handle, (vector3_t *)point_out);

        direction[0] = *(float *)(unit + 0x24) * *(float *)0x2549d4;
        direction[1] = *(float *)(unit + 0x28) * *(float *)0x2549d4;
        direction[2] = *(float *)(unit + 0x2c) * *(float *)0x2549d4;

        vector3d_scale_add(point_out, direction, *(float *)0xbf000000,
                           point_out);

        coll_result = FUN_0014cb00((int)collision_buf, (void *)3, point_out,
                                   direction, (int16_t *)collision_result);

        if (coll_result != 0) {
          /* Compute hit point */
          vector3d_scale_add(point_out, direction,
                             *(float *)(collision_result + 0x0c),
                             surface_out);

          /* Get surface normal */
          {
            int surface_base;
            surface_base = *(int *)(collision_buf + 0x70 - 0x64);
            FUN_0010a1c0(
                (float *)(surface_base +
                          *(int16_t *)collision_result * 0x34),
                (float *)(collision_result + 0x14),
                (float *)normal_out);
          }

          /* Negate normal if backfacing */
          if (*(int *)(collision_result + 0x1c) < 0) {
            plane_negate((float *)normal_out, (float *)normal_out);
          }

          hit_found = 1;
        }
      }

      /* Pop collision user depth */
      if (*(int16_t *)0x4761d8 < 2) {
        display_assert("global_current_collision_user_depth > 1",
                       "c:\\halo\\SOURCE\\units\\units.c", 0x22fe, true);
        system_exit(-1);
      }
      *(int16_t *)0x4761d8 = *(int16_t *)0x4761d8 - 1;
    }
  }

  /* Build damage params from melee damage effect */
  {
    int damage_effect;
    damage_effect = *(int *)(unit_tag_data + 0x294);
    damage_data_new(damage_params, damage_effect);
  }

  /* Set damage params common fields */
  *(int *)(damage_params + 0x00) = unit_handle;
  *(int16_t *)(damage_params + 0x04) = *(int16_t *)(unit + 0x68);
  *(int *)(damage_params + 0x08) = *(int *)(unit + 0x1c8);
  *(float *)(damage_params + 0x20) = 0.03333333f; /* 1/30 */

  if (hit_found) {
    /* Copy hit position and forward direction into damage params */
    *(float *)(damage_params + 0x34) = surface_out[0];
    *(float *)(damage_params + 0x38) = surface_out[1];
    *(float *)(damage_params + 0x30) = surface_out[0]; /* duplicate */
    *(float *)(damage_params + 0x3c) = surface_out[2];

    /* Copy unit forward as damage direction */
    *(float *)(damage_params + 0x2c) = *(float *)(unit + 0x24);
    *(float *)(damage_params + 0x28) = *(float *)(unit + 0x28);
    *(float *)(damage_params + 0x24) = *(float *)(unit + 0x2c);

    *(uint32_t *)(damage_params + 0x04) |= 2;
    *(char *)(unit + 0x23a) = 10;

    object_cause_damage(damage_params, parent_handle,
                        *(int16_t *)collision_result,
                        *(int16_t *)(collision_result + 0x02),
                        *(int16_t *)(collision_result + 0x1a),
                        (unsigned int)normal_out);
  } else {
    object_cause_damage(damage_params, parent_handle,
                        (short)-1, (short)-1, (short)-1, 0);
  }

  /* Decrement attack timer */
  *(char *)(unit + 0x23a) = *(char *)(unit + 0x23a) - 1;
}

/* unit_adjust_plan_overlap (0x1acb70) — FPU quadratic solver for movement plans
 * When two movement plans overlap in time, adjusts the later plan by solving
 * a quadratic equation to trim its acceleration/deceleration phases.
 * Register args: @ecx = plan_a, @eax = plan_b. Stack: dummy, delta_time.
 * Pure math, no side effects beyond plan modification. */
void unit_adjust_plan_overlap(void *plan_a_ptr, void *plan_b_ptr, int dummy,
                              float delta_time)
{
  char *plan_a;
  char *plan_b;
  char *adjust_plan;
  float total_a;
  float total_b;
  float t_extension;
  float t_factor;
  float disc;
  float adj_amount;
  float min_t;
  float accel_t;
  float decel_t;
  float v_peak;

  plan_a = (char *)plan_a_ptr;
  plan_b = (char *)plan_b_ptr;

  /* Both plans must be active (byte 0 == 0) */
  if (*plan_a != 0 || *plan_b != 0) {
    return;
  }

  /* Compute total time for each plan: decel_t + vel_t + accel_t */
  total_a = *(float *)(plan_a + 0x1c) + *(float *)(plan_a + 0x14) +
            *(float *)(plan_a + 0x10);
  total_b = *(float *)(plan_b + 0x1c) + *(float *)(plan_b + 0x14) +
            *(float *)(plan_b + 0x10);

  /* Determine which plan to adjust */
  if (*(float *)(plan_a + 0x10) > 0.0f && total_b > total_a) {
    /* plan_a has priority — adjust plan_b using plan_a's extension */
    t_extension = total_b - total_a;
    adjust_plan = plan_a;
  } else if (*(float *)(plan_b + 0x10) > 0.0f && total_a > total_b) {
    /* plan_b has priority — adjust plan_a using plan_b's extension */
    t_extension = total_a - total_b;
    adjust_plan = plan_b;
  } else {
    return;
  }

  if (adjust_plan == NULL) {
    return;
  }

  /* Assert t_extension > 0 */
  if (t_extension <= 0.0f) {
    display_assert("t_extension > 0",
                   "c:\\halo\\SOURCE\\units\\units.c", 0x8ae, true);
    system_exit(-1);
  }

  /* Solve quadratic for adjustment amount */
  t_factor = (t_extension + *(float *)(adjust_plan + 0x14)) * delta_time;

  {
    float abs_vpeak;
    abs_vpeak = *(float *)(adjust_plan + 0x10) *
                    *(float *)(adjust_plan + 0x0c) +
                *(float *)(adjust_plan + 0x08);
    if (abs_vpeak < 0.0f) {
      abs_vpeak = -abs_vpeak;
    }
    disc = t_factor * t_factor -
           (-t_extension) * abs_vpeak * delta_time * 4.0f;
  }

  /* Assert discriminant >= 0 */
  if (disc < 0.0f) {
    display_assert("disc >= 0", "c:\\halo\\SOURCE\\units\\units.c", 0x8c4,
                   true);
    system_exit(-1);
  }

  /* Quadratic formula: (-b + sqrt(disc)) / (2*a) */
  adj_amount = (sqrtf(disc) - t_factor) / (delta_time + delta_time);

  /* Clamp to min(accel_t, decel_t) */
  if (*(float *)(adjust_plan + 0x10) <= *(float *)(adjust_plan + 0x1c)) {
    min_t = *(float *)(adjust_plan + 0x10);
  } else {
    min_t = *(float *)(adjust_plan + 0x1c);
  }

  if (adj_amount > min_t) {
    if (*(float *)(adjust_plan + 0x10) <= *(float *)(adjust_plan + 0x1c)) {
      adj_amount = *(float *)(adjust_plan + 0x10);
    } else {
      adj_amount = *(float *)(adjust_plan + 0x1c);
    }
  }

  /* Apply adjustment if positive */
  if (adj_amount <= 0.0f) {
    return;
  }

  accel_t = *(float *)(adjust_plan + 0x10) - adj_amount;
  *(float *)(adjust_plan + 0x10) = accel_t;

  v_peak = accel_t * *(float *)(adjust_plan + 0x0c) +
           *(float *)(adjust_plan + 0x08);

  decel_t = *(float *)(adjust_plan + 0x1c) - adj_amount;
  *(float *)(adjust_plan + 0x1c) = decel_t;

  *(float *)(adjust_plan + 0x14) =
      ((v_peak + v_peak + adj_amount * *(float *)(adjust_plan + 0x0c)) *
       adj_amount) / v_peak;

  /* Assert both times remain non-negative */
  if (accel_t < 0.0f || decel_t < 0.0f) {
    display_assert(
        "(adjust_plan->accel_t >= 0) && (adjust_plan->decel_t >= 0)",
        "c:\\halo\\SOURCE\\units\\units.c", 0x8d8, true);
    system_exit(-1);
    return;
  }
}

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


/* FUN_001acd70 (0x1acd70) — unit_try_animation_state
 * Searches the unit's animation graph for a matching seat/weapon animation mode.
 * Register arg: unit_handle in EAX. */
char FUN_001acd70(int unit_handle, const char *seat_label,
                  const char *weapon_name, char apply_state)
{
  char *unit;
  char *unit_tag;
  char *antr_tag;
  int *anim_block;
  int mode_count;
  int16_t mode_index;
  char *mode;
  int sub_count;
  int16_t sub_index;
  char *sub_anim;
  int *weapon_block;
  int weapon_count;
  int16_t weapon_index;
  char *weapon_entry;
  char found;
  char has_multi_weapon;
  int16_t base_seat;
  int16_t si;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (char *)tag_get(0x756e6974, *(int *)unit);
  antr_tag = (char *)tag_get(0x616e7472, *(int *)(unit_tag + 0x44));
  anim_block = (int *)(antr_tag + 0xc);
  mode_count = *anim_block;
  found = 0;

  if (mode_count < 1)
    return 0;

  mode_index = 0;
  while (1) {
    mode = (char *)tag_block_get_element(anim_block, (int)mode_index, 0x64);

    if (seat_label != 0 &&
        crt_stricmp(seat_label, mode) != 0) {
      goto next_mode;
    }

    sub_count = *(int *)(mode + 0x58);
    sub_index = 0;
    if (sub_count < 1)
      goto next_mode;

    while (1) {
      sub_anim = (char *)tag_block_get_element(
        (int *)(mode + 0x58), (int)sub_index, 0xbc);
      weapon_block = (int *)(sub_anim + 0xb0);
      weapon_count = *weapon_block;
      weapon_index = 0;

      if (weapon_count < 1)
        goto next_sub;

      while (1) {
        weapon_entry = (char *)tag_block_get_element(
          weapon_block, (int)weapon_index, 0x3c);

        if (weapon_name == 0)
          goto matched;
        if (csstrcmp(weapon_name, "unarmed") == 0 &&
            *weapon_entry == '\0')
          goto matched;
        if (crt_stricmp(weapon_name, weapon_entry) == 0)
          goto matched;

        weapon_index++;
        if ((int)(int16_t)weapon_index >= weapon_count)
          goto next_sub;
        continue;

      matched:
        if (apply_state == 0)
          goto found_match;

        {
          int num_key_types;
          int *key_data;

          num_key_types = *(int *)(mode + 0x40);
          key_data = *(int **)(mode + 0x44);
          has_multi_weapon = 0;

          if ((num_key_types >= 3 &&
               *(int16_t *)((char *)key_data + 4) != -1) ||
              (num_key_types >= 4 &&
               *(int16_t *)((char *)key_data + 6) != -1) ||
              (num_key_types >= 5 &&
               *(int16_t *)((char *)key_data + 8) != -1)) {
            has_multi_weapon = 1;
          }
        }

        if (*(uint8_t *)(unit + 0x253) != 0x1c)
          *(uint8_t *)(unit + 0x253) = 0xff;

        *(uint8_t *)(unit + 0x250) = (uint8_t)mode_index;

        base_seat = -1;
        for (si = 0; si < NUMBER_OF_UNIT_BASE_SEATS; si++) {
          if (crt_stricmp(seat_label,
                          *(const char **)(0x32e484 + (int)si * 4)) == 0) {
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
        found = 1;
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

/* FUN_001ae490 (0x1ae490) — unit_next_weapon_index
 * Scans weapon slots circularly for the next valid weapon.
 * Register arg: unit_handle in EBX. */
int16_t FUN_001ae490(int unit_handle, int16_t current_index, int16_t direction)
{
  char *unit;
  int iter_index;
  int weapon_handle;
  int seat_label;
  char *weapon_label;
  char can_use;
  char usable;
  char readied;
  int best_index;
  int current;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  best_index = -1;

  if (current_index == (int16_t)-1) {
    current_index = 0;
  } else if (current_index < 0 || current_index >= MAXIMUM_WEAPONS_PER_UNIT) {
    display_assert(
      "current_index>=0 && current_index<MAXIMUM_WEAPONS_PER_UNIT",
      "c:\\halo\\SOURCE\\units\\units.c", 0x1e40, 1);
    system_exit(-1);
  }

  current = current_index;

  do {
    iter_index = (int)(int16_t)current;
    weapon_handle = *(int *)(unit + 0x2a8 + iter_index * 4);

    if (weapon_handle != -1) {
      object_get_and_verify_type(unit_handle, 3);
      object_get_and_verify_type(weapon_handle, 4);

      seat_label = unit_get_seat_label(unit_handle);
      weapon_label = (char *)weapon_get_label(weapon_handle);
      can_use = FUN_001acd70(unit_handle, (const char *)seat_label,
                             (const char *)weapon_label, 0);

      if (can_use != 0) {
        usable = (char)game_engine_allow_weapon_pick_up(unit_handle, weapon_handle);
        if (usable != 0) {
          if (direction != 0) {
            best_index = current;
          } else {
            if ((int16_t)best_index == (int16_t)-1 ||
                *(int *)(unit + 0x2b8 + (int)(int16_t)best_index * 4) <
                  *(int *)(unit + 0x2b8 + iter_index * 4)) {
              best_index = current;
            }
          }

          readied = (char)weapon_must_be_readied(
            *(int *)(unit + 0x2a8 + iter_index * 4));
          if (readied != 0)
            return (int16_t)best_index;

          if ((int16_t)current != current_index)
            return (int16_t)best_index;
        }
      }
    }

    if (direction < 0) {
      if ((int16_t)current == 0)
        current = 3;
      else
        current = iter_index - 1;
    } else {
      if ((int16_t)current == 3)
        current = 0;
      else
        current = iter_index + 1;
    }
  } while ((int16_t)current != current_index);

  return (int16_t)best_index;
}

/* FUN_001b04b0 (0x1b04b0) — unit_postprocess_nodes
 * Applies IK constraints and weapon-hold overlays to animation node matrices. */
void FUN_001b04b0(int unit_handle, int node_matrices)
{
  unsigned int *unit_data;
  int unit_tag;
  int anim_graph;
  int anim_mode;
  int mode_ext;
  int ik_point;
  int weapon_ik_point;
  unsigned int *unit_data2;
  int weapon_handle;
  short ik_index;
  unsigned char *anim_ctrl;
  char ik_active;
  char weapon_ik_active;
  int *ik_block;
  int *weapon_ik_block;
  int idx;

  unit_data = (unsigned int *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (int)tag_get(0x756e6974, *(int *)unit_data);

  if ((*(unsigned int *)(unit_tag + 0x17c) & 0x800) != 0) {
    return;
  }
  if (*(signed char *)((int)unit_data + 0x250) == -1) {
    return;
  }

  anim_graph = (int)tag_get(0x616e7472, *(int *)(unit_tag + 0x44));
  anim_mode = (int)tag_block_get_element(
    (void *)(anim_graph + 0xc),
    (int)*(signed char *)((int)unit_data + 0x250), 100);
  mode_ext = (int)tag_block_get_element(
    (void *)(anim_mode + 0x58),
    (int)*(signed char *)((int)unit_data + 0x251), 0xbc);

  if (*(int *)((int)unit_data + 0xcc) != -1) {
    ik_active = FUN_001a8850((void *)((int)unit_data + 0x248));
    if (ik_active != '\0') {
      ik_block = (int *)(anim_mode + 0x4c);
      ik_index = 0;
      if (0 < *(int *)(anim_mode + 0x4c)) {
        idx = 0;
        do {
          ik_point = (int)tag_block_get_element(ik_block, idx, 0x40);
          FUN_001414e0(unit_handle, ik_point,
                       *(int *)((int)unit_data + 0xcc),
                       ik_point + 0x20, node_matrices);
          ik_index = ik_index + 1;
          idx = (int)ik_index;
        } while (idx < *ik_block);
      }
    }
  }

  if (*(short *)((int)unit_data + 0x2a2) != -1) {
    anim_ctrl = (unsigned char *)((int)unit_data + 0x248);
    weapon_ik_active = FUN_001a87f0((void *)anim_ctrl);
    if (weapon_ik_active != '\0') {
      weapon_ik_block = (int *)(mode_ext + 0xa4);
      ik_index = 0;
      if (0 < *(int *)(mode_ext + 0xa4)) {
        idx = 0;
        do {
          weapon_ik_point = (int)tag_block_get_element(
            weapon_ik_block, idx, 0x40);
          unit_data2 = (unsigned int *)object_get_and_verify_type(
            unit_handle, 3);
          weapon_handle = unit_get_weapon(unit_handle,
            (short)*(unsigned short *)((int)unit_data2 + 0x2a2));
          FUN_001414e0(unit_handle, weapon_ik_point,
                       weapon_handle,
                       weapon_ik_point + 0x20, node_matrices);
          ik_index = ik_index + 1;
          idx = (int)ik_index;
        } while (idx < *weapon_ik_block);
      }
      *anim_ctrl = *anim_ctrl & 0xfe;
    }
  }
}

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

/* FUN_001b0d90 (0x1b0d90) — animation state update
 *
 * Evaluates the current unit animation state and applies transitions.
 * Confirmed: cdecl, 2 stack params.
 * Returns: int16_t (animation flags bitmask).
 */
short FUN_001b0d90(int unit_handle, char *anim_state)
{
  unsigned int *unit;
  int unit_tag_data;
  short desired_state;
  short base_seat;
  short anim_status;
  unsigned short result;
  char apply_flag;
  short global_seat;
  char unit_anim_byte;
  unsigned int *vehicle_unit;
  int vehicle_tag;
  unsigned char *seat_element;
  int mode_tag;
  int anim_graph;
  int anim_element;
  float delta[3];
  char out_matrix[52];
  void *world_matrix;
  int biped_data;
  int biped_tag;

  unit = (unsigned int *)object_get_and_verify_type(unit_handle, 3);
  unit_tag_data = (int)tag_get(0x756e6974, *unit);
  desired_state = (short)*anim_state;
  result = 0;
  apply_flag = 0;

  if (desired_state < 0 || desired_state >= 0x2c) {
    display_assert(
        "desired_state>=0 && desired_state<NUMBER_OF_UNIT_STATES",
        "c:\\halo\\SOURCE\\units\\units.c", 0xb61, 1);
    system_exit(-1);
  }

  base_seat = -1;
  if (unit[0x33] == (unsigned int)-1 &&
      (*(unsigned char *)((int)unit + 0xb6) & 4) == 0) {
    switch (*(unsigned char *)((int)unit + 0x256)) {
    case 0:
      base_seat = 0;
      break;
    case 1:
    case 2:
      base_seat = 1;
      break;
    case 3:
      base_seat = (anim_state[1] != 0) + 2;
      if (base_seat == -1) goto seat_assert;
      break;
    case 4:
      base_seat = 2;
      break;
    case 5:
      base_seat = 4;
      break;
    case 6:
      base_seat = 5;
      break;
    default:
    seat_assert:
      display_assert("desired_base_seat_index!=NONE",
                     "c:\\halo\\SOURCE\\units\\units.c", 0xb73, 1);
      system_exit(-1);
      break;
    }

    if (unit[0x72] != (unsigned int)-1) {
      global_seat = *(short *)0x32de80;
      if (global_seat != -1) {
        if (global_seat < 0) {
          base_seat = 0;
        } else {
          base_seat = 6;
          if (global_seat < 7) {
            base_seat = global_seat;
          }
        }
      }
    }

    if (*(char *)((int)unit + 0x1bf) != -1) {
      base_seat = (short)*(char *)((int)unit + 0x1bf);
    }
    if ((unit[0x6e] & 0x200) != 0) {
      base_seat = 1;
    }
    if (*(char *)((int)unit + 0x23b) != 0) {
      base_seat = 5;
    }

    if (*(char *)((int)unit + 599) != (char)base_seat) {
      char can_change;
      can_change = FUN_001a86b0((void *)((int)unit + 0x248),
                                desired_state);
      if (can_change != 0) {
        char *weapon_name;
        const char *seat_label;
        weapon_name = unit_get_weapon_name(unit_handle, 1);
        seat_label = FUN_001ab6e0(base_seat);
        FUN_001acd70(unit_handle, seat_label, weapon_name, 1);
      }
    }
  }

  if (*(short *)((int)unit + 0x262) != -1) {
    anim_status = FUN_001ab870(
        (void *)((int)unit + 0x262),
        *(int *)(unit_tag_data + 0x44), unit_handle);
    if (anim_status == 2) {
      *(short *)((int)unit + 0x262) = -1;
    }
  }

  if (*(short *)(unit + 0x20) != -1) {
    anim_status = FUN_001ab870(
        (void *)((int)unit + 0x80),
        (int)unit[0x1f], unit_handle);
    if (anim_status == 1) {
      unit_anim_byte = *(char *)((int)unit + 0x253);
      if (unit_anim_byte >= 0x1e && unit_anim_byte <= 0x29) {
        switch (unit_anim_byte) {
        case 0x1e:
        case 0x1f:
        case 0x29:
          unit_cause_melee_damage(unit_handle, 0, -1, -1, -1, -1, 0);
          break;
        case 0x21:
          FUN_001ab110(unit_handle, 0);
          break;
        default:
          break;
        }
      }
    } else if (anim_status == 2) {
      unit_anim_byte = *(char *)((int)unit + 0x253);
      switch (unit_anim_byte) {
      case 0x19:
        if ((*(unsigned char *)(unit_tag_data + 0x17c) & 2) == 0) {
          goto start_limp;
        }
        if ((*(unsigned char *)((int)unit + 4) & 0x20) != 0) {
          goto destroy_unit;
        }
        if (*(short *)(unit + 0x19) != 0) {
          goto set_garbage_flag;
        }
        biped_data = (int)object_get_and_verify_type(unit_handle, 1);
        biped_tag = (int)tag_get(0x62697064,
                            *(unsigned int *)biped_data);
        if ((*(unsigned char *)(biped_data + 0x424) & 1) != 0 &&
            (*(unsigned int *)(biped_tag + 0x2f4) & 0x400) == 0) {
          goto start_limp;
        }
      destroy_unit:
        unit_destroy(unit_handle);
        break;
      start_limp:
        if (*(short *)(unit + 0x19) == 0) {
          biped_start_limp_body_physics(unit_handle);
        }
      set_garbage_flag:
        *(unsigned char *)((int)unit + 0x248) =
            *(unsigned char *)((int)unit + 0x248) | 4;
        *(short *)((int)unit + 0x82) =
            *(short *)((int)unit + 0x82) - 1;
        break;

      case 0x1a:
        vehicle_unit = (unsigned int *)object_get_and_verify_type(
            unit[0x33], 3);
        vehicle_tag = (int)tag_get(0x756e6974, *vehicle_unit);
        seat_element = (unsigned char *)tag_block_get_element(
            (void *)(vehicle_tag + 0x2e4),
            (int)*(short *)(unit + 0xa8), 0x11c);
        object_set_garbage(unit_handle, (~*seat_element) & 1);
        if (vehicle_unit[0xb5] == (unsigned int)unit_handle) {
          unit_close((int)unit[0x33]);
        }
        break;

      case 0x1b:
        mode_tag = (int)tag_get(0x6d6f6465,
                           *(unsigned int *)(unit_tag_data + 0x34));
        anim_graph = (int)tag_get(0x616e7472, unit[0x1f]);
        anim_element = (int)tag_block_get_element(
            (void *)(anim_graph + 0x74),
            (int)*(short *)(unit + 0x20), 0xb4);
        FUN_001234b0((void *)mode_tag, (void *)anim_element,
                     *(unsigned short *)((int)unit + 0x82), delta);
        world_matrix = (void *)object_get_world_matrix(unit_handle,
                                               out_matrix);
        matrix_scale_transform_vector((float *)world_matrix,
                                      delta, delta);
        unit_exit_seat_end(unit_handle);
        vector3d_add((float *)(unit + 6), delta, (float *)(unit + 6));
        break;

      case 0x25:
      case 0x26:
        *(short *)((int)unit + 0x82) =
            *(short *)((int)unit + 0x82) - 1;
        break;

      case 0x27:
        result = 1;
        desired_state = 0x28;
        break;

      default:
        break;
      }

      {
        char anim_ok;
        anim_ok = FUN_001a8790((void *)((int)unit + 0x248));
        if (anim_ok == 0) {
          apply_flag = 1;
        }
      }
    }
  }

  if (*(short *)((int)unit + 0x25a) != -1) {
    anim_status = FUN_001ab870(
        (void *)((int)unit + 0x25a),
        *(int *)(unit_tag_data + 0x44), unit_handle);
    if (anim_status == 2) {
      int refreshed_unit;
      object_set_region_count(unit_handle, 6);
      refreshed_unit = (int)object_get_and_verify_type(unit_handle, 3);
      *(char *)(refreshed_unit + 0x254) = 0;
      *(short *)(refreshed_unit + 0x25a) = -1;
    }
  }

  if (*(short *)((int)unit + 0x25e) != -1) {
    anim_status = FUN_001ab870(
        (void *)((int)unit + 0x25e),
        *(int *)(unit_tag_data + 0x44), unit_handle);
    if (anim_status == 2 || anim_status == 4) {
      unit_anim_byte = *(char *)((int)unit + 0x253);
      if (unit_anim_byte < 3 || unit_anim_byte > 4) {
        *(char *)((int)unit + 0x255) = 0;
        *(short *)((int)unit + 0x25e) = -1;
      }
    }
  }

  if (apply_flag == 0) {
    if ((short)desired_state ==
        (short)*(char *)((int)unit + 0x253)) {
      goto done;
    }
    {
      char can_apply;
      can_apply = FUN_001a86b0((void *)((int)unit + 0x248),
                               desired_state);
      if (can_apply == 0) goto done;
    }
  }
  FUN_001ad260(unit_handle, desired_state);

done:
  return (short)(result & 0xffff);
}

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

/* 0x1a8770 — True when anim_state@ecx byte +0xb is firing (3 or 4). */
#if defined(__clang__)
__attribute__((naked, noinline))
char FUN_001a8770(void *anim_state __attribute__((unused)))
{
  __asm__ volatile(
      "movb 0xb(%%ecx), %%cl\n\t"
      "xorb %%al, %%al\n\t"
      "cmpb $3, %%cl\n\t"
      "jl 1f\n\t"
      "cmpb $4, %%cl\n\t"
      "jg 1f\n\t"
      "movb $1, %%al\n\t"
      "1:\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
char FUN_001a8770(void *anim_state)
{
  char state = *(char *)((char *)anim_state + 0xb);

  if (state < 3)
    return 0;
  if (state > 4)
    return 0;
  return 1;
}
#endif

/* 0x1a8890 — gate on anim_state@ecx [0xc]==0 and motion band at [0xb]. */
#if defined(__clang__)
__attribute__((naked, noinline))
char FUN_001a8890(void *anim_state __attribute__((unused)))
{
  __asm__ volatile(
      "movb 0xc(%%ecx), %%al\n\t"
      "movb 0xb(%%ecx), %%cl\n\t"
      "testb %%al, %%al\n\t"
      "sete %%al\n\t"
      "cmpb $0x17, %%cl\n\t"
      "jl 2f\n\t"
      "cmpb $0x23, %%cl\n\t"
      "jle 1f\n\t"
      "cmpb $0x29, %%cl\n\t"
      "jne 2f\n\t"
      "1:\n\t"
      "xorb %%al, %%al\n\t"
      "2:\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
char FUN_001a8890(void *anim_state)
{
  char zero_flag = *(char *)((char *)anim_state + 0xc);
  char band = *(char *)((char *)anim_state + 0xb);
  char result = (zero_flag == 0);

  if (band < 0x17)
    return result;
  if (band <= 0x23)
    return 0;
  if (band == 0x29)
    return 0;
  return result;
}
#endif

/* 0x1a8910 — table lookup on anim_state@cx for states 0x1e..0x29.
 * XBE uses an in-function jump table; slot table is in .rodata so the PE
 * export ends at ret (same return polarity: 0 for slots marked 0). */
#if defined(__clang__)
static const unsigned char FUN_001a8910_slots[12] = {
    0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0,
};

__attribute__((naked, noinline))
char FUN_001a8910(int16_t anim_state __attribute__((unused)))
{
  __asm__ volatile(
      "movswl %%cx, %%ecx\n\t"
      "addl $-0x1e, %%ecx\n\t"
      "cmpl $0xb, %%ecx\n\t"
      "movb $1, %%al\n\t"
      "ja 2f\n\t"
      "movzbl %[slots](%%ecx), %%ecx\n\t"
      "testb %%cl, %%cl\n\t"
      "jne 2f\n\t"
      "xorb %%al, %%al\n\t"
      "2:\n\t"
      "ret\n\t"
      :
      : [slots] "m"(*(const unsigned char (*)[12])FUN_001a8910_slots)
      : "memory");
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
#if defined(__clang__)
__attribute__((naked, noinline))
int FUN_001a8950(int16_t anim_state __attribute__((unused)),
                 int16_t target_state __attribute__((unused)))
{
  __asm__ volatile(
      "testw %%cx, %%cx\n\t"
      "movl $6, %%eax\n\t"
      "je 1f\n\t"
      "cmpw $2, %%cx\n\t"
      "je 1f\n\t"
      "cmpw $3, %%cx\n\t"
      "jne 2f\n\t"
      "1:\n\t"
      "testw %%dx, %%dx\n\t"
      "je 3f\n\t"
      "cmpw $2, %%dx\n\t"
      "je 3f\n\t"
      "cmpw $3, %%dx\n\t"
      "jne 2f\n\t"
      "3:\n\t"
      "movl $1, %%eax\n\t"
      "2:\n\t"
      "cmpw $0x16, %%cx\n\t"
      "je 4f\n\t"
      "cmpw $0x15, %%cx\n\t"
      "jne 5f\n\t"
      "4:\n\t"
      "movl $2, %%eax\n\t"
      "5:\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
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
#endif
