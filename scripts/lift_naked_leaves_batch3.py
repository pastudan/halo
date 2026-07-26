#!/usr/bin/env python3
"""Batch-3 naked→C lifts (Lifter B: 0x10000–0x80000, 0x140000–0x180000 + ai/hs/effects/physics/structures)."""
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


# --- bitmaps/libtiff getters (0x6d8xx) ---
L(
    0x6D850,
    "bitmaps/libtiff/tif_open.c",
    "TIFFFileName",
    """
/* TIFFFileName (0x6d850) — readable C lift. */
char *TIFFFileName(void *tif)
{
  return *(char **)tif;
}
""",
    "char *TIFFFileName(void *tif);",
)

L(
    0x6D860,
    "bitmaps/libtiff/tif_open.c",
    "TIFFFileno",
    """
/* TIFFFileno (0x6d860) — readable C lift. */
int TIFFFileno(void *tif)
{
  return (int)*((short *)tif + 2);
}
""",
    "int TIFFFileno(void *tif);",
)

L(
    0x6D870,
    "bitmaps/libtiff/tif_open.c",
    "TIFFGetMode",
    """
/* TIFFGetMode (0x6d870) — readable C lift. */
int TIFFGetMode(void *tif)
{
  return (int)*((short *)tif + 3);
}
""",
    "int TIFFGetMode(void *tif);",
)

L(
    0x6D880,
    "bitmaps/libtiff/tif_open.c",
    "TIFFIsTiled",
    """
/* TIFFIsTiled (0x6d880) — readable C lift. */
int TIFFIsTiled(void *tif)
{
  return (((int)*((char *)tif + 0xa)) & 0x80) >> 7;
}
""",
    "int TIFFIsTiled(void *tif);",
)

L(
    0x6D8A0,
    "bitmaps/libtiff/tif_open.c",
    "TIFFCurrentRow",
    """
/* TIFFCurrentRow (0x6d8a0) — readable C lift. */
unsigned int TIFFCurrentRow(void *tif)
{
  return *(unsigned int *)((char *)tif + 0xd4);
}
""",
    "unsigned int TIFFCurrentRow(void *tif);",
)

L(
    0x6D8B0,
    "bitmaps/libtiff/tif_open.c",
    "TIFFCurrentDirectory",
    """
/* TIFFCurrentDirectory (0x6d8b0) — readable C lift. */
unsigned int TIFFCurrentDirectory(void *tif)
{
  return *(unsigned int *)((char *)tif + 0xd8);
}
""",
    "unsigned int TIFFCurrentDirectory(void *tif);",
)

L(
    0x6D8C0,
    "bitmaps/libtiff/tif_open.c",
    "TIFFCurrentStrip",
    """
/* TIFFCurrentStrip (0x6d8c0) — readable C lift. */
unsigned int TIFFCurrentStrip(void *tif)
{
  return *(unsigned int *)((char *)tif + 0xdc);
}
""",
    "unsigned int TIFFCurrentStrip(void *tif);",
)

L(
    0x6D8D0,
    "bitmaps/libtiff/tif_open.c",
    "TIFFCurrentTile",
    """
/* TIFFCurrentTile (0x6d8d0) — readable C lift. */
unsigned int TIFFCurrentTile(void *tif)
{
  return *(unsigned int *)((char *)tif + 0xe8);
}
""",
    "unsigned int TIFFCurrentTile(void *tif);",
)

L(
    0x6D820,
    "bitmaps/libtiff/tif_open.c",
    "TIFFScanlineSize",
    """
/* TIFFScanlineSize (0x6d820) — readable C lift. */
unsigned int TIFFScanlineSize(void *tif)
{
  unsigned int size;

  size = (unsigned int)*((unsigned short *)((char *)tif + 0x36));
  size *= *(unsigned int *)((char *)tif + 0x1c);
  if (*((unsigned short *)((char *)tif + 0x5e)) == 1) {
    size *= (unsigned int)*((unsigned short *)((char *)tif + 0x44));
  }
  return (size + 7) >> 3;
}
""",
    "unsigned int TIFFScanlineSize(void *tif);",
)

