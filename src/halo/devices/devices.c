#include <stdint.h>
/* --- devices.obj batch drafts (2026-07-26) --- */

/* device_new (0x960c0) — readable C lift. */
char device_new(int object_handle)
{
  char *obj = (char *)object_get_and_verify_type(object_handle, 0x380);
  tag_get(0x64657669, *(int *)obj);
  *(unsigned short *)(obj + 0x1b4) = 0xffff;
  *(unsigned short *)(obj + 0x1a8) = 0xffff;
  *(unsigned int *)(obj + 4) |= 0x40000u;
  return 1;
}

/* device_export_function_values (0x96110) — XBE naked draft (batch 255). */
#if defined(__clang__)
static void *(*const b96110_get)(int, int) = object_get_and_verify_type;
static void *(*const b96110_tag)(int, int) = tag_get;
static void *(*const b96110_dget)(void *, int) = (void *(*)(void *, int))datum_get;

__attribute__((naked, noinline))
void device_export_function_values(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x380\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x64657669\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "leal 0xd4(%%edi), %%edx\n\t"
      "leal 0x198(%%ebx), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl $4, -0x10(%%ebp)\n\t"
      ".Ldevice_export_function_values_1:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movw (%%ecx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Ldevice_export_function_values_14\n\t"
      "flds 0x2533c0\n\t"
      "movswl %%ax, %%eax\n\t"
      "decl %%eax\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "cmpl $5, %%eax\n\t"
      "ja .Ldevice_export_function_values_13\n\t"
      "jmp *.Ldevice_export_function_values_jt(,%%eax,4)\n\t"
      ".Ldevice_export_function_values_2:\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x1ac(%%edi)\n\t"
      "jmp .Ldevice_export_function_values_13\n\t"
      ".Ldevice_export_function_values_3:\n\t"
      "flds 0x1b0(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Ldevice_export_function_values_13\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x1b0(%%edi)\n\t"
      "fabs\n\t"
      "fdivs 0x278(%%ebx)\n\t"
      "jmp .Ldevice_export_function_values_13\n\t"
      ".Ldevice_export_function_values_4:\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x1b8(%%edi)\n\t"
      "jmp .Ldevice_export_function_values_13\n\t"
      ".Ldevice_export_function_values_5:\n\t"
      "flds 0x1bc(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Ldevice_export_function_values_13\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x1bc(%%edi)\n\t"
      "fabs\n\t"
      "fdivs 0x288(%%ebx)\n\t"
      "jmp .Ldevice_export_function_values_13\n\t"
      ".Ldevice_export_function_values_6:\n\t"
      "flds 0x1ac(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Ldevice_export_function_values_7\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      "fsts -0xc(%%ebp)\n\t"
      ".Ldevice_export_function_values_7:\n\t"
      "cmpw $7, 0x64(%%edi)\n\t"
      "jne .Ldevice_export_function_values_13\n\t"
      "cmpw $-1, 0x1b4(%%edi)\n\t"
      "je .Ldevice_export_function_values_13\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "fstp %%st(0)\n\t"
      "pushl $0x80\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "movl 0x5aa8c8, %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl 0x1b4(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x1c4(%%esi), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $3, %%cl\n\t"
      "je .Ldevice_export_function_values_8\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Ldevice_export_function_values_9\n\t"
      ".Ldevice_export_function_values_8:\n\t"
      "flds -0xc(%%ebp)\n\t"
      ".Ldevice_export_function_values_9:\n\t"
      "movw 0x2(%%eax), %%ax\n\t"
      "testb $1, %%al\n\t"
      "je .Ldevice_export_function_values_10\n\t"
      "testb $2, %%al\n\t"
      "je .Ldevice_export_function_values_10\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".Ldevice_export_function_values_10:\n\t"
      "cmpl $0x3f800000, 0x1b8(%%esi)\n\t"
      "je .Ldevice_export_function_values_11\n\t"
      "testb $4, %%cl\n\t"
      "je .Ldevice_export_function_values_13\n\t"
      ".Ldevice_export_function_values_11:\n\t"
      "fstp %%st(0)\n\t"
      ".Ldevice_export_function_values_12:\n\t"
      "flds 0x2533c0\n\t"
      ".Ldevice_export_function_values_13:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "fstps (%%eax)\n\t"
      ".Ldevice_export_function_values_14:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $2, %%edx\n\t"
      "addl $4, %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jne .Ldevice_export_function_values_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Ldevice_export_function_values_15:\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x28c(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Ldevice_export_function_values_12\n\t"
      "movswl 0x1c0(%%edi), %%edx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "fcoms 0x28c(%%ebx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Ldevice_export_function_values_11\n\t"
      "fdivs 0x28c(%%ebx)\n\t"
      "jmp .Ldevice_export_function_values_13\n\t"
      "nop\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Ldevice_export_function_values_jt:\n\t"
      ".long .Ldevice_export_function_values_2\n\t"
      ".long .Ldevice_export_function_values_3\n\t"
      ".long .Ldevice_export_function_values_4\n\t"
      ".long .Ldevice_export_function_values_5\n\t"
      ".long .Ldevice_export_function_values_6\n\t"
      ".long .Ldevice_export_function_values_15\n\t"
      ".text\n\t"
      :
      : [get] "m"(b96110_get), [tag] "m"(b96110_tag), [dget] "m"(b96110_dget)
      : "memory");
}
#else
#error "device_export_function_values: clang naked draft required"
#endif


/* device_preprocess_node_orientations (0x96310) — XBE naked draft (batch 270). */
#if defined(__clang__)
static void *(*const b96310_get)(int, int) = object_get_and_verify_type;
static void *(*const b96310_tag)(int, int) = tag_get;
static void *(*const b96310_elem)(void *, int, int) = tag_block_get_element;
static void (*const b96310_ftol)(void) = FUN_001d9068;
static void (*const b96310_c122240)(void *animation, int frame, void *node_output) = overlay_animation_apply;
static void (*const b96310_c122690)(void *animation, float frame, void *node_data) = FUN_00122690;

__attribute__((naked, noinline))
void device_preprocess_node_orientations(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl $0x380\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x64657669\n\t"
      "call *%[tag]\n\t"
      "movl 0x44(%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x616e7472\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x30(%%ebx), %%ecx\n\t"
      "leal 0x30(%%ebx), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "je .Ldevice_preprocess_node_orientations_9\n\t"
      "pushl %%esi\n\t"
      "pushl $0x60\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Ldevice_preprocess_node_orientations_8\n\t"
      "movl 0x54(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .Ldevice_preprocess_node_orientations_7\n\t"
      "movl 0x58(%%esi), %%eax\n\t"
      "movw (%%eax), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Ldevice_preprocess_node_orientations_7\n\t"
      "movswl %%ax, %%ecx\n\t"
      "pushl $0xb4\n\t"
      "pushl %%ecx\n\t"
      "addl $0x74, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movb 0x1a4(%%edi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $1, %%al\n\t"
      "je .Ldevice_preprocess_node_orientations_1\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x1b8(%%edi)\n\t"
      "jmp .Ldevice_preprocess_node_orientations_2\n\t"
      ".Ldevice_preprocess_node_orientations_1:\n\t"
      "flds 0x1b8(%%edi)\n\t"
      ".Ldevice_preprocess_node_orientations_2:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x17c(%%edx), %%eax\n\t"
      "testb $1, %%al\n\t"
      "je .Ldevice_preprocess_node_orientations_3\n\t"
      "movswl 0x22(%%ebx), %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "jmp .Ldevice_preprocess_node_orientations_4\n\t"
      ".Ldevice_preprocess_node_orientations_3:\n\t"
      "movswl 0x22(%%ebx), %%edx\n\t"
      "decl %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      ".Ldevice_preprocess_node_orientations_4:\n\t"
      "testb $2, %%al\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "je .Ldevice_preprocess_node_orientations_5\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "flds -0x4(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "call *%[ftol]\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c122240]\n\t"
      "jmp .Ldevice_preprocess_node_orientations_6\n\t"
      ".Ldevice_preprocess_node_orientations_5:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c122690]\n\t"
      ".Ldevice_preprocess_node_orientations_6:\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "addl $0xc, %%esp\n\t"
      ".Ldevice_preprocess_node_orientations_7:\n\t"
      "cmpl $1, 0x54(%%esi)\n\t"
      "jle .Ldevice_preprocess_node_orientations_8\n\t"
      "movl 0x58(%%esi), %%eax\n\t"
      "movw 0x2(%%eax), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Ldevice_preprocess_node_orientations_8\n\t"
      "movswl %%ax, %%ecx\n\t"
      "pushl $0xb4\n\t"
      "pushl %%ecx\n\t"
      "addl $0x74, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movswl 0x22(%%eax), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%edx\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x1ac(%%edi)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c122690]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Ldevice_preprocess_node_orientations_8:\n\t"
      "popl %%esi\n\t"
      ".Ldevice_preprocess_node_orientations_9:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b96310_get), [tag] "m"(b96310_tag), [elem] "m"(b96310_elem), [ftol] "m"(b96310_ftol), [c122240] "m"(b96310_c122240), [c122690] "m"(b96310_c122690)
      : "memory");
}
#else
#error "device_preprocess_node_orientations: clang naked draft required"
#endif


