#include "x87_math.h"

/* Camera observer — tracks camera position/orientation per player. */

void observer_initialize(void)
{
}

/* Initialize an observer result struct with default camera orientation,
 * zero velocities, and signature markers (0x8a350). Sets the camera up/forward
 * vectors from globals, zeros the integration working area, then copies the
 * template vectors into the active camera state. */
void observer_result_initialize(void *observer)
{
  char *obs = (char *)observer;
  float *up = *(float **)0x31fc3c;
  float *fwd = *(float **)0x31fc44;
  float *pos;

  *(float *)(obs + 0xd0) = up[0];
  *(float *)(obs + 0xd4) = up[1];
  *(float *)(obs + 0xd8) = up[2];
  *(float *)(obs + 0xdc) = fwd[0];
  *(float *)(obs + 0xe0) = fwd[1];
  *(float *)(obs + 0xe4) = fwd[2];
  *(int *)(obs + 0xcc) = 0x3f5f66f3;

  pos = *(float **)0x31fc1c;
  *(float *)(obs + 0x74) = pos[0];
  *(float *)(obs + 0x78) = pos[1];
  *(float *)(obs + 0x7c) = pos[2];

  *(int16_t *)(obs + 0x84) = -1;
  *(int *)(obs + 0x80) = -1;

  {
    float *zero = *(float **)0x31fc38;
    *(float *)(obs + 0x88) = zero[0];
    *(float *)(obs + 0x8c) = zero[1];
    *(float *)(obs + 0x90) = zero[2];
  }

  up = *(float **)0x31fc3c;
  *(float *)(obs + 0x94) = up[0];
  *(float *)(obs + 0x98) = up[1];
  *(float *)(obs + 0x9c) = up[2];

  fwd = *(float **)0x31fc44;
  *(float *)(obs + 0xa0) = fwd[0];
  *(float *)(obs + 0xa4) = fwd[1];
  *(float *)(obs + 0xa8) = fwd[2];
  *(int *)(obs + 0xac) = 0x3f5f66f3;

  csmemset(obs + 0x8, 0, 0x68);

  *(float *)(obs + 0x2c) = *(float *)(obs + 0xd0);
  *(float *)(obs + 0x30) = *(float *)(obs + 0xd4);
  *(float *)(obs + 0x34) = *(float *)(obs + 0xd8);
  *(float *)(obs + 0x38) = *(float *)(obs + 0xdc);
  *(float *)(obs + 0x3c) = *(float *)(obs + 0xe0);
  *(float *)(obs + 0x40) = *(float *)(obs + 0xe4);
  *(int *)(obs + 0x28) = *(int *)(obs + 0xcc);

  *(int *)(obs + 0x298) = 0x72616421;
  *(int *)(obs + 0x0) = 0x72616421;
  *(uint8_t *)(obs + 0x70) = 1;
  *(uint8_t *)(obs + 0x71) = 0;
}

/* Initialize observers for all 4 players. Calls observer_result_initialize
 * with ESI pointing to each player's observer data (base 0x33571c,
 * stride 0x29c). */
