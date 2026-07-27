#include "x87_math.h"

/* FUN_0002a3a0 (0x2a3a0) — readable C lift. */
void FUN_0002a3a0(int actor_handle)
{
  char *actor;

  actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  actor[0x4a8] = 0;
  actor[0x484] = 1;
  *(int *)(actor + 0x4a0) = 0;
}

/* actor_path_input_new (0x2a470) — readable C lift. */
void actor_path_input_new(int actor_handle, char *nav_state_out)
{
  char *actor;
  char *actor_tag;
  char *vehicle_tag;
  unsigned int radius;
  int unit_handle;

  actor = (char *)datum_get(actor_data, actor_handle);
  actor_tag = (char *)tag_get(0x61637472, *(int *)(actor + 0x58));
  radius = *(unsigned int *)(actor_tag + 0x8c);
  unit_handle = *(int *)(actor + 0x18);
  if (*(int16_t *)(actor + 0x15e) > 0) {
    char *vehicle = (char *)object_get_and_verify_type(*(int *)(actor + 0x158), 2);
    vehicle_tag = (char *)tag_get(0x76656869, *(int *)vehicle);
    unit_handle = *(int *)(actor + 0x158);
    if (*(float *)(vehicle_tag + 0x38c) > *(float *)0x2533c0)
      radius = *(unsigned int *)(vehicle_tag + 0x38c);
  }
  actor_find_pathfinding_location(actor_handle);
  path_input_new(nav_state_out, radius, (unsigned char)actor[0x376], unit_handle);
  path_input_set_start(nav_state_out, (float *)(actor + 0x168), *(int *)(actor + 0x164));
}

/* arccosine (0x2a530) — Single-precision arc cosine.
 * The original loads the float argument into ST(0) and tail-jumps to the
 * MSVC CRT acos core at 0x1d94f0 (which stores ST(0) as a double, calls the
 * x87 acos helper at 0x1dee48, then 0x1d950d, and returns the result in
 * ST(0)). Faithful equivalent is acosf(x). Confirmed by caller 0x2daa0
 * (0x2e1e1-0x2e21b): result 0 when arg >= ~1.0, PI (0x40490fdb) when
 * arg <= ~-1.0, CALL 0x1d94f0 otherwise — the defining signature of acos. */
float arccosine(float x)
{
  return acosf(x);
}

/* midpoint3d (0x2a540) — readable C lift. */
void midpoint3d(float *a, float *b, float *out)
{
  float half;

  half = *(float *)0x253398; /* 0.5f */
  out[0] = (a[0] + b[0]) * half;
  out[1] = (a[1] + b[1]) * half;
  out[2] = (a[2] + b[2]) * half;
}

/* actor_test_destination (0x2a580) — readable C lift from XBE leaf. */
char actor_test_destination(int actor_handle)
{
  char *actor;
  short mode;
  float tol;
  float dx, dy, dz;
  float dist2;

  actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  mode = *(short *)(actor + 0x46c);
  if (mode != 0 && mode != 1) {
    tol = actor_destination_tolerance(actor_handle);
    dx = *(float *)(actor + 0x488) - *(float *)(actor + 0x12c);
    dy = *(float *)(actor + 0x48c) - *(float *)(actor + 0x130);
    dz = *(float *)(actor + 0x490) - *(float *)(actor + 0x134);
    dist2 = dx * dx + dy * dy + dz * dz;
    if (dist2 > tol * tol) {
      actor[0x484] = 1;
    }
  } else {
    actor[0x484] = 1;
  }
  return actor[0x484];
}




/* actor_get_stopping_distances (0x2a610) — readable C lift (restored pre-naked) — Compute stopping distances for an
 * actor.
 *
 * Calculates two stopping-distance values based on the actor's current speed,
 * maximum speed, and deceleration sourced from the actor's biped or vehicle
 * tag.
 *
 * param_2 = out: current-speed braking distance = speed^2 / (2 * brake_decel)
 * param_3 = out: lookahead stopping distance =
 *               effective_max^2 / (2 * brake_decel)
 *             + (effective_max^2 - speed^2) / (2 * turn_decel)
 *   where effective_max = max(max_speed, current_speed)
 *
 * Confirmed: FLD float [0x255960] default max_speed; MOV [EBP-0xc]=0x3c888889
 * (turn_decel ~1/60), MOV [EBP-0x8]=0x3cda740e (brake_decel ~1/37.5).
 * Confirmed: bipd branch gated by actor[0x18]!=-1 at 0x2a6be; loads tag+0x334
 * (max), tag+0x33c (turn), tag+0x340 (brake) scaled by [0x2546a4]; conditional
 * multiplier tag+0x34c gated by actor+0x508 and FCOMP [0x2533c0] > 0.
 * Confirmed: vehicle FST/FSTP tag+0x300 stores same value to both decel slots
 * at 0x2a6b0/0x2a6b3; object_get_and_verify_type asserts, no NULL check needed.
 * Confirmed: output section NULL-checks param_2 (0x2a780) and param_3
 * (0x2a798); max(max_speed, current_speed) lives inside param_3 block only. */
void actor_get_stopping_distances(int actor_handle, float *param_2,
                                  float *param_3)
{
  char *actor;
  char *obj;
  char *tag;
  int vehicle_handle;
  int unit_handle;
  int vehicle_count;
  float max_speed;
  float turn_decel;
  float brake_decel;
  float current_speed;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  max_speed = *(float *)0x255960;
  current_speed = 0.0f;
  turn_decel = 0.016666668f;
  brake_decel = 0.026666667f;

  vehicle_handle = *(int *)(actor + 0x158);
  if (vehicle_handle != -1) {
    vehicle_count = (int)*(int16_t *)(actor + 0x15e);
    if (vehicle_count >= 2 && vehicle_count <= 3) {
      /* seated in vehicle: object_get_and_verify_type asserts, no NULL check */
      obj = (char *)object_get_and_verify_type(vehicle_handle, 2);
      tag = (char *)tag_get(0x76656869, *(int *)obj);
      /* disasm 0x2a688: FLD [ESI+0x20]*[ESI+0x2c], FLD [ESI+0x1c]*[ESI+0x28],
       * FADDP, FLD [ESI+0x18]*[ESI+0x24], FADDP */
      current_speed = *(float *)(obj + 0x20) * *(float *)(obj + 0x2c) +
                      *(float *)(obj + 0x1c) * *(float *)(obj + 0x28) +
                      *(float *)(obj + 0x18) * *(float *)(obj + 0x24);
      max_speed = *(float *)(tag + 0x2f8);
      /* FST [EBP-0xc], FSTP [EBP-0x8]: same source tag+0x300 */
      turn_decel = *(float *)(tag + 0x300);
      brake_decel = *(float *)(tag + 0x300);
    }
  } else {
    /* no vehicle: check unit handle */
    unit_handle = *(int *)(actor + 0x18);
    if (unit_handle != -1) {
      obj = (char *)object_try_and_get_and_verify_type(unit_handle, 1);
      if (obj != NULL) {
        /* tag_get called before dot product in disasm, ECX=tag at 0x2a6f1 */
        tag = (char *)tag_get(0x62697064, *(int *)obj);
        /* dot product: velocity [+0x18,+0x1c,+0x20] . facing
         * [+0x24,+0x28,+0x2c] disasm at 0x2a6eb: FLD [ESI+0x20]*[ESI+0x2c], FLD
         * [ESI+0x1c]*[ESI+0x28], FADDP, FLD [ESI+0x24]*[ESI+0x18], FADDP */
        current_speed = *(float *)(obj + 0x20) * *(float *)(obj + 0x2c) +
                        *(float *)(obj + 0x1c) * *(float *)(obj + 0x28) +
                        *(float *)(obj + 0x24) * *(float *)(obj + 0x18);
        /* bit 2 of byte at tag+0x2f4 enables custom movement params */
        if (*(unsigned char *)(tag + 0x2f4) & 4) {
          max_speed = *(float *)(tag + 0x334) * *(float *)0x2546a4;
          turn_decel = *(float *)(tag + 0x33c) * *(float *)0x2546a4;
          brake_decel = *(float *)(tag + 0x340) * *(float *)0x2546a4;
          /* conditional multiplier: only if actor[0x508] != 0 */
          if (*(unsigned char *)(actor + 0x508) != 0) {
            /* FCOMP [0x2533c0] + TEST AH,0x41: skip if multiplier <= 0 */
            if (*(float *)(tag + 0x34c) > *(float *)0x2533c0) {
              max_speed *= *(float *)(tag + 0x34c);
              turn_decel *= *(float *)(tag + 0x34c);
              brake_decel *= *(float *)(tag + 0x34c);
            }
          }
        }
      }
    }
  }

  /* param_2: braking distance from current speed; NULL-checked at 0x2a780 */
  if (param_2 != NULL) {
    *param_2 = (current_speed * current_speed) / (2.0f * brake_decel);
  }
  /* param_3: lookahead distance; NULL-checked at 0x2a798;
   * max() inside this block only (FCOMP at 0x2a79f) */
  if (param_3 != NULL) {
    if (current_speed > max_speed) {
      max_speed = current_speed;
    }
    *param_3 = (max_speed * max_speed) / (2.0f * brake_decel) +
               (max_speed * max_speed - current_speed * current_speed) /
                 (2.0f * turn_decel);
  }
}


/* actor_move_animation_impulse (0x2a7e0) — readable C lift from XBE leaf. */
int actor_move_animation_impulse(int actor_handle, int16_t param_2, int *param_3)
{
  char *actor;
  char *actor2;

  actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  actor_set_dormant(actor_handle, 0);
  actor2 = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  if (*(short *)(actor2 + 0x418) != -1) {
    return 0;
  }
  if (*(int *)(actor2 + 0x18) != -1 && unit_is_busy(*(int *)(actor2 + 0x18))) {
    return 0;
  }
  *(short *)(actor + 0x418) = param_2;
  *(int *)(actor + 0x41c) = param_3[0];
  *(int *)(actor + 0x420) = param_3[1];
  return 1;
}




/* actor_move_force_stop (0x2a860) — readable C lift from XBE leaf. */
int actor_move_force_stop(int actor_handle)
{
  char *actor;
  char *actor2;
  int *dst;
  int *src;

  actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  actor2 = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  if (*(short *)(actor2 + 0x418) != -1) {
    return 0;
  }
  if (*(int *)(actor2 + 0x18) != -1 && unit_is_busy(*(int *)(actor2 + 0x18))) {
    return 0;
  }
  if (actor_action_deny_transition(actor_handle)) {
    return 0;
  }
  actor[0x504] = 0;
  src = *(int **)0x31fc38;
  dst = (int *)(actor + 0x6e0);
  dst[0] = src[0];
  dst[1] = src[1];
  dst[2] = src[2];
  actor_unit_control_stop_animation_impulse(actor_handle);
  return 1;
}




/* actor_move_try_evasion_vector (0x2a8f0) — readable C lift (restored pre-naked) — Test whether an actor can move
 * along a candidate evasion vector and, if not, whether a half-scaled
 * collision-clearance vector is usable instead.
 *
 * Args (all cdecl stack):
 *   actor_handle   = EBP+0x08 actor datum handle
 *   evasion_vector = EBP+0x0c float[2] direction (asserted non-NULL)
 *   scale          = EBP+0x10 step length applied to evasion_vector
 *   param_4        = EBP+0x14 distance/threshold control (>= 0.0)
 *   out_flag       = EBP+0x18 optional char* out (set to local_5)
 *   result         = EBP+0x1c >=28-byte collision/path result buffer
 *                    (asserted non-NULL; FUN_00063e90 fills 7 dwords)
 *
 * Returns BL (char): 1 if a usable move/evasion vector was found, else 0.
 *
 * Confirmed: datum_get(*0x6325a4, actor_handle) at 0x2a907; tag_get('actr',
 * actor[0x58]) at 0x2a917 -> actr_tag (used only for actr_tag[0x8c]).
 * Confirmed: assert "evasion_vector && result" at 0x2a946 when
 * evasion_vector==NULL || result==NULL.
 * Confirmed: gated on actor[0x99]==0 (0x2a955); when nonzero, skips to return.
 * Confirmed: target point local[0]=scale*evasion[0]+actor[0x12c],
 * local[1]=scale*evasion[1]+actor[0x130] at 0x2a963-0x2a981 (2 floats).
 * Confirmed: actor_find_pathfinding_location(actor_handle) at 0x2a984.
 * Confirmed: 9-arg FUN_00063e90(scenario_get(), (u8)actor[0x376],
 * (float*)actor[0x168], actor[0x164], &local_target, -1, actr_tag[0x8c], 0,
 * result) at 0x2a9bf — Ghidra mis-grouped the 8 pushes onto the inner
 * zero-arg scenario_get(); cleanup ADD ESP,0x24=36=9 cdecl args proves it.
 * Confirmed: when that returns 0, set found=1; fVar1=result[3]-actor[0x134];
 * keep found=1 iff (fVar1 <= scale*0.5) && (param_4 != 0.0 ||
 * scale*-0.5 <= fVar1) (FCOMP polarity at 0x2a9d3-0x2aa1d).
 * Confirmed: clearance fallback only when param_4 > 0.0 (0x2aa1f-0x2aa2d).
 *   origin   = ((actor[0x120]+actor[0x12c])*0.5, (actor[0x124]+actor[0x130])
 *               *0.5, (actor[0x128]+actor[0x134])*0.5)
 *   direction= (scale*evasion[0], scale*evasion[1], 0.0)
 * Confirmed: collision_bsp_test_vector(3, global_collision_bsp_get(), 0, 0,
 * &origin, &direction, 0x7f7fffff(FLT_MAX), col_result) at 0x2aaad.
 * Miss (0) => found=1,
 * local_5=1; if param_4 < FLT_MAX, build a half-clearance segment via
 * vector3d_scale_add(&origin, &direction, 1.0, seg_a) and
 * FUN_00012fb0(*(float**)0x31fc50, param_4, seg_b), retest; a hit there
 * clears found back to 0 (0x2aab9-0x2ab24).
 * Confirmed: out_flag NULL-checked at 0x2ab2b; *out_flag=local_5. */
char actor_move_try_evasion_vector(int actor_handle, float *evasion_vector,
                                   float scale, float param_4, char *out_flag,
                                   void *result)
{
  char *actor;
  char *actr_tag;
  float local_target[2];
  float origin[3];
  float direction[3];
  float seg_a[3];
  float seg_b[3];
  int bsp;
  float col_result[264];
  float fVar1;
  char found;
  char local_5;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  actr_tag = (char *)tag_get(0x61637472, *(int *)(actor + 0x58));
  found = 0;
  local_5 = 0;

  if (evasion_vector == (float *)0x0 || result == (void *)0x0) {
    display_assert("evasion_vector && result",
                   "c:\\halo\\SOURCE\\ai\\actor_moving.c", 0x484, 1);
    system_exit(-1);
  }

  if (*(char *)(actor + 0x99) == '\0') {
    local_target[0] = scale * evasion_vector[0] + *(float *)(actor + 0x12c);
    local_target[1] = scale * evasion_vector[1] + *(float *)(actor + 0x130);
    actor_find_pathfinding_location(actor_handle);
    if (FUN_00063e90((int)scenario_get(), *(unsigned char *)(actor + 0x376),
                     (float *)(actor + 0x168), *(int *)(actor + 0x164),
                     local_target, 0xffffffff, *(float *)(actr_tag + 0x8c), 0,
                     (unsigned int *)result) == '\0') {
      found = 1;
      fVar1 = *(float *)((char *)result + 0xc) - *(float *)(actor + 0x134);
      if (!(fVar1 > scale * *(float *)0x253398) &&
          (param_4 != *(float *)0x2533c0 ||
           scale * *(float *)0x255964 <= fVar1)) {
        goto done;
      }
    }
    found = 0;
    if (*(float *)0x2533c0 < param_4) {
      bsp = (int)global_collision_bsp_get();
      origin[0] = (*(float *)(actor + 0x120) + *(float *)(actor + 0x12c)) *
                  *(float *)0x253398;
      origin[1] = (*(float *)(actor + 0x124) + *(float *)(actor + 0x130)) *
                  *(float *)0x253398;
      origin[2] = (*(float *)(actor + 0x128) + *(float *)(actor + 0x134)) *
                  *(float *)0x253398;
      direction[0] = scale * evasion_vector[0];
      direction[1] = scale * evasion_vector[1];
      direction[2] = 0.0f;
      if (collision_bsp_test_vector(3, bsp, 0, 0, (int)origin, (int)direction,
                                    3.4028235e+38f, col_result) == '\0') {
        found = 1;
        local_5 = 1;
        if (param_4 < *(float *)0x2548fc) {
          vector3d_scale_add(origin, direction, 1.0f, seg_a);
          FUN_00012fb0(*(float **)0x31fc50, param_4, seg_b);
          if (collision_bsp_test_vector(3, bsp, 0, 0, (int)seg_a, (int)seg_b,
                                        3.4028235e+38f, col_result) == '\0') {
            found = 0;
          }
        }
      }
    }
  }

done:
  if (out_flag != (char *)0x0) {
    *out_flag = local_5;
  }
  return found;
}


/* actor_move_try_evasion_direction (0x2ab40) — readable C lift (restored pre-naked) — Try one perpendicular evasion
 * direction (and its mirror) derived from the alignment vector.
 *
 * Builds a 2D evade vector from alignment_vector according to the requested
 * reference mode (*evade_direction_reference), then delegates the actual
 * feasibility test to actor_move_try_evasion_vector (0x2a8f0) for each of the
 * candidate directions. On the first feasible candidate the chosen direction
 * index is written back to *evade_direction_reference and 1 is returned. If no
 * candidate is feasible, 0xffff is written back and 0 is returned.
 *
 * Confirmed: datum_get(*0x6325a4, actor_handle) at 0x2ab49-0x2ab54 (only its
 * side effect / handle validation; result unused).
 * Confirmed: assert "alignment_vector && evade_direction_reference && result"
 * at 0x2ab78-0x2ab89 when any of param_2/param_4/param_7 is NULL.
 * Confirmed: switch on (short)*evade_direction_reference (MOVSX, jump table at
 * 0x2acc4), cases 0-4, default asserts at 0x2ac3a (line 0x508).
 *   case 0: evade[0]=-v[1], evade[1]= v[0], index unchanged, count=1.
 *   case 1: evade[0]= v[1], evade[1]=-v[0], index unchanged, count=1.
 *   case 2: evade[0]= v[0], evade[1]= v[1], index unchanged, count=1.
 *   case 3: evade[0]=-v[0], evade[1]=-v[1], index unchanged, count=1.
 *   case 4: random pick of case 0 (index 0) vs case 1 (index 1), count=2;
 *           random_seed_step(seed) <= 0x8000 -> index 1 branch (0x2ac1f).
 * Confirmed: the two evade floats are a contiguous buffer at
 * [EBP-0xc]/[EBP-0x8] passed by address to actor_move_try_evasion_vector at
 * 0x2ac77. Confirmed: per-attempt both evade floats are negated (FCHS at
 * 0x2ac87/0x2ac96) and the index toggles (XOR EDI,1) at 0x2ac89. Confirmed:
 * success writes index to *evade_direction_reference (16-bit store at
 * 0x2aca5/0x2acb9); exhaustion writes 0xffff (0x2aca5). Return is char (AL). */
char actor_move_try_evasion_direction(int actor_handle, float *alignment_vector,
                                      float param_3,
                                      unsigned short *evade_direction_reference,
                                      float param_5, char *out_flag,
                                      void *result)
{
  float evade_dir[2];
  short count;
  short attempt;
  short index;

  datum_get(*(data_t **)0x6325a4, actor_handle);

  count = 1;
  if (alignment_vector == (float *)0x0 ||
      evade_direction_reference == (unsigned short *)0x0 ||
      result == (void *)0x0) {
    display_assert("alignment_vector && evade_direction_reference && result",
                   "c:\\halo\\SOURCE\\ai\\actor_moving.c", 0x4e4, 1);
    system_exit(-1);
  }

  index = *evade_direction_reference;
  switch (index) {
  case 0:
    evade_dir[1] = alignment_vector[0];
    evade_dir[0] = -alignment_vector[1];
    break;
  case 1:
    evade_dir[0] = alignment_vector[1];
    evade_dir[1] = -alignment_vector[0];
    break;
  case 2:
    evade_dir[1] = alignment_vector[1];
    evade_dir[0] = alignment_vector[0];
    break;
  case 3:
    evade_dir[0] = -alignment_vector[0];
    evade_dir[1] = -alignment_vector[1];
    break;
  case 4:
    if (random_seed_step((unsigned int *)get_global_random_seed_address()) <
        0x8001) {
      evade_dir[0] = alignment_vector[1];
      evade_dir[1] = -alignment_vector[0];
      index = 1;
      count = 2;
    } else {
      evade_dir[1] = alignment_vector[0];
      evade_dir[0] = -alignment_vector[1];
      index = 0;
      count = 2;
    }
    break;
  default:
    display_assert((char *)0, "c:\\halo\\SOURCE\\ai\\actor_moving.c", 0x508, 1);
    system_exit(-1);
  }

  attempt = 0;
  if (count > 0) {
    do {
      if (actor_move_try_evasion_vector(actor_handle, evade_dir, param_3,
                                        param_5, out_flag, result) != '\0') {
        *evade_direction_reference = index;
        return 1;
      }
      attempt = attempt + 1;
      evade_dir[0] = -evade_dir[0];
      index = index ^ 1;
      evade_dir[1] = -evade_dir[1];
    } while (attempt < count);
  }

  *evade_direction_reference = 0xffff;
  return 0;
}


