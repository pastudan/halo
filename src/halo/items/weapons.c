#include <stdint.h>
/* 0xfae80 — weapon_get_label */
char *weapon_get_label(int weapon_handle)
{
  char *result = (char *)0x25386f;
  int *obj;
  if (weapon_handle != -1) {
    obj = (int *)object_get_and_verify_type(weapon_handle, 4);
    result = (char *)tag_get(0x77656170, *obj) + 0x30c;
  }
  return result;
}

/* 0xfaeb0 — weapon_set_integrated_light_power */
void weapon_set_integrated_light_power(int weapon_handle, int light_power)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  *(int *)(weapon_obj + 0x1f8) = light_power;
}

/* weapon_preprocess_node_orientations (0xfae30) — readable C lift. */
void weapon_preprocess_node_orientations(int weapon_handle)
{
  int *obj;
  unsigned char *weap;
  unsigned char *antr;
  int count;

  obj = (int *)object_get_and_verify_type(weapon_handle, 4);
  weap = (unsigned char *)tag_get(0x77656170, *obj);
  antr = (unsigned char *)tag_get(0x616e7472, *(int *)(weap + 0x44));
  count = *(int *)(antr + 0x18);
  if (count != 0)
    tag_block_get_element(antr + 0x18, 0, 0x1c);
}



/* 0xfaed0 — weapon_estimate_time_to_target
 *
 * Given a weapon object handle, a trigger index, and a float value, returns
 * the result of evaluating the projectile charge function for that trigger.
 *
 * Steps:
 *   1. Verify weapon object and get its 'weap' tag (first dword of object
 *      data is the tag index).
 *   2. Validate trigger_index against the triggers block at tag+0x4fc.
 *   3. Get the trigger element (element size 0x114) at the given index.
 *   4. Read the 'proj' (projectile) tag reference from trigger+0xa0.
 *   5. Call projectile_estimate_time_to_target(proj_tag, param_3) — returns a
 * float ratio.
 *   6. Default return value is 0.0f (loaded from 0x2533c0 which holds 0.0f).
 *
 * Confirmed: PUSH 0x4 / PUSH EAX → object_get_and_verify_type at 0xfaed6.
 * Confirmed: MOV ECX,[EAX] / PUSH ECX / PUSH 0x77656170 → tag_get at 0xfaedf.
 * Confirmed: FLD [0x2533c0] (0.0f default) at 0xfaeeb.
 * Confirmed: MOV CX,[EBP+0xc] (trigger_index) at 0xfaef1.
 * Confirmed: ADD ESP,0x10 cleans 4 cdecl args (both calls) at 0xfaef5.
 * Confirmed: MOV EDX,[EAX+0x4fc] / ADD EAX,0x4fc block count/ptr at 0xfaefd.
 * Confirmed: PUSH 0x114 / PUSH ECX / PUSH EAX → tag_block_get_element at
 * 0xfaf0f. Confirmed: MOV EDX,[EBP+0x10] (param_3) at 0xfaf1d. Confirmed: MOV
 * EAX,[EAX+0xa0] (proj tag ref) at 0xfaf20. Confirmed: PUSH EDX / PUSH EAX /
 * PUSH 0x70726f6a → tag_get('proj') at 0xfaf29. ADD ESP,0x8 cleans 2 args; EDX
 * (param_3) already on stack for projectile_estimate_time_to_target. Confirmed:
 * PUSH EAX / CALL projectile_estimate_time_to_target at 0xfaf38; ADD ESP,0x8
 * cleans 2.
 */
float weapon_estimate_time_to_target(int weapon_handle, int16_t trigger_index,
                                     float param_3)
{
  int *weapon_data = (int *)object_get_and_verify_type(weapon_handle, 4);
  void *weap_tag = tag_get(0x77656170, weapon_data[0]);
  float result = 0.0f;

  if (trigger_index >= 0) {
    int *trig_block = (int *)((char *)weap_tag + 0x4fc);
    int trigger_count = trig_block[0];
    int trigger_idx = (int)trigger_index;
    if (trigger_idx < trigger_count) {
      void *trig_elem = tag_block_get_element(trig_block, trigger_idx, 0x114);
      int proj_ref = *(int *)((char *)trig_elem + 0xa0);
      void *proj_tag = tag_get(0x70726f6a, proj_ref);
      result = projectile_estimate_time_to_target(proj_tag, param_3);
    }
  }

  return result;
}

/* weapon_must_be_readied (0xfb090) — readable C lift. */
int weapon_must_be_readied(int weapon_handle)
{
  int *obj;
  unsigned int *tag;

  obj = (int *)object_get_and_verify_type(weapon_handle, 4);
  tag = (unsigned int *)tag_get(0x77656170, *obj);
  return (int)((tag[0x308 / 4] >> 3) & 1);
}

/* 0xfb0c0 — weapon_is_flag */
bool weapon_is_flag(int object_index)
{
  int *obj = (int *)object_get_and_verify_type(object_index, 4);
  uint32_t *tag = (uint32_t *)tag_get(0x77656170, *obj);
  return (tag[0x308 / 4] >> 3) & 1;
}

/* weapon_prevents_grenade_throwing (0xfb0f0) — readable C lift. */
int weapon_prevents_grenade_throwing(int weapon_handle)
{
  unsigned char *obj;
  unsigned int *tag;
  unsigned char mode;
  int bit;

  if (weapon_handle == -1)
    return 1;
  obj = (unsigned char *)object_get_and_verify_type(weapon_handle, 4);
  tag = (unsigned int *)tag_get(0x77656170, *(int *)obj);
  mode = obj[0x1e8];
  bit = (int)((tag[0x308 / 4] >> 6) & 1);
  if (mode < 5 || mode > 10)
    return bit;
  return 1;
}

/* 0xfb140 — weapon_get_animation_frame
 *
 * Looks up a weapon's animation graph and returns a frame count for
 * the requested animation slot. param_2 selects the field (0 -> offset
 * 0x22, 1 -> offset 0x34), param_3 is the animation index used to look
 * up into the first tag block element, param_4 selects a variant when
 * the weapon type at tag+0x4e2 is 1 (dual-wield).
 *
 * Confirmed: cdecl, 4 stack args.
 * Confirmed: CALL object_get_and_verify_type(weapon_handle, 4) at 0xfb14c.
 * Confirmed: CALL tag_get(0x77656170, *obj) at 0xfb159.
 * Confirmed: tag+0x478 is antr tag_index, tag+0x4e2 is weapon type.
 * Confirmed: tag_block at antr+0x48 element size 0x1c.
 * Confirmed: tag_block at antr+0x74 element size 0xb4.
 * Confirmed: switch on param_2: case 0 reads +0x22, case 1 reads +0x34.
 * Confirmed: assert at weapons.c line 0x634 for invalid param_2.
 * Confirmed: dual-wield branch reads indices 0x17(+0x2e), 0x18(+0x30),
 *   0x19(+0x32) from first element's index array.
 */
int16_t weapon_get_animation_frame(int weapon_handle, int16_t param_2,
                                   int16_t param_3, int16_t param_4)
{
  uint32_t *weapon_data;
  int weap_tag;
  int16_t result;
  int antr;
  int elem0;
  int16_t anim_index;
  void *antr_block;
  int anim_elem;
  weapon_data = (uint32_t *)object_get_and_verify_type(weapon_handle, 4);
  weap_tag = (int)tag_get(0x77656170, weapon_data[0]);
  result = 0;

  if (*(int *)(weap_tag + 0x478) == -1)
    return result;

  antr = (int)tag_get(0x616e7472, *(int *)(weap_tag + 0x478));

  if (*(int *)(antr + 0x48) == 0)
    return result;

  elem0 = (int)tag_block_get_element((void *)(antr + 0x48), 0, 0x1c);
  if (elem0 == 0)
    return result;

  if (param_3 < 0 || (int)param_3 >= *(int *)(elem0 + 0x10))
    return result;

  anim_index = *(int16_t *)(*(int *)(elem0 + 0x14) + param_3 * 2);
  if (anim_index == -1)
    return result;

  antr_block = (void *)(antr + 0x74);
  anim_elem = (int)tag_block_get_element(antr_block, (int)anim_index, 0xb4);

  if (param_2 == 0) {
    result = *(int16_t *)(anim_elem + 0x22);
  } else if (param_2 == 1) {
    result = *(int16_t *)(anim_elem + 0x34);
  } else {
    display_assert(0, "c:\\halo\\SOURCE\\items\\weapons.c", 0x634, 1);
    system_exit(-1);
  }

  /* Dual-wield variant override: weapon type == 1 and param_2 == 0 */
  if (param_2 == 0 && *(int16_t *)(weap_tag + 0x4e2) == 1) {
    int idx_a;
    int elem_a;
    int idx_b;
    int idx_c;
    if (*(int *)(elem0 + 0x10) < 0x18) {
      idx_a = -1;
    } else {
      idx_a = (int)*(int16_t *)(*(int *)(elem0 + 0x14) + 0x2e);
    }
    elem_a = (int)tag_block_get_element(antr_block, idx_a, 0xb4);

    if (*(int *)(elem0 + 0x10) < 0x19) {
      idx_b = -1;
    } else {
      idx_b = (int)*(int16_t *)(*(int *)(elem0 + 0x14) + 0x30);
    }
    tag_block_get_element(antr_block, idx_b, 0xb4);

    if (*(int *)(elem0 + 0x10) < 0x1a) {
      idx_c = -1;
    } else {
      idx_c = (int)*(int16_t *)(*(int *)(elem0 + 0x14) + 0x32);
    }
    tag_block_get_element(antr_block, idx_c, 0xb4);

    if (param_4 == 0) {
      result = *(int16_t *)(elem_a + 0x22);
    } else if (param_4 == 2) {
      return *(int16_t *)(elem_a + 0x22);
    }
  }

  return result;
}

void *FUN_000fb370(void *weapon_obj, int16_t magazine_index)
{
  int *tag_data = (int *)tag_get(0x77656170, *(int *)weapon_obj);

  assert_halt(magazine_index >= 0 &&
              magazine_index < *(int *)((char *)tag_data + 0x4f0));

  return (void *)((char *)weapon_obj + (magazine_index + 50) * 12);
}

/* weapon_overcharged (0xfb2f0) — readable C lift. */
int weapon_overcharged(int weapon_handle)
{
  unsigned char *obj;
  unsigned char state;

  obj = (unsigned char *)object_get_and_verify_type(weapon_handle, 4);
  state = obj[0x211];
  if (state == 2 || state == 3)
    return 1;
  return 0;
}

/* 0xfb3c0 — weapon_has_activity
 *
 * Returns true if the weapon has any active triggers, magazines, or
 * pending activity. Checks five fields in the weapon data.
 *
 * Confirmed: regparm, weapon_handle in EAX.
 * Confirmed: PUSH 4 / PUSH EAX / CALL object_get_and_verify_type.
 * Confirmed: checks offsets 0x211, 0x235, 0x258, 0x264, 0x1e8.
 * Confirmed: returns 0 (false) only if ALL five are zero/null.
 */
bool weapon_has_activity(int weapon_handle)
{
  char *weapon_data = (char *)object_get_and_verify_type(weapon_handle, 4);

  if (*(char *)(weapon_data + 0x211) != 0)
    return true;
  if (*(char *)(weapon_data + 0x235) != 0)
    return true;
  if (*(int16_t *)(weapon_data + 0x258) != 0)
    return true;
  if (*(int16_t *)(weapon_data + 0x264) != 0)
    return true;
  if (*(char *)(weapon_data + 0x1e8) != 0)
    return true;

  return false;
}

/* 0xfb6e0 — weapon_start_effect
 *
 * Starts an effect or sound associated with a weapon trigger. Resolves
 * the parent object, determines the tag group of the trigger effect
 * (0x65666665='effe' or 0x736e6421='snd!'), and dispatches accordingly.
 *
 * Confirmed: regparm, weapon_handle in EAX, 3 stack args.
 * Confirmed: MOV ESI, EAX at 0xfb6e8 saves weapon_handle.
 * Confirmed: if trigger_effect == -1, returns -1 immediately.
 * Confirmed: object byte+4 bit 0 checked; if set and +0xcc != -1,
 *   parent_handle = object+0xcc.
 * Confirmed: second object_get_and_verify_type call to get unit handle.
 * Confirmed: tag_get_group_tag returns tag group; dispatches on effe/snd!.
 * Confirmed: assert at weapons.c line 0x9d2 for unknown tag group.
 * Confirmed: snd! branch reads globals [0x31fc1c] and [0x31fc3c].
 * Confirmed: effe branch calls FUN_0009ec30 with 8 args.
 */
int weapon_start_effect(int trigger_effect, float scale, float param_3,
                        int weapon_handle)
{
  int result = -1;
  char *weapon_data;
  int parent_handle;
  char *weapon_data2;
  int object_handle;
  int tag_group;

  if (trigger_effect == -1)
    return result;

  /* Determine parent handle: default to weapon_handle, but if the
   * object has bit 0 of byte+4 set and offset 0xcc is valid, use
   * the parent object handle. */
  weapon_data = (char *)object_get_and_verify_type(weapon_handle, 4);
  parent_handle = weapon_handle;
  if ((*(uint8_t *)(weapon_data + 4) & 1) != 0 &&
      *(int *)(weapon_data + 0xcc) != -1) {
    parent_handle = *(int *)(weapon_data + 0xcc);
  }

  /* Determine object_handle (unit) from weapon's parent ref */
  weapon_data2 = (char *)object_get_and_verify_type(weapon_handle, 4);
  object_handle = -1;
  if (*(int *)(weapon_data2 + 0xcc) != -1) {
    int check =
      (int)object_try_and_get_and_verify_type(*(int *)(weapon_data2 + 0xcc), 3);
    if (check != 0) {
      object_handle = *(int *)(weapon_data2 + 0xcc);
    }
  }

  /* Dispatch based on tag group */
  tag_group = tag_get_group_tag(trigger_effect);
  if (tag_group == 0x65666665) {
    /* 'effe' — visual/particle effect */
    result = (int)FUN_0009ec30(trigger_effect, object_handle, parent_handle, -1,
                               scale, param_3, 0, 0);
  } else if (tag_group == 0x736e6421) {
    /* 'snd!' — sound effect */
    float *position = *(float **)0x31fc1c;
    float *forward = *(float **)0x31fc3c;
    object_impulse_sound_new(object_handle, trigger_effect, -1, position,
                             forward, scale);
    result = -1;
  } else {
    display_assert(0, "c:\\halo\\SOURCE\\items\\weapons.c", 0x9d2, 1);
    system_exit(-1);
    result = -1;
  }

  return result;
}

