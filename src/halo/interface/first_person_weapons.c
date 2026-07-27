#include <stdint.h>
/* Allocate the first-person weapons game state block (0xdc750).
 * Reserves 0x7a80 bytes (4 slots of 0x1ea0 each) via game_state_malloc.
 * Asserts on allocation failure. */
void FUN_000dc750(void)
{
  *(void **)0x46bea8 = game_state_malloc("first person weapons", 0, 0x7a80);
  if (*(void **)0x46bea8 == 0) {
    display_assert("first_person_weapons",
                   "c:\\halo\\SOURCE\\interface\\first_person_weapons.c", 0xf0,
                   1);
    system_exit(-1);
  }
}

/* FUN_000dc7a0 (0xdc7a0) — readable C lift. */
void FUN_000dc7a0(void)
{
  int i;
  for (i = 0; i < 4; i++) {
    int off = i * 0x1ea0;
    char *base = *(char **)0x46bea8;
    csmemset(base + off, 0, 0x1ea0);
    *(int *)(base + off + 4) = -1;
    *(int *)(base + off + 0x1e98) = -1;
    *(int16_t *)(base + off + 0x1e9c) = -1;
  }
}

/* Map a first-person weapon state to an animation graph index (0xdc8c0).
 * Pure lookup table: 24 states (0..23) map to animation indices; any
 * out-of-range state returns -1. */
int16_t FUN_000dc8c0(int16_t state)
{
  switch (state) {
  case 0:
    return 0;
  case 1:
    return 0x15;
  case 2:
    return 0x16;
  case 3:
    return 9;
  case 4:
    return 0xc;
  case 5:
    return 1;
  case 6:
    return 2;
  case 7:
    return 0xe;
  case 8:
    return 0x12;
  case 9:
    return 0x13;
  case 10:
    return 0xd;
  case 11:
    return 5;
  case 12:
    return 6;
  case 13:
    return 7;
  case 14:
    return 8;
  case 15:
    return 0x17;
  case 16:
    return 0x18;
  case 17:
    return 0x19;
  case 18:
    return 0xb;
  case 19:
    return 0xa;
  case 20:
    return 0x10;
  case 21:
    return 0x14;
  case 22:
    return 0x1a;
  case 23:
    return 0x1b;
  default:
    return (int16_t)-1;
  }
}

/* Try to play a third-person weapon sound for an object event (0xdc9d0).
 * When no local player owns the weapon, this function looks up the weapon's
 * animation graph tag, maps the event through two state-translation tables
 * (FUN_000dc800 and FUN_000dc8c0), resolves the animation's sound effect
 * tag reference, and plays it at the global origin with default forward. */
void FUN_000dc9d0(int param_2, int object_handle)
{
  int16_t state;
  int16_t anim_index;
  char *weapon_tag;
  int anim_graph_tag_index;
  char *antr_tag;
  char *block_element;
  int16_t lookup_result;
  char *anim_element;
  char *sound_element;
  int sound_tag_index;

  if (object_handle == -1)
    return;
  if ((int16_t)param_2 == -1)
    return;
  if (!object_try_and_get_and_verify_type(object_handle, 4))
    return;

  {
    int *weapon_obj = (int *)object_get_and_verify_type(object_handle, 4);
    weapon_tag = (char *)tag_get(0x77656170, *weapon_obj);
  }

  anim_graph_tag_index = *(int *)(weapon_tag + 0x478);
  if (anim_graph_tag_index == -1)
    return;

  state = FUN_000dc800(param_2);
  if (state == -1)
    return;

  anim_index = FUN_000dc8c0(state);
  if (anim_index == -1)
    return;

  antr_tag = (char *)tag_get(0x616e7472, anim_graph_tag_index);

  if (*(int *)(antr_tag + 0x48) == 0) {
    block_element = NULL;
  } else {
    block_element = (char *)tag_block_get_element(antr_tag + 0x48, 0, 0x1c);
  }

  if (anim_index < 0 || (int)anim_index >= *(int *)(block_element + 0x10))
    return;

  lookup_result =
    *(int16_t *)(*(int *)(block_element + 0x14) + (int)anim_index * 2);
  if (lookup_result == -1)
    return;

  anim_element =
    (char *)tag_block_get_element(antr_tag + 0x74, (int)lookup_result, 0xb4);
  if (*(int16_t *)(anim_element + 0x3c) == -1)
    return;

  sound_element = (char *)tag_block_get_element(
    antr_tag + 0x54, (int)*(int16_t *)(anim_element + 0x3c), 0x14);
  sound_tag_index = *(int *)(sound_element + 0xc);
  if (sound_tag_index == -1)
    return;

  {
    float *position = *(float **)0x31fc1c;
    float *forward = *(float **)0x31fc3c;
    object_impulse_sound_new(object_handle, sound_tag_index, -1, position,
                             forward, 1.0f);
  }
}

/* Toggle the first-person weapon activation state for a local player (0xdcb30).
 * When activating (activate != 0): asserts weapon_index != NONE, then calls
 * effects_start_on_first_person_weapon to start effects. When deactivating:
 * calls effects_stop_on_first_person_weapon to stop effects and FUN_000a1510 to
 * stop sounds. Only acts if the state changes. */
void FUN_000dcb30(int16_t local_player_index, uint8_t activate)
{
  char *fp;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  fp = (char *)(*(int *)0x46bea8 + (int)local_player_index * 0x1ea0);

  if (activate != *(uint8_t *)fp) {
    if (activate != 0) {
      assert_halt(*(int *)(fp + 8) != -1);
      effects_start_on_first_person_weapon((int)local_player_index,
                                           *(int *)(fp + 8));
      *(uint8_t *)fp = activate;
      return;
    }
    effects_stop_on_first_person_weapon((int)local_player_index);
    FUN_000a1510((int)local_player_index);
    *(uint8_t *)fp = 0;
  }
}

/* Copy animation node transforms from the animation graph into the
 * first-person node buffer using a node remap table (0xdcbd0).
 * For each model node i, node_remap[i] gives the source index in the
 * animation graph node array. Copies 0x34 bytes (13 dwords) per node.
 * Asserts that every remap index is within [0, antr->nodes.count). */
void fp_anim_apply_node_remap(int mode_tag_index, int fp_nodes,
                              int antr_tag_index, int anim_nodes,
                              int16_t *node_remap)
{
  char *mode_tag;
  char *antr_tag;
  int node_count;
  int16_t i;
  int16_t remap_idx;
  int src_off;
  int dst_off;
  int j;
  unsigned int *src;
  unsigned int *dst;

  mode_tag = (char *)tag_get(0x6d6f6465, mode_tag_index);
  antr_tag = (char *)tag_get(0x616e7472, antr_tag_index);
  node_count = *(int *)(mode_tag + 0xb8);
  if (node_count <= 0)
    return;

  i = 0;
  do {
    remap_idx = node_remap[(int)i];
    assert_halt(remap_idx >= 0 && (int)remap_idx < *(int *)(antr_tag + 0x68));
    src_off = (int)remap_idx * 0x34;
    dst_off = (int)i * 0x34;
    src = (unsigned int *)(anim_nodes + src_off);
    dst = (unsigned int *)(fp_nodes + dst_off);
    for (j = 0xd; j != 0; j--) {
      *dst = *src;
      src++;
      dst++;
    }
    i++;
  } while ((int)i < *(int *)(mode_tag + 0xb8));
}

/* Match animation node labels between a model tag and an animation graph tag
 * (0xdcc80). For each node in the model's node block, searches the animation
 * graph's node block for a matching string label via csstrcmp. Stores the
 * matching index in the output array. Returns 1 if all nodes matched, 0 if
 * any node had no match. */
uint8_t FUN_000dcc80(int mode_tag_index, int antr_tag_index, int16_t *output)
{
  char *mode_tag;
  char *antr_tag;
  uint8_t success;
  int16_t outer;
  int outer_int;
  void *antr_nodes; /* pointer to antr tag + 0x68 (node block) */

  mode_tag = (char *)tag_get(0x6d6f6465, mode_tag_index);
  antr_tag = (char *)tag_get(0x616e7472, antr_tag_index);

  success = 1;
  outer = 0;
  outer_int = 0;

  if (*(int *)(mode_tag + 0xb8) < 1)
    return 1;

  antr_nodes = (void *)(antr_tag + 0x68);

  do {
    char *mode_element;
    int16_t inner;
    int inner_int;

    mode_element =
      (char *)tag_block_get_element(mode_tag + 0xb8, outer_int, 0x9c);
    inner = 0;

    if (*(int *)antr_nodes > 0) {
      inner_int = 0;
      do {
        char *antr_element;
        antr_element =
          (char *)tag_block_get_element(antr_nodes, inner_int, 0x40);
        if (csstrcmp(mode_element, antr_element) == 0) {
          if (inner != -1) {
            output[outer_int] = inner;
            goto next_outer;
          }
          break;
        }
        inner = inner + 1;
        inner_int = (int)inner;
      } while (inner_int < *(int *)antr_nodes);
    }

    success = 0;

  next_outer:
    outer = outer + 1;
    outer_int = (int)outer;
    if (outer_int >= *(int *)(mode_tag + 0xb8))
      return success;
  } while (1);
}

