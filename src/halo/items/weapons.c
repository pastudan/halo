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

/* 0xfae30 — weapon_preprocess_node_orientations
 *
 * Prefetches the weapon's animation graph block element for node orientation
 * processing. Resolves the weapon tag, finds the 'antr' tag, and calls
 * tag_block_get_element on the first animation element if the block is non-empty.
 * The result is discarded; the call likely primes an internal cache.
 *
 * Confirmed: cdecl, 1 stack arg (weapon_handle).
 * Confirmed: CALL object_get_and_verify_type(weapon_handle, 4).
 * Confirmed: CALL tag_get(0x77656170, *obj) → weap_tag.
 * Confirmed: CALL tag_get(0x616e7472, *(weap_tag+0x44)) → antr.
 * Confirmed: CMP *(int *)(antr+0x18), 0; JZ exit.
 * Confirmed: CALL tag_block_get_element(antr+0x18, 0, 0x1c) (result unused).
 */
void weapon_preprocess_node_orientations(int weapon_handle)
{
  int *obj;
  int tag;
  int antr;

  obj = (int *)object_get_and_verify_type(weapon_handle, 4);
  tag = (int)tag_get(0x77656170, *obj);
  antr = (int)tag_get(0x616e7472, *(int *)(tag + 0x44));
  if (*(int *)(antr + 0x18) != 0) {
    tag_block_get_element((void *)(antr + 0x18), 0, 0x1c);
  }
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

/* 0xfb090 — weapon_must_be_readied
 *
 * Returns non-zero if the weapon's 'must be readied' flag is set
 * (bit 3 of the weapon definition flags at tag+0x308).
 *
 * Confirmed: cdecl, 1 stack arg (weapon_handle).
 * Confirmed: CALL object_get_and_verify_type(weapon_handle, 4).
 * Confirmed: CALL tag_get(0x77656170, *obj).
 * Confirmed: SHR EAX,3; AND EAX,1 on *(uint *)(tag+0x308).
 */
int weapon_must_be_readied(int weapon_handle)
{
  int *obj = (int *)object_get_and_verify_type(weapon_handle, 4);
  int tag = (int)tag_get(0x77656170, *obj);
  return (*(uint32_t *)(tag + 0x308) >> 3) & 1;
}

/* 0xfb0c0 — weapon_is_flag */
bool weapon_is_flag(int object_index)
{
  int *obj = (int *)object_get_and_verify_type(object_index, 4);
  uint32_t *tag = (uint32_t *)tag_get(0x77656170, *obj);
  return (tag[0x308 / 4] >> 3) & 1;
}

/* 0xfb0f0 — weapon_prevents_grenade_throwing
 *
 * Returns 1 if weapon_handle == -1 (no weapon), 1 if the weapon's animation
 * state at +0x1e8 is in range (4, 11), or the flag bit 6 of tag+0x308 is set.
 *
 * Confirmed: cdecl, 1 stack arg (param_1 = weapon_handle).
 * Confirmed: returns 1 immediately if param_1 == -1.
 * Confirmed: CALL object_get_and_verify_type(param_1, 4).
 * Confirmed: CALL tag_get(0x77656170, *obj).
 * Confirmed: SHR EAX,6; AND EAX,1 on *(uint *)(tag+0x308).
 * Confirmed: range check on *(char *)(obj+0x1e8): returns 1 if in (4,11).
 */
int weapon_prevents_grenade_throwing(int weapon_handle)
{
  int *obj;
  int tag;
  char result;

  result = 1;
  if (weapon_handle != -1) {
    obj = (int *)object_get_and_verify_type(weapon_handle, 4);
    tag = (int)tag_get(0x77656170, *obj);
    result = (char)((*(uint32_t *)(tag + 0x308) >> 6) & 1);
    if (*(char *)((char *)obj + 0x1e8) >= 5 &&
        *(char *)((char *)obj + 0x1e8) <= 10) {
      result = 1;
    }
  }
  return result;
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

/* 0xfb2f0 — weapon_overcharged
 *
 * Returns 1 if the weapon's trigger state at +0x211 is 2 (overcharge) or
 * 3 (overcharge-releasing), 0 otherwise.
 *
 * Confirmed: cdecl, 1 stack arg (weapon_handle).
 * Confirmed: CALL object_get_and_verify_type(weapon_handle, 4).
 * Confirmed: CMP BYTE PTR [EAX+0x211], 2 / JE; CMP ..., 3 / JE.
 * Confirmed: returns 1 if state == 2 or 3, else 0.
 */
int weapon_overcharged(int weapon_handle)
{
  int obj = (int)object_get_and_verify_type(weapon_handle, 4);
  if (*(char *)(obj + 0x211) != 2 && *(char *)(obj + 0x211) != 3)
    return 0;
  return 1;
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

/* Begin a magazine reload cycle (0xfc990).
 * If the magazine state is idle (0) or post-reload (2), and the weapon is
 * not in an animation, starts the reload animation and effect. For dual-wield
 * weapons (tag+0x4e2 == 1), computes the animation variant from whether the
 * magazine is one round short of full.
 *
 * Confirmed: magazine_index in AX (register arg), 2 stack args (weapon_handle,
 * param_2). Confirmed: calls object_get_and_verify_type(weapon_handle, 4)
 * twice. Confirmed: calls FUN_000fb370(weapon_obj@<edi>, magazine_index@<si>).
 * Confirmed: calls weapon_set_animation_state(weapon_handle, 0,
 * magazine_index+5 @<bx>). Confirmed: calls weapon_start_effect(mag_def[0x44],
 * 0, 0, weapon_handle@<eax>). Confirmed: calls
 * first_person_weapon_message_from_weapon(weapon_handle, 9 or 10). Confirmed:
 * calls weapon_get_animation_frame(weapon_handle, 0, 7, iVar6). Confirmed:
 * clears bit 3 of weapon_obj[0x1dc] on non-early-exit path.
 */
void FUN_000fc990(int16_t magazine_index, int weapon_handle, int param_2)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  int16_t *magazine_state =
    (int16_t *)FUN_000fb370((void *)weapon_obj, magazine_index);
  int tag_data = (int)tag_get(0x77656170, *(int *)weapon_obj);
  char *mag_def = (char *)tag_block_get_element((char *)tag_data + 0x4f0,
                                                (int)magazine_index, 0x70);

  if (*magazine_state == 0 || *magazine_state == 2) {
    int iVar6 = (int)object_get_and_verify_type(weapon_handle, 4);
    if (*(char *)(iVar6 + 0x211) == 0 && *(char *)(iVar6 + 0x235) == 0 &&
        *(char *)(iVar6 + 0x1e8) == 0) {
      if (magazine_state[3] > 0 &&
          magazine_state[4] < *(int16_t *)(mag_def + 0xa)) {
        int16_t anim_variant = -1;
        int16_t frame;
        weapon_set_animation_state(weapon_handle, 0,
                                   (int16_t)(magazine_index + 5));
        weapon_start_effect(*(int *)(mag_def + 0x44), 0, 0, weapon_handle);
        first_person_weapon_message_from_weapon(weapon_handle,
                                                (magazine_state[4] != 0) + 9);

        if (*(int16_t *)(tag_data + 0x4e2) == 1) {
          int diff_is_one =
            ((int)*(int16_t *)(mag_def + 0xa) - (int)magazine_state[4]) == 1;
          if (param_2 == 0) {
            anim_variant = diff_is_one ? 1 : -1;
          } else {
            anim_variant = diff_is_one ? 2 : 0;
          }
        }

        *magazine_state = 1;
        frame =
          weapon_get_animation_frame(weapon_handle, 0, 7, anim_variant);
        magazine_state[1] = frame;
        magazine_state[2] = frame;
      }
      *(uint32_t *)(weapon_obj + 0x1dc) &= ~0x8u;
    }
  }
}

/* Complete a magazine reload cycle (0xfcaf0).
 * Transfers rounds from unloaded reserve to the loaded count, capped by
 * the tag's rounds-per-reload and maximum-rounds fields. Adjusts reserve
 * for dual-wield. Optionally starts the next reload cycle if rounds remain. */
void FUN_000fcaf0(int weapon_handle, int magazine_index)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  int16_t *magazine =
    (int16_t *)FUN_000fb370((void *)weapon_obj, (int16_t)magazine_index);
  void *tag_data = tag_get(0x77656170, *(int *)weapon_obj);
  char *mag_def = (char *)tag_block_get_element(
    (char *)tag_data + 0x4f0, (int)(int16_t)magazine_index, 0x70);
  int16_t rounds_unloaded;
  int16_t rounds_to_load;
  int16_t total;

  if ((*mag_def & 1) != 0) {
    magazine[4] = 0;
  }

  rounds_unloaded = magazine[3];
  rounds_to_load = rounds_unloaded;
  if (*(int16_t *)(mag_def + 0x18) <= rounds_unloaded) {
    rounds_to_load = *(int16_t *)(mag_def + 0x18);
  }

  total = magazine[4] + rounds_to_load;
  if (total > *(int16_t *)(mag_def + 0xa)) {
    total = *(int16_t *)(mag_def + 0xa);
  }

  if (*(char *)0x5aa892 == 0 && (*(uint8_t *)(weapon_obj + 0x1a4) & 2) != 0) {
    magazine[3] = (rounds_unloaded - total) + magazine[4];
  }

  magazine[4] = total;
  magazine[0] = 2;
  magazine[1] = 0;

  if (magazine[3] > 0 && total < *(int16_t *)(mag_def + 0xa) &&
      (*mag_def & 1) == 0 && (*(uint8_t *)(weapon_obj + 0x1e0) & 0x26) == 0) {
    FUN_000fc990((int16_t)magazine_index, weapon_handle, 0);
  }
}

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

/* 0xfad60 */
int weapon_place(int weapon_handle, void *placement)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  char *tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);
  char *place = (char *)placement;
  int magazine_count = *(int *)(tag_data + 0x4f0);

  if (magazine_count > 0) {
    char *mag_def =
      (char *)tag_block_get_element((void *)(tag_data + 0x4f0), 0, 0x70);
    int16_t total = *(int16_t *)(place + 0x48);
    int16_t max_total = *(int16_t *)(mag_def + 8);
    int16_t loaded = *(int16_t *)(place + 0x4a);
    int16_t max_loaded = *(int16_t *)(mag_def + 0xa);

    if (total > max_total)
      total = max_total;
    if (loaded > max_loaded)
      loaded = max_loaded;

    *(int16_t *)(weapon_obj + 0x25e) = total;
    *(int16_t *)(weapon_obj + 0x260) = loaded;
  }

  if ((place[0x4c] & 1) != 0)
    *(uint32_t *)(weapon_obj + 4) |= 0x20u;
  else
    *(uint32_t *)(weapon_obj + 4) &= ~0x20u;

  weapon_obj[6] |= 2;

  if ((place[0x4c] & 4) != 0)
    *(uint32_t *)(weapon_obj + 0x1a4) &= ~0x20u;
  else
    *(uint32_t *)(weapon_obj + 0x1a4) |= 0x20u;

  if ((place[0x4c] & 1) == 0)
    *(float *)(weapon_obj + 0x14) += *(float *)0x2533e8;

  return weapon_handle;
}

