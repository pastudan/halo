#include "x87_math.h"

/* hud_draw_element_wrapper (0xd3fa0)
 * Wraps FUN_000d3080 with crosshair_overlay=0, passing through remaining
 * params. */
void FUN_000d3fa0(int param_1, short *param_2, int param_3, int param_4,
                  int param_5, int param_6, int param_7, int param_8,
                  int param_9, int param_10)
{
  FUN_000d3080(param_4, param_3, param_1, 0, param_2, *(float *)&param_5,
               param_6, param_7, param_8, param_9, param_10);
}

/* hud_draw_element (0xd3fe0)
 * Draw a HUD element with bitmap lookup, texture caching, and stack canary. */
void FUN_000d3fe0(int param_1, short *param_2, int param_3,
                  unsigned int param_4, int param_5)
{
  int iVar1;
  int iVar2;
  float *puVar3;
  int uVar4;
  char cVar5;
  short sVar6;
  int draw_flag;
  float scale[2];
  float icon_rect[4];
  int local_24c[128];
  unsigned char local_4c[16];
  unsigned int local_24;
  int local_20;
  int local_1c;
  unsigned char local_18[4];
  int local_14;
  int local_10;
  int local_c;
  short *local_8;

  local_20 = FUN_000d1540();
  csmemset(local_24c, 0x62, 0x200);
  iVar1 = verify_tag_reference((int *)(param_3 + 0x24));
  local_8 = (short *)tag_get(0x6269746d, iVar1);
  local_c = (int)FUN_00077040(*(int *)(param_3 + 0x30),
                              *(short *)(param_3 + 0x54), 0);
  iVar2 = (int)xbox_texture_cache_get_hardware_format((void *)local_c, 0, 1);
  if (iVar2 != 0) {
    puVar3 = (float *)FUN_000d1580(
        verify_tag_reference((int *)(param_3 + 0x24)),
        *(short *)(param_3 + 0x54), 0);
    if ((param_4 & 2) == 0) {
      if ((param_4 & 1) == 0) {
        uVar4 = *(int *)(param_3 + 0x34);
      } else {
        uVar4 = FUN_000d2320((int *)(param_3 + 0x34), param_5);
      }
    } else {
      uVar4 = *(int *)(param_3 + 0x4c);
    }
    sVar6 = *local_8;
    local_14 = (sVar6 == 4);
    FUN_000d3080((int)puVar3, (int)param_3, local_c, 0, param_2, 1.0f, 0,
                 uVar4, (param_4 >> 2) & 0xffffff01, (char)local_14, 0);
    local_8 = (short *)0;
    if (0 < *(int *)(param_3 + 0x58)) {
      iVar2 = 0;
      local_24 = param_4 & 4;
      icon_rect[0] = 0.0f;
      icon_rect[2] = 0.0f;
      cVar5 = (char)(sVar6 == 4);
      while (1) {
        local_1c = (int)tag_block_get_element((void *)(param_3 + 0x58), iVar2,
                                              0x1e0);
        icon_rect[1] = 1.0f;
        icon_rect[3] = 1.0f;
        if (cVar5 != '\0') {
          local_10 = (int)*(short *)(local_c + 6);
          icon_rect[1] = (float)(int)*(short *)(local_c + 4);
          icon_rect[3] = (float)local_10;
        }
        if (puVar3 == (float *)0) {
          puVar3 = icon_rect;
        }
        scale[0] = *(float *)(param_3 + 4);
        scale[1] = *(float *)(param_3 + 8);
        if (((short)local_24 == 0) ||
            (draw_flag = 1, (*(unsigned char *)(param_3 + 0xc) & 1) != 0)) {
          draw_flag = 0;
        }
        FUN_000d1f40((short)*(int *)0x506548, (unsigned short *)param_2,
                     (short *)param_3, 0, draw_flag, 0, (short *)local_18);
        /* d1890: =local_4c (out corners), =puVar3 (in rect),
         * =cVar5 (align flag); 2 stack args: bitmap, screen index. */
        FUN_000d1890((float *)local_4c, puVar3, cVar5, (short *)local_c, *param_2);
        /* d27a0: =local_1c (element ptr), =scale[2];
         * 6 stack args; 6th = uVar4 (color, raw int bitpattern). */
        FUN_000d27a0(local_1c, scale, param_1, local_18, puVar3,
                     (float *)local_4c, 0, uVar4);
        iVar2 = iVar2 + 1;
        iVar2 = (int)(short)iVar2;
        if (*(int *)(param_3 + 0x58) <= iVar2) break;
        cVar5 = (char)local_14;
      }
    }
  }
  (void)scale; (void)local_1c;
  sVar6 = 0x7f;
  do {
    if (local_24c[(int)sVar6] != 0x62626262) goto LAB_000d41e7;
    sVar6 = sVar6 - 1;
  } while (-1 < sVar6);
  sVar6 = -1;
LAB_000d41e7:
  iVar2 = FUN_000d1540();
  if (local_20 != iVar2) {
    display_assert("corrupt return address!",
                   "c:\\halo\\SOURCE\\interface\\hud_draw.c", 0x2ad, 1);
    system_exit(-1);
  }
  if (sVar6 != -1) {
    display_assert(
      csprintf((char *)0x5ab100, "corrupt stack at %d!", (int)sVar6),
      "c:\\halo\\SOURCE\\interface\\hud_draw.c", 0x2ad, 1);
    system_exit(-1);
  }
}

/* hud_draw_overlay_elements (0xd4260)
 * Draw overlay bitmap elements for a HUD widget. Iterates over the overlay
 * element tag block, performs bitmap lookup with optional animation cycling,
 * optional color interpolation, and renders each visible element via
 * FUN_000d3080. Protected by a stack canary (0x200 bytes of 0x62). */
void FUN_000d4260(int param_1, int param_2, int param_3,
                  unsigned int param_4, int param_5, unsigned char param_6,
                  int param_7)
{
  int element;
  int bitmap_seq;
  int color;
  int frame_idx;
  int iVar1;
  short sVar5;
  int local_214[128];
  int local_14;
  int out_sprite;
  int out_bitmap;
  int local_4;

  local_14 = FUN_000d1540();
  csmemset(local_214, 0x62, 0x200);
  local_4 = 0;
  if (0 < *(int *)(param_3 + 0x10)) {
    do {
      element = (int)tag_block_get_element((void *)(param_3 + 0x10), local_4,
                                           0x88);
      if ((*(unsigned char *)(element + 0x4c) & 2) == 0 &&
          (param_4 & (int)*(short *)(element + 0x4a)) != 0) {
        bitmap_seq = (int)tag_block_get_element(
          (void *)((int)tag_get(0x6269746d, *(int *)(param_3 + 0xc)) + 0x54),
          (int)*(short *)(element + 0x48), 0x40);
        if ((*(unsigned char *)(element + 0x4c) & 1) == 0 ||
            (param_6 & 1) == 0) {
          color = *(int *)(element + 0x24);
        } else {
          color = FUN_000d2320((int *)(element + 0x24), param_5);
        }
        if ((*(unsigned char *)(element + 0x4c) & 1) == 0 ||
            (param_6 & 1) == 0 || *(short *)(element + 0x44) < 1) {
          frame_idx = 0;
        } else {
          frame_idx =
            ((game_time_get() - param_5) / (int)*(short *)(element + 0x44)) /
              30 %
            *(int *)(bitmap_seq + 0x34);
        }
        out_bitmap = 0;
        out_sprite = 0;
        FUN_000d16a0(*(int *)(param_3 + 0xc),
                     *(unsigned short *)(element + 0x48), frame_idx,
                     &out_bitmap, &out_sprite);
        if (out_bitmap != 0 &&
            (int)xbox_texture_cache_get_hardware_format((void *)out_bitmap, 0,
                                                        1) != 0) {
          FUN_000d3080(out_sprite, element, out_bitmap, 0, (short *)param_2,
                       1.0f, 0, color, param_7, 0, 0);
        }
      }
      local_4 = local_4 + 1;
    } while (local_4 < *(int *)(param_3 + 0x10));
  }
  sVar5 = 0x7f;
  do {
    if (local_214[(int)sVar5] != 0x62626262) goto LAB_000d43f5;
    sVar5 = sVar5 - 1;
  } while (-1 < sVar5);
  sVar5 = -1;
LAB_000d43f5:
  iVar1 = FUN_000d1540();
  if (local_14 != iVar1) {
    display_assert("corrupt return address!",
                   "c:\\halo\\SOURCE\\interface\\hud_draw.c", 0x2ec, 1);
    system_exit(-1);
  }
  if (sVar5 != -1) {
    display_assert(
      csprintf((char *)0x5ab100, "corrupt stack at %d!", (int)sVar5),
      "c:\\halo\\SOURCE\\interface\\hud_draw.c", 0x2ec, 1);
    system_exit(-1);
  }
}

/* hud_draw_text_element (0xd4470)
 * Draw a text element on the HUD, with optional icon rendering.
 * ABI: @esi=src_rect, @edi=dst_rect, @ebx=text, stack: param_1=use_icons */
void FUN_000d4470(char param_1, short *src_rect, short *dst_rect, void *text)
{
  short local_8[4];

  draw_string_set_indents(
    (int)(unsigned short)src_rect[1] - (int)(unsigned short)dst_rect[1], 0);
  FUN_0019cdb0(dst_rect, text, local_8, src_rect);
  src_rect[1] = src_rect[1] - 3;
  local_8[1] = dst_rect[1];
  if (param_1 != '\0') {
    if (game_engine_running() != '\0') {
      draw_string_and_hack_in_icons(local_8, 0, 0, 0, (wchar_t *)text, 1);
      *dst_rect = *src_rect;
      return;
    }
  }
  rasterizer_draw_string(local_8, 0, 0, 0, (unsigned short *)text);
  *dst_rect = *src_rect;
}

/* hud_draw_icon_sprite (0xd44f0)
 * Look up a bitmap element and draw it as a sprite.
 * ABI: @esi=element, @ebx=cursor */
void FUN_000d44f0(int cursor, short *element, int param_1, int param_2)
{
  int iVar4;
  short sVar2;
  int local_14;
  short local_10[2];
  int local_c;
  int local_8;
  float scale;

  iVar4 = 0;
  local_c = 0;
  local_14 = 0;
  if (*(char *)((int)element + 12) != '\0') {
    iVar4 = game_time_get();
    iVar4 = iVar4 / (int)*(char *)((int)element + 12);
  }
  FUN_000d16a0(*(int *)(*(int *)0x46bd0c + 0xb0), *element, iVar4, &local_c,
               &local_14);
  if (local_c != 0 &&
      (int)xbox_texture_cache_get_hardware_format((void *)local_c, 0, 1) != 0) {
    sVar2 = local_player_count();
    local_8 = 0x3f400000;
    if (sVar2 < 2) {
      local_8 = 0x3f800000;
    }
    scale = *(float *)&local_8;
    local_10[0] = (short)((float)(int)element[2] * scale +
                          (float)(int)*(short *)(cursor + 2));
    local_10[1] = (short)((float)(int)*(short *)(cursor + 4) -
                          (float)(int)element[3] * scale);
    if ((*(unsigned char *)((int)element + 0xd) & 2) != 0) {
      param_2 = *(int *)(element + 4);
    }
    FUN_000d3200(local_c, 2, local_10, local_14, scale, 0,
                 param_2, 0);
    if ((*(unsigned char *)((int)element + 0xd) & 4) != 0) {
      *(short *)(cursor + 2) = (short)((float)(int)element[1] * scale +
                                        (float)(int)local_10[0]);
      return;
    }
    if (local_14 != 0) {
      int *rect = (int *)local_14;
      float rect_w = *(float *)(rect + 1) - *(float *)rect;
      *(short *)(cursor + 2) =
          (short)(((float)(int)*(short *)(local_c + 4) * rect_w +
                   (float)(int)element[1]) * scale +
                  (float)(int)local_10[0]);
      return;
    }
    *(short *)(cursor + 2) =
        (short)((float)((int)*(short *)(local_c + 4) +
                        (int)element[1]) * scale +
                (float)(int)local_10[0]);
  }
}

/* HUD message display system. */

/* hud_messaging_initialize (0xd4680) — readable C lift. */
extern char DAT_00281ac4[];
void hud_messaging_initialize(void)
{
  *(void **)0x46bd18 = game_state_malloc(DAT_00281ac4, NULL, 0x11a8);
}

/* FUN_000d46a0 (0xd46a0)
 * Sets the player globals pointer and zeroes the hud messaging buffer. */
void FUN_000d46a0(void)
{
  void *buf;
  int val;
  buf = *(void **)0x46bd18;
  val = *(int *)0x46bd0c;
  *(int *)0x5aa68c = val;
  csmemset(buf, 0, 0x11a8);
}

/* FUN_000d46d0 (0xd46d0)
 * Shared RET stub, tail-called from hud_dispose_from_old_map. Empty body. */
void FUN_000d46d0(void)
{
}

/* FUN_000d46e0 (0xd46e0)
 * Shared RET stub, tail-called from hud_dispose. Empty body. */
void FUN_000d46e0(void)
{
}

/* hud_set_state_message (0xd4d90) — XBE naked draft (batch 91). */
#if defined(__clang__)
static void *(*const bd4d90_tag)(int, int) = tag_get;
static void *(*const bd4d90_elem)(void *, int, int) = tag_block_get_element;

__attribute__((naked, noinline))
void hud_set_state_message(short param_1, short param_2)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x46bd10, %%eax\n\t"
      "movb 0x1(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lhud_set_state_message_3\n\t"
      "movl 0x46bd0c, %%ecx\n\t"
      "movl 0xfc(%%ecx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lhud_set_state_message_3\n\t"
      "movl 0x46bd18, %%edx\n\t"
      "pushl %%esi\n\t"
      "movswl 0x8(%%ebp), %%esi\n\t"
      "imull $0x460, %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "addl %%edx, %%esi\n\t"
      "cmpw $-1, %%di\n\t"
      "je .Lhud_set_state_message_2\n\t"
      "pushl %%eax\n\t"
      "pushl $0x686d7420\n\t"
      "call *%[tag]\n\t"
      "movl 0x20(%%eax), %%edx\n\t"
      "addl $0x20, %%eax\n\t"
      "movswl %%di, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jge .Lhud_set_state_message_1\n\t"
      "pushl $0x40\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $-1, %%di\n\t"
      "setne %%dl\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x454(%%esi)\n\t"
      "movb $0, 0x459(%%esi)\n\t"
      "movb %%dl, 0x458(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lhud_set_state_message_1:\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "cmpw $-1, %%di\n\t"
      ".Lhud_set_state_message_2:\n\t"
      "setne %%dl\n\t"
      "popl %%edi\n\t"
      "movb %%dl, 0x458(%%esi)\n\t"
      "popl %%esi\n\t"
      ".Lhud_set_state_message_3:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(bd4d90_tag), [elem] "m"(bd4d90_elem)
      : "memory");
}
#else
#error "hud_set_state_message: clang naked draft required"
#endif


/* scripted_hud_set_flashing_state (0xd4740)
 * Sets the flashing state flag and records the game tick. */
void scripted_hud_set_flashing_state(char param_1)
{
  int base;

  if (param_1 != '\0' && *(char *)(*(int *)0x46bd18 + 0x1184) == '\0') {
    *(int *)(*(int *)0x46bd18 + 0x1180) = game_time_get();
    base = *(int *)0x46bd18;
    *(char *)(base + 0x1184) = param_1;
    return;
  }
  *(char *)(*(int *)0x46bd18 + 0x1184) = param_1;
}

/* scripted_hud_restart_flashing (0xd4780)
 * Resets the flashing timer if flashing is enabled. */
void scripted_hud_restart_flashing(void)
{
  if (*(char *)(*(int *)0x46bd18 + 0x1184) != '\0') {
    *(int *)(*(int *)0x46bd18 + 0x1180) = game_time_get();
    return;
  }
  error(2, "trying to restart help text flashing when flashing is disabled");
}

/* scripted_hud_set_objective (0xd47c0)
 * Sets the objective text from the HMT tag if it's text-only. */
void scripted_hud_set_objective(short param_1)
{
  int scenario;
  int hmt;
  int element;
  char *pcVar;
  int base;
  int globals;

  scenario = (int)global_scenario_get();
  if (*(int *)(scenario + 0x5a0) != -1) {
    hmt = (int)tag_get(0x686d7420, *(int *)(scenario + 0x5a0));
    element =
      (int)tag_block_get_element((void *)(hmt + 0x20), (int)param_1, 0x40);
    pcVar = (char *)tag_block_get_element(
      (void *)(hmt + 0x14), *(unsigned short *)(element + 0x22), 2);
    base = *(int *)0x46bd18;
    globals = *(int *)0x46bd0c;
    if (*(char *)(element + 0x24) == 1 && *pcVar == '\0') {
      *(int *)(*(int *)0x46bd18 + 0x1190) = element;
      *(short *)(base + 0x1194) =
        *(short *)(globals + 0x11e) + *(short *)(globals + 0x11c);
      return;
    }
    error(2, "objective text MUST only be text, no icons");
  }
}

/* scripted_hud_set_timer_time (0xd4860)
 * Sets the timer countdown value in ticks and records current tick. */
void scripted_hud_set_timer_time(short param_1, short param_2)
{
  int base;
  int tick;
  short sVar;

  base = *(int *)0x46bd18;
  *(short *)(base + 0x119c) = (param_1 * 0x3c + param_2) * 0x1e;
  *(unsigned char *)(base + 0x11a6) = 0;
  *(unsigned char *)(base + 0x11a7) = 1;
  tick = game_time_get();
  base = *(int *)0x46bd18;
  *(int *)(base + 0x1198) = tick;
  sVar = *(short *)(base + 0x11a4);
  if (sVar < 0) {
    *(short *)(base + 0x11a4) = 0;
    return;
  }
  if (4 < sVar) {
    *(short *)(base + 0x11a4) = 4;
    return;
  }
  *(short *)(base + 0x11a4) = sVar;
}

/* scripted_hud_set_timer_warning_cutoff (0xd48e0)
 * Sets the warning cutoff time in ticks. */
void scripted_hud_set_timer_warning_cutoff(short param_1, short param_2)
{
  *(short *)(*(int *)0x46bd18 + 0x119e) = (param_1 * 60 + param_2) * 30;
}

/* scripted_hud_set_timer_position (0xd4900)
 * Sets the timer position on screen. */
void scripted_hud_set_timer_position(short param_1, short param_2,
                                     short param_3)
{
  int base;

  base = *(int *)0x46bd18;
  *(short *)(base + 0x11a0) = param_1;
  *(short *)(base + 0x11a2) = param_2;
  if (param_3 < 0) {
    *(short *)(base + 0x11a4) = 0;
    return;
  }
  if (param_3 > 4) {
    *(short *)(base + 0x11a4) = 4;
    return;
  }
  *(short *)(base + 0x11a4) = param_3;
}

/* scripted_hud_show_timer (0xd4960)
 * Shows or hides the HUD timer. */
void scripted_hud_show_timer(unsigned char param_1)
{
  *(unsigned char *)(*(int *)0x46bd18 + 0x11a7) = param_1;
}

/* scripted_hud_pause_timer (0xd4980)
 * Pauses or unpauses the HUD timer, adjusting remaining ticks. */
void scripted_hud_pause_timer(char param_1)
{
  int base;
  short now;

  base = *(int *)0x46bd18;
  *(char *)(base + 0x11a6) = param_1;
  if (*(short *)(base + 0x119c) > 0) {
    if (param_1 != '\0') {
      now = (short)game_time_get();
      *(short *)(base + 0x119c) += *(short *)(base + 0x1198) - now;
      return;
    }
    now = (short)game_time_get();
    *(short *)(base + 0x119c) += now - *(short *)(base + 0x1198);
  }
}

