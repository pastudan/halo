#!/usr/bin/env python3
"""Atomic naked→C + Unicorn prove + commit for Track A pure leaves."""
from __future__ import annotations

import json
import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
from lift_inventory_batch4 import find_naked_block  # noqa: E402

KB_PATH = ROOT / "kb.json"
RESULTS_RE = re.compile(r"(\d+) passed, (\d+) failed, (\d+) errors")

# (addr, source, name, body, decl)
LIFTS: list[tuple[int, str, str, str, str]] = []


def add(addr, source, name, body, decl):
    LIFTS.append((addr, source, name, body.strip() + "\n", decl))


add(
    0x1909D0,
    "shaders/shaders.c",
    "shader_type_is_transparent",
    """
/* shader_type_is_transparent (0x1909d0) — readable C lift. */
char shader_type_is_transparent(short shader_type)
{
  int t = (int)shader_type;
  if (t == 1) return 1;
  if (t <= 4) return 0;
  if (t > 10) return 0;
  return 1;
}
""",
    "char shader_type_is_transparent(short shader_type);",
)
add(
    0x1909F0,
    "shaders/shaders.c",
    "shader_type_is_lightmapped",
    """
/* shader_type_is_lightmapped (0x1909f0) — readable C lift. */
char shader_type_is_lightmapped(short shader_type)
{
  int t = (int)shader_type;
  if (t < 3) return 0;
  if (t <= 4) return 1;
  return t == 8;
}
""",
    "char shader_type_is_lightmapped(short shader_type);",
)
add(
    0x190A30,
    "shaders/shaders.c",
    "shader_type_is_valid_for_environment",
    """
/* shader_type_is_valid_for_environment (0x190a30) — readable C lift. */
char shader_type_is_valid_for_environment(short shader_type)
{
  int t = (int)shader_type;
  if (t == 3) return 1;
  if (t <= 4) return 0;
  if (t > 9) return 0;
  return 1;
}
""",
    "char shader_type_is_valid_for_environment(short shader_type);",
)
add(
    0x190A70,
    "shaders/shaders.c",
    "shader_type_is_valid_for_modifier",
    """
/* shader_type_is_valid_for_modifier (0x190a70) — readable C lift. */
char shader_type_is_valid_for_modifier(short shader_type)
{
  int t = (int)shader_type;
  if (t == 1) return 1;
  if (t <= 4) return 0;
  if (t > 10) return 0;
  return 1;
}
""",
    "char shader_type_is_valid_for_modifier(short shader_type);",
)
add(
    0xBB2B0,
    "game/players.c",
    "valid_real_vector2d",
    """
/* valid_real_vector2d (0xbb2b0) — readable C lift. */
char valid_real_vector2d(float *v)
{
  unsigned int x = *(unsigned int *)v;
  unsigned int y = *(unsigned int *)(v + 1);
  if ((x & 0x7f800000u) == 0x7f800000u) return 0;
  if ((y & 0x7f800000u) == 0x7f800000u) return 0;
  return 1;
}
""",
    "char valid_real_vector2d(float *v);",
)
add(
    0x87AC0,
    "camera/director.c",
    "FUN_00087ac0",
    """
/* FUN_00087ac0 (0x87ac0) — readable C lift. */
char FUN_00087ac0(char enable)
{
  char prev = *(char *)0x335699;
  void *p;
  *(char *)0x335699 = enable;
  if (!enable) {
    p = *(void **)0x3356b0;
    if (p) *(int *)((char *)p + 0x14) = 0;
  }
  return prev;
}
""",
    "char FUN_00087ac0(char enable);",
)
add(
    0x10C390,
    "math/random_math.c",
    "FUN_0010c390",
    """
/* FUN_0010c390 (0x10c390) — readable C lift. */
float FUN_0010c390(float a, float b, unsigned char t)
{
  if (t == 0xff) return b;
  return a + (b - a) * ((float)t * (1.0f / 255.0f));
}
""",
    "float FUN_0010c390(float a, float b, unsigned char t);",
)
add(
    0x124C10,
    "networking/network_client_manager.c",
    "network_game_client_get_machine",
    """
/* network_game_client_get_machine (0x124c10) — readable C lift. */
void *network_game_client_get_machine(void *client)
{
  unsigned short idx;
  if (!client) return 0;
  idx = *(unsigned short *)client;
  if (idx >= 4) return 0;
  return (char *)client + 0x970 + (int)idx * 0x44;
}
""",
    "void *network_game_client_get_machine(void *client);",
)
add(
    0x101EC0,
    "main/main.c",
    "main_save_map_no_timeout",
    """
/* main_save_map_no_timeout (0x101ec0) — readable C lift. */
void main_save_map_no_timeout(void)
{
  if (*(char *)0x46da28 == 0 || *(char *)0x46da2a != 0) {
    *(char *)0x46da28 = 1;
    *(char *)0x46da29 = 1;
    *(int *)0x46da2c = 0;
    *(int *)0x46da30 = 0;
    *(short *)0x46da38 = 0;
  }
  *(char *)0x46da2a = 0;
}
""",
    "void main_save_map_no_timeout(void);",
)
add(
    0xFBA00,
    "items/weapons.c",
    "FUN_000fba00",
    """
/* FUN_000fba00 (0xfba00) — readable C lift. */
char FUN_000fba00(short value, short threshold)
{
  int t = (int)threshold;
  if (t == 0) return 1;
  if (t <= 0 || t > 2) return 0;
  return value >= threshold;
}
""",
    "char FUN_000fba00(short value, short threshold@<edx>);",
)
add(
    0xE0810,
    "interface/player_ui.c",
    "player_ui_get_single_player_local_player_from_controller",
    """
/* player_ui_get_single_player_local_player_from_controller (0xe0810) — readable C lift. */
short player_ui_get_single_player_local_player_from_controller(short controller)
{
  short i;
  for (i = 0; i < 4; i++) {
    if (*(short *)(0x46bfc4 + (int)i * 2) == controller) return i;
  }
  return (short)-1;
}
""",
    "short player_ui_get_single_player_local_player_from_controller(short controller);",
)
add(
    0x90170,
    "cseries/profile.c",
    "FUN_00090170",
    """
/* FUN_00090170 (0x90170) — readable C lift. */
void FUN_00090170(int *out, int a, int b)
{
  out[0] = a;
  out[1] = b;
}
""",
    "void FUN_00090170(int *out@<eax>, int a, int b);",
)
add(
    0x8F8C0,
    "cseries/profile.c",
    "profile_lapsed_msec",
    """
/* profile_lapsed_msec (0x8f8c0) — readable C lift. */
void profile_lapsed_msec(int value)
{
  *(int *)0x449cd0 = value;
  *(char *)0x449cd4 = value > 0;
}
""",
    "void profile_lapsed_msec(int value);",
)
add(
    0xE2170,
    "interface/progress_bar.c",
    "FUN_000e2170",
    """
/* FUN_000e2170 (0xe2170) — readable C lift. */
void FUN_000e2170(char v)
{
  *(char *)0x30f030 = v;
}
""",
    "void FUN_000e2170(char v);",
)
add(
    0xE4590,
    "interface/ui_widget.c",
    "display_error_abort_to_dashboard_deferred",
    """
/* display_error_abort_to_dashboard_deferred (0xe4590) — readable C lift. */
void display_error_abort_to_dashboard_deferred(short error_handle, char flag)
{
  if (*(short *)0x46cc68 != (short)-1) {
    return;
  }
  *(short *)0x46cc68 = error_handle;
  *(char *)0x46cc6a = flag;
}
""",
    "void display_error_abort_to_dashboard_deferred(short error_handle, char flag);",
)
add(
    0x824A0,
    "bungie_net/network/transport_endpoint_set_winsock.c",
    "FUN_000824a0",
    """
/* FUN_000824a0 (0x824a0) — readable C lift. */
int FUN_000824a0(int *a, int *b)
{
  int av = *a;
  int bv = *b;
  if (av == 0) {
    if (bv == 0) return 0;
    return 1;
  }
  if (bv == 0) return -1;
  return 0;
}
""",
    "int FUN_000824a0(int *a, int *b);",
)
add(
    0x6F890,
    "bitmaps/libtiff/tif_write.c",
    "FUN_0006f890",
    """
/* FUN_0006f890 (0x6f890) — readable C lift. */
unsigned int FUN_0006f890(void *tif)
{
  unsigned int a;
  unsigned int d;
  unsigned char *p = (unsigned char *)tif;
  a = *(unsigned int *)(p + 0x2c);
  if (!a) return 0;
  d = *(unsigned int *)(p + 0x28);
  if (!d) return 0;
  a = (unsigned int)*(unsigned short *)(p + 0x36) * d;
  if (*(unsigned short *)(p + 0x5e) == 1) {
    a *= (unsigned int)*(unsigned short *)(p + 0x44);
  }
  return (a + 7) >> 3;
}
""",
    "unsigned int FUN_0006f890(void *tif);",
)
add(
    0x190A10,
    "shaders/shaders.c",
    "shader_type_is_vertex_lit",
    """
/* shader_type_is_vertex_lit (0x190a10) — readable C lift. */
char shader_type_is_vertex_lit(short shader_type)
{
  int t = (int)shader_type;
  return t == 4 || t == 8;
}
""",
    "char shader_type_is_vertex_lit(short shader_type);",
)
add(
    0x190A50,
    "shaders/shaders.c",
    "shader_type_is_valid_for_model",
    """
/* shader_type_is_valid_for_model (0x190a50) — readable C lift. */
char shader_type_is_valid_for_model(short shader_type)
{
  int t = (int)shader_type;
  return t >= 3 && t <= 10;
}
""",
    "char shader_type_is_valid_for_model(short shader_type);",
)
add(
    0x190BE0,
    "shaders/shaders.c",
    "numeric_countdown_timer_set",
    """
/* numeric_countdown_timer_set (0x190be0) — readable C lift. */
void numeric_countdown_timer_set(int value, char flag)
{
  *(int *)0x4d8a78 = value;
  *(char *)0x4d8a7c = flag;
}
""",
    "void numeric_countdown_timer_set(int value, char flag);",
)
add(
    0x19B8F0,
    "text/draw_string.c",
    "draw_string_set_highlight",
    """
/* draw_string_set_highlight (0x19b8f0) — readable C lift. */
void draw_string_set_highlight(short a, short b)
{
  *(short *)0x4d9b4a = a;
  *(short *)0x4d9b4c = b;
}
""",
    "void draw_string_set_highlight(short a, short b);",
)
add(
    0x19D060,
    "text/international_strings.c",
    "set_language_code",
    """
/* set_language_code (0x19d060) — readable C lift. */
void set_language_code(short code)
{
  short v = code;
  if (v < 0 || v >= 6) v = 0;
  *(short *)0x4d9be0 = v;
}
""",
    "void set_language_code(short code);",
)
add(
    0x1C29A0,
    "saved games/saved_game_files.c",
    "saved_game_file_get_type",
    """
/* saved_game_file_get_type (0x1c29a0) — readable C lift. */
int saved_game_file_get_type(int handle)
{
  return handle & 0xf;
}
""",
    "int saved_game_file_get_type(int handle);",
)
add(
    0xE3D70,
    "interface/ui_widget.c",
    "ui_widgets_active",
    """
/* ui_widgets_active (0xe3d70) — readable C lift. */
char ui_widgets_active(void)
{
  unsigned int *p;
  if (!*(char *)0x46cc82) return 0;
  for (p = (unsigned int *)0x46cc20; p < (unsigned int *)0x46cc30; p++) {
    if (*p != 0) return 1;
  }
  return 0;
}
""",
    "char ui_widgets_active(void);",
)
add(
    0xE0930,
    "interface/player_ui.c",
    "player_ui_autojoin_players_to_next_multiplayer_game",
    """
/* player_ui_autojoin_players_to_next_multiplayer_game (0xe0930) — readable C lift. */
void player_ui_autojoin_players_to_next_multiplayer_game(void)
{
  *(char *)0x46bf14 = *(char *)0x46bfc0;
  *(char *)0x46bf4c = *(char *)0x46bfc1;
  *(char *)0x46bf84 = *(char *)0x46bfc2;
  *(char *)0x46bfbc = *(char *)0x46bfc3;
}
""",
    "void player_ui_autojoin_players_to_next_multiplayer_game(void);",
)
add(
    0xE09E0,
    "interface/player_ui.c",
    "player_ui_get_active_player_profile_index",
    """
/* player_ui_get_active_player_profile_index (0xe09e0) — readable C lift. */
int player_ui_get_active_player_profile_index(short local_player_index)
{
  if (local_player_index < 0 || local_player_index >= 4) return 0;
  return *(int *)(0x46bf10 + (int)local_player_index * 0x38);
}
""",
    "int player_ui_get_active_player_profile_index(short local_player_index);",
)
add(
    0x1CBA00,
    "sound/sound_manager.c",
    "FUN_001cba00",
    """
/* FUN_001cba00 (0x1cba00) — readable C lift: scale * lerp(a,b,t). */
float FUN_001cba00(float scale, float a, float b, float t)
{
  return scale * (a + (b - a) * t);
}
""",
    "float FUN_001cba00(float scale, float a, float b, float t);",
)
add(
    0x1CB9B0,
    "sound/sound_manager.c",
    "sound_manager_set_sound_environment",
    """
/* sound_manager_set_sound_environment (0x1cb9b0) — readable C lift. */
void sound_manager_set_sound_environment(void *environment)
{
  unsigned int *dst = (unsigned int *)0x4eb068;
  unsigned int *src = (unsigned int *)environment;
  int i;
  for (i = 0; i < 0x12; i++) dst[i] = src[i];
}
""",
    "void sound_manager_set_sound_environment(void *environment);",
)
add(
    0x139300,
    "objects/object_lights.c",
    "lights_enable",
    """
/* lights_enable (0x139300) — readable C lift. */
char lights_enable(char active)
{
  char *p = *(char **)0x46f074;
  *p = active;
  return active;
}
""",
    "char lights_enable(char active);",
)


