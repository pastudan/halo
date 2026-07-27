void particle_systems_initialize(void)
{
  particle_system_header_data =
    game_state_data_new("particle systems", 0x40, 0x158);
  particle_system_data =
    game_state_data_new("particle system particles", 0x200, 0x80);
}

void particle_systems_initialize_for_new_map(void)
{
  data_delete_all(particle_system_header_data);
  data_delete_all(particle_system_data);
}

void particle_system_delete(int particle_system_handle)
{
  char *entry, *tag, *particle_entry;
  int particle_index, next_particle;
  int i, instance_count;

  entry =
    (char *)datum_get(particle_system_header_data, particle_system_handle);
  tag = (char *)tag_get(0x7063746c, *(int *)(entry + 8));
  instance_count = *(int *)(tag + 0x5c);
  for (i = 0; i < instance_count; i++) {
    particle_index = *(int *)(entry + 0x94 + i * 0x40);
    while (particle_index != NONE) {
      particle_entry = (char *)datum_get(particle_system_data, particle_index);
      next_particle = *(int *)(particle_entry + 4);
      datum_delete(particle_system_data, particle_index);
      particle_index = next_particle;
    }
  }
  datum_delete(particle_system_header_data, particle_system_handle);
}

void particle_systems_dispose(void)
{
}

/* Advance particle type state to next state index (0x9f920).
 * Computes next_state = current_state + delta, where delta is +1 or -1
 * based on the direction flag at type_state+0x38. If next_state is valid
 * (0 <= next_state < particle_states.count), just stores it. Otherwise:
 * - If type can loop (flag bit 0) and has an object and states exist:
 *   - If ping-pong mode (flag bit 1): bounce off ends, flip direction
 *   - Else: wrap to state 0
 * - Otherwise: terminate by setting both current_state and next_state to -1 */
void FUN_0009f920(void *type_state_arg, void *type_def_arg, void *ps_datum)
{
  char *type_state = (char *)type_state_arg;
  char *type_def = (char *)type_def_arg;
  char direction;
  short delta;
  short current_state;
  short next_state;
  int state_count;
  unsigned int flags;

  direction = *(char *)(type_state + 0x38);
  delta = (direction != 0) ? 1 : -1;
  current_state = *(short *)type_state;
  next_state = current_state + delta;
  *(short *)(type_state + 0x2) = next_state;

  if (next_state >= 0 && (int)next_state < *(int *)(type_def + 0x68)) {
    /* Valid next state */
    return;
  }

  /* Out of bounds - check if we can loop */
  flags = *(unsigned int *)(type_def + 0x20);
  if ((flags & 1) == 0) {
    goto terminate;
  }
  if (*(int *)((char *)ps_datum + 0xc) == -1) {
    goto terminate;
  }
  state_count = *(int *)(type_def + 0x68);
  if (state_count <= 0) {
    goto terminate;
  }

  /* Can loop */
  if ((flags & 2) != 0) {
    /* Ping-pong mode: bounce off ends and flip direction */
    int bounced = (int)current_state - (int)delta;
    if (bounced < 0) {
      *(short *)(type_state + 0x2) = 0;
      *(char *)(type_state + 0x38) = (direction == 0) ? 1 : 0;
      return;
    }
    if (bounced > state_count - 1) {
      bounced = state_count - 1;
    }
    *(short *)(type_state + 0x2) = (short)bounced;
    *(char *)(type_state + 0x38) = (direction == 0) ? 1 : 0;
    return;
  }

  /* Wrap mode: restart at state 0 */
  *(short *)(type_state + 0x2) = 0;
  return;

terminate:
  *(short *)type_state = -1;
  *(short *)(type_state + 0x2) = -1;
}

/* Advance particle state to next state index (0x9f9d0).
 * Similar to FUN_0009f920 but operates on individual particle state rather
 * than type state. Computes next_state = current_state + delta, where delta
 * is +1 or -1 based on the direction flag at particle+0x2. If next_state is
 * valid (0 <= next_state < particle_states.count at sys_def+0x74), stores it.
 * Otherwise:
 * - If type can loop (flag bit 2) and states exist:
 *   - If ping-pong mode (flag bit 3): bounce off ends, flip direction
 *   - Else: wrap to state 0
 * - Otherwise: terminate by setting both current/next_state to -1 */
void FUN_0009f9d0(void *particle_arg, void *sys_def_arg)
{
  char *particle = (char *)particle_arg;
  char *sys_def = (char *)sys_def_arg;
  char direction;
  short delta;
  short current_state;
  short next_state;
  int state_count;
  unsigned int flags;

  direction = *(char *)(particle + 0x2);
  delta = (direction != 0) ? 1 : -1;
  current_state = *(short *)(particle + 0x8);
  next_state = current_state + delta;
  *(short *)(particle + 0xa) = next_state;

  if (next_state >= 0 && (int)next_state < *(int *)(sys_def + 0x74)) {
    /* Valid next state */
    return;
  }

  /* Out of bounds - check if we can loop */
  flags = *(unsigned int *)(sys_def + 0x20);
  if ((flags & 4) == 0) {
    goto terminate;
  }
  state_count = *(int *)(sys_def + 0x74);
  if (state_count <= 0) {
    goto terminate;
  }

  /* Can loop */
  if ((flags & 8) != 0) {
    /* Ping-pong mode: bounce off ends and flip direction */
    int bounced = (int)current_state - (int)delta;
    if (bounced < 0) {
      *(short *)(particle + 0xa) = 0;
      *(char *)(particle + 0x2) = (direction == 0) ? 1 : 0;
      return;
    }
    if (bounced > state_count - 1) {
      bounced = state_count - 1;
    }
    *(short *)(particle + 0xa) = (short)bounced;
    *(char *)(particle + 0x2) = (direction == 0) ? 1 : 0;
    return;
  }

  /* Wrap mode: restart at state 0 */
  *(short *)(particle + 0xa) = 0;
  return;

terminate:
  *(short *)(particle + 0x8) = -1;
  *(short *)(particle + 0xa) = -1;
}

void particle_systems_dispose_from_old_map(void)
{
  int particle_system_index;

  if (particle_system_header_data && particle_system_header_data->valid) {
    for (particle_system_index =
           data_next_index(particle_system_header_data, NONE);
         particle_system_index != NONE;
         particle_system_index = data_next_index(particle_system_header_data,
                                                 particle_system_index)) {
      particle_system_delete(particle_system_index);
    }
    data_make_invalid(particle_system_header_data);
    data_make_invalid(particle_system_data);
  }
}

/* Emit particles for a particle type (0x9fd30).
 * Calculates how many particles to emit based on dt and the type's emission
 * rate, then allocates and initializes each particle. Uses either time-based
 * accumulation or fixed/random count depending on the location-resolved flag.
 * Each particle has its creation physics applied via an indirect call. If the
 * particle fails to resolve a valid location, it's deleted; otherwise it's
 * linked into the type's particle list. */
