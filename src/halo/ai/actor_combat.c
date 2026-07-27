#include "x87_math.h"

/* 0x20f80 — Check whether an actor meets conditions for a given combat mode.
 * mode 1: actor.field_60c==1 and field_268>=8
 * mode 2: actor.field_60c==0, field_268>=5, field_27c!=0, field_278>=0x4b
 * mode 3: mode 1 conditions plus field_161!=0 */
int actor_combat_check_mode(int actor_handle /* @<eax> */, short mode)
{
  char *actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);

  switch (mode) {
  case 1:
    if (*(short *)(actor + 0x60c) == 1 && *(short *)(actor + 0x268) >= 8)
      return 1;
    break;
  case 2:
    if (*(short *)(actor + 0x60c) == 0 && *(short *)(actor + 0x268) >= 5 &&
        *(char *)(actor + 0x27c) != 0 && *(int *)(actor + 0x278) >= 0x4b)
      return 1;
    break;
  case 3:
    if (*(short *)(actor + 0x60c) == 1 && *(short *)(actor + 0x268) >= 8 &&
        *(char *)(actor + 0x161) != 0)
      return 1;
    break;
  }
  return 0;
}

/* 0x21010 — Begin a fixed-duration ("type 4") firing state for an actor.
 * Sets the fire_state enum (actor+0x5f2) to 4 and stores the supplied
 * duration in ticks (actor+0x5f4). cdecl: actor_handle in arg1 (EDI at the
 * call site), ticks is the truncated float result the caller pushes (arg2).
 * The field at +0x5f4 is a short, so the duration is narrowed. */
void FUN_00021010(int actor_handle, int ticks)
{
  char *actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);

  *(short *)(actor + 0x5f2) = 4;
  *(short *)(actor + 0x5f4) = (short)ticks;
}

/* 0x21040 — Raise an actor's "hold burst" timer (actor+0x5f6) to at least
 * the requested number of ticks: field_5f6 = max(field_5f6, ticks).
 * The original compares the requested value against the current short and,
 * when the request is smaller, leaves the field unchanged (a no-op
 * self-assignment in the original codegen); otherwise it stores the new
 * value (narrowed to short). */
void FUN_00021040(int actor_handle, int ticks)
{
  char *actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);

  if (ticks < *(short *)(actor + 0x5f6))
    *(short *)(actor + 0x5f6) = *(short *)(actor + 0x5f6);
  else
    *(short *)(actor + 0x5f6) = (short)ticks;
}

/* 0x21130 — Get the weapon/aim direction for an actor.
 * If the actor is in a vehicle with flag 0x100 set in the vehicle tag,
 * copies the vehicle's position (offset 0x24). Otherwise falls back to
 * unit aiming functions. */
void actor_combat_get_weapon_vector(int actor_handle /* @<eax> */,
                                    float *weapon_vector /* @<ebx> */)
{
  char *actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  int handle = *(int *)(actor + 0x18);

  assert_halt(weapon_vector != NULL);

  if (*(char *)(actor + 0x161) != 0) {
    int *vehicle_obj =
      (int *)object_get_and_verify_type(*(int *)(actor + 0x158), 2);
    char *vehi_tag = (char *)tag_get(0x76656869, *vehicle_obj);
    handle = *(int *)(actor + 0x158);
    if ((*(unsigned int *)(vehi_tag + 0x2f0) & 0x100) != 0) {
      weapon_vector[0] = *(float *)((char *)vehicle_obj + 0x24);
      weapon_vector[1] = *(float *)((char *)vehicle_obj + 0x28);
      weapon_vector[2] = *(float *)((char *)vehicle_obj + 0x2c);
      return;
    }
  }

  object_get_and_verify_type(handle, 3);
  unit_scripting_unit_driver(handle, weapon_vector);
  unit_clip_to_aiming_bounds(handle, weapon_vector, 1);
}

char *actor_combat_get_firing_variant_definition(int actor_handle)
{
  char *actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  char *actv = (char *)tag_get(0x61637476, *(int *)(actor + 0x5c));
  int weapon_handle = actor_attacking_target(actor_handle);
  if (weapon_handle != -1) {
    int *obj = (int *)object_get_and_verify_type(weapon_handle, 4);
    char *weap = (char *)tag_get(0x77656170, *obj);
    if (weap != 0 && *(int *)(weap + 0x3c8) != -1) {
      actv = (char *)tag_get(0x61637476, *(int *)(weap + 0x3c8));
    }
  }
  return actv;
}

/* 0x21270 — Look up burst and firing rate parameters from the actv tag.
 * Selects firing modifier based on actor state flags (field_378/600/601). */
void actor_combat_get_burst_parameters(int actor_handle /* @<eax> */,
                                       void *actv /* @<ecx> */,
                                       void **burst_ref, void **firing_ref)
{
  char *actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  char *tag = (char *)actv;
  void *burst = tag + 0xcc;
  void *firing = NULL;

  if (*(char *)(actor + 0x378) != 0)
    firing = tag + 0x130;
  else if (*(char *)(actor + 0x600) != 0)
    firing = tag + 0x100;
  else if (*(char *)(actor + 0x601) != 0)
    firing = tag + 0x118;

  assert_halt(burst_ref != NULL && firing_ref != NULL);
  *burst_ref = burst;
  *firing_ref = firing;
}

/* 0x21350 — Round a float to the nearest integer using the FPU's current
 * rounding mode (FLD; FISTP). cdecl helper, single float argument, returns
 * the rounded value in EAX. */
int FUN_00021350(float value)
{
  return x87_round_to_int(value);
}

/* 0x21590 — Compute and set the fire delay timer for an actor.
 * Uses burst/firing rate data from the actv tag, random timing,
 * and combat property scaling. Result stored in actor.field_5f4.
 *
 * VC71 72.1% (61/61 insns) is a STRUCTURAL ceiling, not a defect: the @<esi>
 * actor_handle is register-received by the original, but VC71 compiles our
 * annotation as cdecl (adds a [ebp+8] load); burst_ref/firing_ref are
 * address-taken out-params forced onto the stack here while the original keeps
 * them in registers. Residual diffs are FPU store/compare ordering. No recovery
 * lever remains. Verified 2026-06-23 [[project_sub80_vc71_audit_2026-06-23]]. */
void actor_combat_set_fire_timer(int actor_handle /* @<esi> */)
{
  char *actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  void *burst_ref;
  void *firing_ref;
  float random_time;
  float result;

  char *actv = actor_combat_get_firing_variant_definition(actor_handle);
  actor_combat_get_burst_parameters(actor_handle, actv, &burst_ref,
                                    &firing_ref);

  {
    float min_time = *(float *)((char *)burst_ref + 0x1c);
    float max_time = *(float *)((char *)burst_ref + 0x20);
    int *seed = get_global_random_seed_address();
    random_time = random_real_range(seed, min_time, max_time);
  }

  result =
    FUN_000b55b0(0xe, (int)*(unsigned short *)(actor + 0x3e)) * random_time;

  if (firing_ref != NULL) {
    if (*(float *)((char *)firing_ref + 4) != 0.0f)
      result *= *(float *)((char *)firing_ref + 4);
  }

  if (*(char *)(actor + 0x1ca) != 0)
    result *= *(float *)0x254970;

  result *= TICKS_PER_SECOND;
  *(short *)(actor + 0x5f4) = (short)(int)result;
}

/* 0x21640 — Evaluate whether the actor should fire and compute delay.
 * Returns false if prop is in retreat state (field_24==4 or 5)
 * or if actor.field_457 is set. Otherwise computes a random delay
 * from timing_data and returns true.
 *
 * VC71 78.1% (58/70 insns) is a STRUCTURAL ceiling: @<eax>/@<edi> args are
 * register-received by the original (VC71 adds a cdecl [ebp+8] load), and the
 * bool returns compile to branchy movb/xorb here vs the original's `sete %al`.
 * Field offsets (0x3bc/0x457/0x5f4/0x60c) and control flow match exactly — no
 * dropped branch. Verified 2026-06-23 [[project_sub80_vc71_audit_2026-06-23]]. */
bool actor_combat_evaluate_firing(int actor_handle /* @<eax> */,
                                  void *timing_data /* @<edi> */)
{
  char *actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  char flag = *(char *)(actor + 0x457);

  if (*(short *)(actor + 0x60c) == 1) {
    char *prop =
      (char *)datum_get(*(void **)0x5ab23c, *(int *)(actor + 0x610));
    short prop_state = *(short *)(prop + 0x24);
    if (prop_state >= 4 && prop_state <= 5) {
      *(char *)(actor + 0x3bc) = 1;
      *(short *)(actor + 0x5f4) = 0;
      return 0;
    }
  }

  if (flag != 0) {
    *(short *)(actor + 0x5f4) = 0;
    return 0;
  }

  {
    float min_time = *(float *)((char *)timing_data + 0x80);
    float max_time = *(float *)((char *)timing_data + 0x84);
    int *seed = get_global_random_seed_address();
    float delay = random_real_range(seed, min_time, max_time);
    *(short *)(actor + 0x5f4) = (short)(int)(delay * TICKS_PER_SECOND);
  }

  return 1;
}

/* 0x21710 — Compute a ballistic firing solution toward the actor's current
 * impact point and validate the line of fire.
 *
 * Looks up the actor's firing-variant projectile definition (actv tag
 * +0x180 -> globals weapon block element +0x40 -> 'proj' tag), aborts via
 * projectile_aim to get the aim direction, aim speed, target handle and a
 * gating flag. Rejects the shot when the planar aim magnitude is zero or the
 * forward alignment (dir . actor-facing) falls at/below cos(30deg) = 0.866.
 * On success it scales the direction by the aim speed into a desired-impact
 * delta, runs ai_test_ballistic_line_of_fire, and on a positive result caches
 * the aim direction at actor+0x6bc and the aim speed at actor+0x6c8.
 * Returns true when a valid firing solution was produced. */
char actor_combat_compute_ballistic_solution(int actor_handle, int param_2)
{
  int actor;
  int projectile;
  void *variant;
  void *element;
  short defn_index;
  float aim_dir[3];
  float speed;
  float param_3;
  char line_of_fire_flag;
  float ground[3];
  float scaled[3];
  float accel;

  actor = (int)datum_get(*(void **)0x6325a4, actor_handle);
  variant = tag_get(0x61637476, *(int *)(actor + 0x5c));
  defn_index = *(short *)((int)variant + 0x180);
  element = tag_block_get_element((char *)game_globals_get() + 0x128,
                                  defn_index, 0x44);

  projectile = 0;
  if (element != (void *)0 && *(int *)((int)element + 0x40) != -1) {
    projectile = (int)tag_get(0x70726f6a, *(int *)((int)element + 0x40));
  }

  if (projectile == 0) {
    display_assert("projectile_definition",
                   "c:\\halo\\SOURCE\\ai\\actor_combat.c", 0x6c3, 1);
    system_exit(-1);
  }

  if (!projectile_aim(projectile, param_2, actor + 0x6a8, 0, 0, 0,
                      actor + 0x6c8, (int)*(unsigned char *)(actor + 0x6a1),
                      (int)aim_dir, (int)&speed, (int)&param_3, 0,
                      &line_of_fire_flag)) {
    return 0;
  }

  ground[0] = aim_dir[0];
  ground[1] = aim_dir[1];
  /* The original computes magnitude3d over (aim_dir[0], aim_dir[1], aim_speed):
   * it writes only the first two components into the EBP-0x10 buffer and reads
   * the third from EBP-0x8, which projectile_aim already filled with aim_speed
   * (an MSVC stack-overlap). Our clang stack layout does not guarantee that
   * overlap, so write the speed component explicitly. */
  ground[2] = speed;
  if (magnitude3d(ground) <= *(float *)0x2533c0) {
    return 0;
  }

  if (ground[1] * *(float *)(actor + 0x178) +
        ground[0] * *(float *)(actor + 0x174) <= *(float *)0x2533dc) {
    return 0;
  }

  scaled[0] = aim_dir[0] * speed;
  scaled[1] = aim_dir[1] * speed;
  scaled[2] = aim_dir[2] * speed;

  if (line_of_fire_flag != '\0') {
    accel = 0.0f;
  } else {
    accel = projectile_get_ballistic_acceleration(projectile);
  }

  if (!ai_test_ballistic_line_of_fire(actor_handle, param_2, param_3, scaled,
                                      accel, *(int *)(actor + 0x6b8),
                                      (char)(*(int *)(actor + 0x158) != -1))) {
    return 0;
  }

  *(float *)(actor + 0x6bc) = aim_dir[0];
  *(float *)(actor + 0x6c0) = aim_dir[1];
  *(float *)(actor + 0x6c4) = aim_dir[2];
  *(float *)(actor + 0x6c8) = speed;
  return 1;
}