/* device_get_position (0x96470) — readable C lift. */
float device_get_position(int a0)
{
  if (a0 == -1)
    return 0.0f;
  void *obj = object_get_and_verify_type(a0, 0x380);
  return *(float *)((char *)obj + 0x1b8);
}

/* device_get_power (0x964a0) — readable C lift. */
float device_get_power(int a0)
{
  if (a0 == -1)
    return 0.0f;
  void *obj = object_get_and_verify_type(a0, 0x380);
  return *(float *)((char *)obj + 0x1ac);
}

/* device_set_never_appears_locked (0x964d0) — readable C lift (assert wrapper). */
void device_set_never_appears_locked(int a0, int a1)
{
  if (a0 == -1) {
    return;
  }
  {
    void *obj = object_try_and_get_and_verify_type(a0, 0x80);
    if (!obj) {
      return;
    }
    uint32_t flags = *(uint32_t *)((char *)obj + 0x1c4);
    if (a1) {
      flags |= 4;
    }
    *(uint32_t *)((char *)obj + 0x1c4) = flags;
  }
}

/* device_group_set_actual_value (0x96510) — XBE naked draft (batch 267). */
#if defined(__clang__)
static void *(*const b96510_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b96510_c13d6f0)(void *iter, int type_mask, int flags) = object_iterator_new;
static void * (*const b96510_c13d730)(void *iter) = object_iterator_next;

