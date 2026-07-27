#include <stdint.h>
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
void players_update_pvs(void *combined_pvs , bool local_player_only)
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

/* player_examine_nearby_unit (0xbae10) — XBE is a single `ret` stub.
 * Prior C body was wrong (full pickup logic). Match the prototype stub. */
bool player_examine_nearby_unit(int player_unit_handle, int nearby_unit_handle)
{
  (void)player_unit_handle;
  (void)nearby_unit_handle;
  return false;
}


/* Clear the action-result fields on a player datum.
 *
 * player_handle is passed in EAX (register argument).
 * Writes 0 to player+0x28 (action result type, word) and
 * NONE (-1) to player+0x24 (action result object, dword). */
void player_reset_action_result(int player_handle )
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
bool player_try_to_enter_vehicle(int player_handle )
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
bool player_try_to_spawn_in_vehicle(int player_handle )
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

/* valid_real_vector2d (0xbb2b0) — readable C lift. */
char valid_real_vector2d(float *v)
{
  unsigned int x = *(unsigned int *)v;
  unsigned int y = *(unsigned int *)(v + 1);
  if ((x & 0x7f800000u) == 0x7f800000u) return 0;
  if ((y & 0x7f800000u) == 0x7f800000u) return 0;
  return 1;
}

/* FUN_000BB290 (0xbb290) — readable C lift. */
void FUN_000BB290(float *out_direction)
{
  random_seed_get_direction3d(get_global_random_seed_address(), out_direction);
}

/* Look up an 8-byte record by `index` in the scenario tag_block at offset 0x39C
 * and test it against `object_handle` via FUN_0018ef00.
 *
 * index (AX)     -- element index into the tag_block (8-byte records); the
 *                   sentinel -1 short-circuits to 0 (false).
 * object_handle  -- forwarded unchanged as FUN_0018ef00's second argument.
 *
 * The record's first 16-bit field (record[0], zero-extended) is passed as
 * FUN_0018ef00's first argument. Returns a normalized bool: 1 when index is
 * valid and FUN_0018ef00 returns nonzero, otherwise 0. */
char FUN_000ba850(int16_t index , int object_handle)
{
  void *scenario;
  unsigned short *element;

  if (index != -1) {
    scenario = global_scenario_get();
    element = (unsigned short *)tag_block_get_element((char *)scenario + 0x39c,
                                                      (int)index, 8);
    if (FUN_0018ef00((int)*element, object_handle) != 0)
      return 1;
  }
  return 0;
}


/* Mark the player's unit with the camo-active flag.
 *
 * player_handle (@eax) -- player datum handle.
 * powerup_index         -- powerup slot; only index 0 is acted on, mirroring
 *                          the powerup_idx==0 branch of
 * player_set_respawn_timer.
 *
 * Looks up the player datum, fetches its unit object handle (player+0x34) and
 * verifies it is a unit (object type mask 3, biped/vehicle family).  When
 * powerup_index is 0, sets bit 0x10 in the unit flags at +0x1b4 (the
 * camo-active flag, per player_set_respawn_timer) and clears the powerup-type
 * field at unit+0x3d2.  object_get_and_verify_type is called unconditionally,
 * before the branch, matching the original. */
void FUN_000bb180(int player_handle ,
                               int16_t powerup_index)
{
  char *player;
  char *unit_obj;

  player = (char *)datum_get(player_data, player_handle);
  unit_obj = (char *)object_get_and_verify_type(*(int *)(player + 0x34), 3);
  if (powerup_index == 0) {
    *(unsigned int *)(unit_obj + 0x1b4) |= 0x10;
    *(int16_t *)(unit_obj + 0x3d2) = 0;
  }
}


/* Set a unit object flag bit (0x20) at unit+0x1b4 for a player's unit.
 *
 * Sibling of player_set_unit_camo_flag (0xbb180); another powerup branch of
 * player_set_respawn_timer.  Looks up the player datum, fetches its unit
 * object handle (player+0x34) and verifies it is a unit (object type mask 3,
 * biped/vehicle family).  When param2 is 0, ORs bit 0x20 into the unit flags
 * at +0x1b4.  object_get_and_verify_type is called unconditionally, before the
 * branch, matching the original. */
void FUN_000bb1c0(int player_index , int16_t param2)
{
  char *player;
  char *unit_obj;

  player = (char *)datum_get(player_data, player_index);
  unit_obj = (char *)object_get_and_verify_type(*(int *)(player + 0x34), 3);
  if (param2 == 0) {
    *(unsigned int *)(unit_obj + 0x1b4) |= 0x20;
  }
}


/* Sibling of FUN_000bb1c0 (0xbb1c0); another powerup branch of
 * player_set_respawn_timer.  Looks up the player datum, fetches its unit
 * object handle (player+0x34) and verifies it is a unit (object type mask 3,
 * biped/vehicle family).  object_get_and_verify_type is called
 * unconditionally, before the branch, matching the original.  When param2 is
 * 0, clears bit 0x10 of the unit flags dword at +0x1b4. */
void FUN_000bb1f0(int player_index , int16_t param2)
{
  char *player;
  char *unit_obj;

  player = (char *)datum_get(player_data, player_index);
  unit_obj = (char *)object_get_and_verify_type(*(int *)(player + 0x34), 3);
  if (param2 == 0) {
    *(unsigned int *)(unit_obj + 0x1b4) &= 0xffffffef;
  }
}


