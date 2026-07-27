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

/* actor_action_allow_cover_seeking (0x1ccc0) — readable C lift (restored pre-naked)
 * Gating predicate: may the actor begin seeking cover this frame? Result starts
 * true. Only when param_2 == 0 AND the actor+0x1ca suppress byte is clear, two
 * actr-tag cooldown/threshold checks may clear it. Two unconditional overrides
 * follow: actor+0x378 forces deny; actor+0x160 hard-denies (returns 0) ignoring
 * everything above.
 * Confirmed: datum_get(actor_data, actor_handle) at 0x1ccd6.
 * Confirmed: tag_get(0x61637472, actor+0x58) loads the actr tag.
 *   actr_tag+0x2d8 = cover cooldown in seconds (*30 -> ticks @30Hz).
 *   actr_tag+0x324 = threat threshold (float).
 *   actor+0x6e     = short state counter; >= 7 denies.
 *   actor+0x26c    = last cover-seek game time (-1 = none).
 *   actor+0x1c0    = current threat scalar (float).
 * Note: the ftol2 result is spilled and reloaded via MOVSX word (0x1cd9a), so
 * the cooldown tick count is truncated to int16 before being added to
 * actor+0x26c. The (short) cast preserves that. */
char actor_action_allow_cover_seeking(int actor_handle, char param_2)
{
  char *actor;
  int actr_tag;
  short cooldown_ticks;
  char result;

  actor = (char *)datum_get(actor_data, actor_handle);
  actr_tag = (int)tag_get(0x61637472, *(int *)(actor + 0x58));
  result = 1;
  if ((param_2 == '\0') && (*(char *)(actor + 0x1ca) == '\0')) {
    if (*(float *)(actr_tag + 0x2d8) > 0.0f) {
      if (*(short *)(actor + 0x6e) >= 7) {
        result = 0;
      } else {
        cooldown_ticks = (short)(int)(*(float *)(actr_tag + 0x2d8) * 30.0f);
        if (*(int *)(actor + 0x26c) != -1) {
          if (game_time_get() < (int)cooldown_ticks + *(int *)(actor + 0x26c)) {
            result = 0;
          }
        }
      }
    }
    if (*(float *)(actr_tag + 0x324) > 0.0f) {
      if (*(float *)(actor + 0x1c0) < *(float *)(actr_tag + 0x324)) {
        result = 0;
      }
    }
  }
  if (*(char *)(actor + 0x378) != '\0') {
    result = 0;
  }
  if (*(char *)(actor + 0x160) != '\0') {
    return 0;
  }
  return result;
}


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

/* actor_action_handle_panic_transition (0x1dd40) — restored readable C from d2535c6b4 */
/* actor_action_handle_panic_transition (0x1dd40) — Handles a panic-level
 * transition for an actor. If the actor's current panic level (actor+0x308)
 * meets or exceeds param_2 and the actor is not suppressed (actor+0x160),
 * evaluates the transition. In guard action (0x6c==4) with positive shield
 * value (actor+0xa8), clamps the shield to the panic level. Otherwise, if
 * enough time has passed since actor+0x398, checks whether to play a sound
 * event or attempt seek cover via FUN_0001d3c0. Clears panic level on exit.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x1dd50.
 * Confirmed: game_time_get() at 0x1ddd6.
 * Confirmed: display_assert + system_exit pattern at 0x1de08-0x1de25.
 * Confirmed: FUN_00046f10 sound event call at 0x1de43.
 * Confirmed: FUN_0001d3c0 call at 0x1de74. */
char actor_action_handle_panic_transition(int actor_handle, short param_2,
                                          char param_3, short param_4)
{
  char *actor;
  short panic_level;
  short shield_value;
  int iVar5;
  char bVar3;
  volatile char result;

  actor = (char *)datum_get(actor_data, actor_handle);
  panic_level = *(short *)(actor + 0x308);
  result = 0;
  if (param_2 <= panic_level && *(char *)(actor + 0x160) == '\0') {
    if (*(short *)(actor + 0x6c) == 4 &&
        (shield_value = *(short *)(actor + 0xa8), shield_value > 0)) {
      if (panic_level < shield_value) {
        *(short *)(actor + 0xa8) = shield_value;
        *(short *)(actor + 0x308) = 0;
        return result;
      }
      *(short *)(actor + 0xa8) = panic_level;
      *(short *)(actor + 0x308) = 0;
      return result;
    }
    if (*(int *)(actor + 0x398) != -1) {
      iVar5 = game_time_get();
      if (iVar5 <= *(int *)(actor + 0x398) + 7) {
        goto done;
      }
    }
    bVar3 = *(short *)(actor + 0x308) >= param_4;
    if (*(int *)(actor + 0x30c) == 0) {
      display_assert("actor->stimuli.panic_prop_index != 0x00000000",
                     "c:\\halo\\SOURCE\\ai\\actions.c", 0x295, 1);
      system_exit(-1);
    }
    if (param_3 != '\0' && !bVar3) {
      FUN_00046f10(0x22, *(int *)(actor + 0x18), -1, -1, -1, -1, 0);
      *(short *)(actor + 0x308) = 0;
      return result;
    }
    result = FUN_0001d3c0(actor_handle, *(short *)(actor + 0x308),
                          *(int *)(actor + 0x30c), bVar3);
  }
done:
  *(short *)(actor + 0x308) = 0;
  return result;
}

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

