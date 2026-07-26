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
/* --- path_smoothing.obj batch drafts (2026-07-26) --- */

/* 0x62b20 */
void FUN_00062b20(void)
{
  int eax = 0;
  int ebx = 0;

  /* test (char)ebx, (char)ebx -> jne 0x62b92 */
  /* test (char)eax, (char)eax -> je 0x62b92 */
  tag_block_get_element((void *)(uintptr_t)0, 0, 0);
  /* test (char)eax, 8 -> jne 0x62b75 */
  display_assert((char *)0x0025ef00, (char *)0x0025ef48, 482, 1);
  system_exit(-1);

  (void)eax;
  (void)ebx;
}

/* 0x62ba0 */
void FUN_00062ba0(void)
{
  int eax = 0;

  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x62c9a */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  magnitude3d((void *)0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */

  (void)eax;
}

/* 0x62cf0 */
void FUN_00062cf0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x62e10 */
void FUN_00062e10(void)
{
  FUN_0010c3c0();
  FUN_0010c3c0();
  FUN_0010c3c0();
  FUN_0010c3c0();
}

/* 0x63030 */
void find_turning_point(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;
  int local_4 = 0;
  int local_8 = 0;

  tag_block_get_element((void *)((char *)eax + 0xb0), 0, 96);
  breakable_surfaces_get_bsp_surface_data();
  /* test (char)ebx, (char)ebx -> je 0x63098 */
  display_assert((char *)0x0025efe0, (char *)0x0025ef48, 511, 1);
  system_exit(eax);
  tag_block_get_element((void *)((char *)eax + 0x48), 0, 24);
  /* test dl, dl -> jne 0x6313a */
  /* test (char)ebx, (char)ebx -> je 0x6313a */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)eax, 8 -> jne 0x6311e */
  display_assert((char *)0x0025ef00, (char *)0x0025ef48, 482, 1);
  system_exit(-1);
  tag_block_get_element((void *)(uintptr_t)local_8, 0, 16);
  tag_block_get_element((void *)(uintptr_t)local_8, 0, 16);
  /* relift: relift: fcomp qword ptr [0x2533d0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* cmp eax, edi -> jne 0x63237 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* cmp eax, -1 -> jne 0x6325e */
  /* cmp edi, eax -> je 0x633a7 */
  /* cmp eax, -1 -> jne 0x6328e */
  /* relift: cmp byte ptr [ebp + 0x18], 0 -> jne 0x6331a */
  /* test (char)eax, (char)eax -> je 0x6331a */
  tag_block_get_element((void *)(uintptr_t)local_4, 0, 0);
  /* test (char)eax, 8 -> jne 0x632fb */
  display_assert((char *)0x0025ef00, (char *)0x0025ef48, 482, 1);
  system_exit(-1);
  /* relift: cmp (char)eax, byte ptr [ebp + 0x14] -> je 0x63377 */
  tag_block_get_element((void *)(uintptr_t)local_4, 0, 0);
  /* cmp ebx, eax -> je 0x633a7 */
  /* relift: cmp dword ptr [esi], edi -> je 0x63294 */
  /* relift: cmp dword ptr [esi + 4], edi -> je 0x63294 */
  display_assert((char *)0x0025ef70, (char *)0x0025ef48, 631, 1);
  system_exit(-1);
  tag_block_get_element((void *)(uintptr_t)local_8, local_4, 16);

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
  (void)local_4;
  (void)local_8;
}

/* 0x633b0 */
void FUN_000633b0(unsigned int param_1, int param_2, void *param_3, int *param_4, void *param_5, char *param_6)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;
  int local_14 = 0;
  int local_18 = 0;

  /* relift: cmp word ptr [ebp + 0xc], 0 -> jg 0x633da */
  display_assert((char *)0x0025f048, (char *)0x0025ef48, 33, 1);
  system_exit(-1);
  /* test edi, edi -> jne 0x63401 */
  display_assert((char *)0x0025f03c, (char *)0x0025ef48, 34, 1);
  system_exit(-1);
  /* test ebx, ebx -> jne 0x63425 */
  display_assert((char *)0x0025f028, (char *)0x0025ef48, 35, 1);
  system_exit(-1);
  /* test esi, esi -> jne 0x63449 */
  display_assert((char *)0x0025f018, (char *)0x0025ef48, 36, 1);
  system_exit(-1);
  /* test eax, eax -> jne 0x6346d */
  display_assert((char *)0x0025f004, (char *)0x0025ef48, 37, 1);
  system_exit(-1);
  /* relift: cmp word ptr [ebp + 0xc], (int16_t)eax -> jle 0x636e7 */
  FUN_00063e90(0, 0, (void *)0, local_18, (float *)(uintptr_t)local_14, 0, 0.0f, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x63509 */
  /* test (char)ebx, (char)ebx -> jne 0x63515 */
  /* test (char)ebx, (char)ebx -> je 0x63515 */
  /* test (char)ebx, (char)ebx -> je 0x6368f */
  /* cmp edi, -1 -> je 0x6368f */
  find_turning_point();
  find_turning_point();
  /* test (char)eax, (char)eax -> je 0x636c9 */
  /* test (char)ebx, (char)ebx -> je 0x636c9 */
  FUN_00062e10();
  FUN_00062ba0();
  FUN_00062ba0();
  FUN_00062cf0();
  FUN_00063e30();
  tag_block_get_element((void *)(uintptr_t)*(int *)((char *)param_1 + 0x64), 0, 0);
  collision_surface_project_point2d(eax, 0, 0, 0, (float *)0, (float *)0);
  /* test (char)eax, (char)eax -> jne 0x63700 */

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
  (void)ebp;
  (void)local_14;
  (void)local_18;
}

/* 0x639e0 */
int FUN_000639e0(int scenario, unsigned char bsp_idx, float *origin, int node_handle, float *target, int flags, char *result_buf)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  tag_block_get_element((void *)(uintptr_t)eax, 0, 96);
  breakable_surfaces_get_bsp_surface_data();
  display_assert((char *)0x0025f120, (char *)0x0025f09c, 217, 0);
  system_exit(0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 12);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 24);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 16);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)eax, 0x41 -> jne 0x63bbc */
  /* test (char)eax, 0x41 -> jne 0x63bbc */
  /* test (char)eax, 0x41 -> je 0x63bda */
  /* test dl, dl -> jne 0x63c5f */
  /* test (char)eax, (char)eax -> je 0x63d1b */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)eax, 8 -> jne 0x63c43 */
  display_assert((char *)0x0025ef00, (char *)0x0025f09c, 274, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x63d1b */
  /* test (char)eax, (char)eax -> je 0x63de1 */
  /* test esi, esi -> jl 0x63c8f */
  /* relift: cmp esi, dword ptr [edx + 0x1e4] -> jl 0x63caf */
  display_assert((char *)0x0025f0d8, (char *)0x0025f09c, 316, 0);
  system_exit(0);
  /* relift: cmp byte ptr [esi + ecx], 0 -> je 0x63da9 */
  /* relift: tail-call FUN_000639e0(); */
  /* test (char)eax, (char)eax -> jne 0x63da9 */
  collision_surface_project_point2d(0, 0, 0, 0, (float *)0, (float *)0);
  collision_surface_project_point2d(0, 0, 0, 0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)eax);
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}