/* player_get_starting_location_count (0xbaa90) — readable C lift. */
int16_t player_get_starting_location_count(void)
{
  scenario_t *scen = global_scenario_get();
  int16_t fallback = *(int16_t *)((char *)scen + 0x354);
  int idx = *(int *)0x5ac9f4;
  void *el;
  int count;
  if (idx == -1)
    return fallback;
  el = tag_block_get_element((char *)scen + 0x42c, idx & 0xffff, 0xb0);
  count = *(int *)((char *)el + 0xa4);
  if (count <= 0)
    return fallback;
  return (int16_t)count;
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

/* placement_data_set_change_color (0xbaba0) — readable C lift. */
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
/* players_handle_deleted_object (0xbb220) — readable C lift. */
void players_handle_deleted_object(int object_handle)
{
  void *obj;
  unsigned char type_bits;
  unsigned int mask;
  data_iter_t iter;
  void *player;

  obj = object_get_and_verify_type(object_handle, -1);
  type_bits = *(unsigned char *)((char *)obj + 0x64);
  mask = 1u << type_bits;
  if ((mask & 3) == 0)
    return;
  data_iterator_new(&iter, *(data_t **)0x5aa6d4);
  for (player = data_iterator_next(&iter); player != 0; player = data_iterator_next(&iter)) {
    if (*(int *)((char *)player + 0x34) == object_handle)
      player_died(*(int *)((char *)&iter + 8));
  }
}

/* players_set_local_player_unit (0xba5f0) — readable C lift. */
void players_set_local_player_unit(int16_t local_player_index, int unit_handle)
{
  int old_unit;
  char *unit;
  char *player;
  int player_index;

  old_unit = player_control_get_unit_index(local_player_index);
  if (game_connection() != 0) {
    display_assert((const char *)0x26ea18, (const char *)0x26eb68, 0x420, true);
    system_exit(-1);
  }
  if (old_unit != -1) {
    unit = (char *)object_get_and_verify_type(old_unit, 3);
    *(int *)(unit + 0x1c8) = -1;
    unit_set_actively_controlled(old_unit, 0);
  }
  if (unit_handle != -1) {
    unit = (char *)object_get_and_verify_type(unit_handle, 3);
    unit_set_actively_controlled(unit_handle, 1);
    *(int *)(unit + 0x1c8) = local_player_get_player_index(local_player_index);
  }
  player_index = local_player_get_player_index(local_player_index);
  player = (char *)datum_get(*(data_t **)0x5aa6d4, player_index);
  *(int *)(player + 0x34) = unit_handle;
  *(int *)(player + 0x38) = -1;
  player_control_new_unit(local_player_index, unit_handle);
}

/* 0xbbbe0 — Choose the best-scoring starting location for a player.
 *
 * Scores every starting location as pow(random[0,1], 0.5) * rating and
 * returns the index of the highest-scoring one.  The random weighting
 * jitters the pick so respawns are not perfectly deterministic.
 *
 * The location count comes from scenario+0x354, unless the campaign
 * encounter selector (DAT 0x5ac9f4) is active, in which case it is
 * overridden by the selected encounter block element's +0xa4 field
 * (stride 0xb0, block at scenario+0x42c) when that value is positive.
 *
 * Returns the best index (sign-extended 16-bit, MOVSX in the original),
 * or -1 when there are no locations (count < 1) or none scores above 0.
 *
 * Confirmed: cdecl, one stack arg (player_index in EDI at [EBP+8]);
 *   score = pow(random, 0.5) * rating (FLD double[0x25fea8]=0.5, __CIpow);
 *   strict > update on best (FCOM/FNSTSW/TEST AH,0x41/JNZ).
 * Uncertain: param semantics (player/team index fed to the rating fn);
 *   0xbaae0 (player_get_starting_location) returns a starting-location
 *   pointer used here as an opaque handle passed to the rating fn. */
int find_best_starting_location_index(int player_index)
{
  char *scenario;
  char *elem;
  int16_t count;
  int best_index;
  float best_score;
  float rating;
  double score;
  int loc;
  int i;

  scenario = (char *)global_scenario_get();
  count = *(int16_t *)(scenario + 0x354);
  if (*(int *)0x5ac9f4 != NONE) {
    elem = (char *)tag_block_get_element(scenario + 0x42c,
                                         *(int *)0x5ac9f4 & 0xffff, 0xb0);
    if (*(int *)(elem + 0xa4) > 0) {
      count = (int16_t) * (int *)(elem + 0xa4);
    }
  }

  best_index = -1;
  best_score = 0.0f;
  if (count >= 1) {
    i = 0;
    do {
      loc = (int)player_get_starting_location(i);
      rating = game_engine_get_starting_location_rating(player_index, loc);
      score =
        pow(random_real_range(get_global_random_seed_address(), 0.0f, 1.0f),
            *(double *)0x25fea8) *
        rating;
      if (best_score < score) {
        best_score = (float)score;
        best_index = i;
      }
      i++;
    } while (i < count);
  }

  return (int16_t)best_index;
}


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


/* player_teleport (0xbbb80) — readable C lift. */
char player_teleport(int player_handle, void *a, void *b)
{
  void *player;
  int unit_handle;
  void *unit;

  player = datum_get(*(void **)0x5aa6d4, player_handle);
  unit_handle = *(int *)((char *)player + 0x34);
  unit = object_try_and_get_and_verify_type(unit_handle, 1);
  if (unit == 0)
    return 0;
  if (*(int *)((char *)unit + 0xcc) != -1)
    unit_exit_seat_end(unit_handle);
  return FUN_000bb670(player_handle, a, b);
}

/* debug_player_teleport (0xbc6c0) — readable C lift. */
void debug_player_teleport(int16_t local_a, int16_t local_b)
{
  int unit_a;
  int unit_b;
  int player_a;
  void *obj;
  void *pos;

  player_a = local_player_get_player_index(local_a);
  if (player_a == -1)
    unit_a = -1;
  else
    unit_a = *(int *)((char *)datum_get(*(data_t **)0x5aa6d4, player_a) + 0x34);

  player_a = local_player_get_player_index(local_b);
  if (player_a == -1)
    unit_b = -1;
  else
    unit_b = *(int *)((char *)datum_get(*(data_t **)0x5aa6d4, player_a) + 0x34);

  if (unit_a == -1 || unit_b == -1)
    return;
  obj = object_get_and_verify_type(unit_b, 3);
  pos = (char *)obj + 0x50;
  FUN_000bb670(player_index_from_unit_index(unit_a), (void *)unit_b, pos);
}

/* Spawn an object from a small placement record and attach it to a parent.
 *
 * record         (EDI) -- pointer to a record whose tag_index lives at +0xC.
 *                         Two 16-bit values at +0x10 and +0x12 are copied into
 *                         the freshly created object (see below).
 * parent_handle        -- object handle passed through to
 *                         object_placement_data_new as the placement parent.
 *
 * If record->tag_index (+0xC) is NONE (-1), returns NONE without spawning.
 * Otherwise builds an object_placement (0x88 bytes) for that tag, creates the
 * object, and -- when creation succeeds -- verifies it against type_mask 4 and
 * copies record+0x12 -> object+0x25E and record+0x10 -> object+0x260 (note the
 * crossed source offsets; matches the original store order). Returns the new
 * object handle, or NONE on early-out / failed creation. Structurally faithful
 * lift of FUN_000bac10; EAX return is materialized as -1 at entry. */
int FUN_000bac10(void *record, int parent_handle)
{
  int object_index;
  void *object;
  char placement[0x88];

  object_index = -1;
  if (*(int *)((char *)record + 0xc) != -1) {
    object_placement_data_new(placement, *(int *)((char *)record + 0xc),
                              parent_handle);
    object_index = object_new(placement);
    if (object_index != -1) {
      object = object_get_and_verify_type(object_index, 4);
      *(uint16_t *)((char *)object + 0x25e) =
        *(uint16_t *)((char *)record + 0x12);
      *(uint16_t *)((char *)object + 0x260) =
        *(uint16_t *)((char *)record + 0x10);
    }
  }
  return object_index;
}


/*
 * Tears down a player's currently-controlled unit: records the unit handle in
 * the per-slot globals array (base +0x14, stride 4), marks the player dead,
 * then deactivates and garbage-collects the unit and its held weapon.
 * arg1 (player_index) is passed in EAX; param_2 is a cdecl stack arg whose
 * meaning is uncertain (stored to player+0x38 when != NONE).
 */
void FUN_000ba890(int player_index, int param_2)
{
  char *player;
  int slot;
  int object_handle;
  char *object; /* first object_get_and_verify_type result */
  char *object2; /* second (identical) fetch, used for +0x2a2 read */
  int weapon_handle;

  player = (char *)datum_get(player_data, player_index);
  if (*(int *)(player + 0x34) != NONE) {
    if (game_engine_can_score())
      FUN_000b56f0(*(int *)(player + 0x34), -1, -1, -1);

    slot = *(int16_t *)(player + 2);
    *(int *)((char *)players_globals + slot * 4 + 0x14) =
      *(int *)(player + 0x34);
    player_died(player_index);
    object_handle = *(int *)((char *)players_globals + slot * 4 + 0x14);
    object = (char *)object_get_and_verify_type(object_handle, 3);
    object2 = (char *)object_get_and_verify_type(object_handle, 3);
    weapon_handle =
      unit_get_weapon(object_handle, *(int16_t *)(object2 + 0x2a2));
    *(int *)(object + 0x1c8) = NONE;
    object_deactivate(object_handle);
    object_set_garbage(object_handle, 0);
    if (weapon_handle != NONE)
      object_set_garbage(weapon_handle, 0);
    if (param_2 != NONE)
      *(int *)(player + 0x38) = param_2;
    *((char *)players_globals + 0x28) = 0;
  }
}


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


/* Grant a unit its starting equipment from a scenario starting-equipment
 * definition block (scenario+0x348, element size 0x68).
 *
 * unit_handle      -- datum handle of the unit to equip (verified as a type-3
 *                     unit object; must be alive: unit+0x1c8 != -1).
 * equipment_index  -- index into the scenario starting_equipment tag block.
 * reset_flag       -- when nonzero, first strip the unit's weapons and zero
 *                     the powerup/grenade accumulators before applying, and
 *                     mark the first attached weapon as the initial weapon.
 *
 * Each of the two weapon slots (equip_def+0x34 / +0x48 tag refs) that is set
 * spawns a weapon object via FUN_000bac10 (record ptr in EDI: equip_def+0x28
 * for slot 1, equip_def+0x3c for slot 2) parented to the unit, then attaches
 * it via unit_enter_seat. On attach failure the weapon is deleted and an
 * error is logged. Finally the definition's two float powerups (+0x24 -> unit
 * +0x94, +0x20 -> unit+0x90) and two grenade-type counts (+0x50,+0x51 ->
 * unit+0x2ce,+0x2cf) are accumulated into the unit. */
void player_add_equipment(int unit_handle, int16_t equipment_index,
                          char reset_flag)
{
  char *unit;
  char *equip_def;
  int weapon;
  char *dst;
  char *src;
  int count;

  if ((unit_handle != -1) && (equipment_index != -1) &&
      (unit = (char *)object_try_and_get_and_verify_type(unit_handle, 3),
       *(int *)(unit + 0x1c8) != -1)) {
    equip_def = (char *)tag_block_get_element(
      (char *)global_scenario_get() + 0x348, (int)equipment_index, 0x68);

    if (reset_flag != '\0') {
      unit_clear_weapons(unit_handle);
      *(int *)(unit + 0x94) = 0;
      *(int *)(unit + 0x90) = 0;
      *(int16_t *)(unit + 0x2ce) = 0;
    }

    if ((*(int *)(equip_def + 0x34) != -1) &&
        (weapon = FUN_000bac10(equip_def + 0x28, unit_handle), weapon != -1) &&
        !unit_enter_seat(unit_handle, weapon,
                         (int16_t)(uint16_t)(reset_flag != '\0'))) {
      error(2, "Could not attach starting weapon to player");
      object_delete(weapon);
    }

    if ((*(int *)(equip_def + 0x48) != -1) &&
        (weapon = FUN_000bac10(equip_def + 0x3c, unit_handle), weapon != -1) &&
        !unit_enter_seat(unit_handle, weapon, 0)) {
      error(2, "Could not attach starting weapon to player");
      object_delete(weapon);
    }

    *(float *)(unit + 0x94) =
      *(float *)(equip_def + 0x24) + *(float *)(unit + 0x94);
    *(float *)(unit + 0x90) =
      *(float *)(equip_def + 0x20) + *(float *)(unit + 0x90);

    dst = unit + 0x2ce;
    src = equip_def + 0x50;
    count = 2;
    do {
      *dst = (char)(*dst + *src);
      src++;
      dst++;
    } while (--count != 0);
  }
}


/* player_handle_powerup (0xbc320) — readable C lift. */
char player_handle_powerup(int player_handle, int16_t powerup_index, int16_t ticks)
{
  extern char DAT_0026eb68[];
  extern char DAT_0026ee90[];
  char *player;
  char *unit;
  int16_t idx = powerup_index;

  player = (char *)datum_get(*(data_t **)0x5aa6d4, player_handle);
  if (idx < 0 || idx >= 2) {
    display_assert(DAT_0026ee90, DAT_0026eb68, 0xaea, 1);
    system_exit(-1);
  }
  if (idx == 0) {
    unit = (char *)object_get_and_verify_type(*(int *)(player + 0x34), 3);
    if ((*(unsigned char *)(unit + 0x1b4) & 0x10) != 0)
      return 0;
  }
  if (*(int16_t *)(player + 0x68 + (int)idx * 2) == 0) {
    player = (char *)datum_get(*(data_t **)0x5aa6d4, player_handle);
    unit = (char *)object_get_and_verify_type(*(int *)(player + 0x34), 3);
    if (idx == 0) {
      *(unsigned int *)(unit + 0x1b4) |= 0x10u;
      *(int16_t *)(unit + 0x3d2) = 0;
    }
  } else if (!game_engine_running()) {
    player = (char *)datum_get(*(data_t **)0x5aa6d4, player_handle);
    unit = (char *)object_get_and_verify_type(*(int *)(player + 0x34), 3);
    if (idx == 0)
      *(unsigned int *)(unit + 0x1b4) |= 0x20u;
  }
  *(int16_t *)(player + 0x68 + (int)idx * 2) =
      (int16_t)(*(int16_t *)(player + 0x68 + (int)idx * 2) + ticks);
  return 1;
}

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


/* Update one player's unit before game logic runs on the client (0xbc920).
 *
 *  = player_index (register arg); object_handle and position are cdecl
 * stack args (position is asserted non-NULL).  Looks up the player's unit and
 * decides whether it must be re-seated / repositioned this tick:
 *   - If the scenario cluster filter (players_globals+0x2a) is active and the
 *     unit is NOT in that cluster (FUN_0018ef00 == 0), force the update.
 *   - Else, if the unit is at a valid location (FUN_0018e720 != -1), bail.
 *   - If the unit holds a seat handle (+0xcc) that differs from the passed
 *     object's seat, exit the seat; if it still holds one, clear the
 *     pending-flag (players_globals+0x2e) and return.
 *   - Otherwise defer to FUN_000bb670 and record its bool result inverted
 *     into players_globals+0x2e.
 */
void players_update_before_game_client(int player_index ,
                                       int object_handle, void *position)
{
  char *player;
  int unit_handle;
  char *unit;
  char *other_obj;
  bool skip;
  int16_t cluster;
  int loc;
  void *scenario;
  int16_t *element;
  char in_cluster;
  char moved;

  player = (char *)datum_get(player_data, player_index);
  unit_handle = *(int *)(player + 0x34);
  unit = (char *)object_try_and_get_and_verify_type(unit_handle, 1);
  if (player_index == -1) {
    display_assert("player_index!=NONE", "c:\\halo\\SOURCE\\game\\players.c",
                   0x4c7, 1);
    system_exit(-1);
  }
  if (position == NULL) {
    display_assert("position", "c:\\halo\\SOURCE\\game\\players.c", 0x4c8, 1);
    system_exit(-1);
  }
  if (unit == NULL)
    return;

  cluster = *(int16_t *)((char *)players_globals + 0x2a);
  if (cluster != -1) {
    scenario = global_scenario_get();
    element = (int16_t *)tag_block_get_element((char *)scenario + 0x39c,
                                               (int)cluster, 8);
    in_cluster = FUN_0018ef00((int)*element, unit_handle);
    skip = (in_cluster == 0);
  } else {
    skip = false;
  }

  loc = FUN_0018e720((int)(unit + 0x50));
  if (loc != -1 && !skip)
    return;

  if (*(int *)(unit + 0xcc) != -1) {
    other_obj = (char *)object_get_and_verify_type(object_handle, 1);
    if (*(int *)(unit + 0xcc) != *(int *)(other_obj + 0xcc))
      unit_exit_seat_end(unit_handle);
    if (*(int *)(unit + 0xcc) != -1) {
      *((char *)players_globals + 0x2e) = 0;
      return;
    }
  }

  moved = FUN_000bb670(player_index, (void *)(uintptr_t)object_handle, position);
  *((char *)players_globals + 0x2e) = (moved == 0);
}


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
static void (*const bbca60_cbc920)(int player_handle, int anchor_unit, void *position) = players_update_before_game_client;

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


/* FUN_000c0b70 (0xc0b70) — readable C lift (HS eval wrapper). */
void FUN_000c0b70(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00057850(args[0], (char)(unsigned char)args[1]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000bdf80 @ 0x000bdf80
 *
 * HaloScript builtin implementation. Calls FUN_000c95f0() (a no-arg helper
 * that returns a value in EAX) and completes the calling script thread with
 * hs_return(thread_handle, <result>).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP):
 *   function_index  int16_t  [EBP+0x08]  (unused -- never loaded)
 *   thread_handle   int      [EBP+0x0c]  -> hs_return arg1
 *
 * FUN_000c95f0() takes no args; its EAX return is pushed directly as
 * hs_return's value (CALL c95f0; PUSH EAX). The second stack param is then
 * loaded (MOV EAX,[EBP+0xc]) and pushed as hs_return's thread_handle
 * (PUSH EAX; CALL hs_return; ADD ESP,8 cleans the two cdecl args). Ghidra
 * modeled both this function and FUN_000c95f0 as void(void); the EAX return
 * consumed here and the [EBP+0xc] read of the second cdecl param are
 * unmodeled there. */
void FUN_000bdf80(int16_t function_index, int thread_handle)
{
  hs_return(thread_handle, FUN_000c95f0());
}


/* FUN_000be250 (0xbe250) — readable C lift (thin wrapper). */
void FUN_000be250(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  FUN_000c9a50();
  hs_return(thread_datum, 0);
}

/* 0xbdf40 — HS script function handler: evaluate a macro function and, on a
 * non-null result record, forward the record's first dword to FUN_000c95d0,
 * then commit a 0 result to the calling HS thread. Unlike the 0xc135x float
 * trampolines, no value is read back from the callee — hs_return always
 * commits 0. Same evaluator ABI (function_index, thread_datum, init) as the
 * other hs_evaluate_* handlers.
 *
 * ABI (verified against disassembly 0xbdf40): cdecl, plain RET. thread_datum
 * (arg 2, cached in ESI) flows to both the evaluate call (arg 2) and the
 * hs_return call (arg 1). Call site does MOV EDX,[EAX]; PUSH EDX; CALL
 * 0xc95d0 — passing *result (the record's first dword). The combined
 * ADD ESP,0xc after the two trailing calls confirms 0xc95d0 takes exactly
 * one stack arg (Ghidra's void(void) decl dropped it).
 *
 * NOTE: kb groups 0xbdf40 under players.obj, but it is a HaloScript
 * macro-function handler byte-identical in shape to the hs.obj handlers below
 * and calls hs_macro_function_evaluate/hs_return. Placed in hs.c per lift
 * directive (players.c does not compile under VC71 — clang-only __attribute__
 * / raw fnptr casts — so it would be permanently unmeasurable there).
 *
 * Callees (all cdecl, in kb.json):
 *   0xcc560 = hs_macro_function_evaluate(int16 fn_index, int thread_datum,
 *             char init) -> int* (result record, NULL on failure)
 *   0xc95d0 = FUN_000c95d0(int) -> void (record first-dword consumer)
 *   0xcbf80 = hs_return(int thread_handle, int value) */
void FUN_000bdf40(int16_t function_index, int thread_datum, char init)
{
  int *result;

  result =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (result != NULL) {
    FUN_000c95d0((const char *)(uintptr_t)result[0]);
    hs_return(thread_datum, 0);
  }
}


/* 0xbdfa0 — HS script function handler: evaluate a macro function and, on a
 * non-null result record, forward two 16-bit fields to FUN_000ca430, then
 * commit a 0 result to the calling HS thread. Same evaluator ABI
 * (function_index, thread_datum, init) as the other hs_evaluate_* handlers.
 *
 * ABI (verified against disassembly 0xbdfa0): cdecl, plain RET. thread_datum
 * (arg 2, cached in ESI) flows to both the evaluate call (arg 2) and the
 * hs_return call (arg 1). The call site reads MOVSX EAX,word[result+0]
 * (signed int16 -> int) and MOVZX EDX,word[result+4] (unsigned int16 -> int),
 * then PUSH EDX; PUSH EAX; CALL 0xca430 — two cdecl int args (Ghidra's
 * void(void) decl dropped both). The combined ADD ESP,0x10 after the two
 * trailing calls (ca430's 2 + hs_return's 2) confirms the arg counts. Note
 * result is int*, so the +0x4 read is at (char *)result + 4, a narrow int16.
 *
 * Callees (all cdecl, in kb.json):
 *   0xcc560 = hs_macro_function_evaluate(int16 fn_index, int thread_datum,
 *             char init) -> int* (result record, NULL on failure)
 *   0xca430 = FUN_000ca430(int, int) -> void (two-field consumer)
 *   0xcbf80 = hs_return(int thread_handle, int value) */
void FUN_000bdfa0(int16_t function_index, int thread_datum, char init)
{
  int *result;

  result =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (result != NULL) {
    FUN_000ca430(*(short *)result, *(unsigned short *)((char *)result + 4));
    hs_return(thread_datum, 0);
  }
}


/* FUN_000be0d0 (0xbe0d0) — readable C lift (HS eval wrapper). */
void FUN_000be0d0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000c9990((int16_t)(uint16_t)args[0]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000be110 (0xbe110) — readable C lift (HS eval wrapper). */
void FUN_000be110(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000c99e0(args[0]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000be150 (0xbe150) — readable C lift (HS eval wrapper). */
void FUN_000be150(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000ca110((int16_t)(uint16_t)args[0]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000be190 (0xbe190) — readable C lift (HS eval wrapper). */
void FUN_000be190(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000c9b90((const char *)args[0]);
  }
  hs_return(thread_datum, 0);
}

/* 0xbe1d0 — HaloScript macro-function evaluate-then-finalize wrapper.
 * Evaluates a macro-function expression on a thread; when the evaluation
 * yields a result node (non-NULL record ptr in EAX), it runs a fixed
 * side-effecting step FUN_000ca140() (no args) and then commits a literal
 * 0 back to the calling thread via hs_return(thread_datum, 0). Unlike the
 * value-returning neighbors this does not read any field of the record and
 * always returns 0 — the record is used only as an "evaluation complete"
 * predicate.
 *
 * players.obj groups this, but like its siblings it calls hs_runtime.obj's
 * static hs_macro_function_evaluate / hs_return, so it is co-located here.
 *
 * Plain cdecl (caller cleans, RET no immediate). Three stack params:
 *   param1 @ EBP+0x8  = function_index (int16_t)
 *   param2 @ EBP+0xc  = thread_datum
 *   param3 @ EBP+0x10 = init (char)
 *
 * Callees (all in kb.json):
 *   0xcc560 = hs_macro_function_evaluate(function_index, thread_datum, init)
 *             -> result node ptr in EAX (NULL while evaluation pending)
 *   0xca140 = FUN_000ca140() (void, no args)
 *   0xcbf80 = hs_return(thread_datum, 0)
 */
void FUN_000be1d0(int16_t function_index, int thread_datum, char init)
{
  void *record;

  record =
    (void *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != 0) {
    FUN_000ca140((const char *)0);
    hs_return(thread_datum, 0);
  }
}


/* 0xbe210 — HS built-in evaluator, sibling of FUN_000be1d0. Evaluates a
 * single macro-function via hs_macro_function_evaluate; while that returns
 * NULL the evaluation is still pending and nothing is committed this call.
 * Once it yields a non-NULL result datum, FUN_000c9bb0() runs (side-effect
 * cleanup, void/void) and the thread is committed with hs_return(thread, 0).
 * Standard evaluator ABI (function_index, thread_datum, init), plain cdecl.
 *
 * Callees (all in kb.json):
 *   0xcc560 = hs_macro_function_evaluate(function_index, thread_datum, init)
 *             -> result node ptr in EAX (NULL while evaluation pending)
 *   0xc9bb0 = FUN_000c9bb0() (void, no args)
 *   0xcbf80 = hs_return(thread_datum, 0)
 */
void FUN_000be210(int16_t function_index, int thread_datum, char init)
{
  void *record;

  record =
    (void *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != 0) {
    FUN_000c9bb0((const char *)0);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000bdef0 @ 0x000bdef0
 *
 * HaloScript builtin dispatcher, same shape as the breakable-surfaces /
 * recorded-animation builtins below. Evaluates the script function via
 * hs_macro_function_evaluate(function_index, thread_datum, init); on a
 * non-NULL evaluation record it reads the record's first byte (a single-byte
 * load, XOR EDX,EDX; MOV DL,[EAX]) and passes it to FUN_000c95c0, which
 * returns (byte == 0) in AL. That byte result is stored into a pre-zeroed
 * dword result slot (MOV dword[EBP-4],0 before the call; MOV byte[EBP-4],AL
 * inside the branch) and forwarded zero-extended to hs_return(thread_datum,
 * result).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP; PUSH ECX for one local):
 *   function_index  int16_t  [EBP+0x08]
 *   thread_datum    int      [EBP+0x0c]  -> reused for hs_return arg1 (ESI)
 *   init            char     [EBP+0x10]
 *
 * FUN_000c95c0 was modeled void(void) by Ghidra (so the decompile showed a
 * no-arg call and read extraout_AL); the disassembly (000bdf14: XOR EDX,EDX;
 * MOV DL,[EAX]; PUSH EDX; CALL 0xc95c0) shows it takes the record's first
 * byte and returns AL = (byte == 0). Its kb decl is corrected to
 * `unsigned char FUN_000c95c0(unsigned char)`. The single ADD ESP,0xc after
 * the hs_return CALL folds FUN_000c95c0's 1 arg and hs_return's 2 args
 * (adjacent-call cleanup). */
void FUN_000bdef0(int16_t function_index, int thread_datum, char init)
{
  volatile unsigned int result_slot;
  unsigned char *record;
  unsigned int result;

  result_slot = 0;
  record = (unsigned char *)hs_macro_function_evaluate(function_index,
                                                       thread_datum, init);
  if (record != NULL) {
    result_slot = (unsigned char)FUN_000c95c0(record[0]);
    result = (unsigned int)result_slot;
    hs_return(thread_datum, result);
  }
}


/* 0xbe3b0 — HS built-in evaluator. Evaluates a single macro-function
 * argument via hs_macro_function_evaluate; while that returns NULL the
 * evaluation is still pending and nothing is committed this call. Once it
 * yields a value datum, its first dword is converted through FUN_000ce420
 * (returns a 16-bit value in AX, zero-extended by the original into the
 * result slot) and committed with hs_return. Standard evaluator ABI
 * (function_index, thread_datum, init). */
void FUN_000be3b0(int16_t function_index, int thread_datum, char init)
{
  int *result;
  unsigned int value;

  result =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (result != NULL) {
    value = (uint16_t)FUN_000ce420(*result);
    hs_return(thread_datum, (int)value);
  }
}


/* 0xbe5a0 — HS script function handler: evaluate a macro function and, on a
 * non-null result record, forward the record's first dword (+0x0, int) to
 * FUN_000c9d80, then return void to the calling HS thread via
 * hs_return(thread_datum, 0). Same evaluator ABI (function_index, thread_datum,
 * init) as the other hs_evaluate_* handlers.
 *
 * ABI (verified against delinked disassembly 0xbe5a0): cdecl, plain RET.
 * thread_datum (arg 2, cached in ESI) flows to both the evaluate call (arg 2)
 * and the hs_return call (arg 1). On a non-null result (EAX) the call site
 * dereferences the record and passes its first dword to the single-arg callee:
 *   MOV EDX,[EAX] (result[0]); PUSH EDX; CALL 0xc9d80
 * then PUSH 0; PUSH ESI(=thread_datum); CALL hs_return. The combined
 * ADD ESP,0xc after the two trailing calls = FUN_000c9d80's 1 arg (0x4) +
 * hs_return's 2 args (0x8). Ghidra's void(void) decl for 0xc9d80 dropped its
 * single stack arg, misled by that combined cleanup; kb.json decl for 0xc9d80
 * corrected to void(int).
 *
 * Callees (all cdecl, in kb.json):
 *   0xcc560 = hs_macro_function_evaluate(int16 fn_index, int thread_datum,
 *             char init) -> int* (result record, NULL on failure)
 *   0xc9d80 = FUN_000c9d80(int) -> void (record consumer)
 *   0xcbf80 = hs_return(int thread_handle, int value) */
void FUN_000be5a0(int16_t function_index, int thread_datum, char init)
{
  int *result;

  result =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (result != NULL) {
    FUN_000c9d80(result[0]);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000be620 @ 0x000be620
 *
 * HaloScript function-evaluator wrapper (real-valued variant). Evaluates the
 * script function via hs_macro_function_evaluate(function_index, thread_handle,
 * init); on a non-NULL evaluation record it dereferences the record's first
 * dword and passes it to FUN_000ca010, which returns a float in ST0. The float
 * is stored to a 4-byte stack cell and reloaded as a raw int32, then forwarded
 * to hs_return.
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP; PUSH ECX):
 *   function_index  int16_t  [EBP+0x08]
 *   thread_handle   int      [EBP+0x0c]  (held in ESI)
 *   init            char     [EBP+0x10]
 *
 * The FSTP [EBP-4] / MOV EAX,[EBP-4] / PUSH EAX pattern is a raw 4-byte
 * reinterpret of the float bits into the hs value cell -- NOT an (int) cast,
 * which would truncate. FUN_000ca010's 1-arg cdecl float-returning signature is
 * recovered from this call site (MOV EDX,[EAX]; PUSH EDX; CALL; FSTP [EBP-4]);
 * its kb decl was previously void(void). */
void FUN_000be620(int16_t function_index, int thread_handle, char init)
{
  int record;
  union {
    float f;
    int i;
  } cell;

  record = hs_macro_function_evaluate(function_index, thread_handle, init);
  if (record != 0) {
    cell.f = FUN_000ca010(*(int *)record);
    hs_return(thread_handle, cell.i);
  }
}


/* FUN_000be6a0 @ 0x000be6a0
 *
 * HaloScript function-evaluator wrapper (short-valued variant). Evaluates the
 * script function via hs_macro_function_evaluate(function_index, thread_datum,
 * init); on a non-NULL evaluation record it reads the record's first uint16
 * field, passes it (zero-extended) to numeric_countdown_timer_get, masks the
 * result to 16 bits, and forwards it to hs_return.
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP; PUSH ECX):
 *   function_index  int16_t  [EBP+0x08]
 *   thread_datum    int      [EBP+0x0c]
 *   init            char     [EBP+0x10]
 *
 * thread_datum is reused as the first arg to hs_return. The record's first
 * field is dereferenced as uint16 (*(ushort *)record) then zero-extended to
 * uint before the countdown-timer lookup; the getter's return is masked
 * &0xffff before hs_return. kb decl was previously void(void). */
void FUN_000be6a0(int16_t function_index, int thread_datum, char init)
{
  unsigned short *record;
  int value;

  record = (unsigned short *)hs_macro_function_evaluate(function_index,
                                                        thread_datum, init);
  if (record != 0) {
    value = numeric_countdown_timer_get((unsigned int)*record);
    value = value & 0xffff;
    hs_return(thread_datum, value);
  }
}


/* FUN_000be730 @ 0x000be730
 *
 * HaloScript builtin implementation (breakable-surfaces toggle). Evaluates the
 * script function via hs_macro_function_evaluate(function_index, thread_datum,
 * init); on a non-NULL evaluation record it reads the record's first byte (the
 * boolean "active" flag) and forwards it to breakable_surfaces_enable(char),
 * then completes the calling script thread with hs_return(thread_datum, 0).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP):
 *   function_index  int16_t  [EBP+0x08]
 *   thread_datum    int      [EBP+0x0c]  -> hs_return arg1
 *   init            char     [EBP+0x10]
 *
 * hs_macro_function_evaluate returns an evaluation-record pointer in EAX. When
 * non-NULL the original dereferences the record's first byte (a single-byte
 * load, NOT a wider read) and passes it to breakable_surfaces_enable; then
 * pushes 0 and thread_datum for hs_return (PUSH 0; PUSH thread_datum; CALL; ADD
 * ESP,8). Ghidra modeled this void(void); the three cdecl stack params
 * (in_stack_00000004/08/0c) are unmodeled there (kb decl was previously
 * void(void)). */
void FUN_000be730(int16_t function_index, int thread_datum, char init)
{
  char *record;

  record =
    (char *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    breakable_surfaces_enable(*record);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000be860 (0xbe860) — readable C lift (HS eval wrapper). */
void FUN_000be860(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    recorded_animation_kill(args[0]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000be8a0 (0xbe8a0) — readable C lift (HS eval value wrapper). */
void FUN_000be8a0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, (int)(unsigned short)recorded_animation_get_time_left(args[0]));
  } else {
    hs_return(thread_datum, 0);
  }
}

/* FUN_000beab0 @ 0x000beab0
 *
 * HaloScript macro-function trampoline (object body-vitality query). A direct
 * sibling of FUN_000bea10 above, differing only in the single-argument middle
 * callee. Evaluates the script function via hs_macro_function_evaluate(
 * function_index, thread_datum, init), which returns a pointer to an evaluation
 * record. On a non-NULL record it forwards the first dword (*record, MOV
 * EDX,[EAX]) to object_get_maximum_body_vitality, then completes the calling
 * script thread with hs_return(thread_datum, 0).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP; PUSH ESI):
 *   function_index  int16_t  [EBP+0x08]  -> hs_macro_function_evaluate arg1
 *   thread_datum    int      [EBP+0x0c]  -> arg2; held in ESI, reused for
 *                                           hs_return arg1
 *   init            char     [EBP+0x10]  -> arg3
 *
 * The lone PUSH EDX for object_get_maximum_body_vitality is not cleaned
 * immediately; its 4-byte cleanup is folded into the ADD ESP,0xc after
 * hs_return (0xc = 8 for hs_return's two cdecl args + 4 for the single-arg
 * call). Ghidra modeled this void(void) with the three cdecl params read as
 * in_stack_*. */
void FUN_000beab0(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    object_get_maximum_body_vitality(*record);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000beaf0 @ 0x000beaf0
 *
 * HaloScript macro-function trampoline (object damage-eligibility query). A
 * direct sibling of FUN_000beab0 above, differing only in the single-argument
 * middle callee. Evaluates the script function via hs_macro_function_evaluate(
 * function_index, thread_datum, init), which returns a pointer to an evaluation
 * record. On a non-NULL record it forwards the first dword (*record, MOV
 * EDX,[EAX]) to object_can_take_damage, then completes the calling script
 * thread with hs_return(thread_datum, 0).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP; PUSH ESI):
 *   function_index  int16_t  [EBP+0x08]  -> hs_macro_function_evaluate arg1
 *   thread_datum    int      [EBP+0x0c]  -> arg2; held in ESI, reused for
 *                                           hs_return arg1
 *   init            char     [EBP+0x10]  -> arg3
 *
 * The lone PUSH EDX for object_can_take_damage is not cleaned immediately; its
 * 4-byte cleanup is folded into the ADD ESP,0xc after hs_return (0xc = 8 for
 * hs_return's two cdecl args + 4 for the single-arg call). Ghidra modeled this
 * void(void) with the three cdecl params read as in_stack_*. */
void FUN_000beaf0(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    object_can_take_damage(*record);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000beb70 @ 0x000beb70
 *
 * HaloScript macro-function trampoline (object-list side-effect variant). A
 * direct sibling of the FUN_000bebb0 family above. Evaluates the script
 * function via hs_macro_function_evaluate(function_index, thread_datum, init),
 * which returns a pointer to an evaluation record. On a non-NULL record it
 * forwards the first dword (*record, MOV EDX,[EAX]) to FUN_000c9d40, then
 * completes the calling script thread with hs_return(thread_datum, 0).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP):
 *   function_index  int16_t  [EBP+0x08]  -> hs_macro_function_evaluate arg1
 *   thread_datum    int      [EBP+0x0c]  -> arg2, reused for hs_return arg1
 *   init            char     [EBP+0x10]  -> arg3
 *
 * BUGFIX (was a players.obj lift regression, e14f0280): the original does
 *   MOV EDX,[EAX]; PUSH EDX; CALL FUN_000c9d40   (0xbeb8c-0xbeb8f)
 * i.e. it passes *record (the object-list handle) to FUN_000c9d40, which
 * iterates that object list (object_list_iterator_first/next at
 * 0xce450/0xce320). Ghidra models FUN_000c9d40 as void(void), so the original
 * lift called it with no argument; FUN_000c9d40 then read a stale stack value
 * as the handle and asserted "object list header index #N is unused or changed"
 * (data.c). The decl for FUN_000c9d40 is corrected to take the object-list
 * handle. */
void FUN_000beb70(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    FUN_000c9d40(*record);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000bebb0 @ 0x000bebb0
 *
 * HaloScript macro-function trampoline (object-definition predict variant). A
 * direct sibling of the FUN_000bea10/FUN_000beab0 family above. Evaluates the
 * script function via hs_macro_function_evaluate(function_index, thread_datum,
 * init), which returns a pointer to an evaluation record. On a non-NULL record
 * it forwards the first dword (*record, MOV EAX,[EAX]) to
 * object_definition_predict, then completes the calling script thread with
 * hs_return(thread_datum, 0).
 *
 * cdecl frame:
 *   function_index  int16_t  [EBP+0x08]  -> hs_macro_function_evaluate arg1
 *   thread_datum    int      [EBP+0x0c]  -> arg2, reused for hs_return arg1
 *   init            char     [EBP+0x10]  -> arg3
 *
 * Ghidra modeled this void(void) with the three cdecl params read as
 * in_stack_*; the correct prototype is the 3-arg cdecl below. kb decl corrected
 * from void(void) so callers pass all three arguments. */
void FUN_000bebb0(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    object_definition_predict(*record);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000bebf0 @ 0x000bebf0
 *
 * HaloScript macro-function trampoline, a direct sibling of FUN_000bebb0
 * above. Evaluates the script function via hs_macro_function_evaluate(
 * function_index, thread_datum, init), which returns a pointer to an
 * evaluation record. On a non-NULL record it forwards the first dword
 * (*record, MOV EAX,[EAX]) to FUN_0013dbe0, then completes the calling
 * script thread with hs_return(thread_datum, 0).
 *
 * cdecl frame:
 *   function_index  int16_t  [EBP+0x08]  -> hs_macro_function_evaluate arg1
 *   thread_datum    int      [EBP+0x0c]  -> arg2, reused for hs_return arg1
 *   init            char     [EBP+0x10]  -> arg3
 *
 * Ghidra modeled this void(void) with the three cdecl params read as
 * in_stack_*; the correct prototype is the 3-arg cdecl below. kb decl
 * corrected from void(void) so callers pass all three arguments. */
void FUN_000bebf0(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    FUN_0013dbe0(*record);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000bec30 @ 0x000bec30
 *
 * HaloScript macro-function evaluator wrapper, a direct sibling of
 * FUN_000bebf0 above. Evaluates the script function via
 * hs_macro_function_evaluate(function_index, thread_datum, init); while that
 * returns NULL the evaluation is still pending and nothing is committed. Once a
 * non-NULL evaluation record is returned, its first field is loaded as a 16-bit
 * value (*(short *)record) and forwarded to FUN_0013dc10, then the thread is
 * committed with hs_return(thread_datum, 0).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP):
 *   function_index  int16_t  [EBP+0x08]  -> hs_macro_function_evaluate arg1
 *   thread_datum    int      [EBP+0x0c]  -> arg2; reused for hs_return arg1
 *   init            char     [EBP+0x10]  -> arg3
 *
 * hs_macro_function_evaluate returns the record pointer in EAX. On non-NULL the
 * original loads its first field as a 16-bit value (word load) and passes it to
 * FUN_0013dc10 (which takes a short camera_point_index), then commits the
 * thread with hs_return(thread_datum, 0). Ghidra modeled this void(void) with
 * the three cdecl params read as in_stack_*; the correct prototype is the 3-arg
 * cdecl below. kb decl corrected from void(void) so callers pass all three
 * arguments. */
void FUN_000bec30(int16_t function_index, int thread_datum, char init)
{
  short *record;

  record =
    (short *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    FUN_0013dc10(*record);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000bec90 @ 0x000bec90
 *
 * HaloScript macro-function evaluator wrapper, a direct sibling of
 * FUN_000be3b0 / FUN_000bed20 above. Evaluates the script function via
 * hs_macro_function_evaluate(function_index, thread_datum, init); while that
 * returns NULL the evaluation is still pending and nothing is committed. Once a
 * non-NULL evaluation record is returned, its first dword (*record) is passed
 * to object_pvs_activate, then the calling thread is completed with
 * hs_return(thread_datum, 0).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP):
 *   function_index  int16_t  [EBP+0x08]  -> hs_macro_function_evaluate arg1
 *   thread_datum    int      [EBP+0x0c]  -> arg2; reused for hs_return arg1
 *   init            char     [EBP+0x10]  -> arg3
 *
 * hs_macro_function_evaluate returns the record pointer in EAX. On non-NULL the
 * original loads its first dword (MOV [EAX] = *(int *)record) and passes it to
 * object_pvs_activate, then pushes 0 and thread_datum for hs_return. Ghidra
 * modeled this void(void); the three cdecl params were unmodeled (in_stack_*).
 * kb decl for this function was previously void(void). */
void FUN_000bec90(int16_t function_index, int thread_datum, char init)
{
  int *result;

  result =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (result != NULL) {
    object_pvs_activate(*result);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000becd0 @ 0x000becd0
 *
 * HaloScript macro-function evaluator wrapper (byte-valued variant), a direct
 * sibling of FUN_000bec90 / FUN_000bed20 above. Evaluates the script function
 * via hs_macro_function_evaluate(function_index, thread_datum, init); while
 * that returns NULL the evaluation is still pending and nothing is committed.
 * Once a non-NULL evaluation record is returned, its first byte is passed
 * through lights_enable (0x139300, a cdecl byte->byte helper) and the
 * zero-extended result is committed to the calling thread with hs_return.
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP; PUSH ECX for one local):
 *   function_index  int16_t  [EBP+0x08]  -> hs_macro_function_evaluate arg1
 *   thread_datum    int      [EBP+0x0c]  -> arg2; held in ESI, reused for
 *                                           hs_return arg1
 *   init            char     [EBP+0x10]  -> arg3
 *
 * hs_macro_function_evaluate returns the record pointer in EAX. On non-NULL the
 * original loads a single byte from it (XOR EDX,EDX; MOV DL,[EAX] = a
 * zero-extended byte load, NOT a full dword) and passes it to lights_enable
 * (PUSH EDX; CALL). That callee is plain cdecl returning a byte in AL: the
 * caller stores only AL (MOV byte[EBP-4],AL) and forwards the zero-extended
 * value. The lone PUSH EDX for lights_enable is not cleaned immediately; its
 * 4-byte cleanup is folded into the ADD ESP,0xc after hs_return (0xc = 8 for
 * hs_return's two cdecl args + 4 for lights_enable's arg), confirming
 * lights_enable is cdecl with one stack arg. Ghidra modeled this void(void);
 * the three cdecl params were unmodeled (in_stack_*) and lights_enable's
 * argument/return were mis-declared void(void) (kb decl for both was
 * previously void(void)). lights_enable's true name is uncertain; it behaves
 * as a boolean toggle/setter returning a state byte. */
void FUN_000becd0(int16_t function_index, int thread_datum, char init)
{
  unsigned char *result;
  unsigned int value;

  result = (unsigned char *)hs_macro_function_evaluate(function_index,
                                                       thread_datum, init);
  if (result != NULL) {
    value = lights_enable(*result);
    hs_return(thread_datum, (int)value);
  }
}


/* FUN_000bed20 @ 0x000bed20
 *
 * HaloScript macro-function evaluator wrapper (16-bit-valued variant), a direct
 * sibling of FUN_000be3b0 above. Evaluates the script function via
 * hs_macro_function_evaluate(function_index, thread_datum, init); while that
 * returns NULL the evaluation is still pending and nothing is committed. Once a
 * non-NULL evaluation record is returned, its first dword is converted through
 * FUN_00145740 (a cdecl helper returning a 16-bit value in AX) and the
 * zero-extended result is committed to the calling thread with hs_return.
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP; PUSH ECX for one local):
 *   function_index  int16_t  [EBP+0x08]  -> hs_macro_function_evaluate arg1
 *   thread_datum    int      [EBP+0x0c]  -> arg2; held in ESI, reused for
 *                                           hs_return arg1
 *   init            char     [EBP+0x10]  -> arg3
 *
 * hs_macro_function_evaluate returns the record pointer in EAX. On non-NULL the
 * original loads its first dword (MOV EDX,[EAX] = *(int *)record, a full-dword
 * load) and passes it to FUN_00145740 (PUSH EDX; CALL). That callee is plain
 * cdecl (RET 0 at 0x1457a7, POP ESI/POP EBP/RET) returning 16 bits: the caller
 * stores only AX (MOV word[EBP-4],AX) and forwards the zero-extended value. The
 * lone PUSH EDX for FUN_00145740 is not cleaned immediately; its 4-byte cleanup
 * is folded into the ADD ESP,0xc after hs_return (0xc = 8 for hs_return's two
 * cdecl args + 4 for FUN_00145740's arg), confirming FUN_00145740 is cdecl.
 * Ghidra modeled this void(void); the three cdecl params were unmodeled
 * (in_stack_*) and FUN_00145740's argument/return were mis-declared void(void)
 * (kb decl for both was previously void(void)). */
void FUN_000bed20(int16_t function_index, int thread_datum, char init)
{
  int *result;
  unsigned int value;

  result =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (result != NULL) {
    value = (uint16_t)FUN_00145740(*result);
    hs_return(thread_datum, (int)value);
  }
}


/* FUN_000bee00 @ 0x000bee00
 *
 * HaloScript macro-function evaluator wrapper (byte-dispatch variant), a direct
 * sibling of FUN_000bedb0 above. Evaluates the script function via
 * hs_macro_function_evaluate(function_index, thread_datum, init); while that
 * returns NULL the evaluation is still pending and nothing is committed. On a
 * non-NULL evaluation record the zero-extended first byte of the record is
 * forwarded to the side-effect routine at 0x184b60, then the calling thread is
 * completed with hs_return(thread_datum, 0).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP; PUSH ESI for thread_datum):
 *   function_index  int16_t  [EBP+0x08]  -> hs_macro_function_evaluate arg1
 *   thread_datum    int      [EBP+0x0c]  -> arg2; held in ESI, reused for
 *                                           hs_return arg1
 *   init            char     [EBP+0x10]  -> arg3
 *
 * hs_macro_function_evaluate returns the record pointer in EAX (TEST EAX,EAX /
 * JZ). On non-NULL the original zero-extends the record's first byte
 * (XOR EDX,EDX; MOV DL,BYTE PTR [EAX]) and pushes it as the single cdecl arg to
 * the routine at 0x184b60, then pushes (0, thread_datum) for hs_return. One
 * combined ADD ESP,0x0c folds 0x184b60's 1-dword cleanup with hs_return's
 * 2-dword cleanup, confirming 0x184b60 is cdecl caller-cleaned with exactly one
 * argument here. Ghidra modeled this void(void): the three cdecl params were
 * unmodeled (in_stack_*) and 0x184b60's argument was hidden because its kb decl
 * was void render_effects(void). The 0x184b60=render_effects attribution is
 * unverified; only its 1-arg cdecl shape is proven at this call site. */
void FUN_000bee00(int16_t function_index, int thread_datum, char init)
{
  unsigned char *record;

  record = (unsigned char *)hs_macro_function_evaluate(function_index,
                                                       thread_datum, init);
  if (record != NULL) {
    render_effects(*record);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000bee80 @ 0x000bee80
 *
 * HaloScript macro-function evaluator wrapper (unit "open" variant), a direct
 * sibling of FUN_000bee40 above and structurally identical to FUN_000beb70.
 * Evaluates the script function via hs_macro_function_evaluate(function_index,
 * thread_datum, init); while that returns NULL the evaluation is still pending
 * and nothing is committed. On a non-NULL evaluation record the record's first
 * dword (a unit handle) is forwarded to unit_open, then the calling script
 * thread is completed with hs_return(thread_datum, 0).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP; PUSH ESI for thread_datum; no _chkstk,
 * no locals, no FPU):
 *   function_index  int16_t  [EBP+0x08]  -> hs_macro_function_evaluate arg1
 *                                           (loaded to ECX)
 *   thread_datum    int      [EBP+0x0c]  -> arg2; held in ESI across the whole
 *                                           body, reused for hs_return arg1
 *   init            char     [EBP+0x10]  -> arg3 (loaded to EAX)
 *
 * The evaluate call pushes EAX([+0x10]), ESI([+0x0c]), ECX([+0x08]) and cleans
 * with ADD ESP,0xC, so its first argument is [EBP+0x08]. The returned EAX is
 * tested (TEST EAX,EAX / JZ epilogue) and then dereferenced at offset 0
 * (MOV EDX,[EAX]; PUSH EDX) as the single unit_open argument — i.e. the kb decl
 * `int hs_macro_function_evaluate(...)` really returns a record POINTER; cast
 * at the call site rather than widening the callee decl. hs_return's arg1 comes
 * from the preserved ESI (the ORIGINAL thread_datum), not from the record.
 * A single combined ADD ESP,0xC at 0xbeeac folds unit_open's 1-dword cleanup
 * with hs_return's 2-dword cleanup; the context-pack ARG_COUNT warning on
 * 0xcbf80 ("cleanup=3 vs decl=2") is that merge, and the PUSH count proves
 * hs_return still takes exactly 2 args. Ghidra modeled this void(void), so the
 * three cdecl params showed up as in_stack_* — they are stack args, not.
 *
 * Callees (all cdecl, in kb.json):
 *   0xcc560  = hs_macro_function_evaluate(int16_t, int, char) -> record ptr
 *   0x1ae160 = unit_open(int unit_handle)
 *   0xcbf80  = hs_return(int thread_handle, int value) */
void FUN_000bee80(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    unit_open(*record);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000beec0 @ 0x000beec0
 *
 * HaloScript macro-function evaluator wrapper (unit "close" variant), the
 * direct sibling of FUN_000bee80 above: byte-identical in shape, differing
 * only in which record-first-dword consumer it calls (unit_close 0x1ae180
 * instead of unit_open 0x1ae160). Evaluates the script function via
 * hs_macro_function_evaluate(function_index, thread_datum, init); while that
 * returns NULL the evaluation is still pending and nothing is committed. On a
 * non-NULL evaluation record the record's first dword (a unit handle) is
 * forwarded to unit_close, then the calling script thread is completed with
 * hs_return(thread_datum, 0).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP; PUSH ESI for thread_datum; no _chkstk,
 * no locals, no FPU, plain RET so the caller cleans):
 *   function_index  int16_t  [EBP+0x08]  -> hs_macro_function_evaluate arg1
 *                                           (loaded to ECX)
 *   thread_datum    int      [EBP+0x0c]  -> arg2; held in ESI across the whole
 *                                           body, reused for hs_return arg1
 *   init            char     [EBP+0x10]  -> arg3 (loaded to EAX)
 *
 * The evaluate call pushes EAX([+0x10]), ESI([+0x0c]), ECX([+0x08]) and cleans
 * with ADD ESP,0xC, so its first argument is [EBP+0x08]. The returned EAX is
 * tested (TEST EAX,EAX / JZ epilogue) and then dereferenced at offset 0
 * (MOV EDX,[EAX]; PUSH EDX) as the single unit_close argument — i.e. the kb
 * decl `int hs_macro_function_evaluate(...)` really returns a record POINTER;
 * cast at the call site rather than widening the callee decl. hs_return's arg1
 * comes from the preserved ESI (the ORIGINAL thread_datum), not from the
 * record. A single combined ADD ESP,0xC at 0xbeeec folds unit_close's 1-dword
 * cleanup with hs_return's 2-dword cleanup; the ARG_COUNT enrichment warning
 * on 0xcbf80 ("cleanup=3 vs decl=2") is that merge, and the PUSH count proves
 * hs_return still takes exactly 2 args (do NOT "fix" either decl). Ghidra
 * modeled this void(void), so the three cdecl params showed up as in_stack_*
 * — they are stack args, not.
 *
 * Callees (all cdecl, in kb.json):
 *   0xcc560  = hs_macro_function_evaluate(int16_t, int, char) -> record ptr
 *   0x1ae180 = unit_close(int unit_handle)
 *   0xcbf80  = hs_return(int thread_handle, int value) */
void FUN_000beec0(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    unit_close(*record);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000bef00 (0xbef00) — readable C lift (HS eval wrapper). */
void FUN_000bef00(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    unit_set_actively_controlled_flag(args[0]);
  }
  hs_return(thread_datum, 0);
}

/* 0xbef40 — HS script function handler: kill a unit. Structural twin of
 * FUN_000beec0 above; only the middle callee differs (unit_kill @0x1a7fa0
 * instead of unit_close @0x1ae180). 13 instructions, standard EBP frame, ESI
 * is the one callee-saved register and holds thread_datum live across the
 * evaluate call — which is why the SAME value feeds both
 * hs_macro_function_evaluate and hs_return (do not source hs_return's arg1
 * from the record).
 *
 * Binary evidence (0xbef40-0xbef71):
 *   EAX=[EBP+0x10] (init), ECX=[EBP+0x08] (function_index), ESI=[EBP+0x0c]
 *   (thread_datum). CALL 1 @0xbef50 pushes EAX, ESI, ECX (cdecl reverse
 *   order) then ADD ESP,0xC -> C order (function_index, thread_datum, init).
 *   TEST EAX,EAX / JZ 0xbef6f skips both remaining calls on NULL.
 *   CALL 2 @0xbef5f: MOV EDX,[EAX]; PUSH EDX -- the argument is the
 *   DEREFERENCE of the returned record at offset 0, not the pointer.
 *   CALL 3 @0xbef67: PUSH 0; PUSH ESI -> hs_return(thread_datum, 0).
 *   ONE combined ADD ESP,0xC at 0xbef6c folds unit_kill's 1 dword with
 *   hs_return's 2 dwords; the ARG_COUNT enrichment warning on 0xcbf80
 *   ("cleanup=3 vs decl=2") is that merge -- hs_return really takes 2 args,
 *   do NOT "fix" its decl. POP ESI; POP EBP; RET (no immediate -> cdecl).
 *   Ghidra modeled this void(void), so the three cdecl params appeared as
 *   in_stack_* pseudo-locals; they are stack args, not.
 *
 * Callees (all cdecl, in kb.json):
 *   0xcc560  = hs_macro_function_evaluate(int16_t, int, char) -> record ptr
 *   0x1a7fa0 = unit_kill(int unit_handle)
 *   0xcbf80  = hs_return(int thread_handle, int value) */
void FUN_000bef40(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    unit_kill(*record);
    hs_return(thread_datum, 0);
  }
}


void FUN_000bef80(int16_t function_index, int thread_datum, char init)
{
  volatile unsigned int result_slot;
  int *record;
  unsigned int result;

  result_slot = 0;
  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    result_slot = (unsigned short)FUN_001AC0E0(record[0]);
    result = (unsigned int)result_slot;
    hs_return(thread_datum, result);
  }
}


/* 0xbefd0 — HS script function handler: stop a unit's custom animation.
 *
 * Byte-shape twin of FUN_000bdf40 (differs only in the middle callee). cdecl
 * frame: PUSH EBP; MOV EBP,ESP; PUSH ESI; ... POP ESI; POP EBP; RET (no RET
 * immediate — caller cleans).
 *
 * Params from the EBP offsets (Ghidra modeled this void(void) and dropped all
 * three; the in_stack_* names in its output are the tell — they are stack
 * params, NOT register args):
 *   function_index  int16_t  [EBP+0x08] -> ECX -> evaluate arg 1
 *   thread_datum    int      [EBP+0x0c] -> ESI (cached: used twice)
 *   init            char     [EBP+0x10] -> EAX -> evaluate arg 3
 *
 * CALL 0xcc560 pushes EAX(init), ESI(thread_datum), ECX(function_index) and
 * cleans with ADD ESP,0xc — 3 stack args, so the C order is
 * (function_index, thread_datum, init). TEST EAX,EAX; JZ end is the NULL
 * guard on the returned result record.
 *
 * The middle call does MOV EDX,dword ptr [EAX]; PUSH EDX — a FULL 32-bit load
 * of the record's first dword (unlike the byte load in the 0xbdef0 sibling),
 * passed as unit_stop_custom_animation(unit_handle).
 *
 * The single trailing ADD ESP,0xc at 0xbeffc is MERGED cleanup for the 1 arg
 * of unit_stop_custom_animation plus the 2 args of hs_return (1+2 = 3 dwords).
 * The call-site audit's "hs_return cleanup=3 vs decl=2" is a false positive
 * from that adjacent-call merging; the disasm shows exactly 2 pushes for
 * hs_return (PUSH 0x0; PUSH ESI). Same pattern documented on the twin.
 *
 * Callees (all cdecl, in kb.json):
 *   0xcc560   = hs_macro_function_evaluate(int16 fn_index, int thread_datum,
 *               char init) -> int* (result record, NULL on failure)
 *   0x1af0d0  = unit_stop_custom_animation(int unit_handle)
 *   0xcbf80   = hs_return(int thread_handle, int value)
 *
 * Placed in hs.c rather than players.c (where kb groups 0xbefd0) per the same
 * lift directive as the twin: players.c does not compile under VC71 (clang-only
 * __attribute__ / raw fnptr casts), so it would be permanently unmeasurable
 * there. */
void FUN_000befd0(int16_t function_index, int thread_datum, char init)
{
  int *result;

  result =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (result != NULL) {
    unit_stop_custom_animation(result[0]);
    hs_return(thread_datum, 0);
  }
}


void FUN_000bf110(int16_t function_index, int thread_datum, char init)
{
  int *result;
  union {
    int i;
    unsigned char b;
  } value;

  value.i = 0;
  result =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (result != NULL) {
    value.b = (unsigned char)FUN_001ac150(result[0]);
    hs_return(thread_datum, value.i);
  }
}


void FUN_000bf340(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    FUN_001b5500(record[0]);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000bf380 (0xbf380) — readable C lift (HS eval wrapper). */
void FUN_000bf380(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_001a7a90(args[0], *(float *)&args[1], *(float *)&args[2]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000bf3d0 (0xbf3d0) — readable C lift (HS eval wrapper). */
void FUN_000bf3d0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_001a7ad0(args[0], *(float *)&args[1], *(float *)&args[2]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000bf420 (0xbf420) — readable C lift (HS eval wrapper). */
void FUN_000bf420(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_001a7b50(args[0], *(float *)&args[1], *(float *)&args[2]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000bf470 (0xbf470) — readable C lift (HS eval wrapper). */
void FUN_000bf470(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_001a7c70(args[0], *(float *)&args[1], *(float *)&args[2]);
  }
  hs_return(thread_datum, 0);
}

void FUN_000bf560(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    scripting_set_magic_base_seat((const char *)record[0]);
    hs_return(thread_datum, 0);
  }
}


void FUN_000bf600(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    hs_return(thread_datum, unit_scripting_unit_riders(record[0]));
  }
}


void FUN_000bf640(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    hs_return(thread_datum, FUN_001a9ec0(record[0]));
  }
}


void FUN_000bf680(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    hs_return(thread_datum, FUN_001a9ef0(record[0]));
  }
}


void FUN_000bf6c0(int16_t function_index, int thread_datum, char init)
{
  int *record;
  float value;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    value = FUN_001a7cc0(record[0]);
    hs_return(thread_datum, *(int *)&value);
  }
}


void FUN_000bf700(int16_t function_index, int thread_datum, char init)
{
  int *record;
  float value;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    value = FUN_001a7d00(record[0]);
    hs_return(thread_datum, *(int *)&value);
  }
}


void FUN_000bf740(int16_t function_index, int thread_datum, char init)
{
  int *record;
  union {
    unsigned short w;
    int i;
  } value;

  value.i = 0;
  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    value.w = (unsigned short)FUN_001a7d40(record[0]);
    hs_return(thread_datum, value.i);
  }
}


void FUN_000bf830(int16_t function_index, int thread_datum, char init)
{
  int *result;

  result =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (result != NULL) {
    unit_scripting_doesnt_drop_items(result[0]);
    hs_return(thread_datum, 0);
  }
}


void FUN_000bf9a0(int16_t function_index, int thread_datum, char init)
{
  int *record;
  union {
    unsigned char b;
    int i;
  } value;

  value.i = 0;
  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    value.b = (unsigned char)unit_get_current_flashlight_state(record[0]);
    hs_return(thread_datum, value.i);
  }
}


void FUN_000bfa70(int16_t function_index, int thread_datum, char init)
{
  int *record;
  union {
    float f;
    int dw;
  } value;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    value.f = device_get_power(record[0]);
    hs_return(thread_datum, value.dw);
  }
}


void FUN_000bfb00(int16_t function_index, int thread_datum, char init)
{
  int *record;
  union {
    float f;
    int i;
  } value;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    value.f = device_get_position(record[0]);
    hs_return(thread_datum, value.i);
  }
}


void FUN_000bfb80(int16_t function_index, int thread_datum, char init)
{
  unsigned short *record;
  union {
    float f;
    int i;
  } value;

  record = (unsigned short *)hs_macro_function_evaluate(function_index,
                                                        thread_datum, init);
  if (record != NULL) {
    value.f = device_group_get_value((int)record[0]);
    hs_return(thread_datum, value.i);
  }
}


void FUN_000bfdd0(int16_t function_index, int thread_datum, char init)
{
  uint16_t *record;

  record =
    (uint16_t *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    cheat_active_camouflage_local_player((int)*record);
    hs_return(thread_datum, 0);
  }
}


void FUN_000bfe30(int16_t function_index, int thread_datum, char init)
{
  uint8_t *record;

  record =
    (uint8_t *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    ai_globals_ai_active((char)*record);
    hs_return(thread_datum, 0);
  }
}


void FUN_000bfe70(int16_t function_index, int thread_datum, char init)
{
  uint8_t *record;

  record =
    (uint8_t *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    ai_globals_dialogue_triggers_enabled((char)*record);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000bfeb0 (0xbfeb0) — readable C lift (HS eval wrapper). */
void FUN_000bfeb0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    ai_globals_grenades_enabled((char)(unsigned char)args[0]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000bfef0 (0xbfef0) — readable C lift (HS eval wrapper). */
void FUN_000bfef0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000575d0(args[0]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000bff30 (0xbff30) — readable C lift (HS eval wrapper). */
void FUN_000bff30(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000576a0(args[0]);
  }
  hs_return(thread_datum, 0);
}

void FUN_000c0030(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    FUN_00054ac0(record[0]);
    hs_return(thread_datum, 0);
  }
}


void FUN_000c0070(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    FUN_00054b20(record[0]);
    hs_return(thread_datum, 0);
  }
}


void FUN_000c00b0(int16_t function_index, int thread_datum, char init)
{
  unsigned int *record;

  record = (unsigned int *)hs_macro_function_evaluate(function_index,
                                                      thread_datum, init);
  if (record != NULL) {
    FUN_00054bb0(record[0]);
    hs_return(thread_datum, 0);
  }
}


void FUN_000c00f0(int16_t function_index, int thread_datum, char init)
{
  unsigned int *record;

  record = (unsigned int *)hs_macro_function_evaluate(function_index,
                                                      thread_datum, init);
  if (record != NULL) {
    FUN_00054ca0(record[0]);
    hs_return(thread_datum, 0);
  }
}


void FUN_000c0130(int16_t function_index, int thread_datum, char init)
{
  unsigned int *record;

  record = (unsigned int *)hs_macro_function_evaluate(function_index,
                                                      thread_datum, init);
  if (record != NULL) {
    FUN_00054d00(record[0]);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000c0170 (0xc0170) — readable C lift (HS eval wrapper). */
void FUN_000c0170(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00054d60(args[0]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c01d0 (0xc01d0) — readable C lift (HS eval wrapper). */
void FUN_000c01d0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00054e40(args[0]);
  }
  hs_return(thread_datum, 0);
}

void FUN_000c0230(int16_t function_index, int thread_datum, char init)
{
  unsigned int *record;

  record = (unsigned int *)hs_macro_function_evaluate(function_index,
                                                      thread_datum, init);
  if (record != NULL) {
    FUN_00054e80(record[0]);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000c0370 (0xc0370) — readable C lift (HS macro-eval wrapper). */
void FUN_000c0370(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00058a40(args[0]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c0430 (0xc0430) — readable C lift (HS eval wrapper). */
void FUN_000c0430(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00055220(args[0]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c0470 (0xc0470) — readable C lift (HS eval wrapper). */
void FUN_000c0470(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000552b0(args[0]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c04b0 (0xc04b0) — readable C lift (HS eval wrapper). */
void FUN_000c04b0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00055750(args[0]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c04f0 (0xc04f0) — readable C lift (HS eval wrapper). */
void FUN_000c04f0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000557e0(args[0]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c0530 (0xc0530) — readable C lift (HS eval wrapper). */
void FUN_000c0530(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00058ae0(args[0]);
  }
  hs_return(thread_datum, 0);
}

void FUN_000c0570(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    FUN_00055870(record[0]);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000c07b0 (0xc07b0) — readable C lift (HS eval wrapper). */
void FUN_000c07b0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000568e0(args[0]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c08f0 (0xc08f0) — readable C lift (HS eval wrapper). */
void FUN_000c08f0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056de0(args[0]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c0930 (0xc0930) — readable C lift (HS eval wrapper). */
void FUN_000c0930(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056d80(args[0]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c0970 (0xc0970) — readable C lift (HS eval wrapper). */
void FUN_000c0970(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00058d40(args[0]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c09b0 (0xc09b0) — readable C lift (HS eval wrapper). */
void FUN_000c09b0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056e40(args[0]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c0a30 (0xc0a30) — readable C lift (HS eval wrapper). */
void FUN_000c0a30(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056fa0(args[0]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c0af0 (0xc0af0) — readable C lift (HS eval wrapper). */
void FUN_000c0af0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00057230(args[0]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c0b30 (0xc0b30) — readable C lift (HS eval wrapper). */
void FUN_000c0b30(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000572c0(args[0]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000be6f0 @ 0x000be6f0
 *
 * HaloScript builtin implementation. Unlike the surrounding function-evaluator
 * wrappers this does not call hs_macro_function_evaluate: it stops the numeric
 * countdown timer directly, then completes the calling script thread with
 * hs_return(thread_handle, 0).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP):
 *   function_index  int16_t  [EBP+0x08]  (unused -- never loaded)
 *   thread_handle   int      [EBP+0x0c]  -> hs_return arg1
 *
 * numeric_countdown_timer_stop() takes no args. The second stack param is
 * loaded (MOV EAX,[EBP+0xc]) and pushed as hs_return's thread_handle; the
 * constant 0 is pushed as hs_return's value (PUSH 0; PUSH EAX; CALL; ADD
 * ESP,8). Ghidra modeled this void(void); the [EBP+0xc] read of the second
 * cdecl param is unmodeled there (kb decl was previously void(void)). */
void FUN_000be6f0(int16_t function_index, int thread_handle)
{
  numeric_countdown_timer_stop();
  hs_return(thread_handle, 0);
}


/* FUN_000be710 @ 0x000be710
 *
 * HaloScript builtin implementation (restart variant of FUN_000be6f0). Like its
 * neighbor it does not call hs_macro_function_evaluate: it restarts the numeric
 * countdown timer directly, then completes the calling script thread with
 * hs_return(thread_handle, 0).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP):
 *   function_index  int16_t  [EBP+0x08]  (unused -- never loaded)
 *   thread_handle   int      [EBP+0x0c]  -> hs_return arg1
 *
 * numeric_countdown_timer_restart() takes no args. The second stack param is
 * loaded (MOV EAX,[EBP+0xc]) and pushed as hs_return's thread_handle; the
 * constant 0 is pushed as hs_return's value (PUSH 0; PUSH EAX; CALL; ADD
 * ESP,8). Ghidra modeled this void(void) and read only in_stack_00000008 (the
 * second cdecl param); kb decl was previously void(void). */
void FUN_000be710(int16_t function_index, int thread_handle)
{
  numeric_countdown_timer_restart();
  hs_return(thread_handle, 0);
}


/* FUN_000be970 @ 0x000be970
 *
 * HaloScript builtin implementation. Dumps the object subsystem's memory
 * state via objects_dump_memory(), then completes the calling script thread
 * with hs_return(thread_handle, 0).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP):
 *   function_index  int16_t  [EBP+0x08]  (unused -- never loaded)
 *   thread_handle   int      [EBP+0x0c]  -> hs_return arg1
 *
 * objects_dump_memory() takes no args. The second stack param is loaded
 * (MOV EAX,[EBP+0xc]) and pushed as hs_return's thread_handle; the constant 0
 * is pushed as hs_return's value (PUSH 0; PUSH EAX; CALL; ADD ESP,8). Ghidra
 * modeled this void(void) and read only in_stack_00000008 (the second cdecl
 * param); kb decl was previously void(void). */
void FUN_000be970(int16_t function_index, int thread_handle)
{
  objects_dump_memory();
  hs_return(thread_handle, 0);
}


/* 0xbea90 — HS script command handler: force a full garbage-collection pass,
 * then return void to the calling HS thread. This is the `garbage_collect`
 * scripting command; unlike the hs_evaluate_* handlers it takes no macro
 * arguments, so it ignores function_index (arg 1) and init (arg 3) and reads
 * only thread_datum (arg 2) to route the return.
 *
 * ABI (verified against delinked disassembly 0xbea90): cdecl, plain RET.
 * Prologue PUSH EBP;MOV EBP,ESP, then CALL garbage_collect_now (no args),
 * MOV EAX,[EBP+0xc] (thread_datum, the 2nd cdecl slot), PUSH 0; PUSH EAX;
 * CALL hs_return; ADD ESP,0x8 (hs_return's 2 args); POP EBP; RET. Side-effect
 * order preserved: GC runs before the return.
 *
 * Callees (both cdecl, in kb.json):
 *   0x13db50 = garbage_collect_now(void)
 *   0xcbf80  = hs_return(int thread_handle, int value) */
void FUN_000bea90(int16_t function_index, int thread_datum, char init)
{
  garbage_collect_now();
  hs_return(thread_datum, 0);
}


/* FUN_000bec70 @ 0x000bec70
 *
 * HaloScript builtin implementation, a direct sibling of the numeric-countdown
 * wrappers above (FUN_000be6f0 / FUN_000be710). It does not call
 * hs_macro_function_evaluate: it invokes the void/void helper FUN_0013dcb0
 * directly, then completes the calling script thread with
 * hs_return(thread_handle, 0).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP):
 *   function_index  int16_t  [EBP+0x08]  (unused -- never loaded)
 *   thread_handle   int      [EBP+0x0c]  -> hs_return arg1
 *
 * FUN_0013dcb0() takes no args and is called first. The second stack param is
 * then loaded (MOV EAX,[EBP+0xc]) and pushed as hs_return's thread_handle; the
 * constant 0 is pushed as hs_return's value (PUSH 0; PUSH EAX; CALL hs_return;
 * ADD ESP,8 cleans the two cdecl args). Ghidra modeled this void(void) and read
 * the second cdecl param as in_stack_00000008 (mislabeled -- it is [EBP+0xc]);
 * kb decl was previously void(void). */
void FUN_000bec70(int16_t function_index, int thread_handle)
{
  FUN_0013dcb0();
  hs_return(thread_handle, 0);
}


/* FUN_000bf5e0 @ 0xbf5e0 -- HS script-function wrapper, zero-argument variant
 *   (10 instructions, bare EBP frame, no SUB ESP, no locals, no FPU).
 *
 * Signature (Confirmed by disassembly + family shape): the hs script function
 * dispatch table calls every entry as
 *   void (*)(int16_t function_index, int thread_datum, char init)
 * Only thread_datum ([EBP+0xc]) is read here:
 *   MOV EAX,[EBP+0xc]   -- plain full-width MOV, no MOVZX/MOVSX
 *   PUSH 0x0 / PUSH EAX -- cdecl reverse order -> hs_return(thread_datum, 0)
 *   ADD ESP,0x8         -- exactly 2 stack args, no merged cleanup here
 * function_index and init are never touched: this is a zero-argument script
 * function, so there is NO hs_macro_function_evaluate call, no argument
 * record, and consequently no NULL check (unlike the 1-/2-argument twins
 * above).  The 3-arg cdecl decl is still required so the table dispatch ABI
 * matches its twins.
 *
 * Ghidra modelled this void(void), so the cdecl params surfaced as
 * in_stack_00000008 (off by 4 => [EBP+0xc]); they are STACK args, not
 * (lift-learnings 31 / void-decl trap).  kb.json's decl was corrected from
 * `void(void)` to the 3-arg cdecl form as part of this lift.
 *
 * Callees (both cdecl, in kb.json, no args):
 *   0x1b2260 = scripting_magic_melee_attack(void)  -- no args, no ADD ESP
 *   0xcbf80  = hs_return(int thread_handle, int value) */
void FUN_000bf5e0(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;

  scripting_magic_melee_attack();
  hs_return(thread_datum, 0);
}


void FUN_000bf8f0(int16_t function_index, int thread_datum, char init)
{
  union {
    unsigned char b;
    int i;
  } value;

  value.i = 0;
  value.b = (unsigned char)unit_solo_player_integrated_night_vision_is_active();
  hs_return(thread_datum, value.i);
}


void FUN_000bfd10(int16_t function_index, int thread_datum, char init)
{
  breakable_surfaces_reset();
  hs_return(thread_datum, 0);
}


/* FUN_000bfd30 (0xbfd30) — readable C lift (thin wrapper). */
void FUN_000bfd30(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  FUN_000a6b50();
  hs_return(thread_datum, 0);
}

void FUN_000bfd50(int16_t function_index, int thread_datum, char init)
{
  FUN_000a6a80();
  hs_return(thread_datum, 0);
}


/* FUN_000bfd70 (0xbfd70) — readable C lift (thin wrapper). */
void FUN_000bfd70(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  FUN_000a6ba0();
  hs_return(thread_datum, 0);
}

void FUN_000bfd90(int16_t function_index, int thread_datum, char init)
{
  cheat_teleport_to_camera();
  hs_return(thread_datum, 0);
}


void FUN_000bfdb0(int16_t function_index, int thread_datum, char init)
{
  cheat_all_powerups();
  hs_return(thread_datum, 0);
}


void FUN_000bfe10(int16_t function_index, int thread_datum, char init)
{
  cheats_load_from_file();
  hs_return(thread_datum, 0);
}


/* FUN_000c01b0 (0xc01b0) — readable C lift (thin wrapper). */
void FUN_000c01b0(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  FUN_00054df0();
  hs_return(thread_datum, 0);
}

/* FUN_000c0210 (0xc0210) — readable C lift (thin wrapper). */
void FUN_000c0210(int16_t function_index, int thread_datum, char init)
{
  (void)function_index;
  (void)init;
  FUN_00054e20();
  hs_return(thread_datum, 0);
}

/* 0xbdfe0 — HS script function handler: evaluate a macro function and, on a
 * non-null result record, forward a cluster index + object handle to
 * FUN_0018ef00, then commit that call's boolean result to the calling HS
 * thread. Same evaluator ABI (function_index, thread_datum, init) as the other
 * hs_evaluate_* handlers.
 *
 * ABI (verified against disassembly 0xbdfe0): cdecl, plain RET. thread_datum
 * (arg 2, cached in ESI) flows to both the evaluate call (arg 2) and the
 * hs_return call (arg 1). On a non-null result the call site reads
 * MOVSX EAX,word[result+0] (SIGNED int16 -> int cluster index) and
 * MOV EDX,dword[result+4] (full int object handle), then PUSH EDX; PUSH EAX;
 * CALL 0x18ef00 -> char in AL. AL is MOVZX-widened into local_8 and becomes
 * hs_return's value arg. The combined ADD ESP,0x10 after the two trailing calls
 * (18ef00's 2 + hs_return's 2) confirms the arg counts. Note result[+0] is a
 * SIGNED int16 (MOVSX), so (int)*result on a short* must stay signed;
 * result[+4] is a full int (dword), unlike the narrow int16 +4 read in
 * FUN_000bdfa0.
 *
 * Callees (all cdecl, in kb.json):
 *   0xcc560 = hs_macro_function_evaluate(int16 fn_index, int thread_datum,
 *             char init) -> int* (result record, NULL on failure)
 *   0x18ef00 = FUN_0018ef00(int cluster_index, int object_handle) -> char
 *   0xcbf80 = hs_return(int thread_handle, int value) */
void FUN_000bdfe0(int16_t function_index, int thread_datum, char init)
{
  short *result;
  unsigned char eval_result;

  result =
    (short *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (result != NULL) {
    eval_result =
      (unsigned char)FUN_0018ef00((int)*result, *(int *)(result + 2));
    hs_return(thread_datum, (int)eval_result);
  }
}


/* 0xbe030 — HS script function handler: evaluate a macro function and commit a
 * byte predicate result to the calling HS thread. Evaluates the macro
 * arguments via hs_macro_function_evaluate; on a non-null result record, reads
 * a signed int16 at +0x0 (MOVSX word ptr) and an int at +0x4, passes both to
 * FUN_000ca0f0 (returns a byte in AL), zero-extends that byte and returns it to
 * the thread via hs_return. The dword result slot is pre-zeroed and only the
 * low byte is written (zero-init-then-narrow-store idiom) — modeled with a
 * union so the widened value is the zero-extended byte.
 *
 * ABI (verified against disassembly 0xbe030): cdecl, plain RET. thread_datum
 * (arg 2, cached in ESI) flows to both the evaluate call (arg 2) and the
 * hs_return call (arg 1). Result record: int16 @ +0x0 (signed load), int @
 * +0x4. Callees: 0xcc560 = hs_macro_function_evaluate(int16 fn_index, int
 * thread_datum, char init) -> short* (result record, NULL on failure) 0xca0f0 =
 * FUN_000ca0f0(int16_t word0, int dword4) -> unsigned char 0xcbf80 =
 * hs_return(int thread_handle, int value) */
void FUN_000be030(int16_t function_index, int thread_datum, char init)
{
  short *result;
  union {
    int i;
    unsigned char b;
  } value;

  result =
    (short *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (result != NULL) {
    value.i = 0;
    value.b = FUN_000ca0f0(*result, *(int *)(result + 2));
    hs_return(thread_datum, value.i);
  }
}


/* 0xbe080 — HaloScript macro-function call wrapper. Evaluates a macro
 * function expression on a thread; if the evaluation yields a result node,
 * runs it through FUN_000ca050 (a value/cast evaluator returning a byte in
 * AL) and returns that byte on the calling thread via hs_return.
 *
 * players.obj groups this function, but it calls hs_runtime.obj's static
 * hs_macro_function_evaluate / hs_return, so it is co-located here (in the
 * original binary those callees have external linkage; the lift marks them
 * static, so a cross-TU call from players.c would not link). maintain.py
 * relocates this to players.c — that move must be reverted.
 *
 * Plain cdecl (caller cleans, RET no immediate). Three stack params:
 *   param1 @ EBP+0x8  = function_index (int16_t)
 *   param2 @ EBP+0xc  = thread_datum
 *   param3 @ EBP+0x10 = init (char)
 *
 * Callees (all in kb.json):
 *   0xcc560 = hs_macro_function_evaluate(function_index, thread_datum, init)
 *             -> result node ptr (Ghidra's `int` is really a struct*; NULL
 *                when there is nothing to return)
 *   0xca050 = FUN_000ca050(int16 result[+0], int result[+0x4]) -> byte in AL
 *   0xcbf80 = hs_return(thread_datum, value)
 *
 * Result node layout (EAX from call 1, only read when nonzero):
 *   +0x0 (int16_t) : MOVSX'd and passed as FUN_000ca050 arg1
 *   +0x4 (int32_t) : passed as FUN_000ca050 arg2
 * The returned byte is written into a pre-zeroed dword local (only AL stored),
 * so it is zero-extended (uint8 -> int) before being handed to hs_return.
 */
void FUN_000be080(int16_t function_index, int thread_datum, char init)
{
  int *result;
  int value;

  value = 0;
  result =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (result != 0) {
    *(unsigned char *)&value = FUN_000ca050(*(int16_t *)result, result[1]);
    hs_return(thread_datum, value);
  }
}


/* 0xbe270 — HS built-in evaluator, sibling of FUN_000be1d0 / FUN_000be210.
 * Evaluates a single macro-function via hs_macro_function_evaluate; while
 * that returns NULL the evaluation is still pending and nothing is committed
 * this call. Once it yields a non-NULL result datum, its first dword and its
 * zero-extended 16-bit field at +0x4 are handed to FUN_000ca3f0, then the
 * thread is committed with hs_return(thread_datum, 0). Standard evaluator ABI
 * (function_index, thread_datum, init), plain cdecl (caller cleans).
 *
 * Disasm evidence (0xbe28c..0xbe29e): after TEST EAX,EAX / JZ, the non-NULL
 * path does `XOR EDX,EDX; MOV DX,[EAX+0x4]` (u16 zero-extend) and
 * `MOV EAX,[EAX]` (dword), then PUSH EDX; PUSH EAX; CALL 0xca3f0 — i.e.
 * FUN_000ca3f0(record[0], (u16)record->field_0x4). The single trailing
 * ADD ESP,0x10 folds the cleanup of BOTH this 2-arg call and the following
 * 2-arg hs_return(thread_datum, 0). (The prefetch decomp modeled ca3f0 as
 * void/void and dropped both args — corrected here from the binary.)
 *
 * Callees:
 *   0xcc560 = hs_macro_function_evaluate(function_index, thread_datum, init)
 *             -> result node ptr in EAX (NULL while evaluation pending)
 *   0xca3f0 = FUN_000ca3f0(int, int) — 2-arg cdecl (reads [EBP+8],[EBP+c])
 *   0xcbf80 = hs_return(thread_datum, 0)
 */
void FUN_000be270(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != 0) {
    FUN_000ca3f0(record[0], *(unsigned short *)((char *)record + 4));
    hs_return(thread_datum, 0);
  }
}


/* 0xbe2b0 — HS built-in evaluator, sibling of FUN_000be270 above. Evaluates a
 * single macro-function via hs_macro_function_evaluate; while that returns
 * NULL the evaluation is still pending and nothing is committed this call.
 * Once it yields a non-NULL result datum, its first dword and its zero-extended
 * 16-bit field at +0x4 are handed to FUN_000ca410, then the thread is committed
 * with hs_return(thread_datum, 0). Standard evaluator ABI (function_index,
 * thread_datum, init), plain cdecl (caller cleans).
 *
 * Disasm evidence: after TEST EAX,EAX / JZ, the non-NULL path does
 * `XOR EDX,EDX; MOV DX,[EAX+0x4]` (u16 zero-extend) and `MOV EAX,[EAX]`
 * (dword), then PUSH EDX; PUSH EAX; CALL 0xca410 — i.e.
 * FUN_000ca410(record[0], (u16)record->field_0x4). The single trailing
 * ADD ESP,0x10 folds the cleanup of BOTH this 2-arg call and the following
 * 2-arg hs_return(thread_datum, 0). (The prefetch decomp modeled ca410 as
 * void/void and dropped both args — corrected here from the binary.)
 *
 * Callees:
 *   0xcc560 = hs_macro_function_evaluate(function_index, thread_datum, init)
 *             -> result node ptr in EAX (NULL while evaluation pending)
 *   0xca410 = FUN_000ca410(int, int) — 2-arg cdecl (reads [EBP+8],[EBP+c])
 *   0xcbf80 = hs_return(thread_datum, 0)
 */
void FUN_000be2b0(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != 0) {
    FUN_000ca410(record[0], *(unsigned short *)((char *)record + 4));
    hs_return(thread_datum, 0);
  }
}


/* 0xbe330 — HS script function handler: evaluate a macro function and, on a
 * non-null result record, forward the record's first three dwords (at +0x0,
 * +0x4, +0x8) to FUN_000c9c80, then commit a 0 result to the calling HS
 * thread. No value is read back from the callee — hs_return always commits 0.
 * Same evaluator ABI (function_index, thread_datum, init) as the other
 * hs_evaluate_* handlers.
 *
 * ABI (verified against disassembly 0xbe330): cdecl, plain RET. thread_datum
 * (arg 2, cached in ESI) flows to both the evaluate call (arg 2) and the
 * hs_return call (arg 1). On a non-null result the call site does
 * MOV EDX,[result+0x8]; MOV ECX,[result+0x4]; MOV EDX,[result+0x0], then
 * PUSH EDX(+8); PUSH ECX(+4); PUSH EDX(+0); CALL 0xc9c80 — three cdecl int
 * args. Ghidra's void(void) decl for 0xc9c80 dropped all three, misled by the
 * combined ADD ESP,0x14 after the two trailing calls (0xc9c80's 3 args = 0xc
 * plus hs_return's 2 args = 0x8). kb.json decl for 0xc9c80 corrected to
 * void(int,int,int) accordingly.
 *
 * Callees (all cdecl, in kb.json):
 *   0xcc560 = hs_macro_function_evaluate(int16 fn_index, int thread_datum,
 *             char init) -> int* (result record, NULL on failure)
 *   0xc9c80 = FUN_000c9c80(int, int, int) -> void (record 3-dword consumer)
 *   0xcbf80 = hs_return(int thread_handle, int value) */
void FUN_000be330(int16_t function_index, int thread_datum, char init)
{
  int *result;

  result =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (result != NULL) {
    FUN_000c9c80(result[0], result[1], result[2]);
    hs_return(thread_datum, 0);
  }
}


/* 0xbe370 — HS script function handler: evaluate a macro function and, on a
 * non-null result record, forward the record's first dword (+0x0) and a
 * narrow unsigned int16 (+0x4) to FUN_000c9bd0, then commit that callee's
 * return value to the calling HS thread. Unlike the handlers that always
 * commit 0, this one reads FUN_000c9bd0's EAX result and passes it to
 * hs_return. Same evaluator ABI (function_index, thread_datum, init) as the
 * other hs_evaluate_* handlers.
 *
 * ABI (verified against disassembly 0xbe370): cdecl, plain RET. thread_datum
 * (arg 2, cached in ESI) flows to both the evaluate call (arg 2) and the
 * hs_return call (arg 1). On a non-null result the call site does
 * MOVZX EDX,word[result+0x4] (UNSIGNED int16 -> int) and MOV EAX,dword[result]
 * (full int), then PUSH EDX; PUSH EAX; CALL 0xc9bd0 -> int in EAX. That EAX is
 * the value arg to hs_return. The combined ADD ESP,0x10 after the two trailing
 * calls (0xc9bd0's 2 + hs_return's 2) confirms the arg counts. Ghidra's
 * void(void) decl for 0xc9bd0 dropped both args; kb.json decl corrected to
 * int(int,int) accordingly. result is int*, so the +0x4 read is at
 * (char *)result + 4, a narrow unsigned int16 (MOVZX).
 *
 * Callees (all cdecl, in kb.json):
 *   0xcc560 = hs_macro_function_evaluate(int16 fn_index, int thread_datum,
 *             char init) -> int* (result record, NULL on failure)
 *   0xc9bd0 = FUN_000c9bd0(int value, int type) -> int (coerced value)
 *   0xcbf80 = hs_return(int thread_handle, int value) */
void FUN_000be370(int16_t function_index, int thread_datum, char init)
{
  int *result;
  int value;

  result =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (result != NULL) {
    value = FUN_000c9bd0(result[0], *(unsigned short *)((char *)result + 4));
    hs_return(thread_datum, value);
  }
}


/* player_rumble_initialize @ 0x000be400
 *
 * HaloScript function-evaluator wrapper. Evaluates the script function via
 * hs_macro_function_evaluate(function_index, thread_handle, init); on a
 * non-NULL evaluation record it forwards the two record fields to FUN_000c9de0
 * and completes the thread with hs_return(thread_handle, 0).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP; PUSH ESI):
 *   function_index  int16_t  [EBP+0x08]
 *   thread_handle   int      [EBP+0x0c]  (held in ESI)
 *   init            char     [EBP+0x10]
 *
 * hs_macro_function_evaluate returns an evaluation-record pointer in EAX.
 * When non-NULL the original loads EAX+0x00 as a full dword and EAX+0x04 as a
 * MOVZX (zero-extended) 16-bit field, then pushes them right-to-left
 * (PUSH EDX=+0x04; PUSH EAX_val=+0x00). FUN_000c9de0's 2-arg cdecl signature is
 * recovered from this call site (its kb decl was previously void(void)). */
void player_rumble_initialize(int16_t function_index, int thread_handle,
                              char init)
{
  int record;

  record = hs_macro_function_evaluate(function_index, thread_handle, init);
  if (record != 0) {
    FUN_000c9de0(*(int *)record, *(uint16_t *)(record + 4));
    hs_return(thread_handle, 0);
  }
}


/* FUN_000be440 @ 0x000be440
 *
 * HaloScript function-evaluator wrapper, sibling of player_rumble_initialize
 * above. Evaluates the script function via
 * hs_macro_function_evaluate(function_index, thread_datum, init); while that
 * returns NULL the evaluation is still pending and nothing is committed. Once
 * it yields a non-NULL evaluation record, the record's first three dwords
 * (offsets +0x00, +0x04, +0x08) are forwarded to FUN_000c9e50, then the thread
 * is committed with hs_return(thread_datum, 0). Standard evaluator ABI
 * (function_index, thread_datum, init), plain cdecl (caller cleans).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP; PUSH ESI):
 *   function_index  int16_t  [EBP+0x08]  -> hs_macro_function_evaluate arg1
 *   thread_datum    int      [EBP+0x0c]  (held in ESI) -> arg2; reused for
 *                                          hs_return arg1
 *   init            char     [EBP+0x10]  -> arg3
 *
 * hs_macro_function_evaluate returns the record pointer in EAX. On the non-NULL
 * branch (TEST EAX,EAX / JZ) the original loads three dwords and pushes them
 * right-to-left (MOV EDX,[EAX+8]; MOV ECX,[EAX+4]; MOV EDX,[EAX];
 * PUSH [EAX+8]; PUSH [EAX+4]; PUSH [EAX]) -> FUN_000c9e50(result[0],
 * result[1], result[2]). The single trailing ADD ESP,0x14 folds the cleanup of
 * BOTH this 3-arg call (0xc) and the following 2-arg hs_return(thread_datum, 0)
 * (0x8). Ghidra modeled hs_macro_function_evaluate's return as a plain int and
 * FUN_000c9e50 as void(void), dropping all three args; both are corrected here
 * from the binary (return is a >=12-byte record pointer; FUN_000c9e50 is
 * 3-arg cdecl). */
void FUN_000be440(int16_t function_index, int thread_datum, char init)
{
  int *result;

  result =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (result != NULL) {
    FUN_000c9e50(result[0], result[1], result[2]);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000be480 @ 0x000be480
 *
 * HaloScript function-evaluator wrapper, sibling of FUN_000be440 above.
 * Evaluates the script function via hs_macro_function_evaluate(function_index,
 * thread_datum, init); while that returns NULL the evaluation is still pending
 * and nothing is committed. Once it yields a non-NULL evaluation record, two
 * fields of the record are forwarded to FUN_000c9ec0 and the thread is then
 * committed with hs_return(thread_datum, 0). Standard evaluator ABI
 * (function_index, thread_datum, init), plain cdecl (caller cleans).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP; PUSH ESI):
 *   function_index  int16_t  [EBP+0x08]  -> hs_macro_function_evaluate arg1
 *   thread_datum    int      [EBP+0x0c]  (held in ESI) -> arg2; reused for
 *                                          hs_return arg1
 *   init            char     [EBP+0x10]  -> arg3
 *
 * hs_macro_function_evaluate returns the record pointer in EAX. On the non-NULL
 * branch (TEST EAX,EAX / JZ) the original reads a zero-extended 16-bit field
 * and the leading dword and pushes them right-to-left:
 *   XOR EDX,EDX; MOV DX,[EAX+4]; MOV EAX,[EAX]; PUSH EDX; PUSH EAX
 *   -> FUN_000c9ec0(record[0], (uint16_t)record[+0x4]).
 * The single trailing ADD ESP,0x10 folds the cleanup of BOTH this 2-arg call
 * (0x8) and the following 2-arg hs_return(thread_datum, 0) (0x8). Ghidra
 * modeled hs_macro_function_evaluate's return as a plain int and FUN_000c9ec0
 * as void(void), dropping both args; both are corrected here from the binary
 * (return is a record pointer; FUN_000c9ec0 is 2-arg cdecl with a dword first
 * arg and a zero-extended 16-bit second arg). The +0x4 field is a 16-bit word
 * (MOVW / zero-extend), so it is read as uint16_t, not a full dword. */
void FUN_000be480(int16_t function_index, int thread_datum, char init)
{
  int *result;

  result =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (result != NULL) {
    FUN_000c9ec0(result[0], *(uint16_t *)((char *)result + 4));
    hs_return(thread_datum, 0);
  }
}


/* FUN_000be4c0 @ 0x000be4c0
 *
 * HaloScript macro-function evaluator wrapper (side-effect-only variant),
 * sibling of the FUN_000be440/FUN_000be480 evaluators above. Evaluates the
 * script function via hs_macro_function_evaluate(function_index, thread_datum,
 * init); while that returns NULL the evaluation is still pending and nothing is
 * committed. Unlike its siblings the returned record is NOT dereferenced -- on
 * a non-NULL result the wrapper only invokes the parameterless side-effect
 * routine FUN_000c9f30() and then commits the calling thread with
 * hs_return(thread_datum, 0).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP):
 *   function_index  int16_t  [EBP+0x08]  -> hs_macro_function_evaluate arg1
 *   thread_datum    int      [EBP+0x0c]  -> arg2; reused as hs_return arg1
 *   init            char     [EBP+0x10]  -> arg3
 *
 * hs_macro_function_evaluate returns the record pointer in EAX; only its
 * nonzero-ness is tested (TEST EAX,EAX / JZ). hs_return's two args are pushed
 * right-to-left (PUSH 0 = value; PUSH thread_datum = thread_handle). Ghidra
 * modeled this function as void(void) and dropped all three stack args; the
 * 3-arg cdecl signature is recovered from the hs_macro_function_evaluate call
 * site (its kb decl was previously the stub void FUN_000be4c0(void)). */
void FUN_000be4c0(int16_t function_index, int thread_datum, char init)
{
  int record;

  record = hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != 0) {
    FUN_000c9f30(0, 0);
    hs_return(thread_datum, 0);
  }
}


/* player_rumble_set_effect @ 0x000be770
 *
 * Misnomer: this is NOT controller rumble. It is a HaloScript builtin
 * dispatcher (recorded-animation playback) with the same shape as the
 * breakable-surfaces builtin above. Evaluates the script function via
 * hs_macro_function_evaluate(function_index, thread_datum, init); on a
 * non-NULL evaluation record it plays a recorded animation and completes the
 * calling script thread with hs_return(thread_datum, <result>).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP; PUSH ECX for one local):
 *   function_index  int16_t  [EBP+0x08]
 *   thread_datum    int      [EBP+0x0c]  -> reused for hs_return arg1
 *   init            char     [EBP+0x10]
 *
 * hs_macro_function_evaluate returns an evaluation-record pointer in EAX
 * (piVar2). The local [EBP-4] result slot is pre-zeroed (MOV dword[EBP-4],0)
 * before the call. When the record is non-NULL the original reads:
 *   record[0]  int    (actor handle, offset 0x00, full dword load)
 *   record[1]  int16  (anim index,  offset 0x04, zero-extended word load:
 *                       XOR EDX,EDX; MOV DX,[EAX+4])
 * and calls recorded_animation_play(record[0], (short)record[1]) (PUSH EDX;
 * PUSH EAX -> arg1=record[0], arg2=word@0x04). The char return in AL is stored
 * into the pre-zeroed dword slot, so the full value forwarded is the
 * zero-extended byte, and hs_return(thread_datum, (uint)result) completes the
 * thread (PUSH result; PUSH thread_datum; CALL; combined ADD ESP cleanup). */
void player_rumble_set_effect(int16_t function_index, int thread_datum,
                              char init)
{
  volatile unsigned short result_slot;
  int *record;
  unsigned int result;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    /* The original pre-zeroes the result dword and then stores only the byte
     * return (AL) into it. Routing the zero-extended char return through a
     * volatile stack slot reproduces that store-then-reload codegen shape. */
    result_slot = (unsigned char)recorded_animation_play(
      record[0], (short)((unsigned short *)record)[2]);
    result = (unsigned int)result_slot;
    hs_return(thread_datum, result);
  }
}


/* 0xbe7c0 — HS script function handler (recorded-animation play/delete
 * dispatcher), structurally identical to FUN_000be810. Evaluates the macro
 * arguments via hs_macro_function_evaluate(function_index, thread_datum,
 * init); on a non-NULL evaluation record it reads two record fields, calls the
 * byte-returning worker recorded_animation_play_and_delete, and completes the
 * calling HS thread with hs_return(thread_datum, <byte>).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP; PUSH ECX local; PUSH ESI):
 *   function_index  int16_t  [EBP+0x08]
 *   thread_datum    int      [EBP+0x0c]  -> held in ESI, reused for hs_return
 *   init            char     [EBP+0x10]
 *
 * The disassembly (NOT the supplied Ghidra pseudocode, which wrongly modeled
 * this void(void), called the worker as void(void) and read its return from a
 * bare extraout_AL — the classic void-EAX/dropped-arg trap) shows: the
 * [EBP-4] result slot is pre-zeroed before the evaluate call.
 * hs_macro_function_evaluate returns the record pointer in EAX; when non-NULL:
 *   record[0]  int    (offset 0x00, MOV EAX,[EAX])
 *   record.w4  int16  (offset 0x04, zero-extended: XOR EDX,EDX; MOV DX,[EAX+4])
 * and calls recorded_animation_play_and_delete(record[0], (short)record.w4)
 * (PUSH EDX; PUSH EAX -> arg1=record[0], arg2=word@0x04). The AL byte return
 * is stored into the pre-zeroed dword slot (MOV [EBP-4],AL), reloaded
 * (MOV ECX,[EBP-4]) and the zero-extended value forwarded to
 * hs_return(thread_datum, result) (PUSH value; PUSH thread_datum; CALL;
 * ADD ESP,0x10 — the two worker args and the two hs_return args cleaned
 * together). Callees (all cdecl, in kb.json):
 *   0xcc560 = hs_macro_function_evaluate(int16_t, int, char) -> record*
 *   0x95660 = recorded_animation_play_and_delete(int, short) -> char (AL)
 *   0xcbf80 = hs_return(int thread_handle, int value) */
void FUN_000be7c0(int16_t function_index, int thread_datum, char init)
{
  volatile unsigned short result_slot;
  int *record;
  unsigned int result;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    /* The original pre-zeroes the result dword and then stores only the byte
     * return (AL) into it. Routing the zero-extended char return through a
     * volatile stack slot reproduces that store-then-reload codegen shape. */
    result_slot = (unsigned char)recorded_animation_play_and_delete(
      record[0], (short)((unsigned short *)record)[2]);
    result = (unsigned int)result_slot;
    hs_return(thread_datum, result);
  }
}


/* FUN_000be810 @ 0x000be810
 *
 * HaloScript builtin dispatcher, structurally identical to the recorded-
 * animation builtin (player_rumble_set_effect) above. Evaluates the script
 * function via hs_macro_function_evaluate(function_index, thread_datum, init);
 * on a non-NULL evaluation record it reads two record fields, calls a byte-
 * returning worker, and completes the calling script thread with
 * hs_return(thread_datum, <byte>).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP; PUSH ECX for one local; PUSH ESI):
 *   function_index  int16_t  [EBP+0x08]
 *   thread_datum    int      [EBP+0x0c]  -> held in ESI, reused for hs_return
 *   init            char     [EBP+0x10]
 *
 * The disassembly (NOT the supplied Ghidra pseudocode, which wrongly modeled
 * this void(void) and dropped both worker arguments and the record derefs)
 * shows: the local [EBP-4] result slot is pre-zeroed (MOVL [EBP-4],0) before
 * the evaluate call. hs_macro_function_evaluate returns the record pointer in
 * EAX. When non-NULL the original reads:
 *   record[0]  int    (offset 0x00, full dword load: MOV EAX,[EAX])
 *   record.w4  int16  (offset 0x04, zero-extended word: XOR EDX,EDX; MOV
 * DX,[EAX+4]) and calls FUN_00095680(record[0], (short)record.w4) (PUSH EDX;
 * PUSH EAX -> arg1=record[0], arg2=word@0x04). The char return in AL is stored
 * into the pre-zeroed dword slot (MOV [EBP-4],AL), reloaded (MOV ECX,[EBP-4]),
 * and the zero-extended value forwarded to hs_return(thread_datum, result)
 * (PUSH value; PUSH thread_datum; CALL; ADD ESP,0x10). */
void FUN_000be810(int16_t function_index, int thread_datum, char init)
{
  volatile unsigned short result_slot;
  int *record;
  unsigned int result;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    /* The original pre-zeroes the result dword and then stores only the byte
     * return (AL) into it. Routing the zero-extended char return through a
     * volatile stack slot reproduces that store-then-reload codegen shape. */
    result_slot = (unsigned char)FUN_00095680(
      record[0], (short)((unsigned short *)record)[2]);
    result = (unsigned int)result_slot;
    hs_return(thread_datum, result);
  }
}


/* FUN_000bea50 (0xbea50) — readable C lift (HS eval wrapper). */
void FUN_000bea50(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    objects_scripting_detach(args[0], args[1]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000bed70 @ 0x000bed70
 *
 * HaloScript macro-function evaluator wrapper (animation-set variant), a direct
 * sibling of FUN_000bed20 above. Evaluates the script function via
 * hs_macro_function_evaluate(function_index, thread_datum, init); while that
 * returns NULL the evaluation is still pending and nothing is committed. Once a
 * non-NULL evaluation record is returned, its first three dwords are forwarded
 * to FUN_001457b0 (a cdecl helper that sets an object's animation state), then
 * the calling thread is completed with hs_return(thread_datum, 0).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP; PUSH ESI for thread_datum):
 *   function_index  int16_t  [EBP+0x08]  -> hs_macro_function_evaluate arg1
 *   thread_datum    int      [EBP+0x0c]  -> arg2; held in ESI, reused for
 *                                           hs_return arg1
 *   init            char     [EBP+0x10]  -> arg3
 *
 * hs_macro_function_evaluate returns the record pointer in EAX. On non-NULL the
 * original pushes the record's first three dwords in reverse
 * (PUSH [EAX+8]; PUSH [EAX+4]; PUSH [EAX]) and CALLs FUN_001457b0 with three
 * cdecl args = (record[0], record[1], record[2]); record[2] is an animation
 * name pointer (char *). The combined ADD ESP,0x14 after the two trailing calls
 * folds FUN_001457b0's 3-dword cleanup with hs_return's 2-dword cleanup
 * (3 + 2 = 5 dwords = 0x14), confirming both are cdecl. Ghidra modeled this
 * void(void); the three cdecl params were unmodeled (in_stack_*) and
 * FUN_001457b0's arguments were mis-declared void(void) (kb decl was previously
 * void(void) for both this function and FUN_001457b0). */
void FUN_000bed70(int16_t function_index, int thread_datum, char init)
{
  int *result;

  result =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (result != NULL) {
    FUN_001457b0(result[0], result[1], (int)(uintptr_t)(char *)result[2]);
    hs_return(thread_datum, 0);
  }
}


void FUN_000bf1a0(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    FUN_001ac070(record[0], (int)*(unsigned short *)(record + 1));
    hs_return(thread_datum, 0);
  }
}


void FUN_000bf220(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    unit_scripting_enter_vehicle(record[0], record[1], (char *)record[2]);
    hs_return(thread_datum, 0);
  }
}


void FUN_000bf260(int16_t function_index, int thread_datum, char init)
{
  int *record;
  union {
    int i;
    unsigned char b;
  } value;

  value.i = 0;
  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    value.b = FUN_001a9c90(record[0], (const char *)record[1], record[2]);
    hs_return(thread_datum, value.i);
  }
}


void FUN_000bf2b0(int16_t function_index, int thread_datum, char init)
{
  int *record;
  union {
    int i;
    unsigned char b;
  } value;

  value.i = 0;
  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    value.b = unit_scripting_vehicle_test_seat(
      record[0], (const char *)record[1], record[2]);
    hs_return(thread_datum, value.i);
  }
}


void FUN_000bf300(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    unit_scripting_set_emotion_animation(record[0], (const char *)record[1]);
    hs_return(thread_datum, 0);
  }
}


void FUN_000bf4c0(int16_t function_index, int thread_datum, char init)
{
  int *record;
  union {
    int i;
    unsigned short w;
  } value;

  value.i = 0;
  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    value.w = vehicle_scripting_load_magic(record[0], record[1], record[2]);
    hs_return(thread_datum, value.i);
  }
}


void FUN_000bf510(int16_t function_index, int thread_datum, char init)
{
  int *record;
  union {
    int i;
    unsigned short w;
  } value;

  value.i = 0;
  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    value.w = FUN_001b5400(record[0], record[1]);
    hs_return(thread_datum, value.i);
  }
}


void FUN_000bf5a0(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    unit_scripting_set_seat(record[0], (const char *)record[1]);
    hs_return(thread_datum, 0);
  }
}


void FUN_000bf790(int16_t function_index, int thread_datum, char init)
{
  int *record;
  union {
    int i;
    unsigned char b;
  } value;

  value.i = 0;
  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    value.b = FUN_001a7e70(record[0], record[1]);
    hs_return(thread_datum, value.i);
  }
}


void FUN_000bf7e0(int16_t function_index, int thread_datum, char init)
{
  int *record;
  union {
    int i;
    unsigned char b;
  } value;

  value.i = 0;
  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    value.b = FUN_001a7ea0(record[0], record[1]);
    hs_return(thread_datum, value.i);
  }
}


void FUN_000bff70(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    FUN_00054860(record[0], (unsigned int)record[1]);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000bffb0 (0xbffb0) — readable C lift (HS eval wrapper). */
void FUN_000bffb0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    ai_profile_change_render_spray(args[0], (unsigned int)args[1]);
  }
  hs_return(thread_datum, 0);
}

void FUN_000bfff0(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    FUN_00057770((unsigned int)record[0], record[1]);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000c0330 (0xc0330) — readable C lift (HS eval wrapper). */
void FUN_000c0330(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00058970(args[0], args[1]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c03b0 (0xc03b0) — readable C lift (HS eval wrapper). */
void FUN_000c03b0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00055110(args[0], args[1]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c03f0 (0xc03f0) — readable C lift (HS eval wrapper). */
void FUN_000c03f0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000551e0(args[0], args[1]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c05f0 (0xc05f0) — readable C lift (HS eval wrapper). */
void FUN_000c05f0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056320(args[0], args[1]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c0630 (0xc0630) — readable C lift (HS eval wrapper). */
void FUN_000c0630(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000565c0(args[0], args[1], args[2]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c0670 (0xc0670) — readable C lift (HS eval wrapper). */
void FUN_000c0670(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000564b0(args[0], args[1]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c06b0 (0xc06b0) — readable C lift (HS eval wrapper). */
void FUN_000c06b0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    encounters_initialize((short)args[0], (int)(unsigned short)args[1]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c06f0 (0xc06f0) — readable C lift (HS eval wrapper). */
void FUN_000c06f0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056790((short)args[0], (int)(unsigned short)args[1]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c0730 (0xc0730) — readable C lift (HS eval wrapper). */
void FUN_000c0730(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00058c40(args[0], args[1], args[2]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c0770 (0xc0770) — readable C lift (HS eval wrapper). */
void FUN_000c0770(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    ai_scripting_follow_distance(args[0], args[1], args[2]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c09f0 (0xc09f0) — readable C lift (HS eval wrapper). */
void FUN_000c09f0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056ed0(args[0], args[1]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c0a70 (0xc0a70) — readable C lift (HS eval wrapper). */
void FUN_000c0a70(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000570d0(args[0], (int)(unsigned short)args[1]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c0ab0 (0xc0ab0) — readable C lift (HS eval wrapper). */
void FUN_000c0ab0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00057190(args[0], (int)(unsigned short)args[1]);
  }
  hs_return(thread_datum, 0);
}

/* 0xbe2f0 — HS built-in evaluator, sibling of FUN_000be270 / FUN_000be2b0
 * above. Evaluates a single macro-function via hs_macro_function_evaluate;
 * while that returns NULL the evaluation is still pending and nothing is
 * committed this call. Once it yields a non-NULL result datum, its first dword
 * and the float at +0x4 are handed to FUN_000c9c10, then the thread is
 * committed with hs_return(thread_datum, 0). Standard evaluator ABI
 * (function_index, thread_datum, init), plain cdecl (caller cleans).
 *
 * Disasm evidence: after TEST EAX,EAX / JZ, the non-NULL path does
 * `FLD  float ptr [EAX+0x4]` (float payload at result+4) and
 * `MOV  EDX,[EAX]` (dword at result+0), then the float is pushed via the MSVC
 * PUSH-then-FSTP idiom (`PUSH ECX; FSTP float ptr [ESP]` = second/higher slot)
 * and `PUSH EDX` supplies the first arg — i.e.
 * FUN_000c9c10(record[0], *(float*)(record+4)). The single trailing
 * ADD ESP,0x10 folds the cleanup of BOTH this 2-arg call and the following
 * 2-arg hs_return(thread_datum, 0). (The prefetch decomp modeled c9c10 as
 * void/void and dropped both args — corrected here from the binary; the float
 * arg would otherwise be silently lost to the push-then-fstp trap.)
 *
 * Callees:
 *   0xcc560 = hs_macro_function_evaluate(function_index, thread_datum, init)
 *             -> result node ptr in EAX (NULL while evaluation pending)
 *   0xc9c10 = FUN_000c9c10(int, float) — 2-arg cdecl (dword@+0, float@+4)
 *   0xcbf80 = hs_return(thread_datum, 0)
 */
void FUN_000be2f0(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != 0) {
    FUN_000c9c10(record[0], *(float *)((char *)record + 4));
    hs_return(thread_datum, 0);
  }
}


/* 0xbe500 — HS script function handler: evaluate a macro function and, on a
 * non-null result record, forward the record's first two dwords (+0x0, +0x4)
 * and a FLOAT field (+0x8) to FUN_000c9770, then commit that callee's byte
 * return to the calling HS thread. Same evaluator ABI (function_index,
 * thread_datum, init) as the other hs_evaluate_* handlers.
 *
 * ABI (verified against delinked disassembly 0xbe500): cdecl, plain RET.
 * thread_datum (arg 2, cached in ESI) flows to both the evaluate call (arg 2)
 * and the hs_return call (arg 1). On a non-null result the call site loads the
 * three fields and passes them to FUN_000c9770:
 *   FLDS [result+0x8]; PUSH <dummy>; FSTP [ESP]   (float arg3, push-then-fstp)
 *   PUSH [result+0x4] (int arg2); PUSH [result+0x0] (int arg1); CALL 0xc9770
 * then MOV [EBP-4],AL; PUSH ECX(=zero-extended AL); PUSH ESI(=thread_datum);
 * CALL hs_return. The combined ADD ESP,0x14 after the two trailing calls =
 * FUN_000c9770's 3 args (0xc) + hs_return's 2 args (0x8). Ghidra's void(void)
 * decl for 0xc9770 dropped all three args and its AL return, misled by that
 * combined cleanup; kb.json decl for 0xc9770 corrected to
 * unsigned char(int,int,float). The +0x8 field is a FLOAT read via FLDS and
 * passed as a float argument (hazard #2 push-then-fstp), NOT the pushed dummy.
 *
 * Callees (all cdecl, in kb.json):
 *   0xcc560 = hs_macro_function_evaluate(int16 fn_index, int thread_datum,
 *             char init) -> int* (result record, NULL on failure)
 *   0xc9770 = FUN_000c9770(int, int, float) -> unsigned char (record consumer)
 *   0xcbf80 = hs_return(int thread_handle, int value) */
void FUN_000be500(int16_t function_index, int thread_datum, char init)
{
  int *result;
  unsigned char value;

  result =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (result != NULL) {
    value = FUN_000c9770(result[0], result[1], *(float *)((char *)result + 8));
    hs_return(thread_datum, value);
  }
}


/* FUN_000be550 (0xbe550) — readable C lift (HS value-return wrapper). */
void FUN_000be550(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    hs_return(thread_datum, (int)(unsigned char)FUN_000c9840(args[0], (int16_t)(uint16_t)args[1], *(float *)&args[2]));
  }
}

/* FUN_000be5e0 (0xbe5e0) — readable C lift (HS eval wrapper). */
void FUN_000be5e0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_000ca030(args[0], *(float *)&args[1]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000be660 (0xbe660) — readable C lift (HS eval wrapper). */
void FUN_000be660(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    numeric_countdown_timer_set(args[0], (char)(unsigned char)args[1]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000be8f0 @ 0x000be8f0
 *
 * HaloScript macro-function trampoline (object ranged-attack-inhibited setter),
 * structurally simpler than the byte-returning dispatchers above. Evaluates the
 * script function via hs_macro_function_evaluate(function_index, thread_datum,
 * init); this returns a pointer to a 2-int evaluation record. On a non-NULL
 * record it reads two fields and applies them, then completes the calling
 * script thread with hs_return(thread_datum, 0).
 *
 * cdecl frame:
 *   function_index  int16_t  [EBP+0x08]  -> arg1 of hs_macro_function_evaluate
 *   thread_datum    int      [EBP+0x0c]  -> arg2; reused for hs_return
 *   init            char     [EBP+0x10]  -> arg3
 *
 * Record layout used (from the Ghidra pseudocode, which correctly modeled the
 * stack params here):
 *   record[0]  int   (offset 0x00)  object handle
 *   record[1]  int   (offset 0x04)  inhibit flag, truncated to char
 * -> object_set_ranged_attack_inhibited(record[0], (char)record[1]).
 * The script thread is then resolved with hs_return(thread_datum, 0). */
void FUN_000be8f0(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    object_set_ranged_attack_inhibited(record[0], (char)record[1]);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000be930 (0xbe930) — readable C lift (HS eval wrapper). */
void FUN_000be930(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    object_set_melee_attack_inhibited(args[0], (char)(unsigned char)args[1]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000be990 (0xbe990) — readable C lift (HS eval wrapper). */
void FUN_000be990(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    object_scripting_set_collideable(args[0], (char)(unsigned char)args[1]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000be9d0 (0xbe9d0) — readable C lift (HS eval wrapper). */
void FUN_000be9d0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    objects_scripting_set_scale(args[0], args[1], (short)(unsigned short)args[2]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000bea10 @ 0x000bea10
 *
 * HaloScript macro-function trampoline (object scripting-attach). Evaluates the
 * script function via hs_macro_function_evaluate(function_index, thread_datum,
 * init), which returns a pointer to a 4-int evaluation record. On a non-NULL
 * record it forwards the first four dwords to objects_scripting_attach, then
 * completes the calling script thread with hs_return(thread_datum, 0).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP; PUSH ESI):
 *   function_index  int16_t  [EBP+0x08]  -> arg1 of hs_macro_function_evaluate
 *   thread_datum    int      [EBP+0x0c]  -> arg2; held in ESI, reused for
 * hs_return init            char     [EBP+0x10]  -> arg3
 *
 * Record layout (all full dwords, from delinked disassembly):
 *   record[0]  int  (offset 0x00)  MOV (EAX),EAX
 *   record[1]  int  (offset 0x04)  MOV 0x4(EAX),EDX
 *   record[2]  int  (offset 0x08)  MOV 0x8(EAX),ECX
 *   record[3]  int  (offset 0x0c)  MOV 0xc(EAX),EDX
 * -> objects_scripting_attach(record[0], record[1], record[2], record[3]).
 * ADD ESP,0x18 combines the 16-byte attach cleanup and 8-byte hs_return
 * cleanup. Ghidra modeled this void(void) and read the three cdecl params as
 * in_stack_*. */
void FUN_000bea10(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    objects_scripting_attach(record[0], record[1], record[2], record[3]);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000beb30 @ 0x000beb30
 *
 * HaloScript macro-function trampoline (object "beautify" command). A direct
 * sibling of FUN_000beab0/FUN_000beaf0 above, differing in the middle callee
 * taking two arguments. Evaluates the script function via
 * hs_macro_function_evaluate(function_index, thread_datum, init), which returns
 * a pointer to an evaluation record. On a non-NULL record it forwards the first
 * dword (*record) and the low byte of the second dword ((char)record[1]) to
 * object_beautify, then completes the calling script thread with
 * hs_return(thread_datum, 0).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP):
 *   function_index  int16_t  [EBP+0x08]  -> hs_macro_function_evaluate arg1
 *   thread_datum    int      [EBP+0x0c]  -> arg2, reused for hs_return arg1
 *   init            char     [EBP+0x10]  -> arg3
 *
 * Ghidra modeled this void(void) with the three cdecl params read as
 * in_stack_*; the correct prototype is the 3-arg cdecl below. */
void FUN_000beb30(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    object_beautify(record[0], (char)record[1]);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000bedb0 @ 0x000bedb0
 *
 * HaloScript macro-function evaluator wrapper (animation-state variant), a
 * direct sibling of FUN_000bed70 above. Evaluates the script function via
 * hs_macro_function_evaluate(function_index, thread_datum, init); while that
 * returns NULL the evaluation is still pending and nothing is committed. Once a
 * non-NULL evaluation record is returned, its fields are forwarded to the
 * animation-state helper FUN_001457d0, then the calling thread is completed
 * with hs_return(thread_datum, 0).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP; PUSH ESI for thread_datum):
 *   function_index  int16_t  [EBP+0x08]  -> hs_macro_function_evaluate arg1
 *   thread_datum    int      [EBP+0x0c]  -> arg2; held in ESI, reused for
 *                                           hs_return arg1
 *   init            char     [EBP+0x10]  -> arg3
 *
 * hs_macro_function_evaluate returns the record pointer in EAX. On non-NULL the
 * original forwards four cdecl args to FUN_001457d0 in reverse push order:
 *   PUSH movzx(WORD [EAX+0xc])   -> arg4 = zero-extended 16-bit field @ +0xc
 *   PUSH [EAX+8]                 -> arg3 = record[2] (char *, animation name)
 *   PUSH [EAX+4]                 -> arg2 = record[1]
 *   PUSH [EAX]                   -> arg1 = record[0]
 * This is FUN_001457b0's 3-arg animation-state signature plus a trailing 16-bit
 * argument; the arg4 load is `XOR EDX,EDX; MOV DX, WORD PTR [EAX+0xc]` (an
 * unsigned-short widening, hence the [LOADW] shape). The combined ADD ESP,0x18
 * after the two trailing calls folds FUN_001457d0's 4-dword cleanup (0x10) with
 * hs_return's 2-dword cleanup (0x08), confirming both are cdecl. Ghidra modeled
 * this void(void): the three cdecl params were unmodeled (in_stack_*) and
 * FUN_001457d0's arguments were hidden because its kb decl was void(void). */
void FUN_000bedb0(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    FUN_001457d0(record[0], record[1], (int)(uintptr_t)(char *)record[2],
                 *(unsigned short *)(record + 3));
    hs_return(thread_datum, 0);
  }
}


/* FUN_000bee40 @ 0x000bee40
 *
 * HaloScript macro-function evaluator wrapper (unit blink-enable variant), a
 * direct sibling of FUN_000bee00 above. Evaluates the script function via
 * hs_macro_function_evaluate(function_index, thread_datum, init); while that
 * returns NULL the evaluation is still pending and nothing is committed. On a
 * non-NULL evaluation record the record's first dword (a unit handle) and the
 * zero-extended byte at +0x4 (the boolean flag) are forwarded to
 * unit_scripting_can_blink, then the calling thread is completed with
 * hs_return(thread_datum, 0).
 *
 * cdecl frame (PUSH EBP; MOV EBP,ESP; PUSH ESI for thread_datum; no _chkstk,
 * no locals):
 *   function_index  int16_t  [EBP+0x08]  -> hs_macro_function_evaluate arg1
 *                                           (loaded to ECX)
 *   thread_datum    int      [EBP+0x0c]  -> arg2; held in ESI across the whole
 *                                           body, reused for hs_return arg1
 *   init            char     [EBP+0x10]  -> arg3 (loaded to EAX)
 *
 * hs_macro_function_evaluate returns the record pointer in EAX (TEST EAX,EAX /
 * JZ skips the body). On non-NULL the original reads the record's +0x4 field as
 * a ZERO-EXTENDED BYTE (XOR EDX,EDX; MOV DL,BYTE PTR [EAX+0x4]) — not a dword —
 * and reloads the handle with MOV EAX,DWORD PTR [EAX], then PUSH EDX; PUSH EAX.
 * The hs_return arg1 comes from the preserved ESI (the ORIGINAL thread_datum),
 * not from the returned record pointer. A single combined ADD ESP,0x10 at
 * 0xbee72 folds unit_scripting_can_blink's 2-dword cleanup with hs_return's
 * 2-dword cleanup; the context-pack ARG_COUNT warning on 0xcbf80 ("cleanup=4")
 * is that merge, and the PUSH count proves hs_return still takes exactly 2.
 * No FPU ops. Ghidra modeled this void(void): the three cdecl params were
 * unmodeled (in_stack_*), so all three come off the stack — no.
 *
 * Callees (all cdecl, in kb.json):
 *   0xcc560  = hs_macro_function_evaluate(int16_t, int, char) -> record ptr
 *   0x1a9c00 = unit_scripting_can_blink(int unit_handle, char can_blink)
 *   0xcbf80  = hs_return(int thread_handle, int value) */
void FUN_000bee40(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    unit_scripting_can_blink(record[0], *(unsigned char *)(record + 1));
    hs_return(thread_datum, 0);
  }
}


void FUN_000bf010(int16_t function_index, int thread_datum, char init)
{
  volatile unsigned int result_slot;
  int *record;
  unsigned int result;

  result_slot = 0;
  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    result_slot =
      (unsigned char)FUN_001ac180(record[0], record[1], (void *)record[2],
                                  (int)*(unsigned char *)(record + 3));
    result = (unsigned int)result_slot;
    hs_return(thread_datum, result);
  }
}


void FUN_000bf060(int16_t function_index, int thread_datum, char init)
{
  volatile unsigned int result_slot;
  int *record;
  unsigned int result;

  result_slot = 0;
  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    result_slot = (unsigned char)FUN_001a7df0(
      record[0], record[1], record[2], (int)*(unsigned char *)(record + 3));
    result = (unsigned int)result_slot;
    hs_return(thread_datum, result);
  }
}


void FUN_000bf0b0(int16_t function_index, int thread_datum, char init)
{
  volatile unsigned int result_slot;
  int *record;
  unsigned int result;

  result_slot = 0;
  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    result_slot = (unsigned char)unit_custom_animation_at_frame(
      record[0], record[1], record[2], (int)*(unsigned char *)(record + 3),
      *(unsigned short *)(record + 4));
    result = (unsigned int)result_slot;
    hs_return(thread_datum, result);
  }
}


void FUN_000bf160(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    FUN_001ac0a0(record[0], (int)*(unsigned char *)(record + 1));
    hs_return(thread_datum, 0);
  }
}


void FUN_000bf1e0(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    FUN_001ac030(record[0], (int)*(unsigned char *)((char *)record + 4));
    hs_return(thread_datum, 0);
  }
}


void FUN_000bf870(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    FUN_001a7d80(record[0], (char)*(unsigned char *)((char *)record + 4));
    hs_return(thread_datum, 0);
  }
}


void FUN_000bf8b0(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    unit_scripting_suspended(record[0],
                             (char)*(unsigned char *)((char *)record + 4));
    hs_return(thread_datum, 0);
  }
}


void FUN_000bf920(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    units_set_desired_flashlight_state(
      record[0], (char)*(unsigned char *)((char *)record + 4));
    hs_return(thread_datum, 0);
  }
}


void FUN_000bf960(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    unit_set_desired_flashlight_state(
      record[0], (char)*(unsigned char *)((char *)record + 4));
    hs_return(thread_datum, 0);
  }
}


/* FUN_000bf9f0 (0xbf9f0) — readable C lift (HS eval wrapper). */
void FUN_000bf9f0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    device_set_never_appears_locked(args[0], args[1]);
  }
  hs_return(thread_datum, 0);
}

void FUN_000bfa30(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    FUN_00097260(record[0], *(float *)((char *)record + 4));
    hs_return(thread_datum, 0);
  }
}


void FUN_000bfab0(int16_t function_index, int thread_datum, char init)
{
  int *record;
  union {
    unsigned char b;
    int i;
  } value;

  value.i = 0;
  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    value.b =
      (unsigned char)FUN_00097220(record[0], *(float *)((char *)record + 4));
    hs_return(thread_datum, value.i);
  }
}


void FUN_000bfb40(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    FUN_00097040(record[0], *(float *)((char *)record + 4));
    hs_return(thread_datum, 0);
  }
}


void FUN_000bfbc0(int16_t function_index, int thread_datum, char init)
{
  unsigned short *record;
  union {
    unsigned char b;
    int i;
  } value;

  value.i = 0;
  record = (unsigned short *)hs_macro_function_evaluate(function_index,
                                                        thread_datum, init);
  if (record != NULL) {
    value.b = (unsigned char)FUN_00096f20((int)record[0],
                                          *(float *)((char *)record + 4));
    hs_return(thread_datum, value.i);
  }
}


void FUN_000bfc10(int16_t function_index, int thread_datum, char init)
{
  unsigned short *record;

  record = (unsigned short *)hs_macro_function_evaluate(function_index,
                                                        thread_datum, init);
  if (record != NULL) {
    device_group_set_actual_value((int)record[0],
                                  *(volatile float *)((char *)record + 4));
    hs_return(thread_datum, 0);
  }
}


void FUN_000bfc50(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    device_one_sided_set(record[0],
                         (char)*(unsigned char *)((char *)record + 4));
    hs_return(thread_datum, 0);
  }
}


void FUN_000bfc90(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    device_operates_automatically_set(
      record[0], (char)*(unsigned char *)((char *)record + 4));
    hs_return(thread_datum, 0);
  }
}


void FUN_000bfcd0(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    device_group_change_only_once_more_set(
      *(int16_t *)record, (char)*(unsigned char *)((char *)record + 4));
    hs_return(thread_datum, 0);
  }
}


/* FUN_000c0270 (0xc0270) — readable C lift (HS eval wrapper). */
void FUN_000c0270(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00054f90(args[0], (char)(unsigned char)args[1]);
  }
  hs_return(thread_datum, 0);
}

void FUN_000c02b0(int16_t function_index, int thread_datum, char init)
{
  unsigned char *record;

  record = (unsigned char *)hs_macro_function_evaluate(function_index,
                                                       thread_datum, init);
  if (record != NULL) {
    FUN_00055010(*(unsigned int *)record, (char)record[4]);
    hs_return(thread_datum, 0);
  }
}


/* FUN_000c02f0 (0xc02f0) — readable C lift (HS eval wrapper). */
void FUN_000c02f0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00055090(args[0], (char)(unsigned char)args[1]);
  }
  hs_return(thread_datum, 0);
}

void FUN_000c05b0(int16_t function_index, int thread_datum, char init)
{
  int *record;

  record =
    (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (record != NULL) {
    FUN_00055900((unsigned int)record[0], (char)*((unsigned char *)record + 4));
    hs_return(thread_datum, 0);
  }
}


/* FUN_000c07f0 (0xc07f0) — readable C lift (HS eval wrapper). */
void FUN_000c07f0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056980(args[0], (char)(unsigned char)args[1]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c0830 (0xc0830) — readable C lift (HS eval wrapper). */
void FUN_000c0830(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056a20(args[0], (char)(unsigned char)args[1]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c0870 (0xc0870) — readable C lift (HS eval wrapper). */
void FUN_000c0870(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056b20(args[0], (char)(unsigned char)args[1]);
  }
  hs_return(thread_datum, 0);
}

/* FUN_000c08b0 (0xc08b0) — readable C lift (HS eval wrapper). */
void FUN_000c08b0(int16_t function_index, int thread_datum, char init)
{
  int *args = (int *)hs_macro_function_evaluate(function_index, thread_datum, init);
  if (args) {
    FUN_00056bc0(args[0], (char)(unsigned char)args[1]);
  }
  hs_return(thread_datum, 0);
}

/* --- players.obj orphan shells (2026-07-26) --- */

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
bool FUN_000bae20(int player_unit_handle, int nearby_unit_handle)
{
  int *nearby_obj;
  char *weap_tag;
  int weapon_count;
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

