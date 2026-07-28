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

/* draw_quad (0x92ec0) — readable C lift (restored pre-naked). */
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

/* cinematic_stop (0x93050) — readable C lift. */
void cinematic_stop(void)
{
  unsigned char *g;

  g = *(unsigned char **)0x44df00;
  g[8] = 0;
  player_input_enable(1);
  ai_globals_dialogue_triggers_enabled(1);
  g = *(unsigned char **)0x44df00;
  g[9] = 0;
  FUN_0017d950();
  if (*(void **)0x47e4d0 != 0)
    csmemset(*(void **)0x47e4d0, 0, 0x10);
  FUN_0017dec0(0);
  ui_widget_display_deferred_errors();
}

/* cinematic_set_title_delayed (0x930b0) — readable C lift from XBE leaf. */
void cinematic_set_title_delayed(int title_index, float delay_seconds)
{
  char *base;
  int i;
  void *elem;
  int ticks;

  base = *(char **)0x44df00;
  for (i = 0; i < 4; i++) {
    if (*(short *)(base + 0xc + i * 4) == (short)0xffff) {
      break;
    }
  }
  if (i >= 4) {
    elem = tag_block_get_element((char *)global_scenario_get() + 0x4fc, title_index,
                                 0x60);
    error(2, (const char *)0x268e9c, (char *)elem + 4);
    return;
  }
  *(short *)(base + 0xc + i * 4) = (short)title_index;
  ticks = (int)(delay_seconds * *(float *)0x253394);
  *(short *)(base + 0xe + i * 4) = (short)(-ticks);
}




/* cinematic_render (0x93140) — readable C lift (restored pre-naked). */
void cinematic_render(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  /* test (char)eax, 0x41 -> jne 0x93346 */
  ui_widgets_active();
  /* test (char)eax, (char)eax -> jne 0x93346 */
  game_time_get();
  /* test (char)eax, 0x41 -> jne 0x931dc */
  /* test (char)eax, 0x41 -> jne 0x931e0 */
  /* test (char)eax, 0x41 -> jne 0x93346 */
  draw_quad((void *)(uintptr_t)ecx, 0xff000000);
  draw_quad((void *)(uintptr_t)ecx, 0xff000000);
  /* cmp (int16_t)eax, 0xffff -> je 0x9361b */
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  global_scenario_get();
  /* cmp edi, -1 -> je 0x9361b */
  tag_get('rtsu', 0);
  /* test (int16_t)ecx, (int16_t)ecx -> jl 0x9361b */
  /* cmp ecx, edx -> jge 0x9361b */
  /* relift: cmp (int16_t)eax, word ptr [ebx] -> jne 0x93402 */
  game_in_editor();
  /* test (char)eax, (char)eax -> jne 0x93474 */
  /* test (char)eax, 0x41 -> jne 0x93472 */
  /* test (char)eax, 0x41 -> jne 0x93474 */
  pixel32_to_real_argb_color(ecx, (float *)(uintptr_t)eax);
  /* test (char)eax, 0x41 -> jne 0x934ec */
  /* test (char)eax, 0x41 -> jne 0x93503 */
  /* test (char)eax, 0x41 -> jne 0x9351a */
  draw_string_set_font(0, 0, 0, 0, (void *)0);
  /* test eax, eax -> jge 0x9355f */
  /* cmp ecx, eax -> jg 0x9359a */
  rasterizer_text_set_shadow_color((void *)(uintptr_t)eax);
  FUN_0019d420(0, 0);
  rasterizer_draw_string((void *)(uintptr_t)ebx, (void *)0, (void *)0, 0, (void *)(uintptr_t)eax);
  rasterizer_text_set_shadow_color((void *)0);
  game_time_get_paused();
  /* test (char)eax, (char)eax -> je 0x935df */
  game_time_get_elapsed();
  game_in_editor();
  /* test (char)eax, (char)eax -> jne 0x9361b */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}


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
void FUN_00118be0(void *definition, void *data, int count);

