#!/usr/bin/env python3
"""Batch-2 naked→C lifts (globals via absolute XBE addrs, matching Capstone)."""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
KB_PATH = ROOT / "kb.json"

LIFTS: dict[int, tuple[str, str, str, str | None]] = {}


def L(addr: int, source: str, name: str, body: str, decl: str | None = None):
    LIFTS[addr] = (source, name, body.strip() + "\n", decl)


L(
    0xF5640,
    "items/items.c",
    "FUN_000f5640",
    """
/* FUN_000f5640 (0xf5640) — readable C lift. */
char FUN_000f5640(void)
{
  return *(char *)0x46cef0;
}
""",
)

L(
    0xF5650,
    "items/items.c",
    "FUN_000f5650",
    """
/* FUN_000f5650 (0xf5650) — readable C lift. */
char FUN_000f5650(void)
{
  return *(char *)0x46cf06;
}
""",
)

L(
    0xE3C90,
    "interface/ui_widget.c",
    "ui_widgets_set_fade_value",
    """
/* ui_widgets_set_fade_value (0xe3c90) — readable C lift. */
void ui_widgets_set_fade_value(float fade)
{
  *(float *)0x46cc4c = fade;
}
""",
)

L(
    0x100300,
    "main/main.c",
    "main_save_map_nonsafe",
    """
/* main_save_map_nonsafe (0x100300) — readable C lift. */
void main_save_map_nonsafe(void)
{
  *(char *)0x46da28 = 1;
  *(char *)0x46da29 = 0;
}
""",
)

L(
    0x100370,
    "main/main.c",
    "main_won_map",
    """
/* main_won_map (0x100370) — readable C lift. */
void main_won_map(void)
{
  *(char *)0x46da28 = 0;
  *(char *)0x46da3a = 1;
}
""",
)

L(
    0x100380,
    "main/main.c",
    "FUN_00100380",
    """
/* FUN_00100380 (0x100380) — readable C lift. */
void FUN_00100380(void)
{
  *(char *)0x46da28 = 0;
  *(char *)0x46da3b = 1;
}
""",
)

L(
    0xA57A0,
    "game/cheats.c",
    "FUN_000a57a0",
    """
/* FUN_000a57a0 (0xa57a0) — readable C lift: 1/sqrt(x). */
float FUN_000a57a0(float x)
{
  return *(float *)0x2533c8 / x87_sqrt(x);
}
""",
    "float FUN_000a57a0(float x);",
)

L(
    0x1A8770,
    "units/units.c",
    "FUN_001a8770",
    """
/* FUN_001a8770 (0x1a8770) — readable C lift. */
char FUN_001a8770(void *anim_state)
{
  unsigned char state = *((unsigned char *)anim_state + 0xb);

  return state >= 3 && state <= 4;
}
""",
    "char FUN_001a8770(void *anim_state@<ecx>);",
)

L(
    0xA2A90,
    "effects/player_effects.c",
    "FUN_000a2a90",
    """
/* FUN_000a2a90 (0xa2a90) — readable C lift: lerp(a, 1, t) = a+(1-a)*t. */
float FUN_000a2a90(float a, float t)
{
  return (*(float *)0x2533c8 - a) * t + a;
}
""",
    "float FUN_000a2a90(float a, float t);",
)

L(
    0x130F10,
    "main/telnet_console.c",
    "FUN_00130f10",
    """
/* FUN_00130f10 (0x130f10) — readable C lift. */
void FUN_00130f10(void)
{
  if (*(int *)0x5a90d4 != 0) {
    *(int *)0x5a90d4 = 0;
  }
}
""",
)

L(
    0x131A00,
    "main/telnet_console.c",
    "FUN_00131a00",
    """
/* FUN_00131a00 (0x131a00) — readable C lift. */
void FUN_00131a00(void)
{
  if (*(int *)0x5a90d0 != 0) {
    *(int *)0x5a90d0 = 0;
  }
}
""",
)

L(
    0xA7470,
    "game/game.c",
    "FUN_000A7470",
    """
/* FUN_000A7470 (0xa7470) — readable C lift. */
int FUN_000A7470(void)
{
  int16_t v = *(int16_t *)(*(char **)0x4566ec + 0xe);

  if (v > 1) {
    return (int)v;
  }
  return 1;
}
""",
    "int FUN_000A7470(void);",
)