void FUN_0009fd30(void *ps_arg, int type_index, float dt)
{
  char *ps = (char *)ps_arg;
  char *tag_def;
  char *type_def;
  char *type_state;
  char *state_def;
  char *particle;
  char marker_buf[8 * 0x6c]; /* 8 entries at 0x6c bytes each; original SUB
                                ESP,0x380 */
  float local_position[3];
  float local_up[3];
  int particle_handle;
  int loop_count;
  unsigned int target_count;
  short creation_func_idx;
  int emit_count_int;
  float emit_frac;
  char is_location_resolved;
  short location_valid;
  typedef void (*creation_physics_fn)(char *ps, short type_idx, char *particle,
                                      char *marker_buf);

  tag_def = (char *)tag_get(0x7063746c, *(int *)(ps + 8));
  type_state = ps + 0x58 + type_index * 0x40;
  type_def =
    (char *)tag_block_get_element((void *)(tag_def + 0x5c), type_index, 0x80);
  is_location_resolved = (*(unsigned int *)(ps + 4) >> 1) & 1;

  if (is_location_resolved == 0) {
    /* Time-based emission with fractional accumulator */
    state_def = (char *)tag_block_get_element((void *)(type_def + 0x68),
                                              (int)*(short *)type_state, 0xc0);
    emit_frac = dt * *(float *)(type_state + 0x30);
    emit_count_int = (int)emit_frac;
    target_count =
      (unsigned int)(unsigned short)(*(short *)(type_state + 0x3a) +
                                     (short)emit_count_int);
    emit_frac =
      emit_frac - (float)emit_count_int + *(float *)(type_state + 0x34);
    *(float *)(type_state + 0x34) = emit_frac;
    if (emit_frac > 1.0f) {
      target_count = target_count + 1;
      *(float *)(type_state + 0x34) = emit_frac - 1.0f;
    }
  } else {
    /* Fixed or random emission count */
    state_def = (char *)0;
    if ((*(unsigned int *)(type_def + 0x20) & 0x400) == 0) {
      target_count = (unsigned int)(unsigned short)*(short *)(type_def + 0x24);
    } else {
      emit_count_int = (int)*(short *)(type_def + 0x24);
      emit_frac = (float)emit_count_int * *(float *)(ps + 0x14) + 0.5f;
      target_count = (unsigned int)(int)emit_frac;
    }
  }

  if (*(short *)(type_state + 0x3a) >= (short)target_count) {
    goto check_emission_multiplier;
  }

  /* Set up position and orientation for new particles */
  if (*(int *)(ps + 0xc) == -1) {
    /* No object attachment: use system position and gravity */
    local_position[0] = *(float *)(ps + 0x20);
    local_position[1] = *(float *)(ps + 0x24);
    local_position[2] = *(float *)(ps + 0x28);
    local_up[0] = *(float *)(*(int *)0x31fc38 + 0);
    local_up[1] = *(float *)(*(int *)0x31fc38 + 4);
    local_up[2] = *(float *)(*(int *)0x31fc38 + 8);
    location_valid = 1;
    /* Original MSVC stack layout places local_position at marker_buf+0x60.
       The creation physics function (original binary) reads position from
       marker_buf+0x60. Replicate the overlap explicitly. */
    *(float *)(marker_buf + 0x60) = local_position[0];
    *(float *)(marker_buf + 0x64) = local_position[1];
    *(float *)(marker_buf + 0x68) = local_position[2];
  } else {
    /* Get marker from attached object */
    char *obj = (char *)object_get_and_verify_type(*(int *)(ps + 0xc), -1);
    char *obj_tag = (char *)tag_get(0x6f626a65, *(int *)obj);
    char *marker_elem = (char *)tag_block_get_element(
      (void *)(obj_tag + 0x140), (int)*(short *)(ps + 0x10), 0x6c);
    location_valid = object_get_markers_by_string_id(
      *(int *)(ps + 0xc), (void *)(marker_elem + 0x10), marker_buf, 8);
    object_get_location(*(int *)(ps + 0xc), ps + 0x18);
  }

  if (*(short *)(ps + 0x1c) == -1) {
    goto check_emission_multiplier;
  }

  loop_count = 0;
  while (*(short *)(type_state + 0x3a) < (short)target_count) {
    if (location_valid == 0)
      break;
    if (loop_count >= 0x80)
      break;

    particle_handle = data_new_at_index(particle_system_data);
    if (particle_handle == -1)
      break;

    particle = (char *)datum_get(particle_system_data, particle_handle);
    if (is_location_resolved == 0) {
      creation_func_idx = *(short *)(state_def + 0xb0);
    } else {
      creation_func_idx = *(short *)(type_def + 0x54);
    }

    if (particle == (char *)0) {
      display_assert("particle",
                     "c:\\halo\\SOURCE\\effects\\particle_systems.c", 0x1dc, 1);
      system_exit(-1);
    }

    /* Initialize particle */
    *(char *)(particle + 3) = 1;
    *(short *)(particle + 8) = -1;
    *(short *)(particle + 0xa) = -1;
    *(char *)(particle + 2) = 1;
    *(float *)(particle + 0x44) = -1.0f;
    *(float *)(particle + 0x40) = random_real_range(
      (int *)random_math_get_local_seed_address(), 0.0f, 3.14159265f * 2.0f);

    if (creation_func_idx < 0 || creation_func_idx >= 3) {
      display_assert("creation_function_index>=0 && "
                     "creation_function_index<NUMBER_OF_PARTICLE_SYSTEM_TYPE_"
                     "CREATION_PHYSICS",
                     "c:\\halo\\SOURCE\\effects\\particle_systems.c", 0x1e8, 1);
      system_exit(-1);
    }

    /* Call creation physics via function table */
    {
      random_real_range((int *)random_math_get_local_seed_address(), 0.0f,
                        (float)location_valid);
      ((creation_physics_fn *)(0x26ab10))[creation_func_idx](
        ps, (short)type_index, particle, marker_buf);
    }

    /* Resolve particle location from its position */
    scenario_location_from_point(particle + 0x14, particle + 0x1c);

    if (*(short *)(particle + 0x18) == -1) {
      /* Invalid location: delete particle */
      datum_delete(particle_system_data, particle_handle);
    } else {
      /* Link particle into type's list */
      *(short *)(type_state + 0x3a) = *(short *)(type_state + 0x3a) + 1;
      *(int *)(particle + 4) = *(int *)(type_state + 0x3c);
      *(int *)(type_state + 0x3c) = particle_handle;
    }

    loop_count = loop_count + 1;
  }

check_emission_multiplier:
  /* If particle count < threshold, scale down emission timer */
  if ((float)(int)*(short *)(type_state + 0x3a) <
      *(float *)(type_state + 0x2c)) {
    *(float *)(type_state + 0x4) = *(float *)(type_state + 0x4) * 0.5f;
  }
}

/* Populate particle output from state definition (0xa0080).
 * Reads particle state definition properties and fills in 7 floats in the
 * output array. First generates a random interpolation factor t, then:
 * - output[0] = random_range(state_def+0x48, state_def+0x4c)
 * - output[1] = random_range(state_def+0x50, state_def+0x54)
 * - output[2] = random_range(state_def+0x58, state_def+0x5c)
 * - output[3] = random_range(state_def+0x60, state_def+0x70)
 * - output[4] = lerp(state_def+0x64, state_def+0x74, t)
 * - output[5] = lerp(state_def+0x68, state_def+0x78, t)
 * - output[6] = lerp(state_def+0x6c, state_def+0x7c, t) */
void FUN_000a0080(void *sys_def_arg, short state_index, void *output_arg)
{
  char *sys_def = (char *)sys_def_arg;
  float *output = (float *)output_arg;
  char *state_def;
  float t;

  state_def = (char *)tag_block_get_element((void *)(sys_def + 0x74),
                                            (int)state_index, 0x178);

  /* Generate random interpolation factor */
  t =
    random_real_range((int *)random_math_get_local_seed_address(), 0.0f, 1.0f);

  /* Fill output with random ranges */
  output[1] = random_real_range((int *)random_math_get_local_seed_address(),
                                *(float *)(state_def + 0x50),
                                *(float *)(state_def + 0x54));
  output[2] = random_real_range((int *)random_math_get_local_seed_address(),
                                *(float *)(state_def + 0x58),
                                *(float *)(state_def + 0x5c));
  output[0] = random_real_range((int *)random_math_get_local_seed_address(),
                                *(float *)(state_def + 0x48),
                                *(float *)(state_def + 0x4c));
  output[3] = random_real_range((int *)random_math_get_local_seed_address(),
                                *(float *)(state_def + 0x60),
                                *(float *)(state_def + 0x70));

  /* Fill output with linear interpolations */
  output[4] =
    (*(float *)(state_def + 0x74) - *(float *)(state_def + 0x64)) * t +
    *(float *)(state_def + 0x64);
  output[5] =
    (*(float *)(state_def + 0x78) - *(float *)(state_def + 0x68)) * t +
    *(float *)(state_def + 0x68);
  output[6] =
    (*(float *)(state_def + 0x7c) - *(float *)(state_def + 0x6c)) * t +
    *(float *)(state_def + 0x6c);
}

/* Main per-particle-system update tick (0xa0180).
 * Updates object attachment, runs system physics, then iterates all
 * particle types and their linked particles — handling state transitions,
 * lifetime, interpolation, flag-based multipliers, and particle physics.
 * Dead particles are unlinked and deleted. If no active types remain and
 * the system has no object attachment, deletes the system via
 * particle_system_delete. */
