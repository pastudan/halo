#include "x87_math.h"

/* Clear bit 1 of projectile flags at offset 0x1dc. */
void projectile_kill_tracer(int projectile_handle)
{
  char *proj = (char *)object_get_and_verify_type(projectile_handle, 0x20);
  *(uint32_t *)(proj + 0x1dc) &= ~2u;
}

/* Delete all live projectile objects (type_mask 0x20).
 * Walks every projectile in the object table via object_iterator_new/next
 * and calls object_delete on each handle. Used during level teardown or
 * game reset to purge all in-flight projectiles. */
void projectiles_delete_all(void)
{
  object_iter_t iter;

  object_iterator_new(&iter, 0x20, 0);
  while (object_iterator_next(&iter) != NULL) {
    object_delete(iter.last_handle);
  }
}

/* Set the projectile's target handle at offset 0x1e8. */
void projectile_set_target_object_index(int projectile_handle, int target)
{
  char *proj = (char *)object_get_and_verify_type(projectile_handle, 0x20);
  *(int *)(proj + 0x1e8) = target;
}

/* Set bit 1 of projectile flags at offset 0x1dc. */
void projectile_make_tracer(int projectile_handle)
{
  char *proj = (char *)object_get_and_verify_type(projectile_handle, 0x20);
  *(uint32_t *)(proj + 0x1dc) |= 2u;
}

/* Compute the negated gravity contribution for a projectile.
 * Multiplies the per-tick gravity constant (DAT_0032512c) by the float
 * stored at projectile_tag+0x1cc (a physics/velocity field in the proj tag),
 * then negates the result.  The sign flip converts a positive tag-stored value
 * into the downward (negative) acceleration component used by the projectile
 * physics integrator.  Leaf function, no callees. */
float projectile_get_ballistic_acceleration(int projectile_tag)
{
  return -(*(float *)0x32512c * *(float *)(projectile_tag + 0x1cc));
}

/* Compute a normalized value for a projectile tag field at offset 0x1e4.
 * If the tag field (e.g. a max-distance or scale parameter) is greater than
 * the global zero reference at 0x2533c0 (0.0f), returns value / field.
 * Otherwise returns the zero reference unchanged.
 * Used by the caller to normalize a float quantity against the tag's field,
 * guarding against division by zero or a zero/unset field. */
float projectile_estimate_time_to_target(void *proj_tag, float value)
{
  float field;
  field = *(float *)((char *)proj_tag + 0x1e4);
  if (field > *(float *)0x2533c0)
    return value / field;
  return *(float *)0x2533c0;
}

/* Return true if any projectile object (type 0x20) exists in the world.
 * Loads the projectile's tag definition as a side effect (cache priming). */
bool dangerous_projectiles_near_player(void)
{
  char iter[16];
  void *projectile;

  object_iterator_new(iter, 0x20, 0);
  projectile = object_iterator_next(iter);
  if (projectile != NULL) {
    tag_get(0x70726f6a, *(int *)projectile);
    return true;
  }
  return false;
}

/* Clear the projectile's target handle if it matches the given value. */
void projectile_handle_deleted_object(int projectile_handle, int target)
{
  char *proj = (char *)object_get_and_verify_type(projectile_handle, 0x20);
  if (*(int *)(proj + 0x1e8) == target)
    *(int *)(proj + 0x1e8) = -1;
}

/* Escalate the projectile's detonation state (offset 0x1e0) to at least
 * the given state value.  Only updates the field if state is strictly
 * greater than the current value, so the state can only increase
 * (0=none, 1=pending, 2=immediate). Called by FUN_000f9c40 with state=2
 * to force an immediate detonation. */
void FUN_000f7e40(int projectile_handle, int16_t state)
{
  char *proj = (char *)object_get_and_verify_type(projectile_handle, 0x20);
  if (state > *(int16_t *)(proj + 0x1e0))
    *(int16_t *)(proj + 0x1e0) = state;
}

/* FUN_000f7e60 (0xf7e60) — XBE naked draft (batch 66). */
#if defined(__clang__)
static int (*const bf7e60_c9ee40)(int effect_tag_index, int object_index, int attached_object, uint16_t marker_index, short marker_count, void *effect_definition, float *marker_points, float *marker_forwards, float scale_a, float scale_b, float unknown1, float unknown2) = effect_new_attached_from_markers;
static int (*const bf7e60_c9f0e0)(int effect_tag_index, int object_index, float *translational_velocity, short marker_count, void *effect_definition, float *marker_points, float *marker_forwards, float scale_a, float scale_b, float unknown1, float unknown2, float unknown3) = effect_new_unattached_from_markers;

__attribute__((naked, noinline))
void FUN_000f7e60(int effect_tag_index __attribute__((unused)), int object_index __attribute__((unused)), void *tag_def __attribute__((unused)), float *marker_points __attribute__((unused)), float *marker_forwards __attribute__((unused)), float scale_a __attribute__((unused)), float scale_b __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "cmpw $3, (%%eax)\n\t"
      "jne .LFUN_000f7e60_1\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x38(%%eax), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x3e(%%eax), %%cx\n\t"
      "pushl $0x31f3a0\n\t"
      "pushl $5\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c9ee40]\n\t"
      "addl $0x30, %%esp\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f7e60_1:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x31f3a0\n\t"
      "pushl $5\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c9f0e0]\n\t"
      "addl $0x30, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c9ee40] "m"(bf7e60_c9ee40), [c9f0e0] "m"(bf7e60_c9f0e0)
      : "memory");
}
#else
#error "FUN_000f7e60: clang naked draft required"
#endif


/* For each of the 4 scale slots in a projectile's tag definition, compute the
 * current scale value based on the selector enum at tag[0x184 + i*2]:
 *   0 = skip (leave projectile float unchanged)
 *   1 = age fraction: projectile[0x200] / tag[0x1c8]; 0.0 if tag[0x1c8]==0.0
 *   2 = raw float from projectile[0x1f0]
 *   3 = armed flag: 1.0 if projectile[0x1dc] & 0x2, else 0.0
 * Writes the result to projectile[0xd4 + i*4] (four consecutive float slots).
 * Asserts (halts) on any selector value outside 0..3. */
void projectile_export_function_values(int projectile_handle)
{
  char *proj;
  char *tag;
  int16_t *sel_ptr;
  float *out_ptr;
  float local_8;
  int16_t sel;
  int counter;

  proj = (char *)object_get_and_verify_type(projectile_handle, 0x20);
  tag = (char *)tag_get(0x70726f6a, *(int *)proj);

  sel_ptr = (int16_t *)(tag + 0x184);
  out_ptr = (float *)(proj + 0xd4);
  counter = 4;

  do {
    sel = *sel_ptr;
    if (sel != 0) {
      if (sel == 1) {
        if (*(float *)(tag + 0x1c8) == 0.0f) {
          local_8 = 0.0f;
        } else {
          local_8 = *(float *)(proj + 0x200) / *(float *)(tag + 0x1c8);
        }
      } else if (sel == 2) {
        local_8 = *(float *)(proj + 0x1f0);
      } else if (sel == 3) {
        if (*(uint8_t *)(proj + 0x1dc) & 0x2) {
          local_8 = 1.0f;
        } else {
          local_8 = 0.0f;
        }
      } else {
        display_assert(0, "c:\\halo\\SOURCE\\items\\projectiles.c", 0x622, 1);
        system_exit(-1);
        local_8 = 0.0f;
      }
      *out_ptr = local_8;
    }
    sel_ptr++;
    out_ptr++;
    counter--;
  } while (counter != 0);
}

/* FUN_000f7fa0 (0xf7fa0) — XBE naked draft (batch 69). */
#if defined(__clang__)


