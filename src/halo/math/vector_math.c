#include "x87_math.h"

/* FUN_00012140 (0x12140) — Subtract two 3D vectors: result = b - a.
 * Confirmed: cdecl, 3 pointer args. Pure FPU leaf.
 * Confirmed: arg1=a [EBP+0x8], arg2=b [EBP+0xc], arg3=result [EBP+0x10].
 * Confirmed: FLD [ECX] / FSUB [EDX] / FSTP [EAX] where ECX=b, EDX=a,
 * EAX=result. */
void FUN_00012140(float *a, float *b, float *result)
{
  result[0] = b[0] - a[0];
  result[1] = b[1] - a[1];
  result[2] = b[2] - a[2];
}

/* 0x12170 — FUN_00012170: squared magnitude of a 3D vector.
 *
 * Computes vector[0]^2 + vector[1]^2 + vector[2]^2 and returns it.
 *
 * Confirmed: loads three floats from [arg0+0], [arg0+4], and [arg0+8].
 * Confirmed: x87 stack sequence squares each component and accumulates with
 *   FADDP; no globals or calls.
 * Confirmed: returns the accumulated sum in ST0.
 */
float FUN_00012170(float *vector)
{
  return vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2];
}

/* 0x121a0 — distance_squared3d: squared distance between two 3D points.
 *
 * Computes (b[0]-a[0])^2 + (b[1]-a[1])^2 + (b[2]-a[2])^2 and returns it.
 *
 * Confirmed: loads from [arg1+0/4/8] and subtracts [arg0+0/4/8].
 * Confirmed: x87 sequence squares each component delta and sums with FADDP.
 * Confirmed: returns in ST0; no globals or calls.
 */
float distance_squared3d(const float *a, const float *b)
{
  float dx = b[0] - a[0];
  float dy = b[1] - a[1];
  float dz = b[2] - a[2];

  return dx * dx + dy * dy + dz * dz;
}

float FUN_000121e0(float min, float max)
{
  int *seed = get_global_random_seed_address();
  return random_real_range(seed, min, max);
}

/* 0x12e50 — FUN_00012e50: check if actor is in a valid 'swarm flying' state
 * and its state timer has not yet expired.
 *
 * Looks up the actor record via actor_data (0x6325a4) and checks:
 *   actor+0xa0 (short): must equal 3 (swarm flying state)
 *   actor+0xa7 (char):  must be non-zero (active flag)
 * If both conditions hold, reads actor+0xac (int, state end time) and
 * returns true iff game_time_get() <= actor+0xac + 0x1e.
 *
 * Confirmed: cdecl, 1 stack arg (actor_handle). Returns bool.
 * Confirmed: ESI = datum_get result + 0x9c; offsets relative to ESI.
 * Confirmed: SETGE AL after CMP EDX,EAX (EDX=*(int*)(ESI+0x10)+0x1e,
 *   AX=game_time_get()), so bVar1 = (EDX >= EAX). */
bool FUN_00012e50(int actor_handle)
{
  char *actor;
  bool result;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  result = false;
  if (*(short *)(actor + 0xa0) == 3 && *(char *)(actor + 0xa7) != '\0') {
    result = *(int *)(actor + 0xac) + 0x1e >= game_time_get();
  }
  return result;
}

/* magnitude3d (0x12f10) — readable C lift from XBE leaf (normalize2d).
 * Returns 2D magnitude; normalizes v[0],v[1] in place when |mag| >= 1e-4. */
float magnitude3d(float *v)
{
  float mag;
  float scale;

  mag = x87_sqrt(v[0] * v[0] + v[1] * v[1]);
  /* Match x87: only early-out on true less-than; NaN falls into normalize. */
  if (!((double)fabsf(mag) < *(double *)0x2533d0)) {
    scale = *(float *)0x2533c8 / mag;
    v[0] = v[0] * scale;
    v[1] = v[1] * scale;
    return mag;
  }
  return *(float *)0x2533c0;
}

/* 0x12f80 — Compute out = base + scale * direction (3-component). */
float *vector3d_scale_add(float *base, float *direction, float scale, float *out)
{
  out[0] = scale * direction[0] + base[0];
  out[1] = scale * direction[1] + base[1];
  out[2] = scale * direction[2] + base[2];
  return out;
}

/* Normalize a 3D vector in-place.
 * Computes the magnitude (Euclidean length) of v, and if it exceeds a
 * small epsilon threshold (~0.0001), divides each component by the
 * magnitude so v becomes a unit vector. Returns the original magnitude,
 * or 0.0f if the vector was too small to normalize. */
float normalize3d(float *v)
{
  float mag;
  float scale;

  mag = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
  /* Original (0x13010): FCOMP ABS(mag) against the *double* 0.0001 at 0x2533d0
     and normalize only when |mag| >= 0.0001, otherwise return 0.0 (0x2533c0)
     leaving v unchanged.  A prior lift mis-read 0x2533d0 as a float
     (-3.69e19) — making the threshold always-true — and substituted a
     `mag == 0.0f` guard.  That let denormalized / near-zero (but nonzero)
     vectors be divided into a non-unit result that later tripped
     assert_valid_real_normal3d (actor_looking.c:529 via FUN_00028660).  Read
     the threshold as a double to restore the original early-out. */
  if (fabsf(mag) >= *(double *)0x2533d0) {
    scale = 1.0f / mag;
    v[0] = v[0] * scale;
    v[1] = v[1] * scale;
    v[2] = v[2] * scale;
    return mag;
  }
  return 0.0f;
}

/* FUN_00013070 (0x13070) — Dot product of two 3D vectors.
 * Confirmed: cdecl, 2 pointer args. Pure FPU leaf.
 * Confirmed: computes a.z*b.z + a.y*b.y + a.x*b.x (accumulation order). */
