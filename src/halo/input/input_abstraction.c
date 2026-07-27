#include "x87_math.h"

void input_abstraction_dispose(void)
{
  csmemset((void *)0x46b820, 0, 0xdc);
}

/* Snapshot the current system time into the input abstraction globals.
   Called each tick to timestamp when input was last processed. */
void input_abstraction_mark_time(void)
{
  *(unsigned int *)0x46b8f0 = system_milliseconds();
}

void input_abstraction_initialize(void)
{
  int i;
  char *entry;

  csmemset((void *)0x46b820, 0, 0xdc);
  entry = (char *)0x46b828;
  for (i = 0; i < 4; i++) {
    *(float *)(entry - 8) = 120.0f;
    *(float *)(entry - 4) = 60.0f;
    entry[0] = 0;
    entry[1] = 4;
    entry[2] = 2;
    entry[3] = 3;
    entry[4] = 1;
    entry[5] = 5;
    entry[6] = 6;
    entry[7] = 7;
    entry[8] = 0xc;
    entry[9] = 0xd;
    entry[10] = 0xe;
    entry[11] = 0xf;
    *(int16_t *)(entry + 12) = 0;
    entry[14] = 0;
    entry[15] = 0;
    *(char *)(0x46b8f4 + i) = (char)input_has_gamepad(i);
    entry += 0x18;
  }
  *(int *)0x46b8f0 = system_milliseconds();
  *(char *)0x46b8f8 = 1;
}

