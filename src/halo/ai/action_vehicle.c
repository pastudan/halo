/* action_vehicle.c — AI actor "enter vehicle" action setup.
 *
 * Corresponds to action_vehicle.obj.
 * Assertion path: c:\halo\SOURCE\ai\action_vehicle.c
 *
 * Recovered by lifting FUN_0001b750 from cachebeta.xbe (v01.10.12.2276).
 * This function was mis-filed under real_math.obj by whole-object address-range
 * grouping; its behaviour (actor datum lookup, vehicle-seat attach-point query,
 * actor_move_to_point) and the embedded assert path place it in
 * ai/action_vehicle.c.
 */

#include "../../common.h"

/* FUN_0001b750 (0x1b750) — Build the state buffer for an actor's "enter
 * vehicle" action and start the actor moving toward the entry point.
 *
 * Zeroes the 0x4c-byte action state buffer, then (only when the actor is not
 * already assigned to a vehicle: actor+0x158 == -1 and actor+0x6 == 0) verifies
 * the target object is a vehicle whose speed (object+0x38) is at or above the
 * global threshold at 0x253398 and whose object+0xb6 bit 2 is clear. On success
 * it records the vehicle handle / seat index into the state buffer, computes
 * the seat attach transform (FUN_0001aeb0 -> FUN_0001b280), and issues an
 * actor_move_to_point toward the computed entry position.
 *
 * Returns 1 only when every check passes and actor_move_to_point succeeds;
 * otherwise 0.
 *
 * Confirmed (delinked disasm 0x1b750-0x1b897):
 *   datum pool = actor_data (*0x6325a4); actor+0x18 = unit_handle.
 *   object_get_and_verify_type(vehicle_handle, 3); object+0x38 float speed.
 *   FPU: continue iff speed >= *(float*)0x253398 (fld speed; fcomp threshold).
 *   object+0xb6 is a byte; continue iff (~(b>>2)) & 1 (bit 2 clear).
 *   state buffer: +0 = vehicle handle (dword), +4 = seat index (word), +6 = 0.
 *   FUN_0001b280: ECX = actor_handle, EAX = vehicle_handle, out at
 * buf+0x30/+0x48. Note: the second datum_get(actor_data, actor_handle) is
 * present in the original; its result is immediately overwritten by
 * object_get_and_verify_type and never used (preserved here for fidelity).
 */
char FUN_0001b750(int actor_handle, int vehicle_handle, int16_t seat_index,
                  short *state_data)
{
  char *actor;
  char *object;
  volatile long ok; /* volatile: forces the memory store of ok=0, matching
                     * original VC71 codegen (permuter, 86.7% -> 90.8%). */
  float attach[9];

  actor = (char *)datum_get(actor_data, actor_handle);
  ok = 0;
  assert_halt(state_data != 0);
  csmemset(state_data, 0, 0x4c);
  if (*(int *)(actor + 0x158) == -1 && *(char *)(actor + 6) == 0) {
    (void)datum_get(actor_data, actor_handle);
    object = (char *)object_get_and_verify_type(vehicle_handle, 3);
    if (*(float *)(object + 0x38) >= *(float *)0x253398 &&
        (~(*(unsigned char *)(object + 0xb6) >> 2) & 1) != 0) {
      *(int *)state_data = vehicle_handle;
      *(int16_t *)((char *)state_data + 4) = seat_index;
      *((char *)state_data + 6) = 0;
      if (unit_has_animation_to_enter_seat(
            *(int *)(actor + 0x18), vehicle_handle, seat_index) != '\0' &&
          FUN_0001aeb0(actor_handle, vehicle_handle, seat_index, 1, &attach[0],
                       &attach[3], &attach[6], 0, 0, 0, 0) != '\0' &&
          FUN_0001b280(actor_handle, vehicle_handle, &attach[0], &attach[3],
                       &attach[6], 0, (float *)((char *)state_data + 0x30),
                       (int *)((char *)state_data + 0x48)) != '\0' &&
          actor_move_to_point(
            actor_handle, (float *)((char *)state_data + 0x30),
            *(int *)((char *)state_data + 0x48), vehicle_handle) != '\0') {
        return 1;
      }
    }
  }
  return ok;
}
/* --- action_vehicle.obj batch drafts (2026-07-26) --- */

