#include <stdint.h>
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

  cur_index = path_node_from_hash_table((char *)path_buf,
                                        *(unsigned int *)(path_buf + 0x5c));
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
            raw_steps[depth * 4 + 1] = *(unsigned int *)(prev_node_ptr + 0xc);
            raw_steps[depth * 4 + 2] = *(unsigned int *)(prev_node_ptr + 0x10);
            raw_steps[depth * 4 + 3] = *(unsigned int *)(prev_node_ptr + 0x14);
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
        display_assert("child_node->depth == 0", "c:\\halo\\SOURCE\\ai\\path.c",
                       0x1fc, 1);
        system_exit(-1);
      }

      sVar4 = game_connection();
      iVar6 = raw_step_count;
      if (sVar4 == 0 && *(char *)0x5ac9d0 != '\0') {
        smooth_step_count = 4;
        if ((short)raw_step_count < 5) {
          smooth_step_count = raw_step_count;
        }
        csmemcpy(smooth_steps, raw_steps, (int)(short)smooth_step_count << 4);
      } else {
        FUN_000633b0(path_buf, raw_step_count, raw_steps, &smooth_step_count,
                     smooth_steps, &all_nodes_flag);
        iVar6 = raw_step_count;
      }

      sVar4 = (short)iVar6;
      sVar5 = game_connection();
      if (sVar5 == 0 && *(char *)0x5ac9cf != '\0') {
        final_step_count = smooth_step_count;
        if (4 < (short)smooth_step_count) {
          final_step_count = 4;
        }
        csmemcpy(final_steps, smooth_steps, (int)(short)final_step_count << 4);
      LAB_0005ede3:
        *(char *)((char *)puVar10 + 0x19) = (char)final_step_count;
        *(char *)(puVar10 + 6) = all_nodes_flag;
        *(unsigned char *)puVar10 = 1;
        *(char *)((char *)puVar10 + 0x1a) = 0;
        csmemcpy(puVar10 + 7, final_steps, (int)(short)final_step_count << 4);

        puVar9 = nav_state_out;
        if (*(char *)(puVar10 + 6) != '\0') {
          cVar3 = *(char *)((char *)puVar10 + 0x19);
          puVar10[1] = puVar10[(int)cVar3 * 4 + 4];
          puVar10[2] = puVar10[(int)cVar3 * 4 + 5];
          puVar10[3] = puVar10[(int)cVar3 * 4 + 6];
          nav_state_out[4] = puVar10[(int)cVar3 * 4 + 3];
          sVar4 = (short)raw_step_count;
          *(float *)(puVar9 + 5) =
            FUN_0001ad60((float *)(puVar10 + 1), (float *)(path_buf + 0x50));
          puVar10 = puVar9;
        }

        if (*(int *)(path_buf + 0x48) != 0) {
          *(unsigned short *)(*(int *)(path_buf + 0x48) + 0x12) = 5;
        }
      } else {
        cVar3 = FUN_00061750(path_buf, smooth_step_count, smooth_steps,
                             &final_step_count, final_steps, &all_nodes_flag);
        if (*(int *)(path_buf + 0x48) == 0) {
          if (cVar3 != '\0')
            goto LAB_0005ede3;
        } else {
          if (cVar3 != '\0')
            goto LAB_0005ede3;
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
    display_assert("state->debug->path_build_result != _path_build_result_none",
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

/* path_heap_bubble_up (0x5e150) — readable C lift.
 * path@edi, heap_index@eax. */
void path_heap_bubble_up(void *path, int16_t heap_index)
{
  char *p;
  int16_t idx;
  int16_t node;
  int16_t cost;
  char *node_ptr;
  int16_t parent;
  int16_t parent_node;
  int16_t parent_cost;
  char *parent_ptr;

  p = (char *)path;
  idx = heap_index;
  if (idx < 1 || idx > 0x400) {
    display_assert((const char *)0x25e06c, (const char *)0x25e0ac, 0x4ea, 1);
    system_exit(-1);
  }
  node = *(int16_t *)(p + 0x11086 + (int)idx * 4);
  cost = *(int16_t *)(p + 0x11088 + (int)idx * 4);
  if (node < 0 || node >= 0x400) {
    display_assert((const char *)0x25e034, (const char *)0x25e0ac, 0x4ef, 1);
    system_exit(-1);
  }
  node_ptr = p + (int)node * 0x44;
  if (*(int16_t *)(node_ptr + 0xb0) != cost) {
    display_assert((const char *)0x25dff0, (const char *)0x25e0ac, 0x4f0, 1);
    system_exit(-1);
  }

  if (idx > 1) {
    for (;;) {
      parent = (int16_t)(idx >> 1);
      parent_node = *(int16_t *)(p + 0x11086 + (int)parent * 4);
      parent_cost = *(int16_t *)(p + 0x11088 + (int)parent * 4);
      if (parent_node < 0 || parent_node >= 0x400) {
        display_assert((const char *)0x25dfa8, (const char *)0x25e0ac, 0x4ff, 1);
        system_exit(-1);
      }
      parent_ptr = p + (int)parent_node * 0x44;
      if (*(int16_t *)(parent_ptr + 0xb4) != parent) {
        display_assert((const char *)0x25df60, (const char *)0x25e0ac, 0x500, 1);
        system_exit(-1);
      }
      if (*(int16_t *)(parent_ptr + 0xb0) != parent_cost) {
        display_assert((const char *)0x25df08, (const char *)0x25e0ac, 0x501, 1);
        system_exit(-1);
      }
      if (cost >= parent_cost)
        break;
      *(int16_t *)(p + 0x11086 + (int)idx * 4) = parent_node;
      *(int16_t *)(p + 0x11088 + (int)idx * 4) = parent_cost;
      *(int16_t *)(parent_ptr + 0xb4) = idx;
      idx = parent;
      if (parent <= 1)
        break;
    }
  }

  *(int16_t *)(p + 0x11086 + (int)idx * 4) = node;
  *(int16_t *)(p + 0x11088 + (int)idx * 4) = cost;
  *(int16_t *)(node_ptr + 0xb4) = idx;
}

/* path_heap_bubble_down (0x5e330) — readable C lift.
 * path@ebx, heap_index on stack. */
void path_heap_bubble_down(void *path, int16_t heap_index)
{
  char *p;
  int16_t idx;
  int16_t node;
  int16_t cost;
  char *node_ptr;
  int16_t best_idx;
  int16_t best_node;
  int16_t best_cost;
  int16_t child;
  int16_t child_i;
  int16_t child_node;
  int16_t child_cost;
  char *child_ptr;

  p = (char *)path;
  idx = heap_index;
  if (idx < 1 || idx > 0x400) {
    display_assert((const char *)0x25e06c, (const char *)0x25e0ac, 0x524, 1);
    system_exit(-1);
  }
  node = *(int16_t *)(p + 0x11086 + (int)idx * 4);
  cost = *(int16_t *)(p + 0x11088 + (int)idx * 4);
  if (node < 0 || node >= 0x400) {
    display_assert((const char *)0x25e034, (const char *)0x25e0ac, 0x529, 1);
    system_exit(-1);
  }
  node_ptr = p + (int)node * 0x44;
  if (*(int16_t *)(node_ptr + 0xb0) != cost) {
    display_assert((const char *)0x25dff0, (const char *)0x25e0ac, 0x52a, 1);
    system_exit(-1);
  }

  for (;;) {
    best_idx = idx;
    best_node = node;
    best_cost = cost;
    child = (int16_t)(idx << 1);
    for (child_i = 0; child_i < 2; child_i++) {
      if (child >= *(int16_t *)(p + 0x11084))
        break;
      child_node = *(int16_t *)(p + 0x11086 + (int)child * 4);
      child_cost = *(int16_t *)(p + 0x11088 + (int)child * 4);
      if (child_node < 0 || child_node >= 0x400) {
        display_assert((const char *)0x25e160, (const char *)0x25e0ac, 0x53e, 1);
        system_exit(-1);
      }
      child_ptr = p + (int)child_node * 0x44;
      if (*(int16_t *)(child_ptr + 0xb4) != child) {
        display_assert((const char *)0x25e118, (const char *)0x25e0ac, 0x53f, 1);
        system_exit(-1);
      }
      if (*(int16_t *)(child_ptr + 0xb0) != child_cost) {
        display_assert((const char *)0x25e0c8, (const char *)0x25e0ac, 0x540, 1);
        system_exit(-1);
      }
      if (child_cost < best_cost) {
        best_idx = child;
        best_node = child_node;
        best_cost = child_cost;
      }
      child = (int16_t)(child + 1);
    }
    if (best_idx == idx) {
      *(int16_t *)(p + 0x11086 + (int)idx * 4) = node;
      *(int16_t *)(p + 0x11088 + (int)idx * 4) = cost;
      *(int16_t *)(node_ptr + 0xb4) = idx;
      return;
    }
    *(int16_t *)(p + 0x11086 + (int)idx * 4) = best_node;
    *(int16_t *)(p + 0x11088 + (int)idx * 4) = best_cost;
    *(int16_t *)(p + (int)best_node * 0x44 + 0xb4) = idx;
    idx = best_idx;
  }
}


/* path_heap_pop_cheapest_node (0x5e560) — readable C lift. */
int16_t path_heap_pop_cheapest_node(void *path /* @<eax> */)
{
  int16_t result;
  int16_t count;
  char *node;

  result = -1;
  if (*(int16_t *)((char *)path + 0x11084) < 1) {
    display_assert((const char *)0x25e238, (const char *)0x25e0ac, 0x572, 1);
    system_exit(-1);
  }
  if (*(int16_t *)((char *)path + 0x11084) <= 1) {
    return result;
  }
  result = *(int16_t *)((char *)path + 0x1108a);
  if (result < 0 || result >= 0x400) {
    display_assert((const char *)0x25e034, (const char *)0x25e0ac, 0x577, 1);
    system_exit(-1);
  }
  node = (char *)path + (int)result * 0x44;
  if (*(int16_t *)(node + 0xb4) != 1) {
    display_assert((const char *)0x25e208, (const char *)0x25e0ac, 0x579, 1);
    system_exit(-1);
  }
  if (*(int16_t *)(node + 0xb0) != *(int16_t *)((char *)path + 0x1108c)) {
    display_assert((const char *)0x25e1a8, (const char *)0x25e0ac, 0x57a, 1);
    system_exit(-1);
  }
  *(int16_t *)(node + 0xb4) = -1;
  count = (int16_t)(*(int16_t *)((char *)path + 0x11084) - 1);
  *(int16_t *)((char *)path + 0x11084) = count;
  if (count > 1) {
    *(int *)((char *)path + 0x1108a) =
        *(int *)((char *)path + 0x11086 + (int)count * 4);
    path_heap_bubble_down(path, 1);
  }
  return result;
}

/* path_heap_insert (0x5e680) — readable C lift. */
void path_heap_insert(void *path /* @<eax> */, int16_t heap_node, int16_t heap_cost)
{
  int16_t count;
  int16_t idx;

  if (*(int16_t *)((char *)path + 0x11084) < 1) {
    display_assert((const char *)0x25e238, (const char *)0x25e0ac, 0x594, 1);
    system_exit(-1);
  }
  count = *(int16_t *)((char *)path + 0x11084);
  if (count >= 0x400) {
    error(2, (const char *)0x25e250);
    return;
  }
  idx = count;
  *(int16_t *)((char *)path + 0x11084) = (int16_t)(count + 1);
  *(int16_t *)((char *)path + 0x11086 + (int)idx * 4) = heap_node;
  *(int16_t *)((char *)path + 0x11088 + (int)idx * 4) = heap_cost;
  path_heap_bubble_up(path, idx);
}

/* FUN_0005e700 (0x5e700) — readable C lift.
 * block_base @eax; stack: surface_index. */
char FUN_0005e700(int surface_index, void *block_base)
{
  char *chunk;
  char *surf;
  char *bits;
  unsigned idx;
  unsigned mask;
  unsigned word;

  chunk = (char *)tag_block_get_element((char *)block_base + 0xb0, 0, 0x60);
  surf = (char *)tag_block_get_element(chunk + 0x3c, surface_index, 0xc);
  if (!(surf[8] & 8))
    return 0;
  bits = breakable_surfaces_get_bsp_surface_data();
  idx = (unsigned char)surf[9];
  mask = 1u << (idx & 0x1f);
  word = *(unsigned *)(bits + (idx >> 5) * 4);
  return (char)((mask & word) ? 0 : 1);
}




/* path_state_approach_point (0x5e9b0) — XBE naked draft (batch 225). */
#if defined(__clang__)
static short (*const b5e9b0_c5e7e0)(char *param_1, unsigned int param_2) = path_node_from_hash_table;
static char * (*const b5e9b0_c5e760)(char *param_1, short param_2) = path_get_node;
static char (*const b5e9b0_c639e0)(int scenario, unsigned char bsp_idx, float *origin, int start_surface, float *target, int end_surface, char *result_buf) = FUN_000639e0;
static void (*const b5e9b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b5e9b0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
char path_state_approach_point(void *path_state __attribute__((unused)), float *fp_results __attribute__((unused)), int fp_count __attribute__((unused)), char *out_byte __attribute__((unused)), char *out_dest __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c5e7e0]\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%cl, %%cl\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lpath_state_approach_point_6\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c5e760]\n\t"
      "movl %%eax, %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2(%%edi), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lpath_state_approach_point_2\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lpath_state_approach_point_1:\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c5e760]\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x64(%%esi), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x4(%%esi), %%cl\n\t"
      "addl $0xc, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c639e0]\n\t"
      "addl $0x24, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lpath_state_approach_point_2\n\t"
      "movswl 0x2(%%edi), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c5e760]\n\t"
      "movl %%eax, %%edi\n\t"
      "movw 0x2(%%edi), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .Lpath_state_approach_point_1\n\t"
      ".Lpath_state_approach_point_2:\n\t"
      "movl 0x18(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .Lpath_state_approach_point_3\n\t"
      "pushl $1\n\t"
      "pushl $0x12d\n\t"
      "pushl $0x25e0ac\n\t"
      "pushl $0x25e2e4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpath_state_approach_point_3:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lpath_state_approach_point_4\n\t"
      "pushl $1\n\t"
      "pushl $0x12e\n\t"
      "pushl $0x25e0ac\n\t"
      "pushl $0x25e2cc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpath_state_approach_point_4:\n\t"
      "cmpw $-1, 0x2(%%edi)\n\t"
      "jne .Lpath_state_approach_point_5\n\t"
      "movb $1, (%%eax)\n\t"
      "addl $0x14, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x4(%%ebx)\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%edx, 0x8(%%ebx)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lpath_state_approach_point_5:\n\t"
      "movb $0, (%%eax)\n\t"
      "addl $0xc, %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x4(%%ebx)\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%edx, 0x8(%%ebx)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lpath_state_approach_point_6:\n\t"
      "popl %%esi\n\t"
      "movb %%cl, %%al\n\t"
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
      "nop\n\t"
      :
      : [c5e7e0] "m"(b5e9b0_c5e7e0), [c5e760] "m"(b5e9b0_c5e760), [c639e0] "m"(b5e9b0_c639e0), [assert] "m"(b5e9b0_assert), [exitfn] "m"(b5e9b0_exitfn)
      : "memory");
}
#else
#error "path_state_approach_point: clang naked draft required"
#endif


/* FUN_0005ef80 (0x5ef80) — XBE naked draft (batch 81). */
#if defined(__clang__)
static void *(*const b5ef80_elem)(void *, int, int) = tag_block_get_element;
static void (*const b5ef80_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b5ef80_exitfn)(int) = system_exit;
static void (*const b5ef80_ftol)(void) = FUN_001d9068;
static void (*const b5ef80_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b5ef80_c5e680)(void *path, int16_t heap_node, int16_t heap_cost) = path_heap_insert;

__attribute__((naked, noinline))
char FUN_0005ef80(unsigned int *path_buf __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x20(%%edi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0005ef80_3\n\t"
      "flds 0x1c(%%edi)\n\t"
      "fcomps 0x25ddb8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0005ef80_3\n\t"
      "movl 0x64(%%edi), %%eax\n\t"
      "pushl $0x60\n\t"
      "addl $0xb0, %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x20(%%edi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jl .LFUN_0005ef80_1\n\t"
      "cmpl 0x3c(%%eax), %%ecx\n\t"
      "jl .LFUN_0005ef80_2\n\t"
      ".LFUN_0005ef80_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x2b1\n\t"
      "pushl $0x25e0ac\n\t"
      "pushl $0x25e4c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0005ef80_2:\n\t"
      "movb 0x4c(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0005ef80_4\n\t"
      "flds 0x50(%%edi)\n\t"
      "fsubs 0x14(%%edi)\n\t"
      "flds 0x54(%%edi)\n\t"
      "fsubs 0x18(%%edi)\n\t"
      "flds 0x58(%%edi)\n\t"
      "fsubs 0x1c(%%edi)\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x253f34\n\t"
      "call *%[ftol]\n\t"
      "cmpl $0x7fff, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jl .LFUN_0005ef80_5\n\t"
      "flds -0x4(%%ebp)\n\t"
      "pushl $0x40a99966\n\t"
      "pushl $0x60000000\n\t"
      "subl $0x38, %%esp\n\t"
      "fstpl 0x30(%%esp)\n\t"
      "flds 0x58(%%edi)\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x54(%%edi)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds 0x50(%%edi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x1c(%%edi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x18(%%edi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x14(%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25e448\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x48, %%esp\n\t"
      ".LFUN_0005ef80_3:\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0005ef80_4:\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      ".LFUN_0005ef80_5:\n\t"
      "cmpw $0, 0x80(%%edi)\n\t"
      "je .LFUN_0005ef80_6\n\t"
      "pushl $1\n\t"
      "pushl $0x2cc\n\t"
      "pushl $0x25e0ac\n\t"
      "pushl $0x25e42c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0005ef80_6:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movw 0x80(%%edi), %%bx\n\t"
      "movswl %%bx, %%edx\n\t"
      "imull $0x44, %%edx, %%edx\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "pushl %%esi\n\t"
      "leal 0x84(%%edx,%%edi,1), %%esi\n\t"
      "leal 0x1(%%ebx), %%ecx\n\t"
      "movw %%cx, 0x80(%%edi)\n\t"
      "movw %%ax, 0x2(%%esi)\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "movl 0x20(%%edi), %%eax\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "leal 0x14(%%edi), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0xc(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movw -0x8(%%ebp), %%dx\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "pushl $0x60\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, 0x18(%%esi)\n\t"
      "movl %%eax, 0x20(%%esi)\n\t"
      "movl %%eax, 0x24(%%esi)\n\t"
      "movw %%ax, 0x2e(%%esi)\n\t"
      "movl $0x7f7fffff, 0x1c(%%esi)\n\t"
      "movl %%ecx, 0x28(%%esi)\n\t"
      "movw %%dx, 0x2c(%%esi)\n\t"
      "movw $0xffff, 0x32(%%esi)\n\t"
      "movl 0x64(%%edi), %%eax\n\t"
      "addl $0xb0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jl .LFUN_0005ef80_7\n\t"
      "cmpl 0x3c(%%eax), %%ecx\n\t"
      "jl .LFUN_0005ef80_8\n\t"
      ".LFUN_0005ef80_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x2e3\n\t"
      "pushl $0x25e0ac\n\t"
      "pushl $0x25e3d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0005ef80_8:\n\t"
      "movb 0x4c(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0005ef80_9\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x14(%%edi), %%eax\n\t"
      "leal 0x74(%%edi), %%edx\n\t"
      "movl %%ecx, 0x6c(%%edi)\n\t"
      "movl 0x18(%%edi), %%ecx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x1c(%%edi), %%eax\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movw %%bx, 0x68(%%edi)\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl %%ecx, 0x70(%%edi)\n\t"
      ".LFUN_0005ef80_9:\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "andl $0x1ff, %%edx\n\t"
      "pushl %%eax\n\t"
      "shll $4, %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl %%edi, %%eax\n\t"
      "movw %%bx, 0x1208a(%%edx,%%edi,1)\n\t"
      "call *%[c5e680]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b5ef80_elem), [assert] "m"(b5ef80_assert), [exitfn] "m"(b5ef80_exitfn), [ftol] "m"(b5ef80_ftol), [c8f390] "m"(b5ef80_c8f390), [c5e680] "m"(b5ef80_c5e680)
      : "memory");
}
#else
#error "FUN_0005ef80: clang naked draft required"
#endif


/* FUN_0005f1d0 (0x5f1d0) — readable C lift. */
float FUN_0005f1d0(void *base, float *dst, float *src, int surface_index)
{
  void *bsp;
  float scratch[2];
  float dx, dy, dz, dist;

  bsp = tag_block_get_element((char *)base + 0xb0, 0, 0x60);
  collision_surface_find_closest_point2d(
      (int)(uintptr_t)bsp, surface_index, 2, 1, dst, scratch);
  collision_surface_project_point2d(
      bsp, surface_index, 2, 1, src, scratch);
  dx = src[0] - dst[0];
  dy = src[1] - dst[1];
  dz = src[2] - dst[2];
  dist = dx * dx + dy * dy + dz * dz;
  __asm__ volatile("fsqrt" : "+t"(dist));
  return dist;
}


/* build_path_edges_for_surface (0x5f240) — XBE naked draft (batch 83). */
#if defined(__clang__)
static void *(*const b5f240_elem)(void *, int, int) = tag_block_get_element;
static void (*const b5f240_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b5f240_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
int16_t build_path_edges_for_surface(void *scenario __attribute__((unused)), int surface_index __attribute__((unused)), char *out_edges __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "movl 0x1e8(%%eax), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x60\n\t"
      "addl $0xb0, %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "jl .Lbuild_path_edges_for_surface_1\n\t"
      "cmpl 0x3c(%%esi), %%edi\n\t"
      "jl .Lbuild_path_edges_for_surface_2\n\t"
      ".Lbuild_path_edges_for_surface_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x5d8\n\t"
      "pushl $0x25e0ac\n\t"
      "pushl $0x25e584\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbuild_path_edges_for_surface_2:\n\t"
      "pushl $0xc\n\t"
      "leal 0x3c(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl 0x4(%%eax), %%edi\n\t"
      "leal 0x48(%%esi), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $0x54, %%esi\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "jmp .Lbuild_path_edges_for_surface_4\n\t"
      ".Lbuild_path_edges_for_surface_3:\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lbuild_path_edges_for_surface_4:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "pushl $0x18\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x14(%%edi), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "sete %%al\n\t"
      "movswl %%bx, %%esi\n\t"
      "shll $5, %%esi\n\t"
      "addl %%edx, %%esi\n\t"
      "xorl %%edx, %%edx\n\t"
      "incl %%ebx\n\t"
      "testb %%al, %%al\n\t"
      "sete %%dl\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movl 0x10(%%edi,%%edx,4), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "je .Lbuild_path_edges_for_surface_6\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .Lbuild_path_edges_for_surface_5\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "cmpl (%%ecx), %%eax\n\t"
      "jl .Lbuild_path_edges_for_surface_6\n\t"
      ".Lbuild_path_edges_for_surface_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x5ee\n\t"
      "pushl $0x25e0ac\n\t"
      "pushl $0x25e528\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbuild_path_edges_for_surface_6:\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movb (%%eax,%%edx,1), %%cl\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movb %%cl, 0x4(%%esi)\n\t"
      "movl (%%edi), %%edx\n\t"
      "pushl $0x10\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl $0x10\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl %%ebx, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "leal 0x8(%%esi), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "flds (%%eax)\n\t"
      "addl $0x18, %%esp\n\t"
      "fsubs (%%ebx)\n\t"
      "fstps 0x14(%%esi)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "fstps 0x18(%%esi)\n\t"
      "flds 0x8(%%eax)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpw $0x40, %%ax\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "fstps 0x1c(%%esi)\n\t"
      "je .Lbuild_path_edges_for_surface_7\n\t"
      "movzbl -0x1(%%ebp), %%edx\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl 0x8(%%edi,%%edx,4), %%edi\n\t"
      "cmpl 0x4(%%eax), %%edi\n\t"
      "jne .Lbuild_path_edges_for_surface_3\n\t"
      "movw -0x8(%%ebp), %%ax\n\t"
      ".Lbuild_path_edges_for_surface_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b5f240_elem), [assert] "m"(b5f240_assert), [exitfn] "m"(b5f240_exitfn)
      : "memory");
}
#else
#error "build_path_edges_for_surface: clang naked draft required"
#endif


/* closest_point_to_attractor (0x5f3c0) — readable C lift (ai campaign). */
void closest_point_to_attractor(float *segment_start, float *segment_end, float *reference, float *out_point)
{
  float dx = segment_end[0] - segment_start[0];
  float dy = segment_end[1] - segment_start[1];
  float dz = segment_end[2] - segment_start[2];
  float denom = dx * dx + dy * dy + dz * dz;
  float t = ((segment_start[0] - reference[0]) * dx +
             (segment_start[1] - reference[1]) * dy +
             (segment_start[2] - reference[2]) * dz) / denom;
  if (t < 0.0f) {
    out_point[0] = segment_end[0];
    out_point[1] = segment_end[1];
    out_point[2] = segment_end[2];
    return;
  }
  if (t > 1.0f) {
    out_point[0] = segment_end[0];
    out_point[1] = segment_end[1];
    out_point[2] = segment_end[2];
    return;
  }
  out_point[0] = segment_start[0] + t * dx;
  out_point[1] = segment_start[1] + t * dy;
  out_point[2] = segment_start[2] + t * dz;
}

/* path_attractor_weight (0x5f490) — readable C lift.
 * x87 fsqrt; float32-spilled compare for denormal seed parity. */
float path_attractor_weight(void *path_state, float *node_pos, float *step_pos, float *out_dist)
{
  float closest[3];
  float *attractor;
  float dx, dy, dz, dist_sq, weight, dist, radius;
  unsigned dist_bits;
  volatile float dist_sq_f;
  volatile float radius_sq_f;

  attractor = (float *)((char *)path_state + 0x28);
  weight = 0.0f;
  dist_bits = 0x7f7fffffu;
  dist = *(float *)&dist_bits;
  closest_point_to_attractor(node_pos, step_pos, attractor, closest);
  dx = closest[0] - attractor[0];
  dy = closest[1] - attractor[1];
  dz = closest[2] - attractor[2];
  dist_sq = dx * dx + dy * dy + dz * dz;
  radius = *(float *)((char *)path_state + 0x38);
  dist_sq_f = dist_sq;
  radius_sq_f = radius * radius;
  if (dist_sq_f < radius_sq_f) {
    dist = dist_sq;
    __asm__ volatile("fsqrt" : "+t"(dist));
    weight = (*(float *)0x2533c8 - dist / radius) *
             *(float *)((char *)path_state + 0x3c);
  }
  if (out_dist == 0) {
    display_assert((const char *)0x25e5c4, (const char *)0x25e0ac, 0x65f, 1);
    system_exit(-1);
  }
  *out_dist = dist;
  return weight;
}

/* path_state_estimated_distance (0x5f550) — XBE naked draft (batch 114). */
#if defined(__clang__)
static short (*const b5f550_c5e7e0)(char *param_1, unsigned int param_2) = path_node_from_hash_table;
static void (*const b5f550_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b5f550_exitfn)(int) = system_exit;
static char * (*const b5f550_c5e760)(char *param_1, short param_2) = path_get_node;
static void (*const b5f550_c5f3c0)(float *segment_start, float *segment_end, float *reference, float *out_point) = closest_point_to_attractor;
static float (*const b5f550_norm)(float *) = normalize3d;

__attribute__((naked, noinline))
char path_state_estimated_distance(void *path_state __attribute__((unused)), void *fp_element __attribute__((unused)), int surface_index __attribute__((unused)), float *result __attribute__((unused)), float *opt_min_clearance __attribute__((unused)), float *opt_out_vec __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c5e7e0]\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "jne .Lpath_state_estimated_distance_1\n\t"
      "pushl $1\n\t"
      "pushl $0x14e\n\t"
      "pushl $0x25e0ac\n\t"
      "pushl $0x25e5c4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpath_state_estimated_distance_1:\n\t"
      "cmpw $-1, %%bx\n\t"
      "je .Lpath_state_estimated_distance_12\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c5e760]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "movl %%eax, %%esi\n\t"
      "fsubs 0xc(%%esi)\n\t"
      "leal 0xc(%%esi), %%eax\n\t"
      "flds 0x4(%%ecx)\n\t"
      "movb 0x24(%%edi), %%dl\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "addl $8, %%esp\n\t"
      "testb %%dl, %%dl\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fsubs 0x8(%%eax)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fadds 0x20(%%esi)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "je .Lpath_state_estimated_distance_2\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x28(%%edi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c5f3c0]\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fsubs (%%ebx)\n\t"
      "addl $0x10, %%esp\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fcoms 0x1c(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lpath_state_estimated_distance_3\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x1c(%%esi)\n\t"
      "jmp .Lpath_state_estimated_distance_3\n\t"
      ".Lpath_state_estimated_distance_2:\n\t"
      "flds 0x2533c0\n\t"
      ".Lpath_state_estimated_distance_3:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lpath_state_estimated_distance_4\n\t"
      "fstps (%%eax)\n\t"
      "jmp .Lpath_state_estimated_distance_5\n\t"
      ".Lpath_state_estimated_distance_4:\n\t"
      "fstp %%st(0)\n\t"
      ".Lpath_state_estimated_distance_5:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movb $1, %%al\n\t"
      "movb %%al, 0x17(%%ebp)\n\t"
      "je .Lpath_state_estimated_distance_15\n\t"
      "movl %%ebx, %%esi\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lpath_state_estimated_distance_6:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c5e760]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movw %%bx, (%%ecx)\n\t"
      "movl %%esi, %%ebx\n\t"
      "xorl %%esi, %%esi\n\t"
      "movw 0x2(%%ecx), %%si\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $-1, %%si\n\t"
      "jne .Lpath_state_estimated_distance_6\n\t"
      "cmpw %%si, %%bx\n\t"
      "je .Lpath_state_estimated_distance_9\n\t"
      ".Lpath_state_estimated_distance_7:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533f0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lpath_state_estimated_distance_8\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c5e760]\n\t"
      "flds -0x4(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "fadds 0x18(%%ecx)\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movw (%%ecx), %%bx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $-1, %%bx\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jne .Lpath_state_estimated_distance_7\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "jmp .Lpath_state_estimated_distance_11\n\t"
      ".Lpath_state_estimated_distance_8:\n\t"
      "cmpw $-1, %%bx\n\t"
      "jne .Lpath_state_estimated_distance_10\n\t"
      ".Lpath_state_estimated_distance_9:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "jmp .Lpath_state_estimated_distance_11\n\t"
      ".Lpath_state_estimated_distance_10:\n\t"
      "leal 0xc(%%ecx), %%eax\n\t"
      ".Lpath_state_estimated_distance_11:\n\t"
      "flds (%%eax)\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "fsubs 0x14(%%edi)\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%ecx)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x18(%%edi)\n\t"
      "fstps 0x4(%%ecx)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs 0x1c(%%edi)\n\t"
      "fstps 0x8(%%ecx)\n\t"
      "call *%[norm]\n\t"
      "movb 0x17(%%ebp), %%al\n\t"
      "fstp %%st(0)\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lpath_state_estimated_distance_12:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lpath_state_estimated_distance_13\n\t"
      "movl $0x7f7fffff, (%%eax)\n\t"
      ".Lpath_state_estimated_distance_13:\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lpath_state_estimated_distance_14\n\t"
      "movl 0x31fc38, %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      ".Lpath_state_estimated_distance_14:\n\t"
      "movl $0x7f7fffff, (%%esi)\n\t"
      "xorb %%al, %%al\n\t"
      ".Lpath_state_estimated_distance_15:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c5e7e0] "m"(b5f550_c5e7e0), [assert] "m"(b5f550_assert), [exitfn] "m"(b5f550_exitfn), [c5e760] "m"(b5f550_c5e760), [c5f3c0] "m"(b5f550_c5f3c0), [norm] "m"(b5f550_norm)
      : "memory");
}
#else
#error "path_state_estimated_distance: clang naked draft required"
#endif