/* 0xfaf50 */
char weapon_can_be_fired(int weapon_handle)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  char *tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);

  if (*(float *)(weapon_obj + 0x1f0) < *(float *)0x2533c8)
    return 0;

  if (game_engine_running()) {
    if (*(int *)(tag_data + 0x4f0) > 0) {
      char *mag_def =
        (char *)tag_block_get_element((void *)(tag_data + 0x4f0), 0, 0x70);
      if (*(int16_t *)(mag_def + 0xa) > 0 &&
          *(int16_t *)(weapon_obj + 0x260) == 0 &&
          *(int16_t *)(weapon_obj + 0x25e) != 0)
        return 0;
    }
  }

  return 1;
}

/* 0xfafe0 */
char weapon_useful(int weapon_handle)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  return (*(float *)(weapon_obj + 0x1f0) >= *(float *)0x2533c8) ? 1 : 0;
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
  if (mode == 0 || mode == 1) {
    if (*(int16_t *)(weapon_obj + 0x258) != 1 &&
        *(int16_t *)(weapon_obj + 0x264) != 1 && param_3 == 0) {
      return 0.0f;
    }
  }

  return result;
}

/* 0xfb320 */
char *FUN_000fb320(void *weapon_obj, int16_t trigger_index)
{
  return weapon_get_trigger_entry(weapon_obj, trigger_index);
}

