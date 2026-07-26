/* --- weapons.obj unset drafts (batch 2026-07-25) --- */

float FUN_001d9e70(float base, float exponent);
void actor_aim_projectile(float *origin, float *direction, int unit_handle);

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

/* 0xfb010 */
float weapon_compute_movement_penalty(int weapon_handle, char aiming,
                                      char param_3)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  char *tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);
  float result;

  if (aiming)
    result = *(float *)(tag_data + 0x400);
  else
    result = *(float *)(tag_data + 0x404);

  switch ((int)*(int16_t *)(tag_data + 0x3fc)) {
  case 1:
  case 2:
    if (*(int16_t *)(weapon_obj + 0x258) != 1 &&
        *(int16_t *)(weapon_obj + 0x264) != 1 &&
        param_3 == 0) {
      return 0.0f;
    }
    break;
  default:
    break;
  }

  return result;
}

/* 0xfb320 */
char *FUN_000fb320(void *weapon_obj, int16_t trigger_index)
{
  return weapon_get_trigger_entry(weapon_obj, trigger_index);
}

/* 0xfb510 — trigger charge fraction remaining */
float FUN_000fb510(int weapon_handle, int16_t trigger_index)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  char *trigger_entry = weapon_get_trigger_entry(weapon_obj, trigger_index);
  char *tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);
  char *trig_def = (char *)tag_block_get_element((void *)(tag_data + 0x4fc),
                                                 (int)trigger_index, 0x114);
  char state = trigger_entry[1];

  if (state == 2)
    return 1.0f;
  if (state == 3) {
    float period = *(float *)(trig_def + 0x48);
    if (period == 0.0f)
      return 0.0f;
    return 1.0f - (float)*(int16_t *)(trigger_entry + 2) *
                        *(float *)0x2546a4 / period;
  }
  return 0.0f;
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

/* 0xfb690 */
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

/* 0xfb880 */
void weapon_trigger_release_charge(int16_t charge_counter, int weapon_handle,
                                   char state, int16_t trigger_index)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  char *trigger_entry;

  if (trigger_index < 0 || trigger_index >= 2) {
    display_assert(0, "c:\\halo\\SOURCE\\items\\weapons.c", 0xa11, 1);
    system_exit(-1);
  }
  if ((int16_t)state < 0 || (int16_t)state >= 9) {
    display_assert(0, "c:\\halo\\SOURCE\\items\\weapons.c", 0xa12, 1);
    system_exit(-1);
  }

  trigger_entry = weapon_get_trigger_entry(weapon_obj, trigger_index);
  trigger_entry[1] = state;
  *(int16_t *)(trigger_entry + 2) = charge_counter;
}

/* 0xfb910 */
void FUN_000fb910(int weapon_handle, int16_t trigger_index, char flag)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  char *tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);
  char *trigger_entry = weapon_get_trigger_entry(weapon_obj, trigger_index);
  char *trig_def = (char *)tag_block_get_element((void *)(tag_data + 0x4fc),
                                                 (int)trigger_index, 0x114);

  if (*(float *)(trig_def + 0xa4) != 0.0f) {
    if ((*(int *)trig_def & 0x80) != 0) {
      if (flag == 0)
        *(float *)(trigger_entry + 0x14) = 1.0f;
    } else if (flag == 0) {
      *(float *)(trigger_entry + 0x14) = 1.0f;
    }
  }
}

