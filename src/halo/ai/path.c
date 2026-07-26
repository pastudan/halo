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

/* 0x5e150 — bubble a path-heap node toward the root. */
void path_heap_bubble_up(void *path, int16_t heap_index)
{
  int16_t cur_index;
  int16_t parent_index;
  int16_t cur_node;
  int16_t parent_node;
  int16_t cur_cost;
  int16_t parent_cost;
  char *cur_entry;
  char *parent_entry;

  if (heap_index < 1 || heap_index > 0x400) {
    display_assert("heap_index>=1 && heap_index<=MAXIMUM_PATH_HEAP_SIZE",
                   "c:\\halo\\SOURCE\\ai\\path.c", 0x4ea, 1);
    system_exit(-1);
  }

  cur_node = *(int16_t *)((char *)path + heap_index * 4 + 0x11086);
  cur_cost = *(int16_t *)((char *)path + heap_index * 4 + 0x11088);
  if (cur_node < 0 || cur_node >= 0x400) {
    display_assert("heap_node>=0 && heap_node<MAXIMUM_PATH_NODE_COUNT",
                   "c:\\halo\\SOURCE\\ai\\path.c", 0x4ef, 1);
    system_exit(-1);
  }

  cur_entry = (char *)path + cur_node * 0x44 + 0xb0;
  if (*(int16_t *)(cur_entry + 0) != cur_cost) {
    display_assert("path->nodes[heap_node].estimated_distance==heap_cost",
                   "c:\\halo\\SOURCE\\ai\\path.c", 0x4f0, 1);
    system_exit(-1);
  }

  cur_index = heap_index;
  while (cur_index > 1) {
    parent_index = cur_index >> 1;
    parent_node = *(int16_t *)((char *)path + parent_index * 4 + 0x11086);
    parent_cost = *(int16_t *)((char *)path + parent_index * 4 + 0x11088);
    if (parent_node < 0 || parent_node >= 0x400) {
      display_assert("parent_node>=0 && parent_node<MAXIMUM_PATH_NODE_COUNT",
                     "c:\\halo\\SOURCE\\ai\\path.c", 0x4ff, 1);
      system_exit(-1);
    }
    parent_entry = (char *)path + parent_node * 0x44 + 0xb0;
    if (*(int16_t *)(parent_entry + 0xb4) != parent_index) {
      display_assert("path->nodes[parent_node].heap_index==parent_index",
                     "c:\\halo\\SOURCE\\ai\\path.c", 0x500, 1);
      system_exit(-1);
    }
    if (*(int16_t *)(parent_entry + 0) != parent_cost) {
      display_assert("path->nodes[parent_node].estimated_distance==parent_cost",
                     "c:\\halo\\SOURCE\\ai\\path.c", 0x501, 1);
      system_exit(-1);
    }
    if (cur_cost >= parent_cost)
      break;

    *(int16_t *)((char *)path + cur_index * 4 + 0x11086) = parent_node;
    *(int16_t *)((char *)path + cur_index * 4 + 0x11088) = parent_cost;
    *(int16_t *)(parent_entry + 0xb4) = cur_index;

    cur_index = parent_index;
  }

  *(int16_t *)((char *)path + cur_index * 4 + 0x11086) = cur_node;
  *(int16_t *)((char *)path + cur_index * 4 + 0x11088) = cur_cost;
  *(int16_t *)(cur_entry + 0xb4) = cur_index;
}

