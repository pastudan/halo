#include <stdint.h>
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

/* cinematic_start (0x92e20) — readable C lift. */
void cinematic_start(void)
{
  player_input_enable(0);
  ai_globals_dialogue_triggers_enabled(0);
  *(unsigned char *)(*(unsigned char **)0x44df00 + 8) = 1;
  *(unsigned int *)(*(unsigned char **)0x44df00 + 4) = (unsigned int)game_time_get();
  *(unsigned char *)(*(unsigned char **)0x44df00 + 9) = 1;
  projectiles_delete_all();
}
void cinematic_skip_start(void) {
  uint8_t *base = *(uint8_t **)0x44df00;
  *(uint8_t *)(base + 0xa) = (uint8_t)1;
}



void cinematic_skip_stop(void) {
  uint8_t *base = *(uint8_t **)0x44df00;
  *(uint8_t *)(base + 0xa) = (uint8_t)0;
}



/* cinematic_show_letterbox (0x92e90) — readable C lift. */
void cinematic_show_letterbox(int a0)
{
  void *p = *(void **)0x44df00;
  *((char *)p + 8) = (char)a0;
  if (a0)
    *(int *)((char *)p + 4) = game_time_get();
}

/* draw_quad (0x92ec0) — XBE naked draft (batch 271). */
#if defined(__clang__)
static scenario_t * (*const b92ec0_c18e380)(void) = global_scenario_get;
static void * (*const b92ec0_c18e450)(void) = game_globals_get;
static void *(*const b92ec0_elem)(void *, int, int) = tag_block_get_element;
static void *(*const b92ec0_tag)(int, int) = tag_get;
static void *(*const b92ec0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b92ec0_c17cfa0)(void *render_data, void *vertices) = rasterizer_sprites_render;

__attribute__((naked, noinline))
void draw_quad(int16_t *rect __attribute__((unused)), int color __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x100, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c18e380]\n\t"
      "call *%[c18e450]\n\t"
      "movl 0x134(%%eax), %%ecx\n\t"
      "addl $0x134, %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "je .Ldraw_quad_1\n\t"
      "pushl $0x1ac\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Ldraw_quad_2\n\t"
      ".Ldraw_quad_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Ldraw_quad_2:\n\t"
      "movl 0xb8(%%eax), %%eax\n\t"
      "pushl $0x30\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6269746d\n\t"
      "call *%[tag]\n\t"
      "addl $0x60, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movw $8, 0x325652\n\t"
      "movswl 0x2(%%eax), %%ecx\n\t"
      "movswl (%%eax), %%edx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "movswl 0x6(%%eax), %%ecx\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "movswl 0x4(%%eax), %%edx\n\t"
      "fsts -0x24(%%ebp)\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fsts -0x20(%%ebp)\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "leal -0xf8(%%ebp), %%eax\n\t"
      "movl $4, %%edx\n\t"
      "fsts -0x1c(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "fsts -0x10(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".Ldraw_quad_3:\n\t"
      "movl (%%ecx), %%edi\n\t"
      "movl %%edi, -0x8(%%eax)\n\t"
      "movl 0x4(%%ecx), %%edi\n\t"
      "movl %%esi, 0x8(%%eax)\n\t"
      "movl %%ebx, (%%eax)\n\t"
      "movl %%ebx, 0x4(%%eax)\n\t"
      "movl %%edi, -0x4(%%eax)\n\t"
      "addl $8, %%ecx\n\t"
      "addl $0x14, %%eax\n\t"
      "decl %%edx\n\t"
      "jne .Ldraw_quad_3\n\t"
      "pushl $0x8c\n\t"
      "leal -0xb0(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "leal -0x100(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xb0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movw %%bx, -0x28(%%ebp)\n\t"
      "movl $0x3f800000, -0x6c(%%ebp)\n\t"
      "movl $0x3f800000, -0x70(%%ebp)\n\t"
      "movl $0x3f800000, -0x84(%%ebp)\n\t"
      "movl $0x3f800000, -0x88(%%ebp)\n\t"
      "movl %%ebx, -0xb0(%%ebp)\n\t"
      "movb %%bl, -0x26(%%ebp)\n\t"
      "movl %%ecx, -0xa4(%%ebp)\n\t"
      "call *%[c17cfa0]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%bx, 0x325652\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(b92ec0_c18e380), [c18e450] "m"(b92ec0_c18e450), [elem] "m"(b92ec0_elem), [tag] "m"(b92ec0_tag), [memset] "m"(b92ec0_memset), [c17cfa0] "m"(b92ec0_c17cfa0)
      : "memory");
}
#else
#error "draw_quad: clang naked draft required"
#endif