/* 0x219e0 — Find a grenade aim target from the actor's current prop.
 *
 * cdecl: actor_handle (EDI) plus three output pointers. When the actor has a
 * live prop (actor+0x270 != -1) whose datum is active (+0x60 set) and
 * not suppressed (+0x127 clear), and whose type (+0x24) is 2..4, and whose
 * range value (+0x11c) lies within the actv's grenade band
 * (actv+0x194 < range < actv+0x198), it copies the prop's target point
 * (+0xbc/+0xc0/+0xc4) into out_pos with a fixed Z bias (*0x2549d4), reports
 * the prop handle in out_handle and the target prop index (+0x110) in
 * out_extra, and returns 1. If the actor is flagged for aim refinement
 * (actor+0x1ca), it nudges out_pos toward the actor via FUN_00021430 with a
 * 1.5 weight. Returns 0 when no suitable target exists. */
char actor_combat_find_grenade_target(int actor_handle, float *out_pos,
                                       int *out_handle, int *out_extra)
{
  char *actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  char *actv = (char *)tag_get(0x61637476 /* 'actv' */, *(int *)(actor + 0x5c));
  char result = 0;
  char *prop;
  short type;

  if (*(int *)(actor + 0x270) != -1) {
    prop = (char *)datum_get(*(void **)0x5ab23c, *(int *)(actor + 0x270));
    if (*(char *)(prop + 0x60) != 0 && *(char *)(prop + 0x127) == 0) {
      type = *(short *)(prop + 0x24);
      if ((type > 1 && type < 4) || type == 4) {
        if (*(float *)(actv + 0x194) < *(float *)(prop + 0x11c) &&
            *(float *)(prop + 0x11c) < *(float *)(actv + 0x198)) {
          out_pos[0] = *(float *)(prop + 0xbc);
          out_pos[1] = *(float *)(prop + 0xc0);
          out_pos[2] = *(float *)(prop + 0xc4);
          result = 1;
          out_pos[2] = out_pos[2] + *(float *)0x2549d4;
          *out_handle = *(int *)(actor + 0x270);
          *out_extra = *(int *)(prop + 0x110);
          if (*(char *)(actor + 0x1ca) != 0)
            FUN_00021430(out_pos, 1.5f);
        }
      }
    }
  }
  return result;
}

/* FUN_00021ae0 (0x21ae0) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b21ae0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b21ae0_tag)(int, int) = tag_get;
static void (*const b21ae0_c64540)(int *out, int actor_handle) = FUN_00064540;
static int (*const b21ae0_c64570)(int *iter) = FUN_00064570;
static void (*const b21ae0_c59a00)(int *iter, int clump_handle) = encounter_actor_iterator_new;
static int (*const b21ae0_c59a50)(int *iter) = encounter_actor_iterator_next;

__attribute__((naked, noinline))
char FUN_00021ae0(int actor_handle __attribute__((unused)), float range __attribute__((unused)), float param3 __attribute__((unused)), float *encounter_pos __attribute__((unused)), short *out_count __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x98, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x5c(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637476\n\t"
      "movl %%ebx, -0x18(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl %%edx\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "call *%[c64540]\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c64570]\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $0x1c, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00021ae0_9\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00021ae0_1:\n\t"
      "movw 0x24(%%ecx), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .LFUN_00021ae0_7\n\t"
      "cmpw $3, %%ax\n\t"
      "jg .LFUN_00021ae0_7\n\t"
      "movb 0x127(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00021ae0_7\n\t"
      "movb 0x60(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00021ae0_6\n\t"
      "flds (%%esi)\n\t"
      "fsubs 0xbc(%%ecx)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0xc0(%%ecx)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0xc4(%%ecx)\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fcompp\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jne .LFUN_00021ae0_7\n\t"
      "movb 0x12e(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00021ae0_2\n\t"
      "addl $0xa, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00021ae0_7\n\t"
      ".LFUN_00021ae0_2:\n\t"
      "cmpl $-1, 0x110(%%ecx)\n\t"
      "je .LFUN_00021ae0_3\n\t"
      "addl $5, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00021ae0_7\n\t"
      ".LFUN_00021ae0_3:\n\t"
      "movl 0x1c(%%ecx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00021ae0_7\n\t"
      "cmpw $0x20, %%di\n\t"
      "jae .LFUN_00021ae0_4\n\t"
      "movswl %%di, %%edx\n\t"
      "movl %%eax, -0x98(%%ebp,%%edx,4)\n\t"
      "incl %%edi\n\t"
      ".LFUN_00021ae0_4:\n\t"
      "movb 0x14(%%ecx), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00021ae0_5\n\t"
      "pushl %%eax\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movw 0x1e(%%eax), %%cx\n\t"
      "addl $8, %%esp\n\t"
      "addw %%cx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00021ae0_7\n\t"
      ".LFUN_00021ae0_5:\n\t"
      "incl -0x8(%%ebp)\n\t"
      "jmp .LFUN_00021ae0_7\n\t"
      ".LFUN_00021ae0_6:\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00021ae0_7\n\t"
      "flds (%%esi)\n\t"
      "fsubs 0xbc(%%ecx)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0xc0(%%ecx)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0xc4(%%ecx)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fmuls 0x10(%%ebp)\n\t"
      "fcompp\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "je .LFUN_00021ae0_8\n\t"
      ".LFUN_00021ae0_7:\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c64570]\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_00021ae0_1\n\t"
      "jmp .LFUN_00021ae0_9\n\t"
      ".LFUN_00021ae0_8:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_00021ae0_9:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00021ae0_15\n\t"
      "movl 0x270(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00021ae0_15\n\t"
      "pushl %%eax\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x1c(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00021ae0_15\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00021ae0_15\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c59a00]\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c59a50]\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00021ae0_15\n\t"
      ".LFUN_00021ae0_10:\n\t"
      "xorl %%eax, %%eax\n\t"
      "testw %%di, %%di\n\t"
      "jle .LFUN_00021ae0_12\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00021ae0_11:\n\t"
      "movswl %%ax, %%ebx\n\t"
      "cmpl %%edx, -0x98(%%ebp,%%ebx,4)\n\t"
      "je .LFUN_00021ae0_14\n\t"
      "incl %%eax\n\t"
      "cmpw %%di, %%ax\n\t"
      "jl .LFUN_00021ae0_11\n\t"
      ".LFUN_00021ae0_12:\n\t"
      "flds (%%esi)\n\t"
      "fsubs 0x12c(%%ecx)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0x130(%%ecx)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0x134(%%ecx)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fcompp\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jne .LFUN_00021ae0_14\n\t"
      "movb 0x6(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00021ae0_13\n\t"
      "movw 0x1e(%%ecx), %%cx\n\t"
      "addw %%cx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00021ae0_14\n\t"
      ".LFUN_00021ae0_13:\n\t"
      "incl -0x8(%%ebp)\n\t"
      ".LFUN_00021ae0_14:\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c59a50]\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_00021ae0_10\n\t"
      "movl -0x18(%%ebp), %%ebx\n\t"
      ".LFUN_00021ae0_15:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00021ae0_18\n\t"
      "movl 0x34(%%ebx), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_00021ae0_18\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00021ae0_18\n\t"
      "pushl %%ecx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c59a00]\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59a50]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00021ae0_18\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fmuls 0x10(%%ebp)\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "jmp .LFUN_00021ae0_16\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00021ae0_16:\n\t"
      "flds (%%esi)\n\t"
      "fsubs 0x12c(%%eax)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0x130(%%eax)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0x134(%%eax)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0xc(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jnp .LFUN_00021ae0_17\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c59a50]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00021ae0_16\n\t"
      "jmp .LFUN_00021ae0_18\n\t"
      ".LFUN_00021ae0_17:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_00021ae0_18:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_00021ae0_19\n\t"
      "movw -0x8(%%ebp), %%cx\n\t"
      "movw %%cx, (%%eax)\n\t"
      ".LFUN_00021ae0_19:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b21ae0_dget), [tag] "m"(b21ae0_tag), [c64540] "m"(b21ae0_c64540), [c64570] "m"(b21ae0_c64570), [c59a00] "m"(b21ae0_c59a00), [c59a50] "m"(b21ae0_c59a50)
      : "memory");
}
#else
#error "FUN_00021ae0: clang naked draft required"
#endif


/* 0x22010 — Check whether the current fire target is still valid.
 * Only applies when mode==3 (prop targeting). Checks prop data
 * and falls back to FUN_00021ae0 distance-based search. */
int actor_combat_check_fire_target(int actor_handle /* @<edi> */, short mode)
{
  char *actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  char *prop;

  if (mode != 3)
    return 1;

  if (*(short *)(actor + 0x60c) != 1) {
    display_assert(
      "actor->control.current_fire_target_type == _actor_fire_target_prop",
      "c:\\halo\\SOURCE\\ai\\actor_combat.c", 0x3ca, 1);
    system_exit(-1);
  }

  prop =
    (char *)datum_get(*(void **)0x5ab23c, *(int *)(actor + 0x610));

  if (*(int *)(prop + 0x110) != -1)
    return 1;

  if (*(char *)(prop + 0x12e) != 0)
    return 0;

  {
    short result = 0;
    FUN_00021ae0(actor_handle, 6.0f, 0.0f, (float *)(prop + 0xbc), &result);
    return result >= 3;
  }
}

/* FUN_00022390 (0x22390) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const b22390_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char * (*const b22390_c211f0)(int actor_handle) = actor_combat_get_firing_variant_definition;
static int (*const b22390_c22010)(int actor_handle, short mode) = actor_combat_check_fire_target;
static float (*const b22390_cb55b0)(short value_type, int team) = FUN_000b55b0;
static void *(*const b22390_get)(int, int) = object_get_and_verify_type;
static void (*const b22390_c21270)(int actor_handle, void *actv, void **burst_ref, void **firing_ref) = actor_combat_get_burst_parameters;
static int *(*const b22390_gseed)(void) = get_global_random_seed_address;
static float (*const b22390_rrange)(int *, float, float) = random_real_range;
static void (*const b22390_ftol)(void) = FUN_001d9068;
static const char * (*const b22390_c1ba1f0)(int tag_index) = tag_get_name;
static const char * (*const b22390_c19b0d0)(const char *tag_name) = tag_name_strip_path;
static void (*const b22390_cff4d0)(int channel, const char *format, ...) = console_printf;
static int (*const b22390_c3b270)(int actor_handle) = actor_attacking_target;
static float (*const b22390_cfac20)(int weapon_tag_index, float *out_field8) = FUN_000fac20;
static void (*const b22390_c21430)(float *target /* */, float distance) = FUN_00021430;
static float (*const b22390_norm)(float *) = normalize3d;
static uint16_t (*const b22390_c10b2b0)(unsigned int *seed) = random_seed_step;
static void (*const b22390_c46f10)(int16_t type, int unit_handle, int param3, int param4, int16_t param5, int16_t param6, int16_t param7) = FUN_00046f10;

