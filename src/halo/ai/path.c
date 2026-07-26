/* path.c — AI path planning state builders.
 *
 * Corresponds to path.obj (XBE address range ~0x5dfc0–0x5ff70+).
 * __FILE__ = c:\halo\SOURCE\ai\path.c (confirmed via display_assert strings
 * in path_state_build_path at 0x5eae0).
 *
 * Ported: path_state_init (0x5dfc0), path_state_set_focus (0x5e000),
 *         path_state_set_sphere (0x5e030), path_state_set_min_speed (0x5e070),
 *         path_state_commit (0x5e090), path_state_set_obstacle (0x5e0d0),
 *         path_get_node (path node accessor with bounds assert),
 *         path_node_from_hash_table (path hash table lookup by key),
 *         path_3d_available (path ray-cast clearance check),
 *         FUN_0005ff70 (path traverse + debug snapshot).
 * Deferred: path_state_build_path (0x5eae0) — complex path evaluation,
 * deferred.
 */

#include "../../common.h"

/* All callees (csmemset, csmemcpy, scenario_get,
 * global_structure_bsp_index_get) declared via decl.h / generated header */

/* 0x005dfc0 — path_state_init
 * Zero-fills a 0x48-byte path_state record, then writes the initial fields.
 *
 * Disassembly-confirmed field layout (ESI = param_1):
 *   [ESI+0x00] = param_2  (uint32_t flags)
 *   [ESI+0x04] = param_3  (uint8_t — byte at +4 in the uint32_t slot, MSVC
 * packs) [ESI+0x08] = param_4  (int unit_handle) [ESI+0x0c] = 0xffffffff
 *
 * Note: Ghidra showed param_1+1 (dword slot) for param_3 storage, but the
 * disassembly has `MOV byte ptr [ESI+4], CL` — param_3 is stored at byte
 * offset +4, not at dword-slot +1 (+4). The decompiler rendered this as
 * `*(undefined1*)(param_1+1)` due to how it assigns dword-indexed fields.
 * The raw byte offset is +4.
 */
void path_input_new(void *param_1, uint32_t param_2, uint8_t param_3,
                    int param_4)
{
  csmemset(param_1, 0, 0x48);
  *(uint32_t *)param_1 = param_2;
  *(uint8_t *)((char *)param_1 + 4) = param_3;
  *(int *)((char *)param_1 + 8) = param_4;
  *(int *)((char *)param_1 + 0xc) = -1;
  return;
}

/* 0x005dff0 — path_state_set_ignore_object
 * Sets the ignore-object handle in a path_state record.
 *
 * Disassembly: MOV EAX,[EBP+0xc]; MOV ECX,[EBP+0x8]; MOV [ECX+0xc],EAX; RET
 */
void paths_dispose(void *param_1, int param_2)
{
  *(int *)((char *)param_1 + 0xc) = param_2;
}

/* 0x005e000 — path_state_set_focus
 * Sets the focus-position fields in a path_state record.
 *
 * Disassembly-confirmed stores (EAX = param_1):
 *   [EAX+0x10] = 1  (focus_valid flag, uint8_t)
 *   [EAX+0x14] = param_2[0]  (focus_pos.x)
 *   [EAX+0x18] = param_2[1]  (focus_pos.y)
 *   [EAX+0x1c] = param_2[2]  (focus_pos.z)
 *   [EAX+0x20] = param_3  (bone index)
 */
void path_input_set_start(void *param_1, float *param_2, int param_3)
{
  *(uint8_t *)((char *)param_1 + 0x10) = 1;
  *(float *)((char *)param_1 + 0x14) = param_2[0];
  *(float *)((char *)param_1 + 0x18) = param_2[1];
  *(float *)((char *)param_1 + 0x1c) = param_2[2];
  *(int *)((char *)param_1 + 0x20) = param_3;
  return;
}

/* 0x005e030 — path_state_set_sphere
 * Sets the sphere-obstacle fields in a path_state record.
 *
 * Disassembly-confirmed stores (EAX = param_1, ECX/EDX = params 3/4/5):
 *   [EAX+0x24] = 1       (sphere_valid flag, uint8_t)
 *   [EAX+0x28] = param_2[0]  (sphere_pos.x)
 *   [EAX+0x2c] = param_2[1]  (sphere_pos.y)
 *   [EAX+0x30] = param_2[2]  (sphere_pos.z)
 *   [EAX+0x34] = param_4  (flags — note: [EBP+0x14] stored at +0x34, NOT +0x38)
 *   [EAX+0x38] = param_3  (inner_r — note: [EBP+0x10] stored at +0x38, NOT
 * +0x34) [EAX+0x3c] = param_5  (outer_r)
 *
 * Store rotation confirmed: MSVC emitted param_3 → +0x38, param_4 → +0x34
 * (pipeline-scheduled out-of-order). See disassembly:
 *   MOV [EAX+0x38], ECX   ; ECX = [EBP+0x10] = param_3
 *   MOV [EAX+0x34], EDX   ; EDX = [EBP+0x14] = param_4
 */
void path_input_set_attractor(void *param_1, float *param_2, float param_3,
                              uint32_t param_4, float param_5)
{
  *(uint8_t *)((char *)param_1 + 0x24) = 1;
  *(float *)((char *)param_1 + 0x28) = param_2[0];
  *(float *)((char *)param_1 + 0x2c) = param_2[1];
  *(float *)((char *)param_1 + 0x30) = param_2[2];
  *(float *)((char *)param_1 + 0x38) = param_3;
  *(uint32_t *)((char *)param_1 + 0x34) = param_4;
  *(float *)((char *)param_1 + 0x3c) = param_5;
  return;
}

/* 0x005e070 — path_state_set_min_speed
 * Sets the minimum-speed constraint fields in a path_state record.
 *
 * Disassembly-confirmed stores (EAX = param_1):
 *   [EAX+0x40] = 1       (min_speed_valid flag, uint8_t)
 *   [EAX+0x44] = param_2 (min_speed, int)
 */
void path_input_set_search_bounds(void *param_1, int param_2)
{
  *(uint8_t *)((char *)param_1 + 0x40) = 1;
  *(int *)((char *)param_1 + 0x44) = param_2;
  return;
}

/* 0x005e090 — path_state_commit
 * Zero-fills a 0x1408c-byte result buffer, then copies 0x48 bytes (0x12 dwords)
 * from the path_state (param_1) into it, stores the current scenario handle at
 * result+0x64, and writes the cam_ref handle at result+0x48.
 *
 * Disassembly-confirmed (EBX = param_2 = result buffer):
 *   csmemset(param_2, 0, 0x1408c)
 *   param_2[0x19] = scenario_get()   ; at byte offset 0x64 (0x19 * 4)
 *   MOVSD.REP ECX=0x12: copy param_1[0..0x47] → param_2[0..0x47]
 *   param_2[0x12] = param_3          ; at byte offset 0x48 (0x12 * 4)
 *
 * Note: scenario handle stored at +0x64, not +0x19 (raw dword index is 0x19).
 * The copy overwrites param_2[0..0x47], then param_3 is stored at
 * param_2[0x48].
 */
