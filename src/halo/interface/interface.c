#include <stdint.h>
/* UI/HUD interface subsystem init/dispose. */

void interface_initialize(void)
{
  ((void (*)(void))0xe33a0)();
  hud_new();
  ((void (*)(void))0x19b320)();
  ((void (*)(void))0xdc750)();
}

void interface_dispose_from_old_map(void)
{
  ((void (*)(void))0x19b3a0)();
  hud_dispose_from_old_map();
}

void interface_dispose(void)
{
  ((void (*)(void))0x19b3b0)();
  ((void (*)(void))0xe33e0)();
  hud_dispose();
}

#define NUMBER_OF_INTERFACE_TAGS 16

/* Look up a tag_index from the interface globals tag block.
 * The interface globals element (size 0x130) contains an array of 16
 * tag_reference entries (each 0x10 bytes) starting at offset 0x0.
 * The tag_index field is at offset 0xc within each tag_reference.
 * Returns the tag_index for the given interface_tag_index slot. */
int interface_get_tag_index(int interface_tag_index)
{
  char *globals;
  char *element;

  assert_halt(interface_tag_index >= 0 &&
              interface_tag_index < NUMBER_OF_INTERFACE_TAGS);

  globals = (char *)game_globals_get();
  if (*(int *)(globals + 0x140) != 0) {
    globals = (char *)game_globals_get();
    element = (char *)tag_block_get_element(globals + 0x140, 0, 0x130);
    return *(int *)(element + interface_tag_index * 0x10 + 0xc);
  }

  return *(int *)((char *)0 + interface_tag_index * 0x10 + 0xc);
}

/* Look up an ARGB float color from a color_table ('colo') tag.
 * Uses interface_get_tag_index to resolve the color tag, then
 * indexes into the color table block (element size 0x30).
 * Color data is 4 floats (ARGB) at offset 0x20 within each entry.
 * The color_index is taken modulo the block count (as a short).
 * Returns out_color. */
void *interface_get_color(int interface_tag_index, short color_index,
                          void *out_color)
{
  int tag_idx;
  int *color_tag;
  int count;
  char *entry;
  float *out = (float *)out_color;

  tag_idx = interface_get_tag_index(interface_tag_index);

  out[3] = 1.0f;
  out[2] = 1.0f;
  out[1] = 1.0f;
  out[0] = 1.0f;

  if (tag_idx != -1) {
    color_tag = (int *)tag_get(0x636f6c6f, tag_idx);
    count = *color_tag;
    if (count != 0) {
      entry = (char *)tag_block_get_element(color_tag,
                                            (short)(color_index % count), 0x30);
      out[0] = *(float *)(entry + 0x20);
      out[1] = *(float *)(entry + 0x24);
      out[2] = *(float *)(entry + 0x28);
      out[3] = *(float *)(entry + 0x2c);
    }
  }

  return out_color;
}

/* Set up font, color, and style for drawing interface text.
 * Resolves font_index to a tag_index, looks up an ARGB color from the
 * interface color table (indexed by color_tag_index / color_index), then
 * configures the draw_string subsystem with those parameters. */
void interface_draw_text(int font_index, int style, int justify, int flags,
                         int color_tag_index, short color_index)
{
  float color[4];
  int tag_index;

  tag_index = interface_get_tag_index(font_index);
  interface_get_color(color_tag_index, color_index, color);
  draw_string_set_font(tag_index, style, justify, flags, color);
}

/* interface_draw_splitscreen_dividers (0xdfdc0) — readable C lift. */
void interface_draw_splitscreen_dividers(void)
{
  int16_t rect[4];
  int16_t nplayers;

  if (game_engine_force_single_screen())
    return;
  if (cinematic_in_progress())
    return;

  nplayers = local_player_count();
  if (nplayers <= 1)
    return;

  /* Vertical center divider (2+ players). */
  rect[0] = 0xef;
  rect[1] = 0;
  rect[2] = 0xf1;
  rect[3] = 0x280;
  draw_quad(rect, (int)0xff000000);

  if (nplayers <= 2)
    return;

  /* Horizontal divider for 3–4 players. */
  rect[2] = 0x1e0;
  rect[3] = 0x141;
  rect[1] = 0x13f;
  if (nplayers == 3) {
    rect[0] = 0xf0;
    draw_quad(rect, (int)0xff000000);
    return;
  }

  rect[0] = 0;
  if (nplayers != 4) {
    display_assert((const char *)0x2825d0, (const char *)0x2824e0, 0x374, 1);
    system_exit(-1);
  }
  draw_quad(rect, (int)0xff000000);
}


/* Initialize interface for a new map: set up HUD elements and load the
 * first interface globals tag block entry for widget rendering. */
void interface_initialize_for_new_map(void)
{
  char *globals;
  char *element;

  ((void (*)(void))0xd0360)();
  ((void (*)(void))0x19b330)();
  ((void (*)(void))0xdc7a0)();

  globals = (char *)game_globals_get();
  if (*(int *)(globals + 0x140) == 0) {
    element = 0;
  } else {
    globals = (char *)game_globals_get();
    element = (char *)tag_block_get_element(globals + 0x140, 0, 0x130);
  }

  ((void (*)(int, int, int, int, void *))0x19b8b0)(*(int *)(element + 0x1c), -1,
                                                   0, 0, *(void **)0x2ee6c4);
}
/* --- interface.obj batch drafts (2026-07-26) --- */