L(
    0x1002E0,
    "main/main.c",
    "main_skip_cinematic",
    """
/* main_skip_cinematic (0x1002e0) — readable C lift. */
void main_skip_cinematic(void)
{
  *(int16_t *)0x46da40 = (int16_t)0xffff;
  *(char *)0x46da28 = 0;
  *(char *)0x46da27 = 1;
}
""",
)

L(
    0x538D0,
    "ai/ai_debug.c",
    "FUN_000538d0",
    """
/* FUN_000538d0 (0x538d0) — readable C lift. */
int16_t FUN_000538d0(void)
{
  return *(int16_t *)(*(char **)0x5ab270 + 0x30);
}
""",
)

L(
    0x100060,
    "main/main.c",
    "main_set_difficulty",
    """
/* main_set_difficulty (0x100060) — readable C lift. */
void main_set_difficulty(int16_t difficulty)
{
  if (difficulty >= 0 && difficulty < 4) {
    *(int16_t *)0x31fa90 = difficulty;
  }
}
""",
)

L(
    0x100390,
    "main/main.c",
    "main_respawn",
    """
/* main_respawn (0x100390) — readable C lift. */
void main_respawn(char flag)
{
  *(char *)0x46da3c = 1;
  if (flag) {
    *(int16_t *)0x46da4e = 0x5b;
  }
}
""",
)

L(
    0x184B60,
    "render/render.c",
    "render_effects",
    """
/* render_effects (0x184b60) — readable C lift. */
void render_effects(int a0)
{
  char v = (char)a0;

  *(char *)0x32574d = v;
  *(char *)0x32574c = v;
  *(char *)0x32574b = v;
  *(char *)0x32574a = v;
}
""",
)

L(
    0xE3CB0,
    "interface/ui_widget.c",
    "widget_instance_count_children",
    """
/* widget_instance_count_children (0xe3cb0) — readable C lift. */
int widget_instance_count_children(void *widget)
{
  int count = 0;
  void *child;

  if (widget == NULL) {
    return 0;
  }
  child = *(void **)((char *)widget + 0x34);
  if (child == NULL) {
    return 0;
  }
  do {
    child = *(void **)((char *)child + 0x2c);
    count++;
  } while (child != NULL);
  return count;
}
""",
)

L(
    0x1002A0,
    "main/main.c",
    "main_reset_map",
    """
/* main_reset_map (0x1002a0) — readable C lift. */
void main_reset_map(void)
{
  *(int16_t *)0x46da40 = (int16_t)0xffff;
  *(char *)0x46da28 = 0;
  *(char *)0x46da24 = 1;
  *(char *)0x46da3b = 0;
}
""",
)

L(
    0x1002C0,
    "main/main.c",
    "main_revert_map",
    """
/* main_revert_map (0x1002c0) — readable C lift. */
void main_revert_map(void)
{
  *(int16_t *)0x46da40 = (int16_t)0xffff;
  *(char *)0x46da28 = 0;
  *(char *)0x46da26 = 1;
  *(char *)0x46da3b = 0;
}
""",
)

L(
    0x1939D0,
    "structures/structure_detail_objects.c",
    "structure_detail_objects_dispose",
    """
/* structure_detail_objects_dispose (0x1939d0) — readable C lift (empty). */
void structure_detail_objects_dispose(void)
{
}
""",
)

L(
    0x108DD0,
    "math/rectangles.c",
    "FUN_00108dd0",
    """
/* FUN_00108dd0 (0x108dd0) — readable C lift (floor(log2)+1 for n>1). */
int FUN_00108dd0(unsigned int value)
{
  int count = 0;

  if (value != 0) {
    value--;
    if (value != 1) {
      do {
        value >>= 1;
        count++;
      } while (value != 1);
    }
  }
  return count + 1;
}
""",
    "int FUN_00108dd0(unsigned int value);",
)

