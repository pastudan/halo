/* --- devices.obj batch drafts (2026-07-26) --- */

/* 0x960c0 */
void device_new(void)
{
  object_get_and_verify_type(0, 896);
  tag_get('ived', 0);
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


/* 0x96310 */
void device_preprocess_node_orientations(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  object_get_and_verify_type(0, 896);
  tag_get('ived', 0);
  tag_get('rtna', 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 96);
  /* test esi, esi -> je 0x96465 */
  /* test eax, eax -> jle 0x9641c */
  /* cmp (int16_t)eax, 0xffff -> je 0x9641c */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  /* test (char)eax, 1 -> je 0x963be */
  /* test (char)eax, 1 -> je 0x963dd */
  FUN_001d9068();
  overlay_animation_apply(0, 0, 0);
  FUN_00122690((void *)(uintptr_t)ebx, 0.0f, (void *)(uintptr_t)ecx);
  /* relift: cmp dword ptr [esi + 0x54], 1 -> jle 0x96465 */
  /* cmp (int16_t)eax, 0xffff -> je 0x96465 */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  FUN_00122690((void *)(uintptr_t)eax, 0.0f, (void *)0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}

/* 0x96470 */
int device_get_position(int a0)
{
  int eax = 0;

  /* cmp eax, -1 -> je 0x96491 */
  object_get_and_verify_type(0, 896);
  return 0;

  (void)eax;
}

/* 0x964a0 */
int device_get_power(int a0)
{
  int eax = 0;

  /* cmp eax, -1 -> je 0x964c1 */
  object_get_and_verify_type(0, 896);
  return 0;

  (void)eax;
}

/* 0x964d0 */
void device_set_never_appears_locked(int a0, int a1)
{
  int eax = 0;

  /* cmp eax, -1 -> je 0x9650e */
  object_try_and_get_and_verify_type(0, 128);
  /* test eax, eax -> je 0x9650e */

  (void)eax;
}

/* 0x96510 */
void device_group_set_actual_value(int a0, float a1)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test (char)eax, 0x41 -> jne 0x96546 */
  datum_get((void *)(uintptr_t)ecx, 0);
  object_iterator_new((void *)(uintptr_t)eax, 896, 0);
  object_iterator_next((void *)(uintptr_t)ecx);
  /* cmp eax, edi -> je 0x965e5 */
  /* relift: cmp word ptr [eax + 0x1a8], (int16_t)esi -> jne 0x965b6 */
  /* relift: cmp word ptr [eax + 0x1b4], (int16_t)esi -> jne 0x965d4 */
  object_iterator_next((void *)(uintptr_t)edx);
  /* cmp eax, edi -> jne 0x96590 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x965f0 */
void device_one_sided_set(int a0, int a1)
{
  int eax = 0;

  object_try_and_get_and_verify_type(0, 128);
  /* test eax, eax -> je 0x96629 */

  (void)eax;
}

/* 0x96630 */
void device_operates_automatically_set(int a0, int a1)
{
  int eax = 0;

  object_try_and_get_and_verify_type(0, 128);
  /* test eax, eax -> je 0x96669 */

  (void)eax;
}

/* 0x96670 */
void device_group_change_only_once_more_set(int a0, int a1)
{
  int eax = 0;
  int ecx = 0;

  /* cmp eax, -1 -> je 0x966a3 */
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)ecx, (char)ecx -> je 0x9669b */

  (void)eax;
  (void)ecx;
}

/* 0x966b0 */
int device_group_get_value(int a0)
{
  int ecx = 0;

  datum_get((void *)(uintptr_t)ecx, 0);
  return 0;

  (void)ecx;
}

/* 0x966d0 */
void device_group_set_real(int device_group_handle, int unit_handle)
{
  object_get_and_verify_type(0, 896);
  FUN_000958f0(0);
  FUN_00095be0(0);
}

/* 0x96720 */
bool device_can_change_position(int object_handle)
{
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  object_get_and_verify_type(0, 896);
  /* cmp (int16_t)ecx, -1 -> je 0x9679a */
  datum_get((void *)(uintptr_t)edx, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)ecx, 2 -> je 0x96784 */
  /* relift: test byte ptr [edi + 0x1a4], 2 -> je 0x9678f */
  /* relift: cmp dword ptr [edx + 4], 0x3f800000 -> je 0x9679a */
  return 0;

  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x967a0 */
void FUN_000967a0(void *rec, int object)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;

  /* cmp ebx, -1 -> je 0x9683f */
  object_get_and_verify_type(0, 896);
  tag_get_group_tag(0);
  /* cmp eax, 0x65666665 -> je 0x9681e */
  /* cmp eax, 0x736e6421 -> je 0x967fb */
  display_assert((char *)0, (char *)0x00269ac4, 761, 0);
  system_exit(0);
  object_impulse_sound_new(0, 0, 0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0.0f);
  FUN_0009ec30(0, 0, 0, 0, 0.0f, 0.0f, 0, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
}

/* 0x96850 */
void device_effect_new(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  data_new_at_index((void *)(uintptr_t)eax);
  /* cmp (int16_t)esi, -1 -> je 0x96891 */
  datum_get((void *)(uintptr_t)edx, 0);
  display_assert((char *)0x00269af8, (char *)0x00269ac4, 785, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 0xffff -> je 0x968f2 */
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)ecx, 4 -> je 0x968f1 */
  datum_delete((void *)(uintptr_t)ecx, 0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* create_initial_device_groups (0x96900) — XBE naked draft (batch 260). */
#if defined(__clang__)
static scenario_t * (*const b96900_c18e380)(void) = global_scenario_get;
static void *(*const b96900_elem)(void *, int, int) = tag_block_get_element;
static int (*const b96900_c119610)(data_t *data) = data_new_at_index;
static void *(*const b96900_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b96900_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b96900_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void create_initial_device_groups(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "call *%[c18e380]\n\t"
      "leal 0x288(%%eax), %%ebx\n\t"
      "cmpl $0, (%%ebx)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jle .Lcreate_initial_device_groups_6\n\t"
      "pushl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "pushl %%edi\n\t"
      ".Lcreate_initial_device_groups_1:\n\t"
      "pushl $0x34\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movb 0x24(%%eax), %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "testb $1, %%cl\n\t"
      "je .Lcreate_initial_device_groups_2\n\t"
      "movl $1, %%esi\n\t"
      ".Lcreate_initial_device_groups_2:\n\t"
      "movl 0x5aa8c8, %%ecx\n\t"
      "movl 0x20(%%eax), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[c119610]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $-1, %%di\n\t"
      "je .Lcreate_initial_device_groups_3\n\t"
      "movl 0x5aa8c8, %%eax\n\t"
      "movswl %%di, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movw %%si, 0x2(%%eax)\n\t"
      "jmp .Lcreate_initial_device_groups_4\n\t"
      ".Lcreate_initial_device_groups_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x311\n\t"
      "pushl $0x269ac4\n\t"
      "pushl $0x269af8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lcreate_initial_device_groups_4:\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "cmpw %%si, %%di\n\t"
      "je .Lcreate_initial_device_groups_5\n\t"
      "pushl $1\n\t"
      "pushl $0x339\n\t"
      "pushl $0x269ac4\n\t"
      "pushl $0x269b14\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lcreate_initial_device_groups_5:\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "jl .Lcreate_initial_device_groups_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".Lcreate_initial_device_groups_6:\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(b96900_c18e380), [elem] "m"(b96900_elem), [c119610] "m"(b96900_c119610), [dget] "m"(b96900_dget), [assert] "m"(b96900_assert), [exitfn] "m"(b96900_exitfn)
      : "memory");
}
#else
#error "create_initial_device_groups: clang naked draft required"
#endif


/* 0x96a00 */
void device_delete(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  object_get_and_verify_type(0, 896);
  /* cmp (int16_t)eax, 0xffff -> je 0x96a50 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)ecx, 4 -> je 0x96a50 */
  datum_delete((void *)(uintptr_t)edx, 0);
  /* cmp (int16_t)eax, 0xffff -> je 0x96a87 */
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)ecx, 4 -> je 0x96a87 */
  datum_delete((void *)(uintptr_t)ecx, 0);

  (void)eax;
  (void)ecx;
  (void)edx;
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