L(
    0x6D4D0,
    "bitmaps/libtiff/tif_open.c",
    "FUN_0006d4d0",
    """
/* FUN_0006d4d0 (0x6d4d0) — readable C lift. */
int FUN_0006d4d0(void *tif)
{
  *(unsigned int *)((char *)tif + 0xfc) = 0x6d340;
  *(unsigned int *)((char *)tif + 0x104) = 0x6d340;
  *(unsigned int *)((char *)tif + 0x10c) = 0x6d340;
  return 1;
}
""",
    "int FUN_0006d4d0(void *tif);",
)

# --- tif_flush / tif_write small leaves ---
L(
    0x68940,
    "bitmaps/libtiff/tif_flush.c",
    "FUN_00068940",
    """
/* FUN_00068940 (0x68940) — readable C lift. */
int FUN_00068940(void *tif, int count)
{
  int stride;

  stride = *(int *)((char *)tif + 0x124) * count;
  *(int *)((char *)tif + 0x134) += stride;
  *(int *)((char *)tif + 0x138) -= stride;
  return 1;
}
""",
    "int FUN_00068940(void *tif, int count);",
)

L(
    0x68A10,
    "bitmaps/libtiff/tif_flush.c",
    "FUN_00068a10",
    """
/* FUN_00068a10 (0x68a10) — readable C lift: swap global handler. */
void *FUN_00068a10(void *handler)
{
  void *prev;

  prev = *(void **)0x2ca1f4;
  *(void **)0x2ca1f4 = handler;
  return prev;
}
""",
    "void *FUN_00068a10(void *handler);",
)

L(
    0x68A50,
    "bitmaps/libtiff/tif_flush.c",
    "FUN_00068a50",
    """
/* FUN_00068a50 (0x68a50) — readable C lift: set/clear flag bit0 at tif+9. */
void FUN_00068a50(void *tif, int enable)
{
  unsigned char flags;

  flags = *((unsigned char *)tif + 9);
  if (enable) {
    *((unsigned char *)tif + 9) = (unsigned char)(flags | 1);
  } else {
    *((unsigned char *)tif + 9) = (unsigned char)(flags & 0xfe);
  }
}
""",
    "void FUN_00068a50(void *tif, int enable);",
)

L(
    0x6F9B0,
    "bitmaps/libtiff/tif_write.c",
    "FUN_0006f9b0",
    """
/* FUN_0006f9b0 (0x6f9b0) — readable C lift: swap global handler. */
void *FUN_0006f9b0(void *handler)
{
  void *prev;

  prev = *(void **)0x2ecfac;
  *(void **)0x2ecfac = handler;
  return prev;
}
""",
    "void *FUN_0006f9b0(void *handler);",
)

L(
    0x6F1B0,
    "bitmaps/libtiff/tif_write.c",
    "FUN_0006f1b0",
    """
/* FUN_0006f1b0 (0x6f1b0) — readable C lift: swap two bytes. */
void FUN_0006f1b0(unsigned char *p)
{
  unsigned char t;

  t = p[1];
  p[1] = p[0];
  p[0] = t;
}
""",
    "void FUN_0006f1b0(unsigned char *p);",
)

L(
    0x6F1D0,
    "bitmaps/libtiff/tif_write.c",
    "FUN_0006f1d0",
    """
/* FUN_0006f1d0 (0x6f1d0) — readable C lift: endian-swap 4 bytes. */
void FUN_0006f1d0(unsigned char *p)
{
  unsigned char b0;
  unsigned char b1;

  b0 = p[0];
  p[0] = p[3];
  b1 = p[2];
  p[3] = b0;
  p[2] = p[1];
  p[1] = b1;
}
""",
    "void FUN_0006f1d0(unsigned char *p);",
)