void path_state_new(void *param_1, void *param_2, void *param_3)
{
  csmemset(param_2, 0, 0x1408c);
  *(void **)((char *)param_2 + 0x64) = scenario_get();
  /* Copy 0x48 bytes from param_1 into param_2 at offset 0 (MOVSD.REP ECX=0x12)
   */
  csmemcpy(param_2, param_1, 0x48);
  *(void **)((char *)param_2 + 0x48) = param_3;
  return;
}

/* 0x005e0d0 — path_state_set_obstacle
 * Sets an obstacle hit record in a path_state.
 *
 * Disassembly-confirmed stores (EAX = param_1):
 *   [EAX+0x4c] = 1       (obstacle_valid flag, uint8_t)
 *   [EAX+0x50] = param_2[0]  (hit_pos.x)
 *   [EAX+0x54] = param_2[1]  (hit_pos.y)
 *   [EAX+0x58] = param_2[2]  (hit_pos.z)
 *   [EAX+0x5c] = param_3  (hit_flags)
 *   [EAX+0x60] = param_4  (mask)
 */
void FUN_0005e0d0(void *param_1, float *param_2, int param_3, int param_4)
{
  *(uint8_t *)((char *)param_1 + 0x4c) = 1;
  *(float *)((char *)param_1 + 0x50) = param_2[0];
  *(float *)((char *)param_1 + 0x54) = param_2[1];
  *(float *)((char *)param_1 + 0x58) = param_2[2];
  *(int *)((char *)param_1 + 0x5c) = param_3;
  *(int *)((char *)param_1 + 0x60) = param_4;
  return;
}

/* 0x005e760 — path_get_node
 * Returns a pointer to a node within the path state buffer, given a node index.
 *
 * Asserts node_index != NONE (-1) and 0 <= node_index < state->node_count
 * (short at state+0x80). Each node is 0x44 bytes, and the node array starts
 * at state+0x84.
 *
 * Disassembly-confirmed:
 *   param_1 (EDI) = path state pointer
 *   param_2 (SI)  = node_index (short, loaded as word ptr [EBP+0xc])
 *   return: MOVSX EAX,SI; IMUL EAX,EAX,0x44; LEA EAX,[EAX+EDI+0x84]
 */
char *path_get_node(char *param_1, short param_2)
{
  if (param_2 == -1) {
    display_assert("node_index != NONE", "c:\\halo\\SOURCE\\ai\\path.c", 0x611,
                   1);
    system_exit(-1);
  } else if (param_2 >= 0 && param_2 < *(short *)(param_1 + 0x80)) {
    goto done;
  }
  display_assert("(node_index >= 0) && (node_index < state->node_count)",
                 "c:\\halo\\SOURCE\\ai\\path.c", 0x612, 1);
  system_exit(-1);
done:
  return param_1 + (int)param_2 * 0x44 + 0x84;
}

/* 0x005e7e0 — path_hash_lookup
 * Looks up a node in the path state hash table by key.
 *
 * Computes a starting hash slot from (param_2 & 0x1ff) << 3, then probes the
 * hash table at state+0x1208a (array of shorts, 0x1000 entries). For each
 * non-NONE slot, checks if the node's key (at node_base + 0x8 = state +
 * node_index * 0x44 + 0x8c) matches param_2. Returns the matching node index
 * (short in AX), or -1 if not found.
 *
 * Disassembly-confirmed:
 *   ECX = hash slot index (12-bit, masked with 0xfff)
 *   AX  = hash table entry (short, node index or -1)
 *   EDI = sign-extended AX for node key comparison
 *   Loop: MOVSX EAX,CX; MOV AX,[EDX+EAX*2+0x1208a]; INC ECX; AND ECX,0xfff
 */
short path_node_from_hash_table(char *param_1, unsigned int param_2)
{
  unsigned int slot;
  short sVar1;

  slot = (param_2 & 0x1ff) << 3;
  do {
    sVar1 = *(short *)(param_1 + (short)slot * 2 + 0x1208a);
    slot = (slot + 1) & 0xfff;
  } while (sVar1 != -1 &&
           *(unsigned int *)(param_1 + (int)sVar1 * 0x44 + 0x8c) != param_2);
  return sVar1;
}

/* 0x005e830 — path ray-cast clearance check
 * Casts a ray from param_2 toward param_4 using the BSP collision tree at
 * param_1+0xb0.  Returns 1 (clear) if the ray-cast fails, the hit fraction
 * is >= 1.0, or the remaining distance after the hit is below a threshold.
 * Returns 0 otherwise (path is blocked).
 *
 * Disassembly-confirmed:
 *   ESI = param_4[0], EDI = param_4[1], [EBP-0x14] = param_4[2]  (saved dest)
 *   [EBP-0x10] = param_4[0] - param_2[0]  (delta.x)
 *   [EBP-0x0c] = param_4[1] - param_2[1]  (delta.y)
 *   [EBP-0x08] = param_4[2] - param_2[2]  (delta.z)
 *   tag_block_get_element(param_1+0xb0, 0, 0x60) -> bsp element
 *   collision_bsp_test_vector(1, bsp, 0, 0, param_2, &delta, FLT_MAX,
 * result_buf) -> ray cast Condition: (1.0 - t)^2 * dist_sq < 0.1  => clear
 * (return 1) param_5 receives the result byte; param_6 receives param_4 copy
 * (dest pos)
 */
char path_3d_available(int param_1, int *param_2, int param_3, int *param_4,
                       unsigned char *param_5, float *param_6)
{
  char cVar3;
  unsigned char uVar5;
  float local_438[264];
  float local_18;
  float delta[3];
  unsigned char local_5;

  local_18 = *((float *)param_4 + 2);
  delta[0] = *(float *)param_4 - *(float *)param_2;
  uVar5 = 0;
  local_5 = 0;
  delta[1] = *((float *)param_4 + 1) - *((float *)param_2 + 1);
  delta[2] = *((float *)param_4 + 2) - *((float *)param_2 + 2);
  cVar3 = ((char (*)(int, void *, short, int, float *, float *, float,
                     float *))0x149480)(
    1, tag_block_get_element((char *)param_1 + 0xb0, 0, 0x60), 0, 0,
    (float *)param_2, delta, 3.4028235e+38f, local_438);
  if (cVar3 == '\0' || local_438[0] >= *(float *)0x2533c8 ||
      (*(float *)0x2533c8 - local_438[0]) *
          (*(float *)0x2533c8 - local_438[0]) *
          (delta[1] * delta[1] + delta[0] * delta[0] + delta[2] * delta[2]) <
        *(float *)0x25496c) {
    uVar5 = 1;
    local_5 = 1;
  }
  if (param_5 != (unsigned char *)0) {
    *param_5 = local_5;
  }
  if (param_6 != (float *)0) {
    *param_6 = *(float *)param_4;
    param_6[1] = *((float *)param_4 + 1);
    param_6[2] = local_18;
  }
  return (char)uVar5;
}