void observer_initialize_for_new_map(void)
{
  int16_t i;
  char *entry = (char *)0x33571c;

  for (i = 0; i < 4; i++) {
    assert_halt(i >= 0 && i < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
    observer_result_initialize(entry);
    entry += 0x29c;
  }
}

void observer_dispose_from_old_map(void)
{
}

/* Return a pointer to the observer camera result for a local player.
 * Base at 0x33571c, stride 0x29c, camera result at offset +0x74.
 * Validates the cluster index against the current BSP. */
void *observer_get_camera(unsigned __int16 local_player_index)
{
  int16_t idx = (int16_t)local_player_index;
  char *entry;

  if (idx == -1)
    return 0;

  assert_halt(idx >= 0 && idx < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  entry = (char *)0x33571c + (int)idx * 0x29c;

  if (*(int16_t *)(entry + 0x84) < -1 ||
      (int)*(int16_t *)(entry + 0x84) >=
        *(int *)((char *)scenario_get() + 0x134)) {
    display_assert("observer->result.location.cluster_index>=NONE && "
                   "observer->result.location.cluster_index<"
                   "global_structure_bsp_get()->clusters.count",
                   "c:\\halo\\SOURCE\\camera\\observer.c", 0x12d, 1);
    system_exit(-1);
  }

  return (void *)(entry + 0x74);
}

/* Apply spring acceleration to observer state (0x8a660).
 * For each of 5 observer components, evaluates a cubic polynomial
 * (2*vel + t*accel*K1 + t^2*jerk*K2 + t^3*snap*K3) using the component's
 * timer. If any element exceeds its threshold, resets the timer (and any
 * other timers sharing the same value) to zero. */
void observer_apply_acceleration(int16_t local_player_index)
{
  char *observer;
  float *snap_ptr, *jerk_ptr, *accel_ptr, *vel_ptr, *output;
  float *timers, *timers_base;
  int16_t *sizes;
  float *thresholds;
  int16_t comp;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  observer = (char *)0x33571c + (int)local_player_index * 0x29c;
  snap_ptr = (float *)(observer + 0x158);
  jerk_ptr = (float *)(observer + 0x184);
  accel_ptr = (float *)(observer + 0x1b0);
  vel_ptr = (float *)(observer + 0x1dc);
  output = (float *)(observer + 0x120);
  timers_base = (float *)(observer + 0x5c);
  timers = timers_base;
  sizes = (int16_t *)0x2ee6b8;
  thresholds = (float *)0x26738c;

  for (comp = 0; comp < 5; comp++) {
    float t = *timers - *(float *)0x335718;
    int16_t size = *sizes;

    if (t <= 0.0f) {
      csmemset(output, 0, (int)size << 2);
    } else {
      float t_sq = t * t;
      float t_cu = t_sq * t;
      int16_t j;

      for (j = 0; j < size; j++) {
        float result = t_cu * snap_ptr[j] * *(float *)0x254cd0 +
                       t_sq * jerk_ptr[j] * *(float *)0x254cc8 +
                       t * accel_ptr[j] * *(float *)0x254640 + vel_ptr[j] +
                       vel_ptr[j];
        output[j] = result;

        if (result > *thresholds || result < -*thresholds) {
          int16_t k;
          float *tp = timers_base;
          for (k = 0; k < 5; k++) {
            if (k != comp && *tp == *timers)
              *tp = 0.0f;
            tp++;
          }
          *timers = 0.0f;
        }
      }
    }

    snap_ptr += size;
    jerk_ptr += size;
    output += size;
    accel_ptr += size;
    vel_ptr += size;
    timers++;
    thresholds++;
    sizes++;
  }
}

/* Integrate observer spring state (0x8a830). For each of 5 components,
 * evaluates a quartic polynomial (pos + 2*t*vel + t^2*accel*K1 + t^3*jerk*K2
 * + t^4*snap*K3) when the timer is active. When expired, either zeros the
 * output or applies a negated ratio correction from the result buffer. */
void observer_integrate(int16_t local_player_index)
{
  char *observer;
  float *result_ptr, *snap_ptr, *jerk_ptr, *accel_ptr, *vel_ptr, *pos_ptr;
  float *output, *timers;
  uint8_t *byte_flags;
  int16_t *sizes;
  float ratio;
  int count;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  ratio = (float)(*(double *)0x2573d8 / *(float *)0x335718);

  observer = (char *)0x33571c + (int)local_player_index * 0x29c;
  result_ptr = (float *)(observer + 0x260);
  snap_ptr = (float *)(observer + 0x158);
  jerk_ptr = (float *)(observer + 0x184);
  accel_ptr = (float *)(observer + 0x1b0);
  vel_ptr = (float *)(observer + 0x1dc);
  pos_ptr = (float *)(observer + 0x208);
  timers = (float *)(observer + 0x5c);
  byte_flags = (uint8_t *)(observer + 0x54);
  output = (float *)(observer + 0xe8);
  sizes = (int16_t *)0x2ee6b8;

  for (count = 5; count != 0; count--) {
    float t = *timers - *(float *)0x335718;
    int16_t size = *sizes;

    if (t <= 0.0f) {
      uint32_t mode = *(uint32_t *)(observer + 0x8);
      if ((mode & 1) && ((*byte_flags & 2) || (mode & 8))) {
        csmemset(output, 0, (int)size << 2);
      } else if ((mode & 1) && size > 0) {
        int16_t i;
        for (i = 0; i < size; i++)
          output[i] = -(ratio * result_ptr[i]);
      }
    } else {
      float t_sq = t * t;
      float t_cu = t_sq * t;
      float t_q4 = t_cu * t;
      int16_t i;

      for (i = 0; i < size; i++) {
        float v = t * vel_ptr[i];
        output[i] = v + v + t_sq * accel_ptr[i] * *(float *)0x254644 +
                    t_cu * jerk_ptr[i] * *(float *)0x2533d8 +
                    t_q4 * snap_ptr[i] * *(float *)0x254cc4 + pos_ptr[i];
      }
    }

    result_ptr += size;
    snap_ptr += size;
    jerk_ptr += size;
    accel_ptr += size;
    vel_ptr += size;
    output += size;
    pos_ptr += size;
    timers++;
    byte_flags++;
    sizes++;
  }
}

/* Cast a collision ray for the observer camera (0x8ab90).
 * Pushes a collision user tag (0xc = observer), computes direction from
 * ray_origin to ray_endpoint, fires FUN_0014df70, and writes the hit
 * fraction to *out_fraction if a collision is found. */
bool FUN_0008ab90(float *out_fraction, bool indoor, float *ray_origin,
                  float *ray_endpoint)
{
  uint32_t flags;
  bool result;
  float direction[3];
  char collision_result[0x60];

  result = false;
  flags = 0x40e1;
  if (indoor)
    flags = 0x40a1;

  if (*(int16_t *)0x4761d8 >= 0x20) {
    display_assert("global_current_collision_user_depth < "
                   "MAXIMUM_COLLISION_USER_STACK_DEPTH",
                   "c:\\halo\\SOURCE\\camera\\observer.c", 0x4b4, 1);
    system_exit(-1);
  }

  {
    int depth = (int)*(int16_t *)0x4761d8;
    *(int16_t *)(0x5a8c80 + depth * 2) = 0xc;
    *(int16_t *)0x4761d8 += 1;
  }

  direction[0] = ray_endpoint[0] - ray_origin[0];
  direction[1] = ray_endpoint[1] - ray_origin[1];
  direction[2] = ray_endpoint[2] - ray_origin[2];

  if (FUN_0014df70(flags, ray_origin, direction, -1,
                   (int16_t *)collision_result)) {
    *out_fraction = *(float *)(collision_result + 0x14);
    result = true;
  }

  if (*(int16_t *)0x4761d8 <= 1) {
    display_assert("global_current_collision_user_depth > 1",
                   "c:\\halo\\SOURCE\\camera\\observer.c", 0x4ba, 1);
    system_exit(-1);
  }
  *(int16_t *)0x4761d8 -= 1;

  return result;
}

/* Copy/stage camera command block from director into observer state (0x8b060).
 * Validates the command struct (pointed to by observer+0x4): checks forward/up
 * perpendicular, position/orientation in range, velocity valid, distance/FOV/
 * timer bounded. Then adjusts 5 component timers in the command based on the
 * observer's current timers and mode bytes, and finally copies the command
 * struct (0x68 bytes) into the observer at offset +0x8. */
void observer_update_command(int16_t local_player_index)
{
  char *observer;
  char *command;
  float *timer_out;
  uint8_t *mode_bytes;
  float *obs_timers;
  int i;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  observer = (char *)0x33571c + (int)local_player_index * 0x29c;
  command = *(char **)(observer + 0x4);
  timer_out = (float *)(command + 0x54);
  mode_bytes = (uint8_t *)(command + 0x4c);
  obs_timers = (float *)(observer + 0x5c);

  if (command == NULL ||
      ((*(uint8_t *)command & 1) &&
       (!valid_real_normal3d_perpendicular((float *)(command + 0x24),
                                           (float *)(command + 0x30)) ||
        (*(uint32_t *)(command + 0x4) & 0x7f800000) == 0x7f800000 ||
        *(float *)(command + 0x4) < *(float *)0x266e98 ||
        *(float *)(command + 0x4) > *(float *)0x266e94 ||
        (*(uint32_t *)(command + 0x8) & 0x7f800000) == 0x7f800000 ||
        *(float *)(command + 0x8) < *(float *)0x266e98 ||
        *(float *)(command + 0x8) > *(float *)0x266e94 ||
        (*(uint32_t *)(command + 0xc) & 0x7f800000) == 0x7f800000 ||
        *(float *)(command + 0xc) < *(float *)0x266e98 ||
        *(float *)(command + 0xc) > *(float *)0x266e94 ||
        (*(uint32_t *)(command + 0x10) & 0x7f800000) == 0x7f800000 ||
        *(float *)(command + 0x10) < *(float *)0x266e98 ||
        *(float *)(command + 0x10) > *(float *)0x266e94 ||
        (*(uint32_t *)(command + 0x14) & 0x7f800000) == 0x7f800000 ||
        *(float *)(command + 0x14) < *(float *)0x266e98 ||
        *(float *)(command + 0x14) > *(float *)0x266e94 ||
        (*(uint32_t *)(command + 0x18) & 0x7f800000) == 0x7f800000 ||
        *(float *)(command + 0x18) < *(float *)0x266e98 ||
        *(float *)(command + 0x18) > *(float *)0x266e94 ||
        !real_vector3d_valid((float *)(command + 0x3c)) ||
        (*(uint32_t *)(command + 0x1c) & 0x7f800000) == 0x7f800000 ||
        *(float *)(command + 0x1c) < *(float *)0x2533c0 ||
        *(float *)(command + 0x1c) > *(float *)0x266e94 ||
        (*(uint32_t *)(command + 0x20) & 0x7f800000) == 0x7f800000 ||
        *(float *)(command + 0x20) < *(float *)0x255ef8 ||
        *(float *)(command + 0x20) > *(float *)0x2568bc ||
        (*(uint32_t *)(command + 0x48) & 0x7f800000) == 0x7f800000 ||
        *(float *)(command + 0x48) < *(float *)0x2533c0 ||
        *(float *)(command + 0x48) > *(float *)0x266e90))) {
    char *msg = csprintf(
      (char *)0x5ab100,
      "Invalid camera command.\n"
      "F: (%f, %f, %f) U: (%f, %f, %f)\n"
      "P: (%f, %f, %f) O: (%f, %f, %f)\n"
      "D: %f V: (%f, %f, %f), FOV: %f, T: %f, FL: %ld",
      (double)*(float *)(command + 0x24), (double)*(float *)(command + 0x28),
      (double)*(float *)(command + 0x2c), (double)*(float *)(command + 0x30),
      (double)*(float *)(command + 0x34), (double)*(float *)(command + 0x38),
      (double)*(float *)(command + 0x04), (double)*(float *)(command + 0x08),
      (double)*(float *)(command + 0x0c), (double)*(float *)(command + 0x10),
      (double)*(float *)(command + 0x14), (double)*(float *)(command + 0x18),
      (double)*(float *)(command + 0x1c), (double)*(float *)(command + 0x3c),
      (double)*(float *)(command + 0x40), (double)*(float *)(command + 0x44),
      (double)*(float *)(command + 0x20), (double)*(float *)(command + 0x48),
      *(uint32_t *)command);
    display_assert(msg, "c:\\halo\\SOURCE\\camera\\observer.c", 0x172, 1);
    system_exit(-1);
  }

  if (*(uint8_t *)(*(char **)(observer + 0x4)) & 1) {
    for (i = 5; i != 0; i--) {
      if ((*mode_bytes & 1) == 0) {
        command = *(char **)(observer + 0x4);
        if (*(float *)(command + 0x48) < *obs_timers &&
            (*(uint8_t *)command & 8) == 0)
          goto clamp_timer;
        *timer_out = *(float *)(command + 0x48);
      } else if ((*mode_bytes & 2) == 0 && *timer_out < *obs_timers) {
      clamp_timer:
        if (*obs_timers <= *(float *)0x253f40)
          *timer_out = *obs_timers;
        else
          *timer_out = *(float *)0x253f40;
      }

      timer_out++;
      obs_timers++;
      mode_bytes++;
    }

    {
      uint32_t *src = (uint32_t *)*(char **)(observer + 0x4);
      uint32_t *dst = (uint32_t *)(observer + 0x8);
      for (i = 0x1a; i != 0; i--)
        *dst++ = *src++;
    }
  }
}

/* Compute quintic Hermite acceleration coefficients for observer interpolation
 * (0x8b470). Validates the observer command state (forward/up perpendicular,
 * position/orientation in range, velocity valid, distance/FOV/timer bounded).
 * When mode bit 0 is set and timer > delta_time, computes snap/jerk/accel/vel/
 * pos/extra polynomial coefficients for each of 5 observer components.
 * Component 0 receives additional velocity-dependent correction terms. */
void observer_compute_accelerations(int16_t local_player_index)
{
  char *observer;
  char *mode_ptr;
  float *snap_ptr, *jerk_ptr, *accel_ptr, *vel_ptr, *pos_ptr, *extra_ptr;
  float *accel_out_ptr, *vel_out_ptr, *result_ptr;
  float *timers;
  int16_t comp;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  observer = (char *)0x33571c + (int)local_player_index * 0x29c;

  snap_ptr = (float *)(observer + 0x158);
  accel_ptr = (float *)(observer + 0x1b0);
  pos_ptr = (float *)(observer + 0x208);
  jerk_ptr = (float *)(observer + 0x184);
  timers = (float *)(observer + 0x5c);
  vel_ptr = (float *)(observer + 0x1dc);
  extra_ptr = (float *)(observer + 0x234);
  vel_out_ptr = (float *)(observer + 0xe8);
  accel_out_ptr = (float *)(observer + 0x120);
  result_ptr = (float *)(observer + 0x260);

  mode_ptr = observer + 0x8;

  /* Validate observer command state when mode bit 0 is set */
  if (mode_ptr == NULL ||
      ((*(uint8_t *)mode_ptr & 1) &&
       (!valid_real_normal3d_perpendicular((float *)(observer + 0x2c),
                                           (float *)(observer + 0x38)) ||
        (*(uint32_t *)(observer + 0xc) & 0x7f800000) == 0x7f800000 ||
        *(float *)(observer + 0xc) < *(float *)0x266e98 ||
        *(float *)(observer + 0xc) > *(float *)0x266e94 ||
        (*(uint32_t *)(observer + 0x10) & 0x7f800000) == 0x7f800000 ||
        *(float *)(observer + 0x10) < *(float *)0x266e98 ||
        *(float *)(observer + 0x10) > *(float *)0x266e94 ||
        (*(uint32_t *)(observer + 0x14) & 0x7f800000) == 0x7f800000 ||
        *(float *)(observer + 0x14) < *(float *)0x266e98 ||
        *(float *)(observer + 0x14) > *(float *)0x266e94 ||
        (*(uint32_t *)(observer + 0x18) & 0x7f800000) == 0x7f800000 ||
        *(float *)(observer + 0x18) < *(float *)0x266e98 ||
        *(float *)(observer + 0x18) > *(float *)0x266e94 ||
        (*(uint32_t *)(observer + 0x1c) & 0x7f800000) == 0x7f800000 ||
        *(float *)(observer + 0x1c) < *(float *)0x266e98 ||
        *(float *)(observer + 0x1c) > *(float *)0x266e94 ||
        (*(uint32_t *)(observer + 0x20) & 0x7f800000) == 0x7f800000 ||
        *(float *)(observer + 0x20) < *(float *)0x266e98 ||
        *(float *)(observer + 0x20) > *(float *)0x266e94 ||
        !real_vector3d_valid((float *)(observer + 0x44)) ||
        (*(uint32_t *)(observer + 0x24) & 0x7f800000) == 0x7f800000 ||
        *(float *)(observer + 0x24) < *(float *)0x2533c0 ||
        *(float *)(observer + 0x24) > *(float *)0x266e94 ||
        (*(uint32_t *)(observer + 0x28) & 0x7f800000) == 0x7f800000 ||
        *(float *)(observer + 0x28) < *(float *)0x255ef8 ||
        *(float *)(observer + 0x28) > *(float *)0x2568bc ||
        (*(uint32_t *)(observer + 0x50) & 0x7f800000) == 0x7f800000 ||
        *(float *)(observer + 0x50) < *(float *)0x2533c0 ||
        *(float *)(observer + 0x50) > *(float *)0x266e90))) {
    char *msg = csprintf(
      (char *)0x5ab100,
      "Invalid camera command.\n"
      "F: (%f, %f, %f) U: (%f, %f, %f)\n"
      "P: (%f, %f, %f) O: (%f, %f, %f)\n"
      "D: %f V: (%f, %f, %f), FOV: %f, T: %f, FL: %ld",
      (double)*(float *)(observer + 0x2c), (double)*(float *)(observer + 0x30),
      (double)*(float *)(observer + 0x34), (double)*(float *)(observer + 0x38),
      (double)*(float *)(observer + 0x3c), (double)*(float *)(observer + 0x40),
      (double)*(float *)(observer + 0x0c), (double)*(float *)(observer + 0x10),
      (double)*(float *)(observer + 0x14), (double)*(float *)(observer + 0x18),
      (double)*(float *)(observer + 0x1c), (double)*(float *)(observer + 0x20),
      (double)*(float *)(observer + 0x24), (double)*(float *)(observer + 0x44),
      (double)*(float *)(observer + 0x48), (double)*(float *)(observer + 0x4c),
      (double)*(float *)(observer + 0x28), (double)*(float *)(observer + 0x50),
      *(uint32_t *)(observer + 0x8));
    display_assert(msg, "c:\\halo\\SOURCE\\camera\\observer.c", 0x1f6, 1);
    system_exit(-1);
  }

  /* Compute polynomial coefficients for each of 5 components */
  for (comp = 0; comp < 5; comp++) {
    if ((*(uint8_t *)(observer + 0x8) & 1) && *(float *)0x335718 < *timers) {
      float f = 1.0f / *timers;
      float f2 = f * f;
      float f3 = f2 * f;
      float f4 = f3 * f;
      int16_t size = ((int16_t *)0x2ee6b8)[comp];
      int16_t j;

      for (j = 0; j < size; j++) {
        int idx = (int)j;
        int off = idx * 4;

        *(float *)((char *)snap_ptr + off) =
          f3 * *(float *)((char *)accel_out_ptr + off) * *(float *)0x253398 -
          (f4 * *(float *)((char *)vel_out_ptr + off) * *(float *)0x254644 +
           f4 * f * *(float *)((char *)result_ptr + off) * *(float *)0x254640);

        *(float *)((char *)jerk_ptr + off) =
          f3 * *(float *)((char *)vel_out_ptr + off) * *(float *)0x2548f4 +
          f4 * *(float *)((char *)result_ptr + off) * *(float *)0x254cc0 -
          f2 * *(float *)((char *)accel_out_ptr + off);

        *(float *)((char *)accel_ptr + off) =
          f * *(float *)((char *)accel_out_ptr + off) * *(float *)0x253398 -
          (f2 * *(float *)((char *)vel_out_ptr + off) * *(float *)0x2533d8 +
           f3 * *(float *)((char *)result_ptr + off) * *(float *)0x253f34);

        *(int *)((char *)vel_ptr + off) = 0;
        *(int *)((char *)pos_ptr + off) = 0;
        *(int *)((char *)extra_ptr + off) = *(int *)((char *)result_ptr + off);

        if (comp == 0) {
          float fv = *(float *)(observer + 0x44 + off) * TICKS_PER_SECOND;
          *(float *)((char *)snap_ptr + off) -= f4 * fv * *(float *)0x254644;
          *(float *)((char *)jerk_ptr + off) += f3 * fv * *(float *)0x253f78;
          *(float *)((char *)accel_ptr + off) -= f2 * fv * *(float *)0x254640;
          *(float *)((char *)pos_ptr + off) += fv;
        }
      }
    }

    {
      int size = (int)((int16_t *)0x2ee6b8)[comp] * 4;
      snap_ptr = (float *)((char *)snap_ptr + size);
      jerk_ptr = (float *)((char *)jerk_ptr + size);
      accel_ptr = (float *)((char *)accel_ptr + size);
      vel_ptr = (float *)((char *)vel_ptr + size);
      pos_ptr = (float *)((char *)pos_ptr + size);
      extra_ptr = (float *)((char *)extra_ptr + size);
      vel_out_ptr = (float *)((char *)vel_out_ptr + size);
      accel_out_ptr = (float *)((char *)accel_out_ptr + size);
      result_ptr = (float *)((char *)result_ptr + size);
      timers++;
    }
  }
}

/* Apply observer polynomial update and orthogonalize result vectors (0x8ba10).
 * For each of 5 observer components, validates velocities (assert_valid_real),
 * then either copies defaults (when timer expired and mode active), evaluates
 * a quintic polynomial (when timer active), or negates velocity*delta_time
 * (when timer expired but mode not active). For the last component (index 4,
 * forward/up vectors), applies axis-angle rotation via
 * rotate_vector3d_by_sincos instead of simple addition. After the loop,
 * orthogonalizes the forward/up vectors via Gram-Schmidt if they are no longer
 * orthonormal. */
void observer_compute_update(int16_t local_player_index)
{
  char *observer;
  char *result_ptr;
  char *default_ptr;
  char *snap_ptr;
  char *jerk_ptr;
  char *accel_ptr;
  char *vel_ptr;
  float *velocities;
  char *pos_ptr;
  char *extra_ptr;
  float *timers;
  float scratch[14];
  float *scratch_ptr;
  int16_t comp;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  observer = (char *)0x33571c + (int)local_player_index * 0x29c;

  result_ptr = observer + 0xb0;
  default_ptr = observer + 0x0c;
  snap_ptr = observer + 0x158;
  jerk_ptr = observer + 0x184;
  accel_ptr = observer + 0x1b0;
  vel_ptr = observer + 0x1dc;
  velocities = (float *)(observer + 0xe8);
  pos_ptr = observer + 0x208;
  extra_ptr = observer + 0x234;
  timers = (float *)(observer + 0x5c);
  scratch_ptr = scratch;

  /* Validate all 11 velocity floats */
  {
    float *vp = velocities;
    int count = 0xb;
    do {
      if ((*(uint32_t *)vp & 0x7f800000u) == 0x7f800000u) {
        char *msg =
          csprintf((char *)0x5ab100, "%s: assert_valid_real(0x%08X %f)",
                   "observer->velocities.n[parameter_index]", *(uint32_t *)vp,
                   (double)*vp);
        display_assert(msg, "c:\\halo\\SOURCE\\camera\\observer.c", 0x2f4, 1);
        system_exit(-1);
      }
      vp++;
      count--;
    } while (count != 0);
  }

  for (comp = 0; comp < 5; comp++) {
    float elapsed = *timers - *(float *)0x335718;

    if (elapsed <= *(float *)0x2533c0 && (*(uint8_t *)(observer + 0x8) & 1)) {
      /* Timer expired and mode active: copy defaults */
      int16_t j = 0;
      if (j < ((int16_t *)0x2ee6ac)[comp]) {
        do {
          *(uint32_t *)(result_ptr + j * 4) =
            *(uint32_t *)(default_ptr + j * 4);
          j++;
        } while (j < ((int16_t *)0x2ee6ac)[comp]);
      }
    } else {
      /* Compute update values */
      if (elapsed <= *(float *)0x2533c0) {
        /* Timer expired, mode not active: negate velocity*delta_time */
        int16_t j = 0;
        if (j < ((int16_t *)0x2ee6b8)[comp]) {
          do {
            scratch_ptr[j] = -(*(float *)0x335718 * velocities[j]);
            j++;
          } while (j < ((int16_t *)0x2ee6b8)[comp]);
        }
      } else {
        /* Timer active: evaluate quintic polynomial */
        float t2 = elapsed * elapsed;
        float t3 = t2 * elapsed;
        float t4 = t3 * elapsed;
        float t5 = t4 * elapsed;
        int16_t j = 0;

        if (j < ((int16_t *)0x2ee6b8)[comp]) {
          do {
            int idx = (int)j;
            int off = idx * 4;
            j++;
            scratch_ptr[idx] = t5 * *(float *)(snap_ptr + off) +
                               t4 * *(float *)(jerk_ptr + off) +
                               t3 * *(float *)(accel_ptr + off) +
                               t2 * *(float *)(vel_ptr + off) +
                               elapsed * *(float *)(pos_ptr + off) +
                               *(float *)(extra_ptr + off);
          } while (j < ((int16_t *)0x2ee6b8)[comp]);
        }
      }

      if (comp < 4) {
        /* Components 0-3: add scratch to result */
        int16_t j = 0;
        if (j < ((int16_t *)0x2ee6b8)[comp]) {
          do {
            int idx = (int)j;
            int off = idx * 4;
            j++;
            *(float *)(result_ptr + off) =
              scratch_ptr[idx] + *(float *)(result_ptr + off);
          } while (j < ((int16_t *)0x2ee6b8)[comp]);
        }
      } else {
        /* Component 4 (forward/up vectors): axis-angle rotation */
        float axis[3];
        float mag;

        axis[0] = scratch_ptr[0];
        axis[1] = scratch_ptr[1];
        axis[2] = scratch_ptr[2];
        mag = sqrtf(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);

        if (fabsf(mag) >= (float)*(double *)0x2533d0) {
          float inv_mag = *(float *)0x2533c8 / mag;
          axis[0] = axis[0] * inv_mag;
          axis[1] = axis[1] * inv_mag;
          axis[2] = axis[2] * inv_mag;

          if (mag != *(float *)0x2533c0) {
            float sin_val = x87_fsin(mag);
            float cos_val = x87_fcos(mag);
            rotate_vector3d_by_sincos((float *)result_ptr, axis, sin_val,
                                      cos_val);
            rotate_vector3d_by_sincos((float *)(result_ptr + 0xc), axis,
                                      sin_val, cos_val);
          }
        }
      }
    }

    {
      int result_advance = (int)((int16_t *)0x2ee6ac)[comp] * 4;
      int vel_advance = (int)((int16_t *)0x2ee6b8)[comp] * 4;
      default_ptr += result_advance;
      result_ptr += result_advance;
      velocities += (int)((int16_t *)0x2ee6b8)[comp];
      snap_ptr += vel_advance;
      jerk_ptr += vel_advance;
      accel_ptr += vel_advance;
      vel_ptr += vel_advance;
      scratch_ptr += (int)((int16_t *)0x2ee6b8)[comp];
      pos_ptr += vel_advance;
      extra_ptr += vel_advance;
      timers++;
    }
  }

  /* Orthogonalize forward/up vectors if needed */
  {
    float *up = (float *)(observer + 0xd0);
    float *fwd = (float *)(observer + 0xdc);
    float check;

    /* Check if up is unit length */
    check =
      (up[0] * up[0] + up[1] * up[1] + up[2] * up[2]) - *(float *)0x2533c8;
    if ((*(uint32_t *)&check & 0x7f800000u) == 0x7f800000u ||
        fabsf(check) >= (float)*(double *)0x2549d8) {
      goto orthogonalize;
    }

    /* Check if forward is unit length */
    check = (fwd[0] * fwd[0] + fwd[1] * fwd[1] + fwd[2] * fwd[2]) -
            *(float *)0x2533c8;
    if ((*(uint32_t *)&check & 0x7f800000u) == 0x7f800000u ||
        fabsf(check) >= (float)*(double *)0x2549d8) {
      goto orthogonalize;
    }

    /* Check if up and forward are perpendicular */
    check = up[2] * fwd[2] + up[0] * fwd[0] + fwd[1] * up[1];
    if ((*(uint32_t *)&check & 0x7f800000u) == 0x7f800000u ||
        fabsf(check) >= (float)*(double *)0x2549d8) {
      goto orthogonalize;
    }

    return;

  orthogonalize: {
    float right[3];
    float mag;

    /* right = cross(fwd, up) */
    right[0] = up[2] * fwd[1] - fwd[2] * up[1];
    right[1] = up[0] * fwd[2] - up[2] * fwd[0];
    right[2] = up[1] * fwd[0] - up[0] * fwd[1];

    /* fwd = cross(up, right) */
    fwd[0] = right[2] * up[1] - right[1] * up[2];
    fwd[1] = right[0] * up[2] - right[2] * up[0];
    fwd[2] = right[1] * up[0] - right[0] * up[1];

    /* Normalize up */
    mag = sqrtf(up[0] * up[0] + up[1] * up[1] + up[2] * up[2]);
    if (fabsf(mag) >= (float)*(double *)0x2533d0) {
      float inv = *(float *)0x2533c8 / mag;
      up[0] = inv * up[0];
      up[1] = inv * up[1];
      up[2] = inv * up[2];
    }

    /* Normalize forward */
    mag = sqrtf(fwd[0] * fwd[0] + fwd[1] * fwd[1] + fwd[2] * fwd[2]);
    if (fabsf(mag) >= (float)*(double *)0x2533d0) {
      float inv = *(float *)0x2533c8 / mag;
      fwd[0] = inv * fwd[0];
      fwd[1] = inv * fwd[1];
      fwd[2] = inv * fwd[2];
    }
  }
  }
}

/* Validate two orientation axis-pairs and compute angular velocity delta
 * between them (0x8c030). Validates that (forward0, up0) and (forward1, up1)
 * are each a valid perpendicular pair, builds rotation matrices from each,
 * then extracts the angular velocity vector between them into result_angular.
 * forward0/up0 come from state+0x20/+0x2c; forward1/up1 from
 * velocities+0x20/+0x2c. The caller (FUN_0008c440) passes these via EDI/ESI
 * (forward0/up0) and EBX (up1) in the binary; here normalised as C params. */
void FUN_0008c030(float *forward1, float *result_angular, float *forward0,
                  float *up0, float *up1)
{
  float mat0[13]; /* 3x4 matrix (13 floats, padded to 52 bytes) */
  float mat1[13];

  if (!valid_real_normal3d_perpendicular(forward0, up0)) {
    csprintf(
      (char *)0x5ab100,
      "%s, %s: assert_valid_real_vector3d_axes2(%f, %f, %f / %f, %f, %f)",
      "forward0", (char *)0x2674e0, (double)forward0[0], (double)forward0[1],
      (double)forward0[2], (double)up0[0], (double)up0[1], (double)up0[2]);
    display_assert((char *)0x5ab100, "c:\\halo\\SOURCE\\camera\\observer.c",
                   0x382, 1);
    system_exit(-1);
  }
  if (!valid_real_normal3d_perpendicular(forward1, up1)) {
    csprintf(
      (char *)0x5ab100,
      "%s, %s: assert_valid_real_vector3d_axes2(%f, %f, %f / %f, %f, %f)",
      "forward1", (char *)0x267488, (double)forward1[0], (double)forward1[1],
      (double)forward1[2], (double)up1[0], (double)up1[1], (double)up1[2]);
    display_assert((char *)0x5ab100, "c:\\halo\\SOURCE\\camera\\observer.c",
                   0x383, 1);
    system_exit(-1);
  }
  matrix_from_forward_and_up(mat0, forward0, up0);
  matrix_from_forward_and_up(mat1, forward1, up1);
  quaternion_to_angle_and_vector(mat0, mat1, result_angular);
}

/* Near-plane collision fix for the camera focus distance (0x8c150).
 * Casts collision rays from the focus position along the up and right (cross
 * product of up and forward) directions, scaled by a near-plane factor
 * proportional to focus_distance. Finds the closest obstruction among 4
 * directions (+/- up_scaled, +/- right_scaled), then runs a binary-search
 * refinement loop (10 iterations) to converge on the exact obstruction
 * boundary. Adjusts *focus_distance by blending the initial collision
 * fraction with the refined fraction. If no obstruction is found,
 * *focus_distance is simply scaled by the initial collision fraction. */
void FUN_0008c150(float *up, float *focus_distance, float near_plane_dist,
                  float *forward, float *position)
{
  char location[8];
  bool indoor_fog;
  float initial_fraction;
  float best_t;
  float test_fraction;
  float best_sign;
  float *best_plane;
  float adjusted_pos[3];
  float test_point[3];
  float up_scaled[3];
  float right_scaled[3];
  float fVar1;
  float dist;
  int16_t i;
  int counter;

  initial_fraction = 1.0f;

  /* Determine location and indoor fog status at the focus position */
  scenario_location_from_point(location, position);
  indoor_fog = FUN_0018f3e0(location, position, 0);

  /* Compute adjusted position: position - (near_plane_dist + *focus_distance) *
   * forward */
  dist = near_plane_dist + *focus_distance;
  adjusted_pos[0] = -(dist * forward[0]) + position[0];
  adjusted_pos[1] = -(dist * forward[1]) + position[1];
  adjusted_pos[2] = -(dist * forward[2]) + position[2];

  /* Cast initial ray from position to adjusted_pos */
  FUN_0008ab90(&initial_fraction, indoor_fog, position, adjusted_pos);

  /* Scale factor for the near-plane probe vectors */
  fVar1 = *(float *)0x2673a4 * *focus_distance;

  /* Compute scaled up vector */
  up_scaled[0] = up[0] * fVar1;
  up_scaled[1] = up[1] * fVar1;
  up_scaled[2] = up[2] * fVar1;

  /* Compute scaled right vector = cross(up, forward) * fVar1 */
  right_scaled[0] = (up[1] * forward[2] - up[2] * forward[1]) * fVar1;
  right_scaled[1] = (up[2] * forward[0] - up[0] * forward[2]) * fVar1;
  right_scaled[2] = (up[0] * forward[1] - up[1] * forward[0]) * fVar1;

  best_t = initial_fraction;
  best_plane = (float *)0;
  counter = 0;

  /* Sweep 4 directions: -up, -right, +up, +right */
  i = 0;
  do {
    float sign;
    int plane_idx;
    float *plane;

    /* sign: -1 for i=0,1; +1 for i=2,3 */
    sign = (float)(int)(((i & 2) ? 2 : 0) - 1);

    /* plane: up_scaled for even counter, right_scaled for odd */
    plane_idx = counter & 1;
    plane = (plane_idx == 0) ? up_scaled : right_scaled;

    test_point[0] = sign * plane[0] + adjusted_pos[0];
    test_point[1] = sign * plane[1] + adjusted_pos[1];
    test_point[2] = sign * plane[2] + adjusted_pos[2];

    if (FUN_0008ab90(&test_fraction, indoor_fog, position, test_point)) {
      if (test_fraction < best_t) {
        best_t = test_fraction;
        best_plane = plane;
        best_sign = sign;
      }
    }

    i = (int16_t)(i + 1);
    counter = counter + 1;
  } while (i < 4);

  if (best_plane != (float *)0) {
    /* Refinement loop: binary search along the best plane direction */
    float refinement_scale;
    float offset;
    float best_frac;
    float fraction;
    int iterations;
    float final_scale;
    float value;

    refinement_scale = best_sign;
    offset = 0.0f;
    fraction = initial_fraction;
    best_frac = best_t;
    iterations = 10;

    do {
      float step;
      bool hit;

      step = (refinement_scale + offset) * *(float *)0x253398;

      test_point[0] = step * best_plane[0] + adjusted_pos[0];
      test_point[1] = step * best_plane[1] + adjusted_pos[1];
      test_point[2] = step * best_plane[2] + adjusted_pos[2];

      hit = FUN_0008ab90(&test_fraction, indoor_fog, position, test_point);

      if (hit &&
          (float)*(double *)0x2674e8 > fabsf(test_fraction - best_frac)) {
        /* Converged: update the refinement boundary */
        best_frac = test_fraction;
        refinement_scale = step;
      } else {
        /* Did not converge: record the step as offset */
        offset = step;
        if (!hit) {
          fraction = *(float *)0x2533c8;
        } else {
          fraction = test_fraction;
        }
      }

      iterations = iterations - 1;
    } while (iterations != 0);

    /* Determine final_scale from refinement results.
     * Reference (LAB_0008c3cf in delinked observer.obj): the "test $5,ah; jp"
     * takes the branch when fraction >= best_frac, selecting
     * value = (refinement_scale >= C0); the fall-through (fraction < best_frac)
     * selects value = offset. The comparison was previously inverted (> vs <),
     * which flipped the sign of the lerp scale below and collapsed the vehicle
     * chase distance onto the focus point. */
    if (fraction < best_frac) {
      value = offset;
    } else {
      value = (float)(int)(refinement_scale >= *(float *)0x2533c0);
    }

    if (value == *(float *)0x2533c0) {
      /* Negate path */
      if (fraction < best_frac) {
        final_scale = -offset;
      } else {
        final_scale = -refinement_scale;
      }
    } else {
      if (fraction < best_frac) {
        final_scale = offset;
      } else {
        final_scale = refinement_scale;
      }
    }

    *focus_distance = (final_scale * initial_fraction +
                       (*(float *)0x2533c8 - final_scale) * best_t) *
                      *focus_distance;
    return;
  }

  /* No obstruction found: scale focus_distance by initial fraction */
  *focus_distance = initial_fraction * *focus_distance;
}

/* Compute linear and angular velocity deltas between velocities and state
 * (0x8c440). Takes three observer sub-arrays: velocities, result (output),
 * and state. Subtracts state[0..7] from velocities[0..7] into result[0..7]
 * (8 linear floats). Then calls FUN_0008c030 once to compute the angular
 * delta between the forward/up orientation pair at offset +8 (floats) in
 * velocities and state, storing the result into result+8.
 *
 * Register args: result, state. Stack arg: velocities. */
void FUN_0008c440(void *velocities, void *result, void *state)
{
  float *velocities_f;
  float *result_f;
  float *state_f;
  int i;

  velocities_f = (float *)velocities;
  result_f = (float *)result;
  state_f = (float *)state;

  /* Loop 1: 8 iterations — linear component subtraction */
  for (i = 0; i < 8; i++) {
    result_f[i] = velocities_f[i] - state_f[i];
  }

  /* Loop 2: 1 iteration — angular component via orientation matrices */
  FUN_0008c030(velocities_f + 8, /* forward1 */
               result_f + 8, /* result_angular output */
               state_f + 8, /* forward0 */
               state_f + 8 + 3, /* up0 (= state+0x2c from base) */
               velocities_f + 8 + 3); /* up1 (= velocities+0x2c from base) */
}

/* Derive the final observer camera result from staged and integrated state
 * (0x8c4b0). Reads the observer's computed focus position, focus offset,
 * focus distance, forward/up vectors, and field of view. Applies focus offset
 * rotation using the XY-normalized forward vector, optionally runs near-plane
 * collision fix, computes camera position = focus - distance*forward, queries
 * the BSP for cluster location, adjusts Z for ground penetration, validates
 * all results, clamps to world bounds, and copies the final camera state
 * (position, forward, up, velocity, FOV) into the observer result area. */
void observer_update_result(int16_t local_player_index)
{
  char *observer;
  float *forward;
  float *up;
  float focus_position[3];
  float focus_distance;
  float fov;
  float mag_xy, inv_mag;
  float fwd_n_x, fwd_n_y;
  float height_diff;
  int location[2]; /* {leaf_index, cluster_index(int16 at +4)} */

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  observer = (char *)0x33571c + (int)local_player_index * 0x29c;

  /* Read focus position from observer+0xb0 */
  focus_position[0] = *(float *)(observer + 0xb0);
  focus_position[1] = *(float *)(observer + 0xb4);
  focus_position[2] = *(float *)(observer + 0xb8);

  /* Clamp focus distance to [0, max_distance], or FLT_MAX if over */
  {
    float fd = *(float *)(observer + 0xc8);
    if (fd < *(float *)0x2533c0) {
      focus_distance = 0.0f;
    } else if (fd > *(float *)0x2548fc) {
      focus_distance = 3.4028235e+38f;
    } else {
      focus_distance = fd;
    }
  }

  /* assert: valid_world_real_point3d(&focus_position) */
  if ((*(uint32_t *)&focus_position[0] & 0x7f800000u) == 0x7f800000u ||
      focus_position[0] < *(float *)0x266e98 ||
      focus_position[0] > *(float *)0x266e94 ||
      (*(uint32_t *)&focus_position[1] & 0x7f800000u) == 0x7f800000u ||
      focus_position[1] < *(float *)0x266e98 ||
      focus_position[1] > *(float *)0x266e94 ||
      (*(uint32_t *)&focus_position[2] & 0x7f800000u) == 0x7f800000u ||
      focus_position[2] < *(float *)0x266e98 ||
      focus_position[2] > *(float *)0x266e94) {
    display_assert("valid_world_real_point3d(&focus_position)",
                   "c:\\halo\\SOURCE\\camera\\observer.c", 0x3af, 1);
    system_exit(-1);
  }

  /* Validate forward/up axes */
  forward = (float *)(observer + 0xd0);
  up = (float *)(observer + 0xdc);
  if (!valid_real_normal3d_perpendicular(forward, up)) {
    csprintf(
      (char *)0x5ab100,
      "%s, %s: assert_valid_real_vector3d_axes2(%f, %f, %f / %f, %f, %f)",
      "&observer->forward", "&observer->up", (double)forward[0],
      (double)forward[1], (double)forward[2], (double)up[0], (double)up[1],
      (double)up[2]);
    display_assert((char *)0x5ab100, "c:\\halo\\SOURCE\\camera\\observer.c",
                   0x3b0, 1);
    system_exit(-1);
  }

  /* assert: valid_world_real_point3d(&observer->focus_offset) */
  if ((*(uint32_t *)(observer + 0xbc) & 0x7f800000u) == 0x7f800000u ||
      *(float *)(observer + 0xbc) < *(float *)0x266e98 ||
      *(float *)(observer + 0xbc) > *(float *)0x266e94 ||
      (*(uint32_t *)(observer + 0xc0) & 0x7f800000u) == 0x7f800000u ||
      *(float *)(observer + 0xc0) < *(float *)0x266e98 ||
      *(float *)(observer + 0xc0) > *(float *)0x266e94 ||
      (*(uint32_t *)(observer + 0xc4) & 0x7f800000u) == 0x7f800000u ||
      *(float *)(observer + 0xc4) < *(float *)0x266e98 ||
      *(float *)(observer + 0xc4) > *(float *)0x266e94) {
    display_assert(
      "valid_world_real_point3d((real_point3d *) &observer->focus_offset)",
      "c:\\halo\\SOURCE\\camera\\observer.c", 0x3b1, 1);
    system_exit(-1);
  }

  /* assert: valid_focus_distance(focus_distance) */
  if ((*(uint32_t *)&focus_distance & 0x7f800000u) == 0x7f800000u ||
      focus_distance < *(float *)0x2533c0 ||
      focus_distance > *(float *)0x266e94) {
    display_assert("valid_focus_distance(focus_distance)",
                   "c:\\halo\\SOURCE\\camera\\observer.c", 0x3b2, 1);
    system_exit(-1);
  }

  /* Clamp field_of_view to [fov_min, fov_max] */
  {
    float f = *(float *)(observer + 0xcc);
    if (f < *(float *)0x255ef8) {
      fov = *(float *)0x255ef8;
    } else if (f > *(float *)0x2568bc) {
      fov = *(float *)0x2568bc;
    } else {
      fov = f;
    }
    *(float *)(observer + 0xcc) = fov;
  }

  /* Clamp focus_position components to [-5000, 5000] */
  if (focus_position[0] < *(float *)0x266e98) {
    focus_position[0] = -5000.0f;
  } else if (focus_position[0] > *(float *)0x266e94) {
    focus_position[0] = 5000.0f;
  }

  if (focus_position[1] < *(float *)0x266e98) {
    focus_position[1] = -5000.0f;
  } else if (focus_position[1] > *(float *)0x266e94) {
    focus_position[1] = 5000.0f;
  }

  if (focus_position[2] < *(float *)0x266e98) {
    focus_position[2] = -5000.0f;
  } else if (focus_position[2] > *(float *)0x266e94) {
    focus_position[2] = 5000.0f;
  }

  /* Clamp focus_distance to [0, 5000] */
  if (focus_distance < *(float *)0x2533c0) {
    focus_distance = 0.0f;
  } else if (focus_distance > *(float *)0x266e94) {
    focus_distance = 5000.0f;
  }

  /* Normalize forward vector in XY plane */
  fwd_n_x = forward[0];
  fwd_n_y = forward[1];
  mag_xy = sqrtf(fwd_n_x * fwd_n_x + fwd_n_y * fwd_n_y);
  if (fabsf(mag_xy) >= (float)*(double *)0x2533d0) {
    inv_mag = *(float *)0x2533c8 / mag_xy;
    fwd_n_x = inv_mag * fwd_n_x;
    fwd_n_y = inv_mag * fwd_n_y;
  }

  /* Apply rotated focus_offset to focus_position using normalized forward */
  focus_position[0] = fwd_n_x * *(float *)(observer + 0xbc) +
                      fwd_n_y * *(float *)(observer + 0xc0) + focus_position[0];
  focus_position[1] = (fwd_n_y * *(float *)(observer + 0xbc) -
                       fwd_n_x * *(float *)(observer + 0xc0)) +
                      focus_position[1];
  focus_position[2] = focus_position[2] + *(float *)(observer + 0xc4);

  /* Near-plane collision fix (skip if mode bit 0x10 set or focus_distance == 0)
   */
  if ((*(uint8_t *)(observer + 0x8) & 0x10) == 0 &&
      focus_distance != *(float *)0x2533c0) {
    FUN_0008c150(up, &focus_distance, 0.02f, forward, focus_position);
  }

  /* Compute result.position = focus_position - focus_distance * forward */
  *(float *)(observer + 0x74) = focus_position[0] - focus_distance * forward[0];
  *(float *)(observer + 0x78) = focus_position[1] - focus_distance * forward[1];
  *(float *)(observer + 0x7c) = focus_position[2] - focus_distance * forward[2];

  /* Determine BSP cluster location for the camera position */
  scenario_location_from_point(&location, observer + 0x74);

  /* If cluster changed, precache resources for the new cluster */
  {
    int16_t cluster = *(int16_t *)((char *)&location + 4);
    if (cluster != -1) {
      if (cluster != *(int16_t *)(observer + 0x84)) {
        void *element = tag_block_get_element((char *)scenario_get() + 0x134,
                                              (int)cluster, 0x68);
        predicted_resources_precache((int *)((char *)element + 0x28));
      }
      *(int *)(observer + 0x80) = location[0];
      *(int *)(observer + 0x84) = *(int *)((char *)&location + 4);
    }
  }

  /* Ground height adjustment */
  {
    float h = FUN_0018f510(observer + 0x80, observer + 0x74);
    height_diff = h;
    if (fabsf(height_diff) < (float)*(double *)0x25f0c8) {
      if (height_diff <= *(float *)0x2533c0) {
        *(float *)(observer + 0x7c) =
          height_diff + *(float *)(observer + 0x7c) + *(float *)0x2533e8;
      } else {
        *(float *)(observer + 0x7c) =
          *(float *)(observer + 0x7c) - (*(float *)0x2533e8 - height_diff);
      }
    }
  }

  /* assert: valid_world_real_point3d(&observer->result.position) */
  if ((*(uint32_t *)(observer + 0x74) & 0x7f800000u) == 0x7f800000u ||
      *(float *)(observer + 0x74) < *(float *)0x266e98 ||
      *(float *)(observer + 0x74) > *(float *)0x266e94 ||
      (*(uint32_t *)(observer + 0x78) & 0x7f800000u) == 0x7f800000u ||
      *(float *)(observer + 0x78) < *(float *)0x266e98 ||
      *(float *)(observer + 0x78) > *(float *)0x266e94 ||
      (*(uint32_t *)(observer + 0x7c) & 0x7f800000u) == 0x7f800000u ||
      *(float *)(observer + 0x7c) < *(float *)0x266e98 ||
      *(float *)(observer + 0x7c) > *(float *)0x266e94) {
    display_assert("valid_world_real_point3d(&observer->result.position)",
                   "c:\\halo\\SOURCE\\camera\\observer.c", 0x41f, 1);
    system_exit(-1);
  }

  /* Validate forward/up axes again */
  if (!valid_real_normal3d_perpendicular(forward, up)) {
    csprintf(
      (char *)0x5ab100,
      "%s, %s: assert_valid_real_vector3d_axes2(%f, %f, %f / %f, %f, %f)",
      "&observer->forward", "&observer->up", (double)forward[0],
      (double)forward[1], (double)forward[2], (double)up[0], (double)up[1],
      (double)up[2]);
    display_assert((char *)0x5ab100, "c:\\halo\\SOURCE\\camera\\observer.c",
                   0x420, 1);
    system_exit(-1);
  }

  /* assert: valid_field_of_view(observer->field_of_view) */
  if ((*(uint32_t *)(observer + 0xcc) & 0x7f800000u) == 0x7f800000u ||
      *(float *)(observer + 0xcc) < *(float *)0x255ef8 ||
      *(float *)(observer + 0xcc) > *(float *)0x2568bc) {
    display_assert("valid_field_of_view(observer->field_of_view)",
                   "c:\\halo\\SOURCE\\camera\\observer.c", 0x421, 1);
    system_exit(-1);
  }

  /* Clamp result.position to world bounds */
  {
    float v;
    v = *(float *)(observer + 0x74);
    if (v < *(float *)0x266e98) {
      v = *(float *)0x266e98;
    } else if (v > *(float *)0x266e94) {
      v = *(float *)0x266e94;
    }
    *(float *)(observer + 0x74) = v;

    v = *(float *)(observer + 0x78);
    if (v < *(float *)0x266e98) {
      v = *(float *)0x266e98;
    } else if (v > *(float *)0x266e94) {
      v = *(float *)0x266e94;
    }
    *(float *)(observer + 0x78) = v;

    v = *(float *)(observer + 0x7c);
    if (v < *(float *)0x266e98) {
      v = *(float *)0x266e98;
    } else if (v > *(float *)0x266e94) {
      v = *(float *)0x266e94;
    }
    *(float *)(observer + 0x7c) = v;
  }

  /* Copy forward -> result.forward, negate velocities -> result.velocity,
   * copy up -> result.up, copy field_of_view -> result.field_of_view */
  *(float *)(observer + 0x94) = forward[0];
  *(float *)(observer + 0x88) = -*(float *)(observer + 0xe8);
  *(float *)(observer + 0x98) = forward[1];
  *(float *)(observer + 0x9c) = forward[2];
  *(float *)(observer + 0x8c) = -*(float *)(observer + 0xec);
  *(float *)(observer + 0x90) = -*(float *)(observer + 0xf0);
  *(float *)(observer + 0xa0) = up[0];
  *(float *)(observer + 0xa4) = up[1];
  *(float *)(observer + 0xac) = *(float *)(observer + 0xcc);
  *(float *)(observer + 0xa8) = up[2];
}

/* Compute observer velocities from current and target state (0x8ccf0).
 * Dispatches to FUN_0008c440 (linear+angular delta) with pointers into the
 * observer struct: velocities at +0xc, result at +0x260, state at +0xb0. */
void observer_compute_velocities(int16_t local_player_index)
{
  char *observer;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  observer = (char *)0x33571c + (int)local_player_index * 0x29c;
  FUN_0008c440(observer + 0xc, observer + 0x260, observer + 0xb0);
}

/* Update observer position timers and integration (0x8cd40).
 * Validates the player index, checks if the observer is paused (bit 0x20
 * of the byte pointed to by observer+0x4), then dispatches five internal
 * sub-update functions and clamps 5 timer floats at observer+0x5c. */
void observer_update_positions(int16_t local_player_index)
{
  int i;
  char *observer;
  float *timers;
  float val;

  assert_halt(local_player_index >= 0 &&
              local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  observer = (char *)0x33571c + (int)(int16_t)local_player_index * 0x29c;
  timers = (float *)(observer + 0x5c);

  if ((*(unsigned char *)(*(int *)(observer + 0x4)) & 0x20) == 0) {
    observer_compute_velocities(local_player_index);
    observer_compute_accelerations(local_player_index);
    observer_apply_acceleration(local_player_index);
    observer_integrate(local_player_index);
    observer_compute_update(local_player_index);

    for (i = 5; i != 0; i--) {
      val = *timers - *(float *)0x335718;
      if (val <= *(float *)0x2533c0) {
        val = *(float *)0x2533c0;
      }
      *timers = val;
      timers++;
    }
  }
}

/* Per-tick observer update for all local players (0x8cde0).
 * Saves the frame's delta-time into the global at 0x335718, then walks
 * each of MAXIMUM_NUMBER_OF_LOCAL_PLAYERS observers (stride 0x29c from
 * 0x33571c), verifies the header/trailer OBSERVER_SIGNATURE ('!dar' =
 * 0x72616421) and that updated_for_frame is clear, marks it set, and
 * dispatches three observer sub-updates:
 *   - observer_update_command (0x8b060): copies/stages camera block from
 *     director into observer state
 *   - observer_update_positions (0x8cd40): time-dependent integration,
 *     skipped when delta_time matches the cached value at 0x2533c0
 *   - observer_update_result (0x8c4b0): derives the final observer camera
 *     result from staged and integrated state */
void observer_update(float delta_time)
{
  int16_t i;
  char *observer = (char *)0x33571c;

  *(float *)0x335718 = delta_time;

  for (i = 0; i < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS; i++, observer += 0x29c) {
    if (local_player_get_player_index(i) == -1)
      continue;

    if (i < 0 || i >= MAXIMUM_NUMBER_OF_LOCAL_PLAYERS) {
      display_assert("local_player_index>=0 && "
                     "local_player_index<MAXIMUM_NUMBER_OF_LOCAL_PLAYERS",
                     "c:\\halo\\SOURCE\\camera\\observer.c", 0x72, 1);
      system_exit(-1);
    }

    if (*(int *)(observer + 0x0) != 0x72616421 ||
        *(int *)(observer + 0x298) != 0x72616421) {
      display_assert("observer->header_signature==OBSERVER_SIGNATURE && "
                     "observer->trailer_signature==OBSERVER_SIGNATURE",
                     "c:\\halo\\SOURCE\\camera\\observer.c", 0x108, 1);
      system_exit(-1);
    }

    if (*(char *)(observer + 0x70) != 0) {
      display_assert("!observer->updated_for_frame",
                     "c:\\halo\\SOURCE\\camera\\observer.c", 0x109, 1);
      system_exit(-1);
    }

    *(char *)(observer + 0x70) = 1;

    observer_update_command(i);

    if (*(float *)0x335718 != *(float *)0x2533c0) {
      observer_update_positions(i);
    }

    observer_update_result(i);

    if (*(int *)(observer + 0x0) != 0x72616421 ||
        *(int *)(observer + 0x298) != 0x72616421) {
      display_assert("observer->header_signature==OBSERVER_SIGNATURE && "
                     "observer->trailer_signature==OBSERVER_SIGNATURE",
                     "c:\\halo\\SOURCE\\camera\\observer.c", 0x117, 1);
      system_exit(-1);
    }
  }
}
/* --- observer.obj batch drafts (2026-07-26) --- */

/* FUN_00089240 (0x89240) — readable C lift. */
void FUN_00089240(int object_handle, void *arg)
{
  char *obj = (char *)object_get_and_verify_type(object_handle, 3);
  first_person_camera_for_unit_and_vector(obj + 0x1ec, object_handle, arg);
}

/* first_person_camera_update (0x89270) — XBE naked draft (batch 138). */
#if defined(__clang__)
static int (*const b89270_cb6870)(int16_t local_player_index) = player_control_get_unit_index;
static void (*const b89270_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b89270_exitfn)(int) = system_exit;
static float * (*const b89270_cb7f10)(int16_t local_player_index, float *out_direction) = player_control_get_facing_direction;
static void (*const b89270_c88d50)(void *, int, void *) = first_person_camera_for_unit_and_vector;
static float (*const b89270_cb6690)(int16_t local_player_index) = player_control_get_field_of_view;

__attribute__((naked, noinline))
void first_person_camera_update(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[cb6870]\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "addl $4, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .Lfirst_person_camera_update_1\n\t"
      "pushl $1\n\t"
      "pushl $0x9d\n\t"
      "pushl $0x26720c\n\t"
      "pushl $0x266e9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lfirst_person_camera_update_1:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lfirst_person_camera_update_2\n\t"
      "pushl $1\n\t"
      "pushl $0x9e\n\t"
      "pushl $0x26720c\n\t"
      "pushl $0x25f120\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lfirst_person_camera_update_2:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw (%%edi), %%dx\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[cb7f10]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "call *%[c88d50]\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[cb6690]\n\t"
      "fsts 0x20(%%esi)\n\t"
      "fcoms (%%ebx)\n\t"
      "addl $0xc, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Lfirst_person_camera_update_3\n\t"
      "popl %%edi\n\t"
      "movl $0x3e3851ec, 0x60(%%esi)\n\t"
      "movb $1, 0x4f(%%esi)\n\t"
      "fstps (%%ebx)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lfirst_person_camera_update_3:\n\t"
      "popl %%edi\n\t"
      "fstp %%st(0)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cb6870] "m"(b89270_cb6870), [assert] "m"(b89270_assert), [exitfn] "m"(b89270_exitfn), [cb7f10] "m"(b89270_cb7f10), [c88d50] "m"(b89270_c88d50), [cb6690] "m"(b89270_cb6690)
      : "memory");
}
#else
#error "first_person_camera_update: clang naked draft required"
#endif


/* FUN_00089330 (0x89330) — readable C lift. */
void FUN_00089330(float *out)
{
  out[1] = 0.0f;
  out[0] = 0.0f;
  out[3] = 0.0f;
  out[4] = 0.0f;
  out[5] = 0.0f;
  out[6] = 1.2222222f; /* 0x3f9c61aa */
}

/* FUN_00089350 (0x89350) — readable C lift. */
void FUN_00089350(float *dst, float *forward, float *angles_vector)
{
  unsigned int fov_bits = 0x3f9c61aau;

  dst[1] = 0.0f;
  dst[0] = 0.0f;
  dst[4] = 0.0f;
  dst[5] = 0.0f;
  dst[3] = 0.0f;
  *(unsigned int *)(dst + 6) = fov_bits;
  dst[0] = forward[0];
  dst[1] = forward[1];
  dst[2] = forward[2];
  vector_to_angles(dst + 3, angles_vector);
}

/* flying_camera_update (0x893a0) — XBE naked draft (batch 107). */
#if defined(__clang__)
static void (*const b893a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b893a0_exitfn)(int) = system_exit;
static void (*const b893a0_c10cc40)(float *out, float *angles) = angles_to_vector;
static void (*const b893a0_c8aa80)(float *forward, float *up) = observer_up_from_forward;
static void (*const b893a0_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;
static bool (*const b893a0_c84a70)(float *a, float *b) = valid_real_normal3d_perpendicular;
static int (*const b893a0_c84a10)(float *vector) = real_vector3d_valid;
static char * (*const b893a0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;

__attribute__((naked, noinline))
void flying_camera_update(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lflying_camera_update_1\n\t"
      "pushl $1\n\t"
      "pushl $0x29\n\t"
      "pushl $0x267284\n\t"
      "pushl $0x266e9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lflying_camera_update_1:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .Lflying_camera_update_2\n\t"
      "pushl $1\n\t"
      "pushl $0x2a\n\t"
      "pushl $0x267284\n\t"
      "pushl $0x2671f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lflying_camera_update_2:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "jne .Lflying_camera_update_3\n\t"
      "pushl $1\n\t"
      "pushl $0x2b\n\t"
      "pushl $0x267284\n\t"
      "pushl $0x25f120\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".Lflying_camera_update_3:\n\t"
      "movb 0x2(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lflying_camera_update_6\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fadds 0xc(%%edi)\n\t"
      "fstps 0xc(%%edi)\n\t"
      "flds 0xc(%%ebx)\n\t"
      "fadds 0x10(%%edi)\n\t"
      "fcoms 0x2671f4\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lflying_camera_update_4\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2671f4\n\t"
      "jmp .Lflying_camera_update_5\n\t"
      ".Lflying_camera_update_4:\n\t"
      "fcoms 0x2671f0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lflying_camera_update_5\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2671f0\n\t"
      ".Lflying_camera_update_5:\n\t"
      "fstps 0x10(%%edi)\n\t"
      "flds 0x10(%%ebx)\n\t"
      "fadds 0x14(%%edi)\n\t"
      "fstps 0x14(%%edi)\n\t"
      ".Lflying_camera_update_6:\n\t"
      "cmpw %%cx, 0x325716\n\t"
      "jle .Lflying_camera_update_7\n\t"
      "movl %%ecx, 0xc(%%edi)\n\t"
      "movl %%ecx, 0x10(%%edi)\n\t"
      "movl %%ecx, 0x14(%%edi)\n\t"
      "decw 0x325716\n\t"
      ".Lflying_camera_update_7:\n\t"
      "leal 0xc(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x24(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "movl $0x3e99999a, 0x48(%%esi)\n\t"
      "call *%[c10cc40]\n\t"
      "leal 0x30(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8aa80]\n\t"
      "flds 0x14(%%edi)\n\t"
      "fcos\n\t"
      "addl $8, %%esp\n\t"
      "leal 0x30(%%esi), %%eax\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0x14(%%edi)\n\t"
      "fsin\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[rots]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movb 0x2(%%eax), %%cl\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lflying_camera_update_8\n\t"
      "flds 0xc(%%edi)\n\t"
      "fcos\n\t"
      "flds 0xc(%%edi)\n\t"
      "fsin\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x14(%%eax)\n\t"
      "fld %%st(1)\n\t"
      "fmuls 0x18(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fmuls 0x14(%%eax)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x18(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x1c(%%eax)\n\t"
      "movl %%edi, %%eax\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fadds (%%edi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "fxch %%st(1)\n\t"
      "fadds 0x4(%%edi)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "fadds 0x8(%%edi)\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      ".Lflying_camera_update_8:\n\t"
      "movl %%edi, %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movl 0x31fc38, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "leal 0x10(%%esi), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl $0, 0x1c(%%esi)\n\t"
      "movl 0x18(%%edi), %%edx\n\t"
      "leal 0x30(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "movl %%edx, 0x20(%%esi)\n\t"
      "movl $1, (%%esi)\n\t"
      "call *%[c84a70]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lflying_camera_update_9\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "je .Lflying_camera_update_9\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lflying_camera_update_9\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lflying_camera_update_9\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "je .Lflying_camera_update_9\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lflying_camera_update_9\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lflying_camera_update_9\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "je .Lflying_camera_update_9\n\t"
      "flds 0xc(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lflying_camera_update_9\n\t"
      "flds 0xc(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lflying_camera_update_9\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "je .Lflying_camera_update_9\n\t"
      "flds 0x10(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lflying_camera_update_9\n\t"
      "flds 0x10(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lflying_camera_update_9\n\t"
      "movl 0x14(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "je .Lflying_camera_update_9\n\t"
      "flds 0x14(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lflying_camera_update_9\n\t"
      "flds 0x14(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lflying_camera_update_9\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "je .Lflying_camera_update_9\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lflying_camera_update_9\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lflying_camera_update_9\n\t"
      "leal 0x3c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lflying_camera_update_9\n\t"
      "movl $0, 0xc(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "je .Lflying_camera_update_9\n\t"
      "movl 0x20(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "je .Lflying_camera_update_9\n\t"
      "flds 0x20(%%esi)\n\t"
      "fcomps 0x255ef8\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lflying_camera_update_9\n\t"
      "flds 0x20(%%esi)\n\t"
      "fcomps 0x2568bc\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lflying_camera_update_9\n\t"
      "movl 0x48(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "je .Lflying_camera_update_9\n\t"
      "flds 0x48(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lflying_camera_update_9\n\t"
      "flds 0x48(%%esi)\n\t"
      "fcomps 0x266e90\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lflying_camera_update_10\n\t"
      ".Lflying_camera_update_9:\n\t"
      "flds 0x48(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0x95\n\t"
      "pushl $0x267284\n\t"
      "pushl $1\n\t"
      "subl $0x28, %%esp\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds 0x20(%%esi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x44(%%esi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x40(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x3c(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0\n\t"
      "flds 0x18(%%esi)\n\t"
      "pushl $0\n\t"
      "subl $0x60, %%esp\n\t"
      "fstpl 0x58(%%esp)\n\t"
      "flds 0x14(%%esi)\n\t"
      "fstpl 0x50(%%esp)\n\t"
      "flds 0x10(%%esi)\n\t"
      "fstpl 0x48(%%esp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fstpl 0x40(%%esp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fstpl 0x38(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl 0x30(%%esp)\n\t"
      "flds 0x38(%%esi)\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x34(%%esi)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x266e08\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x9c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lflying_camera_update_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b893a0_assert), [exitfn] "m"(b893a0_exitfn), [c10cc40] "m"(b893a0_c10cc40), [c8aa80] "m"(b893a0_c8aa80), [rots] "m"(b893a0_rots), [c84a70] "m"(b893a0_c84a70), [c84a10] "m"(b893a0_c84a10), [c8d9d0] "m"(b893a0_c8d9d0)
      : "memory");
}
#else
#error "flying_camera_update: clang naked draft required"
#endif


/* following_camera_new (0x89850) — readable C lift. */
void following_camera_new(void *camera)
{
  if (!camera) {
    display_assert((const char *)0x266e9c, (const char *)0x2672ac, 0x13, true);
    system_exit(-1);
  }
  *((unsigned char *)camera + 0) = 0;
  *((unsigned char *)camera + 1) = 0;
  *((unsigned char *)camera + 2) = 0;
  *((unsigned char *)camera + 3) = 0;
  *(unsigned short *)((char *)camera + 4) = 0;
  *(int *)((char *)camera + 0x14) = 0;
  *(int *)((char *)camera + 0x10) = 0;
  *(int *)((char *)camera + 8) = -1;
  *(unsigned short *)((char *)camera + 0xc) = 0xffff;
  *(int *)((char *)camera + 0x18) = 0x3f800000;
}

/* FUN_000898b0 (0x898b0) — XBE naked draft (batch 154). */
#if defined(__clang__)
static void *(*const b898b0_get)(int, int) = object_get_and_verify_type;
static void *(*const b898b0_tryget)(int, int) = object_try_and_get_and_verify_type;
static void *(*const b898b0_tag)(int, int) = tag_get;
static void *(*const b898b0_elem)(void *, int, int) = tag_block_get_element;

__attribute__((naked, noinline))
void FUN_000898b0(void)
{
  __asm__ volatile(
      "pushl %%esi\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xcc(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000898b0_1\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000898b0_1\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x76656869\n\t"
      "call *%[tag]\n\t"
      "movswl 0x2a0(%%esi), %%edx\n\t"
      "pushl $0x11c\n\t"
      "pushl %%edx\n\t"
      "addl $0x2e4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movb (%%eax), %%cl\n\t"
      "addl $0x14, %%esp\n\t"
      "testb $0x15, %%cl\n\t"
      "je .LFUN_000898b0_1\n\t"
      "addl $0x84, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000898b0_2\n\t"
      ".LFUN_000898b0_1:\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "addl $0x1a8, %%eax\n\t"
      ".LFUN_000898b0_2:\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [get] "m"(b898b0_get), [tryget] "m"(b898b0_tryget), [tag] "m"(b898b0_tag), [elem] "m"(b898b0_elem)
      : "memory");
}
#else
#error "FUN_000898b0: clang naked draft required"
#endif


/* FUN_00089930 (0x89930) — readable C lift.
 * Load float arg into the x87 stack and call FUN_001da0cc. */
void FUN_00089930(float value)
{
  ((void (*)(float))(void *)FUN_001da0cc)(value);
}

/* FUN_00089940 (0x89940) — XBE naked draft (batch 136). */
#if defined(__clang__)
static void (*const b89940_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b89940_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_00089940(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "flds 0x1c(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00089940_1\n\t"
      "pushl $1\n\t"
      "pushl $0x5e4\n\t"
      "pushl $0x25ed80\n\t"
      "pushl $0x2672f4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00089940_1:\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fcomps 0x18(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00089940_2\n\t"
      "flds 0x1c(%%ebp)\n\t"
      "fmuls 0x254644\n\t"
      "fadds 0x18(%%ebp)\n\t"
      "fcomps 0x20(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_00089940_3\n\t"
      ".LFUN_00089940_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x5e5\n\t"
      "pushl $0x25ed80\n\t"
      "pushl $0x2672d8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00089940_3:\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fsubs 0x10(%%ebp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fsubs 0xc(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fsubs 0x8(%%ebp)\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "fstps 0x14(%%ebp)\n\t"
      "fsubs 0xc(%%ebp)\n\t"
      "flds 0x1c(%%ebp)\n\t"
      ".byte 0xdc, 0xc0\n\t"
      "flds 0x18(%%ebp)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fsubrs 0x20(%%ebp)\n\t"
      "flds 0x14(%%ebp)\n\t"
      ".byte 0xd8, 0xe3\n\t"
      ".byte 0xde, 0xc9\n\t"
      "flds 0x1c(%%ebp)\n\t"
      "fmuls 0x254644\n\t"
      ".byte 0xde, 0xf9\n\t"
      ".byte 0xde, 0xc2\n\t"
      "flds 0x18(%%ebp)\n\t"
      "fadds 0x1c(%%ebp)\n\t"
      "fsubrs 0x20(%%ebp)\n\t"
      ".byte 0xde, 0xca\n\t"
      "fxch %%st(1)\n\t"
      ".byte 0xd8, 0xf1\n\t"
      "fadds 0xc(%%ebp)\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fsubs 0x18(%%ebp)\n\t"
      "fdivs 0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xc9\n\t"
      "fadds 0x8(%%ebp)\n\t"
      "fstp %%st(1)\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b89940_assert), [exitfn] "m"(b89940_exitfn)
      : "memory");
}
#else
#error "FUN_00089940: clang naked draft required"
#endif


/* FUN_00089a20 (0x89a20) — XBE naked draft (batch 139). */
#if defined(__clang__)
static void (*const b89a20_c89940)(void) = FUN_00089940;

__attribute__((naked, noinline))
void FUN_00089a20(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x1c(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x24(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x20(%%ebp), %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c89940]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "fstps (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c89940]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "fstps 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl 0x8(%%edx), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ecx), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c89940]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "addl $0x54, %%esp\n\t"
      "fstps 0x8(%%edx)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c89940] "m"(b89a20_c89940)
      : "memory");
}
#else
#error "FUN_00089a20: clang naked draft required"
#endif


/* camera_track_splut (0x89ab0) — XBE naked draft (batch 122). */
#if defined(__clang__)
static void *(*const b89ab0_elem)(void *, int, int) = tag_block_get_element;
static void * (*const b89ab0_c18e450)(void) = game_globals_get;
static void *(*const b89ab0_tag)(int, int) = tag_get;
static void (*const b89ab0_ftol)(void) = FUN_001d9068;
static void (*const b89ab0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b89ab0_exitfn)(int) = system_exit;
static void (*const b89ab0_c89a20)(void) = FUN_00089a20;

__attribute__((naked, noinline))
void camera_track_splut(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x4c(%%ecx), %%eax\n\t"
      "addl $0x4c, %%ecx\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lcamera_track_splut_1\n\t"
      "decl %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "testl %%eax, %%eax\n\t"
      "setge %%dl\n\t"
      "pushl $0x1c\n\t"
      "decl %%edx\n\t"
      "andl %%edx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lcamera_track_splut_1\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lcamera_track_splut_2\n\t"
      ".Lcamera_track_splut_1:\n\t"
      "pushl $0x10\n\t"
      "pushl $0\n\t"
      "call *%[c18e450]\n\t"
      "addl $0x104, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lcamera_track_splut_2:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x7472616b\n\t"
      "call *%[tag]\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fadds 0x2568bc\n\t"
      "movl 0x4(%%eax), %%ebx\n\t"
      "leal 0x4(%%eax), %%esi\n\t"
      "leal -0x1(%%ebx), %%eax\n\t"
      "fmuls 0x267328\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "fildl -0x4(%%ebp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "call *%[ftol]\n\t"
      "flds 0x2533c8\n\t"
      "cmpl $4, %%ebx\n\t"
      ".byte 0xd8, 0xf1\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%eax, %%edi\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "jge .Lcamera_track_splut_3\n\t"
      "pushl $1\n\t"
      "pushl $0x56\n\t"
      "pushl $0x2672ac\n\t"
      "pushl $0x267300\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl %%edi, %%eax\n\t"
      ".Lcamera_track_splut_3:\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lcamera_track_splut_6\n\t"
      "movl (%%esi), %%edx\n\t"
      ".Lcamera_track_splut_4:\n\t"
      "movswl %%di, %%ecx\n\t"
      "leal 0x4(%%ecx), %%ebx\n\t"
      "cmpl %%edx, %%ebx\n\t"
      "jg .Lcamera_track_splut_5\n\t"
      "movswl %%ax, %%ebx\n\t"
      "decl %%ebx\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "jle .Lcamera_track_splut_6\n\t"
      ".Lcamera_track_splut_5:\n\t"
      "decl %%edi\n\t"
      "testw %%di, %%di\n\t"
      "jg .Lcamera_track_splut_4\n\t"
      ".Lcamera_track_splut_6:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movswl %%di, %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "leal 0x3(%%edi), %%eax\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl $0x3c\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3c\n\t"
      "leal 0x2(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3c\n\t"
      "leal 0x1(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3c\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c89a20]\n\t"
      "addl $0x20, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b89ab0_elem), [c18e450] "m"(b89ab0_c18e450), [tag] "m"(b89ab0_tag), [ftol] "m"(b89ab0_ftol), [assert] "m"(b89ab0_assert), [exitfn] "m"(b89ab0_exitfn), [c89a20] "m"(b89ab0_c89a20)
      : "memory");
}
#else
#error "camera_track_splut: clang naked draft required"
#endif


/* FUN_00089c00 (0x89c00) — XBE naked draft (batch 133). */
#if defined(__clang__)
static void *(*const b89c00_get)(int, int) = object_get_and_verify_type;
static void (*const b89c00_c898b0)(void) = FUN_000898b0;
static void (*const b89c00_useat)(int, float *) = unit_set_seat_state;
static void (*const b89c00_c1da0cc)(void) = FUN_001da0cc;
static void (*const b89c00_c89ab0)(void) = camera_track_splut;

__attribute__((naked, noinline))
void FUN_00089c00(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c898b0]\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[useat]\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "addl $0x1ec, %%ebx\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%ebx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ebx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "flds 0x8(%%esi)\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%edx\n\t"
      "call *%[c1da0cc]\n\t"
      "pushl %%ecx\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "call *%[c89ab0]\n\t"
      "flds (%%esi)\n\t"
      "flds 0x4(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00089c00_1\n\t"
      "fdivrs 0x2533c8\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xde, 0xcb\n\t"
      ".byte 0xde, 0xc9\n\t"
      "jmp .LFUN_00089c00_2\n\t"
      ".LFUN_00089c00_1:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00089c00_2:\n\t"
      "flds -0xc(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "flds -0x10(%%ebp)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds (%%edi)\n\t"
      "fstps (%%edi)\n\t"
      "flds -0x10(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "flds -0xc(%%ebp)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fadds 0x4(%%edi)\n\t"
      "fstps 0x4(%%edi)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fadds 0x8(%%edi)\n\t"
      "fstps 0x8(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b89c00_get), [c898b0] "m"(b89c00_c898b0), [useat] "m"(b89c00_useat), [c1da0cc] "m"(b89c00_c1da0cc), [c89ab0] "m"(b89c00_c89ab0)
      : "memory");
}
#else
#error "FUN_00089c00: clang naked draft required"
#endif