L(
    0x6F1F0,
    "bitmaps/libtiff/tif_write.c",
    "FUN_0006f1f0",
    """
/* FUN_0006f1f0 (0x6f1f0) — readable C lift: swap pairs for count words. */
void FUN_0006f1f0(unsigned char *p, int count)
{
  unsigned char t;

  while (count > 0) {
    t = p[1];
    p[1] = p[0];
    p[0] = t;
    p += 2;
    count -= 1;
  }
}
""",
    "void FUN_0006f1f0(unsigned char *p, int count);",
)

L(
    0x6F220,
    "bitmaps/libtiff/tif_write.c",
    "FUN_0006f220",
    """
/* FUN_0006f220 (0x6f220) — readable C lift: endian-swap count dwords. */
void FUN_0006f220(unsigned char *p, int count)
{
  unsigned char b0;
  unsigned char b1;

  while (count > 0) {
    b0 = p[0];
    p[0] = p[3];
    b1 = p[2];
    p[3] = b0;
    p[2] = p[1];
    p[1] = b1;
    p += 4;
    count -= 1;
  }
}
""",
    "void FUN_0006f220(unsigned char *p, int count);",
)

L(
    0x6F670,
    "bitmaps/libtiff/tif_write.c",
    "FUN_0006f670",
    """
/* FUN_0006f670 (0x6f670) — readable C lift. */
int FUN_0006f670(void *tif)
{
  *(unsigned int *)((char *)tif + 0xfc) = 0x6f620;
  *(unsigned int *)((char *)tif + 0x104) = 0x6f620;
  return 1;
}
""",
    "int FUN_0006f670(void *tif);",
)

L(
    0x6F120,
    "bitmaps/libtiff/tif_write.c",
    "FUN_0006f120",
    """
/* FUN_0006f120 (0x6f120) — readable C lift. */
unsigned int FUN_0006f120(void *tif)
{
  unsigned int a;
  unsigned int b;

  a = *(unsigned int *)((char *)tif + 0x48);
  b = *(unsigned int *)((char *)tif + 0x20);
  if (a == 0xffffffff) {
    return b != 0;
  }
  return (b + a - 1) / a;
}
""",
    "unsigned int FUN_0006f120(void *tif);",
)

# --- ai ---
L(
    0x493D0,
    "ai/ai_debug.c",
    "ai_debug_get_last_path",
    """
/* ai_debug_get_last_path (0x493d0) — readable C lift. */
void ai_debug_get_last_path(float *vec_a, float *vec_b)
{
  *(char *)0x5acab8 = 1;
  *(char *)0x5acab9 = 0;
  *(float *)0x5acabc = vec_a[0];
  *(float *)0x5acac0 = vec_a[1];
  *(float *)0x5acac4 = vec_a[2];
  *(float *)0x5acac8 = vec_b[0];
  *(float *)0x5acacc = vec_b[1];
  *(float *)0x5acad0 = vec_b[2];
  *(int *)0x5acad4 = 0;
}
""",
    "void ai_debug_get_last_path(float *vec_a, float *vec_b);",
)

L(
    0x4B2B0,
    "ai/ai_debug.c",
    "FUN_0004b2b0",
    """
/* FUN_0004b2b0 (0x4b2b0) — readable C lift: advance debug point by dt*vel. */
float *FUN_0004b2b0(void)
{
  float *vel;
  float dt;

  *(float *)0x5ac9a0 = *(float *)0x5ac9b0;
  *(float *)0x5ac9a4 = *(float *)0x5ac9b4;
  *(float *)0x5ac9a8 = *(float *)0x5ac9b8;
  vel = *(float **)0x31fc44;
  dt = *(float *)0x5ac990;
  *(float *)0x5ac9b0 = dt * vel[0] + *(float *)0x5ac9b0;
  *(float *)0x5ac9b4 = dt * vel[1] + *(float *)0x5ac9a4;
  *(float *)0x5ac9b8 = dt * vel[2] + *(float *)0x5ac9a8;
  return (float *)0x5ac9a0;
}
""",
    "float *FUN_0004b2b0(void);",
)

