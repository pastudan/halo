#!/usr/bin/env python3
"""Generate main.obj batch1 draft implementations + disassembly artifact."""
from __future__ import annotations

import json
import re
from pathlib import Path

from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "tools" / "main_batch1_fragment.c"
DISASM_OUT = ROOT / "artifacts" / "main_batch1_disasm.txt"
OBJECT = "main.obj"

IMPL = r'''
/* --- main.obj batch1 drafts (2026-07-26) --- */

bool cache_files_give_time_to_precache(const char *name);
void main_menu_active(char active);

char gamepad_button_is_down(int16_t button)
{
  if (button < 0 || button >= 0x10) {
    display_assert((char *)0x28b078, "c:\\halo\\SOURCE\\main\\main.c", 0xf5, 1);
    system_exit(-1);
  }
  {
    int i;
    for (i = 0; i < 4; i++) {
      if (input_has_gamepad((int16_t)i)) {
        void *state = input_get_gamepad_state(i);
        if ((char)*((char *)state + 0x10 + button) > 0)
          return 1;
      }
    }
  }
  return 0;
}

void main_disallow_persistent_storage(void)
{
  *(char *)0x46da54 = 0;
}

void main_set_map_name(const char *name)
{
  csstrncpy((char *)0x46da55, name, 0xff);
  *(char *)0x46da43 = 0;
  *(char *)0x46db54 = 0;
  *(char *)0x46da54 = 1;
  if (game_in_editor() || game_in_progress()) {
    if (*(int16_t *)0x46da0c == 0)
      *(char *)0x46da25 = 1;
  }
}

void main_set_multiplayer_map_name(const char *name)
{
  csstrncpy((char *)0x46db55, name, 0xff);
  *(char *)0x46dc54 = 0;
  cache_files_give_time_to_precache((char *)0x46db55);
}

const char *main_get_map_name(void)
{
  return (const char *)0x46da55;
}

void main_set_difficulty(int16_t difficulty)
{
  if (difficulty >= 0 && difficulty < 4)
    *(int16_t *)0x31fa90 = difficulty;
}

void main_reset_map(void)
{
  *(int16_t *)0x46da40 = -1;
  *(char *)0x46da28 = 0;
  *(char *)0x46da24 = 1;
  *(char *)0x46da3b = 0;
}

void main_revert_map(void)
{
  *(int16_t *)0x46da40 = -1;
  *(char *)0x46da28 = 0;
  *(char *)0x46da26 = 1;
  *(char *)0x46da3b = 0;
}

void main_skip_cinematic(void)
{
  *(int16_t *)0x46da40 = -1;
  *(char *)0x46da28 = 0;
  *(char *)0x46da27 = 1;
}

void main_save_map_nonsafe(void)
{
  *(char *)0x46da28 = 1;
  *(char *)0x46da29 = 0;
}

char main_saving_map(void)
{
  return *(char *)0x46da28;
}

void main_save_cancel(void)
{
  *(char *)0x46da28 = 0;
}

void main_save_map_safe(void)
{
  if (*(char *)0x46da28 != 0 && *(char *)0x46da2a != 0)
    return;
  *(char *)0x46da28 = 1;
  *(char *)0x46da29 = 1;
  *(char *)0x46da2a = 1;
  *(int *)0x46da2c = 0;
  *(int *)0x46da30 = 0;
  *(int16_t *)0x46da38 = 0;
}

void main_won_map(void)
{
  *(char *)0x46da28 = 0;
  *(char *)0x46da3a = 1;
}

void FUN_00100380(void)
{
  *(char *)0x46da28 = 0;
  *(char *)0x46da3b = 1;
}

void main_respawn(char flag)
{
  *(char *)0x46da3c = 1;
  if (flag)
    *(int16_t *)0x46da4e = 0x5b;
}

void main_save_core(void)
{
  *(char *)0x46da3d = 1;
  csstrcpy((char *)0x46dd55, (char *)0x28b198);
}

void main_save_core_name(const char *name)
{
  if (csstrlen(name) >= 0x40) {
    display_assert((char *)0x28b1a4, "c:\\halo\\SOURCE\\main\\main.c", 0x3a5, 0);
  }
  csstrncpy((char *)0x46dd55, name, 0x3f);
  *(char *)0x46da3d = 1;
}

void main_load_core(void)
{
  *(char *)0x46da3e = 1;
  csstrcpy((char *)0x46dd55, (char *)0x28b198);
}

void main_load_core_at_startup(void)
{
  *(char *)0x46da3f = 1;
  csstrcpy((char *)0x46dd55, (char *)0x28b198);
}

void main_load_core_name(const char *name)
{
  if (csstrlen(name) >= 0x40) {
    display_assert((char *)0x28b1a4, "c:\\halo\\SOURCE\\main\\main.c", 0x3c9, 0);
  }
  csstrncpy((char *)0x46dd55, name, 0x3f);
  *(char *)0x46da3e = 1;
}

void main_load_core_name_at_startup(const char *name)
{
  if (csstrlen(name) >= 0x40) {
    display_assert((char *)0x28b1a4, "c:\\halo\\SOURCE\\main\\main.c", 0x3d7, 0);
  }
  csstrncpy((char *)0x46dd55, name, 0x3f);
  *(char *)0x46da3f = 1;
}

void main_switch_structure_bsp(int16_t bsp_index)
{
  void *scenario = global_scenario_get();
  if (bsp_index < 0 || bsp_index >= *(int *)((char *)scenario + 0x5a4)) {
    console_warning((char *)0x28b1e0, (int)bsp_index);
    return;
  }
  if (bsp_index == *(int16_t *)0x326a0c) {
    console_warning((char *)0x28b20c, (int)bsp_index);
    return;
  }
  *(int16_t *)0x46da40 = bsp_index;
  hud_load(1);
}

void main_skip(int16_t level)
{
  if (level > 0xf) {
    error(2, (char *)0x28b238);
    return;
  }
  *(int16_t *)0x46da4a = level;
  *(char *)0x46da49 = 1;
}

void main_menu_unload(void)
{
  ui_widget_stop_attract_mode();
  main_menu_active(0);
  *(char *)0x46da42 = 0;
}

void main_menu_switch_to_single_player(void)
{
  *(char *)0x46da25 = 1;
}

void main_set_game_connection_to_film_playback(void)
{
  *(char *)0x46da45 = 1;
}

int main_get_solo_level_from_name(const char *map_name)
{
  char buf[0x80];
  static const struct {
    const char *needle;
    int index;
  } levels[] = {
      {(char *)0x284a8c, 0}, {(char *)0x284a50, 1}, {(char *)0x284a14, 2},
      {(char *)0x2849d8, 3}, {(char *)0x28499c, 4}, {(char *)0x284960, 5},
      {(char *)0x284924, 6}, {(char *)0x2848e8, 7}, {(char *)0x2848ac, 8},
      {(char *)0x284870, 9},
  };
  int i;

  csstrncpy(buf, map_name, 0x7f);
  buf[0x7f] = 0;
  csstr_tolower(buf);
  for (i = 0; i < 10; i++) {
    if (crt_strstr(buf, levels[i].needle) != 0)
      return levels[i].index;
  }
  return -1;
}

int main_get_current_solo_level(void)
{
  return main_get_solo_level_from_name((const char *)0x46da55);
}

const char *main_get_solo_level_name(int16_t index)
{
  if (index < 0 || index >= 0xa)
    return 0;
  return *(const char **)(0x31fa9c + (int)index * 4);
}

void main_run_demos(void)
{
  *(char *)0x46da44 = 1;
}

int16_t main_get_window_count(void)
{
  if (game_engine_force_single_screen() || cinematic_in_progress())
    return 1;
  if (local_player_count() < 1)
    return 1;
  if (local_player_count() > 4)
    return 4;
  return local_player_count();
}

void main_crash(int unused)
{
  *(volatile int *)0 = (int)0x28b5a8;
}

void main_print_version(void)
{
  console_printf(0, (char *)0x28b5d4);
}

void main_save_map_no_timeout(void)
{
  if (*(char *)0x46da28 != 0 && *(char *)0x46da2a == 0)
    return;
  *(char *)0x46da28 = 1;
  *(char *)0x46da29 = 1;
  *(int *)0x46da2c = 0;
  *(int *)0x46da30 = 0;
  *(int16_t *)0x46da38 = 0;
  *(char *)0x46da2a = 0;
}

void main_roll_credits(void)
{
  error(2, (char *)0x28b68c);
  main_menu_load();
  FUN_000dc110();
}

void FUN_001008a0(int num_players /* @<ebx> */, int *horizontal_out,
                  int *vertical_out)
{
  int horizontal = 1;
  int vertical = 1;

  if (num_players <= 0) {
    display_assert((char *)0x28b294, "c:\\halo\\SOURCE\\main\\main.c", 0x51c, 1);
    system_exit(-1);
  }
  if (num_players > 1) {
    while (vertical * horizontal < num_players) {
      if (horizontal < vertical)
        horizontal++;
      else {
        horizontal = 1;
        vertical++;
      }
    }
  }
  *horizontal_out = horizontal;
  *vertical_out = vertical;
}

void main_movie_start(float frame_rate)
{
  void *bitmap;

  if (main_globals_movie != NULL) {
    display_assert((char *)0x28b58c, "c:\\halo\\SOURCE\\main\\main.c", 0xa6b, 1);
    system_exit(-1);
  }
  bitmap = bitmap_2d_new(0x280, 0x1e0, 0, 0xa);
  main_globals_movie = bitmap;
  if (bitmap == NULL)
    return;
  directory_create_or_delete_contents();
  movie_frame_count = 0;
  if (frame_rate != *(float *)0x253f44) {
    *(float *)0x46da20 = *(float *)0x2533c8 / frame_rate;
  } else {
    *(float *)0x46da20 = 0.03333333507180214f;
  }
  game_time_set_speed(1.0f);
}
'''

