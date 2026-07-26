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

/* path_state_build_path (0x5eae0) — XBE naked draft (batch 79). */
#if defined(__clang__)
static short (*const b5eae0_c5e7e0)(char *param_1, unsigned int param_2) = path_node_from_hash_table;
static char * (*const b5eae0_c5e760)(char *param_1, short param_2) = path_get_node;
static void (*const b5eae0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b5eae0_exitfn)(int) = system_exit;
static short (*const b5eae0_cfff80)(void) = game_connection;
static void * (*const b5eae0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static char (*const b5eae0_c633b0)(unsigned int param_1, int param_2, void *param_3, int *param_4, void *param_5, char *param_6) = FUN_000633b0;
static char (*const b5eae0_c61750)(unsigned int param_1, int param_2, void *param_3, int *param_4, void *param_5, char *param_6) = FUN_00061750;
static float (*const b5eae0_c1ad60)(float *a, float *b) = FUN_0001ad60;

__attribute__((naked, noinline))
char path_state_build_path(unsigned int path_buf __attribute__((unused)), unsigned int *nav_state_out __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x498, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl 0x48(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "je .Lpath_state_build_path_1\n\t"
      "movw $0, 0x12(%%eax)\n\t"
      ".Lpath_state_build_path_1:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movb $0, (%%esi)\n\t"
      "movb 0x4c(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lpath_state_build_path_23\n\t"
      "movl 0x5c(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c5e7e0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "je .Lpath_state_build_path_2\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c5e760]\n\t"
      "leal 0x4(%%esi), %%edi\n\t"
      "leal 0x50(%%ebx), %%esi\n\t"
      "movl $5, %%ecx\n\t"
      "rep movsl\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl $0, 0x14(%%ecx)\n\t"
      "movl %%ecx, %%esi\n\t"
      "jmp .Lpath_state_build_path_3\n\t"
      ".Lpath_state_build_path_2:\n\t"
      "flds 0x6c(%%ebx)\n\t"
      "fcomps 0x60(%%ebx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lpath_state_build_path_22\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x68(%%ebx), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "call *%[c5e760]\n\t"
      "leal 0x74(%%ebx), %%edx\n\t"
      "movl (%%edx), %%edi\n\t"
      "leal 0x4(%%esi), %%ecx\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%edi\n\t"
      "movl %%edi, 0x4(%%ecx)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x10(%%esi)\n\t"
      "movl 0x6c(%%ebx), %%edx\n\t"
      "movl %%edx, 0x14(%%esi)\n\t"
      ".Lpath_state_build_path_3:\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $-1, -0x10(%%ebp)\n\t"
      "je .Lpath_state_build_path_22\n\t"
      "movswl 0x2e(%%eax), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "incl %%eax\n\t"
      "cmpl $0x40, %%eax\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movb $1, 0xb(%%ebp)\n\t"
      "movl $0xffffffff, -0x18(%%ebp)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl $0x40, -0x8(%%ebp)\n\t"
      "jg .Lpath_state_build_path_4\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".Lpath_state_build_path_4:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c5e760]\n\t"
      "movl %%eax, %%edi\n\t"
      "movw 0x2e(%%edi), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0x40, %%ax\n\t"
      "jl .Lpath_state_build_path_5\n\t"
      "movb $0, 0xb(%%ebp)\n\t"
      "jmp .Lpath_state_build_path_10\n\t"
      ".Lpath_state_build_path_5:\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lpath_state_build_path_6\n\t"
      "cmpw -0x8(%%ebp), %%ax\n\t"
      "jl .Lpath_state_build_path_7\n\t"
      ".Lpath_state_build_path_6:\n\t"
      "pushl $1\n\t"
      "pushl $0x1e8\n\t"
      "pushl $0x25e0ac\n\t"
      "pushl $0x25e398\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpath_state_build_path_7:\n\t"
      "movswl 0x2e(%%edi), %%ecx\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "shll $4, %%ecx\n\t"
      "cmpw $-1, -0x18(%%ebp)\n\t"
      "movl %%edx, -0x498(%%ebp,%%ecx,1)\n\t"
      "movswl 0x2e(%%edi), %%eax\n\t"
      "jne .Lpath_state_build_path_8\n\t"
      "shll $4, %%eax\n\t"
      "leal -0x494(%%ebp,%%eax,1), %%ecx\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "jmp .Lpath_state_build_path_10\n\t"
      ".Lpath_state_build_path_8:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movswl 0x2e(%%ecx), %%edx\n\t"
      "decl %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "je .Lpath_state_build_path_9\n\t"
      "pushl $1\n\t"
      "pushl $0x1f0\n\t"
      "pushl $0x25e0ac\n\t"
      "pushl $0x25e370\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpath_state_build_path_9:\n\t"
      "movswl 0x2e(%%edi), %%edx\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "addl $0xc, %%ecx\n\t"
      "shll $4, %%edx\n\t"
      "leal -0x494(%%ebp,%%edx,1), %%eax\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      ".Lpath_state_build_path_10:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2(%%edi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl %%edi, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jne .Lpath_state_build_path_4\n\t"
      "cmpw %%ax, %%dx\n\t"
      "jne .Lpath_state_build_path_11\n\t"
      "pushl $1\n\t"
      "pushl $0x1fb\n\t"
      "pushl $0x25e0ac\n\t"
      "pushl $0x25e354\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpath_state_build_path_11:\n\t"
      "cmpw $0, 0x2e(%%edi)\n\t"
      "je .Lpath_state_build_path_12\n\t"
      "pushl $1\n\t"
      "pushl $0x1fc\n\t"
      "pushl $0x25e0ac\n\t"
      "pushl $0x25e33c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpath_state_build_path_12:\n\t"
      "call *%[cfff80]\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lpath_state_build_path_14\n\t"
      "movb 0x5ac9d0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lpath_state_build_path_14\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "cmpw $4, %%di\n\t"
      "movl $4, %%eax\n\t"
      "jg .Lpath_state_build_path_13\n\t"
      "movl %%edi, %%eax\n\t"
      ".Lpath_state_build_path_13:\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x498(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x58(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Lpath_state_build_path_15\n\t"
      ".Lpath_state_build_path_14:\n\t"
      "leal 0xb(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "leal -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x498(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c633b0]\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "addl $0x18, %%esp\n\t"
      ".Lpath_state_build_path_15:\n\t"
      "call *%[cfff80]\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lpath_state_build_path_17\n\t"
      "movb 0x5ac9cf, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lpath_state_build_path_17\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "cmpw $4, %%ax\n\t"
      "jle .Lpath_state_build_path_16\n\t"
      "movl $4, %%eax\n\t"
      ".Lpath_state_build_path_16:\n\t"
      "movswl %%ax, %%edx\n\t"
      "shll $4, %%edx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x98(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Lpath_state_build_path_19\n\t"
      ".Lpath_state_build_path_17:\n\t"
      "leal 0xb(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x98(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x58(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c61750]\n\t"
      "movl 0x48(%%ebx), %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Lpath_state_build_path_18\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lpath_state_build_path_19\n\t"
      "movw $4, 0x12(%%ecx)\n\t"
      "jmp .Lpath_state_build_path_21\n\t"
      ".Lpath_state_build_path_18:\n\t"
      "testb %%al, %%al\n\t"
      "je .Lpath_state_build_path_21\n\t"
      ".Lpath_state_build_path_19:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movb 0xb(%%ebp), %%cl\n\t"
      "movswl %%ax, %%edx\n\t"
      "shll $4, %%edx\n\t"
      "movb %%al, 0x19(%%esi)\n\t"
      "pushl %%edx\n\t"
      "leal -0x98(%%ebp), %%eax\n\t"
      "movb %%cl, 0x18(%%esi)\n\t"
      "pushl %%eax\n\t"
      "leal 0x1c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movb $1, (%%esi)\n\t"
      "movb $0, 0x1a(%%esi)\n\t"
      "call *%[c8e0b0]\n\t"
      "movb 0x18(%%esi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lpath_state_build_path_20\n\t"
      "movsbl 0x19(%%esi), %%edx\n\t"
      "shll $4, %%edx\n\t"
      "leal (%%edx,%%esi,1), %%eax\n\t"
      "leal 0x10(%%eax), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "movl (%%edx), %%edi\n\t"
      "leal 0x4(%%esi), %%ecx\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl %%edi, (%%esi)\n\t"
      "movl 0x4(%%edx), %%edi\n\t"
      "movl %%edi, 0x4(%%esi)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%esi)\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "leal 0x50(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, 0x10(%%esi)\n\t"
      "call *%[c1ad60]\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "fstps 0x14(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      ".Lpath_state_build_path_20:\n\t"
      "movl 0x48(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lpath_state_build_path_21\n\t"
      "movw $5, 0x12(%%eax)\n\t"
      ".Lpath_state_build_path_21:\n\t"
      "movl 0x48(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lpath_state_build_path_24\n\t"
      "movw %%di, 0x140fc(%%eax)\n\t"
      "movl 0x48(%%ebx), %%edx\n\t"
      "movswl %%di, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x498(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $0x14100, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8e0b0]\n\t"
      "movl 0x48(%%ebx), %%eax\n\t"
      "movw -0x4(%%ebp), %%cx\n\t"
      "movw %%cx, 0x14500(%%eax)\n\t"
      "movswl -0x4(%%ebp), %%edx\n\t"
      "movl 0x48(%%ebx), %%ecx\n\t"
      "shll $4, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "addl $0x14504, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8e0b0]\n\t"
      "movl 0x48(%%ebx), %%edx\n\t"
      "movw -0xc(%%ebp), %%ax\n\t"
      "movw %%ax, 0x14544(%%edx)\n\t"
      "movswl -0xc(%%ebp), %%ecx\n\t"
      "movl 0x48(%%ebx), %%eax\n\t"
      "shll $4, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x98(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl $0x14548, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0x24, %%esp\n\t"
      "jmp .Lpath_state_build_path_24\n\t"
      ".Lpath_state_build_path_22:\n\t"
      "movl 0x48(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lpath_state_build_path_24\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw $-1, 0x68(%%ebx)\n\t"
      "setne %%cl\n\t"
      "addl $2, %%ecx\n\t"
      "movw %%cx, 0x12(%%eax)\n\t"
      "jmp .Lpath_state_build_path_24\n\t"
      ".Lpath_state_build_path_23:\n\t"
      "movl 0x48(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lpath_state_build_path_24\n\t"
      "movw $1, 0x12(%%eax)\n\t"
      ".Lpath_state_build_path_24:\n\t"
      "movl 0x48(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lpath_state_build_path_27\n\t"
      "leal 0x140a0(%%eax), %%edi\n\t"
      "movl $0x17, %%ecx\n\t"
      "rep movsl\n\t"
      "movl 0x48(%%ebx), %%eax\n\t"
      "cmpw $5, 0x12(%%eax)\n\t"
      "je .Lpath_state_build_path_25\n\t"
      "movb $1, 0xd(%%eax)\n\t"
      ".Lpath_state_build_path_25:\n\t"
      "movl 0x48(%%ebx), %%edx\n\t"
      "cmpw $0, 0x12(%%edx)\n\t"
      "jne .Lpath_state_build_path_26\n\t"
      "pushl $1\n\t"
      "pushl $0x265\n\t"
      "pushl $0x25e0ac\n\t"
      "pushl $0x25e300\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movb (%%eax), %%al\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lpath_state_build_path_26:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movb (%%ecx), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lpath_state_build_path_27:\n\t"
      "movb (%%esi), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c5e7e0] "m"(b5eae0_c5e7e0), [c5e760] "m"(b5eae0_c5e760), [assert] "m"(b5eae0_assert), [exitfn] "m"(b5eae0_exitfn), [cfff80] "m"(b5eae0_cfff80), [c8e0b0] "m"(b5eae0_c8e0b0), [c633b0] "m"(b5eae0_c633b0), [c61750] "m"(b5eae0_c61750), [c1ad60] "m"(b5eae0_c1ad60)
      : "memory");
}
#else
#error "path_state_build_path: clang naked draft required"
#endif


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

/* 0x5f240 — enumerate BSP surface edges into a path-search buffer. */
int16_t build_path_edges_for_surface(void *scenario, int surface_index,
                                     char *out_edges)
{
  char *sc;
  char *bsp;
  char *surfaces_block;
  char *surface;
  char *surfaces_count_ptr;
  char *edges_block;
  char *vertices_block;
  char *sector_map;
  int edge_link;
  int16_t out_count;
  char matched;
  int adj_slot;

  sc = (char *)scenario;
  bsp = tag_block_get_element(sc + 0xb0, 0, 0x60);
  if (surface_index < 0 || surface_index >= *(int *)(bsp + 0x3c)) {
    display_assert("surface_index>=0 && surface_index<bsp->surfaces.count",
                   "c:\\halo\\SOURCE\\ai\\path.c", 0x5d8, 1);
    system_exit(-1);
  }

  surfaces_block = tag_block_get_element(bsp + 0x3c, 0, 0xc);
  surface = tag_block_get_element(surfaces_block, surface_index, 0x18);
  surfaces_count_ptr = bsp + 0x3c;
  edges_block = bsp + 0x48;
  vertices_block = bsp + 0x54;
  sector_map = *(char **)(sc + 0x1e8);

  edge_link = *(int *)(surface + 4);
  out_count = 0;

  for (;;) {
    char *edge_desc;
    char *out;
    int adj_surface;
    float *vert_a;
    float *vert_b;

    edge_desc = tag_block_get_element(edges_block, edge_link, 0x18);
    matched = (char)(surface_index == *(int *)(edge_desc + 0x14));
    adj_slot = matched ? 0 : 1;

    out = out_edges + (int)out_count * 0x20;
    adj_surface = *(int *)(edge_desc + adj_slot * 4 + 0x10);
    *(int *)out = adj_surface;

    if (adj_surface != -1) {
      if (adj_surface < 0 || adj_surface >= *(int *)surfaces_count_ptr) {
        display_assert(
            "adjacent_surface_index>=0 && "
            "adjacent_surface_index<bsp->surfaces.count",
            "c:\\halo\\SOURCE\\ai\\path.c", 0x5ee, 1);
        system_exit(-1);
      }
      *(char *)(out + 4) = sector_map[adj_surface];
    } else {
      *(char *)(out + 4) = 0;
    }

    vert_a = tag_block_get_element(vertices_block, *(int *)edge_desc, 0x10);
    vert_b = tag_block_get_element(vertices_block, *(int *)(edge_desc + 4), 0x10);
    *(float *)(out + 8) = vert_a[0];
    *(float *)(out + 0xc) = vert_a[1];
    *(float *)(out + 0x10) = vert_a[2];
    *(float *)(out + 0x14) = vert_b[0] - vert_a[0];
    *(float *)(out + 0x18) = vert_b[1] - vert_a[1];
    *(float *)(out + 0x1c) = vert_b[2] - vert_a[2];

    out_count++;
    if (out_count >= 0x40)
      break;

    edge_link = *(int *)(edge_desc + adj_slot * 4 + 8);
    if (edge_link == *(int *)(surface + 4))
      break;
  }

  return out_count;
}

/* 0x5f3c0 — closest point on a segment to a reference point. */
void closest_point_to_attractor(float *segment_start, float *segment_end,
                                float *reference, float *out_point)
{
  float delta[3];
  float to_ref[3];
  float denom;
  float t;

  delta[0] = segment_end[0] - segment_start[0];
  delta[1] = segment_end[1] - segment_start[1];
  delta[2] = segment_end[2] - segment_start[2];

  to_ref[0] = reference[0] - segment_start[0];
  to_ref[1] = reference[1] - segment_start[1];
  to_ref[2] = reference[2] - segment_start[2];

  denom = delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2];
  t = (to_ref[0] * delta[0] + to_ref[1] * delta[1] + to_ref[2] * delta[2]) /
      denom;

  if (t >= *(float *)0x2533c0 && t <= *(float *)0x2533c8) {
    out_point[0] = segment_start[0] + t * delta[0];
    out_point[1] = segment_start[1] + t * delta[1];
    out_point[2] = segment_start[2] + t * delta[2];
    return;
  }

  out_point[0] = segment_end[0];
  out_point[1] = segment_end[1];
  out_point[2] = segment_end[2];
}