float FUN_00013070(float *a, float *b)
{
  return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

/* 0x130d0 — Ray-cast between two points. Computes the direction vector
 * (point_b - point_a) and delegates to FUN_0014df70 for the actual
 * collision test along that direction from point_a. */
bool FUN_000130d0(uint32_t collision_flags, float *point_a, float *point_b,
                  int max_distance, int16_t *collision_result)
{
  float direction[3];

  direction[0] = point_b[0] - point_a[0];
  direction[1] = point_b[1] - point_a[1];
  direction[2] = point_b[2] - point_a[2];
  return FUN_0014df70(collision_flags, point_a, direction, max_distance,
                      collision_result);
}

/* 0x213c0 — Compute out = a + b (3-component). */
void vector3d_add(float *a, float *b, float *out)
{
  out[0] = a[0] + b[0];
  out[1] = a[1] + b[1];
  out[2] = a[2] + b[2];
}

/* 0x21fb0 — valid_real_normal3d: check whether a 3D vector is a valid
 * unit normal (length within epsilon of 1.0).
 *
 * Computes squared_length = dot(v, v) and returns true if
 * |squared_length - 1.0f| < 0.001f.
 *
 * Also rejects NaN/infinity by testing the exponent bits.
 *
 * Confirmed: FLD / FMUL / FADDP computes dot(v, v) on x87 stack.
 * Confirmed: FSUB [0x2533c8] subtracts 1.0f.
 * Confirmed: FABS / FCOMP double ptr [0x2549d8] compares against
 * (double)0.001f. */
bool valid_real_normal3d(float *v)
{
  float sq_len = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
  float diff = sq_len - 1.0f;

  if ((*(unsigned int *)&diff & 0x7f800000) == 0x7f800000) {
    return 0;
  }

  return fabsf(diff) < 0.001f;
}

/* 0x28610 — Validate that a 2D vector is a unit normal.
 * Checks that x²+y² is within epsilon of 1.0 and not NaN/Inf. */
int valid_real_normal2d(float *v)
{
  float diff = (v[0] * v[0] + v[1] * v[1]) - 1.0f;
  if ((*(uint32_t *)&diff & 0x7f800000) == 0x7f800000)
    return 0;
  if (fabsf(diff) < *(double *)0x2549d8)
    return 1;
  return 0;
}

/* 0x12ea0 — sqrtf wrapper. */
float FUN_00012ea0(float x)
{
  return sqrtf(x);
}

/* 0x12eb0 — Scale a 2D vector: out = scale * in. */
void FUN_00012eb0(float *in, float scale, float *out)
{
  out[0] = scale * in[0];
  out[1] = scale * in[1];
}

/* 0x12ed0 — Squared magnitude of a 2D vector. */
float FUN_00012ed0(float *v)
{
  return v[0] * v[0] + v[1] * v[1];
}

/* 0x12ef0 — Magnitude of a 2D vector. */
float FUN_00012ef0(float *v)
{
  return sqrtf(v[0] * v[0] + v[1] * v[1]);
}

/* 0x12f60 — Dot product of two 2D vectors. */
float FUN_00012f60(float *a, float *b)
{
  return a[0] * b[0] + a[1] * b[1];
}

/* 0x12fb0 — Scale a 3D vector: out = scale * in. */
void FUN_00012fb0(float *in, float scale, float *out)
{
  out[0] = scale * in[0];
  out[1] = scale * in[1];
  out[2] = scale * in[2];
}

/* 0x12fe0 — Magnitude of a 3D vector. */
float FUN_00012fe0(float *v)
{
  return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

/* 0x13090 — Subtract two 3D vectors: out = a - b. */
void FUN_00013090(float *a, float *b, float *out)
{
  out[0] = a[0] - b[0];
  out[1] = a[1] - b[1];
  out[2] = a[2] - b[2];
}

/* 0x21370 — Sine of a float (x87 FSIN). */
float FUN_00021370(float x)
{
#if defined(_MSC_VER) && !defined(__clang__)
  return (float)sin((double)x);   /* VC71 /Oi inlines as FSIN (matches original) */
#else
  return x87_fsin(x);
#endif
}

/* 0x21380 — Cosine of a float (x87 FCOS). */
float FUN_00021380(float x)
{
#if defined(_MSC_VER) && !defined(__clang__)
  return (float)cos((double)x);   /* VC71 /Oi inlines as FCOS (matches original) */
#else
  return x87_fcos(x);
#endif
}

/* 0x21390 — Tangent of a float (x87 FPTAN). */
float FUN_00021390(float x)
{
#if defined(_MSC_VER) && !defined(__clang__)
  return (float)tan((double)x);   /* VC71 /Oi inlines as FPTAN (matches original) */
#else
  return x87_fsin(x) / x87_fcos(x);
#endif
}

/* 0x213a0 — 2D cross product (z-component): a[0]*b[1] - a[1]*b[0]. */
float FUN_000213a0(float *a, float *b)
{
  return b[1] * a[0] - a[1] * b[0];
}

/* 0x21410 — Check if a float is valid (not NaN/Inf). */
int FUN_00021410(uint32_t bits)
{
  return (bits & 0x7f800000) != 0x7f800000;
}

/* 0x21f70 — Float approximate equality check within epsilon. */
int FUN_00021f70(float a, float b)
{
  float diff = a - b;
  if ((*(uint32_t *)&diff & 0x7f800000) == 0x7f800000)
    return 0;
  if (fabsf(diff) < *(double *)0x2549d8)
    return 1;
  return 0;
}

/* 0x12a80 — action_alert: decrement squad-vehicle-passenger counter
 * if actor is in state 4 (vehicle) and target's state is 3. */
void FUN_00012a80(int actor_handle)
{
  int actor;
  int other_actor;

  actor = (int)datum_get(*(data_t **)0x6325a4, actor_handle);
  if (*(short *)(actor + 0xa0) == 4) {
    other_actor = (int)actor_combat_get_firing_variant_definition(actor_handle);
    if (*(short *)(other_actor + 0x156) == 3 && 0 < *(short *)(actor + 0x5fe)) {
      *(short *)(actor + 0x5fe) = *(short *)(actor + 0x5fe) + -1;
    }
  }
}

/* 0x120e0 — action_alert: clear alert state on actor.
 * Sets actor->state_data1 (0xa2) and state_data2 (0xa4) to 0xffff. */
void FUN_000120e0(int actor_handle)
{
  int actor;

  actor = (int)datum_get(*(data_t **)0x6325a4, actor_handle);
  *(unsigned short *)(actor + 0xa2) = 0xffff;
  *(unsigned short *)(actor + 0xa4) = 0xffff;
}

/* 0x12110 — action_alert: clear another alert/avoid state.
 * Sets actor->field_d0 (short) to 0xffff and field_f4 (int) to -1. */
void FUN_00012110(int actor_handle)
{
  int actor;

  actor = (int)datum_get(*(data_t **)0x6325a4, actor_handle);
  *(unsigned short *)(actor + 0xd0) = 0xffff;
  *(unsigned int *)(actor + 0xf4) = 0xffffffff;
}

/* --- vector_math.obj batch drafts (2026-07-26) --- */

/* FUN_00012000 (0x12000) — readable C lift from XBE leaf. */
extern char DAT_0025334c[];
extern char DAT_00253358[];

char FUN_00012000(int actor_handle, int value, short field, void *state)
{
  char *actor;

  actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  if (state == 0) {
    display_assert(DAT_0025334c, DAT_00253358, 0x23, 1);
    system_exit(-1);
  }
  csmemset(state, 0, 0x5c);
  *(short *)state = (short)(actor[6] ? 0 : value);
  *(short *)((char *)state + 6) = (short)0xffff;
  *(short *)((char *)state + 8) = field;
  ((char *)state)[4] = 1;
  *(short *)((char *)state + 2) = 0;
  ((char *)state)[0xa] = 0;
  return 1;
}


/* FUN_00012090 (0x12090) — readable C lift: actor meta flags from actr tag. */
void FUN_00012090(int actor_handle)
{
  char *actor;
  unsigned char *tag;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  tag = (unsigned char *)tag_get(0x61637472, *(int *)(actor + 0x58));
  *(uint16_t *)(actor + 0x3fc) = 1;
  if (tag[0] & 0x40) {
    actor[0x426] = 1;
    actor[0x427] = 1;
  }
}

/* action_alert_update (0x12200) — XBE naked draft (batch 258). */
#if defined(__clang__)
static void *(*const b12200_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b12200_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b12200_exitfn)(int) = system_exit;
static int (*const b12200_c2a3f0)(int actor_handle) = FUN_0002a3f0;
static scenario_t * (*const b12200_c18e380)(void) = global_scenario_get;
static void *(*const b12200_elem)(void *, int, int) = tag_block_get_element;
static void *(*const b12200_get)(int, int) = object_get_and_verify_type;
static void *(*const b12200_tag)(int, int) = tag_get;
static char (*const b12200_c1ac180)(int actor, int anim_tag, void *entry, int do_flag) = FUN_001ac180;

__attribute__((naked, noinline))
void action_alert_update(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x13(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_alert_update_6\n\t"
      "cmpw $-1, 0xa2(%%esi)\n\t"
      "je .Laction_alert_update_6\n\t"
      "flds 0xa8(%%esi)\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "fsubs 0x12c(%%esi)\n\t"
      "flds 0xac(%%esi)\n\t"
      "fsubs 0x130(%%esi)\n\t"
      "flds 0xb0(%%esi)\n\t"
      "fsubs 0x134(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "je .Laction_alert_update_1\n\t"
      "pushl $1\n\t"
      "pushl $0xae\n\t"
      "pushl $0x253358\n\t"
      "pushl $0x253380\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Laction_alert_update_1:\n\t"
      "pushl %%edi\n\t"
      "call *%[c2a3f0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_alert_update_2\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x25337c\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Laction_alert_update_6\n\t"
      ".Laction_alert_update_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x9e(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Laction_alert_update_3\n\t"
      "decl %%eax\n\t"
      "movw %%ax, 0x9e(%%esi)\n\t"
      ".Laction_alert_update_3:\n\t"
      "movb 0xa6(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_alert_update_6\n\t"
      "movw 0xc4(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Laction_alert_update_5\n\t"
      "movswl %%ax, %%ecx\n\t"
      "pushl $0x3c\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x444, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x2c(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Laction_alert_update_4\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0x44(%%eax), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      ".Laction_alert_update_4:\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ac180]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Laction_alert_update_5:\n\t"
      "movb $0, 0xa6(%%esi)\n\t"
      ".Laction_alert_update_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b12200_dget), [assert] "m"(b12200_assert), [exitfn] "m"(b12200_exitfn), [c2a3f0] "m"(b12200_c2a3f0), [c18e380] "m"(b12200_c18e380), [elem] "m"(b12200_elem), [get] "m"(b12200_get), [tag] "m"(b12200_tag), [c1ac180] "m"(b12200_c1ac180)
      : "memory");
}
#else
#error "action_alert_update: clang naked draft required"
#endif


/* action_alert_next_position (0x12350) — XBE naked draft (batch 244). */
#if defined(__clang__)
static void *(*const b12350_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static scenario_t * (*const b12350_c18e380)(void) = global_scenario_get;
static void *(*const b12350_elem)(void *, int, int) = tag_block_get_element;
static void (*const b12350_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b12350_exitfn)(int) = system_exit;
static void *(*const b12350_memset)(void *, int, unsigned int) = csmemset;
static void (*const b12350_c64540)(int *out, int actor_handle) = FUN_00064540;
static int (*const b12350_c64570)(int *iter) = FUN_00064570;
static short (*const b12350_c53f40)(float *weights, short stride, short count, short weight_offset, int *bitvector) = FUN_00053f40;
static int (*const b12350_gtime)(void) = game_time_get;

__attribute__((naked, noinline))
void action_alert_next_position(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x160(%%esi), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "movl %%esi, -0x14(%%ebp)\n\t"
      "jne .Laction_alert_next_position_27\n\t"
      "movw 0xc(%%ebp), %%bx\n\t"
      "testw %%bx, %%bx\n\t"
      "je .Laction_alert_next_position_27\n\t"
      "movl 0x34(%%esi), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Laction_alert_next_position_28\n\t"
      "andl $0xffff, %%ecx\n\t"
      "pushl $0xb0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl 0x3a(%%esi), %%edx\n\t"
      "pushl $0xe8\n\t"
      "pushl %%edx\n\t"
      "addl $0x80, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edi, -0x18(%%ebp)\n\t"
      "je .Laction_alert_next_position_1\n\t"
      "pushl $1\n\t"
      "pushl $0x113\n\t"
      "pushl $0x253358\n\t"
      "pushl $0x253380\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Laction_alert_next_position_1:\n\t"
      "cmpw $1, %%bx\n\t"
      "jne .Laction_alert_next_position_2\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .Laction_alert_next_position_28\n\t"
      ".Laction_alert_next_position_2:\n\t"
      "pushl $4\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[memset]\n\t"
      "movl 0xc4(%%edi), %%ecx\n\t"
      "leal 0xc4(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jle .Laction_alert_next_position_13\n\t"
      "xorl %%edi, %%edi\n\t"
      "jmp .Laction_alert_next_position_4\n\t"
      ".Laction_alert_next_position_3:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      ".Laction_alert_next_position_4:\n\t"
      "pushl $0x50\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw %%ax, -0xc(%%ebp)\n\t"
      "movb $1, %%bl\n\t"
      "jne .Laction_alert_next_position_5\n\t"
      "xorb %%bl, %%bl\n\t"
      ".Laction_alert_next_position_5:\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "je .Laction_alert_next_position_6\n\t"
      "flds (%%esi)\n\t"
      "fsubs 0x12c(%%ecx)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0x130(%%ecx)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0x134(%%ecx)\n\t"
      "fld %%st(1)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(1)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x25337c\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jp .Laction_alert_next_position_6\n\t"
      "xorb %%bl, %%bl\n\t"
      ".Laction_alert_next_position_6:\n\t"
      "movb 0x1e(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_alert_next_position_7\n\t"
      "cmpb 0x68(%%ecx), %%al\n\t"
      "je .Laction_alert_next_position_7\n\t"
      "xorb %%bl, %%bl\n\t"
      ".Laction_alert_next_position_7:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c64540]\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c64570]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Laction_alert_next_position_10\n\t"
      ".Laction_alert_next_position_8:\n\t"
      "movw 0x24(%%eax), %%cx\n\t"
      "cmpw $2, %%cx\n\t"
      "jl .Laction_alert_next_position_9\n\t"
      "cmpw $3, %%cx\n\t"
      "jg .Laction_alert_next_position_9\n\t"
      "flds (%%esi)\n\t"
      "fsubs 0xbc(%%eax)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0xc0(%%eax)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0xc4(%%eax)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x25337c\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jnp .Laction_alert_next_position_11\n\t"
      ".Laction_alert_next_position_9:\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c64570]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Laction_alert_next_position_8\n\t"
      ".Laction_alert_next_position_10:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Laction_alert_next_position_11\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Laction_alert_next_position_12\n\t"
      ".Laction_alert_next_position_11:\n\t"
      "movl %%edi, %%edx\n\t"
      "sarl $5, %%edx\n\t"
      "leal -0x10(%%ebp,%%edx,4), %%eax\n\t"
      "movl %%edi, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "orl %%edx, (%%eax)\n\t"
      ".Laction_alert_next_position_12:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "movswl %%ax, %%edi\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpl (%%eax), %%edi\n\t"
      "jl .Laction_alert_next_position_3\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_alert_next_position_14\n\t"
      ".Laction_alert_next_position_13:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Laction_alert_next_position_14:\n\t"
      "movw 0xc(%%ebp), %%ax\n\t"
      "cmpw $5, %%ax\n\t"
      "jne .Laction_alert_next_position_15\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%edx), %%ax\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl 0xc8(%%ecx), %%edx\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "pushl $0x50\n\t"
      "pushl %%edx\n\t"
      "call *%[c53f40]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Laction_alert_next_position_15:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testw %%si, %%si\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "jl .Laction_alert_next_position_16\n\t"
      "movl (%%edi), %%edx\n\t"
      "movswl %%si, %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jl .Laction_alert_next_position_17\n\t"
      ".Laction_alert_next_position_16:\n\t"
      "xorl %%esi, %%esi\n\t"
      ".Laction_alert_next_position_17:\n\t"
      "movswl %%ax, %%ebx\n\t"
      ".Laction_alert_next_position_18:\n\t"
      "movl %%ebx, %%ecx\n\t"
      "subl $2, %%ecx\n\t"
      "movb $1, %%al\n\t"
      "je .Laction_alert_next_position_21\n\t"
      "decl %%ecx\n\t"
      "je .Laction_alert_next_position_19\n\t"
      "decl %%ecx\n\t"
      "jne .Laction_alert_next_position_22\n\t"
      "call *%[gtime]\n\t"
      "andb $1, %%al\n\t"
      "jmp .Laction_alert_next_position_22\n\t"
      ".Laction_alert_next_position_19:\n\t"
      "testw %%si, %%si\n\t"
      "je .Laction_alert_next_position_21\n\t"
      "movl (%%edi), %%edx\n\t"
      "movswl %%si, %%eax\n\t"
      "decl %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jne .Laction_alert_next_position_20\n\t"
      "xorb %%al, %%al\n\t"
      "jmp .Laction_alert_next_position_22\n\t"
      ".Laction_alert_next_position_20:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Laction_alert_next_position_24\n\t"
      "movb (%%eax), %%al\n\t"
      "jmp .Laction_alert_next_position_22\n\t"
      ".Laction_alert_next_position_21:\n\t"
      "movb $1, %%al\n\t"
      ".Laction_alert_next_position_22:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Laction_alert_next_position_23\n\t"
      "movb %%al, (%%ecx)\n\t"
      ".Laction_alert_next_position_23:\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_alert_next_position_25\n\t"
      ".Laction_alert_next_position_24:\n\t"
      "movl (%%edi), %%eax\n\t"
      "incl %%esi\n\t"
      "movswl %%si, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jl .Laction_alert_next_position_26\n\t"
      "xorl %%esi, %%esi\n\t"
      "jmp .Laction_alert_next_position_26\n\t"
      ".Laction_alert_next_position_25:\n\t"
      "decl %%esi\n\t"
      "testw %%si, %%si\n\t"
      "jge .Laction_alert_next_position_26\n\t"
      "movw (%%edi), %%si\n\t"
      "decw %%si\n\t"
      ".Laction_alert_next_position_26:\n\t"
      "movswl %%si, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "sarl $5, %%eax\n\t"
      "testl %%edx, -0x10(%%ebp,%%eax,4)\n\t"
      "jne .Laction_alert_next_position_18\n\t"
      "popl %%edi\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Laction_alert_next_position_27:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      ".Laction_alert_next_position_28:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b12350_dget), [c18e380] "m"(b12350_c18e380), [elem] "m"(b12350_elem), [assert] "m"(b12350_assert), [exitfn] "m"(b12350_exitfn), [memset] "m"(b12350_memset), [c64540] "m"(b12350_c64540), [c64570] "m"(b12350_c64570), [c53f40] "m"(b12350_c53f40), [gtime] "m"(b12350_gtime)
      : "memory");
}
#else
#error "action_alert_next_position: clang naked draft required"
#endif