/* actor_action_try_to_throw_grenade (0x1fa60) — readable C lift (restored pre-naked) — Attempts to commit the actor
 * to a grenade throw this tick. Returns 1 if the throw was committed, 0
 * otherwise.
 *
 * Resolves the actor and its unit object (actor+0x18, type 3). Bails
 * (returns 0) if the unit is busy (unit_is_busy) or the object's throw
 * cooldown timer (object+0x9c) has not expired (i.e. is > 0.0). When flag==0,
 * re-tests grenade viability via actor_action_test_grenade and clears the
 * pending flag (actor+0x6a0) if that test fails. If the pending flag is set,
 * computes the horizontal offset from self position (0x12c/0x130) to the
 * grenade target (0x6a8/0x6ac), normalizes it in place (magnitude3d, 2 floats),
 * and requires a nonzero magnitude. Then checks the target lies within the
 * throw arc: the normalized direction dotted with the actor facing
 * (0x174/0x178) must be >= *(float*)0x2533dc (cos(30 deg) = 0.866025388;
 * referenced as the exact global constant, NOT a rounded literal). On success
 * sets the throw-commit flag (actor+0x45c), clears the pending flag, and — if
 * the actor has a valid encounter handle (actor+0x34 != NONE) — stamps that
 * encounter record (encounter+0x5c) with the current game time. */
char actor_action_try_to_throw_grenade(int actor_handle, char flag)
{
  char *actor;
  char *object;
  char *encounter;
  float delta[2];

  actor = (char *)datum_get(actor_data, actor_handle);
  object = (char *)object_get_and_verify_type(*(int *)(actor + 0x18), 3);
  if (unit_is_busy(*(int *)(actor + 0x18)) == 0) {
    if (*(float *)(object + 0x9c) <= *(float *)0x2533c0) {
      if (flag == '\0') {
        if (actor_action_test_grenade(actor_handle) == '\0') {
          *(char *)(actor + 0x6a0) = 0;
        }
      }
      if (*(char *)(actor + 0x6a0) != '\0') {
        delta[0] = *(float *)(actor + 0x6a8) - *(float *)(actor + 0x12c);
        delta[1] = *(float *)(actor + 0x6ac) - *(float *)(actor + 0x130);
        if (*(float *)0x2533c0 < magnitude3d(delta)) {
          if (*(float *)0x2533dc <= delta[0] * *(float *)(actor + 0x174) +
                                      delta[1] * *(float *)(actor + 0x178)) {
            *(char *)(actor + 0x45c) = 1;
            *(char *)(actor + 0x6a0) = 0;
            if (*(int *)(actor + 0x34) != -1) {
              encounter =
                (char *)datum_get(*(data_t **)0x5ab270, *(int *)(actor + 0x34));
              *(int *)(encounter + 0x5c) = game_time_get();
            }
            return 1;
          }
        }
      }
    }
  }
  return 0;
}


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

/* actor_pursuit_find_nearby_actors (0x20280) — readable C lift (restored pre-naked) — Scans the actor's own clump and
 * (when still under-satisfied) its encounter for eligible pursuit targets,
 * counts the qualifiers, records the nearest one's index at actor+0x1d0, and
 * returns the qualifier count.
 *
 * Pass 1 walks the clump-actor iterator (FUN_00064540/FUN_00064570): each
 * record must have flag bytes at +0x60 and +0x127 clear, a valid unit index at
 * +0x1c, and (when flag != 0) a type word at +0x24 in [2,4). FUN_0001d530
 * (actor_handle in EAX) is the category-differs predicate. Each qualifier
 * increments the count; the record with the smallest key at +0x11c becomes the
 * best, its index taken from the iterator cursor iter1[0].
 *
 * threshold = (flag != 0) + 1  (1 or 2). If the count is still below threshold
 * and the actor's encounter handle (+0x34) is valid, Pass 2 walks the encounter
 * iterator (encounter_actor_iterator_new/next). For each element with a valid
 * unit index at +0x18 passing FUN_0001d530, it resolves an active-prop index
 * via prop_get_active_by_unit_index, falling back to FUN_00064b40(...,1,0); on
 * a valid index it counts the element and, when the 3D distance (record
 * +0x12c..) to the actor's own position is closer, records that index. Stops
 * once the count reaches threshold.
 *
 * Confirmed: EDI = actor_handle preserved as the @<eax> arg to both
 * FUN_0001d530 sites (MOV EAX,EDI at 0x20309 and 0x203a2); cdecl pushes are
 * (char)flag then the actor index, one ADD ESP,0x8 each. Confirmed: FLT_MAX
 * seed 0x7f7fffff at 0x202b9; both distance compares are '<' (TEST AH,5;JP).
 * Pass-2 magnitude is FSQRT over +0x12c/+0x130/+0x134 deltas. Confirmed: iter1
 * = 8-byte clump iterator (FUN_00064540 writes +4, FUN_00064570 walks +0/+4);
 * iter2 = 12-byte encounter iterator, current handle at iter2[1] (EBP-0x20).
 * Final store *(int*)(actor+0x1d0) = best_index at 0x2045d. */
