void players_initialize(void)
{
  player_data = game_state_data_new("players", 16, sizeof(player_data_t));
  team_data = game_state_data_new("teams", 16, sizeof(team_data_t));
  players_globals = (players_globals_t *)game_state_malloc(
    "players globals", NULL, sizeof(players_globals_t));
  csmemset(&players_globals->unk_0[4], -1, 0x10u);
  *(_DWORD *)players_globals->unk_0 = -1;
  *(_WORD *)&players_globals->unk_0[36] = 0;
  player_control_initialize();
}

void players_initialize_for_new_map(void)
{
  player_control_initialize_for_new_map();
  csmemset(players_globals, 0, sizeof(players_globals_t));
  csmemset(&players_globals->unk_0[4], 0xFF, 0x10);
  csmemset(&players_globals->unk_0[0x14], 0xFF, 0x10);
  *(_DWORD *)players_globals->unk_0 = -1;
  players_globals->unk_0[0x29] = 0;
  *(_WORD *)&players_globals->unk_0[0x26] = 0;
  players_globals->unk_0[0x28] = 0;
  *(_WORD *)&players_globals->unk_0[0x2A] = 0xFFFF;
  *(_WORD *)&players_globals->unk_0[0x2C] = 0;
  data_delete_all(player_data);
  data_delete_all(team_data);
  csmemset(&local_player_network_indices, 0xFF, 0x40);
}

void players_dispose_from_old_map(void)
{
  data_make_invalid(player_data);
  data_make_invalid(team_data);
}

void players_dispose(void)
{
  if (player_data)
    player_data = 0;
  if (team_data)
    team_data = 0;
  if (players_globals)
    players_globals = 0;
}

void *machine_get_player_list(int16_t machine_index)
{
  return (char *)&local_player_network_indices +
         (unsigned short)machine_index * 0x10;
}

/* Register a player handle into the machine-local slot table
 * (local_player_network_indices) for a given local_player_index.
 *
 * local_player_index is passed in EAX (register argument).
 * Scans the 4 int-sized slots at
 *   local_player_network_indices[local_player_index & 0xffff][0..3]
 * and writes player_handle into the first slot that is -1 (unused).
 * Asserts if no free slot is found ("failed to create a player"). */
void player_register_machine(unsigned __int16 local_player_index,
                             int player_handle)
{
  int i;
  int *slots;

  slots = (int *)((char *)&local_player_network_indices +
                  (unsigned int)local_player_index * 0x10);
  for (i = 0; i < 4; i++) {
    if (slots[i] == -1) {
      slots[i] = player_handle;
      return;
    }
  }
  display_assert("failed to create a player",
                 "c:\\halo\\SOURCE\\game\\players.c", 0xef, 1);
  system_exit(-1);
}

bool local_player_exists(int16_t local_player_index)
{
  data_iter_t iter;
  char *player;

  data_iterator_new(&iter, player_data);
  while ((player = (char *)data_iterator_next(&iter)) != NULL) {
    if (*(int16_t *)(player + 2) == local_player_index)
      return true;
  }
  return false;
}

/* Find the first unused local player index (0..3).
 *
 * First pass: prefer a slot whose gamepad is plugged in (input_has_gamepad)
 * AND which has no existing player (local_player_exists returns false).
 * Second pass (fallback): just find any slot with no existing player.
 * Returns NONE (-1) if all 4 slots are occupied. */
int find_unused_local_player_index(void)
{
  int result;
  int i;

  result = -1;
  for (i = 0; i < 4; i++) {
    if (!input_has_gamepad(i) || local_player_exists(i))
      continue;
    result = i;
    if (i != -1)
      return i;
  }
  /* fallback: any slot without a player */
  for (i = 0; i < 4; i++) {
    if (!local_player_exists(i))
      return i;
  }
  return result;
}

void player_delete(int player_index)
{
  datum_delete(player_data, player_index);
}

int16_t players_get_respawn_failure(void)
{
  return *(int16_t *)((char *)players_globals + 0x2c);
}

