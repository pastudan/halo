/*
 * vehicle_get_estimated_position (0x1b5df0) — predict vehicle contact point.
 *
 * For vehicle types that support ground contact estimation (types 0, 1, 4, 6),
 * casts a ray downward from above the vehicle's current position to find the
 * BSP surface beneath it. The estimated position is:
 *   out[i] = dir_vec[i] + fwd_vec_doubled[i] * ray_t
 * where dir_vec = object_pos + up_vec * 0.4 (start above vehicle) and
 * fwd_vec_doubled = fwd_vec * 2 (ray direction/scale).
 *
 * For types 2, 3, 5 (and types >6): returns -1 immediately.
 * Returns result_buf[2] (EAX on success path, opaque hit info) or -1.
 * Callers only check != -1 to know whether the position was estimated.
 *
 * Confirmed: SUB ESP,0x434 — large stack frame.
 * Confirmed: PUSH 0x2, PUSH ESI -> object_get_and_verify_type(handle, 2).
 * Confirmed: MOV EAX,[EAX] -> obj->tag_index (uint32 at offset 0).
 * Confirmed: PUSH EAX, PUSH 0x76656869 -> tag_get('vehi', tag_index).
 * Confirmed: MOVSX EAX,word ptr [EDI+0x2f4] ->
 * (int16_t)vehicle_tag->type_field. Confirmed: CMP EAX,0x6; JA -> default
 * return -1 for types > 6. Confirmed: switch byte table at 0x1b5f18: types
 * 0,1,4,6 -> case body; 2,3,5 -> default. Confirmed: CALL 0x18e3f0
 * (global_collision_bsp_get) with no args. Confirmed: LEA EDX,[EBP-0xc]; PUSH
 * EDX; PUSH ESI -> object_get_world_position(handle, &adj_pos). Confirmed: MOV
 * EAX,[0x31fc44] -> up_vec_ptr = *(float**)0x31fc44 (global_up_vector_ptr).
 * Confirmed: FMUL float[0x253524] -> 0.4f (constant at 0x253524 = 0x3ECCCCCD).
 * Confirmed: adj_pos[i] = up_vec[i] * 0.4 + world_pos[i] (FSTP to
 * EBP-0xc,-0x8,-0x4). Confirmed: MOV EAX,[0x31fc50] -> fwd_vec_ptr =
 * *(float**)0x31fc50 (global_forward_vector_ptr). Confirmed: FADD ST0,ST0 ->
 * fwd_vec[i] * 2; FSTP to EBP-0x18,-0x14,-0x10. Confirmed: PUSH
 * EAX(result_buf), PUSH 0x7f7fffff(FLT_MAX), PUSH ECX(&fwd_doubled), PUSH
 * EDX(&adj_pos), PUSH 0, PUSH 0, PUSH EDI(bsp), PUSH 1 ->
 * collision_bsp_test_vector. Confirmed: TEST AL,AL; JZ -> if ray misses, fall
 * to default return -1. Confirmed: MOV EAX,[EBP-0x42c] -> result_buf[2] loaded
 * as return value. Confirmed: FMUL [EBP-0x434] -> multiply by result_buf[0]
 * (ray t param). Confirmed: out_pos[i] = fwd_doubled[i] * result_buf[0] +
 * adj_pos[i].
 */
int vehicle_get_estimated_position(int vehicle_handle, vector3_t *out_position)
{
  void *bsp;
  float adj_pos[3]; /* object_pos + up_vec * 0.4, at EBP-0xc */
  float fwd_doubled[3]; /* fwd_vec * 2, at EBP-0x18 */
  float result_buf[0x10d]; /* 0x434/4 floats; ray hit result buffer, at
                              EBP-0x434; only [0] and [2] used */
  int default_ret;

  object_data_t *obj =
    (object_data_t *)object_get_and_verify_type(vehicle_handle, 2);
  void *vehicle_tag = tag_get(0x76656869, *(uint32_t *)obj);
  default_ret = -1;

  /* First call: store current position into out_position (fills in initial
   * value). */
  object_get_world_position(vehicle_handle, out_position);

  /* Switch on vehicle type at tag+0x2f4. */
  int16_t vtype = *(int16_t *)((char *)vehicle_tag + 0x2f4);
  switch (vtype) {
  case 0:
  case 1:
  case 4:
  case 6:
    break;
  default:
    return default_ret;
  }

  /* Get BSP for ray cast. */
  bsp = global_collision_bsp_get();

  /* Get vehicle world position into adj_pos. */
  object_get_world_position(vehicle_handle, (vector3_t *)adj_pos);

  /* Compute adjusted start: pos + up_vec * 0.4 */
  {
    float *up = *(float **)0x31fc44;
    adj_pos[0] = up[0] * 0.4f + adj_pos[0];
    adj_pos[1] = up[1] * 0.4f + adj_pos[1];
    adj_pos[2] = up[2] * 0.4f + adj_pos[2];
  }

  /* Compute direction vector: fwd_vec * 2 */
  {
    float *fwd = *(float **)0x31fc50;
    fwd_doubled[0] = fwd[0] + fwd[0];
    fwd_doubled[1] = fwd[1] + fwd[1];
    fwd_doubled[2] = fwd[2] + fwd[2];
  }

  /* Cast ray. result_buf[0] = t, result_buf[2] = hit object (returned as EAX).
   */
  if (!((char (*)(int, void *, int16_t, int, float *, float *, float,
                  float *))0x149480)(1, bsp, 0, 0, adj_pos, fwd_doubled,
                                     3.4028235e+38f, result_buf)) {
    return default_ret;
  }

  /* Estimated position: adj_pos + fwd_doubled * t */
  out_position->x = fwd_doubled[0] * result_buf[0] + adj_pos[0];
  out_position->y = fwd_doubled[1] * result_buf[0] + adj_pos[1];
  out_position->z = fwd_doubled[2] * result_buf[0] + adj_pos[2];

  /* Return result_buf[2] as EAX (success indicator; caller checks != -1). */
  return *(int *)&result_buf[2];
}

/*
 * vehicle_moving_near_any_player (0x1b7ee0)
 *
 * Scans all local players. For each local player whose unit is on foot (not
 * currently inside a vehicle, checked via object_data+0xcc == NONE), collects
 * up to MAXIMUM_NUMBER_OF_LOCAL_PLAYERS unit handles and their bounding-sphere
 * centres. Then iterates every vehicle object in the world. For each vehicle,
 * checks each on-foot player:
 *   1. The player's unit is not already sitting inside this vehicle
 *      (object_data[unit]+0xcc != vehicle_datum_handle).
 *   2. Squared distance between vehicle position (+0x50) and the cached
 *      player bounding-sphere centre is < 100.0 (within 10 world units).
 *   3. Squared velocity magnitude (+0x18) is >= ~1/900 (speed >= ~1/30 u/tick).
 * Returns true if any qualifying vehicle is found.
 *
 * Called from game_safe_to_save (0xa7530) to block saving while a moving
 * vehicle is close to a player on foot.
 */

#include "../../common.h"