void FUN_000a0180(float dt, int particle_system_handle)
{
  char *ps_datum;
  char *tag_def;
  char *type_def;
  char *type_state;
  char *saved_type_state;
  char *states_block;
  char *state_elem;
  char *particle;
  char *prev_particle;
  char *type_state_def;
  char *tag_block_ptr;
  int particle_handle;
  short next_state;
  short particle_next_state;
  short i;
  short active_types;
  float t, t_inv;
  float duration;

  ps_datum =
    (char *)datum_get(particle_system_header_data, particle_system_handle);
  tag_def = (char *)tag_get(0x7063746c, *(int *)(ps_datum + 8));
  active_types = 0;

  /* Object attachment logic */
  if (*(int *)(ps_datum + 0xc) != -1) {
    char *obj =
      (char *)object_get_and_verify_type(*(int *)(ps_datum + 0xc), -1);
    if ((*(unsigned int *)(obj + 4) & 0x800) != 0 &&
        object_get_function_value(*(int *)(ps_datum + 0xc),
                                  *(short *)(ps_datum + 0x12),
                                  (void *)(ps_datum + 0x14))) {
      *(unsigned int *)(ps_datum + 4) = *(unsigned int *)(ps_datum + 4) | 1;
    } else {
      *(unsigned int *)(ps_datum + 4) = *(unsigned int *)(ps_datum + 4) & ~1u;
    }
    object_get_world_position(*(int *)(ps_datum + 0xc),
                              (vector3_t *)(ps_datum + 0x20));
    object_get_root_location(*(int *)(ps_datum + 0xc),
                             (float *)(ps_datum + 0x2c), (float *)0);
    *(float *)(ps_datum + 0x2c) =
      *(float *)(ps_datum + 0x2c) * TICKS_PER_SECOND;
    *(float *)(ps_datum + 0x30) =
      *(float *)(ps_datum + 0x30) * TICKS_PER_SECOND;
    *(float *)(ps_datum + 0x34) =
      *(float *)(ps_datum + 0x34) * TICKS_PER_SECOND;
  }

  if (*(short *)(tag_def + 0x48) < 0 || *(short *)(tag_def + 0x48) >= 2) {
    display_assert("system_definition->system_update_physics>=0 && "
                   "system_definition->system_update_physics<"
                   "NUMBER_OF_PARTICLE_SYSTEM_UPDATE_PHYSICS",
                   "c:\\halo\\SOURCE\\effects\\particle_systems.c", 0x2e1, 1);
    system_exit(-1);
  }

  /* Indirect call: system physics update */
  {
    typedef void (*system_physics_fn)(char *, float);
    ((system_physics_fn *)(0x26ab08))[*(short *)(tag_def + 0x48)](ps_datum, dt);
  }

  tag_block_ptr = tag_def + 0x5c;
  i = 0;
  if (*(int *)tag_block_ptr < 1)
    goto done;

  /* Outer loop: iterate particle types */
  for (;;) {
    type_def =
      (char *)tag_block_get_element((void *)tag_block_ptr, (int)(short)i, 0x80);
    type_state = ps_datum + 0x58 + (int)(short)i * 0x40;
    saved_type_state = type_state;

    /* Skip disabled types (flag 0x100) */
    if ((*(unsigned int *)(type_def + 0x20) & 0x100) != 0)
      goto next_type;

    /* Decrement type timer */
    *(float *)(type_state + 4) = *(float *)(type_state + 4) - dt;

    /* If current state is NONE, skip */
    if (*(short *)type_state == -1)
      goto next_type;

    states_block = type_def + 0x68;

  state_transition_loop:
    state_elem = (char *)tag_block_get_element((void *)states_block,
                                               (int)*(short *)type_state, 0xc0);
    next_state = *(short *)(type_state + 2);

    /* If timer >= 0.0, do interpolation */
    if (*(float *)(type_state + 4) >= 0.0f)
      goto do_interpolation;

    /* Timer expired: state transition */
    if (next_state == -1) {
      /* No next state: advance via FUN_0009f920 */
      FUN_0009f920(type_state, type_def, ps_datum);
      duration = random_real_range((int *)random_math_get_local_seed_address(),
                                   *(float *)(state_elem + 0x28),
                                   *(float *)(state_elem + 0x2c));
    } else {
      *(short *)type_state = next_state;
      *(short *)(type_state + 2) = -1;
      state_elem = (char *)tag_block_get_element((void *)states_block,
                                                 (int)next_state, 0xc0);
      duration = random_real_range((int *)random_math_get_local_seed_address(),
                                   *(float *)(state_elem + 0x20),
                                   *(float *)(state_elem + 0x24));
    }
    *(float *)(type_state + 8) = duration;
    *(float *)(type_state + 4) = duration + *(float *)(type_state + 4);
    if (*(short *)type_state == -1)
      goto after_interpolation;
    goto state_transition_loop;

  do_interpolation:
    if (next_state == -1) {
      /* Single state: copy properties directly */
      csmemcpy(type_state + 0xc, state_elem + 0x34, 0x28);
    } else {
      char *state_elem2 = (char *)tag_block_get_element((void *)states_block,
                                                        (int)next_state, 0xc0);
      float *src = (float *)(state_elem + 0x34);
      float *src2 = (float *)(state_elem2 + 0x34);
      float *dst = (float *)(type_state + 0xc);
      int k;
      t = *(float *)(type_state + 4) / *(float *)(type_state + 8);
      if (t < 0.0f)
        t = 0.0f;
      else if (t > 1.0f)
        t = 1.0f;
      t_inv = 1.0f - t;
      for (k = 0; k < 10; k++) {
        dst[k] = t * src[k] + t_inv * src2[k];
      }
    }

    /* Flag-based multipliers */
    if ((*(unsigned int *)(type_def + 0x20) & 0x200) != 0) {
      *(float *)(type_state + 0x18) =
        *(float *)(ps_datum + 0x38) * *(float *)(type_state + 0x18);
      *(float *)(type_state + 0x1c) =
        *(float *)(ps_datum + 0x3c) * *(float *)(type_state + 0x1c);
      *(float *)(type_state + 0x20) =
        *(float *)(ps_datum + 0x40) * *(float *)(type_state + 0x20);
      *(float *)(type_state + 0x24) =
        *(float *)(ps_datum + 0x44) * *(float *)(type_state + 0x24);
    }
    if ((*(unsigned int *)(type_def + 0x20) & 0x800) != 0) {
      *(float *)(type_state + 0x2c) =
        *(float *)(ps_datum + 0x14) * *(float *)(type_state + 0x2c);
    }
    if ((*(unsigned int *)(type_def + 0x20) & 0x1000) != 0) {
      *(float *)(type_state + 0x30) =
        *(float *)(ps_datum + 0x14) * *(float *)(type_state + 0x30);
    }
    if ((*(unsigned int *)(type_def + 0x20) & 0x2000) != 0) {
      *(float *)(type_state + 0xc) =
        *(float *)(ps_datum + 0x14) * *(float *)(type_state + 0xc);
    }
    if ((*(unsigned int *)(type_def + 0x20) & 0x4000) != 0) {
      *(float *)(type_state + 0x10) =
        *(float *)(ps_datum + 0x14) * *(float *)(type_state + 0x10);
    }
    if ((*(unsigned int *)(type_def + 0x20) & 0x8000) != 0) {
      *(float *)(type_state + 0x14) =
        *(float *)(ps_datum + 0x14) * *(float *)(type_state + 0x14);
    }

  after_interpolation:
    /* If current state is NONE, no particles to process */
    if (*(short *)type_state == -1)
      goto type_done;

    /* Emit particles if attached (flag bit 0) */
    prev_particle = (char *)0;
    if ((*(unsigned char *)(ps_datum + 4) & 1) != 0) {
      FUN_0009fd30(ps_datum, (int)(short)i, dt);
    }

    /* Inner particle loop: walk linked list at type_state + 0x3c */
    {
      short bx = *(short *)(type_state + 0x3c);
      for (;;) {
        if (bx == -1)
          goto particles_done;
        particle_handle = (int)bx;
        particle = (char *)datum_get(particle_system_data, particle_handle);

        /* Decrement particle lifetime */
        *(float *)(particle + 0xc) = *(float *)(particle + 0xc) - dt;

        /* Particle state init: if state == NONE and type has states */
        if (*(short *)(particle + 8) == -1 && *(int *)(type_def + 0x74) > 0) {
          char *pstate_elem;
          *(short *)(particle + 8) = 0;
          pstate_elem =
            (char *)tag_block_get_element((void *)(type_def + 0x74), 0, 0x178);
          duration = random_real_range(
            (int *)random_math_get_local_seed_address(),
            *(float *)(pstate_elem + 0x20), *(float *)(pstate_elem + 0x24));
          *(float *)(particle + 0xc) = duration;
          *(float *)(particle + 0x10) = duration;
          FUN_000a0080(type_def, *(short *)(particle + 8), particle + 0x48);
        }

        /* If particle direction byte is 0, kill state */
        if (*(char *)(particle + 3) == 0) {
          *(short *)(particle + 8) = -1;
        }

        if (*(short *)(particle + 8) != -1) {
          char *pstates_block = type_def + 0x74;

          /* Particle state transition loop */
          for (;;) {
            char *pstate_elem = (char *)tag_block_get_element(
              (void *)pstates_block, (int)*(short *)(particle + 8), 0x178);

            /* If lifetime >= 0, stop transitioning */
            if (*(float *)(particle + 0xc) >= 0.0f)
              break;

            particle_next_state = *(short *)(particle + 0xa);
            if (particle_next_state == -1) {
              /* End of states: advance particle state */
              FUN_0009f9d0(particle, type_def);
              duration = random_real_range(
                (int *)random_math_get_local_seed_address(),
                *(float *)(pstate_elem + 0x28), *(float *)(pstate_elem + 0x2c));
            } else {
              /* Advance to next particle state */
              *(short *)(particle + 8) = particle_next_state;
              *(short *)(particle + 0xa) = -1;
              pstate_elem = (char *)tag_block_get_element(
                (void *)pstates_block, (int)particle_next_state, 0x178);
              duration = random_real_range(
                (int *)random_math_get_local_seed_address(),
                *(float *)(pstate_elem + 0x20), *(float *)(pstate_elem + 0x24));
            }
            *(float *)(particle + 0x10) = duration;
            *(float *)(particle + 0xc) = duration + *(float *)(particle + 0xc);

            if (*(short *)(particle + 0xa) == -1) {
              int *src_p = (int *)(particle + 0x64);
              int *dst_p = (int *)(particle + 0x48);
              int n;
              for (n = 7; n != 0; n--) {
                *dst_p = *src_p;
                src_p++;
                dst_p++;
              }
            } else {
              /* Regenerate particle output via FUN_000a0080 using next_state */
              FUN_000a0080(type_def, *(short *)(particle + 0xa),
                           particle + 0x64);
            }

            type_state = saved_type_state;

            if (*(short *)(particle + 8) == -1)
              break;
          } /* end particle state transition loop */

          if (*(short *)(particle + 8) != -1) {
            /* Particle is alive: apply physics */
            type_state_def = (char *)tag_block_get_element(
              (void *)states_block, (int)*(short *)type_state, 0xc0);

            if (*(short *)(particle + 0xa) == -1) {
              /* Single state: direct scale */
              *(float *)(particle + 0x40) = *(float *)(particle + 0x50) *
                                              *(float *)(type_state + 0x14) *
                                              dt +
                                            *(float *)(particle + 0x40);
              t = *(float *)(particle + 0x4c);
            } else {
              /* Interpolated state */
              tag_block_get_element((void *)(type_def + 0x74),
                                    (int)*(short *)(particle + 8), 0x178);
              t = *(float *)(particle + 0xc) / *(float *)(particle + 0x10);
              if (t < 0.0f)
                t = 0.0f;
              else if (t > 1.0f)
                t = 1.0f;
              t_inv = 1.0f - t;
              *(float *)(particle + 0x40) =
                (t * *(float *)(particle + 0x50) +
                 t_inv * *(float *)(particle + 0x6c)) *
                  *(float *)(type_state + 0x14) * dt +
                *(float *)(particle + 0x40);
              t = t * *(float *)(particle + 0x4c) +
                  t_inv * *(float *)(particle + 0x68);
            }

            *(float *)(particle + 0x44) =
              t * *(float *)(type_state + 0x10) * dt +
              *(float *)(particle + 0x44);

            if (*(short *)(type_state_def + 0xb2) < 0 ||
                *(short *)(type_state_def + 0xb2) >= 1) {
              display_assert(
                "type_state_definition->particle_update_physics>=0 && "
                "type_state_definition->particle_update_physics<"
                "NUMBER_OF_PARTICLE_SYSTEM_TYPE_UPDATE_PHYSICS",
                "c:\\halo\\SOURCE\\effects\\particle_systems.c", 0x3af, 1);
              system_exit(-1);
            }

            /* Indirect call: particle physics update */
            {
              typedef void (*particle_physics_fn)(char *, int, float, char *);
              ((particle_physics_fn *)(0x26ab1c))[*(
                short *)(type_state_def + 0xb2)](ps_datum, (int)(short)i, dt,
                                                 particle);
            }

            prev_particle = particle;
            bx = *(short *)(particle + 4);
            continue;
          }
        }

        /* Particle is dead: unlink and delete */
        if (prev_particle == (char *)0) {
          *(int *)(type_state + 0x3c) = *(int *)(particle + 4);
        } else {
          *(int *)(prev_particle + 4) = *(int *)(particle + 4);
        }
        datum_delete(particle_system_data, particle_handle);
        bx = *(short *)(particle + 4);
        *(short *)(type_state + 0x3a) = *(short *)(type_state + 0x3a) - 1;
        continue;
      }
    }

  particles_done:
    active_types = active_types + 1;
  type_done:
  next_type:
    i = i + 1;
    if ((int)(short)i >= *(int *)tag_block_ptr)
      break;
  }

done:
  /* Clear bit 1 of flags */
  *(unsigned int *)(ps_datum + 4) = *(unsigned int *)(ps_datum + 4) & ~2u;
  /* If no active types and no object, delete system */
  if (active_types == 0 && *(int *)(ps_datum + 0xc) == -1) {
    particle_system_delete(particle_system_handle);
  }
}

