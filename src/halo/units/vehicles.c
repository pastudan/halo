#include "../../x87_math.h"

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
      display_assert((char *)0x002b68c0, (char *)0x002b7ac8, 0x1284, 1);
      system_exit(-1);
    }
    *(unsigned char *)(unit + 0xb6) |= 4;
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



/* FUN_001b5400 (0x1b5400) — readable C lift: exit seats matching name. */
int16_t FUN_001b5400(int unit_handle, int seat_name_substr)
{
  object_iter_t iter;
  char *unit_tag;
  char *unit_obj;
  char seat_name[0x110];
  int16_t exit_count;
  const char *needle;
  char match_any;

  exit_count = 0;
  needle = (const char *)(uintptr_t)seat_name_substr;
  if (unit_handle == -1)
    return 0;

  unit_obj = (char *)object_get_and_verify_type(unit_handle, 3);
  unit_tag = (char *)tag_get(0x756e6974, *(int *)unit_obj); /* 'unit' */
  if (needle != 0 && csstrlen(needle) != 0)
    match_any = 0;
  else
    match_any = 1;

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

    exit_count = (int16_t)(exit_count + 1);
  }

  return exit_count;
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
  char *vehicle_tag = (char *)tag_get(0x76656869, *(int *)vehicle_obj);

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


/* vehicle_is_flipped (0x1b5680) — readable C lift. */
char vehicle_is_flipped(int vehicle_handle)
{
  char *vehicle_obj = (char *)object_get_and_verify_type(vehicle_handle, 2);

  /* XBE: fcomp + test ah,5 / jp -> 0; else 1 when up-Z is below threshold. */
  if (*(float *)(vehicle_obj + 0x38) < *(float *)0x2549d4)
    return 1;
  return 0;
}

/* 0x1b56b0 — Update wheel-compression counters (vehicle@eax, physics@edi). */
void FUN_001b56b0(int vehicle_handle, void *physics_state)
{
  char *vehicle;
  char *vehicle_tag;
  char *physics_tag;
  int wheel_count;
  int wheel_index;
  unsigned char wheel_flags;

  vehicle = (char *)object_get_and_verify_type(vehicle_handle, 2);
  vehicle_tag = (char *)tag_get(0x76656869, *(int *)vehicle); /* 'vehi' */
  physics_tag =
      (char *)tag_get(0x70687973, *(int *)(vehicle_tag + 0x8c)); /* 'phys' */

  if ((unsigned char)vehicle[0x428] != 0xff)
    vehicle[0x428]++;

  wheel_count = *(int *)(physics_tag + 0x74);
  for (wheel_index = 0; wheel_index < wheel_count; wheel_index++) {
    char *wheel_state = (char *)physics_state + wheel_index * 0x130;

    wheel_flags = (unsigned char)*(int *)wheel_state;
    if ((wheel_flags & 2) != 0) {
      vehicle[0x428] = 0;
      if ((unsigned char)vehicle[0x42b] != 0xff)
        vehicle[0x42b]++;
      return;
    }
    if ((wheel_flags & 0x10) != 0)
      vehicle[0x428] = 0;
  }

  vehicle[0x42b] = 0;
}


/* set_real_quaternion (0x1b5750) — readable C lift from XBE leaf. */
void set_real_quaternion(float *quat, float w, int x, int y, int z)
{
  quat[0] = w;
  *(int *)(quat + 1) = x;
  *(int *)(quat + 2) = y;
  *(int *)(quat + 3) = z;
}

/* vehicle_reset (0x1b5770) — readable C lift. */
void vehicle_reset(int vehicle_handle)
{
  char *vehicle;
  vehicle = (char *)object_get_and_verify_type(vehicle_handle, 2);
  *(int16_t *)(vehicle + 0x424) = 0;
  *(int16_t *)(vehicle + 0x426) = 0;
  vehicle[0x428] = 0;
  vehicle[0x429] = 0;
  vehicle[0x42a] = 0;
  vehicle[0x42b] = 0;
  *(int *)(vehicle + 0x42c) = 0;
  *(int *)(vehicle + 0x430) = 0;
  *(int *)(vehicle + 0x434) = 0;
  *(int *)(vehicle + 0x438) = 0;
  *(int *)(vehicle + 0x43c) = 0;
  *(int *)(vehicle + 0x440) = 0;
  *(int *)(vehicle + 0x448) = 0;
  *(int *)(vehicle + 0x444) = 0;
  csmemset(vehicle + 0x44c, 0, 8);
  *(int *)(vehicle + 0x460) = 0;
  *(int *)(vehicle + 0x464) = 0;
  *(int *)(vehicle + 0x468) = 0;
  *(int *)(vehicle + 0x46c) = 0;
  *(int *)(vehicle + 0x470) = 0;
  *(int *)(vehicle + 0x474) = 0;
  *(int *)(vehicle + 0x478) = 0;
}


/* vehicle_new (0x1b5820) — readable C lift. */
char vehicle_new(int vehicle_handle)
{
  char *vehicle;
  char *vehicle_tag;
  int flags;

  vehicle = (char *)object_get_and_verify_type(vehicle_handle, 2);
  vehicle_tag = (char *)tag_get(0x76656869, *(int *)vehicle); /* 'vehi' */
  vehicle_reset(vehicle_handle);
  flags = *(int *)(vehicle + 4);
  if (*(int *)(vehicle_tag + 0x8c) == -1)
    flags |= 0x20;
  else
    flags &= ~0x20;
  *(int *)(vehicle + 4) = flags;
  if (*(int *)(vehicle_tag + 0x8c) != -1)
    *(float *)(vehicle + 0x14) =
        *(float *)(vehicle + 0x14) +
        *(float *)(vehicle_tag + 4) * *(float *)0x253398;
  return 1;
}


/* 0x1b5890 — Preprocess vehicle node orientations from model_animations
 * (antr / 'rtna') tag referenced at vehicle_tag+0x44. */
#if !defined(__clang__)
static float vehicle_clamp_unit_float(float value)
{
  if (!(value > 0.0f))
    return 0.0f;
  if (!(value <= 1.0f))
    return 1.0f;
  return value;
}
#endif