__attribute__((naked, noinline))
void device_group_set_actual_value(int a0 __attribute__((unused)), float a1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Ldevice_group_set_actual_value_1\n\t"
      "movl $0, 0xc(%%ebp)\n\t"
      "jmp .Ldevice_group_set_actual_value_2\n\t"
      ".Ldevice_group_set_actual_value_1:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Ldevice_group_set_actual_value_2\n\t"
      "movl $0x3f800000, 0xc(%%ebp)\n\t"
      ".Ldevice_group_set_actual_value_2:\n\t"
      "movl 0x5aa8c8, %%ecx\n\t"
      "pushl %%esi\n\t"
      "movw 0x8(%%ebp), %%si\n\t"
      "movswl %%si, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl %%edi\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl $0x380\n\t"
      "pushl %%eax\n\t"
      "call *%[c13d6f0]\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13d730]\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .Ldevice_group_set_actual_value_6\n\t"
      "pushl %%ebx\n\t"
      "movl $4, %%ebx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Ldevice_group_set_actual_value_3:\n\t"
      "cmpw %%si, 0x1a8(%%eax)\n\t"
      "jne .Ldevice_group_set_actual_value_4\n\t"
      "movl 0x1a4(%%eax), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "orl %%ebx, %%ecx\n\t"
      "movl %%ecx, 0x1a4(%%eax)\n\t"
      "movl %%edx, 0x1ac(%%eax)\n\t"
      "movl %%edi, 0x1b0(%%eax)\n\t"
      ".Ldevice_group_set_actual_value_4:\n\t"
      "cmpw %%si, 0x1b4(%%eax)\n\t"
      "jne .Ldevice_group_set_actual_value_5\n\t"
      "orl %%ebx, 0x1a4(%%eax)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x1b8(%%eax)\n\t"
      "movl %%edi, 0x1bc(%%eax)\n\t"
      ".Ldevice_group_set_actual_value_5:\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c13d730]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jne .Ldevice_group_set_actual_value_3\n\t"
      "popl %%ebx\n\t"
      ".Ldevice_group_set_actual_value_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b96510_dget), [c13d6f0] "m"(b96510_c13d6f0), [c13d730] "m"(b96510_c13d730)
      : "memory");
}
#else
#error "device_group_set_actual_value: clang naked draft required"
#endif