int local_player_get_player_index(int16_t local_player_index)
{
  assert_halt(local_player_index >= NONE &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
  if (local_player_index == NONE)
    return NONE;
  return *(int *)&players_globals->unk_0[4 + local_player_index * 4];
}

int local_player_set_player_index(unsigned __int16 local_player_index,
                                  int player_index)
{
  int old_player;
  char *player;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  old_player = *(int *)&players_globals->unk_0[4 + local_player_index * 4];
  if (old_player != -1) {
    player = (char *)datum_get(player_data, old_player);
    *(int16_t *)(player + 2) = -1;
  }
  *(int *)&players_globals->unk_0[4 + local_player_index * 4] = player_index;
  if (player_index != -1) {
    player = (char *)datum_get(player_data, player_index);
    *(int16_t *)(player + 2) = local_player_index;
  }
  return old_player;
}

__int16 local_player_count(void)
{
  return *(__int16 *)&players_globals->unk_0[0x24];
}

__int16 local_player_get_next(__int16 local_player_index)
{
  __int16 result;
  __int16 i;

  result = -1;
  for (i = 0; i < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS; i++) {
    if (*(int *)&players_globals->unk_0[4 + i * 4] != -1 &&
        local_player_index < i) {
      if (i < result || result == -1)
        result = i;
    }
  }
  return result;
}

int player_index_from_unit_index(int unit_index)
{
  data_iter_t iter;
  char *player;
  int result;

  result = NONE;
  data_iterator_new(&iter, player_data);
  while ((player = (char *)data_iterator_next(&iter)) != NULL) {
    if (*(int *)(player + 0x34) == unit_index)
      result = iter.datum_handle;
  }
  return result;
}

void player_died(int player_handle)
{
  char *player;
  data_iter_t iter;

  player = (char *)datum_get(player_data, player_handle);
  *(int *)(player + 0x38) = *(int *)(player + 0x34);
  *(int *)(player + 0x34) = NONE;
  if (*(int16_t *)(player + 2) != -1)
    player_control_new_unit(*(int16_t *)(player + 2), NONE);

  *((char *)players_globals + 0x28) = 1;
  data_iterator_new(&iter, player_data);
  while ((player = (char *)data_iterator_next(&iter)) != NULL) {
    if (*(int *)(player + 0x34) != NONE)
      *((char *)players_globals + 0x28) = 0;
  }
}

bool players_are_all_dead(void)
{
  return *((char *)players_globals + 0x28);
}

void *players_get_combined_pvs_local(void)
{
  return (char *)players_globals + 0x70;
}

void *players_get_combined_pvs(void)
{
  return (char *)players_globals + 0x30;
}

void player_input_enable(bool enable)
{
  *((char *)players_globals + 0x29) = !enable;
}

bool player_input_enabled(void)
{
  return *((char *)players_globals + 0x29) == 0;
}

/* Check whether any active player's unit is currently airborne.
 *
 * Iterates every player datum. For each player with a valid unit handle:
 *   1. If the root object has flag 0x200000 set (+0x4), return true
 * immediately.
 *   2. If the unit is NOT in a vehicle (unit+0xCC == NONE):
 *      - If unit+0x64 (animation state) == 0: call the biped airborne check
 *        (0x1a0db0); return true if it reports airborne.
 *      - If unit+0x64 == 1: fall through to the altitude check.
 *   3. If the unit IS in a vehicle (unit+0xCC != NONE):
 *      - Look up the vehicle object via object_try_and_get_type (type 2).
 *      - Look up the vehicle tag ('vehi') and check if bit 0x40 is set at
 *        tag+0x17C. If so, fall through to the altitude check.
 *   4. Altitude check: if byte at object+0x428 > 2, return true.
 *
 * Returns false if no player meets any airborne criterion. */
bool any_player_is_in_the_air(void)
{
  data_iter_t iter;
  char *player;
  char *unit_obj;
  int unit_handle;
  char *root_obj;
  int root_handle;
  char *vehicle_obj;
  char *vehi_tag;

  data_iterator_new(&iter, player_data);
  while ((player = (char *)data_iterator_next(&iter)) != NULL) {
    unit_handle = *(int *)(player + 0x34);
    if (unit_handle == NONE)
      continue;

    unit_obj = (char *)object_get_and_verify_type(unit_handle, 3);
    root_handle = ((int (*)(int))0x13d7f0)(unit_handle);
    root_obj = (char *)object_get_and_verify_type(root_handle, NONE);

    if ((*(unsigned int *)(root_obj + 0x4) & 0x200000) != 0)
      return true;

    if (*(int *)(unit_obj + 0xCC) != NONE) {
      /* Unit is in a vehicle -- ESI becomes the vehicle object */
      vehicle_obj = (char *)object_try_and_get_and_verify_type(
        *(int *)(unit_obj + 0xCC), 2);
      if (vehicle_obj == NULL)
        continue;
      vehi_tag = (char *)tag_get(0x76656869, *(int *)vehicle_obj);
      if ((*(unsigned char *)(vehi_tag + 0x17C) & 0x40) == 0)
        continue;
      /* altitude check uses vehicle object (ESI was reassigned) */
      if (*(unsigned char *)(vehicle_obj + 0x428) > 2)
        return true;
    } else {
      /* Unit is on foot */
      if (*(short *)(unit_obj + 0x64) == 0) {
        if (((bool (*)(int))0x1a0db0)(unit_handle))
          return true;
        continue;
      } else if (*(short *)(unit_obj + 0x64) != 1) {
        continue;
      }
      /* animation state 1: altitude check uses unit object */
      if (*(unsigned char *)(unit_obj + 0x428) > 2)
        return true;
    }
  }
  return false;
}

bool any_player_is_dead(void)
{
  data_iter_t iter;
  char *player;

  data_iterator_new(&iter, player_data);
  while ((player = (char *)data_iterator_next(&iter)) != NULL) {
    if (*(int *)(player + 0x34) == -1)
      return true;
  }
  return false;
}

/* Update a combined PVS (potentially-visible-set) bit vector from the current
 * player set (or, in editor mode, from the debug observer camera).
 *
 * combined_pvs       (EDI) -- 0x40-byte bit vector buffer, one bit per cluster
 *                             in the current structure_bsp. Zeroed at entry
 *                             then OR-combined with each contributor's PVS.
 * local_player_only        -- if true, only players with a valid
 *                             local_player_index (player+0x2 != -1) contribute.
 *
 * Caller passes combined_pvs in EDI; see callers at 0xbbacc (player_teleport)
 * and 0xbd753/0xbd763 (players_update_before_game) which take addresses inside
 * players_globals (offsets 0x30 and 0x70 -- combined_pvs and
 * combined_pvs_local respectively).
 *
 * Editor branch (game_in_editor() true):
 *   - Look up the leaf index under the debug camera via the bsp3d, mask off
 *     the sign bit, fetch the leaf record from scenario+0xE0 (size 0x10),
 *     read its cluster index at +0x8, and OR that single cluster's
 *     visibility row into combined_pvs.
 *
 * Game branch:
 *   - For each player datum:
 *       - if local_player_only and player has no local_player_index, skip
 *       - if player has a unit, walk to root object and copy its
 *         object.cluster_index (offset 0x4C) into player+0x3C
 *       - if player+0x3C is valid, OR that cluster's visibility row into
 *         combined_pvs.
 *   - Then OR in the cluster returned by 0x13DCC0 (the "currently focused
 *     parent object" cluster -- see objects.c FUN_0013dcc0) when valid. */
void players_update_pvs(void *combined_pvs /* @<edi> */, bool local_player_only)
{
  void *structure_bsp;
  data_iter_t iter;
  char *player;
  int16_t saved_cluster;
  int unit_handle;
  int root_handle;
  char *root_object;
  int16_t root_cluster;
  int16_t player_cluster;
  unsigned char *cluster_data;
  unsigned int cluster_count;

  structure_bsp = ((void *(*)(void))0x18e3c0)(); /* scenario_get */
  csmemset(combined_pvs, 0, 0x40);

  if (game_in_editor()) {
    /* Editor: use the leaf under the observer camera. */
    int leaf_handle;
    int leaf_index;
    void *scenario;
    void *block;
    char *leaf;
    int16_t leaf_cluster;

    leaf_handle =
      ((int (*)(void *))0x18e720)(observer_get_camera(0)); /* bsp3d query */
    if (leaf_handle == -1)
      return;

    leaf_index =
      ((int (*)(void *))0x18e720)(observer_get_camera(0)) & 0x7fffffff;
    scenario = ((void *(*)(void))0x18e3c0)();
    block = (char *)scenario + 0xe0;
    leaf = (char *)tag_block_get_element(block, leaf_index, 0x10);
    leaf_cluster = *(int16_t *)(leaf + 8);
    if (leaf_cluster == -1)
      return;

    cluster_data = (unsigned char *)((void *(*)(void *, int16_t))0x193550)(
      structure_bsp, leaf_cluster);
    cluster_count = (unsigned int)*(int *)((char *)structure_bsp + 0x134);
    ((void (*)(int16_t, void *, void *, void *))0x108f00)(
      (int16_t)cluster_count, combined_pvs, cluster_data, combined_pvs);
    return;
  }

  /* Game: combine PVS from each player + the parent-object cluster. */
  saved_cluster =
    (int16_t)((unsigned short (*)(void))0x13dcc0)(); /* parent obj cluster */

  data_iterator_new(&iter, player_data);
  while ((player = (char *)data_iterator_next(&iter)) != NULL) {
    if (local_player_only && *(int16_t *)(player + 2) == -1)
      continue;

    unit_handle = *(int *)(player + 0x34);
    if (unit_handle != -1) {
      root_handle = ((int (*)(int))0x13d7f0)(unit_handle); /* object root */
      root_object = (char *)object_get_and_verify_type(root_handle, -1);
      root_cluster = *(int16_t *)(root_object + 0x4c);
      if (root_cluster != -1)
        *(int16_t *)(player + 0x3c) = root_cluster;
    }

    player_cluster = *(int16_t *)(player + 0x3c);
    if (player_cluster != -1) {
      cluster_data = (unsigned char *)((void *(*)(void *, int16_t))0x193550)(
        structure_bsp, player_cluster);
      cluster_count = (unsigned int)*(int *)((char *)structure_bsp + 0x134);
      ((void (*)(int16_t, void *, void *, void *))0x108f00)(
        (int16_t)cluster_count, combined_pvs, cluster_data, combined_pvs);
    }
  }

  if (saved_cluster != -1) {
    cluster_data = (unsigned char *)((void *(*)(void *, int16_t))0x193550)(
      structure_bsp, saved_cluster);
    cluster_count = (unsigned int)*(int *)((char *)structure_bsp + 0x134);
    ((void (*)(int16_t, void *, void *, void *))0x108f00)(
      (int16_t)cluster_count, combined_pvs, cluster_data, combined_pvs);
  }
}

/* Count how many of the 4 local player slots have a valid (non-NONE) player
 * index assigned in players_globals.
 * Reads players_globals+0x4 through +0x10 (4 dwords). */
int players_compute_local_player_count(void)
{
  int count;
  int *slot;
  int i;

  count = 0;
  slot = (int *)((char *)players_globals + 0x4);
  for (i = 4; i != 0; i--) {
    if (*slot != -1)
      count++;
    slot++;
  }
  return count;
}

/* Check whether the player's unit should interact with a nearby unit
 * (e.g. swap weapons on approach).
 *
 * player_unit_handle  -- the player's unit datum handle
 * nearby_unit_handle  -- the unit near the player to examine
 *
 * Returns true if the player should pick up / interact with the nearby unit.
 * The decision involves:
 *   1. Looking up the nearby unit's weapon tag (weap at +0x308 flags)
 *   2. Checking unit weapon counts (0x1aad90, 0x1aae00)
 *   3. Checking game engine running state
 *   4. Checking unit_can_pick_up_weapon (0xaba00) as fallback */
bool player_examine_nearby_unit(int player_unit_handle, int nearby_unit_handle)
{
  int *nearby_obj;
  char *weap_tag;
  short weapon_count;
  bool can_swap;

  nearby_obj = (int *)object_try_and_get_and_verify_type(nearby_unit_handle, 4);
  weap_tag = (char *)tag_get(0x77656170, *nearby_obj);
  weapon_count = unit_count_weapons(player_unit_handle);
  can_swap = unit_weapon_is_new(player_unit_handle, nearby_unit_handle);
  if ((can_swap && (*(unsigned char *)(weap_tag + 0x308) & 0x10) != 0) ||
      weapon_count == 0) {
    return true;
  }
  if (!game_engine_running()) {
    if (unit_weapon_is_new(player_unit_handle, nearby_unit_handle) &&
        weapon_count < 2) {
      return true;
    }
  }
  if (game_engine_can_pick_up_weapon(player_unit_handle, nearby_unit_handle)) {
    return true;
  }
  return false;
}

/* Clear the action-result fields on a player datum.
 *
 * player_handle is passed in EAX (register argument).
 * Writes 0 to player+0x28 (action result type, word) and
 * NONE (-1) to player+0x24 (action result object, dword). */
void player_reset_action_result(int player_handle /* @<eax> */)
{
  char *player;

  player = (char *)datum_get(player_data, player_handle);
  *(unsigned short *)(player + 0x28) = 0;
  *(int *)(player + 0x24) = -1;
}

/* Attempt to enter a vehicle or interact with a seat object based on the
 * player's current action result.
 *
 * player_handle is passed in EAX (register argument).
 *
 * Action result type (player+0x28):
 *   6 = enter vehicle seat: call unit_set_in_vehicle, then unit_enter_seat.
 *       If both succeed, notify the HUD and clear aim assist. Returns true.
 *   7 = interact with seat object: call unit_enter_seat only.
 *       If it succeeds, notify the HUD. Returns false.
 *   other: returns false immediately.
 *
 * The action result object (player+0x24) is the vehicle or seat object
 * the player is interacting with. */
bool player_try_to_enter_vehicle(int player_handle /* @<eax> */)
{
  char *player;
  int *vehicle_obj;

  player = (char *)datum_get(player_data, player_handle);
  object_get_and_verify_type(*(int *)(player + 0x34), 3);

  if (*(short *)(player + 0x28) == 6) {
    /* Enter vehicle seat */
    if (!unit_set_in_vehicle(*(int *)(player + 0x34), 1))
      return true;
    if (unit_enter_seat(*(int *)(player + 0x34), *(int *)(player + 0x24), 1)) {
      vehicle_obj =
        (int *)object_get_and_verify_type(*(int *)(player + 0x24), 4);
      hud_player_set_vehicle(*(unsigned short *)(player + 0x2), *vehicle_obj);
      player_clear_aim_assist(*(int *)(player + 0x34));
    }
    return true;
  } else if (*(short *)(player + 0x28) == 7) {
    /* Interact with seat object */
    if (unit_enter_seat(*(int *)(player + 0x34), *(int *)(player + 0x24), 1)) {
      vehicle_obj =
        (int *)object_get_and_verify_type(*(int *)(player + 0x24), 4);
      hud_player_set_vehicle(*(unsigned short *)(player + 0x2), *vehicle_obj);
    }
  }
  return false;
}

/* Apply the overshield powerup effect to the player.
 * Builds a player-effect descriptor struct with the overshield parameters
 * and submits it via player_effect_apply. ESI = player_handle. */
void player_apply_overshield_effect(int player_handle)
{
  char *player;
  struct {
    int16_t type;
    int16_t unk_02;
    int32_t pad[3];
    float field_10;
    int16_t field_14;
    int16_t pad_16;
    int32_t pad_18[2];
    float field_20;
    int32_t field_24;
    float field_28;
    float field_2c;
    float field_30;
    float field_34;
  } effect;

  if (player_handle == -1)
    return;
  player = (char *)datum_get(player_data, player_handle);
  if (*(int16_t *)(player + 2) == -1)
    return;

  csmemset(&effect, 0, sizeof(effect));
  effect.type = *(int16_t *)0x2f1480;
  effect.unk_02 = 2;
  effect.field_10 = *(float *)0x2f1490;
  effect.field_14 = *(int16_t *)0x46b6ac;
  effect.field_20 = *(float *)0x2f1484;
  effect.field_24 = 0;
  effect.field_28 = *(float *)0x46b6b0;
  effect.field_2c = *(float *)0x2f1488;
  effect.field_30 = *(float *)0x46b6b4;
  effect.field_34 = *(float *)0x2f148c;
  player_effect_apply(player_handle, &effect, 1.0f);
}

/* Notify the game that active camo was activated (triggers a location-based
 * player effect notification). ESI = player_handle. */
void player_apply_camo_notification(int player_handle)
{
  char *player;
  struct {
    int16_t type;
    int16_t unk_02;
    int32_t pad[3];
    float field_10;
    int16_t field_14;
    int16_t pad_16;
    int32_t pad_18[2];
    float field_20;
    int32_t field_24;
    float field_28;
    float field_2c;
    float field_30;
    float field_34;
  } effect;

  if (player_handle == -1)
    return;
  player = (char *)datum_get(player_data, player_handle);
  if (*(int16_t *)(player + 2) == -1)
    return;

  csmemset(&effect, 0, sizeof(effect));
  effect.type = *(int16_t *)0x2f1494;
  effect.unk_02 = 2;
  effect.field_10 = *(float *)0x2f14a4;
  effect.field_14 = *(int16_t *)0x46b6b8;
  effect.field_20 = *(float *)0x2f1498;
  effect.field_24 = 0;
  effect.field_28 = *(float *)0x46b6bc;
  effect.field_2c = *(float *)0x2f149c;
  effect.field_30 = *(float *)0x2f14a0;
  effect.field_34 = *(float *)0x46b6c0;
  player_effect_apply(player_handle, &effect, 1.0f);
}

/* Apply the health powerup effect to the player.
 * Unlike overshield/camo, this uses entirely inline constants
 * rather than loading from global addresses. ESI = player_handle. */
void player_apply_health_effect(int player_handle)
{
  char *player;
  struct {
    int16_t type;
    int16_t unk_02;
    int32_t pad[3];
    float field_10;
    int16_t field_14;
    int16_t pad_16;
    int32_t pad_18[2];
    float field_20;
    int32_t field_24;
    float field_28;
    float field_2c;
    float field_30;
    float field_34;
  } effect;

  if (player_handle == -1)
    return;
  player = (char *)datum_get(player_data, player_handle);
  if (*(int16_t *)(player + 2) == -1)
    return;

  csmemset(&effect, 0, sizeof(effect));
  effect.type = 6;
  effect.unk_02 = 2;
  effect.field_10 = 2.0f;
  effect.field_14 = 1;
  effect.field_20 = 0.5f;
  effect.field_24 = 0;
  effect.field_28 = 1.0f;
  effect.field_2c = 0.917647f;
  effect.field_30 = 0.917647f;
  effect.field_34 = 0.917647f;
  player_effect_apply(player_handle, &effect, 1.0f);
}

/* Allocate and initialise a new player datum.
 *
 * local_player_index  (a1) -- which local player slot to assign; NONE (-1) is
 *                             allowed (player is not locally controlled).
 * player_handle_hint  (a2) -- if -1, allocate the next free datum;
 *                             otherwise re-use this specific datum handle.
 * local_player_index2 (a3) -- same value as a1; written into the player
 *                             record at offset +0x2.
 * player_name         (a4) -- pointer to a wide-char name (max 0xb chars),
 *                             or NULL to use the empty default name.
 *
 * Returns the new player datum handle, or -1 on failure. */
int player_new(unsigned __int16 a1, int a2, unsigned __int16 a3, char *a4)
{
  int player_handle;
  char *player;
  char *player2;
  wchar_t *name_src;

  /* Allocate the player datum. */
  if (a2 == -1) {
    player_handle = data_new_at_index(player_data);
  } else {
    player_handle = data_new_datum(player_data, a2);
  }

  /* Validate the local_player_index argument. */
  if (((a3 < 0) || (3 < a3)) && (a3 != (unsigned __int16)-1)) {
    display_assert(
      "((local_player_index>=0) && (local_player_index<MAXIMUM_NUMBER_OF_"
      "LOCAL_PLAYERS)) || (local_player_index==NONE)",
      "c:\\halo\\SOURCE\\game\\players.c", 0x134, 1);
    system_exit(-1);
  }

  if (player_handle != -1) {
    /* Initialise the new player record. */
    player = (char *)datum_get(player_data, player_handle);

    /* Copy player name (up to 0xb wide chars); use empty default if no name
     * supplied. */
    name_src = (a4 != NULL) ? (wchar_t *)a4 : (wchar_t *)0x26cdf0;
    ustrncpy((wchar_t *)(player + 4), name_src, 0xb);

    *(unsigned __int16 *)(player + 0x1a) = 0;
    *(short *)(player + 0x2) = (short)a3;
    *(int *)(player + 0x34) = -1;
    *(int *)(player + 0x38) = -1;
    *(int *)(player + 0x1c) = -1;
    *(unsigned short *)(player + 0x3c) = 0xffff;
    *(int *)(player + 0x40) = -1;
    *(int *)(player + 0x6c) = 0x3f800000; /* 1.0f */
    *(int *)(player + 0x20) = 1;

    /* Second datum_get for the same handle (compiler re-fetched the
     * pointer after the intervening writes). */
    player2 = (char *)datum_get(player_data, player_handle);
    *(unsigned short *)(player2 + 0x28) = 0;
    *(int *)(player2 + 0x24) = -1;

    *(int *)(player + 0xcc) = -1;
    *(char *)(player + 0xd1) = 0;

    /* Copy full player name into the +0x48 slot if a name was given. */
    if (a4 != NULL) {
      csmemcpy(player + 0x48, a4, 0x20);
    }
  }

  /* Register the player handle in the machine-local slot table. */
  player_register_machine(a1, player_handle);
  return player_handle;
}

/* Build the aiming/facing update for a player's unit when riding in a
 * vehicle.
 *
 * If the player's unit is seated in a vehicle and the seat does NOT have
 * the 0x10 flag set (steering seat), transform the player's aiming
 * vector from world-space into the vehicle's local coordinate frame.
 *
 * The transformation uses the vehicle's forward vector (object+0x30)
 * to build a rotation matrix, then multiplies aiming_out by that matrix.
 *
 * datum_handle   -- player datum handle
 * aiming_out     -- [in/out] 3-float aiming direction (yaw/pitch converted)
 * desired_facing -- 2-float desired facing angles (yaw, pitch) */
void player_build_action_update(int datum_handle, float *aiming_out,
                                float *desired_facing)
{
  char *player;
  char *unit;
  char *vehicle;
  char *vehi_tag;
  unsigned char *seat_data;
  float forward[3];
  float matrix[13]; /* 3x3 matrix + scale, 52 bytes at [EBP-0x34] */

  player = (char *)datum_get(player_data, datum_handle);
  angles_to_vector(aiming_out, desired_facing);

  if (*(int *)(player + 0x34) == -1)
    return;

  unit = (char *)object_get_and_verify_type(*(int *)(player + 0x34), 3);
  if (*(int *)(unit + 0xCC) == -1)
    return;

  vehicle =
    (char *)object_try_and_get_and_verify_type(*(int *)(unit + 0xCC), 2);
  if (vehicle == NULL)
    return;

  vehi_tag = (char *)tag_get(0x76656869, *(int *)vehicle);
  seat_data = (unsigned char *)tag_block_get_element(
    vehi_tag + 0x2E4, (int)*(short *)(unit + 0x2A0), 0x11C);
  if ((*seat_data & 0x10) != 0)
    return;

  /* Build a rotation matrix from the vehicle's up vector (forward in
   * object space at +0x30). Cross product with global -Y to get the
   * right vector; if degenerate, fall back to -Z. */
  cross_product3d((float *)(vehicle + 0x30), *(float **)0x31fc4c, forward);
  if (normalize3d(forward) == 0.0f) {
    cross_product3d((float *)(vehicle + 0x30), *(float **)0x31fc50, forward);
    normalize3d(forward);
  }
  matrix_from_forward_and_up(matrix, forward, (float *)(vehicle + 0x30));
  matrix_transform_vector(matrix, aiming_out, aiming_out); /* dup-args-ok */
}

/* Spawn (or respawn) a player.
 *
 * Two paths:
 *   A. Campaign/singleplayer path (game engine NOT running): if the player
 *      already has a "saved unit" parked in players_globals+0x14+idx*4, try
 *      to reuse it.  Otherwise fabricate a new unit from the current spawn
 *      point.
 *   B. Multiplayer / game-engine path: always allocate a fresh unit via
 *      object_placement_data_new + object_new_from_placement_data.
 *
 * Structurally faithful lift of the original FUN_bbcb0.  Helper addresses
 * (0xbbbe0, 0xbaae0, 0xbaba0, 0xba5f0, 0x10cc70, 0x13fc20, 0x13fb30,
 * 0x13ffc0, 0x140cc0, 0x143c80, 0x1adeb0, 0x1adf10, 0xbb410, 0xa99a0,
 * 0x8aa30) are not yet in kb.json; invoked by address to keep the lift
 * narrowly scoped.
 *
 * Uncertain: exact semantics of players_globals+0x14 (cached-unit table
 * per local player), scenario+0x348 (starting-equipment count / flags),
 * globals+0x170 tag block (default unit biped tag), globals+0x164
 * (MP-specific unit tag), and DAT_5ac9f4 (campaign encounter selector).
 * Field names for these are deliberately kept as raw offsets. */
void player_spawn(int player_handle)
{
  char *player; /* [EBP-0x4] player datum ptr (EDI)          */
  int saved_unit; /* ESI: handle of a cached unit to reuse   */
  int16_t local_player_index;
  char *unit_data;
  int prev_weapon;
  int16_t spawn_slot;
  char *globals_ptr; /* [EBP-0x8] game_globals_get() result  */
  char *default_unit_block;
  void *position; /* vec3 from FUN_baae0                    */
  int tag_handle; /* biped tag handle fed to placement data */
  char placement[0x88]; /* [EBP-0xa8] object_placement_data  */
  float orient_tmp[3]; /* [EBP-0x20] local_24: out-param for FUN_a99a0 */
  float orient[3]; /* [EBP-0x14] local_18: copied, passed to FUN_baba0 */
  int new_unit;
  char *unit_obj;
  char *player2; /* re-fetched player ptr after object_new  */
  int scen_starting_count;
  void *mp_unit_block;

  player = (char *)datum_get(player_data, player_handle);
  saved_unit = NONE;
  /* Record the original player pointer for the common tail. */

  /* --- Path A/B selector: campaign code first tries to reuse a cached
   *     unit stored at players_globals+0x14+lpi*4. ---- */
  if (!game_engine_running()) {
    local_player_index = *(int16_t *)(player + 2);
    if (local_player_index != NONE) {
      saved_unit =
        *(int *)&players_globals->unk_0[0x14 + local_player_index * 4];
      *(int *)&players_globals->unk_0[0x14 + local_player_index * 4] = NONE;
      if (saved_unit != NONE) {
        unit_data = (char *)object_get_and_verify_type(saved_unit, 3);
        if ((unit_data[0xb6] & 4) != 0) {
          /* Cached unit was deleted/marked-deleted: drop it and fall
           * through to the fresh-spawn path. */
          object_delete(saved_unit);
          saved_unit = NONE;
        }
      }
    }
  }

  if (!game_engine_running() && saved_unit != NONE) {
    /* --- Reuse cached unit path. --- */
    unit_data = (char *)object_get_and_verify_type(saved_unit, 3);
    prev_weapon = unit_get_weapon(saved_unit, *(int16_t *)(unit_data + 0x2a2));
    if (*(int16_t *)(player + 2) == NONE) {
      display_assert("player->local_player_index!=NONE",
                     "c:\\halo\\SOURCE\\game\\players.c", 0x736, 1);
      system_exit(-1);
    }
    ((void (*)(int))0x13fb30)(saved_unit);
    object_set_garbage(saved_unit, 1);
    ((void (*)(uint16_t, int))0xba5f0)((uint16_t) * (int16_t *)(player + 2),
                                       saved_unit);
    if (prev_weapon != NONE) {
      object_set_garbage(prev_weapon, 1);
    }
  } else {
    /* --- Fresh-spawn path. --- */
    globals_ptr = (char *)global_scenario_get();
    if (*(int *)0x5ac9f4 != NONE) {
      /* Touch the campaign-encounter selector entry (side effect unused
       * here; the original preserves the call). */
      tag_block_get_element(globals_ptr + 0x42c, *(int *)0x5ac9f4 & 0xffff,
                            0xb0);
    }
    spawn_slot = (int16_t)((int (*)(int))0xbbbe0)(player_handle);
    if (spawn_slot == NONE) {
      goto common_tail;
    }
    globals_ptr = (char *)game_globals_get();
    default_unit_block = (char *)tag_block_get_element(
      (char *)game_globals_get() + 0x170, 0, 0xf4);
    if (*(int *)(default_unit_block + 0xc) == NONE) {
      goto common_tail;
    }
    position = ((void *(*)(int16_t))0xbaae0)(spawn_slot);
    if (game_engine_running()) {
      mp_unit_block = tag_block_get_element(globals_ptr + 0x164, 0, 0xa0);
      tag_handle = *(int *)((char *)mp_unit_block + 0x1c);
    } else {
      tag_handle = *(int *)(default_unit_block + 0xc);
    }
    ((void (*)(char *, int, int))0x13fc20)(placement, tag_handle, -1);
    /* Copy position vec3 from FUN_baae0 into placement+0x18..+0x20. */
    *(int *)(placement + 0x18) = *(int *)((char *)position + 0x00);
    *(int *)(placement + 0x1c) = *(int *)((char *)position + 0x04);
    *(int *)(placement + 0x20) = *(int *)((char *)position + 0x08);
    /* placement+0x34 = forward vec3 from yaw (position+0xc). */
    ((void (*)(float *, float))0x10cc70)((float *)(placement + 0x34),
                                         *(float *)((char *)position + 0xc));
    /* placement+0x40 = up vec3 copied from global at *(void**)0x31fc44. */
    *(int *)(placement + 0x40) = *(int *)(*(int *)0x31fc44 + 0);
    *(int *)(placement + 0x44) = *(int *)(*(int *)0x31fc44 + 4);
    *(int *)(placement + 0x48) = *(int *)(*(int *)0x31fc44 + 8);
    /* Compute starting team/color vec3.  The original fetches into
     * local_24, then copies the three dwords into local_18 before calling
     * FUN_baba0 — preserve both buffers. */
    {
      float *ret =
        ((float *(*)(float *, int))0xa99a0)(orient_tmp, player_handle);
      orient[0] = ret[0];
      orient[1] = ret[1];
      orient[2] = ret[2];
    }
    ((void (*)(char *, float *))0xbaba0)(placement, orient);
    new_unit = ((int (*)(char *))0x143c80)(placement);
    if (new_unit == NONE) {
      goto common_tail;
    }
    unit_obj = (char *)object_try_and_get_and_verify_type(new_unit, 3);
    if (unit_obj == NULL) {
      goto common_tail;
    }
    player2 = (char *)datum_get(player_data, player_handle);
    *(int *)(unit_obj + 0x70) = player_handle;
    *(int16_t *)(unit_obj + 0x68) = *(int16_t *)(player2 + 0x20);
    *(int *)(unit_obj + 0x1c8) = player_handle;
    *(int *)(player2 + 0x34) = new_unit;
    ((void (*)(int, char))0x1adf10)(new_unit, 1);
    if (*(int16_t *)(player2 + 2) != NONE) {
      player_control_new_unit((uint16_t) * (int16_t *)(player2 + 2), new_unit);
    }
    if (!game_engine_running()) {
      scen_starting_count = *(int *)((char *)global_scenario_get() + 0x348);
      if (scen_starting_count > 1 && *(int16_t *)(player2 + 0xaa) > 0) {
        player_add_equipment(*(int *)(player2 + 0x34), 1, 1);
      } else if (scen_starting_count != 0) {
        player_add_equipment(*(int *)(player2 + 0x34), 0, 1);
      }
    }
    /* Restore EDI (original player ptr) for the common tail. */
  }

common_tail:
  csmemset(player + 0x68, 0, 4);
  player2 = (char *)datum_get(player_data, player_handle);
  *(int16_t *)(player2 + 0x28) = 0;
  *(int *)(player2 + 0x24) = NONE;
  if (*(int16_t *)(player + 2) != NONE) {
    ((void (*)(int16_t))0x8aa30)(*(int16_t *)(player + 2));
  }
}

/* Attempt to spawn the player into a vehicle or interact with a world
 * object, based on the player's action result type (player+0x28).
 *
 * player_handle is passed in EAX (register argument).
 *
 * Action result types handled:
 *   5  = pickup equipment: clear seat equipment, then try unit_pickup_equipment
 *   8,9 = find nearby seat: try unit_find_nearby_seat + unit_board_vehicle
 *   10 = device group interaction: set device group position
 *   11 = vehicle approach: store approach info on unit, compute approach
 *        direction (front/behind/above/below)
 *   6,7 = default: return false
 *
 * Returns true on success, false otherwise. */
bool player_try_to_spawn_in_vehicle(int player_handle /* @<eax> */)
{
  char *player;
  char *unit;
  char *item_obj;
  int *vehicle_obj;
  int nearby_unit;
  char *nearby_unit_data;
  char *world_matrix_a;
  char *world_matrix_b;
  float delta[3];
  float dot;
  char action_type;
  char out_a[52];
  char out_b[52];

  player = (char *)datum_get(player_data, player_handle);
  object_get_and_verify_type(*(int *)(player + 0x34), 3);

  switch (*(short *)(player + 0x28)) {
  case 5:
    /* Equipment pickup */
    unit_clear_seat_equipment(*(int *)(player + 0x34));
    if (unit_pickup_equipment(*(int *)(player + 0x34), *(int *)(player + 0x24),
                              0)) {
      vehicle_obj =
        (int *)object_get_and_verify_type(*(int *)(player + 0x24), 8);
      hud_player_set_vehicle_seat(*(unsigned short *)(player + 0x2),
                                  *vehicle_obj);
      return true;
    }
    break;

  case 8:
  case 9: {
    /* Find nearby seat and board vehicle */
    nearby_unit = -1;
    if (unit_find_nearby_seat(*(int *)(player + 0x34), *(int *)(player + 0x24),
                              *(short *)(player + 0x2a), &nearby_unit)) {
      unit_board_vehicle(*(int *)(player + 0x34), *(int *)(player + 0x24),
                         *(short *)(player + 0x2a));
      return false;
    }
    if (nearby_unit == -1)
      return false;
    nearby_unit_data = (char *)object_get_and_verify_type(nearby_unit, 3);
    if (*(int *)(nearby_unit_data + 0x1a4) == -1)
      return false;
    ai_handle_unit_approach(*(int *)(nearby_unit_data + 0x1a4),
                            *(int *)(player + 0x34), 1);
    return false;
  }

  case 10:
    /* Device group interaction */
    device_group_set_real(*(int *)(player + 0x24), *(int *)(player + 0x34));
    return true;

  case 11: {
    /* Vehicle approach: compute approach direction */
    unit = (char *)object_get_and_verify_type(*(int *)(player + 0x34), 3);
    item_obj = (char *)object_get_and_verify_type(*(int *)(player + 0x24), 2);
    *(int *)(unit + 0x2dc) = *(int *)(player + 0x24);
    *(int *)(unit + 0x2e0) = game_time_get();

    {
      float fwd_z = *(float *)(item_obj + 0x2c);
      float abs_fwd_z = fwd_z < 0.0f ? -fwd_z : fwd_z;

      if (abs_fwd_z <= *(double *)0x26ee88) {
        /* Nearly horizontal: compute direction from dot product */
        world_matrix_a =
          (char *)object_get_world_matrix(*(int *)(player + 0x24), out_b);
        world_matrix_b =
          (char *)object_get_world_matrix(*(int *)(player + 0x34), out_a);
        delta[0] =
          *(float *)(world_matrix_a + 0x28) - *(float *)(world_matrix_b + 0x28);
        delta[1] =
          *(float *)(world_matrix_a + 0x2c) - *(float *)(world_matrix_b + 0x2c);
        delta[2] =
          *(float *)(world_matrix_a + 0x30) - *(float *)(world_matrix_b + 0x30);
        cross_product3d(*(float **)0x31fc44, delta, delta); /* dup-args-ok */
        dot = delta[2] * *(float *)(item_obj + 0x2c) +
              delta[1] * *(float *)(item_obj + 0x28) +
              delta[0] * *(float *)(item_obj + 0x24);
        action_type = (dot > 0.0f ? 1 : 0) + 1;
      } else if (*(float *)(item_obj + 0x2c) >= *(float *)0x2533c0) {
        action_type = 4;
      } else {
        action_type = 3;
      }
    }

    *(unsigned char *)(item_obj + 0x424) |= 0x10;
    *(char *)(item_obj + 0x429) = action_type;
    *(char *)(item_obj + 0x42a) = 0;
    break;
  }

  default:
    return false;
  }
  return true;
}

/* unit_control_t layout as used by unit_set_control (from units.c strings):
 *   +0x00  animation_state (byte)
 *   +0x01  aiming_speed (byte)
 *   +0x02  control_flags (uint16)  — flags field
 *   +0x04  weapon_index (int16)
 *   +0x06  grenade_index (int16)
 *   +0x08  zoom_level (int16)
 *   +0x0a  pad
 *   +0x0c  throttle (vec3)
 *   +0x18  primary_trigger (float)
 *   +0x1c  facing_vector (vec3)
 *   +0x28  aiming_vector (vec3)
 *   +0x34  looking_vector (vec3)
 * Total: at least 0x40 bytes. */
typedef struct {
  char animation_state; /* +0x00 */
  char aiming_speed; /* +0x01 */
  int16_t control_flags; /* +0x02 */
  int16_t weapon_index; /* +0x04 */
  int16_t grenade_index; /* +0x06 */
  int16_t zoom_level; /* +0x08 */
  char pad_a[2]; /* +0x0a */
  float throttle_x; /* +0x0c */
  float throttle_y; /* +0x10 */
  float throttle_z; /* +0x14 */
  float primary_trigger; /* +0x18 */
  float facing_x; /* +0x1c */
  float facing_y; /* +0x20 */
  float facing_z; /* +0x24 */
  float aiming_x; /* +0x28 */
  float aiming_y; /* +0x2c */
  float aiming_z; /* +0x30 */
  float looking_x; /* +0x34 */
  float looking_y; /* +0x38 */
  float looking_z; /* +0x3c */
} unit_control_t;

/* player_action_t layout as filled by player_control_get_current_actions:
 *   +0x00  buttons (uint32 flags, bit 6 = binoculars, bit 14 = zoom, bit 7 =
 * alt_attack) +0x04  desired_facing_yaw (float) +0x08  desired_facing_pitch
 * (float) +0x0c  throttle_x (float) +0x10  throttle_y (float) +0x14
 * primary_trigger (float) +0x18  desired_weapon_index (int16) +0x1a
 * desired_grenade_index (int16) +0x1c  desired_zoom_level (int16) +0x1e  pad
 * Total: 0x20 bytes per action entry. */
typedef struct {
  uint32_t buttons;
  float desired_facing_yaw;
  float desired_facing_pitch;
  float throttle_x;
  float throttle_y;
  float primary_trigger;
  int16_t desired_weapon_index;
  int16_t desired_grenade_index;
  int16_t desired_zoom_level;
  char pad[2];
} player_action_t;

/* Apply a powerup timer to a player. Despite the kb.json name "respawn_timer",
 * the binary assert and source path show this sets the powerup countdown at
 * player+0x68 (indexed by powerup_type: 0=active_camo, 1=full_spectrum).
 *
 * If the slot is currently empty (timer == 0) and powerup_type == 0 (active
 * camo), also marks the unit at player+0x34 with flag 0x10 in field+0x1b4 and
 * records the type in field+0x3d2.
 *
 * The timer is only ever raised, never lowered: stored = max(current, ticks).
 */
void player_set_respawn_timer(int player_handle, int16_t respawn_type,
                              int16_t respawn_ticks)
{
  char *player;
  char *unit_obj;
  int powerup_idx;

  player = (char *)datum_get(player_data, player_handle);

  /* powerup_type (respawn_type in kb.json) must be 0 or 1 */
  assert_halt(respawn_type >= 0 && respawn_type < 2);

  powerup_idx = (int)respawn_type;

  if (*(int16_t *)(player + 0x68 + powerup_idx * 2) == 0) {
    /* Slot was empty — fetch the unit and mark it. */
    char *player2 = (char *)datum_get(player_data, player_handle);
    unit_obj = (char *)object_get_and_verify_type(*(int *)(player2 + 0x34), 3);
    if (powerup_idx == 0) {
      /* Active camo: set camo-active flag on the unit object. */
      *(unsigned int *)(unit_obj + 0x1b4) |= 0x10;
      *(int16_t *)(unit_obj + 0x3d2) = respawn_type;
    }
  }

  /* Raise the timer: store max(current, ticks). */
  {
    int16_t cur = *(int16_t *)(player + 0x68 + powerup_idx * 2);
    if (cur < respawn_ticks)
      cur = respawn_ticks;
    *(int16_t *)(player + 0x68 + powerup_idx * 2) = cur;
  }
}

/* Decrement the player's short weapon/vehicle timers (at player+0x68,
 * 2 x int16_t).  When a timer reaches zero the corresponding flag bit
 * is cleared on the unit object (bit 0x10 at unit+0x1b4).
 * EBX = datum_handle (register arg). */
void player_update_weapon_timers(int datum_handle)
{
  char *player;
  char *unit;
  int16_t *timer;
  int i;
  int16_t val;

  player = (char *)datum_get(player_data, datum_handle);
  timer = (int16_t *)(player + 0x68);
  for (i = 0; i < 2; i++) {
    val = timer[i];
    if (val > 0) {
      val--;
      timer[i] = val;
      if (val == 0) {
        player = (char *)datum_get(player_data, datum_handle);
        unit = (char *)object_get_and_verify_type(*(int *)(player + 0x34), 3);
        if (i == 0)
          *(unsigned int *)(unit + 0x1b4) &= ~0x10u;
      }
    }
  }
}

__attribute__((noinline)) static bool
players_respawn_coop_teleport(int player_handle, int anchor_unit_handle,
                              void *anchor_position)
{
  return ((bool (*)(int, int, void *))0xbbb80)(
    player_handle, anchor_unit_handle, anchor_position);
}

/* Attempt to respawn all dead players in co-op by teleporting them to a
 * living player's unit position.
 *
 * Returns true if at least one dead player was successfully respawned.
 *
 * Flow:
 *  1. Clear respawn_failure (players_globals+0x2c) to 0.
 *  2. If the respawn-pending flag (players_globals+0x2e) is clear:
 *     a. If dangerous_projectiles_near_player() or any_unit_is_dangerous():
 *        set failure=1, return false.
 *     b. If FUN_425b0() (AI enemies visible/near): set failure=2, return
 *        false.
 *  3. Iterate all players via data_iterator_new/data_iterator_next on
 *     player_data. For each player with a valid unit handle (+0x34 != -1):
 *     - Walk the object parent chain via FUN_13d7f0 to find the root object.
 *     - If root == player->unit (no parent):
 *         call object_try_and_get_type(unit, 1) to get unit data.
 *         live := (unit_data[0x424] & 1) != 0  (alive/shield flag).
 *     - Else (player is seated in a vehicle):
 *         call object_try_and_get_type(root, 2) to get vehicle data.
 *         live := vehicle_data[0x428] != 0  (SETA: passengers > 0).
 *     - If live: set failure=3.
 *     - Else: record unit as iVar7 (a live anchor for respawn).
 *  4. If iVar7 != -1 (at least one living player found):
 *     Reinitialise iterator; for each dead player (unit handle == -1):
 *       - Call FUN_bbcb0(player_handle) to trigger the respawn sequence.
 *       - If player still has no unit: mark respawn failed (bVar2=0).
 *       - Else: look up a spawn position (object_get_and_verify_type(iVar7,
 *         0xffffffff) + 0x50) and call FUN_bbb80(player_handle, iVar7,
 *         spawn_pos) to place them.
 *  5. Update respawn-pending flag and, on success, clear respawn_failure.
 *
 * Uncertain: exact semantics of FUN_bbb80 (player_teleport_to_unit?),
 * FUN_bbcb0 (player_spawn?), FUN_425b0 (ai_enemies_near_player?),
 * and the field meanings at object+0x424, object+0x428. */
bool players_respawn_coop(void)
{
  bool bVar1;
  bool bVar2;
  char uVar3;
  data_iter_t iter;
  char *player;
  int iVar7; /* handle of a living player's unit used as respawn anchor */
  void *live_obj;

  /* Step 1: clear respawn failure code. */
  *(int16_t *)((char *)players_globals + 0x2c) = 0;
  bVar2 = 0;

  /* Step 2a: if not already in a wait state, check for hazards. */
  if (*((char *)players_globals + 0x2e) == 0) {
    if (dangerous_projectiles_near_player() || any_unit_is_dangerous()) {
      *(int16_t *)((char *)players_globals + 0x2c) = 1;
      return (bool)bVar2;
    }
  }

  /* Step 2b: check if enemies are nearby (AI visibility). */
  if (*((char *)players_globals + 0x2e) == 0) {
    if (((bool (*)(void))0x425b0)()) {
      *(int16_t *)((char *)players_globals + 0x2c) = 2;
      return (bool)bVar2;
    }
  }

  /* Step 3: scan all players; find a live anchor unit. */
  iVar7 = NONE;
  data_iterator_new(&iter, player_data);
  while ((player = (char *)data_iterator_next(&iter)) != NULL) {
    if (*(int *)(player + 0x34) != NONE) {
      /* Walk parent chain to root object. */
      int root = ((int (*)(int))0x13d7f0)(*(int *)(player + 0x34));
      if (root == *(int *)(player + 0x34)) {
        /* No parent: check unit data at +0x424. */
        char *udata = (char *)object_try_and_get_and_verify_type(
          *(int *)(player + 0x34), 1);
        if (udata != NULL) {
          bVar1 = (udata[0x424] & 1) != 0;
          goto check_live;
        }
      } else {
        /* Has parent (seated): check vehicle data at +0x428. */
        char *vdata = (char *)object_try_and_get_and_verify_type(root, 2);
        if (vdata != NULL) {
          bVar1 = (unsigned char)vdata[0x428] > 0;
          goto check_live;
        }
      }
      iVar7 = *(int *)(player + 0x34);
      continue;
    check_live:
      if (bVar1) {
        *(int16_t *)((char *)players_globals + 0x2c) = 3;
      } else {
        iVar7 = *(int *)(player + 0x34);
      }
    }
  }

  /* Step 4: respawn dead players near the live anchor. */
  if (iVar7 != NONE) {
    bVar2 = 1;
    data_iterator_new(&iter, player_data);
    while ((player = (char *)data_iterator_next(&iter)) != NULL) {
      if (*(int *)(player + 0x34) == NONE) {
        /* Try to spawn the dead player. */
        player_spawn(iter.datum_handle);
        if (*(int *)(player + 0x34) == NONE) {
          /* Still dead: respawn failed. */
          bVar2 = 0;
        } else {
          /* Teleport to anchor unit's position (+0x50). */
          live_obj = object_get_and_verify_type(iVar7, 0xffffffff);
          bVar2 = players_respawn_coop_teleport(iter.datum_handle, iVar7,
                                                (char *)live_obj + 0x50);
        }
      }
    }
  }

  /* Step 5: update the respawn-pending flag and clear failure on success. */
  if (*((char *)players_globals + 0x2e) == 0 || bVar2 != 0) {
    uVar3 = 0;
  } else {
    uVar3 = 1;
  }
  *((char *)players_globals + 0x2e) = uVar3;
  if (bVar2 != 0) {
    *(int16_t *)((char *)players_globals + 0x2c) = 0;
  }
  return bVar2;
}

/* FUN_000bbfe0 (0xbbfe0) — XBE naked draft (batch 130). */
#if defined(__clang__)
static void *(*const bbbfe0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const bbbfe0_get)(int, int) = object_get_and_verify_type;

__attribute__((naked, noinline))
void FUN_000bbfe0(int player_handle __attribute__((unused)), int16_t action_result_type __attribute__((unused)), int object_handle __attribute__((unused)), int16_t seat_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movw 0x8(%%ebp), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0xb, %%ax\n\t"
      "je .LFUN_000bbfe0_1\n\t"
      "movw 0x28(%%ebx), %%cx\n\t"
      "cmpw %%cx, %%ax\n\t"
      "jne .LFUN_000bbfe0_3\n\t"
      "movl 0x34(%%ebx), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x24(%%ebx), %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "addl $0xc, %%esi\n\t"
      "call *%[get]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "addl $0xc, %%edi\n\t"
      "call *%[get]\n\t"
      "flds (%%edi)\n\t"
      "fsubs (%%esi)\n\t"
      "addl $0xc, %%eax\n\t"
      "flds 0x4(%%edi)\n\t"
      "addl $0x18, %%esp\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "flds 0x8(%%edi)\n\t"
      "popl %%edi\n\t"
      "fsubs 0x8(%%esi)\n\t"
      "flds (%%eax)\n\t"
      "fsubs (%%esi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs 0x8(%%esi)\n\t"
      "popl %%esi\n\t"
      "fstps -0x4(%%ebp)\n\t"
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
      "flds -0x4(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fxch %%st(1)\n\t"
      "fxch %%st(1)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000bbfe0_2\n\t"
      "movw 0x8(%%ebp), %%ax\n\t"
      ".LFUN_000bbfe0_1:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movw %%ax, 0x28(%%ebx)\n\t"
      "movw 0x10(%%ebp), %%ax\n\t"
      "movl %%edx, 0x24(%%ebx)\n\t"
      "movw %%ax, 0x2a(%%ebx)\n\t"
      ".LFUN_000bbfe0_2:\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000bbfe0_3:\n\t"
      "jle .LFUN_000bbfe0_2\n\t"
      "jmp .LFUN_000bbfe0_1\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [dget] "m"(bbbfe0_dget), [get] "m"(bbbfe0_get)
      : "memory");
}
#else
#error "FUN_000bbfe0: clang naked draft required"
#endif


