/* path_obstacles.c — AI path obstacle debug rendering.
 *
 * Corresponds to path_smoothing.obj (this TU is the path_obstacles.c
 * translation unit within it). Source path confirmed via __FILE__ assert
 * xref: c:\halo\SOURCE\ai\path_obstacles.c
 *
 * Ported:
 *   FUN_00062960 (0x62960) — path_obstacles_debug_render: iterate the
 *     obstacle-disc array, raycast each disc's point, and draw either a
 *     projected disc (on hit) or a 3D sphere (on miss), tinted by the disc's
 *     owning obstacle index.
 *
 * Key layout (obstacles record):
 *   +0x00  int16  obstacle_count
 *   +0x02  int16  disc_count            (both reloaded each iteration)
 * Per-disc record (stride 0x18, base = obstacles + disc_index*0x18):
 *   +0x0a  int16  obstacle_index
 *   +0x10  float  point.x
 *   +0x14  float  point.y
 *   +0x18  float  radius
 *   +0x1c  float  point.z
 * MAXIMUM_DISC_COUNT = 0x80.
 *
 * Globals:
 *   0x2533c0  float  zero/threshold constant (radius > this => extra draw)
 *   0x25eeac  float  ray-direction Z scale factor
 *   0x2c8fb8  color table, 0x10-byte entries indexed by obstacle_index
 *             (byte-offset pointer add, NOT float-element indexing).
 */

#include "../../common.h"

/* 0x00062960 — path_obstacles_debug_render
 *
 * Note the hit/miss asymmetry, preserved from the original:
 *   - On raycast HIT, the projected-disc call (FUN_0018a860) receives
 *     &disc->point (pfVar1, pointing into the obstacles buffer, where the
 *     three contiguous floats are x, y, radius — z lives at +0x1c and is not
 *     part of that view; the disc renderer only uses x/y + the plane).
 *   - On raycast MISS, the sphere call (FUN_00189540) receives the local
 *     {x,y,z} point copy, which reads z from disc+0x1c.
 */
void path_obstacles_debug_render(void *obstacles, float radius)
{
  short disc_index;
  short
    count; /* reused: disc_count, then disc->obstacle_index (matches orig) */
  int disc_off;
  float *disc_point;
  bool hit;
  short collision_result[18]; /* 36-byte buffer for FUN_0014df70 */
  float plane_scratch[11]; /* scratch/output buffer for FUN_0018a860 */
  float ray_dir[3]; /* {0, 0, dir.z} */
  float point[3]; /* contiguous {x, y, z} */

  count = *(short *)((char *)obstacles + 2); /* disc_count */
  disc_index = 0;
  if (0 < count) {
    do {
      if ((disc_index < 0) || (count <= disc_index) || (0x80 < count)) {
        display_assert("disc_index>=0 && disc_index<obstacles->disc_count && "
                       "obstacles->disc_count<=MAXIMUM_DISC_COUNT",
                       "c:\\halo\\source\\ai\\path.h", 0x18c, true);
        system_exit(-1);
      }
      disc_off = disc_index * 0x18;
      count =
        *(short *)((char *)obstacles + disc_off + 10); /* obstacle_index */
      if ((count < 0) || (*(short *)obstacles <= count)) {
        display_assert("disc->obstacle_index>=0 && "
                       "disc->obstacle_index<obstacles->obstacle_count",
                       "c:\\halo\\SOURCE\\ai\\path_obstacles.c", 0x211, true);
        system_exit(-1);
      }
      point[1] = *(float *)((char *)obstacles + disc_off + 0x14); /* y */
      point[0] = *(float *)((char *)obstacles + disc_off + 0x10); /* x */
      point[2] = *(float *)((char *)obstacles + disc_off + 0x1c); /* z */
      disc_point = (float *)((char *)obstacles + disc_off + 0x10);
      ray_dir[2] = (radius + *(float *)((char *)obstacles + disc_off + 0x18)) *
                   *(float *)0x25eeac;
      ray_dir[0] = 0.0f;
      ray_dir[1] = 0.0f;
      hit = FUN_0014df70(0x21, point, ray_dir, -1, collision_result);
      if (hit) {
        FUN_0018a860(1, plane_scratch, 2, 1, disc_point,
                     *(float *)((char *)obstacles + disc_off + 0x18),
                     (char *)0x2c8fb8 +
                       *(short *)((char *)obstacles + disc_off + 10) * 0x10,
                     0.015625f);
        if (*(float *)0x2533c0 < radius) {
          FUN_0018a860(1, plane_scratch, 2, 1, disc_point,
                       radius + *(float *)((char *)obstacles + disc_off + 0x18),
                       (char *)0x2c8fb8 +
                         *(short *)((char *)obstacles + disc_off + 10) * 0x10,
                       0.015625f);
        }
      } else {
        FUN_00189540(1, point, *(float *)((char *)obstacles + disc_off + 0x18),
                     (char *)0x2c8fb8 +
                       *(short *)((char *)obstacles + disc_off + 10) * 0x10);
        if (*(float *)0x2533c0 < radius) {
          FUN_00189540(1, point,
                       radius + *(float *)((char *)obstacles + disc_off + 0x18),
                       (char *)0x2c8fb8 +
                         *(short *)((char *)obstacles + disc_off + 10) * 0x10);
        }
      }
      count = *(short *)((char *)obstacles + 2); /* reload disc_count */
      disc_index = disc_index + 1;
    } while (disc_index < count);
  }
  return;
}

