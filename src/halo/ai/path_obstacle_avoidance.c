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

/* 0x60c80 — append or reuse a path obstacle-avoidance step */
int16_t path_add_step(void *path, float *target_point, int16_t zone_index,
                      char surface_flag, float step_cost, int16_t parent_step)
{
  int16_t step_count;
  int16_t step_index;
  char *step;
  char *new_step;
  float delta[2];

  step_count = *(int16_t *)((char *)path + 0x2c);
  if (step_count >= 0x80)
    return -1;

  delta[0] = *(float *)((char *)path + 0x10) - target_point[0];
  delta[1] = *(float *)((char *)path + 0x14) - target_point[1];

  if (parent_step != -1) {
    step_index = parent_step;
    for (;;) {
      if (step_index < 0 || step_index >= step_count)
        break;
      step = (char *)FUN_000600f0(path, step_index);
      if (*(int16_t *)(step + 0x18) != zone_index) {
        if (*(int16_t *)((char *)path + 0x1c) != zone_index)
          return -1;
        break;
      }
      if (*(char *)(step + 0x1a) != surface_flag)
        return -1;
      if (*(int16_t *)(step + 0x24) == -1)
        break;
      step_index = *(int16_t *)(step + 0x24);
    }
  }

  new_step = (char *)FUN_000600f0(path, step_count);
  *(int16_t *)((char *)path + 0x2c) = step_count + 1;
  *(float *)(new_step + 0xc) = delta[0];
  *(float *)(new_step + 0x10) = delta[1];
  *(float *)(new_step + 0x20) = step_cost;
  *(int16_t *)(new_step + 0x18) = zone_index;
  *(char *)(new_step + 0x1a) = surface_flag;
  *(int16_t *)(new_step + 0x24) = parent_step;
  csmemset(new_step + 0x1c, 0xff, 4);

  if (*(char *)((char *)path + 0x29) != 0) {
    if (*(float *)(new_step + 0x14) > *(float *)((char *)path + 0x24)) {
      *(float *)((char *)path + 0x24) = *(float *)(new_step + 0x14);
      *(int16_t *)((char *)path + 0x20) = parent_step;
    }
  }

  if (!FUN_00060910(path, step_count)) {
    display_assert("heap_addition_succeeded",
                   "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 420, 1);
    system_exit(-1);
  }
  return parent_step;
}

/* 0x60ea0 — initialize avoidance record and seed first step */
void FUN_00060ea0(void *avoidance_record, float *end_point, void *param_2, void *scenario, unsigned char param_4, float radius, float *start_point, int param_7, float param_8, unsigned char param_9, unsigned char param_10)
{
  int16_t disc_index;
  int16_t link_index;
  void *obstacles;

  (void)param_7;
  (void)param_8;

  *(float *)avoidance_record = end_point[0];
  *(unsigned char *)((char *)avoidance_record + 4) = param_4;
  *(void **)((char *)avoidance_record + 8) = param_2;
  *(void **)((char *)avoidance_record + 0xc) = scenario;
  *(float *)((char *)avoidance_record + 0x10) = start_point[0];
  *(float *)((char *)avoidance_record + 0x14) = start_point[1];
  *(void **)((char *)avoidance_record + 0x18) = end_point;
  *(int16_t *)((char *)avoidance_record + 0x1c) = -1;
  *(int16_t *)((char *)avoidance_record + 0x1e) = -1;
  *(int16_t *)((char *)avoidance_record + 0x20) = -1;
  *(uint32_t *)((char *)avoidance_record + 0x24) = 0x7f7fffffU;
  *(unsigned char *)((char *)avoidance_record + 0x28) = 0;
  *(unsigned char *)((char *)avoidance_record + 0x29) = param_9;
  *(unsigned char *)((char *)avoidance_record + 0x2a) = param_10;
  *(int16_t *)((char *)avoidance_record + 0x2c) = 0;
  *(int16_t *)((char *)avoidance_record + 0x1430) = 0;

  obstacles = *(void **)((char *)avoidance_record + 8);
  disc_index =
      FUN_00062410(obstacles, -1, end_point, radius);
  if (disc_index == -1)
    link_index = -1;
  else
    link_index = FUN_000600c0(obstacles, disc_index);
  *(int16_t *)((char *)avoidance_record + 0x1c) = link_index;

  path_add_step(avoidance_record, end_point, link_index, 0, 0.0f, -1);
}

/* 0x61080 */
void FUN_00061080(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test (char)eax, (char)eax -> je 0x610af */
  /* test (char)eax, (char)eax -> jne 0x611e1 */
  structure_test_ray2d((void *)(uintptr_t)edx, ecx, (float *)(uintptr_t)edi, 0, (float *)(uintptr_t)ebx, 0.0f, (void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x610f2 */
  /* test (char)eax, 0x41 -> jne 0x610f2 */
  perpendicular2d((float *)(uintptr_t)ebx, (float *)(uintptr_t)edx);
  structure_test_ray2d((void *)0, 0, (float *)0, 0, (float *)0, 0.0f, (void *)0);
  structure_test_ray2d((void *)(uintptr_t)edx, ecx, (float *)(uintptr_t)eax, 0, (float *)(uintptr_t)ebx, 0.0f, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x6116c */
  /* test (char)eax, 0x41 -> jne 0x6116c */
  structure_test_ray2d((void *)0, 0, (float *)0, 0, (float *)0, 0.0f, (void *)0);
  structure_test_ray2d((void *)(uintptr_t)ecx, eax, (float *)(uintptr_t)edx, 0, (float *)(uintptr_t)ebx, 0.0f, (void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x611e1 */
  /* test (char)eax, 0x41 -> jne 0x611e1 */
  FUN_000624b0((void *)(uintptr_t)eax, 0, (float *)(uintptr_t)edi, (float *)(uintptr_t)ebx, 0.0f, 0.0f, edx, (void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x61231 */
  /* test (char)eax, 0x41 -> jne 0x61231 */
  /* relift: cmp dword ptr [esi + 8], eax -> jne 0x6124a */
  /* relift: cmp word ptr [esi + 0xc], (int16_t)eax -> jne 0x6124a */
  structure_test_ray2d((void *)(uintptr_t)ecx, eax, (float *)(uintptr_t)edi, 0, (float *)(uintptr_t)ebx, 0.0f, (void *)(uintptr_t)eax);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x61280 */
void path_add_steps(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp (int16_t)edi, (int16_t)eax -> jge 0x612a5 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x612c2 */
  display_assert((char *)0x0025e9b0, (char *)0x0025ea14, 40, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 0x80 -> jle 0x61301 */
  display_assert((char *)0x0025ec60, (char *)0x0025ea14, 594, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)edx, 0, ecx);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x6132e */
  /* relift: cmp (int16_t)ebx, word ptr [eax + 2] -> jl 0x6134e */
  display_assert((char *)0x0025ec18, (char *)0x0025ea14, 597, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x613b1 */
  /* cmp (int16_t)edi, (int16_t)eax -> jge 0x613b1 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x613d1 */
  display_assert((char *)0x0025e930, (char *)0x0025e990, 396, 0);
  system_exit(0);
  FUN_000625a0((void *)(uintptr_t)edx, 0, (float *)(uintptr_t)ecx, 0.0f, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  FUN_00061080();
  /* cmp (int16_t)edi, -1 -> je 0x61501 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x61487 */
  /* relift: cmp (int16_t)edi, word ptr [eax + 2] -> jl 0x614a7 */
  display_assert((char *)0x0025ebd0, (char *)0x0025ea14, 625, 0);
  system_exit(0);
  /* test edx, eax -> jne 0x61501 */
  display_assert((char *)0x0025ebb0, (char *)0x0025ea14, 631, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> jne 0x6158b */
  /* relift: cmp word ptr [ebp - 0x26], (int16_t)edx -> je 0x6158b */
  structure_test_ray2d((void *)(uintptr_t)ecx, eax, (float *)(uintptr_t)edi, 0, (float *)(uintptr_t)ebx, 0.0f, (void *)0);
  path_add_step((void *)(uintptr_t)edi, (float *)(uintptr_t)ecx, 0, 0, 0.0f,
                (int16_t)ebx);
  /* relift: cmp word ptr [ebp - 8], 0 -> jg 0x61378 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)ebp;
}

/* 0x615b0 */
int FUN_000615b0(void *avoidance_record)
{
  int16_t step_index;
  char *step;
  float target_point[2];
  float step_cost;
  float scale;

  step_index = FUN_00060970(avoidance_record);
  if (step_index == -1)
    return 0;

  step = (char *)FUN_000600f0(avoidance_record, step_index);
  if (*(int16_t *)(step + 0x24) == -1)
    scale = *(float *)((char *)avoidance_record + 0x18);
  else
    scale = *(float *)(step + 0x20) - *(float *)(step + 0x14) +
            *(float *)((char *)avoidance_record + 0x18);

  target_point[0] = *(float *)(step + 0xc) * scale + *(float *)step;
  target_point[1] = *(float *)(step + 0x10) * scale + *(float *)(step + 4);
  step_cost = *(float *)(step + 0x20) - *(float *)(step + 0x14) + scale;

  path_add_step(avoidance_record, target_point,
                *(int16_t *)((char *)avoidance_record + 0x1c), 0, step_cost,
                -1);
  *(int16_t *)((char *)avoidance_record + 0x1e) = step_index;
  return 0;
}

/* 0x616e0 */
void FUN_000616e0(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  scenario_get();
  FUN_00060ea0((void *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)0, (void *)0, 0, 0.0f, (float *)0, 0, 0.0f, 0, 0);
  FUN_000615b0((void *)0);
  /* test (char)eax, (char)eax -> jne 0x61710 */
  /* relift: cmp word ptr [esi + 0x1e], (int16_t)ecx -> je 0x61733 */
  /* cmp (int16_t)eax, (int16_t)ecx -> je 0x61740 */

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x61750 */
char FUN_00061750(unsigned int param_1, int param_2, void *param_3, int *param_4, void *param_5, char *param_6)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001d90e0();
  global_collision_bsp_get();
  /* test (char)eax, 0x41 -> jne 0x61781 */
  /* test (char)ecx, (char)ecx -> jne 0x617d0 */
  display_assert((char *)0x0025ed20, (char *)0x0025ea14, 761, 0);
  system_exit(0);
  /* test (int16_t)edx, (int16_t)edx -> jle 0x61827 */
  /* test eax, eax -> je 0x618e4 */
  /* test (char)ecx, (char)ecx -> je 0x618e4 */
  /* relift: cmp (int16_t)edx, word ptr [eax + 0x1458a] -> jl 0x6195d */
  FUN_00061d80((void *)(uintptr_t)ecx);
  obstacles_get_discs_in_sphere();
  /* test (char)ecx, (char)ecx -> je 0x61932 */
  FUN_00062020((void *)(uintptr_t)ecx, eax, 0, (float *)(uintptr_t)edx, ecx);
  FUN_000628b0((void *)(uintptr_t)eax, edx);
  /* test eax, eax -> je 0x6195d */
  /* test (char)ecx, (char)ecx -> jne 0x6195d */
  scenario_get();
  FUN_00060ea0((void *)(uintptr_t)eax, (float *)(uintptr_t)eax, (void *)0, (void *)0, 0, 0.0f, (float *)0, 0, 0.0f, 0, 0);
  FUN_000615b0((void *)0);
  /* test (char)eax, (char)eax -> jne 0x61993 */
  /* relift: cmp word ptr [ebx + 0x1e], (int16_t)ecx -> je 0x619ad */
  /* cmp (int16_t)eax, (int16_t)ecx -> je 0x619ba */
  /* test (char)eax, (char)eax -> jne 0x61a04 */
  /* relift: cmp word ptr [eax + 4], 0 -> jle 0x61bd8 */
  FUN_000616e0();
  /* test (char)eax, (char)eax -> je 0x61bd8 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x61a47 */
  /* cmp (int16_t)esi, (int16_t)eax -> jge 0x61a47 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x61a64 */
  display_assert((char *)0x0025e9b0, (char *)0x0025ea14, 40, 0);
  system_exit(0);
  collision_surface_project_point2d(0, 0, 0, 0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  /* test (int16_t)esi, (int16_t)esi -> je 0x61b55 */
  /* cmp (int16_t)esi, (int16_t)eax -> jge 0x61ac9 */
  /* cmp (int16_t)eax, 0x80 -> jle 0x61ae6 */
  display_assert((char *)0x0025e9b0, (char *)0x0025ea14, 40, 0);
  system_exit(0);
  collision_surface_project_point2d(0, 0, 0, 0, (float *)(uintptr_t)esi, (float *)(uintptr_t)edi);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x61b1e */
  /* relift: cmp (int16_t)esi, word ptr [ebx + 0x2c] -> jl 0x61b3e */
  display_assert((char *)0x0025ecd0, (char *)0x0025ea14, 875, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp - 8], 0x80 -> jge 0x61b51 */
  /* test (int16_t)esi, (int16_t)esi -> jne 0x61aa0 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