__attribute__((naked, noinline))
float FUN_000f7fa0(void *tag __attribute__((unused)), float range_begin __attribute__((unused)), float range_end __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fsubs 0x8(%%ebp)\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "flds 0x2533c0\n\t"
      "flds 0x1e4(%%ecx)\n\t"
      "fcomps 0x1e8(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000f7fa0_1\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000f7fa0_1\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x1e4(%%ecx)\n\t"
      "flds 0x1e8(%%ecx)\n\t"
      "fld %%st(1)\n\t"
      "fmulp %%st(2)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      ".byte 0xde, 0xea\n\t" /* fsubp %st(2) — gas emits fsubrp for one-op form */
      "flds 0xc(%%ebp)\n\t"
      ".byte 0xdc, 0xc0\n\t" /* fadd %st(0), %st(0) (DC C0; gas prefers D8 C0) */
      ".byte 0xde, 0xfa\n\t" /* fdivp %st(2) */
      "fstp %%st(0)\n\t"
      ".LFUN_000f7fa0_1:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_000f7fa0: clang naked draft required"
#endif


/* Arm a projectile and detach it from its parent object.
 * Asserts that the projectile has a valid parent (parent_object_index != NONE
 * at offset 0xcc).  Sets both the "age scale" float at 0x1f0 and the
 * "fade scale" float at 0x1f8 to 1.0, clears bit 3 (0x8) of the flags word
 * at 0x1dc (the "attached-to-parent" flag), then calls
 * object_detach_from_parent to unlink the projectile from the weapon/unit that
 * fired it. Returns 1 (bool true) unconditionally on success. Source line
 * reference: c:\halo\SOURCE\items\projectiles.c line 1845. */
char projectile_handle_parent_destroyed(int projectile_handle)
{
  char *proj;

  proj = (char *)object_get_and_verify_type(projectile_handle, 0x20);
  if (*(int *)(proj + 0xcc) == -1) {
    display_assert("projectile->object.parent_object_index != NONE",
                   "c:\\halo\\SOURCE\\items\\projectiles.c", 0x735, 1);
    system_exit(-1);
  }
  *(float *)(proj + 0x1f8) = 1.0f;
  *(float *)(proj + 0x1f0) = 1.0f;
  *(uint32_t *)(proj + 0x1dc) &= ~0x8u;
  object_detach_from_parent(projectile_handle);
  return 1;
}

/* Scatter a direction vector using the global random seed.
 * Retrieves the engine-wide random seed via get_global_random_seed_address,
 * then delegates to random_direction3d to produce a randomised unit vector
 * within 'angle' radians of 'forward'.  'zero' is always passed as 0.0
 * at call sites (minimum cone half-angle).  The resulting direction is
 * written to 'result'.  This is the global-seed variant; callers that own a
 * local seed call random_direction3d directly. */
void random_vector_in_cone3d(float *forward, float zero, float angle,
                             float *result)
{
  int *seed = get_global_random_seed_address();
  random_direction3d(seed, forward, zero, angle, result);
}

/*
 * Ballistic arc trajectory solver.
 *
 * Computes the initial aim direction for a projectile that must follow a
 * parabolic arc from origin to target under gravity.  The caller supplies an
 * initial speed budget (speed), the effective per-tick gravity scale (gravity),
 * 3D origin and target vectors, and optional constraints / override values.
 * On success the function fills aim_vector with the normalised launch direction
 * and populates up to five optional output scalars; it returns 1 when a
 * non-trivial arc solution was found and 0 when the fallback minimum-range
 * trajectory is used instead.
 *
 * Algorithm overview
 * ------------------
 * 1. Compute the displacement delta = target - origin.
 * 2. Derive the effective gravity coefficient
 *      a_coeff = max(0, per_tick_const * gravity)
 *    and the quadratic coefficient a = a_coeff^2 * 0.25.
 * 3. Compute the discriminant base (4*a*c, where c = |delta|^2) and verify
 *    that a solution exists (assert 4ac > 0).
 * 4. The maximum time-of-flight for which the quadratic has real solutions is
 *      t_sq_max = sqrt(4*a*c) / (2*a)
 *    (asserted >= 0).  t_max = sqrt(t_sq_max).
 * 5. The minimum time-of-flight (t_min) is:
 *      t_min = sqrt(a_coeff * dz - disc_base)  if that is >= 0, else 0.
 * 6. Choose launch speed V:
 *    - If param_7 != NULL: V = *param_7.
 *    - Else start with V = speed; if param_6 != NULL and *param_6 > 0 then
 *      reduce V to match the desired time (capped at the caller's max speed).
 * 7. If a valid arc solution exists (t_min <= V), solve the quadratic for the
 *    time parameter t_disc and replace V when the result is valid.
 * 8. Build the initial velocity vector (vx,vy,vz) from the chosen t/V values,
 *    normalise it, and write the unit direction to aim_vector.
 * 9. Fill optional outputs: param_10 = time, param_11 = t_param,
 *    param_12 = t_param*time, param_13 = vertical velocity, param_14 =
 *    horizontal speed magnitude.
 *
 * Source ref: c:\halo\SOURCE\items\projectiles.c lines 0x2ee-0x36f.
 */
char projectile_aim_ballistic(float speed, float gravity, float *origin,
                              float *target, int param_5, float *param_6,
                              float *param_7, char param_8, float *aim_vector,
                              float *param_10, float *param_11, float *param_12,
                              float *param_13, float *param_14)
{
  /* Local variables mirror the original MSVC stack frame layout.
   * Frame size: SUB ESP,0x34 (= 52 bytes = 13 float slots + 1 char).
   *
   * Locals at EBP-N (Ghidra names):
   *   EBP-0x34 = aim_vec[0]   (float buffer for normalize3d)
   *   EBP-0x30 = aim_vec[1]
   *   EBP-0x2c = aim_vec[2]   (also holds aim_z)
   *   EBP-0x28 = dx
   *   EBP-0x24 = dy
   *   EBP-0x20 = dz
   *   EBP-0x1c = t_max
   *   EBP-0x18 = two_a
   *   EBP-0x14 = dist_sq
   *   EBP-0x10 = disc_base (-sqrt(4ac)), then t_min
   *   EBP-0x0c = c4 = 4*a*c
   *   EBP-0x08 = b = a_coeff*dz
   *   EBP-0x01 = result (char)
   *
   * Parameter slots reused as float temps by the original MSVC code:
   *   EBP+0x08 (speed)   -> t_sol
   *   EBP+0x0c (gravity) -> a (quadratic coefficient a = a_coeff^2*0.25)
   *   EBP+0x10 (origin)  -> a_coeff, then t_sol*V_out product
   *   EBP+0x14 (target)  -> V (chosen speed), then V_out
   *
   * Source ref: c:\halo\SOURCE\items\projectiles.c lines 0x2ee-0x36f.
   */
  /* Declare as contiguous array so normalize3d reads all three components.
   * MSVC placed local_38/34/30 adjacent (EBP-0x34/-0x30/-0x2c); clang may
   * insert a gap (local_14 lands between Y and Z), causing normalize3d to
   * read the wrong Z and leave it unnormalized → assert_valid_real_normal3d. */
  float aim_xyz[3]; /* [0]=local_38 (X), [1]=local_34 (Y), [2]=local_30 (Z) */
#define local_38 aim_xyz[0]
#define local_34 aim_xyz[1]
#define local_30 aim_xyz[2]
  float local_2c; /* dx */
  float local_28; /* dy */
  float local_24; /* dz */
  float local_20; /* t_max */
  float local_1c; /* two_a = 2*a */
  float local_18; /* dist_sq */
  float local_14; /* disc_base = -sqrt(4*a*c), then t_min */
  float local_10; /* c4 = 4*a*c */
  float local_c; /* b = a_coeff*dz */
  char local_5; /* result flag: 1=arc, 0=fallback */
  float a; /* quadratic coeff a = a_coeff^2 * 0.25 */
  float a_coeff; /* effective gravity: max(0, per_tick*gravity) */
  float V; /* chosen launch speed, then V_out at output stage */
  float fVar1; /* scratch */
  float fVar2; /* scratch */
  float partial; /* dy^2 + dx^2 partial sum for interleaved dist_sq */

  /* 1. Displacement = target - origin.
   * local_5 is set to 1 here to match the original's instruction order:
   * FSUB,FSTP(dx),MOVB(1),FSUB,FSTP(dy),FSUB,FSTP(dz). */
  local_2c = target[0] - origin[0];
  local_5 = 1;
  local_28 = target[1] - origin[1];
  local_24 = target[2] - origin[2];

  /* 2. Partial distance sum (dy^2 + dx^2) computed first.
   * The original interleaves this with the gravity computation:
   * partial stays on the FPU stack as st1 while a_coeff/a are computed,
   * then dz^2 is added to partial to complete dist_sq. */
  partial = local_28 * local_28 + local_2c * local_2c;

  /* 3. Effective gravity coefficient, clamped to zero. */
  a_coeff = *(float *)0x32512c * gravity;
  if (a_coeff < *(float *)0x2533c0) {
    a_coeff = 0.0f;
  }

  /* 4. Quadratic coefficient a = a_coeff^2 * 0.25.
   * Two-step to force a_coeff*a_coeff before *0.25 (matches MSVC operand
   * order). */
  fVar1 = a_coeff * a_coeff;
  a = fVar1 * *(float *)0x25337c;

  /* 5. Complete dist_sq by adding dz^2 to partial sum. */
  local_18 = local_24 * local_24 + partial;

  /* 6. c4 = dist_sq * a * 4.0; assert > 0.
   * Two-step to force dist_sq*a before *4.0 (matches MSVC operand order). */
  fVar1 = local_18 * a;
  local_10 = fVar1 * *(float *)0x2533d8;
  if (local_10 <= *(float *)0x2533c0) {
    display_assert("4.0f * a * c > 0.0f",
                   "c:\\halo\\SOURCE\\items\\projectiles.c", 0x2f8, 1);
    system_exit(-1);
  }

  /* 7. disc_base = -sqrt(c4); two_a = 2*a. */
  local_14 = -sqrtf(local_10);
  local_1c = a + a;

  /* t_sq_max = -disc_base / two_a; assert >= 0. */
  V = -local_14 / local_1c;
  if (V < *(float *)0x2533c0) {
    display_assert("t_squared_max >= 0.0f",
                   "c:\\halo\\SOURCE\\items\\projectiles.c", 0x2fc, 1);
    system_exit(-1);
  }
  local_20 = sqrtf(V); /* t_max */

  /* 8. b = a_coeff * dz; t_min = sqrt(b - disc_base) if >= 0, else 0.
   * Branch polarity: original falls through to the zero path, jumps to sqrt. */
  local_c = a_coeff * local_24;
  if (local_c - local_14 < *(float *)0x2533c0) {
    local_14 = 0.0f;
  } else {
    local_14 = sqrtf(local_c - local_14);
  }

  /* 9. Choose launch speed V. */
  if (param_7 != NULL) {
    V = *param_7;
  } else {
    V = speed;
    if ((param_6 != NULL) && (*param_6 > *(float *)0x2533c0)) {
      fVar2 = local_20 * *param_6;
      fVar2 = fVar2 * fVar2;
      fVar1 = local_c - -(fVar2 * a + local_18 / fVar2);
      if (fVar1 <= *(float *)0x2533c0) {
        display_assert("v_desired_sq > 0.0f",
                       "c:\\halo\\SOURCE\\items\\projectiles.c", 0x326, 1);
        system_exit(-1);
      }
      fVar1 = sqrtf(fVar1);
      if (speed > fVar1) {
        V = fVar1;
      }
    }
  }

  /* 10. If V >= t_min, try to find an arc solution. */
  if (V >= local_14) {
    fVar1 = local_c - V * V;
    fVar2 = fVar1 * fVar1 - local_10;
    if ((fVar1 < *(float *)0x2533c0) && (fVar2 >= *(float *)0x2533c0)) {
      speed =
        (sqrtf(fVar2) * (float)(int)((unsigned int)(param_8 != '\0') * 2 + -1) -
         fVar1) /
        local_1c;
      if (*(float *)0x2533c0 < speed) {
        speed = sqrtf(speed);
        goto LAB_output;
      }
    }
  }
  local_5 = 0;
  speed = local_20; /* t_sol = t_max */
  V = local_14; /* V_out = t_min */

LAB_output:
  /* 11. Build velocity direction (dx/t, dy/t, a_coeff*t*0.5 + dz/t). */
  fVar1 = *(float *)0x2533c8 / speed;
  local_38 = local_2c * fVar1;
  local_34 = local_28 * fVar1;
  local_30 = fVar1 * local_24 + speed * a_coeff * *(float *)0x253398;

  /* Precompute sqrt(aim_y^2 + aim_x^2) for param_14 output, stored early. */
  fVar2 = local_34 * local_34 + local_38 * local_38;
  fVar2 = sqrtf(fVar2);

  /* Store aim_z before normalize overwrites local_30. */
  fVar1 = local_30;

  /* Compute t_sol*V_out product into a_coeff slot (mirrors MSVC FSTP EBP+0x10).
   */
  a_coeff = speed * V;

  if (normalize3d(aim_xyz) == *(float *)0x2533c0) {
    /* Degenerate: fall back to displacement direction. */
    local_38 = local_2c;
    local_5 = 0;
    local_34 = local_28;
    local_30 = local_24;
    if (normalize3d(aim_xyz) == *(float *)0x2533c0) {
      /* Degenerate displacement: use global up vector. */
      local_30 = *(float *)(*(int *)0x31fc44 + 8);
      local_38 = *(float *)(*(int *)0x31fc44);
      local_34 = *(float *)(*(int *)0x31fc44 + 4);
    }
  }

  if (aim_vector == NULL) {
    display_assert("result_aim_vector",
                   "c:\\halo\\SOURCE\\items\\projectiles.c", 0x363, 1);
    system_exit(-1);
  }

  aim_vector[0] = local_38;
  aim_vector[1] = local_34;
  aim_vector[2] = local_30;

  if (param_12 != NULL) {
    *param_12 = a_coeff; /* t_sol * V_out */
  }
  if (param_10 != NULL) {
    *param_10 = V; /* V_out */
  }
  if (param_13 != NULL) {
    *param_13 = fVar1; /* aim_z before normalize */
  }
  if (param_14 != NULL) {
    *param_14 = fVar2; /* sqrt(aim_y^2 + aim_x^2) */
  }
  if (param_11 != NULL) {
    *param_11 = speed; /* t_sol */
  }
  return local_5;
#undef local_38
#undef local_34
#undef local_30
}

/* Compute the straight-line aim vector and travel parameters for a projectile
 * with no ballistic arc (no gravity).
 * Subtracts origin from target to form the direction delta, normalises it in
 * place (normalize3d overwrites the local vector with the unit vector and
 * returns the original length as the distance), then writes outputs:
 *   aim_vector  - normalised direction from origin to target (required,
 * asserted non-NULL) out_dist    - optional: raw length of the origin→target
 * vector out_speed   - optional: copy of the input speed out_t       -
 * optional: travel time = dist / speed; 0.0 if speed <= 0.0 Returns 1 (bool
 * true) unconditionally. Source ref: c:\halo\SOURCE\items\projectiles.c line
 * 0x399 (921). */
int projectile_aim_linear(float speed, float *origin, float *target,
                          float *aim_vector, float *out_speed, float *out_t,
                          float *out_dist)
{
  float local_vec[3];
  float dist;
  float t;

  local_vec[0] = target[0] - origin[0];
  local_vec[1] = target[1] - origin[1];
  local_vec[2] = target[2] - origin[2];

  dist = normalize3d(local_vec);

  if (speed <= *(float *)0x2533c0) {
    t = 0.0f;
  } else {
    t = dist / speed;
  }

  if (aim_vector == NULL) {
    display_assert("result_aim_vector",
                   "c:\\halo\\SOURCE\\items\\projectiles.c", 0x399, 1);
    system_exit(-1);
  }

  aim_vector[0] = local_vec[0];
  aim_vector[1] = local_vec[1];
  aim_vector[2] = local_vec[2];

  if (out_dist != NULL) {
    *out_dist = dist;
  }
  if (out_speed != NULL) {
    *out_speed = speed;
  }
  if (out_t != NULL) {
    *out_t = t;
  }

  return 1;
}

/* Resolve the launch speed for a projectile and compute its aim direction.
 *
 * If param_4 is NULL the speed is read from the projectile tag definition at
 * offset 0x1e4 (pointer to float).  Otherwise param_4 is dereferenced to get
 * the speed value.  The resolved speed is stored back into param_4 so both
 * call paths share the same code below.
 *
 * If the projectile tag has the ballistic-arc flag set (bit 1 of byte at
 * param_1+0x17c) AND the per-arc gravity value at param_1+0x1cc is > 0.0f,
 * projectile_aim_ballistic (ballistic arc solver) is called to compute a curved
 * trajectory.  Otherwise the simpler straight-line aim helper
 * projectile_aim_linear is used.  param_13, when non-NULL, receives 0 for the
 * arc path and 1 for the straight-line path. */
/* Returns the inner aim-solver's success flag in EAX (void-EAX implicit
 * return). The original is declared void and writes the arc/linear selector
 * through param_13, but it leaks the residual EAX of projectile_aim_ballistic
 * / projectile_aim_linear (neither path resets AL/EAX before RET). Callers such
 * as actor_combat firing-solution (actor_combat_compute_ballistic_solution) test this AL to decide whether
 * a valid aim solution exists; return-ignoring callers are unaffected. */
char projectile_aim(int projectile_tag, int param_2, int param_3, void *param_4,
                    int param_5, int param_6, int param_7, int param_8,
                    int param_9, int param_10, int param_11, int param_12,
                    void *param_13)
{
  float speed;
  char *out;
  char result;

  if (param_4 == NULL) {
    speed = *(float *)(projectile_tag + 0x1e4);
  } else {
    speed = *(float *)param_4;
  }

  out = (char *)param_13;

  if ((*(unsigned char *)(projectile_tag + 0x17c) & 2) &&
      (*(float *)(projectile_tag + 0x1cc) > *(float *)0x2533c0)) {
    result = projectile_aim_ballistic(
        speed, *(float *)(projectile_tag + 0x1cc), (float *)param_2,
        (float *)param_3, param_5, (float *)param_6, (float *)param_7,
        (char)param_8, (float *)param_9, (float *)param_10, (float *)param_11,
        (float *)param_12, 0, 0);
    if (out != NULL) {
      *out = 0;
    }
  } else {
    result = (char)projectile_aim_linear(
        speed, (float *)param_2, (float *)param_3, (float *)param_9,
        (float *)param_10, (float *)param_11, (float *)param_12);
    if (out != NULL) {
      *out = 1;
    }
  }

  return result;
}

/* FUN_000f8590 (0xf8590) — XBE naked draft (batch 65). */
#if defined(__clang__)
static void *(*const bf8590_get)(int, int) = object_get_and_verify_type;

__attribute__((naked, noinline))
void FUN_000f8590(int projectile_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl $0x20\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x44(%%ecx)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x40(%%ecx)\n\t"
      "flds 0x3c(%%ecx)\n\t"
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
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "movl 0x1dc(%%ecx), %%eax\n\t"
      "jnp .LFUN_000f8590_1\n\t"
      "flds 0x2533c8\n\t"
      "orl $1, %%eax\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "movl %%eax, 0x1dc(%%ecx)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x3c(%%ecx)\n\t"
      "fstps 0x214(%%ecx)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x40(%%ecx)\n\t"
      "fstps 0x218(%%ecx)\n\t"
      "fmuls 0x44(%%ecx)\n\t"
      "fstps 0x21c(%%ecx)\n\t"
      "fld %%st(0)\n\t"
      "fsin\n\t"
      "fstps 0x220(%%ecx)\n\t"
      "fcos\n\t"
      "fstps 0x224(%%ecx)\n\t"
      "ret\n\t"
      ".LFUN_000f8590_1:\n\t"
      "andl $0xfffffffe, %%eax\n\t"
      "fstp %%st(0)\n\t"
      "movl %%eax, 0x1dc(%%ecx)\n\t"
      "movl $0, 0x220(%%ecx)\n\t"
      "movl $0x3f800000, 0x224(%%ecx)\n\t"
      "ret\n\t"
      :
      : [get] "m"(bf8590_get)
      : "memory");
}
#else
#error "FUN_000f8590: clang naked draft required"
#endif


