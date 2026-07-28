/* 0x18e3c0 is structure-BSP getter; Capstone named it scenario_get (see decl.h). */

#include "x87_math.h" /* x87_fatan2f: inline FPATAN atan2, matches original */

/* MSVC 7.1 FABS intrinsic: declared+pragma here so fabs() inlines to a single
 * FABS instruction instead of a CRT call. */
extern double __cdecl fabs(double);
#if defined(_MSC_VER) && !defined(__clang__)
#pragma intrinsic(fabs)
#else
/* clang builds with -fno-builtin, which ignores the intrinsic pragma above and
 * emits a real CRT call to fabs. The original inlines a single x87 FABS. Force
 * clang to inline via the always-available builtin so the codegen matches the
 * binary (and so equivalence harnesses don't see an external fabs stub). */
#define fabs __builtin_fabs
#endif

/* FUN_00061ca0 (0x61ca0)
 *
 * Per-tick debug path-obstacle-avoidance key handler.  When the debug enable
 * byte (0x3340a9) is set and the developer console is not active, polls debug
 * keys and toggles the mode/enable bytes, optionally (re)builds the obstacle
 * avoidance record and advances it, then draws the current obstacle discs and
 * path steps.  Runs the two draw calls whenever the enable byte is set,
 * regardless of console state.
 *
 * Confirmed from disassembly at 0x61ca0:
 *   - scenario_get() is 0-arg (returns the current scenario tag base; 50+
 *     ported callers).  The 7 pushes Ghidra attributed to scenario_get are
 *     actually FUN_00060ea0's stack args (cdecl arg mis-grouping, §7).
 *   - FUN_00060ea0 is __thiscall + @eax: ECX=0x331f68 (avoidance record),
 *     EAX=0x5ab250 (end point2d), plus 9 cdecl stack args.  ADD ESP,0x24
 *     (36 bytes = 9 args) proves the split is 0 (scenario_get) + 9, not 7+2.
 *   - FUN_000615b0 takes @eax=0x331f68 (the record); its return is discarded.
 *   - path_obstacles_debug_render(&0x3334a0 obstacles, 0x5ab240 radius) and
 *     FUN_000609e0(&0x331f68 path) are clean cdecl (ADD ESP,0xc = 2+1).
 */
void FUN_00061ca0(void)
{
  void *scenario;

  if (*(char *)0x3340a9 != 0) {
    if (!console_is_active()) {
      if (input_key_is_down(0x22)) {
        *(char *)0x3340a8 = 1;
        *(char *)0x3340a9 = 0;
      }
      if (input_key_is_down(0x31)) {
        *(char *)0x3340a8 = 0;
        *(char *)0x3340a9 = 0;
      }
      if (input_key_is_down(0x3f)) {
        scenario = scenario_get();
        FUN_00060ea0((void *)0x331f68, (float *)0x5ab250, (void *)0x3334a0,
                     scenario, *(unsigned char *)0x5ab244, *(float *)0x5ab240,
                     (float *)0x5ab260, *(int *)0x5ab25c, *(float *)0x5ab248,
                     *(unsigned char *)0x5ab245, 0);
      }
      if (input_key_is_down(0x26)) {
        FUN_000615b0((void *)0x331f68);
      }
    }
    path_obstacles_debug_render((void *)0x3334a0, *(float *)0x5ab240);
    FUN_000609e0((void *)0x331f68);
  }
  return;
}

/* FUN_00061d80 (0x61d80)
 *
 * Zero-clear three consecutive int16 fields (6 bytes) at the pointer arg.
 * Disassembly: XOR ECX,ECX then MOV WORD PTR [EAX+{0,2,4}],CX -- the 0x66
 * operand-size prefix confirms 16-bit store width (LOADW), so the target is
 * a short[3] / small struct of three int16 fields, not int[3].  cdecl, one
 * stack pointer arg; leaf, no calls, no FPU.
 */
void FUN_00061d80(int16_t *out)
{
  out[0] = 0;
  out[1] = 0;
  out[2] = 0;
  return;
}

/* FUN_00061da0 (0x61da0)
 *
 * Store a float/int pair into a structure: value0 (float) -> [out+0x0],
 * value1 (int) -> [out+0x4].  cdecl, three stack args, void return; leaf,
 * no calls.  Disassembly: FLDS 0xc(ebp) / FSTPS (eax) proves the first field
 * is a float copied through the x87 (not a plain MOV); the second field is a
 * plain MOV of a 32-bit int/handle.  The Ghidra "undefined4" for arg0 masked
 * the float store.
 */
void FUN_00061da0(void *out, float value0, int value1)
{
  *(float *)out = value0;
  *((int *)out + 1) = value1;
  return;
}

/* FUN_00061dc0 (0x61dc0)
 *
 * 2D rotation / complex multiply.  Rotates the 2D vector (point[0], point[1])
 * by an angle whose sine is rot_sin and cosine is rot_cos, writing the result
 * to out[0..1]:
 *   out[0] = rot_cos*point[0] - rot_sin*point[1]   (real part, FSUBP)
 *   out[1] = rot_sin*point[0] + rot_cos*point[1]   (imag part, FADDP)
 * cdecl, four stack args, void return; leaf, no calls.  Disassembly verified:
 * each product uses a memory-operand FMUL in the exact binary order, and the
 * real part is evaluated first (FSUBRP st1-st0 = cos*x - sin*y, NOT inverted)
 * then the imag part (FADDP), storing real then imag.  Computing both into
 * named temps (real before imag) before the two stores reproduces that
 * evaluation order exactly -- 100% VC71 (18/18 insns).
 */
void FUN_00061dc0(float *point, float rot_sin, float rot_cos, float *out)
{
  float real;
  float imag;

  real = rot_cos * point[0] - rot_sin * point[1];
  imag = rot_sin * point[0] + rot_cos * point[1];
  out[0] = real;
  out[1] = imag;
  return;
}

/* Projection axis remapping table at 0x28cb10.
 * Indexed as [projection_axis * 2 + projection_sign][component].
 * Maps a 3D projection basis + sign to two axis indices for 2D projection.
 * Component 0 -> out[0], component 1 -> out[1]. */
static const short g_projection3d_mappings[6][2] = {
  { 2, 1 }, { 1, 2 }, { 0, 2 }, { 2, 0 }, { 1, 0 }, { 0, 1 },
};

/* 0x61df0 — Project a 3D point onto a 2D plane.
 * Selects two of the three float lanes of `point` according to the projection
 * axis (0..2) and sign (0/1), writing them to out_projected[0] and [1].
 * real_math.h:0x35b/0x35c assert projection in [_x,_z] and sign in {0,1}. */
void FUN_00061df0(void *point, short projection, unsigned char sign,
                  void *out_projected)
{
  int idx;
  float tmp;

  if ((projection < 0) || (projection > 2)) {
    display_assert("projection>=_x && projection<=_z", "..\\math\\real_math.h",
                   0x35b, 1);
    system_exit(-1);
  }
  if (!(~(sign & ~1))) {
    display_assert("~(sign&~1)", "..\\math\\real_math.h", 0x35c, 1);
    system_exit(-1);
  }
  idx = sign + projection * 2;
  /* out[1] loaded first (FPU), out[0] copied as a raw dword, matching the
   * original's interleaved fld / integer-mov scheduling. */
  tmp = ((float *)point)[g_projection3d_mappings[idx][1]];
  ((unsigned int *)out_projected)[0] =
    ((unsigned int *)point)[g_projection3d_mappings[idx][0]];
  ((float *)out_projected)[1] = tmp;
}

/* FUN_00061e80 (0x61e80) — readable C lift from XBE leaf. */
int FUN_00061e80(float *p0, float *p1, float radius)
{
  float dx = p1[0] - p0[0];
  float dy = p1[1] - p0[1];
  return (dx * dx + dy * dy) <= (radius * radius);
}



/* 0x61ec0 — 3D point-in-radius test.
 * Returns 1 when the squared 3D distance between points p0 and p1 (x=[0],
 * y=[1], z=[2] lanes) is <= radius*radius, else 0.  Pure leaf, cdecl, three
 * stack args (two float*, one float).  The sum order is y-term, z-term,
 * x-term, matching the decompiler's fld ordering at 0x61ed9; every product is
 * a self-multiply so there is no operand-order/cross-product hazard.  This is
 * the 3D counterpart to the 2D test at 0x61e80. */
int FUN_00061ec0(float *p0, float *p1, float radius)
{
  if ((p1[1] - p0[1]) * (p1[1] - p0[1]) + (p1[2] - p0[2]) * (p1[2] - p0[2]) +
        (p1[0] - p0[0]) * (p1[0] - p0[0]) <=
      radius * radius) {
    return 1;
  }
  return 0;
}

/* 0x61f10 - 2D ray/segment vs circle nearest-hit solve.
 *
 * Given the 2D unit direction vec_a, the segment endpoints pt0 and pt1, and a
 * circle radius, projects the segment vector (pt1-pt0) onto vec_a (dot).  When
 * dot > 0, forms d = |pt1-pt0|^2 - radius^2: if d <= 0 the origin is inside the
 * circle and out=0 is returned (hit); otherwise the discriminant dot^2 - d is
 * tested and, if >= 0, out = dot - sqrt(disc) (the near intersection distance).
 * Returns 1 when a value was written to out, 0 otherwise (dot <= 0, or negative
 * discriminant).  Comparisons use the shared 0.0f constant at 0x2533c0 and keep
 * the original ordered/unordered (NaN) branch behaviour.
 *
 * Register ABI (prologue at 0x61f10): no entry moves; EAX read as vec_a
 * (FMUL [EAX],[EAX+4]), ECX as pt0 (FSUB [ECX],[ECX+4]), EDX as pt1
 * (FLD [EDX],[EDX+4]), ESI as the out pointer (FSTP [ESI]/MOV [ESI],0).
 * radius is the sole stack arg [EBP+8] (float).  Return AL (char). */
char FUN_00061f10(float *vec_a, float *pt0, float *pt1, float *out, float radius)
{
  float dx;
  float dy;
  float dot;
  float disc;

  dx = pt1[0] - pt0[0];
  dy = pt1[1] - pt0[1];
  dot = dx * vec_a[0] + dy * vec_a[1];
  if (*(float *)0x002533c0 < dot) {
    disc = (dx * dx + dy * dy) - radius * radius;
    if (disc <= *(float *)0x002533c0) {
      out[0] = 0.0f;
      return 1;
    }
    disc = dot * dot - disc;
    if (*(float *)0x002533c0 <= disc) {
      out[0] = dot - sqrtf(disc);
      return 1;
    }
  }
  return 0;
}

/* 0x61fa0 - build the two boundary rays of a 2D cone around a direction.
 *
 * Given the 2D direction vec and a cone whose sine is num/denom (clamped to the
 * 1.0f constant at 0x2533c8), computes cos = sqrt(1 - sin^2) and rotates vec by
 * +/- the cone half-angle:
 *   out_a = { cos*vx - sin*vy, cos*vy + sin*vx }   (rotate by -angle)
 *   out_b = { cos*vx + sin*vy, cos*vy - sin*vx }   (rotate by +angle)
 * and writes out_scalar = cos*denom.  All FPU; no calls but sqrtf (FSQRT).
 *
 * Register ABI (prologue at 0x61fa0): no entry moves; ECX read as vec
 * (FMUL [ECX],[ECX+4]), EDX as out_a (FSTP [EDX],[EDX+4]), ESI as out_b
 * (FSTP [ESI],[ESI+4]).  Stack args: denom=[EBP+8], num=[EBP+0xc],
 * out_scalar=[EBP+0x10] (float*).  EAX is loaded from [EBP+0x10] (not an arg).
 * void return. */
void FUN_00061fa0(float *vec, float *out_a, float *out_b, float denom, float num,
                  float *out_scalar)
{
  float s;
  float c;
  float vx;
  float vy;

  s = num / denom;
  if (*(float *)0x002533c8 < s) {
    s = *(float *)0x002533c8;
  }
  c = sqrtf(*(float *)0x002533c8 - s * s);
  vx = vec[0];
  vy = vec[1];
  out_b[0] = c * vec[0] + s * vec[1];
  out_b[1] = c * vy - s * vx;
  vx = vec[0];
  vy = vec[1];
  out_a[0] = c * vec[0] - s * vec[1];
  out_a[1] = c * vy + s * vx;
  out_scalar[0] = c * denom;
}

/* FUN_00062020 (0x62020)  --  add_obstacle (path_obstacles.c)
 *
 * Append one obstacle record to an obstacle-set.  The set header is a small
 * int16 struct: [+0x00] obstacle_count, [+0x02] disc_count (element count,
 * MAXIMUM_DISC_COUNT == 0x80), [+0x04] a secondary count bumped only when the
 * flags low bit is set.  Records begin at +0x08 with a 24-byte (0xc short)
 * stride; record N lives at (char *)set + N*24 + 8.
 *
 * Two bounds asserts (path_obstacles.c lines 0x68/0x69) then a capacity guard
 * that returns false when the set is full.  On success the new record is
 * filled and true is returned.
 *
 * Field-copy widths are taken from the disassembly (0x62020): rec+0x0c is an
 * x87 float copy (FLD/FSTP) of vector[j]; rec+0x08 and rec+0x14 are raw 32-bit
 * dword copies (integer MOV) of vector[i] and vector[2].  DAT_0028cb24 /
 * DAT_0028cb26 are int16 axis-index selectors (read via MOVSX), i.e. the two
 * projected components of the vector.  cdecl, five stack args, bool in AL.
 */
bool FUN_00062020(int16_t *obstacle_set, uint32_t datum, uint16_t flags,
                  float *vector, uint32_t param_5)
{
  int16_t disc_count;
  int16_t i;
  int16_t j;
  char *rec;

  /* obstacles->disc_count>=0 && obstacles->disc_count<=MAXIMUM_DISC_COUNT */
  if (obstacle_set[1] < 0 || obstacle_set[1] > 0x80) {
    display_assert(
      "obstacles->disc_count>=0 && obstacles->disc_count<=MAXIMUM_DISC_COUNT",
      "c:\\halo\\SOURCE\\ai\\path_obstacles.c", 0x68, 1);
    system_exit(-1);
  }
  /* obstacles->obstacle_count>=0 &&
   * obstacles->obstacle_count<=obstacles->disc_count */
  if (obstacle_set[0] < 0 || obstacle_set[0] > obstacle_set[1]) {
    display_assert("obstacles->obstacle_count>=0 && "
                   "obstacles->obstacle_count<=obstacles->disc_count",
                   "c:\\halo\\SOURCE\\ai\\path_obstacles.c", 0x69, 1);
    system_exit(-1);
  }

  disc_count = obstacle_set[1];
  if (disc_count == 0x80)
    return false; /* set is full */

  obstacle_set[1] = disc_count + 1;
  rec = (char *)obstacle_set + disc_count * 24 + 8;
  if ((flags & 1) != 0)
    obstacle_set[2] = obstacle_set[2] + 1;

  *(uint16_t *)(rec + 0x00) = flags;
  *(uint32_t *)(rec + 0x04) = datum;
  *(uint16_t *)(rec + 0x02) = 0xffff;

  i = *(int16_t *)0x28cb24;
  j = *(int16_t *)0x28cb26;
  *(uint32_t *)(rec + 0x08) = *(uint32_t *)&vector[i];
  *(float *)(rec + 0x0c) = vector[j];
  *(uint32_t *)(rec + 0x10) = param_5;
  *(uint32_t *)(rec + 0x14) = *(uint32_t *)&vector[2];

  return true;
}

/* path_obstacles.c — AI path obstacle-disc connectivity.
 *
 * Corresponds to a routine in structures.obj (its sole ported caller,
 * cluster_partition_assign_groups / FUN_000628b0 at 0x628b0, lives in
 * src/halo/structures/structures.c).  __FILE__ evidence for this function is
 * c:\halo\SOURCE\ai\path_obstacles.c (from its display_assert strings at
 * lines 0x183, 0x18c, 0x1a5); two interior asserts cite
 * c:\halo\source\ai\path.h (0x18c) verbatim.
 *
 * Ported: FUN_00062680 (0x62680) — flood-fill of the "obstacle disc" set.
 */

#include "../../common.h"
#include "../../x87_math.h"

/* FUN_00062410 (0x62410) — readable C lift (restored pre-naked). */
short FUN_00062410(void *obstacles, short disc_index_skip, float *position_xy,
                   float radius)
{
  char *base;
  short i;
  short disc_count;
  char *disc;
  float sum_radius;
  float dx;
  float dy;

  base = (char *)obstacles;
  disc_count = *(short *)(base + 2);
  i = 0;
  if (disc_count > 0) {
    do {
      if (i != disc_index_skip) {
        if (i < 0 || disc_count <= i || disc_count > 0x80) {
          display_assert("disc_index>=0 && disc_index<obstacles->disc_count && "
                         "obstacles->disc_count<=MAXIMUM_DISC_COUNT",
                         "c:\\halo\\source\\ai\\path.h", 0x18c, 1);
          system_exit(-1);
        }
        disc = base + 8 + i * 0x18;
        sum_radius = *(float *)(disc + 0x10) + radius;
        dx = *(float *)(disc + 8) - position_xy[0];
        dy = *(float *)(disc + 0xc) - position_xy[1];
        if (!(sum_radius * sum_radius < dy * dy + dx * dx)) {
          return i;
        }
      }
      disc_count = *(short *)(base + 2);
      i = i + 1;
    } while (i < disc_count);
  }
  return -1;
}


/* FUN_00062680 (0x62680) — XBE naked draft (batch 82). */
#if defined(__clang__)
static void (*const b62680_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b62680_exitfn)(int) = system_exit;
static void *(*const b62680_memset)(void *, int, unsigned int) = csmemset;

__attribute__((naked, noinline))
void FUN_00062680(int16_t *partition __attribute__((unused)), uint32_t arg2 __attribute__((unused)), int16_t index __attribute__((unused)), uint32_t *out_mask __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x108, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movw 0x2(%%edi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00062680_1\n\t"
      "cmpw $0x80, %%ax\n\t"
      "jle .LFUN_00062680_2\n\t"
      ".LFUN_00062680_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x183\n\t"
      "pushl $0x25ee38\n\t"
      "pushl $0x25edf0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00062680_2:\n\t"
      "movswl 0x2(%%edi), %%eax\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "addl $0x1f, %%eax\n\t"
      "sarl $5, %%eax\n\t"
      "shll $2, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[memset]\n\t"
      "movw 0x10(%%ebp), %%si\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $-1, %%si\n\t"
      "je .LFUN_00062680_14\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_00062680_3\n\t"
      "cmpw 0x2(%%edi), %%si\n\t"
      "jl .LFUN_00062680_4\n\t"
      ".LFUN_00062680_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x18c\n\t"
      "pushl $0x25ee38\n\t"
      "pushl $0x25ee70\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00062680_4:\n\t"
      "movswl %%si, %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "sarl $5, %%edx\n\t"
      "leal (%%ebx,%%edx,4), %%eax\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movw %%si, -0x108(%%ebp)\n\t"
      "movl $1, %%ebx\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00062680_5:\n\t"
      "decl %%ebx\n\t"
      "movswl %%bx, %%eax\n\t"
      "movw -0x108(%%ebp,%%eax,2), %%si\n\t"
      "testw %%si, %%si\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "jl .LFUN_00062680_6\n\t"
      "movw 0x2(%%edi), %%ax\n\t"
      "cmpw %%ax, %%si\n\t"
      "jge .LFUN_00062680_6\n\t"
      "cmpw $0x80, %%ax\n\t"
      "jle .LFUN_00062680_7\n\t"
      ".LFUN_00062680_6:\n\t"
      "pushl $1\n\t"
      "pushl $0x18c\n\t"
      "pushl $0x25e990\n\t"
      "pushl $0x25e930\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00062680_7:\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "movw 0x2(%%edi), %%ax\n\t"
      "leal 0x8(%%edi,%%ecx,8), %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "xorl %%edx, %%edx\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "jle .LFUN_00062680_13\n\t"
      ".LFUN_00062680_8:\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "movswl %%dx, %%esi\n\t"
      "movl %%esi, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edi\n\t"
      "shll %%cl, %%edi\n\t"
      "movl %%esi, %%ecx\n\t"
      "sarl $5, %%ecx\n\t"
      "leal (%%ebx,%%ecx,4), %%ebx\n\t"
      "testl %%edi, (%%ebx)\n\t"
      "jne .LFUN_00062680_12\n\t"
      "testw %%dx, %%dx\n\t"
      "jl .LFUN_00062680_9\n\t"
      "cmpw %%ax, %%dx\n\t"
      "jge .LFUN_00062680_9\n\t"
      "cmpw $0x80, %%ax\n\t"
      "jle .LFUN_00062680_10\n\t"
      ".LFUN_00062680_9:\n\t"
      "pushl $1\n\t"
      "pushl $0x18c\n\t"
      "pushl $0x25e990\n\t"
      "pushl $0x25e930\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00062680_10:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "flds 0xc(%%ebp)\n\t"
      "leal (%%esi,%%esi,2), %%eax\n\t"
      "fadds 0x18(%%ecx,%%eax,8)\n\t"
      "leal 0x8(%%ecx,%%eax,8), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fadds 0x10(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs 0x8(%%ecx)\n\t"
      "flds 0xc(%%eax)\n\t"
      "fsubs 0xc(%%ecx)\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      "fcompp\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $1, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jne .LFUN_00062680_12\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "orl %%edi, %%ecx\n\t"
      "cmpw $0x80, %%si\n\t"
      "movl %%ecx, (%%ebx)\n\t"
      "jl .LFUN_00062680_11\n\t"
      "pushl $1\n\t"
      "pushl $0x1a5\n\t"
      "pushl $0x25ee38\n\t"
      "pushl $0x25ebb0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00062680_11:\n\t"
      "movswl %%si, %%eax\n\t"
      "incl %%esi\n\t"
      "movw %%dx, -0x108(%%ebp,%%eax,2)\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      ".LFUN_00062680_12:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movw 0x2(%%ecx), %%ax\n\t"
      "incl %%edx\n\t"
      "cmpw %%ax, %%dx\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "jl .LFUN_00062680_8\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "movl %%ecx, %%edi\n\t"
      ".LFUN_00062680_13:\n\t"
      "testw %%bx, %%bx\n\t"
      "jg .LFUN_00062680_5\n\t"
      ".LFUN_00062680_14:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b62680_assert), [exitfn] "m"(b62680_exitfn), [memset] "m"(b62680_memset)
      : "memory");
}
#else
#error "FUN_00062680: clang naked draft required"
#endif


/* FUN_000624b0 (0x624b0) — readable C lift (restored pre-naked). */
char FUN_000624b0(void *obstacles, short skip_index, float *pt0, float *vec_a,
                  float radius_base, float max_distance, char check_extant,
                  void *result)
{
  short i;
  short disc_count;
  float *disc;

  *(float *)result = max_distance;
  *(short *)((char *)result + 4) = -1;
  *(short *)((char *)result + 6) = -1;
  disc_count = *(short *)((char *)obstacles + 2);
  i = 0;
  if (disc_count > 0) {
    do {
      if (i != skip_index) {
        if (i < 0 || i >= disc_count || disc_count > 0x80) {
          display_assert(
              "disc_index>=0 && disc_index<obstacles->disc_count && "
              "obstacles->disc_count<=MAXIMUM_DISC_COUNT",
              "c:\\halo\\source\\ai\\path.h", 0x18c, true);
          system_exit(-1);
        }
        disc = (float *)((char *)obstacles + (int)i * 0x18 + 8);
        if (check_extant == 0 || (*(char *)disc & 1) == 0) {
          if (FUN_00061f10(vec_a, pt0, (float *)((char *)disc + 8),
                           &max_distance, radius_base + disc[4]) != 0) {
            if (*(float *)result > max_distance) {
              *(float *)result = max_distance;
              *(short *)((char *)result + 4) = i;
              *(short *)((char *)result + 6) = *(short *)((char *)disc + 2);
            }
          }
        }
      }
      disc_count = *(short *)((char *)obstacles + 2);
      i = (short)(i + 1);
    } while (i < disc_count);
  }
  return (char)(*(short *)((char *)result + 4) != -1);
}



/* FUN_000625a0 (0x625a0) — XBE naked draft (batch 87). */
#if defined(__clang__)
static void (*const b625a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b625a0_exitfn)(int) = system_exit;
static void (*const b625a0_c61fa0)(float *vec, float *out_a, float *out_b, float denom, float num, float *out_scalar) = FUN_00061fa0;

__attribute__((naked, noinline))
void FUN_000625a0(void *obstacles __attribute__((unused)), short disc_index __attribute__((unused)), float *point __attribute__((unused)), float base_value __attribute__((unused)), float *out_b __attribute__((unused)), float *out_a __attribute__((unused)), float *out_scalar __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%esi\n\t"
      "movw 0xc(%%ebp), %%si\n\t"
      "testw %%si, %%si\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "jl .LFUN_000625a0_1\n\t"
      "movw 0x2(%%edi), %%ax\n\t"
      "cmpw %%ax, %%si\n\t"
      "jge .LFUN_000625a0_1\n\t"
      "cmpw $0x80, %%ax\n\t"
      "jle .LFUN_000625a0_2\n\t"
      ".LFUN_000625a0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x18c\n\t"
      "pushl $0x25e990\n\t"
      "pushl $0x25e930\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000625a0_2:\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal 0x8(%%edi,%%eax,8), %%ecx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fsubs (%%eax)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0xc(%%ecx)\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fsts 0xc(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_000625a0_3\n\t"
      "flds 0x2533c8\n\t"
      "fdivs 0xc(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "jmp .LFUN_000625a0_4\n\t"
      ".LFUN_000625a0_3:\n\t"
      "movl $0, 0xc(%%ebp)\n\t"
      ".LFUN_000625a0_4:\n\t"
      "flds 0x14(%%ebp)\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "fadds 0x10(%%ecx)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "pushl %%edx\n\t"
      "fadds 0x25ee6c\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "call *%[c61fa0]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b625a0_assert), [exitfn] "m"(b625a0_exitfn), [c61fa0] "m"(b625a0_c61fa0)
      : "memory");
}
#else
#error "FUN_000625a0: clang naked draft required"
#endif


/* FUN_000628b0 (0x628b0) — XBE naked draft (batch 88). */
#if defined(__clang__)
static void (*const b628b0_c62680)(int16_t *partition, uint32_t arg2, int16_t index, uint32_t *out_mask) = FUN_00062680;

__attribute__((naked, noinline))
void FUN_000628b0(int16_t *partition __attribute__((unused)), uint32_t arg2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw %%ax, 0x2(%%esi)\n\t"
      "movw $0, (%%esi)\n\t"
      "jle .LFUN_000628b0_2\n\t"
      ".LFUN_000628b0_1:\n\t"
      "movswl %%ax, %%ecx\n\t"
      "leal (%%ecx,%%ecx,2), %%ecx\n\t"
      "incl %%eax\n\t"
      "movw $0xffff, 0xa(%%esi,%%ecx,8)\n\t"
      "cmpw 0x2(%%esi), %%ax\n\t"
      "jl .LFUN_000628b0_1\n\t"
      ".LFUN_000628b0_2:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpw %%bx, 0x2(%%esi)\n\t"
      "movl %%ebx, 0x8(%%ebp)\n\t"
      "jle .LFUN_000628b0_7\n\t"
      "pushl %%edi\n\t"
      "jmp .LFUN_000628b0_3\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_000628b0_3:\n\t"
      "movswl %%bx, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "cmpw $-1, 0xa(%%esi,%%edx,8)\n\t"
      "jne .LFUN_000628b0_6\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "xorl %%edi, %%edi\n\t"
      "movw (%%esi), %%di\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "leal 0x1(%%edi), %%eax\n\t"
      "movw %%ax, (%%esi)\n\t"
      "call *%[c62680]\n\t"
      "xorl %%edx, %%edx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw %%dx, 0x2(%%esi)\n\t"
      "jle .LFUN_000628b0_6\n\t"
      ".LFUN_000628b0_4:\n\t"
      "movswl %%dx, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%ebx\n\t"
      "shll %%cl, %%ebx\n\t"
      "movl %%eax, %%ecx\n\t"
      "sarl $5, %%ecx\n\t"
      "testl %%ebx, -0x10(%%ebp,%%ecx,4)\n\t"
      "je .LFUN_000628b0_5\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "movw %%di, 0xa(%%esi,%%eax,8)\n\t"
      ".LFUN_000628b0_5:\n\t"
      "incl %%edx\n\t"
      "cmpw 0x2(%%esi), %%dx\n\t"
      "jl .LFUN_000628b0_4\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      ".LFUN_000628b0_6:\n\t"
      "incl %%ebx\n\t"
      "cmpw 0x2(%%esi), %%bx\n\t"
      "movl %%ebx, 0x8(%%ebp)\n\t"
      "jl .LFUN_000628b0_3\n\t"
      "popl %%edi\n\t"
      ".LFUN_000628b0_7:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c62680] "m"(b628b0_c62680)
      : "memory");
}
#else
#error "FUN_000628b0: clang naked draft required"
#endif


/* FUN_00099070 (0x99070)
 *
 * Debug overlay for the decal render queue and per-cluster decal labels.
 * Runs only when the global debug flag at 0x5aa8b4 is set.
 *
 * Part 1 (decal queue): for each queue in [0, *0x4547da), walk its
 * *0x453fda[queue] elements.  Elements are 0x18-byte records in three
 * parallel arrays: point_a base 0x44dfc0, point_b base 0x44dfd8, and a
 * flag byte base 0x44dfec, all indexed by (element + base)*0x18.  For each
 * element FUN_00189270 draws the edge (running point) -> point_b in the
 * global color at 0x2ee6e0, then FUN_00189150 draws point_b as a 0.0625f
 * point using color 0x2ee6d0 (flag set) or 0x2ee6c4 (flag clear).  After
 * each queue a duplicate-surface-index scan over 0x4547dc reports an error.
 *
 * Part 2 (cluster labels): for each rendered cluster in [0, *0x5137cc), and
 * each of its 5 layers, walk the decal linked list (next handle at
 * record+0x34, -1 terminates) resolved through the decals pool *0x5aa8b8;
 * label each decal with its surface index (record+0x2a, sign-extended and
 * <<2) drawn at record+8.
 *
 * Confirmed from decompile at 0x99070:
 *   - loop bound *0x4547da is re-read after every error() and each inner draw.
 *   - FUN_00189150 scale arg is float 0.0625f (0x3d800000), passed by value.
 *   - sprintf vararg is (int)(short)*(record+0x2a) << 2.
 *   - the linked-list "next" is read from the resolved record pointer +0x34.
 * ABI: cdecl, no args, void return.
 */