/* FUN_000dedf0 (0xdedf0) — readable C lift (restored pre-naked). */
void FUN_000dedf0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  local_player_get_player_index(eax);
  datum_get((void *)(uintptr_t)ecx, 0);
  director_get_perspective(edx);
  /* test ecx, ecx -> je 0xdef9b */
  /* relift: cmp byte ptr [ecx], 0 -> je 0xdef9b */
  /* cmp (int16_t)eax, 3 -> je 0xdef9b */
  /* cmp (int16_t)eax, 2 -> je 0xdef9b */
  /* cmp eax, ebx -> je 0xdef9b */
  object_get_and_verify_type(0, 0);
  unit_get_weapon(0, eax);
  object_get_and_verify_type(0, 0);
  /* cmp eax, ebx -> je 0xdef9b */
  /* relift: cmp word ptr [esi + 0x2a0], (int16_t)ebx -> je 0xdef9b */
  object_get_and_verify_type(0, 0);
  tag_get(0x756e6974, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)ecx, 8 -> je 0xdef9b */
  object_get_and_verify_type(0, 0);
  unit_get_weapon(0, ecx);
  object_get_and_verify_type(0, 0);
  /* cmp esi, -1 -> je 0xdef9b */
  object_get_and_verify_type(0, 0);
  tag_get('paew', 0);
  /* cmp eax, -1 -> je 0xdef7e */
  unit_count_weapons(0);
  /* test (int16_t)eax, (int16_t)eax -> jne 0xdef9b */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}


/* interface_draw_screen (0xdefb0) — XBE naked draft (batch 109). */
#if defined(__clang__)
static void (*const bdefb0_cdedf0)(void) = FUN_000dedf0;
static void *(*const bdefb0_tag)(int, int) = tag_get;
static void *(*const bdefb0_elem)(void *, int, int) = tag_block_get_element;
static int16_t (*const bdefb0_cb6a70)(int16_t local_player_index) = player_control_get_zoom_level;
static void *(*const bdefb0_memset)(void *, int, unsigned int) = csmemset;
static int16_t (*const bdefb0_c100b00)(void) = main_get_window_count;
static void (*const bdefb0_c10b820)(float a, float b, float blend, float *out) = scalars_interpolate;
static void (*const bdefb0_c17d9d0)(void) = (void *)FUN_0017d9d0;
static void (*const bdefb0_c17cb90)(void *decal) = FUN_0017cb90;
static void (*const bdefb0_cd1400)(void) = FUN_000d1400;
static void (*const bdefb0_cafdf0)(void) = FUN_000afdf0;

