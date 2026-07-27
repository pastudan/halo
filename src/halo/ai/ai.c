/* ai.c — AI subsystem top-level lifecycle and query functions.
 *
 * Corresponds to ai.obj (XBE address range ~0x3f5f0–0x425b0).
 * Implements initialize, dispose, dispose_from_old_map, place,
 * ai_handle_unit_approach, game_allegiance_apply_change,
 * unit_vehicle_board_notify, ai_initialize_for_new_map,
 * ai_update, ai_clump, and enemies_can_see_player entry points.
 */

/* FUN_0003f5f0: per-tick AI actor activation sweep.
 * Called from ai_update on the first-frame/map-load branch.
 * Copies ai_globals[6..7] (int16_t) into ai_globals[4..5], then clears
 * both ai_globals[6..7] and the byte flag at ai_globals[3].
 * Iterates all active player-actors (flag=1) via
 * encounter_iterator_next/FUN_00059b50. For each actor record:
 *   - if record+0xb is nonzero: calls actor_erase(actor_handle, 0)
 *     to delete/dispose the actor entry.
 *   - if record+0xb is zero and record+0x6a > 0: calls FUN_0003ec80(@esi)
 *     to activate the actor (full AI init sequence).
 * The datum handle comes from iter offset 0x14 (stored by FUN_00059b50).
 * Confirmed: void(void), called from ai_update at 0x41206 with no args.
 * Confirmed: FUN_0003ec80 takes @esi register arg (MOV ESI,[EBP-8]; CALL).
 * Confirmed: actor_erase is cdecl with 2 stack args (PUSH 0; PUSH EAX; CALL;
 * ADD ESP,8). */
void FUN_0003f5f0(void)
{
  char *g;
  char iter[0x1c]; /* extended AI actor iterator */
  char *record;

  g = *(char **)0x632574;

  /* rotate scheduling counters: copy [6..7] into [4..5], clear [6..7] and flag
   * [3] */
  *(int16_t *)(g + 4) = *(int16_t *)(g + 6);
  *(int16_t *)(g + 6) = 0;
  *(char *)(g + 3) = 0;

  /* iterate over all active player-actors */
  encounter_iterator_next(iter, 1);
  record = (char *)FUN_00059b50(iter);
  while (record != 0) {
    if (*(char *)(record + 0xb) != 0) {
      /* actor marked for deletion — dispose it */
      actor_erase(*(int *)(iter + 0x14), 0);
    } else {
      if (*(int16_t *)(record + 0x6a) > 0) {
        /* actor ready for activation — full init via @esi */
        FUN_0003ec80(*(int *)(iter + 0x14));
      }
    }
    record = (char *)FUN_00059b50(iter);
  }
}

/* ai_initialize: allocate AI globals and initialize all AI subsystems.
 * Allocates 0x8dc bytes via game_state_malloc, stores the pointer at
 * global 0x632574, zeroes the block, then calls 9 subsystem init
 * functions in order. The last call (actor_move_get_avoidance_direction) is a
 * tail-call (JMP in the original binary). Confirmed: PUSH order for
 * game_state_malloc("ai globals", NULL, 0x8dc); assert string "ai_globals" at
 * line 0x8c (140) of ai.c. */
void ai_initialize(void)
{
  void *globals = game_state_malloc("ai globals", 0, 0x8dc);
  *(void **)0x632574 = globals;
  if (!globals) {
    display_assert("ai_globals", "c:\\halo\\SOURCE\\ai\\ai.c", 0x8c, 1);
    system_exit(-1);
  }
  csmemset(*(void **)0x632574, 0, 0x8dc);
  ai_debug_initialize();
  set_real_point3d();
  FUN_0005df80();
  actors_initialize();
  FUN_00064100();
  FUN_00058eb0();
  FUN_000540b0();
  ai_communication_initialize();
  actor_move_get_avoidance_direction();
}

/* ai_dispose: shut down all AI subsystems in reverse-init order.
 * Calls eight subsidiary dispose functions and tail-calls the last one.
 * Confirmed: 7 CALL + 1 JMP (tail call to ai_debug_dispose) in disassembly. */
void ai_dispose(void)
{
  ai_communication_dispose();
  ai_profile_dispose();
  encounters_dispose();
  FUN_00064140();
  actors_dispose();
  FUN_0005df90();
  ai_debug_lineoffire_success();
  ai_debug_dispose();
}

/* ai_dispose_from_old_map: release per-map AI state when leaving a map.
 * Calls eight subsidiary dispose_from_old_map helpers, then clears the
 * AI active flag (byte at offset 1 in the AI globals struct) to mark the
 * subsystem inactive. Confirmed: 8 CALLs + MOV EAX,[0x632574] / MOV
 * byte ptr [EAX+1],0 in disassembly. */
void ai_dispose_from_old_map(void)
{
  ai_communication_dispose_from_old_map();
  ai_profile_dispose_from_old_map();
  encounter_compute_activation_cluster_bit_vector();
  FUN_00064160();
  actors_dispose_from_old_map();
  FUN_0005dfb0();
  ai_debug_lineofsight_reset();
  ai_debug_dispose_from_old_map();
  /* clear the AI active flag (offset 1 in the AI globals block) */
  *(char *)(*(int *)0x632574 + 1) = 0;
}

/* ai_place: JMP thunk — forwards directly to encounters_create_for_new_map.
 * The binary at 0x3f760 is a single JMP instruction; the real body
 * lives at 0x5ddc0 (not yet identified as a named symbol). */
void ai_place(void)
{
  encounters_create_for_new_map();
}

/* 0x3f770 — Set the first byte of the AI globals block.
 * Asserts ai_globals is non-null, then writes param_1 to the first byte. */
void ai_globals_ai_active(char param_1)
{
  if (*(char **)0x632574 == NULL) {
    display_assert("ai_globals", "c:\\halo\\SOURCE\\ai\\ai.c", 0x13a, 1);
    system_exit(-1);
  }
  **(char **)0x632574 = param_1;
}

/* 0x3f7b0 — Set byte at ai_globals+0x10. */
void ai_globals_dialogue_triggers_enabled(char param_1)
{
  if (*(char **)0x632574 == NULL) {
    display_assert("ai_globals", "c:\\halo\\SOURCE\\ai\\ai.c", 0x143, 1);
    system_exit(-1);
  }
  *(char *)(*(char **)0x632574 + 0x10) = param_1;
}

/* 0x3f800 — Set byte at ai_globals+0x3b4. */
void ai_globals_grenades_enabled(char param_1)
{
  if (*(char **)0x632574 == NULL) {
    display_assert("ai_globals", "c:\\halo\\SOURCE\\ai\\ai.c", 0x14c, 1);
    system_exit(-1);
  }
  *(char *)(*(char **)0x632574 + 0x3b4) = param_1;
}

/* 0x3f850 — Decode a force-type enum into force_major/is_random/random_chance.
 *
 * Translates an AI force-type code (param_1) into a trio of output values:
 *   force_major   — non-zero when the force is a "major" (definitive) event
 *   is_random     — non-zero when the force has a random-chance component
 *   random_chance — the probability [0,1] fetched from game globals difficulty
 *
 * Force-type mapping (from assert string: "force_major && is_random &&
 * random_chance"): 1 (default): is_random=1, random_chance=FUN_000b5590(0x1c)
 * (normal random) 2:           is_random=1, random_chance=FUN_000b5590(0x1d)
 * (variant 1) 3:           is_random=1, random_chance=FUN_000b5590(0x1e)
 * (variant 2) 4:           is_random=0, force_major=0  (non-random, non-major)
 *   5:           is_random=0, force_major=1  (non-random, major)
 *
 * Confirmed: 4 cdecl stack args; no register args; no return value.
 * Confirmed: ADD ESP,0x14 after display_assert+system_exit pair at 0x3f888.
 * Confirmed: MOVSX EAX, word [EBP+8]; DEC EAX; CMP EAX,3; JA default (jump
 * table 1-4). Confirmed: ESI=[EBP+0x10]=is_random, EDI=[EBP+0xc]=force_major,
 * EBX=[EBP+0x14]=random_chance. Confirmed: case 1 at 0x3f8b2: MOV [ESI],1; PUSH
 * 0x1d; CALL FUN_000b5590; FSTP [EBX]. Confirmed: case 2 at 0x3f8c6: MOV
 * [ESI],1; PUSH 0x1e; CALL; FSTP [EBX]. Confirmed: case 3 at 0x3f89c: MOV
 * [ESI],0; MOV [EDI],0. Confirmed: case 4 at 0x3f8a7: MOV [ESI],0; MOV [EDI],1.
 * Confirmed: default at 0x3f8da: MOV [ESI],1; PUSH 0x1c; CALL; FSTP [EBX].
 */
void ai_get_major_upgrade_chance(int16_t param_1, char *force_major,
                                 char *is_random, float *random_chance)
{
  if ((force_major == NULL) || (is_random == NULL) || (random_chance == NULL)) {
    display_assert("force_major && is_random && random_chance",
                   "c:\\halo\\SOURCE\\ai\\ai.c", 0x158, 1);
    system_exit(-1);
  }
  switch (param_1) {
  case 3:
    *is_random = 0;
    *force_major = 0;
    return;
  case 4:
    *is_random = 0;
    *force_major = 1;
    return;
  case 1:
    *is_random = 1;
    *random_chance = FUN_000b5590(0x1d);
    return;
  case 2:
    *is_random = 1;
    *random_chance = FUN_000b5590(0x1e);
    return;
  default:
    *is_random = 1;
    *random_chance = FUN_000b5590(0x1c);
    return;
  }
}

/* ai_erase: erase AI actors matching an encounter/squad/squad-group filter.
 * Guards on AI globals active flag (*(char*)(ai_globals+1) != 0).
 * If param_1 == -1 (all encounters): iterates all actors via
 *   encounter_iterator_next (flag=0) + FUN_00059b50; erases each via
 *   actor_erase(iter+0x14 handle, param_4).
 * Else: initialises a per-encounter actor iterator via
 *   encounter_actor_iterator_new(&iter, param_1) +
 * encounter_actor_iterator_next; for each actor, skips if actor+0x3c != param_2
 * (unless param_2==-1) or actor+0x3a != param_3 (unless param_3==-1); erases
 * matching actors via actor_erase(iter[1] handle, param_4).
 *
 * Stack layout (SUB ESP,0x28):
 *   [EBP-0x28..EBP-0x15]: enc_iter[0x1c] (encounter iterator, all-branch)
 *   [EBP-0x14]:           enc_iter+0x14 (actor handle field in iterator)
 *   [EBP-0x0c..EBP-0x09]: actor_iter[2] (encounter-actor iterator,
 * single-branch) [EBP-0x08]:           actor_iter[1] (actor handle, 4 bytes
 * into actor_iter)
 *
 * Confirmed: PUSH 0x0 at 0x3f992 → encounter_iterator_next flag=0.
 * Confirmed: MOVSX+CMP for short fields at actor+0x3c (param_2) and
 *            actor+0x3a (param_3).
 * Confirmed: actor_erase args: PUSH param_4, PUSH actor_handle (cdecl). */
void ai_erase(int param_1, int param_2, int param_3, int param_4)
{
  char enc_iter[0x1c]; /* encounter iterator for the all-encounters branch */
  int actor_iter[2]; /* encounter-actor iterator: [0]=state, [1]=handle */
  int has_more;
  int actor;

  if (*(char *)(*(int *)0x632574 + 1) == 0) {
    return;
  }

  if (param_1 == -1) {
    /* iterate all actors across all encounters */
    encounter_iterator_next(enc_iter, 0);
    has_more = FUN_00059b50(enc_iter);
    while (has_more != 0) {
      actor_erase(*(int *)(enc_iter + 0x14), (char)param_4);
      has_more = FUN_00059b50(enc_iter);
    }
  } else {
    /* iterate actors within the specified encounter, applying filters */
    encounter_actor_iterator_new(actor_iter, param_1);
    actor = encounter_actor_iterator_next(actor_iter);
    while (actor != 0) {
      if ((param_2 == -1 || *(short *)(actor + 0x3c) == param_2) &&
          (param_3 == -1 || *(short *)(actor + 0x3a) == param_3)) {
        actor_erase(actor_iter[1], (char)param_4);
      }
      actor = encounter_actor_iterator_next(actor_iter);
    }
  }
}

/* ai_release_inactive_swarms: count and erase swarm units, format a result
 * description.
 *
 * Iterates all AI actors via encounter_iterator_next (flag=0) + FUN_00059b50.
 * For each actor record where:
 *   record[6] != 0  (actor is active/alive)
 *   record[8] == 0  (not in some suppressed state)
 *   *(int*)(record+0xc) != -1  (has a valid reference)
 * accumulates *(short*)(record+0x1e) into swarm_count, then erases the actor
 * via actor_erase(handle, 1).
 *
 * After iteration: formats "%d swarm units" into result_description via
 * crt_sprintf, sets *more_to_release = 0, returns 1 if swarm_count > 0.
 *
 * Stack layout (SUB ESP,0x20):
 *   [EBP-0x20..EBP-0xd]: iter[0x14] (encounter iterator, 20-byte body)
 *   [EBP-0xc]:           iter+0x14  (actor handle stored by FUN_00059b50)
 *   [EBP-0x4]:           local_8    (initialized to 0; base for swarm_count/SI)
 *
 * Confirmed: assert string "result_description && more_to_release", line
 * 0x1f7=503. Confirmed: encounter_iterator_next flag=0 (PUSH 0x0 at 0x3fa81).
 * Confirmed: MOV EDX,[EBP-0xc]; PUSH EDX as actor_erase first arg (handle at
 * iter+0x14). Confirmed: ADD SI,word[EAX+0x1e] accumulates short field at
 * record+0x1e. Confirmed: MOVSX ECX,SI; PUSH ECX; PUSH fmt; PUSH EDI →
 * crt_sprintf(result_desc,...). Confirmed: XOR EAX,EAX; TEST SI,SI; SETG AL →
 * returns 1 if swarm_count > 0. Confirmed: MOV byte[EBX],0x0 → *more_to_release
 * = 0. */
int ai_release_inactive_swarms(int result_description, char *more_to_release)
{
  char iter[0x1c]; /* extended AI actor iterator; fields through iter+0x18 */
  int record;
  short swarm_count;

  swarm_count = 0;

  if ((result_description == 0) || (more_to_release == (char *)0x0)) {
    display_assert("result_description && more_to_release",
                   "c:\\halo\\SOURCE\\ai\\ai.c", 0x1f7, 1);
    system_exit(-1);
  }

  encounter_iterator_next(iter, 0);
  record = FUN_00059b50(iter);
  while (record != 0) {
    if ((*(char *)(record + 6) != '\0') && (*(char *)(record + 8) == '\0') &&
        (*(int *)(record + 0xc) != -1)) {
      swarm_count = (short)(swarm_count + *(short *)(record + 0x1e));
      actor_erase(*(int *)(iter + 0x14), 1);
    }
    record = FUN_00059b50(iter);
  }

  crt_sprintf((char *)result_description, "%d swarm units", (int)swarm_count);
  *more_to_release = 0;
  return swarm_count > 0;
}

/* Compare two AI records for sorting. Primary key: int at offset 8 (ascending).
   Secondary key: unsigned byte at offset 0 (ascending).
   Returns 1 if param_1 < param_2, -1 if param_1 > param_2, 0 if equal. */
int FUN_0003fb00(unsigned char *param_1, unsigned char *param_2)
{
  if (*(int *)(param_2 + 8) < *(int *)(param_1 + 8)) {
    return 1;
  }
  if (*(int *)(param_2 + 8) > *(int *)(param_1 + 8)) {
    return 0xffffffff;
  }
  if (*param_2 < *param_1) {
    return 0xffffffff;
  }
  return (*param_1 < *param_2);
}

/* ai_handle_unit_approach: test whether a unit is approaching a valid
 * target for an AI actor, and optionally record the approach.
 * Looks up the actor via actor_data, checks the unit against
 * object_get_and_verify_type (type 3 = unit), tests team friendship via
 * game_allegiance_get_team_is_friendly, and returns true (1) when the
 * teams are NOT friendly (i.e. the unit is an enemy worth approaching).
 * If flag is non-zero and the check passes, sets the approach-active
 * flag at actor+0x2ed by calling FUN_00036e30.
 * Confirmed: 3 args (PUSH count), no ADD ESP after final CALL, bool
 * return via AL; ADD ESP,8 after each of the two inner calls. */
bool ai_handle_unit_approach(int ai_handle, int unit_handle, bool flag)
{
  char *actor;
  char *unit;
  bool result;

  actor = datum_get(actor_data, ai_handle);
  result = 0;
  if (unit_handle != -1) {
    unit = object_get_and_verify_type(unit_handle, 3);
    if (*(int *)(unit + 0x1c8) != -1) {
      /* game_allegiance_get_team_is_friendly returns true when friendly;
       * we return true (enemy) only when NOT friendly. */
      if (!game_allegiance_get_team_is_friendly(*(int16_t *)(unit + 0x68),
                                                *(int16_t *)(actor + 0x3e))) {
        result = 1;
        if (flag) {
          /* set the approach-active flag at actor+0x2ed */
          FUN_00036e30(ai_handle);
        }
      }
    }
  }
  return result;
}

/* ai_get_responsible_unit: resolve a vehicle unit handle to an occupant handle.
 *
 * Given a vehicle unit handle, returns the handle of a key occupant:
 *  - If prefer_passenger is nonzero and the vehicle has a passenger
 *    (unit+0x2d8 != -1), resolve to the passenger handle.
 *  - Otherwise, if the vehicle has a driver (unit+0x2d4 != -1), resolve
 *    to the driver handle.
 *  - If no resolution changed the handle (remains -1 or unchanged), returns
 *    the resolved handle directly.
 *
 * Debug filter (applied only in non-multiplayer with debug flag set):
 *  - If game_connection() != 0 (multiplayer): skip filter, return resolved.
 *  - If byte[0x5ac9c6] == 0 (AI debug flag off): skip filter, return resolved.
 *  - If the resolved unit has no rider (unit+0x1c8 == -1): skip filter,
 *    return resolved.
 *  - Otherwise (debug on, singleplayer, resolved unit has a rider): return -1.
 *
 * Confirmed: param_1=[EBP+8] (int), prefer_passenger=[EBP+C] (char).
 * Returns int in EAX. */
int ai_get_responsible_unit(int unit_handle, char prefer_passenger)
{
  void *obj;
  int resolved;
  int candidate;

  if (unit_handle == -1) {
    return -1;
  }
  obj = object_try_and_get_and_verify_type(unit_handle, 3);
  if (obj == NULL) {
    return -1;
  }

  resolved = unit_handle;
  if (prefer_passenger != '\0') {
    candidate = *(int *)((char *)obj + 0x2d8);
    if (candidate != -1) {
      resolved = candidate;
      goto check_debug;
    }
  }
  candidate = *(int *)((char *)obj + 0x2d4);
  if (candidate != -1) {
    resolved = candidate;
  }

check_debug:
  if (resolved == -1) {
    return resolved;
  }
  if (game_connection() != 0) {
    return resolved;
  }
  if (*(char *)0x5ac9c6 == '\0') {
    return resolved;
  }
  obj = object_get_and_verify_type(resolved, 3);
  if (*(int *)((char *)obj + 0x1c8) == -1) {
    return resolved;
  }
  return -1;
}