int actor_pursuit_find_nearby_actors(int actor_handle, char flag)
{
  int actor;
  int rec;
  int count;
  int best_index;
  float best_dist;
  int threshold;
  int threshold_raw;
  int mapped;
  float dx;
  float dy;
  float dz;
  float dist;
  int iter1[2];
  int iter2[3];

  actor = (int)datum_get(actor_data, actor_handle);
  count = 0;
  best_index = -1;
  best_dist = 3.4028235e+38f;
  FUN_00064540(iter1, actor_handle);
  threshold_raw = (flag != '\0') + 1;
  rec = FUN_00064570(iter1);
  while (rec != 0) {
    if (*(char *)(rec + 0x60) == '\0' && *(char *)(rec + 0x127) == '\0' &&
        *(int *)(rec + 0x1c) != -1 &&
        (flag == '\0' ||
         (1 < *(short *)(rec + 0x24) && *(short *)(rec + 0x24) < 4)) &&
        FUN_0001d530(actor_handle, flag, *(int *)(rec + 0x1c)) != '\0') {
      count++;
      if (*(float *)(rec + 0x11c) < best_dist) {
        best_dist = *(float *)(rec + 0x11c);
        best_index = iter1[0];
      }
    }
    rec = FUN_00064570(iter1);
  }
  threshold = (short)threshold_raw;
  if (count < threshold && *(int *)(actor + 0x34) != -1) {
    encounter_actor_iterator_new(iter2, *(int *)(actor + 0x34));
    rec = encounter_actor_iterator_next(iter2);
    while (rec != 0) {
      if (*(int *)(rec + 0x18) != -1 &&
          FUN_0001d530(actor_handle, flag, iter2[1]) != '\0') {
        mapped =
          prop_get_active_by_unit_index(actor_handle, *(int *)(rec + 0x18));
        if (mapped == -1) {
          mapped = FUN_00064b40(actor_handle, *(int *)(rec + 0x18), 1, 0);
        }
        if (mapped != -1) {
          count++;
          dx = *(float *)(rec + 0x12c) - *(float *)(actor + 0x12c);
          dy = *(float *)(rec + 0x130) - *(float *)(actor + 0x130);
          dz = *(float *)(rec + 0x134) - *(float *)(actor + 0x134);
          dist = sqrtf(dx * dx + dy * dy + dz * dz);
          if (dist < best_dist) {
            best_index = mapped;
            best_dist = dist;
          }
          if (threshold <= count) {
            break;
          }
        }
      }
      rec = encounter_actor_iterator_next(iter2);
    }
  }
  *(int *)(actor + 0x1d0) = best_index;
  return count;
}


/* actor_action_consider_grenade (0x1fb80) — Probabilistically decides whether
 * the actor should begin a grenade throw this tick. Gated by: the "already
 * considering" flag (actor+0x6a0), the global AI grenade-enable flag
 * (*(char**)0x632574 + 0x3b4), and the actv tag having both grenade type
 * fields present (tag+0x180 and tag+0x182 != -1). Enforces a cooldown: if the
 * last-throw timestamp (actor+0x6a4) is valid (!= -1) and the cooldown window
 * (tag+0x1a4 * 30.0f + stamp) has not yet elapsed relative to game_time, bail.
 * Otherwise re-stamps the cooldown, rolls a random value against
 * (team-scaled multiplier * tag throw-chance at 0x1a0), and if the roll
 * succeeds and actor_action_test_grenade passes, sets the consider flag and
 * kicks off the throw. Returns 1 while inside the consider window, else 0. */
char actor_action_consider_grenade(int actor_handle)
{
  char *actor;
  char *actv_tag;
  int current_time;
  int *seed;
  float expiry;
  float throw_chance;
  float team_mult;
  float roll;

  actor = (char *)datum_get(actor_data, actor_handle);
  actv_tag = (char *)tag_get(0x61637476, *(int *)(actor + 0x5c));
  if (*(char *)(actor + 0x6a0) == '\0') {
    if (*(char *)(*(char **)0x632574 + 0x3b4) == '\0')
      return 0;
    if (*(short *)(actv_tag + 0x180) == -1)
      return 0;
    if (*(short *)(actv_tag + 0x182) == -1)
      return 0;
    current_time = game_time_get();
    if (*(int *)(actor + 0x6a4) != -1) {
      expiry = *(float *)(actv_tag + 0x1a4) * *(float *)0x253394 +
               (float)*(int *)(actor + 0x6a4);
      if (expiry > (float)current_time)
        return 0;
    }
    throw_chance = *(float *)(actv_tag + 0x1a0);
    team_mult = FUN_000b55b0(0x17, *(short *)(actor + 0x3e));
    *(int *)(actor + 0x6a4) = current_time;
    seed = get_global_random_seed_address();
    roll = random_math_real((unsigned int *)seed);
    if (team_mult * throw_chance <= roll ||
        actor_action_test_grenade(actor_handle) == '\0')
      return 0;
    *(char *)(actor + 0x6a0) = 1;
    actor_action_try_to_throw_grenade(actor_handle, 1);
  }
  return 1;
}