void player_update_nearby_biped(int datum_handle, int object_handle)
{
  char *player;
  char *nearby_biped;
  char *unit;
  void *game_globals;
  char *difficulty_entry;
  float angle_delta;
  int16_t seat_index;
  int16_t seat_state;

  player = (char *)datum_get(player_data, datum_handle);
  nearby_biped = (char *)object_get_and_verify_type(object_handle, 2);
  if ((*(unsigned char *)(nearby_biped + 0xb6) & 4) != 0)
    return;

  game_globals = game_globals_get();
  difficulty_entry =
    (char *)tag_block_get_element((char *)game_globals + 0x110, 0, 0x80);
  angle_delta = *(float *)0x2568bc - *(float *)(difficulty_entry + 0x70);

  nearby_biped = (char *)object_get_and_verify_type(object_handle, 2);
  if (*(float *)(nearby_biped + 0x38) <= xbox_cosf(angle_delta)) {
    if ((*(unsigned char *)(nearby_biped + 0x424) & 0x10) == 0 &&
        *(int *)(nearby_biped + 0x2d4) == -1) {
      FUN_000bbfe0(datum_handle, 11, object_handle, -1);
    }
  } else {
    if (unit_current_weapon_is_busy(*(int *)(player + 0x34)))
      return;

    unit = (char *)object_get_and_verify_type(*(int *)(player + 0x34), 3);
    if (*(float *)(unit + 0x20) * *(float *)(unit + 0x20) +
          *(float *)(unit + 0x1c) * *(float *)(unit + 0x1c) +
          *(float *)(unit + 0x18) * *(float *)(unit + 0x18) >=
        *(float *)0x25bb10)
      return;

    nearby_biped = (char *)object_get_and_verify_type(object_handle, 2);
    if (FUN_00012170((float *)(nearby_biped + 0x3c)) >= *(float *)0x25bb10)
      return;

    seat_index = -1;
    seat_state = unit_find_best_enter_seat(*(int *)(player + 0x34),
                                           object_handle, &seat_index);

    if (seat_state == 2) {
      if (seat_index == -1) {
        display_assert("seat_index != NONE",
                       "c:\\halo\\SOURCE\\game\\players.c", 0x838, 1);
        system_exit(-1);
      }
      FUN_000bbfe0(datum_handle, 8, object_handle,
                                     seat_index);
      return;
    }
    if (seat_state == 1) {
      if (seat_index == -1) {
        display_assert("seat_index != NONE",
                       "c:\\halo\\SOURCE\\game\\players.c", 0x83d, 1);
        system_exit(-1);
      }
      FUN_000bbfe0(datum_handle, 9, object_handle,
                                     seat_index);
      return;
    }
  }
}

void player_update_nearby_weapon(int datum_handle, int object_handle)
{
  char *player;
  char *unit;
  char *weapon;
  float local_position[3];

  player = (char *)datum_get(player_data, datum_handle);
  unit = (char *)object_get_and_verify_type(*(int *)(player + 0x34), 3);
  weapon = (char *)object_get_and_verify_type(object_handle, 0x380);

  unit_set_seat_state(*(int *)(player + 0x34), local_position);
  if (!fast_vector_intersects_sphere(local_position, (float *)(unit + 0x1ec),
                                     (float *)(weapon + 0x50),
                                     *(float *)(weapon + 0x5c)))
    return;
  if (!FUN_000971a0(object_handle, local_position, (float *)(unit + 0x1ec)))
    return;
  if (!device_can_change_position(object_handle))
    return;

  FUN_000bbfe0(datum_handle, 10, object_handle, -1);
}

/* Handle the result of a player interacting with an equipment (powerup) object.
 *
 * Reads the equipment's tag definition to determine the powerup type
 * (offset 0x308 in the 'eqip' tag) and the duration (offset 0x30c,
 * multiplied by 30 ticks/second).  Dispatches by powerup type:
 *   1 = double speed  — adds ticks to players_globals+0x26, enables flag
 *   2 = overshield    — checks unit body vitality, triggers shield effect
 *   5 = health        — checks unit shield vitality, triggers health effect
 *   3 = active camo   — powerup index 0, calls player_try_to_apply_powerup
 *   4 = full-spectrum — powerup index 1, calls player_try_to_apply_powerup
 * On success, notifies the scoring system, plays the equipment pickup
 * sound, and deactivates the equipment object. */
void player_set_action_result_for_equipment(int player_handle,
                                            int equipment_handle)
{
  char *player;
  char *eqip_obj;
  char *tag;
  int16_t powerup_type;
  int16_t ticks;
  int powerup_index;

  player = (char *)datum_get(player_data, player_handle);
  eqip_obj = (char *)object_get_and_verify_type(equipment_handle, 8);
  tag = (char *)tag_get(0x65716970, *(int *)eqip_obj);

  /* Duration in ticks: tag float * 30.0f, truncated to int16_t. */
  ticks = (int16_t)(*(float *)(tag + 0x30c) * 30.0f);
  if (ticks <= 0)
    return;

  powerup_type = *(int16_t *)(tag + 0x308);

  if (powerup_type == 1) {
    /* Double speed: accumulate ticks and set flag. */
    *(int16_t *)((char *)players_globals + 0x26) += ticks;
    game_set_players_are_double_speed(true);
  } else if (powerup_type == 2) {
    /* Overshield: check if unit can receive it. */
    if (!object_double_charge_shield(*(int *)(player + 0x34)))
      return;
    player_apply_overshield_effect(player_handle);
  } else if (powerup_type == 5) {
    /* Health: check if unit can receive it. */
    if (!object_restore_body(*(int *)(player + 0x34)))
      return;
    player_apply_health_effect(player_handle);
  } else {
    /* Active camo (3) or full-spectrum vision (4). */
    if (powerup_type == 3) {
      powerup_index = 0;
    } else if (powerup_type == 4) {
      powerup_index = 1;
    } else {
      display_assert(0, "c:\\halo\\SOURCE\\game\\players.c", 0xac7, 1);
      system_exit(-1);
    }
    /* Try to apply the powerup. */
    if (!player_handle_powerup(player_handle, powerup_index, ticks))
      return;
    /* Active camo (index 0) triggers a location notification. */
    if ((int16_t)powerup_index == 0) {
      player_apply_camo_notification(player_handle);
    }
  }

  /* Common exit: notify scoring, play pickup sound, deactivate equipment. */
  eqip_obj = (char *)object_get_and_verify_type(equipment_handle, 8);
  {
    int16_t local_player_idx =
      *(int16_t *)(player + 2); /* player+0x2: local_player_index */
    ((void (*)(int, int))0xd0c60)((unsigned short)local_player_idx,
                                  *(int *)eqip_obj);
  }
  if (*(int16_t *)(player + 2) != -1) {
    item_activate_equipment_effect(equipment_handle);
  }
  object_delete(equipment_handle);
}

