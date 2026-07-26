/* Allocate a new particle system header and initialize it (0xa1210).
 * Copies position, velocity, and tint/orientation data into the datum,
 * resolves lighting color via FUN_00139480, then runs setup (FUN_000a0fd0).
 * Returns the datum handle, or -1 on failure. */
int FUN_000a1210(int tag_index, float *position, float *velocity,
                 void *ext_data, float scale)
{
  int handle;
  char *datum;
  char local_buf[12];

  handle = data_new_at_index(particle_system_header_data);
  if (handle != -1) {
    datum = (char *)datum_get(particle_system_header_data, handle);
    *(int *)(datum + 0x08) = tag_index;
    *(int *)(datum + 0x0c) = -1;

    *(float *)(datum + 0x20) = position[0];
    *(float *)(datum + 0x24) = position[1];
    *(float *)(datum + 0x28) = position[2];

    *(float *)(datum + 0x2c) = velocity[0];
    *(float *)(datum + 0x30) = velocity[1];
    *(float *)(datum + 0x34) = velocity[2];

    *(float *)(datum + 0x38) = ((float *)ext_data)[0];
    *(float *)(datum + 0x3c) = ((float *)ext_data)[1];
    *(float *)(datum + 0x40) = ((float *)ext_data)[2];
    *(float *)(datum + 0x44) = ((float *)ext_data)[3];

    *(float *)(datum + 0x14) = scale;
    *(uint32_t *)(datum + 0x04) |= 1;

    FUN_00139480((void *)(datum + 0x20), (void *)(datum + 0x48), local_buf, 0);

    if (!FUN_000a0fd0(handle)) {
      datum_delete(particle_system_header_data, handle);
      return -1;
    }
  }
  return handle;
}

/* Create a particle system header from an object attachment (0xa12e0).
 * Looks up the object's particle system element at attach_index in the
 * object tag's particle_systems block (obje+0x140), copies spawn data
 * into the new datum, resolves the marker position, samples the object's
 * root location, sets up velocity and function-value flag, then calls
 * FUN_000a0fd0 to allocate the particle pool.
 * Returns the datum handle, or -1 on failure. */
int FUN_000a12e0(int particle_tag_index, int object_handle,
                 int16_t attach_index)
{
  int datum_handle;
  char *datum;
  char *object_ptr;
  char *obje_tag;
  char *ps_elem;
  char marker_buf[0x6c];

  datum_handle = data_new_at_index(particle_system_header_data);
  if (datum_handle != -1) {
    datum = (char *)datum_get(particle_system_header_data, datum_handle);
    object_ptr = (char *)object_get_and_verify_type(object_handle, -1);
    obje_tag = (char *)tag_get(0x6f626a65, *(int *)object_ptr);
    ps_elem =
      (char *)tag_block_get_element(obje_tag + 0x140, (int)attach_index, 0x48);

    *(int *)(datum + 0x8) = particle_tag_index;
    *(int *)(datum + 0xc) = object_handle;
    *(int16_t *)(datum + 0x10) = attach_index;
    *(int16_t *)(datum + 0x12) = *(int16_t *)(ps_elem + 0x30) - 1;

    if (*(int16_t *)(ps_elem + 0x34) != 0) {
      int node_idx = ((int)(*(int16_t *)(ps_elem + 0x34)) + 0x1e) * 3;
      char *node = object_ptr + node_idx * 4;
      *(int *)(datum + 0x3c) = *(int *)node;
      *(int *)(datum + 0x40) = *(int *)(node + 4);
      *(int *)(datum + 0x44) = *(int *)(node + 8);
      *(uint32_t *)(datum + 0x38) = 0x3f800000;
    } else {
      char *default_color = *(char **)0x2ee6c4;
      *(int *)(datum + 0x38) = *(int *)default_color;
      *(int *)(datum + 0x3c) = *(int *)(default_color + 4);
      *(int *)(datum + 0x40) = *(int *)(default_color + 8);
      *(int *)(datum + 0x44) = *(int *)(default_color + 12);
    }

    object_get_markers_by_string_id(object_handle, ps_elem + 0x10, marker_buf,
                                    1);
    *(int *)(datum + 0x20) = *(int *)(marker_buf + 0x60);
    *(int *)(datum + 0x24) = *(int *)(marker_buf + 0x64);
    *(int *)(datum + 0x28) = *(int *)(marker_buf + 0x68);

    object_get_root_location(object_handle, (float *)(datum + 0x2c), NULL);
    *(float *)(datum + 0x2c) *= TICKS_PER_SECOND;
    *(float *)(datum + 0x30) *= TICKS_PER_SECOND;
    *(float *)(datum + 0x34) *= TICKS_PER_SECOND;

    {
      char *default_vel = *(char **)0x2ee708;
      *(int *)(datum + 0x48) = *(int *)default_vel;
      *(int *)(datum + 0x4c) = *(int *)(default_vel + 4);
      *(int *)(datum + 0x50) = *(int *)(default_vel + 8);
    }

    {
      bool has_value;
      uint32_t f;
      has_value = (bool)object_get_function_value(
        object_handle, (int)(*(uint16_t *)(datum + 0x12)), datum + 0x14);
      f = *(uint32_t *)(datum + 0x4);
      *(uint32_t *)(datum + 0x4) = has_value ? (f | 0x1) : (f & ~0x1U);
    }

    if (!FUN_000a0fd0(datum_handle)) {
      datum_delete(particle_system_header_data, datum_handle);
      datum_handle = -1;
    }
  }
  return datum_handle;
}