/* cinematic_force_title (0x93010) — readable C lift. */
void cinematic_force_title(short title)
{
  uint8_t *base = *(uint8_t **)0x44df00;
  *(uint16_t *)(base + 0xc) = (uint16_t)title;
  *(uint16_t *)(*(uint8_t **)0x44df00 + 0xe) = 0;
}

/* cinematic_suppress_bsp_object_creation (0x93030) — readable C lift. */
void cinematic_suppress_bsp_object_creation(char suppress)
{
  char *g = *(char **)0x44df00;
  g[0xb] = suppress;
}

/* cinematic_set_title_delayed (0x930b0) — XBE naked draft (batch 273). */
#if defined(__clang__)
static scenario_t * (*const b930b0_c18e380)(void) = global_scenario_get;
static void *(*const b930b0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b930b0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void cinematic_set_title_delayed(int a0 __attribute__((unused)), float a1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x44df00, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "orl $0xffffffff, %%edx\n\t"
      "pushl %%esi\n\t"
      ".Lcinematic_set_title_delayed_1:\n\t"
      "movswl %%ax, %%esi\n\t"
      "cmpw %%dx, 0xc(%%ecx,%%esi,4)\n\t"
      "je .Lcinematic_set_title_delayed_3\n\t"
      "incl %%eax\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .Lcinematic_set_title_delayed_1\n\t"
      ".Lcinematic_set_title_delayed_2:\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x60\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x4fc, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x268e9c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcinematic_set_title_delayed_3:\n\t"
      "cmpw $4, %%ax\n\t"
      "jge .Lcinematic_set_title_delayed_2\n\t"
      "flds 0xc(%%ebp)\n\t"
      "movw 0x8(%%ebp), %%dx\n\t"
      "fmuls 0x253394\n\t"
      "movswl %%ax, %%eax\n\t"
      "movw %%dx, 0xc(%%ecx,%%eax,4)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fistps -0x8(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x44df00, %%edx\n\t"
      "negl %%ecx\n\t"
      "movw %%cx, 0xe(%%edx,%%eax,4)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(b930b0_c18e380), [elem] "m"(b930b0_elem), [c8f390] "m"(b930b0_c8f390)
      : "memory");
}
#else
#error "cinematic_set_title_delayed: clang naked draft required"
#endif


/* cinematic_render (0x93140) — XBE naked draft (batch 249). */
#if defined(__clang__)
static char (*const b93140_ce3d70)(void) = (void *)ui_widgets_active;
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


/* FUN_00093640 (0x93640) — readable C lift. */
void FUN_00093640(int title)
{
  cinematic_set_title_delayed(title, 0);
}

/* FUN_00093660 (0x93660) — readable C lift. */
void FUN_00093660(void *a, void *b, void *c)
{
  unsigned char t = *((unsigned char *)a + 0x20);
  if (t >= 1 && t <= 3) {
    unsigned int v = *((unsigned char *)a + 0x22);
    FUN_00094ba0(b, c, (int)v);
    return;
  }
  if (t == 4) {
    unsigned int v = *((unsigned char *)a + 0x22);
    FUN_00094290(b, c, (int)v);
  }
}
/* FUN_00093710 (0x93710) — XBE naked draft (batch 266). */
#if defined(__clang__)
static void (*const b93710_c118be0)(void *definition, void *data, int count) = FUN_00118be0;

__attribute__((naked, noinline))
void FUN_00093710(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      ".LFUN_00093710_1:\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "cmpb $1, %%al\n\t"
      "movzbl %%al, %%ecx\n\t"
      "ja .LFUN_00093710_2\n\t"
      "movl $1, %%ecx\n\t"
      ".LFUN_00093710_2:\n\t"
      "movswl -0x4(%%ebp), %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .LFUN_00093710_5\n\t"
      "movl 0x2ee950(,%%eax,4), %%esi\n\t"
      "cmpl %%ebx, 0x4(%%esi)\n\t"
      "je .LFUN_00093710_4\n\t"
      ".LFUN_00093710_3:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c118be0]\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl (%%edi), %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "addl $0xc, %%esi\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jne .LFUN_00093710_3\n\t"
      ".LFUN_00093710_4:\n\t"
      "incl -0x4(%%ebp)\n\t"
      "jmp .LFUN_00093710_1\n\t"
      ".LFUN_00093710_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c118be0] "m"(b93710_c118be0)
      : "memory");
}
#else
#error "FUN_00093710: clang naked draft required"
#endif