/* ai_handle_death: Notify AI systems when a unit exits a vehicle.
 *
 * param_1 (unit_handle): the unit that just exited.
 * param_2: passed to ai_get_responsible_unit as unit_handle for
 * vehicle-occupant resolution. param_3: vehicle/context handle; used to control
 * prefer_passenger (word !=9) and forwarded as param5 of FUN_00046f10.
 *
 * Resolves the occupant from param_2 via ai_get_responsible_unit, determines a
 * relationship code (0=same unit, 2=enemy, 3=friendly, or 0xffffffff if no
 * valid occupant), then notifies the AI communication system (FUN_00046f10),
 * clears encounter references (ai_conversation_unit_died), and updates
 * encounter kill counts (encounters_unit_died).
 *
 * Confirmed: [EBP+8]=unit_handle (int), [EBP+C]=param_2 (int),
 *            [EBP+10]=param_3 compared as word ptr. */
void ai_handle_death(int unit_handle, int param_2, short param_3)
{
  int relation;
  int resolved;
  void *obj_unit;
  void *obj_resolved;

  resolved = ai_get_responsible_unit(param_2, (char)(param_3 != 9));
  relation = 0;
  if (unit_handle == resolved) {
    relation = 1;
  } else if (resolved != -1) {
    obj_unit = object_get_and_verify_type(unit_handle, 3);
    obj_resolved = object_get_and_verify_type(resolved, 3);
    relation = (game_allegiance_get_team_is_friendly(
                  *(short *)((char *)obj_unit + 0x68),
                  *(short *)((char *)obj_resolved + 0x68)) != 0) +
               2;
  }
  FUN_00046f10(0, unit_handle, resolved, relation, (int)param_3, -1, 0);
  ai_conversation_unit_died(unit_handle, '\0');
  encounters_unit_died(unit_handle);
}

/*
 * ai_handle_killing_spree: AI killing spree threshold check and notification.
 *
 * Given a unit handle and a killing spree count, checks whether the count
 * meets the threshold to trigger a killing-spree AI communication event.
 * Threshold is 3 if the unit has no rider (unit+0x1c8 == 0xffffffff), or
 * 5 if it does. When the debug flag at 0x5aca60 is set, logs the spree count
 * to the console. If the threshold is met, fires FUN_00046f10 with type=1
 * and returns 1; otherwise returns 0.
 *
 * Confirmed: [EBP+8]=unit_handle (int), [EBP+C]=killing_spree_count (short),
 *            threshold = (uVar1 != 0xffffffff)*2 + 3 = 3 (no rider) or 5
 * (rider).
 */
char ai_handle_killing_spree(int unit_handle, short killing_spree_count)
{
  char buf[512];
  void *obj;
  unsigned int rider;
  short threshold;

  obj = object_get_and_verify_type(unit_handle, 3);
  rider = *(unsigned int *)((char *)obj + 0x1c8);
  threshold = (short)((rider != 0xffffffffu) * 2 + 3);

  if (*(char *)0x5aca60 != '\0') {
    if (rider == 0xffffffffu) {
      ai_debug_describe_actor(*(int *)((char *)obj + 0x1a4), unit_handle, 1,
                              buf, 0x200);
    } else {
      crt_sprintf(buf, "player%d", (unsigned int)(rider & 0xffff));
    }
    console_printf(0, "%s killing spree: %d", buf, (int)killing_spree_count);
  }

  if (killing_spree_count >= threshold) {
    FUN_00046f10(1, unit_handle, -1, -1, -1, -1, 0);
    return 1;
  }
  return 0;
}

/* game_allegiance_apply_change: apply an allegiance change between two
 * teams, updating all matching actor records in the AI actor iterator.
 * Iterates over all active player-actors via
 * encounter_iterator_next/FUN_00059b50; for each actor whose team matches
 * team_a or team_b, walks the actor's clump items via FUN_00064540/FUN_00064570
 * and applies the friendship and force flags. Confirmed: 4 args via PUSH count
 * + ADD ESP,0x18 cleanup at 0x40068. Operand sizes confirmed: team_a/team_b as
 * int16_t (MOVSX + CMP AX,DI); friendship/force as char (MOV byte ptr).
 *
 * Stack layout (EBP-based, SUB ESP,0x24):
 *   [EBP-0x24..EBP-0x09]: ai_actor_iter (0x1c bytes extended iterator)
 *   [EBP-0x08]:           clump_item_iter[0] (current clump-item handle)
 *   [EBP-0x04]:           clump_item_iter[1] (next clump-item handle)
 * Note: [EBP-0x10] == ai_actor_iter.field_0x14 (current actor handle);
 *       the decompiler names it 'local_14' because it overlaps the iter. */
void game_allegiance_apply_change(int16_t team_a, int16_t team_b,
                                  char friendship, char force)
{
  char iter[0x1c]; /* extended AI actor iterator; see encounter_iterator_next */
  int clump_iter[2]; /* clump-item walk: [0]=current handle, [1]=next */
  int16_t matched_team;
  int actor;
  int clump_item;

  /* optional debug console print */
  if (*(char *)0x5aca55) {
    const char *perm = force ? " permanently" : "";
    const char *rel = friendship ? "broken" : "reformed";
    console_printf(0, "allegiance between teams %s and %s %s%s",
                   ((const char **)0x2efdf8)[team_a],
                   ((const char **)0x2efdf8)[team_b], rel, perm);
  }

  /* initialise iterator over all active player-actors (flag=1) */
  encounter_iterator_next(iter, 1);
  actor = FUN_00059b50(iter);
  while (actor != 0) {
    /* check if this actor belongs to team_a or team_b */
    matched_team = team_b;
    if (*(int16_t *)(actor + 0x3e) == team_a) {
      matched_team = team_b;
    } else if (*(int16_t *)(actor + 0x3e) == team_b) {
      matched_team = team_a;
    } else {
      goto next_actor;
    }
    if (matched_team == -1) {
      goto next_actor;
    }

    /* walk this actor's clump items, using actor handle from iter.field_0x14 */
    FUN_00064540(clump_iter, *(int *)(iter + 0x14));
    clump_item = FUN_00064570(clump_iter);
    while (clump_item != 0) {
      if (*(int16_t *)(clump_item + 0x12) == matched_team) {
        if (!force) {
          /* mark clump item fields +0x61 and +0x62 */
          *(char *)(clump_item + 0x61) = 1;
          *(char *)(clump_item + 0x62) = 1;
        }
        if (!friendship || force) {
          *(char *)(clump_item + 0x60) = friendship;
          *(char *)(clump_item + 0xa4) = actor_get_perception_knowledge(
            *(int *)(iter + 0x14), clump_iter[0]);
          *(float *)(clump_item + 0x50) = actor_compute_prop_target_weight(
            *(int *)(iter + 0x14), clump_iter[0]);
        }
      }
      clump_item = FUN_00064570(clump_iter);
    }

  next_actor:
    actor = FUN_00059b50(iter);
  }
}

/* 0x40280 — Update clump-item perception fields for all active AI actors.
 * Iterates all active actors; for each actor's clump items, retrieves the
 * unit's team, checks friendliness/hostility against the actor's team,
 * and computes perception visibility and distance. */
void ai_update_team_status(void)
{
  char iter[0x1c];
  int clump_iter[2];
  int actor;
  int clump_item;
  int unit;
  short team;

  encounter_iterator_next(iter, 1);
  actor = FUN_00059b50(iter);
  while (actor != 0) {
    FUN_00064540(clump_iter, *(int *)(iter + 0x14));
    clump_item = FUN_00064570(clump_iter);
    while (clump_item != 0) {
      unit = (int)object_get_and_verify_type(*(int *)(clump_item + 0x18), 3);
      team = *(short *)(unit + 0x68);
      *(short *)(clump_item + 0x12) = team;
      *(char *)(clump_item + 0x60) = game_allegiance_get_team_is_friendly(
        *(short *)(actor + 0x3e), (int)team);
      *(char *)(clump_item + 0x61) = game_team_is_ally(
        *(short *)(actor + 0x3e), *(short *)(clump_item + 0x12));
      *(char *)(clump_item + 0xa4) =
        actor_get_perception_knowledge(*(int *)(iter + 0x14), clump_iter[0]);
      *(float *)(clump_item + 0x50) =
        actor_compute_prop_target_weight(*(int *)(iter + 0x14), clump_iter[0]);
      clump_item = FUN_00064570(clump_iter);
    }
    actor = FUN_00059b50(iter);
  }
}

/*
 * ai_handle_bump: Remove AI encounter relationships between two units.
 *
 * param_1: actor/unit handle (the acting unit; provides the encounter via
 * +0x1a4). param_2: vehicle or unit handle to resolve; if the resolved unit has
 * a driver (unit+0x2d4 != -1), the driver handle replaces param_2.
 *
 * Conditions that skip the encounter removal:
 *   - param_2 == -1 or try_and_get resolves NULL.
 *   - The resolved handle is still -1 after driver promotion.
 *   - game_connection() == 0 AND DAT_005ac9c6 != '\0' AND rider (unit+0x1c8) !=
 * -1.
 *   - word at (resolved_unit + 0x64) != 0.
 *
 * When all conditions pass, calls FUN_00064b40 to look up the slot index,
 * then actor_handle_unit_effect(encounter_handle, slot_index, 0) on both
 * directions (param_1's encounter vs param_2, and param_2's encounter vs
 * param_1).
 *
 * Confirmed: [EBP+8]=param_1 (int), [EBP+C]=param_2 (int), [EBP+10]=velocity_ptr (ignored).
 * The third arg is pushed by FUN_001a0a40 but never accessed by this function.
 */
void ai_handle_bump(int param_1, int param_2, float *velocity_ptr)
{
  void *obj2;
  void *obj1;
  int slot;
  int enc;

  if (param_2 == -1) {
    return;
  }
  obj2 = object_try_and_get_and_verify_type(param_2, 3);
  if (obj2 == NULL) {
    return;
  }
  /* promote param_2 to driver if present */
  if (*(int *)((char *)obj2 + 0x2d4) != -1) {
    param_2 = *(int *)((char *)obj2 + 0x2d4);
  }
  if (param_2 == -1) {
    return;
  }
  /* network + rider guard: skip if standalone + rider occupied */
  if (game_connection() == 0 && *(char *)0x5ac9c6 != '\0') {
    obj2 = object_get_and_verify_type(param_2, 3);
    if (*(int *)((char *)obj2 + 0x1c8) != -1) {
      return;
    }
  }
  /* skip if field_64 word is non-zero */
  obj2 = object_get_and_verify_type(param_2, 3);
  if (*(short *)((char *)obj2 + 0x64) != 0) {
    return;
  }

  /* remove param_1's encounter entry for param_2 */
  obj1 = object_get_and_verify_type(param_1, 3);
  enc = *(int *)((char *)obj1 + 0x1a4);
  if (enc != -1) {
    slot = FUN_00064b40(enc, param_2, 1, 0);
    if (slot != -1) {
      actor_handle_unit_effect(*(int *)((char *)obj1 + 0x1a4), slot, 0);
    }
  }

  /* remove param_2's encounter entry for param_1 */
  enc = *(int *)((char *)obj2 + 0x1a4);
  if (enc != -1) {
    slot = FUN_00064b40(enc, param_1, 1, 0);
    if (slot != -1) {
      actor_handle_unit_effect(*(int *)((char *)obj2 + 0x1a4), slot, 0);
    }
  }
}

/* FUN_00040570: spawn AI actors into vehicle seats from pending vehicle list.
 * Called each tick from ai_update. Iterates the vehicle spawn queue stored
 * in the AI globals block: a count at offset +0x8b8 (int16_t) and an array
 * of object handles starting at offset +0x8bc. For each queued vehicle,
 * looks up its unit tag definition and walks the tag_block at tag+0x2e4
 * (element size 0x11c). For each seat element with a valid actor variant
 * tag index at element+0x104, creates an actor via FUN_0003f030 using the
 * vehicle's world position as the starting location, then boards the new
 * actor's unit into the vehicle at the corresponding seat index.
 * Clears the queue count to zero after processing.
 *
 * Confirmed: void(void) — no args, no return value.
 * Confirmed: outer loop uses CMP SI (16-bit comparison).
 * Confirmed: inner loop counter sign-extended via MOVSX EAX,AX.
 * Confirmed: csmemset size 0x1c, word at buffer+0x1a = 0xffff.
 * Confirmed: FUN_0003f030 args: 6 pushes, ADD ESP,0x2c (cleans 6 args + prior
 * 5). Confirmed: unit_board_vehicle args: PUSH EDX(seat), PUSH EDI(vehicle),
 * PUSH EAX(unit). */
void FUN_00040570(void)
{
  int g;
  int vehicle_handle;
  char *unit_obj;
  char *tag_data;
  int *seats_block;
  char *seat_element;
  int actor_handle;
  char *actor;
  char starting_location[0x1c];
  int16_t i;
  int16_t j;

  g = *(volatile int *)0x632574;
  if (*(int16_t *)(g + 0x8b8) < 1) {
    *(int16_t *)(g + 0x8b8) = 0;
    return;
  }

  for (i = 0; i < *(int16_t *)(g + 0x8b8); i++) {
    g = *(volatile int *)0x632574;
    vehicle_handle = *(int *)(g + 0x8bc + (int16_t)i * 4);
    unit_obj = object_get_and_verify_type(vehicle_handle, 3);
    tag_data = tag_get(0x756e6974, *(int *)unit_obj);
    seats_block = (int *)(tag_data + 0x2e4);

    for (j = 0; (int)j < *seats_block; j++) {
      seat_element = tag_block_get_element(seats_block, (int)j, 0x11c);
      if (*(int *)(seat_element + 0x104) != -1) {
        csmemset(starting_location, 0, 0x1c);
        *(int16_t *)(starting_location + 0x1a) = (int16_t)0xffff;
        object_get_world_position(vehicle_handle,
                                  (vector3_t *)starting_location);
        actor_handle = FUN_0003f030(*(int *)(seat_element + 0x104), -1, -1,
                                    starting_location, 0, 0);
        if (actor_handle != -1) {
          actor = datum_get(actor_data, actor_handle);
          unit_board_vehicle(*(int *)(actor + 0x18), vehicle_handle, j);
        }
      }
    }
  }

  *(int16_t *)(*(volatile int *)0x632574 + 0x8b8) = 0;
}

/* ai_create_mounted_weapons_for_unit: enqueue a vehicle unit handle into the AI
 * mounted-weapon pending spawn list. Checks the AI-initialized guard at
 * globals+0x1, then appends param_1 to the array at globals+0x8bc (capacity 8,
 * count int16_t at globals+0x8b8) if there is room. If the list is full, logs a
 * warning via error(). Called from unit_new (one caller).
 *
 * Confirmed: one stack param [EBP+8], no return value.
 * Confirmed: CMP AX,0x8; MOVSX EAX,AX before indexed store.
 * Confirmed: object_get_and_verify_type(param_1, 3) → *(ptr) → tag_get_name →
 *   tag_name_strip_path → error(2, warning_str, name) when list is full. */
void ai_create_mounted_weapons_for_unit(int param_1)
{
  int g;
  void *unit_obj;
  int tag_index;
  const char *tag_name;
  const char *stripped;

  g = *(volatile int *)0x632574;
  if (*(char *)(g + 1) != '\0') {
    if (*(int16_t *)(g + 0x8b8) < 8) {
      *(int *)(g + 0x8bc + (int)(*(int16_t *)(g + 0x8b8)) * 4) = param_1;
      g = *(volatile int *)0x632574;
      *(int16_t *)(g + 0x8b8) += 1;
      return;
    }
    unit_obj = object_get_and_verify_type(param_1, 3);
    tag_index = *(int *)unit_obj;
    tag_name = tag_get_name(tag_index);
    stripped = tag_name_strip_path(tag_name);
    error(2,
          "WARNING: cannot create mounted weapons for %s, exceeded "
          "MAXIMUM_NUMBER_OF_MOUNTED_WEAPON_UNITS",
          stripped);
  }
}

/* unit_vehicle_board_notify: notify the AI subsystem that a unit is boarding
 * a vehicle. Verifies the unit object (type_mask=3 for biped|vehicle), and
 * if the unit has an AI actor (offset 0x1a4 != -1), dispatches an AI
 * command via FUN_00046f10 with command type 0x24.
 * The vehicle_handle parameter is accepted but unused in this function body.
 * Confirmed: 1 stack param used ([EBP+8]), second param ([EBP+0xc]) untouched.
 * Confirmed: PUSH order for FUN_00046f10 — 7 args, cdecl (ADD ESP,0x1c). */
void unit_vehicle_board_notify(int unit_handle, int vehicle_handle)
{
  void *unit_obj = object_get_and_verify_type(unit_handle, 3);
  if (*(int *)((char *)unit_obj + 0x1a4) != -1) {
    FUN_00046f10(0x24, unit_handle, -1, -1, -1, -1, 0);
  }
}

/* ai_handle_exit_vehicle: notify the AI subsystem that a unit is exiting a
 * vehicle. Looks up the unit object (type_mask=3), checks whether the unit has
 * a valid AI actor handle at offset +0x1a4. If the actor exists, retrieves the
 * actor record from actor_data and checks the byte flag at actor+0x38c. If
 * the flag is clear, dispatches AI command 0x25 via FUN_00046f10 to notify
 * the subsystem of the vehicle-exit event. The flag at actor+0x38c is then
 * cleared unconditionally (whether or not the command was dispatched).
 *
 * Confirmed: 1 stack param [EBP+8] (unit handle). No return value.
 * Confirmed: object_get_and_verify_type(param_1, 3); EAX+0x1a4 = actor handle.
 * Confirmed: datum_get([0x6325a4], actor_handle); result in ESI.
 * Confirmed: TEST AL,AL on [ESI+0x38c]; JNZ skips FUN_00046f10 call.
 * Confirmed: FUN_00046f10(0x25, param_1, -1, -1, -1, -1, 0), 7 args cdecl
 *   (ADD ESP,0x1c). MOV byte [ESI+0x38c],0 always executes. */
void ai_handle_exit_vehicle(int param_1)
{
  char *unit_obj;
  int actor_handle;
  char *actor;

  unit_obj = (char *)object_get_and_verify_type(param_1, 3);
  actor_handle = *(int *)(unit_obj + 0x1a4);
  if (actor_handle != -1) {
    actor = (char *)datum_get(actor_data, actor_handle);
    if (*(char *)(actor + 0x38c) == '\0') {
      FUN_00046f10(0x25, param_1, -1, -1, -1, -1, 0);
    }
    *(char *)(actor + 0x38c) = 0;
  }
}