/* Find the local player index (0..3) whose unit currently holds the given
 * weapon object. Iterates all local players, resolves each player's
 * controlled unit, and checks if the unit's active weapon slot matches the
 * given object handle. Returns the local player index or -1 if not found. */
int16_t FUN_000dcd60(int object_handle)
{
  int16_t i;

  for (i = 0; i < 4; i++) {
    int player_handle;
    char *player;
    int unit_handle;
    char *unit;
    int16_t weapon_index;

    player_handle = local_player_get_player_index(i);
    if (player_handle == -1)
      continue;

    player = (char *)datum_get(player_data, player_handle);
    unit_handle = *(int *)(player + 0x34);
    if (unit_handle == -1)
      continue;

    unit = (char *)object_get_and_verify_type(unit_handle, 3);
    weapon_index = *(int16_t *)(unit + 0x2a2);
    if (weapon_index == -1)
      continue;

    if (object_handle == *(int *)(unit + 0x2a8 + (int)weapon_index * 4))
      return i;
  }

  return (int16_t)-1;
}

/* Precache the weapon's predicted resources and set the reload timer (0xdce00).
 * If the player has a valid weapon, resolves the weapon tag and calls
 * predicted_resources_precache on the resource block at weapon_tag + 0x4e4.
 * Always sets the timer at fp + 0x12 to 0x1e (30 ticks). */
void FUN_000dce00(int16_t local_player_index)
{
  char *fp;
  int weapon_handle;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  weapon_handle =
    *(int *)((int)local_player_index * 0x1ea0 + 8 + *(int *)0x46bea8);
  fp = (char *)((int)local_player_index * 0x1ea0 + *(int *)0x46bea8);

  if (weapon_handle != -1) {
    int *weapon_obj = (int *)object_get_and_verify_type(weapon_handle, 4);
    char *weapon_tag = (char *)tag_get(0x77656170, *weapon_obj);
    predicted_resources_precache((int *)(weapon_tag + 0x4e4));
  }

  *(int16_t *)(fp + 0x12) = 0x1e;
}

/* first_person_weapon_get_local_index (0xdd110) — readable C lift. */
int first_person_weapon_get_local_index(int object_handle)
{
  extern char DAT_00266fc0[];
  extern char DAT_00282294[];
  int i;
  char *base;
  char *fp;
  int *slot;

  for (i = 0; i < 4; i++) {
    if ((int16_t)i < 0 || (int16_t)i >= 4) {
      display_assert(DAT_00266fc0, DAT_00282294, 0x599, 1);
      system_exit(-1);
    }
    base = *(char **)0x46bea8;
    fp = base + i * 0x1ea0;
    slot = (int *)(fp + 8);
    if (*slot == object_handle && *fp != 0)
      return i;
  }
  return -1;
}

/* Return a pointer to the node transform for a given node in the local
 * player's first-person weapon animation state (0xdd410).
 * Validates the local_player_index (0..3) and node_index against the
 * animation graph node count. Returns fp_base + 0x108c + node_index * 0x34. */
void *first_person_weapon_get_node_matrix(int param_1, int param_2)
{
  int16_t local_player_index = (int16_t)param_1;
  int16_t node_index = (int16_t)param_2;
  char *fp;
  int *weapon_obj;
  char *weapon_tag;
  char *antr_tag;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  fp = (char *)(*(int *)0x46bea8 + (int)local_player_index * 0x1ea0);
  weapon_obj = (int *)object_get_and_verify_type(*(int *)(fp + 8), 4);
  weapon_tag = (char *)tag_get(0x77656170, *weapon_obj);
  antr_tag = (char *)tag_get(0x616e7472, *(int *)(weapon_tag + 0x478));

  assert_halt(node_index >= 0 && (int)node_index < *(int *)(antr_tag + 0x68));

  return (void *)((int)node_index * 0x34 + 0x108c + (int)fp);
}

/* Copy animation node data from the current buffer to the blend buffer and
 * update blend timing (0xdd4d0). Copies node_count * 32 bytes from fp + 0x8c
 * to fp + 0x88c. If blend_ticks >= (fp[0x8a] - fp[0x88]), resets the blend
 * origin to 0 and sets the blend target to blend_ticks. */
void FUN_000dd4d0(int16_t local_player_index, int16_t blend_ticks)
{
  char *fp;
  int *weapon_obj;
  char *weapon_tag;
  char *antr_tag;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  fp = (char *)(*(int *)0x46bea8 + (int)local_player_index * 0x1ea0);
  weapon_obj = (int *)object_get_and_verify_type(*(int *)(fp + 8), 4);
  weapon_tag = (char *)tag_get(0x77656170, *weapon_obj);
  antr_tag = (char *)tag_get(0x616e7472, *(int *)(weapon_tag + 0x478));

  csmemcpy(fp + 0x88c, fp + 0x8c, *(int *)(antr_tag + 0x68) << 5);

  if ((int)blend_ticks >=
      (int)*(int16_t *)(fp + 0x8a) - (int)*(int16_t *)(fp + 0x88)) {
    *(int16_t *)(fp + 0x88) = 0;
    *(int16_t *)(fp + 0x8a) = blend_ticks;
  }
}

/* Set the first-person weapon animation state for a local player (0xddbd0).
 * Applies state-transition filtering: certain incoming states are rejected
 * depending on the current state. For dual-wielding weapons (type 3), maps
 * state 3 to state 0 unless the weapon has a specific flag. Looks up the
 * animation index via FUN_000dc8c0 and the animation graph to validate the
 * transition. If param_3 is nonzero, stops any pending sound. */