void input_abstraction_update(void)
{
  float lx, ly, rx, ry;
  float lmag, rmag;
  float lang, rang;
  float ldom, rdom;
  float fVar1, fVar2;
  int iVar10, iVar13, iVar14;
  int uVar15;
  bool bVar16;
  char cVar6;
  int16_t sVar9;
  uint16_t uVar7, uVar8;
  int local_18;
  int local_20;
  uint8_t *pbVar11;
  uint8_t *puVar12;

  iVar10 = ((int (*)(void))0x18e450)();
  tag_block_get_element((void *)(iVar10 + 0x110), 0, 0x80);

  for (local_18 = 0; local_18 <= 3; local_18++) {
    iVar10 = (int)input_get_gamepad_state(local_18);
    if (iVar10 == 0) {
      if (((char *)0x46b8f4)[local_18] != '\0') {
        cVar6 = ((char (*)(void))0xe43e0)();
        iVar10 = local_18;
        if (cVar6 == '\0') {
          iVar13 = ((int (*)(void))0x12a240)();
          bVar16 = iVar13 == 0;
          uVar15 = bVar16 ? 0xc : 0xd;
          cVar6 = (char)local_player_exists(local_18);
          if (cVar6 != '\x01')
            goto skip_disconnect_ui;
        } else {
          iVar14 = 0;
          for (iVar13 = 0; iVar13 < 4; iVar13++) {
            if (((char *)0x46b8f4)[iVar13] != '\0')
              iVar14++;
          }
          bVar16 = false;
          uVar15 = 0xd;
          if (iVar14 < 2) {
            sVar9 = player_ui_get_single_player_local_player_controller(0);
            if (sVar9 != local_18) {
              sVar9 = player_ui_get_single_player_local_player_controller(1);
              if (sVar9 != local_18) {
                sVar9 = player_ui_get_single_player_local_player_controller(2);
                if (sVar9 != local_18) {
                  sVar9 =
                    player_ui_get_single_player_local_player_controller(3);
                  if (sVar9 != local_18) {
                    cVar6 = ((char (*)(int))0xe0890)(local_18);
                    if (cVar6 == '\0')
                      iVar10 = -1;
                  }
                }
              }
            }
          } else {
            sVar9 = player_ui_get_single_player_local_player_controller(0);
            if (sVar9 != local_18) {
              sVar9 = player_ui_get_single_player_local_player_controller(1);
              if (sVar9 != local_18) {
                sVar9 = player_ui_get_single_player_local_player_controller(2);
                if (sVar9 != local_18) {
                  sVar9 =
                    player_ui_get_single_player_local_player_controller(3);
                  if (sVar9 != local_18) {
                    cVar6 = ((char (*)(int))0xe0890)(local_18);
                    if (cVar6 == '\0')
                      goto skip_disconnect_ui;
                  }
                }
              }
            }
          }
        }
        cVar6 = ((char (*)(void))0xf5640)();
        if (cVar6 != '\0')
          ((void (*)(void))0xf5f90)();
        ((void (*)(int, int, bool, bool))0xe4500)(uVar15, iVar10, bVar16,
                                                  bVar16);
      }
    skip_disconnect_ui:
      ((char *)0x46b8f4)[local_18] = 0;
    } else {
      iVar13 = local_18 * 0x18;

      /* copy per-player look sensitivity and vehicle look speed to output */
      uVar15 = *(int32_t *)((char *)0x46b824 + iVar13);
      *(int32_t *)((char *)0x457098 + local_18 * 4) =
        *(int32_t *)((char *)0x46b820 + iVar13);
      *(int32_t *)((char *)0x4570a8 + local_18 * 4) = uVar15;

      /* normalize left stick via dominant-axis scaling */
      lang = (float)atan2((double)(int)*(int16_t *)(iVar10 + 0x22),
                          (double)(int)*(int16_t *)(iVar10 + 0x20));
      fVar1 = lang;
      ldom = fabsf(x87_fsin(lang));
      fVar2 = fabsf(x87_fcos(fVar1));
      if (ldom <= fVar2)
        ldom = fVar2;
      lx = (float)(int)*(int16_t *)(iVar10 + 0x20) * *(float *)0x280f80 *
           (*(double *)0x2573d8 / ldom);
      lx = lx < *(float *)0x255e94 ? -1.0f :
           lx > *(float *)0x2533c8 ? 1.0f :
                                     lx;
      ly = (float)(int)*(int16_t *)(iVar10 + 0x22) * *(float *)0x280f80 *
           (*(double *)0x2573d8 / ldom);
      ly = ly < *(float *)0x255e94 ? -1.0f :
           ly > *(float *)0x2533c8 ? 1.0f :
                                     ly;

      /* normalize right stick */
      rang = (float)atan2((double)(int)*(int16_t *)(iVar10 + 0x26),
                          (double)(int)*(int16_t *)(iVar10 + 0x24));
      fVar2 = rang;
      rdom = fabsf(x87_fsin(rang));
      fVar1 = fabsf(x87_fcos(fVar2));
      if (rdom <= fVar1)
        rdom = fVar1;
      rx = (float)(int)*(int16_t *)(iVar10 + 0x24) * *(float *)0x280f80 *
           (*(double *)0x2573d8 / rdom);
      rx = rx < *(float *)0x255e94 ? -1.0f :
           rx > *(float *)0x2533c8 ? 1.0f :
                                     rx;
      ry = (float)(int)*(int16_t *)(iVar10 + 0x26) * *(float *)0x280f80 *
           (*(double *)0x2573d8 / rdom);
      ry = ry < *(float *)0x255e94 ? -1.0f :
           ry > *(float *)0x2533c8 ? 1.0f :
                                     ry;

      /* copy button state with remapping */
      pbVar11 = (uint8_t *)((char *)0x46b829 + iVar13);
      puVar12 = (uint8_t *)((char *)0x46b881 + local_18 * 0x1c);
      puVar12[-1] = *(uint8_t *)(pbVar11[-1] + 0x10 + iVar10);
      puVar12[0] = *(uint8_t *)(pbVar11[0] + 0x10 + iVar10);
      puVar12[1] = *(uint8_t *)(pbVar11[1] + 0x10 + iVar10);
      puVar12[2] = *(uint8_t *)(pbVar11[2] + 0x10 + iVar10);
      puVar12[3] = *(uint8_t *)(pbVar11[3] + 0x10 + iVar10);
      puVar12[4] = *(uint8_t *)(pbVar11[4] + 0x10 + iVar10);
      pbVar11 += 6;
      puVar12 += 6;
      puVar12[-1] = *(uint8_t *)(pbVar11[-1] + 0x10 + iVar10);
      puVar12[0] = *(uint8_t *)(pbVar11[0] + 0x10 + iVar10);
      puVar12[1] = *(uint8_t *)(pbVar11[1] + 0x10 + iVar10);
      puVar12[2] = *(uint8_t *)(pbVar11[2] + 0x10 + iVar10);
      puVar12[3] = *(uint8_t *)(pbVar11[3] + 0x10 + iVar10);
      puVar12[4] = *(uint8_t *)(pbVar11[4] + 0x10 + iVar10);

      /* axis snapping for presets 2 and 3 */
      if (*(int16_t *)((char *)0x46b834 + iVar13) == 2 ||
          *(int16_t *)((char *)0x46b834 + iVar13) == 3) {
        uVar7 = (uint16_t)(*(float *)0x2533c0 <= ly ? 0 : 2);
        uVar8 = (uint16_t)(*(float *)0x2533c0 <= ry ? 0 : 2);
        lmag = sqrtf(lx * lx + ly * ly);
        rmag = sqrtf(rx * rx + ry * ry);
        fVar1 = fabsf(
          lang - *(float *)((char *)0x280f84 +
                            (int16_t)((lx < *(float *)0x2533c0) | uVar7) * 4));
        if (*(double *)0x281148 <= fVar1) {
          if (fabsf(lx) <= fabsf(ly)) {
            local_20 = *(float *)0x2533c0 <= ly ? 1 : -1;
            lx = 0.0f;
            ly = (float)local_20 * lmag;
          } else {
            local_20 = *(float *)0x2533c0 <= lx ? 1 : -1;
            ly = 0.0f;
            lx = (float)local_20 * lmag;
          }
        } else if (fabsf(lang) < *(float *)0x254a58 ||
                   *(float *)0x26af48 < fabsf(lang)) {
          local_20 = *(float *)0x2533c0 <= lx ? 1 : -1;
          lx = (float)local_20 * lmag;
          local_20 = *(float *)0x2533c0 <= ly ? 1 : -1;
          ly = (float)local_20 * lmag *
               (*(double *)0x2573d8 - fVar1 * *(double *)0x281140);
        } else {
          local_20 = *(float *)0x2533c0 <= ly ? 1 : -1;
          ly = (float)local_20 * lmag;
          local_20 = *(float *)0x2533c0 <= lx ? 1 : -1;
          lx = (float)local_20 * lmag *
               (*(double *)0x2573d8 - fVar1 * *(double *)0x281140);
        }
        fVar2 = fabsf(
          rang - *(float *)((char *)0x280f84 +
                            (int16_t)((rx < *(float *)0x2533c0) | uVar8) * 4));
        if (*(double *)0x281138 <= fVar2) {
          if (fabsf(ry) < fabsf(rx)) {
            local_20 = *(float *)0x2533c0 <= rx ? 1 : -1;
            ry = 0.0f;
            rx = (float)local_20 * rmag;
          } else {
            local_20 = *(float *)0x2533c0 <= ry ? 1 : -1;
            rx = 0.0f;
            ry = (float)local_20 * rmag;
          }
        } else if (fabsf(rang) < *(float *)0x254a58 ||
                   *(float *)0x26af48 < fabsf(rang)) {
          local_20 = *(float *)0x2533c0 <= rx ? 1 : -1;
          rx = (float)local_20 * rmag;
          local_20 = *(float *)0x2533c0 <= ry ? 1 : -1;
          ry = (float)local_20 * rmag *
               (*(double *)0x2573d8 - fVar2 * *(double *)0x281140);
        } else {
          local_20 = *(float *)0x2533c0 <= ry ? 1 : -1;
          ry = (float)local_20 * rmag;
          local_20 = *(float *)0x2533c0 <= rx ? 1 : -1;
          rx = (float)local_20 * rmag *
               (*(double *)0x2573d8 - fVar2 * *(double *)0x281140);
        }
      }

      /* inversion flags */
      cVar6 = ((char *)0x46b836)[iVar13];
      if (cVar6 == '\0' && ((char *)0x46b837)[iVar13] != '\0') {
        int _player = local_18;
        asm volatile("" : "+a"(_player));
        cVar6 = ((char (*)(void))0xce8c0)();
      }

      /* output axes per joystick preset */
      switch (*(int16_t *)((char *)0x46b834 + iVar13)) {
      case 0:
        ((float *)0x46b890)[local_18 * 7] =
          *(char *)(iVar10 + 0x1a) != '\0' ? 1.0f :
          *(char *)(iVar10 + 0x1b) != '\0' ? -1.0f :
                                             -lx;
        ((float *)0x46b88c)[local_18 * 7] =
          *(char *)(iVar10 + 0x18) != '\0' ? 1.0f :
          *(char *)(iVar10 + 0x19) != '\0' ? -1.0f :
                                             ly;
        ((float *)0x46b894)[local_18 * 7] = -rx;
        ((float *)0x46b898)[local_18 * 7] =
          cVar6 == '\0' ? *(float *)0x2533c8 * ry : *(float *)0x255e94 * ry;
        ((char *)0x46b8f4)[local_18] = 1;
        break;
      case 1:
        ((float *)0x46b894)[local_18 * 7] =
          *(char *)(iVar10 + 0x1a) != '\0' ? 1.0f :
          *(char *)(iVar10 + 0x1b) != '\0' ? -1.0f :
                                             -lx;
        {
          float fv = *(float *)0x2533c8;
          if (*(char *)(iVar10 + 0x18) == '\0') {
            if (*(char *)(iVar10 + 0x19) == '\0') {
              fv = cVar6 != '\0' ? *(float *)0x255e94 * ly :
                                   *(float *)0x2533c8 * ly;
            } else if (cVar6 == '\0') {
              fv = *(float *)0x255e94;
            }
          } else if (cVar6 != '\0') {
            fv = *(float *)0x255e94;
          }
          ((float *)0x46b898)[local_18 * 7] = fv;
        }
        ((float *)0x46b88c)[local_18 * 7] = ry;
        ((float *)0x46b890)[local_18 * 7] = -rx;
        ((char *)0x46b8f4)[local_18] = 1;
        break;
      case 2:
        ((float *)0x46b894)[local_18 * 7] =
          *(char *)(iVar10 + 0x1a) != '\0' ? 1.0f :
          *(char *)(iVar10 + 0x1b) != '\0' ? -1.0f :
                                             -lx;
        ((float *)0x46b88c)[local_18 * 7] =
          *(char *)(iVar10 + 0x18) != '\0' ? 1.0f :
          *(char *)(iVar10 + 0x19) != '\0' ? -1.0f :
                                             ly;
        ((float *)0x46b890)[local_18 * 7] = -rx;
        ((float *)0x46b898)[local_18 * 7] =
          cVar6 == '\0' ? *(float *)0x2533c8 * ry : *(float *)0x255e94 * ry;
        ((char *)0x46b8f4)[local_18] = 1;
        break;
      case 3:
        ((float *)0x46b890)[local_18 * 7] =
          *(char *)(iVar10 + 0x1a) != '\0' ? 1.0f :
          *(char *)(iVar10 + 0x1b) != '\0' ? -1.0f :
                                             -lx;
        {
          float fv = *(float *)0x2533c8;
          if (*(char *)(iVar10 + 0x18) == '\0') {
            if (*(char *)(iVar10 + 0x19) == '\0') {
              fv = cVar6 != '\0' ? *(float *)0x255e94 * ly :
                                   *(float *)0x2533c8 * ly;
            } else if (cVar6 == '\0') {
              fv = *(float *)0x255e94;
            }
          } else if (cVar6 != '\0') {
            fv = *(float *)0x255e94;
          }
          ((float *)0x46b898)[local_18 * 7] = fv;
        }
        ((float *)0x46b88c)[local_18 * 7] = ry;
        ((float *)0x46b894)[local_18 * 7] = -rx;
        ((char *)0x46b8f4)[local_18] = 1;
        break;
      default:
        error(2, "unknown joystick preset");
        ((char *)0x46b8f4)[local_18] = 1;
        break;
      }
    }
  }
}
/* --- input_abstraction.obj batch drafts (2026-07-26) --- */