/* FUN_00093780 (0x93780) — XBE naked draft (batch 265). */
#if defined(__clang__)
static void *(*const b93780_memset)(void *, int, unsigned int) = csmemset;
static void * (*const b93780_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;

__attribute__((naked, noinline))
void FUN_00093780(int a __attribute__((unused)), int *cursor __attribute__((unused)), int c __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x40\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[memset]\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "movw $0xffff, 0x8(%%ebx)\n\t"
      "movl $0, 0x8(%%ebp)\n\t"
      ".LFUN_00093780_1:\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "cmpb $1, %%al\n\t"
      "movzbl %%al, %%ecx\n\t"
      "ja .LFUN_00093780_2\n\t"
      "movl $1, %%ecx\n\t"
      ".LFUN_00093780_2:\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .LFUN_00093780_6\n\t"
      "movl 0x2ee950(,%%eax,4), %%eax\n\t"
      "leal 0x4(%%eax), %%esi\n\t"
      "cmpl $-1, (%%esi)\n\t"
      "je .LFUN_00093780_5\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00093780_3:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00093780_4\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl (%%edi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "addl %%ebx, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00093780_4:\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl (%%edi), %%edx\n\t"
      "addl %%eax, %%edx\n\t"
      "addl $0xc, %%esi\n\t"
      "movl %%edx, (%%edi)\n\t"
      "cmpl $-1, (%%esi)\n\t"
      "jne .LFUN_00093780_3\n\t"
      ".LFUN_00093780_5:\n\t"
      "incl 0x8(%%ebp)\n\t"
      "jmp .LFUN_00093780_1\n\t"
      ".LFUN_00093780_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [memset] "m"(b93780_memset), [c8e0b0] "m"(b93780_c8e0b0)
      : "memory");
}
#else
#error "FUN_00093780: clang naked draft required"
#endif


/* FUN_00093810 (0x93810) — XBE naked draft (batch 264). */
#if defined(__clang__)
static void * (*const b93810_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;

__attribute__((naked, noinline))
void FUN_00093810(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      ".LFUN_00093810_1:\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "cmpb $1, %%al\n\t"
      "movzbl %%al, %%ecx\n\t"
      "ja .LFUN_00093810_2\n\t"
      "movl $1, %%ecx\n\t"
      ".LFUN_00093810_2:\n\t"
      "movswl -0x4(%%ebp), %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .LFUN_00093810_5\n\t"
      "movl 0x2ee950(,%%eax,4), %%eax\n\t"
      "leal 0x4(%%eax), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00093810_4\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00093810_3:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "addl %%ebx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8e0b0]\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl (%%edi), %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "addl $0xc, %%esi\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_00093810_3\n\t"
      ".LFUN_00093810_4:\n\t"
      "incl -0x4(%%ebp)\n\t"
      "jmp .LFUN_00093810_1\n\t"
      ".LFUN_00093810_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8e0b0] "m"(b93810_c8e0b0)
      : "memory");
}
#else
#error "FUN_00093810: clang naked draft required"
#endif


/* FUN_00093880 (0x93880) — readable C lift. */
void FUN_00093880(void *unused, void *dest, unsigned char *typeinfo, unsigned char **cursor)
{
  extern char DAT_002690a0[];
  extern char DAT_002690a8[];
  extern char DAT_00265d1c[];
  extern char DAT_0026906c[];
  (void)unused;
  if (!dest) {
    display_assert(DAT_002690a0, DAT_002690a8, 25, 1);
    system_exit(-1);
  }
  if (!typeinfo) {
    display_assert(DAT_00265d1c, DAT_002690a8, 25, 1);
    system_exit(-1);
  }
  if ((typeinfo[0] & 0xfc) != 8) {
    display_assert(DAT_0026906c, DAT_002690a8, 25, 1);
    system_exit(-1);
  }
  *(unsigned char *)((char *)dest + 0) = **cursor;
  *cursor += 1;
}



/* FUN_00093910 (0x93910) — readable C lift. */
void FUN_00093910(void *unused, void *dest, unsigned char *typeinfo, unsigned char **cursor)
{
  extern char DAT_002690a0[];
  extern char DAT_002690a8[];
  extern char DAT_00265d1c[];
  extern char DAT_002690e0[];
  (void)unused;
  if (!dest) {
    display_assert(DAT_002690a0, DAT_002690a8, 26, 1);
    system_exit(-1);
  }
  if (!typeinfo) {
    display_assert(DAT_00265d1c, DAT_002690a8, 26, 1);
    system_exit(-1);
  }
  if ((typeinfo[0] & 0xfc) != 12) {
    display_assert(DAT_002690e0, DAT_002690a8, 26, 1);
    system_exit(-1);
  }
  *(unsigned char *)((char *)dest + 1) = **cursor;
  *cursor += 1;
}



/* FUN_000939a0 (0x939a0) — readable C lift. */
void FUN_000939a0(void *unused, void *dest, unsigned char *typeinfo, unsigned char **cursor)
{
  extern char DAT_002690a0[];
  extern char DAT_002690a8[];
  extern char DAT_00265d1c[];
  extern char DAT_00269110[];
  (void)unused;
  if (!dest) {
    display_assert(DAT_002690a0, DAT_002690a8, 27, 1);
    system_exit(-1);
  }
  if (!typeinfo) {
    display_assert(DAT_00265d1c, DAT_002690a8, 27, 1);
    system_exit(-1);
  }
  if ((typeinfo[0] & 0xfc) != 16) {
    display_assert(DAT_00269110, DAT_002690a8, 27, 1);
    system_exit(-1);
  }
  *(unsigned short *)((char *)dest + 2) = *(unsigned short *)*cursor;
  *cursor += 2;
}