DECLS = {
    "0xffef0": "char gamepad_button_is_down(int16_t button);",
    "0xfff90": "void main_disallow_persistent_storage(void);",
    "0xfffa0": "void main_set_map_name(const char *name);",
    "0x100010": "void main_set_multiplayer_map_name(const char *name);",
    "0x100040": "const char *main_get_map_name(void);",
    "0x100060": "void main_set_difficulty(int16_t difficulty);",
    "0x1002a0": "void main_reset_map(void);",
    "0x1002c0": "void main_revert_map(void);",
    "0x1002e0": "void main_skip_cinematic(void);",
    "0x100300": "void main_save_map_nonsafe(void);",
    "0x100310": "char main_saving_map(void);",
    "0x100320": "void main_save_cancel(void);",
    "0x100330": "void main_save_map_safe(void);",
    "0x100370": "void main_won_map(void);",
    "0x100380": "void FUN_00100380(void);",
    "0x100390": "void main_respawn(char flag);",
    "0x1003b0": "void main_save_core(void);",
    "0x1003d0": "void main_save_core_name(const char *name);",
    "0x100420": "void main_load_core(void);",
    "0x100440": "void main_load_core_at_startup(void);",
    "0x100460": "void main_load_core_name(const char *name);",
    "0x1004b0": "void main_load_core_name_at_startup(const char *name);",
    "0x100500": "void main_switch_structure_bsp(int16_t bsp_index);",
    "0x100560": "void main_skip(int16_t level);",
    "0x100690": "void main_menu_unload(void);",
    "0x1006d0": "void main_menu_switch_to_single_player(void);",
    "0x1006e0": "void main_set_game_connection_to_film_playback(void);",
    "0x1006f0": "int main_get_solo_level_from_name(const char *map_name);",
    "0x100860": "int main_get_current_solo_level(void);",
    "0x100870": "const char *main_get_solo_level_name(int16_t index);",
    "0x100890": "void main_run_demos(void);",
    "0x100b00": "int16_t main_get_window_count(void);",
    "0x101cb0": "void main_crash(int unused);",
    "0x101cc0": "void main_print_version(void);",
    "0x101ec0": "void main_save_map_no_timeout(void);",
    "0x102070": "void main_roll_credits(void);",
    "0x1008a0": "void FUN_001008a0(int num_players @<ebx>, int *horizontal_out, int *vertical_out);",
    "0x101bc0": "void main_movie_start(float frame_rate);",
}