/* scripted_hud_get_timer_ticks (0xd49d0)
 * Returns remaining timer ticks, or 0 if hidden. */
short scripted_hud_get_timer_ticks(void)
{
  int base;
  short result;

  base = *(int *)0x46bd18;
  result = 0;
  if (*(char *)(base + 0x11a7) != '\0') {
    result = *(short *)(base + 0x119c);
    if (result == -1) {
      return -1;
    }
    if (*(char *)(base + 0x11a6) == '\0') {
      result = (short)game_time_get();
      result = (*(short *)(base + 0x119c) + *(short *)(base + 0x1198)) - result;
    }
  }
  return result;
}

/* scripted_hud_time_code_show (0xd4a20) — XBE naked draft (batch 101). */
#if defined(__clang__)
static int (*const bd4a20_gtime)(void) = game_time_get;

__attribute__((naked, noinline))
void scripted_hud_time_code_show(char param_1)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movb 0x8(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lscripted_hud_time_code_show_1\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, 0x2f66e4\n\t"
      "movl %%eax, 0x2f66e8\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lscripted_hud_time_code_show_1:\n\t"
      "movl $0xffffffff, 0x2f66e4\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [gtime] "m"(bd4a20_gtime)
      : "memory");
}
#else
#error "scripted_hud_time_code_show: clang naked draft required"
#endif


/* scripted_hud_time_code_start (0xd4a50) — XBE naked draft (batch 99). */
#if defined(__clang__)
static int (*const bd4a50_gtime)(void) = game_time_get;

__attribute__((naked, noinline))
void scripted_hud_time_code_start(char param_1)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movb 0x8(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lscripted_hud_time_code_start_1\n\t"
      "call *%[gtime]\n\t"
      "movl 0x2f66e8, %%edx\n\t"
      "movl 0x2f66e4, %%ecx\n\t"
      "subl %%edx, %%eax\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl %%ecx, 0x2f66e4\n\t"
      "movl $0xffffffff, 0x2f66e8\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lscripted_hud_time_code_start_1:\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, 0x2f66e8\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [gtime] "m"(bd4a50_gtime)
      : "memory");
}
#else
#error "scripted_hud_time_code_start: clang naked draft required"
#endif


/* scripted_hud_time_code_reset (0xd4a90) — XBE naked draft (batch 102). */
#if defined(__clang__)
static int (*const bd4a90_gtime)(void) = game_time_get;

__attribute__((naked, noinline))
void scripted_hud_time_code_reset(void)
{
  __asm__ volatile(
      "call *%[gtime]\n\t"
      "cmpl $-1, 0x2f66e8\n\t"
      "movl %%eax, 0x2f66e4\n\t"
      "je .Lscripted_hud_time_code_reset_1\n\t"
      "movl %%eax, 0x2f66e8\n\t"
      ".Lscripted_hud_time_code_reset_1:\n\t"
      "ret\n\t"
      :
      : [gtime] "m"(bd4a90_gtime)
      : "memory");
}
#else
#error "scripted_hud_time_code_reset: clang naked draft required"
#endif



/* hud_render_timer (0xd4ab0) */
void hud_render_timer(void)
{
  int iVar10;
  int *piVar7;
  int iVar6;
  int iVar8;
  int *puVar9;
  int *puVar11;
  short uVar1;
  short sVar2;
  short local_90;
  int local_8e[8];
  short local_8e_tail;
  int local_68;
  float local_64;
  float local_60;
  int local_48[8];
  char local_28;
  char local_27;
  char local_26;
  char pad_21;
  double local_14;
  int local_10;
  int local_c;
  int local_8;
  int local_4;
  int loading_time;

  iVar10 = *(int *)0x46bd18;
  piVar7 = (int *)(iVar10 + 0x1198);
  if (*(char *)(iVar10 + 0x11a7) != '\0') {
    local_90 = *(short *)(iVar10 + 0x11a4);
    csmemset(local_8e, 0, 34);
    local_8 = game_time_get();
    iVar8 = 0;
    local_c = 0;
    local_10 = (int)scripted_hud_get_timer_ticks();
    local_68 = *(int *)(iVar10 + 0x11a0);
    *(volatile char *)&local_28 = 2;
    *(volatile char *)&local_26 = 4;
    *(volatile char *)&local_27 = 1;
    *(volatile float *)&local_64 = 1.0f;
    *(volatile float *)&local_60 = 1.0f;
    (void)local_8e_tail;
    (void)pad_21;
    iVar6 = interface_get_tag_index(0xb);
    if (iVar6 != -1) {
      iVar6 = (int)tag_get(0x68756423, iVar6);
      local_c = (int)*(char *)(iVar6 + 0x11);
      iVar8 = (int)((double)local_c * 2.0);
      local_c = iVar8;
    }
    switch (*(short *)(iVar10 + 0x11a4)) {
    case 0:
    case 2:
      break;
    case 1:
    case 3:
      *(short *)&local_68 = (short)(*(short *)&local_68 + (short)iVar8 * 5);
      local_c = -iVar8;
      break;
    case 4:
      *(short *)&local_68 = (short)(*(short *)&local_68 + (short)iVar8 * -3);
      break;
    default:
      display_assert("!\"unreachable\"",
                     "c:\\halo\\SOURCE\\interface\\hud_messaging.c", 0x1f8, 1);
      system_exit(-1);
    }
    iVar6 = 8;
    if ((short)local_10 > 0) {
      uVar1 = (short)local_10;
      puVar9 = (int *)(*(int *)0x46bd0c + 0x360);
      puVar11 = local_48;
      for (; iVar6 != 0; iVar6 = iVar6 - 1) {
        *puVar11 = *puVar9;
        puVar9 = puVar9 + 1;
        puVar11 = puVar11 + 1;
      }
      sVar2 = *(short *)(iVar10 + 0x119e);
      iVar6 = local_c;
      if ((short)uVar1 <= sVar2) {
        iVar6 = 1;
        if (sVar2 < *(short *)(iVar10 + 0x119c)) {
          *(short *)(iVar10 + 0x119c) = sVar2;
          *piVar7 = ((int)sVar2 - (int)(short)uVar1) + local_8;
        }
      }
    } else {
      iVar8 = *piVar7;
      *(short *)(iVar10 + 0x119c) = (short)-1;
      puVar9 = (int *)(*(int *)0x46bd0c + 0x380);
      puVar11 = local_48;
      for (; iVar6 != 0; iVar6 = iVar6 - 1) {
        *puVar11 = *puVar9;
        puVar9 = puVar9 + 1;
        puVar11 = puVar11 + 1;
      }
      local_c = 1;
      if (iVar8 == -1) {
        *piVar7 = game_time_get();
      }
      uVar1 = (short)local_10;
      iVar6 = local_c;
    }
    iVar10 = (int)(short)(uVar1 & ((short)uVar1 < 1) - 1);
    local_8 = iVar10;
    local_4 = iVar10;
    iVar8 = (int)((float)local_4 * *(float *)0x2546a4 * *(float *)0x25634c);
    FUN_000d3860((short)*(int *)0x506548, &local_90, &local_68,
                 iVar8, -1, iVar6, *piVar7, 2.0f);
    local_4 = (int)(short)local_c;
    local_14 = (double)local_4 * *(double *)0x281b40;
    local_4 = (int)*(short *)&local_68;
    *(short *)&local_68 = (short)(int)((double)local_4 + local_14);
    iVar8 = (iVar10 / 30) % 60;
    FUN_000d3860((short)*(int *)0x506548, &local_90, &local_68,
                 iVar8, -1, iVar6, *piVar7, 2.0f);
    local_4 = (int)*(short *)&local_68;
    *(short *)&local_68 = (short)(int)((double)local_4 + local_14);
    iVar8 = ((iVar10 % 1800) * 100) / 30;
    FUN_000d3860((short)*(int *)0x506548, &local_90, &local_68,
                 iVar8, -1, iVar6, *piVar7, 2.0f);
  }
  if (*(int *)0x2f66e4 != -1) {
    loading_time = *(int *)0x2f66e8;
    if (loading_time == -1) {
      loading_time = game_time_get();
    }
    crt_sprintf((char *)0x5ab100, (const char *)0x25acb8,
                loading_time - *(int *)0x2f66e4);
    FUN_00189c40(1, (const char *)0x5ab100);
  }
}

/* hud_enable_custom_state_message (0xd4f00) — XBE naked draft (batch 94). */
#if defined(__clang__)
static wchar_t * (*const bd4f00_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;

__attribute__((naked, noinline))
void hud_enable_custom_state_message(short param_1, char param_2)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x46bd18, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movb 0xc(%%ebp), %%bl\n\t"
      "pushl %%esi\n\t"
      "movswl 0x8(%%ebp), %%esi\n\t"
      "imull $0x460, %%esi, %%esi\n\t"
      "movb 0x458(%%esi,%%ecx,1), %%al\n\t"
      "movb 0x45e(%%esi,%%ecx,1), %%dl\n\t"
      "addl %%ecx, %%esi\n\t"
      "cmpb %%bl, %%al\n\t"
      "setne %%al\n\t"
      "orb %%al, %%dl\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpb %%al, %%bl\n\t"
      "movb %%dl, 0x45e(%%esi)\n\t"
      "movb %%bl, 0x458(%%esi)\n\t"
      "movl %%eax, 0x454(%%esi)\n\t"
      "je .Lhud_enable_custom_state_message_1\n\t"
      "pushl $0xff\n\t"
      "leal 0x230(%%esi), %%ecx\n\t"
      "pushl $0x26cdf0\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, 0x454(%%esi)\n\t"
      "call *%[c19dc90]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lhud_enable_custom_state_message_1:\n\t"
      "movb %%bl, 0x45f(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c19dc90] "m"(bd4f00_c19dc90)
      : "memory");
}
#else
#error "hud_enable_custom_state_message: clang naked draft required"
#endif


/* hud_set_state_text (0xd4f70) — XBE naked draft (batch 99). */
#if defined(__clang__)
static wchar_t * (*const bd4f70_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;

__attribute__((naked, noinline))
void hud_set_state_text(short param_1, wchar_t *param_2)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x46bd18, %%eax\n\t"
      "pushl %%esi\n\t"
      "movswl 0x8(%%ebp), %%esi\n\t"
      "imull $0x460, %%esi, %%esi\n\t"
      "addl %%eax, %%esi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl $0xff\n\t"
      "pushl %%eax\n\t"
      "leal 0x230(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19dc90]\n\t"
      "addl $0xc, %%esp\n\t"
      "movw $0, 0x42e(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c19dc90] "m"(bd4f70_c19dc90)
      : "memory");
}
#else
#error "hud_set_state_text: clang naked draft required"
#endif


/* hud_messaging_get_objective (0xd4fb0) — XBE naked draft (batch 90). */
#if defined(__clang__)
static scenario_t * (*const bd4fb0_c18e380)(void) = global_scenario_get;
static void *(*const bd4fb0_tag)(int, int) = tag_get;
static void *(*const bd4fb0_elem)(void *, int, int) = tag_block_get_element;
static void (*const bd4fb0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bd4fb0_exitfn)(int) = system_exit;
static void * (*const bd4fb0_c19b1a0)(void *tag_data, int offset, int size) = tag_data_get_pointer;

__attribute__((naked, noinline))
int hud_messaging_get_objective(void)
{
  __asm__ volatile(
      "movl 0x46bd18, %%ecx\n\t"
      "movl 0x1190(%%ecx), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%edx, %%edx\n\t"
      "je .Lhud_messaging_get_objective_3\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c18e380]\n\t"
      "movl 0x5a0(%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x686d7420\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x46bd18, %%eax\n\t"
      "movl 0x1190(%%eax), %%esi\n\t"
      "movzwl 0x22(%%esi), %%ecx\n\t"
      "pushl $2\n\t"
      "pushl %%ecx\n\t"
      "leal 0x14(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movb 0x24(%%esi), %%al\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpb $1, %%al\n\t"
      "je .Lhud_messaging_get_objective_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2a1\n\t"
      "pushl $0x281b48\n\t"
      "pushl $0x281b9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lhud_messaging_get_objective_1:\n\t"
      "cmpb $0, (%%ebx)\n\t"
      "je .Lhud_messaging_get_objective_2\n\t"
      "pushl $1\n\t"
      "pushl $0x2a2\n\t"
      "pushl $0x281b48\n\t"
      "pushl $0x281b74\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lhud_messaging_get_objective_2:\n\t"
      "movzbl 0x1(%%ebx), %%eax\n\t"
      "movzwl 0x20(%%esi), %%ecx\n\t"
      "shll $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "shll $1, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c19b1a0]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".Lhud_messaging_get_objective_3:\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(bd4fb0_c18e380), [tag] "m"(bd4fb0_tag), [elem] "m"(bd4fb0_elem), [assert] "m"(bd4fb0_assert), [exitfn] "m"(bd4fb0_exitfn), [c19b1a0] "m"(bd4fb0_c19b1a0)
      : "memory");
}
#else
#error "hud_messaging_get_objective: clang naked draft required"
#endif


/* hud_set_state_message_icon (0xd4e30) — XBE naked draft (batch 95). */
#if defined(__clang__)


__attribute__((naked, noinline))
void hud_set_state_message_icon(short param_1, short param_2, int param_3)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "movl 0x46bd18, %%edx\n\t"
      "imull $0x460, %%eax, %%eax\n\t"
      "movb 0x458(%%eax,%%edx,1), %%cl\n\t"
      "addl %%edx, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lhud_set_state_message_icon_1\n\t"
      "movl 0x46bd10, %%ecx\n\t"
      "movb 0x1(%%ecx), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .Lhud_set_state_message_icon_1\n\t"
      "movl 0x454(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Lhud_set_state_message_icon_1\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "movswl 0xc(%%ebp), %%esi\n\t"
      "movl %%edx, 0x434(%%eax,%%esi,4)\n\t"
      "movl %%esi, %%ecx\n\t"
      "movb $1, %%dl\n\t"
      "shlb %%cl, %%dl\n\t"
      "movb 0x459(%%eax), %%cl\n\t"
      "popl %%esi\n\t"
      "notb %%dl\n\t"
      "andb %%dl, %%cl\n\t"
      "movb %%cl, 0x459(%%eax)\n\t"
      ".Lhud_set_state_message_icon_1:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "hud_set_state_message_icon: clang naked draft required"
#endif


/* hud_set_state_message_text (0xd4e90) — XBE naked draft (batch 94). */
#if defined(__clang__)


__attribute__((naked, noinline))
void hud_set_state_message_text(short param_1, short param_2, short param_3, unsigned char param_4)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "movl 0x46bd18, %%edx\n\t"
      "imull $0x460, %%eax, %%eax\n\t"
      "movb 0x458(%%eax,%%edx,1), %%cl\n\t"
      "addl %%edx, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lhud_set_state_message_text_1\n\t"
      "movl 0x46bd10, %%ecx\n\t"
      "movb 0x1(%%ecx), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .Lhud_set_state_message_text_1\n\t"
      "movl 0x454(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Lhud_set_state_message_text_1\n\t"
      "movw 0x10(%%ebp), %%dx\n\t"
      "movb 0x14(%%ebp), %%cl\n\t"
      "pushl %%esi\n\t"
      "movswl 0xc(%%ebp), %%esi\n\t"
      "movw %%dx, 0x434(%%eax,%%esi,4)\n\t"
      "movb %%cl, 0x436(%%eax,%%esi,4)\n\t"
      "movl %%esi, %%ecx\n\t"
      "movb $1, %%dl\n\t"
      "shlb %%cl, %%dl\n\t"
      "movb 0x459(%%eax), %%cl\n\t"
      "popl %%esi\n\t"
      "orb %%dl, %%cl\n\t"
      "movb %%cl, 0x459(%%eax)\n\t"
      ".Lhud_set_state_message_text_1:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "hud_set_state_message_text: clang naked draft required"
#endif


/* Find a message slot in the 4-entry array at base (each 0x8c bytes).
 * Prefers: exact match (tag_handle + param2), then free slot, then oldest.
 * tag_handle passed in ESI (register arg). */
void *hud_find_message_slot(int base, int param2, int tag_handle /*  */)
{
  int16_t i;
  int16_t best_index;
  int best_time;
  void *result;
  char *entry;

  i = 0;
  best_index = 0;
  best_time = 0x7fffffff;
  result = (void *)0;

  do {
    entry = (char *)(base + (int)i * 0x8c);

    if ((tag_handle == -1 || tag_handle != *(int *)(entry + 0x84) ||
         (char)param2 != *(char *)(entry + 0x8a)) &&
        *(char *)(entry + 0x82) != 0) {
      int time_val = *(int *)entry;
      if (time_val < best_time) {
        best_time = time_val;
        best_index = i;
      }
    } else {
      result = (void *)entry;
      if (tag_handle == -1 || tag_handle == *(int *)(entry + 0x84))
        break;
    }

    i++;
  } while ((uint16_t)i < 4);

  if (result == (void *)0) {
    result = (void *)(base + (int)best_index * 0x8c);
  }
  return result;
}

/* hud_messaging_slot_compare (0xd50f0) — readable C lift. */
int hud_messaging_slot_compare(const void *a, const void *b)
{
  int delta;

  delta = *(const int *)b - *(const int *)a;
  if (delta != 0)
    return delta;
  delta = *(const int *)((const char *)b + 0x84) - *(const int *)((const char *)a + 0x84);
  if (delta != 0)
    return delta;
  return (int)*(const unsigned char *)((const char *)b + 0x83) -
         (int)*(const unsigned char *)((const char *)a + 0x83);
}

/* Clear all scripted HUD message slots across all 4 players x 4 slots. */
_BYTE *scripted_hud_messages_clear(void)
{
  char *base = *(char **)0x46bd18 + 0x82;
  int player, slot;

  for (player = 0; player < 4; player++) {
    char *p = base;
    for (slot = 0; slot < 4; slot++) {
      *p = 0;
      p += 0x8c;
    }
    base += 0x460;
  }
  return 0;
}

/* hud_get_font_index (0xd5160) — XBE naked draft (batch 102). */
#if defined(__clang__)
static __int16 (*const bd5160_cba4b0)(void) = local_player_count;

__attribute__((naked, noinline))
int hud_get_font_index(void)
{
  __asm__ volatile(
      "call *%[cba4b0]\n\t"
      "cmpw $1, %%ax\n\t"
      "movl 0x5aa68c, %%ecx\n\t"
      "jle .Lhud_get_font_index_1\n\t"
      "movl 0x64(%%ecx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lhud_get_font_index_2\n\t"
      ".Lhud_get_font_index_1:\n\t"
      "movl 0x54(%%ecx), %%eax\n\t"
      ".Lhud_get_font_index_2:\n\t"
      "ret\n\t"
      :
      : [cba4b0] "m"(bd5160_cba4b0)
      : "memory");
}
#else
#error "hud_get_font_index: clang naked draft required"
#endif


/* hud_get_text_color (0xd5180) — readable C lift. */
void *hud_get_text_color(void *out_argb)
{
  const uint32_t *src;

  src = (const uint32_t *)(*(uint8_t **)0x5aa68c + 0x70);
  ((uint32_t *)out_argb)[0] = src[0];
  ((uint32_t *)out_argb)[1] = src[1];
  ((uint32_t *)out_argb)[2] = src[2];
  ((uint32_t *)out_argb)[3] = src[3];
  return out_argb;
}

/* hud_messaging_globals_update (0xd51b0)
 * Resets the HUD message priority counter to 0. */