# --- effects ---
L(
    0x99490,
    "effects/decals.c",
    "FUN_00099490",
    """
/* FUN_00099490 (0x99490) — readable C lift: plane from point+normal. */
void FUN_00099490(float *plane, float *point, float *normal)
{
  plane[0] = normal[0];
  plane[1] = normal[1];
  plane[2] = normal[2];
  plane[3] = plane[0] * point[0] + plane[1] * point[1] + plane[2] * point[2];
}
""",
    "void FUN_00099490(float *plane, float *point, float *normal);",
)

L(
    0x9FAD0,
    "effects/particle_systems.c",
    "FUN_0009fad0",
    """
/* FUN_0009fad0 (0x9fad0) — readable C lift: copy particle velocity/position fields. */
void FUN_0009fad0(float *src_a, int unused_b, float *dst, float *src_b)
{
  float *from;
  float *to;

  (void)unused_b;
  from = src_b + 24; /* +0x60 bytes */
  to = dst + 7;      /* +0x1c bytes */
  to[0] = from[0];
  to[1] = from[1];
  to[2] = from[2];
  from = src_a + 11; /* +0x2c */
  to = dst + 10;     /* +0x28 */
  to[0] = from[0];
  to[1] = from[1];
  to[2] = from[2];
}
""",
    "void FUN_0009fad0(float *src_a, int unused_b, float *dst, float *src_b);",
)

L(
    0xA28E0,
    "effects/player_effects.c",
    "scripted_player_effect_set_rotation",
    """
/* scripted_player_effect_set_rotation (0xa28e0) — readable C lift (deg→rad scale). */
void scripted_player_effect_set_rotation(float yaw, float pitch, float roll)
{
  char *fx;
  float scale;

  fx = *(char **)0x4557ec;
  scale = *(float *)0x253d4c;
  *(float *)(fx + 0x3d0) = yaw * scale;
  *(float *)(fx + 0x3d4) = pitch * scale;
  *(float *)(fx + 0x3d8) = roll * scale;
}
""",
    "void scripted_player_effect_set_rotation(float yaw, float pitch, float roll);",
)

L(
    0xA2E40,
    "effects/player_effects.c",
    "scripted_player_effect_stop",
    """
/* scripted_player_effect_stop (0xa2e40) — readable C lift. */
void scripted_player_effect_stop(float seconds)
{
  char *fx;
  int ticks;

  ticks = (int)(seconds * *(float *)0x253394);
  fx = *(char **)0x4557ec;
  *(short *)(fx + 0x3e0) = (short)ticks;
  *(short *)(fx + 0x3e2) = (short)ticks;
  *(int *)(fx + 0x3e4) |= 2;
}
""",
    "void scripted_player_effect_stop(float seconds);",
)

# --- structures ---
L(
    0x1937A0,
    "structures/structure_bsp_definitions.c",
    "vertex_type_from_shader_tag",
    """
/* vertex_type_from_shader_tag (0x1937a0) — readable C lift. */
void vertex_type_from_shader_tag(int unused_a, short *type_a, short *type_b, char lit)
{
  (void)unused_a;
  if (lit) {
    *type_a = 1;
    *type_b = 3;
  } else {
    *type_a = 0;
    *type_b = 2;
  }
}
""",
    "void vertex_type_from_shader_tag(int unused_a, short *type_a, short *type_b, char lit);",
)