/* 0x5e330 — sink a path-heap node toward the leaves. */
void path_heap_bubble_down(void *path, int16_t heap_index)
{
  int16_t heap_size;
  int16_t orig_node;
  int16_t orig_cost;
  int16_t cur_index;
  char *orig_entry;

  if (heap_index < 1 || heap_index > 0x400) {
    display_assert("heap_index>=1 && heap_index<=MAXIMUM_PATH_HEAP_SIZE",
                   "c:\\halo\\SOURCE\\ai\\path.c", 0x524, 1);
    system_exit(-1);
  }

  orig_node = *(int16_t *)((char *)path + heap_index * 4 + 0x11086);
  orig_cost = *(int16_t *)((char *)path + heap_index * 4 + 0x11088);
  if (orig_node < 0 || orig_node >= 0x400) {
    display_assert("heap_node>=0 && heap_node<MAXIMUM_PATH_NODE_COUNT",
                   "c:\\halo\\SOURCE\\ai\\path.c", 0x529, 1);
    system_exit(-1);
  }

  orig_entry = (char *)path + orig_node * 0x44 + 0xb0;
  if (*(int16_t *)(orig_entry + 0) != orig_cost) {
    display_assert("path->nodes[heap_node].estimated_distance==heap_cost",
                   "c:\\halo\\SOURCE\\ai\\path.c", 0x52a, 1);
    system_exit(-1);
  }

  heap_size = *(int16_t *)((char *)path + 0x11084);
  cur_index = heap_index;

  for (;;) {
    int16_t best_index;
    int16_t best_cost;
    int16_t child_idx;
    int pass;

    best_index = cur_index;
    best_cost = orig_cost;
    child_idx = (int16_t)(cur_index + cur_index);

    for (pass = 0; pass < 2; pass++, child_idx++) {
      int16_t child_node;
      int16_t child_cost;
      char *child_entry;

      if (child_idx >= heap_size)
        break;

      child_node = *(int16_t *)((char *)path + child_idx * 4 + 0x11086);
      child_cost = *(int16_t *)((char *)path + child_idx * 4 + 0x11088);
      if (child_node < 0 || child_node >= 0x400) {
        display_assert("child_node>=0 && child_node<MAXIMUM_PATH_NODE_COUNT",
                       "c:\\halo\\SOURCE\\ai\\path.c", 0x53e, 1);
        system_exit(-1);
      }

      child_entry = (char *)path + child_node * 0x44 + 0xb0;
      if (*(int16_t *)(child_entry + 0xb4) != child_idx) {
        display_assert("path->nodes[child_node].heap_index==child_index",
                       "c:\\halo\\SOURCE\\ai\\path.c", 0x53f, 1);
        system_exit(-1);
      }
      if (*(int16_t *)(child_entry + 0) != child_cost) {
        display_assert("path->nodes[child_node].estimated_distance==child_cost",
                       "c:\\halo\\SOURCE\\ai\\path.c", 0x540, 1);
        system_exit(-1);
      }

      if (child_cost < best_cost) {
        best_cost = child_cost;
        best_index = child_idx;
      }
    }

    if (best_index == cur_index) {
      *(int16_t *)((char *)path + cur_index * 4 + 0x11086) = orig_node;
      *(int16_t *)((char *)path + cur_index * 4 + 0x11088) = orig_cost;
      *(int16_t *)(orig_entry + 0xb4) = cur_index;
      return;
    }

    {
      int16_t moved_node;
      char *moved_entry;

      moved_node =
          *(int16_t *)((char *)path + best_index * 4 + 0x11086);
      *(int16_t *)((char *)path + cur_index * 4 + 0x11086) = moved_node;
      *(int16_t *)((char *)path + cur_index * 4 + 0x11088) =
          *(int16_t *)((char *)path + best_index * 4 + 0x11088);
      moved_entry = (char *)path + moved_node * 0x44 + 0xb0;
      *(int16_t *)(moved_entry + 0xb4) = cur_index;
    }
    cur_index = best_index;
  }
}