/* Initialize particle system type instances from the pctl tag (0xa0fd0).
 * For each particle type in the tag definition:
 *   - If the type has no particle states, returns false (setup failed).
 *   - Otherwise, initializes the instance state: sets the current state
 *     index to 0, next state to NONE, marks as initialized, clears
 *     particle count and first-particle handle, and picks a random
 *     duration from the first particle state's bounds.
 * Resolves the BSP location from the system's position, sets the
 * "location resolved" flag, then runs an initial 0.001s update tick
 * via FUN_000a0180 if all types were valid. */
char FUN_000a0fd0(int particle_handle)
{
  char *entry;
  char *tag;
  int *tag_block_ptr;
  char *type_def;
  char *state_elem;
  char *instance;
  short i;
  int idx;
  char result;
  float duration;

  entry = (char *)datum_get(particle_system_header_data, particle_handle);
  tag = (char *)tag_get(0x7063746c, *(int *)(entry + 8));
  result = 1;
  scenario_location_from_point(entry + 0x18, entry + 0x20);
  tag_block_ptr = (int *)(tag + 0x5c);
  *(unsigned int *)(entry + 4) |= 2;
  idx = 0;
  i = 0;
  if (*tag_block_ptr < 1) {
    result = 1;
  } else {
    do {
      instance = entry + 0x58 + idx * 0x40;
      type_def = (char *)tag_block_get_element(tag_block_ptr, idx, 0x80);
      if (*(int *)(type_def + 0x68) == 0) {
        result = 0;
      } else {
        *(short *)(instance + 0x00) = 0;
        *(short *)(instance + 0x02) = (short)NONE;
        *(char *)(instance + 0x38) = 1;
        *(short *)(instance + 0x3a) = 0;
        *(int *)(instance + 0x3c) = NONE;
        if (*(int *)(type_def + 0x68) > 0) {
          state_elem =
            (char *)tag_block_get_element((int *)(type_def + 0x68), 0, 0xc0);
          duration = random_real_range(
            (int *)random_math_get_local_seed_address(),
            *(float *)(state_elem + 0x20), *(float *)(state_elem + 0x24));
          *(float *)(instance + 0x04) = duration;
          *(float *)(instance + 0x08) = duration;
        }
      }
      i = i + 1;
      idx = (int)i;
    } while (idx < *tag_block_ptr);
    if (result == 0) {
      return 0;
    }
  }
  FUN_000a0180(0.001f, particle_handle);
  return result;
}