void FUN_00099070(void)
{
  char local_50[64];
  int base_element;
  int queue_index;
  short queue_count_g;
  short count;
  short e;
  short dup;
  int byte_off;
  float *point_a;
  float *point_b;
  void *color;
  int ri;
  void *cluster;
  short cluster_id;
  short layer;
  int node;
  char *rec;

  if (*(char *)0x5aa8b4 == 0)
    return;

  base_element = 0;
  queue_index = 0;
  queue_count_g = *(short *)0x4547da;
  if (queue_count_g > 0) {
    do {
      count = ((short *)0x453fda)[(short)queue_index];
      e = 0;
      point_a = (float *)(0x44dfc0 + (count + (short)base_element) * 0x18);
      if (count > 0) {
        do {
          byte_off = (e + (short)base_element) * 0x18;
          point_b = (float *)(0x44dfd8 + byte_off);
          FUN_00189270(1, point_a, point_b, *(void **)0x2ee6e0);
          color = *(void **)0x2ee6d0;
          /* flag byte lives at 0x44dfec + byte_off (== point_b + 0x14); both
           * are byte reads, so the [LOADW-WARN] is a benign addressing-encoding
           * diff. */
          if (*(char *)(0x44dfec + byte_off) == 0)
            color = *(void **)0x2ee6c4;
          FUN_00189150(1, point_b, 0.0625f, color);
          e = e + 1;
          point_a = point_b;
          queue_count_g = *(short *)0x4547da;
        } while (e < ((short *)0x453fda)[(short)queue_index]);
      }
      dup = 0;
      if (queue_count_g > 0) {
        do {
          if (dup != (short)queue_index &&
              ((short *)0x4547dc)[(short)queue_index] ==
                ((short *)0x4547dc)[dup]) {
            error(2, "### ERROR decals: duplicate surface indices in queue -- "
                     "tell Bernie!!");
            queue_count_g = *(short *)0x4547da;
          }
          dup = dup + 1;
        } while (dup < queue_count_g);
      }
      base_element = base_element + count;
      queue_index = queue_index + 1;
    } while ((short)queue_index < queue_count_g);
  }

  ri = 0;
  if (*(short *)0x5137cc > 0) {
    do {
      cluster = rendered_cluster_get(ri);
      cluster_id = *(short *)cluster;
      layer = 0;
      do {
        node = FUN_00098fe0(cluster_id, layer);
        while (node != -1) {
          rec = (char *)datum_get(*(void **)0x5aa8b8, node);
          crt_sprintf(local_50, "%d", (int)*(short *)(rec + 0x2a) << 2);
          FUN_00189cb0(0, rec + 8, local_50, *(int *)0x2ee6d0);
          node = *(int *)(rec + 0x34);
        }
        layer = layer + 1;
      } while ((short)layer < 5);
      ri = ri + 1;
    } while ((short)ri < *(short *)0x5137cc);
  }
}

/* FUN_00099220 (0x99220)
 *
 * Determine the dominant axis of a plane normal.  Returns the index
 * (0=x, 1=y, 2=z) of the component with the largest absolute value.
 */
uint32_t FUN_00099220(float *plane)
{
  float ax = plane[0] < 0.0f ? -plane[0] : plane[0];
  float ay = plane[1] < 0.0f ? -plane[1] : plane[1];
  float az = plane[2] < 0.0f ? -plane[2] : plane[2];

  if (ay <= az && ax <= az)
    return 2;
  if (ay < ax)
    return 0;
  return 1;
}

/* FUN_00099270 (0x99270)
 *
 * Return 1 if the plane normal component at the given projection axis
 * is positive, 0 otherwise.
 */
uint8_t FUN_00099270(float *plane, uint32_t basis)
{
  assert_halt((int16_t)basis >= 0 && (int16_t)basis <= 2);
  if (plane[basis] > 0.0f)
    return 1;
  return 0;
}

/* FUN_00104bd0 (0x104bd0)  error_geometry.c:0x237-0x239
 *
 * Debug two-point (line segment) axis-aligned bounding box.  Expands the
 * per-axis min/max of p0 and p1 outward by 'radius', packs the 6-float box and
 * the 4-float color (red channel scaled by 0.5) into a contiguous scratch
 * buffer, hands them to FUN_001049d0, then renders the segment via
 * FUN_00103e80.  Gated on the debug-geometry-enabled predicate FUN_00103d30.
 *
 * cdecl, verified from disassembly at 0x104bd0:
 *   [EBP+0x8]=p0 (ESI), [EBP+0xc]=p1 (EDI), [EBP+0x10]=radius (float),
 *   [EBP+0x14]=color (EBX).  Both min and max select on (p0<=p1).  Color scale
 *   const 0x253398 = 0.5f.  0x1029a0 thunk in the decompiler is actually
 *   system_exit(-1) (CALL 0x8e2f0).  Box buffer EBP-0x28..-0x14, color
 * -0x10..-0x4.
 */
void FUN_00104bd0(float *p0, float *p1, float radius, float *color)
{
  float box[6];
  float col[4];

  if (p0 == 0) {
    display_assert("p0", "c:\\halo\\SOURCE\\tool\\error_geometry.c", 0x237,
                   true);
    system_exit(-1);
  }
  if (p1 == 0) {
    display_assert("p1", "c:\\halo\\SOURCE\\tool\\error_geometry.c", 0x238,
                   true);
    system_exit(-1);
  }
  if (color == 0) {
    display_assert("color", "c:\\halo\\SOURCE\\tool\\error_geometry.c", 0x239,
                   true);
    system_exit(-1);
  }
  if (FUN_00103d30()) {
    if (p0[0] <= p1[0])
      box[0] = p0[0];
    else
      box[0] = p1[0];
    box[0] = box[0] - radius;
    if (p0[0] <= p1[0])
      box[1] = p1[0];
    else
      box[1] = p0[0];
    box[1] = box[1] + radius;
    if (p0[1] <= p1[1])
      box[2] = p0[1];
    else
      box[2] = p1[1];
    box[2] = box[2] - radius;
    if (p0[1] <= p1[1])
      box[3] = p1[1];
    else
      box[3] = p0[1];
    box[3] = box[3] + radius;
    if (p0[2] <= p1[2])
      box[4] = p0[2];
    else
      box[4] = p1[2];
    box[4] = box[4] - radius;
    if (p0[2] <= p1[2])
      box[5] = p1[2];
    else
      box[5] = p0[2];
    box[5] = box[5] + radius;
    col[1] = color[1];
    col[2] = color[2];
    col[3] = color[3];
    col[0] = color[0] * 0.5f;
    FUN_001049d0(box, col);
    FUN_00103e80(p0, p1, color);
  }
}

/* FUN_00104d40 (0x104d40)  error_geometry.c:0x255-0x258
 *
 * Debug three-point (triangle) axis-aligned bounding box.  Computes the 3-way
 * per-axis min/max of p0,p1,p2 (min(p1,p2) resolved first, then folded against
 * p0), expands by 'radius', and emits box+color (red*0.5) via FUN_001049d0
 * then FUN_00104040.  cdecl, verified at 0x104d40: [EBP+0x8]=p0 (EBX),
 * [EBP+0xc]=p1 (EDI), [EBP+0x10]=p2 (ESI), [EBP+0x14]=radius, [EBP+0x18]=color.
 * All comparisons select on '<=' (FCOMP TEST AH,0x41 / TEST AH,0x5 JP idiom).
 */
void FUN_00104d40(float *p0, float *p1, float *p2, float radius, float *color)
{
  float box[6];
  float col[4];
  float m;

  if (p0 == 0) {
    display_assert("p0", "c:\\halo\\SOURCE\\tool\\error_geometry.c", 0x255,
                   true);
    system_exit(-1);
  }
  if (p1 == 0) {
    display_assert("p1", "c:\\halo\\SOURCE\\tool\\error_geometry.c", 0x256,
                   true);
    system_exit(-1);
  }
  if (p2 == 0) {
    display_assert("p2", "c:\\halo\\SOURCE\\tool\\error_geometry.c", 0x257,
                   true);
    system_exit(-1);
  }
  if (color == 0) {
    display_assert("color", "c:\\halo\\SOURCE\\tool\\error_geometry.c", 0x258,
                   true);
    system_exit(-1);
  }
  if (FUN_00103d30()) {
    /* X */
    if (p1[0] <= p2[0])
      m = p1[0];
    else
      m = p2[0];
    if (p0[0] <= m)
      box[0] = p0[0];
    else if (p1[0] <= p2[0])
      box[0] = p1[0];
    else
      box[0] = p2[0];
    box[0] = box[0] - radius;
    if (p1[0] <= p2[0])
      m = p2[0];
    else
      m = p1[0];
    if (p0[0] <= m) {
      if (p1[0] <= p2[0])
        box[1] = p2[0];
      else
        box[1] = p1[0];
    } else
      box[1] = p0[0];
    box[1] = box[1] + radius;
    /* Y */
    if (p1[1] <= p2[1])
      m = p1[1];
    else
      m = p2[1];
    if (p0[1] <= m)
      box[2] = p0[1];
    else if (p1[1] <= p2[1])
      box[2] = p1[1];
    else
      box[2] = p2[1];
    box[2] = box[2] - radius;
    if (p1[1] <= p2[1])
      m = p2[1];
    else
      m = p1[1];
    if (p0[1] <= m) {
      if (p1[1] <= p2[1])
        box[3] = p2[1];
      else
        box[3] = p1[1];
    } else
      box[3] = p0[1];
    box[3] = box[3] + radius;
    /* Z */
    if (p1[2] <= p2[2])
      m = p1[2];
    else
      m = p2[2];
    if (p0[2] <= m)
      box[4] = p0[2];
    else if (p1[2] <= p2[2])
      box[4] = p1[2];
    else
      box[4] = p2[2];
    box[4] = box[4] - radius;
    if (p1[2] <= p2[2])
      m = p2[2];
    else
      m = p1[2];
    if (p0[2] <= m) {
      if (p1[2] <= p2[2])
        box[5] = p2[2];
      else
        box[5] = p1[2];
    } else
      box[5] = p0[2];
    box[5] = box[5] + radius;
    col[1] = color[1];
    col[2] = color[2];
    col[0] = color[0] * 0.5f;
    col[3] = color[3];
    FUN_001049d0(box, col);
    FUN_00104040(p0, p1, p2, color);
  }
}

/* FUN_00104fa0 (0x104fa0)  error_geometry.c:0x273-0x275
 *
 * Debug point-cloud axis-aligned bounding box.  Iterates 'point_count' packed
 * 3-float points, accumulates per-axis min/max (min uses '<', max uses '<=',
 * matching the FCOMP polarity), expands by 'radius', and emits the box+color
 * via FUN_001049d0 then FUN_00104240.  Requires count>=3.  The z-max
 * accumulator is register-resident (ST0) in the original; modelling it as a
 * local produces the documented ~84% VC71 structural cap (accepted via
 * equivalence).  cdecl, verified at 0x104fa0: [EBP+0x8]=count (low 16 bits,
 * signed; loop count zero-extended), [EBP+0xc]=points (stride 12B),
 * [EBP+0x10]=radius, [EBP+0x14]=color.  FLT_MAX=0x7f7fffff, -FLT_MAX (z init
 * const 0x255c98)=0xff7fffff.
 */
void FUN_00104fa0(int point_count, float *points, float radius, float *color)
{
  float box[6];
  float col[4];
  float *p;
  short count;
  unsigned int i;

  count = (short)point_count;
  if (count < 0) {
    display_assert("point_count>=0", "c:\\halo\\SOURCE\\tool\\error_geometry.c",
                   0x273, true);
    system_exit(-1);
  }
  if (points == 0) {
    display_assert("points", "c:\\halo\\SOURCE\\tool\\error_geometry.c", 0x274,
                   true);
    system_exit(-1);
  }
  if (color == 0) {
    display_assert("color", "c:\\halo\\SOURCE\\tool\\error_geometry.c", 0x275,
                   true);
    system_exit(-1);
  }
  if (count > 2) {
    if (FUN_00103d30()) {
      box[0] = 3.4028235e+38f;
      box[1] = -3.4028235e+38f;
      box[2] = 3.4028235e+38f;
      box[3] = -3.4028235e+38f;
      box[4] = 3.4028235e+38f;
      box[5] = -3.4028235e+38f;
      if (count > 0) {
        p = points + 2;
        i = (unsigned int)point_count & 0xffff;
        do {
          if (p[-2] < box[0])
            box[0] = p[-2];
          if (box[1] <= p[-2])
            box[1] = p[-2];
          if (p[-1] < box[2])
            box[2] = p[-1];
          if (box[3] <= p[-1])
            box[3] = p[-1];
          if (p[0] < box[4])
            box[4] = p[0];
          if (box[5] <= p[0])
            box[5] = p[0];
          p = p + 3;
          i = i - 1;
        } while (i != 0);
      }
      box[0] = box[0] - radius;
      col[1] = color[1];
      col[2] = color[2];
      col[3] = color[3];
      box[1] = box[1] + radius;
      box[2] = box[2] - radius;
      box[3] = box[3] + radius;
      box[4] = box[4] - radius;
      box[5] = box[5] + radius;
      col[0] = color[0] * 0.5f;
      FUN_001049d0(box, col);
      FUN_00104240(point_count, points, color);
    }
  }
}

/* 0x105550 — error_geometry.c: draw a small fixed-size debug marker box at a
 * point (half-extent _DAT_0025bb10 = 0.01f on each axis).  cdecl, 2 stack args.
 * Asserts at source lines 0x77-0x78. */
void FUN_00105550(float *point, float *color)
{
  float bounds[6];

  if (point == 0) {
    display_assert("point", "c:\\halo\\SOURCE\\tool\\error_geometry.c", 0x77,
                   1);
    system_exit(-1);
  }
  if (color == 0) {
    display_assert("color", "c:\\halo\\SOURCE\\tool\\error_geometry.c", 0x78,
                   1);
    system_exit(-1);
  }
  if (FUN_00103d30()) {
    bounds[0] = *point - 0.01f;
    bounds[1] = *point + 0.01f;
    bounds[2] = point[1] - 0.01f;
    bounds[3] = point[1] + 0.01f;
    bounds[4] = point[2] - 0.01f;
    bounds[5] = point[2] + 0.01f;
    FUN_001049d0(bounds, color);
  }
}

/* FUN_00105610 (0x105610)  error_geometry.c:0x21b-0x21c
 *
 * Debug single-point cube: builds an AABB centered on 'point' with half-extent
 * 'radius' on every axis, packs box+color (red*0.5), and emits via
 * FUN_001049d0 then FUN_00105550.  cdecl, verified at 0x105610:
 *   [EBP+0x8]=point (ESI), [EBP+0xc]=radius (float), [EBP+0x10]=color (EDI).
 *   Max axes computed as (radius + point[i]) matching the FLD radix/FADD order.
 */
void FUN_00105610(float *point, float radius, float *color)
{
  float box[6];
  float col[4];

  if (point == 0) {
    display_assert("point", "c:\\halo\\SOURCE\\tool\\error_geometry.c", 0x21b,
                   true);
    system_exit(-1);
  }
  if (color == 0) {
    display_assert("color", "c:\\halo\\SOURCE\\tool\\error_geometry.c", 0x21c,
                   true);
    system_exit(-1);
  }
  if (FUN_00103d30()) {
    box[0] = point[0] - radius;
    col[1] = color[1];
    col[2] = color[2];
    col[3] = color[3];
    box[1] = radius + point[0];
    box[2] = point[1] - radius;
    box[3] = radius + point[1];
    box[4] = point[2] - radius;
    box[5] = radius + point[2];
    col[0] = color[0] * 0.5f;
    FUN_001049d0(box, col);
    FUN_00105550(point, color);
  }
}

/* 0x1056e0 — Dispose of a sphere geometry object.
 * Asserts the sphere handle and its two allocated arrays (vertices at +0x4,
 * triangle_strip_vertex_indices at +0x8) are non-NULL, then frees the two
 * arrays followed by the sphere structure itself.
 * Source: c:\halo\SOURCE\math\geometry.c (lines 0x75-0x7b). */
void FUN_001056e0(void *handle)
{
  if (handle == 0) {
    display_assert("sphere", "c:\\halo\\SOURCE\\math\\geometry.c", 0x75, 1);
    system_exit(-1);
  }
  if (*(int *)((char *)handle + 4) == 0) {
    display_assert("sphere->vertices", "c:\\halo\\SOURCE\\math\\geometry.c",
                   0x76, 1);
    system_exit(-1);
  }
  if (*(int *)((char *)handle + 8) == 0) {
    display_assert("sphere->triangle_strip_vertex_indices",
                   "c:\\halo\\SOURCE\\math\\geometry.c", 0x77, 1);
    system_exit(-1);
  }
  debug_free(*(void **)((char *)handle + 4),
             "c:\\halo\\SOURCE\\math\\geometry.c", 0x79);
  debug_free(*(void **)((char *)handle + 8),
             "c:\\halo\\SOURCE\\math\\geometry.c", 0x7a);
  debug_free(handle, "c:\\halo\\SOURCE\\math\\geometry.c", 0x7b);
}

/* FUN_001057a0 (0x1057a0)
 *
 * Signed-distance evaluation of a 2D point against a plane2d
 * (normal.x, normal.y, distance).  Computes the 2D dot product of the
 * first two components of param_1 and param_2, then subtracts the third
 * component of param_1: (p1[0]*p2[0] + p1[1]*p2[1]) - p1[2].
 * Pure x87 leaf; operand order preserved to match FADD/FSUBP ordering.
 */
float FUN_001057a0(float *param_1, float *param_2)
{
  return (param_1[0] * param_2[0] + param_1[1] * param_2[1]) - param_1[2];
}

/* FUN_001057c0 (0x1057c0)
 *
 * 2D parametric line-intersection solve.  Given plane2d param_1 and param_2
 * (each normal.x, normal.y with param_1 carrying a distance at +0x8) and a
 * shared point/direction param_3 (x at +0x0, y at +0x4, offset at +0x8),
 * returns the negated ratio of two signed 2D evaluations:
 *   num = param_1[0]*param_3[0] + param_1[1]*param_3[1] - param_3[2]
 *   den = param_2[0]*param_3[0] + param_2[1]*param_3[1]
 *   return -(num / den)
 * Pure x87 leaf; single-expression form keeps intermediates in ST(0) to
 * match the FLD/FMUL/FADDP/FSUB/FDIVP/FCHS chain (FSUB not FSUBR: the
 * subtrahend is param_3[2]; FDIVP yields num/den; FCHS negates).
 * EAX holds param_3 throughout; ECX switches from param_1 to param_2.
 */
float FUN_001057c0(float *param_1, float *param_2, float *param_3)
{
  return -(((param_1[0] * param_3[0] + param_1[1] * param_3[1]) - param_3[2]) /
           (param_2[0] * param_3[0] + param_2[1] * param_3[1]));
}

/* FUN_001057f0 (0x1057f0)
 *
 * 3D ray/plane parametric-t solve (3D twin of FUN_001057c0).  param_3 is a
 * plane3d (normal.x/y/z at +0x0/+0x4/+0x8, distance at +0xc); param_1 and
 * param_2 are 3D vectors:
 *   num = param_1[0]*param_3[0] + param_1[1]*param_3[1] + param_1[2]*param_3[2]
 * - param_3[3] den = param_2[0]*param_3[0] + param_2[1]*param_3[1] +
 * param_2[2]*param_3[2] return -(num / den) Pure x87 leaf; single-expression
 * form keeps intermediates in ST(0) to match the FLD/FMUL/FADDP/FSUB/FDIVP/FCHS
 * chain (FSUB not FSUBR: the subtrahend is param_3[3]; FDIVP yields num/den;
 * FCHS negates).  EAX holds param_3 throughout; ECX switches from param_1 to
 * param_2.
 */
float FUN_001057f0(float *param_1, float *param_2, float *param_3)
{
  return -((((param_1[0] * param_3[0] + param_1[1] * param_3[1] +
              param_1[2] * param_3[2]) -
             param_3[3]) /
            (param_2[0] * param_3[0] + param_2[1] * param_3[1] +
             param_2[2] * param_3[2])));
}

/* calculate_vertex (0x105830) — readable C lift (restored pre-naked). */
void calculate_vertex(short subdivision_index /* @<eax> */,
                      short subdivision_count /* @<ecx> */,
                      short parent2 /* @<edx> */, short parent1 /* @<ebx> */,
                      void *sphere /* @<edi> */, short new_vertex)
{
  float frac;
  float inv_frac;
  int itmp;
  float *verts;
  float *vp1;
  float *vp2;
  float *vout;
  short vertex_count;

  itmp = subdivision_index;
  frac = (float)itmp;
  itmp = subdivision_count;
  frac = frac / itmp;
  inv_frac = *(float *)0x002533c8 - frac;

  if (subdivision_index <= 0 || subdivision_index >= subdivision_count) {
    display_assert(
        "subdivision_index > 0 && subdivision_index < subdivision_count",
        "c:\\halo\\SOURCE\\math\\geometry.c", 0x13b, true);
    system_exit(-1);
  }
  vertex_count = *(short *)((char *)sphere + 0xc);
  if (parent1 < 0 || parent1 > vertex_count) {
    display_assert("parent1 >=0 && parent1 <= sphere->vertex_count",
                   "c:\\halo\\SOURCE\\math\\geometry.c", 0x13c, true);
    system_exit(-1);
  }
  if (parent2 < 0 || parent2 > vertex_count) {
    display_assert("parent2 >=0 && parent2 <= sphere->vertex_count",
                   "c:\\halo\\SOURCE\\math\\geometry.c", 0x13d, true);
    system_exit(-1);
  }
  if (new_vertex < 0 || new_vertex > vertex_count) {
    display_assert("new_vertex >=0 && new_vertex <= sphere->vertex_count",
                   "c:\\halo\\SOURCE\\math\\geometry.c", 0x13e, true);
    system_exit(-1);
  }

  verts = *(float **)((char *)sphere + 4);
  vp1 = verts + (int)parent1 * 3;
  vp2 = verts + (int)parent2 * 3;
  vout = verts + (int)new_vertex * 3;
  vout[0] = inv_frac * vp1[0] + frac * vp2[0];
  vout[1] = frac * vp2[1] + inv_frac * vp1[1];
  vout[2] = frac * vp2[2] + inv_frac * vp1[2];
  normalize3d(vout);
}


/* 0x105980 — Build a ring/cylinder (torus-like) mesh.
 * Sweeps ring_segment_count rings around a cross-section of
 * cylinder_segment_count segments. For each ring the ring angle drives a
 * cos/sin pair (scaled by param_8) that offsets a cross-section built by
 * rotating a base radius (param_10) about the ring normal, then transforms
 * each vertex by the caller's matrix.
 * Outputs: vertex positions (out_positions, stride 3 floats), tex coords
 * (out_texcoords, stride 2 floats), a triangle-strip index buffer
 * (out_indices), the emitted vertex count (*out_vertex_count) and the number
 * of strip index-runs (*out_index_run_count).
 * The ring normal is the cross product of the cross-section direction
 * (cos*param_8, sin*param_8, 0) with the global axis vector at *0x31fc44,
 * normalized when its length is >= the epsilon at 0x2533d0.
 * Constants: 0x255a54 = 6.2831855f (2*pi), 0x2533c0 = 0.0f, 0x2533c8 = 1.0f,
 * 0x2533d0 = double epsilon. Asserts at geometry.c:0x15a/0x15b.
 * Source: c:\halo\SOURCE\math\geometry.c:346 */
void FUN_00105980(float *matrix, short *out_vertex_count,
                  short *out_index_run_count, float *out_positions,
                  float *out_texcoords, short *out_indices,
                  short ring_segment_count, float param_8,
                  int cylinder_segment_count, float param_10)
{
  float fVar1, fVar2, fVar4, angle;
  float fVar9, fVar10, fVar11, fVar12, fVar_sin;
  int iVar5;
  float *pfVar6;
  float *pfVar7;
  short sVar8;
  /* normal[0]=local_38, normal[1]=local_34, normal[2]=local_30; the three
   * must be contiguous+ascending because &normal[0] is passed as the axis
   * argument to rotate_vector3d_by_sincos (stack-aliasing hazard). */
  float normal[3];
  int local_2c;
  float local_28, local_24;
  int local_20, local_1c, local_18, local_14, local_10, local_c, local_8;

  local_1c = 0;
  local_8 = 0;
  if (ring_segment_count <= 2) {
    display_assert("ring_segment_count>2", "c:\\halo\\SOURCE\\math\\geometry.c",
                   0x15a, 1);
    system_exit(-1);
  }
  if ((short)cylinder_segment_count <= 2) {
    display_assert("cylinder_segment_count>2",
                   "c:\\halo\\SOURCE\\math\\geometry.c", 0x15b, 1);
    system_exit(-1);
  }
  local_10 = 0;
  if (ring_segment_count < 0) {
    *out_vertex_count = 0;
    *out_index_run_count = 0;
    return;
  }
  local_20 = (int)ring_segment_count;
  local_18 = 0;
  local_24 = (float)local_20;
  pfVar6 = *(float **)0x0031fc44;
  pfVar7 = out_texcoords;
  do {
    fVar9 = (float)local_18 / local_24;
    angle = *(float *)0x00255a54 * fVar9;
    fVar10 = x87_fcos(angle);
    fVar1 = fVar10 * param_8;
    fVar11 = x87_fsin(angle);
    fVar2 = param_8 * fVar11;
    /* ring normal = (fVar1, fVar2, 0) x axis[]; 0x2533c0 == 0.0f.
     * normal[2]=A, normal[1]=B, normal[0]=C; length sum is (C^2+B^2)+A^2 to
     * match the original's x87 add order. */
    normal[2] = fVar1 * pfVar6[1] - fVar2 * pfVar6[0];
    normal[1] = pfVar6[0] * *(float *)0x002533c0 - fVar1 * pfVar6[2];
    normal[0] = fVar2 * pfVar6[2] - pfVar6[1] * *(float *)0x002533c0;
    fVar4 = sqrtf(normal[0] * normal[0] + normal[1] * normal[1] +
                  normal[2] * normal[2]);
    if (fabsf(fVar4) >= (float)*(double *)0x002533d0) {
      fVar4 = *(float *)0x002533c8 / fVar4;
      normal[0] = normal[0] * fVar4;
      normal[1] = normal[1] * fVar4;
      normal[2] = fVar4 * normal[2];
    }
    sVar8 = 0;
    if (-1 < (short)cylinder_segment_count) {
      local_c = (int)(short)cylinder_segment_count;
      local_14 = (local_8 - cylinder_segment_count) + -1;
      local_28 = (float)(fVar9 + fVar9);
      do {
        pfVar7[1] = local_28;
        if (0 < (short)local_10) {
          if (sVar8 == 0) {
            *out_indices = (short)cylinder_segment_count * 2 + 2;
            out_indices = out_indices + 1;
            local_1c = local_1c + 1;
          }
          *out_indices = (short)local_8;
          out_indices[1] = (short)local_14;
          out_indices = out_indices + 2;
        }
        if ((short)local_10 == ring_segment_count) {
          /* last ring: copy the vertex/texcoord from the first ring */
          iVar5 = (local_c + 1) * local_20;
          pfVar6 = out_positions + iVar5 * -3;
          *out_positions = *pfVar6;
          out_positions[1] = pfVar6[1];
          out_positions[2] = pfVar6[2];
          *out_texcoords = out_texcoords[iVar5 * -2];
          pfVar7 = out_texcoords;
        } else {
          local_2c = (int)sVar8;
          fVar9 = (float)local_2c / (float)local_c;
          *pfVar7 = (float)(fVar9 + fVar9);
          if (sVar8 == (short)cylinder_segment_count) {
            /* seam: copy from the start of this ring */
            pfVar6 = out_positions + local_c * -3;
            *out_positions = *pfVar6;
            out_positions[1] = pfVar6[1];
            out_positions[2] = pfVar6[2];
          } else {
            angle = *(float *)0x00255a54 * fVar9;
            fVar12 = x87_fcos(angle);
            *out_positions = fVar10 * param_10;
            out_positions[1] = fVar11 * param_10;
            out_positions[2] = 0.0f;
            fVar_sin = x87_fsin(angle);
            rotate_vector3d_by_sincos(out_positions, normal, fVar_sin, fVar12);
            *out_positions = fVar1 + *out_positions;
            out_positions[2] = out_positions[2];
            out_positions[1] = fVar2 + out_positions[1];
            matrix_transform_point(matrix, out_positions, out_positions);
          }
        }
        pfVar7 = pfVar7 + 2;
        out_positions = out_positions + 3;
        local_8 = local_8 + 1;
        local_14 = local_14 + 1;
        sVar8 = sVar8 + 1;
        pfVar6 = *(float **)0x0031fc44;
        out_texcoords = pfVar7;
      } while (sVar8 <= (short)cylinder_segment_count);
    }
    local_10 = local_10 + 1;
    local_18 = local_18 + 1;
  } while ((short)local_10 <= ring_segment_count);
  *out_vertex_count = (short)local_8;
  *out_index_run_count = (short)local_1c;
}

/* shell_update (0x105c80) — readable C lift (restored pre-naked). */
short shell_update(short vertex_count, float *vertices /* @<ebx> */)
{
  float line[3]; /* [EBP-0x14]=nx, [EBP-0x10]=ny, [EBP-0xc]=d */
  float p0[2];   /* [EBP-0x8], [EBP-0x4] */
  short state;
  short i;
  float eval;

  state = -1;
  for (i = 0; i < vertex_count; i++) {
    int s = (int)state;
    if (s == -1) {
      p0[0] = vertices[i * 2];
      p0[1] = vertices[i * 2 + 1];
      state = 0;
    } else if (s == 0) {
      if (plane2d_from_points(line, &vertices[i * 2], p0) != (float *)0) {
        state = 1;
      }
    } else if (s == 1) {
      eval = line[0] * vertices[i * 2] + line[1] * vertices[i * 2 + 1] - line[2];
      if (fabs(eval) >= *(double *)0x002533d0) {
        state = 2;
      }
    }
    if (state >= 2) {
      break;
    }
  }
  return state;
}



