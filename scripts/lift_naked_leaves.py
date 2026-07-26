#!/usr/bin/env python3
"""Replace known tiny naked Capstone drafts with readable C and fix kb decls."""
from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
KB_PATH = ROOT / "kb.json"

# addr_int -> (source relative to src/halo, name, new_c_body, optional new_decl)
# new_c_body is the full replacement from the XBE naked comment through #endif
LIFTS: dict[int, tuple[str, str, str, str | None]] = {}


def L(addr: int, source: str, name: str, body: str, decl: str | None = None):
    LIFTS[addr] = (source, name, body.strip() + "\n", decl)


# --- math/geometry ---
L(
    0x994D0,
    "math/geometry.c",
    "plane_negate",
    """
/* plane_negate (0x994d0) — readable C lift from XBE leaf. */
void plane_negate(float *plane_in, float *plane_out)
{
  plane_out[0] = -plane_in[0];
  plane_out[1] = -plane_in[1];
  plane_out[2] = -plane_in[2];
  plane_out[3] = -plane_in[3];
}
""",
)

# --- math/rectangles ---
L(
    0x1089A0,
    "math/rectangles.c",
    "FUN_001089a0",
    """
/* FUN_001089a0 (0x1089a0) — readable C lift from XBE leaf.
 * Sets rectangle2d as (x0,y0,x1,y1) from (y0,x0,y1,x1) args. */
void FUN_001089a0(int16_t *bounds, int y0, int x0, int y1, int x1)
{
  bounds[1] = (int16_t)y0;
  bounds[0] = (int16_t)x0;
  bounds[3] = (int16_t)y1;
  bounds[2] = (int16_t)x1;
}
""",
    "void FUN_001089a0(int16_t *bounds, int y0, int x0, int y1, int x1);",
)

L(
    0x1089D0,
    "math/rectangles.c",
    "FUN_001089d0",
    """
/* FUN_001089d0 (0x1089d0) — readable C lift from XBE leaf. */
void FUN_001089d0(int16_t *point, int x, int y)
{
  point[0] = (int16_t)x;
  point[1] = (int16_t)y;
}
""",
    "void FUN_001089d0(int16_t *point, int x, int y);",
)

L(
    0x1089F0,
    "math/rectangles.c",
    "FUN_001089f0",
    """
/* FUN_001089f0 (0x1089f0) — readable C lift from XBE leaf. */
void FUN_001089f0(int16_t *point, int dx, int dy)
{
  point[0] = (int16_t)(point[0] + (int16_t)dx);
  point[1] = (int16_t)(point[1] + (int16_t)dy);
}
""",
    "void FUN_001089f0(int16_t *point, int dx, int dy);",
)

L(
    0x108A10,
    "math/rectangles.c",
    "FUN_00108a10",
    """
/* FUN_00108a10 (0x108a10) — readable C lift from XBE leaf (rect height). */
int FUN_00108a10(int16_t *rect)
{
  return (int)(uint16_t)rect[3] - (int)rect[1];
}
""",
    "int FUN_00108a10(int16_t *rect);",
)

L(
    0x108A30,
    "math/rectangles.c",
    "FUN_00108a30",
    """
/* FUN_00108a30 (0x108a30) — readable C lift from XBE leaf (rect width). */
int FUN_00108a30(int16_t *rect)
{
  return (int)(uint16_t)rect[2] - (int)rect[0];
}
""",
    "int FUN_00108a30(int16_t *rect);",
)

L(
    0x108A50,
    "math/rectangles.c",
    "FUN_00108a50",
    """
/* FUN_00108a50 (0x108a50) — readable C lift from XBE leaf (inset rect). */
void FUN_00108a50(int16_t *rect, int dy, int dx)
{
  rect[1] = (int16_t)(rect[1] + (int16_t)dy);
  rect[3] = (int16_t)(rect[3] - (int16_t)dy);
  rect[0] = (int16_t)(rect[0] + (int16_t)dx);
  rect[2] = (int16_t)(rect[2] - (int16_t)dx);
}
""",
    "void FUN_00108a50(int16_t *rect, int dy, int dx);",
)

L(
    0x108D80,
    "math/rectangles.c",
    "FUN_00108d80",
    """
/* FUN_00108d80 (0x108d80) — readable C lift from XBE leaf (point2d equal). */
int FUN_00108d80(int16_t *a, int16_t *b)
{
  if (a[0] != b[0]) {
    return 0;
  }
  if (a[1] != b[1]) {
    return 0;
  }
  return 1;
}
""",
    "int FUN_00108d80(int16_t *a, int16_t *b);",
)