L(
    0x108DF0,
    "math/rectangles.c",
    "FUN_00108df0",
    """
/* FUN_00108df0 (0x108df0) — readable C lift (largest power-of-two <= n?). */
int FUN_00108df0(unsigned int value)
{
  int result = 1;
  int next;

  if ((int)value >= 2) {
    next = 2;
    do {
      result = next;
      next = result + result;
    } while (next <= (int)value);
  }
  return result;
}
""",
    "int FUN_00108df0(unsigned int value);",
)

L(
    0x4A6E0,
    "ai/ai_debug.c",
    "ai_debug_idle_look_clear",
    """
/* ai_debug_idle_look_clear (0x4a6e0) — readable C lift. */
void ai_debug_idle_look_clear(int actor_handle)
{
  *(char *)0x6323d4 = actor_handle != -1;
  *(int *)0x6323d8 = actor_handle;
  *(int16_t *)0x6323dc = 0;
}
""",
)

L(
    0xB6430,
    "game/player_control.c",
    "scripted_player_control_set_camera_control",
    """
/* scripted_player_control_set_camera_control (0xb6430) — readable C lift. */
void scripted_player_control_set_camera_control(char enable)
{
  unsigned int *flags = (unsigned int *)((char *)player_control_globals + 0xc);

  if (enable) {
    *flags &= ~1u;
  } else {
    *flags |= 1u;
  }
}
""",
)

L(
    0xE3B80,
    "interface/ui_widget.c",
    "event_controller_index_compatible_with_widget",
    """
/* event_controller_index_compatible_with_widget (0xe3b80) — readable C lift. */
bool event_controller_index_compatible_with_widget(void *widget, void *event_data)
{
  int16_t idx = *(int16_t *)((char *)event_data + 8);

  if (idx == (int16_t)0xffff) {
    return true;
  }
  if (idx == *(int16_t *)((char *)widget + 2)) {
    return true;
  }
  return false;
}
""",
)

L(
    0xA2DC0,
    "effects/player_effects.c",
    "scripted_player_effect_set_translation",
    """
/* scripted_player_effect_set_translation (0xa2dc0) — readable C lift. */
void scripted_player_effect_set_translation(int a0, float a1, float a2)
{
  char *g = *(char **)0x4557ec;

  *(int *)(g + 0x3c4) = a0;
  *(float *)(g + 0x3c8) = a1;
  *(float *)(g + 0x3cc) = a2;
}
""",
)

L(
    0xE3BB0,
    "interface/ui_widget.c",
    "set_ui_plasma_effect_color",
    """
/* set_ui_plasma_effect_color (0xe3bb0) — readable C lift. */
void set_ui_plasma_effect_color(float r, float g, float b, float a)
{
  *(float *)0x5aa460 = r;
  *(float *)0x5aa464 = g;
  *(float *)0x5aa468 = b;
  *(float *)0x5aa46c = a;
}
""",
)

L(
    0xE9FD0,
    "interface/ui_widget.c",
    "FUN_000e9fd0",
    """
/* FUN_000e9fd0 (0xe9fd0) — readable C lift. */
char FUN_000e9fd0(void *widget)
{
  *(int *)((char *)widget + 0x40) = 0;
  *(int16_t *)((char *)widget + 0x44) = 0;
  return 1;
}
""",
)

L(
    0x108D40,
    "math/rectangles.c",
    "FUN_00108d40",
    """
/* FUN_00108d40 (0x108d40) — readable C lift (rectangle2d equal). */
int FUN_00108d40(int *a, int *b)
{
  int16_t *ra = (int16_t *)a;
  int16_t *rb = (int16_t *)b;

  if (ra[1] != rb[1]) {
    return 0;
  }
  if (ra[3] != rb[3]) {
    return 0;
  }
  if (ra[0] != rb[0]) {
    return 0;
  }
  if (ra[2] != rb[2]) {
    return 0;
  }
  return 1;
}
""",
    "int FUN_00108d40(int *a, int *b);",
)

L(
    0x108D00,
    "math/rectangles.c",
    "FUN_00108d00",
    """
/* FUN_00108d00 (0x108d00) — readable C lift (rect a inside rect b). */
int FUN_00108d00(int *outer, int *inner)
{
  int16_t *o = (int16_t *)outer;
  int16_t *i = (int16_t *)inner;

  if (i[1] < o[1]) {
    return 0;
  }
  if (i[3] > o[3]) {
    return 0;
  }
  if (i[0] < o[0]) {
    return 0;
  }
  if (i[2] > o[2]) {
    return 0;
  }
  return 1;
}
""",
    "int FUN_00108d00(int *outer, int *inner);",
)