/* input_abstraction_get_local_player_preferences (0xce6c0) — readable C lift. */
void input_abstraction_get_local_player_preferences(short local_player_index,
                                                    void *preferences_out)
{
  if (local_player_index < 0 || local_player_index >= 4) {
    display_assert((const char *)0x280fa0, (const char *)0x280fe4, 0x1ef, 1);
    system_exit(-1);
  }
  if (!preferences_out) {
    display_assert((const char *)0x280f94, (const char *)0x280fe4, 0x1f0, 1);
    system_exit(-1);
  }
  csmemcpy(preferences_out, (void *)(0x46b820 + (int)local_player_index * 0x18),
           0x18);
}

/* input_abstraction_update_local_player_preferences (0xce740) — readable C lift. */
void input_abstraction_update_local_player_preferences(short local_player_index,
                                                       void *preferences_in)
{
  if (local_player_index < 0 || local_player_index >= 4) {
    display_assert((const char *)0x281054, (const char *)0x280fe4, 0x1fb, 1);
    system_exit(-1);
  }
  if (!preferences_in) {
    display_assert((const char *)0x280f94, (const char *)0x280fe4, 0x1fc, 1);
    system_exit(-1);
  }
  if (((unsigned char *)preferences_in)[0x10] != 0xc ||
      ((unsigned char *)preferences_in)[0x11] != 0xd) {
    display_assert((const char *)0x281010, (const char *)0x280fe4, 0x1ff, 1);
    system_exit(-1);
  }
  csmemcpy((void *)(0x46b820 + (int)local_player_index * 0x18), preferences_in,
           0x18);
}

