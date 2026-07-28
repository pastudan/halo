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

__attribute__((unused))
static float path_dot2d(const float *a, const float *b)
{
  return a[0] * b[0] + a[1] * b[1];
}

__attribute__((unused))
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

__attribute__((unused))
static __attribute__((unused)) char path_surface_breakable_is_blocking(void *bsp_block, int surf_index,
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

/* FUN_00062ba0 (0x62ba0) — readable C lift.
 * point@ecx, anchor@esi, out@edi; stack: scale, pick_alt. */
void FUN_00062ba0(float *point, float *anchor, float scale, char pick_alt, float *out_point)
{
  float dx = point[0] - anchor[0];
  float dy = point[1] - anchor[1];
  float len_sq = dx * dx + dy * dy;
  float inv = scale / len_sq;
  float disc = len_sq - scale * scale;
  float root, p0x, p0y, p1x, p1y, ax0, ay0, ax1, ay1, cross;
  int prefer, idx;
  float tmp[3];
  float mag;
  float *def_dir;

  if (disc > *(float *)0x2533c0) {
    root = sqrtf(disc);
    p0x = (dx * scale + dy * root) * inv + anchor[0];
    p0y = (dy * scale - dx * root) * inv + anchor[1];
    p1x = (dx * scale - dy * root) * inv + anchor[0];
    p1y = (dy * scale + dx * root) * inv + anchor[1];
    ax0 = p0x - point[0];
    ay0 = p0y - point[1];
    ax1 = p1x - point[0];
    ay1 = p1y - point[1];
    cross = ay1 * ax0 - ax1 * ay0;
    prefer = (cross > *(float *)0x2533c0) ? 1 : 0;
    idx = (prefer != (unsigned char)pick_alt) ? 1 : 0;
    out_point[0] = idx ? p1x : p0x;
    out_point[1] = idx ? p1y : p0y;
    return;
  }
  tmp[0] = dx;
  tmp[1] = dy;
  tmp[2] = 0.0f;
  mag = magnitude3d(tmp);
  if (!(mag != *(float *)0x2533c0)) {
    def_dir = *(float **)0x31fc10;
    tmp[0] = def_dir[0];
    tmp[1] = def_dir[1];
  }
  out_point[0] = tmp[0] * scale + anchor[0];
  out_point[1] = tmp[1] * scale + anchor[1];
}

/* FUN_00062cf0 (0x62cf0) — readable C lift.
 * corner@edi, packed_b@edx, a@ecx, out@esi; stack: scale. */
void FUN_00062cf0(float *corner, float *packed_b, float *a, float scale, float *out)
{
  float d0, d1, d2, d3;
  float cross;
  float t;
  float ox, oy;
  float dx, dy;
  float dist2;
  float len;
  float inv;
  float *def_dir;

  d0 = packed_b[0] - a[0];
  d1 = packed_b[1] - a[1];
  d2 = packed_b[2] - a[0];
  d3 = packed_b[3] - a[1];
  cross = d3 * d0 - d1 * d2;

  if (fabs((double)cross) >= *(double *)0x2533d0) {
    t = (scale * scale) / cross;
    oy = (d0 - d2) * t + a[1];
    ox = a[0] - (d1 - d3) * t;
    out[0] = ox;
    out[1] = oy;
    dx = ox - a[0];
    dy = oy - a[1];
    dist2 = dx * dx + dy * dy;
    if (!(dist2 < *(float *)0x2533d8 * scale * scale))
      return;
  }

  dx = packed_b[0] - corner[0];
  dy = packed_b[1] - corner[1];
  len = sqrtf(dx * dx + dy * dy);
  if (fabs((double)len) >= *(double *)0x2533d0) {
    inv = *(float *)0x2533c8 / len;
    dx = dx * inv;
    dy = dy * inv;
    out[0] = dx * scale + packed_b[0];
    out[1] = dy * scale + packed_b[1];
    return;
  }
  def_dir = *(float **)0x31fc10;
  dx = def_dir[0];
  dy = def_dir[1];
  out[0] = dx * scale + packed_b[0];
  out[1] = dy * scale + packed_b[1];
}

char FUN_00062e10(float *work, float *prev_step, float *next_step, float *turn_a, float *turn_b, float *out)
{
  float v_wp[2];
  float v_np[2];
  float v_tb_p[2];
  float v_wa[2];
  float v_na[2];
  float v_tb_a[2];
  float sum_a;
  float sum_b;

  v_wp[0] = work[0] - prev_step[0];
  v_wp[1] = work[1] - prev_step[1];
  path_normalize2d(v_wp);
  v_np[0] = next_step[0] - prev_step[0];
  v_np[1] = next_step[1] - prev_step[1];
  path_normalize2d(v_np);
  v_tb_p[0] = turn_b[0] - prev_step[0];
  v_tb_p[1] = turn_b[1] - prev_step[1];
  path_normalize2d(v_tb_p);
  v_wa[0] = work[0] - turn_a[0];
  v_wa[1] = work[1] - turn_a[1];
  path_normalize2d(v_wa);
  v_na[0] = next_step[0] - turn_a[0];
  v_na[1] = next_step[1] - turn_a[1];
  path_normalize2d(v_na);
  v_tb_a[0] = turn_b[0] - turn_a[0];
  v_tb_a[1] = turn_b[1] - turn_a[1];
  path_normalize2d(v_tb_a);

  sum_a = path_dot2d(v_tb_p, v_np) + path_dot2d(v_wp, v_np);
  sum_b = path_dot2d(v_tb_a, v_na) + path_dot2d(v_wa, v_na);
  if (-sum_b > sum_a) {
    out[0] = prev_step[0];
    out[1] = prev_step[1];
    return 1;
  }
  out[0] = turn_a[0];
  out[1] = turn_a[1];
  return 0;
}


/* find_turning_point (0x63030) — XBE naked draft (batch 223). */
#if defined(__clang__)
static void *(*const b63030_elem)(void *, int, int) = tag_block_get_element;
static char * (*const b63030_c1459e0)(void) = breakable_surfaces_get_bsp_surface_data;
static void (*const b63030_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b63030_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
char find_turning_point(void *scenario __attribute__((unused)), float *point __attribute__((unused)), float scale __attribute__((unused)), int *surface_index __attribute__((unused)), unsigned char expected_side __attribute__((unused)), unsigned char path_surface_flag __attribute__((unused)), float *out_point __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x44, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl $0x60\n\t"
      "leal 0xb0(%%esi), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x1e8(%%esi), %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "call *%[c1459e0]\n\t"
      "movb 0x14(%%ebp), %%bl\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "cmpb $1, %%bl\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "movl %%esi, -0x1c(%%ebp)\n\t"
      "je .Lfind_turning_point_1\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lfind_turning_point_1\n\t"
      "pushl $1\n\t"
      "pushl $0x1ff\n\t"
      "pushl $0x25ef48\n\t"
      "pushl $0x25efe0\n\t"
      "call *%[assert]\n\t"
      "pushl %%esi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lfind_turning_point_1:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movzbl %%bl, %%ecx\n\t"
      "fchs\n\t"
      "leal 0x54(%%edi), %%eax\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      ".Lfind_turning_point_2:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl $0x18\n\t"
      "pushl %%edx\n\t"
      "leal 0x48(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movb 0x18(%%ebp), %%dl\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "movb (%%eax,%%ecx,1), %%cl\n\t"
      "movb %%cl, %%bl\n\t"
      "shrb $6, %%bl\n\t"
      "addl $0xc, %%esp\n\t"
      "andb $1, %%bl\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .Lfind_turning_point_4\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lfind_turning_point_4\n\t"
      "testb %%cl, %%cl\n\t"
      "jns .Lfind_turning_point_4\n\t"
      "pushl $0xc\n\t"
      "pushl %%eax\n\t"
      "addl $0x3c, %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movb 0x8(%%edi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $8, %%al\n\t"
      "jne .Lfind_turning_point_3\n\t"
      "pushl $1\n\t"
      "pushl $0x1e2\n\t"
      "pushl $0x25ef48\n\t"
      "pushl $0x25ef00\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lfind_turning_point_3:\n\t"
      "movzbl 0x9(%%edi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "shrl $5, %%eax\n\t"
      "testl %%edx, (%%ecx,%%eax,4)\n\t"
      "setne %%bl\n\t"
      ".Lfind_turning_point_4:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movzbl %%bl, %%edx\n\t"
      "movl (%%esi,%%edx,4), %%eax\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "testb %%bl, %%bl\n\t"
      "sete %%dl\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $0x10\n\t"
      "movl (%%esi,%%edx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "flds (%%eax)\n\t"
      "fsubs (%%edi)\n\t"
      "addl $0x18, %%esp\n\t"
      "flds 0x4(%%eax)\n\t"
      "xorb %%cl, %%cl\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "fsts -0x34(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fchs\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lfind_turning_point_5\n\t"
      "fdivrs 0x2533c8\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      ".byte 0xde, 0xc9\n\t"
      "jmp .Lfind_turning_point_6\n\t"
      ".Lfind_turning_point_5:\n\t"
      "fstp %%st(0)\n\t"
      ".Lfind_turning_point_6:\n\t"
      "flds -0x34(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fadds (%%eax)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fadds 0x4(%%eax)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0x34(%%ebp)\n\t"
      "fadds (%%eax)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fadds 0x4(%%eax)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds (%%edi)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs -0x40(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds (%%edi)\n\t"
      "fsubs -0x3c(%%ebp)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs -0x38(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmul %%st(5), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lfind_turning_point_7\n\t"
      "movl $1, %%eax\n\t"
      "jmp .Lfind_turning_point_8\n\t"
      ".Lfind_turning_point_7:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lfind_turning_point_8:\n\t"
      "movl -0x20(%%ebp), %%edi\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jne .Lfind_turning_point_9\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmul %%st(5), %%st(0)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lfind_turning_point_9\n\t"
      "movb $1, %%cl\n\t"
      ".Lfind_turning_point_9:\n\t"
      "fxch %%st(1)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fxch %%st(1)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jp .Lfind_turning_point_10\n\t"
      "movb $1, %%cl\n\t"
      ".Lfind_turning_point_10:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lfind_turning_point_11\n\t"
      "movb $1, %%cl\n\t"
      ".Lfind_turning_point_11:\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpb %%bl, %%cl\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "setne %%dl\n\t"
      "subl %%edi, %%edx\n\t"
      "negl %%edx\n\t"
      "sbbl %%edx, %%edx\n\t"
      "movl 0x4(%%esi,%%edx,4), %%edi\n\t"
      "incl %%edx\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "movl %%edi, -0x24(%%ebp)\n\t"
      "je .Lfind_turning_point_17\n\t"
      "cmpl %%eax, %%edi\n\t"
      "je .Lfind_turning_point_18\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lfind_turning_point_12\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      ".Lfind_turning_point_12:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      ".Lfind_turning_point_13:\n\t"
      "cmpl 0x4(%%esi), %%edi\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "sete %%al\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testb %%al, %%al\n\t"
      "sete %%bl\n\t"
      "movl 0x10(%%esi,%%ebx,4), %%ecx\n\t"
      "movb (%%ecx,%%edx,1), %%dl\n\t"
      "movb %%dl, %%al\n\t"
      "shrb $6, %%al\n\t"
      "andb $1, %%al\n\t"
      "cmpb $0, 0x18(%%ebp)\n\t"
      "jne .Lfind_turning_point_15\n\t"
      "testb %%al, %%al\n\t"
      "je .Lfind_turning_point_15\n\t"
      "testb %%dl, %%dl\n\t"
      "jns .Lfind_turning_point_15\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl $0xc\n\t"
      "pushl %%ecx\n\t"
      "addl $0x3c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movb 0x8(%%edi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $8, %%al\n\t"
      "jne .Lfind_turning_point_14\n\t"
      "pushl $1\n\t"
      "pushl $0x1e2\n\t"
      "pushl $0x25ef48\n\t"
      "pushl $0x25ef00\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lfind_turning_point_14:\n\t"
      "movzbl 0x9(%%edi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "shrl $5, %%eax\n\t"
      "testl %%edx, (%%ecx,%%eax,4)\n\t"
      "movl -0x24(%%ebp), %%edi\n\t"
      "setne %%al\n\t"
      ".Lfind_turning_point_15:\n\t"
      "cmpb 0x14(%%ebp), %%al\n\t"
      "je .Lfind_turning_point_16\n\t"
      "movl 0x8(%%esi,%%ebx,4), %%ebx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl $0x18\n\t"
      "addl $0x48, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, 0x10(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "je .Lfind_turning_point_18\n\t"
      "cmpl %%edi, (%%esi)\n\t"
      "je .Lfind_turning_point_13\n\t"
      "cmpl %%edi, 0x4(%%esi)\n\t"
      "je .Lfind_turning_point_13\n\t"
      "pushl $1\n\t"
      "pushl $0x277\n\t"
      "pushl $0x25ef48\n\t"
      "pushl $0x25ef70\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lfind_turning_point_13\n\t"
      ".Lfind_turning_point_16:\n\t"
      "movl %%edi, -0x1c(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "jmp .Lfind_turning_point_2\n\t"
      ".Lfind_turning_point_17:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl $0x10\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lfind_turning_point_18:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b63030_elem), [c1459e0] "m"(b63030_c1459e0), [assert] "m"(b63030_assert), [exitfn] "m"(b63030_exitfn)
      : "memory");
}
#else
#error "find_turning_point: clang naked draft required"
#endif


/* FUN_000633b0 (0x633b0) — XBE naked draft (batch 220). */
#if defined(__clang__)
static void (*const b633b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b633b0_exitfn)(int) = system_exit;
static char (*const b633b0_c63e90)(int scenario, unsigned char bsp_idx, float *origin, int node_handle, float *target, int flags, float param_7, int param_8, unsigned int *result) = FUN_00063e90;
static char (*const b633b0_c63030)(void *scenario, float *point, float scale, int *surface_index, unsigned char expected_side, unsigned char path_surface_flag, float *out_point) = find_turning_point;
static char (*const b633b0_c62e10)(float *work, float *prev_step, float *next_step, float *turn_a, float *turn_b, float *out) = FUN_00062e10;
static void (*const b633b0_c62ba0)(float *point, float *anchor, float scale, char pick_alt, float *out_point) = (void *)FUN_00062ba0;
static void (*const b633b0_c62cf0)(float *corner, float *packed_b, float *a, float scale, float *out) = (void *)FUN_00062cf0;
static int (*const b633b0_c63e30)(int scenario, unsigned char bsp_idx, float *origin, int surface_index, float *out_point) = FUN_00063e30;
static void *(*const b633b0_elem)(void *, int, int) = tag_block_get_element;
static int (*const b633b0_c147990)(int bsp, int surface_index, int projection, int sign, float *point, float *out_point) = collision_surface_project_point2d;

__attribute__((naked, noinline))
char FUN_000633b0(unsigned int param_1 __attribute__((unused)), int param_2 __attribute__((unused)), void *param_3 __attribute__((unused)), int *param_4 __attribute__((unused)), void *param_5 __attribute__((unused)), char *param_6 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x78, %%esp\n\t"
      "cmpw $0, 0xc(%%ebp)\n\t"
      "jg .LFUN_000633b0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x21\n\t"
      "pushl $0x25ef48\n\t"
      "pushl $0x25f048\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000633b0_1:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000633b0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x22\n\t"
      "pushl $0x25ef48\n\t"
      "pushl $0x25f03c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000633b0_2:\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .LFUN_000633b0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x23\n\t"
      "pushl $0x25ef48\n\t"
      "pushl $0x25f028\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000633b0_3:\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000633b0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x24\n\t"
      "pushl $0x25ef48\n\t"
      "pushl $0x25f018\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000633b0_4:\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000633b0_5\n\t"
      "pushl $1\n\t"
      "pushl $0x25\n\t"
      "pushl $0x25ef48\n\t"
      "pushl $0x25f004\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000633b0_5:\n\t"
      "movl $1, %%eax\n\t"
      "cmpw %%ax, 0xc(%%ebp)\n\t"
      "jle .LFUN_000633b0_13\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl 0x20(%%esi), %%ecx\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000633b0_6:\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpw 0xc(%%ebp), %%ax\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jge .LFUN_000633b0_11\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jmp .LFUN_000633b0_8\n\t"
      ".LFUN_000633b0_7:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      ".LFUN_000633b0_8:\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal -0x78(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "pushl $0x3e99999a\n\t"
      "pushl %%ecx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x4(%%esi), %%cl\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "movl 0x64(%%esi), %%edx\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c63e90]\n\t"
      "addl $0x24, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000633b0_9\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_000633b0_10\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl -0x64(%%ebp), %%edi\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_000633b0_10\n\t"
      ".LFUN_000633b0_9:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_000633b0_10\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_000633b0_10:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "incl %%eax\n\t"
      "addl $0x10, %%edx\n\t"
      "cmpw 0xc(%%ebp), %%ax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "jl .LFUN_000633b0_7\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_000633b0_11\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_000633b0_11\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0x4(%%esi), %%dl\n\t"
      "leal -0x4c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "pushl $0x3e99999a\n\t"
      "pushl %%eax\n\t"
      "movl 0x64(%%esi), %%eax\n\t"
      "call *%[c63030]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0x4(%%esi), %%dl\n\t"
      "leal -0x44(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movb %%al, %%bl\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl $0x3e99999a\n\t"
      "pushl %%eax\n\t"
      "movl 0x64(%%esi), %%eax\n\t"
      "call *%[c63030]\n\t"
      "addl $0x30, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000633b0_12\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_000633b0_12\n\t"
      "movswl -0xc(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "shll $4, %%ecx\n\t"
      "leal (%%ecx,%%edx,1), %%eax\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x4(%%eax), %%ebx\n\t"
      "leal -0xc(%%eax), %%edx\n\t"
      "leal -0x44(%%ebp), %%edi\n\t"
      "leal -0x4c(%%ebp), %%esi\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "call *%[c62e10]\n\t"
      "movb %%al, -0x1c(%%ebp)\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x3eb33333\n\t"
      "leal -0x5c(%%ebp), %%edi\n\t"
      "leal -0x2c(%%ebp), %%esi\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "call *%[c62ba0]\n\t"
      "movb -0x1c(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "sete %%al\n\t"
      "leal -0x54(%%ebp), %%edi\n\t"
      "leal -0x2c(%%ebp), %%esi\n\t"
      "movl %%ebx, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3eb33333\n\t"
      "call *%[c62ba0]\n\t"
      "pushl $0x3eb33333\n\t"
      "leal -0x34(%%ebp), %%esi\n\t"
      "leal -0x24(%%ebp), %%edi\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "leal -0x5c(%%ebp), %%edx\n\t"
      "call *%[c62cf0]\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0x4(%%eax), %%dl\n\t"
      "movl 0x64(%%eax), %%eax\n\t"
      "movl %%ecx, -0x3c(%%ebp)\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "leal -0x3c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c63e30]\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "movswl %%di, %%esi\n\t"
      "addl $0x2c, %%esp\n\t"
      "shll $4, %%esi\n\t"
      "addl %%ecx, %%esi\n\t"
      "leal 0x4(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x64(%%eax), %%ecx\n\t"
      "pushl $2\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x60\n\t"
      "addl $0xb0, %%ecx\n\t"
      "pushl $0\n\t"
      "incl %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl %%ebx, -0x18(%%ebp)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c147990]\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpw $4, %%di\n\t"
      "movl %%ebx, (%%esi)\n\t"
      "jge .LFUN_000633b0_12\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "jmp .LFUN_000633b0_6\n\t"
      ".LFUN_000633b0_11:\n\t"
      "movswl 0xc(%%ebp), %%edx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "shll $4, %%edx\n\t"
      "leal -0x10(%%edx,%%eax,1), %%ecx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movswl %%ax, %%edx\n\t"
      "shll $4, %%edx\n\t"
      "addl %%esi, %%edx\n\t"
      "movl (%%ecx), %%esi\n\t"
      "movl %%esi, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%esi\n\t"
      "movl %%esi, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%esi\n\t"
      "movl %%esi, 0x8(%%edx)\n\t"
      "movl 0xc(%%ecx), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%ecx, 0xc(%%edx)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_000633b0_12:\n\t"
      "movw -0x8(%%ebp), %%ax\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movw %%ax, (%%edx)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000633b0_14\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $0, (%%ecx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000633b0_13:\n\t"
      "movw %%ax, (%%ebx)\n\t"
      "movl (%%edi), %%edx\n\t"
      "movl %%edx, (%%esi)\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "movl 0x8(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x8(%%esi)\n\t"
      "movl 0xc(%%edi), %%edx\n\t"
      "movl %%edx, 0xc(%%esi)\n\t"
      ".LFUN_000633b0_14:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [assert] "m"(b633b0_assert), [exitfn] "m"(b633b0_exitfn), [c63e90] "m"(b633b0_c63e90), [c63030] "m"(b633b0_c63030), [c62e10] "m"(b633b0_c62e10), [c62ba0] "m"(b633b0_c62ba0), [c62cf0] "m"(b633b0_c62cf0), [c63e30] "m"(b633b0_c63e30), [elem] "m"(b633b0_elem), [c147990] "m"(b633b0_c147990)
      : "memory");
}
#else
#error "FUN_000633b0: clang naked draft required"
#endif


/* FUN_00062b20 (0x62b20) — readable C lift. */
char FUN_00062b20(unsigned char *flag_base, int index, char skip_check, void *block, void *bitvec)
{
  unsigned char flags;
  char bit6;
  void *edge;
  unsigned int key;

  flags = flag_base[index];
  bit6 = (char)((flags >> 6) & 1);
  if (skip_check != 0)
    return bit6;
  if (bit6 == 0)
    return 0;
  if ((char)flags >= 0)
    return bit6;
  edge = tag_block_get_element((char *)block + 0x3c, index, 0xc);
  if ((*(unsigned char *)((char *)edge + 8) & 8) == 0) {
    display_assert((const char *)0x25ef00, (const char *)0x25ef48, 0x1e2, 1);
    system_exit(-1);
  }
  key = *(unsigned char *)((char *)edge + 9);
  return (char)((*(unsigned int *)((char *)bitvec + ((key >> 5) << 2)) & (1u << (key & 0x1f))) != 0);
}

/* FUN_000639e0 (0x639e0) — XBE naked draft (batch 225). */
#if defined(__clang__)
static void *(*const b639e0_elem)(void *, int, int) = tag_block_get_element;
static char * (*const b639e0_c1459e0)(void) = breakable_surfaces_get_bsp_surface_data;
static void (*const b639e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b639e0_exitfn)(int) = system_exit;
static char (*const b639e0_c639e0)(int scenario, unsigned char bsp_idx, float *origin, int start_surface, float *target, int end_surface, char *result_buf) = FUN_000639e0;
static int (*const b639e0_c147990)(int bsp, int surface_index, int projection, int sign, float *point, float *out_point) = collision_surface_project_point2d;

__attribute__((naked, noinline))
char FUN_000639e0(int scenario __attribute__((unused)), unsigned char bsp_idx __attribute__((unused)), float *origin __attribute__((unused)), int start_surface __attribute__((unused)), float *target __attribute__((unused)), int end_surface __attribute__((unused)), char *result_buf __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x70, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $0x60\n\t"
      "leal 0xb0(%%edi), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x1e8(%%edi), %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "call *%[c1459e0]\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "jne .LFUN_000639e0_1\n\t"
      "pushl $1\n\t"
      "pushl $0xd9\n\t"
      "pushl $0x25f09c\n\t"
      "pushl $0x25f120\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000639e0_1:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "flds (%%eax)\n\t"
      "fsubs (%%ebx)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000639e0_2:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "pushl $0xc\n\t"
      "pushl %%eax\n\t"
      "leal 0x3c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl 0x31fc1c, %%edx\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, -0x54(%%ebp)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, -0x50(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%edx, -0x4c(%%ebp)\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movb $0, -0x3(%%ebp)\n\t"
      ".LFUN_000639e0_3:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "pushl $0x18\n\t"
      "pushl %%eax\n\t"
      "leal 0x48(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "cmpl 0x14(%%edi), %%ecx\n\t"
      "sete %%al\n\t"
      "xorl %%edx, %%edx\n\t"
      "testb %%al, %%al\n\t"
      "sete %%dl\n\t"
      "movb %%al, 0x13(%%ebp)\n\t"
      "pushl $0x10\n\t"
      "movl %%edx, %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl (%%edi,%%eax,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x54(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movzbl 0x13(%%ebp), %%eax\n\t"
      "movl (%%edi,%%eax,4), %%ecx\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl $0x10\n\t"
      "pushl %%ecx\n\t"
      "addl $0x54, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "flds (%%eax)\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "fsubs (%%esi)\n\t"
      "addl $0x24, %%esp\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds (%%ecx)\n\t"
      "fsubs (%%esi)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "flds (%%esi)\n\t"
      "fsubs (%%ebx)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds (%%eax)\n\t"
      "fsubs (%%ebx)\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "cmpl %%edx, 0x10(%%edi,%%eax,4)\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "jne .LFUN_000639e0_4\n\t"
      "movb $1, -0x3(%%ebp)\n\t"
      ".LFUN_000639e0_4:\n\t"
      "flds -0x54(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "fadds (%%esi)\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fadds 0x4(%%esi)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "fadds 0x8(%%esi)\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fxch %%st(2)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      ".byte 0xde, 0xea\n\t"
      "fxch %%st(1)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000639e0_5\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls -0x40(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000639e0_5\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls -0x48(%%ebp)\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_000639e0_6\n\t"
      ".LFUN_000639e0_5:\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl 0x8(%%edi,%%eax,4), %%edi\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "cmpl 0x4(%%eax), %%edi\n\t"
      "movl %%edi, -0x14(%%ebp)\n\t"
      "je .LFUN_000639e0_9\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "jmp .LFUN_000639e0_3\n\t"
      ".LFUN_000639e0_6:\n\t"
      "movb 0x13(%%ebp), %%al\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testb %%al, %%al\n\t"
      "sete %%cl\n\t"
      "movl 0x10(%%edi,%%ecx,4), %%edi\n\t"
      "movb (%%edi,%%edx,1), %%cl\n\t"
      "movb 0xc(%%ebp), %%dl\n\t"
      "movb %%cl, %%al\n\t"
      "shrb $6, %%al\n\t"
      "andb $1, %%al\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .LFUN_000639e0_8\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000639e0_12\n\t"
      "testb %%cl, %%cl\n\t"
      "jns .LFUN_000639e0_8\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl $0xc\n\t"
      "addl $0x3c, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x8(%%esi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $8, %%al\n\t"
      "jne .LFUN_000639e0_7\n\t"
      "pushl $1\n\t"
      "pushl $0x112\n\t"
      "pushl $0x25f09c\n\t"
      "pushl $0x25ef00\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000639e0_7:\n\t"
      "movzbl 0x9(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "shrl $5, %%eax\n\t"
      "testl %%edx, (%%ecx,%%eax,4)\n\t"
      "setne %%al\n\t"
      ".LFUN_000639e0_8:\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000639e0_12\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "jmp .LFUN_000639e0_2\n\t"
      ".LFUN_000639e0_9:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000639e0_14\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LFUN_000639e0_10\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "cmpl 0x1e4(%%edx), %%esi\n\t"
      "jl .LFUN_000639e0_11\n\t"
      ".LFUN_000639e0_10:\n\t"
      "pushl $1\n\t"
      "pushl $0x13c\n\t"
      "pushl $0x25f09c\n\t"
      "pushl $0x25f0d8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000639e0_11:\n\t"
      "movswl -0x10(%%ebp), %%eax\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "fildl 0x10(%%ebp)\n\t"
      "fdivrs 0x2533c8\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "fmuls -0x50(%%ebp)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "jne .LFUN_000639e0_13\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "cmpb $0, (%%esi,%%ecx,1)\n\t"
      "je .LFUN_000639e0_13\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "leal -0x70(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "leal -0x54(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c639e0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000639e0_13\n\t"
      "movl -0x60(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jmp .LFUN_000639e0_2\n\t"
      ".LFUN_000639e0_12:\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "movl 0x20(%%ebp), %%esi\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      "flds -0x40(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "leal 0x4(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      ".byte 0xde, 0xe9\n\t"
      "pushl %%edx\n\t"
      "flds -0x30(%%ebp)\n\t"
      "pushl $1\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      "pushl $2\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "pushl %%eax\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fxch %%st(1)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x25f0d0\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fadds (%%ebx)\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fadds 0x4(%%ebx)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "call *%[c147990]\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "addl $0x18, %%esp\n\t"
      "movl %%edi, 0x10(%%esi)\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, 0x14(%%esi)\n\t"
      "movb $1, (%%esi)\n\t"
      "movl %%edx, 0x18(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000639e0_13:\n\t"
      "movl 0x20(%%ebp), %%esi\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl $1\n\t"
      "pushl $2\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c147990]\n\t"
      "addl $0x18, %%esp\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x10(%%esi)\n\t"
      "movl %%eax, 0x14(%%esi)\n\t"
      "movb $1, (%%esi)\n\t"
      "movl $0, 0x18(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000639e0_14:\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      "cmpl %%edx, %%edi\n\t"
      "je .LFUN_000639e0_15\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000639e0_15\n\t"
      "cmpl $-1, %%edx\n\t"
      "jne .LFUN_000639e0_13\n\t"
      ".LFUN_000639e0_15:\n\t"
      "movl 0x20(%%ebp), %%esi\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl $2\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c147990]\n\t"
      "addl $0x18, %%esp\n\t"
      "movl %%edi, 0x10(%%esi)\n\t"
      "popl %%edi\n\t"
      "movl $0xffffffff, 0x14(%%esi)\n\t"
      "movb $0, (%%esi)\n\t"
      "movl $0x3f800000, 0x18(%%esi)\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [elem] "m"(b639e0_elem), [c1459e0] "m"(b639e0_c1459e0), [assert] "m"(b639e0_assert), [exitfn] "m"(b639e0_exitfn), [c639e0] "m"(b639e0_c639e0), [c147990] "m"(b639e0_c147990)
      : "memory");
}
#else
#error "FUN_000639e0: clang naked draft required"
#endif