def apply_all() -> list[tuple[int, str]]:
    applied = []
    by_src: dict[str, list] = {}
    for item in LIFTS:
        by_src.setdefault(item[1], []).append(item)
    for src, items in by_src.items():
        path = ROOT / "src" / "halo" / src
        text = path.read_text(encoding="utf-8", errors="replace")
        changed = False
        for addr, _s, name, body, _d in sorted(items, key=lambda x: -x[0]):
            span = find_naked_block(text, name, addr)
            if span is None:
                if "readable C lift" in text and f"0x{addr:x}" in text.lower():
                    applied.append((addr, name))
                    print(f"already-C {hex(addr)} {name}")
                else:
                    print(f"FAIL locate {hex(addr)} {name}")
                continue
            text = text[: span[0]] + body + "\n" + text[span[1] :]
            changed = True
            applied.append((addr, name))
            print(f"lifted {hex(addr)} {name}")
        if changed:
            path.write_text(text, encoding="utf-8")
    # decls
    decl = {a: d for a, _s, _n, _b, d in LIFTS}
    kb = json.loads(KB_PATH.read_text())
    for obj in kb.get("objects", []):
        for fn in obj.get("functions") or []:
            if not fn.get("addr"):
                continue
            ai = int(fn["addr"], 16)
            if ai in decl:
                fn["decl"] = decl[ai]
    KB_PATH.write_text(json.dumps(kb, indent=2) + "\n")
    return applied