/* 0xfba20 — weapon_set_animation_state
 *
 * Sets the weapon's animation state by looking up the animation graph
 * and choosing a random animation for the given state. The state
 * parameter arrives in BX.
 *
 * Confirmed: regparm, state in BX. 2 stack args (weapon_handle, param_2).
 * Confirmed: PUSH 4 / PUSH [EBP+8] / CALL object_get_and_verify_type.
 * Confirmed: tag_get(0x77656170, *obj) for weapon tag.
 * Confirmed: param_2 == 0 && weapon_data+0x1e8 != 0 => priority check.
 * Confirmed: tag+0x44 is the animation graph tag_index (antr).
 * Confirmed: tag_block at antr+0x18, element size 0x1c.
 * Confirmed: switch on state (0..10) maps to animation indices.
 * Confirmed: model_animation_choose_random(1, tag+0x44, anim_index).
 * Confirmed: stores to weapon_data+0x80, +0x82, +0x1e8.
 * Confirmed: tail section resolves unit handle and calls
 * unit_handle_weapon_state_change. Confirmed: returns AL=1 on success, AL=0 on
 * early exit.
 */
int weapon_set_animation_state(int weapon_handle, char param_2, int16_t state)
{
  uint32_t *weapon_data =
    (uint32_t *)object_get_and_verify_type(weapon_handle, 4);
  int weap_tag = (int)tag_get(0x77656170, weapon_data[0]);
  int antr;
  int elem;
  int16_t anim_slot;
  uint16_t raw_index;
  int16_t chosen;

  /* Priority check: if param_2 is 0 and weapon has a current state,
   * only allow transitions from equal or higher priority */
  if (param_2 == 0) {
    int16_t current_state = (int16_t) * (char *)((char *)weapon_data + 0x1e8);
    if (current_state != 0) {
      if (current_state < 1)
        return 0;
      if (current_state > 2)
        return 0;
      if (state < current_state)
        return 0;
    }
  }

  /* Look up animation graph */
  if (*(int *)(weap_tag + 0x44) == -1)
    goto tail;

  antr = (int)tag_get(0x616e7472, *(int *)(weap_tag + 0x44));
  if (*(int *)(antr + 0x18) == 0)
    goto tail;

  elem = (int)tag_block_get_element((void *)(antr + 0x18), 0, 0x1c);
  if (elem == 0)
    goto tail;

  /* Map weapon animation state to animation block index */
  switch (state) {
  case 0:
    anim_slot = 0;
    break;
  case 1:
    anim_slot = 9;
    break;
  case 2:
    anim_slot = 10;
    break;
  case 3:
    anim_slot = 5;
    break;
  case 4:
    anim_slot = 6;
    break;
  case 5:
  case 6:
    anim_slot = 3;
    break;
  case 7:
  case 8:
    anim_slot = 8;
    break;
  case 9:
    anim_slot = 1;
    break;
  case 10:
    anim_slot = 2;
    break;
  default:
    goto tail;
  }

  /* Resolve animation index from the lookup table */
  if ((int)anim_slot < *(int *)(elem + 0x10)) {
    raw_index = *(uint16_t *)(*(int *)(elem + 0x14) + anim_slot * 2);
    if (raw_index == 0xffff) {
      if (state != 0)
        goto tail;
    }
  } else {
    raw_index = 0xffff;
    if (state != 0)
      goto tail;
  }

  /* Choose a random animation and set the weapon state */
  chosen = (int16_t)model_animation_choose_random(
    1, *(int *)(weap_tag + 0x44), (int16_t)raw_index);
  *(int16_t *)((char *)weapon_data + 0x80) = chosen;
  *(int16_t *)((char *)weapon_data + 0x82) = 0;
  *(char *)((char *)weapon_data + 0x1e8) = (char)state;

tail:
  /* Resolve unit handle and notify sound system */
  {
    int unit_data;
    int unit_handle;
    int check;
    int check2;
    unit_data = (int)object_get_and_verify_type(weapon_handle, 4);
    unit_handle = -1;
    if (*(int *)(unit_data + 0xcc) != -1) {
      check =
        (int)object_try_and_get_and_verify_type(*(int *)(unit_data + 0xcc), 3);
      if (check != 0) {
        unit_handle = *(int *)(unit_data + 0xcc);
      }
    }
    check2 = (int)object_try_and_get_and_verify_type(unit_handle, 3);
    if (check2 != 0) {
      unit_handle_weapon_state_change(unit_handle, state);
    }
  }
  return 1;
}

/* weapon_set_total_rounds (0xfbbd0)
 *
 * Sets weapon magazine rounds from an input array. For each magazine,
 * clamps the input value to the magazine's maximum capacity, then clamps
 * the loaded rounds to not exceed the new total.
 */
void weapon_set_total_rounds(int weapon_handle, int16_t *rounds_array)
{
  int *weapon = (int *)object_get_and_verify_type(weapon_handle, 4);
  int tag_data = (int)tag_get(0x77656170, *weapon);
  int magazine_count;
  int16_t i;

  if (rounds_array == NULL) {
    display_assert("rounds_array", "c:\\halo\\SOURCE\\items\\weapons.c", 0xc0a,
                   1);
    system_exit(-1);
  }

  magazine_count = *(int *)(tag_data + 0x4f0);
  for (i = 0; (int)i < magazine_count; i++) {
    int check_tag;
    char *mag_def;
    int16_t max_rounds;
    int16_t input_rounds;
    int16_t new_total;
    char *magazine;
    int16_t current_loaded;
    int16_t new_loaded;
    check_tag = (int)tag_get(0x77656170, *weapon);
    if ((int16_t)i < 0 || (int)i >= *(int *)(check_tag + 0x4f0)) {
      display_assert("magazine_index>=0 && "
                     "magazine_index<weapon_definition->weapon.magazines.count",
                     "c:\\halo\\SOURCE\\items\\weapons.c", 0x672, 1);
      system_exit(-1);
    }
    mag_def =
      (char *)tag_block_get_element((int *)(tag_data + 0x4f0), (int)i, 0x70);
    max_rounds = *(int16_t *)(mag_def + 8);
    input_rounds = rounds_array[i];
    new_total = (input_rounds < max_rounds) ? input_rounds : max_rounds;
    magazine = (char *)weapon + ((int)i * 3 + 0x96) * 4;
    current_loaded = *(int16_t *)(magazine + 8);
    *(int16_t *)(magazine + 6) = new_total;
    new_loaded =
      (current_loaded <= new_total) ? current_loaded : new_total;
    *(int16_t *)(magazine + 8) = new_loaded;
  }
}

/* Transfer ammunition from a source object into a weapon's magazines (0xfc290).
 * For each magazine that's below initial capacity, tries to transfer rounds
 * from either the same weapon type or matching equipment. Deletes the source if
 * fully depleted. Returns true if any ammo source was matched. */
bool weapon_handle_potential_inventory_item(int weapon_handle,
                                            int source_handle,
                                            uint16_t local_player_index,
                                            int16_t *rounds_out)
{
  int *weapon_data = (int *)object_get_and_verify_type(weapon_handle, 4);
  int tag_data = (int)tag_get(0x77656170, *weapon_data);
  int *source_data = (int *)object_get_and_verify_type(source_handle, 0x1c);
  int source_tag = *source_data;
  bool found = false;

  {
    int16_t i;
    for (i = 0; (int)i < *(int *)(tag_data + 0x4f0); i++) {
      int check_tag;
      int mag_offset;
      char *mag_def;
      int16_t *mag_rounds;
      int16_t transfer;
      check_tag = (int)tag_get(0x77656170, *weapon_data);
      if ((int16_t)i < 0 || (int)i >= *(int *)(check_tag + 0x4f0)) {
        display_assert("magazine_index>=0 && "
                       "magazine_index<weapon_definition->weapon.magazines.count",
                       "c:\\halo\\SOURCE\\items\\weapons.c", 0x672, 1);
        system_exit(-1);
      }
      mag_offset = ((int)i * 3 + 0x96) * 4;
      mag_def =
        (char *)tag_block_get_element((char *)tag_data + 0x4f0, (int)i, 0x70);
      mag_rounds = (int16_t *)((char *)weapon_data + mag_offset + 6);
      transfer = 0;
      if (*mag_rounds < *(int16_t *)(mag_def + 8)) {
        int16_t need;
        need = *(int16_t *)(mag_def + 8) - *mag_rounds;
        if (*weapon_data == source_tag) {
          int *src_weap;
          int src_tag2;
          int16_t *src_rounds;
          src_weap = (int *)object_get_and_verify_type(source_handle, 4);
          src_tag2 = (int)tag_get(0x77656170, *src_weap);
          if ((int16_t)i < 0 || (int)i >= *(int *)(src_tag2 + 0x4f0)) {
            display_assert(
              "magazine_index>=0 && "
              "magazine_index<weapon_definition->weapon.magazines.count",
              "c:\\halo\\SOURCE\\items\\weapons.c", 0x672, 1);
            system_exit(-1);
          }
          src_rounds = (int16_t *)((char *)src_weap + mag_offset + 6);
          transfer = need;
          if (*src_rounds <= need) {
            transfer = *src_rounds;
          }
          if (transfer > 0) {
            *src_rounds = *src_rounds - transfer;
            if (*(int *)(tag_data + 0x49c) != -1 &&
                (int16_t)local_player_index != -1) {
              sound_impulse_start(*(int *)(tag_data + 0x49c), 1.0f);
            }
            if (*src_rounds == 0) {
              object_delete(source_handle);
            }
          }
          found = true;
        } else {
          int *equip_block;
          int16_t j;
          equip_block = (int *)(mag_def + 0x64);
          for (j = 0; (int)j < *equip_block; j++) {
            int16_t *entry;
            entry =
              (int16_t *)tag_block_get_element(equip_block, (int)j, 0x1c);
            if (*(int *)(entry + 0xc) == source_tag) {
              transfer = need;
              if (*entry <= need) {
                transfer = *entry;
              }
              if (transfer > 0) {
                if ((int16_t)local_player_index != -1) {
                  FUN_000f67f0(*(int *)(entry + 0xc));
                }
                object_delete(source_handle);
                found = true;
                break;
              }
            }
          }
        }
        *mag_rounds = *mag_rounds + transfer;
        *rounds_out = transfer;
      }
    }
  }
  return found;
}

/* FUN_000fc990 (0xfc990) — XBE naked draft (batch 58). */
#if defined(__clang__)
static void *(*const bfc990_get)(int, int) = object_get_and_verify_type;
static void * (*const bfc990_cfb370)(void *weapon_obj, int16_t magazine_index) = FUN_000fb370;
static void *(*const bfc990_tag)(int, int) = tag_get;
static void *(*const bfc990_elem)(void *, int, int) = tag_block_get_element;
static int (*const bfc990_cfba20)(int weapon_handle, char param_2, int16_t state) = weapon_set_animation_state;
static int (*const bfc990_cfb6e0)(int trigger_effect, float scale, float param_3, int weapon_handle) = weapon_start_effect;
static void (*const bfc990_cde3b0)(int object_handle, int param_2) = first_person_weapon_message_from_weapon;
static int16_t (*const bfc990_cfb140)(int weapon_handle, int16_t param_2, int16_t param_3, int16_t param_4) = weapon_get_animation_frame;

__attribute__((naked, noinline))
void FUN_000fc990(int16_t magazine_index __attribute__((unused)), int weapon_handle __attribute__((unused)), int param_2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%ebx, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[cfb370]\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x77656170\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[tag]\n\t"
      "movswl %%bx, %%edx\n\t"
      "pushl $0x70\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "addl $0x4f0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movswl (%%edi), %%eax\n\t"
      "addl $0x1c, %%esp\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_000fc990_1\n\t"
      "subl $2, %%eax\n\t"
      "jne .LFUN_000fc990_5\n\t"
      ".LFUN_000fc990_1:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movb 0x211(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_000fc990_5\n\t"
      "movb 0x235(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_000fc990_5\n\t"
      "movb 0x1e8(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_000fc990_5\n\t"
      "cmpw $0, 0x6(%%edi)\n\t"
      "jle .LFUN_000fc990_4\n\t"
      "movw 0x8(%%edi), %%cx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "cmpw 0xa(%%edx), %%cx\n\t"
      "jge .LFUN_000fc990_4\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "addl $5, %%ebx\n\t"
      "pushl %%eax\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "call *%[cfba20]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x44(%%ecx), %%edx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[cfb6e0]\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw %%ax, 0x8(%%edi)\n\t"
      "setne %%al\n\t"
      "addl $9, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[cde3b0]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "addl $0x1c, %%esp\n\t"
      "cmpw $1, 0x4e2(%%ecx)\n\t"
      "jne .LFUN_000fc990_3\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000fc990_2\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movswl 0x8(%%edi), %%edx\n\t"
      "movswl 0xa(%%eax), %%esi\n\t"
      "subl %%edx, %%esi\n\t"
      "decl %%esi\n\t"
      "negl %%esi\n\t"
      "sbbl %%esi, %%esi\n\t"
      "andl $0xfffffffe, %%esi\n\t"
      "addl $2, %%esi\n\t"
      "jmp .LFUN_000fc990_3\n\t"
      ".LFUN_000fc990_2:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movswl 0x8(%%edi), %%ecx\n\t"
      "movswl 0xa(%%edx), %%esi\n\t"
      "subl %%ecx, %%esi\n\t"
      "decl %%esi\n\t"
      "negl %%esi\n\t"
      "sbbl %%esi, %%esi\n\t"
      "andl $0xfffffffe, %%esi\n\t"
      "incl %%esi\n\t"
      ".LFUN_000fc990_3:\n\t"
      "pushl %%esi\n\t"
      "pushl $7\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "movw $1, (%%edi)\n\t"
      "call *%[cfb140]\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      "movw %%ax, 0x2(%%edi)\n\t"
      "movw %%ax, 0x4(%%edi)\n\t"
      ".LFUN_000fc990_4:\n\t"
      "andl $0xfffffff7, 0x1dc(%%esi)\n\t"
      ".LFUN_000fc990_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(bfc990_get), [cfb370] "m"(bfc990_cfb370), [tag] "m"(bfc990_tag), [elem] "m"(bfc990_elem), [cfba20] "m"(bfc990_cfba20), [cfb6e0] "m"(bfc990_cfb6e0), [cde3b0] "m"(bfc990_cde3b0), [cfb140] "m"(bfc990_cfb140)
      : "memory");
}
#else
#error "FUN_000fc990: clang naked draft required"
#endif