/* Update all player actions before game logic runs for this tick.
 *
 * For each player:
 *   1. Validate the action data received from player_control.
 *   2. If the player has no unit, try to spawn them (in a vehicle or
 *      normally), or defer to the game engine's respawn logic.
 *   3. If the player has a live unit and input is not inhibited, build
 *      a unit_control_t from the action and apply it to the unit via
 *      unit_set_control.  If input IS inhibited but the unit has no
 *      vehicle seat, derive a neutral control from the unit's current
 *      facing/aiming/looking vectors and apply that instead.
 * After iterating all players, update both local and full PVS, then
 * recount local players into players_globals+0x24. */
void players_update_before_game(void)
{
  player_action_t action_buf[16]; /* [EBP-0x2a8]: 16*0x20 = 0x200 bytes */
  data_iter_t iter; /* [EBP-0x14]                          */
  int datum_handle; /* [EBP-0xc] = iter.datum_handle       */
  char *player; /* [EBP-0x4] = current player datum ptr */
  unit_control_t ctl; /* [EBP-0x68]: control for enabled-input path */
  unit_control_t ctl2; /* [EBP-0xac]: control for disabled-input path */
  int action_index;
  player_action_t *action;
  char *unit_data;
  int unit_handle;
  unit_control_t *ctl_ptr;
  char *def_zero; /* ptr to default zero vector (*(char**)0x31fc38) */

  /* Profile enter. */
  if (*(char *)0x449ef1 != 0 && *(char *)0x2f0898 != 0)
    profile_enter_private((void *)0x2f0890);

  /* Collect current player actions from the controller subsystem.
   * action_buf receives up to 16 entries (one per network player slot),
   * each 0x20 bytes. Returns false if the action queue is not ready. */
  if (!player_control_get_current_actions(action_buf)) {
    display_assert(NULL, "c:\\halo\\SOURCE\\game\\players.c", 0x30a, 1);
    system_exit(-1);
  }

  /* Iterate all player datums. */
  data_iterator_new(&iter, player_data);
  player = (char *)data_iterator_next(&iter);
  while (player != NULL) {
    datum_handle = (int)iter.datum_handle;

    /* action_index = low 16 bits of datum handle (slot index in action_buf).
     * Each entry is 0x20 bytes wide. */
    action_index = (int)(int16_t)(datum_handle & 0xffff);

    if (action_index < 0 || action_index >= 16) {
      display_assert(
        "action_index>=0 && action_index<NETWORK_GAME_MAXIMUM_PLAYER_COUNT",
        "c:\\halo\\SOURCE\\game\\players.c", 0x255, 1);
      system_exit(-1);
    }
    action = &action_buf[action_index];

    /* --- Validate action fields: NaN/inf checks on floats --- */

    /* desired_facing.pitch */
    if (((*(uint32_t *)&action->desired_facing_pitch) & 0x7f800000u) ==
        0x7f800000u) {
      csprintf((char *)0x5ab100, "%s: assert_valid_real(0x%08X %f)",
               "action->desired_facing.pitch",
               *(uint32_t *)&action->desired_facing_pitch,
               (double)action->desired_facing_pitch,
               "c:\\halo\\SOURCE\\game\\players.c", 0x25a, 1);
      display_assert(NULL, "c:\\halo\\SOURCE\\game\\players.c", 0x25a, 1);
      system_exit(-1);
    }

    /* desired_facing.yaw */
    if (((*(uint32_t *)&action->desired_facing_yaw) & 0x7f800000u) ==
        0x7f800000u) {
      csprintf((char *)0x5ab100, "%s: assert_valid_real(0x%08X %f)",
               "action->desired_facing.yaw",
               *(uint32_t *)&action->desired_facing_yaw,
               (double)action->desired_facing_yaw,
               "c:\\halo\\SOURCE\\game\\players.c", 0x25b, 1);
      display_assert(NULL, "c:\\halo\\SOURCE\\game\\players.c", 0x25b, 1);
      system_exit(-1);
    }

    /* throttle (2D vector) */
    if (((*(uint32_t *)&action->throttle_x) & 0x7f800000u) == 0x7f800000u ||
        ((*(uint32_t *)&action->throttle_y) & 0x7f800000u) == 0x7f800000u) {
      csprintf((char *)0x5ab100, "%s: assert_valid_real_vector2d(%f, %f)",
               "&action->throttle", (double)action->throttle_x,
               (double)action->throttle_y, "c:\\halo\\SOURCE\\game\\players.c",
               0x25c, 1);
      display_assert(NULL, "c:\\halo\\SOURCE\\game\\players.c", 0x25c, 1);
      system_exit(-1);
    }

    /* primary_trigger */
    if (((*(uint32_t *)&action->primary_trigger) & 0x7f800000u) ==
        0x7f800000u) {
      csprintf((char *)0x5ab100, "%s: assert_valid_real(0x%08X %f)",
               "action->primary_trigger", *(uint32_t *)&action->primary_trigger,
               (double)action->primary_trigger,
               "c:\\halo\\SOURCE\\game\\players.c", 0x25d, 1);
      display_assert(NULL, "c:\\halo\\SOURCE\\game\\players.c", 0x25d, 1);
      system_exit(-1);
    }

    /* desired_weapon_index: NONE or [0..MAXIMUM_WEAPONS_PER_UNIT=4] */
    if (action->desired_weapon_index != -1 &&
        (action->desired_weapon_index < 0 ||
         action->desired_weapon_index > 4)) {
      display_assert(
        "(NONE == action->desired_weapon_index) || ((action->desired_weapon_"
        "index >= 0) && (action->desired_weapon_index <= "
        "MAXIMUM_WEAPONS_PER_UNIT))",
        "c:\\halo\\SOURCE\\game\\players.c", 0x25f, 1);
      system_exit(-1);
    }

    /* desired_grenade_index: NONE or [0..NUMBER_OF_UNIT_GRENADE_TYPES=2] */
    if (action->desired_grenade_index != -1 &&
        (action->desired_grenade_index < 0 ||
         action->desired_grenade_index > 2)) {
      display_assert(
        "(NONE == action->desired_grenade_index) || ((action->desired_grenade"
        "_index >= 0) && (action->desired_grenade_index <= "
        "NUMBER_OF_UNIT_GRENADE_TYPES))",
        "c:\\halo\\SOURCE\\game\\players.c", 0x260, 1);
      system_exit(-1);
    }

    /* desired_zoom_level: NONE or >= 0 */
    if (action->desired_zoom_level != -1 && action->desired_zoom_level < 0) {
      display_assert(
        "(NONE == action->desired_zoom_level) || ((action->desired_zoom_level"
        " >= 0))",
        "c:\\halo\\SOURCE\\game\\players.c", 0x261, 1);
      system_exit(-1);
    }

    /* --- Spawn logic: player currently has no unit --- */
    if (*(int *)(player + 0x34) == -1 && !game_in_editor()) {
      if (game_engine_running()) {
        /* Multiplayer / game-engine managed respawn.
         * FUN_a8c80: check if player is allowed to respawn (timer, etc).
         * FUN_a8df0: clear the respawn window state.
         * FUN_ad3e0: post-spawn game-engine notification. */
        if (((bool (*)(int))0xa8c80)(datum_handle)) {
          ((void (*)(int))0xa8df0)(datum_handle);
          player_spawn(datum_handle);
          if (*(int *)(player + 0x34) == -1) {
            /* Spawn failed — mark respawn deferred at player+0x2c. */
            *(int *)(player + 0x2c) = 1;
          } else {
            ((void (*)(int))0xad3e0)(datum_handle);
          }
        }
      } else {
        /* Single-player / co-op spawn path.
         * FUN_e43e0: check if some cutscene/mode blocks spawning. */
        if (!((bool (*)(void))0xe43e0)()) {
          if (*(int16_t *)(player + 0xaa) == 0) {
            /* Normal: spawn the player. */
            player_spawn(datum_handle);
          } else if (*((char *)players_globals + 0x28) == 0) {
            /* All-dead flag is clear: call the deferred-respawn helper with
             * players_globals+0x2e byte (respawn context). */
            ((void (*)(int))0x100390)(
              (int)(unsigned char)*((char *)players_globals + 0x2e));
          }
        }
      }
    }

    /* --- Control logic: player has a unit --- */
    unit_handle = *(int *)(player + 0x34);
    if (unit_handle == -1 || !unit_is_alive(unit_handle))
      goto next_player;

    /* Resolve unit data pointer (type 3 = biped/unit). */
    unit_data = (char *)object_get_and_verify_type(unit_handle, 3);

    if (*((char *)players_globals + 0x29) == 0) {
      /* Input is ENABLED. */

      /* Binoculars request (action bit 6): if the unit has no active
       * weapon-seat tag (unit+0xcc == -1) and the game is not in a
       * "no-binoculars" state, set binoculars-pending flag (bit 10). */
      if ((action->buttons & 0x40u) != 0 && *(int *)(unit_data + 0xcc) == -1 &&
          !player_try_to_spawn_in_vehicle(datum_handle)) {
        action->buttons |= 0x400u;
      }

      /* Zoom tracking: player+0x3e caches the zoom-change result.
       * Clear it unless the zoom-hold flag (bit 14) is set and the
       * unit has no active weapon-seat tag. */
      if ((action->buttons & 0x4000u) == 0 ||
          *(int *)(unit_data + 0xcc) != -1) {
        *(char *)(player + 0x3e) = 0;
      } else if (*(char *)(player + 0x3e) == 0) {
        *(char *)(player + 0x3e) =
          (char)player_try_to_enter_vehicle(datum_handle);
      }

      /* Alt-attack / throw-weapon (sign bit of action->buttons byte 0):
       * if set and unit has a weapon in the special slot (unit+0x2c8 != -1),
       * invoke the vehicle-action result handler and clear the seat tag. */
      if ((*(char *)&action->buttons & 0x80) != 0 &&
          *(int *)(unit_data + 0x2c8) != -1) {
        player_set_action_result_for_equipment(datum_handle,
                                               *(int *)(unit_data + 0x2c8));
        unit_clear_seat_tag(*(int *)(player + 0x34));
      }

      /* Determine active weapon handle and handle zoom-change request.
       *
       * Re-fetches unit data (compiler re-fetched the pointer after the
       * intervening writes above), reads the currently-selected weapon slot
       * index from unit+0x2a2 (sign-extended), then calls unit_get_weapon to
       * get the weapon's datum handle.  If valid and the weapon can zoom,
       * propagate scope change (bits 0x1800) to the unit, then sync the
       * active weapon index into the action's desired_weapon_index. */
      {
        char *udata2;
        int16_t active_wi;
        int wep_handle;

        udata2 = (char *)object_get_and_verify_type(*(int *)(player + 0x34), 3);
        active_wi = *(int16_t *)(udata2 + 0x2a2);
        wep_handle = unit_get_weapon(*(int *)(player + 0x34), active_wi);

        if (wep_handle != -1 && ((bool (*)(int))0xfb090)(wep_handle)) {
          /* Weapon can zoom. If scope-change bits set, call FUN_1ae600. */
          if (action->buttons & 0x1800u) {
            unit_set_in_vehicle(*(int *)(player + 0x34), 1);
          }
          /* Sync active weapon index into the action record. */
          action->desired_weapon_index = *(int16_t *)(unit_data + 0x2a2);
        }
      }

      /* Build the unit_control_t from the player action.
       * player_build_action_update writes three floats via
       * internal helper 0x10cc40 at offsets +0/+4/+8 relative to
       * arg2, so arg2 must point at the aiming vector slot
       * (ctl+0x28 = &ctl.aiming_x), NOT at the ctl header.
       * Original 0xbd563 does LEA ECX,[EBP-0x40] = &ctl.aiming_x.
       * Arg1 is the full 32-bit datum_handle (salt|index), forwarded
       * to data_get helper 0x119320. Arg3 is &action->desired_facing_yaw
       * (yaw/pitch float pair). */
      csmemset(&ctl, 0, sizeof(ctl));
      ctl.control_flags = (int16_t)action->buttons;
      player_build_action_update(datum_handle, &ctl.aiming_x,
                                 &action->desired_facing_yaw);

      /* Original 0xbd57a-0xbd58f copies aiming into both facing
       * (ctl+0x1c) and looking (ctl+0x34). player_build_action_update
       * only writes aiming; the caller is responsible for mirroring
       * it into the other two vectors so unit_set_control's unit-vector
       * validation doesn't see zero-length facing/looking. */
      ctl.facing_x = ctl.aiming_x;
      ctl.facing_y = ctl.aiming_y;
      ctl.facing_z = ctl.aiming_z;
      ctl.looking_x = ctl.aiming_x;
      ctl.looking_y = ctl.aiming_y;
      ctl.looking_z = ctl.aiming_z;

      /* Copy action scalars into control (player_build_action_update fills
       * facing/aiming/looking vectors but leaves these untouched). */
      ctl.throttle_x = action->throttle_x;
      ctl.weapon_index = action->desired_weapon_index;
      ctl.throttle_y = action->throttle_y;
      ctl.grenade_index = action->desired_grenade_index;
      ctl.primary_trigger = action->primary_trigger;
      ctl.zoom_level = action->desired_zoom_level;
      ctl.animation_state = 3;
      ctl.aiming_speed = 0;

      /* Validate assembled control data (mirrors unit_set_control
       * internal checks). */
      if (ctl.weapon_index != -1 &&
          (ctl.weapon_index < 0 || ctl.weapon_index > 4)) {
        display_assert(
          "(NONE == control_data.weapon_index) || ((control_data.weapon_"
          "index >= 0) && (control_data.weapon_index <= "
          "MAXIMUM_WEAPONS_PER_UNIT))",
          "c:\\halo\\SOURCE\\game\\players.c", 0x2e2, 1);
        system_exit(-1);
      }
      if (ctl.grenade_index != -1 &&
          (ctl.grenade_index < 0 || ctl.grenade_index > 2)) {
        display_assert(
          "(NONE == control_data.grenade_index) || ((control_data.grenade_"
          "index >= 0) && (control_data.grenade_index <= "
          "NUMBER_OF_UNIT_GRENADE_TYPES))",
          "c:\\halo\\SOURCE\\game\\players.c", 0x2e3, 1);
        system_exit(-1);
      }
      if (ctl.zoom_level != -1 && ctl.zoom_level < 0) {
        display_assert(
          "(NONE == control_data.zoom_level) || ((control_data.zoom_level"
          " >= 0))",
          "c:\\halo\\SOURCE\\game\\players.c", 0x2e4, 1);
        system_exit(-1);
      }
      ctl_ptr = &ctl;

    } else {
      /* Input is DISABLED (players_globals+0x29 != 0). */

      /* If the unit is currently seated in a vehicle (1a4/1a8 != -1),
       * skip the control update entirely. */
      if (*(int *)(unit_data + 0x1a8) != -1 ||
          *(int *)(unit_data + 0x1a4) != -1)
        goto next_player;

      /* Build a neutral control using the unit's own stored orientation
       * vectors, so unit_set_control's normalization asserts pass.
       * Original 0xbd6b3-0xbd722 writes:
       *   ctl2.throttle ← *(char**)0x31fc38 (zero vector)
       *   ctl2.facing   ← unit[0x1d4..0x1dc] (unit's current facing)
       *   ctl2.aiming   ← unit[0x1e0..0x1e8] (unit's current aiming)
       *   ctl2.looking  ← unit[0x204..0x20c] (unit's current looking) */
      csmemset(&ctl2, 0, sizeof(ctl2));
      ctl2.weapon_index = -1;
      ctl2.grenade_index = -1;
      ctl2.zoom_level = -1;
      ctl2.animation_state = 3;
      ctl2.aiming_speed = 0;
      ctl2.control_flags = 0;

      /* throttle = zero vector (*(char**)0x31fc38 → vec3 at [+0..+8]) */
      def_zero = *(char **)0x31fc38;
      ctl2.throttle_x = *(float *)(def_zero + 0);
      ctl2.throttle_y = *(float *)(def_zero + 4);
      ctl2.throttle_z = *(float *)(def_zero + 8);

      /* facing = unit's current facing vector (unit+0x1d4..0x1dc) */
      ctl2.facing_x = *(float *)(unit_data + 0x1d4);
      ctl2.facing_y = *(float *)(unit_data + 0x1d8);
      ctl2.facing_z = *(float *)(unit_data + 0x1dc);

      /* aiming = unit's current aiming vector (unit+0x1e0..0x1e8) */
      ctl2.aiming_x = *(float *)(unit_data + 0x1e0);
      ctl2.aiming_y = *(float *)(unit_data + 0x1e4);
      ctl2.aiming_z = *(float *)(unit_data + 0x1e8);

      /* looking = unit's current looking vector (unit+0x204..0x20c) */
      ctl2.looking_x = *(float *)(unit_data + 0x204);
      ctl2.looking_y = *(float *)(unit_data + 0x208);
      ctl2.looking_z = *(float *)(unit_data + 0x20c);

      ctl_ptr = &ctl2;
    }

    /* Apply the computed control to the unit. */
    unit_set_control(unit_handle, ctl_ptr);

  next_player:
    player = (char *)data_iterator_next(&iter);
  }

  /* Update potential visibility sets:
   * local players first (pass 1), then all players (pass 0).
   * players_update_pvs takes combined_pvs via EDI; original 0xbd100
   * reloads players_globals and offsets by 0x70 then 0x30 before
   * each call. */
  players_update_pvs(players_get_combined_pvs_local(), 1);
  players_update_pvs(players_get_combined_pvs(), 0);

  /* Recount local players: walk the 4 player-handle slots at
   * players_globals+0x4..0x10 and count non-NONE entries.
   * Result is stored at players_globals+0x24 (local_player_count field). */
  {
    int16_t count;
    int *slot;
    int i;

    count = 0;
    slot = (int *)((char *)players_globals + 4);
    for (i = 0; i < 4; i++, slot++) {
      if (*slot != -1)
        count++;
    }
    *(int16_t *)((char *)players_globals + 0x24) = count;
  }

  /* Profile exit. */
  if (*(char *)0x449ef1 != 0 && *(char *)0x2f0898 != 0)
    profile_exit_private((void *)0x2f0890);
}