void hud_messaging_globals_update(void)
{
  *(uint8_t *)(*(char **)0x46bd18 + 0x1185) = 0;
}

/* Display a message on a player's HUD. Finds an empty message slot,
 * copies the wide string, and initializes the display timer. */
void hud_print_message(__int16 player, wchar_t *message)
{
  int base;
  char *slot;

  if (player == -1)
    return;

  base = (int)player * 0x460 + *(int *)0x46bd18;
  /* Find a message slot. ESI = -1 means "don't match any vehicle". */
  slot = (char *)hud_find_message_slot(base, 0, -1);
  ustrncpy((wchar_t *)(slot + 4), message, 0x3f);
  *(int *)(slot + 0x84) = -1;
  *(int *)slot = game_time_get();
  *(uint8_t *)(slot + 0x82) = 1;
  *(uint8_t *)(slot + 0x83) = *(uint8_t *)(*(char **)0x46bd18 + 0x1185);
  *(uint8_t *)(*(char **)0x46bd18 + 0x1185) += 1;
  *(uint8_t *)(base + 0x45e) = 0;
}

/* Set a vehicle notification on a player's HUD. Called when a player
 * enters a vehicle or changes seat. Finds a message slot via 0xd5070,
 * stores the vehicle tag handle and seat info, and initializes the
 * display timer. param_3 accumulates into the slot's counter at +0x88
 * if the slot was already active; otherwise the counter is reset first. */
void hud_messaging_set_vehicle_notification(int16_t local_player_index,
                                            int vehicle_tag_handle,
                                            int16_t param_3, int param_4)
{
  int base;
  char *slot;

  if (local_player_index == -1)
    return;

  base = (int)local_player_index * 0x460 + *(int *)0x46bd18;
  /* Find a message slot, matching vehicle tag handle via @esi. */
  slot = (char *)hud_find_message_slot(base, param_4, vehicle_tag_handle);
  if (*(uint8_t *)(slot + 0x82) == 0) {
    *(int16_t *)(slot + 0x88) = 0;
  }
  *(int16_t *)(slot + 0x88) += param_3;
  *(int *)(slot + 0x84) = vehicle_tag_handle;
  *(uint8_t *)(slot + 0x8a) = (uint8_t)param_4;
  *(int *)slot = game_time_get();
  *(uint8_t *)(slot + 0x82) = 1;
  *(uint8_t *)(slot + 0x83) = *(uint8_t *)(*(char **)0x46bd18 + 0x1185);
  *(uint8_t *)(*(char **)0x46bd18 + 0x1185) += 1;
  *(uint8_t *)(base + 0x45e) = 0;
}

/* FUN_000d52e0 (0xd52e0)
 * Sends a scripted HUD message to all local players whose object is
 * on the same team as the given actor. Iterates all 4 local player
 * slots, looks up each player's object, compares team (offset 0x20)
 * with the actor's team, and calls hud_print_message for matches.
 * Only runs if a game engine is active (game_engine_running).
 *
 * Confirmed: game_engine_running at 0xa8e30; local_player_get_player_index
 * at 0xba3c0; datum_get(0x5aa6d4) for player objects; +0x20 = team field;
 * hud_print_message at 0xd51c0. */
void FUN_000d52e0(int actor_handle, wchar_t *message)
{
  char cVar1;
  int player_obj;
  int actor_obj;
  int player_index;
  int i;

  cVar1 = game_engine_running();
  if (cVar1 != '\0') {
    i = 0;
    do {
      player_index = local_player_get_player_index((int16_t)i);
      if (player_index != -1) {
        player_obj = (int)datum_get(*(data_t **)0x5aa6d4, player_index);
        actor_obj = (int)datum_get(*(data_t **)0x5aa6d4, actor_handle);
        if (*(int *)(player_obj + 0x20) == *(int *)(actor_obj + 0x20)) {
          hud_print_message((int16_t)i, message);
        }
      }
      i++;
    } while ((int16_t)i < 4);
  }
}