/* actor_action_try_to_evade (0x1fca0) - Attempt to start an evade (sidestep)
 * action away from the actor's current target/attractor.
 *
 * Pre-screen guards (all fall through to a false return):
 *   1. actor+0x158 (swarm element handle) must be NONE (-1).
 *   2. FUN_0002a360(actor_handle) must be false (some blocking condition).
 *   3. actor+0x504 (a boolean flag) must be clear.
 *   4. actor+0x270 (target prop/attractor datum handle) must be valid (!= -1).
 *   5. unit_tag+0x234 (evade-enable / max-evade scalar) must be > 0.0f.
 *
 * Reads the attractor direction (2D vector at prop+0xe0) and measures its
 * alignment with the actor's facing (actor+0x174/0x178). When actr_tag flag
 * 0x200000 is set the alignment is a 3-component dot (FUN_00013070); otherwise
 * the attractor vector is copied, normalized (magnitude3d), and dotted in 2D.
 * A zero-length attractor vector skips the alignment gate. The alignment must
 * exceed 0.4f (0x253524) to proceed.
 *
 * Builds the alignment vector (normalized copy of prop+0xe0), requests a
 * feasible evade direction from actor_move_try_evasion_direction with the
 * "random" reference mode (4). On success the returned direction index selects
 * an animation impulse (1 -> 7, 0 -> 6; anything else asserts), which is
 * validated via unit_test_animation_impulse before being committed with
 * actor_move_animation_impulse.
 *
 * Confirmed: datum_get(actor_data, actor_handle); tag_get('actr', actor+0x58);
 * object_get_and_verify_type(actor+0x18, 3); tag_get('unit', *object);
 * datum_get(prop_data 0x5ab23c, actor+0x270). Confirmed float constants
 * 0x2533c0 = 0.0f, 0x253524 = 0.4f. Confirmed FUN_0002ab40 result buffer is a
 * pathfinding-location scratch (28-byte frame reservation, callee reads +0xc).
 * Confirmed default-case assert "evade_direction == _actor_evade_left",
 * line 0xce3, + system_exit(-1). Returns bool in AL. */
char actor_action_try_to_evade(int actor_handle)
{
  char *actor;
  int *actr_tag;
  char *unit_tag;
  char *prop;
  float *attractor_vec;
  float scratch[2];
  float alignment_vec[2];
  float dot;
  int evade_dir_ref;
  char out_flag;
  char result;
  int impulse;
  char path_result[0x1c];

  actor = (char *)datum_get(actor_data, actor_handle);
  result = 0;
  if (*(int *)(actor + 0x158) != -1) {
    return result;
  }
  if (FUN_0002a360(actor_handle) != 0) {
    return result;
  }
  if (*(char *)(actor + 0x504) != '\0') {
    return result;
  }
  if (*(int *)(actor + 0x270) == -1) {
    return result;
  }

  actr_tag = (int *)tag_get(0x61637472, *(int *)(actor + 0x58));
  unit_tag = (char *)tag_get(
      0x756e6974,
      *(int *)object_get_and_verify_type(*(int *)(actor + 0x18), 3));
  prop = (char *)datum_get(*(data_t **)0x5ab23c, *(int *)(actor + 0x270));
  if (*(float *)(unit_tag + 0x234) <= *(float *)0x2533c0) {
    return result;
  }

  attractor_vec = (float *)(prop + 0xe0);
  if ((*actr_tag & 0x200000) != 0) {
    dot = FUN_00013070(attractor_vec, (float *)(actor + 0x174));
  } else {
    scratch[0] = attractor_vec[0];
    scratch[1] = attractor_vec[1];
    if (magnitude3d(scratch) <= *(float *)0x2533c0) {
      goto do_evade;
    }
    dot = scratch[1] * *(float *)(actor + 0x178) +
          scratch[0] * *(float *)(actor + 0x174);
  }
  if (dot <= *(float *)0x253524) {
    return result;
  }

do_evade:
  alignment_vec[0] = attractor_vec[0];
  alignment_vec[1] = attractor_vec[1];
  evade_dir_ref = 4;
  magnitude3d(alignment_vec);
  if (actor_move_try_evasion_direction(actor_handle, alignment_vec,
                                       *(float *)(unit_tag + 0x234),
                                       (unsigned short *)&evade_dir_ref, 0.0f,
                                       &out_flag, path_result) != '\0') {
    if ((unsigned short)evade_dir_ref == 1) {
      impulse = 7;
    } else if ((unsigned short)evade_dir_ref == 0) {
      impulse = 6;
    } else {
      display_assert("evade_direction == _actor_evade_left",
                     "c:\\halo\\SOURCE\\ai\\actions.c", 0xce3, 1);
      system_exit(-1);
    }
    if (unit_test_animation_impulse(*(int *)(actor + 0x18), impulse) != 0) {
      result = (char)actor_move_animation_impulse(
        actor_handle, (int16_t)impulse, (int *)alignment_vec);
    }
  }
  return result;
}


