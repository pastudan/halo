void debug_pvs(uint8_t param_1)
{
  *(uint8_t *)0x505702 = param_1;
  *(uint8_t *)0x505701 = param_1;
}

void structure_visibility_find_camera(void *param_1)
{
  char *scenario;
  uint32_t leaf;
  char *cluster_elem;
  char *fog_elem;

  scenario = (char *)scenario_get();
  leaf = bsp3d_find_leaf(tag_block_get_element(scenario + 0xb0, 0, 0x60), 0,
                         param_1);

  if (leaf == 0xffffffff) {
    leaf = *(uint32_t *)0x506780;
    /* Faithful to original 0x1965f0: the cached-leaf path (jl LAB_00196637)
     * jumps to the RESET block, not past it. Jumping straight to do_cluster
     * leaves visible_sky_model (0x506789) at a stale 1 while visible_sky_index
     * (0x50678a) gets a -1 cluster sky -> render_sky.c:38 asserts
     * (!visible_sky_model || scenario_get_sky(visible_sky_index)). Only the
     * 0x506780 store is skipped on this path. */
    if ((int)leaf < *(int *)(scenario + 0xe0))
      goto reset_sky;
    leaf = 0xffffffff;
  }

  *(uint32_t *)0x506780 = leaf;
reset_sky:
  *(int *)0x506784 = -1;
  *(short *)0x50678a = -1;
  *(uint8_t *)0x506789 = 0;
  if (leaf == 0xffffffff)
    return;

  /* fall-through (was label do_cluster): also reached from the cached-leaf
   * path via `goto reset_sky` above. */
  cluster_elem = (char *)tag_block_get_element(scenario + 0xe0,
                                               (int)(leaf & 0x7fffffff), 0x10);
  *(int *)0x506784 = (int)*(short *)(cluster_elem + 8);
  fog_elem =
    (char *)tag_block_get_element(scenario + 0x134, *(int *)0x506784, 0x68);
  *(short *)0x50678a = *(short *)fog_elem;
  fog_elem = (char *)FUN_0018e7d0((int)*(short *)0x50678a);
  if (fog_elem != 0 && *(int *)(fog_elem + 0xc) != -1)
    *(uint8_t *)0x506789 = 1;
}

/* FUN_001966b0: scenario visibility cluster sweep.
 *   For each rendered cluster, walk its frustum-visible portals
 *   and mark referenced bitfield entries until a cap (0x4000) is hit.
 *   param_1 = scenario pointer (tag block base at +0x134 = clusters table). */
void FUN_001966b0(int param_1)
{
  short *local_8;
  int local_10;
  int sVar6;
  char *iVar3;
  int iVar4;
  int *piVar1;
  int *piVar5;
  int sVar2;
  int iVar_bit;
  unsigned int uVar7;

  if (*(char *)0x449ef1 != '\0' && *(char *)0x32c368 != '\0') {
    profile_enter_private((void *)0x32c360);
  }
  local_10 = 0;
  if (0 < *(short *)0x5137cc) {
    do {
      if (*(short *)0x5937d0 >= 0x4000)
        break;
      local_8 = (short *)rendered_cluster_get(local_10);
      iVar3 = (char *)tag_block_get_element((char *)param_1 + 0x134,
                                            (int)*local_8, 0x68);
      if (*(unsigned char *)0x505701 == 0 && *(int *)0x506784 != -1) {
        local_8 = local_8 + 10;
      } else {
        local_8 = (short *)0x5065a4;
      }
      iVar3 = iVar3 + 0x34;
      sVar6 = 0;
      if (0 < *(int *)iVar3) {
        do {
          if (*(short *)0x5937d0 >= 0x4000)
            break;
          iVar4 = (int)tag_block_get_element(iVar3, sVar6, 0x24);
          if (render_frustum_cube_visible(local_8, iVar4, 0) != 0) {
            piVar1 = (int *)(iVar4 + 0x18);
            piVar5 = (int *)tag_block_get_element(piVar1, 0, 4);
            sVar2 = 0;
            if (0 < *piVar1) {
              do {
                iVar_bit = *piVar5 >> 5;
                uVar7 = 1u << (*piVar5 & 0x1f);
                if ((uVar7 &
                     *(unsigned int *)((char *)0x5137d0 + iVar_bit * 4)) == 0) {
                  if (*(short *)0x5937d0 >= 0x4000)
                    break;
                  *(unsigned int *)((char *)0x5137d0 + iVar_bit * 4) |= uVar7;
                  *(short *)0x5937d0 = *(short *)0x5937d0 + 1;
                }
                piVar5 = piVar5 + 1;
                sVar2 = sVar2 + 1;
              } while ((short)sVar2 < *piVar1);
            }
          }
          sVar6 = sVar6 + 1;
        } while ((short)sVar6 < *(int *)iVar3);
      }
      local_10 = local_10 + 1;
    } while ((short)local_10 < *(short *)0x5137cc);
  }
  if (*(char *)0x449ef1 != '\0' && *(char *)0x32c368 != '\0') {
    profile_exit_private((void *)0x32c360);
  }
}