/* 0x00063710 — structure_test_ray2d  (TU:
 * c:\halo\SOURCE\ai\path_structure_bsp.c)
 *
 * March a 2D line query through the structure-bsp surface set, skipping
 * surfaces flagged in the per-surface skip byte-array and (unless
 * ignore_breakable) surfaces whose breakable bit is set in the runtime
 * breakable bitmap. Returns true (1) if the line is blocked by a surface
 * within the query, writing the hit into out_result as
 * {float t; int surface_index; int leaf/pass}; returns false (0) on miss,
 * writing {t, surface_index, -1}.
 *
 * ABI (cdecl, all stack params; returns bool in AL):
 *   +0x08 structure_bsp     (uses +0xb0 surface tag_block, +0x1e8 skip-flag
 * ptr) +0x0c ignore_breakable  (nonzero => skip the breakable test) +0x10 point
 * (forwarded to collision_surface_test_line2d) +0x14 surface_index     (initial
 * surf; reused as scratch/out surface index) +0x18 direction (forwarded) +0x1c
 * t                 (LHS of every FCOMP) +0x20 out_result        (3 dwords)
 *
 * out_result layout mirrors the 6-float scratch buffer filled by
 * collision_surface_test_line2d: two records {t, aux, surface_index}, the
 * "enter" record at buf[0..2] and the "exit" record at buf[3..5].
 */
char structure_test_ray2d(void *structure_bsp, char ignore_breakable,
                          float *point, int surface_index, float *direction,
                          float t, void *out_result)
{
  void *bsp_surfaces; /* EDI: surface tag_block element base */
  unsigned int *breakable_bitmap; /* EBX: per-surface breakable dwords */
  char *skip_flags; /* [structure_bsp+0x1e8]: skip byte-array */
  int cur_surf;
  char flagbyte;
  char surf_blocked;
  char *coll_surface;
  volatile unsigned int
    word; /* store/reload shape lever to match original codegen */
  int *out;
  float buf[6]; /* out_result of collision_surface_test_line2d:
                   enter{t,aux,surf}, exit{t,aux,surf} */

  bsp_surfaces = tag_block_get_element((char *)structure_bsp + 0xb0, 0, 0x60);
  breakable_bitmap = (unsigned int *)breakable_surfaces_get_bsp_surface_data();
  skip_flags = *(char **)((char *)structure_bsp + 0x1e8);

  collision_surface_test_line2d((int)bsp_surfaces, surface_index, 2, 1, point,
                                direction, buf);

  while (1) {
    /* enter-surface handling (only when the query point is before enter_t) */
    if (t < buf[0]) {
      cur_surf = *(int *)&buf[2]; /* enter surface index */
      flagbyte = skip_flags[cur_surf];
      if (flagbyte != 0) {
        if (ignore_breakable == 0 && flagbyte < 0) {
          coll_surface = (char *)tag_block_get_element(
            (char *)bsp_surfaces + 0x3c, cur_surf, 0xc);
          if ((coll_surface[8] & 8) == 0) {
            display_assert("TEST_FLAG(collision_surface->flags, "
                           "_collision_surface_breakable_bit)",
                           "c:\\halo\\SOURCE\\ai\\path_structure_bsp.c", 0x69,
                           true);
            system_exit(-1);
          }
          word = (unsigned char)coll_surface[9];
          surf_blocked =
            (breakable_bitmap[word >> 5] & (1u << (word & 0x1f))) != 0;
          if (surf_blocked == 0)
            goto exit_check; /* breakable & broken => not blocking here */
          cur_surf = *(int *)&buf[2];
        }
        if (cur_surf != -1)
          goto march;
      }
    }

  exit_check:
    /* exit-surface handling; writeout when the query point is at/before exit_t
     */
    if (t <= buf[3])
      break;
    cur_surf = *(int *)&buf[5]; /* exit surface index */
    flagbyte = skip_flags[cur_surf];
    if (flagbyte == 0)
      break;
    if (ignore_breakable == 0 && flagbyte < 0) {
      coll_surface = (char *)tag_block_get_element((char *)bsp_surfaces + 0x3c,
                                                   cur_surf, 0xc);
      if ((coll_surface[8] & 8) == 0) {
        display_assert("TEST_FLAG(collision_surface->flags, "
                       "_collision_surface_breakable_bit)",
                       "c:\\halo\\SOURCE\\ai\\path_structure_bsp.c", 0x7e,
                       true);
        system_exit(-1);
      }
      word = (unsigned char)coll_surface[9];
      surf_blocked = (breakable_bitmap[word >> 5] & (1u << (word & 0x1f))) != 0;
      if (surf_blocked == 0)
        break;
      cur_surf = *(int *)&buf[5];
    }
    if (cur_surf == -1)
      break;

  march:
    surface_index = cur_surf;
    collision_surface_test_line2d((int)bsp_surfaces, cur_surf, 2, 1, point,
                                  direction, buf);
  }

  /* writeout (0x63890) */
  out = (int *)out_result;
  if (t < buf[0]) { /* Path A: blocked at enter surface */
    *(float *)out = buf[0];
    out[1] = surface_index;
    out[2] = *(int *)&buf[1];
    return 1;
  }
  out[1] = surface_index;
  if (t <= buf[3]) { /* Path C: miss */
    out[2] = -1;
    *(float *)out = t;
    return 0;
  }
  /* Path B: blocked at exit surface */
  *(float *)out = buf[3];
  out[2] = *(int *)&buf[4];
  return 1;
}