# --- physics ---
L(
    0x1546F0,
    "physics/point_physics.c",
    "FUN_001546f0",
    """
/* FUN_001546f0 (0x1546f0) — readable C lift: wrapped delta sign helper. */
float FUN_001546f0(float *bounds, float from, char wrap_flag, float to)
{
  float delta;
  float span;
  float abs_delta;

  delta = to - from;
  if (delta == *(float *)0x2533c0) {
    return delta;
  }
  if (wrap_flag) {
    abs_delta = delta < 0.0f ? -delta : delta;
    span = (bounds[0] - bounds[1]) * *(float *)0x253398;
    if (abs_delta > span) {
      delta = -delta;
    }
  }
  if (delta > *(float *)0x2533c0) {
    return *(float *)0x2533c8;
  }
  return *(float *)0x255e94;
}
""",
    "float FUN_001546f0(float *bounds@<ecx>, float from, char wrap_flag, float to);",
)

# --- rasterizer globals / helpers ---
L(
    0x1792C0,
    "rasterizer/rasterizer.c",
    "FUN_001792C0",
    """
/* FUN_001792C0 (0x1792c0) — readable C lift. */
void FUN_001792C0(char flag)
{
  *(char *)0x47e4c9 = flag;
}
""",
    "void FUN_001792C0(char flag);",
)

L(
    0x1792A0,
    "rasterizer/rasterizer.c",
    "FUN_001792a0",
    """
/* FUN_001792a0 (0x1792a0) — readable C lift. */
void FUN_001792a0(char flag)
{
  *(char *)0x47e4c8 = (char)(flag == 0);
  *(char *)0x47e4c9 = flag;
}
""",
    "void FUN_001792a0(char flag);",
)

L(
    0x174B60,
    "rasterizer/rasterizer.c",
    "FUN_00174b60",
    """
/* FUN_00174b60 (0x174b60) — readable C lift: plane/vec4 subtract. */
void FUN_00174b60(float *a, float *b, float *out)
{
  out[0] = a[0] - b[0];
  out[1] = a[1] - b[1];
  out[2] = a[2] - b[2];
  out[3] = a[3] - b[3];
}
""",
    "void FUN_00174b60(float *a, float *b, float *out);",
)

L(
    0x174B90,
    "rasterizer/rasterizer.c",
    "FUN_00174b90",
    """
/* FUN_00174b90 (0x174b90) — readable C lift: out = a + t*b (vec4). */
void FUN_00174b90(float *a, float *b, float t, float *out)
{
  out[0] = t * b[0] + a[0];
  out[1] = t * b[1] + a[1];
  out[2] = t * b[2] + a[2];
  out[3] = t * b[3] + a[3];
}
""",
    "void FUN_00174b90(float *a, float *b, float t, float *out);",
)

L(
    0x17DC60,
    "rasterizer/rasterizer_sprites.c",
    "FUN_0017dc60",
    """
/* FUN_0017dc60 (0x17dc60) — readable C lift. */
void FUN_0017dc60(void)
{
  char *spr;

  spr = *(char **)0x47e4d4;
  if (spr) {
    spr[0x38] = 0;
  }
}
""",
)

L(
    0x17DEC0,
    "rasterizer/rasterizer_sprites.c",
    "FUN_0017dec0",
    """
/* FUN_0017dec0 (0x17dec0) — readable C lift. */
void FUN_0017dec0(int value)
{
  char *spr;

  spr = *(char **)0x47e4d4;
  if (spr) {
    *(int *)(spr + 0x74) = value;
  }
}
""",
    "void FUN_0017dec0(int value);",
)

L(
    0x17DB20,
    "rasterizer/rasterizer_sprites.c",
    "FUN_0017db20",
    """
/* FUN_0017db20 (0x17db20) — readable C lift. */
void FUN_0017db20(int a, int b, int c)
{
  char *spr;

  spr = *(char **)0x47e4d4;
  if (spr) {
    *(int *)(spr + 0x14) = a;
    *(int *)(spr + 0x18) = b;
    *(int *)(spr + 0x1c) = c;
  }
}
""",
    "void FUN_0017db20(int a, int b, int c);",
)