void particles_initialize(void)
{
  particle_data = game_state_data_new("particle", 0x400, 0x70);
  if (!particle_data)
    error(0, "couldn't allocate particle globals");
}

void particles_initialize_for_new_map(void)
{
  data_delete_all(particle_data);
}

void particles_dispose_from_old_map(void)
{
  data_make_invalid(particle_data);
}

void particles_dispose(void)
{
  if (particle_data)
    particle_data = 0;
}

/* Delete particle datum from the particle pool (0xa14f0). */
void particle_delete(int datum_handle)
{
  datum_delete(particle_data, datum_handle);
}

/* Delete all particles owned by a local player that have an attached
   object (flag 0x40 set and object handle != -1). */
void FUN_000a1510(int16_t local_player_index)
{
  int handle;
  char *datum;

  for (handle = data_next_index(particle_data, -1); handle != -1;
       handle = data_next_index(particle_data, handle)) {
    datum = (char *)datum_get(particle_data, handle);
    if (*(uint8_t *)(datum + 0xf) == (uint8_t)local_player_index &&
        (*(uint8_t *)(datum + 2) & 0x40) != 0 && *(int *)(datum + 8) != -1) {
      datum_delete(particle_data, handle);
    }
  }
}

/* Walk all live particles and reattach each one's location to its owner
 * (0xa1590). For each particle:
 *   - If owner handle (particle+0x8) is -1 (free / unparented): use the
 *     embedded marker matrix at particle+0x30 as the position source.
 *   - Else if flag 0x40 is set in particle+0x2: position from the
 *     first-person weapon node matrix indexed by particle+0xf (marker)
 *     and particle+0xc (node).
 *   - Else: verify the owner object is still alive; if so, position
 *     from the object's node matrix; if dead, delete the particle.
 * The position pointer always advances by 0x28 (past the matrix header
 * to the translation column) before scenario_location_from_point is
 * called to write the new location at particle+0x28. If the resulting
 * scenario location's leaf index (particle+0x2c) is -1 the particle
 * has left the BSP and is deleted.
 *
 * Referenced from a function-pointer table at 0x326a20 — appears to be
 * a per-frame engine update callback. */
void FUN_000a1590(void)
{
  int handle;
  char *particle;
  int owner;
  void *position;

  handle = data_next_index(particle_data, -1);
  while (handle != -1) {
    particle = (char *)datum_get(particle_data, handle);
    owner = *(int *)(particle + 0x8);
    if (owner == -1) {
      position = particle + 0x30;
    } else {
      if ((*(uint8_t *)(particle + 0x2) & 0x40) != 0) {
        position =
          (char *)first_person_weapon_get_node_matrix(
            *(uint8_t *)(particle + 0xf), *(int16_t *)(particle + 0xc)) +
          0x28;
      } else if (object_try_and_get_and_verify_type(owner, -1) != 0) {
        position = (char *)object_get_node_matrix(
                     *(int *)(particle + 0x8), *(int16_t *)(particle + 0xc)) +
                   0x28;
      } else {
        datum_delete(particle_data, handle);
        goto next;
      }
    }
    if (position == NULL) {
      datum_delete(particle_data, handle);
    } else {
      scenario_location_from_point(particle + 0x28, position);
      if (*(int16_t *)(particle + 0x2c) == -1) {
        datum_delete(particle_data, handle);
      }
    }
  next:
    handle = data_next_index(particle_data, handle);
  }
}

/* Compute the particle's current visual size (0xa1670).
 * Interpolates between the tag's min/max size based on the ratio of
 * elapsed time to total lifetime, then scales by the particle's
 * individual size factor. Returns the interpolated size. */
float particle_get_radius(int datum_handle)
{
  char *datum;
  char *tag;

  datum = (char *)datum_get(particle_data, datum_handle);
  tag = (char *)tag_get(0x70617274, *(int *)(datum + 0x04));

  return (((*(float *)(tag + 0x78) - *(float *)(tag + 0x74)) *
           (*(float *)(datum + 0x14) / *(float *)(datum + 0x18))) +
          *(float *)(tag + 0x74)) *
         *(float *)(datum + 0x5c);
}

/* Check whether a 3D point has all finite float components (0x0a16b0).
 * Returns true if none of the three components are NaN or infinity
 * (IEEE 754 exponent field != 0x7f800000). */
bool valid_real_point3d(float *point)
{
  uint32_t *p = (uint32_t *)point;
  if ((p[0] & 0x7f800000) == 0x7f800000)
    return false;
  if ((p[1] & 0x7f800000) == 0x7f800000)
    return false;
  if ((p[2] & 0x7f800000) == 0x7f800000)
    return false;
  return true;
}

/* Validate an ARGB color (0xa1710).
 * The alpha component (color[0]) must be finite, in [0.0, 1.0],
 * and the RGB components (color[1..3]) must each be finite and valid.
 * Returns true if the color is valid. */
bool valid_real_argb_color(float *color)
{
  /* Check alpha is not NaN/Inf */
  if ((*(uint32_t *)color & 0x7f800000) == 0x7f800000)
    return false;

  /* Check alpha >= 0.0 */
  if (*color < 0.0f)
    return false;

  /* Check alpha <= 1.0 */
  if (*color > 1.0f)
    return false;

  /* Validate RGB components */
  if (!valid_real_rgb_color(color + 1))
    return false;

  return true;
}