/* actor_aim_jump (0x2ace0) — readable C lift (restored pre-naked) — Compute and clamp the jump aim velocity vector.
 *
 * Checks actor->swarm_element (-1 at actor[0x158]) and mounted state
 * (actor[0x6] != 0). If mounted, delegates to the actor-type vtable via
 * FUN_0003a920 and clears actor[0x530]. If not mounted but jump-aim is
 * active (actor[0x530] != 0), reads the stored jump velocity:
 *   param_5[0] = actor[0x534] * actor[0x53c]
 *   param_5[1] = actor[0x538] * actor[0x53c]
 *   param_5[2] = actor[0x540]
 * Computes the magnitude. If the actor is in swarm mode (actor[0x6c]==10
 * && actor[0xa0]==3), forces clamping on (overrides param_3=0). Otherwise
 * uses param_3 to control clamping. If clamping is off and
 * param_4 < magnitude, scales the output vector to length param_4.
 * Always clears actor[0x530] and returns 1.
 *
 * Confirmed: datum_get(actor_data, actor_handle) at 0x2acf0.
 * Confirmed: CMP [ESI+0x158],-1 at 0x2acf7-0x2ad03.
 * Confirmed: TEST [ESI+0x6],AL / JZ at 0x2ad09-0x2ad0e.
 * Confirmed: FUN_0003a920(actor_handle, a2, param_4, param_5) at 0x2ad1d.
 * Confirmed: TEST [ESI+0x530] at 0x2ad34-0x2ad3c.
 * Confirmed: CMP [ESI+0x6c],10 && CMP [ESI+0xa0],3 condition at
 * 0x2ad42-0x2ad55.
 * Confirmed: param_5[0]=actor[0x534]*actor[0x53c] (FSTP [ECX]) at 0x2ad7b.
 * Confirmed: param_5[1]=actor[0x538]*actor[0x53c] (FST [ECX+4]) at 0x2ad7d.
 * Confirmed: param_5[2]=actor[0x540] (FLD ST1; FSTP [ECX+8]) at
 * 0x2ad80-0x2ad82. Confirmed: sqrtf via FSQRT; FSTP [EBP-4] at 0x2ad97-0x2ad99.
 * Confirmed: FCOMP [EBP+0x14] (magnitude vs param_4) at 0x2ada7.
 * Confirmed: TEST AH,0x41; JNZ skip (param_4 >= magnitude → skip) at 0x2adac.
 * Confirmed: FUN_00012fb0(param_5, param_4/magnitude, param_5) at 0x2adbd.
 * Confirmed: actor[0x530]=0; return 1 at 0x2adc6-0x2adcf.
 */
int actor_aim_jump(int actor_handle, int a2, char param_3, float param_4,
                   float *param_5)
{
  char *actor;
  char cVar3;
  float magnitude;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  if (*(int *)(actor + 0x158) == -1) {
    if (*(char *)(actor + 0x6) != 0) {
      FUN_0003a920(actor_handle, a2, param_4, param_5);
      *(char *)(actor + 0x530) = 0;
      return 1;
    }
    if (*(char *)(actor + 0x530) != 0) {
      if (*(int16_t *)(actor + 0x6c) == 10 && *(int16_t *)(actor + 0xa0) == 3) {
        cVar3 = 1;
      } else {
        cVar3 = param_3;
      }
      param_5[0] = *(float *)(actor + 0x534) * *(float *)(actor + 0x53c);
      param_5[1] = *(float *)(actor + 0x538) * *(float *)(actor + 0x53c);
      param_5[2] = *(float *)(actor + 0x540);
      magnitude = sqrtf(param_5[0] * param_5[0] + param_5[1] * param_5[1] +
                        param_5[2] * param_5[2]);
      if (cVar3 == 0) {
        if (param_4 < magnitude) {
          FUN_00012fb0(param_5, param_4 / magnitude, param_5);
        }
      }
    }
  }
  *(char *)(actor + 0x530) = 0;
  return 1;
}


/* FUN_0002ade0 (0x2ade0) — XBE naked draft (batch 81). */
#if defined(__clang__)
static void (*const b2ade0_chkstk)(void) = FUN_001d90e0;
static void *(*const b2ade0_get)(int, int) = object_get_and_verify_type;
static int16_t (*const b2ade0_c1415f0)(int flags, unsigned int type_mask, void *cluster_info, float *position, float radius, int *out_handles, int16_t max_count) = object_find_in_radius;
static void *(*const b2ade0_tag)(int, int) = tag_get;
static void (*const b2ade0_c1aae0)(int object_handle, float *center, float *radius) = FUN_0001aae0;
static void * (*const b2ade0_c141480)(int object_handle, void *out_matrix) = object_get_world_matrix;
static void *(*const b2ade0_elem)(void *, int, int) = tag_block_get_element;
static void *(*const b2ade0_onode)(int, short) = object_get_node_matrix;
static void (*const b2ade0_xfrmpt)(float *, float *, float *) = matrix_transform_point;

__attribute__((naked, noinline))
void FUN_0002ade0(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x2064, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "flds 0x2557f0\n\t"
      "fcomps 0x255778\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002ade0_1\n\t"
      "flds 0x2557f0\n\t"
      "jmp .LFUN_0002ade0_2\n\t"
      ".LFUN_0002ade0_1:\n\t"
      "flds 0x255778\n\t"
      ".LFUN_0002ade0_2:\n\t"
      "fmuls 0x6044(%%esi)\n\t"
      "pushl $0x800\n\t"
      "leal -0x2064(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "leal 0xc(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "addl $0x48, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xc2\n\t"
      "pushl $1\n\t"
      "call *%[c1415f0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "movw $0, 0x3c(%%esi)\n\t"
      "jle .LFUN_0002ade0_12\n\t"
      "movzwl %%ax, %%edx\n\t"
      "leal -0x2064(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "nop\n\t"
      ".LFUN_0002ade0_3:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ebx\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "movl %%ebx, -0x24(%%ebp)\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .LFUN_0002ade0_11\n\t"
      "cmpl 0x8(%%esi), %%ebx\n\t"
      "je .LFUN_0002ade0_11\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl 0x7c(%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x636f6c6c\n\t"
      "call *%[tag]\n\t"
      "leal 0x280(%%eax), %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_0002ade0_11\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "call *%[c1aae0]\n\t"
      "leal -0x64(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c141480]\n\t"
      "movl (%%edi), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jle .LFUN_0002ade0_9\n\t"
      ".LFUN_0002ade0_4:\n\t"
      "pushl $0x20\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%esi), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_0002ade0_5\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[onode]\n\t"
      "movl %%eax, %%ebx\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x10(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[xfrmpt]\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fmuls (%%ebx)\n\t"
      "movl -0x24(%%ebp), %%ebx\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_0002ade0_6\n\t"
      ".LFUN_0002ade0_5:\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x10(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x64(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[xfrmpt]\n\t"
      "flds -0x64(%%ebp)\n\t"
      "fmuls 0x1c(%%esi)\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0002ade0_6:\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fsubs -0x20(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fsubs -0x1c(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xde, 0xca\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      ".byte 0xde, 0xc2\n\t"
      "fxch %%st(1)\n\t"
      "fsqrt\n\t"
      "fstp %%st(1)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0002ade0_7\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jmp .LFUN_0002ade0_8\n\t"
      ".LFUN_0002ade0_7:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0002ade0_8:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl (%%edi), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_0002ade0_4\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      ".LFUN_0002ade0_9:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x3c(%%esi), %%ax\n\t"
      "cmpw $0x400, %%ax\n\t"
      "jge .LFUN_0002ade0_11\n\t"
      "flds -0x10(%%ebp)\n\t"
      "leal 0x1(%%eax), %%edx\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "movw %%dx, 0x3c(%%esi)\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal (%%esi,%%eax,8), %%ecx\n\t"
      "movl %%edx, 0x54(%%ecx)\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "leal 0x44(%%ecx), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movl %%ebx, 0x40(%%ecx)\n\t"
      "fsubrs 0x4c(%%ecx)\n\t"
      "fstps 0x4c(%%ecx)\n\t"
      "flds -0x10(%%ebp)\n\t"
      ".byte 0xdc, 0xc0\n\t"
      "flds -0x4(%%ebp)\n\t"
      ".byte 0xdc, 0xc0\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x2533c0\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002ade0_10\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      ".LFUN_0002ade0_10:\n\t"
      "fstps 0x50(%%ecx)\n\t"
      ".LFUN_0002ade0_11:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jne .LFUN_0002ade0_3\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0002ade0_12:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(b2ade0_chkstk), [get] "m"(b2ade0_get), [c1415f0] "m"(b2ade0_c1415f0), [tag] "m"(b2ade0_tag), [c1aae0] "m"(b2ade0_c1aae0), [c141480] "m"(b2ade0_c141480), [elem] "m"(b2ade0_elem), [onode] "m"(b2ade0_onode), [xfrmpt] "m"(b2ade0_xfrmpt)
      : "memory");
}
#else
#error "FUN_0002ade0: clang naked draft required"
#endif


/* FUN_0002b020 (0x2b020) — XBE naked draft (batch 80). */
#if defined(__clang__)
static void (*const b2b020_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b2b020_exitfn)(int) = system_exit;
static char (*const b2b020_c149480)(int collision_flags, int bsp, short flags, int breakable_surfaces, int origin, int direction, float max_t, float *result) = collision_bsp_test_vector;
static char (*const b2b020_c10d4c0)(float *p1, float p2, float p3, float *p4, float *p5, float *p6, float *p7) = FUN_0010d4c0;