/* Recursively flood rendered clusters across BSP portal connections (0x197b00).
 * DFS over the cluster portal graph. Sets a per-cluster "visited" bit (dynamic
 * bit-vector at *0x4d8ed8) on entry and clears it on exit (backtrack). The
 * first time a cluster is reached (permanent-mark set at 0x50678c) it allocates
 * a rendered_cluster record: record[0]=cluster_index plus a 16-byte block
 * copied from *(void**)0x31fc68; a bounded counter at 0x5137cc (<0x80) indexes
 * them. For each portal it looks up the connection (scenario+0x154, 0x40-byte
 * record), picks the neighbor cluster (the other side), and, if the neighbor is
 * visible and sound-carrying, recurses -- either with the same sound list, or a
 * freshly built portal-clipped list (FUN_00108060). The assert file string
 * proves this function lives in structure_visibility.c.
 *
 * FUN_00197570 (@edx records / @esi count / float threshold) and
 * FUN_00196e10 (@edi sound_list / @ebx env / float dist) take register args --
 * verified against callee disassembly (0x197570 reads SI+EDX; 0x196e10 reads
 * [EDI] and pushes EBX without saving them). */
void FUN_00197b00(int16_t cluster_index, uint16_t *sound_list)
{
  uint16_t built_list[1026]; /* local_102c([0]=count) + local_1028(elements @
                                &[2]) -- MUST stay contiguous */
  uint16_t portal_hull[1026]; /* original: ONE hull buffer at EBP-0x824
                                 ([0]=count word, float pairs @ &[2]).
                                 FUN_001974f0 -> FUN_00197310 writes up to
                                 0x100 points (0x804 bytes) through it; the
                                 prior split into `int local_828` + work_b
                                 smashed the clang frame (map-load crash,
                                 read of 0xc0170662 at FUN_00197b00+0x2a9). */
  void *bsp;
  int cluster_index_i;
  char *clusters_block;
  char *connections_block;
  uint16_t *cluster_elem;
  uint32_t *sound_bits;
  uint32_t bit_mask;
  int bit_offset;
  int16_t *rec;
  int i;
  void *sound_env_out;

  bsp = scenario_get();
  cluster_index_i = (int)cluster_index;
  cluster_elem = (uint16_t *)tag_block_get_element((char *)bsp + 0x134,
                                                   cluster_index_i, 0x68);
  sound_bits = structure_bsp_get_cluster_sound_data(bsp, *(int16_t *)0x506784);

  if (sound_list == 0 || (int16_t)*sound_list < 0 ||
      (int16_t)*sound_list > 0x100) {
    display_assert("valid_portal_hull(visible_region)",
                   "c:\\halo\\SOURCE\\structures\\structure_visibility.c",
                   0x3ee, 1);
    system_exit(-1);
  }

  bit_mask = 1u << (cluster_index_i & 0x1f);
  bit_offset = (cluster_index_i >> 5) * 4;
  *(uint32_t *)(bit_offset + *(int *)0x4d8ed8) |= bit_mask;

  if ((*(uint32_t *)(bit_offset + 0x50678c) & bit_mask) == 0) {
    char *src;
    uint16_t rc_index;

    if (*(int16_t *)0x5137cc >= 0x80) {
      display_assert("raise MAXIMUM_RENDERED_CLUSTERS",
                     "c:\\halo\\SOURCE\\structures\\structure_visibility.c",
                     0x3f5, 1);
      system_exit(-1);
    }
    if ((int16_t)cluster_index < 0 || (int16_t)cluster_index >= 0x200) {
      display_assert("cluster_index>=0 && cluster_index<MAXIMUM_CLUSTERS",
                     "c:\\halo\\SOURCE\\structures\\structure_visibility.c",
                     0x3f8, 1);
      system_exit(-1);
    }

    rc_index = *(uint16_t *)0x5137cc;
    *(uint16_t *)(0x4d8edc + cluster_index_i * 2) = rc_index;
    *(uint16_t *)0x5137cc = rc_index + 1;
    rec = (int16_t *)rendered_cluster_get(
      *(uint16_t *)(0x4d8edc + cluster_index_i * 2));
    rec[0] = cluster_index;
    src = *(char **)0x31fc68;
    *(uint32_t *)((char *)rec + 4) = *(uint32_t *)(src + 0);
    *(uint32_t *)((char *)rec + 8) = *(uint32_t *)(src + 4);
    *(uint32_t *)((char *)rec + 12) = *(uint32_t *)(src + 8);
    *(uint32_t *)((char *)rec + 16) = *(uint32_t *)(src + 12);
  } else {
    rec = (int16_t *)rendered_cluster_get(
      *(uint16_t *)(0x4d8edc + cluster_index_i * 2));
    if (rec[0] != cluster_index) {
      display_assert("rendered_cluster->cluster_index==cluster_index",
                     "c:\\halo\\SOURCE\\structures\\structure_visibility.c",
                     0x403, 1);
      system_exit(-1);
    }
  }

  *(uint32_t *)(bit_offset + 0x50678c) |= bit_mask;
  /* 0x197ca9: original sets EDI=[ebp+0xc] (visible_region hull param) and
   * ESI=rec+4 (rendered-cluster bounds rect) before CALL. Accumulates the
   * hull's 2D points into the rect (min/max union). */
  FUN_00196d60((float *)((char *)rec + 4), (int16_t *)sound_list);

  if (*(char *)0x505702 != 0) {
    FUN_00196e10(sound_list, *(void **)0x2ee6d0, 0.05f);
  } else if (ai_debug_highlight_cluster(cluster_index, &sound_env_out) != 0) {
    FUN_00196e10(sound_list, sound_env_out, 0.05f);
  }

  clusters_block = (char *)bsp + 0x134;
  connections_block = (char *)bsp + 0x154;
  for (i = 0; i < *(int *)((char *)cluster_elem + 0x5c); i++) {
    int16_t conn_index;
    int16_t *conn;
    int pick;
    int16_t neighbor;
    uint32_t nmask;
    int noff;

    conn_index =
      *(int16_t *)tag_block_get_element((char *)cluster_elem + 0x5c, i, 2);
    conn = (int16_t *)tag_block_get_element(connections_block, (int)conn_index,
                                            0x40);
    pick = (conn[0] == cluster_index) ? 1 : 0;
    neighbor = conn[pick];
    if (neighbor < 0 || (int)neighbor >= *(int *)clusters_block)
      continue;

    nmask = 1u << ((int)neighbor & 0x1f);
    noff = ((int)neighbor >> 5) * 4;
    if ((*(uint32_t *)((char *)(*(int *)0x4d8ed8) + noff) & nmask) != 0)
      continue;
    if ((*(uint32_t *)((char *)sound_bits + noff) & nmask) == 0)
      continue;

    {
      int16_t r = FUN_001974f0(conn_index, (char)pick, (int *)portal_hull);

      if (r == 2) {
        FUN_00197b00(neighbor, sound_list);
      } else if (r == 0) {
        if (*(char *)0x506789 == 0) {
          char c =
            FUN_00197570(*(float **)((char *)conn + 0x38),
                         *(int16_t *)((char *)conn + 0x34), *(float *)0x506590);
          if (c == 0)
            continue;
        }
        /* 0x197dd6: arg3 is the dword loaded from the hull base (count word),
         * arg4 the hull points at base+4 — both from the ONE buffer 1974f0
         * filled. */
        built_list[0] =
          (uint16_t)FUN_00108060(*sound_list, sound_list + 2,
                                 *(int *)portal_hull, portal_hull + 2,
                                 0x100, &built_list[2], 0x38d1b717);
        if ((int16_t)built_list[0] > 0) {
          FUN_00197b00(neighbor, built_list);
        } else if (built_list[0] == 0xffff) {
          error(2, "portal intersection failed.");
          FUN_00197b00(neighbor, sound_list);
        }
      }
    }
  }

  *(uint32_t *)(bit_offset + *(int *)0x4d8ed8) &= ~bit_mask;
}