/* Particle physics cleanup dispatch (0xa1770).
 * Called when deleting a particle that has a secondary physics tag.
 * Dispatches to effect creation ('effe') or sound playback ('snd!'). */
void FUN_000a1770(int particle, int tag_group, int physics_tag, int param)
{
  float velocity[3];
  float *default_fwd;

  velocity[0] = *(float *)(particle + 0x48) * *(float *)0x2546a4;
  velocity[1] = *(float *)(particle + 0x4c) * *(float *)0x2546a4;
  velocity[2] = *(float *)(particle + 0x50) * *(float *)0x2546a4;

  if (tag_group == 0x65666665) {
    float marker_points[6];
    float marker_forwards[6];

    marker_points[0] = *(float *)(particle + 0x30);
    marker_points[1] = *(float *)(particle + 0x34);
    marker_points[2] = *(float *)(particle + 0x38);
    marker_points[3] = *(float *)(particle + 0x30);
    marker_points[4] = *(float *)(particle + 0x34);
    marker_points[5] = *(float *)(particle + 0x38);

    marker_forwards[0] = *(float *)(particle + 0x3c);
    marker_forwards[1] = *(float *)(particle + 0x40);
    marker_forwards[2] = *(float *)(particle + 0x44);
    normalize3d(marker_forwards);

    default_fwd = *(float **)0x31fc50;
    marker_forwards[3] = default_fwd[0];
    marker_forwards[4] = default_fwd[1];
    marker_forwards[5] = default_fwd[2];

    effect_new_unattached_from_markers(
      physics_tag, -1, velocity, 2, (void *)0x2ef7d8, marker_points,
      marker_forwards, *(float *)&param, 0.0f, 0.0f, 0.0f, 0.0f);
    return;
  }

  if (tag_group == 0x736e6421) {
    float location[11];

    location[0] = *(float *)(particle + 0x30);
    location[1] = *(float *)(particle + 0x34);
    location[2] = *(float *)(particle + 0x38);

    default_fwd = *(float **)0x31fc3c;
    location[3] = default_fwd[0];
    location[4] = default_fwd[1];
    location[5] = default_fwd[2];

    location[6] = velocity[0];
    location[7] = velocity[1];
    location[8] = velocity[2];

    *(int *)&location[9] = *(int *)(particle + 0x28);
    *(int *)&location[10] = *(int *)(particle + 0x2c);

    unattached_impulse_sound_new(physics_tag, location, *(float *)&param);
    return;
  }

  display_assert(0, "c:\\halo\\SOURCE\\effects\\particles.c", 799, 1);
  system_exit(-1);
}

/* Delete a particle (0xa18c0).
 * Checks the particle tag for a secondary physics resource; if present,
 * dispatches cleanup via FUN_000a1770. Then removes the particle datum. */
void FUN_000a18c0(int datum_handle)
{
  char *datum;
  char *tag;

  datum = (char *)datum_get(particle_data, datum_handle);
  tag = (char *)tag_get(0x70617274, *(int *)(datum + 0x04));
  if (*(int *)(tag + 0x64) != -1) {
    FUN_000a1770((int)datum, *(int *)(tag + 0x58), *(int *)(tag + 0x64), 0);
  }
  datum_delete(particle_data, datum_handle);
}

/* TODO: particle_step and particle_move temporarily reverted to original
 * binary due to a stale datum handle crash during gameplay. These need
 * debugging — the implementations are preserved in git history (commit
 * 08bf664). The issue manifests as "particle index #X is unused or changed"
 * in datum_get after loading a campaign level. */

/* Set up the particle's bitmap sequence index (0xa1910).
 * Walks through up to 4 animation phases (creation, attached, detached,
 * fading) and picks a random frame range for each phase based on the
 * particle tag's sequence counts at tag offsets 0x98..0x9e.
 * Each phase accumulates the total frame offset from prior phases.
 * If the final frame index is valid within the bitmap tag's sequence
 * array, clamps it and returns true. Otherwise calls particle_delete
 * (FUN_000a18c0) and returns false. */