L(
    0x108CD0,
    "math/rectangles.c",
    "FUN_00108cd0",
    """
/* FUN_00108cd0 (0x108cd0) — readable C lift from XBE leaf (point in rect).
 * Point stored as (y,x); rect as (x0,y0,x1,y1); half-open ranges. */
char FUN_00108cd0(int16_t *rect, int16_t *point)
{
  int16_t py = point[0];
  int16_t px = point[1];

  if (py < rect[1]) {
    return 0;
  }
  if (py >= rect[3]) {
    return 0;
  }
  if (px < rect[0]) {
    return 0;
  }
  if (px >= rect[2]) {
    return 0;
  }
  return 1;
}
""",
    "char FUN_00108cd0(int16_t *rect, int16_t *point);",
)

L(
    0x108E20,
    "math/rectangles.c",
    "FUN_00108e20",
    """
/* FUN_00108e20 (0x108e20) — readable C lift from XBE leaf (next power of two). */
int FUN_00108e20(unsigned int value)
{
  int result = 1;

  if ((int)value > 1) {
    while (result < (int)value) {
      result <<= 1;
    }
  }
  return result;
}
""",
    "int FUN_00108e20(unsigned int value);",
)

# --- ai/actor_perception ---
L(
    0x2FB60,
    "ai/actor_perception.c",
    "arctangent",
    """
/* arctangent (0x2fb60) — readable C lift from XBE leaf (x87 fpatan). */
float arctangent(float y, float x)
{
  return x87_fatan2f(y, x);
}
""",
)

# --- hs/hs_runtime ---
L(
    0xC95C0,
    "hs/hs_runtime.c",
    "FUN_000c95c0",
    """
/* FUN_000c95c0 (0xc95c0) — readable C lift from XBE leaf (!value as bool). */
char FUN_000c95c0(char value)
{
  return value == 0;
}
""",
)

L(
    0xCAE80,
    "hs/hs_runtime.c",
    "FUN_000cae80",
    """
/* FUN_000cae80 (0xcae80) — readable C lift from XBE leaf (int == 0). */
char FUN_000cae80(int value)
{
  return value == 0;
}
""",
)

L(
    0xCAEA0,
    "hs/hs_runtime.c",
    "FUN_000caea0",
    """
/* FUN_000caea0 (0xcaea0) — readable C lift from XBE leaf (int16 == 0). */
char FUN_000caea0(int16_t value)
{
  return value == 0;
}
""",
)

L(
    0xCAF70,
    "hs/hs_runtime.c",
    "FUN_000caf70",
    """
/* FUN_000caf70 (0xcaf70) — readable C lift from XBE leaf (int16 identity). */
int16_t FUN_000caf70(int16_t value)
{
  return value;
}
""",
)

L(
    0xCAF10,
    "hs/hs_runtime.c",
    "FUN_000caf10",
    """
/* FUN_000caf10 (0xcaf10) — readable C lift: int→float bits in EAX. */
int FUN_000caf10(int value)
{
  float f = (float)value;
  int bits;

  __builtin_memcpy(&bits, &f, sizeof(bits));
  return bits;
}
""",
    "int FUN_000caf10(int value);",
)

L(
    0xCAEF0,
    "hs/hs_runtime.c",
    "FUN_000caef0",
    """
/* FUN_000caef0 (0xcaef0) — readable C lift: int16→float bits in EAX. */
int FUN_000caef0(int16_t value)
{
  float f = (float)(int)value;
  int bits;

  __builtin_memcpy(&bits, &f, sizeof(bits));
  return bits;
}
""",
    "int FUN_000caef0(int16_t value);",
)

L(
    0xCAF20,
    "hs/hs_runtime.c",
    "FUN_000caf20",
    """
/* FUN_000caf20 (0xcaf20) — readable C lift: (int16+1)→float bits in EAX. */
int FUN_000caf20(int16_t value)
{
  float f = (float)((int)value + 1);
  int bits;

  __builtin_memcpy(&bits, &f, sizeof(bits));
  return bits;
}
""",
    "int FUN_000caf20(int16_t value);",
)

# --- game/cheats ---
L(
    0xA5810,
    "game/cheats.c",
    "FUN_000a5810",
    """
/* FUN_000a5810 (0xa5810) — readable C lift from XBE leaf. */
void FUN_000a5810(int *out, float value, int field0)
{
  out[1] = *(int *)&value;
  out[0] = field0;
}
""",
    "void FUN_000a5810(int *out, float value, int field0);",
)

# --- ai/ai_debug ---
L(
    0x493B0,
    "ai/ai_debug.c",
    "FUN_000493B0",
    """
/* FUN_000493B0 (0x493b0) — readable C lift from XBE leaf. */
void FUN_000493B0(float *out, float value, int field_4, int field_8)
{
  out[0] = value;
  *(int *)(out + 1) = field_4;
  *(int *)(out + 2) = field_8;
}
""",
)