__attribute__((naked, noinline))
void FUN_00022390(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x50, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c211f0]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x604(%%ebx), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "je .LFUN_00022390_1\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x156(%%esi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c22010]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00022390_1\n\t"
      "movb %%al, 0x604(%%ebx)\n\t"
      ".LFUN_00022390_1:\n\t"
      "movb 0x604(%%ebx), %%dl\n\t"
      "movl 0x158(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movb %%dl, 0x603(%%ebx)\n\t"
      "movb $0, 0x604(%%ebx)\n\t"
      "jne .LFUN_00022390_4\n\t"
      "movb 0x15c(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00022390_5\n\t"
      "movb 0x504(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00022390_5\n\t"
      ".LFUN_00022390_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00022390_3:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x3e(%%ebx), %%cx\n\t"
      "movb %%al, 0x601(%%ebx)\n\t"
      "movl 0x88(%%esi), %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xd\n\t"
      "call *%[cb55b0]\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "fildl 0x61c(%%ebx)\n\t"
      "addl $8, %%esp\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x253394\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022390_6\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_00022390_7\n\t"
      ".LFUN_00022390_4:\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "flds 0x20(%%eax)\n\t"
      "flds 0x1c(%%eax)\n\t"
      "addl $0x18, %%eax\n\t"
      "flds (%%eax)\n\t"
      "addl $8, %%esp\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x2533c8\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jne .LFUN_00022390_2\n\t"
      ".LFUN_00022390_5:\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_00022390_3\n\t"
      ".LFUN_00022390_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00022390_7:\n\t"
      "movb %%al, 0x600(%%ebx)\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c21270]\n\t"
      "flds 0x458(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "movl -0x1c(%%ebp), %%edi\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022390_8\n\t"
      "flds 0x458(%%ebx)\n\t"
      "jmp .LFUN_00022390_10\n\t"
      ".LFUN_00022390_8:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl 0x18(%%eax), %%ecx\n\t"
      "movl 0x14(%%eax), %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_00022390_9\n\t"
      "flds (%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00022390_9\n\t"
      "fmuls (%%edi)\n\t"
      ".LFUN_00022390_9:\n\t"
      "movb 0x1ca(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022390_10\n\t"
      "fmuls 0x253f3c\n\t"
      ".LFUN_00022390_10:\n\t"
      "fmuls 0x253394\n\t"
      "call *%[ftol]\n\t"
      "movw %%ax, 0x5f4(%%ebx)\n\t"
      "movl 0x7c(%%esi), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x3e(%%ebx), %%ax\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl $0xb\n\t"
      "call *%[cb55b0]\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_00022390_11\n\t"
      "flds 0xc(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00022390_11\n\t"
      "fmuls 0xc(%%edi)\n\t"
      ".LFUN_00022390_11:\n\t"
      "movb 0x1ca(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022390_12\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds 0x253d4c\n\t"
      ".LFUN_00022390_12:\n\t"
      "fstps 0x698(%%ebx)\n\t"
      "movl $0, 0x69c(%%ebx)\n\t"
      "flds 0xc4(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022390_13\n\t"
      "flds 0xc4(%%esi)\n\t"
      "fsts 0x69c(%%ebx)\n\t"
      "movb 0x5aca5c, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022390_15\n\t"
      "movl 0x5c(%%ebx), %%ecx\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ba1f0]\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b0d0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x254a98\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00022390_16\n\t"
      ".LFUN_00022390_13:\n\t"
      "flds 0xc8(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022390_16\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c3b270]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00022390_16\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[cfac20]\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x78(%%esi)\n\t"
      "addl $0x10, %%esp\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022390_14\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x78(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022390_14\n\t"
      "movl 0x78(%%esi), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      ".LFUN_00022390_14:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022390_16\n\t"
      "flds 0xc8(%%esi)\n\t"
      "fdivs -0x8(%%ebp)\n\t"
      "fsts 0x69c(%%ebx)\n\t"
      "movb 0x5aca5c, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022390_15\n\t"
      "movl 0x5c(%%ebx), %%ecx\n\t"
      "subl $0x28, %%esp\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds 0xc8(%%esi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ba1f0]\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b0d0]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x254a5c\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "addl $0x34, %%esp\n\t"
      "jmp .LFUN_00022390_16\n\t"
      ".LFUN_00022390_15:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00022390_16:\n\t"
      "movb 0x603(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00022390_17\n\t"
      "movb 0x602(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022390_19\n\t"
      ".LFUN_00022390_17:\n\t"
      "flds 0xf8(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022390_18\n\t"
      "flds 0x69c(%%ebx)\n\t"
      "fmuls 0xf8(%%esi)\n\t"
      "fstps 0x69c(%%ebx)\n\t"
      ".LFUN_00022390_18:\n\t"
      "flds 0xfc(%%esi)\n\t"
      "fadds 0x698(%%ebx)\n\t"
      "fstps 0x698(%%ebx)\n\t"
      ".LFUN_00022390_19:\n\t"
      "flds 0x14c(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022390_21\n\t"
      "cmpw $1, 0x60c(%%ebx)\n\t"
      "jne .LFUN_00022390_21\n\t"
      "movl 0x610(%%ebx), %%edx\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movw 0x24(%%eax), %%cx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, %%cx\n\t"
      "jl .LFUN_00022390_20\n\t"
      "cmpw $3, %%cx\n\t"
      "jg .LFUN_00022390_20\n\t"
      "cmpw $0, 0x32(%%eax)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jne .LFUN_00022390_21\n\t"
      ".LFUN_00022390_20:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_00022390_21:\n\t"
      "leal 0x62c(%%ebx), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "je .LFUN_00022390_22\n\t"
      "movl 0x14c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x38(%%ebp), %%esi\n\t"
      "call *%[c21430]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00022390_22:\n\t"
      "flds -0x38(%%ebp)\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "fsubs 0x120(%%ebx)\n\t"
      "pushl %%eax\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fsubs 0x124(%%ebx)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fsubs 0x128(%%ebx)\n\t"
      "fmuls 0x2533c0\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      ".byte 0xd8, 0xe2\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x2533c0\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x2533c0\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[c10b2b0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0x8000, %%ax\n\t"
      "jbe .LFUN_00022390_23\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x24(%%ebp)\n\t"
      ".LFUN_00022390_23:\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "flds 0x4(%%esi)\n\t"
      "fchs\n\t"
      "movl %%ecx, %%edx\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "movl 0x10(%%esi), %%ecx\n\t"
      "flds 0x10(%%esi)\n\t"
      "addl $0xc, %%esp\n\t"
      "fchs\n\t"
      "movl %%ecx, %%edx\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x3e(%%ebx), %%cx\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xc\n\t"
      "call *%[cb55b0]\n\t"
      "fmuls (%%esi)\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "addl $0x14, %%esp\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x3e(%%ebx), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl $0xc\n\t"
      "call *%[cb55b0]\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "movb 0x1ca(%%ebx), %%al\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "je .LFUN_00022390_24\n\t"
      "flds -0x8(%%ebp)\n\t"
      ".byte 0xdc, 0xc0\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      ".byte 0xdc, 0xc0\n\t"
      "fstps -0xc(%%ebp)\n\t"
      ".LFUN_00022390_24:\n\t"
      "movw 0x5f4(%%ebx), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jle .LFUN_00022390_28\n\t"
      "flds 0x24(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022390_28\n\t"
      "movswl %%cx, %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "fildl -0x18(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x24(%%esi)\n\t"
      "fmuls 0x2546a4\n\t"
      "fcoms 0x254a58\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022390_25\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x254a58\n\t"
      ".LFUN_00022390_25:\n\t"
      "fptan\n\t"
      "fstp %%st(0)\n\t"
      "fmuls 0x638(%%ebx)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps -0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022390_27\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x2533ec\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps -0x18(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00022390_26\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fdivs -0x10(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fistps -0x10(%%ebp)\n\t"
      "movw -0x10(%%ebp), %%dx\n\t"
      "movw %%dx, 0x5f4(%%ebx)\n\t"
      "jmp .LFUN_00022390_28\n\t"
      ".LFUN_00022390_26:\n\t"
      "fmuls 0x2533ec\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fistps -0x20(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "movw -0x20(%%ebp), %%ax\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movw %%ax, 0x5f4(%%ebx)\n\t"
      ".byte 0xd8, 0xf9\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "jmp .LFUN_00022390_28\n\t"
      ".LFUN_00022390_27:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00022390_28:\n\t"
      "flds -0x14(%%ebp)\n\t"
      "movw 0x5f4(%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "fcos\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fsin\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fcos\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fsin\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x2533c0\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "flds -0x2c(%%ebp)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x24(%%ebp)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x2533c0\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "jle .LFUN_00022390_29\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "fildl -0x20(%%ebp)\n\t"
      "fdivrs 0x2533c8\n\t"
      "flds -0x44(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "flds -0x40(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      ".LFUN_00022390_29:\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "movl -0x50(%%ebp), %%esi\n\t"
      "leal 0x64c(%%ebx), %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl -0x34(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "leal 0x664(%%ebx), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "movl %%esi, (%%edx)\n\t"
      "movl -0x4c(%%ebp), %%esi\n\t"
      "movl %%esi, 0x4(%%edx)\n\t"
      "movl -0x48(%%ebp), %%esi\n\t"
      "movl %%esi, 0x8(%%edx)\n\t"
      "movl -0x44(%%ebp), %%esi\n\t"
      "leal 0x670(%%ebx), %%edx\n\t"
      "movl %%esi, (%%edx)\n\t"
      "movl -0x40(%%ebp), %%esi\n\t"
      "movl %%esi, 0x4(%%edx)\n\t"
      "movl -0x3c(%%ebp), %%esi\n\t"
      "movl %%esi, 0x8(%%edx)\n\t"
      "flds (%%eax)\n\t"
      "fadds (%%ecx)\n\t"
      "fstps 0x67c(%%ebx)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fadds 0x4(%%ecx)\n\t"
      "fstps 0x680(%%ebx)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fadds 0x8(%%ecx)\n\t"
      "fstps 0x684(%%ebx)\n\t"
      "cmpw $7, 0x6e(%%ebx)\n\t"
      "jl .LFUN_00022390_35\n\t"
      "xorb %%cl, %%cl\n\t"
      "orl $0xffffffff, %%edx\n\t"
      "cmpw $1, 0x60c(%%ebx)\n\t"
      "jne .LFUN_00022390_30\n\t"
      "movl 0x610(%%ebx), %%eax\n\t"
      "movl 0x5ab23c, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movb 0x61(%%eax), %%cl\n\t"
      "movl 0x18(%%eax), %%edx\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00022390_30:\n\t"
      "movb 0x378(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022390_31\n\t"
      "movl $0x1c, %%eax\n\t"
      "jmp .LFUN_00022390_34\n\t"
      ".LFUN_00022390_31:\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00022390_32\n\t"
      "movl $0x1e, %%eax\n\t"
      "jmp .LFUN_00022390_34\n\t"
      ".LFUN_00022390_32:\n\t"
      "cmpb $5, 0x1f8(%%ebx)\n\t"
      "jl .LFUN_00022390_33\n\t"
      "movl $0x1d, %%eax\n\t"
      "jmp .LFUN_00022390_34\n\t"
      ".LFUN_00022390_33:\n\t"
      "movb 0x161(%%ebx), %%cl\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "setne %%al\n\t"
      "addl $0x1a, %%eax\n\t"
      ".LFUN_00022390_34:\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "movl 0x18(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c46f10]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_00022390_35:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b22390_dget), [c211f0] "m"(b22390_c211f0), [c22010] "m"(b22390_c22010), [cb55b0] "m"(b22390_cb55b0), [get] "m"(b22390_get), [c21270] "m"(b22390_c21270), [gseed] "m"(b22390_gseed), [rrange] "m"(b22390_rrange), [ftol] "m"(b22390_ftol), [c1ba1f0] "m"(b22390_c1ba1f0), [c19b0d0] "m"(b22390_c19b0d0), [cff4d0] "m"(b22390_cff4d0), [c3b270] "m"(b22390_c3b270), [cfac20] "m"(b22390_cfac20), [c21430] "m"(b22390_c21430), [norm] "m"(b22390_norm), [c10b2b0] "m"(b22390_c10b2b0), [c46f10] "m"(b22390_c46f10)
      : "memory");
}
#else
#error "FUN_00022390: clang naked draft required"
#endif