def ensure_oracle(addr: int) -> None:
    oracle = ROOT / "delinked" / "functions" / f"{addr:08x}.obj"
    if oracle.exists() and oracle.stat().st_size > 0:
        return
    oracle.parent.mkdir(parents=True, exist_ok=True)
    subprocess.run(
        [
            sys.executable,
            str(ROOT / "tools/equivalence/xbe_to_coff.py"),
            "--addr",
            hex(addr),
            "--out",
            str(oracle),
        ],
        cwd=ROOT,
        capture_output=True,
    )


def prove(name: str, addr: int, seeds: int = 100) -> bool:
    ensure_oracle(addr)
    proc = subprocess.run(
        [
            sys.executable,
            str(ROOT / "tools/equivalence/unicorn_diff.py"),
            name,
            "--allow-stubs",
            "--seeds",
            str(seeds),
            "-q",
        ],
        cwd=ROOT,
        capture_output=True,
        text=True,
        timeout=50,
    )
    text = (proc.stdout or "") + (proc.stderr or "")
    m = RESULTS_RE.search(text)
    if not m:
        print(f"  no-parse {name}: {text[-160:].replace(chr(10), ' ')}")
        return False
    p, f, e = map(int, m.groups())
    ok = proc.returncode == 0 and f == 0 and e == 0 and p >= int(0.9 * seeds)
    print(f"  unicorn {name}: {p}/{f}/{e} ok={ok}")
    return ok