/* FUN_00040a40: clear the AI encounter/firing-position cache fields in the
 * globals block. Zeroes the int16_t counts at globals+0x130 and globals+0x132,
 * then csmemsets 0x280 bytes starting at globals+0x134 to zero.
 *
 * Confirmed: void(void) — no args, no return value.
 * Confirmed: three stores then CALL csmemset(globals+0x134, 0, 0x280).
 * Confirmed: ADD ESP,0xc (3 args); RET. */
void FUN_00040a40(void)
{
  int g;

  g = *(volatile int *)0x632574;
  *(int16_t *)(g + 0x132) = 0;
  *(int16_t *)(g + 0x130) = 0;
  csmemset((void *)(g + 0x134), 0, 0x280);
}

/* ai_reconnect_to_structure_bsp: iterate all encounterless actors and re-attach
 * any whose encounter's BSP index matches the current structure BSP.
 *
 * Walks the global encounterless-actor linked list (head at globals+0x8,
 * next-handle at actor+0x2c). For each actor:
 *   - Asserts actor[9] != 0 (encounterless flag must be set).
 *   - Skips actors with no encounter reference (actor+0x30 == -1).
 *   - Resolves the encounter element via global_scenario_get() +
 *     tag_block_get_element(scenario+0x42c, encounter_index, 0xb0).
 *   - If the element's BSP index (element+0x7e) matches the current BSP,
 *     calls encounterless_detach_actor (encounter_leave/detach) then
 * encounter_attach_actor to re-attach the actor to its encounter and squad.
 *
 * Confirmed: void(void) — no args, no return.
 * Confirmed: PUSH 0xb0 + PUSH encounter_idx are pre-staged args for
 *   tag_block_get_element; ADD ESP,0xc cleans all 3 args at once.
 * Confirmed: XOR EAX,EAX; MOV AX,[ESI+0x38] = zero-extend squad index.
 * Confirmed: MOV EBX,[ESI+0x2c] saved before body — next saved early. */
void ai_reconnect_to_structure_bsp(void)
{
  short bsp_index;
  int actor_handle;
  int next_handle;
  char *actor;
  char *scenario;
  char *encounter_element;
  int encounter_ref;
  int g;

  bsp_index = global_structure_bsp_index_get();
  g = *(int *)0x632574;
  actor_handle = *(int *)(g + 0x8);
  while (actor_handle != -1) {
    actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
    next_handle = *(int *)(actor + 0x2c);
    if (*(char *)(actor + 0x9) == '\0') {
      display_assert("actor->meta.encounterless", "c:\\halo\\SOURCE\\ai\\ai.c",
                     0x96f, 1);
      system_exit(-1);
    }
    encounter_ref = *(int *)(actor + 0x30);
    if (encounter_ref != -1) {
      scenario = (char *)global_scenario_get();
      encounter_element = (char *)tag_block_get_element(
        scenario + 0x42c, encounter_ref & 0xffff, 0xb0);
      if (*(short *)(encounter_element + 0x7e) == bsp_index) {
        encounterless_detach_actor(actor_handle);
        encounter_attach_actor(actor_handle, *(int *)(actor + 0x30),
                               *(int16_t *)(actor + 0x38), 1);
      }
    }
    actor_handle = next_handle;
  }
}

/* ai_get_race_from_team_index: map an actor/encounter type index to a flag/size
 * value. Takes a short type code (1-5) and returns the corresponding constant:
 *   1 -> 1, 2 -> 2, 3 -> 4, 4 -> 0x38, 5 -> 0x40, else 0.
 * Confirmed from disasm at 0x41040: MOV CX,word ptr [EBP+0x8],
 * cdecl short param, returns int via EAX. */
int ai_get_race_from_team_index(short param_1)
{
  int uVar1;

  uVar1 = 0;
  if (param_1 == 1) {
    return 1;
  }
  if (param_1 == 2) {
    return 2;
  }
  if (param_1 == 3) {
    return 4;
  }
  if (param_1 == 4) {
    return 0x38;
  }
  if (param_1 == 5) {
    uVar1 = 0x40;
  }
  return uVar1;
}

/* ai_initialize_for_new_map: reset the AI globals block and initialise
 * all per-map AI subsystems.
 * Zeroes the 0x8dc-byte globals block (at *(int*)0x632574), writes
 * initial state into known fields, calls 8 per-map init helpers, then
 * zeroes the scheduling counters and finally sets the AI active flag
 * (globals[1]) to mark the subsystem ready.
 *
 * Store-offset table for writes to *(int*)0x632574 (derived from disasm):
 *   +0x00 (byte): 1   — first-frame flag
 *   +0x02 (byte): 1   — second flag
 *   +0x08 (dword): -1 — initial actor handle sentinel
 *   +0x10 (byte): 1   — flag
 *   +0x14..+0x1b: 0xff fill (8 bytes via csmemset)
 *   +0x1c..+0x23: 0xff fill (8 bytes via csmemset)
 *   +0x24..+0x2b: 0xff fill (8 bytes via csmemset)
 *   +0x130 (word): 0  — schedule count
 *   +0x132 (word): 0  — schedule index
 *   +0x134..+0x3b3: 0 fill (0x280 bytes via csmemset)
 *   +0x3b4 (byte): 1  — another flag
 *   +0x01 (byte): 1   — AI active flag (set last)
 *
 * Confirmed: ADD ESP,0x3c at 0x41172 cleans all 5 csmemset call arg
 * triples (5×3=15 args, 15×4=60=0x3c). */
void ai_initialize_for_new_map(void)
{
  int *g = *(int **)0x632574;

  csmemset(g, 0, 0x8dc);
  *(char *)((char *)g + 0x00) = 1;
  *(char *)((char *)g + 0x02) = 1;
  *(int *)((char *)g + 0x08) = -1;
  *(char *)((char *)g + 0x3b4) = 1;
  *(char *)((char *)g + 0x10) = 1;
  csmemset((char *)g + 0x14, -1, 8);
  csmemset((char *)g + 0x1c, -1, 8);
  csmemset((char *)g + 0x24, -1, 8);

  ai_debug_initialize_for_new_map();
  FUN_00053650();
  FUN_0005dfa0();
  actor_in_combat();
  FUN_00064150();
  encounters_initialize_for_new_map();
  FUN_000540d0();
  ai_communication_initialize_for_new_map();

  *(int16_t *)((char *)g + 0x132) = 0;
  *(int16_t *)((char *)g + 0x130) = 0;
  csmemset((char *)g + 0x134, 0, 0x280);

  /* mark AI subsystem active */
  *(char *)((char *)g + 0x01) = 1;
}

/* ai_update: per-tick AI update dispatcher.
 * Reads the AI active flag from globals[1] and the pause flag from
 * 0x5abaa0 to decide whether to run the main update. If the scheduling
 * flag 0x5abaa1 (cVar2) is set, runs actor_update_scripted branch;
 * otherwise branches on globals[0] to run normal actor updates or
 * process accumulated spawns (globals[2]).
 * Wraps the update body in profile_enter_private / profile_exit_private
 * when profile_global_enable (0x449ef1) and the profile enable flag
 * (0x2c8738) are both set.
 * Confirmed: ai_active = globals[1], globals[0] = first-frame flag,
 * globals[2] = pending-spawn flag; all byte accesses verified in disasm. */
void ai_update(void)
{
  bool should_update;
  char schedule_flag;

  schedule_flag = *(char *)0x5abaa1;

  /* check AI active and not paused */
  if (*(char *)(*(int *)0x632574 + 1) && !*(char *)0x5abaa0) {
    should_update = 1;
  } else {
    should_update = 0;
  }

  if (*(bool *)0x449ef1 && *(char *)0x2c8738) {
    profile_enter_private(*(void **)0x2c8730);
  }

  if (should_update) {
    ai_debug_update();
    FUN_00053680();
    FUN_00040570();
    if (schedule_flag) {
      /* scripted/scheduled actor branch */
      actors_move_randomly();
      *(char *)(*(int *)0x632574 + 2) = 1;
    } else {
      if (*(char *)*(int *)0x632574) {
        /* first-frame / map-load branch */
        ai_conversation_update();
        FUN_0005de80();
        FUN_0003f5f0();
        *(char *)(*(int *)0x632574 + 2) = 1;
      } else {
        /* accumulated-spawn branch */
        if (*(char *)(*(int *)0x632574 + 2)) {
          actors_freeze();
          *(char *)(*(int *)0x632574 + 2) = 0;
        }
      }
    }
  }

  if (*(bool *)0x449ef1 && *(char *)0x2c8738) {
    profile_exit_private(*(void **)0x2c8730);
  }
}

/* FUN_000413c0: fill one ai_firing_pos_entry_t in the candidate buffer.
 *
 * Register args (thunk loads before CALL):
 *   ESI = ai_firing_pos_entry_t *entry  — pointer to the slot to fill
 *   EDI = int unit_handle               — the object handle passed through
 *                                         as entry->handle_b and as arg to
 *                                         biped_get_camera_height_and_offset
 *
 * Stack arg:
 *   [EBP+0x8] = int actor_handle        — stored as entry->handle_a
 *
 * Calls biped_get_camera_height_and_offset(unit_handle, &entry->vec_a[0],
 *   &height_offset, &camera_height) to populate the biped's eye position.
 *
 * is_sphere:  height_offset == 0.0f (height_offset at [EBP-4];
 *             compared against DAT_002533c0 = 0.0f via FCOMP).
 * scalar_a:   height_offset ([EBP-4]).
 * radius:     camera_height ([EBP-8]) + DAT_00256140 (~0.15f).
 * handle_a:   actor_handle ([EBP+0x8]).
 * handle_b:   unit_handle (EDI).
 * occupied:   0 (CL = 0, XOR ECX,ECX done before test; written last).
 * vec_b[0/1]: 0 (ECX = 0).
 *
 * Store-offset table (from disasm, NOT decompiler):
 *   [ESI+0x01] = is_sphere            MOV byte [ESI+1], AL (0x41402)
 *   [ESI+0x10] = vec_b[0] = 0         MOV dword [ESI+0x10], ECX (0x41408)
 *   [ESI+0x14] = vec_b[1] = 0         MOV dword [ESI+0x14], ECX (0x4140b)
 *   [ESI+0x18] = scalar_a             MOV dword [ESI+0x18], EAX (0x4140e)
 *   [ESI+0x24] = radius (fstp)        FSTP float [ESI+0x24]     (0x41411)
 *   [ESI+0x1c] = handle_a             MOV dword [ESI+0x1c], EDX (0x41414)
 *   [ESI+0x20] = handle_b (EDI)       MOV dword [ESI+0x20], EDI (0x41417)
 *   [ESI+0x00] = occupied = 0         MOV byte [ESI], CL        (0x4141a)
 *
 * Note: MSVC reorders stores (pipeline scheduling). occupied written last
 * even though it logically comes first. Preserved here in disasm order.
 *
 * Confirmed: cdecl, 1 stack arg, RET (no stack cleanup in callee).
 * Confirmed: ADD ESP,0x10 at 0x413e1 cleans all 4 pushes to 0x1a0890. */
void FUN_000413c0(ai_firing_pos_entry_t *entry, int unit_handle,
                  int actor_handle)
{
  float height_offset;
  float camera_height;

  biped_get_camera_height_and_offset(unit_handle, (vector3_t *)entry->vec_a,
                                     &height_offset, &camera_height);

  /* is_sphere: true when biped has no height offset (eye at ground level) */
  entry->is_sphere = (height_offset == 0.0f);
  entry->vec_b[0] = 0.0f;
  entry->vec_b[1] = 0.0f;
  entry->scalar_a = height_offset;
  entry->radius = camera_height + *(float *)0x256140;
  entry->handle_a = actor_handle;
  entry->handle_b = unit_handle;
  entry->occupied = 0;
}

/* FUN_00041420: build the firing-position candidate list for an actor.
 *
 * Iterates two linked lists:
 *   1. The actor's own encounter clump (via
 * encounter_actor_iterator_new/encounter_actor_iterator_next on
 * actor->clump_handle at actor_record+0x34).  For each member:
 *        - skip if member handle == actor_handle (self)
 *        - skip if count >= max_count
 *        - skip if member has no object (member+0x18 == -1)
 *        - skip if member is already targeting something (member+0x158 != -1)
 *        Calls prop_get_active_by_unit_index(actor_handle,
 * member_object_handle) to get a staging handle, then FUN_000413c0(@esi=entry,
 * @edi=object_handle, actor_handle_from_64ab0) to fill the slot.
 *
 *   2. A secondary prop/enemy list (via FUN_00064540/FUN_00064570).
 *      For each entry:
 *        - skip if entry+0x60 is nonzero (flag)
 *        - skip if entry+0x127 is nonzero (flag)
 *        - skip if weapon-slot type != 3 (entry+0x24)
 *        - skip if entry+0x110 != -1
 *        - verify via object_get_and_verify_type that object type bit 0 is set
 *        - skip if both are in the same encounter (same encounter handle)
 *        - skip if count >= max_count
 *        Calls FUN_000413c0(@esi=entry, @edi=entry_object_handle,
 *        local_10[0]) to fill the slot.
 *
 * Returns count of candidates written (int16_t in BX, returned via AX).
 *
 * Entry pointer arithmetic (confirmed from disasm):
 *   MOVSX EAX,BX               ; EAX = count (sign-extended)
 *   LEA EAX,[EAX + EAX*4]      ; EAX = count * 5
 *   LEA ESI,[buf + EAX*8]      ; ESI = buf + count * 0x28
 *
 * Confirmed: 3 stack args, cdecl, returns int16_t in AX (MOV AX,BX at epilog).
 * Confirmed: ESI restored to param_1 at 0x4149f/0x414a2 after inner call.
 * Confirmed: BX used as count throughout; EBX callee-saved across all calls.
 * Confirmed: first loop iterator at [EBP-0x10] (12 bytes: handle/current/next).
 *            second loop iterator at [EBP-0xc] (8 bytes: actor_handle/next).
 *
 * Call-site verification table — call to FUN_000413c0 at 0x4149a:
 *   arg      | binary source         | C expr             | match?
 *   stack[0] | PUSH EAX (ret 64ab0) | actor_handle_64ab0 | YES
 *   @esi     | LEA ESI,[buf+cnt*40] | &buf[count]        | YES
 *   @edi     | MOV EDI,[EDI+0x18]   | member_object_hdl  | YES
 *
 * Call-site verification table — call to FUN_000413c0 at 0x41567:
 *   arg      | binary source         | C expr             | match?
 *   stack[0] | PUSH ECX ([EBP-0xc]) | local_10[0]        | YES
 *   @esi     | LEA ESI,[buf+cnt*40] | &buf[count]        | YES
 *   @edi     | MOV EDI,[EDI+0x18]   | prop_object_handle | YES */
int16_t FUN_00041420(int actor_handle, int16_t max_count,
                     ai_firing_pos_entry_t *buf)
{
  char *actor;
  char *member;
  char *prop;
  char *prop_obj;
  int prop_obj_handle;
  int staging;
  int member_object_handle;
  int iter_a[3]; /* [EBP-0x10]: encounter-clump iterator (12 bytes) */
  int local_10[2]; /* [EBP-0xc]: prop-list iterator (8 bytes) */
  int16_t count;

  actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  count = 0;

  /* --- loop 1: encounter clump members --- */
  if (*(int *)(actor + 0x34) != -1) {
    encounter_actor_iterator_new(iter_a, *(int *)(actor + 0x34));
    member = (char *)encounter_actor_iterator_next(iter_a);
    while (member) {
      if (iter_a[1] != actor_handle && count < max_count &&
          *(int *)(member + 0x18) != -1 && *(int *)(member + 0x158) == -1) {
        member_object_handle = *(int *)(member + 0x18);
        staging =
          prop_get_active_by_unit_index(actor_handle, member_object_handle);
        /* entry ptr = buf + count*0x28; EDI = member_object_handle */
        FUN_000413c0(&buf[count], member_object_handle, staging);
        count++;
      }
      member = (char *)encounter_actor_iterator_next(iter_a);
    }
  }

  /* --- loop 2: prop / enemy list --- */
  FUN_00064540(local_10, actor_handle);
  prop = (char *)FUN_00064570(local_10);
  while (prop) {
    if (*(char *)(prop + 0x60) == 0 && *(char *)(prop + 0x127) == 0 &&
        *(int16_t *)(prop + 0x24) == 3 && *(int *)(prop + 0x110) == -1) {
      prop_obj_handle = *(int *)(prop + 0x18);
      prop_obj = (char *)object_get_and_verify_type(prop_obj_handle, (int)-1);
      if ((1 << (*(unsigned char *)(prop_obj + 0x64) & 0x1f) & 1u) != 0) {
        /* same-encounter filter */
        if (*(int *)(actor + 0x34) == -1 || *(int *)(prop + 0x1c) == -1 ||
            *(int *)((char *)datum_get(*(void **)0x6325a4,
                                       *(int *)(prop + 0x1c)) +
                     0x34) != *(int *)(actor + 0x34)) {
          if (count < max_count) {
            prop_obj_handle = *(int *)(prop + 0x18);
            /* entry ptr = buf + count*0x28; EDI = prop_obj_handle */
            FUN_000413c0(&buf[count], prop_obj_handle, local_10[0]);
            count++;
          }
        }
      }
    }
    prop = (char *)FUN_00064570(local_10);
  }

  return count;
}

/* ai_firing_pos_entry_t: see types.h for layout. */

/* ai_test_line_of_fire: test whether the actor can fire at a target through any
 * candidate firing position, and return the best candidate handle.
 *
 * Builds up to 0x20 candidate firing-position entries via FUN_00041420
 * (collecting nearby cover points / target-prop positions), then for each
 * entry:
 *   - skips entries whose handle_b matches excluded_handle (param_2)
 *   - if entry.is_sphere: calls fast_vector_intersects_sphere (line-sphere
 * intersection test)
 *   - otherwise:          calls vector_intersects_pill3d (segment-segment
 * proximity test) On the first passing test, marks that entry as occupied,
 * stores its handle_a as the result datum, clears the success flag, and breaks.
 *
 * When ai_debug lineoffire rendering is active (0x5aca69 != 0), records
 * the session begin/end and logs each entry via ai_debug helpers.
 *
 * Returns: 1 (bool true) if a valid position was found, 0 otherwise.
 * Output:  *result_out = handle_a of winning entry (-1 if none).
 *
 * Confirmed: 5 args, cdecl, ADD ESP,0x14 at call site (0x00023e02).
 * Confirmed: return in AL (low byte of success flag; 1=found, 0=not found).
 * Confirmed: global INC at 0x5ac6e4 = entry-attempt counter (word).
 * Confirmed: guard 0x5aca69 = ai_debug lineoffire enable flag.
 * Confirmed: EBX = param_5 (int *result_out) loaded at 0x000415cc AFTER
 *   the FUN_00041420 call+cleanup. EBX is callee-saved and used throughout.
 * Confirmed: buf size = 0x508 bytes (SUB ESP,0x508; buf at EBP-0x508). */