L(
    0x17ED70,
    "rasterizer/rasterizer_sprites.c",
    "FUN_0017ed70",
    """
/* FUN_0017ed70 (0x17ed70) — readable C lift. */
char FUN_0017ed70(unsigned short a, unsigned short b)
{
  return a > b;
}
""",
    "char FUN_0017ed70(unsigned short a, unsigned short b);",
)

L(
    0x15E7A0,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_0015e7a0",
    """
/* FUN_0015e7a0 (0x15e7a0) — readable C lift. */
void FUN_0015e7a0(void *obj, int *out, int addend)
{
  *out = *(int *)((char *)obj + 4) + addend;
}
""",
    "void FUN_0015e7a0(void *obj@<eax>, int *out@<edx>, int addend);",
)

L(
    0x15E7D0,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_0015e7d0",
    """
/* FUN_0015e7d0 (0x15e7d0) — readable C lift. */
int FUN_0015e7d0(void *obj, int *out, int addend)
{
  *out = *(int *)((char *)obj + 4) + addend;
  return 0;
}
""",
    "int FUN_0015e7d0(void *obj@<eax>, int *out@<edx>, int addend);",
)

L(
    0x168C70,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_00168c70",
    """
/* FUN_00168c70 (0x168c70) — readable C lift. */
void FUN_00168c70(void *obj, int *out, int addend)
{
  *out = *(int *)((char *)obj + 4) + addend;
}
""",
    "void FUN_00168c70(void *obj@<eax>, int *out@<edx>, int addend);",
)

L(
    0x168CA0,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_00168ca0",
    """
/* FUN_00168ca0 (0x168ca0) — readable C lift. */
int FUN_00168ca0(void *obj, int *out, int addend)
{
  *out = *(int *)((char *)obj + 4) + addend;
  return 0;
}
""",
    "int FUN_00168ca0(void *obj@<eax>, int *out@<edx>, int addend);",
)


L(
    0x17DEE0,
    "rasterizer/rasterizer_sprites.c",
    "FUN_0017dee0",
    """
/* FUN_0017dee0 (0x17dee0) — readable C lift. */
float FUN_0017dee0(void)
{
  char *spr;
  float v;

  spr = *(char **)0x47e4d4;
  v = *(float *)0x2af1ac;
  if (spr) {
    if (*(float *)(spr + 0x74) > *(float *)0x2533c0) {
      v = *(float *)(spr + 0x74);
    }
  }
  return v;
}
""",
    "float FUN_0017dee0(void);",
)

L(
    0x17E010,
    "rasterizer/rasterizer_sprites.c",
    "FUN_0017e010",
    """
/* FUN_0017e010 (0x17e010) — readable C lift. */
void FUN_0017e010(void)
{
  *(int *)0x47e4e0 = 0;
  *(int *)0x47e4e8 = 0;
  *(int *)0x47e4f0 = 0;
  *(int *)0x47e4f4 = 0;
}
""",
)

L(
    0x17D9A0,
    "rasterizer/rasterizer_sprites.c",
    "FUN_0017d9a0",
    """
/* FUN_0017d9a0 (0x17d9a0) — readable C lift. */
void FUN_0017d9a0(short index, float value)
{
  char *spr;

  spr = *(char **)0x47e4d4;
  if (spr && index >= 0 && index < 4) {
    *(float *)(spr + 0x64 + (int)index * 4) = value;
  }
}
""",
    "void FUN_0017d9a0(short index, float value);",
)

L(
    0x17D9D0,
    "rasterizer/rasterizer_sprites.c",
    "FUN_0017d9d0",
    """
/* FUN_0017d9d0 (0x17d9d0) — readable C lift. */
float FUN_0017d9d0(short index)
{
  char *spr;

  spr = *(char **)0x47e4d4;
  if (!spr || index < 0 || index >= 4) {
    return *(float *)0x2533c0;
  }
  return *(float *)(spr + 0x64 + (int)index * 4);
}
""",
    "float FUN_0017d9d0(short index);",
)