/* following_camera_update (0x89cd0) — XBE naked draft (batch 105). */
#if defined(__clang__)
static void (*const b89cd0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b89cd0_exitfn)(int) = system_exit;
static void (*const b89cd0_cb6740)(int16_t local_player_index, void *out_info) = player_control_get_unit_camera_info;
static void *(*const b89cd0_get)(int, int) = object_get_and_verify_type;
static float * (*const b89cd0_cb7e30)(int16_t local_player_index) = player_control_get_facing_angles;
static void (*const b89cd0_c10cc40)(float *out, float *angles) = angles_to_vector;
static void (*const b89cd0_c89ab0)(void) = camera_track_splut;
static void (*const b89cd0_c140070)(int object_handle, float *position_out, float *direction_out) = object_get_root_location;
static void (*const b89cd0_c8aa80)(float *forward, float *up) = observer_up_from_forward;
static bool (*const b89cd0_c84a70)(float *a, float *b) = valid_real_normal3d_perpendicular;
static int (*const b89cd0_c84a10)(float *vector) = real_vector3d_valid;
static char * (*const b89cd0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;

__attribute__((naked, noinline))
void following_camera_update(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x2c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lfollowing_camera_update_1\n\t"
      "pushl $1\n\t"
      "pushl $0x8a\n\t"
      "pushl $0x2672ac\n\t"
      "pushl $0x266e9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lfollowing_camera_update_1:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lfollowing_camera_update_2\n\t"
      "pushl $1\n\t"
      "pushl $0x8b\n\t"
      "pushl $0x2672ac\n\t"
      "pushl $0x25f120\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lfollowing_camera_update_2:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%ebx), %%cx\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[cb6740]\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movw -0x28(%%ebp), %%cx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movl $0, 0x48(%%esi)\n\t"
      "movl $0, (%%esi)\n\t"
      "movl $0x3f9c61aa, 0x20(%%esi)\n\t"
      "movb (%%edi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "je .Lfollowing_camera_update_4\n\t"
      "cmpl 0x8(%%edi), %%eax\n\t"
      "jne .Lfollowing_camera_update_3\n\t"
      "cmpw 0xc(%%edi), %%cx\n\t"
      "je .Lfollowing_camera_update_4\n\t"
      ".Lfollowing_camera_update_3:\n\t"
      "movl $0x3f800000, 0x48(%%esi)\n\t"
      ".Lfollowing_camera_update_4:\n\t"
      "movw %%cx, 0xc(%%edi)\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, 0x8(%%edi)\n\t"
      "je .Lfollowing_camera_update_20\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movb 0x1b8(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $3, %%cl\n\t"
      "jne .Lfollowing_camera_update_5\n\t"
      "xorb %%cl, %%cl\n\t"
      "jmp .Lfollowing_camera_update_6\n\t"
      ".Lfollowing_camera_update_5:\n\t"
      "movb $1, %%cl\n\t"
      ".Lfollowing_camera_update_6:\n\t"
      "cmpb 0x2(%%edi), %%cl\n\t"
      "je .Lfollowing_camera_update_9\n\t"
      "flds 0x253398\n\t"
      "movb $1, 0x4d(%%esi)\n\t"
      "fcomps 0x58(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lfollowing_camera_update_7\n\t"
      "flds 0x253398\n\t"
      "jmp .Lfollowing_camera_update_8\n\t"
      ".Lfollowing_camera_update_7:\n\t"
      "flds 0x58(%%esi)\n\t"
      ".Lfollowing_camera_update_8:\n\t"
      "fstps 0x58(%%esi)\n\t"
      "movb %%cl, 0x2(%%edi)\n\t"
      ".Lfollowing_camera_update_9:\n\t"
      "movb 0x2(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lfollowing_camera_update_11\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fadds 0x10(%%edi)\n\t"
      "fstps 0x10(%%edi)\n\t"
      "flds 0xc(%%ebx)\n\t"
      "fadds 0x14(%%edi)\n\t"
      "fstps 0x14(%%edi)\n\t"
      "movb $1, 0x50(%%esi)\n\t"
      "flds 0x253524\n\t"
      "fcomps 0x64(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lfollowing_camera_update_10\n\t"
      "flds 0x253524\n\t"
      "fstps 0x64(%%esi)\n\t"
      "jmp .Lfollowing_camera_update_13\n\t"
      ".Lfollowing_camera_update_10:\n\t"
      "flds 0x64(%%esi)\n\t"
      "fstps 0x64(%%esi)\n\t"
      "jmp .Lfollowing_camera_update_13\n\t"
      ".Lfollowing_camera_update_11:\n\t"
      "flds 0x10(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lfollowing_camera_update_12\n\t"
      "flds 0x14(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Lfollowing_camera_update_13\n\t"
      ".Lfollowing_camera_update_12:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, 0x14(%%edi)\n\t"
      "movl %%eax, 0x10(%%edi)\n\t"
      ".Lfollowing_camera_update_13:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw (%%ebx), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[cb7e30]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fadds 0x10(%%edi)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fadds 0x14(%%edi)\n\t"
      "fcoms 0x2568b8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lfollowing_camera_update_14\n\t"
      "fstp %%st(0)\n\t"
      "movl $0xbfc90fdb, -0x4(%%ebp)\n\t"
      "jmp .Lfollowing_camera_update_16\n\t"
      ".Lfollowing_camera_update_14:\n\t"
      "fcoms 0x2568bc\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lfollowing_camera_update_15\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3fc90fdb, -0x4(%%ebp)\n\t"
      "jmp .Lfollowing_camera_update_16\n\t"
      ".Lfollowing_camera_update_15:\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".Lfollowing_camera_update_16:\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x24(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c10cc40]\n\t"
      "flds 0x8(%%ebx)\n\t"
      "flds 0x4(%%ebx)\n\t"
      "addl $8, %%esp\n\t"
      "flds (%%ebx)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fcomps 0x267388\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lfollowing_camera_update_17\n\t"
      "flds 0x8(%%ebx)\n\t"
      "flds 0x4(%%ebx)\n\t"
      "flds (%%ebx)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fcomps 0x267384\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lfollowing_camera_update_18\n\t"
      ".Lfollowing_camera_update_17:\n\t"
      "pushl $1\n\t"
      "pushl $0xd4\n\t"
      "pushl $0x2672ac\n\t"
      "pushl $0x267330\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lfollowing_camera_update_18:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c89ab0]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fsts 0x1c(%%esi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcos\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fmuls 0x18(%%edi)\n\t"
      "fstps 0x10(%%esi)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x18(%%edi)\n\t"
      "fchs\n\t"
      "fstps 0x14(%%esi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fsin\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fmuls 0x18(%%edi)\n\t"
      "fstps 0x18(%%esi)\n\t"
      "fsubs 0x253f3c\n\t"
      "fmuls 0x18(%%edi)\n\t"
      "fadds 0x253f3c\n\t"
      "fcoms 0x253f3c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lfollowing_camera_update_19\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x253f3c\n\t"
      ".Lfollowing_camera_update_19:\n\t"
      "movl -0x2c(%%ebp), %%ecx\n\t"
      "fstps 0x1c(%%esi)\n\t"
      "pushl $0\n\t"
      "leal 0x3c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c140070]\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "orl $1, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      ".Lfollowing_camera_update_20:\n\t"
      "leal 0x30(%%esi), %%ebx\n\t"
      "leal 0x24(%%esi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "call *%[c8aa80]\n\t"
      "movb (%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb $1, %%al\n\t"
      "je .Lfollowing_camera_update_22\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[c84a70]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lfollowing_camera_update_21\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "je .Lfollowing_camera_update_21\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lfollowing_camera_update_21\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lfollowing_camera_update_21\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "je .Lfollowing_camera_update_21\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lfollowing_camera_update_21\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lfollowing_camera_update_21\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "je .Lfollowing_camera_update_21\n\t"
      "flds 0xc(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lfollowing_camera_update_21\n\t"
      "flds 0xc(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lfollowing_camera_update_21\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "je .Lfollowing_camera_update_21\n\t"
      "flds 0x10(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lfollowing_camera_update_21\n\t"
      "flds 0x10(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lfollowing_camera_update_21\n\t"
      "movl 0x14(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "je .Lfollowing_camera_update_21\n\t"
      "flds 0x14(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lfollowing_camera_update_21\n\t"
      "flds 0x14(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lfollowing_camera_update_21\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "je .Lfollowing_camera_update_21\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lfollowing_camera_update_21\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lfollowing_camera_update_21\n\t"
      "leal 0x3c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lfollowing_camera_update_21\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "je .Lfollowing_camera_update_21\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lfollowing_camera_update_21\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lfollowing_camera_update_21\n\t"
      "movl 0x20(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "je .Lfollowing_camera_update_21\n\t"
      "flds 0x20(%%esi)\n\t"
      "fcomps 0x255ef8\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lfollowing_camera_update_21\n\t"
      "flds 0x20(%%esi)\n\t"
      "fcomps 0x2568bc\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lfollowing_camera_update_21\n\t"
      "movl 0x48(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      "je .Lfollowing_camera_update_21\n\t"
      "flds 0x48(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lfollowing_camera_update_21\n\t"
      "flds 0x48(%%esi)\n\t"
      "fcomps 0x266e90\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lfollowing_camera_update_22\n\t"
      ".Lfollowing_camera_update_21:\n\t"
      "movl (%%esi), %%eax\n\t"
      "flds 0x48(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0xee\n\t"
      "pushl $0x2672ac\n\t"
      "pushl %%eax\n\t"
      "subl $0x90, %%esp\n\t"
      "fstpl 0x88(%%esp)\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "flds 0x20(%%esi)\n\t"
      "fstpl 0x80(%%esp)\n\t"
      "flds 0x44(%%esi)\n\t"
      "fstpl 0x78(%%esp)\n\t"
      "flds 0x40(%%esi)\n\t"
      "fstpl 0x70(%%esp)\n\t"
      "flds 0x3c(%%esi)\n\t"
      "fstpl 0x68(%%esp)\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fstpl 0x60(%%esp)\n\t"
      "flds 0x18(%%esi)\n\t"
      "fstpl 0x58(%%esp)\n\t"
      "flds 0x14(%%esi)\n\t"
      "fstpl 0x50(%%esp)\n\t"
      "flds 0x10(%%esi)\n\t"
      "fstpl 0x48(%%esp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fstpl 0x40(%%esp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fstpl 0x38(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl 0x30(%%esp)\n\t"
      "flds 0x38(%%esi)\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x34(%%esi)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds (%%ebx)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%ecx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x266e08\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x9c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lfollowing_camera_update_22:\n\t"
      "movb $1, (%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b89cd0_assert), [exitfn] "m"(b89cd0_exitfn), [cb6740] "m"(b89cd0_cb6740), [get] "m"(b89cd0_get), [cb7e30] "m"(b89cd0_cb7e30), [c10cc40] "m"(b89cd0_c10cc40), [c89ab0] "m"(b89cd0_c89ab0), [c140070] "m"(b89cd0_c140070), [c8aa80] "m"(b89cd0_c8aa80), [c84a70] "m"(b89cd0_c84a70), [c84a10] "m"(b89cd0_c84a10), [c8d9d0] "m"(b89cd0_c8d9d0)
      : "memory");
}
#else
#error "following_camera_update: clang naked draft required"
#endif