/* 0x000638f0 — path_smoothing surface-height coplanarity test.
 *
 * Projects `point` onto two collision surfaces (surf_a, surf_b) of the
 * structure-BSP block at def+0xB0 and compares the projected height
 * (third component of each projection output). Returns false when either
 * surface index is -1, or when the two heights differ by less than the
 * global tolerance (i.e. the two projections are coplanar/close enough);
 * returns true when the height difference exceeds the tolerance.
 *
 * ABI (disasm): 4 cdecl stack args, BYTE-BOOL return in AL. Default AL=0;
 * MOV AL,1 only on the fall-through where ABS(diff) is NOT < threshold.
 *
 * Projection-output-size (§5): collision_surface_project_point2d writes 3
 * floats to out_point (Ghidra sized the buffers float[2] — wrong). The two
 * output buffers are contiguous in the 0x18-byte frame; the compare reads
 * the THIRD component of each (out1[2] @ EBP-0x4, out2[2] @ EBP-0x10).
 *
 * Threshold at 0x25f0c8 is a DOUBLE (FCOMP double ptr): the x87 ABS of the
 * float difference is promoted to double for the compare. */
bool FUN_000638f0(int def, float *point, int surf_a, int surf_b)
{
  void *block_elem;
  float out1[3];
  float out2[3];

  block_elem = tag_block_get_element((void *)(def + 0xb0), 0, 0x60);
  if ((surf_a != -1) && (surf_b != -1)) {
    collision_surface_project_point2d((int)block_elem, surf_a, 2, 1, point,
                                      out1);
    collision_surface_project_point2d((int)block_elem, surf_b, 2, 1, point,
                                      out2);
    if (fabs(out1[2] - out2[2]) < *(double *)0x25f0c8)
      return 0;
    return 1;
  }
  return 0;
}

/*
 * FUN_00063970 (0x63970) — interval/segment clamp.
 * Clamps hi upward to *a and lo downward to *b, then collapses one endpoint:
 * compares the two gaps (*b - hi) vs (lo - *a) and moves only the
 * smaller-shortfall side. Returns 1 when the clamp left the interval
 * inverted/empty (*a > *b), else 0.
 * (Tail at 0x639c2: FCOMP *a,*b; TEST AH,0x41; JNE -> XOR EAX,EAX (return 0);
 *  fall-through -> MOV EAX,1 (return 1). So EAX = (*a > *b) ? 1 : 0.)
 * cdecl, 4 stack args, BOOL return in EAX (Ghidra misread this as void(void)).
 *
 * Shape notes (delinked 00063970.obj):
 *  - Both clamps are TERNARIES with both-arm assignment: the hi clamp's else
 *    arm is a literal self-store (MOV ECX,[EBP+0x14]; MOV [EBP+0x14],ECX) and
 *    the taken arm copies the float via integer MOV EAX. Spelling them as
 *    ternaries (not `if`) reproduces this under VC71; clang folds them to
 *    selects (same semantics, both predicates false on NaN). VC71 store-merges
 *    our hi-clamp arms (3-insn ceiling vs the original's distinct-arm copies;
 *    the self-assign spelling that would split them is clang-hostile).
 *  - The lo/min select stays ST-resident (FLD lo/FLD *b straight into the
 *    gap compare) — t_lo is a single-assignment non-volatile local.
 *  - Gap compare: FCOMPP; TEST AH,0x5; JP => (*b - hi) <= (t_lo - *a) takes
 *    the *b = t_lo path (NaN also lands there). Equivalence-verified 100/100
 *    (unicorn, high confidence) on this predicate orientation.
 */
int FUN_00063970(float *a, float *b, float lo, float hi)
{
  float t_lo;

  hi = (*a > hi) ? *a : hi;
  t_lo = (lo > *b) ? *b : lo;
  if (*b - hi > t_lo - *a)
    *a = hi;
  else
    *b = t_lo;
  return (*a > *b) ? 1 : 0;
}
/* --- path_smoothing.obj hand ports (2026-07-26) --- */

static float path_dot2d(const float *a, const float *b)
{
  return a[0] * b[0] + a[1] * b[1];
}

static void path_normalize2d(float *v)
{
  float len_sq;

  len_sq = v[0] * v[0] + v[1] * v[1];
  if (fabs(len_sq) >= *(double *)0x2533d0) {
    float inv = 1.0f / sqrtf(len_sq);
    v[0] *= inv;
    v[1] *= inv;
  }
}

static char path_surface_breakable_is_blocking(void *bsp_block, int surf_index,
                                               unsigned int *breakable_bitmap,
                                               char path_surface_flag)
{
  char *coll_surface;
  unsigned int word;

  if (path_surface_flag != 0)
    return 0;
  coll_surface = (char *)tag_block_get_element((char *)bsp_block + 0x3c,
                                               surf_index, 0xc);
  if ((coll_surface[8] & 8) == 0) {
    display_assert("TEST_FLAG(collision_surface->flags, "
                   "_collision_surface_breakable_bit)",
                   "c:\\halo\\SOURCE\\ai\\path_smoothing.c", 0x1e2, 1);
    system_exit(-1);
  }
  word = (unsigned char)coll_surface[9];
  return (breakable_bitmap[word >> 5] & (1u << (word & 0x1f))) != 0;
}