def raw_cast_ok() -> bool:
    r = subprocess.run(
        [sys.executable, str(ROOT / "tools/audit/check_raw_casts.py")],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    print(r.stdout or r.stderr)
    return r.returncode == 0


def main() -> int:
    t0 = time.time()
    applied = apply_all()
    if not raw_cast_ok():
        return 1

    kb = json.loads(KB_PATH.read_text())
    by = {}
    for obj in kb.get("objects", []):
        for fn in obj.get("functions") or []:
            if fn.get("addr"):
                by[int(fn["addr"], 16)] = fn

    true0 = sum(1 for fn in by.values() if fn.get("ported") is True)
    flips = []
    for addr, name in applied:
        fn = by.get(addr)
        if not fn or fn.get("ported") is not False:
            continue
        if prove(name, addr):
            fn["ported"] = True
            flips.append((addr, name))

    KB_PATH.write_text(json.dumps(kb, indent=2) + "\n")
    if not raw_cast_ok():
        return 1

    # stage + commit + push immediately
    subprocess.run(
        ["git", "add", "-A", "src/halo", "kb.json", "scripts/grind_batch5_atomic.py", "tools/equivalence/leaf_cache.json"],
        cwd=ROOT,
        check=False,
    )
    msg = f"lift(track-a): Unicorn-prove {len(flips)} batch5 pure leaves (ported:true)."
    r = subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True)
    print(r.stdout, r.stderr)
    sha = subprocess.check_output(["git", "rev-parse", "HEAD"], cwd=ROOT, text=True).strip()
    pr = subprocess.run(["git", "push", "pastudan", "HEAD"], cwd=ROOT, capture_output=True, text=True)
    print(pr.stdout, pr.stderr)

    true1 = sum(
        1
        for o in json.loads(KB_PATH.read_text()).get("objects", [])
        for fn in o.get("functions") or []
        if fn.get("ported") is True
    )
    print(
        f"DONE flips={len(flips)} true {true0}->{true1} sha={sha} dt={time.time()-t0:.1f}s"
    )
    print("flips", [hex(a) for a, _ in flips])
    Path("/tmp/batch5_summary.json").write_text(
        json.dumps(
            {
                "flips": [hex(a) for a, _ in flips],
                "true0": true0,
                "true1": true1,
                "sha": sha,
            },
            indent=2,
        )
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