# --- camera/observer ---
L(
    0x89330,
    "camera/observer.c",
    "FUN_00089330",
    """
/* FUN_00089330 (0x89330) — readable C lift from XBE leaf. */
void FUN_00089330(int *out)
{
  out[1] = 0;
  out[0] = 0;
  out[3] = 0;
  out[4] = 0;
  out[5] = 0;
  out[6] = 0x3f9c61aa; /* ~1.222f */
}
""",
    "void FUN_00089330(int *out);",
)

# --- units/vehicles ---
L(
    0x1B5750,
    "units/vehicles.c",
    "set_real_quaternion",
    """
/* set_real_quaternion (0x1b5750) — readable C lift from XBE leaf. */
void set_real_quaternion(float *quat, float w, int x, int y, int z)
{
  quat[0] = w;
  *(int *)(quat + 1) = x;
  *(int *)(quat + 2) = y;
  *(int *)(quat + 3) = z;
}
""",
)

# --- interface/ui_widget ---
L(
    0xEA1F0,
    "interface/ui_widget.c",
    "FUN_000ea1f0",
    """
/* FUN_000ea1f0 (0xea1f0) — readable C lift from XBE leaf. */
char FUN_000ea1f0(void *widget)
{
  *(int *)((char *)widget + 0x40) = 0;
  *(int16_t *)((char *)widget + 0x44) = 0;
  return 1;
}
""",
)

# --- interface/progress_bar ---
L(
    0xE21E0,
    "interface/progress_bar.c",
    "D3DXMatrixIdentity",
    """
/* D3DXMatrixIdentity (0xe21e0) — readable C lift from XBE leaf. */
void D3DXMatrixIdentity(float *m)
{
  int i;

  for (i = 0; i < 16; i++) {
    m[i] = 0.0f;
  }
  m[0] = 1.0f;
  m[5] = 1.0f;
  m[10] = 1.0f;
  m[15] = 1.0f;
}
""",
    "void D3DXMatrixIdentity(float *m);",
)

# --- game/player_control bit tests ---
L(
    0xB6A90,
    "game/player_control.c",
    "player_control_action_test_reset",
    """
/* player_control_action_test_reset (0xb6a90) — readable C lift. */
void player_control_action_test_reset(void)
{
  *(int *)player_control_globals = 0;
  *((int *)player_control_globals + 1) = 0;
}
""",
)

L(
    0xB6B10,
    "game/player_control.c",
    "player_control_action_test_jump",
    """
/* player_control_action_test_jump (0xb6b10) — readable C lift. */
char player_control_action_test_jump(void)
{
  return (*(unsigned int *)player_control_globals >> 1) & 1;
}
""",
)

L(
    0xB6B20,
    "game/player_control.c",
    "player_control_action_test_primary_trigger",
    """
/* player_control_action_test_primary_trigger (0xb6b20) — readable C lift. */
char player_control_action_test_primary_trigger(void)
{
  return (*(unsigned int *)player_control_globals >> 4) & 1;
}
""",
)

L(
    0xB6B30,
    "game/player_control.c",
    "player_control_action_test_grenade_trigger",
    """
/* player_control_action_test_grenade_trigger (0xb6b30) — readable C lift. */
char player_control_action_test_grenade_trigger(void)
{
  return (*(unsigned int *)player_control_globals >> 5) & 1;
}
""",
)

L(
    0xB6B40,
    "game/player_control.c",
    "player_control_action_test_zoom",
    """
/* player_control_action_test_zoom (0xb6b40) — readable C lift. */
char player_control_action_test_zoom(void)
{
  return (*(unsigned int *)player_control_globals >> 6) & 1;
}
""",
)

L(
    0xB6BB0,
    "game/player_control.c",
    "player_control_action_test_look_relative_up",
    """
/* player_control_action_test_look_relative_up (0xb6bb0) — readable C lift. */
char player_control_action_test_look_relative_up(void)
{
  return (*(unsigned int *)player_control_globals >> 7) & 1;
}
""",
)

L(
    0xB6BC0,
    "game/player_control.c",
    "player_control_action_test_look_relative_down",
    """
/* player_control_action_test_look_relative_down (0xb6bc0) — readable C lift. */
char player_control_action_test_look_relative_down(void)
{
  return (*(unsigned int *)player_control_globals >> 8) & 1;
}
""",
)

L(
    0xB6B90,
    "game/player_control.c",
    "player_control_action_test_look_relative_left",
    """
/* player_control_action_test_look_relative_left (0xb6b90) — readable C lift. */
char player_control_action_test_look_relative_left(void)
{
  return (*(unsigned int *)player_control_globals >> 9) & 1;
}
""",
)

L(
    0xB6BA0,
    "game/player_control.c",
    "player_control_action_test_look_relative_right",
    """
/* player_control_action_test_look_relative_right (0xb6ba0) — readable C lift. */
char player_control_action_test_look_relative_right(void)
{
  return (*(unsigned int *)player_control_globals >> 10) & 1;
}
""",
)