void vehicle_preprocess_node_orientations(int vehicle_handle, void *node_output)
{
  char *vehicle;
  char *vehicle_tag;
  char *animations_tag;
  char *node_block;
  int16_t *node_indices;
  int node_count;
  int wheel_count;
  int wheel_index;
  float frame;
  float steer;

  vehicle = (char *)object_get_and_verify_type(vehicle_handle, 2);
  vehicle_tag = (char *)tag_get(0x76656869, *(int *)vehicle); /* 'vehi' */

  if (*(int *)(vehicle_tag + 0x44) == -1)
    return;

  animations_tag =
      (char *)tag_get(0x616e7472, *(int *)(vehicle_tag + 0x44)); /* 'antr' */
  if (*(int *)(animations_tag + 0x24) == 0)
    return;
  node_block = (char *)tag_block_get_element(animations_tag + 0x24, 0, 0x74);
  if (node_block == 0)
    return;

  node_count = *(int *)(node_block + 0x5c);
  node_indices = *(int16_t **)(node_block + 0x60);

  /* Animation graph lookups use animations_tag+0x74 (not vehicle_tag). */
  if (node_count > 0 && node_indices[0] != (int16_t)-1) {
    char *animation = (char *)tag_block_get_element(
        animations_tag + 0x74, (int)node_indices[0], 0xb4);
    /* blend_params = node_block; direction = vehicle throttle-aim float. */
    FUN_00122e50((int)animation, (float *)node_block,
                 *(float *)(vehicle + 0x434), 0.0f, (int)node_output);
  }

  if (node_count > 1 && node_indices[1] != (int16_t)-1) {
    char *animation = (char *)tag_block_get_element(
        animations_tag + 0x74, (int)node_indices[1], 0xb4);
    steer = triple_product3d((float *)(vehicle + 0x18),
                             (float *)(vehicle + 0x24),
                             (float *)(vehicle + 0x30));
    steer /= *(float *)(vehicle_tag + 0x2f8);
    steer += *(float *)0x2533c8;
    steer *= *(float *)0x253398;
    frame = vehicle_clamp_unit_float(steer);
    frame *= (float)(*(int16_t *)(animation + 0x22) - 1);
    FUN_00122690(animation, frame, node_output);
  }

  if (node_count > 2 && node_indices[2] != (int16_t)-1) {
    char *animation = (char *)tag_block_get_element(
        animations_tag + 0x74, (int)node_indices[2], 0xb4);
    /* XBE: negative path only when velocity < 0 (not <=). */
    if (*(float *)(vehicle + 0x42c) < 0.0f) {
      frame = *(float *)(vehicle + 0x42c) / *(float *)(vehicle_tag + 0x2fc);
      frame *= *(float *)0x253398;
      frame = *(float *)0x253398 - frame;
    } else {
      frame = *(float *)(vehicle + 0x42c) / *(float *)(vehicle_tag + 0x2f8);
      frame += *(float *)0x2533c8;
      frame *= *(float *)0x253398;
    }
    frame *= (float)(*(int16_t *)(animation + 0x22) - 1);
    FUN_00122690(animation, frame, node_output);
  }

  if (node_count > 3 && node_indices[3] != (int16_t)-1) {
    char *animation = (char *)tag_block_get_element(
        animations_tag + 0x74, (int)node_indices[3], 0xb4);
    steer = *(float *)(vehicle + 0x20) * *(float *)(vehicle + 0x2c) +
            *(float *)(vehicle + 0x1c) * *(float *)(vehicle + 0x28) +
            *(float *)(vehicle + 0x18) * *(float *)(vehicle + 0x24);
    frame = vehicle_clamp_unit_float(steer);
    frame /= fabsf(*(float *)(vehicle_tag + 0x2f8));
    frame = vehicle_clamp_unit_float(frame);
    frame *= (float)(*(int16_t *)(animation + 0x22) - 1);
    FUN_00122690(animation, frame, node_output);
  }

  if (node_count > 4 && node_indices[4] != (int16_t)-1)
    (void)tag_block_get_element(animations_tag + 0x74, (int)node_indices[4],
                                0xb4);

  if (node_count > 5 && node_indices[5] != (int16_t)-1) {
    char *animation = (char *)tag_block_get_element(
        animations_tag + 0x74, (int)node_indices[5], 0xb4);
    if (*(float *)(vehicle_tag + 0x310) > 0.0f)
      frame = *(float *)(vehicle + 0x438) / *(float *)(vehicle_tag + 0x310);
    else
      frame = 0.0f;
    frame *= (float)*(int16_t *)(animation + 0x22);
    FUN_00122690(animation, frame, node_output);
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

    wheel_animation = (char *)tag_block_get_element(animations_tag + 0x74,
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



/* 0x1b5c90 — add an impulse to vehicle velocity and clear the grounded bit. */
void vehicle_accelerate(int handle, float *velocity)
{
  char *veh;
  char *vehi;
  float *global_up;
  float lateral[3];
  float len;

  veh = (char *)object_get_and_verify_type(handle, 2);
  vehi = (char *)tag_get(0x76656869, *(int *)veh); /* 'vehi' */
  if (*(int *)(vehi + 0x8c) == -1)
    return;

  (void)tag_get(0x70687973, *(int *)(vehi + 0x8c)); /* 'phys' */

  *(float *)(veh + 0x18) += velocity[0];
  *(float *)(veh + 0x1c) += velocity[1];
  *(float *)(veh + 0x20) += velocity[2];

  global_up = *(float **)0x31fc44;
  /* XBE builds cross(up, velocity) into a temp, then scales by |temp|*k. */
  cross_product3d(global_up, velocity, lateral);
  len = normalize3d(lateral);
  if (len > 0.0f) {
    float scale = len * *(float *)0x256980;
    *(float *)(veh + 0x3c) += lateral[0] * scale;
    *(float *)(veh + 0x40) += lateral[1] * scale;
    *(float *)(veh + 0x44) += lateral[2] * scale;
  }

  *(int *)(veh + 4) &= ~0x20;
}



/* 0x1b5d90 — vehicle_render_debug: empty wheel-count loop when debug flag set. */
void vehicle_render_debug(int vehicle_handle)
{
  char *vehicle;
  char *vehicle_tag;
  int physics_tag_handle;
  char *physics_tag;
  int wheel_count;
  short i;

  vehicle = (char *)object_get_and_verify_type(vehicle_handle, 2);
  vehicle_tag = (char *)tag_get(0x76656869, *(int *)vehicle); /* vehi */
  physics_tag_handle = *(int *)(vehicle_tag + 0x8c);
  if (physics_tag_handle == -1)
    return;
  physics_tag = (char *)tag_get(0x70687973, physics_tag_handle); /* phys */
  if (!*(char *)0x5054f4)
    return;
  wheel_count = *(int *)(physics_tag + 0x74);
  for (i = 0; i < wheel_count; i++) {
  }
}

/* FUN_001b5f20 (0x1b5f20) — Project a delta vector onto a reference axis and
 * clamp its length. Register args: a@<eax>, b@<ecx>, out@<esi>. */
float *FUN_001b5f20(float *a, float *b, float *out, float scale_a, float scale_b)
{
  float dot;
  float ratio;
  float limit;

  out[0] = b[0] - a[0];
  out[1] = b[1] - a[1];
  out[2] = (b[2] - a[2]) + *(float *)0x32512c;

  dot = out[0] * b[0] + out[1] * b[1] + out[2] * b[2];
  if (dot <= 0.0001f) {
    FUN_000a57b0(out, scale_b);
    return out;
  }

  ratio = (out[0] * b[0] + out[1] * b[1] + out[2] * out[2]) / (dot * dot);
  limit = (scale_a - scale_b) * ratio + scale_b;
  FUN_000a57b0(out, limit);
  return out;
}


/* FUN_001b5ff0 (0x1b5ff0) — readable C lift. */
void FUN_001b5ff0(int vehicle_handle, void *physics_buffer, void *wheel_state)
{
  char *veh;
  char *vehi;
  char *phys;
  char *ws;
  float left;
  float right;
  float wrap;
  float max_v;

  veh = (char *)object_get_and_verify_type(vehicle_handle, 2);
  vehi = (char *)tag_get(0x76656869, *(int *)veh);
  phys = (char *)tag_get(0x70687973, *(int *)(vehi + 0x8c));
  ws = (char *)wheel_state;
  max_v = *(float *)(vehi + 0x310);

  left = *(float *)(veh + 0x42c) - *(float *)(veh + 0x434);
  right = *(float *)(veh + 0x434) + *(float *)(veh + 0x42c);

  wrap = left + *(float *)(veh + 0x43c);
  *(float *)(veh + 0x43c) = wrap;
  wrap = (float)x87_fmod(wrap, (double)max_v);
  *(float *)(veh + 0x43c) = wrap;
  if (wrap < *(float *)0x2533c0)
    *(float *)(veh + 0x43c) = wrap + max_v;

  wrap = right + *(float *)(veh + 0x440);
  *(float *)(veh + 0x440) = wrap;
  wrap = (float)x87_fmod(wrap, (double)max_v);
  *(float *)(veh + 0x440) = wrap;
  if (wrap < *(float *)0x2533c0)
    *(float *)(veh + 0x440) = wrap + max_v;

  if (*(int *)(phys + 0x68) == 2) {
    *(float *)(ws + 0) = left;
    *(int *)(ws + 0x1c) = 0;
    *(int *)(ws + 0x20) = 0;
    *(int *)(ws + 0x24) = 0;
    *(int *)(ws + 0x28) = 0x3f800000;
    *(float *)(ws + 0x60) = right;
    *(int *)(ws + 0x7c) = 0;
    *(int *)(ws + 0x80) = 0;
    *(int *)(ws + 0x84) = 0;
    *(int *)(ws + 0x88) = 0x3f800000;
    FUN_00154270(vehicle_handle, ws, physics_buffer, 0, 0);
  } else {
    FUN_00154270(vehicle_handle, 0, physics_buffer, 0, 0);
  }
}

/* FUN_001b6140 (0x1b6140) — readable C lift. */
void FUN_001b6140(int vehicle_handle, void *physics_buffer, void *wheel_state)
{
  char *veh;
  char *vehi;
  char *phys;
  char *ws;
  float throttle;
  float wrap;
  float max_v;
  float angle;

  veh = (char *)object_get_and_verify_type(vehicle_handle, 2);
  vehi = (char *)tag_get(0x76656869, *(int *)veh);
  phys = (char *)tag_get(0x70687973, *(int *)(vehi + 0x8c));
  ws = (char *)wheel_state;
  max_v = *(float *)(vehi + 0x310);

  throttle = *(float *)(veh + 0x42c) + *(float *)(veh + 0x438);
  *(float *)(veh + 0x438) = throttle;
  wrap = (float)x87_fmod(throttle, (double)max_v);
  *(float *)(veh + 0x438) = wrap;
  if (wrap < *(float *)0x2533c0)
    *(float *)(veh + 0x438) = wrap + max_v;

  if (*(int *)(phys + 0x68) == 2) {
    float s;
    float c;
    angle = *(float *)(veh + 0x434) * *(float *)0x253398;
    s = xbox_sinf(angle);
    c = xbox_cosf(angle);
    *(float *)(ws + 0) = *(float *)(veh + 0x42c);
    *(int *)(ws + 0x1c) = 0;
    *(int *)(ws + 0x20) = 0;
    *(float *)(ws + 0x24) = s;
    *(float *)(ws + 0x28) = c;
    *(float *)(ws + 0x60) = *(float *)(veh + 0x42c);
    *(int *)(ws + 0x7c) = 0;
    *(int *)(ws + 0x80) = 0;
    *(float *)(ws + 0x84) = -s;
    *(float *)(ws + 0x88) = c;
    FUN_00154270(vehicle_handle, ws, physics_buffer, 0, 0);
  } else {
    FUN_00154270(vehicle_handle, 0, physics_buffer, 0, 0);
  }
}

/* FUN_001b6250 (0x1b6250) — flying-vehicle wheel/contact setup (physics type 3).
 * wheel_state arrives in ESI from the caller. */
#if defined(__clang__)
static void *(*const b6250_get)(int, int) = object_get_and_verify_type;
static void *(*const b6250_tag)(int, int) = tag_get;
static float (*const b6250_norm)(float *) = normalize3d;
static void (*const b6250_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;
static float (*const b6250_mc510)(float *, float *) = FUN_0010c510;
static void (*const b6250_pphys)(int, void *, void *, float *, float *) = FUN_00154270;

__attribute__((naked, noinline))
void FUN_001b6250(int vehicle_handle __attribute__((unused)), void *physics_buffer __attribute__((unused)), void *wheel_state __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x3c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $2\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x76656869\n\t"
      "call *%[tag]\n\t"
      "movl 0x8c(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x70687973\n\t"
      "call *%[tag]\n\t"
      "movl 0x68(%%eax), %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl $3, %%ecx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jne .LFUN_001b6250_10\n\t"
      "flds 0x20(%%ebx)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "flds 0x18(%%ebx)\n\t"
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
      "fmuls 0x254e04\n\t"
      "fabs\n\t"
      "flds 0x434(%%ebx)\n\t"
      "fmuls 0x253398\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b6250_1\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_001b6250_1:\n\t"
      "fsubrs 0x2533c8\n\t"
      "movl 0x42c(%%ebx), %%edx\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "movl $0x3b449ba6, %%ecx\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "movl %%ecx, 0xc(%%esi)\n\t"
      "xorl %%eax, %%eax\n\t"
      "fld %%st(0)\n\t"
      "movl %%eax, 0x1c(%%esi)\n\t"
      "fsin\n\t"
      "movl %%eax, 0x20(%%esi)\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "leal 0x24(%%ebx), %%edi\n\t"
      "fstps 0x24(%%esi)\n\t"
      "fcos\n\t"
      "fstps 0x28(%%esi)\n\t"
      "movl %%ecx, 0x6c(%%esi)\n\t"
      "movl %%eax, 0x7c(%%esi)\n\t"
      "movl %%eax, 0x80(%%esi)\n\t"
      "movl %%eax, 0x84(%%esi)\n\t"
      "movl $0x3f800000, %%ecx\n\t"
      "movl %%ecx, 0x88(%%esi)\n\t"
      "movl $0x3ba3d70a, 0xcc(%%esi)\n\t"
      "movl %%eax, 0xdc(%%esi)\n\t"
      "movl %%eax, 0xe0(%%esi)\n\t"
      "movl %%eax, 0xe4(%%esi)\n\t"
      "movl %%ecx, 0xe8(%%esi)\n\t"
      "flds 0x2c(%%ebx)\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "fchs\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%edi)\n\t"
      "fadds (%%eax)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "fadds 0x4(%%eax)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "fadds 0x8(%%eax)\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_001b6250_8\n\t"
      "flds 0x34(%%ebx)\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "subl $8, %%esp\n\t"
      "flds 0x4(%%edi)\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "fmuls 0x38(%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds 0x38(%%ebx)\n\t"
      "fmuls (%%edi)\n\t"
      "flds 0x30(%%ebx)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls 0x30(%%ebx)\n\t"
      "flds 0x34(%%ebx)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls 0x18(%%ebx)\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fmuls (%%edi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls 0x18(%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "faddp %%st(1)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls (%%eax)\n\t"
      "faddp %%st(1)\n\t"
      "fmuls 0x255a54\n\t"
      "fld %%st(0)\n\t"
      "fcos\n\t"
      "fstps 0x4(%%esp)\n\t"
      "fsin\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[rots]\n\t"
      "leal 0x30(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[mc510]\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "addl $0x18, %%esp\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b6250_2\n\t"
      "fchs\n\t"
      ".LFUN_001b6250_2:\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls 0x44(%%ebx)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls 0x40(%%ebx)\n\t"
      "faddp %%st(1)\n\t"
      "flds 0x3c(%%ebx)\n\t"
      "fmuls (%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_001b6250_4\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b6250_3\n\t"
      "movl $0xffffffff, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001b6250_5\n\t"
      ".LFUN_001b6250_3:\n\t"
      "movl $1, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001b6250_5\n\t"
      ".LFUN_001b6250_4:\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      ".LFUN_001b6250_5:\n\t"
      "fabs\n\t"
      "fmull 0x2b7ce8\n\t"
      "fsqrt\n\t"
      "fimull -0x4(%%ebp)\n\t"
      "fsubs -0x8(%%ebp)\n\t"
      "fcoms 0x2b7ce4\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b6250_6\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2b7ce4\n\t"
      "jmp .LFUN_001b6250_7\n\t"
      ".LFUN_001b6250_6:\n\t"
      "fcoms 0x2b7ce0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b6250_7\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2b7ce0\n\t"
      ".LFUN_001b6250_7:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "fmuls 0x50(%%eax)\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%edi)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "jmp .LFUN_001b6250_9\n\t"
      ".LFUN_001b6250_8:\n\t"
      "movl $0, -0x24(%%ebp)\n\t"
      "movl $0, -0x20(%%ebp)\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      ".LFUN_001b6250_9:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[pphys]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001b6250_10:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[pphys]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b6250_get), [tag] "m"(b6250_tag), [norm] "m"(b6250_norm), [rots] "m"(b6250_rots), [mc510] "m"(b6250_mc510), [pphys] "m"(b6250_pphys)
      : "memory");
}
#else
#error "FUN_001b6250: clang naked draft required"
#endif

/* FUN_001b6560 (0x1b6560) — wheel suspension force for physics type 2. */
void FUN_001b6560(int vehicle_handle, void *wheel_buffer, void *scratch_buffer)
{
  char *veh;
  char *vehi;
  char *phys;
  float thrust[3];
  float projected[3];
  float basis[9];
  float ground_normal[3];
  float side[3];
  float matrix_a[9];
  float matrix_b[9];
  float quat[4];
  float angle;
  float axis[3];
  float force[3];
  float speed;
  float suspension_delta;
  float scale;
  float div_max;
  float cos_t;
  float sin_t;
  float *wb;

  veh = (char *)object_get_and_verify_type(vehicle_handle, 2);
  vehi = (char *)tag_get(0x76656869, *(int *)veh);
  phys = (char *)tag_get(0x70687973, *(int *)(vehi + 0x8c));
  wb = (float *)wheel_buffer;
  if (*(int *)(phys + 0x68) != 2) {
    force[0] = 0.0f;
    force[1] = 0.0f;
    force[2] = 0.0f;
    side[0] = 0.0f;
    side[1] = 0.0f;
    side[2] = 0.0f;
    FUN_00154270(vehicle_handle, wheel_buffer, scratch_buffer, force, side);
    return;
  }

  thrust[0] = *(float *)(veh + 0x42c) * *(float *)(veh + 0x24);
  thrust[1] = *(float *)(veh + 0x42c) * *(float *)(veh + 0x28);
  thrust[2] = *(float *)(veh + 0x42c) * *(float *)(veh + 0x2c);

  if (*(float *)(veh + 0x42c) <= 0.0f)
    div_max = *(float *)(vehi + 0x2fc);
  else
    div_max = *(float *)(vehi + 0x2f8);
  if (div_max > 0.0f) {
    float inv = *(float *)(veh + 0x42c) / div_max;
    if (*(float *)(veh + 0x42c) <= 0.0f)
      inv = -inv;
    FUN_001b5f20((float *)(veh + 0x18), thrust, projected, inv * *(float *)(phys + 0x300),
                 inv * *(float *)(phys + 0x304));
  } else {
    projected[0] = 0.0f;
    projected[1] = 0.0f;
    projected[2] = 0.0f;
  }

  scale = *(float *)(phys + 8) * *(float *)(veh + 0x2e8);
  force[0] = projected[0] * scale;
  force[1] = projected[1] * scale;
  force[2] = projected[2] * scale;

  FUN_0010a2c0(basis, (float *)(veh + 0x24), (float *)(veh + 0x30));

  ground_normal[0] = -*(float *)(veh + 0x1d4);
  ground_normal[1] = -*(float *)(veh + 0x1d8);
  ground_normal[2] = -*(float *)(veh + 0x1dc);
  if (normalize3d(ground_normal) <= 0.0f) {
    float *fallback = (float *)0x31fc44;
    ground_normal[0] = *(float *)fallback;
    ground_normal[1] = *(float *)(fallback + 4);
    ground_normal[2] = *(float *)(fallback + 8);
  }

  if (!FUN_001aa4d0(vehicle_handle)) {
    cos_t = cosf(*(float *)(phys + 0x364));
    sin_t = sinf(*(float *)(phys + 0x364));
    FUN_0010c700(ground_normal, (float *)(veh + 0x1d4), cos_t, sin_t);
  }

  {
    float steer = (ground_normal[1] * *(float *)(veh + 0x1c) -
                   ground_normal[0] * *(float *)(veh + 0x20)) /
                  *(float *)(vehi + 0x2f8);
    steer *= *(float *)(phys + 0x308);
    cos_t = cosf(steer);
    sin_t = sinf(steer);
    FUN_0010c690(ground_normal, (float *)(veh + 0x1d4), cos_t, sin_t);
  }

  side[0] = ground_normal[1] * force[2] - ground_normal[2] * force[1];
  side[1] = ground_normal[2] * force[0] - ground_normal[0] * force[2];
  side[2] = ground_normal[0] * force[1] - ground_normal[1] * force[0];

  FUN_00109c70(basis, side, matrix_a);
  FUN_00109c70(matrix_a, ground_normal, matrix_b);
  FUN_0010a330(matrix_b, quat);
  FUN_0010caf0(quat, &angle, axis);

  angle = -angle * *(float *)(phys + 0x314) * *(float *)0x267328;
  force[0] = projected[0] * angle;
  force[1] = projected[1] * angle;
  force[2] = projected[2] * angle;
  force[0] -= *(float *)(veh + 0x3c);
  force[1] -= *(float *)(veh + 0x40);
  force[2] -= *(float *)(veh + 0x44);

  scale = *(float *)(phys + 0x58) + *(float *)(phys + 0x54) + *(float *)(phys + 0x50);
  scale *= *(float *)0x259ec0;
  force[0] *= scale;
  force[1] *= scale;
  force[2] *= scale;

  force[0] *= *(float *)(veh + 0x2e8);
  force[1] *= *(float *)(veh + 0x2e8);
  force[2] *= *(float *)(veh + 0x2e8);

  speed = sqrtf(*(float *)(veh + 0x3c) * *(float *)(veh + 0x3c) +
                *(float *)(veh + 0x40) * *(float *)(veh + 0x40) +
                *(float *)(veh + 0x44) * *(float *)(veh + 0x44));
  speed /= *(float *)(phys + 0x314);

  if (speed <= *(float *)(veh + 0x448)) {
    float delta = (1.0f - *(float *)(veh + 0x448));
    delta = delta * delta * *(float *)0x2549d4;
    if (delta < *(float *)0x25bb10)
      delta = *(float *)0x25bb10;
    else if (delta > *(float *)0x2533e8)
      delta = *(float *)0x2533e8;
    suspension_delta = speed - *(float *)(veh + 0x448);
    if (suspension_delta > delta)
      suspension_delta = delta;
  } else {
    suspension_delta = *(float *)(veh + 0x448) * *(float *)(veh + 0x448) *
                       *(float *)0x2533e8;
    if (suspension_delta > *(float *)0x29d9ac)
      suspension_delta = *(float *)0x29d9ac;
    suspension_delta = -suspension_delta;
    speed = speed - *(float *)(veh + 0x448);
    if (speed < suspension_delta)
      speed = suspension_delta;
    suspension_delta = speed;
  }
  *(float *)(veh + 0x448) = suspension_delta + *(float *)(veh + 0x448);

  wb[6] = *(float *)(veh + 0x2e8);
  csmemcpy((char *)wheel_buffer + 0x1c, (char *)0x31fc5c, 0x10);
  wb[30] = *(float *)(veh + 0x2e8);
  csmemcpy((char *)wheel_buffer + 0x7c, (char *)0x31fc5c, 0x10);

  FUN_00154270(vehicle_handle, wheel_buffer, scratch_buffer, force, side);
}



/* FUN_001b69a0 (0x1b69a0) — Flying-vehicle wheel force setup (physics type 2).
 * wheel_buffer arrives in EDI from the caller. */
#if defined(__clang__)
static void *(*const b69a0_get)(int, int) = object_get_and_verify_type;
static void *(*const b69a0_tag)(int, int) = tag_get;
static float (*const b69a0_norm)(float *) = normalize3d;
static void (*const b69a0_mc690)(float *, float *, float, float) = FUN_0010c690;
static void (*const b69a0_mffu)(float *, float *, float *) = matrix_from_forward_and_up;
static void (*const b69a0_minv)(float *, float *) = matrix_inverse;
static void (*const b69a0_mmul)(float *, float *, float *) = matrix4x3_multiply;
static void (*const b69a0_m9fc0)(float *, float *) = FUN_00109fc0;
static void (*const b69a0_mcaf0)(float *, float *, float *) = FUN_0010caf0;
static void (*const b69a0_pphys)(int, void *, void *, float *, float *) = FUN_00154270;

__attribute__((naked, noinline))
void FUN_001b69a0(int vehicle_handle __attribute__((unused)), void *wheel_buffer __attribute__((unused)), void *scratch_buffer __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xf0, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x76656869\n\t"
      "call *%[tag]\n\t"
      "movl 0x8c(%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x70687973\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x68(%%ebx), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl $2, %%eax\n\t"
      "jne .LFUN_001b69a0_2\n\t"
      "leal 0x1d4(%%esi), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "movl 0x31fc44, %%ecx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl (%%ecx), %%edx\n\t"
      "fchs\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "fchs\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fsubrs 0x2533c8\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001b69a0_1\n\t"
      "movl $0x3f800000, -0x20(%%ebp)\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      ".LFUN_001b69a0_1:\n\t"
      "flds 0x20(%%esi)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "fmuls 0x2c(%%esi)\n\t"
      "movl 0x1c(%%esi), %%edx\n\t"
      "flds 0x1c(%%esi)\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "fmuls 0x28(%%esi)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "subl $8, %%esp\n\t"
      "faddp %%st(1)\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "flds 0x18(%%esi)\n\t"
      "fmuls 0x24(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "flds 0x42c(%%esi)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "fmuls 0x2533e8\n\t"
      "fxch %%st(1)\n\t"
      "fdivs 0x2f8(%%eax)\n\t"
      "fabs\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "fmuls 0x32512c\n\t"
      "fmuls 0x2b7cf4\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x30(%%esi)\n\t"
      "fld %%st(2)\n\t"
      "fmuls 0x24(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x34(%%esi)\n\t"
      "fld %%st(2)\n\t"
      "fmuls 0x28(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "fmuls 0x38(%%esi)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x2c(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fmuls 0x2568bc\n\t"
      "flds 0x2f8(%%eax)\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "fabs\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fld %%st(0)\n\t"
      "fcos\n\t"
      "fstps 0x4(%%esp)\n\t"
      "fsin\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[mc690]\n\t"
      "leal 0x30(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x24(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xbc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[mffu]\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x88(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[mffu]\n\t"
      "leal -0x88(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x88(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[minv]\n\t"
      "leal -0xf0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x88(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xbc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[mmul]\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0xf0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[m9fc0]\n\t"
      "addl $0x44, %%esp\n\t"
      "leal -0x54(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x48(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[mcaf0]\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x2b7cf0\n\t"
      "movl 0x2e8(%%esi), %%ecx\n\t"
      "flds -0x54(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds (%%ebx)\n\t"
      "fmuls (%%ebx)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "fmuls 0x2533e8\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fsubs 0x3c(%%esi)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fstp %%st(1)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fsubs 0x40(%%esi)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fsubs 0x44(%%esi)\n\t"
      "movl %%ecx, 0x18(%%edi)\n\t"
      "movl $0x3f800000, %%ecx\n\t"
      "movl %%ecx, 0x28(%%edi)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "movl %%eax, 0x1c(%%edi)\n\t"
      "movl %%eax, 0x20(%%edi)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "movl %%eax, 0x24(%%edi)\n\t"
      "movl 0x2e8(%%esi), %%edx\n\t"
      "movl %%edx, 0x78(%%edi)\n\t"
      "movl %%ecx, 0x88(%%edi)\n\t"
      "movl %%eax, 0x7c(%%edi)\n\t"
      "movl %%eax, 0x80(%%edi)\n\t"
      "movl %%eax, 0x84(%%edi)\n\t"
      "flds 0x2e8(%%esi)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "movl 0x2e8(%%esi), %%eax\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[pphys]\n\t"
      "addl $0x20, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001b69a0_2:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[pphys]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b69a0_get), [tag] "m"(b69a0_tag), [norm] "m"(b69a0_norm), [mc690] "m"(b69a0_mc690), [mffu] "m"(b69a0_mffu), [minv] "m"(b69a0_minv), [mmul] "m"(b69a0_mmul), [m9fc0] "m"(b69a0_m9fc0), [mcaf0] "m"(b69a0_mcaf0), [pphys] "m"(b69a0_pphys)
      : "memory");
}
#else
#error "FUN_001b69a0: clang naked draft required"
#endif

/* 0x1b6ca0 — Decay vehicle impulse and re-seat orientation after a collision. */
void FUN_001b6ca0(int vehicle_handle)
{
  char *veh;
  float position[3];
  float forward[3];
  float up[3];
  float rot_matrix[12];
  float axis[3];
  float angle;
  float *global_vel;

  veh = (char *)object_get_and_verify_type(vehicle_handle, 2);
  *(int16_t *)(veh + 0x426) -= 1;

  *(float *)(veh + 0x18) *= *(float *)0x2b7cf8;
  *(float *)(veh + 0x1c) *= *(float *)0x2b7cf8;
  *(float *)(veh + 0x20) *= *(float *)0x2b7cf8;
  *(float *)(veh + 0x3c) *= *(float *)0x2b7cf8;
  *(float *)(veh + 0x40) *= *(float *)0x2b7cf8;
  *(float *)(veh + 0x44) *= *(float *)0x2b7cf8;

  position[0] = *(float *)(veh + 0xc) + *(float *)(veh + 0x18);
  position[1] = *(float *)(veh + 0x10) + *(float *)(veh + 0x1c);
  position[2] = *(float *)(veh + 0x14) + *(float *)(veh + 0x20);

  axis[0] = *(float *)(veh + 0x3c);
  axis[1] = *(float *)(veh + 0x40);
  axis[2] = *(float *)(veh + 0x44);
  angle = normalize3d(axis);
  if (angle > 0.0f) {
    FUN_001092d0(rot_matrix, axis, sinf(angle), cosf(angle));
    matrix_scale_transform_vector(rot_matrix, (float *)(veh + 0x24), forward);
    matrix_scale_transform_vector(rot_matrix, (float *)(veh + 0x30), up);
  } else {
    forward[0] = *(float *)(veh + 0x24);
    forward[1] = *(float *)(veh + 0x28);
    forward[2] = *(float *)(veh + 0x2c);
    up[0] = *(float *)(veh + 0x30);
    up[1] = *(float *)(veh + 0x34);
    up[2] = *(float *)(veh + 0x38);
  }

  if (*(int16_t *)(veh + 0x426) == 0) {
    global_vel = *(float **)0x31fc38;
    *(float *)(veh + 0x18) = global_vel[0];
    *(float *)(veh + 0x1c) = global_vel[1];
    *(float *)(veh + 0x20) = global_vel[2];
    *(float *)(veh + 0x3c) = global_vel[0];
    *(float *)(veh + 0x40) = global_vel[1];
    *(float *)(veh + 0x44) = global_vel[2];
  }

  object_set_position(vehicle_handle, position, forward, up);
}



/* 0x1b6e20 — Spawn vehicle scrape/spark effects from wheel contact markers. */
void FUN_001b6e20(int vehicle_handle)
{
  char *veh;
  char *vehi;
  char marker_buf[0x78c];
  int marker_count_a;
  int marker_count_b;
  int marker_total;
  int marker_index;
  float scale_base;
  float dir[3];
  float ray_dir[3];
  float collision[0x40];
  float marker_points[9];
  float marker_forwards[9];
  float rgb[3];
  float effect_scale;
  void *marker_names[3];

  veh = (char *)object_get_and_verify_type(vehicle_handle, 2);
  vehi = (char *)tag_get(0x76656869, *(int *)veh);
  if (*(int *)(vehi + 0x3ec) == -1)
    return;

  marker_count_a = object_get_markers_by_string_id(
      vehicle_handle, (void *)0x002b7d18, marker_buf, 15);
  marker_count_b = object_get_markers_by_string_id(
      vehicle_handle, (void *)0x002b7d08,
      marker_buf + marker_count_a * 0x6c, 16 - marker_count_a);
  marker_total = marker_count_a + marker_count_b;
  if (marker_total <= 0)
    return;

  for (marker_index = 0; marker_index < marker_total; marker_index++) {
    char *marker;

    marker = marker_buf + marker_index * 0x6c;
    /* Cone angle 0x3e860a92 ~= 0.2618 rad (15 deg). */
    random_direction3d((int *)random_math_get_local_seed_address(),
                       (float *)(marker + 0x3c), 0.0f, 0.2617994f, dir);

    if (marker_index >= marker_count_a)
      scale_base = *(float *)(veh + 0x448);
    else
      scale_base = *(float *)(veh + 0x444);
    scale_base *= *(float *)0x254640;
    scale_base += *(float *)0x253f40;

    /* Collision ray direction is the scaled random direction. */
    ray_dir[0] = dir[0] * scale_base;
    ray_dir[1] = dir[1] * scale_base;
    ray_dir[2] = dir[2] * scale_base;

    if (!FUN_0014df70(0x61, (float *)(marker + 0x60), ray_dir, vehicle_handle,
                      (int16_t *)collision))
      continue;

    /* Hit point from collision+0x18, replicated across 3 markers. */
    marker_points[0] = *(float *)((char *)collision + 0x18);
    marker_points[1] = *(float *)((char *)collision + 0x1c);
    marker_points[2] = *(float *)((char *)collision + 0x20);
    marker_points[3] = marker_points[0];
    marker_points[4] = marker_points[1];
    marker_points[5] = marker_points[2];
    marker_points[6] = marker_points[0];
    marker_points[7] = marker_points[1];
    marker_points[8] = marker_points[2];

    marker_forwards[0] = -dir[0];
    marker_forwards[1] = -dir[1];
    marker_forwards[2] = -dir[2];
    marker_forwards[3] = marker_forwards[0];
    marker_forwards[4] = marker_forwards[1];
    marker_forwards[5] = marker_forwards[2];
    marker_forwards[6] = marker_forwards[0];
    marker_forwards[7] = marker_forwards[1];
    marker_forwards[8] = marker_forwards[2];

    FUN_0010c8e0(dir, (float *)((char *)collision + 0x24), rgb);

    marker_names[0] = (void *)0x0028ab18;
    marker_names[1] = (void *)0x0026b188;
    marker_names[2] = (void *)0x002b7cfc;

    effect_scale = *(float *)0x2533c8 - *(float *)((char *)collision + 0x14);
    effect_new_unattached_from_markers(
        *(int *)(vehi + 0x3ec), -1, NULL, 3, marker_names, marker_points,
        marker_forwards, effect_scale, effect_scale, 0.0f, 0.0f, 1.0f);
  }
}



/* 0x1b7020 — Spawn wheel dust effects from ground contact markers. */
void FUN_001b7020(int vehicle_handle)
{
  char *veh;
  char *vehi;
  char marker_buf[0x7b4];
  int marker_count;
  int marker_index;
  float scale;
  float dir[3];
  float origin[3];
  float collision[0x40];
  float marker_points[12];
  float marker_forwards[3];
  float rgb[3];

  veh = (char *)object_get_and_verify_type(vehicle_handle, 2);
  vehi = (char *)tag_get(0x76656869, *(int *)veh);
  if (*(int *)(vehi + 0x3ec) == -1)
    return;
  if (*(float *)(veh + 0x2e8) <= 0.0f)
    return;

  marker_count = object_get_markers_by_string_id(
      vehicle_handle, (void *)0x002b7d18, marker_buf, 15);
  if (marker_count <= 0)
    return;

  for (marker_index = 0; marker_index < marker_count; marker_index++) {
    char *marker;
    float ray_origin[3];

    float effect_fwd[3];
    int copy_index;

    marker = marker_buf + marker_index * 0x6c;
    random_direction3d((int *)random_math_get_local_seed_address(),
                       (float *)(marker + 0x3c), 0.0f, 15.0f, dir);
    ray_origin[0] = *(float *)(marker + 0x60);
    ray_origin[1] = *(float *)(marker + 0x64);
    ray_origin[2] = *(float *)(marker + 0x68);

    if (!FUN_0014df70(0x61, ray_origin, dir, vehicle_handle,
                      (int16_t *)collision))
      continue;

    scale = -*(float *)(marker + 0x44) * (1.0f - *(float *)(collision + 0x20));
    scale *= *(float *)(veh + 0x2e8);
    if (scale <= 0.0f)
      continue;
    if (scale > 1.0f)
      scale = 1.0f;

    marker_points[0] = *(float *)(collision + 0x24) * *(float *)0x253398 +
                       *(float *)(marker + 0x60);
    marker_points[1] = *(float *)(collision + 0x28) * *(float *)0x253398 +
                       *(float *)(marker + 0x64);
    marker_points[2] = *(float *)(collision + 0x2c) * *(float *)0x253398 +
                       *(float *)(marker + 0x68);
    for (copy_index = 1; copy_index < 4; copy_index++) {
      marker_points[copy_index * 3 + 0] = marker_points[0];
      marker_points[copy_index * 3 + 1] = marker_points[1];
      marker_points[copy_index * 3 + 2] = marker_points[2];
    }

    origin[0] = *(float *)(collision + 0x30);
    origin[1] = *(float *)(collision + 0x34);
    origin[2] = *(float *)(collision + 0x38);
    effect_fwd[0] = -dir[0];
    effect_fwd[1] = -dir[1];
    effect_fwd[2] = -dir[2];
    FUN_0010c8e0(origin, effect_fwd, rgb);
    FUN_0010c8e0((float *)(marker + 0x60), dir, marker_forwards);

    effect_new_unattached_from_markers(
        *(int *)(vehi + 0x3ec), -1, NULL, 4, (void *)0x002b7cfc,
        marker_points, marker_forwards, scale, scale, 0.0f, 0.0f, 1.0f);
  }
}



/* 0x1b72b0 — Apply wheel-collision damage and scrape sounds to a vehicle. */

void FUN_001b72b0(int vehicle_handle, void *contact_point, void *wheel_state)
{
  char *veh;
  char *vehi;
  char *phys;
  char *damage_globals;
  char *damage_block;
  char *wheel_flags;
  float contact[3];
  float dist;
  float scale;
  float damage_amount;
  int wheel_count;
  int wheel_index;
  char damage_params[0x54];

  veh = (char *)object_get_and_verify_type(vehicle_handle, 2);
  vehi = (char *)tag_get(0x76656869, *(int *)veh);
  phys = (char *)tag_get(0x70687973, *(int *)(vehi + 0x8c));
  damage_globals = (char *)game_globals_get();
  damage_block = (char *)tag_block_get_element(damage_globals + 0x188, 0, 0x98);
  if (*(int *)(damage_block + 0x48) == -1 && *(int *)(vehi + 0x3cc) == -1)
    return;

  contact[0] = *(float *)(veh + 0x18) - *(float *)contact_point;
  contact[1] = *(float *)(veh + 0x1c) - *((float *)contact_point + 1);
  contact[2] = *(float *)(veh + 0x20) - *((float *)contact_point + 2);
  dist = sqrtf(contact[0] * contact[0] + contact[1] * contact[1] +
               contact[2] * contact[2]);
  if (dist > *(float *)0x255ca0)
    return;

  wheel_count = *(int *)(phys + 0x74);
  if (wheel_count <= 0)
    return;

  wheel_flags = (char *)wheel_state;
  for (wheel_index = 0; wheel_index < wheel_count; wheel_index++) {
    if ((wheel_flags[wheel_index * 0x130] & 2) == 0)
      continue;

    scale = (dist - *(float *)0x255ca0) * *(float *)0x2b7d34;
    if (*(int *)(damage_block + 0x48) != -1) {
      damage_data_new(damage_params, *(int *)(damage_block + 0x48));
      if (scale <= 0.0f)
        damage_amount = 0.0f;
      else if (scale >= 1.0f)
        damage_amount = 1.0f;
      else
        damage_amount = scale;
      *(float *)(damage_params + 0x1c) = *(float *)(veh + 0x50);
      *(float *)(damage_params + 0x20) = *(float *)(veh + 0x54);
      *(float *)(damage_params + 0x24) = *(float *)(veh + 0x58);
      *(float *)(damage_params + 0x34) = contact[0];
      *(float *)(damage_params + 0x38) = contact[1];
      *(float *)(damage_params + 0x3c) = contact[2];
      *(float *)(damage_params + 0x40) = damage_amount;
      object_cause_damage(damage_params, vehicle_handle, -1, -1, -1, 0);
    }

    if (*(int *)(vehi + 0x3cc) == -1)
      return;

    if (scale <= 0.0f)
      damage_amount = 0.0f;
    else if (scale >= 1.0f)
      damage_amount = 1.0f;
    else
      damage_amount = scale;
    object_impulse_sound_new(
        vehicle_handle, *(int *)(vehi + 0x3cc), -1,
        (float *)(uintptr_t)*(int *)(0x31fc1c),
        (float *)(uintptr_t)*(int *)(0x31fc3c), damage_amount);
    return;
  }
}



/* 0x1b74d0 — Update vehicle antenna compression from collision rays; returns true
 * when a scrape sound was triggered. */

char FUN_001b74d0(int vehicle_handle)
{
  char *veh;
  char *vehi;
  char *rtna;
  char *phys;
  char *rtna_root;
  char *antenna_block;
  char *antenna_elem;
  float object_matrix[12];
  float world_point[3];
  float world_dir[3];
  char collision[0xd4];
  float ray_origin[3];
  float ray_direction[3];
  float hit_distance;
  float hit_blend;
  float factor;
  float max_blend;
  float sound_scale;
  int antenna_count;
  int antenna_index;

  veh = (char *)object_get_and_verify_type(vehicle_handle, 2);
  vehi = (char *)tag_get(0x76656869, *(int *)veh);
  if (*(int *)(vehi + 0x44) == -1)
    return 0;

  rtna = (char *)tag_get(0x616e7472, *(int *)(vehi + 0x44));
  if (*(int *)(rtna + 0x24) == 0)
    return 0;

  rtna_root = (char *)tag_block_get_element(rtna + 0x24, 0, 0x74);
  if (rtna_root == 0)
    return 0;

  phys = (char *)tag_get(0x70687973, *(int *)(vehi + 0x8c));
  matrix4x3_from_forward_up_position(object_matrix, (float *)(veh + 0xc),
                                     (float *)(veh + 0x24), (float *)(veh + 0x30));

  antenna_block = rtna_root + 0x68;
  antenna_count = *(int *)antenna_block;
  max_blend = 0.0f;
  for (antenna_index = 0; antenna_index < antenna_count; antenna_index++) {
    char *wheel_entry;
    float span;
    float ray_t;
    float doubled_span;
    float candidate;
    unsigned char packed;

    antenna_elem =
        (char *)tag_block_get_element(antenna_block, antenna_index, 0x14);
    if (*(int16_t *)antenna_elem < 0)
      continue;

    wheel_entry = (char *)tag_block_get_element(phys + 0x74, *(int16_t *)antenna_elem,
                                                0x80);
    if (*(int16_t *)(antenna_elem + 2) == -1)
      continue;

    (void)tag_block_get_element(rtna + 0x74, *(int16_t *)(antenna_elem + 2), 0xb4);

    if (*(unsigned char *)(veh + 0x44c + antenna_index) == 0xff)
      factor = 1.0f;
    else
      factor = (float)*(unsigned char *)(veh + 0x44c + antenna_index) *
               *(float *)0x261518;

    matrix_transform_point(object_matrix, (float *)(wheel_entry + 0x38), world_point);
    matrix_transform_vector(object_matrix, (float *)(wheel_entry + 0x50), world_dir);

    span = *(float *)(antenna_elem + 4) - *(float *)(antenna_elem + 8);
    ray_t = span - (*(float *)(antenna_elem + 8) - *(float *)(phys + 0x14));
    doubled_span = span + span;
    ray_origin[0] = world_dir[0] * ray_t + world_point[0];
    ray_origin[1] = world_dir[1] * ray_t + world_point[1];
    ray_origin[2] = world_dir[2] * ray_t + world_point[2];
    ray_direction[0] = world_dir[0] * doubled_span;
    ray_direction[1] = world_dir[1] * doubled_span;
    ray_direction[2] = world_dir[2] * doubled_span;

    if (!FUN_0014df70(0xc0a0, ray_origin, ray_direction, vehicle_handle,
                      (int16_t *)collision))
      continue;

    hit_distance = *(float *)(collision + 0x14);
    hit_blend = (1.0f - hit_distance) * 2.0f;
    hit_blend = vehicle_clamp_unit_float(hit_blend);
    candidate = hit_blend - factor;
    if (candidate > max_blend)
      max_blend = candidate;
    packed = quantize_real_to_byte_lower_bound(
        0.0f, 1.0f, (hit_blend + factor) * *(float *)0x253398);
    *(unsigned char *)(veh + 0x44c + antenna_index) = packed;
  }

  if (*(int *)(vehi + 0x3bc) == -1)
    return 0;

  if (max_blend <= *(float *)0x2533e4)
    return 0;

  sound_scale =
      (max_blend - *(float *)0x2533e4) * *(float *)0x2b7d38;
  sound_scale = vehicle_clamp_unit_float(sound_scale);
  object_impulse_sound_new(
      vehicle_handle, *(int *)(vehi + 0x3bc), -1,
      (float *)(uintptr_t)*(int *)(0x31fc1c),
      (float *)(uintptr_t)*(int *)(0x31fc3c), sound_scale);
  return 1;
}



/* FUN_001b77f0 (0x1b77f0) — XBE naked draft (batch 225). */
#if defined(__clang__)
static void *(*const b1b77f0_get)(int, int) = object_get_and_verify_type;
static void *(*const b1b77f0_tag)(int, int) = tag_get;
static void *(*const b1b77f0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1b77f0_o9f430)(int, short, short, void *, void *, void *, float) = FUN_0009f430;

__attribute__((naked, noinline))
void FUN_001b77f0(int vehicle_handle __attribute__((unused)), void *scratch __attribute__((unused)), void *wheel_state __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x28, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x76656869\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x8c(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x70687973\n\t"
      "call *%[tag]\n\t"
      "movl 0x3dc(%%ebx), %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_001b77f0_7\n\t"
      "pushl %%edi\n\t"
      "leal 0x74(%%eax), %%edi\n\t"
      "cmpl $0, (%%edi)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jle .LFUN_001b77f0_6\n\t"
      "xorl %%eax, %%eax\n\t"
      "pushl %%esi\n\t"
      "jmp .LFUN_001b77f0_1\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_001b77f0_1:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "imull $0x130, %%esi, %%esi\n\t"
      "pushl $0x80\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "addl %%ecx, %%esi\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movb (%%esi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $2, %%al\n\t"
      "je .LFUN_001b77f0_5\n\t"
      "flds 0x5c(%%esi)\n\t"
      "flds 0x58(%%esi)\n\t"
      "flds 0x54(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x25bc08\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b77f0_5\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fsubs 0x25bc08\n\t"
      "fmuls 0x2b7d3c\n\t"
      "flds 0x74(%%esi)\n\t"
      "fsubs 0x68(%%ecx)\n\t"
      "fadds 0x2b2264\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x60(%%esi)\n\t"
      "fadds 0x4(%%esi)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x64(%%esi)\n\t"
      "fadds 0x8(%%esi)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "fmuls 0x68(%%esi)\n\t"
      "fadds 0xc(%%esi)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds 0x2533dc\n\t"
      "fdivs -0x4(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x54(%%esi)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x58(%%esi)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x5c(%%esi)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x60(%%esi)\n\t"
      "fmuls 0x253398\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x64(%%esi)\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x68(%%esi)\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b77f0_2\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "jmp .LFUN_001b77f0_4\n\t"
      ".LFUN_001b77f0_2:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b77f0_3\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, -0x8(%%ebp)\n\t"
      "jmp .LFUN_001b77f0_4\n\t"
      ".LFUN_001b77f0_3:\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".LFUN_001b77f0_4:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x24(%%ecx), %%ecx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "addl $0x48, %%edx\n\t"
      "pushl %%edx\n\t"
      "andb $1, %%cl\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x70(%%esi), %%ax\n\t"
      "negb %%cl\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x3dc(%%ebx), %%edx\n\t"
      "pushl %%eax\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "negl %%ecx\n\t"
      "addl $9, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[o9f430]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_001b77f0_5:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl (%%edi), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_001b77f0_1\n\t"
      "popl %%esi\n\t"
      ".LFUN_001b77f0_6:\n\t"
      "popl %%edi\n\t"
      ".LFUN_001b77f0_7:\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [get] "m"(b1b77f0_get), [tag] "m"(b1b77f0_tag), [elem] "m"(b1b77f0_elem), [o9f430] "m"(b1b77f0_o9f430)
      : "memory");
}
#else
#error "FUN_001b77f0: clang naked draft required"
#endif


/* vehicle_export_function_values (0x1b79c0) — fill vehicle+0xd4 function-value
 * slots from vehi tag indices (4 entries at vehi+0x31c). */

void vehicle_export_function_values(int vehicle_handle)
{
  char *veh;
  char *vehi;
  float *out;
  int16_t *fn_idx;
  int slot;
  float max_fwd_tag;
  float max_back_tag;
  float max_fwd;
  float max_right_a;
  float max_right_b;
  float max_right_max;
  float max_up_a;
  float max_up_b;
  float max_up_max;
  float value;

  veh = (char *)object_get_and_verify_type(vehicle_handle, 2);
  vehi = (char *)tag_get(0x76656869, *(int *)veh);
  max_fwd_tag = fabsf(*(float *)(vehi + 0x2f8));
  max_back_tag = fabsf(*(float *)(vehi + 0x2fc));
  max_fwd = max_fwd_tag;
  if (max_fwd < max_back_tag)
    max_fwd = max_back_tag;
  max_right_a = fabsf(*(float *)(vehi + 0x330));
  max_right_b = fabsf(*(float *)(vehi + 0x334));
  max_right_max = max_right_a;
  if (max_right_max < max_right_b)
    max_right_max = max_right_b;
  max_up_a = fabsf(*(float *)(vehi + 0x308));
  max_up_b = fabsf(*(float *)(vehi + 0x30c));
  max_up_max = max_up_a;
  if (max_up_max < max_up_b)
    max_up_max = max_up_b;

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
    case 28:
    case 29:
    case 30:
    case 31:
      value = fabsf(*(float *)(veh + 0x42c)) / max_fwd;
      break;
    case 2:
      if (*(float *)(veh + 0x42c) <= 0.0f)
        value = 0.0f;
      else
        value = *(float *)(veh + 0x42c) / max_fwd_tag;
      break;
    case 3:
      if (*(float *)(veh + 0x42c) <= 0.0f)
        value = 0.0f;
      else
        value = fabsf(*(float *)(veh + 0x42c)) / max_back_tag;
      break;
    case 4:
      value = fabsf(*(float *)(veh + 0x42c)) / max_back_tag;
      break;
    case 5:
      value = fabsf(*(float *)(veh + 0x430)) / max_right_a;
      break;
    case 6:
      value = fabsf(*(float *)(veh + 0x430)) / max_right_b;
      break;
    case 7:
      a = fabsf(*(float *)(veh + 0x42c)) / max_fwd;
      b = fabsf(*(float *)(veh + 0x430)) / max_right_max;
      value = a > b ? a : b;
      break;
    case 8:
      value = fabsf(*(float *)(veh + 0x434)) / max_up_max;
      break;
    case 9:
      value = fabsf(*(float *)(veh + 0x434)) / max_up_a;
      break;
    case 10:
      value = fabsf(*(float *)(veh + 0x434)) / max_up_b;
      break;
    case 11:
      if ((*(unsigned char *)(veh + 0x424) & 4) != 0)
        value = 0.0f;
      else
        value = 1.0f;
      break;
    case 12:
      if ((*(unsigned char *)(veh + 0x424) & 8) != 0)
        value = 0.0f;
      else
        value = 1.0f;
      break;
    case 13:
      value = 0.0f;
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
      value =
          fabsf(*(float *)(veh + 0x20) * *(float *)(veh + 0x2c) +
                *(float *)(veh + 0x1c) * *(float *)(veh + 0x28) +
                *(float *)(veh + 0x18) * *(float *)(veh + 0x24)) /
          max_fwd;
      break;
    case 18:
    case 19:
      value =
          fabsf(*(float *)(veh + 0x20) * *(float *)(veh + 0x38) +
                *(float *)(veh + 0x1c) * *(float *)(veh + 0x34) +
                *(float *)(veh + 0x18) * *(float *)(veh + 0x30)) /
          max_fwd;
      break;
    case 20:
      value = *(float *)(veh + 0x43c) / *(float *)(vehi + 0x310);
      break;
    case 21:
      value = *(float *)(veh + 0x440) / *(float *)(vehi + 0x310);
      break;
    case 22:
      value = fabsf(*(float *)(veh + 0x42c) - *(float *)(veh + 0x434)) /
              max_fwd;
      break;
    case 23:
      value = fabsf(*(float *)(veh + 0x434) + *(float *)(veh + 0x42c)) /
              max_fwd;
      break;
    case 24:
    case 25:
    case 26:
    case 27:
      value = *(float *)(veh + 0x438) / *(float *)(vehi + 0x310);
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
      value = *(float *)(veh + 0x444);
      break;
    case 34:
      value = *(float *)(veh + 0x448);
      break;
    case 35: {
      float ratio_a;
      float ratio_b;
      float t;
      unsigned char blend = *(unsigned char *)(veh + 0x428);
      ratio_a =
          fabsf(*(float *)(veh + 0x20) * *(float *)(veh + 0x2c) +
                *(float *)(veh + 0x1c) * *(float *)(veh + 0x28) +
                *(float *)(veh + 0x18) * *(float *)(veh + 0x24)) /
          max_fwd;
      ratio_b = fabsf(*(float *)(veh + 0x42c)) / max_fwd_tag;
      t = (float)blend * *(float *)0x2549d4 + *(float *)0x2533c8;
      t *= *(float *)0x253398;
      if (t <= 0.0f)
        t = 0.0f;
      else if (t >= 1.0f)
        t = 1.0f;
      value = ratio_a + (ratio_b - ratio_a) * t;
      break;
    }
    case 36:
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



/* 0x1b8060 — true when vehicle contact normals oppose the stuck probe vector. */
char vehicle_stuck(int unit_handle, float *vec)
{
  char *vehicle;
  char contact[0x64];
  float accum[3];
  float average[3];
  float world[3];
  float *gravity;
  float *plane;
  int mask;
  int contact_count;
  int matched;
  int i;
  char *block;

  vehicle = (char *)object_get_and_verify_type(unit_handle, 2);
  mask = *(int *)(vehicle + 0x478);
  if (mask == 0)
    return 0;
  if (!FUN_001509c0((int *)contact, unit_handle))
    return 0;

  gravity = *(float **)0x31fc1c;
  accum[0] = gravity[0];
  accum[1] = gravity[1];
  accum[2] = gravity[2];

  block = *(char **)(contact + 4);
  contact_count = *(int *)(block + 0x74);
  matched = 0;
  for (i = 0; i < contact_count; i++) {
    if ((mask & (1 << i)) != 0) {
      plane = (float *)((char *)tag_block_get_element(block + 0x74, i, 0x80) +
                        0x38);
      accum[0] += plane[0];
      accum[1] += plane[1];
      accum[2] += plane[2];
      matched++;
    }
  }

  if (matched <= 0)
    return 0;

  {
    float inv = *(float *)0x2533c8 / (float)matched;
    accum[0] *= inv;
    accum[1] *= inv;
    accum[2] *= inv;
  }

  matrix_transform_point((float *)(contact + 8), accum, average);
  object_get_world_position(unit_handle, (void *)world);
  vec[0] = average[0] - world[0];
  vec[1] = average[1] - world[1];
  vec[2] = average[2] - world[2];
  if (normalize3d(vec) == 0.0f)
    return 0;
  return 1;
}



/* 0x1b81d0 — vehicle ground force / wheel integration.
 * Caller pushes (handle, scratch_a, force_buffer). scratch_a is unused here. */

void FUN_001b81d0(int object_handle, void *unused_scratch, void *force_buffer)
{
  char *object;
  char *vehicle_tag;
  char *physics_tag;
  float *forward;
  float speed_ratio;
  float damping;
  float delta;
  float ground[3];
  float tilted[3];
  float left[3];
  float force[3];
  float aux[3];
  float mat_a[12];
  float mat_b[12];
  float mat_c[12];
  float quat[4];
  float angle;
  float axis[3];
  float yaw;
  float scale;
  float mass_term;
  unsigned short flags;

  (void)unused_scratch;
  object = (char *)object_get_and_verify_type(object_handle, 2);
  vehicle_tag = (char *)tag_get(0x76656869, *(int *)object); /* 'vehi' */
  physics_tag =
      (char *)tag_get(0x70687973, *(int *)(vehicle_tag + 0x8c)); /* 'phys' */
  flags = *(unsigned short *)(object + 0x424);

  if ((flags & 2) != 0) {
    csmemset(force_buffer, 0, *(int *)(physics_tag + 0x74) * 0x130);
    FUN_001b6e20(object_handle);
    return;
  }

  /* Clamp forward speed into [0, max_forward], square, normalize by max. */
  if (*(float *)(object + 0x42c) < 0.0f)
    speed_ratio = 0.0f;
  else if (!(*(float *)(object + 0x42c) <= *(float *)(vehicle_tag + 0x2f8)))
    speed_ratio = *(float *)(vehicle_tag + 0x2f8);
  else
    speed_ratio = *(float *)(object + 0x42c);
  speed_ratio /= *(float *)(vehicle_tag + 0x2f8);
  speed_ratio *= speed_ratio;

  if ((flags & 4) != 0)
    damping = *(float *)0x25337c; /* 0.25 */
  else if ((flags & 8) != 0)
    damping = 1.0f;
  else
    damping = *(float *)0x25afcc; /* 0.75 */

  delta = (1.0f - speed_ratio) * damping * *(float *)(object + 0x2e8) -
          *(float *)(object + 0x444);
  if (delta < *(float *)0x2b7d44)
    delta = *(float *)0x2b7d44;
  else if (!(delta <= *(float *)0x2533e8))
    delta = *(float *)0x2533e8;
  *(float *)(object + 0x444) += delta;

  ground[0] = *(float *)(object + 0x1d4);
  ground[1] = *(float *)(object + 0x1d8);
  ground[2] = *(float *)(object + 0x1dc);

  scale = speed_ratio * *(float *)(object + 0x2e8);
  *(float *)(object + 0x448) = scale;

  /* Build nearly-vertical tilt from ground normal. */
  tilted[0] = -(ground[0] * ground[2]);
  tilted[1] = -(ground[1] * ground[2]);
  tilted[2] = 1.0f - ground[2] * ground[2];
  if (normalize3d(tilted) == 0.0f) {
    tilted[0] = 1.0f;
    tilted[1] = 0.0f;
    tilted[2] = 0.0f;
  }

  forward = (float *)(object + 0x24);
  left[0] = *(float *)(object + 0x18);
  left[1] = *(float *)(object + 0x1c);
  left[2] = *(float *)(object + 0x20);

  {
    float facing_dot = left[2] * forward[2] + left[1] * forward[1] +
                       left[0] * forward[0];
    float drive = (*(float *)(object + 0x42c) - facing_dot) * scale *
                  *(float *)(physics_tag + 8) * *(float *)0x2533e8;
    float turn = fabsf(*(float *)(object + 0x42c) /
                       *(float *)(vehicle_tag + 0x2f8)) *
                     *(float *)0x2b7cf4 +
                 *(float *)(object + 0x444) * *(float *)0x255b9c;
    turn *= *(float *)0x32512c * *(float *)(physics_tag + 8);

    force[0] = turn * *(float *)(object + 0x30) + drive * forward[0];
    force[1] = turn * *(float *)(object + 0x34) + drive * *(float *)(object + 0x28);
    force[2] = turn * *(float *)(object + 0x38) + drive * *(float *)(object + 0x2c);
  }

  yaw = (left[1] * ground[0] - left[0] * ground[1]) * *(float *)0x2568bc;
  yaw /= fabsf(*(float *)(vehicle_tag + 0x2f8));
  FUN_0010c690(tilted, ground, sinf(yaw), cosf(yaw));

  matrix_from_forward_and_up(mat_a, forward, (float *)(object + 0x30));
  matrix_from_forward_and_up(mat_b, tilted, ground);
  matrix_inverse(mat_b, mat_b);
  matrix4x3_multiply(mat_a, mat_b, mat_c);
  FUN_00109fc0(mat_c, quat);
  FUN_0010caf0(quat, &angle, axis);

  angle *= *(float *)0x2546a4;
  mass_term = *(float *)physics_tag * *(float *)physics_tag *
              *(float *)(physics_tag + 8) * *(float *)0x2533e8;

  aux[0] = (axis[0] * angle - *(float *)(object + 0x3c)) * mass_term;
  aux[1] = (axis[1] * angle - *(float *)(object + 0x40)) * mass_term;
  aux[2] = (axis[2] * angle - *(float *)(object + 0x44)) * mass_term;

  force[0] *= *(float *)(object + 0x2e8);
  force[1] *= *(float *)(object + 0x2e8);
  force[2] *= *(float *)(object + 0x2e8);
  aux[0] *= *(float *)(object + 0x2e8);
  aux[1] *= *(float *)(object + 0x2e8);
  aux[2] *= *(float *)(object + 0x2e8);

  FUN_00154270(object_handle, 0, force_buffer, force, aux);
  FUN_001b6e20(object_handle);
}



/* 0x1b8570 — per-tick vehicle force integration.
 * Args: handle, dt, contact_buf (stride 0x60), wheel_buf (stride 0x130). */
#if defined(__clang__)
static float (*const b8570_mag)(float *) = magnitude3d;
static float (*const b8570_norm)(float *) = normalize3d;
static short (*const b8570_a57b0)(float *, float) = (void *)FUN_000a57b0;
static void (*const b8570_mscale)(float *, float *, float *) = matrix_scale_transform_vector;
static void (*const b8570_m3x3v)(void *, vector3_t *, vector3_t *) = real_matrix3x3_transform_vector;
static void (*const b8570_m4x3)(void *, float *, float *, float *) = matrix4x3_from_forward_up_position;
static void *(*const b8570_get)(int, int) = object_get_and_verify_type;
static void (*const b8570_pphys)(int, void *, void *, float *, float *) = FUN_00154270;
static float (*const b8570_f8510)(void *, void *) = FUN_0018f510;
static void *(*const b8570_elem)(void *, int, int) = tag_block_get_element;
static void (*const b8570_b7020)(int) = FUN_001b7020;
static void *(*const b8570_tag)(int, int) = tag_get;

__attribute__((naked, noinline))
void FUN_001b8570(int object_handle __attribute__((unused)), float dt __attribute__((unused)), void *contact_buf __attribute__((unused)), void *wheel_buf __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x94, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x76656869\n\t"
      "call *%[tag]\n\t"
      "movl 0x8c(%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x70687973\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "leal 0xc(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x48(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, -0x30(%%ebp)\n\t"
      "call *%[f8510]\n\t"
      "movl 0x31fc38, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edx, -0x40(%%ebp)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x3c(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "movl 0x2e8(%%esi), %%eax\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movl 0x68(%%edi), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "addl $0x20, %%esp\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jle .LFUN_001b8570_2\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_001b8570_1:\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "shll $5, %%eax\n\t"
      "addl %%ebx, %%eax\n\t"
      "movl -0x2c(%%ebp), %%ebx\n\t"
      "movl %%ebx, 0x18(%%eax)\n\t"
      "incl %%ecx\n\t"
      "movl %%edx, 0x1c(%%eax)\n\t"
      "movl %%edx, 0x20(%%eax)\n\t"
      "movl %%edx, 0x24(%%eax)\n\t"
      "movl $0x3f800000, 0x28(%%eax)\n\t"
      "movl 0x68(%%edi), %%ebx\n\t"
      "movswl %%cx, %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jl .LFUN_001b8570_1\n\t"
      ".LFUN_001b8570_2:\n\t"
      "fcomps 0x253398\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b8570_34\n\t"
      "flds 0x38(%%esi)\n\t"
      "fcomps 0x255ba4\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8570_34\n\t"
      "leal 0x30(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "leal 0x24(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "leal 0xc(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x94(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[m4x3]\n\t"
      "leal -0x60(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x18(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x94(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[m3x3v]\n\t"
      "flds 0x444(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x1c, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8570_6\n\t"
      "testb $8, 0x424(%%esi)\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "flds 0x2f8(%%eax)\n\t"
      "je .LFUN_001b8570_3\n\t"
      "fmuls 0x2533f0\n\t"
      ".LFUN_001b8570_3:\n\t"
      "movl 0x300(%%eax), %%ecx\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x228(%%esi)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movb 0x42b(%%esi), %%cl\n\t"
      "fxch %%st(1)\n\t"
      "testb %%cl, %%cl\n\t"
      "fmuls 0x22c(%%esi)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "fsubs -0x60(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x48(%%ebp)\n\t"
      "fsubs -0x5c(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "jbe .LFUN_001b8570_5\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x25b3f0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8570_5\n\t"
      "movzbl %%cl, %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "fildl -0x18(%%ebp)\n\t"
      "fmuls 0x2533e8\n\t"
      "fcoms 0x291060\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8570_4\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x291060\n\t"
      ".LFUN_001b8570_4:\n\t"
      "flds 0x2533c8\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_001b8570_5:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[a57b0]\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x94(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[mscale]\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "flds 0x8(%%edx)\n\t"
      "addl $0x14, %%esp\n\t"
      "fmuls 0x444(%%esi)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x28(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x24(%%ebp)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fadds -0x20(%%ebp)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      ".LFUN_001b8570_6:\n\t"
      "flds 0x444(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8570_13\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls 0x44(%%esi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "flds 0x3c(%%esi)\n\t"
      "fmuls (%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_001b8570_8\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b8570_7\n\t"
      "movl $0xffffffff, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001b8570_9\n\t"
      ".LFUN_001b8570_7:\n\t"
      "movl $1, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001b8570_9\n\t"
      ".LFUN_001b8570_8:\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      ".LFUN_001b8570_9:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fabs\n\t"
      "fmull 0x2b7d68\n\t"
      "fsqrt\n\t"
      "fimull -0x4(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8570_10\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fcomps 0x253f40\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b8570_10\n\t"
      "fstp %%st(0)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      ".LFUN_001b8570_10:\n\t"
      ".byte 0xde, 0xe1\n\t"
      "fcoms 0x2b7d60\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b8570_11\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2b7d60\n\t"
      "jmp .LFUN_001b8570_12\n\t"
      ".LFUN_001b8570_11:\n\t"
      "fcoms 0x2b7d5c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8570_12\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2b7d5c\n\t"
      ".LFUN_001b8570_12:\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "fmuls 0x58(%%eax)\n\t"
      "fmuls 0x444(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%edi)\n\t"
      "fadds -0x40(%%ebp)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "fadds -0x3c(%%ebp)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "fadds -0x38(%%ebp)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      ".LFUN_001b8570_13:\n\t"
      "flds 0x444(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b8570_26\n\t"
      "flds 0x8(%%ebx)\n\t"
      "movl 0x31fc08, %%eax\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "flds 0x4(%%ebx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl %%ecx, -0x54(%%ebp)\n\t"
      "movl 0x4(%%ebx), %%ecx\n\t"
      ".byte 0xde, 0xe9\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "movl -0x4c(%%ebp), %%edx\n\t"
      "flds 0x8(%%edi)\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "fmuls (%%ebx)\n\t"
      "pushl %%ecx\n\t"
      "flds (%%edi)\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "flds (%%edi)\n\t"
      "movl -0x48(%%ebp), %%eax\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls (%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fstp %%st(0)\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[mag]\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x38(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8570_24\n\t"
      "flds -0x4(%%ebp)\n\t"
      "movl 0x31fc08, %%eax\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "fmuls (%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "fmuls 0x3c(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x40(%%esi)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x3c(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fchs\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fsub %%st(2), %%st(0)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fstp %%st(2)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x254cc0\n\t"
      "fsubrs -0x1c(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x254cc0\n\t"
      "fsubr %%st(1), %%st(0)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x228(%%esi)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_001b8570_15\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b8570_14\n\t"
      "movl $0xffffffff, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001b8570_16\n\t"
      ".LFUN_001b8570_14:\n\t"
      "movl $1, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001b8570_16\n\t"
      ".LFUN_001b8570_15:\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      ".LFUN_001b8570_16:\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fabs\n\t"
      "fimull -0x4(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x22c(%%esi)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_001b8570_18\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b8570_17\n\t"
      "movl $0xffffffff, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001b8570_19\n\t"
      ".LFUN_001b8570_17:\n\t"
      "movl $1, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001b8570_19\n\t"
      ".LFUN_001b8570_18:\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      ".LFUN_001b8570_19:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fabs\n\t"
      "fimull -0x4(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fadds 0x2533c8\n\t"
      "fcoms 0x2533e4\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b8570_20\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533e4\n\t"
      "jmp .LFUN_001b8570_21\n\t"
      ".LFUN_001b8570_20:\n\t"
      "fcoms 0x254e04\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8570_21\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x254e04\n\t"
      ".LFUN_001b8570_21:\n\t"
      "fmuls 0x228(%%esi)\n\t"
      "fmuls 0x2b7d58\n\t"
      "fadds -0x54(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fadds 0x2533c8\n\t"
      "fcoms 0x2533e4\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b8570_22\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533e4\n\t"
      "jmp .LFUN_001b8570_23\n\t"
      ".LFUN_001b8570_22:\n\t"
      "fcoms 0x254e04\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8570_23\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x254e04\n\t"
      ".LFUN_001b8570_23:\n\t"
      "fmuls 0x22c(%%esi)\n\t"
      "fmuls 0x2b7d58\n\t"
      "fadds -0x50(%%ebp)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x38(%%esi)\n\t"
      "fmuls 0x2b7d54\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "jmp .LFUN_001b8570_25\n\t"
      ".LFUN_001b8570_24:\n\t"
      "flds 0x228(%%esi)\n\t"
      "fmuls 0x2b7d58\n\t"
      "fadds -0x54(%%ebp)\n\t"
      "flds 0x22c(%%esi)\n\t"
      "fmuls 0x2b7d58\n\t"
      ".LFUN_001b8570_25:\n\t"
      "fadds -0x50(%%ebp)\n\t"
      "movl 0x31fc38, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "fxch %%st(1)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "fmuls 0x54(%%eax)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x48(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fmuls 0x50(%%eax)\n\t"
      "fchs\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%ebx)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x444(%%esi)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fadds -0x40(%%ebp)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fadds -0x3c(%%ebp)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fadds -0x38(%%ebp)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      ".LFUN_001b8570_26:\n\t"
      "testb $8, 0x424(%%esi)\n\t"
      "je .LFUN_001b8570_33\n\t"
      "flds 0x8(%%ebx)\n\t"
      "movl -0x34(%%ebp), %%ecx\n\t"
      "fmuls 0x20(%%esi)\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fmuls 0x1c(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "flds (%%ebx)\n\t"
      "fmuls 0x18(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fdivs 0x2f8(%%ecx)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b8570_27\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_001b8570_28\n\t"
      ".LFUN_001b8570_27:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8570_28\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_001b8570_28:\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls (%%ebx)\n\t"
      "flds (%%edi)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fmuls (%%edi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "movl 0x31fc44, %%edi\n\t"
      "fmuls (%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8570_29\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "flds 0x54(%%eax)\n\t"
      "fmuls 0x444(%%esi)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fmuls 0x2b7d50\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x40(%%ebp)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x3c(%%ebp)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x38(%%ebp)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x444(%%esi)\n\t"
      "fmulp %%st(1)\n\t"
      "fmuls 0x2b7d4c\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%edi)\n\t"
      "fadds -0x28(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "fadds -0x24(%%ebp)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "fadds -0x20(%%ebp)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "jmp .LFUN_001b8570_30\n\t"
      ".LFUN_001b8570_29:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_001b8570_30:\n\t"
      "movb 0x428(%%esi), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "jbe .LFUN_001b8570_33\n\t"
      "flds -0x10(%%ebp)\n\t"
      "leal -0x4c(%%ebp), %%edx\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "pushl %%edx\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8570_33\n\t"
      "movzbl %%bl, %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "fildl -0x18(%%ebp)\n\t"
      "fmuls 0x2546a4\n\t"
      "fsubrs 0x2533c8\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b8570_31\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_001b8570_32\n\t"
      ".LFUN_001b8570_31:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8570_32\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_001b8570_32:\n\t"
      "flds 0x2533c8\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "fsubs 0x444(%%esi)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fmuls 0x2b7d48\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x28(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0x48(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x24(%%ebp)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x20(%%ebp)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x444(%%esi)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "fmulp %%st(1)\n\t"
      "fmuls 0x255ef8\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%edi)\n\t"
      "fadds -0x28(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "fadds -0x24(%%ebp)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "fadds -0x20(%%ebp)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      ".LFUN_001b8570_33:\n\t"
      "flds -0x28(%%ebp)\n\t"
      "movl -0x30(%%ebp), %%edi\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      ".LFUN_001b8570_34:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "leal -0x40(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[pphys]\n\t"
      "flds 0x253524\n\t"
      "fcomps 0x38(%%esi)\n\t"
      "addl $0x14, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8570_35\n\t"
      "movl $0x3ecccccd, -0x18(%%ebp)\n\t"
      "jmp .LFUN_001b8570_36\n\t"
      ".LFUN_001b8570_35:\n\t"
      "movl 0x38(%%esi), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      ".LFUN_001b8570_36:\n\t"
      "movl 0x74(%%edi), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "leal 0x74(%%edi), %%ebx\n\t"
      "movl $0, -0x2c(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "jle .LFUN_001b8570_39\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_001b8570_37:\n\t"
      "pushl $0x80\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $-1, 0x20(%%eax)\n\t"
      "je .LFUN_001b8570_38\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "imull $0x130, %%edi, %%edi\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "testb $0x10, (%%edi,%%ecx,1)\n\t"
      "je .LFUN_001b8570_38\n\t"
      "incl -0x30(%%ebp)\n\t"
      ".LFUN_001b8570_38:\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "movswl %%ax, %%edi\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "cmpl (%%ebx), %%edi\n\t"
      "jl .LFUN_001b8570_37\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_001b8570_39\n\t"
      "movswl -0x30(%%ebp), %%edx\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "fildl -0x34(%%ebp)\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "fidivl -0x34(%%ebp)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      ".LFUN_001b8570_39:\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b8570_40\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_001b8570_41\n\t"
      ".LFUN_001b8570_40:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8570_41\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_001b8570_41:\n\t"
      "fld %%st(0)\n\t"
      "fsubs 0x444(%%esi)\n\t"
      "fcoms 0x25496c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_001b8570_42\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x444(%%esi)\n\t"
      "fadds 0x25496c\n\t"
      "jmp .LFUN_001b8570_43\n\t"
      ".LFUN_001b8570_42:\n\t"
      "fcomps 0x25e884\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001b8570_43\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x444(%%esi)\n\t"
      "fsubs 0x25496c\n\t"
      ".LFUN_001b8570_43:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "fstps 0x444(%%esi)\n\t"
      "pushl %%ecx\n\t"
      "call *%[b7020]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [mag] "m"(b8570_mag), [norm] "m"(b8570_norm), [a57b0] "m"(b8570_a57b0), [mscale] "m"(b8570_mscale), [m3x3v] "m"(b8570_m3x3v), [m4x3] "m"(b8570_m4x3), [get] "m"(b8570_get), [pphys] "m"(b8570_pphys), [f8510] "m"(b8570_f8510), [elem] "m"(b8570_elem), [b7020] "m"(b8570_b7020), [tag] "m"(b8570_tag)
      : "memory");
}
#else
void FUN_001b8570(int object_handle, float dt, void *contact_buf,
                  void *wheel_buf)
{
  char *veh;
  char *vehi;
  char *phys;
  float *global_vel;
  float mass;
  float gravity_scale;
  float force_a[3];
  float force_b[3];
  float matrix[12];
  float transformed[3];
  float air_speed;
  int contact_count;
  int i;
  int grounded;
  int flagged;
  float ground_frac;
  float target;
  float delta;

  veh = (char *)object_get_and_verify_type(object_handle, 2);
  vehi = (char *)tag_get(0x76656869, *(int *)veh);
  phys = (char *)tag_get(0x70687973, *(int *)(vehi + 0x8c));
  gravity_scale = FUN_0018f510(veh + 0x48, veh + 0xc);

  global_vel = *(float **)0x31fc38;
  force_a[0] = global_vel[0];
  force_a[1] = global_vel[1];
  force_a[2] = global_vel[2];
  force_b[0] = global_vel[0];
  force_b[1] = global_vel[1];
  force_b[2] = global_vel[2];
  mass = *(float *)(veh + 0x2e8);

  contact_count = *(int *)(phys + 0x68);
  for (i = 0; i < contact_count; i++) {
    char *slot = (char *)contact_buf + i * 0x60;
    *(float *)(slot + 0x18) = mass;
    *(int *)(slot + 0x1c) = 0;
    *(int *)(slot + 0x20) = 0;
    *(int *)(slot + 0x24) = 0;
    *(int *)(slot + 0x28) = 0x3f800000;
  }

  /* Full aero/ground forces only when gravity_scale < 0.5 and up.z > -0.2. */
  if (gravity_scale < *(float *)0x253398 &&
      *(float *)(veh + 0x38) > *(float *)0x255ba4) {
    matrix4x3_from_forward_up_position(matrix, (float *)(veh + 0xc),
                                       (float *)(veh + 0x24),
                                       (float *)(veh + 0x30));
    real_matrix3x3_transform_vector(matrix, (vector3_t *)(veh + 0x18),
                                    (vector3_t *)transformed);

    if (*(float *)(veh + 0x444) > 0.0f) {
      float max_speed = *(float *)(vehi + 0x2f8);
      float scale = *(float *)(vehi + 0x300);
      float lateral[3];

      if ((*(unsigned char *)(veh + 0x424) & 8) != 0)
        max_speed *= *(float *)0x2533f0;

      lateral[0] = max_speed * *(float *)(veh + 0x228) - transformed[0];
      lateral[1] = max_speed * *(float *)(veh + 0x22c) - transformed[1];
      lateral[2] = 0.0f;

      if ((unsigned char)*(veh + 0x42b) > 0 &&
          fabsf(dt) > *(double *)0x25b3f0) {
        float fade =
            (float)(unsigned char)*(veh + 0x42b) * *(float *)0x2533e8;
        if (fade > *(float *)0x291060)
          fade = *(float *)0x291060;
        scale *= (1.0f - fade);
      }
      FUN_000a57b0(lateral, scale);
      matrix_scale_transform_vector(matrix, lateral, lateral);
      {
        float thrust = *(float *)(phys + 8) * *(float *)(veh + 0x444);
        force_a[0] += lateral[0] * thrust;
        force_a[1] += lateral[1] * thrust;
        force_a[2] += lateral[2] * thrust;
      }
    }

    if (*(float *)(veh + 0x444) > 0.0f) {
      float *up = (float *)(veh + 0x30);
      float ground_speed = up[0] * *(float *)(veh + 0x3c) +
                           up[1] * *(float *)(veh + 0x40) +
                           up[2] * *(float *)(veh + 0x44);
      int sign;
      float lift;

      if (dt == 0.0f)
        sign = 0;
      else if (dt < 0.0f)
        sign = -1;
      else
        sign = 1;
      lift = fabsf(dt) * sqrtf(*(double *)0x2b7d68) * (float)sign;
      if (fabsf(lift) > *(double *)0x2533d0 &&
          dt / lift < *(float *)0x253f40)
        lift = dt * *(float *)0x253398;
      lift = ground_speed - lift;
      if (lift < *(float *)0x2b7d60)
        lift = *(float *)0x2b7d60;
      else if (!(lift <= *(float *)0x2b7d5c))
        lift = *(float *)0x2b7d5c;
      lift *= *(float *)(phys + 0x58) * *(float *)(veh + 0x444);
      force_b[0] += up[0] * lift;
      force_b[1] += up[1] * lift;
      force_b[2] += up[2] * lift;
    }

    /* Air/partial-ground control: steer into force_b while ground_frac < 1. */
    if (*(float *)(veh + 0x444) < *(float *)0x2533c8) {
      float *forward = (float *)(veh + 0x24);
      float *up = (float *)(veh + 0x30);
      float side[3];
      float turn[3];
      float *plane = *(float **)0x31fc08;
      float air_force[3];
      float sx, sy, air_blend, yaw_scale;

      side[0] = forward[2] * up[1] - forward[1] * up[2];
      side[1] = forward[0] * up[2] - forward[2] * up[0];
      side[2] = forward[1] * up[0] - forward[0] * up[1];
      turn[0] = up[2] * forward[1] - up[1] * forward[2];
      turn[1] = up[0] * forward[2] - up[2] * forward[0];
      turn[2] = up[1] * forward[0] - up[0] * forward[1];
      (void)magnitude3d(side);
      (void)magnitude3d(turn);

      air_force[0] = plane[0];
      air_force[1] = plane[1];
      air_force[2] = 0.0f;

      if (*(float *)(veh + 0x38) > 0.0f) {
        float fwd_dot = forward[0] * *(float *)(veh + 0x3c) +
                        forward[1] * *(float *)(veh + 0x40);
        float side_dot = side[0] * *(float *)(veh + 0x3c) +
                         side[1] * *(float *)(veh + 0x40);
        float corr_x = side[0] * *(float *)(veh + 0x3c) +
                       side[1] * *(float *)(veh + 0x40);
        float corr_y = -(forward[0] * *(float *)(veh + 0x3c) +
                         forward[1] * *(float *)(veh + 0x40));
        float dx = plane[0] - fwd_dot;
        float dy = plane[1] - side_dot;
        dx -= corr_x * *(float *)0x254cc0;
        dy -= corr_y * *(float *)0x254cc0;
        sx = dx * *(float *)(veh + 0x228);
        sy = dy * *(float *)(veh + 0x22c);
        if (sx < 0.0f)
          sx = -fabsf(dx);
        else if (sx > 0.0f)
          sx = fabsf(dx);
        else
          sx = 0.0f;
        if (sy < 0.0f)
          sy = -fabsf(dy);
        else if (sy > 0.0f)
          sy = fabsf(dy);
        else
          sy = 0.0f;
        sx = sx + 1.0f;
        if (sx < *(float *)0x2533e4)
          sx = *(float *)0x2533e4;
        else if (sx > *(float *)0x254e04)
          sx = *(float *)0x254e04;
        sy = sy + 1.0f;
        if (sy < *(float *)0x2533e4)
          sy = *(float *)0x2533e4;
        else if (sy > *(float *)0x254e04)
          sy = *(float *)0x254e04;
        air_force[0] += sx * *(float *)(veh + 0x228) * *(float *)0x2b7d58;
        air_force[1] += sy * *(float *)(veh + 0x22c) * *(float *)0x2b7d58;
        air_blend = (1.0f - *(float *)(veh + 0x38)) * *(float *)0x2b7d54;
        air_force[0] += air_blend * dx;
        air_force[1] += air_blend * dy;
      } else {
        air_force[0] += *(float *)(veh + 0x228) * *(float *)0x2b7d58;
        air_force[1] += *(float *)(veh + 0x22c) * *(float *)0x2b7d58;
      }

      {
        float *grav = *(float **)0x31fc38;
        float torque = *(float *)(phys + 0x54);
        air_force[0] = grav[0] + side[0] * air_force[0] * torque;
        air_force[1] = grav[1] + side[1] * air_force[1] * torque;
        air_force[2] = grav[2] + side[2] * air_force[2] * torque;
        yaw_scale = -air_force[0] * *(float *)(phys + 0x50);
        /* reuse turn as yaw axis contribution onto air_force */
        air_force[0] += forward[0] * yaw_scale;
        air_force[1] += forward[1] * yaw_scale;
        air_force[2] += forward[2] * yaw_scale;
        air_blend = 1.0f - *(float *)(veh + 0x444);
        force_b[0] += air_force[0] * air_blend;
        force_b[1] += air_force[1] * air_blend;
        force_b[2] += air_force[2] * air_blend;
      }
    }

    /* Banked-flight extra forces when vehicle flags bit 3 set. */
    if ((*(unsigned char *)(veh + 0x424) & 8) != 0) {
      float *forward = (float *)(veh + 0x24);
      float *up = (float *)(veh + 0x30);
      float *world_up = *(float **)0x31fc44;
      float side[3];
      float speed_frac;
      float bank;

      speed_frac = (forward[0] * *(float *)(veh + 0x18) +
                    forward[1] * *(float *)(veh + 0x1c) +
                    forward[2] * *(float *)(veh + 0x20)) /
                   *(float *)(vehi + 0x2f8);
      if (speed_frac < 0.0f)
        speed_frac = 0.0f;
      else if (speed_frac > 1.0f)
        speed_frac = 1.0f;

      side[0] = up[1] * forward[2] - up[2] * forward[1];
      side[1] = up[2] * forward[0] - up[0] * forward[2];
      side[2] = up[0] * forward[1] - up[1] * forward[0];

      if (speed_frac > 0.0f) {
        bank = *(float *)(phys + 0x54) * *(float *)(veh + 0x444) * speed_frac *
               *(float *)0x2b7d50;
        force_b[0] += side[0] * bank;
        force_b[1] += side[1] * bank;
        force_b[2] += side[2] * bank;
        bank = *(float *)(phys + 8) * *(float *)(veh + 0x444) * speed_frac *
               *(float *)0x2b7d4c;
        force_a[0] += world_up[0] * bank;
        force_a[1] += world_up[1] * bank;
        force_a[2] += world_up[2] * bank;
      }

      if ((unsigned char)*(veh + 0x428) > 0) {
        float lateral[3];
        float fade;
        lateral[0] = side[1] * world_up[2] - side[2] * world_up[1];
        lateral[1] = side[2] * world_up[0] - side[0] * world_up[2];
        lateral[2] = side[0] * world_up[1] - side[1] * world_up[0];
        if (normalize3d(lateral) > 0.0f) {
          fade = 1.0f - (float)(unsigned char)*(veh + 0x428) *
                            *(float *)0x2546a4;
          if (fade < 0.0f)
            fade = 0.0f;
          else if (fade > 1.0f)
            fade = 1.0f;
          bank = (1.0f - *(float *)(veh + 0x444)) * *(float *)(phys + 8) *
                 fade * *(float *)0x2b7d48;
          force_a[0] += lateral[0] * bank;
          force_a[1] += lateral[1] * bank;
          force_a[2] += lateral[2] * bank;
          bank = (1.0f - *(float *)(veh + 0x444)) * *(float *)(phys + 8) *
                 fade * *(float *)0x255ef8;
          force_a[0] += world_up[0] * bank;
          force_a[1] += world_up[1] * bank;
          force_a[2] += world_up[2] * bank;
        }
      }
    }

    force_a[0] *= mass;
    force_a[1] *= mass;
    force_a[2] *= mass;
    force_b[0] *= mass;
    force_b[1] *= mass;
    force_b[2] *= mass;
  }

  FUN_00154270(object_handle, contact_buf, wheel_buf, force_a, force_b);

  /* Ground-fraction from powered wheels (phys mass points with marker != -1). */
  grounded = 0;
  flagged = 0;
  ground_frac = 0.0f;
  air_speed = (*(float *)(veh + 0x38) < *(float *)0x253524)
                  ? 0.4f
                  : *(float *)(veh + 0x38);
  {
    int wheel_count = *(int *)(phys + 0x74);
    for (i = 0; i < wheel_count; i++) {
      char *mass_point =
          (char *)tag_block_get_element(phys + 0x74, i, 0x80);
      if (*(int16_t *)(mass_point + 0x20) == (int16_t)-1)
        continue;
      grounded++;
      if ((((char *)wheel_buf)[i * 0x130] & 0x10) != 0)
        flagged++;
    }
    if (grounded > 0)
      ground_frac = (float)flagged / (float)grounded;
  }

  target = ground_frac * air_speed;
  if (target < 0.0f)
    target = 0.0f;
  else if (target > 1.0f)
    target = 1.0f;
  delta = target - *(float *)(veh + 0x444);
  if (delta > *(float *)0x25496c)
    *(float *)(veh + 0x444) += *(float *)0x25496c;
  else if (!(delta >= *(float *)0x25e884))
    *(float *)(veh + 0x444) -= *(float *)0x25496c;
  else
    *(float *)(veh + 0x444) = target;

  FUN_001b7020(object_handle);
}
#endif

