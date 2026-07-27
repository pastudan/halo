#!/usr/bin/env python3
"""Hand-lift Track A G1 naked leaves → readable C (apply only; prove separately)."""
from __future__ import annotations

import argparse
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
    0xF6820,
    "items/items.c",
    "item_new",
    """
/* item_new (0xf6820) — readable C lift. */
char item_new(int object_handle)
{
  unsigned char *obj;
  int16_t remain;
  char ok;

  obj = (unsigned char *)object_get_and_verify_type(object_handle, 0x10);
  remain = (int16_t)(*(int16_t *)(obj + 0x1dc) - 1);
  *(int16_t *)(obj + 0x1dc) = remain;
  ok = remain > 0;
  if (!ok)
    object_delete(object_handle);
  return ok;
}
""",
)

L(
    0xF6860,
    "items/items.c",
    "item_begin_garbage_collection",
    """
/* item_begin_garbage_collection (0xf6860) — readable C lift. */
bool item_begin_garbage_collection(int item_handle)
{
  int *obj;
  int16_t ttl;

  obj = (int *)object_get_and_verify_type(item_handle, 0x10);
  object_set_garbage_flag(item_handle, 1);
  obj[1] = obj[1] | 0xc0000;
  ttl = random_range((unsigned int *)get_global_random_seed_address(), 0x12c, 0x258);
  *(int16_t *)((char *)obj + 0x1dc) = ttl;
  return true;
}
""",
)

L(
    0xF6D00,
    "items/items.c",
    "valid_real_matrix4x3",
    """
/* valid_real_matrix4x3 (0xf6d00) — readable C lift. */
char valid_real_matrix4x3(float *mat)
{
  unsigned int bits;

  bits = *(unsigned int *)mat;
  if ((bits & 0x7f800000) == 0x7f800000)
    return 0;
  if (!valid_real_vector3d_axes3(mat + 1, mat + 4, mat + 7))
    return 0;
  if (!valid_real_point3d(mat + 10))
    return 0;
  return 1;
}
""",
)

L(
    0xF6750,
    "items/items.c",
    "FUN_000f6750",
    """
/* FUN_000f6750 (0xf6750) — readable C lift. */
void FUN_000f6750(int object_datum, void *definition)
{
  int *obj;
  unsigned char *def;
  int flags;

  obj = (int *)object_get_and_verify_type(object_datum, 8);
  def = (unsigned char *)definition;
  flags = obj[1];
  if (def[0x22] & 1)
    flags |= 0x20;
  else
    flags &= ~0x20;
  flags |= 0x60000;
  obj[1] = flags;
  if (!(def[0x22] & 4))
    obj[0x1a4 / 4] = obj[0x1a4 / 4] | 0x20;
  else
    obj[0x1a4 / 4] = obj[0x1a4 / 4] & ~0x20;
  if (!(def[0x22] & 1))
    ((float *)obj)[0x14 / 4] = ((float *)obj)[0x14 / 4] + *(float *)0x2533e8;
}
""",
)

L(
    0xFAE30,
    "items/weapons.c",
    "weapon_preprocess_node_orientations",
    """
/* weapon_preprocess_node_orientations (0xfae30) — readable C lift. */
void weapon_preprocess_node_orientations(int weapon_handle)
{
  int *obj;
  unsigned char *weap;
  unsigned char *antr;
  int count;

  obj = (int *)object_get_and_verify_type(weapon_handle, 4);
  weap = (unsigned char *)tag_get(0x77656170, *obj);
  antr = (unsigned char *)tag_get(0x616e7472, *(int *)(weap + 0x44));
  count = *(int *)(antr + 0x18);
  if (count != 0)
    tag_block_get_element(antr + 0x18, 0, 0x1c);
}
""",
)