void particle_systems_update(float dt)
{
  int particle_system_index;

  assert_halt(particle_system_header_data &&
              particle_system_header_data->valid);
  for (particle_system_index =
         data_next_index(particle_system_header_data, NONE);
       particle_system_index != NONE;
       particle_system_index =
         data_next_index(particle_system_header_data, particle_system_index)) {
    FUN_000a0180(dt, particle_system_index);
  }
}
/* --- particle_systems.obj batch drafts (2026-07-26) --- */

/* FUN_0009f570 (0x9f570) — XBE naked draft (batch 128). */
#if defined(__clang__)
static void *(*const b9f570_tag)(int, int) = tag_get;
static void *(*const b9f570_elem)(void *, int, int) = tag_block_get_element;
static bool (*const b9f570_ray)(unsigned int, float *, float *, int, short *) = FUN_0014df70;
static bool (*const b9f570_c18f3e0)(void *location, void *position, int16_t *out_sky_index) = FUN_0018f3e0;
static void (*const b9f570_o9f430)(int, short, short, void *, void *, void *, float) = FUN_0009f430;
static void (*const b9f570_c189540)(char flag, void *center, float radius, void *color) = FUN_00189540;

__attribute__((naked, noinline))
void FUN_0009f570(float *src_a __attribute__((unused)), int unused_b __attribute__((unused)), float *dst __attribute__((unused)), float *src_b __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x68, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x666f6f74\n\t"
      "call *%[tag]\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl (%%eax), %%edx\n\t"
      "movswl %%bx, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jge .LFUN_0009f570_4\n\t"
      "pushl %%esi\n\t"
      "pushl $0x1c\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl %%esi, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fadds 0x256140\n\t"
      "movl 0x31fc50, %%eax\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "leal -0x68(%%ebp), %%ecx\n\t"
      "flds (%%eax)\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x2533e4\n\t"
      "pushl $-1\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x2533e4\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "fmuls 0x2533e4\n\t"
      "pushl %%eax\n\t"
      "pushl $0xc2a0\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "call *%[ray]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0009f570_2\n\t"
      "pushl $0\n\t"
      "leal -0x50(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x5c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c18f3e0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl $0x1c, %%eax\n\t"
      "jne .LFUN_0009f570_1\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      ".LFUN_0009f570_1:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x5c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x44(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x50(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[o9f430]\n\t"
      "addl $0x1c, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0009f570_2:\n\t"
      "movb 0x4557e9, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0009f570_3\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3d4ccccd\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "call *%[c189540]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0009f570_3:\n\t"
      "popl %%esi\n\t"
      ".LFUN_0009f570_4:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(b9f570_tag), [elem] "m"(b9f570_elem), [ray] "m"(b9f570_ray), [c18f3e0] "m"(b9f570_c18f3e0), [o9f430] "m"(b9f570_o9f430), [c189540] "m"(b9f570_c189540)
      : "memory");
}
#else
#error "FUN_0009f570: clang naked draft required"
#endif


/* particle_systems_reconnect_to_structure_bsp (0x9f7e0) — XBE naked draft (batch 125). */
#if defined(__clang__)
static int (*const b9f7e0_c1198f0)(data_t *data, int prev_index) = data_next_index;
static void *(*const b9f7e0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b9f7e0_tag)(int, int) = tag_get;
static void (*const b9f7e0_c140130)(int object_handle, void *location_out) = object_get_location;
static void (*const b9f7e0_c18f180)(void *location_out, void *point) = scenario_location_from_point;
static void (*const b9f7e0_c1196d0)(data_t *data, int datum_handle) = datum_delete;
static void (*const b9f7e0_c9f710)(int particle_system_handle) = particle_system_delete;

__attribute__((naked, noinline))
void particle_systems_reconnect_to_structure_bsp(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x5aa8a8, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1198f0]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "je .Lparticle_systems_reconnect_to_structure_bsp_11\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "jmp .Lparticle_systems_reconnect_to_structure_bsp_2\n\t"
      ".Lparticle_systems_reconnect_to_structure_bsp_1:\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lparticle_systems_reconnect_to_structure_bsp_2:\n\t"
      "movl 0x5aa8a8, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x8(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x7063746c\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%ebx), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "je .Lparticle_systems_reconnect_to_structure_bsp_6\n\t"
      "leal 0x18(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c140130]\n\t"
      "addl $8, %%esp\n\t"
      ".Lparticle_systems_reconnect_to_structure_bsp_3:\n\t"
      "movl 0x5c(%%esi), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jle .Lparticle_systems_reconnect_to_structure_bsp_10\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lparticle_systems_reconnect_to_structure_bsp_4:\n\t"
      "shll $6, %%eax\n\t"
      "leal 0x94(%%eax,%%ebx,1), %%edi\n\t"
      "cmpl $-1, (%%edi)\n\t"
      "je .Lparticle_systems_reconnect_to_structure_bsp_9\n\t"
      "nop\n\t"
      ".Lparticle_systems_reconnect_to_structure_bsp_5:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "movl 0x5aa8a4, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "leal 0x1c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x14(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18f180]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $-1, 0x18(%%esi)\n\t"
      "jne .Lparticle_systems_reconnect_to_structure_bsp_7\n\t"
      "movl (%%edi), %%edx\n\t"
      "movl 0x5aa8a4, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1196d0]\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "jmp .Lparticle_systems_reconnect_to_structure_bsp_8\n\t"
      ".Lparticle_systems_reconnect_to_structure_bsp_6:\n\t"
      "leal 0x20(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x18(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c18f180]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $-1, 0x1c(%%ebx)\n\t"
      "jne .Lparticle_systems_reconnect_to_structure_bsp_3\n\t"
      "pushl %%edi\n\t"
      "call *%[c9f710]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .Lparticle_systems_reconnect_to_structure_bsp_10\n\t"
      ".Lparticle_systems_reconnect_to_structure_bsp_7:\n\t"
      "leal 0x4(%%esi), %%edi\n\t"
      ".Lparticle_systems_reconnect_to_structure_bsp_8:\n\t"
      "cmpl $-1, (%%edi)\n\t"
      "jne .Lparticle_systems_reconnect_to_structure_bsp_5\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      ".Lparticle_systems_reconnect_to_structure_bsp_9:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x5c(%%esi), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .Lparticle_systems_reconnect_to_structure_bsp_4\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      ".Lparticle_systems_reconnect_to_structure_bsp_10:\n\t"
      "movl 0x5aa8a8, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c1198f0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .Lparticle_systems_reconnect_to_structure_bsp_1\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".Lparticle_systems_reconnect_to_structure_bsp_11:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1198f0] "m"(b9f7e0_c1198f0), [dget] "m"(b9f7e0_dget), [tag] "m"(b9f7e0_tag), [c140130] "m"(b9f7e0_c140130), [c18f180] "m"(b9f7e0_c18f180), [c1196d0] "m"(b9f7e0_c1196d0), [c9f710] "m"(b9f7e0_c9f710)
      : "memory");
}
#else
#error "particle_systems_reconnect_to_structure_bsp: clang naked draft required"
#endif


/* FUN_0009fa60 (0x9fa60) — readable C lift from XBE leaf. */
void FUN_0009fa60(void *particle, void *arg)
{
  char *p;
  char *pctl;
  int physics_tag;
  void *phyd;
  float delta_time;
  union { void *p; float f; } u;

  p = (char *)particle;
  u.p = arg;
  delta_time = u.f;
  pctl = (char *)tag_get(0x7063746c, *(int *)(p + 8));
  if (*(int *)(p + 0xc) != -1)
    return;
  physics_tag = *(int *)(pctl + 0x44);
  if (physics_tag == -1)
    return;
  phyd = tag_get(0x70706879, physics_tag);
  FUN_00154a50(0, (int)phyd, (int *)(p + 0x18), -1, (float *)(p + 0x20),
               (float *)(p + 0x2c), 0, 0, 0, *(float *)0x2533c8, delta_time);
}