/* 0x62ba0 — offset a 2D point along a segment by scale, pick the best side. */
void FUN_00062ba0(float *point, float *anchor, float scale, char pick_alt,
                  float *out_point)
{
  float delta[2];
  float len_sq;
  float inv_len;
  float along;
  float perp[2];
  float cand_a[2];
  float cand_b[2];
  int use_alt;

  delta[0] = point[0] - anchor[0];
  delta[1] = point[1] - anchor[1];
  len_sq = delta[0] * delta[0] + delta[1] * delta[1];
  if (*(float *)0x2533c0 < len_sq) {
    inv_len = scale / sqrtf(len_sq);
    along = scale * scale - inv_len * inv_len;
    if (*(float *)0x2533c0 < along) {
      inv_len = scale / sqrtf(len_sq);
      cand_a[0] = delta[0] * inv_len + anchor[0];
      cand_a[1] = delta[1] * inv_len + anchor[1];
      cand_b[0] = anchor[0] - delta[0] * inv_len;
      cand_b[1] = anchor[1] - delta[1] * inv_len;
      use_alt = pick_alt;
      if (path_dot2d(cand_a, point) < path_dot2d(cand_b, point))
        use_alt = !use_alt;
      out_point[0] = use_alt ? cand_b[0] : cand_a[0];
      out_point[1] = use_alt ? cand_b[1] : cand_a[1];
      return;
    }
  }
  perp[0] = -delta[1];
  perp[1] = delta[0];
  if (path_dot2d(perp, perp) < *(float *)0x2533c0) {
    out_point[0] = *(float *)0x31fc10;
    out_point[1] = *(((float *)0x31fc10) + 1);
    return;
  }
  inv_len = scale / sqrtf(perp[0] * perp[0] + perp[1] * perp[1]);
  out_point[0] = perp[0] * inv_len + anchor[0];
  out_point[1] = perp[1] * inv_len + anchor[1];
}

/* 0x62cf0 — blend two offset points toward a corner. */
void FUN_00062cf0(float *corner, float *packed_b, float *a, float scale,
                  float *out)
{
  float cross;
  float da0;
  float da1;
  float db0;
  float db1;
  float len_a;
  float inv;

  da0 = packed_b[0] - corner[0];
  da1 = packed_b[1] - corner[1];
  db0 = packed_b[2] - corner[0];
  db1 = packed_b[3] - corner[1];
  cross = da0 * db1 - da1 * db0;
  if (fabs(cross) >= *(double *)0x2533d0) {
    inv = (scale * scale) / cross;
    out[0] = corner[0] + (da0 - db0) * inv;
    out[1] = corner[1] + (da1 - db1) * inv;
    da0 = out[0] - corner[0];
    da1 = out[1] - corner[1];
    if (da0 * da0 + da1 * da1 > *(float *)0x2533d8 * scale * scale)
      return;
  }
  da0 = a[0] - corner[0];
  da1 = a[1] - corner[1];
  len_a = sqrtf(da0 * da0 + da1 * da1);
  if (fabs(len_a) >= *(double *)0x2533d0) {
    inv = scale / len_a;
    out[0] = da0 * inv + corner[0];
    out[1] = da1 * inv + corner[1];
    if (*(float *)0x2533c0 < len_a)
      return;
  }
  out[0] = *(float *)0x31fc10;
  out[1] = *(((float *)0x31fc10) + 1);
}

/* 0x62e10 — pick the better turning point between two candidates. */
char FUN_00062e10(float *work, float *prev_step, float *next_step,
                  float *turn_a, float *turn_b, float *out)
{
  float v_wp[2];
  float v_np[2];
  float v_nx[2];
  float v_wa[2];
  float v_na[2];
  float v_nb[2];
  float sum_a;
  float sum_b;

  v_wp[0] = work[0] - prev_step[0];
  v_wp[1] = work[1] - prev_step[1];
  path_normalize2d(v_wp);
  v_np[0] = next_step[0] - prev_step[0];
  v_np[1] = next_step[1] - prev_step[1];
  path_normalize2d(v_np);
  v_nx[0] = next_step[0] - prev_step[0];
  v_nx[1] = next_step[1] - prev_step[1];
  path_normalize2d(v_nx);
  v_wa[0] = work[0] - turn_a[0];
  v_wa[1] = work[1] - turn_a[1];
  path_normalize2d(v_wa);
  v_na[0] = next_step[0] - turn_a[0];
  v_na[1] = next_step[1] - turn_a[1];
  path_normalize2d(v_na);
  v_nb[0] = next_step[0] - turn_b[0];
  v_nb[1] = next_step[1] - turn_b[1];
  path_normalize2d(v_nb);

  sum_a = path_dot2d(v_nx, v_np) + path_dot2d(v_wp, v_np);
  sum_b = path_dot2d(v_nb, v_na) + path_dot2d(v_wa, v_na);
  if (-sum_b > sum_a) {
    out[0] = turn_a[0];
    out[1] = turn_a[1];
    return 1;
  }
  out[0] = turn_b[0];
  out[1] = turn_b[1];
  return 0;
}

