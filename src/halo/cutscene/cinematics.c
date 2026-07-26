void cinematic_initialize(void)
{
  cinematic_globals = (cinematic_globals_t *)game_state_malloc(
    "cinematic globals", 0, sizeof(cinematic_globals_t));
  assert_halt(cinematic_globals);
}

void cinematic_dispose(void)
{
}

void cinematic_initialize_for_new_map(void)
{
  csmemset(cinematic_globals, 0, sizeof(cinematic_globals_t));
  csmemset(cinematic_globals->unk_12, 0xFF, sizeof(cinematic_globals->unk_12));
}

void cinematic_dispose_from_old_map(void)
{
  cinematic_globals->unk_8 = false;
  cinematic_globals->in_progress = false;
}

bool cinematic_can_be_skipped(void)
{
  return cinematic_globals->can_be_skipped;
}

bool cinematic_in_progress(void)
{
  return cinematic_globals->in_progress;
}
/* --- cinematics.obj batch drafts (2026-07-26) --- */

/* 0x92e20 */
void cinematic_start(void)
{
  player_input_enable(0);
  ai_globals_dialogue_triggers_enabled(0);
  game_time_get();
}

/* 0x92e70 */
void cinematic_skip_start(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x92e80 */
void cinematic_skip_stop(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x92e90 */
void cinematic_show_letterbox(int a0)
{
  game_time_get();
}

/* 0x92ec0 */
void draw_quad(int16_t *rect, int color)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;

  global_scenario_get();
  game_globals_get();
  /* cmp ecx, ebx -> je 0x92ef8 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 428);
  tag_get(0x6269746d, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  csmemset((void *)(uintptr_t)eax, 0, 140);
  rasterizer_sprites_render((void *)(uintptr_t)eax, (void *)(uintptr_t)edx);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
}

/* 0x93010 */
void cinematic_force_title(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x93030 */
void cinematic_suppress_bsp_object_creation(int a0)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x93050 */
void cinematic_stop(void)
{
  int eax = 0;

  player_input_enable(0);
  ai_globals_dialogue_triggers_enabled(0);
  FUN_0017d950();
  /* test eax, eax -> je 0x9308f */
  csmemset((void *)(uintptr_t)eax, 0, 16);
  FUN_0017dec0(0);

  (void)eax;
}

/* 0x930b0 */
void cinematic_set_title_delayed(int a0, float a1)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* relift: cmp word ptr [ecx + esi*4 + 0xc], (int16_t)edx -> je 0x93102 */
  /* cmp (int16_t)eax, 4 -> jl 0x930c2 */
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  error(0, (char *)0x00268e9c);
  /* cmp (int16_t)eax, 4 -> jge 0x930d3 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* cinematic_render (0x93140) — XBE naked draft (batch 249). */
#if defined(__clang__)
static char (*const b93140_ce3d70)(void) = ui_widgets_active;
static int (*const b93140_gtime)(void) = game_time_get;
static void (*const b93140_c92ec0)(int16_t *rect, int color) = draw_quad;
static scenario_t * (*const b93140_c18e380)(void) = global_scenario_get;
static void *(*const b93140_elem)(void *, int, int) = tag_block_get_element;
static void *(*const b93140_tag)(int, int) = tag_get;
static bool (*const b93140_c977f0)(void) = game_in_editor;
static void (*const b93140_c7af20)(unsigned int color, float *dst) = pixel32_to_real_argb_color;
static void (*const b93140_c19b8b0)(int tag_index, int style, int justify, int flags, const void *color) = draw_string_set_font;
static void (*const b93140_c1836e0)(const void *color) = rasterizer_text_set_shadow_color;
static int (*const b93140_c19d420)(int param_1, int param_2) = FUN_0019d420;
static void (*const b93140_c184060)(void *screen_pos, short *bounds, const void *color, int flags, unsigned short *text) = rasterizer_draw_string;
static bool (*const b93140_cb5c30)(void) = game_time_get_paused;
static int16_t (*const b93140_cb5ae0)(void) = game_time_get_elapsed;

__attribute__((naked, noinline))
void cinematic_render(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x38, %%esp\n\t"
      "movl 0x44df00, %%eax\n\t"
      "movb 0x8(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .Lcinematic_render_1\n\t"
      "flds (%%eax)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lcinematic_render_6\n\t"
      ".Lcinematic_render_1:\n\t"
      "call *%[ce3d70]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lcinematic_render_6\n\t"
      "call *%[gtime]\n\t"
      "movl 0x44df00, %%ecx\n\t"
      "movl 0x4(%%ecx), %%esi\n\t"
      "movl %%eax, %%edx\n\t"
      "subl %%esi, %%edx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x44df00, %%eax\n\t"
      "movb 0x8(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "fmuls 0x2546a4\n\t"
      "je .Lcinematic_render_2\n\t"
      "fadds (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      "movl 0x44df00, %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lcinematic_render_3\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Lcinematic_render_5\n\t"
      ".Lcinematic_render_2:\n\t"
      "fsubrs (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      "movl 0x44df00, %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lcinematic_render_4\n\t"
      ".Lcinematic_render_3:\n\t"
      "flds (%%ecx)\n\t"
      "jmp .Lcinematic_render_5\n\t"
      ".Lcinematic_render_4:\n\t"
      "flds 0x2533c0\n\t"
      ".Lcinematic_render_5:\n\t"
      "fstps (%%ecx)\n\t"
      "movl 0x44df00, %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lcinematic_render_6\n\t"
      "flds (%%ecx)\n\t"
      "movswl 0x50657c, %%eax\n\t"
      "fmuls 0x268ed0\n\t"
      "movswl 0x506580, %%ecx\n\t"
      "movswl 0x50657e, %%edx\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "subl %%eax, %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fistps -0xc(%%ebp)\n\t"
      "movswl 0x506582, %%ecx\n\t"
      "movw -0xc(%%ebp), %%ax\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movw %%ax, -0x26(%%ebp)\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fistps -0xc(%%ebp)\n\t"
      "movswl 0x50657c, %%eax\n\t"
      "movw -0xc(%%ebp), %%dx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movw %%dx, -0x22(%%ebp)\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fistps -0xc(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movswl 0x50657c, %%edx\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "movw -0xc(%%ebp), %%cx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movw %%cx, -0x28(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fistps -0xc(%%ebp)\n\t"
      "movw -0xc(%%ebp), %%ax\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl $0xff000000\n\t"
      "pushl %%ecx\n\t"
      "movw %%ax, -0x24(%%ebp)\n\t"
      "call *%[c92ec0]\n\t"
      "movswl 0x50657e, %%edx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fistps -0xc(%%ebp)\n\t"
      "movswl 0x506582, %%ecx\n\t"
      "movw -0xc(%%ebp), %%ax\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movw %%ax, -0x26(%%ebp)\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fistps -0xc(%%ebp)\n\t"
      "movswl 0x506580, %%eax\n\t"
      "movw -0xc(%%ebp), %%dx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movw %%dx, -0x22(%%ebp)\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fistps -0xc(%%ebp)\n\t"
      "movswl 0x506580, %%edx\n\t"
      "movw -0xc(%%ebp), %%cx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movw %%cx, -0x28(%%ebp)\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fistps -0xc(%%ebp)\n\t"
      "movw -0xc(%%ebp), %%ax\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl $0xff000000\n\t"
      "pushl %%ecx\n\t"
      "movw %%ax, -0x24(%%ebp)\n\t"
      "call *%[c92ec0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lcinematic_render_6:\n\t"
      "movl $0xc, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl $4, -0x10(%%ebp)\n\t"
      ".Lcinematic_render_7:\n\t"
      "movl 0x44df00, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movw (%%eax), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lcinematic_render_22\n\t"
      "movl 0x46bd0c, %%ecx\n\t"
      "movl 0x54(%%ecx), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "je .Lcinematic_render_22\n\t"
      "movswl %%ax, %%edx\n\t"
      "pushl $0x60\n\t"
      "pushl %%edx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x4fc, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c18e380]\n\t"
      "movl 0x590(%%eax), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lcinematic_render_22\n\t"
      "pushl %%edi\n\t"
      "pushl $0x75737472\n\t"
      "call *%[tag]\n\t"
      "movw 0x30(%%esi), %%cx\n\t"
      "addl $8, %%esp\n\t"
      "testw %%cx, %%cx\n\t"
      "jl .Lcinematic_render_22\n\t"
      "movl (%%eax), %%edx\n\t"
      "movswl %%cx, %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jge .Lcinematic_render_22\n\t"
      "movw 0x2e(%%esi), %%dx\n\t"
      "cmpw 0x2a(%%esi), %%dx\n\t"
      "leal 0x28(%%esi), %%ebx\n\t"
      "movl $0x3f800000, -0x4(%%ebp)\n\t"
      "je .Lcinematic_render_8\n\t"
      "movw 0x4(%%ebx), %%ax\n\t"
      "cmpw (%%ebx), %%ax\n\t"
      "jne .Lcinematic_render_9\n\t"
      ".Lcinematic_render_8:\n\t"
      "movl 0x46bd0c, %%ebx\n\t"
      "addl $0x2dc, %%ebx\n\t"
      ".Lcinematic_render_9:\n\t"
      "call *%[c977f0]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lcinematic_render_14\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movswl 0x2(%%ecx), %%edx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "fcoms 0x44(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lcinematic_render_10\n\t"
      "fdivs 0x44(%%esi)\n\t"
      "jmp .Lcinematic_render_11\n\t"
      ".Lcinematic_render_10:\n\t"
      "fcoms 0x48(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lcinematic_render_13\n\t"
      "fsubs 0x48(%%esi)\n\t"
      "fdivs 0x4c(%%esi)\n\t"
      "fsubrs 0x2533c8\n\t"
      ".Lcinematic_render_11:\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lcinematic_render_12\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jmp .Lcinematic_render_14\n\t"
      ".Lcinematic_render_12:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lcinematic_render_14\n\t"
      "movl $0x3f800000, -0x4(%%ebp)\n\t"
      "jmp .Lcinematic_render_14\n\t"
      ".Lcinematic_render_13:\n\t"
      "fstp %%st(0)\n\t"
      ".Lcinematic_render_14:\n\t"
      "movl 0x3c(%%esi), %%ecx\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7af20]\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fsubs 0x2533c8\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lcinematic_render_17\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fsubs 0x2533c8\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lcinematic_render_17\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fsubs 0x2533c8\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lcinematic_render_17\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fcomps 0x2533f0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lcinematic_render_15\n\t"
      "movl $0x3f4ccccd, -0x34(%%ebp)\n\t"
      ".Lcinematic_render_15:\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fcomps 0x2533f0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lcinematic_render_16\n\t"
      "movl $0x3f4ccccd, -0x30(%%ebp)\n\t"
      ".Lcinematic_render_16:\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fcomps 0x2533f0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lcinematic_render_17\n\t"
      "movl $0x3f4ccccd, -0x2c(%%ebp)\n\t"
      ".Lcinematic_render_17:\n\t"
      "movl 0x38(%%esi), %%eax\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x34(%%esi), %%cx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x32(%%esi), %%dx\n\t"
      "decw %%dx\n\t"
      "pushl %%eax\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b8b0]\n\t"
      "movzbl 0x43(%%esi), %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "addl $0x14, %%esp\n\t"
      "fildl -0x18(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fistps -0x1c(%%ebp)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .Lcinematic_render_18\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lcinematic_render_19\n\t"
      ".Lcinematic_render_18:\n\t"
      "movzbl 0x43(%%esi), %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "fildl -0x18(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fistps -0x20(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl $0xff, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jg .Lcinematic_render_19\n\t"
      "movzbl 0x43(%%esi), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "fildl -0x18(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fistps -0x24(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      ".Lcinematic_render_19:\n\t"
      "movl 0x40(%%esi), %%ecx\n\t"
      "shll $0x18, %%eax\n\t"
      "andl $0xffffff, %%ecx\n\t"
      "orl %%ecx, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1836e0]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x30(%%esi), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c19d420]\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[c184060]\n\t"
      "pushl $0\n\t"
      "call *%[c1836e0]\n\t"
      "addl $0x24, %%esp\n\t"
      "call *%[cb5c30]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lcinematic_render_20\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lcinematic_render_21\n\t"
      ".Lcinematic_render_20:\n\t"
      "call *%[cb5ae0]\n\t"
      "movswl %%ax, %%eax\n\t"
      ".Lcinematic_render_21:\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "addw %%ax, 0x2(%%edi)\n\t"
      "call *%[c977f0]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lcinematic_render_22\n\t"
      "movswl 0x2(%%edi), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "fildl -0x18(%%ebp)\n\t"
      "flds 0x4c(%%esi)\n\t"
      "fadds 0x48(%%esi)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lcinematic_render_22\n\t"
      "movw $0xffff, (%%edi)\n\t"
      "movw $0xffff, 0x2(%%edi)\n\t"
      ".Lcinematic_render_22:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "addl $4, %%eax\n\t"
      "decl %%ecx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "jne .Lcinematic_render_7\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [ce3d70] "m"(b93140_ce3d70), [gtime] "m"(b93140_gtime), [c92ec0] "m"(b93140_c92ec0), [c18e380] "m"(b93140_c18e380), [elem] "m"(b93140_elem), [tag] "m"(b93140_tag), [c977f0] "m"(b93140_c977f0), [c7af20] "m"(b93140_c7af20), [c19b8b0] "m"(b93140_c19b8b0), [c1836e0] "m"(b93140_c1836e0), [c19d420] "m"(b93140_c19d420), [c184060] "m"(b93140_c184060), [cb5c30] "m"(b93140_cb5c30), [cb5ae0] "m"(b93140_cb5ae0)
      : "memory");
}
#else
#error "cinematic_render: clang naked draft required"
#endif


/* 0x93640 */
void FUN_00093640(int a0)
{
  cinematic_set_title_delayed(0, 0.0f);
}

/* FUN_00093660 (0x93660) — XBE naked draft (batch 255). */
#if defined(__clang__)
static void (*const b93660_c94290)(void) = FUN_00094290;
static void (*const b93660_c94ba0)(void) = FUN_00094ba0;

__attribute__((naked, noinline))
void FUN_00093660(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movb 0x20(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jbe .LFUN_00093660_2\n\t"
      "cmpb $3, %%al\n\t"
      "jbe .LFUN_00093660_1\n\t"
      "cmpb $4, %%al\n\t"
      "jne .LFUN_00093660_2\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x22(%%ecx), %%al\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c94290]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00093660_1:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x22(%%ecx), %%al\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c94ba0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00093660_2:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c94290] "m"(b93660_c94290), [c94ba0] "m"(b93660_c94ba0)
      : "memory");
}
#else
#error "FUN_00093660: clang naked draft required"
#endif


/* 0x93710 */
void FUN_00093710(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  /* cmp eax, ecx -> jge 0x9376f */
  /* relift: cmp dword ptr [esi + 4], ebx -> je 0x9376a */
  FUN_00118be0((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, 0);
  /* cmp eax, ebx -> jne 0x93747 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}

/* 0x93780 */
void FUN_00093780(int a, int *cursor, int c)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  csmemset((void *)(uintptr_t)ebx, 0, 64);
  /* cmp eax, ecx -> jge 0x937fe */
  /* relift: cmp dword ptr [esi], -1 -> je 0x937f9 */
  /* cmp eax, -1 -> je 0x937e9 */
  csmemcpy((void *)(uintptr_t)eax, (void *)0, 0);
  /* relift: cmp dword ptr [esi], -1 -> jne 0x937d0 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}

/* 0x93810 */
void FUN_00093810(void)
{
  int eax = 0;
  int ecx = 0;

  /* cmp eax, ecx -> jge 0x93879 */
  /* cmp eax, -1 -> je 0x93874 */
  csmemcpy((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, 0);
  /* cmp eax, -1 -> jne 0x93850 */

  (void)eax;
  (void)ecx;
}

/* 0x93880 */
void FUN_00093880(void)
{
  int eax = 0;
  int ecx = 0;

  display_assert((char *)0x002690a0, (char *)0x002690a8, 25, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x938d3 */
  display_assert((char *)0x00265d1c, (char *)0x002690a8, 25, 0);
  system_exit(0);
  /* cmp (char)ecx, 8 -> je 0x938fd */
  display_assert((char *)0x0026906c, (char *)0x002690a8, 25, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
}

/* 0x93910 */
void FUN_00093910(void)
{
  int eax = 0;
  int ecx = 0;

  display_assert((char *)0x002690a0, (char *)0x002690a8, 26, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x93963 */
  display_assert((char *)0x00265d1c, (char *)0x002690a8, 26, 0);
  system_exit(0);
  /* cmp (char)ecx, 0xc -> je 0x9398d */
  display_assert((char *)0x002690e0, (char *)0x002690a8, 26, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
}

/* 0x939a0 */
void FUN_000939a0(void)
{
  int eax = 0;
  int ecx = 0;

  display_assert((char *)0x002690a0, (char *)0x002690a8, 27, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x939f3 */
  display_assert((char *)0x00265d1c, (char *)0x002690a8, 27, 0);
  system_exit(0);
  /* cmp (char)ecx, 0x10 -> je 0x93a1d */
  display_assert((char *)0x00269110, (char *)0x002690a8, 27, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
}

/* 0x93a30 */
void FUN_00093a30(void)
{
  int eax = 0;
  int ecx = 0;

  display_assert((char *)0x002690a0, (char *)0x002690a8, 28, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x93a83 */
  display_assert((char *)0x00265d1c, (char *)0x002690a8, 28, 0);
  system_exit(0);
  /* cmp (char)ecx, 0x14 -> je 0x93aad */
  display_assert((char *)0x00269140, (char *)0x002690a8, 28, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
}

/* 0x93ac0 */
void FUN_00093ac0(void)
{
  int eax = 0;
  int ecx = 0;

  display_assert((char *)0x002690a0, (char *)0x002690a8, 33, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x93b13 */
  display_assert((char *)0x00265d1c, (char *)0x002690a8, 35, 0);
  system_exit(0);
  /* cmp (char)ecx, 0x18 -> je 0x93b3d */
  display_assert((char *)0x00269170, (char *)0x002690a8, 36, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
}

/* FUN_00093b60 (0x93b60) — XBE naked draft (batch 252). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_00093b60(void)
{
  __asm__ volatile(
      "movsbw (%%edx), %%cx\n\t"
      "addw %%cx, (%%eax)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%eax), %%cx\n\t"
      "cmpw $0x3e8, %%cx\n\t"
      "jle .LFUN_00093b60_1\n\t"
      "addl $0xfffffc18, %%ecx\n\t"
      "movw %%cx, (%%eax)\n\t"
      "movsbw 0x1(%%edx), %%dx\n\t"
      "addw %%dx, 0x2(%%eax)\n\t"
      "ret\n\t"
      ".LFUN_00093b60_1:\n\t"
      "cmpw $0xfc18, %%cx\n\t"
      "jge .LFUN_00093b60_2\n\t"
      "addl $0x3e8, %%ecx\n\t"
      "movw %%cx, (%%eax)\n\t"
      ".LFUN_00093b60_2:\n\t"
      "movsbw 0x1(%%edx), %%dx\n\t"
      "addw %%dx, 0x2(%%eax)\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_00093b60: clang naked draft required"
#endif


/* FUN_00093ba0 (0x93ba0) — XBE naked draft (batch 252). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_00093ba0(void)
{
  __asm__ volatile(
      "movw (%%edx), %%cx\n\t"
      "addw %%cx, (%%eax)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%eax), %%cx\n\t"
      "cmpw $0x3e8, %%cx\n\t"
      "jle .LFUN_00093ba0_1\n\t"
      "addl $0xfffffc18, %%ecx\n\t"
      "movw %%cx, (%%eax)\n\t"
      "movw 0x2(%%edx), %%dx\n\t"
      "addw %%dx, 0x2(%%eax)\n\t"
      "ret\n\t"
      ".LFUN_00093ba0_1:\n\t"
      "cmpw $0xfc18, %%cx\n\t"
      "jge .LFUN_00093ba0_2\n\t"
      "addl $0x3e8, %%ecx\n\t"
      "movw %%cx, (%%eax)\n\t"
      ".LFUN_00093ba0_2:\n\t"
      "movw 0x2(%%edx), %%dx\n\t"
      "addw %%dx, 0x2(%%eax)\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_00093ba0: clang naked draft required"
#endif


/* 0x93be0 */
void FUN_00093be0(void)
{
  angles_to_vector((void *)0, (void *)0);
}

/* FUN_00093c20 (0x93c20) — XBE naked draft (batch 245). */
#if defined(__clang__)
static void (*const b93c20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b93c20_exitfn)(int) = system_exit;
static void (*const b93c20_c10cc40)(float *out, float *angles) = angles_to_vector;
static void (*const b93c20_c93b60)(void) = FUN_00093b60;
static void (*const b93c20_c93be0)(void) = FUN_00093be0;

__attribute__((naked, noinline))
void FUN_00093c20(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jne .LFUN_00093c20_1\n\t"
      "pushl $1\n\t"
      "pushl $0x64\n\t"
      "pushl $0x2690a8\n\t"
      "pushl $0x2690a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00093c20_1:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00093c20_2\n\t"
      "pushl $1\n\t"
      "pushl $0x66\n\t"
      "pushl $0x2690a8\n\t"
      "pushl $0x265d1c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00093c20_2:\n\t"
      "movb (%%esi), %%al\n\t"
      "movb %%al, %%dl\n\t"
      "andb $0xfc, %%dl\n\t"
      "cmpb $0x1c, %%dl\n\t"
      "jb .LFUN_00093c20_3\n\t"
      "movzbl %%al, %%eax\n\t"
      "shrl $2, %%eax\n\t"
      "subl $7, %%eax\n\t"
      "cmpl $8, %%eax\n\t"
      "jl .LFUN_00093c20_4\n\t"
      ".LFUN_00093c20_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x67\n\t"
      "pushl $0x2690a8\n\t"
      "pushl $0x2691a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00093c20_4:\n\t"
      "movb (%%esi), %%cl\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "shrb $2, %%cl\n\t"
      "pushl %%ebx\n\t"
      "movzbw %%cl, %%bx\n\t"
      "subl $7, %%ebx\n\t"
      "movl %%ebx, %%eax\n\t"
      "andl $1, %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "je .LFUN_00093c20_8\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movsbw (%%ecx), %%dx\n\t"
      "addw %%dx, (%%esi)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%esi), %%ax\n\t"
      "cmpw $0x3e8, %%ax\n\t"
      "jle .LFUN_00093c20_5\n\t"
      "addl $0xfffffc18, %%eax\n\t"
      "jmp .LFUN_00093c20_6\n\t"
      ".LFUN_00093c20_5:\n\t"
      "cmpw $0xfc18, %%ax\n\t"
      "jge .LFUN_00093c20_7\n\t"
      "addl $0x3e8, %%eax\n\t"
      ".LFUN_00093c20_6:\n\t"
      "movw %%ax, (%%esi)\n\t"
      ".LFUN_00093c20_7:\n\t"
      "movsbw 0x1(%%ecx), %%ax\n\t"
      "movswl (%%esi), %%ecx\n\t"
      "addw %%ax, 0x2(%%esi)\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "movswl %%ax, %%edx\n\t"
      "fildl 0x10(%%ebp)\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "fmuls 0x26919c\n\t"
      "pushl %%eax\n\t"
      "leal 0x1c(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fildl 0x10(%%ebp)\n\t"
      "fmuls 0x26919c\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "call *%[c10cc40]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00093c20_8:\n\t"
      "movl %%ebx, %%ecx\n\t"
      "andl $2, %%ecx\n\t"
      "testw %%cx, %%cx\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "je .LFUN_00093c20_11\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_00093c20_9\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "leal 0x1c(%%edi), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0x28(%%edi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "jmp .LFUN_00093c20_10\n\t"
      ".LFUN_00093c20_9:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "call *%[c93b60]\n\t"
      "leal 0x28(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c93be0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00093c20_10:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      ".LFUN_00093c20_11:\n\t"
      "testb $4, %%bl\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_00093c20_14\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_00093c20_12\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl %%edx, 0x8(%%esi)\n\t"
      "leal 0x1c(%%edi), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "addl $0x34, %%edi\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "movl %%edx, 0x4(%%edi)\n\t"
      "movl %%eax, 0x8(%%edi)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "addl $2, %%ecx\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00093c20_12:\n\t"
      "testw %%cx, %%cx\n\t"
      "je .LFUN_00093c20_13\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x8(%%esi)\n\t"
      "leal 0x28(%%edi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "addl $0x34, %%edi\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x4(%%edi)\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "addl $2, %%ecx\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00093c20_13:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "leal 0x8(%%esi), %%eax\n\t"
      "call *%[c93b60]\n\t"
      "addl $0x34, %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c93be0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00093c20_14:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "addl $2, %%ecx\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b93c20_assert), [exitfn] "m"(b93c20_exitfn), [c10cc40] "m"(b93c20_c10cc40), [c93b60] "m"(b93c20_c93b60), [c93be0] "m"(b93c20_c93be0)
      : "memory");
}
#else
#error "FUN_00093c20: clang naked draft required"
#endif


/* FUN_00093e20 (0x93e20) — XBE naked draft (batch 245). */
#if defined(__clang__)
static void (*const b93e20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b93e20_exitfn)(int) = system_exit;
static void (*const b93e20_c10cc40)(float *out, float *angles) = angles_to_vector;
static void (*const b93e20_c93ba0)(void) = FUN_00093ba0;
static void (*const b93e20_c93be0)(void) = FUN_00093be0;

__attribute__((naked, noinline))
void FUN_00093e20(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jne .LFUN_00093e20_1\n\t"
      "pushl $1\n\t"
      "pushl $0xa0\n\t"
      "pushl $0x2690a8\n\t"
      "pushl $0x2690a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00093e20_1:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00093e20_2\n\t"
      "pushl $1\n\t"
      "pushl $0xa2\n\t"
      "pushl $0x2690a8\n\t"
      "pushl $0x265d1c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00093e20_2:\n\t"
      "movb (%%esi), %%al\n\t"
      "movb %%al, %%dl\n\t"
      "andb $0xfc, %%dl\n\t"
      "cmpb $0x3c, %%dl\n\t"
      "jb .LFUN_00093e20_3\n\t"
      "movzbl %%al, %%eax\n\t"
      "shrl $2, %%eax\n\t"
      "subl $0xf, %%eax\n\t"
      "cmpl $8, %%eax\n\t"
      "jl .LFUN_00093e20_4\n\t"
      ".LFUN_00093e20_3:\n\t"
      "pushl $1\n\t"
      "pushl $0xa3\n\t"
      "pushl $0x2690a8\n\t"
      "pushl $0x269238\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00093e20_4:\n\t"
      "movb (%%esi), %%cl\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "shrb $2, %%cl\n\t"
      "pushl %%ebx\n\t"
      "movzbw %%cl, %%bx\n\t"
      "subl $0xf, %%ebx\n\t"
      "movl %%ebx, %%eax\n\t"
      "andl $1, %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "je .LFUN_00093e20_8\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movw (%%ecx), %%dx\n\t"
      "addw %%dx, (%%esi)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%esi), %%ax\n\t"
      "cmpw $0x3e8, %%ax\n\t"
      "jle .LFUN_00093e20_5\n\t"
      "addl $0xfffffc18, %%eax\n\t"
      "jmp .LFUN_00093e20_6\n\t"
      ".LFUN_00093e20_5:\n\t"
      "cmpw $0xfc18, %%ax\n\t"
      "jge .LFUN_00093e20_7\n\t"
      "addl $0x3e8, %%eax\n\t"
      ".LFUN_00093e20_6:\n\t"
      "movw %%ax, (%%esi)\n\t"
      ".LFUN_00093e20_7:\n\t"
      "movw 0x2(%%ecx), %%ax\n\t"
      "movswl (%%esi), %%ecx\n\t"
      "addw %%ax, 0x2(%%esi)\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "movswl %%ax, %%edx\n\t"
      "fildl 0x10(%%ebp)\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "fmuls 0x26919c\n\t"
      "pushl %%eax\n\t"
      "leal 0x1c(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fildl 0x10(%%ebp)\n\t"
      "fmuls 0x26919c\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "call *%[c10cc40]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00093e20_8:\n\t"
      "movl %%ebx, %%ecx\n\t"
      "andl $2, %%ecx\n\t"
      "testw %%cx, %%cx\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "je .LFUN_00093e20_11\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_00093e20_9\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "leal 0x1c(%%edi), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0x28(%%edi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "jmp .LFUN_00093e20_10\n\t"
      ".LFUN_00093e20_9:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "call *%[c93ba0]\n\t"
      "leal 0x28(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c93be0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00093e20_10:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      ".LFUN_00093e20_11:\n\t"
      "testb $4, %%bl\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_00093e20_14\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_00093e20_12\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl %%edx, 0x8(%%esi)\n\t"
      "leal 0x1c(%%edi), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "addl $0x34, %%edi\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "movl %%edx, 0x4(%%edi)\n\t"
      "movl %%eax, 0x8(%%edi)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "addl $4, %%ecx\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00093e20_12:\n\t"
      "testw %%cx, %%cx\n\t"
      "je .LFUN_00093e20_13\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x8(%%esi)\n\t"
      "leal 0x28(%%edi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "addl $0x34, %%edi\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x4(%%edi)\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "addl $4, %%ecx\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00093e20_13:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "leal 0x8(%%esi), %%eax\n\t"
      "call *%[c93ba0]\n\t"
      "addl $0x34, %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c93be0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00093e20_14:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "addl $4, %%ecx\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b93e20_assert), [exitfn] "m"(b93e20_exitfn), [c10cc40] "m"(b93e20_c10cc40), [c93ba0] "m"(b93e20_c93ba0), [c93be0] "m"(b93e20_c93be0)
      : "memory");
}
#else
#error "FUN_00093e20: clang naked draft required"
#endif

/* --- cinematics.obj orphan shells (2026-07-26) --- */

/* 0x936b0 */
short FUN_000936b0(void *scenario, void *entry)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  /* test ecx, ecx -> jle 0x936ff */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 64);
  crt_stricmp((char *)(uintptr_t)eax, (char *)(uintptr_t)ebx);
  /* test eax, eax -> je 0x936fc */
  /* cmp eax, ecx -> jl 0x936d3 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}
