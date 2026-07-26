#include <stdint.h>
/* --- object_lights.obj batch drafts (2026-07-26) --- */

/* lights_initialize (0x1391e0) — XBE naked draft (batch 230). */
#if defined(__clang__)
static data_t * (*const b1391e0_c1bfe10)(char *name, __int16 maximum_count, __int16 size) = game_state_data_new;
static void * (*const b1391e0_c1bfbf0)(const char *name, const char *a2, int size) = game_state_malloc;
static void (*const b1391e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1391e0_exitfn)(int) = system_exit;
static void (*const b1391e0_c191500)(void **out, const char *name) = cluster_partition_globals_new;
static void (*const b1391e0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void lights_initialize(void)
{
  __asm__ volatile(
      "pushl $0x7c\n\t"
      "pushl $0x380\n\t"
      "pushl $0x29b444\n\t"
      "call *%[c1bfe10]\n\t"
      "pushl $4\n\t"
      "pushl $0\n\t"
      "pushl $0x29b434\n\t"
      "movl %%eax, 0x5a90bc\n\t"
      "call *%[c1bfbf0]\n\t"
      "movl %%eax, 0x46f074\n\t"
      "movl 0x5a90bc, %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Llights_initialize_1\n\t"
      "pushl $1\n\t"
      "pushl $0xc2\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b428\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Llights_initialize_1:\n\t"
      "movl 0x46f074, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Llights_initialize_2\n\t"
      "pushl $1\n\t"
      "pushl $0xc3\n\t"
      "pushl $0x29b324\n\t"
      "pushl $0x29b414\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Llights_initialize_2:\n\t"
      "movl 0x46f074, %%eax\n\t"
      "movb $1, (%%eax)\n\t"
      "movl 0x5a90bc, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Llights_initialize_3\n\t"
      "pushl $0x25b590\n\t"
      "pushl $0x5a90b0\n\t"
      "call *%[c191500]\n\t"
      "addl $8, %%esp\n\t"
      "ret\n\t"
      ".Llights_initialize_3:\n\t"
      "pushl $0x29b3e8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "ret\n\t"
      :
      : [c1bfe10] "m"(b1391e0_c1bfe10), [c1bfbf0] "m"(b1391e0_c1bfbf0), [assert] "m"(b1391e0_assert), [exitfn] "m"(b1391e0_exitfn), [c191500] "m"(b1391e0_c191500), [c8f390] "m"(b1391e0_c8f390)
      : "memory");
}
#else
#error "lights_initialize: clang naked draft required"
#endif


/* lights_dispose (0x1392a0) — readable C lift. */
void lights_dispose(void)
{
  cluster_partition_null_references((int *)0x5a90b0);
}

/* lights_initialize_for_new_map (0x1392b0) — readable C lift. */
void lights_initialize_for_new_map(void)
{
  data_delete_all(*(void **)0x5a90bc);
  **(unsigned char **)0x46f074 = 1;
  cluster_partition_clear((void *)0x5a90b0);
}



/* lights_dispose_from_old_map (0x1392e0) — readable C lift. */
void lights_dispose_from_old_map(void)
{
  data_make_invalid(*(void **)0x5a90bc);
  cluster_partition_dispose((void *)0x5a90b0);
}



/* 0x139300 — set the global lights-active flag (returns the stored value). */
char lights_enable(char active)
{
  **(char **)0x46f074 = active;
  return active;
}

/* light_delete (0x139310) — readable C lift. */
void light_delete(int light_handle)
{
  void *light;

  light = datum_get(*(data_t **)0x5a90bc, light_handle);
  cluster_partition_remove_object((void *)0x5a90b0, light_handle,
                                  (char *)light + 0x10);
  datum_delete(*(data_t **)0x5a90bc, light_handle);
}
/* FUN_00139350 (0x139350) — readable C lift: collect light clusters. */
int16_t FUN_00139350(int light_handle, int16_t *out_buffer, int16_t max_count)
{
  void *light;
  int state;
  int16_t count;
  int16_t cluster;

  light = datum_get(*(data_t **)0x5a90bc, light_handle);
  cluster = (int16_t)FUN_00191690((void *)0x5a90b0, &state,
                                  *(int *)((char *)light + 0x10));
  count = 0;
  if (max_count > 0) {
    while (cluster != (int16_t)0xffff && count < max_count) {
      out_buffer[count] = cluster;
      count = (int16_t)(count + 1);
      cluster = (int16_t)FUN_001916d0(0x5a90b0, &state);
    }
  }
  return count;
}


/* object_get_self_illumination (0x1393b0) — readable C lift. */
float object_get_self_illumination(int object_handle)
{
  char *obj;
  char *obj_tag;
  int count;
  int i;
  float sum;
  int light_handle;
  void *light_datum;

  obj = (char *)object_get_and_verify_type(object_handle, -1);
  obj_tag = (char *)tag_get(0x6f626a65, *(int *)obj); /* 'obje' */
  count = *(int *)(obj_tag + 0x140);
  sum = 0.0f;
  for (i = 0; i < count; i++) {
    if (obj[0xf4 + i] != 0)
      continue;
    light_handle = *(int *)(obj + 0xfc + i * 4);
    if (light_handle == -1)
      continue;
    light_datum = datum_get(*(void **)0x5a90bc, light_handle);
    sum += real_rgb_color_brightness((float *)((char *)light_datum + 0x14));
  }
  if (*(int *)(obj + 0xc8) != -1)
    sum += object_get_self_illumination(*(int *)(obj + 0xc8));
  if (*(int *)(obj + 0xc4) != -1)
    sum += object_get_self_illumination(*(int *)(obj + 0xc4));
  return sum;
}


__attribute__((unused)) __attribute__((unused))
static void light_sample_clamp_rgb(float *rgb)
{
  int i;

  for (i = 0; i < 3; i++) {
    float v = rgb[i] + *(float *)0x25496c;
    if (v > 1.0f)
      v = 1.0f;
    rgb[i] = v;
  }
}

/* FUN_00139480 (0x139480) — XBE naked draft (batch 235). */
#if defined(__clang__)
static char (*const b139480_c198cb0)(float *point, float *direction, float *out_point, int16_t *out_collection_index, int16_t *out_bsp_index) = (char (*)(float *, float *, float *, int16_t *, int16_t *))(void *)structure_test_vector;
static void * (*const b139480_c18e3c0)(void) = scenario_get;
static void *(*const b139480_elem)(void *, int, int) = tag_block_get_element;
static void *(*const b139480_tag)(int, int) = tag_get;
static void * (*const b139480_c1906b0)(void *shader, int shader_type) = FUN_001906b0;
static void * (*const b139480_c76ff0)(int tag_index, short bitmap_index) = FUN_00076ff0;
static int (*const b139480_c138ee0)(int hardware_format) = FUN_00138ee0;
static void *(*const b139480_xtex)(void *, bool, bool) = xbox_texture_cache_get_hardware_format;
static void (*const b139480_c138fd0)(int material, int lightmap, unsigned short *vertex_indices, float u, float v, float *out_rgb) = FUN_00138fd0;
static void (*const b139480_c1390d0)(int material, int bitmap_ref, uint16_t *indices, float bary_u, float bary_v, float *out_rgb) = FUN_001390d0;

__attribute__((naked, noinline))
void FUN_00139480(void *position __attribute__((unused)), void *tint_color __attribute__((unused)), void *out_color __attribute__((unused)), char use_lightmap __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x28, %%esp\n\t"
      "movl 0x2ee70c, %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movl 0x2ee70c, %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x29b204\n\t"
      "pushl %%edx\n\t"
      "call *%[c198cb0]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00139480_11\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c18e3c0]\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl -0x4(%%ebp), %%eax\n\t"
      "pushl $0x20\n\t"
      "pushl %%eax\n\t"
      "leal 0x104(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%esi, -0x14(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movswl -0x8(%%ebp), %%edx\n\t"
      "pushl $0x100\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "addl $0x14, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0xc(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x73686472\n\t"
      "call *%[tag]\n\t"
      "addl $0x20, %%esp\n\t"
      "cmpw $3, 0x24(%%eax)\n\t"
      "jne .LFUN_00139480_10\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[c1906b0]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00139480_10\n\t"
      "cmpl $-1, 0x94(%%edi)\n\t"
      "je .LFUN_00139480_10\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movswl (%%ecx), %%ecx\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .LFUN_00139480_10\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c76ff0]\n\t"
      "movl 0x94(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x6269746d\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movswl 0x10(%%ebx), %%eax\n\t"
      "cdq\n\t"
      "idivl 0x60(%%ecx)\n\t"
      "pushl %%edx\n\t"
      "movl 0x94(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c76ff0]\n\t"
      "addl $0x18, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "je .LFUN_00139480_6\n\t"
      "movb 0x14(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00139480_1\n\t"
      "pushl %%esi\n\t"
      "call *%[c138ee0]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00139480_2\n\t"
      ".LFUN_00139480_1:\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[xtex]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00139480_6\n\t"
      ".LFUN_00139480_2:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "pushl $6\n\t"
      "pushl %%eax\n\t"
      "addl $0xf8, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c138fd0]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "addl $0x24, %%esp\n\t"
      "fadds 0x25496c\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00139480_3\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_00139480_3:\n\t"
      "fstps (%%ecx)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fadds 0x25496c\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00139480_4\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_00139480_4:\n\t"
      "fstps 0x4(%%ecx)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fadds 0x25496c\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00139480_5\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_00139480_5:\n\t"
      "fstps 0x8(%%ecx)\n\t"
      ".LFUN_00139480_6:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00139480_10\n\t"
      "movb 0x14(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00139480_7\n\t"
      "pushl %%eax\n\t"
      "call *%[c138ee0]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00139480_8\n\t"
      ".LFUN_00139480_7:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[xtex]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00139480_10\n\t"
      ".LFUN_00139480_8:\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00139480_9\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "pushl $6\n\t"
      "pushl %%eax\n\t"
      "addl $0xf8, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      ".LFUN_00139480_9:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1390d0]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_00139480_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00139480_11:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c198cb0] "m"(b139480_c198cb0), [c18e3c0] "m"(b139480_c18e3c0), [elem] "m"(b139480_elem), [tag] "m"(b139480_tag), [c1906b0] "m"(b139480_c1906b0), [c76ff0] "m"(b139480_c76ff0), [c138ee0] "m"(b139480_c138ee0), [xtex] "m"(b139480_xtex), [c138fd0] "m"(b139480_c138fd0), [c1390d0] "m"(b139480_c1390d0)
      : "memory");
}
#else
#error "FUN_00139480: clang naked draft required"
#endif