/* actor_action_try_to_dive (0x1fe70) - Attempt to start a dive/dodge action in
 * a lateral direction chosen relative to the actor's facing frame.
 *
 * On entry the actor's avoidance-state record (base *(int*)0x331f58, stride
 * 0x657c, indexed by the low 16 bits of the handle) is stamped at +0x184 with
 * the current game time; the final outcome is written at +0x188:
 *   1 = pre-screen / evasion-direction rejection, 2 = no feasible dive
 *   possibility, 3 = animation impulse rejected, 4 = success.
 *
 * Pre-screen (outcome 1): the actor must not be in a vehicle (actor+0x158 ==
 * NONE) and actor_move_try_evasion_direction must accept the requested
 * direction. direction_ref is an IN/OUT reference-mode word: on success the
 * callee overwrites it with the chosen reference direction (0..3), which then
 * selects how the input 2D vector is rotated into (dive_x, dive_y).
 *
 * (dive_x, dive_y) is projected onto the actor's facing axes (actor+0x174 /
 * +0x178) to build four candidate alignment scores. The static dive-possibility
 * table at 0x2542b2 is walked; each 8-byte entry carries {impulse index (-2),
 * animation_direction (0), score bias (+2, float)}. A possibility wins when its
 * biased score beats the running best (seeded to -0.5f) and
 * unit_test_animation_impulse accepts its impulse on the actor's object. If a
 * winner is found the output direction is re-derived from the winning
 * animation_direction and committed via actor_move_animation_impulse; on success
 * a 0x2c event is fired (FUN_00046f10) and the impulse result is returned.
 *
 * Confirmed: datum_get(actor_data, actor_handle); avoidance record
 * *(int*)0x331f58 + (handle & 0xffff)*0x657c; game_time_get() stamp at +0x184;
 * actor_move_try_evasion_direction 7-arg call (float scalars arg3/arg5, IN/OUT
 * unsigned-short ref arg4, out flag + 28-byte path scratch); asserts at
 * actions.c 0xd24 / 0xd3e / 0xd69 each followed by system_exit(-1); float
 * constant 0xbf000000 = -0.5f. cases 2 and 3 are byte-identical in both
 * switches (separate jump-table slots). Returns bool in AL. */
char actor_action_try_to_dive(int actor_handle, short direction_ref, float param_3,
                              float *direction, float param_5)
{
  char *actor;
  int record;
  char out_flag;
  char path_result[0x1c];
  float dive_x;
  float dive_y;
  float scores[4];
  short best_index;
  float best_score;
  float out_vec[2];
  unsigned short *poss;
  char result;

  actor = (char *)datum_get(actor_data, actor_handle);
  record = (actor_handle & 0xffff) * 0x657c + *(int *)0x331f58;
  out_flag = 0;
  *(int *)(record + 0x184) = game_time_get();

  if (*(int *)(actor + 0x158) != -1 ||
      actor_move_try_evasion_direction(actor_handle, direction, param_3,
                                       (unsigned short *)&direction_ref, param_5,
                                       &out_flag, path_result) == '\0') {
    *(short *)(record + 0x188) = 1;
    return '\0';
  }

  switch (direction_ref) {
  case 0:
    dive_x = *direction;
    dive_y = -direction[1];
    break;
  case 1:
    dive_y = direction[1];
    dive_x = -*direction;
    break;
  case 2:
    dive_x = direction[1];
    dive_y = *direction;
    break;
  case 3:
    dive_x = direction[1];
    dive_y = *direction;
    break;
  default:
    display_assert(0, "c:\\halo\\SOURCE\\ai\\actions.c", 0xd24, 1);
    system_exit(-1);
  }

  /* The winning animation_direction shares out_vec[1]'s stack slot: it lives
   * during the possibility scan, is read by the second switch's dispatch, then
   * the slot is overwritten with the output vector's Y component. */
  best_index = -1;
  *(int *)(out_vec + 1) = -1;
  best_score = -0.5f;
  scores[2] = dive_y * *(float *)(actor + 0x174) + dive_x * *(float *)(actor + 0x178);
  scores[0] = *(float *)(actor + 0x174) * dive_x + -*(float *)(actor + 0x178) * dive_y;
  scores[3] = -scores[2];
  scores[1] = -scores[0];

  poss = (unsigned short *)0x2542b2;
  do {
    if ((short)poss[0] < 0 || 3 < (short)poss[0]) {
      display_assert(
          "(possibility->animation_direction >= 0) && (possibility->animation_direction < 4)",
          "c:\\halo\\SOURCE\\ai\\actions.c", 0xd3e, 1);
      system_exit(-1);
    }
    if (best_score < scores[(short)poss[0]] + *(float *)(poss + 1) &&
        unit_test_animation_impulse(*(int *)(actor + 0x18), poss[-1]) != 0) {
      best_index = poss[-1];
      *(int *)(out_vec + 1) = poss[0];
      best_score = scores[(short)poss[0]] + *(float *)(poss + 1);
    }
    poss = poss + 4;
  } while (poss[-1] != 0xffff);

  if (best_index == -1) {
    *(short *)(record + 0x188) = 2;
    return '\0';
  }

  switch (*(short *)(out_vec + 1)) {
  case 0:
    out_vec[1] = -dive_y;
    out_vec[0] = dive_x;
    break;
  case 1:
    out_vec[0] = -dive_x;
    out_vec[1] = dive_y;
    break;
  case 2:
    out_vec[0] = dive_y;
    out_vec[1] = dive_x;
    break;
  case 3:
    out_vec[0] = dive_y;
    out_vec[1] = dive_x;
    break;
  default:
    display_assert(0, "c:\\halo\\SOURCE\\ai\\actions.c", 0xd69, 1);
    system_exit(-1);
  }

  result = (char)actor_move_animation_impulse(actor_handle, best_index,
                                              (int *)out_vec);
  if (result == '\0') {
    *(short *)(record + 0x188) = 3;
    return result;
  }
  FUN_00046f10(0x2c, *(int *)(actor + 0x18), -1, -1, -1, -1, 0);
  *(short *)(record + 0x188) = 4;
  return result;
}


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