/* FUN_00093a30 (0x93a30) — readable C lift. */
void FUN_00093a30(void *unused, void *dest, unsigned char *typeinfo, unsigned char **cursor)
{
  extern char DAT_002690a0[];
  extern char DAT_002690a8[];
  extern char DAT_00265d1c[];
  extern char DAT_00269140[];
  (void)unused;
  if (!dest) {
    display_assert(DAT_002690a0, DAT_002690a8, 28, 1);
    system_exit(-1);
  }
  if (!typeinfo) {
    display_assert(DAT_00265d1c, DAT_002690a8, 28, 1);
    system_exit(-1);
  }
  if ((typeinfo[0] & 0xfc) != 20) {
    display_assert(DAT_00269140, DAT_002690a8, 28, 1);
    system_exit(-1);
  }
  *(unsigned short *)((char *)dest + 4) = *(unsigned short *)*cursor;
  *cursor += 2;
}



/* FUN_00093ac0 (0x93ac0) — readable C lift. */
void FUN_00093ac0(void *unused, void *dest, unsigned char *typeinfo, unsigned char **cursor)
{
  extern char DAT_002690a0[];
  extern char DAT_002690a8[];
  extern char DAT_00265d1c[];
  extern char DAT_00269170[];
  (void)unused;
  if (!dest) {
    display_assert(DAT_002690a0, DAT_002690a8, 0x21, 1);
    system_exit(-1);
  }
  if (!typeinfo) {
    display_assert(DAT_00265d1c, DAT_002690a8, 0x23, 1);
    system_exit(-1);
  }
  if ((typeinfo[0] & 0xfc) != 0x18) {
    display_assert(DAT_00269170, DAT_002690a8, 0x24, 1);
    system_exit(-1);
  }
  *(int *)((char *)dest + 0xc) = *(int *)*cursor;
  *(int *)((char *)dest + 0x10) = *(int *)(*cursor + 4);
  *(int *)((char *)dest + 0x14) = 0;
  *cursor += 8;
}



/* FUN_00093b60 (0x93b60) — readable C lift. */
void FUN_00093b60(int16_t *dst, const int8_t *src)
{
  int v = (int16_t)(*dst + (int8_t)src[0]);
  if (v > 1000) {
    v -= 1000;
    *dst = (int16_t)v;
  } else if (v < -1000) {
    v += 1000;
    *dst = (int16_t)v;
  } else {
    *dst = (int16_t)v;
  }
  dst[1] = (int16_t)(dst[1] + (int8_t)src[1]);
}

/* FUN_00093ba0 (0x93ba0) — readable C lift. */
void FUN_00093ba0(int16_t *dst, const int16_t *src)
{
  int v = (int16_t)(*dst + *src);
  if (v > 1000) {
    v -= 1000;
    *dst = (int16_t)v;
  } else if (v < -1000) {
    v += 1000;
    *dst = (int16_t)v;
  } else {
    *dst = (int16_t)v;
  }
  dst[1] = (int16_t)(dst[1] + src[1]);
}

/* FUN_00093be0 (0x93be0) — readable C lift. */
void FUN_00093be0(float *out_vec, const int16_t *angles)
{
  float tmp[3];
  tmp[0] = (float)angles[0] * *(float *)0x26919c;
  tmp[1] = (float)angles[1] * *(float *)0x26919c;
  tmp[2] = 0.0f;
  angles_to_vector(out_vec, tmp);
}

/* FUN_00093c20 (0x93c20) — XBE naked draft (batch 245). */
#if defined(__clang__)
static void (*const b93c20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b93c20_exitfn)(int) = system_exit;
static void (*const b93c20_c10cc40)(float *out, float *angles) = angles_to_vector;
static void (*const b93c20_c93b60)(void) = (void (*)(void))FUN_00093b60;
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
static void (*const b93e20_c93ba0)(void) = (void (*)(void))FUN_00093ba0;
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

/* FUN_000936b0 (0x936b0) — readable C lift. */
short FUN_000936b0(void *scenario, void *entry)
{
  void *block;
  int count;
  short i;
  char *elem;

  block = (char *)scenario + 0x36c;
  count = *(int *)block;
  if (count <= 0)
    return -1;
  for (i = 0; i < count; i++) {
    elem = (char *)tag_block_get_element(block, i, 0x40);
    if (crt_stricmp(elem, (const char *)entry) == 0)
      return i;
  }
  return -1;
}

