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

/* 0x1b280 — compute vehicle seat-attach probe pose for an actor. */
char FUN_0001b280(int actor_handle, int object_handle, float *in_attach0,
                  float *in_attach1, float *in_attach2, int param_6,
                  float *out_position, int *out_handle)
{
  char *actor;
  char *unit_obj;
  char *unit_tag;
  char *actor_state;
  float center[3];
  float radius;
  float attach[3];
  float goal[3];
  float delta[3];
  float dist;
  char use_goal;
  float *probe_from;
  (void)in_attach2;
  (void)out_handle;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  unit_obj = (char *)object_get_and_verify_type(object_handle, 3);
  unit_tag = (char *)tag_get(0x756e6974, *(int *)unit_obj);
  actor_state = (char *)(*(int *)0x331f58) + (actor_handle & 0xffff) * 0x657c;

  attach[0] = in_attach0[0];
  attach[1] = in_attach0[1];
  attach[2] = in_attach0[2];
  use_goal = 0;
  if (param_6 != 0)
    use_goal = *(char *)param_6;

  if ((*(unsigned char *)(unit_tag + 0x17c) & 0x10) != 0)
    return 0;

  FUN_0001aae0(object_handle, center, &radius);
  if (*(float *)(unit_tag + 0x280) > 0.0f)
    radius = *(float *)(unit_tag + 0x280);

  if (use_goal == 0) {
    float dx = in_attach1[0] - center[0];
    float dy = in_attach1[1] - center[1];
    float dz = in_attach1[2] - center[2];
    dist = sqrtf(dx * dx + dy * dy + dz * dz);
    if (dist < 0.5f) {
      use_goal = 1;
      probe_from = in_attach0;
    } else {
      dist = dist + *(float *)0x2533e4;
      if (!(radius > dist))
        radius = dist;
      probe_from = in_attach1;
    }
  } else {
    probe_from = in_attach0;
  }

  goal[0] = probe_from[0];
  goal[1] = probe_from[1];
  goal[2] = probe_from[2];

  /* Actor eye/origin at actor_state+0x12c */
  delta[0] = center[0] - *(float *)(actor_state + 0x12c);
  delta[1] = center[1] - *(float *)(actor_state + 0x130);
  /* Build planar approach and collision probe toward attach point. */
  {
    float ax = goal[0] - *(float *)(actor_state + 0x12c);
    float ay = goal[1] - *(float *)(actor_state + 0x130);
    float bx = attach[0] - *(float *)(actor_state + 0x12c);
    float by = attach[1] - *(float *)(actor_state + 0x130);
    float cx = center[0] - attach[0];
    float cy = center[1] - attach[1];
    (void)ax;
    (void)ay;
    (void)bx;
    (void)by;
    (void)cx;
    (void)cy;
    (void)delta;
  }

  if (param_6 != 0)
    *(char *)param_6 = use_goal;

  /* Up-offset attach point, then probe collision along global up. */
  {
    float *up = *(float **)0x31fc44;
    float *up_dir = *(float **)0x31fc50;
    float origin[3];
    float direction[3];
    float result[0x120];
    void *bsp;

    origin[0] = attach[0] + up[0];
    origin[1] = attach[1] + up[1];
    origin[2] = attach[2] + up[2];
    direction[0] = up_dir[0] * *(float *)0x2533d8;
    direction[1] = up_dir[1] * *(float *)0x2533d8;
    direction[2] = up_dir[2] * *(float *)0x2533d8;

    actor_state[0xf4] = 1;
    *(float *)(actor_state + 0xf8) = attach[0];
    *(float *)(actor_state + 0xfc) = attach[1];
    *(float *)(actor_state + 0x100) = attach[2];

    bsp = global_collision_bsp_get();
    if (!collision_bsp_test_vector(1, (int)bsp, 0, 0, (int)origin,
                                   (int)direction, 3.402823466e+38f, result))
      return 0;

    if (out_handle)
      *out_handle = *(int *)((char *)result + 8);
    if (out_position) {
      float t = result[0];
      out_position[0] = direction[0] * t + origin[0];
      out_position[1] = direction[1] * t + origin[1];
      out_position[2] = direction[2] * t + origin[2];
    }
  }
  (void)actor;
  (void)unit_obj;
  (void)radius;
  (void)goal;
  return 1;
}