/* 0xfb990 */
void FUN_000fb990(int weapon_handle)
{
  char anim_state =
    *(char *)((char *)object_get_and_verify_type(weapon_handle, 4) + 0x1e8);

  if (anim_state == 3)
    FUN_000fb910(weapon_handle, 0, 1);
  else if (anim_state == 4)
    FUN_000fb910(weapon_handle, 1, 1);
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

/* 0xfbd10 */
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
    char *mag_def = (char *)tag_block_get_element((void *)(tag_data + 0x4f0),
                                                  (int)magazine_index, 0x70);
    char *mag_entry = (char *)weapon_obj + ((int)magazine_index * 3 + 0x96) * 4;
    int16_t initial_total = *(int16_t *)(mag_def + 6);
    int16_t max_loaded = *(int16_t *)(mag_def + 0xa);
    int16_t loaded = initial_total;

    if (loaded > max_loaded)
      loaded = max_loaded;

    *(int16_t *)(mag_entry + 8) = loaded;
    *(int16_t *)(mag_entry + 6) = initial_total - loaded;
  }

  for (trigger_index = 0; (int)trigger_index < *(int *)(tag_data + 0x4fc);
       trigger_index++) {
    char *trigger_entry =
      weapon_get_trigger_entry(weapon_obj, trigger_index);
    tag_block_get_element((void *)(tag_data + 0x4fc), (int)trigger_index,
                          0x114);
    trigger_entry[0] = 0x7f;
    *(int *)(trigger_entry + 0x20) = -1;
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

static float weapon_export_eval_function(int weapon_handle, char *weapon_obj,
                                         char *tag_data, int16_t function_id)
{
  float value = 0.0f;
  int16_t trigger_index;
  int16_t magazine_index;

  switch (function_id) {
  case 1:
  case 7:
    value = 1.0f;
    break;
  case 2:
    value = *(float *)(weapon_obj + 0x1ec);
    break;
  case 3:
  case 4:
    magazine_index = (int16_t)(function_id - 2);
    if ((int)magazine_index < *(int *)(tag_data + 0x4f0)) {
      char *mag_def = (char *)tag_block_get_element(
        (void *)(tag_data + 0x4f0), (int)magazine_index, 0x70);
      int16_t loaded = *(int16_t *)((char *)weapon_obj +
                                    ((int)magazine_index * 3 + 0x96) * 4 + 8);
      if (*(int16_t *)(mag_def + 0xa) != 0)
        value = (float)loaded / (float) * (int16_t *)(mag_def + 0xa);
    }
    break;
  case 5:
  case 6:
    trigger_index = (int16_t)(function_id - 4);
    if ((int)trigger_index < *(int *)(tag_data + 0x4fc))
      value = *(float *)(weapon_get_trigger_entry(weapon_obj, trigger_index) +
                         0x10);
    break;
  case 8:
  case 9:
    trigger_index = (int16_t)(function_id - 7);
    if ((int)trigger_index < *(int *)(tag_data + 0x4fc))
      value = *(float *)(weapon_get_trigger_entry(weapon_obj, trigger_index) +
                         0x14);
    break;
  case 10:
    if ((*(uint8_t *)(weapon_obj + 0x1dc) & 1) != 0 &&
        *(float *)(tag_data + 0x34c) != 1.0f)
      value = (*(float *)(weapon_obj + 0x1ec) - *(float *)(tag_data + 0x34c)) /
              (1.0f - *(float *)(tag_data + 0x34c));
    break;
  case 11:
  case 12:
    trigger_index = (int16_t)(function_id - 10);
    value = FUN_000fb510(weapon_handle, trigger_index);
    break;
  case 13: {
    int i;
    value = 0.0f;
    for (i = 0; i < *(int *)(tag_data + 0x4fc); i++) {
      char *trig_def = (char *)tag_block_get_element(
        (void *)(tag_data + 0x4fc), i, 0x114);
      char *trigger_entry = weapon_get_trigger_entry(weapon_obj, (int16_t)i);
      float candidate = 0.0f;

      if (*(float *)(trig_def + 0x48) != 0.0f) {
        candidate = FUN_000fb510(weapon_handle, (int16_t)i) *
                    *(float *)(trig_def + 0x54);
        if (candidate > value)
          value = candidate;
      }
      if (trigger_entry[1] == 3) {
        candidate = (1.0f - *(float *)(trig_def + 0x54)) *
                      *(float *)(weapon_obj + 0x1f4) +
                    *(float *)(trig_def + 0x54);
        if (candidate > value)
          value = candidate;
      }
      if (value > *(float *)(trigger_entry + 0x18))
        *(float *)(trigger_entry + 0x18) = value;
      else
        value = *(float *)(trigger_entry + 0x18);
    }
    if (*(float *)(tag_data + 0x360) * *(float *)(weapon_obj + 0x1ec) > value)
      value = *(float *)(tag_data + 0x360) * *(float *)(weapon_obj + 0x1ec);
    break;
  }
  case 14:
    value = *(float *)(weapon_obj + 0x1f0);
    break;
  case 15:
    value = (float) * (int *)(weapon_obj + 0x1f8);
    break;
  case 16:
    trigger_index = (int16_t)(function_id - 15);
    if ((int)trigger_index < *(int *)(tag_data + 0x4fc)) {
      value = *(float *)(weapon_get_trigger_entry(weapon_obj, trigger_index) +
                         0x10);
      if (game_time_get() - *(int *)(weapon_obj + 0x278) <= 1)
        value = 0.0f;
    }
    break;
  default:
    break;
  }

  return value;
}

/* 0xfbf00 */
void weapon_export_function_values(int weapon_handle)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  char *tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);
  char *weapon_root = weapon_obj;
  int slot;

  while ((weapon_obj[4] & 1) != 0 && *(int *)(weapon_obj + 0xcc) != -1) {
    weapon_obj =
      (char *)object_get_and_verify_type(*(int *)(weapon_obj + 0xcc), -1);
    if ((weapon_obj[4] & 1) == 0)
      break;
  }

  for (slot = 0; slot < 4; slot++) {
    int16_t function_id = *(int16_t *)(tag_data + 0x330 + slot * 2);
    float *out = (float *)(weapon_root + 0xd4 + slot * 4);

    if (function_id == 0)
      continue;
    if ((int)function_id - 1 > 15)
      continue;

    *out = weapon_export_eval_function(weapon_handle, weapon_root, tag_data,
                                     function_id);
  }
}