/* observer_command_has_finished (0x8a570) — readable C lift. */
char observer_command_has_finished(short index)
{
  char *base;
  short i;

  if (index < 0 || index >= 4) {
    display_assert((const char *)0x266fc0, (const char *)0x2673a8, 0x72, true);
    system_exit(-1);
  }
  base = (char *)0x33571c + (int)index * 0x29c;
  if (*(float *)(base + 0x50) != *(float *)0x2533c0)
    return 0;
  for (i = 0; i < 5; i++) {
    if (*(float *)(base + 0x5c + (int)i * 4) != *(float *)0x2533c0)
      return 0;
  }
  return 1;
}

/* observer_reconnect_to_structure_bsp (0x8a5f0) — readable C lift. */
void observer_reconnect_to_structure_bsp(void)
{
  extern char DAT_00266fc0[];
  extern char DAT_002673a8[];
  int16_t i;
  char *obs = (char *)0x33579c;

  for (i = 0; i < 4; i++, obs += 0x29c) {
    if (local_player_get_player_index(i) == -1)
      continue;
    if (i < 0 || i >= 4) {
      display_assert(DAT_00266fc0, DAT_002673a8, 0x72, 1);
      system_exit(-1);
    }
    scenario_location_from_point(obs, obs - 0xc);
  }
}