bool FUN_000a1910(int datum_handle)
{
  char *datum;
  char *tag;
  char *bitmap_tag;
  int16_t frame_index;
  int16_t rval;
  unsigned int *seed;

  datum = (char *)datum_get(particle_data, datum_handle);
  tag = (char *)tag_get(0x70617274, *(int *)(datum + 0x04));
  bitmap_tag = (char *)tag_get(0x6269746d, *(int *)(tag + 0x10));

  frame_index = -1;
  *(int16_t *)(datum + 0x24) = frame_index;

  /* Phase 0 → 1: creation sequence */
  if (*(char *)(datum + 0x0e) == 0) {
    if (*(int16_t *)(tag + 0x9a) > 0) {
      seed = random_math_get_local_seed_address();
      rval = random_range(seed, 0, *(int16_t *)(tag + 0x9a));
      *(int16_t *)(datum + 0x24) = *(int16_t *)(tag + 0x98) + rval;
    }
    (*(char *)(datum + 0x0e))++;
  }

  /* Check if we need to skip to phase 2 */
  if (*(int16_t *)(datum + 0x24) == -1 && *(char *)(datum + 0x0e) == 1) {
    *(char *)(datum + 0x0e) = 2;
  } else if (*(char *)(datum + 0x0e) != 2) {
    goto skip_phase2;
  }

  /* Phase 2: attached/detached transition sequence */
  if (*(float *)(datum + 0x14) >= *(float *)(datum + 0x18) ||
      *(int16_t *)(tag + 0x9c) < 1) {
    (*(char *)(datum + 0x0e))++;
  } else {
    seed = random_math_get_local_seed_address();
    rval = random_range(seed, 0, *(int16_t *)(tag + 0x9c));
    *(int16_t *)(datum + 0x24) =
      *(int16_t *)(tag + 0x9a) + *(int16_t *)(tag + 0x98) + rval;
  }

skip_phase2:
  /* Phase 3 → 4: fading sequence */
  if (*(int16_t *)(datum + 0x24) == -1 && *(char *)(datum + 0x0e) == 3) {
    if (*(int16_t *)(tag + 0x9e) > 0) {
      seed = random_math_get_local_seed_address();
      rval = random_range(seed, 0, *(int16_t *)(tag + 0x9e));
      *(int16_t *)(datum + 0x24) = *(int16_t *)(tag + 0x9c) +
                                   *(int16_t *)(tag + 0x9a) +
                                   *(int16_t *)(tag + 0x98) + rval;
    }
    (*(char *)(datum + 0x0e))++;
  }

  /* Clamp frame_index and validate against bitmap sequence count */
  frame_index = *(int16_t *)(datum + 0x24);
  if (frame_index != -1 && *(int *)(bitmap_tag + 0x54) != 0) {
    if (frame_index < 0) {
      *(int16_t *)(datum + 0x24) = 0;
      return true;
    }
    {
      int max_index = *(int *)(bitmap_tag + 0x54) - 1;
      int idx = (int)frame_index;
      if (idx > max_index)
        idx = max_index;
      *(int16_t *)(datum + 0x24) = (int16_t)idx;
    }
    return true;
  }

  /* No valid frame — delete particle */
  FUN_000a18c0(datum_handle);
  return false;
}

/* Advance particle bitmap frame counter by one step (0xa1a90).
 * Selects forward or backward animation based on datum flag bit 0x1.
 * When the last/first frame is reached, calls FUN_000a1910 to pick the
 * next sequence. Returns true while the animation is still alive. */
bool FUN_000a1a90(int datum_handle)
{
  char *datum;
  char *part_tag;
  char *bitm_tag;
  char *seq_elem;
  int16_t frame_counter;
  int frame_count;
  bool result;

  datum = (char *)datum_get(particle_data, datum_handle);
  part_tag = (char *)tag_get(0x70617274, *(int *)(datum + 0x04));
  bitm_tag = (char *)tag_get(0x6269746d, *(int *)(part_tag + 0x10));
  *(uint32_t *)(datum + 0x1c) = 0;
  if ((*(uint8_t *)(datum + 0x2) & 0x1) != 0) {
    /* Backward: decrement toward zero */
    frame_counter = *(int16_t *)(datum + 0x26);
    if (frame_counter > 0) {
      *(int16_t *)(datum + 0x26) = frame_counter - 1;
      return 1;
    }
    result = FUN_000a1910(datum_handle);
    if (result) {
      seq_elem = (char *)tag_block_get_element(
        bitm_tag + 0x54, (int)(*(int16_t *)(datum + 0x24)), 0x40);
      *(int16_t *)(datum + 0x26) = *(int16_t *)(seq_elem + 0x34) - 1;
    }
    return result;
  }
  /* Forward: increment toward frame_count */
  seq_elem = (char *)tag_block_get_element(
    bitm_tag + 0x54, (int)(*(int16_t *)(datum + 0x24)), 0x40);
  frame_count = *(int32_t *)(seq_elem + 0x34);
  frame_counter = *(int16_t *)(datum + 0x26);
  if ((int)(frame_counter + 1) < frame_count) {
    *(int16_t *)(datum + 0x26) = frame_counter + 1;
    return 1;
  }
  result = FUN_000a1910(datum_handle);
  *(int16_t *)(datum + 0x26) = 0;
  return result;
}

/* Advance particle frame timer by delta_time (0xa1b60).
 * datum_handle via @edi. Handles three animation modes via tag flags:
 *   bit 1+2: early-exit (both must be set),
 *   bit 3: random-start (advance once if delta_time != 0),
 *   default: accumulate time and advance frames in a loop.
 * Returns true while the particle is still alive. */
bool FUN_000a1b60(int datum_handle, float delta_time)
{
  char *datum;
  uint32_t flags;
  float frame_remainder;
  bool result;

  datum = (char *)datum_get(particle_data, datum_handle);
  flags = *(uint32_t *)tag_get(0x70617274, *(int *)(datum + 0x04));
  result = 1;
  if ((flags & 0x2) != 0 && (*(uint8_t *)(datum + 0x2) & 0x2) != 0)
    goto done;
  if (flags & 0x8) {
    if (delta_time != 0.0f)
      return (bool)FUN_000a1a90(datum_handle);
  } else {
    if (*(uint32_t *)(datum + 0x1c) == 0xbf800000u) {
      result = (bool)FUN_000a1a90(datum_handle);
      *(uint32_t *)(datum + 0x1c) = 0;
    }
    if (delta_time > 0.0f && result) {
      while (result) {
        frame_remainder = *(float *)(datum + 0x20) - *(float *)(datum + 0x1c);
        if (frame_remainder > delta_time) {
          *(float *)(datum + 0x1c) += delta_time;
          return result;
        }
        result = (bool)FUN_000a1a90(datum_handle);
        delta_time -= frame_remainder;
        if (delta_time <= 0.0f)
          return result;
      }
    }
  }
done:
  return result;
}