/* 0x63030 — walk adjacent structure surfaces to find a turning point. */
char find_turning_point(void *scenario, float *point, float scale,
                        int *surface_index, unsigned char expected_side,
                        unsigned char path_surface_flag, float *out_point)
{
  void *bsp_block;
  unsigned int *breakable_bitmap;
  char *skip_flags;
  float neg_scale;
  float dir[2];
  float edge0[2];
  float edge1[2];
  int start_surf;
  int cur_surf;
  int prev_surf;
  int next_surf;
  int *surf_def;
  char *edges_base;
  int edge_slot;
  char surf_side;
  char blocked;
  char cl;
  int coll_idx;
  char *coll;

  bsp_block = tag_block_get_element((char *)scenario + 0xb0, 0, 0x60);
  skip_flags = *(char **)((char *)scenario + 0x1e8);
  breakable_bitmap = (unsigned int *)breakable_surfaces_get_bsp_surface_data();
  edges_base = (char *)bsp_block + 0x54;

  if (expected_side != 0 && expected_side != 1) {
    display_assert("expected_side==0 || expected_side==1",
                   "c:\\halo\\SOURCE\\ai\\path_smoothing.c", 0x1ff, 1);
    system_exit(-1);
  }

  neg_scale = -scale;
  start_surf = *surface_index;
  cur_surf = start_surf;
  prev_surf = -1;

  for (;;) {
    float *edge_a;
    float *edge_b;
    float test_back[2];

    surf_def = (int *)tag_block_get_element((char *)bsp_block + 0x48, cur_surf,
                                            0x18);
    edge_a = (float *)tag_block_get_element(edges_base, surf_def[4], 0x10);
    edge_b = (float *)tag_block_get_element(edges_base, surf_def[5], 0x10);
    dir[0] = edge_b[0] - edge_a[0];
    dir[1] = edge_b[1] - edge_a[1];
    path_normalize2d(dir);
    test_back[0] = neg_scale * dir[0] + point[0];
    test_back[1] = neg_scale * dir[1] + point[1];

    next_surf = -1;
    cl = 0;

    for (;;) {
      if (next_surf == start_surf)
        goto turning_success;
      if (next_surf == prev_surf)
        return 0;
      if (next_surf != -1) {
        prev_surf = cur_surf;
        cur_surf = next_surf;
        break;
      }

      edge_slot = (cur_surf == surf_def[1]) ? 1 : 0;
      coll_idx = surf_def[4 + edge_slot];
      coll = (char *)tag_block_get_element((char *)bsp_block + 0x3c, coll_idx,
                                           0xc);
      surf_side = (char)((coll[0] >> 6) & 1);
      blocked = 0;
      if (path_surface_flag == 0 && surf_side != 0 && skip_flags[coll_idx] < 0)
        blocked = path_surface_breakable_is_blocking(bsp_block, coll_idx,
                                                     breakable_bitmap,
                                                     path_surface_flag);
      if (blocked == 0 && surf_side == (char)expected_side) {
        next_surf = surf_def[edge_slot];
        if (next_surf == start_surf)
          goto turning_success;
        prev_surf = cur_surf;
        cur_surf = next_surf;
        break;
      }

      edge0[0] = edge_a[0] - test_back[0];
      edge0[1] = edge_a[1] - test_back[1];
      if (*(float *)0x2533c0 <= edge0[0] * dir[1] - edge0[1] * dir[0])
        cl = 1;
      edge1[0] = edge_a[0] - (dir[0] * scale + point[0]);
      edge1[1] = edge_a[1] - (dir[1] * scale + point[1]);
      if (*(float *)0x2533c0 <= edge1[0] * (-dir[1]) - edge1[1] * (-dir[0]))
        cl = 1;
      if (prev_surf == -1)
        cl = 1;

      next_surf = surf_def[1 + ((cl != (char)expected_side) ? 0 : -1)];
      if (cl == (char)expected_side) {
        *surface_index = next_surf;
        prev_surf = cur_surf;
        cur_surf = next_surf;
        break;
      }

      surf_def = (int *)tag_block_get_element((char *)bsp_block + 0x48,
                                              next_surf, 0x18);
      if (surf_def[0] != cur_surf && surf_def[1] != cur_surf) {
        display_assert("adjacent_surface->surface_index==current_surface || "
                       "adjacent_surface->surface_index==next_surface",
                       "c:\\halo\\SOURCE\\ai\\path_smoothing.c", 0x277, 1);
        system_exit(-1);
      }
      cur_surf = next_surf;
    }
  }

turning_success:
  {
    float *vert = (float *)tag_block_get_element(edges_base, cur_surf, 0x10);
    out_point[0] = vert[0];
    out_point[1] = vert[1];
    *surface_index = cur_surf;
    return 1;
  }
}