void player_update_nearby_vehicle(int datum_handle, int object_handle)
{
  char *player;
  char *unit;
  char *nearby;
  int16_t local_player_index;
  int16_t i;
  int16_t seat_index;
  int nearby_weapon_count;
  int current_weapon_handle;
  int *equipment_obj;
  int *nearby_weapon_obj;
  int *current_weapon_obj;
  char *equipment_tag;
  char *nearby_weapon_tag;
  char *current_weapon_tag;
  bool in_vehicle_scope_state;
  bool current_is_special;
  int seat_occupant;

  player = (char *)datum_get(player_data, datum_handle);
  unit = (char *)object_get_and_verify_type(*(int *)(player + 0x34), 3);
  nearby = (char *)object_get_and_verify_type(object_handle, 0x1c);

  if (*(int *)(nearby + 0xcc) != -1 ||
      *(int *)(nearby + 0x1b0) == *(int *)(player + 0x34))
    return;

  local_player_index = *(int16_t *)(player + 2);

  for (i = 0; i < 4; i++) {
    seat_occupant = *(int *)(unit + 0x2a8 + (int)i * 4);
    if (seat_occupant != -1 && weapon_handle_potential_inventory_item(
                                 seat_occupant, object_handle,
                                 (uint16_t)local_player_index, &seat_index)) {
      if (seat_index > 0) {
        equipment_obj = (int *)object_get_and_verify_type(seat_occupant, 4);
        hud_player_enter_vehicle((uint16_t)local_player_index, *equipment_obj,
                                 seat_index);
      }
      break;
    }
  }

  equipment_obj = (int *)object_try_and_get_and_verify_type(object_handle, 8);
  if (equipment_obj != NULL) {
    equipment_tag = (char *)tag_get(0x65716970, *equipment_obj);
    if (*(int16_t *)(equipment_tag + 0x308) == 6) {
      if (unit_try_add_grenade(*(int *)(player + 0x34), object_handle)) {
        hud_player_set_equipment((uint16_t)local_player_index, *equipment_obj);
      }
    } else if (*(int16_t *)(equipment_tag + 0x308) != 0) {
      seat_occupant = unit_get_equipment(*(int *)(player + 0x34));
      if (seat_occupant == -1) {
        player_set_action_result_for_equipment(datum_handle, object_handle);
      } else {
        object_get_and_verify_type(seat_occupant, 8);
        current_weapon_tag = (char *)tag_get(0x65716970, *equipment_obj);
        if (*(int16_t *)(equipment_tag + 0x308) !=
            *(int16_t *)(current_weapon_tag + 0x308)) {
          FUN_000bbfe0(datum_handle, 5, object_handle, -1);
        }
      }
    }
  }

  nearby_weapon_obj =
    (int *)object_try_and_get_and_verify_type(object_handle, 4);
  if (nearby_weapon_obj == NULL ||
      !unit_can_enter_seat(*(int *)(player + 0x34), object_handle))
    return;

  nearby_weapon_tag = (char *)tag_get(0x77656170, *nearby_weapon_obj);
  in_vehicle_scope_state = (*(unsigned int *)(unit + 0x1b8) & 0x1800) != 0;
  unit = (char *)object_get_and_verify_type(*(int *)(player + 0x34), 3);
  current_weapon_handle =
    unit_get_weapon(*(int *)(player + 0x34), *(int16_t *)(unit + 0x2a2));
  nearby_weapon_count = unit_count_weapons(*(int *)(player + 0x34));

  current_is_special = false;
  if (nearby_weapon_count > 1 && current_weapon_handle != -1 &&
      (*(unsigned char *)(nearby_weapon_tag + 0x308) & 0x10) == 0) {
    current_weapon_obj =
      (int *)object_get_and_verify_type(current_weapon_handle, 4);
    current_weapon_tag = (char *)tag_get(0x77656170, *current_weapon_obj);
    if ((*(unsigned char *)(current_weapon_tag + 0x308) & 0x10) != 0) {
      current_is_special = true;
    }
  }

  if (in_vehicle_scope_state &&
      (*(unsigned char *)(nearby_weapon_tag + 0x308) & 8) != 0)
    return;

  if (player_examine_nearby_unit(*(int *)(player + 0x34), object_handle)) {
    if (unit_enter_seat(*(int *)(player + 0x34), object_handle, 1)) {
      nearby_weapon_obj = (int *)object_get_and_verify_type(object_handle, 4);
      hud_player_set_vehicle((uint16_t)local_player_index, *nearby_weapon_obj);
      player_clear_aim_assist(*(int *)(player + 0x34));
      return;
    }
  } else {
    if (!current_is_special &&
        unit_should_swap_weapon(*(int *)(player + 0x34), object_handle)) {
      current_weapon_obj =
        (int *)object_try_and_get_and_verify_type(current_weapon_handle, 4);
      if (nearby_weapon_count == 1 && current_weapon_obj != NULL &&
          *current_weapon_obj != *nearby_weapon_obj) {
        FUN_000bbfe0(datum_handle, 7, object_handle, -1);
        return;
      }
      FUN_000bbfe0(datum_handle, 6, object_handle, -1);
    }
  }
}

/* Check nearby objects via spatial query and dispatch spawn-state events.
 * For each object found within the unit's bounding sphere, switch on the
 * object type to call the appropriate handler.
 * EBX = datum_handle (register arg). */
void player_update_spawn_state(int datum_handle)
{
  char *player;
  char *unit;
  uint16_t count;
  int handles[16];
  int i;
  char *obj;
  int16_t obj_type;

  player = (char *)datum_get(player_data, datum_handle);
  if (*(int *)(player + 0x34) == -1)
    return;
  unit = (char *)object_get_and_verify_type(*(int *)(player + 0x34), 3);
  if (*(int *)(unit + 0xcc) != -1)
    return;

  count = (uint16_t)object_find_in_radius(
    0, 0x11f, (float *)(unit + 0x48), (float *)(unit + 0x50),
    *(float *)(unit + 0x5c), handles, 0x10);
  if ((int16_t)count <= 0)
    return;

  for (i = 0; i < (int16_t)count; i++) {
    obj = (char *)object_get_and_verify_type(handles[i], -1);
    obj_type = *(int16_t *)(obj + 0x64);
    switch (obj_type) {
    case 1:
      player_update_nearby_biped(datum_handle, handles[i]);
      break;
    case 2:
    case 3:
      player_update_nearby_vehicle(datum_handle, handles[i]);
      break;
    case 8:
      player_update_nearby_weapon(datum_handle, handles[i]);
      break;
    }
  }
}

/* Post-game-tick player update.
 *
 * Called once per tick after game logic has run.  Responsibilities:
 *   1. Tick down the double-speed-movement countdown stored at
 *      players_globals+0x26; when it reaches zero, clear the flag.
 *   2. For each player datum:
 *        a. If the telefrag-pending flag (player+0xd0) is clear, decay the
 *           effect timer (player+0xc8) toward zero.
 *        b. If the flag IS set and timer < 0x5a, trigger a player effect
 *           fade via FUN_a2ed0(datum_handle, (float)timer * CONST_26f2e0).
 *           If timer >= 0x5a and the unit exists and is not already flagged
 *           for deletion (bit 0x20 at unit+0xb6), print the "telefragged"
 *           HUD message, stop the effect (FUN_a2930), and mark the unit for
 *           deletion (FUN_1a7f80 sets bit 0x20 at unit+0xb6).
 *        c. Clear the telefrag-pending flag.
 *        d. Advance the player's short weapon/vehicle timers via FUN_bc4b0
 *
 * (EBX = datum_handle register arg). Binary comparison shows this
 * helper
 * only decrements small player/unit timers and is not where
 *           the
 * actual camera blend math lives.
 *        e. If the unit exists and its
 * object-type flags don't include 0x200000, scan scenario trigger volumes (tag
 * block at scenario+0x39c) for BSP-switch triggers that contain the player's
 * unit, and fire the BSP switch if found. f. Reset the player's pending-action
 * fields and call the per-player post-update helper FUN_bdb00 (EBX =
 * datum_handle).
 *   3. Advance the BSP-transition nibble counter packed into
 *      players_globals+0x2f (high nibble = counter, low nibble = bsp index).
 *   4. Handle the "all players dead" restart flag (players_globals+0x28):
 *      if clear, reset DAT_0046b6a8; if set and game engine is not running,
 *      trigger the SP-restart sequence (FUN_100380) and set the flag byte. */
void players_update_after_game(void)
{
  data_iter_t iter; /* [EBP-0x14] */
  int datum_handle; /* [EBP-0xc]  */
  int timer_val; /* [EBP-0x4]  */
  char *player;
  int16_t bsp_counter;
  int16_t i;
  void *block;
  void *entry;
  int16_t entry_bsp;
  char triggers_player;
  char cur_bsp_nibble;
  int unit_obj;
  int unit_handle;
  int scenario_bsp_count;
  unsigned char packed;

  /* Profile enter. */
  if (*(char *)0x449ef1 != 0 && *(char *)0x2f0e90 != 0)
    profile_enter_private((void *)0x2f0e88);

  /* Tick down the double-speed movement countdown. */
  if (*(int16_t *)((char *)players_globals + 0x26) > 0) {
    *(int16_t *)((char *)players_globals + 0x26) -= 1;
    if (*(int16_t *)((char *)players_globals + 0x26) == 0)
      game_set_players_are_double_speed(0);
  }

  /* Iterate all player datums. */
  data_iterator_new(&iter, player_data);
  player = (char *)data_iterator_next(&iter);
  while (player != NULL) {
    datum_handle = (int)iter.datum_handle;
    timer_val = *(int *)(player + 0xc8);

    if (*(char *)(player + 0xd0) == 0) {
      /* Telefrag-pending flag is clear: decay the effect timer. */
      if (timer_val > 0)
        *(int *)(player + 0xc8) = timer_val - 1;
    } else if (timer_val < 0x5a) {
      /* Flag set, early in window: trigger player effect fade.
       * Disasm: FILD [timer_val]; FMUL float ptr [0x26f2e0]; push as float;
       *         PUSH datum_handle; CALL FUN_a2ed0 */
      ((void (*)(int, float))0xa2ed0)(datum_handle,
                                      (float)timer_val * (*(float *)0x26f2e0));
    } else {
      /* Flag set, timer >= 0x5a: telefrag kill path. */
      unit_handle = *(int *)(player + 0x34);
      if (unit_handle != -1) {
        /* Check unit's delete-pending bit (bit 5 at unit+0xb6). */
        unit_obj = (int)object_get_and_verify_type(unit_handle, 3);
        if ((*(unsigned char *)(unit_obj + 0xb6) & 0x20) == 0) {
          /* Print "telefragged" to player's HUD (wchar_t literal). */
          if (*(int16_t *)(player + 2) != -1)
            hud_print_message(*(int16_t *)(player + 2),
                              L"You were telefragged");
          /* Stop player effect. */
          ((void (*)(int))0xa2930)(datum_handle);
          /* Mark unit for deletion: sets bit 0x20 at unit+0xb6. */
          ((void (*)(int))0x1a7f80)(*(int *)(player + 0x34));
        }
      }
    }

    /* Clear the telefrag-pending flag. */
    *(char *)(player + 0xd0) = 0;

    /* Advance the player's short weapon/vehicle timers.
     * Original CALL to
     * FUN_bc4b0 with EBX = datum_handle (register arg). */
    if (*(int *)(player + 0x34) != -1) {
      player_update_weapon_timers(datum_handle);
    }

    /* BSP-switch trigger volume scan. */
    if (*(int *)(player + 0x34) != -1) {
      /* Walk up to the root object to read its type flags.
       * FUN_13d7f0: follows parent chain, returns root object handle. */
      int root_handle = ((int (*)(int))0x13d7f0)(*(int *)(player + 0x34));
      unit_obj = (int)object_get_and_verify_type(root_handle, -1);
      /* Skip if object has type flag 0x200000 set (object+0x4). */
      if ((*(unsigned int *)(unit_obj + 4) & 0x200000) == 0) {
        /* scenario+0x39c = tag block for structure BSP trigger volumes.
         * Each element is 8 bytes: [0]=int16 handle, [2]=int16 bsp_index,
         * [4]=int16 destination_bsp. */
        scenario_t *scen = global_scenario_get();
        block = (void *)((char *)scen + 0x39c);
        scenario_bsp_count = *(int *)block;
        bsp_counter = 0;
        i = 0;
        while ((int)i < scenario_bsp_count) {
          entry = tag_block_get_element(block, (int)i, 8);
          /* [+2] = bsp index this trigger belongs to; DAT_326a0c = current
           * bsp index. */
          entry_bsp = *(int16_t *)((char *)entry + 2);
          if (entry_bsp == *(int16_t *)0x326a0c) {
            /* FUN_18ef00(trigger_handle, player_unit_handle):
             * returns non-zero if unit is inside the trigger volume. */
            triggers_player = (char)((char (*)(int16_t, int))0x18ef00)(
              *(int16_t *)entry, *(int *)(player + 0x34));
            if (triggers_player) {
              /* Extract the current BSP nibble from players_globals+0x2f.
               * Low nibble = current bsp index (sign-extended to byte). */
              cur_bsp_nibble =
                (char)(*(char *)((char *)players_globals + 0x2f) << 4) >> 4;
              if (cur_bsp_nibble != (char)0xff &&
                  (int16_t)cur_bsp_nibble != *(int16_t *)(player + 2)) {
                error(2, "!!!WARNING!!! teleported player triggering a "
                         "bsp switch!!!");
              }
              /* Pack local_player_index into low nibble. */
              *(unsigned char *)((char *)players_globals + 0x2f) &= 0xf;
              *(unsigned char *)((char *)players_globals + 0x2f) ^=
                (*(unsigned char *)(player + 2) ^
                 *(unsigned char *)((char *)players_globals + 0x2f)) &
                0xf;
              /* Record the trigger index and fire the BSP switch.
               * FUN_100500(int16 bsp_index): entry[4] = destination bsp. */
              *(int16_t *)((char *)players_globals + 0x2a) = bsp_counter;
              ((void (*)(int16_t))0x100500)(*(int16_t *)((char *)entry + 4));
            }
          }
          bsp_counter++;
          i++;
        }
      }
    }

    /* Reset pending-action state and run the per-player post helper.
     * datum_get returns the live datum pointer (may differ from 'player'
     * if the block was reallocated during iteration). */
    {
      char *pdatum = (char *)datum_get(player_data, datum_handle);
      *(int16_t *)(pdatum + 0x28) = 0;
      *(int *)(pdatum + 0x24) = -1;
    }
    player_update_spawn_state(datum_handle);

    player = (char *)data_iterator_next(&iter);
  }

  /* Advance the BSP-transition nibble counter at players_globals+0x2f.
   * High nibble is the per-tick counter (incremented by 0x10), low nibble
   * is the BSP destination index.  When the high nibble exceeds 0xc0
   * (i.e., more than 12 ticks elapsed), clamp it to 0xf0 and then clear
   * the low nibble to 0 (invalidate the pending switch). */
  packed = *(unsigned char *)((char *)players_globals + 0x2f);
  if ((packed & 0xf) != 0xf) {
    unsigned char hi = (unsigned char)(packed & 0xf0) + 0x10;
    unsigned char lo = packed & 0xf;
    packed = hi ^ lo;
    *(unsigned char *)((char *)players_globals + 0x2f) = packed;
    packed = *(unsigned char *)((char *)players_globals + 0x2f);
    if ((packed & 0xf0) > 0xc0) {
      packed |= 0xf;
      *(unsigned char *)((char *)players_globals + 0x2f) = packed;
      *(unsigned char *)((char *)players_globals + 0x2f) &= 0xf;
    }
  }

  /* Handle the "all players dead" restart flag at players_globals+0x28.
   * DAT_46b6a8 tracks whether the SP restart has already been kicked off
   * this death sequence. */
  if (*(char *)((char *)players_globals + 0x28) == 0) {
    /* No restart pending: clear the "already triggered" latch. */
    if (*(char *)0x46b6a8 != 0)
      *(char *)0x46b6a8 = 0;
  } else {
    /* Restart pending and engine is not running: kick off restart once. */
    if (!game_engine_running() && *(char *)0x46b6a8 == 0) {
      ((void (*)(void))0x100380)();
      *(char *)0x46b6a8 = 1;
    }
  }

  /* Profile exit. */
  if (*(char *)0x449ef1 != 0 && *(char *)0x2f0e90 != 0)
    profile_exit_private((void *)0x2f0e88);
}

char valid_real_vector2d(float *v)
{
  uint32_t bits;

  bits = *(uint32_t *)v;
  if ((bits & 0x7f800000) == 0x7f800000)
    return 0;
  bits = *(uint32_t *)(v + 1);
  if ((bits & 0x7f800000) == 0x7f800000)
    return 0;
  return 1;
}

void FUN_000BB290(float *out_direction)
{
  random_seed_get_direction3d((unsigned int *)get_global_random_seed_address(),
                              out_direction);
}

char FUN_000ba850(int16_t cluster_index, int object_handle)
{
  void *elem;

  if (cluster_index == (int16_t)NONE)
    return 0;
  elem = tag_block_get_element((char *)global_scenario_get() + 0x39c,
                               cluster_index, 8);
  if (FUN_0018ef00(*(uint16_t *)elem, object_handle))
    return 1;
  return 0;
}

void FUN_000bb180(int player_handle, int16_t flag)
{
  char *player;
  char *unit;

  player = (char *)datum_get(player_data, player_handle);
  unit = (char *)object_get_and_verify_type(*(int *)(player + 0x34), 3);
  if (flag == 0) {
    *(int *)(unit + 0x1b4) |= 0x10;
    *(int16_t *)(unit + 0x3d2) = 0;
  }
}

void FUN_000bb1c0(int player_handle, int16_t flag)
{
  char *player;
  char *unit;

  player = (char *)datum_get(player_data, player_handle);
  unit = (char *)object_get_and_verify_type(*(int *)(player + 0x34), 3);
  if (flag == 0)
    *(int *)(unit + 0x1b4) |= 0x20;
}

void FUN_000bb1f0(int player_handle, int16_t flag)
{
  char *player;
  char *unit;

  player = (char *)datum_get(player_data, player_handle);
  unit = (char *)object_get_and_verify_type(*(int *)(player + 0x34), 3);
  if (flag == 0)
    *(int *)(unit + 0x1b4) &= ~0x10;
}

int16_t player_get_starting_location_count(void)
{
  void *scenario;
  int netgame_index;
  void *netgame;
  int count;

  scenario = global_scenario_get();
  netgame_index = *(int *)0x5ac9f4;
  count = *(int16_t *)((char *)scenario + 0x354);
  if (netgame_index != NONE) {
    netgame = tag_block_get_element((char *)scenario + 0x42c,
                                    netgame_index & 0xffff, 0xb0);
    if (*(int *)((char *)netgame + 0xa4) > 0)
      return (int16_t)*(int *)((char *)netgame + 0xa4);
  }
  return count;
}

void *player_get_starting_location(int16_t index)
{
  void *scenario;
  void *loc;
  int netgame_index;
  void *netgame;
  void *net_loc;
  int16_t bsp_index;

  scenario = global_scenario_get();
  loc = NULL;
  if (index >= 0 && index < *(int *)((char *)scenario + 0x354))
    loc = tag_block_get_element((char *)scenario + 0x354, index, 0x34);
  netgame_index = *(int *)0x5ac9f4;
  if (netgame_index == NONE)
    return loc;
  netgame = tag_block_get_element((char *)scenario + 0x42c,
                                  netgame_index & 0xffff, 0xb0);
  if (index < 0 || index >= *(int *)((char *)netgame + 0xa4))
    return loc;
  net_loc = tag_block_get_element((char *)netgame + 0xa4, index, 0x34);
  bsp_index = *(int16_t *)((char *)netgame + 0x7e);
  if (bsp_index >= 0 &&
      bsp_index < *(int *)((char *)scenario + 0x5a4)) {
    *(int16_t *)((char *)net_loc + 0x12) = bsp_index;
    return net_loc;
  }
  return net_loc;
}

/* Copy RGB color into four consecutive float3 slots on placement (+0x58..). */
void placement_data_set_change_color(void *placement, float *color)
{
  float *dst;
  int i;

  dst = (float *)((char *)placement + 0x58);
  for (i = 0; i < 4; i++) {
    dst[0] = color[0];
    dst[1] = color[1];
    dst[2] = color[2];
    dst += 3;
  }
}

void players_handle_deleted_object(int object_handle)
{
  char *obj;
  uint8_t type;
  uint32_t type_bit;
  data_iter_t iter;
  char *player;

  obj = (char *)object_get_and_verify_type(object_handle, NONE);
  type = *(uint8_t *)(obj + 0x64);
  type_bit = 1u << type;
  if ((type_bit & 3) == 0)
    return;
  data_iterator_new(&iter, player_data);
  while ((player = (char *)data_iterator_next(&iter)) != NULL) {
    if (*(int *)(player + 0x34) == object_handle)
      player_died((int)iter.datum_handle);
  }
}

/* players_set_local_player_unit (0xba5f0) — XBE naked draft (batch 142). */
#if defined(__clang__)
static int (*const bba5f0_cb6870)(int16_t local_player_index) = player_control_get_unit_index;
static short (*const bba5f0_cfff80)(void) = game_connection;
static void (*const bba5f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bba5f0_exitfn)(int) = system_exit;
static void *(*const bba5f0_get)(int, int) = object_get_and_verify_type;
static void (*const bba5f0_c1adf10)(int unit_handle, char param_2) = unit_set_actively_controlled;
static int (*const bba5f0_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void *(*const bba5f0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const bba5f0_cb6fc0)(uint16_t local_player_index, int player_index) = player_control_new_unit;

__attribute__((naked, noinline))
void players_set_local_player_unit(int16_t local_player_index __attribute__((unused)), int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[cb6870]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[cfff80]\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Lplayers_set_local_player_unit_1\n\t"
      "pushl $1\n\t"
      "pushl $0x420\n\t"
      "pushl $0x26eb68\n\t"
      "pushl $0x26ea18\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayers_set_local_player_unit_1:\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lplayers_set_local_player_unit_2\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "movl $0xffffffff, 0x1c8(%%eax)\n\t"
      "call *%[c1adf10]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lplayers_set_local_player_unit_2:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lplayers_set_local_player_unit_3\n\t"
      "pushl %%ebx\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c1adf10]\n\t"
      "pushl %%edi\n\t"
      "call *%[cba3c0]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl %%eax, 0x1c8(%%ebx)\n\t"
      "popl %%ebx\n\t"
      ".Lplayers_set_local_player_unit_3:\n\t"
      "pushl %%edi\n\t"
      "call *%[cba3c0]\n\t"
      "pushl %%eax\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, 0x34(%%eax)\n\t"
      "movl $0xffffffff, 0x38(%%eax)\n\t"
      "call *%[cb6fc0]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cb6870] "m"(bba5f0_cb6870), [cfff80] "m"(bba5f0_cfff80), [assert] "m"(bba5f0_assert), [exitfn] "m"(bba5f0_exitfn), [get] "m"(bba5f0_get), [c1adf10] "m"(bba5f0_c1adf10), [cba3c0] "m"(bba5f0_cba3c0), [dget] "m"(bba5f0_dget), [cb6fc0] "m"(bba5f0_cb6fc0)
      : "memory");
}
#else
#error "players_set_local_player_unit: clang naked draft required"
#endif