/* 0xfb510 — trigger charge fraction remaining (state 2 = charging). */
#if defined(__i386__) && defined(__GNUC__)
__attribute__((noinline))
#endif
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
    /* charging: 1.0 - frame * tick / period */
    return *(float *)0x2533c8 -
           (float)*(int16_t *)(trigger_entry + 2) * *(float *)0x2546a4 /
               *(float *)(trig_def + 0x48);
  }
  if (state == 1)
    return *(float *)0x2533c8; /* charged */
  return *(float *)0x2533c0;
}

/* 0xfb5a0 — trigger ready to fire */
char FUN_000fb5a0(int weapon_handle, int16_t trigger_index)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  char *trigger_entry = weapon_get_trigger_entry(weapon_obj, trigger_index);
  char *tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);
  char *trig_def = (char *)tag_block_get_element((void *)(tag_data + 0x4fc),
                                                 (int)trigger_index, 0x114);
  float threshold;
  float charge;
  char result = 0;

  if ((trig_def[0] & 2) != 0)
    charge = *(float *)(weapon_obj + 0x1e4);
  else
    charge = *(float *)(trigger_entry + 0x10);

  threshold = (*(float *)(trig_def + 8) - *(float *)(trig_def + 4)) *
                charge +
              *(float *)(trig_def + 4);

  if (threshold == *(float *)0x253f44)
    threshold = 0.0f;
  else
    threshold = *(float *)0x253394 / threshold;

  if (*(float *)(tag_data + 0x444) != 0.0f)
    threshold = (*(float *)(weapon_obj + 0x1f0) * *(float *)(tag_data + 0x444) +
                 1.0f) *
                threshold;

  if ((float)(char)trigger_entry[0] + 1.0f >= threshold)
    result = 1;

  if ((trig_def[0] & 8) != 0 && (*(uint8_t *)(weapon_obj + 0x1a4) & 2) != 0 &&
      (trigger_entry[4] & 1) == 0)
    return 0;

  return result;
}