/* 0x633b0 — smooth path steps around structure corners. */
char FUN_000633b0(unsigned int param_1, int param_2, void *param_3,
                  int *param_4, void *param_5, char *param_6)
{
  char *path;
  int16_t input_count;
  char *input_steps;
  int16_t *out_count;
  char *out_steps;
  char *all_nodes_flag;
  void *scenario;
  int16_t segment_index;
  int16_t out_index;
  int16_t scan_index;
  char success;
  char visible_run;
  int16_t visible_start;
  float ref_point[3];
  float turn_a[2];
  float turn_b[2];
  float work[2];
  float corner[2];
  float offset_a[2];
  float offset_b[2];
  float packed_b[4];
  float smooth[2];
  float step_point[3];
  float proj_in[3];
  int surface_index;
  char pick_alt;
  char turn_ok_a;
  char turn_ok_b;
  char geom_ok;
  void *bsp_elem;
  unsigned int vis_scratch[0x78 / 4];
  char *out_slot;

  path = (char *)(uintptr_t)param_1;
  input_count = (int16_t)param_2;
  input_steps = (char *)param_3;
  out_count = (int16_t *)param_4;
  out_steps = (char *)param_5;
  all_nodes_flag = param_6;

  if (input_count <= 0) {
    display_assert("input_step_count>0", "c:\\halo\\SOURCE\\ai\\path_smoothing.c",
                   0x21, 1);
    system_exit(-1);
  }
  if (input_steps == NULL) {
    display_assert("input_steps", "c:\\halo\\SOURCE\\ai\\path_smoothing.c", 0x22,
                   1);
    system_exit(-1);
  }
  if (out_count == NULL) {
    display_assert("output_step_count",
                   "c:\\halo\\SOURCE\\ai\\path_smoothing.c", 0x23, 1);
    system_exit(-1);
  }
  if (out_steps == NULL) {
    display_assert("output_steps", "c:\\halo\\SOURCE\\ai\\path_smoothing.c",
                   0x24, 1);
    system_exit(-1);
  }
  if (all_nodes_flag == NULL) {
    display_assert("all_nodes", "c:\\halo\\SOURCE\\ai\\path_smoothing.c", 0x25,
                   1);
    system_exit(-1);
  }

  if (input_count == 1) {
    *out_count = 1;
    csmemcpy(out_steps, input_steps, 0x10);
    return 1;
  }

  scenario = *(void **)(path + 0x64);
  ref_point[0] = *(float *)(path + 0x14);
  ref_point[1] = *(float *)(path + 0x18);
  ref_point[2] = *(float *)(path + 0x20);
  segment_index = 0;
  out_index = 0;
  success = 0;

  while (segment_index < input_count) {
    visible_run = 0;
    visible_start = -1;
    scan_index = segment_index;

    while (scan_index < input_count) {
      char *step = input_steps + scan_index * 0x10;
      char vis;

      vis = FUN_00063e90((int)scenario, *(unsigned char *)(path + 4), ref_point,
                         -1, (float *)(step + 4), 1, 0.2f, 0, vis_scratch);
      if (vis) {
        if (!visible_run) {
          visible_start = scan_index;
          visible_run = 1;
        }
      } else if (visible_run) {
        visible_run = 0;
        visible_start = -1;
      }
      scan_index++;
    }

    if (!visible_run || visible_start == -1) {
      segment_index = input_count;
      break;
    }

    surface_index = *(int *)(input_steps + visible_start * 0x10);
    turn_ok_a =
        find_turning_point(scenario, ref_point, 0.2f, &surface_index, 1,
                           *(unsigned char *)(path + 4), turn_a);
    turn_ok_b =
        find_turning_point(scenario, ref_point, 0.2f, &surface_index, 0,
                           *(unsigned char *)(path + 4), turn_b);
    if (!turn_ok_a || !turn_ok_b)
      break;

    work[0] = ref_point[0];
    work[1] = ref_point[1];
    geom_ok = FUN_00062e10(
        work, (float *)(input_steps + visible_start * 0x10 + 4),
        (float *)(input_steps + visible_start * 0x10 - 0xc), turn_a, turn_b,
        corner);
    pick_alt = geom_ok ? 0 : 1;
    FUN_00062ba0((float *)(input_steps + visible_start * 0x10 + 4), turn_a,
                 0.35f, pick_alt, offset_a);
    FUN_00062ba0((float *)(input_steps + visible_start * 0x10 + 4), turn_b,
                 0.35f, pick_alt, offset_b);
    packed_b[0] = offset_a[0];
    packed_b[1] = offset_a[1];
    packed_b[2] = offset_b[0];
    packed_b[3] = offset_b[1];
    FUN_00062cf0(corner, packed_b, offset_a, 0.35f, smooth);

    ref_point[0] = smooth[0];
    ref_point[1] = smooth[1];
    proj_in[0] = smooth[0];
    proj_in[1] = smooth[1];
    proj_in[2] = ref_point[2];
    surface_index = FUN_00063e30((int)scenario, *(unsigned char *)(path + 4),
                                 proj_in, surface_index, ref_point);

    if (out_index >= 4)
      break;

    out_slot = out_steps + out_index * 0x10;
    step_point[0] = smooth[0];
    step_point[1] = smooth[1];
    step_point[2] = ref_point[2];
    bsp_elem = tag_block_get_element((char *)scenario + 0xb0, 0, 0x60);
    collision_surface_project_point2d((int)bsp_elem, surface_index, 2, 1,
                                      step_point, (float *)(out_slot + 4));
    *(int *)out_slot = surface_index;
    out_index++;
    segment_index = visible_start;
  }

  if (out_index < input_count) {
    int16_t copy_index;
    char *tail_in;
    char *tail_out;

    tail_in = input_steps + (input_count - 1) * 0x10;
    copy_index = out_index;
    while (copy_index < input_count) {
      tail_out = out_steps + copy_index * 0x10;
      csmemcpy(tail_out, tail_in - (input_count - 1 - copy_index) * 0x10,
               0x10);
      copy_index++;
    }
    out_index = input_count;
    success = 1;
  }

  *out_count = out_index;
  if (!success)
    *all_nodes_flag = 0;
  return success;
}

