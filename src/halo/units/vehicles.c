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

/* 0x1b4dc0 */
void FUN_001b4dc0(int handle, void *damage_data, unsigned int flags, float body_vitality, float shield_vitality, int param_6, int param_7)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;
  int local_10 = 0;
  int local_14 = 0;
  int local_18 = 0;
  int local_1c = 0;
  int local_20 = 0;
  int local_4 = 0;
  int local_8 = 0;

  object_get_and_verify_type(handle, 3);
  tag_get('tinu', *(int *)(eax));
  tag_get('!tpj', *(int *)(damage_data));
  /* relift: relift: mov (char)eax, byte ptr [0x5054f9] */
  /* relift: cmp dword ptr [esi + 0x1c8], -1 -> je 0x1b4ebe */
  object_get_and_verify_type(0, -1);
  tag_get('ejbo', *(int *)(eax));
  strrchr((const char *)(uintptr_t)*(int *)((char *)eax + 0x2c), 92);
  /* test eax, eax -> je 0x1b4e6b */
  /* cmp eax, -1 -> je 0x1b4e8a */
  tag_get_name(*(int *)(damage_data));
  strrchr((char *)(uintptr_t)eax, 92);
  /* test eax, eax -> je 0x1b4e8a */
  console_printf(0, (char *)0x002b7cac);
  /* test (char)eax, 0x41 -> jne 0x1b4f19 */
  /* cmp eax, -1 -> je 0x1b4f1b */
  /* test (char)ecx, 0x10 -> je 0x1b4f4f */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test dl, dl -> je 0x1b4f6d */
  /* relift: relift: fcomp dword ptr [0x253f40] */
  /* test (char)eax, 1 -> je 0x1b4f71 */
  /* test dl, dl -> jne 0x1b504e */
  /* test (char)ecx, 0x20 -> je 0x1b504e */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b504e */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b504e */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b504e */
  /* test (char)eax, 0x41 -> jne 0x1b504e */
  FUN_000121e0(0.0f, 0.0f);
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x1b501d */
  /* relift: relift: fld dword ptr [0x2533c8] */
  FUN_001d9068();
  display_assert((char *)0x002b7ac8, (char *)0x002b68c0, 4740, 1);
  system_exit(-1);
  /* relift: test byte ptr [edi + 4], 0x10 -> jne 0x1b5167 */
  /* test (char)eax, (char)eax -> jne 0x1b5073 */
  /* test (char)eax, (char)eax -> jne 0x1b5073 */
  /* relift: test byte ptr [esi + 0xb6], 4 -> jne 0x1b5167 */
  /* relift: test dword ptr [esi + 0x1b4], 0x800000 -> jne 0x1b5167 */
  /* relift: test byte ptr [edx + 4], 0x10 -> jne 0x1b5167 */
  magnitude3d((void *)0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b5100 */
  magnitude3d((void *)0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b5100 */
  FUN_0010c3c0();
  /* relift: test byte ptr [eax + 4], 4 -> jne 0x1b511a */
  /* test (char)eax, (char)eax -> jbe 0x1b5128 */
  /* relift: test byte ptr [ebp + 0x10], 0x8a -> je 0x1b5132 */
  FUN_001b1400(handle, local_4, local_8, local_1c, local_10, local_18, local_14, param_7, handle);
  /* cmp ecx, -1 -> je 0x1b5191 */
  game_engine_player_damaged_player(0, 0, flags);
  /* cmp eax, -1 -> jne 0x1b519e */
  /* relift: cmp dword ptr [edi + 0xc], eax -> je 0x1b51c5 */
  unit_record_damage(handle, local_20, 0, local_4, 0, 0, 0);
  /* relift: test byte ptr [edi + 4], 0x10 -> jne 0x1b521a */
  /* test (char)ecx, 1 -> jne 0x1b51f3 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x1b51f3 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b521a */
  FUN_001a71c0(handle, (void *)(uintptr_t)damage_data, 0, 0, 0.0f);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x1b523a */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b5243 */
  unit_reset_weapon_state(handle);
  /* relift: cmp word ptr [esi + 0x64], 0 -> jne 0x1b5294 */
  /* test (char)eax, (char)eax -> je 0x1b526a */
  ai_handle_death(handle, 0, 0);
  /* relift: test byte ptr [esi + 0xb6], 4 -> jne 0x1b5294 */
  ai_handle_damage(0, 0, 0, 0.0f, 0, 0);
  /* relift: cmp dword ptr [esi + 0x1c8], -1 -> je 0x1b53d1 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b53d1 */
  game_engine_running();
  /* test (char)eax, (char)eax -> jne 0x1b52ce */
  /* relift: relift: mov (char)eax, byte ptr [0x5054f8] */
  /* test (char)eax, (char)eax -> je 0x1b53d1 */
  game_globals_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x1b533f */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x1b536c */
  /* test (char)eax, 0x41 -> jne 0x1b536c */
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();
  /* relift: cmp word ptr [esi + 0x3d8], (int16_t)edi -> jge 0x1b53b3 */
  /* test (char)eax, (char)eax -> jne 0x1b53df */
  /* test (char)eax, (char)eax -> je 0x1b53ec */
  unit_died(handle, local_8);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
  (void)local_10;
  (void)local_14;
  (void)local_18;
  (void)local_1c;
  (void)local_20;
  (void)local_4;
  (void)local_8;
}

/* 0x1b5400 */
int FUN_001b5400(int a0, int a1)
{
  int eax = 0;
  int ebx = 0;
  int edi = 0;
  int local_c = 0;

  object_get_and_verify_type(a0, 3);
  tag_get('tinu', *(int *)(eax));
  /* test eax, eax -> je 0x1b544f */
  csstrlen((char *)(uintptr_t)a1);
  /* test eax, eax -> je 0x1b544f */
  object_iterator_new((void *)0, 3, 0);
  object_iterator_next((void *)0);
  /* test eax, eax -> je 0x1b54f0 */
  /* relift: cmp dword ptr [eax + 0xcc], edi -> jne 0x1b54e0 */
  tag_block_get_element((void *)((char *)eax + 0x2e4), eax, 284);
  csstrcpy((void *)0, (char *)(uintptr_t)eax);
  csstr_tolower((void *)0);
  /* test (char)ebx, (char)ebx -> jne 0x1b54cd */
  crt_strstr((void *)0, (char *)(uintptr_t)a1);
  /* test eax, eax -> je 0x1b54e0 */
  unit_try_and_exit_seat(local_c);
  /* test (char)eax, (char)eax -> je 0x1b54e0 */
  object_iterator_next((void *)0);
  /* test eax, eax -> jne 0x1b5472 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)edi;
  (void)local_c;
}

/* 0x1b5500 */
void FUN_001b5500(int a0)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* cmp esi, -1 -> je 0x1b5535 */
  object_get_and_verify_type(a0, 3);
  /* cmp ecx, -1 -> je 0x1b5535 */
  /* relift: cmp word ptr [eax + 0x2a0], -1 -> je 0x1b5535 */
  unit_try_and_exit_seat(a0);

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x1b5580 */
void vehicle_causes_collision_damage(void)
{
  unit_place(0, (void *)0);
  FUN_0013d870(0, (void *)0);
}

/* 0x1b55c0 */
void vehicle_hover(void)
{
  object_get_and_verify_type(0, 0);
  tag_get('ihev', 0);
}

/* 0x1b5610 */
void FUN_001b5610(int a0, int a1)
{
  int eax = 0;
  int edi = 0;

  /* cmp edi, -1 -> je 0x1b5654 */
  object_get_and_verify_type(a0, 2);
  /* test (char)eax, (char)eax -> je 0x1b564c */
  object_get_world_position(a0, (vector3_t *)((char *)eax + 0x454));
  FUN_00154270();

  (void)eax;
  (void)edi;
}

/* 0x1b5680 */
void vehicle_is_flipped(void)
{
  object_get_and_verify_type(0, 0);
}

/* 0x1b56b0 */
void FUN_001b56b0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;

  object_get_and_verify_type(eax, 2);
  tag_get('ihev', *(int *)(eax));
  tag_get('syhp', 0);
  /* cmp (char)ecx, 0xff -> jae 0x1b56f0 */
  /* cmp ecx, ebx -> jle 0x1b5723 */
  /* test (char)ecx, 2 -> jne 0x1b572c */
  /* test (char)ecx, 0x10 -> je 0x1b571a */
  /* relift: cmp ecx, dword ptr [eax + 0x74] -> jl 0x1b5700 */

  (void)eax;
  (void)ebx;
  (void)ecx;
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

/* 0x1b5890 */
void vehicle_preprocess_node_orientations(void)
{
  int eax = 0;
  int ecx = 0;
  int edi = 0;
  int local_8 = 0;

  object_get_and_verify_type(0, 2);
  tag_get('ihev', *(int *)(eax));
  /* cmp eax, -1 -> je 0x1b5c85 */
  tag_get('rtna', 0);
  /* test ecx, ecx -> je 0x1b5c83 */
  tag_block_get_element((void *)((char *)eax + 0x24), 0, 116);
  /* test edi, edi -> je 0x1b5c83 */
  /* test eax, eax -> jle 0x1b5939 */
  /* cmp (int16_t)eax, 0xffff -> je 0x1b5939 */
  tag_block_get_element((void *)((char *)eax + 0x74), 0, 180);
  FUN_00122e50(eax, (float *)0, 0.0f, 0.0f, 0);
  /* relift: cmp dword ptr [edi + 0x5c], 1 -> jle 0x1b59e1 */
  /* cmp (int16_t)eax, 0xffff -> je 0x1b59e1 */
  tag_block_get_element((void *)((char *)eax + 0x74), eax, 180);
  triple_product3d((float *)((char *)eax + 0x30), (float *)((char *)eax + 0x24), (float *)((char *)eax + 0x18));
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b59be */
  /* relift: relift: fld dword ptr [0x2533c8] */
  FUN_00122690((void *)0, 0.0f, (void *)0);
  /* relift: cmp dword ptr [edi + 0x5c], 2 -> jle 0x1b5a74 */
  /* cmp (int16_t)eax, 0xffff -> je 0x1b5a74 */
  tag_block_get_element((void *)((char *)eax + 0x74), eax, 180);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  FUN_00122690((void *)0, 0.0f, (void *)0);
  /* relift: cmp dword ptr [edi + 0x5c], 3 -> jle 0x1b5b41 */
  /* cmp (int16_t)eax, 0xffff -> je 0x1b5b41 */
  tag_block_get_element((void *)((char *)eax + 0x74), 0, 180);
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b5ae8 */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b5b21 */
  /* relift: relift: fld dword ptr [0x2533c8] */
  FUN_00122690((void *)0, 0.0f, (void *)0);
  /* relift: cmp dword ptr [edi + 0x5c], 4 -> jle 0x1b5b69 */
  /* cmp (int16_t)eax, 0xffff -> je 0x1b5b69 */
  tag_block_get_element((void *)((char *)eax + 0x74), eax, 180);
  /* relift: cmp dword ptr [edi + 0x5c], 5 -> jle 0x1b5bdc */
  /* cmp (int16_t)eax, 0xffff -> je 0x1b5bdc */
  tag_block_get_element((void *)((char *)eax + 0x74), eax, 180);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b5bb7 */
  /* relift: relift: fld dword ptr [0x2533c0] */
  FUN_00122690((void *)0, 0.0f, (void *)0);
  tag_block_get_element((void *)(uintptr_t)local_8, 0, 20);
  /* cmp (int16_t)eax, 0xffff -> je 0x1b5c6e */
  tag_block_get_element((void *)((char *)eax + 0x74), eax, 180);
  /* cmp (char)ecx, 0xff -> jne 0x1b5c3f */
  /* relift: relift: fld dword ptr [0x2533c8] */
  FUN_00122690((void *)0, 0.0f, (void *)0);
  /* relift: cmp edi, dword ptr [eax] -> jl 0x1b5bf8 */

  (void)eax;
  (void)ecx;
  (void)edi;
  (void)local_8;
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
  FUN_00154270();
  FUN_00154270();
}

/* 0x1b6140 */
void FUN_001b6140(void)
{
  object_get_and_verify_type(0, 0);
  tag_get('ihev', 0);
  tag_get('syhp', 0);
  FUN_001daf7e();
  FUN_00154270();
  FUN_00154270();
}

/* 0x1b6250 */
void FUN_001b6250(void)
{
  int eax = 0;

  object_get_and_verify_type(0, 2);
  tag_get('ihev', *(int *)(eax));
  tag_get('syhp', 0);
  /* test (char)eax, 0x41 -> jne 0x1b62e2 */
  /* relift: relift: fld dword ptr [0x2533c8] */
  normalize3d((float *)0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  rotate_vector3d_by_sincos((void *)0, (float *)((char *)eax + 0x24), 0.0f, 0.0f);
  FUN_0010c510((void *)0, (float *)((char *)eax + 0x30));
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b6464 */
  /* relift: relift: fld dword ptr [0x2b7ce4] */
  /* test (char)eax, 0x41 -> jne 0x1b64eb */
  /* relift: relift: fld dword ptr [0x2b7ce0] */
  FUN_00154270();
  FUN_00154270();

  (void)eax;
}

/* 0x1b6560 */
void FUN_001b6560(void)
{
  int eax = 0;

  object_get_and_verify_type(0, 2);
  tag_get('ihev', *(int *)(eax));
  tag_get('syhp', 0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b65e8 */
  FUN_001b5f20();
  FUN_0010a2c0((float *)0, (float *)0, (float *)0);
  normalize3d((float *)0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  FUN_001aa4d0(0);
  /* test (char)eax, (char)eax -> jne 0x1b670e */
  FUN_0010c700((void *)0, (void *)0, 0.0f, 0.0f);
  FUN_0010c690((void *)0, (void *)0, 0.0f, 0.0f);
  FUN_001099f0((float *)0, (float *)0);
  FUN_00109c70((void *)0, (void *)0, (void *)0);
  FUN_0010a330((void *)0, (void *)0);
  FUN_0010caf0((void *)0, (void *)0, (void *)0);
  /* test (char)eax, 0x41 -> jne 0x1b68c6 */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x25bb10] */
  /* test (char)eax, 0x41 -> jne 0x1b68af */
  /* relift: relift: fld dword ptr [0x2533e8] */
  /* test (char)eax, 0x41 -> je 0x1b6907 */
  /* test (char)eax, 0x41 -> je 0x1b68eb */
  /* relift: relift: fld dword ptr [0x29d9ac] */
  /* test (char)eax, 0x41 -> jne 0x1b6907 */
  FUN_00154270();
  FUN_00154270();

  (void)eax;
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
  FUN_00154270();
  FUN_00154270();

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

/* 0x1b79c0 */
void vehicle_export_function_values(void)
{
  int eax = 0;

  object_get_and_verify_type(0, 2);
  tag_get('ihev', *(int *)(eax));
  /* test (char)eax, 0x41 -> jne 0x1b7a13 */
  /* test (char)eax, 0x41 -> jne 0x1b7a44 */
  /* test (char)eax, 0x41 -> jne 0x1b7a75 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x1b7e28 */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* cmp eax, 0x23 -> ja 0x1b7e23 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b7b1f */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x1b7df7 */
  /* test (char)eax, 4 -> jne 0x1b7e1d */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* test (char)eax, 8 -> jne 0x1b7e1d */
  /* relift: relift: fld dword ptr [0x2533c0] */
  FUN_00012fe0((float *)((char *)eax + 0x18));
  /* test (char)eax, 0x1c -> je 0x1b7e06 */
  FUN_00012fe0((float *)((char *)eax + 0x18));
  /* test (char)eax, 2 -> je 0x1b7e06 */
  FUN_00012fe0((float *)((char *)eax + 0x18));
  FUN_0010b8a0((float *)((char *)eax + 0x18), (float *)((char *)eax + 0x24), (void *)0, (void *)0);
  FUN_00012fe0((void *)0);
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b7dbf */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  FUN_00012fe0((float *)((char *)eax + 0x18));
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1b7e23 */
  /* relift: relift: fld dword ptr [0x2533c8] */

  (void)eax;
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
