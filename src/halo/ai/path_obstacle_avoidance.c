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

/* 0x61080 — cast a ray against structure BSP for one obstacle-disc direction. */
void FUN_00061080(void *structure_bsp, unsigned char path_surface_flag,
                  float *step_data, int surface_hint, float *direction,
                  void *obstacles, int16_t disc_index,
                  unsigned char use_cost_delta, float max_cost,
                  unsigned char skip_ray_march, float ray_t, void *out_result)
{
  (void)structure_bsp;
  (void)path_surface_flag;
  (void)step_data;
  (void)surface_hint;
  (void)direction;
  (void)obstacles;
  (void)disc_index;
  (void)use_cost_delta;
  (void)max_cost;
  (void)skip_ray_march;
  (void)ray_t;
  (void)out_result;
}

/* 0x61280 — flood obstacle discs from a seed and append avoidance steps. */
void path_add_steps(void *path, int16_t seed_disc_index, int16_t step_index)
{
  char *path_rec;
  char *obstacles;
  int16_t disc_count;
  char *step;
  uint32_t visited[(0x80 + 31) / 32];
  int16_t disc_stack[0x80];
  int16_t stack_top;
  int16_t disc_index;
  int16_t zone_link;
  float scalar;
  float cone_b[2];
  float cone_a[2];
  float direction[2];
  float ray_result[4];
  float target[2];
  float t;
  float step_cost;
  int16_t result_surface;
  int direction_pass;
  int16_t parent_step;

  path_rec = (char *)path;
  if (step_index < 0 || step_index >= *(int16_t *)(path_rec + 0x2c) ||
      *(int16_t *)(path_rec + 0x2c) > 0x80) {
    display_assert("step_index>=0 && step_index<path->step_count && "
                   "path->step_count<=MAXIMUM_OBSTACLE_AVOIDANCE_STEPS",
                   "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 40, 1);
    system_exit(-1);
  }

  obstacles = *(char **)(path_rec + 8);
  disc_count = *(int16_t *)(obstacles + 2);
  if (disc_count < 0 || disc_count > 0x80) {
    display_assert("path->obstacles->disc_count>=0 && "
                   "path->obstacles->disc_count<=MAXIMUM_DISC_COUNT",
                   "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 594, 1);
    system_exit(-1);
  }

  step = (char *)FUN_000600f0(path, step_index);

  csmemset(visited, 0, ((disc_count + 31) >> 5) << 2);

  if (seed_disc_index < 0 || seed_disc_index >= disc_count) {
    display_assert("seed_disc_index>=0 && "
                   "seed_disc_index<path->obstacles->disc_count",
                   "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 597, 1);
    system_exit(-1);
  }

  visited[(unsigned int)seed_disc_index >> 5] |=
      1U << (seed_disc_index & 31);
  disc_stack[0] = seed_disc_index;
  stack_top = 1;

  while (stack_top > 0) {
    stack_top--;
    disc_index = disc_stack[stack_top];

    if (disc_index < 0 || disc_index >= disc_count || disc_count > 0x80) {
      display_assert("disc_index>=0 && disc_index<obstacles->disc_count && "
                     "obstacles->disc_count<=MAXIMUM_DISC_COUNT",
                     "c:\\halo\\source\\ai\\path.h", 0x18c, 1);
      system_exit(-1);
    }

    if (disc_index == -1)
      zone_link = -1;
    else
      zone_link =
          *(int16_t *)(obstacles + 8 + (int)disc_index * 0x18 + 0xa);

    FUN_000625a0(obstacles, disc_index, (float *)step, *(float *)path_rec,
                 cone_b, cone_a, &scalar);
    if (scalar > *(float *)path_rec)
      scalar = *(float *)path_rec;

    direction[0] = cone_b[0];
    direction[1] = cone_b[1];
    for (direction_pass = 0; direction_pass < 2; direction_pass++) {
      FUN_00061080(*(void **)(path_rec + 0xc), *(unsigned char *)(path_rec + 4),
                   (float *)step, 0, direction, obstacles, disc_index,
                   *(unsigned char *)(path_rec + 0x2a), *(float *)path_rec * 2.0f,
                   0, scalar + *(float *)path_rec, ray_result);

      disc_index = (int16_t)*(int32_t *)(ray_result + 2);
      result_surface = *(int16_t *)((char *)ray_result + 0xc);

      if (disc_index != -1) {
        if (disc_index < 0 || disc_index >= disc_count) {
          display_assert("result.disc_index>=0 && "
                         "result.disc_index<path->obstacles->disc_count",
                         "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 625,
                         1);
          system_exit(-1);
        }
        if (!(visited[(unsigned int)disc_index >> 5] &
              (1U << (disc_index & 31)))) {
          visited[(unsigned int)disc_index >> 5] |=
              1U << (disc_index & 31);
          if (stack_top >= 0x80) {
            display_assert("stack_top<MAXIMUM_DISC_COUNT",
                           "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c",
                           631, 1);
            system_exit(-1);
          }
          disc_stack[stack_top] = disc_index;
          stack_top++;
        }
      }

      if (*(float *)ray_result <= scalar && result_surface != zone_link) {
        float ray_test_out[6];

        t = (*(float *)ray_result + scalar) * *(float *)0x253398;
        target[0] = *(float *)step + direction[0] * t;
        target[1] = *(float *)(step + 4) + direction[1] * t;
        structure_test_ray2d(
            *(void **)(path_rec + 0xc), *(unsigned char *)(path_rec + 4),
            (float *)step, *(int *)(step + 8), direction, t, ray_test_out);
        step_cost =
            *(float *)(step + 0x20) - *(float *)(step + 0x14) + t;
        parent_step = -1;
        path_add_step(path, target, zone_link, 0, step_cost, parent_step);
      }

      direction[0] = cone_a[0];
      direction[1] = cone_a[1];
    }
  }
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

  if (*(int16_t *)((char *)avoidance_record + 0x1e) == -1 &&
      *(int16_t *)((char *)avoidance_record + 0x1430) > 0)
    return 1;
  return 0;
}

/* 0x616e0 — Seed avoidance search then drain heap via FUN_000615b0. */
char FUN_000616e0(void *avoidance_record, unsigned char path_flag,
                  void *param_3, void *param_4, void *param_5, void *param_6,
                  float *end_point, unsigned char param_8)
{
  void *scenario;

  (void)param_3;
  (void)param_4;
  (void)param_5;
  (void)param_6;

  scenario = scenario_get();
  FUN_00060ea0(avoidance_record, end_point, param_5, scenario, path_flag,
               *(float *)((char *)avoidance_record + 0x18),
               (float *)((char *)avoidance_record + 0x10), 0, 0.0f,
               *(unsigned char *)((char *)avoidance_record + 0x29), param_8);

  while (FUN_000615b0(avoidance_record))
    ;

  if (*(int16_t *)((char *)avoidance_record + 0x1e) == -1) {
    if (*(int16_t *)((char *)avoidance_record + 0x20) != -1)
      *(int16_t *)((char *)avoidance_record + 0x1e) =
          *(int16_t *)((char *)avoidance_record + 0x20);
    return (char)(*(int16_t *)((char *)avoidance_record + 0x1e) != -1);
  }

  *(char *)((char *)avoidance_record + 0x28) = 1;
  return 1;
}

/* 0x61750 — run obstacle avoidance over smoothed path segments. */
char FUN_00061750(unsigned int param_1, int param_2, void *param_3,
                  int *param_4, void *param_5, char *param_6)
{
  char *path;
  char *smooth_steps;
  char *out_bytes;
  char *debug_state;
  void *collision_bsp;
  float search_radius;
  int16_t smooth_count;
  int16_t segment_index;
  char all_nodes;
  char avoidance_record[0x1440];
  int16_t obstacle_partition[0x628];
  float delta[3];
  float ref_point[3];
  float cur_point[3];
  float segment_length;
  float inv_length;
  int16_t obstacle_step;
  int16_t out_slot;
  void *obstacles;
  void *scenario;
  char try_all_nodes;
  char found_segment;
  uint8_t temp_steps[0x80 * 16];

  path = (char *)(uintptr_t)param_1;
  smooth_steps = (char *)param_3;
  out_bytes = (char *)param_5;
  smooth_count = (int16_t)param_2;

  collision_bsp = global_collision_bsp_get();

  if ((*(uint32_t *)path & 0x7f800000U) != 0x7f800000U &&
      *(float *)path <= *(float *)0x2549d4)
    search_radius = *(float *)path;
  else
    search_radius = 0.2f;

  debug_state = *(char **)(path + 0x48);
  if (debug_state != NULL && *(char *)(debug_state + 0x14588) == 0) {
    if (smooth_count > 4) {
      display_assert("input_step_count <= MAXIMUM_SMOOTHED_PATH_STEPS",
                     "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 761, 1);
      system_exit(-1);
    }
    *(int16_t *)(debug_state + 0x1458a) = 0;
  }

  if (smooth_count <= 0)
    return 0;

  segment_index = 0;
  all_nodes = 0;

  while (segment_index < smooth_count) {
    float *prev_pt;
    float *cur_pt_ptr;

    try_all_nodes = 0;
    if (segment_index == smooth_count - 1 && *param_6 != 0)
      try_all_nodes = 1;

    if (segment_index > 0) {
      prev_pt = ref_point;
    } else {
      prev_pt = *(float **)(path + 0x20);
      if (prev_pt == NULL)
        prev_pt = (float *)(path + 0x10);
    }

    cur_pt_ptr =
        (float *)(smooth_steps + (int)segment_index * 16);
    cur_point[0] = cur_pt_ptr[0];
    cur_point[1] = cur_pt_ptr[1];
    cur_point[2] = cur_pt_ptr[2];

    delta[0] = cur_point[0] - prev_pt[0];
    delta[1] = cur_point[1] - prev_pt[1];
    delta[2] = cur_point[2] - prev_pt[2];
    segment_length =
        sqrtf(delta[1] * delta[1] + delta[2] * delta[2] + delta[0] * delta[0]);

    if (fabs(segment_length) >= *(double *)0x2533d0) {
      inv_length = *(float *)0x2533c8 / segment_length;
      delta[0] = delta[0] * inv_length;
      delta[1] = delta[1] * inv_length;
      delta[2] = delta[2] * inv_length;
    }

    if (debug_state != NULL && *(char *)(debug_state + 0x14588) != 0 &&
        segment_index < *(int16_t *)(debug_state + 0x1458a))
      goto next_segment;

    obstacles = *(void **)(path + 8);
    scenario = *(void **)(path + 0xc);
    FUN_00061d80(obstacle_partition);
    obstacles_get_discs_in_sphere(obstacle_partition, prev_pt, 4.0f, delta,
                                  obstacles, scenario);

    if (*(char *)(path + 0x24) != 0) {
      FUN_00062020(obstacle_partition, *(uint32_t *)(path + 0x34),
                     *(uint16_t *)(path + 0x38),
                     (float *)(path + 0x28), 0);
    }

    FUN_000628b0(obstacle_partition, *(uint32_t *)&search_radius);

    if (debug_state != NULL && *(char *)(debug_state + 0x14588) == 0)
      *(int16_t *)(debug_state + 0x1458a) = segment_index + 1;

    csmemset(avoidance_record, 0, sizeof(avoidance_record));
    scenario = scenario_get();
    FUN_00060ea0(avoidance_record, cur_point, obstacles, scenario,
                 *(unsigned char *)(path + 4), search_radius, prev_pt, 0, 0.0f,
                 try_all_nodes, 0);

    while (FUN_000615b0(avoidance_record))
      ;

    found_segment = 0;
    if (*(int16_t *)(avoidance_record + 0x1e) != -1)
      found_segment = 1;
    else if (*(int16_t *)(avoidance_record + 0x20) != -1) {
      *(int16_t *)(avoidance_record + 0x1e) =
          *(int16_t *)(avoidance_record + 0x20);
      found_segment = 1;
    }

    if (!found_segment && obstacle_partition[2] > 0) {
      found_segment = FUN_000616e0(
          avoidance_record, 1, prev_pt, ref_point, obstacles, obstacle_partition,
          cur_point, try_all_nodes);
    }

    if (!found_segment)
      return 0;

    if (*(char *)(avoidance_record + 0x28) != 0) {
      ref_point[0] = cur_point[0];
      ref_point[1] = cur_point[1];
      ref_point[2] = cur_point[2];
    } else {
      obstacle_step = *(int16_t *)(avoidance_record + 0x1e);
      if (obstacle_step < 0 ||
          obstacle_step >= *(int16_t *)(avoidance_record + 0x2c) ||
          *(int16_t *)(avoidance_record + 0x2c) > 0x80) {
        display_assert("step_index>=0 && step_index<path->step_count && "
                       "path->step_count<=MAXIMUM_OBSTACLE_AVOIDANCE_STEPS",
                       "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 40, 1);
        system_exit(-1);
      }
      {
        char *step =
            (char *)FUN_000600f0(avoidance_record, obstacle_step);
        collision_surface_project_point2d((int)collision_bsp,
                                          *(int *)(step + 8), 2, 1,
                                          (float *)step, ref_point);
      }
    }

    out_slot = 0;
    obstacle_step = *(int16_t *)(avoidance_record + 0x1e);
    if (obstacle_step != 0) {
      for (;;) {
        char *step;

        if (obstacle_step < 0 ||
            obstacle_step >= *(int16_t *)(avoidance_record + 0x2c) ||
            *(int16_t *)(avoidance_record + 0x2c) > 0x80) {
          display_assert("step_index>=0 && step_index<path->step_count && "
                         "path->step_count<=MAXIMUM_OBSTACLE_AVOIDANCE_STEPS",
                         "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 40,
                         1);
          system_exit(-1);
        }

        step = (char *)FUN_000600f0(avoidance_record, obstacle_step);
        collision_surface_project_point2d((int)collision_bsp, *(int *)(step + 8),
                                          2, 1, (float *)step,
                                          (float *)(temp_steps + out_slot * 16 + 4));

        *(uint32_t *)(temp_steps + out_slot * 16) =
            *(uint32_t *)(step + 0xc);
        *(uint32_t *)(temp_steps + out_slot * 16 + 8) =
            *(uint32_t *)(step + 0x10);
        *(uint32_t *)(temp_steps + out_slot * 16 + 12) =
            *(uint32_t *)(step + 0x14);

        out_slot++;
        if (out_slot >= 0x80) {
          all_nodes = 1;
          break;
        }

        obstacle_step = *(int16_t *)(step + 0x24);
        if (obstacle_step < 0 ||
            obstacle_step >= *(int16_t *)(avoidance_record + 0x2c)) {
          display_assert("(obstacle_step_index >= 0) && "
                         "(obstacle_step_index < obstacle_path->step_count)",
                         "c:\\halo\\SOURCE\\ai\\path_obstacle_avoidance.c", 875,
                         1);
          system_exit(-1);
        }
        if (obstacle_step == 0)
          break;
      }
    }

    if (!all_nodes) {
      int16_t copy_index;
      int16_t out_index;

      out_index = *(int16_t *)param_4;
      copy_index = (int16_t)(out_slot - 1);
      while (copy_index >= 0 && out_index < 4) {
        csmemcpy(out_bytes + (int)out_index * 16,
                 temp_steps + (int)copy_index * 16, 16);
        out_index++;
        copy_index--;
      }
      *(int16_t *)param_4 = out_index;
    } else {
      all_nodes = 1;
    }

  next_segment:
    segment_index++;
  }

  if (all_nodes) {
    *param_6 = 0;
    return 1;
  }

  return 1;
}