void FUN_000ddbd0(int param_1, int param_2, int param_3)
{
  int16_t local_player_index = (int16_t)param_1;
  int16_t state = (int16_t)param_2;
  char *fp;
  int weapon_handle;
  int16_t sVar1;
  int16_t blend_ticks;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  fp = (char *)(*(int *)0x46bea8 + (int)local_player_index * 0x1ea0);
  weapon_handle = *(int *)(fp + 8);

  /* If the unit's weapon has the dual-wield flag (byte 0x1dc bit 0),
   * remap certain states. */
  if (weapon_handle != -1) {
    char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
    if ((*(uint8_t *)(weapon_obj + 0x1dc) & 1) != 0) {
      if (state == 0x13) {
        state = 2;
      } else if (state == 0x14) {
        state = 0x15;
      }
    }
  }

  /* First switch: filter incoming states based on current state.
   * Binary switch table at 0xdde40/0xdde50 maps:
   *   6,7,8,9 → handler 0 (melee filter)
   *   0xb,0xc → handler 1 (grenade filter)
   *   0x13    → handler 2
   *   0xa,0xd-0x12 → handler 3 (default, no filter) */
  switch (state) {
  case 6:
  case 7:
  case 8:
  case 9: {
    int16_t cur = *(int16_t *)(fp + 0xc);
    if (cur != 0 && cur != 5 && cur != 6 && cur != 4 && cur != 0xf &&
        cur != 0x16 && cur != 0x10 && cur != 0x11 && cur != 0xd && cur != 0xe) {
      return;
    }
    break;
  }
  case 0xb:
  case 0xc:
    if (*(int16_t *)(fp + 0xc) != 0 && *(int16_t *)(fp + 0xc) != 5) {
      return;
    }
    break;
  case 0x13:
    if (*(int16_t *)(fp + 0xc) == 0x13)
      return;
    break;
  default:
    break;
  }

  if (state == -1)
    return;
  if (*(int *)(fp + 8) == -1)
    return;

  {
    int *weapon_obj2 = (int *)object_get_and_verify_type(*(int *)(fp + 8), 4);
    char *weapon_tag = (char *)tag_get(0x77656170, *weapon_obj2);

    /* For weapon type 3, if state is also 3 and the dual-wield flag is
     * not set, reset state to 0. */
    if (*(int16_t *)(weapon_tag + 0x4e2) == 3 && state == 3 &&
        (*(uint8_t *)((char *)weapon_obj2 + 0x1dc) & 1) == 0) {
      state = 0;
    }

    sVar1 = FUN_000dc8c0(state);

    /* If weapon type is 1 and current state is 0x10, use blend_ticks = 0. */
    if (*(int16_t *)(weapon_tag + 0x4e2) == 1 &&
        *(int16_t *)(fp + 0xc) == 0x10) {
      blend_ticks = 0;
    } else {
      /* Second switch: determine blend tick count. */
      switch (state) {
      case 3:
      case 10:
      case 0x13:
        blend_ticks = 0;
        break;
      case 6:
      case 7:
      case 8:
      case 9:
        blend_ticks = 3;
        break;
      default:
        blend_ticks = 6;
        break;
      }
    }

    if (*(int *)(fp + 4) == -1)
      return;
    if (*(int *)(fp + 8) == -1)
      return;

    {
      int *weapon_obj3 = (int *)object_get_and_verify_type(*(int *)(fp + 8), 4);
      char *weapon_tag2 = (char *)tag_get(0x77656170, *weapon_obj3);
      char *antr_tag =
        (char *)tag_get(0x616e7472, *(int *)(weapon_tag2 + 0x478));

      if (*(int *)(antr_tag + 0x48) != 0) {
        char *anim_block =
          (char *)tag_block_get_element(antr_tag + 0x48, 0, 0x1c);
        if (anim_block != NULL && sVar1 >= 0 &&
            (int)sVar1 < *(int *)(anim_block + 0x10)) {
          int16_t anim_index =
            *(int16_t *)(*(int *)(anim_block + 0x14) + (int)sVar1 * 2);
          if (anim_index != -1) {
            if ((char)param_3 != 0 && *(int *)(fp + 0x1e98) != -1 &&
                *(int16_t *)(fp + 0x1e9c) != 1) {
              sound_stop_impulse(*(int *)(fp + 0x1e98));
              *(int *)(fp + 0x1e98) = -1;
              *(int16_t *)(fp + 0x1e9c) = -1;
            }
            if (blend_ticks > 0) {
              FUN_000dd4d0(local_player_index, blend_ticks);
            }
            *(int16_t *)(fp + 0xc) = state;
            *(int16_t *)(fp + 0x16) = anim_index;
            *(int16_t *)(fp + 0x18) = 0;
          }
        }
      }
    }
  }
}

/* Initialize or reinitialize a local player's first-person weapon (0xdde80).
 * Clears the current weapon reference, deactivates visual/sound state if
 * previously active, then resolves the unit's current weapon and sets up
 * the animation graph, idle animation index, and initial weapon state. */