/* 0xfb690 — Zero one weapon magazine's loaded/reserve counts. */
void FUN_000fb690(int weapon_handle, int16_t magazine_index)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  int16_t *magazine =
    (int16_t *)FUN_000fb370((void *)weapon_obj, magazine_index);
  char *tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);

  tag_block_get_element((void *)(tag_data + 0x4f0), (int)magazine_index, 0x70);
  magazine[0] = 0;
  magazine[1] = 0;
}

/* 0xfb7d0 — start attached effect on parent object */
int FUN_000fb7d0(int effect_tag, int weapon_handle)
{
  char *weapon_obj;
  int parent_handle = weapon_handle;
  int object_handle;

  if (effect_tag == -1)
    return -1;

  weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  if ((weapon_obj[4] & 1) != 0 && *(int *)(weapon_obj + 0xcc) != -1)
    parent_handle = *(int *)(weapon_obj + 0xcc);

  weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  object_handle = -1;
  if (*(int *)(weapon_obj + 0xcc) != -1 &&
      object_try_and_get_and_verify_type(*(int *)(weapon_obj + 0xcc), 3) != 0)
    object_handle = *(int *)(weapon_obj + 0xcc);
  (void)object_handle;

  if (parent_handle == -1)
    return -1;

  return FUN_0009eb40(effect_tag, parent_handle, (int16_t)-1, (int16_t)-1,
                      (int16_t)-1);
}

/* 0xfb880 — set a weapon trigger's state/frame (charge release path). */
#if defined(__i386__) && defined(__GNUC__)
__attribute__((noinline))
#endif
void weapon_trigger_release_charge(int16_t charge_counter, int weapon_handle,
                                   char state, int16_t trigger_index)
{
  char *weapon_obj;
  int idx;

  weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  if ((int16_t)trigger_index < 0 || (int16_t)trigger_index >= 2) {
    display_assert((char *)0x0028ae40, (char *)0x0028ad48, 0xa11, 1);
    system_exit(-1);
  }
  if ((int16_t)state < 0 || (int16_t)state >= 9) {
    display_assert((char *)0x0028ae08, (char *)0x0028ad48, 0xa12, 1);
    system_exit(-1);
  }

  idx = (int)(int16_t)trigger_index;
  weapon_obj[idx * 36 + 0x211] = state;
  *(int16_t *)(weapon_obj + idx * 36 + 0x212) = charge_counter;
}