/* FUN_00062b20 (0x62b20) — XBE naked draft (batch 151). */
#if defined(__clang__)
static void *(*const b62b20_elem)(void *, int, int) = tag_block_get_element;
static void (*const b62b20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b62b20_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_00062b20(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movb (%%eax,%%edx,1), %%cl\n\t"
      "movb %%cl, %%al\n\t"
      "shrb $6, %%al\n\t"
      "andb $1, %%al\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_00062b20_2\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00062b20_2\n\t"
      "testb %%cl, %%cl\n\t"
      "jns .LFUN_00062b20_2\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl $0xc\n\t"
      "pushl %%edx\n\t"
      "addl $0x3c, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x8(%%esi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $8, %%al\n\t"
      "jne .LFUN_00062b20_1\n\t"
      "pushl $1\n\t"
      "pushl $0x1e2\n\t"
      "pushl $0x25ef48\n\t"
      "pushl $0x25ef00\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00062b20_1:\n\t"
      "movzbl 0x9(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "shrl $5, %%eax\n\t"
      "testl %%edx, (%%ecx,%%eax,4)\n\t"
      "setne %%al\n\t"
      "popl %%esi\n\t"
      ".LFUN_00062b20_2:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b62b20_elem), [assert] "m"(b62b20_assert), [exitfn] "m"(b62b20_exitfn)
      : "memory");
}
#else
#error "FUN_00062b20: clang naked draft required"
#endif