L(
    0x1B13A0,
    "units/units.c",
    "unit_has_night_vision_weapon",
    """
/* unit_has_night_vision_weapon (0x1b13a0) — readable C lift. */
char unit_has_night_vision_weapon(int unit_handle)
{
  unsigned char *unit;
  int weapon_handle;
  int *weapon;
  unsigned int *tag;
  int16_t weapon_index;

  unit = (unsigned char *)object_get_and_verify_type(unit_handle, 3);
  if (unit[0x2d0] == 0xff)
    return 0;
  unit = (unsigned char *)object_get_and_verify_type(unit_handle, 3);
  weapon_index = *(int16_t *)(unit + 0x2a2);
  weapon_handle = unit_get_weapon(unit_handle, weapon_index);
  if (weapon_handle == -1)
    return 0;
  weapon = (int *)object_get_and_verify_type(weapon_handle, 4);
  tag = (unsigned int *)tag_get(0x77656170, *weapon);
  return (char)((tag[0x308 / 4] >> 14) & 1);
}
""",
    "char unit_has_night_vision_weapon(int unit_handle@<esi>);",
)

L(
    0x1B2740,
    "units/units.c",
    "unit_select_weapon_after_vehicle_exit",
    """
/* unit_select_weapon_after_vehicle_exit (0x1b2740) — readable C lift. */
void unit_select_weapon_after_vehicle_exit(int unit_handle)
{
  unsigned char *unit;
  int16_t current;
  int16_t next;

  unit = (unsigned char *)object_get_and_verify_type(unit_handle, 3);
  current = *(int16_t *)(unit + 0x2a2);
  next = FUN_001ae490(unit_handle, current, 0);
  *(int16_t *)(unit + 0x2a4) = next;
  unit_update_weapon_readiness(unit_handle, 1);
}
""",
    "void unit_select_weapon_after_vehicle_exit(int unit_handle@<eax>);",
)

L(
    0x13EC00,
    "objects/objects.c",
    "object_markers_need_update",
    """
/* object_markers_need_update (0x13ec00) — readable C lift. */
int object_markers_need_update(int object_handle)
{
  int *obj;
  unsigned char *globals;

  obj = (int *)object_get_and_verify_type(object_handle, -1);
  globals = *(unsigned char **)0x46f084;
  if (!globals[1]) {
    extern char DAT_0029b91c[];
    extern char DAT_0029bc30[];
    display_assert(DAT_0029bc30, DAT_0029b91c, 0xdc6, 1);
    system_exit(-1);
  }
  return obj[2] != *(int *)0x5a8d28;
}
""",
)

L(
    0x139930,
    "objects/objects.c",
    "FUN_00139930",
    """
/* FUN_00139930 (0x139930) — readable C lift. */
int FUN_00139930(int param_1)
{
  int *datum;

  datum = (int *)datum_get(*(void **)0x5a90bc, param_1);
  if (!*(unsigned char *)0x5a8d60) {
    extern char DAT_0029b324[];
    extern char DAT_0029b4ac[];
    display_assert(DAT_0029b4ac, DAT_0029b324, 0x66f, 1);
    system_exit(-1);
  }
  return datum[3] != *(int *)0x5a8d64;
}
""",
)

L(
    0x144AE0,
    "objects/objects.c",
    "objects_scripting_attach",
    """
/* objects_scripting_attach (0x144ae0) — readable C lift. */
void objects_scripting_attach(int param_1, int param_2, int param_3, int param_4)
{
  int *child;

  if (param_1 == -1)
    return;
  if (param_3 == -1)
    return;
  child = (int *)object_get_and_verify_type(param_3, -1);
  if (child[0xcc / 4] != -1)
    return;
  object_attach_to_marker(param_1, (void *)param_2, param_3, (void *)param_4);
}
""",
)

L(
    0xCE3C0,
    "hs/hs_runtime.c",
    "FUN_000ce3c0",
    """
/* FUN_000ce3c0 (0xce3c0) — readable C lift. */
void FUN_000ce3c0(void)
{
  int index;
  short *datum;

  for (index = data_next_index(*(data_t **)0x5aa698, -1); index != -1;
       index = data_next_index(*(data_t **)0x5aa698, index)) {
    datum = (short *)datum_get(*(void **)0x5aa698, index);
    if (datum[2] == 0)
      object_list_delete(index);
  }
}
""",
)