bool ai_test_line_of_fire(int actor_handle, int excluded_handle, float *origin,
                          float *offset, int *result_out)
{
  ai_firing_pos_entry_t buf[0x20]; /* 0x20 entries × 0x28 = 0x500 bytes */
  int result_datum;
  bool success;
  int i, count;

  datum_get(*(void **)0x6325a4, actor_handle);
  *(int16_t *)0x5ac6e4 += 1;

  success = 1;
  result_datum = -1;

  count = (int)(int16_t)FUN_00041420(actor_handle, 0x20, buf);

  if (count > 0) {
    for (i = 0; i < count; i++) {
      ai_firing_pos_entry_t *e = &buf[i];

      /* skip entries whose exclusion handle matches param_2 */
      if (e->handle_b == excluded_handle) {
        continue;
      }

      {
        bool hit;
        if (e->is_sphere) {
          /* push-then-fstp pattern: radius is loaded via FLD then
           * FSTP [ESP] after PUSH ECX (dummy). Confirmed at 0x41600:
           * FLD [EBP+EAX+0xfffffb1c]; PUSH ECX; FSTP [ESP]. */
          hit =
            fast_vector_intersects_sphere(origin, offset, e->vec_a, e->radius);
        } else {
          hit = vector_intersects_pill3d(origin, offset, e->vec_a, e->vec_b,
                                         e->scalar_a);
        }

        if (hit) {
          result_datum = e->handle_a;
          success = 0;
          e->occupied = 1;
          break;
        }
      }
    }
  }

  /* ai_debug lineoffire rendering */
  if (*(char *)0x5aca69) {
    ai_debug_get_last_path(origin, offset);
    for (i = 0; i < count; i++) {
      ai_firing_pos_entry_t *e = &buf[i];
      ai_debug_lineoffire_addpill(e->vec_a, e->vec_b, *(int *)&e->radius,
                                  e->occupied);
    }
    FUN_000494d0((char)success);
  }

  if (result_out) {
    *result_out = result_datum;
  }
  return (bool)success;
}

/* ai_clump (ai_clump): scan all active player-actor records to find
 * any actor that should trigger a clump (grouping) response.
 * Iterates via data_iterator_new/data_iterator_next over the data at
 * 0x5ab23c. For each record: checks active/valid flags, verifies the
 * unit is a vehicle occupant, looks up the actor, selects target via
 * actor->field_6, retrieves the unit tag and checks the 0x80000 flag.
 * Various clump-eligibility conditions are tested (swarm flag, state
 * range, timers, squads) with float comparisons from constants embedded
 * in the binary. Returns 1 (true) if any clump-eligible actor is found,
 * 0 otherwise.
 * Confirmed: param_1 is char (PUSH 0 / PUSH 1 at call sites);
 * return via AL = 0 or 1 (two separate RETs); two exit paths.
 * Inferred: 0x5ab23c = swarm/clump data_t; 0x2533d8, 0x254cc0,
 * 0x254cc8, 0x254e74 are float constants embedded in the game binary. */
bool ai_clump(char param_1)
{
  int current_time;
  data_iter_t iter; /* standard 0x10-byte data iterator */
  char *rec;
  char *unit;
  char *actor;
  char *tag;
  bool bVar4;
  int16_t state;

  current_time = game_time_get();
  data_iterator_new(&iter, *(data_t **)0x5ab23c);
  rec = data_iterator_next(&iter);

  do {
    if (rec == 0) {
      return 0;
    }

    /* check active (0x12e) and enabled (0x60) flags */
    if (*(char *)(rec + 0x12e) && *(char *)(rec + 0x60)) {
      char *unit_rec;
      /* verify unit is a vehicle occupant (type 3), with a rider (1c8) */
      unit = object_get_and_verify_type(*(int *)(rec + 0x18), 3);
      if (*(int *)(unit + 0x1c8) != -1) {
        /* look up actor for this record */
        actor = datum_get(actor_data, *(int *)(rec + 0x4));

        /* select target handle based on actor->field_6 */
        if (*(char *)(actor + 0x6)) {
          unit_rec = (char *)*(int *)(actor + 0x24);
        } else {
          unit_rec = (char *)*(int *)(actor + 0x18);
        }

        unit_rec = object_get_and_verify_type((int)unit_rec, 3);
        tag = tag_get(0x756e6974, *(int *)unit_rec);

        /* check unit tag has swarm flag (bit 19 = 0x80000) */
        bVar4 = 0;
        if (*(int *)(tag + 0x17c) & 0x80000) {
          /* compare distance to constant at 0x2533d8 */
          bVar4 = *(float *)(rec + 0x11c) > *(float *)0x2533d8;
        }

        /* if param_1 set and actor is not already clumped/in-range,
         * apply proximity override check against constant at 0x254cc0 */
        if (param_1 && *(int16_t *)(actor + 0x5f2) == 0 &&
            *(int16_t *)(actor + 0x6c) != 10) {
          if (*(float *)(rec + 0x11c) <= *(float *)0x254cc0) {
            goto next_rec;
          }
        }

        if (bVar4) {
          goto next_rec;
        }

        state = *(int16_t *)(rec + 0x24);

        /* states outside [4,5]: check timer handle */
        if ((state < 4 || state > 5) && *(int *)(rec + 0x8c) != -1 &&
            *(int *)(rec + 0x8c) + 0x5a >= current_time) {
          return 1;
        }

        /* states outside [4,5]: compare distance again */
        if ((state < 4 || state > 5)) {
          if (*(float *)(rec + 0x11c) < *(float *)0x2533d8) {
            return 1;
          }
        }

        /* squad check: actor->field_0x270 must match iter.datum_handle
         * (iter.datum_handle = EBP-0xc in disassembly, overlaps the
         * decompiler's 'local_10' variable) */
        if (*(int *)(actor + 0x270) == (int)iter.datum_handle) {
          if (state > 1 && state <= 3) {
            return 1;
          }
          if (state >= 4 && state <= 5) {
            /* check leading-actor flag and squad membership */
            if (*(char *)(rec + 0xb8)) {
              return 1;
            }
            /* look up leader actor via record->field_0xc */
            actor = datum_get(*(data_t **)0x5ab23c, *(int *)(rec + 0xc));
            if (*(int16_t *)(rec + 0x24) == 4 &&
                *(float *)(rec + 0x11c) < *(float *)0x254cc8) {
              /* distance-squared check between two position fields */
              if (distance_squared3d((void *)(actor + 0xbc),
                                     (void *)(rec + 0xbc)) <
                  *(float *)0x254e74) {
                return 1;
              }
            }
          }
        }
      }
    }

  next_rec:
    rec = data_iterator_next(&iter);
  } while (1);
}

/* ai_enemies_can_see_player: query whether any AI enemy can currently see
 * a player. Delegates entirely to ai_clump(0). Returns true if any
 * enemy has line-of-sight to a player, false otherwise.
 * Confirmed: PUSH 0 / CALL 0x42390 / ADD ESP,4 / RET; caller (0xa74f0)
 * checks the return value as a bool. */
bool ai_enemies_can_see_player(void)
{
  return ai_clump(0);
}

/* ai_enemies_attacking_player: unconditionally trigger a clump check with
 * flag=1. Thin wrapper around ai_clump (ai_clump). Return value is
 * discarded by the caller. Confirmed: PUSH 1 / CALL 0x42390 / ADD ESP,4 / RET.
 */
void ai_enemies_attacking_player(void)
{
  ai_clump(1);
}

/* FUN_000425c0 (0x425c0) — XBE naked draft (batch 69). */
#if defined(__clang__)
static int (*const b425c0_gtime)(void) = game_time_get;
static void (*const b425c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b425c0_exitfn)(int) = system_exit;
static float (*const b425c0_c121a0)(const float *a, const float *b) = distance_squared3d;
static void (*const b425c0_c3c0c0)(int object_handle, short effect_type, float *position, short volume, short count) = actors_handle_spatial_effect;

__attribute__((naked, noinline))
void FUN_000425c0(int object_handle __attribute__((unused)), float *position __attribute__((unused)), short effect_type __attribute__((unused)), short volume __attribute__((unused)), short count __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x40, %%esp\n\t"
      "movl 0x632574, %%eax\n\t"
      "movzbl 0x1(%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_000425c0_23\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movswl 0x18(%%ebp), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "jg .LFUN_000425c0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x80e\n\t"
      "pushl $0x2575c0\n\t"
      "pushl $0x257c5c\n\t"
      "call *%[assert]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000425c0_1:\n\t"
      "movswl 0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_000425c0_2\n\t"
      "movswl 0x14(%%ebp), %%ecx\n\t"
      "cmpl $5, %%ecx\n\t"
      "jl .LFUN_000425c0_3\n\t"
      ".LFUN_000425c0_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x80f\n\t"
      "pushl $0x2575c0\n\t"
      "pushl $0x257800\n\t"
      "call *%[assert]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000425c0_3:\n\t"
      "movswl 0x10(%%ebp), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "jl .LFUN_000425c0_4\n\t"
      "movswl 0x10(%%ebp), %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "jl .LFUN_000425c0_5\n\t"
      ".LFUN_000425c0_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x810\n\t"
      "pushl $0x2575c0\n\t"
      "pushl $0x257c20\n\t"
      "call *%[assert]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000425c0_5:\n\t"
      "movswl 0x14(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .LFUN_000425c0_23\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "subl $0x1e, %%edx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "subl $0x1e, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "subl $0x5a, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "movb $1, -0x1d(%%ebp)\n\t"
      "movw $0xffff, -0xc(%%ebp)\n\t"
      "movl 0x632574, %%edx\n\t"
      "movw 0x130(%%edx), %%ax\n\t"
      "movw %%ax, -0x18(%%ebp)\n\t"
      "jmp .LFUN_000425c0_7\n\t"
      ".LFUN_000425c0_6:\n\t"
      "movswl -0x18(%%ebp), %%ecx\n\t"
      "addl $1, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movw %%cx, -0x18(%%ebp)\n\t"
      ".LFUN_000425c0_7:\n\t"
      "movswl -0x18(%%ebp), %%edx\n\t"
      "movl 0x632574, %%eax\n\t"
      "movswl 0x132(%%eax), %%ecx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "je .LFUN_000425c0_16\n\t"
      "movb $0, -0x1e(%%ebp)\n\t"
      "movswl 0x10(%%ebp), %%edx\n\t"
      "movswl -0x18(%%ebp), %%eax\n\t"
      "imull $0x14, %%eax, %%eax\n\t"
      "movl 0x632574, %%ecx\n\t"
      "movswl 0x134(%%ecx,%%eax,1), %%eax\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jne .LFUN_000425c0_8\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movswl -0x18(%%ebp), %%edx\n\t"
      "imull $0x14, %%edx, %%edx\n\t"
      "movl 0x632574, %%eax\n\t"
      "leal 0x138(%%eax,%%edx,1), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c121a0]\n\t"
      "addl $8, %%esp\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000425c0_8\n\t"
      "movb $1, -0x1e(%%ebp)\n\t"
      ".LFUN_000425c0_8:\n\t"
      "movswl -0x18(%%ebp), %%edx\n\t"
      "imull $0x14, %%edx, %%edx\n\t"
      "movl 0x632574, %%eax\n\t"
      "movl 0x144(%%eax,%%edx,1), %%ecx\n\t"
      "cmpl -0x8(%%ebp), %%ecx\n\t"
      "jg .LFUN_000425c0_11\n\t"
      "movswl -0x18(%%ebp), %%edx\n\t"
      "imull $0x14, %%edx, %%edx\n\t"
      "movl 0x632574, %%eax\n\t"
      "movw $0xffff, 0x134(%%eax,%%edx,1)\n\t"
      "movswl -0x18(%%ebp), %%ecx\n\t"
      "movl 0x632574, %%edx\n\t"
      "movswl 0x130(%%edx), %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jne .LFUN_000425c0_9\n\t"
      "movswl -0x18(%%ebp), %%ecx\n\t"
      "addl $1, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl 0x632574, %%edx\n\t"
      "movw %%cx, 0x130(%%edx)\n\t"
      "jmp .LFUN_000425c0_10\n\t"
      ".LFUN_000425c0_9:\n\t"
      "movw -0x18(%%ebp), %%ax\n\t"
      "movw %%ax, -0xc(%%ebp)\n\t"
      ".LFUN_000425c0_10:\n\t"
      "jmp .LFUN_000425c0_15\n\t"
      ".LFUN_000425c0_11:\n\t"
      "movzbl -0x1e(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_000425c0_15\n\t"
      "movswl -0x18(%%ebp), %%edx\n\t"
      "imull $0x14, %%edx, %%edx\n\t"
      "movl 0x632574, %%eax\n\t"
      "leal 0x134(%%eax,%%edx,1), %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movswl 0x2(%%edx), %%eax\n\t"
      "addl $1, %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movw %%ax, 0x2(%%ecx)\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl 0x10(%%edx), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl -0x1c(%%ebp), %%eax\n\t"
      "setl %%cl\n\t"
      "movb %%cl, -0x1d(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl 0x10(%%edx), %%eax\n\t"
      "cmpl -0x14(%%ebp), %%eax\n\t"
      "jge .LFUN_000425c0_13\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "addl $4, %%edx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "movzbl -0x1d(%%ebp), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .LFUN_000425c0_12\n\t"
      "pushl $1\n\t"
      "pushl $0x847\n\t"
      "pushl $0x2575c0\n\t"
      "pushl $0x257c18\n\t"
      "call *%[assert]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000425c0_12:\n\t"
      "jmp .LFUN_000425c0_14\n\t"
      ".LFUN_000425c0_13:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movswl 0x2(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x40(%%ebp)\n\t"
      "fildl -0x40(%%ebp)\n\t"
      "fdivrs 0x2533c8\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fsubs -0x24(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0x4(%%edx)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "fstps 0x4(%%ecx)\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0x8(%%edx)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "fstps 0x8(%%ecx)\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0xc(%%edx)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "fstps 0xc(%%ecx)\n\t"
      ".LFUN_000425c0_14:\n\t"
      "jmp .LFUN_000425c0_16\n\t"
      ".LFUN_000425c0_15:\n\t"
      "jmp .LFUN_000425c0_6\n\t"
      ".LFUN_000425c0_16:\n\t"
      "cmpl $0, -0x10(%%ebp)\n\t"
      "jne .LFUN_000425c0_22\n\t"
      "movswl -0xc(%%ebp), %%edx\n\t"
      "cmpl $-1, %%edx\n\t"
      "jne .LFUN_000425c0_18\n\t"
      "movl 0x632574, %%eax\n\t"
      "movw 0x132(%%eax), %%cx\n\t"
      "movw %%cx, -0x18(%%ebp)\n\t"
      "movl 0x632574, %%edx\n\t"
      "movswl 0x132(%%edx), %%eax\n\t"
      "addl $1, %%eax\n\t"
      "andl $0x1f, %%eax\n\t"
      "movl 0x632574, %%ecx\n\t"
      "movw %%ax, 0x132(%%ecx)\n\t"
      "movl 0x632574, %%edx\n\t"
      "movswl 0x132(%%edx), %%eax\n\t"
      "movl 0x632574, %%ecx\n\t"
      "movswl 0x130(%%ecx), %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jne .LFUN_000425c0_17\n\t"
      "movl 0x632574, %%eax\n\t"
      "movswl 0x130(%%eax), %%ecx\n\t"
      "addl $1, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl 0x632574, %%edx\n\t"
      "movw %%cx, 0x130(%%edx)\n\t"
      ".LFUN_000425c0_17:\n\t"
      "jmp .LFUN_000425c0_19\n\t"
      ".LFUN_000425c0_18:\n\t"
      "movw -0xc(%%ebp), %%ax\n\t"
      "movw %%ax, -0x18(%%ebp)\n\t"
      ".LFUN_000425c0_19:\n\t"
      "movswl -0x18(%%ebp), %%ecx\n\t"
      "movl 0x632574, %%edx\n\t"
      "movswl 0x130(%%edx), %%eax\n\t"
      "subl %%eax, %%ecx\n\t"
      "addl $0x20, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movw %%cx, -0x2c(%%ebp)\n\t"
      "movl 0x632574, %%ecx\n\t"
      "movswl 0x132(%%ecx), %%edx\n\t"
      "movl 0x632574, %%eax\n\t"
      "movswl 0x130(%%eax), %%ecx\n\t"
      "subl %%ecx, %%edx\n\t"
      "addl $0x20, %%edx\n\t"
      "andl $0x1f, %%edx\n\t"
      "movw %%dx, -0x30(%%ebp)\n\t"
      "movswl -0x2c(%%ebp), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "jl .LFUN_000425c0_20\n\t"
      "movswl -0x2c(%%ebp), %%eax\n\t"
      "movswl -0x30(%%ebp), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_000425c0_21\n\t"
      ".LFUN_000425c0_20:\n\t"
      "pushl $1\n\t"
      "pushl $0x871\n\t"
      "pushl $0x2575c0\n\t"
      "pushl $0x257bc8\n\t"
      "call *%[assert]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000425c0_21:\n\t"
      "movswl -0x18(%%ebp), %%edx\n\t"
      "imull $0x14, %%edx, %%edx\n\t"
      "movl 0x632574, %%eax\n\t"
      "leal 0x134(%%eax,%%edx,1), %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "movl (%%edx), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x10(%%eax)\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movw 0x10(%%ebp), %%ax\n\t"
      "movw %%ax, (%%edx)\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movw $1, 0x2(%%ecx)\n\t"
      ".LFUN_000425c0_22:\n\t"
      "movzbl -0x1d(%%ebp), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LFUN_000425c0_23\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movw 0x2(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "movw 0x14(%%ebp), %%dx\n\t"
      "pushl %%edx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movw (%%ecx), %%dx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c3c0c0]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000425c0_23:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [gtime] "m"(b425c0_gtime), [assert] "m"(b425c0_assert), [exitfn] "m"(b425c0_exitfn), [c121a0] "m"(b425c0_c121a0), [c3c0c0] "m"(b425c0_c3c0c0)
      : "memory");
}
#else
#error "FUN_000425c0: clang naked draft required"
#endif

/* --- ai.obj batch drafts (2026-07-26) --- */