/* FUN_001978a0: recursive bsp3d structure-visibility traversal.
 *   Original: c:\halo\SOURCE\structures\structure_visibility.c line ~0x2ab.
 *
 * Walks the structure BSP3D node tree from `node_index`. At each node it
 * subdivides the incoming (parent) bounds across the node's fraction record
 * (FUN_00196eb0 -> child bounds in `bounds`), tests those bounds against the
 * cull bounds (FUN_00196a60) and the frustum planes (FUN_00196b10) unless the
 * caller already reported "fully inside" ((short)intersection == 2), then for
 * each of the node's two child slots that survive the splitting-plane sphere
 * test recurses into subtrees (child >= 0) or dispatches leaves (child < 0,
 * child != -1) via FUN_00197130. Returns the accumulated 16-bit count in AX.
 *
 * 11 cdecl stack args (recursive tail cleans ADD ESP,0x2c = 44 = 11*4).
 * ESI is the running accumulator, EDI the propagated intersection mode.
 *
 * Verified against disasm 0x1978a0-0x197afa. Notes on decompiler traps fixed
 * here:
 *   - The two side flags are independent stack bytes (side[0]/side[1]),
 *     defaulted to 1 and cleared by the plane test; Ghidra modelled them as a
 *     CONCAT into param_2. param_2 is really a float* (parent bounds).
 *   - The value passed to children in slot 7 is the UNCHANGED radius (held in
 *     EBX across the FPU block), not fVar1; the decompiler mis-aliased EBX.
 *   - FUN_00196eb0 is a 3-arg call (bounds, fractions, out); its 3rd arg is the
 *     &local_24 push that tag_block_get_element left on the stack (this is the
 *     ADD ESP,0xc "anomaly"). FUN_00196b10 takes &bounds in @eax. */
