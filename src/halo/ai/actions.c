/* actions.c — AI actor action dispatch.
 *
 * Corresponds to actions.obj.
 * Assertion path: c:\halo\SOURCE\ai\actions.c
 */

#include "../../common.h"

/* FUN_0001bba0 (0x1bba0) — Scan a vehicle unit's seats and select the seat
 * whose attach transform yields the greatest score for an actor.
 *
 * Resolves the vehicle object (object_get_and_verify_type(vehicle_handle, 3)),
 * reads its unit definition tag (tag_get('unit', object[0])), then iterates
 * seat indices in [0, unit_def->seat_count @ +0x2e4). For each seat, calls
 * FUN_0001aeb0 to compute three attach vec3s plus a scalar score into scratch
 * buffers; tracks the seat with the maximum score (update only when the new
 * score exceeds the running best). For each non-NULL output pointer, the best
 * seat's corresponding attach vec3 is written on exit. Returns the winning
 * seat index, or -1 if no seat produced a qualifying score.
 *
 * The seat index is compared as a 16-bit value (movsx si before cmp),
 * preserving the original truncating loop bound. The best-vector scratch is
 * deliberately left uninitialized when no seat qualifies, matching the
 * original codegen (garbage is written to non-NULL outputs, which the caller
 * ignores when the returned index is -1).
 *
 * Confirmed: object_get_and_verify_type(vehicle_handle, 3) at 0x1bba0+0xe.
 * Confirmed: tag_get('unit', object[0]) at 0x1bba0+0x17.
 * Confirmed: seat count at unit_def+0x2e4; FCOMP greater-than update. */
int FUN_0001bba0(int actor_handle, int vehicle_handle, float *out_attach0,
                 float *out_attach1, float *out_attach2)
{
  int *object;
  char *unit_def;
  int i;
  int best_index;
  float best_score;
  float score;
  float cand0[3];
  float cand1[3];
  float cand2[3];
  float best0[3];
  float best1[3];
  float best2[3];

  object = (int *)object_get_and_verify_type(vehicle_handle, 3);
  unit_def = (char *)tag_get(0x756e6974 /* 'unit' */, *object);
  best_index = -1;
  best_score = 0.0f;
  for (i = 0; (short)i < *(int *)(unit_def + 0x2e4); i++) {
    if (FUN_0001aeb0(actor_handle, vehicle_handle, (short)i, 0, &cand0[0],
                     &cand1[0], &cand2[0], (int)&score, 0, 0, 0) != '\0') {
      if (best_score < score) {
        best_score = score;
        best0[0] = cand0[0];
        best0[1] = cand0[1];
        best0[2] = cand0[2];
        best1[0] = cand1[0];
        best1[1] = cand1[1];
        best1[2] = cand1[2];
        best2[0] = cand2[0];
        best2[1] = cand2[1];
        best2[2] = cand2[2];
        best_index = i;
      }
    }
  }
  if (out_attach0 != NULL) {
    out_attach0[0] = best0[0];
    out_attach0[1] = best0[1];
    out_attach0[2] = best0[2];
  }
  if (out_attach1 != NULL) {
    out_attach1[0] = best1[0];
    out_attach1[1] = best1[1];
    out_attach1[2] = best1[2];
  }
  if (out_attach2 != NULL) {
    out_attach2[0] = best2[0];
    out_attach2[1] = best2[1];
    out_attach2[2] = best2[2];
  }
  return best_index;
}

/* FUN_0001c030 (0x1c030) — Initialize actor guard state based on combat status.
 * Sets guard mode (0x3e8) to 3/5/1 depending on whether the actor is a
 * designated combatant, has a valid encounter with positive attack count,
 * or is in a default state. Also sets 0x3fc=3 and clears flags at
 * 0x424-0x428, 0x454. */
void FUN_0001c030(int actor_handle)
{
  char *actor;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(char *)(actor + 0x504) != '\0') {
    *(int16_t *)(actor + 0x3e8) = 3;
    *(int16_t *)(actor + 0x3ec) = 0;
  } else if (*(char *)(actor + 0x1cc) == '\0' &&
             *(int *)(actor + 0x1d0) != -1 && *(int16_t *)(actor + 0xa8) > 0) {
    *(int16_t *)(actor + 0x3e8) = 5;
    *(int16_t *)(actor + 0x3ec) = 1;
    *(int *)(actor + 0x3f0) = *(int *)(actor + 0x1d0);
  } else {
    *(int16_t *)(actor + 0x3e8) = 1;
  }
  *(int16_t *)(actor + 0x3fc) = 3;
  *(char *)(actor + 0x454) = 0;
  *(char *)(actor + 0x426) = 0;
  *(char *)(actor + 0x427) = 0;
  *(char *)(actor + 0x428) = 0;
  *(char *)(actor + 0x424) = 0;
  *(char *)(actor + 0x425) = 0;
}

/* FUN_0001c0e0 (0x1c0e0) — readable C lift. */
char FUN_0001c0e0(int actor_handle, char param_2, int state_data)
{
  char *actor;
  char *state;
  char result;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  state = (char *)state_data;
  result = 0;
  if (state == 0) {
    display_assert((const char *)0x25334c, (const char *)0x253f7c, 0x21, 1);
    system_exit(-1);
  }
  csmemset(state, 0, 0x18);
  if (actor[0x160] != 0) {
    return result;
  }
  state[1] = actor[0x1cc];
  state[2] = param_2;
  *(int *)(state + 8) = game_time_get();
  *(short *)(state + 0xe) = 0;
  *(short *)(state + 0xc) = 0x78;
  state[3] = 1;
  *(short *)(state + 0x10) = random_range(
      (unsigned int *)get_global_random_seed_address(), 0x12c, 0x258);
  return 1;
}

/* FUN_0001c190 (0x1c190) — Tick down actor wait/guard timers.
 * Decrements actor+0xac, 0xaa, and 0xa8 counters, triggering sound events and
 * state changes when they reach zero. */
void FUN_0001c190(int actor_handle)
{
  char *actor;
  int16_t sVar1;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(int16_t *)(actor + 0xac) > 0) {
    sVar1 = *(int16_t *)(actor + 0xac) - 1;
    *(int16_t *)(actor + 0xac) = sVar1;
    if (sVar1 == 0) {
      if (*(int *)(actor + 0x18) != -1) {
        FUN_00046f10(0x11, *(int *)(actor + 0x18), -1, -1, -1, -1, 0);
      }
      *(int16_t *)(actor + 0xac) = random_range(
        (unsigned int *)get_global_random_seed_address(), 300, 600);
    }
  }
  if (*(int16_t *)(actor + 0xaa) > 0) {
    sVar1 = *(int16_t *)(actor + 0xaa) - 1;
    *(int16_t *)(actor + 0xaa) = sVar1;
    if (sVar1 == 0) {
      if (*(char *)(actor + 0x9d) != '\0' && *(int *)(actor + 0x18) != -1) {
        FUN_00046f10(0x14, *(int *)(actor + 0x18), -1, -1, -1, -1, 0);
      }
      *(char *)(actor + 0x9c) = 1;
    }
  }
  if (*(char *)(actor + 0x9f) == '\0' && *(int16_t *)(actor + 0xa8) > 0) {
    *(int16_t *)(actor + 0xa8) = *(int16_t *)(actor + 0xa8) - 1;
  }
}

/* actor_action_perform (0x1c300) — actor_execute_current_action
 *
 * Dispatches the current action's execute handler via the action_definitions
 * table. Returns the handler's result, or 0 if no handler is set.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x1c310.
 * Confirmed: actor+0x6c = action index (short), asserted in [0,14).
 * Confirmed: table at 0x253fb8, stride 0x38 (execute handler at +0x14 in
 * entry). Confirmed: handler called with (actor_handle), returns int32_t.
 * Confirmed: returns 0 when handler is NULL (XOR BL,BL; MOV AL,BL at 0x1c369).
 */
int32_t actor_action_perform(int actor_handle)
{
  typedef int32_t (*action_execute_fn_t)(int);

  char *actor;
  short action;
  action_execute_fn_t handler;

  actor = (char *)datum_get(actor_data, actor_handle);
  action = *(short *)(actor + 0x6c);

  assert_halt(action >= 0 && action < 14);

  handler = *(action_execute_fn_t *)(0x253fb8 + action * 0x38);
  if (handler != NULL) {
    return handler(actor_handle);
  }
  return 0;
}

/* actor_action_update (0x1c370) — actor_action_update
 *
 * Dispatches the current action's update handler (table+0x1c) for the given
 * actor. Called each tick from the actor update loop after the decision logic
 * has run.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x1c37f.
 * Confirmed: actor+0x6c = action index (short), asserted in [0, 14) at line
 *   0x9e (158).
 * Confirmed: table at 0x253fbc (action_definitions base 0x253fa0 + entry
 *   stride 0x38 + field offset 0x1c), stride 0x38.
 * Confirmed: handler called with (actor_handle); no return value used by
 *   caller (void dispatch).
 */
void actor_action_update(int actor_handle)
{
  typedef void (*action_update_fn_t)(int);

  char *actor;
  short action;
  action_update_fn_t handler;

  actor = (char *)datum_get(actor_data, actor_handle);
  action = *(short *)(actor + 0x6c);

  assert_halt(action >= 0 && action < 14);

  handler = *(action_update_fn_t *)(0x253fbc + action * 0x38);
  if (handler != NULL) {
    handler(actor_handle);
  }
}

/* actor_action_control (0x1c3e0) — actor_action_notify
 *
 * Dispatches the current action's notify handler (table+0x20) for the given
 * actor. Called each tick from the actor update loop after actor_action_update,
 * as part of the secondary per-tick action dispatch sequence.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x1c3ef.
 * Confirmed: actor+0x6c = action index (short), asserted in [0, 14) at line
 *   0xad (173).
 * Confirmed: table at 0x253fc0 (action_definitions base 0x253fa0 + entry
 *   stride 0x38 + field offset 0x20), stride 0x38.
 * Confirmed: handler called with (actor_handle); no return value used by
 *   caller (void dispatch).
 * Inferred: handler name "notify" — binary only confirms it is the table+0x20
 *   slot; the semantic role is not directly evidenced.
 */
void actor_action_control(int actor_handle)
{
  typedef void (*action_notify_fn_t)(int);

  char *actor;
  short action;
  action_notify_fn_t handler;

  actor = (char *)datum_get(actor_data, actor_handle);
  action = *(short *)(actor + 0x6c);

  assert_halt(action >= 0 && action < 14);

  handler = *(action_notify_fn_t *)(0x253fc0 + action * 0x38);
  if (handler != NULL) {
    handler(actor_handle);
  }
}

/* actor_action_replace_prop (0x1c450)
 * Dispatch action-specific prop replacement for an actor.
 *
 * Looks up the actor via actor_data, validates the action index is in range,
 * then dispatches to the action's prop_replace handler (if any) through
 * the action_definitions table at 0x253fcc (stride 0x38, function pointer
 * at offset 0 of each entry).
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x1c45f.
 * Confirmed: actor+0x6c is short action index.
 * Confirmed: assert at line 0xbe (190) checks 0 <= action < 14.
 * Confirmed: table at 0x253fcc, stride 0x38, first field is function pointer.
 * Confirmed: indirect call passes (actor_handle, old_prop, new_prop).
 * Confirmed: __FILE__ = "c:\halo\SOURCE\ai\actions.c". */
void actor_action_replace_prop(int actor_handle, int old_prop, int new_prop)
{
  typedef void (*action_prop_replace_fn_t)(int, int, int);

  char *actor;
  short action;
  action_prop_replace_fn_t handler;

  actor = (char *)datum_get(actor_data, actor_handle);
  action = *(short *)(actor + 0x6c);

  assert_halt(action >= 0 && action < 14);

  handler = *(action_prop_replace_fn_t *)(0x253fcc + action * 0x38);
  if (handler != NULL) {
    handler(actor_handle, old_prop, new_prop);
  }
}

/* actor_action_flush_position_indices (0x1c4c0)
 *
 * Dispatches the current action's handler at table slot +0x30 (0x253fd0,
 * stride 0x38) for the given actor. The semantic role of this slot is not
 * directly evidenced by the binary; it is the field immediately after the
 * prop_replace handler (+0x2c) in each action_definitions entry.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x1c4cf.
 * Confirmed: actor+0x6c = action index (short), asserted in [0, 14) at
 *   line 0xcd (205).
 * Confirmed: IMUL ECX,ECX,0x38; MOV EAX,[ECX+0x253fd0] at 0x1c50f.
 * Confirmed: handler called with (actor_handle); TEST EAX,EAX guards call.
 * Confirmed: __FILE__ "c:\halo\SOURCE\ai\actions.c".
 */
void actor_action_flush_position_indices(int actor_handle)
{
  typedef void (*action_slot30_fn_t)(int);

  char *actor;
  short action;
  action_slot30_fn_t handler;

  actor = (char *)datum_get(actor_data, actor_handle);
  action = *(short *)(actor + 0x6c);

  assert_halt(action >= 0 && action < 14);

  handler = *(action_slot30_fn_t *)(0x253fd0 + action * 0x38);
  if (handler != NULL) {
    handler(actor_handle);
  }
}

/* actor_action_flush_structure_indices (0x1c530) —
 * actor_action_flush_structure_indices
 *
 * Dispatches the current action's handler at table slot +0x34 (0x253fd4,
 * stride 0x38) for the given actor. Semantically "flush structure indices" —
 * the table slot immediately after slot+0x30.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x1c53f.
 * Confirmed: actor+0x6c = action index (short), asserted in [0, 14) at
 *   line 0xdc (220).
 * Confirmed: IMUL EAX,EAX,0x38; MOV ECX,[EAX+0x253fd4] at 0x1c573/0x1c57a.
 * Confirmed: handler called with (actor_handle); TEST ECX,ECX guards call.
 * Confirmed: __FILE__ "c:\halo\SOURCE\ai\actions.c".
 */
void actor_action_flush_structure_indices(int actor_handle)
{
  typedef void (*action_slot34_fn_t)(int);

  char *actor;
  short action;
  action_slot34_fn_t handler;

  actor = (char *)datum_get(actor_data, actor_handle);
  action = *(short *)(actor + 0x6c);

  assert_halt(action >= 0 && action < 14);

  handler = *(action_slot34_fn_t *)(0x253fd4 + action * 0x38);
  if (handler != NULL) {
    handler(actor_handle);
  }
}

/* actor_action_handle_panic_from_surprise (0x1c5a0)
 *
 * Checks if an actor should enter a surprise-panic state. Sets the panic
 * substate (actor+0x308) and prop index (actor+0x30c) when the actor's
 * surprise-panic flag (actor+0x2f0) is set AND the actr tag allows it
 * (flag 0x400). Clears the flag after handling.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x1c5af.
 * Confirmed: tag_get(0x61637472, actor+0x58) loads actr tag.
 * Confirmed: actor+0x2f0 = surprise-panic flag; actor+0x308 = panic substate
 *   (short), clamped min to 7; actor+0x30c = prop index; actor+0x2f4 = default
 *   prop index to use.
 * Confirmed: assert at line 0x210 checks panic state consistency.
 * Inferred: "surprise" type because flag at +0x2f0 and prop from +0x2f4.
 */
int actor_action_handle_panic_from_surprise(int actor_handle)
{
  char *actor;
  int *actr_tag;
  short panic_type;
  int result;

  actor = (char *)datum_get(actor_data, actor_handle);
  actr_tag = (int *)tag_get(0x61637472, *(int *)(actor + 0x58));
  result = 0;
  if ((*(char *)(actor + 0x2f0) != '\0') &&
      ((*(unsigned int *)actr_tag & 0x400) != 0)) {
    panic_type = *(short *)(actor + 0x308);
    if ((panic_type == 0) || (*(int *)(actor + 0x30c) == -1)) {
      *(int *)(actor + 0x30c) = *(int *)(actor + 0x2f4);
    }
    if (panic_type < 8) {
      panic_type = 7;
    }
    *(short *)(actor + 0x308) = panic_type;
    *(char *)(actor + 0x2f0) = 0;
    result = 1;
  }
  assert_halt(*(short *)(actor + 0x308) == 0 || *(int *)(actor + 0x30c) != 0);
  return result;
}

/* actor_action_handle_panic_from_damage (0x1c660)
 *
 * Checks if an actor should enter a damage-panic state. Sets panic substate
 * (actor+0x308, clamped to min 1) and prop index (actor+0x30c) when the
 * damage-panic flag (actor+0x2ec) is set, the actor is in a networked or
 * client context, and the actor's current damage pain boost exceeds the tag
 * threshold. Clears flag after handling.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x1c66f.
 * Confirmed: tag_get(0x61637472, actor+0x58) loads actr tag.
 * Confirmed: actor+0x2ec = damage-panic flag; actor+0x308 = panic substate
 *   (short); actor+0x30c = prop index; actor+0x1c0 = pain boost (float);
 *   actr_tag+0x2ac = pain threshold (float).
 * Confirmed: game_connection() != 0 or !DAT_005ac9c8 enables the check.
 * Confirmed: actor_get_best_damaging_prop(actor_handle, 1) = get best target
 * prop. Confirmed: assert at line 0x228 checks panic state consistency.
 */
char actor_action_handle_panic_from_damage(int actor_handle)
{
  char *actor;
  int actr_tag;
  short panic_type;
  int result;

  actor = (char *)datum_get(actor_data, actor_handle);
  actr_tag = (int)tag_get(0x61637472, *(int *)(actor + 0x58));
  result = 0;
  if (*(char *)(actor + 0x2ec) != '\0') {
    if ((game_connection() != 0) || (*(char *)0x5ac9c8 == '\0')) {
      if (*(float *)(actor + 0x1c0) <= *(float *)(actr_tag + 0x2ac))
        goto check_assert_damage;
    }
    panic_type = *(short *)(actor + 0x308);
    if ((panic_type == 0) || (*(int *)(actor + 0x30c) == -1)) {
      *(int *)(actor + 0x30c) = actor_get_best_damaging_prop(actor_handle, 1);
    }
    if (*(short *)(actor + 0x308) < 2) {
      *(short *)(actor + 0x308) = 1;
    }
    *(char *)(actor + 0x2ec) = 0;
    result = 1;
  }
check_assert_damage:
  assert_halt(*(short *)(actor + 0x308) == 0 || *(int *)(actor + 0x30c) != 0);
  return result;
}

/* actor_action_handle_panic_from_burning_to_death (0x1c750)
 *
 * Checks if an actor should panic because it is burning to death. Sets panic
 * substate (actor+0x308, clamped to min 0xc) and prop index (actor+0x30c)
 * when the burning-death flag (actor+0x1b5) is set. Looks up the responsible
 * unit's vehicle/turret mount as the prop source.
 *
 * Confirmed: datum_get(actor_data, actor_handle); actor+0x1b5 = on-fire flag.
 * Confirmed: actor+0x18 = unit handle; object_get_and_verify_type(..., 3).
 * Confirmed: ai_get_responsible_unit(unit+0x3c0, 1);
 * prop_get_active_by_unit_index. Confirmed: actor+0x308 substate clamped min
 * 0xc (12). Confirmed: actor+0x30c prop index set only if substate==0 or
 * current==-1.
 */
int actor_action_handle_panic_from_burning_to_death(int actor_handle)
{
  char *actor;
  int unit;
  int responsible;
  int prop_handle;
  short panic_type;
  int result;

  actor = (char *)datum_get(actor_data, actor_handle);
  result = 0;
  if (*(char *)(actor + 0x1b5) != '\0') {
    prop_handle = -1;
    if (*(int *)(actor + 0x18) != -1) {
      unit = (int)object_get_and_verify_type(*(int *)(actor + 0x18), 3);
      responsible = ai_get_responsible_unit(*(int *)(unit + 0x3c0), 1);
      if (responsible != -1) {
        prop_handle = prop_get_active_by_unit_index(actor_handle, responsible);
      }
    }
    panic_type = *(short *)(actor + 0x308);
    if ((panic_type == 0) || (*(int *)(actor + 0x30c) == -1)) {
      *(int *)(actor + 0x30c) = prop_handle;
    }
    if (panic_type < 0xd) {
      panic_type = 0xc;
    }
    *(short *)(actor + 0x308) = panic_type;
    result = 1;
  }
  return result;
}

/* actor_action_handle_panic_from_attached_projectiles (0x1c7f0)
 *
 * Checks if an actor should panic because it has projectiles attached to it.
 * Sets panic substate (actor+0x308, clamped to min 0xa) and prop index
 * (actor+0x30c) when the attached-projectile handle (actor+0x1b0) is valid.
 *
 * Confirmed: datum_get(actor_data, actor_handle); actor+0x1b0 = projectile
 * handle. Confirmed: object_try_and_get_and_verify_type(actor+0x1b0,
 * 0xffffffff). Confirmed: ai_get_responsible_unit(obj+0x74, 1). Confirmed:
 * prop_get_active_by_unit_index for prop lookup. Confirmed: actor+0x308
 * substate clamped min 0xa (10).
 */
int actor_action_handle_panic_from_attached_projectiles(int actor_handle)
{
  char *actor;
  int projectile;
  int responsible;
  int prop_handle;
  short panic_type;
  int result;

  actor = (char *)datum_get(actor_data, actor_handle);
  result = 0;
  if (*(int *)(actor + 0x1b0) != -1) {
    projectile = (int)object_try_and_get_and_verify_type(
      *(int *)(actor + 0x1b0), 0xffffffff);
    prop_handle = -1;
    if (projectile != 0) {
      responsible = ai_get_responsible_unit(*(int *)(projectile + 0x74), 1);
      if (responsible != -1) {
        prop_handle = prop_get_active_by_unit_index(actor_handle, responsible);
      }
    }
    panic_type = *(short *)(actor + 0x308);
    if ((panic_type == 0) || (*(int *)(actor + 0x30c) == -1)) {
      *(int *)(actor + 0x30c) = prop_handle;
    }
    if (panic_type < 0xb) {
      panic_type = 10;
    }
    *(short *)(actor + 0x308) = panic_type;
    result = 1;
  }
  return result;
}

/* actor_action_handle_panic_from_attached_melee_attackers (0x1c880)
 *
 * Checks if an actor should panic due to attached melee attackers. Sets panic
 * substate (actor+0x308, clamped to min 0xb) and clears prop index
 * (actor+0x30c) when the attached-melee flag (actor+0x1b4) is set.
 *
 * Confirmed: datum_get(actor_data, actor_handle); actor+0x1b4 = attached-melee
 * flag. Confirmed: actor+0x308 substate clamped min 0xb (not to 0xc —
 * max(current,0xb)). Confirmed: actor+0x30c set to 0xffffffff (-1 = NONE).
 * Confirmed: returns 1 if triggered, 0 otherwise.
 */
char actor_action_handle_panic_from_attached_melee_attackers(int actor_handle)
{
  char *actor;
  short panic_type;
  char result;

  actor = (char *)datum_get(actor_data, actor_handle);
  result = 0;
  if (*(char *)(actor + 0x1b4) != '\0') {
    panic_type = *(short *)(actor + 0x308);
    if ((int)panic_type < 0xc) {
      panic_type = 0xb;
    }
    *(short *)(actor + 0x308) = panic_type;
    *(int *)(actor + 0x30c) = -1;
    result = 1;
  }
  return result;
}

/* actor_action_handle_berserking_from_attacking_mode (0x1c8d0)
 *
 * Checks if an actor should enter berserk mode due to being in high-aggression
 * attacking mode. Sets berserk substate (actor+0x310, clamped to min 1) when
 * the actor's aggression (actor+0x6e) > 4, berserk-from-attack flag
 * (actor+0x1c9) is clear, and the actr tag allows berserk (flag 0x80000).
 *
 * Confirmed: datum_get(actor_data, actor_handle);
 * tag_get(0x61637472,actor+0x58). Confirmed: *actr_tag & 0x80000 =
 * allows_berserk flag. Confirmed: actor+0x1c9 = berserk-from-attack
 * already-triggered flag. Confirmed: actor+0x6e = aggression level (short),
 * must be > 4. Confirmed: actor+0x310 = berserk substate, clamped min 1.
 * Confirmed: returns 1 if triggered, 0 otherwise.
 */
char actor_action_handle_berserking_from_attacking_mode(int actor_handle)
{
  char *actor;
  int *actr_tag;
  short berserk_state;
  char result;

  actor = (char *)datum_get(actor_data, actor_handle);
  actr_tag = (int *)tag_get(0x61637472, *(int *)(actor + 0x58));
  result = 0;
  if (((*(unsigned int *)actr_tag & 0x80000) != 0) &&
      (*(char *)(actor + 0x1c9) == '\0') && (*(short *)(actor + 0x6e) >= 5)) {
    berserk_state = *(short *)(actor + 0x310);
    if (berserk_state < 2) {
      berserk_state = 1;
    }
    *(short *)(actor + 0x310) = berserk_state;
    result = 1;
  }
  return result;
}

/* actor_action_handle_berserking_from_proximity (0x1c940)
 *
 * Checks if an actor should enter berserk mode because its target is too
 * close (within the tag's proximity berserk threshold). Sets berserk substate
 * (actor+0x310, clamped to min 2) when aggression (actor+0x6e) > 4 and
 * target-to-actor distance < actr_tag berserk_proximity_distance threshold.
 *
 * Confirmed: datum_get(actor_data); datum_get(props_data?, actor+0x270).
 * Confirmed: actor+0x270 = target prop index; assert != NONE.
 * Confirmed: prop+0x11c = prop distance (float); actr_tag+0x3a0 = threshold
 * (float). Confirmed: actor+0x310 = berserk substate, clamped min 2. Confirmed:
 * actor+0x6e = aggression level (short), must be > 4. Confirmed: returns 1 if
 * triggered, 0 otherwise.
 */
char actor_action_handle_berserking_from_proximity(int actor_handle)
{
  char *actor;
  char *actr_tag;
  char *prop;
  int prop_handle;
  float dist;
  float threshold;
  short berserk_state;

  actor = (char *)datum_get(actor_data, actor_handle);
  actr_tag = (char *)tag_get(0x61637472, *(int *)(actor + 0x58));
  if (4 < *(short *)(actor + 0x6e)) {
    prop = (char *)datum_get(*(data_t **)0x5ab23c, *(int *)(actor + 0x270));
    prop_handle = *(int *)(actor + 0x270);
    assert_halt(prop_handle != -1);
    dist = *(float *)(prop + 0x11c);
    threshold = *(float *)(actr_tag + 0x3a0);
    if (dist < threshold) {
      berserk_state = *(short *)(actor + 0x310);
      if (berserk_state < 3) {
        berserk_state = 2;
      }
      *(short *)(actor + 0x310) = berserk_state;
      return 1;
    }
  }
  return 0;
}