/* 0x1aeb0 */
char FUN_0001aeb0(int actor_handle, int vehicle_handle, short seat_index, int param_4, float *out_attach0, float *out_attach1, float *out_attach2, int param_8, int param_9, int param_10, int param_11)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;
  int ebp = 0;

  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('rtca', 0);
  tag_get('vtca', 0);
  unit_seat_filled(0, ecx);
  /* test (char)eax, (char)eax -> jne 0x1b276 */
  unit_seat_allow_noncombatants(0, eax);
  /* test (char)eax, (char)eax -> je 0x1b276 */
  unit_get_seat_enter_position(0, 0, ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x1b276 */
  object_get_world_position(0, (void *)(uintptr_t)eax);
  magnitude3d((float *)0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  FUN_00064540((void *)0, 0);
  FUN_00064570((void *)(uintptr_t)edx);
  /* test eax, eax -> je 0x1b0e5 */
  /* test (char)ecx, (char)ecx -> jne 0x1b0d1 */
  /* cmp eax, -1 -> je 0x1b0d1 */
  datum_absolute_index_to_index((void *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [eax + 0x6c], (int16_t)ebx -> jne 0x1b0d1 */
  /* relift: cmp dword ptr [eax + 0x9c], edi -> jne 0x1b0d1 */
  /* relift: cmp (int16_t)ecx, word ptr [ebp + 0x10] -> jne 0x1b0c7 */
  unit_seat_is_driver(0, ecx);
  FUN_00064570((void *)(uintptr_t)ecx);
  /* test eax, eax -> jne 0x1b050 */
  object_get_and_verify_type(0, 0);
  /* test (char)ecx, (char)ecx -> jne 0x1b113 */
  tag_get('ihev', 0);
  unit_seat_is_driver(0, ebx);
  magnitude3d((float *)0);
  /* relift: relift: fcomp dword ptr [0x2533c4] */
  /* test (char)eax, 0x41 -> je 0x1b17d */
  /* relift: relift: fcomp dword ptr [0x253f38] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b1a2 */
  unit_seat_is_gunner(0, 0);
  /* test (char)eax, (char)eax -> jne 0x1b1f1 */
  unit_seat_is_gunner(0, 0);
  /* test (char)eax, (char)eax -> je 0x1b1f1 */
  /* test eax, eax -> je 0x1b20c */
  /* test eax, eax -> je 0x1b224 */
  /* test eax, eax -> je 0x1b23c */
  /* test eax, eax -> je 0x1b247 */
  /* test eax, eax -> je 0x1b255 */
  /* test eax, eax -> je 0x1b261 */
  /* test eax, eax -> je 0x1b26d */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)ebp;
  return 0;
}

/* 0x1b280 */
char FUN_0001b280(int actor_handle, int object_handle, float *in_attach0, float *in_attach1, float *in_attach2, int param_6, float *out_position, int *out_handle)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  datum_get((void *)(uintptr_t)eax, 0);
  object_get_and_verify_type(0, 0);
  tag_get('tinu', 0);
  /* relift: test byte ptr [edi + 0x17c], 0x10 -> jne 0x1b67f */
  FUN_0001aae0(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b32d */
  /* test (char)eax, 0x41 -> je 0x1b38f */
  /* relift: relift: fcomp dword ptr [0x253f4c] */
  game_time_get();
  /* test (char)eax, 0x41 -> jne 0x1b526 */
  /* relift: relift: fcomp dword ptr [0x253f48] */
  perpendicular2d((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b543 */
  /* test (char)eax, (char)eax -> jne 0x1b67f */
  magnitude3d((float *)(uintptr_t)edx);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b67f */
  /* relift: relift: fcomp dword ptr [0x253f44] */
  /* test (char)eax, 0x41 -> jne 0x1b65d */
  /* relift: relift: fcomp dword ptr [0x2533d8] */
  perpendicular2d((float *)0, (float *)0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  magnitude3d((float *)(uintptr_t)edx);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b65d */
  /* relift: relift: fld dword ptr [0x253f40] */
  vector3d_scale_add((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (float *)0);
  global_collision_bsp_get();
  collision_bsp_test_vector(0, 0, 0, 0, 0, 0, 0.0f, (float *)0);
  /* test (char)eax, (char)eax -> je 0x1b743 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)edi;
  return 0;
}