/* 0x005e920 — path_find_initial
 * Builds an initial navigation state record from a source position.
 *
 * Zeroes a 0x5c-byte output struct, then calls path_3d_available to perform a
 * pathfinding query. If path_3d_available succeeds, the output struct is
 * populated with the destination position (from param_4), a result vector from
 * the query, and various flags/sentinel values. Returns 1 on success, 0 on
 * failure.
 *
 * Output struct layout (ESI = param_5):
 *   [+0x00] = 1              (valid flag, byte)
 *   [+0x04] = param_4[0]     (destination position x)
 *   [+0x08] = param_4[1]     (destination position y)
 *   [+0x0c] = param_4[2]     (destination position z)
 *   [+0x10] = 0xFFFFFFFF     (sentinel)
 *   [+0x14] = 0x00000000     (cleared)
 *   [+0x18] = local_byte     (byte from path_3d_available output)
 *   [+0x19] = 1              (byte flag)
 *   [+0x1a] = 0              (byte flag)
 *   [+0x1c] = 0xFFFFFFFF     (sentinel)
 *   [+0x20] = local_vec[0]   (result vector x)
 *   [+0x24] = local_vec[1]   (result vector y)
 *   [+0x28] = local_vec[2]   (result vector z)
 */
char path_3d_build_path(int param_1, int *param_2, int param_3, int *param_4,
                        char *param_5)
{
  char result;
  float local_vec[3];
  uint8_t local_byte;

  csmemset(param_5, 0, 0x5c);
  result = path_3d_available(param_1, param_2, param_3, param_4, &local_byte,
                             local_vec);
  if (result != 0) {
    *(float *)(param_5 + 0x20) = local_vec[0];
    *(float *)(param_5 + 0x24) = local_vec[1];
    *(float *)(param_5 + 0x28) = local_vec[2];
    *(uint8_t *)(param_5 + 0x19) = 1;
    *(int *)(param_5 + 0x1c) = -1;
    *(uint8_t *)(param_5 + 0x1a) = 0;
    *(uint8_t *)(param_5 + 0x18) = local_byte;
    *(int *)(param_5 + 0x04) = param_4[0];
    *(int *)(param_5 + 0x08) = param_4[1];
    *(int *)(param_5 + 0x0c) = param_4[2];
    *(int *)(param_5 + 0x10) = -1;
    *(int *)(param_5 + 0x14) = 0;
    *(uint8_t *)param_5 = 1;
  }
  return *param_5;
}

/* 0x005eae0 — path_build_steps
 * Builds the step list for a path from the traversal node graph.
 *
 * Walks backward through the node chain (via parent links at node+0x02)
 * collecting raw steps (datum_ref + entry_point) indexed by depth.
 * Then applies smoothing (FUN_000633b0) and obstacle avoidance (FUN_00061750)
 * to produce the final step list stored in nav_state_out.
 *
 * nav_state_out layout (0x5c bytes):
 *   [+0x00] = valid (byte)
 *   [+0x04] = destination position (3 floats)
 *   [+0x10] = datum ref
 *   [+0x14] = distance
 *   [+0x18] = all_nodes_encountered flag (byte)
 *   [+0x19] = step_count (byte)
 *   [+0x1a] = zero (byte)
 *   [+0x1c] = step array (step_count * 16 bytes)
 *
 * Each step is 16 bytes: datum_ref(4) + position(12).
 *
 * Returns: nav_state_out[0] (valid flag byte).
 */