/* actor_action_handle_berserking_from_damage (0x1ca00)
 * Returns 1 if actor triggers berserk from damage: actor+0x2ec flag set,
 * health (actor+0x1c0) > actr_tag+0x398, and speed (actor+0x1b8) <
 * actr_tag+0x39c. Clamps berserk_state (actor+0x310) to min 3, clears the 0x2ec
 * flag. */
char actor_action_handle_berserking_from_damage(int actor_handle)
{
  char *actor;
  int actr_tag;
  short berserk_state;
  char result;

  actor = (char *)datum_get(actor_data, actor_handle);
  actr_tag = (int)tag_get(0x61637472, *(int *)(actor + 0x58));
  result = 0;
  if (*(char *)(actor + 0x2ec) != '\0') {
    if (*(float *)(actor + 0x1c0) > *(float *)(actr_tag + 0x398)) {
      if (*(float *)(actor + 0x1b8) < *(float *)(actr_tag + 0x39c)) {
        berserk_state = *(short *)(actor + 0x310);
        if (berserk_state < 4) {
          berserk_state = 3;
        }
        *(short *)(actor + 0x310) = berserk_state;
        *(char *)(actor + 0x2ec) = 0;
        result = 1;
      }
    }
  }
  return result;
}

/* actor_action_deny_transition (0x1ca90)
 * Returns 1 if the actor must deny an action transition: pending command list,
 * squad timer active with low state, or berserking with specific flags clear.
 */
char actor_action_deny_transition(int actor_handle)
{
  char *actor;
  char *squad;
  char result;

  actor = (char *)datum_get(actor_data, actor_handle);
  result = 0;
  if ((*(short *)(actor + 0x90) != -1) && (0 < *(short *)(actor + 0x92))) {
    result = 1;
  }
  if (*(int *)(actor + 0x34) != -1) {
    squad = encounter_get_squad(
      datum_get(*(data_t **)0x5ab270, *(int *)(actor + 0x34)),
      *(short *)(actor + 0x3a));
    if (0 < *(short *)(squad + 0x12)) {
      if (*(short *)(actor + 0x6e) >= 5) {
        encounter_squad_timer_expire(*(int *)(actor + 0x34),
                                     *(short *)(actor + 0x3a));
      } else {
        result = 1;
      }
    }
  }
  if (*(short *)(actor + 0x6c) == 0xb) {
    if ((*(char *)(actor + 0x9e) == '\0') &&
        (*(char *)(actor + 0xa1) == '\0')) {
      return 1;
    }
  }
  return result;
}

/* FUN_0001cb30 (0x1cb30) — Per-record action cooldown / dedup gate.
 * Returns 0 (deny) only when record_index equals the record's stored id at
 * +0x390 AND the game clock has not yet reached the deadline at +0x394;
 * otherwise returns 1 (allow). The record is fetched via
 * datum_get(actor_data, datum_handle), where datum_handle arrives in EAX.
 * Confirmed: PUSH EAX (@eax) then PUSH actor_data before CALL datum_get at
 * 0x1cb3d; game_time_get() at 0x1cb52; fields +0x390 (int, equality via JNZ)
 * and +0x394 (int, game-time deadline via JGE). Return is a bool in AL. */
char FUN_0001cb30(int record_index, int datum_handle /* @<eax> */)
{
  char *record;

  record = (char *)datum_get(actor_data, datum_handle);
  if (record_index == *(int *)(record + 0x390)) {
    if (game_time_get() < *(int *)(record + 0x394)) {
      return 0;
    }
  }
  return 1;
}

/* actor_action_handle_vehicle_exit (0x1cb70)
 * Attempts to exit the actor's current vehicle seat. Returns 1 on success.
 * Iterates nearby props to check for berserking attackers; tries
 * unit_try_and_exit_seat on the actor's unit, storing the vehicle handle and a
 * cooldown timer on success. */
char actor_action_handle_vehicle_exit(int actor_handle)
{
  char *actor;
  char berserk_nearby;
  char local_5;
  char iter_buf[12];
  int prop;
  char exit_ok;
  int t;
  char result;

  actor = (char *)datum_get(actor_data, actor_handle);
  result = 0;
  if (*(int *)(actor + 0x158) == -1) {
    goto done_clear;
  }
  berserk_nearby = 0;
  local_5 = 0;
  FUN_00064540((int *)iter_buf, actor_handle);
  prop = FUN_00064570((int *)iter_buf);
  while (prop != 0) {
    if (((1 < *(short *)(prop + 0x24)) && (*(short *)(prop + 0x24) < 4)) &&
        (*(char *)(prop + 0x12e) != '\0') && (*(char *)(prop + 0x60) != '\0') &&
        (*(int *)(prop + 0x110) == *(int *)(actor + 0x158))) {
      berserk_nearby = 1;
      local_5 = 1;
      break;
    }
    prop = FUN_00064570((int *)iter_buf);
  }
  if (*(char *)(actor + 0x2ed) != '\0') {
    berserk_nearby = 1;
  }
  if ((*(char *)(actor + 0x160) == '\0') ||
      ((*(int *)(actor + 0x1b0) == -1) &&
       ((*(short *)(actor + 0x280) != 2 ||
         (*(char *)(actor + 0x28a) == '\0'))))) {
    if (!berserk_nearby) {
      goto done_clear;
    }
  } else {
    local_5 = 1;
  }
  *(char *)(actor + 0x38c) = local_5;
  exit_ok = unit_try_and_exit_seat(*(int *)(actor + 0x18));
  if (exit_ok != '\0') {
    *(int *)(actor + 0x390) = *(int *)(actor + 0x158);
    t = game_time_get();
    *(int *)(actor + 0x394) = t + 0xb4;
    *(char *)(actor + 0x38c) = 0;
    *(char *)(actor + 0x2ed) = 0;
    return 1;
  }
  *(char *)(actor + 0x38c) = 0;
  *(char *)(actor + 0x2ed) = 0;
  return result;
done_clear:
  *(char *)(actor + 0x2ed) = 0;
  return result;
}

/* actor_action_allow_cover_seeking (0x1ccc0) — XBE naked draft (batch 87). */
#if defined(__clang__)
static void *(*const b1ccc0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1ccc0_tag)(int, int) = tag_get;
static void (*const b1ccc0_ftol)(void) = FUN_001d9068;
static int (*const b1ccc0_gtime)(void) = game_time_get;

__attribute__((naked, noinline))
char actor_action_allow_cover_seeking(int actor_handle __attribute__((unused)), char param_2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x58(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movb $1, %%bl\n\t"
      "jne .Lactor_action_allow_cover_seeking_3\n\t"
      "movb 0x1ca(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_allow_cover_seeking_3\n\t"
      "flds 0x2d8(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_action_allow_cover_seeking_2\n\t"
      "cmpw $7, 0x6e(%%esi)\n\t"
      "jge .Lactor_action_allow_cover_seeking_1\n\t"
      "flds 0x2d8(%%edi)\n\t"
      "fmuls 0x253394\n\t"
      "call *%[ftol]\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "cmpl $-1, 0x26c(%%esi)\n\t"
      "je .Lactor_action_allow_cover_seeking_2\n\t"
      "call *%[gtime]\n\t"
      "movswl 0xc(%%ebp), %%ecx\n\t"
      "addl 0x26c(%%esi), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .Lactor_action_allow_cover_seeking_2\n\t"
      ".Lactor_action_allow_cover_seeking_1:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".Lactor_action_allow_cover_seeking_2:\n\t"
      "flds 0x324(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_action_allow_cover_seeking_3\n\t"
      "flds 0x1c0(%%esi)\n\t"
      "fcomps 0x324(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_action_allow_cover_seeking_3\n\t"
      "xorb %%bl, %%bl\n\t"
      ".Lactor_action_allow_cover_seeking_3:\n\t"
      "movb 0x378(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_allow_cover_seeking_4\n\t"
      "xorb %%bl, %%bl\n\t"
      ".Lactor_action_allow_cover_seeking_4:\n\t"
      "movb 0x160(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_allow_cover_seeking_5\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_allow_cover_seeking_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1ccc0_dget), [tag] "m"(b1ccc0_tag), [ftol] "m"(b1ccc0_ftol), [gtime] "m"(b1ccc0_gtime)
      : "memory");
}
#else
#error "actor_action_allow_cover_seeking: clang naked draft required"
#endif


/* actor_action_can_stop_guarding (0x1cf10)
 * Returns 1 if the actor can stop the guard action, based on state counters and
 * flags. Asserts that the actor's current action is _actor_action_guard (6). */
char actor_action_can_stop_guarding(int actor_handle, short min_state,
                                    short max_state)
{
  char *actor;

  actor = (char *)datum_get(actor_data, actor_handle);
  assert_halt(*(short *)(actor + 0x6c) == 6);
  if (*(char *)(actor + 0xa4) != '\0') {
    return max_state <= *(short *)(actor + 0x6e);
  }
  if (((0 < *(short *)(actor + 0x9c)) &&
       (*(short *)(actor + 0x6e) < min_state)) &&
      ((*(short *)(actor + 0x1e4) < 1 || (*(char *)(actor + 0xa1) != '\0')))) {
    return 0;
  }
  return 1;
}

/* actor_action_can_stop_conversing (0x1cfa0) — readable C lift. */
char actor_action_can_stop_conversing(int actor_handle, int flag)
{
  (void)flag;
  char *actor;
  int conv;
  char *rec;
  void *block;
  unsigned char flags;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  conv = *(int *)(actor + 0x1dc);
  if (conv == -1)
    return 1;
  rec = (char *)datum_get(*(data_t **)0x6324ec, conv);
  block = tag_block_get_element((char *)global_scenario_get() + 0x468,
                                (int)*(short *)(rec + 2), 0x74);
  flags = *(unsigned char *)((char *)block + 0x20);
  if ((flags & 2) && actor[0x1f6])
    return 1;
  if ((flags & 4) && *(short *)(actor + 0x268) >= 9)
    return 1;
  if ((flags & 8) && *(short *)(actor + 0x268) >= 6)
    return 1;
  return 0;
}
/* actor_action_change (0x1d030) — actor_set_action
 *
 * Transitions an actor to a new action type: calls the old action's exit
 * handler, adjusts the actor's priority level, copies action-specific state
 * data, sets the new action index, and calls the new action's begin handler.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x1d040.
 * Confirmed: INC word [0x5ac87c] (global action-change counter) at 0x1d04b.
 * Confirmed: assert new_action_type in [0,14) at line 0xb83.
 * Confirmed: assert table[new_action].action == new_action_type at line 0xb84.
 * Confirmed: assert actor+0x6c (old action) in [0,14) at line 0xb87.
 * Confirmed: exit handler at table+0x24 (0x253fc4) called with actor_handle.
 * Confirmed: priority adjust using table+0x10 (0x253fb0) short field.
 * Confirmed: actor_clear_discarded_firing_positions(actor_handle, 0) at
 * 0x1d122. Confirmed: csmemcpy(actor+0x9c, param_3, data_size) when data_size >
 * 0. Confirmed: actor+0x6c = (short)param_2, actor+0x70 = 1 at 0x1d153/0x1d157.
 * Confirmed: begin handler at table+0x14 (0x253fb4) called with actor_handle.
 */
void actor_action_change(int actor_handle, int new_action_type, int param_3)
{
  typedef void (*action_handler_fn_t)(int);

  char *actor;
  int table_offset;
  action_handler_fn_t handler;

  actor = (char *)datum_get(actor_data, actor_handle);

  (*(uint16_t *)0x5ac87c)++;

  assert_halt(new_action_type >= 0 && new_action_type < 14);

  table_offset = new_action_type * 0x38;

  assert_halt(*(int *)(0x253fa0 + table_offset) == new_action_type);

  assert_halt(*(short *)(actor + 0x6c) >= 0 && *(short *)(actor + 0x6c) < 14);

  handler =
    *(action_handler_fn_t *)(0x253fc4 + *(short *)(actor + 0x6c) * 0x38);
  if (handler != NULL) {
    handler(actor_handle);
  }

  if (*(short *)(0x253fb0 + table_offset) == 0) {
    if (*(short *)(actor + 0x6a) > 2) {
      *(short *)(actor + 0x6a) = 2;
    }
  } else {
    if (*(short *)(actor + 0x6a) < 3) {
      *(short *)(actor + 0x6a) = 3;
    }
  }

  actor_clear_discarded_firing_positions(actor_handle, 0);

  if (*(unsigned int *)(0x253fac + table_offset) != 0 && param_3 != 0) {
    csmemcpy(actor + 0x9c, (void *)param_3, *(int *)(0x253fac + table_offset));
  }

  *(short *)(actor + 0x6c) = (short)new_action_type;
  *(char *)(actor + 0x70) = 1;

  handler = *(action_handler_fn_t *)(0x253fb4 + (short)new_action_type * 0x38);
  if (handler != NULL) {
    handler(actor_handle);
  }
}

/* actor_action_try_to_seek_cover (0x1d350) — Attempt to make the actor seek
 * cover. Gets actor+0x270 as param_2 for FUN_00015040, then calls
 * actor_action_change with action 4 if successful. */
char actor_action_try_to_seek_cover(int actor_handle, char param_2,
                                    char param_3)
{
  char *actor;
  char cVar1;
  short local_88[66];

  actor = (char *)datum_get(actor_data, actor_handle);
  cVar1 = FUN_00015040(actor_handle, 0, *(int *)(actor + 0x270), 0, param_2,
                       param_3, local_88);
  if (cVar1 != '\0') {
    actor_action_change(actor_handle, 4, (int)local_88);
    return 1;
  }
  return 0;
}

/* FUN_0001d3c0 (0x1d3c0) — Attempt to make the actor seek cover with explicit
 * parameters. Calls FUN_00015040 with param_2/param_3/param_4 and no actor
 * lookup, then actor_action_change with action 4 if successful. */
char FUN_0001d3c0(int actor_handle, short param_2, int param_3, char param_4)
{
  char cVar1;
  short local_88[66];

  cVar1 = FUN_00015040(actor_handle, param_2, param_3, param_4, 0, 0, local_88);
  if (cVar1 != '\0') {
    actor_action_change(actor_handle, 4, (int)local_88);
    return 1;
  }
  return 0;
}

/* actor_action_try_to_enter_vehicle (0x1d420) — Attempt to make the actor
 * enter a vehicle. Iterates seat indices (from param_6 array, or discovered
 * via vehicle_scripting_find_available_seats if param_6 is NULL). For each
 * valid seat index, checks unit_has_animation_to_enter_seat then
 * FUN_0001b750, and on success calls actor_action_change with action type 9.
 * Marks the consumed seat as -1 in the seat array.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x1d437.
 * Confirmed: actor+0x18 used as unit_handle for seat check at 0x1d48a.
 * Confirmed: action type 9 at 0x1d4cf.
 * Confirmed: seat marked 0xffff at 0x1d4df. */
char actor_action_try_to_enter_vehicle(int actor_handle, int param_2,
                                       int param_3, int param_4,
                                       int16_t param_5, int16_t *param_6)
{
  char *actor;
  int16_t i;
  int16_t seat_index;
  int16_t local_seats[16];
  short action_buf[66];

  actor = (char *)datum_get(actor_data, actor_handle);
  if (param_6 == NULL) {
    param_6 = local_seats;
    param_5 = vehicle_scripting_find_available_seats(param_2, param_3, param_4,
                                                     local_seats, 0x10);
  }
  for (i = 0; i < param_5; i++) {
    seat_index = param_6[i];
    if (seat_index != -1 &&
        unit_has_animation_to_enter_seat(*(int *)(actor + 0x18), param_2,
                                         seat_index) != '\0' &&
        FUN_0001b750(actor_handle, param_2, seat_index, action_buf) != '\0') {
      actor_action_change(actor_handle, 9, (int)action_buf);
      param_6[i] = (int16_t)0xffff;
      return 1;
    }
  }
  return 0;
}

/* FUN_0001d530 (0x1d530) — Predicate: is the actor at a given absolute index
 * an eligible target of a differing category. Validates actor_handle (@<eax>)
 * via datum_get(actor_data, ...) with the result discarded (validation only),
 * resolves the actor record from actor_index, then gates on a bounded type
 * field (field_6e in [2,4)) and a mode field (field_6c). On a qualifying mode
 * it maps the actor's type word (field_4) through FUN_0003a7f0 and returns 1
 * when the mapped category differs from param_1; otherwise returns 0.
 *
 * Confirmed: datum_get(actor_data, actor_handle@<eax>) at 0x1d53c; two pushes
 *   for datum_get + two for datum_absolute_index_to_index cleaned by one
 *   ADD ESP,0x10. Return value discarded.
 * Confirmed: datum_absolute_index_to_index(actor_data, actor_index) at 0x1d54e;
 *   result used as the actor record base pointer.
 * Confirmed: field_6e bounded (1 < field_6e < 4), word.
 * Confirmed: field_6c mode set {7,5, 8 iff param_1==0, 6 iff field_a4==0 &&
 *   field_9c>0}, word (field_a4 byte, field_9c word).
 * Confirmed: FUN_0003a7f0(*(int16_t *)(actor + 4)) compared to param_1;
 *   MOV AL,1 / MOV BL,AL byte-only return -> char. */
char FUN_0001d530(int actor_handle, char param_1, int actor_index)
{
  char *actor;
  short mode;

  datum_get(actor_data, actor_handle);
  actor = (char *)datum_absolute_index_to_index(actor_data, actor_index);
  if (actor != NULL && 1 < *(short *)(actor + 0x6e) &&
      *(short *)(actor + 0x6e) < 4) {
    mode = *(short *)(actor + 0x6c);
    if (mode == 7 || mode == 5 || (param_1 == '\0' && mode == 8) ||
        (mode == 6 && *(char *)(actor + 0xa4) == '\0' &&
         0 < *(short *)(actor + 0x9c))) {
      if ((char)FUN_0003a7f0(*(int16_t *)(actor + 4)) != param_1) {
        return 1;
      }
    }
  }
  return 0;
}

/* actor_action_name (0x1d5c0) — action_type_get_name
 *
 * Returns the name string for a given action type index from the
 * action_definitions table. Returns "unknown" if out of range.
 *
 * Confirmed: range check [0, 14) at 0x1d5c7/0x1d5d1.
 * Confirmed: IMUL EAX,EAX,0x38 (stride 56) at 0x1d5da.
 * Confirmed: name ptr at [EAX + 0x253fa4] (table base+0x04).
 * Confirmed: default "unknown" string at 0x254608. */
const char *actor_action_name(int16_t action_type)
{
  const char *name = (const char *)0x254608;
  if (action_type >= 0 && action_type < 0xe) {
    name = *(const char **)(0x253fa4 + action_type * 0x38);
  }
  return name;
}

/* actor_mode_name (0x1d5f0) — Returns the name string for a given actor mode
 * index. Returns "unknown" if out of range [0, 4). Lookup table at 0x2c8510. */
const char *actor_mode_name(int16_t param_1)
{
  const char *name = (const char *)0x254608;
  if (param_1 >= 0 && param_1 < 4) {
    name = *(const char **)(0x2c8510 + param_1 * 4);
  }
  return name;
}

/* actor_action_debug_color (0x1d620) — Compute the debug-visualization color
 * for an actor's current action.
 *
 * Copies a default color (4 dwords) from the global default-color pointer at
 * 0x2ee6cc into the shared scratch color buffer at 0x6328e0. If the actor's
 * action index (actor+0x6c, signed short) is in range [0, 14), overrides the
 * color from the action_definitions entry's color field (0x253fa8, stride
 * 0x38); that field is a double-indirect pointer to the 4-dword color. Then,
 * if the entry's callback field (0x253fc8, stride 0x38) is non-null, invokes
 * it as (actor_handle, &scratch_color) so the action type may adjust the
 * color. Always returns a pointer to the scratch color buffer.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x1d62e (pool 0x6325a4);
 *   result is NOT asserted.
 * Confirmed: default color = *(uint32_t **)0x2ee6cc, 4 dwords (pointer deref,
 *   0x1d633: mov ecx,[0x2ee6cc]; mov [ecx+k]).
 * Confirmed: actor+0x6c signed int16 action index; range [0,14) via signed
 *   TEST/JL + CMP 0xe/JGE at 0x1d663 — silent skip (no assert), unlike the
 *   sibling dispatchers.
 * Confirmed: color field 0x253fa8+action*0x38 is DOUBLE-indirect
 *   (0x1d674 mov ecx,[edx+0x253fa8]; 0x1d67a mov edx,[ecx]; 0x1d67c mov
 * ecx,[edx]). Confirmed: callback field 0x253fc8+action*0x38 (action re-read
 * via movsx at 0x1d69f); cdecl (actor_handle, &color), caller ADD ESP,8.
 * Confirmed: returns &scratch (0x6328e0) unconditionally (0x1d6bb mov
 * eax,0x6328e0). Confirmed: __FILE__ "c:\halo\SOURCE\ai\actions.c". */
void *actor_action_debug_color(int actor_handle)
{
  typedef void (*action_debug_color_fn_t)(int, void *);

  char *actor;
  int16_t action;
  uint32_t *color;
  action_debug_color_fn_t callback;

  actor = (char *)datum_get(actor_data, actor_handle);

  color = *(uint32_t **)0x2ee6cc;
  *(uint32_t *)0x6328e0 = color[0];
  *(uint32_t *)0x6328e4 = color[1];
  *(uint32_t *)0x6328e8 = color[2];
  *(uint32_t *)0x6328ec = color[3];

  action = *(int16_t *)(actor + 0x6c);
  if (action >= 0 && action < 14) {
    color = *(uint32_t **)(*(int *)(0x253fa8 + action * 0x38));
    *(uint32_t *)0x6328e0 = color[0];
    *(uint32_t *)0x6328e4 = color[1];
    *(uint32_t *)0x6328e8 = color[2];
    *(uint32_t *)0x6328ec = color[3];

    callback = *(action_debug_color_fn_t *)(0x253fc8 +
                                            *(int16_t *)(actor + 0x6c) * 0x38);
    if (callback != NULL) {
      callback(actor_handle, (void *)0x6328e0);
    }
  }

  return (void *)0x6328e0;
}

/* actor_action_try_to_panic (0x1d6d0) — actor_get_action_priority_flag
 *
 * Returns the priority flag (short) for the actor's current action from the
 * action_definitions table. A non-zero value indicates the action raises the
 * actor's priority to the high-priority tier (>= 3); zero means normal (< 3).
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x1d6df.
 * Confirmed: actor+0x6c = action index (short), asserted in [0, 14).
 * Confirmed: IMUL EDX,EDX,0x38 at 0x1d71c; MOV AX,[EDX+0x253fb0] at 0x1d71f.
 * Confirmed: table field 0x253fb0 = priority_flag (short at +0x10 from entry
 *   base 0x253fa0, same field used in actor_set_action at 0x1d030+0x79).
 * Confirmed: assert line 0xe98, __FILE__ "c:\halo\SOURCE\ai\actions.c".
 */
int16_t actor_action_try_to_panic(int actor_handle)
{
  char *actor;
  int16_t action;

  actor = (char *)datum_get(actor_data, actor_handle);
  action = *(int16_t *)(actor + 0x6c);

  assert_halt(action >= 0 && action < 14);

  return *(int16_t *)(0x253fb0 + action * 0x38);
}

/* actor_action_get_default_state (0x1d730) — Map a starting location index to
 * an action category. Returns a short from a 12-entry lookup table at 0x254300,
 * or 0 if the index is out of range [0, 12).
 *
 * Confirmed: CMP CX,0xc bounds check, table at 0x254300 =
 * {0,2,2,3,4,5,6,7,8,9,9,8}.
 */
short actor_action_get_default_state(short param_1)
{
  if (param_1 < 0 || param_1 >= 12)
    return 0;
  return *(short *)(0x254300 + (int)param_1 * 2);
}

/* set_real_vector2d (0x1d760) — Store two float values into a 2D vector
 * output pointer. */
void set_real_vector2d(float *out, float x, float y)
{
  out[0] = x;
  out[1] = y;
}

/* set_real_vector3d (0x1d780) — Store three float values into a 3D vector
 * output pointer. */
void set_real_vector3d(float *out, float x, float y, float z)
{
  out[0] = x;
  out[1] = y;
  out[2] = z;
}

/* point_to_line_distance3d (0x1d7a0) — readable C lift. */
float point_to_line_distance3d(float *p1, float *p2, float *p3)
{
  return sqrtf(FUN_0010cd40(p1, p2, p3));
}

/* actor_action_set_default_state (0x1d7c0) — XBE naked draft (batch 109). */
#if defined(__clang__)
static void *(*const b1d7c0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const b1d7c0_gtime)(void) = game_time_get;
static void (*const b1d7c0_c1d030)(int actor_handle, int new_action_type, int param_3) = actor_action_change;
static int (*const b1d7c0_c15880)(int actor_handle, char *state_data) = FUN_00015880;
static char (*const b1d7c0_c12000)(int actor_handle, int param_2, int param_3, int state_data) = FUN_00012000;
static int (*const b1d7c0_c15900)(int actor_handle, short param_2, char *state_data) = FUN_00015900;
static int16_t (*const b1d7c0_c1d6d0)(int actor_handle) = actor_action_try_to_panic;
static char (*const b1d7c0_c1ef90)(int actor_handle) = actor_action_handle_lost_contact;
static char (*const b1d7c0_c15040)(int actor_handle, short param_2, int param_3, char param_4, char param_5, char param_6, short *param_7) = FUN_00015040;