/* FUN_000f8640 (0xf8640) — XBE naked draft (batch 64). */
#if defined(__clang__)
static void *(*const bf8640_get)(int, int) = object_get_and_verify_type;
static void *(*const bf8640_tag)(int, int) = tag_get;
static float (*const bf8640_cf7fa0)(void *tag, float range_begin, float range_end) = FUN_000f7fa0;

__attribute__((naked, noinline))
void FUN_000f8640(int projectile_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl $0x20\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x70726f6a\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movb 0x4(%%esi), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $0x10, %%al\n\t"
      "je .LFUN_000f8640_1\n\t"
      "movl 0x1e0(%%ecx), %%edx\n\t"
      "movl 0x1dc(%%ecx), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[cf7fa0]\n\t"
      "fstps 0x20c(%%esi)\n\t"
      "movl 0x1e0(%%ecx), %%edx\n\t"
      "movl %%edx, 0x210(%%esi)\n\t"
      "flds 0x1dc(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f8640_2\n\t"
      "flds 0x1dc(%%ecx)\n\t"
      "fdivs 0x1e4(%%ecx)\n\t"
      "fstps 0x208(%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LFUN_000f8640_1:\n\t"
      "movl 0x1d4(%%ecx), %%eax\n\t"
      "movl 0x1d0(%%ecx), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[cf7fa0]\n\t"
      "fstps 0x20c(%%esi)\n\t"
      "movl 0x1e0(%%ecx), %%eax\n\t"
      "movl %%eax, 0x210(%%esi)\n\t"
      "flds 0x1d0(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f8640_2\n\t"
      "flds 0x1d0(%%ecx)\n\t"
      "fdivs 0x1e4(%%ecx)\n\t"
      "fstps 0x208(%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LFUN_000f8640_2:\n\t"
      "movl $0x3f800000, 0x204(%%esi)\n\t"
      "movl $0, 0x208(%%esi)\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [get] "m"(bf8640_get), [tag] "m"(bf8640_tag), [cf7fa0] "m"(bf8640_cf7fa0)
      : "memory");
}
#else
#error "FUN_000f8640: clang naked draft required"
#endif


/* FUN_000f8720 (0xf8720) — XBE naked draft (batch 58). */
#if defined(__clang__)
static void *(*const bf8720_get)(int, int) = object_get_and_verify_type;
static void *(*const bf8720_tag)(int, int) = tag_get;
static bool (*const bf8720_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;
static float (*const bf8720_norm)(float *) = normalize3d;
static bool (*const bf8720_v30d0)(unsigned int, float *, float *, int, short *) = FUN_000130d0;

__attribute__((naked, noinline))
bool FUN_000f8720(int projectile_handle __attribute__((unused)), float *new_pos __attribute__((unused)), int16_t *collision_result __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x40, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl $0x20\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x70726f6a\n\t"
      "call *%[tag]\n\t"
      "flds (%%edi)\n\t"
      "fsubs 0xc(%%ebx)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "leal 0xc(%%ebx), %%esi\n\t"
      "pushl %%edx\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "flds 0x4(%%edi)\n\t"
      "movl 0x1e4(%%ebx), %%eax\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "flds 0x8(%%edi)\n\t"
      "pushl $0x1000e9\n\t"
      "fsubs 0x8(%%esi)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "addl $0x24, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f8720_4\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "flds 0x1a0(%%ecx)\n\t"
      "fcomps 0x253f44\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000f8720_2\n\t"
      ".LFUN_000f8720_1:\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f8720_2:\n\t"
      "flds (%%edi)\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "fsubs (%%esi)\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "flds 0x4(%%edi)\n\t"
      "pushl %%edx\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsubs 0x8(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fld %%st(2)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fld %%st(2)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls (%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000f8720_3\n\t"
      "movl 0x31fc40, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".LFUN_000f8720_3:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "flds 0x1a0(%%eax)\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "flds -0x10(%%ebp)\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds (%%esi)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x4(%%esi)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x8(%%esi)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x1a0(%%eax)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds (%%edi)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x4(%%edi)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fadds 0x8(%%edi)\n\t"
      "flds 0x1a0(%%eax)\n\t"
      "movl 0x1e4(%%ebx), %%eax\n\t"
      "fchs\n\t"
      "fld %%st(0)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds (%%esi)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x4(%%esi)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x8(%%esi)\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "fstp %%st(0)\n\t"
      "pushl $0x89\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds (%%edi)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x4(%%edi)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x8(%%edi)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fsubs -0x1c(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fsubs -0x18(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fsubs -0x14(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f8720_4\n\t"
      "movl 0x1e4(%%ebx), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x89\n\t"
      "call *%[v30d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f8720_1\n\t"
      ".LFUN_000f8720_4:\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(bf8720_get), [tag] "m"(bf8720_tag), [ray] "m"(bf8720_ray), [norm] "m"(bf8720_norm), [v30d0] "m"(bf8720_v30d0)
      : "memory");
}
#else
#error "FUN_000f8720: clang naked draft required"
#endif