/* actor_action_handle_evasion (0x20670) — readable C lift (restored pre-naked) — Decides whether the actor should
 * take an evasive action (dodge a thrown grenade, seek cover, or side-step)
 * this tick, and starts it. Returns 1 if an evasion action was started, 0
 * otherwise.
 *
 * Resolves the actor object plus its 'actv' (actor variant, actor+0x5c) and
 * 'actr' (actor, actor+0x58) tag blocks, and the current game time.
 *
 * 1. Grenade-avoidance dodge: only when the actor has a pending
 *    grenade-avoid target (short actor+0x3a8 > 0), no vehicle (actor+0x158 ==
 *    NONE), the target prop's flag (prop+0xa4) is set and its state
 *    (prop+0x38) is 0 or 1, and the 0x1e-tick dodge cooldown (actor+0x36c)
 *    has expired. Refreshes the cooldown, then gates on
 *    actor_action_allow_cover_seeking(actor,1); attempts
 *    actor_action_try_to_seek_cover, else (when the 'actr' flag 0x400000 is
 *    set) FUN_0001d3c0 toward the grenade prop.
 * 2. Selects an evasion radius from the 'actr' tag: tag+0x314 when actor+0x374
 *    is set and actor+0x378 is clear, otherwise tag+0x310. When actor+0x1ca is
 *    set and tag+0x318 exceeds *(float*)0x2533c0, the radius is clamped down to
 *    *(float*)0x253f38. If actor+0x354 <= radius the actor is outside evasion
 *    range and nothing is done.
 * 3. When actor+0x504 is clear, one RNG draw is consumed (result discarded) to
 *    keep the random stream aligned.
 * 4. If the 'actv' grenade type (tag+0x184) is 2 and
 *    actor_action_consider_grenade succeeds, clears actor+0x354 and marks the
 *    action as taken.
 * 5. Otherwise (action not yet taken): a retreat gate (b_retreat, from
 *    actor+0x358 / 'actr' flag 0x20 / the target prop's +0x122,+0x121 fields)
 *    may start a seek-cover + fire-retreat-event sequence (FUN_00046f10 event
 *    0x18); or, when the side-step gate (b_sidestep, cleared when actor+0x6c
 *    == 10 with actor+0xa0 in {2,3}) is open and actor+0x368 == 0, calls
 *    actor_action_try_to_evade and stores a timer at actor+0x368.
 *
 * Verified against delinked reference (delinked/actions.obj). Both datum_get
 * lookups (actor+0x3ac and actor+0x270) use prop_data. FUN_001d9068 at the tail
 * is the _ftol2 intrinsic, written here as (short)(int)(...). */
char actor_action_handle_evasion(int actor_handle)
{
  char *actor;
  char *actv_tag;
  char *actr_tag;
  char *prop;
  char *other_prop;
  int now;
  char status;
  char b_retreat;
  char b_sidestep;
  float radius;

  actor = (char *)datum_get(actor_data, actor_handle);
  actv_tag = (char *)tag_get(0x61637476, *(int *)(actor + 0x5c));
  actr_tag = (char *)tag_get(0x61637472, *(int *)(actor + 0x58));
  now = game_time_get();
  status = 0;

  if (*(short *)(actor + 0x3a8) > 0 && *(int *)(actor + 0x158) == -1) {
    prop = (char *)datum_get(prop_data, *(int *)(actor + 0x3ac));
    if (*(char *)(prop + 0xa4) != '\0' &&
        (*(short *)(prop + 0x38) == 0 || *(short *)(prop + 0x38) == 1) &&
        (*(int *)(actor + 0x36c) == -1 ||
         *(int *)(actor + 0x36c) + 0x1e <= now)) {
      *(int *)(actor + 0x36c) = now;
      if (actor_action_allow_cover_seeking(actor_handle, 1)) {
        if (actor_action_try_to_seek_cover(actor_handle, 0, 1)) {
          return 1;
        }
        if ((*(unsigned int *)actr_tag & 0x400000) &&
            FUN_0001d3c0(actor_handle, 5, *(int *)(actor + 0x3ac), 0)) {
          return 1;
        }
      }
    }
  }

  if (*(char *)(actor + 0x374) != '\0' && *(char *)(actor + 0x378) == '\0') {
    radius = *(float *)(actr_tag + 0x314);
  } else {
    radius = *(float *)(actr_tag + 0x310);
  }
  if (*(char *)(actor + 0x1ca) != '\0') {
    if (*(float *)(actr_tag + 0x318) > *(float *)0x2533c0 &&
        radius > *(float *)0x253f38) {
      radius = *(float *)0x253f38;
    }
  }
  if (*(float *)(actor + 0x354) <= radius) {
    return 0;
  }

  if (*(char *)(actor + 0x504) == '\0') {
    random_math_real((unsigned int *)get_global_random_seed_address());
  }

  if (*(short *)(actv_tag + 0x184) == 2 &&
      actor_action_consider_grenade(actor_handle)) {
    *(int *)(actor + 0x354) = 0;
    status = 1;
  }

  b_retreat = 1;
  b_sidestep = 1;
  if (*(char *)(actor + 0x358) != '\0' && (*(unsigned int *)actr_tag & 0x20)) {
    b_retreat = 0;
    if (*(int *)(actor + 0x270) != -1) {
      other_prop = (char *)datum_get(prop_data, *(int *)(actor + 0x270));
      if (*(char *)(other_prop + 0x122) <= 2 &&
          *(char *)(other_prop + 0x121) <= 1) {
        b_retreat = 1;
      }
    }
  }
  if (*(short *)(actor + 0x6c) == 10 &&
      (*(short *)(actor + 0xa0) == 2 || *(short *)(actor + 0xa0) == 3)) {
    b_sidestep = 0;
  }

  if (status == 0) {
    if (b_retreat != '\0' && (*(int *)(actor + 0x36c) == -1 ||
                              *(int *)(actor + 0x36c) + 0x1e <= now)) {
      *(int *)(actor + 0x36c) = now;
      if (actor_action_allow_cover_seeking(actor_handle, 0)) {
        if (random_math_real((unsigned int *)get_global_random_seed_address()) <
            *(float *)(actr_tag + 0x318)) {
          if (actor_action_try_to_seek_cover(actor_handle, 0, 1)) {
            FUN_00046f10(0x18, *(int *)(actor + 0x18),
                         actor_target_unit_index(actor_handle), -1, -1, -1, 0);
            *(int *)(actor + 0x354) = 0;
            return 1;
          }
        }
      }
    }
    if (b_sidestep == '\0') {
      return status;
    }
    if (*(short *)(actor + 0x368) != 0) {
      return status;
    }
    if (actor_action_try_to_evade(actor_handle)) {
      *(int *)(actor + 0x354) = 0;
      *(short *)(actor + 0x368) =
        (short)(int)(*(float *)(actr_tag + 0x31c) * *(float *)0x253394);
      *(char *)(actor + 0x3bb) = 1;
      return 1;
    }
    return status;
  }
  return status;
}


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