/* FUN_0003f350 (0x3f350) — XBE naked draft (batch 113). */
#if defined(__clang__)
static void *(*const b3f350_get)(int, int) = object_get_and_verify_type;
static void *(*const b3f350_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b3f350_tag)(int, int) = tag_get;
static int *(*const b3f350_gseed)(void) = get_global_random_seed_address;
static float (*const b3f350_rrange)(int *, float, float) = random_real_range;
static void (*const b3f350_opnew)(void *, int, int) = object_placement_data_new;
static void (*const b3f350_c10cc70)(float *output, float angle) = vector3d_from_angle;
static vector3_t * (*const b3f350_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static int (*const b3f350_onew)(void *) = object_new;
static char (*const b3f350_c1a1430)(int unit_handle, int seat_handle, float *initial_position, float *final_position, float scale, char keep_basis, char dont_teleport, char scale_by_height) = biped_fix_position;
static void (*const b3f350_c3c7c0)(int actv_tag_index, int unit_index) = actor_customize_unit;
static int (*const b3f350_c3edc0)(char flags, int unit_index, int actv_tag_index, int encounter_index, int squad_index, char param6, int exclude_actor_handle, char encounter_flag, short starting_location_index, short squad_position_index, unsigned short param11, char param12) = actor_create_for_unit;
static void (*const b3f350_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b3f350_odel)(int) = object_delete;
static void (*const b3f350_c3aca0)(int actor_handle) = actor_verify_activation;
static void (*const b3f350_c1a4a70)(int handle, float *velocity) = FUN_001a4a70;

__attribute__((naked, noinline))
int FUN_0003f350(int unit_handle __attribute__((unused)), int spawn_tag __attribute__((unused)), int16_t count __attribute__((unused)), float radius __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xac, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpl $-1, %%ebx\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "je .LFUN_0003f350_10\n\t"
      "movw 0x10(%%ebp), %%si\n\t"
      "testw %%si, %%si\n\t"
      "jle .LFUN_0003f350_10\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0x1a8(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "jne .LFUN_0003f350_1\n\t"
      "movl 0x1a4(%%eax), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_0003f350_2\n\t"
      ".LFUN_0003f350_1:\n\t"
      "movl 0x1a4(%%eax), %%ecx\n\t"
      "movl 0x6325a4, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movw 0x34(%%eax), %%cx\n\t"
      "movw 0x3a(%%eax), %%dx\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0003f350_3\n\t"
      ".LFUN_0003f350_2:\n\t"
      "movw 0x2e4(%%eax), %%cx\n\t"
      "movw 0x2e6(%%eax), %%dx\n\t"
      ".LFUN_0003f350_3:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "cmpw %%ax, %%cx\n\t"
      "movw %%cx, -0xc(%%ebp)\n\t"
      "movw %%dx, 0xc(%%ebp)\n\t"
      "je .LFUN_0003f350_10\n\t"
      "cmpw %%ax, %%dx\n\t"
      "je .LFUN_0003f350_10\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x61637476\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl 0x10(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%si, %%si\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jle .LFUN_0003f350_10\n\t"
      "movzwl %%si, %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0003f350_4:\n\t"
      "pushl $0x40c90fdb\n\t"
      "pushl $0\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl 0x20(%%edx), %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "leal -0xac(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[opnew]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x78(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c10cc70]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "leal -0x94(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1412f0]\n\t"
      "flds -0x8c(%%ebp)\n\t"
      "fadds 0x2533e4\n\t"
      "leal -0xac(%%ebp), %%eax\n\t"
      "flds -0x78(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "fmuls 0x2533e4\n\t"
      "fadds -0x94(%%ebp)\n\t"
      "fstps -0x94(%%ebp)\n\t"
      "flds -0x74(%%ebp)\n\t"
      "fmuls 0x2533e4\n\t"
      "fadds -0x90(%%ebp)\n\t"
      "fstps -0x90(%%ebp)\n\t"
      "flds -0x70(%%ebp)\n\t"
      "fmuls 0x2533e4\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fstps -0x8c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[onew]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x2c, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_0003f350_9\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, 0x64(%%edi)\n\t"
      "jne .LFUN_0003f350_5\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0\n\t"
      "leal -0x94(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "call *%[c1a1430]\n\t"
      "addl $0x20, %%esp\n\t"
      ".LFUN_0003f350_5:\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c3c7c0]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movswl -0xc(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "pushl $2\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "shrl $0x1a, %%edx\n\t"
      "andl $0xffffff01, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c3edc0]\n\t"
      "addl $0x38, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_0003f350_6\n\t"
      "pushl $0x257548\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "pushl %%esi\n\t"
      "call *%[odel]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_0003f350_8\n\t"
      ".LFUN_0003f350_6:\n\t"
      "pushl %%eax\n\t"
      "call *%[c3aca0]\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0003f350_7\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0x3f000000\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x3fc00000\n\t"
      "pushl $0x3f4ccccd\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "flds -0x78(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0, 0x64(%%edi)\n\t"
      "flds -0x74(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x14(%%ebp)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "fmuls 0x14(%%ebp)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "fmuls 0x14(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "jne .LFUN_0003f350_7\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1a4a70]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0003f350_7:\n\t"
      "incl -0x8(%%ebp)\n\t"
      ".LFUN_0003f350_8:\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      ".LFUN_0003f350_9:\n\t"
      "decl -0x10(%%ebp)\n\t"
      "jne .LFUN_0003f350_4\n\t"
      ".LFUN_0003f350_10:\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b3f350_get), [dget] "m"(b3f350_dget), [tag] "m"(b3f350_tag), [gseed] "m"(b3f350_gseed), [rrange] "m"(b3f350_rrange), [opnew] "m"(b3f350_opnew), [c10cc70] "m"(b3f350_c10cc70), [c1412f0] "m"(b3f350_c1412f0), [onew] "m"(b3f350_onew), [c1a1430] "m"(b3f350_c1a1430), [c3c7c0] "m"(b3f350_c3c7c0), [c3edc0] "m"(b3f350_c3edc0), [c8f390] "m"(b3f350_c8f390), [odel] "m"(b3f350_odel), [c3aca0] "m"(b3f350_c3aca0), [c1a4a70] "m"(b3f350_c1a4a70)
      : "memory");
}
#else
#error "FUN_0003f350: clang naked draft required"
#endif


/* ai_adjust_damage (0x3f900) — readable C lift (ai campaign). */
char ai_adjust_damage(int player_index, void *damage_params, float *scale)
{
  char bl = 0;
  if (player_index == -1)
    return 0;
  void *edx = datum_get(*(void **)0x6325a4, player_index);
  unsigned char al = *((unsigned char *)damage_params + 4);
  if ((al & 8) != 0) {
    float v = *(float *)((char *)edx + 0x69c);
    if (!(v <= *(float *)0x2533c0)) {
      *scale = *scale * v;
      bl = 1;
    }
  }
  if (*((unsigned char *)edx + 0x1ca)) {
    *scale = *scale * *(float *)0x2533e4;
    return 1;
  }
  return bl;
}

/* ai_find_inactive_encounters (0x3fb40) — XBE naked draft (batch 221). */
#if defined(__clang__)
static void (*const b3fb40_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b3fb40_exitfn)(int) = system_exit;
static void (*const b3fb40_c59a00)(int *iter, int clump_handle) = encounter_actor_iterator_new;
static int (*const b3fb40_c59a50)(int *iter) = encounter_actor_iterator_next;
static void (*const b3fb40_c59990)(int iter, char param_2) = encounter_iterator_new;
static void * (*const b3fb40_c599c0)(int iter) = FUN_000599c0;
static void __cdecl (*const b3fb40_c1d9260)(void *base, size_t nmemb, size_t size, int (__cdecl *compar)(const void *, const void *)) = qsort;

__attribute__((naked, noinline))
void ai_find_inactive_encounters(void *out_list __attribute__((unused)), int buf_size __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "cmpw $0xc04, 0xc(%%ebp)\n\t"
      "jae .Lai_find_inactive_encounters_1\n\t"
      "pushl $1\n\t"
      "pushl $0x22e\n\t"
      "pushl $0x2575c0\n\t"
      "pushl $0x257648\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_find_inactive_encounters_1:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movw $0, (%%esi)\n\t"
      "movw $0, 0x2(%%esi)\n\t"
      "call *%[c59a00]\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59a50]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lai_find_inactive_encounters_4\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lai_find_inactive_encounters_2:\n\t"
      "movw (%%esi), %%cx\n\t"
      "cmpw $0x100, %%cx\n\t"
      "jge .Lai_find_inactive_encounters_4\n\t"
      "movb 0x8(%%eax), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .Lai_find_inactive_encounters_3\n\t"
      "cmpl %%edi, 0xc(%%eax)\n\t"
      "je .Lai_find_inactive_encounters_3\n\t"
      "movswl %%cx, %%ecx\n\t"
      "leal (%%ecx,%%ecx,2), %%edx\n\t"
      "movb $1, 0x4(%%esi,%%edx,4)\n\t"
      "movswl (%%esi), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "leal (%%ecx,%%ecx,2), %%ecx\n\t"
      "movl %%edx, 0x8(%%esi,%%ecx,4)\n\t"
      "movswl (%%esi), %%ecx\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "incl %%ecx\n\t"
      "leal (%%ecx,%%ecx,2), %%ecx\n\t"
      "movl %%edx, (%%esi,%%ecx,4)\n\t"
      "incw (%%esi)\n\t"
      ".Lai_find_inactive_encounters_3:\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c59a50]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lai_find_inactive_encounters_2\n\t"
      ".Lai_find_inactive_encounters_4:\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59990]\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c599c0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lai_find_inactive_encounters_7\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lai_find_inactive_encounters_5:\n\t"
      "movw (%%esi), %%cx\n\t"
      "cmpw $0x100, %%cx\n\t"
      "jge .Lai_find_inactive_encounters_7\n\t"
      "movb 0xd(%%eax), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .Lai_find_inactive_encounters_6\n\t"
      "cmpw $0, 0x2a(%%eax)\n\t"
      "jle .Lai_find_inactive_encounters_6\n\t"
      "cmpl %%edi, 0x10(%%eax)\n\t"
      "je .Lai_find_inactive_encounters_6\n\t"
      "movswl %%cx, %%ecx\n\t"
      "leal (%%ecx,%%ecx,2), %%ecx\n\t"
      "movb $0, 0x4(%%esi,%%ecx,4)\n\t"
      "movswl (%%esi), %%ecx\n\t"
      "leal (%%ecx,%%ecx,2), %%edx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x8(%%esi,%%edx,4)\n\t"
      "movswl (%%esi), %%ecx\n\t"
      "movl 0x10(%%eax), %%eax\n\t"
      "incl %%ecx\n\t"
      "leal (%%ecx,%%ecx,2), %%edx\n\t"
      "movl %%eax, (%%esi,%%edx,4)\n\t"
      "incw (%%esi)\n\t"
      ".Lai_find_inactive_encounters_6:\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c599c0]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lai_find_inactive_encounters_5\n\t"
      ".Lai_find_inactive_encounters_7:\n\t"
      "movw (%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lai_find_inactive_encounters_8\n\t"
      "pushl $0x3fb00\n\t"
      "movswl %%ax, %%edx\n\t"
      "pushl $0xc\n\t"
      "pushl %%edx\n\t"
      "addl $4, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d9260]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lai_find_inactive_encounters_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [assert] "m"(b3fb40_assert), [exitfn] "m"(b3fb40_exitfn), [c59a00] "m"(b3fb40_c59a00), [c59a50] "m"(b3fb40_c59a50), [c59990] "m"(b3fb40_c59990), [c599c0] "m"(b3fb40_c599c0), [c1d9260] "m"(b3fb40_c1d9260)
      : "memory");
}
#else
#error "ai_find_inactive_encounters: clang naked draft required"
#endif


/* ai_release_inactive_encounters (0x3fc90) — XBE naked draft (batch 234). */
#if defined(__clang__)
static void (*const b3fc90_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b3fc90_exitfn)(int) = system_exit;
static void *(*const b3fc90_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static const char * (*const b3fc90_c1ba1f0)(int tag_index) = tag_get_name;
static const char * (*const b3fc90_c19b0d0)(const char *tag_name) = tag_name_strip_path;
static int (*const b3fc90_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static void (*const b3fc90_c3d950)(int actor_handle, char flag) = actor_erase;
static scenario_t * (*const b3fc90_c18e380)(void) = global_scenario_get;
static void *(*const b3fc90_elem)(void *, int, int) = tag_block_get_element;
static void (*const b3fc90_c3f970)(int param_1, int param_2, int param_3, int param_4) = ai_erase;

__attribute__((naked, noinline))
char ai_release_inactive_encounters(char *result_description __attribute__((unused)), char *more_to_release __attribute__((unused)), void *list __attribute__((unused)), int16_t working_memory_size __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "xorb %%bl, %%bl\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%edi\n\t"
      "je .Lai_release_inactive_encounters_1\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lai_release_inactive_encounters_2\n\t"
      ".Lai_release_inactive_encounters_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x270\n\t"
      "pushl $0x2575c0\n\t"
      "pushl $0x257620\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_release_inactive_encounters_2:\n\t"
      "cmpw $0xc04, 0x14(%%ebp)\n\t"
      "jae .Lai_release_inactive_encounters_3\n\t"
      "pushl $1\n\t"
      "pushl $0x271\n\t"
      "pushl $0x2575c0\n\t"
      "pushl $0x257648\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_release_inactive_encounters_3:\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "movw 0x2(%%edi), %%ax\n\t"
      "cmpw (%%edi), %%ax\n\t"
      "jge .Lai_release_inactive_encounters_6\n\t"
      "movswl %%ax, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "pushl %%esi\n\t"
      "leal 0x4(%%edi,%%eax,4), %%esi\n\t"
      "cmpb $0, (%%esi)\n\t"
      "je .Lai_release_inactive_encounters_4\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl 0x6325a4, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x5c(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ba1f0]\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b0d0]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2576a8\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "call *%[c3d950]\n\t"
      "addl $0x24, %%esp\n\t"
      "jmp .Lai_release_inactive_encounters_5\n\t"
      ".Lai_release_inactive_encounters_4:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "andl $0xffff, %%eax\n\t"
      "pushl $0xb0\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl 0x5ab270, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[dget]\n\t"
      "movswl 0x2a(%%eax), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x257690\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[c3f970]\n\t"
      "addl $0x34, %%esp\n\t"
      ".Lai_release_inactive_encounters_5:\n\t"
      "incw 0x2(%%edi)\n\t"
      "movb $1, %%bl\n\t"
      "popl %%esi\n\t"
      ".Lai_release_inactive_encounters_6:\n\t"
      "movw 0x2(%%edi), %%ax\n\t"
      "cmpw (%%edi), %%ax\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "setl %%cl\n\t"
      "popl %%edi\n\t"
      "movb %%bl, %%al\n\t"
      "movb %%cl, (%%edx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b3fc90_assert), [exitfn] "m"(b3fc90_exitfn), [dget] "m"(b3fc90_dget), [c1ba1f0] "m"(b3fc90_c1ba1f0), [c19b0d0] "m"(b3fc90_c19b0d0), [c1d90f0] "m"(b3fc90_c1d90f0), [c3d950] "m"(b3fc90_c3d950), [c18e380] "m"(b3fc90_c18e380), [elem] "m"(b3fc90_elem), [c3f970] "m"(b3fc90_c3f970)
      : "memory");
}
#else
#error "ai_release_inactive_encounters: clang naked draft required"
#endif


/* ai_handle_allegiance_broken_notification (0x40150) — XBE naked draft (batch 232). */
#if defined(__clang__)
static void (*const b40150_cff4d0)(int channel, const char *format, ...) = console_printf;
static void (*const b40150_c59b10)(void *iter, char flag) = encounter_iterator_next;
static int (*const b40150_c59b50)(void *iter) = FUN_00059b50;
static void (*const b40150_c64540)(int *out, int actor_handle) = FUN_00064540;
static int (*const b40150_c64570)(int *iter) = FUN_00064570;
static bool (*const b40150_c2fc20)(int actor_handle, int clump_item_handle) = actor_get_perception_knowledge;
static float (*const b40150_c2fd10)(int actor_handle, int clump_item_handle) = actor_compute_prop_target_weight;
static void (*const b40150_ca7c30)(int16_t team_a, int16_t team_b) = game_allegiance_notify_change;

__attribute__((naked, noinline))
void ai_handle_allegiance_broken_notification(int16_t team_a __attribute__((unused)), int16_t team_b __attribute__((unused)), char print_message __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24, %%esp\n\t"
      "movb 0x5aca55, %%al\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpb %%bl, %%al\n\t"
      "je .Lai_handle_allegiance_broken_notification_2\n\t"
      "cmpb %%bl, 0x10(%%ebp)\n\t"
      "movl $0x257718, %%eax\n\t"
      "jne .Lai_handle_allegiance_broken_notification_1\n\t"
      "movl $0x25770c, %%eax\n\t"
      ".Lai_handle_allegiance_broken_notification_1:\n\t"
      "movswl 0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movswl 0xc(%%ebp), %%eax\n\t"
      "movl 0x2efdf8(,%%eax,4), %%ecx\n\t"
      "movl 0x2efdf8(,%%edx,4), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x257730\n\t"
      "pushl %%ebx\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_handle_allegiance_broken_notification_2:\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59b10]\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c59b50]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .Lai_handle_allegiance_broken_notification_9\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lai_handle_allegiance_broken_notification_3:\n\t"
      "movw 0x3e(%%eax), %%ax\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "cmpw %%di, %%ax\n\t"
      "jne .Lai_handle_allegiance_broken_notification_4\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "jmp .Lai_handle_allegiance_broken_notification_5\n\t"
      ".Lai_handle_allegiance_broken_notification_4:\n\t"
      "cmpw 0xc(%%ebp), %%ax\n\t"
      "jne .Lai_handle_allegiance_broken_notification_8\n\t"
      ".Lai_handle_allegiance_broken_notification_5:\n\t"
      "cmpw $-1, %%di\n\t"
      "je .Lai_handle_allegiance_broken_notification_8\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c64540]\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c64570]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .Lai_handle_allegiance_broken_notification_8\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lai_handle_allegiance_broken_notification_6:\n\t"
      "cmpw %%di, 0x12(%%esi)\n\t"
      "jne .Lai_handle_allegiance_broken_notification_7\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "movb $1, 0x61(%%esi)\n\t"
      "movb %%bl, 0x62(%%esi)\n\t"
      "movb %%al, 0x60(%%esi)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c2fc20]\n\t"
      "movb %%al, 0xa4(%%esi)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2fd10]\n\t"
      "fstps 0x50(%%esi)\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lai_handle_allegiance_broken_notification_7:\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c64570]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .Lai_handle_allegiance_broken_notification_6\n\t"
      ".Lai_handle_allegiance_broken_notification_8:\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c59b50]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jne .Lai_handle_allegiance_broken_notification_3\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".Lai_handle_allegiance_broken_notification_9:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[ca7c30]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cff4d0] "m"(b40150_cff4d0), [c59b10] "m"(b40150_c59b10), [c59b50] "m"(b40150_c59b50), [c64540] "m"(b40150_c64540), [c64570] "m"(b40150_c64570), [c2fc20] "m"(b40150_c2fc20), [c2fd10] "m"(b40150_c2fd10), [ca7c30] "m"(b40150_ca7c30)
      : "memory");
}
#else
#error "ai_handle_allegiance_broken_notification: clang naked draft required"
#endif