/* 0xfb910 — Reset trigger charge when definition charge time is zero. */
#if defined(__i386__) && defined(__GNUC__)
__attribute__((regparm(2)))
#endif
void FUN_000fb910(int weapon_handle, int16_t trigger_index, char flag)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  char *tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);
  char *trigger_entry = FUN_000fb320(weapon_obj, trigger_index);
  char *trig_def = (char *)tag_block_get_element((void *)(tag_data + 0x4fc),
                                                 (int)trigger_index, 0x114);

  if (*(float *)(trig_def + 0xa4) != 0.0f)
    return;

  if ((*(int *)trig_def & 0x80) != 0) {
    if (flag != 0)
      *(float *)(trigger_entry + 0x14) = 1.0f;
  } else if (flag == 0) {
    *(float *)(trigger_entry + 0x14) = 1.0f;
  }
}

/* 0xfb990 — Reset trigger charge from weapon animation state. */
#if defined(__i386__) && defined(__GNUC__)
__attribute__((noinline))
#endif
void FUN_000fb990(int weapon_handle)
{
  char *weapon_obj;
  int state;

  weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  tag_get(0x77656170, *(int *)weapon_obj);
  state = (int)(signed char)weapon_obj[0x1e8];
  if (state == 3)
    FUN_000fb910(weapon_handle, (int16_t)0, 1);
  else if (state == 4)
    FUN_000fb910(weapon_handle, (int16_t)1, 1);
}

/* 0xfba00 */
char FUN_000fba00(int16_t value, int16_t threshold)
{
  if (value == 0)
    return 1;
  if (value <= 0 || value > 2)
    return 0;
  return (char)(threshold >= value);
}

/* 0xfbcf0 */
float FUN_000fbcf0(float base, float exponent)
{
  return FUN_001d9e70(base, exponent);
}

/* 0xfbd10 — initialize magazines/triggers for a newly created weapon. */
#if defined(__i386__) && defined(__GNUC__)
__attribute__((noinline))
#endif
char weapon_new(int weapon_handle)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  char *tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);
  int16_t magazine_index;
  int16_t trigger_index;

  weapon_obj[0x1e8] = 0;
  *(int *)(weapon_obj + 0x274) = -1;

  for (magazine_index = 0; (int)magazine_index < *(int *)(tag_data + 0x4f0);
       magazine_index++) {
    char *mag_def;
    char *mag_entry;
    int16_t initial_total;
    int16_t max_loaded;
    int16_t loaded;

    tag_get(0x77656170, *(int *)weapon_obj);
    if ((int16_t)magazine_index < 0 ||
        (int)magazine_index >= *(int *)(tag_data + 0x4f0)) {
      display_assert((char *)0x0028adb8, (char *)0x0028ad48, 0x672, 1);
      system_exit(-1);
    }
    mag_entry =
        (char *)weapon_obj + ((int)magazine_index * 3 + 0x96) * 4;
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

    tag_get(0x77656170, *(int *)weapon_obj);
    if ((int16_t)trigger_index < 0 ||
        (int)trigger_index >= *(int *)(tag_data + 0x4fc)) {
      display_assert((char *)0x0028ad68, (char *)0x0028ad48, 0x667, 1);
      system_exit(-1);
    }
    trigger_entry =
        (char *)weapon_obj + (int)trigger_index * 36 + 0x210;
    tag_block_get_element((void *)(tag_data + 0x4fc), (int)trigger_index,
                          0x114);
    *(int *)(trigger_entry + 0x20) = -1;
    trigger_entry[0] = (char)0x7f;
  }

  return 1;
}

/* 0xfbea0 */
void weapon_delete(int weapon_handle)
{
  char *tag_data;

  if (!game_engine_running())
    return;

  tag_data = (char *)tag_get(
    0x77656170,
    *(int *)object_get_and_verify_type(weapon_handle, 4));

  if ((*(uint32_t *)(tag_data + 0x308) >> 3) & 1) {
    display_assert(0, "c:\\halo\\SOURCE\\items\\weapons.c", 0xea, 1);
    system_exit(-1);
  }
}

