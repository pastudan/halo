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

/* FUN_00196850 (0x196850) — XBE naked draft (batch 116). */
#if defined(__clang__)
static void (*const b196850_penter)(void *) = profile_enter_private;
static void * (*const b196850_c184e50)(int rendered_cluster_index) = rendered_cluster_get;
static void *(*const b196850_elem)(void *, int, int) = tag_block_get_element;
static void (*const b196850_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b196850_exitfn)(int) = system_exit;
static void (*const b196850_c186790)(void) = render_frustum_triangle_visible;
static void (*const b196850_pexit)(void *) = profile_exit_private;

__attribute__((naked, noinline))
void FUN_00196850(int param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "movb 0x449ef1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00196850_1\n\t"
      "movb 0x32c960, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00196850_1\n\t"
      "pushl $0x32c958\n\t"
      "call *%[penter]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00196850_1:\n\t"
      "cmpw $0, 0x5137cc\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "jle .LFUN_00196850_11\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00196850_2:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c184e50]\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl (%%esi), %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x68\n\t"
      "pushl %%ecx\n\t"
      "addl $0x134, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movb 0x505701, %%al\n\t"
      "movl 0x48(%%ebx), %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "jne .LFUN_00196850_3\n\t"
      "cmpl $-1, 0x506784\n\t"
      "je .LFUN_00196850_3\n\t"
      "addl $0x14, %%esi\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00196850_4\n\t"
      ".LFUN_00196850_3:\n\t"
      "movl $0x5065a4, -0xc(%%ebp)\n\t"
      ".LFUN_00196850_4:\n\t"
      "movl 0x44(%%ebx), %%eax\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_00196850_10\n\t"
      "jmp .LFUN_00196850_5\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00196850_5:\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl $0x100\n\t"
      "pushl %%edx\n\t"
      "pushl $0x20\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0x104, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0x14, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x8(%%edi), %%ecx\n\t"
      "addl $8, %%edi\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "leal 0x3(%%ecx,%%esi,1), %%eax\n\t"
      "addl $3, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $4, %%edi\n\t"
      "cmpl %%eax, %%esi\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "jge .LFUN_00196850_9\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00196850_6:\n\t"
      "cmpw $0x4000, 0x5937d0\n\t"
      "jge .LFUN_00196850_9\n\t"
      "movl (%%edi), %%esi\n\t"
      "movl 0x48(%%ebx), %%eax\n\t"
      "addl $4, %%edi\n\t"
      "movl %%edi, %%edx\n\t"
      "subl %%eax, %%edx\n\t"
      "movl 0x44(%%ebx), %%eax\n\t"
      "sarl $2, %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jle .LFUN_00196850_7\n\t"
      "pushl $1\n\t"
      "pushl $0x1a0\n\t"
      "pushl $0x2b36c8\n\t"
      "pushl $0x2b3668\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00196850_7:\n\t"
      "movl %%esi, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      "movl $1, %%ebx\n\t"
      "sarl $5, %%eax\n\t"
      "shll %%cl, %%ebx\n\t"
      "movl 0x5137d0(,%%eax,4), %%ecx\n\t"
      "leal 0x5137d0(,%%eax,4), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "testl %%ebx, %%ecx\n\t"
      "jne .LFUN_00196850_8\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $6\n\t"
      "addl $0xf8, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movzwl (%%eax), %%ecx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl 0xf8(%%edx), %%esi\n\t"
      "movzwl 0x2(%%eax), %%edx\n\t"
      "movzwl 0x4(%%eax), %%eax\n\t"
      "shll $5, %%eax\n\t"
      "addl %%esi, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "shll $5, %%edx\n\t"
      "shll $5, %%ecx\n\t"
      "addl %%esi, %%edx\n\t"
      "pushl %%edx\n\t"
      "addl %%esi, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c186790]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00196850_8\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "orl %%ebx, (%%eax)\n\t"
      "incw 0x5937d0\n\t"
      ".LFUN_00196850_8:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "incl %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%eax, %%esi\n\t"
      "jl .LFUN_00196850_6\n\t"
      ".LFUN_00196850_9:\n\t"
      "cmpl 0x44(%%ebx), %%esi\n\t"
      "jl .LFUN_00196850_5\n\t"
      ".LFUN_00196850_10:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw 0x5137cc, %%ax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jl .LFUN_00196850_2\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00196850_11:\n\t"
      "movb 0x449ef1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00196850_12\n\t"
      "movb 0x32c960, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00196850_12\n\t"
      "pushl $0x32c958\n\t"
      "call *%[pexit]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00196850_12:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [penter] "m"(b196850_penter), [c184e50] "m"(b196850_c184e50), [elem] "m"(b196850_elem), [assert] "m"(b196850_assert), [exitfn] "m"(b196850_exitfn), [c186790] "m"(b196850_c186790), [pexit] "m"(b196850_pexit)
      : "memory");
}
#else
#error "FUN_00196850: clang naked draft required"
#endif