/* device_one_sided_set (0x965f0) — readable C lift (assert wrapper). */
void device_one_sided_set(int a0, int a1)
{
  {
    void *obj = object_try_and_get_and_verify_type(a0, 0x80);
    if (!obj) {
      return;
    }
    uint32_t flags = *(uint32_t *)((char *)obj + 0x1c4);
    if (a1) {
      flags |= 2;
    }
    *(uint32_t *)((char *)obj + 0x1c4) = flags;
  }
}

/* device_operates_automatically_set (0x96630) — readable C lift (assert wrapper). */
void device_operates_automatically_set(int a0, int a1)
{
  {
    void *obj = object_try_and_get_and_verify_type(a0, 0x80);
    if (!obj) {
      return;
    }
    uint32_t flags = *(uint32_t *)((char *)obj + 0x1c4);
    if (!a1) {
      flags |= 1;
    }
    *(uint32_t *)((char *)obj + 0x1c4) = flags;
  }
}

/* device_group_change_only_once_more_set (0x96670) — readable C lift. */
void device_group_change_only_once_more_set(int a0, int a1)
{
  if (a0 == -1)
    return;
  unsigned char *d = (unsigned char *)datum_get(*(void **)0x5aa8c8, a0);
  if (a1) {
    d[2] |= 1;
    d[2] &= (unsigned char)0xfd;
  } else {
    d[2] &= (unsigned char)0xfe;
    d[2] &= (unsigned char)0xfd;
  }
}

/* device_group_get_value (0x966b0) — readable C lift. */
float device_group_get_value(int a0)
{
  extern data_t *DAT_005aa8c8;
  char *g = (char *)datum_get(DAT_005aa8c8, (int)(int16_t)a0);
  return *(float *)(g + 4);
}

/* device_can_change_position (0x96720) — readable C lift. */
bool device_can_change_position(int object_handle)
{
  extern data_t *DAT_005aa8c8;
  char *obj;
  char *group_a;
  char *group_b;
  int16_t group_index;
  unsigned char flags;
  char ok;

  obj = (char *)object_get_and_verify_type(object_handle, 0x380);
  group_index = *(int16_t *)(obj + 0x1b4);
  ok = 0;
  if (group_index == -1)
    return (bool)ok;

  group_a = (char *)datum_get(DAT_005aa8c8, (int)group_index);
  group_b = (char *)datum_get(DAT_005aa8c8, (int)*(int16_t *)(obj + 0x1a8));
  flags = (unsigned char)*(uint16_t *)(group_a + 2);
  ok = 1;
  if ((flags & 1) && (flags & 2))
    ok = 0;
  if ((*(unsigned char *)(obj + 0x1a4) & 2) != 0)
    ok = 0;
  if (*(int *)(group_b + 4) != 0x3f800000)
    ok = 0;
  return (bool)ok;
}