/* Jump-table cases at 0xfc244 — function_id is 1..16 (table index = id-1). */
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

/* 0xfbf00 — export up to 4 weapon function values onto the attachment root. */
void weapon_export_function_values(int weapon_handle)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  char *tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);
  char *out_obj = weapon_obj;
  int16_t *fn_ids;
  float *out_slots;
  int remaining;

  /* Walk attached parents while the "attached" flag stays set. */
  if ((out_obj[4] & 1) != 0) {
    while (*(int *)(out_obj + 0xcc) != -1) {
      out_obj =
          (char *)object_get_and_verify_type(*(int *)(out_obj + 0xcc), -1);
      if ((out_obj[4] & 1) == 0)
        break;
    }
  }

  out_slots = (float *)(out_obj + 0xd4);
  fn_ids = (int16_t *)(tag_data + 0x330);
  remaining = 4;
  do {
    int16_t function_id = *fn_ids;

    if (function_id != 0) {
      float value = 0.0f;
      if ((unsigned)((int)function_id - 1) <= 15)
        value = weapon_export_eval_function(weapon_handle, weapon_obj, tag_data,
                                            function_id);
      *out_slots = value;
    }

    fn_ids++;
    out_slots++;
    remaining--;
  } while (remaining != 0);
}

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

/* 0xfc550 */
void weapon_build_weapon_interface_state(int weapon_handle, int out_state)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  char *tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);
  char *state = (char *)out_state;
  int16_t magazine_index;

  *(int *)(state + 0) = *(int *)(weapon_obj + 0x1ec);
  *(float *)(state + 4) = *(float *)(weapon_obj + 0x1f0);
  state[8] = (char)(*(uint8_t *)(weapon_obj + 0x1dc) & 1);
  *(int16_t *)(state + 0xa) = *(int16_t *)(tag_data + 0x4f0);

  for (magazine_index = 0; (int)magazine_index < *(int *)(tag_data + 0x4f0);
       magazine_index++) {
    char *mag_entry =
      (char *)weapon_obj + ((int)magazine_index * 3 + 0x96) * 4;
    char *mag_def = (char *)tag_block_get_element(
      (void *)(tag_data + 0x4f0), (int)magazine_index, 0x70);
    char *out_mag = state + 0xc + (int)magazine_index * 8;
    char reloading;

    if (*(int16_t *)mag_entry == 1 || *(int16_t *)mag_entry == 3)
      reloading = 1;
    else
      reloading = 0;

    out_mag[0] = reloading;
    out_mag[1] = (*(int16_t *)mag_entry == 0) ? 1 : 0;
    *(int16_t *)(out_mag + 2) = *(int16_t *)(mag_entry + 8);
    *(int16_t *)(out_mag + 4) = *(int16_t *)(mag_def + 0xa);
    *(int16_t *)(out_mag + 6) = *(int16_t *)(mag_entry + 6);
    *(int16_t *)(state + 0xa + (int)magazine_index * 2 + 8) =
      *(int16_t *)(mag_def + 8);
  }
}

/* 0xfc690 — true if magazine 0 is currently in the reloading state. */
#if defined(__i386__) && defined(__GNUC__)
__attribute__((noinline))
#endif
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

/* 0xfc710 */
int16_t weapon_rotate_zoom_level(int weapon_handle, int16_t zoom_level)
{
  char *tag_data = (char *)tag_get(
    0x77656170,
    *(int *)object_get_and_verify_type(weapon_handle, 4));

  if (weapon_reloading(weapon_handle))
    return zoom_level;

  if (zoom_level >= 0 && zoom_level < *(int16_t *)(tag_data + 0x3da) - 1)
    return (int16_t)(zoom_level + 1);

  return (int16_t)((zoom_level != *(int16_t *)(tag_data + 0x3da) - 1) - 1);
}