/* FUN_000fcaf0 (0xfcaf0) — XBE naked draft (batch 63). */
#if defined(__clang__)
static void *(*const bfcaf0_get)(int, int) = object_get_and_verify_type;
static void * (*const bfcaf0_cfb370)(void *weapon_obj, int16_t magazine_index) = FUN_000fb370;
static void *(*const bfcaf0_tag)(int, int) = tag_get;
static void *(*const bfcaf0_elem)(void *, int, int) = tag_block_get_element;
static void (*const bfcaf0_cfc990)(int16_t magazine_index, int weapon_handle, int param_2) = FUN_000fc990;

__attribute__((naked, noinline))
void FUN_000fcaf0(int weapon_handle __attribute__((unused)), int magazine_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl %%ebx, %%edi\n\t"
      "call *%[cfb370]\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x77656170\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[tag]\n\t"
      "movswl 0xc(%%ebp), %%edx\n\t"
      "pushl $0x70\n\t"
      "pushl %%edx\n\t"
      "addl $0x4f0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movb (%%eax), %%cl\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb $1, %%cl\n\t"
      "je .LFUN_000fcaf0_1\n\t"
      "movw $0, 0x8(%%esi)\n\t"
      ".LFUN_000fcaf0_1:\n\t"
      "movw 0x6(%%esi), %%dx\n\t"
      "movw 0x18(%%eax), %%cx\n\t"
      "cmpw %%dx, %%cx\n\t"
      "movswl %%dx, %%edi\n\t"
      "jg .LFUN_000fcaf0_2\n\t"
      "movswl %%cx, %%edi\n\t"
      ".LFUN_000fcaf0_2:\n\t"
      "movw 0x8(%%esi), %%cx\n\t"
      "addw %%di, %%cx\n\t"
      "xorl %%edi, %%edi\n\t"
      "movw 0xa(%%eax), %%di\n\t"
      "cmpw %%di, %%cx\n\t"
      "jle .LFUN_000fcaf0_3\n\t"
      "movl %%edi, %%ecx\n\t"
      ".LFUN_000fcaf0_3:\n\t"
      "cmpb $0, 0x5aa892\n\t"
      "jne .LFUN_000fcaf0_4\n\t"
      "testb $2, 0x1a4(%%ebx)\n\t"
      "je .LFUN_000fcaf0_4\n\t"
      "subl %%ecx, %%edx\n\t"
      "addw 0x8(%%esi), %%dx\n\t"
      "movw %%dx, 0x6(%%esi)\n\t"
      ".LFUN_000fcaf0_4:\n\t"
      "cmpw $0, 0x6(%%esi)\n\t"
      "movw %%cx, 0x8(%%esi)\n\t"
      "movw $2, (%%esi)\n\t"
      "movw $0, 0x2(%%esi)\n\t"
      "jle .LFUN_000fcaf0_5\n\t"
      "cmpw 0xa(%%eax), %%cx\n\t"
      "jge .LFUN_000fcaf0_5\n\t"
      "testb $1, (%%eax)\n\t"
      "jne .LFUN_000fcaf0_5\n\t"
      "testb $0x26, 0x1e0(%%ebx)\n\t"
      "jne .LFUN_000fcaf0_5\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "call *%[cfc990]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000fcaf0_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(bfcaf0_get), [cfb370] "m"(bfcaf0_cfb370), [tag] "m"(bfcaf0_tag), [elem] "m"(bfcaf0_elem), [cfc990] "m"(bfcaf0_cfc990)
      : "memory");
}
#else
#error "FUN_000fcaf0: clang naked draft required"
#endif


/* 0xfcf20 — weapon_reset_state
 *
 * Resets all trigger and magazine states on a weapon. Iterates over
 * trigger entries and sets each trigger state byte to 8 and counter
 * to 0. Then iterates over magazine entries, checks for auto-reload
 * condition, and resets magazine state/counter fields.
 *
 * Confirmed: cdecl, 1 stack arg (weapon_handle).
 * Confirmed: CALL object_get_and_verify_type(weapon_handle, 4).
 * Confirmed: CALL tag_get(0x77656170, *obj) for weapon tag.
 * Confirmed: trigger loop: tag+0x4fc count, stride 0x24 (36 bytes)
 *   per trigger entry in weapon data starting at +0x210.
 * Confirmed: assert at weapons.c:0x667 for trigger_index bounds.
 * Confirmed: tag_block_get_element(tag+0x4fc, index, 0x114).
 * Confirmed: stores +0x211 = 8, +0x212 = 0 per trigger.
 * Confirmed: magazine loop: tag+0x4f0 count, stride 12 bytes per
 *   magazine entry starting at weapon_data + 0x258.
 * Confirmed: assert at weapons.c:0x672 for magazine_index bounds.
 * Confirmed: tag_block_get_element(tag+0x4f0, index, 0x70).
 * Confirmed: auto-reload check: magazine[0]==1 and frame*2 < count.
 * Confirmed: calls weapon_get_animation_frame(handle, 0, 7, -1).
 * Confirmed: calls FUN_000fcaf0(handle, magazine_index).
 * Confirmed: resets magazine[0] and magazine[1] to 0.
 */
void weapon_reset_state(int weapon_handle)
{
  uint32_t *weapon_data =
    (uint32_t *)object_get_and_verify_type(weapon_handle, 4);
  int weap_tag = (int)tag_get(0x77656170, weapon_data[0]);
  int magazine_int;
  int mag_tag_ptr;

  /* Reset trigger states */
  int16_t trigger_index = 0;
  if (0 < *(int *)(weap_tag + 0x4fc)) {
    int trigger_count_index = 0;
    do {
      int weap_tag2 = (int)tag_get(0x77656170, weapon_data[0]);
      char *trigger_entry;
      if (trigger_index < 0 ||
          trigger_count_index >= *(int *)(weap_tag2 + 0x4fc)) {
        display_assert("trigger_index>=0 && trigger_index<weapon_definition->"
                       "weapon.triggers.count",
                       "c:\\halo\\SOURCE\\items\\weapons.c", 0x667, 1);
        system_exit(-1);
      }

      /* Compute trigger entry pointer:
       * base + trigger_index * 9 * 4 + 0x210 */
      trigger_entry =
        (char *)weapon_data + trigger_count_index * 36 + 0x210;

      tag_block_get_element((void *)(weap_tag + 0x4fc), trigger_count_index,
                            0x114);

      trigger_index = trigger_index + 1;
      trigger_count_index = (int)trigger_index;

      *(char *)(trigger_entry + 1) = 8;
      *(int16_t *)(trigger_entry + 2) = 0;
    } while (trigger_count_index < *(int *)(weap_tag + 0x4fc));
  }

  /* Reset magazine states */
  magazine_int = 0;
  mag_tag_ptr = weap_tag + 0x4f0;
  if (0 < *(int *)(weap_tag + 0x4f0)) {
    int mag_count_index = 0;
    do {
      int weap_tag3 = (int)tag_get(0x77656170, weapon_data[0]);
      int16_t *mag_entry;
      if ((int16_t)magazine_int < 0 ||
          mag_count_index >= *(int *)(weap_tag3 + 0x4f0)) {
        display_assert("magazine_index>=0 && magazine_index<weapon_definition->"
                       "weapon.magazines.count",
                       "c:\\halo\\SOURCE\\items\\weapons.c", 0x672, 1);
        system_exit(-1);
      }

      /* Compute magazine entry pointer:
       * base + (magazine_index * 3 + 0x96) * 4 */
      mag_entry =
        (int16_t *)((char *)weapon_data + (mag_count_index * 3 + 0x96) * 4);

      tag_block_get_element((void *)mag_tag_ptr, mag_count_index, 0x70);

      if (mag_entry[0] == 1) {
        int16_t frame = weapon_get_animation_frame(weapon_handle, 0, 7, -1);
        if (mag_entry[1] * 2 < (int)frame) {
          FUN_000fcaf0(weapon_handle, magazine_int);
        }
      }

      magazine_int = magazine_int + 1;
      mag_count_index = (int)(int16_t)magazine_int;
      mag_entry[0] = 0;
      mag_entry[1] = 0;
    } while (mag_count_index < *(int *)(mag_tag_ptr));
  }
}

/* weapon_set_current_amount (0xfd180)
 *
 * Sets weapon ammo level based on a fraction. For battery-based weapons
 * (no magazines or has triggers with charging threshold), stores the charge
 * level at weapon+0x1f0. For magazine-based weapons, sets the loaded rounds
 * in the first magazine and adjusts the total accordingly.
 */
void weapon_set_current_amount(int weapon_handle, float ammo_fraction)
{
  int *weapon = (int *)object_get_and_verify_type(weapon_handle, 4);
  int tag_data = (int)tag_get(0x77656170, *weapon);

  bool is_battery = false;
  int magazine_count = *(int *)(tag_data + 0x4f0);

  if (magazine_count == 0) {
    is_battery = true;
  } else {
    int16_t i;
    int trigger_count = *(int *)(tag_data + 0x4fc);
    for (i = 0; (int)i < trigger_count; i++) {
      char *trigger =
        (char *)tag_block_get_element((int *)(tag_data + 0x4fc), (int)i, 0x114);
      if (*(float *)(trigger + 0xbc) > 0.0f) {
        is_battery = true;
        break;
      }
    }
  }

  if (ammo_fraction < 0.0f) {
    ammo_fraction = 0.0f;
  } else if (ammo_fraction > 1.0f) {
    ammo_fraction = 1.0f;
  }

  if (is_battery) {
    *(float *)((char *)weapon + 0x1f0) = 1.0f - ammo_fraction;
    return;
  }

  if (magazine_count > 0) {
    char *mag_def =
      (char *)tag_block_get_element((int *)(tag_data + 0x4f0), 0, 0x70);
    int check_tag = (int)tag_get(0x77656170, *weapon);
    int16_t max_rounds;
    int16_t new_loaded;
    int16_t current_loaded;
    if (*(int *)(check_tag + 0x4f0) < 1) {
      display_assert("magazine_index>=0 && "
                     "magazine_index<weapon_definition->weapon.magazines.count",
                     "c:\\halo\\SOURCE\\items\\weapons.c", 0x672, 1);
      system_exit(-1);
    }

    max_rounds = *(int16_t *)(mag_def + 0xa);
    new_loaded = (int16_t)(int)((float)max_rounds * ammo_fraction);
    current_loaded = *(int16_t *)((char *)weapon + 0x260);
    *(int16_t *)((char *)weapon + 0x260) = new_loaded;
    *(int16_t *)((char *)weapon + 0x25e) += (new_loaded - current_loaded);
  }
}

/* weapon_activate — no binary address assigned.
 * Initializes a weapon after it becomes the active weapon for a unit.
 * Resets trigger/magazine state, sets the ready animation (state 9),
 * fires the initial effect from the weapon triggers tag block, and
 * stores the ready animation frame count into the weapon data. */
void weapon_activate(int weapon_handle)
{
  uint32_t *weapon_data =
    (uint32_t *)object_get_and_verify_type(weapon_handle, 4);
  int tag_data = (int)tag_get(0x77656170, weapon_data[0]);
  int16_t frame;

  weapon_reset_state(weapon_handle);
  weapon_set_animation_state(weapon_handle, 1, 9);
  first_person_weapon_message_from_weapon(weapon_handle, 0xc);
  weapon_start_effect(*(int *)(tag_data + 0x348), 0, 0, weapon_handle);

  frame = weapon_get_animation_frame(weapon_handle, 0, 10, -1);
  *(int16_t *)((int)weapon_data + 0x1ea) = frame;
}

/* weapon_try_place — no binary address assigned.
 * Attempts to place (holster/put-away) the current weapon. If flag is
 * zero and the weapon has active triggers or animations, the placement
 * is rejected. On success, sets the put-away animation (state 10),
 * resets trigger/magazine state, disposes any attached effect, and
 * starts the put-away effect sequence. */
bool weapon_try_place(int weapon_handle, int flag)
{
  uint32_t *weapon_data =
    (uint32_t *)object_get_and_verify_type(weapon_handle, 4);
  tag_get(0x77656170, weapon_data[0]);

  if ((char)flag == 0 && weapon_has_activity(weapon_handle))
    return false;

  if (!weapon_set_animation_state(weapon_handle, flag, 10))
    return false;

  *(int16_t *)((int)weapon_data + 0x1e0) = 0;
  weapon_reset_state(weapon_handle);

  if (*(int *)((int)weapon_data + 0x274) != -1) {
    effect_delete(*(int *)((int)weapon_data + 0x274));
    *(int *)((int)weapon_data + 0x274) = -1;
  }

  first_person_weapon_message_from_weapon(weapon_handle, 0xb);
  return true;
}