L(
    0x27A10,
    "ai/actor_looking.c",
    "FUN_00027a10",
    """
/* FUN_00027a10 (0x27a10) — readable C lift. */
int FUN_00027a10(int actor_handle)
{
  unsigned char *actor;
  unsigned char *tag;
  int kind;

  actor = (unsigned char *)datum_get(*(void **)0x6325a4, actor_handle);
  tag = (unsigned char *)tag_get(0x61637472, *(int *)(actor + 0x58));
  kind = *(int16_t *)(actor + 0x3fc);
  if (kind == 2)
    return (int)(tag + 0xf4);
  if (kind > 2 && kind <= 4)
    return (int)(tag + 0x10c);
  return (int)(tag + 0xdc);
}
""",
    "int FUN_00027a10(int actor_handle /* @<eax> */);",
)

L(
    0x15EB0,
    "ai/actor_looking.c",
    "actor_reset_action_state",
    """
/* actor_reset_action_state (0x15eb0) — readable C lift. */
void actor_reset_action_state(int actor_handle)
{
  unsigned char *actor;
  int16_t state;

  actor = (unsigned char *)datum_get(*(void **)0x6325a4, actor_handle);
  if (actor[0xa4] != 0 && *(int16_t *)(actor + 0xc0) == 3) {
    actor[0xa4] = 0;
    *(int16_t *)(actor + 0xa8) = 0;
    actor[0xa6] = 0;
  }
  state = *(int16_t *)(actor + 0xc0);
  if (state == 3 || (state == 1 && actor[0x160] == 0)) {
    *(int16_t *)(actor + 0xc0) = 0;
    *(int16_t *)(actor + 0xc4) = (int16_t)0xffff;
    actor[0xaa] = 1;
  }
}
""",
)

L(
    0x32BB0,
    "ai/actor_perception.c",
    "actor_perception_tried_to_search",
    """
/* actor_perception_tried_to_search (0x32bb0) — readable C lift. */
void actor_perception_tried_to_search(int actor_handle, int prop_handle)
{
  unsigned char *actor;
  unsigned char *prop;

  if (prop_handle == -1)
    return;
  actor = (unsigned char *)datum_get(*(void **)0x6325a4, actor_handle);
  prop = (unsigned char *)datum_get(*(void **)0x5ab23c, prop_handle);
  prop[0xba] = 1;
  if (*(int *)(actor + 0x270) == prop_handle) {
    actor_situation_update_target_status(actor_handle);
    actor_situation_combat_status_update(actor_handle);
  }
}
""",
)

L(
    0x32B50,
    "ai/actor_perception.c",
    "actor_perception_tried_to_uncover",
    """
/* actor_perception_tried_to_uncover (0x32b50) — readable C lift. */
void actor_perception_tried_to_uncover(int actor_handle, int prop_handle)
{
  unsigned char *actor;
  unsigned char *prop;

  if (prop_handle == -1)
    return;
  actor = (unsigned char *)datum_get(*(void **)0x6325a4, actor_handle);
  prop = (unsigned char *)datum_get(*(void **)0x5ab23c, prop_handle);
  prop[0xb9] = 1;
  if (*(int *)(actor + 0x270) == prop_handle) {
    actor_situation_update_target_status(actor_handle);
    actor_situation_combat_status_update(actor_handle);
  }
}
""",
)

L(
    0x48FA0,
    "ai/ai_debug.c",
    "ai_debug_dispose_from_old_map",
    """
/* ai_debug_dispose_from_old_map (0x48fa0) — readable C lift. */
void ai_debug_dispose_from_old_map(void)
{
  unsigned char *scenario;
  void *elem;
  int index;

  scenario = (unsigned char *)FUN_0018e3b0();
  index = *(int *)0x5ac9f4;
  if (scenario == 0 || index == -1) {
    csstrcpy((char *)0x5ac9d2, (const char *)0x25386f);
    return;
  }
  elem = tag_block_get_element(scenario + 0x42c, index & 0xffff, 0xb0);
  csstrncpy((char *)0x5ac9d2, (const char *)elem, 0x20);
  *(unsigned char *)0x5ac9f1 = 0;
}
""",
)