/* FUN_0009fad0 (0x9fad0) — readable C lift: copy particle velocity/position fields. */
void FUN_0009fad0(float *src_a, int unused_b, float *dst, float *src_b)
{
  float *from;
  float *to;

  (void)unused_b;
  from = src_b + 24; /* +0x60 bytes */
  to = dst + 7;      /* +0x1c bytes */
  to[0] = from[0];
  to[1] = from[1];
  to[2] = from[2];
  from = src_a + 11; /* +0x2c */
  to = dst + 10;     /* +0x28 */
  to[0] = from[0];
  to[1] = from[1];
  to[2] = from[2];
}

/* FUN_0009fb10 (0x9fb10) — XBE naked draft (batch 121). */
#if defined(__clang__)
static void *(*const b9fb10_tag)(int, int) = tag_get;
static void *(*const b9fb10_elem)(void *, int, int) = tag_block_get_element;
static void (*const b9fb10_c1548c0)(float *definition_a, float *definition_b, float t, float *definition_out) = point_physics_definition_interpolate;
static int (*const b9fb10_c154a50)(int flags, int physics_tag_data, int *collision_location, int object_handle, float *position, float *velocity, float *force, float *collision_normal_out, int16_t *surface_index_out, float radius, float delta_time) = FUN_00154a50;

__attribute__((naked, noinline))
void FUN_0009fb10(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x40, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl 0x8(%%ebx), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x7063746c\n\t"
      "call *%[tag]\n\t"
      "movswl 0xc(%%ebp), %%esi\n\t"
      "pushl $0x80\n\t"
      "addl $0x5c, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "shll $6, %%esi\n\t"
      "leal 0x58(%%esi,%%ebx,1), %%ecx\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "movswl 0x8(%%esi), %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $0x178\n\t"
      "leal 0x74(%%edi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movw 0xa(%%esi), %%ax\n\t"
      "addl $0x20, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .LFUN_0009fb10_1\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "flds 0x80(%%ebx)\n\t"
      "fmuls 0x28(%%eax)\n\t"
      "movl 0x90(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x70706879\n\t"
      "fmuls 0x2c(%%edi)\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_0009fb10_4\n\t"
      ".LFUN_0009fb10_1:\n\t"
      "movswl %%ax, %%edx\n\t"
      "pushl $0x178\n\t"
      "pushl %%edx\n\t"
      "leal 0x74(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0xc(%%esi)\n\t"
      "addl $0xc, %%esp\n\t"
      "fdivs 0x10(%%esi)\n\t"
      "fsts 0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0009fb10_2\n\t"
      "movl $0, 0xc(%%ebp)\n\t"
      "jmp .LFUN_0009fb10_3\n\t"
      ".LFUN_0009fb10_2:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0009fb10_3\n\t"
      "movl $0x3f800000, 0xc(%%ebp)\n\t"
      ".LFUN_0009fb10_3:\n\t"
      "flds 0x2533c8\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "fsubs 0xc(%%ebp)\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "flds 0xc(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "fmuls 0x80(%%ebx)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x80(%%ecx)\n\t"
      "movl 0x90(%%ecx), %%ecx\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls 0x28(%%eax)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fmuls 0x2c(%%edi)\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x70706879\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "movl 0x90(%%ebx), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl $0x70706879\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1548c0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0009fb10_4:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal 0x28(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x1c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $-1\n\t"
      "leal 0x14(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c154a50]\n\t"
      "addl $0x2c, %%esp\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_0009fb10_5\n\t"
      "testb $0x20, 0x20(%%edi)\n\t"
      "jne .LFUN_0009fb10_7\n\t"
      ".LFUN_0009fb10_5:\n\t"
      "testb $2, %%al\n\t"
      "je .LFUN_0009fb10_6\n\t"
      "testb $0x10, 0x20(%%edi)\n\t"
      "jne .LFUN_0009fb10_7\n\t"
      ".LFUN_0009fb10_6:\n\t"
      "testb $4, %%al\n\t"
      "je .LFUN_0009fb10_8\n\t"
      "testb $0x40, 0x20(%%edi)\n\t"
      "je .LFUN_0009fb10_8\n\t"
      ".LFUN_0009fb10_7:\n\t"
      "movb $0, 0x3(%%esi)\n\t"
      ".LFUN_0009fb10_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(b9fb10_tag), [elem] "m"(b9fb10_elem), [c1548c0] "m"(b9fb10_c1548c0), [c154a50] "m"(b9fb10_c154a50)
      : "memory");
}
#else
#error "FUN_0009fb10: clang naked draft required"
#endif


/* FUN_0009fca0 (0x9fca0) — readable C lift. */
void FUN_0009fca0(void *system, void *arg)
{
  (void)tag_get(0x7063746c, *(int *)((char *)system + 8));
  FUN_0009fa60(system, arg);
}

/* FUN_000a0800 (0xa0800) — XBE naked draft (batch 234). */
#if defined(__clang__)
static void *(*const ba0800_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const ba0800_tag)(int, int) = tag_get;
static void *(*const ba0800_elem)(void *, int, int) = tag_block_get_element;
static char (*const ba0800_c184de0)(void *location) = render_location_visible;
static void (*const ba0800_xfrmpt)(float *, float *, float *) = matrix_transform_point;
static void (*const ba0800_c109680)(float *matrix, float *in, float *out) = matrix_transform_vector;
static unsigned int *(*const ba0800_lseed)(void) = random_math_get_local_seed_address;
static int16_t (*const ba0800_c10b2d0)(unsigned int *seed, int16_t min, int16_t max) = random_range;
static void (*const ba0800_ftol)(void) = FUN_001d9068;
static void (*const ba0800_c18d2c0)(uint32_t *param_1, int16_t param_2, uint32_t param_3, int param_4, uint32_t param_5) = FUN_0018d2c0;
static void (*const ba0800_c18dcf0)(void *param_1, unsigned int param_2, int param_3, int param_4, void *param_5, void *param_6, float param_7, float param_8, void *param_9, float param_10) = FUN_0018dcf0;
static void (*const ba0800_c18d6e0)(void *data, int16_t mode, int16_t sequence_index, int16_t sprite_index, float *untransformed_origin, float *untransformed_direction, float angle, float scale, float *color, float intensity, uint32_t flags) = FUN_0018d6e0;
static void (*const ba0800_c18d360)(void *sprite_build_data) = FUN_0018d360;