__attribute__((naked, noinline))
void interface_draw_screen(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x44, %%esp\n\t"
      "cmpw $-1, 0x506548\n\t"
      "je .Linterface_draw_screen_36\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[cdedf0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Linterface_draw_screen_35\n\t"
      "pushl %%eax\n\t"
      "pushl $0x77706869\n\t"
      "call *%[tag]\n\t"
      "movl 0xac(%%eax), %%ecx\n\t"
      "addl $0xac, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .Linterface_draw_screen_35\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl $0xb8\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x506548, %%cx\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[cb6a70]\n\t"
      "pushl $0x38\n\t"
      "leal -0x44(%%ebp), %%edx\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "setne %%bl\n\t"
      "call *%[memset]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Linterface_draw_screen_1\n\t"
      "testb $1, 0x4(%%esi)\n\t"
      "jne .Linterface_draw_screen_4\n\t"
      ".Linterface_draw_screen_1:\n\t"
      "call *%[c100b00]\n\t"
      "cmpw $1, %%ax\n\t"
      "jg .Linterface_draw_screen_2\n\t"
      "movl 0x24(%%esi), %%eax\n\t"
      "jmp .Linterface_draw_screen_3\n\t"
      ".Linterface_draw_screen_2:\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      ".Linterface_draw_screen_3:\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Linterface_draw_screen_4\n\t"
      "pushl $0x30\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6269746d\n\t"
      "call *%[tag]\n\t"
      "addl $0x60, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movb 0x6c(%%esi), %%al\n\t"
      "shrb $2, %%al\n\t"
      "andb $1, %%al\n\t"
      "movb %%al, -0x23(%%ebp)\n\t"
      "movb 0x8c(%%esi), %%cl\n\t"
      "shrb $3, %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "andb $1, %%cl\n\t"
      "movb %%cl, -0x22(%%ebp)\n\t"
      ".Linterface_draw_screen_4:\n\t"
      "call *%[c100b00]\n\t"
      "cmpw $1, %%ax\n\t"
      "jg .Linterface_draw_screen_12\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Linterface_draw_screen_5\n\t"
      "testb $1, 0x40(%%esi)\n\t"
      "jne .Linterface_draw_screen_13\n\t"
      ".Linterface_draw_screen_5:\n\t"
      "flds 0x44(%%esi)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "fcomps 0x48(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Linterface_draw_screen_9\n\t"
      "flds 0x506578\n\t"
      "fsubs 0x44(%%esi)\n\t"
      "flds 0x48(%%esi)\n\t"
      "fsubs 0x44(%%esi)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Linterface_draw_screen_6\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "jmp .Linterface_draw_screen_8\n\t"
      ".Linterface_draw_screen_6:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Linterface_draw_screen_7\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, -0x8(%%ebp)\n\t"
      "jmp .Linterface_draw_screen_8\n\t"
      ".Linterface_draw_screen_7:\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".Linterface_draw_screen_8:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x50(%%esi), %%ecx\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x4c(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c10b820]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .Linterface_draw_screen_10\n\t"
      ".Linterface_draw_screen_9:\n\t"
      "flds 0x50(%%esi)\n\t"
      ".Linterface_draw_screen_10:\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Linterface_draw_screen_11\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "movw $2, -0x42(%%ebp)\n\t"
      "jmp .Linterface_draw_screen_12\n\t"
      ".Linterface_draw_screen_11:\n\t"
      "fstp %%st(0)\n\t"
      ".Linterface_draw_screen_12:\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Linterface_draw_screen_14\n\t"
      ".Linterface_draw_screen_13:\n\t"
      "testb $1, 0x6c(%%esi)\n\t"
      "jne .Linterface_draw_screen_24\n\t"
      ".Linterface_draw_screen_14:\n\t"
      "movl 0x70(%%esi), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "testb $2, 0x6c(%%esi)\n\t"
      "je .Linterface_draw_screen_18\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Linterface_draw_screen_15\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Linterface_draw_screen_17\n\t"
      ".Linterface_draw_screen_15:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Linterface_draw_screen_16\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Linterface_draw_screen_17\n\t"
      ".Linterface_draw_screen_16:\n\t"
      "flds -0x4(%%ebp)\n\t"
      ".Linterface_draw_screen_17:\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".Linterface_draw_screen_18:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x6e(%%esi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17d9d0]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Linterface_draw_screen_19\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Linterface_draw_screen_21\n\t"
      ".Linterface_draw_screen_19:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x6e(%%esi), %%dx\n\t"
      "pushl %%edx\n\t"
      "call *%[c17d9d0]\n\t"
      "fcomps 0x2533c8\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Linterface_draw_screen_20\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Linterface_draw_screen_21\n\t"
      ".Linterface_draw_screen_20:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6e(%%esi), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c17d9d0]\n\t"
      "addl $4, %%esp\n\t"
      ".Linterface_draw_screen_21:\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Linterface_draw_screen_22\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "jmp .Linterface_draw_screen_23\n\t"
      ".Linterface_draw_screen_22:\n\t"
      "fstp %%st(0)\n\t"
      ".Linterface_draw_screen_23:\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Linterface_draw_screen_25\n\t"
      ".Linterface_draw_screen_24:\n\t"
      "testb $1, 0x8c(%%esi)\n\t"
      "jne .Linterface_draw_screen_34\n\t"
      ".Linterface_draw_screen_25:\n\t"
      "testb $2, 0x8c(%%esi)\n\t"
      "movl 0x90(%%esi), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "je .Linterface_draw_screen_29\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Linterface_draw_screen_26\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Linterface_draw_screen_28\n\t"
      ".Linterface_draw_screen_26:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Linterface_draw_screen_27\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Linterface_draw_screen_28\n\t"
      ".Linterface_draw_screen_27:\n\t"
      "flds -0x4(%%ebp)\n\t"
      ".Linterface_draw_screen_28:\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".Linterface_draw_screen_29:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x8e(%%esi), %%dx\n\t"
      "pushl %%edx\n\t"
      "call *%[c17d9d0]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Linterface_draw_screen_30\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Linterface_draw_screen_32\n\t"
      ".Linterface_draw_screen_30:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x8e(%%esi), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c17d9d0]\n\t"
      "fcomps 0x2533c8\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Linterface_draw_screen_31\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Linterface_draw_screen_32\n\t"
      ".Linterface_draw_screen_31:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x8e(%%esi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17d9d0]\n\t"
      "addl $4, %%esp\n\t"
      ".Linterface_draw_screen_32:\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Linterface_draw_screen_33\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "movb 0x8c(%%esi), %%dl\n\t"
      "shrb $2, %%dl\n\t"
      "andb $1, %%dl\n\t"
      "movb %%dl, -0x24(%%ebp)\n\t"
      "addl $0x94, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl %%ecx, -0x2c(%%ebp)\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "leal -0x44(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "call *%[c17cb90]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "call *%[cd1400]\n\t"
      "call *%[cafdf0]\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Linterface_draw_screen_33:\n\t"
      "fstp %%st(0)\n\t"
      ".Linterface_draw_screen_34:\n\t"
      "leal -0x44(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c17cb90]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "call *%[cd1400]\n\t"
      "call *%[cafdf0]\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Linterface_draw_screen_35:\n\t"
      "pushl $0\n\t"
      "call *%[c17cb90]\n\t"
      "addl $4, %%esp\n\t"
      "call *%[cd1400]\n\t"
      "call *%[cafdf0]\n\t"
      ".Linterface_draw_screen_36:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cdedf0] "m"(bdefb0_cdedf0), [tag] "m"(bdefb0_tag), [elem] "m"(bdefb0_elem), [cb6a70] "m"(bdefb0_cb6a70), [memset] "m"(bdefb0_memset), [c100b00] "m"(bdefb0_c100b00), [c10b820] "m"(bdefb0_c10b820), [c17d9d0] "m"(bdefb0_c17d9d0), [c17cb90] "m"(bdefb0_c17cb90), [cd1400] "m"(bdefb0_cd1400), [cafdf0] "m"(bdefb0_cafdf0)
      : "memory");
}
#else
#error "interface_draw_screen: clang naked draft required"
#endif


/* profile_graph_toggle (0xdf350) — readable C lift. */
void profile_graph_toggle(const char *name)
{
  int16_t count = *(int16_t *)0x306d20;
  for (int16_t i = 0; i < count; i++) {
    char *entry = (char *)0x306d28 + (int)i * 0x20c;
    if (crt_stricmp(name, entry) == 0 || crt_stricmp(name, entry + 0x100) == 0) {
      entry[0x209] = !entry[0x209];
    }
  }
}

/* FUN_000df3d0 (0xdf3d0) — readable C lift (restored pre-naked). */
void FUN_000df3d0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  matrix_transform_point((void *)0x005065e8, (float *)(uintptr_t)ecx, (float *)0);
  matrix_transform_point((void *)0x005065e8, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  rasterizer_hud_motion_sensor_blip_begin();

  (void)eax;
  (void)ecx;
  (void)edx;
}


/* FUN_000df4e0 (0xdf4e0) — XBE naked draft (batch 104). */
#if defined(__clang__)
static void (*const bdf4e0_chkstk)(void) = FUN_001d90e0;
static void * (*const bdf4e0_c18e450)(void) = game_globals_get;
static void *(*const bdf4e0_elem)(void *, int, int) = tag_block_get_element;
static void * (*const bdf4e0_cded20)(int interface_tag_index, short color_index, void *out_color) = interface_get_color;
static void (*const bdf4e0_c19b8b0)(int tag_index, int style, int justify, int flags, const void *color) = draw_string_set_font;
static void (*const bdf4e0_c13db60)(short *param_1) = FUN_0013db60;
static void (*const bdf4e0_c8e480)(uint32_t *output) = FUN_0008e480;
static void (*const bdf4e0_c9c910)(short *out) = FUN_0009c910;
static char * (*const bdf4e0_c8dff0)(char *destination, const char *source) = csstrcpy;
static int (*const bdf4e0_c8df60)(const char *s1) = csstrlen;
static int (*const bdf4e0_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static void (*const bdf4e0_c53790)(void) = (void (*)(void))FUN_00053790;
static void (*const bdf4e0_c14da20)(char *display_line) = FUN_0014da20;
static void (*const bdf4e0_c183e60)(void *screen_pos, short *bounds, const void *color, int flags, const char *text) = rasterizer_text_draw;
static void (*const bdf4e0_c902f0)(void) = profile_dump;
static void (*const bdf4e0_c19b560)(void *stops, short count) = draw_string_set_tab_stops;
static void (*const bdf4e0_c185f80)(void *frustum, float *bounds) = render_frustum_get_projection_bounds;
static void (*const bdf4e0_c908a0)(void) = profile_find_frame_value;
static void (*const bdf4e0_c17ca10)(void) = rasterizer_hud_motion_sensor_blip_begin;
static void *(*const bdf4e0_memset)(void *, int, unsigned int) = csmemset;
static void (*const bdf4e0_c17ca40)(void) = FUN_0017ca40;
static void (*const bdf4e0_c910b0)(int16_t *iter) = profile_frame_iterator_new;
static char (*const bdf4e0_c91110)(int16_t *iter, uint32_t *out_cycles) = profile_frame_iterator_next;
static void (*const bdf4e0_c90d10)(void) = profile_frame_get_value;
static void (*const bdf4e0_ftol)(void) = FUN_001d9068;
static void (*const bdf4e0_xfrmpt)(float *, float *, float *) = matrix_transform_point;
static void (*const bdf4e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bdf4e0_exitfn)(int) = system_exit;
static void (*const bdf4e0_c17ca60)(short *points, int16_t point_count, float *color) = FUN_0017ca60;
static void * (*const bdf4e0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const bdf4e0_c17ca70)(void) = FUN_0017ca70;
static void (*const bdf4e0_c17ca00)(void) = rasterizer_widget_get_occlusion_test_result;
static void (*const bdf4e0_c91190)(int16_t *frame_ref) = profile_frame_get_messages;
static int (*const bdf4e0_c91220)(int16_t *frame_ref, int16_t *out_count, int *out_val) = profile_frame_get_stalls;
static void (*const bdf4e0_cdf3d0)(void) = FUN_000df3d0;
static void (*const bdf4e0_c17ca30)(void) = rasterizer_hud_motion_sensor_blip_end;

__attribute__((naked, noinline))
void FUN_000df4e0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x23b48, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "movb 0x5aa675, %%al\n\t"
      "testb %%al, %%al\n\t"
      "pushl %%esi\n\t"
      "je .LFUN_000df4e0_3\n\t"
      "call *%[c18e450]\n\t"
      "movl 0x140(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_000df4e0_1\n\t"
      "pushl $0x130\n\t"
      "pushl $0\n\t"
      "call *%[c18e450]\n\t"
      "addl $0x140, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_000df4e0_2\n\t"
      ".LFUN_000df4e0_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_000df4e0_2:\n\t"
      "movl 0x1c(%%eax), %%esi\n\t"
      "leal -0x70(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $5\n\t"
      "call *%[cded20]\n\t"
      "leal -0x70(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "call *%[c19b8b0]\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c13db60]\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e480]\n\t"
      "leal -0x3c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c9c910]\n\t"
      "leal -0x2b48(%%ebp), %%edx\n\t"
      "pushl $0x25386f\n\t"
      "pushl %%edx\n\t"
      "call *%[c8dff0]\n\t"
      "fildl -0x18(%%ebp)\n\t"
      "addl $0x24, %%esp\n\t"
      "leal -0x2b48(%%ebp), %%eax\n\t"
      "fmuls 0x2825cc\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "fildl -0x1c(%%ebp)\n\t"
      "fmuls 0x2825cc\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2825ac\n\t"
      "pushl %%eax\n\t"
      "call *%[c8df60]\n\t"
      "leal -0x2b48(%%ebp,%%eax,1), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x253f00\n\t"
      "movswl -0x24(%%ebp), %%edx\n\t"
      "movswl -0x22(%%ebp), %%eax\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x2b48(%%ebp), %%ecx\n\t"
      "pushl $0x28257c\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8df60]\n\t"
      "leal -0x2b48(%%ebp,%%eax,1), %%edx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "movswl -0x3a(%%ebp), %%eax\n\t"
      "movswl -0x3c(%%ebp), %%ecx\n\t"
      "movswl -0x38(%%ebp), %%edx\n\t"
      "addl $0x18, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x2b48(%%ebp), %%eax\n\t"
      "pushl $0x28254c\n\t"
      "pushl %%eax\n\t"
      "call *%[c8df60]\n\t"
      "leal -0x2b48(%%ebp,%%eax,1), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "movl 0x5aa8a0, %%edx\n\t"
      "movswl 0x30(%%edx), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%eax\n\t"
      "leal -0x2b48(%%ebp), %%ecx\n\t"
      "pushl $0x282538\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8df60]\n\t"
      "addl $4, %%esp\n\t"
      "leal -0x2b48(%%ebp,%%eax,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x2b48(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c53790]\n\t"
      "leal -0x2b48(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c14da20]\n\t"
      "leal -0x2b48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c183e60]\n\t"
      "leal -0x2b48(%%ebp), %%eax\n\t"
      "pushl $0x282528\n\t"
      "pushl %%eax\n\t"
      "movw $0x12c, -0x1c(%%ebp)\n\t"
      "movw $0x17c, -0x1a(%%ebp)\n\t"
      "movw $0x1cc, -0x18(%%ebp)\n\t"
      "movw $0x21c, -0x16(%%ebp)\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x2b48(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8df60]\n\t"
      "leal -0x2b48(%%ebp,%%eax,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0xa\n\t"
      "pushl $1\n\t"
      "pushl $2\n\t"
      "pushl $0\n\t"
      "call *%[c902f0]\n\t"
      "addl $0x48, %%esp\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b560]\n\t"
      "leal -0x2b48(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c183e60]\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c19b560]\n\t"
      "addl $0x24, %%esp\n\t"
      ".LFUN_000df4e0_3:\n\t"
      "movb 0x5aa674, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000df4e0_31\n\t"
      "leal -0x70(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5065a4\n\t"
      "call *%[c185f80]\n\t"
      "flds -0x70(%%ebp)\n\t"
      "fsubs 0x25496c\n\t"
      "movswl 0x32565a, %%eax\n\t"
      "movswl 0x325656, %%ecx\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds -0x6c(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "fadds 0x25496c\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movswl 0x325658, %%eax\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds -0x64(%%ebp)\n\t"
      "fadds 0x25496c\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movswl 0x325654, %%ecx\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds -0x68(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fsubs 0x25496c\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "fmuls 0x25496c\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "movb 0x5aa674, %%al\n\t"
      "testb %%al, %%al\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fstps -0x5c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "fmuls 0x25496c\n\t"
      "fildl -0x10(%%ebp)\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "je .LFUN_000df4e0_31\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpw %%di, 0x306d20\n\t"
      "jle .LFUN_000df4e0_5\n\t"
      "jmp .LFUN_000df4e0_4\n\t"
      "leal (%%esp), %%esp\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000df4e0_4:\n\t"
      "movswl %%di, %%esi\n\t"
      "imull $0x20c, %%esi, %%esi\n\t"
      "addl $0x306d28, %%esi\n\t"
      "leal 0x206(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c908a0]\n\t"
      "addl $8, %%esp\n\t"
      "incl %%edi\n\t"
      "cmpw 0x306d20, %%di\n\t"
      "movw %%ax, 0x204(%%esi)\n\t"
      "jl .LFUN_000df4e0_4\n\t"
      ".LFUN_000df4e0_5:\n\t"
      "movb 0x5aa674, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000df4e0_30\n\t"
      "flds -0x34(%%ebp)\n\t"
      "movl 0x325678, %%edx\n\t"
      "fmuls 0x25496c\n\t"
      "movl 0x2ee6c4, %%ecx\n\t"
      "movl 0x32567c, %%eax\n\t"
      "pushl %%ebx\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "pushl $0\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "addl $4, %%ecx\n\t"
      "fmuls 0x25496c\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "leal -0x50(%%ebp), %%edx\n\t"
      "fsts -0x3c(%%ebp)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "fmuls 0x25496c\n\t"
      "leal -0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "movl $0xbdcccccd, -0x38(%%ebp)\n\t"
      "movl $0xbdcccccd, -0x48(%%ebp)\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "call *%[c17ca10]\n\t"
      "pushl $0x80\n\t"
      "leal -0x108(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "call *%[c17ca40]\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c910b0]\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c91110]\n\t"
      "addl $0x28, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000df4e0_18\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_000df4e0_6:\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "movl -0x1c(%%ebp), %%esi\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "subl %%esi, %%edx\n\t"
      "sbbl %%ecx, %%eax\n\t"
      "movl %%eax, -0x48(%%ebp)\n\t"
      "movl %%edx, -0x4c(%%ebp)\n\t"
      "fildl -0x4c(%%ebp)\n\t"
      "fmuls 0x25634c\n\t"
      "fcoms 0x253f34\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000df4e0_16\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw %%cx, 0x306d20\n\t"
      "fsubs -0x60(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fmuls 0x25496c\n\t"
      "fadds -0x60(%%ebp)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fsubs -0x34(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fmuls 0x25496c\n\t"
      "fadds -0x34(%%ebp)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "jle .LFUN_000df4e0_17\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000df4e0_7:\n\t"
      "movswl %%cx, %%esi\n\t"
      "movl %%esi, %%edi\n\t"
      "imull $0x20c, %%edi, %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x306f2c(%%edi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_000df4e0_15\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x306f2e(%%edi), %%cx\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c90d10]\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fcomps 0x2533c0\n\t"
      "xorb %%bl, %%bl\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000df4e0_8\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "jmp .LFUN_000df4e0_9\n\t"
      ".LFUN_000df4e0_8:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x253f00\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000df4e0_9\n\t"
      "movl $0x42c80000, -0x8(%%ebp)\n\t"
      ".LFUN_000df4e0_9:\n\t"
      "movb 0x306f30(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000df4e0_10\n\t"
      "cmpw $0, -0xc(%%ebp)\n\t"
      "jle .LFUN_000df4e0_10\n\t"
      "movb 0x306d25(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000df4e0_10\n\t"
      "cmpw $-1, 0x306d20(%%edi)\n\t"
      "je .LFUN_000df4e0_10\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000df4e0_10\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fsubs -0x34c(%%ebp,%%esi,4)\n\t"
      "fabs\n\t"
      "fcompl 0x2674e8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000df4e0_10\n\t"
      "flds -0x248(%%ebp,%%esi,4)\n\t"
      "fsubs -0x24c(%%ebp,%%esi,4)\n\t"
      "fabs\n\t"
      "fcompl 0x2674e8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000df4e0_10\n\t"
      "movb $1, %%bl\n\t"
      ".LFUN_000df4e0_10:\n\t"
      "flds -0x44(%%ebp)\n\t"
      "call *%[ftol]\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x25bb10\n\t"
      "movw %%ax, -0x10(%%ebp)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fsubs -0x58(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds -0x58(%%ebp)\n\t"
      "call *%[ftol]\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls 0x25496c\n\t"
      "movw %%ax, -0xe(%%ebp)\n\t"
      "leal -0x7c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fstps -0x88(%%ebp)\n\t"
      "leal -0x88(%%ebp), %%ecx\n\t"
      "flds -0x28(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fsubs -0x2c(%%ebp)\n\t"
      "pushl $0x5065e8\n\t"
      "movl $0xbdcccccd, -0x80(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds -0x2c(%%ebp)\n\t"
      "fmuls 0x25496c\n\t"
      "fstps -0x84(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[xfrmpt]\n\t"
      "movb 0x306f31(%%edi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000df4e0_13\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000df4e0_13\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_000df4e0_13\n\t"
      "cmpw $0, -0x108(%%ebp,%%esi,2)\n\t"
      "jne .LFUN_000df4e0_11\n\t"
      "movl -0x548(%%ebp,%%esi,4), %%eax\n\t"
      "movl %%esi, %%edx\n\t"
      "shll $0xb, %%edx\n\t"
      "movl %%eax, -0x23b48(%%ebp,%%edx,1)\n\t"
      "movw $1, -0x108(%%ebp,%%esi,2)\n\t"
      ".LFUN_000df4e0_11:\n\t"
      "cmpw $0x200, -0x108(%%ebp,%%esi,2)\n\t"
      "jl .LFUN_000df4e0_12\n\t"
      "pushl $1\n\t"
      "pushl $0x2c0\n\t"
      "pushl $0x2824e0\n\t"
      "pushl $0x282508\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000df4e0_12:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw -0x108(%%ebp,%%esi,2), %%ax\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "shll $9, %%ecx\n\t"
      "addl %%edx, %%ecx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "incl %%eax\n\t"
      "movl %%edx, -0x23b48(%%ebp,%%ecx,4)\n\t"
      "movw %%ax, -0x108(%%ebp,%%esi,2)\n\t"
      "jmp .LFUN_000df4e0_14\n\t"
      ".LFUN_000df4e0_13:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw -0x108(%%ebp,%%esi,2), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_000df4e0_14\n\t"
      "movl 0x306f28(%%edi), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "addl $4, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%eax\n\t"
      "shll $0xb, %%eax\n\t"
      "leal -0x23b48(%%ebp,%%eax,1), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17ca60]\n\t"
      "addl $0xc, %%esp\n\t"
      "movw $0, -0x108(%%ebp,%%esi,2)\n\t"
      ".LFUN_000df4e0_14:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "flds -0x8(%%ebp)\n\t"
      "leal (%%esi,%%esi,2), %%eax\n\t"
      "fstps -0x348(%%ebp,%%esi,4)\n\t"
      "movl %%edx, -0x448(%%ebp,%%esi,4)\n\t"
      "movl -0x7c(%%ebp), %%edx\n\t"
      "leal -0x848(%%ebp,%%eax,4), %%ecx\n\t"
      "movl -0x78(%%ebp), %%eax\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0x74(%%ebp), %%edx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      ".LFUN_000df4e0_15:\n\t"
      "incl %%ecx\n\t"
      "cmpw 0x306d20, %%cx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jl .LFUN_000df4e0_7\n\t"
      "jmp .LFUN_000df4e0_17\n\t"
      ".LFUN_000df4e0_16:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_000df4e0_17:\n\t"
      "pushl $0x100\n\t"
      "leal -0x348(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x248(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0x100\n\t"
      "leal -0x448(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x548(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0x300\n\t"
      "leal -0x848(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xb48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8e0b0]\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c91110]\n\t"
      "addl $0x2c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000df4e0_6\n\t"
      ".LFUN_000df4e0_18:\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpw %%di, 0x306d20\n\t"
      "jle .LFUN_000df4e0_21\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000df4e0_19:\n\t"
      "movswl %%di, %%eax\n\t"
      "movw -0x108(%%ebp,%%eax,2), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "leal -0x108(%%ebp,%%eax,2), %%esi\n\t"
      "jle .LFUN_000df4e0_20\n\t"
      "movl %%eax, %%edx\n\t"
      "imull $0x20c, %%edx, %%edx\n\t"
      "movl 0x306f28(%%edx), %%edx\n\t"
      "movl (%%edx), %%edx\n\t"
      "addl $4, %%edx\n\t"
      "pushl %%edx\n\t"
      "shll $0xb, %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x23b48(%%ebp,%%eax,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c17ca60]\n\t"
      "addl $0xc, %%esp\n\t"
      "movw $0, (%%esi)\n\t"
      ".LFUN_000df4e0_20:\n\t"
      "incl %%edi\n\t"
      "cmpw 0x306d20, %%di\n\t"
      "jl .LFUN_000df4e0_19\n\t"
      ".LFUN_000df4e0_21:\n\t"
      "call *%[c17ca70]\n\t"
      "call *%[c17ca00]\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c910b0]\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c91110]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000df4e0_29\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000df4e0_22:\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "subl %%edx, %%ecx\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "sbbl %%eax, %%edx\n\t"
      "movl %%ecx, -0x4c(%%ebp)\n\t"
      "movl %%edx, -0x48(%%ebp)\n\t"
      "fildl -0x4c(%%ebp)\n\t"
      "fmuls 0x25634c\n\t"
      "fcoms 0x253f34\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000df4e0_27\n\t"
      "flds -0x30(%%ebp)\n\t"
      "leal -0x148(%%ebp), %%ecx\n\t"
      "fsubs -0x34(%%ebp)\n\t"
      "leal -0x3b48(%%ebp), %%eax\n\t"
      "movl $0x30, %%edx\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fmuls 0x25496c\n\t"
      "fadds -0x34(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "jmp .LFUN_000df4e0_23\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000df4e0_23:\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "addl $0x100, %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "decl %%edx\n\t"
      "jne .LFUN_000df4e0_23\n\t"
      "leal -0x208(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x308(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x148(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x30\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "xorl %%esi, %%esi\n\t"
      "pushl %%ecx\n\t"
      "movl %%esi, -0x38(%%ebp)\n\t"
      "call *%[c91190]\n\t"
      "leal -0x44(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "movl %%esi, -0x44(%%ebp)\n\t"
      "call *%[c91220]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0x24, %%esp\n\t"
      "cmpl %%esi, %%edi\n\t"
      "je .LFUN_000df4e0_28\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl $1, %%eax\n\t"
      "movb %%dl, %%cl\n\t"
      "shll %%cl, %%eax\n\t"
      "movl $0x3c23d70a, -0x8(%%ebp)\n\t"
      "testl %%eax, %%edi\n\t"
      "je .LFUN_000df4e0_24\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "pushl $0x3dcccccd\n\t"
      "pushl %%ecx\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "call *%[cdf3d0]\n\t"
      "movb -0xc(%%ebp), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "notl %%edx\n\t"
      "andl %%edx, %%edi\n\t"
      ".LFUN_000df4e0_24:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      ".LFUN_000df4e0_25:\n\t"
      "movl $1, %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "shll %%cl, %%eax\n\t"
      "testl %%eax, %%edi\n\t"
      "je .LFUN_000df4e0_26\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "pushl $0x3dcccccd\n\t"
      "pushl %%ecx\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "movl %%esi, %%edx\n\t"
      "call *%[cdf3d0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000df4e0_26:\n\t"
      "incl %%esi\n\t"
      "incl %%ebx\n\t"
      "cmpw $0x1b, %%si\n\t"
      "jl .LFUN_000df4e0_25\n\t"
      "jmp .LFUN_000df4e0_28\n\t"
      ".LFUN_000df4e0_27:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_000df4e0_28:\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c91110]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000df4e0_22\n\t"
      ".LFUN_000df4e0_29:\n\t"
      "call *%[c17ca30]\n\t"
      "popl %%ebx\n\t"
      ".LFUN_000df4e0_30:\n\t"
      "popl %%edi\n\t"
      ".LFUN_000df4e0_31:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(bdf4e0_chkstk), [c18e450] "m"(bdf4e0_c18e450), [elem] "m"(bdf4e0_elem), [cded20] "m"(bdf4e0_cded20), [c19b8b0] "m"(bdf4e0_c19b8b0), [c13db60] "m"(bdf4e0_c13db60), [c8e480] "m"(bdf4e0_c8e480), [c9c910] "m"(bdf4e0_c9c910), [c8dff0] "m"(bdf4e0_c8dff0), [c8df60] "m"(bdf4e0_c8df60), [c1d90f0] "m"(bdf4e0_c1d90f0), [c53790] "m"(bdf4e0_c53790), [c14da20] "m"(bdf4e0_c14da20), [c183e60] "m"(bdf4e0_c183e60), [c902f0] "m"(bdf4e0_c902f0), [c19b560] "m"(bdf4e0_c19b560), [c185f80] "m"(bdf4e0_c185f80), [c908a0] "m"(bdf4e0_c908a0), [c17ca10] "m"(bdf4e0_c17ca10), [memset] "m"(bdf4e0_memset), [c17ca40] "m"(bdf4e0_c17ca40), [c910b0] "m"(bdf4e0_c910b0), [c91110] "m"(bdf4e0_c91110), [c90d10] "m"(bdf4e0_c90d10), [ftol] "m"(bdf4e0_ftol), [xfrmpt] "m"(bdf4e0_xfrmpt), [assert] "m"(bdf4e0_assert), [exitfn] "m"(bdf4e0_exitfn), [c17ca60] "m"(bdf4e0_c17ca60), [c8e0b0] "m"(bdf4e0_c8e0b0), [c17ca70] "m"(bdf4e0_c17ca70), [c17ca00] "m"(bdf4e0_c17ca00), [c91190] "m"(bdf4e0_c91190), [c91220] "m"(bdf4e0_c91220), [cdf3d0] "m"(bdf4e0_cdf3d0), [c17ca30] "m"(bdf4e0_c17ca30)
      : "memory");
}
#else
#error "FUN_000df4e0: clang naked draft required"
#endif