/* 0x5e560 — remove and return the cheapest open path node. */
int16_t path_heap_pop_cheapest_node(void *path)
{
  int16_t heap_size;
  int16_t node_index;
  int16_t node_cost;
  char *node_entry;

  heap_size = *(int16_t *)((char *)path + 0x11084);
  if (heap_size < 1) {
    display_assert("path->heap_size>=1", "c:\\halo\\SOURCE\\ai\\path.c", 0x572,
                   1);
    system_exit(-1);
  }

  node_index = *(int16_t *)((char *)path + 0x1108a);
  if (node_index < 0 || node_index >= 0x400) {
    display_assert("heap_node>=0 && heap_node<MAXIMUM_PATH_NODE_COUNT",
                   "c:\\halo\\SOURCE\\ai\\path.c", 0x577, 1);
    system_exit(-1);
  }

  node_entry = (char *)path + node_index * 0x44 + 0xb0;
  if (*(int16_t *)(node_entry + 0xb4) != 1) {
    display_assert("path->nodes[heap_node].heap_index==1",
                   "c:\\halo\\SOURCE\\ai\\path.c", 0x579, 1);
    system_exit(-1);
  }
  node_cost = *(int16_t *)(node_entry + 0);
  if (node_cost != *(int16_t *)((char *)path + 0x1108c)) {
    display_assert("path->nodes[heap_node].estimated_distance==heap_cost",
                   "c:\\halo\\SOURCE\\ai\\path.c", 0x57a, 1);
    system_exit(-1);
  }

  *(int16_t *)(node_entry + 0xb4) = -1;
  *(int16_t *)((char *)path + 0x11084) = heap_size - 1;
  heap_size = *(int16_t *)((char *)path + 0x11084);

  if (heap_size > 1) {
    *(int32_t *)((char *)path + 0x1108a) =
        *(int32_t *)((char *)path + heap_size * 4 + 0x11086);
    path_heap_bubble_down(path, 1);
  }

  return node_index;
}