/* observer_obsolete_position (0x8aa30) — readable C lift. */
void observer_obsolete_position(int16_t a0)
{
  if ((int16_t)a0 < 0 || (int16_t)a0 >= 4) {
    display_assert((const char *)0x266fc0, (const char *)0x2673a8, 0x72, 1);
    system_exit(-1);
  }
  observer_result_initialize((void *)(0x33571c + (int)(int16_t)a0 * 0x29c));
}

/* observer_up_from_forward (0x8aa80) — readable C lift. */
void observer_up_from_forward(float *forward, float *up)
{
  float tmp[3];
  float len;

  tmp[0] = forward[1];
  tmp[1] = -forward[0];
  tmp[2] = 0.0f;
  len = normalize3d(tmp);
  if (len == *(float *)0x2533c0) {
    tmp[0] = 1.0f;
    tmp[1] = 0.0f;
    tmp[2] = 0.0f;
  }
  /* up = cross(tmp, forward) */
  up[0] = tmp[1] * forward[2] - tmp[2] * forward[1];
  up[1] = tmp[2] * forward[0] - tmp[0] * forward[2];
  up[2] = tmp[0] * forward[1] - tmp[1] * forward[0];
}

/* FUN_0008ab10 (0x8ab10) — XBE naked draft (batch 148). */
#if defined(__clang__)
static float (*const b8ab10_norm)(float *) = normalize3d;
static void (*const b8ab10_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;

__attribute__((naked, noinline))
void FUN_0008ab10(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcoms 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_0008ab10_1\n\t"
      "fld %%st(0)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "fsin\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "fcos\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[rots]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[rots]\n\t"
      "addl $0x20, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0008ab10_1:\n\t"
      "fstp %%st(0)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [norm] "m"(b8ab10_norm), [rots] "m"(b8ab10_rots)
      : "memory");
}
#else
#error "FUN_0008ab10: clang naked draft required"
#endif