/* 0x22ba0 — Compute an actor's grenade-throw aim vector.
 *
 * Looks up the actor (0x6325a4). If the actor has a current prop
 * (actor+0x6b4 != -1), reads its record from the AI prop pool
 * (prop_data, 0x5ab23c): when its type
 * (prop+0x24) is 2 or 3 the prop's object datum (prop+0x18) becomes the return
 * value, and when the type is outside [0,1] a seed aim point is built from
 * prop+0xbc/0xc0/0xc4 (with a Z bias of *0x2549d4) and fed to the helper
 * FUN_00022b40 (actor_handle in EBX, &aim point in ESI).
 *
 * It then runs the ballistic firing solution (actor_combat_compute_ballistic_
 * solution), and if the actor currently has no live grenade target
 * (actor+0x158 == -1), derives the throw direction from the cached aim
 * (actor+0x6bc/0x6c0/0x6c4): it normalizes the planar (x,y) part, and when
 * that planar direction points far enough off the actor facing
 * (actor+0x174/0x178), it rotates the actor-facing normal by a fixed cos
 * (0x3f5db3d7) and a +/- sin (*0x253398, sign from the planar cross sign),
 * rescales by the original planar magnitude, asserts the result is a valid
 * real normal, and adopts it as the new aim vector.
 *
 * Finally the chosen vector is scaled by the throw speed (actor+0x6c8) and
 * written to out_aim_vector. Returns the prop datum (or -1).
 *
 * VC71 75.0% (168/176 insns) is a STRUCTURAL ceiling: x87 op scheduling
 * (faddp/fsqrt order), register allocation (ebx vs edi for the arg, reg-vs-stack
 * -1 init), and byte/dword compare idioms (jle/jl, testl/testb). The
 * display_assert(...,0x749,1) is present and aligned; no FPU operand swap.
 * Verified 2026-06-23 [[project_sub80_vc71_audit_2026-06-23]]. */
int actor_aim_grenade(int actor_handle, void *aim_params, float *out_aim_vector)
{
  char *actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  float aim_x, aim_y, aim_z;   /* [ebp-0x24/-0x20/-0x1c] chosen aim vector  */
  float nrm[3];                /* [ebp-0x18/-0x14/-0x10] rotated facing nrm;
                                  MUST be contiguous — passed by &nrm[0] to
                                  rotate_vector3d_by_sincos and
                                  valid_real_normal3d, both of which read 3
                                  adjacent floats. Separate scalar locals let
                                  clang scatter the stack slots, so the pointer
                                  reads picked up unrelated locals and a valid
                                  unit normal failed assert_valid_real_normal3d. */
  float planar[2];             /* [ebp-0xc/-0x8] planar dir for normalize    */
  int result;                  /* [ebp-0x4] prop datum / -1             */
  char *prop;
  short prop_type;
  float aim_vec[3];            /* contiguous buffer for FUN_00022b40 (ESI)   */
  float speed;
  float planar_mag;
  float t;
  int sign;
  float sin_a;

  result = -1;
  if (*(int *)(actor + 0x6b4) != -1) {
    prop = (char *)datum_get(*(void **)0x5ab23c, *(int *)(actor + 0x6b4));
    prop_type = *(short *)(prop + 0x24);
    if (prop_type > 1 && prop_type < 4)
      result = *(int *)(prop + 0x18);
    if (prop_type < 0 || prop_type > 1) {
      aim_vec[0] = *(float *)(prop + 0xbc);
      aim_vec[1] = *(float *)(prop + 0xc0);
      aim_vec[2] = *(float *)(prop + 0xc4) + *(float *)0x2549d4;
      FUN_00022b40(actor_handle, aim_vec);
    }
  }

  actor_combat_compute_ballistic_solution(actor_handle, (int)aim_params);

  aim_x = *(float *)(actor + 0x6bc);
  aim_y = *(float *)(actor + 0x6c0);
  aim_z = *(float *)(actor + 0x6c4);
  if (*(int *)(actor + 0x158) == -1) {
    planar[0] = aim_x;
    planar[1] = aim_y;
    if (magnitude3d(planar) > *(float *)0x2533c0 &&
        planar[0] * *(float *)(actor + 0x174) +
            planar[1] * *(float *)(actor + 0x178) < *(float *)0x2533dc) {
      nrm[0] = *(float *)(actor + 0x174);
      nrm[1] = *(float *)(actor + 0x178);
      nrm[2] = *(float *)(actor + 0x17c);
      t = planar[1] * *(float *)(actor + 0x174) -
          planar[0] * *(float *)(actor + 0x178);
      sign = (t > *(float *)0x2533c0) ? 1 : -1;
      sin_a = (float)sign * *(float *)0x253398;
      /* orig 0x22cc2: rotate input z is the facing z (actor+0x17c), set at
         line 649 above. Do NOT clobber it with aim_z before the rotate. */
      /* cos(30 deg); paired with sin_a = +/-0.5 (*0x253398 = sin 30 deg) for a
         length-preserving 30-degree rotation about world-up. The prior literal
         0.857651889f (0x3f5b8f13, cos 30.95 deg) did NOT match the original
         immediate 0x3f5db3d7 = 0.866025388: with sin=0.5 that pair has
         sin^2+cos^2 = 0.9856, so it shrank the rotated facing ~0.7% and tripped
         assert_valid_real_normal3d at actor_combat.c:1865 on grenade throws
         whose aim was >30deg off the actor facing (PoA covenant combat). */
      rotate_vector3d_by_sincos(nrm, *(float **)0x31fc44, sin_a,
                                0.866025388f /* 0x3f5db3d7 = cos(30 deg) */);
      /* orig 0x22d1b: overwrite the rotated z with aim_z AFTER the rotate. */
      nrm[2] = aim_z;
      planar_mag = (float)x87_sqrt(aim_x * aim_x + aim_y * aim_y);
      nrm[0] = nrm[0] * planar_mag;
      nrm[1] = planar_mag * nrm[1];
      if (!valid_real_normal3d(nrm)) {
        csprintf((char *)0x5ab100,
                 "%s: assert_valid_real_normal3d(%f, %f, %f)", "&new_aim_vector",
                 (double)nrm[0], (double)nrm[1], (double)aim_z);
        display_assert((char *)0x5ab100, "c:\\halo\\SOURCE\\ai\\actor_combat.c",
                       0x749, 1);
        system_exit(-1);
      }
      aim_x = nrm[0];
      aim_y = nrm[1];
      aim_z = nrm[2];
    }
  }

  speed = *(float *)(actor + 0x6c8);
  out_aim_vector[0] = aim_x * speed;
  out_aim_vector[1] = aim_y * speed;
  out_aim_vector[2] = speed * aim_z;
  return result;
}
/* --- actor_combat.obj batch drafts (2026-07-26) --- */

/* actor_combat_build_grenade_trajectory (0x218d0) — readable C lift.
 * ABI: origin@<eax>, direction@<ebx>; remaining args on stack.
 * Solves a grenade ballistic arc and optionally writes launch velocity. */
char actor_combat_build_grenade_trajectory(float *origin, float *direction,
                                           int16_t grenade_index,
                                           float grenade_speed,
                                           float *target_pos, float *unused_a,
                                           float *unused_b, float *aim_speed_out,
                                           float *aim_param_out,
                                           float *launch_velocity,
                                           float *out_accel)
{
  void *element;
  void *projectile;
  char linear_flag;
  char ok;

  (void)unused_a;
  (void)unused_b;

  if (!origin || !target_pos || !direction || !aim_speed_out) {
    display_assert((const char *)0x254990, (const char *)0x254910, 0x6f4, true);
    system_exit(-1);
  }

  element = tag_block_get_element((char *)game_globals_get() + 0x128,
                                 (int)grenade_index, 0x44);
  if (!element)
    return 0;
  if (*(int *)((char *)element + 0x40) == -1)
    return 0;

  projectile = tag_get(0x70726f6a, *(int *)((char *)element + 0x40));
  if (!projectile)
    return 0;

  linear_flag = 0;
  ok = projectile_aim((int)projectile, (int)origin, (int)target_pos,
                      &grenade_speed, 0, (int)unused_a, 0, 0, (int)direction,
                      (int)aim_speed_out, (int)aim_param_out, 0, &linear_flag);
  if (!ok)
    return 0;

  if (launch_velocity) {
    float speed = *aim_speed_out;
    launch_velocity[0] = speed * direction[0];
    launch_velocity[1] = speed * direction[1];
    launch_velocity[2] = speed * direction[2];
  }

  if (out_accel) {
    if (linear_flag)
      *out_accel = *(float *)0x2533c0; /* 0.0f */
    else
      *out_accel = projectile_get_ballistic_acceleration((int)projectile);
  }
  return 1;
}