SKIP_DISASM = {"0xe8e20", "0xffeb0"}


def write_disasm() -> None:
    xbe = Xbe.from_file(str(ROOT / "halo-patched/cachebeta.xbe"))
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    kb = json.loads((ROOT / "kb.json").read_text())
    obj = next(o for o in kb["objects"] if o["name"] == OBJECT)
    fns = sorted(obj["functions"], key=lambda f: int(f["addr"], 16))
    addrs = [(int(f["addr"], 16), f) for f in fns]

    addr_name: dict[int, str] = {}
    for o in kb["objects"]:
        for f in o.get("functions", []):
            m = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", f.get("decl") or "")
            if m:
                addr_name[int(f["addr"], 16)] = m.group(1)

    def get_bytes(va: int, end: int) -> bytes:
        for sec in xbe.sections.values():
            s = sec.header.virtual_addr
            if s <= va < s + sec.header.virtual_size:
                return bytes(sec.data[va - s : end - s])
        raise RuntimeError(hex(va))

    chunks: list[str] = []
    for i, (va, f) in enumerate(addrs):
        if f.get("ported") in (True, False):
            continue
        if f["addr"] in SKIP_DISASM:
            continue
        end = addrs[i + 1][0] if i + 1 < len(addrs) else va + 0x200
        size = end - va
        data = get_bytes(va, min(end, va + 0x800))
        insns = list(md.disasm(data, va))
        lines: list[str] = []
        calls = 0
        for x in insns:
            if x.address >= end:
                break
            line = f"  {x.address:08x}: {x.mnemonic:8} {x.op_str}"
            if x.mnemonic == "call" and x.op_str.startswith("0x"):
                t = int(x.op_str, 16)
                nm = addr_name.get(t, "")
                if nm:
                    line += f"  ; {nm}"
                calls += 1
            lines.append(line)
        name = re.search(
            r"([A-Za-z_][A-Za-z0-9_]*)\s*\(",
            f.get("decl", "void FUN(void);"),
        ).group(1)
        header = (
            f"\n=== {name} @ {f['addr']} end~{end:08x} "
            f"insns={len(lines)} calls={calls} ===\n"
        )
        body = "\n".join(lines[:200])
        if len(lines) > 200:
            body += f"\n  ... ({len(lines) - 200} more insns)"
        chunks.append(header + body)

    DISASM_OUT.parent.mkdir(exist_ok=True)
    DISASM_OUT.write_text("\n".join(chunks) + ("\n" if chunks else ""))
    print("wrote", DISASM_OUT, len(chunks), "functions")


def main() -> None:
    OUT.write_text(IMPL.lstrip() + "\n")
    write_disasm()
    print("wrote", OUT, len(DECLS), "functions")


if __name__ == "__main__":
    main()
