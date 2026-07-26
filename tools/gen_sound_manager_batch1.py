#!/usr/bin/env python3
"""Generate sound_manager.obj batch1 draft implementations."""
from __future__ import annotations

from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "tools" / "sound_manager_batch1_fragment.c"

IMPL = r'''
/* --- sound_manager.obj batch1 drafts (2026-07-25) --- */

void FUN_001ac030(int unit_handle, char flag)
{
  if (unit_handle == -1)
    return;
  {
    char *unit = (char *)object_get_and_verify_type(unit_handle, 3);
    if (flag)
      *(uint32_t *)(unit + 0x1b4) &= ~0x10000u;
    else
      *(uint32_t *)(unit + 0x1b4) |= 0x10000u;
  }
}

void FUN_001ac070(int unit_handle, char flag)
{
  if (unit_handle == -1)
    return;
  {
    char *unit = (char *)object_get_and_verify_type(unit_handle, 3);
    unit[0x258] = flag;
    object_set_region_count(unit_handle, 6);
  }
}

void FUN_001ac0a0(int unit_handle, char flag)
{
  if (unit_handle == -1)
    return;
  {
    char *unit = (char *)object_get_and_verify_type(unit_handle, 3);
    if (flag)
      *(uint32_t *)(unit + 0x1b4) |= 0x4000u;
    else
      *(uint32_t *)(unit + 0x1b4) &= ~0x4000u;
  }
}

int FUN_001AC0E0(int unit_handle)
{
  if (unit_handle == -1)
    return 0;
  {
    char *unit = (char *)object_get_and_verify_type(unit_handle, 3);
    int anim_tag;
    void *anim_elem;
    int frame_delta;

    if (unit[0x253] != 0x1c)
      return 0;

    anim_tag = (int)tag_get(0x616e7472, *(int *)(unit + 0x7c));
    anim_elem = tag_block_get_element((void *)(anim_tag + 0x74),
                                      (int)*(int16_t *)(unit + 0x80), 0xb4);
    frame_delta = (int)*(int16_t *)((char *)anim_elem + 0x22) -
                  (int)*(int16_t *)(unit + 0x82) - 2;
    if (frame_delta <= 0)
      return frame_delta;
    return 0;
  }
}

char FUN_001ac150(int unit_handle)
{
  if (unit_handle == -1)
    return 0;
  return (char)(*(char *)((char *)object_get_and_verify_type(unit_handle, 3) +
                          0x253) == 0x1c);
}

int16_t sound_dispose(int unit_handle)
{
  char *unit = (char *)object_get_and_verify_type(unit_handle, 3);
  int16_t slot;

  for (slot = 0; slot < 4; slot++) {
    int weapon_handle = *(int *)(unit + 0x2a8 + (int)slot * 4);
    if (weapon_handle == -1)
      continue;
    if (!weapon_has_activity(weapon_handle))
      return slot;
  }
  return (int16_t)-1;
}

char FUN_001ac3b0(int unit_handle, int weapon_handle)
{
  char *unit = (char *)object_get_and_verify_type(unit_handle, 3);
  int i;

  for (i = 0; i < 4; i++) {
    if (*(int *)(unit + 0x2a8 + i * 4) == weapon_handle)
      return 1;
  }
  return 0;
}

void FUN_001be100(void *perm_entry)
{
  char *entry = (char *)perm_entry;
  datum_get(*(data_t **)0x4e9368, *(int *)(entry + 0x2c));
  if ((uint8_t)entry[5] < 0xffu) {
    entry[5]++;
    return;
  }
  *(int16_t *)0x5054ea += 1;
}

void FUN_001be140(void *perm_entry)
{
  char *entry = (char *)perm_entry;
  datum_get(*(data_t **)0x4e9368, *(int *)(entry + 0x2c));
  if (entry[5] != 0) {
    entry[5]--;
    return;
  }
  *(int16_t *)0x5054ea += 1;
}

char FUN_001be170(int cache_handle)
{
  char *entry = (char *)datum_get(*(data_t **)0x4e9368, cache_handle);
  if (entry[2] == 0 && entry[4] == 0 && entry[5] == 0)
    return 0;
  return 1;
}

char sound_try_and_get(int sound_index)
{
  int index =
    datum_absolute_index_to_index(*(data_t **)0x4fdba4, sound_index);
  int result = -index;
  result = result - result - (result != 0);
  result = -result;
  return (char)result;
}

void sound_enable(char enabled)
{
  *(char *)0x4eaf41 = enabled;
}

char sound_scripted_dialog_is_playing(void)
{
  return (char)(game_time_get() < *(int *)0x4eaf44);
}

void sound_manager_set_sound_environment(void *environment)
{
  int i;
  int *dst = (int *)0x4eb068;
  int *src = (int *)environment;
  for (i = 0; i < 0x12; i++)
    dst[i] = src[i];
}

void FUN_001cb9d0(void)
{
  unsigned int tick = system_milliseconds();
  float delta = (float)(int)(tick - *(unsigned int *)0x4eaf4c);
  *(unsigned int *)0x4eaf4c = tick;
  *(float *)0x4eaf50 = delta * *(float *)0x25bc08;
}

float FUN_001cba00(float scale, float a, float b, float t)
{
  return ((b - a) * t + a) * scale;
}
'''

DECLS = {
    "0x1ac030": "void FUN_001ac030(int unit_handle, char flag);",
    "0x1ac070": "void FUN_001ac070(int unit_handle, char flag);",
    "0x1ac0a0": "void FUN_001ac0a0(int unit_handle, char flag);",
    "0x1ac0e0": "int FUN_001AC0E0(int unit_handle);",
    "0x1ac150": "char FUN_001ac150(int unit_handle);",
    "0x1ac350": "int16_t sound_dispose(int unit_handle);",
    "0x1ac3b0": "char FUN_001ac3b0(int unit_handle, int weapon_handle);",
    "0x1be100": "void FUN_001be100(void *cache_entry);",
    "0x1be140": "void FUN_001be140(void *cache_entry);",
    "0x1be170": "char FUN_001be170(int cache_handle);",
    "0x1cb960": "char sound_try_and_get(int sound_index);",
    "0x1cb980": "void sound_enable(char enabled);",
    "0x1cb990": "char sound_scripted_dialog_is_playing(void);",
    "0x1cb9b0": "void sound_manager_set_sound_environment(void *environment);",
    "0x1cb9d0": "void FUN_001cb9d0(void);",
    "0x1cba00": "float FUN_001cba00(float scale, float a, float b, float t);",
}


def main() -> None:
    OUT.write_text(IMPL.lstrip() + "\n")
    print("wrote", OUT, len(DECLS), "functions")


if __name__ == "__main__":
    main()