/* FUN_00093710 (0x93710) — readable C lift from XBE leaf. */
void FUN_00093710(int *cursor, unsigned char mode)
{
  int i;
  int limit;
  int *entry;

  i = 0;
  for (;;) {
    limit = (int)mode;
    if (mode <= 1)
      limit = 1;
    if ((short)i >= limit)
      break;
    entry = *(int **)(0x2ee950 + (int)(short)i * 4);
    if (entry[1] != -1) {
      do {
        FUN_00118be0((void *)entry[0], (void *)*cursor, 1);
        *cursor += entry[1];
        entry += 3;
      } while (entry[1] != -1);
    }
    i++;
  }
}

/* FUN_00093780 (0x93780) — readable C lift from XBE leaf. */
void FUN_00093780(void *base, void **cursor, unsigned char mode)
{
  int i;
  int limit;
  int *rec;
  int size;
  int offset;

  csmemset(base, 0, 0x40);
  *(short *)((char *)base + 8) = (short)0xffff;
  limit = mode;
  if (limit <= 1) {
    limit = 1;
  }
  for (i = 0; i < limit; i++) {
    rec = (int *)(*(int *)(0x2ee950 + i * 4) + 4);
    if (rec[0] == -1) {
      continue;
    }
    do {
      offset = rec[1];
      size = rec[0];
      if (offset != -1) {
        csmemcpy((char *)base + offset, *cursor, (size_t)size);
      }
      *cursor = (char *)*cursor + size;
      rec += 3;
    } while (rec[0] != -1);
  }
}




/* FUN_00093810 (0x93810) — readable C lift from XBE leaf. */
void FUN_00093810(void *base, void **cursor, unsigned char mode)
{
  int i;
  int limit;
  int *rec;
  int size;

  limit = mode;
  if (limit <= 1) {
    limit = 1;
  }
  for (i = 0; i < limit; i++) {
    rec = (int *)(*(int *)(0x2ee950 + i * 4) + 4);
    size = rec[0];
    if (size == -1) {
      continue;
    }
    do {
      csmemcpy(*cursor, (char *)base + rec[1], (size_t)size);
      *cursor = (char *)*cursor + size;
      rec += 3;
      size = rec[0];
    } while (size != -1);
  }
}




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


/* FUN_00093e20 (0x93e20) — readable C lift (restored pre-naked). */
void FUN_00093e20(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  display_assert((char *)0x002690a0, (char *)0x002690a8, 160, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x93e7e */
  display_assert((char *)0x00265d1c, (char *)0x002690a8, 162, 0);
  system_exit(0);
  /* cmp dl, 0x3c -> jb 0x93e98 */
  /* cmp eax, 8 -> jl 0x93eb8 */
  display_assert((char *)0x00269238, (char *)0x002690a8, 163, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 0x3e8 -> jle 0x93ef0 */
  /* cmp (int16_t)eax, 0xfc18 -> jge 0x93efe */
  angles_to_vector((float *)0, (float *)0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x93f70 */
  ((void(*)(void))FUN_00093ba0)();
  ((void(*)(void))FUN_00093be0)();
  /* test (int16_t)eax, (int16_t)eax -> je 0x93fc3 */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x93ff4 */
  ((void(*)(void))FUN_00093ba0)();
  ((void(*)(void))FUN_00093be0)();
  FUN_00093780(0, (void *)(uintptr_t)esi, 0);
  /* test eax, eax -> jne 0x940ca */
  display_assert((char *)0x002690a0, (char *)0x002690a8, 275, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x940f1 */
  display_assert((char *)0x00269368, (char *)0x002690a8, 276, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x9411a */
  display_assert((char *)0x00269358, (char *)0x002690a8, 277, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi], 0 -> jne 0x9413f */
  display_assert((char *)0x00269344, (char *)0x002690a8, 278, 0);
  system_exit(0);
  /* cmp eax, 3 -> ja 0x941b9 */
  /* cmp (int16_t)ebx, 0xff -> jbe 0x941d9 */
  display_assert((char *)0x00255ee8, (char *)0x002690a8, 309, 0);
  system_exit(0);
  /* cmp edx, eax -> jl 0x94254 */
  /* cmp (char)eax, 4 -> je 0x94254 */
  /* cmp (char)eax, 0x5c -> jb 0x94220 */
  display_assert((char *)0x002692cc, (char *)0x002690a8, 315, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}


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

