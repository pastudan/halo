/* action_vehicle.c — AI actor "enter vehicle" action setup.
 *
 * Corresponds to action_vehicle.obj.
 * Assertion path: c:\halo\SOURCE\ai\action_vehicle.c
 *
 * Recovered by lifting FUN_0001b750 from cachebeta.xbe (v01.10.12.2276).
 * This function was mis-filed under real_math.obj by whole-object address-range
 * grouping; its behaviour (actor datum lookup, vehicle-seat attach-point query,
 * actor_move_to_point) and the embedded assert path place it in
 * ai/action_vehicle.c.
 */

#include "../../common.h"

/* FUN_0001b750 (0x1b750) — Build the state buffer for an actor's "enter
 * vehicle" action and start the actor moving toward the entry point.
 *
 * Zeroes the 0x4c-byte action state buffer, then (only when the actor is not
 * already assigned to a vehicle: actor+0x158 == -1 and actor+0x6 == 0) verifies
 * the target object is a vehicle whose speed (object+0x38) is at or above the
 * global threshold at 0x253398 and whose object+0xb6 bit 2 is clear. On success
 * it records the vehicle handle / seat index into the state buffer, computes
 * the seat attach transform (FUN_0001aeb0 -> FUN_0001b280), and issues an
 * actor_move_to_point toward the computed entry position.
 *
 * Returns 1 only when every check passes and actor_move_to_point succeeds;
 * otherwise 0.
 *
 * Confirmed (delinked disasm 0x1b750-0x1b897):
 *   datum pool = actor_data (*0x6325a4); actor+0x18 = unit_handle.
 *   object_get_and_verify_type(vehicle_handle, 3); object+0x38 float speed.
 *   FPU: continue iff speed >= *(float*)0x253398 (fld speed; fcomp threshold).
 *   object+0xb6 is a byte; continue iff (~(b>>2)) & 1 (bit 2 clear).
 *   state buffer: +0 = vehicle handle (dword), +4 = seat index (word), +6 = 0.
 *   FUN_0001b280: ECX = actor_handle, EAX = vehicle_handle, out at
 * buf+0x30/+0x48. Note: the second datum_get(actor_data, actor_handle) is
 * present in the original; its result is immediately overwritten by
 * object_get_and_verify_type and never used (preserved here for fidelity).
 */
char FUN_0001b750(int actor_handle, int vehicle_handle, int16_t seat_index,
                  short *state_data)
{
  char *actor;
  char *object;
  volatile long ok; /* volatile: forces the memory store of ok=0, matching
                     * original VC71 codegen (permuter, 86.7% -> 90.8%). */
  float attach[9];

  actor = (char *)datum_get(actor_data, actor_handle);
  ok = 0;
  assert_halt(state_data != 0);
  csmemset(state_data, 0, 0x4c);
  if (*(int *)(actor + 0x158) == -1 && *(char *)(actor + 6) == 0) {
    (void)datum_get(actor_data, actor_handle);
    object = (char *)object_get_and_verify_type(vehicle_handle, 3);
    if (*(float *)(object + 0x38) >= *(float *)0x253398 &&
        (~(*(unsigned char *)(object + 0xb6) >> 2) & 1) != 0) {
      *(int *)state_data = vehicle_handle;
      *(int16_t *)((char *)state_data + 4) = seat_index;
      *((char *)state_data + 6) = 0;
      if (unit_has_animation_to_enter_seat(
            *(int *)(actor + 0x18), vehicle_handle, seat_index) != '\0' &&
          FUN_0001aeb0(actor_handle, vehicle_handle, seat_index, 1, &attach[0],
                       &attach[3], &attach[6], 0, 0, 0, 0) != '\0' &&
          FUN_0001b280(actor_handle, vehicle_handle, &attach[0], &attach[3],
                       &attach[6], 0, (float *)((char *)state_data + 0x30),
                       (int *)((char *)state_data + 0x48)) != '\0' &&
          actor_move_to_point(
            actor_handle, (float *)((char *)state_data + 0x30),
            *(int *)((char *)state_data + 0x48), vehicle_handle) != '\0') {
        return 1;
      }
    }
  }
  return ok;
}
/* --- action_vehicle.obj batch drafts (2026-07-26) --- */