/* action_vehicle_perform (0x1b8a0) — readable C lift (restored pre-naked). */
void action_vehicle_perform(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), 0);
  object_try_and_get_and_verify_type(0, 2);
  /* test (char)eax, (char)eax -> je 0x1b8f4 */
  display_assert((char *)0x00253380, (char *)0x00253f50, 161, 1);
  system_exit(-1);
  /* cmp ecx, eax -> je 0x1b90a */
  /* test (char)ecx, (char)ecx -> jne 0x1b925 */
  /* test esi, esi -> jne 0x1b94a */
  /* test (char)eax, (char)eax -> jne 0x1bb93 */
  /* test (char)eax, (char)eax -> jne 0x1bb93 */
  FUN_0001ada0();
  /* test (char)eax, (char)eax -> je 0x1b91e */
  game_time_get();
  /* cmp eax, edx -> jl 0x1b9df */
  distance_squared3d((const float *)((char *)eax + 0xb0), (const float *)((char *)eax + 0x12c));
  /* relift: relift: fcomp dword ptr [0x253f74] */
  /* relift: cmp word ptr [edi + 0xaa], 8 -> jge 0x1b91e */
  FUN_0001aeb0(0, 0, 0, 0, (void *)0, (float *)0, (float *)0, 0, 0, 0, 0);
  /* test (char)eax, (char)eax -> je 0x1b91e */
  /* test (char)eax, (char)eax -> je 0x1ba57 */
  /* relift: cmp word ptr [edi + 0xc6], 0x1e -> jl 0x1ba60 */
  /* test (char)eax, (char)eax -> je 0x1baa5 */
  /* test (char)eax, (char)eax -> je 0x1ba97 */
  unit_board_vehicle(0, 0, 0);
  FUN_0002f1a0(0);
  /* test (char)eax, (char)eax -> je 0x1bb36 */
  FUN_0001b280(0, 0, (void *)0, (float *)((char *)eax + 0xa3), (float *)((char *)eax + 0xcc), 0, (float *)0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x1bb0c */
  actor_move_to_point(0, (float *)((char *)eax + 0xcc), 0, 0);
  /* test (char)eax, (char)eax -> je 0x1bb0c */
  /* cmp (int16_t)eax, (int16_t)ecx -> jle 0x1bb36 */
  distance_squared3d((const float *)((char *)eax + 0x12c), (void *)0);
  /* relift: relift: fcomp dword ptr [0x2533c8] */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}


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


/* FUN_0001beb0 (0x1beb0) — readable C lift (restored pre-naked). */
void FUN_0001beb0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), 0);
  /* test (char)eax, (char)eax -> je 0x1c025 */
  actor_pursuit_find_nearby_actors(0, 0);
  /* test (char)eax, (char)eax -> je 0x1bf7c */
  /* relift: cmp dword ptr [esi + 0x1d0], -1 -> jne 0x1bf19 */
  /* relift: cmp word ptr [esi + 0xaa], 0 -> jne 0x1bf35 */
  game_time_get();
  /* cmp eax, edx -> jl 0x1bf35 */
  /* test (char)eax, (char)eax -> jne 0x1c025 */
  /* test (char)eax, (char)eax -> je 0x1c01c */
  actor_move_to_prop(0, 0, 0.0f);
  /* cmp eax, -1 -> je 0x1bf35 */
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), 0);
  /* test (char)eax, (char)eax -> je 0x1bfb3 */
  /* test (char)eax, (char)eax -> je 0x1bfdf */
  /* relift: cmp word ptr [ecx + 0x32], 2 -> jl 0x1bf2e */
  /* relift: relift: fcomp dword ptr [0x253f78] */
  /* test (char)eax, (char)eax -> jne 0x1c009 */
  /* relift: relift: fcomp dword ptr [0x253f30] */
  /* test (char)eax, 0x41 -> jne 0x1c009 */
  FUN_0002f1a0(0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}