/* 0xfc4b0 */
void weapon_owner_update(int weapon_handle)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  int16_t param_2 = 0;
  int function_type = 0;
  float value;

  *(int16_t *)(weapon_obj + 0x1e0) = param_2;
  value = transition_function_evaluate((int16_t)function_type, (float)param_2);
  *(float *)(weapon_obj + 0x1e4) = value;

  if ((*(uint32_t *)&value & 0x7f800000u) == 0x7f800000u) {
    display_assert(csprintf((char *)0x5ab100, "%s: %f",
                            "weapon_owner_update", (double)value),
                   "c:\\halo\\SOURCE\\items\\weapons.c", 0x4af, 1);
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

/* 0xfc690 */
char weapon_reloading(int weapon_handle)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  char *tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);

  if (*(int *)(tag_data + 0x4f0) > 0) {
    if (*(int *)(tag_data + 0x4f0) <= 0) {
      display_assert(0, "c:\\halo\\SOURCE\\items\\weapons.c", 0x672, 1);
      system_exit(-1);
    }
    if (*(int16_t *)(weapon_obj + 0x258) == 1)
      return 1;
  }
  return 0;
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

/* 0xfcd10 */
void FUN_000fcd10(int trigger_index, int weapon_handle)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  char *tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);
  char *trig_def = (char *)tag_block_get_element((void *)(tag_data + 0x4fc),
                                                 trigger_index, 0x114);
  char *trigger_entry = weapon_get_trigger_entry(weapon_obj, (int16_t)trigger_index);
  int16_t frame;

  if (trigger_index < 0 || trigger_index >= 2) {
    display_assert(0, "c:\\halo\\SOURCE\\items\\weapons.c", 0xa11, 1);
    system_exit(-1);
  }

  frame = (int16_t)(int)(*(float *)(trig_def + 0x4c) * *(float *)0x253394);
  trigger_entry[1] = 3;
  *(int16_t *)(trigger_entry + 2) = frame;
  weapon_set_animation_state(weapon_handle, 1, (int16_t)(trigger_index + 7));
  first_person_weapon_message_from_weapon(weapon_handle, 0xe);
}

/* 0xfcdd0 */
void FUN_000fcdd0(int trigger_index, int weapon_handle)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  char *trigger_entry;

  weapon_get_trigger_entry(weapon_obj, (int16_t)trigger_index);
  tag_get(0x77656170, *(int *)weapon_obj);
  tag_block_get_element(
    (char *)tag_get(0x77656170, *(int *)weapon_obj) + 0x4fc, trigger_index,
    0x114);

  if (trigger_index < 0 || trigger_index >= 2) {
    display_assert(0, "c:\\halo\\SOURCE\\items\\weapons.c", 0xa11, 1);
    system_exit(-1);
  }

  weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  trigger_entry = weapon_get_trigger_entry(weapon_obj, (int16_t)trigger_index);
  trigger_entry[1] = 0;
  *(int16_t *)(trigger_entry + 2) = 0;
}