void FUN_000dde80(int param_1)
{
  int16_t local_player_index = (int16_t)param_1;
  char *fp;
  uint8_t was_active;
  int weapon_handle;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  fp = (char *)(*(int *)0x46bea8 + (int)local_player_index * 0x1ea0);
  was_active = *(uint8_t *)fp;

  /* Clear weapon handle. */
  *(int *)(fp + 8) = -1;

  /* If previously active, deactivate effects and sounds. */
  if (was_active != 0) {
    assert_halt(local_player_index >= 0 &&
                local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

    {
      char *fp2 = (char *)(*(int *)0x46bea8 + (int)local_player_index * 0x1ea0);
      if (*(uint8_t *)fp2 != 0) {
        effects_stop_on_first_person_weapon(param_1);
        FUN_000a1510(param_1);
        *(uint8_t *)fp2 = 0;
      }
    }
  }

  /* If no unit is assigned, skip weapon setup. */
  if (*(int *)(fp + 4) == -1)
    goto done;

  {
    char *unit_obj = (char *)object_get_and_verify_type(*(int *)(fp + 4), 3);
    int16_t weapon_index = *(int16_t *)(unit_obj + 0x2a2);

    weapon_handle = unit_get_weapon(*(int *)(fp + 4), weapon_index);
    if (weapon_handle == -1)
      goto done;

    {
      int *weapon_obj = (int *)object_get_and_verify_type(weapon_handle, 4);
      char *weapon_tag = (char *)tag_get(0x77656170, *weapon_obj);

      if (*(int *)(weapon_tag + 0x468) == -1)
        goto done;
      if (*(int *)(weapon_tag + 0x478) == -1)
        goto done;

      {
        char *antr_tag =
          (char *)tag_get(0x616e7472, *(int *)(weapon_tag + 0x478));

        if (*(int *)(antr_tag + 0x48) == 0)
          goto done;

        {
          char *anim_block =
            (char *)tag_block_get_element(antr_tag + 0x48, 0, 0x1c);
          if (anim_block == NULL)
            goto done;

          /* Set idle animation index from the animation lookup table. */
          *(int16_t *)(fp + 0x14) = -1;
          if (*(int *)(anim_block + 0x10) > 4) {
            int16_t anim_lookup = *(int16_t *)(*(int *)(anim_block + 0x14) + 8);
            if (anim_lookup != -1) {
              char *anim_entry = (char *)tag_block_get_element(
                antr_tag + 0x74, (int)anim_lookup, 0xb4);
              if (*(int16_t *)(anim_entry + 0x22) >= 9) {
                *(int16_t *)(fp + 0x14) = anim_lookup;
              }
            }
          }

          /* Check game globals for the global fp animation model. */
          {
            char *game_globals = (char *)game_globals_get();
            char *gg_element =
              (char *)tag_block_get_element(game_globals + 0x17c, 0, 0xc0);

            if (*(int *)(gg_element + 0xc) != -1) {
              *(uint8_t *)(fp + 0x1e0e) = FUN_000dcc80(
                *(int *)(gg_element + 0xc), *(int *)(weapon_tag + 0x478),
                (int16_t *)(fp + 0x1e10));
            }
          }

          *(uint8_t *)(fp + 0x1d8c) = FUN_000dcc80(*(int *)(weapon_tag + 0x468),
                                                   *(int *)(weapon_tag + 0x478),
                                                   (int16_t *)(fp + 0x1d8e));

          if (*(uint8_t *)(fp + 0x1d8c) == 0)
            goto done;
          if (*(uint8_t *)(fp + 0x1e0e) == 0)
            goto done;

          /* Set weapon handle and clear animation state. */
          *(int *)(fp + 0x8) = weapon_handle;
          *(int16_t *)(fp + 0xc) = -1;
          *(int16_t *)(fp + 0x16) = -1;
          *(int16_t *)(fp + 0x1a) = -1;
          *(int16_t *)(fp + 0x20) = -1;
          *(int *)(fp + 0x28) = 0;
          *(int *)(fp + 0x2c) = 0;
          *(int16_t *)(fp + 0x10) = 0;
          *(int *)(fp + 0x1e98) = -1;
          *(int16_t *)(fp + 0x1e9c) = -1;

          FUN_000ddbd0(param_1, 0, 1);

          *(int16_t *)(fp + 0x8a) = 0;

          if (was_active != 0) {
            FUN_000dcb30(local_player_index, 1);
          }
        }
      }
    }
  }

done:
  FUN_000dce00(local_player_index);
}

/* Process a weapon event for a local player's first-person weapon (0xde140).
 * Handles reload initiation, weapon put-away, aim-assist clearing, and state
 * transitions. Computes reload count from trigger data and weapon ammo state,
 * then selects the appropriate animation state. */
void FUN_000de140(int param_1, int param_2)
{
  char *fp;
  int saved_event;
  int new_state;

  if ((int16_t)param_1 == -1)
    return;

  assert_halt((int16_t)param_1 >= 0 &&
              (int16_t)param_1 < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  fp = (char *)(*(int *)0x46bea8 + (int)(int16_t)param_1 * 0x1ea0);
  saved_event = (int)(int16_t)param_2;

  switch ((int16_t)param_2) {
  case 0:
    *(float *)(fp + 0x2c) += 0.05f;
    break;
  case 9:
  case 10:
    player_clear_aim_assist(*(int *)(fp + 4));
    break;
  case 0xc:
    FUN_000dde80(param_1);
    break;
  case 0xd:
    *(int *)(fp + 0x8) = -1;
    break;
  }

  if (*(int *)(fp + 0x8) == -1)
    goto default_handler;

  {
    int *weapon;
    char *tag;

    weapon = (int *)object_get_and_verify_type(*(int *)(fp + 0x8), 4);
    if (*weapon == -1)
      goto default_handler;

    tag = (char *)tag_get(0x77656170, *weapon);
    if (*(int16_t *)(tag + 0x4e2) != 1)
      goto default_handler;

    if ((int16_t)param_2 != 9 && (int16_t)param_2 != 10)
      goto default_handler;

    {
      char *trigger;
      int16_t current_state;
      int16_t rounds_loaded;
      int16_t ammo_remaining;
      int reload_count;
      int16_t reload_type;

      trigger = (char *)tag_block_get_element(tag + 0x4f0, 0, 0x70);
      current_state = *(int16_t *)(fp + 0xc);
      rounds_loaded = *(int16_t *)((char *)weapon + 0x260);
      ammo_remaining = *(int16_t *)((char *)weapon + 0x25e);

      reload_count = (int)*(int16_t *)(trigger + 0xa) - (int)rounds_loaded;
      if (reload_count > (int)ammo_remaining)
        reload_count = (int)ammo_remaining;

      if (current_state == 0xf || current_state == 0x16 ||
          current_state == 0x10 || current_state == 0x11 ||
          current_state == 0xd || current_state == 0xe ||
          *(int16_t *)((char *)weapon + 0x258) != 0) {
        if (reload_count == 1)
          *(int16_t *)(fp + 0x1e94) = 1;
        else
          *(int16_t *)(fp + 0x1e94) = -1;
      } else {
        *(int16_t *)(fp + 0x1e92) = (int16_t)reload_count;
        *(uint8_t *)(fp + 0x1e90) = (rounds_loaded == 0);
        *(uint16_t *)(fp + 0x1e94) = (uint16_t)(((reload_count != 1) - 1) & 2);
      }

      reload_type = *(int16_t *)(fp + 0x1e94);
      if (reload_type == -1) {
        new_state = 0xd;
      } else if (reload_type == 0 || reload_type == 2) {
        new_state = 0xf;
      } else {
        goto default_handler;
      }
      goto apply_state;
    }
  }

default_handler:
  new_state = (int)FUN_000dc800(param_2);
  if ((int16_t)new_state == -1)
    goto cleanup;

apply_state:
  FUN_000ddbd0(param_1, new_state, 1);

cleanup:
  if (saved_event == 0xc)
    *(int16_t *)(fp + 0x8a) = 0;
}

/* Notify the first-person weapon system of an object event (0xde3b0).
 * Finds the local player holding the weapon, processes the event, and if
 * no local player owns it, attempts third-person sound playback. */
void first_person_weapon_message_from_weapon(int object_handle, int param_2)
{
  int16_t local_player = FUN_000dcd60(object_handle);
  FUN_000de140(local_player, param_2);
  if (local_player == -1) {
    FUN_000dc9d0(param_2, object_handle);
  }
}

/* Update first-person weapon state for all local players. Detects when
 * a player's controlled unit changes and reinitializes their weapon
 * rendering state. Calls per-player weapon update each frame. */
void first_person_weapons_update(void)
{
  int i;
  int offset;

  offset = 0;
  for (i = 0; (int16_t)i < 4; i++, offset += 0x1ea0) {
    int player_handle;
    char *fp;
    void *player;
    int unit;

    player_handle = local_player_get_player_index(i);
    if (player_handle == NONE)
      continue;

    assert_halt((int16_t)i >= 0 &&
                (int16_t)i < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

    fp = (char *)*(int *)0x46bea8 + offset;
    player = datum_get(player_data, player_handle);
    unit = *(int *)((char *)player + 0x34);

    if (*(int *)(fp + 4) != unit) {
      assert_halt((int16_t)i >= 0 &&
                  (int16_t)i < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
      *(uint8_t *)(fp + 0x50) = 0;
      *(int *)(fp + 4) = unit;
      FUN_000dde80(i);
    }
    if (*(int *)(fp + 8) == NONE)
      FUN_000dde80(i);
    ((void (*)(int))0xde560)(i);
  }
}
/* --- first_person_weapons.obj batch drafts (2026-07-26) --- */

/* 0xdcaf0 — FP weapon state blob for a local player index. */
char *FUN_000dcaf0(int16_t local_player_index)
{
  if (local_player_index < 0 || local_player_index >= 4) {
    display_assert((char *)0x00266fc0, (char *)0x00282294, 0x599, 1);
    system_exit(-1);
  }
  return (char *)(*(int *)0x46bea8) + (int)local_player_index * 0x1ea0;
}

/* FUN_000dcdc0 (0xdcdc0) — readable C lift. */
int16_t FUN_000dcdc0(int object_handle)
{
  int16_t i;
  for (i = 0; i < 4; i++) {
    int player_handle = local_player_get_player_index(i);
    char *player;
    if (player_handle == -1)
      continue;
    player = (char *)datum_get(*(void **)0x5aa6d4, player_handle);
    if (*(int *)(player + 0x34) == object_handle)
      return i;
  }
  return (int16_t)-1;
}

/* first_person_weapon_draw (0xdce80) — XBE naked draft (batch 234). */
#if defined(__clang__)
static void (*const bdce80_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bdce80_exitfn)(int) = system_exit;
static int (*const bdce80_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void *(*const bdce80_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const bdce80_get)(int, int) = object_get_and_verify_type;
static void *(*const bdce80_tag)(int, int) = tag_get;
static void * (*const bdce80_c18e450)(void) = game_globals_get;
static void *(*const bdce80_elem)(void *, int, int) = tag_block_get_element;
static void * (*const bdce80_c18c0b0)(int object_handle, float lod) = scenario_leaf_index_from_point;
static void (*const bdce80_cdcbd0)(int mode_tag_index, int fp_nodes, int antr_tag_index, int anim_nodes, int16_t *node_remap) = fp_anim_apply_node_remap;
static void (*const bdce80_c123ed0)(int model_ref, float distance, void *node_matrices, void *arg4, void *node_transforms, void *node_matrices2, int lighting, void *position, int arg9, void *effect_record, int object_handle, int arg12, int render_flag) = FUN_00123ed0;

__attribute__((naked, noinline))
void first_person_weapon_draw(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xd38, %%esp\n\t"
      "movl 0x506548, %%eax\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "cmpw %%di, %%ax\n\t"
      "je .Lfirst_person_weapon_draw_7\n\t"
      "testw %%ax, %%ax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "jl .Lfirst_person_weapon_draw_1\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .Lfirst_person_weapon_draw_2\n\t"
      ".Lfirst_person_weapon_draw_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x599\n\t"
      "pushl $0x282294\n\t"
      "pushl $0x266fc0\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x506548, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lfirst_person_weapon_draw_2:\n\t"
      "movl 0x46bea8, %%ecx\n\t"
      "movswl %%si, %%esi\n\t"
      "imull $0x1ea0, %%esi, %%esi\n\t"
      "pushl %%eax\n\t"
      "addl %%ecx, %%esi\n\t"
      "call *%[cba3c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .Lfirst_person_weapon_draw_6\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x506548, %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[cba3c0]\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "je .Lfirst_person_weapon_draw_6\n\t"
      "cmpb $0, (%%esi)\n\t"
      "je .Lfirst_person_weapon_draw_6\n\t"
      "cmpl %%edi, 0x4(%%esi)\n\t"
      "je .Lfirst_person_weapon_draw_6\n\t"
      "cmpl %%edi, 0x8(%%esi)\n\t"
      "je .Lfirst_person_weapon_draw_6\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "pushl $4\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x77656170\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x478(%%edi), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lfirst_person_weapon_draw_6\n\t"
      "pushl $0xc0\n\t"
      "pushl $0\n\t"
      "call *%[c18e450]\n\t"
      "addl $0x17c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x478(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x616e7472\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl $0x7f7fffff\n\t"
      "pushl %%edx\n\t"
      "call *%[c18c0b0]\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movb 0x1b4(%%ebx), %%al\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb $0x10, %%al\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "jne .Lfirst_person_weapon_draw_3\n\t"
      "flds 0x32c(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lfirst_person_weapon_draw_3\n\t"
      "movw %%cx, -0x38(%%ebp)\n\t"
      "jmp .Lfirst_person_weapon_draw_4\n\t"
      ".Lfirst_person_weapon_draw_3:\n\t"
      "movl 0x32c(%%ebx), %%eax\n\t"
      "movl 0x330(%%ebx), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "movl 0x506550, %%eax\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "movl 0x506554, %%ecx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl 0x506558, %%edx\n\t"
      "movw $1, -0x38(%%ebp)\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      ".Lfirst_person_weapon_draw_4:\n\t"
      "movb 0x1d8c(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lfirst_person_weapon_draw_5\n\t"
      "movl 0x468(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lfirst_person_weapon_draw_5\n\t"
      "leal 0x1d8e(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x478(%%edi), %%ecx\n\t"
      "leal 0x108c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xd38(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[cdcbd0]\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl $8\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0x506550\n\t"
      "pushl %%edx\n\t"
      "leal 0xe4(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $0x168, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x468(%%edi), %%eax\n\t"
      "pushl $0\n\t"
      "leal -0xd38(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c123ed0]\n\t"
      "addl $0x44, %%esp\n\t"
      ".Lfirst_person_weapon_draw_5:\n\t"
      "movb 0x1e0e(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lfirst_person_weapon_draw_6\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ecx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lfirst_person_weapon_draw_6\n\t"
      "leal 0x1e10(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x478(%%edi), %%edx\n\t"
      "leal 0x108c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0xd38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cdcbd0]\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl $8\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0x506550\n\t"
      "pushl %%ecx\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "leal 0xe4(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0xc(%%ecx), %%edx\n\t"
      "addl $0x168, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl $0\n\t"
      "leal -0xd38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c123ed0]\n\t"
      "addl $0x44, %%esp\n\t"
      ".Lfirst_person_weapon_draw_6:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".Lfirst_person_weapon_draw_7:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(bdce80_assert), [exitfn] "m"(bdce80_exitfn), [cba3c0] "m"(bdce80_cba3c0), [dget] "m"(bdce80_dget), [get] "m"(bdce80_get), [tag] "m"(bdce80_tag), [c18e450] "m"(bdce80_c18e450), [elem] "m"(bdce80_elem), [c18c0b0] "m"(bdce80_c18c0b0), [cdcbd0] "m"(bdce80_cdcbd0), [c123ed0] "m"(bdce80_c123ed0)
      : "memory");
}
#else
#error "first_person_weapon_draw: clang naked draft required"
#endif


/* first_person_weapon_get_marker_by_name (0xdd190) — readable C lift. */
int16_t first_person_weapon_get_marker_by_name(int object_handle,
                                               const char *marker_name,
                                               void *out_markers,
                                               int16_t max_markers)
{
  char *weapon;
  int16_t local_player;
  char *fp;
  char *weap_tag;
  char *antr_tag;
  int model_ref;
  int antr_ref;

  weapon = (char *)object_try_and_get_and_verify_type(object_handle, 4);
  if (!weapon)
    return 0;

  local_player = FUN_000dcd60(object_handle);
  if (local_player == (int16_t)-1)
    return 0;
  if (director_get_perspective(local_player) != 0)
    return 0;

  fp = FUN_000dcaf0(local_player);
  weap_tag = (char *)tag_get(0x77656170, *(int *)weapon);
  if (!fp[0x1d8c])
    return 0;
  model_ref = *(int *)(weap_tag + 0x468);
  if (model_ref == -1)
    return 0;
  antr_ref = *(int *)(weap_tag + 0x478);
  if (antr_ref == -1)
    return 0;

  antr_tag = (char *)tag_get(0x616e7472, antr_ref);
  return FUN_00124730(model_ref, marker_name, 0, (int)(fp + 0x1d8e),
                      (int16_t)*(uint16_t *)(antr_tag + 0x68), fp + 0x108c, 0,
                      out_markers, max_markers);
}

/* first_person_weapon_center_flashlight (0xdd260) — readable C lift. */
void first_person_weapon_center_flashlight(int object_handle, float *out_position,
                                           float *out_forward, float *out_up)
{
  extern char DAT_00266fc0[];
  extern char DAT_00282294[];
  extern char DAT_00282364[];
  int16_t local_player;
  char *slots;
  char *slot;
  char marker[0x6c];
  int16_t n;
  float scale;

  local_player = FUN_000dcdc0(object_handle);
  if (local_player == (int16_t)-1)
    return;
  if ((int16_t)local_player < 0 || (int16_t)local_player >= 4) {
    display_assert(DAT_00266fc0, DAT_00282294, 0x599, 1);
    system_exit(-1);
  }

  slots = *(char **)0x46bea8;
  slot = slots + (int)local_player * 0x1ea0;
  if (!slot[0])
    return;

  n = first_person_weapon_get_marker_by_name(*(int *)(slot + 8), DAT_00282364,
                                            marker, 1);
  if (n <= 0)
    return;

  scale = *(float *)0x253398;
  out_position[0] = *(float *)(marker + 0x60) - *(float *)(marker + 0x3c) * scale;
  out_position[1] = *(float *)(marker + 0x64) - *(float *)(marker + 0x40) * scale;
  out_position[2] = *(float *)(marker + 0x68) - *(float *)(marker + 0x44) * scale;
  out_forward[0] = *(float *)(marker + 0x3c);
  out_forward[1] = *(float *)(marker + 0x40);
  out_forward[2] = *(float *)(marker + 0x44);
  out_up[0] = *(float *)(marker + 0x54);
  out_up[1] = *(float *)(marker + 0x58);
  out_up[2] = *(float *)(marker + 0x5c);
}

/* first_person_weapon_adjust_light (0xdd340) — readable C lift. */
char first_person_weapon_adjust_light(int object_handle, const char *marker_name,
                                      void *out_position, void *out_forward,
                                      void *out_up)
{
  char *weapon;
  char *unit;
  int light_datum;
  void *light;
  int16_t local_player;
  char *fp;
  char marker[0x6c];
  int16_t n;
  float *pos;
  float *fwd;
  float *up;

  weapon = (char *)object_get_and_verify_type(object_handle, 4);
  unit = (char *)object_get_and_verify_type(*(int *)(weapon + 0xcc), 3);
  light_datum = *(int *)(unit + 0x1c8);
  if (light_datum == -1)
    return 0;

  light = datum_get(*(void **)0x5aa6d4, light_datum);
  local_player = *(int16_t *)((char *)light + 2);
  if (local_player == (int16_t)-1)
    return 0;
  if (local_player != *(int16_t *)0x506548)
    return 0;

  fp = FUN_000dcaf0(local_player);
  if (!fp[0])
    return 0;

  n = first_person_weapon_get_marker_by_name(object_handle, marker_name, marker,
                                            1);
  if (n <= 0)
    return 0;

  pos = (float *)out_position;
  fwd = (float *)out_forward;
  up = (float *)out_up;
  pos[0] = *(float *)(marker + 0x60);
  pos[1] = *(float *)(marker + 0x64);
  pos[2] = *(float *)(marker + 0x68);
  fwd[0] = *(float *)(marker + 0x3c);
  fwd[1] = *(float *)(marker + 0x40);
  fwd[2] = *(float *)(marker + 0x44);
  up[0] = *(float *)(marker + 0x54);
  up[1] = *(float *)(marker + 0x58);
  up[2] = *(float *)(marker + 0x5c);
  return 1;
}

/* 0xdd580 — per-tick update for a local player's first-person weapon pose. */

void first_person_weapon_update(int16_t local_player_index)
{
  char *fp;
  char *weapon_obj;
  char *weap;
  char *mode;
  char *antr;
  char *anim_root;
  char *nodes;
  int weapon_handle;
  int16_t anim_index;
  int16_t frame;

  if (local_player_index < 0 || local_player_index >= 4) {
    display_assert((char *)0x00266fc0, (char *)0x00282294, 0x599, 1);
    system_exit(-1);
  }

  fp = (char *)(*(int *)0x46bea8) + (int)local_player_index * 0x1ea0;
  nodes = fp + 0x8c;

  if (fp[0x50] == 0) {
    vector_to_angles((float *)(fp + 0x60), (float *)0x50655c);
    *(float *)(fp + 0x70) = *(float *)0x506550;
    *(float *)(fp + 0x74) = *(float *)0x506554;
    *(float *)(fp + 0x78) = *(float *)0x506558;
  }

  /* Cache previous look angles / camera position, then refresh from camera. */
  *(int *)(fp + 0x68) = *(int *)(fp + 0x60);
  *(int *)(fp + 0x6c) = *(int *)(fp + 0x64);
  *(int *)(fp + 0x7c) = *(int *)(fp + 0x70);
  *(int *)(fp + 0x80) = *(int *)(fp + 0x74);
  *(int *)(fp + 0x84) = *(int *)(fp + 0x78);
  vector_to_angles((float *)(fp + 0x60), (float *)0x50655c);
  *(float *)(fp + 0x70) = *(float *)0x506550;
  *(float *)(fp + 0x74) = *(float *)0x506554;
  *(float *)(fp + 0x78) = *(float *)0x506558;
  *(float *)(fp + 0x54) = *(float *)0x50655c;
  *(float *)(fp + 0x58) = *(float *)0x506560;
  *(float *)(fp + 0x5c) = *(float *)0x506564;
  fp[0x50] = 1;

  weapon_handle = *(int *)(fp + 8);
  if (weapon_handle != -1) {
    if (object_try_and_get_and_verify_type(weapon_handle, 4) == 0) {
      error(3, (char *)0x002823ac, (int)local_player_index, weapon_handle);
      *(int *)(fp + 8) = -1;
      weapon_handle = -1;
    }
  }
  if (weapon_handle == -1)
    return;

  weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  weap = (char *)tag_get(0x77656170, *(int *)weapon_obj); /* 'weap' */
  mode = (char *)tag_get(0x6d6f6465, *(int *)(weap + 0x468)); /* 'mode' */
  antr = (char *)tag_get(0x616e7472, *(int *)(weap + 0x478)); /* 'antr' */
  if (*(int *)(antr + 0x48) == 0)
    return;

  anim_root = (char *)tag_block_get_element(antr + 0x48, 0, 0x1c);
  if (anim_root == 0)
    return;

  anim_index = *(int16_t *)(fp + 0x16);
  if (anim_index != (int16_t)0xffff) {
    char *animation = (char *)tag_block_get_element(antr + 0x74, anim_index, 0xb4);
    FUN_00121d60(0, animation, *(unsigned short *)(fp + 0x18), nodes);
  } else {
    display_assert((char *)0, (char *)0x00282294, 0x50e, 1);
    system_exit(-1);
    FUN_00123aa0(mode, nodes);
  }

  if (*(int *)(anim_root + 0x10) > 0x11) {
    int16_t *index_list = *(int16_t **)(anim_root + 0x14);
    int16_t ik_index = index_list[0x11]; /* word at +0x22 of element? XBE: [eax+0x22] where eax=list base+? */
    /* XBE: mov eax,[anim_root+0x14]; mov ax,[eax+0x22] */
    ik_index = *(int16_t *)((char *)index_list + 0x22);
    if (ik_index != (int16_t)0xffff) {
      char *ik_anim = (char *)tag_block_get_element(antr + 0x74, ik_index, 0xb4);
      if (*(int16_t *)(weap + 0x4e2) == 2) {
        int16_t state = *(int16_t *)(*(char **)0x46bea8 + 0xc);
        if (state == 0xd || state == 0xe) {
          int16_t ticks = (int16_t)(*(int16_t *)(weapon_obj + 0x25c) -
                                    *(int16_t *)(weapon_obj + 0x25a));
          frame = *(int16_t *)(weapon_obj + 0x260);
          if (ticks >= 0x2c) {
            char *trigger = (char *)tag_block_get_element(weap + 0x4f0, 0, 0x70);
            float t = (float)(ticks - 0x2c) * *(float *)0x2549d4;
            int16_t max_f;
            if (!(t <= 1.0f))
              t = 1.0f;
            max_f = *(int16_t *)(trigger + 0xa);
            {
              int16_t cur = *(int16_t *)(weapon_obj + 0x25e);
              if (cur > max_f)
                cur = max_f;
              {
                int delta = (int)cur - (int)frame;
                float add = (float)delta * t;
                /* fistp via FUN_001d9068 truncation */
                frame = (int16_t)((int)frame + (int)add);
              }
            }
          }
          overlay_animation_apply(ik_anim, frame, nodes);
        } else {
          frame = *(int16_t *)(weapon_obj + 0x260);
          if (frame < *(int16_t *)(ik_anim + 0x22))
            overlay_animation_apply(ik_anim, frame, nodes);
        }
      } else {
        frame = *(int16_t *)(weapon_obj + 0x260);
        if (frame < *(int16_t *)(ik_anim + 0x22))
          overlay_animation_apply(ik_anim, frame, nodes);
      }
    }
  }

  anim_index = *(int16_t *)(fp + 0x1a);
  if (anim_index != (int16_t)0xffff) {
    char *animation = (char *)tag_block_get_element(antr + 0x74, anim_index, 0xb4);
    overlay_animation_apply(animation, *(unsigned short *)(fp + 0x1c), nodes);
  }

  anim_index = *(int16_t *)(fp + 0x20);
  if (anim_index != (int16_t)0xffff) {
    char *animation = (char *)tag_block_get_element(antr + 0x74, anim_index, 0xb4);
    {
      float blend = *(float *)(weapon_obj + 0x1f4) + *(float *)0x253398;
      FUN_00122a50((int)animation, *(float *)(fp + 0x24), blend, (int)nodes);
    }
  }

  if (*(int *)(anim_root + 0x10) > 4) {
    int16_t ov_index = *(int16_t *)(*(char **)(anim_root + 0x14) + 8);
    if (ov_index != (int16_t)0xffff) {
      char *ov = (char *)tag_block_get_element(antr + 0x74, ov_index, 0xb4);
      if (*(int16_t *)(ov + 0x22) >= 9) {
        float s;
        s = *(float *)(fp + 0x30);
        if (s > 0.0f)
          overlay_animation_apply_scaled(ov, 0, s, nodes);
        else if (s < 0.0f)
          overlay_animation_apply_scaled(ov, 1, -s, nodes);
        s = *(float *)(fp + 0x34);
        if (s > 0.0f)
          overlay_animation_apply_scaled(ov, 3, s, nodes);
        else if (s < 0.0f)
          overlay_animation_apply_scaled(ov, 2, -s, nodes);
        s = *(float *)(fp + 0x40);
        if (s > 0.0f)
          overlay_animation_apply_scaled(ov, 4, s, nodes);
        else if (s < 0.0f)
          overlay_animation_apply_scaled(ov, 5, -s, nodes);
        s = *(float *)(fp + 0x44);
        if (s > 0.0f)
          overlay_animation_apply_scaled(ov, 7, s, nodes);
        else if (s < 0.0f)
          overlay_animation_apply_scaled(ov, 6, -s, nodes);
        s = *(float *)(fp + 0x28);
        if (s > 0.0f)
          overlay_animation_apply_scaled(ov, 8, s, nodes);
      }
    }
  }

  if (*(int16_t *)(fp + 0x8a) > 0) {
    ((void (*)(int, void *, void *, int, int))interpolate_node_orientations)(
        *(unsigned short *)(antr + 0x68), fp + 0x88c, nodes,
        *(unsigned short *)(fp + 0x88), *(unsigned short *)(fp + 0x8a));
  }

  ((void (*)(int, void *, void *, float *, float *, float *))
       animation_graph_node_matrices_from_orientations)(
      *(int *)(weap + 0x478), fp + 0x108c, nodes, (float *)0x506550,
      (float *)0x50655c, (float *)0x506568);
}



/* first_person_weapon_render_update (0xddae0) — XBE naked draft (batch 225). */
#if defined(__clang__)
static void (*const bddae0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bddae0_exitfn)(int) = system_exit;
static int16_t (*const bddae0_c86410)(int16_t local_player_index) = director_get_perspective;
static int16_t (*const bddae0_cb6a70)(int16_t local_player_index) = player_control_get_zoom_level;
static void (*const bddae0_cdcb30)(int16_t local_player_index, uint8_t activate) = FUN_000dcb30;

__attribute__((naked, noinline))
void first_person_weapon_render_update(void)
{
  __asm__ volatile(
      "movl 0x506548, %%eax\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "cmpw %%di, %%ax\n\t"
      "je .Lfirst_person_weapon_render_update_6\n\t"
      "testw %%ax, %%ax\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "jl .Lfirst_person_weapon_render_update_1\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .Lfirst_person_weapon_render_update_2\n\t"
      ".Lfirst_person_weapon_render_update_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x599\n\t"
      "pushl $0x282294\n\t"
      "pushl $0x266fc0\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x506548, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lfirst_person_weapon_render_update_2:\n\t"
      "movl 0x46bea8, %%edx\n\t"
      "movswl %%si, %%esi\n\t"
      "imull $0x1ea0, %%esi, %%esi\n\t"
      "movl 0x4(%%esi,%%edx,1), %%ecx\n\t"
      "addl %%edx, %%esi\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "je .Lfirst_person_weapon_render_update_5\n\t"
      "cmpl %%edi, 0x8(%%esi)\n\t"
      "je .Lfirst_person_weapon_render_update_5\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c86410]\n\t"
      "addl $4, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lfirst_person_weapon_render_update_3\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x506548, %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[cb6a70]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw %%di, %%ax\n\t"
      "jne .Lfirst_person_weapon_render_update_3\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lfirst_person_weapon_render_update_4\n\t"
      ".Lfirst_person_weapon_render_update_3:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".Lfirst_person_weapon_render_update_4:\n\t"
      "movl 0x506548, %%edi\n\t"
      "call *%[cdcb30]\n\t"
      "cmpb $0, (%%esi)\n\t"
      "popl %%ebx\n\t"
      "je .Lfirst_person_weapon_render_update_5\n\t"
      "movl 0x506548, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%edi\n\t"
      ".byte 0xe9, 0xf6, 0xf9, 0xff, 0xff\n\t"
      ".Lfirst_person_weapon_render_update_5:\n\t"
      "popl %%esi\n\t"
      ".Lfirst_person_weapon_render_update_6:\n\t"
      "popl %%edi\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [assert] "m"(bddae0_assert), [exitfn] "m"(bddae0_exitfn), [c86410] "m"(bddae0_c86410), [cb6a70] "m"(bddae0_cb6a70), [cdcb30] "m"(bddae0_cdcb30)
      : "memory");
}
#else
#error "first_person_weapon_render_update: clang naked draft required"
#endif


/* 0xddb90 — resolve a marker only for the currently rendered local player. */
#if defined(__clang__)
__attribute__((unused))
static int16_t (*const fp_marker_local)(int) = FUN_000dcd60;
__attribute__((unused))
static int16_t (*const fp_marker_by_name)(int, const char *, void *, int16_t) =
    first_person_weapon_get_marker_by_name;

/* first_person_weapon_get_marker_by_name_render (0xddb90) — readable C lift. */
int16_t first_person_weapon_get_marker_by_name_render(
    int object_handle, const char *marker_name, void *out_markers, int16_t max_markers)
{
  if (*(int16_t *)0x506548 != (int16_t)FUN_000dcd60(object_handle))
    return 0;
  return first_person_weapon_get_marker_by_name(
      object_handle, marker_name, out_markers, max_markers);
}

#else
int16_t first_person_weapon_get_marker_by_name_render(int object_handle,
                                                     const char *marker_name,
                                                     void *out_markers,
                                                     int16_t max_markers)
{
  if (FUN_000dcd60(object_handle) != *(int16_t *)0x506548)
    return 0;
  return first_person_weapon_get_marker_by_name(object_handle, marker_name,
                                                out_markers, max_markers);
}
#endif

/* 0xde0e0 — bind an object into a local player's first-person weapon slot. */
#if defined(__i386__) && defined(__GNUC__)
__attribute__((noinline))
#endif
/* FUN_000de0e0 (0xde0e0) — readable C lift. */
void FUN_000de0e0(int object_handle, int16_t local_player_index)
{
  extern char DAT_00266fc0[];
  extern char DAT_00282294[];
  char *slot;
  if ((int16_t)local_player_index < 0 || (int16_t)local_player_index >= 4) {
    display_assert(DAT_00266fc0, DAT_00282294, 0x599, 1);
    system_exit(-1);
  }
  slot = *(char **)0x46bea8 + (int16_t)local_player_index * 0x1ea0;
  slot[0x50] = 0;
  *(int *)(slot + 4) = object_handle;
  FUN_000dde80(local_player_index);
}

/* first_person_weapon_message_from_unit (0xde360) — readable C lift. */
void first_person_weapon_message_from_unit(int unit_handle, int message_type)
{
  int16_t local_player = FUN_000dcdc0(unit_handle);
  FUN_000de140(local_player, message_type);
  if (local_player == (int16_t)-1) {
    char *unit = (char *)object_get_and_verify_type(unit_handle, 3);
    int16_t weapon_index = *(int16_t *)(unit + 0x2a2);
    if (weapon_index != (int16_t)-1)
      FUN_000dc9d0(message_type, (int)weapon_index);
  }
}

/* 0xde3f0 — Advance first-person weapon state for one local player. */
#if defined(__i386__) && defined(__GNUC__)
__attribute__((regparm(1)))
#endif
/* FUN_000de3f0 (0xde3f0) — XBE naked draft (batch 2269). */
#if defined(__clang__)
static void (*const bde3f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bde3f0_exitfn)(int) = system_exit;
static void (*const bde3f0_cddbd0)(int local_player_index, int state, int param_3) = FUN_000ddbd0;
static void *(*const bde3f0_get)(int, int) = object_get_and_verify_type;
static void *(*const bde3f0_tag)(int, int) = tag_get;

__attribute__((naked, noinline))
void FUN_000de3f0(int local_player_index)
{
  __asm__ volatile(
      "testw %%bx, %%bx\n\t"
      "jl .LFUN_000de3f0_1\n\t"
      "cmpw $4, %%bx\n\t"
      "jl .LFUN_000de3f0_2\n\t"
      ".LFUN_000de3f0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x599\n\t"
      "pushl $0x282294\n\t"
      "pushl $0x266fc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000de3f0_2:\n\t"
      "movl 0x46bea8, %%edx\n\t"
      "pushl %%esi\n\t"
      "movswl %%bx, %%esi\n\t"
      "imull $0x1ea0, %%esi, %%esi\n\t"
      "movswl 0xc(%%esi,%%edx,1), %%eax\n\t"
      "addl %%edx, %%esi\n\t"
      "cmpl $0x17, %%eax\n\t"
      "ja .LFUN_000de3f0_9\n\t"
      "movzbl 0xde548(%%eax), %%eax\n\t"
      "jmp *.LFUN_000de3f0_jt(,%%eax,4)\n\t"
      ".LFUN_000de3f0_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[cddbd0]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LFUN_000de3f0_4:\n\t"
      "movl $3, %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[cddbd0]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LFUN_000de3f0_5:\n\t"
      "decw 0x18(%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LFUN_000de3f0_6:\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "pushl $4\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x77656170\n\t"
      "call *%[tag]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $1, 0x4e2(%%eax)\n\t"
      "jne .LFUN_000de3f0_3\n\t"
      "cmpw $2, 0x1e94(%%esi)\n\t"
      "jne .LFUN_000de3f0_3\n\t"
      "jmp .LFUN_000de3f0_8\n\t"
      ".LFUN_000de3f0_7:\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x77656170\n\t"
      "call *%[tag]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $1, 0x4e2(%%eax)\n\t"
      "jne .LFUN_000de3f0_3\n\t"
      "movw 0x1e94(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_000de3f0_3\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_000de3f0_3\n\t"
      "cmpw $2, %%ax\n\t"
      "je .LFUN_000de3f0_8\n\t"
      "cmpw $1, %%ax\n\t"
      "je .LFUN_000de3f0_8\n\t"
      "pushl $1\n\t"
      "pushl $0x31f\n\t"
      "pushl $0x282294\n\t"
      "pushl $0x2823e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000de3f0_8:\n\t"
      "movb 0x1e90(%%esi), %%al\n\t"
      "negb %%al\n\t"
      "sbbl %%eax, %%eax\n\t"
      "addl $0x11, %%eax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_000de3f0_9\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[cddbd0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000de3f0_9:\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      "movl %%edi, %%edi\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000de3f0_jt:\n\t"
      ".long .LFUN_000de3f0_3\n\t"
      ".long .LFUN_000de3f0_4\n\t"
      ".long .LFUN_000de3f0_7\n\t"
      ".long .LFUN_000de3f0_6\n\t"
      ".long .LFUN_000de3f0_5\n\t"
      ".long .LFUN_000de3f0_9\n\t"
      ".text\n\t"
      :
      : [assert] "m"(bde3f0_assert), [exitfn] "m"(bde3f0_exitfn), [cddbd0] "m"(bde3f0_cddbd0), [get] "m"(bde3f0_get), [tag] "m"(bde3f0_tag)
      : "memory");
}
#else
#error "FUN_000de3f0: clang naked draft required"
#endif


/* 0xde560 — Per-frame first-person weapon animation and overlay update. */

void FUN_000de560(int local_player_index)
{
  char *fp;
  int weapon_handle;
  char *weapon_obj;
  char *weapon_tag;
  char *mode_tag;
  int unit_handle;
  int sound_index;
  char low_speed;
  float speed;
  int16_t anim_result;

  if ((int16_t)local_player_index < 0 || (int16_t)local_player_index >= 4) {
    display_assert((char *)0x00266fc0, (char *)0x00282294, 0x599, 1);
    system_exit(-1);
  }

  fp = (char *)(*(int *)0x46bea8 + (int)(int16_t)local_player_index * 0x1ea0);
  weapon_handle = *(int *)(fp + 8);
  if (weapon_handle != -1) {
    weapon_obj = (char *)object_try_and_get_and_verify_type(weapon_handle, 4);
    if (weapon_obj == 0) {
      error(3, (char *)0x002823ac, local_player_index, weapon_handle);
      *(int *)(fp + 8) = -1;
    }
  }

  unit_handle = *(int *)(fp + 4);
  if (unit_handle == -1 || *(int *)(fp + 8) == -1)
    goto finish;

  weapon_obj = (char *)object_get_and_verify_type(*(int *)(fp + 8), 4);
  weapon_tag = (char *)tag_get(0x77656170, *(int *)weapon_obj);
  mode_tag = (char *)tag_get(0x6d6f6465, *(int *)(weapon_tag + 0x468));

  if (*(int16_t *)(fp + 0xc) == 3 || *(int16_t *)(fp + 0xc) == 1) {
    if ((*(unsigned char *)(weapon_obj + 0x1dc) & 2) != 0)
      FUN_000ddbd0(local_player_index, 0x16, 1);
    if ((*(unsigned char *)(weapon_obj + 0x1dc) & 1) == 0)
      FUN_000ddbd0(local_player_index, 0, 1);
  }

  sound_index = -1;
  anim_result = (int16_t)animation_update_internal(
      0, *(int *)(weapon_tag + 0x478), (int16_t *)(fp + 0x16), &sound_index);
  if (anim_result == 1 || anim_result == 2)
    FUN_000de3f0(local_player_index);

  if (sound_index != -1 &&
      director_get_perspective((int16_t)local_player_index) == 0) {
    *(int *)(fp + 0x1e98) = object_impulse_sound_new(
        *(int *)(fp + 8), sound_index, -1, (float *)(uintptr_t)*(int *)0x31fc1c,
        (float *)(uintptr_t)*(int *)0x31fc3c, 1.0f);
    *(int16_t *)(fp + 0x1e9c) = *(int16_t *)(fp + 0xc);
  }

  speed = sqrtf(*(float *)(weapon_obj + 0x228) * *(float *)(weapon_obj + 0x228) +
                *(float *)(weapon_obj + 0x22c) * *(float *)(weapon_obj + 0x22c) +
                *(float *)(weapon_obj + 0x230) * *(float *)(weapon_obj + 0x230));
  low_speed = (speed <= *(float *)0x25496c);
  if (unit_flying_through_air(unit_handle))
    low_speed = 0;

  if (*(int16_t *)(fp + 0x1a) != -1) {
    if (!low_speed && *(int16_t *)(fp + 0xc) == 0)
      FUN_000dd4d0((int16_t)local_player_index, 6);
    *(int16_t *)(fp + 0x1a) = -1;
  } else if (low_speed) {
    char *rtna = (char *)tag_get(0x616e7472, *(int *)(mode_tag + 0x44));
    char *block = (char *)tag_block_get_element(rtna + 0x48, 0, 0x1c);
    if (block != 0) {
      *(int16_t *)(fp + 0x1c) = 0;
      if (*(int *)(block + 0x10) > 3)
        *(int16_t *)(fp + 0x1a) =
            *(int16_t *)(*(int *)(block + 0x14) + 6);
      else
        *(int16_t *)(fp + 0x1a) = -1;
    }
  }

  if (*(int16_t *)(fp + 0x20) == -1) {
    if (*(int16_t *)(fp + 0xc) == 4) {
      char *rtna = (char *)tag_get(0x616e7472, *(int *)(mode_tag + 0x44));
      char *block = (char *)tag_block_get_element(rtna + 0x48, 0, 0x1c);
      if (block != 0) {
        *(int *)(fp + 0x24) = 0;
        if (*(int *)(block + 0x10) > 0xf)
          *(int16_t *)(fp + 0x20) =
              *(int16_t *)(*(int *)(block + 0x14) + 0x1e);
        else
          *(int16_t *)(fp + 0x20) = -1;
      }
    }
  } else if (*(int16_t *)(fp + 0xc) == 4) {
    char *animation = (char *)tag_block_get_element(
        mode_tag + 0x74, (int)*(int16_t *)(fp + 0x20), 0xb4);
    float frame = (*(float *)(weapon_obj + 0x1f4) + 1.0f) * 2.0f +
                  *(float *)(fp + 0x24);
    frame *= (float)(*(int16_t *)(animation + 0x22));
    *(float *)(fp + 0x24) = frame;
  } else {
    *(int16_t *)(fp + 0x20) = -1;
  }

  if (*(char *)(fp + 0x50) != 0) {
    float pitch_delta;
    float yaw_delta;
    float clamped_pitch;
    float clamped_yaw;

    accelerate_to_position((float *)(fp + 0x30), (float *)(fp + 0x38), 0.0f,
                           0.0625f, 0.5f, -1.0f, 1.0f, 0);
    accelerate_to_position((float *)(fp + 0x34), (float *)(fp + 0x3c), 0.0f,
                           0.0625f, 0.5f, -1.0f, 1.0f, 0);
    pitch_delta = FUN_000b6dd0(*(float *)(fp + 0x60), *(float *)(fp + 0x68));
    yaw_delta = FUN_000b6dd0(*(float *)(fp + 0x64), *(float *)(fp + 0x6c));
    pitch_delta *= *(float *)0x253394;
    yaw_delta *= *(float *)0x282490;

    if (pitch_delta <= *(float *)0x255e94)
      clamped_pitch = -1.0f;
    else if (pitch_delta >= 1.0f)
      clamped_pitch = 1.0f;
    else
      clamped_pitch = pitch_delta;

    if (yaw_delta <= *(float *)0x255e94)
      clamped_yaw = -1.0f;
    else if (yaw_delta >= 1.0f)
      clamped_yaw = 1.0f;
    else
      clamped_yaw = yaw_delta;

    accelerate_to_position((float *)(fp + 0x40), (float *)(fp + 0x48),
                           clamped_pitch, 0.2f, 0.5f, -1.0f, 1.0f, 0);
    accelerate_to_position((float *)(fp + 0x44), (float *)(fp + 0x4c),
                           clamped_yaw, 0.2f, 0.5f, -1.0f, 1.0f, 0);
    accelerate_to_position((float *)(fp + 0x28), (float *)(fp + 0x2c), 0.0f,
                           0.01f, 0.0f, 0.0f, 0.0f, 0);
    if (*(float *)(fp + 0x28) == 1.0f)
      *(float *)(fp + 0x2c) = 0.0f;
  }

  if (*(int16_t *)(fp + 0x8a) > 0) {
    *(int16_t *)(fp + 0x88) += 1;
    if (*(int16_t *)(fp + 0x88) >= *(int16_t *)(fp + 0x8a))
      *(int16_t *)(fp + 0x8a) = 0;
  }

  if (player_control_get_autoaim_level((int16_t)local_player_index) <= 0.0f &&
      player_control_get_zoom_level((int16_t)local_player_index) == -1 &&
      *(float *)(fp + 0x28) == 0.0f && *(float *)(fp + 0x30) == 0.0f &&
      *(float *)(fp + 0x34) == 0.0f && *(float *)(fp + 0x40) == 0.0f &&
      *(float *)(fp + 0x44) == 0.0f && *(int16_t *)(fp + 0xc) == 0) {
    char *globals = (char *)game_globals_get();
    char *entry = (char *)tag_block_get_element(globals + 0x170, 0, 0xf4);
    if (*(int16_t *)(fp + 0xe) == 0) {
      float range = FUN_000849f0(*(float *)(entry + 0x9c),
                                 *(float *)(entry + 0xa0));
      range *= *(float *)0x253394;
      *(int16_t *)(fp + 0xe) = (int16_t)(int)range;
    }
    *(int16_t *)(fp + 0x10) += 1;
    if (*(int16_t *)(fp + 0x10) > *(int16_t *)(fp + 0xe)) {
      *(int16_t *)(fp + 0xe) = 0;
      if (real_local_random() <= *(float *)(entry + 0xa4))
        FUN_000ddbd0(local_player_index, 5, 1);
    }
  } else if (*(int16_t *)(fp + 0xc) == 5) {
    *(int16_t *)(fp + 0x10) = 0;
    FUN_000ddbd0(local_player_index, 0, 1);
  } else {
    *(int16_t *)(fp + 0x10) = 0;
  }

finish:
  *(int16_t *)(fp + 0x12) -= 1;
}