/* find_best_starting_location_index (0xbbbe0) — XBE naked draft (batch 138). */
#if defined(__clang__)
static scenario_t * (*const bbbbe0_c18e380)(void) = global_scenario_get;
static void *(*const bbbbe0_elem)(void *, int, int) = tag_block_get_element;
static void * (*const bbbbe0_cbaae0)(int16_t index) = player_get_starting_location;
static float (*const bbbbe0_cadcf0)(int param_1, int param_2) = game_engine_get_starting_location_rating;
static int *(*const bbbbe0_gseed)(void) = get_global_random_seed_address;
static float (*const bbbbe0_rrange)(int *, float, float) = random_real_range;
static float (*const bbbbe0_c1d9e70)(float base, float exponent) = FUN_001d9e70;

__attribute__((naked, noinline))
int16_t find_best_starting_location_index(int team_or_player __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c18e380]\n\t"
      "movl 0x5ac9f4, %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "movw 0x354(%%eax), %%bx\n\t"
      "je .Lfind_best_starting_location_index_1\n\t"
      "pushl $0xb0\n\t"
      "andl $0xffff, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0xa4(%%eax), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .Lfind_best_starting_location_index_1\n\t"
      "movw %%cx, %%bx\n\t"
      ".Lfind_best_starting_location_index_1:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "xorl %%esi, %%esi\n\t"
      "testw %%bx, %%bx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jle .Lfind_best_starting_location_index_5\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lfind_best_starting_location_index_2:\n\t"
      "pushl %%esi\n\t"
      "call *%[cbaae0]\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[cadcf0]\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x3f800000\n\t"
      "pushl $0\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fldl 0x25fea8\n\t"
      "addl $0xc, %%esp\n\t"
      "call *%[c1d9e70]\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fcoms -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lfind_best_starting_location_index_3\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "jmp .Lfind_best_starting_location_index_4\n\t"
      ".Lfind_best_starting_location_index_3:\n\t"
      "fstp %%st(0)\n\t"
      ".Lfind_best_starting_location_index_4:\n\t"
      "incl %%esi\n\t"
      "cmpw %%bx, %%si\n\t"
      "jl .Lfind_best_starting_location_index_2\n\t"
      "movswl -0x8(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lfind_best_starting_location_index_5:\n\t"
      "popl %%esi\n\t"
      "movswl %%ax, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(bbbbe0_c18e380), [elem] "m"(bbbbe0_elem), [cbaae0] "m"(bbbbe0_cbaae0), [cadcf0] "m"(bbbbe0_cadcf0), [gseed] "m"(bbbbe0_gseed), [rrange] "m"(bbbbe0_rrange), [c1d9e70] "m"(bbbbe0_c1d9e70)
      : "memory");
}
#else
#error "find_best_starting_location_index: clang naked draft required"
#endif


/* FUN_000bb670 (0xbb670) — XBE naked draft (batch 106). */
#if defined(__clang__)
static void *(*const bbb670_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const bbb670_get)(int, int) = object_get_and_verify_type;
static void (*const bbb670_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bbb670_exitfn)(int) = system_exit;
static int (*const bbb670_c13d7f0)(int object_handle) = object_get_root_parent;
static void *(*const bbb670_tag)(int, int) = tag_get;
static float (*const bbb670_norm)(float *) = normalize3d;
static void (*const bbb670_m4x3)(void *, float *, float *, float *) = matrix4x3_from_forward_up_position;
static void (*const bbb670_xfrmpt)(float *, float *, float *) = matrix_transform_point;
static char (*const bbb670_c1a1430)(int unit_handle, int seat_handle, float *initial_position, float *final_position, float scale, char keep_basis, char dont_teleport, char scale_by_height) = biped_fix_position;
static int *(*const bbb670_gseed)(void) = get_global_random_seed_address;
static void (*const bbb670_c10b380)(unsigned int *seed, float *out) = random_seed_get_direction3d;
static scenario_t * (*const bbb670_c18e380)(void) = global_scenario_get;
static void *(*const bbb670_elem)(void *, int, int) = tag_block_get_element;
static char (*const bbb670_c18ef00)(int cluster_index, int object_handle) = FUN_0018ef00;
static void *(*const bbb670_tryget)(int, int) = object_try_and_get_and_verify_type;
static void (*const bbb670_cb6ea0)(uint16_t local_player_index, float *direction) = player_control_set_facing;
static void * (*const bbb670_c18e450)(void) = game_globals_get;
static void (*const bbb670_cbac80)(void *combined_pvs, bool local_player_only) = players_update_pvs;
static int (*const bbb670_o9ec30)(int, int, int, short, float, float, int, int) = FUN_0009ec30;
static void (*const bbb670_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const bbb670_cba890)(int player_handle, int target_handle) = FUN_000ba890;

__attribute__((naked, noinline))
char FUN_000bb670(int player_handle __attribute__((unused)), void *a __attribute__((unused)), void *b __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x7c, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%edi, -0x14(%%ebp)\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "je .LFUN_000bb670_19\n\t"
      "movl 0x5aa6cc, %%edx\n\t"
      "cmpw $1, 0x24(%%edx)\n\t"
      "jg .LFUN_000bb670_1\n\t"
      "pushl $1\n\t"
      "pushl $0x4f7\n\t"
      "pushl $0x26eb68\n\t"
      "pushl $0x26ee54\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000bb670_1:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13d7f0]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_000bb670_19\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13d7f0]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[get]\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ecx\n\t"
      "leal 0x18(%%ecx), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "flds -0x24(%%ebp)\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      "addl $0x14, %%esp\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "movl %%esi, 0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_000bb670_4\n\t"
      "flds 0x2c(%%ecx)\n\t"
      "fcomps 0x254b50\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000bb670_2\n\t"
      "addl $0x24, %%ecx\n\t"
      "jmp .LFUN_000bb670_3\n\t"
      ".LFUN_000bb670_2:\n\t"
      "addl $0x30, %%ecx\n\t"
      ".LFUN_000bb670_3:\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      ".LFUN_000bb670_4:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x62697064\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl 0x42c(%%eax), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fmuls 0x254644\n\t"
      "fadds 0x5c(%%edx)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000bb670_5\n\t"
      "pushl $1\n\t"
      "pushl $0x521\n\t"
      "pushl $0x26eb68\n\t"
      "pushl $0x26ee2c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000bb670_5:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000bb670_6\n\t"
      "pushl $1\n\t"
      "pushl $0x522\n\t"
      "pushl $0x26eb68\n\t"
      "pushl $0x26ee24\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000bb670_6:\n\t"
      "flds -0x24(%%ebp)\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "fchs\n\t"
      "pushl %%eax\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "movl 0x31fc44, %%ecx\n\t"
      "fstp %%st(0)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl $0x50, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x7c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[m4x3]\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "addl $0x14, %%esp\n\t"
      "movl %%edx, -0x7c(%%ebp)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      ".LFUN_000bb670_7:\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_000bb670_11\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movswl -0xc(%%ebp), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "leal 0x26ea88(,%%ecx,4), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x7c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[xfrmpt]\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0x40000000\n\t"
      "pushl $0\n\t"
      "leal -0x3c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a1430]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $0x2c, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_000bb670_10\n\t"
      "xorl %%edi, %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000bb670_8:\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_000bb670_9\n\t"
      "movl 0x31fc38, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, -0x2c(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[c10b380]\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "fadds -0x3c(%%ebp)\n\t"
      "pushl $0\n\t"
      "pushl $0x40000000\n\t"
      "pushl $0\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "fadds -0x38(%%ebp)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fadds -0x34(%%ebp)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "call *%[c1a1430]\n\t"
      "addl $0x28, %%esp\n\t"
      "incl %%edi\n\t"
      "cmpw $8, %%di\n\t"
      "movb %%al, %%bl\n\t"
      "jl .LFUN_000bb670_8\n\t"
      ".LFUN_000bb670_9:\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      ".LFUN_000bb670_10:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw $9, %%ax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jb .LFUN_000bb670_7\n\t"
      ".LFUN_000bb670_11:\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      ".LFUN_000bb670_12:\n\t"
      "testb %%bl, %%bl\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "movw $0xffff, 0x3c(%%edi)\n\t"
      "je .LFUN_000bb670_21\n\t"
      "call *%[c18e380]\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "cmpl $-1, 0x34(%%edi)\n\t"
      "jne .LFUN_000bb670_13\n\t"
      "pushl $1\n\t"
      "pushl $0x566\n\t"
      "pushl $0x26eb68\n\t"
      "pushl $0x26ee08\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000bb670_13:\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl 0x39c(%%edi), %%ecx\n\t"
      "addl $0x39c, %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "jle .LFUN_000bb670_16\n\t"
      ".LFUN_000bb670_14:\n\t"
      "pushl $8\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "movw 0x2(%%eax), %%dx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw 0x326a0c, %%dx\n\t"
      "jne .LFUN_000bb670_15\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x34(%%ecx), %%edx\n\t"
      "movswl (%%eax), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c18ef00]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000bb670_20\n\t"
      ".LFUN_000bb670_15:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl (%%edi), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_000bb670_14\n\t"
      ".LFUN_000bb670_16:\n\t"
      "movl 0x31fc38, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "leal 0x18(%%esi), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "je .LFUN_000bb670_23\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "addl $0x24, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "call *%[tryget]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000bb670_17\n\t"
      "movl 0x42c(%%eax), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_000bb670_17\n\t"
      "movl %%ecx, 0x42c(%%esi)\n\t"
      "movb 0x42b(%%eax), %%cl\n\t"
      "movb %%cl, 0x42b(%%esi)\n\t"
      ".LFUN_000bb670_17:\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "movl -0x2c(%%ebp), %%ecx\n\t"
      "leal 0x1d4(%%esi), %%edx\n\t"
      "movl %%edx, %%edi\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl %%ecx, 0x4(%%edi)\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      "leal 0x1e0(%%esi), %%edi\n\t"
      "addl $0x204, %%esi\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x4(%%edi)\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      "movl %%edx, 0x8(%%esi)\n\t"
      "movswl 0x2(%%eax), %%eax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_000bb670_18\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[cb6ea0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000bb670_18:\n\t"
      "pushl $0xf4\n\t"
      "pushl $0\n\t"
      "call *%[c18e450]\n\t"
      "addl $0x170, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0xc4(%%eax), %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_000bb670_23\n\t"
      "movl 0x5aa6cc, %%edi\n\t"
      "pushl $0\n\t"
      "addl $0x30, %%edi\n\t"
      "call *%[cbac80]\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[o9ec30]\n\t"
      "addl $0x24, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000bb670_19:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0x40000000\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a1430]\n\t"
      "addl $0x20, %%esp\n\t"
      "movb %%al, %%bl\n\t"
      "jmp .LFUN_000bb670_12\n\t"
      ".LFUN_000bb670_20:\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_000bb670_21:\n\t"
      "pushl $0x26edd8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $-1, 0x2(%%edi)\n\t"
      "jne .LFUN_000bb670_22\n\t"
      "pushl $1\n\t"
      "pushl $0x5a7\n\t"
      "pushl $0x26eb68\n\t"
      "pushl $0x26edb4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000bb670_22:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[cba890]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000bb670_23:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(bbb670_dget), [get] "m"(bbb670_get), [assert] "m"(bbb670_assert), [exitfn] "m"(bbb670_exitfn), [c13d7f0] "m"(bbb670_c13d7f0), [tag] "m"(bbb670_tag), [norm] "m"(bbb670_norm), [m4x3] "m"(bbb670_m4x3), [xfrmpt] "m"(bbb670_xfrmpt), [c1a1430] "m"(bbb670_c1a1430), [gseed] "m"(bbb670_gseed), [c10b380] "m"(bbb670_c10b380), [c18e380] "m"(bbb670_c18e380), [elem] "m"(bbb670_elem), [c18ef00] "m"(bbb670_c18ef00), [tryget] "m"(bbb670_tryget), [cb6ea0] "m"(bbb670_cb6ea0), [c18e450] "m"(bbb670_c18e450), [cbac80] "m"(bbb670_cbac80), [o9ec30] "m"(bbb670_o9ec30), [c8f390] "m"(bbb670_c8f390), [cba890] "m"(bbb670_cba890)
      : "memory");
}
#else
#error "FUN_000bb670: clang naked draft required"
#endif


/* Teleport wrapper: exit seat if needed, then FUN_000bb670. */
char player_teleport(int player_handle, void *a, void *b)
{
  char *player;
  int unit_handle;
  void *unit_obj;

  player = (char *)datum_get(player_data, player_handle);
  unit_handle = *(int *)(player + 0x34);
  unit_obj = object_try_and_get_and_verify_type(unit_handle, 1);
  if (!unit_obj)
    return 0;
  if (*(int *)((char *)unit_obj + 0xcc) != NONE)
    unit_exit_seat_end(unit_handle);
  return FUN_000bb670(player_handle, a, b);
}