__attribute__((naked, noinline))
void FUN_000a0800(int particle_system_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x118, %%esp\n\t"
      "movl 0x5aa8a8, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x7063746c\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "leal 0x5c(%%eax), %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "xorl %%esi, %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%esi, %%eax\n\t"
      "movl %%esi, -0x30(%%ebp)\n\t"
      "movl %%ebx, -0x68(%%ebp)\n\t"
      "jle .LFUN_000a0800_23\n\t"
      "pushl %%edi\n\t"
      ".LFUN_000a0800_1:\n\t"
      "pushl $0x80\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "shll $6, %%esi\n\t"
      "leal 0x58(%%esi,%%eax,1), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $-1, (%%eax)\n\t"
      "movl %%edi, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "je .LFUN_000a0800_22\n\t"
      "movl 0x20(%%edi), %%ecx\n\t"
      "testb $1, %%ch\n\t"
      "jne .LFUN_000a0800_22\n\t"
      "movw 0x3c(%%eax), %%si\n\t"
      "cmpw $-1, %%si\n\t"
      "je .LFUN_000a0800_22\n\t"
      "jmp .LFUN_000a0800_3\n\t"
      ".LFUN_000a0800_2:\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000a0800_3:\n\t"
      "movl 0x5aa8a4, %%edx\n\t"
      "movswl %%si, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x3(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000a0800_21\n\t"
      "leal 0x14(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c184de0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000a0800_21\n\t"
      "movswl 0x8(%%esi), %%ecx\n\t"
      "pushl $0x178\n\t"
      "pushl %%ecx\n\t"
      "addl $0x74, %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "leal -0x64(%%ebp), %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl %%edx\n\t"
      "leal 0x1c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x5065b4\n\t"
      "movl $0, -0x34(%%ebp)\n\t"
      "call *%[xfrmpt]\n\t"
      "leal -0x74(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x34(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x5065b4\n\t"
      "call *%[c109680]\n\t"
      "movw 0xa(%%esi), %%ax\n\t"
      "addl $0x24, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .LFUN_000a0800_4\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "flds 0x48(%%esi)\n\t"
      "fmuls 0xc(%%eax)\n\t"
      "movl $0, -0x2c(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x54(%%esi)\n\t"
      "fmuls 0x18(%%eax)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds 0x58(%%esi)\n\t"
      "fmuls 0x1c(%%eax)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds 0x5c(%%esi)\n\t"
      "fmuls 0x20(%%eax)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x60(%%esi)\n\t"
      "fmuls 0x24(%%eax)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "jmp .LFUN_000a0800_7\n\t"
      ".LFUN_000a0800_4:\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl $0x178\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edx\n\t"
      "flds 0xc(%%esi)\n\t"
      "addl $0xc, %%esp\n\t"
      "fdivs 0x10(%%esi)\n\t"
      "leal 0xb8(%%edx), %%ecx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_000a0800_5\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jmp .LFUN_000a0800_6\n\t"
      ".LFUN_000a0800_5:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a0800_6\n\t"
      "movl $0x3f800000, -0x4(%%ebp)\n\t"
      ".LFUN_000a0800_6:\n\t"
      "flds 0x2533c8\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fmuls 0x64(%%esi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x48(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls 0xc(%%eax)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x70(%%esi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x54(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls 0x18(%%eax)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x74(%%esi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x58(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls 0x1c(%%eax)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x78(%%esi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x5c(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls 0x20(%%eax)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x7c(%%esi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x60(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls 0x24(%%eax)\n\t"
      "leal 0xb8(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "je .LFUN_000a0800_8\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_000a0800_8\n\t"
      "movw 0x2a(%%eax), %%di\n\t"
      "cmpw 0x2a(%%ecx), %%di\n\t"
      "jne .LFUN_000a0800_8\n\t"
      "movw 0x2e(%%eax), %%ax\n\t"
      "cmpw 0x2e(%%ecx), %%ax\n\t"
      "jne .LFUN_000a0800_8\n\t"
      "movw 0x40(%%ebx), %%cx\n\t"
      "cmpw 0x40(%%edx), %%cx\n\t"
      "jne .LFUN_000a0800_8\n\t"
      ".LFUN_000a0800_7:\n\t"
      "movl $0x3f800000, -0x4(%%ebp)\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      ".LFUN_000a0800_8:\n\t"
      "movl 0x3c(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x6269746d\n\t"
      "call *%[tag]\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $1, 0x28(%%ecx)\n\t"
      "movw 0x40(%%ebx), %%cx\n\t"
      "jne .LFUN_000a0800_9\n\t"
      "incw %%cx\n\t"
      ".LFUN_000a0800_9:\n\t"
      "movswl %%cx, %%edx\n\t"
      "pushl $0x40\n\t"
      "pushl %%edx\n\t"
      "addl $0x54, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x44(%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $0xbf800000, %%eax\n\t"
      "jne .LFUN_000a0800_10\n\t"
      "movswl 0x34(%%edi), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[c10b2d0]\n\t"
      "movswl %%ax, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "fsts 0x44(%%esi)\n\t"
      "call *%[ftol]\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jmp .LFUN_000a0800_11\n\t"
      ".LFUN_000a0800_10:\n\t"
      "flds 0x44(%%esi)\n\t"
      "call *%[ftol]\n\t"
      "movswl %%ax, %%eax\n\t"
      "cdq\n\t"
      "idivl 0x34(%%edi)\n\t"
      "movw %%dx, %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "jge .LFUN_000a0800_11\n\t"
      "addw 0x34(%%edi), %%ax\n\t"
      "movw %%ax, -0xc(%%ebp)\n\t"
      ".LFUN_000a0800_11:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "movl -0x1c(%%ebp), %%edi\n\t"
      "fcomps 0x25bb10\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a0800_16\n\t"
      "cmpw $0, 0xe2(%%ebx)\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x58(%%ebp)\n\t"
      "movl %%edx, -0x54(%%ebp)\n\t"
      "movl %%edi, -0x50(%%ebp)\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "jne .LFUN_000a0800_12\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x48(%%eax)\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fmuls 0x4c(%%eax)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "fmuls 0x50(%%eax)\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      ".LFUN_000a0800_12:\n\t"
      "movl 0x3c(%%ebx), %%ecx\n\t"
      "pushl $0\n\t"
      "leal 0xb8(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x118(%%ebp), %%edx\n\t"
      "pushl $2\n\t"
      "pushl %%edx\n\t"
      "call *%[c18d2c0]\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl $1, %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw %%cx, 0x28(%%eax)\n\t"
      "jne .LFUN_000a0800_14\n\t"
      "movb 0x20(%%eax), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "jns .LFUN_000a0800_13\n\t"
      "movl $3, %%ecx\n\t"
      ".LFUN_000a0800_13:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "leal -0x58(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x40(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "leal -0x74(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "leal -0x64(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x40(%%ebx), %%dx\n\t"
      "pushl %%eax\n\t"
      "leal -0x118(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c18dcf0]\n\t"
      "addl $0x28, %%esp\n\t"
      "jmp .LFUN_000a0800_15\n\t"
      ".LFUN_000a0800_14:\n\t"
      "pushl %%ecx\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movswl 0x2a(%%eax), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "leal -0x58(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x40(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x74(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "leal -0x64(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x40(%%ebx), %%dx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x118(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18d6e0]\n\t"
      "addl $0x2c, %%esp\n\t"
      ".LFUN_000a0800_15:\n\t"
      "movl 0x80(%%ebx), %%edx\n\t"
      "movl -0x110(%%ebp), %%eax\n\t"
      "leal -0x118(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, 0x98(%%eax)\n\t"
      "call *%[c18d360]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000a0800_16:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x25bb10\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_000a0800_21\n\t"
      "cmpw $0, 0xe2(%%ebx)\n\t"
      "movl -0x24(%%ebp), %%edx\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x48(%%ebp)\n\t"
      "movl %%eax, -0x44(%%ebp)\n\t"
      "movl %%edi, -0x40(%%ebp)\n\t"
      "movl %%ecx, -0x3c(%%ebp)\n\t"
      "jne .LFUN_000a0800_17\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x48(%%eax)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls 0x4c(%%eax)\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls 0x50(%%eax)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      ".LFUN_000a0800_17:\n\t"
      "movl -0x34(%%ebp), %%edx\n\t"
      "movl -0x2c(%%ebp), %%edi\n\t"
      "movl 0x3c(%%edi), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x118(%%ebp), %%ecx\n\t"
      "pushl $2\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18d2c0]\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "fadds 0x255ef8\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl $1, %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw %%cx, 0x28(%%eax)\n\t"
      "fstps -0x5c(%%ebp)\n\t"
      "jne .LFUN_000a0800_19\n\t"
      "movb 0x20(%%eax), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "jns .LFUN_000a0800_18\n\t"
      "movl $3, %%ecx\n\t"
      ".LFUN_000a0800_18:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "leal -0x48(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x40(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x74(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "leal -0x64(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x40(%%edi), %%ax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x118(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18dcf0]\n\t"
      "addl $0x28, %%esp\n\t"
      "jmp .LFUN_000a0800_20\n\t"
      ".LFUN_000a0800_19:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "leal -0x48(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x40(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x74(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "leal -0x64(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x40(%%edi), %%cx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2a(%%eax), %%dx\n\t"
      "leal -0x118(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c18d6e0]\n\t"
      "addl $0x2c, %%esp\n\t"
      ".LFUN_000a0800_20:\n\t"
      "movl 0x80(%%ebx), %%ecx\n\t"
      "movl -0x110(%%ebp), %%edx\n\t"
      "leal -0x118(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, 0x98(%%edx)\n\t"
      "call *%[c18d360]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000a0800_21:\n\t"
      "movw 0x4(%%esi), %%si\n\t"
      "cmpw $-1, %%si\n\t"
      "jne .LFUN_000a0800_2\n\t"
      "movl -0x68(%%ebp), %%ebx\n\t"
      ".LFUN_000a0800_22:\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "movswl %%ax, %%esi\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "cmpl (%%ebx), %%esi\n\t"
      "jl .LFUN_000a0800_1\n\t"
      "popl %%edi\n\t"
      ".LFUN_000a0800_23:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(ba0800_dget), [tag] "m"(ba0800_tag), [elem] "m"(ba0800_elem), [c184de0] "m"(ba0800_c184de0), [xfrmpt] "m"(ba0800_xfrmpt), [c109680] "m"(ba0800_c109680), [lseed] "m"(ba0800_lseed), [c10b2d0] "m"(ba0800_c10b2d0), [ftol] "m"(ba0800_ftol), [c18d2c0] "m"(ba0800_c18d2c0), [c18dcf0] "m"(ba0800_c18dcf0), [c18d6e0] "m"(ba0800_c18d6e0), [c18d360] "m"(ba0800_c18d360)
      : "memory");
}
#else
#error "FUN_000a0800: clang naked draft required"
#endif



/* FUN_000a0d50 (0xa0d50) — XBE naked draft (batch 128). */
#if defined(__clang__)
static void *(*const ba0d50_tag)(int, int) = tag_get;
static void *(*const ba0d50_elem)(void *, int, int) = tag_block_get_element;
static unsigned int *(*const ba0d50_lseed)(void) = random_math_get_local_seed_address;
static void (*const ba0d50_c10b380)(unsigned int *seed, float *out) = random_seed_get_direction3d;
static void (*const ba0d50_rots)(float *, float *, float, float) = rotate_vector3d_by_sincos;

__attribute__((naked, noinline))
void FUN_000a0d50(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl 0x8(%%ebx), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x7063746c\n\t"
      "call *%[tag]\n\t"
      "movswl 0xc(%%ebp), %%ecx\n\t"
      "pushl $0x80\n\t"
      "pushl %%ecx\n\t"
      "addl $0x5c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "pushl $4\n\t"
      "leal 0x5c(%%eax), %%esi\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "movl (%%eax), %%edx\n\t"
      "pushl $4\n\t"
      "pushl $1\n\t"
      "pushl %%esi\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl $4\n\t"
      "pushl $2\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl (%%eax), %%ecx\n\t"
      "addl $0x38, %%esp\n\t"
      "leal 0x28(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[c10b380]\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "addl $8, %%esp\n\t"
      "fsts (%%edi)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fmuls 0x2c(%%esi)\n\t"
      "fsts 0x2c(%%esi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x30(%%esi)\n\t"
      "fsts 0x30(%%esi)\n\t"
      "movb 0x54(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000a0d50_1\n\t"
      "fabs\n\t"
      "fstps 0x30(%%esi)\n\t"
      "jmp .LFUN_000a0d50_2\n\t"
      ".LFUN_000a0d50_1:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_000a0d50_2:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "fld %%st(1)\n\t"
      "fadds 0x60(%%eax)\n\t"
      "pushl $0\n\t"
      "pushl $0x3f800000\n\t"
      "fstps 0x1c(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fadds 0x64(%%eax)\n\t"
      "fstps 0x20(%%esi)\n\t"
      "flds 0x68(%%eax)\n\t"
      "leal 0x34(%%esi), %%eax\n\t"
      "fadds 0x30(%%esi)\n\t"
      "movl $0, 0x3c(%%esi)\n\t"
      "fstps 0x24(%%esi)\n\t"
      "fld %%st(1)\n\t"
      "fstps (%%eax)\n\t"
      "fsts 0x38(%%esi)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fadds 0x2c(%%ebx)\n\t"
      "fstps (%%edi)\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fadds 0x30(%%ebx)\n\t"
      "fstps 0x2c(%%esi)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x30(%%esi)\n\t"
      "fadds 0x34(%%ebx)\n\t"
      "fstps 0x30(%%esi)\n\t"
      "movl 0x31fc44, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[rots]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(ba0d50_tag), [elem] "m"(ba0d50_elem), [lseed] "m"(ba0d50_lseed), [c10b380] "m"(ba0d50_c10b380), [rots] "m"(ba0d50_rots)
      : "memory");
}
#else
#error "FUN_000a0d50: clang naked draft required"
#endif


/* FUN_000a0e60 (0xa0e60) — XBE naked draft (batch 121). */
#if defined(__clang__)
static void *(*const ba0e60_tag)(int, int) = tag_get;
static void *(*const ba0e60_elem)(void *, int, int) = tag_block_get_element;
static unsigned int *(*const ba0e60_lseed)(void) = random_math_get_local_seed_address;
static void (*const ba0e60_c10b380)(unsigned int *seed, float *out) = random_seed_get_direction3d;

__attribute__((naked, noinline))
void FUN_000a0e60(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x7063746c\n\t"
      "call *%[tag]\n\t"
      "movswl 0xc(%%ebp), %%ecx\n\t"
      "pushl $0x80\n\t"
      "pushl %%ecx\n\t"
      "addl $0x5c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "pushl $4\n\t"
      "leal 0x5c(%%eax), %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "movl (%%eax), %%edx\n\t"
      "pushl $4\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl $4\n\t"
      "pushl $2\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "flds 0x26ab24\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "flds 0xc(%%ebp)\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "addl $0x38, %%esp\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "pushl %%edx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0xc(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[c10b380]\n\t"
      "flds 0xc(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "fmuls 0x3c(%%edx)\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "flds -0x10(%%ebp)\n\t"
      "leal 0x60(%%edx), %%eax\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds 0x2c(%%esi)\n\t"
      "fstps 0x28(%%ecx)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x40(%%edx)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds 0x30(%%esi)\n\t"
      "fstps 0x2c(%%ecx)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x44(%%edx)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds 0x34(%%esi)\n\t"
      "leal 0x1c(%%ecx), %%esi\n\t"
      "fstps 0x30(%%ecx)\n\t"
      "movl (%%eax), %%edi\n\t"
      "movl %%edi, (%%esi)\n\t"
      "movl 0x4(%%eax), %%edi\n\t"
      "movl %%edi, 0x4(%%esi)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "popl %%edi\n\t"
      "fcomps 0x2533c0\n\t"
      "popl %%esi\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_000a0e60_1\n\t"
      "movl 0x31fc44, %%eax\n\t"
      "flds 0x28(%%ecx)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "flds 0x2c(%%ecx)\n\t"
      "fmuls (%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x30(%%ecx)\n\t"
      "fmuls (%%eax)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x28(%%ecx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x2c(%%ecx)\n\t"
      "flds 0x30(%%ecx)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x34(%%ecx)\n\t"
      "fstps 0x38(%%ecx)\n\t"
      "fstps 0x3c(%%ecx)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000a0e60_1:\n\t"
      "flds 0x2c(%%ecx)\n\t"
      "fmuls 0x3c(%%edx)\n\t"
      "flds 0x28(%%ecx)\n\t"
      "fmuls 0x40(%%edx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x44(%%edx)\n\t"
      "fmuls 0x28(%%ecx)\n\t"
      "flds 0x30(%%ecx)\n\t"
      "fmuls 0x3c(%%edx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x30(%%ecx)\n\t"
      "fmuls 0x40(%%edx)\n\t"
      "flds 0x44(%%edx)\n\t"
      "fmuls 0x2c(%%ecx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x34(%%ecx)\n\t"
      "fstps 0x38(%%ecx)\n\t"
      "fstps 0x3c(%%ecx)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(ba0e60_tag), [elem] "m"(ba0e60_elem), [lseed] "m"(ba0e60_lseed), [c10b380] "m"(ba0e60_c10b380)
      : "memory");
}
#else
#error "FUN_000a0e60: clang naked draft required"
#endif


/* particle_system_update (0xa1170) — readable C lift. */
void particle_system_update(void)
{
  extern char DAT_0032574c[];
  extern char DAT_0026abcc[];
  extern char DAT_0026ad14[];
  void *header;
  int idx;
  char *ps;
  void (__attribute__((regparm(1))) *update_one)(int) =
      (void (__attribute__((regparm(1))) *)(int))FUN_000a0800;

  if (!*(unsigned char *)DAT_0032574c)
    return;
  header = *(void **)0x5aa8a8;
  if (header == 0 || !*((unsigned char *)header + 0x24)) {
    display_assert(DAT_0026ad14, DAT_0026abcc, 0x3d0, 1);
    system_exit(-1);
    header = *(void **)0x5aa8a8;
  }
  idx = data_next_index((data_t *)header, -1);
  while (idx != -1) {
    ps = (char *)datum_get(*(data_t **)0x5aa8a8, idx);
    if (*(short *)(ps + 0x1c) != (short)0xffff) {
      if (scenario_location_potentially_visible_local(ps + 0x18))
        update_one(idx);
    }
    idx = data_next_index(*(data_t **)0x5aa8a8, idx);
  }
}
