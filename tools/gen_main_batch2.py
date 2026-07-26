#!/usr/bin/env python3
"""Generate main.obj batch2 draft implementations + disassembly artifact."""
from __future__ import annotations

import json
import re
from pathlib import Path

from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "tools" / "main_batch2_fragment.c"
DISASM_OUT = ROOT / "artifacts" / "main_batch2_disasm.txt"
MAIN_C = ROOT / "src" / "halo" / "main" / "main.c"
OBJECT = "main.obj"
MARKER = "/* --- main.obj batch2 drafts (2026-07-26) --- */"

IMPL = r'''
/* --- main.obj batch2 drafts (2026-07-26) --- */

void FUN_00054df0(void);

/* kb.json spans 0xe8e20..0xffe10 (94 KiB) across many distinct functions.
 * Bogus single-symbol boundary — placeholder draft only. */
void FUN_000e8e20(int a0)
{
  (void)a0;
}

void FUN_000ffeb0(char param_1)
{
  if (param_1 != 0) {
    FUN_00054df0();
    return;
  }
}

void main_framerate_render(void)
{
  char text[4];
  char text2[4];
  int16_t pos[2];
  int player;
  int fps;
  float progress;

  if (*(char *)0x46e004 != 0) {
    player = *(int *)(*(int *)0x46bd0c + 0x54);
    if (player != -1) {
      float frame = *(float *)0x46da08;
      float capped;

      if (frame <= *(float *)0x25bb10)
        capped = frame;
      else
        capped = *(float *)0x2533c8 / *(float *)0x25bb10;
      fps = (int)capped;
      if (*(char *)0x46dd9a != 0)
        fps = 60 / *(int16_t *)0x46dd96;

      snprintf(text, 3, (char *)0x25acb8, fps);
      pos[0] = (int16_t)(*(int *)0x506588 - 0x32);
      pos[1] = (int16_t)(*(int *)0x506584 - 0x32);
      draw_string_set_style_justify_flags(-1, 0, 0);
      draw_string_set_color((const void *)((int16_t)fps < 0x1e
                                               ? *(int *)0x2ee6d0
                                               : *(int *)0x2ee6d4));
      FUN_0019B7E0();
      rasterizer_text_draw(0, pos, 0, 0, text);
    }
  }

  if (*(char *)0x46e005 != 0) {
    int16_t dx;
    int16_t total;

    player = *(int *)(*(int *)0x46bd0c + 0x54);
    if (player != -1) {
      pos[0] = (int16_t)(*(int *)0x506588 - 0x32);
      pos[1] = (int16_t)(*(int *)0x506584 - 0x32);
      total = *(int16_t *)0x46dddc;
      dx = (int16_t)((total + 0xe) / 0xf);
      if (dx != total) {
        do {
          int16_t val = *(int16_t *)(dx * 2 + 0x46ddde);

          pos[0] = (int16_t)(pos[0] - 20);
          pos[1] = (int16_t)(pos[1] - 20);
          snprintf(text2, 3, (char *)0x25acb8, val);
          draw_string_set_style_justify_flags(-1, 1, 0);
          FUN_0019B7E0();
          draw_string_set_color((const void *)(val == 2 ? *(int *)0x2ee6c4
                                                         : *(int *)0x2ee6d0));
          rasterizer_text_draw(0, pos, 0, 0, text2);
          dx = (int16_t)((dx + 0xe) / 0xf);
        } while (dx != total);
      }
    }
  }

  if (*(char *)0x46e006 == 0)
    return;
  if (!cache_files_precache_in_progress())
    return;

  player = *(int *)(*(int *)0x46bd0c + 0x54);
  if (player == -1)
    return;
  if (cache_files_precache_map_status(&progress) != 0)
    return;

  fps = (int)(progress * *(float *)0x253f00);
  snprintf(text, 3, (char *)0x25acb8, fps);
  pos[0] = (int16_t)(*(int *)0x506588 - 0x32);
  pos[1] = (int16_t)(*(int *)0x506584 - 0x64);
  draw_string_set_style_justify_flags(-1, 0, 0);
  draw_string_set_color((const void *)*(int *)0x2ee6f4);
  FUN_0019B7E0();
  rasterizer_text_draw(0, pos, 0, 0, text);
}

void FUN_001034b0(int *obj)
{
  array_new(obj, 0xc);
  array_new(obj + 3, 0x1c);
  array_new(obj + 6, 0x18);
}

int FUN_00103600(int *array /* @<esi> */, float *vec /* @<ebx> */)
{
  int i;
  int count;
  float *elem;

  count = array[1];
  for (i = 0; i < count; i++) {
    elem = (float *)FUN_00117ee0(array, i, 0xc);
    if (fabs(vec[0] - elem[0]) > *(double *)0x2549d8)
      continue;
    if (fabs(vec[1] - elem[1]) > *(double *)0x2549d8)
      continue;
    if (fabs(vec[2] - elem[2]) > *(double *)0x2549d8)
      continue;
    return i;
  }
  if (i != count)
    return i;
  i = FUN_00117da0(array);
  if (i == -1)
    return i;
  elem = (float *)FUN_00117ee0(array, i, 0xc);
  elem[0] = vec[0];
  elem[1] = vec[1];
  elem[2] = vec[2];
  return i;
}

int FUN_001036c0(int *base /* @<eax> */, int a, int b, int flag)
{
  int i;
  int count;
  int *elem;
  char insert_flag;

  count = base[4];
  insert_flag = 1;
  for (i = 0; i < count; i++) {
    elem = (int *)FUN_00117ee0(base + 3, i, 0x1c);
    if (elem[3] == a && elem[4] == b) {
      insert_flag = 1;
      goto done_search;
    }
    if (elem[3] == b && elem[4] == a) {
      insert_flag = 0;
      goto done_search;
    }
  }
done_search:
  if (i == count) {
    i = FUN_00117da0(base + 3);
    if (i == -1)
      goto out;
    elem = (int *)FUN_00117ee0(base + 3, i, 0x1c);
    array_new(elem, 4);
    elem[3] = a;
    elem[4] = b;
  }
  if (i == -1)
    goto out;
  elem = (int *)FUN_00117ee0(base + 3, i, 0x1c);
  {
    int slot = FUN_00117da0(elem);
    if (slot == -1)
      goto out;
    *(int *)FUN_00117ee0(elem, slot, 4) = flag;
    if (insert_flag != 0)
      return i;
    return i | 0x80000000;
  }
out:
  return -1;
}

float *FUN_001037b0(float *out, float *p0, float *p1, float *p2)
{
  float e1[3];
  float e2[3];

  e1[0] = p1[0] - p0[0];
  e1[1] = p1[1] - p0[1];
  e1[2] = p1[2] - p0[2];
  e2[0] = p2[0] - p0[0];
  e2[1] = p2[1] - p0[1];
  e2[2] = p2[2] - p0[2];
  out[0] = e1[1] * e2[2] - e1[2] * e2[1];
  out[1] = e1[2] * e2[0] - e1[0] * e2[2];
  out[2] = e1[0] * e2[1] - e1[1] * e2[0];
  normalize3d(out);
  if (out[0] * out[0] + out[1] * out[1] + out[2] * out[2] <= *(float *)0x2533c0) {
    out[3] = 0.0f;
    return 0;
  }
  out[3] = out[0] * p0[0] + out[1] * p0[1] + out[2] * p0[2];
  return out;
}

int FUN_00103860(int base, float *a, float *b, float *c, char flag)
{
  int slot;
  int i;
  int *elem;
  int indices[3];
  int result;

  slot = FUN_00117da0((int *)(base + 0x18));
  if (slot == -1)
    return -1;
  elem = (int *)FUN_00117ee0((int *)(base + 0x18), slot, 0x18);
  result = FUN_00103600((int *)base, a);
  indices[0] = result;
  result = FUN_00103600((int *)base, b);
  indices[1] = result;
  result = FUN_00103600((int *)base, c);
  indices[2] = result;
  if (indices[0] == -1 || indices[1] == -1 || indices[2] == -1)
    slot = -1;
  elem = (int *)FUN_00117ee0((int *)(base + 0x18), slot, 0x18);
  for (i = 1; i <= 3; i++) {
    int edge = FUN_001036c0((int *)base, indices[i % 3], indices[i - 1], flag);
    elem[i - 1] = edge;
    if (edge == 0)
      slot = 0;
  }
  csmemset(elem + 3, 0, 8);
  elem[3] = -1;
  if (flag == 0)
    return slot;
  {
    int tri;
    int *tri_elem;
    int j;

    for (tri = 0; tri < *(int *)(base + 0x1c); tri++) {
      tri_elem = (int *)FUN_00117ee0((int *)(base + 0x18), tri, 0x18);
      for (j = 0; j < 3; j++) {
        int lhs = tri_elem[j] & 0x7fffffff;
        int rhs = indices[j] & 0x7fffffff;
        if (lhs != rhs)
          break;
      }
      if (j == 3)
        goto draw;
    }
    if (j == 3)
      goto done;
draw:
    FUN_00104040(a, b, c, (float *)0x2ee6f0);
    if (*(char *)0x46e393 == 0) {
      ((void (__cdecl *)(wchar_t *))0x1db443)((wchar_t *)0x28b780);
      *(char *)0x46e393 = 1;
    }
done:
    return slot;
  }
}

char FUN_00103a00(uint32_t mark, int base, uint32_t *node, uint32_t plane_arg)
{
  float *plane;
  float *p0;
  float *p1;
  float *p2;
  float local[4];
  float dot0;
  float dot1;
  float dot2;

  (void)mark;
  plane = (float *)plane_arg;
  p0 = (float *)FUN_00117ee0((int *)(base + 0xc),
                               node[0] & 0x7fffffff, 0x1c);
  p0 = (float *)FUN_00117ee0((int *)p0, node[0] >> 31 ? 1 : 0, 0xc);
  p1 = (float *)FUN_00117ee0((int *)(base + 0xc),
                               node[1] & 0x7fffffff, 0x1c);
  p1 = (float *)FUN_00117ee0((int *)p1, node[1] >> 31 ? 1 : 0, 0xc);
  p2 = (float *)FUN_00117ee0((int *)(base + 0xc),
                               node[2] & 0x7fffffff, 0x1c);
  p2 = (float *)FUN_00117ee0((int *)p2, node[2] >> 31 ? 1 : 0, 0xc);
  dot0 = p0[0] * plane[0] + p0[1] * plane[1] + p0[2] * plane[2] - plane[3];
  if (fabs(dot0) > *(double *)0x28b800)
    return 0;
  dot1 = p1[0] * plane[0] + p1[1] * plane[1] + p1[2] * plane[2] - plane[3];
  if (fabs(dot1) > *(double *)0x28b800)
    return 0;
  dot2 = p2[0] * plane[0] + p2[1] * plane[1] + p2[2] * plane[2] - plane[3];
  if (fabs(dot2) > *(double *)0x28b800)
    return 0;
  if (FUN_001037b0(local, p0, p1, p2) == 0)
    return 0;
  if (local[0] * p0[0] + local[2] * p0[2] + local[1] * p0[1] >= *(float *)0x2533c0)
    return 0;
  return 1;
}

int FUN_00103c00(int *obj)
{
  int i;
  int count;
  int marked;
  float plane[4];

  marked = 0;
  count = obj[7];
  if (count <= 0)
    return marked;
  for (i = 0; i < count; i++) {
    int *node;
    float *p0;
    float *p1;
    float *p2;

    node = (int *)FUN_00117ee0(obj + 6, i, 0x18);
    p0 = (float *)FUN_00117ee0(obj + 3, node[1] & 0x7fffffff, 0x1c);
    p0 = (float *)FUN_00117ee0((int *)p0, node[1] >> 31 ? 1 : 0, 0xc);
    p1 = (float *)FUN_00117ee0(obj + 3, node[2] & 0x7fffffff, 0x1c);
    p1 = (float *)FUN_00117ee0((int *)p1, node[2] >> 31 ? 1 : 0, 0xc);
    p2 = (float *)FUN_00117ee0(obj + 3, node[0] & 0x7fffffff, 0x1c);
    p2 = (float *)FUN_00117ee0((int *)p2, node[0] >> 31 ? 1 : 0, 0xc);
    if (FUN_001037b0(plane, p0, p1, p2) == 0)
      continue;
    if (node[3] == -1) {
      FUN_00103530((int)obj, FUN_00103a00, (uint32_t)plane, i, marked);
      marked++;
    }
  }
  return marked;
}

void FUN_00103d80(void)
{
  if (*(void **)0x46e394 != NULL) {
    display_assert((char *)0x28b81c, (char *)0x28b838, 0x44, 1);
    system_exit(-1);
  }
  FUN_001db4a9();
}

static void error_geometry_assert_null(const char *name, int line)
{
  display_assert((char *)name, (char *)0x28b838, line, 1);
  system_exit(-1);
}

void FUN_00103e80(float *p0, float *p1, float *color)
{
  float xform0[3];
  float xform1[3];

  if (p0 == 0)
    error_geometry_assert_null((char *)0x28b948, 0x8f);
  if (p1 == 0)
    error_geometry_assert_null((char *)0x28b944, 0x90);
  if (color == 0)
    error_geometry_assert_null((char *)0x269fd8, 0x91);
  if (!FUN_00103d30())
    return;

  matrix_transform_point(xform0, p0, (float *)0x31fb08);
  matrix_transform_point(xform1, p1, (float *)0x31fb08);
  crt_fprintf(*(void **)0x46e394, (char *)0x28b934, *(void **)0x46e394);
  crt_fprintf(*(void **)0x46e394, (char *)0x28b908, xform0[0] * *(float *)0x253f00,
              xform0[1] * *(float *)0x253f00, xform0[2] * *(float *)0x253f00,
              xform1[0] * *(float *)0x253f00, xform1[1] * *(float *)0x253f00,
              xform1[2] * *(float *)0x253f00);
  crt_fprintf(*(void **)0x46e394, (char *)0x28b8e0, *(void **)0x46e394);
  crt_fprintf(*(void **)0x46e394, (char *)0x28b898, *(float *)0x2533c8 - color[0],
              color[1], color[2], color[3], color[1], color[2], color[3]);
  crt_fprintf(*(void **)0x46e394, (char *)0x28b86c, *(void **)0x46e394);
  crt_fprintf(*(void **)0x46e394, (char *)0x28b868, *(void **)0x46e394);
  crt_fflush(*(void **)0x46e394);
}

void FUN_00104040(float *p0, float *p1, float *p2, float *color)
{
  float xform0[3];
  float xform1[3];
  float xform2[3];

  if (p0 == 0)
    error_geometry_assert_null((char *)0x28b948, 0xb1);
  if (p1 == 0)
    error_geometry_assert_null((char *)0x28b944, 0xb2);
  if (p2 == 0)
    error_geometry_assert_null((char *)0x28ba10, 0xb3);
  if (color == 0)
    error_geometry_assert_null((char *)0x269fd8, 0xb4);
  if (!FUN_00103d30())
    return;

  matrix_transform_point(xform0, p0, (float *)0x31fb08);
  matrix_transform_point(xform1, p1, (float *)0x31fb08);
  matrix_transform_point(xform2, p2, (float *)0x31fb08);
  crt_fprintf(*(void **)0x46e394, (char *)0x28b934, *(void **)0x46e394);
  crt_fprintf(*(void **)0x46e394, (char *)0x28b9d8, xform0[0] * *(float *)0x253f00,
              xform0[1] * *(float *)0x253f00, xform0[2] * *(float *)0x253f00,
              xform1[0] * *(float *)0x253f00, xform1[1] * *(float *)0x253f00,
              xform1[2] * *(float *)0x253f00, xform2[0] * *(float *)0x253f00,
              xform2[1] * *(float *)0x253f00, xform2[2] * *(float *)0x253f00);
  crt_fprintf(*(void **)0x46e394, (char *)0x28b9b0, *(void **)0x46e394);
  crt_fprintf(*(void **)0x46e394, (char *)0x28b978, *(float *)0x2533c8 - color[0],
              color[1], color[2], color[3]);
  crt_fprintf(*(void **)0x46e394, (char *)0x28b94c, *(void **)0x46e394);
  crt_fprintf(*(void **)0x46e394, (char *)0x28b868, *(void **)0x46e394);
  crt_fflush(*(void **)0x46e394);
}

void FUN_00104240(int point_count, float *points, float *color)
{
  int i;
  int16_t count;
  float xform[3];

  count = (int16_t)point_count;
  if (count < 0)
    error_geometry_assert_null((char *)0x28ba78, 0xd3);
  if (points == 0)
    error_geometry_assert_null((char *)0x28ba70, 0xd4);
  if (color == 0)
    error_geometry_assert_null((char *)0x269fd8, 0xd5);
  if (count < 3)
    return;
  if (!FUN_00103d30())
    return;

  crt_fprintf(*(void **)0x46e394, (char *)0x28b934, *(void **)0x46e394);
  crt_fprintf(*(void **)0x46e394, (char *)0x28ba58, *(void **)0x46e394);
  if (count > 0) {
    for (i = 0; i < count - 1; i++) {
      matrix_transform_point(xform, points + i * 3, (float *)0x31fb08);
      crt_fprintf(*(void **)0x46e394,
                  (char *)(i + 1 == count - 1 ? 0x28ba4c : 0x28ba54),
                  xform[0] * *(float *)0x253f00, xform[1] * *(float *)0x253f00,
                  xform[2] * *(float *)0x253f00);
    }
  }
  crt_fprintf(*(void **)0x46e394, (char *)0x28b9b0, *(void **)0x46e394);
  crt_fprintf(*(void **)0x46e394, (char *)0x28b978, *(float *)0x2533c8 - color[0],
              color[1], color[2], color[3]);
  crt_fprintf(*(void **)0x46e394, (char *)0x28ba20, *(void **)0x46e394);
  if (count > 0) {
    for (i = 0; i < count; i++)
      crt_fprintf(*(void **)0x46e394, (char *)0x28ba1c, i);
  }
  crt_fprintf(*(void **)0x46e394, (char *)0x28ba14, *(void **)0x46e394);
  crt_fprintf(*(void **)0x46e394, (char *)0x28b868, *(void **)0x46e394);
  crt_fflush(*(void **)0x46e394);
}

void FUN_00104430(int count, int16_t *sections, float *points, float *color)
{
  int i;
  int j;
  int vtx;
  float xform[3];

  if (count < 0)
    error_geometry_assert_null((char *)0x28bb94, 0x14c);
  if (sections == 0)
    error_geometry_assert_null((char *)0x28bb84, 0x14d);
  if (points == 0)
    error_geometry_assert_null((char *)0x28ba70, 0x14e);
  if (count <= 0)
    return;
  if (!FUN_00103d30())
    return;

  crt_fprintf(*(void **)0x46e394, (char *)0x28b934, *(void **)0x46e394);
  crt_fprintf(*(void **)0x46e394, (char *)0x28bb64, *(void **)0x46e394);
  vtx = 0;
  for (i = 0; i < count; i++) {
    int16_t n = sections[i * 2 + 1];
    int k;

    for (k = 0; k < n; k++) {
      matrix_transform_point(xform, points + vtx * 3, (float *)0x31fb08);
      crt_fprintf(*(void **)0x46e394, (char *)0x28bb54,
                  xform[0] * *(float *)0x253f00, xform[1] * *(float *)0x253f00,
                  xform[2] * *(float *)0x253f00);
      vtx++;
    }
  }
  crt_fprintf(*(void **)0x46e394, (char *)0x28bb4c, *(void **)0x46e394);
  crt_fprintf(*(void **)0x46e394, (char *)0x28bb20, *(void **)0x46e394);
  if (color != 0) {
    crt_fprintf(*(void **)0x46e394, (char *)0x28bafc, *(void **)0x46e394);
    for (j = 2; j <= count; j++) {
      crt_fprintf(*(void **)0x46e394, (char *)0x28baec, color[j - 2],
                  color[j - 1], color[j]);
    }
  }
  crt_fprintf(*(void **)0x46e394, (char *)0x28bb0c, *(void **)0x46e394);
  crt_fflush(*(void **)0x46e394);
}
'''