/* weapon_aim (0xfd400) — weapon_try_and_fire_projectile
 *
 * Attempts to fire a projectile for a given weapon trigger. Validates the
 * weapon object (type 4), resolves the 'weap' tag, then validates the
 * trigger_index is in range [0, triggers.count). If in range, fetches the
 * trigger block element (0x114 bytes each) at [weap_tag+0x4fc], reads the
 * 'proj' tag reference from [trigger_elem+0xa0], and resolves it via
 * tag_get('proj',...). Passes the resolved projectile tag along with the
 * remaining parameters to projectile_aim (projectile fire dispatcher), then
 * validates param_6 as a valid 3D unit normal using valid_real_normal3d. If
 * the vector is invalid, formats an assert message via csprintf and calls
 * display_assert + system_exit. Returns true (1) on success, false (0) if
 * trigger_index is out of range.
 *
 * Line number evidence: assert at line 0x515 (1301) in weapons.c.
 *
 * Confirmed: object_get_and_verify_type(weapon_handle, 4) at 0xfd40c.
 * Confirmed: tag_get(0x77656170, weapon_data[0]) at 0xfd41b; ADD ESP,0x10
 *   cleans both preceding calls (object_get + tag_get = 4 args).
 * Confirmed: TEST SI,SI / JL at 0xfd42a–0xfd42d guards trigger_index < 0.
 * Confirmed: MOV EDX,[EBX+0x4fc] / ADD EBX,0x4fc at 0xfd433–fd439 =
 *   trigger block count and pointer.
 * Confirmed: MOVSX ECX,SI / CMP ECX,EDX / JGE at 0xfd43f–0xfd447 guards
 *   trigger_index >= triggers.count.
 * Confirmed: CALL 0xfb320 at 0xfd44d is a debug assertion using caller ESI/EDI;
 *   not representable as a plain C call — elided (bounds already checked
 * above). Confirmed: tag_block_get_element(EBX, ECX, 0x114) at 0xfd45c where
 * EBX= &triggers_block ([weap_tag+0x4fc] after ADD EBX,0x4fc). Confirmed: MOV
 * EAX,[EAX+0xa0] at 0xfd475 reads proj tag reference from trigger element.
 * Confirmed: tag_get(0x70726f6a, proj_ref, ...) at 0xfd496 with 14 pushes;
 *   ADD ESP,0x8 cleans only tag_get's own 2 args.
 * Confirmed: projectile_aim called with proj_tag + 12 stale stack args at
 * 0xfd49f; receives proj_tag as arg1, then param_3..param_9 interleaved with
 * 0-padding. Confirmed: valid_real_normal3d(param_6) at 0xfd4a5 (PUSH ESI where
 * ESI=[EBP+0x1c]). Confirmed: csprintf(&DAT_005ab100, ...) assert-format at
 * 0xfd4e2; float args loaded FLD+FSTP double via MSVC push-then-fstp pattern.
 * Confirmed: CALL display_assert at 0xfd4eb; CALL system_exit at 0xfd4f2.
 * Confirmed: return 1 at 0xfd4fa; return 0 (XOR AL,AL) at 0xfd428 on early
 * exit.
 */
bool weapon_aim(int weapon_handle, int16_t trigger_index, void *param_3,
                void *param_4, int param_5, float *param_6, int param_7,
                void *param_8, void *param_9)
{
  int *weapon_data = (int *)object_get_and_verify_type(weapon_handle, 4);
  char *weap_tag = (char *)tag_get(0x77656170, weapon_data[0]);
  int trigger_count;
  int trig_idx;
  char *trigger_elem;
  int proj_ref;
  void *proj_tag;

  if (trigger_index < 0)
    return false;

  trigger_count = *(int *)(weap_tag + 0x4fc);
  trig_idx = (int)trigger_index;
  if (trig_idx >= trigger_count)
    return false;

  /* FUN_000fb320 assertion (trigger bounds) elided: reads caller ESI/EDI,
   * not representable as a plain C call. Bounds already checked above. */

  trigger_elem =
    (char *)tag_block_get_element((void *)(weap_tag + 0x4fc), trig_idx, 0x114);
  proj_ref = *(int *)(trigger_elem + 0xa0);

  /* tag_get + projectile_aim share a single stack cleanup.
   * Disassembly-verified push sequence at 0xfd46d–0xfd495 (14 pushes, right-to-left):
   *   [P1] ECX=param_9, [P2] EDX=param_8, [P3] ECX=param_7, [P4] 0,
   *   [P5] ESI=param_6, [P6] EDX=param_5, [P7-P10] 0,0,0,0,
   *   [P11] ECX=param_4 (ECX reloaded via MOV ECX,[EBP+0x14] at 0xfd47c),
   *   [P12] EDX=param_3, [P13] EAX=proj_ref, [P14] 'proj'
   * tag_get (at 0xfd496) uses P14+'proj' and P13=proj_ref; ADD ESP,8 cleans them.
   * PUSH EAX (proj_tag) at 0xfd49e, then CALL projectile_aim at 0xfd49f:
   *   arg2=P12=param_3(origin), arg3=P11=param_4(target), arg8=P6=param_5,
   *   arg9=P5=param_6(aim_vector), arg11=P3=param_7, arg12=P2=param_8,
   *   arg13=P1=param_9. */
  proj_tag = tag_get(0x70726f6a, proj_ref);
  ((void (*)(void *, void *, void *, int, int, int, int, int, float *, int, int,
             void *, void *))0xf84d0)(proj_tag, param_3, param_4, 0, 0, 0, 0,
                                      param_5, param_6, 0, param_7, param_8,
                                      param_9);

  if (!((bool (*)(float *))0x21fb0)(param_6)) {
    display_assert(csprintf((char *)0x5ab100,
                            "%s: assert_valid_real_normal3d(%f, %f, %f)",
                            "result_aim_vector", (double)param_6[0],
                            (double)param_6[1], (double)param_6[2]),
                   "c:\\halo\\SOURCE\\items\\weapons.c", 0x515, 1);
    system_exit(-1);
  }

  return true;
}
/* --- weapons.obj unset drafts (batch 2026-07-25) --- */

float FUN_001d9e70(float base, float exponent);
int actor_aim_projectile(int unit_handle, float *direction_in, float *direction_out,
                         int *out_extra);

static char *weapon_get_trigger_entry(void *weapon_obj, int16_t trigger_index)
{
  int *tag_data = (int *)tag_get(0x77656170, *(int *)weapon_obj);

  if (trigger_index < 0 || (int)trigger_index >= *(int *)((char *)tag_data + 0x4fc)) {
    display_assert("trigger_index>=0 && trigger_index<weapon_definition->"
                   "weapon.triggers.count",
                   "c:\\halo\\SOURCE\\items\\weapons.c", 0x667, 1);
    system_exit(-1);
  }

  return (char *)weapon_obj + (int)trigger_index * 36 + 0x210;
}

/* weapon_place (0xfad60) — readable C lift. */
int weapon_place(int weapon_handle, void *placement)
{
  char *weapon;
  char *tag;
  char *mag_block;
  char *mag_elem;
  char *place = (char *)placement;
  int16_t a, b;

  weapon = (char *)object_get_and_verify_type(weapon_handle, 4);
  tag = (char *)tag_get(0x77656170, *(int *)weapon);
  mag_block = tag + 0x4f0;
  if (*(int *)mag_block > 0) {
    mag_elem = (char *)tag_block_get_element(mag_block, 0, 0x70);
    a = *(int16_t *)(place + 0x48);
    b = *(int16_t *)(mag_elem + 8);
    if (a > b)
      a = b;
    *(int16_t *)(weapon + 0x25e) = a;
    a = *(int16_t *)(mag_elem + 0xa);
    b = *(int16_t *)(place + 0x4a);
    if (b > a)
      ; /* keep a */
    else
      a = b;
    *(int16_t *)(weapon + 0x260) = a;
  }
  if (place[0x4c] & 1)
    *(int *)(weapon + 4) |= 0x20;
  else
    *(int *)(weapon + 4) &= ~0x20;
  weapon[6] |= 2;
  if (!(place[0x4c] & 4))
    *(int *)(weapon + 0x1a4) |= 0x20;
  else
    *(int *)(weapon + 0x1a4) &= ~0x20;
  if (!(place[0x4c] & 1))
    *(float *)(weapon + 0x14) += *(float *)0x2533e8;
  return weapon_handle;
}

/* weapon_can_be_fired (0xfaf50) — readable C lift. */
char weapon_can_be_fired(int weapon_handle)
{
  char *obj;
  char *tag;
  void *block;
  void *elem;

  obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  tag = (char *)tag_get(0x77656170, *(int *)obj);
  if (!(*(float *)(obj + 0x1f0) < *(float *)0x2533c8))
    return 0;
  if (!game_engine_running())
    return 1;
  block = tag + 0x4f0;
  if (*(int *)block <= 0)
    return 1;
  elem = tag_block_get_element(block, 0, 0x70);
  if (*(short *)((char *)elem + 0xa) <= 0)
    return 1;
  if (*(short *)(obj + 0x260) != 0)
    return 1;
  if (*(short *)(obj + 0x25e) != 0)
    return 1;
  return 0;
}

/* 0xfafe0 — true when weapon age/heat is still below 1.0. */
char weapon_useful(int weapon_handle)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  return (*(float *)(weapon_obj + 0x1f0) < *(float *)0x2533c8) ? 1 : 0;
}


/* 0xfb010 — Movement penalty from weapon tag, gated by trigger mode. */
float weapon_compute_movement_penalty(int weapon_handle, char aiming,
                                      char param_3)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  char *tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);
  float result;
  int mode;

  if (aiming)
    result = *(float *)(tag_data + 0x400);
  else
    result = *(float *)(tag_data + 0x404);

  mode = *(int16_t *)(tag_data + 0x3fc) - 1;
  if (mode == 0)
    goto gate;
  if (mode != 1)
    return result;
  if (*(int16_t *)(weapon_obj + 0x258) == 1 ||
      *(int16_t *)(weapon_obj + 0x264) == 1) {
  gate:
    if (param_3 == 0)
      return *(float *)0x2533c0;
  }
  return result;
}


/* 0xfb320 */
char *FUN_000fb320(void *weapon_obj, int16_t trigger_index)
{
  return weapon_get_trigger_entry(weapon_obj, trigger_index);
}

/* FUN_000fb510 (0xfb510) — readable C lift. */
float FUN_000fb510(int weapon_handle, int16_t trigger_index)
{
  char *weapon_obj;
  char *trigger_entry;
  char *trig_def;
  int state;

  weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  trigger_entry = FUN_000fb320(weapon_obj, trigger_index);
  trig_def = (char *)tag_block_get_element(
      (char *)tag_get(0x77656170, *(int *)weapon_obj) + 0x4fc,
      (int)trigger_index, 0x114);

  state = (int)(signed char)trigger_entry[1] - 2;
  if (state == 0) {
    return *(float *)0x2533c8 -
           (float)*(int16_t *)(trigger_entry + 2) * *(float *)0x2546a4 /
               *(float *)(trig_def + 0x48);
  }
  if (state == 1)
    return *(float *)0x2533c8;
  return *(float *)0x2533c0;
}

/* FUN_000fb5a0 (0xfb5a0) — readable C lift. */
char FUN_000fb5a0(int weapon_handle, int16_t trigger_index)
{
  char *weapon_obj;
  char *trigger_entry;
  char *tag_data;
  char *trig_def;
  uint32_t trig_flags;
  float threshold;
  float charge;
  char result;

  weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  trigger_entry = FUN_000fb320(weapon_obj, trigger_index);
  tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);
  trig_def = (char *)tag_block_get_element((void *)(tag_data + 0x4fc),
                                           (int)trigger_index, 0x114);
  trig_flags = *(uint32_t *)trig_def;
  result = 0;

  if ((trig_flags & 0x200) != 0)
    charge = *(float *)(weapon_obj + 0x1e4);
  else
    charge = *(float *)(trigger_entry + 0x10);

  threshold = (*(float *)(trig_def + 8) - *(float *)(trig_def + 4)) * charge +
              *(float *)(trig_def + 4);
  if (!(threshold > *(float *)0x253f44))
    threshold = *(float *)0x2533c0;
  else
    threshold = *(float *)0x253394 / threshold;

  if (*(float *)(tag_data + 0x444) > *(float *)0x2533c0)
    threshold = (*(float *)(weapon_obj + 0x1f0) * *(float *)(tag_data + 0x444) +
                 *(float *)0x2533c8) *
                threshold;

  if ((float)(signed char)trigger_entry[0] + *(float *)0x2533c8 >= threshold)
    result = 1;

  if ((trig_flags & 8) != 0 && (*(uint8_t *)(weapon_obj + 0x1a4) & 2) != 0 &&
      (trigger_entry[4] & 1) == 0)
    return 0;

  return result;
}

/* FUN_000fb690 (0xfb690) — readable C lift: clear magazine state. */
void FUN_000fb690(int weapon_handle /*@<eax>*/, int16_t magazine_index /*@<cx>*/)
{
  char *weapon;
  void *mag;
  void *tag;

  weapon = (char *)object_get_and_verify_type(weapon_handle, 4);
  mag = FUN_000fb370(weapon, magazine_index);
  tag = tag_get(0x77656170, *(int *)weapon);
  (void)tag_block_get_element((char *)tag + 0x4f0, (int)magazine_index, 0x70);
  *(int16_t *)mag = 0;
  *(int16_t *)((char *)mag + 2) = 0;
}

/* FUN_000fb7d0 (0xfb7d0) — readable C lift. */
int FUN_000fb7d0(int effect_tag, int weapon_handle)
{
  char *weapon;
  int owner;
  int parent;

  if (effect_tag == -1)
    return -1;
  weapon = (char *)object_get_and_verify_type(weapon_handle, 4);
  owner = weapon_handle;
  if ((weapon[4] & 1) != 0) {
    parent = *(int *)(weapon + 0xcc);
    if (parent != -1)
      owner = parent;
  }
  weapon = (char *)object_get_and_verify_type(weapon_handle, 4);
  parent = *(int *)(weapon + 0xcc);
  if (parent != -1)
    (void)object_try_and_get_and_verify_type(parent, 3);
  if (owner == -1)
    return -1;
  return FUN_0009eb40(effect_tag, owner, -1, -1, -1);
}

/* weapon_trigger_release_charge (0xfb880) — readable C lift. */
void weapon_trigger_release_charge(int weapon_handle, int16_t trigger_index,
                                   int16_t state, int16_t charge_counter)
{
  extern char DAT_0028ae40[];
  extern char DAT_0028ad48[];
  extern char DAT_0028ae08[];
  char *weapon_obj;
  char *slot;

  weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  if (trigger_index < 0 || trigger_index >= 2) {
    display_assert(DAT_0028ae40, DAT_0028ad48, 0xa11, 1);
    system_exit(-1);
  }
  if (state < 0 || state >= 9) {
    display_assert(DAT_0028ae08, DAT_0028ad48, 0xa12, 1);
    system_exit(-1);
  }
  slot = weapon_obj + (int)trigger_index * 36;
  slot[0x211] = (char)state;
  *(int16_t *)(slot + 0x212) = charge_counter;
}

/* FUN_000fb910 (0xfb910) — readable C lift. */
void FUN_000fb910(int weapon_handle, int16_t trigger_index, char flag)
{
  char *weapon_obj;
  char *weap_tag;
  char *trig_def;
  char *entry;
  int has_bit;

  weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  weap_tag = (char *)tag_get(0x77656170, *(int *)weapon_obj);
  entry = FUN_000fb320(weapon_obj, trigger_index);
  trig_def = (char *)tag_block_get_element((void *)(weap_tag + 0x4fc),
                                           (int)trigger_index, 0x114);
  if (!(*(float *)(trig_def + 0xa4) > *(float *)0x2533c0))
    return;
  has_bit = (*(unsigned *)trig_def & 0x80) != 0;
  if (has_bit == (flag != 0))
    *(float *)(entry + 0x14) = 1.0f;
}