/* FUN_000f8920 (0xf8920) — XBE naked draft (batch 57). */
#if defined(__clang__)
static void *(*const bf8920_get)(int, int) = object_get_and_verify_type;
static void *(*const bf8920_tag)(int, int) = tag_get;
static bool (*const bf8920_gerun)(void) = game_engine_running;
static int *(*const bf8920_gseed)(void) = get_global_random_seed_address;
static float (*const bf8920_rmreal)(unsigned int *) = random_math_real;
static vector3_t * (*const bf8920_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static void (*const bf8920_c1411c0)(int object_handle) = object_detach_from_parent;
static void (*const bf8920_otrans)(int, float *, void *) = object_translate;
static bool (*const bf8920_oplace)(int, float *) = object_try_place;
static void (*const bf8920_c1446a0)(int object_handle) = object_update_children_recursive;
static void (*const bf8920_c141b70)(int object_handle) = object_compute_node_matrices;
static void (*const bf8920_c986d0)(int contrail_handle, bool reset_points, float delta_time) = contrail_set_state_for_object;
static void (*const bf8920_c141360)(int object_handle, float *out_forward, float *out_up) = object_get_orientation;
static int (*const bf8920_c9f0e0)(int effect_tag_index, int object_index, float *translational_velocity, short marker_count, void *effect_definition, float *marker_points, float *marker_forwards, float scale_a, float scale_b, float unknown1, float unknown2, float unknown3) = effect_new_unattached_from_markers;
static void (*const bf8920_c136750)(void *damage_params, int tag_index) = damage_data_new;
static void (*const bf8920_c137d20)(void *damage_params, int object_handle, short node_index, short region_index, short permutation_index, unsigned int flags) = object_cause_damage;
static void *(*const bf8920_elem)(void *, int, int) = tag_block_get_element;
static void (*const bf8920_c425c0)(int object_handle, float *position, short effect_type, short volume, short count) = FUN_000425c0;

__attribute__((naked, noinline))
void FUN_000f8920(int projectile_handle __attribute__((unused)), char has_hit_count __attribute__((unused)), float current_time __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc0, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $0x20\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x70726f6a\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl $0x25386f, -0x14(%%ebp)\n\t"
      "movl $0x26ad40, -0x10(%%ebp)\n\t"
      "movb 0x17c(%%ebx), %%al\n\t"
      "movl 0x1b8(%%ebx), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $8, %%al\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "je .LFUN_000f8920_11\n\t"
      "testb $0x40, 0x1dc(%%esi)\n\t"
      "jne .LFUN_000f8920_11\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000f8920_11\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0xc8(%%ebx), %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%ebx, -0x18(%%ebp)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "je .LFUN_000f8920_3\n\t"
      ".LFUN_000f8920_1:\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%edx\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jne .LFUN_000f8920_2\n\t"
      "pushl $0x20\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movb 0x1dc(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $0x40, %%cl\n\t"
      "jne .LFUN_000f8920_2\n\t"
      "incl -0x4(%%ebp)\n\t"
      ".LFUN_000f8920_2:\n\t"
      "movl 0xc4(%%ebx), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .LFUN_000f8920_1\n\t"
      "movl -0x18(%%ebp), %%ebx\n\t"
      ".LFUN_000f8920_3:\n\t"
      "cmpw $0, 0x64(%%ebx)\n\t"
      "jne .LFUN_000f8920_10\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0x1c8(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_000f8920_4\n\t"
      "call *%[gerun]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f8920_10\n\t"
      ".LFUN_000f8920_4:\n\t"
      "cmpw $6, -0x4(%%ebp)\n\t"
      "jle .LFUN_000f8920_10\n\t"
      "movl 0xc8(%%ebx), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_000f8920_9\n\t"
      "jmp .LFUN_000f8920_5\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_000f8920_5:\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jne .LFUN_000f8920_8\n\t"
      "pushl $0x20\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movb 0x1dc(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $0x40, %%cl\n\t"
      "jne .LFUN_000f8920_8\n\t"
      "pushl $0x20\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $6, -0x4(%%ebp)\n\t"
      "movl %%eax, %%edi\n\t"
      "jg .LFUN_000f8920_6\n\t"
      "orl $0x40, 0x1dc(%%edi)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fmuls 0x1f0(%%edi)\n\t"
      "fstps 0x1f0(%%edi)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fmuls 0x1f8(%%edi)\n\t"
      "addl $8, %%esp\n\t"
      "fstps 0x1f8(%%edi)\n\t"
      "jmp .LFUN_000f8920_7\n\t"
      ".LFUN_000f8920_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, 0x1f0(%%edi)\n\t"
      "movl %%eax, 0x1f8(%%edi)\n\t"
      ".LFUN_000f8920_7:\n\t"
      "decl -0x4(%%ebp)\n\t"
      ".LFUN_000f8920_8:\n\t"
      "movl 0xc4(%%ebx), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .LFUN_000f8920_5\n\t"
      ".LFUN_000f8920_9:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0x198(%%edx), %%eax\n\t"
      "movl 0xcc(%%esi), %%edx\n\t"
      "leal -0xb4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "call *%[c1412f0]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1411c0]\n\t"
      "leal 0xc(%%esi), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x3c(%%ebp)\n\t"
      "pushl $0\n\t"
      "leal -0xb4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "call *%[otrans]\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[oplace]\n\t"
      "pushl %%edi\n\t"
      "call *%[c1446a0]\n\t"
      "addl $0x24, %%esp\n\t"
      ".LFUN_000f8920_10:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      ".LFUN_000f8920_11:\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f8920_12\n\t"
      "movl 0x1ec(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000f8920_12\n\t"
      "cmpl $-1, 0xfc(%%esi,%%eax,4)\n\t"
      "je .LFUN_000f8920_12\n\t"
      "pushl %%edi\n\t"
      "call *%[c141b70]\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x10(%%ebp)\n\t"
      "movl 0x1ec(%%esi), %%eax\n\t"
      "movl 0xfc(%%esi,%%eax,4), %%ecx\n\t"
      "fmuls 0x28ab38\n\t"
      "fstps (%%esp)\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c986d0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000f8920_12:\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1412f0]\n\t"
      "leal -0xc0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x54(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c141360]\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "movl 0x31fc50, %%edx\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "pushl $0\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl (%%edx), %%eax\n\t"
      "pushl $0\n\t"
      "movl %%eax, -0x48(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "pushl $0\n\t"
      "movl %%ecx, -0x44(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "leal -0x54(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, -0x40(%%ebp)\n\t"
      "movl 0x74(%%esi), %%eax\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $2\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c9f0e0]\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "addl $0x44, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000f8920_13\n\t"
      "movl 0x220(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000f8920_13\n\t"
      "pushl %%eax\n\t"
      "leal -0xa8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c136750]\n\t"
      "movl -0xa4(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "leal -0x74(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "orl $8, %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, -0xa4(%%ebp)\n\t"
      "call *%[c141360]\n\t"
      "leal -0x8c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1412f0]\n\t"
      "movl -0x8c(%%ebp), %%edx\n\t"
      "movl -0x88(%%ebp), %%eax\n\t"
      "movl -0x84(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "movl %%edx, -0x80(%%ebp)\n\t"
      "movl 0x74(%%esi), %%edx\n\t"
      "movl %%eax, -0x7c(%%ebp)\n\t"
      "movl 0x70(%%esi), %%eax\n\t"
      "pushl $-1\n\t"
      "movl %%edx, -0x9c(%%ebp)\n\t"
      "movl 0xcc(%%esi), %%edx\n\t"
      "pushl $-1\n\t"
      "movl %%eax, -0xa0(%%ebp)\n\t"
      "movl %%ecx, -0x78(%%ebp)\n\t"
      "movw 0x68(%%esi), %%cx\n\t"
      "pushl %%edx\n\t"
      "leal -0xa8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movw %%cx, -0x98(%%ebp)\n\t"
      "call *%[c137d20]\n\t"
      "addl $0x34, %%esp\n\t"
      ".LFUN_000f8920_13:\n\t"
      "movw 0x1e2(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_000f8920_16\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_000f8920_14\n\t"
      "movl 0x240(%%ebx), %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "leal 0x240(%%ebx), %%ecx\n\t"
      "jge .LFUN_000f8920_14\n\t"
      "pushl $0xa0\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_000f8920_15\n\t"
      ".LFUN_000f8920_14:\n\t"
      "movl $0x31ed08, %%eax\n\t"
      ".LFUN_000f8920_15:\n\t"
      "movl 0x74(%%eax), %%eax\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x54(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x74(%%esi), %%edx\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $2\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c9f0e0]\n\t"
      "addl $0x30, %%esp\n\t"
      ".LFUN_000f8920_16:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x1f0(%%ebx), %%cx\n\t"
      "pushl $1\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl $2\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c425c0]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(bf8920_get), [tag] "m"(bf8920_tag), [gerun] "m"(bf8920_gerun), [gseed] "m"(bf8920_gseed), [rmreal] "m"(bf8920_rmreal), [c1412f0] "m"(bf8920_c1412f0), [c1411c0] "m"(bf8920_c1411c0), [otrans] "m"(bf8920_otrans), [oplace] "m"(bf8920_oplace), [c1446a0] "m"(bf8920_c1446a0), [c141b70] "m"(bf8920_c141b70), [c986d0] "m"(bf8920_c986d0), [c141360] "m"(bf8920_c141360), [c9f0e0] "m"(bf8920_c9f0e0), [c136750] "m"(bf8920_c136750), [c137d20] "m"(bf8920_c137d20), [elem] "m"(bf8920_elem), [c425c0] "m"(bf8920_c425c0)
      : "memory");
}
#else
#error "FUN_000f8920: clang naked draft required"
#endif


/* Initialise a newly-created projectile object.
 *
 * Called once per projectile spawn.  Sets up all per-object state that cannot
 * be baked into the tag definition:
 *
 *   - Sets the object active-flags bit (0x2000) and the fuze-type field
 *     (proj+0x1dc = 2).
 *   - Clears the target-object handle (proj+0x1e8 = -1) and the per-tick
 *     counter word (proj+0x1e0 = 0; proj+0x1e2 = 0xFFFF).
 *   - Resolves and stores the root-parent handle for the owner object
 *     (proj+0x1e4 = object_get_root_parent(proj[0x1d])).
 *   - Computes per-tick speed and range decay factors:
 *       proj+0x1f4 = 1.0f / (initial_speed * 30.0f)  if >= 1 tick worth
 *       proj+0x1fc = 1.0f / (max_range   * 30.0f)    if >= 1 tick worth
 *     (30.0f = TICKS_PER_SECOND at 0x253394; 1.0f = 0x2533c8).
 *   - Walks the tag's material-response block (tag+0x140, element size 0x48)
 *     and records the first index whose type-tag == 'cont' (0x636f6e74) at
 *     proj+0x1ec (-1 if none).
 *   - Applies one tick of velocity to position:
 *       proj+0x18..0x20 (pos.xyz) += tag[0x1e4] * proj+0x24..0x2c (vel.xyz)
 *   - Tests whether the new position is inside a valid world region via
 *     FUN_0018f3e0(&proj[0x48], &proj[0x50], NULL).  Sets or clears bit 4
 *     of the object flags word (proj+0x4) accordingly.
 *   - Calls FUN_000f8590 (velocity direction cache) and FUN_000f8640
 *     (detonation radius cache) with the projectile handle in EAX.
 *   - Sets flags bits 0xc0000 (active + detonating-armed) in proj+0x4.
 *   - Returns 1 (success).
 *
 * Layout notes (all relative to proj = object_get_and_verify_type(handle,
 * 0x20)): proj+0x04  object flags (uint32) proj+0x18  position.xyz (3 floats)
 *   proj+0x24  velocity.xyz / direction (3 floats, pre-normalised by spawner)
 *   proj+0x48  location struct (passed as arg1 to FUN_0018f3e0)
 *   proj+0x50  world position (passed as arg2 to FUN_0018f3e0)
 *   proj+0x74  parent object handle (int)
 *   proj+0x1dc fuze type (uint32; 2 = standard)
 *   proj+0x1e0 counter word (uint16)
 *   proj+0x1e2 counter high word (uint16; init 0xFFFF)
 *   proj+0x1e4 root-parent handle (int)
 *   proj+0x1e8 target-object handle (int; -1 = none)
 *   proj+0x1ec contact-material index (int; -1 = none)
 *   proj+0x1f4 speed decay factor (float)
 *   proj+0x1fc range decay factor (float)
 *
 * Disasm-verified: call at 0x000f8eaf passes handle in EAX (FUN_000f8590);
 * call at 0x000f8ebf passes handle in EAX (FUN_000f8640).
 * All cdecl stack args confirmed from PUSH/ADD-ESP pairs. */
int projectile_new(int projectile_handle)
{
  char *proj; /* projectile object base (type 0x20) */
  char *proj_tag; /* projectile tag data ('proj') */
  float initial_speed; /* tag+0x1bc / random range result */
  float speed_factor; /* initial_speed * 30.0f */
  float range_factor; /* tag+0x1a4 * 30.0f */
  int root_parent; /* result of object_get_root_parent */
  void *mat_block; /* material response block element pointer */
  int mat_count; /* number of material response entries */
  int mat_idx; /* loop index into material response block */
  int *seed; /* random seed pointer from get_global_random_seed_address */

  proj = (char *)object_get_and_verify_type(projectile_handle, 0x20);
  proj_tag = (char *)tag_get(0x70726f6a, *(int *)proj);

  /* Set active flag bit, fuze type, and clear target/counter fields. */
  *(uint32_t *)(proj + 0x4) |= 0x2000u;
  *(uint32_t *)(proj + 0x1dc) = 2;
  *(int *)(proj + 0x1e8) = -1;
  *(uint16_t *)(proj + 0x1e0) = 0;
  *(uint16_t *)(proj + 0x1e2) = 0xFFFF;

  /* Resolve and store root-parent handle. */
  root_parent = object_get_root_parent(*(int *)(proj + 0x74));
  *(int *)(proj + 0x1e4) = root_parent;

  /* Compute per-tick speed decay factor from initial_speed tag field.
   * Tag+0x17c bit2: if set, initial_speed is a fixed float (tag+0x1bc).
   * Otherwise: random_real_range(seed, tag+0x1bc, tag+0x1c0). */
  if (*(uint8_t *)(proj_tag + 0x17c) & 4) {
    initial_speed = *(float *)(proj_tag + 0x1bc);
  } else {
    seed = get_global_random_seed_address();
    initial_speed = random_real_range(seed, *(float *)(proj_tag + 0x1bc),
                                      *(float *)(proj_tag + 0x1c0));
  }

  /* Store 1.0 / (initial_speed * 30.0) if speed exceeds one-tick threshold. */
  speed_factor = initial_speed * TICKS_PER_SECOND;
  if (*(float *)0x2533c8 <= speed_factor) {
    *(float *)(proj + 0x1f4) = *(float *)0x2533c8 / speed_factor;
  }
  /* Compute per-tick range decay factor from max-range tag field (tag+0x1a4).
   */
  range_factor = *(float *)(proj_tag + 0x1a4) * TICKS_PER_SECOND;
  if (*(float *)0x2533c8 <= range_factor) {
    *(float *)(proj + 0x1fc) = *(float *)0x2533c8 / range_factor;
  }

  /* Find first 'cont' (contact) material response entry in tag block.
   * tag+0x140 = tag_block_t: { int count; ... }; element size = 0x48.
   * Stores the matching index into proj+0x1ec, or -1 if none found. */
  *(int *)(proj + 0x1ec) = -1;
  mat_count = *(int *)(proj_tag + 0x140);
  mat_idx = 0;
  while (mat_idx < mat_count) {
    mat_block =
      tag_block_get_element((void *)(proj_tag + 0x140), mat_idx, 0x48);
    if (*(int *)mat_block == 0x636f6e74) {
      *(int *)(proj + 0x1ec) = mat_idx;
      break;
    }
    mat_idx++;
  }

  /* Apply one tick of initial velocity to position.
   * proj+0x18..0x20 = position.xyz
   * proj+0x24..0x2c = velocity direction (unit vector * initial_speed from
   * spawner) tag+0x1e4 = initial speed (used as the tick delta multiplier here)
   */
  {
    float tick_speed = *(float *)(proj_tag + 0x1e4);
    *(float *)(proj + 0x18) += tick_speed * *(float *)(proj + 0x24);
    *(float *)(proj + 0x1c) += tick_speed * *(float *)(proj + 0x28);
    *(float *)(proj + 0x20) += tick_speed * *(float *)(proj + 0x2c);
  }

  /* Test world-region validity.  FUN_0018f3e0 returns non-zero if the position
   * is inside a valid region.  Bit 4 of object flags = "region-valid" marker.
   */
  if (FUN_0018f3e0((void *)(proj + 0x48), (void *)(proj + 0x50), 0)) {
    *(uint32_t *)(proj + 0x4) |= 0x10u;
  } else {
    *(uint32_t *)(proj + 0x4) &= ~0x10u;
  }

  /* Update velocity direction cache and detonation radius cache.
   * Both functions take the handle in EAX (register-arg convention). */
  FUN_000f8590(projectile_handle);
  projectile_export_function_values(projectile_handle);
  FUN_000f8640(projectile_handle);

  /* Set active + detonating-armed flag bits. */
  *(uint32_t *)(proj + 0x4) |= 0xc0000u;

  return 1;
}

/*
 * Apply an acceleration vector to a projectile's translational velocity and
 * add a random scatter impulse.
 *
 * param_1: projectile datum handle
 * param_2: pointer to a 3-float acceleration vector (x, y, z)
 *
 * Only operates when the projectile has no parent object (proj+0xcc == -1).
 * When active:
 *   1. Validates param_2 (acceleration) and proj+0x18 (translational velocity)
 *      with assert_valid_real_vector2d checks.
 *   2. Adds the acceleration to the object's translational velocity at
 *      proj+0x18..0x20.
 *   3. Generates a random unit direction via random_seed_get_direction3d and
 *      scales it by magnitude(acceleration) * random_real * (PI/2).
 *   4. Adds the scaled random vector to the projectile impulse velocity at
 *      proj+0x3c..0x44.
 *   5. Rebuilds the velocity direction cache (FUN_000f8590).
 *   6. Clears bit 5 of the object flags word at proj+0x4.
 *
 * Disasm-verified: FUN_000f8590 called with projectile_handle in EAX.
 * Deferred stack cleanup: ADD ESP,0x10 at 0xf906b cleans 4 accumulated pushes
 * (random_seed_get_direction3d args + random_math_real arg +
 * real_vector3d_valid arg). The float constant at 0x2568bc = PI/2 (0x3FC90FDB).
 */
void projectile_accelerate(int projectile_handle, float *acceleration)
{
  char *proj; /* projectile object base (type 0x20) */
  char *vel; /* pointer to proj+0x18 (translational velocity xyz) */
  float *seed; /* engine-wide random seed pointer */
  float dir[3]; /* random unit direction from random_seed_get_direction3d */
  float sq_mag; /* squared magnitude of acceleration vector */
  float magnitude; /* magnitude of acceleration vector */
  float rand_real; /* random float in [0,1) from random_math_real */
  float scale; /* scatter scale: rand_real * magnitude * (PI/2) */

  proj = (char *)object_get_and_verify_type(projectile_handle, 0x20);
  tag_get(0x70726f6a, *(int *)proj);

  if (!real_vector3d_valid(acceleration)) {
    csprintf((char *)0x5ab100, "%s: assert_valid_real_vector2d(%f, %f, %f)",
             "acceleration", (double)acceleration[0], (double)acceleration[1],
             (double)acceleration[2]);
    display_assert((char *)0x5ab100, "c:\\halo\\SOURCE\\items\\projectiles.c",
                   0x3ef, 1);
    system_exit(-1);
  }

  /* Only apply acceleration when the projectile has no parent. */
  if (*(int *)(proj + 0xcc) == -1) {
    vel = proj + 0x18;

    if (!real_vector3d_valid((float *)vel)) {
      csprintf((char *)0x5ab100, "%s: assert_valid_real_vector2d(%f, %f, %f)",
               "&projectile->object.translational_velocity",
               (double)*(float *)(proj + 0x18), (double)*(float *)(proj + 0x1c),
               (double)*(float *)(proj + 0x20));
      display_assert((char *)0x5ab100, "c:\\halo\\SOURCE\\items\\projectiles.c",
                     0x3f3, 1);
      system_exit(-1);
    }

    /* Add acceleration to object translational velocity (proj+0x18..0x20). */
    *(float *)(proj + 0x18) += acceleration[0];
    *(float *)(proj + 0x1c) += acceleration[1];
    *(float *)(proj + 0x20) += acceleration[2];

    /* Get a random direction vector into dir[3]. */
    seed = (float *)get_global_random_seed_address();
    random_seed_get_direction3d((unsigned int *)seed, dir);

    /* Compute squared magnitude, then scale = sqrt(sq_mag) * rand * PI/2. */
    sq_mag = acceleration[0] * acceleration[0] +
             acceleration[1] * acceleration[1] +
             acceleration[2] * acceleration[2];

    seed = (float *)get_global_random_seed_address();
    rand_real = random_math_real((unsigned int *)seed);
    magnitude = sqrtf(sq_mag);
    scale = rand_real * magnitude * *(float *)0x2568bc;

    /* Add random scatter to projectile impulse velocity (proj+0x3c..0x44). */
    *(float *)(proj + 0x3c) += dir[0] * scale;
    *(float *)(proj + 0x40) += dir[1] * scale;
    *(float *)(proj + 0x44) += dir[2] * scale;

    /* Rebuild velocity direction cache. */
    FUN_000f8590(projectile_handle);

    /* Clear object flag bit 5 ("motion-pending" or similar). */
    *(uint32_t *)(proj + 0x4) &= ~0x20u;

    if (!real_vector3d_valid((float *)vel)) {
      csprintf((char *)0x5ab100, "%s: assert_valid_real_vector2d(%f, %f, %f)",
               "&projectile->object.translational_velocity",
               (double)*(float *)(proj + 0x18), (double)*(float *)(proj + 0x1c),
               (double)*(float *)(proj + 0x20));
      display_assert((char *)0x5ab100, "c:\\halo\\SOURCE\\items\\projectiles.c",
                     0x405, 1);
      system_exit(-1);
    }
  }
}

/* FUN_000f90d0 (0xf90d0) — XBE naked draft (batch 50). */
#if defined(__clang__)
static void *(*const bf90d0_get)(int, int) = object_get_and_verify_type;
static void *(*const bf90d0_tag)(int, int) = tag_get;
static float (*const bf90d0_norm)(float *) = normalize3d;
static void (*const bf90d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf90d0_exitfn)(int) = system_exit;
static void (*const bf90d0_c136750)(void *damage_params, int tag_index) = damage_data_new;
static void (*const bf90d0_c137d20)(void *damage_params, int object_handle, short node_index, short region_index, short permutation_index, unsigned int flags) = object_cause_damage;
static void *(*const bf90d0_elem)(void *, int, int) = tag_block_get_element;
static int *(*const bf90d0_gseed)(void) = get_global_random_seed_address;
static float (*const bf90d0_rrange)(int *, float, float) = random_real_range;
static float (*const bf90d0_c10c510)(float *v1, float *v2) = FUN_0010c510;
static void *(*const bf90d0_tryget)(int, int) = object_try_and_get_and_verify_type;
static float (*const bf90d0_rmreal)(unsigned int *) = random_math_real;
static void (*const bf90d0_c146a90)(int surface_id, void *damage_params, int unknown) = FUN_00146a90;
static void (*const bf90d0_cf8640)(int projectile_handle) = FUN_000f8640;
static void (*const bf90d0_rndir)(int *, float *, float, float, float *) = random_direction3d;
static void (*const bf90d0_c10b910)(float *v, float *n, float *proj_out, float *perp_out) = FUN_0010b910;
static void (*const bf90d0_c10c8e0)(float *v, float *n, float *out) = FUN_0010c8e0;
static int (*const bf90d0_c9ee40)(int effect_tag_index, int object_index, int attached_object, uint16_t marker_index, short marker_count, void *effect_definition, float *marker_points, float *marker_forwards, float scale_a, float scale_b, float unknown1, float unknown2) = effect_new_attached_from_markers;
static int (*const bf90d0_c9f0e0)(int effect_tag_index, int object_index, float *translational_velocity, short marker_count, void *effect_definition, float *marker_points, float *marker_forwards, float scale_a, float scale_b, float unknown1, float unknown2, float unknown3) = effect_new_unattached_from_markers;
static void (*const bf90d0_otrans)(int, float *, void *) = object_translate;
static void (*const bf90d0_c144240)(int parent_handle, int child_handle, int parent_node_index) = object_attach_to_parent;

__attribute__((naked, noinline))
void FUN_000f90d0(int projectile_handle __attribute__((unused)), float *hit_pos __attribute__((unused)), float param_3 __attribute__((unused)), float *velocity __attribute__((unused)), int16_t *col_result __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xe4, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x20\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x70726f6a\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movw 0x34(%%esi), %%dx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%edi, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movw %%dx, -0x4(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x2c(%%ebp)\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl $0x3f800000, -0x1c(%%ebp)\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcoms 0x2533c0\n\t"
      "addl $0x14, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000f90d0_1\n\t"
      "movl 0x31fc44, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      ".LFUN_000f90d0_1:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "flds 0x1e8(%%ecx)\n\t"
      "fcomps 0x1e4(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000f90d0_3\n\t"
      "fsubs 0x1e8(%%ecx)\n\t"
      "flds 0x1e4(%%ecx)\n\t"
      "fsubs 0x1e8(%%ecx)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fsts -0x20(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000f90d0_2\n\t"
      "movl $0, -0x20(%%ebp)\n\t"
      "jmp .LFUN_000f90d0_5\n\t"
      ".LFUN_000f90d0_2:\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f90d0_5\n\t"
      "jmp .LFUN_000f90d0_4\n\t"
      ".LFUN_000f90d0_3:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_000f90d0_4:\n\t"
      "movl $0x3f800000, -0x20(%%ebp)\n\t"
      ".LFUN_000f90d0_5:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "cmpw $3, (%%esi)\n\t"
      "jne .LFUN_000f90d0_8\n\t"
      "cmpl %%eax, 0x230(%%ecx)\n\t"
      "je .LFUN_000f90d0_8\n\t"
      "cmpl %%eax, 0x38(%%esi)\n\t"
      "jne .LFUN_000f90d0_6\n\t"
      "pushl $1\n\t"
      "pushl $0x47c\n\t"
      "pushl $0x28ab3c\n\t"
      "pushl $0x28ac28\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f90d0_6:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x230(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x8c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c136750]\n\t"
      "movl -0x88(%%ebp), %%eax\n\t"
      "movl 0x70(%%ebx), %%ecx\n\t"
      "movl 0x74(%%ebx), %%edx\n\t"
      "orl $8, %%eax\n\t"
      "movl %%eax, -0x88(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "movw 0x68(%%ebx), %%ax\n\t"
      "movl %%ecx, -0x84(%%ebp)\n\t"
      "movw %%ax, -0x7c(%%ebp)\n\t"
      "leal 0x18(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl %%edx, -0x80(%%ebp)\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x64(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x60(%%ebp)\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%ecx, -0x5c(%%ebp)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%edx, -0x70(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl %%ecx, -0x6c(%%ebp)\n\t"
      "movl %%edi, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%edx, -0x68(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x58(%%ebp)\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x54(%%ebp)\n\t"
      "movl %%eax, -0x50(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4e(%%esi), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x3c(%%esi), %%cx\n\t"
      "leal 0x24(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x3e(%%esi), %%dx\n\t"
      "pushl %%eax\n\t"
      "movl 0x38(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x8c(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c137d20]\n\t"
      "addl $0x24, %%esp\n\t"
      "cmpw $-1, -0x40(%%ebp)\n\t"
      "je .LFUN_000f90d0_7\n\t"
      "movl -0x40(%%ebp), %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".LFUN_000f90d0_7:\n\t"
      "movl -0x44(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      ".LFUN_000f90d0_8:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "testw %%dx, %%dx\n\t"
      "movw %%dx, 0x1e2(%%ebx)\n\t"
      "jl .LFUN_000f90d0_9\n\t"
      "leal 0x240(%%ecx), %%eax\n\t"
      "movswl %%dx, %%ecx\n\t"
      "cmpl (%%eax), %%ecx\n\t"
      "jge .LFUN_000f90d0_9\n\t"
      "pushl $0xa0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "jmp .LFUN_000f90d0_10\n\t"
      ".LFUN_000f90d0_9:\n\t"
      "movl $0x31ed08, %%ebx\n\t"
      ".LFUN_000f90d0_10:\n\t"
      "flds 0x64(%%ebx)\n\t"
      "pushl $0\n\t"
      "fchs\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "movl 0x60(%%ebx), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%edx, %%eax\n\t"
      "fsubr %%st(1), %%st(0)\n\t"
      "pushl %%eax\n\t"
      "flds 0x28(%%esi)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x24(%%esi)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x60(%%ebx)\n\t"
      "fchs\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "leal 0x24(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c10c510]\n\t"
      "fsubs 0x2568bc\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw $0, 0x24(%%ebx)\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "je .LFUN_000f90d0_14\n\t"
      "flds 0x30(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000f90d0_11\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fcomps 0x2c(%%ebx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000f90d0_14\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fcomps 0x30(%%ebx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000f90d0_14\n\t"
      ".LFUN_000f90d0_11:\n\t"
      "flds 0x38(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000f90d0_12\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fcomps 0x34(%%ebx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000f90d0_14\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fcomps 0x38(%%ebx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000f90d0_14\n\t"
      ".LFUN_000f90d0_12:\n\t"
      "testb $1, 0x26(%%ebx)\n\t"
      "je .LFUN_000f90d0_13\n\t"
      "cmpw $3, (%%esi)\n\t"
      "jne .LFUN_000f90d0_14\n\t"
      "movl 0x38(%%esi), %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000f90d0_14\n\t"
      ".LFUN_000f90d0_13:\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "fcomps 0x28(%%ebx)\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000f90d0_14\n\t"
      "movw 0x24(%%ebx), %%ax\n\t"
      "movl 0x48(%%ebx), %%ecx\n\t"
      "movw %%ax, -0x18(%%ebp)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jmp .LFUN_000f90d0_15\n\t"
      ".LFUN_000f90d0_14:\n\t"
      "movw 0x2(%%ebx), %%dx\n\t"
      "movl 0x10(%%ebx), %%eax\n\t"
      "movw %%dx, -0x18(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".LFUN_000f90d0_15:\n\t"
      "cmpw $2, (%%esi)\n\t"
      "jne .LFUN_000f90d0_18\n\t"
      "testb $8, 0x4c(%%esi)\n\t"
      "je .LFUN_000f90d0_18\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x230(%%ecx), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x8c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c136750]\n\t"
      "orl $8, -0x88(%%ebp)\n\t"
      "leal 0x18(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x64(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x60(%%ebp)\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%ecx, -0x5c(%%ebp)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%edx, -0x70(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl %%ecx, -0x6c(%%ebp)\n\t"
      "movl %%edi, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%edx, -0x68(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x58(%%ebp)\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x54(%%ebp)\n\t"
      "movl %%eax, -0x50(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "movw 0x34(%%esi), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "movw %%ax, -0x40(%%ebp)\n\t"
      "jl .LFUN_000f90d0_16\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x240(%%ecx), %%edx\n\t"
      "addl $0x240, %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jge .LFUN_000f90d0_16\n\t"
      "pushl $0xa0\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "jmp .LFUN_000f90d0_17\n\t"
      ".LFUN_000f90d0_16:\n\t"
      "movl $0x31ed08, -0x3c(%%ebp)\n\t"
      ".LFUN_000f90d0_17:\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "movl 0x44(%%esi), %%ecx\n\t"
      "movl %%eax, -0x74(%%ebp)\n\t"
      "movzbw 0x4d(%%esi), %%ax\n\t"
      "movl %%edx, -0x78(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "leal -0x8c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c146a90]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000f90d0_18:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "leal 0x18(%%esi), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .LFUN_000f90d0_28\n\t"
      "movw (%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_000f90d0_21\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "testb $0x10, %%al\n\t"
      "jne .LFUN_000f90d0_19\n\t"
      "orl $0x10, %%eax\n\t"
      "jmp .LFUN_000f90d0_20\n\t"
      ".LFUN_000f90d0_19:\n\t"
      "andl $0xffffffef, %%eax\n\t"
      ".LFUN_000f90d0_20:\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "call *%[cf8640]\n\t"
      "flds 0x24(%%esi)\n\t"
      "fmuls 0x255ef8\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "fsubrs (%%eax)\n\t"
      "fstps (%%eax)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fmuls 0x255ef8\n\t"
      "fsubrs 0x4(%%eax)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fmuls 0x255ef8\n\t"
      "fsubrs 0x8(%%eax)\n\t"
      "fstps 0x8(%%eax)\n\t"
      "jmp .LFUN_000f90d0_24\n\t"
      ".LFUN_000f90d0_21:\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .LFUN_000f90d0_22\n\t"
      "flds 0x2533c8\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "fsubs 0x90(%%ebx)\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%edi)\n\t"
      "fstps (%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "fstps 0x4(%%edi)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "fstps 0x8(%%edi)\n\t"
      "movl 0x38(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x1e4(%%edx)\n\t"
      "jmp .LFUN_000f90d0_24\n\t"
      ".LFUN_000f90d0_22:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "flds 0x1c0(%%eax)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000f90d0_27\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "orl $0x14, 0x1dc(%%eax)\n\t"
      "movl $4, -0x18(%%ebp)\n\t"
      ".LFUN_000f90d0_23:\n\t"
      "movl 0x31fc38, %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      ".LFUN_000f90d0_24:\n\t"
      "flds 0x60(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000f90d0_25\n\t"
      "movl 0x60(%%ebx), %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rndir]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f90d0_25:\n\t"
      "flds 0x64(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000f90d0_26\n\t"
      "pushl %%edi\n\t"
      "call *%[norm]\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000f90d0_26\n\t"
      "flds 0x64(%%ebx)\n\t"
      "movl 0x64(%%ebx), %%eax\n\t"
      "fchs\n\t"
      "movl %%eax, %%ecx\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "movl -0x38(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x90(%%ebp)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%edi)\n\t"
      "fstps (%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "fstps 0x4(%%edi)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "fstps 0x8(%%edi)\n\t"
      ".LFUN_000f90d0_26:\n\t"
      "cmpw $4, -0x18(%%ebp)\n\t"
      "flds 0x8(%%edi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "flds (%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "faddp %%st(1)\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fsts -0x38(%%ebp)\n\t"
      "je .LFUN_000f90d0_29\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "flds 0x1c4(%%eax)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fxch %%st(1)\n\t"
      "fxch %%st(2)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000f90d0_30\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0x20\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "movl $1, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%cx, 0x1e0(%%eax)\n\t"
      "jge .LFUN_000f90d0_30\n\t"
      "movw %%cx, 0x1e0(%%eax)\n\t"
      "jmp .LFUN_000f90d0_30\n\t"
      ".LFUN_000f90d0_27:\n\t"
      "movl $1, -0x18(%%ebp)\n\t"
      "jmp .LFUN_000f90d0_23\n\t"
      ".LFUN_000f90d0_28:\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .LFUN_000f90d0_23\n\t"
      "leal -0x9c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0xa8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x24(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c10b910]\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x9c(%%ebx)\n\t"
      "addl $0x10, %%esp\n\t"
      "fmuls -0x9c(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x98(%%ebx)\n\t"
      "fmuls -0xa8(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps (%%edi)\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x9c(%%ebx)\n\t"
      "fmuls -0x98(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x98(%%ebx)\n\t"
      "fmuls -0xa4(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x4(%%edi)\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x9c(%%ebx)\n\t"
      "fmuls -0x94(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x98(%%ebx)\n\t"
      "fmuls -0xa0(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x8(%%edi)\n\t"
      "jmp .LFUN_000f90d0_24\n\t"
      ".LFUN_000f90d0_29:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_000f90d0_30:\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fcomps 0x253f44\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000f90d0_31\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl 0x1dc(%%eax), %%ecx\n\t"
      "orl $0x10, %%ecx\n\t"
      "movl %%ecx, 0x1dc(%%eax)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fcomps 0x2533e4\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f90d0_31\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "orl $0x20, %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "flds 0x1c0(%%edx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000f90d0_31\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x20\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl $1, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%cx, 0x1e0(%%eax)\n\t"
      "jge .LFUN_000f90d0_31\n\t"
      "movw %%cx, 0x1e0(%%eax)\n\t"
      ".LFUN_000f90d0_31:\n\t"
      "movswl 0x5c(%%ebx), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_000f90d0_32\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_000f90d0_35\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls 0x28ac24\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "jmp .LFUN_000f90d0_33\n\t"
      ".LFUN_000f90d0_32:\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      ".LFUN_000f90d0_33:\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000f90d0_34\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      "jmp .LFUN_000f90d0_35\n\t"
      ".LFUN_000f90d0_34:\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f90d0_35\n\t"
      "movl $0x3f800000, -0x1c(%%ebp)\n\t"
      ".LFUN_000f90d0_35:\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000f90d0_36\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "jmp .LFUN_000f90d0_37\n\t"
      ".LFUN_000f90d0_36:\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f90d0_37\n\t"
      "movl $0x3f800000, -0x14(%%ebp)\n\t"
      ".LFUN_000f90d0_37:\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "movl -0x2c(%%ebp), %%edx\n\t"
      "fmuls 0x255e94\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "movl %%edx, -0xcc(%%ebp)\n\t"
      "movl 0x31fc50, %%edx\n\t"
      "fstps -0xd8(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "movl %%ecx, -0xc4(%%ebp)\n\t"
      "fmuls 0x255e94\n\t"
      "movl %%eax, -0xc8(%%ebp)\n\t"
      "fstps -0xd4(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x255e94\n\t"
      "fstps -0xd0(%%ebp)\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, -0xb4(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, -0xb0(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "leal 0x24(%%esi), %%eax\n\t"
      "movl %%edx, -0xac(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0xe4(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0xe0(%%ebp)\n\t"
      "leal -0xc0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0xdc(%%ebp)\n\t"
      "call *%[c10c8e0]\n\t"
      "addl $0xc, %%esp\n\t"
      "leal -0x74(%%ebp), %%eax\n\t"
      "movl $5, %%edx\n\t"
      ".LFUN_000f90d0_38:\n\t"
      "leal 0x18(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%ebx, (%%edi)\n\t"
      "movl 0x4(%%ecx), %%ebx\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ebx, 0x4(%%edi)\n\t"
      "addl $0xc, %%eax\n\t"
      "decl %%edx\n\t"
      "movl %%ecx, 0x8(%%edi)\n\t"
      "jne .LFUN_000f90d0_38\n\t"
      "flds -0x34(%%ebp)\n\t"
      "movl -0x1c(%%ebp), %%ebx\n\t"
      "fcomps 0x28ac20\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f90d0_41\n\t"
      "cmpw $3, (%%esi)\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "leal -0x74(%%ebp), %%ecx\n\t"
      "leal -0xe4(%%ebp), %%eax\n\t"
      "jne .LFUN_000f90d0_39\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "movl 0x38(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x3e(%%esi), %%dx\n\t"
      "pushl $0x31f3a0\n\t"
      "pushl $5\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c9ee40]\n\t"
      "jmp .LFUN_000f90d0_40\n\t"
      ".LFUN_000f90d0_39:\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x31f3a0\n\t"
      "pushl $5\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c9f0e0]\n\t"
      ".LFUN_000f90d0_40:\n\t"
      "addl $0x30, %%esp\n\t"
      ".LFUN_000f90d0_41:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl 0x1dc(%%eax), %%eax\n\t"
      "testb $0x20, %%al\n\t"
      "jne .LFUN_000f90d0_45\n\t"
      "testb $0x10, %%al\n\t"
      "jne .LFUN_000f90d0_42\n\t"
      "cmpw $4, -0x18(%%ebp)\n\t"
      "jne .LFUN_000f90d0_45\n\t"
      ".LFUN_000f90d0_42:\n\t"
      "cmpw $3, (%%esi)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x200(%%ecx), %%eax\n\t"
      "jne .LFUN_000f90d0_43\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "leal -0xe4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x3e(%%esi), %%cx\n\t"
      "leal -0x74(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x38(%%esi), %%edx\n\t"
      "pushl $0x31f3a0\n\t"
      "pushl $5\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c9ee40]\n\t"
      "jmp .LFUN_000f90d0_44\n\t"
      ".LFUN_000f90d0_43:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "leal -0xe4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x74(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x31f3a0\n\t"
      "pushl $5\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c9f0e0]\n\t"
      ".LFUN_000f90d0_44:\n\t"
      "addl $0x30, %%esp\n\t"
      ".LFUN_000f90d0_45:\n\t"
      "movswl -0x18(%%ebp), %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .LFUN_000f90d0_56\n\t"
      "jmp *.LFUN_000f90d0_jt(,%%eax,4)\n\t"
      ".LFUN_000f90d0_46:\n\t"
      "pushl $0x20\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl $2, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%cx, 0x1e0(%%eax)\n\t"
      "jge .LFUN_000f90d0_55\n\t"
      "popl %%edi\n\t"
      "movw %%cx, 0x1e0(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f90d0_47:\n\t"
      "pushl $0x20\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl $1, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%cx, 0x1e0(%%eax)\n\t"
      "jge .LFUN_000f90d0_55\n\t"
      "popl %%edi\n\t"
      "movw %%cx, 0x1e0(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f90d0_48:\n\t"
      "cmpw $3, (%%esi)\n\t"
      "jne .LFUN_000f90d0_52\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "testb $8, 0x17c(%%edx)\n\t"
      "je .LFUN_000f90d0_52\n\t"
      "movl 0x38(%%esi), %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0xc8(%%eax), %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "je .LFUN_000f90d0_52\n\t"
      "nop\n\t"
      ".LFUN_000f90d0_49:\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "movl (%%edx), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jne .LFUN_000f90d0_50\n\t"
      "pushl $0x20\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movb 0x1dc(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $0x40, %%cl\n\t"
      "jne .LFUN_000f90d0_50\n\t"
      "pushl $0x20\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%ecx, 0x1f8(%%eax)\n\t"
      "movl %%ecx, 0x1f0(%%eax)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".LFUN_000f90d0_50:\n\t"
      "cmpw $6, -0x4(%%ebp)\n\t"
      "jge .LFUN_000f90d0_51\n\t"
      "movl 0xc4(%%ebx), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .LFUN_000f90d0_49\n\t"
      "jmp .LFUN_000f90d0_52\n\t"
      ".LFUN_000f90d0_51:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "orl $0x80, 0x1dc(%%eax)\n\t"
      ".LFUN_000f90d0_52:\n\t"
      "movl 0x31fc38, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "leal 0x18(%%edi), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl 0x31fc38, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal 0x3c(%%edi), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl 0x1dc(%%edi), %%edx\n\t"
      "orl $0x20, %%ecx\n\t"
      "orl $8, %%edx\n\t"
      "movl %%ecx, 0x4(%%edi)\n\t"
      "leal 0xc(%%esi), %%ecx\n\t"
      "movl %%edx, 0x1dc(%%edi)\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[otrans]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $3, (%%esi)\n\t"
      "jne .LFUN_000f90d0_53\n\t"
      "movl 0x38(%%esi), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x3e(%%esi), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c144240]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000f90d0_53:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "testb $4, 0x17c(%%eax)\n\t"
      "je .LFUN_000f90d0_55\n\t"
      "flds 0x1c0(%%eax)\n\t"
      "fmuls 0x253394\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000f90d0_54\n\t"
      "flds 0x2533c8\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fstps 0x1f4(%%edi)\n\t"
      ".LFUN_000f90d0_54:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_000f90d0_55:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000f90d0_56:\n\t"
      "pushl $1\n\t"
      "pushl $0x5cf\n\t"
      "pushl $0x28ab3c\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000f90d0_jt:\n\t"
      ".long .LFUN_000f90d0_46\n\t"
      ".long .LFUN_000f90d0_47\n\t"
      ".long .LFUN_000f90d0_55\n\t"
      ".long .LFUN_000f90d0_55\n\t"
      ".long .LFUN_000f90d0_48\n\t"
      ".text\n\t"
      :
      : [get] "m"(bf90d0_get), [tag] "m"(bf90d0_tag), [norm] "m"(bf90d0_norm), [assert] "m"(bf90d0_assert), [exitfn] "m"(bf90d0_exitfn), [c136750] "m"(bf90d0_c136750), [c137d20] "m"(bf90d0_c137d20), [elem] "m"(bf90d0_elem), [gseed] "m"(bf90d0_gseed), [rrange] "m"(bf90d0_rrange), [c10c510] "m"(bf90d0_c10c510), [tryget] "m"(bf90d0_tryget), [rmreal] "m"(bf90d0_rmreal), [c146a90] "m"(bf90d0_c146a90), [cf8640] "m"(bf90d0_cf8640), [rndir] "m"(bf90d0_rndir), [c10b910] "m"(bf90d0_c10b910), [c10c8e0] "m"(bf90d0_c10c8e0), [c9ee40] "m"(bf90d0_c9ee40), [c9f0e0] "m"(bf90d0_c9f0e0), [otrans] "m"(bf90d0_otrans), [c144240] "m"(bf90d0_c144240)
      : "memory");
}
#else
#error "FUN_000f90d0: clang naked draft required"
#endif


/* FUN_000f9c40 (0xf9c40) — XBE naked draft (batch 50). */
#if defined(__clang__)
static void *(*const bf9c40_get)(int, int) = object_get_and_verify_type;
static void *(*const bf9c40_tag)(int, int) = tag_get;
static void (*const bf9c40_penter)(void *) = profile_enter_private;
static void (*const bf9c40_c978f0)(int contrail_handle) = contrail_delete;
static void (*const bf9c40_cf7ec0)(int projectile_handle) = projectile_export_function_values;
static int (*const bf9c40_c84a10)(float *vector) = real_vector3d_valid;
static char * (*const bf9c40_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const bf9c40_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bf9c40_exitfn)(int) = system_exit;
static float (*const bf9c40_cb5590)(int16_t value_type) = FUN_000b5590;
static float (*const bf9c40_c1ad60)(float *a, float *b) = FUN_0001ad60;
static void (*const bf9c40_c1a9520)(int object_handle, float *out_position) = FUN_001a9520;
static int (*const bf9c40_gtime)(void) = game_time_get;
static float (*const bf9c40_c10a5e0)(int16_t function_type, float input) = FUN_0010a5e0;
static void (*const bf9c40_c10cc40)(float *out, float *angles) = angles_to_vector;
static void (*const bf9c40_cross)(float *, float *, float *) = cross_product3d;
static float (*const bf9c40_norm)(float *) = normalize3d;
static void (*const bf9c40_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;
static void (*const bf9c40_cf7e40)(int projectile_handle, int16_t state) = FUN_000f7e40;
static bool (*const bf9c40_ca16b0)(float *point) = valid_real_point3d;
static bool (*const bf9c40_cf8720)(int projectile_handle, float *new_pos, int16_t *collision_result) = FUN_000f8720;
static void (*const bf9c40_cf90d0)(int projectile_handle, float *hit_pos, float param_3, float *velocity, int16_t *col_result) = FUN_000f90d0;
static void (*const bf9c40_c425c0)(int object_handle, float *position, short effect_type, short volume, short count) = FUN_000425c0;
static int (*const bf9c40_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void *(*const bf9c40_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static float (*const bf9c40_c1c8d10)(int sound_tag_index) = sound_get_default_priority;
static void (*const bf9c40_c10b910)(float *v, float *n, float *proj_out, float *perp_out) = FUN_0010b910;
static float (*const bf9c40_c12170)(float *vector) = FUN_00012170;
static float *(*const bf9c40_vsca)(float *, float *, float, float *) = vector3d_scale_add;
static void (*const bf9c40_usnd)(int, void *, float) = unattached_impulse_sound_new;
static void (*const bf9c40_perp)(float *, float *) = perpendicular3d;
static void (*const bf9c40_otrans)(int, float *, void *) = object_translate;
static void (*const bf9c40_c141b70)(int object_handle) = object_compute_node_matrices;
static void (*const bf9c40_c986d0)(int contrail_handle, bool reset_points, float delta_time) = contrail_set_state_for_object;
static void (*const bf9c40_cf8920)(int projectile_handle, char has_hit_count, float current_time) = FUN_000f8920;
static void (*const bf9c40_odel)(int) = object_delete;
static bool (*const bf9c40_c84a70)(float *a, float *b) = valid_real_normal3d_perpendicular;
static void (*const bf9c40_pexit)(void *) = profile_exit_private;

__attribute__((naked, noinline))
int FUN_000f9c40(int projectile_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x164, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x20\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x70726f6a\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x449ef1, %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl %%esi, -0x24(%%ebp)\n\t"
      "movl $0x3f800000, -0x18(%%ebp)\n\t"
      "movl $0, -0x34(%%ebp)\n\t"
      "movb $0, -0x1d(%%ebp)\n\t"
      "je .LFUN_000f9c40_1\n\t"
      "movb 0x31edb0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f9c40_1\n\t"
      "pushl $0x31eda8\n\t"
      "call *%[penter]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000f9c40_1:\n\t"
      "movb 0x1dc(%%ebx), %%al\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "testb $2, %%al\n\t"
      "jne .LFUN_000f9c40_3\n\t"
      "movl 0x1ec(%%ebx), %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .LFUN_000f9c40_3\n\t"
      "movl 0xfc(%%ebx,%%eax,4), %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .LFUN_000f9c40_2\n\t"
      "pushl %%eax\n\t"
      "call *%[c978f0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000f9c40_2:\n\t"
      "movl 0x1ec(%%ebx), %%edx\n\t"
      "movl %%edi, 0xfc(%%ebx,%%edx,4)\n\t"
      "movl %%edi, 0x1ec(%%ebx)\n\t"
      ".LFUN_000f9c40_3:\n\t"
      "flds 0x1fc(%%ebx)\n\t"
      "fadds 0x1f8(%%ebx)\n\t"
      "fstps 0x1f8(%%ebx)\n\t"
      "flds 0x208(%%ebx)\n\t"
      "fadds 0x204(%%ebx)\n\t"
      "fstps 0x204(%%ebx)\n\t"
      "movswl 0x180(%%esi), %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000f9c40_4\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000f9c40_4\n\t"
      "movb $1, %%cl\n\t"
      "jmp .LFUN_000f9c40_5\n\t"
      ".LFUN_000f9c40_4:\n\t"
      "movl 0x1dc(%%ebx), %%ecx\n\t"
      "shrl $4, %%ecx\n\t"
      "andb $1, %%cl\n\t"
      ".LFUN_000f9c40_5:\n\t"
      "movl 0x1dc(%%ebx), %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "andl $0x20, %%edx\n\t"
      "jne .LFUN_000f9c40_6\n\t"
      "testb $8, %%al\n\t"
      "jne .LFUN_000f9c40_6\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_000f9c40_8\n\t"
      ".LFUN_000f9c40_6:\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .LFUN_000f9c40_7\n\t"
      "orl $0x20, %%eax\n\t"
      "movl %%eax, 0x1dc(%%ebx)\n\t"
      ".LFUN_000f9c40_7:\n\t"
      "flds 0x1f4(%%ebx)\n\t"
      "fadds 0x1f0(%%ebx)\n\t"
      "fsts 0x1f0(%%ebx)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000f9c40_8\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x20\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $1, 0x1e0(%%eax)\n\t"
      "jge .LFUN_000f9c40_8\n\t"
      "movw $1, 0x1e0(%%eax)\n\t"
      ".LFUN_000f9c40_8:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cf7ec0]\n\t"
      "addl $4, %%esp\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000f9c40_9:\n\t"
      "movw 0x1e0(%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_000f9c40_10\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .LFUN_000f9c40_50\n\t"
      "flds 0x1fc(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000f9c40_50\n\t"
      "flds 0x1f8(%%ebx)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000f9c40_50\n\t"
      ".LFUN_000f9c40_10:\n\t"
      "testb $8, 0x1dc(%%ebx)\n\t"
      "jne .LFUN_000f9c40_50\n\t"
      "testb $0x20, 0x4(%%ebx)\n\t"
      "jne .LFUN_000f9c40_50\n\t"
      "cmpl $-1, 0xcc(%%ebx)\n\t"
      "jne .LFUN_000f9c40_50\n\t"
      "flds 0x20(%%ebx)\n\t"
      "leal 0x18(%%ebx), %%esi\n\t"
      "flds 0x4(%%esi)\n\t"
      "movl %%esi, %%edx\n\t"
      "flds (%%esi)\n\t"
      "movl (%%edx), %%eax\n\t"
      "fld %%st(0)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "fld %%st(2)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%esi, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "faddp %%st(1)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "fld %%st(3)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x50(%%ebp)\n\t"
      "movl 0x1e4(%%ebx), %%ecx\n\t"
      "faddp %%st(1)\n\t"
      "pushl %%esi\n\t"
      "movb $0, -0x11(%%ebp)\n\t"
      "movl %%edx, -0x4c(%%ebp)\n\t"
      "fsqrt\n\t"
      "movl %%eax, -0x48(%%ebp)\n\t"
      "movl %%ecx, -0x8c(%%ebp)\n\t"
      "fsts -0x1c(%%ebp)\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fsts -0x2c(%%ebp)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f9c40_11\n\t"
      "flds 0x20(%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0x146\n\t"
      "pushl $0x28ab3c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x28abe4\n\t"
      "pushl $0x26ae40\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f9c40_11:\n\t"
      "movl 0x1e8(%%ebx), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "movl -0x24(%%ebp), %%edi\n\t"
      "je .LFUN_000f9c40_17\n\t"
      "flds 0x1ec(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f9c40_17\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "flds 0x1ec(%%edi)\n\t"
      "movb 0x64(%%eax), %%cl\n\t"
      "fmuls 0x2546a4\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "testb $3, %%dl\n\t"
      "je .LFUN_000f9c40_12\n\t"
      "movl 0x1e8(%%ebx), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0x1c8(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_000f9c40_12\n\t"
      "pushl $0x13\n\t"
      "call *%[cb5590]\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "fstps -0x30(%%ebp)\n\t"
      ".LFUN_000f9c40_12:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "leal 0x50(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $0x50, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1ad60]\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fcomps 0x253f34\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f9c40_13\n\t"
      "movl $0x3f800000, -0x28(%%ebp)\n\t"
      "jmp .LFUN_000f9c40_15\n\t"
      ".LFUN_000f9c40_13:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x253f40\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f9c40_14\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fsubs 0x253f40\n\t"
      "fmuls 0x268ed0\n\t"
      "fsts -0x28(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_000f9c40_14\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f9c40_15\n\t"
      "movl $0x3f800000, -0x28(%%ebp)\n\t"
      "jmp .LFUN_000f9c40_15\n\t"
      ".LFUN_000f9c40_14:\n\t"
      "movl $0, -0x28(%%ebp)\n\t"
      ".LFUN_000f9c40_15:\n\t"
      "movl 0x1e8(%%ebx), %%ecx\n\t"
      "leal -0x6c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1a9520]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "sarl $0x10, %%edi\n\t"
      "call *%[gtime]\n\t"
      "movl %%edi, %%edx\n\t"
      "imull $7, %%edx, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "andl $0xffff, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "fmuls 0x26f2e0\n\t"
      "fstps (%%esp)\n\t"
      "pushl $0xa\n\t"
      "call *%[c10a5e0]\n\t"
      "fmuls 0x255a54\n\t"
      "fstps -0x88(%%ebp)\n\t"
      "call *%[gtime]\n\t"
      "leal (%%edi,%%edi,2), %%ecx\n\t"
      "addl %%ecx, %%eax\n\t"
      "andl $0xffff, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "fmuls 0x26f2e0\n\t"
      "fstps (%%esp)\n\t"
      "pushl $0xa\n\t"
      "call *%[c10a5e0]\n\t"
      "fmuls 0x2568bc\n\t"
      "movl -0x88(%%ebp), %%edx\n\t"
      "leal -0x94(%%ebp), %%eax\n\t"
      "fsubrs 0x256980\n\t"
      "pushl %%eax\n\t"
      "leal -0xb8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x90(%%ebp)\n\t"
      "movl %%edx, -0x94(%%ebp)\n\t"
      "call *%[c10cc40]\n\t"
      "flds -0xb8(%%ebp)\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      "leal -0xfc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x84(%%ebp), %%eax\n\t"
      "fadds -0x6c(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "fstps -0x6c(%%ebp)\n\t"
      "flds -0xb4(%%ebp)\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      "fadds -0x68(%%ebp)\n\t"
      "fstps -0x68(%%ebp)\n\t"
      "flds -0xb0(%%ebp)\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      "fadds -0x64(%%ebp)\n\t"
      "fstps -0x64(%%ebp)\n\t"
      "flds -0x6c(%%ebp)\n\t"
      "fsubs 0xc(%%ebx)\n\t"
      "fstps -0x84(%%ebp)\n\t"
      "flds -0x68(%%ebp)\n\t"
      "fsubs 0x10(%%ebx)\n\t"
      "fstps -0x80(%%ebp)\n\t"
      "flds -0x64(%%ebp)\n\t"
      "fsubs 0x14(%%ebx)\n\t"
      "fstps -0x7c(%%ebp)\n\t"
      "call *%[cross]\n\t"
      "flds -0x7c(%%ebp)\n\t"
      "addl $0x1c, %%esp\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "flds -0x80(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x84(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "faddp %%st(1)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f9c40_16\n\t"
      "leal -0xfc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f9c40_16\n\t"
      "flds -0x30(%%ebp)\n\t"
      "subl $8, %%esp\n\t"
      "fcos\n\t"
      "leal -0xfc(%%ebp), %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fsin\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[rots]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_000f9c40_16:\n\t"
      "movl -0x24(%%ebp), %%edi\n\t"
      ".LFUN_000f9c40_17:\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f9c40_18\n\t"
      "pushl $1\n\t"
      "pushl $0x19d\n\t"
      "pushl $0x28ab3c\n\t"
      "pushl $0x28acec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f9c40_18:\n\t"
      "flds 0x204(%%ebx)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000f9c40_23\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fcomps 0x1e8(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f9c40_20\n\t"
      "flds 0x20c(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000f9c40_20\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x20c(%%ebx)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fsts -0x2c(%%ebp)\n\t"
      "fcomps 0x1e8(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000f9c40_19\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fsubs 0x1e8(%%edi)\n\t"
      ".byte 0xde, 0xf1\n\t"
      "flds 0x1e8(%%edi)\n\t"
      "fmuls 0x28ace8\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fmuls 0x253398\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x1e8(%%edi)\n\t"
      "faddp %%st(1)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fdivs -0x1c(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fadds (%%esi)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fmuls 0x253398\n\t"
      "fld %%st(1)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fadds 0x1c(%%ebx)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fmuls 0x253398\n\t"
      "fld %%st(1)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fadds 0x20(%%ebx)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fmuls 0x253398\n\t"
      "fxch %%st(1)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "jmp .LFUN_000f9c40_23\n\t"
      ".LFUN_000f9c40_19:\n\t"
      "fmuls 0x253398\n\t"
      "fsubrs -0x1c(%%ebp)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fdivs -0x1c(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fadds (%%esi)\n\t"
      "fmuls 0x253398\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fadds 0x1c(%%ebx)\n\t"
      "fmuls 0x253398\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fadds 0x20(%%ebx)\n\t"
      "fmuls 0x253398\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "jmp .LFUN_000f9c40_23\n\t"
      ".LFUN_000f9c40_20:\n\t"
      "flds 0x1c8(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000f9c40_22\n\t"
      "flds 0x1c0(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000f9c40_22\n\t"
      "flds 0x1c4(%%edi)\n\t"
      "fcomps 0x1e8(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_000f9c40_22\n\t"
      "flds 0x20c(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000f9c40_21\n\t"
      "flds 0x200(%%ebx)\n\t"
      "fcomps 0x210(%%ebx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000f9c40_22\n\t"
      ".LFUN_000f9c40_21:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl $2, %%esi\n\t"
      "call *%[cf7e40]\n\t"
      "jmp .LFUN_000f9c40_23\n\t"
      ".LFUN_000f9c40_22:\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fcomps 0x1e8(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000f9c40_23\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f9c40_23\n\t"
      "flds 0x1e8(%%edi)\n\t"
      "fdivs -0x1c(%%ebp)\n\t"
      "fmuls 0x28ace8\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".LFUN_000f9c40_23:\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl $1, %%esi\n\t"
      "jne .LFUN_000f9c40_24\n\t"
      "pushl %%esi\n\t"
      "pushl $0x1cd\n\t"
      "pushl $0x28ab3c\n\t"
      "pushl $0x28acb8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f9c40_24:\n\t"
      "movb 0x4(%%ebx), %%al\n\t"
      "flds 0x32512c\n\t"
      "testb $0x10, %%al\n\t"
      "je .LFUN_000f9c40_25\n\t"
      "fmuls 0x1d8(%%edi)\n\t"
      "jmp .LFUN_000f9c40_26\n\t"
      ".LFUN_000f9c40_25:\n\t"
      "fmuls 0x1cc(%%edi)\n\t"
      ".LFUN_000f9c40_26:\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "flds -0x4(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fsubrs -0x48(%%ebp)\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f9c40_27\n\t"
      "pushl %%esi\n\t"
      "pushl $0x1dc\n\t"
      "pushl $0x28ab3c\n\t"
      "pushl $0x28ac8c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f9c40_27:\n\t"
      "flds 0x1c8(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000f9c40_30\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "fadds 0x200(%%ebx)\n\t"
      "fcomps 0x1c8(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f9c40_30\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000f9c40_28\n\t"
      "flds 0x1c8(%%edi)\n\t"
      "fsubs 0x200(%%ebx)\n\t"
      "fdivs -0x38(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "jmp .LFUN_000f9c40_29\n\t"
      ".LFUN_000f9c40_28:\n\t"
      "movl $0, -0x60(%%ebp)\n\t"
      ".LFUN_000f9c40_29:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0x20\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%si, 0x1e0(%%eax)\n\t"
      "jge .LFUN_000f9c40_31\n\t"
      "movw %%si, 0x1e0(%%eax)\n\t"
      "jmp .LFUN_000f9c40_31\n\t"
      ".LFUN_000f9c40_30:\n\t"
      "movl $0x3f800000, -0x60(%%ebp)\n\t"
      ".LFUN_000f9c40_31:\n\t"
      "flds -0x60(%%ebp)\n\t"
      "leal -0x5c(%%ebp), %%edx\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0xc(%%ebx)\n\t"
      "fstps -0x5c(%%ebp)\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x10(%%ebx)\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "fmuls -0x48(%%ebp)\n\t"
      "fadds 0x14(%%ebx)\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "call *%[ca16b0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f9c40_32\n\t"
      "flds -0x54(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "pushl $0x1f9\n\t"
      "pushl $0x28ab3c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x28ac7c\n\t"
      "pushl $0x26ae04\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f9c40_32:\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "jl .LFUN_000f9c40_33\n\t"
      "pushl %%esi\n\t"
      "pushl $0x1fb\n\t"
      "pushl $0x28ab3c\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f9c40_33:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "incw %%ax\n\t"
      "cmpw $0xa, -0x34(%%ebp)\n\t"
      "movw $0xe, 0x5a8c80(,%%ecx,2)\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "je .LFUN_000f9c40_37\n\t"
      "cmpw $2, 0x1e0(%%ebx)\n\t"
      "je .LFUN_000f9c40_38\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal -0x164(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x5c(%%ebp), %%edi\n\t"
      "movb $1, -0x11(%%ebp)\n\t"
      "call *%[cf8720]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f9c40_38\n\t"
      "flds 0x2533c8\n\t"
      "fsubs -0x150(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000f9c40_35\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x20c(%%ebx)\n\t"
      "fadds -0x2c(%%ebp)\n\t"
      "fcoms -0x1c(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f9c40_34\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      ".LFUN_000f9c40_34:\n\t"
      "fdivs -0x2c(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".LFUN_000f9c40_35:\n\t"
      "flds -0x138(%%ebp)\n\t"
      "fcomps 0x2533e4\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f9c40_36\n\t"
      "orl $4, 0x1dc(%%ebx)\n\t"
      ".LFUN_000f9c40_36:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%eax\n\t"
      "leal -0x5c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "leal -0x164(%%ebp), %%esi\n\t"
      "movl $0xffffffff, 0x1e4(%%ebx)\n\t"
      "call *%[cf90d0]\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "movl -0x34(%%ebp), %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x182(%%edx), %%ax\n\t"
      "pushl $1\n\t"
      "leal -0x14c(%%ebp), %%ecx\n\t"
      "incl %%esi\n\t"
      "movl %%esi, -0x34(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c425c0]\n\t"
      "movb 0x1dc(%%ebx), %%al\n\t"
      "addl $0x20, %%esp\n\t"
      "testb $8, %%al\n\t"
      "je .LFUN_000f9c40_39\n\t"
      "movb $0, -0x11(%%ebp)\n\t"
      "jmp .LFUN_000f9c40_39\n\t"
      ".LFUN_000f9c40_37:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $0x20\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%si, 0x1e0(%%eax)\n\t"
      "jge .LFUN_000f9c40_38\n\t"
      "movw $1, 0x1e0(%%eax)\n\t"
      ".LFUN_000f9c40_38:\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      ".LFUN_000f9c40_39:\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "jg .LFUN_000f9c40_40\n\t"
      "pushl $1\n\t"
      "pushl $0x230\n\t"
      "pushl $0x28ab3c\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f9c40_40:\n\t"
      "movb -0x11(%%ebp), %%al\n\t"
      "decw 0x4761d8\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f9c40_48\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "movb -0x1d(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "fsubs 0xc(%%ebx)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fsubs 0x10(%%ebx)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fsubs 0x14(%%ebx)\n\t"
      "fsts -0x3c(%%ebp)\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls -0x40(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fmuls -0x44(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fsqrt\n\t"
      "fadds 0x200(%%ebx)\n\t"
      "fstps 0x200(%%ebx)\n\t"
      "jne .LFUN_000f9c40_43\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "cmpl $-1, 0x210(%%eax)\n\t"
      "je .LFUN_000f9c40_43\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_000f9c40_41:\n\t"
      "pushl %%edi\n\t"
      "call *%[cba3c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000f9c40_42\n\t"
      "pushl %%edi\n\t"
      "call *%[cba3c0]\n\t"
      "movl 0x5aa6d4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000f9c40_42\n\t"
      "cmpl -0x8c(%%ebp), %%eax\n\t"
      "je .LFUN_000f9c40_42\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x210(%%edx), %%eax\n\t"
      "pushl %%eax\n\t"
      "addl $0x50, %%esi\n\t"
      "call *%[c1c8d10]\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds (%%esi)\n\t"
      "leal -0xc4(%%ebp), %%ecx\n\t"
      "fsubs 0xc(%%ebx)\n\t"
      "pushl %%ecx\n\t"
      "leal -0xa0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fstps -0xac(%%ebp)\n\t"
      "leal -0x44(%%ebp), %%eax\n\t"
      "flds 0x4(%%esi)\n\t"
      "pushl %%eax\n\t"
      "fsubs 0x10(%%ebx)\n\t"
      "leal -0xac(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstps -0xa8(%%ebp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0x14(%%ebx)\n\t"
      "fstps -0xa4(%%ebp)\n\t"
      "call *%[c10b910]\n\t"
      "flds -0x98(%%ebp)\n\t"
      "addl $0x1c, %%esp\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      "flds -0x9c(%%ebp)\n\t"
      "fmuls -0x40(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "flds -0xa0(%%ebp)\n\t"
      "fmuls -0x44(%%ebp)\n\t"
      "faddp %%st(1)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_000f9c40_42\n\t"
      "leal -0x44(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c12170]\n\t"
      "fcomps -0x4(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f9c40_42\n\t"
      "leal -0xc4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c12170]\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f9c40_42\n\t"
      "leal -0xf0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xbf800000\n\t"
      "leal -0xc4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[vsca]\n\t"
      "movl -0x44(%%ebp), %%eax\n\t"
      "movl -0x40(%%ebp), %%ecx\n\t"
      "movl -0x3c(%%ebp), %%edx\n\t"
      "movl %%eax, -0xe4(%%ebp)\n\t"
      "leal -0xe4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0xe0(%%ebp)\n\t"
      "movl %%edx, -0xdc(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "movl 0x31fc38, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0xd8(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl -0x158(%%ebp), %%edx\n\t"
      "movl %%eax, -0xd4(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl -0x154(%%ebp), %%eax\n\t"
      "movl %%ecx, -0xd0(%%ebp)\n\t"
      "movl %%edx, -0xcc(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "pushl $0x3f800000\n\t"
      "leal -0xf0(%%ebp), %%ecx\n\t"
      "movl %%eax, -0xc8(%%ebp)\n\t"
      "movl 0x210(%%edx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[usnd]\n\t"
      "addl $0x20, %%esp\n\t"
      "movb $1, -0x1d(%%ebp)\n\t"
      ".LFUN_000f9c40_42:\n\t"
      "incl %%edi\n\t"
      "cmpw $4, %%di\n\t"
      "jl .LFUN_000f9c40_41\n\t"
      ".LFUN_000f9c40_43:\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "testb $1, 0x17c(%%ecx)\n\t"
      "je .LFUN_000f9c40_46\n\t"
      "flds 0x18(%%ebx)\n\t"
      "leal 0x18(%%ebx), %%ecx\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000f9c40_44\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000f9c40_44\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000f9c40_46\n\t"
      ".LFUN_000f9c40_44:\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x78(%%ebp)\n\t"
      "leal -0x78(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x74(%%ebp)\n\t"
      "movl %%ecx, -0x70(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000f9c40_45\n\t"
      "movl -0x78(%%ebp), %%ecx\n\t"
      "movl -0x74(%%ebp), %%edx\n\t"
      "leal 0x24(%%ebx), %%esi\n\t"
      "movl %%esi, %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x70(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "leal -0x114(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x30(%%ebx), %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "call *%[cross]\n\t"
      "pushl %%edi\n\t"
      "leal -0x114(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[cross]\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0x1c, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000f9c40_45\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[perp]\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000f9c40_45:\n\t"
      "movl 0x224(%%ebx), %%ecx\n\t"
      "movl 0x220(%%ebx), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal 0x24(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x30(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[rots]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_000f9c40_47\n\t"
      ".LFUN_000f9c40_46:\n\t"
      "testb $1, 0x1dc(%%ebx)\n\t"
      "je .LFUN_000f9c40_47\n\t"
      "movl 0x224(%%ebx), %%edx\n\t"
      "movl 0x220(%%ebx), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x214(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x24(%%ebx), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[rots]\n\t"
      "movl 0x224(%%ebx), %%edx\n\t"
      "movl 0x220(%%ebx), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x214(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x30(%%ebx), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[rots]\n\t"
      "pushl %%esi\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "leal -0x108(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[cross]\n\t"
      "pushl %%edi\n\t"
      "leal -0x108(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[cross]\n\t"
      "pushl %%edi\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $0x40, %%esp\n\t"
      ".LFUN_000f9c40_47:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "leal -0x158(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x5c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[otrans]\n\t"
      "flds -0x18(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "fcomps 0x2533c0\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "leal 0x18(%%ebx), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "fnstsw %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000f9c40_48\n\t"
      "cmpw $0, -0x34(%%ebp)\n\t"
      "je .LFUN_000f9c40_48\n\t"
      "movl 0x1ec(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000f9c40_48\n\t"
      "cmpl $-1, 0xfc(%%ebx,%%eax,4)\n\t"
      "je .LFUN_000f9c40_48\n\t"
      "pushl %%esi\n\t"
      "call *%[c141b70]\n\t"
      "flds 0x2533c8\n\t"
      "fsubs -0x18(%%ebp)\n\t"
      "movl 0x1ec(%%ebx), %%eax\n\t"
      "movl 0xfc(%%ebx,%%eax,4), %%ecx\n\t"
      "fmuls 0x28ab38\n\t"
      "fstps (%%esp)\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c986d0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000f9c40_48:\n\t"
      "leal 0x18(%%ebx), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f9c40_49\n\t"
      "flds 0x20(%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0x2a0\n\t"
      "pushl $0x28ab3c\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x28abe4\n\t"
      "pushl $0x26ae40\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f9c40_49:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_000f9c40_9\n\t"
      ".LFUN_000f9c40_50:\n\t"
      "movswl 0x1e0(%%ebx), %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000f9c40_51\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000f9c40_53\n\t"
      "jmp .LFUN_000f9c40_54\n\t"
      ".LFUN_000f9c40_51:\n\t"
      "flds 0x1fc(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000f9c40_52\n\t"
      "flds 0x1f8(%%ebx)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_000f9c40_54\n\t"
      ".LFUN_000f9c40_52:\n\t"
      "cmpw $0, -0x34(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "sete %%al\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[cf8920]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_000f9c40_53:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[odel]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000f9c40_54:\n\t"
      "leal 0x30(%%ebx), %%esi\n\t"
      "leal 0x24(%%ebx), %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c84a70]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000f9c40_55\n\t"
      "flds 0x38(%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0x2b0\n\t"
      "pushl $0x28ab3c\n\t"
      "subl $0x30, %%esp\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x34(%%ebx)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x2c(%%ebx)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x28(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x28ac64\n\t"
      "pushl $0x28ac48\n\t"
      "pushl $0x267490\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x40, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000f9c40_55:\n\t"
      "movb 0x449ef1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_000f9c40_56\n\t"
      "movb 0x31edb0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000f9c40_56\n\t"
      "pushl $0x31eda8\n\t"
      "call *%[pexit]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000f9c40_56:\n\t"
      "movb $1, %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(bf9c40_get), [tag] "m"(bf9c40_tag), [penter] "m"(bf9c40_penter), [c978f0] "m"(bf9c40_c978f0), [cf7ec0] "m"(bf9c40_cf7ec0), [c84a10] "m"(bf9c40_c84a10), [c8d9d0] "m"(bf9c40_c8d9d0), [assert] "m"(bf9c40_assert), [exitfn] "m"(bf9c40_exitfn), [cb5590] "m"(bf9c40_cb5590), [c1ad60] "m"(bf9c40_c1ad60), [c1a9520] "m"(bf9c40_c1a9520), [gtime] "m"(bf9c40_gtime), [c10a5e0] "m"(bf9c40_c10a5e0), [c10cc40] "m"(bf9c40_c10cc40), [cross] "m"(bf9c40_cross), [norm] "m"(bf9c40_norm), [rots] "m"(bf9c40_rots), [cf7e40] "m"(bf9c40_cf7e40), [ca16b0] "m"(bf9c40_ca16b0), [cf8720] "m"(bf9c40_cf8720), [cf90d0] "m"(bf9c40_cf90d0), [c425c0] "m"(bf9c40_c425c0), [cba3c0] "m"(bf9c40_cba3c0), [dget] "m"(bf9c40_dget), [c1c8d10] "m"(bf9c40_c1c8d10), [c10b910] "m"(bf9c40_c10b910), [c12170] "m"(bf9c40_c12170), [vsca] "m"(bf9c40_vsca), [usnd] "m"(bf9c40_usnd), [perp] "m"(bf9c40_perp), [otrans] "m"(bf9c40_otrans), [c141b70] "m"(bf9c40_c141b70), [c986d0] "m"(bf9c40_c986d0), [cf8920] "m"(bf9c40_cf8920), [odel] "m"(bf9c40_odel), [c84a70] "m"(bf9c40_c84a70), [pexit] "m"(bf9c40_pexit)
      : "memory");
}
#else
#error "FUN_000f9c40: clang naked draft required"
#endif


/* FUN_000fac20 (0xfac20) — XBE naked draft (batch 64). */
#if defined(__clang__)
static void *(*const bfac20_tag)(int, int) = tag_get;
static void *(*const bfac20_elem)(void *, int, int) = tag_block_get_element;

__attribute__((naked, noinline))
float FUN_000fac20(int weapon_tag_index __attribute__((unused)), float *out_field8 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x77656170\n\t"
      "call *%[tag]\n\t"
      "pushl $0x114\n\t"
      "addl $0x4fc, %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "je .LFUN_000fac20_1\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      ".LFUN_000fac20_1:\n\t"
      "movl 0xa0(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "pushl %%esi\n\t"
      "je .LFUN_000fac20_3\n\t"
      "pushl %%eax\n\t"
      "pushl $0x70726f6a\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x230(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000fac20_2\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6a707421\n\t"
      "call *%[tag]\n\t"
      "flds 0x1d8(%%eax)\n\t"
      "fadds 0x1d4(%%eax)\n\t"
      "addl $8, %%esp\n\t"
      "fmuls 0x253398\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".LFUN_000fac20_2:\n\t"
      "movl 0x220(%%esi), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_000fac20_3\n\t"
      "pushl %%esi\n\t"
      "pushl $0x6a707421\n\t"
      "call *%[tag]\n\t"
      "flds 0x1d8(%%eax)\n\t"
      "fadds 0x1d4(%%eax)\n\t"
      "addl $8, %%esp\n\t"
      "popl %%esi\n\t"
      "fmuls 0x253398\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000fac20_3:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(bfac20_tag), [elem] "m"(bfac20_elem)
      : "memory");
}
#else
#error "FUN_000fac20: clang naked draft required"
#endif


/*
 * Wrapper: advance animation state by one frame (update_kind=1) for the
 * given animation graph tag and animation state pointer. Thin wrapper around
 * animation_update_internal with a fixed update_kind of 1.
 * No known direct call-graph callers (likely dispatched via function pointer
 * or animation callback table).
 */
void FUN_000face0(int animation_graph_tag_index, short *state, int *out_sound)
{
  animation_update_internal(1, animation_graph_tag_index, state, out_sound);
}

/* FUN_000fad00 (0xfad00) — readable C lift from XBE leaf. */
int16_t FUN_000fad00(int animation_graph_tag_index, int16_t animation_index)
{
  return (int16_t)model_animation_choose_random(1, animation_graph_tag_index, animation_index);
}