/* FUN_0008ac70 (0x8ac70) — readable C lift. */
bool FUN_0008ac70(float scale, float *out_fraction, bool indoor, float *delta, float *base, float *ray_origin)
{
  float end[3];
  end[0] = scale * delta[0] + base[0];
  end[1] = scale * delta[1] + base[1];
  end[2] = scale * delta[2] + base[2];
  return FUN_0008ab90(out_fraction, indoor, ray_origin, end);
}

/* observer_set_camera (0x8acb0) — XBE naked draft (batch 110). */
#if defined(__clang__)
static void (*const b8acb0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b8acb0_exitfn)(int) = system_exit;
static bool (*const b8acb0_c84a70)(float *a, float *b) = valid_real_normal3d_perpendicular;
static int (*const b8acb0_c84a10)(float *vector) = real_vector3d_valid;
static char * (*const b8acb0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void *(*const b8acb0_memset)(void *, int, unsigned int) = csmemset;

__attribute__((naked, noinline))
void observer_set_camera(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movw 0x8(%%ebp), %%si\n\t"
      "testw %%si, %%si\n\t"
      "pushl %%edi\n\t"
      "jl .Lobserver_set_camera_1\n\t"
      "cmpw $4, %%si\n\t"
      "jl .Lobserver_set_camera_2\n\t"
      ".Lobserver_set_camera_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x72\n\t"
      "pushl $0x2673a8\n\t"
      "pushl $0x266fc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobserver_set_camera_2:\n\t"
      "movswl %%si, %%edi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "imull $0x29c, %%edi, %%edi\n\t"
      "addl $0x33571c, %%edi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lobserver_set_camera_3\n\t"
      "testb $1, (%%esi)\n\t"
      "je .Lobserver_set_camera_4\n\t"
      "leal 0x30(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x24(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c84a70]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobserver_set_camera_3\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "je .Lobserver_set_camera_3\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lobserver_set_camera_3\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lobserver_set_camera_3\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "je .Lobserver_set_camera_3\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lobserver_set_camera_3\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lobserver_set_camera_3\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "je .Lobserver_set_camera_3\n\t"
      "flds 0xc(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lobserver_set_camera_3\n\t"
      "flds 0xc(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lobserver_set_camera_3\n\t"
      "movl 0x10(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "je .Lobserver_set_camera_3\n\t"
      "flds 0x10(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lobserver_set_camera_3\n\t"
      "flds 0x10(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lobserver_set_camera_3\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "je .Lobserver_set_camera_3\n\t"
      "flds 0x14(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lobserver_set_camera_3\n\t"
      "flds 0x14(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lobserver_set_camera_3\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "je .Lobserver_set_camera_3\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lobserver_set_camera_3\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lobserver_set_camera_3\n\t"
      "leal 0x3c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lobserver_set_camera_3\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "je .Lobserver_set_camera_3\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lobserver_set_camera_3\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lobserver_set_camera_3\n\t"
      "movl 0x20(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "je .Lobserver_set_camera_3\n\t"
      "flds 0x20(%%esi)\n\t"
      "fcomps 0x255ef8\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lobserver_set_camera_3\n\t"
      "flds 0x20(%%esi)\n\t"
      "fcomps 0x2568bc\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lobserver_set_camera_3\n\t"
      "movl 0x48(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "je .Lobserver_set_camera_3\n\t"
      "flds 0x48(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lobserver_set_camera_3\n\t"
      "flds 0x48(%%esi)\n\t"
      "fcomps 0x266e90\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lobserver_set_camera_4\n\t"
      ".Lobserver_set_camera_3:\n\t"
      "movl (%%esi), %%eax\n\t"
      "flds 0x48(%%esi)\n\t"
      "pushl $1\n\t"
      "pushl $0xe9\n\t"
      "pushl $0x2673a8\n\t"
      "pushl %%eax\n\t"
      "subl $0x90, %%esp\n\t"
      "fstpl 0x88(%%esp)\n\t"
      "flds 0x20(%%esi)\n\t"
      "fstpl 0x80(%%esp)\n\t"
      "flds 0x44(%%esi)\n\t"
      "fstpl 0x78(%%esp)\n\t"
      "flds 0x40(%%esi)\n\t"
      "fstpl 0x70(%%esp)\n\t"
      "flds 0x3c(%%esi)\n\t"
      "fstpl 0x68(%%esp)\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fstpl 0x60(%%esp)\n\t"
      "flds 0x18(%%esi)\n\t"
      "fstpl 0x58(%%esp)\n\t"
      "flds 0x14(%%esi)\n\t"
      "fstpl 0x50(%%esp)\n\t"
      "flds 0x10(%%esi)\n\t"
      "fstpl 0x48(%%esp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fstpl 0x40(%%esp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fstpl 0x38(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl 0x30(%%esp)\n\t"
      "flds 0x38(%%esi)\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x34(%%esi)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds 0x30(%%esi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds 0x24(%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x266e08\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x9c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lobserver_set_camera_4:\n\t"
      "movb 0x71(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl %%esi, 0x4(%%edi)\n\t"
      "movb $0, 0x70(%%edi)\n\t"
      "jne .Lobserver_set_camera_5\n\t"
      "movb $1, 0x71(%%edi)\n\t"
      "movl $0, 0x48(%%esi)\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "orl $8, (%%eax)\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "pushl $0x14\n\t"
      "addl $0x54, %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lobserver_set_camera_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b8acb0_assert), [exitfn] "m"(b8acb0_exitfn), [c84a70] "m"(b8acb0_c84a70), [c84a10] "m"(b8acb0_c84a10), [c8d9d0] "m"(b8acb0_c8d9d0), [memset] "m"(b8acb0_memset)
      : "memory");
}
#else
#error "observer_set_camera: clang naked draft required"
#endif