unsigned short FUN_001978a0(int node_index, float *parent_bounds, void *param_3,
                            int *param_4, int param_5, float *center,
                            float radius, float *cull_bounds, int param_9,
                            int param_10, int intersection)
{
  int accum;
  char *scenario;
  char *nodes_block;
  unsigned char *fractions;
  int mode;
  int t;
  int *node;
  float *plane;
  float dist;
  unsigned char side[2];
  int count;
  int *child_ptr;
  unsigned char *side_ptr;
  int child;
  float bounds[6];

  accum = 0;
  scenario = (char *)scenario_get();
  nodes_block = (char *)tag_block_get_element(scenario + 0xb0, 0, 0x60);

  if (parent_bounds == 0) {
    display_assert("parent_bounds",
                   "c:\\halo\\SOURCE\\structures\\structure_visibility.c",
                   0x2ab, true);
    system_exit(-1);
  }
  if (center == 0) {
    display_assert("cull_sphere_center",
                   "c:\\halo\\SOURCE\\structures\\structure_visibility.c",
                   0x2ac, true);
    system_exit(-1);
  }
  if (cull_bounds == 0) {
    display_assert("cull_bounds",
                   "c:\\halo\\SOURCE\\structures\\structure_visibility.c",
                   0x2ad, true);
    system_exit(-1);
  }
  /* the original loads intersection into EDI here and keeps that register as
   * the running mode for the rest of the function */
  mode = intersection;
  if ((short)mode == 0) {
    display_assert("intersection",
                   "c:\\halo\\SOURCE\\structures\\structure_visibility.c",
                   0x2ae, true);
    system_exit(-1);
  }

  fractions =
    (unsigned char *)tag_block_get_element(scenario + 0xbc, node_index, 6);
  FUN_00196eb0(parent_bounds, fractions, bounds);

  if ((short)mode != 2) {
    mode = FUN_00196a60(cull_bounds, bounds);
    if ((short)mode == 0)
      return (unsigned short)accum;
    t = FUN_00196b10(bounds, param_9, param_10);
    if ((short)t == 2)
      param_9 = 0;
    if ((short)mode > (short)t)
      mode = t;
  }

  if ((short)mode != 0) {
    node = (int *)tag_block_get_element(nodes_block, node_index, 0xc);
    plane = (float *)tag_block_get_element(nodes_block + 0xc, *node, 0x10);
    dist = plane[2] * center[2] + plane[1] * center[1] + center[0] * plane[0] -
           plane[3];

    side[0] = 1;
    if (!(dist < radius))
      side[0] = 0;
    side[1] = 1;
    if (!(dist > -radius))
      side[1] = 0;

    child_ptr = node + 1;
    side_ptr = side;
    count = 2;
    do {
      if (*side_ptr != 0) {
        child = *child_ptr;
        /* recurse arm first: original falls through into the self-call and
         * sinks the leaf arm past the join (JS to it) */
        if (child >= 0) {
          accum += FUN_001978a0(child, bounds, param_3, param_4 + (short)accum,
                                param_5 - accum, center, radius, cull_bounds,
                                param_9, param_10, mode);
        } else if (child != -1) {
          /* 0x19713c: callee reads the leaf ref from EAX (strips the sign
           * bit itself via AND 0x7fffffff) — implicit @<eax> arg. */
          accum += FUN_00197130(bounds, param_3, param_4 + (short)accum,
                                param_5 - accum, center, radius, cull_bounds,
                                param_9, param_10, mode, child);
        }
      }
      child_ptr++;
      side_ptr++;
    } while (--count != 0);
  }

  return (unsigned short)accum;
}
/* --- structure_visibility.obj batch drafts (2026-07-26) --- */

