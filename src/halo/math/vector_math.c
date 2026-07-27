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

/* magnitude3d (0x12f10) — readable C lift from XBE leaf (normalize2d). */
float magnitude3d(float *v)
{
  float mag;

  __asm__ __volatile__(
      "flds 4(%1)\n\t"
      "flds (%1)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "faddp %%st(1), %%st(0)\n\t"
      "fsqrt\n\t"
      "fstp %%st(2)\n\t"
      "fstp %%st(0)\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp 1f\n\t"
      "flds 0x2533c8\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%1)\n\t"
      "fstps (%1)\n\t"
      "fmuls 4(%1)\n\t"
      "fstps 4(%1)\n\t"
      "jmp 2f\n\t"
      "1:\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "2:\n\t"
      : "=t"(mag)
      : "r"(v)
      : "ax", "memory");
  return mag;
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

/* action_alert_update (0x12200) — readable C lift from XBE leaf. */
void action_alert_update(int actor_handle)
{
  void *actor;
  float dx, dy, dz;
  float dist_sq;
  short timer;
  short cue_index;
  void *entry;
  int anim_tag;
  void *unit_tag;
  void *obj;

  actor = datum_get(*(data_t **)0x6325a4, actor_handle);
  if (*((unsigned char *)actor + 0x13))
    return;
  if (*(short *)((char *)actor + 0xa2) == (short)-1)
    return;

  dx = *(float *)((char *)actor + 0xa8) - *(float *)((char *)actor + 0x12c);
  dy = *(float *)((char *)actor + 0xac) - *(float *)((char *)actor + 0x130);
  dz = *(float *)((char *)actor + 0xb0) - *(float *)((char *)actor + 0x134);
  dist_sq = dx * dx + dy * dy + dz * dz;

  if (*((unsigned char *)actor + 6)) {
    display_assert((const char *)0x253380, (const char *)0x253358, 0xae, 1);
    system_exit(-1);
  }

  if (!FUN_0002a3f0(actor_handle)) {
    if (!(dist_sq < *(float *)0x25337c))
      return;
  }

  timer = *(short *)((char *)actor + 0x9e);
  if (timer > 0) {
    timer = (short)(timer - 1);
    *(short *)((char *)actor + 0x9e) = timer;
  }

  if (!*((unsigned char *)actor + 0xa6))
    return;

  cue_index = *(short *)((char *)actor + 0xc4);
  if (cue_index != (short)-1) {
    entry = tag_block_get_element(
        (char *)global_scenario_get() + 0x444, (int)cue_index, 0x3c);
    anim_tag = *(int *)((char *)entry + 0x2c);
    if (anim_tag == -1) {
      obj = object_get_and_verify_type(*(int *)((char *)actor + 0x18), 3);
      unit_tag = tag_get(0x756e6974, *(int *)obj);
      anim_tag = *(int *)((char *)unit_tag + 0x44);
    }
    FUN_001ac180(*(int *)((char *)actor + 0x18), anim_tag, entry, 1);
  }
  *((unsigned char *)actor + 0xa6) = 0;
}



/* action_alert_next_position (0x12350) — readable C lift (restored pre-naked). */
void action_alert_next_position(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x12648 */
  /* cmp ecx, -1 -> je 0x1264b */
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  display_assert((char *)0x00253380, (char *)0x00253358, 275, 0);
  system_exit(0);
  /* cmp (int16_t)ebx, 1 -> jne 0x1240e */
  /* cmp (int16_t)eax, 0xffff -> jne 0x1264b */
  csmemset((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 80);
  /* test (char)eax, (char)eax -> je 0x124b8 */
  /* relift: cmp (char)eax, byte ptr [ecx + 0x68] -> je 0x124b8 */
  FUN_00064540((void *)(uintptr_t)edx, 0);
  FUN_00064570((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x12532 */
  /* cmp (int16_t)ecx, 2 -> jl 0x12522 */
  /* cmp (int16_t)ecx, 3 -> jg 0x12522 */
  FUN_00064570((void *)(uintptr_t)ecx);
  /* test eax, eax -> jne 0x124d5 */
  /* test (char)ebx, (char)ebx -> je 0x1253c */
  /* relift: cmp edi, dword ptr [eax] -> jl 0x12444 */
  /* test (char)eax, (char)eax -> jne 0x1257b */
  /* cmp (int16_t)eax, 5 -> jne 0x125af */
  FUN_00053f40((float *)(uintptr_t)edx, 80, 0, 16, (void *)(uintptr_t)ecx);
  /* cmp ecx, edx -> jl 0x125c5 */
  game_time_get();
  /* test (int16_t)esi, (int16_t)esi -> je 0x125fe */
  /* cmp eax, edx -> jne 0x125f3 */
  /* test eax, eax -> je 0x1260d */
  /* test ecx, ecx -> je 0x12609 */
  /* test (char)eax, (char)eax -> je 0x1261b */
  /* cmp ecx, eax -> jl 0x12626 */
  /* test (int16_t)esi, (int16_t)esi -> jge 0x12626 */
  /* relift: test dword ptr [ebp + eax*4 - 0x10], edx -> jne 0x125c8 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}


/* action_alert_perform (0x12660) — readable C lift (restored pre-naked). */
void action_alert_perform(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  datum_get((void *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [ebx + 0x9c], 0 -> je 0x12770 */
  /* relift: cmp word ptr [ebx + 0xa4], (int16_t)edi -> jne 0x12770 */
  /* test (char)eax, (char)eax -> je 0x126bc */
  display_assert((char *)0x00253380, (char *)0x00253358, 71, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebx + 0xa2], (int16_t)edi -> je 0x12718 */
  FUN_0002a3d0(0);
  /* test (char)eax, (char)eax -> je 0x12718 */
  distance_squared3d((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  actor_destination_tolerance(0);
  /* test (char)eax, 0x41 -> je 0x12706 */
  /* test (char)eax, 0x41 -> je 0x12770 */
  /* relift: cmp word ptr [ebx + 0x9e], 0 -> jg 0x12770 */
  /* test (char)eax, (char)eax -> jne 0x12770 */
  object_get_and_verify_type(0, 0);
  /* cmp (char)ecx, 0x1c -> je 0x12770 */
  action_alert_next_position();
  /* test (char)eax, (char)eax -> je 0x128ab */
  /* test (char)eax, (char)eax -> jne 0x128ab */
  /* relift: cmp word ptr [ebx + 0xa4], (int16_t)edi -> je 0x128ab */
  /* test (char)eax, (char)eax -> je 0x127b6 */
  display_assert((char *)0x00253380, (char *)0x00253358, 120, 0);
  system_exit(0);
  /* cmp eax, edi -> je 0x12886 */
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (int16_t)ecx, (int16_t)ecx -> jl 0x12886 */
  /* cmp ecx, edx -> jge 0x12886 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 80);
  FUN_000121e0(0.0f, 0.0f);
  FUN_001d9068();
  actor_move_to_move_position(0, edx);
  /* test (char)eax, (char)eax -> jne 0x128ab */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}


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

/* action_avoid_perform (0x12920) — readable C lift from XBE leaf. */
char action_avoid_perform(int actor_handle)
{
  void *actor;
  char buf_a[0x670];
  char buf_b[0x40];
  static char big[0x14740];
  int out0;
  int out1;
  short prep;
  short (*prep_fn)(int, void *, void *, void *, void *, void *);
  short (*finish_fn)(int, short, void *, int, void *, int);

  actor = datum_get(*(data_t **)0x6325a4, actor_handle);
  if (*((unsigned char *)actor + 6)) {
    display_assert((const char *)0x253380, (const char *)0x25339c, 0x37, 1);
    system_exit(-1);
  }
  if (*((unsigned char *)actor + 0x4c)) {
    csmemset(buf_a, 0, 0x670);
    *(short *)(buf_a + 4) = 6;
    prep_fn = (short (*)(int, void *, void *, void *, void *, void *))FUN_00027090;
    finish_fn =
        (short (*)(int, short, void *, int, void *, int))FUN_000272d0;
    prep = prep_fn(actor_handle, buf_a, buf_b, &out1, big, &out0);
    finish_fn(actor_handle, prep, buf_b, out1, big, out0);
  }
  return (char)(*(short *)((char *)actor + 0x280) == 0);
}



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

/* FUN_00012ad0 (0x12ad0) — readable C lift from XBE leaf.
 * Charge / ranged fire range lookup from actor + weapon tag. */
float FUN_00012ad0(int actor_handle, int action_type, void *charge_state)
{
  void *actor;
  void *weapon_tag;
  float result;
  unsigned char charged;

  actor = datum_get(*(data_t **)0x6325a4, actor_handle);
  result = 0.0f;

  if ((short)action_type != 2 && (short)action_type != 3) {
    if ((short)action_type != 4 && (short)action_type != 0)
      return result;
    if (!actor_has_ranged_weapon(actor_handle))
      return result;
    if (*(short *)((char *)actor + 0x268) < 7)
      return result;
    if (!(*(float *)0x2533c0 <= *(float *)((char *)actor + 0x608)))
      return result;
    return *(float *)((char *)actor + 0x608);
  }

  weapon_tag = tag_get(0x61637472, *(int *)((char *)actor + 0x58));
  if ((short)action_type == 3) {
    if (*(float *)0x2533c0 <= *(float *)((char *)weapon_tag + 0x388))
      result = *(float *)((char *)weapon_tag + 0x388);
  }

  charged = *((unsigned char *)charge_state + 0x30);
  if (charged) {
    if (!(result <= *(float *)((char *)weapon_tag + 0x37c)))
      return result;
    return *(float *)((char *)weapon_tag + 0x37c);
  }

  {
    float capped;
    capped = *(float *)((char *)weapon_tag + 0x37c) +
             *(float *)((char *)charge_state + 0x34);
    if (result <= capped)
      return capped;
  }
  return result;
}



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

/* FUN_00012c30 (0x12c30) — readable C lift (restored pre-naked). */
void FUN_00012c30(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  datum_get((void *)(uintptr_t)eax, 0);
  tag_get('rtca', 0);
  /* cmp (int16_t)eax, 2 -> je 0x12c80 */
  /* cmp (int16_t)eax, 3 -> jne 0x12cac */
  /* test (char)eax, (char)eax -> je 0x12cac */
  /* test (char)eax, (char)eax -> jne 0x12cac */
  FUN_0002a3d0(0);
  /* test (char)eax, (char)eax -> jne 0x12cac */
  /* relift: cmp word ptr [esi + 0x6e], (int16_t)eax -> jl 0x12ccc */
  /* relift: cmp word ptr [esi + 0xa0], 1 -> je 0x12ccc */
  /* relift: cmp word ptr [esi + 0xa0], (int16_t)edi -> jne 0x12d05 */
  /* test (char)eax, (char)eax -> jne 0x12d2e */
  /* relift: test dword ptr [ecx], 0x10000 -> je 0x12d2e */
  /* test (char)eax, (char)eax -> je 0x12dcf */
  /* test (char)eax, 0x41 -> jne 0x12d6e */
  game_time_get();
  /* relift: test dword ptr [eax], 0x100000 -> je 0x12e17 */
  /* test (char)eax, (char)eax -> jne 0x12df7 */
  /* cmp (int16_t)eax, 2 -> je 0x12df7 */
  /* cmp (int16_t)eax, 3 -> jne 0x12e17 */
  /* test (char)eax, (char)eax -> je 0x12e0f */
  /* test (char)eax, (char)eax -> jne 0x12e0f */

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}


/* action_charge_perform (0x13120) — readable C lift (restored pre-naked). */
void action_charge_perform(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  datum_get((void *)(uintptr_t)eax, 0);
  tag_get('rtca', 0);
  tag_get('vtca', 0);
  actor_combat_get_firing_variant_definition(0);
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp eax, -1 -> je 0x131b1 */
  /* cmp (int16_t)eax, 5 -> je 0x131a8 */
  /* cmp (int16_t)eax, 4 -> je 0x131a8 */
  /* cmp (int16_t)eax, 2 -> je 0x13396 */
  /* cmp (int16_t)eax, 3 -> je 0x13396 */
  /* relift: test dword ptr [edx], 0x20000 -> je 0x131f5 */
  /* relift: cmp word ptr [esi + 0x6e], 5 -> jl 0x131f5 */
  /* test (char)eax, (char)eax -> jne 0x131f5 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x13220 */
  /* cmp (int16_t)eax, 1 -> jne 0x13230 */
  /* relift: cmp byte ptr [ecx + 0x122], 2 -> jg 0x13230 */
  /* relift: test dword ptr [edx], 0x40000 -> je 0x13247 */
  /* test (char)eax, (char)eax -> je 0x13253 */
  /* relift: cmp byte ptr [ecx + 0x124], 1 -> jg 0x1326d */
  /* test (char)eax, 0x41 -> jne 0x13560 */
  /* test (char)eax, 1 -> jne 0x13560 */
  actor_has_ranged_weapon(0);
  /* test (char)eax, (char)eax -> je 0x131a8 */
  /* test (char)eax, (char)eax -> jne 0x131a8 */
  FUN_000210f0(0);
  /* test ecx, ecx -> je 0x13331 */
  /* test (char)eax, 0x41 -> jne 0x13331 */
  /* test (char)eax, 0x41 -> je 0x13331 */
  /* test (char)eax, 0x41 -> jne 0x1335f */
  /* test (char)eax, 0x41 -> jne 0x13560 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x13560 */
  /* cmp (int16_t)eax, 1 -> je 0x13560 */
  actor_has_ranged_weapon(0);
  /* test (char)eax, (char)eax -> jne 0x133bb */
  /* test (char)eax, (char)eax -> je 0x133e2 */
  display_assert((char *)0x00253380, (char *)0x002533f4, 288, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x1342b */
  /* test (char)eax, (char)eax -> jne 0x1342b */
  /* test (char)eax, (char)eax -> jne 0x1342b */
  /* test (char)eax, (char)eax -> jne 0x1340e */
  actor_has_ranged_weapon(0);
  /* test (char)eax, (char)eax -> jne 0x1342f */
  /* test (char)eax, (char)eax -> je 0x13420 */
  /* test (char)eax, (char)eax -> je 0x13478 */
  /* test (char)eax, 0x41 -> jne 0x1345a */
  /* test (char)eax, 0x41 -> jne 0x13478 */
  /* test (char)ebx, (char)ebx -> je 0x13498 */
  game_time_get();
  /* test (char)ecx, (char)ecx -> jne 0x134f8 */
  /* relift: cmp word ptr [eax + 0x9c], 0 -> jle 0x13502 */
  /* test (char)eax, (char)eax -> je 0x13560 */
  /* relift: cmp word ptr [eax + 0x9c], 0 -> jg 0x13532 */
  /* test (char)eax, (char)eax -> je 0x13593 */
  /* cmp esi, -1 -> je 0x13586 */
  unit_is_busy(0);
  /* test (char)eax, (char)eax -> je 0x13586 */
  /* test (char)eax, (char)eax -> jne 0x13b9d */
  /* cmp (int16_t)eax, 2 -> je 0x135b2 */
  /* cmp (int16_t)eax, 3 -> jne 0x13b9d */
  /* test eax, eax -> je 0x13b9d */
  game_time_get();
  /* test (char)eax, (char)eax -> je 0x136af */
  display_assert((char *)0x00253380, (char *)0x002533f4, 487, 0);
  system_exit(0);
  object_get_and_verify_type(0, 0);
  FUN_00012fe0((float *)(uintptr_t)eax);
  /* test (char)eax, 0x41 -> jne 0x13751 */
  FUN_00013070((float *)(uintptr_t)eax, (float *)0);
  vector3d_scale_add((float *)0, (float *)0, 0.0f, (float *)0);
  vector3d_scale_add((float *)0, (float *)0, 0.0f, (float *)0);
  normalize3d((float *)(uintptr_t)ecx);
  /* cmp (int16_t)eax, 3 -> jne 0x139a3 */
  /* test (char)ecx, (char)ecx -> jne 0x139a3 */
  /* relift: cmp word ptr [eax + 0x9c], 0 -> jne 0x138b5 */
  /* test dl, dl -> jne 0x138b5 */
  projectile_aim_ballistic(0.0f, 0.0f, (float *)(uintptr_t)ebx, (float *)(uintptr_t)ecx, 0, (float *)0, (float *)0, 0, (float *)0, (float *)0, (float *)0, (float *)0, (float *)0, (float *)0);
  /* test (char)eax, (char)eax -> je 0x13a8e */
  magnitude3d((float *)(uintptr_t)eax);
  magnitude3d((float *)(uintptr_t)ecx);
  /* test (char)ecx, (char)ecx -> je 0x13a29 */
  FUN_00013090((float *)(uintptr_t)eax, (float *)0, (float *)0);
  /* test (char)eax, 0x41 -> jne 0x13a8e */
  /* cmp (int16_t)eax, 3 -> jne 0x13a5b */
  /* test (char)eax, (char)eax -> je 0x13a5b */
  /* test (char)eax, (char)eax -> jne 0x13aa3 */
  /* test (char)eax, (char)eax -> je 0x13b0c */
  /* test (char)eax, (char)eax -> jne 0x13b0c */
  magnitude3d((float *)(uintptr_t)eax);
  /* test (char)eax, 0x41 -> jne 0x13b0c */
  /* test (char)eax, (char)eax -> je 0x13ad7 */
  magnitude3d((float *)(uintptr_t)eax);
  unit_melee_attack_begin(0, 0, 0);
  /* test (char)eax, (char)eax -> je 0x13b9d */
  FUN_00046f10(43, 0, 0, 0, 0, 0, 0);
  game_time_get();
  /* cmp (int16_t)ecx, 3 -> jne 0x13c09 */
  /* test (char)eax, (char)eax -> jne 0x13c09 */
  /* test (char)eax, (char)eax -> jne 0x13c09 */
  /* test (char)eax, (char)eax -> je 0x13bd5 */
  /* relift: cmp word ptr [edi + 0xe], 0xf -> jle 0x13c09 */
  /* test (char)eax, 0x41 -> jne 0x13c09 */
  /* cmp (int16_t)ecx, 4 -> je 0x13c15 */
  /* cmp (int16_t)ecx, 5 -> jne 0x13c1e */
  FUN_00012ad0(0, 0, (char *)0);
  /* test (char)eax, (char)eax -> jne 0x13d77 */
  /* test (char)eax, (char)eax -> je 0x13d77 */
  /* test (char)eax, (char)eax -> jne 0x13ccb */
  /* test (char)eax, (char)eax -> jne 0x13ccb */
  /* test (char)eax, (char)eax -> je 0x13ccb */
  /* relift: cmp word ptr [edi + 4], 3 -> jne 0x13c81 */
  /* test (char)eax, 0x41 -> jne 0x13c96 */
  actor_move_to_prop(0, 0, 0.0f);
  /* test (char)eax, (char)eax -> je 0x13cc1 */
  FUN_0002a330(0);
  FUN_0002f1a0(0);
  /* relift: cmp word ptr [esi + 0x268], 7 -> jl 0x13d77 */
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)eax, 0x41 -> jne 0x13d12 */
  /* cmp (int16_t)eax, 2 -> je 0x13d22 */
  /* cmp (int16_t)eax, 3 -> jne 0x13d37 */
  /* test (char)eax, (char)eax -> jne 0x13d63 */
  /* test (char)eax, (char)eax -> jne 0x13d63 */
  /* test (char)eax, (char)eax -> jne 0x13d63 */
  /* test (char)ecx, (char)ecx -> je 0x13d63 */
  /* test (char)eax, (char)eax -> jne 0x13d5f */
  FUN_0002a3d0(0);
  /* test (char)eax, (char)eax -> je 0x13d5f */
  /* test (char)eax, 0x41 -> jne 0x13d63 */
  actor_perception_unreachable(0, 0, ecx);
  /* cmp (int16_t)eax, 2 -> je 0x13d9d */
  /* cmp (int16_t)eax, 3 -> je 0x13d9d */
  /* cmp (int16_t)eax, 4 -> je 0x13d93 */
  /* cmp (int16_t)eax, 5 -> jne 0x13dc4 */
  /* test (char)eax, (char)eax -> jne 0x13dbb */
  /* test (char)eax, (char)eax -> jne 0x13dbb */
  /* test (char)eax, (char)eax -> jne 0x13dbb */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* relift: cmp word ptr [0x4761d8], 0x20 -> jl 0x13e39 */
  display_assert((char *)0x00253440, (char *)0x002533f4, 889, ebx);
  system_exit(0);
  FUN_0014df70(0, (float *)0, (float *)0, 0, (void *)0);
  /* relift: cmp word ptr [0x4761d8], (int16_t)ebx -> jg 0x13eae */
  display_assert((char *)0x00253418, (char *)0x002533f4, 897, ebx);
  system_exit(0);
  /* test (char)ecx, (char)ecx -> je 0x13ee7 */
  unit_estimate_position(0, ebx, (void *)(uintptr_t)edx, (void *)0, (void *)0, (void *)(uintptr_t)ecx);
  datum_get((void *)(uintptr_t)eax, 0);
  tag_get('rtca', 0);
  game_time_get();
  /* test eax, eax -> jne 0x13f6a */
  display_assert((char *)0x0025334c, (char *)0x002533f4, 47, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)edx, 0, 56);
  game_time_get();
  /* cmp (int16_t)eax, 5 -> je 0x14261 */
  /* cmp (int16_t)eax, 4 -> je 0x14261 */
  /* cmp (int16_t)eax, 2 -> jne 0x14226 */
  /* test (char)eax, (char)eax -> je 0x13fbe */
  object_get_and_verify_type(0, 0);
  /* cmp eax, -1 -> jne 0x14009 */
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> jne 0x140a4 */
  /* relift: cmp word ptr [ebx + 0x9c], 0 -> jg 0x140a4 */
  get_global_random_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  /* test (char)ecx, (char)ecx -> je 0x140cb */
  unit_get_melee_range_and_ticks(0, ecx, (void *)(uintptr_t)eax, (float *)(uintptr_t)edx, (void *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1421b */
  /* relift: test dword ptr [eax], 0x8000000 -> je 0x1411c */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x14164 */
  tag_get('vtca', 0);
  /* test eax, eax -> je 0x1414c */
  error(0, (char *)0x0025348c);
  FUN_00012ad0(0, 0, (char *)0);
  /* cmp (int16_t)esi, 3 -> jne 0x1419c */
  /* test (char)eax, 0x41 -> jne 0x141b1 */
  actor_move_to_prop(0, 0, 0.0f);
  /* test (char)eax, (char)eax -> je 0x14207 */
  FUN_0002a330(0);
  FUN_00013dd0(0, (float *)0);
  /* test (char)eax, (char)eax -> je 0x14207 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x14256 */
  /* relift: test dword ptr [ebx], 0x20000 -> je 0x14256 */
  /* relift: cmp word ptr [esi + 0x6e], 5 -> jl 0x14256 */
  /* test (char)eax, (char)eax -> jne 0x14256 */
  datum_get((void *)(uintptr_t)ecx, 0);
  datum_get((void *)(uintptr_t)edx, 0);
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  display_assert((char *)0x0025334c, (char *)0x002534bc, 33, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)esi, 0, 20);
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x1444d */
  /* cmp eax, -1 -> je 0x143b0 */
  FUN_00064b40(0, 0, 0, 0);
  /* cmp eax, -1 -> je 0x14447 */
  /* test (char)ecx, (char)ecx -> jne 0x1440e */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* relift: cmp word ptr [ecx + 0x32], 2 -> jl 0x143f5 */
  /* test (char)eax, (char)eax -> je 0x1442c */
  FUN_0002f1a0(0);
  actor_move_to_prop(0, 0, 0.0f);
  /* test (char)eax, (char)eax -> jne 0x1444d */
  datum_get((void *)(uintptr_t)ecx, 0);
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp ecx, -1 -> je 0x144ba */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp ecx, -1 -> je 0x144c9 */
  /* test eax, eax -> je 0x144e1 */
  /* cmp eax, -1 -> je 0x144e1 */
  prop_get_active_by_unit_index(0, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp edx, ecx -> jne 0x1453e */
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp eax, -1 -> je 0x145b6 */
  /* cmp eax, -1 -> je 0x145b6 */
  prop_get_active_by_unit_index(0, 0);
  /* cmp eax, -1 -> je 0x1458c */
  unit_get_head_position(0, (float *)(uintptr_t)ecx);
  FUN_00027a60(0, 0, 0, (void *)(uintptr_t)eax);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp eax, -1 -> je 0x145ee */
  ai_conversation_finish(0, 0, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp eax, -1 -> je 0x1461e */
  ai_conversation_finish(0, 0, 0);
  /* test esi, esi -> jne 0x14648 */
  display_assert((char *)0x0025334c, (char *)0x002534e0, 30, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)esi, 0, 0);
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (int16_t)ecx, (int16_t)ecx -> jle 0x146e0 */
  /* test dl, dl -> je 0x146e0 */
  /* cmp (int16_t)ecx, -1 -> je 0x146e0 */
  /* test dl, dl -> jne 0x146e0 */
  FUN_00024be0(0, 0, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* relift: cmp word ptr [eax + 0x6e], 5 -> jl 0x1476a */
  FUN_001d90e0();
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x147b8 */
  display_assert((char *)0x00253380, (char *)0x002534e0, 55, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x14b2f */
  tag_get('rtca', 0);
  actor_combat_get_firing_variant_definition(0);
  /* test (char)eax, (char)eax -> jne 0x14a26 */
  /* test (char)eax, (char)eax -> je 0x14912 */
  /* relift: test byte ptr [ebx], 0x20 -> je 0x14912 */
  actor_find_pathfinding_location(0);
  actor_has_accessible_firing_position(0, (float *)(uintptr_t)eax, 0, 0);
  /* test (char)eax, (char)eax -> je 0x14912 */
  /* relift: cmp word ptr [esi + 0x3b8], -1 -> je 0x148a2 */
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  actor_destination_tolerance(0);
  distance_squared3d((float *)(uintptr_t)edx, (float *)(uintptr_t)ebx);
  /* test (char)eax, 0x41 -> jne 0x148a2 */
  /* test (char)eax, (char)eax -> je 0x148f0 */
  /* test (char)eax, (char)eax -> jne 0x148f0 */
  /* cmp eax, -1 -> je 0x14a26 */
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> jne 0x14a26 */
  FUN_0002f1a0(0);
  csmemset((void *)(uintptr_t)edx, 0, 1648);
  FUN_00027090(0, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  FUN_000272d0(0, 0, (void *)(uintptr_t)ecx, 0, ecx, edx);
  /* cmp (int16_t)eax, 0xffff -> jne 0x14986 */
  /* cmp (int16_t)eax, (int16_t)ebx -> je 0x14a26 */
  get_global_random_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  /* relift: cmp word ptr [esi + 0x15e], 0 -> jle 0x14a11 */
  object_get_and_verify_type(0, 0);
  tag_get('ihev', 0);
  /* test (char)eax, 0x41 -> jne 0x14a11 */
  /* test (char)eax, 0x41 -> jne 0x14a11 */
  FUN_001d9068();
  /* relift: cmp word ptr [esi + 0x268], 7 -> jl 0x14b2f */
  datum_get((void *)(uintptr_t)ecx, 0);
  actor_has_ranged_weapon(0);
  /* test (char)eax, (char)eax -> je 0x14b1b */
  /* cmp eax, -1 -> je 0x14b1b */
  /* relift: cmp word ptr [esi + 0x3b8], -1 -> je 0x14b1b */
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  actor_destination_tolerance(0);
  distance_squared3d((float *)(uintptr_t)eax, (float *)(uintptr_t)ebx);
  distance_squared3d((float *)(uintptr_t)ebx, (float *)(uintptr_t)edx);
  /* test (char)eax, 0x41 -> jne 0x14b1b */
  actor_perception_unreachable(0, 0, eax);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp eax, -1 -> je 0x14b67 */
  unit_stop_running_blindly(0);
  datum_get((void *)(uintptr_t)ecx, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* relift: cmp word ptr [eax + 0xc], 0 -> jle 0x14be3 */
  FUN_001d90e0();
  datum_get((void *)(uintptr_t)eax, 0);
  tag_get('rtca', 0);
  /* test (char)eax, (char)eax -> je 0x14c6a */
  display_assert((char *)0x00253380, (char *)0x00253504, 522, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)edx, 0, 1648);
  /* test (char)eax, 0x41 -> jne 0x14d00 */
  actor_get_firing_position_group(0, 0, 0);
  FUN_00025c10(0, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx);
  FUN_000272d0(0, 0, (void *)(uintptr_t)edx, 0, edx, ecx);
  /* test (char)ecx, (char)ecx -> jne 0x14d78 */
  /* cmp eax, -1 -> je 0x14e7c */
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp (int16_t)eax, 2 -> jl 0x14dc5 */
  /* cmp (int16_t)eax, 3 -> jg 0x14dc5 */
  actor_perception_find_prop_pathfinding_location(0, 0);
  /* cmp eax, -1 -> jne 0x14dd3 */
  path_input_new((void *)(uintptr_t)ecx, eax, 0, 0);
  path_input_set_start((void *)(uintptr_t)eax, (float *)(uintptr_t)edi, 0);
  paths_dispose((void *)(uintptr_t)eax, 0);
  path_state_new((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, (void *)0);
  FUN_0005e0d0((void *)(uintptr_t)edx, (float *)(uintptr_t)eax, 0, 0);
  FUN_0005ff70((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x14e7c */
  path_state_approach_point((void *)(uintptr_t)edx, (float *)(uintptr_t)eax, 0, (char *)(uintptr_t)edx, (char *)(uintptr_t)ecx);
  datum_get((void *)(uintptr_t)ecx, 0);
  display_assert((char *)0x00253380, (char *)0x00253504, 613, 0);
  system_exit(0);
  /* cmp eax, ecx -> je 0x14fe2 */
  /* cmp eax, ecx -> je 0x14fe2 */
  /* relift: cmp word ptr [esi + 8], (int16_t)ecx -> je 0x14fe2 */
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  datum_get((void *)(uintptr_t)eax, 0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  unit_estimate_position(0, 0, (void *)(uintptr_t)ebx, (void *)0, (void *)0, (void *)(uintptr_t)eax);
  ai_test_line_of_sight((float *)(uintptr_t)ecx, 0, (float *)(uintptr_t)edx, 0, 0, 0, 0, edx);
  /* cmp (int16_t)ecx, 2 -> jl 0x14fab */
  /* cmp (int16_t)ecx, 3 -> jg 0x14fab */
  /* test (int16_t)eax, (int16_t)eax -> je 0x14fb9 */
  /* cmp (int16_t)eax, 3 -> jne 0x14fd9 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp edx, ecx -> jne 0x1501e */
  /* cmp (int16_t)eax, 9 -> jl 0x1503a */
  /* cmp (int16_t)eax, 0xc -> jg 0x1503a */
  datum_get((void *)(uintptr_t)eax, 0);
  /* test esi, esi -> jne 0x15095 */
  display_assert((char *)0x0025334c, (char *)0x00253504, 44, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)esi, 0, 48);
  actor_situation_try_new_target(0, 0);
  /* cmp (int16_t)edi, 9 -> jl 0x15117 */
  /* cmp (int16_t)edi, 0xc -> jg 0x15117 */
  get_global_random_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0x15136 */
  FUN_00014c10(0, (void *)0, 0);
  /* relift: cmp word ptr [esi + 8], -1 -> jne 0x1510e */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* relift: cmp word ptr [eax + 0x9e], (int16_t)ecx -> jne 0x151aa */
  /* cmp ecx, -1 -> je 0x151aa */
  /* cmp (int16_t)eax, 9 -> jl 0x151aa */
  /* cmp (int16_t)eax, 0xc -> jg 0x151aa */
  unit_start_running_blindly(0);
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x1522b */
  /* cmp ecx, -1 -> je 0x1522b */
  /* cmp (int16_t)eax, 9 -> jl 0x1522b */
  /* cmp (int16_t)eax, 0xc -> jg 0x1522b */
  unit_start_running_blindly(0);
  /* relift: cmp word ptr [esi + 0xa8], 0 -> jle 0x15245 */
  game_time_get();
  datum_get((void *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [esi + 0xa8], (int16_t)ebx -> jle 0x1528e */
  /* cmp eax, -1 -> je 0x152ca */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* relift: cmp word ptr [eax + 0x32], (int16_t)ebx -> jle 0x152ca */
  /* relift: cmp dword ptr [esi + 0xb8], -1 -> je 0x152f3 */
  /* cmp (int16_t)eax, 9 -> jl 0x1532d */
  /* cmp (int16_t)eax, 0xc -> jg 0x1532d */
  /* cmp (int16_t)eax, 0xffff -> jne 0x1536a */
  FUN_0002f1a0(0);
  /* relift: cmp byte ptr [esi + 0x4c], (char)ebx -> je 0x153d6 */
  actor_move_to_firing_position(0, eax, (void *)(uintptr_t)ebx);
  /* test (char)eax, (char)eax -> je 0x1539d */
  /* cmp (int16_t)eax, 0xffff -> je 0x153c6 */
  FUN_00024be0(0, 0, ebx);
  FUN_0002f1a0(0);
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x1541a */
  display_assert((char *)0x00253380, (char *)0x00253504, 470, 0);
  system_exit(0);
  /* cmp eax, -1 -> je 0x15519 */
  /* relift: cmp word ptr [esi + 0x3b8], -1 -> je 0x15519 */
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  FUN_0002a3f0(0);
  /* test (char)eax, (char)eax -> je 0x15492 */
  /* relift: cmp word ptr [esi + 0x46c], 3 -> jne 0x15492 */
  /* relift: cmp (int16_t)edx, word ptr [esi + 0x3b8] -> jne 0x15492 */
  actor_destination_tolerance(0);
  /* cmp esi, -1 -> je 0x15511 */
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x1550f */
  /* cmp (int16_t)eax, 1 -> je 0x1550f */
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp (int16_t)eax, 9 -> jl 0x15560 */
  /* cmp (int16_t)eax, 0xc -> jg 0x15560 */
  /* relift: cmp word ptr [esi + 2], 0 -> jle 0x15572 */
  /* relift: cmp word ptr [esi + 8], (int16_t)eax -> jne 0x15584 */
  /* relift: cmp word ptr [edi + 0x3b8], (int16_t)eax -> jne 0x1559a */
  FUN_000153e0(0);
  /* test (char)eax, (char)eax -> je 0x15648 */
  /* relift: cmp word ptr [edi + 0x3b8], -1 -> jne 0x155d1 */
  display_assert((char *)0x00253600, (char *)0x00253504, 152, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi], 0 -> je 0x155dd */
  datum_get((void *)(uintptr_t)eax, 0);
  actor_situation_update_target_status(0);
  actor_situation_combat_status_update(0);
  /* cmp eax, 3 -> ja 0x1567a */
  /* test (char)eax, (char)eax -> jne 0x1567a */
  /* test (char)eax, (char)eax -> je 0x156e9 */
  /* test (char)eax, (char)eax -> jne 0x156e9 */
  /* relift: cmp word ptr [esi + 8], (int16_t)ebx -> je 0x156af */
  /* relift: cmp word ptr [esi], 0 -> jne 0x156af */
  FUN_00014e90(0, (char *)0);
  /* test (char)eax, (char)eax -> je 0x156af */
  /* test (char)eax, (char)eax -> je 0x156bf */
  /* test (char)eax, (char)eax -> je 0x156e9 */
  FUN_00014c10(0, (void *)0, 0);
  /* relift: cmp word ptr [esi + 8], -1 -> jne 0x156e9 */
  game_time_get();
  /* cmp (int16_t)eax, 9 -> jl 0x15711 */
  /* cmp (int16_t)eax, 0xc -> jg 0x15711 */
  /* cmp eax, -1 -> je 0x15711 */
  FUN_001a6bc0(0);
  /* test (char)eax, (char)eax -> jne 0x15711 */
  /* relift: cmp word ptr [esi + 0xc], 0 -> jle 0x157f3 */
  /* relift: cmp word ptr [esi + 8], (int16_t)eax -> je 0x157f3 */
  /* test (char)ecx, (char)ecx -> jne 0x157f3 */
  /* relift: cmp dword ptr [edi + 0x18], eax -> je 0x157f3 */
  game_time_get();
  /* test (char)eax, (char)eax -> je 0x15759 */
  /* cmp ecx, ebx -> jl 0x157f3 */
  /* cmp (int16_t)eax, 0xc -> je 0x157e2 */
  /* cmp (int16_t)eax, 0xb -> je 0x157e2 */
  /* cmp (int16_t)eax, 9 -> je 0x157da */
  /* cmp (int16_t)eax, 0xa -> je 0x157da */
  /* cmp ecx, -1 -> je 0x15793 */
  datum_get((void *)(uintptr_t)edx, 0);
  FUN_00046f10(ecx, 0, 0, 0, 0, 0, 0);
  FUN_00046f10(33, 0, 0, 0, 0, 0, 0);
  FUN_001a74d0(0, 0);
  /* test (char)eax, (char)eax -> jne 0x15844 */
  /* test (char)eax, (char)eax -> jne 0x15808 */
  /* test (char)eax, (char)eax -> jne 0x15844 */
  /* relift: cmp word ptr [esi + 2], 0 -> jg 0x15844 */
  /* relift: cmp word ptr [esi + 8], -1 -> jne 0x15844 */
  /* test (char)eax, (char)eax -> jne 0x15859 */
  /* test (char)eax, (char)eax -> jne 0x15844 */
  display_assert((char *)0x00253528, (char *)0x00253504, 302, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x15859 */
  /* test (char)eax, (char)eax -> jne 0x15859 */
  datum_get((void *)(uintptr_t)ecx, 0);
  display_assert((char *)0x0025334c, (char *)0x00253638, 114, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)esi, 0, 68);
  datum_get((void *)(uintptr_t)ecx, 0);
  display_assert((char *)0x0025334c, (char *)0x00253638, 134, ebx);
  system_exit(0);
  csmemset((void *)(uintptr_t)esi, 0, 68);
  /* test (char)eax, (char)eax -> jne 0x159b2 */
  /* test (char)eax, (char)eax -> jne 0x159b2 */
  datum_get((void *)(uintptr_t)ecx, 0);
  display_assert((char *)0x0025334c, (char *)0x00253638, 172, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)esi, 0, 68);
  /* relift: cmp word ptr [edi + 0x15e], 4 -> jne 0x15a50 */
  /* test (char)eax, (char)eax -> jne 0x15b09 */
  /* test (char)eax, (char)eax -> jne 0x15b09 */
  /* cmp eax, -1 -> je 0x15b09 */
  datum_get((void *)(uintptr_t)edx, 0);
  /* cmp eax, 3 -> ja 0x15b08 */
  actor_perception_find_prop_pathfinding_location(0, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}


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