/* FUN_000fb990 (0xfb990) — readable C lift. */
void FUN_000fb990(int weapon_handle /*@<edi>*/)
{
  char *obj;
  int kind;

  obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  tag_get(0x77656170, *(int *)obj);
  kind = (int)(signed char)obj[0x1e8];
  if (kind == 3) {
    FUN_000fb910(weapon_handle, 0, 1);
    return;
  }
  if (kind == 4)
    FUN_000fb910(weapon_handle, 1, 1);
}

/* FUN_000fba00 (0xfba00) — readable C lift. */
char FUN_000fba00(short value, short threshold)
{
  int t = (int)threshold;
  if (t == 0) return 1;
  if (t <= 0 || t > 2) return 0;
  return value >= threshold;
}

/* FUN_000fbcf0 (0xfbcf0) — readable C lift. */
float FUN_000fbcf0(float base, float exponent)
{
  return FUN_001d9e70(base, exponent);
}
/* weapon_new (0xfbd10) — readable C lift. */
char weapon_new(int weapon_handle)
{
  extern char DAT_0028adb8[];
  extern char DAT_0028ad48[];
  extern char DAT_0028ad68[];
  char *weapon_obj;
  char *tag_data;
  int16_t magazine_index;
  int16_t trigger_index;

  weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);
  weapon_obj[0x1e8] = 0;
  *(int *)(weapon_obj + 0x274) = -1;

  for (magazine_index = 0; (int)magazine_index < *(int *)(tag_data + 0x4f0);
       magazine_index++) {
    char *mag_def;
    char *mag_entry;
    int16_t initial_total;
    int16_t max_loaded;
    int16_t loaded;

    (void)tag_get(0x77656170, *(int *)weapon_obj);
    if ((int16_t)magazine_index < 0 ||
        (int)magazine_index >= *(int *)(tag_data + 0x4f0)) {
      display_assert(DAT_0028adb8, DAT_0028ad48, 0x672, 1);
      system_exit(-1);
    }
    mag_entry = (char *)weapon_obj + ((int)magazine_index * 3 + 0x96) * 4;
    mag_def = (char *)tag_block_get_element((void *)(tag_data + 0x4f0),
                                            (int)magazine_index, 0x70);
    initial_total = *(int16_t *)(mag_def + 6);
    max_loaded = *(int16_t *)(mag_def + 0xa);
    loaded = (initial_total <= max_loaded) ? initial_total : max_loaded;
    *(int16_t *)(mag_entry + 8) = loaded;
    *(int16_t *)(mag_entry + 6) = (int16_t)(initial_total - loaded);
  }

  for (trigger_index = 0; (int)trigger_index < *(int *)(tag_data + 0x4fc);
       trigger_index++) {
    char *trigger_entry;

    (void)tag_get(0x77656170, *(int *)weapon_obj);
    if ((int16_t)trigger_index < 0 ||
        (int)trigger_index >= *(int *)(tag_data + 0x4fc)) {
      display_assert(DAT_0028ad68, DAT_0028ad48, 0x667, 1);
      system_exit(-1);
    }
    trigger_entry = (char *)weapon_obj + (int)trigger_index * 36 + 0x210;
    (void)tag_block_get_element((void *)(tag_data + 0x4fc), (int)trigger_index,
                                0x114);
    *(int *)(trigger_entry + 0x20) = -1;
    trigger_entry[0] = (char)0x7f;
  }

  return 1;
}


/* 0xfbea0 — assert non-deletable network weapons are not deleted in MP. */
#if defined(__i386__) && defined(__GNUC__)
__attribute__((noinline))
#endif
/* weapon_delete (0xfbea0) — readable C lift. */
void weapon_delete(int weapon_handle)
{
  void *obj;
  void *def;
  if (!game_engine_running())
    return;
  obj = object_get_and_verify_type(weapon_handle, 4);
  def = tag_get(0x77656170, *(int *)obj);
  if (((*(unsigned int *)((char *)def + 0x308)) >> 3) & 1) {
    display_assert((const char *)0x28ae98, (const char *)0x28ad48, 0xea, 1);
    system_exit(-1);
  }
}
/* Jump-table cases at 0xfc244 — superseded by naked weapon_export_function_values. */
#if 0
static float weapon_export_eval_function(int weapon_handle, char *weapon_obj,
                                         char *tag_data, int16_t function_id)
{
  float value = 0.0f;
  int16_t trigger_index;
  int16_t magazine_index;

  switch (function_id) {
  case 1: /* heat */
    value = *(float *)(weapon_obj + 0x1ec);
    break;
  case 2:
  case 3: /* magazine rounds fraction */
    magazine_index = (int16_t)(function_id - 2);
    if ((int)magazine_index < *(int *)(tag_data + 0x4f0)) {
      char *mag_def = (char *)tag_block_get_element(
          (void *)(tag_data + 0x4f0), (int)magazine_index, 0x70);
      int16_t capacity = *(int16_t *)(mag_def + 0xa);
      int16_t loaded =
          *(int16_t *)(weapon_obj + (int)magazine_index * 12 + 0x260);
      if (capacity != 0)
        value = (float)loaded / (float)capacity;
    }
    break;
  case 4:
  case 5: /* trigger primary float at entry+0x10 */
    trigger_index = (int16_t)(function_id - 4);
    if ((int)trigger_index < *(int *)(tag_data + 0x4fc))
      value = *(float *)(weapon_get_trigger_entry(weapon_obj, trigger_index) +
                         0x10);
    break;
  case 6: /* constant one */
    value = 1.0f;
    break;
  case 7:
  case 8: /* trigger secondary float at entry+0x14 */
    trigger_index = (int16_t)(function_id - 7);
    if ((int)trigger_index < *(int *)(tag_data + 0x4fc))
      value = *(float *)(weapon_get_trigger_entry(weapon_obj, trigger_index) +
                         0x14);
    break;
  case 9: /* illuminated overheat fraction */
    if ((*(uint8_t *)(weapon_obj + 0x1dc) & 1) != 0 &&
        *(float *)(tag_data + 0x34c) != 1.0f)
      value = (*(float *)(weapon_obj + 0x1ec) - *(float *)(tag_data + 0x34c)) /
              (1.0f - *(float *)(tag_data + 0x34c));
    break;
  case 10:
  case 11:
    trigger_index = (int16_t)(function_id - 10);
    if ((int)trigger_index < *(int *)(tag_data + 0x4fc))
      value = FUN_000fb510(weapon_handle, trigger_index);
    break;
  case 12: { /* aggregated trigger age / illumination */
    int i;
    value = 0.0f;
    for (i = 0; i < *(int *)(tag_data + 0x4fc); i++) {
      char *trig_def = (char *)tag_block_get_element(
          (void *)(tag_data + 0x4fc), i, 0x114);
      char *trigger_entry = FUN_000fb320(weapon_obj, (int16_t)i);
      float candidate;

      if (*(float *)(trig_def + 0x48) > 0.0f) {
        candidate = FUN_000fb510(weapon_handle, (int16_t)i) *
                    *(float *)(trig_def + 0x54);
        if (!(value > candidate))
          value = candidate;
      }
      if (trigger_entry[1] == 3) {
        candidate = (1.0f - *(float *)(trig_def + 0x54)) *
                        *(float *)(weapon_obj + 0x1f4) +
                    *(float *)(trig_def + 0x54);
        if (!(value > candidate))
          value = candidate;
      }
      if (!(value > *(float *)(trigger_entry + 0x18)))
        value = *(float *)(trigger_entry + 0x18);
      *(float *)(trigger_entry + 0x18) = value;
    }
    {
      float illuminated =
          *(float *)(tag_data + 0x360) * *(float *)(weapon_obj + 0x1ec);
      if (!(value > illuminated))
        value = illuminated;
    }
    break;
  }
  case 13:
    value = *(float *)(weapon_obj + 0x1f0);
    break;
  case 14:
    value = *(float *)(weapon_obj + 0x1f8);
    break;
  case 15:
  case 16:
    trigger_index = (int16_t)(function_id - 15);
    if ((int)trigger_index < *(int *)(tag_data + 0x4fc)) {
      value = *(float *)(weapon_get_trigger_entry(weapon_obj, trigger_index) +
                         0x10);
      /* XBE: zero when age > 1 tick. */
      if (game_time_get() - *(int *)(weapon_obj + 0x278) > 1)
        value = 0.0f;
    }
    break;
  default:
    break;
  }

  return value;
}
#endif

/* weapon_export_function_values (0xfbf00) — export up to 4 weapon function values onto the attachment root. */
#if defined(__clang__)
static void *(*const wefv_get)(int, int) = object_get_and_verify_type;
static void *(*const wefv_tag)(int, int) = tag_get;
static void *(*const wefv_elem)(void *, int, int) = tag_block_get_element;
static char *(*const wefv_fb320)(void *, short) = FUN_000fb320;
static float (*const wefv_fb510)(int, short) = FUN_000fb510;
static int (*const wefv_gtime)(void) = game_time_get;

__attribute__((naked, noinline))
void weapon_export_function_values(int weapon_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x77656170\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movb 0x4(%%edi), %%cl\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $1, %%cl\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "movl %%edi, %%eax\n\t"
      "je .Lweapon_export_function_values_2\n\t"
      "jmp .Lweapon_export_function_values_1\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lweapon_export_function_values_1:\n\t"
      "movl 0xcc(%%eax), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lweapon_export_function_values_2\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "movb 0x4(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $1, %%cl\n\t"
      "jne .Lweapon_export_function_values_1\n\t"
      ".Lweapon_export_function_values_2:\n\t"
      "addl $0xd4, %%eax\n\t"
      "leal 0x330(%%ebx), %%edx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl $4, -0x18(%%ebp)\n\t"
      ".Lweapon_export_function_values_3:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movw (%%eax), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Lweapon_export_function_values_24\n\t"
      "movswl %%ax, %%ecx\n\t"
      "decl %%ecx\n\t"
      "cmpl $0xf, %%ecx\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "ja .Lweapon_export_function_values_23\n\t"
      "jmp *.Lweapon_export_function_values_jt(,%%ecx,4)\n\t"
      ".Lweapon_export_function_values_4:\n\t"
      "movl $0x3f800000, -0x4(%%ebp)\n\t"
      "jmp .Lweapon_export_function_values_23\n\t"
      ".Lweapon_export_function_values_5:\n\t"
      "movl 0x1ec(%%edi), %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jmp .Lweapon_export_function_values_23\n\t"
      ".Lweapon_export_function_values_6:\n\t"
      "testb $1, 0x1dc(%%edi)\n\t"
      "je .Lweapon_export_function_values_23\n\t"
      "cmpl $0x3f800000, 0x34c(%%ebx)\n\t"
      "je .Lweapon_export_function_values_23\n\t"
      "flds 0x1ec(%%edi)\n\t"
      "fsubs 0x34c(%%ebx)\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x34c(%%ebx)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jmp .Lweapon_export_function_values_23\n\t"
      ".Lweapon_export_function_values_7:\n\t"
      "movl 0x4fc(%%ebx), %%eax\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .Lweapon_export_function_values_14\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lweapon_export_function_values_8\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lweapon_export_function_values_8:\n\t"
      "pushl $0x114\n\t"
      "pushl %%eax\n\t"
      "leal 0x4fc(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[fb320]\n\t"
      "flds 0x48(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "movl %%eax, %%edi\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lweapon_export_function_values_10\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[fb510]\n\t"
      "fmuls 0x54(%%ebx)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lweapon_export_function_values_9\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jmp .Lweapon_export_function_values_10\n\t"
      ".Lweapon_export_function_values_9:\n\t"
      "fstp %%st(0)\n\t"
      ".Lweapon_export_function_values_10:\n\t"
      "cmpb $3, 0x1(%%edi)\n\t"
      "jne .Lweapon_export_function_values_12\n\t"
      "flds 0x2533c8\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "fsubs 0x54(%%ebx)\n\t"
      "fmuls 0x1f4(%%edx)\n\t"
      "fadds 0x54(%%ebx)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lweapon_export_function_values_11\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jmp .Lweapon_export_function_values_12\n\t"
      ".Lweapon_export_function_values_11:\n\t"
      "fstp %%st(0)\n\t"
      ".Lweapon_export_function_values_12:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x18(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lweapon_export_function_values_13\n\t"
      "movl 0x18(%%edi), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".Lweapon_export_function_values_13:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "movl %%ecx, 0x18(%%edi)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl 0x4fc(%%ecx), %%edx\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "incl %%esi\n\t"
      "addl $0x4fc, %%ecx\n\t"
      "movswl %%si, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .Lweapon_export_function_values_8\n\t"
      ".Lweapon_export_function_values_14:\n\t"
      "flds 0x360(%%ebx)\n\t"
      "fmuls 0x1ec(%%edi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lweapon_export_function_values_22\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jmp .Lweapon_export_function_values_23\n\t"
      ".Lweapon_export_function_values_15:\n\t"
      "addl $-2, %%eax\n\t"
      "movswl %%ax, %%esi\n\t"
      "movl 0x4f0(%%ebx), %%eax\n\t"
      "cmpl %%eax, %%esi\n\t"
      "leal 0x4f0(%%ebx), %%ecx\n\t"
      "jge .Lweapon_export_function_values_23\n\t"
      "pushl $0x70\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movw 0xa(%%eax), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Lweapon_export_function_values_23\n\t"
      "leal (%%esi,%%esi,2), %%edx\n\t"
      "movswl 0x260(%%edi,%%edx,4), %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movswl %%ax, %%edx\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "fidivl -0x4(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jmp .Lweapon_export_function_values_23\n\t"
      ".Lweapon_export_function_values_16:\n\t"
      "movl 0x4fc(%%ebx), %%ecx\n\t"
      "addl $-7, %%eax\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .Lweapon_export_function_values_23\n\t"
      "leal (%%eax,%%eax,8), %%eax\n\t"
      "flds 0x224(%%edi,%%eax,4)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jmp .Lweapon_export_function_values_23\n\t"
      ".Lweapon_export_function_values_17:\n\t"
      "movl 0x4fc(%%ebx), %%ecx\n\t"
      "addl $-4, %%eax\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .Lweapon_export_function_values_23\n\t"
      "leal (%%eax,%%eax,8), %%ecx\n\t"
      "flds 0x220(%%edi,%%ecx,4)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jmp .Lweapon_export_function_values_23\n\t"
      ".Lweapon_export_function_values_18:\n\t"
      "movl 0x4fc(%%ebx), %%ecx\n\t"
      "addl $-0xf, %%eax\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .Lweapon_export_function_values_23\n\t"
      "leal (%%eax,%%eax,8), %%edx\n\t"
      "flds 0x220(%%edi,%%edx,4)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[gtime]\n\t"
      "subl 0x278(%%edi), %%eax\n\t"
      "cmpl $1, %%eax\n\t"
      "jle .Lweapon_export_function_values_23\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jmp .Lweapon_export_function_values_23\n\t"
      ".Lweapon_export_function_values_19:\n\t"
      "movl 0x4fc(%%ebx), %%edx\n\t"
      "leal -0xa(%%eax), %%esi\n\t"
      "leal 0x4fc(%%ebx), %%eax\n\t"
      "movswl %%si, %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jge .Lweapon_export_function_values_23\n\t"
      "pushl $0x114\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "call *%[fb320]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[fb510]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "jmp .Lweapon_export_function_values_23\n\t"
      ".Lweapon_export_function_values_20:\n\t"
      "movl 0x1f8(%%edi), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .Lweapon_export_function_values_23\n\t"
      ".Lweapon_export_function_values_21:\n\t"
      "movl 0x1f0(%%edi), %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jmp .Lweapon_export_function_values_23\n\t"
      ".Lweapon_export_function_values_22:\n\t"
      "fstp %%st(0)\n\t"
      ".Lweapon_export_function_values_23:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      ".Lweapon_export_function_values_24:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "addl $2, %%edx\n\t"
      "addl $4, %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "jne .Lweapon_export_function_values_3\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lweapon_export_function_values_jt:\n\t"
      ".long .Lweapon_export_function_values_5\n\t"
      ".long .Lweapon_export_function_values_15\n\t"
      ".long .Lweapon_export_function_values_15\n\t"
      ".long .Lweapon_export_function_values_17\n\t"
      ".long .Lweapon_export_function_values_17\n\t"
      ".long .Lweapon_export_function_values_4\n\t"
      ".long .Lweapon_export_function_values_16\n\t"
      ".long .Lweapon_export_function_values_16\n\t"
      ".long .Lweapon_export_function_values_6\n\t"
      ".long .Lweapon_export_function_values_19\n\t"
      ".long .Lweapon_export_function_values_19\n\t"
      ".long .Lweapon_export_function_values_7\n\t"
      ".long .Lweapon_export_function_values_21\n\t"
      ".long .Lweapon_export_function_values_20\n\t"
      ".long .Lweapon_export_function_values_18\n\t"
      ".long .Lweapon_export_function_values_18\n\t"
      ".text\n\t"
      :
      : [get] "m"(wefv_get), [tag] "m"(wefv_tag), [elem] "m"(wefv_elem), [fb320] "m"(wefv_fb320), [fb510] "m"(wefv_fb510), [gtime] "m"(wefv_gtime)
      : "memory");
}
#else
#error "weapon_export_function_values: clang naked draft required"
#endif

/* 0xfc4b0 — store owner transition state and evaluate owned-weapon curve. */
void weapon_owner_update(int weapon_handle, int16_t owner_state, float t)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  float value;

  tag_get(0x77656170, *(int *)weapon_obj); /* 'weap' */
  *(int16_t *)(weapon_obj + 0x1e0) = owner_state;
  value = transition_function_evaluate(4, t);
  *(float *)(weapon_obj + 0x1e4) = value;

  if ((*(uint32_t *)&value & 0x7f800000u) == 0x7f800000u) {
    display_assert(
        csprintf((char *)0x5ab100, (char *)0x0025eb8c, (char *)0x0028aeb8,
                 *(unsigned int *)(weapon_obj + 0x1e4), (double)value),
        (char *)0x0028ad48, 0x4af, 1);
    system_exit(-1);
  }
}