/* FUN_000967a0 (0x967a0) — readable C lift. */
void FUN_000967a0(void *rec, int object)
{
  char *device;
  int group;
  extern char DAT_00269ac4[];

  if (object == -1)
    return;
  device = (char *)object_get_and_verify_type((int)rec, 0x380);
  group = tag_get_group_tag(object);
  if (group == 0x65666665) { /* 'effe' */
    FUN_0009ec30(object, (int)rec, (int)rec, -1,
                 *(float *)(device + 0x1b8), *(float *)(device + 0x1ac), 0, 0);
    return;
  }
  if (group == 0x736e6421) { /* 'snd!' */
    object_impulse_sound_new((int)rec, object, (int16_t)-1, (float *)0x31fc1c,
                             (float *)0x31fc3c, 1.0f);
    return;
  }
  display_assert((const char *)0, DAT_00269ac4, 0x2f9, 1);
  system_exit(-1);
}



/* device_effect_new (0x96850) — readable C lift. */
int16_t device_effect_new(int a, int16_t b)
{
  extern char DAT_00269af8[];
  extern char DAT_00269ac4[];
  int16_t idx = (int16_t)data_new_at_index(*(data_t **)0x5aa8c8);
  char *d;
  if (idx == -1) {
    display_assert(DAT_00269af8, DAT_00269ac4, 0x311, 1);
    system_exit(-1);
    return idx;
  }
  d = (char *)datum_get(*(data_t **)0x5aa8c8, idx);
  *(int *)(d + 4) = a;
  *(int16_t *)(d + 2) = b;
  return idx;
}

/* create_initial_device_groups (0x96900) — readable C lift. */
void create_initial_device_groups(void)
{
  extern char DAT_00269ac4[];
  extern char DAT_00269af8[];
  extern char DAT_00269b14[];
  char *scenario;
  char *block;
  int i;
  int count;
  char *elem;
  int name_index;
  short flags;
  short handle;
  char *rec;

  scenario = (char *)global_scenario_get();
  block = scenario + 0x288;
  count = *(int *)block;
  for (i = 0; i < count; i++) {
    elem = (char *)tag_block_get_element(block, i, 0x34);
    flags = 0;
    if ((elem[0x24] & 1) != 0)
      flags = 1;
    name_index = *(int *)(elem + 0x20);
    handle = (short)data_new_at_index(*(data_t **)0x5aa8c8);
    if (handle == (short)0xffff) {
      display_assert(DAT_00269af8, DAT_00269ac4, 0x311, 1);
      system_exit(-1);
    } else {
      rec = (char *)datum_get(*(data_t **)0x5aa8c8, (int)handle);
      *(int *)(rec + 4) = name_index;
      *(short *)(rec + 2) = flags;
    }
    if (handle != (short)i) {
      display_assert(DAT_00269b14, DAT_00269ac4, 0x339, 1);
      system_exit(-1);
    }
  }
}
/* device_delete (0x96a00) — readable C lift. */
void device_delete(int object_handle)
{
  char *device;
  short idx;
  char *rec;

  device = (char *)object_get_and_verify_type(object_handle, 0x380);
  idx = *(short *)(device + 0x1a8);
  if (idx != (short)0xffff) {
    rec = (char *)datum_get(*(void **)0x5aa8c8, (int)idx);
    if ((*(unsigned char *)(rec + 2) & 4) != 0)
      datum_delete(*(data_t **)0x5aa8c8, (int)idx);
  }
  idx = *(short *)(device + 0x1b4);
  if (idx != (short)0xffff) {
    rec = (char *)datum_get(*(void **)0x5aa8c8, (int)idx);
    if ((*(unsigned char *)(rec + 2) & 4) != 0)
      datum_delete(*(data_t **)0x5aa8c8, (int)idx);
  }
}