/* input_abstraction_update_device_changes (0xce840) — readable C lift. */
void input_abstraction_update_device_changes(int device_flags)
{
  unsigned int now;

  if (!*(unsigned char *)0x46b8f8) {
    return;
  }
  if (device_flags) {
    now = system_milliseconds();
    if (now - *(unsigned int *)0x46b8f0 >= 0x7d0u ||
        (*(unsigned int *)0x46b8fc != 0 &&
         now - *(unsigned int *)0x46b8fc >= 0x7d0u)) {
      error(2, (const char *)0x281094);
      bink_playback_stop();
    }
  }
  if ((device_flags & 0xfff000) != 0 && *(unsigned int *)0x46b8fc == 0) {
    *(unsigned int *)0x46b8fc = system_milliseconds();
  }
}


/* input_abstraction_print_config_control (0xce8c0) — XBE naked draft (batch 127). */
#if defined(__clang__)
static void (*const bce8c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bce8c0_exitfn)(int) = system_exit;
static int (*const bce8c0_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static int (*const bce8c0_c119270)(data_t *data, int absolute_index) = datum_absolute_index_to_index;
static void *(*const bce8c0_tryget)(int, int) = object_try_and_get_and_verify_type;
static void *(*const bce8c0_get)(int, int) = object_get_and_verify_type;
static void *(*const bce8c0_tag)(int, int) = tag_get;
static void *(*const bce8c0_elem)(void *, int, int) = tag_block_get_element;

__attribute__((naked, noinline))
void input_abstraction_print_config_control(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "testw %%si, %%si\n\t"
      "jl .Linput_abstraction_print_config_control_1\n\t"
      "cmpw $4, %%si\n\t"
      "jl .Linput_abstraction_print_config_control_2\n\t"
      ".Linput_abstraction_print_config_control_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x239\n\t"
      "pushl $0x280fe4\n\t"
      "pushl $0x2810d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Linput_abstraction_print_config_control_2:\n\t"
      "pushl %%esi\n\t"
      "call *%[cba3c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Linput_abstraction_print_config_control_4\n\t"
      "pushl %%eax\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119270]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Linput_abstraction_print_config_control_4\n\t"
      "movl 0x34(%%eax), %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "call *%[tryget]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Linput_abstraction_print_config_control_4\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Linput_abstraction_print_config_control_4\n\t"
      "cmpw $-1, 0x2a0(%%esi)\n\t"
      "je .Linput_abstraction_print_config_control_4\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x76656869\n\t"
      "call *%[tag]\n\t"
      "movw 0x2f4(%%eax), %%cx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $3, %%cx\n\t"
      "je .Linput_abstraction_print_config_control_3\n\t"
      "cmpw $5, %%cx\n\t"
      "jne .Linput_abstraction_print_config_control_4\n\t"
      ".Linput_abstraction_print_config_control_3:\n\t"
      "movswl 0x2a0(%%esi), %%ecx\n\t"
      "pushl $0x11c\n\t"
      "pushl %%ecx\n\t"
      "addl $0x2e4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movb (%%eax), %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $4, %%cl\n\t"
      "movb $1, %%al\n\t"
      "jne .Linput_abstraction_print_config_control_5\n\t"
      ".Linput_abstraction_print_config_control_4:\n\t"
      "movb %%bl, %%al\n\t"
      ".Linput_abstraction_print_config_control_5:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      : [assert] "m"(bce8c0_assert), [exitfn] "m"(bce8c0_exitfn), [cba3c0] "m"(bce8c0_cba3c0), [c119270] "m"(bce8c0_c119270), [tryget] "m"(bce8c0_tryget), [get] "m"(bce8c0_get), [tag] "m"(bce8c0_tag), [elem] "m"(bce8c0_elem)
      : "memory");
}
#else
#error "input_abstraction_print_config_control: clang naked draft required"
#endif

/* --- input_abstraction.obj orphan shells (2026-07-26) --- */

/* 0xce7f0 */
void *input_abstraction_get_input_state(int gamepad_index)
{
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0xce803 */
  /* cmp (int16_t)esi, 4 -> jl 0xce823 */
  display_assert((char *)0x00280fa0, (char *)0x00280fe4, 521, 0);
  system_exit(0);
  return NULL;

  (void)esi;
}