/* weapon_build_weapon_interface_state (0xfc550) — readable C lift. */
void weapon_build_weapon_interface_state(int weapon_handle, int out_state)
{
  extern char DAT_0028adb8[];
  extern char DAT_0028ad48[];
  char *weapon;
  char *tag_data;
  char *out;
  void *mag_block;
  int count;
  int16_t i;

  weapon = (char *)object_get_and_verify_type(weapon_handle, 4);
  tag_data = (char *)tag_get(0x77656170, *(int *)weapon);
  out = (char *)out_state;

  *(int *)out = *(int *)(weapon + 0x1ec);
  *(int *)(out + 4) = *(int *)(weapon + 0x1f0);
  out[8] = (char)(weapon[0x1dc] & 1);
  mag_block = (void *)(tag_data + 0x4f0);
  *(int16_t *)(out + 0xa) = *(int16_t *)mag_block;
  count = *(int *)mag_block;

  for (i = 0; (int)i < count; i++) {
    char *mag_entry;
    char *mag_def;
    char *rec;
    int16_t state;
    char busy;

    (void)tag_get(0x77656170, *(int *)weapon);
    if ((int16_t)i < 0 || (int)i >= *(int *)(tag_data + 0x4f0)) {
      display_assert(DAT_0028adb8, DAT_0028ad48, 0x672, 1);
      system_exit(-1);
    }
    mag_entry = weapon + ((int)i * 3 + 0x96) * 4;
    mag_def = (char *)tag_block_get_element(mag_block, (int)i, 0x70);
    state = *(int16_t *)mag_entry;
    busy = (state == 1 || state == 3) ? 1 : 0;
    rec = out + 0xc + (int)i * 10;
    rec[0] = busy;
    rec[1] = (state == 0) ? 1 : 0;
    *(int16_t *)(rec + 2) = *(int16_t *)(mag_entry + 8);
    *(int16_t *)(rec + 4) = *(int16_t *)(mag_def + 0xa);
    *(int16_t *)(rec + 6) = *(int16_t *)(mag_entry + 6);
    *(int16_t *)(rec + 8) = *(int16_t *)(mag_def + 8);
  }
}

/* 0xfc690 — true if magazine 0 is currently in the reloading state. */
char weapon_reloading(int weapon_handle)
{
  char *weapon_obj;
  char *tag_data;
  char result;

  weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);
  result = 0;
  if (*(int *)(tag_data + 0x4f0) > 0) {
    tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);
    if (*(int *)(tag_data + 0x4f0) <= 0) {
      display_assert((char *)0x0028adb8, (char *)0x0028ad48, 0x672, 1);
      system_exit(-1);
    }
    if (*(int16_t *)(weapon_obj + 0x258) == 1)
      return 1;
  }
  return result;
}


/* weapon_rotate_zoom_level (0xfc710) — readable C lift. */
int16_t weapon_rotate_zoom_level(int weapon_handle, int16_t zoom_level)
{
  char *weapon_obj; char *weapon_tag; int16_t levels;
  weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  weapon_tag = (char *)tag_get(0x77656170, *(int *)weapon_obj);
  if (weapon_reloading(weapon_handle)) return zoom_level;
  if (zoom_level >= 0) {
    levels = *(int16_t *)(weapon_tag + 0x3da);
    if ((int)zoom_level < (int)levels - 1) return (int16_t)(zoom_level + 1);
  }
  levels = *(int16_t *)(weapon_tag + 0x3da);
  if ((int)zoom_level == (int)levels - 1) return -1;
  return 0;
}
/* weapon_get_zoom_magnification (0xfc780) — readable C lift. */
float weapon_get_zoom_magnification(int weapon_handle, int16_t zoom_level)
{
  extern char DAT_0028ad48[];
  extern char DAT_0028aed8[];
  extern char DAT_0028aeec[];
  char *tag_data;
  float result;
  float min_zoom;
  float max_zoom;
  float t;

  tag_data = (char *)tag_get(
      0x77656170, *(int *)object_get_and_verify_type(weapon_handle, 4));
  result = *(float *)0x2533c8;
  if (zoom_level < 0 || zoom_level >= *(int16_t *)(tag_data + 0x3da))
    return result;

  if (*(int16_t *)(tag_data + 0x3da) > 1)
    t = (float)zoom_level / (float)(*(int16_t *)(tag_data + 0x3da) - 1);
  else
    t = 0.0f;

  min_zoom = (*(float *)(tag_data + 0x3dc) > *(float *)0x2533c0)
                 ? *(float *)(tag_data + 0x3dc)
                 : *(float *)0x2533c8;
  max_zoom = (*(float *)(tag_data + 0x3e0) > *(float *)0x2533c0)
                 ? *(float *)(tag_data + 0x3e0)
                 : *(float *)0x2533c8;

  result = FUN_001d9e70(max_zoom / min_zoom, t) * min_zoom;

  if ((*(unsigned int *)&result & 0x7f800000u) == 0x7f800000u) {
    display_assert(DAT_0028aeec, DAT_0028ad48, 0x5a2, 1);
    system_exit(-1);
  }
  if (!(result > *(float *)0x2533c0)) {
    display_assert(DAT_0028aed8, DAT_0028ad48, 0x5a3, 1);
    system_exit(-1);
  }
  return result;
}

/* weapon_get_field_of_view (0xfc8e0) — readable C lift. */
float weapon_get_field_of_view(int weapon_handle, float base_fov, int16_t zoom_level)
{
  float mag = weapon_get_zoom_magnification(weapon_handle, zoom_level);
  float one = *(float *)0x2533c8;
  float v;
  if (mag == one)
    return base_fov;
  v = base_fov / mag;
  /* Keep v only if v > *(float*)0x28af00 and v < *(float*)0x28aefc (asm tests). */
  if (v > *(float *)0x28af00 && v < *(float *)0x28aefc)
    return v;
  return base_fov;
}
/* weapon_prevents_melee_attack (0xfc930) — readable C lift. */
char weapon_prevents_melee_attack(int weapon_handle)
{
  void *obj;
  void *def;
  unsigned char state;
  unsigned char flag;
  if (weapon_handle == -1)
    return 1;
  obj = object_get_and_verify_type(weapon_handle, 4);
  def = tag_get(0x77656170, *(int *)obj);
  flag = (unsigned char)(((*(unsigned int *)((char *)def + 0x308)) >> 9) & 1);
  obj = object_get_and_verify_type(weapon_handle, 4);
  state = *(unsigned char *)((char *)obj + 0x211);
  if (state == 2)
    return flag;
  if (state != 3)
    return 0;
  return 1;
}
/* FUN_000fcbd0 (0xfcbd0) — readable C lift. */
void FUN_000fcbd0(int16_t magazine_index, int weapon_handle)
{
  char *weapon;
  char *mag;
  char *weap_tag;
  char *mag_def;

  weapon = (char *)object_get_and_verify_type(weapon_handle, 4);
  mag = (char *)FUN_000fb370(weapon, magazine_index);
  if (*(int16_t *)mag != 0 && *(int16_t *)mag != 2)
    return;
  weapon = (char *)object_get_and_verify_type(weapon_handle, 4);
  if (weapon[0x211] || weapon[0x235] || weapon[0x1e8])
    return;
  weap_tag = (char *)tag_get(0x77656170, *(int *)weapon);
  mag_def = (char *)tag_block_get_element((void *)(weap_tag + 0x4f0),
                                          (int)magazine_index, 0x70);
  (void)weapon_set_animation_state(weapon_handle, 0, (int16_t)(magazine_index + 3));
  (void)weapon_start_effect(*(int *)(mag_def + 0x54), 0.0f, 0.0f, weapon_handle);
  *(int16_t *)mag = 3;
  *(int16_t *)(mag + 2) =
      (int16_t)(int)(*(float *)(mag_def + 0x1c) * *(float *)0x253394);
}

/* FUN_000fcc90 (0xfcc90) — readable C lift: clear magazine loaded/total. */
void FUN_000fcc90(int16_t magazine_index /*@<eax>*/, int weapon_handle)
{
  char *weapon;
  int16_t *mag;
  void *tag;
  int16_t idx;

  idx = magazine_index;
  weapon = (char *)object_get_and_verify_type(weapon_handle, 4);
  mag = (int16_t *)FUN_000fb370(weapon, idx);
  tag = tag_get(0x77656170, *(int *)weapon);
  (void)tag_block_get_element((char *)tag + 0x4f0, (int)idx, 0x70);
  weapon = (char *)object_get_and_verify_type(weapon_handle, 4);
  mag = (int16_t *)FUN_000fb370(weapon, idx);
  tag = tag_get(0x77656170, *(int *)weapon);
  (void)tag_block_get_element((char *)tag + 0x4f0, (int)idx, 0x70);
  mag[0] = 0;
  mag[1] = 0;
}

/* 0xfcd10 — begin charged-trigger fire (trigger@eax, weapon cdecl). */
void FUN_000fcd10(int16_t trigger_index, int weapon_handle)
{
  char *weapon_obj;
  char *trig_def;
  int16_t frame;
  int idx;

  weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  FUN_000fb320(weapon_obj, trigger_index);
  trig_def = (char *)tag_block_get_element(
      (char *)tag_get(0x77656170, *(int *)weapon_obj) + 0x4fc,
      (int)trigger_index, 0x114);
  frame = (int16_t)(int)(*(float *)(trig_def + 0x4c) * 30.0f);

  weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  if ((int16_t)trigger_index < 0 || (int16_t)trigger_index >= 2) {
    display_assert((char *)0x0028ae40, (char *)0x0028ad48, 0xa11, 1);
    system_exit(-1);
  }

  idx = (int)(int16_t)trigger_index;
  weapon_obj[idx * 36 + 0x211] = 3;
  *(int16_t *)(weapon_obj + idx * 36 + 0x212) = frame;
  weapon_set_animation_state(weapon_handle, 1, (int16_t)(idx + 7));
  first_person_weapon_message_from_weapon(weapon_handle, 0xe);
}