/* action_alert_perform (0x12660) — XBE naked draft (batch 249). */
#if defined(__clang__)
static void *(*const b12660_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b12660_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b12660_exitfn)(int) = system_exit;
static char (*const b12660_c2a3d0)(int actor_handle) = FUN_0002a3d0;
static float (*const b12660_c121a0)(const float *a, const float *b) = distance_squared3d;
static float (*const b12660_c3bd50)(int actor_handle) = actor_destination_tolerance;
static void *(*const b12660_get)(int, int) = object_get_and_verify_type;
static void (*const b12660_c12350)(void) = action_alert_next_position;
static scenario_t * (*const b12660_c18e380)(void) = global_scenario_get;
static void *(*const b12660_elem)(void *, int, int) = tag_block_get_element;
static float (*const b12660_c121e0)(float min, float max) = FUN_000121e0;
static void (*const b12660_ftol)(void) = FUN_001d9068;
static char (*const b12660_c2d850)(int actor_handle, int16_t param_2) = actor_move_to_move_position;

__attribute__((naked, noinline))
void action_alert_perform(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "cmpw $0, 0x9c(%%ebx)\n\t"
      "je .Laction_alert_perform_4\n\t"
      "cmpw %%di, 0xa4(%%ebx)\n\t"
      "jne .Laction_alert_perform_4\n\t"
      "movb 0x6(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_alert_perform_1\n\t"
      "pushl $1\n\t"
      "pushl $0x47\n\t"
      "pushl $0x253358\n\t"
      "pushl $0x253380\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Laction_alert_perform_1:\n\t"
      "cmpw %%di, 0xa2(%%ebx)\n\t"
      "je .Laction_alert_perform_3\n\t"
      "pushl %%esi\n\t"
      "call *%[c2a3d0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_alert_perform_3\n\t"
      "leal 0xa8(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x12c(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c121a0]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "call *%[c3bd50]\n\t"
      "fcoms 0x253398\n\t"
      "addl $0xc, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Laction_alert_perform_2\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x253398\n\t"
      ".Laction_alert_perform_2:\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Laction_alert_perform_4\n\t"
      ".Laction_alert_perform_3:\n\t"
      "cmpw $0, 0x9e(%%ebx)\n\t"
      "jg .Laction_alert_perform_4\n\t"
      "movb 0xa6(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_alert_perform_4\n\t"
      "movl 0x18(%%ebx), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movb 0x253(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "cmpb $0x1c, %%cl\n\t"
      "je .Laction_alert_perform_4\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xa2(%%ebx), %%dx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x9c(%%ebx), %%ax\n\t"
      "leal 0xa0(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c12350]\n\t"
      "addl $0x10, %%esp\n\t"
      "movw %%ax, 0xa4(%%ebx)\n\t"
      ".Laction_alert_perform_4:\n\t"
      "movb 0x4c(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_alert_perform_7\n\t"
      "movb 0x13(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_alert_perform_7\n\t"
      "cmpw %%di, 0xa4(%%ebx)\n\t"
      "je .Laction_alert_perform_7\n\t"
      "movb 0x6(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_alert_perform_5\n\t"
      "pushl $1\n\t"
      "pushl $0x78\n\t"
      "pushl $0x253358\n\t"
      "pushl $0x253380\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Laction_alert_perform_5:\n\t"
      "movl 0x34(%%ebx), %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .Laction_alert_perform_6\n\t"
      "andl $0xffff, %%eax\n\t"
      "pushl $0xb0\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl 0x3a(%%ebx), %%ecx\n\t"
      "pushl $0xe8\n\t"
      "pushl %%ecx\n\t"
      "addl $0x80, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movw 0xa4(%%ebx), %%cx\n\t"
      "addl $0x18, %%esp\n\t"
      "testw %%cx, %%cx\n\t"
      "jl .Laction_alert_perform_6\n\t"
      "movl 0xc4(%%eax), %%edx\n\t"
      "addl $0xc4, %%eax\n\t"
      "movswl %%cx, %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jge .Laction_alert_perform_6\n\t"
      "pushl $0x50\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c121e0]\n\t"
      "fmuls 0x253394\n\t"
      "movw 0xa4(%%ebx), %%cx\n\t"
      "movw %%cx, 0xa2(%%ebx)\n\t"
      "movw %%di, 0xa4(%%ebx)\n\t"
      "leal 0xa8(%%ebx), %%edi\n\t"
      "movl $0x14, %%ecx\n\t"
      "rep movsl\n\t"
      "call *%[ftol]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xa2(%%ebx), %%dx\n\t"
      "movw %%ax, 0x9e(%%ebx)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movb $1, 0xa6(%%ebx)\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c2d850]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_alert_perform_7\n\t"
      "orl $0xffffffff, %%edi\n\t"
      ".Laction_alert_perform_6:\n\t"
      "movw 0xa4(%%ebx), %%cx\n\t"
      "movw %%cx, 0xa2(%%ebx)\n\t"
      "movw %%di, 0xa4(%%ebx)\n\t"
      "movw $0, 0x9e(%%ebx)\n\t"
      "movb $0, 0xa6(%%ebx)\n\t"
      ".Laction_alert_perform_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b12660_dget), [assert] "m"(b12660_assert), [exitfn] "m"(b12660_exitfn), [c2a3d0] "m"(b12660_c2a3d0), [c121a0] "m"(b12660_c121a0), [c3bd50] "m"(b12660_c3bd50), [get] "m"(b12660_get), [c12350] "m"(b12660_c12350), [c18e380] "m"(b12660_c18e380), [elem] "m"(b12660_elem), [c121e0] "m"(b12660_c121e0), [ftol] "m"(b12660_ftol), [c2d850] "m"(b12660_c2d850)
      : "memory");
}
#else
#error "action_alert_perform: clang naked draft required"
#endif