/* ai_handle_damage (0x40460) — XBE naked draft (batch 231). */
#if defined(__clang__)
static void *(*const b40460_get)(int, int) = object_get_and_verify_type;
static int (*const b40460_c3fe30)(int unit_handle, char prefer_passenger) = ai_get_responsible_unit;
static void (*const b40460_c3b700)(int param_1, int prop_handle, float param_3, int param_4) = actor_handle_damage;
static bool (*const b40460_ca7a30)(int16_t team_a, int16_t team_b) = game_allegiance_get_team_is_friendly;
static void (*const b40460_c46f10)(int16_t type, int unit_handle, int param3, int param4, int16_t param5, int16_t param6, int16_t param7) = FUN_00046f10;
static void (*const b40460_ca7bc0)(int16_t team_a, int16_t team_b) = game_allegiance_provoke;

__attribute__((naked, noinline))
void ai_handle_damage(int victim_handle __attribute__((unused)), int source_handle __attribute__((unused)), int16_t damage_type __attribute__((unused)), float damage_amount __attribute__((unused)), int param_4 __attribute__((unused)), char skip_provoke __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "cmpw $9, %%bx\n\t"
      "setne %%al\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c3fe30]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "jne .Lai_handle_damage_1\n\t"
      "movl $0, 0x8(%%ebp)\n\t"
      "jmp .Lai_handle_damage_2\n\t"
      ".Lai_handle_damage_1:\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      ".Lai_handle_damage_2:\n\t"
      "movb 0x1c(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lai_handle_damage_3\n\t"
      "cmpw $1, %%bx\n\t"
      "je .Lai_handle_damage_3\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x1a4(%%edx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lai_handle_damage_3\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c3b700]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lai_handle_damage_3:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%esi, %%edi\n\t"
      "jne .Lai_handle_damage_4\n\t"
      "movl $1, %%ecx\n\t"
      "jmp .Lai_handle_damage_5\n\t"
      ".Lai_handle_damage_4:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lai_handle_damage_5\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movswl 0x68(%%eax), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x68(%%ecx), %%dx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[ca7a30]\n\t"
      "addl $8, %%esp\n\t"
      "negb %%al\n\t"
      "sbbl %%eax, %%eax\n\t"
      "negl %%eax\n\t"
      "addl $2, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      ".Lai_handle_damage_5:\n\t"
      "movb 0x1c(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lai_handle_damage_6\n\t"
      "cmpw $2, %%cx\n\t"
      "jne .Lai_handle_damage_6\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "pushl $2\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "jmp .Lai_handle_damage_7\n\t"
      ".Lai_handle_damage_6:\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fcomps 0x2533e4\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lai_handle_damage_8\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $2\n\t"
      ".Lai_handle_damage_7:\n\t"
      "call *%[c46f10]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".Lai_handle_damage_8:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "je .Lai_handle_damage_9\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movswl 0x68(%%eax), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x68(%%ecx), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[ca7bc0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lai_handle_damage_9:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b40460_get), [c3fe30] "m"(b40460_c3fe30), [c3b700] "m"(b40460_c3b700), [ca7a30] "m"(b40460_ca7a30), [c46f10] "m"(b40460_c46f10), [ca7bc0] "m"(b40460_ca7bc0)
      : "memory");
}
#else
#error "ai_handle_damage: clang naked draft required"
#endif


/* ai_handle_deleted_object (0x40700) — XBE naked draft (batch 232). */
#if defined(__clang__)
static void *(*const b40700_get)(int, int) = object_get_and_verify_type;
static void (*const b40700_c3cc10)(int actor_handle, int flag) = actor_delete;
static void (*const b40700_c3d330)(int actor_handle, int unit_handle) = actor_swarm_unit_died;
static void (*const b40700_c1197b0)(data_iter_t *iter, data_t *data) = data_iterator_new;
static void * (*const b40700_c119810)(data_iter_t *iterator) = data_iterator_next;
static void (*const b40700_c3b410)(int actor_handle, int old_prop, int new_prop) = FUN_0003b410;
static void (*const b40700_c64a80)(int actor_handle, int prop_handle) = prop_iterator_next;
static void (*const b40700_c44660)(int unit_handle, char param_2) = ai_conversation_unit_died;

__attribute__((naked, noinline))
void ai_handle_deleted_object(int object_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x632574, %%eax\n\t"
      "movb 0x1(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lai_handle_deleted_object_11\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movb 0x64(%%eax), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "testb $3, %%dl\n\t"
      "je .Lai_handle_deleted_object_10\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl 0x1a4(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lai_handle_deleted_object_1\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c3cc10]\n\t"
      "jmp .Lai_handle_deleted_object_2\n\t"
      ".Lai_handle_deleted_object_1:\n\t"
      "movl 0x1a8(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lai_handle_deleted_object_3\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c3d330]\n\t"
      ".Lai_handle_deleted_object_2:\n\t"
      "addl $8, %%esp\n\t"
      ".Lai_handle_deleted_object_3:\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1197b0]\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c119810]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lai_handle_deleted_object_7\n\t"
      "nop\n\t"
      ".Lai_handle_deleted_object_4:\n\t"
      "cmpl %%edi, 0x18(%%esi)\n\t"
      "jne .Lai_handle_deleted_object_5\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c3b410]\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c64a80]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lai_handle_deleted_object_6\n\t"
      ".Lai_handle_deleted_object_5:\n\t"
      "cmpl %%edi, 0x110(%%esi)\n\t"
      "jne .Lai_handle_deleted_object_6\n\t"
      "movl $0xffffffff, 0x110(%%esi)\n\t"
      "movb $0, 0x136(%%esi)\n\t"
      "movb $0, 0x135(%%esi)\n\t"
      ".Lai_handle_deleted_object_6:\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c119810]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lai_handle_deleted_object_4\n\t"
      ".Lai_handle_deleted_object_7:\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[c44660]\n\t"
      "movl 0x632574, %%eax\n\t"
      "movw 0x8b8(%%eax), %%cx\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%edx, %%edx\n\t"
      "testw %%cx, %%cx\n\t"
      "jle .Lai_handle_deleted_object_10\n\t"
      "jmp .Lai_handle_deleted_object_8\n\t"
      "leal (%%esp), %%esp\n\t"
      "nop\n\t"
      ".Lai_handle_deleted_object_8:\n\t"
      "movswl %%dx, %%esi\n\t"
      "leal 0x8bc(,%%esi,4), %%esi\n\t"
      "cmpl %%edi, (%%esi,%%eax,1)\n\t"
      "jne .Lai_handle_deleted_object_9\n\t"
      "decl %%ecx\n\t"
      "movw %%cx, 0x8b8(%%eax)\n\t"
      "movl 0x632574, %%eax\n\t"
      "movw 0x8b8(%%eax), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jle .Lai_handle_deleted_object_9\n\t"
      "movswl %%cx, %%ecx\n\t"
      "movl 0x8bc(%%eax,%%ecx,4), %%ecx\n\t"
      "movl %%ecx, (%%esi,%%eax,1)\n\t"
      "movl 0x632574, %%eax\n\t"
      ".Lai_handle_deleted_object_9:\n\t"
      "movw 0x8b8(%%eax), %%cx\n\t"
      "incl %%edx\n\t"
      "cmpw %%cx, %%dx\n\t"
      "jl .Lai_handle_deleted_object_8\n\t"
      ".Lai_handle_deleted_object_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".Lai_handle_deleted_object_11:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b40700_get), [c3cc10] "m"(b40700_c3cc10), [c3d330] "m"(b40700_c3d330), [c1197b0] "m"(b40700_c1197b0), [c119810] "m"(b40700_c119810), [c3b410] "m"(b40700_c3b410), [c64a80] "m"(b40700_c64a80), [c44660] "m"(b40700_c44660)
      : "memory");
}
#else
#error "ai_handle_deleted_object: clang naked draft required"
#endif


/* ai_handle_unit_effect (0x40860) — readable C lift. */
void ai_handle_unit_effect(int unit_handle, int effect_type, int priority)
{
  extern char DAT_002575c0[];
  extern char DAT_00257800[];
  extern char DAT_002577c8[];
  char *unit;
  char *child;
  int now;
  int16_t object_type;
  int child_handle;

  if (!*(unsigned char *)(*(unsigned char **)0x632574 + 1)) {
    return;
  }
  if ((int16_t)priority < 0 || (int16_t)priority >= 5) {
    display_assert(DAT_00257800, DAT_002575c0, 0x729, true);
    system_exit(-1);
  }
  if ((int16_t)effect_type < 0 || (int16_t)effect_type >= 4) {
    display_assert(DAT_002577c8, DAT_002575c0, 0x72a, true);
    system_exit(-1);
  }
  if (unit_handle == -1 || (int16_t)priority <= 0) {
    return;
  }
  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  now = game_time_get();
  if (game_connection() == 0 && *(char *)0x5ac9c6 != 0 &&
      *(int *)(unit + 0x1c8) != -1) {
    return;
  }
  if ((int16_t)effect_type <= *(int16_t *)(unit + 0x1cc) &&
      now <= *(int *)(unit + 0x1d0) + 0x1e) {
    return;
  }
  object_type = *(int16_t *)(unit + 0x64);
  *(int16_t *)(unit + 0x1cc) = (int16_t)effect_type;
  *(int *)(unit + 0x1d0) = now;
  if (object_type == 1) {
    child_handle = *(int *)(unit + 0xc8);
    while (child_handle != -1) {
      child = (char *)object_get_and_verify_type(child_handle, -1);
      if (*(int16_t *)(child + 0x64) == 0) {
        actors_handle_unit_effect(child_handle, (int16_t)effect_type, priority);
      }
      child_handle = *(int *)(child + 0xc4);
    }
    return;
  }
  if (object_type == 0) {
    actors_handle_unit_effect(unit_handle, (int16_t)effect_type, priority);
  }
}


/* ai_disconnect_from_structure_bsp (0x40a80) — XBE naked draft (batch 106). */
#if defined(__clang__)
static scenario_t * (*const b40a80_c18e380)(void) = global_scenario_get;
static void *(*const b40a80_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b40a80_c59a00)(int *iter, int clump_handle) = encounter_actor_iterator_new;
static int (*const b40a80_c59a50)(int *iter) = encounter_actor_iterator_next;
static char * (*const b40a80_c49ac0)(int actor_handle, int object_handle, char with_actor, char *buf, int buf_size) = ai_debug_describe_actor;
static void (*const b40a80_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b40a80_exitfn)(int) = system_exit;
static bool (*const b40a80_ca7a30)(int16_t team_a, int16_t team_b) = game_allegiance_get_team_is_friendly;
static void (*const b40a80_c64540)(int *out, int actor_handle) = FUN_00064540;
static int (*const b40a80_c64570)(int *iter) = FUN_00064570;
static void * (*const b40a80_cba6c0)(void) = players_get_combined_pvs;
static int (*const b40a80_c13d7f0)(int object_handle) = object_get_root_parent;
static void *(*const b40a80_get)(int, int) = object_get_and_verify_type;
static void (*const b40a80_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b40a80_c3ae60)(int actor_handle, int unit_handle) = actor_swarm_detach_from_unit;
static int (*const b40a80_c3edc0)(char flags, int unit_index, int actv_tag_index, int encounter_index, int squad_index, char param6, int exclude_actor_handle, char encounter_flag, short starting_location_index, short squad_position_index, unsigned short param11, char param12) = actor_create_for_unit;
static void (*const b40a80_odel)(int) = object_delete;
static void (*const b40a80_c3b5e0)(int actor_handle) = actor_flush_position_indices;
static void (*const b40a80_c59480)(int actor_handle, char flag) = encounter_detach_actor;
static void (*const b40a80_c59740)(int actor_handle) = encounterless_attach_actor;
static void (*const b40a80_c5baa0)(int encounter_handle) = encounter_force_deactivate;
static void (*const b40a80_c3b630)(int actor_handle) = actor_flush_structure_indices;

__attribute__((naked, noinline))
void ai_disconnect_from_structure_bsp(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x174, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c18e380]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x42c(%%ebx), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "movl %%ebx, -0x34(%%ebp)\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "jle .Lai_disconnect_from_structure_bsp_28\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lai_disconnect_from_structure_bsp_1:\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl 0x5ab270, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movb 0xd(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lai_disconnect_from_structure_bsp_27\n\t"
      "cmpw $0, 0x2a(%%eax)\n\t"
      "jle .Lai_disconnect_from_structure_bsp_27\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59a00]\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c59a50]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "je .Lai_disconnect_from_structure_bsp_27\n\t"
      "jmp .Lai_disconnect_from_structure_bsp_3\n\t"
      ".Lai_disconnect_from_structure_bsp_2:\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      ".Lai_disconnect_from_structure_bsp_3:\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "pushl $0x100\n\t"
      "leal -0x174(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c49ac0]\n\t"
      "movl 0x270(%%esi), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lai_disconnect_from_structure_bsp_6\n\t"
      "cmpw $5, 0x268(%%esi)\n\t"
      "jl .Lai_disconnect_from_structure_bsp_6\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movw 0x24(%%edi), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .Lai_disconnect_from_structure_bsp_5\n\t"
      "cmpw $5, %%ax\n\t"
      "jg .Lai_disconnect_from_structure_bsp_5\n\t"
      "cmpl $-1, 0xc(%%edi)\n\t"
      "jne .Lai_disconnect_from_structure_bsp_4\n\t"
      "pushl $1\n\t"
      "pushl $0x8b9\n\t"
      "pushl $0x2575c0\n\t"
      "pushl $0x25795c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_disconnect_from_structure_bsp_4:\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "movl 0x5ab23c, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      ".Lai_disconnect_from_structure_bsp_5:\n\t"
      "movb 0x12e(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_disconnect_from_structure_bsp_26\n\t"
      "movl 0x88(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lai_disconnect_from_structure_bsp_26\n\t"
      "cmpl $0x5a, %%eax\n\t"
      "jge .Lai_disconnect_from_structure_bsp_26\n\t"
      "flds 0x11c(%%edi)\n\t"
      "fcomps 0x253f34\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lai_disconnect_from_structure_bsp_26\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lai_disconnect_from_structure_bsp_10\n\t"
      ".Lai_disconnect_from_structure_bsp_6:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x3e(%%esi), %%dx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "call *%[ca7a30]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lai_disconnect_from_structure_bsp_26\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c64540]\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c64570]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lai_disconnect_from_structure_bsp_26\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lai_disconnect_from_structure_bsp_7:\n\t"
      "movb 0x12e(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lai_disconnect_from_structure_bsp_9\n\t"
      "cmpw $2, 0x32(%%eax)\n\t"
      "jge .Lai_disconnect_from_structure_bsp_8\n\t"
      "flds 0x11c(%%eax)\n\t"
      "fcomps 0x254644\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lai_disconnect_from_structure_bsp_9\n\t"
      ".Lai_disconnect_from_structure_bsp_8:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".Lai_disconnect_from_structure_bsp_9:\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c64570]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lai_disconnect_from_structure_bsp_7\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_disconnect_from_structure_bsp_26\n\t"
      ".Lai_disconnect_from_structure_bsp_10:\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_disconnect_from_structure_bsp_24\n\t"
      "movl 0x28(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lai_disconnect_from_structure_bsp_26\n\t"
      "movl 0x6325a0, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[cba6c0]\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpw %%bx, 0x2(%%edi)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "jle .Lai_disconnect_from_structure_bsp_15\n\t"
      ".Lai_disconnect_from_structure_bsp_11:\n\t"
      "movswl %%bx, %%edx\n\t"
      "movl 0x18(%%edi,%%edx,4), %%eax\n\t"
      "leal 0x18(%%edi,%%edx,4), %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c13d7f0]\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movw 0x4c(%%eax), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lai_disconnect_from_structure_bsp_12\n\t"
      "movswl %%ax, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "sarl $5, %%eax\n\t"
      "testl %%edx, (%%ecx,%%eax,4)\n\t"
      "jne .Lai_disconnect_from_structure_bsp_14\n\t"
      ".Lai_disconnect_from_structure_bsp_12:\n\t"
      "cmpw $0x10, -0x8(%%ebp)\n\t"
      "jl .Lai_disconnect_from_structure_bsp_13\n\t"
      "pushl $1\n\t"
      "pushl $0x8eb\n\t"
      "pushl $0x2575c0\n\t"
      "pushl $0x257918\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_disconnect_from_structure_bsp_13:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movswl %%ax, %%edx\n\t"
      "incl %%eax\n\t"
      "movl %%ecx, -0x74(%%ebp,%%edx,4)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".Lai_disconnect_from_structure_bsp_14:\n\t"
      "incl %%ebx\n\t"
      "cmpw 0x2(%%edi), %%bx\n\t"
      "jl .Lai_disconnect_from_structure_bsp_11\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "testw %%bx, %%bx\n\t"
      "jne .Lai_disconnect_from_structure_bsp_16\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      ".Lai_disconnect_from_structure_bsp_15:\n\t"
      "movb 0x5aca63, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_disconnect_from_structure_bsp_24\n\t"
      "leal -0x174(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x2578e4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Lai_disconnect_from_structure_bsp_24\n\t"
      ".Lai_disconnect_from_structure_bsp_16:\n\t"
      "movswl 0x2(%%edi), %%edi\n\t"
      "cmpw %%di, %%bx\n\t"
      "movl %%edi, -0x30(%%ebp)\n\t"
      "jne .Lai_disconnect_from_structure_bsp_17\n\t"
      "movb 0x5aca63, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_disconnect_from_structure_bsp_26\n\t"
      "leal -0x174(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2578b8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Lai_disconnect_from_structure_bsp_26\n\t"
      ".Lai_disconnect_from_structure_bsp_17:\n\t"
      "xorl %%eax, %%eax\n\t"
      "testw %%bx, %%bx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jle .Lai_disconnect_from_structure_bsp_21\n\t"
      "movzwl %%bx, %%ecx\n\t"
      "leal -0x74(%%ebp), %%edi\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "jmp .Lai_disconnect_from_structure_bsp_18\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lai_disconnect_from_structure_bsp_18:\n\t"
      "movl (%%edi), %%esi\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c3ae60]\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "pushl $2\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl 0x34(%%eax), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x3a(%%eax), %%cx\n\t"
      "movl 0x5c(%%eax), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "call *%[c3edc0]\n\t"
      "addl $0x38, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lai_disconnect_from_structure_bsp_19\n\t"
      "pushl %%esi\n\t"
      "call *%[odel]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .Lai_disconnect_from_structure_bsp_20\n\t"
      ".Lai_disconnect_from_structure_bsp_19:\n\t"
      "incl -0x8(%%ebp)\n\t"
      ".Lai_disconnect_from_structure_bsp_20:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "addl $4, %%edi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jne .Lai_disconnect_from_structure_bsp_18\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x30(%%ebp), %%edi\n\t"
      ".Lai_disconnect_from_structure_bsp_21:\n\t"
      "movb 0x5aca63, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lai_disconnect_from_structure_bsp_23\n\t"
      "cmpw %%bx, %%ax\n\t"
      "movl $0x2578a8, %%ecx\n\t"
      "jl .Lai_disconnect_from_structure_bsp_22\n\t"
      "movl $0x25386f, %%ecx\n\t"
      ".Lai_disconnect_from_structure_bsp_22:\n\t"
      "pushl %%ecx\n\t"
      "movswl %%ax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movswl %%di, %%edx\n\t"
      "pushl %%edx\n\t"
      "movswl %%bx, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x174(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x257878\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".Lai_disconnect_from_structure_bsp_23:\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      ".Lai_disconnect_from_structure_bsp_24:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_disconnect_from_structure_bsp_26\n\t"
      "movb 0x5aca63, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_disconnect_from_structure_bsp_25\n\t"
      "leal -0x174(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x25784c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lai_disconnect_from_structure_bsp_25:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movw 0x3a(%%esi), %%cx\n\t"
      "movl %%eax, 0x30(%%esi)\n\t"
      "movw %%cx, 0x38(%%esi)\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c3b5e0]\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c59480]\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59740]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lai_disconnect_from_structure_bsp_26:\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c59a50]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jne .Lai_disconnect_from_structure_bsp_2\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl -0x34(%%ebp), %%ebx\n\t"
      ".Lai_disconnect_from_structure_bsp_27:\n\t"
      "pushl %%edi\n\t"
      "call *%[c5baa0]\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movl 0x42c(%%ebx), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jl .Lai_disconnect_from_structure_bsp_1\n\t"
      ".Lai_disconnect_from_structure_bsp_28:\n\t"
      "movl 0x632574, %%eax\n\t"
      "movl 0x8(%%eax), %%esi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "cmpl %%edi, %%esi\n\t"
      "je .Lai_disconnect_from_structure_bsp_33\n\t"
      ".Lai_disconnect_from_structure_bsp_29:\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movb 0x9(%%eax), %%cl\n\t"
      "movl 0x2c(%%eax), %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lai_disconnect_from_structure_bsp_30\n\t"
      "pushl $1\n\t"
      "pushl $0x94a\n\t"
      "pushl $0x2575c0\n\t"
      "pushl $0x257830\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_disconnect_from_structure_bsp_30:\n\t"
      "pushl %%esi\n\t"
      "call *%[c3b630]\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c64540]\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c64570]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lai_disconnect_from_structure_bsp_32\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lai_disconnect_from_structure_bsp_31:\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movw %%di, 0x100(%%eax)\n\t"
      "movl %%edi, 0xfc(%%eax)\n\t"
      "movl %%edi, 0xec(%%eax)\n\t"
      "call *%[c64570]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lai_disconnect_from_structure_bsp_31\n\t"
      ".Lai_disconnect_from_structure_bsp_32:\n\t"
      "cmpl %%edi, %%ebx\n\t"
      "movl %%ebx, %%esi\n\t"
      "jne .Lai_disconnect_from_structure_bsp_29\n\t"
      ".Lai_disconnect_from_structure_bsp_33:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(b40a80_c18e380), [dget] "m"(b40a80_dget), [c59a00] "m"(b40a80_c59a00), [c59a50] "m"(b40a80_c59a50), [c49ac0] "m"(b40a80_c49ac0), [assert] "m"(b40a80_assert), [exitfn] "m"(b40a80_exitfn), [ca7a30] "m"(b40a80_ca7a30), [c64540] "m"(b40a80_c64540), [c64570] "m"(b40a80_c64570), [cba6c0] "m"(b40a80_cba6c0), [c13d7f0] "m"(b40a80_c13d7f0), [get] "m"(b40a80_get), [c8f390] "m"(b40a80_c8f390), [c3ae60] "m"(b40a80_c3ae60), [c3edc0] "m"(b40a80_c3edc0), [odel] "m"(b40a80_odel), [c3b5e0] "m"(b40a80_c3b5e0), [c59480] "m"(b40a80_c59480), [c59740] "m"(b40a80_c59740), [c5baa0] "m"(b40a80_c5baa0), [c3b630] "m"(b40a80_c3b630)
      : "memory");
}
#else
#error "ai_disconnect_from_structure_bsp: clang naked draft required"
#endif