__attribute__((naked, noinline))
char actor_action_set_default_state(int actor_handle __attribute__((unused)), short state __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x84, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[gtime]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpw $-1, %%cx\n\t"
      "jne .Lactor_action_set_default_state_1\n\t"
      "movl 0x64(%%esi), %%edx\n\t"
      "cmpl $-1, %%edx\n\t"
      "je .Lactor_action_set_default_state_1\n\t"
      "addl $0x2d, %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jge .Lactor_action_set_default_state_11\n\t"
      ".Lactor_action_set_default_state_1:\n\t"
      "cmpw $-1, %%cx\n\t"
      "movl %%eax, 0x64(%%esi)\n\t"
      "je .Lactor_action_set_default_state_2\n\t"
      "movl %%ecx, %%eax\n\t"
      "jmp .Lactor_action_set_default_state_4\n\t"
      ".Lactor_action_set_default_state_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x60(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lactor_action_set_default_state_3\n\t"
      "movw $0xffff, 0x60(%%esi)\n\t"
      "jmp .Lactor_action_set_default_state_4\n\t"
      ".Lactor_action_set_default_state_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x62(%%esi), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "sete %%cl\n\t"
      "decl %%ecx\n\t"
      "andl %%ecx, %%eax\n\t"
      ".Lactor_action_set_default_state_4:\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl $0xb, %%eax\n\t"
      "ja .Lactor_action_set_default_state_9\n\t"
      "jmp *.Lactor_action_set_default_state_jt(,%%eax,4)\n\t"
      ".Lactor_action_set_default_state_5:\n\t"
      "movl $1, %%eax\n\t"
      "cmpw %%ax, 0x6a(%%esi)\n\t"
      "je .Lactor_action_set_default_state_9\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "movw %%ax, 0x6a(%%esi)\n\t"
      "call *%[c1d030]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_set_default_state_6:\n\t"
      "cmpw $6, 0x6c(%%esi)\n\t"
      "jne .Lactor_action_set_default_state_7\n\t"
      "cmpw $1, 0xc0(%%esi)\n\t"
      "je .Lactor_action_set_default_state_9\n\t"
      ".Lactor_action_set_default_state_7:\n\t"
      "leal -0x84(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c15880]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_set_default_state_9\n\t"
      "leal -0x84(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $6\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d030]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_set_default_state_8:\n\t"
      "cmpw $6, 0x6c(%%esi)\n\t"
      "jne .Lactor_action_set_default_state_12\n\t"
      "cmpw $3, 0xc0(%%esi)\n\t"
      "je .Lactor_action_set_default_state_9\n\t"
      "movb $1, 0xaa(%%esi)\n\t"
      ".Lactor_action_set_default_state_9:\n\t"
      "cmpw $0, 0x6c(%%esi)\n\t"
      "jne .Lactor_action_set_default_state_11\n\t"
      "leal -0x84(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c12000]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_set_default_state_11\n\t"
      "leal -0x84(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      ".Lactor_action_set_default_state_10:\n\t"
      "pushl $2\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d030]\n\t"
      "addl $0xc, %%esp\n\t"
      "movb $1, %%bl\n\t"
      ".Lactor_action_set_default_state_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_set_default_state_12:\n\t"
      "leal -0x84(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c15900]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_set_default_state_9\n\t"
      "leal -0x84(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $6\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d030]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_set_default_state_13:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d6d0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $3, %%ax\n\t"
      "je .Lactor_action_set_default_state_9\n\t"
      "movl $2, %%eax\n\t"
      "pushl %%edi\n\t"
      "movw $3, 0x6a(%%esi)\n\t"
      "movw %%ax, 0x72(%%esi)\n\t"
      "movw %%ax, 0x6e(%%esi)\n\t"
      "call *%[c1ef90]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_set_default_state_9\n\t"
      "leal -0x84(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c15880]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_set_default_state_9\n\t"
      "leal -0x84(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $6\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d030]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_set_default_state_14:\n\t"
      "cmpw $4, 0x6c(%%esi)\n\t"
      "je .Lactor_action_set_default_state_9\n\t"
      "leal -0x84(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl $0xd\n\t"
      "pushl %%edi\n\t"
      "call *%[c15040]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_set_default_state_15\n\t"
      "leal -0x84(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $4\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d030]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_set_default_state_15:\n\t"
      "cmpw $6, 0x6c(%%esi)\n\t"
      "je .Lactor_action_set_default_state_9\n\t"
      "leal -0x84(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c15880]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_set_default_state_9\n\t"
      "leal -0x84(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $6\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d030]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_set_default_state_16:\n\t"
      "cmpw $2, 0x6c(%%esi)\n\t"
      "jne .Lactor_action_set_default_state_17\n\t"
      "movw 0x9c(%%esi), %%cx\n\t"
      "cmpw 0x2542e8(,%%eax,2), %%cx\n\t"
      "je .Lactor_action_set_default_state_9\n\t"
      ".Lactor_action_set_default_state_17:\n\t"
      "movswl 0x2542e8(,%%eax,2), %%eax\n\t"
      "leal -0x84(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c12000]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_set_default_state_9\n\t"
      "leal -0x84(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "jmp .Lactor_action_set_default_state_10\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lactor_action_set_default_state_jt:\n\t"
      ".long .Lactor_action_set_default_state_16\n\t"
      ".long .Lactor_action_set_default_state_5\n\t"
      ".long .Lactor_action_set_default_state_16\n\t"
      ".long .Lactor_action_set_default_state_16\n\t"
      ".long .Lactor_action_set_default_state_16\n\t"
      ".long .Lactor_action_set_default_state_16\n\t"
      ".long .Lactor_action_set_default_state_16\n\t"
      ".long .Lactor_action_set_default_state_16\n\t"
      ".long .Lactor_action_set_default_state_6\n\t"
      ".long .Lactor_action_set_default_state_8\n\t"
      ".long .Lactor_action_set_default_state_13\n\t"
      ".long .Lactor_action_set_default_state_14\n\t"
      ".text\n\t"
      :
      : [dget] "m"(b1d7c0_dget), [gtime] "m"(b1d7c0_gtime), [c1d030] "m"(b1d7c0_c1d030), [c15880] "m"(b1d7c0_c15880), [c12000] "m"(b1d7c0_c12000), [c15900] "m"(b1d7c0_c15900), [c1d6d0] "m"(b1d7c0_c1d6d0), [c1ef90] "m"(b1d7c0_c1ef90), [c15040] "m"(b1d7c0_c15040)
      : "memory");
}
#else
#error "actor_action_set_default_state: clang naked draft required"
#endif


/* actor_action_handle_initial_action (0x1dab0)
 * If the actor is in the idle action (0x6c == 0) and has a non-zero
 * default-state index (0x6a), runs actor_action_set_default_state to
 * initiate that default state. Returns 1 if the state was set, 0 otherwise.
 *
 * Confirmed: datum_get(actor_data, actor_handle); actor+0x6c = short action;
 * actor+0x6a = short default_state_index. */
char actor_action_handle_initial_action(int actor_handle)
{
  char *actor;
  char result;

  actor = (char *)datum_get(actor_data, actor_handle);
  result = 0;
  if ((*(short *)(actor + 0x6c) == 0) && (*(short *)(actor + 0x6a) != 0)) {
    result = actor_action_set_default_state(actor_handle, 0xffff);
  }
  return result;
}

/* actor_action_handle_pending_command_list (0x1daf0)
 * Handles any pending command-list action stored in actor+0x90.
 * Returns 0 if no pending command, if guarding with no default state, or
 * if the current transition is denied. Otherwise starts the command-list
 * action (type 0xb), clears the pending entry, and returns 1.
 *
 * Confirmed: datum_get(actor_data, actor_handle); actor+0x90 = short
 * pending_action; actor+0x8e = char flag; actor+0x6a = short state.
 * actor_action_deny_transition at 0x1ca90; FUN_00016e70 at 0x16e70;
 * actor_action_change(actor_handle, 0xb, buf); actor+0x8e cleared. */
char actor_action_handle_pending_command_list(int actor_handle)
{
  char *actor;
  char cVar1;
  char result;
  char action_buf[132];

  actor = (char *)datum_get(actor_data, actor_handle);
  result = 0;
  if (*(short *)(actor + 0x90) == -1) {
    return 0;
  }
  if (*(char *)(actor + 0x8e) != '\0') {
    goto do_action;
  }
  if (*(short *)(actor + 0x6a) == 0) {
    return 0;
  }
  cVar1 = actor_action_deny_transition(actor_handle);
  if (cVar1 != '\0') {
    return 0;
  }
do_action:
  cVar1 = FUN_00016e70(actor_handle, *(short *)(actor + 0x90), action_buf);
  if (cVar1 != '\0') {
    actor_action_change(actor_handle, 0xb, (int)action_buf);
    result = 1;
  }
  *(char *)(actor + 0x8e) = 0;
  *(short *)(actor + 0x90) = -1;
  return result;
}

/* actor_action_handle_surprise (0x1db90) — Process an actor's surprise
 * reaction. If the actor is not dead (field_160 == 0) and the surprise level
 * (field_2ee) is at least as large as the requested type, computes a flee
 * direction, triggers a surprise animation impulse (type 4 = forward, type 5 =
 * backward), fires a sound event (0x29), and optionally queues wild fire and a
 * new combat target. Always clears the surprise level (field_2ee = 0) before
 * returning. */
char actor_action_handle_surprise(int actor_handle, short type)
{
  char *actor;
  char *actv_tag;
  char *prop;
  float direction[2];
  float dot;
  int anim_type;
  int weapon_trigger_index;
  int weapon_state;
  int prop_handle;

  actor = (char *)datum_get(actor_data, actor_handle);
  actv_tag = (char *)tag_get(0x61637476, *(int *)(actor + 0x5c));

  if (*(char *)(actor + 0x160) != '\0') {
    *(short *)(actor + 0x2ee) = 0;
    return 0;
  }
  if (*(short *)(actor + 0x2ee) < type) {
    *(short *)(actor + 0x2ee) = 0;
    return 0;
  }

  if (*(char *)(actor + 0x2f8) != '\0') {
    direction[0] = *(float *)(actor + 0x2fc);
    direction[1] = *(float *)(actor + 0x300);
    magnitude3d(direction);
    dot = direction[1] * *(float *)(actor + 0x5a8) +
          direction[0] * *(float *)(actor + 0x5a4);
    if (dot < 0.0f) {
      direction[0] = -direction[0];
      direction[1] = -direction[1];
      anim_type = 5;
    } else {
      anim_type = 4;
    }
  } else {
    direction[0] = *(float *)(actor + 0x174);
    direction[1] = *(float *)(actor + 0x178);
    magnitude3d(direction);
    anim_type = 4;
  }

  actor_move_animation_impulse(actor_handle, (short)anim_type,
                               (int *)direction);

  prop_handle = *(int *)(actor + 0x2f4);
  weapon_trigger_index = -1;
  weapon_state = 0;
  if (prop_handle != -1) {
    prop = (char *)datum_get(prop_data, prop_handle);
    weapon_trigger_index = *(int *)(prop + 0x18);
    weapon_state = (*(char *)(prop + 0x60) != '\0') + 2;
  }

  FUN_00046f10(0x29, *(int *)(actor + 0x18), weapon_trigger_index, weapon_state,
               -1, -1, 0);

  if (*(float *)(actv_tag + 0x90) > 0.0f) {
    FUN_00021010(actor_handle, (int)(*(float *)(actv_tag + 0x90) * 30.0f));
  }

  if (*(float *)(actv_tag + 0x8c) > 0.0f) {
    FUN_00021040(actor_handle, (int)(*(float *)(actv_tag + 0x8c) * 30.0f));
  }

  FUN_00036da0(actor_handle);

  prop_handle = *(int *)(actor + 0x2f4);
  if (prop_handle != -1) {
    actor_situation_try_new_target(actor_handle, prop_handle);
  }

  *(short *)(actor + 0x2ee) = 0;
  return 1;
}

/* actor_action_handle_panic_transition (0x1dd40) — XBE naked draft (batch 126). */
#if defined(__clang__)
static void *(*const b1dd40_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const b1dd40_gtime)(void) = game_time_get;
static void (*const b1dd40_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1dd40_exitfn)(int) = system_exit;
static void (*const b1dd40_c46f10)(int16_t type, int unit_handle, int param3, int param4, int16_t param5, int16_t param6, int16_t param7) = FUN_00046f10;
static char (*const b1dd40_c1d3c0)(int actor_handle, short param_2, int param_3, char param_4) = FUN_0001d3c0;

__attribute__((naked, noinline))
char actor_action_handle_panic_transition(int actor_handle __attribute__((unused)), short param_2 __attribute__((unused)), char param_3 __attribute__((unused)), short param_4 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movw 0x308(%%esi), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw 0xc(%%ebp), %%ax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jl .Lactor_action_handle_panic_transition_6\n\t"
      "movb 0x160(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lactor_action_handle_panic_transition_6\n\t"
      "cmpw $4, 0x6c(%%esi)\n\t"
      "jne .Lactor_action_handle_panic_transition_2\n\t"
      "movw 0xa8(%%esi), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jle .Lactor_action_handle_panic_transition_2\n\t"
      "cmpw %%ax, %%cx\n\t"
      "jle .Lactor_action_handle_panic_transition_1\n\t"
      "movswl %%cx, %%eax\n\t"
      "movw %%ax, 0xa8(%%esi)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "movw $0, 0x308(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_handle_panic_transition_1:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movw %%ax, 0xa8(%%esi)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "movw $0, 0x308(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_handle_panic_transition_2:\n\t"
      "cmpl $-1, 0x398(%%esi)\n\t"
      "je .Lactor_action_handle_panic_transition_3\n\t"
      "call *%[gtime]\n\t"
      "movl 0x398(%%esi), %%ecx\n\t"
      "addl $7, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jge .Lactor_action_handle_panic_transition_6\n\t"
      ".Lactor_action_handle_panic_transition_3:\n\t"
      "movw 0x308(%%esi), %%dx\n\t"
      "cmpw 0x14(%%ebp), %%dx\n\t"
      "movl 0x30c(%%esi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "setge %%bl\n\t"
      "testl %%eax, %%eax\n\t"
      "movb %%bl, 0xc(%%ebp)\n\t"
      "jne .Lactor_action_handle_panic_transition_4\n\t"
      "pushl $1\n\t"
      "pushl $0x295\n\t"
      "pushl $0x2544b0\n\t"
      "pushl $0x254610\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_action_handle_panic_transition_4:\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_panic_transition_5\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lactor_action_handle_panic_transition_5\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "pushl $0x22\n\t"
      "call *%[c46f10]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0x1c, %%esp\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "movw $0, 0x308(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_handle_panic_transition_5:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x30c(%%esi), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x308(%%esi), %%ax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d3c0]\n\t"
      "addl $0x10, %%esp\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "popl %%ebx\n\t"
      ".Lactor_action_handle_panic_transition_6:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "movw $0, 0x308(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1dd40_dget), [gtime] "m"(b1dd40_gtime), [assert] "m"(b1dd40_assert), [exitfn] "m"(b1dd40_exitfn), [c46f10] "m"(b1dd40_c46f10), [c1d3c0] "m"(b1dd40_c1d3c0)
      : "memory");
}
#else
#error "actor_action_handle_panic_transition: clang naked draft required"
#endif


/* actor_action_handle_combat_targeting (0x1dea0)
 * If the actor has a valid target (actor+0x1b0 != NONE) and its current action
 * index (actor+0x6e) is greater than 4, checks whether the target prop's field
 * at +0x11c is below the firing-variant definition's field at +0x16c. If so,
 * rolls a random real against the 'actr' tag probability at +0x3a8 and, on
 * success, clamps the retry field at actor+0x310 to a minimum of 4 and returns
 * 1. Returns 0 otherwise. Return value is discarded by both callers.
 * Confirmed: datum_get(actor_data, actor_handle); tag_get(0x61637472,
 * actor+0x58); actor_combat_get_firing_variant_definition(actor_handle);
 * datum_get(prop_data, actor+0x270). Assert path display_assert +
 * system_exit(-1) at 0x1de08, line 0x2c8, __FILE__
 * "c:\halo\SOURCE\ai\actions.c". */
char actor_action_handle_combat_targeting(int actor_handle)
{
  char *actor;
  int actr_tag;
  char *firing_variant;
  char *prop;
  int retry;

  actor = (char *)datum_get(actor_data, actor_handle);
  actr_tag = (int)tag_get(0x61637472, *(int *)(actor + 0x58));
  firing_variant = actor_combat_get_firing_variant_definition(actor_handle);
  if ((*(unsigned int *)(actor + 0x1b0) != 0xffffffff) &&
      (4 < *(short *)(actor + 0x6e))) {
    prop = (char *)datum_get(prop_data, *(int *)(actor + 0x270));
    if (*(int *)(actor + 0x270) == -1) {
      display_assert("actor->target.target_prop_index != NONE",
                     "c:\\halo\\SOURCE\\ai\\actions.c", 0x2c8, 1);
      system_exit(-1);
    }
    if (*(float *)(prop + 0x11c) < *(float *)(firing_variant + 0x16c)) {
      if (random_math_real((unsigned int *)get_global_random_seed_address()) <
          *(float *)(actr_tag + 0x3a8)) {
        retry = *(short *)(actor + 0x310);
        if (*(short *)(actor + 0x310) < 5) {
          retry = 4;
        }
        *(short *)(actor + 0x310) = (short)retry;
        return 1;
      }
    }
  }
  return 0;
}

/* actor_action_handle_active_cover_seeking (0x1e700) — When the actor's
 * active-cover gate flag (actor+0x4c) is set, evaluate whether the actor should
 * panic and seek cover. If the actor's stress field (actor+0x1bc) is at or
 * below the 'actr' tag threshold (tag+0x2dc), call actor_action_try_to_panic;
 * for a panic result of 3 or 4 with the suppress flag (actor+0x378) clear and
 * the action counter (actor+0x6e) greater than 1, throttle on a 0x1e-tick
 * cooldown (actor+0x370). On a fresh cooldown, gate on
 * actor_action_allow_cover_seeking then try actor_action_try_to_seek_cover;
 * failing that (and only when param2 is set) try FUN_0001d3c0 with the actor's
 * cover target (actor+0x270). Returns 1 if a cover-seek action was started, 0
 * otherwise.
 *
 * The per-actor state-trace record (base *(int*)0x331f58 +
 * (handle&0xffff)*0x657c) fields +0xb8/+0xba/+0xbc/+0xc0 are debug telemetry
 * only; they do not affect control flow. Confirmed: datum_get(actor_data,
 * actor_handle); tag_get(0x61637472, actor+0x58); game_time_get();
 * actor_action_try_to_panic(actor_handle);
 * actor_action_allow_cover_seeking(actor_handle, 0);
 * actor_action_try_to_seek_cover(actor_handle, 1, 0);
 * FUN_0001d3c0(actor_handle, 4, actor+0x270, param3). FPU: FLD actor+0x1bc;
 * FCOMP tag+0x2dc; TEST AH,0x41; JP => (actor+0x1bc <= tag+0x2dc). */
char actor_action_handle_active_cover_seeking(int actor_handle, char param2,
                                              int param3)
{
  char *actor;
  char *trace;
  int actr_tag;
  int elapsed;
  short panic;
  int now;
  char cVar1;
  char result;

  result = 0;
  actor = (char *)datum_get(actor_data, actor_handle);
  trace = (char *)((actor_handle & 0xffff) * 0x657c + *(int *)0x331f58);
  actr_tag = (int)tag_get(0x61637472, *(int *)(actor + 0x58));
  if (*(char *)(actor + 0x4c) != '\0') {
    *(char *)(trace + 0xb8) = 1;
    *(int16_t *)(trace + 0xba) = 4;
    if (*(int *)(actor + 0x26c) == -1) {
      elapsed = 1000;
    } else {
      elapsed = game_time_get() - *(int *)(actor + 0x26c);
    }
    *(int16_t *)(trace + 0xbc) = (int16_t)elapsed;
    *(int *)(trace + 0xc0) = *(int *)(actor + 0x1bc);
    if (*(float *)(actor + 0x1bc) <= *(float *)(actr_tag + 0x2dc)) {
      panic = actor_action_try_to_panic(actor_handle);
      *(int16_t *)(trace + 0xba) = 0;
      if (*(char *)(actor + 0x378) == '\0' && (panic == 4 || panic == 3)) {
        *(int16_t *)(trace + 0xba) = 1;
        if (*(short *)(actor + 0x6e) >= 2) {
          now = game_time_get();
          *(int16_t *)(trace + 0xba) = 2;
          if (*(int *)(actor + 0x370) == -1 ||
              *(int *)(actor + 0x370) + 0x1e <= now) {
            *(int16_t *)(trace + 0xba) = 3;
            *(int *)(actor + 0x370) = now;
            cVar1 = actor_action_allow_cover_seeking(actor_handle, 0);
            if (cVar1 != '\0') {
              *(int16_t *)(trace + 0xba) = 5;
              cVar1 = actor_action_try_to_seek_cover(actor_handle, 1, 0);
              if (cVar1 != '\0') {
                *(int16_t *)(trace + 0xba) = 6;
                return 1;
              }
              if (param2 != '\0') {
                cVar1 = FUN_0001d3c0(actor_handle, 4, *(int *)(actor + 0x270),
                                     param3);
                if (cVar1 != '\0') {
                  *(int16_t *)(trace + 0xba) = 7;
                  result = 1;
                }
              }
            }
          }
        }
      }
    }
  }
  return result;
}

/* actor_action_handle_done_fleeing (0x1f6e0) — readable C lift. */
char actor_action_handle_done_fleeing(int actor_handle)
{
  char *actor;
  char buf[0x84];

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  if (*(short *)(actor + 0x6c) != 4) {
    return 0;
  }
  if (actor[0xab] == 0) {
    return 0;
  }
  if (!FUN_00016210(actor_handle, (int)(actor + 0x9c), (short *)buf)) {
    display_assert((const char *)0x254818, (const char *)0x2544b0, 0xa79, 1);
    system_exit(-1);
  }
  actor_action_change(actor_handle, 6, (int)buf);
  return 1;
}

/* actor_action_handle_combat_failure (0x1f920) — readable C lift. */
char actor_action_handle_combat_failure(int actor_handle)
{
  char *actor;
  short mode;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  if (*(short *)(actor + 0x6c) != 0xa) {
    return 0;
  }
  mode = *(short *)(actor + 0xa0);
  if (mode == 2 || mode == 3) {
    if (actor[0xa3] != 0 || actor[0xa4] != 0 || actor[0xc5] != 0) {
      actor_action_handle_combat_selection(actor_handle);
    }
    return 0;
  }
  if (mode == 4 || mode == 5) {
    if (actor[0xc5] != 0) {
      actor_action_handle_combat_selection(actor_handle);
    }
  }
  return 0;
}

/* actor_action_handle_exit_pursuit (0x1f9a0) — Handles exit from pursuit-type
 * actions (guard=5, vehicle_patrol=7, vehicle=8). For guard actions, checks
 * offset 0x9d; for vehicle actions, checks 0x9c. If the flag is set and
 * the timer at 0xa4 is zero, calls the appropriate perception notification
 * (tried_to_uncover, tried_to_search, or abandoned_search) with the actor's
 * prop handle (0x270). Then delegates to actor_action_handle_lost_contact
 * to handle the actual transition. Returns 0 if no transition occurred. */
char actor_action_handle_exit_pursuit(int actor_handle)
{
  char *actor;
  short action_type;

  actor = (char *)datum_get(actor_data, actor_handle);
  action_type = *(short *)(actor + 0x6c);

  switch (action_type) {
  case 5:
    if (*(char *)(actor + 0x9d) == '\0')
      return 0;
    if (*(short *)(actor + 0xa4) == 0)
      actor_perception_tried_to_uncover(actor_handle, *(int *)(actor + 0x270));
    return actor_action_handle_lost_contact(actor_handle);
  case 7:
    if (*(char *)(actor + 0x9c) == '\0')
      return 0;
    if (*(short *)(actor + 0xa4) == 0) {
      actor_perception_tried_to_search(actor_handle, *(int *)(actor + 0x270));
      return actor_action_handle_lost_contact(actor_handle);
    }
    return actor_action_handle_lost_contact(actor_handle);
  case 8:
    if (*(char *)(actor + 0x9c) == '\0')
      return 0;
    actor_perception_abandoned_search(actor_handle, *(int *)(actor + 0x270));
    return actor_action_handle_lost_contact(actor_handle);
  default:
    return 0;
  }
}

/* actor_action_try_to_throw_grenade (0x1fa60) — XBE naked draft (batch 85). */
#if defined(__clang__)
static void *(*const b1fa60_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1fa60_get)(int, int) = object_get_and_verify_type;
static bool (*const b1fa60_c1a9ad0)(int unit_handle) = unit_is_busy;
static char (*const b1fa60_c1d180)(int actor_handle) = actor_action_test_grenade;
static float (*const b1fa60_mag)(float *) = magnitude3d;
static int (*const b1fa60_gtime)(void) = game_time_get;

__attribute__((naked, noinline))
char actor_action_try_to_throw_grenade(int actor_handle __attribute__((unused)), char flag __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c1a9ad0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_try_to_throw_grenade_3\n\t"
      "flds 0x9c(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_action_try_to_throw_grenade_3\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_try_to_throw_grenade_1\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d180]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_try_to_throw_grenade_1\n\t"
      "movb %%al, 0x6a0(%%esi)\n\t"
      ".Lactor_action_try_to_throw_grenade_1:\n\t"
      "movb 0x6a0(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_try_to_throw_grenade_3\n\t"
      "flds 0x6a8(%%esi)\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "fsubs 0x12c(%%esi)\n\t"
      "pushl %%edx\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x6ac(%%esi)\n\t"
      "fsubs 0x130(%%esi)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_action_try_to_throw_grenade_3\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x178(%%esi)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x174(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x2533dc\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lactor_action_try_to_throw_grenade_3\n\t"
      "movb $1, 0x45c(%%esi)\n\t"
      "movb $0, 0x6a0(%%esi)\n\t"
      "movl 0x34(%%esi), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lactor_action_try_to_throw_grenade_2\n\t"
      "movl 0x5ab270, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, 0x5c(%%esi)\n\t"
      ".Lactor_action_try_to_throw_grenade_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_try_to_throw_grenade_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1fa60_dget), [get] "m"(b1fa60_get), [c1a9ad0] "m"(b1fa60_c1a9ad0), [c1d180] "m"(b1fa60_c1d180), [mag] "m"(b1fa60_mag), [gtime] "m"(b1fa60_gtime)
      : "memory");
}
#else
#error "actor_action_try_to_throw_grenade: clang naked draft required"
#endif