/* 0x1aeb0 — score / produce seat-enter attach points for an actor→vehicle. */
char FUN_0001aeb0(int actor_handle, int vehicle_handle, short seat_index,
                  int param_4, float *out_attach0, float *out_attach1,
                  float *out_attach2, int param_8, int param_9, int param_10,
                  int param_11)
{
  char *actor;
  char *actr;
  char *actv;
  float attach0[3];
  float attach1[3];
  float attach2[3];
  float world[3];
  float dir[3];
  float iter[6];
  float dist;
  float score;
  char flag_near;
  char flag_mid;
  char flag_far;
  int *prop;
  int other_handle;
  char *other;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  actr = (char *)tag_get(0x61637472, *(int *)(actor + 0x58)); /* 'actr' */
  actv = (char *)tag_get(0x61637476, *(int *)(actor + 0x5c)); /* 'actv' */

  if (unit_seat_filled(vehicle_handle, seat_index))
    return 0;
  if ((*(unsigned char *)(actr + 4) & 8) != 0 &&
      !unit_seat_allow_noncombatants(vehicle_handle, seat_index))
    return 0;
  if (!unit_get_seat_enter_position(*(int *)(actor + 0x18), vehicle_handle,
                                    seat_index, attach0, attach1, attach2))
    return 0;

  object_get_world_position(vehicle_handle, (void *)world);
  (void)world;

  dir[0] = attach1[0] - attach0[0];
  dir[1] = attach1[1] - attach0[1];
  dir[2] = 0.0f;
  if (magnitude3d(dir) == 0.0f) {
    dir[0] = *(float *)(actor + 0x174);
    dir[1] = *(float *)(actor + 0x178);
    dir[2] = *(float *)(actor + 0x17c);
  }

  {
    float dx0 = attach0[0] - *(float *)(actor + 0x12c);
    float dy0 = attach0[1] - *(float *)(actor + 0x130);
    float dx1 = attach1[0] - *(float *)(actor + 0x12c);
    float dy1 = attach1[1] - *(float *)(actor + 0x130);
    float d0 = sqrtf(dx0 * dx0 + dy0 * dy0);
    float d1 = sqrtf(dx1 * dx1 + dy1 * dy1);
    if (d1 < d0) {
      dist = d1;
    } else {
      dist = d0;
    }
  }

  FUN_00064540((int *)iter, actor_handle);
  for (prop = (int *)FUN_00064570((int *)iter); prop != 0;
       prop = (int *)FUN_00064570((int *)iter)) {
    if (*(char *)((char *)prop + 0x60) != 0)
      continue;
    other_handle = *(int *)((char *)prop + 0x1c);
    if (other_handle == -1)
      continue;
    other = (char *)datum_absolute_index_to_index(*(data_t **)0x6325a4,
                                                  other_handle);
    if (other == 0)
      continue;
    if (*(int16_t *)(other + 0x6c) != 9)
      continue;
    if (*(int *)(other + 0x9c) != vehicle_handle)
      continue;
    if (*(int16_t *)(other + 0xa0) != seat_index) {
      (void)unit_seat_is_driver(vehicle_handle, *(int16_t *)(other + 0xa0));
      continue;
    }
    {
      float ox = *(float *)(other + 0xcc) - *(float *)(other + 0x12c);
      float oy = *(float *)(other + 0xd0) - *(float *)(other + 0x130);
      if ((ox * ox + oy * oy) < dist * dist)
        return 0;
    }
  }

  {
    char *vehicle = (char *)object_get_and_verify_type(vehicle_handle, 2);
    if (!param_4) {
      (void)tag_get(0x76656869, *(int *)vehicle); /* 'vehi' */
      (void)unit_seat_is_driver(vehicle_handle, seat_index);
    }
  }

  {
    float dx = attach1[0] - *(float *)(actor + 0x12c);
    float dy = attach1[1] - *(float *)(actor + 0x130);
    float facing_dot =
        dy * *(float *)(actor + 0x178) + dx * *(float *)(actor + 0x174);
    float scratch[3];

    scratch[0] = dx;
    scratch[1] = dy;
    scratch[2] = 0.0f;
    (void)magnitude3d(scratch);

    flag_near = 1;
    if (dist < *(float *)0x2533c4)
      flag_near = 0;

    flag_mid = 1;
    if (!(facing_dot > *(float *)0x253f3c))
      flag_mid = 0;

    flag_far = 0;
    if (dist < *(float *)0x253f38 && facing_dot > 0.0f)
      flag_far = 1;

    score = *(float *)0x253f34 / (dist + *(float *)0x2533c8);
    if ((signed char)actv[0] < 0) {
      if (!unit_seat_is_gunner(vehicle_handle, seat_index))
        score += *(float *)0x253f30;
    } else if (unit_seat_is_gunner(vehicle_handle, seat_index)) {
      score += *(float *)0x253f30;
    }

    if (out_attach0) {
      out_attach0[0] = attach0[0];
      out_attach0[1] = attach0[1];
      out_attach0[2] = attach0[2];
    }
    if (out_attach1) {
      out_attach1[0] = dir[0];
      out_attach1[1] = dir[1];
      out_attach1[2] = dir[2];
    }
    if (out_attach2) {
      out_attach2[0] = attach2[0];
      out_attach2[1] = attach2[1];
      out_attach2[2] = attach2[2];
    }
    if (param_8)
      *(float *)param_8 = score;
    if (param_9)
      *(char *)param_9 = flag_near;
    if (param_10)
      *(char *)param_10 = flag_mid;
    if (param_11)
      *(char *)param_11 = flag_far;
  }

  return 1;
}