/* ai_consider_major_upgrade (0x41250) — XBE naked draft (batch 225). */
#if defined(__clang__)
static void *(*const b41250_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char * (*const b41250_c1c270)(char *encounter, int16_t squad_index) = encounter_get_squad;
static int *(*const b41250_gseed)(void) = get_global_random_seed_address;
static float (*const b41250_rmreal)(unsigned int *) = random_math_real;
static scenario_t * (*const b41250_c18e380)(void) = global_scenario_get;
static void *(*const b41250_elem)(void *, int, int) = tag_block_get_element;
static char * (*const b41250_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b41250_cff4d0)(int channel, const char *format, ...) = console_printf;
static void (*const b41250_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
char ai_consider_major_upgrade(int encounter_handle __attribute__((unused)), int16_t squad_index __attribute__((unused)), float spawn_cost __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "movl 0x5ab270, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c270]\n\t"
      "movl 0x632574, %%edx\n\t"
      "flds 0xc(%%edx)\n\t"
      "movl %%eax, %%esi\n\t"
      "fmuls 0x2579e8\n\t"
      "addl $0x10, %%esp\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fchs\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fabs\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fabs\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lai_consider_major_upgrade_1\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .Lai_consider_major_upgrade_2\n\t"
      ".Lai_consider_major_upgrade_1:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      ".Lai_consider_major_upgrade_2:\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fsts -0x14(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "fadds 0x10(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fcomps -0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lai_consider_major_upgrade_3\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lai_consider_major_upgrade_4\n\t"
      ".Lai_consider_major_upgrade_3:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".Lai_consider_major_upgrade_4:\n\t"
      "movzbl %%bl, %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "fsubs 0x10(%%ebp)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fadds 0x8(%%esi)\n\t"
      "fstps 0x8(%%esi)\n\t"
      "movl 0x632574, %%eax\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fadds 0xc(%%eax)\n\t"
      "fstps 0xc(%%eax)\n\t"
      "movb 0x5aca49, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_consider_major_upgrade_6\n\t"
      "pushl $0xb0\n\t"
      "andl $0xffff, %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "movl %%eax, %%esi\n\t"
      "movl $0x2579e4, %%eax\n\t"
      "jne .Lai_consider_major_upgrade_5\n\t"
      "movl $0x2579e0, %%eax\n\t"
      ".Lai_consider_major_upgrade_5:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "subl $0x28, %%esp\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "leal 0x80(%%esi), %%ecx\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%eax\n\t"
      "flds 0x10(%%ebp)\n\t"
      "movswl 0xc(%%ebp), %%eax\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0xe8\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $0x257988\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x4c, %%esp\n\t"
      "pushl $0x5ab100\n\t"
      "pushl $0x257984\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lai_consider_major_upgrade_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [dget] "m"(b41250_dget), [c1c270] "m"(b41250_c1c270), [gseed] "m"(b41250_gseed), [rmreal] "m"(b41250_rmreal), [c18e380] "m"(b41250_c18e380), [elem] "m"(b41250_elem), [c8d9d0] "m"(b41250_c8d9d0), [cff4d0] "m"(b41250_cff4d0), [c8f390] "m"(b41250_c8f390)
      : "memory");
}
#else
#error "ai_consider_major_upgrade: clang naked draft required"
#endif


/* ai_test_line_of_sight (0x416e0) — XBE naked draft (batch 108). */
#if defined(__clang__)
static void (*const b416e0_c4b770)(void) = ai_debug_lineofsight;
static void (*const b416e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b416e0_exitfn)(int) = system_exit;
static bool (*const b416e0_c18e800)(int cluster_index, int16_t cluster_index1) = scenario_ensure_point_within_world;
static short (*const b416e0_cfff80)(void) = game_connection;
static bool (*const b416e0_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;
static float (*const b416e0_c18e690)(void) = FUN_0018e690;
static float (*const b416e0_norm)(float *) = normalize3d;
static bool (*const b416e0_v30d0)(unsigned int, float *, float *, int, short *) = FUN_000130d0;
static float *(*const b416e0_vsca)(float *, float *, float, float *) = vector3d_scale_add;

__attribute__((naked, noinline))
int ai_test_line_of_sight(float *origin __attribute__((unused)), int bsp __attribute__((unused)), float *target __attribute__((unused)), int param_4 __attribute__((unused)), short param_5 __attribute__((unused)), char param_6 __attribute__((unused)), int param_7 __attribute__((unused)), char param_8 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x80, %%esp\n\t"
      "movb 0x5aca6a, %%al\n\t"
      "testb %%al, %%al\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "je .Lai_test_line_of_sight_1\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c4b770]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lai_test_line_of_sight_1:\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "jl .Lai_test_line_of_sight_2\n\t"
      "pushl $1\n\t"
      "pushl $0x349\n\t"
      "pushl $0x2575c0\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_test_line_of_sight_2:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "incw %%ax\n\t"
      "incw 0x5ac65c\n\t"
      "cmpw $-1, %%bx\n\t"
      "movw $2, 0x5a8c80(,%%ecx,2)\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "je .Lai_test_line_of_sight_3\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lai_test_line_of_sight_3\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c18e800]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_test_line_of_sight_20\n\t"
      ".Lai_test_line_of_sight_3:\n\t"
      "movl $0xc2a3, %%ebx\n\t"
      "call *%[cfff80]\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lai_test_line_of_sight_4\n\t"
      "movb 0x5ac9c4, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_test_line_of_sight_4\n\t"
      "movl $0x23, %%ebx\n\t"
      ".Lai_test_line_of_sight_4:\n\t"
      "movb 0x1c(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_test_line_of_sight_5\n\t"
      "orl $0x10, %%ebx\n\t"
      "jmp .Lai_test_line_of_sight_6\n\t"
      ".Lai_test_line_of_sight_5:\n\t"
      "orl $4, %%ebx\n\t"
      ".Lai_test_line_of_sight_6:\n\t"
      "movb 0x24(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_test_line_of_sight_7\n\t"
      "andl $0xfffffdff, %%ebx\n\t"
      ".Lai_test_line_of_sight_7:\n\t"
      "incw 0x5ac5d4\n\t"
      "flds (%%esi)\n\t"
      "fsubs (%%edi)\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "leal -0x80(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "flds 0x4(%%esi)\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lai_test_line_of_sight_8\n\t"
      "movb $1, 0xf(%%ebp)\n\t"
      "jmp .Lai_test_line_of_sight_9\n\t"
      ".Lai_test_line_of_sight_8:\n\t"
      "movl -0x6c(%%ebp), %%edx\n\t"
      "movb $0, 0xf(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      ".Lai_test_line_of_sight_9:\n\t"
      "leal -0x68(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x7c(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18e690]\n\t"
      "fcoms 0x2533f0\n\t"
      "addl $0xc, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lai_test_line_of_sight_17\n\t"
      "fcomps 0x253f3c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lai_test_line_of_sight_15\n\t"
      "cmpw $0, 0x18(%%ebp)\n\t"
      "je .Lai_test_line_of_sight_16\n\t"
      "flds 0x4(%%edi)\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "pushl %%edx\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds (%%esi)\n\t"
      "fsubs (%%edi)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lai_test_line_of_sight_10\n\t"
      "movl 0x31fc3c, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      ".Lai_test_line_of_sight_10:\n\t"
      "cmpw $1, 0x18(%%ebp)\n\t"
      "movb 0xf(%%ebp), %%al\n\t"
      "jne .Lai_test_line_of_sight_12\n\t"
      "flds -0x18(%%ebp)\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "fmuls 0x25337c\n\t"
      "leal -0x80(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "fld %%st(0)\n\t"
      "pushl %%esi\n\t"
      "fadds (%%edi)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x25337c\n\t"
      "fld %%st(0)\n\t"
      "fadds 0x4(%%edi)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x25337c\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fadds 0x8(%%edi)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds (%%edi)\n\t"
      ".byte 0xd8, 0xe2\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x4(%%edi)\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x8(%%edi)\n\t"
      "incw 0x5ac5d4\n\t"
      "fsubs -0x8(%%ebp)\n\t"
      "testb %%al, %%al\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "je .Lai_test_line_of_sight_11\n\t"
      "call *%[v30d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lai_test_line_of_sight_15\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "leal -0x80(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "jmp .Lai_test_line_of_sight_13\n\t"
      ".Lai_test_line_of_sight_11:\n\t"
      "call *%[v30d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "negb %%al\n\t"
      "sbbb %%al, %%al\n\t"
      "incb %%al\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "jne .Lai_test_line_of_sight_15\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "incw 0x5ac5d4\n\t"
      "leal -0x80(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[v30d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "negb %%al\n\t"
      "sbbb %%al, %%al\n\t"
      "incb %%al\n\t"
      "jmp .Lai_test_line_of_sight_14\n\t"
      ".Lai_test_line_of_sight_12:\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_test_line_of_sight_18\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3dcccccd\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[vsca]\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0xbdcccccd\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[vsca]\n\t"
      "movl 0x31fc50, %%eax\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x3dcccccd\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[vsca]\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "incw 0x5ac5d4\n\t"
      "leal -0x80(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[v30d0]\n\t"
      "addl $0x44, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lai_test_line_of_sight_15\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "incw 0x5ac5d4\n\t"
      "leal -0x80(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[v30d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lai_test_line_of_sight_15\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "leal -0x80(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      ".Lai_test_line_of_sight_13:\n\t"
      "incw 0x5ac5d4\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[v30d0]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_test_line_of_sight_14:\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_test_line_of_sight_16\n\t"
      ".Lai_test_line_of_sight_15:\n\t"
      "movl $1, %%esi\n\t"
      "jmp .Lai_test_line_of_sight_21\n\t"
      ".Lai_test_line_of_sight_16:\n\t"
      "movb 0xf(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_test_line_of_sight_18\n\t"
      "xorl %%esi, %%esi\n\t"
      "jmp .Lai_test_line_of_sight_21\n\t"
      ".Lai_test_line_of_sight_17:\n\t"
      "fstp %%st(0)\n\t"
      ".Lai_test_line_of_sight_18:\n\t"
      "flds (%%esi)\n\t"
      "fsubs (%%edi)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lai_test_line_of_sight_20\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lai_test_line_of_sight_19\n\t"
      "movl $2, %%esi\n\t"
      "jmp .Lai_test_line_of_sight_21\n\t"
      ".Lai_test_line_of_sight_19:\n\t"
      "flds 0x2533c8\n\t"
      "movl $3, %%esi\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fcomps 0x2533d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lai_test_line_of_sight_21\n\t"
      ".Lai_test_line_of_sight_20:\n\t"
      "movl $4, %%esi\n\t"
      ".Lai_test_line_of_sight_21:\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "jg .Lai_test_line_of_sight_22\n\t"
      "pushl $1\n\t"
      "pushl $0x3f0\n\t"
      "pushl $0x2575c0\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_test_line_of_sight_22:\n\t"
      "decw 0x4761d8\n\t"
      "popl %%edi\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c4b770] "m"(b416e0_c4b770), [assert] "m"(b416e0_assert), [exitfn] "m"(b416e0_exitfn), [c18e800] "m"(b416e0_c18e800), [cfff80] "m"(b416e0_cfff80), [ray] "m"(b416e0_ray), [c18e690] "m"(b416e0_c18e690), [norm] "m"(b416e0_norm), [v30d0] "m"(b416e0_v30d0), [vsca] "m"(b416e0_vsca)
      : "memory");
}
#else
#error "ai_test_line_of_sight: clang naked draft required"
#endif


/* ai_test_ballistic_line_of_fire (0x41ad0) — XBE naked draft (batch 109). */
#if defined(__clang__)
static void *(*const b41ad0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b41ad0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b41ad0_exitfn)(int) = system_exit;
static int16_t (*const b41ad0_c41420)(int actor_handle, int16_t max_count, ai_firing_pos_entry_t *buf) = FUN_00041420;
static bool (*const b41ad0_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;
static bool (*const b41ad0_c10e040)(float *line_a_start, float *line_a_dir, float *line_b_start, float *line_b_dir, float radius) = vector_intersects_pill3d;

__attribute__((naked, noinline))
char ai_test_ballistic_line_of_fire(int actor_handle __attribute__((unused)), int param_2 __attribute__((unused)), int target __attribute__((unused)), float *impact_point __attribute__((unused)), float accel __attribute__((unused)), int param_6 __attribute__((unused)), char param_7 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x594, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "jl .Lai_test_ballistic_line_of_fire_1\n\t"
      "pushl $1\n\t"
      "pushl $0x408\n\t"
      "pushl $0x2575c0\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_test_ballistic_line_of_fire_1:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "leal -0x594(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movswl %%ax, %%ecx\n\t"
      "incw %%ax\n\t"
      "pushl $0x20\n\t"
      "pushl %%esi\n\t"
      "movw $4, 0x5a8c80(,%%ecx,2)\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "call *%[c41420]\n\t"
      "movb 0x5aca48, %%cl\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "jne .Lai_test_ballistic_line_of_fire_5\n\t"
      "movb $1, 0x5f8cb4\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, 0x5f8cb8\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x5f8cbc\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x5f8cc0\n\t"
      "movl %%ebx, %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "movl %%ecx, 0x5f8cc4\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x5f8cc8\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw $0x10, %%ax\n\t"
      "movl %%edx, 0x5f8ccc\n\t"
      "movl %%ecx, 0x5f8e94\n\t"
      "jle .Lai_test_ballistic_line_of_fire_2\n\t"
      "movl $0x10, %%eax\n\t"
      "jmp .Lai_test_ballistic_line_of_fire_3\n\t"
      ".Lai_test_ballistic_line_of_fire_2:\n\t"
      "movswl %%ax, %%eax\n\t"
      ".Lai_test_ballistic_line_of_fire_3:\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, 0x5f8cd0\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "jle .Lai_test_ballistic_line_of_fire_6\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lai_test_ballistic_line_of_fire_4:\n\t"
      "leal (%%eax,%%eax,4), %%ecx\n\t"
      "shll $3, %%ecx\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "shll $2, %%edx\n\t"
      "leal -0x590(%%ebp,%%ecx,1), %%esi\n\t"
      "movl (%%esi), %%ebx\n\t"
      "leal 0x5f8cd4(%%edx), %%edi\n\t"
      "movl %%ebx, (%%edi)\n\t"
      "movl 0x4(%%esi), %%ebx\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "movl %%ebx, 0x4(%%edi)\n\t"
      "movl %%esi, 0x8(%%edi)\n\t"
      "leal -0x584(%%ebp,%%ecx,1), %%esi\n\t"
      "movl (%%esi), %%edi\n\t"
      "movl -0x570(%%ebp,%%ecx,1), %%ecx\n\t"
      "leal 0x5f8d94(%%edx), %%edx\n\t"
      "movl %%edi, (%%edx)\n\t"
      "movl 0x4(%%esi), %%edi\n\t"
      "movl 0x8(%%esi), %%esi\n\t"
      "movl %%edi, 0x4(%%edx)\n\t"
      "movl %%esi, 0x8(%%edx)\n\t"
      "movl %%ecx, 0x5f8e54(,%%eax,4)\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl 0x5f8cd0, %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lai_test_ballistic_line_of_fire_4\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      ".Lai_test_ballistic_line_of_fire_5:\n\t"
      "movl 0x5f8e94, %%ecx\n\t"
      ".Lai_test_ballistic_line_of_fire_6:\n\t"
      "movb 0x20(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl $0xc2b3, 0xc(%%ebp)\n\t"
      "je .Lai_test_ballistic_line_of_fire_7\n\t"
      "movl $0xc0b3, 0xc(%%ebp)\n\t"
      ".Lai_test_ballistic_line_of_fire_7:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "flds 0x2533c0\n\t"
      "flds 0x254640\n\t"
      "movl (%%edi), %%edx\n\t"
      "fcomps 0x10(%%ebp)\n\t"
      "movl 0x4(%%edi), %%esi\n\t"
      "movl 0x8(%%edi), %%edi\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movl 0x8(%%ebx), %%eax\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "testb $0x41, %%ah\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "jne .Lai_test_ballistic_line_of_fire_8\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%eax, 0x20(%%ebp)\n\t"
      "jmp .Lai_test_ballistic_line_of_fire_9\n\t"
      ".Lai_test_ballistic_line_of_fire_8:\n\t"
      "movl $0x40c00000, 0x20(%%ebp)\n\t"
      ".Lai_test_ballistic_line_of_fire_9:\n\t"
      "movb 0x5aca48, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lai_test_ballistic_line_of_fire_10\n\t"
      "cmpl $0x40, %%ecx\n\t"
      "jge .Lai_test_ballistic_line_of_fire_10\n\t"
      "leal (%%ecx,%%ecx,2), %%ecx\n\t"
      "leal 0x5f8e98(,%%ecx,4), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl %%esi, 0x4(%%eax)\n\t"
      "movl %%edi, 0x8(%%eax)\n\t"
      "incl 0x5f8e94\n\t"
      ".Lai_test_ballistic_line_of_fire_10:\n\t"
      "fsubrs 0x20(%%ebp)\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "leal -0x94(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fsts 0x14(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "leal -0x44(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fmuls 0x18(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fsubs -0x8(%%ebp)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "addl $0x14, %%esp\n\t"
      "movb %%al, %%bl\n\t"
      "negb %%bl\n\t"
      "sbbb %%bl, %%bl\n\t"
      "incb %%bl\n\t"
      "je .Lai_test_ballistic_line_of_fire_16\n\t"
      "flds -0x18(%%ebp)\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpw %%si, -0x1c(%%ebp)\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fsubs -0x8(%%ebp)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "jle .Lai_test_ballistic_line_of_fire_12\n\t"
      ".Lai_test_ballistic_line_of_fire_11:\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%eax\n\t"
      "shll $3, %%eax\n\t"
      "movl -0x570(%%ebp,%%eax,1), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x584(%%ebp,%%eax,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x590(%%ebp,%%eax,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c10e040]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lai_test_ballistic_line_of_fire_14\n\t"
      "incl %%esi\n\t"
      "cmpw -0x1c(%%ebp), %%si\n\t"
      "jl .Lai_test_ballistic_line_of_fire_11\n\t"
      ".Lai_test_ballistic_line_of_fire_12:\n\t"
      "flds 0x14(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "fmuls 0x18(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%esi\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "fadds -0x24(%%ebp)\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds 0x20(%%ebp)\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fadds 0x254640\n\t"
      "fsts 0x20(%%ebp)\n\t"
      "fcomps 0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lai_test_ballistic_line_of_fire_13\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%eax, 0x20(%%ebp)\n\t"
      ".Lai_test_ballistic_line_of_fire_13:\n\t"
      "fcoms 0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lai_test_ballistic_line_of_fire_15\n\t"
      "movl 0x5f8e94, %%ecx\n\t"
      "jmp .Lai_test_ballistic_line_of_fire_9\n\t"
      ".Lai_test_ballistic_line_of_fire_14:\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .Lai_test_ballistic_line_of_fire_16\n\t"
      ".Lai_test_ballistic_line_of_fire_15:\n\t"
      "fstp %%st(0)\n\t"
      ".Lai_test_ballistic_line_of_fire_16:\n\t"
      "movb 0x5aca48, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lai_test_ballistic_line_of_fire_18\n\t"
      "movl 0x5f8e94, %%eax\n\t"
      "cmpl $0x40, %%eax\n\t"
      "jge .Lai_test_ballistic_line_of_fire_17\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "leal 0x5f8e98(,%%ecx,4), %%edx\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl %%edi, 0x8(%%edx)\n\t"
      "movl 0x5f8e94, %%ecx\n\t"
      "movb 0x5aca48, %%al\n\t"
      "incl %%ecx\n\t"
      "testb %%al, %%al\n\t"
      "movl %%ecx, 0x5f8e94\n\t"
      "jne .Lai_test_ballistic_line_of_fire_18\n\t"
      ".Lai_test_ballistic_line_of_fire_17:\n\t"
      "movb %%bl, 0x5f8cb5\n\t"
      ".Lai_test_ballistic_line_of_fire_18:\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "jg .Lai_test_ballistic_line_of_fire_19\n\t"
      "pushl $1\n\t"
      "pushl $0x478\n\t"
      "pushl $0x2575c0\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_test_ballistic_line_of_fire_19:\n\t"
      "decw 0x4761d8\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b41ad0_dget), [assert] "m"(b41ad0_assert), [exitfn] "m"(b41ad0_exitfn), [c41420] "m"(b41ad0_c41420), [ray] "m"(b41ad0_ray), [c10e040] "m"(b41ad0_c10e040)
      : "memory");
}
#else
#error "ai_test_ballistic_line_of_fire: clang naked draft required"
#endif


/* ai_handle_editing (0x41e80) — XBE naked draft (batch 106). */
#if defined(__clang__)
static scenario_t * (*const b41e80_c18e380)(void) = global_scenario_get;
static void *(*const b41e80_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b41e80_elem)(void *, int, int) = tag_block_get_element;
static char * (*const b41e80_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b41e80_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b41e80_exitfn)(int) = system_exit;
static void (*const b41e80_c8dae0)(void *dest, const void *src, unsigned int size) = csmemmove;
static void *(*const b41e80_memset)(void *, int, unsigned int) = csmemset;
static void (*const b41e80_c59a00)(int *iter, int clump_handle) = encounter_actor_iterator_new;
static int (*const b41e80_c59a50)(int *iter) = encounter_actor_iterator_next;
static void (*const b41e80_c3cf10)(int actor_handle, char by_player, char no_delete) = actor_kill;
static void (*const b41e80_c16ff0)(int actor_handle) = FUN_00016ff0;
static void (*const b41e80_c3b5e0)(int actor_handle) = actor_flush_position_indices;
static void (*const b41e80_c59b10)(void *iter, char flag) = encounter_iterator_next;
static int (*const b41e80_c59b50)(void *iter) = FUN_00059b50;
static void (*const b41e80_c42ca0)(void) = ai_communication_dispose_from_old_map;
static void (*const b41e80_c540e0)(void) = ai_profile_dispose_from_old_map;
static void (*const b41e80_c58fb0)(void) = encounter_compute_activation_cluster_bit_vector;
static void (*const b41e80_c64160)(void) = FUN_00064160;
static void (*const b41e80_c3aa90)(void) = actors_dispose_from_old_map;
static void (*const b41e80_c5dfb0)(void) = FUN_0005dfb0;
static void (*const b41e80_c53670)(void) = ai_debug_lineofsight_reset;
static void (*const b41e80_c48fa0)(void) = ai_debug_dispose_from_old_map;
static void (*const b41e80_c41090)(void) = ai_initialize_for_new_map;

__attribute__((naked, noinline))
void ai_handle_editing(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x38, %%esp\n\t"
      "movl 0x632574, %%eax\n\t"
      "movb 0x1(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "je .Lai_handle_editing_30\n\t"
      "pushl %%edi\n\t"
      "call *%[c18e380]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testw %%di, %%di\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jl .Lai_handle_editing_26\n\t"
      "movl 0x42c(%%eax), %%edx\n\t"
      "movswl %%di, %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jge .Lai_handle_editing_26\n\t"
      "movl 0x5ab270, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edi, %%eax\n\t"
      "andl $0xffff, %%eax\n\t"
      "pushl $0xb0\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movw 0x80(%%eax), %%bx\n\t"
      "subw 0x6(%%esi), %%bx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movswl 0x8c(%%eax), %%eax\n\t"
      "subw 0xa(%%esi), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%bx, %%bx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .Lai_handle_editing_3\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x42c(%%ecx), %%edx\n\t"
      "movl 0x5ab270, %%eax\n\t"
      "decl %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movw 0x6(%%eax), %%cx\n\t"
      "addw 0x4(%%eax), %%cx\n\t"
      "movswl %%bx, %%eax\n\t"
      "movswl %%cx, %%edi\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "addl %%edi, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $0x400, %%eax\n\t"
      "jle .Lai_handle_editing_1\n\t"
      "pushl $1\n\t"
      "pushl $0x6b0\n\t"
      "pushl $0x2575c0\n\t"
      "pushl $0x400\n\t"
      "pushl $0x257b8c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_handle_editing_1:\n\t"
      "movswl 0x4(%%esi), %%eax\n\t"
      "movswl 0x6(%%esi), %%ecx\n\t"
      "subl %%eax, %%edi\n\t"
      "leal (%%eax,%%ecx,1), %%edx\n\t"
      "shll $5, %%edx\n\t"
      "subl %%ecx, %%edi\n\t"
      "movl 0x5ab278, %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "addl $0x80, %%edx\n\t"
      "movl (%%edx), %%edx\n\t"
      "addl %%eax, %%edx\n\t"
      "shll $5, %%edx\n\t"
      "addl %%ecx, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8dae0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%bx, %%bx\n\t"
      "jle .Lai_handle_editing_2\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movswl 0x4(%%esi), %%ecx\n\t"
      "movl 0x5ab278, %%edx\n\t"
      "shll $5, %%eax\n\t"
      "pushl %%eax\n\t"
      "movswl 0x6(%%esi), %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "shll $5, %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lai_handle_editing_2:\n\t"
      "addw %%bx, 0x6(%%esi)\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      ".Lai_handle_editing_3:\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Lai_handle_editing_6\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0x42c(%%edx), %%eax\n\t"
      "movl 0x5ab270, %%ecx\n\t"
      "decl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movw 0xa(%%eax), %%cx\n\t"
      "addw 0x8(%%eax), %%cx\n\t"
      "movswl -0x4(%%ebp), %%eax\n\t"
      "movswl %%cx, %%edi\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "addl %%edi, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $0x100, %%eax\n\t"
      "jle .Lai_handle_editing_4\n\t"
      "pushl $1\n\t"
      "pushl $0x6c4\n\t"
      "pushl $0x2575c0\n\t"
      "pushl $0x100\n\t"
      "pushl $0x257b50\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_handle_editing_4:\n\t"
      "movswl 0x8(%%esi), %%eax\n\t"
      "movswl 0xa(%%esi), %%ecx\n\t"
      "subl %%eax, %%edi\n\t"
      "leal (%%eax,%%ecx,1), %%edx\n\t"
      "shll $4, %%edx\n\t"
      "subl %%ecx, %%edi\n\t"
      "movl 0x5ab274, %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl 0x8c(%%edx), %%edx\n\t"
      "addl %%eax, %%edx\n\t"
      "shll $4, %%edx\n\t"
      "addl %%ecx, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8dae0]\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%di, %%di\n\t"
      "jle .Lai_handle_editing_5\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movswl 0xa(%%esi), %%ecx\n\t"
      "movl 0x5ab274, %%edx\n\t"
      "shll $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "movswl 0x8(%%esi), %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lai_handle_editing_5:\n\t"
      "addw %%di, 0xa(%%esi)\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      ".Lai_handle_editing_6:\n\t"
      "testw %%bx, %%bx\n\t"
      "jne .Lai_handle_editing_7\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Lai_handle_editing_13\n\t"
      ".Lai_handle_editing_7:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0x42c(%%edx), %%ecx\n\t"
      "leal 0x1(%%edi), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .Lai_handle_editing_13\n\t"
      "nop\n\t"
      ".Lai_handle_editing_8:\n\t"
      "pushl %%eax\n\t"
      "movl 0x5ab270, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "addw %%bx, 0x4(%%edi)\n\t"
      "movw 0x4(%%edi), %%ax\n\t"
      "movswl 0x6(%%esi), %%ecx\n\t"
      "movswl 0x4(%%esi), %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "addl %%edx, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .Lai_handle_editing_9\n\t"
      "pushl $1\n\t"
      "pushl $0x6dc\n\t"
      "pushl $0x2575c0\n\t"
      "pushl $0x257b00\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_handle_editing_9:\n\t"
      "movswl 0x6(%%edi), %%ecx\n\t"
      "movswl 0x4(%%edi), %%edx\n\t"
      "addl %%edx, %%ecx\n\t"
      "cmpl $0x400, %%ecx\n\t"
      "jle .Lai_handle_editing_10\n\t"
      "pushl $1\n\t"
      "pushl $0x6dd\n\t"
      "pushl $0x2575c0\n\t"
      "pushl $0x257aa8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_handle_editing_10:\n\t"
      "movw -0x4(%%ebp), %%ax\n\t"
      "addw %%ax, 0x8(%%edi)\n\t"
      "movw 0x8(%%edi), %%ax\n\t"
      "movswl 0x8(%%esi), %%ecx\n\t"
      "movswl 0xa(%%esi), %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "addl %%edx, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .Lai_handle_editing_11\n\t"
      "pushl $1\n\t"
      "pushl $0x6e0\n\t"
      "pushl $0x2575c0\n\t"
      "pushl $0x257a50\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_handle_editing_11:\n\t"
      "movswl 0xa(%%edi), %%ecx\n\t"
      "movswl 0x8(%%edi), %%edx\n\t"
      "addl %%edx, %%ecx\n\t"
      "cmpl $0x100, %%ecx\n\t"
      "jle .Lai_handle_editing_12\n\t"
      "pushl $1\n\t"
      "pushl $0x6e1\n\t"
      "pushl $0x2575c0\n\t"
      "pushl $0x2579f0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lai_handle_editing_12:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x42c(%%ecx), %%edx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .Lai_handle_editing_8\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      ".Lai_handle_editing_13:\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c59a00]\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c59a50]\n\t"
      "movl %%eax, %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .Lai_handle_editing_29\n\t"
      "jmp .Lai_handle_editing_14\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lai_handle_editing_14:\n\t"
      "movw 0x3a(%%esi), %%ax\n\t"
      "cmpw %%bx, %%ax\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      "jl .Lai_handle_editing_15\n\t"
      "movswl %%ax, %%ecx\n\t"
      "cmpl 0x80(%%edi), %%ecx\n\t"
      "jl .Lai_handle_editing_18\n\t"
      ".Lai_handle_editing_15:\n\t"
      "movl 0x80(%%edi), %%ecx\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "leal 0x80(%%edi), %%eax\n\t"
      "je .Lai_handle_editing_17\n\t"
      "pushl $0xe8\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movw %%bx, 0x3a(%%esi)\n\t"
      "movw 0x22(%%eax), %%dx\n\t"
      "movw %%dx, 0x3c(%%esi)\n\t"
      "movw 0x22(%%eax), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw %%bx, %%ax\n\t"
      "jl .Lai_handle_editing_16\n\t"
      "movl 0x8c(%%edi), %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lai_handle_editing_18\n\t"
      ".Lai_handle_editing_16:\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      "jmp .Lai_handle_editing_19\n\t"
      ".Lai_handle_editing_17:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c3cf10]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Lai_handle_editing_25\n\t"
      ".Lai_handle_editing_18:\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      ".Lai_handle_editing_19:\n\t"
      "movw 0x3c(%%esi), %%ax\n\t"
      "cmpw %%bx, %%ax\n\t"
      "jl .Lai_handle_editing_20\n\t"
      "movswl %%ax, %%edx\n\t"
      "cmpl 0x8c(%%edi), %%edx\n\t"
      "jl .Lai_handle_editing_21\n\t"
      ".Lai_handle_editing_20:\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      ".Lai_handle_editing_21:\n\t"
      "movw 0x90(%%esi), %%ax\n\t"
      "cmpw %%bx, %%ax\n\t"
      "jl .Lai_handle_editing_22\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0x438(%%edx), %%edi\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jl .Lai_handle_editing_23\n\t"
      ".Lai_handle_editing_22:\n\t"
      "movw %%cx, 0x90(%%esi)\n\t"
      ".Lai_handle_editing_23:\n\t"
      "cmpw $0xb, 0x6c(%%esi)\n\t"
      "jne .Lai_handle_editing_24\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c16ff0]\n\t"
      "addl $4, %%esp\n\t"
      ".Lai_handle_editing_24:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c3b5e0]\n\t"
      "addl $4, %%esp\n\t"
      ".Lai_handle_editing_25:\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c59a50]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .Lai_handle_editing_14\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lai_handle_editing_26:\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl $0xffffffff, 0x5ac9f4\n\t"
      "call *%[c59b10]\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59b50]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lai_handle_editing_28\n\t"
      ".Lai_handle_editing_27:\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c3cf10]\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c59b50]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lai_handle_editing_27\n\t"
      ".Lai_handle_editing_28:\n\t"
      "call *%[c42ca0]\n\t"
      "call *%[c540e0]\n\t"
      "call *%[c58fb0]\n\t"
      "call *%[c64160]\n\t"
      "call *%[c3aa90]\n\t"
      "call *%[c5dfb0]\n\t"
      "call *%[c53670]\n\t"
      "call *%[c48fa0]\n\t"
      "movl 0x632574, %%ecx\n\t"
      "movb $0, 0x1(%%ecx)\n\t"
      "call *%[c41090]\n\t"
      ".Lai_handle_editing_29:\n\t"
      "popl %%edi\n\t"
      ".Lai_handle_editing_30:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(b41e80_c18e380), [dget] "m"(b41e80_dget), [elem] "m"(b41e80_elem), [c8d9d0] "m"(b41e80_c8d9d0), [assert] "m"(b41e80_assert), [exitfn] "m"(b41e80_exitfn), [c8dae0] "m"(b41e80_c8dae0), [memset] "m"(b41e80_memset), [c59a00] "m"(b41e80_c59a00), [c59a50] "m"(b41e80_c59a50), [c3cf10] "m"(b41e80_c3cf10), [c16ff0] "m"(b41e80_c16ff0), [c3b5e0] "m"(b41e80_c3b5e0), [c59b10] "m"(b41e80_c59b10), [c59b50] "m"(b41e80_c59b50), [c42ca0] "m"(b41e80_c42ca0), [c540e0] "m"(b41e80_c540e0), [c58fb0] "m"(b41e80_c58fb0), [c64160] "m"(b41e80_c64160), [c3aa90] "m"(b41e80_c3aa90), [c5dfb0] "m"(b41e80_c5dfb0), [c53670] "m"(b41e80_c53670), [c48fa0] "m"(b41e80_c48fa0), [c41090] "m"(b41e80_c41090)
      : "memory");
}
#else
#error "ai_handle_editing: clang naked draft required"
#endif