/* Step a single particle: physics, collision, effects, and aging (0xa1c30).
 * Free-floating particles run point physics (FUN_00154a50) for gravity and
 * collision; attached particles apply velocity damping. Returns false if the
 * particle was deleted during this step. */
bool FUN_000a1c30(int datum_handle, float delta_time)
{
  char *particle;
  int *tag;
  char *physics_tag;
  char *velocity;
  float collision_normal[3];
  int surface_index;
  int physics_result;
  int hit_flags;
  float speed_ratio;
  float radius;
  float drag;
  float mass_val;
  float damping;
  float new_vel_x;
  float new_vel_y;
  char stopped;

  particle = (char *)datum_get(particle_data, datum_handle);
  tag = (int *)tag_get(0x70617274, *(int *)(particle + 4));

  /* Settled/dying particle: verify parent object still exists */
  if (*(uint8_t *)(particle + 2) & 2) {
    if (*(int *)(particle + 8) == -1)
      return 1;
    if (object_try_and_get_and_verify_type(*(int *)(particle + 8), -1) != NULL)
      return 1;
    datum_delete(particle_data, datum_handle);
    return 0;
  }

  stopped = 0;
  physics_tag = (char *)tag_get(0x70706879, tag[8]);

  if (*(int *)(particle + 8) == -1) {
    /* Free-floating particle — run point physics */
    velocity = particle + 0x48;
    radius = particle_get_radius(datum_handle);

    physics_result = FUN_00154a50(
      0, (int)physics_tag, (int *)(particle + 0x28), -1,
      (float *)(particle + 0x30), (float *)(particle + 0x48), NULL,
      collision_normal, (int16_t *)&surface_index, radius, delta_time);

    hit_flags = physics_result & 4;

    if (hit_flags) {
      if (tag[0x15] != -1 || tag[0xc] != 0) {
        /* Compute speed ratio from velocity magnitude */
        float vz = *(float *)(velocity + 8);
        float vy = *(float *)(velocity + 4);
        float vx = *(float *)velocity;
        float mag;

        mag = sqrtf(vx * vx + vy * vy + vz * vz);

        speed_ratio = (mag - *(float *)0x26ad4c) /
                      (*(float *)0x26ad48 - *(float *)0x26ad4c);
        if (speed_ratio < 0.0f)
          speed_ratio = 0.0f;
        else if (speed_ratio > 1.0f)
          speed_ratio = 1.0f;

        if (tag[0x15] != -1) {
          FUN_000a1770((int)particle, tag[0x12], tag[0x15],
                       *(int *)&speed_ratio);
        }
        if (tag[0xc] != -1 && FUN_0009f3b0(particle + 0x30)) {
          FUN_0009f430(tag[0xc], 8, surface_index, particle + 0x30,
                       collision_normal, particle + 0x28, speed_ratio);
        }
      }

      /* Die on contact */
      if (*(uint8_t *)tag & 0x20) {
        if (tag[0x15] == -1) {
          FUN_000a18c0(datum_handle);
          return 0;
        }
        particle_delete(datum_handle);
        return 0;
      }
    }

    /* Death on ground/water contact */
    if ((physics_result & 1) && (*(uint32_t *)tag & 0x100))
      goto delete_particle;
    if ((physics_result & 2) && (*(int8_t *)tag < 0))
      goto delete_particle;

    /* Collision normal / ground check */
    if (hit_flags || (physics_result & 8)) {
      if (collision_normal[2] > *(float *)0x2533f0)
        stopped = 1;
      *(float *)(particle + 0x20) =
        *(float *)(particle + 0x20) + *(float *)((char *)tag + 0x88);
    }
  } else {
    /* Attached particle — velocity damping */
    if (!(*(uint8_t *)(particle + 2) & 0x40) &&
        object_try_and_get_and_verify_type(*(int *)(particle + 8), -1) ==
          NULL) {
      datum_delete(particle_data, datum_handle);
      return 0;
    }

    velocity = particle + 0x48;
    radius = particle_get_radius(datum_handle);
    drag = radius * *(float *)(physics_tag + 0x24) * radius;
    mass_val = point_physics_definition_get_mass((int)physics_tag, radius);

    if (mass_val == 0.0f) {
      if (drag != 0.0f)
        damping = 1.0f;
      else
        damping = 0.0f;
    } else {
      damping = 1.0f - (drag / mass_val) * delta_time;
      if (damping < 0.0f)
        damping = 0.0f;
      else if (damping > 1.0f)
        damping = 1.0f;
    }

    new_vel_x = damping * *(float *)velocity;
    stopped = 1;
    *(float *)velocity = new_vel_x;
    new_vel_y = damping * *(float *)(velocity + 4);
    *(float *)(velocity + 4) = new_vel_y;
    *(float *)(velocity + 8) = damping * *(float *)(velocity + 8);

    *(float *)(particle + 0x30) += new_vel_x * delta_time;
    *(float *)(particle + 0x34) += new_vel_y * delta_time;
    *(float *)(particle + 0x38) += *(float *)(velocity + 8) * delta_time;
  }

  /* Velocity magnitude check — update heading or mark settled */
  {
    float vz = *(float *)(velocity + 8);
    float vy = *(float *)(velocity + 4);
    float vx = *(float *)velocity;
    float mag_sq = vx * vx + vy * vy + vz * vz;

    if (mag_sq >= *(float *)0x255d90) {
      *(int *)(particle + 0x3c) = *(int *)velocity;
      *(int *)(particle + 0x40) = *(int *)(velocity + 4);
      *(int *)(particle + 0x44) = *(int *)(velocity + 8);
    } else if (stopped) {
      if (*(uint8_t *)tag & 0x10)
        goto delete_particle;
      *(uint8_t *)(particle + 2) |= 2;
    }
  }

  /* Age update */
  *(float *)(particle + 0x54) += delta_time * *(float *)(particle + 0x58);
  return 1;

delete_particle:
  FUN_000a18c0(datum_handle);
  return 0;
}