L(
    0x4A710,
    "ai/ai_debug.c",
    "ai_debug_idle_look_addprop",
    """
/* ai_debug_idle_look_addprop (0x4a710) — readable C lift. */
void ai_debug_idle_look_addprop(int index, float value)
{
  int16_t count;

  if (!*(unsigned char *)0x6323d4) {
    extern char DAT_0025ab74[];
    extern char DAT_0025aeac[];
    display_assert(DAT_0025aeac, DAT_0025ab74, 0x13b1, 1);
    system_exit(-1);
  }
  count = *(int16_t *)0x6323dc;
  if (count >= 0x20)
    return;
  ((int *)0x6323e0)[count] = index;
  ((float *)0x632460)[*(int16_t *)0x6323dc] = value;
  *(int16_t *)0x6323dc = (int16_t)(*(int16_t *)0x6323dc + 1);
}
""",
)

L(
    0x4A220,
    "ai/ai_debug.c",
    "ai_debug_speak",
    """
/* ai_debug_speak (0x4a220) — readable C lift. */
void ai_debug_speak(int a0)
{
  unsigned char *actor;
  int handle;
  short speech;

  handle = *(int *)0x5ac9f8;
  if (handle == -1)
    return;
  actor = (unsigned char *)datum_get(*(void **)0x6325a4, handle);
  speech = FUN_001a67e0((const char *)a0);
  if (*(int *)(actor + 0x18) == -1)
    return;
  if (speech == (short)0xffff)
    return;
  *(unsigned char *)0x5aca89 = 1;
  *(unsigned char *)0x6324e0 = 1;
  *(int16_t *)0x6324e8 = 0;
  *(unsigned char *)0x6324e1 = 0;
  *(int *)0x6324e4 = *(int *)(actor + 0x18);
  *(int16_t *)0x6324ea = speech;
}
""",
)


def find_naked_block(text: str, name: str, addr: int):
    addr_hex = f"0x{addr:x}"
    # Prefer exact " (0xADDR) — XBE naked draft " marker through first #endif
    marker = f"({addr_hex}) — XBE naked draft"
    idx = text.find(marker)
    if idx < 0:
        marker = f"({addr_hex}) - XBE naked draft"
        idx = text.find(marker)
    if idx >= 0:
        # walk back to comment start
        start = text.rfind("/*", 0, idx)
        if start < 0 or idx - start > 200:
            start = idx
        end = text.find("#endif", idx)
        if end < 0:
            return None
        end = end + len("#endif")
        # include trailing newline
        if end < len(text) and text[end] == "\n":
            end += 1
        block = text[start:end]
        if len(block) > 2500:
            print(f"ABORT oversized block {addr_hex} {name}: {len(block)} bytes", file=sys.stderr)
            return None
        if "naked" not in block:
            print(f"ABORT no naked in block {addr_hex} {name}", file=sys.stderr)
            return None
        return start, end
    return None


def apply_lifts(addrs: list[int] | None) -> list[dict]:
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
        for a in sorted(alist, reverse=True):
            _source, name, body, decl = LIFTS[a]
            span = find_naked_block(text, name, a)
            if span is None:
                print(f"FAIL locate {hex(a)} {name} in {src}", file=sys.stderr)
                results.append({"addr": hex(a), "name": name, "ok": False})
                continue
            start, end = span
            text = text[:start] + body + "\n" + text[end:]
            print(f"lifted {hex(a)} {name} in {src}")
            results.append({"addr": hex(a), "name": name, "ok": True, "decl": decl, "source": src})
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
    ap = argparse.ArgumentParser()
    ap.add_argument("--addrs", nargs="*", help="hex addrs")
    ap.add_argument("--list", action="store_true")
    args = ap.parse_args()
    if args.list:
        for a in sorted(LIFTS):
            print(f"0x{a:x} {LIFTS[a][1]} {LIFTS[a][0]}")
        return 0
    addrs = [int(x, 16) for x in args.addrs] if args.addrs else None
    results = apply_lifts(addrs)
    ok = sum(1 for r in results if r.get("ok"))
    print(f"done: {ok}/{len(results)} lifted")
    return 0 if ok == len(results) else 1


if __name__ == "__main__":
    raise SystemExit(main())