/* 0xfc780 */
float weapon_get_zoom_magnification(int weapon_handle, int16_t zoom_level)
{
  char *tag_data = (char *)tag_get(
    0x77656170,
    *(int *)object_get_and_verify_type(weapon_handle, 4));
  float result = 1.0f;
  float min_zoom;
  float max_zoom;
  float t;

  if (zoom_level < 0 || zoom_level >= *(int16_t *)(tag_data + 0x3da))
    return result;

  if (*(int16_t *)(tag_data + 0x3da) > 1) {
    t = (float)zoom_level / (float)(*(int16_t *)(tag_data + 0x3da) - 1);
  } else {
    t = 0.0f;
  }

  min_zoom = (*(float *)(tag_data + 0x3dc) != 0.0f) ? *(float *)(tag_data + 0x3dc)
                                                     : 1.0f;
  max_zoom = (*(float *)(tag_data + 0x3e0) != 0.0f) ? *(float *)(tag_data + 0x3e0)
                                                     : 1.0f;

  result = FUN_000fbcf0(max_zoom / min_zoom, t) * min_zoom;

  if ((*(uint32_t *)&result & 0x7f800000u) == 0x7f800000u) {
    display_assert(0, "c:\\halo\\SOURCE\\items\\weapons.c", 0x5a2, 1);
    system_exit(-1);
  }
  if (result <= 0.0f) {
    display_assert(0, "c:\\halo\\SOURCE\\items\\weapons.c", 0x5a3, 1);
    system_exit(-1);
  }

  return result;
}

/* 0xfc8e0 */
float weapon_get_field_of_view(int weapon_handle, float base_fov,
                               int16_t zoom_level)
{
  float mag = weapon_get_zoom_magnification(weapon_handle, zoom_level);

  if (mag == 1.0f)
    return base_fov;
  if (base_fov / mag >= *(float *)0x28af00)
    return base_fov;
  if (base_fov / mag <= *(float *)0x28aefc)
    return base_fov;
  return base_fov / mag;
}

/* 0xfc930 */
char weapon_prevents_melee_attack(int weapon_handle)
{
  char *tag_data;
  char trigger_state;

  if (weapon_handle == -1)
    return 1;

  tag_data = (char *)tag_get(
    0x77656170,
    *(int *)object_get_and_verify_type(weapon_handle, 4));

  trigger_state = *(char *)((char *)object_get_and_verify_type(weapon_handle, 4) +
                            0x211);
  if (trigger_state == 2 || trigger_state == 3)
    return 1;

  return (char)((*(uint32_t *)(tag_data + 0x308) >> 9) & 1);
}

/* 0xfcbd0 */
void FUN_000fcbd0(int16_t magazine_index, int weapon_handle)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  int16_t *magazine =
    (int16_t *)FUN_000fb370((void *)weapon_obj, magazine_index);
  int16_t state = magazine[0];

  if (state != 0 && state != 2)
    return;

  weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  if (*(char *)(weapon_obj + 0x211) != 0 || *(char *)(weapon_obj + 0x235) != 0 ||
      *(char *)(weapon_obj + 0x1e8) != 0)
    return;

  {
    char *tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);
    char *mag_def = (char *)tag_block_get_element(
      (void *)(tag_data + 0x4f0), (int)magazine_index, 0x70);

    weapon_set_animation_state(weapon_handle, 0, (int16_t)(magazine_index + 3));
    weapon_start_effect(*(int *)(mag_def + 0x54), 0.0f, 0.0f, weapon_handle);
    magazine[0] = 3;
    magazine[1] =
      (int16_t)(int)(*(float *)(mag_def + 0x1c) * *(float *)0x253394);
  }
}

/* 0xfcc90 */
void FUN_000fcc90(int weapon_handle, int16_t magazine_index)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  int16_t *magazine =
    (int16_t *)FUN_000fb370((void *)weapon_obj, magazine_index);

  tag_get(0x77656170, *(int *)weapon_obj);
  tag_block_get_element(
    (char *)tag_get(0x77656170,
                    *(int *)object_get_and_verify_type(weapon_handle, 4)) +
      0x4f0,
    (int)magazine_index, 0x70);

  magazine[0] = 0;
  magazine[1] = 0;
}

/* 0xfcd10 — begin a charged-trigger fire (state 3) and notify FP weapons. */
#if defined(__i386__) && defined(__GNUC__)
__attribute__((noinline))
#endif
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
  frame = (int16_t)(int)(*(float *)(trig_def + 0x4c) * *(float *)0x253394);

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