/* 0x5f490 — compute path attractor weight from a step position. */
float path_attractor_weight(void *path_state, float *node_pos, float *step_pos,
                            float *out_dist)
{
  char *path;
  float closest[3];
  float delta[3];
  float dist_sq;
  float dist;
  float weight;

  path = (char *)path_state;
  closest_point_to_attractor(step_pos, (float *)(path + 0x28), node_pos,
                             closest);

  delta[0] = closest[0] - *(float *)(path + 0x28);
  delta[1] = closest[1] - *(float *)(path + 0x2c);
  delta[2] = closest[2] - *(float *)(path + 0x30);
  dist_sq = delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2];

  weight = 0.0f;
  dist = 3.4028235e38f;
  if (dist_sq < *(float *)(path + 0x38) * *(float *)(path + 0x38)) {
    dist = sqrtf(dist_sq);
    weight = (*(float *)0x2533c8 - dist / *(float *)(path + 0x38)) *
             *(float *)(path + 0x3c);
  }

  if (out_dist == 0) {
    display_assert("out_dist",
                   "c:\\halo\\SOURCE\\ai\\path.c", 0x65f, 1);
    system_exit(-1);
  }
  *out_dist = dist;
  return weight;
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
  /* relift: closest_point_to_attractor(...) */
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
static void (*const b5f740_c5e150)(void *path, int16_t heap_index) = path_heap_bubble_up;
static void (*const b5f740_c5f1d0)(void) = FUN_0005f1d0;

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