char path_state_build_path(unsigned int path_buf, unsigned int *nav_state_out)
{
  unsigned int *puVar9;
  unsigned int *puVar10;
  int iVar6;
  int iVar8;
  int node_ptr;
  short sVar4;
  short sVar5;
  char cVar3;
  char all_nodes_flag;
  unsigned int raw_steps[256]; /* 64 entries * 4 dwords = 0x400 bytes */
  unsigned int final_steps[16]; /* 4 entries * 4 dwords = 0x40 bytes */
  unsigned int smooth_steps[16]; /* 4 entries * 4 dwords = 0x40 bytes */
  unsigned int prev_node_index;
  int prev_node_ptr;
  unsigned int cur_index;
  int final_step_count;
  int raw_step_count;
  int smooth_step_count;

  puVar10 = nav_state_out;
  if (*(int *)(path_buf + 0x48) != 0) {
    *(unsigned short *)(*(int *)(path_buf + 0x48) + 0x12) = 0;
  }
  *(unsigned char *)nav_state_out = 0;

  if (*(char *)(path_buf + 0x4c) == '\0') {
    if (*(int *)(path_buf + 0x48) != 0) {
      *(unsigned short *)(*(int *)(path_buf + 0x48) + 0x12) = 1;
    }
    goto LAB_0005ef13;
  }

  cur_index = path_node_from_hash_table((char *)path_buf, *(unsigned int *)(path_buf + 0x5c));
  if ((short)cur_index == -1) {
    if (*(float *)(path_buf + 0x6c) < *(float *)(path_buf + 0x60)) {
      cur_index = (unsigned int)*(unsigned short *)(path_buf + 0x68);
      iVar6 = (int)path_get_node((char *)path_buf, cur_index);
      puVar10[1] = *(unsigned int *)(path_buf + 0x74);
      puVar10[2] = *(unsigned int *)(path_buf + 0x78);
      puVar10[3] = *(unsigned int *)(path_buf + 0x7c);
      puVar10[4] = *(unsigned int *)(iVar6 + 8);
      puVar10[5] = *(unsigned int *)(path_buf + 0x6c);
      goto LAB_0005eb88;
    }
  } else {
    iVar6 = (int)path_get_node((char *)path_buf, cur_index);
    /* memcpy 5 dwords from path_buf+0x50 to nav_state_out+0x04 */
    puVar9 = (unsigned int *)(path_buf + 0x50);
    puVar10 = nav_state_out + 1;
    for (iVar8 = 5; iVar8 != 0; iVar8--) {
      *puVar10 = *puVar9;
      puVar10++;
      puVar9++;
    }
    nav_state_out[5] = 0;
    puVar10 = nav_state_out;
LAB_0005eb88:
    if ((short)cur_index != -1) {
      int depth_plus_one = *(short *)(iVar6 + 0x2e) + 1;
      smooth_step_count = 0;
      final_step_count = 0;
      all_nodes_flag = 1;
      prev_node_index = 0xffffffff;
      prev_node_ptr = 0;
      raw_step_count = 0x40;
      if (depth_plus_one < 0x41) {
        raw_step_count = depth_plus_one;
      }

      do {
        unsigned int next_index;
        int depth;

        node_ptr = (int)path_get_node((char *)path_buf, cur_index);
        sVar4 = *(short *)(node_ptr + 0x2e);

        if (sVar4 < 0x40) {

          if (sVar4 < 0 || sVar4 >= (short)raw_step_count) {
            display_assert(
                "(node->depth >= 0) && (node->depth < raw_step_count)",
                "c:\\halo\\SOURCE\\ai\\path.c", 0x1e8, 1);
            system_exit(-1);
          }

          raw_steps[*(short *)(node_ptr + 0x2e) * 4] =
              *(unsigned int *)(node_ptr + 8);
          depth = (int)*(short *)(node_ptr + 0x2e);

          if ((short)prev_node_index == -1) {
            /* First node: copy destination from nav_state_out */
            raw_steps[depth * 4 + 1] = puVar10[1];
            raw_steps[depth * 4 + 3] = puVar10[3];
            raw_steps[depth * 4 + 2] = puVar10[2];
          } else {
            if (depth != *(short *)(prev_node_ptr + 0x2e) - 1) {
              display_assert("node->depth == child_node->depth - 1",
                             "c:\\halo\\SOURCE\\ai\\path.c", 0x1f0, 1);
              system_exit(-1);
            }
            depth = (int)*(short *)(node_ptr + 0x2e);
            raw_steps[depth * 4 + 1] =
                *(unsigned int *)(prev_node_ptr + 0xc);
            raw_steps[depth * 4 + 2] =
                *(unsigned int *)(prev_node_ptr + 0x10);
            raw_steps[depth * 4 + 3] =
                *(unsigned int *)(prev_node_ptr + 0x14);
          }
        } else {
          all_nodes_flag = 0;
        }

        prev_node_index = cur_index;
        next_index = (unsigned int)*(unsigned short *)(node_ptr + 2);
        prev_node_ptr = node_ptr;
        cur_index = next_index;
      } while (*(unsigned short *)(node_ptr + 2) != 0xffff);

      sVar4 = (short)prev_node_index;
      cur_index = (unsigned int)*(unsigned short *)(node_ptr + 2);

      if (sVar4 == -1) {
        display_assert("child_node_index != NONE",
                       "c:\\halo\\SOURCE\\ai\\path.c", 0x1fb, 1);
        system_exit(-1);
      }
      if (*(short *)(node_ptr + 0x2e) != 0) {
        display_assert("child_node->depth == 0",
                       "c:\\halo\\SOURCE\\ai\\path.c", 0x1fc, 1);
        system_exit(-1);
      }

      sVar4 = game_connection();
      iVar6 = raw_step_count;
      if (sVar4 == 0 && *(char *)0x5ac9d0 != '\0') {
        smooth_step_count = 4;
        if ((short)raw_step_count < 5) {
          smooth_step_count = raw_step_count;
        }
        csmemcpy(smooth_steps, raw_steps,
                 (int)(short)smooth_step_count << 4);
      } else {
        FUN_000633b0(path_buf, raw_step_count, raw_steps,
                     &smooth_step_count, smooth_steps, &all_nodes_flag);
        iVar6 = raw_step_count;
      }

      sVar4 = (short)iVar6;
      sVar5 = game_connection();
      if (sVar5 == 0 && *(char *)0x5ac9cf != '\0') {
        final_step_count = smooth_step_count;
        if (4 < (short)smooth_step_count) {
          final_step_count = 4;
        }
        csmemcpy(final_steps, smooth_steps,
                 (int)(short)final_step_count << 4);
LAB_0005ede3:
        *(char *)((char *)puVar10 + 0x19) = (char)final_step_count;
        *(char *)(puVar10 + 6) = all_nodes_flag;
        *(unsigned char *)puVar10 = 1;
        *(char *)((char *)puVar10 + 0x1a) = 0;
        csmemcpy(puVar10 + 7, final_steps,
                 (int)(short)final_step_count << 4);

        puVar9 = nav_state_out;
        if (*(char *)(puVar10 + 6) != '\0') {
          cVar3 = *(char *)((char *)puVar10 + 0x19);
          puVar10[1] = puVar10[(int)cVar3 * 4 + 4];
          puVar10[2] = puVar10[(int)cVar3 * 4 + 5];
          puVar10[3] = puVar10[(int)cVar3 * 4 + 6];
          nav_state_out[4] = puVar10[(int)cVar3 * 4 + 3];
          sVar4 = (short)raw_step_count;
          *(float *)(puVar9 + 5) = FUN_0001ad60(
              (float *)(puVar10 + 1), (float *)(path_buf + 0x50));
          puVar10 = puVar9;
        }

        if (*(int *)(path_buf + 0x48) != 0) {
          *(unsigned short *)(*(int *)(path_buf + 0x48) + 0x12) = 5;
        }
      } else {
        cVar3 = FUN_00061750(path_buf, smooth_step_count, smooth_steps,
                             &final_step_count, final_steps,
                             &all_nodes_flag);
        if (*(int *)(path_buf + 0x48) == 0) {
          if (cVar3 != '\0') goto LAB_0005ede3;
        } else {
          if (cVar3 != '\0') goto LAB_0005ede3;
          *(unsigned short *)(*(int *)(path_buf + 0x48) + 0x12) = 4;
        }
      }

      /* Debug: store raw, smooth, and final steps */
      if (*(int *)(path_buf + 0x48) != 0) {
        *(short *)(*(int *)(path_buf + 0x48) + 0x140fc) = sVar4;
        csmemcpy((void *)(*(int *)(path_buf + 0x48) + 0x14100), raw_steps,
                 (int)sVar4 << 4);
        *(short *)(*(int *)(path_buf + 0x48) + 0x14500) =
            (short)smooth_step_count;
        csmemcpy((void *)(*(int *)(path_buf + 0x48) + 0x14504), smooth_steps,
                 (int)(short)smooth_step_count << 4);
        *(short *)(*(int *)(path_buf + 0x48) + 0x14544) =
            (short)final_step_count;
        csmemcpy((void *)(*(int *)(path_buf + 0x48) + 0x14548), final_steps,
                 (int)(short)final_step_count << 4);
      }
      goto LAB_0005ef13;
    }
  }

  /* Neither branch produced a valid path */
  if (*(int *)(path_buf + 0x48) != 0) {
    *(unsigned short *)(*(int *)(path_buf + 0x48) + 0x12) =
        (unsigned short)(*(short *)(path_buf + 0x68) != -1) + 2;
  }

LAB_0005ef13:
  if (*(int *)(path_buf + 0x48) == 0) {
    return *(char *)puVar10;
  }

  /* Copy nav_state_out (0x5c bytes = 0x17 dwords) into debug buffer */
  puVar9 = (unsigned int *)(*(int *)(path_buf + 0x48) + 0x140a0);
  for (iVar6 = 0x17; iVar6 != 0; iVar6--) {
    *puVar9 = *puVar10;
    puVar10++;
    puVar9++;
  }

  if (*(short *)(*(int *)(path_buf + 0x48) + 0x12) != 5) {
    *(char *)(*(int *)(path_buf + 0x48) + 0xd) = 1;
  }
  if (*(short *)(*(int *)(path_buf + 0x48) + 0x12) == 0) {
    display_assert(
        "state->debug->path_build_result != _path_build_result_none",
        "c:\\halo\\SOURCE\\ai\\path.c", 0x265, 1);
    system_exit(-1);
    return *(char *)nav_state_out;
  }
  return *(char *)nav_state_out;
}

/* 0x005ff70 — path traverse and debug snapshot
 * Initializes a path traverse operation on a path buffer, then optionally
 * copies the resulting state into a debug record.
 *
 * Increments one of two global 16-bit counters depending on a flag at +0x4c
 * (obstacle_valid). Clears the node list, resets distance fields, calls
 * FUN_0005ef80 (@edi) to set up the initial path node. If that succeeds,
 * calls FUN_0005f740 to perform the full traverse. If a debug record exists
 * at +0x48, copies the entire path buffer into it, stores the BSP index, and
 * asserts the traverse result is non-zero (not _path_traverse_result_none).
 * If the result is not 5, marks the debug record as needing attention.
 *
 * Returns: char (0 = failed/skipped, nonzero = traverse result from
 * FUN_0005f740)
 */