/* interface_get_rgb_color (0xdff00) — readable C lift. */
int16_t *interface_get_rgb_color(int interface_tag_index, int16_t color_index, int16_t *out_rgb)
{
  float tmp[4];
  float scale;
  interface_get_color(interface_tag_index, color_index, tmp);
  scale = *(float *)0x2647cc;
  out_rgb[0] = (int16_t)(int)(tmp[0] * scale);
  out_rgb[1] = (int16_t)(int)(tmp[1] * scale);
  out_rgb[2] = (int16_t)(int)(tmp[2] * scale);
  out_rgb[3] = (int16_t)(int)(tmp[3] * scale);
  return out_rgb;
}

/* interface_draw_fullscreen_overlays (0xdff70) — readable C lift. */
void interface_draw_fullscreen_overlays(void)
{
  cinematic_render();
  interface_draw_splitscreen_dividers();
  hud_render_timer();
  terminal_draw();
  main_framerate_render();
  FUN_000df4e0();
}

/* interface_draw_bitmap (0xdff90) — readable C lift (restored pre-naked). */
void interface_draw_bitmap(int sprite_handle, short *offset_xy, void *color, float scale_a, int flag, float scale_b)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  FUN_001d9068();
  /* test dl, 2 -> je 0xe004c */
  /* cmp (int16_t)esi, 1 -> jle 0xe0059 */
  csmemset((void *)(uintptr_t)edx, 0, 0);
  rasterizer_sprites_render((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}


/* FUN_000e0110 (0xe0110) — XBE naked draft (batch 121). */
#if defined(__clang__)
static void (*const be0110_ftol)(void) = FUN_001d9068;
static void *(*const be0110_memset)(void *, int, unsigned int) = csmemset;
static void (*const be0110_c17cfa0)(void *render_data, void *vertices) = rasterizer_sprites_render;

__attribute__((naked, noinline))
void FUN_000e0110(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xf0, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movswl 0x4(%%ebx), %%eax\n\t"
      "movswl 0x6(%%ebx), %%ecx\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fsin\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fcos\n\t"
      "fstps 0x18(%%ebp)\n\t"
      "jne .LFUN_000e0110_1\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      ".LFUN_000e0110_1:\n\t"
      "movl 0x1c(%%ebp), %%edi\n\t"
      "flds (%%edi)\n\t"
      "fmuls 0x2602c8\n\t"
      "call *%[ftol]\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls 0x2602c8\n\t"
      "movl %%eax, %%esi\n\t"
      "shll $8, %%esi\n\t"
      "call *%[ftol]\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls 0x2602c8\n\t"
      "orl %%eax, %%esi\n\t"
      "shll $8, %%esi\n\t"
      "call *%[ftol]\n\t"
      "flds 0xc(%%edi)\n\t"
      "fmuls 0x2602c8\n\t"
      "orl %%eax, %%esi\n\t"
      "shll $8, %%esi\n\t"
      "call *%[ftol]\n\t"
      "movswl 0x12(%%ebx), %%edx\n\t"
      "orl %%eax, %%esi\n\t"
      "movswl 0x10(%%ebx), %%eax\n\t"
      "movl %%eax, 0x1c(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "fildl 0x1c(%%ebp)\n\t"
      "movl %%edx, 0x1c(%%ebp)\n\t"
      "movswl (%%eax), %%edx\n\t"
      "fildl 0x1c(%%ebp)\n\t"
      "movswl 0x2(%%eax), %%eax\n\t"
      "movl %%edx, 0x1c(%%ebp)\n\t"
      "movl $1, %%edx\n\t"
      "fildl 0x1c(%%ebp)\n\t"
      "movl %%eax, 0x1c(%%ebp)\n\t"
      "leal -0xec(%%ebp), %%eax\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fildl 0x1c(%%ebp)\n\t"
      "fstps 0x1c(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000e0110_2:\n\t"
      "testb $2, %%dl\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "je .LFUN_000e0110_3\n\t"
      "flds 0x4(%%edi)\n\t"
      "jmp .LFUN_000e0110_4\n\t"
      ".LFUN_000e0110_3:\n\t"
      "flds (%%edi)\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      ".LFUN_000e0110_4:\n\t"
      "cmpw $1, %%cx\n\t"
      "jle .LFUN_000e0110_5\n\t"
      "flds 0xc(%%edi)\n\t"
      "jmp .LFUN_000e0110_6\n\t"
      ".LFUN_000e0110_5:\n\t"
      "flds 0x8(%%edi)\n\t"
      ".LFUN_000e0110_6:\n\t"
      "fld %%st(1)\n\t"
      "incl %%ecx\n\t"
      ".byte 0xd8, 0xe4\n\t"
      "movl %%esi, 0xc(%%eax)\n\t"
      "incl %%edx\n\t"
      "addl $0x14, %%eax\n\t"
      "cmpw $4, %%cx\n\t"
      "fmuls 0x14(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xe4\n\t"
      "fmuls 0x14(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x18(%%ebp)\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x18(%%eax)\n\t"
      "fmuls 0x18(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds 0x1c(%%ebp)\n\t"
      "fstps -0x14(%%eax)\n\t"
      "fxch %%st(1)\n\t"
      "fstps -0x10(%%eax)\n\t"
      "fstps -0xc(%%eax)\n\t"
      "jl .LFUN_000e0110_2\n\t"
      "pushl $0x8c\n\t"
      "fstp %%st(0)\n\t"
      "leal -0xa0(%%ebp), %%ecx\n\t"
      "fstp %%st(0)\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "movw 0x20(%%ebp), %%dx\n\t"
      "leal -0xf0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xa0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl $0x3f800000, -0x5c(%%ebp)\n\t"
      "movl $0x3f800000, -0x60(%%ebp)\n\t"
      "movl $0x3f800000, -0x74(%%ebp)\n\t"
      "movl $0x3f800000, -0x78(%%ebp)\n\t"
      "movl $0, -0xa0(%%ebp)\n\t"
      "movb $0, -0x16(%%ebp)\n\t"
      "movw %%dx, -0x18(%%ebp)\n\t"
      "movl %%ebx, -0x94(%%ebp)\n\t"
      "call *%[c17cfa0]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [ftol] "m"(be0110_ftol), [memset] "m"(be0110_memset), [c17cfa0] "m"(be0110_c17cfa0)
      : "memory");
}
#else
#error "FUN_000e0110: clang naked draft required"
#endif