/* debug_player_teleport (0xbc6c0) — XBE naked draft (batch 145). */
#if defined(__clang__)
static int (*const bbc6c0_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void *(*const bbc6c0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const bbc6c0_get)(int, int) = object_get_and_verify_type;
static int (*const bbc6c0_cba500)(int) = player_index_from_unit_index;
static char (*const bbc6c0_cbb670)(int player_handle, void *a, void *b) = FUN_000bb670;

__attribute__((naked, noinline))
void debug_player_teleport(int16_t local_a __attribute__((unused)), int16_t local_b __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[cba3c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Ldebug_player_teleport_1\n\t"
      "orl %%eax, %%edi\n\t"
      "jmp .Ldebug_player_teleport_2\n\t"
      ".Ldebug_player_teleport_1:\n\t"
      "pushl %%esi\n\t"
      "call *%[cba3c0]\n\t"
      "pushl %%eax\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      ".Ldebug_player_teleport_2:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[cba3c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Ldebug_player_teleport_3\n\t"
      "orl %%eax, %%esi\n\t"
      "jmp .Ldebug_player_teleport_4\n\t"
      ".Ldebug_player_teleport_3:\n\t"
      "pushl %%esi\n\t"
      "call *%[cba3c0]\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      ".Ldebug_player_teleport_4:\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Ldebug_player_teleport_5\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Ldebug_player_teleport_5\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "addl $0x50, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[cba500]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[cbb670]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Ldebug_player_teleport_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cba3c0] "m"(bbc6c0_cba3c0), [dget] "m"(bbc6c0_dget), [get] "m"(bbc6c0_get), [cba500] "m"(bbc6c0_cba500), [cbb670] "m"(bbc6c0_cbb670)
      : "memory");
}
#else
#error "debug_player_teleport: clang naked draft required"
#endif


/* Spawn an object at a starting-location record (EDI). */
int FUN_000bac10(int tag_index, void *start_loc)
{
  char placement[0x88];
  int handle;
  char *obj;

  if (*(int *)((char *)start_loc + 0xc) == NONE)
    return NONE;
  object_placement_data_new(placement, *(int *)((char *)start_loc + 0xc),
                            tag_index);
  handle = object_new(placement);
  if (handle == NONE)
    return NONE;
  obj = (char *)object_get_and_verify_type(handle, 4);
  *(int16_t *)(obj + 0x25e) = *(int16_t *)((char *)start_loc + 0x12);
  *(int16_t *)(obj + 0x260) = *(int16_t *)((char *)start_loc + 0x10);
  return handle;
}

/* FUN_000ba890 (0xba890) — XBE naked draft (batch 136). */
#if defined(__clang__)
static void *(*const bba890_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static bool (*const bba890_ca8e40)(void) = game_engine_can_score;
static void (*const bba890_cb56f0)(int handle, int param_2, int param_3, int param_4) = FUN_000b56f0;
static void (*const bba890_cba550)(int) = player_died;
static void *(*const bba890_get)(int, int) = object_get_and_verify_type;
static int (*const bba890_c1adeb0)(int unit_handle, int16_t weapon_index) = unit_get_weapon;
static void (*const bba890_c13fb80)(int object_handle) = object_deactivate;
static void (*const bba890_c13ffc0)(int object_handle, int flag) = object_set_garbage;

__attribute__((naked, noinline))
void FUN_000ba890(int player_handle __attribute__((unused)), int target_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x34(%%edi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000ba890_4\n\t"
      "call *%[ca8e40]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000ba890_1\n\t"
      "movl 0x34(%%edi), %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "call *%[cb56f0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_000ba890_1:\n\t"
      "movswl 0x2(%%edi), %%edx\n\t"
      "movl 0x34(%%edi), %%eax\n\t"
      "movl 0x5aa6cc, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, 0x14(%%ecx,%%edx,4)\n\t"
      "call *%[cba550]\n\t"
      "movswl 0x2(%%edi), %%edx\n\t"
      "movl 0x5aa6cc, %%eax\n\t"
      "movl 0x14(%%eax,%%edx,4), %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[get]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x2a2(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1adeb0]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl $0xffffffff, 0x1c8(%%edx)\n\t"
      "call *%[c13fb80]\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c13ffc0]\n\t"
      "addl $0x28, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .LFUN_000ba890_2\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[c13ffc0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000ba890_2:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_000ba890_3\n\t"
      "movl %%eax, 0x38(%%edi)\n\t"
      ".LFUN_000ba890_3:\n\t"
      "movl 0x5aa6cc, %%eax\n\t"
      "movb $0, 0x28(%%eax)\n\t"
      ".LFUN_000ba890_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(bba890_dget), [ca8e40] "m"(bba890_ca8e40), [cb56f0] "m"(bba890_cb56f0), [cba550] "m"(bba890_cba550), [get] "m"(bba890_get), [c1adeb0] "m"(bba890_c1adeb0), [c13fb80] "m"(bba890_c13fb80), [c13ffc0] "m"(bba890_c13ffc0)
      : "memory");
}
#else
#error "FUN_000ba890: clang naked draft required"
#endif


/* player_control_update_for_loaded_game_state (0xba970) — XBE naked draft (batch 128). */
#if defined(__clang__)
static __int16 (*const bba970_ce07c0)(__int16 a1) = player_ui_get_single_player_local_player_controller;
static int (*const bba970_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void (*const bba970_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bba970_exitfn)(int) = system_exit;
static void *(*const bba970_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const bba970_cba410)(unsigned __int16 a1, int a2) = local_player_set_player_index;
static void (*const bba970_cb6fc0)(uint16_t local_player_index, int player_index) = player_control_new_unit;
static void (*const bba970_cd98c0)(void) = FUN_000d98c0;
static void (*const bba970_cd7780)(short old_player, short new_player) = FUN_000d7780;
static void (*const bba970_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void player_control_update_for_loaded_game_state(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[ce07c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .Lplayer_control_update_for_loaded_game_state_1\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "movl %%esi, %%eax\n\t"
      ".Lplayer_control_update_for_loaded_game_state_1:\n\t"
      "pushl %%eax\n\t"
      "call *%[cba3c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lplayer_control_update_for_loaded_game_state_9\n\t"
      "movw 0x31fa94, %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .Lplayer_control_update_for_loaded_game_state_8\n\t"
      "pushl %%edi\n\t"
      ".Lplayer_control_update_for_loaded_game_state_2:\n\t"
      "cmpw $-1, %%si\n\t"
      "jl .Lplayer_control_update_for_loaded_game_state_3\n\t"
      "cmpw $4, %%si\n\t"
      "jl .Lplayer_control_update_for_loaded_game_state_4\n\t"
      ".Lplayer_control_update_for_loaded_game_state_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x3ab\n\t"
      "pushl $0x26eb68\n\t"
      "pushl $0x26eb88\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayer_control_update_for_loaded_game_state_4:\n\t"
      "cmpw $-1, %%si\n\t"
      "je .Lplayer_control_update_for_loaded_game_state_5\n\t"
      "movl 0x5aa6cc, %%ecx\n\t"
      "movswl %%si, %%eax\n\t"
      "movl 0x4(%%ecx,%%eax,4), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .Lplayer_control_update_for_loaded_game_state_6\n\t"
      ".Lplayer_control_update_for_loaded_game_state_5:\n\t"
      "incl %%esi\n\t"
      "cmpw $4, %%si\n\t"
      "jl .Lplayer_control_update_for_loaded_game_state_2\n\t"
      "jmp .Lplayer_control_update_for_loaded_game_state_7\n\t"
      ".Lplayer_control_update_for_loaded_game_state_6:\n\t"
      "movl 0x5aa6d4, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[cba410]\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "call *%[cb6fc0]\n\t"
      "pushl %%edi\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[cba410]\n\t"
      "movl 0x34(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[cb6fc0]\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[cd98c0]\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[cd7780]\n\t"
      "pushl $0x26ece4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x40, %%esp\n\t"
      "popl %%ebx\n\t"
      ".Lplayer_control_update_for_loaded_game_state_7:\n\t"
      "cmpw $4, %%si\n\t"
      "popl %%edi\n\t"
      "jne .Lplayer_control_update_for_loaded_game_state_9\n\t"
      "pushl $0x26ec78\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_control_update_for_loaded_game_state_8:\n\t"
      "movswl %%ax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x26ebd8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lplayer_control_update_for_loaded_game_state_9:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [ce07c0] "m"(bba970_ce07c0), [cba3c0] "m"(bba970_cba3c0), [assert] "m"(bba970_assert), [exitfn] "m"(bba970_exitfn), [dget] "m"(bba970_dget), [cba410] "m"(bba970_cba410), [cb6fc0] "m"(bba970_cb6fc0), [cd98c0] "m"(bba970_cd98c0), [cd7780] "m"(bba970_cd7780), [c8f390] "m"(bba970_c8f390)
      : "memory");
}
#else
#error "player_control_update_for_loaded_game_state: clang naked draft required"
#endif


/* player_add_equipment (0xbb410) — XBE naked draft (batch 125). */
#if defined(__clang__)
static void *(*const bbb410_tryget)(int, int) = object_try_and_get_and_verify_type;
static scenario_t * (*const bbb410_c18e380)(void) = global_scenario_get;
static void *(*const bbb410_elem)(void *, int, int) = tag_block_get_element;
static void (*const bbb410_c1aac80)(int unit_handle) = unit_clear_weapons;
static int (*const bbb410_cbac10)(int tag_index, void *start_loc) = FUN_000bac10;
static bool (*const bbb410_c1b1db0)(int unit_handle, int seat_object_handle, int16_t flag) = unit_enter_seat;
static void (*const bbb410_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const bbb410_odel)(int) = object_delete;

__attribute__((naked, noinline))
void player_add_equipment(int unit_handle __attribute__((unused)), int16_t equipment_index __attribute__((unused)), char reset __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lplayer_add_equipment_7\n\t"
      "pushl %%ebx\n\t"
      "movw 0xc(%%ebp), %%bx\n\t"
      "cmpw $-1, %%bx\n\t"
      "pushl %%esi\n\t"
      "je .Lplayer_add_equipment_6\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[tryget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x1c8(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lplayer_add_equipment_6\n\t"
      "call *%[c18e380]\n\t"
      "movswl %%bx, %%ecx\n\t"
      "pushl $0x68\n\t"
      "pushl %%ecx\n\t"
      "addl $0x348, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_add_equipment_1\n\t"
      "pushl %%edi\n\t"
      "call *%[c1aac80]\n\t"
      "addl $4, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, 0x94(%%esi)\n\t"
      "movl %%eax, 0x90(%%esi)\n\t"
      "movw %%ax, 0x2ce(%%esi)\n\t"
      ".Lplayer_add_equipment_1:\n\t"
      "cmpl $-1, 0x34(%%ebx)\n\t"
      "je .Lplayer_add_equipment_3\n\t"
      "pushl %%edi\n\t"
      "leal 0x28(%%ebx), %%edi\n\t"
      "call *%[cbac10]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lplayer_add_equipment_2\n\t"
      "movb 0x10(%%ebp), %%cl\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "testb %%cl, %%cl\n\t"
      "setne %%dl\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1b1db0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lplayer_add_equipment_2\n\t"
      "pushl $0x26ed88\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "pushl %%edi\n\t"
      "call *%[odel]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lplayer_add_equipment_2:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      ".Lplayer_add_equipment_3:\n\t"
      "cmpl $-1, 0x48(%%ebx)\n\t"
      "je .Lplayer_add_equipment_4\n\t"
      "pushl %%edi\n\t"
      "leal 0x3c(%%ebx), %%edi\n\t"
      "call *%[cbac10]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lplayer_add_equipment_4\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1b1db0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lplayer_add_equipment_4\n\t"
      "pushl $0x26ed88\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "pushl %%edi\n\t"
      "call *%[odel]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lplayer_add_equipment_4:\n\t"
      "flds 0x24(%%ebx)\n\t"
      "addl $0x2ce, %%esi\n\t"
      "fadds -0x23a(%%esi)\n\t"
      "addl $0x50, %%ebx\n\t"
      "movl $2, %%eax\n\t"
      "fstps -0x23a(%%esi)\n\t"
      "flds -0x30(%%ebx)\n\t"
      "fadds -0x23e(%%esi)\n\t"
      "fstps -0x23e(%%esi)\n\t"
      ".Lplayer_add_equipment_5:\n\t"
      "movb (%%ebx), %%dl\n\t"
      "movb (%%esi), %%cl\n\t"
      "addb %%dl, %%cl\n\t"
      "incl %%ebx\n\t"
      "movb %%cl, (%%esi)\n\t"
      "incl %%esi\n\t"
      "decl %%eax\n\t"
      "jne .Lplayer_add_equipment_5\n\t"
      ".Lplayer_add_equipment_6:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".Lplayer_add_equipment_7:\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tryget] "m"(bbb410_tryget), [c18e380] "m"(bbb410_c18e380), [elem] "m"(bbb410_elem), [c1aac80] "m"(bbb410_c1aac80), [cbac10] "m"(bbb410_cbac10), [c1b1db0] "m"(bbb410_c1b1db0), [c8f390] "m"(bbb410_c8f390), [odel] "m"(bbb410_odel)
      : "memory");
}
#else
#error "player_add_equipment: clang naked draft required"
#endif


/* player_handle_powerup (0xbc320) — XBE naked draft (batch 132). */
#if defined(__clang__)
static void *(*const bbc320_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const bbc320_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bbc320_exitfn)(int) = system_exit;
static void *(*const bbc320_get)(int, int) = object_get_and_verify_type;
static bool (*const bbc320_gerun)(void) = game_engine_running;

__attribute__((naked, noinline))
char player_handle_powerup(int player_handle __attribute__((unused)), int16_t powerup_index __attribute__((unused)), int16_t ticks __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movw 0xc(%%ebp), %%si\n\t"
      "addl $8, %%esp\n\t"
      "testw %%si, %%si\n\t"
      "movl %%eax, %%ebx\n\t"
      "jl .Lplayer_handle_powerup_1\n\t"
      "cmpw $2, %%si\n\t"
      "jl .Lplayer_handle_powerup_2\n\t"
      ".Lplayer_handle_powerup_1:\n\t"
      "pushl $1\n\t"
      "pushl $0xaea\n\t"
      "pushl $0x26eb68\n\t"
      "pushl $0x26ee90\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayer_handle_powerup_2:\n\t"
      "testw %%si, %%si\n\t"
      "jne .Lplayer_handle_powerup_3\n\t"
      "movl 0x34(%%ebx), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movb 0x1b4(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $0x10, %%cl\n\t"
      "je .Lplayer_handle_powerup_3\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_handle_powerup_3:\n\t"
      "movswl %%si, %%esi\n\t"
      "cmpw $0, 0x68(%%ebx,%%esi,2)\n\t"
      "jne .Lplayer_handle_powerup_4\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lplayer_handle_powerup_6\n\t"
      "movl 0x1b4(%%eax), %%ecx\n\t"
      "orl $0x10, %%ecx\n\t"
      "movw %%si, 0x3d2(%%eax)\n\t"
      "jmp .Lplayer_handle_powerup_5\n\t"
      ".Lplayer_handle_powerup_4:\n\t"
      "call *%[gerun]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lplayer_handle_powerup_6\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lplayer_handle_powerup_6\n\t"
      "movl 0x1b4(%%eax), %%ecx\n\t"
      "orl $0x20, %%ecx\n\t"
      ".Lplayer_handle_powerup_5:\n\t"
      "movl %%ecx, 0x1b4(%%eax)\n\t"
      ".Lplayer_handle_powerup_6:\n\t"
      "movw 0x10(%%ebp), %%dx\n\t"
      "addw %%dx, 0x68(%%ebx,%%esi,2)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(bbc320_dget), [assert] "m"(bbc320_assert), [exitfn] "m"(bbc320_exitfn), [get] "m"(bbc320_get), [gerun] "m"(bbc320_gerun)
      : "memory");
}
#else
#error "player_handle_powerup: clang naked draft required"
#endif


/* players_debug_render (0xbc520) — XBE naked draft (batch 120). */
#if defined(__clang__)
static __int16 (*const bbc520_cba4c0)(__int16 a1) = local_player_get_next;
static void (*const bbc520_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bbc520_exitfn)(int) = system_exit;
static int (*const bbc520_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void *(*const bbc520_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const bbc520_get)(int, int) = object_get_and_verify_type;
static void (*const bbc520_c1a0890)(int unit_handle, vector3_t *out_pos, float *out_height_offset, float *out_camera_height) = biped_get_camera_height_and_offset;
static char (*const bbc520_c1a1430)(int unit_handle, int seat_handle, float *initial_position, float *final_position, float scale, char keep_basis, char dont_teleport, char scale_by_height) = biped_fix_position;
static void *(*const bbc520_tag)(int, int) = tag_get;
static char (*const bbc520_c14e7d0)(uint32_t collision_flags, float *point, float *offset_vec, float p4, int unit_handle, void *result) = FUN_0014e7d0;
static void (*const bbc520_c189860)(char flag, void *center, void *height_vec, float radius, void *color) = FUN_00189860;

__attribute__((naked, noinline))
void players_debug_render(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x84, %%esp\n\t"
      "movb 0x46b6c4, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayers_debug_render_8\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "call *%[cba4c0]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lplayers_debug_render_1:\n\t"
      "cmpw $-1, %%bx\n\t"
      "je .Lplayers_debug_render_7\n\t"
      "jl .Lplayers_debug_render_2\n\t"
      "cmpw $4, %%bx\n\t"
      "jl .Lplayers_debug_render_3\n\t"
      ".Lplayers_debug_render_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x3ab\n\t"
      "pushl $0x26eb68\n\t"
      "pushl $0x26eb88\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayers_debug_render_3:\n\t"
      "movl 0x5aa6cc, %%ecx\n\t"
      "movswl %%bx, %%eax\n\t"
      "cmpl $-1, 0x4(%%ecx,%%eax,4)\n\t"
      "je .Lplayers_debug_render_6\n\t"
      "pushl %%ebx\n\t"
      "call *%[cba3c0]\n\t"
      "movl 0x5aa6d4, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lplayers_debug_render_6\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1a0890]\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl $0x40000000\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl $-1\n\t"
      "call *%[c1a1430]\n\t"
      "addl $0x38, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayers_debug_render_6\n\t"
      "movl (%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1a0890]\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fadds 0x42c(%%edi)\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "leal -0x84(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x4029\n\t"
      "call *%[c14e7d0]\n\t"
      "addl $0x30, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayers_debug_render_4\n\t"
      "movl 0x2ee6d0, %%ecx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "jmp .Lplayers_debug_render_5\n\t"
      ".Lplayers_debug_render_4:\n\t"
      "movl 0x2ee6d4, %%edx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      ".Lplayers_debug_render_5:\n\t"
      "pushl $0\n\t"
      "call *%[c189860]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayers_debug_render_6:\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "incl %%esi\n\t"
      "pushl %%ebx\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "call *%[cba4c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $2, %%si\n\t"
      "movl %%eax, %%ebx\n\t"
      "jl .Lplayers_debug_render_1\n\t"
      ".Lplayers_debug_render_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".Lplayers_debug_render_8:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cba4c0] "m"(bbc520_cba4c0), [assert] "m"(bbc520_assert), [exitfn] "m"(bbc520_exitfn), [cba3c0] "m"(bbc520_cba3c0), [dget] "m"(bbc520_dget), [get] "m"(bbc520_get), [c1a0890] "m"(bbc520_c1a0890), [c1a1430] "m"(bbc520_c1a1430), [tag] "m"(bbc520_tag), [c14e7d0] "m"(bbc520_c14e7d0), [c189860] "m"(bbc520_c189860)
      : "memory");
}
#else
#error "players_debug_render: clang naked draft required"
#endif


/* players_update_before_game_client (0xbc920) — XBE naked draft (batch 125). */
#if defined(__clang__)
static void *(*const bbc920_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const bbc920_tryget)(int, int) = object_try_and_get_and_verify_type;
static void (*const bbc920_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bbc920_exitfn)(int) = system_exit;
static scenario_t * (*const bbc920_c18e380)(void) = global_scenario_get;
static void *(*const bbc920_elem)(void *, int, int) = tag_block_get_element;
static char (*const bbc920_c18ef00)(int cluster_index, int object_handle) = FUN_0018ef00;
static int (*const bbc920_c18e720)(int point) = FUN_0018e720;
static void *(*const bbc920_get)(int, int) = object_get_and_verify_type;
static void (*const bbc920_c1b2dd0)(int unit_handle) = unit_exit_seat_end;
static char (*const bbc920_cbb670)(int player_handle, void *a, void *b) = FUN_000bb670;

__attribute__((naked, noinline))
void players_update_before_game_client(int player_handle __attribute__((unused)), int anchor_unit __attribute__((unused)), float *position __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[tryget]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "movl %%eax, %%esi\n\t"
      "jne .Lplayers_update_before_game_client_1\n\t"
      "pushl $1\n\t"
      "pushl $0x4c7\n\t"
      "pushl $0x26eb68\n\t"
      "pushl $0x26c18c\n\t"
      "call *%[assert]\n\t"
      "pushl %%ebx\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayers_update_before_game_client_1:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lplayers_update_before_game_client_2\n\t"
      "pushl $1\n\t"
      "pushl $0x4c8\n\t"
      "pushl $0x26eb68\n\t"
      "pushl $0x267114\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayers_update_before_game_client_2:\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lplayers_update_before_game_client_9\n\t"
      "movl 0x5aa6cc, %%ecx\n\t"
      "movw 0x2a(%%ecx), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lplayers_update_before_game_client_3\n\t"
      "movswl %%ax, %%edx\n\t"
      "pushl $8\n\t"
      "pushl %%edx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x39c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl (%%eax), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c18ef00]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "je .Lplayers_update_before_game_client_4\n\t"
      ".Lplayers_update_before_game_client_3:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".Lplayers_update_before_game_client_4:\n\t"
      "leal 0x50(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18e720]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lplayers_update_before_game_client_5\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayers_update_before_game_client_9\n\t"
      ".Lplayers_update_before_game_client_5:\n\t"
      "cmpl $-1, 0xcc(%%esi)\n\t"
      "je .Lplayers_update_before_game_client_7\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "movl 0xcc(%%esi), %%ecx\n\t"
      "movl 0xcc(%%eax), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "je .Lplayers_update_before_game_client_6\n\t"
      "pushl %%edi\n\t"
      "call *%[c1b2dd0]\n\t"
      "addl $4, %%esp\n\t"
      ".Lplayers_update_before_game_client_6:\n\t"
      "cmpl $-1, 0xcc(%%esi)\n\t"
      "jne .Lplayers_update_before_game_client_8\n\t"
      ".Lplayers_update_before_game_client_7:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[cbb670]\n\t"
      "movl 0x5aa6cc, %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "sete %%cl\n\t"
      "popl %%edi\n\t"
      "movb %%cl, 0x2e(%%edx)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayers_update_before_game_client_8:\n\t"
      "movl 0x5aa6cc, %%edx\n\t"
      "movb $1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "sete %%cl\n\t"
      "movb %%cl, 0x2e(%%edx)\n\t"
      ".Lplayers_update_before_game_client_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(bbc920_dget), [tryget] "m"(bbc920_tryget), [assert] "m"(bbc920_assert), [exitfn] "m"(bbc920_exitfn), [c18e380] "m"(bbc920_c18e380), [elem] "m"(bbc920_elem), [c18ef00] "m"(bbc920_c18ef00), [c18e720] "m"(bbc920_c18e720), [get] "m"(bbc920_get), [c1b2dd0] "m"(bbc920_c1b2dd0), [cbb670] "m"(bbc920_cbb670)
      : "memory");
}
#else
#error "players_update_before_game_client: clang naked draft required"
#endif


/* players_reconnect_to_structure_bsp (0xbca60) — XBE naked draft (batch 111). */
#if defined(__clang__)
static scenario_t * (*const bbca60_c18e380)(void) = global_scenario_get;
static void *(*const bbca60_elem)(void *, int, int) = tag_block_get_element;
static char (*const bbca60_c4dc30)(int, float *, int) = FUN_0014dc30;
static void (*const bbca60_c1197b0)(data_iter_t *iter, data_t *data) = data_iterator_new;
static void * (*const bbca60_c119810)(data_iter_t *iterator) = data_iterator_next;
static char (*const bbca60_c18ef00)(int cluster_index, int object_handle) = FUN_0018ef00;
static void (*const bbca60_c1a0890)(int unit_handle, vector3_t *out_pos, float *out_height_offset, float *out_camera_height) = biped_get_camera_height_and_offset;
static int (*const bbca60_c18e720)(int point) = FUN_0018e720;
static void * (*const bbca60_c18e3c0)(void) = scenario_get;
static void (*const bbca60_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bbca60_exitfn)(int) = system_exit;
static __int16 (*const bbca60_cba4c0)(__int16 a1) = local_player_get_next;
static int (*const bbca60_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void *(*const bbca60_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const bbca60_cbc920)(int player_handle, int anchor_unit, float *position) = players_update_before_game_client;

__attribute__((naked, noinline))
void players_reconnect_to_structure_bsp(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x38, %%esp\n\t"
      "movl 0x5aa6cc, %%eax\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "cmpw %%di, 0x2a(%%eax)\n\t"
      "je .Lplayers_reconnect_to_structure_bsp_13\n\t"
      "cmpw $1, 0x24(%%eax)\n\t"
      "jle .Lplayers_reconnect_to_structure_bsp_13\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c18e380]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x5aa6cc, %%eax\n\t"
      "movswl 0x2a(%%eax), %%ecx\n\t"
      "pushl $8\n\t"
      "pushl %%ecx\n\t"
      "leal 0x39c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movw 0x6(%%eax), %%ax\n\t"
      "xorb %%bl, %%bl\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw %%di, %%ax\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "je .Lplayers_reconnect_to_structure_bsp_3\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl $0x5c\n\t"
      "pushl %%eax\n\t"
      "addl $0x4e4, %%esi\n\t"
      "pushl %%esi\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $0x24, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lplayers_reconnect_to_structure_bsp_1:\n\t"
      "pushl %%edi\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x4029\n\t"
      "call *%[c4dc30]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayers_reconnect_to_structure_bsp_2\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fadds 0x2533e8\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fadds 0x2533e8\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fcomps 0x2533e4\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lplayers_reconnect_to_structure_bsp_1\n\t"
      ".Lplayers_reconnect_to_structure_bsp_2:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "fcomps 0x2533e4\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lplayers_reconnect_to_structure_bsp_3\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".Lplayers_reconnect_to_structure_bsp_3:\n\t"
      "movl 0x5aa6d4, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1197b0]\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c119810]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lplayers_reconnect_to_structure_bsp_8\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lplayers_reconnect_to_structure_bsp_4:\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lplayers_reconnect_to_structure_bsp_9\n\t"
      "movl 0x34(%%edi), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lplayers_reconnect_to_structure_bsp_7\n\t"
      "movl 0x5aa6cc, %%edx\n\t"
      "movw 0x2a(%%edx), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lplayers_reconnect_to_structure_bsp_7\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl $8\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x39c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%eax), %%cx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18ef00]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayers_reconnect_to_structure_bsp_7\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x34(%%edi), %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1a0890]\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e720]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lplayers_reconnect_to_structure_bsp_7\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl $0x10\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18e720]\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e3c0]\n\t"
      "addl $0xe0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl 0x8(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lplayers_reconnect_to_structure_bsp_7\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lplayers_reconnect_to_structure_bsp_5\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "jmp .Lplayers_reconnect_to_structure_bsp_6\n\t"
      ".Lplayers_reconnect_to_structure_bsp_5:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      ".Lplayers_reconnect_to_structure_bsp_6:\n\t"
      "movl 0x34(%%edi), %%edx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movb $1, %%bl\n\t"
      ".Lplayers_reconnect_to_structure_bsp_7:\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119810]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lplayers_reconnect_to_structure_bsp_4\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lplayers_reconnect_to_structure_bsp_9\n\t"
      ".Lplayers_reconnect_to_structure_bsp_8:\n\t"
      "pushl $1\n\t"
      "pushl $0x63a\n\t"
      "pushl $0x26eb68\n\t"
      "pushl $0x26eecc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lplayers_reconnect_to_structure_bsp_12\n\t"
      ".Lplayers_reconnect_to_structure_bsp_9:\n\t"
      "pushl $-1\n\t"
      "call *%[cba4c0]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpw $-1, %%si\n\t"
      "je .Lplayers_reconnect_to_structure_bsp_12\n\t"
      ".Lplayers_reconnect_to_structure_bsp_10:\n\t"
      "pushl %%esi\n\t"
      "call *%[cba3c0]\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lplayers_reconnect_to_structure_bsp_11\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .Lplayers_reconnect_to_structure_bsp_11\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cbc920]\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $0x10, %%esp\n\t"
      "movw $0xffff, 0x3c(%%eax)\n\t"
      ".Lplayers_reconnect_to_structure_bsp_11:\n\t"
      "pushl %%esi\n\t"
      "call *%[cba4c0]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpw $-1, %%si\n\t"
      "jne .Lplayers_reconnect_to_structure_bsp_10\n\t"
      ".Lplayers_reconnect_to_structure_bsp_12:\n\t"
      "movl 0x5aa6cc, %%ecx\n\t"
      "popl %%esi\n\t"
      "movw $0xffff, 0x2a(%%ecx)\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "popl %%ebx\n\t"
      ".Lplayers_reconnect_to_structure_bsp_13:\n\t"
      "movl 0x5aa6d4, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1197b0]\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c119810]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lplayers_reconnect_to_structure_bsp_15\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lplayers_reconnect_to_structure_bsp_14:\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movw %%di, 0x3c(%%eax)\n\t"
      "call *%[c119810]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lplayers_reconnect_to_structure_bsp_14\n\t"
      ".Lplayers_reconnect_to_structure_bsp_15:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(bbca60_c18e380), [elem] "m"(bbca60_elem), [c4dc30] "m"(bbca60_c4dc30), [c1197b0] "m"(bbca60_c1197b0), [c119810] "m"(bbca60_c119810), [c18ef00] "m"(bbca60_c18ef00), [c1a0890] "m"(bbca60_c1a0890), [c18e720] "m"(bbca60_c18e720), [c18e3c0] "m"(bbca60_c18e3c0), [assert] "m"(bbca60_assert), [exitfn] "m"(bbca60_exitfn), [cba4c0] "m"(bbca60_cba4c0), [cba3c0] "m"(bbca60_cba3c0), [dget] "m"(bbca60_dget), [cbc920] "m"(bbca60_cbc920)
      : "memory");
}
#else
#error "players_reconnect_to_structure_bsp: clang naked draft required"
#endif


void FUN_000c0b70(int16_t function_index, int thread_datum, char init)
{
  char *args;

  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00057850(*(unsigned int *)(args + 0), (char)args[4]);
    hs_return(thread_datum, 0);
  }
}

void FUN_000bdf80(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  hs_return(thread_datum, FUN_000c95f0());
}

void FUN_000be250(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  FUN_000c9a50();
  hs_return(thread_datum, 0);
}

void FUN_000bdf40(int16_t function_index, int thread_datum, char init)
{
  int *args;

  args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000c95d0((const char *)args[0]);
    hs_return(thread_datum, 0);
  }
}

void FUN_000bdfa0(int16_t function_index, int thread_datum, char init)
{
  int16_t *args;

  args = (int16_t *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000ca430((int)args[0], (int)(uint16_t)args[2]);
    hs_return(thread_datum, 0);
  }
}

void FUN_000be0d0(int16_t function_index, int thread_datum, char init)
{
  uint16_t *args;

  args = (uint16_t *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000c9990(args[0]);
    hs_return(thread_datum, 0);
  }
}

void FUN_000be110(int16_t function_index, int thread_datum, char init)
{
  int *args;

  args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000c99e0(args[0]);
    hs_return(thread_datum, 0);
  }
}