/* FUN_0005f740 (0x5f740) — XBE naked draft (batch 79). */
#if defined(__clang__)
static int16_t (*const b5f740_c5e560)(void *path) = path_heap_pop_cheapest_node;
static char * (*const b5f740_c5e760)(char *param_1, short param_2) = path_get_node;
static void *(*const b5f740_elem)(void *, int, int) = tag_block_get_element;
static void (*const b5f740_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b5f740_exitfn)(int) = system_exit;
static int16_t (*const b5f740_c5f240)(void *scenario, int surface_index, char *out_edges) = build_path_edges_for_surface;
static char * (*const b5f740_c1459e0)(void) = breakable_surfaces_get_bsp_surface_data;
static float (*const b5f740_c5f490)(void *path_state, float *node_pos, float *step_pos, float *out_dist) = path_attractor_weight;
static void (*const b5f740_ftol)(void) = FUN_001d9068;
static void (*const b5f740_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b5f740_c5e680)(void *path, int16_t heap_node, int16_t heap_cost) = path_heap_insert;
static void (*const b5f740_c5e150)(void *path, int16_t heap_index) = (void *)path_heap_bubble_up;
static float (*const b5f740_c5f1d0)(void *base, float *dst, float *src, int surface_index) = FUN_0005f1d0;