/* particle_new (0xa1fd0) — XBE naked draft (batch 105). */
#if defined(__clang__)
static int (*const ba1fd0_c84a10)(float *vector) = real_vector3d_valid;
static char * (*const ba1fd0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const ba1fd0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const ba1fd0_exitfn)(int) = system_exit;
static bool (*const ba1fd0_ca16b0)(float *point) = valid_real_point3d;
static bool (*const ba1fd0_ca1710)(float *color) = valid_real_argb_color;
static void *(*const ba1fd0_tag)(int, int) = tag_get;
static void * (*const ba1fd0_cdd410)(int marker_index, int node_index) = first_person_weapon_get_node_matrix;
static void (*const ba1fd0_xfrmpt)(float *, float *, float *) = matrix_transform_point;
static void *(*const ba1fd0_onode)(int, short) = object_get_node_matrix;
static void (*const ba1fd0_c18f180)(void *location_out, void *point) = scenario_location_from_point;
static bool (*const ba1fd0_c18e910)(void *location) = scenario_location_potentially_visible_local;
static int (*const ba1fd0_c119610)(data_t *data) = data_new_at_index;
static void *(*const ba1fd0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static uint16_t (*const ba1fd0_c8e7c0)(void) = FUN_0008e7c0;
static unsigned int *(*const ba1fd0_lseed)(void) = random_math_get_local_seed_address;
static float (*const ba1fd0_rrange)(int *, float, float) = random_real_range;
static __int16 (*const ba1fd0_cba4b0)(void) = local_player_count;
static float (*const ba1fd0_c849f0)(float min, float max) = FUN_000849f0;
static float (*const ba1fd0_ca1670)(int datum_handle) = particle_get_radius;
static float (*const ba1fd0_c1548a0)(int tag_data, float scale) = point_physics_definition_get_mass;
static void (*const ba1fd0_c139480)(void *position, void *tint_color, void *out_color, char use_lightmap) = FUN_00139480;
static bool (*const ba1fd0_c7b020)(float *rgb) = valid_real_rgb_color;
static bool (*const ba1fd0_ca1910)(int datum_handle) = FUN_000a1910;
static void *(*const ba1fd0_elem)(void *, int, int) = tag_block_get_element;
static int16_t (*const ba1fd0_c97c80)(int16_t min, int16_t max) = local_random_range;

__attribute__((naked, noinline))
void particle_new(void *spawn_params __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x38, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "leal 0x28(%%edi), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lparticle_new_1\n\t"
      "flds 0x30(%%edi)\n\t"
      "pushl $1\n\t"
      "pushl $0x6d\n\t"
      "pushl $0x26ad88\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x2c(%%edi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x26ae6c\n\t"
      "pushl $0x26ae40\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lparticle_new_1:\n\t"
      "leal 0x10(%%edi), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[ca16b0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lparticle_new_2\n\t"
      "flds 0x18(%%edi)\n\t"
      "pushl $1\n\t"
      "pushl $0x6e\n\t"
      "pushl $0x26ad88\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x14(%%edi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x26ae30\n\t"
      "pushl $0x26ae04\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lparticle_new_2:\n\t"
      "leal 0x4c(%%edi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[ca1710]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lparticle_new_3\n\t"
      "flds 0x58(%%edi)\n\t"
      "pushl $1\n\t"
      "pushl $0x6f\n\t"
      "pushl $0x26ad88\n\t"
      "subl $0x20, %%esp\n\t"
      "fstpl 0x18(%%esp)\n\t"
      "flds 0x54(%%edi)\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x50(%%edi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%ebx)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x26adf4\n\t"
      "pushl $0x26adc0\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x2c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lparticle_new_3:\n\t"
      "movl (%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lparticle_new_28\n\t"
      "pushl %%eax\n\t"
      "pushl $0x70617274\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lparticle_new_5\n\t"
      "movb 0xc(%%edi), %%cl\n\t"
      "xorl %%edx, %%edx\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lparticle_new_4\n\t"
      "movw 0xa(%%edi), %%dx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x8(%%edi), %%cx\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[cdd410]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[xfrmpt]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Lparticle_new_6\n\t"
      ".Lparticle_new_4:\n\t"
      "movw 0x8(%%edi), %%dx\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[onode]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[xfrmpt]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Lparticle_new_6\n\t"
      ".Lparticle_new_5:\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      ".Lparticle_new_6:\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18f180]\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lparticle_new_28\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c18e910]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lparticle_new_28\n\t"
      "movl 0x5aa8a0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119610]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .Lparticle_new_28\n\t"
      "movl 0x5aa8a0, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movw $0, 0x2(%%esi)\n\t"
      "movb (%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $1, %%cl\n\t"
      "je .Lparticle_new_7\n\t"
      "call *%[c8e7c0]\n\t"
      "andl $1, %%eax\n\t"
      "orw %%ax, 0x2(%%esi)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      ".Lparticle_new_7:\n\t"
      "movl (%%eax), %%ecx\n\t"
      "testb $4, %%ch\n\t"
      "je .Lparticle_new_8\n\t"
      "call *%[c8e7c0]\n\t"
      "andl $4, %%eax\n\t"
      "orw %%ax, 0x2(%%esi)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      ".Lparticle_new_8:\n\t"
      "movl (%%eax), %%ecx\n\t"
      "testb $8, %%ch\n\t"
      "je .Lparticle_new_9\n\t"
      "call *%[c8e7c0]\n\t"
      "andl $8, %%eax\n\t"
      "orw %%ax, 0x2(%%esi)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      ".Lparticle_new_9:\n\t"
      "movb 0xd(%%edi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lparticle_new_10\n\t"
      "orb $0x10, 0x2(%%esi)\n\t"
      "jmp .Lparticle_new_11\n\t"
      ".Lparticle_new_10:\n\t"
      "andb $0xef, 0x2(%%esi)\n\t"
      ".Lparticle_new_11:\n\t"
      "movb 0xe(%%edi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lparticle_new_12\n\t"
      "orb $0x20, 0x2(%%esi)\n\t"
      "jmp .Lparticle_new_13\n\t"
      ".Lparticle_new_12:\n\t"
      "andb $0xdf, 0x2(%%esi)\n\t"
      ".Lparticle_new_13:\n\t"
      "movb 0xc(%%edi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lparticle_new_14\n\t"
      "orb $0x40, 0x2(%%esi)\n\t"
      "jmp .Lparticle_new_15\n\t"
      ".Lparticle_new_14:\n\t"
      "andb $0xbf, 0x2(%%esi)\n\t"
      ".Lparticle_new_15:\n\t"
      "movl (%%edi), %%edx\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "movb 0xa(%%edi), %%cl\n\t"
      "movb %%cl, 0xf(%%esi)\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "movl %%edx, 0x8(%%esi)\n\t"
      "movw 0x8(%%edi), %%cx\n\t"
      "movw %%cx, 0xc(%%esi)\n\t"
      "movb $0, 0xe(%%esi)\n\t"
      "movl 0x506540, %%edx\n\t"
      "movl %%edx, 0x10(%%esi)\n\t"
      "movl 0x3c(%%eax), %%ecx\n\t"
      "movl 0x38(%%eax), %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fcoms 0x2533c4\n\t"
      "addl $0xc, %%esp\n\t"
      "fsts 0x18(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lparticle_new_16\n\t"
      "fsubs 0x2533c4\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "call *%[cba4b0]\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "fdivrs -0x8(%%ebp)\n\t"
      "fadds 0x2533c4\n\t"
      "fstps 0x18(%%esi)\n\t"
      "jmp .Lparticle_new_17\n\t"
      ".Lparticle_new_16:\n\t"
      "fstp %%st(0)\n\t"
      ".Lparticle_new_17:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "flds 0x84(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Lparticle_new_18\n\t"
      "movl 0x84(%%ecx), %%eax\n\t"
      "movl 0x80(%%ecx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c849f0]\n\t"
      "fdivrs 0x2533c8\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Lparticle_new_19\n\t"
      ".Lparticle_new_18:\n\t"
      "flds 0x2548fc\n\t"
      ".Lparticle_new_19:\n\t"
      "fstps 0x20(%%esi)\n\t"
      "movl $0xbf800000, 0x1c(%%esi)\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl %%edx, 0x28(%%esi)\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl %%eax, 0x2c(%%esi)\n\t"
      "movl 0x10(%%edi), %%edx\n\t"
      "leal 0x30(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x14(%%edi), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x18(%%edi), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "leal 0x1c(%%edi), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0x3c(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movl 0x40(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x54(%%esi)\n\t"
      "movl 0x48(%%edi), %%edx\n\t"
      "movl %%edx, 0x5c(%%esi)\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "leal 0x60(%%esi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%ebx), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ebx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl 0xc(%%ebx), %%edx\n\t"
      "movl %%edx, 0xc(%%eax)\n\t"
      "movl 0x28(%%edi), %%ecx\n\t"
      "leal 0x48(%%esi), %%ebx\n\t"
      "movl %%ebx, %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x2c(%%edi), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x30(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "cmpl $-1, 0x8(%%esi)\n\t"
      "jne .Lparticle_new_20\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[ca1670]\n\t"
      "fstps (%%esp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x20(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x70706879\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1548a0]\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x34(%%edi)\n\t"
      "addl $8, %%esp\n\t"
      "fadds (%%ebx)\n\t"
      "fstps (%%ebx)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x38(%%edi)\n\t"
      "fadds 0x4c(%%esi)\n\t"
      "fstps 0x4c(%%esi)\n\t"
      "fmuls 0x3c(%%edi)\n\t"
      "fadds 0x50(%%esi)\n\t"
      "fstps 0x50(%%esi)\n\t"
      ".Lparticle_new_20:\n\t"
      "movl 0x44(%%edi), %%edx\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl %%edx, 0x58(%%esi)\n\t"
      "movl (%%edi), %%eax\n\t"
      "testb $2, %%ah\n\t"
      "je .Lparticle_new_21\n\t"
      "testb $0x40, %%al\n\t"
      "je .Lparticle_new_25\n\t"
      ".Lparticle_new_21:\n\t"
      "pushl $0\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c139480]\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c7b020]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lparticle_new_22\n\t"
      "flds -0x18(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0xcf\n\t"
      "pushl $0x26ad88\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x26adb8\n\t"
      "pushl $0x26488c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lparticle_new_22:\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7b020]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lparticle_new_23\n\t"
      "flds -0x24(%%ebp)\n\t"
      "pushl $1\n\t"
      "pushl $0xd0\n\t"
      "pushl $0x26ad88\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x26adac\n\t"
      "pushl $0x26488c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x24, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lparticle_new_23:\n\t"
      "movl (%%edi), %%eax\n\t"
      "testb $2, %%ah\n\t"
      "jne .Lparticle_new_24\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x64(%%esi)\n\t"
      "fstps 0x64(%%esi)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x68(%%esi)\n\t"
      "fstps 0x68(%%esi)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x6c(%%esi)\n\t"
      "fstps 0x6c(%%esi)\n\t"
      ".Lparticle_new_24:\n\t"
      "testb $0x40, (%%edi)\n\t"
      "je .Lparticle_new_25\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls 0x64(%%esi)\n\t"
      "fstps 0x64(%%esi)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0x68(%%esi)\n\t"
      "fstps 0x68(%%esi)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x6c(%%esi)\n\t"
      "fstps 0x6c(%%esi)\n\t"
      ".Lparticle_new_25:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[ca1910]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lparticle_new_28\n\t"
      "movl 0x10(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6269746d\n\t"
      "call *%[tag]\n\t"
      "movswl 0x24(%%esi), %%ecx\n\t"
      "pushl $0x40\n\t"
      "pushl %%ecx\n\t"
      "addl $0x54, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movb (%%edi), %%cl\n\t"
      "addl $0x14, %%esp\n\t"
      "testb $4, %%cl\n\t"
      "je .Lparticle_new_26\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x34(%%eax), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "call *%[c97c80]\n\t"
      "movb 0x2(%%esi), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "andb $1, %%cl\n\t"
      "negb %%cl\n\t"
      "popl %%edi\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl $2, %%ecx\n\t"
      "decl %%ecx\n\t"
      "addl %%ecx, %%eax\n\t"
      "movw %%ax, 0x26(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lparticle_new_26:\n\t"
      "testb $1, 0x2(%%esi)\n\t"
      "je .Lparticle_new_27\n\t"
      "movw 0x34(%%eax), %%dx\n\t"
      "popl %%edi\n\t"
      "movw %%dx, 0x26(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lparticle_new_27:\n\t"
      "movw $0xffff, 0x26(%%esi)\n\t"
      ".Lparticle_new_28:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c84a10] "m"(ba1fd0_c84a10), [c8d9d0] "m"(ba1fd0_c8d9d0), [assert] "m"(ba1fd0_assert), [exitfn] "m"(ba1fd0_exitfn), [ca16b0] "m"(ba1fd0_ca16b0), [ca1710] "m"(ba1fd0_ca1710), [tag] "m"(ba1fd0_tag), [cdd410] "m"(ba1fd0_cdd410), [xfrmpt] "m"(ba1fd0_xfrmpt), [onode] "m"(ba1fd0_onode), [c18f180] "m"(ba1fd0_c18f180), [c18e910] "m"(ba1fd0_c18e910), [c119610] "m"(ba1fd0_c119610), [dget] "m"(ba1fd0_dget), [c8e7c0] "m"(ba1fd0_c8e7c0), [lseed] "m"(ba1fd0_lseed), [rrange] "m"(ba1fd0_rrange), [cba4b0] "m"(ba1fd0_cba4b0), [c849f0] "m"(ba1fd0_c849f0), [ca1670] "m"(ba1fd0_ca1670), [c1548a0] "m"(ba1fd0_c1548a0), [c139480] "m"(ba1fd0_c139480), [c7b020] "m"(ba1fd0_c7b020), [ca1910] "m"(ba1fd0_ca1910), [elem] "m"(ba1fd0_elem), [c97c80] "m"(ba1fd0_c97c80)
      : "memory");
}
#else
#error "particle_new: clang naked draft required"
#endif


void particles_update(float delta_time)
{
  int datum_handle;
  char *datum;
  char *tag;
  bool just_created;
  float new_lifetime;

  if (profile_global_enable && *(char *)0x2ef1e8)
    profile_enter_private((void *)0x2ef1e0);

  for (datum_handle = data_next_index(particle_data, -1); datum_handle != -1;
       datum_handle = data_next_index(particle_data, datum_handle)) {
    datum = (char *)datum_get(particle_data, datum_handle);
    tag = (char *)tag_get(0x70617274, *(int *)(datum + 4));
    just_created = *(float *)(datum + 0x14) == *(float *)0x2533c0;
    if (render - *(int *)(datum + 0x10) < 0x10) {
      new_lifetime = delta_time + *(float *)(datum + 0x14);
      *(float *)(datum + 0x14) = new_lifetime;
      if (new_lifetime < *(float *)(datum + 0x18) || just_created ||
          *(int16_t *)(tag + 0x9e) != 0) {
        if (FUN_000a1b60(datum_handle, delta_time))
          FUN_000a1c30(datum_handle, delta_time);
      } else {
        FUN_000a18c0(datum_handle);
      }
    } else {
      datum_delete(particle_data, datum_handle);
    }
  }

  if (profile_global_enable && *(char *)0x2ef1e8)
    profile_exit_private((void *)0x2ef1e0);
}