/* FUN_0008cf10 (0x8cf10) — readable C lift. */
void FUN_0008cf10(float *angles, float pitch, float *vec)
{
  angles[2] = pitch;
  vector_to_angles(angles, vec);
}

/* FUN_0008cf30 (0x8cf30) — XBE naked draft (batch 108). */
#if defined(__clang__)
static void (*const b8cf30_cb6740)(int16_t local_player_index, void *out_info) = player_control_get_unit_camera_info;
static void (*const b8cf30_c86220)(int16_t player_index) = director_set_local_player_context;
static void (*const b8cf30_c10cc40)(float *out, float *angles) = angles_to_vector;
static void (*const b8cf30_c8aa80)(float *forward, float *up) = observer_up_from_forward;
static void (*const b8cf30_c140070)(int object_handle, float *position_out, float *direction_out) = object_get_root_location;
static bool (*const b8cf30_c84a70)(float *a, float *b) = valid_real_normal3d_perpendicular;
static int (*const b8cf30_c84a10)(float *vector) = real_vector3d_valid;
static char * (*const b8cf30_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b8cf30_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b8cf30_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_0008cf30(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%ebx), %%cx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[cb6740]\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "movb 0x2(%%ebx), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0008cf30_3\n\t"
      "flds (%%edi)\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "fstps (%%edi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs 0xc(%%ebx)\n\t"
      "fcoms 0x267208\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0008cf30_1\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x267208\n\t"
      "jmp .LFUN_0008cf30_2\n\t"
      ".LFUN_0008cf30_1:\n\t"
      "fcoms 0x267204\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0008cf30_2\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x267204\n\t"
      ".LFUN_0008cf30_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      "fstps 0x4(%%edi)\n\t"
      "movw (%%ebx), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c86220]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_0008cf30_3:\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fmuls 0x259ec0\n\t"
      "fsubrs 0x8(%%edi)\n\t"
      "fcoms 0x253f3c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0008cf30_4\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x253f3c\n\t"
      ".LFUN_0008cf30_4:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "fstps 0x8(%%edi)\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0008cf30_5\n\t"
      "leal 0x24(%%esi), %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c10cc40]\n\t"
      "leal 0x30(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8aa80]\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "leal 0x3c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c140070]\n\t"
      "flds 0x2676ac\n\t"
      "fadds 0xc(%%esi)\n\t"
      "addl $0x1c, %%esp\n\t"
      "movl $1, (%%esi)\n\t"
      "fstps 0xc(%%esi)\n\t"
      ".LFUN_0008cf30_5:\n\t"
      "movl 0x31fc38, %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "leal 0x10(%%esi), %%ebx\n\t"
      "movl %%ebx, %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl 0x26769c, %%eax\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl 0x2676a8, %%ecx\n\t"
      "movl %%eax, 0x20(%%esi)\n\t"
      "testb $1, (%%esi)\n\t"
      "movl %%edx, 0x1c(%%esi)\n\t"
      "movl %%ecx, 0x48(%%esi)\n\t"
      "je .LFUN_0008cf30_7\n\t"
      "leal 0x30(%%esi), %%edi\n\t"
      "leal 0x24(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "call *%[c84a70]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0008cf30_6\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "je .LFUN_0008cf30_6\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0008cf30_6\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_0008cf30_6\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "je .LFUN_0008cf30_6\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0008cf30_6\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_0008cf30_6\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "je .LFUN_0008cf30_6\n\t"
      "flds 0xc(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0008cf30_6\n\t"
      "flds 0xc(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_0008cf30_6\n\t"
      "movl (%%ebx), %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "je .LFUN_0008cf30_6\n\t"
      "flds (%%ebx)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0008cf30_6\n\t"
      "flds (%%ebx)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_0008cf30_6\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "je .LFUN_0008cf30_6\n\t"
      "flds 0x14(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0008cf30_6\n\t"
      "flds 0x14(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_0008cf30_6\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "je .LFUN_0008cf30_6\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x266e98\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0008cf30_6\n\t"
      "flds 0x18(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_0008cf30_6\n\t"
      "leal 0x3c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0008cf30_6\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7f800000, %%ecx\n\t"
      "cmpl $0x7f800000, %%ecx\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "je .LFUN_0008cf30_6\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0008cf30_6\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fcomps 0x266e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_0008cf30_6\n\t"
      "movl 0x26769c, %%edx\n\t"
      "movl %%edx, %%eax\n\t"
      "andl $0x7f800000, %%eax\n\t"
      "cmpl $0x7f800000, %%eax\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "je .LFUN_0008cf30_6\n\t"
      "flds 0x26769c\n\t"
      "fcomps 0x255ef8\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0008cf30_6\n\t"
      "flds 0x26769c\n\t"
      "fcomps 0x2568bc\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_0008cf30_6\n\t"
      "movl 0x2676a8, %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x7f800000, %%edx\n\t"
      "cmpl $0x7f800000, %%edx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "je .LFUN_0008cf30_6\n\t"
      "flds 0x2676a8\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0008cf30_6\n\t"
      "flds 0x2676a8\n\t"
      "fcomps 0x266e90\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_0008cf30_7\n\t"
      ".LFUN_0008cf30_6:\n\t"
      "movl (%%esi), %%eax\n\t"
      "flds 0x2676a8\n\t"
      "pushl $1\n\t"
      "pushl $0x47\n\t"
      "pushl $0x2676b0\n\t"
      "pushl %%eax\n\t"
      "subl $0x90, %%esp\n\t"
      "fstpl 0x88(%%esp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "flds 0x26769c\n\t"
      "fstpl 0x80(%%esp)\n\t"
      "flds 0x44(%%esi)\n\t"
      "fstpl 0x78(%%esp)\n\t"
      "flds 0x40(%%esi)\n\t"
      "fstpl 0x70(%%esp)\n\t"
      "flds 0x3c(%%esi)\n\t"
      "fstpl 0x68(%%esp)\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fstpl 0x60(%%esp)\n\t"
      "flds 0x18(%%esi)\n\t"
      "fstpl 0x58(%%esp)\n\t"
      "flds 0x14(%%esi)\n\t"
      "fstpl 0x50(%%esp)\n\t"
      "flds (%%ebx)\n\t"
      "fstpl 0x48(%%esp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fstpl 0x40(%%esp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fstpl 0x38(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl 0x30(%%esp)\n\t"
      "flds 0x38(%%esi)\n\t"
      "fstpl 0x28(%%esp)\n\t"
      "flds 0x34(%%esi)\n\t"
      "fstpl 0x20(%%esp)\n\t"
      "flds (%%edi)\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%eax)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x266e08\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x9c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0008cf30_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cb6740] "m"(b8cf30_cb6740), [c86220] "m"(b8cf30_c86220), [c10cc40] "m"(b8cf30_c10cc40), [c8aa80] "m"(b8cf30_c8aa80), [c140070] "m"(b8cf30_c140070), [c84a70] "m"(b8cf30_c84a70), [c84a10] "m"(b8cf30_c84a10), [c8d9d0] "m"(b8cf30_c8d9d0), [assert] "m"(b8cf30_assert), [exitfn] "m"(b8cf30_exitfn)
      : "memory");
}
#else
#error "FUN_0008cf30: clang naked draft required"
#endif


/* FUN_0008d3a0 (0x8d3a0) — readable C lift. */
void FUN_0008d3a0(float *dst, float *a, float b, float *c, float *d, float e, float f, float g)
{
  dst[0] = a[0];
  dst[1] = a[1];
  dst[2] = a[2];
  dst[3] = b;
  dst[4] = c[0];
  dst[5] = c[1];
  dst[6] = c[2];
  dst[7] = d[0];
  dst[8] = d[1];
  dst[9] = d[2];
  dst[10] = e;
  dst[11] = f;
  *((unsigned char *)dst + 0x34) = 0;
  dst[12] = g;
}