/* 0x5e680 — insert a node into the path heap and bubble it up. */
void path_heap_insert(void *path, int16_t heap_node, int16_t heap_cost)
{
  int16_t heap_size;
  int16_t heap_index;

  heap_size = *(int16_t *)((char *)path + 0x11084);
  if (heap_size < 1) {
    display_assert("path->heap_size>=1", "c:\\halo\\SOURCE\\ai\\path.c", 0x594,
                   1);
    system_exit(-1);
  }

  if (heap_size >= 0x400) {
    error(2, (char *)0x0025e250);
    return;
  }

  heap_index = heap_size;
  *(int16_t *)((char *)path + 0x11084) = heap_size + 1;
  *(int16_t *)((char *)path + heap_index * 4 + 0x11086) = heap_node;
  *(int16_t *)((char *)path + heap_index * 4 + 0x11088) = heap_cost;
  path_heap_bubble_up(path, heap_index);
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

/* 0x5e9b0 — test whether a path can approach a firing-position point. */
char path_state_approach_point(void *path_state, float *fp_results, int fp_count,
                               char *out_byte, char *out_dest)
{
  char *path;
  short node_index;
  char *node;
  short parent_index;
  char march_result[0x1c];

  path = (char *)path_state;
  node_index = path_node_from_hash_table(path, (unsigned int)fp_count);
  if (node_index == -1)
    return 0;

  node = path_get_node(path, node_index);
  if (*(int16_t *)(node + 2) == -1)
    goto write_result;

  for (;;) {
    char *parent;

    parent_index = *(int16_t *)(node + 2);
    parent = path_get_node(path, parent_index);
    if (FUN_000639e0((int)*(void **)(path + 0x64),
                     *(unsigned char *)(path + 4), fp_results, fp_count,
                     (float *)(parent + 0xc), *(int *)(parent + 8),
                     march_result))
      goto write_result;

    node = parent;
    if (*(int16_t *)(node + 2) == -1)
      break;
  }

write_result:
  if (out_dest == NULL) {
    display_assert("destination", "c:\\halo\\SOURCE\\ai\\path.c", 0x12d, 1);
    system_exit(-1);
  }
  if (out_byte == NULL) {
    display_assert("approach_point", "c:\\halo\\SOURCE\\ai\\path.c", 0x12e, 1);
    system_exit(-1);
  }

  if (*(int16_t *)(node + 2) == -1) {
    *out_byte = 1;
    *(int *)out_dest = *(int *)(path + 0x14);
    *(int *)((char *)out_dest + 4) = *(int *)(path + 0x18);
    *(int *)((char *)out_dest + 8) = *(int *)(path + 0x1c);
  } else {
    *out_byte = 0;
    *(int *)out_dest = *(int *)(node + 0xc);
    *(int *)((char *)out_dest + 4) = *(int *)(node + 0x10);
    *(int *)((char *)out_dest + 8) = *(int *)(node + 0x14);
  }
  return 1;
}

/* 0x5ef80 — allocate the initial path-search node and heap-insert it. */
char FUN_0005ef80(unsigned int *path_buf)
{
  char *path;
  int focus_surface;
  int16_t node_index;
  int16_t estimated_cost;
  char *node;
  unsigned int hash_slot;
  void *scenario;
  void *bsp;
  float dist_sq;
  float dist;
  int cost_i;

  path = (char *)path_buf;
  focus_surface = *(int *)(path + 0x20);
  if (focus_surface == -1)
    return 0;

  if (*(float *)(path + 0x1c) >= -1000.0f)
    return 0;

  scenario = *(void **)(path + 0x64);
  bsp = tag_block_get_element((char *)scenario + 0xb0, 0, 0x60);
  if (focus_surface < 0 ||
      focus_surface >= *(int *)((char *)bsp + 0x3c)) {
    display_assert("current_surface>=0 && "
                   "current_surface<scenario->structure_bsp.surface_count",
                   "c:\\halo\\SOURCE\\ai\\path.c", 0x2b1, 1);
    system_exit(-1);
  }

  cost_i = 0;
  estimated_cost = 0;
  if (*(char *)(path + 0x4c) != 0) {
    float dx;
    float dy;
    float dz;

    dx = *(float *)(path + 0x50) - *(float *)(path + 0x14);
    dy = *(float *)(path + 0x54) - *(float *)(path + 0x18);
    dz = *(float *)(path + 0x58) - *(float *)(path + 0x1c);
    dist_sq = dx * dx + dy * dy + dz * dz;
    dist = sqrtf(dist_sq);
    cost_i = (int)(dist * *(float *)0x253f34);
    if (cost_i >= 0x7fff) {
      error(2, (char *)0x0025e448);
      return 0;
    }
    estimated_cost = (int16_t)cost_i;
  }

  if (*(int16_t *)(path + 0x80) == 0) {
    display_assert("state->node_count>0", "c:\\halo\\SOURCE\\ai\\path.c", 0x2cc,
                   1);
    system_exit(-1);
  }

  node_index = *(int16_t *)(path + 0x80);
  node = path + node_index * 0x44 + 0x84;
  *(int16_t *)(path + 0x80) = node_index + 1;

  *(int16_t *)(node + 2) = -1;
  *(int *)(node + 4) = -1;
  *(int *)(node + 8) = focus_surface;
  *(int *)(node + 0xc) = *(int *)(path + 0x14);
  *(int *)(node + 0x10) = *(int *)(path + 0x18);
  *(int *)(node + 0x14) = *(int *)(path + 0x1c);
  *(int *)(node + 0x18) = 0;
  *(int *)(node + 0x20) = 0;
  *(int *)(node + 0x24) = 0;
  *(int *)(node + 0x1c) = 0x7f7fffff;
  *(int16_t *)(node + 0x2e) = 0;
  *(int16_t *)(node + 0x32) = -1;
  *(int *)(node + 0x28) = cost_i;
  *(int16_t *)(node + 0x2c) = estimated_cost;

  if (*(char *)(path + 0x4c) != 0) {
    *(int *)(path + 0x6c) = cost_i;
    *(int16_t *)(path + 0x68) = node_index;
    *(float *)(path + 0x74) = *(float *)(path + 0x14);
    *(float *)(path + 0x78) = *(float *)(path + 0x18);
    *(float *)(path + 0x7c) = *(float *)(path + 0x1c);
    *(int *)(path + 0x70) = cost_i;
  }

  hash_slot = (unsigned int)(focus_surface & 0x1ff) << 4;
  *(int16_t *)(path + hash_slot + 0x1208a) = node_index;
  path_heap_insert(path, node_index, estimated_cost);
  return 1;
}

/* 0x5f1d0 */
void FUN_0005f1d0(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  collision_surface_find_closest_point2d(eax, 0, 2, 1, (float *)(uintptr_t)edi, (void *)0);
  collision_surface_project_point2d(eax, 0, 2, 1, (void *)0, (float *)(uintptr_t)esi);

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x5f240 */
void build_path_edges_for_surface(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int local_10 = 0;
  int local_c = 0;

  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* relift: cmp edi, dword ptr [esi + 0x3c] -> jl 0x5f294 */
  display_assert((char *)0x0025e584, (char *)0x0025e0ac, 1496, 1);
  system_exit(-1);
  tag_block_get_element((void *)((char *)eax + 0x3c), 0, 12);
  tag_block_get_element((void *)(uintptr_t)local_10, 0, 24);
  /* test eax, eax -> jl 0x5f30b */
  /* relift: cmp eax, dword ptr [ecx] -> jl 0x5f32b */
  display_assert((char *)0x0025e528, (char *)0x0025e0ac, 1518, 1);
  system_exit(-1);
  tag_block_get_element((void *)(uintptr_t)local_c, *(int *)(eax), 16);
  tag_block_get_element((void *)(uintptr_t)local_c, 0, 16);
  /* relift: cmp edi, dword ptr [eax + 4] -> jne 0x5f2ba */

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)local_10;
  (void)local_c;
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
  display_assert((char *)0x0025e5c4, (char *)0x0025e0ac, 1631, 1);
  system_exit(-1);

  (void)esi;
}

/* 0x5f550 */
char path_state_estimated_distance(void *path_state, void *fp_element, int surface_index, float *result, float *opt_min_clearance, float *opt_out_vec)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int local_4 = 0;

  path_node_from_hash_table((char *)(uintptr_t)path_state, surface_index);
  display_assert((char *)0x0025e5c4, (char *)0x0025e0ac, 334, 1);
  system_exit(-1);
  /* cmp (int16_t)ebx, -1 -> je 0x5f706 */
  path_get_node((char *)(uintptr_t)path_state, eax);
  closest_point_to_attractor();
  /* test (char)eax, 0x41 -> jne 0x5f63c */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* test eax, eax -> je 0x5f647 */
  path_get_node((char *)(uintptr_t)path_state, local_4);
  /* cmp (int16_t)esi, -1 -> jne 0x5f670 */
  /* cmp (int16_t)ebx, (int16_t)esi -> je 0x5f6cd */
  /* relift: relift: fcomp dword ptr [0x2533f0] */
  path_get_node((char *)(uintptr_t)path_state, local_4);
  /* cmp (int16_t)ebx, -1 -> jne 0x5f6d2 */
  normalize3d((float *)0);
  /* test eax, eax -> je 0x5f713 */
  /* test eax, eax -> je 0x5f730 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)local_4;
}

/* 0x5f740 — expand the path search frontier from the cost heap. */
char FUN_0005f740(unsigned int *path_buf)
{
  char *path;
  char success;
  float cost_scale;
  int16_t node_index;
  char *node;
  char edges[0x860];
  int16_t edge_count;
  char *edge;
  int edge_remaining;
  char *scenario;
  int surface_index;
  void *tag_block;
  void *surface_table;
  char process_edge;
  float step_cost;
  float dist_sq;
  float new_cost;
  float focus_dist_sq;
  float step_pos[3];
  float heap_key;

  path = (char *)path_buf;
  success = 1;
  if (*(float *)0x2549d4 >= *(float *)path)
    cost_scale = 0.2f;
  else
    cost_scale = *(float *)path;

  while (1) {
    node_index = path_heap_pop_cheapest_node(path);
    if (node_index == -1)
      break;

    node = path_get_node(path, node_index);
    scenario = (char *)path + *(int *)(path + 0x64);
    tag_block = tag_block_get_element(scenario + 0xb0, 0, 0x60);
    surface_index = *(int *)(node + 8);
    if (surface_index < 0 ||
        surface_index >= *(int *)((char *)tag_block + 0x3c)) {
      display_assert("surface_index>=0 && surface_index<bsp->surfaces.count",
                     "c:\\halo\\SOURCE\\ai\\path.c", 0x35d, 1);
      system_exit(-1);
    }

    if (*(char *)(path + 0x4c) != 0) {
      if (surface_index == *(int *)(path + 0x5c))
        goto copy_goal_state;
      if (*(float *)(path + 0x6c) < *(float *)0x254cc4)
        step_cost = *(float *)0x254cc4;
      else
        step_cost = *(float *)(path + 0x6c);
      step_cost = step_cost * *(float *)0x253f34 + *(float *)(path + 0x70);
      if (*(float *)(node + 0x28) <= step_cost)
        goto mark_unreachable;
    }

    build_path_edges_for_surface();
    edge_count = 0;
    if (edge_count <= 0)
      continue;

    edge = edges + 0x28;
    edge_remaining = edge_count;
    while (edge_remaining-- > 0) {
      process_edge = 1;
      if (*(char *)(path + 4) == 0 && *(char *)(edge - 0x14) < 0) {
        surface_table = tag_block_get_element(scenario + 0xb0, 0, 0x60);
        tag_block = tag_block_get_element((char *)surface_table + 0x3c, 0, 0xc);
        tag_block = tag_block_get_element(tag_block, *(int *)(edge - 0x18), 0x10);
        if ((*(char *)((char *)tag_block + 8) & 8) != 0) {
          if (breakable_surfaces_get_bsp_surface_data() == 0)
            process_edge = 0;
        }
      }
      if (!process_edge)
        goto next_edge;

      step_cost = cost_scale / *(float *)(edge - 0x34);
      if (step_cost > *(float *)0x2533c8)
        step_cost = *(float *)0x2533c8;
      else if (*(float *)0x2533c8 - step_cost > 0.0f)
        step_cost = *(float *)0x2533c8 - step_cost;

      step_pos[0] =
          step_cost * *(float *)(edge - 4) + *(float *)(edge - 0x10);
      step_pos[1] = step_cost * *(float *)edge + *(float *)(edge - 0xc);
      step_pos[2] =
          step_cost * *(float *)(edge + 4) + *(float *)(edge - 8);

      dist_sq = (step_pos[0] - *(float *)(node + 0xc)) *
                    (step_pos[0] - *(float *)(node + 0xc)) +
                (step_pos[1] - *(float *)(node + 0x10)) *
                    (step_pos[1] - *(float *)(node + 0x10)) +
                (step_pos[2] - *(float *)(node + 0x14)) *
                    (step_pos[2] - *(float *)(node + 0x14));
      new_cost = sqrtf(dist_sq) + *(float *)(node + 0x20);
      heap_key = new_cost + *(float *)(node + 0x24);

      if (*(char *)(path + 0x24) != 0) {
        path_attractor_weight();
        if (new_cost + *(float *)0x2533c8 < *(float *)(node + 0x1c))
          step_pos[0] = *(float *)(node + 0x1c);
      }

      if (*(char *)(path + 0x4c) != 0) {
        focus_dist_sq =
            (step_pos[0] - *(float *)(path + 0x50)) *
                (step_pos[0] - *(float *)(path + 0x50)) +
            (step_pos[1] - *(float *)(path + 0x54)) *
                (step_pos[1] - *(float *)(path + 0x54)) +
            (step_pos[2] - *(float *)(path + 0x58)) *
                (step_pos[2] - *(float *)(path + 0x58));
        new_cost = sqrtf(focus_dist_sq) + heap_key;
      }

      if (new_cost - *(float *)(node + 0x28) >= *(float *)0x25e884) {
        display_assert("new_cost-node->cost < MAXIMUM_PATH_COST",
                       "c:\\halo\\SOURCE\\ai\\path.c", 0x3ed, 1);
        system_exit(-1);
      }

      if (*(int16_t *)(edge - 0x10) == -1) {
        path_heap_insert(path, node_index, *(int16_t *)(edge - 0x10));
        continue;
      }

      if (*(int16_t *)(path + (int)*(int16_t *)(edge - 0x10) * 4 + 0x11088) <
          (int16_t)new_cost)
        path_heap_bubble_up(path, *(int16_t *)(edge - 0x10));

      if (*(char *)(path + 0x4c) != 0 &&
          focus_dist_sq <= *(float *)0x2533d8) {
        FUN_0005f1d0();
        *(float *)(path + (int)*(int16_t *)(edge - 0x10) * 4 + 0x11088) =
            new_cost;
        *(int *)(path + 0x50) = *(int *)edge;
        *(int *)(path + 0x54) = *(int *)(edge + 4);
        *(int *)(path + 0x58) = *(int *)(edge + 8);
        *(float *)(path + 0x6c) = new_cost;
        *(int16_t *)(path + 0x68) = *(int16_t *)(edge - 0x10);
        *(float *)(path + 0x70) = heap_key;
      }

    next_edge:
      edge += 0x20;
    }
  }

  if (*(char **)(path + 0x48) != 0 &&
      *(int16_t *)(*(char **)(path + 0x48) + 0x10) == 0)
    *(int16_t *)(*(char **)(path + 0x48) + 0x10) = 3;
  goto finish;

copy_goal_state:
  *(float *)(path + 0x74) = *(float *)(path + 0x50);
  *(float *)(path + 0x78) = *(float *)(path + 0x54);
  *(float *)(path + 0x7c) = *(float *)(path + 0x58);
  *(int16_t *)(path + 0x68) = node_index;
  *(float *)(path + 0x6c) = 0.0f;
  goto finish;

mark_unreachable:
  if (*(char **)(path + 0x48) != 0 &&
      *(int16_t *)(*(char **)(path + 0x48) + 0x10) == 0)
    *(int16_t *)(*(char **)(path + 0x48) + 0x10) = 2;

finish:
  if (*(char *)(path + 0x4c) != 0 &&
      *(float *)(path + 0x6c) > *(float *)(path + 0x60))
    success = 0;
  if (*(char **)(path + 0x48) != 0 &&
      *(int16_t *)(*(char **)(path + 0x48) + 0x10) == 0)
    success = 0;
  return success;
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

/* 0x60140 — map heap slot to path step index */
int16_t FUN_00060140(void *path, int16_t heap_index)
{
  int16_t heap_count;

  heap_count = *(int16_t *)((char *)path + 0x1430);
  if (heap_index < 0 || heap_index >= heap_count || heap_count > 0x80) {
    display_assert(
        "heap_index>=0 && heap_index<path->heap_count && "
        "path->heap_count<=MAXIMUM_PATH_STEPS",
        "c:\\halo\\SOURCE\\ai\\path.h", 49, 1);
    system_exit(-1);
  }
  return *(int16_t *)((char *)path + (int)heap_index * 2 + 0x1432);
}

/* 0x60200 — step cost for heap slot */
float FUN_00060200(void *path, int16_t heap_index)
{
  int16_t step_index;
  char *step;

  step_index = FUN_00060140(path, heap_index);
  if (step_index < 0 || step_index >= *(int16_t *)((char *)path + 0x2c) ||
      *(int16_t *)((char *)path + 0x2c) > 0x80) {
    display_assert("step_index>=0 && step_index<path->step_count && "
                   "path->step_count<=MAXIMUM_PATH_STEPS",
                   "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 40, 1);
    system_exit(-1);
  }
  step = (char *)FUN_000600f0(path, step_index);
  return *(float *)step;
}

/* 0x60260 */
void FUN_00060260(void)
{
  int esi = 0;
  int edi = 0;

  /* test (int16_t)eax, (int16_t)eax -> jle 0x60324 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x60288 */
  /* cmp (int16_t)esi, (int16_t)eax -> jge 0x60288 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x602a5 */
  display_assert((char *)0x0025ea40, (char *)0x0025ea14, 49, 1);
  system_exit(-1);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x602c4 */
  /* cmp (int16_t)edi, (int16_t)eax -> jge 0x602c4 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x602e1 */
  display_assert((char *)0x0025e9b0, (char *)0x0025ea14, 40, 1);
  system_exit(-1);
  error(0, (char *)0x0025eab4);
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0x60278 */

  (void)esi;
  (void)edi;
}

static float path_step_heap_cost(void *path, int16_t step_index)
{
  char *step;

  step = (char *)FUN_000600f0(path, step_index);
  return *(float *)step;
}

static void path_assert_heap_index(void *path, int16_t heap_index, int line_kind)
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

/* 0x60330 — validate min-heap order on path->heap indices */
char FUN_00060330(void *path, const char *debug_context)
{
  int16_t heap_count;
  int heap_index;
  int16_t child_step;
  int16_t parent_step;
  float child_cost;
  float parent_cost;

  heap_count = *(int16_t *)((char *)path + 0x1430);
  if (heap_count <= 1)
    return 1;

  for (heap_index = 1; heap_index < heap_count; heap_index++) {
    int parent_index = (heap_index - 1) / 2;

    path_assert_heap_index(path, (int16_t)heap_index, 0);
    path_assert_heap_index(path, (int16_t)parent_index, 0);
    child_step =
        *(int16_t *)((char *)path + heap_index * 2 + 0x1432);
    parent_step =
        *(int16_t *)((char *)path + parent_index * 2 + 0x1432);
    child_cost = path_step_heap_cost(path, child_step);
    parent_cost = path_step_heap_cost(path, parent_step);
    if (child_cost >= parent_cost)
      continue;

    error(2, debug_context);
    error(2, "c:\\halo\\SOURCE\\ai\\path.h");
    FUN_00060260();
    return 0;
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

/* 0x60910 — push step_index onto path cost heap */
char FUN_00060910(void *path, int16_t step_index)
{
  int16_t heap_count;
  int16_t new_heap_count;

  FUN_00060330(path, "path_add_step");
  heap_count = *(int16_t *)((char *)path + 0x1430);
  if (heap_count >= 0x80)
    return 0;

  new_heap_count = heap_count + 1;
  *(int16_t *)((char *)path + 0x1430) = new_heap_count;
  (void)FUN_000600f0(path, new_heap_count);
  *(int16_t *)((char *)path + (int)heap_count * 2 + 0x1432) = step_index;
  FUN_000604e0(path, heap_count);
  FUN_00060330(path, "path_add_step");
  return 1;
}

/* 0x60970 — pop cheapest step index from path heap */
int16_t FUN_00060970(void *path)
{
  int16_t heap_count;
  int16_t root_step;
  int16_t last_step;

  FUN_00060330(path, "path_pop_step");
  heap_count = *(int16_t *)((char *)path + 0x1430);
  if (heap_count <= 0)
    return -1;

  heap_count--;
  *(int16_t *)((char *)path + 0x1430) = heap_count;
  last_step = *(int16_t *)((char *)path + (int)heap_count * 2 + 0x1432);
  root_step = *(int16_t *)((char *)path + 0x1432);
  *(int16_t *)((char *)path + 0x1432) = last_step;
  FUN_00060670(path, 0);
  FUN_00060330(path, "path_pop_step");
  return root_step;
}

/* 0x609e0 — render / validate existing path steps */
void FUN_000609e0(void *path)
{
  int16_t step_count;

  step_count = *(int16_t *)((char *)path + 0x2c);
  if (step_count <= 0)
    return;

  tag_block_get_element(*(void **)((char *)path + 0xc), 0, 0x60);
  /* remaining step projection loop still relift stub */
}