DECLS = {
    "0xe8e20": "void FUN_000e8e20(int a0);",
    "0xffeb0": "void FUN_000ffeb0(char param_1);",
    "0x102700": "void main_framerate_render(void);",
    "0x1034b0": "void FUN_001034b0(int *obj);",
    "0x103600": "int FUN_00103600(int *array @<esi>, float *vec @<ebx>);",
    "0x1036c0": "int FUN_001036c0(int *base @<eax>, int a, int b, int flag);",
    "0x1037b0": "float *FUN_001037b0(float *out, float *p0, float *p1, float *p2);",
    "0x103860": "int FUN_00103860(int base, float *a, float *b, float *c, char flag);",
    "0x103a00": "char FUN_00103a00(uint32_t mark, int base, uint32_t *node, uint32_t plane_arg);",
    "0x103c00": "int FUN_00103c00(int *obj);",
    "0x103d80": "void FUN_00103d80(void);",
    "0x103e80": "void FUN_00103e80(float *p0, float *p1, float *color);",
    "0x104040": "void FUN_00104040(float *p0, float *p1, float *p2, float *color);",
    "0x104240": "void FUN_00104240(int point_count, float *points, float *color);",
    "0x104430": "void FUN_00104430(int count, int16_t *sections, float *points, float *color);",
}