/* Squared proximity threshold: 10.0^2 = 100.0 world units. */
#define VEHICLE_NEAR_PLAYER_DIST_SQ 100.0f
/* Squared velocity threshold: (1/30)^2 = 1/900. Vehicle must exceed this to
 * be considered "moving". Value from binary at 0x25620c. */
#define VEHICLE_MIN_SPEED_SQ 0.001111111138f

bool vehicle_moving_near_any_player(void)
{
  /* Object iterator buffer: 0x10-byte struct identical in layout to
   * data_iter_t. object_iterator_next writes the current datum handle at
   * byte offset 0x08 (iter_buf[2] as an int array). */
  int iter_buf[4];
  int unit_handles[4]; /* handles of on-foot player units */
  float player_pos[12]; /* 3-float bounding-sphere centre per player */
  float radius_scratch; /* radius out-param, not used here */
  int16_t lpi; /* current local_player_index */
  int16_t n; /* count of on-foot player units collected */
  int16_t i;
  int player_handle;
  char *player;
  int unit_handle;
  void *unit_obj;
  void *veh_obj;
  int vehicle_datum_handle;
  float dx, dy, dz;
  float vx, vy, vz;
  char found; /* 1 = no vehicle found yet, 0 = found; matches local_5 */

  n = 0;
  found = 1;

  /* Phase 1: collect on-foot local player units and their positions.
   * local_player_get_next(-1) returns the first valid local_player_index. */
  lpi = ((int16_t(*)(int16_t))0xba4c0)((int16_t)-1);
  if (lpi == (int16_t)-1)
    goto done;

  /* Push ESI before inner loop (matches disasm 001b7f07: PUSH ESI). */
  do {
    /* First call: validate player index. */
    player_handle = ((int (*)(int16_t))0xba3c0)(lpi);
    if (player_handle != -1) {
      /* Second call: get handle for datum_get (matches disasm 001b7f16). */
      player_handle = ((int (*)(int16_t))0xba3c0)(lpi);
      player = (char *)((void *(*)(void *, int))0x119320)(*(void **)0x5aa6d4,
                                                          player_handle);
      unit_handle = *(int *)(player + 0x34);
      if (unit_handle != -1) {
        /* object_get_and_verify_type(handle, 3): accepts biped or vehicle. */
        unit_obj = ((void *(*)(int, int))0x13d680)(unit_handle, 3);
        /* +0xcc = parent_object_index; NONE (-1) means unit is on foot. */
        if (*(int *)((char *)unit_obj + 0xcc) == -1) {
          unit_handles[n] = unit_handle;
          /* object_get_bounding_sphere: writes centre to &player_pos[n*3],
           * radius to &radius_scratch. Centre is at object_data+0x50. */
          ((void (*)(int, float *, float *))0x1aae0)(
            unit_handle, &player_pos[n * 3], &radius_scratch);
          n++;
        }
      }
    }
    lpi = ((int16_t(*)(int16_t))0xba4c0)(lpi);
  } while (lpi != (int16_t)-1);

  if (n == 0)
    goto done;

  /* Phase 2: iterate all vehicle objects (type_mask=2 = bit 1 = vehicle). */
  object_iterator_new(iter_buf, 2, 0);

  while ((veh_obj = object_iterator_next(iter_buf)) != NULL) {
    /* iter_buf[2] holds the datum handle of the current vehicle object,
     * written by object_iterator_next at offset 0x08 in the iter buffer. */
    vehicle_datum_handle = iter_buf[2];

    i = 0;
    if (n <= 0)
      continue;

    do {
      unit_obj = ((void *(*)(int, int))0x13d680)(unit_handles[i], 3);
      /* Skip player whose unit is already inside this vehicle. */
      if (*(int *)((char *)unit_obj + 0xcc) == vehicle_datum_handle) {
        i++;
        continue;
      }

      /* Squared distance: vehicle pos (+0x50) vs player bounding centre. */
      dx = *(float *)((char *)veh_obj + 0x50) - player_pos[i * 3];
      dy = *(float *)((char *)veh_obj + 0x54) - player_pos[i * 3 + 1];
      dz = *(float *)((char *)veh_obj + 0x58) - player_pos[i * 3 + 2];
      if (dx * dx + dy * dy + dz * dz >= VEHICLE_NEAR_PLAYER_DIST_SQ) {
        i++;
        continue;
      }

      /* Squared velocity: vehicle velocity (+0x18) must exceed threshold. */
      vx = *(float *)((char *)veh_obj + 0x18);
      vy = *(float *)((char *)veh_obj + 0x1c);
      vz = *(float *)((char *)veh_obj + 0x20);
      if (vx * vx + vy * vy + vz * vz >= VEHICLE_MIN_SPEED_SQ) {
        found = 0;
        goto done;
      }
      i++;
    } while (i < n);
  }

done:
  return found == 0;
}
/* --- vehicles.obj batch drafts (2026-07-26) --- */

/* FUN_001b4dc0 (0x1b4dc0) — Unit damage aftermath: stun counters, animation
 * impulses, scoring hooks, AI notifications, and death handling. */