/* FUN_00196a60 (0x196a60) — readable C lift from XBE leaf. */
int FUN_00196a60(float *cull_bounds, float *bounds)
{
  if (cull_bounds[1] < bounds[0] || cull_bounds[0] > bounds[1])
    return 0;
  if (cull_bounds[3] < bounds[2] || cull_bounds[2] > bounds[3])
    return 0;
  if (cull_bounds[5] < bounds[4] || cull_bounds[4] > bounds[5])
    return 0;
  if (bounds[0] < cull_bounds[0] || bounds[1] > cull_bounds[1])
    return 1;
  if (bounds[2] < cull_bounds[2] || bounds[3] > cull_bounds[3])
    return 1;
  if (bounds[4] < cull_bounds[4] || bounds[5] > cull_bounds[5])
    return 1;
  return 2;
}



/* FUN_00196b10 (0x196b10) — XBE naked draft (batch 121). */
#if defined(__clang__)


__attribute__((naked, noinline))
int FUN_00196b10(float *bounds __attribute__((unused)), int param_2 __attribute__((unused)), int param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $6, %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "leal -0x30(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      "movw 0x8(%%ebp), %%si\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "xorl %%edx, %%edx\n\t"
      "testw %%si, %%si\n\t"
      "jle .LFUN_00196b10_10\n\t"
      ".LFUN_00196b10_1:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "flds -0x20(%%ebp)\n\t"
      "movswl %%dx, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fadds 0x8(%%ebp)\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00196b10_2\n\t"
      "movl $1, %%ecx\n\t"
      ".LFUN_00196b10_2:\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00196b10_3\n\t"
      "orl $2, %%ecx\n\t"
      ".LFUN_00196b10_3:\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "flds -0x4(%%ebp)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00196b10_4\n\t"
      "orl $4, %%ecx\n\t"
      ".LFUN_00196b10_4:\n\t"
      ".byte 0xd8, 0xc2\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00196b10_5\n\t"
      "orl $8, %%ecx\n\t"
      ".LFUN_00196b10_5:\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fadds 0x8(%%ebp)\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00196b10_6\n\t"
      "orl $0x10, %%ecx\n\t"
      ".LFUN_00196b10_6:\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc3\n\t"
      "fadds 0x8(%%ebp)\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00196b10_7\n\t"
      "orl $0x20, %%ecx\n\t"
      ".LFUN_00196b10_7:\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x4(%%ebp)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00196b10_8\n\t"
      "orl $0x40, %%ecx\n\t"
      ".LFUN_00196b10_8:\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00196b10_9\n\t"
      "orl $0x80, %%ecx\n\t"
      ".LFUN_00196b10_9:\n\t"
      "cmpw $0xff, %%cx\n\t"
      "je .LFUN_00196b10_12\n\t"
      "orl %%ecx, %%ebx\n\t"
      "incl %%edx\n\t"
      "cmpw %%si, %%dx\n\t"
      "jl .LFUN_00196b10_1\n\t"
      "testw %%bx, %%bx\n\t"
      "movl $1, %%eax\n\t"
      "jne .LFUN_00196b10_11\n\t"
      ".LFUN_00196b10_10:\n\t"
      "movl $2, %%eax\n\t"
      ".LFUN_00196b10_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00196b10_12:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_00196b10: clang naked draft required"
#endif


/* FUN_00196e10 (0x196e10) — walk sound cluster list; expand env AABB.
 * ABI: sound_list@<edi>, env@<ebx>; distance unused on stack in XBE body. */
void FUN_00196e10(uint16_t *sound_list /*@<edi>*/, void *env /*@<ebx>*/,
                  float distance)
{
  float cur[3];
  float nxt[3];
  int i;
  int n;

  (void)distance;
  n = (int)(short)sound_list[0];
  if (n != 0) {
    cur[0] = *(float *)((char *)sound_list + n * 8 - 4);
    cur[1] = *(float *)((char *)sound_list + n * 8);
    cur[2] = -1.0f;
    FUN_00109590((void *)0x5065e8, cur, cur);
  }
  for (i = 0; i < n; i++) {
    nxt[0] = *(float *)((char *)sound_list + i * 8 + 4);
    nxt[1] = *(float *)((char *)sound_list + i * 8 + 8);
    nxt[2] = -1.0f;
    FUN_00109590((void *)0x5065e8, nxt, nxt);
    FUN_00189270(1, nxt, cur, env);
    cur[0] = nxt[0];
    cur[1] = nxt[1];
    cur[2] = nxt[2];
  }
}

/* FUN_00196eb0 (0x196eb0) — decode 6 quantized fractions into a real AABB. */
float *FUN_00196eb0(float *parent_bounds, unsigned char *fractions, float *out)
{
  int i;
  float lo;
  float hi;
  unsigned char f;

  for (i = 0; i < 6; i++) {
    if (i < 2) {
      lo = parent_bounds[0];
      hi = parent_bounds[1];
    } else if (i < 4) {
      lo = parent_bounds[2];
      hi = parent_bounds[3];
    } else {
      lo = parent_bounds[4];
      hi = parent_bounds[5];
    }
    f = fractions[i];
    if (f == 0xff)
      out[i] = hi;
    else
      out[i] = lo + (hi - lo) * ((float)(int)f * *(float *)0x261518);
  }
  return out;
}