/* FUN_000d5350 (0xd5350) — XBE naked draft (batch 104). */
#if defined(__clang__)
static bool (*const bd5350_c930a0)(void) = cinematic_in_progress;
static int (*const bd5350_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static char (*const bd5350_cab230)(int param_1) = FUN_000ab230;
static __int16 (*const bd5350_cba4b0)(void) = local_player_count;
static void (*const bd5350_cd1f40)(short local_player, unsigned short *absolute_placement, short *placement, int offset_struct, char flag, float in_scale, short *out) = FUN_000d1f40;
static void *(*const bd5350_tag)(int, int) = tag_get;
static void (*const bd5350_cce6c0)(short local_player_index, void *preferences_out) = input_abstraction_get_local_player_preferences;
static int (*const bd5350_gtime)(void) = game_time_get;
static uint32_t (*const bd5350_cd2320)(int *param_1, int param_2) = FUN_000d2320;
static void (*const bd5350_c7af20)(unsigned int color, float *dst) = pixel32_to_real_argb_color;
static unsigned int (*const bd5350_d1c90)(float *) = FUN_000d1c90;
static void (*const bd5350_c19b8b0)(int tag_index, int style, int justify, int flags, const void *color) = draw_string_set_font;
static void (*const bd5350_cd4470)(char param_1, short *src_rect, short *dst_rect, void *text) = FUN_000d4470;
static void (*const bd5350_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bd5350_exitfn)(int) = system_exit;
static int16_t (*const bd5350_cb5ae0)(void) = game_time_get_elapsed;
static scenario_t * (*const bd5350_c18e380)(void) = global_scenario_get;
static void *(*const bd5350_elem)(void *, int, int) = tag_block_get_element;
static int (*const bd5350_c19d420)(int param_1, int param_2) = FUN_0019d420;
static void (*const bd5350_cd44f0)(int cursor, short *element, int param_1, int param_2) = FUN_000d44f0;
static void (*const bd5350_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static int16_t (*const bd5350_ce4da0)(int16_t icon_type, int local_player_index) = remap_sticks_for_local_player;
static void (*const bd5350_c19b5d0)(int width, int height) = draw_string_set_indents;
static void (*const bd5350_c19cdb0)(short *out_rect, void *text, short *out_bounds, short *in_rect) = FUN_0019cdb0;
static void (*const bd5350_c184060)(void *screen_pos, short *bounds, const void *color, int flags, unsigned short *text) = rasterizer_draw_string;
static void * (*const bd5350_c19b1a0)(void *tag_data, int offset, int size) = tag_data_get_pointer;
static void (*const bd5350_ftol)(void) = FUN_001d9068;
static void __cdecl (*const bd5350_c1d9260)(void *base, size_t nmemb, size_t size, int (__cdecl *compar)(const void *, const void *)) = qsort;
static float (*const bd5350_c1d9e70)(float base, float exponent) = FUN_001d9e70;
static wchar_t * (*const bd5350_cd0ba0)(int a1) = hud_get_item_string;
static int (*const bd5350_c19eaa0)(wchar_t *buffer, const wchar_t *format, ...) = usprintf;

__attribute__((naked, noinline))
void FUN_000d5350(int param_1)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x2a0, %%esp\n\t"
      "call *%[c930a0]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000d5350_77\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "cmpw $-1, %%si\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_000d5350_76\n\t"
      "pushl %%esi\n\t"
      "call *%[cba3c0]\n\t"
      "pushl %%eax\n\t"
      "call *%[cab230]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000d5350_76\n\t"
      "call *%[cba4b0]\n\t"
      "cmpw $1, %%ax\n\t"
      "movl 0x5aa68c, %%ecx\n\t"
      "jle .LFUN_000d5350_1\n\t"
      "movl 0x64(%%ecx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000d5350_2\n\t"
      ".LFUN_000d5350_1:\n\t"
      "movl 0x54(%%ecx), %%eax\n\t"
      ".LFUN_000d5350_2:\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "call *%[cba4b0]\n\t"
      "leal -0x60(%%ebp), %%ecx\n\t"
      "cmpw $1, %%ax\n\t"
      "pushl %%ecx\n\t"
      "setg %%bl\n\t"
      "pushl $0\n\t"
      "movb %%bl, -0x2d(%%ebp)\n\t"
      "call *%[cba4b0]\n\t"
      "cmpw $1, %%ax\n\t"
      "movl 0x5aa68c, %%eax\n\t"
      "setg %%dl\n\t"
      "leal 0x24(%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[cd1f40]\n\t"
      "movl -0x3c(%%ebp), %%edx\n\t"
      "movl -0x5e(%%ebp), %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl $0x666f6e74\n\t"
      "call *%[tag]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x8(%%eax), %%cx\n\t"
      "addl $0x24, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_000d5350_3\n\t"
      "addw 0x4(%%eax), %%cx\n\t"
      "subl 0x2f66ec, %%edi\n\t"
      "jmp .LFUN_000d5350_4\n\t"
      ".LFUN_000d5350_3:\n\t"
      "addw 0x6(%%eax), %%cx\n\t"
      "addw 0x4(%%eax), %%cx\n\t"
      ".LFUN_000d5350_4:\n\t"
      "movswl 0x506548, %%esi\n\t"
      "movl 0x46bd18, %%eax\n\t"
      "imull $0x460, %%esi, %%esi\n\t"
      "addl %%eax, %%esi\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "movl %%esi, -0x40(%%ebp)\n\t"
      "call *%[cba4b0]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw $1, %%ax\n\t"
      "setg %%cl\n\t"
      "movl $4, %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%eax, -0x48(%%ebp)\n\t"
      "movl 0x46bd18, %%eax\n\t"
      "movl 0x1190(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_000d5350_5\n\t"
      "cmpw $0, 0x1194(%%eax)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jne .LFUN_000d5350_6\n\t"
      ".LFUN_000d5350_5:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_000d5350_6:\n\t"
      "movl 0x46bd10, %%edx\n\t"
      "movb 0x1(%%edx), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_000d5350_7\n\t"
      "movl 0x118c(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "jne .LFUN_000d5350_8\n\t"
      ".LFUN_000d5350_7:\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      ".LFUN_000d5350_8:\n\t"
      "movb 0x458(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000d5350_10\n\t"
      "movl 0x454(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000d5350_9\n\t"
      "cmpw $0, 0x230(%%esi)\n\t"
      "je .LFUN_000d5350_10\n\t"
      ".LFUN_000d5350_9:\n\t"
      "movb $1, %%al\n\t"
      "jmp .LFUN_000d5350_11\n\t"
      ".LFUN_000d5350_10:\n\t"
      "xorb %%al, %%al\n\t"
      ".LFUN_000d5350_11:\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "movb %%al, -0x19(%%ebp)\n\t"
      "jne .LFUN_000d5350_12\n\t"
      "movb -0x2(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_000d5350_12\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000d5350_53\n\t"
      ".LFUN_000d5350_12:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "leal -0xa0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x230(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "call *%[cce6c0]\n\t"
      "movb -0x1(%%ebp), %%bl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_000d5350_14\n\t"
      "movl 0x46bd0c, %%esi\n\t"
      "addl $0x100, %%esi\n\t"
      "call *%[gtime]\n\t"
      "movl 0x46bd18, %%ecx\n\t"
      "movswl 0x1194(%%ecx), %%edx\n\t"
      "movswl 0x1c(%%esi), %%ecx\n\t"
      "subl %%ecx, %%edx\n\t"
      "movswl 0x1e(%%esi), %%ecx\n\t"
      "subl %%ecx, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "leal -0x58(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[cd2320]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c7af20]\n\t"
      "movl 0x46bd18, %%eax\n\t"
      "movswl 0x1194(%%eax), %%ecx\n\t"
      "movswl 0x1e(%%esi), %%edx\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fildl -0x28(%%ebp)\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "fidivl -0x28(%%ebp)\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000d5350_13\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_000d5350_13:\n\t"
      "fmuls -0x58(%%ebp)\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "call *%[d1c90]\n\t"
      "movl -0x40(%%ebp), %%esi\n\t"
      "jmp .LFUN_000d5350_19\n\t"
      ".LFUN_000d5350_14:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000d5350_18\n\t"
      "movl 0x46bd18, %%eax\n\t"
      "movb 0x1184(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_000d5350_15\n\t"
      "movl 0x1180(%%eax), %%ecx\n\t"
      "movl 0x46bd0c, %%edx\n\t"
      "pushl %%ecx\n\t"
      "addl $0xd0, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[cd2320]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "jmp .LFUN_000d5350_17\n\t"
      ".LFUN_000d5350_15:\n\t"
      "movl 0x46bd0c, %%eax\n\t"
      "testb $1, 0xe2(%%eax)\n\t"
      "jne .LFUN_000d5350_16\n\t"
      "movl 0xd0(%%eax), %%eax\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "jmp .LFUN_000d5350_17\n\t"
      ".LFUN_000d5350_16:\n\t"
      "movl 0xd4(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      ".LFUN_000d5350_17:\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "leal -0x58(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c7af20]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000d5350_20\n\t"
      ".LFUN_000d5350_18:\n\t"
      "movl 0x5aa68c, %%ecx\n\t"
      "addl $0x70, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x58(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, -0x54(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%edx\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      "movl 0xc(%%ecx), %%eax\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "call *%[d1c90]\n\t"
      ".LFUN_000d5350_19:\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      ".LFUN_000d5350_20:\n\t"
      "movw 0x50658a, %%ax\n\t"
      "subw 0x50657e, %%ax\n\t"
      "movw -0x60(%%ebp), %%dx\n\t"
      "movl 0x46bd10, %%ecx\n\t"
      "movw %%ax, -0x12(%%ebp)\n\t"
      "movw %%dx, -0x16(%%ebp)\n\t"
      "movw %%di, -0x18(%%ebp)\n\t"
      "movb 0x1(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "je .LFUN_000d5350_21\n\t"
      "leal (%%edi,%%eax,4), %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "jmp .LFUN_000d5350_22\n\t"
      ".LFUN_000d5350_21:\n\t"
      "addl %%edi, %%eax\n\t"
      ".LFUN_000d5350_22:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movw %%ax, -0x14(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl -0x3c(%%ebp), %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "call *%[c19b8b0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_000d5350_23\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000d5350_28\n\t"
      "movl 0x454(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000d5350_29\n\t"
      "movl -0x34(%%ebp), %%edx\n\t"
      "cmpw $0, (%%edx)\n\t"
      "je .LFUN_000d5350_52\n\t"
      "pushl $1\n\t"
      "movl %%edx, %%ebx\n\t"
      "leal -0x10(%%ebp), %%esi\n\t"
      "leal -0x18(%%ebp), %%edi\n\t"
      "call *%[cd4470]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_000d5350_51\n\t"
      ".LFUN_000d5350_23:\n\t"
      "movl 0x46bd18, %%eax\n\t"
      "movl 0x1190(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_000d5350_24\n\t"
      "cmpw $0, 0x1194(%%eax)\n\t"
      "jne .LFUN_000d5350_25\n\t"
      ".LFUN_000d5350_24:\n\t"
      "pushl $1\n\t"
      "pushl $0x41e\n\t"
      "pushl $0x281b48\n\t"
      "pushl $0x281cc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x46bd18, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000d5350_25:\n\t"
      "leal 0x1194(%%eax), %%esi\n\t"
      "call *%[cb5ae0]\n\t"
      "movswl (%%esi), %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "subl %%eax, %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .LFUN_000d5350_26\n\t"
      "movl 0x46bd18, %%esi\n\t"
      "addl $0x1194, %%esi\n\t"
      "call *%[cb5ae0]\n\t"
      "movswl %%ax, %%edx\n\t"
      "movswl (%%esi), %%eax\n\t"
      "subl %%edx, %%eax\n\t"
      "jmp .LFUN_000d5350_27\n\t"
      ".LFUN_000d5350_26:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_000d5350_27:\n\t"
      "movw %%ax, (%%esi)\n\t"
      "call *%[c18e380]\n\t"
      "movl 0x5a0(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x686d7420\n\t"
      "call *%[tag]\n\t"
      "movl 0x46bd18, %%ecx\n\t"
      "movl 0x1190(%%ecx), %%edx\n\t"
      "movl -0x40(%%ebp), %%esi\n\t"
      "jmp .LFUN_000d5350_31\n\t"
      ".LFUN_000d5350_28:\n\t"
      "call *%[c18e380]\n\t"
      "movl 0x5a0(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x686d7420\n\t"
      "call *%[tag]\n\t"
      "movl 0x46bd18, %%ecx\n\t"
      "movl 0x118c(%%ecx), %%edx\n\t"
      "jmp .LFUN_000d5350_31\n\t"
      ".LFUN_000d5350_29:\n\t"
      "movb -0x19(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000d5350_30\n\t"
      "pushl $1\n\t"
      "pushl $0x42a\n\t"
      "pushl $0x281b48\n\t"
      "pushl $0x281cac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000d5350_30:\n\t"
      "movl 0x46bd0c, %%eax\n\t"
      "movl 0xfc(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x686d7420\n\t"
      "call *%[tag]\n\t"
      "movl 0x454(%%esi), %%edx\n\t"
      ".LFUN_000d5350_31:\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl %%edx, %%eax\n\t"
      "movw 0x20(%%eax), %%cx\n\t"
      "movw %%cx, -0x2c(%%ebp)\n\t"
      "movb 0x24(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "movl %%edx, -0x44(%%ebp)\n\t"
      "movl $0, -0x28(%%ebp)\n\t"
      "jbe .LFUN_000d5350_52\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl -0x34(%%ebp), %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "addl $0x14, %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      ".LFUN_000d5350_32:\n\t"
      "movl -0x44(%%ebp), %%ecx\n\t"
      "movzwl 0x22(%%ecx), %%edx\n\t"
      "addl %%eax, %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl $2\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movzbl (%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_000d5350_49\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000d5350_33\n\t"
      "pushl $1\n\t"
      "pushl $0x4a5\n\t"
      "pushl $0x281b48\n\t"
      "pushl $0x255ee8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_000d5350_50\n\t"
      ".LFUN_000d5350_33:\n\t"
      "movb 0x1(%%esi), %%al\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "cmpb $0x11, %%al\n\t"
      "jbe .LFUN_000d5350_44\n\t"
      "cmpb $0x1f, %%al\n\t"
      "ja .LFUN_000d5350_35\n\t"
      "cmpb $0x1c, %%al\n\t"
      "ja .LFUN_000d5350_34\n\t"
      "movzbl %%al, %%ecx\n\t"
      "movsbl 0x2f66c2(%%ecx), %%edx\n\t"
      "movzbw -0x98(%%ebp,%%edx,1), %%bx\n\t"
      "jmp .LFUN_000d5350_45\n\t"
      ".LFUN_000d5350_34:\n\t"
      "movzbl %%al, %%eax\n\t"
      "movsbw 0x2f66c2(%%eax), %%bx\n\t"
      "jmp .LFUN_000d5350_45\n\t"
      ".LFUN_000d5350_35:\n\t"
      "movl 0x46bd10, %%ecx\n\t"
      "movb 0x1(%%ecx), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .LFUN_000d5350_43\n\t"
      "movzbw %%al, %%si\n\t"
      "subl $0x20, %%esi\n\t"
      "cmpw $8, %%si\n\t"
      "jl .LFUN_000d5350_36\n\t"
      "pushl $1\n\t"
      "pushl $0x455\n\t"
      "pushl $0x281b48\n\t"
      "pushl $0x281c84\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000d5350_36:\n\t"
      "movb 0x229(%%edi), %%al\n\t"
      "movswl %%si, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testb %%al, %%dl\n\t"
      "je .LFUN_000d5350_41\n\t"
      "movw 0x204(%%edi,%%ecx,4), %%si\n\t"
      "cmpw $-1, %%si\n\t"
      "je .LFUN_000d5350_39\n\t"
      "movb 0x206(%%edi,%%ecx,4), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000d5350_38\n\t"
      "call *%[c18e380]\n\t"
      "cmpl $-1, 0x580(%%eax)\n\t"
      "jne .LFUN_000d5350_37\n\t"
      "pushl $1\n\t"
      "pushl $0x45e\n\t"
      "pushl $0x281b48\n\t"
      "pushl $0x281c4c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000d5350_37:\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c18e380]\n\t"
      "movl 0x580(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19d420]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "jmp .LFUN_000d5350_40\n\t"
      ".LFUN_000d5350_38:\n\t"
      "movl 0x46bd0c, %%ecx\n\t"
      "movl 0xc0(%%ecx), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c19d420]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "jmp .LFUN_000d5350_40\n\t"
      ".LFUN_000d5350_39:\n\t"
      "pushl $0\n\t"
      "movl $0x281c38, %%ebx\n\t"
      ".LFUN_000d5350_40:\n\t"
      "leal -0x10(%%ebp), %%esi\n\t"
      "leal -0x18(%%ebp), %%edi\n\t"
      "call *%[cd4470]\n\t"
      "movl -0x34(%%ebp), %%edi\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_000d5350_50\n\t"
      ".LFUN_000d5350_41:\n\t"
      "movl 0x204(%%edi,%%ecx,4), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_000d5350_42\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%ecx, %%esi\n\t"
      "leal -0x10(%%ebp), %%ebx\n\t"
      "call *%[cd44f0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000d5350_50\n\t"
      ".LFUN_000d5350_42:\n\t"
      "pushl $0x281c00\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000d5350_50\n\t"
      ".LFUN_000d5350_43:\n\t"
      "pushl $0x281bdc\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000d5350_45\n\t"
      ".LFUN_000d5350_44:\n\t"
      "movzbw %%al, %%bx\n\t"
      ".LFUN_000d5350_45:\n\t"
      "movl 0x46bd0c, %%ecx\n\t"
      "movl 0xc4(%%ecx), %%edx\n\t"
      "movswl %%bx, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jge .LFUN_000d5350_48\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[ce4da0]\n\t"
      "movl 0x46bd0c, %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "addl $0xc4, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0xd(%%esi), %%al\n\t"
      "addl $0x14, %%esp\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_000d5350_47\n\t"
      "testb $2, %%al\n\t"
      "je .LFUN_000d5350_46\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "leal -0x88(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c7af20]\n\t"
      "movl -0x3c(%%ebp), %%edx\n\t"
      "leal -0x88(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[c19b8b0]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_000d5350_46:\n\t"
      "movl 0x46bd0c, %%ecx\n\t"
      "movl 0xc0(%%ecx), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0xe(%%esi), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c19d420]\n\t"
      "movl -0x16(%%ebp), %%ebx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl -0xe(%%ebp), %%eax\n\t"
      "subl %%ebx, %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b5d0]\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x78(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c19cdb0]\n\t"
      "movw -0x16(%%ebp), %%cx\n\t"
      "addw $-3, -0xe(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x78(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "movw %%cx, -0x76(%%ebp)\n\t"
      "call *%[c184060]\n\t"
      "movl -0x3c(%%ebp), %%edx\n\t"
      "movw -0x10(%%ebp), %%ax\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "movw %%ax, -0x18(%%ebp)\n\t"
      "call *%[c19b8b0]\n\t"
      "addl $0x48, %%esp\n\t"
      "jmp .LFUN_000d5350_50\n\t"
      ".LFUN_000d5350_47:\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x10(%%ebp), %%ebx\n\t"
      "call *%[cd44f0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000d5350_50\n\t"
      ".LFUN_000d5350_48:\n\t"
      "movl -0xe(%%ebp), %%edx\n\t"
      "subl -0x16(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c19b5d0]\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x68(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl $0x281bb8\n\t"
      "pushl %%edx\n\t"
      "call *%[c19cdb0]\n\t"
      "movw -0x16(%%ebp), %%ax\n\t"
      "addw $-3, -0xe(%%ebp)\n\t"
      "pushl $0x281bb8\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x68(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "movw %%ax, -0x66(%%ebp)\n\t"
      "call *%[c184060]\n\t"
      "movw -0x10(%%ebp), %%dx\n\t"
      "addl $0x2c, %%esp\n\t"
      "movw %%dx, -0x18(%%ebp)\n\t"
      "jmp .LFUN_000d5350_50\n\t"
      ".LFUN_000d5350_49:\n\t"
      "movzbl 0x1(%%esi), %%eax\n\t"
      "movzwl -0x2c(%%ebp), %%ecx\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "shll $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "shll $1, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19b1a0]\n\t"
      "movl -0x16(%%ebp), %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl -0xe(%%ebp), %%eax\n\t"
      "subl %%edx, %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b5d0]\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x70(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c19cdb0]\n\t"
      "movw -0x16(%%ebp), %%cx\n\t"
      "addw $-3, -0xe(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x70(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "movw %%cx, -0x6e(%%ebp)\n\t"
      "call *%[c184060]\n\t"
      "movw -0x10(%%ebp), %%ax\n\t"
      "movw %%ax, -0x18(%%ebp)\n\t"
      "movzbw 0x1(%%esi), %%cx\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "addl $0x38, %%esp\n\t"
      "addl %%ecx, %%eax\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      ".LFUN_000d5350_50:\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movl -0x44(%%ebp), %%edx\n\t"
      "movzbl 0x24(%%edx), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_000d5350_32\n\t"
      ".LFUN_000d5350_51:\n\t"
      "movl -0x40(%%ebp), %%esi\n\t"
      ".LFUN_000d5350_52:\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c19b5d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000d5350_57\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000d5350_57\n\t"
      "movb -0x2d(%%ebp), %%bl\n\t"
      ".LFUN_000d5350_53:\n\t"
      "movb 0x458(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000d5350_54\n\t"
      "movb 0x45e(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000d5350_57\n\t"
      ".LFUN_000d5350_54:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_000d5350_55\n\t"
      "movswl -0x5e(%%ebp), %%edx\n\t"
      "movl 0x2f66ec, %%eax\n\t"
      "movl 0x5aa68c, %%ecx\n\t"
      "subl %%eax, %%edx\n\t"
      "movswl -0x38(%%ebp), %%eax\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "fmuls 0x90(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "jmp .LFUN_000d5350_56\n\t"
      ".LFUN_000d5350_55:\n\t"
      "movswl -0x38(%%ebp), %%edx\n\t"
      "movl 0x5aa68c, %%eax\n\t"
      "movswl -0x5e(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "fmuls 0x90(%%eax)\n\t"
      "fiaddl -0x8(%%ebp)\n\t"
      ".LFUN_000d5350_56:\n\t"
      "call *%[ftol]\n\t"
      "movl %%eax, %%edi\n\t"
      "decl -0x48(%%ebp)\n\t"
      ".LFUN_000d5350_57:\n\t"
      "pushl $0xd50f0\n\t"
      "pushl $0x8c\n\t"
      "pushl $4\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9260]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $0, -0x48(%%ebp)\n\t"
      "movl $0, -0x20(%%ebp)\n\t"
      "jle .LFUN_000d5350_76\n\t"
      "jmp .LFUN_000d5350_58\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000d5350_58:\n\t"
      "movswl -0x20(%%ebp), %%esi\n\t"
      "movl -0x40(%%ebp), %%ecx\n\t"
      "imull $0x8c, %%esi, %%esi\n\t"
      "movb 0x82(%%esi,%%ecx,1), %%al\n\t"
      "addl %%ecx, %%esi\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000d5350_76\n\t"
      "call *%[gtime]\n\t"
      "movl 0x5aa68c, %%ebx\n\t"
      "leal 0x80(%%ebx), %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "movl %%ecx, -0x58(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, -0x54(%%ebp)\n\t"
      "movl 0x8(%%edx), %%ecx\n\t"
      "movl %%ecx, -0x50(%%ebp)\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl 0xc(%%edx), %%edx\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movl %%edx, -0x4c(%%ebp)\n\t"
      "flds 0x68(%%ebx)\n\t"
      "fmuls 0x253394\n\t"
      "fld %%st(1)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000d5350_62\n\t"
      "fxch %%st(1)\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "flds 0x6c(%%ebx)\n\t"
      "fmuls 0x253394\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fsubrs 0x2533c8\n\t"
      "fstp %%st(1)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000d5350_59\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x2c(%%ebp)\n\t"
      "jmp .LFUN_000d5350_61\n\t"
      ".LFUN_000d5350_59:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000d5350_60\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, -0x2c(%%ebp)\n\t"
      "jmp .LFUN_000d5350_61\n\t"
      ".LFUN_000d5350_60:\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      ".LFUN_000d5350_61:\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fldl 0x26b678\n\t"
      "call *%[c1d9e70]\n\t"
      "fmuls -0x58(%%ebp)\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "jmp .LFUN_000d5350_63\n\t"
      ".LFUN_000d5350_62:\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_000d5350_63:\n\t"
      "movl 0x506584, %%eax\n\t"
      "movl 0x506588, %%ecx\n\t"
      "movw -0x60(%%ebp), %%dx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movw 0x50658a, %%ax\n\t"
      "subw 0x50657e, %%ax\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movw %%ax, -0xa(%%ebp)\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "movw %%dx, -0xe(%%ebp)\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "leal (%%eax,%%edi,1), %%ecx\n\t"
      "movswl %%di, %%eax\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movw %%cx, -0xc(%%ebp)\n\t"
      "movw %%di, -0x10(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "fmuls 0x90(%%ebx)\n\t"
      "fiaddl -0x8(%%ebp)\n\t"
      "call *%[ftol]\n\t"
      "movl -0x3c(%%ebp), %%edx\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c19b8b0]\n\t"
      "movl 0x84(%%esi), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000d5350_70\n\t"
      "movb 0x8a(%%esi), %%cl\n\t"
      "cmpb $0xff, %%cl\n\t"
      "jne .LFUN_000d5350_64\n\t"
      "cmpw $1, 0x88(%%esi)\n\t"
      "setg -0x1(%%ebp)\n\t"
      "jmp .LFUN_000d5350_65\n\t"
      ".LFUN_000d5350_64:\n\t"
      "movb %%cl, -0x1(%%ebp)\n\t"
      ".LFUN_000d5350_65:\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6974656d\n\t"
      "call *%[tag]\n\t"
      "movsbw -0x1(%%ebp), %%cx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movw 0x180(%%ebx), %%ax\n\t"
      "addw %%cx, %%ax\n\t"
      "movswl %%ax, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[cd0ba0]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movb 0x8a(%%esi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpb $0xff, %%al\n\t"
      "jne .LFUN_000d5350_66\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000d5350_67\n\t"
      ".LFUN_000d5350_66:\n\t"
      "cmpw $0, 0x88(%%esi)\n\t"
      "je .LFUN_000d5350_69\n\t"
      ".LFUN_000d5350_67:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x188(%%ebx), %%dx\n\t"
      "cmpw $1, %%dx\n\t"
      "jg .LFUN_000d5350_68\n\t"
      "movl $1, %%edx\n\t"
      ".LFUN_000d5350_68:\n\t"
      "movswl 0x88(%%esi), %%eax\n\t"
      "movswl %%dx, %%ebx\n\t"
      "cdq\n\t"
      "idivl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x2a0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19eaa0]\n\t"
      "leal -0x2a0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c184060]\n\t"
      "addl $0x20, %%esp\n\t"
      "jmp .LFUN_000d5350_72\n\t"
      ".LFUN_000d5350_69:\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "jmp .LFUN_000d5350_71\n\t"
      ".LFUN_000d5350_70:\n\t"
      "leal 0x4(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      ".LFUN_000d5350_71:\n\t"
      "call *%[c184060]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000d5350_72:\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "subl (%%esi), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x5aa68c, %%eax\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "flds 0x6c(%%eax)\n\t"
      "fadds 0x68(%%eax)\n\t"
      "fmuls 0x253394\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000d5350_73\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_000d5350_74\n\t"
      ".LFUN_000d5350_73:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_000d5350_74:\n\t"
      "testb %%al, %%al\n\t"
      "movb %%al, 0x82(%%esi)\n\t"
      "jne .LFUN_000d5350_75\n\t"
      "movl $0xffffffff, (%%esi)\n\t"
      ".LFUN_000d5350_75:\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw -0x48(%%ebp), %%ax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jl .LFUN_000d5350_58\n\t"
      ".LFUN_000d5350_76:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_000d5350_77:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c930a0] "m"(bd5350_c930a0), [cba3c0] "m"(bd5350_cba3c0), [cab230] "m"(bd5350_cab230), [cba4b0] "m"(bd5350_cba4b0), [cd1f40] "m"(bd5350_cd1f40), [tag] "m"(bd5350_tag), [cce6c0] "m"(bd5350_cce6c0), [gtime] "m"(bd5350_gtime), [cd2320] "m"(bd5350_cd2320), [c7af20] "m"(bd5350_c7af20), [d1c90] "m"(bd5350_d1c90), [c19b8b0] "m"(bd5350_c19b8b0), [cd4470] "m"(bd5350_cd4470), [assert] "m"(bd5350_assert), [exitfn] "m"(bd5350_exitfn), [cb5ae0] "m"(bd5350_cb5ae0), [c18e380] "m"(bd5350_c18e380), [elem] "m"(bd5350_elem), [c19d420] "m"(bd5350_c19d420), [cd44f0] "m"(bd5350_cd44f0), [c8f390] "m"(bd5350_c8f390), [ce4da0] "m"(bd5350_ce4da0), [c19b5d0] "m"(bd5350_c19b5d0), [c19cdb0] "m"(bd5350_c19cdb0), [c184060] "m"(bd5350_c184060), [c19b1a0] "m"(bd5350_c19b1a0), [ftol] "m"(bd5350_ftol), [c1d9260] "m"(bd5350_c1d9260), [c1d9e70] "m"(bd5350_c1d9e70), [cd0ba0] "m"(bd5350_cd0ba0), [c19eaa0] "m"(bd5350_c19eaa0)
      : "memory");
}
#else
#error "FUN_000d5350: clang naked draft required"
#endif

/* hud_find_nav_point_by_name (0xd5ec0) — XBE naked draft (batch 92). */
#if defined(__clang__)
static void *(*const bd5ec0_elem)(void *, int, int) = tag_block_get_element;
static int (*const bd5ec0_c1dd801)(const char *a, const char *b) = crt_stricmp;
static void (*const bd5ec0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
short hud_find_nav_point_by_name(const char *param_1)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x46bd0c, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%edi\n\t"
      "je .Lhud_find_nav_point_by_name_3\n\t"
      "movl 0x160(%%eax), %%ecx\n\t"
      "addl $0x160, %%eax\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .Lhud_find_nav_point_by_name_3\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".Lhud_find_nav_point_by_name_1:\n\t"
      "pushl $0x68\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c1dd801]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lhud_find_nav_point_by_name_2\n\t"
      "movl 0x46bd0c, %%eax\n\t"
      "movl 0x160(%%eax), %%edx\n\t"
      "incl %%esi\n\t"
      "addl $0x160, %%eax\n\t"
      "movswl %%si, %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jl .Lhud_find_nav_point_by_name_1\n\t"
      "jmp .Lhud_find_nav_point_by_name_3\n\t"
      ".Lhud_find_nav_point_by_name_2:\n\t"
      "cmpw $-1, %%si\n\t"
      "movl %%esi, %%ebx\n\t"
      "jne .Lhud_find_nav_point_by_name_4\n\t"
      ".Lhud_find_nav_point_by_name_3:\n\t"
      "pushl $0x281d14\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lhud_find_nav_point_by_name_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%bx, %%ax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(bd5ec0_elem), [c1dd801] "m"(bd5ec0_c1dd801), [c8f390] "m"(bd5ec0_c8f390)
      : "memory");
}
#else
#error "hud_find_nav_point_by_name: clang naked draft required"
#endif


/* hud_get_nav_point_data (0xd5f40) — XBE naked draft (batch 94). */
#if defined(__clang__)
static void (*const bd5f40_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bd5f40_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
int hud_get_nav_point_data(short param_1)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movw 0x8(%%ebp), %%si\n\t"
      "testw %%si, %%si\n\t"
      "jl .Lhud_get_nav_point_data_1\n\t"
      "cmpw $4, %%si\n\t"
      "jl .Lhud_get_nav_point_data_2\n\t"
      ".Lhud_get_nav_point_data_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x5f\n\t"
      "pushl $0x281d8c\n\t"
      "pushl $0x281d40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lhud_get_nav_point_data_2:\n\t"
      "movl 0x46bd1c, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lhud_get_nav_point_data_3\n\t"
      "pushl $1\n\t"
      "pushl $0x60\n\t"
      "pushl $0x281d8c\n\t"
      "pushl $0x281d30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lhud_get_nav_point_data_3:\n\t"
      "movl 0x46bd1c, %%ecx\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "shll $4, %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(bd5f40_assert), [exitfn] "m"(bd5f40_exitfn)
      : "memory");
}
#else
#error "hud_get_nav_point_data: clang naked draft required"
#endif


/* hud_nav_points_initialize (0xd5fb0) — XBE naked draft (batch 99). */
#if defined(__clang__)
static void * (*const bd5fb0_c1bfbf0)(const char *name, const char *a2, int size) = game_state_malloc;
static void (*const bd5fb0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bd5fb0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void hud_nav_points_initialize(void)
{
  __asm__ volatile(
      "pushl $0xc0\n\t"
      "pushl $0\n\t"
      "pushl $0x281db8\n\t"
      "call *%[c1bfbf0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x46bd1c\n\t"
      "jne .Lhud_nav_points_initialize_1\n\t"
      "pushl $1\n\t"
      "pushl $0x6a\n\t"
      "pushl $0x281d8c\n\t"
      "pushl $0x281d30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lhud_nav_points_initialize_1:\n\t"
      "ret\n\t"
      :
      : [c1bfbf0] "m"(bd5fb0_c1bfbf0), [assert] "m"(bd5fb0_assert), [exitfn] "m"(bd5fb0_exitfn)
      : "memory");
}
#else
#error "hud_nav_points_initialize: clang naked draft required"
#endif


/* hud_messaging_initialize_for_new_map (0xd5ff0) — readable C lift. */
void hud_messaging_initialize_for_new_map(void)
{
  csmemset(*(void **)0x46bd1c, -1, 0xc0);
}

/* hud_messaging_dispose_from_old_map: no-op stub.
 * Called from hud_dispose_from_old_map (0xd03e0). */
void hud_messaging_dispose_from_old_map(void)
{
}

/* hud_messaging_dispose: no-op stub.
 * Called from hud_dispose (0xd0340). */
void hud_messaging_dispose(void)
{
}

/* nav_point_set: add or update a nav point entry for a player (0xd6030).
 * Searches for existing match or empty slot in the 4-entry array.
 * ABI: @eax=player_handle, stack: type_value, nav_type, object_handle, extra */
void FUN_000d6030(int player_handle, short type_value, short nav_type,
                  int object_handle, int extra)
{
  short local_player;
  int nav_data;
  short best;
  short i;
  short *entry;
  short cx;

  if (player_handle == -1)
    return;
  local_player =
    *(short *)((int)datum_get(*(data_t **)0x5aa6d4, player_handle) + 2);
  if (local_player < 0 || local_player >= 4 || object_handle == -1 ||
      type_value == -1)
    return;

  nav_data = hud_get_nav_point_data(local_player);
  best = -1;
  i = 0;
  do {
    entry = (short *)(nav_data + i * 0xc);
    cx = (short)(entry[1] << 12) >> 12;
    if (cx == nav_type && *(int *)(entry + 4) == object_handle) {
      *entry = type_value;
      *(int *)(entry + 2) = extra;
      return;
    }
    if (cx == -1) {
      best = i;
    }
    i = i + 1;
  } while (i < 4);

  if (best != -1) {
    entry = (short *)(nav_data + best * 0xc);
    *(int *)(entry + 4) = object_handle;
    *(int *)(entry + 2) = extra;
    entry[1] =
      entry[1] ^
      ((*(unsigned char *)(entry + 1) ^ (unsigned char)nav_type) & 0xf);
    *entry = type_value;
    return;
  }
  error(2, "Could not add another nav point");
}

/* nav_point_set_flag wrapper (0xd6120).
 * Calls FUN_000d6030 with nav_type=2 (flag). */
void FUN_000d6120(int param_1, int player_handle, short param_3, int param_4)
{
  FUN_000d6030(player_handle, (short)param_1, 2, (int)param_3, param_4);
}

/* nav_point_set_object wrapper (0xd6140).
 * Calls FUN_000d6030 with nav_type=0 (object). */
void FUN_000d6140(int param_1, int player_handle, short param_3, int param_4)
{
  FUN_000d6030(player_handle, (short)param_1, 0, (int)param_3, param_4);
}

/* nav_point_set_enemy wrapper (0xd6160).
 * Calls FUN_000d6030 with nav_type=1 (enemy). */
void FUN_000d6160(int param_1, int player_handle, int param_3, int param_4)
{
  FUN_000d6030(player_handle, (short)param_1, 1, param_3, param_4);
}

/* FUN_000d6180 (0xd6180)
 * Set nav point for all players on a matching team.
 * ABI: @ebx=nav_type, @esi=extra, @edi=object_handle, stack: type_value, team,
 * param_3 */
void FUN_000d6180(int type_value, short team, int param_3, short nav_type,
                  int extra, int object_handle)
{
  int iter[4];
  int datum;

  data_iterator_new((void *)iter, *(data_t **)0x5aa6d4);
  datum = (int)data_iterator_next((void *)iter);
  while (datum != 0) {
    if (*(short *)(datum + 2) != -1 && (int)team == *(int *)(datum + 0x20)) {
      /* Pass the FULL 32-bit object handle. The original pushes EDI whole
       * (000d61c7: PUSH EDI); a prior lift truncated it via (int)(short),
       * dropping the datum salt (e.g. 0xeaab000d -> 0x0000000d). For object/
       * enemy navs (nav_type 0/1) that corrupts the tracked handle, so
       * nav_point_visibility_test's hit-object compare (collision_result+0x38
       * == handle) never matches and the nav never hides when you board or
       * look at the tracked object. NOTE: the sibling FUN_000d6280 genuinely
       * truncates in the original (000d62ba: MOVSX EAX,DI), so its (short)
       * cast is faithful and is deliberately left untouched. */
      FUN_000d6030(iter[2], (short)type_value, nav_type, object_handle, extra);
    }
    datum = (int)data_iterator_next((void *)iter);
  }
}

/* FUN_000d61f0 (0xd61f0)
 * Set flag nav point for all players on a team. */
void FUN_000d61f0(int type_value, int team, short object_handle, int extra)
{
  FUN_000d6180(type_value, (short)team, extra, 2, 0, (int)object_handle);
}

/* FUN_000d6220 (0xd6220)
 * Set object nav point for all players on a team. */
void FUN_000d6220(int type_value, int team, short object_handle, int extra)
{
  FUN_000d6180(type_value, (short)team, extra, 0, 0, (int)object_handle);
}

/* FUN_000d6250 (0xd6250)
 * Set enemy nav point for all players on a team. */
void FUN_000d6250(int type_value, int team, int object_handle, int extra)
{
  FUN_000d6180(type_value, (short)team, extra, 1, 0, object_handle);
}

/* FUN_000d6280 (0xd6280)
 * Set nav points for all players.
 * ABI: @ebx=nav_type, @edi=object_handle, stack: type_value, extra */
void FUN_000d6280(int type_value, int extra, short nav_type, int object_handle)
{
  int iter[4];
  int datum;

  data_iterator_new((void *)iter, *(data_t **)0x5aa6d4);
  datum = (int)data_iterator_next((void *)iter);
  while (datum != 0) {
    if (*(short *)(datum + 2) != -1) {
      FUN_000d6030(iter[2], (short)type_value, nav_type,
                   (int)(short)object_handle, extra);
    }
    datum = (int)data_iterator_next((void *)iter);
  }
}

/* FUN_000d62f0 (0xd62f0)
 * Set flag nav points for all players. */
void FUN_000d62f0(int type_value, int object_handle, int extra)
{
  FUN_000d6280(type_value, extra, 2, object_handle);
}

/* nav_point_clear: remove a nav point entry for a player (0xd6320).
 * ABI: @eax=player_handle, @esi=nav_type, @edi=object_handle */
void FUN_000d6320(int player_handle, short nav_type, int object_handle)
{
  short local_player;
  int nav_data;
  short i;
  short *entry;
  short bx;

  if (player_handle == -1)
    return;
  local_player =
    *(short *)((int)datum_get(*(data_t **)0x5aa6d4, player_handle) + 2);
  if (local_player < 0 || local_player >= 4 || object_handle == -1)
    return;

  nav_data = hud_get_nav_point_data(local_player);
  i = 0;
  do {
    entry = (short *)(nav_data + i * 0xc);
    bx = (short)(entry[1] << 12) >> 12;
    if (bx == nav_type && *(int *)(entry + 4) == object_handle) {
      *(unsigned char *)(entry + 1) = *(unsigned char *)(entry + 1) | 0xf;
      *(int *)(entry + 4) = -1;
      *entry = -1;
      return;
    }
    i = i + 1;
  } while (i < 4);
}

/* nav_point_clear_flag wrapper (0xd6390).
 * Clears a flag nav point (type=2). */
void FUN_000d6390(int player_handle, short object_handle)
{
  FUN_000d6320(player_handle, 2, (int)object_handle);
}

/* nav_point_clear_object wrapper (0xd63b0).
 * Clears an object nav point (type=0). */
void FUN_000d63b0(int player_handle, short object_handle)
{
  FUN_000d6320(player_handle, 0, (int)object_handle);
}

/* nav_point_clear_enemy wrapper (0xd63d0).
 * Clears an enemy nav point (type=1). */
void FUN_000d63d0(int player_handle, int object_handle)
{
  FUN_000d6320(player_handle, 1, object_handle);
}

/* FUN_000d63f0 (0xd63f0)
 * Clear nav points for all players on a given team.
 * ABI: @eax=object_handle, @ecx=nav_type, @ebx=team_handle */
void FUN_000d63f0(int object_handle, short nav_type, int team_handle)
{
  int iter[4];
  int datum;

  data_iterator_new((void *)iter, *(data_t **)0x5aa6d4);
  datum = (int)data_iterator_next((void *)iter);
  while (datum != 0) {
    if (*(short *)(datum + 2) != -1 &&
        (int)(short)team_handle == *(int *)(datum + 0x20)) {
      FUN_000d6320(iter[2], nav_type, object_handle);
    }
    datum = (int)data_iterator_next((void *)iter);
  }
}

/* FUN_000d6450 (0xd6450) — clear object nav points by team. */
void FUN_000d6450(int team_handle, short object_handle)
{
  FUN_000d63f0((int)object_handle, 0, team_handle);
}

/* FUN_000d6470 (0xd6470) — clear enemy nav points by team. */
void FUN_000d6470(int team_handle, int object_handle)
{
  FUN_000d63f0(object_handle, 1, team_handle);
}

/* FUN_000d6490 (0xd6490) — set object nav point for a unit's player. */
void FUN_000d6490(int param_1, int unit_handle, short param_3, int param_4)
{
  int player_index;

  player_index = player_index_from_unit_index(unit_handle);
  if (player_index != -1) {
    FUN_000d6030(player_index, (short)param_1, 0, (int)param_3, param_4);
  }
}

/* FUN_000d64c0 (0xd64c0) — set enemy nav point for a unit's player. */
void FUN_000d64c0(int param_1, int unit_handle, int param_3, int param_4)
{
  int player_index;

  player_index = player_index_from_unit_index(unit_handle);
  if (player_index != -1) {
    FUN_000d6030(player_index, (short)param_1, 1, param_3, param_4);
  }
}

/* FUN_000d64f0 (0xd64f0) — clear object nav point for a unit's player.
 * param_2 is a 16-bit object handle: the original sign-extends it
 * (MOVSX EDI,word[EBP+0xc]) before the full 32-bit compare in FUN_000d6320,
 * so it must be a short here, not an int. */
void FUN_000d64f0(int param_1, short param_2)
{
  int player_index;

  player_index = player_index_from_unit_index(param_1);
  if (player_index != -1) {
    FUN_000d6320(player_index, 0, (int)param_2);
  }
}

/* FUN_000d6520 (0xd6520)
 * Clear enemy nav point for a unit's player. */
void FUN_000d6520(int param_1, int param_2)
{
  int player_index;

  player_index = player_index_from_unit_index(param_1);
  if (player_index != -1) {
    FUN_000d6320(player_index, 1, param_2);
  }
}

/* nav_point_visibility_test (0xd6550)
 * Ray-cast from param_2 to param_3 to check if the nav point is visible. */
short FUN_000d6550(int param_1, float *param_2, float *param_3, int param_4)
{
  int player_handle;
  int player;
  int unit_handle;
  short result;
  char collision_result[80];
  float direction[3];

  if (global_current_collision_user_depth >= 0x20) {
    display_assert("global_current_collision_user_depth < "
                   "MAXIMUM_COLLISION_USER_STACK_DEPTH",
                   "c:\\halo\\SOURCE\\interface\\hud_nav_points.c", 0x1fe, 1);
    system_exit(-1);
  }
  collision_user_stack[global_current_collision_user_depth] = 0x14;
  global_current_collision_user_depth = global_current_collision_user_depth + 1;

  player_handle = local_player_get_player_index((short)param_1);
  if (player_handle == -1) {
    unit_handle = -1;
  } else {
    player_handle = local_player_get_player_index((short)param_1);
    player = (int)datum_get(*(data_t **)0x5aa6d4, player_handle);
    unit_handle = *(int *)(player + 0x34);
  }

  direction[0] = param_3[0] - param_2[0];
  direction[1] = param_3[1] - param_2[1];
  direction[2] = param_3[2] - param_2[2];

  if (FUN_0014df70(0xc2ad, param_2, direction, unit_handle,
                   (short *)collision_result) ==
        '\0' ||
      (*(short *)collision_result == 3 &&
       *(int *)(collision_result + 0x38) == param_4)) {
    result = 0;
  } else {
    result = 2;
  }

  if (global_current_collision_user_depth <= 1) {
    display_assert("global_current_collision_user_depth > 1",
                   "c:\\halo\\SOURCE\\interface\\hud_nav_points.c", 0x210, 1);
    system_exit(-1);
  }
  global_current_collision_user_depth = global_current_collision_user_depth - 1;
  return result;
}

/* nav_point_draw_single (0xd6660)
 * Draw a single nav point indicator with distance/angle calculations. */
void FUN_000d6660(int param_1, float *param_2, short param_3, short param_4)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  char cVar5;
  short sVar7;
  int iVar8;
  int iVar9;
  unsigned int uVar10;
  int uVar11;
  unsigned char bVar12;
  unsigned int uVar13;
  int local_2ac[128];
  char text_element[36];
  char text_pos_buf[84];
  int local_34;
  float local_30[3];
  float local_24[3] = {0, 0, 0};
  float distance;
  float local_14;
  float screen_pos[2] = {0, 0};
  float local_8;
  short screen_coords[2];
  local_34 = FUN_000d1540();
  csmemset(local_2ac, 0x62, 0x200);
  iVar8 = (int)tag_block_get_element(
    (void *)(*(int *)0x46bd0c + 0x160), (int)param_3, 0x68);
  pfVar4 = param_2;
  local_30[0] = *param_2;
  local_30[1] = param_2[1];
  local_30[2] = param_2[2];
  iVar9 = local_player_get_player_index(param_1);
  if (iVar9 == -1) {
    uVar11 = -1;
  } else {
    uVar11 = local_player_get_player_index(param_1);
    iVar9 = (int)datum_get(*(data_t **)0x5aa6d4, uVar11);
    uVar11 = *(int *)(iVar9 + 0x34);
  }
  unit_set_seat_state(uVar11, local_24);
  distance = sqrtf((*pfVar4 - local_24[0]) * (*pfVar4 - local_24[0]) +
                  (pfVar4[1] - local_24[1]) * (pfVar4[1] - local_24[1]) +
                  (pfVar4[2] - local_24[2]) * (pfVar4[2] - local_24[2]));
  if (distance > *(float *)0x254cc0) {
    local_14 = 0.5f;
  } else {
    local_14 = (float)pow(
        (double)(*(float *)0x2533c8 - distance * *(float *)0x253d48),
        *(double *)0x281e18) + *(float *)0x253398;
  }
  matrix_transform_point((float *)0x5065b4, local_30, local_30);
  sVar7 = param_4;
  if (sVar7 == 1 ||
      (cVar5 = render_camera_view_to_screen((int *)0x506550, (int *)0x5065a4, local_30,
                            screen_pos),
       cVar5 == '\0')) {
    screen_pos[0] = local_30[0];
    screen_pos[1] = -local_30[1];
    sVar7 = 1;
  } else {
    screen_pos[0] = screen_pos[0] - (float)(((int)*(short *)0x506582 -
                                   (int)*(short *)0x50657e) /
                                      2 +
                                  (int)*(short *)0x50657e);
    screen_pos[1] = screen_pos[1] - (float)(((int)*(short *)0x506580 -
                                 (int)*(short *)0x50657c) /
                                    2 +
                                (int)*(short *)0x50657c);
  }
  local_8 = 0.0f;
  fVar1 =
      ((float)((int)*(short *)0x50658a - (int)*(short *)0x506586) -
       (*(float *)(*(int *)0x46bd0c + 300) +
        *(float *)(*(int *)0x46bd0c + 0x128))) *
      *(float *)0x253398;
  fVar3 = ((float)((int)*(short *)0x506588 - (int)*(short *)0x506584) -
           (*(float *)(*(int *)0x46bd0c + 0x124) +
            *(float *)(*(int *)0x46bd0c + 0x120))) *
          *(float *)0x253398;
  fVar2 = fVar3 * fVar1;
  fVar1 = fVar1 * screen_pos[1];
  if (sVar7 == 1 ||
      fVar2 * fVar2 <= fVar3 * screen_pos[0] * (fVar3 * screen_pos[0]) + fVar1 * fVar1) {
    sVar7 = 1;
    fVar1 = sqrtf((fVar2 * fVar2) /
                 (fVar3 * screen_pos[0] * (fVar3 * screen_pos[0]) + fVar1 * fVar1));
    screen_pos[0] = screen_pos[0] * fVar1;
    screen_pos[1] = fVar1 * screen_pos[1];
    if ((*(unsigned char *)(iVar8 + 0x4c) & 1) == 0) {
      local_8 = -(float)atan2((double)screen_pos[0], (double)screen_pos[1]);
    }
  }
  screen_pos[0] =
      (float)(((int)*(short *)0x506582 - (int)*(short *)0x50657e) / 2) +
      screen_pos[0];
  screen_pos[1] = (float)(((int)*(short *)0x506580 - (int)*(short *)0x50657c) / 2) +
            screen_pos[1];
  if (sVar7 == -1) {
    display_assert(
        "waypoint_type!=NONE",
        "c:\\halo\\SOURCE\\interface\\hud_nav_points.c", 0x267, 1);
    system_exit(-1);
  }
  iVar9 = 0;
  uVar11 = 0;
  FUN_000d16a0(*(int *)(*(int *)0x46bd0c + 0x15c),
               *(short *)(iVar8 + 0x34 + sVar7 * 2), 0, &iVar9, &uVar11);
  if (iVar9 != 0 &&
      (int)xbox_texture_cache_get_hardware_format((void *)iVar9, 0, 1) != 0) {
    {
      int alpha_round = FUN_000d1c50(*(float *)(iVar8 + 0x2c));
      int alpha_scaled = alpha_round * 0xff;
      if (alpha_scaled < 0) {
        bVar12 = 0;
      } else if (alpha_scaled > 0xff) {
        bVar12 = 0xff;
      } else {
        bVar12 = (unsigned char)(-(char)FUN_000d1c50(*(float *)(iVar8 + 0x2c)));
      }
    }
    pixel32_to_real_rgb_color(*(unsigned int *)(iVar8 + 0x28), local_24);
    fVar1 = *(float *)0x2533c8 - *(float *)(iVar8 + 0x30);
    fVar2 = *(float *)0x2533c0;
    if (*(float *)0x2533c0 <= fVar1) {
      fVar2 = fVar1;
      if (*(float *)0x2533c8 < fVar1) {
        fVar2 = *(float *)0x2533c8;
      }
    }
    local_24[0] = fVar2 * local_24[0];
    fVar2 = *(float *)0x2533c0;
    if (*(float *)0x2533c0 <= fVar1) {
      fVar2 = fVar1;
      if (*(float *)0x2533c8 < fVar1) {
        fVar2 = *(float *)0x2533c8;
      }
    }
    local_24[1] = fVar2 * local_24[1];
    fVar2 = *(float *)0x2533c0;
    if (*(float *)0x2533c0 <= fVar1) {
      fVar2 = fVar1;
      if (*(float *)0x2533c8 < fVar1) {
        fVar2 = *(float *)0x2533c8;
      }
    }
    local_24[2] = fVar2 * local_24[2];
    uVar13 = (unsigned int)bVar12 << 0x18;
    uVar10 = FUN_000d1dd0(local_24);
    screen_coords[0] = (short)screen_pos[0];
    screen_coords[1] = (short)screen_pos[1];
    FUN_000d3200(iVar9, 4, screen_coords, uVar11, local_14, local_8,
                 uVar10 | uVar13, 0);

    if (sVar7 != 1) {
      short *text_pos_ptr;
      short text_x, text_y;
      int tmp_int;
      float pow_val;
      int text_value;

      /* Original 0xd6ac7: FLD [EBP-0x14] -- the sqrtf distance slot -- times
       * 0x281e00 (world units -> meters). The seat/color buffer local_24 ends
       * at [EBP-0x18]; the distance is a separate local, not local_24[3]. */
      distance = distance * *(float *)0x281e00;
      csmemset(text_element, 0, 0x24);
      csmemset(text_pos_buf, 0, 0x54);
      *(short *)text_element = 0;
      /* original writes the 5 color/style fields into text_pos_buf (arg3), NOT
       * text_element (arg2, whose only write is the first-word zero above).
       * Disasm: stores at [EBP-0x60]/[EBP-0x5c]/[EBP-0x40]/[EBP-0x3f]/[EBP-0x3e]
       * = text_pos_buf+0x24/+0x28/+0x44/+0x45/+0x46 (base EBP-0x84). */
      *(unsigned int *)(text_pos_buf + 0x24) =
          FUN_000d1dd0(local_24) | uVar13;
      *(unsigned int *)(text_pos_buf + 0x28) =
          FUN_000d1dd0(local_24) | uVar13;
      text_pos_buf[0x44] = 3;
      text_pos_buf[0x46] = 1;
      text_pos_buf[0x45] = 5;

      {
        short scr_x = (short)screen_pos[0];
        short scr_y = (short)screen_pos[1];
        float bmp_w;
        float bmp_h;

        tmp_int = (int)*(short *)(iVar9 + 4);
        bmp_w = (*(float *)(uVar11 + 4) - *(float *)uVar11);
        text_x = (short)((float)(int)scr_x +
                 bmp_w * (float)tmp_int * *(float *)0x253398 *
                 local_14 * *(float *)0x281dfc);

        tmp_int = (int)*(short *)(iVar9 + 6);
        bmp_h = (*(float *)(uVar11 + 0xc) - *(float *)(uVar11 + 0x8));
        text_y = (short)((float)(int)scr_y +
                 bmp_h * (float)tmp_int * *(float *)0x253398 *
                 local_14 * *(float *)0x281df8);

        text_x = text_x + (*(short *)0x50657e - *(short *)0x506586);
        text_y = text_y + (*(short *)0x50657c - *(short *)0x506584);
      }

      text_pos_ptr = (short *)text_pos_buf;
      text_pos_ptr[0] = text_x;
      text_pos_ptr[1] = text_y;

      pow_val = (float)pow(*(double *)0x281df0, *(double *)0x281de8);
      {
        float fmod_input = (float)fabs((double)(pow_val * distance));
        /* clang -mno-sse compiles fmod() to FPREM1 (IEEE remainder, result
         * can be negative); the original 0xd6bdc uses FPREM (truncating).
         * A negative tenths digit prints a stray '-' and the displayed
         * digit count flickers. x87_fmod keeps the result in [0, pow_val). */
        float fmod_result = x87_fmod(fmod_input, (double)pow_val);
        text_value = (int)fmod_result;
      }

      {
        int rounded = FUN_000d1c50(distance);
        FUN_000d3860((short)param_1, text_element, text_pos_buf,
                     rounded, text_value, 0, 0, 0.0f);
      }
    }
  }
  sVar7 = 0x7f;
  do {
    if (local_2ac[(int)sVar7] != 0x62626262) goto LAB_000d6c45;
    sVar7 = sVar7 - 1;
  } while (-1 < sVar7);
  sVar7 = -1;
LAB_000d6c45:
  iVar8 = FUN_000d1540();
  if (local_34 != iVar8) {
    display_assert("corrupt return address!",
                   "c:\\halo\\SOURCE\\interface\\hud_nav_points.c", 0x2a3, 1);
    system_exit(-1);
  }
  if (sVar7 != -1) {
    display_assert(
        csprintf((char *)0x5ab100, "corrupt stack at %d!", (int)sVar7),
        "c:\\halo\\SOURCE\\interface\\hud_nav_points.c", 0x2a3, 1);
    system_exit(-1);
  }
}

/* nav_point_render (0xd6cc0)
 * Render nav points for a player. */
void FUN_000d6cc0(int param_1)
{
  int nav_data;
  int player;
  int unit_handle;
  unsigned short *puVar6;
  int iVar2;
  short sVar5;
  int loop_count;
  float position[3];
  /* Save the local_player_index up front (original: uVar1 = param_1 @0xd6cc6).
   * The case-1 (object waypoint) branch below reuses param_1's stack slot as a
   * throwaway scratch for FUN_0001aae0's radius out-param, so param_1 itself is
   * clobbered. The original keeps the real index in uVar1 and uses it for
   * FUN_000d6660 and game_engine_render_nav_points; the prior lift dropped that
   * save and reused the clobbered param_1, tripping the players.c#133
   * local_player_index range assert on object-tracking nav points. */
  int local_player_index = param_1;

  if ((short)param_1 == -1)
    goto done;
  if (local_player_get_player_index((short)param_1) == -1)
    goto done;
  player = local_player_get_player_index((short)local_player_index);
  player = (int)datum_get(*(data_t **)0x5aa6d4, player);
  unit_handle = *(int *)(player + 0x34);
  if (unit_handle == -1)
    goto done;
  if (*(int *)(*(int *)0x46bd0c + 0x15c) == -1)
    goto done;

  nav_data = hud_get_nav_point_data((short)local_player_index);
  puVar6 = (unsigned short *)(nav_data + 8);
  loop_count = 4;
  do {
    if (puVar6[-4] == 0xffff || *(int *)puVar6 == -1 ||
        ((*((unsigned short *)puVar6 - 3) & 0xf) == 0xf)) {
      *(unsigned char *)((char *)puVar6 - 6) |= 0xf;
    } else {
      sVar5 = (short)(*((unsigned short *)puVar6 - 3) << 12) >> 12;
      switch (sVar5) {
      case 0:
        iVar2 = (int)global_scenario_get();
        iVar2 = (int)tag_block_get_element((void *)(iVar2 + 0x4e4),
                                           *(int *)puVar6, 0x5c);
        position[0] = *(float *)(iVar2 + 0x24);
        position[1] = *(float *)(iVar2 + 0x28);
        position[2] = *(float *)(iVar2 + 0x2c);
        break;
      case 1:
        iVar2 = (int)object_try_and_get_and_verify_type(*(int *)puVar6, -1);
        if (iVar2 == 0)
          goto skip;
        FUN_0001aae0(*(int *)puVar6, position, (float *)&param_1);
        break;
      case 2:
        game_engine_get_goal_position((int *)position, (short)*(int *)puVar6);
        break;
      default:
        display_assert("!\"unreachable\"",
                       "c:\\halo\\SOURCE\\interface\\hud_nav_points.c", 0x2d5,
                       1);
        system_exit(-1);
        break;
      }
      position[2] = position[2] + *(float *)((char *)puVar6 - 4);
      FUN_000d6660(
        local_player_index, position, (short)puVar6[-4],
        (short)((unsigned short)(*(unsigned char *)((char *)puVar6 - 6))
                << 8) >>
          12);
    }
  skip:
    puVar6 = puVar6 + 6;
    loop_count = loop_count - 1;
  } while (loop_count != 0);

done:
  game_engine_render_nav_points(local_player_index);
}

/* nav_point_update (0xd6e50)
 * Update nav point visibility flags for a player. */
void FUN_000d6e50(int param_1)
{
  int nav_data;
  int unit_handle;
  int player;
  int iVar2;
  unsigned short *puVar6;
  short sVar5;
  int loop_count;
  int local_234[128];
  float local_28[3];
  float local_1c[4];
  float target_pos[3];
  int local_18;
  short sVar;
  int obj_handle;
  char vis;

  local_18 = FUN_000d1540();
  csmemset(local_234, 0x62, 0x200);
  nav_data = hud_get_nav_point_data((short)param_1);
  player = local_player_get_player_index((short)param_1);
  if (player == -1) {
    unit_handle = -1;
  } else {
    player = local_player_get_player_index((short)param_1);
    player = (int)datum_get(*(data_t **)0x5aa6d4, player);
    unit_handle = *(int *)(player + 0x34);
  }
  puVar6 = (unsigned short *)(nav_data + 2);
  loop_count = 4;
  do {
    obj_handle = -1;
    if (puVar6[-1] == 0xffff || *(int *)(puVar6 + 3) == -1 ||
        (*puVar6 & 0xf) == 0xf) {
      *(unsigned char *)puVar6 = *(unsigned char *)puVar6 | 0xf;
    } else if (unit_handle != -1) {
      unit_get_head_position(unit_handle, local_28);
      sVar5 = (short)(*puVar6 << 12) >> 12;
      switch (sVar5) {
      case 0:
        iVar2 = (int)global_scenario_get();
        iVar2 = (int)tag_block_get_element((void *)(iVar2 + 0x4e4),
                                           *(int *)(puVar6 + 3), 0x5c);
        target_pos[0] = *(float *)(iVar2 + 0x24);
        target_pos[1] = *(float *)(iVar2 + 0x28);
        target_pos[2] = *(float *)(iVar2 + 0x2c);
        break;
      case 1:
        iVar2 =
          (int)object_try_and_get_and_verify_type(*(int *)(puVar6 + 3), -1);
        obj_handle = *(int *)(puVar6 + 3);
        if (iVar2 == 0 || (*(unsigned char *)(iVar2 + 0xb6) & 4) != 0) {
          *(unsigned char *)puVar6 = *(unsigned char *)puVar6 | 0xf;
          puVar6[3] = 0xffff;
          puVar6[4] = 0xffff;
          puVar6[-1] = 0xffff;
          goto next;
        }
        FUN_0001aae0(obj_handle, target_pos, local_1c);
        break;
      case 2:
        game_engine_get_goal_position((int *)target_pos, (unsigned short)puVar6[3]);
        break;
      }
      target_pos[2] = target_pos[2] + *(float *)(puVar6 + 1);
      {
        vis = (char)FUN_000d6550(param_1, local_28, target_pos, obj_handle);
        {
          int shifted = (int)vis << 4;
          *puVar6 = *puVar6 ^ (unsigned short)(((unsigned char)shifted ^ (unsigned char)*puVar6) & 0xf0);
        }
      }
    }
  next:
    puVar6 = puVar6 + 6;
    loop_count = loop_count - 1;
  } while (loop_count != 0);
  sVar = 0x7f;
  do {
    if (local_234[(int)sVar] != 0x62626262)
      goto check;
    sVar = sVar - 1;
  } while (sVar >= 0);
  sVar = -1;
check:
  iVar2 = FUN_000d1540();
  if (local_18 != iVar2) {
    display_assert("corrupt return address!",
                   "c:\\halo\\SOURCE\\interface\\hud_nav_points.c", 0x1f0, 1);
    system_exit(-1);
  }
  if (sVar != -1) {
    display_assert(
      csprintf((char *)0x5ab100, "corrupt stack at %d!", (int)sVar),
      "c:\\halo\\SOURCE\\interface\\hud_nav_points.c", 0x1f0, 1);
    system_exit(-1);
  }
}

/* FUN_000d7080 (0xd7080)
 * Iterate all local players and update nav point rendering. */
void FUN_000d7080(void)
{
  int result;
  short sVar;

  result = (int)local_player_get_next(-1);
  sVar = (short)result;
  while (sVar != -1) {
    FUN_000d6e50(result);
    result = (int)local_player_get_next((short)result);
    sVar = (short)result;
  }
}

/* hud_sounds_update (0xd70b0)
 * Update HUD sound effects based on state flags. */
void FUN_000d70b0(short param_1, unsigned int param_2, int *param_3,
                  int param_4, unsigned short *param_5)
{
  float new_var;
  int iVar1;
  short sVar2;
  int *piVar3;
  int iVar6;
  unsigned char bVar5;

  iVar6 = 0;
  sVar2 = 0;
  if (0 < *param_3) {
    do {
      piVar3 = (int *)tag_block_get_element((void *)param_3, iVar6, 0x38);
      bVar5 = (unsigned char)iVar6;
      new_var = *(float *)(piVar3 + 5);
      if ((param_2 & piVar3[4]) != 0) {
        if (*piVar3 == 0x6c736e64) {
          if (*(int *)(param_4 + iVar6 * 4) == -1) {
            *(int *)(param_4 + iVar6 * 4) =
              unattached_looping_sound_start(piVar3[3], -1, piVar3[5]);
          }
        } else if (*piVar3 == 0x736e6421) {
          iVar1 = *(int *)(param_4 + iVar6 * 4);
          if (iVar1 != -1) {
            if (((unsigned int)*param_5 & (1 << (bVar5 & 0x1f))) != 0)
              goto set_bit;
            if (iVar1 != -1) {
              sound_stop_impulse(iVar1);
            }
          }
          /* store the RETURNED sound datum handle (not the tag index piVar3[3]);
           * this slot is consumed later by sound_stop_impulse. */
          *(int *)(param_4 + iVar6 * 4) =
              sound_impulse_start(piVar3[3], new_var);
        } else {
          display_assert("!\"unreachable\"",
                         "c:\\halo\\SOURCE\\interface\\hud_sounds.c", 0x2f,
                         1);
          system_exit(-1);
          *param_5 = *param_5 | (unsigned short)(1 << (bVar5 & 0x1f));
          goto next;
        }
      set_bit:
        *param_5 = *param_5 | (unsigned short)(1 << (bVar5 & 0x1f));
      } else {
        iVar1 = *(int *)(param_4 + iVar6 * 4);
        if (iVar1 != -1) {
          if (*piVar3 == 0x6c736e64) {
            unattached_looping_sound_stop(iVar1);
          } else if (*piVar3 != 0x736e6421) {
            display_assert("!\"unreachable\"",
                           "c:\\halo\\SOURCE\\interface\\hud_sounds.c", 0x40,
                           1);
            system_exit(-1);
          }
          *(int *)(param_4 + iVar6 * 4) = -1;
          *param_5 = *param_5 & ~(unsigned short)(1 << (bVar5 & 0x1f));
        }
      }
    next:
      sVar2 = sVar2 + 1;
      iVar6 = (int)sVar2;
    } while (iVar6 < *param_3);
  }
}

/* unit_hud_slot_reset (0xd7240)
 * Reset a unit HUD slot to default values.
 * ABI: @esi=slot_pointer */
void FUN_000d7240(int slot)
{
  csmemset((void *)(slot + 0x22), 0xff, 2);
  *(int *)(slot + 4) = (int)0xbf800000;
  *(int *)(slot) = (int)0xbf800000;
  *(int *)(slot + 0x14) = -1;
  *(int *)(slot + 0x18) = -1;
  *(int *)(slot + 8) = (int)0xbf800000;
  *(int *)(slot + 0x1c) = -1;
}

/* unit_hud_get_slot (0xd7280)
 * Returns pointer to a player's unit HUD slot.
 * ABI: @esi=local_player_index */
int FUN_000d7280(short local_player_index)
{
  if (local_player_index < 0 || local_player_index >= 4) {
    display_assert("local_player_index>=0 && "
                   "local_player_index<MAXIMUM_NUMBER_OF_LOCAL_PLAYERS",
                   "c:\\halo\\SOURCE\\interface\\hud_unit.c", 0x106, 1);
    system_exit(-1);
  }
  if (*(int *)0x46bd20 == 0) {
    display_assert("unit_hud_globals",
                   "c:\\halo\\SOURCE\\interface\\hud_unit.c", 0x107, 1);
    system_exit(-1);
  }
  return local_player_index * 0x58 + *(int *)0x46bd20;
}

/* unit_hud_initialize (0xd72f0)
 * Allocates the unit HUD interface globals buffer. */
void FUN_000d72f0(void)
{
  *(int *)0x46bd20 = (int)game_state_malloc("hud unit interface", 0, 0x164);
  if (*(int *)0x46bd20 == 0) {
    display_assert("unit_hud_globals",
                   "c:\\halo\\SOURCE\\interface\\hud_unit.c", 0x110, 1);
    system_exit(-1);
  }
}

/* FUN_000d7330 (0xd7330)
 * Initialize unit_hud_globals: clears the global buffer (0x164 bytes),
 * then for each of 4 local players sets float fields to -1.0f (0xbf800000),
 * marks int fields as -1, and fills remaining slot bytes with 0xff. */
void FUN_000d7330(void)
{
  int *slot;
  int i;
  int16_t j;

  if (*(void **)0x46bd20 == 0) {
    display_assert("unit_hud_globals",
                   "c:\\halo\\SOURCE\\interface\\hud_unit.c", 0x11b, 1);
    system_exit(-1);
  }
  csmemset(*(void **)0x46bd20, 0, 0x164);
  j = 0;
  i = 0;
  do {
    if ((j < 0) || (j >= 4)) {
      display_assert("local_player_index>=0 && "
                     "local_player_index<MAXIMUM_NUMBER_OF_LOCAL_PLAYERS",
                     "c:\\halo\\SOURCE\\interface\\hud_unit.c", 0x106, 1);
      system_exit(-1);
    }
    if (*(void **)0x46bd20 == 0) {
      display_assert("unit_hud_globals",
                     "c:\\halo\\SOURCE\\interface\\hud_unit.c", 0x107, 1);
      system_exit(-1);
    }
    slot = (int *)(i + *(int *)0x46bd20);
    csmemset((char *)slot + 0x22, 0xff, 2);
    slot[1] = (int)0xbf800000;
    slot[0] = (int)0xbf800000;
    slot[5] = -1;
    slot[6] = -1;
    slot[2] = (int)0xbf800000;
    slot[7] = -1;
    *(int16_t *)((char *)slot + 0x24) = 0;
    csmemset((char *)slot + 0x28, 0xff, 0x30);
    j++;
    i += 0x58;
  } while (j < 4);
}

/* FUN_000d7420 (0xd7420)
 * Shared RET stub, tail-called from hud_dispose_from_old_map. Empty body. */
void FUN_000d7420(void)
{
}

/* FUN_000d7430 (0xd7430)
 * Shared RET stub, tail-called from hud_dispose. Empty body. */
void FUN_000d7430(void)
{
}

/* show_hud (0xd7440) — toggle HUD visibility flag bit 0. */
void FUN_000d7440(char param_1)
{
  if (param_1 == '\0') {
    *(unsigned int *)(*(int *)0x46bd20 + 0x160) =
      *(unsigned int *)(*(int *)0x46bd20 + 0x160) | 1;
    return;
  }
  *(unsigned int *)(*(int *)0x46bd20 + 0x160) =
    *(unsigned int *)(*(int *)0x46bd20 + 0x160) & 0xfffffffe;
}

/* show_hud_help_text (0xd7470) — toggle help text flag bit 1. */
void FUN_000d7470(char param_1)
{
  if (param_1 != '\0') {
    *(unsigned int *)(*(int *)0x46bd20 + 0x160) =
      *(unsigned int *)(*(int *)0x46bd20 + 0x160) | 2;
    return;
  }
  *(unsigned int *)(*(int *)0x46bd20 + 0x160) =
    *(unsigned int *)(*(int *)0x46bd20 + 0x160) & 0xfffffffd;
}

/* show_hud_health (0xd74a0) — toggle health display flag bit 2. */
void FUN_000d74a0(char param_1)
{
  if (param_1 == '\0') {
    *(unsigned int *)(*(int *)0x46bd20 + 0x160) =
      *(unsigned int *)(*(int *)0x46bd20 + 0x160) | 4;
    return;
  }
  *(unsigned int *)(*(int *)0x46bd20 + 0x160) =
    *(unsigned int *)(*(int *)0x46bd20 + 0x160) & 0xfffffffb;
}

/* show_hud_motion_sensor (0xd74d0) — toggle motion sensor flag bit 3. */
void FUN_000d74d0(char param_1)
{
  if (param_1 != '\0') {
    *(unsigned int *)(*(int *)0x46bd20 + 0x160) =
      *(unsigned int *)(*(int *)0x46bd20 + 0x160) | 8;
    return;
  }
  *(unsigned int *)(*(int *)0x46bd20 + 0x160) =
    *(unsigned int *)(*(int *)0x46bd20 + 0x160) & 0xfffffff7;
}

/* show_hud_crosshair (0xd7500) — toggle crosshair display flag bit 4. */
void FUN_000d7500(char param_1)
{
  if (param_1 == '\0') {
    *(unsigned int *)(*(int *)0x46bd20 + 0x160) =
      *(unsigned int *)(*(int *)0x46bd20 + 0x160) | 0x10;
    return;
  }
  *(unsigned int *)(*(int *)0x46bd20 + 0x160) =
    *(unsigned int *)(*(int *)0x46bd20 + 0x160) & 0xffffffef;
}

/* show_hud_ammo (0xd7530) — toggle ammo display flag bit 5. */
void FUN_000d7530(char param_1)
{
  if (param_1 != '\0') {
    *(unsigned int *)(*(int *)0x46bd20 + 0x160) =
      *(unsigned int *)(*(int *)0x46bd20 + 0x160) | 0x20;
    return;
  }
  *(unsigned int *)(*(int *)0x46bd20 + 0x160) =
    *(unsigned int *)(*(int *)0x46bd20 + 0x160) & 0xffffffdf;
}

/* unit_hud_update_sounds (0xd7560)
 * Build sound state flags from unit properties and update HUD sounds. */
void FUN_000d7560(int param_1, char param_2)
{
  char cVar1;
  short sVar2;
  int *pfVar3;
  int iVar4;
  int *puVar5;
  int iVar7;
  unsigned int uVar8;

  pfVar3 = (int *)FUN_000d7280(*(short *)(param_1 + 2));
  iVar4 = *(int *)(param_1 + 0x34);
  if (iVar4 == -1) {
    iVar4 = pfVar3[7];
  }
  puVar5 = (int *)object_try_and_get_and_verify_type(iVar4, 3);
  if (puVar5 != (int *)0) {
    iVar7 = (int)tag_get(0x756e6974, *puVar5);
    sVar2 = local_player_count();
    iVar7 = FUN_001a6820(iVar7, 1 < sVar2);
    if (iVar7 != -1) {
      iVar7 = (int)tag_get(0x756e6869, iVar7);
      uVar8 = 0;
      if ((*(unsigned char *)((int)puVar5 + 4) & 4) != 0 ||
          *(float *)((int)puVar5 + 0x90) <= *(float *)0x2533c0) {
        pfVar3[7] = -1;
      } else if (param_2 != '\0' &&
                 (cVar1 = cinematic_in_progress(), cVar1 == '\0')) {
        if (*(int *)pfVar3 != (int)0xbf800000) {
          iVar4 = local_player_get_player_index(*(short *)(param_1 + 2));
          cVar1 = game_engine_has_shield(iVar4);
          if (cVar1 != '\0' &&
              (*(unsigned int *)(*(int *)0x46bd20 + 0x160) & 4) == 0) {
            uVar8 =
                (*(unsigned short *)((int)puVar5 + 0xb6) & 0x1000) >> 0xc;
            if (*(float *)pfVar3 < *(float *)((int)puVar5 + 0x94)) {
              uVar8 = uVar8 | 2;
            }
            if (*(float *)((int)puVar5 + 0x94) < *(float *)0x25337c &&
                *(float *)0x2533c0 < *(float *)((int)puVar5 + 0x94)) {
              uVar8 = uVar8 | 4;
            }
            if (*(float *)((int)puVar5 + 0x94) == *(float *)0x2533c0) {
              uVar8 = uVar8 | 8;
            }
          }
        }
        if ((*(unsigned int *)(*(int *)0x46bd20 + 0x160) & 1) == 0) {
          if (*(float *)((int)puVar5 + 0x90) < *(float *)0x25337c) {
            uVar8 = uVar8 | 0x10;
          }
          if ((*(unsigned char *)((int)puVar5 + 0xb6) & 4) != 0) {
            uVar8 = uVar8 | 0x20;
          }
          if (*(float *)((int)puVar5 + 0x90) < *(float *)(pfVar3 + 1) &&
              *(float *)(pfVar3 + 1) - *(float *)((int)puVar5 + 0x90) <
                  *(float *)0x281e94) {
            uVar8 = uVar8 | 0x40;
          }
          if (*(float *)0x281e94 <=
              *(float *)(pfVar3 + 1) - *(float *)((int)puVar5 + 0x90)) {
            uVar8 = uVar8 | 0x80;
          }
        }
      }
      FUN_000d70b0(*(short *)(param_1 + 2), uVar8, (int *)(iVar7 + 0x3c0),
                   (int)(pfVar3 + 10), (unsigned short *)(pfVar3 + 9));
    }
  }
}

/* unit_hud_copy_slot (0xd7780)
 * Copy unit HUD data from old player to new player. */
void FUN_000d7780(short old_player, short new_player)
{
  int *src;
  int *dst;

  if (old_player == -1) {
    display_assert("old_local_player_index!=NONE",
                   "c:\\halo\\SOURCE\\interface\\hud_unit.c", 0x1ab, 1);
    system_exit(-1);
  }
  if (new_player == -1) {
    display_assert("new_local_player_index!=NONE",
                   "c:\\halo\\SOURCE\\interface\\hud_unit.c", 0x1ac, 1);
    system_exit(-1);
  }
  src = (int *)FUN_000d7280(old_player);
  dst = (int *)FUN_000d7280(new_player);
  memcpy(dst, src, 0x58);
}

/* unit_hud_update_shield_health (0xd7800)
 * Track shield/health changes and manage regen timing.
 * ABI: @eax=player_handle */
void FUN_000d7800(int player_handle)
{
  char cVar1;
  int iVar2;
  int iVar6;
  short sVar7;
  float *pfVar4;
  float fVar5;
  int local_20c[128];
  int local_c;
  int local_8;

  local_c = FUN_000d1540();
  csmemset(local_20c, 0x62, 0x200);
  iVar2 = local_player_get_player_index(player_handle);
  if (iVar2 == -1) goto LAB_000d794f;
  iVar2 = local_player_get_player_index(player_handle);
  iVar2 = (int)datum_get(*(data_t **)0x5aa6d4, iVar2);
  if (*(int *)(iVar2 + 0x34) == -1) goto LAB_000d794f;
  iVar2 = (int)object_get_and_verify_type(*(int *)(iVar2 + 0x34), 3);
  pfVar4 = (float *)FUN_000d7280((short)player_handle);
  if (pfVar4[1] == -1.0f) {
    pfVar4[1] = *(float *)(iVar2 + 0x90);
  }
  if (*pfVar4 == -1.0f) {
    *pfVar4 = *(float *)(iVar2 + 0x94);
  }
  fVar5 = *(float *)0x2533c0;
  if (*pfVar4 <= *(float *)(iVar2 + 0x94)) {
    if (*(float *)(iVar2 + 0x94) <= *pfVar4) {
      *pfVar4 = *(float *)(iVar2 + 0x94);
      if (fVar5 < pfVar4[2]) {
        local_8 = game_time_get();
        local_8 = local_8 - (int)pfVar4[3];
        goto LAB_000d7939;
      }
    } else {
      *pfVar4 = *(float *)(iVar2 + 0x94);
      pfVar4[2] = -1.0f;
    }
  } else {
    if (pfVar4[2] < *(float *)0x2533c0 ||
        *(float *)0x2533c8 < pfVar4[2]) {
      fVar5 = (float)game_time_get();
      pfVar4[3] = fVar5;
    }
    iVar6 = game_time_get();
    if (iVar6 - (int)pfVar4[3] < 0xf) {
      pfVar4[2] = 0.0f;
      goto LAB_000d794f;
    }
    *pfVar4 = *(float *)(iVar2 + 0x94);
    local_8 = game_time_get();
    local_8 = local_8 - (int)pfVar4[3];
  LAB_000d7939:
    pfVar4[2] = (float)local_8 * *(float *)0x2546a4 + pfVar4[2];
  }
  fVar5 = (float)game_time_get();
  pfVar4[3] = fVar5;
LAB_000d794f:
  cVar1 = cinematic_in_progress();
  if (cVar1 != '\0') {
    iVar2 = local_player_get_player_index(player_handle);
    if (iVar2 != -1) {
      iVar2 = (int)datum_get(*(data_t **)0x5aa6d4, iVar2);
      FUN_000d7560(iVar2, **(char **)0x46bd10);
    }
  }
  sVar7 = 0x7f;
  do {
    if (local_20c[(int)sVar7] != 0x62626262) goto LAB_000d79a8;
    sVar7 = sVar7 - 1;
  } while (-1 < sVar7);
  sVar7 = -1;
LAB_000d79a8:
  iVar2 = FUN_000d1540();
  if (local_c != iVar2) {
    display_assert("corrupt return address!",
                   "c:\\halo\\SOURCE\\interface\\hud_unit.c", 0x201, 1);
    system_exit(-1);
  }
  if (sVar7 != -1) {
    display_assert(
      csprintf((char *)0x5ab100, "corrupt stack at %d!", (int)sVar7),
      "c:\\halo\\SOURCE\\interface\\hud_unit.c", 0x201, 1);
    system_exit(-1);
  }
}

/* hud_render_damage_indicators (0xd7a20)
 * Render motion sensor direction indicators for incoming damage. */
void FUN_000d7a20(int param_1)
{
  int iVar3;
  int iVar5;
  int iVar6;
  float fVar7;
  short sVar2;
  unsigned char local_18[4];
  int local_14;
  short local_10[2];
  int local_c;
  int local_8;
  int tmp;
  float pos_x;
  float pos_y;
  short *pESI;

  if ((short)param_1 == -1) {
    return;
  }
  iVar3 = local_player_get_player_index(param_1);
  if (iVar3 == -1) {
    iVar3 = 0;
  } else {
    iVar3 = local_player_get_player_index(param_1);
    iVar3 = (int)datum_get(*(data_t **)0x5aa6d4, iVar3);
    iVar3 = *(int *)(iVar3 + 0x34);
  }
  iVar5 = (int)object_try_and_get_and_verify_type(iVar3, 3);
  if (iVar5 == 0) {
    player_effect_clear_damage_indicators(param_1);
    return;
  }
  iVar3 = *(int *)0x46bd0c;
  pESI = (short *)(iVar3 + 0x310);
  sVar2 = local_player_count();
  fVar7 = FUN_000d1690(1 < sVar2);
  player_effect_get_damage_indicators(param_1, local_18);
  local_14 = 4;
  iVar5 = 0;
  do {
    if (local_18[iVar5] != 0 && local_18[iVar5] < 0x1e) {
      switch (iVar5) {
      case 0:
        pos_x = (float)((int)pESI[0] + (int)*(short *)0x506584);
        tmp = ((int)*(short *)0x506582 + (int)*(short *)0x50657e) / 2;
        param_1 = 0x40490fdb;
        pos_y = (float)tmp;
        break;
      case 1:
        pos_x = (float)((int)pESI[2] + (int)*(short *)0x506586);
        tmp = ((int)*(short *)0x506580 + (int)*(short *)0x50657c) / 2;
        param_1 = 0x3fc90fdb;
        pos_y = (float)tmp;
        break;
      case 2:
        pos_x = (float)((int)*(short *)0x506588 - (int)pESI[1]);
        tmp = ((int)*(short *)0x506582 + (int)*(short *)0x50657e) / 2;
        param_1 = 0;
        pos_y = (float)tmp;
        break;
      case 3:
        pos_x = (float)((int)*(short *)0x50658a - (int)pESI[3]);
        tmp = ((int)*(short *)0x506580 + (int)*(short *)0x50657c) / 2;
        param_1 = 0x4096cbe4;
        pos_y = (float)tmp;
        break;
      default:
        display_assert("!\"unreachable\"",
                       "c:\\halo\\SOURCE\\interface\\hud_unit.c", 0x400, 1);
        system_exit(-1);
      }

      pos_x = pos_x - (float)(int)*(short *)0x50657e;
      pos_y = pos_y - (float)(int)*(short *)0x50657c;

      iVar6 = *(int *)(iVar3 + 0x344);
      sVar2 = local_player_count();
      if (sVar2 < 2) {
        sVar2 = *(short *)(iVar3 + 0x348);
      } else {
        sVar2 = *(short *)(iVar3 + 0x34a);
      }
      local_8 = 0;
      local_c = 0;
      FUN_000d16a0(iVar6, sVar2, 0, &local_8, &local_c);
      if (local_8 != 0 &&
          (int)xbox_texture_cache_get_hardware_format((void *)local_8, 0, 1) !=
              0) {
        local_10[0] = (short)pos_x;
        local_10[1] = (short)pos_y;
        FUN_000d3200(local_8, 4, local_10, local_c, fVar7,
                     *(float *)&param_1, *(int *)(iVar3 + 0x34c), 0);
      }
    }
    iVar5 = iVar5 + 1;
    local_14 = local_14 - 1;
  } while (local_14 != 0);
}

/* FUN_000d7cd0 (0xd7cd0)
 * Subtract damage amount from a player's HUD damage indicator. */
void FUN_000d7cd0(int player_handle, float param_2)
{
  int player;
  float *pfVar2;

  player = (int)datum_get(*(data_t **)0x5aa6d4, player_handle);
  if (*(short *)(player + 2) != -1) {
    pfVar2 = (float *)FUN_000d7280(*(short *)(player + 2));
    *pfVar2 = *pfVar2 - param_2;
  }
}

/* FUN_000d7d10 (0xd7d10)
 * Iterate local players and update unit HUD for each. */
void FUN_000d7d10(void)
{
  int result;
  short sVar;

  result = (int)local_player_get_next(-1);
  sVar = (short)result;
  while (sVar != -1) {
    FUN_000d7800(sVar);
    result = (int)local_player_get_next(sVar);
    sVar = (short)result;
  }
}

/* FUN_000d7d40 (0xd7d40)
 * Full HUD unit render for a single player. Draws shield meters,
 * health bars, damage indicators, motion tracker, and overlay widgets.
 * Uses a 0x200-byte stack canary (0x62 fill) with post-check.
 * Source: c:\halo\SOURCE\interface\hud_unit.c line 0x209. */
void FUN_000d7d40(int param_1)
{
  int canary_buf[128];
  int handle_slots[18];
  int tag_indices[18];
  /*
   * In the original MSVC frame this is &local_24 (base EBP-0x20); only
   * fraction_slots[0] (the shield fraction, unit_ptr+0x2f4) is ever stored.
   * The overlay loop reads fraction_slots[*psVar12], where *psVar12 is the
   * overlay_type. That read is reached only via the (full_shield & (1<<type))
   * branch, and full_shield is forced to {0,1} at 0x7f91/0x7f9a
   * (= unit_ptr+0x2f0 == 1.0f). A {0,1} value ANDed with (1<<type) is nonzero
   * only for type==0, so the indexed read is structurally always
   * fraction_slots[0]; slots [1..3] are dead on the read path and the latent
   * OOB for overlay_type>=4 cannot occur here. The discrete float[4] is
   * therefore faithful. (See FUN_000d7d40 disasm 0x87d2-0x87e1.)
   */
  float fraction_slots[4];
  unsigned int full_shield;
  unsigned int damage_active;
  unsigned int slot_count;
  unsigned int local_player_idx;
  int player_index;
  int canary_cookie;
  int *unit_ptr;
  int unit_data;
  int unhi_tag;
  int parent_handle;
  int health_meter_data[26];
  int widget_meter_data[26];
  short local_130[2];
  int overlay_colors[6];
  unsigned int flags;
  int iVar7, iVar8, iVar13;
  int flash_param_int;
  int clamp_a, clamp_b;
  short sVar4, sVar5;
  char cVar3;
  unsigned char bVar;
  float fVar1, fVar2, fVar14;
  float local_44;
  float local_34;
  float local_48;
  float meter_scale;
  short *psVar12;
  short *psVar22;
  int tag_ref_result;
  int *meter_src_ptr;
  int i;
  void *local_78_buf[1];
  float *pfVar6;
  unsigned char *unit_tag_data;

  canary_cookie = FUN_000d1540();
  csmemset(canary_buf, 0x62, 0x200);

  if (*(short *)(param_1 + 2) != *(short *)0x506548) {
    display_assert(
        "player->local_player_index==render.local_player_index",
        "c:\\halo\\SOURCE\\interface\\hud_unit.c", 0x209, 1);
    system_exit(-1);
  }

  if (*(short *)(param_1 + 2) != *(short *)0x506548)
    goto done_canary_check;
  if (*(int *)(param_1 + 0x34) == -1)
    goto done_canary_check;

  unit_ptr = (int *)object_get_and_verify_type(*(int *)(param_1 + 0x34), 3);
  unit_tag_data = (unsigned char *)tag_get(0x756e6974, *unit_ptr);
  local_player_idx = (unsigned int)(unsigned short)*(short *)(param_1 + 2);
  player_index = local_player_get_player_index(local_player_idx);
  pfVar6 = (float *)FUN_000d7280((short)local_player_idx);

  handle_slots[0] = *(int *)(param_1 + 0x34);
  csmemset(handle_slots + 1, 0, 17 * 4);

  sVar4 = local_player_count();
  tag_indices[0] = FUN_001a6820((int)unit_tag_data, 1 < sVar4);

  csmemset(tag_indices + 1, 0, 17 * 4);

  slot_count = 1;

  if (*(int *)((char *)pfVar6 + 0x1c) == (int)0xFFFFFFFF) {
    csmemset((char *)pfVar6 + 0x22, 0xFF, 2);
    *(float *)pfVar6 = -1.0f;
    *(float *)((char *)pfVar6 + 0x04) = -1.0f;
    *(float *)((char *)pfVar6 + 0x08) = -1.0f;
    *(int *)((char *)pfVar6 + 0x14) = -1;
    *(int *)((char *)pfVar6 + 0x18) = -1;
    *(int *)((char *)pfVar6 + 0x1c) = -1;
  }

  *(int *)((char *)pfVar6 + 0x1c) = *(int *)(param_1 + 0x34);

  parent_handle = unit_ptr[0x33];

  if (parent_handle != -1 && *(short *)((char *)unit_ptr + 0x2a0) != -1) {
    int *vehicle_ptr;
    int vehicle_tag;
    int seat_element;

    vehicle_ptr = (int *)object_get_and_verify_type(parent_handle, 3);
    vehicle_tag = (int)tag_get(0x756e6974, *vehicle_ptr);
    seat_element = (int)tag_block_get_element(
        (void *)(vehicle_tag + 0x2e4),
        (int)*(short *)((char *)unit_ptr + 0x2a0), 0x11c);
    unit_tag_data = (unsigned char *)seat_element;

    FUN_000d7280((short)local_player_idx);
    sVar4 = local_player_count();
    iVar8 = FUN_001a6820(vehicle_tag, 1 < sVar4);

    if ((*unit_tag_data & 4) != 0) {
      if (iVar8 != -1) {
        handle_slots[1] = parent_handle;
        tag_indices[1] = iVar8;
        slot_count = 2;
      }

      iVar13 = vehicle_ptr[0x32];
      while (iVar13 != -1 && slot_count < 0x12) {
        unsigned char *next_obj_data;
        int next_unit;

        next_obj_data = (unsigned char *)object_get_and_verify_type(
            iVar13, (int)0xFFFFFFFF);
        next_unit =
            (int)object_try_and_get_and_verify_type(iVar13, 3);
        if (next_unit != 0 &&
            *(int *)(next_unit + 0xcc) == parent_handle &&
            *(short *)(next_unit + 0x2a0) != -1) {
          handle_slots[slot_count] = iVar13;
          sVar4 = local_player_count();
          iVar13 = FUN_001a6870(
              vehicle_tag,
              *(unsigned short *)(next_unit + 0x2a0), 1 < sVar4);
          tag_indices[slot_count] = iVar13;
          slot_count = slot_count + 1;
        }
        iVar13 = *(int *)(next_obj_data + 0xc4);
      }
    }
  }

  {
    int shield_frac_raw = *(int *)((char *)unit_ptr + 0x2f0);
    full_shield = (unsigned int)(shield_frac_raw == 0x3f800000);

    if ((unit_ptr[0x6d] & 0x80000) != 0 ||
        *(float *)((char *)unit_ptr + 0x2f4) >= *(float *)0x2549d4) {
      damage_active = 0;
    } else if ((*(unsigned char *)((char *)unit_ptr + 0x1b8) & 0x10) != 0) {
      damage_active = 1;
    } else {
      damage_active = 0;
    }

    fraction_slots[0] = *(float *)((char *)unit_ptr + 0x2f4);
  }

  {
    unsigned int uVar16 = slot_count;
    unsigned int uVar18;

    while (uVar16 != 0) {
      uVar18 = uVar16 - 1;

      iVar13 = (int)object_try_and_get_and_verify_type(
          handle_slots[uVar16 - 1], 3);
      unit_data = iVar13;

      uVar16 = uVar18;
      if (iVar13 == 0 || tag_indices[uVar18] == -1)
        goto next_slot;

      iVar7 = (int)tag_get(0x756e6869, tag_indices[uVar18]);
      unhi_tag = iVar7;

      if (*(int *)(iVar7 + 0x54) != -1) {
        bVar = (unsigned char)((*(unsigned char *)(iVar13 + 0xb6)) >> 1) & 2;
        sVar4 = local_player_count();
        if (1 < sVar4) {
          bVar = bVar | 4;
        }
        FUN_000d3fe0(local_player_idx, (short *)iVar7, iVar7 + 0x24,
                     (unsigned int)bVar, (int)0xFFFFFFFF);
      }

      cVar3 = game_engine_has_shield(player_index);
      iVar8 = unit_data;
      {
        int iVar21 = unhi_tag;

        if (cVar3 != '\0' &&
            (iVar8 = iVar13, iVar21 = iVar7,
             (*(unsigned int *)(*(int *)0x46bd20 + 0x160) & 4) == 0)) {

          if (*(float *)(iVar13 + 0x94) < *(float *)0x25337c ||
              (*(unsigned int *)(*(int *)0x46bd20 + 0x160) & 8) != 0) {
            flags = 1;
          } else {
            flags = 0;
          }

          if ((*(unsigned char *)(unit_data + 0xb6) & 4) != 0) {
            flags = flags | 2;
          }

          sVar4 = local_player_count();
          if (1 < sVar4) {
            flags = flags | 4;
          }

          if (uVar18 == 0) {
            if ((flags & 1) == 0) {
              *(int *)((char *)pfVar6 + 0x10) = (int)0xFFFFFFFF;
            } else if (*(int *)((char *)pfVar6 + 0x10) == (int)0xFFFFFFFF) {
              *(int *)((char *)pfVar6 + 0x10) = game_time_get();
            }
          }

          if (*(int *)(iVar7 + 0x124) != -1) {
            int layer_idx;
            int saved_layer_idx;
            int meter_max;
            int *color_ptr;

            game_engine_running();

            if (uVar18 == 0) {
              local_44 = pfVar6[0];
            } else {
              local_44 = *(float *)(unit_data + 0x94);
            }

            meter_max =
                (int)(unsigned short)*(unsigned short *)(unhi_tag + 0x13e);
            if (meter_max == 0) {
              meter_max = 0xff;
            }

            meter_src_ptr = (int *)(unhi_tag + 0xf4);
            {
              int *src = (int *)(unhi_tag + 0xf4);
              int *dst = widget_meter_data;
              int cnt;
              for (cnt = 0x1a; cnt != 0; cnt--) {
                *dst = *src;
                src++;
                dst++;
              }
            }

            overlay_colors[0] = 0;
            overlay_colors[1] = 0xff0000;
            overlay_colors[2] = 0xff00;
            overlay_colors[3] = 0xffff00;
            overlay_colors[4] = 0x7f00ff;
            color_ptr = overlay_colors;

            layer_idx = 0;

            if (0 <= *(int *)0x2f66f0) {
              do {
                saved_layer_idx = layer_idx;

                local_34 =
                    *(float *)(unit_data + 0x94) - (float)layer_idx;
                if (local_34 < *(float *)0x2533c0) {
                  local_34 = 0.0f;
                } else if (local_34 > *(float *)0x2533c8) {
                  local_34 = 1.0f;
                }

                fVar14 = local_44 - (float)layer_idx;
                fVar1 = *(float *)0x2533c0;
                if (*(float *)0x2533c0 <= fVar14) {
                  fVar1 = fVar14;
                  if (*(float *)0x2533c8 < fVar14) {
                    fVar1 = *(float *)0x2533c8;
                  }
                }

                fVar2 = local_34;
                if (local_34 < fVar1) {
                  fVar2 = fVar1;
                }

                if ((local_34 < *(float *)0x2533c0 !=
                     (local_34 == *(float *)0x2533c0)) &&
                    (fVar2 < *(float *)0x2533c0 !=
                         (fVar2 == *(float *)0x2533c0)))
                  break;

                if (fVar1 <= local_34) {
                  flash_param_int = (int)0xbf800000;
                } else {
                  flash_param_int = *(int *)((char *)pfVar6 + 0x08);
                }

                local_48 = (float)(short)meter_max * fVar2;
                clamp_a = (int)local_48;
                if (clamp_a < 0) {
                  clamp_a = 0;
                } else {
                  if ((int)local_48 > 0xff) {
                    clamp_a = 0xff;
                  } else {
                    clamp_a = (int)local_48;
                  }
                }

                {
                  float local_38_v =
                      (float)(short)meter_max * local_34;
                  clamp_b = (int)local_38_v;
                  if (clamp_b < 0) {
                    clamp_b = 0;
                  } else {
                    if ((int)local_38_v > 0xff) {
                      clamp_b = 0xff;
                    } else {
                      clamp_b = (int)local_38_v;
                    }
                  }
                }

                {
                  int *meter_data_ptr;
                  widget_meter_data[13] = *color_ptr;
                  widget_meter_data[14] = *color_ptr;
                  if (layer_idx == 0) {
                    meter_data_ptr = meter_src_ptr;
                  } else {
                    meter_data_ptr = widget_meter_data;
                  }

                  FUN_000d3340(local_player_idx, unhi_tag,
                               (int)meter_data_ptr, clamp_b, clamp_a,
                               flags, flash_param_int, local_34);
                }

                color_ptr = color_ptr + 1;
                layer_idx = saved_layer_idx + 1;
              } while (saved_layer_idx + 1 <= *(int *)0x2f66f0);
            }
          }

          iVar8 = unit_data;
          iVar21 = unhi_tag;

          if (*(int *)(unhi_tag + 0xbc) != -1) {
            FUN_000d3fe0(local_player_idx, (short *)unhi_tag,
                         unhi_tag + 0x8c, flags,
                         *(int *)((char *)pfVar6 + 0x10));
            iVar8 = unit_data;
            iVar21 = unhi_tag;
          }
        }

        if ((*(unsigned int *)(*(int *)0x46bd20 + 0x160) & 1) == 0) {
          unsigned short health_status_bits;

          health_status_bits = *(unsigned short *)(iVar8 + 0xb6);
          if ((health_status_bits & 8) == 0 &&
              (*(unsigned int *)(*(int *)0x46bd20 + 0x160) & 2) == 0) {
            flags = 0;
          } else {
            flags = 1;
          }
          if ((health_status_bits & 4) != 0) {
            flags = flags | 2;
          }
          sVar4 = local_player_count();
          if (1 < sVar4) {
            flags = flags | 4;
          }

          if (uVar18 == 0) {
            if ((flags & 1) == 0) {
              *(int *)((char *)pfVar6 + 0x14) = (int)0xFFFFFFFF;
            } else if (*(int *)((char *)pfVar6 + 0x14) ==
                       (int)0xFFFFFFFF) {
              *(int *)((char *)pfVar6 + 0x14) = game_time_get();
            }
          }

          iVar13 = unhi_tag;
          if (*(int *)(iVar21 + 0x214) != -1) {
            short health_max;
            int health_alpha;
            int health_flash_alpha;

            health_max = *(short *)(iVar21 + 0x22e);
            if (health_max == 0) {
              health_max = 8;
            }

            {
              int *h_src = (int *)(unhi_tag + 0x1e4);
              int *h_dst = health_meter_data;
              int h_cnt;
              for (iVar8 = unit_data, h_cnt = 0x1a; h_cnt != 0;
                   h_cnt--) {
                *h_dst = *h_src;
                h_src++;
                h_dst++;
              }
            }

            if (*(float *)(unit_data + 0x90) <
                *(float *)(iVar13 + 0x250)) {
              if (*(float *)(unit_data + 0x90) <
                      *(float *)(iVar13 + 0x254) ||
                  *(float *)(unit_data + 0x90) ==
                      *(float *)(iVar13 + 0x254)) {
                /* override stores at base+0x38/+0x34 = indices 14/13, not 15/14
                 * (disasm: MOV [EBP-0x15c]/[EBP-0x160], base EBP-0x194). */
                health_meter_data[14] = health_meter_data[13];
              } else {
                health_meter_data[14] = *(int *)(iVar13 + 0x24c);
              }
            }
            health_meter_data[13] = health_meter_data[14];

            meter_scale = (float)(int)health_max;

            iVar7 = FUN_000d1c50(
                meter_scale * *(float *)(unit_data + 0x90));
            if (iVar7 < 0) {
              health_alpha = 0;
            } else {
              iVar7 = FUN_000d1c50(
                  meter_scale * *(float *)(iVar8 + 0x90));
              if (iVar7 < 0x100) {
                health_alpha = FUN_000d1c50(
                    meter_scale * *(float *)(iVar8 + 0x90));
              } else {
                health_alpha = 0xff;
              }
            }

            iVar7 = FUN_000d1c50(
                meter_scale * *(float *)(iVar8 + 0x90));
            if (iVar7 < 0) {
              health_flash_alpha = 0;
            } else {
              iVar7 = FUN_000d1c50(
                  meter_scale * *(float *)(iVar8 + 0x90));
              if (iVar7 < 0x100) {
                health_flash_alpha = FUN_000d1c50(
                    meter_scale * *(float *)(iVar8 + 0x90));
              } else {
                health_flash_alpha = 0xff;
              }
            }

            FUN_000d3340(local_player_idx, iVar13,
                         (int)health_meter_data, health_flash_alpha,
                         health_alpha, flags, (int)0xbf800000,
                         *(float *)(iVar8 + 0x90));
            iVar21 = unhi_tag;
          }

          if (*(int *)(iVar21 + 0x1ac) != -1) {
            FUN_000d3fe0(local_player_idx, (short *)iVar21,
                         iVar21 + 0x17c, flags,
                         *(int *)((char *)pfVar6 + 0x14));
          }

          pfVar6[1] = *(float *)(unit_data + 0x90);
        }

        if (uVar18 == 0 &&
            (*(unsigned char *)(*(int *)0x46bd20 + 0x160) & 0x10) == 0 &&
            FUN_000a9f90(player_index) != '\0') {

          local_130[0] = 2;

          sVar4 = local_player_count();
          bVar = (unsigned char)((sVar4 < 2) - 1) & 4;
          if ((*(unsigned char *)(*(int *)0x46bd20 + 0x160) & 0x20) !=
              0) {
            bVar = bVar | 1;
          }

          if ((bVar & 1) == 0) {
            *(int *)((char *)pfVar6 + 0x18) = (int)0xFFFFFFFF;
          } else if (*(int *)((char *)pfVar6 + 0x18) ==
                     (int)0xFFFFFFFF) {
            *(int *)((char *)pfVar6 + 0x18) = game_time_get();
          }

          iVar13 = unhi_tag;
          if (*(int *)(unhi_tag + 0x29c) != -1) {
            FUN_000d3fe0(local_player_idx, local_130,
                         unhi_tag + 0x26c, (unsigned int)bVar,
                         (int)0xFFFFFFFF);
          }
          if (*(int *)(iVar13 + 0x304) != -1) {
            FUN_000d3fe0(local_player_idx, local_130,
                         iVar13 + 0x2d4, (unsigned int)bVar,
                         (int)0xFFFFFFFF);
          }

          sVar4 = local_player_count();
          FUN_000d1f40((short)local_player_idx, (unsigned short *)local_130,
                       (short *)(iVar13 + 0x35c), 0, 1 < sVar4, 0,
                       (short *)local_78_buf);

          sVar4 = local_player_count();
          FUN_000dbfb0(local_player_idx, 1 < sVar4,
                       (int)local_78_buf);
        }

        {
          int widget_base;
          int *widget_block_ptr;
          int widget_flags_mask;

          iVar13 = unhi_tag;
          widget_base = unhi_tag + 0x380;
          cVar3 = FUN_000a95a0();
          sVar4 = local_player_count();
          widget_block_ptr = (int *)(iVar13 + 0x3a4);
          widget_flags_mask = (int)((sVar4 < 2) - 1) & 4;

          if (0 < *(int *)(iVar13 + 0x3a4)) {
            int widget_type_mask;
            int widget_idx_int;

            widget_type_mask = (unsigned int)(cVar3 != '\0');
            widget_idx_int = 0;

            do {
              int widget_element;

              widget_element = (int)tag_block_get_element(
                  (void *)widget_block_ptr, widget_idx_int, 0x84);

              if ((widget_type_mask &
                   (1 << (*(unsigned char *)(widget_element + 0x68) &
                          0x1f))) != 0) {
                if ((*(unsigned char *)(widget_element + 0x6a) & 1) !=
                    0) {
                  unsigned int packed_color;
                  packed_color = FUN_000d1dd0(
                      (float *)(unit_data + 0x138));
                  *(unsigned int *)(widget_element + 0x34) =
                      packed_color | 0xff000000;
                }

                FUN_000d3fe0(local_player_idx,
                             (short *)widget_base,
                             widget_element,
                             (unsigned int)widget_flags_mask,
                             (int)0xFFFFFFFF);
              }

              i = (int)(short)(widget_idx_int + 1);
              widget_idx_int = i;
            } while (i < *widget_block_ptr);
          }
        }

        {
          int overlay_loop_idx = 0;

          if (0 < *(int *)(unhi_tag + 0x3cc)) {
            int overlay_idx = 0;

            do {
              psVar12 = (short *)tag_block_get_element(
                  (void *)(unhi_tag + 0x3cc), overlay_idx, 0x144);

              {
                short overlay_type;
                unsigned int type_bit;
                unsigned int bitmask_20;

                overlay_type = *psVar12;
                type_bit =
                    1 << ((unsigned char)overlay_type & 0x1f);
                bitmask_20 = (unsigned int)*(unsigned short
                                                *)((char *)pfVar6 +
                                                   0x20);

                if ((type_bit & bitmask_20) != 0 &&
                    (full_shield & type_bit) == 0) {
                  *(short *)((char *)pfVar6 +
                             overlay_type * 2 + 0x22) =
                      (short)0xffff;
                }

                overlay_type = *psVar12;
                type_bit =
                    1 << ((unsigned char)overlay_type & 0x1f);

                if ((full_shield & type_bit) == 0) {
                  if ((damage_active & type_bit) == 0) {
                    psVar22 =
                        (short *)((char *)pfVar6 +
                                  overlay_type * 2 + 0x22);
                    if (*psVar22 != -1) {
                      psVar22 = (short *)((char *)pfVar6 +
                                          *psVar12 * 2 + 0x22);
                      iVar13 =
                          FUN_000d2300((int)(psVar12 + 0x24));
                      if (*psVar22 < iVar13)
                        goto overlay_active_no_shield;
                    }
                    *psVar22 = -1;
                  } else {
                  overlay_active_no_shield:
                    tag_ref_result = verify_tag_reference(
                        (int *)(psVar12 + 0x1c));
                    sVar4 = local_player_count();
                    psVar22 =
                        (short *)((char *)pfVar6 +
                                  *psVar12 * 2 + 0x22);
                    sVar5 = game_time_get_elapsed();
                    *psVar22 = *psVar22 + sVar5;

                    if (tag_ref_result != (int)0xFFFFFFFF) {
                      int time_val = game_time_get();
                      FUN_000d3fe0(
                          local_player_idx,
                          (short *)unhi_tag,
                          (int)(psVar12 + 10),
                          ((unsigned int)((sVar4 < 2) - 1) &
                           4) |
                              1,
                          time_val -
                              (int)*(short *)((char *)pfVar6 +
                                              *psVar12 * 2 +
                                              0x22));
                    }
                  }
                } else {
                  int overlay_ref2;

                  tag_ref_result = verify_tag_reference(
                      (int *)(psVar12 + 0x1c));
                  overlay_ref2 = verify_tag_reference(
                      (int *)(psVar12 + 0x50));
                  sVar4 = local_player_count();
                  flags =
                      (unsigned int)((sVar4 < 2) - 1) & 4;

                  if (fraction_slots[*psVar12] <
                          *(float *)(psVar12 + 0x72) &&
                      fraction_slots[*psVar12] !=
                          *(float *)(psVar12 + 0x72)) {
                    flags = flags | 1;
                  }

                  psVar22 =
                      (short *)((char *)pfVar6 +
                                *psVar12 * 2 + 0x22);
                  sVar5 = game_time_get_elapsed();
                  *psVar22 = *psVar22 + sVar5;

                  psVar22 =
                      (short *)((char *)pfVar6 +
                                *psVar12 * 2 + 0x22);
                  iVar13 =
                      FUN_000d2300((int)(psVar12 + 0x24));
                  *psVar22 =
                      (short)((int)*psVar22 % (iVar13 << 1));

                  if (tag_ref_result != (int)0xFFFFFFFF) {
                    int time_val2 = game_time_get();
                    FUN_000d3fe0(
                        local_player_idx,
                        (short *)unhi_tag,
                        (int)(psVar12 + 10), flags,
                        time_val2 -
                            (int)*(short *)((char *)pfVar6 +
                                            *psVar12 * 2 +
                                            0x22));
                  }

                  if (overlay_ref2 != (int)0xFFFFFFFF) {
                    float frac_value;
                    float computed_alpha;
                    int alpha_a2, alpha_b2;
                    short alpha_scale;

                    alpha_scale = psVar12[99];
                    frac_value = fraction_slots[*psVar12];
                    meter_scale = (float)(int)alpha_scale;
                    computed_alpha = meter_scale * frac_value;

                    clamp_a = (int)computed_alpha;
                    if (clamp_a < 0) {
                      alpha_a2 = 0;
                    } else {
                      clamp_a = (int)computed_alpha;
                      if (clamp_a > 0xff) {
                        alpha_a2 = 0xff;
                      } else {
                        alpha_a2 = (int)computed_alpha;
                      }
                    }

                    clamp_b = (int)computed_alpha;
                    if (clamp_b < 0) {
                      alpha_b2 = 0;
                    } else {
                      clamp_b = (int)computed_alpha;
                      if (clamp_b > 0xff) {
                        alpha_b2 = 0xff;
                      } else {
                        alpha_b2 = (int)computed_alpha;
                      }
                    }

                    FUN_000d3340(
                        local_player_idx, unhi_tag,
                        (int)(psVar12 + 0x3e), alpha_b2,
                        alpha_a2, flags, (int)0xbf800000,
                        frac_value);
                  }
                }
              }

              overlay_idx =
                  (int)(short)(overlay_loop_idx + 1);
              overlay_loop_idx = overlay_loop_idx + 1;
            } while (overlay_idx <
                     *(int *)(unhi_tag + 0x3cc));
          }
        }

        *(unsigned short *)((char *)pfVar6 + 0x20) =
            (unsigned short)full_shield;
      }

    next_slot:
      slot_count = uVar18;
    }
  }

done_canary_check:
  {
    short canary_idx = 0x7f;
    do {
      if (canary_buf[canary_idx] != 0x62626262)
        goto canary_found;
      canary_idx = canary_idx - 1;
    } while (canary_idx >= 0);
    canary_idx = -1;

  canary_found:
    {
      int cookie_check = FUN_000d1540();
      if (canary_cookie != cookie_check) {
        display_assert("corrupt return address!",
                       "c:\\halo\\SOURCE\\interface\\hud_unit.c",
                       0x3c9, 1);
        system_exit(-1);
      }
      if (canary_idx != -1) {
        char *msg =
            csprintf((char *)0x5ab100, "corrupt stack at %d!",
                     (int)canary_idx);
        display_assert(
            msg, "c:\\halo\\SOURCE\\interface\\hud_unit.c",
            0x3c9, 1);
        system_exit(-1);
      }
    }
  }
}