/* action_avoid_setup (0x128c0) — readable C lift. */
char action_avoid_setup(void * a0, void * a1)
{
  if (a1 == NULL) {
    display_assert((const char *)0x25334c, (const char *)0x25339c, 0x1e, 1);
    system_exit(-1);
  }
  {
    uintptr_t _r = (uintptr_t)csmemset(a1, 0, 4);
    return (char)((_r & ~0xffu) | 1u);
  }
}

/* action_avoid_perform (0x12920) — XBE naked draft (batch 267). */
#if defined(__clang__)
static void (*const b12920_chkstk)(void) = FUN_001d90e0;
static void *(*const b12920_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b12920_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b12920_exitfn)(int) = system_exit;
static void *(*const b12920_memset)(void *, int, unsigned int) = csmemset;
static short (*const b12920_c27090)(int actor_handle, void *param_2, void *param_3, void *param_4, void *param_5, void *param_6) = FUN_00027090;
static short (*const b12920_c272d0)(int actor_handle, short param_2, void *param_3, int param_4, unsigned int param_5, char param_6) = FUN_000272d0;

__attribute__((naked, noinline))
void action_avoid_perform(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x14740, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_avoid_perform_1\n\t"
      "pushl $1\n\t"
      "pushl $0x37\n\t"
      "pushl $0x25339c\n\t"
      "pushl $0x253380\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Laction_avoid_perform_1:\n\t"
      "movb 0x4c(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_avoid_perform_2\n\t"
      "pushl $0x670\n\t"
      "leal -0x6b4(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "leal -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x14740(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x44(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x6b4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "movw $6, -0x6b0(%%ebp)\n\t"
      "call *%[c27090]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "leal -0x14740(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x44(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c272d0]\n\t"
      "addl $0x3c, %%esp\n\t"
      ".Laction_avoid_perform_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw %%ax, 0x280(%%esi)\n\t"
      "popl %%edi\n\t"
      "sete %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(b12920_chkstk), [dget] "m"(b12920_dget), [assert] "m"(b12920_assert), [exitfn] "m"(b12920_exitfn), [memset] "m"(b12920_memset), [c27090] "m"(b12920_c27090), [c272d0] "m"(b12920_c272d0)
      : "memory");
}
#else
#error "action_avoid_perform: clang naked draft required"
#endif


/* FUN_000129f0 (0x129f0) — readable C lift. */
void FUN_000129f0(int datum_index)
{
  char *obj;
  obj = (char *)datum_get(*(void **)0x6325a4, datum_index);
  if (*(short *)(obj + 0x268) >= 5) {
    *(unsigned char *)(obj + 0x454) = 1;
    *(short *)(obj + 0x3e8) = 7;
    *(short *)(obj + 0x3ec) = 2;
  } else {
    *(short *)(obj + 0x3e8) = 5;
    if (*(short *)(obj + 0x280) > 0)
      *(short *)(obj + 0x3ec) = 5;
    else
      *(short *)(obj + 0x3ec) = 2;
  }
  *(short *)(obj + 0x3fc) = 4;
  *(unsigned char *)(obj + 0x426) = *(unsigned char *)(obj + 0x358);
  *(unsigned char *)(obj + 0x427) = 0;
  *(unsigned char *)(obj + 0x428) = 0;
  *(unsigned char *)(obj + 0x424) = 0;
  *(unsigned char *)(obj + 0x425) = 0;
}

/* FUN_00012ad0 (0x12ad0) — XBE naked draft (batch 77). */
#if defined(__clang__)
static void *(*const b12ad0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static bool (*const b12ad0_c3b320)(int actor_handle) = actor_has_ranged_weapon;
static void *(*const b12ad0_tag)(int, int) = tag_get;

__attribute__((naked, noinline))
float FUN_00012ad0(int actor_handle __attribute__((unused)), int action_type __attribute__((unused)), void *charge_state __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, %%si\n\t"
      "movl %%eax, %%edi\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "je .LFUN_00012ad0_2\n\t"
      "cmpw $3, %%si\n\t"
      "je .LFUN_00012ad0_2\n\t"
      "cmpw $4, %%si\n\t"
      "je .LFUN_00012ad0_1\n\t"
      "testw %%si, %%si\n\t"
      "jne .LFUN_00012ad0_6\n\t"
      ".LFUN_00012ad0_1:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c3b320]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00012ad0_6\n\t"
      "cmpw $7, 0x268(%%edi)\n\t"
      "jl .LFUN_00012ad0_6\n\t"
      "flds 0x2533c0\n\t"
      "fcomps 0x608(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00012ad0_6\n\t"
      "movl 0x608(%%edi), %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00012ad0_2:\n\t"
      "movl 0x58(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $3, %%si\n\t"
      "movl %%eax, %%ecx\n\t"
      "jne .LFUN_00012ad0_3\n\t"
      "flds 0x2533c0\n\t"
      "fcomps 0x388(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00012ad0_3\n\t"
      "movl 0x388(%%ecx), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".LFUN_00012ad0_3:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movb 0x30(%%eax), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00012ad0_4\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x37c(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00012ad0_6\n\t"
      "movl 0x37c(%%ecx), %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00012ad0_4:\n\t"
      "flds 0x37c(%%ecx)\n\t"
      "fadds 0x34(%%eax)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00012ad0_5\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "popl %%edi\n\t"
      "flds -0x4(%%ebp)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00012ad0_5:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00012ad0_6:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b12ad0_dget), [c3b320] "m"(b12ad0_c3b320), [tag] "m"(b12ad0_tag)
      : "memory");
}
#else
#error "FUN_00012ad0: clang naked draft required"
#endif


/* FUN_00012be0 (0x12be0) — readable C lift. */
void FUN_00012be0(int datum_index)
{
  char *obj;
  obj = (char *)datum_get(*(void **)0x6325a4, datum_index);
  if (*(short *)(obj + 0xa0) == 3
      && *(unsigned char *)(obj + 0xa7)
      && !*(unsigned char *)(obj + 0xa2)
      && !*(unsigned char *)(obj + 0x15c)) {
    *(short *)(obj + 0xaa) += 1;
  }
}

/* FUN_00012c30 (0x12c30) — XBE naked draft (batch 252). */
#if defined(__clang__)
static void *(*const b12c30_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b12c30_tag)(int, int) = tag_get;
static char (*const b12c30_c2a3d0)(int actor_handle) = FUN_0002a3d0;
static int (*const b12c30_gtime)(void) = game_time_get;

__attribute__((naked, noinline))
void FUN_00012c30(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x58(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movw $2, 0x3ec(%%esi)\n\t"
      "movw $4, 0x3fc(%%esi)\n\t"
      "movw 0xa0(%%esi), %%ax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "je .LFUN_00012c30_1\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .LFUN_00012c30_2\n\t"
      ".LFUN_00012c30_1:\n\t"
      "movb 0xa5(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00012c30_2\n\t"
      "movb 0x504(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00012c30_2\n\t"
      "pushl %%edi\n\t"
      "call *%[c2a3d0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00012c30_2\n\t"
      "movw $4, 0x3e8(%%esi)\n\t"
      "jmp .LFUN_00012c30_4\n\t"
      ".LFUN_00012c30_2:\n\t"
      "movl $5, %%eax\n\t"
      "cmpw %%ax, 0x6e(%%esi)\n\t"
      "jl .LFUN_00012c30_3\n\t"
      "cmpw $1, 0xa0(%%esi)\n\t"
      "je .LFUN_00012c30_3\n\t"
      "movw $7, 0x3e8(%%esi)\n\t"
      "jmp .LFUN_00012c30_4\n\t"
      ".LFUN_00012c30_3:\n\t"
      "movw %%ax, 0x3e8(%%esi)\n\t"
      ".LFUN_00012c30_4:\n\t"
      "movl $1, %%edi\n\t"
      "cmpw %%di, 0xa0(%%esi)\n\t"
      "jne .LFUN_00012c30_5\n\t"
      "movb 0xc1(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "sete %%dl\n\t"
      "movb %%dl, 0x426(%%esi)\n\t"
      "movb 0xc1(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "sete %%al\n\t"
      "movb %%al, 0x427(%%esi)\n\t"
      "jmp .LFUN_00012c30_7\n\t"
      ".LFUN_00012c30_5:\n\t"
      "movb 0x428(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00012c30_6\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "testl $0x10000, (%%ecx)\n\t"
      "je .LFUN_00012c30_6\n\t"
      "movb 0x358(%%esi), %%al\n\t"
      "movb %%al, 0x426(%%esi)\n\t"
      "movb %%al, 0x427(%%esi)\n\t"
      "jmp .LFUN_00012c30_7\n\t"
      ".LFUN_00012c30_6:\n\t"
      "movb $0, 0x426(%%esi)\n\t"
      "movb $0, 0x427(%%esi)\n\t"
      ".LFUN_00012c30_7:\n\t"
      "movb 0xa8(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00012c30_10\n\t"
      "movb $1, 0x440(%%esi)\n\t"
      "flds 0xb8(%%esi)\n\t"
      "fmuls 0x2533c4\n\t"
      "fcomps 0xbc(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00012c30_8\n\t"
      "movl %%edi, %%eax\n\t"
      "jmp .LFUN_00012c30_9\n\t"
      ".LFUN_00012c30_8:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00012c30_9:\n\t"
      "movb %%al, 0x441(%%esi)\n\t"
      "movb $1, 0x442(%%esi)\n\t"
      "movl 0xb0(%%esi), %%edx\n\t"
      "movl %%edx, 0x444(%%esi)\n\t"
      "movl 0xb4(%%esi), %%eax\n\t"
      "movl %%eax, 0x448(%%esi)\n\t"
      "movl 0xb8(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x44c(%%esi)\n\t"
      "movl 0xbc(%%esi), %%edx\n\t"
      "movl %%edx, 0x450(%%esi)\n\t"
      "movb $1, 0xa7(%%esi)\n\t"
      "movb $0, 0xa8(%%esi)\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, 0xac(%%esi)\n\t"
      "movw $0, 0xaa(%%esi)\n\t"
      ".LFUN_00012c30_10:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "testl $0x100000, (%%eax)\n\t"
      "je .LFUN_00012c30_14\n\t"
      "movb 0x378(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00012c30_11\n\t"
      "movw 0xa0(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "je .LFUN_00012c30_11\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .LFUN_00012c30_14\n\t"
      ".LFUN_00012c30_11:\n\t"
      "movb 0xc4(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00012c30_12\n\t"
      "movb 0x427(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00012c30_12\n\t"
      "movl %%edi, %%eax\n\t"
      "jmp .LFUN_00012c30_13\n\t"
      ".LFUN_00012c30_12:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00012c30_13:\n\t"
      "movb %%al, 0x428(%%esi)\n\t"
      ".LFUN_00012c30_14:\n\t"
      "movb $1, 0x42a(%%esi)\n\t"
      "movb $0, 0x424(%%esi)\n\t"
      "movb $0, 0x425(%%esi)\n\t"
      "cmpw %%di, 0xa0(%%esi)\n\t"
      "popl %%edi\n\t"
      "setne %%cl\n\t"
      "movb %%cl, 0x454(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b12c30_dget), [tag] "m"(b12c30_tag), [c2a3d0] "m"(b12c30_c2a3d0), [gtime] "m"(b12c30_gtime)
      : "memory");
}
#else
#error "FUN_00012c30: clang naked draft required"
#endif


/* action_charge_perform (0x13120) — XBE naked draft (batch 242). */
#if defined(__clang__)
static void *(*const b13120_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b13120_tag)(int, int) = tag_get;
static char * (*const b13120_c211f0)(int actor_handle) = actor_combat_get_firing_variant_definition;
static bool (*const b13120_c3b320)(int actor_handle) = actor_has_ranged_weapon;
static char * (*const b13120_c210f0)(int actor_handle) = FUN_000210f0;
static void (*const b13120_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b13120_exitfn)(int) = system_exit;
static int (*const b13120_gtime)(void) = game_time_get;
static bool (*const b13120_c1a9ad0)(int unit_handle) = unit_is_busy;
static void *(*const b13120_get)(int, int) = object_get_and_verify_type;
static float (*const b13120_v2fe0)(float *) = FUN_00012fe0;
static float (*const b13120_c13070)(float *a, float *b) = FUN_00013070;
static float *(*const b13120_vsca)(float *, float *, float, float *) = vector3d_scale_add;
static float (*const b13120_norm)(float *) = normalize3d;
static char (*const b13120_cf80a0)(float speed, float gravity, float *origin, float *target, int param_5, float *param_6, float *param_7, char param_8, float *aim_vector, float *param_10, float *param_11, float *param_12, float *param_13, float *param_14) = projectile_aim_ballistic;
static float (*const b13120_mag)(float *) = magnitude3d;
static void (*const b13120_c13090)(float *a, float *b, float *out) = FUN_00013090;
static char (*const b13120_c1b1b60)(int unit_handle, char param_2, int param_3) = unit_melee_attack_begin;
static void (*const b13120_c46f10)(int16_t type, int unit_handle, int param3, int param4, int16_t param5, int16_t param6, int16_t param7) = FUN_00046f10;
static float (*const b13120_c12ad0)(int actor_handle, int action_type, void *charge_state) = FUN_00012ad0;
static char (*const b13120_c2d9b0)(int actor_handle, int encounter_handle, float distance) = actor_move_to_prop;
static void (*const b13120_c2a330)(int actor_handle) = FUN_0002a330;
static void (*const b13120_c2f1a0)(int actor_handle) = FUN_0002f1a0;
static char (*const b13120_c2a3d0)(int actor_handle) = FUN_0002a3d0;
static void (*const b13120_c32ac0)(int actor_handle, int prop_handle, char flag) = actor_perception_unreachable;

__attribute__((naked, noinline))
void action_charge_perform(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x38, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x58(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl 0x5c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637476\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "call *%[c211f0]\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl 0x270(%%esi), %%eax\n\t"
      "addl $0x1c, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "leal 0x9c(%%esi), %%edi\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "movb $0, -0x3(%%ebp)\n\t"
      "je .Laction_charge_perform_36\n\t"
      "pushl %%eax\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x1b0(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Laction_charge_perform_2\n\t"
      ".Laction_charge_perform_1:\n\t"
      "movb $1, 0x28(%%edi)\n\t"
      "jmp .Laction_charge_perform_37\n\t"
      ".Laction_charge_perform_2:\n\t"
      "movw 0x4(%%edi), %%ax\n\t"
      "cmpw $5, %%ax\n\t"
      "je .Laction_charge_perform_1\n\t"
      "cmpw $4, %%ax\n\t"
      "je .Laction_charge_perform_1\n\t"
      "cmpw $2, %%ax\n\t"
      "je .Laction_charge_perform_18\n\t"
      "cmpw $3, %%ax\n\t"
      "je .Laction_charge_perform_18\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "testl $0x20000, (%%edx)\n\t"
      "je .Laction_charge_perform_3\n\t"
      "cmpw $5, 0x6e(%%esi)\n\t"
      "jl .Laction_charge_perform_3\n\t"
      "movb 0x378(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_3\n\t"
      "movb $1, %%al\n\t"
      "jmp .Laction_charge_perform_4\n\t"
      ".Laction_charge_perform_3:\n\t"
      "xorb %%al, %%al\n\t"
      ".Laction_charge_perform_4:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testb %%al, %%al\n\t"
      "setne %%cl\n\t"
      "movl %%ecx, %%eax\n\t"
      "cmpw $1, %%ax\n\t"
      "movw %%ax, 0x4(%%edi)\n\t"
      "jne .Laction_charge_perform_12\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movw 0x38(%%ecx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Laction_charge_perform_5\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .Laction_charge_perform_6\n\t"
      ".Laction_charge_perform_5:\n\t"
      "cmpb $2, 0x122(%%ecx)\n\t"
      "jg .Laction_charge_perform_6\n\t"
      "movl $1, %%eax\n\t"
      "jmp .Laction_charge_perform_7\n\t"
      ".Laction_charge_perform_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Laction_charge_perform_7:\n\t"
      "testb %%al, %%al\n\t"
      "movb %%al, 0x24(%%edi)\n\t"
      "je .Laction_charge_perform_8\n\t"
      "testl $0x40000, (%%edx)\n\t"
      "je .Laction_charge_perform_8\n\t"
      "movb $0, 0x28(%%edi)\n\t"
      "jmp .Laction_charge_perform_9\n\t"
      ".Laction_charge_perform_8:\n\t"
      "movb $1, 0x28(%%edi)\n\t"
      ".Laction_charge_perform_9:\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_charge_perform_10\n\t"
      "incw 0x26(%%edi)\n\t"
      ".Laction_charge_perform_10:\n\t"
      "testb %%al, %%al\n\t"
      "movb $0, 0x25(%%edi)\n\t"
      "jne .Laction_charge_perform_11\n\t"
      "cmpb $1, 0x124(%%ecx)\n\t"
      "jg .Laction_charge_perform_11\n\t"
      "movb $1, 0x25(%%edi)\n\t"
      "jmp .Laction_charge_perform_37\n\t"
      ".Laction_charge_perform_11:\n\t"
      "flds 0x32c(%%edx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Laction_charge_perform_37\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "flds 0x11c(%%edx)\n\t"
      "fcomps 0x32c(%%eax)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Laction_charge_perform_37\n\t"
      "movb $1, 0x25(%%edi)\n\t"
      "jmp .Laction_charge_perform_37\n\t"
      ".Laction_charge_perform_12:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c3b320]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_charge_perform_1\n\t"
      "movb 0x15d(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_1\n\t"
      "movb 0x378(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "je .Laction_charge_perform_13\n\t"
      "movl 0x168(%%eax), %%ecx\n\t"
      "movl 0x16c(%%eax), %%edx\n\t"
      "jmp .Laction_charge_perform_14\n\t"
      ".Laction_charge_perform_13:\n\t"
      "movl 0x9c(%%eax), %%ecx\n\t"
      "movl 0xa0(%%eax), %%edx\n\t"
      ".Laction_charge_perform_14:\n\t"
      "pushl %%ebx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "call *%[c210f0]\n\t"
      "movl %%eax, %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Laction_charge_perform_15\n\t"
      "flds 0x40c(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Laction_charge_perform_15\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fcomps 0x40c(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Laction_charge_perform_15\n\t"
      "movl 0x40c(%%ecx), %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      ".Laction_charge_perform_15:\n\t"
      "movb 0x28(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "flds 0x11c(%%ecx)\n\t"
      "je .Laction_charge_perform_16\n\t"
      "fcomps -0x14(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Laction_charge_perform_17\n\t"
      "movb $0, 0x28(%%edi)\n\t"
      "jmp .Laction_charge_perform_17\n\t"
      ".Laction_charge_perform_16:\n\t"
      "fcomps -0x18(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Laction_charge_perform_17\n\t"
      "movb $1, 0x28(%%edi)\n\t"
      ".Laction_charge_perform_17:\n\t"
      "flds 0x11c(%%ecx)\n\t"
      "fcomps 0x2533c4\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Laction_charge_perform_37\n\t"
      "movw 0x38(%%ecx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Laction_charge_perform_37\n\t"
      "cmpw $1, %%ax\n\t"
      "je .Laction_charge_perform_37\n\t"
      "movb $1, 0x28(%%edi)\n\t"
      "jmp .Laction_charge_perform_37\n\t"
      ".Laction_charge_perform_18:\n\t"
      "movb 0x378(%%esi), %%cl\n\t"
      "pushl %%ebx\n\t"
      "movl $0x7f7fffff, -0x14(%%ebp)\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      "movb %%cl, -0x1(%%ebp)\n\t"
      "call *%[c3b320]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_19\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".Laction_charge_perform_19:\n\t"
      "movb 0x6(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_charge_perform_20\n\t"
      "pushl $1\n\t"
      "pushl $0x120\n\t"
      "pushl $0x2533f4\n\t"
      "pushl $0x253380\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Laction_charge_perform_20:\n\t"
      "movb 0x6(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_23\n\t"
      "movb 0xb(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_23\n\t"
      "movb 0xc(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_23\n\t"
      "movb 0x378(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_21\n\t"
      "pushl %%ebx\n\t"
      "call *%[c3b320]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_24\n\t"
      ".Laction_charge_perform_21:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_charge_perform_22\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "flds 0x174(%%edx)\n\t"
      "jmp .Laction_charge_perform_25\n\t"
      ".Laction_charge_perform_22:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "flds 0x164(%%eax)\n\t"
      "jmp .Laction_charge_perform_25\n\t"
      ".Laction_charge_perform_23:\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      ".Laction_charge_perform_24:\n\t"
      "flds -0x14(%%ebp)\n\t"
      ".Laction_charge_perform_25:\n\t"
      "movb 0x1cb(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_charge_perform_28\n\t"
      "flds 0x2533c0\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "fcomps 0x37c(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Laction_charge_perform_26\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Laction_charge_perform_27\n\t"
      ".Laction_charge_perform_26:\n\t"
      "flds 0x37c(%%ecx)\n\t"
      ".Laction_charge_perform_27:\n\t"
      "fadds 0x2533f0\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "fcoms -0x18(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Laction_charge_perform_28\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x18(%%ebp)\n\t"
      ".Laction_charge_perform_28:\n\t"
      "movb -0x2(%%ebp), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Laction_charge_perform_29\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "fcomps 0x11c(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Laction_charge_perform_30\n\t"
      "movb $1, 0x8(%%edi)\n\t"
      "jmp .Laction_charge_perform_37\n\t"
      ".Laction_charge_perform_29:\n\t"
      "fstp %%st(0)\n\t"
      ".Laction_charge_perform_30:\n\t"
      "call *%[gtime]\n\t"
      "testb %%bl, %%bl\n\t"
      "movl %%eax, 0x380(%%esi)\n\t"
      "movb $1, 0x28(%%edi)\n\t"
      "je .Laction_charge_perform_37\n\t"
      "cmpw $2, 0x4(%%edi)\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "jne .Laction_charge_perform_35\n\t"
      "flds 0x388(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Laction_charge_perform_32\n\t"
      "flds 0x390(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Laction_charge_perform_32\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movb 0x130(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Laction_charge_perform_31\n\t"
      "cmpw $0, 0x9c(%%eax)\n\t"
      "jle .Laction_charge_perform_33\n\t"
      ".Laction_charge_perform_31:\n\t"
      "movb $1, 0xa(%%edi)\n\t"
      "jmp .Laction_charge_perform_33\n\t"
      ".Laction_charge_perform_32:\n\t"
      "movb $0, 0xa(%%edi)\n\t"
      ".Laction_charge_perform_33:\n\t"
      "movb 0xa(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_charge_perform_37\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpw $0, 0x9c(%%eax)\n\t"
      "jg .Laction_charge_perform_34\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "flds 0x384(%%edx)\n\t"
      "fmuls 0x2533ec\n\t"
      "fcomps 0x11c(%%eax)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Laction_charge_perform_37\n\t"
      ".Laction_charge_perform_34:\n\t"
      "movw $3, 0x4(%%edi)\n\t"
      "jmp .Laction_charge_perform_37\n\t"
      ".Laction_charge_perform_35:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "flds 0x11c(%%eax)\n\t"
      "fcomps 0x384(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Laction_charge_perform_37\n\t"
      "movw $2, 0x4(%%edi)\n\t"
      "movb $1, 0xa(%%edi)\n\t"
      "jmp .Laction_charge_perform_37\n\t"
      ".Laction_charge_perform_36:\n\t"
      "movb $0, 0x28(%%edi)\n\t"
      ".Laction_charge_perform_37:\n\t"
      "movb 0x6(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_charge_perform_39\n\t"
      "movl 0x18(%%esi), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Laction_charge_perform_38\n\t"
      "pushl %%esi\n\t"
      "call *%[c1a9ad0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_charge_perform_38\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb %%al, 0x7(%%edi)\n\t"
      "jmp .Laction_charge_perform_60\n\t"
      ".Laction_charge_perform_38:\n\t"
      "movl $1, %%eax\n\t"
      "movb %%al, 0x7(%%edi)\n\t"
      "jmp .Laction_charge_perform_60\n\t"
      ".Laction_charge_perform_39:\n\t"
      "movb 0xc(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_60\n\t"
      "movw 0x4(%%edi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "je .Laction_charge_perform_40\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .Laction_charge_perform_60\n\t"
      ".Laction_charge_perform_40:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Laction_charge_perform_60\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0x331f58, %%ecx\n\t"
      "andl $0xffff, %%esi\n\t"
      "imull $0x657c, %%esi, %%esi\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "addl %%ecx, %%esi\n\t"
      "call *%[gtime]\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "movl %%eax, 0x104(%%esi)\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "addl $0x12c, %%ebx\n\t"
      "flds (%%eax)\n\t"
      "leal 0x114(%%esi), %%edx\n\t"
      "fmuls 0x2533e8\n\t"
      "fadds (%%ebx)\n\t"
      "fstps 0x108(%%esi)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x2533e8\n\t"
      "fadds 0x4(%%ebx)\n\t"
      "fstps 0x10c(%%esi)\n\t"
      "flds 0x8(%%eax)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "fmuls 0x2533e8\n\t"
      "addl $0x174, %%eax\n\t"
      "fadds 0x8(%%ebx)\n\t"
      "fstps 0x110(%%esi)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "flds (%%eax)\n\t"
      "addl $0xbc, %%ecx\n\t"
      "fmuls 0x2533e8\n\t"
      "fadds (%%ecx)\n\t"
      "fstps 0x120(%%esi)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x2533e8\n\t"
      "fadds 0x4(%%ecx)\n\t"
      "fstps 0x124(%%esi)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x2533e8\n\t"
      "fadds 0x8(%%ecx)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "fstps 0x128(%%esi)\n\t"
      "movb 0x6(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_charge_perform_41\n\t"
      "pushl $1\n\t"
      "pushl $0x1e7\n\t"
      "pushl $0x2533f4\n\t"
      "pushl $0x253380\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Laction_charge_perform_41:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "flds 0x11c(%%ecx)\n\t"
      "fcomps 0x2533f0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Laction_charge_perform_42\n\t"
      "addl $0xe0, %%ecx\n\t"
      "movb $1, 0x139(%%esi)\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "jmp .Laction_charge_perform_53\n\t"
      ".Laction_charge_perform_42:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl 0x18(%%edx), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0xd4, %%eax\n\t"
      "pushl %%eax\n\t"
      "movb $0, 0x139(%%esi)\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      "call *%[v2fe0]\n\t"
      "fsts -0x18(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $0xc, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Laction_charge_perform_43\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "leal 0xe0(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $0xd4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13070]\n\t"
      "fdivs -0x18(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fadds 0x2533c8\n\t"
      "fmuls 0x253398\n\t"
      "jmp .Laction_charge_perform_44\n\t"
      ".Laction_charge_perform_43:\n\t"
      "flds -0x1c(%%ebp)\n\t"
      ".Laction_charge_perform_44:\n\t"
      "movswl 0x32(%%edi), %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "fildl -0x1c(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "leal 0xd4(%%ecx), %%eax\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "leal 0xbc(%%ecx), %%eax\n\t"
      "pushl %%eax\n\t"
      "fstp %%st(0)\n\t"
      "call *%[vsca]\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fsubs (%%ebx)\n\t"
      "movl 0x31fc44, %%edx\n\t"
      "leal 0x13c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "pushl $0x3d4ccccd\n\t"
      "flds -0x34(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "call *%[vsca]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0xe8(%%eax)\n\t"
      "addl $0x20, %%esp\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0xe4(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls 0xe0(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Laction_charge_perform_45\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "flds 0x2533c0\n\t"
      "movl 0xe0(%%eax), %%ecx\n\t"
      "movl 0xe4(%%eax), %%edx\n\t"
      "movl 0xe8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x2c(%%ebp)\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "jmp .Laction_charge_perform_46\n\t"
      ".Laction_charge_perform_45:\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[norm]\n\t"
      "fcoms 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Laction_charge_perform_46\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0xe0(%%eax), %%edx\n\t"
      "movl 0xe4(%%eax), %%ecx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl 0xe8(%%eax), %%edx\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      ".Laction_charge_perform_46:\n\t"
      "movw 0x4(%%edi), %%ax\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .Laction_charge_perform_49\n\t"
      "movb 0xb(%%edi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Laction_charge_perform_49\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl 0x384(%%ecx), %%eax\n\t"
      "movl %%eax, 0x148(%%esi)\n\t"
      "movl 0x388(%%ecx), %%edx\n\t"
      "movl %%edx, 0x14c(%%esi)\n\t"
      "fcoms 0x384(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Laction_charge_perform_47\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpw $0, 0x9c(%%eax)\n\t"
      "jne .Laction_charge_perform_47\n\t"
      "movb 0x130(%%eax), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .Laction_charge_perform_47\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "movb $1, 0x8(%%edi)\n\t"
      "movl $0xffffffff, 0x380(%%eax)\n\t"
      "jmp .Laction_charge_perform_54\n\t"
      ".Laction_charge_perform_47:\n\t"
      "fcomps 0x388(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Laction_charge_perform_54\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "flds 0x38c(%%eax)\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x2533e4\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal 0x394(%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x38c(%%eax), %%edx\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "addl $0xbc, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%edx\n\t"
      "call *%[cf80a0]\n\t"
      "addl $0x38, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_charge_perform_54\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Laction_charge_perform_48\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $0x174, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Laction_charge_perform_48\n\t"
      "movl 0x31fc3c, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      ".Laction_charge_perform_48:\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "movl -0x34(%%ebp), %%ecx\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl %%eax, 0x14(%%edi)\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movb $1, 0xc(%%edi)\n\t"
      "movl %%ecx, 0x18(%%edi)\n\t"
      "movl %%edx, 0x1c(%%edi)\n\t"
      "movl %%eax, 0x20(%%edi)\n\t"
      "jmp .Laction_charge_perform_54\n\t"
      ".Laction_charge_perform_49:\n\t"
      "movb 0x30(%%edi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Laction_charge_perform_51\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl $0, 0x148(%%esi)\n\t"
      "movl 0x37c(%%ecx), %%edx\n\t"
      "movl %%edx, 0x14c(%%esi)\n\t"
      "fcoms 0x37c(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Laction_charge_perform_50\n\t"
      "fstp %%st(0)\n\t"
      "jmp .Laction_charge_perform_53\n\t"
      ".Laction_charge_perform_50:\n\t"
      "fcomps 0x3a4(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Laction_charge_perform_54\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0x18, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $0xd4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13090]\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x2533e0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Laction_charge_perform_54\n\t"
      "jmp .Laction_charge_perform_53\n\t"
      ".Laction_charge_perform_51:\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .Laction_charge_perform_52\n\t"
      "movb 0xb(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_charge_perform_52\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x20(%%eax)\n\t"
      "movswl 0x32(%%edi), %%edx\n\t"
      "flds -0x28(%%ebp)\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "fmuls 0x1c(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls 0x18(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fimull -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      ".Laction_charge_perform_52:\n\t"
      "movl 0x34(%%edi), %%eax\n\t"
      "movl %%eax, 0x148(%%esi)\n\t"
      "flds 0x34(%%edi)\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "fadds 0x37c(%%eax)\n\t"
      "fstps 0x14c(%%esi)\n\t"
      "flds 0x34(%%edi)\n\t"
      "fadds 0x37c(%%eax)\n\t"
      "fxch %%st(1)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Laction_charge_perform_54\n\t"
      ".Laction_charge_perform_53:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".Laction_charge_perform_54:\n\t"
      "movb 0xc(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_55\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_charge_perform_58\n\t"
      "movb 0x30(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_58\n\t"
      ".Laction_charge_perform_55:\n\t"
      "movl -0x2c(%%ebp), %%ecx\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Laction_charge_perform_58\n\t"
      "movb 0xb(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_charge_perform_56\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Laction_charge_perform_57\n\t"
      ".Laction_charge_perform_56:\n\t"
      "flds 0x2533dc\n\t"
      ".Laction_charge_perform_57:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x178(%%eax)\n\t"
      "addl $0x174, %%eax\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls (%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jp .Laction_charge_perform_58\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movb $0, 0xc(%%edi)\n\t"
      "movb $1, 0x9(%%edi)\n\t"
      ".Laction_charge_perform_58:\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movl -0x24(%%ebp), %%ebx\n\t"
      "leal 0x12c(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "movl -0x2c(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl %%ebx, 0x8(%%edx)\n\t"
      "movb -0x1(%%ebp), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "movb %%dl, 0x138(%%esi)\n\t"
      "je .Laction_charge_perform_60\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "call *%[mag]\n\t"
      "fcomps 0x2533c0\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Laction_charge_perform_59\n\t"
      "movl 0x174(%%esi), %%ecx\n\t"
      "movl 0x178(%%esi), %%edx\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      ".Laction_charge_perform_59:\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1b1b60]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_charge_perform_60\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0x18(%%edx), %%eax\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2b\n\t"
      "call *%[c46f10]\n\t"
      "addl $0x1c, %%esp\n\t"
      "movb $1, 0x6(%%edi)\n\t"
      ".Laction_charge_perform_60:\n\t"
      "call *%[gtime]\n\t"
      "movw 0x4(%%edi), %%cx\n\t"
      "cmpw $2, %%cx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%esi, -0x1c(%%ebp)\n\t"
      "je .Laction_charge_perform_61\n\t"
      "cmpw $3, %%cx\n\t"
      "jne .Laction_charge_perform_64\n\t"
      ".Laction_charge_perform_61:\n\t"
      "movb 0x6(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_64\n\t"
      "movb 0xc(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_64\n\t"
      "movb 0xb(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_charge_perform_62\n\t"
      "cmpw $0xf, 0xe(%%edi)\n\t"
      "jle .Laction_charge_perform_64\n\t"
      "jmp .Laction_charge_perform_63\n\t"
      ".Laction_charge_perform_62:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "flds 0x380(%%edx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Laction_charge_perform_64\n\t"
      "fildl -0x1c(%%ebp)\n\t"
      "flds 0x380(%%edx)\n\t"
      "fmuls 0x253394\n\t"
      "fiaddl (%%edi)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Laction_charge_perform_64\n\t"
      ".Laction_charge_perform_63:\n\t"
      "movb $1, 0x8(%%edi)\n\t"
      ".Laction_charge_perform_64:\n\t"
      "cmpw $4, %%cx\n\t"
      "je .Laction_charge_perform_65\n\t"
      "cmpw $5, %%cx\n\t"
      "jne .Laction_charge_perform_66\n\t"
      ".Laction_charge_perform_65:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%esi, 0x388(%%edx)\n\t"
      ".Laction_charge_perform_66:\n\t"
      "movw 0x4(%%edi), %%si\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c12ad0]\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x2c(%%edi)\n\t"
      "movb 0x6(%%ecx), %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_80\n\t"
      "movl %%ecx, %%esi\n\t"
      "movb 0x4c(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_charge_perform_80\n\t"
      "movb 0x6(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb $0, 0x29(%%edi)\n\t"
      "jne .Laction_charge_perform_72\n\t"
      "movb 0xb(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_72\n\t"
      "movb 0xc(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_72\n\t"
      "movb 0x28(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_charge_perform_72\n\t"
      "cmpw $3, 0x4(%%edi)\n\t"
      "jne .Laction_charge_perform_67\n\t"
      "flds 0x2533d8\n\t"
      "jmp .Laction_charge_perform_68\n\t"
      ".Laction_charge_perform_67:\n\t"
      "flds 0x2533ec\n\t"
      ".Laction_charge_perform_68:\n\t"
      "fcoms -0x14(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Laction_charge_perform_69\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "jmp .Laction_charge_perform_70\n\t"
      ".Laction_charge_perform_69:\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "fstp %%st(0)\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      ".Laction_charge_perform_70:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl 0x270(%%esi), %%ecx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c2d9b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_charge_perform_71\n\t"
      "pushl %%ebx\n\t"
      "call *%[c2a330]\n\t"
      "jmp .Laction_charge_perform_74\n\t"
      ".Laction_charge_perform_71:\n\t"
      "movb $1, 0x29(%%edi)\n\t"
      "movb $0, 0x28(%%edi)\n\t"
      "jmp .Laction_charge_perform_73\n\t"
      ".Laction_charge_perform_72:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      ".Laction_charge_perform_73:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c2f1a0]\n\t"
      ".Laction_charge_perform_74:\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $7, 0x268(%%esi)\n\t"
      "jl .Laction_charge_perform_80\n\t"
      "movl 0x270(%%esi), %%edx\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "flds 0x11c(%%eax)\n\t"
      "fcomps 0x2c(%%edi)\n\t"
      "addl $8, %%esp\n\t"
      "xorb %%cl, %%cl\n\t"
      "movb $0, -0x14(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Laction_charge_perform_75\n\t"
      "movb $1, %%cl\n\t"
      ".Laction_charge_perform_75:\n\t"
      "movw 0x4(%%edi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "je .Laction_charge_perform_76\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .Laction_charge_perform_77\n\t"
      ".Laction_charge_perform_76:\n\t"
      "movb 0xb(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_79\n\t"
      "movb 0xc(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_79\n\t"
      "movb 0x6(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_79\n\t"
      ".Laction_charge_perform_77:\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Laction_charge_perform_79\n\t"
      "movb 0x29(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_78\n\t"
      "pushl %%ebx\n\t"
      "call *%[c2a3d0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Laction_charge_perform_78\n\t"
      "flds 0x4bc(%%esi)\n\t"
      "fcomps 0x2c(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Laction_charge_perform_79\n\t"
      ".Laction_charge_perform_78:\n\t"
      "movb $1, -0x14(%%ebp)\n\t"
      ".Laction_charge_perform_79:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl 0x270(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c32ac0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Laction_charge_perform_80:\n\t"
      "movw 0x4(%%edi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "je .Laction_charge_perform_82\n\t"
      "cmpw $3, %%ax\n\t"
      "je .Laction_charge_perform_82\n\t"
      "cmpw $4, %%ax\n\t"
      "je .Laction_charge_perform_81\n\t"
      "cmpw $5, %%ax\n\t"
      "jne .Laction_charge_perform_84\n\t"
      ".Laction_charge_perform_81:\n\t"
      "movb 0x29(%%edi), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Laction_charge_perform_82:\n\t"
      "movb 0x8(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_83\n\t"
      "movb 0x7(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_83\n\t"
      "movb 0x29(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Laction_charge_perform_83\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Laction_charge_perform_83:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Laction_charge_perform_84:\n\t"
      "movb -0x3(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b13120_dget), [tag] "m"(b13120_tag), [c211f0] "m"(b13120_c211f0), [c3b320] "m"(b13120_c3b320), [c210f0] "m"(b13120_c210f0), [assert] "m"(b13120_assert), [exitfn] "m"(b13120_exitfn), [gtime] "m"(b13120_gtime), [c1a9ad0] "m"(b13120_c1a9ad0), [get] "m"(b13120_get), [v2fe0] "m"(b13120_v2fe0), [c13070] "m"(b13120_c13070), [vsca] "m"(b13120_vsca), [norm] "m"(b13120_norm), [cf80a0] "m"(b13120_cf80a0), [mag] "m"(b13120_mag), [c13090] "m"(b13120_c13090), [c1b1b60] "m"(b13120_c1b1b60), [c46f10] "m"(b13120_c46f10), [c12ad0] "m"(b13120_c12ad0), [c2d9b0] "m"(b13120_c2d9b0), [c2a330] "m"(b13120_c2a330), [c2f1a0] "m"(b13120_c2f1a0), [c2a3d0] "m"(b13120_c2a3d0), [c32ac0] "m"(b13120_c32ac0)
      : "memory");
}
#else
#error "action_charge_perform: clang naked draft required"
#endif


/* FUN_00021430 (0x21430) — XBE naked draft (batch 258). */
#if defined(__clang__)
static int *(*const b21430_gseed)(void) = get_global_random_seed_address;
static float (*const b21430_rrange)(int *, float, float) = random_real_range;
static void (*const b21430_c10cc70)(float *output, float angle) = vector3d_from_angle;
static bool (*const b21430_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;

__attribute__((naked, noinline))
void FUN_00021430(float *target /* */ __attribute__((unused)), float distance __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x80, %%esp\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "flds (%%eax)\n\t"
      "pushl $0x40490fdb\n\t"
      "fmuls 0x2533ec\n\t"
      "pushl $0xc0490fdb\n\t"
      "fadds (%%esi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x2533ec\n\t"
      "fadds 0x4(%%esi)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x2533ec\n\t"
      "fadds 0x8(%%esi)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps 0x8(%%esp)\n\t"
      "addl $8, %%esp\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c10cc70]\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "leal -0x80(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "pushl $0x23\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsubs (%%esi)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fsubs 0x8(%%esi)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00021430_1\n\t"
      "movl %%esi, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".LFUN_00021430_1:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "leal -0x80(%%ebp), %%ecx\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "flds -0x14(%%ebp)\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "fsubs -0x8(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl $0x23\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00021430_3\n\t"
      "flds -0x6c(%%ebp)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fsubs 0x25496c\n\t"
      "flds 0x2533c0\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00021430_2\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      ".LFUN_00021430_2:\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00021430_3:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [gseed] "m"(b21430_gseed), [rrange] "m"(b21430_rrange), [c10cc70] "m"(b21430_c10cc70), [ray] "m"(b21430_ray)
      : "memory");
}
#else
#error "FUN_00021430: clang naked draft required"
#endif


/* FUN_00021e50 (0x21e50) — XBE naked draft (batch 261). */
#if defined(__clang__)
static void *(*const b21e50_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b21e50_tag)(int, int) = tag_get;
static char (*const b21e50_c218d0)(int origin, float *direction, int16_t grenade_index, float *target_pos, float *param_14, float *aim_vector, float *param_20, float *launch_velocity, float *out_speed) = actor_combat_build_grenade_trajectory;
static char (*const b21e50_c41ad0)(int actor_handle, int param_2, int target, float *impact_point, float accel, int param_6, char param_7) = ai_test_ballistic_line_of_fire;

__attribute__((naked, noinline))
char FUN_00021e50(int actor_handle __attribute__((unused)), short param_2 __attribute__((unused)), float *param_3 __attribute__((unused)), int param_4 __attribute__((unused)), int param_5 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x5c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637476\n\t"
      "call *%[tag]\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "leal 0x120(%%esi), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "leal 0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x190(%%eax), %%edx\n\t"
      "movswl 0x180(%%eax), %%eax\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x24(%%ebp), %%ebx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c218d0]\n\t"
      "addl $0x34, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00021e50_1\n\t"
      "movl 0x158(%%esi), %%ebx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "cmpl $-1, %%ebx\n\t"
      "movl 0x18(%%ebp), %%ebx\n\t"
      "setne %%cl\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c41ad0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00021e50_1\n\t"
      "movl (%%edi), %%edx\n\t"
      "leal 0x6a8(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "movl %%eax, 0x6b4(%%esi)\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "leal 0x6bc(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%ebx, 0x6b8(%%esi)\n\t"
      "movl %%eax, 0x6c8(%%esi)\n\t"
      "movb $0, 0x6a1(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00021e50_1:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b21e50_dget), [tag] "m"(b21e50_tag), [c218d0] "m"(b21e50_c218d0), [c41ad0] "m"(b21e50_c41ad0)
      : "memory");
}
#else
#error "FUN_00021e50: clang naked draft required"
#endif


/* FUN_00028250 (0x28250) — XBE naked draft (batch 262). */
#if defined(__clang__)
static void *(*const b28250_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b28250_tag)(int, int) = tag_get;
static char * (*const b28250_c210f0)(int actor_handle) = FUN_000210f0;
static void (*const b28250_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b28250_exitfn)(int) = system_exit;
static char * (*const b28250_c49ac0)(int actor_handle, int object_handle, char with_actor, char *buf, int buf_size) = ai_debug_describe_actor;
static void (*const b28250_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static int *(*const b28250_gseed)(void) = get_global_random_seed_address;
static float (*const b28250_rrange)(int *, float, float) = random_real_range;

__attribute__((naked, noinline))
int FUN_00028250(float *look_vectors __attribute__((unused)), char is_secondary __attribute__((unused)), int actor_handle __attribute__((unused)), int look_type __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x58(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "pushl %%esi\n\t"
      "call *%[c210f0]\n\t"
      "movswl %%di, %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl %%edi, %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_00028250_3\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00028250_2\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00028250_1\n\t"
      "pushl $1\n\t"
      "pushl $0x3da\n\t"
      "pushl $0x255284\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00028250_5\n\t"
      ".LFUN_00028250_1:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x10(%%eax), %%edx\n\t"
      "movl 0x14(%%eax), %%eax\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00028250_5\n\t"
      ".LFUN_00028250_2:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "jmp .LFUN_00028250_4\n\t"
      ".LFUN_00028250_3:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      ".LFUN_00028250_4:\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".LFUN_00028250_5:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00028250_6\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00028250_6\n\t"
      "flds -0x4(%%ebp)\n\t"
      "subl $0x10, %%esp\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "movl $0x25530c, -0x14(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl $0x255304, -0x10(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "movl $0x2552fc, -0xc(%%ebp)\n\t"
      "movl -0x14(%%ebp,%%edi,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x100\n\t"
      "pushl $0x5ab100\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "call *%[c49ac0]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2552b0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "flds 0x253398\n\t"
      "addl $0x20, %%esp\n\t"
      "jmp .LFUN_00028250_7\n\t"
      ".LFUN_00028250_6:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00028250_7:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_00028250_8\n\t"
      "flds 0x410(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00028250_8\n\t"
      "fmuls 0x410(%%ebx)\n\t"
      ".LFUN_00028250_8:\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_00028250_9\n\t"
      "fmuls 0x2533ec\n\t"
      ".LFUN_00028250_9:\n\t"
      "fmuls 0x253394\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fistps -0x8(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpl $1, %%eax\n\t"
      "jg .LFUN_00028250_10\n\t"
      "movl $1, %%eax\n\t"
      ".LFUN_00028250_10:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b28250_dget), [tag] "m"(b28250_tag), [c210f0] "m"(b28250_c210f0), [assert] "m"(b28250_assert), [exitfn] "m"(b28250_exitfn), [c49ac0] "m"(b28250_c49ac0), [c8f390] "m"(b28250_c8f390), [gseed] "m"(b28250_gseed), [rrange] "m"(b28250_rrange)
      : "memory");
}
#else
#error "FUN_00028250: clang naked draft required"
#endif


/* FUN_000283b0 (0x283b0) — XBE naked draft (batch 259). */
#if defined(__clang__)
static float (*const b283b0_norm)(float *) = normalize3d;
static int *(*const b283b0_gseed)(void) = get_global_random_seed_address;
static float (*const b283b0_rrange)(int *, float, float) = random_real_range;
static void (*const b283b0_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;
static void (*const b283b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b283b0_exitfn)(int) = system_exit;
static bool (*const b283b0_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;

__attribute__((naked, noinline))
char FUN_000283b0(float *actor_facing __attribute__((unused)), char is_aim __attribute__((unused)), float az_min __attribute__((unused)), float az_max __attribute__((unused)), float el_min __attribute__((unused)), float el_max __attribute__((unused)), float *out_vec3 __attribute__((unused)), float *current_dir __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x7c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "flds 0x4(%%esi)\n\t"
      "movl (%%esi), %%eax\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "fchs\n\t"
      "pushl %%edi\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_000283b0_1\n\t"
      "movl 0x31fc40, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      ".LFUN_000283b0_1:\n\t"
      "movl 0x1c(%%ebp), %%edi\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000283b0_2:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fld %%st(0)\n\t"
      "fcos\n\t"
      "addl $4, %%esp\n\t"
      "movl %%esi, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "fsin\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[rots]\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcos\n\t"
      "addl $8, %%esp\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fsin\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[rots]\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000283b0_5\n\t"
      "incw 0x5ac5d4\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "jl .LFUN_000283b0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x42a\n\t"
      "pushl $0x255284\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000283b0_3:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x254644\n\t"
      "movswl %%ax, %%edx\n\t"
      "incw %%ax\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "leal -0x7c(%%ebp), %%eax\n\t"
      "flds -0x10(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "fmuls 0x254644\n\t"
      "pushl $-1\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "movw $1, 0x5a8c80(,%%edx,2)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x254644\n\t"
      "pushl %%edx\n\t"
      "pushl $0x21\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "addl $0x14, %%esp\n\t"
      "movb %%al, %%bl\n\t"
      "negb %%bl\n\t"
      "sbbb %%bl, %%bl\n\t"
      "incb %%bl\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "jg .LFUN_000283b0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x42e\n\t"
      "pushl $0x255284\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000283b0_4:\n\t"
      "decw 0x4761d8\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_000283b0_5\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw $0xa, %%ax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jl .LFUN_000283b0_2\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000283b0_5:\n\t"
      "movl 0x20(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000283b0_6\n\t"
      "pushl $1\n\t"
      "pushl $0x435\n\t"
      "pushl $0x255284\n\t"
      "pushl $0x255314\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000283b0_6:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_000283b0_7\n\t"
      "fdivrs 0x2533c8\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      ".LFUN_000283b0_7:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%eax, (%%esi)\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      "popl %%edi\n\t"
      "movl %%edx, 0x8(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [norm] "m"(b283b0_norm), [gseed] "m"(b283b0_gseed), [rrange] "m"(b283b0_rrange), [rots] "m"(b283b0_rots), [assert] "m"(b283b0_assert), [exitfn] "m"(b283b0_exitfn), [ray] "m"(b283b0_ray)
      : "memory");
}
#else
#error "FUN_000283b0: clang naked draft required"
#endif