L(
    0x17ED90,
    "rasterizer/rasterizer_sprites.c",
    "FUN_0017ed90",
    """
/* FUN_0017ed90 (0x17ed90) — readable C lift. */
int FUN_0017ed90(short *a, short *b)
{
  if (!a) {
    return 0;
  }
  if (!b) {
    return 0;
  }
  if (a[0] == 1) {
    return *(int *)(a + 2) + 2;
  }
  if (a[0] == 0) {
    return *(int *)(b + 2);
  }
  return 0;
}
""",
    "int FUN_0017ed90(short *a, short *b);",
)

L(
    0x165FD0,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_00165fd0",
    """
/* FUN_00165fd0 (0x165fd0) — readable C lift. */
void FUN_00165fd0(float *out, float f0, int a, int b, int c)
{
  out[0] = f0;
  *(int *)(out + 1) = a;
  *(int *)(out + 2) = b;
  *(int *)(out + 3) = c;
}
""",
    "void FUN_00165fd0(float *out, float f0, int a, int b, int c);",
)

L(
    0x16B270,
    "rasterizer/xbox/rasterizer_xbox_dynavobgeom.c",
    "FUN_0016b270",
    """
/* FUN_0016b270 (0x16b270) — readable C lift. */
void FUN_0016b270(int a0, float a1, float a2, float a3)
{
  char *g;

  g = *(char **)0x47e4d0;
  if (g) {
    *(int *)g = a0;
    *(float *)(g + 4) = a1;
    *(float *)(g + 8) = a2;
    *(float *)(g + 0xc) = a3;
  }
}
""",
    "void FUN_0016b270(int a0, float a1, float a2, float a3);",
)

L(
    0x6DD50,
    "bitmaps/libtiff/tif_open.c",
    "FUN_0006dd50",
    """
/* FUN_0006dd50 (0x6dd50) — readable C lift. */
int FUN_0006dd50(void *tif)
{
  *(unsigned int *)((char *)tif + 0xfc) = 0x6dbf0;
  *(unsigned int *)((char *)tif + 0x104) = 0x6dbf0;
  *(unsigned int *)((char *)tif + 0x10c) = 0x6dbf0;
  *(unsigned int *)((char *)tif + 0xf4) = 0x6d980;
  *(unsigned int *)((char *)tif + 0x100) = 0x6d9c0;
  *(unsigned int *)((char *)tif + 0x108) = 0x6dd00;
  *(unsigned int *)((char *)tif + 0x110) = 0x6dd00;
  return 1;
}
""",
    "int FUN_0006dd50(void *tif);",
)

L(
    0x70570,
    "bitmaps/libtiff/tif_write.c",
    "FUN_00070570",
    """
/* FUN_00070570 (0x70570) — readable C lift: pack RGB888→RGB565. */
void FUN_00070570(unsigned char *rgb, unsigned short *out)
{
  unsigned int r;
  unsigned int g;
  unsigned int b;

  b = (unsigned int)(rgb[2] >> 3);
  g = (unsigned int)(rgb[1] >> 2);
  r = (unsigned int)(rgb[0] >> 3);
  *out = (unsigned short)(((b << 6) | g) << 5 | r);
}
""",
    "void FUN_00070570(unsigned char *rgb@<eax>, unsigned short *out);",
)