/* FUN_0001cda0 (0x1cda0) — readable C lift (restored pre-naked). */
void FUN_0001cda0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), 0);
  /* cmp (int16_t)esi, 1 -> jne 0x1cddb */
  /* test (char)ebx, (char)ebx -> je 0x1cddb */
  /* cmp (int16_t)edi, 2 -> je 0x1ce01 */
  /* cmp (int16_t)edi, 1 -> jne 0x1cdeb */
  /* test (char)ebx, (char)ebx -> jne 0x1ce01 */
  /* cmp (int16_t)ecx, 2 -> je 0x1ce07 */
  /* cmp (int16_t)ecx, 1 -> jne 0x1ce0d */
  /* test (char)ebx, (char)ebx -> je 0x1ce0d */
  /* test (char)ecx, (char)ecx -> je 0x1ce26 */
  /* cmp eax, -1 -> jne 0x1ce44 */
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), 0);
  /* test (char)eax, (char)eax -> je 0x1ceca */
  /* cmp (int16_t)eax, 2 -> jl 0x1ceac */
  /* cmp (int16_t)eax, 3 -> jg 0x1ceac */
  actor_perception_find_prop_pathfinding_location(0, 0);
  actor_has_accessible_firing_position(0, (float *)(uintptr_t)eax, 0, 0);
  /* relift: cmp word ptr [eax + 0x6e], 3 -> jge 0x1cedf */
  /* relift: cmp word ptr [eax + 0x15e], 0 -> jle 0x1ceef */
  /* relift: cmp word ptr [eax + 0x15e], 4 -> jne 0x1cf02 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}


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



/* actor_action_find_escape_from_danger (0x1e360) — readable C lift (restored pre-naked). */
void actor_action_find_escape_from_danger(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;
  int local_10 = 0;
  int local_c = 0;

  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), 0);
  object_get_and_verify_type(0, 3);
  tag_get('tinu', *(int *)(eax));
  display_assert((char *)0x002546a8, (char *)0x002544b0, 1393, 1);
  system_exit(-1);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1e69b */
  magnitude3d((float *)0);
  /* relift: relift: fcomp dword ptr [0x2546a4] */
  magnitude3d((float *)0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  magnitude3d((void *)0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  tag_get('rtca', 0);
  actor_move_try_evasion_vector(0, (float *)0, 0.0f, 0.0f, (char *)0, (void *)0);
  FUN_0010cd40((void *)0, (float *)((char *)eax + 0x2b0), (void *)0);
  /* test (char)eax, 0x41 -> je 0x1e5b7 */
  actor_move_try_evasion_vector(0, (void *)0, local_c, local_10, (void *)0, (void *)0);
  FUN_0010cd40((void *)0, (float *)((char *)eax + 0x2b0), (void *)0);
  /* test (char)eax, 0x41 -> jne 0x1e60c */
  /* test dl, dl -> je 0x1e689 */
  /* test (char)ecx, (char)ecx -> je 0x1e679 */
  /* cmp dl, (char)eax -> ja 0x1e671 */
  /* relift: relift: fcomp dword ptr [0x2533e4] */
  /* test (char)eax, 0x41 -> je 0x1e671 */
  /* cmp (char)ebx, (char)ecx -> ja 0x1e66b */
  /* relift: cmp byte ptr [ebp - 3], dl -> ja 0x1e66b */
  /* relift: relift: fcomp dword ptr [0x2546a0] */
  /* test (char)ecx, (char)ecx -> je 0x1e69b */
  /* test esi, esi -> je 0x1e6b0 */
  /* test eax, eax -> je 0x1e6b0 */
  /* test eax, eax -> jne 0x1e6d3 */
  display_assert((char *)0x00254648, (char *)0x002544b0, 1484, 1);
  system_exit(-1);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)ebp;
  (void)local_10;
  (void)local_c;
}


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


/* FUN_00020990 (0x20990) — readable C lift. */
char FUN_00020990(int actor_handle)
{
  char *actor;
  char *debug;
  int16_t motion_state;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  debug = (char *)0x331f58 + (actor_handle & 0xffff) * 0x657c;
  *(int *)(debug + 0x168) = game_time_get();
  *(int16_t *)(debug + 0x16c) = 0;
  *(int16_t *)(debug + 0x188) = 0;
  *(char *)(debug + 0x16e) = 0;

  motion_state = *(int16_t *)(actor + 0x280);
  if (motion_state == 0) {
    *(int16_t *)(debug + 0x16c) = 0;
    return 0;
  }
  if (*(char *)(actor + 0x287) == 0) {
    *(int16_t *)(debug + 0x16c) = 1;
    return *(char *)(debug + 0xfd);
  }
  return 0;
}