/* FUN_00096a90 (0x96a90) — XBE naked draft (batch 254). */
#if defined(__clang__)
static void *(*const b96a90_get)(int, int) = object_get_and_verify_type;
static void *(*const b96a90_tag)(int, int) = tag_get;
static void *(*const b96a90_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char (*const b96a90_c10f5b0)(float *pos, float *vel, float target, float accel, float max_speed, float wrap_min, float wrap_max, char wrap_flag) = accelerate_to_position;
static void (*const b96a90_c967a0)(void *rec, int object) = FUN_000967a0;

__attribute__((naked, noinline))
void FUN_00096a90(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x380\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x64657669\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "movw 0x1a8(%%esi), %%ax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "je .LFUN_00096a90_3\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl 0x5aa8c8, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ecx\n\t"
      "leal 0x1ac(%%esi), %%ebx\n\t"
      "flds 0x4(%%ecx)\n\t"
      "addl $8, %%esp\n\t"
      "fcomps (%%ebx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00096a90_1\n\t"
      "flds 0x1b0(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00096a90_3\n\t"
      ".LFUN_00096a90_1:\n\t"
      "movl (%%ebx), %%edx\n\t"
      "movl 0x278(%%edi), %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl 0x274(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x1b0(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c10f5b0]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00096a90_2\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_00096a90_2:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps (%%ebx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00096a90_3\n\t"
      "orl $4, 0x1a4(%%esi)\n\t"
      ".LFUN_00096a90_3:\n\t"
      "movw 0x1b4(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00096a90_15\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl 0x5aa8c8, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "leal 0x1b8(%%esi), %%ecx\n\t"
      "flds 0x4(%%eax)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "fcomps (%%ecx)\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00096a90_4\n\t"
      "flds 0x1bc(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00096a90_4\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "movw $0, 0x1c0(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00096a90_4:\n\t"
      "flds 0x2533c8\n\t"
      "leal 0x1bc(%%esi), %%ebx\n\t"
      "fsubs 0x1ac(%%esi)\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x27c(%%edi)\n\t"
      "flds 0x284(%%edi)\n\t"
      "fmuls 0x1ac(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fmuls 0x280(%%edi)\n\t"
      "flds 0x288(%%edi)\n\t"
      "fmuls 0x1ac(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds (%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00096a90_5\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      ".LFUN_00096a90_5:\n\t"
      "movw 0x1c0(%%esi), %%dx\n\t"
      "movswl %%dx, %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "fcomps 0x28c(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_00096a90_6\n\t"
      "flds (%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00096a90_6\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "flds 0x4(%%eax)\n\t"
      "fcomps (%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00096a90_6\n\t"
      "leal 0x1(%%edx), %%eax\n\t"
      "cmpw $1, %%ax\n\t"
      "movw %%ax, 0x1c0(%%esi)\n\t"
      "jne .LFUN_00096a90_15\n\t"
      "movl 0x218(%%edi), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c967a0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00096a90_6:\n\t"
      "flds (%%ebx)\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl (%%ecx), %%edx\n\t"
      "fabs\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "fcompp\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00096a90_8\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "flds -0x8(%%ebp)\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00096a90_7\n\t"
      "fchs\n\t"
      ".LFUN_00096a90_7:\n\t"
      "fstps (%%ebx)\n\t"
      ".LFUN_00096a90_8:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x17c(%%edi), %%al\n\t"
      "andl $0xffffff01, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10f5b0]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00096a90_10\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00096a90_9\n\t"
      "movl 0x1cc(%%edi), %%edi\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c967a0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_00096a90_14\n\t"
      ".LFUN_00096a90_9:\n\t"
      "movl 0x1dc(%%edi), %%edi\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c967a0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_00096a90_14\n\t"
      ".LFUN_00096a90_10:\n\t"
      "flds (%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00096a90_13\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls (%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00096a90_13\n\t"
      "flds (%%ebx)\n\t"
      "fcomps -0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00096a90_11\n\t"
      "movl 0x1ac(%%edi), %%edi\n\t"
      "jmp .LFUN_00096a90_12\n\t"
      ".LFUN_00096a90_11:\n\t"
      "movl 0x1bc(%%edi), %%edi\n\t"
      ".LFUN_00096a90_12:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c967a0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00096a90_13:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_00096a90_14:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fcomps 0x1b8(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00096a90_15\n\t"
      "orl $4, 0x1a4(%%esi)\n\t"
      ".LFUN_00096a90_15:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b96a90_get), [tag] "m"(b96a90_tag), [dget] "m"(b96a90_dget), [c10f5b0] "m"(b96a90_c10f5b0), [c967a0] "m"(b96a90_c967a0)
      : "memory");
}
#else
#error "FUN_00096a90: clang naked draft required"
#endif