/* FUN_000fcdd0 (0xfcdd0) — readable C lift. */
void FUN_000fcdd0(int16_t trigger_index, int weapon_handle)
{
  extern char DAT_0028ae40[];
  extern char DAT_0028ad48[];
  char *weapon;
  char *weap_tag;
  char *slot;
  weapon = (char *)object_get_and_verify_type(weapon_handle, 4);
  (void)FUN_000fb320(weapon, trigger_index);
  weap_tag = (char *)tag_get(0x77656170, *(int *)weapon);
  (void)tag_block_get_element((void *)(weap_tag + 0x4fc), (int)trigger_index, 0x114);
  weapon = (char *)object_get_and_verify_type(weapon_handle, 4);
  if (trigger_index < 0 || trigger_index >= 2) {
    display_assert(DAT_0028ae40, DAT_0028ad48, 0xa11, 1);
    system_exit(-1);
  }
  slot = weapon + (int)trigger_index * 36;
  slot[0x211] = 0;
  *(int16_t *)(slot + 0x212) = 0;
}

/* FUN_000fce60 (0xfce60) — readable C lift: init trigger overcharged state. */
void FUN_000fce60(int weapon_handle /*@<eax>*/, int16_t trigger_index /*@<si>*/)
{
  extern char DAT_0028ad48[];
  extern char DAT_0028ae40[];
  char *weapon;
  char *slot;

  weapon = (char *)object_get_and_verify_type(weapon_handle, 4);
  if (trigger_index < 0 || trigger_index >= 2) {
    display_assert(DAT_0028ae40, DAT_0028ad48, 0xa11, 1);
    system_exit(-1);
  }
  slot = weapon + (int)trigger_index * 36;
  *(unsigned char *)(slot + 0x211) = 7;
  *(int16_t *)(slot + 0x212) = -1;
}

/* FUN_000fcec0 (0xfcec0) — readable C lift. */
void FUN_000fcec0(int16_t trigger_index, int weapon_handle)
{
  char *weapon;
  char *state;
  char *weap_tag;
  weapon = (char *)object_get_and_verify_type(weapon_handle, 4);
  state = (char *)FUN_000fb320(weapon, trigger_index);
  weap_tag = (char *)tag_get(0x77656170, *(int *)weapon);
  (void)tag_block_get_element((void *)(weap_tag + 0x4fc), (int)trigger_index, 0x114);
  *state = 0;
  FUN_000fcdd0(trigger_index, weapon_handle);
}

/* FUN_000fd0b0 (0xfd0b0) — readable C lift. */
void FUN_000fd0b0(int16_t angle_index, float *out_x, float *out_y,
                  int16_t param_3, float scale, char flag)
{
  float angle;
  int16_t idx;

  idx = angle_index;
  if ((flag & 1) != 0) {
    if (idx == 0) {
      angle = *(float *)0x2533c0;
    } else if (((idx - 1) & 1) != 0) {
      angle = (float)(int)((int16_t)(idx - 1) >> 1);
    } else {
      angle = (float)(int)(int16_t)(-(idx >> 1));
    }
  } else {
    angle = (float)(int)(int16_t)(idx >> 1) - *(float *)0x253398;
    if ((idx & 1) != 0)
      angle = -angle;
  }

  angle *= scale;

  if ((int16_t)(param_3 - 1) == 0) {
    float sin_a;
    float cos_a;

    cos_a = xbox_cosf(angle);
    sin_a = xbox_sinf(angle);
    rotate_vector3d_by_sincos(out_x, out_y, sin_a, cos_a);
  }
}

/* FUN_000fd150 (0xfd150) — readable C lift: reset weapon anim if not in fire states. */
void FUN_000fd150(int weapon_handle /*@<esi>*/)
{
  char *weapon;
  unsigned char state;

  weapon = (char *)object_get_and_verify_type(weapon_handle, 4);
  state = *(unsigned char *)(weapon + 0x1e8);
  if (state < 7 || (state > 8 && state != 10))
    weapon_set_animation_state(weapon_handle, 1, 0);
}

/* 0xfd510 */
void weapon_stop_reload(int weapon_handle)
{
  weapon_reset_state(weapon_handle);
}

/* FUN_000fd520 (0xfd520) — readable C lift: clear trigger ownership then reset. */
void FUN_000fd520(int16_t trigger_index /*@<eax>*/, int weapon_handle /*@<ecx>*/)
{
  char *weapon;
  char *trig;
  void *tag;

  weapon = (char *)object_get_and_verify_type(weapon_handle, 4);
  trig = FUN_000fb320(weapon, trigger_index);
  tag = tag_get(0x77656170, *(int *)weapon);
  (void)trig;
  (void)tag_block_get_element((char *)tag + 0x4fc, (int)trigger_index, 0x114);
  *(int *)(weapon + 0x200) = -1;
  FUN_000fcec0(trigger_index, weapon_handle);
}

/* 0xfd570 — fire projectile(s) from a weapon trigger. */
#if defined(__clang__)
static float (*const fd570_norm)(float *) = normalize3d;
static char (*const fd570_a1080)(int) = FUN_00021080;
static int (*const fd570_aap)(int, float *, float *, int *) = actor_aim_projectile;
static int (*const fd570_pap)(int, float *, float *) = player_aim_projectile;
static void (*const fd570_pkill)(int) = projectile_kill_tracer;
static void (*const fd570_pstgt)(int, int) = projectile_set_target_object_index;
static char *(*const fd570_fb320)(void *, short) = FUN_000fb320;
static void (*const fd570_fd0b0)(short, float *, float *, short, float, char) = FUN_000fd0b0;
static int *(*const fd570_gseed)(void) = get_global_random_seed_address;
static void (*const fd570_rndir)(int *, float *, float, float, float *) = random_direction3d;
static void (*const fd570_perp)(float *, float *) = perpendicular3d;
static void *(*const fd570_tryget)(int, int) = object_try_and_get_and_verify_type;
static void *(*const fd570_get)(int, int) = object_get_and_verify_type;
static void (*const fd570_opnew)(void *, int, int) = object_placement_data_new;
static short (*const fd570_markers)(int, void *, void *, int) = object_get_markers_by_string_id;
static int (*const fd570_onew)(void *) = object_new;
static bool (*const fd570_oplace)(int, float *) = object_try_place;
static void *(*const fd570_elem)(void *, int, int) = tag_block_get_element;
static void (*const fd570_useat)(int, float *) = unit_set_seat_state;
static void (*const fd570_uadj)(int, float *, float *, float *, char, char) = unit_adjust_projectile_ray;
static void *(*const fd570_tag)(int, int) = tag_get;
static void (*const fd570_chkstk)(void) = FUN_001d90e0;