/* FUN_0001b280 (0x1b280) — XBE naked draft (batch 224). */
#if defined(__clang__)
static void *(*const b1b280_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1b280_get)(int, int) = object_get_and_verify_type;
static void *(*const b1b280_tag)(int, int) = tag_get;
static void (*const b1b280_c1aae0)(int object_handle, float *center, float *radius) = FUN_0001aae0;
static int (*const b1b280_gtime)(void) = game_time_get;
static void (*const b1b280_c10b600)(float *in, float *out) = perpendicular2d;
static float (*const b1b280_mag)(float *) = magnitude3d;
static float *(*const b1b280_vsca)(float *, float *, float, float *) = vector3d_scale_add;
static void *(*const b1b280_gbsp)(void) = global_collision_bsp_get;
static char (*const b1b280_c149480)(int collision_flags, int bsp, short flags, int breakable_surfaces, int origin, int direction, float max_t, float *result) = collision_bsp_test_vector;

__attribute__((naked, noinline))
char FUN_0001b280(int actor_handle __attribute__((unused)), int object_handle __attribute__((unused)), float *in_attach0 __attribute__((unused)), float *in_attach1 __attribute__((unused)), float *in_attach2 __attribute__((unused)), int param_6 __attribute__((unused)), float *out_position __attribute__((unused)), int *out_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x464, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "pushl $3\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0x331f58, %%edx\n\t"
      "andl $0xffff, %%esi\n\t"
      "imull $0x657c, %%esi, %%esi\n\t"
      "addl %%edx, %%esi\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "je .LFUN_0001b280_1\n\t"
      "movb (%%eax), %%al\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "jmp .LFUN_0001b280_2\n\t"
      ".LFUN_0001b280_1:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_0001b280_2:\n\t"
      "testb $0x10, 0x17c(%%edi)\n\t"
      "jne .LFUN_0001b280_17\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1aae0]\n\t"
      "flds 0x280(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0xc, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0001b280_3\n\t"
      "movl 0x280(%%edi), %%eax\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      ".LFUN_0001b280_3:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "jne .LFUN_0001b280_4\n\t"
      "flds (%%ecx)\n\t"
      "fsubs -0x10(%%ebp)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fsubs -0x8(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fcoms 0x253398\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0001b280_5\n\t"
      "fstp %%st(0)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_0001b280_4:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "jmp .LFUN_0001b280_8\n\t"
      ".LFUN_0001b280_5:\n\t"
      "fadds 0x2533e4\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0001b280_6\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "jmp .LFUN_0001b280_7\n\t"
      ".LFUN_0001b280_6:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0001b280_7:\n\t"
      "movl %%ecx, %%eax\n\t"
      ".LFUN_0001b280_8:\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fsubs 0x12c(%%edi)\n\t"
      "movl (%%eax), %%ebx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "addl $0x12c, %%edi\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "flds -0xc(%%ebp)\n\t"
      "movl %%ebx, -0x24(%%ebp)\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fsubs (%%edi)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fsubs -0x24(%%ebp)\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsubs -0x20(%%ebp)\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "jne .LFUN_0001b280_9\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "flds (%%ecx)\n\t"
      "fsubs (%%eax)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fchs\n\t"
      "fxch %%st(2)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fadds -0x2c(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x28(%%ebp)\n\t"
      "fstp %%st(1)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x253f4c\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0001b280_9\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_0001b280_9:\n\t"
      "call *%[gtime]\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      "movl %%eax, 0xc4(%%esi)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "movl %%edi, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "leal 0xc8(%%esi), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      ".byte 0xde, 0xc1\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "fcoms 0x2533c0\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "leal 0xd4(%%esi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "leal 0xe4(%%esi), %%eax\n\t"
      "movl %%ebx, (%%eax)\n\t"
      "movl %%edx, 0xe0(%%esi)\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "fnstsw %%ax\n\t"
      "movl $0x7f7fffff, 0xf0(%%esi)\n\t"
      "testb $0x41, %%ah\n\t"
      "movb $0, 0xf4(%%esi)\n\t"
      "jne .LFUN_0001b280_16\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x40(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x44(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      ".byte 0xde, 0xf1\n\t"
      "fcoms 0x2533c0\n\t"
      "fsts 0xf0(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0001b280_10\n\t"
      "fcomps 0x253f48\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0001b280_11\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10b600]\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x40(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0001b280_13\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "jmp .LFUN_0001b280_12\n\t"
      ".LFUN_0001b280_10:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0001b280_11:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0001b280_17\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x48(%%ebp)\n\t"
      ".LFUN_0001b280_12:\n\t"
      "fchs\n\t"
      "fstps -0x14(%%ebp)\n\t"
      ".LFUN_0001b280_13:\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0001b280_17\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls 0x253f38\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fsubs (%%edi)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x253f44\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0001b280_15\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x2533d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0001b280_15\n\t"
      "flds 0x8(%%ebp)\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "fsqrt\n\t"
      "pushl %%eax\n\t"
      "leal -0x4c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "call *%[c10b600]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0001b280_14\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0xc(%%ebp)\n\t"
      ".LFUN_0001b280_14:\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0001b280_15\n\t"
      "flds 0x253f40\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "fsubs 0x8(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[vsca]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0001b280_15:\n\t"
      "movl -0x3c(%%ebp), %%eax\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "movl -0x34(%%ebp), %%edx\n\t"
      "movb $1, 0xf4(%%esi)\n\t"
      "addl $0xf8, %%esi\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      "movl %%edx, 0x8(%%esi)\n\t"
      "jmp .LFUN_0001b280_17\n\t"
      ".LFUN_0001b280_16:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0001b280_17:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_0001b280_18\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "movb %%cl, (%%eax)\n\t"
      ".LFUN_0001b280_18:\n\t"
      "call *%[gbsp]\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "movl 0x31fc44, %%ecx\n\t"
      "fadds (%%ecx)\n\t"
      "leal -0x464(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x7f7fffff\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fadds 0x4(%%ecx)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fadds 0x8(%%ecx)\n\t"
      "movl 0x31fc50, %%ecx\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds (%%ecx)\n\t"
      "fmuls 0x2533d8\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fmuls 0x2533d8\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "fmuls 0x2533d8\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "call *%[c149480]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0001b280_19\n\t"
      "flds -0x24(%%ebp)\n\t"
      "movl -0x45c(%%ebp), %%eax\n\t"
      "fmuls -0x464(%%ebp)\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "fstps (%%eax)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x464(%%ebp)\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x464(%%ebp)\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fstps 0x8(%%eax)\n\t"
      "movb $1, %%al\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0001b280_19:\n\t"
      "xorb %%al, %%al\n\t"
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
      : [dget] "m"(b1b280_dget), [get] "m"(b1b280_get), [tag] "m"(b1b280_tag), [c1aae0] "m"(b1b280_c1aae0), [gtime] "m"(b1b280_gtime), [c10b600] "m"(b1b280_c10b600), [mag] "m"(b1b280_mag), [vsca] "m"(b1b280_vsca), [gbsp] "m"(b1b280_gbsp), [c149480] "m"(b1b280_c149480)
      : "memory");
}
#else
#error "FUN_0001b280: clang naked draft required"
#endif