/* actor_aim_projectile (0x220c0) — XBE naked draft (batch 223). */
#if defined(__clang__)
static void *(*const b220c0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const b220c0_gtime)(void) = game_time_get;
static void (*const b220c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b220c0_exitfn)(int) = system_exit;
static float (*const b220c0_norm)(float *) = normalize3d;
static bool (*const b220c0_c21fb0)(float *v) = valid_real_normal3d;
static char * (*const b220c0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b220c0_c21130)(int actor_handle, float *weapon_vector) = actor_combat_get_weapon_vector;
static void (*const b220c0_perp)(float *, float *) = perpendicular3d;
static void (*const b220c0_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;

__attribute__((naked, noinline))
int actor_aim_projectile(int unit_handle __attribute__((unused)), float *direction_in __attribute__((unused)), float *direction_out __attribute__((unused)), int *out_extra __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, 0x5f2(%%ebx)\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .Lactor_aim_projectile_10\n\t"
      "movl 0x331f58, %%ecx\n\t"
      "andl $0xffff, %%edi\n\t"
      "imull $0x657c, %%edi, %%edi\n\t"
      "addl %%ecx, %%edi\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, 0x5c(%%edi)\n\t"
      "cmpw $1, 0x60c(%%ebx)\n\t"
      "jne .Lactor_aim_projectile_1\n\t"
      "movl 0x610(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_aim_projectile_1\n\t"
      "movl 0x5ab23c, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movw 0x24(%%eax), %%cx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, %%cx\n\t"
      "jl .Lactor_aim_projectile_1\n\t"
      "cmpw $3, %%cx\n\t"
      "jg .Lactor_aim_projectile_1\n\t"
      "movl 0x18(%%eax), %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".Lactor_aim_projectile_1:\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lactor_aim_projectile_2\n\t"
      "pushl $1\n\t"
      "pushl $0x42f\n\t"
      "pushl $0x254910\n\t"
      "pushl $0x254a50\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_aim_projectile_2:\n\t"
      "movb 0x688(%%ebx), %%al\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movb %%al, 0x60(%%edi)\n\t"
      "movl (%%edx), %%eax\n\t"
      "leal 0x64(%%edi), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movb 0x688(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_aim_projectile_3\n\t"
      "addl $0x68c, %%ebx\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%ebx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ebx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "jmp .Lactor_aim_projectile_4\n\t"
      ".Lactor_aim_projectile_3:\n\t"
      "leal 0x67c(%%ebx), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl (%%ecx), %%ebx\n\t"
      "leal 0x7c(%%edi), %%edx\n\t"
      "movl %%ebx, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%ebx\n\t"
      "movl %%ebx, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "flds (%%eax)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "fsubs (%%ecx)\n\t"
      "pushl %%esi\n\t"
      "fstps (%%esi)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x4(%%ecx)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs 0x8(%%ecx)\n\t"
      "fstps 0x8(%%esi)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $4, %%esp\n\t"
      ".Lactor_aim_projectile_4:\n\t"
      "pushl %%esi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_aim_projectile_5\n\t"
      "flds 0x8(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x442\n\t"
      "pushl $0x254910\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x254a50\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_aim_projectile_5:\n\t"
      "movl %%esi, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal 0x70(%%edi), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal -0x14(%%ebp), %%ebx\n\t"
      "call *%[c21130]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x2533dc\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_aim_projectile_8\n\t"
      "flds -0x10(%%ebp)\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "pushl %%ecx\n\t"
      "flds -0xc(%%ebp)\n\t"
      "movb $1, %%bl\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lactor_aim_projectile_6\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[perp]\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0xc, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lactor_aim_projectile_6\n\t"
      "xorb %%bl, %%bl\n\t"
      ".Lactor_aim_projectile_6:\n\t"
      "testb %%bl, %%bl\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl %%esi, %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "je .Lactor_aim_projectile_7\n\t"
      "pushl $0x3f5db3d7\n\t"
      "pushl $0x3f000000\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[rots]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lactor_aim_projectile_7:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "leal 0x98(%%edi), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movb $1, 0x88(%%edi)\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl (%%esi), %%ecx\n\t"
      "addl $0x8c, %%edi\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl %%edx, 0x4(%%edi)\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl %%eax, 0x8(%%edi)\n\t"
      "jmp .Lactor_aim_projectile_9\n\t"
      ".Lactor_aim_projectile_8:\n\t"
      "movb $0, 0x88(%%edi)\n\t"
      ".Lactor_aim_projectile_9:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x698(%%ecx), %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "popl %%esi\n\t"
      ".Lactor_aim_projectile_10:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [dget] "m"(b220c0_dget), [gtime] "m"(b220c0_gtime), [assert] "m"(b220c0_assert), [exitfn] "m"(b220c0_exitfn), [norm] "m"(b220c0_norm), [c21fb0] "m"(b220c0_c21fb0), [c8d9d0] "m"(b220c0_c8d9d0), [c21130] "m"(b220c0_c21130), [perp] "m"(b220c0_perp), [rots] "m"(b220c0_rots)
      : "memory");
}
#else
#error "actor_aim_projectile: clang naked draft required"
#endif