/* 0x196850 */
void FUN_00196850(int param_1)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* relift: relift: mov (char)eax, byte ptr [0x449ef1] */
  /* test (char)eax, (char)eax -> je 0x196875 */
  /* relift: relift: mov (char)eax, byte ptr [0x32c960] */
  /* test (char)eax, (char)eax -> je 0x196875 */
  profile_enter_private((void *)0x0032c958);
  rendered_cluster_get(0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* relift: relift: mov (char)eax, byte ptr [0x505701] */
  /* relift: cmp dword ptr [0x506784], -1 -> je 0x1968d4 */
  /* test eax, eax -> jle 0x196a1f */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* relift: cmp word ptr [0x5937d0], 0x4000 -> jge 0x196a16 */
  /* cmp edx, eax -> jle 0x196985 */
  display_assert((char *)0x002b3668, (char *)0x002b36c8, 416, 0);
  system_exit(0);
  /* test ecx, ebx -> jne 0x1969ff */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  render_frustum_triangle_visible();
  /* test (char)eax, (char)eax -> je 0x1969ff */
  /* relift: cmp esi, dword ptr [ebx + 0x44] -> jl 0x1968f0 */
  /* relift: relift: mov (char)eax, byte ptr [0x449ef1] */
  /* test (char)eax, (char)eax -> je 0x196a55 */
  /* relift: relift: mov (char)eax, byte ptr [0x32c960] */
  /* test (char)eax, (char)eax -> je 0x196a55 */
  profile_exit_private((void *)0x0032c958);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x196a60 */
int FUN_00196a60(float *cull_bounds, float *bounds)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x196b10 */
int FUN_00196b10(float *bounds, int param_2, int param_3)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test (int16_t)esi, (int16_t)esi -> jle 0x196c75 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* cmp (int16_t)ecx, 0xff -> je 0x196c81 */
  /* cmp (int16_t)edx, (int16_t)esi -> jl 0x196b36 */
  scenario_get();
  rendered_cluster_get(0);
  /* cmp esi, -1 -> je 0x196d36 */
  /* test (char)eax, (char)eax -> je 0x196d25 */
  /* relift: cmp (int16_t)edi, word ptr [ebp + 0xc] -> jge 0x196d25 */
  /* relift: cmp dword ptr [0x506784], -1 -> je 0x196d14 */
  render_frustum_sphere_visible((void *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0.0f);
  /* test (int16_t)eax, (int16_t)eax -> je 0x196d25 */
  /* cmp esi, -1 -> jne 0x196cd2 */
  /* test esi, esi -> jne 0x196d84 */
  display_assert((char *)0x002b3714, (char *)0x002b36c8, 1231, 0);
  system_exit(0);
  /* test edi, edi -> je 0x196d96 */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x196d96 */
  /* cmp (int16_t)eax, 0x100 -> jle 0x196db6 */
  display_assert((char *)0x002b36fc, (char *)0x002b36c8, 1232, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> jne 0x196dcf */
  /* test (char)eax, 0x41 -> jne 0x196df3 */
  /* relift: cmp (int16_t)edx, word ptr [edi] -> jl 0x196dc0 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x196e4c */
  matrix_transform_point((void *)0x005065e8, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  /* relift: cmp word ptr [edi], (int16_t)esi -> jle 0x196eab */
  matrix_transform_point((void *)0x005065e8, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  FUN_00189270(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (void *)(uintptr_t)ebx);
  scenario_get();
  /* relift: cmp (int16_t)edi, word ptr [ebp + 0xc] -> jge 0x19711a */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* relift: cmp (int16_t)edi, word ptr [ebp + 0xc] -> jge 0x197109 */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 36);
  FUN_00196a60((float *)0, (float *)0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x1970f5 */
  /* relift: tail-call FUN_00196b10(); */
  /* test (int16_t)eax, (int16_t)eax -> je 0x1970f5 */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  /* relift: test dword ptr [edx + 0x5137d0], esi -> je 0x1970e1 */
  /* test esi, ecx -> jne 0x1970e1 */
  /* relift: cmp edx, dword ptr [ebx] -> jl 0x197097 */
  /* cmp eax, ecx -> jl 0x197034 */
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  display_assert((char *)0x002b3798, (char *)0x002b36c8, 752, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1971b5 */
  display_assert((char *)0x002b3788, (char *)0x002b36c8, 753, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1971dc */
  display_assert((char *)0x002b3774, (char *)0x002b36c8, 754, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x197203 */
  display_assert((char *)0x002b3768, (char *)0x002b36c8, 755, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x197217 */
  /* relift: cmp ecx, dword ptr [edi + 0x134] -> jl 0x197237 */
  display_assert((char *)0x002b3720, (char *)0x002b36c8, 756, 0);
  system_exit(0);
  FUN_00196eb0((float *)(uintptr_t)eax, (unsigned char *)(uintptr_t)esi, (float *)(uintptr_t)edx);
  /* cmp (int16_t)ebx, 2 -> je 0x197275 */
  FUN_00196a60((float *)0, (float *)0);
  /* relift: tail-call FUN_00196b10(); */
  /* cmp (int16_t)ebx, (int16_t)eax -> jle 0x197275 */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x197300 */
  /* cmp ebx, eax -> jge 0x197300 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  /* test edx, ecx -> je 0x1972ef */
  /* test edx, ecx -> jne 0x1972ef */
  /* relift: cmp word ptr [ebp + 0x2c], (int16_t)edi -> jge 0x197300 */
  /* cmp ebx, ecx -> jl 0x197294 */
  scenario_get();
  /* relift: relift: fcomp qword ptr [0x2674e8] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1974d8 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x1973ca */
  matrix_transform_point((float *)(uintptr_t)ecx, (float *)(uintptr_t)esi, (float *)(uintptr_t)eax);
  convex_polygon3d_clip_to_plane(eax, (float *)(uintptr_t)ecx, (void *)0x002b35c4, 256, (float *)(uintptr_t)edx, (void *)0, 0.0f, (void *)0);
  display_assert((char *)0x002b37b0, (char *)0x002b36c8, 1157, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp + 0x10], 1 -> jne 0x197432 */
  /* relift: cmp (int16_t)edi, word ptr [ebp - 4] -> je 0x1974c5 */
  /* relift: relift: fld dword ptr [0x255e94] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x197496 */
  display_assert((char *)0x002b37a8, (char *)0x002b36c8, 1175, 0);
  system_exit(0);
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 64);
  tag_block_get_element((void *)(uintptr_t)edi, 0, 96);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  FUN_00197310((void *)0x005065a4, (void *)0, (void *)0, (void *)0, 0, 0, (void *)0);
  /* test (int16_t)esi, (int16_t)esi -> jle 0x1975d5 */
  /* relift: relift: fld dword ptr [0x506564] */
  /* relift: relift: fld dword ptr [0x506560] */
  /* relift: relift: fld dword ptr [0x50655c] */
  /* cmp (int16_t)ecx, (int16_t)esi -> jl 0x197580 */
  FUN_001d90e0();
  scenario_get();
  render_frustum_get_projection_bounds((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  /* relift: relift: mov (int16_t)ecx, word ptr [0x506784] */
  structure_bsp_get_cluster_sound_data((void *)(uintptr_t)esi, ecx);
  /* relift: cmp dword ptr [eax], 0 -> je 0x19786e */
  /* cmp eax, ebx -> jge 0x197874 */
  /* relift: test dword ptr [ecx], edx -> je 0x197854 */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 104);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 64);
  FUN_00197310((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)0, (void *)(uintptr_t)edx, 0, 0, (void *)0);
  /* test (int16_t)eax, (int16_t)eax -> jne 0x19776b */
  FUN_00108060(eax, (void *)(uintptr_t)edx, 0, (void *)(uintptr_t)eax, 256, (void *)(uintptr_t)edx, 0x38d1b717);
  /* cmp (int16_t)eax, 2 -> jne 0x19783d */
  tag_get('rdhs', 0);
  /* relift: cmp word ptr [eax + 0x24], 3 -> jne 0x1977a9 */
  FUN_001906b0((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x197819 */
  /* relift: relift: fcomp qword ptr [0x2533d0] */
  /* relift: relift: fcomp qword ptr [0x2533d0] */
  /* relift: relift: fcomp qword ptr [0x2533d0] */
  /* relift: relift: fcomp qword ptr [0x2533d0] */
  error(0, (char *)0x002b37cc);
  /* cmp eax, ecx -> jl 0x1976f1 */
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 96);
  /* test eax, eax -> jne 0x1978ee */
  display_assert((char *)0x002b3788, (char *)0x002b36c8, 683, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x197915 */
  display_assert((char *)0x002b3774, (char *)0x002b36c8, 684, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x19793c */
  display_assert((char *)0x002b3768, (char *)0x002b36c8, 685, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jne 0x197964 */
  display_assert((char *)0x002b3798, (char *)0x002b36c8, 686, 0);
  system_exit(0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  FUN_00196eb0((float *)(uintptr_t)eax, (unsigned char *)(uintptr_t)eax, (float *)0);
  /* cmp (int16_t)edi, 2 -> je 0x1979cd */
  FUN_00196a60((float *)0, (float *)0);
  /* test (int16_t)edi, (int16_t)edi -> je 0x197af1 */
  /* relift: tail-call FUN_00196b10(); */
  /* cmp (int16_t)eax, 2 -> jne 0x1979c6 */
  /* cmp (int16_t)edi, (int16_t)eax -> jle 0x1979cd */
  /* test (int16_t)edi, (int16_t)edi -> je 0x197af1 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 12);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)eax, 0x41 -> je 0x197a3f */
  /* relift: cmp byte ptr [edx], 0 -> je 0x197ad4 */
  FUN_001978a0(0, (float *)(uintptr_t)edx, (void *)(uintptr_t)ecx, (void *)(uintptr_t)edx, 0, (float *)0, 0.0f, (float *)0, 0, 0, 0);
  /* cmp eax, -1 -> je 0x197ad4 */
  FUN_00197130((float *)(uintptr_t)edx, (void *)(uintptr_t)ecx, (void *)(uintptr_t)edx, 0, (float *)0, 0.0f, (float *)0, 0, 0, 0, 0);
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