/* convex_hull2d_reduce (0x105d20) — XBE naked draft (batch 80). */
#if defined(__clang__)
static short (*const b105d20_c105c80)(short vertex_count, float *vertices) = shell_update;
static void (*const b105d20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b105d20_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
int16_t convex_hull2d_reduce(int16_t vertex_count __attribute__((unused)), float *vertices __attribute__((unused)), int16_t *out_indices __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, %%ebx\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "call *%[c105c80]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .Lconvex_hull2d_reduce_17\n\t"
      "flds 0x2533c0\n\t"
      "movl $0x7f7fffff, -0x10(%%ebp)\n\t"
      "xorl %%edx, %%edx\n\t"
      "testw %%si, %%si\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movl $0x7f7fffff, -0xc(%%ebp)\n\t"
      "jle .Lconvex_hull2d_reduce_5\n\t"
      "leal 0x4(%%edi), %%ecx\n\t"
      ".Lconvex_hull2d_reduce_1:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsubs 0x253f44\n\t"
      "fcomps (%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lconvex_hull2d_reduce_3\n\t"
      "flds (%%ecx)\n\t"
      "fcomps -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lconvex_hull2d_reduce_2\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fadds 0x253f44\n\t"
      "fcomps -0x4(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lconvex_hull2d_reduce_3\n\t"
      ".Lconvex_hull2d_reduce_2:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fadds 0x253f44\n\t"
      "fcomps (%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_hull2d_reduce_4\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fsubs 0x253f44\n\t"
      "fcomps -0x4(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_hull2d_reduce_4\n\t"
      ".Lconvex_hull2d_reduce_3:\n\t"
      "movl -0x4(%%ecx), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl (%%ecx), %%eax\n\t"
      "movl %%edx, %%esi\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      ".Lconvex_hull2d_reduce_4:\n\t"
      "incl %%edx\n\t"
      "addl $8, %%ecx\n\t"
      "cmpw 0x8(%%ebp), %%dx\n\t"
      "jl .Lconvex_hull2d_reduce_1\n\t"
      ".Lconvex_hull2d_reduce_5:\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      ".Lconvex_hull2d_reduce_6:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpw %%ax, %%cx\n\t"
      "movl $0x7f7fffff, -0x10(%%ebp)\n\t"
      "jge .Lconvex_hull2d_reduce_18\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movswl %%cx, %%ecx\n\t"
      "movw %%si, (%%edx,%%ecx,2)\n\t"
      "incl -0x8(%%ebp)\n\t"
      "xorl %%edx, %%edx\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lconvex_hull2d_reduce_13\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%edi,%%eax,8), %%esi\n\t"
      "movl %%edi, %%ecx\n\t"
      ".Lconvex_hull2d_reduce_7:\n\t"
      "flds (%%ecx)\n\t"
      "fcomps (%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lconvex_hull2d_reduce_8\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fcomps 0x4(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Lconvex_hull2d_reduce_12\n\t"
      ".Lconvex_hull2d_reduce_8:\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "flds (%%ecx)\n\t"
      "fsubs (%%esi)\n\t"
      "fpatan\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "fcoms 0x26a810\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lconvex_hull2d_reduce_10\n\t"
      "jmp .Lconvex_hull2d_reduce_9\n\t"
      "leal (%%esp), %%esp\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lconvex_hull2d_reduce_9:\n\t"
      "fadds 0x255a54\n\t"
      "fcoms 0x26a810\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lconvex_hull2d_reduce_9\n\t"
      ".Lconvex_hull2d_reduce_10:\n\t"
      "fcoms -0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lconvex_hull2d_reduce_11\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "movl %%edx, %%ebx\n\t"
      "jmp .Lconvex_hull2d_reduce_12\n\t"
      ".Lconvex_hull2d_reduce_11:\n\t"
      "fstp %%st(0)\n\t"
      ".Lconvex_hull2d_reduce_12:\n\t"
      "incl %%edx\n\t"
      "addl $8, %%ecx\n\t"
      "cmpw 0x8(%%ebp), %%dx\n\t"
      "jl .Lconvex_hull2d_reduce_7\n\t"
      ".Lconvex_hull2d_reduce_13:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "testb %%al, %%al\n\t"
      "movl %%ebx, %%esi\n\t"
      "jne .Lconvex_hull2d_reduce_15\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movswl (%%edx), %%eax\n\t"
      "movswl %%bx, %%ecx\n\t"
      "flds (%%edi,%%ecx,8)\n\t"
      "leal (%%edi,%%ecx,8), %%ecx\n\t"
      "fsubs (%%edi,%%eax,8)\n\t"
      "leal (%%edi,%%eax,8), %%edx\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lconvex_hull2d_reduce_14\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fsubs 0x4(%%edx)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lconvex_hull2d_reduce_15\n\t"
      ".Lconvex_hull2d_reduce_14:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".Lconvex_hull2d_reduce_15:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movw (%%ecx), %%ax\n\t"
      "cmpw %%ax, %%bx\n\t"
      "je .Lconvex_hull2d_reduce_16\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lconvex_hull2d_reduce_6\n\t"
      "movswl %%bx, %%edx\n\t"
      "flds (%%edi,%%edx,8)\n\t"
      "movswl %%ax, %%eax\n\t"
      "fsubs (%%edi,%%eax,8)\n\t"
      "leal (%%edi,%%edx,8), %%ecx\n\t"
      "leal (%%edi,%%eax,8), %%edx\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lconvex_hull2d_reduce_6\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fsubs 0x4(%%edx)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lconvex_hull2d_reduce_6\n\t"
      ".Lconvex_hull2d_reduce_16:\n\t"
      "fstp %%st(0)\n\t"
      ".Lconvex_hull2d_reduce_17:\n\t"
      "movw -0x8(%%ebp), %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lconvex_hull2d_reduce_18:\n\t"
      "leal -0x1(%%ecx), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "leal -0x1(%%eax), %%esi\n\t"
      "testw %%si, %%si\n\t"
      "jle .Lconvex_hull2d_reduce_25\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movswl %%ax, %%edx\n\t"
      "movw (%%ecx,%%edx,2), %%dx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lconvex_hull2d_reduce_19:\n\t"
      "movswl %%si, %%edi\n\t"
      "cmpw %%dx, (%%ecx,%%edi,2)\n\t"
      "je .Lconvex_hull2d_reduce_20\n\t"
      "decl %%esi\n\t"
      "testw %%si, %%si\n\t"
      "jg .Lconvex_hull2d_reduce_19\n\t"
      "jmp .Lconvex_hull2d_reduce_25\n\t"
      ".Lconvex_hull2d_reduce_20:\n\t"
      "subl %%esi, %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jle .Lconvex_hull2d_reduce_24\n\t"
      "movswl %%si, %%ebx\n\t"
      "leal (%%ecx,%%ebx,2), %%eax\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      ".Lconvex_hull2d_reduce_21:\n\t"
      "cmpw 0x8(%%ebp), %%di\n\t"
      "jl .Lconvex_hull2d_reduce_22\n\t"
      "pushl $1\n\t"
      "pushl $0x279\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28bfb8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lconvex_hull2d_reduce_22:\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "jl .Lconvex_hull2d_reduce_23\n\t"
      "pushl $1\n\t"
      "pushl $0x27a\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28bf88\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lconvex_hull2d_reduce_23:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movw (%%eax), %%dx\n\t"
      "incl %%edi\n\t"
      "movw %%dx, (%%ecx)\n\t"
      "addl $2, %%eax\n\t"
      "addl $2, %%ecx\n\t"
      "incl %%ebx\n\t"
      "cmpw -0x8(%%ebp), %%di\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jl .Lconvex_hull2d_reduce_21\n\t"
      ".Lconvex_hull2d_reduce_24:\n\t"
      "testw %%si, %%si\n\t"
      "jg .Lconvex_hull2d_reduce_17\n\t"
      ".Lconvex_hull2d_reduce_25:\n\t"
      "pushl $1\n\t"
      "pushl $0x282\n\t"
      "pushl $0x28be44\n\t"
      "pushl $0x28bf70\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movw -0x8(%%ebp), %%ax\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c105c80] "m"(b105d20_c105c80), [assert] "m"(b105d20_assert), [exitfn] "m"(b105d20_exitfn)
      : "memory");
}
#else
#error "convex_hull2d_reduce: clang naked draft required"
#endif


/* FUN_00106030 (0x106030) — XBE naked draft (batch 85). */
#if defined(__clang__)
static float (*const b106030_c10c440)(float *param_1, float *param_2) = FUN_0010c440;

__attribute__((naked, noinline))
int FUN_00106030(void *param_1 __attribute__((unused)), int param_2 __attribute__((unused)), short param_3 __attribute__((unused)), int param_4 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "movw 0x10(%%ebp), %%cx\n\t"
      "pushl %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "testw %%cx, %%cx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jle .LFUN_00106030_3\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movswl %%cx, %%ebx\n\t"
      "jmp .LFUN_00106030_1\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00106030_1:\n\t"
      "movswl %%ax, %%edx\n\t"
      "leal -0x1(%%edx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_00106030_2\n\t"
      "leal -0x1(%%ebx), %%eax\n\t"
      ".LFUN_00106030_2:\n\t"
      "movswl (%%edi,%%eax,2), %%eax\n\t"
      "leal (%%esi,%%eax,8), %%ecx\n\t"
      "movswl (%%edi,%%edx,2), %%eax\n\t"
      "flds (%%esi,%%eax,8)\n\t"
      "leal (%%esi,%%eax,8), %%eax\n\t"
      "fsubs (%%ecx)\n\t"
      "leal 0x1(%%edx), %%esi\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "setge %%dl\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x4(%%ecx)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "decl %%edx\n\t"
      "andl %%esi, %%edx\n\t"
      "movswl (%%edi,%%edx,2), %%edx\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "leal (%%esi,%%edx,8), %%edx\n\t"
      "flds (%%edx)\n\t"
      "fsubs (%%eax)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x4(%%edx)\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00106030_4\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10c440]\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "incl %%eax\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "cmpw 0x10(%%ebp), %%ax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jl .LFUN_00106030_1\n\t"
      ".LFUN_00106030_3:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fsubs 0x255a54\n\t"
      "fabs\n\t"
      "fcompl 0x2549d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00106030_5\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00106030_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00106030_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c10c440] "m"(b106030_c10c440)
      : "memory");
}
#else
#error "FUN_00106030: clang naked draft required"
#endif


/* FUN_00106130 (0x106130)
 *
 * Test whether a query point lies within a given radius of a 2D convex
 * polygon.  Points are 2D (x, y pairs, stride 8 bytes).  Uses the
 * cross-product sign to check sidedness; if the point is outside any
 * edge beyond the radius, returns false.
 */
bool FUN_00106130(uint16_t point_count, void *points, void *query_point,
                  float radius)
{
  float *pts = (float *)points;
  float *qp = (float *)query_point;
  int16_t i;
  float radius_sq = radius * radius;

  if ((int16_t)point_count <= 0)
    return true;

  for (i = 0; i < (int16_t)point_count; i++) {
    int idx = (int)i;
    int next = (idx + 1 < (int)(int16_t)point_count) ? idx + 1 : 0;
    float ex, ey, edge_len_sq, dx, dy, cross;

    ex = pts[next * 2] - pts[idx * 2];
    ey = pts[next * 2 + 1] - pts[idx * 2 + 1];
    edge_len_sq = ex * ex + ey * ey;

    if (edge_len_sq == 0.0f)
      continue;

    dx = qp[0] - pts[idx * 2];
    dy = qp[1] - pts[idx * 2 + 1];
    cross = dx * ey - dy * ex;

    if (cross <= 0.0f)
      continue;

    if (cross * cross < edge_len_sq * radius_sq)
      continue;

    return false;
  }
  return true;
}

/* FUN_00106200 (0x106200)
 *
 * 2D point-in-polygon winding test with epsilon tolerance.
 * Tests whether a query point lies inside a 2D polygon by checking the
 * cross-product of each edge against the query point.  Points are stored
 * as float[2] pairs (x, y).  For every edge (vert[i] -> vert[next]),
 * computes:  cross = (point.y - vert_i.y) * (next.x - vert_i.x)
 *                  - (point.x - vert_i.x) * (next.y - vert_i.y)
 * If cross < -epsilon for any edge, the point is outside and returns false.
 * The wrap-around index uses: next = (i+1 >= count) ? 0 : i+1.
 */
bool FUN_00106200(int16_t count, void *points, float *query_point,
                  float epsilon)
{
  int16_t i;
  float neg_epsilon;
  float *qp;
  float *pts;

  i = 0;
  if (count <= 0)
    return true;

  neg_epsilon = -epsilon;
  qp = (float *)query_point;
  pts = (float *)points;

  do {
    int idx = (int)i;
    int next = (idx + 1 >= (int)count) ? 0 : idx + 1;
    float ex, ey, dx, dy;

    ex = pts[next * 2] - pts[idx * 2];
    ey = pts[next * 2 + 1] - pts[idx * 2 + 1];
    dx = qp[0] - pts[idx * 2];
    dy = qp[1] - pts[idx * 2 + 1];

    if (dy * ex - dx * ey < neg_epsilon)
      return false;

    i++;
  } while (i < count);

  return true;
}

/* FUN_00106290 (0x106290)
 *
 * Indexed variant of the 2D point-in-polygon winding test (FUN_00106200).
 * Instead of iterating vertices directly, the polygon boundary is described
 * by an index array (int16 indices, stride 2) into a shared vertex pool
 * (float[2] per vertex, x at +0, y at +4).  For every edge
 * (vert[index[i]] -> vert[index[next]]) computes:
 *   cross = (P.y - A.y) * (B.x - A.x) - (P.x - A.x) * (B.y - A.y)
 * and returns 0 as soon as cross < -epsilon for any edge (point is outside
 * that edge beyond the tolerance).  Returns 1 if the point passes every edge.
 * Empty polygon (count <= 0) returns 1.  Wrap-around index uses
 * next = (i+1 >= count) ? 0 : i+1.  Indices are loaded narrow (int16, signed);
 * the cross-product/subtraction order matches FUN_00106200 and disassembly.
 */
int FUN_00106290(int16_t count, void *index_array, void *vertex_base,
                 float *query_point, float epsilon)
{
  int16_t i;
  float neg_epsilon;
  int16_t *indices;
  float *verts;
  float *qp;

  i = 0;
  if (count <= 0)
    return 1;

  neg_epsilon = -epsilon;
  indices = (int16_t *)index_array;
  verts = (float *)vertex_base;
  qp = query_point;

  do {
    int idx = (int)i;
    int next = (idx + 1 >= (int)count) ? 0 : idx + 1;
    int a = (int)indices[idx];
    int b = (int)indices[next];
    float *A = &verts[a * 2];
    float ax = A[0], ay = A[1];
    float bx = verts[b * 2];
    float by = verts[b * 2 + 1];
    float dx = qp[0] - ax;
    float dy = qp[1] - ay;
    float ex = bx - ax;
    float ey = by - ay;

    if (dy * ex - dx * ey < neg_epsilon)
      return 0;

    i++;
  } while (i < count);

  return 1;
}

/* FUN_00106330 (0x106330) — readable C lift from XBE leaf. */
float FUN_00106330(int16_t count, float *points)
{
  float acc;
  float half = *(float *)0x253398;
  float zero = *(float *)0x2533c0;
  int i;
  float dx1, dy1, dx2, dy2;

  acc = zero;
  if (count > 2) {
    for (i = 0; i < (int)count - 2; i++) {
      dx1 = points[2 * (i + 1)] - points[0];
      dy1 = points[2 * (i + 1) + 1] - points[1];
      dx2 = points[2 * (i + 2)] - points[0];
      dy2 = points[2 * (i + 2) + 1] - points[1];
      acc += (dx1 * dy2 - dy1 * dx2) * half;
    }
  }
  if (acc < 0) {
    acc = -acc;
  }
  return acc;
}




/* FUN_0018e420 (0x18e420)
 *
 * Returns the global BSP3D pointer (DAT_005064d8). Asserts with a halt if
 * the pointer has not been initialized (i.e. is NULL). Called by BSP
 * traversal and portal-intersection code to obtain the current structure
 * BSP3D tag data.
 *
 * Confirmed: no parameters (plain MOV EAX,[global]; TEST; RET).
 * Confirmed: assert string "global_bsp3d", file scenario.c, line 0xd5.
 */
void *FUN_0018e420(void)
{
  if (*(void **)0x5064d8 == NULL) {
    display_assert("global_bsp3d", "c:\\halo\\SOURCE\\scenario\\scenario.c",
                   0xd5, true);
    system_exit(-1);
  }
  return *(void **)0x5064d8;
}

/* reference_list_remove (0x1913c0) — XBE naked draft (batch 90). */
#if defined(__clang__)
static void *(*const b1913c0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char * (*const b1913c0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b1913c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1913c0_exitfn)(int) = system_exit;
static void (*const b1913c0_c1196d0)(data_t *data, int datum_handle) = datum_delete;

__attribute__((naked, noinline))
void reference_list_remove(data_t *data __attribute__((unused)), int *head __attribute__((unused)), int value __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "cmpl $-1, (%%esi)\n\t"
      "pushl %%edi\n\t"
      "je .Lreference_list_remove_2\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      ".Lreference_list_remove_1:\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .Lreference_list_remove_3\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "leal 0x8(%%edi), %%esi\n\t"
      "jne .Lreference_list_remove_1\n\t"
      ".Lreference_list_remove_2:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl $0x6d\n\t"
      "pushl $0x2b25a0\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2b2564\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lreference_list_remove_3:\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1196d0]\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "movl %%eax, (%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1913c0_dget), [c8d9d0] "m"(b1913c0_c8d9d0), [assert] "m"(b1913c0_assert), [exitfn] "m"(b1913c0_exitfn), [c1196d0] "m"(b1913c0_c1196d0)
      : "memory");
}
#else
#error "reference_list_remove: clang naked draft required"
#endif


/* reference_list_copy (0x191440) — XBE naked draft (batch 89). */
#if defined(__clang__)
static void (*const b191440_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b191440_exitfn)(int) = system_exit;
static void (*const b191440_c1196d0)(data_t *data, int datum_handle) = datum_delete;

__attribute__((naked, noinline))
void reference_list_copy(void *result __attribute__((unused)), void *source __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movw 0x22(%%edi), %%ax\n\t"
      "cmpw 0x22(%%ebx), %%ax\n\t"
      "je .Lreference_list_copy_1\n\t"
      "pushl $1\n\t"
      "pushl $0x88\n\t"
      "pushl $0x2b25a0\n\t"
      "pushl $0x2b25f0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lreference_list_copy_1:\n\t"
      "movw 0x20(%%edi), %%cx\n\t"
      "cmpw 0x20(%%ebx), %%cx\n\t"
      "je .Lreference_list_copy_2\n\t"
      "pushl $1\n\t"
      "pushl $0x89\n\t"
      "pushl $0x2b25a0\n\t"
      "pushl $0x2b25c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lreference_list_copy_2:\n\t"
      "movl 0x34(%%edi), %%eax\n\t"
      "movl 0x34(%%ebx), %%ebx\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpw %%si, 0x20(%%edi)\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "jle .Lreference_list_copy_6\n\t"
      ".Lreference_list_copy_3:\n\t"
      "cmpw $0, (%%ebx)\n\t"
      "je .Lreference_list_copy_4\n\t"
      "movl %%ebx, %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "jmp .Lreference_list_copy_5\n\t"
      ".Lreference_list_copy_4:\n\t"
      "cmpw $0, (%%eax)\n\t"
      "je .Lreference_list_copy_5\n\t"
      "movswl %%si, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c1196d0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lreference_list_copy_5:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "incl %%esi\n\t"
      "addl $0xc, %%eax\n\t"
      "addl $0xc, %%ebx\n\t"
      "cmpw 0x20(%%edi), %%si\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "jl .Lreference_list_copy_3\n\t"
      ".Lreference_list_copy_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b191440_assert), [exitfn] "m"(b191440_exitfn), [c1196d0] "m"(b191440_c1196d0)
      : "memory");
}
#else
#error "reference_list_copy: clang naked draft required"
#endif


/* cluster_partition_globals_new (0x191500) — readable C lift.
 *
 * Allocate the cluster first-ref table (0x800 bytes) plus two game-state
 * datum arrays (object refs / cluster refs), stuffing them into out[0..2].
 */
void cluster_partition_globals_new(void **out, const char *name)
{
  char name_buf[0x100];
  char full_buf[0x100];

  out[0] = game_state_malloc(name, (const char *)0x2b2654, 0x800);
  crt_sprintf(name_buf, (const char *)0x2b2648, name);
  crt_sprintf(full_buf, (const char *)0x280e94, name_buf);
  out[1] = game_state_data_new(full_buf, 0x800, 0xc);
  crt_sprintf(name_buf, (const char *)0x2b263c, name);
  crt_sprintf(full_buf, (const char *)0x280e94, name_buf);
  out[2] = game_state_data_new(full_buf, 0x800, 0xc);
  if (out[0] == NULL || out[2] == NULL || out[1] == NULL)
    error(0, (const char *)0x2b260c, name);
}


/* cluster_partition_clear (0x1915d0) — readable C lift. */
void cluster_partition_clear(void *partition)
{
  char *p = (char *)partition;
  csmemset(*(void **)p, -1, 0x800);
  data_delete_all(*(data_t **)(p + 8));
  data_delete_all(*(data_t **)(p + 4));
}

/* cluster_partition_dispose (0x191600) — readable C lift. */
void cluster_partition_dispose(void *partition)
{
  char *p = (char *)partition;
  data_t *a = *(data_t **)(p + 8);
  data_t *b = *(data_t **)(p + 4);
  if (*(char *)((char *)a + 0x24) != 0) {
    data_make_invalid(a);
  }
  if (*(char *)((char *)b + 0x24) != 0) {
    data_make_invalid(b);
  }
}

/* cluster_partition_null_references (0x191630) — readable C lift. */
void cluster_partition_null_references(int *partition)
{
  if (partition[0] != 0) {
    partition[0] = 0;
  }
  if (partition[2] != 0) {
    partition[2] = 0;
  }
  if (partition[1] != 0) {
    partition[1] = 0;
  }
}

/* cluster_partition_iter_next (0x191660) — readable C lift. */
int cluster_partition_iter_next(void *partition, int *state)
{
  int cur = *state;
  char *entry;
  if (cur == -1) {
    return -1;
  }
  entry = (char *)datum_get(*(void **)((char *)partition + 4), cur);
  *state = *(int *)(entry + 8);
  return *(int *)(entry + 4);
}

/* Seed-and-advance a cluster iterator (0x191690).
 * Stores cluster_handle into *out_cluster unconditionally; if the handle is
 * valid (!= -1), fetches the cluster reference datum from the pool at
 * cluster_list+8, overwrites *out_cluster with the next link (ref+8), and
 * returns the reference value (ref+4). Returns -1 for an exhausted handle.
 */
int FUN_00191690(void *cluster_list, int *out_cluster, int cluster_handle)
{
  *out_cluster = cluster_handle;
  if (cluster_handle != -1) {
    char *cluster_reference =
      datum_get(*(void **)((char *)cluster_list + 8), cluster_handle);
    *out_cluster = *(int *)(cluster_reference + 8);
    return *(int *)(cluster_reference + 4);
  }

  return -1;
}

/* Advance a cluster iterator over the pool at offset +8 (0x1916d0).
 * Advance-only counterpart to FUN_00191690 (which seeds *state first). If the
 * current handle (*state) is exhausted (-1) returns -1; otherwise fetches the
 * reference datum from the pool at partition+8, advances *state to the next
 * link (ref+8), and returns the reference value (ref+4).
 */
int FUN_001916d0(int partition, int *state)
{
  if (*state != -1) {
    char *cluster_reference = datum_get(*(void **)(partition + 8), *state);
    *state = *(int *)(cluster_reference + 8);
    return *(int *)(cluster_reference + 4);
  }

  return -1;
}

/* cluster_partition_copy (0x191700) — readable C lift from XBE leaf. */
void cluster_partition_copy(void *destination, void *source)
{
  void *scenario;
  int count;

  scenario = global_scenario_get();
  count = *(int *)((char *)scenario + 0x134);
  csmemcpy(*(void **)destination, *(void **)source, (size_t)count * 4);  reference_list_copy(*(void **)((char *)destination + 8),
                      *(void **)((char *)source + 8));
  reference_list_copy(*(void **)((char *)destination + 4),
                      *(void **)((char *)source + 4));
}




/* FUN_00191750 (0x191750) — readable C lift from XBE leaf. */int *FUN_00191750(short cluster_index, int **partition)
{
  extern char DAT_002b2668[];
  extern char DAT_002b26b8[];
  void *scenario;

  if (cluster_index < 0) {
    goto bad;
  }
  scenario = global_scenario_get();
  if ((int)cluster_index >= *(int *)((char *)scenario + 0x134)) {
bad:    display_assert(DAT_002b2668, DAT_002b26b8, 0xd5, true);
    system_exit(-1);
  }
  return *partition + (int)cluster_index;
}



/* cluster_partition_add_object (0x1917a0) — readable C lift (restored pre-naked). */
void cluster_partition_add_object(void *partition, int object_handle,
                                  void *first_cluster_ref, void *position,
                                  uint32_t radius_fp, void *location)
{
  int **part = (int **)partition;
  int *first_ref = (int *)first_cluster_ref;
  short *pos = (short *)position;
  char *loc = (char *)location;
  short local_clusters[64];
  uint16_t cluster_bsp_index;
  union {
    uint32_t u;
    float f;
  } rad;
  int16_t cluster_count;

  assert_halt(partition);
  assert_halt(first_cluster_ref);
  assert_halt(*first_ref == -1);
  assert_halt(position);
  assert_halt(location);

  cluster_bsp_index = *(uint16_t *)(loc + 4);
  rad.u = radius_fp;

  cluster_count = structure_find_in_cluster(cluster_bsp_index, (float *)pos,
                                            rad.f, 0x40, local_clusters);

  if (cluster_count > 0x40) {
    error(2, "an object or light spanned %d clusters.", (int)cluster_count);
    cluster_count = 0x40;
  }

  {
    int i;
    short *cluster_ptr = local_clusters;
    for (i = 0; i < (int)(uint16_t)cluster_count; i++, cluster_ptr++) {
      short cluster_index = *cluster_ptr;

      {
        data_t *obj_ref_data = (data_t *)part[2];
        int obj_ref_handle = data_new_at_index(obj_ref_data);
        if (obj_ref_handle == -1) {
          error(2, "WARNING: maximum %ss per map (%d) exceeded.", obj_ref_data,
                (int)*(short *)((char *)obj_ref_data + 0x20));
        } else {
          int *obj_ref = (int *)datum_get(obj_ref_data, obj_ref_handle);
          obj_ref[1] = (int)cluster_index;
          obj_ref[2] = *first_ref;
          *first_ref = obj_ref_handle;
        }
      }

      if (cluster_index < 0 ||
          (int)cluster_index >= *(int *)((char *)scenario_get() + 0x134)) {
        display_assert(
          "cluster_index>=0 && "
          "cluster_index<global_structure_bsp_get()->clusters.count",
          "c:\\halo\\SOURCE\\structures\\cluster_partitions.c", 0xd5, true);
        system_exit(-1);
      }

      {
        int *cluster_head = &part[0][(int)cluster_index];
        data_t *cluster_ref_data = (data_t *)part[1];
        int cluster_ref_handle = data_new_at_index(cluster_ref_data);
        if (cluster_ref_handle == -1) {
          error(2, "WARNING: maximum %ss per map (%d) exceeded.",
                cluster_ref_data,
                (int)*(short *)((char *)cluster_ref_data + 0x20));
        } else {
          int *cluster_ref =
            (int *)datum_get(cluster_ref_data, cluster_ref_handle);
          cluster_ref[1] = object_handle;
          cluster_ref[2] = *cluster_head;
          *cluster_head = cluster_ref_handle;
        }
      }
    }
  }
}



/* cluster_partition_remove_object (0x1919a0) — readable C lift.
 *
 * Walk the object's cluster-ref linked list, deleting each cluster-ref datum
 * and removing the object from that cluster's object list, then clear the
 * caller's first_cluster_ref head to -1.
 */
void cluster_partition_remove_object(void *partition, int object_handle,
                                     void *first_cluster_ref)
{
  char *part = (char *)partition;
  int *head = (int *)first_cluster_ref;
  int handle;
  char *datum;
  int16_t cluster_idx;
  void *scenario;

  handle = *head;
  if (handle != -1) {
    do {
      datum = (char *)datum_get(*(void **)(part + 8), handle);
      cluster_idx = *(int16_t *)(datum + 4);
      datum_delete(*(data_t **)(part + 8), handle);
      if (cluster_idx < 0) {
        display_assert((const char *)0x2b2668, (const char *)0x2b26b8, 0xd5,
                       true);
        system_exit(-1);
      }
      scenario = scenario_get();
      if ((int)cluster_idx >= *(int *)((char *)scenario + 0x134)) {
        display_assert((const char *)0x2b2668, (const char *)0x2b26b8, 0xd5,
                       true);
        system_exit(-1);
      }
      reference_list_remove(*(void **)(part + 4),
                            (int *)(*(int *)part + (int)cluster_idx * 4),
                            object_handle);
      handle = *(int *)(datum + 8);
    } while (handle != -1);
  }
  *head = -1;
}


/* cluster_partition_iter_first (0x191a50) — readable C lift from XBE leaf. */
int cluster_partition_iter_first(void *partition, int *state, int16_t cluster_idx)
{
  void *scenario;
  int handle;
  void *data;
  char *datum;

  if (cluster_idx < 0) {
    extern char DAT_002b2668[];
    extern char DAT_002b26b8[];
    display_assert(DAT_002b2668, DAT_002b26b8, 0xd5, 1);
    system_exit(-1);
  }
  scenario = global_scenario_get();
  if ((int)cluster_idx >= *(int *)((char *)scenario + 0x134)) {
    extern char DAT_002b2668[];
    extern char DAT_002b26b8[];
    display_assert(DAT_002b2668, DAT_002b26b8, 0xd5, 1);
    system_exit(-1);
  }
  handle = *(int *)(*(int *)partition + (int)cluster_idx * 4);
  *state = handle;
  data = *(void **)((char *)partition + 4);
  if (handle == -1)
    return -1;
  datum = (char *)datum_get(data, handle);
  *state = *(int *)(datum + 8);
  return *(int *)(datum + 4);
}



/* leaf_map_node_stack_push (FUN_00191ad0, 0x191ad0)
 *
 * Bounds-checked push onto the global leaf-map node stack.  If the stack is
 * already full (count > MAXIMUM_NODE_STACK_COUNT-1 = 0xff), fires the engine
 * assert then system_exit(-1); otherwise stores the node value at
 * node_stack[count] and increments count.
 *
 * Confirmed from disassembly at 0x191ad0:
 *   - node_stack_count : int16 @ 0x4d8e90 (cmpw $0x100 / movswl / incw prove
 *     a 16-bit signed counter, not int32)
 *   - node_stack       : int32[256] @ 0x4d8a90 (0x400 bytes, ends at 0x4d8e90)
 *   - MAXIMUM_NODE_STACK_COUNT = 0x100; guard fires when count >= 0x100.
 *   - display_assert(reason, "c:\\halo\\SOURCE\\structures\\leaf_map.c", 0x2a,
 * 1) then system_exit(-1) (thunk_FUN_001029a0 resolves to system_exit
 * @0x8e2f0).
 *   - Single cdecl stack arg (the pushed node value); kb decl was void(void).
 */
void leaf_map_node_stack_push(int32_t node)
{
  if (*(int16_t *)0x4d8e90 >= 0x100) {
    display_assert("leaf_map_globals.node_stack_count<MAXIMUM_NODE_STACK_COUNT",
                   "c:\\halo\\SOURCE\\structures\\leaf_map.c", 0x2a, 1);
    system_exit(-1);
  }
  *(int32_t *)(0x4d8a90 + *(int16_t *)0x4d8e90 * 4) = node;
  ++*(int16_t *)0x4d8e90;
}

/* leaf_map_node_stack_pop (0x191b20)
 *
 * Pops and returns the top entry of the global leaf-map node stack.
 * Asserts the stack is non-empty (leaf_map.c:0x33) then decrements the
 * 16-bit count and returns node_stack[count].
 *
 * Confirmed from disassembly at 0x191b20: 16-bit DEC on AX then MOVSWL of
 * the same register indexes the int32 array at 0x4d8a90.  No callers exist
 * in the shipped XBE (editor-era leaf_map code, like its neighbors).
 */
int32_t leaf_map_node_stack_pop(void)
{
  int16_t count;
  if (*(int16_t *)0x4d8e90 <= 0) {
    display_assert("leaf_map_globals.node_stack_count>0",
                   "c:\\halo\\SOURCE\\structures\\leaf_map.c", 0x33, 1);
    system_exit(-1);
  }
  count = (int16_t)(*(int16_t *)0x4d8e90 - 1);
  *(int16_t *)0x4d8e90 = count;
  return *(int32_t *)(0x4d8a90 + count * 4);
}

/* leaf_map_node_stack_peek (0x191b60)
 *
 * Returns the stack entry levels_up below the top without popping:
 * node_stack[count - levels_up - 1] (levels_up = 0 reads the top).
 * Asserts 0 <= levels_up < count (leaf_map.c:0x3b).
 *
 * Confirmed from disassembly at 0x191b60:
 *   - levels_up arrives in SI (TESTW SI,SI at entry with no prior write);
 *     registered as @<si> in kb.json.
 *   - the load uses base 0x4d8a8c = node_stack - 4 with index
 *     (count - levels_up), i.e. node_stack[count - levels_up - 1].
 *   - No callers exist in the shipped XBE.
 */
int32_t leaf_map_node_stack_peek(int16_t levels_up)
{
  if (!(levels_up >= 0 && levels_up < *(int16_t *)0x4d8e90)) {
    display_assert(
      "levels_up>=0 && levels_up<leaf_map_globals.node_stack_count",
      "c:\\halo\\SOURCE\\structures\\leaf_map.c", 0x3b, 1);
    system_exit(-1);
  }
  return *(int32_t *)(0x4d8a8c +
                      ((int32_t) * (int16_t *)0x4d8e90 - levels_up) * 4);
}