__attribute__((naked, noinline))
char FUN_0005f740(unsigned int *path_buf __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x85c, %%esp\n\t"
      "flds 0x2549d4\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "fcomps (%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0005f740_1\n\t"
      "movl $0x3e4ccccd, -0x3c(%%ebp)\n\t"
      "jmp .LFUN_0005f740_2\n\t"
      ".LFUN_0005f740_1:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      ".LFUN_0005f740_2:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, %%eax\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movb $0, -0x3(%%ebp)\n\t"
      "call *%[c5e560]\n\t"
      "movl %%eax, %%ebx\n\t"
      "cmpw $-1, %%bx\n\t"
      "movl %%ebx, -0x50(%%ebp)\n\t"
      "je .LFUN_0005f740_42\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0005f740_3:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c5e760]\n\t"
      "movl 0x64(%%edi), %%ecx\n\t"
      "pushl $0x60\n\t"
      "addl $0xb0, %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "movl %%esi, -0x40(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jl .LFUN_0005f740_4\n\t"
      "cmpl 0x3c(%%eax), %%ecx\n\t"
      "jl .LFUN_0005f740_5\n\t"
      ".LFUN_0005f740_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x35d\n\t"
      "pushl $0x25e0ac\n\t"
      "pushl $0x25e888\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0005f740_5:\n\t"
      "movb 0x4c(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0005f740_8\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "cmpl 0x5c(%%edi), %%edx\n\t"
      "je .LFUN_0005f740_43\n\t"
      "flds 0x254cc4\n\t"
      "fcomps 0x6c(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0005f740_6\n\t"
      "flds 0x254cc4\n\t"
      "jmp .LFUN_0005f740_7\n\t"
      ".LFUN_0005f740_6:\n\t"
      "flds 0x6c(%%edi)\n\t"
      ".LFUN_0005f740_7:\n\t"
      "flds 0x253f34\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds 0x70(%%edi)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0005f740_44\n\t"
      ".LFUN_0005f740_8:\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "leal -0x85c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x64(%%edi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c5f240]\n\t"
      "addl $8, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_0005f740_41\n\t"
      "movzwl %%ax, %%eax\n\t"
      "leal -0x844(%%ebp), %%edx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      ".LFUN_0005f740_9:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl -0x40(%%ebp), %%ecx\n\t"
      "movl -0x18(%%eax), %%esi\n\t"
      "cmpl 0x4(%%ecx), %%esi\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "jne .LFUN_0005f740_10\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      ".LFUN_0005f740_10:\n\t"
      "movb -0x14(%%eax), %%al\n\t"
      "testb $0x40, %%al\n\t"
      "jne .LFUN_0005f740_11\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      ".LFUN_0005f740_11:\n\t"
      "movb 0x4(%%edi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_0005f740_12\n\t"
      "testb %%al, %%al\n\t"
      "jns .LFUN_0005f740_12\n\t"
      "movl 0x64(%%edi), %%eax\n\t"
      "pushl $0x60\n\t"
      "addl $0xb0, %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "pushl $0xc\n\t"
      "addl $0x3c, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x8(%%esi), %%al\n\t"
      "addl $0x18, %%esp\n\t"
      "testb $8, %%al\n\t"
      "je .LFUN_0005f740_12\n\t"
      "call *%[c1459e0]\n\t"
      "movzbl 0x9(%%esi), %%edx\n\t"
      "movl %%edx, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%ebx\n\t"
      "shll %%cl, %%ebx\n\t"
      "shrl $5, %%edx\n\t"
      "andl (%%eax,%%edx,4), %%ebx\n\t"
      "negl %%ebx\n\t"
      "sbbb %%bl, %%bl\n\t"
      "incb %%bl\n\t"
      "movb %%bl, -0x41(%%ebp)\n\t"
      "jne .LFUN_0005f740_40\n\t"
      ".LFUN_0005f740_12:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0005f740_40\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "flds -0x4(%%ecx)\n\t"
      "movb 0x4c(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0x10(%%ecx)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds (%%ecx)\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0xc(%%ecx)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0x8(%%ecx)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "je .LFUN_0005f740_15\n\t"
      "flds 0x4(%%ecx)\n\t"
      "flds (%%ecx)\n\t"
      "flds -0x4(%%ecx)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "fstp %%st(0)\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fcomps 0x254e74\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0005f740_15\n\t"
      "flds -0x3c(%%ebp)\n\t"
      ".byte 0xdc, 0xc0\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0005f740_15\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fsqrt\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds 0x50(%%edi)\n\t"
      "fsubs -0x10(%%ecx)\n\t"
      "flds 0x54(%%edi)\n\t"
      "fsubs -0xc(%%ecx)\n\t"
      "flds 0x58(%%edi)\n\t"
      "fsubs -0x8(%%ecx)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "fxch %%st(2)\n\t"
      "fmuls -0x4(%%ecx)\n\t"
      ".byte 0xde, 0xc2\n\t"
      "fmuls (%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fdivs -0x8(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fdivs -0x34(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fcoms -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0005f740_13\n\t"
      "fstp %%st(0)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "jmp .LFUN_0005f740_14\n\t"
      ".LFUN_0005f740_13:\n\t"
      "flds 0x2533c8\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fcoms -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0005f740_14\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x8(%%ebp)\n\t"
      ".LFUN_0005f740_14:\n\t"
      "fld %%st(0)\n\t"
      "fmuls -0x4(%%ecx)\n\t"
      "fadds -0x10(%%ecx)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%ecx)\n\t"
      "fadds -0xc(%%ecx)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "fadds -0x8(%%ecx)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      ".LFUN_0005f740_15:\n\t"
      "movl -0x40(%%ebp), %%esi\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fsubs 0xc(%%esi)\n\t"
      "leal 0xc(%%esi), %%eax\n\t"
      "flds -0x24(%%ebp)\n\t"
      "movb 0x24(%%edi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fsubs 0x8(%%eax)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fadds 0x20(%%esi)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "je .LFUN_0005f740_16\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c5f490]\n\t"
      "fadds 0x2533c8\n\t"
      "addl $0x10, %%esp\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps -0x30(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0005f740_17\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "jmp .LFUN_0005f740_17\n\t"
      ".LFUN_0005f740_16:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "movl $0, -0x30(%%ebp)\n\t"
      ".LFUN_0005f740_17:\n\t"
      "fadds 0x24(%%esi)\n\t"
      "movb 0x4c(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "je .LFUN_0005f740_18\n\t"
      "flds 0x50(%%edi)\n\t"
      "fsubs -0x28(%%ebp)\n\t"
      "flds 0x54(%%edi)\n\t"
      "fsubs -0x24(%%ebp)\n\t"
      "flds 0x58(%%edi)\n\t"
      "fsubs -0x20(%%ebp)\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x48(%%ebp)\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      ".LFUN_0005f740_18:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fsubs 0x28(%%esi)\n\t"
      "fcomps 0x25e884\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_0005f740_19\n\t"
      "pushl $1\n\t"
      "pushl $0x3ed\n\t"
      "pushl $0x25e0ac\n\t"
      "pushl $0x25e828\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0005f740_19:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x253f34\n\t"
      "call *%[ftol]\n\t"
      "cmpl $0x7fff, %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "jl .LFUN_0005f740_20\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0005f740_40\n\t"
      "flds -0x18(%%ebp)\n\t"
      "pushl $0x40a99966\n\t"
      "pushl $0x60000000\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x25e7d8\n\t"
      "pushl $3\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x18, %%esp\n\t"
      "movb $1, -0x3(%%ebp)\n\t"
      "jmp .LFUN_0005f740_40\n\t"
      ".LFUN_0005f740_20:\n\t"
      "movb 0x40(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0005f740_21\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fcomps 0x44(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0005f740_40\n\t"
      ".LFUN_0005f740_21:\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movw -0x18(%%edx), %%bx\n\t"
      "xorl %%esi, %%esi\n\t"
      "andl $0x1ff, %%ebx\n\t"
      "shll $3, %%ebx\n\t"
      "movswl %%bx, %%eax\n\t"
      "movw 0x1208a(%%edi,%%eax,2), %%si\n\t"
      "cmpw $-1, %%si\n\t"
      "je .LFUN_0005f740_23\n\t"
      ".LFUN_0005f740_22:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c5e760]\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "je .LFUN_0005f740_27\n\t"
      "incl %%ebx\n\t"
      "andl $0xfff, %%ebx\n\t"
      "movswl %%bx, %%edx\n\t"
      "movw 0x1208a(%%edi,%%edx,2), %%si\n\t"
      "cmpw $-1, %%si\n\t"
      "jne .LFUN_0005f740_22\n\t"
      ".LFUN_0005f740_23:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x80(%%edi), %%ax\n\t"
      "cmpw $0x400, %%ax\n\t"
      "jge .LFUN_0005f740_32\n\t"
      "leal 0x1(%%eax), %%ecx\n\t"
      "movswl %%bx, %%edx\n\t"
      "movw %%cx, 0x80(%%edi)\n\t"
      "movw %%ax, 0x1208a(%%edi,%%edx,2)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "imull $0x44, %%eax, %%eax\n\t"
      "movw $0xffff, 0xb4(%%eax,%%edi,1)\n\t"
      ".LFUN_0005f740_24:\n\t"
      "cmpw $-1, -0x10(%%ebp)\n\t"
      "je .LFUN_0005f740_40\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c5e760]\n\t"
      "movw -0x50(%%ebp), %%dx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl -0x40(%%ebp), %%eax\n\t"
      "movw %%dx, 0x2(%%ebx)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl %%ecx, 0x4(%%ebx)\n\t"
      "movl -0x18(%%edx), %%ecx\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "movl %%ecx, 0x8(%%ebx)\n\t"
      "movl %%ecx, -0x2c(%%ebp)\n\t"
      "leal 0xc(%%ebx), %%esi\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "movl %%ecx, 0x18(%%ebx)\n\t"
      "movl -0x34(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x1c(%%ebx)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl %%ecx, 0x20(%%ebx)\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x24(%%ebx)\n\t"
      "movw -0x1c(%%ebp), %%dx\n\t"
      "movl %%ecx, 0x28(%%ebx)\n\t"
      "movw %%dx, 0x2c(%%ebx)\n\t"
      "movw 0x2e(%%eax), %%ax\n\t"
      "incw %%ax\n\t"
      "movw %%ax, 0x2e(%%ebx)\n\t"
      "movw $0xffff, 0x32(%%ebx)\n\t"
      "movl $0x7f7fffff, 0x34(%%ebx)\n\t"
      "movl 0x64(%%edi), %%ecx\n\t"
      "pushl $0x60\n\t"
      "addl $0xb0, %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0x8(%%ebx), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jl .LFUN_0005f740_25\n\t"
      "cmpl 0x3c(%%eax), %%ecx\n\t"
      "jl .LFUN_0005f740_26\n\t"
      ".LFUN_0005f740_25:\n\t"
      "pushl $1\n\t"
      "pushl $0x466\n\t"
      "pushl $0x25e0ac\n\t"
      "pushl $0x25e780\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0005f740_26:\n\t"
      "movw 0x30(%%ebx), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .LFUN_0005f740_33\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c5e680]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0005f740_37\n\t"
      ".LFUN_0005f740_27:\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "movswl 0x2c(%%eax), %%ecx\n\t"
      "cmpl %%ecx, -0x1c(%%ebp)\n\t"
      "jge .LFUN_0005f740_40\n\t"
      "movw 0x30(%%eax), %%bx\n\t"
      "cmpw $-1, %%bx\n\t"
      "jne .LFUN_0005f740_28\n\t"
      "pushl $0x25e744\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0005f740_40\n\t"
      ".LFUN_0005f740_28:\n\t"
      "cmpw $1, %%bx\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "jl .LFUN_0005f740_29\n\t"
      "cmpw 0x11084(%%edi), %%bx\n\t"
      "jl .LFUN_0005f740_30\n\t"
      ".LFUN_0005f740_29:\n\t"
      "pushl $1\n\t"
      "pushl $0x423\n\t"
      "pushl $0x25e0ac\n\t"
      "pushl $0x25e708\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0005f740_30:\n\t"
      "movswl %%bx, %%ebx\n\t"
      "cmpw %%si, 0x11086(%%edi,%%ebx,4)\n\t"
      "je .LFUN_0005f740_31\n\t"
      "pushl $1\n\t"
      "pushl $0x424\n\t"
      "pushl $0x25e0ac\n\t"
      "pushl $0x25e6d4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0005f740_31:\n\t"
      "movw 0x11088(%%edi,%%ebx,4), %%dx\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "cmpw 0x2c(%%eax), %%dx\n\t"
      "je .LFUN_0005f740_24\n\t"
      "pushl $1\n\t"
      "pushl $0x425\n\t"
      "pushl $0x25e0ac\n\t"
      "pushl $0x25e680\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_0005f740_24\n\t"
      ".LFUN_0005f740_32:\n\t"
      "movl 0x48(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0005f740_40\n\t"
      "cmpw $0, 0x10(%%eax)\n\t"
      "jne .LFUN_0005f740_40\n\t"
      "movw $4, 0x10(%%eax)\n\t"
      "jmp .LFUN_0005f740_40\n\t"
      ".LFUN_0005f740_33:\n\t"
      "cmpw $1, %%ax\n\t"
      "jl .LFUN_0005f740_34\n\t"
      "cmpw 0x11084(%%edi), %%ax\n\t"
      "jl .LFUN_0005f740_35\n\t"
      ".LFUN_0005f740_34:\n\t"
      "pushl $1\n\t"
      "pushl $0x471\n\t"
      "pushl $0x25e0ac\n\t"
      "pushl $0x25e630\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0005f740_35:\n\t"
      "movswl 0x30(%%ebx), %%ecx\n\t"
      "movswl 0x11088(%%edi,%%ecx,4), %%edx\n\t"
      "cmpl %%edx, -0x1c(%%ebp)\n\t"
      "jle .LFUN_0005f740_36\n\t"
      "pushl $1\n\t"
      "pushl $0x472\n\t"
      "pushl $0x25e0ac\n\t"
      "pushl $0x25e5d8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0005f740_36:\n\t"
      "movswl 0x30(%%ebx), %%eax\n\t"
      "movw -0x1c(%%ebp), %%cx\n\t"
      "movw %%cx, 0x11088(%%edi,%%eax,4)\n\t"
      "movw 0x30(%%ebx), %%ax\n\t"
      "call *%[c5e150]\n\t"
      ".LFUN_0005f740_37:\n\t"
      "movb 0x4c(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0005f740_40\n\t"
      "flds -0x48(%%ebp)\n\t"
      "movl (%%esi), %%edx\n\t"
      "flds -0x48(%%ebp)\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "fcomps 0x2533d8\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "movl %%edx, -0x5c(%%ebp)\n\t"
      "movl %%ecx, -0x58(%%ebp)\n\t"
      "movl %%esi, -0x54(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0005f740_38\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "movl -0x2c(%%ebp), %%edx\n\t"
      "leal 0x50(%%eax), %%edi\n\t"
      "movl 0x64(%%eax), %%eax\n\t"
      "pushl %%edx\n\t"
      "leal -0x5c(%%ebp), %%esi\n\t"
      "call *%[c5f1d0]\n\t"
      "movl -0x54(%%ebp), %%esi\n\t"
      "movl -0x58(%%ebp), %%ecx\n\t"
      "movl -0x5c(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0005f740_38:\n\t"
      "fsts 0x34(%%ebx)\n\t"
      "addl $0x38, %%ebx\n\t"
      "movl %%edx, (%%ebx)\n\t"
      "movl %%ecx, 0x4(%%ebx)\n\t"
      "movl %%esi, 0x8(%%ebx)\n\t"
      "fcoms 0x6c(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0005f740_39\n\t"
      "movw -0x10(%%ebp), %%ax\n\t"
      "fstps 0x6c(%%edi)\n\t"
      "movw %%ax, 0x68(%%edi)\n\t"
      "leal 0x74(%%edi), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl %%esi, 0x8(%%eax)\n\t"
      "movl %%ecx, 0x70(%%edi)\n\t"
      "jmp .LFUN_0005f740_40\n\t"
      ".LFUN_0005f740_39:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0005f740_40:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl -0x4c(%%ebp), %%eax\n\t"
      "addl $0x20, %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "jne .LFUN_0005f740_9\n\t"
      ".LFUN_0005f740_41:\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c5e560]\n\t"
      "movl %%eax, %%ebx\n\t"
      "cmpw $-1, %%bx\n\t"
      "movl %%ebx, -0x50(%%ebp)\n\t"
      "jne .LFUN_0005f740_3\n\t"
      ".LFUN_0005f740_42:\n\t"
      "movl 0x48(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0005f740_45\n\t"
      "cmpw $0, 0x10(%%eax)\n\t"
      "jne .LFUN_0005f740_45\n\t"
      "movw $3, 0x10(%%eax)\n\t"
      "jmp .LFUN_0005f740_45\n\t"
      ".LFUN_0005f740_43:\n\t"
      "leal 0x50(%%edi), %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "leal 0x74(%%edi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movw %%bx, 0x68(%%edi)\n\t"
      "movl $0, 0x6c(%%edi)\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "jmp .LFUN_0005f740_45\n\t"
      ".LFUN_0005f740_44:\n\t"
      "movl 0x48(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0005f740_45\n\t"
      "cmpw $0, 0x10(%%eax)\n\t"
      "jne .LFUN_0005f740_45\n\t"
      "movw $2, 0x10(%%eax)\n\t"
      ".LFUN_0005f740_45:\n\t"
      "movb 0x4c(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_0005f740_46\n\t"
      "flds 0x6c(%%edi)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "fcomps 0x60(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_0005f740_46\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_0005f740_46:\n\t"
      "movl 0x48(%%edi), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "je .LFUN_0005f740_47\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0005f740_47\n\t"
      "movw $5, 0x10(%%edi)\n\t"
      ".LFUN_0005f740_47:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c5e560] "m"(b5f740_c5e560), [c5e760] "m"(b5f740_c5e760), [elem] "m"(b5f740_elem), [assert] "m"(b5f740_assert), [exitfn] "m"(b5f740_exitfn), [c5f240] "m"(b5f740_c5f240), [c1459e0] "m"(b5f740_c1459e0), [c5f490] "m"(b5f740_c5f490), [ftol] "m"(b5f740_ftol), [c8f390] "m"(b5f740_c8f390), [c5e680] "m"(b5f740_c5e680), [c5e150] "m"(b5f740_c5e150), [c5f1d0] "m"(b5f740_c5f1d0)
      : "memory");
}
#else
#error "FUN_0005f740: clang naked draft required"
#endif


/* FUN_00060070 (0x60070) — readable C lift (ai campaign). */
void *FUN_00060070(void *obstacles, int16_t disc_index)
{
  extern char DAT_0025e930[];
  extern char DAT_0025e990[];
  int16_t count;
  if (disc_index < 0)
    goto do_assert;
  count = *(int16_t *)((char *)obstacles + 2);
  if (disc_index >= count)
    goto do_assert;
  if (count > 0x80)
    goto do_assert;
  return (char *)obstacles + 8 + (int)disc_index * 24;
do_assert:
  display_assert(DAT_0025e930, DAT_0025e990, 0x18c, 1);
  system_exit(-1);
  return (char *)obstacles + 8 + (int)disc_index * 24;
}

/* FUN_000600c0 (0x600c0) — readable C lift (ai campaign). */
int16_t FUN_000600c0(void *obstacles, int16_t disc_index)
{
  if (disc_index == (int16_t)0xffff)
    return (int16_t)-1;
  void *p = FUN_00060070(obstacles, disc_index);
  return *(int16_t *)((char *)p + 2);
}

/* FUN_000600f0 (0x600f0) — readable C lift (ai campaign). */
void *FUN_000600f0(void *path, int16_t step_index)
{
  extern char DAT_0025e9b0[];
  extern char DAT_0025ea14[];
  int16_t count;
  if (step_index < 0)
    goto do_assert;
  count = *(int16_t *)((char *)path + 0x2c);
  if (step_index >= count)
    goto do_assert;
  if (count > 0x80)
    goto do_assert;
  return (char *)path + 0x30 + (int)step_index * 40;
do_assert:
  display_assert(DAT_0025e9b0, DAT_0025ea14, 0x28, 1);
  system_exit(-1);
  return (char *)path + 0x30 + (int)step_index * 40;
}

/* FUN_000601a0 (0x601a0) — readable C lift (ai campaign). */
int FUN_000601a0(int16_t heap_index)
{
  extern char DAT_0025eaa4[];
  extern char DAT_0025ea14[];
  if (heap_index > 0)
    return ((int)heap_index - 1) >> 1;
  display_assert(DAT_0025eaa4, DAT_0025ea14, 0x39, 1);
  system_exit(-1);
  return ((int)heap_index - 1) >> 1;
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

/* FUN_00060140 (0x60140) — readable C lift (ai campaign). */
int16_t FUN_00060140(void *path, int16_t heap_index)
{
  extern char DAT_0025ea40[];
  extern char DAT_0025ea14[];
  int16_t count;
  if (heap_index < 0)
    goto do_assert;
  count = *(int16_t *)((char *)path + 0x1430);
  if (heap_index >= count)
    goto do_assert;
  if (count > 0x80)
    goto do_assert;
  return *(int16_t *)((char *)path + 0x1432 + (int)heap_index * 2);
do_assert:
  display_assert(DAT_0025ea40, DAT_0025ea14, 0x31, 1);
  system_exit(-1);
  return *(int16_t *)((char *)path + 0x1432 + (int)heap_index * 2);
}

/* FUN_00060200 (0x60200) — readable C lift. */
float FUN_00060200(void *path, int16_t heap_index)
{
  int16_t node;
  int16_t count;
  int idx;
  node = FUN_00060140(path, heap_index);
  count = *(int16_t *)((char *)path + 0x2c);
  if (node < 0 || node >= count || count > 0x80) {
    display_assert((const char *)0x25e9b0, (const char *)0x25ea14, 0x28, true);
    system_exit(-1);
  }
  idx = (int)node + 2;
  idx = idx + idx * 4;
  return *(float *)((char *)path + idx * 8);
}

/* FUN_00060260 (0x60260) — readable C lift. */
void FUN_00060260(unsigned short channel, void *path)
{
  int16_t count;
  int16_t i;
  int16_t node;
  float val;
  unsigned bits;

  count = *(int16_t *)((char *)path + 0x1430);
  if (count <= 0)
    return;
  for (i = 0; i < count; i++) {
    if (i < 0 || i >= count || count > 0x80) {
      display_assert((const char *)0x25ea40, (const char *)0x25ea14, 0x31, 1);
      system_exit(-1);
    }
    node = *(int16_t *)((char *)path + 0x1432 + (int)i * 2);
    if (node < 0 || node >= *(int16_t *)((char *)path + 0x2c) ||
        *(int16_t *)((char *)path + 0x2c) > 0x80) {
      display_assert((const char *)0x25e9b0, (const char *)0x25ea14, 0x28, 1);
      system_exit(-1);
    }
    val = *(float *)((char *)path + ((int)node + 2) * 40);
    bits = *(unsigned *)&val;
    error(channel, (const char *)0x25eab4, (int)i, (double)val, bits);
  }
}

__attribute__((unused))
static __attribute__((unused)) float path_step_heap_cost(void *path, int16_t step_index)
{
  char *step;

  step = (char *)FUN_000600f0(path, step_index);
  return *(float *)step;
}

__attribute__((unused))
static __attribute__((unused)) void path_assert_heap_index(void *path, int16_t heap_index, int line_kind)
{
  int16_t heap_count;
  int16_t step_count;
  int16_t step_index;

  heap_count = *(int16_t *)((char *)path + 0x1430);
  if (heap_index < 0 || heap_index >= heap_count || heap_count > 0x80) {
    display_assert(
        "heap_index>=0 && heap_index<path->heap_count && "
        "path->heap_count<=MAXIMUM_PATH_STEPS",
        "c:\\halo\\SOURCE\\ai\\path.h", 49, 1);
    system_exit(-1);
  }
  step_index = *(int16_t *)((char *)path + (int)heap_index * 2 + 0x1432);
  if (step_index < 0) {
    display_assert("step_index>=0 && step_index<path->step_count && "
                   "path->step_count<=MAXIMUM_PATH_STEPS",
                   "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 40, 1);
    system_exit(-1);
  }
  step_count = *(int16_t *)((char *)path + 0x2c);
  if (step_index >= step_count || step_count > 0x80) {
    display_assert("step_index>=0 && step_index<path->step_count && "
                   "path->step_count<=MAXIMUM_PATH_STEPS",
                   "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 40, 1);
    system_exit(-1);
  }
  (void)line_kind;
}

/* FUN_00060330 (0x60330) — readable C lift.
 * path@eax; stack: debug_context. Validates path heap cost order. */
char FUN_00060330(void *path, const char *debug_context)
{
  char *p;
  int16_t i;
  int16_t parent;
  int16_t node;
  int16_t count;
  float parent_cost;
  float node_cost;

  p = (char *)path;
  count = *(int16_t *)(p + 0x1430);
  if (count <= 1)
    return 1;

  for (i = 1; i < count; i++) {
    if (i <= 0) {
      display_assert((const char *)0x25eaa4, (const char *)0x25ea14, 0x39, 1);
      system_exit(-1);
    }
    parent = (int16_t)(((int)i - 1) >> 1);
    if (parent < 0 || parent >= count || count > 0x80) {
      display_assert((const char *)0x25ea40, (const char *)0x25ea14, 0x31, 1);
      system_exit(-1);
    }
    node = *(int16_t *)(p + 0x1432 + (int)parent * 2);
    if (node < 0 || node >= *(int16_t *)(p + 0x2c) || *(int16_t *)(p + 0x2c) > 0x80) {
      display_assert((const char *)0x25e9b0, (const char *)0x25ea14, 0x28, 1);
      system_exit(-1);
    }
    parent_cost = *(float *)(p + ((int)node + 2) * 40);

    if (i < 0 || i >= count || count > 0x80) {
      display_assert((const char *)0x25ea40, (const char *)0x25ea14, 0x31, 1);
      system_exit(-1);
    }
    node = *(int16_t *)(p + 0x1432 + (int)i * 2);
    if (node < 0 || node >= *(int16_t *)(p + 0x2c) || *(int16_t *)(p + 0x2c) > 0x80) {
      display_assert((const char *)0x25e9b0, (const char *)0x25ea14, 0x28, 1);
      system_exit(-1);
    }
    node_cost = *(float *)(p + ((int)node + 2) * 40);

    if (node_cost < parent_cost) {
      error(2, (const char *)0x25eaec, debug_context);
      error(2, (const char *)0x25eac4);
      FUN_00060260(3, p);
      return 0;
    }
  }
  return 1;
}

/* 0x604e0 — sift heap entry up at heap_index */
void FUN_000604e0(void *path, int16_t heap_index)
{
  int16_t parent_index;
  int16_t child_step;
  int16_t parent_step;
  float child_cost;
  float parent_cost;
  int16_t *heap_entry;
  int16_t *parent_entry;

  if (heap_index <= 0)
    return;

  while (heap_index > 0) {
    parent_index = (int16_t)((heap_index - 1) / 2);
    path_assert_heap_index(path, heap_index, 0);
    path_assert_heap_index(path, parent_index, 0);
    child_step =
        *(int16_t *)((char *)path + (int)heap_index * 2 + 0x1432);
    parent_step =
        *(int16_t *)((char *)path + (int)parent_index * 2 + 0x1432);
    child_cost = path_step_heap_cost(path, child_step);
    parent_cost = path_step_heap_cost(path, parent_step);
    if (child_cost >= parent_cost)
      break;

    heap_entry = (int16_t *)((char *)path + (int)heap_index * 2 + 0x1432);
    parent_entry =
        (int16_t *)((char *)path + (int)parent_index * 2 + 0x1432);
    *heap_entry = parent_step;
    *parent_entry = child_step;
    heap_index = parent_index;
  }
}

/* 0x60670 — sift heap entry down from heap_index */
void FUN_00060670(void *path, int16_t heap_index)
{
  int16_t heap_count;
  int16_t best_index;
  int16_t left_index;
  int16_t right_index;
  int16_t step_index;
  int16_t swap_step;
  float best_cost;
  float left_cost;
  float right_cost;
  int16_t *best_entry;
  int16_t *swap_entry;

  heap_count = *(int16_t *)((char *)path + 0x1430);
  while (heap_index < heap_count) {
    left_index = (int16_t)(heap_index * 2 + 1);
    right_index = (int16_t)(heap_index * 2 + 2);
    best_index = heap_index;

    path_assert_heap_index(path, heap_index, 0);
    step_index =
        *(int16_t *)((char *)path + (int)heap_index * 2 + 0x1432);
    best_cost = path_step_heap_cost(path, step_index);

    if (left_index < heap_count) {
      int16_t left_step;

      path_assert_heap_index(path, left_index, 0);
      left_step =
          *(int16_t *)((char *)path + (int)left_index * 2 + 0x1432);
      left_cost = path_step_heap_cost(path, left_step);
      if (left_cost < best_cost) {
        best_index = left_index;
        best_cost = left_cost;
      }
    }

    if (right_index < heap_count) {
      int16_t right_step;

      path_assert_heap_index(path, right_index, 0);
      right_step =
          *(int16_t *)((char *)path + (int)right_index * 2 + 0x1432);
      right_cost = path_step_heap_cost(path, right_step);
      if (right_cost < best_cost)
        best_index = right_index;
    }

    if (best_index == heap_index)
      break;

    best_entry =
        (int16_t *)((char *)path + (int)heap_index * 2 + 0x1432);
    swap_entry =
        (int16_t *)((char *)path + (int)best_index * 2 + 0x1432);
    swap_step = *swap_entry;
    *swap_entry = *best_entry;
    *best_entry = swap_step;
    heap_index = best_index;
  }
}

/* FUN_00060910 (0x60910) — readable C lift. */
char FUN_00060910(void *path, int16_t step_index)
{
  int16_t count;

  FUN_00060330(path, (const char *)0x25eb18);
  count = *(int16_t *)((char *)path + 0x1430);
  if (count >= 0x80) {
    return 0;
  }
  *(int16_t *)((char *)path + 0x1430) = (int16_t)(count + 1);
  FUN_000600f0(path, step_index);
  *(int16_t *)((char *)path + 0x1432 + (int)count * 2) = step_index;
  FUN_000604e0(path, count);
  FUN_00060330(path, (const char *)0x25eb04);
  return 1;
}

/* FUN_00060970 (0x60970) — readable C lift. */
int16_t FUN_00060970(void *path)
{
  int16_t count;
  int16_t old_head;
  int16_t new_head;

  FUN_00060330(path, (const char *)0x25eb40);
  count = *(int16_t *)((char *)path + 0x1430);
  if (count <= 0) {
    return (int16_t)-1;
  }
  count = (int16_t)(count - 1);
  *(int16_t *)((char *)path + 0x1430) = count;
  new_head = *(int16_t *)((char *)path + 0x1432 + (int)count * 2);
  old_head = *(int16_t *)((char *)path + 0x1432);
  *(int16_t *)((char *)path + 0x1432) = new_head;
  FUN_00060670(path, 0);
  FUN_00060330(path, (const char *)0x25eb2c);
  return old_head;
}

/* FUN_000609e0 (0x609e0) — XBE naked draft (batch 113). */
#if defined(__clang__)
static void *(*const b609e0_elem)(void *, int, int) = tag_block_get_element;
static float *(*const b609e0_c147990)(void *bsp, int surface_index, int projection, int sign, float *point, float *out_point) = collision_surface_project_point2d;
static void (*const b609e0_c189150)(char flag, float *position, float scale, void *color) = FUN_00189150;
static void *(*const b609e0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b609e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b609e0_exitfn)(int) = system_exit;
static void (*const b609e0_c189270)(char flag, float *point_a, float *point_b, void *color) = FUN_00189270;

__attribute__((naked, noinline))
void FUN_000609e0(void *path __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "cmpw $0, 0x2c(%%edi)\n\t"
      "jle .LFUN_000609e0_17\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl $0x60\n\t"
      "addl $0xb0, %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x30(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x38(%%edi), %%eax\n\t"
      "pushl $1\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "call *%[c147990]\n\t"
      "movl 0x18(%%edi), %%eax\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x10(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c147990]\n\t"
      "movl 0x2ee6c4, %%eax\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "addl $0x3c, %%esp\n\t"
      "cmpw %%bx, 0x1e(%%edi)\n\t"
      "jne .LFUN_000609e0_1\n\t"
      "movl 0x2ee6e0, %%eax\n\t"
      ".LFUN_000609e0_1:\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3e000000\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "movl 0x2ee6c4, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw %%bx, 0x1e(%%edi)\n\t"
      "jne .LFUN_000609e0_2\n\t"
      "movl 0x2ee6e0, %%eax\n\t"
      ".LFUN_000609e0_2:\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3e000000\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c189150]\n\t"
      "movswl 0x2c(%%edi), %%eax\n\t"
      "movw 0x1e(%%edi), %%si\n\t"
      "addl $0x1f, %%eax\n\t"
      "sarl $5, %%eax\n\t"
      "shll $2, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "addl $0x1c, %%esp\n\t"
      "cmpw %%bx, %%si\n\t"
      "je .LFUN_000609e0_6\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_000609e0_3:\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_000609e0_4\n\t"
      "movw 0x2c(%%edi), %%ax\n\t"
      "cmpw %%ax, %%si\n\t"
      "jge .LFUN_000609e0_4\n\t"
      "cmpw $0x80, %%ax\n\t"
      "jle .LFUN_000609e0_5\n\t"
      ".LFUN_000609e0_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x28\n\t"
      "pushl $0x25ea14\n\t"
      "pushl $0x25e9b0\n\t"
      "call *%[assert]\n\t"
      "pushl %%ebx\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000609e0_5:\n\t"
      "movswl %%si, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "sarl $5, %%edx\n\t"
      "movl $1, %%esi\n\t"
      "shll %%cl, %%esi\n\t"
      "movl -0x30(%%ebp,%%edx,4), %%ecx\n\t"
      "leal -0x30(%%ebp,%%edx,4), %%edx\n\t"
      "leal (%%eax,%%eax,4), %%eax\n\t"
      "orl %%esi, %%ecx\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movw 0x54(%%edi,%%eax,8), %%si\n\t"
      "cmpw %%bx, %%si\n\t"
      "jne .LFUN_000609e0_3\n\t"
      ".LFUN_000609e0_6:\n\t"
      "movw 0x2c(%%edi), %%ax\n\t"
      "xorl %%esi, %%esi\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%esi, 0x8(%%ebp)\n\t"
      "jle .LFUN_000609e0_16\n\t"
      "jmp .LFUN_000609e0_8\n\t"
      ".LFUN_000609e0_7:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      ".LFUN_000609e0_8:\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_000609e0_9\n\t"
      "cmpw %%ax, %%si\n\t"
      "jge .LFUN_000609e0_9\n\t"
      "cmpw $0x80, %%ax\n\t"
      "jle .LFUN_000609e0_10\n\t"
      ".LFUN_000609e0_9:\n\t"
      "pushl $1\n\t"
      "pushl $0x28\n\t"
      "pushl $0x25ea14\n\t"
      "pushl $0x25e9b0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000609e0_10:\n\t"
      "movswl %%si, %%esi\n\t"
      "leal (%%esi,%%esi,4), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x54(%%edi,%%ecx,8), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "leal 0x30(%%edi,%%ecx,8), %%ebx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "je .LFUN_000609e0_15\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_000609e0_11\n\t"
      "movw 0x2c(%%edi), %%cx\n\t"
      "cmpw %%cx, %%ax\n\t"
      "jge .LFUN_000609e0_11\n\t"
      "cmpw $0x80, %%cx\n\t"
      "jle .LFUN_000609e0_12\n\t"
      ".LFUN_000609e0_11:\n\t"
      "pushl $1\n\t"
      "pushl $0x28\n\t"
      "pushl $0x25ea14\n\t"
      "pushl $0x25e9b0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000609e0_12:\n\t"
      "movswl %%ax, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%edx\n\t"
      "leal 0x30(%%edi,%%edx,8), %%eax\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl $1\n\t"
      "pushl $2\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c147990]\n\t"
      "movl 0x8(%%ebx), %%edx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl $1\n\t"
      "pushl $2\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c147990]\n\t"
      "movl %%esi, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "sarl $5, %%esi\n\t"
      "movl -0x30(%%ebp,%%esi,4), %%eax\n\t"
      "addl $0x30, %%esp\n\t"
      "testl %%edx, %%eax\n\t"
      "je .LFUN_000609e0_13\n\t"
      "movl 0x2ee6c4, %%eax\n\t"
      "jmp .LFUN_000609e0_14\n\t"
      ".LFUN_000609e0_13:\n\t"
      "movb 0x1a(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x2ee6d4, %%eax\n\t"
      "jne .LFUN_000609e0_14\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      ".LFUN_000609e0_14:\n\t"
      "pushl %%eax\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_000609e0_15:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movw 0x2c(%%edi), %%ax\n\t"
      "incl %%ecx\n\t"
      "cmpw %%ax, %%cx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "jl .LFUN_000609e0_7\n\t"
      ".LFUN_000609e0_16:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_000609e0_17:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b609e0_elem), [c147990] "m"(b609e0_c147990), [c189150] "m"(b609e0_c189150), [memset] "m"(b609e0_memset), [assert] "m"(b609e0_assert), [exitfn] "m"(b609e0_exitfn), [c189270] "m"(b609e0_c189270)
      : "memory");
}
#else
#error "FUN_000609e0: clang naked draft required"
#endif