/* 0x639e0 — march structure BSP surfaces between two points. */
char FUN_000639e0(int scenario, unsigned char bsp_idx, float *origin,
                  int start_surface, float *target, int end_surface,
                  char *result_buf)
{
  void *bsp_block;
  char *skip_flags;
  unsigned int *breakable_bitmap;
  float delta[2];
  float accum[3];
  float edge_vec[2];
  float proj_in[2];
  float proj_out[3];
  int cur_surface;
  int walk_surface;
  int coll_target;
  int *surf_def;
  char *coll_rec;
  int16_t step_count;
  char edge_clear;
  char target_edge;
  char recurse;
  int side_idx;
  int next_surface;
  float cross;
  float t_param;

  if (result_buf == NULL) {
    display_assert("result", "c:\\halo\\SOURCE\\ai\\path_smoothing.c", 0xd9, 0);
    system_exit(-1);
  }

  bsp_block = tag_block_get_element((char *)scenario + 0xb0, 0, 0x60);
  skip_flags = *(char **)((char *)scenario + 0x1e8);
  breakable_bitmap = (unsigned int *)breakable_surfaces_get_bsp_surface_data();

  delta[0] = target[0] - origin[0];
  delta[1] = target[1] - origin[1];

  accum[0] = *(float *)0x31fc1c;
  accum[1] = *(((float *)0x31fc1c) + 1);
  accum[2] = *(((float *)0x31fc1c) + 2);

  cur_surface = start_surface;
  walk_surface = start_surface;
  step_count = 0;
  edge_clear = 0;
  target_edge = 0;
  recurse = 0;

  coll_rec = (char *)tag_block_get_element((char *)bsp_block + 0x3c, cur_surface,
                                           0xc);
  walk_surface = *(int *)(coll_rec + 4);

  for (;;) {
    float *edge_a;
    float *edge_b;
    float *far_edge;
    char breakable_side;
    char blocked;

    surf_def = (int *)tag_block_get_element((char *)bsp_block + 0x48,
                                            walk_surface, 0x18);
    side_idx = (cur_surface == surf_def[5]) ? 1 : 0;
    edge_a = (float *)tag_block_get_element((char *)bsp_block + 0x54,
                                            surf_def[4 + side_idx], 0x10);
    far_edge = (float *)tag_block_get_element((char *)bsp_block + 0x54,
                                              surf_def[4 + (1 - side_idx)], 0x10);
    edge_b = far_edge;

    edge_vec[0] = edge_b[0] - edge_a[0];
    edge_vec[1] = edge_b[1] - edge_a[1];

    if (*(int *)((char *)surf_def + side_idx * 4 + 0x10) == end_surface)
      target_edge = 1;

    accum[0] += edge_a[0];
    accum[1] += edge_a[1];
    accum[2] += edge_a[2];
    step_count++;

    cross = edge_vec[0] * delta[1] - edge_vec[1] * delta[0];
    if (*(float *)0x2533c0 < cross)
      edge_clear = 1;

    edge_vec[0] = target[0] - edge_a[0];
    edge_vec[1] = target[1] - edge_a[1];
    if (edge_vec[0] * delta[1] - edge_vec[1] * delta[0] >= *(float *)0x2533c0)
      edge_clear = 1;

    edge_vec[0] = origin[0] - edge_a[0];
    edge_vec[1] = origin[1] - edge_a[1];
    if (edge_vec[0] * delta[1] - edge_vec[1] * delta[0] >= *(float *)0x2533c0)
      edge_clear = 1;

    if (*(float *)0x2533c0 < cross) {
      next_surface = *(int *)((char *)surf_def + side_idx * 4 + 8);
      coll_rec = (char *)tag_block_get_element((char *)bsp_block + 0x3c,
                                               walk_surface, 0xc);
      coll_target = *(int *)(coll_rec + 4);
      if (next_surface == coll_target)
        break;
      walk_surface = next_surface;
      continue;
    }

    next_surface = surf_def[4 + (side_idx ^ 1)];
    blocked = 0;
    if (bsp_idx == 0) {
      char flagbyte = skip_flags[next_surface];
      coll_rec = (char *)tag_block_get_element((char *)bsp_block + 0x3c,
                                               next_surface, 0xc);
      breakable_side = (coll_rec[0] >> 6) & 1;
      if (breakable_side && flagbyte < 0)
        blocked = path_surface_breakable_is_blocking(bsp_block, next_surface,
                                                     breakable_bitmap, 0);
    }
    if (!blocked)
      goto project_hit;

    cur_surface = next_surface;
    walk_surface = cur_surface;
    coll_rec = (char *)tag_block_get_element((char *)bsp_block + 0x3c,
                                             cur_surface, 0xc);
    walk_surface = *(int *)(coll_rec + 4);

    if (!recurse && cur_surface >= 0 &&
        cur_surface < *(int *)((char *)scenario + 0x1e4) &&
        skip_flags[cur_surface] != 0) {
      char sub_result[0x70];
      if (!FUN_000639e0(scenario, bsp_idx, accum, cur_surface, target, -1,
                        sub_result)) {
        cur_surface = *(int *)(sub_result + 0x10);
        recurse = 1;
        walk_surface = cur_surface;
        coll_rec = (char *)tag_block_get_element((char *)bsp_block + 0x3c,
                                                 cur_surface, 0xc);
        walk_surface = *(int *)(coll_rec + 4);
      }
    }
    if (step_count > 0x200)
      break;
  }

  if (edge_clear) {
    if (cur_surface < 0 ||
        cur_surface >= *(int *)((char *)scenario + 0x1e4)) {
      display_assert("current_surface>=0 && "
                     "current_surface<scenario->structure_bsp.surface_count",
                     "c:\\halo\\SOURCE\\ai\\path_smoothing.c", 0x13c, 0);
      system_exit(-1);
    }
    t_param = (float)step_count;
    t_param = 1.0f / t_param;
    accum[0] *= t_param;
    accum[1] *= t_param;
    if (!recurse) {
      if (skip_flags[cur_surface] == 0)
        goto write_fail;
    }
    proj_in[0] = accum[0];
    proj_in[1] = accum[1];
    collision_surface_project_point2d((int)bsp_block, cur_surface, 2, 1, proj_in,
                                      proj_out);
    *(float *)(result_buf + 4) = proj_out[0];
    *(float *)(result_buf + 8) = proj_out[1];
    *(int *)(result_buf + 0x10) = cur_surface;
    *(int *)(result_buf + 0x14) = end_surface;
    result_buf[0] = 1;
    *(float *)(result_buf + 0x18) = t_param;
    return 1;
  }

  if (cur_surface != end_surface && !target_edge && end_surface != -1)
    goto write_partial;

write_fail:
  collision_surface_project_point2d((int)bsp_block, cur_surface, 2, 1, origin,
                                    proj_out);
  *(int *)(result_buf + 0x10) = cur_surface;
  *(int *)(result_buf + 0x14) = -1;
  result_buf[0] = 0;
  *(float *)(result_buf + 0x18) = 1.0f;
  return 0;

write_partial:
  collision_surface_project_point2d((int)bsp_block, end_surface, 2, 1, target,
                                    proj_out);
  *(int *)(result_buf + 0x10) = -1;
  *(int *)(result_buf + 0x14) = -1;
  result_buf[0] = 1;
  *(float *)(result_buf + 0x18) = 0.0f;
  return 1;

project_hit:
  cross = edge_vec[1] * delta[0] - edge_vec[0] * delta[1];
  t_param = sqrtf(delta[0] * edge_vec[0] + delta[1] * edge_vec[1]);
  if (*(float *)0x2533c0 < t_param) {
    float denom = edge_vec[0] * edge_vec[0] + edge_vec[1] * edge_vec[1];
    float scale = *(float *)0x25f0d0;
    if (*(float *)0x2533c0 < denom) {
      t_param = (sqrtf(denom) * scale - t_param) / cross;
      proj_in[0] = delta[0] * t_param + origin[0];
      proj_in[1] = delta[1] * t_param + origin[1];
      collision_surface_project_point2d((int)bsp_block, next_surface, 2, 1,
                                        proj_in, proj_out);
      *(float *)(result_buf + 4) = proj_out[0];
      *(float *)(result_buf + 8) = proj_out[1];
      *(int *)(result_buf + 0x10) = next_surface;
      *(int *)(result_buf + 0x14) = walk_surface;
      result_buf[0] = 1;
      *(float *)(result_buf + 0x18) = t_param;
      return 1;
    }
  }
  goto write_partial;
}