/* FUN_00191ba0 (0x191ba0)
 *
 * Clears two tag_block members of a structure by resizing each to zero
 * elements.  The structure base is passed as a single cdecl stack argument;
 * the two 0xC-byte tag_blocks (count/address/definition triple) live at
 * base+0x4 and base+0x10.
 *
 * Confirmed from disassembly at 0x191ba0:
 *   - No FPU ops, no branching; two cdecl CALLs to tag_block_resize
 *     (FUN_001b9a90), each: push 0 (count); push block-ptr; call; ADD ESP,8.
 *   - kb decl was void(void); real signature is void f(void *base).
 */
void FUN_00191ba0(void *base)
{
  tag_block_resize((char *)base + 0x4, 0);
  tag_block_resize((char *)base + 0x10, 0);
}

/* FUN_00191bd0 (0x191bd0) — readable C lift (restored pre-naked). */
char FUN_00191bd0(int search_value /* @<ebx> */, void **param_1, char *out)
{
  short count;
  short i;
  int node;
  int *element;

  count = *(short *)0x004d8e90;
  i = 0;
  if (count <= 0) {
    return 0;
  }
  do {
    if (i < 0 || i >= count) {
      display_assert(
          "levels_up>=0 && levels_up<leaf_map_globals.node_stack_count",
          "c:\\halo\\SOURCE\\structures\\leaf_map.c", 0x3b, true);
      system_exit(-1);
    }
    node = *(int *)(0x004d8a8c + ((int)count - (int)i) * 4);
    element = (int *)tag_block_get_element(*param_1, node & 0x7fffffff, 0xc);
    if (*element == search_value) {
      *out = (char)((node & 0x80000000) != 0);
      return 1;
    }
    count = *(short *)0x004d8e90;
    i = (short)(i + 1);
  } while (i < count);
  return 0;
}



/* FUN_00191c70 (0x191c70) — readable C lift from XBE leaf. */
short FUN_00191c70(void *block, int search_value)
{
  short i;
  void *elem;

  if (*(int *)block <= 0) {
    return (short)0xffff;
  }
  i = 0;
  do {
    elem = tag_block_get_element(block, (int)i, 0x10);
    if (*(int *)elem == search_value) {
      return i;
    }
    i = (short)(i + 1);
  } while ((int)i < *(int *)block);
  return (short)0xffff;
}




/* leaf_map_mark_portal_designators (0x191cb0) — readable C lift (restored pre-naked). */
void leaf_map_mark_portal_designators(void *structure, uint32_t portal_index)
{
  int *designator_count;
  uint32_t *designator;
  int block_index;
  short designator_index;
  int remaining;
  uint32_t *portal;
  int leaves_block;

  portal = (uint32_t *)tag_block_get_element((char *)structure + 0x10,
                                             portal_index, 0x18);
  leaves_block = (int)structure + 4;
  remaining = 2;
  do {
    portal = portal + 1;
    block_index = (int)tag_block_get_element((void *)leaves_block,
                                             *portal & 0x7fffffff, 0x18);
    designator_count = (int *)(block_index + 0xc);
    designator_index = 0;
    if (0 < *designator_count) {
      block_index = 0;
      do {
        designator =
          (uint32_t *)tag_block_get_element(designator_count, block_index, 4);
        if ((*designator & 0x7fffffff) == portal_index) {
          *designator = *designator | 0x80000000;
          break;
        }
        designator_index = designator_index + 1;
        block_index = (int)designator_index;
      } while (block_index < *designator_count);
    }
    if ((int)designator_index == *designator_count) {
      display_assert("portal_designator_index!=leaf->portal_designators.count",
                     "c:\\halo\\SOURCE\\structures\\leaf_map.c", 0x2a1, 1);
      system_exit(-1);
    }
    remaining = remaining - 1;
  } while (remaining != 0);
}



/* FUN_00191d80 (0x191d80)
 *
 * Fetches an outer tag_block element (block = base+4, index masked to
 * 31 bits, stride 0x18), then scans the nested tag_block located at
 * outer_element+0xc (stride 4). Returns false (0) as soon as any inner
 * element's leading int is non-negative; otherwise returns the low byte
 * of the nested element count.
 *
 * Confirmed from disassembly at 0x191d80:
 *   - two cdecl calls to tag_block_get_element (ADD ESP,0xc each);
 *     push order gives (block, index, element_size).
 *   - the nested block pointer (outer_element+0xc) is held in ESI for
 *     the whole function; *ESI is the element count (int at offset 0).
 *   - inner loop counter is a signed short: INC EDI; MOVSX EAX,DI;
 *     CMP EAX,ECX; JL — kept as `short` so codegen emits the MOVSX.
 *   - both RET sites return AL only: early XOR AL,AL (false), and
 *     fall-through MOV AL,byte ptr [ESI] (low byte of the count).
 */
char FUN_00191d80(int base, unsigned int index)
{
  int *count_block;
  int count;
  int *inner;
  short i;

  count_block = (int *)((int)tag_block_get_element((void *)(base + 4),
                                                   index & 0x7fffffff, 0x18) +
                        0xc);
  count = *count_block;
  i = 0;
  if (0 < count) {
    count = 0;
    do {
      inner = (int *)tag_block_get_element(count_block, count, 4);
      if (-1 < *inner) {
        return 0;
      }
      i = i + 1;
      count = (int)i;
    } while (count < *count_block);
  }
  return *(char *)count_block;
}

/* FUN_00191de0 (0x191de0)
 *
 * Recursive cluster-visibility flood-fill. Given a cluster index, walks that
 * cluster's portal list (nested tag_block at cluster+0xc). For each portal it
 * resolves the connection element (descriptor+0x10) to find the neighbouring
 * cluster: the connection stores its two endpoint cluster indices at +4 and
 * +8; whichever is not the current cluster is the neighbour. It sets the
 * neighbour's bit in the destination bitset and, if that bit was newly set,
 * recurses into the neighbour.
 *
 * Confirmed from disassembly at 0x191de0:
 * - cluster elem = tag_block_get_element(descriptor+4, index&0x7fffffff, 0x18)
 * - portal block header at cluster+0xc; portal element size 4, its *value is
 *   the connection index (masked 0x7fffffff)
 * - connection elem = tag_block_get_element(descriptor+0x10, conn, 0x18)
 * - neighbour = *(conn+4); if neighbour == index, neighbour = *(conn+8)
 * - bit_mask = 1 << (neighbour & 0x1f); word = dst + (neighbour>>5)*4
 * - the loop counter is a signed 16-bit index (MOVSX AX), compared against the
 *   portal count re-read from *(cluster+0xc) each iteration
 * All calls cdecl, args pushed right-to-left; self-recursive.
 */
void FUN_00191de0(int descriptor, int dst, unsigned int cluster_index)
{
  int *portal_block;
  int connection_elem;
  unsigned int *portal;
  unsigned int neighbor;
  unsigned int bit_mask;
  unsigned int *word;
  short i;
  int i_idx;

  portal_block =
    (int *)((char *)tag_block_get_element((void *)(descriptor + 4),
                                          cluster_index & 0x7fffffff, 0x18) +
            0xc);
  i = 0;
  if (0 < *portal_block) {
    i_idx = 0;
    do {
      portal = (unsigned int *)tag_block_get_element(portal_block, i_idx, 4);
      connection_elem = (int)tag_block_get_element((void *)(descriptor + 0x10),
                                                   *portal & 0x7fffffff, 0x18);
      neighbor = *(unsigned int *)(connection_elem + 4);
      if (neighbor == cluster_index) {
        neighbor = *(unsigned int *)(connection_elem + 8);
      }
      bit_mask = 1 << (neighbor & 0x1f);
      word = (unsigned int *)(dst + ((int)neighbor >> 5) * 4);
      if ((bit_mask & *word) == 0) {
        *word = *word | bit_mask;
        FUN_00191de0(descriptor, dst, neighbor);
      }
      i = i + 1;
      i_idx = (int)i;
    } while (i_idx < *portal_block);
  }
  return;
}

/* FUN_00191e90 (0x191e90)
 *
 * Draws a debug triangle-fan outline for one element of a tag block.
 * Fetches the outer tag_block element (block = param_1+0x10, index =
 * low 31 bits of param_2, stride 0x18); the nested tag_block at
 * element+0xc holds the fan vertices (count@0, elements@+4, stride 0xc).
 * The high bit of param_2 selects one of two hard-coded fill colors.
 *
 * For each vertex i in [2, count):
 *   - FUN_00188890 fills the fan triangle (vertex0, vertex(i-1),
 *     vertex(i)) with the selected color.
 *   - FUN_00189270 draws the edge line vertex(i-1)->vertex(i) in the
 *     global debug color pointed to by [0x2ee6d0].
 * Two trailing FUN_00189270 calls close the fan: edge (0,1) and edge
 * (0,count-1).
 *
 * Confirmed from disassembly at 0x191e90:
 *   - Ghidra mis-groups the cdecl args (§7): each tag_block_get_element
 *     cleans only 3 args (ADD ESP,0xc); the surplus pushes belong to the
 *     outer FUN_00188890 (ADD ESP,0x14) / FUN_00189270 (ADD ESP,0x10).
 *   - color select: TEST ESI,0x80000000; SETNZ CL; color = colors+CL*0x10.
 *   - fan index is a signed short widened to int each iteration (INC;MOVSX).
 *   - the global color [0x2ee6d0] is re-read fresh on every call.
 *   - MSVC evaluates call args right-to-left, so the tag_block_get_element
 *     for the higher vertex index fires before the lower one; the arg
 *     order below reproduces that push sequence.
 */
void FUN_00191e90(int param_1, int param_2)
{
  int *verts;
  float colors[8];
  short i;
  int idx;

  verts = (int *)((int)tag_block_get_element((void *)(param_1 + 0x10),
                                             param_2 & 0x7fffffff, 0x18) +
                  0xc);
  colors[0] = 0.1f;
  colors[1] = 0.0f;
  colors[2] = 1.0f;
  colors[3] = 0.0f;
  colors[4] = 0.1f;
  colors[5] = 1.0f;
  colors[6] = 0.0f;
  colors[7] = 0.0f;

  i = 2;
  idx = 2;
  if (2 < *verts) {
    do {
      FUN_00188890(
        1, (float *)tag_block_get_element(verts, 0, 0xc),
        (float *)tag_block_get_element(verts, idx - 1, 0xc),
        (float *)tag_block_get_element(verts, idx, 0xc),
        (void *)((char *)colors +
                 (((unsigned int)param_2 & 0x80000000) != 0) * 0x10));
      FUN_00189270(1, (float *)tag_block_get_element(verts, idx - 1, 0xc),
                   (float *)tag_block_get_element(verts, idx, 0xc),
                   *(void **)0x2ee6d0);
      i = i + 1;
      idx = (int)i;
    } while (idx < *verts);
  }
  FUN_00189270(1, (float *)tag_block_get_element(verts, 0, 0xc),
               (float *)tag_block_get_element(verts, 1, 0xc),
               *(void **)0x2ee6d0);
  FUN_00189270(1, (float *)tag_block_get_element(verts, 0, 0xc),
               (float *)tag_block_get_element(verts, *verts - 1, 0xc),
               *(void **)0x2ee6d0);
}

/* FUN_00191ff0 (0x191ff0)
 *
 * Tag-block iterator. Fetches the tag-block element at
 * (index & 0x7fffffff) with stride 0x18 from the block at base+4,
 * then walks the nested tag-block at element+0xc (count@0, elements@+4),
 * passing each 4-byte element's first dword to FUN_00191e90(base, *elem).
 *
 * Confirmed from disassembly at 0x191ff0:
 * - outer tag_block_get_element(base+4, index & 0x7fffffff, 0x18)
 * - nested block pointer = element + 0xc
 * - inner tag_block_get_element(nested, i, 4)
 * - loop counter is a 16-bit short widened to int each iteration (movsx)
 * All calls cdecl, args pushed right-to-left. No FPU.
 */
void FUN_00191ff0(int base, unsigned int index)
{
  int *count_block;
  int i_idx;
  int *inner;
  short i;

  count_block = (int *)((int)tag_block_get_element((void *)(base + 4),
                                                   index & 0x7fffffff, 0x18) +
                        0xc);
  i = 0;
  if (0 < *count_block) {
    i_idx = 0;
    do {
      inner = (int *)tag_block_get_element(count_block, i_idx, 4);
      FUN_00191e90(base, *inner);
      i = i + 1;
      i_idx = (int)i;
    } while (i_idx < *count_block);
  }
}

/* FUN_001926a0 (0x1926a0)
 *
 * Copies a tag-block bitset from src to dst (word-granular), then for
 * every bit set in the destination bitset invokes FUN_00191de0 to
 * propagate/traverse the corresponding element.
 *
 * Confirmed from disassembly at 0x1926a0:
 * - descriptor at param_1; element count at *(param_1+4)
 * - if src != dst: csmemcpy(dst, src, ((count+0x1f)>>5)<<2) bytes
 *   (word-granular rounded copy of the bitset)
 * - for each bit index i in [0,count) that is set in the dst bitset:
 *     FUN_00191de0(descriptor, dst, i)
 * - count is re-read from *(param_1+4) every iteration (not cached)
 * - returns byte-bool true (AL=1; CONCAT31 high bytes are incidental)
 * All calls cdecl, args pushed right-to-left. No FPU.
 */
unsigned char FUN_001926a0(int descriptor, int src, int dst)
{
  int count;
  int i;

  if (src != dst) {
    csmemcpy((void *)dst, (void *)src,
             (size_t)(((*(int *)(descriptor + 4) + 0x1f) >> 5) * 4));
  }
  count = *(int *)(descriptor + 4);
  i = 0;
  if (0 < count) {
    do {
      if ((*(unsigned int *)(dst + (i >> 5) * 4) & (1 << (i & 0x1f))) != 0) {
        FUN_00191de0(descriptor, dst, i);
      }
      count = *(int *)(descriptor + 4);
      i = i + 1;
    } while (i < count);
  }
  return 1;
}

void structure_detail_objects_initialize(void)
{
  int base;

  base = (int)game_state_malloc("structure detail objects", 0, 0xa430);
  *(int *)(base + 0xa420) = 0;
  *(int *)(base + 0xa424) = 0;
  *(int *)(base + 0xa428) = 0x3f800000; /* 1.0f */
  *(int *)0x4d8ea0 = base;
  *(int *)(base + 0xa42c) = 0;
}

/* structure_detail_objects_initialize_for_new_map @ 0x193bb0
 * Per-map reset of the detail_object_global_runtime_data block. Asserts the
 * block was allocated (sibling structure_detail_objects_initialize stores the
 * base at 0x4d8ea0), then zeroes the whole 0xa430-byte block and clears the
 * byte at base+0x520e. display_assert lineno 0x6d (109), halt=1; on failure
 * the original tail-calls system_exit(-1) (the assert hard-exit).
 * Global 0x4d8ea0 re-read (not cached) to match the original. */
/* noinline: original build had this in a separate TU
 * (structure_detail_objects.c). */
__declspec(noinline) void structure_detail_objects_initialize_for_new_map(void)
{
  if (*(int *)0x4d8ea0 == 0) {
    display_assert("detail_object_global_runtime_data",
                   "c:\\halo\\SOURCE\\structures\\structure_detail_objects.c",
                   0x6d, 1);
    system_exit(-1);
  }
  csmemset(*(void **)0x4d8ea0, 0, 0xa430);
  *(uint8_t *)(*(int *)0x4d8ea0 + 0x520e) = 0;
}

/* FUN_00194360 (0x194360)
 * qsort/bsort comparator. Two cdecl stack args are pointers to records.
 * Reads a signed int16 field at offset +0x10 of each record and orders
 * descending by that field: returns +1 when the second record's field is
 * strictly less than the first's (first sorts earlier), -1 otherwise. The
 * equal case also falls into -1, matching the original (cond*2 - 1) shape.
 */
int FUN_00194360(int param_1, int param_2)
{
  return (unsigned int)(*(short *)(param_2 + 0x10) <
                        *(short *)(param_1 + 0x10)) *
           2 +
         -1;
}

/* FUN_00194380 (0x194380)
 * Collision-BSP point query. Fetches the structure's bsp3d root element
 * (tag_block at param_1+0xb0, element 0, stride 0x60), locates the leaf that
 * contains point param_2 via bsp3d_find_leaf(root, node=0, point), then returns
 * the signed int16 field at +0x8 of the matching leaf element (tag_block at
 * param_1+0xe0, stride 0x10). Returns -1 on the 0xffffffff not-found sentinel.
 *
 * NOTE: Ghidra mis-groups the two calls. MSVC evaluates and pushes
 * bsp3d_find_leaf's 2nd arg (0) and 3rd arg (param_2) BEFORE the inner
 * tag_block_get_element call, so the decompiler folded them into
 * tag_block_get_element as a bogus 5-arg call and showed bsp3d_find_leaf with
 * a single arg. Both callees are proven 3-arg cdecl: 0x19b210 reads only
 * [ebp+8]/[ebp+0xc]/[ebp+0x10], and the third call site is a clean
 * 3-push / add esp,0xc. The nested call form reproduces the push interleave.
 * The leaf index has its high bit stripped (& 0x7fffffff) before use.
 */
int FUN_00194380(int param_1, void *param_2)
{
  void *leaf_element;
  unsigned int leaf;

  leaf = bsp3d_find_leaf(
    tag_block_get_element((void *)(param_1 + 0xb0), 0, 0x60), 0, param_2);
  if (leaf != 0xffffffff) {
    leaf_element = tag_block_get_element((void *)(param_1 + 0xe0),
                                         (int)(leaf & 0x7fffffff), 0x10);
    return (int)*(short *)((char *)leaf_element + 8);
  }
  return -1;
}

/* FUN_00195530 (0x195530)
 * Integer greater-than comparator, likely a qsort/bsearch comparison callback.
 * Two cdecl stack int args, bool/AL return. Returns true only when
 * param_1 > param_2 (the equal case returns false). The two-branch shape
 * (early-return false on param_2 > param_1, then param_2 < param_1) is the
 * original MSVC codegen shape (cmp param_2,param_1 / jle / xor al,al / setl al)
 * and is preserved verbatim; collapsing it to a single param_1 > param_2 would
 * change the emitted branch structure. VC71 recomputes the compare for the
 * trailing setl (clean-bool-via-edx idiom) where the original reused the
 * branch's flags directly, a ~3-insn small-function idiom gap (88.9% VC71).
 */
char FUN_00195530(int param_1, int param_2)
{
  if (param_2 > param_1) {
    return 0;
  }
  return param_2 < param_1;
}

/* FUN_001954d0 (0x1954d0) — readable C lift. */
void FUN_001954d0(void)
{
  build_structure_lens_flares(scenario_get());
}

/* FUN_00195550 (0x195550) — readable C lift (restored pre-naked). */
void FUN_00195550(short surface_count, int *out_indices, uint32_t *mask,
                  int out_surfaces)
{
  int *block;
  int scenario;
  short bit;
  short write_index;
  int surface_index;
  uint16_t *dst;
  uint16_t *elem;

  scenario = (int)scenario_get();
  block = (int *)(scenario + 0xf8);
  write_index = 0;
  surface_index = 0;
  if (0 < *(int *)(scenario + 0xf8)) {
    do {
      if (*mask == 0) {
        surface_index = surface_index + 0x20;
      } else {
        bit = 0;
        do {
          if (*block <= surface_index)
            break;
          if ((*mask & 1 << ((uint8_t)bit & 0x1f)) != 0) {
            elem = (uint16_t *)tag_block_get_element(block, surface_index, 6);
            if ((write_index < 0) || (surface_count <= write_index)) {
              display_assert(
                "surface_index_index>=0 && surface_index_index<surface_count",
                "c:\\halo\\SOURCE\\structures\\structure_render.c", 0x1a5,
                true);
              system_exit(-1);
            }
            *out_indices = surface_index;
            out_indices = out_indices + 1;
            dst = (uint16_t *)(out_surfaces + write_index * 6);
            dst[0] = elem[0];
            dst[1] = elem[1];
            dst[2] = elem[2];
            write_index = write_index + 1;
          }
          bit = bit + 1;
          surface_index = surface_index + 1;
        } while (bit < 0x20);
      }
      mask = mask + 1;
    } while (surface_index < *block);
  }
}



/* FUN_00195650 (0x195650) — readable C lift (restored pre-naked). */
void FUN_00195650(void *out, int *indices, short count)
{
  int scenario;
  int *block;
  uint16_t *elem;
  uint16_t *dst;
  int remaining;

  scenario = (int)scenario_get();
  FUN_00091ef0(indices, count, (int (*)(int, int))FUN_00195530);
  if (0 < count) {
    block = (int *)(scenario + 0xf8);
    dst = (uint16_t *)out;
    remaining = (unsigned short)count;
    do {
      elem = (uint16_t *)tag_block_get_element(block, *indices, 6);
      dst[0] = elem[0];
      dst[1] = elem[1];
      dst[2] = elem[2];
      indices = indices + 1;
      dst = dst + 3;
      remaining = remaining - 1;
    } while (remaining != 0);
  }
}



/* FUN_001956d0 (0x1956d0) — readable C lift (restored pre-naked). */
int FUN_001956d0(void *param_1, void *param_2, short param_3)
{
  int handle;
  void *triangles;

  scenario_get();
  if (0 < param_3) {
    handle = rasterizer_widget_submit((int)param_3);
    if (handle != -1) {
      triangles = rasterizer_widget_begin(handle);
      if (triangles == NULL) {
        display_assert("triangles",
                       "c:\\halo\\SOURCE\\structures\\structure_render.c", 0x1e6,
                       true);
        system_exit(-1);
      }
      if (param_2 == NULL) {
        FUN_00195650(triangles, (int *)param_1, param_3);
        rasterizer_widget_set_texture(handle);
        return handle;
      }
      FUN_00195550(param_3, (int *)param_1, (unsigned int *)param_2,
                   (int)triangles);
      rasterizer_widget_set_texture(handle);
      return handle;
    }
    if (*(short *)0x32bd60 != 0) {
      error(2, "unable to allocate dynamic structure triangles.");
      *(short *)0x32bd60 = 0;
    }
  }
  return -1;
}



/* FUN_001959f0 (0x1959f0)
 *
 * Structure render-triangle build entry.  Under the profiler gate
 * (0x449ef1 && 0x3275c8), brackets the build call in
 * profile_enter/exit_private("render_structure_build_triangle").  Builds the
 * triangle set via FUN_001956d0(&0x5937d4, &0x5137d0), stashing the returned
 * bsp/structure index at 0x4d8eb4 and a validity flag (index != -1) at
 * 0x4d8eb0.  Then, when the two staged indices (0x3275b8, 0x3275bc) are in
 * range against the scenario tag-block counts at scenario+0x270 / scenario+
 * 0x27c, replays them through the tag-block iterators FUN_00191ff0 /
 * FUN_00191e90 (both operate on scenario+0x26c).  When the rebuild-all byte
 * 0x505703 is set, walks every element of the scenario+0x27c tag-block
 * (stride 0x18, element pointer discarded) and reissues FUN_00191e90 for each.
 * Finally clears 0x4d8eb8 and snapshots the forward vector (3 dwords) from
 * *(0x31fc38) into 0x4d8ebc/ec0/ec4.
 *
 * Confirmed from decompile at 0x1959f0:
 *   - scenario_get() 0-arg; scenario+0x270 guards 0x3275b8, +0x27c guards
 *     0x3275bc and the rebuild loop (element count at *(scenario+0x27c)).
 *   - FUN_001956d0 returns int (EAX -> 0x4d8eb4), two pointer args.
 *   - loop sets index=0 before the count check (preserved), stride 0x18.
 *   - forward-vector snapshot copied as raw dwords (no FPU).
 * All calls cdecl, args pushed right-to-left.
 */
void FUN_001959f0(void)
{
  int scenario;
  int index;
  char *fwd;

  scenario = (int)scenario_get();

  if (*(char *)0x449ef1 != 0 && *(char *)0x3275c8 != 0) {
    profile_enter_private((void *)0x3275c0);
  }
  /* 0x195a18: MOV ESI,[0x5937d0] before the call — count is an implicit
   * @<esi> arg (callee tests SI). */
  *(int *)0x4d8eb4 =
    FUN_001956d0((void *)0x5937d4, (void *)0x5137d0, *(int16_t *)0x5937d0);
  if (*(char *)0x449ef1 != 0 && *(char *)0x3275c8 != 0) {
    profile_exit_private((void *)0x3275c0);
  }
  *(char *)0x4d8eb0 = (char)(*(int *)0x4d8eb4 != -1);

  if (-1 < *(int *)0x3275b8 && *(int *)0x3275b8 < *(int *)(scenario + 0x270)) {
    FUN_00191ff0(scenario + 0x26c, *(int *)0x3275b8);
  }
  if (-1 < *(int *)0x3275bc && *(int *)0x3275bc < *(int *)(scenario + 0x27c)) {
    FUN_00191e90(scenario + 0x26c, *(int *)0x3275bc);
  }

  if (*(char *)0x505703 != 0) {
    index = 0;
    if (0 < *(int *)(scenario + 0x27c)) {
      do {
        tag_block_get_element((void *)(scenario + 0x27c), index, 0x18);
        FUN_00191e90(scenario + 0x26c, index);
        index = index + 1;
      } while (index < *(int *)(scenario + 0x27c));
    }
  }

  *(int *)0x4d8eb8 = 0;
  fwd = *(char **)0x31fc38;
  *(int *)0x4d8ebc = *(int *)fwd;
  *(int *)0x4d8ec0 = *(int *)(fwd + 4);
  *(int *)0x4d8ec4 = *(int *)(fwd + 8);
}

/* FUN_00195b10 (0x195b10)
 *
 * render_structure_lightmaps: thin render-orchestration wrapper (string ref
 * "render_structure_lightmaps" @0x327bb8).  Profiles the scope, and when the
 * map has a valid lightmap (byte at 0x4d8eb0 != 0) it briefly forces the 16-bit
 * word at 0x3256b0 to 1 -- only when the scenario has no bsp switch pending
 * (scenario+0xc == -1) and the word is currently 0 -- brackets a rasterizer
 * setup/teardown pair (FUN_0017cc00 / FUN_0017cc40) around the per-surface
 * lightmap draw walk (FUN_00195790), then restores the saved low word.
 *
 * Notes from disasm/decompile:
 *  - 0x3256b0 is a 16-bit word: the save reads the full dword (MOV ESI,dword),
 *    but the conditional set and the restore are word-sized (MOV word,1 /
 *    MOV word,SI), and the "==0" test is a word compare (CMP word,0).  Do NOT
 *    transcribe as a 32-bit store.
 *  - FUN_00195790 takes an @eax pointer (=0x5937d4, surface->material offset
 *    table) plus 6 stack args (confirmed: its decompile uses int *in_EAX as
 *    in_EAX + param_1).  arg1 is the zero-extended uint16 at 0x5937d0.
 */
void FUN_00195b10(void)
{
  int scenario;
  int saved_flag;

  if (*(char *)0x449ef1 != 0 && *(char *)0x327bc0 != 0) {
    profile_enter_private((void *)0x327bb8);
  }

  saved_flag = *(int *)0x3256b0;

  if (*(char *)0x4d8eb0 != 0) {
    scenario = (int)scenario_get();
    if (*(int *)(scenario + 0xc) == -1 && *(short *)0x3256b0 == 0) {
      *(short *)0x3256b0 = 1;
    }
    FUN_0017cc00();
    FUN_00195790((int *)0x5937d4, *(unsigned short *)0x5937d0, *(int *)0x4d8eb4,
                 (void *)FUN_0017cc10, (void *)FUN_0017cc20, (void *)0x17cc30,
                 0);
    FUN_0017cc40();
    *(short *)0x3256b0 = (short)saved_flag;
  }

  if (*(char *)0x449ef1 != 0 && *(char *)0x327bc0 != 0) {
    profile_exit_private((void *)0x327bb8);
  }
}

/* FUN_00195bc0 (0x195bc0)
 *
 * render_structure_diffuse_texture: thin render-orchestration wrapper (string
 * ref "render_structure_diffuse_texture" @0x3281b0).  Profiles the scope, and
 * when the map has a valid diffuse/lightmap pass (byte at 0x4d8eb0 != 0) it
 * brackets a scope enter/exit pair (FUN_00162790 / FUN_00160950, reached in the
 * original via 1-instr JMP thunks at 0x17cd20/0x17cd40) around the per-surface
 * diffuse-texture draw walk (FUN_00195790).
 *
 * Notes from disasm/decompile:
 *  - FUN_00195790 takes an @eax pointer (=0x5937d4, surface->material offset
 *    table) plus 6 stack args.  arg1 (surface_count) is the zero-extended
 *    uint16 at 0x5937d0 (XOR ECX,ECX; MOV CX,word ptr); arg2
 *    (lightmap_pass_index) is the dword at 0x4d8eb4.  This variant has a single
 *    callback: FUN_0017cd30 is the 5th param (surface_draw_cb);
 *    material_begin_cb / pass_end_cb / param_7 are all 0.  (Confirmed via push
 *    order: ADD ESP,0x18 = 6 stack dwords.)
 */
void FUN_00195bc0(void)
{
  if (*(char *)0x449ef1 != 0 && *(char *)0x3281b8 != 0) {
    profile_enter_private((void *)0x3281b0);
  }

  if (*(char *)0x4d8eb0 != 0) {
    FUN_00162790();
    FUN_00195790((int *)0x5937d4, *(unsigned short *)0x5937d0, *(int *)0x4d8eb4,
                 (void *)0, (void *)FUN_0017cd30, (void *)0, 0);
    FUN_00160950();
  }

  if (*(char *)0x449ef1 != 0 && *(char *)0x3281b8 != 0) {
    profile_exit_private((void *)0x3281b0);
  }
}

/* FUN_00195c40 (0x195c40)
 *
 * Sibling of FUN_00195b10: when the map has a valid lightmap pass (byte at
 * 0x4d8eb0 != 0), briefly forces the 16-bit word at 0x3256b0 to 1 -- only when
 * the scenario has no bsp switch pending (scenario+0xc == -1) and the word is
 * currently 0 -- brackets a rasterizer setup/teardown pair (thunks 0x17cda0 /
 * 0x17cde0 -> FUN_00163c40 / FUN_001609a0) around the per-surface draw walk
 * (FUN_00195790), then restores the saved low word.  Unlike FUN_00195b10 this
 * variant has no profiler scope.
 *
 * Confirmed from disassembly at 0x195c40:
 *  - 0x3256b0 is a 16-bit word: the save reads the full dword
 *    (MOV ESI,dword ptr [0x3256b0]), but the conditional set and the restore
 *    are word-sized (MOV word,1 / MOV word,SI), and the "==0" test is a word
 *    compare (CMP word,0).  The save/restore live inside the gate block (the
 *    MOV ESI read is after the JZ), not before it.  Do NOT emit a 32-bit store.
 *  - FUN_00195790 takes an @eax pointer (MOV EAX,0x5937d4 = surface->material
 *    offset table) plus 6 stack args; ADD ESP,0x18 = 6 stack dwords.  Push
 *    order (first push = last C arg): 0 (param_7), 0x17cdd0 (pass_end_cb),
 *    0x17cdc0 (surface_draw_cb), 0x17cdb0 (material_begin_cb), *0x4d8eb4
 *    (lightmap_pass_index), uint16 @0x5937d0 (surface_count).  0x17cdd0 is a
 *    bare label, passed as a raw address.
 */