__attribute__((naked, noinline))
short FUN_0002b020(float *avoidance_ray __attribute__((unused)), float *ray_origin __attribute__((unused)), int avoidance_data __attribute__((unused)), float *ray_direction __attribute__((unused)), float *collision_t __attribute__((unused)), char *param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x438, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "je .LFUN_0002b020_1\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_0002b020_2\n\t"
      ".LFUN_0002b020_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x7f7\n\t"
      "pushl $0x255984\n\t"
      "pushl $0x255a08\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0002b020_2:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0002b020_3\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0002b020_4\n\t"
      ".LFUN_0002b020_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x7f8\n\t"
      "pushl $0x255984\n\t"
      "pushl $0x2559ec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0002b020_4:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0002b020_5\n\t"
      "pushl $1\n\t"
      "pushl $0x7f9\n\t"
      "pushl $0x255984\n\t"
      "pushl $0x2559e0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0002b020_5:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl $0x7f7fffff, (%%eax)\n\t"
      "flds 0x4(%%edi)\n\t"
      "movl 0x31fc38, %%eax\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x18(%%esi)\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x1c(%%esi)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl (%%eax), %%edx\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "fmuls 0x20(%%esi)\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fmuls 0x24(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x28(%%esi)\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x2c(%%esi)\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0xc(%%edi)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fmuls 0x30(%%esi)\n\t"
      ".byte 0xd8, 0xc2\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x34(%%esi)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fstp %%st(2)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x38(%%esi)\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "flds 0x10(%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x18(%%esi)\n\t"
      "fadds -0x20(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x1c(%%esi)\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x20(%%esi)\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x14(%%edi)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fmuls 0x24(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x28(%%esi)\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x2c(%%esi)\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x18(%%edi)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fmuls 0x30(%%esi)\n\t"
      "leal 0xc(%%esi), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      ".byte 0xd8, 0xc2\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x34(%%esi)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x38(%%esi)\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x6040(%%esi)\n\t"
      "flds -0x14(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds (%%eax)\n\t"
      "fstps (%%ebx)\n\t"
      "fxch %%st(2)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fadds 0x4(%%eax)\n\t"
      "fstps 0x4(%%ebx)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds 0x8(%%eax)\n\t"
      "fstps 0x8(%%ebx)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x6044(%%esi)\n\t"
      "fmuls (%%edi)\n\t"
      "flds -0x20(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps (%%ecx)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps 0x4(%%ecx)\n\t"
      "flds -0x18(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps 0x8(%%ecx)\n\t"
      "leal -0x438(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstp %%st(0)\n\t"
      "pushl $0x3f800000\n\t"
      "flds (%%ebx)\n\t"
      "pushl %%edx\n\t"
      "fsubs (%%eax)\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fsubs 0x8(%%eax)\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $3\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "call *%[c149480]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0002b020_6\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl $2, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl $0, (%%ecx)\n\t"
      "jmp .LFUN_0002b020_8\n\t"
      ".LFUN_0002b020_6:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "leal -0x438(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl $3\n\t"
      "call *%[c149480]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0002b020_7\n\t"
      "movl -0x438(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl $2, -0x8(%%ebp)\n\t"
      "movl %%edx, (%%eax)\n\t"
      ".LFUN_0002b020_7:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      ".LFUN_0002b020_8:\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpw %%di, 0x3c(%%esi)\n\t"
      "jle .LFUN_0002b020_11\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_0002b020_9:\n\t"
      "movswl %%di, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "leal 0x40(%%esi,%%ecx,8), %%eax\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x10(%%eax), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c10d4c0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0002b020_10\n\t"
      "flds -0x4(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "fcomps (%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0002b020_10\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl $1, -0x8(%%ebp)\n\t"
      "movl %%eax, (%%ecx)\n\t"
      ".LFUN_0002b020_10:\n\t"
      "incl %%edi\n\t"
      "cmpw 0x3c(%%esi), %%di\n\t"
      "jl .LFUN_0002b020_9\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      ".LFUN_0002b020_11:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "testl %%edx, %%edx\n\t"
      "popl %%edi\n\t"
      "je .LFUN_0002b020_13\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_0002b020_12\n\t"
      "movb $0, (%%edx)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0002b020_12:\n\t"
      "movb (%%edx), %%cl\n\t"
      "cmpb $0xff, %%cl\n\t"
      "jae .LFUN_0002b020_13\n\t"
      "incb %%cl\n\t"
      "movb %%cl, (%%edx)\n\t"
      ".LFUN_0002b020_13:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b2b020_assert), [exitfn] "m"(b2b020_exitfn), [c149480] "m"(b2b020_c149480), [c10d4c0] "m"(b2b020_c10d4c0)
      : "memory");
}
#else
#error "FUN_0002b020: clang naked draft required"
#endif


/* FUN_0002b310 (0x2b310) — XBE naked draft (batch 85). */
#if defined(__clang__)


__attribute__((naked, noinline))
char FUN_0002b310(float *direction __attribute__((unused)), short count __attribute__((unused)), int records __attribute__((unused)), float *values __attribute__((unused)), float *out_index __attribute__((unused)), float *out_value __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "leal -0x1(%%ebx), %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal (%%edx,%%eax,4), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "testw %%bx, %%bx\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jle .LFUN_0002b310_3\n\t"
      "nop\n\t"
      ".LFUN_0002b310_1:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movswl %%dx, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal (%%esi,%%eax,4), %%esi\n\t"
      "flds 0x4(%%esi)\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x4(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_0002b310_2\n\t"
      "flds 0x8(%%esi)\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%ecx)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0002b310_4\n\t"
      ".LFUN_0002b310_2:\n\t"
      "movl %%edx, %%edi\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "incl %%edx\n\t"
      "cmpw %%bx, %%dx\n\t"
      "jl .LFUN_0002b310_1\n\t"
      ".LFUN_0002b310_3:\n\t"
      "popl %%edi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0002b310_4:\n\t"
      "testw %%dx, %%dx\n\t"
      "jne .LFUN_0002b310_5\n\t"
      "movswl %%bx, %%ecx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "jmp .LFUN_0002b310_6\n\t"
      ".LFUN_0002b310_5:\n\t"
      "movswl %%dx, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      ".LFUN_0002b310_6:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "movswl %%di, %%eax\n\t"
      ".byte 0xd8, 0xe9\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movswl %%dx, %%edx\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "popl %%edi\n\t"
      ".byte 0xd8, 0xca\n\t"
      "popl %%esi\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      ".byte 0xd8, 0xf1\n\t"
      "fstps (%%ecx)\n\t"
      "fxch %%st(1)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "fmuls (%%ecx,%%eax,4)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls (%%ecx,%%edx,4)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      ".byte 0xde, 0xe9\n\t"
      ".byte 0xd8, 0xf1\n\t"
      "fstps (%%eax)\n\t"
      "movb $1, %%al\n\t"
      "fstp %%st(0)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_0002b310: clang naked draft required"
#endif


/* actor_move_transform_avoidance_vector (0x2b400) — readable C lift from XBE leaf. */
void actor_move_transform_avoidance_vector(char *obj, float *local, float *out)
{
  float *origin;
  float s;

  origin = *(float **)0x31fc38;
  out[0] = origin[0];
  out[1] = origin[1];
  out[2] = origin[2];
  s = local[0];
  out[0] += s * *(float *)(obj + 0x18);
  out[1] += s * *(float *)(obj + 0x1c);
  out[2] += s * *(float *)(obj + 0x20);
  s = local[1];
  out[0] += s * *(float *)(obj + 0x24);
  out[1] += s * *(float *)(obj + 0x28);
  out[2] += s * *(float *)(obj + 0x2c);
  s = local[2];
  out[0] += s * *(float *)(obj + 0x30);
  out[1] += s * *(float *)(obj + 0x34);
  out[2] += s * *(float *)(obj + 0x38);
}



/* actor_move_get_avoidance_vector (0x2b490) — readable C lift (restored pre-naked). */
void actor_move_get_avoidance_vector(int matrix, float dir_index,
                                     float *out_vec)
{
  const float *angles = (const float *)0x2557f4;
  short sector;
  int idx;
  float next_angle;
  float frac;
  float angle;
  float vec[3];

  /* Clamp the index into the valid [0, 8) range. */
  if (dir_index < *(const float *)0x2533c0 ||
      *(const float *)0x253f78 <= dir_index) {
    dir_index = 0.0f;
  }

  angle = 0.0f;
  sector = 0;
  do {
    if (dir_index < (float)(int)sector + *(const float *)0x2533c8) {
      idx = (int)sector;
      next_angle = *(const float *)0x2557f4;
      if (sector != 7) {
        next_angle = ((const float *)0x2557f8)[idx];
      }
      frac = dir_index - (float)idx;
      angle =
        next_angle * frac + (*(const float *)0x2533c8 - frac) * angles[idx];
      if (angle != *(const float *)0x2548fc) {
        if (angle < *(const float *)0x2533c0 ||
            *(const float *)0x255a54 <= angle) {
          display_assert("(angle >= 0.0f) && (angle < _full_circle)",
                         "c:\\halo\\SOURCE\\ai\\actor_moving.c", 0xab7, 1);
          system_exit(-1);
        }
        goto build_vector;
      }
      break;
    }
    sector = sector + 1;
  } while (sector < 8);

  angle = 0.0f;
  error(2,
        "warning: actor_move_get_avoidance_vector couldn't find out-of-bounds "
        "direction %.4f",
        (double)dir_index);

build_vector:
  vec[0] = 0.0f;
  vec[1] = x87_fcos(angle);
  vec[2] = x87_fsin(angle);
  actor_move_transform_avoidance_vector(matrix, vec, out_vec);
}


/* actor_move_get_avoidance_direction (0x2b5d0) — readable C lift (restored pre-naked). */
void actor_move_get_avoidance_direction(void)
{
  float(*table_a)[7] = (float(*)[7])0x6327e0;
  float(*table_b)[7] = (float(*)[7])0x6325c0;
  float(*basis)[3] = (float(*)[3])0x632780;

  const float *angle_table_9 = (const float *)0x2557cc;
  const float *scale_table_9 = (const float *)0x2557a8;
  const float *length_table_9 = (const float *)0x255784;
  const float k_angle = *(const float *)0x255780;
  const float k_length = *(const float *)0x25577c;
  const float k_base = *(const float *)0x255778;

  const float *outer_angles = (const float *)0x25581c;
  const float *outer_scales = (const float *)0x255814;
  const float *inner_angles = (const float *)0x2557f4;
  const float k_inner_base = *(const float *)0x2557f0;

  int i;
  int row;
  int col;
  float angle, sin_angle, cos_angle, scaled_angle, sin_scaled, scaled_len;
  float sin_outer, cos_outer, row_scale;
  float inner, cos_inner, sin_inner;
  int index;

  for (i = 0; i < 9; i++) {
    angle = angle_table_9[i];
    sin_angle = sinf(angle);
    cos_angle = cosf(angle);
    scaled_angle = k_angle * scale_table_9[i];
    sin_scaled = sinf(scaled_angle);
    scaled_len = k_length * length_table_9[i];

    table_a[i][0] = k_base;
    table_a[i][1] = 0.0f;
    table_a[i][2] = scaled_len * cos_angle;
    table_a[i][3] = scaled_len * sin_angle;
    table_a[i][4] = cosf(scaled_len);
    table_a[i][5] = sin_scaled * scaled_angle;
    table_a[i][6] = sin_scaled * sin_angle;
  }

  for (row = 0; row < 2; row++) {
    sin_outer = sinf(outer_angles[row]);
    cos_outer = cosf(outer_angles[row]);
    row_scale = outer_scales[row];

    for (col = 0; col < 8; col++) {
      inner = inner_angles[col];
      cos_inner = cosf(inner);
      sin_inner = sinf(inner);
      index = row * 8 + col;

      basis[index][0] = 0.0f;
      basis[index][1] = cos_inner;
      basis[index][2] = sin_inner;

      table_b[index][0] = k_inner_base;
      table_b[index][1] = row_scale * basis[index][0];
      table_b[index][2] = row_scale * basis[index][1];
      table_b[index][3] = row_scale * basis[index][2];
      table_b[index][4] = cos_outer;
      table_b[index][5] = sin_outer * basis[index][1];
      table_b[index][6] = sin_outer * basis[index][2];
    }
  }
}


/* actor_path_3d_available (0x2b720) — readable C lift (restored pre-naked) — Check if vehicle actor should brake.
 *
 * If actor is in a type-4 vehicle state (actor[0x15e] == 4):
 *   - Reads vehicle tag stopping distance (vehi_tag[0x388])
 *   - If stopping distance > 0 and actor's speed factor (actor[0x5ec]) >
 * threshold:
 *     - Computes delta vector from actor position to dest_pos
 *     - Normalizes delta (getting distance)
 *     - If distance > 0 and dot(normalized_delta, facing) > threshold:
 *       returns 0 (should brake)
 * Writes stopping distance to *dist_out if non-NULL.
 * Returns 1 (don't brake) by default.
 *
 * Confirmed: datum_get at 0x2b733. BL=1 default at 0x2b74c.
 * Confirmed: CMP word [ESI+0x15e],4 at 0x2b73d.
 * Confirmed: object_get_and_verify_type(actor[0x158], 2) at 0x2b75d.
 * Confirmed: tag_get('vehi', vehicle[0]) at 0x2b76a.
 * Confirmed: vehi[0x388] → local_8 at 0x2b76f.
 * Confirmed: FCOMP [0x2533c0] checks at 0x2b77e, 0x2b7d1.
 * Confirmed: FCOMP [0x2555d0] speed check at 0x2b795.
 * Confirmed: normalize3d(&delta) at 0x2b7cc.
 * Confirmed: dot product z*fz + y*fy + x*fx at 0x2b7e1-0x2b7fe.
 * Confirmed: FCOMP [0x253d54] dot threshold at 0x2b800.
 * Confirmed: dist_out write if non-NULL at 0x2b80f-0x2b819.
 */
char actor_path_3d_available(int actor_handle, float *dest_pos, float *dist_out)
{
  char *actor;
  char *vehi;
  float local_8;
  float delta[3];
  char result;

  actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  local_8 = 0.0f;
  result = 1;
  if (*(int16_t *)(actor + 0x15e) == 4) {
    vehi = (char *)object_get_and_verify_type(*(int *)(actor + 0x158), 2);
    vehi = (char *)tag_get(0x76656869, *(int *)vehi);
    local_8 = *(float *)(vehi + 0x388);
    if (local_8 > *(float *)0x2533c0 &&
        *(float *)(actor + 0x5ec) > *(float *)0x2555d0) {
      delta[0] = dest_pos[0] - *(float *)(actor + 0x12c);
      delta[1] = dest_pos[1] - *(float *)(actor + 0x130);
      delta[2] = dest_pos[2] - *(float *)(actor + 0x134);
      if (normalize3d(delta) > *(float *)0x2533c0 &&
          delta[0] * *(float *)(actor + 0x174) +
              delta[1] * *(float *)(actor + 0x178) +
              delta[2] * *(float *)(actor + 0x17c) >
            *(float *)0x253d54) {
        result = 0;
      }
    }
  }
  if (dist_out != (float *)0) {
    *dist_out = local_8;
  }
  return result;
}


/* FUN_0002b830 (0x2b830) — XBE naked draft (batch 81). */
#if defined(__clang__)
static float (*const b2b830_norm)(float *) = normalize3d;
static char * (*const b2b830_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b2b830_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b2b830_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_0002b830(float *facing_basis __attribute__((unused)), char use_3d __attribute__((unused)), float *out_vector __attribute__((unused)), short *out_index __attribute__((unused)), float *in_vec __attribute__((unused)), float *weight_vec __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x3c, %%esp\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "movb 0x8(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x3c(%%ebp)\n\t"
      "leal -0x3c(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "je .LFUN_0002b830_2\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_0002b830_1\n\t"
      "movl %%esi, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      ".LFUN_0002b830_1:\n\t"
      "movl 0x31fc38, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "jmp .LFUN_0002b830_4\n\t"
      ".LFUN_0002b830_2:\n\t"
      "movl $0, -0x34(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_0002b830_3\n\t"
      "movl %%esi, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      ".LFUN_0002b830_3:\n\t"
      "flds -0x38(%%ebp)\n\t"
      "movl -0x3c(%%ebp), %%eax\n\t"
      "fchs\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      ".LFUN_0002b830_4:\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "fchs\n\t"
      "xorl %%edx, %%edx\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x10(%%ebp)\n\t"
      ".LFUN_0002b830_5:\n\t"
      "movb 0x8(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0002b830_6\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "flds (%%ecx)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%edi)\n\t"
      "fmuls -0x4(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x8(%%esi)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "flds (%%esi)\n\t"
      "fmuls -0x4(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "jmp .LFUN_0002b830_7\n\t"
      ".LFUN_0002b830_6:\n\t"
      "flds (%%ecx)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "flds (%%edi)\n\t"
      "fmuls -0x4(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%esi)\n\t"
      "fmuls -0x4(%%ecx)\n\t"
      ".LFUN_0002b830_7:\n\t"
      "cmpw $-1, %%bx\n\t"
      "flds (%%ecx)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "je .LFUN_0002b830_11\n\t"
      "fld %%st(1)\n\t"
      "fcomps -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "fcomps -0x4(%%ebp)\n\t"
      "testb $0x41, %%ah\n\t"
      "fnstsw %%ax\n\t"
      "jne .LFUN_0002b830_10\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0002b830_12\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x253398\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0002b830_12\n\t"
      ".LFUN_0002b830_8:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0002b830_9:\n\t"
      "incl %%edx\n\t"
      "addl $0xc, %%ecx\n\t"
      "cmpw $4, %%dx\n\t"
      "jl .LFUN_0002b830_5\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movw %%bx, (%%ecx)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movswl %%bx, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "leal -0x3c(%%ebp,%%edx,4), %%eax\n\t"
      "movl (%%eax), %%esi\n\t"
      "movl %%ecx, %%edx\n\t"
      "movl %%esi, (%%edx)\n\t"
      "movl 0x4(%%eax), %%esi\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%esi, 0x4(%%edx)\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "popl %%esi\n\t"
      "flds 0x8(%%ecx)\n\t"
      "popl %%ebx\n\t"
      "flds 0x4(%%ecx)\n\t"
      "flds (%%ecx)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0x2533c8\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fsts 0x8(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "je .LFUN_0002b830_13\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0002b830_15\n\t"
      "jmp .LFUN_0002b830_14\n\t"
      ".LFUN_0002b830_10:\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002b830_8\n\t"
      "fcoms 0x253398\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002b830_8\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "movl %%edx, %%ebx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .LFUN_0002b830_9\n\t"
      ".LFUN_0002b830_11:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0002b830_12:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "movl %%edx, %%ebx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .LFUN_0002b830_9\n\t"
      ".LFUN_0002b830_13:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0002b830_14:\n\t"
      "flds 0x8(%%ecx)\n\t"
      "pushl $1\n\t"
      "pushl $0x764\n\t"
      "pushl $0x255984\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%ecx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255aac\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0002b830_15:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [norm] "m"(b2b830_norm), [c8d9d0] "m"(b2b830_c8d9d0), [assert] "m"(b2b830_assert), [exitfn] "m"(b2b830_exitfn)
      : "memory");
}
#else
#error "FUN_0002b830: clang naked draft required"
#endif


/* FUN_0002bab0 (0x2bab0) — XBE naked draft (batch 80). */
#if defined(__clang__)
static bool (*const b2bab0_c21fb0)(float *v) = valid_real_normal3d;
static char * (*const b2bab0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b2bab0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b2bab0_exitfn)(int) = system_exit;
static void (*const b2bab0_c1a2d90)(float *forward, float *left, float *up) = biped_build_flying_axes;
static float (*const b2bab0_norm)(float *) = normalize3d;
static int (*const b2bab0_c28610)(float *v) = valid_real_normal2d;

__attribute__((naked, noinline))
void FUN_0002bab0(char use_3d __attribute__((unused)), float *movement_direction __attribute__((unused)), float *facing_direction __attribute__((unused)), float *out __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "pushl %%esi\n\t"
      "je .LFUN_0002bab0_3\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0002bab0_1\n\t"
      "flds 0x8(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x775\n\t"
      "pushl $0x255984\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255b80\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0002bab0_1:\n\t"
      "pushl %%edi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0002bab0_2\n\t"
      "flds 0x8(%%edi)\n\t"
      "pushl $1\n\t"
      "pushl $0x776\n\t"
      "pushl $0x255984\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255b6c\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0002bab0_2:\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1a2d90]\n\t"
      "flds 0x8(%%edi)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "pushl %%ebx\n\t"
      "flds 0x4(%%edi)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%esi)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps (%%ebx)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps 0x4(%%ebx)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps 0x8(%%ebx)\n\t"
      "call *%[norm]\n\t"
      "addl $0x10, %%esp\n\t"
      "fstp %%st(0)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0002bab0_3:\n\t"
      "call *%[c28610]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0002bab0_4\n\t"
      "flds 0x4(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x785\n\t"
      "pushl $0x255984\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255b44\n\t"
      "pushl $0x2555d4\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0002bab0_4:\n\t"
      "pushl %%edi\n\t"
      "call *%[c28610]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0002bab0_5\n\t"
      "flds 0x4(%%edi)\n\t"
      "pushl $1\n\t"
      "pushl $0x786\n\t"
      "pushl $0x255984\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255b20\n\t"
      "pushl $0x2555d4\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0002bab0_5:\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "je .LFUN_0002bab0_6\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0002bab0_8\n\t"
      "jmp .LFUN_0002bab0_7\n\t"
      ".LFUN_0002bab0_6:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0002bab0_7:\n\t"
      "flds 0x8(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x787\n\t"
      "pushl $0x255984\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255b18\n\t"
      "pushl $0x255b00\n\t"
      "pushl $0x255ad8\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x20, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0002bab0_8:\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "je .LFUN_0002bab0_9\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0002bab0_11\n\t"
      "jmp .LFUN_0002bab0_10\n\t"
      ".LFUN_0002bab0_9:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0002bab0_10:\n\t"
      "flds 0x8(%%edi)\n\t"
      "pushl $1\n\t"
      "pushl $0x788\n\t"
      "pushl $0x255984\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255b18\n\t"
      "pushl $0x255ac4\n\t"
      "pushl $0x255ad8\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x20, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0002bab0_11:\n\t"
      "flds 0x4(%%edi)\n\t"
      "pushl %%ebx\n\t"
      "fchs\n\t"
      "flds (%%edi)\n\t"
      "flds (%%esi)\n\t"
      "fmuls (%%edi)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps (%%ebx)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls (%%esi)\n\t"
      "movl $0, 0x8(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps 0x4(%%ebx)\n\t"
      "call *%[norm]\n\t"
      "addl $4, %%esp\n\t"
      "fstp %%st(0)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c21fb0] "m"(b2bab0_c21fb0), [c8d9d0] "m"(b2bab0_c8d9d0), [assert] "m"(b2bab0_assert), [exitfn] "m"(b2bab0_exitfn), [c1a2d90] "m"(b2bab0_c1a2d90), [norm] "m"(b2bab0_norm), [c28610] "m"(b2bab0_c28610)
      : "memory");
}
#else
#error "FUN_0002bab0: clang naked draft required"
#endif


/* FUN_0002bd80 (0x2bd80) — XBE naked draft (batch 79). */
#if defined(__clang__)
static void (*const b2bd80_chkstk)(void) = FUN_001d90e0;
static void *(*const b2bd80_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b2bd80_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b2bd80_exitfn)(int) = system_exit;
static void *(*const b2bd80_get)(int, int) = object_get_and_verify_type;
static int (*const b2bd80_gtime)(void) = game_time_get;
static void * (*const b2bd80_c18e3c0)(void) = scenario_get;
static void *(*const b2bd80_gbsp)(void) = global_collision_bsp_get;
static vector3_t * (*const b2bd80_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static void (*const b2bd80_c2ade0)(int actor_handle) = FUN_0002ade0;
static void *(*const b2bd80_memset)(void *, int, unsigned int) = csmemset;
static short (*const b2bd80_c2b020)(float *avoidance_ray, float *ray_origin, int avoidance_data, float *ray_direction, float *collision_t, char *param_3) = FUN_0002b020;
static char (*const b2bd80_c2b310)(float *direction, short count, int records, float *values, float *out_index, float *out_value) = FUN_0002b310;
static void * (*const b2bd80_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b2bd80_c2b400)(int matrix, float *in_vec, float *out_vec) = actor_move_transform_avoidance_vector;
static float (*const b2bd80_c10c510)(float *v1, float *v2) = FUN_0010c510;

__attribute__((naked, noinline))
void FUN_0002bd80(int actor_handle __attribute__((unused)), float *facing __attribute__((unused)), float *vel_out __attribute__((unused)), float *speed_out __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x60e0, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "flds 0x2533c0\n\t"
      "movl 0x31fc38, %%ecx\n\t"
      "fsts -0x44(%%ebp)\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x158(%%eax), %%edi\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%eax, -0x5c(%%ebp)\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "jne .LFUN_0002bd80_1\n\t"
      "movl 0x18(%%eax), %%edi\n\t"
      ".LFUN_0002bd80_1:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0002bd80_2\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0002bd80_3\n\t"
      ".LFUN_0002bd80_2:\n\t"
      "pushl $1\n\t"
      "fstp %%st(0)\n\t"
      "pushl $0x887\n\t"
      "pushl $0x255984\n\t"
      "pushl $0x255ca8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "flds -0x44(%%ebp)\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0002bd80_3:\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_0002bd80_72\n\t"
      "pushl $-1\n\t"
      "fstp %%st(0)\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl 0x331f58, %%edx\n\t"
      "andl $0xffff, %%esi\n\t"
      "imull $0x657c, %%esi, %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl %%edx, %%esi\n\t"
      "movl %%ebx, -0x68(%%ebp)\n\t"
      "movb $0, -0x11(%%ebp)\n\t"
      "movl %%esi, -0x58(%%ebp)\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, 0x19c(%%esi)\n\t"
      "call *%[c18e3c0]\n\t"
      "movl %%eax, -0x60e0(%%ebp)\n\t"
      "call *%[gbsp]\n\t"
      "leal -0x60d4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x60dc(%%ebp)\n\t"
      "movl %%edi, -0x60d8(%%ebp)\n\t"
      "call *%[c1412f0]\n\t"
      "leal 0x24(%%ebx), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x60c8(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, -0x60c4(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, -0x60c0(%%ebp)\n\t"
      "leal 0x30(%%ebx), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%edi, -0x60b0(%%ebp)\n\t"
      "movl 0x4(%%edx), %%edi\n\t"
      "movl %%edi, -0x60ac(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, -0x60a8(%%ebp)\n\t"
      "flds (%%ecx)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "flds (%%eax)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds (%%eax)\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      "flds (%%ecx)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "leal -0x60e0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0x41400000, -0x9c(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "movl $0x3f800000, -0xa0(%%ebp)\n\t"
      "fstps -0x60bc(%%ebp)\n\t"
      "fstps -0x60b8(%%ebp)\n\t"
      "fstps -0x60b4(%%ebp)\n\t"
      "call *%[c2ade0]\n\t"
      "pushl $0x20\n\t"
      "leal -0x8c(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "movl $0, -0x4c(%%ebp)\n\t"
      "call *%[memset]\n\t"
      "movl -0x5c(%%ebp), %%edx\n\t"
      "movw 0x5d8(%%edx), %%ax\n\t"
      "addl $0x20, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_0002bd80_8\n\t"
      "cmpw $8, %%ax\n\t"
      "jge .LFUN_0002bd80_8\n\t"
      "movswl %%ax, %%eax\n\t"
      "leal 0x1(%%eax), %%ecx\n\t"
      "andl $0x80000007, %%ecx\n\t"
      "jns .LFUN_0002bd80_4\n\t"
      "decl %%ecx\n\t"
      "orl $0xfffffff8, %%ecx\n\t"
      "incl %%ecx\n\t"
      ".LFUN_0002bd80_4:\n\t"
      "leal 0x2(%%eax), %%edx\n\t"
      "andl $0x80000007, %%edx\n\t"
      "jns .LFUN_0002bd80_5\n\t"
      "decl %%edx\n\t"
      "orl $0xfffffff8, %%edx\n\t"
      "incl %%edx\n\t"
      ".LFUN_0002bd80_5:\n\t"
      "leal 0x7(%%eax), %%edi\n\t"
      "andl $0x80000007, %%edi\n\t"
      "jns .LFUN_0002bd80_6\n\t"
      "decl %%edi\n\t"
      "orl $0xfffffff8, %%edi\n\t"
      "incl %%edi\n\t"
      ".LFUN_0002bd80_6:\n\t"
      "leal 0x6(%%eax), %%ebx\n\t"
      "andl $0x80000007, %%ebx\n\t"
      "jns .LFUN_0002bd80_7\n\t"
      "decl %%ebx\n\t"
      "orl $0xfffffff8, %%ebx\n\t"
      "incl %%ebx\n\t"
      ".LFUN_0002bd80_7:\n\t"
      "flds -0x8c(%%ebp,%%eax,4)\n\t"
      "leal -0x8c(%%ebp,%%eax,4), %%eax\n\t"
      "fadds 0x253524\n\t"
      "fstps (%%eax)\n\t"
      "movswl %%cx, %%eax\n\t"
      "flds 0x255954\n\t"
      "leal -0x8c(%%ebp,%%eax,4), %%eax\n\t"
      "fmuls 0x253524\n\t"
      "fld %%st(0)\n\t"
      "fadds (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      "movswl %%dx, %%eax\n\t"
      "flds 0x255958\n\t"
      "leal -0x8c(%%ebp,%%eax,4), %%eax\n\t"
      "fmuls 0x253524\n\t"
      "fld %%st(0)\n\t"
      "fadds (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      "movswl %%di, %%eax\n\t"
      "leal -0x8c(%%ebp,%%eax,4), %%eax\n\t"
      "fxch %%st(1)\n\t"
      "fadds (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      "movswl %%bx, %%eax\n\t"
      "leal -0x8c(%%ebp,%%eax,4), %%eax\n\t"
      "fadds (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      ".LFUN_0002bd80_8:\n\t"
      "leal 0x61fc(%%esi), %%eax\n\t"
      "leal 0x61e8(%%esi), %%ecx\n\t"
      "movl $0x255828, -0x2c(%%ebp)\n\t"
      "movl $0x6327e0, -0x34(%%ebp)\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "leal 0x628c(%%esi), %%edi\n\t"
      "movl $9, -0x4(%%ebp)\n\t"
      ".LFUN_0002bd80_9:\n\t"
      "pushl $0\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "leal -0x10(%%ebp), %%ebx\n\t"
      "leal -0x60e0(%%ebp), %%esi\n\t"
      "call *%[c2b020]\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "leal -0x6c(%%edi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl -0x40(%%ebp), %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0x3c(%%ebp), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl -0x38(%%ebp), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "movw %%ax, (%%ecx)\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "jle .LFUN_0002bd80_13\n\t"
      "flds 0x2533c8\n\t"
      "movl -0x2c(%%ebp), %%edx\n\t"
      "fsubs -0x28(%%ebp)\n\t"
      "leal -0x8c(%%ebp), %%ecx\n\t"
      "movl $8, %%esi\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "jmp .LFUN_0002bd80_10\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0002bd80_10:\n\t"
      "fld %%st(0)\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002bd80_11\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_0002bd80_11:\n\t"
      "fmuls (%%edx)\n\t"
      "addl $4, %%edx\n\t"
      "addl $4, %%ecx\n\t"
      "decl %%esi\n\t"
      "fadds -0x4(%%ecx)\n\t"
      "fstps -0x4(%%ecx)\n\t"
      "jne .LFUN_0002bd80_10\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0002bd80_12\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "jmp .LFUN_0002bd80_13\n\t"
      ".LFUN_0002bd80_12:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0002bd80_13:\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "movl -0x34(%%ebp), %%ebx\n\t"
      "movl $2, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "addl $4, %%ecx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl -0x2c(%%ebp), %%edx\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "addl $0x1c, %%ebx\n\t"
      "addl $0x20, %%edx\n\t"
      "addl $0xc, %%edi\n\t"
      "decl %%ecx\n\t"
      "movl %%ebx, -0x34(%%ebp)\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jne .LFUN_0002bd80_9\n\t"
      "movl -0x58(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x6c(%%ebp)\n\t"
      "movl -0x5c(%%ebp), %%eax\n\t"
      "addl $0x5c9, %%eax\n\t"
      "leal -0x8c(%%ebp), %%edx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%edx, -0x60(%%ebp)\n\t"
      "leal 0x6418(%%ecx), %%esi\n\t"
      "leal 0x62f8(%%ecx), %%eax\n\t"
      "movl $0x6325c0, %%edx\n\t"
      "addl $0x6318, %%ecx\n\t"
      "movl $8, -0x54(%%ebp)\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0002bd80_14:\n\t"
      "leal -0x50(%%ebp), %%ebx\n\t"
      "movl %%ebx, -0x64(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "decl %%ebx\n\t"
      "leal -0x3c(%%ebp), %%edi\n\t"
      "movl %%ebx, -0x18(%%ebp)\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "movl %%esi, -0x34(%%ebp)\n\t"
      "movl $2, -0x48(%%ebp)\n\t"
      ".LFUN_0002bd80_15:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x98(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "leal -0x10(%%ebp), %%ebx\n\t"
      "leal -0x60e0(%%ebp), %%esi\n\t"
      "call *%[c2b020]\n\t"
      "movl -0x34(%%ebp), %%ecx\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "movl -0x64(%%ebp), %%edx\n\t"
      "leal -0xc0(%%ecx), %%esi\n\t"
      "movl %%ebx, (%%esi)\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "movl %%ebx, 0x4(%%esi)\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "movl %%ebx, 0x8(%%esi)\n\t"
      "movl -0x98(%%ebp), %%ebx\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl %%ebx, (%%esi)\n\t"
      "movl -0x94(%%ebp), %%ebx\n\t"
      "movl %%ebx, 0x4(%%esi)\n\t"
      "movl -0x90(%%ebp), %%ebx\n\t"
      "movl %%ebx, 0x8(%%esi)\n\t"
      "movl -0x2c(%%ebp), %%esi\n\t"
      "movl (%%edi), %%ebx\n\t"
      "movw %%ax, (%%edx)\n\t"
      "movw %%ax, (%%esi)\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "movl %%ebx, (%%eax)\n\t"
      "movl -0x28(%%ebp), %%ebx\n\t"
      "addl $0x1c, %%ebx\n\t"
      "addl $4, %%eax\n\t"
      "movl %%ebx, -0x28(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%ebx\n\t"
      "addl $0xc, %%ecx\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movl -0x48(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "incl %%ebx\n\t"
      "addl $2, %%edx\n\t"
      "addl $2, %%esi\n\t"
      "addl $4, %%edi\n\t"
      "decl %%eax\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "movl %%ebx, -0x18(%%ebp)\n\t"
      "movl %%edx, -0x64(%%ebp)\n\t"
      "movl %%esi, -0x2c(%%ebp)\n\t"
      "movl %%eax, -0x48(%%ebp)\n\t"
      "jne .LFUN_0002bd80_15\n\t"
      "flds 0x2533c0\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "xorb %%bl, %%bl\n\t"
      "leal -0x4e(%%ebp), %%esi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl $2, %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0002bd80_16:\n\t"
      "cmpw $0, (%%esi)\n\t"
      "flds 0x2533c8\n\t"
      "jne .LFUN_0002bd80_20\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_0002bd80_19\n\t"
      "movb (%%edx), %%al\n\t"
      "fstp %%st(0)\n\t"
      "cmpb $0x4b, %%al\n\t"
      "jae .LFUN_0002bd80_17\n\t"
      "flds 0x2533c0\n\t"
      "fmuls 0x25594c(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "jmp .LFUN_0002bd80_22\n\t"
      ".LFUN_0002bd80_17:\n\t"
      "movzbl %%al, %%eax\n\t"
      "movl %%eax, -0x48(%%ebp)\n\t"
      "fildl -0x48(%%ebp)\n\t"
      "fdivrs 0x255ca4\n\t"
      "fsubrs 0x2533c8\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0002bd80_18\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "fmuls 0x25594c(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "jmp .LFUN_0002bd80_22\n\t"
      ".LFUN_0002bd80_18:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002bd80_19\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_0002bd80_19:\n\t"
      "fmuls 0x25594c(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "jmp .LFUN_0002bd80_22\n\t"
      ".LFUN_0002bd80_20:\n\t"
      "fsubs -0x38(%%ebp,%%ecx,1)\n\t"
      ".byte 0xdc, 0xc0\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002bd80_21\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_0002bd80_21:\n\t"
      "fmuls 0x25594c(%%ecx)\n\t"
      "movb $1, %%bl\n\t"
      ".byte 0xde, 0xe9\n\t"
      ".LFUN_0002bd80_22:\n\t"
      "subl $2, %%esi\n\t"
      "decl %%edx\n\t"
      "subl $4, %%ecx\n\t"
      "decl %%edi\n\t"
      "jne .LFUN_0002bd80_16\n\t"
      "movl -0x6c(%%ebp), %%eax\n\t"
      "leal -0x1(%%eax), %%ecx\n\t"
      "andl $0x80000007, %%ecx\n\t"
      "jns .LFUN_0002bd80_23\n\t"
      "decl %%ecx\n\t"
      "orl $0xfffffff8, %%ecx\n\t"
      "incl %%ecx\n\t"
      ".LFUN_0002bd80_23:\n\t"
      "movl %%eax, %%edx\n\t"
      "andl $0x80000007, %%edx\n\t"
      "jns .LFUN_0002bd80_24\n\t"
      "decl %%edx\n\t"
      "orl $0xfffffff8, %%edx\n\t"
      "incl %%edx\n\t"
      ".LFUN_0002bd80_24:\n\t"
      "leal 0x5(%%eax), %%esi\n\t"
      "andl $0x80000007, %%esi\n\t"
      "jns .LFUN_0002bd80_25\n\t"
      "decl %%esi\n\t"
      "orl $0xfffffff8, %%esi\n\t"
      "incl %%esi\n\t"
      ".LFUN_0002bd80_25:\n\t"
      "leal 0x4(%%eax), %%edi\n\t"
      "andl $0x80000007, %%edi\n\t"
      "jns .LFUN_0002bd80_26\n\t"
      "decl %%edi\n\t"
      "orl $0xfffffff8, %%edi\n\t"
      "incl %%edi\n\t"
      ".LFUN_0002bd80_26:\n\t"
      "movl -0x60(%%ebp), %%ebx\n\t"
      "fld %%st(0)\n\t"
      "fadds (%%ebx)\n\t"
      "movswl %%cx, %%ecx\n\t"
      "leal -0x8c(%%ebp,%%ecx,4), %%ecx\n\t"
      "addl $4, %%ebx\n\t"
      "fstps -0x4(%%ebx)\n\t"
      "movl %%ebx, -0x60(%%ebp)\n\t"
      "flds 0x255954\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(0)\n\t"
      "fadds (%%ecx)\n\t"
      "fstps (%%ecx)\n\t"
      "movswl %%dx, %%ecx\n\t"
      "leal -0x8c(%%ebp,%%ecx,4), %%ecx\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x255958\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "fsts -0x48(%%ebp)\n\t"
      "fadds (%%ecx)\n\t"
      "fstps (%%ecx)\n\t"
      "movswl %%si, %%ecx\n\t"
      "movl -0x34(%%ebp), %%esi\n\t"
      "fadds -0x8c(%%ebp,%%ecx,4)\n\t"
      "leal -0x8c(%%ebp,%%ecx,4), %%ecx\n\t"
      "fstps (%%ecx)\n\t"
      "movswl %%di, %%ecx\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "flds -0x48(%%ebp)\n\t"
      "fadds -0x8c(%%ebp,%%ecx,4)\n\t"
      "addl $2, %%edi\n\t"
      "leal -0x8c(%%ebp,%%ecx,4), %%ecx\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl -0x54(%%ebp), %%edi\n\t"
      "incl %%eax\n\t"
      "fstps (%%ecx)\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "decl %%edi\n\t"
      "movl %%eax, -0x6c(%%ebp)\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "movl %%edi, -0x54(%%ebp)\n\t"
      "jne .LFUN_0002bd80_14\n\t"
      "movl -0x68(%%ebp), %%ecx\n\t"
      "flds 0x44(%%ecx)\n\t"
      "movl -0x58(%%ebp), %%esi\n\t"
      "flds 0x40(%%ecx)\n\t"
      "flds 0x3c(%%ecx)\n\t"
      "movb $0, 0x6551(%%esi)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fcomps 0x255ca0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002bd80_34\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fsubs 0x255ca0\n\t"
      "fmuls 0x255c9c\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002bd80_27\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_0002bd80_27:\n\t"
      "fmuls 0x2533f0\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "flds -0x60ac(%%ebp)\n\t"
      "fmuls 0x40(%%ecx)\n\t"
      "flds -0x60a8(%%ebp)\n\t"
      "fmuls 0x44(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x60b0(%%ebp)\n\t"
      "fmuls 0x3c(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x60b4(%%ebp)\n\t"
      "fmuls 0x44(%%ecx)\n\t"
      "flds -0x60b8(%%ebp)\n\t"
      "fmuls 0x40(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x60bc(%%ebp)\n\t"
      "fmuls 0x3c(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fchs\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0002bd80_31\n\t"
      "flds 0x2533c8\n\t"
      ".byte 0xd8, 0xf1\n\t"
      "flds 0x2533c0\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002bd80_32\n\t"
      "leal -0x54(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x60(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x8c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x632780\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "movl $8, %%ebx\n\t"
      "call *%[c2b310]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0002bd80_32\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fcomps 0x253398\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002bd80_32\n\t"
      "flds -0x50(%%ebp)\n\t"
      "leal -0x8c(%%ebp), %%edx\n\t"
      "movl $0x632784, %%ecx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0002bd80_28:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x4(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls (%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0002bd80_29\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds (%%edx)\n\t"
      "fstps (%%edx)\n\t"
      "jmp .LFUN_0002bd80_30\n\t"
      ".LFUN_0002bd80_29:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0002bd80_30:\n\t"
      "addl $0xc, %%ecx\n\t"
      "addl $4, %%edx\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_0002bd80_28\n\t"
      "jmp .LFUN_0002bd80_33\n\t"
      ".LFUN_0002bd80_31:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0002bd80_32:\n\t"
      "flds 0x2533c0\n\t"
      ".LFUN_0002bd80_33:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "fstps 0x6554(%%esi)\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "leal 0x655c(%%esi), %%edx\n\t"
      "movl %%ecx, 0x6558(%%esi)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl -0x54(%%ebp), %%ecx\n\t"
      "movb $1, 0x6551(%%esi)\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl %%ecx, 0x6568(%%esi)\n\t"
      ".LFUN_0002bd80_34:\n\t"
      "flds 0x255c98\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "fsts -0x2c(%%ebp)\n\t"
      "movl %%edi, -0x28(%%ebp)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "leal -0x8c(%%ebp), %%edx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0002bd80_35:\n\t"
      "fcoms (%%edx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0002bd80_36\n\t"
      "fstp %%st(0)\n\t"
      "movl %%ecx, %%edi\n\t"
      "flds (%%edx)\n\t"
      ".LFUN_0002bd80_36:\n\t"
      "incl %%ecx\n\t"
      "addl $4, %%edx\n\t"
      "cmpw $8, %%cx\n\t"
      "jl .LFUN_0002bd80_35\n\t"
      "testw %%di, %%di\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "movl %%edi, -0x28(%%ebp)\n\t"
      "jl .LFUN_0002bd80_37\n\t"
      "cmpw $8, %%di\n\t"
      "jl .LFUN_0002bd80_38\n\t"
      ".LFUN_0002bd80_37:\n\t"
      "pushl $1\n\t"
      "pushl $0x983\n\t"
      "pushl $0x255984\n\t"
      "pushl $0x255c30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0002bd80_38:\n\t"
      "pushl $0x20\n\t"
      "leal -0x8c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x64d8(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "movl %%edx, -0x40(%%ebp)\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      "movl 0x31fc38, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      ".byte 0xde, 0xc1\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "flds -0x40(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "fmuls -0x40(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "movl $0x3f800000, -0x30(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "movl $0, -0x34(%%ebp)\n\t"
      "fsqrt\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0002bd80_40\n\t"
      "flds 0x2533c8\n\t"
      ".byte 0xd8, 0xf1\n\t"
      "flds -0x40(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002bd80_41\n\t"
      "flds -0x60c0(%%ebp)\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "fmuls -0x38(%%ebp)\n\t"
      "flds -0x60c4(%%ebp)\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls -0x60c8(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls -0x60b4(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls -0x60b8(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls -0x60bc(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls -0x60ac(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls -0x60a8(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls -0x60b0(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0002bd80_40\n\t"
      "flds 0x2533c8\n\t"
      ".byte 0xd8, 0xf1\n\t"
      "flds 0x2533c0\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002bd80_41\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x8c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x632780\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "movl $8, %%ebx\n\t"
      "call *%[c2b310]\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x10, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0002bd80_39\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x253f78\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_0002bd80_41\n\t"
      ".LFUN_0002bd80_39:\n\t"
      "pushl $1\n\t"
      "pushl $0x9a2\n\t"
      "pushl $0x255984\n\t"
      "pushl $0x255bb0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_0002bd80_41\n\t"
      ".LFUN_0002bd80_40:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0002bd80_41:\n\t"
      "movl -0x60c8(%%ebp), %%ecx\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fsubs -0x34(%%ebp)\n\t"
      "leal 0x6524(%%esi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x60c4(%%ebp), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl -0x60c0(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl %%edi, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal 0x6530(%%esi), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl -0x2c(%%ebp), %%ecx\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "fcomps 0x253f3c\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movw -0x28(%%ebp), %%dx\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "movl %%eax, 0x6504(%%esi)\n\t"
      "movl %%ecx, 0x64fc(%%esi)\n\t"
      "movl -0x34(%%ebp), %%ecx\n\t"
      "fnstsw %%ax\n\t"
      "movw %%dx, 0x6500(%%esi)\n\t"
      "testb $0x41, %%ah\n\t"
      "movl %%ecx, 0x6508(%%esi)\n\t"
      "jne .LFUN_0002bd80_43\n\t"
      "fsubs 0x253f3c\n\t"
      "fmuls 0x255ba8\n\t"
      "flds 0x2533c8\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0002bd80_42\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_0002bd80_42:\n\t"
      "fadds 0x2533c8\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jmp .LFUN_0002bd80_45\n\t"
      ".LFUN_0002bd80_43:\n\t"
      "fmuls 0x254e6c\n\t"
      "flds 0x2533c8\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002bd80_44\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jmp .LFUN_0002bd80_45\n\t"
      ".LFUN_0002bd80_44:\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, -0x4(%%ebp)\n\t"
      ".LFUN_0002bd80_45:\n\t"
      "flds -0x30(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "fcomps 0x255ba4\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "movl -0x5c(%%ebp), %%ebx\n\t"
      "movl %%eax, 0x650c(%%esi)\n\t"
      "movl %%edx, 0x6510(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0002bd80_53\n\t"
      "movw 0x5f0(%%ebx), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_0002bd80_46\n\t"
      "cmpw $0x5a, %%ax\n\t"
      "jge .LFUN_0002bd80_46\n\t"
      "movw $7, 0x653c(%%esi)\n\t"
      "jmp .LFUN_0002bd80_48\n\t"
      ".LFUN_0002bd80_46:\n\t"
      "movl -0x68(%%ebp), %%eax\n\t"
      "flds 0x44(%%eax)\n\t"
      "flds 0x40(%%eax)\n\t"
      "flds 0x3c(%%eax)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x255ba0\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jne .LFUN_0002bd80_47\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fcomps 0x253f40\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002bd80_53\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fcomps 0x253f40\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002bd80_53\n\t"
      "movw $6, 0x653c(%%esi)\n\t"
      "jmp .LFUN_0002bd80_48\n\t"
      ".LFUN_0002bd80_47:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x253398\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002bd80_53\n\t"
      "movw $5, 0x653c(%%esi)\n\t"
      ".LFUN_0002bd80_48:\n\t"
      "movw 0x5f0(%%ebx), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .LFUN_0002bd80_52\n\t"
      "movw $0, 0x5f0(%%ebx)\n\t"
      ".LFUN_0002bd80_49:\n\t"
      "movswl -0x28(%%ebp), %%eax\n\t"
      "leal -0x40(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "leal 0x632780(,%%edx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x60e0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2b400]\n\t"
      "addl $0xc, %%esp\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0002bd80_50\n\t"
      "flds 0x2533c8\n\t"
      ".byte 0xd8, 0xf1\n\t"
      "flds -0x10(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002bd80_51\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c10c510]\n\t"
      "flds -0x10(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "addl $8, %%esp\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      ".LFUN_0002bd80_50:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0002bd80_51:\n\t"
      "flds 0x253f40\n\t"
      "fsubs -0x34(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fsubs 0x253398\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0002bd80_54\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_0002bd80_55\n\t"
      ".LFUN_0002bd80_52:\n\t"
      "incl %%eax\n\t"
      "movw %%ax, 0x5f0(%%ebx)\n\t"
      "jmp .LFUN_0002bd80_49\n\t"
      ".LFUN_0002bd80_53:\n\t"
      "flds -0x30(%%ebp)\n\t"
      "movw $0xffff, 0x5f0(%%ebx)\n\t"
      "fcomps 0x253398\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0002bd80_63\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fcomps 0x255b9c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002bd80_62\n\t"
      "movswl -0x28(%%ebp), %%ecx\n\t"
      "flds -0x8(%%ebp)\n\t"
      "leal (%%ecx,%%ecx,2), %%ecx\n\t"
      "fmuls 0x632788(,%%ecx,4)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x632784(,%%ecx,4)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x632780(,%%ecx,4)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcoms 0x253398\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002bd80_61\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x255b98\n\t"
      "fsubs 0x253398\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0002bd80_57\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_0002bd80_58\n\t"
      ".LFUN_0002bd80_54:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002bd80_55\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_0002bd80_55:\n\t"
      "fcoms -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0002bd80_56\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x4(%%ebp)\n\t"
      ".LFUN_0002bd80_56:\n\t"
      "movb $1, -0x11(%%ebp)\n\t"
      "jmp .LFUN_0002bd80_69\n\t"
      ".LFUN_0002bd80_57:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002bd80_58\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_0002bd80_58:\n\t"
      "fcoms -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0002bd80_59\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x4(%%ebp)\n\t"
      ".LFUN_0002bd80_59:\n\t"
      "flds 0x255b94\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x632784(,%%ecx,4)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x632788(,%%ecx,4)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002bd80_60\n\t"
      "fchs\n\t"
      ".LFUN_0002bd80_60:\n\t"
      "flds -0x60c8(%%ebp)\n\t"
      "movb $1, -0x11(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x60c4(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x60c0(%%ebp)\n\t"
      "movw $4, 0x653c(%%esi)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "fstps 0x6518(%%esi)\n\t"
      "jmp .LFUN_0002bd80_69\n\t"
      ".LFUN_0002bd80_61:\n\t"
      "fstps 0x6514(%%esi)\n\t"
      "movw $3, 0x653c(%%esi)\n\t"
      "jmp .LFUN_0002bd80_68\n\t"
      ".LFUN_0002bd80_62:\n\t"
      "movw $2, 0x653c(%%esi)\n\t"
      "jmp .LFUN_0002bd80_68\n\t"
      ".LFUN_0002bd80_63:\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002bd80_67\n\t"
      "movl 0x31fc38, %%eax\n\t"
      "flds -0x4(%%ebp)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movswl -0x28(%%ebp), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "shll $2, %%eax\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "flds 0x632788(%%eax)\n\t"
      "movl $0, -0x50(%%ebp)\n\t"
      "fchs\n\t"
      "flds -0x60bc(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds -0x24(%%ebp)\n\t"
      "flds -0x60b8(%%ebp)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fadds -0x20(%%ebp)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x60b4(%%ebp)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x632784(%%eax)\n\t"
      "fsts -0x44(%%ebp)\n\t"
      "fmuls -0x60b0(%%ebp)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x60ac(%%ebp)\n\t"
      "fmuls -0x44(%%ebp)\n\t"
      "fadds -0x20(%%ebp)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x60a8(%%ebp)\n\t"
      "fmuls -0x44(%%ebp)\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "fsts -0x1c(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0002bd80_64\n\t"
      "flds 0x2533c8\n\t"
      ".byte 0xd8, 0xf1\n\t"
      "flds -0x24(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0002bd80_65\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x255b94\n\t"
      "flds -0x24(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "jmp .LFUN_0002bd80_66\n\t"
      ".LFUN_0002bd80_64:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0002bd80_65:\n\t"
      "flds -0x50(%%ebp)\n\t"
      ".LFUN_0002bd80_66:\n\t"
      "movl -0x4c(%%ebp), %%ecx\n\t"
      "fstps 0x6520(%%esi)\n\t"
      "movb $1, -0x11(%%ebp)\n\t"
      "movw $1, 0x653c(%%esi)\n\t"
      "movl %%ecx, 0x651c(%%esi)\n\t"
      "jmp .LFUN_0002bd80_69\n\t"
      ".LFUN_0002bd80_67:\n\t"
      "movw $0, 0x653c(%%esi)\n\t"
      ".LFUN_0002bd80_68:\n\t"
      "flds -0x44(%%ebp)\n\t"
      ".LFUN_0002bd80_69:\n\t"
      "movb -0x11(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb %%al, 0x6550(%%esi)\n\t"
      "je .LFUN_0002bd80_70\n\t"
      "movw -0x28(%%ebp), %%dx\n\t"
      "movw %%dx, 0x5d8(%%ebx)\n\t"
      "jmp .LFUN_0002bd80_71\n\t"
      ".LFUN_0002bd80_70:\n\t"
      "movw $0xffff, 0x5d8(%%ebx)\n\t"
      ".LFUN_0002bd80_71:\n\t"
      "movl -0x58(%%ebp), %%edi\n\t"
      "movl -0x58(%%ebp), %%eax\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl $0x1812, %%ecx\n\t"
      "leal -0x60e0(%%ebp), %%esi\n\t"
      "addl $0x1a0, %%edi\n\t"
      "rep movsl\n\t"
      "fsts 0x654c(%%eax)\n\t"
      "leal 0x6540(%%eax), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      ".LFUN_0002bd80_72:\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, 0x4(%%ebx)\n\t"
      "movl %%edx, 0x8(%%ebx)\n\t"
      "fstps (%%eax)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(b2bd80_chkstk), [dget] "m"(b2bd80_dget), [assert] "m"(b2bd80_assert), [exitfn] "m"(b2bd80_exitfn), [get] "m"(b2bd80_get), [gtime] "m"(b2bd80_gtime), [c18e3c0] "m"(b2bd80_c18e3c0), [gbsp] "m"(b2bd80_gbsp), [c1412f0] "m"(b2bd80_c1412f0), [c2ade0] "m"(b2bd80_c2ade0), [memset] "m"(b2bd80_memset), [c2b020] "m"(b2bd80_c2b020), [c2b310] "m"(b2bd80_c2b310), [c8e0b0] "m"(b2bd80_c8e0b0), [c2b400] "m"(b2bd80_c2b400), [c10c510] "m"(b2bd80_c10c510)
      : "memory");
}
#else
#error "FUN_0002bd80: clang naked draft required"
#endif


/*
 * 0x2cdb0 — actor_path_refresh: Compute and populate the actor's path control
 * state for the current movement mode.
 *
 * This function is the per-tick "where should I go?" resolver for actors. It
 * reads the actor's movement source type (actor[0x46c]) to determine how to
 * fill the actor's destination fields (actor[0x488..0x494]) and navigation
 * state (actor[0x4a8]). After resolving the target, it initiates pathfinding
 * and sets actor[0x4a4]=1 when successful.
 *
 * Arguments:
 *   actor_handle   — datum handle identifying the actor.
 *   store_distance — if non-zero, writes the computed 3D distance to the
 *                    destination into actor[0x4a0].
 *   override_path  — if non-NULL (and actor is not mounted), use this
 *                    pre-computed path instead of computing a new one.
 *
 * Returns 1 if pathfinding succeeded (or a target was found), 0 on failure.
 *
 * Movement source types (actor[0x46c]):
 *   0 — none / disabled (early-return, mark ready).
 *   1 — disabled variant (same early-return).
 *   2 — absolute world-space position stored in actor[0x470..0x47c].
 *   3 — AI squad order position (scenario squads block).
 *   4 — encounter squad order (scenario encounter/squad/order blocks).
 *   5 — prop (perception object) position (from prop datum at actor[0x470]).
 *
 * Confirmed: cdecl, 3 args, char return.
 * Confirmed: ESI=actor ptr, EDI=&actor[0x488] after switch cases.
 * Confirmed: BL carries the function return value (0 or 1).
 * Confirmed float constants: 0.0f at 0x2533c0, threshold at 0x255d1c,
 *   threshold2 at 0x253398.
 */
char actor_path_refresh(int actor_handle, char store_distance,
                        void *override_path)
{
  /* All C89 declarations at top of function scope. */
  char *actor;
  short move_src;
  char had_path;
  char path_found;
  char path_found2;
  float saved_pos[3]; /* [EBP-0x18..-0x10]: copy of old actor[0x488..0x490] */
  char *tag; /* [EBP-0xc]: actor tag pointer from tag_get */
  float dist; /* [EBP-0x8]: 3D distance actor→destination */
  char local_nav[0x48]; /* [EBP-0x60]: nav-state struct (waypoint init output).
                         * MUST be >= 0x48: actor_path_input_new -> path_input_new
                         * does csmemset(buf, 0, 0x48). Original reserved -0x60..-0x18
                         * (0x48 bytes); a too-small [44] overflowed and zeroed the
                         * cached actor+0x4a8 nav_state_out pointer -> NULL write in
                         * path_state_build_path -> PoA campaign access-violation. */
  static char
    large_buf[0x1408c]; /* [EBP+0xfffebf14]: path-build scratch 82060 bytes */
  void
    *path_state; /* allocated path cache slot from ai_debug_get_path_storage */
  int scenario;
  int squad_elem;
  int order_elem;
  int order_elem2;
  short order_idx;
  int prop;
  int game_tick;
  unsigned int actor_handle_u;
  int ai_idx;
  float dist_sq_saved;

  /* datum_get confirmed at 0x0002cdcb: PUSH EAX(actor_handle), PUSH
   * ECX(0x6325a4) */
  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  move_src = *(short *)(actor + 0x46c);
  had_path = 0;

  /* If move_src != 0 and != 1, save old destination and set had_path. */
  if (move_src != 0 && move_src != 1) {
    saved_pos[0] = *(float *)(actor + 0x488);
    saved_pos[1] = *(float *)(actor + 0x48c);
    saved_pos[2] = *(float *)(actor + 0x490);
    had_path = 1;
  }

  /*
   * Early-return conditions — actor is busy, paused, or at a terminal state:
   *   actor[0x160] != 0 (some "is_doing" flag)
   *   move_src == 0 or 1 (no movement source)
   *   move_src == 3 && actor[0x3bb] != 0 (squad-order terminal condition)
   * In all cases: re-fetch actor, clear fields, set is_moving=1, return 1.
   * Confirmed at 0x0002d2fb: second datum_get, then BL (=1) is returned.
   */
  if (*(char *)(actor + 0x160) != '\0' || move_src == 0 || move_src == 1 ||
      (move_src == 3 && *(char *)(actor + 0x3bb) != '\0')) {
    /* Second datum_get at 0x0002d305 */
    actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
    *(int *)(actor + 0x4a0) = 0;
    *(char *)(actor + 0x4a8) = 0;
    *(char *)(actor + 0x484) = 1;
    return '\x01';
  }

  /* Clear navigation state fields for this tick. */
  *(char *)(actor + 0x4a8) = 0;
  *(char *)(actor + 0x484) = 0;
  *(int *)(actor + 0x4a0) = 0;
  *(char *)(actor + 0x506) = 0;

  /* Resolve destination by movement source type. */
  switch (move_src) {
  case 2:
    /*
     * Absolute position: copy actor[0x470..0x47c] directly.
     * Confirmed at 0x0002ce6f: LEA EDI,[ESI+0x488]; copy 3 dwords from
     * [ESI+0x470]; then [ESI+0x494] = [ESI+0x47c].
     */
    *(unsigned int *)(actor + 0x488) = *(unsigned int *)(actor + 0x470);
    *(unsigned int *)(actor + 0x48c) = *(unsigned int *)(actor + 0x474);
    *(unsigned int *)(actor + 0x490) = *(unsigned int *)(actor + 0x478);
    *(unsigned int *)(actor + 0x494) = *(unsigned int *)(actor + 0x47c);
    break;

  case 3:
    /*
     * Squad order position: look up the order waypoint from the scenario
     * squads block, indexed by actor[0x34] (squad handle low word).
     *
     * Disasm 0x0002cf62: tag_block_get_element chain (batch ESP cleanup
     * at 0x0002cfbb). Sequence:
     *   global_scenario_get() -> scenario+0x42c = &squads_block
     *   tag_block_get_element(&squads_block, squad_idx, 0xb0) -> squad
     *   tag_block_get_element(squad+0x98, actor[0x470], 0x18) -> order
     *   Copy order[0..8] -> actor[0x488..0x490], order[0x14] -> actor[0x494]
     */
    if (*(unsigned int *)(actor + 0x34) == 0xffffffff) {
      goto LAB_fail;
    }
    ai_idx = (int)(*(unsigned int *)(actor + 0x34) & 0xffff);
    scenario = (int)global_scenario_get();
    squad_elem =
      (int)tag_block_get_element((void *)(scenario + 0x42c), ai_idx, 0xb0);
    order_elem = (int)tag_block_get_element(
      (void *)(squad_elem + 0x98), (int)(short)*(short *)(actor + 0x470), 0x18);
    *(unsigned int *)(actor + 0x488) = *(unsigned int *)(order_elem + 0);
    *(unsigned int *)(actor + 0x48c) = *(unsigned int *)(order_elem + 4);
    *(unsigned int *)(actor + 0x490) = *(unsigned int *)(order_elem + 8);
    *(unsigned int *)(actor + 0x494) = *(unsigned int *)(order_elem + 0x14);
    break;

  case 4:
    /*
     * Encounter order position: look up in scenario encounters ->
     * squads -> orders, indexed by actor[0x34] (encounter handle low
     * word), actor[0x3a] (squad index), actor[0x470] (order index).
     *
     * Disasm 0x0002cec7-0x0002cf5d: same ESP batch pattern.
     * actor[0x494] = order_entry[0x4c] (facing handle).
     */
    if (*(unsigned int *)(actor + 0x34) == 0xffffffff) {
      goto LAB_fail;
    }
    ai_idx = (int)(*(unsigned int *)(actor + 0x34) & 0xffff);
    scenario = (int)global_scenario_get();
    squad_elem =
      (int)tag_block_get_element((void *)(scenario + 0x42c), ai_idx, 0xb0);
    order_elem = (int)tag_block_get_element(
      (void *)(squad_elem + 0x80), (int)(short)*(short *)(actor + 0x3a), 0xe8);
    order_idx = *(short *)(actor + 0x470);
    if (order_idx < 0) {
      goto LAB_fail;
    }
    if ((int)order_idx >= *(int *)(order_elem + 0xc4)) {
      goto LAB_fail;
    }
    order_elem2 = (int)tag_block_get_element((void *)(order_elem + 0xc4),
                                             (int)order_idx, 0x50);
    *(unsigned int *)(actor + 0x488) = *(unsigned int *)(order_elem2 + 0);
    *(unsigned int *)(actor + 0x48c) = *(unsigned int *)(order_elem2 + 4);
    *(unsigned int *)(actor + 0x490) = *(unsigned int *)(order_elem2 + 8);
    *(unsigned int *)(actor + 0x494) = *(unsigned int *)(order_elem2 + 0x4c);
    break;

  case 5:
    /*
     * Prop position: actor[0x470] is a prop datum handle. Fetch the prop
     * from prop_data (DAT_005ab23c). Validate it is in a valid-prop state
     * (prop[0x24] in [4,5]), then copy position fields.
     *
     * actor[0x99] selects between two prop position fields:
     *   ==0: prop[0xf0..0xf8] (normal position)
     *   !=0: prop[0xc8..0xd0] (vehicle/mounted position)
     * actor[0x494] = prop[0xec] (velocity handle).
     * actor[0x498] = actor[0x474] (facing yaw carry-over).
     */
    prop = (int)datum_get(*(data_t **)0x5ab23c, *(int *)(actor + 0x470));
    if ((*(short *)(prop + 0x24) < 4) || (*(short *)(prop + 0x24) > 5)) {
      /* Prop state invalid: notify and continue (don't abort). */
      actor_perception_find_prop_pathfinding_location(actor_handle,
                                                      *(int *)(actor + 0x470));
    }
    if (*(char *)(actor + 0x99) != '\0') {
      *(unsigned int *)(actor + 0x488) = *(unsigned int *)(prop + 0xc8);
      *(unsigned int *)(actor + 0x48c) = *(unsigned int *)(prop + 0xcc);
      *(unsigned int *)(actor + 0x490) = *(unsigned int *)(prop + 0xd0);
    } else {
      *(unsigned int *)(actor + 0x488) = *(unsigned int *)(prop + 0xf0);
      *(unsigned int *)(actor + 0x48c) = *(unsigned int *)(prop + 0xf4);
      *(unsigned int *)(actor + 0x490) = *(unsigned int *)(prop + 0xf8);
    }
    *(unsigned int *)(actor + 0x494) = *(unsigned int *)(prop + 0xec);
    *(unsigned int *)(actor + 0x498) = *(unsigned int *)(actor + 0x474);
    goto LAB_check_dest;

  default:
    display_assert((char *)0, "c:\\halo\\SOURCE\\ai\\actor_moving.c", 0xb7f, 1);
    system_exit(-1);
    goto LAB_fail;
  }

  /* Cases 2/3/4 fall through here; case 5 jumps to LAB_check_dest. */
  *(int *)(actor + 0x498) = 0;

LAB_check_dest:
  /*
   * Validate destination. Two branches:
   *
   * B) actor[0x99]!=0 (mounted): call actor_path_3d_available to check whether
   * the destination is accessible for a mounted actor; output dist. Confirmed
   * at 0x0002ceab-0x0002cebf: JZ skip (actor[0x99]==0) PUSH
   * LEA[EBP-0xc](&dist); PUSH EDI(&actor[0x488]); PUSH ECX CALL
   * actor_path_3d_available
   *
   * A) actor[0x99]==0 (on foot): if actor[0x498]==0.0f, check
   *    actor[0x494]!=-1. If -1, fail. If actor[0x498]!=0.0f, fall through.
   *    Confirmed at 0x0002d096-0x0002d0b3.
   */
  if (*(char *)(actor + 0x99) != '\0') {
    path_found =
      actor_path_3d_available(actor_handle, (float *)(actor + 0x488), &dist);
    if (path_found == '\0') {
      goto LAB_fail;
    }
  } else {
    if (*(float *)(actor + 0x498) == 0.0f) {
      path_found = (char)(*(int *)(actor + 0x494) != -1);
      if (path_found == '\0') {
        goto LAB_fail;
      }
    }
  }

  /* Try fast path: actor is already navigating to the same destination. */
  path_found = actor_test_destination(actor_handle);
  if (path_found != '\0') {
    if (!had_path) {
      goto LAB_path_ok;
    }
    /*
     * Had a previous destination endpoint. Compute squared distance between
     * the saved endpoint (saved_pos) and the new destination (actor[0x488]).
     * If close enough (dist_sq <= threshold at 0x255d1c), return 1 quickly.
     * If destination has changed significantly, fall through to do a full
     * re-path.
     * Confirmed at 0x0002d0d6-0x0002d0ee:
     *   LEA EDX,[EBP-0x18](saved_pos); PUSH EDI(&actor[0x488]); PUSH EDX
     *   CALL distance_squared3d  (distance_squared3d = 0x000121a0)
     *   FCOMP [0x255d1c]; FNSTSW AX; TEST AH,0x41; JNZ 0x2d32a (return 1)
     * JNZ taken when: AH & 0x41 != 0 → C3|C0 set → FPU flags for <=
     *   So jump to return-1 when dist_sq <= threshold.
     *   Fall through (full repath) when dist_sq > threshold.
     */
    dist_sq_saved =
      (float)distance_squared3d(saved_pos, (float *)(actor + 0x488));
    if (dist_sq_saved <= *(float *)0x255d1c) {
      goto LAB_path_ok;
    }
    /* Destination changed significantly: fall through to full pathfinding. */
  }

  /*
   * actor_test_destination failed. Compute actual 3D distance from actor
   * position to destination, allocate path cache, and run the pathfinder.
   *
   * tag_get at 0x0002d0f7: PUSH [ESI+0x58]; PUSH 0x61637472 ('rtra'='actr')
   * FUN_0001ad60 at 0x0002d10d: PUSH EDI(&actor[0x488]); PUSH &actor[0x12c]
   *   returns float in FPU; FSTP [EBP-0x8] -> dist
   * game_time_get at 0x0002d12c: no args -> current game tick
   * Confirmed at 0x0002d131: MOV [EBX+4],EAX (path slot timestamp)
   */
  tag = (char *)tag_get(0x61637472, *(int *)(actor + 0x58));
  dist =
    (float)FUN_0001ad60((float *)(actor + 0x12c), (float *)(actor + 0x488));
  actor_handle_u = (unsigned int)actor_handle;
  game_tick = game_time_get();
  *(int *)((actor_handle_u & 0xffff) * 0x657c + *(int *)0x331f58 + 4) =
    game_tick;

  /* Select pathfinding mode: mounted (vehicle) vs on-foot vs override. */
  if (*(char *)(actor + 0x99) != '\0') {
    /*
     * Mounted: use scenario-based vehicle pathfinding (path_3d_build_path).
     * Args confirmed at 0x0002d13e-0x0002d155:
     *   pre-push: &actor[0x4a8], &actor[0x488](EDI), 0, &actor[0x12c]
     *   scenario_get() -> push EAX
     *   CALL path_3d_build_path(scenario, &actor[0x12c], 0, &actor[0x488],
     *                     &actor[0x4a8])
     * ADD ESP,0x14 = 5 args.
     */
    path_found =
      path_3d_build_path((int)scenario_get(), (int *)(actor + 0x12c), 0,
                         (int *)(actor + 0x488), (char *)(actor + 0x4a8));
  } else if (override_path != (void *)0) {
    /*
     * Caller provided a pre-computed path override.
     * Assert: actor[0x480] (dest_object) must be NONE (-1).
     * Then set up override_path as the navigation state:
     *   FUN_0005e0d0(override_path, &actor[0x488], actor[0x494], actor[0x498])
     *   path_state_build_path(override_path, &actor[0x4a8])
     * Confirmed at 0x0002d194: MOV ECX,[ESI+0x498]; MOV EDX,[ESI+0x494];
     *   PUSH ECX; PUSH EDX; PUSH EDI(&actor[0x488]); PUSH EBX(override_path);
     *   CALL FUN_0005e0d0 -> args (override_path, &actor[0x488], actor[0x494],
     *   actor[0x498]) — same destination/facing setup as the on-foot branch,
     *   only the path-build buffer differs (override_path vs large_buf). The
     *   prior lift passed (override_path, &actor[0x494], actor[0x498], 0),
     *   which seeded the override path-build state with the FACING field as
     *   the destination -> path_state_build_path failed -> scripted a10 door
     *   grunts could not advance to their firing positions.
     */
    if (*(int *)(actor + 0x480) != -1) {
      display_assert("actor->control.path.destination_orders."
                     "ignore_target_object_index == NONE",
                     "c:\\halo\\SOURCE\\ai\\actor_moving.c", 0xbbc, 1);
      system_exit(-1);
    }
    FUN_0005e0d0(override_path, (float *)(actor + 0x488),
                 *(int *)(actor + 0x494), *(int *)(actor + 0x498));
    path_found = path_state_build_path((unsigned int)override_path,
                                       (unsigned int *)(actor + 0x4a8));
  } else {
    /*
     * Normal on-foot pathfinding pipeline:
     *  1. actor_path_input_new(actor_handle, local_nav): initialize nav-state
     * struct (actor position, facing, vehicle info, etc.).
     *  2. paths_dispose(local_nav, actor[0x480]): if ignore_object!=-1,
     *     store it at local_nav+0xc.
     *  3. (Optional) path_input_set_attractor: encode movement-constraint
     * orders into local_nav when actor has standing orders (actor[0x280]>0,
     *     actor[0x28a]==0, tag flag bit 4 clear). Float arg 0x41200000=10.0f.
     *  4. ai_debug_get_path_storage(actor_handle): allocate/find path cache
     * slot.
     *  5. path_state_new(local_nav, large_buf, path_state): init path-build
     *     state in large_buf from local_nav and the cache slot.
     *  6. FUN_0005e0d0(large_buf, &actor[0x488], actor[0x494], actor[0x498]):
     *     set destination in path-build state.
     *  7. FUN_0005ff70(large_buf): run pathfinder; returns 1 on success.
     *  8. path_state_build_path(large_buf, &actor[0x4a8]): extract waypoint
     * result into actor nav-control struct. Returns 1 if path is usable.
     *
     * Disasm confirmed:
     *   local_nav at [EBP-0x60] (44 bytes)
     *   large_buf at [EBP+0xfffebf14] (82060 bytes = 0x1408c)
     */
    actor_path_input_new(actor_handle, local_nav);
    if (*(int *)(actor + 0x480) != -1) {
      paths_dispose(local_nav, *(int *)(actor + 0x480));
    }
    if ((*(short *)(actor + 0x280) > 0) && (*(char *)(actor + 0x28a) == '\0') &&
        ((*(unsigned char *)(tag + 4) & 0x10) == 0)) {
      path_input_set_attractor(
        local_nav, (float *)(actor + 0x2b0), *(float *)(actor + 0x294),
        *(unsigned int *)(actor + 0x28c),
        10.0f); /* original PUSHes bits 0x41200000 = 10.0f attractor weight.
                   param_5 is float: an (unsigned int) cast here would do an
                   int->float NUMERIC conversion (1.09e9), not a bit-reinterpret,
                   corrupting the A* attractor weight -> path.c:1005 cost assert. */
    }
    path_state = ai_debug_get_path_storage(actor_handle);
    path_state_new(local_nav, large_buf, path_state);
    FUN_0005e0d0(large_buf, (float *)(actor + 0x488), *(int *)(actor + 0x494),
                 *(int *)(actor + 0x498));
    path_found = FUN_0005ff70((unsigned int *)large_buf);
    if (path_found != '\0') {
      path_found2 = path_state_build_path((unsigned int)large_buf,
                                          (unsigned int *)(actor + 0x4a8));
      path_found = path_found2 ? '\x01' : '\0';
    }
  }

  /* Mark path-computation attempted this tick. */
  *(char *)(actor + 0x4a4) = 1;
  if (store_distance != '\0') {
    *(float *)(actor + 0x4a0) = dist;
  }

  if (path_found != '\0') {
    /*
     * Pathfinding succeeded. Hysteresis check: if the actor was already
     * moving (actor[0x4bc]>0.0f) and the new distance is less than the
     * expected move distance (dist < actor[0x498]) AND the delta is small
     * (dist - actor[0x4bc] < threshold), reset the path to avoid jitter.
     * Confirmed at 0x0002d2ad-0x0002d2f2:
     *   FLD [ESI+0x4bc]; FCOMP 0.0f; TEST AH,0x41; JNZ done
     *   FLD dist; FCOMP [ESI+0x498]; TEST AH,0x5; JP done
     *   FLD dist; FSUB [ESI+0x4bc]; FCOMP [0x253398]; TEST AH,0x5; JP done
     *   CALL FUN_0002a3a0(actor_handle)
     */
    if ((*(float *)(actor + 0x4bc) > 0.0f) &&
        (dist < *(float *)(actor + 0x498)) &&
        (dist - *(float *)(actor + 0x4bc) < *(float *)0x253398)) {
      FUN_0002a3a0(actor_handle);
    }
    return path_found;
  }

LAB_fail:
  FUN_0002a3a0(actor_handle);
  return '\0';

LAB_path_ok:
  /*
   * actor_test_destination fast-path success. At 0x2d32a the original simply
   * loads AL=1 and returns — NO side effects (does not touch actor[0x4a4] or
   * actor[0x4a0]). On this path `dist` is not yet computed (it is computed at
   * 0x2d10d, which is bypassed), so writing it would be UB. Just return 1.
   */
  return '\x01';
}


/* 0x2d350 — actor_destination_update: Update actor path state and compute
 * target destination.
 *
 * Called every tick for an actor. Has three main branches:
 *
 * 1. PATH ACTIVE (actor[0x4a8] != 0):
 *    Walks the actor's waypoint path. Each tick it checks whether the actor
 *    has reached the current path node (within 0.15 world units, 2D) or is
 *    close enough to the segment (within 0.25 units perpendicular). If so,
 *    it advances path_step_index. When path is exhausted (step_index+1 >=
 *    step_count), sets path_final_step and either calls actor_path_stop
 *    (if path_loop) or logs "fell off end of unfinished path" (debug).
 *    Then copies the current waypoint to actor[0x50c] as the movement target
 *    and computes actor[0x518] = target - actor_position. Validates that
 *    the distance is less than 1,000,000 world units ("tau ceti" guard).
 *
 * 2. MOVEMENT TYPE != 4 (no far-movement):
 *    Resets path state (has_destination=0, final_step=0, is_moving=1) and
 *    clears path_active. Returns.
 *
 * 3. MOVEMENT TYPE == 4 (far_movement, seek/flee):
 *    Computes a step 3.0 world units ahead (or behind) along the actor's
 *    facing vector. Direction sign: +1 if actor[0x5ec] <= 0.9f, else -1.
 *    Writes target offset and absolute position into actor[0x518..0x514].
 *
 * Confirmed: cdecl, 1 arg (actor_handle), void return.
 * Confirmed: EBX=actor_handle, ESI=actor_ptr, EDI=&actor[0x4a8].
 * Confirmed float constants: 0.0225f=near_sq(0.15), 0.0625f=seg_sq(0.25),
 *   0.0f=zero, 1000000.0f=tau_ceti_sq, 3.0f=step_dist, 0.9f=facing_thresh.
 */
void actor_destination_update(int actor_handle)
{
  char *actor;
  char *path_ctl;
  char exhausted;
  int step_idx;
  int step_cnt;
  int cur_off;
  int next_off;
  float cur_x, cur_y, next_x, next_y;
  float to_cur_x, to_cur_y;
  float seg_x, seg_y;
  float dot_seg_to_cur, dot_seg_facing;
  float t, perp_x, perp_y, perp_sq;
  float dist_sq;
  char name_buf[0x200];
  float *node;
  float dx, dy, dz, dist;
  int sign_val;
  float step;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);

  if (*(char *)(actor + 0x4c) != '\0' && *(char *)(actor + 0x4a4) == '\0' &&
      *(char *)(actor + 0x13) == '\0') {
    actor_path_refresh(actor_handle, 0, 0);
  }

  actor_test_destination(actor_handle);

  path_ctl = actor + 0x4a8;
  if (*(char *)(actor + 0x4a8) != '\0') {
    exhausted = '\0';

    while (1) {
      step_idx = (int)*(signed char *)(actor + 0x4c2);
      step_cnt = (int)*(signed char *)(actor + 0x4c1);

      if (step_idx + 1 >= step_cnt) {
        exhausted = '\x01';
        break;
      }

      cur_off = (step_idx + 2) * 0x10;
      next_off = (step_idx + 3) * 0x10;

      cur_x = *(float *)(path_ctl + cur_off);
      cur_y = *(float *)(path_ctl + cur_off + 4);
      next_x = *(float *)(path_ctl + next_off);
      next_y = *(float *)(path_ctl + next_off + 4);

      to_cur_x = cur_x - *(float *)(actor + 0x12c);
      to_cur_y = cur_y - *(float *)(actor + 0x130);

      seg_x = next_x - cur_x;
      seg_y = next_y - cur_y;

      /* Load path_final_step flag (actor+0x506). */
      if (*(char *)(actor + 0x506) == '\0') {
        /* Check whether to use simple distance or projected segment test. */
        if (*(char *)(actor + 0x504) != '\0' &&
            *(char *)(actor + 0x507) != '\0') {
          /* Segment projection test.
           *
           * dot_seg_to_cur = dot(seg_dir, to_cur)
           * dot_seg_facing = dot(seg_dir, actor_facing)
           *
           * Skip advance if:
           *   - dot_seg_facing <= 0.0f (not facing toward next step), OR
           *   - dot_seg_to_cur >= 0.0f (actor already past current node)
           *
           * If both pass, compute perpendicular distance from actor to segment
           * and advance only if perp_dist_sq < 0.0625f.
           *
           * Disassembly verified operand order:
           *   0x2d425: FLD [EBP-0x10] (seg_y) FMUL [EBP-0x8] (to_cur_y)
           *   0x2d42b: FLD [EBP-0x14] (seg_x) FMUL [EBP-0xc] (to_cur_x)
           *   FADDP => dot_seg_to_cur = seg_y*to_cur_y + seg_x*to_cur_x
           *   0x2d433: FLD [EBP-0x10] (seg_y) FMUL [ESI+0x178] (facing_y)
           *   0x2d43f: FLD [EBP-0x14] (seg_x) FMUL [ESI+0x174] (facing_x)
           *   FADDP => dot_seg_facing = seg_y*facing_y + seg_x*facing_x
           */
          dot_seg_to_cur = seg_y * to_cur_y + seg_x * to_cur_x;
          dot_seg_facing = seg_y * *(float *)(actor + 0x178) +
                           seg_x * *(float *)(actor + 0x174);

          /* FCOMP [0x2533c0]=0.0f; TEST AH,0x41; JNZ => jump if <= 0 */
          if (dot_seg_facing <= 0.0f) {
            break;
          }
          /* FCOM [0x2533c0]=0.0f; TEST AH,0x5; JP => jump if >= 0 */
          if (dot_seg_to_cur >= 0.0f) {
            break;
          }

          /* Perpendicular distance from actor to segment line.
           * t = -dot_seg_to_cur (positive, since dot_seg_to_cur < 0)
           * perp = to_cur + t * seg_dir
           * perp_sq = perp.x^2 + perp.y^2
           *
           * Disasm 0x2d461-0x2d47b:
           *   FCHS   => t = -dot_seg_to_cur (ST0 now t)
           *   FLD seg_x; FMUL ST1 => seg_x * t
           *   FADD to_cur_x => perp_x = seg_x*t + to_cur_x
           *   FLD seg_y; FMUL ST2 => seg_y * t (ST2 = t)
           *   FADD to_cur_y => perp_y = seg_y*t + to_cur_y
           *   FLD ST0; FMUL ST1 => perp_y*perp_y
           *   FLD ST2; FMUL ST3 => perp_x*perp_x (ST3=perp_x)
           *   Wait: at 0x2d473: FLD ST0 = perp_y, FMUL ST1 = perp_y*perp_y
           *         0x2d477: FLD ST2 = perp_x, FMUL ST3 = perp_x*perp_y ... no
           *
           * Re-trace FPU stack at 0x2d461:
           *   ST0 = dot_seg_to_cur (the one from FADDP at 0x2d431)
           *   dot_seg_facing was computed 0x2d433-0x2d445, then FCOMP popped it
           *   So at 0x2d461: ST0 = dot_seg_to_cur
           *   FCHS => ST0 = t = -dot_seg_to_cur
           *   0x2d463: FLD seg_x (ST0=seg_x, ST1=t)
           *   0x2d466: FMUL ST1 => ST0 = seg_x*t; ST1=t
           *   0x2d468: FADD to_cur_x => ST0 = perp_x; ST1=t
           *   0x2d46b: FLD seg_y (ST0=seg_y, ST1=perp_x, ST2=t)
           *   0x2d46e: FMUL ST2 => ST0 = seg_y*t; ST1=perp_x; ST2=t
           *   0x2d470: FADD to_cur_y => ST0=perp_y; ST1=perp_x; ST2=t
           *   0x2d473: FLD ST0 => ST0=perp_y; ST1=perp_y; ST2=perp_x; ST3=t
           *   0x2d475: FMUL ST1 => ST0=perp_y*perp_y; ST1=perp_y; ST2=perp_x
           *   0x2d477: FLD ST2 => ST0=perp_x; ST1=perp_y*perp_y; ST2=perp_y;
           * ST3=perp_x 0x2d479: FMUL ST3 => ST0=perp_x*perp_x;
           * ST1=perp_y*perp_y 0x2d47b: FADDP => ST0=perp_x*perp_x+perp_y*perp_y
           * = perp_sq
           */
          t = -dot_seg_to_cur;
          perp_x = seg_x * t + to_cur_x;
          perp_y = seg_y * t + to_cur_y;
          perp_sq = perp_x * perp_x + perp_y * perp_y;

          /* FCOMP [0x255d90]=0.0625f; TEST AH,0x5; JP => jump if >= 0.0625f */
          if (perp_sq >= 0.0625f) {
            break;
          }
        } else {
          /* Simple 2D distance-to-current-node check.
           * Disasm 0x2d48b-0x2d499:
           *   FLD to_cur_y; FMUL to_cur_y  => to_cur_y^2
           *   FLD to_cur_x; FMUL to_cur_x  => to_cur_x^2
           *   FADDP => dist_sq
           *   FCOMP [0x255d8c]=0.0225f; TEST AH,0x5; JP => jump if >= 0.0225f
           */
          dist_sq = to_cur_y * to_cur_y + to_cur_x * to_cur_x;
          if (dist_sq >= 0.0225f) {
            break;
          }
        }
      }

      /* Advance to next step. */
      *(signed char *)(actor + 0x4c2) += 1;
      *(char *)(actor + 0x506) = '\0';
    }

    /* Handle path-exhausted or final-step state. */
    if (*(char *)(actor + 0x506) != '\0') {
      if (exhausted == '\0') {
        /* Reached the final step but loop says we shouldn't be here. */
        display_assert("final_step", "c:\\halo\\SOURCE\\ai\\actor_moving.c",
                       0xb4, 1);
        system_exit(-1);
      }

      if (*(char *)(actor + 0x4c0) != '\0') {
        /* Path has a loop/done handler — call actor_path_stop. */
        FUN_0002a3a0(actor_handle);
      } else if (*(char *)0x5aca62 != '\0') {
        /* Debug: log "fell off end of unfinished path".
         * ai_debug_describe_actor: actor_describe_name(actor_handle, -1, 1,
         * buf, 0x200) Disasm 0x2d518-0x2d529: PUSH 0x200; PUSH EDX(local_218);
         * PUSH 1; PUSH -1; PUSH EBX
         */
        ai_debug_describe_actor(actor_handle, -1, 1, name_buf, 0x200);
        error(2, "%s: fell off end of unfinished path %d/%d", name_buf,
              (int)*(signed char *)(actor + 0x4c1), 4);
      }
    }

    /* If path_active and (has_destination or not is_moving), set the
     * current target position from the path node at step_index. */
    if (*path_ctl != '\0' && (*(char *)(actor + 0x504) != '\0' ||
                              *(char *)(actor + 0x484) == '\0')) {
      *(char *)(actor + 0x504) = '\x01';

      /* Copy node position: actor[0x4c8 + step_index*0x10] → actor[0x50c].
       * Disasm 0x2d574-0x2d5a1: MOVSX EDX,byte[ESI+0x4c2]; SHL EDX,4;
       *   LEA ECX,[EDX+ESI+0x4c8]; copy 3 dwords to [ESI+0x50c].
       */
      step_idx = (int)*(signed char *)(actor + 0x4c2);
      node = (float *)(actor + 0x4c8 + step_idx * 0x10);

      *(float *)(actor + 0x50c) = node[0];
      *(float *)(actor + 0x510) = node[1];
      *(float *)(actor + 0x514) = node[2];

      /* Compute vector from actor to target. */
      *(float *)(actor + 0x518) =
        *(float *)(actor + 0x50c) - *(float *)(actor + 0x12c);
      *(float *)(actor + 0x51c) =
        *(float *)(actor + 0x510) - *(float *)(actor + 0x130);
      *(float *)(actor + 0x520) =
        *(float *)(actor + 0x514) - *(float *)(actor + 0x134);

      /* Sanity check: if distance^2 < 1,000,000 (i.e. < 1000 units), OK.
       * Disasm 0x2d5d0-0x2d605: FPU computes sqrt(dx^2+dy^2+dz^2), then
       *   FCOMP [0x255d50]=1000000.0f; TEST AH,0x1; JNZ => jump if < 1000000.
       * TEST AH,0x1 = test C0 (ST0 < mem). JNZ = jump if C0 set (sqrt <
       * 1000000). But FSQRT was done before, so we compare sqrt (distance)
       * against sqrt(1000000) = 1000? No — looking again at disasm: FSQRT at
       * 0x2d5f2 FSTP ST3 at 0x2d5f4 (saves result into ST3 slot, discards from
       * top) FSTP ST0 twice (discards remaining ST0, ST1) Then FCOMP [0x255d50]
       * at 0x2d5fa After FSTP ST3: the stack shrinks, so the FCOMP operand is
       * the distance value itself (the sqrt result stored into ST3 then brought
       * to top via the STPs). Actually:
       *   At 0x2d5d0: FLD dz -> FLD dy -> FLD dx -> FLD ST0 (=dx)
       *   0x2d5e4: FMUL ST1 => dx*dx; stack: dx*dx, dx, dy, dz
       *   0x2d5e6: FLD ST2 (=dy); FMUL ST3 (=dy) => dy*dy
       *   0x2d5ea: FADDP => dx*dx+dy*dy; stack: sum, dx, dy, dz
       *   0x2d5ec: FLD ST3 (=dz); FMUL ST4 (=dz) => dz*dz
       *   0x2d5f0: FADDP => sum+dz*dz; stack: dist_sq, dx, dy, dz
       *   0x2d5f2: FSQRT => dist; stack: dist, dx, dy, dz
       *   0x2d5f4: FSTP ST3 => ST3=dist, pops: stack: dx, dy, dist
       *     (FSTP ST3 stores ST0 into ST3 slot then pops ST0)
       *     After: ST0=dx, ST1=dy, ST2=dist, ST3=dz was at ST3
       *     Wait: FSTP STn stores ST0 into STn then pops. After FSQRT:
       *       ST0=dist, ST1=dx, ST2=dy, ST3=dz
       *     FSTP ST3: ST3 = dist, pop ST0: ST0=dx, ST1=dy, ST2=dz -> wait
       *     Actually FSTP ST3 sets ST3=ST0=dist, then increments stack pointer
       *     (pops ST0). So new stack: ST0=dx, ST1=dy, ST2=dz, ST3=dist
       *   0x2d5f6: FSTP ST0 => discard dx; ST0=dy, ST1=dz, ST2=dist
       *   0x2d5f8: FSTP ST0 => discard dy; ST0=dz, ST1=dist
       *   Hmm, but FCOMP at 0x2d5fa uses 1 operand and pops ST0.
       *   We need dist to be in ST0. Let me re-read disasm...
       *   0x2d5f4: FSTP ST3 => stores dist into position 3 (which is dz), pops
       * ST0 After: ST0=dx, ST1=dy, ST2=dz(overwritten=dist) 0x2d5f6: FSTP ST0
       * => pops ST0=dx, discards it After: ST0=dy, ST1=dist 0x2d5f8: FSTP ST0
       * => pops ST0=dy, discards it After: ST0=dist 0x2d5fa: FCOMP
       * [0x255d50]=1000000.0f => compares dist to 1000000.0f TEST AH,0x1 =>
       * test C0 (ST0<mem). JNZ => jump if dist < 1000000.0f
       *
       * So we compare distance (not distance^2) to 1,000,000. This is
       * "tau ceti" = 1 million world units (absurd distance).
       */
      dx = *(float *)(actor + 0x518);
      dy = *(float *)(actor + 0x51c);
      dz = *(float *)(actor + 0x520);
      dist = sqrtf(dx * dx + dy * dy + dz * dz);

      /* Jump past error if distance is sane (< 1,000,000 units). */
      if (dist < 1000000.0f) {
        return;
      }

      /* Insanely far target: log error and clear path. */
      error(2, "pathfinding is attempting to walk to tau ceti");
      *path_ctl = '\0';
      return;
    }
    /*
     * Fall through to the move-type evaluation (0x2d624). The path-active
     * block does NOT unconditionally return: at 0x2d556 (*path_ctl cleared,
     * e.g. by actor_path_stop) and at 0x2d56e (path active but
     * actor[0x504]==0 && actor[0x484]!=0) the original jumps to the shared
     * move-type tail at 0x2d624. The set-target block above returns on both
     * its exits, so only those two fall-through edges reach here.
     */
  }

  /*
   * Move-type evaluation (join at 0x2d624): reached when the path was never
   * active (entry 0x2d3ac), when an active path was cleared, or when an
   * active path yielded no target this tick.
   */
  if (*(short *)(actor + 0x15e) != 4) {
    /* Not far-movement: reset path destination and target state. */
    *(char *)(actor + 0x504) = '\0';
    *(char *)(actor + 0x506) = '\0';
    *(char *)(actor + 0x484) = '\x01';

    /* Re-fetch actor (second datum_get call in this branch, confirmed at
     * 0x2d6ea). */
    actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
    *(char *)(actor + 0x4a8) = '\0';
    *(char *)(actor + 0x484) = '\x01';
    *(int *)(actor + 0x4a0) = 0;
    return;
  }

  /* Movement type == 4: far_movement. Compute step along facing vector.
   *
   * actor[0x5ec]: if > 0.9f → sign=-1 (backward), else sign=+1 (forward).
   * Disasm 0x2d632-0x2d693:
   *   FLD [ESI+0x5ec]; FCOMP [0x2555d0]=0.9f; FNSTSW AX
   *   TEST AH,0x41; JNZ 0x2d649 (set AL=0); else: MOV AL,1
   *   XOR EDX,EDX; TEST AL,AL; SETZ DL   => DL=1 if AL==0, DL=0 if AL!=0
   *   LEA EDX,[EDX+EDX-1]                => EDX = DL*2 - 1
   *     if actor[0x5ec]>0.9: AL=1,DL=0 → EDX=-1
   *     if actor[0x5ec]<=0.9: AL=0,DL=1 → EDX=1
   *   FILD [EBP-0x8] (=EDX); FMUL [0x254644]=3.0f  => sign * 3.0
   */
  *(char *)(actor + 0x504) = '\x01';
  *(char *)(actor + 0x506) = '\0';

  /* FCOMP test: if actor[0x5ec] <= 0.9f → sign=+1, else sign=-1 */
  if (*(float *)(actor + 0x5ec) > 0.9f) {
    sign_val = -1;
  } else {
    sign_val = 1;
  }

  step = (float)sign_val * 3.0f;

  *(float *)(actor + 0x518) = step * *(float *)(actor + 0x174);
  *(float *)(actor + 0x51c) = step * *(float *)(actor + 0x178);
  *(float *)(actor + 0x520) = step * *(float *)(actor + 0x17c);

  *(float *)(actor + 0x50c) =
    *(float *)(actor + 0x12c) + *(float *)(actor + 0x518);
  *(float *)(actor + 0x510) =
    *(float *)(actor + 0x130) + *(float *)(actor + 0x51c);
  *(float *)(actor + 0x514) =
    *(float *)(actor + 0x134) + *(float *)(actor + 0x520);
}



/* actor_move_to_point (0x2d720) — readable C lift. */
char actor_move_to_point(int actor_handle, float *destination, int param_3,
                         int param_4)
{
  char *actor;
  float dx, dy, dz, dist2;
  int i;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (destination == NULL) {
    display_assert((const char *)0x255d94, (const char *)0x255984, 0x3b7, 1);
    system_exit(-1);
  }
  *(int16_t *)(actor + 0x3b8) = -1;
  actor_set_dormant(actor_handle, 0);
  if (*(int16_t *)(actor + 0x46c) == 2 &&
      *(int *)(actor + 0x47c) == param_3) {
    dx = *(float *)(actor + 0x470) - destination[0];
    dy = *(float *)(actor + 0x474) - destination[1];
    dz = *(float *)(actor + 0x478) - destination[2];
    dist2 = dx * dx + dy * dy + dz * dz;
    if (dist2 <= *(float *)0x255d1c) {
      if (actor[0x4c] == 0 || actor[0x4a4] != 0)
        return 1;
      return actor_path_refresh(actor_handle, 0, NULL);
    }
  }
  actor[0x402] = 0;
  *(int16_t *)(actor + 0x400) = 2;
  *(float *)(actor + 0x404) = destination[0];
  *(float *)(actor + 0x408) = destination[1];
  *(float *)(actor + 0x40c) = destination[2];
  *(int *)(actor + 0x410) = param_3;
  *(int *)(actor + 0x414) = param_4;
  for (i = 0; i < 6; i++)
    ((int *)(actor + 0x46c))[i] = ((int *)(actor + 0x400))[i];
  return actor_path_refresh(actor_handle, 1, NULL);
}

/* actor_move_to_move_position (0x2d850) — readable C lift from XBE leaf. */
char actor_move_to_move_position(int actor_handle, int16_t pos_index)
{
  char *actor;
  int16_t *dst;
  int i;
  int *src;
  int *out;

  actor = (char *)datum_get(actor_data, actor_handle);
  *(int16_t *)(actor + 0x3b8) = (int16_t)-1;
  actor_set_dormant(actor_handle, 0);
  dst = (int16_t *)(actor + 0x46c);
  if (dst[0] == 4 && *(int16_t *)(actor + 0x470) == pos_index) {
    if (actor[0x4c] == 0 || actor[0x4a4] != 0)
      return 1;
    return actor_path_refresh(actor_handle, 0, 0);
  }
  *(int16_t *)(actor + 0x404) = pos_index;
  *(int *)(actor + 0x414) = -1;
  actor[0x402] = 0;
  *(int16_t *)(actor + 0x400) = 4;
  src = (int *)(actor + 0x400);
  out = (int *)(actor + 0x46c);
  for (i = 0; i < 6; i++)
    out[i] = src[i];
  return actor_path_refresh(actor_handle, 1, 0);
}



/* actor_move_to_firing_position (0x2d900) — readable C lift from XBE leaf. */
char actor_move_to_firing_position(int actor_handle, int16_t pos_index, void *override_path)
{
  char *actor;
  int16_t *dst;
  int i;
  int *src;
  int *out;

  actor = (char *)datum_get(actor_data, actor_handle);
  actor_set_dormant(actor_handle, 0);
  dst = (int16_t *)(actor + 0x46c);
  if (dst[0] == 3 && *(int16_t *)(actor + 0x470) == pos_index) {
    if (actor[0x4c] == 0 || actor[0x4a4] != 0)
      return 1;
    return actor_path_refresh(actor_handle, 0, override_path);
  }
  *(int16_t *)(actor + 0x404) = pos_index;
  actor[0x402] = 0;
  *(int *)(actor + 0x414) = -1;
  actor[0x3bb] = 0;
  *(int16_t *)(actor + 0x400) = 3;
  src = (int *)(actor + 0x400);
  out = (int *)(actor + 0x46c);
  for (i = 0; i < 6; i++)
    out[i] = src[i];
  return actor_path_refresh(actor_handle, 1, override_path);
}



/* actor_move_to_prop (0x2d9b0) — readable C lift. */
char actor_move_to_prop(int actor_handle, int prop_handle, float distance)
{
  char *actor;
  char *prop;
  int unit_handle;
  int i;

  actor = (char *)datum_get(actor_data, actor_handle);
  *(int16_t *)(actor + 0x3b8) = -1;
  actor_set_dormant(actor_handle, 0);
  if (*(int16_t *)(actor + 0x46c) == 5 &&
      *(int *)(actor + 0x470) == prop_handle &&
      *(float *)(actor + 0x474) == distance) {
    if (actor[0x4c] == 0 || actor[0x4a4] != 0)
      return 1;
    return actor_path_refresh(actor_handle, 0, NULL);
  }
  prop = (char *)datum_get(*(data_t **)0x5ab23c, prop_handle);
  *(int *)(actor + 0x404) = prop_handle;
  *(int16_t *)(actor + 0x400) = 5;
  actor[0x402] = 0;
  *(float *)(actor + 0x408) = distance;
  unit_handle = *(int *)(prop + 0x110);
  if (unit_handle == -1)
    unit_handle = *(int *)(prop + 0x18);
  *(int *)(actor + 0x414) = unit_handle;
  for (i = 0; i < 6; i++)
    ((int *)(actor + 0x46c))[i] = ((int *)(actor + 0x400))[i];
  return actor_path_refresh(actor_handle, 1, NULL);
}

/* actor_move_compute_facing (0x2daa0) — XBE naked draft (batch 79). */
#if defined(__clang__)
static void *(*const b2daa0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b2daa0_tag)(int, int) = tag_get;
static float (*const b2daa0_norm)(float *) = normalize3d;
static void (*const b2daa0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b2daa0_exitfn)(int) = system_exit;
static void (*const b2daa0_c2bab0)(char use_3d , float *movement_direction , float *facing_direction , float *out) = FUN_0002bab0;
static void (*const b2daa0_c2b830)(float *facing_basis , char use_3d, float *out_vector, short *out_index, float *in_vec , float *weight_vec) = FUN_0002b830;
static bool (*const b2daa0_c21fb0)(float *v) = valid_real_normal3d;
static char * (*const b2daa0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b2daa0_c3bc90)(int actor_handle) = actor_find_pathfinding_location;
static float (*const b2daa0_mag)(float *) = magnitude3d;
static float *(*const b2daa0_vsca)(float *, float *, float, float *) = vector3d_scale_add;
static void * (*const b2daa0_c18e3c0)(void) = scenario_get;
static char (*const b2daa0_c639e0)(int scenario, unsigned char bsp_idx, float *origin, int start_surface, float *target, int end_surface, char *result_buf) = FUN_000639e0;
static float (*const b2daa0_c3bd50)(int actor_handle) = actor_destination_tolerance;
static void (*const b2daa0_c2a610)(int actor_handle, float *param_2, float *param_3) = actor_get_stopping_distances;
static short (*const b2daa0_cfff80)(void) = game_connection;
static void (*const b2daa0_c1d94f0)(void) = FUN_001d94f0;
static void (*const b2daa0_cff4d0)(int channel, const char *format, ...) = console_printf;
static void (*const b2daa0_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;

__attribute__((naked, noinline))
void actor_move_compute_facing(char want_facing __attribute__((unused)), short move_dir __attribute__((unused)), int actor_handle __attribute__((unused)), char use_z __attribute__((unused)), float max_speed_sq __attribute__((unused)), char path_gate __attribute__((unused)), float arg4 __attribute__((unused)), float arg5 __attribute__((unused)), float arg6 __attribute__((unused)), float arg7 __attribute__((unused)), float maximum_throttle __attribute__((unused)), float *movement __attribute__((unused)), float *out_facing __attribute__((unused)), short *out_dir __attribute__((unused)), float *out_vec2 __attribute__((unused)), char *out_byte __attribute__((unused)), char *out_bool __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x5c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movb %%al, %%bl\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%ecx, %%edi\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x58(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637472\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movb 0x42a(%%esi), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl $0x3f5db3d7, -0xc(%%ebp)\n\t"
      "movl $0xffffffff, -0x8(%%ebp)\n\t"
      "je .Lactor_move_compute_facing_1\n\t"
      "movb $1, 0x591(%%esi)\n\t"
      ".Lactor_move_compute_facing_1:\n\t"
      "testw %%di, %%di\n\t"
      "jl .Lactor_move_compute_facing_11\n\t"
      "cmpw $3, %%di\n\t"
      "jg .Lactor_move_compute_facing_11\n\t"
      "movl 0x2c(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "jne .Lactor_move_compute_facing_2\n\t"
      "movl $0, -0x20(%%ebp)\n\t"
      ".Lactor_move_compute_facing_2:\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lactor_move_compute_facing_3\n\t"
      "leal 0x174(%%esi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      ".Lactor_move_compute_facing_3:\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .Lactor_move_compute_facing_8\n\t"
      "jmp *.Lactor_move_compute_facing_jt0(,%%eax,4)\n\t"
      ".Lactor_move_compute_facing_4:\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_9\n\t"
      ".Lactor_move_compute_facing_5:\n\t"
      "flds -0x28(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "fchs\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_9\n\t"
      ".Lactor_move_compute_facing_6:\n\t"
      "flds -0x24(%%ebp)\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "fchs\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_9\n\t"
      ".Lactor_move_compute_facing_7:\n\t"
      "flds -0x28(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "fchs\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_9\n\t"
      ".Lactor_move_compute_facing_8:\n\t"
      "pushl $1\n\t"
      "pushl $0x598\n\t"
      "pushl $0x255984\n\t"
      "pushl $0x255ee8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_move_compute_facing_9:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lactor_move_compute_facing_27\n\t"
      "leal -0x1c(%%ebp), %%edi\n\t"
      "leal -0x28(%%ebp), %%esi\n\t"
      ".Lactor_move_compute_facing_10:\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "leal -0x40(%%ebp), %%ebx\n\t"
      "call *%[c2bab0]\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "movl $4, -0x8(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_27\n\t"
      ".Lactor_move_compute_facing_11:\n\t"
      "movl 0x2c(%%ebp), %%edx\n\t"
      "flds 0x8(%%edx)\n\t"
      "flds 0x4(%%edx)\n\t"
      "flds (%%edx)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fcoms 0x253dc8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_move_compute_facing_12\n\t"
      "movl 0xa0(%%ecx), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      ".Lactor_move_compute_facing_12:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lactor_move_compute_facing_22\n\t"
      "fcomps 0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_move_compute_facing_23\n\t"
      "movl (%%edx), %%ecx\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "movb 0x505(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "movl 0x8(%%edx), %%ecx\n\t"
      "movl %%ecx, -0x2c(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "je .Lactor_move_compute_facing_13\n\t"
      "leal 0x524(%%esi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "cmpw $0, 0x15e(%%esi)\n\t"
      "jle .Lactor_move_compute_facing_14\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_14\n\t"
      ".Lactor_move_compute_facing_13:\n\t"
      "leal 0x174(%%esi), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      ".Lactor_move_compute_facing_14:\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_move_compute_facing_15\n\t"
      "movl $0, -0x2c(%%ebp)\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      ".Lactor_move_compute_facing_15:\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lactor_move_compute_facing_16\n\t"
      "leal 0x174(%%esi), %%edx\n\t"
      "movl (%%edx), %%ebx\n\t"
      "movl %%ebx, -0x1c(%%ebp)\n\t"
      "movl 0x4(%%edx), %%edi\n\t"
      "movl %%edi, -0x18(%%ebp)\n\t"
      "movl 0x8(%%edx), %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_17\n\t"
      ".Lactor_move_compute_facing_16:\n\t"
      "movl -0x18(%%ebp), %%edi\n\t"
      "movl -0x1c(%%ebp), %%ebx\n\t"
      ".Lactor_move_compute_facing_17:\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lactor_move_compute_facing_18\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl %%ebx, -0x34(%%ebp)\n\t"
      "movl %%edi, -0x30(%%ebp)\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      ".Lactor_move_compute_facing_18:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_move_compute_facing_21\n\t"
      "addl $0x174, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "jne .Lactor_move_compute_facing_19\n\t"
      "movl $0, -0x20(%%ebp)\n\t"
      ".Lactor_move_compute_facing_19:\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lactor_move_compute_facing_20\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl %%ebx, -0x28(%%ebp)\n\t"
      "movl %%edi, -0x24(%%ebp)\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      ".Lactor_move_compute_facing_20:\n\t"
      "leal -0x28(%%ebp), %%edi\n\t"
      "leal -0x34(%%ebp), %%esi\n\t"
      "jmp .Lactor_move_compute_facing_10\n\t"
      ".Lactor_move_compute_facing_21:\n\t"
      "leal -0x1c(%%ebp), %%edi\n\t"
      "leal -0x34(%%ebp), %%esi\n\t"
      "jmp .Lactor_move_compute_facing_10\n\t"
      ".Lactor_move_compute_facing_22:\n\t"
      "fstp %%st(0)\n\t"
      ".Lactor_move_compute_facing_23:\n\t"
      "movb 0x505(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_move_compute_facing_24\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal 0x174(%%esi), %%ecx\n\t"
      "leal 0x524(%%esi), %%edi\n\t"
      "movl %%edx, %%eax\n\t"
      "call *%[c2b830]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Lactor_move_compute_facing_27\n\t"
      ".Lactor_move_compute_facing_24:\n\t"
      "movl (%%edx), %%ecx\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl 0x8(%%edx), %%ecx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "jne .Lactor_move_compute_facing_25\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      ".Lactor_move_compute_facing_25:\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lactor_move_compute_facing_26\n\t"
      "leal 0x174(%%esi), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      ".Lactor_move_compute_facing_26:\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      ".Lactor_move_compute_facing_27:\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_move_compute_facing_28\n\t"
      "flds -0x14(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0x5fc\n\t"
      "pushl $0x255984\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255ed8\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_move_compute_facing_28:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "movb 0x14(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "fmuls 0x178(%%esi)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x17c(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x174(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "jne .Lactor_move_compute_facing_35\n\t"
      "cmpw $4, 0x6dc(%%esi)\n\t"
      "je .Lactor_move_compute_facing_35\n\t"
      "movb 0x99(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_move_compute_facing_34\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c3bc90]\n\t"
      "movl 0x164(%%esi), %%ebx\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .Lactor_move_compute_facing_34\n\t"
      "movswl -0x8(%%ebp), %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .Lactor_move_compute_facing_34\n\t"
      "jmp *.Lactor_move_compute_facing_jt1(,%%eax,4)\n\t"
      ".Lactor_move_compute_facing_29:\n\t"
      "flds 0x178(%%esi)\n\t"
      "movl 0x174(%%esi), %%eax\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_33\n\t"
      ".Lactor_move_compute_facing_30:\n\t"
      "flds 0x174(%%esi)\n\t"
      "fchs\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds 0x178(%%esi)\n\t"
      "fchs\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_33\n\t"
      ".Lactor_move_compute_facing_31:\n\t"
      "flds 0x174(%%esi)\n\t"
      "movl 0x178(%%esi), %%ecx\n\t"
      "fchs\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_33\n\t"
      ".Lactor_move_compute_facing_32:\n\t"
      "flds 0x178(%%esi)\n\t"
      "movl 0x174(%%esi), %%edx\n\t"
      "fchs\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      ".Lactor_move_compute_facing_33:\n\t"
      "flds 0x17c(%%esi)\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_move_compute_facing_34\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3ecccccd\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x12c(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "movl $0, -0x20(%%ebp)\n\t"
      "call *%[vsca]\n\t"
      "addl $0x10, %%esp\n\t"
      "leal -0x5c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $-1\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0x376(%%esi), %%dl\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c18e3c0]\n\t"
      "pushl %%eax\n\t"
      "call *%[c639e0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_move_compute_facing_34\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x255ed4\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_move_compute_facing_34\n\t"
      "movl $0x3f733333, -0xc(%%ebp)\n\t"
      ".Lactor_move_compute_facing_34:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_move_compute_facing_35\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .Lactor_move_compute_facing_36\n\t"
      ".Lactor_move_compute_facing_35:\n\t"
      "movb $1, %%bl\n\t"
      ".Lactor_move_compute_facing_36:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c3bd50]\n\t"
      "movl 0x2c(%%ebp), %%eax\n\t"
      "flds 0x8(%%eax)\n\t"
      "addl $4, %%esp\n\t"
      "flds 0x4(%%eax)\n\t"
      "flds (%%eax)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fxch %%st(1)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_move_compute_facing_37\n\t"
      "movl $1, %%eax\n\t"
      "jmp .Lactor_move_compute_facing_38\n\t"
      ".Lactor_move_compute_facing_37:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lactor_move_compute_facing_38:\n\t"
      "movl 0x40(%%ebp), %%ecx\n\t"
      "leal 0x2c(%%ebp), %%edx\n\t"
      "movb %%al, (%%ecx)\n\t"
      "pushl %%edx\n\t"
      "leal 0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c2a610]\n\t"
      "movb 0x46e(%%esi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_move_compute_facing_43\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fmuls 0x14(%%ebp)\n\t"
      "fcomps -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_move_compute_facing_43\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsqrt\n\t"
      "fstps 0x40(%%ebp)\n\t"
      "flds 0x2c(%%ebp)\n\t"
      "fadds 0x2533e8\n\t"
      "fcomps 0x40(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_move_compute_facing_39\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fcomps 0x2c(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_move_compute_facing_39\n\t"
      "flds 0x40(%%ebp)\n\t"
      "fsubs 0x2c(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fsubs 0x2c(%%ebp)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "flds 0x28(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_move_compute_facing_40\n\t"
      "fstps 0x28(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_41\n\t"
      ".Lactor_move_compute_facing_39:\n\t"
      "movl $0, 0x28(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_43\n\t"
      ".Lactor_move_compute_facing_40:\n\t"
      "fstp %%st(0)\n\t"
      ".Lactor_move_compute_facing_41:\n\t"
      "flds 0x28(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lactor_move_compute_facing_42\n\t"
      "flds 0x28(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lactor_move_compute_facing_43\n\t"
      ".Lactor_move_compute_facing_42:\n\t"
      "pushl $1\n\t"
      "pushl $0x662\n\t"
      "pushl $0x255984\n\t"
      "pushl $0x255e98\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_move_compute_facing_43:\n\t"
      "testb %%bl, %%bl\n\t"
      "movl 0x31fc38, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "je .Lactor_move_compute_facing_51\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .Lactor_move_compute_facing_49\n\t"
      "jmp *.Lactor_move_compute_facing_jt2(,%%eax,4)\n\t"
      ".Lactor_move_compute_facing_44:\n\t"
      "movl $0x3f800000, -0x28(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_50\n\t"
      ".Lactor_move_compute_facing_45:\n\t"
      "movl $0xbf800000, -0x28(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_50\n\t"
      ".Lactor_move_compute_facing_46:\n\t"
      "movl $0xbf800000, -0x24(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_50\n\t"
      ".Lactor_move_compute_facing_47:\n\t"
      "movl $0x3f800000, -0x24(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_50\n\t"
      ".Lactor_move_compute_facing_48:\n\t"
      "movl -0x40(%%ebp), %%edx\n\t"
      "movl -0x3c(%%ebp), %%eax\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_50\n\t"
      ".Lactor_move_compute_facing_49:\n\t"
      "pushl $1\n\t"
      "pushl $0x671\n\t"
      "pushl $0x255984\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_move_compute_facing_50:\n\t"
      "flds -0x28(%%ebp)\n\t"
      "movl 0x3c(%%ebp), %%edx\n\t"
      "fmuls 0x28(%%ebp)\n\t"
      "movb $0, (%%edx)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x28(%%ebp)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x28(%%ebp)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_52\n\t"
      ".Lactor_move_compute_facing_51:\n\t"
      "movl 0x3c(%%ebp), %%eax\n\t"
      "movb $1, 0x591(%%esi)\n\t"
      "movb $1, (%%eax)\n\t"
      ".Lactor_move_compute_facing_52:\n\t"
      "call *%[cfff80]\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lactor_move_compute_facing_53\n\t"
      "movb 0x5ac9d1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_move_compute_facing_53\n\t"
      "movl $0, 0x20(%%ebp)\n\t"
      "movl $0, 0x1c(%%ebp)\n\t"
      ".Lactor_move_compute_facing_53:\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_move_compute_facing_54\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_move_compute_facing_73\n\t"
      ".Lactor_move_compute_facing_54:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lactor_move_compute_facing_55\n\t"
      "movl $0, 0x2c(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_57\n\t"
      ".Lactor_move_compute_facing_55:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lactor_move_compute_facing_56\n\t"
      "movl $0x40490fdb, 0x2c(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_57\n\t"
      ".Lactor_move_compute_facing_56:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "call *%[c1d94f0]\n\t"
      "fstps 0x2c(%%ebp)\n\t"
      ".Lactor_move_compute_facing_57:\n\t"
      "flds 0x18(%%ebp)\n\t"
      "movl 0x2c(%%ebp), %%ecx\n\t"
      "fcomps 0x2533c0\n\t"
      "movl %%ecx, 0x14(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_move_compute_facing_63\n\t"
      "flds 0x18(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "fmuls 0x24(%%ebp)\n\t"
      "movl %%edx, 0x40(%%ebp)\n\t"
      "flds 0x24(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_move_compute_facing_60\n\t"
      "flds 0x24(%%ebp)\n\t"
      "fcomps 0x2533ec\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_move_compute_facing_58\n\t"
      "flds 0x2533ec\n\t"
      "jmp .Lactor_move_compute_facing_59\n\t"
      ".Lactor_move_compute_facing_58:\n\t"
      "flds 0x24(%%ebp)\n\t"
      ".Lactor_move_compute_facing_59:\n\t"
      "fmuls 0x18(%%ebp)\n\t"
      "fstps 0x40(%%ebp)\n\t"
      ".Lactor_move_compute_facing_60:\n\t"
      "flds 0x2c(%%ebp)\n\t"
      "fmuls 0x254644\n\t"
      "fsts 0x18(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_move_compute_facing_61\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x18(%%ebp)\n\t"
      ".Lactor_move_compute_facing_61:\n\t"
      "flds 0x2c(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_move_compute_facing_62\n\t"
      "fstps 0x14(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_63\n\t"
      ".Lactor_move_compute_facing_62:\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2c(%%ebp)\n\t"
      "fcomps 0x40(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_move_compute_facing_63\n\t"
      "movl 0x40(%%ebp), %%eax\n\t"
      "movl %%eax, 0x14(%%ebp)\n\t"
      ".Lactor_move_compute_facing_63:\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fcomps 0x594(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_move_compute_facing_67\n\t"
      "movb 0x591(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_move_compute_facing_66\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fcomps 0x1c(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_move_compute_facing_66\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fcomps 0x20(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_move_compute_facing_64\n\t"
      "flds 0x20(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_65\n\t"
      ".Lactor_move_compute_facing_64:\n\t"
      "flds 0x14(%%ebp)\n\t"
      ".Lactor_move_compute_facing_65:\n\t"
      "fsts 0x594(%%esi)\n\t"
      "movb 0x5aca5e, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_move_compute_facing_71\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255e74\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x18, %%esp\n\t"
      "jmp .Lactor_move_compute_facing_72\n\t"
      ".Lactor_move_compute_facing_66:\n\t"
      "movb 0x5aca5e, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_move_compute_facing_72\n\t"
      "flds 0x14(%%ebp)\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255e68\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .Lactor_move_compute_facing_72\n\t"
      ".Lactor_move_compute_facing_67:\n\t"
      "flds 0x594(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_move_compute_facing_72\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fcomps 0x1c(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "movb 0x5aca5e, %%al\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_move_compute_facing_69\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_move_compute_facing_68\n\t"
      "flds 0x594(%%esi)\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x1c(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255e3c\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x20, %%esp\n\t"
      ".Lactor_move_compute_facing_68:\n\t"
      "movl $0, 0x594(%%esi)\n\t"
      "jmp .Lactor_move_compute_facing_72\n\t"
      ".Lactor_move_compute_facing_69:\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_move_compute_facing_70\n\t"
      "flds 0x594(%%esi)\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255e1c\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x18, %%esp\n\t"
      ".Lactor_move_compute_facing_70:\n\t"
      "movl 0x594(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x14(%%ebp)\n\t"
      "jmp .Lactor_move_compute_facing_72\n\t"
      ".Lactor_move_compute_facing_71:\n\t"
      "fstp %%st(0)\n\t"
      ".Lactor_move_compute_facing_72:\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fsubs 0x2c(%%ebp)\n\t"
      "fsts 0x18(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_move_compute_facing_73\n\t"
      "flds -0x14(%%ebp)\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "fmuls 0x178(%%esi)\n\t"
      "pushl %%edx\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x17c(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x17c(%%esi)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x174(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x174(%%esi)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x178(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_move_compute_facing_73\n\t"
      "flds 0x18(%%ebp)\n\t"
      "subl $8, %%esp\n\t"
      "fcos\n\t"
      "leal -0x40(%%ebp), %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fsin\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[rots]\n\t"
      "movb 0x5aca5e, %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_move_compute_facing_73\n\t"
      "flds 0x18(%%ebp)\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x2c(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x255df8\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x20, %%esp\n\t"
      ".Lactor_move_compute_facing_73:\n\t"
      "movb 0x505(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_move_compute_facing_74\n\t"
      "cmpw $-1, 0x42e(%%esi)\n\t"
      "jne .Lactor_move_compute_facing_74\n\t"
      "testw %%di, %%di\n\t"
      "je .Lactor_move_compute_facing_74\n\t"
      "cmpw $4, %%di\n\t"
      "je .Lactor_move_compute_facing_74\n\t"
      "pushl $1\n\t"
      "pushl $0x6f1\n\t"
      "pushl $0x255984\n\t"
      "pushl $0x255da0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_move_compute_facing_74:\n\t"
      "movl 0x30(%%ebp), %%eax\n\t"
      "movl 0x34(%%ebp), %%edx\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movw %%di, (%%edx)\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl 0x38(%%ebp), %%eax\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lactor_move_compute_facing_jt0:\n\t"
      ".long .Lactor_move_compute_facing_4\n\t"
      ".long .Lactor_move_compute_facing_5\n\t"
      ".long .Lactor_move_compute_facing_6\n\t"
      ".long .Lactor_move_compute_facing_7\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lactor_move_compute_facing_jt1:\n\t"
      ".long .Lactor_move_compute_facing_29\n\t"
      ".long .Lactor_move_compute_facing_30\n\t"
      ".long .Lactor_move_compute_facing_31\n\t"
      ".long .Lactor_move_compute_facing_32\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lactor_move_compute_facing_jt2:\n\t"
      ".long .Lactor_move_compute_facing_44\n\t"
      ".long .Lactor_move_compute_facing_45\n\t"
      ".long .Lactor_move_compute_facing_46\n\t"
      ".long .Lactor_move_compute_facing_47\n\t"
      ".long .Lactor_move_compute_facing_48\n\t"
      ".text\n\t"
      :
      : [dget] "m"(b2daa0_dget), [tag] "m"(b2daa0_tag), [norm] "m"(b2daa0_norm), [assert] "m"(b2daa0_assert), [exitfn] "m"(b2daa0_exitfn), [c2bab0] "m"(b2daa0_c2bab0), [c2b830] "m"(b2daa0_c2b830), [c21fb0] "m"(b2daa0_c21fb0), [c8d9d0] "m"(b2daa0_c8d9d0), [c3bc90] "m"(b2daa0_c3bc90), [mag] "m"(b2daa0_mag), [vsca] "m"(b2daa0_vsca), [c18e3c0] "m"(b2daa0_c18e3c0), [c639e0] "m"(b2daa0_c639e0), [c3bd50] "m"(b2daa0_c3bd50), [c2a610] "m"(b2daa0_c2a610), [cfff80] "m"(b2daa0_cfff80), [c1d94f0] "m"(b2daa0_c1d94f0), [cff4d0] "m"(b2daa0_cff4d0), [rots] "m"(b2daa0_rots)
      : "memory");
}
#else
#error "actor_move_compute_facing: clang naked draft required"
#endif


/* 0x2e560 — actor_move_update: Top-level per-tick actor movement dispatcher.
 * Re-evaluates the actor's facing seed, picks the movement state from the
 * pending move-type (actor[0x15e]) and vehicle/path context, then calls
 * actor_move_compute_facing to resolve the final facing/throttle and applies
 * crouch/jump unit control.
 *
 * cdecl, sole arg actor_handle (confirmed: caller FUN_0003ec80 @ 0x3ed88,
 * prologue MOV EDI,[EBP+0x8] is the only stack arg, RET with MOV ESP,EBP).
 *
 * Confirmed: datum_get(*0x6325a4, actor_handle) at 0x2e573; tag_get('actr',
 *            actor[0x58]) at 0x2e583 -> actr_tag (uint*, control flags).
 * Confirmed: assert_valid_real_normal3d(actor+0x174) at 0x2e5d4 then seed
 *            desired_facing actor[0x5a4] = actor[0x174] at 0x2e62f.
 * Confirmed: actor[0x430] branch (0x2e64d) copies actor[0x434] vec into
 *            actor[0x518] and resets the smoothing state (0x5dc..0x5ec).
 * Confirmed: vehicle smoothing path when actor[0x15e]==4 (0x2e6bf) via
 *            FUN_0002bd80(actor+0x518 or scaled, &slerp, &weight)@<ecx>.
 * Confirmed: facing-direction resolution from actor[0x42c]/0x429/0x428/0x6a
 *            at 0x2e8b7 -> actor[0x6dc].
 * Confirmed: big move-state switch on actor[0x15e] (vehicle / >0 path) at
 *            0x2e958 and the no-vehicle branch at 0x2eb77.
 * Confirmed: actor_move_compute_facing(...) call at 0x2edbf (al=local_5,
 *            ecx=actor[0x42e]).
 * Confirmed: actor_unit_control_crouch(actor_handle, crouch) at 0x2ef32,
 *            actor_unit_control_jump at 0x2f04b/0x2f123, and the leap/anim
 *            impulse path (0x2efa4-0x2f039 and 0x2f083-0x2f166). */
void actor_move_update(int actor_handle)
{
  char *actor;
  unsigned int *actr_tag;
  float vec_scratch[3]; /* [EBP-0x44..-0x3c] */
  float slerp[3]; /* [EBP-0x38..-0x30] */
  short facing_dir; /* [EBP-0x30] (resolved facing-direction selector) */
  float arg4; /* [EBP-0x28] */
  float arg5; /* [EBP-0x24] */
  float arg6; /* [EBP-0x20] */
  float arg7; /* [EBP-0x1c] */
  float maximum_throttle; /* [EBP-0x18] */
  char use_z; /* [EBP-0x14] -> compute_facing arg1 */
  float max_speed_sq; /* [EBP-0x10] */
  float weight; /* [EBP-0x8] (FUN_0002bd80 speed out) */
  char want_facing; /* [EBP-0x1]  -> compute_facing want_facing@al */
  char need_jump; /* [EBP-0x2]  seed-fallback gate */
  char leap_jump; /* [EBP-0x3]  unit-control-jump gate */
  char clear_firing; /* [EBP-0x4]  discarded-firing-position gate */
  char path_gate; /* [EBP-0x2c] -> compute_facing arg3 */
  char crouch; /* low byte of [EBP-0x8] crouch flag (bVar14/BL) */
  char *src;
  char *vehicle;
  char *vehicle_tag;
  short pending;
  short submode;
  int handle;
  float fade;
  float keep;
  float len_sq;
  float inv_len;
  float forward[3]; /* [EBP-0x34..-0x30] cross-edge scratch */

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  actr_tag = (unsigned int *)tag_get(0x61637472, *(int *)(actor + 0x58));
  want_facing = 0;
  use_z = 0;
  path_gate = 0;
  clear_firing = 0;
  need_jump = 0;
  leap_jump = 0;
  crouch = 0;
  max_speed_sq = 0.0f;
  arg4 = 0.0f;
  arg6 = 0.0f;
  arg5 = 0.0f;
  arg7 = 0.0f;
  maximum_throttle = 1.0f;

  if (valid_real_normal3d((float *)(actor + 0x174)) == 0) {
    display_assert(csprintf((char *)0x5ab100,
                            "%s: assert_valid_real_normal3d(%f, %f, %f)",
                            (char *)0x255efc, (double)*(float *)(actor + 0x174),
                            (double)*(float *)(actor + 0x178),
                            (double)*(float *)(actor + 0x17c)),
                   "c:\\halo\\SOURCE\\ai\\actor_moving.c", 0x11e, 1);
    system_exit(-1);
  }
  *(float *)(actor + 0x5a4) = *(float *)(actor + 0x174);
  *(int *)(actor + 0x5a8) = *(int *)(actor + 0x178);
  *(int *)(actor + 0x5ac) = *(int *)(actor + 0x17c);
  *(char *)(actor + 0x591) = 0;
  *(char *)(actor + 0x58d) = 1;
  *(char *)(actor + 0x58e) = 1;

  if (*(char *)(actor + 0x430) != '\0') {
    *(int *)(actor + 0x518) = *(int *)(actor + 0x434);
    *(int *)(actor + 0x51c) = *(int *)(actor + 0x438);
    *(int *)(actor + 0x520) = *(int *)(actor + 0x43c);
    *(char *)(actor + 0x504) = 1;
    *(char *)(actor + 0x58d) = 0;
    *(int *)(actor + 0x5dc) = *(int *)*(int *)0x31fc38;
    *(int *)(actor + 0x5e0) = ((int *)*(int *)0x31fc38)[1];
    *(int *)(actor + 0x5e4) = ((int *)*(int *)0x31fc38)[2];
    *(int *)(actor + 0x5e8) = 0;
    *(int *)(actor + 0x5ec) = 0;
  } else if (*(int16_t *)(actor + 0x15e) == 4) {
    if (*(char *)(actor + 0x504) == '\0') {
      vec_scratch[0] = *(float *)(actor + 0x174) * *(float *)0x254644;
      vec_scratch[1] = *(float *)(actor + 0x178) * *(float *)0x254644;
      vec_scratch[2] = *(float *)(actor + 0x17c) * *(float *)0x254644;
      src = (char *)vec_scratch;
    } else {
      src = actor + 0x518;
    }
    FUN_0002bd80(actor_handle, (float *)src, slerp, &weight);
    fade = *(float *)0x2533e8;
    if (*(float *)(actor + 0x5e4) * *(float *)(actor + 0x5e4) +
          *(float *)(actor + 0x5e0) * *(float *)(actor + 0x5e0) +
          *(float *)(actor + 0x5dc) * *(float *)(actor + 0x5dc) <
        slerp[2] * slerp[2] + slerp[1] * slerp[1] + slerp[0] * slerp[0]) {
      fade = *(float *)0x2533e4;
    }
    keep = *(float *)0x2533c8 - fade;
    *(float *)(actor + 0x5dc) = keep * *(float *)(actor + 0x5dc);
    *(float *)(actor + 0x5e0) = keep * *(float *)(actor + 0x5e0);
    *(float *)(actor + 0x5e4) = keep * *(float *)(actor + 0x5e4);
    *(float *)(actor + 0x5dc) = slerp[0] * fade + *(float *)(actor + 0x5dc);
    *(float *)(actor + 0x5e0) = slerp[1] * fade + *(float *)(actor + 0x5e0);
    *(float *)(actor + 0x5e4) = slerp[2] * fade + *(float *)(actor + 0x5e4);
    if (*(float *)(actor + 0x5e4) * *(float *)(actor + 0x5e4) +
          *(float *)(actor + 0x5e0) * *(float *)(actor + 0x5e0) +
          *(float *)(actor + 0x5dc) * *(float *)(actor + 0x5dc) <
        *(float *)0x253f44) {
      *(int *)(actor + 0x5dc) = *(int *)*(int *)0x31fc38;
      *(int *)(actor + 0x5e0) = ((int *)*(int *)0x31fc38)[1];
      *(int *)(actor + 0x5e4) = ((int *)*(int *)0x31fc38)[2];
    }
    *(float *)(actor + 0x5ec) = weight;
    fade = fade * weight + keep * *(float *)(actor + 0x5e8);
    *(float *)(actor + 0x5e8) = fade;
    if (fade < *(float *)0x255ef8) {
      *(int *)(actor + 0x5e8) = 0;
    }
    if (*(char *)(actor + 0x504) != '\0') {
      slerp[0] = *(float *)(actor + 0x5dc);
      slerp[1] = *(float *)(actor + 0x5e0);
      slerp[2] = *(float *)(actor + 0x5e4);
      len_sq = slerp[1] * slerp[1] + slerp[2] * slerp[2] + slerp[0] * slerp[0];
      if (*(float *)0x253f44 < len_sq) {
        inv_len = *(float *)0x2533c8 / sqrtf(len_sq);
        slerp[0] = slerp[0] * inv_len;
        slerp[1] = slerp[1] * inv_len;
        slerp[2] = slerp[2] * inv_len;
        rotate_vector3d_by_sincos((float *)(actor + 0x518), slerp,
                                  x87_fsin(sqrtf(len_sq)),
                                  x87_fcos(sqrtf(len_sq)));
      }
      arg7 = *(float *)(actor + 0x5e8);
    }
  }

  pending = *(int16_t *)(actor + 0x42c);
  if (pending == -1) {
    pending = 2;
    if (*(char *)(actor + 0x429) != '\0') {
      pending = 4;
    } else if (*(char *)(actor + 0x428) != '\0') {
      pending = 3;
    } else {
      submode = *(int16_t *)(actor + 0x6a);
      if (submode == 1) {
        pending = 1;
      } else if (submode == 2) {
        pending = 0;
      } else if (submode == 3) {
        pending = 2;
      }
    }
  }
  *(int16_t *)(actor + 0x6dc) = pending;
  facing_dir = *(int16_t *)(actor + 0x42e);

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  if (*(char *)(actor + 0x4a8) == '\0' ||
      *(float *)(actor + 0x4a0) < (float)actr_tag[0x25]) {
    crouch = *(char *)(actor + 0x426);
  } else {
    crouch = *(char *)(actor + 0x427);
  }

  if (*(int16_t *)(actor + 0x15e) < 1) {
    if (*(char *)(actor + 0x160) == '\0') {
      if (*(int16_t *)(actor + 0x418) == -1) {
        pending = *(int16_t *)(actor + 0x6dc);
        if (pending == 1) {
          crouch = 0;
          *(char *)(actor + 0x504) = 0;
          *(char *)(actor + 0x58d) = 0;
          *(char *)(actor + 0x58e) = 0;
          need_jump = 1;
        } else if (*(char *)(actor + 0x15c) == '\0' ||
                   *(char *)(actor + 0x99) != '\0') {
          if (*(char *)(actor + 0x6a0) == '\0') {
            if (*(int16_t *)(actor + 0x360) < 1) {
              clear_firing = 1;
              if (pending != 2 || (crouch == 0 ? (*actr_tag & 0x4000) != 0 :
                                                 (char)(*actr_tag >> 8) < 0)) {
                *(char *)(actor + 0x505) = 0;
              }
              if (pending == 4) {
                need_jump = 1;
              }
              if ((*actr_tag & 0x200000) != 0) {
                max_speed_sq = (float)actr_tag[0x26] * (float)actr_tag[0x26];
                use_z = 1;
                want_facing = 1;
                if (*(char *)(actor + 0x505) != '\0') {
                  max_speed_sq = max_speed_sq * *(float *)0x2533d8;
                }
              }
            } else {
              *(char *)(actor + 0x504) = 0;
              *(char *)(actor + 0x58d) = 1;
              crouch = (char)(*actr_tag >> 0x1e) & 1;
            }
          } else {
            *(char *)(actor + 0x504) = 0;
            FUN_00012140((float *)(actor + 0x12c), (float *)(actor + 0x6a8),
                         vec_scratch);
            crouch = 0;
            if (normalize3d(vec_scratch) == *(float *)0x2533c0) {
              *(char *)(actor + 0x58d) = 1;
            } else {
              *(float *)(actor + 0x5a4) = vec_scratch[0];
              *(float *)(actor + 0x5a8) = vec_scratch[1];
              *(float *)(actor + 0x5ac) = vec_scratch[2];
              *(char *)(actor + 0x58d) = 0;
              *(char *)(actor + 0x58e) = 0;
              *(char *)(actor + 0x591) = 1;
            }
          }
        } else {
          crouch = 0;
          *(char *)(actor + 0x504) = 0;
          *(char *)(actor + 0x58d) = 1;
        }
      } else {
        crouch = 0;
        *(char *)(actor + 0x504) = 0;
        *(char *)(actor + 0x58d) = 0;
        *(char *)(actor + 0x58e) = 0;
      }
    } else {
      *(char *)(actor + 0x504) = 0;
      *(int16_t *)(actor + 0x50a) = 0;
      if (*(int16_t *)(actor + 4) == 0xf || *(char *)(actor + 0x161) != '\0') {
        *(char *)(actor + 0x58d) = 1;
      } else {
        *(char *)(actor + 0x58d) = 0;
      }
      crouch = 0;
      *(char *)(actor + 0x58e) = 0;
    }
  } else {
    vehicle = (char *)object_get_and_verify_type(*(int *)(actor + 0x158), 2);
    vehicle_tag = (char *)tag_get(0x76656869, *(int *)vehicle);
    arg4 = *(float *)(vehicle_tag + 0x3a0);
    if (*(float *)0x2533c0 < *(float *)(vehicle_tag + 0x3a4)) {
      maximum_throttle = *(float *)(vehicle_tag + 0x3a4);
    }
    arg5 = *(float *)(vehicle_tag + 0x398);
    arg6 = *(float *)(vehicle_tag + 0x39c);
    pending = *(int16_t *)(actor + 0x15e);
    if (pending == 2) {
      if (*(char *)(vehicle + 0x428) == '\0') {
        if (*(float *)(vehicle + 0x444) < *(float *)0x2533c4 &&
            (leap_jump = 1, *(float *)(vehicle + 0x38) < *(float *)0x2533f0)) {
          vec_scratch[0] = *(float *)(vehicle + 0x30);
          vec_scratch[1] = *(float *)(vehicle + 0x34);
          vec_scratch[2] = 0.0f;
          if (*(float *)0x2533c0 < magnitude3d(vec_scratch)) {
            *(char *)(actor + 0x504) = 1;
            crouch = 0;
            *(float *)(actor + 0x518) = vec_scratch[0] * *(float *)0x254644;
            *(float *)(actor + 0x51c) = vec_scratch[1] * *(float *)0x254644;
            *(float *)(actor + 0x520) = vec_scratch[2] * *(float *)0x254644;
          } else {
            crouch = 0;
            *(char *)(actor + 0x504) = 0;
          }
        } else {
          goto length_seed;
        }
      } else {
        crouch = 0;
        leap_jump = 1;
        *(char *)(actor + 0x504) = 0;
        *(char *)(actor + 0x58d) = 1;
      }
    } else if (pending == 3) {
    length_seed:
      crouch = 0;
      max_speed_sq =
        *(float *)(vehicle_tag + 0x380) * *(float *)(vehicle_tag + 0x380);
      want_facing = 1;
    } else if (pending == 4) {
      if (vehicle_stuck(*(int *)(actor + 0x158), vec_scratch) == '\0') {
        crouch = 0;
        facing_dir = 0;
        path_gate = 1;
        use_z = 1;
      } else {
        *(char *)(actor + 0x504) = 0;
        *(char *)(actor + 0x58d) = 0;
        *(char *)(actor + 0x58e) = 0;
        *(float *)(actor + 0x5a4) = -vec_scratch[0];
        crouch = 0;
        *(float *)(actor + 0x5a8) = -vec_scratch[1];
        *(float *)(actor + 0x5ac) = -vec_scratch[2];
      }
    } else {
      *(char *)(actor + 0x504) = 0;
      *(int16_t *)(actor + 0x50a) = 0;
      if (*(int16_t *)(actor + 4) == 0xf || *(char *)(actor + 0x161) != '\0') {
        *(char *)(actor + 0x58d) = 1;
      } else {
        *(char *)(actor + 0x58d) = 0;
      }
      crouch = 0;
    }
  }

  if (*(char *)(actor + 0x504) == '\0') {
    goto seed_fallback;
  } else {
    if (*(char *)(actor + 0x506) == '\0') {
      actor_move_compute_facing(
        want_facing, facing_dir, actor_handle, use_z, max_speed_sq, path_gate,
        arg4, arg5, arg6, arg7, maximum_throttle, (float *)(actor + 0x518),
        (float *)(actor + 0x5a4), (short *)(actor + 0x50a),
        (float *)(actor + 0x6e0), (char *)(actor + 0x507),
        (char *)(actor + 0x506));
      if (*(char *)(actor + 0x506) != '\0') {
        *(char *)(actor + 0x504) = 0;
      }
    }
    if (*(char *)(actor + 0x504) == '\0') {
      goto seed_fallback;
    }
    *(char *)(actor + 0x58e) = 0;
    goto clear_active;
  }

seed_fallback:
  if (need_jump != '\0') {
    *(int *)(actor + 0x5a4) = *(int *)(actor + 0x174);
    *(int *)(actor + 0x5a8) = *(int *)(actor + 0x178);
    *(int *)(actor + 0x5ac) = *(int *)(actor + 0x17c);
    *(char *)(actor + 0x58e) = 0;
    goto clear_pending;
  }
  if (*(char *)(actor + 0x590) != '\0') {
    *(int *)(actor + 0x5a4) = *(int *)(actor + 0x598);
    *(int *)(actor + 0x5a8) = *(int *)(actor + 0x59c);
    *(int *)(actor + 0x5ac) = *(int *)(actor + 0x5a0);
    *(char *)(actor + 0x58e) = 1;
  clear_pending:
    *(int16_t *)(actor + 0x50a) = 0;
  clear_active:
    *(char *)(actor + 0x58d) = 0;
  }

  if (valid_real_normal3d((float *)(actor + 0x5a4)) == 0) {
    display_assert(csprintf((char *)0x5ab100,
                            "%s: assert_valid_real_normal3d(%f, %f, %f)",
                            "&actor->control.desired_facing_vector",
                            (double)*(float *)(actor + 0x5a4),
                            (double)*(float *)(actor + 0x5a8),
                            (double)*(float *)(actor + 0x5ac)),
                   "c:\\halo\\SOURCE\\ai\\actor_moving.c", 0x28f, 1);
    system_exit(-1);
  }
  if (clear_firing != '\0' && *(char *)(actor + 0x504) == '\0') {
    actor_clear_discarded_firing_positions(actor_handle, 1);
  }
  if (*(char *)(actor + 0x504) != '\0' && (*actr_tag & 0x10000000) != 0) {
    crouch = 0;
  }
  if (game_connection() == 0 && *(char *)0x5ac9ce != '\0') {
    crouch = 1;
  }
  *(char *)(actor + 0x58f) = 0;
  if (crouch != 0 && (*actr_tag & 0x20000000) != 0) {
    *(char *)(actor + 0x58f) = 1;
  }
  *(char *)(actor + 0x508) = crouch;
  actor_unit_control_crouch(actor_handle, crouch);

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  if (*(int16_t *)(actor + 0x418) == -1 &&
      (*(int *)(actor + 0x18) == -1 ||
       unit_is_busy(*(int *)(actor + 0x18)) == 0) &&
      *(int *)(actor + 0x158) == -1 && *(char *)(actor + 0x15c) == '\0' &&
      *(char *)(actor + 0x378) != '\0' && *(char *)(actor + 0x379) == '\0') {
    forward[0] = *(float *)(actor + 0x174);
    forward[1] = *(float *)(actor + 0x178);
    handle = -1;
    if (*(int *)(actor + 0x270) != -1) {
      src = (char *)datum_get(*(data_t **)0x5ab23c, *(int *)(actor + 0x270));
      forward[0] = *(float *)(src + 0xe0);
      forward[1] = *(float *)(src + 0xe4);
      handle = *(int *)(src + 0x18);
      if (magnitude3d(forward) == *(float *)0x2533c0) {
        forward[0] = *(float *)(actor + 0x174);
        forward[1] = *(float *)(actor + 0x178);
      }
    }
    actor_move_animation_impulse(actor_handle, 0, (int *)forward);
    FUN_00046f10(0x2a, *(int *)(actor + 0x18), handle, 3, -1, -1, 0);
    *(char *)(actor + 0x379) = 1;
  }

  if (leap_jump != '\0') {
    actor_unit_control_jump(actor_handle);
    goto store_prev;
  }
  if (*(char *)(actor + 0x15c) != '\0' || *(int *)(actor + 0x158) != -1) {
    *(char *)(actor + 0x530) = 0;
    goto store_prev;
  }
  if (FUN_0002a360(actor_handle) != '\0' || *(char *)(actor + 0x440) == '\0') {
    goto store_prev;
  }
  if (*(char *)(actor + 0x441) == '\0') {
    actor_unit_control_jump(actor_handle);
  } else {
    if (*(char *)(actor + 0x442) == '\0') {
      forward[0] = *(float *)(actor + 0x174);
      forward[1] = *(float *)(actor + 0x178);
      if (magnitude3d(forward) == *(float *)0x2533c0) {
        forward[0] = *(float *)*(int *)0x31fc0c;
        forward[1] = ((float *)*(int *)0x31fc0c)[1];
      }
    } else {
      forward[0] = *(float *)(actor + 0x444);
      forward[1] = *(float *)(actor + 0x448);
    }
    if (unit_leap_begin(*(int *)(actor + 0x18), forward) == '\0') {
      actor_unit_control_jump(actor_handle);
    } else {
      FUN_00046f10(0x2f, *(int *)(actor + 0x18), -1, -1, -1, -1, 0);
    }
  }
  if (*(char *)(actor + 0x442) != '\0') {
    *(int *)(actor + 0x534) = *(int *)(actor + 0x444);
    *(char *)(actor + 0x530) = 1;
    *(int *)(actor + 0x538) = *(int *)(actor + 0x448);
    *(int *)(actor + 0x53c) = *(int *)(actor + 0x44c);
    *(int *)(actor + 0x540) = *(int *)(actor + 0x450);
  }

store_prev:
  *(int *)(actor + 0x6ec) = *(int *)(actor + 0x418);
  *(int *)(actor + 0x6f0) = *(int *)(actor + 0x41c);
  *(int *)(actor + 0x6f4) = *(int *)(actor + 0x420);
}