__attribute__((naked, noinline))
void FUN_000fd570(int weapon_handle __attribute__((unused)), short trigger_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x1c20, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, -0x54(%%ebp)\n\t"
      "call *%[fb320]\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x77656170\n\t"
      "movl %%eax, -0x88(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movswl %%si, %%ebx\n\t"
      "pushl $0x114\n\t"
      "movl %%eax, -0x64(%%ebp)\n\t"
      "addl $0x4fc, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $4\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "addl $0x24, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl $0xffffffff, -0x3c(%%ebp)\n\t"
      "je .LFUN_000fd570_1\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000fd570_1\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      ".LFUN_000fd570_1:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl $4\n\t"
      "pushl %%esi\n\t"
      "movl $0x267238, -0x6c(%%ebp)\n\t"
      "movl $0x28af04, -0x68(%%ebp)\n\t"
      "call *%[get]\n\t"
      "movb 0x4(%%eax), %%dl\n\t"
      "addl $8, %%esp\n\t"
      "testb $1, %%dl\n\t"
      "movl %%esi, %%ecx\n\t"
      "je .LFUN_000fd570_2\n\t"
      "movl 0xcc(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000fd570_2\n\t"
      "movl %%eax, %%ecx\n\t"
      ".LFUN_000fd570_2:\n\t"
      "movl -0x6c(%%ebp,%%ebx,4), %%eax\n\t"
      "pushl $0x40\n\t"
      "leal -0x1c20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[markers]\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_000fd570_3\n\t"
      "movl $1, %%eax\n\t"
      ".LFUN_000fd570_3:\n\t"
      "testb $0x20, (%%edi)\n\t"
      "jne .LFUN_000fd570_4\n\t"
      "movl $1, %%eax\n\t"
      ".LFUN_000fd570_4:\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_000fd570_36\n\t"
      "movzwl %%ax, %%edx\n\t"
      "leal -0x1bc0(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "movl %%edx, -0x60(%%ebp)\n\t"
      ".LFUN_000fd570_5:\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "addl $-0x24, %%eax\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl -0x3c(%%ebp), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl $0, -0x40(%%ebp)\n\t"
      "movl $0, -0x30(%%ebp)\n\t"
      "call *%[tryget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%edi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testb $8, %%ah\n\t"
      "movl %%esi, -0x58(%%ebp)\n\t"
      "movl $0xffffffff, -0x50(%%ebp)\n\t"
      "jne .LFUN_000fd570_12\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000fd570_12\n\t"
      "testb $4, 0xb6(%%esi)\n\t"
      "jne .LFUN_000fd570_12\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl -0x58(%%ebp), %%edx\n\t"
      "movl 0x1c8(%%esi), %%ebx\n\t"
      "movl 0x1a4(%%esi), %%esi\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl 0x2d8(%%edx), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000fd570_6\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0x1c8(%%eax), %%ebx\n\t"
      "movl 0x1a4(%%eax), %%esi\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000fd570_6:\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl 0x17c(%%eax), %%ecx\n\t"
      "shrl $3, %%ecx\n\t"
      "andb $1, %%cl\n\t"
      "cmpl $-1, %%esi\n\t"
      "movb %%cl, -0x8c(%%ebp)\n\t"
      "movb $1, -0x5c(%%ebp)\n\t"
      "je .LFUN_000fd570_7\n\t"
      "pushl %%esi\n\t"
      "call *%[a1080]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000fd570_7\n\t"
      "movb $0, -0x5c(%%ebp)\n\t"
      ".LFUN_000fd570_7:\n\t"
      "movl -0x58(%%ebp), %%edx\n\t"
      "cmpl $-1, 0x2d8(%%edx)\n\t"
      "je .LFUN_000fd570_8\n\t"
      "movb $0, -0x5c(%%ebp)\n\t"
      ".LFUN_000fd570_8:\n\t"
      "movl -0x5c(%%ebp), %%eax\n\t"
      "movl -0x8c(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0x3c(%%ebp), %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[uadj]\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .LFUN_000fd570_10\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000fd570_9\n\t"
      "movl 0x31fc40, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      ".LFUN_000fd570_9:\n\t"
      "flds -0x24(%%ebp)\n\t"
      "leal -0x78(%%ebp), %%edx\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x78(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x74(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x70(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x84(%%edi)\n\t"
      "movl 0x88(%%edi), %%eax\n\t"
      "flds -0x10(%%ebp)\n\t"
      "movl %%eax, -0x48(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movl 0x8c(%%edi), %%ecx\n\t"
      "movl %%ecx, -0x4c(%%ebp)\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "flds -0xc(%%ebp)\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x48(%%ebp)\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstp %%st(2)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x48(%%ebp)\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x48(%%ebp)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x78(%%ebp)\n\t"
      "fmuls -0x4c(%%ebp)\n\t"
      "fadd %%st(2), %%st(0)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x74(%%ebp)\n\t"
      "fmuls -0x4c(%%ebp)\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x70(%%ebp)\n\t"
      "fmuls -0x4c(%%ebp)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "call *%[pap]\n\t"
      "jmp .LFUN_000fd570_11\n\t"
      ".LFUN_000fd570_10:\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_000fd570_12\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[aap]\n\t"
      ".LFUN_000fd570_11:\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, -0x50(%%ebp)\n\t"
      ".LFUN_000fd570_12:\n\t"
      "testb $0x20, (%%edi)\n\t"
      "je .LFUN_000fd570_13\n\t"
      "movl -0x34(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      ".LFUN_000fd570_13:\n\t"
      "cmpw $0, 0xc(%%ebp)\n\t"
      "movl -0x54(%%ebp), %%ebx\n\t"
      "jne .LFUN_000fd570_15\n\t"
      "cmpw $0, 0x20c(%%ebx)\n\t"
      "jle .LFUN_000fd570_15\n\t"
      "movl -0x64(%%ebp), %%eax\n\t"
      "pushl $0x114\n\t"
      "addl $0x4fc, %%eax\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl -0x64(%%ebp), %%edx\n\t"
      "movl 0xa0(%%eax), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x20c(%%ebx), %%cx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $4, 0x32c(%%edx)\n\t"
      "jne .LFUN_000fd570_14\n\t"
      "incl %%ecx\n\t"
      ".LFUN_000fd570_14:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x6e(%%edi), %%dx\n\t"
      "imulw %%cx, %%dx\n\t"
      "movw $0, 0x20c(%%ebx)\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "jmp .LFUN_000fd570_16\n\t"
      ".LFUN_000fd570_15:\n\t"
      "movw 0x6e(%%edi), %%cx\n\t"
      "movl 0xa0(%%edi), %%eax\n\t"
      "movw %%cx, -0x38(%%ebp)\n\t"
      ".LFUN_000fd570_16:\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000fd570_35\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $4\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl $0xffffffff, -0x44(%%ebp)\n\t"
      "je .LFUN_000fd570_17\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000fd570_17\n\t"
      "movl 0x2d8(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl 0xcc(%%esi), %%ecx\n\t"
      "movl %%ecx, -0x44(%%ebp)\n\t"
      "je .LFUN_000fd570_17\n\t"
      "movl %%eax, -0x44(%%ebp)\n\t"
      ".LFUN_000fd570_17:\n\t"
      "cmpw $0, -0x38(%%ebp)\n\t"
      "movl $0, -0x20(%%ebp)\n\t"
      "jle .LFUN_000fd570_35\n\t"
      "jmp .LFUN_000fd570_19\n\t"
      ".LFUN_000fd570_18:\n\t"
      "movl -0x54(%%ebp), %%ebx\n\t"
      ".LFUN_000fd570_19:\n\t"
      "movl -0x44(%%ebp), %%edx\n\t"
      "movl 0xa0(%%edi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x114(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[opnew]\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl %%ecx, -0xf4(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0xd8(%%ebp)\n\t"
      "movl -0x88(%%ebp), %%ecx\n\t"
      "flds 0x10(%%ecx)\n\t"
      "movl %%eax, -0xf8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0xdc(%%ebp)\n\t"
      "movl %%edx, -0xfc(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "fnstsw %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%edx, -0xe0(%%ebp)\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000fd570_20\n\t"
      "movw 0x26(%%edi), %%dx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0xe(%%ecx), %%ax\n\t"
      "cmpw %%dx, %%ax\n\t"
      "leal 0x1(%%eax), %%esi\n\t"
      "movw %%si, 0xe(%%ecx)\n\t"
      "jl .LFUN_000fd570_21\n\t"
      ".LFUN_000fd570_20:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movw $0, 0xe(%%ecx)\n\t"
      ".LFUN_000fd570_21:\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000fd570_24\n\t"
      "movl (%%edi), %%eax\n\t"
      "testb $2, %%ah\n\t"
      "je .LFUN_000fd570_22\n\t"
      "flds 0x1e4(%%ebx)\n\t"
      "jmp .LFUN_000fd570_23\n\t"
      ".LFUN_000fd570_22:\n\t"
      "flds 0x1c(%%ecx)\n\t"
      ".LFUN_000fd570_23:\n\t"
      "flds 0x2533c8\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fmuls 0x7c(%%edi)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x80(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      ".LFUN_000fd570_24:\n\t"
      "movl (%%edi), %%eax\n\t"
      "testb $4, %%ah\n\t"
      "je .LFUN_000fd570_25\n\t"
      "testb $0x40, 0x1e0(%%ebx)\n\t"
      "jne .LFUN_000fd570_26\n\t"
      ".LFUN_000fd570_25:\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "movl 0x78(%%edi), %%eax\n\t"
      "leal -0xe0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0xe0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x68(%%ebp)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rndir]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000fd570_26:\n\t"
      "movl -0x20(%%ebp), %%esi\n\t"
      "testw %%si, %%si\n\t"
      "jne .LFUN_000fd570_27\n\t"
      "movl -0xe0(%%ebp), %%edx\n\t"
      "movl -0xdc(%%ebp), %%eax\n\t"
      "movl -0xd8(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x84(%%ebp)\n\t"
      "movl %%eax, -0x80(%%ebp)\n\t"
      "movl %%ecx, -0x7c(%%ebp)\n\t"
      ".LFUN_000fd570_27:\n\t"
      "movl (%%edi), %%eax\n\t"
      "testb $0x10, %%ah\n\t"
      "je .LFUN_000fd570_28\n\t"
      "movl -0x84(%%ebp), %%edx\n\t"
      "movl -0x80(%%ebp), %%eax\n\t"
      "movl -0x7c(%%ebp), %%ecx\n\t"
      "movl %%edx, -0xe0(%%ebp)\n\t"
      "movl %%eax, -0xdc(%%ebp)\n\t"
      "movl %%ecx, -0xd8(%%ebp)\n\t"
      ".LFUN_000fd570_28:\n\t"
      "leal -0xd4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xe0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[perp]\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x8(%%ecx)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x4(%%ecx)\n\t"
      "flds (%%ecx)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_000fd570_29\n\t"
      "fdivrs 0x2533c8\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%ecx)\n\t"
      "fstps (%%ecx)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "fstps 0x4(%%ecx)\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      "fstps 0x8(%%ecx)\n\t"
      "jmp .LFUN_000fd570_30\n\t"
      ".LFUN_000fd570_29:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_000fd570_30:\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "movl 0x70(%%edi), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x6c(%%edi), %%ax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0xd4(%%ebp), %%ecx\n\t"
      "leal -0xe0(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[fd0b0]\n\t"
      "flds -0xe0(%%ebp)\n\t"
      "fmuls -0x40(%%ebp)\n\t"
      "movl -0x58(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "fstps -0xec(%%ebp)\n\t"
      "flds -0xdc(%%ebp)\n\t"
      "fmuls -0x40(%%ebp)\n\t"
      "fstps -0xe8(%%ebp)\n\t"
      "flds -0xd8(%%ebp)\n\t"
      "fmuls -0x40(%%ebp)\n\t"
      "fstps -0xe4(%%ebp)\n\t"
      "je .LFUN_000fd570_37\n\t"
      "cmpl $-1, 0x1c8(%%eax)\n\t"
      "je .LFUN_000fd570_37\n\t"
      "movl -0x110(%%ebp), %%eax\n\t"
      "orl $2, %%eax\n\t"
      "movb $1, %%bl\n\t"
      "movl %%eax, -0x110(%%ebp)\n\t"
      ".LFUN_000fd570_31:\n\t"
      "leal -0x114(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[onew]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_000fd570_34\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_000fd570_32\n\t"
      "movl -0x3c(%%ebp), %%edx\n\t"
      "leal -0x120(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[useat]\n\t"
      "leal -0x120(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[oplace]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_000fd570_32:\n\t"
      "movl -0x50(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000fd570_33\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[pstgt]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000fd570_33:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000fd570_34\n\t"
      "pushl %%esi\n\t"
      "call *%[pkill]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000fd570_34:\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw -0x38(%%ebp), %%ax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jl .LFUN_000fd570_18\n\t"
      ".LFUN_000fd570_35:\n\t"
      "movl -0x34(%%ebp), %%ecx\n\t"
      "movl -0x60(%%ebp), %%eax\n\t"
      "addl $0x6c, %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "movl %%eax, -0x60(%%ebp)\n\t"
      "jne .LFUN_000fd570_5\n\t"
      ".LFUN_000fd570_36:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000fd570_37:\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .LFUN_000fd570_31\n\t"
      :
      : [norm] "m"(fd570_norm), [a1080] "m"(fd570_a1080), [aap] "m"(fd570_aap), [pap] "m"(fd570_pap), [pkill] "m"(fd570_pkill), [pstgt] "m"(fd570_pstgt), [fb320] "m"(fd570_fb320), [fd0b0] "m"(fd570_fd0b0), [gseed] "m"(fd570_gseed), [rndir] "m"(fd570_rndir), [perp] "m"(fd570_perp), [tryget] "m"(fd570_tryget), [get] "m"(fd570_get), [opnew] "m"(fd570_opnew), [markers] "m"(fd570_markers), [onew] "m"(fd570_onew), [oplace] "m"(fd570_oplace), [elem] "m"(fd570_elem), [useat] "m"(fd570_useat), [uadj] "m"(fd570_uadj), [tag] "m"(fd570_tag), [chkstk] "m"(fd570_chkstk)
      : "memory");
}
#else
void FUN_000fd570(int weapon_handle, int16_t trigger_index)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  char *trigger_entry = FUN_000fb320(weapon_obj, trigger_index);
  char *tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);
  char *trig_def = (char *)tag_block_get_element((void *)(tag_data + 0x4fc),
                                                 (int)trigger_index, 0x114);
  int unit_handle = -1;
  int owner_unit = -1;
  int parent_handle;
  int marker_string_ids[2] = {0x267238, 0x28af04};
  void *marker_name = (void *)marker_string_ids[(int)trigger_index];
  int16_t marker_count;
  char marker_buf[0x40 * 0x6c];
  int16_t marker_index;
  int16_t projectile_count;
  int16_t shot_index;
  float origin[3];
  float direction[3];
  float up[3];
  int aim_extra;
  int proj_tag;
  char placement[0x100];
  int aim_target;
  float first_dir[3];

  if (*(int *)(weapon_obj + 0xcc) != -1 &&
      object_try_and_get_and_verify_type(*(int *)(weapon_obj + 0xcc), 3) != 0)
    unit_handle = *(int *)(weapon_obj + 0xcc);

  parent_handle = weapon_handle;
  {
    char *obj2 = (char *)object_get_and_verify_type(weapon_handle, 4);
    if ((obj2[4] & 1) != 0 && *(int *)(obj2 + 0xcc) != -1)
      parent_handle = *(int *)(obj2 + 0xcc);
  }

  marker_count = object_get_markers_by_string_id(parent_handle, marker_name,
                                                 marker_buf, 0x40);
  if (marker_count == 0)
    marker_count = 1;
  if ((*(unsigned char *)trig_def & 0x20) == 0)
    marker_count = 1;
  if (marker_count <= 0)
    return;

  for (marker_index = 0; marker_index < marker_count; marker_index++) {
    char *marker = marker_buf + marker_index * 0x6c;
    float *marker_pos = (float *)(marker + 0x60);
    float *marker_fwd = (float *)(marker + 0x3c);
    float *marker_up = (float *)(marker + 0x48);

    origin[0] = marker_pos[0];
    origin[1] = marker_pos[1];
    origin[2] = marker_pos[2];
    direction[0] = marker_fwd[0];
    direction[1] = marker_fwd[1];
    direction[2] = marker_fwd[2];
    up[0] = marker_up[0];
    up[1] = marker_up[1];
    up[2] = marker_up[2];
    aim_target = -1;
    aim_extra = 0;

    if ((*(unsigned int *)trig_def & 0x800) == 0 && unit_handle != -1) {
      char *unit =
          (char *)object_try_and_get_and_verify_type(unit_handle, 3);
      if (unit != 0 && (*(unsigned char *)(unit + 0xb6) & 4) == 0) {
        unit_adjust_projectile_ray(unit_handle, origin, direction, up, 1, 1);
        if (normalize3d(up) == 0.0f) {
          float *world_up = *(float **)0x31fc40;
          up[0] = world_up[0];
          up[1] = world_up[1];
          up[2] = world_up[2];
        }
      } else {
        aim_target =
            actor_aim_projectile(unit_handle, origin, direction, &aim_extra);
      }
    } else if (unit_handle != -1) {
      aim_target =
          actor_aim_projectile(unit_handle, origin, direction, &aim_extra);
    }

    if ((*(unsigned char *)trig_def & 0x20) != 0) {
      origin[0] = marker_pos[0];
      origin[1] = marker_pos[1];
      origin[2] = marker_pos[2];
    }

    proj_tag = *(int *)(trig_def + 0xa0);
    if (trigger_index == 0 && *(int16_t *)(weapon_obj + 0x20c) > 0) {
      int16_t bursts = *(int16_t *)(weapon_obj + 0x20c);
      if (*(int16_t *)(tag_data + 0x32c) == 4)
        bursts = (int16_t)(bursts + 1);
      projectile_count =
          (int16_t)(*(int16_t *)(trig_def + 0x6e) * (int)bursts);
      *(int16_t *)(weapon_obj + 0x20c) = 0;
    } else {
      projectile_count = *(int16_t *)(trig_def + 0x6e);
    }
    if (proj_tag == -1 || projectile_count <= 0)
      continue;

    owner_unit = -1;
    {
      char *w = (char *)object_get_and_verify_type(weapon_handle, 4);
      if (*(int *)(w + 0xcc) != -1) {
        char *parent =
            (char *)object_try_and_get_and_verify_type(*(int *)(w + 0xcc), 3);
        if (parent != 0) {
          owner_unit = *(int *)(w + 0xcc);
          if (*(int *)(parent + 0x2d8) != -1)
            owner_unit = *(int *)(parent + 0x2d8);
        }
      }
    }

    for (shot_index = 0; shot_index < projectile_count; shot_index++) {
      char is_tracer = 0;
      int proj_handle;
      float shot_dir[3];
      float error_angle;
      char from_vehicle = 0;

      object_placement_data_new(placement, proj_tag, owner_unit);
      *(float *)(placement + 0x20) = origin[0];
      *(float *)(placement + 0x24) = origin[1];
      *(float *)(placement + 0x28) = origin[2];

      if (*(float *)(trigger_entry + 0x10) != 0.0f) {
        if ((unsigned short)*(int16_t *)(trigger_entry + 0xe) >=
            (unsigned short)*(int16_t *)(trig_def + 0x26)) {
          is_tracer = 1;
          *(int16_t *)(trigger_entry + 0xe) = 0;
        } else {
          *(int16_t *)(trigger_entry + 0xe) =
              (int16_t)(*(int16_t *)(trigger_entry + 0xe) + 1);
        }
      }

      error_angle = 0.0f;
      if ((*(unsigned int *)trig_def & 0x200) != 0)
        error_angle = *(float *)(weapon_obj + 0x1e4);
      else
        error_angle = *(float *)(trigger_entry + 0x1c);
      error_angle = (1.0f - error_angle) * *(float *)(trig_def + 0x7c) +
                    error_angle * *(float *)(trig_def + 0x80);

      shot_dir[0] = direction[0];
      shot_dir[1] = direction[1];
      shot_dir[2] = direction[2];
      if ((*(unsigned int *)trig_def & 0x400) == 0 ||
          (*(unsigned char *)(weapon_obj + 0x1e0) & 0x40) == 0) {
        random_direction3d(get_global_random_seed_address(), shot_dir, 0.0f,
                           error_angle, shot_dir);
      }

      if (shot_index == 0) {
        first_dir[0] = shot_dir[0];
        first_dir[1] = shot_dir[1];
        first_dir[2] = shot_dir[2];
      }
      if ((*(unsigned int *)trig_def & 0x1000) != 0) {
        shot_dir[0] = first_dir[0];
        shot_dir[1] = first_dir[1];
        shot_dir[2] = first_dir[2];
      }

      {
        float perp[3];
        float mag;
        perpendicular3d(shot_dir, perp);
        mag = magnitude3d(shot_dir);
        if (mag > *(double *)0x2533d0) {
          shot_dir[0] /= mag;
          shot_dir[1] /= mag;
          shot_dir[2] /= mag;
        }
        (void)perp;
      }

      FUN_000fd0b0(shot_index, shot_dir, up, *(int16_t *)(trig_def + 0x6c),
                   *(float *)(trig_def + 0x70), (char)projectile_count);

      *(float *)(placement + 0x3c) = shot_dir[0];
      *(float *)(placement + 0x40) = shot_dir[1];
      *(float *)(placement + 0x44) = shot_dir[2];

      if (unit_handle != -1) {
        char *unit_obj =
            (char *)object_try_and_get_and_verify_type(unit_handle, 3);
        if (unit_obj != 0 && *(int *)(unit_obj + 0x1c8) != -1) {
          *(unsigned int *)(placement + 4) |= 2;
          from_vehicle = 1;
        }
      }

      proj_handle = object_new(placement);
      if (proj_handle != -1) {
        if (from_vehicle != 0) {
          float seat_pos[3];
          unit_set_seat_state(unit_handle, seat_pos);
          object_try_place(proj_handle, seat_pos);
        }
        if (aim_target != -1)
          projectile_set_target_object_index(proj_handle, aim_target);
        if (is_tracer == 0)
          projectile_kill_tracer(proj_handle);
      }
    }
  }
}
#endif