void FUN_00195c40(void)
{
  int scenario;
  int saved_flag;

  if (*(char *)0x4d8eb0 != 0) {
    saved_flag = *(int *)0x3256b0;
    scenario = (int)scenario_get();
    if (*(int *)(scenario + 0xc) == -1 && *(short *)0x3256b0 == 0) {
      *(short *)0x3256b0 = 1;
    }
    FUN_0017cda0();
    FUN_00195790((int *)0x5937d4, *(unsigned short *)0x5937d0, *(int *)0x4d8eb4,
                 (void *)FUN_0017cdb0, (void *)FUN_0017cdc0, (void *)0x17cdd0,
                 0);
    FUN_0017cde0();
    *(short *)0x3256b0 = (short)saved_flag;
  }
}

/* FUN_00195cb0 (0x195cb0)
 *
 * Sibling of FUN_00195af0: when the map has a valid lightmap pass (byte at
 * 0x4d8eb0 != 0), brackets a setup/teardown pair (1-instr JMP thunks
 * FUN_0017cdf0 -> FUN_001643e0 / FUN_0017ce30 -> FUN_00160bc0) around the
 * per-surface draw walk (FUN_00195790).  This is the simplest variant: no
 * profiler scope, no scenario/bsp-switch check, no 0x3256b0 word forcing.
 *
 * Notes from disasm (0x195cb0):
 *  - FUN_00195790 takes an @eax pointer (MOV EAX,0x5937d4 = surface->material
 *    offset table) plus 6 stack args.  Push order (first push = last C arg):
 *    0 (param_7), 0x17ce20 (pass_end_cb, bare label), FUN_0017ce10
 *    (surface_draw_cb), FUN_0017ce00 (material_begin_cb), *0x4d8eb4
 *    (lightmap_pass_index), uint16 @0x5937d0 (surface_count, XOR ECX,ECX;
 *    MOV CX,word ptr).  ADD ESP,0x18 = 6 stack dwords confirms.
 *  - The teardown is emitted in the original as a tail JMP 0x17ce30.
 */
void FUN_00195cb0(void)
{
  if (*(char *)0x4d8eb0 != 0) {
    FUN_0017cdf0();
    FUN_00195790((int *)0x5937d4, *(unsigned short *)0x5937d0, *(int *)0x4d8eb4,
                 (void *)FUN_0017ce00, (void *)FUN_0017ce10, (void *)0x17ce20,
                 0);
    FUN_0017ce30();
  }
}

/* FUN_00195d00 (0x195d00)
 *
 * Sibling of FUN_00195d40 (render_structure_reflections): when the map has a
 * valid reflection/lightmap pass (byte at 0x4d8eb0 != 0), brackets a scope
 * enter/exit pair (FUN_0017ce40 / FUN_0017ce60, 1-instr JMP thunks forwarding
 * to FUN_00160bd0 / FUN_00160be0) around the per-surface draw walk
 * (FUN_00195790).  No profiler scope.
 *
 * Confirmed from disassembly at 0x195d00:
 *  - Gate: MOV AL,[0x4d8eb0]; TEST AL,AL; JZ end.  When the byte is 0 the
 *    function does nothing.
 *  - FUN_00195790 takes an @eax pointer (MOV EAX,0x5937d4 = surface->material
 *    offset table -- passed as an ADDRESS, not a deref) plus 6 stack args;
 *    ADD ESP,0x18 = 6 stack dwords.  Push order (first push = last C arg):
 *    0 (param_7), 0 (pass_end_cb), 0x17ce50 (surface_draw_cb), 0
 *    (material_begin_cb), *0x4d8eb4 (lightmap_pass_index), zero-extended uint16
 *    @0x5937d0 (surface_count, XOR ECX,ECX / MOV CX -> unsigned short read).
 *  - Two distinct globals: uint16 count @0x5937d0 vs int[] offsets @0x5937d4.
 *  - The teardown FUN_0017ce60 is reached via a tail-call JMP in the original.
 */
void FUN_00195d00(void)
{
  if (*(char *)0x4d8eb0 != 0) {
    FUN_0017ce40();
    FUN_00195790((int *)0x5937d4, *(unsigned short *)0x5937d0, *(int *)0x4d8eb4,
                 (void *)0, (void *)FUN_0017ce50, (void *)0, 0);
    FUN_0017ce60();
  }
}

/* FUN_00195d40 (0x195d40)
 *
 * render_structure_reflections: thin render-orchestration wrapper (string ref
 * "render_structure_reflections" @0x3287a8).  Profiles the scope, and when the
 * map has a valid reflection/lightmap pass (byte at 0x4d8eb0 != 0) it brackets
 * a scope enter/exit pair (FUN_00160bf0 / FUN_00160c00, reached in the original
 * via 1-instr JMP thunks at 0x17ce70/0x17ce90) around the per-surface
 * reflection draw walk (FUN_00195790).
 *
 * Notes from disasm/decompile:
 *  - FUN_00195790 takes an @eax pointer (=0x5937d4, surface->material offset
 *    table) plus 6 stack args.  arg1 (surface_count) is the zero-extended
 *    uint16 at 0x5937d0 (MOV CX,word ptr); arg2 (lightmap_pass_index) is the
 *    dword at 0x4d8eb4.  This variant has a single callback: FUN_0017ce80 is
 *    the 5th param (surface_draw_cb); material_begin_cb / pass_end_cb / param_7
 *    are all 0.  (Confirmed via push order: ADD ESP,0x18 = 6 stack dwords.)
 */
void FUN_00195d40(void)
{
  if (*(char *)0x449ef1 != 0 && *(char *)0x3287b0 != 0) {
    profile_enter_private((void *)0x3287a8);
  }

  if (*(char *)0x4d8eb0 != 0) {
    FUN_00160bf0();
    FUN_00195790((int *)0x5937d4, *(unsigned short *)0x5937d0, *(int *)0x4d8eb4,
                 (void *)0, (void *)FUN_0017ce80, (void *)0, 0);
    FUN_00160c00();
  }

  if (*(char *)0x449ef1 != 0 && *(char *)0x3287b0 != 0) {
    profile_exit_private((void *)0x3287a8);
  }
}

/* FUN_00195dc0 (0x195dc0)
 *
 * render_structure_transparent_geo: thin render-orchestration wrapper (string
 * ref "render_structure_transparent_geo" @0x328da0).  Profiles the scope, and
 * when the map has a valid lightmap/material pass (byte at 0x4d8eb0 != 0) it
 * brackets a scope enter/exit pair (thunks 0x17cea0 / 0x17cec0 forwarding to
 * FUN_00160c10 / FUN_00160c20) around the per-surface transparent-geometry draw
 * walk (FUN_00195790).
 *
 * Confirmed from disassembly at 0x195dc0:
 *  - Outer profiler scope: MOV AL,[0x449ef1]; TEST/JZ; MOV AL,[0x328da8];
 *    TEST/JZ around PUSH 0x328da0; CALL profile_enter_private; ADD ESP,4.
 *    Mirrored at the tail with profile_exit_private (PUSH 0x328da0; CALL; POP).
 *  - Middle block gate: MOV AL,[0x4d8eb0]; TEST AL,AL; JZ end.
 *  - FUN_00195790 takes an @eax pointer (MOV EAX,0x5937d4 = surface->material
 *    offset table -- passed as an ADDRESS, not a deref) plus 6 stack args;
 *    ADD ESP,0x18 = 6 stack dwords.  Push order (first push = last C arg):
 *    0x17ceb0 (param_7 -- fn ptr FUN_0017ceb0), 0 (pass_end_cb), 0
 *    (surface_draw_cb), 0 (material_begin_cb), *0x4d8eb4 (lightmap_pass_index),
 *    zero-extended uint16 @0x5937d0 (surface_count, XOR ECX,ECX / MOV CX).
 *  - Two distinct globals: uint16 count @0x5937d0 vs int[] offsets @0x5937d4.
 *    The lone callback (FUN_0017ceb0) rides in the param_7 slot, unlike the
 *    sibling reflection/lightmap passes which use surface_draw_cb.
 * All calls cdecl, args pushed right-to-left.
 */
void FUN_00195dc0(void)
{
  if (*(char *)0x449ef1 != 0 && *(char *)0x328da8 != 0) {
    profile_enter_private((void *)0x328da0);
  }

  if (*(char *)0x4d8eb0 != 0) {
    FUN_0017cea0();
    FUN_00195790((int *)0x5937d4, *(unsigned short *)0x5937d0, *(int *)0x4d8eb4,
                 (void *)0, (void *)0, (void *)0, (int)FUN_0017ceb0);
    FUN_0017cec0();
  }

  if (*(char *)0x449ef1 != 0 && *(char *)0x328da8 != 0) {
    profile_exit_private((void *)0x328da0);
  }
}

/* FUN_00195e40 (0x195e40)
 *
 * render_structure_fog: thin render-orchestration wrapper (string ref
 * "render_structure_fog" @0x329398).  Profiles the scope, and when the map has
 * a valid lightmap/material pass (byte at 0x4d8eb0 != 0) it brackets a
 * rasterizer setup/teardown pair (thunks 0x17ced0 / 0x17cef0 forwarding to
 * FUN_00166400 / FUN_00165dd0) around the per-surface fog draw walk
 * (FUN_00195790).  Simpler than FUN_00195b10: no scenario_get / 0x3256b0
 * save-restore.
 *
 * Confirmed from disassembly at 0x195e40:
 *  - Outer profiler scope: MOV AL,[0x449ef1]; TEST/JZ; MOV AL,[0x3293a0];
 *    TEST/JZ around PUSH 0x329398; CALL profile_enter_private; ADD ESP,4.
 *    Mirrored at the tail with profile_exit_private (PUSH 0x329398; CALL; POP).
 *  - Middle block gate: MOV AL,[0x4d8eb0]; TEST AL,AL; JZ end.
 *  - FUN_0017ced0 (rasterizer setup) before the walk, FUN_0017cef0 (teardown)
 *    after; both no-arg thunks.
 *  - FUN_00195790 takes an @eax pointer (MOV EAX,0x5937d4 = surface->material
 *    offset table -- passed as an ADDRESS, not a deref) plus 6 stack args;
 *    ADD ESP,0x18 = 6 stack dwords.  Push order (first push = last C arg):
 *    0 (param_7), 0 (pass_end_cb), 0x17cee0 (surface_draw_cb FUN_0017cee0), 0
 *    (material_begin_cb), *0x4d8eb4 (lightmap_pass_index), zero-extended uint16
 *    @0x5937d0 (surface_count, XOR ECX,ECX / MOV CX read).
 *  - Two distinct globals: uint16 count @0x5937d0 vs int[] offsets @0x5937d4.
 * All calls cdecl, args pushed right-to-left.
 */
void FUN_00195e40(void)
{
  if (*(char *)0x449ef1 != 0 && *(char *)0x3293a0 != 0) {
    profile_enter_private((void *)0x329398);
  }

  if (*(char *)0x4d8eb0 != 0) {
    FUN_0017ced0();
    FUN_00195790((int *)0x5937d4, *(unsigned short *)0x5937d0, *(int *)0x4d8eb4,
                 (void *)0, (void *)FUN_0017cee0, (void *)0, 0);
    FUN_0017cef0();
  }

  if (*(char *)0x449ef1 != 0 && *(char *)0x3293a0 != 0) {
    profile_exit_private((void *)0x329398);
  }
}

/* FUN_00195ec0 (0x195ec0)
 *
 * Two-pass structure lightmap draw driver.  Sibling of FUN_00195b10 /
 * FUN_00195c40 but with no scenario_get / 0x3256b0 save-restore: when the map
 * has a valid lightmap pass (byte at 0x4d8eb0 != 0) it runs the per-surface
 * draw walk (FUN_00195790) twice, once per pass -- FUN_0017cf10(0) then
 * FUN_0017cf10(1) select the pass index -- with a fog emit (FUN_00167920)
 * after each walk.
 *
 * Confirmed from disassembly at 0x195ec0 (delinked/functions/00195ec0.obj):
 *  - Gate: MOV AL,[0x4d8eb0]; TEST AL,AL; JZ end.
 *  - FUN_0017cf10 takes one int arg (PUSH 0 / PUSH 1).  Stack cleanup is
 *    deferred to a single ADD ESP,0x38 at the end (0x38 = 56 = 4 + 24 + 4 + 24:
 *    the two cf10 args plus two 6-stack-arg FUN_00195790 calls).
 *  - FUN_00195790 takes an @eax pointer (MOV EAX,0x5937d4 = surface->material
 *    offset table) plus 6 stack args.  Push order (first push = last C arg):
 *    0 (param_7), 0 (pass_end_cb), 0x17cf20 (surface_draw_cb), 0
 *    (material_begin_cb), *0x4d8eb4 (lightmap_pass_index), zero-extended uint16
 *    @0x5937d0 (surface_count, XOR ECX,ECX / MOV CX read).
 *  - Two distinct globals: uint16 count @0x5937d0 vs int[] offsets @0x5937d4.
 *  - FUN_0017cf20 is passed as a raw callback address, not called here.
 *  - FUN_00167920 (fog emit) takes no args.
 */
void FUN_00195ec0(void)
{
  if (*(char *)0x4d8eb0 != 0) {
    FUN_0017cf10(0);
    FUN_00195790((int *)0x5937d4, *(unsigned short *)0x5937d0, *(int *)0x4d8eb4,
                 0, (void *)FUN_0017cf20, 0, 0);
    FUN_00167920();
    FUN_0017cf10(1);
    FUN_00195790((int *)0x5937d4, *(unsigned short *)0x5937d0, *(int *)0x4d8eb4,
                 0, (void *)FUN_0017cf20, 0, 0);
    FUN_00167920();
  }
}

/* FUN_00195f30 (0x195f30)
 *
 * render_structure_specular_lights: structure specular-light render entry
 * (string refs "render_structure_specular_lights" @0x329f88 and the outer
 * scope string @0x329990).  Allocates a 0x4000-byte surface-material scratch
 * table on the stack, then either builds a per-gel surface set into it
 * (gel_buffer != 0) or falls back to the globally-built structure surface
 * table at 0x5937d0/0x5937d4 (gel_buffer == 0).  When the resulting
 * lightmap/material index is valid (!= -1), sets up the object, walks the
 * surfaces through FUN_00195790 with a single surface-draw callback
 * (FUN_0017cd70), ends the rasterizer HUD scope, and (only on the gel path)
 * commits the tint factor.  The whole body is bracketed by the outer profiler
 * scope (0x449ef1 && 0x329998); the draw/setup section by the inner scope
 * (0x449ef1 && 0x329f90).
 *
 * Confirmed from disassembly at 0x195f30:
 *   - Frame: _chkstk(0x4004) -> 0x4000-byte scratch @[EBP-0x4004]; its address
 *     is stashed to [EBP-4] in the prologue (used later as the FUN_00195790
 *     @eax argument), and overwritten to the global 0x5937d4 on the fallback
 *     path.  Callee-saved EBX/ESI/EDI hold gel_buffer / surface_count /
 *     material_index across the body.
 *   - gel path: FUN_00197e90(buffer, 0x1000, position, radius, 0, 0, 0,
 *     gel_count, gel_buffer) returns a short (MOVSX AX -> ESI = surface_count);
 *     FUN_001956d0(buffer, 0) returns int (EAX -> EDI = material_index).
 *     Shared ADD ESP,0x2C = 9+2 stack args.
 *   - fallback: material_index = *(int*)0x4d8eb4, surface_count =
 *     (short)*(short*)0x5937d0 (MOVSX), material_offsets = 0x5937d4.
 *   - draw section: FUN_0017cd60(object_handle) [1 arg]; FUN_00195790 takes
 *     @eax = material_offsets ([EBP-4]) plus 6 stack args (surface_count,
 *     material_index, 0, FUN_0017cd70 surface-draw cb, 0, 0) -- shared
 *     ADD ESP,0x1C = 1+6 stack args; _rasterizer_hud_end() via 1-instr JMP
 *     thunk @0x17cd80 -> 0x160970; rasterizer_widget_set_tint_factor gated on
 *     gel_buffer != 0.
 *   - radius is a float passed by value (raw dword push); position is float*.
 * All calls cdecl, args pushed right-to-left.
 */
void FUN_00195f30(int object_handle, float *position, float radius,
                  int gel_count, int gel_buffer)
{
  char buffer[0x4000];
  int *material_offsets;
  short surface_count;
  int material_index;

  material_offsets = (int *)buffer;

  if (*(char *)0x449ef1 != 0 && *(char *)0x329998 != 0) {
    profile_enter_private((void *)0x329990);
  }

  if (gel_buffer != 0) {
    surface_count = FUN_00197e90(buffer, 0x1000, position, radius, 0, 0, 0,
                                 gel_count, gel_buffer);
    material_index = FUN_001956d0(buffer, (void *)0, surface_count);
  } else {
    material_index = *(int *)0x4d8eb4;
    surface_count = *(short *)0x5937d0;
    material_offsets = (int *)0x5937d4;
  }

  if (material_index != -1) {
    if (*(char *)0x449ef1 != 0 && *(char *)0x329f90 != 0) {
      profile_enter_private((void *)0x329f88);
    }
    FUN_0017cd60(object_handle);
    FUN_00195790(material_offsets, surface_count, material_index, 0,
                 (void *)FUN_0017cd70, 0, 0);
    _rasterizer_hud_end();
    if (gel_buffer != 0) {
      rasterizer_widget_set_tint_factor(material_index);
    }
    if (*(char *)0x449ef1 != 0 && *(char *)0x329f90 != 0) {
      profile_exit_private((void *)0x329f88);
    }
  }

  if (*(char *)0x449ef1 != 0 && *(char *)0x329998 != 0) {
    profile_exit_private((void *)0x329990);
  }
}

/* FUN_00196060 (0x196060)
 *
 * render_structure_diffuse_lights: structure diffuse-light render entry.  The
 * diffuse sibling of FUN_00195f30 (specular): byte-identical shape, differing
 * only in the diffuse-specific profiler scopes, object-setup/draw callbacks,
 * and HUD-end thunk.  Allocates a 0x4000-byte surface-material scratch table on
 * the stack, then either builds a per-gel surface set into it (gel_buffer != 0)
 * or falls back to the globally-built structure surface table at
 * 0x5937d0/0x5937d4 (gel_buffer == 0).  When the resulting lightmap/material
 * index is valid (!= -1), sets up the object, walks the surfaces through
 * FUN_00195790 with a single surface-draw callback (FUN_0017cc70), commits the
 * tint factor (gel path only), then ends the rasterizer HUD scope.  The whole
 * body is bracketed by the outer profiler scope (0x449ef1 && 0x32a588); the
 * draw/setup section by the inner scope (0x449ef1 && 0x32ab80).
 *
 * Confirmed from disassembly at 0x196060:
 *   - Frame: _chkstk(0x4004) -> 0x4000-byte scratch @[EBP-0x4004]; its address
 *     is stashed to [EBP-4] in the prologue (used later as the FUN_00195790
 *     @eax argument), and overwritten to the global 0x5937d4 on the fallback
 *     path.  Callee-saved EBX/ESI/EDI hold gel_buffer / surface_count /
 *     material_index across the body.
 *   - gel path: FUN_00197e90(buffer, 0x1000, position, radius, 0, 0, 0,
 *     gel_count, gel_buffer) returns a short (MOVSX AX -> ESI = surface_count);
 *     FUN_001956d0(buffer, 0) returns int (EAX -> EDI = material_index).
 *     Shared ADD ESP,0x2C = 9+2 stack args.
 *   - fallback: material_index = *(int*)0x4d8eb4, surface_count =
 *     (short)*(short*)0x5937d0 (MOVSX), material_offsets = 0x5937d4.
 *   - draw section: FUN_0017cc60(object_handle) [1 arg]; FUN_00195790 takes
 *     @eax = material_offsets ([EBP-4]) plus 6 stack args (surface_count,
 *     material_index, 0, FUN_0017cc70 surface-draw cb, 0, 0) -- shared
 *     ADD ESP,0x1C = 1+6 stack args; rasterizer_widget_set_tint_factor
 *     (@0x196139) gated on gel_buffer != 0; FUN_00160930() (HUD end) via
 *     1-instr JMP thunk @0x17cc80.
 *   - radius is a float passed by value (raw dword push); position is float*.
 * All calls cdecl, args pushed right-to-left.
 */
void FUN_00196060(int object_handle, float *position, float radius,
                  int gel_count, int gel_buffer)
{
  char buffer[0x4000];
  int *material_offsets;
  short surface_count;
  int material_index;

  material_offsets = (int *)buffer;

  if (*(char *)0x449ef1 != 0 && *(char *)0x32a588 != 0) {
    profile_enter_private((void *)0x32a580);
  }

  if (gel_buffer != 0) {
    surface_count = FUN_00197e90(buffer, 0x1000, position, radius, 0, 0, 0,
                                 gel_count, gel_buffer);
    material_index = FUN_001956d0(buffer, (void *)0, surface_count);
  } else {
    material_index = *(int *)0x4d8eb4;
    surface_count = *(short *)0x5937d0;
    material_offsets = (int *)0x5937d4;
  }

  if (material_index != -1) {
    if (*(char *)0x449ef1 != 0 && *(char *)0x32ab80 != 0) {
      profile_enter_private((void *)0x32ab78);
    }
    FUN_0017cc60(object_handle);
    FUN_00195790(material_offsets, surface_count, material_index, 0,
                 (void *)FUN_0017cc70, 0, 0);
    if (gel_buffer != 0) {
      rasterizer_widget_set_tint_factor(material_index);
    }
    FUN_00160930();
    if (*(char *)0x449ef1 != 0 && *(char *)0x32ab80 != 0) {
      profile_exit_private((void *)0x32ab78);
    }
  }

  if (*(char *)0x449ef1 != 0 && *(char *)0x32a588 != 0) {
    profile_exit_private((void *)0x32a580);
  }
}

/*
 * FUN_00196190 (0x196190) — structures.obj
 *
 * render_structure_shadows: structure shadow render entry.  Sibling of
 * FUN_00196060 (diffuse lights) / FUN_00195f30 (specular): identical shape, but
 * with shadow-specific profiler scopes, NO per-gel branch (always builds the
 * surface set from the passed center/radius/bounds/count/planes), a single
 * surface-draw callback (FUN_0017ccf0), and rasterizer_widget_set_tint_factor
 * as the post-draw thunk (no HUD-end call).  Allocates a 0x4000-byte
 * surface-material scratch table on the stack, builds the shadow surface set
 * via FUN_00197e90, resolves the lightmap/pass index via FUN_001956d0, and when
 * valid (!= -1) walks the surfaces through FUN_00195790.  Outer profiler scope:
 * 0x449ef1 && 0x32b178 ("render_structure_shadows" @0x32b170); draw scope:
 * 0x449ef1 && 0x32b770 ("render_structure_shadows_draw" @0x32b768).
 *
 * Confirmed from disassembly at 0x196190 (delinked obj):
 *   - Frame: _chkstk(0x4000) -> 0x4000-byte scratch @[EBP-0x4000]. Callee-saved
 *     ESI/EDI hold surface_count / pass_index across the body (EBX unused; no
 *     gel branch).  The PUSH ESI / PUSH EDI scheduled after the outer
 *     profile_enter are register SAVES, not call arguments (popped at
 * epilogue); confirmed by ADD ESP,0x2C == 9+2 stack args cleaning both calls
 * below.
 *   - FUN_00197e90(buffer, 0x1000, center, radius, bounds, count, planes, 0, 0)
 *     returns short (MOVSX AX -> ESI = surface_count); FUN_001956d0(buffer, 0)
 *     returns int (EAX -> EDI = pass_index).  Skip draw when pass_index == -1.
 *   - draw section: FUN_00195790 @eax = buffer + 6 stack args (surface_count,
 *     pass_index, 0, FUN_0017ccf0 surface-draw cb, 0, 0) [the 5-byte PUSH at
 *     +0x95 is a reloc-stripped PUSH 0x17ccf0]; then
 *     rasterizer_widget_set_tint_factor(pass_index).  ADD ESP,0x1C == 6+1 args.
 *   - center/bounds/planes are pointers passed through as dwords; radius is a
 *     float by value.  All calls cdecl, args pushed right-to-left.
 */
void FUN_00196190(float *center, float radius_x4, float *bounds6, int count,
                  float *planes6)
{
  char buffer[0x4000];
  short surface_count;
  int pass_index;

  if (*(char *)0x449ef1 != 0 && *(char *)0x32b178 != 0) {
    profile_enter_private((void *)0x32b170);
  }

  surface_count = FUN_00197e90(buffer, 0x1000, center, radius_x4, (int)bounds6,
                               count, (int)planes6, 0, 0);
  pass_index = FUN_001956d0(buffer, (void *)0, surface_count);

  if (pass_index != -1) {
    if (*(char *)0x449ef1 != 0 && *(char *)0x32b770 != 0) {
      profile_enter_private((void *)0x32b768);
    }
    FUN_00195790((int *)buffer, surface_count, pass_index, 0,
                 (void *)FUN_0017ccf0, 0, 0);
    rasterizer_widget_set_tint_factor(pass_index);
    if (*(char *)0x449ef1 != 0 && *(char *)0x32b770 != 0) {
      profile_exit_private((void *)0x32b768);
    }
  }

  if (*(char *)0x449ef1 != 0 && *(char *)0x32b178 != 0) {
    profile_exit_private((void *)0x32b170);
  }
}

void structure_runtime_decals_initialize(void)
{
  *(void **)0x4d8ec8 = game_state_malloc("structure decals", 0, 4);
  if (*(void **)0x4d8ec8 == NULL) {
    display_assert("structure_decals_globals",
                   "c:\\halo\\SOURCE\\structures\\structure_runtime_decals.c",
                   0x1c, true);
    system_exit(-1);
  }
}

/* noinline: original build had this in a separate TU
 * (structure_runtime_decals.c), so callers in structures.c emit real CALLs —
 * keep that shape under VC71 /O2. */
__declspec(noinline) void structure_runtime_decals_initialize_for_new_map(void)
{
  uint8_t *runtime_decal_globals = *(uint8_t **)0x4d8ec8;

  if (runtime_decal_globals == NULL) {
    display_assert("structure_decals_globals",
                   "c:\\halo\\SOURCE\\structures\\structure_runtime_decals.c",
                   0x24, true);
    system_exit(-1);
  }

  *runtime_decal_globals = 0;
}

/*
 * FUN_00196330  (0x196330) — structures.obj
 *
 * Sweeps the current scenario's structure-cluster tag block and deletes
 * permanent decals from clusters flagged for removal.  Guarded by
 * scenario+0x258 (an int) being non-zero.  The cluster tag block has its
 * count word at scenario+0x134 and element stride 0x68.  For each cluster
 * whose int16 field at +0xc is (!= -1) AND whose int16 field at +0xe is
 * (!= 0), decals_delete_permanent_from_cluster is called with the loop index.
 *
 * Confirmed from disassembly 0x196330-0x196391:
 *   - scenario_get() 0-arg (leading PUSH ECX is a local-slot reserve).
 *   - +0x258 is an int guard; early return when zero.
 *   - block pointer = scenario+0x134 passed to tag_block_get_element
 *     (PUSH 0x68; PUSH index; PUSH block; cdecl, ADD ESP,0xc).
 *   - count = uint16 at +0x134; signed compare (MOVSX AX; TEST; JLE).
 *   - element gate: word[elem+0xc] != -1  AND  word[elem+0xe] != 0 (int16).
 *   - decals_delete_permanent_from_cluster((int16_t)index) — cdecl 1 arg;
 *     BX (loop index) compared against count spilled at [EBP-4].
 * All cdecl; no FPU, SEH, or intrinsics.
 */
void FUN_00196330(void)
{
  char *scenario;
  void *block;
  int16_t cluster_count; /* short local: movw load + full-reg spill to EBP-4 */
  int16_t cluster_index; /* BX */
  int element_index; /* ESI */

  scenario = (char *)scenario_get();
  if (*(int *)(scenario + 0x258) != 0) {
    block = (void *)(scenario + 0x134);
    cluster_count = *(int16_t *)block;
    cluster_index = 0;
    if (cluster_count > 0) {
      element_index = 0;
      do {
        char *cluster = tag_block_get_element(block, element_index, 0x68);
        if (*(int16_t *)(cluster + 0xc) != -1 &&
            *(int16_t *)(cluster + 0xe) != 0) {
          decals_delete_permanent_from_cluster(cluster_index);
        }
        cluster_index = (int16_t)(cluster_index + 1);
        element_index += 1;
      } while (cluster_index < cluster_count);
    }
  }
}

/* structure_runtime_decals_dispose_from_old_map (0x1963a0) — structures.obj
 *
 * Empty no-op in this build: the disassembly is a single RET (C3). Preserved
 * as an empty body to keep the address populated and the ABI intact. */
void structure_runtime_decals_dispose_from_old_map(void)
{
}

/* structure_runtime_decals_dispose (0x1963b0) — structures.obj
 *
 * Empty no-op in this build: the disassembly is a single RET (C3) with no
 * prologue, stack frame, FPU, memory access, or calls. Preserved as an
 * empty body to keep the address populated and the ABI intact. */
void structure_runtime_decals_dispose(void)
{
}

/* FUN_00196fd0 (0x196fd0) — structures.obj
 *
 * Gathers de-duplicated surface/portal indices from a set of clusters into
 * out_buf, capped at max_count.  For every cluster in cluster_indices[] it
 * walks the cluster's sub-block (element+0x34), and for each sub-element that
 * passes both the cull test FUN_00196a60(element, bounds) and the visibility
 * test FUN_00196b10(element, arg_1c, arg_20) it iterates the element's index
 * list (element+0x18, dword indices).  Each index is bit-tested against the
 * allowed-set bitvector at 0x5137d0; if allowed and not yet marked in the
 * caller-supplied seen_mask bitvector, it is marked and appended to out_buf.
 * Returns the number of indices written (AX = running EDI counter).
 *
 * Cdecl; +0x10/+0x14 are present-but-unused stack slots (kept in the
 * signature to preserve the stack layout of the arguments after them).
 * All three loop counters are 32-bit stack homes used with (short) truncation
 * (matches the disasm's movsx/16-bit-compare pattern).  The bitvector accesses
 * use raw base+byteoffset arithmetic (byteoffset = (val>>5)*4), NOT [i]
 * indexing, to match the original codegen.  Ghidra split the single EDI
 * running counter into two locals and invented a sVar11<->sVar5 swap; the
 * disassembly shows one variable at [ebp-4] that is both the append index and
 * the return value. */