void FUN_000be150(int16_t function_index, int thread_datum, char init)
{
  uint16_t *args;

  args = (uint16_t *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000ca110(args[0]);
    hs_return(thread_datum, 0);
  }
}

void FUN_000be190(int16_t function_index, int thread_datum, char init)
{
  int *args;

  args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000c9b90((const char *)args[0]);
    hs_return(thread_datum, 0);
  }
}

void FUN_000be1d0(int16_t function_index, int thread_datum, char init)
{
  int *args;

  args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000ca140((const char *)args[0]);
    hs_return(thread_datum, 0);
  }
}

void FUN_000be210(int16_t function_index, int thread_datum, char init)
{
  int *args;

  args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000c9bb0((const char *)args[0]);
    hs_return(thread_datum, 0);
  }
}

void FUN_000bdef0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_000c95c0(*(int *)(args + 0)));
  }
}

void FUN_000be3b0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_000ce420(*(int *)(args + 0)));
  }
}

void FUN_000be5a0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000c9d80(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000be620(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_000ca010(*(int *)(args + 0)));
  }
}

void FUN_000be6a0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, numeric_countdown_timer_get((int)*(uint16_t *)(args + 0)));
  }
}

void FUN_000be730(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    breakable_surfaces_enable(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000be860(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    recorded_animation_kill(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000be8a0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, recorded_animation_get_time_left(*(int *)(args + 0)));
  }
}

void FUN_000beab0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    object_get_maximum_body_vitality(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000beaf0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    object_can_take_damage(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000beb70(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000c9d40(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bebb0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    object_definition_predict(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bebf0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_0013dbe0(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bec30(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_0013dc10((int)*(uint16_t *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bec90(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    object_pvs_activate(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000becd0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, lights_enable(*(int *)(args + 0)));
  }
}

void FUN_000bed20(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_00145740(*(int *)(args + 0)));
  }
}

void FUN_000bee00(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    render_effects(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bee80(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    unit_open(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000beec0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    unit_close(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bef00(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    unit_set_actively_controlled_flag(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bef40(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    unit_kill(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bef80(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_001AC0E0(*(int *)(args + 0)));
  }
}

void FUN_000befd0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    unit_stop_custom_animation(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bf110(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_001ac150(*(int *)(args + 0)));
  }
}

void FUN_000bf340(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_001b5500(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bf380(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_001a7a90(*(int *)args, *(float *)(args + 4), *(float *)(args + 8));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bf3d0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_001a7ad0(*(int *)args, *(int *)(args + 4), *(int *)(args + 8));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bf420(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_001a7b50(*(int *)args, *(float *)(args + 4), *(float *)(args + 8));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bf470(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_001a7c70(*(int *)args, *(int *)(args + 4), *(int *)(args + 8));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bf560(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    scripting_set_magic_base_seat(*(const char **)args);
    hs_return(thread_datum, 0);
  }
}

void FUN_000bf600(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, unit_scripting_unit_riders(*(int *)(args + 0)));
  }
}

void FUN_000bf640(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_001a9ec0(*(int *)(args + 0)));
  }
}

void FUN_000bf680(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_001a9ef0(*(int *)(args + 0)));
  }
}

void FUN_000bf6c0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_001a7cc0(*(int *)(args + 0)));
  }
}

void FUN_000bf700(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_001a7d00(*(int *)(args + 0)));
  }
}

void FUN_000bf740(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_001a7d40(*(int *)(args + 0)));
  }
}

void FUN_000bf830(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    unit_scripting_doesnt_drop_items(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bf9a0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, unit_get_current_flashlight_state(*(int *)(args + 0)));
  }
}

void FUN_000bfa70(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, device_get_power(*(int *)(args + 0)));
  }
}

void FUN_000bfb00(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, device_get_position(*(int *)(args + 0)));
  }
}

void FUN_000bfb80(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, device_group_get_value((int)*(uint16_t *)(args + 0)));
  }
}

void FUN_000bfdd0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    cheat_active_camouflage_local_player((int)*(uint16_t *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bfe30(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    ai_globals_ai_active(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bfe70(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    ai_globals_dialogue_triggers_enabled(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bfeb0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    ai_globals_grenades_enabled(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bfef0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000575d0(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bff30(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000576a0(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0030(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00054ac0(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0070(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00054b20(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c00b0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00054bb0(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c00f0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00054ca0(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0130(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00054d00(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0170(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00054d60(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c01d0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00054e40(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0230(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00054e80(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0370(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00058a40(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0430(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00055220(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0470(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000552b0(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c04b0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00055750(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c04f0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000557e0(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0530(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00058ae0(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0570(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00055870(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c07b0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000568e0(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c08f0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056de0(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0930(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056d80(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0970(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00058d40(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c09b0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056e40(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0a30(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056fa0(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0af0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00057230(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0b30(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000572c0(*(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000be6f0(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  numeric_countdown_timer_stop();
  hs_return(thread_datum, 0);
}

void FUN_000be710(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  numeric_countdown_timer_restart();
  hs_return(thread_datum, 0);
}

void FUN_000be970(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  objects_dump_memory();
  hs_return(thread_datum, 0);
}

void FUN_000bea90(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  garbage_collect_now();
  hs_return(thread_datum, 0);
}

void FUN_000bec70(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  FUN_0013dcb0();
  hs_return(thread_datum, 0);
}

void FUN_000bf5e0(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  scripting_magic_melee_attack();
  hs_return(thread_datum, 0);
}

void FUN_000bf8f0(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  hs_return(thread_datum, unit_solo_player_integrated_night_vision_is_active());
}

void FUN_000bfd10(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  breakable_surfaces_reset();
  hs_return(thread_datum, 0);
}

void FUN_000bfd30(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  FUN_000a6b50();
  hs_return(thread_datum, 0);
}

void FUN_000bfd50(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  FUN_000a6a80();
  hs_return(thread_datum, 0);
}

void FUN_000bfd70(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  FUN_000a6ba0();
  hs_return(thread_datum, 0);
}

void FUN_000bfd90(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  cheat_teleport_to_camera();
  hs_return(thread_datum, 0);
}

void FUN_000bfdb0(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  cheat_all_powerups();
  hs_return(thread_datum, 0);
}

void FUN_000bfe10(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  cheats_load_from_file();
  hs_return(thread_datum, 0);
}

void FUN_000c01b0(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  FUN_00054df0();
  hs_return(thread_datum, 0);
}

void FUN_000c0210(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  FUN_00054e20();
  hs_return(thread_datum, 0);
}

void FUN_000bdfe0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_0018ef00(*(int *)(args + 4), (int)*(int16_t *)(args + 0)));
  }
}

void FUN_000be030(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_000ca0f0(*(int *)(args + 4), (int)*(int16_t *)(args + 0)));
  }
}

void FUN_000be080(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_000ca050(*(int *)(args + 4), (int)*(int16_t *)(args + 0)));
  }
}

void FUN_000be270(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000ca3f0((int)*(uint16_t *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000be2b0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000ca410((int)*(uint16_t *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000be330(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000c9c80(*(int *)(args + 8), *(int *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000be370(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_000c9bd0((int)*(uint16_t *)(args + 4), *(int *)(args + 0)));
  }
}

void player_rumble_initialize(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000c9de0((int)*(uint16_t *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000be440(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000c9e50(*(int *)(args + 8), *(int *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000be480(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000c9ec0((int)*(uint16_t *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000be4c0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000c9f30(*(int *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void player_rumble_set_effect(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, recorded_animation_play((int)*(uint16_t *)(args + 4), *(int *)(args + 0)));
  }
}

void FUN_000be7c0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, recorded_animation_play_and_delete((int)*(uint16_t *)(args + 4), *(int *)(args + 0)));
  }
}

void FUN_000be810(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_00095680((int)*(uint16_t *)(args + 4), *(int *)(args + 0)));
  }
}

void FUN_000bea50(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    objects_scripting_detach(*(int *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bed70(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_001457b0(*(int *)(args + 8), *(int *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bf1a0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_001ac070((int)*(uint16_t *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bf220(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    unit_scripting_enter_vehicle(*(int *)(args + 8), *(int *)(args + 4),
                                 *(char **)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bf260(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum,
              FUN_001a9c90(*(int *)(args + 8), *(const char **)(args + 4),
                           *(int *)(args + 0)));
  }
}

void FUN_000bf2b0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum,
              unit_scripting_vehicle_test_seat(
                  *(int *)(args + 8), *(const char **)(args + 4),
                  *(int *)(args + 0)));
  }
}

void FUN_000bf300(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    unit_scripting_set_emotion_animation(*(int *)(args + 4),
                                         *(const char **)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bf4c0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, vehicle_scripting_load_magic(*(int *)(args + 8), *(int *)(args + 4), *(int *)(args + 0)));
  }
}

void FUN_000bf510(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_001b5400(*(int *)(args + 4), *(int *)(args + 0)));
  }
}

void FUN_000bf5a0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    unit_scripting_set_seat(*(int *)(args + 4), *(const char **)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bf790(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_001a7e70(*(int *)(args + 4), *(int *)(args + 0)));
  }
}

void FUN_000bf7e0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_001a7ea0(*(int *)(args + 4), *(int *)(args + 0)));
  }
}

void FUN_000bff70(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00054860(*(int *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bffb0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    ai_profile_change_render_spray(*(int *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bfff0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00057770(*(int *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0330(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00058970(*(int *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c03b0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00055110(*(int *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c03f0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000551e0(*(int *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c05f0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056320(*(int *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0630(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000565c0(*(int *)(args + 8), *(int *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0670(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000564b0(*(int *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c06b0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    encounters_initialize((int)*(uint16_t *)(args + 4), (int)*(int16_t *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c06f0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056790((int)*(uint16_t *)(args + 4), (int)*(int16_t *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0730(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00058c40(*(int *)(args + 8), *(int *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0770(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    ai_scripting_follow_distance(*(int *)(args + 8), *(int *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c09f0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056ed0(*(int *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0a70(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000570d0((int)*(uint16_t *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0ab0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00057190((int)*(uint16_t *)(args + 4), *(int *)(args + 0));
    hs_return(thread_datum, 0);
  }
}

void FUN_000be2f0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000c9c10(*(int *)(args + 0), *(float *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000be500(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_000c9770(*(int *)(args + 0), *(int *)(args + 4), *(float *)(args + 8)));
  }
}

void FUN_000be550(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_000c9840(*(int *)(args + 0), (int)*(uint16_t *)(args + 4), *(float *)(args + 8)));
  }
}

void FUN_000be5e0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000ca030(*(int *)(args + 0), *(float *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000be660(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    numeric_countdown_timer_set(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000be8f0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    object_set_ranged_attack_inhibited(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000be930(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    object_set_melee_attack_inhibited(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000be990(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    object_scripting_set_collideable(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000be9d0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    objects_scripting_set_scale(*(int *)(args + 0), *(float *)(args + 4), (int)*(uint16_t *)(args + 8));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bea10(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    objects_scripting_attach(*(int *)(args + 0), *(int *)(args + 4), *(int *)(args + 8), *(int *)(args + 12));
    hs_return(thread_datum, 0);
  }
}

void FUN_000beb30(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    object_beautify(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bedb0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_001457d0(*(int *)(args + 0), *(int *)(args + 4), *(int *)(args + 8), (int)*(uint16_t *)(args + 12));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bee40(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    unit_scripting_can_blink(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bf010(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum,
              FUN_001ac180(*(int *)(args + 0), *(int *)(args + 4),
                           (void *)*(int *)(args + 8),
                           (int)*(uint8_t *)(args + 12)));
  }
}

void FUN_000bf060(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_001a7df0(*(int *)(args + 0), *(int *)(args + 4), *(int *)(args + 8), (int)*(uint8_t *)(args + 12)));
  }
}

void FUN_000bf0b0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, unit_custom_animation_at_frame(*(int *)(args + 0), *(int *)(args + 4), *(int *)(args + 8), (int)*(uint8_t *)(args + 12), (int)*(uint16_t *)(args + 16)));
  }
}

void FUN_000bf160(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_001ac0a0(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bf1e0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_001ac030(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bf870(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_001a7d80(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bf8b0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    unit_scripting_suspended(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bf920(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    units_set_desired_flashlight_state(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bf960(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    unit_set_desired_flashlight_state(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bf9f0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    device_set_never_appears_locked(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bfa30(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00097260(*(int *)(args + 0), *(float *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bfab0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_00097220(*(int *)(args + 0), *(float *)(args + 4)));
  }
}

void FUN_000bfb40(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00097040(*(int *)(args + 0), *(float *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bfbc0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, FUN_00096f20((int)*(uint16_t *)(args + 0), *(float *)(args + 4)));
  }
}

void FUN_000bfc10(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    device_group_set_actual_value((int)*(uint16_t *)(args + 0), *(float *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bfc50(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    device_one_sided_set(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bfc90(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    device_operates_automatically_set(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000bfcd0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    device_group_change_only_once_more_set((int)*(int16_t *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0270(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00054f90(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c02b0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00055010(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c02f0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00055090(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c05b0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00055900(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c07f0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056980(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0830(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056a20(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c0870(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056b20(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}

void FUN_000c08b0(int16_t function_index, int thread_datum, char init)
{
  char *args;
  args = (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056bc0(*(int *)(args + 0), (int)*(uint8_t *)(args + 4));
    hs_return(thread_datum, 0);
  }
}
/* --- players.obj orphan shells (2026-07-26) --- */

/* FUN_000bae20 (0xbae20) — XBE naked draft (batch 143). */
#if defined(__clang__)
static void *(*const bbae20_tryget)(int, int) = object_try_and_get_and_verify_type;
static void *(*const bbae20_tag)(int, int) = tag_get;
static int16_t (*const bbae20_c1aad90)(int unit_handle) = unit_count_weapons;
static bool (*const bbae20_c1aae00)(int unit_handle, int weapon_unit_handle) = unit_weapon_is_new;
static bool (*const bbae20_gerun)(void) = game_engine_running;
static bool (*const bbae20_caba00)(int player_unit_handle, int weapon_unit_handle) = game_engine_can_pick_up_weapon;

__attribute__((naked, noinline))
bool FUN_000bae20(int player_unit_handle __attribute__((unused)), int nearby_unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $4\n\t"
      "pushl %%esi\n\t"
      "call *%[tryget]\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x77656170\n\t"
      "call *%[tag]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[c1aad90]\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movswl %%ax, %%ebx\n\t"
      "call *%[c1aae00]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000bae20_1\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "testb $0x10, 0x308(%%ecx)\n\t"
      "jne .LFUN_000bae20_3\n\t"
      ".LFUN_000bae20_1:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_000bae20_3\n\t"
      "call *%[gerun]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000bae20_2\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1aae00]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000bae20_2\n\t"
      "cmpl $2, %%ebx\n\t"
      "jl .LFUN_000bae20_3\n\t"
      ".LFUN_000bae20_2:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[caba00]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000bae20_3\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000bae20_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tryget] "m"(bbae20_tryget), [tag] "m"(bbae20_tag), [c1aad90] "m"(bbae20_c1aad90), [c1aae00] "m"(bbae20_c1aae00), [gerun] "m"(bbae20_gerun), [caba00] "m"(bbae20_caba00)
      : "memory");
}
#else
#error "FUN_000bae20: clang naked draft required"
#endif