char FUN_0005ff70(unsigned int *param_1)
{
  char cVar1;
  short uVar2;
  unsigned int *puVar4;
  unsigned int *puVar5;
  int iVar3;
  char local_5;

  local_5 = 0;
  if (*(char *)((char *)param_1 + 0x4c) != '\0') {
    (*(short *)0x5ac7f4)++;
  } else {
    (*(short *)0x5ac76c)++;
  }
  *(short *)((char *)param_1 + 0x80) = 0;
  *(short *)((char *)param_1 + 0x11084) = 1;
  csmemset((char *)param_1 + 0x1208a, -1, 0x2000);
  *(unsigned int *)((char *)param_1 + 0x6c) = 0x7f7fffff;
  *(unsigned int *)((char *)param_1 + 0x70) = 0x7f7fffff;
  *(short *)((char *)param_1 + 0x68) = (short)0xffff;
  if (*(unsigned int *)((char *)param_1 + 0x48) != 0) {
    *(short *)(*(unsigned int *)((char *)param_1 + 0x48) + 0x10) = 0;
  }
  cVar1 = FUN_0005ef80(param_1);
  if (cVar1 != '\0') {
    local_5 = FUN_0005f740(param_1);
  } else {
    if (*(unsigned int *)((char *)param_1 + 0x48) != 0) {
      *(short *)(*(unsigned int *)((char *)param_1 + 0x48) + 0x10) = 1;
    }
  }
  if (*(unsigned int *)((char *)param_1 + 0x48) != 0) {
    puVar4 = param_1;
    puVar5 = (unsigned int *)(*(unsigned int *)((char *)param_1 + 0x48) + 0x14);
    for (iVar3 = 0x5023; iVar3 != 0; iVar3 = iVar3 - 1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    uVar2 = global_structure_bsp_index_get();
    *(short *)(*(unsigned int *)((char *)param_1 + 0x48) + 0xe) = uVar2;
    if (*(short *)(*(unsigned int *)((char *)param_1 + 0x48) + 0x10) == 0) {
      display_assert(
        "state->debug->path_traverse_result != _path_traverse_result_none",
        "c:\\halo\\SOURCE\\ai\\path.c", 0x32d, 1);
      system_exit(-1);
    }
    if (*(short *)(*(unsigned int *)((char *)param_1 + 0x48) + 0x10) != 5) {
      *(char *)(*(unsigned int *)((char *)param_1 + 0x48) + 0xd) = 1;
      return local_5;
    }
  }
  return local_5;
}
/* --- path.obj batch drafts (2026-07-26) --- */

/* 0x5e150 */
void path_heap_bubble_up(void)
{
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

  /* cmp (int16_t)ebx, 0x400 -> jle 0x5e187 */
  display_assert((char *)0x0025e06c, (char *)0x0025e0ac, 1258, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 0x400 -> jl 0x5e1cf */
  display_assert((char *)0x0025e034, (char *)0x0025e0ac, 1263, 0);
  system_exit(0);
  display_assert((char *)0x0025dff0, (char *)0x0025e0ac, 1264, 0);
  system_exit(0);
  /* cmp (int16_t)ebx, 1 -> jle 0x5e308 */
  /* cmp (int16_t)ecx, 0x400 -> jl 0x5e264 */
  display_assert((char *)0x0025dfa8, (char *)0x0025e0ac, 1279, 0);
  system_exit(0);
  display_assert((char *)0x0025df60, (char *)0x0025e0ac, 1280, 0);
  system_exit(0);
  /* relift: cmp word ptr [edx + 0xb0], (int16_t)eax -> je 0x5e2d1 */
  display_assert((char *)0x0025df08, (char *)0x0025e0ac, 1281, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp - 0xc], (int16_t)eax -> jge 0x5e305 */

  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)ebp;
}

/* 0x5e330 */
void path_heap_bubble_down(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp (int16_t)edi, 1 -> jl 0x5e348 */
  /* cmp (int16_t)edi, 0x400 -> jle 0x5e368 */
  display_assert((char *)0x0025e06c, (char *)0x0025e0ac, 1316, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 0x400 -> jl 0x5e3b0 */
  display_assert((char *)0x0025e034, (char *)0x0025e0ac, 1321, 0);
  system_exit(0);
  display_assert((char *)0x0025dff0, (char *)0x0025e0ac, 1322, 0);
  system_exit(0);
  /* relift: cmp (int16_t)esi, word ptr [ebx + 0x11084] -> jge 0x5e4ed */
  /* cmp (int16_t)edi, 0x400 -> jl 0x5e460 */
  display_assert((char *)0x0025e160, (char *)0x0025e0ac, 1342, 0);
  system_exit(0);
  display_assert((char *)0x0025e118, (char *)0x0025e0ac, 1343, 0);
  system_exit(0);
  /* relift: cmp word ptr [eax + 0xb0], (int16_t)ecx -> je 0x5e4c6 */
  display_assert((char *)0x0025e0c8, (char *)0x0025e0ac, 1344, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [ebp - 4] -> jge 0x5e4d8 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x5e560 */
void path_heap_pop_cheapest_node(void)
{
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp word ptr [ebx + 0x11084], (int16_t)esi -> jge 0x5e59c */
  display_assert((char *)0x0025e238, (char *)0x0025e0ac, 1394, esi);
  system_exit(0);
  /* relift: cmp word ptr [ebx + 0x11084], (int16_t)esi -> jle 0x5e66f */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x5e5b5 */
  /* cmp (int16_t)edi, 0x400 -> jl 0x5e5d4 */
  display_assert((char *)0x0025e034, (char *)0x0025e0ac, 1399, esi);
  system_exit(0);
  display_assert((char *)0x0025e208, (char *)0x0025e0ac, 1401, 0);
  system_exit(0);
  /* relift: cmp (int16_t)ecx, word ptr [ebx + 0x1108c] -> je 0x5e638 */
  display_assert((char *)0x0025e1a8, (char *)0x0025e0ac, 1402, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 1 -> jle 0x5e66f */
  path_heap_bubble_down();

  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x5e680 */
void path_heap_insert(void)
{
  int edi = 0;

  /* relift: cmp word ptr [edi + 0x11084], 1 -> jge 0x5e6b0 */
  display_assert((char *)0x0025e238, (char *)0x0025e0ac, 1428, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 0x400 -> jge 0x5e6ec */
  path_heap_bubble_up();
  error(0, (char *)0x0025e250);

  (void)edi;
}

/* 0x5e700 */
void FUN_0005e700(void)
{
  int eax = 0;
  int ecx = 0;

  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)ecx, 8 -> je 0x5e758 */
  breakable_surfaces_get_bsp_surface_data();

  (void)eax;
  (void)ecx;
}

/* 0x5e9b0 */
char path_state_approach_point(void *path_state, float *fp_results, int fp_count, char *out_byte, char *out_dest)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  path_node_from_hash_table((char *)(uintptr_t)esi, ebx);
  /* cmp (int16_t)eax, 0xffff -> je 0x5eace */
  path_get_node((char *)(uintptr_t)esi, 0);
  /* cmp (int16_t)eax, 0xffff -> je 0x5ea38 */
  path_get_node((char *)(uintptr_t)esi, 0);
  FUN_000639e0(0, ecx, (float *)(uintptr_t)eax, 0, (float *)(uintptr_t)eax, 0, (char *)0);
  /* test (char)eax, (char)eax -> jne 0x5ea38 */
  path_get_node((char *)(uintptr_t)esi, 0);
  /* cmp (int16_t)eax, 0xffff -> jne 0x5e9f0 */
  /* test ebx, ebx -> jne 0x5ea5f */
  display_assert((char *)0x0025e2e4, (char *)0x0025e0ac, 301, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x5ea89 */
  display_assert((char *)0x0025e2cc, (char *)0x0025e0ac, 302, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi + 2], -1 -> jne 0x5eaaf */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x5ef80 */
char FUN_0005ef80(unsigned int *path_buf)
{
  int eax = 0;
  int ecx = 0;
  int edi = 0;

  /* cmp eax, -1 -> je 0x5f086 */
  /* relift: relift: fcomp dword ptr [0x25ddb8] */
  /* test (char)eax, 0x41 -> jne 0x5f086 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test ecx, ecx -> jl 0x5efca */
  /* relift: cmp ecx, dword ptr [eax + 0x3c] -> jl 0x5efea */
  display_assert((char *)0x0025e4c0, (char *)0x0025e0ac, 689, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x5f08d */
  FUN_001d9068();
  error(0, (char *)0x0025e448);
  /* relift: cmp word ptr [edi + 0x80], 0 -> je 0x5f0c5 */
  display_assert((char *)0x0025e42c, (char *)0x0025e0ac, 716, 0);
  system_exit(0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test ecx, ecx -> jl 0x5f156 */
  /* relift: cmp ecx, dword ptr [eax + 0x3c] -> jl 0x5f176 */
  display_assert((char *)0x0025e3d0, (char *)0x0025e0ac, 739, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x5f1a1 */
  path_heap_insert();
  (void)ecx;
  (void)edi;
  return 0;
}

/* 0x5f1d0 */
void FUN_0005f1d0(void)
{
  tag_block_get_element((void *)0, 0, 0);
  collision_surface_find_closest_point2d(0, 0, 0, 0, (void *)0, (void *)0);
  collision_surface_project_point2d(0, 0, 0, 0, (void *)0, (void *)0);
}

/* 0x5f240 */
void build_path_edges_for_surface(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* relift: cmp edi, dword ptr [esi + 0x3c] -> jl 0x5f294 */
  display_assert((char *)0x0025e584, (char *)0x0025e0ac, 1496, 0);
  system_exit(0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 12);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 24);
  /* test eax, eax -> jl 0x5f30b */
  /* relift: cmp eax, dword ptr [ecx] -> jl 0x5f32b */
  display_assert((char *)0x0025e528, (char *)0x0025e0ac, 1518, 0);
  system_exit(0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 16);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 16);
  /* relift: cmp edi, dword ptr [eax + 4] -> jne 0x5f2ba */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x5f3c0 */
void closest_point_to_attractor(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x5f490 */
void path_attractor_weight(void)
{
  int esi = 0;

  closest_point_to_attractor();
  /* test esi, esi -> jne 0x5f53b */
  display_assert((char *)0x0025e5c4, (char *)0x0025e0ac, 1631, 0);
  system_exit(0);

  (void)esi;
}

/* 0x5f550 */
char path_state_estimated_distance(void *path_state, void *fp_element, int surface_index, float *result, float *opt_min_clearance, float *opt_out_vec)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  path_node_from_hash_table((char *)(uintptr_t)edi, eax);
  display_assert((char *)0x0025e5c4, (char *)0x0025e0ac, 334, 0);
  system_exit(0);
  /* cmp (int16_t)ebx, -1 -> je 0x5f706 */
  path_get_node((char *)(uintptr_t)edi, 0);
  closest_point_to_attractor();
  /* test (char)eax, 0x41 -> jne 0x5f63c */
  /* test eax, eax -> je 0x5f647 */
  path_get_node((char *)(uintptr_t)edi, 0);
  /* cmp (int16_t)esi, -1 -> jne 0x5f670 */
  /* cmp (int16_t)ebx, (int16_t)esi -> je 0x5f6cd */
  path_get_node((char *)(uintptr_t)edi, 0);
  /* cmp (int16_t)ebx, -1 -> jne 0x5f6d2 */
  normalize3d((float *)0);
  /* test eax, eax -> je 0x5f713 */
  /* test eax, eax -> je 0x5f730 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x5f740 */
char FUN_0005f740(unsigned int *path_buf)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test (char)eax, 0x41 -> jne 0x5f765 */
  path_heap_pop_cheapest_node();
  path_get_node((char *)(uintptr_t)edi, 0);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  /* test ecx, ecx -> jl 0x5f7be */
  /* relift: cmp ecx, dword ptr [eax + 0x3c] -> jl 0x5f7de */
  display_assert((char *)0x0025e888, (char *)0x0025e0ac, 861, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x5f829 */
  /* relift: cmp edx, dword ptr [edi + 0x5c] -> je 0x5feff */
  /* test (char)eax, 0x41 -> jne 0x5f809 */
  /* test (char)eax, 0x41 -> je 0x5ff22 */
  build_path_edges_for_surface();
  /* test (int16_t)eax, (int16_t)eax -> jle 0x5fed3 */
  /* test (char)eax, 0x40 -> jne 0x5f87b */
  /* test (char)ecx, (char)ecx -> jne 0x5f8da */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)eax, 8 -> je 0x5f8da */
  breakable_surfaces_get_bsp_surface_data();
  /* test (char)eax, (char)eax -> je 0x5febd */
  /* test (char)eax, 0x41 -> jne 0x5f9ef */
  /* test (char)eax, 0x41 -> jne 0x5f9ef */
  /* test (char)eax, 0x41 -> jne 0x5f9d1 */
  path_attractor_weight();
  /* test (char)eax, 0x41 -> je 0x5fa6c */
  /* test (char)eax, 1 -> je 0x5fae8 */
  display_assert((char *)0x0025e828, (char *)0x0025e0ac, 1005, 0);
  system_exit(0);
  FUN_001d9068();
  /* test (char)eax, (char)eax -> jne 0x5febd */
  error(0, (char *)0x0025e7d8);
  /* test (char)eax, (char)eax -> je 0x5fb4e */
  /* test (char)eax, 0x41 -> je 0x5febd */
  /* cmp (int16_t)esi, -1 -> je 0x5fba6 */
  path_get_node((char *)(uintptr_t)edi, 0);
  /* cmp (int16_t)esi, -1 -> jne 0x5fb73 */
  /* cmp (int16_t)eax, 0x400 -> jge 0x5fd96 */
  /* relift: cmp word ptr [ebp - 0x10], -1 -> je 0x5febd */
  path_get_node((char *)(uintptr_t)edi, 0);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  /* test ecx, ecx -> jl 0x5fc8a */
  /* relift: cmp ecx, dword ptr [eax + 0x3c] -> jl 0x5fcaa */
  display_assert((char *)0x0025e780, (char *)0x0025e0ac, 1126, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 0xffff -> jne 0x5fdb7 */
  path_heap_insert();
  /* relift: cmp dword ptr [ebp - 0x1c], ecx -> jge 0x5febd */
  /* cmp (int16_t)ebx, -1 -> jne 0x5fcfd */
  error(0, (char *)0x0025e744);
  /* relift: cmp (int16_t)ebx, word ptr [edi + 0x11084] -> jl 0x5fd2f */
  display_assert((char *)0x0025e708, (char *)0x0025e0ac, 1059, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi + ebx*4 + 0x11086], (int16_t)esi -> je 0x5fd5c */
  display_assert((char *)0x0025e6d4, (char *)0x0025e0ac, 1060, 0);
  system_exit(0);
  /* relift: cmp (int16_t)edx, word ptr [eax + 0x2c] -> je 0x5fbe1 */
  display_assert((char *)0x0025e680, (char *)0x0025e0ac, 1061, 0);
  system_exit(0);
  /* test eax, eax -> je 0x5febd */
  /* relift: cmp word ptr [eax + 0x10], 0 -> jne 0x5febd */
  /* cmp (int16_t)eax, 1 -> jl 0x5fdc6 */
  /* relift: cmp (int16_t)eax, word ptr [edi + 0x11084] -> jl 0x5fde6 */
  display_assert((char *)0x0025e630, (char *)0x0025e0ac, 1137, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp - 0x1c], edx -> jle 0x5fe17 */
  display_assert((char *)0x0025e5d8, (char *)0x0025e0ac, 1138, 0);
  system_exit(0);
  path_heap_bubble_up();
  /* test (char)eax, (char)eax -> je 0x5febd */
  FUN_0005f1d0();
  path_heap_pop_cheapest_node();
  /* test eax, eax -> je 0x5ff36 */
  /* relift: cmp word ptr [eax + 0x10], 0 -> jne 0x5ff36 */
  /* test eax, eax -> je 0x5ff36 */
  /* relift: cmp word ptr [eax + 0x10], 0 -> jne 0x5ff36 */
  /* test (char)eax, (char)eax -> je 0x5ff68 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x60070 — obstacle disc node accessor (path.h:396) */
void *FUN_00060070(void *obstacles, int16_t disc_index)
{
  int16_t disc_count;

  disc_count = *(int16_t *)((char *)obstacles + 2);
  if (disc_index < 0 || disc_index >= disc_count || disc_count > 0x80) {
    display_assert(
        "disc_index>=0 && disc_index<obstacles->disc_count && "
        "obstacles->disc_count<=MAXIMUM_OBSTACLE_DISCS",
        "c:\\halo\\source\\ai\\path.h", 396, 1);
    system_exit(-1);
  }
  return (char *)obstacles + (int)disc_index * 24 + 8;
}

/* 0x600c0 — disc field at node+2, or -1 for invalid index */
int16_t FUN_000600c0(void *obstacles, int16_t disc_index)
{
  void *node;

  if (disc_index == -1)
    return -1;
  node = FUN_00060070(obstacles, disc_index);
  return *(int16_t *)((char *)node + 2);
}

/* 0x600f0 — path step node accessor (path_obstacle_avoidance.c:40) */
void *FUN_000600f0(void *path, int16_t step_index)
{
  int16_t step_count;

  step_count = *(int16_t *)((char *)path + 0x2c);
  if (step_index < 0 || step_index >= step_count || step_count > 0x80) {
    display_assert(
        "step_index>=0 && step_index<path->step_count && "
        "path->step_count<=MAXIMUM_PATH_STEPS",
        "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 40, 1);
    system_exit(-1);
  }
  return (char *)path + (int)step_index * 40 + 0x30;
}

/* 0x601a0 — parent heap index (path_obstacle_avoidance.c:57) */
int FUN_000601a0(int16_t heap_index)
{
  if (heap_index <= 0) {
    display_assert("heap_index>0",
                   "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 57, 1);
    system_exit(-1);
  }
  return ((int)heap_index - 1) / 2;
}

/* 0x601e0 — binary-heap left child index */
int FUN_000601e0(int heap_index)
{
  return heap_index * 2 + 1;
}

/* 0x601f0 — binary-heap right child index */
int FUN_000601f0(int heap_index)
{
  return heap_index * 2 + 2;
}

/* 0x60140 */
void FUN_00060140(void)
{
  int esi = 0;

  /* cmp (int16_t)esi, (int16_t)eax -> jge 0x60163 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x6018f */
  display_assert((char *)0x0025ea40, (char *)0x0025ea14, 49, 0);
  system_exit(0);

  (void)esi;
}

/* 0x60200 */
void FUN_00060200(void)
{
  int esi = 0;

  FUN_00060140();
  /* test (int16_t)esi, (int16_t)esi -> jl 0x6022b */
  /* cmp (int16_t)esi, (int16_t)eax -> jge 0x6022b */
  /* cmp (int16_t)eax, 0x80 -> jle 0x60248 */
  display_assert((char *)0x0025e9b0, (char *)0x0025ea14, 40, 0);
  system_exit(0);

  (void)esi;
}

/* 0x60260 */
void FUN_00060260(void)
{
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test (int16_t)eax, (int16_t)eax -> jle 0x60324 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x60288 */
  /* cmp (int16_t)esi, (int16_t)eax -> jge 0x60288 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x602a5 */
  display_assert((char *)0x0025ea40, (char *)0x0025ea14, 49, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x602c4 */
  /* cmp (int16_t)edi, (int16_t)eax -> jge 0x602c4 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x602e1 */
  display_assert((char *)0x0025e9b0, (char *)0x0025ea14, 40, 0);
  system_exit(0);
  error(edx, (char *)0x0025eab4);
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0x60278 */

  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x60330 */
void FUN_00060330(void)
{
  int ecx = 0;
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jg 0x6037a */
  display_assert((char *)0x0025eaa4, (char *)0x0025ea14, 57, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x60399 */
  /* cmp (int16_t)esi, (int16_t)eax -> jge 0x60399 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x603b6 */
  display_assert((char *)0x0025ea40, (char *)0x0025ea14, 49, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x603d5 */
  /* cmp (int16_t)esi, (int16_t)eax -> jge 0x603d5 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x603f2 */
  display_assert((char *)0x0025e9b0, (char *)0x0025ea14, 40, 0);
  system_exit(0);
  /* cmp (int16_t)ecx, (int16_t)eax -> jge 0x6041b */
  /* cmp (int16_t)eax, 0x80 -> jle 0x60438 */
  display_assert((char *)0x0025ea40, (char *)0x0025ea14, 49, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x60454 */
  /* cmp (int16_t)esi, (int16_t)eax -> jge 0x60454 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x60471 */
  display_assert((char *)0x0025e9b0, (char *)0x0025ea14, 40, 0);
  system_exit(0);
  error(0, (char *)0x0025eaec);
  error(0, (char *)0x0025eac4);
  FUN_00060260();

  (void)ecx;
  (void)esi;
}

/* 0x604e0 */
void FUN_000604e0(void)
{
  int ebx = 0;
  int ecx = 0;
  int edi = 0;

  /* test (int16_t)edi, (int16_t)edi -> jle 0x60667 */
  /* test (int16_t)edi, (int16_t)edi -> jg 0x60522 */
  display_assert((char *)0x0025eaa4, (char *)0x0025ea14, 57, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x60542 */
  /* cmp (int16_t)ebx, (int16_t)eax -> jge 0x60542 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x6055f */
  display_assert((char *)0x0025ea40, (char *)0x0025ea14, 49, 0);
  system_exit(0);
  /* cmp (int16_t)edi, (int16_t)eax -> jge 0x60588 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x605a5 */
  display_assert((char *)0x0025e9b0, (char *)0x0025ea14, 40, 0);
  system_exit(0);
  /* cmp (int16_t)eax, (int16_t)ecx -> jge 0x605cf */
  /* cmp (int16_t)ecx, 0x80 -> jle 0x605ec */
  display_assert((char *)0x0025ea40, (char *)0x0025ea14, 49, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x6060b */
  /* cmp (int16_t)edi, (int16_t)eax -> jge 0x6060b */
  /* cmp (int16_t)eax, 0x80 -> jle 0x6062b */
  display_assert((char *)0x0025e9b0, (char *)0x0025ea14, 40, 0);
  system_exit(0);

  (void)ebx;
  (void)ecx;
  (void)edi;
}

/* 0x60670 */
void FUN_00060670(void)
{
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp (int16_t)edi, word ptr [esi + 0x1430] -> jge 0x60909 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x606b7 */
  /* cmp (int16_t)edi, (int16_t)eax -> jge 0x606b7 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x606d4 */
  display_assert((char *)0x0025ea40, (char *)0x0025ea14, 49, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x606f3 */
  /* cmp (int16_t)edi, (int16_t)eax -> jge 0x606f3 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x60710 */
  display_assert((char *)0x0025e9b0, (char *)0x0025ea14, 40, 0);
  system_exit(0);
  /* cmp (int16_t)ebx, (int16_t)eax -> jge 0x60736 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x60753 */
  display_assert((char *)0x0025ea40, (char *)0x0025ea14, 49, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x60772 */
  /* cmp (int16_t)edi, (int16_t)eax -> jge 0x60772 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x6078f */
  display_assert((char *)0x0025e9b0, (char *)0x0025ea14, 40, 0);
  system_exit(0);
  /* cmp (int16_t)ecx, (int16_t)eax -> jge 0x608ce */
  /* test (int16_t)ecx, (int16_t)ecx -> jl 0x607d2 */
  /* cmp (int16_t)ecx, (int16_t)eax -> jge 0x607d2 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x607ef */
  display_assert((char *)0x0025ea40, (char *)0x0025ea14, 49, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x6080f */
  /* cmp (int16_t)edi, (int16_t)eax -> jge 0x6080f */
  /* cmp (int16_t)eax, 0x80 -> jle 0x6082c */
  display_assert((char *)0x0025e9b0, (char *)0x0025ea14, 40, 0);
  system_exit(0);
  /* cmp (int16_t)ebx, (int16_t)eax -> jge 0x60859 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x60876 */
  display_assert((char *)0x0025ea40, (char *)0x0025ea14, 49, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x60895 */
  /* cmp (int16_t)edi, (int16_t)eax -> jge 0x60895 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x608b2 */
  display_assert((char *)0x0025e9b0, (char *)0x0025ea14, 40, 0);
  system_exit(0);
  /* cmp (int16_t)eax, (int16_t)edi -> je 0x60908 */

  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x60910 */
void FUN_00060910(void)
{
  int edi = 0;

  FUN_00060330();
  /* cmp (int16_t)edi, 0x80 -> jge 0x60967 */
  FUN_000600f0((void *)0, (int16_t)edi);
  FUN_000604e0();
  FUN_00060330();

  (void)edi;
}

/* 0x60970 */
void FUN_00060970(void)
{
  FUN_00060330();
  /* test (int16_t)eax, (int16_t)eax -> jle 0x609cc */
  FUN_00060670();
  FUN_00060330();
}

/* 0x609e0 */
void FUN_000609e0(void *path)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp word ptr [edi + 0x2c], 0 -> jle 0x60c37 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  collision_surface_project_point2d(0, 0, 0, 0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  collision_surface_project_point2d(0, 0, 0, 0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  /* relift: cmp word ptr [edi + 0x1e], (int16_t)ebx -> jne 0x60a50 */
  FUN_00189150(0, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  /* relift: cmp word ptr [edi + 0x1e], (int16_t)ebx -> jne 0x60a74 */
  FUN_00189150(0, (float *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)eax);
  csmemset((void *)(uintptr_t)ecx, 0, eax);
  /* cmp (int16_t)esi, (int16_t)ebx -> je 0x60b0f */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x60ac4 */
  /* cmp (int16_t)esi, (int16_t)eax -> jge 0x60ac4 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x60ae0 */
  display_assert((char *)0x0025e9b0, (char *)0x0025ea14, 40, 0);
  system_exit(0);
  /* cmp (int16_t)esi, (int16_t)ebx -> jne 0x60ab0 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x60b36 */
  /* cmp (int16_t)esi, (int16_t)eax -> jge 0x60b36 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x60b53 */
  display_assert((char *)0x0025e9b0, (char *)0x0025ea14, 40, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x60b86 */
  /* cmp (int16_t)eax, (int16_t)ecx -> jge 0x60b86 */
  /* cmp (int16_t)ecx, 0x80 -> jle 0x60ba6 */
  display_assert((char *)0x0025e9b0, (char *)0x0025ea14, 40, 0);
  system_exit(0);
  collision_surface_project_point2d(0, 0, 0, 0, (float *)(uintptr_t)eax, (float *)(uintptr_t)ecx);
  collision_surface_project_point2d(0, 0, 0, 0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)ecx);
  /* test eax, edx -> je 0x60bfd */
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)eax);
  /* relift: cmp word ptr [edi + 0x2c], 0x80 -> jge 0x60e96 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x60cd4 */
  /* cmp (int16_t)esi, (int16_t)eax -> jge 0x60cd4 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x60cf1 */
  display_assert((char *)0x0025e9b0, (char *)0x0025ea14, 40, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x18], (int16_t)eax -> jne 0x60d20 */
  /* relift: cmp byte ptr [esi + 0x1a], (char)ecx -> jne 0x60e91 */
  /* cmp (int16_t)esi, -1 -> jne 0x60cc0 */
  /* cmp (int16_t)eax, (int16_t)ecx -> jne 0x60dd6 */
  /* cmp (int16_t)ecx, -1 -> je 0x60dd6 */
  /* cmp (int16_t)eax, 0xffff -> je 0x60db7 */
  FUN_000600f0(path, (int16_t)esi);
  FUN_000600f0(path, (int16_t)esi);
  /* test (char)eax, 0x41 -> jne 0x60db4 */
  /* cmp (int16_t)eax, 0xffff -> jne 0x60dd6 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