int16_t FUN_00196fd0(int *out_buf, int16_t max_count, int unused_10,
                     int unused_14, float *bounds, int arg_1c, int arg_20,
                     uint32_t *seen_mask, int16_t cluster_count,
                     int16_t *cluster_indices)
{
  char *scenario;
  int out_count; /* [ebp-4]    running append count == EDI == return */
  int outer_index; /* [ebp-0x14] cluster loop index */
  int inner_index; /* [ebp-8]    sub-element loop index */
  int inner2_index; /* [ebp-0xc]  index-list loop index */
  char *cluster;
  int *sub_block; /* element+0x34 */
  char *element;
  int *idx_block; /* element+0x18 */
  int *idx_ptr;
  short cull;
  int cluster_idx;
  int val;
  uint32_t bit;
  int byteoff;

  (void)unused_10;
  (void)unused_14;

  scenario = (char *)scenario_get();
  out_count = 0;
  outer_index = 0;
  if (cluster_count > 0) {
    do {
      if ((short)out_count >= max_count) {
        break;
      }
      cluster_idx = cluster_indices[(short)outer_index];
      cluster = (char *)tag_block_get_element((void *)(scenario + 0x134),
                                              cluster_idx, 0x68);
      sub_block = (int *)(cluster + 0x34);
      inner_index = 0;
      if (*sub_block > 0) {
        do {
          if ((short)out_count >= max_count) {
            break;
          }
          element = (char *)tag_block_get_element((void *)sub_block,
                                                  (short)inner_index, 0x24);
          cull = (short)FUN_00196a60((float *)element, bounds);
          if (cull != 0) {
            cull = (short)FUN_00196b10((float *)element, arg_1c, arg_20);
            if (cull != 0) {
              idx_block = (int *)(element + 0x18);
              idx_ptr = (int *)tag_block_get_element((void *)idx_block, 0, 4);
              inner2_index = 0;
              if (*idx_block > 0) {
                do {
                  val = *idx_ptr;
                  bit = 1u << (val & 0x1f);
                  byteoff = (val >> 5) * 4;
                  /* allowed-set bitvector at 0x5137d0, raw base+byteoff */
                  if ((*(uint32_t *)((char *)0x5137d0 + byteoff) & bit) != 0 &&
                      (bit & *(uint32_t *)((char *)seen_mask + byteoff)) == 0) {
                    if ((short)out_count >= max_count) {
                      break;
                    }
                    *(uint32_t *)((char *)seen_mask + byteoff) |= bit;
                    out_buf[(short)out_count] = *idx_ptr;
                    out_count++;
                  }
                  idx_ptr++;
                  inner2_index++;
                } while ((short)inner2_index < *idx_block);
              }
            }
          }
          inner_index++;
        } while ((short)inner_index < *sub_block);
      }
      outer_index++;
    } while ((short)outer_index < cluster_count);
  }
  return (int16_t)out_count;
}

/* FUN_00195790 (0x195790) — readable C lift (restored pre-naked). */
void FUN_00195790(int *surface_material_offsets /* @<eax> */,
                  unsigned short surface_count, int lightmap_pass_index,
                  void *material_begin_cb, void *surface_draw_cb,
                  void *pass_end_cb, int param_7)
{
  typedef void (*material_begin_fn)(void *);
  typedef void (*surface_draw_fn)(void *, unsigned short, int, int, int, void *);
  typedef void (*pass_end_fn)(void);
  typedef void (*transparent_draw_fn)(void *, unsigned short, void *, int, int,
                                      int, void *, void *, void *, void *,
                                      void *, int);
  void *scenario;
  int *surf;     /* EBX: current surface offset cursor */
  int *surf_end; /* [EBP-0x4] */
  char *materials;
  int mat_idx;   /* [EBP-0x14] */
  int accum;     /* [EBP+0x8] running surface accumulator */
  void *lightmap;/* [EBP-0x8] */

  scenario = scenario_get();
  surf = surface_material_offsets;
  surf_end = surface_material_offsets + (short)surface_count;
  materials = (char *)scenario + 0x104;
  accum = 0;
  mat_idx = 0;

  if (*(int *)materials > 0) {
    do {
      char *mat;
      int *submat_block;
      void *last_sub;
      if (surf_end <= surf) {
        return;
      }
      mat = (char *)tag_block_get_element(materials, mat_idx, 0x20);
      submat_block = (int *)(mat + 0x14);
      last_sub = tag_block_get_element(submat_block, *submat_block - 1, 0x100);
      if (*surf < *(int *)((char *)last_sub + 0x18) +
                      *(int *)((char *)last_sub + 0x14)) {
        int submat_idx;
        if (*(int *)((char *)scenario + 0xc) == -1) {
          lightmap = (void *)0;
        } else {
          lightmap = FUN_00076ff0(*(int *)((char *)scenario + 0xc),
                                  *(short *)mat);
        }
        if (material_begin_cb != (void *)0) {
          ((material_begin_fn)material_begin_cb)(lightmap);
        }
        submat_idx = 0;
        if (*submat_block > 0) {
          do {
            char *sub;
            if (surf_end <= surf) {
              break;
            }
            sub = (char *)tag_block_get_element(submat_block, submat_idx, 0x100);
            if (*surf < *(int *)(sub + 0x14) + *(int *)(sub + 0x18)) {
              void *shader;
              int *run_start;
              short run_count;
              run_start = surf;
              shader = tag_get(0x73686472, *(int *)(sub + 0xc));
              do {
                surf = surf + 1;
                if (surf_end <= surf) {
                  break;
                }
              } while (*surf < *(int *)(sub + 0x14) + *(int *)(sub + 0x18));
              run_count = (short)(surf - run_start);
              if (breakable_surface_extant(*(short *)(sub + 0xac)) != '\0') {
                if (shader_type_is_transparent(
                        *(short *)((char *)shader + 0x24)) == '\0') {
                  if (surface_draw_cb != (void *)0) {
                    ((surface_draw_fn)surface_draw_cb)(
                        shader, *(unsigned short *)(sub + 0x10),
                        lightmap_pass_index, accum, run_count, sub + 0xb0);
                  }
                } else if (param_7 != 0) {
                  void *xform;
                  void *extra;
                  unsigned short flags = *(unsigned short *)(sub + 0x12);
                  if ((flags & 2) != 0) {
                    xform = (void *)0x4d8ebc;
                  } else {
                    xform = *(void **)0x0031fc38;
                  }
                  if ((flags & 1) != 0) {
                    extra = sub + 0x9c;
                  } else {
                    extra = (void *)0;
                  }
                  ((transparent_draw_fn)(unsigned int)param_7)(
                      shader, *(unsigned short *)(sub + 0x10), lightmap,
                      lightmap_pass_index, accum, run_count, sub + 0xb0,
                      sub + 0x1c, extra, xform, sub + 0x28, 0);
                }
              }
              accum = accum + run_count;
            }
            submat_idx = submat_idx + 1;
          } while ((short)submat_idx < *submat_block);
        }
        if (pass_end_cb != (void *)0) {
          ((pass_end_fn)pass_end_cb)();
        }
      }
      mat_idx = mat_idx + 1;
    } while ((short)mat_idx < *(int *)((char *)scenario + 0x104));
  }

  if (surf < surf_end) {
    display_assert(
        "there are more surfaces than materials that reference them, stupid.",
        "c:\\halo\\SOURCE\\structures\\structure_render.c", 599, true);
    system_exit(-1);
  }
}



/* FUN_00197130 (0x197130) — readable C lift (restored pre-naked). */
int FUN_00197130(float *bounds, void *param_2, int *param_3, int count,
                 float *center, float radius, float *cull_bounds, int param_8,
                 int param_9, int intersection, int leaf /* @<eax> */)
{
  void *scenario;
  char *leaf_element;
  int accumulator;
  int cull_result;
  float local_20[6];

  (void)radius;
  accumulator = 0;
  scenario = scenario_get();
  leaf_element = (char *)tag_block_get_element((char *)scenario + 0xe0,
                                               leaf & 0x7fffffff, 0x10);

  if ((short)intersection == 0) {
    display_assert("intersection",
                   "c:\\halo\\SOURCE\\structures\\structure_visibility.c", 0x2f0,
                   true);
    system_exit(-1);
  }
  if (bounds == (float *)0) {
    display_assert("parent_bounds",
                   "c:\\halo\\SOURCE\\structures\\structure_visibility.c", 0x2f1,
                   true);
    system_exit(-1);
  }
  if (center == (float *)0) {
    display_assert("cull_sphere_center",
                   "c:\\halo\\SOURCE\\structures\\structure_visibility.c", 0x2f2,
                   true);
    system_exit(-1);
  }
  if (cull_bounds == (float *)0) {
    display_assert("cull_bounds",
                   "c:\\halo\\SOURCE\\structures\\structure_visibility.c", 0x2f3,
                   true);
    system_exit(-1);
  }
  if (*(short *)(leaf_element + 8) < 0 ||
      *(int *)((char *)scenario + 0x134) <= (int)*(short *)(leaf_element + 8)) {
    display_assert(
        "leaf->cluster_index>=0 && leaf->cluster_index<structure->clusters.count",
        "c:\\halo\\SOURCE\\structures\\structure_visibility.c", 0x2f4, true);
    system_exit(-1);
  }

  FUN_00196eb0(bounds, (unsigned char *)leaf_element, local_20);

  cull_result = (short)intersection;
  if ((short)intersection != 2) {
    int a = FUN_00196a60(cull_bounds, local_20);
    int b = FUN_00196b10(local_20, param_8, param_9);
    cull_result = a;
    if ((short)b < (short)a) {
      cull_result = b;
    }
  }

  if ((short)cull_result != 0) {
    int i;
    int first = *(int *)(leaf_element + 0xc);
    int end = (int)*(short *)(leaf_element + 0xa) + first;
    char *surface_block = (char *)scenario + 0xec;
    for (i = first; i < end; i++) {
      int *elem = (int *)tag_block_get_element(surface_block, i, 8);
      int cluster = *elem;
      int word_off = (cluster >> 5) * 4;
      unsigned int mask = 1u << (cluster & 0x1f);
      if ((mask & *(unsigned int *)((char *)0x5137d0 + word_off)) != 0) {
        unsigned int *per_call = (unsigned int *)((char *)param_2 + word_off);
        if ((mask & *per_call) == 0) {
          if ((short)count <= (short)accumulator) {
            break;
          }
          *per_call |= mask;
          param_3[(short)accumulator] = cluster;
          accumulator = accumulator + 1;
        }
      }
      end = (int)*(short *)(leaf_element + 0xa) + *(int *)(leaf_element + 0xc);
    }
  }

  return accumulator;
}



/* FUN_00197310 (0x197310) — readable C lift (restored pre-naked). */
short FUN_00197310(void *verts, void *plane, void *ref, void *arg1,
                   int16_t count, int sign, short *out)
{
  float *v = (float *)verts;
  float *p = (float *)plane;
  float *r = (float *)ref;
  float buf[256][3];
  float side;
  float ooz;
  int orig_sign;
  int j;
  short idx;
  short end;
  short oidx;

  scenario_get();
  *out = 0;
  orig_sign = (short)sign;
  side = (r[2] * p[2] + r[1] * p[1] + r[0] * p[0] - p[3]) * (float)orig_sign;
  if (*((char *)ref + 0x24) != '\0') {
    sign = -sign;
  }
  if (fabs(side) < *(double *)0x002674e8) {
    return 2;
  }
  if (side <= *(float *)0x002533c0) {
    return 1;
  }

  if (count > 0) {
    float *mtx = (float *)((char *)arg1 + 0x10);
    for (j = 0; j < count; j++) {
      matrix_transform_point(mtx, v + j * 3, &buf[j][0]);
    }
  }

  *out = convex_polygon3d_clip_to_plane(count, &buf[0][0], (float *)0x002b35c4,
                                        0x100, &buf[0][0], (uint32_t *)0,
                                        0.0001f, (void *)0x1);
  if (*out == -1) {
    display_assert("result->vertex_count!=NONE",
                   "c:\\halo\\SOURCE\\structures\\structure_visibility.c", 0x485,
                   true);
    system_exit(-1);
  }

  if (sign == 1) {
    idx = 0;
    end = *out;
  } else {
    idx = (short)(*out - 1);
    end = -1;
  }
  oidx = 0;
  if (idx != end) {
    do {
      int e = (int)idx;
      ooz = *(float *)0x00255e94 / buf[e][2];
      if (ooz <= *(float *)0x002533c0) {
        display_assert("ooz>0.f",
                       "c:\\halo\\SOURCE\\structures\\structure_visibility.c",
                       0x497, true);
        system_exit(-1);
      }
      *(float *)(out + oidx * 4 + 2) = ooz * buf[e][0];
      *(float *)(out + oidx * 4 + 4) = ooz * buf[e][1];
      idx = (short)(idx + sign);
      oidx = (short)(oidx + 1);
    } while (idx != end);
  }

  return (short)(*out < 3);
}


/* 0x1974f0 - resolve a structure-connection plane and dispatch the edge solve.
 *
 * Looks up the scenario structure connection at index connection_index in the
 * scenario connections tag_block (scenario+0x154, stride 0x40).  The connection
 * record supplies the plane-block index (*(int*)(conn+4)) and an edge count
 * (*(short*)(conn+0x34)).  It fetches the shared structure block
 * (tag_block scenario+0xb0, element 0, stride 0x60), then the plane element
 * (tag_block block+0xc, index conn+4, stride 0x10 = one plane[4]).  Finally it
 * calls the edge-solve helper FUN_00197310 with the connection's vertex array
 * (*(void**)(conn+0x38)) in EAX, the plane in ECX, the fixed global reference
 * struct 0x506550 in EDX, the fixed global table 0x5065a4 as stack arg1, the
 * edge count, a +1/-1 sign selected by `pick` ((pick==0)?1:-1), and the caller
 * out pointer.  Returns FUN_00197310's short result in AX.
 *
 * ABI (prologue at 0x1974f0): PUSH EBP/MOV EBP,ESP/PUSH ESI/PUSH EDI with no
 * entry register moves -> pure cdecl.  connection_index=[EBP+8] (word, MOVSX),
 * pick=[EBP+0xc] (byte), out=[EBP+0x10] (dword).  scenario_get / the three
 * tag_block_get_element calls are cdecl; FUN_00197310 is register-arg
 * (EAX/ECX/EDX + 4 stack args, ADD ESP,0x10 cleanup). */
short FUN_001974f0(int16_t connection_index, char pick, int *out)
{
  int scenario;
  void *conn;

  scenario = (int)scenario_get();
  conn = tag_block_get_element((void *)(scenario + 0x154), connection_index,
                               0x40);
  return FUN_00197310(
      *(void **)((char *)conn + 0x38),
      tag_block_get_element(
          (void *)((char *)tag_block_get_element((void *)(scenario + 0xb0), 0,
                                                 0x60) +
                   0xc),
          *(int *)((char *)conn + 4), 0x10),
      (void *)0x506550, (void *)0x5065a4, *(short *)((char *)conn + 0x34),
      (pick == 0) ? 1 : -1, (short *)out);
}

/* 0x197570 - test a run of structure vertices against a stored plane.
 *
 * Walks records[count] (stride 3 floats = 0xc bytes) and, for each vertex,
 * computes the signed distance to the plane whose reference point is the
 * vector3 at 0x506550 and whose normal is the vector3 at 0x50655c:
 *   d = n.x*(v.x-p.x) + n.y*(v.y-p.y) + n.z*(v.z-p.z)
 * Returns 1 as soon as any vertex has d <= threshold (the original's
 * FCOMP [EBP+8] / TEST AH,0x41 / JNP: jump-to-return-1 on C3|C0, i.e. the
 * less-or-equal ordered case; unordered/greater continues).  Returns 0 when
 * no vertex satisfies the test (or count <= 0).
 *
 * Register ABI (prologue at 0x197570): no entry moves; EDX is used directly as
 * the record base (LEA [EDX+EAX*4]) and SI as the loop bound (TEST SI,SI) ->
 * records=EDX, count=ESI (int16).  threshold is the sole stack arg [EBP+8]
 * (float).  Return AL (char).  The accumulation order mirrors the original:
 * normal.z term first, then .y, then .x. */
char FUN_00197570(float *records, int16_t count, float threshold)
{
  int16_t i;
  float *rec;
  float d;

  i = 0;
  if (0 < count) {
    do {
      rec = records + i * 3;
      d = *(float *)0x50655c * (rec[0] - *(float *)0x506550) +
          *(float *)0x506560 * (rec[1] - *(float *)0x506554) +
          *(float *)0x506564 * (rec[2] - *(float *)0x506558);
      if (d <= threshold) {
        return 1;
      }
      i = i + 1;
    } while (i < count);
  }
  return 0;
}

/* FUN_00197e90 (0x197e90) — structures.obj
 *
 * Cluster-query dispatcher for a bounding sphere.  Gathers the visible
 * structure surfaces overlapping the sphere (center=position, radius) into
 * `buffer` (capped at max_count) and returns the count.  Three dispatch paths,
 * all sharing a per-call visibility bitmask (zeroed once up front):
 *   - radius < 2.0            -> walk the collision BSP from its root node
 *                                (scenario+0xc8) via FUN_001978a0.
 *   - explicit cluster list   -> when gel_buffer != 0, gather directly from the
 *                                caller-supplied clusters via FUN_00196fd0.
 *   - else                    -> resolve the point's cluster
 *                                (scenario_location_from_point); if valid,
 *                                flood the neighbouring clusters
 *                                (structure_find_in_cluster) then gather via
 *                                FUN_00196fd0; otherwise fall back to the BSP
 *                                walk (FUN_001978a0).
 *
 * Confirmed from disassembly 0x197e90-0x19806b:
 *   - Prologue MOV EAX,0x4424 / CALL _chkstk (0x1d90e0) — triggered by the two
 *     large stack buffers; NOT emitted as a C call.
 *   - scenario_get() result kept in EDI across the whole body and homed at
 *     [EBP-4]; scenario+0xf8 = cluster count (bits), scenario+0xc8 = root
 *     collision-BSP node passed as FUN_001978a0's parent_bounds arg.
 *   - assert(bounding_sphere_center)               @ line 0x265 (reason string
 *       "bounding_sphere_center", 0x2b38b8)
 *   - assert(!bounding_surface_count || bounding_surfaces) @ line 0x266
 *       (reason "!bounding_surface_count || bounding_surfaces", 0x2b3888);
 *       tested as (short)surface_count and surfaces==NULL.  Both asserts are
 *       display_assert(reason, file, line, 1); system_exit(-1) (0x8e2f0),
 *       NOT halt_and_catch_fire.
 *   - visibility_mask (local_4428, 0x4000 bytes) zeroed with
 *     csmemset(mask, 0, ((clustercount+0x1f)>>5)*4) — one 32-bit word per 32
 *     clusters; size spelled *4 to match the ref's SAR/SHL codegen.
 *   - cull_bounds: when param_5 (cull_bounds_in) is NULL, a local 6-float AABB
 *     is filled {cx-r, cx+r, cy-r, cy+r, cz-r, cz+r} and used as the cull
 *     region; the subtract operands are (center - radius) and the add operands
 *     are (radius + center), matching the FLD/FSUB vs FLD/FADD operand order.
 *   - Radius threshold is the float global at 0x32cf50 (== 2.0f); FCOMP + TEST
 *     AH,0x5 / JP is the `radius < threshold` primitive (fall-through takes
 * it).
 *   - loc: scenario_location_from_point writes a dword handle at +0 and a word
 *     cluster reference at +4; the +4 field is read as a 32-bit int once
 *     (MOV EAX,[loc+4]) and used for both the (short)!=-1 compare (CMP AX) and
 *     the structure_find_in_cluster cluster arg (PUSH EAX), so it is modelled
 *     as an int field.  structure_find_in_cluster's out buffer is 0x200 int16
 *     indices (local_428, exactly 0x400 bytes).
 *   - FUN_00196fd0 args 3/4 receive the center pointer and the raw radius dword
 *     (integer PUSHes); the callee ignores both (unused_10/unused_14), so the
 *     radius is forwarded as its bit pattern to reproduce the exact push.
 *
 * All calls verified push-by-push against the disassembly (cdecl; cleanups
 * 0x2c for FUN_001978a0, 0x28/0x3c for FUN_00196fd0).  param_5/6/7 kept as int
 * per kb.json (callers cast pointers to int); cast to the real types locally.
 */
short FUN_00197e90(void *buffer, int max_count, float *position, float radius,
                   int cull_bounds_in, int surface_count, int surfaces,
                   int gel_count, int gel_buffer)
{
  char *scenario;
  float *cull_bounds;
  int16_t cluster_count_found;
  float local_bounds[6];
  struct {
    int location_index;
    int cluster_index;
  } loc;
  int16_t cluster_indices[0x200];
  uint32_t visibility_mask[0x1000];

  scenario = (char *)scenario_get();

  if (position == (float *)0) {
    display_assert("bounding_sphere_center",
                   "c:\\halo\\SOURCE\\structures\\structure_visibility.c",
                   0x265, 1);
    system_exit(-1);
  }
  if ((short)surface_count != 0 && surfaces == 0) {
    display_assert("!bounding_surface_count || bounding_surfaces",
                   "c:\\halo\\SOURCE\\structures\\structure_visibility.c",
                   0x266, 1);
    system_exit(-1);
  }

  csmemset(visibility_mask, 0, ((*(int *)(scenario + 0xf8) + 0x1f) >> 5) * 4);

  cull_bounds = (float *)cull_bounds_in;
  if (cull_bounds == (float *)0) {
    cull_bounds = local_bounds;
    local_bounds[0] = position[0] - radius;
    local_bounds[1] = radius + position[0];
    local_bounds[2] = position[1] - radius;
    local_bounds[3] = radius + position[1];
    local_bounds[4] = position[2] - radius;
    local_bounds[5] = radius + position[2];
  }

  if (radius < *(float *)0x32cf50) {
    return FUN_001978a0(0, (float *)(scenario + 0xc8), visibility_mask,
                        (int *)buffer, max_count, position, radius, cull_bounds,
                        surface_count, surfaces, 1);
  }

  if (gel_buffer != 0) {
    return FUN_00196fd0((int *)buffer, max_count, (int)position,
                        *(const int *)&radius, cull_bounds, surface_count,
                        surfaces, visibility_mask, gel_count,
                        (int16_t *)gel_buffer);
  }

  scenario_location_from_point(&loc, position);
  if ((short)loc.cluster_index != -1) {
    cluster_count_found = structure_find_in_cluster(
      loc.cluster_index, position, radius, 0x200, cluster_indices);
    return FUN_00196fd0((int *)buffer, max_count, (int)position,
                        *(const int *)&radius, cull_bounds, surface_count,
                        surfaces, visibility_mask, cluster_count_found,
                        cluster_indices);
  }

  return FUN_001978a0(0, (float *)(scenario + 0xc8), visibility_mask,
                      (int *)buffer, max_count, position, radius, cull_bounds,
                      surface_count, surfaces, 1);
}

/* FUN_00198070 (0x198070) — structures.obj
 *
 * Per-frame rebuild of the active cluster's environment sound/geometry list,
 * then for every rendered cluster this frame it evaluates the clipped frustum
 * bounds and builds the camera frustum used to draw that cluster.
 *
 * Runs only when the active-cluster handle at 0x506784 is not -1.
 *
 * Confirmed from disassembly 0x198070-0x19817d:
 *   - scenario_get() called first (result kept in ESI across the whole body);
 *     guard is a dword compare CMP [0x506784],-1 / JZ.
 *   - render_frustum_get_projection_bounds(0x5065a4, proj_bounds) fills a
 *     4-dword buffer whose base is [EBP-0x10] (Ghidra's "local_14".."local_4";
 *     the base is EBP-0x10, NOT EBP-0x14 as the decompiler implied).
 *   - The 4 bounds dwords are scattered into an int16-tagged struct at
 *     EBP-0x864 (word 4 at +0x0, then 8 dwords at +0x4). Scatter map derived
 *     from the raw MOV destination offsets, not the decompiler local names:
 *       +0x04=b[0] +0x08=b[2] +0x0c=b[1] +0x10=b[2]
 *       +0x14=b[1] +0x18=b[3] +0x1c=b[0] +0x20=b[3]
 *   - Global 0x4d8ed8 is set to &cluster_buf (a 0x40-byte stack buffer) BEFORE
 *     csmemset(cluster_buf,0,0x40); tail store order preserved: set global,
 *     word=4, memset, then FUN_00197b00((uint16)*0x506784, sound_list).
 *   - Loop over [0, (int16)*0x5137cc): rendered_cluster_get(i) -> cluster;
 *     tag_block_get_element(scenario+0x134, (int16)*cluster, 0x68) (result
 *     discarded); render_camera_build_clipped_frustum_bounds(0x506550,
 *     cluster+2 shorts, frustum_bounds) (result discarded);
 *     render_camera_build_frustum(0x506550, frustum_bounds, cluster+10 shorts,
 *     1). scenario+0x134 is hoisted into EBX before the loop (ESI is reused as
 *     the cluster pointer) — these are distinct variables in C.
 *   - Signed int16 loop counter/compare (CMP DI,word[0x5137cc] / JL).
 * All cdecl; no FPU subtraction, SEH, or intrinsics.
 */
void FUN_00198070(void)
{
  char *scenario;
  int16_t *cluster;
  int cluster_index;
  float proj_bounds[4];
  float frustum_bounds[4];
  unsigned char cluster_buf[0x40];
  struct {
    int16_t tag;
    int16_t pad;
    float v[8];
  } sound_list;

  scenario = (char *)scenario_get();
  if (*(int *)0x506784 != -1) {
    render_frustum_get_projection_bounds((void *)0x5065a4, proj_bounds);

    sound_list.v[0] = proj_bounds[0]; /* +0x04 */
    sound_list.v[1] = proj_bounds[2]; /* +0x08 */
    sound_list.v[2] = proj_bounds[1]; /* +0x0c */
    sound_list.v[3] = proj_bounds[2]; /* +0x10 */
    sound_list.v[4] = proj_bounds[1]; /* +0x14 */
    sound_list.v[5] = proj_bounds[3]; /* +0x18 */
    sound_list.v[6] = proj_bounds[0]; /* +0x1c */
    sound_list.v[7] = proj_bounds[3]; /* +0x20 */

    *(void **)0x4d8ed8 = cluster_buf;
    sound_list.tag = 4;
    csmemset(cluster_buf, 0, 0x40);
    FUN_00197b00(*(uint16_t *)0x506784, (uint16_t *)&sound_list);

    cluster_index = 0;
    if (*(int16_t *)0x5137cc > 0) {
      do {
        cluster = (int16_t *)rendered_cluster_get(cluster_index);
        tag_block_get_element(scenario + 0x134, *cluster, 0x68);
        render_camera_build_clipped_frustum_bounds(
          (camera_t *)0x506550, (float *)(cluster + 2), frustum_bounds);
        render_camera_build_frustum((camera_t *)0x506550, frustum_bounds,
                                    (float *)(cluster + 10), 1);
        cluster_index += 1;
      } while ((int16_t)cluster_index < *(int16_t *)0x5137cc);
    }
  }
}

/* FUN_00198180 (0x198180) render_structure_visibility:
 *   Per-frame rebuild of the structure BSP visibility bitvectors, followed by
 *   construction of the rendered-cluster list and dispatch to the fast or
 *   legacy cluster-visibility sweep.
 *
 *   scenario = scenario_get(); clusters tag_block at scenario+0x134 (element
 *   size 0x68, count = *(int*)(scenario+0x134)); scenario+0xf8 sizes the
 *   per-portal bitvector.  Per-cluster visibility bitvector at 0x50678c is
 *   memset to 0xffffffff when the active cluster (0x506784) is -1, else 0; the
 *   per-portal bitvector at 0x5137d0 is zeroed.  0x5137cc = rendered-cluster
 *   count (int16), 0x4d8edc = cluster_index -> rendered_cluster_index table
 *   (int16[]).
 *
 *   Register-alias note (verified against disasm 0x198180-0x1983b5): ESI holds
 *   the scenario pointer, but is reused as the loop's bit_index inside the
 *   sweep and reloaded from [EBP-4] afterward.  Kept as two distinct C locals
 *   (scenario / bit_index).  The final structure_bsp record at
 *   tag_block_get_element(clusters,0,0x68)+0x34 selects FUN_001966b0 (!=0, has
 *   precomputed visibility) vs FUN_00196850 (==0, legacy path that emits the
 *   reimport warning).
 *
 *   __FILE__ = c:\halo\SOURCE\structures\structure_visibility.c */
void render_structure_visibility(void)
{
  int scenario;
  int *clusters;
  int bit_index;
  int cluster_index;
  short *cluster_rec;
  void *sound_data;
  char *first_cluster;

  scenario = (int)scenario_get();
  if (*(char *)0x449ef1 != '\0' && *(char *)0x32bd70 != '\0') {
    profile_enter_private((void *)0x32bd68);
  }
  clusters = (int *)(scenario + 0x134);
  /* original branches on the active cluster and duplicates the size
   * computation per arm (two push sites merged at the call) */
  if (*(int *)0x506784 != -1) {
    csmemset((void *)0x50678c, 0, ((*clusters + 0x1f) >> 5) * 4);
  } else {
    csmemset((void *)0x50678c, -1, ((*clusters + 0x1f) >> 5) * 4);
  }
  *(short *)0x5937d0 = 0;
  csmemset((void *)0x5137d0, 0, ((*(int *)(scenario + 0xf8) + 0x1f) >> 5) * 4);
  *(short *)0x5137cc = 0;
  FUN_00198070();
  if (*(char *)0x505701 != '\0') {
    *(short *)0x5137cc = 0;
    /* zero-extended load (XOR ECX + MOV CX) in the original */
    sound_data = structure_bsp_get_cluster_sound_data((void *)scenario,
                                                      *(uint16_t *)0x506784);
    csmemcpy((void *)0x50678c, sound_data, ((*clusters + 0x1f) >> 5) * 4);
    if (0 < *clusters) {
      cluster_index = 0;
      bit_index = 0;
      do {
        if ((((unsigned int *)0x50678c)[bit_index >> 5] &
             (1u << (bit_index & 0x1f))) != 0) {
          tag_block_get_element(clusters, bit_index, 0x68);
          if (*(short *)0x5137cc >= 0x80) {
            display_assert(
              "raise MAXIMUM_RENDERED_CLUSTERS",
              "c:\\halo\\SOURCE\\structures\\structure_visibility.c", 0x118, 1);
            system_exit(-1);
          }
          if ((short)cluster_index < 0 || (short)cluster_index >= 0x200) {
            display_assert(
              "cluster_index>=0 && "
              "cluster_index<MAXIMUM_CLUSTERS_PER_STRUCTURE",
              "c:\\halo\\SOURCE\\structures\\structure_visibility.c", 0x11b, 1);
            system_exit(-1);
          }
          ((short *)0x4d8edc)[bit_index] = *(short *)0x5137cc;
          *(short *)0x5137cc = *(short *)0x5137cc + 1;
          cluster_rec = (short *)rendered_cluster_get(
            ((unsigned short *)0x4d8edc)[bit_index]);
          *cluster_rec = (short)cluster_index;
          render_frustum_get_projection_bounds((void *)0x5065a4,
                                               (float *)(cluster_rec + 2));
        }
        cluster_index = cluster_index + 1;
        bit_index = (int)(short)cluster_index;
      } while (bit_index < *clusters);
    }
  }
  if (*(char *)0x449ef1 != '\0' && *(char *)0x32bd70 != '\0') {
    profile_exit_private((void *)0x32bd68);
  }
  first_cluster = (char *)tag_block_get_element(clusters, 0, 0x68);
  if (*(int *)(first_cluster + 0x34) == 0) {
    if (*(char *)0x4d8ed0 == '\0') {
      if (0 < *(int *)(scenario + 0xf8)) {
        error(2, "### WARNING: this structure_bsp needs to be reimported for "
                 "new, faster visibility.");
      }
      *(char *)0x4d8ed0 = '\x01';
    }
    FUN_00196850(scenario);
    return;
  }
  FUN_001966b0(scenario);
}

void structures_initialize(void)
{
  structure_detail_objects_initialize();
  structure_runtime_decals_initialize();
}

void structures_initialize_for_new_map(void)
{
  structure_detail_objects_initialize_for_new_map();
  structure_runtime_decals_initialize_for_new_map();
}

/* structures_dispose_from_old_map (0x1983e0): CALL 0x1963a0 + tail-JMP
 * 0x1939c0 in the original — decals first, then detail objects (reverse of
 * the initialize order). Both callees are bare RETs in this build, but the
 * call shape is preserved. */
void structures_dispose_from_old_map(void)
{
  structure_runtime_decals_dispose_from_old_map();
  structure_detail_objects_dispose_from_old_map();
}

/* structures_dispose (0x1983f0): CALL 0x1963b0 + tail-JMP 0x1939d0. */
void structures_dispose(void)
{
  structure_runtime_decals_dispose();
  structure_detail_objects_dispose();
}