/* 0xfce60 */
void FUN_000fce60(int weapon_handle, int16_t trigger_index)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  char *trigger_entry;

  if (trigger_index < 0 || trigger_index >= 2) {
    display_assert(0, "c:\\halo\\SOURCE\\items\\weapons.c", 0xa11, 1);
    system_exit(-1);
  }

  trigger_entry = weapon_get_trigger_entry(weapon_obj, trigger_index);
  trigger_entry[1] = 7;
  *(int16_t *)(trigger_entry + 2) = (int16_t)-1;
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

/* 0xfd570 — fire projectile from weapon trigger (large) */
void FUN_000fd570(int weapon_handle, int16_t trigger_index)
{
  char *weapon_obj = (char *)object_get_and_verify_type(weapon_handle, 4);
  char *trigger_entry = weapon_get_trigger_entry(weapon_obj, trigger_index);
  char *tag_data = (char *)tag_get(0x77656170, *(int *)weapon_obj);
  char *trig_def = (char *)tag_block_get_element((void *)(tag_data + 0x4fc),
                                                 (int)trigger_index, 0x114);
  int unit_handle = -1;
  int parent_handle = -1;
  int marker_string_ids[2] = {0x267238, 0x28af04};
  void *marker_name = (void *)marker_string_ids[trigger_index];
  int16_t marker_count;
  char marker_buf[0x40 * 0x6c];
  int16_t marker_index;
  float origin[3];
  float direction[3];
  float velocity[3];
  int proj_tag;

  if (*(int *)(weapon_obj + 0xcc) != -1 &&
      object_try_and_get_and_verify_type(*(int *)(weapon_obj + 0xcc), 3) != 0)
    unit_handle = *(int *)(weapon_obj + 0xcc);

  parent_handle = weapon_handle;
  {
    char *obj2 = (char *)object_get_and_verify_type(weapon_handle, 4);
    if ((obj2[4] & 1) != 0 && *(int *)(obj2 + 0xcc) != -1)
      parent_handle = *(int *)(obj2 + 0xcc);
  }

  marker_count = object_get_markers_by_string_id(
    parent_handle, marker_name, marker_buf, 0x40);
  if ((trig_def[0] & 0x20) == 0)
    marker_count = 1;
  if (marker_count <= 0)
    return;

  for (marker_index = 0; marker_index < marker_count; marker_index++) {
    float *marker_pos = (float *)(marker_buf + marker_index * 0x6c);
    float *marker_fwd = marker_pos + 3;
    float *marker_up = marker_pos + 6;

    origin[0] = marker_pos[0];
    origin[1] = marker_pos[1];
    origin[2] = marker_pos[2];
    direction[0] = marker_fwd[0];
    direction[1] = marker_fwd[1];
    direction[2] = marker_fwd[2];
    velocity[0] = marker_up[0];
    velocity[1] = marker_up[1];
    velocity[2] = marker_up[2];

    if (unit_handle != -1 &&
        (trig_def[0] & 8) == 0 &&
        object_try_and_get_and_verify_type(unit_handle, 3) != 0 &&
        (*(uint8_t *)((char *)object_try_and_get_and_verify_type(unit_handle, 3) +
                      0xb6) &
          4) == 0) {
      char use_forward = 1;
      char adjust_origin = 1;
      unit_adjust_projectile_ray(unit_handle, origin, direction, velocity,
                                 adjust_origin, use_forward);
      if (normalize3d(velocity) == 0.0f) {
        float *world_up = *(float **)0x31fc40;
        velocity[0] = world_up[0];
        velocity[1] = world_up[1];
        velocity[2] = world_up[2];
      }
    } else if (unit_handle != -1) {
      actor_aim_projectile(origin, direction, unit_handle);
    }

    proj_tag = *(int *)(trig_def + 0xa0);
    if (proj_tag == -1)
      continue;

    if (*(int16_t *)(weapon_obj + 0x20c) > 0 && trigger_index == 0) {
      int16_t spread = *(int16_t *)(trig_def + 0x6e);
      if (*(int16_t *)(tag_data + 0x32c) == 4)
        spread = (int16_t)(spread * 2);
      *(int16_t *)(weapon_obj + 0x20c) = 0;
    }

    if (*(int16_t *)(trig_def + 0x6e) <= 0)
      continue;

    (void)trigger_entry;
    (void)proj_tag;
    (void)origin;
    (void)direction;
    (void)velocity;
  }
}