SKIP_DISASM = {"0xe8e20"}


def write_disasm() -> None:
    xbe = Xbe.from_file(str(ROOT / "halo-patched/cachebeta.xbe"))
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    kb = json.loads((ROOT / "kb.json").read_text())
    obj = next(o for o in kb["objects"] if o["name"] == OBJECT)
    addrs = sorted(
        ((int(f["addr"], 16), f) for f in obj["functions"] if f["addr"] in DECLS),
        key=lambda x: x[0],
    )

    addr_name: dict[int, str] = {}
    for o in kb["objects"]:
        for f in o.get("functions", []):
            m = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", f.get("decl") or "")
            if m:
                addr_name[int(f["addr"], 16)] = m.group(1)

    all_fns = sorted(
        ((int(f["addr"], 16), f) for o in kb["objects"] for f in o["functions"]),
        key=lambda x: x[0],
    )
    end_map = {a: all_fns[i + 1][0] if i + 1 < len(all_fns) else a + 0x200
               for i, (a, _) in enumerate(all_fns)}

    def get_bytes(va: int, end: int) -> bytes:
        for sec in xbe.sections.values():
            s = sec.header.virtual_addr
            if s <= va < s + sec.header.virtual_size:
                return bytes(sec.data[va - s : end - s])
        raise RuntimeError(hex(va))

    chunks: list[str] = []
    for va, f in addrs:
        if f["addr"] in SKIP_DISASM:
            chunks.append(
                f"\n=== {f['addr']} SKIPPED (94KB bogus kb boundary) ===\n"
            )
            continue
        end = end_map.get(va, va + 0x200)
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
            DECLS[f["addr"]],
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
    DISASM_OUT.write_text("\n".join(chunks) + "\n")
    print("wrote", DISASM_OUT, len(chunks), "functions")


def append_to_main_c() -> None:
    text = MAIN_C.read_text()
    fragment = IMPL.lstrip() + "\n"
    if MARKER in text:
        before, rest = text.split(MARKER, 1)
        # drop prior batch2 body (until EOF or next batch marker)
        if not before.endswith("\n"):
            before += "\n"
        MAIN_C.write_text(before + fragment)
        print("replaced batch2 fragment in", MAIN_C)
        return
    if not text.endswith("\n"):
        text += "\n"
    MAIN_C.write_text(text + fragment)
    print("appended batch2 fragment to", MAIN_C)


def main() -> None:
    OUT.write_text(IMPL.lstrip() + "\n")
    write_disasm()
    append_to_main_c()
    print("wrote", OUT, len(DECLS), "functions")


if __name__ == "__main__":
    main()