/* FUN_00022dc0 (0x22dc0) — XBE naked draft (batch 104). */
#if defined(__clang__)
static void *(*const b22dc0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b22dc0_tag)(int, int) = tag_get;
static char * (*const b22dc0_c211f0)(int actor_handle) = actor_combat_get_firing_variant_definition;
static int (*const b22dc0_c3b270)(int actor_handle) = actor_attacking_target;
static void *(*const b22dc0_get)(int, int) = object_get_and_verify_type;
static void (*const b22dc0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b22dc0_exitfn)(int) = system_exit;
static float (*const b22dc0_c121a0)(const float *a, const float *b) = distance_squared3d;
static bool (*const b22dc0_c3b320)(int actor_handle) = actor_has_ranged_weapon;
static int16_t (*const b22dc0_c1aae70)(int unit_handle, int16_t grenade_type) = unit_get_grenade_count;
static int16_t (*const b22dc0_c1aaa90)(int unit_handle, int16_t grenade_type, int16_t grenade_count) = unit_set_grenade_count;
static void (*const b22dc0_c3c370)(int actor_handle) = actor_handle_communication;
static void (*const b22dc0_c46f10)(int16_t type, int unit_handle, int param3, int param4, int16_t param5, int16_t param6, int16_t param7) = FUN_00046f10;
static float (*const b22dc0_cb55b0)(short value_type, int team) = FUN_000b55b0;
static int (*const b22dc0_c20f80)(int actor_handle, short mode) = actor_combat_check_mode;
static float (*const b22dc0_c121e0)(float min, float max) = FUN_000121e0;
static int *(*const b22dc0_gseed)(void) = get_global_random_seed_address;
static float (*const b22dc0_rmreal)(unsigned int *) = random_math_real;
static void (*const b22dc0_ftol)(void) = FUN_001d9068;
static int (*const b22dc0_c22010)(int actor_handle, short mode) = actor_combat_check_fire_target;
static void *(*const b22dc0_elem)(void *, int, int) = tag_block_get_element;
static void * (*const b22dc0_cba6c0)(void) = players_get_combined_pvs;
static float (*const b22dc0_c1ad60)(float *a, float *b) = FUN_0001ad60;
static int (*const b22dc0_c416e0)(float *origin, int bsp, float *target, int param_4, short param_5, char param_6, int param_7, char param_8) = ai_test_line_of_sight;
static bool (*const b22dc0_cfd400)(int weapon_handle, int16_t trigger_index, void *param_3, void *param_4, int param_5, float *param_6, int param_7, void *param_8, void *param_9) = weapon_aim;
static int (*const b22dc0_c2a360)(int actor_handle) = FUN_0002a360;
static int (*const b22dc0_gtime)(void) = game_time_get;
static void (*const b22dc0_c21130)(int actor_handle, float *weapon_vector) = actor_combat_get_weapon_vector;
static void (*const b22dc0_c21590)(int actor_handle) = actor_combat_set_fire_timer;
static bool (*const b22dc0_c21640)(int actor_handle, void *timing_data) = actor_combat_evaluate_firing;
static void (*const b22dc0_c22390)(int actor_handle) = FUN_00022390;
static void (*const b22dc0_c12140)(float *a, float *b, float *result) = FUN_00012140;
static float *(*const b22dc0_vsca)(float *, float *, float, float *) = vector3d_scale_add;
static float (*const b22dc0_cfaed0)(int weapon_handle, int16_t trigger_index, float param_3) = weapon_estimate_time_to_target;
static void (*const b22dc0_useat)(int, float *) = unit_set_seat_state;
static float (*const b22dc0_c12170)(float *vector) = FUN_00012170;
static float (*const b22dc0_mag)(float *) = magnitude3d;
static void (*const b22dc0_c1a93e0)(int unit_handle, int16_t estimate_mode, vector3_t *body_position, vector3_t *desired_facing, vector3_t *desired_gun_offset, vector3_t *out_position) = unit_estimate_position;
static bool (*const b22dc0_c21fb0)(float *v) = valid_real_normal3d;
static char * (*const b22dc0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static bool (*const b22dc0_c41590)(int actor_handle, int excluded_handle, float *origin, float *offset, int *result_out) = ai_test_line_of_fire;
static void (*const b22dc0_c21270)(int actor_handle, void *actv, void **burst_ref, void **firing_ref) = actor_combat_get_burst_parameters;
static void (*const b22dc0_c3c2d0)(int actor_handle, char flag, int target) = actor_unit_control_primary_trigger;
static void (*const b22dc0_c3c330)(int actor_handle, char flag) = actor_unit_control_secondary_trigger;

__attribute__((naked, noinline))
void FUN_00022dc0(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x4c, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x58(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "movl %%ebx, -0x24(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl 0x5c(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637476\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "call *%[c211f0]\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl $0, -0x20(%%ebp)\n\t"
      "call *%[c3b270]\n\t"
      "addl $0x20, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00022dc0_1\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x77656170\n\t"
      "call *%[tag]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      ".LFUN_00022dc0_1:\n\t"
      "movl 0x18(%%ebx), %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "pushl %%esi\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "call *%[c3b270]\n\t"
      "movl 0x331f58, %%edx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%esi, %%eax\n\t"
      "andl $0xffff, %%eax\n\t"
      "imull $0x657c, %%eax, %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x5f4(%%ebx), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "movl $0xffffffff, -0x8(%%ebp)\n\t"
      "jle .LFUN_00022dc0_2\n\t"
      "decl %%eax\n\t"
      "movw %%ax, 0x5f4(%%ebx)\n\t"
      ".LFUN_00022dc0_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x5f6(%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00022dc0_3\n\t"
      "decl %%eax\n\t"
      "movw %%ax, 0x5f6(%%ebx)\n\t"
      ".LFUN_00022dc0_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x5f8(%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00022dc0_4\n\t"
      "decl %%eax\n\t"
      "movw %%ax, 0x5f8(%%ebx)\n\t"
      ".LFUN_00022dc0_4:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x5fc(%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00022dc0_5\n\t"
      "decl %%eax\n\t"
      "movw %%ax, 0x5fc(%%ebx)\n\t"
      ".LFUN_00022dc0_5:\n\t"
      "movw 0x60c(%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00022dc0_6\n\t"
      "incl 0x61c(%%ebx)\n\t"
      ".LFUN_00022dc0_6:\n\t"
      "cmpw $2, 0x5f2(%%ebx)\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_00022dc0_13\n\t"
      "movb 0x454(%%ebx), %%cl\n\t"
      "xorl %%edi, %%edi\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00022dc0_8\n\t"
      "movb 0x45d(%%ebx), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00022dc0_7\n\t"
      "movl $2, %%edi\n\t"
      "jmp .LFUN_00022dc0_8\n\t"
      ".LFUN_00022dc0_7:\n\t"
      "cmpl $-1, 0x270(%%ebx)\n\t"
      "je .LFUN_00022dc0_8\n\t"
      "movl $1, %%edi\n\t"
      ".LFUN_00022dc0_8:\n\t"
      "cmpw %%ax, %%di\n\t"
      "jne .LFUN_00022dc0_9\n\t"
      "cmpw $1, %%di\n\t"
      "jne .LFUN_00022dc0_11\n\t"
      "movl 0x610(%%ebx), %%eax\n\t"
      "movl 0x270(%%ebx), %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "setne %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022dc0_10\n\t"
      ".LFUN_00022dc0_9:\n\t"
      "movl $0, 0x61c(%%ebx)\n\t"
      ".LFUN_00022dc0_10:\n\t"
      "cmpw $1, %%di\n\t"
      "movw %%di, 0x60c(%%ebx)\n\t"
      "jne .LFUN_00022dc0_12\n\t"
      "movl 0x270(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, 0x610(%%ebx)\n\t"
      "jne .LFUN_00022dc0_13\n\t"
      "pushl $1\n\t"
      "pushl $0x85\n\t"
      "pushl $0x254910\n\t"
      "pushl $0x254bbc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00022dc0_13\n\t"
      ".LFUN_00022dc0_11:\n\t"
      "cmpw $2, %%di\n\t"
      "jne .LFUN_00022dc0_10\n\t"
      "leal 0x610(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x460(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c121a0]\n\t"
      "fcomps 0x25337c\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00022dc0_9\n\t"
      "jmp .LFUN_00022dc0_10\n\t"
      ".LFUN_00022dc0_12:\n\t"
      "cmpw $2, %%di\n\t"
      "jne .LFUN_00022dc0_13\n\t"
      "leal 0x460(%%ebx), %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "leal 0x610(%%ebx), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      ".LFUN_00022dc0_13:\n\t"
      "pushl %%esi\n\t"
      "movb $0, 0x628(%%ebx)\n\t"
      "call *%[c3b320]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022dc0_14\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "flds 0x74(%%eax)\n\t"
      "jmp .LFUN_00022dc0_15\n\t"
      ".LFUN_00022dc0_14:\n\t"
      "flds 0x2533c0\n\t"
      ".LFUN_00022dc0_15:\n\t"
      "movb 0x45c(%%ebx), %%al\n\t"
      "fstps 0x608(%%ebx)\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022dc0_17\n\t"
      "movl -0x18(%%ebp), %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x180(%%edi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00022dc0_16\n\t"
      "movl 0x18(%%ebx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1aae70]\n\t"
      "addl $8, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_00022dc0_16\n\t"
      "movl 0x18(%%ebx), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x180(%%edi), %%dx\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1aaa90]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00022dc0_16:\n\t"
      "pushl %%esi\n\t"
      "call *%[c3c370]\n\t"
      "movl 0x18(%%ebx), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "pushl $9\n\t"
      "call *%[c46f10]\n\t"
      "addl $0x20, %%esp\n\t"
      "jmp .LFUN_00022dc0_54\n\t"
      ".LFUN_00022dc0_17:\n\t"
      "pushl %%esi\n\t"
      "call *%[c3b320]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022dc0_54\n\t"
      "cmpw $4, 0x5f2(%%ebx)\n\t"
      "jne .LFUN_00022dc0_18\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_55\n\t"
      ".LFUN_00022dc0_18:\n\t"
      "cmpl $-1, -0x14(%%ebp)\n\t"
      "movb $1, -0x3(%%ebp)\n\t"
      "jne .LFUN_00022dc0_19\n\t"
      "pushl $1\n\t"
      "pushl $0xad\n\t"
      "pushl $0x254910\n\t"
      "pushl $0x254ba4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00022dc0_19:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "cmpw $0, 0x154(%%edx)\n\t"
      "jle .LFUN_00022dc0_24\n\t"
      "movw 0x5f2(%%ebx), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "je .LFUN_00022dc0_24\n\t"
      "cmpw $4, %%ax\n\t"
      "je .LFUN_00022dc0_24\n\t"
      "cmpw $0, 0x5fc(%%ebx)\n\t"
      "jg .LFUN_00022dc0_24\n\t"
      "cmpw $0, 0x5fe(%%ebx)\n\t"
      "jg .LFUN_00022dc0_24\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "pushl $4\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x77656170\n\t"
      "call *%[tag]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x3e(%%ebx), %%dx\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl $0x12\n\t"
      "call *%[cb55b0]\n\t"
      "fstp %%st(0)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movswl 0x154(%%eax), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00022dc0_22\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_00022dc0_20\n\t"
      "cmpl $1, 0x4fc(%%edi)\n\t"
      "setg %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022dc0_24\n\t"
      ".LFUN_00022dc0_20:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x156(%%edx), %%ax\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c20f80]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022dc0_24\n\t"
      "pushl $0x3fc00000\n\t"
      "pushl $0\n\t"
      "call *%[c121e0]\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      "fadds 0x15c(%%edi)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0x253394\n\t"
      "addl $0xc, %%esp\n\t"
      "call *%[ftol]\n\t"
      "movw %%ax, 0x5fc(%%ebx)\n\t"
      "fcomps 0x158(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00022dc0_24\n\t"
      "movl %%edi, %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x156(%%ecx), %%dx\n\t"
      "movl %%esi, %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c22010]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022dc0_24\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl $3, %%ecx\n\t"
      "cmpw %%cx, 0x156(%%eax)\n\t"
      "jne .LFUN_00022dc0_21\n\t"
      "movw %%cx, 0x5fe(%%ebx)\n\t"
      ".LFUN_00022dc0_21:\n\t"
      "movswl 0x154(%%eax), %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00022dc0_23\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_00022dc0_24\n\t"
      "movb $1, 0x604(%%ebx)\n\t"
      "jmp .LFUN_00022dc0_24\n\t"
      ".LFUN_00022dc0_22:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x3e(%%ebx), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x11\n\t"
      "call *%[cb55b0]\n\t"
      "fstp %%st(0)\n\t"
      "movl 0x4fc(%%edi), %%eax\n\t"
      "addl $0x4fc, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_00022dc0_24\n\t"
      "pushl $0x114\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_00022dc0_20\n\t"
      ".LFUN_00022dc0_23:\n\t"
      "movb $1, 0x602(%%ebx)\n\t"
      ".LFUN_00022dc0_24:\n\t"
      "movw 0x60c(%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00022dc0_31\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .LFUN_00022dc0_25\n\t"
      "movl 0x610(%%ebx), %%eax\n\t"
      "movl 0x5ab23c, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x11c(%%edi), %%edx\n\t"
      "movl %%edx, 0x638(%%ebx)\n\t"
      "leal 0xc8(%%edi), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0x62c(%%ebx), %%esi\n\t"
      "movl %%esi, %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movw 0x38(%%edi), %%cx\n\t"
      "movw %%cx, 0x626(%%ebx)\n\t"
      "movb 0x118(%%edi), %%dl\n\t"
      "addl $8, %%esp\n\t"
      "movb %%dl, 0x621(%%ebx)\n\t"
      "call *%[cba6c0]\n\t"
      "movb $1, 0x624(%%ebx)\n\t"
      "movw 0x100(%%edi), %%di\n\t"
      "cmpw $-1, %%di\n\t"
      "je .LFUN_00022dc0_27\n\t"
      "movswl %%di, %%edi\n\t"
      "movl %%edi, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "sarl $5, %%edi\n\t"
      "andl (%%eax,%%edi,4), %%edx\n\t"
      "negl %%edx\n\t"
      "sbbb %%dl, %%dl\n\t"
      "incb %%dl\n\t"
      "movb %%dl, 0x624(%%ebx)\n\t"
      "jmp .LFUN_00022dc0_27\n\t"
      ".LFUN_00022dc0_25:\n\t"
      "cmpw $2, %%ax\n\t"
      "je .LFUN_00022dc0_26\n\t"
      "pushl $1\n\t"
      "pushl $0x128\n\t"
      "pushl $0x254910\n\t"
      "pushl $0x254b58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00022dc0_26:\n\t"
      "leal 0x610(%%ebx), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl (%%ecx), %%edi\n\t"
      "leal 0x62c(%%ebx), %%esi\n\t"
      "movl %%esi, %%edx\n\t"
      "movl %%edi, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%edi\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edi, 0x4(%%edx)\n\t"
      "pushl %%eax\n\t"
      "leal 0x120(%%ebx), %%edi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "call *%[c1ad60]\n\t"
      "fstps 0x638(%%ebx)\n\t"
      "movl 0x61c(%%ebx), %%eax\n\t"
      "cdq\n\t"
      "movl $0xa, %%ecx\n\t"
      "idivl %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "movb $0, 0x621(%%ebx)\n\t"
      "movb $0, 0x624(%%ebx)\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .LFUN_00022dc0_27\n\t"
      "cmpl $-1, 0x158(%%ebx)\n\t"
      "setne %%dl\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x148(%%ebx), %%ax\n\t"
      "pushl %%edx\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c416e0]\n\t"
      "addl $0x20, %%esp\n\t"
      "movw %%ax, 0x626(%%ebx)\n\t"
      ".LFUN_00022dc0_27:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movb $0, 0x622(%%ebx)\n\t"
      "flds 0x148(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022dc0_28\n\t"
      "flds 0x638(%%ebx)\n\t"
      "fcomps 0x148(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022dc0_28\n\t"
      "movb $1, 0x622(%%ebx)\n\t"
      ".LFUN_00022dc0_28:\n\t"
      "movb 0x455(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022dc0_29\n\t"
      "flds 0x14c(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022dc0_29\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_00022dc0_30\n\t"
      ".LFUN_00022dc0_29:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00022dc0_30:\n\t"
      "leal -0x3(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x622(%%ebx), %%cl\n\t"
      "leal 0x648(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "movb %%al, 0x623(%%ebx)\n\t"
      "leal 0x63c(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "leal 0x120(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[cfd400]\n\t"
      "addl $0x24, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00022dc0_31\n\t"
      "movw $0, 0x60c(%%ebx)\n\t"
      ".LFUN_00022dc0_31:\n\t"
      "cmpw $0, 0x60c(%%ebx)\n\t"
      "jne .LFUN_00022dc0_32\n\t"
      "movl $3, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_54\n\t"
      ".LFUN_00022dc0_32:\n\t"
      "movb 0x624(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022dc0_33\n\t"
      "movl $4, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_54\n\t"
      ".LFUN_00022dc0_33:\n\t"
      "movb 0x457(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00022dc0_34\n\t"
      "cmpw $0, 0x5f6(%%ebx)\n\t"
      "jle .LFUN_00022dc0_34\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_54\n\t"
      ".LFUN_00022dc0_34:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c2a360]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022dc0_35\n\t"
      "movl $1, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_54\n\t"
      ".LFUN_00022dc0_35:\n\t"
      "movb 0x457(%%ebx), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .LFUN_00022dc0_37\n\t"
      "movb 0x15c(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022dc0_36\n\t"
      "movb 0x99(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00022dc0_36\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "testb $1, (%%ecx)\n\t"
      "jne .LFUN_00022dc0_36\n\t"
      "movl $0xe, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_54\n\t"
      ".LFUN_00022dc0_36:\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .LFUN_00022dc0_37\n\t"
      "movl -0x1c(%%ebp), %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "testb $2, %%ah\n\t"
      "je .LFUN_00022dc0_38\n\t"
      "movb 0x508(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00022dc0_38\n\t"
      "movl $0xf, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_54\n\t"
      ".LFUN_00022dc0_37:\n\t"
      "movl -0x1c(%%ebp), %%esi\n\t"
      ".LFUN_00022dc0_38:\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .LFUN_00022dc0_40\n\t"
      "testb $2, 0x4(%%esi)\n\t"
      "je .LFUN_00022dc0_39\n\t"
      "movb 0x508(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022dc0_39\n\t"
      "movl $0x10, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_54\n\t"
      ".LFUN_00022dc0_39:\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .LFUN_00022dc0_40\n\t"
      "testb $4, 0x4(%%esi)\n\t"
      "je .LFUN_00022dc0_40\n\t"
      "movb 0x504(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022dc0_40\n\t"
      "movl $0x11, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_54\n\t"
      ".LFUN_00022dc0_40:\n\t"
      "movb 0x621(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00022dc0_53\n\t"
      "movb 0x15d(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00022dc0_53\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00022dc0_41\n\t"
      "flds 0x40c(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022dc0_41\n\t"
      "flds 0x638(%%ebx)\n\t"
      "fcomps 0x40c(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00022dc0_41\n\t"
      "movl $0x13, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_54\n\t"
      ".LFUN_00022dc0_41:\n\t"
      "cmpw $0, 0x3e8(%%ebx)\n\t"
      "movl $2, %%eax\n\t"
      "je .LFUN_00022dc0_52\n\t"
      "cmpw %%ax, 0x3ec(%%ebx)\n\t"
      "jne .LFUN_00022dc0_52\n\t"
      "movb 0x58c(%%ebx), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00022dc0_52\n\t"
      "cmpw %%ax, 0x5f2(%%ebx)\n\t"
      "jne .LFUN_00022dc0_42\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_55\n\t"
      ".LFUN_00022dc0_42:\n\t"
      "movw 0x626(%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_00022dc0_43\n\t"
      "cmpw $1, %%ax\n\t"
      "je .LFUN_00022dc0_43\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_00022dc0_44\n\t"
      ".LFUN_00022dc0_43:\n\t"
      "movl $1, %%eax\n\t"
      ".LFUN_00022dc0_44:\n\t"
      "testb %%al, %%al\n\t"
      "movb %%al, 0x620(%%ebx)\n\t"
      "jne .LFUN_00022dc0_45\n\t"
      "movb 0x623(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00022dc0_45\n\t"
      "movl $5, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_54\n\t"
      ".LFUN_00022dc0_45:\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .LFUN_00022dc0_46\n\t"
      "flds 0x638(%%ebx)\n\t"
      "fcomps 0x608(%%ebx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00022dc0_46\n\t"
      "movl $6, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_54\n\t"
      ".LFUN_00022dc0_46:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movb $1, 0x628(%%ebx)\n\t"
      "call *%[gtime]\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x34(%%ecx)\n\t"
      "movl (%%esi), %%eax\n\t"
      "testb $0x20, %%ah\n\t"
      "je .LFUN_00022dc0_47\n\t"
      "movb $1, 0x38(%%ecx)\n\t"
      "movb $1, 0x39(%%ecx)\n\t"
      "jmp .LFUN_00022dc0_55\n\t"
      ".LFUN_00022dc0_47:\n\t"
      "flds 0x638(%%ebx)\n\t"
      "fcomps 0x2533ec\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00022dc0_48\n\t"
      "flds 0x638(%%ebx)\n\t"
      "fmuls 0x254b54\n\t"
      "fadds 0x254b50\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_49\n\t"
      ".LFUN_00022dc0_48:\n\t"
      "movl $0x3f7851ec, -0x18(%%ebp)\n\t"
      ".LFUN_00022dc0_49:\n\t"
      "leal -0x40(%%ebp), %%ebx\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c21130]\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "fmuls 0x640(%%edx)\n\t"
      "addl $0x63c, %%edx\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls 0x8(%%edx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls (%%edx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcoms -0x18(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00022dc0_50\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      ".LFUN_00022dc0_50:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl -0x40(%%ebp), %%esi\n\t"
      "leal 0x3c(%%ecx), %%eax\n\t"
      "movl %%esi, (%%eax)\n\t"
      "movl -0x3c(%%ebp), %%esi\n\t"
      "movl %%esi, 0x4(%%eax)\n\t"
      "movl -0x38(%%ebp), %%esi\n\t"
      "movl %%esi, 0x8(%%eax)\n\t"
      "movl (%%edx), %%esi\n\t"
      "leal 0x48(%%ecx), %%eax\n\t"
      "movl %%esi, (%%eax)\n\t"
      "movl 0x4(%%edx), %%esi\n\t"
      "movl %%esi, 0x4(%%eax)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "fsts 0x58(%%ecx)\n\t"
      "fcomps -0x18(%%ebp)\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl %%eax, 0x54(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00022dc0_51\n\t"
      "movl -0x24(%%ebp), %%ebx\n\t"
      "movl $1, %%eax\n\t"
      "movb %%al, 0x38(%%ecx)\n\t"
      "movb $0, 0x39(%%ecx)\n\t"
      "jmp .LFUN_00022dc0_55\n\t"
      ".LFUN_00022dc0_51:\n\t"
      "movl -0x24(%%ebp), %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb %%al, 0x38(%%ecx)\n\t"
      "movb %%al, 0x39(%%ecx)\n\t"
      "jmp .LFUN_00022dc0_55\n\t"
      ".LFUN_00022dc0_52:\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_54\n\t"
      ".LFUN_00022dc0_53:\n\t"
      "movl $0x12, -0x8(%%ebp)\n\t"
      ".LFUN_00022dc0_54:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movw $0, 0x5f2(%%ebx)\n\t"
      ".LFUN_00022dc0_55:\n\t"
      "cmpw $0, 0x5f2(%%ebx)\n\t"
      "je .LFUN_00022dc0_62\n\t"
      "cmpw $-1, -0x8(%%ebp)\n\t"
      "je .LFUN_00022dc0_56\n\t"
      "pushl $1\n\t"
      "pushl $0x205\n\t"
      "pushl $0x254910\n\t"
      "pushl $0x254b38\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00022dc0_56:\n\t"
      "movswl 0x5f2(%%ebx), %%eax\n\t"
      "decl %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "ja .LFUN_00022dc0_61\n\t"
      "jmp *.LFUN_00022dc0_jt0(,%%eax,4)\n\t"
      ".LFUN_00022dc0_57:\n\t"
      "movl $0xc, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_62\n\t"
      ".LFUN_00022dc0_58:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw %%cx, 0x5f4(%%ebx)\n\t"
      "setne %%cl\n\t"
      "addl $8, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_62\n\t"
      ".LFUN_00022dc0_59:\n\t"
      "movl $0xd, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_62\n\t"
      ".LFUN_00022dc0_60:\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpw %%dx, 0x5f4(%%ebx)\n\t"
      "setne %%dl\n\t"
      "addl $0xa, %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_62\n\t"
      ".LFUN_00022dc0_61:\n\t"
      "pushl $1\n\t"
      "pushl $0x21a\n\t"
      "pushl $0x254910\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00022dc0_62:\n\t"
      "movw 0x5f2(%%ebx), %%cx\n\t"
      "movswl %%cx, %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .LFUN_00022dc0_69\n\t"
      "jmp *.LFUN_00022dc0_jt1(,%%eax,4)\n\t"
      ".LFUN_00022dc0_63:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022dc0_75\n\t"
      "movl $1, %%esi\n\t"
      ".LFUN_00022dc0_64:\n\t"
      "cmpw %%cx, %%si\n\t"
      "movl %%esi, -0x18(%%ebp)\n\t"
      "jne .LFUN_00022dc0_65\n\t"
      "pushl $1\n\t"
      "pushl $0x24c\n\t"
      "pushl $0x254910\n\t"
      "pushl $0x254b10\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00022dc0_65:\n\t"
      "movswl %%si, %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00022dc0_72\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00022dc0_70\n\t"
      "decl %%eax\n\t"
      "jne .LFUN_00022dc0_74\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "call *%[c21590]\n\t"
      "movl -0x18(%%ebp), %%esi\n\t"
      "jmp .LFUN_00022dc0_74\n\t"
      ".LFUN_00022dc0_66:\n\t"
      "cmpw $0, 0x5f4(%%ebx)\n\t"
      "jne .LFUN_00022dc0_75\n\t"
      "movl $3, %%esi\n\t"
      "jmp .LFUN_00022dc0_64\n\t"
      ".LFUN_00022dc0_67:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00022dc0_75\n\t"
      "cmpw $0, 0x5f4(%%ebx)\n\t"
      "jne .LFUN_00022dc0_75\n\t"
      "movl $2, %%esi\n\t"
      "jmp .LFUN_00022dc0_64\n\t"
      ".LFUN_00022dc0_68:\n\t"
      "cmpw $0, 0x5f4(%%ebx)\n\t"
      "jne .LFUN_00022dc0_75\n\t"
      "xorl %%esi, %%esi\n\t"
      "jmp .LFUN_00022dc0_64\n\t"
      ".LFUN_00022dc0_69:\n\t"
      "pushl $1\n\t"
      "pushl $0x246\n\t"
      "pushl $0x254910\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00022dc0_75\n\t"
      ".LFUN_00022dc0_70:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022dc0_71\n\t"
      "pushl $1\n\t"
      "pushl $0x263\n\t"
      "pushl $0x254910\n\t"
      "pushl $0x254afc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00022dc0_71:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "jmp .LFUN_00022dc0_73\n\t"
      ".LFUN_00022dc0_72:\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "call *%[c21640]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00022dc0_74\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00022dc0_74\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl $2, %%esi\n\t"
      "pushl %%ecx\n\t"
      ".LFUN_00022dc0_73:\n\t"
      "call *%[c22390]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00022dc0_74:\n\t"
      "movw %%si, 0x5f2(%%ebx)\n\t"
      ".LFUN_00022dc0_75:\n\t"
      "movw 0x5f2(%%ebx), %%ax\n\t"
      "cmpw $4, %%ax\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movb $0, 0x688(%%ebx)\n\t"
      "jne .LFUN_00022dc0_77\n\t"
      ".LFUN_00022dc0_76:\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_100\n\t"
      ".LFUN_00022dc0_77:\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .LFUN_00022dc0_100\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "cmpl %%esi, %%eax\n\t"
      "movl %%esi, -0x24(%%ebp)\n\t"
      "jne .LFUN_00022dc0_78\n\t"
      "pushl $1\n\t"
      "pushl $0x280\n\t"
      "pushl $0x254910\n\t"
      "pushl $0x254ba4\n\t"
      "call *%[assert]\n\t"
      "pushl %%esi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00022dc0_78:\n\t"
      "leal 0x64c(%%ebx), %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "movl (%%edx), %%esi\n\t"
      "leal 0x658(%%ebx), %%edi\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl %%esi, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%esi\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%esi, 0x4(%%ecx)\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0x1c(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movl 0x31fc38, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "leal 0x28(%%esi), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movw 0x60c(%%ebx), %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .LFUN_00022dc0_84\n\t"
      "movl 0x610(%%ebx), %%edx\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x10, %%ecx\n\t"
      "leal 0xc8(%%esi), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movl 0x114(%%esi), %%ecx\n\t"
      "movl 0xbc(%%edx), %%eax\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x3e(%%ebx), %%cx\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xf\n\t"
      "call *%[cb55b0]\n\t"
      "fadds -0x28(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "addl $0x10, %%esp\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022dc0_79\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022dc0_81\n\t"
      "jmp .LFUN_00022dc0_80\n\t"
      ".LFUN_00022dc0_79:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00022dc0_80:\n\t"
      "movb 0x623(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00022dc0_81\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0xc8(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x64c(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c12140]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl 0xbc(%%eax), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[vsca]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".LFUN_00022dc0_81:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $0x1c, %%eax\n\t"
      "movl %%edi, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl 0xc0(%%edx), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x3e(%%ebx), %%cx\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x10\n\t"
      "call *%[cb55b0]\n\t"
      "fadds -0x28(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "addl $8, %%esp\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022dc0_82\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022dc0_86\n\t"
      "jmp .LFUN_00022dc0_83\n\t"
      ".LFUN_00022dc0_82:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00022dc0_83:\n\t"
      "movl 0x648(%%ebx), %%edx\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movb 0x603(%%ebx), %%dl\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%dl, %%dl\n\t"
      "setne %%al\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[cfaed0]\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0xd4(%%esi)\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $0x28, %%eax\n\t"
      "pushl %%edi\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "movl -0x40(%%ebp), %%edx\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0xd8(%%esi)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "movl -0x3c(%%ebp), %%ecx\n\t"
      "fmuls 0xdc(%%esi)\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "movl -0x38(%%ebp), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl 0xc0(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[vsca]\n\t"
      "addl $0x1c, %%esp\n\t"
      "jmp .LFUN_00022dc0_86\n\t"
      ".LFUN_00022dc0_84:\n\t"
      "cmpw $2, %%ax\n\t"
      "je .LFUN_00022dc0_85\n\t"
      "pushl $1\n\t"
      "pushl $0x2c3\n\t"
      "pushl $0x254910\n\t"
      "pushl $0x254b58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00022dc0_85:\n\t"
      "movl %%edi, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "addl $0x10, %%esi\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      ".LFUN_00022dc0_86:\n\t"
      "flds 0x670(%%ebx)\n\t"
      "leal 0x67c(%%ebx), %%esi\n\t"
      "fadds 0x664(%%ebx)\n\t"
      "fstps 0x664(%%ebx)\n\t"
      "flds 0x674(%%ebx)\n\t"
      "fadds 0x668(%%ebx)\n\t"
      "fstps 0x668(%%ebx)\n\t"
      "flds 0x678(%%ebx)\n\t"
      "fadds 0x66c(%%ebx)\n\t"
      "fstps 0x66c(%%ebx)\n\t"
      "flds 0x664(%%ebx)\n\t"
      "fadds (%%edi)\n\t"
      "fstps (%%esi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fadds 0x668(%%ebx)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fadds 0x66c(%%ebx)\n\t"
      "fstps 0x8(%%esi)\n\t"
      "movl 0x158(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00022dc0_87\n\t"
      "movl 0x18(%%ebx), %%edx\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[useat]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_00022dc0_95\n\t"
      ".LFUN_00022dc0_87:\n\t"
      "movb 0x508(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      "je .LFUN_00022dc0_88\n\t"
      "addl $0xb0, %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c12170]\n\t"
      "fcomps 0x253f44\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00022dc0_90\n\t"
      "movl -0x1c(%%ebp), %%edi\n\t"
      "addl $0x40, %%edi\n\t"
      "jmp .LFUN_00022dc0_89\n\t"
      ".LFUN_00022dc0_88:\n\t"
      "addl $0xa4, %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c12170]\n\t"
      "fcomps 0x253f44\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00022dc0_90\n\t"
      "movl -0x1c(%%ebp), %%edi\n\t"
      "addl $0x34, %%edi\n\t"
      ".LFUN_00022dc0_89:\n\t"
      "pushl %%edi\n\t"
      "call *%[c12170]\n\t"
      "fcomps 0x253f44\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022dc0_91\n\t"
      ".LFUN_00022dc0_90:\n\t"
      "movl %%edi, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%edi, -0x18(%%ebp)\n\t"
      "jne .LFUN_00022dc0_92\n\t"
      ".LFUN_00022dc0_91:\n\t"
      "leal 0x120(%%ebx), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_95\n\t"
      ".LFUN_00022dc0_92:\n\t"
      "flds 0x12c(%%ebx)\n\t"
      "leal 0x12c(%%ebx), %%edi\n\t"
      "fsubs (%%esi)\n\t"
      "leal -0x40(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsubs 0x8(%%esi)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022dc0_93\n\t"
      "movl $0, -0x38(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_94\n\t"
      ".LFUN_00022dc0_93:\n\t"
      "leal 0x174(%%ebx), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "movl %%ecx, -0x3c(%%ebp)\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      ".LFUN_00022dc0_94:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x18(%%ebx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a93e0]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_00022dc0_95:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0x622(%%ebx), %%dl\n\t"
      "leal -0x3(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal 0x68c(%%ebx), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movb 0x603(%%ebx), %%al\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testb %%al, %%al\n\t"
      "setne %%cl\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[cfd400]\n\t"
      "addl $0x24, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00022dc0_96\n\t"
      "pushl $1\n\t"
      "pushl $0x310\n\t"
      "pushl $0x254910\n\t"
      "pushl $0x254aec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00022dc0_96:\n\t"
      "pushl %%edi\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00022dc0_97\n\t"
      "flds 0x694(%%ebx)\n\t"
      "pushl $1\n\t"
      "pushl $0x311\n\t"
      "pushl $0x254910\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x690(%%ebx)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x254ac8\n\t"
      "pushl $0x254a24\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00022dc0_97:\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "sete %%al\n\t"
      "movb %%al, 0x688(%%ebx)\n\t"
      "flds (%%esi)\n\t"
      "fsubs -0x34(%%ebp)\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "leal -0x4c(%%ebp), %%edx\n\t"
      "flds 0x4(%%esi)\n\t"
      "pushl %%edx\n\t"
      "fsubs -0x30(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "flds 0x8(%%esi)\n\t"
      "pushl %%edx\n\t"
      "fsubs -0x2c(%%ebp)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "call *%[c41590]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022dc0_98\n\t"
      "movb 0x603(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movw $0, 0x5fa(%%ebx)\n\t"
      "je .LFUN_00022dc0_76\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_100\n\t"
      ".LFUN_00022dc0_98:\n\t"
      "incw 0x5fa(%%ebx)\n\t"
      "movw 0x5fa(%%ebx), %%ax\n\t"
      "incw 0x5f4(%%ebx)\n\t"
      "cmpw $0x2d, %%ax\n\t"
      "movl $7, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jl .LFUN_00022dc0_100\n\t"
      "cmpw %%cx, 0x268(%%ebx)\n\t"
      "jl .LFUN_00022dc0_100\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl $0xffffffff, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .LFUN_00022dc0_99\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x18(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00022dc0_99:\n\t"
      "movl 0x18(%%ebx), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xe\n\t"
      "call *%[c46f10]\n\t"
      "addl $0x1c, %%esp\n\t"
      "movw $0, 0x5fa(%%ebx)\n\t"
      ".LFUN_00022dc0_100:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb $0, -0x14(%%ebp)\n\t"
      "movb $0, -0x24(%%ebp)\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      "popl %%edi\n\t"
      "je .LFUN_00022dc0_104\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "movb 0x602(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x78(%%esi), %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "jne .LFUN_00022dc0_105\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00022dc0_108\n\t"
      "cmpw $0, 0x5f8(%%ebx)\n\t"
      "jne .LFUN_00022dc0_109\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x3e(%%ebx), %%ax\n\t"
      "movb $1, -0x14(%%ebp)\n\t"
      "movl $0x3f800000, -0x1c(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl $0xa\n\t"
      "call *%[cb55b0]\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c21270]\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00022dc0_101\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00022dc0_101\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      "jmp .LFUN_00022dc0_102\n\t"
      ".LFUN_00022dc0_101:\n\t"
      "flds -0x18(%%ebp)\n\t"
      ".LFUN_00022dc0_102:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "fld %%st(0)\n\t"
      "fstps 0xc(%%eax)\n\t"
      "flds 0x253394\n\t"
      ".byte 0xd8, 0xf1\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fistps -0x20(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "cmpw $2, %%ax\n\t"
      "jge .LFUN_00022dc0_103\n\t"
      "movl $2, %%eax\n\t"
      "movw %%ax, 0x5f8(%%ebx)\n\t"
      "jmp .LFUN_00022dc0_109\n\t"
      ".LFUN_00022dc0_103:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movw %%ax, 0x5f8(%%ebx)\n\t"
      "jmp .LFUN_00022dc0_109\n\t"
      ".LFUN_00022dc0_104:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb 0x602(%%ebx), %%al\n\t"
      "je .LFUN_00022dc0_107\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022dc0_106\n\t"
      ".LFUN_00022dc0_105:\n\t"
      "movb $0, 0x602(%%ebx)\n\t"
      "jmp .LFUN_00022dc0_109\n\t"
      ".LFUN_00022dc0_106:\n\t"
      "movb $1, -0x24(%%ebp)\n\t"
      "jmp .LFUN_00022dc0_109\n\t"
      ".LFUN_00022dc0_107:\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00022dc0_109\n\t"
      ".LFUN_00022dc0_108:\n\t"
      "movb $1, -0x14(%%ebp)\n\t"
      "movl $0x3f800000, -0x1c(%%ebp)\n\t"
      ".LFUN_00022dc0_109:\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c3c2d0]\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c3c330]\n\t"
      "movw -0x8(%%ebp), %%cx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%esi\n\t"
      "movw %%cx, 0x8(%%edx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00022dc0_jt0:\n\t"
      ".long .LFUN_00022dc0_58\n\t"
      ".long .LFUN_00022dc0_59\n\t"
      ".long .LFUN_00022dc0_60\n\t"
      ".long .LFUN_00022dc0_57\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00022dc0_jt1:\n\t"
      ".long .LFUN_00022dc0_63\n\t"
      ".long .LFUN_00022dc0_67\n\t"
      ".long .LFUN_00022dc0_66\n\t"
      ".long .LFUN_00022dc0_67\n\t"
      ".long .LFUN_00022dc0_68\n\t"
      ".text\n\t"
      :
      : [dget] "m"(b22dc0_dget), [tag] "m"(b22dc0_tag), [c211f0] "m"(b22dc0_c211f0), [c3b270] "m"(b22dc0_c3b270), [get] "m"(b22dc0_get), [assert] "m"(b22dc0_assert), [exitfn] "m"(b22dc0_exitfn), [c121a0] "m"(b22dc0_c121a0), [c3b320] "m"(b22dc0_c3b320), [c1aae70] "m"(b22dc0_c1aae70), [c1aaa90] "m"(b22dc0_c1aaa90), [c3c370] "m"(b22dc0_c3c370), [c46f10] "m"(b22dc0_c46f10), [cb55b0] "m"(b22dc0_cb55b0), [c20f80] "m"(b22dc0_c20f80), [c121e0] "m"(b22dc0_c121e0), [gseed] "m"(b22dc0_gseed), [rmreal] "m"(b22dc0_rmreal), [ftol] "m"(b22dc0_ftol), [c22010] "m"(b22dc0_c22010), [elem] "m"(b22dc0_elem), [cba6c0] "m"(b22dc0_cba6c0), [c1ad60] "m"(b22dc0_c1ad60), [c416e0] "m"(b22dc0_c416e0), [cfd400] "m"(b22dc0_cfd400), [c2a360] "m"(b22dc0_c2a360), [gtime] "m"(b22dc0_gtime), [c21130] "m"(b22dc0_c21130), [c21590] "m"(b22dc0_c21590), [c21640] "m"(b22dc0_c21640), [c22390] "m"(b22dc0_c22390), [c12140] "m"(b22dc0_c12140), [vsca] "m"(b22dc0_vsca), [cfaed0] "m"(b22dc0_cfaed0), [useat] "m"(b22dc0_useat), [c12170] "m"(b22dc0_c12170), [mag] "m"(b22dc0_mag), [c1a93e0] "m"(b22dc0_c1a93e0), [c21fb0] "m"(b22dc0_c21fb0), [c8d9d0] "m"(b22dc0_c8d9d0), [c41590] "m"(b22dc0_c41590), [c21270] "m"(b22dc0_c21270), [c3c2d0] "m"(b22dc0_c3c2d0), [c3c330] "m"(b22dc0_c3c330)
      : "memory");
}
#else
#error "FUN_00022dc0: clang naked draft required"
#endif

/* --- actor_combat.obj orphan shells (2026-07-26) --- */

/* 0x22b40 — Validate aim point and cache on actor when clear. */
#if defined(__i386__) && defined(__GNUC__)
__attribute__((regparm(2)))
#endif
/* FUN_00022b40 (0x22b40) — readable C lift. */
char FUN_00022b40(int actor_handle, float *aim_vector)
{
  char *actor;
  char *actv;
  char ok;
  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  actv = (char *)tag_get(0x61637476, *(int *)(actor + 0x5c));
  ok = FUN_00021ae0(
      actor_handle,
      *(float *)(actv + 0x188),
      *(float *)(actv + 0x19c),
      aim_vector,
      0);
  if (!ok) {
    return 0;
  }
  *(float *)(actor + 0x6a8) = aim_vector[0];
  *(float *)(actor + 0x6ac) = aim_vector[1];
  *(float *)(actor + 0x6b0) = aim_vector[2];
  return 1;
}

