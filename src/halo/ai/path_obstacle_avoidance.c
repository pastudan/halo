/* path_obstacle_avoidance.c — AI path obstacle-avoidance helpers.
 *
 * Corresponds to path_obstacle_avoidance.obj.
 *
 * Recovered by lifting from cachebeta.xbe (v01.10.12.2276).
 */
#include "../../common.h"

/*
 * FUN_00060c40 -- valid_real_point2d: returns true when both components of a
 * real_point2d (x, y) are finite (neither NaN nor +/-Inf).
 *
 * A float is non-finite iff its IEEE-754 exponent field is all ones, i.e.
 * (bits & 0x7f800000) == 0x7f800000. The original materializes the boolean
 * in full EAX (MOV EAX,1 / XOR EAX,EAX); Ghidra collapsed the two returns to
 * void because callers discarded the result. Same 0x7f800000 mask idiom as
 * valid_real_rgb_color.
 *
 * ABI: cdecl, one stack pointer arg (real_point2d*), pure integer leaf.
 *
 * Shape (delinked 00060c40.obj): each component is copied into a float local
 * first, then bit-tested through the local — VC71 spills the local into the
 * dead param home slot ([EBP+8], MOV [EBP+8],ECX / MOV [EBP+8],EAX), keeping
 * the frame at zero locals. Testing point[N]'s bits directly loses those
 * stores (59.5%); the local recovers them. The tests are spelled as a nested
 * valid-chain (`!= mask` guarding inward, shared `return 0` tail) so both
 * branches compile to JE into the trailing XOR EAX block — goto/early-return
 * spellings made VC71 flip the second branch (85.7%). 100.0% VC71.
 */
int valid_real_point2d(float *point)
{
  float v;

  v = point[0];
  if ((*(uint32_t *)&v & 0x7f800000) != 0x7f800000) {
    v = point[1];
    if ((*(uint32_t *)&v & 0x7f800000) != 0x7f800000)
      return 1;
  }
  return 0;
}
/* --- path_obstacle_avoidance.obj batch drafts (2026-07-26) --- */

/* 0x60c80 */
void path_add_step(void)
{

}

/* 0x60ea0 */
void FUN_00060ea0(void *avoidance_record, float *end_point, void *param_2, void *scenario, unsigned char param_4, float radius, float *start_point, int param_7, float param_8, unsigned char param_9, unsigned char param_10)
{
  (void)avoidance_record;
  (void)end_point;
  (void)param_2;
  (void)scenario;
  (void)param_4;
  (void)radius;
  (void)start_point;
  (void)param_7;
  (void)param_8;
  (void)param_9;
  (void)param_10;
}

/* 0x61080 */
void FUN_00061080(void)
{

}

/* 0x61280 */
void path_add_steps(void)
{

}

/* 0x615b0 */
int FUN_000615b0(void *avoidance_record)
{
  (void)avoidance_record;
  return 0;
}

/* 0x616e0 */
void FUN_000616e0(void)
{

}

/* 0x61750 */
char FUN_00061750(unsigned int param_1, int param_2, void *param_3, int *param_4, void *param_5, char *param_6)
{
  (void)param_1;
  (void)param_2;
  (void)param_3;
  (void)param_4;
  (void)param_5;
  (void)param_6;
  return 0;
}