/* actors_searching_same_position (0x20140) — Returns true when two actors are
 * searching/investigating the same position. Each actor's search record is the
 * sub-struct at actor+0xa4, but only consulted when the actor's search-type tag
 * at actor+0x6c is 5 or 7 (otherwise its record pointer stays NULL and the
 * function returns false). The record's first word (offset 0) is a "position
 * kind":
 *   kind 0 (world position): resolve each actor's referenced object
 *     (actor+0x270 is an absolute index into object pool 0x5ab23c) and compare
 *     the squared distance between the two object positions (object+0xbc)
 *     against the threshold at 0x253dd0 (~0.49 = 0.7^2); same only if closer.
 *   kind 1 (index/waypoint): equal only if the index word at record+2
 *     (actor+0xa6) matches.
 *   kind 2: always treated as the same position.
 * Mismatched kinds return false. */
bool actors_searching_same_position(int actor_handle, int param_2)
{
  int rec1;
  int rec2;
  int rec;
  short *search1;
  short *search2;
  short kind1;
  bool result;

  rec1 = (int)datum_get(actor_data, actor_handle);
  rec2 = (int)datum_get(actor_data, param_2);

  rec = (int)datum_get(actor_data, actor_handle);
  search1 = NULL;
  if (*(short *)(rec + 0x6c) == 7 || *(short *)(rec + 0x6c) == 5) {
    search1 = (short *)(rec + 0xa4);
  }

  rec = (int)datum_get(actor_data, param_2);
  search2 = NULL;
  if (*(short *)(rec + 0x6c) == 7 || *(short *)(rec + 0x6c) == 5) {
    search2 = (short *)(rec + 0xa4);
  }

  result = 0;
  if (search1 != NULL && search2 != NULL) {
    kind1 = *search1;
    if (kind1 == 0 && *search2 == 0) {
      rec1 = datum_absolute_index_to_index(*(data_t **)0x5ab23c,
                                           *(int *)(rec1 + 0x270));
      rec2 = datum_absolute_index_to_index(*(data_t **)0x5ab23c,
                                           *(int *)(rec2 + 0x270));
      if (rec1 == 0) {
        return 0;
      }
      if (rec2 == 0) {
        return 0;
      }
      if (*(float *)0x253dd0 <=
          distance_squared3d((float *)(rec1 + 0xbc), (float *)(rec2 + 0xbc))) {
        return 0;
      }
    } else {
      if (kind1 == 1 && *search2 == 1) {
        return search1[1] == search2[1];
      }
      if (kind1 != 2) {
        return 0;
      }
      if (*search2 != 2) {
        return 0;
      }
    }
    result = 1;
  }
  return result;
}

/* actor_pursuit_find_nearby_actors (0x20280) — XBE naked draft (batch 82). */
#if defined(__clang__)
static void *(*const b20280_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b20280_c64540)(int *out, int actor_handle) = FUN_00064540;
static int (*const b20280_c64570)(int *iter) = FUN_00064570;
static char (*const b20280_c1d530)(int actor_handle, char param_1, int actor_index) = FUN_0001d530;
static void (*const b20280_c59a00)(int *iter, int clump_handle) = encounter_actor_iterator_new;
static int (*const b20280_c59a50)(int *iter) = encounter_actor_iterator_next;
static int (*const b20280_c64ab0)(int actor_handle, int object_handle) = prop_get_active_by_unit_index;
static int (*const b20280_c64b40)(int actor_handle, int unit_handle, char create_if_needed, char refresh_flag) = FUN_00064b40;

__attribute__((naked, noinline))
int actor_pursuit_find_nearby_actors(int actor_handle __attribute__((unused)), char flag __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movb 0xc(%%ebp), %%cl\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testb %%cl, %%cl\n\t"
      "setne %%bl\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "movl $0xffffffff, -0xc(%%ebp)\n\t"
      "incl %%ebx\n\t"
      "movl $0x7f7fffff, -0x8(%%ebp)\n\t"
      "call *%[c64540]\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c64570]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lactor_pursuit_find_nearby_actors_4\n\t"
      ".Lactor_pursuit_find_nearby_actors_1:\n\t"
      "movb 0x60(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_pursuit_find_nearby_actors_3\n\t"
      "movb 0x127(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_pursuit_find_nearby_actors_3\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lactor_pursuit_find_nearby_actors_3\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "testb %%dl, %%dl\n\t"
      "je .Lactor_pursuit_find_nearby_actors_2\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .Lactor_pursuit_find_nearby_actors_3\n\t"
      "cmpw $3, %%ax\n\t"
      "jg .Lactor_pursuit_find_nearby_actors_3\n\t"
      ".Lactor_pursuit_find_nearby_actors_2:\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1d530]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_pursuit_find_nearby_actors_3\n\t"
      "flds 0x11c(%%esi)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_pursuit_find_nearby_actors_3\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl 0x11c(%%esi), %%ecx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      ".Lactor_pursuit_find_nearby_actors_3:\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c64570]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lactor_pursuit_find_nearby_actors_1\n\t"
      ".Lactor_pursuit_find_nearby_actors_4:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movswl %%bx, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jge .Lactor_pursuit_find_nearby_actors_10\n\t"
      "movl 0x34(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_pursuit_find_nearby_actors_10\n\t"
      "pushl %%eax\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c59a00]\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59a50]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lactor_pursuit_find_nearby_actors_10\n\t"
      "nop\n\t"
      ".Lactor_pursuit_find_nearby_actors_5:\n\t"
      "cmpl $-1, 0x18(%%esi)\n\t"
      "je .Lactor_pursuit_find_nearby_actors_9\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1d530]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_pursuit_find_nearby_actors_9\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c64ab0]\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "jne .Lactor_pursuit_find_nearby_actors_6\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c64b40]\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lactor_pursuit_find_nearby_actors_9\n\t"
      ".Lactor_pursuit_find_nearby_actors_6:\n\t"
      "flds 0x12c(%%esi)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "fsubs 0x12c(%%ebx)\n\t"
      "incl %%eax\n\t"
      "flds 0x130(%%esi)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fsubs 0x130(%%ebx)\n\t"
      "flds 0x134(%%esi)\n\t"
      "fsubs 0x134(%%ebx)\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xde, 0xcb\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xc3\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      ".byte 0xde, 0xc3\n\t"
      "fxch %%st(2)\n\t"
      "fsqrt\n\t"
      "fstp %%st(2)\n\t"
      "fstp %%st(0)\n\t"
      "fcoms -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_pursuit_find_nearby_actors_7\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jmp .Lactor_pursuit_find_nearby_actors_8\n\t"
      ".Lactor_pursuit_find_nearby_actors_7:\n\t"
      "fstp %%st(0)\n\t"
      ".Lactor_pursuit_find_nearby_actors_8:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "cmpl -0x14(%%ebp), %%eax\n\t"
      "jge .Lactor_pursuit_find_nearby_actors_10\n\t"
      ".Lactor_pursuit_find_nearby_actors_9:\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59a50]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lactor_pursuit_find_nearby_actors_5\n\t"
      ".Lactor_pursuit_find_nearby_actors_10:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%edx, 0x1d0(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b20280_dget), [c64540] "m"(b20280_c64540), [c64570] "m"(b20280_c64570), [c1d530] "m"(b20280_c1d530), [c59a00] "m"(b20280_c59a00), [c59a50] "m"(b20280_c59a50), [c64ab0] "m"(b20280_c64ab0), [c64b40] "m"(b20280_c64b40)
      : "memory");
}
#else
#error "actor_pursuit_find_nearby_actors: clang naked draft required"
#endif


/* actor_action_consider_grenade (0x1fb80) — XBE naked draft (batch 86). */
#if defined(__clang__)
static void *(*const b1fb80_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1fb80_tag)(int, int) = tag_get;
static int (*const b1fb80_gtime)(void) = game_time_get;
static float (*const b1fb80_cb55b0)(short value_type, int team) = FUN_000b55b0;
static int *(*const b1fb80_gseed)(void) = get_global_random_seed_address;
static float (*const b1fb80_rmreal)(unsigned int *) = random_math_real;
static char (*const b1fb80_c1d180)(int actor_handle) = actor_action_test_grenade;
static char (*const b1fb80_c1fa60)(int actor_handle, char flag) = actor_action_try_to_throw_grenade;

__attribute__((naked, noinline))
char actor_action_consider_grenade(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x5c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637476\n\t"
      "call *%[tag]\n\t"
      "movb 0x6a0(%%esi), %%cl\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "xorb %%al, %%al\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lactor_action_consider_grenade_2\n\t"
      "movl 0x632574, %%ecx\n\t"
      "movb 0x3b4(%%ecx), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .Lactor_action_consider_grenade_4\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "cmpw %%cx, 0x180(%%edi)\n\t"
      "je .Lactor_action_consider_grenade_4\n\t"
      "cmpw %%cx, 0x182(%%edi)\n\t"
      "je .Lactor_action_consider_grenade_4\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x6a4(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "je .Lactor_action_consider_grenade_1\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "flds 0x1a4(%%edi)\n\t"
      "fmuls 0x253394\n\t"
      "fiaddl -0x8(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lactor_action_consider_grenade_3\n\t"
      ".Lactor_action_consider_grenade_1:\n\t"
      "movl 0x1a0(%%edi), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x3e(%%esi), %%ax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl $0x17\n\t"
      "call *%[cb55b0]\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "movl %%ebx, 0x6a4(%%esi)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fcomps -0x4(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_action_consider_grenade_3\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d180]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_consider_grenade_3\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "movb $1, 0x6a0(%%esi)\n\t"
      "call *%[c1fa60]\n\t"
      "addl $8, %%esp\n\t"
      ".Lactor_action_consider_grenade_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_consider_grenade_3:\n\t"
      "xorb %%al, %%al\n\t"
      ".Lactor_action_consider_grenade_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1fb80_dget), [tag] "m"(b1fb80_tag), [gtime] "m"(b1fb80_gtime), [cb55b0] "m"(b1fb80_cb55b0), [gseed] "m"(b1fb80_gseed), [rmreal] "m"(b1fb80_rmreal), [c1d180] "m"(b1fb80_c1d180), [c1fa60] "m"(b1fb80_c1fa60)
      : "memory");
}
#else
#error "actor_action_consider_grenade: clang naked draft required"
#endif


/* actor_action_try_to_evade (0x1fca0) — XBE naked draft (batch 83). */
#if defined(__clang__)
static void *(*const b1fca0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const b1fca0_c2a360)(int actor_handle) = FUN_0002a360;
static void *(*const b1fca0_tag)(int, int) = tag_get;
static void *(*const b1fca0_get)(int, int) = object_get_and_verify_type;
static float (*const b1fca0_c13070)(float *a, float *b) = FUN_00013070;
static float (*const b1fca0_mag)(float *) = magnitude3d;
static char (*const b1fca0_c2ab40)(int actor_handle, float *alignment_vector, float param_3, unsigned short *evade_direction_reference, float param_5, char *out_flag, void *result) = actor_move_try_evasion_direction;
static void (*const b1fca0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1fca0_exitfn)(int) = system_exit;
static uint32_t (*const b1fca0_c1a97c0)(int unit_handle, int impulse_index) = unit_test_animation_impulse;
static int (*const b1fca0_c2a7e0)(int actor_handle, int16_t param_2, int *param_3) = actor_move_animation_impulse;

__attribute__((naked, noinline))
char actor_action_try_to_evade(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x158(%%esi), %%eax\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jne .Lactor_action_try_to_evade_7\n\t"
      "pushl %%edi\n\t"
      "call *%[c2a360]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_try_to_evade_7\n\t"
      "movb 0x504(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_try_to_evade_7\n\t"
      "cmpl %%ebx, 0x270(%%esi)\n\t"
      "je .Lactor_action_try_to_evade_7\n\t"
      "movl 0x58(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0x270(%%esi), %%ecx\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[dget]\n\t"
      "flds 0x234(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $0x20, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_action_try_to_evade_7\n\t"
      "testl $0x200000, (%%edi)\n\t"
      "leal 0xe0(%%ecx), %%edi\n\t"
      "je .Lactor_action_try_to_evade_1\n\t"
      "leal 0x174(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c13070]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Lactor_action_try_to_evade_2\n\t"
      ".Lactor_action_try_to_evade_1:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_action_try_to_evade_3\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x178(%%esi)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x174(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      ".Lactor_action_try_to_evade_2:\n\t"
      "fcomps 0x253524\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_action_try_to_evade_7\n\t"
      ".Lactor_action_try_to_evade_3:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $4, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fstp %%st(0)\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x234(%%ebx), %%ecx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "leal -0x2(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c2ab40]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_try_to_evade_7\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .Lactor_action_try_to_evade_4\n\t"
      "movl $7, %%edi\n\t"
      "jmp .Lactor_action_try_to_evade_6\n\t"
      ".Lactor_action_try_to_evade_4:\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Lactor_action_try_to_evade_5\n\t"
      "pushl $1\n\t"
      "pushl $0xce3\n\t"
      "pushl $0x2544b0\n\t"
      "pushl $0x254874\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_action_try_to_evade_5:\n\t"
      "movl $6, %%edi\n\t"
      ".Lactor_action_try_to_evade_6:\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a97c0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_try_to_evade_7\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c2a7e0]\n\t"
      "addl $0xc, %%esp\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      ".Lactor_action_try_to_evade_7:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1fca0_dget), [c2a360] "m"(b1fca0_c2a360), [tag] "m"(b1fca0_tag), [get] "m"(b1fca0_get), [c13070] "m"(b1fca0_c13070), [mag] "m"(b1fca0_mag), [c2ab40] "m"(b1fca0_c2ab40), [assert] "m"(b1fca0_assert), [exitfn] "m"(b1fca0_exitfn), [c1a97c0] "m"(b1fca0_c1a97c0), [c2a7e0] "m"(b1fca0_c2a7e0)
      : "memory");
}
#else
#error "actor_action_try_to_evade: clang naked draft required"
#endif


/* actor_action_try_to_dive (0x1fe70) — XBE naked draft (batch 80). */
#if defined(__clang__)
static void *(*const b1fe70_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const b1fe70_gtime)(void) = game_time_get;
static char (*const b1fe70_c2ab40)(int actor_handle, float *alignment_vector, float param_3, unsigned short *evade_direction_reference, float param_5, char *out_flag, void *result) = actor_move_try_evasion_direction;
static void (*const b1fe70_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1fe70_exitfn)(int) = system_exit;
static uint32_t (*const b1fe70_c1a97c0)(int unit_handle, int impulse_index) = unit_test_animation_impulse;
static int (*const b1fe70_c2a7e0)(int actor_handle, int16_t param_2, int *param_3) = actor_move_animation_impulse;
static void (*const b1fe70_c46f10)(int16_t type, int unit_handle, int param3, int param4, int16_t param5, int16_t param6, int16_t param7) = FUN_00046f10;

__attribute__((naked, noinline))
char actor_action_try_to_dive(int actor_handle __attribute__((unused)), short direction_ref __attribute__((unused)), float param_3 __attribute__((unused)), float *direction __attribute__((unused)), float param_5 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x4c, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x331f58, %%ecx\n\t"
      "movl %%esi, %%edi\n\t"
      "andl $0xffff, %%edi\n\t"
      "imull $0x657c, %%edi, %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "movl %%ebx, -0x18(%%ebp)\n\t"
      "addl %%ecx, %%edi\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, 0x184(%%edi)\n\t"
      "cmpl $-1, 0x158(%%ebx)\n\t"
      "jne .Lactor_action_try_to_dive_19\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "leal -0x4c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x1(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "leal 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c2ab40]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_try_to_dive_19\n\t"
      "movswl 0xc(%%ebp), %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .Lactor_action_try_to_dive_5\n\t"
      "jmp *.Lactor_action_try_to_dive_jt0(,%%eax,4)\n\t"
      ".Lactor_action_try_to_dive_1:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "flds 0x4(%%eax)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "fchs\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "jmp .Lactor_action_try_to_dive_6\n\t"
      ".Lactor_action_try_to_dive_2:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "flds (%%eax)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "fchs\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "jmp .Lactor_action_try_to_dive_6\n\t"
      ".Lactor_action_try_to_dive_3:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "flds 0x4(%%eax)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "jmp .Lactor_action_try_to_dive_6\n\t"
      ".Lactor_action_try_to_dive_4:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "flds 0x4(%%eax)\n\t"
      "movl (%%eax), %%edx\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "jmp .Lactor_action_try_to_dive_6\n\t"
      ".Lactor_action_try_to_dive_5:\n\t"
      "pushl $1\n\t"
      "pushl $0xd24\n\t"
      "pushl $0x2544b0\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_action_try_to_dive_6:\n\t"
      "flds 0x178(%%ebx)\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "fchs\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "flds 0x174(%%ebx)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "movl $0xbf000000, -0xc(%%ebp)\n\t"
      "fmuls 0x178(%%ebx)\n\t"
      "movl $0x2542b2, %%esi\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x174(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      ".Lactor_action_try_to_dive_7:\n\t"
      "movw (%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lactor_action_try_to_dive_8\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .Lactor_action_try_to_dive_9\n\t"
      ".Lactor_action_try_to_dive_8:\n\t"
      "pushl $1\n\t"
      "pushl $0xd3e\n\t"
      "pushl $0x2544b0\n\t"
      "pushl $0x2548a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_action_try_to_dive_9:\n\t"
      "movswl (%%esi), %%eax\n\t"
      "flds -0x30(%%ebp,%%eax,4)\n\t"
      "fadds 0x2(%%esi)\n\t"
      "fcomps -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_action_try_to_dive_10\n\t"
      "movl 0x18(%%ebx), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw -0x2(%%esi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1a97c0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_try_to_dive_10\n\t"
      "movw -0x2(%%esi), %%ax\n\t"
      "movw %%ax, -0x8(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%esi), %%ax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "flds -0x30(%%ebp,%%ecx,4)\n\t"
      "fadds 0x2(%%esi)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      ".Lactor_action_try_to_dive_10:\n\t"
      "addl $8, %%esi\n\t"
      "cmpw $-1, -0x2(%%esi)\n\t"
      "jne .Lactor_action_try_to_dive_7\n\t"
      "cmpw $-1, -0x8(%%ebp)\n\t"
      "jne .Lactor_action_try_to_dive_11\n\t"
      "movw $2, 0x188(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_try_to_dive_11:\n\t"
      "movswl -0x10(%%ebp), %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .Lactor_action_try_to_dive_16\n\t"
      "jmp *.Lactor_action_try_to_dive_jt1(,%%eax,4)\n\t"
      ".Lactor_action_try_to_dive_12:\n\t"
      "flds -0x20(%%ebp)\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "fchs\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "jmp .Lactor_action_try_to_dive_17\n\t"
      ".Lactor_action_try_to_dive_13:\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "fchs\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "jmp .Lactor_action_try_to_dive_17\n\t"
      ".Lactor_action_try_to_dive_14:\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "jmp .Lactor_action_try_to_dive_17\n\t"
      ".Lactor_action_try_to_dive_15:\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "jmp .Lactor_action_try_to_dive_17\n\t"
      ".Lactor_action_try_to_dive_16:\n\t"
      "pushl $1\n\t"
      "pushl $0xd69\n\t"
      "pushl $0x2544b0\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_action_try_to_dive_17:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2a7e0]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lactor_action_try_to_dive_18\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl 0x18(%%edx), %%eax\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2c\n\t"
      "call *%[c46f10]\n\t"
      "addl $0x1c, %%esp\n\t"
      "movw $4, 0x188(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_try_to_dive_18:\n\t"
      "movw $3, 0x188(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_try_to_dive_19:\n\t"
      "movw $1, 0x188(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lactor_action_try_to_dive_jt0:\n\t"
      ".long .Lactor_action_try_to_dive_1\n\t"
      ".long .Lactor_action_try_to_dive_2\n\t"
      ".long .Lactor_action_try_to_dive_3\n\t"
      ".long .Lactor_action_try_to_dive_4\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lactor_action_try_to_dive_jt1:\n\t"
      ".long .Lactor_action_try_to_dive_12\n\t"
      ".long .Lactor_action_try_to_dive_13\n\t"
      ".long .Lactor_action_try_to_dive_14\n\t"
      ".long .Lactor_action_try_to_dive_15\n\t"
      ".text\n\t"
      :
      : [dget] "m"(b1fe70_dget), [gtime] "m"(b1fe70_gtime), [c2ab40] "m"(b1fe70_c2ab40), [assert] "m"(b1fe70_assert), [exitfn] "m"(b1fe70_exitfn), [c1a97c0] "m"(b1fe70_c1a97c0), [c2a7e0] "m"(b1fe70_c2a7e0), [c46f10] "m"(b1fe70_c46f10)
      : "memory");
}
#else
#error "actor_action_try_to_dive: clang naked draft required"
#endif


/* actor_action_handle_berserk_transition (0x20470) — readable C lift. */
char actor_action_handle_berserk_transition(int actor_handle, short param_2)
{
  char *actor;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  if (*(short *)(actor + 0x310) < param_2 || actor[0x378] != 0) {
    *(short *)(actor + 0x310) = 0;
    return 0;
  }
  actor_berserk(actor_handle, 1);
  if (*(short *)(actor + 0x6e) >= 4) {
    actor_action_handle_combat_selection(actor_handle);
    *(short *)(actor + 0x310) = 0;
    return 0;
  }
  *(short *)(actor + 0x310) = 0;
  return 0;
}


/* actor_action_handle_combat_transition (0x204f0) — readable C lift. */
char actor_action_handle_combat_transition(int actor_handle)
{
  char *actor;
  char buf[0x84];
  int16_t alert;

  actor = (char *)datum_get(actor_data, actor_handle);
  alert = *(int16_t *)(actor + 0x6a);
  if (alert < 3) {
    if (*(int16_t *)(actor + 0x312) != 0) {
      *(int16_t *)(actor + 0x6a) = 3;
      if (FUN_00016050(actor_handle, (short *)buf)) {
        actor_action_change(actor_handle, 6, (int)buf);
        *(int16_t *)(actor + 0x312) = 0;
        return 1;
      }
      actor_action_handle_combat_selection(actor_handle);
      *(int16_t *)(actor + 0x312) = 0;
      return 1;
    }
  } else if (alert == 3 && *(int16_t *)(actor + 0x6e) == 0) {
    actor_action_try_to_panic(actor_handle);
  }
  return 0;
}

/* actor_action_handle_grenade_throwing (0x205a0) — readable C lift. */
char actor_action_handle_grenade_throwing(int actor_handle)
{
  char *actor;
  char *unit;
  char *prop;
  char result;
  int kind;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  unit = (char *)tag_get(0x61637476, *(int *)(actor + 0x5c)); /* 'actv' */
  result = 0;
  if (*(short *)(actor + 0x268) < 5) {
    actor[0x6a0] = 0;
    return 0;
  }
  if (*(short *)(actor + 0x6c) == 4 && *(short *)(actor + 0xa8) > 0) {
    actor[0x6a0] = 0;
    return 0;
  }
  prop = (char *)datum_get(*(data_t **)0x5ab23c, *(int *)(actor + 0x270));
  kind = (int)*(short *)(unit + 0x184);
  if (kind == 1) {
    if (*(short *)(actor + 0x6e) >= 5) {
      result = actor_action_consider_grenade(actor_handle);
    }
  } else if (kind == 2) {
    if (prop[0x14] != 0 || (*(short *)(actor + 0x6c) == 4 && *(short *)(actor + 0xa8) == 0)) {
      result = actor_action_consider_grenade(actor_handle);
    }
  }
  if (actor[0x6a0] != 0) {
    actor_action_try_to_throw_grenade(actor_handle, 0);
  }
  return result;
}

/* actor_action_handle_evasion (0x20670) — XBE naked draft (batch 80). */
#if defined(__clang__)
static void *(*const b20670_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b20670_tag)(int, int) = tag_get;
static int (*const b20670_gtime)(void) = game_time_get;
static char (*const b20670_c1ccc0)(int actor_handle, char param_2) = actor_action_allow_cover_seeking;
static char (*const b20670_c1d350)(int actor_handle, char param_2, char param_3) = actor_action_try_to_seek_cover;
static char (*const b20670_c1d3c0)(int actor_handle, short param_2, int param_3, char param_4) = FUN_0001d3c0;
static int *(*const b20670_gseed)(void) = get_global_random_seed_address;
static float (*const b20670_rmreal)(unsigned int *) = random_math_real;
static char (*const b20670_c1fb80)(int actor_handle) = actor_action_consider_grenade;
static int (*const b20670_c3b380)(int actor_handle) = actor_target_unit_index;
static void (*const b20670_c46f10)(int16_t type, int unit_handle, int param3, int param4, int16_t param5, int16_t param6, int16_t param7) = FUN_00046f10;
static char (*const b20670_c1fca0)(int actor_handle) = actor_action_try_to_evade;
static void (*const b20670_ftol)(void) = FUN_001d9068;