/* structures_cluster_marker_begin (0x198400)
 *
 * Asserts that the cluster marker is not already initialized,
 * increments the cluster-marker reference counter, and sets the
 * initialized flag.
 *
 * Confirmed: TEST AL,AL on byte ptr [0x4d92e1].
 * Confirmed: INC dword ptr [0x4d92e4].
 * Confirmed: MOV byte ptr [0x4d92e1], 1.
 */
void structures_cluster_marker_begin(void)
{
  if (*(uint8_t *)0x4d92e1 != 0) {
    display_assert("!structure_globals.cluster_marker_initialized",
                   "c:\\halo\\SOURCE\\structures\\structures.c", 0x103, true);
    system_exit(-1);
  }
  *(uint32_t *)0x4d92e4 += 1;
  *(uint8_t *)0x4d92e1 = 1;
}

bool structure_cluster_unmarked(int16_t cluster_index)
{
  if (*(uint8_t *)0x4d92e1 == 0) {
    display_assert("structure_globals.cluster_marker_initialized",
                   "c:\\halo\\SOURCE\\structures\\structures.c", 0x10e, true);
    system_exit(-1);
  }

  if (cluster_index < 0 || cluster_index > 0x1ff) {
    display_assert("cluster_index>=0 && "
                   "cluster_index<MAXIMUM_CLUSTERS_PER_STRUCTURE",
                   "c:\\halo\\SOURCE\\structures\\structures.c", 0x10f, true);
    system_exit(-1);
  }

  return ((int *)0x4d92e8)[cluster_index] != *(int *)0x4d92e4;
}

int structure_cluster_mark(int16_t cluster_index)
{
  if (*(uint8_t *)0x4d92e1 == 0) {
    display_assert("structure_globals.cluster_marker_initialized",
                   "c:\\halo\\SOURCE\\structures\\structures.c", 0x11e, true);
    system_exit(-1);
  }

  if (cluster_index < 0 || cluster_index > 0x1ff) {
    display_assert("cluster_index>=0 && "
                   "cluster_index<MAXIMUM_CLUSTERS_PER_STRUCTURE",
                   "c:\\halo\\SOURCE\\structures\\structures.c", 0x11f, true);
    system_exit(-1);
  }

  if (((int *)0x4d92e8)[cluster_index] != *(int *)0x4d92e4) {
    ((int *)0x4d92e8)[cluster_index] = *(int *)0x4d92e4;
    return 1;
  }

  return 0;
}

/* structures_cluster_marker_end (0x198540)
 *
 * Asserts that the cluster-marker session is currently active (initialized),
 * then clears the initialized flag, ending the session begun by
 * structures_cluster_marker_begin.
 *
 * Confirmed: TEST AL,AL on byte ptr [0x4d92e1] at 0x198545.
 * Confirmed: assert string "structure_globals.cluster_marker_initialized",
 *   __FILE__ "c:\halo\SOURCE\structures\structures.c", line 0x130 (304).
 * Confirmed: MOV byte ptr [0x4d92e1], 0 at 0x198569.
 */
void structures_cluster_marker_end(void)
{
  if (*(uint8_t *)0x4d92e1 == 0) {
    display_assert("structure_globals.cluster_marker_initialized",
                   "c:\\halo\\SOURCE\\structures\\structures.c", 0x130, true);
    system_exit(-1);
  }
  *(uint8_t *)0x4d92e1 = 0;
}

/* structure_render_surface_from_point_and_leaf (0x198580) — XBE naked draft (batch 82). */
#if defined(__clang__)
static void * (*const b198580_c18e3c0)(void) = (void *(*)(void))global_scenario_get;
static void *(*const b198580_elem)(void *, int, int) = tag_block_get_element;
static void (*const b198580_c1935f0)(void *scenario, int surface_index, int16_t *out_collection_index, int16_t *out_geometry_index) = (void *)structure_bsp_find_material_for_surface;
static void (*const b198580_c180500)(float *param_1, float *param_2) = FUN_00180500;
static char (*const b198580_c10d830)(float *p1, float *p2, float *p3, float *p4, float *out_u, float *out_v) = FUN_0010d830;

__attribute__((naked, noinline))
char structure_render_surface_from_point_and_leaf(void *render_context __attribute__((unused)), uint32_t leaf_index __attribute__((unused)), int material_type __attribute__((unused)), int16_t *out_collection_index __attribute__((unused)), int16_t *out_geometry_index __attribute__((unused)), int32_t *out_surface __attribute__((unused)), float *out_u __attribute__((unused)), float *out_v __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x2c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c18e3c0]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl $0x10\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0xe0(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%eax), %%esi\n\t"
      "movswl 0xa(%%eax), %%edx\n\t"
      "addl %%esi, %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "xorb %%cl, %%cl\n\t"
      "cmpl %%edx, %%esi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "jge .Lstructure_render_surface_from_point_and_leaf_6\n\t"
      ".Lstructure_render_surface_from_point_and_leaf_1:\n\t"
      "pushl $8\n\t"
      "leal 0xec(%%edi), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lstructure_render_surface_from_point_and_leaf_4\n\t"
      "pushl $0xc\n\t"
      "pushl %%eax\n\t"
      "pushl $0x60\n\t"
      "leal 0xb0(%%edi), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl (%%eax), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jne .Lstructure_render_surface_from_point_and_leaf_4\n\t"
      "movl (%%ebx), %%edx\n\t"
      "pushl $6\n\t"
      "pushl %%edx\n\t"
      "leal 0xf8(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl (%%ebx), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "call *%[c1935f0]\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movswl (%%eax), %%ecx\n\t"
      "pushl $0x20\n\t"
      "pushl %%ecx\n\t"
      "leal 0x104(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movswl (%%esi), %%ecx\n\t"
      "pushl $0x100\n\t"
      "pushl %%ecx\n\t"
      "addl $0x14, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movw 0xb0(%%esi), %%ax\n\t"
      "addl $0x34, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Lstructure_render_surface_from_point_and_leaf_2\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .Lstructure_render_surface_from_point_and_leaf_3\n\t"
      ".Lstructure_render_surface_from_point_and_leaf_2:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movzwl (%%eax), %%ecx\n\t"
      "movl 0xf8(%%esi), %%eax\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "shll $5, %%ecx\n\t"
      "pushl %%edx\n\t"
      "addl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c180500]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movzwl 0x2(%%eax), %%ecx\n\t"
      "movl 0xf8(%%esi), %%eax\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "shll $5, %%ecx\n\t"
      "pushl %%edx\n\t"
      "addl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c180500]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movzwl 0x4(%%eax), %%ecx\n\t"
      "movl 0xf8(%%esi), %%eax\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "shll $5, %%ecx\n\t"
      "pushl %%edx\n\t"
      "addl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c180500]\n\t"
      "movl 0x24(%%ebp), %%edx\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10d830]\n\t"
      "addl $0x30, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lstructure_render_surface_from_point_and_leaf_5\n\t"
      ".Lstructure_render_surface_from_point_and_leaf_3:\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      ".Lstructure_render_surface_from_point_and_leaf_4:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movswl 0xa(%%eax), %%edx\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "incl %%esi\n\t"
      "addl %%ecx, %%edx\n\t"
      "cmpl %%edx, %%esi\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "jl .Lstructure_render_surface_from_point_and_leaf_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lstructure_render_surface_from_point_and_leaf_5:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lstructure_render_surface_from_point_and_leaf_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%cl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e3c0] "m"(b198580_c18e3c0), [elem] "m"(b198580_elem), [c1935f0] "m"(b198580_c1935f0), [c180500] "m"(b198580_c180500), [c10d830] "m"(b198580_c10d830)
      : "memory");
}
#else
#error "structure_render_surface_from_point_and_leaf: clang naked draft required"
#endif


/* Resolve the planar-fog definition index for a BSP cluster/leaf.
 * index == -1 returns the -1 sentinel. When flag == 0 the fog reference is
 * read from the cluster element (+0x134, stride 0x68) at +2; a set top bit
 * indicates indirection through the +0x178 table (stride 0x20). The masked
 * reference indexes the +0x184 block (stride 0x28); its +0x24 field indexes
 * the +0x190 fog-definition block (stride 0x88) whose +0x2c dword is the
 * result. When flag != 0 the global default (FUN_0018e7d0(0)+0xa4) is used. */
int32_t structure_get_planar_fog_definition_index(void *structure_bsp,
                                                  int16_t index, char flag)
{
  int16_t fog_ref; /* AX-resident through every gate in the original */
  char *element;
  int32_t result = -1; /* EDI; all failure paths share the sunk return */

  if (index == -1) {
    return result;
  }

  element =
    tag_block_get_element((char *)structure_bsp + 0x134, (int)index, 0x68);

  /* flag != 0 arm falls through first in the original; the cluster path is
   * the sunk arm at 0x198781 */
  if (flag != '\0') {
    element = FUN_0018e7d0(0);
    if (element == 0) {
      goto fail;
    }
    return *(int32_t *)(element + 0xa4);
  }

  fog_ref = *(int16_t *)(element + 2);
  if (fog_ref == -1) {
    goto fail;
  }
  if (fog_ref < 0) {
    element = tag_block_get_element((char *)structure_bsp + 0x178,
                                    fog_ref & 0x7fff, 0x20);
    fog_ref = *(int16_t *)element;
  } else {
    fog_ref = (int16_t)(fog_ref & 0x7fff);
  }
  if (fog_ref == -1) {
    goto fail;
  }
  element =
    tag_block_get_element((char *)structure_bsp + 0x184, (int)fog_ref, 0x28);
  fog_ref = *(int16_t *)(element + 0x24);
  if (fog_ref == -1) {
    goto fail;
  }
  element =
    tag_block_get_element((char *)structure_bsp + 0x190, (int)fog_ref, 0x88);
  return *(int32_t *)(element + 0x2c);

fail:
  return result;
}

bool structure_get_planar_fog(void *scenario, int16_t portal_index,
                              float *position, float radius)
{
  uint8_t projected_vertices[1024];
  uint8_t projected_center[8];
  float projected_hit[3];
  char *portal =
    tag_block_get_element((char *)scenario + 0x154, (int)portal_index, 0x40);
  char *structure_bsp = tag_block_get_element((char *)scenario + 0xb0, 0, 0x60);
  float *portal_plane = tag_block_get_element((int *)(structure_bsp + 0xc),
                                              *(int *)(portal + 4), 0x10);
  float plane_distance = position[0] * portal_plane[0] +
                         position[1] * portal_plane[1] +
                         position[2] * portal_plane[2] - portal_plane[3];

  if (fabsf(plane_distance) < radius) {
    float dx = *(float *)(portal + 8) - position[0];
    float dy = *(float *)(portal + 0xc) - position[1];
    float dz = *(float *)(portal + 0x10) - position[2];
    float expanded_radius = radius + *(float *)(portal + 0x14);

    if (dx * dx + dy * dy + dz * dz < expanded_radius * expanded_radius) {
      int portal_plane_index = *(int *)(portal + 4);
      char *bsp3d = FUN_0018e420();
      uint32_t plane_basis;
      uint8_t plane_axis;
      int *portal_vertices = (int *)(portal + 0x34);
      int16_t vertex = 0;

      portal_plane =
        tag_block_get_element((int *)(bsp3d + 0xc), portal_plane_index, 0x10);
      plane_basis = FUN_00099220(portal_plane);
      plane_axis = FUN_00099270(portal_plane, plane_basis);

      projected_hit[0] = -plane_distance * portal_plane[0] + position[0];
      projected_hit[1] = -plane_distance * portal_plane[1] + position[1];
      projected_hit[2] = -plane_distance * portal_plane[2] + position[2];
      FUN_00061df0(projected_hit, plane_basis, plane_axis, projected_center);

      if (*portal_vertices > 0) {
        do {
          FUN_00061df0(tag_block_get_element(portal_vertices, (int)vertex, 0xc),
                       plane_basis, plane_axis,
                       projected_vertices + (int)vertex * 8);
          vertex += 1;
        } while ((int)vertex < *portal_vertices);
      }

      if (FUN_00106130(
            (uint16_t)*portal_vertices, projected_vertices, projected_center,
            sqrtf(radius * radius - plane_distance * plane_distance))) {
        return true;
      }
    }
  }

  return false;
}

int16_t FUN_001989b0(uint16_t cluster_count, float *position, float radius,
                     int max_count, int16_t *out_indices)
{
  void *scenario = scenario_get();
  int16_t current_cluster = (int16_t)cluster_count;
  char *cluster =
    tag_block_get_element((char *)scenario + 0x134, (int)current_cluster, 0x68);
  int remaining_count = max_count - 1;
  int visited_count = 1;

  if ((int16_t)max_count > 0) {
    *out_indices = current_cluster;
    out_indices += 1;
  }

  structure_cluster_mark(cluster_count);

  if (*(int *)(cluster + 0x5c) > 0) {
    int16_t portal_iter = 0;

    do {
      int16_t *portal_index_ptr =
        tag_block_get_element((int *)(cluster + 0x5c), portal_iter, 2);
      int16_t portal_index = *portal_index_ptr;
      int16_t *portal = tag_block_get_element((char *)scenario + 0x154,
                                              (int)portal_index, 0x40);
      int16_t adjacent_cluster = portal[0];

      if (adjacent_cluster == current_cluster) {
        adjacent_cluster = portal[1];
      }

      if (structure_cluster_unmarked(adjacent_cluster) &&
          structure_get_planar_fog(scenario, portal_index, position, radius)) {
        int recurse_count = FUN_001989b0((uint16_t)adjacent_cluster, position,
                                         radius, remaining_count, out_indices);
        visited_count += recurse_count;
        remaining_count -= recurse_count;
        out_indices += (int16_t)recurse_count;
      }

      portal_iter += 1;
    } while ((int)portal_iter < *(int *)(cluster + 0x5c));
  }

  return (int16_t)visited_count;
}

/* structure_clusters_in_cone (0x198ad0) — XBE naked draft (batch 83). */
#if defined(__clang__)
static void (*const b198ad0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b198ad0_exitfn)(int) = system_exit;
static void * (*const b198ad0_c18e3c0)(void) = (void *(*)(void))global_scenario_get;
static int (*const b198ad0_c1984c0)(int16_t cluster_index) = structure_cluster_mark;
static void *(*const b198ad0_elem)(void *, int, int) = tag_block_get_element;
static bool (*const b198ad0_c198440)(int16_t cluster_index) = structure_cluster_unmarked;
static char (*const b198ad0_c110210)(float *p1, float p2, float *p3, float *p4, float p5, float sine, float cosine) = FUN_00110210;

__attribute__((naked, noinline))
int16_t structure_clusters_in_cone(int16_t starting_cluster __attribute__((unused)), float *point __attribute__((unused)), float *direction __attribute__((unused)), float length __attribute__((unused)), float sine __attribute__((unused)), float cosine __attribute__((unused)), int16_t max_count __attribute__((unused)), int16_t *out_indices __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x410, %%esp\n\t"
      "movb 0x4d92e1, %%al\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testb %%al, %%al\n\t"
      "je .Lstructure_clusters_in_cone_1\n\t"
      "pushl $1\n\t"
      "pushl $0x103\n\t"
      "pushl $0x2b3954\n\t"
      "pushl $0x2b3924\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lstructure_clusters_in_cone_1:\n\t"
      "movl 0x4d92e4, %%edx\n\t"
      "pushl %%esi\n\t"
      "incl %%edx\n\t"
      "pushl %%edi\n\t"
      "movl %%edx, 0x4d92e4\n\t"
      "movb $1, 0x4d92e1\n\t"
      "call *%[c18e3c0]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "call *%[c1984c0]\n\t"
      "movw %%si, -0x410(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "movl $1, %%esi\n\t"
      "jmp .Lstructure_clusters_in_cone_2\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lstructure_clusters_in_cone_2:\n\t"
      "cmpw 0x20(%%ebp), %%bx\n\t"
      "jge .Lstructure_clusters_in_cone_9\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "decl %%esi\n\t"
      "movswl %%si, %%eax\n\t"
      "movw -0x410(%%ebp,%%eax,2), %%di\n\t"
      "movswl %%di, %%ecx\n\t"
      "pushl $0x68\n\t"
      "pushl %%ecx\n\t"
      "addl $0x134, %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl 0x24(%%ebp), %%edx\n\t"
      "movswl %%bx, %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "incl %%ebx\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "leal 0x5c(%%eax), %%ebx\n\t"
      "movw %%di, (%%edx,%%ecx,2)\n\t"
      "cmpl $0, (%%ebx)\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "jle .Lstructure_clusters_in_cone_8\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lstructure_clusters_in_cone_3:\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movw (%%eax), %%ax\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl $0x40\n\t"
      "pushl %%eax\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $0x154, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movw (%%esi), %%ax\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpw %%di, %%ax\n\t"
      "jne .Lstructure_clusters_in_cone_4\n\t"
      "movw 0x2(%%esi), %%cx\n\t"
      "movw %%cx, 0x8(%%ebp)\n\t"
      "jmp .Lstructure_clusters_in_cone_5\n\t"
      ".Lstructure_clusters_in_cone_4:\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      ".Lstructure_clusters_in_cone_5:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c198440]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lstructure_clusters_in_cone_7\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x14(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "addl $8, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c110210]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lstructure_clusters_in_cone_7\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1984c0]\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $0x200, %%si\n\t"
      "jl .Lstructure_clusters_in_cone_6\n\t"
      "pushl $1\n\t"
      "pushl $0xf5\n\t"
      "pushl $0x2b3954\n\t"
      "pushl $0x2b39ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lstructure_clusters_in_cone_6:\n\t"
      "movw 0x8(%%ebp), %%dx\n\t"
      "movswl %%si, %%ecx\n\t"
      "incl %%esi\n\t"
      "movw %%dx, -0x410(%%ebp,%%ecx,2)\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      ".Lstructure_clusters_in_cone_7:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lstructure_clusters_in_cone_3\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      ".Lstructure_clusters_in_cone_8:\n\t"
      "testw %%si, %%si\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "jg .Lstructure_clusters_in_cone_2\n\t"
      ".Lstructure_clusters_in_cone_9:\n\t"
      "movb 0x4d92e1, %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "jne .Lstructure_clusters_in_cone_10\n\t"
      "pushl $1\n\t"
      "pushl $0x130\n\t"
      "pushl $0x2b3954\n\t"
      "pushl $0x2b397c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lstructure_clusters_in_cone_10:\n\t"
      "movw %%bx, %%ax\n\t"
      "movb $0, 0x4d92e1\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b198ad0_assert), [exitfn] "m"(b198ad0_exitfn), [c18e3c0] "m"(b198ad0_c18e3c0), [c1984c0] "m"(b198ad0_c1984c0), [elem] "m"(b198ad0_elem), [c198440] "m"(b198ad0_c198440), [c110210] "m"(b198ad0_c110210)
      : "memory");
}
#else
#error "structure_clusters_in_cone: clang naked draft required"
#endif


/* structure_test_vector (0x198cb0) — XBE naked draft (batch 56). */
#if defined(__clang__)
static void (*const b198cb0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b198cb0_exitfn)(int) = system_exit;
static bool (*const b198cb0_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;
static void * (*const b198cb0_c18e3c0)(void) = (void *(*)(void))global_scenario_get;
static char (*const b198cb0_c198580)(void *render_context, uint32_t leaf_index, int material_type, int16_t *out_collection_index, int16_t *out_geometry_index, int32_t *out_surface, float *out_u, float *out_v) = structure_render_surface_from_point_and_leaf;
static void *(*const b198cb0_elem)(void *, int, int) = tag_block_get_element;

__attribute__((naked, noinline))
char structure_test_vector(float *point __attribute__((unused)), float *direction __attribute__((unused)), float *out_point __attribute__((unused)), int16_t *out_collection_index __attribute__((unused)), int16_t *out_material_index __attribute__((unused)), int32_t *out_surface_index __attribute__((unused)), float *out_u __attribute__((unused)), float *out_v __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x54, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jne .Lstructure_test_vector_1\n\t"
      "pushl $1\n\t"
      "pushl $0x188\n\t"
      "pushl $0x2b3954\n\t"
      "pushl $0x26856c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lstructure_test_vector_1:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lstructure_test_vector_2\n\t"
      "pushl $1\n\t"
      "pushl $0x189\n\t"
      "pushl $0x2b3954\n\t"
      "pushl $0x2a3e7c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lstructure_test_vector_2:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lstructure_test_vector_3\n\t"
      "pushl $1\n\t"
      "pushl $0x18a\n\t"
      "pushl $0x2b3954\n\t"
      "pushl $0x2b39ec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lstructure_test_vector_3:\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lstructure_test_vector_4\n\t"
      "pushl $1\n\t"
      "pushl $0x18b\n\t"
      "pushl $0x2b3954\n\t"
      "pushl $0x2b39dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lstructure_test_vector_4:\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lstructure_test_vector_5\n\t"
      "pushl $1\n\t"
      "pushl $0x18c\n\t"
      "pushl $0x2b3954\n\t"
      "pushl $0x2b39d8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lstructure_test_vector_5:\n\t"
      "movl 0x24(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lstructure_test_vector_6\n\t"
      "pushl $1\n\t"
      "pushl $0x18d\n\t"
      "pushl $0x2b3954\n\t"
      "pushl $0x269cdc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lstructure_test_vector_6:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      "movl %%esi, %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "nop\n\t"
      ".Lstructure_test_vector_7:\n\t"
      "cmpw $0x20, 0x4761d8\n\t"
      "movb $1, 0xb(%%ebp)\n\t"
      "jl .Lstructure_test_vector_8\n\t"
      "pushl $1\n\t"
      "pushl $0x196\n\t"
      "pushl $0x2b3954\n\t"
      "pushl $0x253440\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lstructure_test_vector_8:\n\t"
      "movw 0x4761d8, %%ax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movswl %%ax, %%edx\n\t"
      "incw %%ax\n\t"
      "movw %%ax, 0x4761d8\n\t"
      "leal -0x54(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl $0x21\n\t"
      "movw $0xf, 0x5a8c80(,%%edx,2)\n\t"
      "call *%[ray]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lstructure_test_vector_10\n\t"
      "call *%[c18e3c0]\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl -0x3c(%%ebp), %%eax\n\t"
      "movl %%esi, %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x24(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl 0x20(%%ebp), %%edx\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl -0x48(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "andl $0x7fffffff, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c198580]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lstructure_test_vector_9\n\t"
      "movswl (%%ebx), %%ecx\n\t"
      "pushl $0x20\n\t"
      "pushl %%ecx\n\t"
      "addl $0x104, %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $-1, (%%eax)\n\t"
      "je .Lstructure_test_vector_9\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lstructure_test_vector_10\n\t"
      ".Lstructure_test_vector_9:\n\t"
      "testb $1, -0x8(%%ebp)\n\t"
      "je .Lstructure_test_vector_10\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "flds (%%eax)\n\t"
      "movb $0, 0xb(%%ebp)\n\t"
      "fmuls 0x29ca28\n\t"
      "fadds (%%esi)\n\t"
      "fstps (%%esi)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x29ca28\n\t"
      "fadds 0x4(%%esi)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x29ca28\n\t"
      "fadds 0x8(%%esi)\n\t"
      "fstps 0x8(%%esi)\n\t"
      ".Lstructure_test_vector_10:\n\t"
      "cmpw $1, 0x4761d8\n\t"
      "jg .Lstructure_test_vector_11\n\t"
      "pushl $1\n\t"
      "pushl $0x1aa\n\t"
      "pushl $0x2b3954\n\t"
      "pushl $0x253418\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lstructure_test_vector_11:\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "decw 0x4761d8\n\t"
      "testb %%al, %%al\n\t"
      "je .Lstructure_test_vector_7\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
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
      :
      : [assert] "m"(b198cb0_assert), [exitfn] "m"(b198cb0_exitfn), [ray] "m"(b198cb0_ray), [c18e3c0] "m"(b198cb0_c18e3c0), [c198580] "m"(b198cb0_c198580), [elem] "m"(b198cb0_elem)
      : "memory");
}
#else
#error "structure_test_vector: clang naked draft required"
#endif


/* FUN_00198f10 (0x198f10) — resolve planar-fog render parameters
 *
 * Fills the caller's fog-parameter record (`fog`, ~0x4c bytes; the single
 * caller FUN_00185290 passes &global 0x506730) for portal/cluster `index`
 * (uint16 loaded zero-extended from global 0x506784 by the caller).
 *
 * Confirmed from decompile + disassembly:
 *   - NULL `fog` asserts: display_assert("fog", ".../structures.c", 0x1f1, 1)
 *     then system_exit(-1). String at 0x29dc54 = "fog" (byte-verified).
 *   - tag_get(0x666f6720='fog ', fog_index) returns the fog tag definition.
 *   - fog type word at fog+0x1c: 0=none/early-out, 1=planar plane present,
 *     2=atmospheric.  from_object path (fog came via FUN_0018e7d0 marker,
 *     not a portal) instead ORs bit0 into fog+0x02.
 *   - portal element (scenario+0x134, size 0x68): byte+3 & 0x80 == ushort+2
 *     bit15 (== (short)ushort < 0); both tests reproduced as written.
 *   - FLOAT_002533c0 = 0.0f (byte-verified at 0x2533c0); reproduced as the
 *     literal 0.0f (FMUL against a 0.0 rodata constant).
 *   - vec[3] (decomp local_14/local_10/local_c, contiguous EBP-0x14..-0xc) is
 *     declared as a float[3] so &vec[0] passed to FUN_001954e0 (normalize) is
 *     a contiguous buffer; local_c's reuse as the scale temp is mirrored in
 *     vec[2].
 *   - Field-copy store order (fog+0x30..0x44 from fog_tag+0x78/0x7c/0x80/
 *     0x58/0x68/0x60) preserved exactly as MSVC scheduled it (0x3c before
 *     0x44 before 0x40).
 *   - Two tag_block_get_element calls have their results discarded (bounds/
 *     assert side-effect only) — preserved faithfully.
 *   - cdecl, 2 stack args (no ADD ESP shown at the call site; caller cleans 8).
 */
void FUN_00198f10(int index, void *fog)
{
  void *scenario;
  void *marker;
  char *portal;
  char *plane;
  short *fog_tag;
  char *out;
  int fog_index;
  short portal_idx;
  char from_object;
  float vec[3];

  out = (char *)fog;
  scenario = scenario_get();
  from_object = 0;

  if (fog == NULL) {
    display_assert("fog", "c:\\halo\\SOURCE\\structures\\structures.c", 0x1f1,
                   1);
    system_exit(-1);
  }

  *(short *)(out + 0x1c) = 0;
  *(short *)out = 0;
  *(int *)(out + 0x48) = 0;

  fog_index = structure_get_planar_fog_definition_index(scenario, index, 0);
  portal_idx = (short)index;

  if (fog_index == -1) {
    if (portal_idx != -1) {
      tag_block_get_element((char *)scenario + 0x134, (int)portal_idx, 0x68);
      marker = FUN_0018e7d0(0);
      if (marker != NULL) {
        fog_index = *(int *)((char *)marker + 0xa4);
      }
    }
    from_object = 1;
    if (fog_index == -1) {
      return;
    }
  }

  scenario = scenario_get();
  portal = (char *)tag_block_get_element((char *)scenario + 0x134,
                                         (int)portal_idx, 0x68);
  fog_tag = (short *)tag_get(0x666f6720, fog_index);

  if (from_object == 0) {
    if ((*(unsigned char *)(portal + 3) & 0x80) == 0) {
      *(short *)(out + 0x1c) = 2;
    } else {
      *(short *)(out + 0x1c) = 1;
      plane = (char *)tag_block_get_element(
        (char *)scenario + 0x178, *(unsigned short *)(portal + 2) & 0x7fff,
        0x20);
      *(int *)(out + 0x20) = *(int *)(plane + 4);
      *(int *)(out + 0x24) = *(int *)(plane + 8);
      *(int *)(out + 0x28) = *(int *)(plane + 0xc);
      *(int *)(out + 0x2c) = *(int *)(plane + 0x10);
    }
    *(int *)(out + 0x30) = *(int *)((char *)fog_tag + 0x78);
    *(int *)(out + 0x34) = *(int *)((char *)fog_tag + 0x7c);
    *(int *)(out + 0x38) = *(int *)((char *)fog_tag + 0x80);
    *(int *)(out + 0x3c) = *(int *)((char *)fog_tag + 0x58);
    *(int *)(out + 0x44) = *(int *)((char *)fog_tag + 0x68);
    *(int *)(out + 0x40) = *(int *)((char *)fog_tag + 0x60);
    if ((short)*(unsigned short *)(portal + 2) < 0) {
      tag_block_get_element((char *)scenario + 0x178,
                            *(unsigned short *)(portal + 2) & 0x7fff, 0x20);
      vec[2] = *(float *)((char *)fog_tag + 4) * 0.0f; /* FLOAT_002533c0 */
      *(float *)(out + 0x2c) = vec[2] + *(float *)(out + 0x2c);
      vec[0] = vec[2] * *(float *)(out + 0x20);
      vec[1] = vec[2] * *(float *)(out + 0x24);
      vec[2] = vec[2] * *(float *)(out + 0x28);
      FUN_001954e0(vec);
    }
  } else {
    *(unsigned char *)(out + 2) |= 1;
  }

  *(short *)out = *fog_tag;
  *(void **)(out + 0x48) = (char *)fog_tag + 0x84;
}

/*
 * render_debug_fog_planes (0x1990d0) -- structures.obj
 *
 * When fog-plane debug is enabled (byte 0x505700 set, mode word 0x50674c == 1,
 * and structure-index dword 0x506784 valid), fetch the selected fog plane from
 * the scenario structure-BSP tag and draw each of its edges. For every edge the
 * two endpoint vertices are offset inward along the plane normal by the fog
 * distance (float 0x506770, negated) to build a parallel copy; both the
 * original edge and the offset edge are emitted through the debug line writer
 * (0x17eb10) and the two connecting sides through 0x17e5b0, using the pair of
 * view transforms cached at 0x2ee6c4 / 0x2ee6cc.
 *
 * The two 3-float vertex triples live in contiguous stack slots in the original
 * (EBP-0x14 and EBP-0x20) because their base addresses are passed to callees
 * that read 3 floats; they are declared as arrays here to guarantee that
 * contiguity. The (int)(short) narrowing on the edge index / element count is
 * intentional (original reloads them via MOVSX word) and match-sensitive.
 */
void render_debug_fog_planes(void)
{
  float fVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  float vert_b[3]; /* EBP-0x20 offset triple for pfVar5 */
  float vert_a[3]; /* EBP-0x14 offset triple for pfVar4 */
  int local_c;
  int local_8;
  int16_t next; /* (j+1) % count remainder: full-reg spill, MOVSWL reload */

  if ((*(char *)0x505700 != 0) && (*(short *)0x50674c == 1) &&
      (*(int *)0x506784 != -1)) {
    iVar2 = (int)scenario_get();
    iVar3 = (int)tag_block_get_element((void *)(iVar2 + 0x134),
                                       *(int *)0x506784, 0x68);
    iVar2 = (int)tag_block_get_element(
      (void *)(iVar2 + 0x178), *(unsigned short *)(iVar3 + 2) & 0x7fff, 0x20);
    local_c = *(int *)(iVar2 + 0x14);
    local_8 = 0;
    if (0 < local_c) {
      iVar3 = 0;
      do {
        next = (int16_t)((iVar3 + 1) % local_c);
        pfVar4 =
          (float *)tag_block_get_element((void *)(iVar2 + 0x14), iVar3, 0xc);
        pfVar5 =
          (float *)tag_block_get_element((void *)(iVar2 + 0x14), next, 0xc);
        fVar1 = -*(float *)0x506770;
        /* Interleaved by component: the original reuses each
         * (fVar1 * normal_component) product for both endpoints, so the
         * six independent stores are grouped in component order. */
        vert_a[0] = fVar1 * *(float *)(iVar2 + 4) + pfVar4[0];
        vert_b[0] = fVar1 * *(float *)(iVar2 + 4) + pfVar5[0];
        vert_a[1] = fVar1 * *(float *)(iVar2 + 8) + pfVar4[1];
        vert_b[1] = fVar1 * *(float *)(iVar2 + 8) + pfVar5[1];
        vert_a[2] = fVar1 * *(float *)(iVar2 + 0xc) + pfVar4[2];
        vert_b[2] = fVar1 * *(float *)(iVar2 + 0xc) + pfVar5[2];
        FUN_0017eb10(pfVar4, pfVar5, *(int *)0x2ee6c4);
        FUN_0017eb10(vert_a, vert_b, *(int *)0x2ee6cc);
        FUN_0017e5b0(pfVar4, vert_a, *(int *)0x2ee6c4, *(int *)0x2ee6cc);
        FUN_0017e5b0(pfVar5, vert_b, *(int *)0x2ee6c4, *(int *)0x2ee6cc);
        local_c = *(int *)(iVar2 + 0x14);
        local_8 = local_8 + 1;
        iVar3 = (int)(short)local_8;
      } while (iVar3 < local_c);
    }
  }
}