/* 0xfcdd0 — clear a weapon trigger's charge/state after definition lookup. */
#if defined(__i386__) && defined(__GNUC__)
__attribute__((noinline))
#endif
void FUN_000fcdd0(int16_t trigger_index, int weapon_handle)
{
  char *weapon_obj;
  char *trigger_entry;
  int trigger_idx;

  weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  FUN_000fb320(weapon_obj, trigger_index);
  tag_block_get_element(
      (char *)tag_get(0x77656170, *(int *)weapon_obj) + 0x4fc,
      (int)trigger_index, 0x114);

  weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  if (trigger_index < 0 || trigger_index >= 2) {
    display_assert((char *)0x0028ae40, (char *)0x0028ad48, 0xa11, 1);
    system_exit(-1);
  }

  trigger_idx = (int)trigger_index;
  trigger_entry = (char *)weapon_obj + trigger_idx * 36 + 0x210;
  trigger_entry[1] = 0;
  *(int16_t *)(trigger_entry + 2) = 0;
}

/* 0xfce60 — force a weapon trigger into overheated/empty recovery state. */
#if defined(__i386__) && defined(__GNUC__)
__attribute__((noinline))
#endif
void FUN_000fce60(int weapon_handle, int16_t trigger_index)
{
  char *weapon_obj;
  int idx;

  weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  if ((int16_t)trigger_index < 0 || (int16_t)trigger_index >= 2) {
    display_assert((char *)0x0028ae40, (char *)0x0028ad48, 0xa11, 1);
    system_exit(-1);
  }

  idx = (int)(int16_t)trigger_index;
  weapon_obj[idx * 36 + 0x211] = 7;
  *(int16_t *)(weapon_obj + idx * 36 + 0x212) = (int16_t)-1;
}

/* 0xfcec0 */
void FUN_000fcec0(int param_a, int weapon_handle, int16_t trigger_index)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  char *trigger_entry = weapon_get_trigger_entry(weapon_obj, trigger_index);

  tag_get(0x77656170, *(int *)weapon_obj);
  tag_block_get_element(
    (char *)tag_get(0x77656170, *(int *)weapon_obj) + 0x4fc,
    (int)trigger_index, 0x114);

  trigger_entry[0] = 0;
  FUN_000fcdd0((int)trigger_index, weapon_handle);
}

/* 0xfd0b0 */
void FUN_000fd0b0(int16_t angle_index, float *out_x, float *out_y,
                    int16_t param_3, float scale, char flag)
{
  float angle;

  if ((flag & 1) == 0) {
    angle = (float)(angle_index >> 1) - *(float *)0x253398;
    if ((angle_index & 1) == 0)
      angle = -angle;
  } else if (angle_index == 0) {
    angle = 0.0f;
  } else if ((angle_index & 1) != 0) {
    angle = (float)((angle_index - 1) >> 1);
  } else {
    angle = (float)(-(angle_index >> 1));
  }

  angle *= scale;

  if (param_3 == 1) {
    float sin_a;
    float cos_a;
    sin_a = xbox_sinf(angle);
    cos_a = xbox_cosf(angle);
    rotate_vector3d_by_sincos(out_x, out_y, sin_a, cos_a);
  }
}

/* 0xfd150 */
void FUN_000fd150(int weapon_handle)
{
  char anim_state =
    *(char *)((char *)object_get_and_verify_type(weapon_handle, 4) + 0x1e8);

  if (anim_state >= 7 && anim_state <= 8)
    return;
  if (anim_state == 10)
    return;

  weapon_set_animation_state(weapon_handle, 1, 0);
}

/* 0xfd510 */
void weapon_stop_reload(int weapon_handle)
{
  weapon_reset_state(weapon_handle);
}

/* 0xfd520 */
void FUN_000fd520(int param_a, int weapon_handle, int16_t trigger_index)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);

  weapon_get_trigger_entry(weapon_obj, trigger_index);
  tag_get(0x77656170, *(int *)weapon_obj);
  tag_block_get_element(
    (char *)tag_get(0x77656170, *(int *)weapon_obj) + 0x4fc,
    (int)trigger_index, 0x114);

  *(int *)(weapon_obj + 0x200) = -1;
  FUN_000fcec0(param_a, weapon_handle, trigger_index);
}

/* 0xfd570 — fire projectile(s) from a weapon trigger. */
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