void FUN_001b4dc0(int handle, void *damage_data, unsigned int flags,
                  float body_vitality, float shield_vitality, int param_6,
                  int param_7)
{
  char *unit;
  char *unit_tag;
  char *dd;
  char *jpt_ext;
  char flags_bit0;
  char feign_death;
  char lethal_from_jpt;
  float total_damage;
  float impulse_mag;
  float impulse_dir[3];
  char has_impulse;
  char ping_damage;
  char ground_damage;
  char air_damage;
  const char *weapon_name_a;
  const char *weapon_name_b;
  char *path;
  int16_t dialog_idx;

  (void)param_6;
  (void)param_7;

  unit = (char *)object_get_and_verify_type(handle, 3);
  unit_tag = (char *)tag_get(0x756e6974, *(int *)unit);
  dd = (char *)damage_data;
  jpt_ext = (char *)tag_get(0x6a707421, *(int *)dd) + 0x1c4;
  flags_bit0 = (char)(flags & 1);
  feign_death = 0;
  total_damage = body_vitality + shield_vitality;

  if (*(char *)0x5054f9 != 0 && *(int *)(unit + 0x1c8) != -1) {
    const char *default_name = (const char *)0x0025b724;
    weapon_name_a = default_name;
    weapon_name_b = default_name;
    if (*(int *)(dd + 0xc) != -1) {
      char *att_obj =
          (char *)object_get_and_verify_type(*(int *)(dd + 0xc), -1);
      char *att_obje = (char *)tag_get(0x6f626a65, *(int *)att_obj);
      path = strrchr(att_obje + 0x2c, '\\');
      if (path != 0)
        weapon_name_a = path + 1;
    }
    if (*(int *)dd != -1) {
      path = strrchr((char *)tag_get_name(*(int *)dd), '\\');
      if (path != 0)
        weapon_name_b = path + 1;
    }
    console_printf(0, (char *)0x002b7cac, *(unsigned short *)(unit + 0x1c8),
                   weapon_name_a, weapon_name_b, body_vitality, shield_vitality);
  }

  if (*(float *)(unit + 0xa4) + *(float *)(unit + 0xa8) <= 0.0f) {
    *(int16_t *)(unit + 0x3b4) = *(int16_t *)(jpt_ext + 2);
    *(int16_t *)(unit + 0x3b6) = 0x2d;
    if (*(float *)(unit + 0x3b8) > *(float *)(jpt_ext + 0x1c))
      *(float *)(unit + 0x3b8) = *(float *)(jpt_ext + 0x1c);
    if (*(int *)(dd + 0xc) != -1)
      *(int *)(unit + 0x3bc) = *(int *)(dd + 0xc);
  }

  if ((*(unsigned int *)(unit + 0x1b4) & 0x10) != 0) {
    *(float *)(unit + 0x32c) -= *(float *)(jpt_ext + 0x1c);
    if (*(float *)(unit + 0x32c) < 0.0f)
      *(float *)(unit + 0x32c) = 0.0f;
  }

  lethal_from_jpt = (char)(*(float *)(jpt_ext + 0x30) > 0.0001f);

  if (flags_bit0 == 0 && (*(unsigned int *)(unit + 0x1b4) & 0x20) != 0 &&
      *(float *)(unit_tag + 0x22c) <= 0.0f &&
      *(float *)(unit_tag + 0x230) <= 0.0f &&
      *(float *)(unit + 0x90) <= 0.0f &&
      *(float *)(unit + 0xa8) <= *(float *)(unit_tag + 0x22c)) {
    float roll = FUN_000121e0(0.0f, 1.0f) + *(float *)(unit_tag + 0x230);
    roll *= *(float *)0x253394;
    if (roll > 1.0f)
      roll = 1.0f;
    dialog_idx = (int16_t)(int)roll;
    if (dialog_idx <= 0) {
      display_assert((char *)0x002b68c0, (char *)0x002b7ac8, 4740, 1);
      system_exit(-1);
    }
    *(int16_t *)(unit + 0x3d0) = dialog_idx;
    feign_death = 1;
  }

  if ((dd[4] & 0x10) == 0 &&
      (flags_bit0 != 0 || feign_death != 0 ||
       (*(unsigned char *)(unit + 0xb6) & 4) != 0) &&
      (*(unsigned int *)(unit + 0x1b4) & 0x800000) == 0 &&
      (jpt_ext[4] & 0x10) == 0) {
    impulse_dir[0] = *(float *)(dd + 0x34);
    impulse_dir[1] = *(float *)(dd + 0x38);
    impulse_dir[2] = *(float *)(dd + 0x3c);
    impulse_mag = 0.0f;
    has_impulse = 0;
    if (magnitude3d(impulse_dir) > 0.0f) {
      float vel[3];
      float vel_mag;
      vel[0] = *(float *)(unit + 0x24);
      vel[1] = *(float *)(unit + 0x28);
      vel[2] = *(float *)(unit + 0x2c);
      vel_mag = magnitude3d(vel);
      if (vel_mag > 0.0f) {
        impulse_mag =
            vel[0] * impulse_dir[0] + vel[1] * impulse_dir[1] +
            vel[2] * impulse_dir[2];
        has_impulse = 1;
      }
    }
    ping_damage = 0;
    if ((*(signed char *)(unit_tag + 0x17c) < 0) && (dd[4] & 4) == 0)
      ping_damage = 1;
    if (*(unsigned char *)(unit + 0x23b) > 0)
      ping_damage = 1;
    ground_damage = (char)((flags & 0x8a) != 0);
    air_damage = lethal_from_jpt;
    FUN_001b1400(handle, flags_bit0, 0, air_damage, ground_damage, ping_damage,
                 impulse_mag, -1,
                 has_impulse ? (int)(uintptr_t)impulse_dir : 0);
  }

  if (*(int *)(dd + 8) != -1 && *(int *)(unit + 0x1c8) != -1)
    game_engine_player_damaged_player(*(int *)(dd + 8), *(int *)(unit + 0x1c8),
                                      (flags >> 4) & 1);

  if (*(int *)(dd + 8) != -1 || *(int *)(dd + 0xc) != -1) {
    unit_record_damage(handle, total_damage, *(int16_t *)(jpt_ext + 2),
                       flags_bit0, *(int *)(dd + 8),
                       *(int16_t *)(dd + 0x10), *(int *)(dd + 0xc));
  }

  if ((dd[4] & 0x10) == 0 &&
      (flags_bit0 != 0 || shield_vitality <= 0.0f || body_vitality <= 0.0f)) {
    char combo = (char)(feign_death | flags_bit0);
    FUN_001a71c0(handle, (int *)dd, (flags >> 6) & 1, combo, shield_vitality);
  }

  if (shield_vitality <= 0.0f && body_vitality <= 0.0f)
    unit_reset_weapon_state(handle);

  if (*(int16_t *)(unit + 0x64) == 0) {
    if (flags_bit0 != 0) {
      ai_handle_death(handle, *(int *)(dd + 0xc),
                      *(int16_t *)(jpt_ext + 2));
    } else if ((*(unsigned char *)(unit + 0xb6) & 4) == 0) {
      ai_handle_damage(handle, *(int *)(dd + 0xc), *(int16_t *)(jpt_ext + 2),
                       total_damage, (int)(uintptr_t)(dd + 0x34), 0);
    }
  }

  if (*(int *)(unit + 0x1c8) != -1 && *(float *)(jpt_ext + 0x20) > 0.0f &&
      (game_engine_running() || *(char *)0x5054f8 != 0)) {
    char *globals = (char *)game_globals_get();
    char *player_settings =
        (char *)tag_block_get_element(globals + 0x170, 0, 0xf4);
    float shake_x = *(float *)(jpt_ext + 0x20) * *(float *)(dd + 0x40);
    float shake_y = *(float *)(jpt_ext + 0x24) * *(float *)(dd + 0x40);
    if (shake_x < 0.0f)
      shake_x = 0.0f;
    if (shake_y < 0.0f)
      shake_y = 0.0f;
    else if (shake_y > 1.0f)
      shake_y = 1.0f;
    if (shake_x <= *(float *)(unit + 0x3d4))
      *(float *)(unit + 0x3d4) += shake_x;
    else
      *(float *)(unit + 0x3d4) = shake_x;
    {
      int16_t low = (int16_t)(int)(*(float *)(jpt_ext + 0x28) *
                                   *(float *)0x253394);
      int16_t high =
          (int16_t)(int)(*(float *)(player_settings + 0x8c) *
                         *(float *)0x253394);
      int16_t dur = (int16_t)(int)(*(float *)(player_settings + 0x90) *
                                   *(float *)0x253394);
      if (*(int16_t *)(unit + 0x3d8) < low)
        *(int16_t *)(unit + 0x3d8) = low;
      *(int16_t *)(unit + 0x3d8) = (int16_t)(*(int16_t *)(unit + 0x3d8) + dur);
      if (*(int16_t *)(unit + 0x3d8) > high)
        *(int16_t *)(unit + 0x3d8) = high;
    }
    (void)shake_y;
  }

  if (flags_bit0 != 0 || feign_death != 0)
    unit_died(handle, (char)(feign_death | flags_bit0));
}