L(
    0xB6AF0,
    "game/player_control.c",
    "player_control_action_test_action",
    """
/* player_control_action_test_action (0xb6af0) — readable C lift. */
char player_control_action_test_action(void)
{
  unsigned int *g = (unsigned int *)player_control_globals;

  g[1] |= 1u;
  g[2] |= 1u;
  return (char)(g[0] & 1u);
}
""",
)

L(
    0xB6AB0,
    "game/player_control.c",
    "player_control_action_test_accept",
    """
/* player_control_action_test_accept (0xb6ab0) — readable C lift. */
char player_control_action_test_accept(void)
{
  unsigned int *g = (unsigned int *)player_control_globals;

  g[1] |= 4u;
  g[2] |= 4u;
  return (char)((g[0] >> 2) & 1u);
}
""",
)

L(
    0xB6AD0,
    "game/player_control.c",
    "player_control_action_test_back",
    """
/* player_control_action_test_back (0xb6ad0) — readable C lift. */
char player_control_action_test_back(void)
{
  unsigned int *g = (unsigned int *)player_control_globals;

  g[1] |= 8u;
  g[2] |= 8u;
  return (char)((g[0] >> 3) & 1u);
}
""",
)

L(
    0xB6B50,
    "game/player_control.c",
    "player_control_action_test_move_relative_all_directions",
    """
/* player_control_action_test_move_relative_all_directions (0xb6b50). */
char player_control_action_test_move_relative_all_directions(void)
{
  unsigned int flags = *(unsigned int *)player_control_globals;

  return (char)((flags & 0x7800u) == 0x7800u);
}
""",
)

L(
    0xB6B70,
    "game/player_control.c",
    "player_control_action_test_look_relative_all_directions",
    """
/* player_control_action_test_look_relative_all_directions (0xb6b70). */
char player_control_action_test_look_relative_all_directions(void)
{
  unsigned int flags = *(unsigned int *)player_control_globals;

  return (char)((flags & 0x780u) == 0x780u);
}
""",
)


NAKED_BLOCK_RE = re.compile(
    r"/\*[^*]*(?:XBE naked draft|naked draft \(batch)[\s\S]*?#endif\s*\n",
    re.M,
)


def find_naked_block(text: str, name: str, addr: int) -> tuple[int, int] | None:
    """Return [start,end) of naked block for name/addr."""
    addr_hex = f"0x{addr:x}"
    # Prefer comment containing addr
    for m in NAKED_BLOCK_RE.finditer(text):
        block = m.group(0)
        if addr_hex not in block and f"FUN_{addr:08x}" not in block and name not in block:
            continue
        if f"{name}(" not in block and f"FUN_{addr:08x}" not in block:
            # still accept if addr in comment and naked attr present
            if "__attribute__" not in block or "naked" not in block:
                continue
        if "naked" not in block and "__asm__" not in block:
            continue
        return m.start(), m.end()
    # Fallback: locate function def with naked attr
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
    # after first #include block
    m = re.search(r'(#include[^\n]+\n(?:#include[^\n]+\n)*)', text)
    if m:
        return text[: m.end()] + f'#include "{header}"\n' + text[m.end() :]
    return f'#include "{header}"\n' + text


def apply_lifts(addrs: list[int] | None) -> list[dict]:
    by_source: dict[str, list[int]] = {}
    selected = addrs if addrs else sorted(LIFTS.keys())
    for a in selected:
        if a not in LIFTS:
            print(f"skip unknown {hex(a)}", file=sys.stderr)
            continue
        src = LIFTS[a][0]
        by_source.setdefault(src, []).append(a)

    results = []
    for src, alist in by_source.items():
        path = ROOT / "src" / "halo" / src
        text = path.read_text(encoding="utf-8", errors="replace")
        if src == "ai/actor_perception.c":
            text = ensure_include(text, "x87_math.h")
        # apply high addr first to keep offsets stable? use iterative search each time
        for a in sorted(alist, reverse=True):
            source, name, body, decl = LIFTS[a]
            span = find_naked_block(text, name, a)
            if span is None:
                print(f"FAIL locate {hex(a)} {name} in {src}", file=sys.stderr)
                results.append({"addr": hex(a), "name": name, "ok": False, "reason": "locate"})
                continue
            start, end = span
            text = text[:start] + body + "\n" + text[end:]
            print(f"lifted {hex(a)} {name} in {src}")
            results.append({"addr": hex(a), "name": name, "ok": True, "decl": decl, "source": src})
        path.write_text(text, encoding="utf-8")

    # update kb decls
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    decl_map = {a: LIFTS[a][3] for a in selected if a in LIFTS and LIFTS[a][3]}
    if decl_map:
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
    ap.add_argument("--addrs", nargs="*", help="hex addrs to lift (default: all in table)")
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