__attribute__((naked, noinline))
char actor_action_handle_evasion(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x5c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637476\n\t"
      "call *%[tag]\n\t"
      "movl 0x58(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637472\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "addl $0x18, %%esp\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[gtime]\n\t"
      "cmpw $0, 0x3a8(%%esi)\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jle .Lactor_action_handle_evasion_3\n\t"
      "cmpl $-1, 0x158(%%esi)\n\t"
      "jne .Lactor_action_handle_evasion_3\n\t"
      "movl 0x3ac(%%esi), %%eax\n\t"
      "movl 0x5ab23c, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movb 0xa4(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lactor_action_handle_evasion_3\n\t"
      "movw 0x38(%%eax), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Lactor_action_handle_evasion_1\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .Lactor_action_handle_evasion_3\n\t"
      ".Lactor_action_handle_evasion_1:\n\t"
      "movl 0x36c(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_action_handle_evasion_2\n\t"
      "addl $0x1e, %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jg .Lactor_action_handle_evasion_3\n\t"
      ".Lactor_action_handle_evasion_2:\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, 0x36c(%%esi)\n\t"
      "call *%[c1ccc0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_evasion_3\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d350]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_evasion_15\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "testl $0x400000, (%%ebx)\n\t"
      "je .Lactor_action_handle_evasion_4\n\t"
      "movl 0x3ac(%%esi), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl $5\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d3c0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_evasion_4\n\t"
      "popl %%edi\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_handle_evasion_3:\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      ".Lactor_action_handle_evasion_4:\n\t"
      "movb 0x374(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_evasion_5\n\t"
      "movb 0x378(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_evasion_5\n\t"
      "flds 0x314(%%ebx)\n\t"
      "jmp .Lactor_action_handle_evasion_6\n\t"
      ".Lactor_action_handle_evasion_5:\n\t"
      "flds 0x310(%%ebx)\n\t"
      ".Lactor_action_handle_evasion_6:\n\t"
      "movb 0x1ca(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_evasion_7\n\t"
      "flds 0x318(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_action_handle_evasion_7\n\t"
      "fcoms 0x253f38\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_action_handle_evasion_7\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x253f38\n\t"
      ".Lactor_action_handle_evasion_7:\n\t"
      "fcomps 0x354(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_action_handle_evasion_16\n\t"
      "movb 0x504(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_evasion_8\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fstp %%st(0)\n\t"
      "addl $4, %%esp\n\t"
      ".Lactor_action_handle_evasion_8:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "cmpw $2, 0x184(%%eax)\n\t"
      "jne .Lactor_action_handle_evasion_9\n\t"
      "pushl %%edi\n\t"
      "call *%[c1fb80]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_evasion_9\n\t"
      "movl $0, 0x354(%%esi)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".Lactor_action_handle_evasion_9:\n\t"
      "movb 0x358(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb $1, %%bl\n\t"
      "movb %%bl, -0x2(%%ebp)\n\t"
      "je .Lactor_action_handle_evasion_10\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "testb $0x20, (%%ecx)\n\t"
      "je .Lactor_action_handle_evasion_10\n\t"
      "movl 0x270(%%esi), %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_action_handle_evasion_10\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movb 0x122(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "cmpb $2, %%cl\n\t"
      "jg .Lactor_action_handle_evasion_10\n\t"
      "cmpb $1, 0x121(%%eax)\n\t"
      "jg .Lactor_action_handle_evasion_10\n\t"
      "movb $1, %%bl\n\t"
      ".Lactor_action_handle_evasion_10:\n\t"
      "cmpw $0xa, 0x6c(%%esi)\n\t"
      "jne .Lactor_action_handle_evasion_12\n\t"
      "movw 0xa0(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "je .Lactor_action_handle_evasion_11\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .Lactor_action_handle_evasion_12\n\t"
      ".Lactor_action_handle_evasion_11:\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      ".Lactor_action_handle_evasion_12:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_evasion_16\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lactor_action_handle_evasion_14\n\t"
      "movl 0x36c(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_action_handle_evasion_13\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "addl $0x1e, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jg .Lactor_action_handle_evasion_14\n\t"
      ".Lactor_action_handle_evasion_13:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, 0x36c(%%esi)\n\t"
      "call *%[c1ccc0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_evasion_14\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "fcomps 0x318(%%ecx)\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_action_handle_evasion_14\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d350]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_evasion_14\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[c3b380]\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl $0x18\n\t"
      "call *%[c46f10]\n\t"
      "addl $0x1c, %%esp\n\t"
      "popl %%edi\n\t"
      "movl $0, 0x354(%%esi)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_handle_evasion_14:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_evasion_16\n\t"
      "cmpw $0, 0x368(%%esi)\n\t"
      "jne .Lactor_action_handle_evasion_16\n\t"
      "pushl %%edi\n\t"
      "call *%[c1fca0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_evasion_16\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl $0, 0x354(%%esi)\n\t"
      "flds 0x31c(%%eax)\n\t"
      "fmuls 0x253394\n\t"
      "call *%[ftol]\n\t"
      "movw %%ax, 0x368(%%esi)\n\t"
      "movb $1, 0x3bb(%%esi)\n\t"
      ".Lactor_action_handle_evasion_15:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".Lactor_action_handle_evasion_16:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b20670_dget), [tag] "m"(b20670_tag), [gtime] "m"(b20670_gtime), [c1ccc0] "m"(b20670_c1ccc0), [c1d350] "m"(b20670_c1d350), [c1d3c0] "m"(b20670_c1d3c0), [gseed] "m"(b20670_gseed), [rmreal] "m"(b20670_rmreal), [c1fb80] "m"(b20670_c1fb80), [c3b380] "m"(b20670_c3b380), [c46f10] "m"(b20670_c46f10), [c1fca0] "m"(b20670_c1fca0), [ftol] "m"(b20670_ftol)
      : "memory");
}
#else
#error "actor_action_handle_evasion: clang naked draft required"
#endif


/* FUN_00021080 (0x21080) — Returns non-zero if the actor's fire_state
 * enum (actor+0x5f2) equals 4. Paired with FUN_00021040 (actor_combat.c),
 * which sets fire_state to 4. */
char FUN_00021080(int actor_handle)
{
  char *actor;

  actor = (char *)datum_get(actor_data, actor_handle);
  return *(short *)(actor + 0x5f2) == 4;
}

/* FUN_000210b0 (0x210b0) — Primary-look eligibility predicate. Resolves the
 * actor via datum_get(actor_data, actor_handle) and returns true only when the
 * signed 16-bit action counter/timer at actor+0x60c is positive (> 0; signed
 * CMP/JLE in the original) AND the fire_state enum at actor+0x5f2 (same field
 * read by sibling FUN_00021080) equals 2. When the counter is <= 0 it returns
 * false without inspecting fire_state. Called by actor_looking to gate primary
 * look-mode selection. */
bool FUN_000210b0(int actor_handle)
{
  char *actor;
  bool result;

  actor = (char *)datum_get(actor_data, actor_handle);
  result = 0;
  if (*(short *)(actor + 0x60c) > 0) {
    result = *(short *)(actor + 0x5f2) == 2;
  }
  return result;
}
/* --- actions.obj batch drafts (2026-07-26) --- */

/* action_vehicle_perform (0x1b8a0) — XBE naked draft (batch 111). */
#if defined(__clang__)
static void *(*const b1b8a0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1b8a0_tryget)(int, int) = object_try_and_get_and_verify_type;
static void (*const b1b8a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1b8a0_exitfn)(int) = system_exit;
static void (*const b1b8a0_c1ada0)(void) = FUN_0001ada0;
static int (*const b1b8a0_gtime)(void) = game_time_get;
static float (*const b1b8a0_c121a0)(const float *a, const float *b) = distance_squared3d;
static char (*const b1b8a0_c1aeb0)(int actor_handle, int vehicle_handle, short seat_index, int param_4, float *out_attach0, float *out_attach1, float *out_attach2, int param_8, int param_9, int param_10, int param_11) = FUN_0001aeb0;
static bool (*const b1b8a0_c1b2b80)(int unit_handle, int vehicle_handle, int16_t seat_index) = unit_board_vehicle;
static void (*const b1b8a0_c2f1a0)(int actor_handle) = FUN_0002f1a0;
static char (*const b1b8a0_c1b280)(int actor_handle, int object_handle, float *in_attach0, float *in_attach1, float *in_attach2, int param_6, float *out_position, int *out_handle) = FUN_0001b280;
static char (*const b1b8a0_c2d720)(int actor_handle, float *destination, int param_3, int param_4) = actor_move_to_point;

__attribute__((naked, noinline))
void action_vehicle_perform(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x28, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x9c(%%edi), %%ecx\n\t"
      "pushl $2\n\t"
      "pushl %%ecx\n\t"
      "call *%[tryget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x6(%%edi), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_vehicle_perform_1\n\t"
      "pushl $1\n\t"
      "pushl $0xa1\n\t"
      "pushl $0x253f50\n\t"
      "pushl $0x253380\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Laction_vehicle_perform_1:\n\t"
      "movl 0x158(%%edi), %%ecx\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .Laction_vehicle_perform_2\n\t"
      "movb $1, 0xa5(%%edi)\n\t"
      "jmp .Laction_vehicle_perform_4\n\t"
      ".Laction_vehicle_perform_2:\n\t"
      "movb 0xa4(%%edi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Laction_vehicle_perform_4\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Laction_vehicle_perform_5\n\t"
      "movl %%eax, 0x9c(%%edi)\n\t"
      ".Laction_vehicle_perform_3:\n\t"
      "movb $1, 0xa6(%%edi)\n\t"
      ".Laction_vehicle_perform_4:\n\t"
      "movb 0xa5(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_vehicle_perform_18\n\t"
      "movb 0xa6(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_vehicle_perform_18\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Laction_vehicle_perform_5:\n\t"
      "movl 0xc0(%%edi), %%edx\n\t"
      "movl 0xbc(%%edi), %%eax\n\t"
      "movl 0x9c(%%edi), %%esi\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movb 0xa2(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "sete %%cl\n\t"
      "movl %%ebx, %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ada0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_vehicle_perform_3\n\t"
      "call *%[gtime]\n\t"
      "movl 0xac(%%edi), %%edx\n\t"
      "addl $0x96, %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .Laction_vehicle_perform_8\n\t"
      "leal 0x12c(%%edi), %%esi\n\t"
      "leal 0xb0(%%edi), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, 0xac(%%edi)\n\t"
      "call *%[c121a0]\n\t"
      "fcomps 0x253f74\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Laction_vehicle_perform_6\n\t"
      "incw 0xaa(%%edi)\n\t"
      "jmp .Laction_vehicle_perform_7\n\t"
      ".Laction_vehicle_perform_6:\n\t"
      "movw $0, 0xaa(%%edi)\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x4(%%ebx)\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movl %%edx, 0x8(%%ebx)\n\t"
      ".Laction_vehicle_perform_7:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      ".Laction_vehicle_perform_8:\n\t"
      "cmpw $8, 0xaa(%%edi)\n\t"
      "jge .Laction_vehicle_perform_3\n\t"
      "leal -0x3(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x2(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movb 0xa2(%%edi), %%al\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "testb %%al, %%al\n\t"
      "sete %%al\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0xa0(%%edi), %%cx\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x9c(%%edi), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1aeb0]\n\t"
      "addl $0x2c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_vehicle_perform_3\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_vehicle_perform_9\n\t"
      "incw 0xc6(%%edi)\n\t"
      "cmpw $0x1e, 0xc6(%%edi)\n\t"
      "jl .Laction_vehicle_perform_10\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "jmp .Laction_vehicle_perform_11\n\t"
      ".Laction_vehicle_perform_9:\n\t"
      "movw $0, 0xc6(%%edi)\n\t"
      ".Laction_vehicle_perform_10:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_vehicle_perform_13\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_vehicle_perform_12\n\t"
      ".Laction_vehicle_perform_11:\n\t"
      "movl 0x9c(%%edi), %%ecx\n\t"
      "movl 0x18(%%edi), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0xa0(%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1b2b80]\n\t"
      "addl $0xc, %%esp\n\t"
      "movb $1, 0xa4(%%edi)\n\t"
      "jmp .Laction_vehicle_perform_15\n\t"
      ".Laction_vehicle_perform_12:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c2f1a0]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .Laction_vehicle_perform_15\n\t"
      ".Laction_vehicle_perform_13:\n\t"
      "movb 0x4c(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_vehicle_perform_15\n\t"
      "leal 0xe4(%%edi), %%esi\n\t"
      "pushl %%esi\n\t"
      "leal 0xcc(%%edi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "leal 0xa3(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x9c(%%edi), %%eax\n\t"
      "call *%[c1b280]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_vehicle_perform_14\n\t"
      "movl 0x9c(%%edi), %%ecx\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c2d720]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_vehicle_perform_14\n\t"
      "movw $0, 0xa8(%%edi)\n\t"
      "jmp .Laction_vehicle_perform_15\n\t"
      ".Laction_vehicle_perform_14:\n\t"
      "incw 0xa8(%%edi)\n\t"
      "movb 0xa2(%%edi), %%cl\n\t"
      "movw 0xa8(%%edi), %%ax\n\t"
      "negb %%cl\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl $0xffffffd3, %%ecx\n\t"
      "addl $0x32, %%ecx\n\t"
      "cmpw %%cx, %%ax\n\t"
      "jle .Laction_vehicle_perform_15\n\t"
      "movb $1, 0xa6(%%edi)\n\t"
      ".Laction_vehicle_perform_15:\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x12c(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c121a0]\n\t"
      "fcomps 0x2533c8\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Laction_vehicle_perform_16\n\t"
      "movl $1, %%eax\n\t"
      "jmp .Laction_vehicle_perform_17\n\t"
      ".Laction_vehicle_perform_16:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Laction_vehicle_perform_17:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "leal 0xd8(%%edi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movb %%al, 0xc8(%%edi)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movb -0x2(%%ebp), %%cl\n\t"
      "movb %%al, 0xc5(%%edi)\n\t"
      "movb %%cl, 0xc4(%%edi)\n\t"
      "jmp .Laction_vehicle_perform_4\n\t"
      ".Laction_vehicle_perform_18:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1b8a0_dget), [tryget] "m"(b1b8a0_tryget), [assert] "m"(b1b8a0_assert), [exitfn] "m"(b1b8a0_exitfn), [c1ada0] "m"(b1b8a0_c1ada0), [gtime] "m"(b1b8a0_gtime), [c121a0] "m"(b1b8a0_c121a0), [c1aeb0] "m"(b1b8a0_c1aeb0), [c1b2b80] "m"(b1b8a0_c1b2b80), [c2f1a0] "m"(b1b8a0_c2f1a0), [c1b280] "m"(b1b8a0_c1b280), [c2d720] "m"(b1b8a0_c2d720)
      : "memory");
}
#else
#error "action_vehicle_perform: clang naked draft required"
#endif


/* action_vehicle_setup_impromptu (0x1bcd0) — XBE naked draft (batch 115). */
#if defined(__clang__)
static void *(*const b1bcd0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b1bcd0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1bcd0_exitfn)(int) = system_exit;
static void *(*const b1bcd0_memset)(void *, int, unsigned int) = csmemset;
static void *(*const b1bcd0_get)(int, int) = object_get_and_verify_type;
static vector3_t * (*const b1bcd0_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static float (*const b1bcd0_c12170)(float *vector) = FUN_00012170;
static int (*const b1bcd0_c1bba0)(int actor_handle, int vehicle_handle, float *out_attach0, float *out_attach1, float *out_attach2) = FUN_0001bba0;
static char (*const b1bcd0_c1b0d00)(int unit_handle, int vehicle_handle, int16_t seat_index) = unit_has_animation_to_enter_seat;
static char (*const b1bcd0_c1b280)(int actor_handle, int object_handle, float *in_attach0, float *in_attach1, float *in_attach2, int param_6, float *out_position, int *out_handle) = FUN_0001b280;
static char (*const b1bcd0_c2d720)(int actor_handle, float *destination, int param_3, int param_4) = actor_move_to_point;

__attribute__((naked, noinline))
char action_vehicle_setup_impromptu(int actor_handle __attribute__((unused)), int vehicle_handle __attribute__((unused)), float param_3 __attribute__((unused)), float param_4 __attribute__((unused)), void *out_state __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x2c, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jne .Laction_vehicle_setup_impromptu_1\n\t"
      "pushl $1\n\t"
      "pushl $0x38\n\t"
      "pushl $0x253f50\n\t"
      "pushl $0x25334c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Laction_vehicle_setup_impromptu_1:\n\t"
      "pushl $0x4c\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl %%ecx, 0x20(%%esi)\n\t"
      "movl %%edx, 0x24(%%esi)\n\t"
      "movl 0x158(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Laction_vehicle_setup_impromptu_4\n\t"
      "movb 0x6(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_vehicle_setup_impromptu_4\n\t"
      "cmpw $9, 0x6c(%%edi)\n\t"
      "je .Laction_vehicle_setup_impromptu_4\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "call *%[get]\n\t"
      "movb 0xb6(%%eax), %%cl\n\t"
      "addl $0x10, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "testb $4, %%cl\n\t"
      "movl %%eax, 0x18(%%ebp)\n\t"
      "jne .Laction_vehicle_setup_impromptu_2\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1412f0]\n\t"
      "flds -0x14(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "fsubs 0x12c(%%eax)\n\t"
      "addl $8, %%esp\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fsubs 0x130(%%eax)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsubs 0x134(%%eax)\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fmuls 0x14(%%ebp)\n\t"
      "fcompp\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jne .Laction_vehicle_setup_impromptu_3\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "addl $0x18, %%edx\n\t"
      "pushl %%edx\n\t"
      "movb $1, %%bl\n\t"
      "call *%[c12170]\n\t"
      "fcomps 0x253f2c\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Laction_vehicle_setup_impromptu_3\n\t"
      ".Laction_vehicle_setup_impromptu_2:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".Laction_vehicle_setup_impromptu_3:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "flds 0x38(%%eax)\n\t"
      "fcomps 0x253398\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Laction_vehicle_setup_impromptu_4\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Laction_vehicle_setup_impromptu_4\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl %%edi, (%%esi)\n\t"
      "call *%[c1bba0]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movw %%ax, 0x4(%%esi)\n\t"
      "je .Laction_vehicle_setup_impromptu_4\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movb $1, 0x6(%%esi)\n\t"
      "movl 0x18(%%edx), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1b0d00]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_vehicle_setup_impromptu_4\n\t"
      "leal 0x48(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "addl $0x30, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1b280]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_vehicle_setup_impromptu_4\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c2d720]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_vehicle_setup_impromptu_4\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".Laction_vehicle_setup_impromptu_4:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1bcd0_dget), [assert] "m"(b1bcd0_assert), [exitfn] "m"(b1bcd0_exitfn), [memset] "m"(b1bcd0_memset), [get] "m"(b1bcd0_get), [c1412f0] "m"(b1bcd0_c1412f0), [c12170] "m"(b1bcd0_c12170), [c1bba0] "m"(b1bcd0_c1bba0), [c1b0d00] "m"(b1bcd0_c1b0d00), [c1b280] "m"(b1bcd0_c1b280), [c2d720] "m"(b1bcd0_c2d720)
      : "memory");
}
#else
#error "action_vehicle_setup_impromptu: clang naked draft required"
#endif


/* FUN_0001beb0 (0x1beb0) — XBE naked draft (batch 127). */
#if defined(__clang__)
static void *(*const b1beb0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const b1beb0_c20280)(int actor_handle, char flag) = actor_pursuit_find_nearby_actors;
static int (*const b1beb0_gtime)(void) = game_time_get;
static char (*const b1beb0_c2d9b0)(int actor_handle, int encounter_handle, float distance) = actor_move_to_prop;
static void (*const b1beb0_c2f1a0)(int actor_handle) = FUN_0002f1a0;

__attribute__((naked, noinline))
void FUN_0001beb0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x4c(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0001beb0_9\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb $0, 0x9f(%%esi)\n\t"
      "movb 0x1cc(%%esi), %%cl\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c20280]\n\t"
      "movb 0x9d(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0001beb0_4\n\t"
      "cmpl $-1, 0x1d0(%%esi)\n\t"
      "jne .LFUN_0001beb0_1\n\t"
      "cmpw $0, 0xaa(%%esi)\n\t"
      "jne .LFUN_0001beb0_3\n\t"
      "movw $0x96, 0xaa(%%esi)\n\t"
      "jmp .LFUN_0001beb0_3\n\t"
      ".LFUN_0001beb0_1:\n\t"
      "call *%[gtime]\n\t"
      "movl 0xa4(%%esi), %%edx\n\t"
      "addl $0xa8c, %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .LFUN_0001beb0_3\n\t"
      ".LFUN_0001beb0_2:\n\t"
      "movb $1, 0x9c(%%esi)\n\t"
      ".LFUN_0001beb0_3:\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0001beb0_9\n\t"
      "movb 0x9f(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0001beb0_8\n\t"
      "movl 0x1d0(%%esi), %%ecx\n\t"
      "pushl $0x41000000\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c2d9b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movb 0x9c(%%esi), %%al\n\t"
      "jne .LFUN_0001beb0_10\n\t"
      "popl %%edi\n\t"
      "movb $1, 0xa0(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0001beb0_4:\n\t"
      "movb $1, 0x9c(%%esi)\n\t"
      "movl 0x1d0(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0001beb0_3\n\t"
      "pushl %%eax\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movb 0x9e(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0001beb0_5\n\t"
      "movb 0xa0(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0001beb0_6\n\t"
      ".LFUN_0001beb0_5:\n\t"
      "cmpw $2, 0x32(%%ecx)\n\t"
      "jl .LFUN_0001beb0_2\n\t"
      "flds 0x11c(%%ecx)\n\t"
      "fcomps 0x253f78\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0001beb0_2\n\t"
      "movb 0xa0(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0001beb0_7\n\t"
      ".LFUN_0001beb0_6:\n\t"
      "flds 0x11c(%%ecx)\n\t"
      "fcomps 0x253f30\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0001beb0_7\n\t"
      "movl $1, %%eax\n\t"
      "movb %%al, 0x9f(%%esi)\n\t"
      "movb $0, 0x9c(%%esi)\n\t"
      "jmp .LFUN_0001beb0_3\n\t"
      ".LFUN_0001beb0_7:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb %%al, 0x9f(%%esi)\n\t"
      "movb %%al, 0x9c(%%esi)\n\t"
      "jmp .LFUN_0001beb0_3\n\t"
      ".LFUN_0001beb0_8:\n\t"
      "pushl %%edi\n\t"
      "call *%[c2f1a0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0001beb0_9:\n\t"
      "movb 0x9c(%%esi), %%al\n\t"
      ".LFUN_0001beb0_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1beb0_dget), [c20280] "m"(b1beb0_c20280), [gtime] "m"(b1beb0_gtime), [c2d9b0] "m"(b1beb0_c2d9b0), [c2f1a0] "m"(b1beb0_c2f1a0)
      : "memory");
}
#else
#error "FUN_0001beb0: clang naked draft required"
#endif


/* FUN_0001cda0 (0x1cda0) — XBE naked draft (batch 122). */
#if defined(__clang__)
static void *(*const b1cda0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b1cda0_c2f910)(int actor_handle, int prop_handle) = actor_perception_find_prop_pathfinding_location;
static char (*const b1cda0_c25a00)(int actor_handle, float *position, int surface_index, int group_mask) = actor_has_accessible_firing_position;

__attribute__((naked, noinline))
void FUN_0001cda0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movb %%al, %%bl\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movw %%cx, %%di\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movw %%dx, %%si\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, %%si\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LFUN_0001cda0_1\n\t"
      "cmpw $1, %%si\n\t"
      "jne .LFUN_0001cda0_2\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_0001cda0_2\n\t"
      ".LFUN_0001cda0_1:\n\t"
      "movl 0x24(%%ebp), %%edx\n\t"
      "movb $0, (%%edx)\n\t"
      ".LFUN_0001cda0_2:\n\t"
      "cmpw $2, %%di\n\t"
      "je .LFUN_0001cda0_4\n\t"
      "cmpw $1, %%di\n\t"
      "jne .LFUN_0001cda0_3\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_0001cda0_4\n\t"
      ".LFUN_0001cda0_3:\n\t"
      "movw 0xc(%%ebp), %%cx\n\t"
      "cmpw $2, %%cx\n\t"
      "je .LFUN_0001cda0_5\n\t"
      "cmpw $1, %%cx\n\t"
      "jne .LFUN_0001cda0_6\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_0001cda0_6\n\t"
      "jmp .LFUN_0001cda0_5\n\t"
      ".LFUN_0001cda0_4:\n\t"
      "movl 0x28(%%ebp), %%edx\n\t"
      "movb $0, (%%edx)\n\t"
      ".LFUN_0001cda0_5:\n\t"
      "movl 0x2c(%%ebp), %%ecx\n\t"
      "movb $0, (%%ecx)\n\t"
      ".LFUN_0001cda0_6:\n\t"
      "movb 0x14(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_0001cda0_7\n\t"
      "movl 0x28(%%ebp), %%edx\n\t"
      "movl 0x2c(%%ebp), %%ecx\n\t"
      "movb $0, (%%edx)\n\t"
      "movl 0x30(%%ebp), %%edx\n\t"
      "movb $0, (%%ecx)\n\t"
      "movb $0, (%%edx)\n\t"
      ".LFUN_0001cda0_7:\n\t"
      "movl 0x270(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_0001cda0_8\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movl 0x24(%%ebp), %%ecx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $0, (%%eax)\n\t"
      "movb $0, (%%ecx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0001cda0_8:\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movb 0x18(%%ebp), %%cl\n\t"
      "movl 0x24(%%ebp), %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0xb9(%%esi), %%bl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "movl 0x1c(%%ebp), %%ebx\n\t"
      "sete %%al\n\t"
      "movb %%al, (%%ebx)\n\t"
      "movb 0xba(%%esi), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "sete %%al\n\t"
      "testb %%cl, %%cl\n\t"
      "movb %%al, (%%edi)\n\t"
      "je .LFUN_0001cda0_9\n\t"
      "movb $0, (%%ebx)\n\t"
      "jmp .LFUN_0001cda0_11\n\t"
      ".LFUN_0001cda0_9:\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0001cda0_11\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .LFUN_0001cda0_10\n\t"
      "cmpw $3, %%ax\n\t"
      "jg .LFUN_0001cda0_10\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x270(%%ecx), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c2f910]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0001cda0_10:\n\t"
      "movl 0xec(%%esi), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "addl $0xf0, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c25a00]\n\t"
      "addl $0x10, %%esp\n\t"
      "movb %%al, (%%edi)\n\t"
      ".LFUN_0001cda0_11:\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "cmpb $0, (%%eax)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "jne .LFUN_0001cda0_12\n\t"
      "cmpw $3, 0x6e(%%eax)\n\t"
      "jge .LFUN_0001cda0_12\n\t"
      "movb $0, (%%ebx)\n\t"
      ".LFUN_0001cda0_12:\n\t"
      "cmpw $0, 0x15e(%%eax)\n\t"
      "jle .LFUN_0001cda0_13\n\t"
      "movl 0x30(%%ebp), %%ecx\n\t"
      "movb $0, (%%ecx)\n\t"
      ".LFUN_0001cda0_13:\n\t"
      "cmpw $4, 0x15e(%%eax)\n\t"
      "jne .LFUN_0001cda0_14\n\t"
      "movl 0x2c(%%ebp), %%edx\n\t"
      "movb $0, (%%edi)\n\t"
      "movb $0, (%%edx)\n\t"
      ".LFUN_0001cda0_14:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1cda0_dget), [c2f910] "m"(b1cda0_c2f910), [c25a00] "m"(b1cda0_c25a00)
      : "memory");
}
#else
#error "FUN_0001cda0: clang naked draft required"
#endif