def find_naked_block(text: str, name: str, addr: int):
    """Locate the Capstone naked draft that *defines* name (not mere callee refs)."""
    addr_hex = f"0x{addr:x}"
    alt_names = {name, f"FUN_{addr:08x}", f"FUN_{addr:08X}"}
    for nm in alt_names:
        pat = re.compile(
            rf"/\*[^*]*\b{re.escape(addr_hex)}\b[^*]*(?:XBE naked draft|naked draft \(batch)?[^*]*\*/\s*"
            rf"#if defined\(__clang__\)\s*"
            rf"(?:static[\s\S]*?)?"
            rf"__attribute__\(\(naked[^\)]*\)\)\s*"
            rf"[\w\s\*]+?\b{re.escape(nm)}\s*\([\s\S]*?#endif\s*\n",
            re.M | re.I,
        )
        m = pat.search(text)
        if m:
            return m.start(), m.end()
    return None


def cast_stale_fnptrs(text: str, names: set[str]) -> str:
    """Keep old static fnptr types; cast initializers through void* to silence -Werror."""

    def repl(m: re.Match) -> str:
        sym = m.group(2)
        if sym not in names:
            return m.group(0)
        if "(void *)" in m.group(0) or "(void*)" in m.group(0):
            return m.group(0)
        return f"{m.group(1)}(void *){sym};"

    return re.sub(
        r"(static\s+[\w\s\*]+?\(\s*\*\s*const\s+b[0-9a-fA-F]+_[cC][0-9a-fA-F]+\s*\)\s*\([^;]*?\)\s*=\s*)(?:\([^)]*\)\s*)?([A-Za-z_][\w]*)\s*;",
        repl,
        text,
    )


def apply_lifts(addrs=None):
    selected = addrs if addrs else sorted(LIFTS.keys())
    by_source: dict[str, list[int]] = {}
    names: set[str] = set()
    for a in selected:
        if a not in LIFTS:
            print(f"skip unknown {hex(a)}", file=sys.stderr)
            continue
        by_source.setdefault(LIFTS[a][0], []).append(a)
        names.add(LIFTS[a][1])

    results = []
    for src, alist in by_source.items():
        path = ROOT / "src" / "halo" / src
        text = path.read_text(encoding="utf-8", errors="replace")
        before = text
        for a in sorted(alist, reverse=True):
            _source, name, body, decl = LIFTS[a]
            span = find_naked_block(text, name, a)
            if span is None:
                print(f"FAIL locate {hex(a)} {name} in {src}", file=sys.stderr)
                results.append({"addr": hex(a), "ok": False})
                continue
            start, end = span
            # Guard: replaced span must mention this addr and define this name.
            chunk = text[start:end]
            if f"0x{a:x}" not in chunk.lower() and f"0x{a:X}" not in chunk:
                print(f"FAIL addr-guard {hex(a)} {name} in {src}", file=sys.stderr)
                results.append({"addr": hex(a), "ok": False})
                continue
            text = text[:start] + body + "\n" + text[end:]
            print(f"lifted {hex(a)} {name}")
            results.append({"addr": hex(a), "name": name, "ok": True, "decl": decl})
        if text != before:
            path.write_text(text, encoding="utf-8")

    for path in (ROOT / "src" / "halo").rglob("*.c"):
        text = path.read_text(encoding="utf-8", errors="replace")
        text2 = cast_stale_fnptrs(text, names)
        if text2 != text:
            path.write_text(text2, encoding="utf-8")
            print(f"cast-fnptrs {path.relative_to(ROOT)}")

    decl_map = {a: LIFTS[a][3] for a in selected if a in LIFTS and LIFTS[a][3]}
    if decl_map:
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        n = 0
        for obj in kb.get("objects", []):
            for fn in obj.get("functions") or []:
                if not isinstance(fn, dict) or not fn.get("addr"):
                    continue
                ai = int(fn["addr"], 16)
                if ai in decl_map:
                    fn["decl"] = decl_map[ai]
                    n += 1
        KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        print(f"updated {n} kb decls")
    return results


def main() -> int:
    results = apply_lifts()
    ok = sum(1 for r in results if r.get("ok"))
    print(f"done: {ok}/{len(results)}")
    return 0 if ok == len(results) else 1


if __name__ == "__main__":
    raise SystemExit(main())