/* 0x1b5400 — Exit seated units whose seat name matches a substring. */
int FUN_001b5400(int unit_handle, int seat_name_substr)
{
  object_iter_t iter;
  char *unit_tag;
  char *unit_obj;
  char seat_name[0x110];
  int16_t exit_count = 0;
  const char *needle = (const char *)(uintptr_t)seat_name_substr;
  char match_any;

  if (unit_handle == -1)
    return 0;

  unit_obj = (char *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (char *)tag_get('tinu', *(int *)unit_obj);
  match_any = (needle == 0 || csstrlen(needle) == 0);

  object_iterator_new(&iter, 3, 0);
  while ((unit_obj = (char *)object_iterator_next(&iter)) != 0) {
    int16_t seat_index;
    char *seat_entry;

    if (*(int *)(unit_obj + 0xcc) != unit_handle)
      continue;

    seat_index = *(int16_t *)(unit_obj + 0x2a0);
    seat_entry = (char *)tag_block_get_element(unit_tag + 0x2e4, (int)seat_index,
                                               0x11c);
    csstrcpy(seat_name, seat_entry + 4);
    csstr_tolower(seat_name);

    if (!match_any && crt_strstr(seat_name, needle) == 0)
      continue;

    if (!unit_try_and_exit_seat(iter.last_handle))
      continue;

    exit_count++;
  }

  return (int)exit_count;
}

/* 0x1b5500 — Exit vehicle seat when unit is seated with a valid seat index. */
void FUN_001b5500(int unit_handle)
{
  char *unit;

  if (unit_handle == -1)
    return;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  if (*(int *)(unit + 0xcc) == -1)
    return;
  if (*(int16_t *)(unit + 0x2a0) == -1)
    return;

  unit_try_and_exit_seat(unit_handle);
}

/* 0x1b5580 — Place vehicle and apply collision damage from placement. */
void vehicle_causes_collision_damage(int vehicle_handle, void *placement)
{
  char *place = (char *)placement;

  unit_place(vehicle_handle, place + 0x48);
  FUN_0013d870(vehicle_handle, place + 0x28);
}

/* 0x1b55c0 — Returns true when the vehicle tag has hover physics enabled. */
char vehicle_hover(int vehicle_handle)
{
  char *vehicle_obj = (char *)object_get_and_verify_type(vehicle_handle, 2);
  char *vehicle_tag = (char *)tag_get('ihev', *(int *)vehicle_obj);

  return (char)((*(unsigned int *)(vehicle_tag + 0x2f0) >> 7) & 1);
}

/* 0x1b5610 — Toggle vehicle world-position refresh flag (+0x424 bit 1). */
void FUN_001b5610(int vehicle_handle, char flag)
{
  char *vehicle;

  if (vehicle_handle == -1)
    return;

  vehicle = (char *)object_get_and_verify_type(vehicle_handle, 2);
  if (flag) {
    object_get_world_position(vehicle_handle, (vector3_t *)(vehicle + 0x454));
    vehicle[0x424] |= 2;
  } else {
    vehicle[0x424] &= 0xfd;
  }
}

/* 0x1b5680 — True when the vehicle up-axis dot threshold is exceeded. */
char vehicle_is_flipped(int vehicle_handle)
{
  char *vehicle_obj = (char *)object_get_and_verify_type(vehicle_handle, 2);

  if (*(float *)(vehicle_obj + 0x38) <= *(float *)0x2549d4)
    return 0;
  return 1;
}

/* 0x1b56b0 — Update vehicle wheel-compression counters from physics state. */
void FUN_001b56b0(int vehicle_handle, void *physics_state)
{
  char *vehicle;
  char *vehicle_tag;
  char *physics_tag;
  int wheel_count;
  int wheel_index;
  unsigned char wheel_flags;

  vehicle = (char *)object_get_and_verify_type(vehicle_handle, 2);
  vehicle_tag = (char *)tag_get('ihev', *(int *)vehicle);
  physics_tag = (char *)tag_get('syhp', *(int *)(vehicle_tag + 0x8c));

  if ((unsigned char)vehicle[0x428] != 0xff)
    vehicle[0x428]++;

  wheel_count = *(int *)(physics_tag + 0x74);
  for (wheel_index = 0; wheel_index < wheel_count; wheel_index++) {
    char *wheel_state = (char *)physics_state + wheel_index * 0x130;

    wheel_flags = (unsigned char)*(int *)wheel_state;
    if ((wheel_flags & 2) != 0) {
      if ((unsigned char)vehicle[0x42b] != 0xff)
        vehicle[0x42b]++;
      vehicle[0x428] = 0;
      return;
    }
    if ((wheel_flags & 0x10) != 0)
      vehicle[0x428] = 0;
  }

  vehicle[0x42b] = 0;
}

/* 0x1b5750 — pack float w + three int components into quaternion storage */
void set_real_quaternion(float *quat, float w, int x, int y, int z)
{
  *quat = w;
  *(int *)((char *)quat + 4) = x;
  *(int *)((char *)quat + 8) = y;
  *(int *)((char *)quat + 0xc) = z;
}

/* 0x1b5770 */
void vehicle_reset(void)
{
  object_get_and_verify_type(0, 0);
  csmemset((void *)0, 0, 0);
}

/* 0x1b5820 */
void vehicle_new(void)
{
  object_get_and_verify_type(0, 0);
  tag_get('ihev', 0);
  vehicle_reset();
}

/* 0x1b5890 — Preprocess vehicle antenna node orientations from rtna tag. */
static float vehicle_clamp_unit_float(float value)
{
  if (!(value > 0.0f))
    return 0.0f;
  if (value > 1.0f)
    return 1.0f;
  return value;
}

static void vehicle_preprocess_apply_frame(char *vehicle_tag, char *node_block,
                                           int node_index, void *node_output,
                                           float frame)
{
  int16_t *indices;
  char *animation;

  if (*(int *)(node_block + 0x5c) <= node_index)
    return;

  indices = *(int16_t **)(node_block + 0x60);
  if (indices[node_index] == (int16_t)-1)
    return;

  animation = (char *)tag_block_get_element(vehicle_tag + 0x74,
                                            (int)indices[node_index], 0xb4);
  FUN_00122690(animation, frame, node_output);
}

void vehicle_preprocess_node_orientations(int vehicle_handle, void *node_output)
{
  char *vehicle;
  char *vehicle_tag;
  char *antenna_tag;
  char *node_block;
  int16_t *node_indices;
  int node_count;
  int wheel_count;
  int wheel_index;
  float frame;
  float steer;

  vehicle = (char *)object_get_and_verify_type(vehicle_handle, 2);
  vehicle_tag = (char *)tag_get('ihev', *(int *)vehicle);

  if (*(int *)(vehicle_tag + 0x44) == -1)
    return;

  antenna_tag = (char *)tag_get('rtna', *(int *)(vehicle_tag + 0x44));
  node_block = (char *)tag_block_get_element(antenna_tag + 0x24, 0, 0x74);
  if (node_block == 0)
    return;

  node_count = *(int *)(node_block + 0x5c);
  node_indices = *(int16_t **)(node_block + 0x60);

  if (node_count > 0 && node_indices[0] != (int16_t)-1) {
    char *animation =
      (char *)tag_block_get_element(vehicle_tag + 0x74, (int)node_indices[0],
                                    0xb4);
    FUN_00122e50((int)animation, (float *)(vehicle + 0x434), 0.0f, 0.0f,
                 (int)node_output);
  }

  if (node_count > 1 && node_indices[1] != (int16_t)-1) {
    char *animation =
      (char *)tag_block_get_element(vehicle_tag + 0x74, (int)node_indices[1],
                                    0xb4);
    steer = triple_product3d((float *)(vehicle + 0x18),
                             (float *)(vehicle + 0x24),
                             (float *)(vehicle + 0x30));
    steer /= *(float *)(vehicle_tag + 0x2f8);
    steer += 1.0f;
    steer *= *(float *)0x253398;
    frame = vehicle_clamp_unit_float(steer);
    frame *= (float)(*(int16_t *)(animation + 0x22) - 1);
    vehicle_preprocess_apply_frame(vehicle_tag, node_block, 1, node_output,
                                 frame);
  }

  if (node_count > 2 && node_indices[2] != (int16_t)-1) {
    char *animation =
      (char *)tag_block_get_element(vehicle_tag + 0x74, (int)node_indices[2],
                                    0xb4);
    if (*(float *)(vehicle + 0x42c) <= 0.0f) {
      frame = 0.0f;
    } else {
      frame = *(float *)(vehicle + 0x42c) / *(float *)(vehicle_tag + 0x2fc);
      frame = *(float *)0x253398 - frame;
    }
    frame = vehicle_clamp_unit_float(frame);
    frame *= (float)(*(int16_t *)(animation + 0x22) - 1);
    vehicle_preprocess_apply_frame(vehicle_tag, node_block, 2, node_output,
                                 frame);
  }

  if (node_count > 3 && node_indices[3] != (int16_t)-1) {
    char *animation =
      (char *)tag_block_get_element(vehicle_tag + 0x74, (int)node_indices[3],
                                    0xb4);
    steer = *(float *)(vehicle + 0x20) * *(float *)(vehicle + 0x2c) +
            *(float *)(vehicle + 0x1c) * *(float *)(vehicle + 0x28) +
            *(float *)(vehicle + 0x18) * *(float *)(vehicle + 0x24);
    if (!(steer > 0.0f))
      frame = 0.0f;
    else {
      if (steer < 0.0f)
        steer = -steer;
      frame = vehicle_clamp_unit_float(steer / *(float *)(vehicle_tag + 0x2f8));
    }
    frame *= (float)(*(int16_t *)(animation + 0x22) - 1);
    vehicle_preprocess_apply_frame(vehicle_tag, node_block, 3, node_output,
                                 frame);
  }

  if (node_count > 4 && node_indices[4] != (int16_t)-1)
    (void)tag_block_get_element(vehicle_tag + 0x74, (int)node_indices[4], 0xb4);

  if (node_count > 5 && node_indices[5] != (int16_t)-1) {
    char *animation =
      (char *)tag_block_get_element(vehicle_tag + 0x74, (int)node_indices[5],
                                    0xb4);
    if (*(float *)(vehicle_tag + 0x310) > 0.0f)
      frame = *(float *)(vehicle + 0x438) / *(float *)(vehicle_tag + 0x310);
    else
      frame = 0.0f;
    frame *= (float)*(int16_t *)(animation + 0x22);
    vehicle_preprocess_apply_frame(vehicle_tag, node_block, 5, node_output,
                                 frame);
  }

  wheel_count = *(int *)(node_block + 0x68);
  for (wheel_index = 0; wheel_index < wheel_count; wheel_index++) {
    char *wheel_entry;
    char *wheel_animation;
    int16_t anim_index;

    wheel_entry = (char *)tag_block_get_element(node_block + 0x68, wheel_index,
                                                0x14);
    anim_index = *(int16_t *)(wheel_entry + 2);
    if (anim_index == (int16_t)-1)
      continue;

    wheel_animation = (char *)tag_block_get_element(vehicle_tag + 0x74,
                                                    (int)anim_index, 0xb4);
    if ((unsigned char)vehicle[0x44c + wheel_index] == 0xff)
      frame = 1.0f;
    else
      frame = (float)(unsigned char)vehicle[0x44c + wheel_index] *
              *(float *)0x261518;
    frame *= (float)(*(int16_t *)(wheel_animation + 0x22) - 1);
    FUN_00122690(wheel_animation, frame, node_output);
  }
}

/* 0x1b5c90 */
void vehicle_accelerate(int handle, float *velocity)
{
  int eax = 0;

  object_get_and_verify_type(handle, 2);
  tag_get('ihev', *(int *)(eax));
  /* cmp eax, -1 -> je 0x1b5d87 */
  tag_get('syhp', 0);
  normalize3d((float *)0);
  /* test (char)eax, 0x41 -> jne 0x1b5d7c */

  (void)eax;
}

/* 0x1b5d90 */
void vehicle_render_debug(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  object_get_and_verify_type(0, 2);
  tag_get('ihev', *(int *)(eax));
  /* cmp eax, -1 -> je 0x1b5de8 */
  tag_get('syhp', 0);
  /* relift: relift: mov (char)ecx, byte ptr [0x5054f4] */
  /* test (char)ecx, (char)ecx -> je 0x1b5de8 */
  /* test eax, eax -> jle 0x1b5de8 */
  /* cmp edx, eax -> jl 0x1b5de0 */

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x1b5f20 */
void FUN_001b5f20(void)
{
  int eax = 0;
  int esi = 0;

  /* relift: relift: fcomp dword ptr [0x253f44] */
  /* test (char)eax, 0x41 -> jne 0x1b5fd5 */
  FUN_000a57b0((float *)0, 0.0f);
  FUN_000a57b0((float *)(uintptr_t)esi, 0);

  (void)eax;
  (void)esi;
}

/* 0x1b5ff0 */
void FUN_001b5ff0(void)
{
  object_get_and_verify_type(0, 0);
  tag_get('ihev', 0);
  tag_get('syhp', 0);
  FUN_001daf7e();
  FUN_001daf7e();
  FUN_00154270(0, 0, 0, 0, 0);
  FUN_00154270(0, 0, 0, 0, 0);
}

/* 0x1b6140 */
void FUN_001b6140(void)
{
  object_get_and_verify_type(0, 0);
  tag_get('ihev', 0);
  tag_get('syhp', 0);
  FUN_001daf7e();
  FUN_00154270(0, 0, 0, 0, 0);
  FUN_00154270(0, 0, 0, 0, 0);
}

/* FUN_001b6250 (0x1b6250) — flying-vehicle wheel/contact setup (physics type 3).
 * wheel_state arrives in ESI from the caller. */
void FUN_001b6250(int vehicle_handle, void *physics_buffer,
                  void *wheel_state /* @<esi> */)
{
  char *veh;
  char *vehi;
  char *phys;
  char *ws;
  float angle;
  float force[3];
  float local_mat[12];

  veh = (char *)object_get_and_verify_type(vehicle_handle, 2);
  vehi = (char *)tag_get(0x76656869, *(int *)veh);
  phys = (char *)tag_get(0x70687973, *(int *)(vehi + 0x8c));
  ws = (char *)wheel_state;
  if (*(int *)(phys + 0x68) != 3)
    return;

  angle = *(float *)(veh + 0x434) * *(float *)0x253398;
  if (angle > 1.0f)
    angle = 1.0f;
  angle = 1.0f - angle;

  *(float *)(ws + 4) = *(float *)(veh + 0x42c);
  *(int *)(ws + 0xc) = 0x3b449ba6;
  *(int *)(ws + 0x1c) = 0;
  *(float *)(ws + 0x24) = sinf(angle);
  *(float *)(ws + 0x28) = cosf(angle);
  *(int *)(ws + 0x6c) = 0x3b449ba6;
  *(int *)(ws + 0x7c) = 0;
  *(int *)(ws + 0x80) = 0;
  *(int *)(ws + 0x84) = 0;
  *(int *)(ws + 0x88) = 0x3f800000;
  *(int *)(ws + 0xcc) = 0x3ba3d70a;
  *(int *)(ws + 0xdc) = 0;
  *(int *)(ws + 0xe0) = 0;
  *(int *)(ws + 0xe4) = 0;
  *(int *)(ws + 0xe8) = 0x3f800000;

  force[0] = 0.0f;
  force[1] = 0.0f;
  force[2] = 0.0f;
  if (magnitude3d((float *)(veh + 0x18)) > 0.0f) {
    float forward[3];
    float ground;
    float scale;
    forward[0] = *(float *)(veh + 0x24);
    forward[1] = *(float *)(veh + 0x28);
    forward[2] = *(float *)(veh + 0x2c);
    if (magnitude3d(forward) > 0.0f) {
      ground = *(float *)(veh + 0x3c) * forward[0] +
               *(float *)(veh + 0x40) * forward[1] +
               *(float *)(veh + 0x44) * forward[2];
      scale = *(float *)(phys + 0x50);
      if (scale > *(float *)0x2b7ce4)
        scale = *(float *)0x2b7ce4;
      else if (scale < *(float *)0x2b7ce0)
        scale = *(float *)0x2b7ce0;
      force[0] = scale * forward[0];
      force[1] = scale * forward[1];
      force[2] = scale * forward[2];
      (void)ground;
    }
  }

  csmemset(local_mat, 0, sizeof(local_mat));
  FUN_00154270(vehicle_handle, ws, physics_buffer, force, local_mat);
}

/* FUN_001b6560 (0x1b6560) — wheel suspension force for physics type 2. */
void FUN_001b6560(int vehicle_handle, void *wheel_buffer, void *scratch_buffer)
{
  char *veh;
  char *vehi;
  char *phys;
  float local_force[3];
  float side[3];
  float speed;
  float new_suspension;

  veh = (char *)object_get_and_verify_type(vehicle_handle, 2);
  vehi = (char *)tag_get(0x76656869, *(int *)veh);
  phys = (char *)tag_get(0x70687973, *(int *)(vehi + 0x8c));
  if (*(int *)(phys + 0x68) != 2)
    return;

  if (*(float *)(veh + 0x42c) <= 0.0f)
    FUN_001b5f20();
  else
    FUN_001b5f20();

  local_force[0] = 0.0f;
  local_force[1] = 0.0f;
  local_force[2] = 0.0f;
  side[0] = 0.0f;
  side[1] = 0.0f;
  side[2] = 0.0f;

  speed = magnitude3d((float *)(veh + 0x3c));
  new_suspension = *(float *)(veh + 0x448);
  if (speed <= new_suspension) {
    float delta = (1.0f - new_suspension);
    delta = delta * delta * *(float *)0x2549d4;
    if (delta < *(float *)0x25bb10)
      delta = *(float *)0x25bb10;
    else if (delta > *(float *)0x2533e8)
      delta = *(float *)0x2533e8;
    new_suspension = speed - *(float *)(veh + 0x448);
    if (new_suspension > delta)
      new_suspension = delta;
  } else {
    new_suspension = new_suspension * new_suspension * *(float *)0x2533e8;
    if (new_suspension > *(float *)0x29d9ac)
      new_suspension = *(float *)0x29d9ac;
    new_suspension = -new_suspension;
    speed = speed - *(float *)(veh + 0x448);
    if (speed < new_suspension)
      speed = new_suspension;
    new_suspension = speed;
  }
  *(float *)(veh + 0x448) = new_suspension + *(float *)(veh + 0x448);

  *(float *)((char *)wheel_buffer + 0x18) = *(float *)(veh + 0x2e8);
  csmemcpy((char *)wheel_buffer + 0x1c, (char *)0x31fc5c, 0x10);
  *(float *)((char *)wheel_buffer + 0x78) = *(float *)(veh + 0x2e8);
  csmemcpy((char *)wheel_buffer + 0x7c, (char *)0x31fc5c, 0x10);

  FUN_00154270(vehicle_handle, wheel_buffer, scratch_buffer, local_force, side);
}

/* 0x1b69a0 */
void FUN_001b69a0(void)
{
  int eax = 0;

  object_get_and_verify_type(0, 2);
  tag_get('ihev', *(int *)(eax));
  tag_get('syhp', 0);
  /* cmp eax, 2 -> jne 0x1b6c7f */
  normalize3d((float *)0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  FUN_0010c690((void *)0, (void *)0, 0.0f, 0.0f);
  matrix_from_forward_and_up((void *)0, (float *)((char *)eax + 0x24), (float *)((char *)eax + 0x30));
  matrix_from_forward_and_up((void *)0, (void *)0, (void *)0);
  matrix_inverse((void *)0, (void *)0);
  matrix4x3_multiply((void *)0, (void *)0, (void *)0);
  FUN_00109fc0((void *)0, (void *)0);
  FUN_0010caf0((void *)0, (void *)0, (void *)0);
  FUN_00154270(0, 0, 0, 0, 0);
  FUN_00154270(0, 0, 0, 0, 0);

  (void)eax;
}

/* 0x1b6ca0 */
void FUN_001b6ca0(void)
{
  int eax = 0;
  int edi = 0;

  object_get_and_verify_type(0, 2);
  normalize3d((void *)0);
  FUN_001092d0((void *)0, (void *)0, 0.0f, 0.0f);
  matrix_scale_transform_vector((void *)0, (float *)((char *)eax + 0x24), (void *)0);
  matrix_scale_transform_vector((void *)0, (float *)((char *)eax + 0x30), (void *)0);
  /* relift: cmp word ptr [edi + 0x426], 0 -> jne 0x1b6df2 */
  object_set_position(0, (void *)0, (void *)0, (void *)0);

  (void)eax;
  (void)edi;
}

/* 0x1b6e20 */
void FUN_001b6e20(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int ebp = 0;
  int local_14 = 0;

  object_get_and_verify_type(0, 2);
  tag_get('ihev', *(int *)(eax));
  /* cmp eax, -1 -> je 0x1b7010 */
  object_get_markers_by_string_id(0, (void *)0x002b7d18, (void *)0, 15);
  object_get_markers_by_string_id(0, (void *)0x002b7d08, (void *)0, 16);
  random_math_get_local_seed_address();
  random_direction3d((void *)0, (float *)0, 0.0f, 0.0f, (float *)0);
  /* relift: cmp (int16_t)ebx, word ptr [ebp - 0x1c] -> jge 0x1b6ee8 */
  FUN_0014df70(0, (float *)0, (float *)0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x1b7000 */
  FUN_0010c8e0((void *)0, (void *)0, (void *)0);
  /* relift: relift: fld dword ptr [0x2533c8] */
  effect_new_unattached_from_markers(0, -1, (float *)0, 3, (void *)0, (void *)0, (void *)0, local_14, local_14, 0.0f, 0.0f, 0.0f);
  /* cmp eax, ecx -> jl 0x1b6eb0 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)ebp;
  (void)local_14;
}

/* 0x1b7020 */
void FUN_001b7020(void)
{
  int eax = 0;
  int ecx = 0;
  int ebp = 0;
  int local_8 = 0;

  object_get_and_verify_type(0, 2);
  tag_get('ihev', *(int *)(eax));
  /* cmp eax, -1 -> je 0x1b729e */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b729e */
  object_get_markers_by_string_id(0, (void *)0x002b7d18, (void *)0, 15);
  random_math_get_local_seed_address();
  random_direction3d((int *)((char *)/* [ebp + eax - 0x7b4] */ + 0x3c), (float *)0, 0.0f, 0.0f, (float *)0);
  FUN_0014df70(97, (float *)((char *)/* [ebp + eax - 0x7b4] */ + 0x60), (void *)0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x1b7289 */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x1b7142 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b7289 */
  FUN_0010c8e0((float *)0, (float *)0, (float *)0);
  FUN_0010c8e0((void *)0, (void *)0, (void *)0);
  effect_new_unattached_from_markers(0, -1, (float *)0, 4, (void *)0, (void *)0, (void *)0, local_8, local_8, 0.0f, 0.0f, 1);
  /* cmp eax, ecx -> jl 0x1b70a2 */

  (void)eax;
  (void)ecx;
  (void)ebp;
  (void)local_8;
}

/* 0x1b72b0 */
void FUN_001b72b0(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int local_4 = 0;

  object_get_and_verify_type(0, 2);
  tag_get('ihev', *(int *)(eax));
  tag_get('syhp', 0);
  game_globals_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* relift: cmp dword ptr [esi + 0x3cc], ecx -> je 0x1b74bf */
  /* relift: relift: fcomp dword ptr [0x255ca0] */
  /* test (char)eax, 0x41 -> jne 0x1b74bf */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 128);
  /* test (char)ecx, 2 -> jne 0x1b73b5 */
  /* relift: cmp esi, dword ptr [edi] -> jl 0x1b7380 */
  damage_data_new((void *)0, 0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x1b7415 */
  object_cause_damage((void *)0, 0, -1, -1, -1, 0);
  /* cmp ecx, -1 -> je 0x1b74bf */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x1b7499 */
  object_impulse_sound_new(0, 0, -1, (float *)(uintptr_t)*(int *)(0x31fc1c), (float *)(uintptr_t)*(int *)(0x31fc3c), local_4);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)local_4;
}

/* 0x1b74d0 */
void FUN_001b74d0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edi = 0;
  int local_18 = 0;
  int local_28 = 0;
  int local_4 = 0;

  object_get_and_verify_type(0, 2);
  tag_get('ihev', *(int *)(eax));
  tag_get('rtna', 0);
  /* test ecx, ecx -> je 0x1b77d8 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 116);
  /* test ebx, ebx -> je 0x1b77cf */
  tag_get('syhp', 0);
  matrix4x3_from_forward_up_position((void *)0, (float *)(uintptr_t)eax, (float *)0, (float *)0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 20);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1b7734 */
  /* cmp eax, ecx -> jge 0x1b7731 */
  /* cmp (int16_t)eax, 0xffff -> je 0x1b7731 */
  tag_block_get_element((void *)(uintptr_t)local_28, 0, 0);
  tag_block_get_element((void *)(uintptr_t)local_18, eax, 128);
  /* cmp (char)eax, 0xff -> jne 0x1b7611 */
  matrix_transform_point((void *)0, (float *)((char *)eax + 0x38), (void *)0);
  matrix_transform_vector((void *)0, (float *)(uintptr_t)eax, (float *)0);
  FUN_0014df70(0, (float *)0, (float *)0, 0, (void *)0);
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b76f5 */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x1b7709 */
  quantize_real_to_byte_lower_bound(0.0f, 0.0f, 0.0f);
  /* relift: cmp edi, dword ptr [ebx] -> jl 0x1b7595 */
  /* cmp edi, -1 -> je 0x1b77cf */
  /* relift: relift: fcomp dword ptr [0x2533e4] */
  /* test (char)eax, 0x41 -> jne 0x1b77cf */
  /* test (char)eax, 0x41 -> jne 0x1b77a3 */
  object_impulse_sound_new(0, 0, -1, (float *)(uintptr_t)*(int *)(0x31fc1c), (float *)(uintptr_t)*(int *)(0x31fc3c), local_4);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edi;
  (void)local_18;
  (void)local_28;
  (void)local_4;
}

/* 0x1b77f0 */
void FUN_001b77f0(void)
{
  int eax = 0;
  int ecx = 0;

  object_get_and_verify_type(eax, 2);
  tag_get('ihev', *(int *)(eax));
  tag_get('syhp', 0);
  /* cmp ecx, -1 -> je 0x1b79b8 */
  tag_block_get_element((void *)0, 0, 0);
  /* test (char)eax, 2 -> je 0x1b79a2 */
  /* relift: relift: fcomp dword ptr [0x25bc08] */
  /* test (char)eax, 0x41 -> jne 0x1b79a2 */
  /* relift: relift: fld dword ptr [0x2533dc] */
  /* test (char)eax, 0x41 -> jne 0x1b7966 */
  FUN_0009f430(0, 0, 0, (void *)0, (void *)0, (void *)0, 0.0f);
  /* cmp eax, ecx -> jl 0x1b7850 */

  (void)eax;
  (void)ecx;
}

/* vehicle_export_function_values (0x1b79c0) — fill vehicle+0xd4 function-value
 * slots from vehi tag indices (4 entries at vehi+0x31c). */
void vehicle_export_function_values(int vehicle_handle)
{
  char *veh;
  char *vehi;
  float *out;
  int16_t *fn_idx;
  int slot;
  float max_fwd;
  float max_back;
  float max_right_a;
  float max_right_b;
  float max_up_a;
  float max_up_b;
  float value;

  veh = (char *)object_get_and_verify_type(vehicle_handle, 2);
  vehi = (char *)tag_get(0x76656869, *(int *)veh);
  max_fwd = fabsf(*(float *)(vehi + 0x2f8));
  max_back = fabsf(*(float *)(vehi + 0x2fc));
  if (max_fwd < max_back)
    max_fwd = max_back;
  max_right_a = fabsf(*(float *)(vehi + 0x330));
  max_right_b = fabsf(*(float *)(vehi + 0x334));
  max_up_a = fabsf(*(float *)(vehi + 0x308));
  max_up_b = fabsf(*(float *)(vehi + 0x30c));

  out = (float *)(veh + 0xd4);
  fn_idx = (int16_t *)(vehi + 0x31c);
  for (slot = 0; slot < 4; slot++) {
    int index;
    float a;
    float b;
    value = 0.0f;
    if (fn_idx[slot] == 0)
      break;
    index = (int)fn_idx[slot] - 1;
    if (index < 0 || index > 0x23) {
      value = 0.0f;
      goto store;
    }
    switch (index + 1) {
    case 1:
      value = fabsf(*(float *)(veh + 0x42c)) / max_fwd;
      break;
    case 2:
      value = *(float *)(veh + 0x42c) / max_fwd;
      if (*(float *)(veh + 0x42c) <= 0.0f)
        value = 0.0f / max_fwd;
      break;
    case 3:
      value = *(float *)(veh + 0x42c) / max_fwd;
      if (*(float *)(veh + 0x42c) > 0.0f)
        value = fabsf(*(float *)(vehi + 0x2fc));
      value = *(float *)(veh + 0x42c) / max_fwd;
      break;
    case 4:
      value = fabsf(*(float *)(veh + 0x42c)) / max_back;
      break;
    case 5:
      value = fabsf(*(float *)(veh + 0x430)) / max_right_a;
      break;
    case 6:
      value = fabsf(*(float *)(veh + 0x430)) / max_right_b;
      break;
    case 7:
      value = fabsf(*(float *)(veh + 0x430)) /
              (max_right_a > max_right_b ? max_right_a : max_right_b);
      break;
    case 8:
      a = fabsf(*(float *)(veh + 0x42c)) / max_fwd;
      b = fabsf(*(float *)(veh + 0x430)) / max_right_a;
      value = a > b ? a : b;
      break;
    case 9:
      value = fabsf(*(float *)(veh + 0x434)) / max_up_a;
      break;
    case 10:
      value = fabsf(*(float *)(veh + 0x434)) / max_up_b;
      break;
    case 11:
      value = fabsf(*(float *)(veh + 0x434)) /
              (max_up_a > max_up_b ? max_up_a : max_up_b);
      break;
    case 12:
      if ((*(unsigned char *)(veh + 0x424) & 4) != 0)
        value = 0.0f;
      else
        value = 1.0f;
      break;
    case 13:
      if ((*(unsigned char *)(veh + 0x424) & 8) != 0)
        value = 0.0f;
      else
        value = 1.0f;
      break;
    case 14:
      value = magnitude3d((float *)(veh + 0x18)) / max_fwd;
      break;
    case 15:
      if ((*(unsigned char *)(veh + 4) & 0x1c) != 0)
        value = magnitude3d((float *)(veh + 0x18)) / max_fwd;
      else
        value = 0.0f;
      break;
    case 16:
      if ((*(unsigned char *)(veh + 4) & 2) != 0)
        value = magnitude3d((float *)(veh + 0x18)) / max_fwd;
      else
        value = 0.0f;
      break;
    case 17:
    case 18:
      value =
          fabsf(*(float *)(veh + 0x20) * *(float *)(veh + 0x2c) +
                *(float *)(veh + 0x1c) * *(float *)(veh + 0x28) +
                *(float *)(veh + 0x18) * *(float *)(veh + 0x24)) /
          max_fwd;
      break;
    case 19:
    case 20:
      value = *(float *)(veh + 0x43c) / *(float *)(vehi + 0x310);
      break;
    case 21:
    case 22:
      value = *(float *)(veh + 0x440) / *(float *)(vehi + 0x310);
      break;
    case 23:
      value = fabsf(*(float *)(veh + 0x42c) - *(float *)(veh + 0x434)) /
              max_fwd;
      break;
    case 24:
      value = fabsf(*(float *)(veh + 0x434) + *(float *)(veh + 0x42c)) /
              max_fwd;
      break;
    case 25:
    case 26:
    case 27:
      value = *(float *)(veh + 0x438) / *(float *)(vehi + 0x310);
      break;
    case 28:
    case 29:
    case 30:
    case 31:
      value = fabsf(*(float *)(veh + 0x42c)) / max_fwd;
      break;
    case 32: {
      float cross[3];
      float tmp[3];
      FUN_0010b8a0((float *)(veh + 0x18), (float *)(veh + 0x24), tmp, cross);
      value = magnitude3d(cross) * *(float *)0x254e6c;
      value *= value;
      break;
    }
    case 33:
      value = *(float *)(veh + 0x448);
      break;
    case 34:
      value = *(float *)(veh + 0x444);
      break;
    case 35:
      value = magnitude3d((float *)(veh + 0x18)) / *(float *)(vehi + 0x2f8);
      value = value * *(float *)(veh + 0x448) - *(float *)0x2533e8;
      value *= *(float *)0x2b7d40;
      break;
    default:
      value = 0.0f;
      break;
    }
  store:
    if (value <= 0.0f)
      value = 0.0f;
    else if (value >= 1.0f)
      value = 1.0f;
    out[slot] = value;
  }
}

/* 0x1b8060 */
char vehicle_stuck(int unit_handle, float *vec)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int local_60 = 0;

  object_get_and_verify_type(unit_handle, 2);
  FUN_001509c0((void *)0, unit_handle);
  /* test (char)eax, (char)eax -> je 0x1b81b6 */
  /* test ecx, ecx -> jle 0x1b81be */
  /* relift: test dword ptr [ebx + 0x478], edx -> je 0x1b8110 */
  tag_block_get_element((void *)(uintptr_t)local_60, 0, 128);
  /* cmp ecx, edx -> jl 0x1b80d0 */
  /* test (int16_t)esi, (int16_t)esi -> jle 0x1b81ad */
  matrix_transform_point((float *)0, (float *)0, (float *)0);
  object_get_world_position(unit_handle, (void *)0);
  normalize3d((float *)0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)local_60;
}

/* 0x1b81d0 — reset vehicle wheel state from object definition */
void FUN_001b81d0(int object_handle, void *wheel_buffer)
{
  char *object;
  char *vehicle_tag;
  char *physics_tag;
  int wheel_stride;

  object = (char *)object_get_and_verify_type(object_handle, 2);
  vehicle_tag = (char *)tag_get('ihev', *(int *)object);
  physics_tag = (char *)tag_get('syhp', *(int *)(vehicle_tag + 0x8c));
  if (*(unsigned short *)(object + 0x424) & 2) {
    wheel_stride = *(int *)(physics_tag + 0x74) * 0x130;
    csmemset(wheel_buffer, 0, wheel_stride);
    FUN_001b6e20();
  }
  (void)physics_tag;
}

/* 0x1b8570 — vehicle physics setup from object definition */
void FUN_001b8570(int object_handle)
{
  char *object;
  char *vehicle_tag;

  object = (char *)object_get_and_verify_type(object_handle, 2);
  vehicle_tag = (char *)tag_get('ihev', *(int *)object);
  (void)tag_get('syhp', *(int *)(vehicle_tag + 0x8c));
  FUN_0018f510(object + 0x48, object + 0xc);
}