/* actor_action_test_grenade (0x1d180) — XBE naked draft (batch 117). */
#if defined(__clang__)
static void *(*const b1d180_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1d180_tag)(int, int) = tag_get;
static int (*const b1d180_gtime)(void) = game_time_get;
static float (*const b1d180_cb55b0)(short value_type, int team) = FUN_000b55b0;
static void (*const b1d180_ftol)(void) = FUN_001d9068;
static char (*const b1d180_c219e0)(int actor_handle, float *out_pos, int *out_handle, int *out_extra) = actor_combat_find_grenade_target;
static char (*const b1d180_c21ae0)(int actor_handle, float range, float param3, float *encounter_pos, short *out_count) = FUN_00021ae0;
static char (*const b1d180_c21e50)(int actor_handle, short param_2, float *param_3, int param_4, int param_5) = FUN_00021e50;

__attribute__((naked, noinline))
char actor_action_test_grenade(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x5c(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637476\n\t"
      "call *%[tag]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[gtime]\n\t"
      "movl 0x331f58, %%ecx\n\t"
      "andl $0xffff, %%esi\n\t"
      "imull $0x657c, %%esi, %%esi\n\t"
      "addl %%ecx, %%esi\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%eax, 0x150(%%esi)\n\t"
      "cmpl $-1, 0x158(%%edi)\n\t"
      "je .Lactor_action_test_grenade_1\n\t"
      "popl %%edi\n\t"
      "movw $0, 0x154(%%esi)\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_test_grenade_1:\n\t"
      "movl 0x34(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_action_test_grenade_3\n\t"
      "movl 0x5ab270, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x1a8(%%ebx), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2(%%eax), %%dx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "pushl $0x18\n\t"
      "call *%[cb55b0]\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "movb 0x1ca(%%edi), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_test_grenade_2\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      ".Lactor_action_test_grenade_2:\n\t"
      "fmuls 0x253394\n\t"
      "call *%[ftol]\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0x5c(%%edx), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lactor_action_test_grenade_3\n\t"
      "movswl %%ax, %%edi\n\t"
      "addl %%ecx, %%edi\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "jle .Lactor_action_test_grenade_3\n\t"
      "subl %%ecx, %%eax\n\t"
      "movw $5, 0x154(%%esi)\n\t"
      "addw 0x5c(%%edx), %%ax\n\t"
      "popl %%edi\n\t"
      "movw %%ax, 0x156(%%esi)\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_test_grenade_3:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c219e0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_test_grenade_7\n\t"
      "movl 0x19c(%%ebx), %%edx\n\t"
      "leal 0xa(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x188(%%ebx), %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c21ae0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_test_grenade_6\n\t"
      "movw 0xa(%%ebp), %%ax\n\t"
      "cmpw 0x186(%%ebx), %%ax\n\t"
      "jl .Lactor_action_test_grenade_5\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x182(%%ebx), %%cx\n\t"
      "pushl %%edx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c21e50]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_test_grenade_4\n\t"
      "popl %%edi\n\t"
      "movw $0xa, 0x154(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_test_grenade_4:\n\t"
      "popl %%edi\n\t"
      "movw $9, 0x154(%%esi)\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_test_grenade_5:\n\t"
      "movw %%ax, 0x158(%%esi)\n\t"
      "movw $7, 0x154(%%esi)\n\t"
      "movw 0x186(%%ebx), %%dx\n\t"
      "popl %%edi\n\t"
      "movw %%dx, 0x15a(%%esi)\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_test_grenade_6:\n\t"
      "popl %%edi\n\t"
      "movw $8, 0x154(%%esi)\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_test_grenade_7:\n\t"
      "popl %%edi\n\t"
      "movw $6, 0x154(%%esi)\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1d180_dget), [tag] "m"(b1d180_tag), [gtime] "m"(b1d180_gtime), [cb55b0] "m"(b1d180_cb55b0), [ftol] "m"(b1d180_ftol), [c219e0] "m"(b1d180_c219e0), [c21ae0] "m"(b1d180_c21ae0), [c21e50] "m"(b1d180_c21e50)
      : "memory");
}
#else
#error "actor_action_test_grenade: clang naked draft required"
#endif



/* actor_get_pursuit_location (0x1d4f0) — Returns the address of the actor's
 * pursuit-location sub-record (actor+0xa4) when the actor's mode word
 * (field_6c) is 7 or 5; otherwise returns NULL.
 *
 * Confirmed: datum_get(actor_data, actor_handle) — MOV EAX,[EBP+8];
 *   MOV ECX,[0x6325a4]; PUSH EAX; PUSH ECX; CALL 0x119320; ADD ESP,0x8.
 *   First PUSH is the last arg, so the pool is arg1 and the handle is arg2.
 * Confirmed: MOV CX,word ptr [EAX+0x6c] — 16-bit field, loaded ONCE and
 *   compared twice (CMP CX,7 / JZ; CMP CX,5 / JNZ). Read before the ADD ESP.
 * Confirmed: hit path is ADD EAX,0xa4 — 0xa4 is used as an ADDRESS (base of a
 *   sub-record), not dereferenced as a value here (contrast the byte read of
 *   field_a4 in FUN_0001d530).
 * Confirmed: miss path is XOR EDX,EDX / MOV EAX,EDX — returns NULL. Ghidra
 *   typed this function `void`, which silently drops the EAX return.
 * Confirmed: the datum_get result is NOT NULL-checked before the +0x6c load;
 *   preserved verbatim (no added guard).
 * Uncertain: the pointed-to type. The name suggests a location (likely
 *   real_point3d) but this function alone gives no typed evidence, so the
 *   return stays void *.
 *
 * MATCH-SENSITIVE SHAPE: the single-return accumulator form below (result
 * pre-set to NULL, assigned only on the hit path) is what reproduces the
 * original's hoisted XOR EDX,EDX / CMP 7 / JZ hit / CMP 5 / JNZ miss layout
 * with MOV EAX,EDX on the out-of-line miss epilogue. Both equivalent
 * early-return forms (`if (mode != 7 && mode != 5) return NULL;` and the
 * ternary) instead compile to XOR EAX,EAX with the null path as fallthrough
 * — verified 76.9% vs 100% under VC71. Do not "simplify" to an early return. */
void *actor_get_pursuit_location(int actor_handle)
{
  char *actor;
  int16_t mode;
  char *result;

  actor = (char *)datum_get(actor_data, actor_handle);
  result = NULL;
  mode = *(int16_t *)(actor + 0x6c);
  if (mode == 7 || mode == 5) {
    result = actor + 0xa4;
  }
  return result;
}