L(
    0x1A8890,
    "units/units.c",
    "FUN_001a8890",
    """
/* FUN_001a8890 (0x1a8890) — readable C lift. */
char FUN_001a8890(void *anim_state)
{
  unsigned char flag = *((unsigned char *)anim_state + 0xc);
  unsigned char state = *((unsigned char *)anim_state + 0xb);
  char result = (flag == 0);

  if (state >= 0x17 && state <= 0x23) {
    result = 0;
  } else if (state == 0x29) {
    result = 0;
  }
  return result;
}
""",
    "char FUN_001a8890(void *anim_state@<ecx>);",
)


NAKED_BLOCK_RE = re.compile(
    r"/\*[^*]*(?:XBE naked draft|naked draft \(batch)[\s\S]*?#endif\s*\n",
    re.M,
)


def find_naked_block(text: str, name: str, addr: int):
    addr_hex = f"0x{addr:x}"
    for m in NAKED_BLOCK_RE.finditer(text):
        block = m.group(0)
        if addr_hex not in block and f"FUN_{addr:08x}" not in block and name not in block:
            continue
        if "naked" not in block and "__asm__" not in block:
            continue
        return m.start(), m.end()
    pat = re.compile(
        rf"(?:/\*[^*]*{re.escape(addr_hex)}[^*]*\*/\s*)?"
        rf"#if defined\(__clang__\)[\s\S]*?"
        rf"__attribute__\(\(naked[^\)]*\)\)[\s\S]*?"
        rf"\b{re.escape(name)}\s*\([\s\S]*?#endif\s*\n",
        re.M,
    )
    m = pat.search(text)
    if m:
        return m.start(), m.end()
    return None


def ensure_include(text: str, header: str) -> str:
    if header in text:
        return text
    m = re.search(r"(#include[^\n]+\n(?:#include[^\n]+\n)*)", text)
    if m:
        return text[: m.end()] + f'#include "{header}"\n' + text[m.end() :]
    return f'#include "{header}"\n' + text


def apply_lifts(addrs=None):
    selected = addrs if addrs else sorted(LIFTS.keys())
    by_source: dict[str, list[int]] = {}
    for a in selected:
        if a not in LIFTS:
            print(f"skip unknown {hex(a)}", file=sys.stderr)
            continue
        by_source.setdefault(LIFTS[a][0], []).append(a)

    results = []
    for src, alist in by_source.items():
        path = ROOT / "src" / "halo" / src
        text = path.read_text(encoding="utf-8", errors="replace")
        if src == "game/cheats.c":
            text = ensure_include(text, "x87_math.h")
        for a in sorted(alist, reverse=True):
            _source, name, body, decl = LIFTS[a]
            span = find_naked_block(text, name, a)
            if span is None:
                print(f"FAIL locate {hex(a)} {name} in {src}", file=sys.stderr)
                results.append({"addr": hex(a), "ok": False})
                continue
            start, end = span
            text = text[:start] + body + "\n" + text[end:]
            print(f"lifted {hex(a)} {name}")
            results.append({"addr": hex(a), "name": name, "ok": True, "decl": decl})
        path.write_text(text, encoding="utf-8")

    decl_map = {a: LIFTS[a][3] for a in selected if a in LIFTS and LIFTS[a][3]}
    if decl_map:
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        for obj in kb.get("objects", []):
            for fn in obj.get("functions") or []:
                if not isinstance(fn, dict) or not fn.get("addr"):
                    continue
                ai = int(fn["addr"], 16)
                if ai in decl_map:
                    fn["decl"] = decl_map[ai]
        KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        print(f"updated {len(decl_map)} kb decls")
    return results


def main() -> int:
    results = apply_lifts()
    ok = sum(1 for r in results if r.get("ok"))
    print(f"done: {ok}/{len(results)}")
    return 0 if ok == len(results) else 1


if __name__ == "__main__":
    raise SystemExit(main())