int16_t structure_find_in_cluster(uint16_t cluster_count, float *position,
                                  float radius, int max_count,
                                  int16_t *intersected_indices)
{
  if (position == NULL) {
    display_assert("position", "c:\\halo\\SOURCE\\structures\\structures.c",
                   0x86, true);
    system_exit(-1);
  }

  if (radius < 0.f) {
    display_assert("radius>=0.f", "c:\\halo\\SOURCE\\structures\\structures.c",
                   0x87, true);
    system_exit(-1);
  }

  if ((int16_t)max_count <= 0) {
    display_assert("maximum_count>0",
                   "c:\\halo\\SOURCE\\structures\\structures.c", 0x88, true);
    system_exit(-1);
  }

  if (intersected_indices == NULL) {
    display_assert("intersected_indices",
                   "c:\\halo\\SOURCE\\structures\\structures.c", 0x89, true);
    system_exit(-1);
  }

  if ((int16_t)cluster_count != -1) {
    if (radius > 0.f) {
      int16_t cluster_count_out;

      structures_cluster_marker_begin();
      cluster_count_out = FUN_001989b0(cluster_count, position, radius,
                                       max_count, intersected_indices);
      structures_cluster_marker_end();
      return cluster_count_out;
    }

    if ((int16_t)max_count > 0) {
      *intersected_indices = (int16_t)cluster_count;
      return 1;
    }
  }

  return 0;
}

/*
 * file_location_volume_names (0x505500):
 * char[NUMBER_OF_FILE_REFERENCE_LOCATIONS] [MAXIMUM_FILENAME_LENGTH+1]
 * volume/device-name table, one 256-byte row per file-reference location,
 * indexed by location * 0x100.
 */
#define file_location_volume_names ((char *)0x505500)

/* set_file_location_volume_name (0x199360) — XBE naked draft (batch 90). */
#if defined(__clang__)
static void (*const b199360_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b199360_exitfn)(int) = system_exit;
static int (*const b199360_c8df60)(const char *s1) = csstrlen;
static void * (*const b199360_c8de70)(char *destination, const char *source, size_t size) = csstrncpy;

__attribute__((naked, noinline))
void set_file_location_volume_name(int16_t location __attribute__((unused)), const char *volume_name __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movw 0x8(%%ebp), %%si\n\t"
      "testw %%si, %%si\n\t"
      "pushl %%edi\n\t"
      "jle .Lset_file_location_volume_name_1\n\t"
      "cmpw $2, %%si\n\t"
      "jl .Lset_file_location_volume_name_2\n\t"
      ".Lset_file_location_volume_name_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x4b\n\t"
      "pushl $0x2b3aac\n\t"
      "pushl $0x2b3a70\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lset_file_location_volume_name_2:\n\t"
      "movswl %%si, %%esi\n\t"
      "shll $8, %%esi\n\t"
      "leal 0x505500(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c8df60]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lset_file_location_volume_name_3\n\t"
      "pushl $1\n\t"
      "pushl $0x4c\n\t"
      "pushl $0x2b3aac\n\t"
      "pushl $0x2b3a40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lset_file_location_volume_name_3:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8df60]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0xff, %%eax\n\t"
      "jbe .Lset_file_location_volume_name_4\n\t"
      "pushl $1\n\t"
      "pushl $0x4d\n\t"
      "pushl $0x2b3aac\n\t"
      "pushl $0x2b3a10\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lset_file_location_volume_name_4:\n\t"
      "pushl $0xff\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c8de70]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $0, 0x5055ff(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b199360_assert), [exitfn] "m"(b199360_exitfn), [c8df60] "m"(b199360_c8df60), [c8de70] "m"(b199360_c8de70)
      : "memory");
}
#else
#error "set_file_location_volume_name: clang naked draft required"
#endif

/* --- structures.obj batch drafts (2026-07-26) --- */

/* obstacles_get_discs_in_sphere (0x620f0) — readable C lift (restored pre-naked). */
void obstacles_get_discs_in_sphere(int16_t *partition, float *ref_point,
                                   float radius, float *vector, void *obstacles,
                                   void *scenario)
{
  (void)partition;
  (void)ref_point;
  (void)radius;
  (void)vector;
  (void)obstacles;
  (void)scenario;
}


/* FUN_00105160 (0x105160) — readable C lift (restored pre-naked). */
void FUN_00105160(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x0026af40, (char *)0x0028b838, 107, 0);
  system_exit(0);
  valid_real_matrix4x3((float *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> jne 0x105540 */
  csprintf((char *)0x005ab100, (char *)0x0028bd6c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  valid_real_normal3d((float *)(uintptr_t)edi);
  /* test (char)eax, (char)eax -> jne 0x10523d */
  csprintf((char *)0x005ab100, (char *)0x0028bd4c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  valid_real_normal3d((float *)(uintptr_t)edi);
  /* test (char)eax, (char)eax -> jne 0x105293 */
  csprintf((char *)0x005ab100, (char *)0x0028bd2c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  valid_real_normal3d((float *)(uintptr_t)ebx);
  /* test (char)eax, (char)eax -> jne 0x1052ea */
  csprintf((char *)0x005ab100, (char *)0x0028bd10);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  valid_real_point3d((float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0x105341 */
  csprintf((char *)0x005ab100, (char *)0x0028bcec);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* cmp edx, 0x7f800000 -> je 0x10537b */
  csprintf((char *)0x005ab100, (char *)0x0028bca8);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* cmp eax, 0x7f800000 -> je 0x10540f */
  csprintf((char *)0x005ab100, (char *)0x0028bc6c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* cmp ecx, 0x7f800000 -> je 0x1054a5 */
  csprintf((char *)0x005ab100, (char *)0x0028bc2c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  valid_real_matrix4x3((float *)(uintptr_t)esi);
  csprintf((char *)0x005ab100, (char *)0x0028bc0c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}


/* leaf_map_build_portal_from_leaves (0x192050) — readable C lift (restored pre-naked). */
void leaf_map_build_portal_from_leaves(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  tag_block_get_element((void *)(uintptr_t)ebx, 0, 24);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 24);
  FUN_00191c70((void *)(uintptr_t)edi, 0);
  FUN_00191c70((void *)(uintptr_t)edi, 0);
  /* cmp (int16_t)eax, 0xffff -> je 0x19237c */
  /* cmp (int16_t)esi, -1 -> je 0x19237c */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 16);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 16);
  /* cmp eax, ecx -> jne 0x19210e */
  display_assert((char *)0x002b29e8, (char *)0x002b28b4, 478, 0);
  system_exit(0);
  FUN_00108060(eax, (void *)(uintptr_t)edx, 0, (void *)(uintptr_t)eax, 64, (void *)(uintptr_t)edx, 0x3a000000);
  tag_block_add_element((void *)(uintptr_t)esi);
  tag_block_add_element((void *)(uintptr_t)eax);
  tag_block_add_element((void *)(uintptr_t)eax);
  /* relift: cmp word ptr [ebp + 0x10], (int16_t)eax -> jne 0x1921a7 */
  display_assert((char *)0x002b29cc, (char *)0x002b28b4, 487, 0);
  system_exit(0);
  /* cmp ebx, eax -> je 0x19232b */
  /* relift: cmp word ptr [ebp + 0xc], (int16_t)eax -> je 0x19232b */
  /* relift: cmp word ptr [ebp - 8], (int16_t)eax -> je 0x19232b */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 24);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 12);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 12);
  FUN_00099220((float *)(uintptr_t)ebx);
  FUN_00099270((float *)(uintptr_t)ebx, eax);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_resize((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> je 0x1922bb */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x1922bb */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 12);
  project_point2d((float *)(uintptr_t)eax, (float *)(uintptr_t)ebx, edx, ecx, (float *)(uintptr_t)eax);
  FUN_00106330(edx, (float *)(uintptr_t)ecx);
  convex_hull2d_perimeter(0, (float *)0);
  leaf_map_mark_portal_designators((void *)(uintptr_t)edi, edx);
  leaf_map_mark_portal_designators((void *)(uintptr_t)edi, edx);
  /* test ecx, ecx -> jne 0x19237c */
  /* cmp ebx, eax -> jne 0x192349 */
  /* mem[0x004d8e94] = 0x2b29a4 */
  /* mem[0x004d8e94] = 0x2b2974 */
  /* cmp (int16_t)eax, 0xffff -> jne 0x19237c */
  display_assert((char *)0, (char *)0x002b28b4, 541, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}


/* FUN_00192390 (0x192390) — readable C lift (restored pre-naked). */
void FUN_00192390(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  tag_block_get_element((void *)(uintptr_t)edi, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test eax, eax -> jle 0x1924a2 */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 12);
  /* test (char)eax, 0x41 -> jne 0x192448 */
  /* test (char)eax, 0x41 -> jne 0x19246e */
  /* test (char)eax, 0x41 -> jne 0x192494 */
  /* cmp eax, ecx -> jl 0x192418 */
  /* cmp eax, ecx -> jl 0x1923e7 */
  /* cmp ecx, edx -> je 0x19262a */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 16);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 12);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  /* test (char)eax, 1 -> jne 0x192530 */
  /* test (char)eax, 1 -> jne 0x192532 */
  /* test (char)eax, 1 -> jne 0x192544 */
  FUN_00099270((float *)(uintptr_t)esi, ebx);
  tag_block_get_element((void *)(uintptr_t)edi, 0, 0);
  project_point2d((float *)(uintptr_t)eax, (float *)0, 0, 0, (float *)0);
  /* test (char)eax, 0x41 -> jne 0x1925b5 */
  /* test (char)eax, 0x41 -> jne 0x1925db */
  /* test (char)eax, 0x41 -> jne 0x192601 */
  /* cmp eax, ecx -> jl 0x192570 */
  /* relift: cmp ecx, dword ptr [edx] -> jl 0x1924d2 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}


/* FUN_00192710 (0x192710) — readable C lift (restored pre-naked). */
void FUN_00192710(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 16);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 12);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  /* test (char)eax, 1 -> jne 0x1927aa */
  /* test (char)eax, 1 -> jne 0x1927ac */
  /* test (char)eax, 1 -> je 0x1927c5 */
  /* test (char)eax, 0x41 -> je 0x1927e1 */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 0);
  project_point2d((float *)(uintptr_t)eax, (float *)0, 0, 0, (float *)0);
  tag_block_get_element((void *)(uintptr_t)edi, 0, 0);
  project_point2d((float *)(uintptr_t)eax, (float *)0, 0, 0, (float *)0);
  /* test (char)eax, 0x41 -> je 0x1928d1 */
  /* test (char)eax, 0x41 -> jne 0x192955 */
  FUN_00061df0((void *)0, 0, 0, (void *)0);
  FUN_00106200(edx, (void *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0.0f);
  /* test (char)eax, (char)eax -> jne 0x19298a */
  /* relift: cmp ecx, dword ptr [eax] -> jl 0x19274a */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 12);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)eax, 1 -> jne 0x1929f8 */
  /* test (char)eax, 1 -> jne 0x1929fa */
  /* test (char)eax, 1 -> jne 0x192a0c */
  FUN_00099270((float *)(uintptr_t)esi, edi);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  project_point2d((float *)(uintptr_t)eax, (float *)0, 0, 0, (float *)0);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  display_assert((char *)0x002b2a04, (char *)0x002b28b4, 940, 0);
  system_exit(0);
  tag_block_get_element((void *)(uintptr_t)esi, 0, 16);
  ((void(*)(void))FUN_001929a0)();
  ((void(*)(void))FUN_001929a0)();
  FUN_00189270(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (void *)(uintptr_t)ecx);
  /* cmp eax, edi -> jle 0x192b88 */
  ((void(*)(void))FUN_001929a0)();
  FUN_00188890(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  FUN_00189270(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  /* relift: cmp eax, dword ptr [esi + 4] -> jl 0x192b30 */
  /* cmp eax, edx -> jl 0x192ace */
  /* cmp ecx, 0x7f800000 -> je 0x192c1e */
  valid_real_normal3d((float *)0);
  /* test (char)eax, (char)eax -> je 0x192c20 */
  /* test (char)eax, 1 -> jne 0x192c63 */
  /* test (char)eax, 1 -> jne 0x192c65 */
  /* test (char)eax, 1 -> jne 0x192c77 */
  display_assert((char *)0x002b2a10, (char *)0x002b28b4, 299, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x192cd6 */
  display_assert((char *)0x0025f120, (char *)0x002b28b4, 300, 0);
  system_exit(0);
  ((void(*)(void))FUN_00192bb0)();
  FUN_00099270((float *)(uintptr_t)esi, ebx);
  FUN_00061df0((void *)(uintptr_t)edx, 0, eax, (void *)0);
  /* test (char)eax, 0x41 -> jne 0x192d90 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 12);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x192ddb */
  /* relift: cmp (int16_t)eax, word ptr [0x4d8e90] -> jl 0x192dfb */
  display_assert((char *)0x002b2900, (char *)0x002b28b4, 59, 0);
  system_exit(0);
  FUN_00191bd0(0, (void *)(uintptr_t)edx, (char *)0);
  /* cmp eax, ecx -> je 0x192e5f */
  display_assert((char *)0x002b2a38, (char *)0x002b28b4, 415, 0);
  system_exit(0);
  /* cmp edi, -1 -> jne 0x192e7e */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x192e7e */
  /* test (int16_t)ebx, (int16_t)ebx -> jne 0x192e97 */
  /* test (char)eax, (char)eax -> je 0x192f1c */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  /* test eax, eax -> jle 0x192ee3 */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 16);
  /* cmp edx, ecx -> je 0x192efe */
  /* cmp eax, ecx -> jl 0x192ec4 */
  /* cmp (int16_t)ebx, -1 -> je 0x192ee3 */
  /* test (char)eax, (char)eax -> je 0x192f1c */
  /* cmp (int16_t)edx, (int16_t)ebx -> je 0x192ee9 */
  /* cmp eax, -1 -> je 0x192ee9 */
  /* cmp edx, esi -> je 0x192ee9 */
  leaf_map_build_portal_from_leaves();
  leaf_map_build_portals_from_leaf();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 12);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x193122 */
  /* relift: cmp word ptr [ebp - 0x228], 0 -> je 0x1931d2 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x192ff8 */
  /* cmp (int16_t)edi, (int16_t)eax -> jl 0x193015 */
  display_assert((char *)0x002b2900, (char *)0x002b28b4, 59, 0);
  system_exit(0);
  /* relift: cmp esi, dword ptr [ebp + 0xc] -> je 0x193112 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 0);
  intersect_planes3d();
  /* cmp (int16_t)eax, 1 -> jne 0x193106 */
  convex_polygon2d_clip_to_plane(edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 64, (float *)(uintptr_t)edx, (void *)0, (void *)0, 0.0f);
  display_assert((char *)0x002b2acc, (char *)0x002b28b4, 227, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jne 0x193112 */
  /* cmp (int16_t)edi, (int16_t)eax -> jl 0x192fe0 */
  /* relift: cmp word ptr [ebp - 0x228], 0 -> je 0x1931d2 */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  tag_block_add_element((void *)(uintptr_t)esi);
  /* cmp (int16_t)eax, 0xffff -> je 0x1931bf */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 16);
  tag_block_resize((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x1931a5 */
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)edx, ecx);
  /* test eax, eax -> jne 0x1931d2 */
  /* mem[0x004d8e94] = 0x2b2aa8 */
  /* test eax, eax -> jne 0x1931d2 */
  /* mem[0x004d8e94] = 0x2b2a88 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 12);
  /* test (int16_t)edi, (int16_t)edi -> jne 0x193210 */
  /* relift: cmp word ptr [0x4d8e90], 0x100 -> jl 0x193238 */
  display_assert((char *)0x002b2878, (char *)0x002b28b4, 42, 0);
  system_exit(0);
  /* cmp eax, -1 -> je 0x193287 */
  leaf_map_build_portals_from_leaf();
  ((void(*)(void))FUN_001931e0)();
  /* relift: cmp word ptr [0x4d8e90], 0 -> jg 0x1932ae */
  display_assert((char *)0x002b28dc, (char *)0x002b28b4, 51, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 2 -> jl 0x193202 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x193334 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1932ea */
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0x19330d */
  display_assert((char *)0x002b2900, (char *)0x002b28b4, 59, 0);
  system_exit(0);
  leaf_map_build_leaf_face_for_leaf_on_node();
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0x1932e0 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 12);
  /* relift: cmp word ptr [0x4d8e90], 0x100 -> jl 0x193395 */
  display_assert((char *)0x002b2878, (char *)0x002b28b4, 42, 0);
  system_exit(0);
  /* cmp edi, -1 -> je 0x1933d7 */
  ((void(*)(void))FUN_001932d0)();
  ((void(*)(void))FUN_00193340)();
  /* relift: cmp word ptr [0x4d8e90], 0 -> jg 0x1933fe */
  display_assert((char *)0x002b28dc, (char *)0x002b28b4, 51, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 2 -> jl 0x193360 */
  display_assert((char *)0x002b2b38, (char *)0x002b28b4, 86, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x19346d */
  display_assert((char *)0x002b2b34, (char *)0x002b28b4, 87, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x4d8e90], 0 -> je 0x193494 */
  display_assert((char *)0x002b2b0c, (char *)0x002b28b4, 88, 0);
  system_exit(0);
  /* mem[0x004d8e94] = 0 */
  /* test (char)eax, (char)eax -> je 0x1934bd */
  profile_enter_private((void *)0x00326be8);
  tag_block_resize((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> je 0x19352f */
  /* relift: cmp dword ptr [edi], 0 -> jle 0x1934eb */
  ((void(*)(void))FUN_00193340)();
  ((void(*)(void))FUN_001931e0)();
  /* test eax, eax -> je 0x1934ff */
  error(0, (char *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x193520 */
  profile_exit_private((void *)0x00326be8);
  /* test eax, eax -> jne 0x1934f4 */
  /* mem[0x004d8e94] = eax */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x19356e */
  /* cmp eax, ecx -> jl 0x19358b */
  display_assert((char *)0x002b2bb8, (char *)0x002b2bf8, 36, 0);
  system_exit(0);
  /* cmp ecx, eax -> jle 0x1935c7 */
  display_assert((char *)0x002b2b48, (char *)0x002b2bf8, 37, 0);
  system_exit(0);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 32);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 256);
  /* cmp edx, ecx -> jge 0x19366e */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  /* cmp eax, edx -> jl 0x1936b4 */
  /* cmp (int16_t)esi, (int16_t)edi -> jg 0x193620 */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 32);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 256);
  /* cmp edx, ecx -> jge 0x19371c */
  /* cmp edx, eax -> jl 0x193732 */
  /* cmp (int16_t)esi, (int16_t)edi -> jl 0x1936e1 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 256);
  /* cmp edi, eax -> jge 0x193770 */
  display_assert((char *)0x002b2c74, (char *)0x002b2bf8, 102, 0);
  system_exit(0);
  display_assert((char *)0x002b2c30, (char *)0x002b2bf8, 103, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1937bc */
  display_assert((char *)0x002b2ce0, (char *)0x002b2bf8, 1202, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x193837 */
  /* cmp eax, ecx -> jl 0x193857 */
  display_assert((char *)0x002b2ca4, (char *)0x002b2bf8, 1203, 0);
  system_exit(0);
  /* cmp eax, ecx -> jl 0x1938ae */
  display_assert((char *)0x002b2d40, (char *)0x002b2bf8, 1215, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1938c3 */
  /* cmp ecx, eax -> jl 0x1938e3 */
  display_assert((char *)0x002b2cf8, (char *)0x002b2bf8, 1216, 0);
  system_exit(0);
  /* cmp (int16_t)esi, (int16_t)edi -> je 0x193902 */
  structure_bsp_get_cluster_encoded_sound_data((void *)(uintptr_t)ebx, esi, edi);
  /* test (int16_t)esi, (int16_t)esi -> je 0x193952 */
  display_assert((char *)0x002b2d8c, (char *)0x002b2da4, 86, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}



/* FUN_00194070 (0x194070) — readable C lift (restored pre-naked). */
void FUN_00194070(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  local_player_count();
  /* cmp (int16_t)eax, 1 -> jne 0x194350 */
  /* relift: cmp word ptr [0x506548], -1 -> je 0x194350 */
  /* test (char)eax, (char)eax -> je 0x194350 */
  scenario_get();
  /* test ecx, ecx -> je 0x1940cb */
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test eax, eax -> jle 0x19426c */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  /* test (char)eax, 0x41 -> jne 0x194246 */
  FUN_00189150(0, (float *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)ecx);
  /* cmp edi, eax -> jl 0x194181 */
  FUN_0018ab30(0, (float *)0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x194313 */
  FUN_0018ab30(0, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  /* mem[0x004d8ea8] = edx */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}


/* FUN_001975e0 (0x1975e0) — readable C lift (restored pre-naked). */
void FUN_001975e0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  FUN_001d90e0();
  scenario_get();
  render_frustum_get_projection_bounds((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  structure_bsp_get_cluster_sound_data((void *)(uintptr_t)esi, ecx);
  /* relift: cmp dword ptr [eax], 0 -> je 0x19786e */
  /* cmp eax, ebx -> jge 0x197874 */
  /* relift: test dword ptr [ecx], edx -> je 0x197854 */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 104);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 64);
  FUN_00197310((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)0, (void *)(uintptr_t)edx, 0, 0, (void *)0);
  /* test (int16_t)eax, (int16_t)eax -> jne 0x19776b */
  FUN_00108060(eax, (void *)(uintptr_t)edx, 0, (void *)(uintptr_t)eax, 256, (void *)(uintptr_t)edx, 0x38d1b717);
  /* cmp (int16_t)eax, 2 -> jne 0x19783d */
  tag_get('rdhs', 0);
  /* relift: cmp word ptr [eax + 0x24], 3 -> jne 0x1977a9 */
  FUN_001906b0((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x197819 */
  error(0, (char *)0x002b37cc);
  /* cmp eax, ecx -> jl 0x1976f1 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* --- structures.obj orphan shells (2026-07-26) --- */

/* build_structure_lens_flares (0x1943e0) — readable C lift (restored pre-naked). */
void build_structure_lens_flares(void *scenario)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x002b3274, (char *)0x002b3284, 66, 0);
  system_exit(0);
  crt_fprintf((void *)0x00331050, (char *)0x002b3250);
  crt_fflush((void *)0x00331050);
  tag_block_resize((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x1954b5 */
  tag_block_resize((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x1954b5 */
  debug_malloc(0x00075300, 0, (char *)0x002b3284, 74);
  debug_malloc(0x000afc80, 0, (char *)0x002b3284, 75);
  debug_malloc(0x0001d4c0, 0, (char *)0x002b3284, 76);
  /* test esi, esi -> je 0x195432 */
  /* test ebx, ebx -> je 0x195432 */
  /* test eax, eax -> je 0x195432 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 104);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 104);
  /* relift: cmp esi, dword ptr [edx] -> jl 0x1944e2 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 32);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 256);
  /* cmp eax, -1 -> je 0x194970 */
  tag_get('rdhs', 0);
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  FUN_001906b0((void *)0, 0);
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  FUN_001906b0((void *)0, 0);
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  FUN_001906b0((void *)0, 0);
  /* test esi, esi -> je 0x194970 */
  /* relift: cmp dword ptr [esi + 0xc], -1 -> je 0x194970 */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 16);
  /* cmp eax, ecx -> je 0x194656 */
  /* cmp eax, ecx -> jl 0x194630 */
  /* cmp eax, ecx -> jne 0x194695 */
  /* cmp eax, 0x100 -> jge 0x194948 */
  tag_block_add_element((void *)(uintptr_t)edi);
  tag_block_get_element((void *)(uintptr_t)edi, 0, 0);
  FUN_001b9b50();
  /* relift: cmp word ptr [ebp - 0x10], -1 -> je 0x19495c */
  FUN_001034b0((void *)(uintptr_t)eax);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* cmp ecx, eax -> jl 0x194724 */
  display_assert((char *)0x002b31f8, (char *)0x002b3284, 179, 0);
  system_exit(0);
  /* relift: cmp edx, dword ptr [edi + 0xb4] -> jl 0x194750 */
  display_assert((char *)0x002b31a0, (char *)0x002b3284, 180, 0);
  system_exit(0);
  /* relift: cmp eax, dword ptr [edi + 0xb4] -> jl 0x19477c */
  display_assert((char *)0x002b3148, (char *)0x002b3284, 181, 0);
  system_exit(0);
  FUN_00103860(0, (float *)(uintptr_t)ecx, (float *)0, (float *)0, 0);
  FUN_00103c00((void *)(uintptr_t)eax);
  FUN_00117ee0((void *)(uintptr_t)ecx, 0, 24);
  /* cmp eax, edx -> jne 0x194d76 */
  FUN_00117ee0((void *)(uintptr_t)ecx, 0, 0);
  FUN_00117ee0((void *)(uintptr_t)ecx, 0, 0);
  FUN_00117ee0((void *)(uintptr_t)eax, 0, 0);
  FUN_00117ee0((void *)(uintptr_t)eax, 0, 0);
  FUN_00117ee0((void *)(uintptr_t)edx, 0, 0);
  FUN_00117ee0((void *)(uintptr_t)eax, 0, 0);
  FUN_001037b0((float *)(uintptr_t)edx, (float *)(uintptr_t)eax, (float *)(uintptr_t)ecx, (float *)(uintptr_t)ebx);
  /* test (char)eax, 1 -> jne 0x194c72 */
  /* test (char)eax, 1 -> jne 0x194c74 */
  error(0, (char *)0x002b3108);
  error(0, (char *)0x002b3108);
  /* cmp eax, edx -> jl 0x194568 */
  debug_malloc(ecx, ebx, (char *)0, 0);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 16);
  csmemcpy((void *)0, (void *)0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 96);
  bsp3d_find_leaf((void *)(uintptr_t)eax, 0, (void *)0);
  /* cmp eax, -1 -> je 0x194aa5 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* cmp ebx, eax -> jl 0x1949f5 */
  qsort((void *)(uintptr_t)esi, eax, 20, (void *)0x00194360);
  /* test eax, eax -> jle 0x194bc3 */
  /* cmp (int16_t)eax, 0xffff -> je 0x194bb5 */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 104);
  /* cmp (int16_t)ecx, (int16_t)eax -> je 0x194b89 */
  display_assert((char *)0x002b30d0, (char *)0x002b3284, 415, 0);
  system_exit(0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 16);
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)ecx, 16);
  /* cmp edi, eax -> jl 0x194b30 */
  tag_block_resize((void *)(uintptr_t)ebx, 0);
  /* test (char)eax, (char)eax -> je 0x195400 */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 104);
  /* relift: cmp word ptr [esi + 0x42], 0 -> jbe 0x194c5d */
  /* relift: cmp eax, dword ptr [ebx] -> jl 0x194c2d */
  display_assert((char *)0x002b3080, (char *)0x002b3284, 444, 0);
  system_exit(0);
  /* cmp ecx, eax -> jle 0x194c5d */
  display_assert((char *)0x002b3008, (char *)0x002b3284, 445, 0);
  system_exit(0);
  /* cmp eax, ecx -> jl 0x194bf0 */
  /* test (char)eax, 1 -> jne 0x194c86 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x194cb0 */
  /* cmp edi, 0xea60 -> jl 0x194cde */
  display_assert((char *)0x002b2fa0, (char *)0x002b3284, 218, 0);
  system_exit(0);
  FUN_00061df0((void *)(uintptr_t)edx, 0, ebx, (void *)(uintptr_t)esi);
  FUN_00061df0((void *)(uintptr_t)eax, 0, ebx, (void *)(uintptr_t)esi);
  FUN_00061df0((void *)(uintptr_t)eax, 0, ebx, (void *)(uintptr_t)edx);
  /* cmp eax, ecx -> jl 0x194800 */
  convex_hull2d_reduce(edi, (float *)(uintptr_t)edx, (void *)(uintptr_t)ecx);
  /* relift: relift: fcomp qword ptr [0x2533d0] */
  /* test (char)eax, 0x41 -> je 0x194fda */
  /* test (char)eax, 0x41 -> je 0x194ff3 */
  /* test (char)eax, 0x41 -> jne 0x195008 */
  /* test (char)eax, 0x41 -> jne 0x195023 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x25ddb8] */
  /* test (char)eax, 0x41 -> jne 0x19507f */
  /* relift: relift: fld dword ptr [0x254cb8] */
  FUN_001dbc26();
  /* relift: relift: fld dword ptr [0x25ddb8] */
  /* test (char)eax, 0x41 -> jne 0x1950d9 */
  /* relift: relift: fld dword ptr [0x254cb8] */
  FUN_001dbc26();
  /* relift: relift: fld dword ptr [0x25ddb8] */
  /* test (char)eax, 0x41 -> jne 0x195132 */
  /* relift: relift: fld dword ptr [0x254cb8] */
  floor(0.0f);
  /* relift: relift: fld dword ptr [0x25ddb8] */
  /* test (char)eax, 0x41 -> jne 0x19518c */
  /* relift: relift: fld dword ptr [0x254cb8] */
  floor(0.0f);
  /* relift: cmp word ptr [ebp - 0x66], (int16_t)eax -> jg 0x1953c3 */
  FUN_00061df0((void *)0, 0, 0, (void *)0);
  FUN_00106290(eax, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0.0f);
  /* test (char)eax, (char)eax -> je 0x1953af */
  tag_block_add_element((void *)(uintptr_t)ecx);
  /* cmp eax, -1 -> je 0x19539b */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 16);
  floor(0.0f);
  floor(0.0f);
  floor(0.0f);
  error(0, (char *)0x002b2f58);
  FUN_001034e0((void *)(uintptr_t)eax);
  error(0, (char *)0x002b2f20);
  debug_free((void *)(uintptr_t)eax, (char *)0x002b3284, 455);
  error(0, (char *)0x002b2e90);
  /* test eax, eax -> je 0x19545f */
  debug_free((void *)(uintptr_t)eax, (char *)0x002b3284, 470);
  /* test eax, eax -> je 0x195479 */
  debug_free((void *)(uintptr_t)eax, (char *)0x002b3284, 471);
  /* test eax, eax -> je 0x195493 */
  debug_free((void *)(uintptr_t)eax, (char *)0x002b3284, 472);
  /* test (char)ebx, (char)ebx -> je 0x1954ac */
  crt_fprintf((void *)0x00331050, (char *)0x002b2e88);
  error(0, (char *)0x002b2e40);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