/* actor_action_handle_vehicle_entry (0x1dfa0) — XBE naked draft (batch 230). */
#if defined(__clang__)
static void *(*const b1dfa0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1dfa0_tag)(int, int) = tag_get;
static int (*const b1dfa0_gtime)(void) = game_time_get;
static void (*const b1dfa0_c64540)(int *out, int actor_handle) = FUN_00064540;
static int (*const b1dfa0_c64570)(int *iter) = FUN_00064570;
static char (*const b1dfa0_c1cb30)(int record_index, int datum_handle) = FUN_0001cb30;
static void *(*const b1dfa0_tryget)(int, int) = object_try_and_get_and_verify_type;
static vector3_t * (*const b1dfa0_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static float (*const b1dfa0_c121a0)(const float *a, const float *b) = distance_squared3d;
static char (*const b1dfa0_c1bcd0)(int actor_handle, int vehicle_handle, float param_3, float param_4, void *out_state) = action_vehicle_setup_impromptu;
static void (*const b1dfa0_c1d030)(int actor_handle, int new_action_type, int param_3) = actor_action_change;

__attribute__((naked, noinline))
char actor_action_handle_vehicle_entry(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xb0, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x58(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[gtime]\n\t"
      "movw 0x6c(%%edi), %%cx\n\t"
      "xorb %%dl, %%dl\n\t"
      "cmpw $4, %%cx\n\t"
      "jne .Lactor_action_handle_vehicle_entry_1\n\t"
      "cmpw $0, 0xa8(%%edi)\n\t"
      "jg .Lactor_action_handle_vehicle_entry_21\n\t"
      ".Lactor_action_handle_vehicle_entry_1:\n\t"
      "cmpw $0xb, %%cx\n\t"
      "je .Lactor_action_handle_vehicle_entry_21\n\t"
      "movl 0x384(%%edi), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lactor_action_handle_vehicle_entry_2\n\t"
      "addl $0x2d, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jge .Lactor_action_handle_vehicle_entry_21\n\t"
      ".Lactor_action_handle_vehicle_entry_2:\n\t"
      "movl %%eax, 0x384(%%edi)\n\t"
      "movl (%%esi), %%eax\n\t"
      "testb $0x10, %%ah\n\t"
      "movl $0x7f7fffff, -0x8(%%ebp)\n\t"
      "movl $0x7f7fffff, -0x10(%%ebp)\n\t"
      "movl $0x7f7fffff, -0xc(%%ebp)\n\t"
      "movl $0xffffffff, -0x4(%%ebp)\n\t"
      "je .Lactor_action_handle_vehicle_entry_6\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[c64540]\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c64570]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lactor_action_handle_vehicle_entry_6\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lactor_action_handle_vehicle_entry_3:\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .Lactor_action_handle_vehicle_entry_5\n\t"
      "cmpw $3, %%ax\n\t"
      "jg .Lactor_action_handle_vehicle_entry_5\n\t"
      "movb 0x12e(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_vehicle_entry_5\n\t"
      "movb 0x60(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_vehicle_entry_5\n\t"
      "movl 0x110(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_action_handle_vehicle_entry_5\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c1cb30]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_vehicle_entry_5\n\t"
      "movl 0x110(%%esi), %%ecx\n\t"
      "pushl $2\n\t"
      "pushl %%ecx\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lactor_action_handle_vehicle_entry_5\n\t"
      "movl 0x2d4(%%eax), %%edx\n\t"
      "cmpl 0x18(%%esi), %%edx\n\t"
      "jne .Lactor_action_handle_vehicle_entry_5\n\t"
      "movl 0x110(%%esi), %%ecx\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1412f0]\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x12c(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c121a0]\n\t"
      "fcoms 0x253f00\n\t"
      "addl $0x10, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_action_handle_vehicle_entry_4\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_action_handle_vehicle_entry_5\n\t"
      "flds 0x11c(%%esi)\n\t"
      "movl 0x110(%%esi), %%ecx\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl $0x41000000, -0x10(%%ebp)\n\t"
      "movl $0x41200000, -0xc(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".Lactor_action_handle_vehicle_entry_4:\n\t"
      "fstp %%st(0)\n\t"
      ".Lactor_action_handle_vehicle_entry_5:\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c64570]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lactor_action_handle_vehicle_entry_3\n\t"
      "cmpl $-1, -0x4(%%ebp)\n\t"
      "jne .Lactor_action_handle_vehicle_entry_19\n\t"
      ".Lactor_action_handle_vehicle_entry_6:\n\t"
      "cmpl $0x3c, 0x84(%%edi)\n\t"
      "jl .Lactor_action_handle_vehicle_entry_20\n\t"
      "movl 0x632574, %%ecx\n\t"
      "cmpw $0, 0x3b6(%%ecx)\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "jle .Lactor_action_handle_vehicle_entry_20\n\t"
      "jmp .Lactor_action_handle_vehicle_entry_7\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lactor_action_handle_vehicle_entry_7:\n\t"
      "movswl -0x18(%%ebp), %%eax\n\t"
      "leal (%%eax,%%eax,4), %%eax\n\t"
      "leal 0x3b8(%%ecx,%%eax,8), %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl $2\n\t"
      "pushl %%ecx\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lactor_action_handle_vehicle_entry_18\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c1cb30]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_vehicle_entry_18\n\t"
      "movl (%%esi), %%ecx\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1412f0]\n\t"
      "leal 0x12c(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c121a0]\n\t"
      "fsts -0x14(%%ebp)\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "addl $0x10, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_action_handle_vehicle_entry_18\n\t"
      "cmpl $0x7f7fffff, 0x4(%%esi)\n\t"
      "je .Lactor_action_handle_vehicle_entry_8\n\t"
      "flds 0x4(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_action_handle_vehicle_entry_18\n\t"
      ".Lactor_action_handle_vehicle_entry_8:\n\t"
      "movw 0x8(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lactor_action_handle_vehicle_entry_9\n\t"
      "movw 0x3e(%%edi), %%cx\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .Lactor_action_handle_vehicle_entry_18\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "testl %%edx, %%eax\n\t"
      "je .Lactor_action_handle_vehicle_entry_18\n\t"
      ".Lactor_action_handle_vehicle_entry_9:\n\t"
      "movw 0xa(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lactor_action_handle_vehicle_entry_10\n\t"
      "movb 0x4(%%edi), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "testl %%edx, %%eax\n\t"
      "je .Lactor_action_handle_vehicle_entry_18\n\t"
      ".Lactor_action_handle_vehicle_entry_10:\n\t"
      "movw 0xc(%%esi), %%bx\n\t"
      "testw %%bx, %%bx\n\t"
      "jle .Lactor_action_handle_vehicle_entry_16\n\t"
      "xorb %%al, %%al\n\t"
      "xorl %%edx, %%edx\n\t"
      "testw %%bx, %%bx\n\t"
      "jle .Lactor_action_handle_vehicle_entry_17\n\t"
      "jmp .Lactor_action_handle_vehicle_entry_11\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lactor_action_handle_vehicle_entry_11:\n\t"
      "movswl %%dx, %%ecx\n\t"
      "movl 0x10(%%esi,%%ecx,4), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "je .Lactor_action_handle_vehicle_entry_15\n\t"
      "movl 0x34(%%edi), %%eax\n\t"
      "xorl %%ecx, %%eax\n\t"
      "andl $0xffff, %%eax\n\t"
      "negl %%eax\n\t"
      "sbbb %%al, %%al\n\t"
      "incb %%al\n\t"
      "je .Lactor_action_handle_vehicle_entry_15\n\t"
      "shrl $0x1e, %%ecx\n\t"
      "decl %%ecx\n\t"
      "je .Lactor_action_handle_vehicle_entry_12\n\t"
      "decl %%ecx\n\t"
      "jne .Lactor_action_handle_vehicle_entry_14\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "shrl $0x10, %%eax\n\t"
      "movzbl %%al, %%eax\n\t"
      "cmpw %%ax, 0x3a(%%edi)\n\t"
      "jmp .Lactor_action_handle_vehicle_entry_13\n\t"
      ".Lactor_action_handle_vehicle_entry_12:\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "shrl $0x10, %%ecx\n\t"
      "movzbl %%cl, %%ecx\n\t"
      "cmpw %%cx, 0x3c(%%edi)\n\t"
      ".Lactor_action_handle_vehicle_entry_13:\n\t"
      "sete %%al\n\t"
      ".Lactor_action_handle_vehicle_entry_14:\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_vehicle_entry_16\n\t"
      ".Lactor_action_handle_vehicle_entry_15:\n\t"
      "incl %%edx\n\t"
      "cmpw %%bx, %%dx\n\t"
      "jl .Lactor_action_handle_vehicle_entry_11\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_vehicle_entry_17\n\t"
      ".Lactor_action_handle_vehicle_entry_16:\n\t"
      "flds 0x4(%%esi)\n\t"
      "movl (%%esi), %%edx\n\t"
      "fadds 0x254644\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fadds 0x254640\n\t"
      "fstps -0xc(%%ebp)\n\t"
      ".Lactor_action_handle_vehicle_entry_17:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      ".Lactor_action_handle_vehicle_entry_18:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl 0x632574, %%ecx\n\t"
      "incl %%eax\n\t"
      "cmpw 0x3b6(%%ecx), %%ax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "jl .Lactor_action_handle_vehicle_entry_7\n\t"
      "cmpl $-1, -0x4(%%ebp)\n\t"
      "je .Lactor_action_handle_vehicle_entry_20\n\t"
      ".Lactor_action_handle_vehicle_entry_19:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "leal -0xb0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1bcd0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_vehicle_entry_20\n\t"
      "leal -0xb0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $9\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d030]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_handle_vehicle_entry_20:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_handle_vehicle_entry_21:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%dl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1dfa0_dget), [tag] "m"(b1dfa0_tag), [gtime] "m"(b1dfa0_gtime), [c64540] "m"(b1dfa0_c64540), [c64570] "m"(b1dfa0_c64570), [c1cb30] "m"(b1dfa0_c1cb30), [tryget] "m"(b1dfa0_tryget), [c1412f0] "m"(b1dfa0_c1412f0), [c121a0] "m"(b1dfa0_c121a0), [c1bcd0] "m"(b1dfa0_c1bcd0), [c1d030] "m"(b1dfa0_c1d030)
      : "memory");
}
#else
#error "actor_action_handle_vehicle_entry: clang naked draft required"
#endif



/* actor_action_find_escape_from_danger (0x1e360) — XBE naked draft (batch 108). */
#if defined(__clang__)
static void *(*const b1e360_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1e360_get)(int, int) = object_get_and_verify_type;
static void *(*const b1e360_tag)(int, int) = tag_get;
static void (*const b1e360_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1e360_exitfn)(int) = system_exit;
static float (*const b1e360_mag)(float *) = magnitude3d;
static char (*const b1e360_c2a8f0)(int actor_handle, float *evasion_vector, float scale, float param_4, char *out_flag, void *result) = actor_move_try_evasion_vector;
static float (*const b1e360_c10cd40)(float *p1, float *p2, float *p3) = FUN_0010cd40;

__attribute__((naked, noinline))
void actor_action_find_escape_from_danger(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x74, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0x238(%%eax), %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "cmpw $0, 0x280(%%esi)\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jg .Lactor_action_find_escape_from_danger_1\n\t"
      "pushl $1\n\t"
      "pushl $0x571\n\t"
      "pushl $0x2544b0\n\t"
      "pushl $0x2546a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_action_find_escape_from_danger_1:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_action_find_escape_from_danger_14\n\t"
      "flds 0x2bc(%%esi)\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "fchs\n\t"
      "pushl %%edx\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x2c0(%%esi)\n\t"
      "fchs\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2546a4\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_action_find_escape_from_danger_2\n\t"
      "flds 0x2b0(%%esi)\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "fsubs 0x12c(%%esi)\n\t"
      "pushl %%eax\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x2b4(%%esi)\n\t"
      "fsubs 0x130(%%esi)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lactor_action_find_escape_from_danger_2\n\t"
      "movl 0x174(%%esi), %%ecx\n\t"
      "movl 0x178(%%esi), %%edx\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lactor_action_find_escape_from_danger_2\n\t"
      "movl 0x31fc0c, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      ".Lactor_action_find_escape_from_danger_2:\n\t"
      "movl 0x58(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testl $0x2000000, %%ecx\n\t"
      "movl $0x41000000, -0x10(%%ebp)\n\t"
      "jne .Lactor_action_find_escape_from_danger_3\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      ".Lactor_action_find_escape_from_danger_3:\n\t"
      "flds 0x2c8(%%esi)\n\t"
      "pushl %%edi\n\t"
      "fsubs 0x2b0(%%esi)\n\t"
      "leal 0x2b0(%%esi), %%edi\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "flds 0x2cc(%%esi)\n\t"
      "leal -0x74(%%ebp), %%eax\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "pushl %%eax\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "flds 0x2d0(%%esi)\n\t"
      "leal -0x7(%%ebp), %%ecx\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "flds -0x18(%%ebp)\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "fchs\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "movl $0, -0x20(%%ebp)\n\t"
      "fchs\n\t"
      "movl $0, -0x2c(%%ebp)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fadds 0x12c(%%esi)\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fadds 0x130(%%esi)\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x2533c0\n\t"
      "fld %%st(0)\n\t"
      "fadds 0x134(%%esi)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fadds 0x12c(%%esi)\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fadds 0x130(%%esi)\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "fadds 0x134(%%esi)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "call *%[c2a8f0]\n\t"
      "movb %%al, -0x6(%%ebp)\n\t"
      "leal -0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x4c(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10cd40]\n\t"
      "fsqrt\n\t"
      "movb -0x6(%%ebp), %%al\n\t"
      "addl $0x24, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "je .Lactor_action_find_escape_from_danger_4\n\t"
      "flds -0x14(%%ebp)\n\t"
      "movb $1, -0x4(%%ebp)\n\t"
      "fcomps 0x294(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_action_find_escape_from_danger_5\n\t"
      ".Lactor_action_find_escape_from_danger_4:\n\t"
      "movb $0, -0x4(%%ebp)\n\t"
      ".Lactor_action_find_escape_from_danger_5:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "leal -0x74(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "leal -0x5(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2a8f0]\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movb %%al, -0x3(%%ebp)\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c10cd40]\n\t"
      "fsqrt\n\t"
      "movb -0x3(%%ebp), %%cl\n\t"
      "addl $0x24, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "popl %%edi\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "je .Lactor_action_find_escape_from_danger_6\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x294(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_action_find_escape_from_danger_6\n\t"
      "movb $1, %%al\n\t"
      "movb %%al, -0x3(%%ebp)\n\t"
      "jmp .Lactor_action_find_escape_from_danger_7\n\t"
      ".Lactor_action_find_escape_from_danger_6:\n\t"
      "movb $0, -0x3(%%ebp)\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      ".Lactor_action_find_escape_from_danger_7:\n\t"
      "movb -0x6(%%ebp), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .Lactor_action_find_escape_from_danger_11\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lactor_action_find_escape_from_danger_10\n\t"
      "flds -0x14(%%ebp)\n\t"
      "movb -0x7(%%ebp), %%cl\n\t"
      "fsubs -0x10(%%ebp)\n\t"
      "movb -0x5(%%ebp), %%bl\n\t"
      "cmpb %%bl, %%cl\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "ja .Lactor_action_find_escape_from_danger_9\n\t"
      "movb -0x4(%%ebp), %%dl\n\t"
      "cmpb %%al, %%dl\n\t"
      "ja .Lactor_action_find_escape_from_danger_9\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fcomps 0x2533e4\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_action_find_escape_from_danger_9\n\t"
      "cmpb %%cl, %%bl\n\t"
      "ja .Lactor_action_find_escape_from_danger_8\n\t"
      "cmpb %%dl, -0x3(%%ebp)\n\t"
      "ja .Lactor_action_find_escape_from_danger_8\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fcomps 0x2546a0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lactor_action_find_escape_from_danger_8\n\t"
      "movl $4, %%ebx\n\t"
      "movb %%dl, -0x2(%%ebp)\n\t"
      "jmp .Lactor_action_find_escape_from_danger_13\n\t"
      ".Lactor_action_find_escape_from_danger_8:\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "jmp .Lactor_action_find_escape_from_danger_12\n\t"
      ".Lactor_action_find_escape_from_danger_9:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "jmp .Lactor_action_find_escape_from_danger_13\n\t"
      ".Lactor_action_find_escape_from_danger_10:\n\t"
      "movb -0x7(%%ebp), %%dl\n\t"
      "movb -0x4(%%ebp), %%al\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movb %%dl, -0x1(%%ebp)\n\t"
      "movb %%al, -0x2(%%ebp)\n\t"
      "jmp .Lactor_action_find_escape_from_danger_14\n\t"
      ".Lactor_action_find_escape_from_danger_11:\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lactor_action_find_escape_from_danger_14\n\t"
      "movb %%al, -0x2(%%ebp)\n\t"
      ".Lactor_action_find_escape_from_danger_12:\n\t"
      "movb -0x5(%%ebp), %%cl\n\t"
      "movl $1, %%ebx\n\t"
      ".Lactor_action_find_escape_from_danger_13:\n\t"
      "movb %%cl, -0x1(%%ebp)\n\t"
      ".Lactor_action_find_escape_from_danger_14:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lactor_action_find_escape_from_danger_15\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lactor_action_find_escape_from_danger_15\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lactor_action_find_escape_from_danger_16\n\t"
      ".Lactor_action_find_escape_from_danger_15:\n\t"
      "pushl $1\n\t"
      "pushl $0x5cc\n\t"
      "pushl $0x2544b0\n\t"
      "pushl $0x254648\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_action_find_escape_from_danger_16:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movw %%bx, (%%esi)\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "movb %%cl, (%%edx)\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "popl %%esi\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1e360_dget), [get] "m"(b1e360_get), [tag] "m"(b1e360_tag), [assert] "m"(b1e360_assert), [exitfn] "m"(b1e360_exitfn), [mag] "m"(b1e360_mag), [c2a8f0] "m"(b1e360_c2a8f0), [c10cd40] "m"(b1e360_c10cd40)
      : "memory");
}
#else
#error "actor_action_find_escape_from_danger: clang naked draft required"
#endif


/* actor_action_handle_combat_selection (0x1e8a0) — XBE naked draft (batch 105). */
#if defined(__clang__)
static void *(*const b1e8a0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1e8a0_tag)(int, int) = tag_get;
static char * (*const b1e8a0_c211f0)(int actor_handle) = actor_combat_get_firing_variant_definition;
static void (*const b1e8a0_ftol)(void) = FUN_001d9068;
static char (*const b1e8a0_c1d350)(int actor_handle, char param_2, char param_3) = actor_action_try_to_seek_cover;
static void (*const b1e8a0_c31440)(int actor_handle, int berserk_flag) = actor_berserk;
static bool (*const b1e8a0_c3b320)(int actor_handle) = actor_has_ranged_weapon;
static void *(*const b1e8a0_get)(int, int) = object_get_and_verify_type;
static int (*const b1e8a0_gtime)(void) = game_time_get;
static float (*const b1e8a0_cb5590)(int16_t value_type) = FUN_000b5590;
static char (*const b1e8a0_c13ef0)(int actor_handle, int action_type, void *charge_state) = FUN_00013ef0;
static void (*const b1e8a0_c1d030)(int actor_handle, int new_action_type, int param_3) = actor_action_change;
static float (*const b1e8a0_c13070)(float *a, float *b) = FUN_00013070;
static char (*const b1e8a0_c14620)(int actor_handle, void *state_data) = FUN_00014620;
static void (*const b1e8a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1e8a0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
char actor_action_handle_combat_selection(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xa4, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x58(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movl 0x5c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl $0x61637476\n\t"
      "movl %%ebx, -0x1c(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "call *%[c211f0]\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl 0x270(%%esi), %%eax\n\t"
      "addl $0x1c, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "movl $0x7f7fffff, -0x8(%%ebp)\n\t"
      "je .Lactor_action_handle_combat_selection_21\n\t"
      "pushl %%eax\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x11c(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0xa, 0x6c(%%esi)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jne .Lactor_action_handle_combat_selection_4\n\t"
      "cmpw $1, 0xa0(%%esi)\n\t"
      "jne .Lactor_action_handle_combat_selection_4\n\t"
      "movb 0x74(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lactor_action_handle_combat_selection_2\n\t"
      "movb 0x12f(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lactor_action_handle_combat_selection_1\n\t"
      "cmpb $1, 0x121(%%eax)\n\t"
      "jle .Lactor_action_handle_combat_selection_2\n\t"
      ".Lactor_action_handle_combat_selection_1:\n\t"
      "flds 0x328(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_action_handle_combat_selection_4\n\t"
      "flds 0x328(%%ebx)\n\t"
      "fmuls 0x253394\n\t"
      "call *%[ftol]\n\t"
      "cmpw %%ax, 0xc2(%%esi)\n\t"
      "jl .Lactor_action_handle_combat_selection_4\n\t"
      ".Lactor_action_handle_combat_selection_2:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "fcomps 0xa0(%%edx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_action_handle_combat_selection_3\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d350]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movb %%al, -0x2(%%ebp)\n\t"
      "jne .Lactor_action_handle_combat_selection_4\n\t"
      ".Lactor_action_handle_combat_selection_3:\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[c31440]\n\t"
      "addl $8, %%esp\n\t"
      ".Lactor_action_handle_combat_selection_4:\n\t"
      "pushl %%edi\n\t"
      "call *%[c3b320]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_combat_selection_5\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "cmpl $-1, 0x110(%%eax)\n\t"
      "jne .Lactor_action_handle_combat_selection_18\n\t"
      "movl %%eax, %%ecx\n\t"
      "movb 0x14(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_combat_selection_18\n\t"
      ".Lactor_action_handle_combat_selection_5:\n\t"
      "cmpw $0xa, 0x6c(%%esi)\n\t"
      "jne .Lactor_action_handle_combat_selection_6\n\t"
      "movw 0xa0(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "je .Lactor_action_handle_combat_selection_18\n\t"
      "cmpw $3, %%ax\n\t"
      "je .Lactor_action_handle_combat_selection_18\n\t"
      ".Lactor_action_handle_combat_selection_6:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_combat_selection_18\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_combat_selection_18\n\t"
      "cmpl $-1, 0x158(%%esi)\n\t"
      "jne .Lactor_action_handle_combat_selection_18\n\t"
      "cmpw $2, 0x5f2(%%esi)\n\t"
      "je .Lactor_action_handle_combat_selection_18\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "call *%[gtime]\n\t"
      "movb 0x378(%%esi), %%bl\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, -0x18(%%ebp)\n\t"
      "call *%[c3b320]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_combat_selection_7\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "testl $0x20000, (%%ecx)\n\t"
      "jne .Lactor_action_handle_combat_selection_7\n\t"
      "movb $1, %%bl\n\t"
      ".Lactor_action_handle_combat_selection_7:\n\t"
      "movb 0x378(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_combat_selection_8\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jmp .Lactor_action_handle_combat_selection_9\n\t"
      ".Lactor_action_handle_combat_selection_8:\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl 0x378(%%edx), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      ".Lactor_action_handle_combat_selection_9:\n\t"
      "pushl $0x15\n\t"
      "call *%[cb5590]\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "pushl $0x14\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "call *%[cb5590]\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "je .Lactor_action_handle_combat_selection_10\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "flds 0x170(%%ecx)\n\t"
      "jmp .Lactor_action_handle_combat_selection_11\n\t"
      ".Lactor_action_handle_combat_selection_10:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "flds 0x160(%%edx)\n\t"
      ".Lactor_action_handle_combat_selection_11:\n\t"
      "movl 0x37c(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_action_handle_combat_selection_12\n\t"
      "addl $0xa, %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jge .Lactor_action_handle_combat_selection_17\n\t"
      ".Lactor_action_handle_combat_selection_12:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_action_handle_combat_selection_18\n\t"
      "movb 0x1cb(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_combat_selection_15\n\t"
      "flds 0x2533c0\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "fcomps 0x37c(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_action_handle_combat_selection_13\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lactor_action_handle_combat_selection_14\n\t"
      ".Lactor_action_handle_combat_selection_13:\n\t"
      "flds 0x37c(%%ecx)\n\t"
      ".Lactor_action_handle_combat_selection_14:\n\t"
      "flds 0x2533f0\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_action_handle_combat_selection_18\n\t"
      ".Lactor_action_handle_combat_selection_15:\n\t"
      "movl 0x380(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "je .Lactor_action_handle_combat_selection_16\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x253394\n\t"
      "fiaddl -0x10(%%ebp)\n\t"
      "fildl -0x18(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lactor_action_handle_combat_selection_18\n\t"
      ".Lactor_action_handle_combat_selection_16:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c3b320]\n\t"
      "leal -0xa4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $2\n\t"
      "pushl %%ebx\n\t"
      "movl %%edi, 0x37c(%%esi)\n\t"
      "call *%[c13ef0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_combat_selection_18\n\t"
      "leal -0xa4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xa\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d030]\n\t"
      "addl $0xc, %%esp\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "jmp .Lactor_action_handle_combat_selection_18\n\t"
      ".Lactor_action_handle_combat_selection_17:\n\t"
      "fstp %%st(0)\n\t"
      ".Lactor_action_handle_combat_selection_18:\n\t"
      "cmpw $0xa, 0x6c(%%esi)\n\t"
      "je .Lactor_action_handle_combat_selection_20\n\t"
      "movb 0x1cb(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_combat_selection_20\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_combat_selection_46\n\t"
      "cmpw $0, 0x15e(%%esi)\n\t"
      "jle .Lactor_action_handle_combat_selection_21\n\t"
      "movl 0x158(%%esi), %%edx\n\t"
      "pushl $2\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x76656869\n\t"
      "call *%[tag]\n\t"
      "movl 0x388(%%esi), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "je .Lactor_action_handle_combat_selection_19\n\t"
      "flds 0x390(%%eax)\n\t"
      "fmuls 0x253394\n\t"
      "fiaddl -0x18(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "fildl -0x18(%%ebp)\n\t"
      "fcomps -0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_action_handle_combat_selection_21\n\t"
      ".Lactor_action_handle_combat_selection_19:\n\t"
      "cmpw $4, 0x15e(%%esi)\n\t"
      "jne .Lactor_action_handle_combat_selection_21\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "fcomps 0x160(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_action_handle_combat_selection_21\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "cmpw $0, 0x38(%%edx)\n\t"
      "jne .Lactor_action_handle_combat_selection_21\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0xa4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $4\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13ef0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_combat_selection_21\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal -0xa4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0xa\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d030]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_handle_combat_selection_20:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_combat_selection_46\n\t"
      ".Lactor_action_handle_combat_selection_21:\n\t"
      "movb 0x375(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_combat_selection_22\n\t"
      "movb 0x1cb(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "je .Lactor_action_handle_combat_selection_23\n\t"
      ".Lactor_action_handle_combat_selection_22:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".Lactor_action_handle_combat_selection_23:\n\t"
      "movb 0x1cb(%%esi), %%al\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "xorb %%bl, %%bl\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_combat_selection_24\n\t"
      "pushl %%edi\n\t"
      "call *%[c3b320]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_combat_selection_24\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "testl $0x1000000, (%%ecx)\n\t"
      "je .Lactor_action_handle_combat_selection_24\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".Lactor_action_handle_combat_selection_24:\n\t"
      "cmpw $0xa, 0x6c(%%esi)\n\t"
      "jne .Lactor_action_handle_combat_selection_32\n\t"
      "movw 0xa0(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "je .Lactor_action_handle_combat_selection_30\n\t"
      "cmpw $3, %%ax\n\t"
      "je .Lactor_action_handle_combat_selection_30\n\t"
      "movb 0x1cb(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lactor_action_handle_combat_selection_25\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jmp .Lactor_action_handle_combat_selection_36\n\t"
      ".Lactor_action_handle_combat_selection_25:\n\t"
      "cmpw $4, %%ax\n\t"
      "je .Lactor_action_handle_combat_selection_26\n\t"
      "cmpw $5, %%ax\n\t"
      "jne .Lactor_action_handle_combat_selection_32\n\t"
      ".Lactor_action_handle_combat_selection_26:\n\t"
      "movb 0xc5(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lactor_action_handle_combat_selection_31\n\t"
      "cmpw $1, 0x15e(%%esi)\n\t"
      "jle .Lactor_action_handle_combat_selection_31\n\t"
      "cmpw $4, %%ax\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jne .Lactor_action_handle_combat_selection_33\n\t"
      "movl 0x158(%%esi), %%edx\n\t"
      "pushl $2\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x76656869\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movb 0x484(%%esi), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_combat_selection_27\n\t"
      "cmpw $5, 0x46c(%%esi)\n\t"
      "jne .Lactor_action_handle_combat_selection_27\n\t"
      "movl 0x470(%%esi), %%edx\n\t"
      "cmpl 0x270(%%esi), %%edx\n\t"
      "jne .Lactor_action_handle_combat_selection_27\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jmp .Lactor_action_handle_combat_selection_36\n\t"
      ".Lactor_action_handle_combat_selection_27:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x394(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_action_handle_combat_selection_28\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jmp .Lactor_action_handle_combat_selection_36\n\t"
      ".Lactor_action_handle_combat_selection_28:\n\t"
      "flds 0x394(%%ecx)\n\t"
      ".byte 0xdc, 0xc0\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_action_handle_combat_selection_33\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "addl $0xe0, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x174(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13070]\n\t"
      "fcomps 0x253398\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_action_handle_combat_selection_33\n\t"
      ".Lactor_action_handle_combat_selection_29:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jmp .Lactor_action_handle_combat_selection_36\n\t"
      ".Lactor_action_handle_combat_selection_30:\n\t"
      "movb 0xa3(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_combat_selection_31\n\t"
      "movb 0xa4(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_combat_selection_31\n\t"
      "movb 0xc5(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_combat_selection_31\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lactor_action_handle_combat_selection_33\n\t"
      ".Lactor_action_handle_combat_selection_31:\n\t"
      "movb $1, %%bl\n\t"
      ".Lactor_action_handle_combat_selection_32:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_combat_selection_36\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lactor_action_handle_combat_selection_34\n\t"
      ".Lactor_action_handle_combat_selection_33:\n\t"
      "cmpw $0xa, 0x6c(%%esi)\n\t"
      "je .Lactor_action_handle_combat_selection_35\n\t"
      ".Lactor_action_handle_combat_selection_34:\n\t"
      "leal -0xa4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c13ef0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_combat_selection_29\n\t"
      "leal -0xa4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0xa\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d030]\n\t"
      "addl $0xc, %%esp\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      ".Lactor_action_handle_combat_selection_35:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "jne .Lactor_action_handle_combat_selection_38\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_combat_selection_46\n\t"
      ".Lactor_action_handle_combat_selection_36:\n\t"
      "cmpw $3, 0x6c(%%esi)\n\t"
      "je .Lactor_action_handle_combat_selection_39\n\t"
      "leal -0xa4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c14620]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_combat_selection_37\n\t"
      "pushl $1\n\t"
      "pushl $0x87b\n\t"
      "pushl $0x2544b0\n\t"
      "pushl $0x254818\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_action_handle_combat_selection_37:\n\t"
      "leal -0xa4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d030]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_handle_combat_selection_38:\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_combat_selection_46\n\t"
      ".Lactor_action_handle_combat_selection_39:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_combat_selection_44\n\t"
      "cmpw $0xa, 0x6c(%%esi)\n\t"
      "je .Lactor_action_handle_combat_selection_40\n\t"
      "pushl $1\n\t"
      "pushl $0x886\n\t"
      "pushl $0x2544b0\n\t"
      "pushl $0x2547ec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_action_handle_combat_selection_40:\n\t"
      "movw 0xa0(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "je .Lactor_action_handle_combat_selection_42\n\t"
      "cmpw $3, %%ax\n\t"
      "je .Lactor_action_handle_combat_selection_42\n\t"
      "cmpw $4, %%ax\n\t"
      "je .Lactor_action_handle_combat_selection_41\n\t"
      "cmpw $5, %%ax\n\t"
      "jne .Lactor_action_handle_combat_selection_46\n\t"
      ".Lactor_action_handle_combat_selection_41:\n\t"
      "movb 0xc5(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_combat_selection_46\n\t"
      "pushl $1\n\t"
      "pushl $0x88d\n\t"
      "pushl $0x2544b0\n\t"
      "pushl $0x2547b8\n\t"
      "jmp .Lactor_action_handle_combat_selection_45\n\t"
      ".Lactor_action_handle_combat_selection_42:\n\t"
      "movb 0xa3(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_combat_selection_43\n\t"
      "movb 0xa4(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_combat_selection_43\n\t"
      "movb 0xc5(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_combat_selection_46\n\t"
      ".Lactor_action_handle_combat_selection_43:\n\t"
      "pushl $1\n\t"
      "pushl $0x889\n\t"
      "pushl $0x2544b0\n\t"
      "pushl $0x254710\n\t"
      "jmp .Lactor_action_handle_combat_selection_45\n\t"
      ".Lactor_action_handle_combat_selection_44:\n\t"
      "cmpw $3, 0x6c(%%esi)\n\t"
      "je .Lactor_action_handle_combat_selection_46\n\t"
      "pushl $1\n\t"
      "pushl $0x892\n\t"
      "pushl $0x2544b0\n\t"
      "pushl $0x2546e4\n\t"
      ".Lactor_action_handle_combat_selection_45:\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_action_handle_combat_selection_46:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1e8a0_dget), [tag] "m"(b1e8a0_tag), [c211f0] "m"(b1e8a0_c211f0), [ftol] "m"(b1e8a0_ftol), [c1d350] "m"(b1e8a0_c1d350), [c31440] "m"(b1e8a0_c31440), [c3b320] "m"(b1e8a0_c3b320), [get] "m"(b1e8a0_get), [gtime] "m"(b1e8a0_gtime), [cb5590] "m"(b1e8a0_cb5590), [c13ef0] "m"(b1e8a0_c13ef0), [c1d030] "m"(b1e8a0_c1d030), [c13070] "m"(b1e8a0_c13070), [c14620] "m"(b1e8a0_c14620), [assert] "m"(b1e8a0_assert), [exitfn] "m"(b1e8a0_exitfn)
      : "memory");
}
#else
#error "actor_action_handle_combat_selection: clang naked draft required"
#endif


/* actor_action_handle_lost_contact (0x1ef90) — XBE naked draft (batch 105). */
#if defined(__clang__)
static void (*const b1ef90_chkstk)(void) = FUN_001d90e0;
static void *(*const b1ef90_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1ef90_tag)(int, int) = tag_get;
static int16_t (*const b1ef90_c1d6d0)(int actor_handle) = actor_action_try_to_panic;
static int16_t (*const b1ef90_c3a790)(int16_t actor_type) = FUN_0003a790;
static int16_t (*const b1ef90_c3a7b0)(int16_t actor_type) = FUN_0003a7b0;
static int16_t (*const b1ef90_c3a7d0)(int16_t actor_type) = FUN_0003a7d0;
static unsigned char (*const b1ef90_c3a7f0)(int16_t actor_type) = FUN_0003a7f0;
static void (*const b1ef90_c59d30)(int encounter_handle, int16_t profile_index, char *flag, int16_t *a, char *e, int16_t *b, int16_t *c, int16_t *d) = encounter_modify_pursuit_desires;
static void (*const b1ef90_c59dd0)(int encounter_handle, int actor_handle, int16_t *mode, char flag, char *out_guard, char *out_active, char *out_limit_a, char *out_limit_b, char *out_nearby, char *out_has_target, char *out_summary) = encounter_determine_pursuit_availability;
static void (*const b1ef90_c1cda0)(void) = FUN_0001cda0;
static int (*const b1ef90_c1a080)(int actor_handle, char param_2, char *state_data) = FUN_0001a080;
static void (*const b1ef90_c1d030)(int actor_handle, int new_action_type, int param_3) = actor_action_change;
static void (*const b1ef90_c32b50)(int actor_handle, int prop_handle) = actor_perception_tried_to_uncover;
static int (*const b1ef90_c19750)(int actor_handle, char param_2, char *state_data) = FUN_00019750;
static void (*const b1ef90_c32bb0)(int actor_handle, int prop_handle) = actor_perception_tried_to_search;
static int (*const b1ef90_c3b380)(int actor_handle) = actor_target_unit_index;
static void (*const b1ef90_c46f10)(int16_t type, int unit_handle, int param3, int param4, int16_t param5, int16_t param6, int16_t param7) = FUN_00046f10;
static int (*const b1ef90_c198d0)(int actor_handle, int param_2, char *state_data) = FUN_000198d0;
static void *(*const b1ef90_memset)(void *, int, unsigned int) = csmemset;
static int (*const b1ef90_c24a60)(int actor_handle, short param_2, int param_3) = actor_get_firing_position_group;
static short (*const b1ef90_c25c10)(int actor_handle, void *eval_ctx, int *out_record, int *out_owner, void *huge_buf, int *out_found) = FUN_00025c10;
static int (*const b1ef90_c1a100)(int actor_handle, short param_2, char *state_data) = FUN_0001a100;
static int (*const b1ef90_c197d0)(int actor_handle, short param_2, char param_3, char *state_data) = FUN_000197d0;
static char (*const b1ef90_c5b5e0)(int encounter_handle, int position_hash, int16_t pursuit_index, int min_time) = encounter_mark_examined_pursuit_position;
static char (*const b1ef90_c1c0e0)(int actor_handle, char param_2, int state_data) = FUN_0001c0e0;
static char (*const b1ef90_c159d0)(int actor_handle, short *state_data) = FUN_000159d0;
static void (*const b1ef90_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1ef90_exitfn)(int) = system_exit;
static char (*const b1ef90_c1d7c0)(int actor_handle, short state) = actor_action_set_default_state;
static void (*const b1ef90_c32c10)(int actor_handle, int prop_handle) = actor_perception_abandoned_search;
static int (*const b1ef90_c15900)(int actor_handle, short param_2, char *state_data) = FUN_00015900;

__attribute__((naked, noinline))
char actor_action_handle_lost_contact(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x147f4, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x58(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lactor_action_handle_lost_contact_1\n\t"
      "xorl %%edi, %%edi\n\t"
      "jmp .Lactor_action_handle_lost_contact_2\n\t"
      ".Lactor_action_handle_lost_contact_1:\n\t"
      "movl 0x5ab270, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      ".Lactor_action_handle_lost_contact_2:\n\t"
      "xorb %%al, %%al\n\t"
      "testl %%edi, %%edi\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "movb %%al, -0x4(%%ebp)\n\t"
      "movl $2, %%ecx\n\t"
      "je .Lactor_action_handle_lost_contact_3\n\t"
      "movb 0x42(%%edi), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .Lactor_action_handle_lost_contact_3\n\t"
      "cmpw %%cx, 0x6e(%%esi)\n\t"
      "jg .Lactor_action_handle_lost_contact_3\n\t"
      "cmpw $0, 0x72(%%esi)\n\t"
      "jne .Lactor_action_handle_lost_contact_3\n\t"
      "cmpw $0, 0x74(%%esi)\n\t"
      "jne .Lactor_action_handle_lost_contact_3\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      ".Lactor_action_handle_lost_contact_3:\n\t"
      "cmpw $0, 0x1e4(%%esi)\n\t"
      "jle .Lactor_action_handle_lost_contact_4\n\t"
      "cmpw %%cx, 0x6e(%%esi)\n\t"
      "jg .Lactor_action_handle_lost_contact_4\n\t"
      "cmpw $0, 0x74(%%esi)\n\t"
      "jne .Lactor_action_handle_lost_contact_4\n\t"
      "movb $1, %%al\n\t"
      "movb %%al, -0x4(%%ebp)\n\t"
      ".Lactor_action_handle_lost_contact_4:\n\t"
      "cmpw $3, 0x6a(%%esi)\n\t"
      "jge .Lactor_action_handle_lost_contact_5\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d6d0]\n\t"
      "addl $4, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Lactor_action_handle_lost_contact_42\n\t"
      "movb -0x4(%%ebp), %%al\n\t"
      ".Lactor_action_handle_lost_contact_5:\n\t"
      "movb 0x160(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lactor_action_handle_lost_contact_32\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_lost_contact_33\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_lost_contact_36\n\t"
      "cmpw $2, 0x6e(%%esi)\n\t"
      "jl .Lactor_action_handle_lost_contact_38\n\t"
      "movl 0x270(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lactor_action_handle_lost_contact_6\n\t"
      "xorl %%edi, %%edi\n\t"
      "jmp .Lactor_action_handle_lost_contact_7\n\t"
      ".Lactor_action_handle_lost_contact_6:\n\t"
      "pushl %%eax\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      ".Lactor_action_handle_lost_contact_7:\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%edi, -0x18(%%ebp)\n\t"
      "movb $0, -0x12(%%ebp)\n\t"
      "movb $0, -0x6(%%ebp)\n\t"
      "movb $0, -0x4(%%ebp)\n\t"
      "movb $0, -0xa(%%ebp)\n\t"
      "movb $0, -0xe(%%ebp)\n\t"
      "movb $0, -0x3(%%ebp)\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "je .Lactor_action_handle_lost_contact_8\n\t"
      "movb 0xbb(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_lost_contact_12\n\t"
      ".Lactor_action_handle_lost_contact_8:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c3a790]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%esi), %%dx\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "call *%[c3a7b0]\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c3a7d0]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c3a7f0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "movb %%al, -0x38(%%ebp)\n\t"
      "movl $0, -0x28(%%ebp)\n\t"
      "movb $0, -0x5(%%ebp)\n\t"
      "movb $0, -0x2c(%%ebp)\n\t"
      "je .Lactor_action_handle_lost_contact_9\n\t"
      "movb $1, -0x4(%%ebp)\n\t"
      "movb $1, -0x6(%%ebp)\n\t"
      ".Lactor_action_handle_lost_contact_9:\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movb $1, -0xe(%%ebp)\n\t"
      "movb $1, -0xa(%%ebp)\n\t"
      "movb $1, -0x3(%%ebp)\n\t"
      "je .Lactor_action_handle_lost_contact_11\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x3a(%%esi), %%dx\n\t"
      "leal -0x12(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c59d30]\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_lost_contact_10\n\t"
      "movb $1, -0xa(%%ebp)\n\t"
      "movb $1, -0x4(%%ebp)\n\t"
      "movb $1, -0x6(%%ebp)\n\t"
      "movb $1, -0x3(%%ebp)\n\t"
      "movb $1, -0xe(%%ebp)\n\t"
      "jmp .Lactor_action_handle_lost_contact_11\n\t"
      ".Lactor_action_handle_lost_contact_10:\n\t"
      "leal -0x2(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x5(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x3(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xe(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xa(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0x38(%%ebp), %%edx\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "leal -0x6(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x34(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59dd0]\n\t"
      "addl $0x30, %%esp\n\t"
      ".Lactor_action_handle_lost_contact_11:\n\t"
      "leal -0x2(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x3(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xe(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xa(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0x375(%%esi), %%dl\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "leal -0x6(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x34(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movb -0x5(%%ebp), %%al\n\t"
      "pushl %%ecx\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1cda0]\n\t"
      "addl $0x2c, %%esp\n\t"
      ".Lactor_action_handle_lost_contact_12:\n\t"
      "movl 0x270(%%esi), %%eax\n\t"
      "cmpl %%eax, 0x3c0(%%esi)\n\t"
      "je .Lactor_action_handle_lost_contact_13\n\t"
      "movw $0, 0x3c4(%%esi)\n\t"
      "movl %%eax, 0x3c0(%%esi)\n\t"
      "movb $0, 0x3bc(%%esi)\n\t"
      "movb $0, 0x3bd(%%esi)\n\t"
      ".Lactor_action_handle_lost_contact_13:\n\t"
      "movb -0x6(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_lost_contact_14\n\t"
      "movl -0xa(%%ebp), %%eax\n\t"
      "leal -0xbc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1a080]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_lost_contact_14\n\t"
      "leal -0xbc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $5\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d030]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_handle_lost_contact_14:\n\t"
      "movl 0x270(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c32b50]\n\t"
      "movb -0xa(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_lost_contact_15\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x375(%%esi), %%cl\n\t"
      "leal -0xbc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c19750]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_lost_contact_15\n\t"
      "leal -0xbc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $7\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d030]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_handle_lost_contact_15:\n\t"
      "movl 0x270(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c32bb0]\n\t"
      "movb 0x3bc(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_lost_contact_16\n\t"
      "movb 0x3bd(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_lost_contact_16\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[c3b380]\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xd\n\t"
      "call *%[c46f10]\n\t"
      "addl $0x1c, %%esp\n\t"
      "movb $1, 0x3bd(%%esi)\n\t"
      ".Lactor_action_handle_lost_contact_16:\n\t"
      "movb -0xe(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_lost_contact_30\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "testb %%al, %%al\n\t"
      "movb $0, -0x5(%%ebp)\n\t"
      "movb $1, 0x98(%%esi)\n\t"
      "je .Lactor_action_handle_lost_contact_17\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_lost_contact_30\n\t"
      "movl -0x12(%%ebp), %%eax\n\t"
      "leal -0xbc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c198d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Lactor_action_handle_lost_contact_25\n\t"
      ".Lactor_action_handle_lost_contact_17:\n\t"
      "cmpw $5, 0x6c(%%esi)\n\t"
      "jne .Lactor_action_handle_lost_contact_18\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_lost_contact_18\n\t"
      "cmpw $1, 0xa4(%%esi)\n\t"
      "jne .Lactor_action_handle_lost_contact_18\n\t"
      "movw 0xa6(%%esi), %%di\n\t"
      "cmpw $-1, %%di\n\t"
      "movb $1, -0x5(%%ebp)\n\t"
      "jne .Lactor_action_handle_lost_contact_24\n\t"
      ".Lactor_action_handle_lost_contact_18:\n\t"
      "cmpl $-1, 0x1d0(%%esi)\n\t"
      "jne .Lactor_action_handle_lost_contact_19\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movw 0x356(%%edx), %%ax\n\t"
      "jmp .Lactor_action_handle_lost_contact_20\n\t"
      ".Lactor_action_handle_lost_contact_19:\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movw 0x354(%%eax), %%ax\n\t"
      ".Lactor_action_handle_lost_contact_20:\n\t"
      "movb -0x12(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lactor_action_handle_lost_contact_21\n\t"
      "movl 0x3c0(%%esi), %%ecx\n\t"
      "cmpl 0x270(%%esi), %%ecx\n\t"
      "jne .Lactor_action_handle_lost_contact_21\n\t"
      "cmpw %%ax, 0x3c4(%%esi)\n\t"
      "jge .Lactor_action_handle_lost_contact_30\n\t"
      ".Lactor_action_handle_lost_contact_21:\n\t"
      "pushl $0x670\n\t"
      "leal -0x768(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl 0x270(%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movw $5, -0x764(%%ebp)\n\t"
      "movl %%eax, -0x760(%%ebp)\n\t"
      "jne .Lactor_action_handle_lost_contact_22\n\t"
      "movl $0xffffffff, -0x75c(%%ebp)\n\t"
      "jmp .Lactor_action_handle_lost_contact_23\n\t"
      ".Lactor_action_handle_lost_contact_22:\n\t"
      "movl 0x7c(%%ecx), %%ecx\n\t"
      "movl %%ecx, -0x75c(%%ebp)\n\t"
      ".Lactor_action_handle_lost_contact_23:\n\t"
      "movb -0x12(%%ebp), %%dl\n\t"
      "pushl $0\n\t"
      "cmpl $-1, %%eax\n\t"
      "setne %%al\n\t"
      "pushl $5\n\t"
      "pushl %%ebx\n\t"
      "movb %%dl, -0x758(%%ebp)\n\t"
      "movb %%al, -0x725(%%ebp)\n\t"
      "call *%[c24a60]\n\t"
      "leal -0x1d(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x147f4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x768(%%ebp)\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xf8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x768(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl $0x41a00000, -0x74c(%%ebp)\n\t"
      "call *%[c25c10]\n\t"
      "addl $0x24, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      "cmpw $-1, %%di\n\t"
      "je .Lactor_action_handle_lost_contact_30\n\t"
      "movb -0x5(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_lost_contact_24\n\t"
      "leal -0xbc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1a100]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_lost_contact_24\n\t"
      "leal -0xbc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $5\n\t"
      "jmp .Lactor_action_handle_lost_contact_26\n\t"
      ".Lactor_action_handle_lost_contact_24:\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_lost_contact_30\n\t"
      "movl -0x12(%%ebp), %%eax\n\t"
      "leal -0xbc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c197d0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lactor_action_handle_lost_contact_25:\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_lost_contact_30\n\t"
      "leal -0xbc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $7\n\t"
      ".Lactor_action_handle_lost_contact_26:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d030]\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jne .Lactor_action_handle_lost_contact_27\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "jmp .Lactor_action_handle_lost_contact_28\n\t"
      ".Lactor_action_handle_lost_contact_27:\n\t"
      "movl 0x7c(%%eax), %%ecx\n\t"
      ".Lactor_action_handle_lost_contact_28:\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_action_handle_lost_contact_44\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c5b5e0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_lost_contact_44\n\t"
      "cmpw $0, 0x3c4(%%esi)\n\t"
      "jne .Lactor_action_handle_lost_contact_29\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "pushl $0x10\n\t"
      "call *%[c46f10]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".Lactor_action_handle_lost_contact_29:\n\t"
      "incw 0x3c4(%%esi)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_handle_lost_contact_30:\n\t"
      "cmpw $0, 0x3c4(%%esi)\n\t"
      "jle .Lactor_action_handle_lost_contact_31\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_action_handle_lost_contact_31\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "pushl $0x13\n\t"
      "call *%[c46f10]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".Lactor_action_handle_lost_contact_31:\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_lost_contact_38\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_lost_contact_38\n\t"
      "movl -0xe(%%ebp), %%ecx\n\t"
      "leal -0xbc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1c0e0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_lost_contact_38\n\t"
      "leal -0xbc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $8\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d030]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_handle_lost_contact_32:\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_lost_contact_35\n\t"
      ".Lactor_action_handle_lost_contact_33:\n\t"
      "cmpw $6, 0x6c(%%esi)\n\t"
      "jne .Lactor_action_handle_lost_contact_34\n\t"
      "movb 0xa1(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_lost_contact_42\n\t"
      ".Lactor_action_handle_lost_contact_34:\n\t"
      "leal -0xbc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c159d0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_lost_contact_41\n\t"
      ".Lactor_action_handle_lost_contact_35:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_lost_contact_38\n\t"
      ".Lactor_action_handle_lost_contact_36:\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lactor_action_handle_lost_contact_37\n\t"
      "pushl $1\n\t"
      "pushl $0xa45\n\t"
      "pushl $0x2544b0\n\t"
      "pushl $0x254868\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_action_handle_lost_contact_37:\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d7c0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "jne .Lactor_action_handle_lost_contact_44\n\t"
      ".Lactor_action_handle_lost_contact_38:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d6d0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $1, %%ax\n\t"
      "je .Lactor_action_handle_lost_contact_43\n\t"
      "movw 0x6c(%%esi), %%ax\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpw $7, %%ax\n\t"
      "jne .Lactor_action_handle_lost_contact_39\n\t"
      "movb 0x9d(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lactor_action_handle_lost_contact_40\n\t"
      ".Lactor_action_handle_lost_contact_39:\n\t"
      "cmpw $8, %%ax\n\t"
      "je .Lactor_action_handle_lost_contact_40\n\t"
      "movl $0x5a, %%edi\n\t"
      ".Lactor_action_handle_lost_contact_40:\n\t"
      "movl 0x270(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c32c10]\n\t"
      "leal -0xbc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c15900]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_lost_contact_41\n\t"
      "pushl $1\n\t"
      "pushl $0xa62\n\t"
      "pushl $0x2544b0\n\t"
      "pushl $0x254818\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_action_handle_lost_contact_41:\n\t"
      "leal -0xbc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $6\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d030]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lactor_action_handle_lost_contact_42:\n\t"
      "popl %%edi\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_handle_lost_contact_43:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d6d0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $1, %%ax\n\t"
      "je .Lactor_action_handle_lost_contact_44\n\t"
      "pushl $1\n\t"
      "pushl $0xa67\n\t"
      "pushl $0x2544b0\n\t"
      "pushl $0x254820\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_action_handle_lost_contact_44:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(b1ef90_chkstk), [dget] "m"(b1ef90_dget), [tag] "m"(b1ef90_tag), [c1d6d0] "m"(b1ef90_c1d6d0), [c3a790] "m"(b1ef90_c3a790), [c3a7b0] "m"(b1ef90_c3a7b0), [c3a7d0] "m"(b1ef90_c3a7d0), [c3a7f0] "m"(b1ef90_c3a7f0), [c59d30] "m"(b1ef90_c59d30), [c59dd0] "m"(b1ef90_c59dd0), [c1cda0] "m"(b1ef90_c1cda0), [c1a080] "m"(b1ef90_c1a080), [c1d030] "m"(b1ef90_c1d030), [c32b50] "m"(b1ef90_c32b50), [c19750] "m"(b1ef90_c19750), [c32bb0] "m"(b1ef90_c32bb0), [c3b380] "m"(b1ef90_c3b380), [c46f10] "m"(b1ef90_c46f10), [c198d0] "m"(b1ef90_c198d0), [memset] "m"(b1ef90_memset), [c24a60] "m"(b1ef90_c24a60), [c25c10] "m"(b1ef90_c25c10), [c1a100] "m"(b1ef90_c1a100), [c197d0] "m"(b1ef90_c197d0), [c5b5e0] "m"(b1ef90_c5b5e0), [c1c0e0] "m"(b1ef90_c1c0e0), [c159d0] "m"(b1ef90_c159d0), [assert] "m"(b1ef90_assert), [exitfn] "m"(b1ef90_exitfn), [c1d7c0] "m"(b1ef90_c1d7c0), [c32c10] "m"(b1ef90_c32c10), [c15900] "m"(b1ef90_c15900)
      : "memory");
}
#else
#error "actor_action_handle_lost_contact: clang naked draft required"
#endif


/* actor_action_handle_combat_status (0x1f770) — XBE naked draft (batch 121). */
#if defined(__clang__)
static void *(*const b1f770_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int16_t (*const b1f770_c1d6d0)(int actor_handle) = actor_action_try_to_panic;
static char (*const b1f770_c1e8a0)(int actor_handle) = actor_action_handle_combat_selection;
static char (*const b1f770_c1ef90)(int actor_handle) = actor_action_handle_lost_contact;
static void (*const b1f770_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1f770_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
char actor_action_handle_combat_status(int actor_handle __attribute__((unused)), int param2 __attribute__((unused)), int param3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1d6d0]\n\t"
      "movb 0x10(%%ebp), %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "testb %%cl, %%cl\n\t"
      "movb $1, %%cl\n\t"
      "jne .Lactor_action_handle_combat_status_1\n\t"
      "movb 0xc(%%ebp), %%cl\n\t"
      ".Lactor_action_handle_combat_status_1:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movl $4, %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "ja .Lactor_action_handle_combat_status_13\n\t"
      "jmp *.Lactor_action_handle_combat_status_jt(,%%eax,4)\n\t"
      ".Lactor_action_handle_combat_status_2:\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lactor_action_handle_combat_status_7\n\t"
      "movw 0x6e(%%esi), %%ax\n\t"
      "cmpw $5, %%ax\n\t"
      "jl .Lactor_action_handle_combat_status_3\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e8a0]\n\t"
      "jmp .Lactor_action_handle_combat_status_6\n\t"
      ".Lactor_action_handle_combat_status_3:\n\t"
      "cmpw $2, %%ax\n\t"
      "jge .Lactor_action_handle_combat_status_4\n\t"
      "cmpw $2, 0x6c(%%esi)\n\t"
      "je .Lactor_action_handle_combat_status_4\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lactor_action_handle_combat_status_7\n\t"
      "movb 0x1c8(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_action_handle_combat_status_4\n\t"
      "cmpw $0, 0x1e4(%%esi)\n\t"
      "jle .Lactor_action_handle_combat_status_7\n\t"
      ".Lactor_action_handle_combat_status_4:\n\t"
      "pushl %%edi\n\t"
      ".Lactor_action_handle_combat_status_5:\n\t"
      "call *%[c1ef90]\n\t"
      ".Lactor_action_handle_combat_status_6:\n\t"
      "movb %%al, %%bl\n\t"
      "addl $4, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lactor_action_handle_combat_status_14\n\t"
      ".Lactor_action_handle_combat_status_7:\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_action_handle_combat_status_14\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ef90]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_action_handle_combat_status_8:\n\t"
      "cmpw %%dx, 0x6e(%%esi)\n\t"
      "pushl %%edi\n\t"
      "jl .Lactor_action_handle_combat_status_5\n\t"
      "call *%[c1e8a0]\n\t"
      "jmp .Lactor_action_handle_combat_status_6\n\t"
      ".Lactor_action_handle_combat_status_9:\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lactor_action_handle_combat_status_10\n\t"
      "cmpw %%dx, 0x6e(%%esi)\n\t"
      "jl .Lactor_action_handle_combat_status_10\n\t"
      "pushl %%edi\n\t"
      "call *%[c1e8a0]\n\t"
      "jmp .Lactor_action_handle_combat_status_6\n\t"
      ".Lactor_action_handle_combat_status_10:\n\t"
      "cmpw $2, 0x6e(%%esi)\n\t"
      "jl .Lactor_action_handle_combat_status_4\n\t"
      "movl 0x270(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_action_handle_combat_status_7\n\t"
      "movl 0x5ab23c, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x270(%%esi), %%edx\n\t"
      "movl 0x3c0(%%esi), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jne .Lactor_action_handle_combat_status_4\n\t"
      "movb 0xb9(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lactor_action_handle_combat_status_11\n\t"
      "cmpw $5, 0x6c(%%esi)\n\t"
      "jne .Lactor_action_handle_combat_status_4\n\t"
      "cmpw $0, 0xa4(%%esi)\n\t"
      "jne .Lactor_action_handle_combat_status_4\n\t"
      ".Lactor_action_handle_combat_status_11:\n\t"
      "movb 0xba(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lactor_action_handle_combat_status_7\n\t"
      "movw 0x6c(%%esi), %%ax\n\t"
      "cmpw $5, %%ax\n\t"
      "jne .Lactor_action_handle_combat_status_12\n\t"
      "cmpw $0, 0xa4(%%esi)\n\t"
      "je .Lactor_action_handle_combat_status_7\n\t"
      ".Lactor_action_handle_combat_status_12:\n\t"
      "cmpw $7, %%ax\n\t"
      "jne .Lactor_action_handle_combat_status_4\n\t"
      "cmpw $0, 0xa4(%%esi)\n\t"
      "je .Lactor_action_handle_combat_status_7\n\t"
      "jmp .Lactor_action_handle_combat_status_4\n\t"
      ".Lactor_action_handle_combat_status_13:\n\t"
      "pushl $1\n\t"
      "pushl $0xb19\n\t"
      "pushl $0x2544b0\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lactor_action_handle_combat_status_7\n\t"
      ".Lactor_action_handle_combat_status_14:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lactor_action_handle_combat_status_jt:\n\t"
      ".long .Lactor_action_handle_combat_status_7\n\t"
      ".long .Lactor_action_handle_combat_status_2\n\t"
      ".long .Lactor_action_handle_combat_status_2\n\t"
      ".long .Lactor_action_handle_combat_status_9\n\t"
      ".long .Lactor_action_handle_combat_status_8\n\t"
      ".text\n\t"
      :
      : [dget] "m"(b1f770_dget), [c1d6d0] "m"(b1f770_c1d6d0), [c1e8a0] "m"(b1f770_c1e8a0), [c1ef90] "m"(b1f770_c1ef90), [assert] "m"(b1f770_assert), [exitfn] "m"(b1f770_exitfn)
      : "memory");
}
#else
#error "actor_action_handle_combat_status: clang naked draft required"
#endif


/* FUN_00020990 (0x20990) — XBE naked draft (batch 105). */
#if defined(__clang__)
static void *(*const b20990_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const b20990_gtime)(void) = game_time_get;
static float (*const b20990_c1ad60)(float *a, float *b) = FUN_0001ad60;
static int (*const b20990_c2a360)(int actor_handle) = FUN_0002a360;
static void (*const b20990_c12140)(float *a, float *b, float *result) = FUN_00012140;
static float (*const b20990_c10cd40)(float *p1, float *p2, float *p3) = FUN_0010cd40;
static char (*const b20990_c2a3d0)(int actor_handle) = FUN_0002a3d0;
static float (*const b20990_c10ce10)(float *p1, float *p2, float *p3, float *p4) = vector_to_line_distance_squared3d;
static void (*const b20990_c24be0)(int actor_handle, short param_2, char param_3) = FUN_00024be0;
static float (*const b20990_c10d680)(float *ray_origin, float *ray_dir, float *sphere_center, float radius) = FUN_0010d680;
static void (*const b20990_c46f10)(int16_t type, int unit_handle, int param3, int param4, int16_t param5, int16_t param6, int16_t param7) = FUN_00046f10;
static void (*const b20990_c1e360)(void) = actor_action_find_escape_from_danger;
static void *(*const b20990_tag)(int, int) = tag_get;
static char (*const b20990_c1fe70)(int actor_handle, short direction_ref, float param_3, float *direction, float param_5) = actor_action_try_to_dive;
static int (*const b20990_c2a3f0)(int actor_handle) = FUN_0002a3f0;
static int16_t (*const b20990_c1d6d0)(int actor_handle) = actor_action_try_to_panic;
static int (*const b20990_c128c0)(int *a0, int *a1) = action_avoid_setup;
static void (*const b20990_c1d030)(int actor_handle, int new_action_type, int param_3) = actor_action_change;
static void (*const b20990_c20f67)(void) = (void (*)(void))actor_combat_check_mode;
static void (*const b20990_c20f50)(void) = (void (*)(void))actor_combat_check_mode;

__attribute__((naked, noinline))
char FUN_00020990(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xac, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x331f58, %%ecx\n\t"
      "andl $0xffff, %%edi\n\t"
      "imull $0x657c, %%edi, %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "addl %%ecx, %%edi\n\t"
      "movb %%bl, -0x3(%%ebp)\n\t"
      "movb %%bl, -0x2(%%ebp)\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, 0x168(%%edi)\n\t"
      "movw %%bx, 0x16c(%%edi)\n\t"
      "movw %%bx, 0x188(%%edi)\n\t"
      "movb %%bl, 0x16e(%%edi)\n\t"
      "cmpw %%bx, 0x280(%%esi)\n\t"
      "jne .LFUN_00020990_1\n\t"
      "movw %%bx, 0x16c(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00020990_1:\n\t"
      "movb 0x287(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00020990_2\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "movw $1, 0x16c(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00020990_2:\n\t"
      "movb 0x28a(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00020990_3\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "movw $0xd, 0x16c(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00020990_3:\n\t"
      "flds 0x2dc(%%esi)\n\t"
      "leal 0x2dc(%%esi), %%ecx\n\t"
      "fsubs 0x12c(%%esi)\n\t"
      "leal 0x12c(%%esi), %%ebx\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "flds 0x2d8(%%esi)\n\t"
      "fadds 0x254644\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fld %%st(4)\n\t"
      ".byte 0xd8, 0xcd\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fcompp\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jp .LFUN_00020990_4\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movw $4, 0x16c(%%edi)\n\t"
      "call *%[c1ad60]\n\t"
      "fstps 0x170(%%edi)\n\t"
      "flds 0x2d8(%%esi)\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "fadds 0x254644\n\t"
      "addl $8, %%esp\n\t"
      "fstps 0x174(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00020990_4:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2a360]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00020990_5\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "movw $2, 0x16c(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00020990_5:\n\t"
      "movb 0x160(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00020990_6\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "movw $3, 0x16c(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00020990_6:\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x2c8(%%esi), %%ecx\n\t"
      "leal 0x2b0(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c12140]\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x2b0(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c10cd40]\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "flds 0x294(%%esi)\n\t"
      "addl $0x18, %%esp\n\t"
      "fld %%st(0)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00020990_7\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_00020990_7:\n\t"
      "flds 0x294(%%esi)\n\t"
      "movb $1, -0x4(%%ebp)\n\t"
      "fadds 0x253f30\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fxch %%st(1)\n\t"
      "fxch %%st(2)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00020990_8\n\t"
      "movb $0, -0x4(%%ebp)\n\t"
      ".LFUN_00020990_8:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c2a3d0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00020990_13\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x2b0(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x4ac(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c10cd40]\n\t"
      "flds 0x294(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "addl $0xc, %%esp\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fxch %%st(1)\n\t"
      "fxch %%st(2)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00020990_9\n\t"
      "movb $1, %%al\n\t"
      "jmp .LFUN_00020990_10\n\t"
      ".LFUN_00020990_9:\n\t"
      "xorb %%al, %%al\n\t"
      ".LFUN_00020990_10:\n\t"
      "movb 0x504(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00020990_14\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00020990_14\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00020990_15\n\t"
      "flds 0x518(%%esi)\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "fmuls 0x254644\n\t"
      "pushl %%eax\n\t"
      "leal 0x2b0(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "flds 0x51c(%%esi)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x254644\n\t"
      "pushl %%ebx\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x520(%%esi)\n\t"
      "fmuls 0x254644\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "call *%[c10ce10]\n\t"
      "flds 0x294(%%esi)\n\t"
      "addl $0x10, %%esp\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fxch %%st(1)\n\t"
      "fxch %%st(2)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00020990_11\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "jmp .LFUN_00020990_15\n\t"
      ".LFUN_00020990_11:\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      ".LFUN_00020990_12:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "fsqrt\n\t"
      "movw $5, 0x16c(%%edi)\n\t"
      "fstps 0x178(%%edi)\n\t"
      "movl 0x294(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x17c(%%edi)\n\t"
      "jmp .LFUN_00020990_37\n\t"
      ".LFUN_00020990_13:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      ".LFUN_00020990_14:\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00020990_16\n\t"
      ".LFUN_00020990_15:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x3b8(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00020990_16\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c24be0]\n\t"
      "addl $0xc, %%esp\n\t"
      "movb $1, 0x16e(%%edi)\n\t"
      ".LFUN_00020990_16:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00020990_12\n\t"
      "movl 0x294(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x2b0(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c10d680]\n\t"
      "fcoms 0x2548fc\n\t"
      "addl $0x10, %%esp\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00020990_17\n\t"
      "fmuls 0x2548f8\n\t"
      "fsts -0x8(%%ebp)\n\t"
      ".LFUN_00020990_17:\n\t"
      "movw 0x280(%%esi), %%dx\n\t"
      "movswl %%dx, %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00020990_19\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00020990_18\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_00020990_20\n\t"
      "fcomps 0x253394\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00020990_21\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_00020990_21\n\t"
      ".LFUN_00020990_18:\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00020990_21\n\t"
      "movw 0x2e8(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00020990_21\n\t"
      "cmpw $0x14, %%ax\n\t"
      "jge .LFUN_00020990_21\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_00020990_21\n\t"
      ".LFUN_00020990_19:\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00020990_21\n\t"
      "movw 0x2e8(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00020990_21\n\t"
      "cmpw $0x1e, %%ax\n\t"
      "jge .LFUN_00020990_21\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_00020990_21\n\t"
      ".LFUN_00020990_20:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00020990_21:\n\t"
      "movw 0x282(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_00020990_22\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00020990_27\n\t"
      ".LFUN_00020990_22:\n\t"
      "movb 0x289(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00020990_27\n\t"
      "movswl %%ax, %%eax\n\t"
      "subl $0, %%eax\n\t"
      "movl $0xffffffff, %%ecx\n\t"
      "je .LFUN_00020990_24\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00020990_23\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_00020990_25\n\t"
      "movl $1, %%ecx\n\t"
      "jmp .LFUN_00020990_25\n\t"
      ".LFUN_00020990_23:\n\t"
      "movl $2, %%ecx\n\t"
      "jmp .LFUN_00020990_25\n\t"
      ".LFUN_00020990_24:\n\t"
      "movl $3, %%ecx\n\t"
      ".LFUN_00020990_25:\n\t"
      "cmpw $2, %%dx\n\t"
      "jne .LFUN_00020990_26\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "pushl $0xc\n\t"
      "call *%[c46f10]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_00020990_26:\n\t"
      "movb $1, 0x289(%%esi)\n\t"
      ".LFUN_00020990_27:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "leal 0xb(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1e360]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw $-1, -0x10(%%ebp)\n\t"
      "jne .LFUN_00020990_28\n\t"
      "movw $7, 0x16c(%%edi)\n\t"
      "jmp .LFUN_00020990_37\n\t"
      ".LFUN_00020990_28:\n\t"
      "movb 0x288(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00020990_10000\n\t"
      "cmpl $-1, 0x158(%%esi)\n\t"
      "jne .LFUN_00020990_10000\n\t"
      "movswl 0x280(%%esi), %%ecx\n\t"
      "decl %%ecx\n\t"
      "je .LFUN_00020990_31\n\t"
      "decl %%ecx\n\t"
      "je .LFUN_00020990_29\n\t"
      "decl %%ecx\n\t"
      "jne .LFUN_00020990_10001\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00020990_10001\n\t"
      "movw $0xb, 0x16c(%%edi)\n\t"
      "jmp .LFUN_00020990_35\n\t"
      ".LFUN_00020990_29:\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00020990_30\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00020990_34\n\t"
      ".LFUN_00020990_30:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x2548f4\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jmp .LFUN_00020990_33\n\t"
      ".LFUN_00020990_31:\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00020990_32\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00020990_34\n\t"
      ".LFUN_00020990_32:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      ".LFUN_00020990_33:\n\t"
      "jp .LFUN_00020990_34\n\t"
      "movw $9, 0x16c(%%edi)\n\t"
      "jmp .LFUN_00020990_35\n\t"
      ".LFUN_00020990_34:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00020990_10001\n\t"
      "movw $0xa, 0x16c(%%edi)\n\t"
      ".LFUN_00020990_35:\n\t"
      "movl 0x58(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testl $0x2000000, %%ecx\n\t"
      "movl $0x41000000, 0x8(%%ebp)\n\t"
      "jne .LFUN_00020990_36\n\t"
      "movl $0, 0x8(%%ebp)\n\t"
      ".LFUN_00020990_36:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1fe70]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movb %%al, -0x3(%%ebp)\n\t"
      "jne .LFUN_00020990_40\n\t"
      ".LFUN_00020990_37:\n\t"
      "movb -0x4(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00020990_40\n\t"
      "pushl %%ebx\n\t"
      "call *%[c2a3f0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00020990_38\n\t"
      "movb 0x504(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00020990_38\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00020990_40\n\t"
      ".LFUN_00020990_38:\n\t"
      "movb 0x375(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00020990_40\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d6d0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $1, %%ax\n\t"
      "je .LFUN_00020990_39\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .LFUN_00020990_40\n\t"
      ".LFUN_00020990_39:\n\t"
      "leal -0xac(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c128c0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00020990_40\n\t"
      "leal -0xac(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0xd\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d030]\n\t"
      "addl $0xc, %%esp\n\t"
      "movb $1, -0x3(%%ebp)\n\t"
      ".LFUN_00020990_40:\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00020990_10000:\n\t"
      "jmp *%[c20f67]\n\t"
      ".LFUN_00020990_10001:\n\t"
      "jmp *%[c20f50]\n\t"
      :
      : [dget] "m"(b20990_dget), [gtime] "m"(b20990_gtime), [c1ad60] "m"(b20990_c1ad60), [c2a360] "m"(b20990_c2a360), [c12140] "m"(b20990_c12140), [c10cd40] "m"(b20990_c10cd40), [c2a3d0] "m"(b20990_c2a3d0), [c10ce10] "m"(b20990_c10ce10), [c24be0] "m"(b20990_c24be0), [c10d680] "m"(b20990_c10d680), [c46f10] "m"(b20990_c46f10), [c1e360] "m"(b20990_c1e360), [tag] "m"(b20990_tag), [c1fe70] "m"(b20990_c1fe70), [c2a3f0] "m"(b20990_c2a3f0), [c1d6d0] "m"(b20990_c1d6d0), [c128c0] "m"(b20990_c128c0), [c1d030] "m"(b20990_c1d030), [c20f67] "m"(b20990_c20f67), [c20f50] "m"(b20990_c20f50)
      : "memory");
}
#else
#error "FUN_00020990: clang naked draft required"
#endif

