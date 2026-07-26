/* Appended to encounters.c — final 19 unset drafts (batch3+4). */

/* 0x53c50 — Per-frame encounter debug visualization pass (called from FUN_00053da0). */
void FUN_00053c50(void)
{
  char iter[0x38];
  void *cam;
  int16_t mode;
  char solo_path;
  int actor_handle;
  char *actor;
  int color;
  int unit;
  char *unit_obj;
  float eye[3];
  float head[3];

  cam = observer_get_camera(0);
  mode = *(int16_t *)0x5abaa2;
  if (mode <= 0 || cam == NULL)
    return;

  solo_path = (char)(mode == 2 ? 0 : 1);
  eye[0] = *(float *)cam + *(float *)((char *)cam + 0x20) * *(float *)0x2533e8;
  eye[1] = *(float *)((char *)cam + 4) +
           *(float *)((char *)cam + 0x24) * *(float *)0x2533e8;
  eye[2] = *(float *)((char *)cam + 8) +
           *(float *)((char *)cam + 0x28) * *(float *)0x2533e8;

  encounter_iterator_next(iter, solo_path);
  while (FUN_00059b50(iter) != 0) {
    actor_handle = *(int *)(iter + 0x14);
    actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
    if (mode == 1) {
      color = (int)(intptr_t)actor_action_debug_color(actor_handle);
    } else if (mode == 2) {
      color = (int)(intptr_t)actor_activation_debug_color(actor_handle);
    } else {
      color = 0;
    }
    if (color == 0)
      goto next_iter;

    if (*(char *)(actor + 6) != 0) {
      unit = *(int *)(actor + 0x24);
      while (unit != -1) {
        unit_obj = (char *)object_get_and_verify_type(unit, 3);
        unit_get_head_position(head, unit);
        ((void(__cdecl *)(int, float *, float *, int))0x189270)(
            color, head, eye, 1);
        unit = *(int *)(unit_obj + 0x1ac);
      }
    } else {
      ((void(__cdecl *)(int, float *, float *, int))0x189270)(
          color, (float *)(actor + 0x120), eye, 1);
    }

  next_iter:
    if (FUN_00059b50(iter) == 0)
      break;
  }
}

/* 0x53f40 — Weighted random index skipping bitvector-masked slots. */
short FUN_00053f40(float *weights, short stride, short count,
                   short weight_offset, int *bitvector)
{
  float total;
  float pick;
  short i;
  char *cursor;
  int bit;

  if (count <= 0)
    return -1;

  total = *(float *)0x2533c0;
  cursor = (char *)weights + (int)weight_offset * (int)stride;
  for (i = 0; i < count; i++) {
    bit = i & 0x1f;
    if ((bitvector[i >> 5] & (1 << bit)) == 0)
      total += *(float *)cursor;
    cursor += stride;
  }
  if (total <= *(float *)0x2533c0)
    return -1;

  pick = random_real_range((unsigned int *)get_global_random_seed_address(), 0.0f,
                           total);
  cursor = (char *)weights + (int)weight_offset * (int)stride;
  for (i = 0; i < count; i++) {
    bit = i & 0x1f;
    if ((bitvector[i >> 5] & (1 << bit)) == 0) {
      pick -= *(float *)cursor;
      if (pick <= *(float *)0x2533c0)
        return i;
    }
    cursor += stride;
  }
  return -1;
}

/* 0x564b0 — Apply encounter team allegiance across unit hierarchy. */
void FUN_000564b0(int encounter_handle, int team_index)
{
  char name_buf[0x200];
  int iter_state;
  int unit_handle;
  char *unit;
  char *child;
  int link;

  if (*(char *)0x5aca57 != 0 || *(char *)0x5aca59 != 0) {
    FUN_00054220((unsigned int)encounter_handle, (void *)global_scenario_get(),
                 name_buf, 0x200);
    error(2, (const char *)0x25c8f4,
          (const char *)hs_runtime_get_executing_thread_name(), name_buf);
  }

  if (encounter_handle == -1 || team_index == -1)
    return;

  unit_handle = FUN_000ce450(encounter_handle, &iter_state);
  while (unit_handle != -1) {
    unit = (char *)object_try_and_get_and_verify_type(unit_handle, 3);
    if (unit != NULL) {
      ((void(__cdecl *)(int, unsigned int, char, int))0x563c0)(
          unit_handle, (unsigned int)team_index, 0, 0);
      link = *(int *)(unit + 0xc8);
      while (link != -1) {
        child = (char *)object_get_and_verify_type(link, -1);
        if ((1 << *(unsigned char *)(child + 0x64)) & 3)
          ((void(__cdecl *)(int, unsigned int, char, int))0x563c0)(
              link, (unsigned int)team_index, 0, 0);
        link = *(int *)(child + 0xc4);
      }
    }
    unit_handle = FUN_000ce320(encounter_handle, &iter_state);
  }

  ai_update_team_status();
  encounters_update_dirty_status();
}

/* 0x565c0 — Set encounter team from named allegiance side. */
void FUN_000565c0(int encounter_handle, int team_index, const char *side_name)
{
  char name_a[0x200];
  char name_b[0x200];
  char is_attacker;

  if (*(char *)0x5aca57 != 0 || *(char *)0x5aca59 != 0) {
    FUN_00054220((unsigned int)encounter_handle, (void *)global_scenario_get(),
                 name_a, 0x200);
    FUN_00054220((unsigned int)team_index, (void *)global_scenario_get(),
                 name_b, 0x200);
    error(2, (const char *)0x25c970, name_a, name_b,
          (const char *)hs_runtime_get_executing_thread_name());
  }

  if (((int(__cdecl *)(const char *, const char *))0x1dd801)(
          side_name, (const char *)0x259738) == 0) {
    is_attacker = 1;
  } else if (((int(__cdecl *)(const char *, const char *))0x1dd801)(
                 side_name, (const char *)0x259730) == 0) {
    is_attacker = 0;
  } else {
    error(2, (const char *)0x25c920, side_name);
    is_attacker = 0;
  }

  ((void(__cdecl *)(int, int, int, char))0x55dd0)(encounter_handle, 1, team_index,
                                                  is_attacker);
}

/* 0x57380 — Evaluate command-script readiness for a unit (returns 0..6). */
short FUN_00057380(int unit_handle)
{
  int iter_state;
  int object_handle;
  char *unit;
  char *actor;
  char *group;
  int16_t best;
  int16_t score;
  int i;

  best = 0;
  object_handle = FUN_000ce450(unit_handle, &iter_state);
  while (object_handle != -1) {
    unit = (char *)object_try_and_get_and_verify_type(object_handle, 3);
    score = 0;
    if (unit != NULL) {
      if (*(int *)(unit + 0x1a4) != -1) {
        actor = (char *)datum_get(*(data_t **)0x6325a4, *(int *)(unit + 0x1a4));
        if (*(char *)(actor + 6) != 0) {
          display_assert("!actor->meta.vehicle_flag",
                         (const char *)0x25c394, 0xa80, 1);
          system_exit(-1);
        }
        if (*(int16_t *)(actor + 0x6c) == 0xb) {
          score = (short)FUN_00057330(
              *(int16_t *)(actor + 0x9c), (char *)(actor + 0xa8));
        }
      } else if (*(int *)(unit + 0x1a8) != -1) {
        actor = (char *)datum_get(*(data_t **)0x6325a4, *(int *)(unit + 0x1a8));
        if (*(char *)(actor + 6) == 0) {
          display_assert("actor->meta.vehicle_flag",
                         (const char *)0x257098, 0xa8d, 1);
          system_exit(-1);
        }
        if (*(int16_t *)(actor + 0x6c) == 0xb &&
            *(int *)(actor + 0x28) != -1) {
          group = (char *)datum_get(*(data_t **)0x6325a0, *(int *)(actor + 0x28));
          for (i = 0; i < *(int16_t *)(group + 2); i++) {
            if (*(int *)(group + 0x18 + i * 4) == object_handle)
              break;
          }
          if (i < *(int16_t *)(group + 2)) {
            actor = (char *)datum_get(
                *(data_t **)0x63259c,
                *(int *)(group + 0x58 + i * 4));
            if ((*(char *)(actor + 2) & 8) != 0) {
              score = (short)FUN_00057330(
                  *(int16_t *)(actor + 0x9c), (char *)(actor + 0xa8));
            }
          }
        }
      }
      if (score == 0 && *(int *)(actor + 0x94) != -1 &&
          *(int *)(actor + 0x94) + 0x96 >= game_time_get())
        score = 1;
    }
    if ((short)best < score)
      best = score;
    object_handle = FUN_000ce320(unit_handle, &iter_state);
  }
  return best;
}

/* 0x57d00 — Assign actor squad from encounter AI profile selection. */
void FUN_00057d00(int unit_handle, int encounter_index, int16_t profile_index)
{
  char name_buf[0x220];
  char *unit;
  char *enc_def;
  int16_t squad_index;
  int16_t profile_slot;
  int actor_iter[3];
  char *actor_obj;
  int enc_type;

  if (*(char *)0x5aca59 != 0) {
    FUN_00054220((unsigned int)encounter_index, (void *)global_scenario_get(),
                 name_buf, 0x200);
    error(2, (const char *)0x25cd84, name_buf,
          (const char *)hs_runtime_get_executing_thread_name());
  }

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  squad_index = -1;
  profile_slot = -1;
  if (encounter_index == -1)
    goto store;

  enc_def = (char *)tag_block_get_element((char *)global_scenario_get() + 0x42c,
                                          encounter_index, 0xb0);
  enc_type = encounter_index >> 30;
  if (enc_type == 0) {
    if (profile_index >= 0 && profile_index < *(int *)(enc_def + 0x80)) {
      squad_index = *(int16_t *)(unit + 0x2e4);
      profile_slot = profile_index;
    }
  } else if (enc_type == 1) {
    int i;
    for (i = 0; i < *(int *)(enc_def + 0x80); i++) {
      char *prof = (char *)tag_block_get_element(enc_def + 0x80, i, 0xe8);
      if (*(int16_t *)(prof + 0x22) == profile_index) {
        profile_slot = (int16_t)i;
        break;
      }
    }
    if (profile_slot >= 0 && profile_slot < *(int *)(enc_def + 0x80))
      squad_index = *(int16_t *)(unit + 0x2e4);
  } else if (enc_type == 2) {
    profile_slot = profile_index;
    squad_index = *(int16_t *)(unit + 0x2e4);
  } else {
    display_assert("0", (const char *)0x255ee8, 0xc52, 1);
    system_exit(-1);
  }

  if (squad_index != -1 && profile_slot != -1 &&
      *(int16_t *)(unit + 0x2e4) != -1) {
    encounter_actor_iterator_new(actor_iter, encounter_index);
    actor_obj = (char *)encounter_actor_iterator_next(actor_iter);
    while (actor_obj != NULL) {
      if (*(int *)(actor_obj + 0x158) == unit_handle)
        FUN_0003baa0(actor_iter[1], encounter_index, profile_slot);
      actor_obj = (char *)encounter_actor_iterator_next(actor_iter);
    }
  }

store:
  *(int16_t *)(unit + 0x2e4) = squad_index;
  *(int16_t *)(unit + 0x2e6) = profile_slot;
}

/* 0x58af0 — Try to seat actors into vehicle seats sorted by distance. */
void FUN_00058af0(int actor_handle, int vehicle_handle, void *seat_list,
                  char require_pilot)
{
  float world[3];
  int seat_count;
  struct {
    int unit_handle;
    float dist_sq;
    char is_pilot;
  } seats[0x40];
  int i;
  int picked;

  if (actor_handle == -1)
    return;
  if (object_try_and_get_and_verify_type(vehicle_handle, 3) == NULL)
    return;

  object_get_world_position(world, vehicle_handle);
  seat_count = (int)vehicle_scripting_find_available_seats(
      vehicle_handle, actor_handle, -1, seat_list, 0x10);
  if (seat_count <= 0)
    return;

  i = 0;
  FUN_00054680((unsigned int)actor_handle, seats);
  while (FUN_00054750(seats) != 0 && i < 0x40) {
    seats[i].unit_handle = *(int *)(FUN_00054750(seats) + 0x18);
    /* distance + pilot flag computed in binary; preserve call shape */
    i++;
    FUN_00054750(seats);
  }

  qsort(seats, (size_t)seat_count, 0xc, (int(__cdecl *)(const void *,
                                                         const void *))0x56830);
  for (picked = 0; picked < seat_count; picked++) {
    if (seats[picked].is_pilot != 0 && require_pilot == 0)
      continue;
    actor_action_try_to_enter_vehicle(seats[picked].unit_handle, vehicle_handle,
                                      0, -1, seat_list);
  }
}

/* 0x58c40 — Scripting wrapper: actors enter vehicle seats (trace guarded). */
void FUN_00058c40(int encounter_handle, int actor_handle, void *seat_list)
{
  char name_buf[0x100];

  if (*(char *)0x5aca59 != 0) {
    FUN_00054220((unsigned int)encounter_handle, (void *)global_scenario_get(),
                 name_buf, 0x100);
    error(2, (const char *)0x25d1ac, name_buf, actor_handle & 0xffff,
          (const char *)hs_runtime_get_executing_thread_name());
  }
  FUN_00058af0(actor_handle, encounter_handle, seat_list, 0);
}

/* 0x58fd0 — Build encounter cluster visibility bitvector (PVS intersection). */
void FUN_00058fd0(int encounter_handle, char update_actor_visibility,
                  int cluster_count, int pvs, char *out_cluster_bv)
{
  char *encounter;
  char *enc_def;
  char *scenario;
  int actor_handle;
  char *actor;
  char *unit;
  char *root;
  int16_t cluster;
  int firing_groups;
  int i;
  int j;
  int bv_words;
  char visible;

  scenario = (char *)scenario_get();
  encounter =
      (char *)datum_get(*(data_t **)0x5ab270, encounter_handle);
  enc_def = (char *)tag_block_get_element((char *)global_scenario_get() + 0x42c,
                                          encounter_handle & 0xffff, 0xb0);
  if (*(int *)(scenario + 0x134) > cluster_count) {
    display_assert("cluster_count >= scenario->cluster_count",
                   (const char *)0x25d390, 0x163, 1);
    system_exit(-1);
  }

  bv_words = ((cluster_count + 0x1f) >> 5) << 2;
  csmemset(out_cluster_bv, 0, bv_words);

  actor_handle = *(int *)(encounter + 0x14);
  while (actor_handle != -1) {
    actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
    visible = 1;
    if (*(char *)(actor + 6) != 0) {
      unit = *(int *)(actor + 0x24);
      while (unit != -1) {
        unit = (int)object_get_and_verify_type(unit, 3);
        root = object_get_root_parent(unit);
        root = (char *)object_get_and_verify_type((int)root, -1);
        cluster = *(int16_t *)(root + 0x4c);
        if (cluster >= 0 && cluster < cluster_count)
          out_cluster_bv[(cluster >> 5) * 4] |= (1 << (cluster & 0x1f));
        unit = *(int *)(((char *)unit) + 0x1ac);
      }
    } else {
      unit = (int)object_get_and_verify_type(*(int *)(actor + 0x18), 3);
      root = object_get_root_parent(*(int *)(actor + 0x18));
      root = (char *)object_get_and_verify_type((int)root, -1);
      cluster = *(int16_t *)(root + 0x4c);
      if (cluster >= 0 && cluster < cluster_count)
        out_cluster_bv[(cluster >> 5) * 4] |= (1 << (cluster & 0x1f));
    }
    if (update_actor_visibility) {
      char *squad = encounter_get_squad(encounter, *(int16_t *)(actor + 0x3a));
      *(char *)(actor + 0x12) =
          (char)((*(char *)(squad + 0x14) != 0) ? 0 : visible);
    }
    actor_handle = *(int *)(actor + 0x2c);
  }

  firing_groups = 0;
  for (i = 0; i < *(int *)(enc_def + 0x98); i++) {
    char *fg =
        (char *)tag_block_get_element(enc_def + 0x98, i, 0x18);
    if (*(int16_t *)(fg + 0xe) != -1 && *(int16_t *)(fg + 0xe) >= 0 &&
        *(int16_t *)(fg + 0xe) < cluster_count) {
      cluster = *(int16_t *)(fg + 0xe);
      out_cluster_bv[(cluster >> 5) * 4] |= (1 << (cluster & 0x1f));
    }
  }

  for (i = 0; i < *(int *)(enc_def + 0x80); i++) {
    char *profile =
        (char *)tag_block_get_element(enc_def + 0x80, i, 0xe8);
    for (j = 0; j < *(int *)(profile + 0xc4); j++) {
      char *fp = (char *)tag_block_get_element(profile + 0xc4, j, 0x50);
      if (*(int16_t *)(fp + 0x28) != -1 && *(int16_t *)(fp + 0x28) >= 0 &&
          *(int16_t *)(fp + 0x28) < cluster_count) {
        cluster = *(int16_t *)(fp + 0x28);
        out_cluster_bv[(cluster >> 5) * 4] |= (1 << (cluster & 0x1f));
      }
    }
  }
}

/* 0x59dd0 — Compute pursuit availability flags for an actor. */
void encounter_determine_pursuit_availability(
    int encounter_handle, int actor_handle, int16_t *mode, char flag,
    char *out_guard, char *out_active, char *out_limit_a, char *out_limit_b,
    char *out_nearby, char *out_has_target, char *out_summary)
{
  int actor_iter;
  char *actor;
  int16_t idle_count;
  int16_t combat_count;
  int16_t alert_count;
  int16_t mode_val;
  char nearby_ok;
  char has_target;

  actor_iter = -1;
  if (*(char *)(*(char **)0x632574 + 1) != 0) {
    if (encounter_handle == -1)
      actor_iter = *(int *)(*(char **)0x632574 + 8);
    else
      actor_iter = *(int *)((char *)datum_get(*(data_t **)0x5ab270,
                                              encounter_handle) +
                            0x14);
  }

  idle_count = 0;
  combat_count = 0;
  alert_count = 0;
  while (*(char *)(*(char **)0x632574 + 1) != 0 && actor_iter != -1) {
    actor = (char *)datum_get(*(data_t **)0x6325a4, actor_iter);
    if (actor_iter != actor_handle && *(char *)(actor + 0x1cc) == flag) {
      if (*(int16_t *)(actor + 0x6c) == 5 &&
          *(int16_t *)(actor + 0xa4) == 0 &&
          *(int16_t *)(actor + 0x6e) < 3)
        alert_count++;
      else if (*(int16_t *)(actor + 0x6c) == 7 &&
               *(int16_t *)(actor + 0xa4) == 0)
        combat_count++;
      else
        idle_count++;
    }
    if (*(int16_t *)(actor + 0x6a) == 3)
      alert_count++;
    actor_iter = *(int *)(actor + 0x2c);
  }

  if (mode != NULL) {
    if (*mode == 1)
      mode_val = 0;
    else if (*mode == 2)
      mode_val = 999;
    else {
      int third = (int)alert_count / 3;
      mode_val = (int16_t)(third >= 3 ? third : 3);
    }
    *mode = mode_val;
  }

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  if (flag != 0) {
    nearby_ok =
        (char)(actor_pursuit_find_nearby_actors(actor_handle, 1) >= 2 ? 1 : 0);
    if (out_nearby)
      *out_nearby = nearby_ok;
    *(char *)(actor + 0x1cc) = nearby_ok;
  } else {
    has_target = (char)(*(int *)(actor + 0x1d0) != -1 ? 1 : 0);
    if (out_has_target)
      *out_has_target = has_target;
    *(char *)(actor + 0x1cc) = 0;
    nearby_ok = has_target;
  }

  if (out_summary)
    *out_summary = (char)((out_nearby || out_has_target) ? 1 : 0);
  if (out_guard)
    *out_guard = (char)(alert_count < 6 ? 1 : 0);
  if (out_active)
    *out_active = (char)(combat_count < 4 ? 1 : 0);
  if (out_limit_a)
    *out_limit_a = (char)(idle_count < *mode ? 1 : 0);
  if (out_limit_b)
    *out_limit_b = (char)(idle_count < *mode ? 1 : 0);
}

/* 0x5b370 — Verify firing-position owner actor indices are unique. */
void encounter_verify_firing_position_owner_actor_indices(int encounter_handle)
{
  char *enc_def;
  int count;
  int *seen;
  int actor_handle;
  char *actor;
  int16_t fp_index;
  char stack_seen[0x80c];

  enc_def = (char *)tag_block_get_element((char *)global_scenario_get() + 0x42c,
                                          encounter_handle & 0xffff, 0xb0);
  count = *(int *)(enc_def + 0x98);
  seen = (int *)stack_seen;
  csmemset(seen, 0xff, count * 4);

  actor_handle = -1;
  if (*(char *)(*(char **)0x632574 + 1) != 0) {
    if (encounter_handle == -1)
      actor_handle = *(int *)(*(char **)0x632574 + 8);
    else
      actor_handle = *(int *)((char *)datum_get(*(data_t **)0x5ab270,
                                                encounter_handle) +
                              0x14);
  }

  while (*(char *)(*(char **)0x632574 + 1) != 0 && actor_handle != -1) {
    actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
    fp_index = *(int16_t *)(actor + 0x3b8);
    if (fp_index != -1) {
      if (fp_index < 0 || fp_index >= count) {
        display_assert("firing_position_index>=0 && firing_position_index<count",
                       (const char *)0x25d908, 0x12e, 1);
        system_exit(-1);
      }
      if (seen[fp_index] != -1) {
        display_assert("!firing_position_owner_actor_indices[firing_position_index]",
                       (const char *)0x25d8b8, 0x12f, 1);
        system_exit(-1);
      }
      seen[fp_index] = actor_handle;
    }
    actor_handle = *(int *)(actor + 0x2c);
  }
}

/* 0x5b4b0 — Build firing-position owner actor index table. */
void encounter_build_firing_position_owner_actor_indices(
    int encounter_handle, int *firing_position_owner_actor_indices)
{
  char *enc_def;
  int count;
  int actor_handle;
  char *actor;
  int16_t fp_index;

  enc_def = (char *)tag_block_get_element((char *)global_scenario_get() + 0x42c,
                                          encounter_handle & 0xffff, 0xb0);
  count = *(int *)(enc_def + 0x98);
  csmemset(firing_position_owner_actor_indices, 0xff, count * 4);

  actor_handle = -1;
  if (*(char *)(*(char **)0x632574 + 1) != 0) {
    if (encounter_handle == -1)
      actor_handle = *(int *)(*(char **)0x632574 + 8);
    else
      actor_handle = *(int *)((char *)datum_get(*(data_t **)0x5ab270,
                                                encounter_handle) +
                              0x14);
  }

  while (*(char *)(*(char **)0x632574 + 1) != 0 && actor_handle != -1) {
    actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
    fp_index = *(int16_t *)(actor + 0x3b8);
    if (fp_index != -1) {
      if (fp_index < 0 || fp_index >= count) {
        display_assert("firing_position_index>=0 && firing_position_index<count",
                       (const char *)0x25d908, 0x14c, 1);
        system_exit(-1);
      }
      if (firing_position_owner_actor_indices[fp_index] != -1) {
        display_assert("!firing_position_owner_actor_indices[firing_position_index]",
                       (const char *)0x25d9a0, 0x14d, 1);
        system_exit(-1);
      }
      firing_position_owner_actor_indices[fp_index] = actor_handle;
    }
    actor_handle = *(int *)(actor + 0x2c);
  }
}

/* 0x5bad0 — Weighted random post-combat behavior selection (4 slots). */
int16_t encounter_post_combat_select_random_behavior(void *samples, int *out)
{
  float total;
  float pick;
  int count;
  int i;
  int16_t last;

  total = *(float *)0x2533c0;
  count = 0;
  last = -1;
  for (i = 0; i < 4; i++) {
    char *slot = (char *)samples + i * 0x20;
    if (*(float *)(slot + 4) > *(float *)0x2533c0 &&
        *(int *)slot != -1) {
      total += *(float *)(slot + 4);
      last = (int16_t)i;
      count++;
    }
  }
  if (count <= 1)
    return last;

  pick = random_math_real((unsigned int *)get_global_random_seed_address()) *
         total;
  for (i = 0; i < 4; i++) {
    char *slot = (char *)samples + i * 0x20;
    if (*(float *)(slot + 4) > *(float *)0x2533c0 && *(int *)slot != -1) {
      pick -= *(float *)(slot + 4);
      if (pick <= *(float *)0x2533c0) {
        last = (int16_t)i;
        break;
      }
    }
  }
  if (last != -1 && last >= 0 && last < 4 && out != NULL) {
    char *slot = (char *)samples + (int)last * 0x20;
    out[0] = *(int *)slot;
    out[1] = *(int *)(slot + 4);
    out[2] = *(int *)(slot + 8);
    out[3] = *(int *)(slot + 0xc);
  }
  return last;
}

/* 0x5b790 — Pick random starting location index for a squad profile. */
char FUN_0005B790(int encounter_handle, int16_t squad_index, int flag)
{
  char *encounter;
  char *enc_def;
  char *squad;
  char *profile;
  int total;
  int pick;
  int i;
  int16_t chosen;
  char used_mask[8];

  encounter = (char *)datum_get(*(data_t **)0x5ab270, encounter_handle);
  enc_def = (char *)tag_block_get_element((char *)global_scenario_get() + 0x42c,
                                          encounter_handle & 0xffff, 0xb0);
  squad = encounter_get_squad(encounter, squad_index);
  profile = (char *)tag_block_get_element(enc_def + 0x80, (int)squad_index,
                                          0xe8);
  csmemset(used_mask, 0, 8);

  for (;;) {
    total = 0;
    for (i = 0; i < *(int *)(profile + 0xd0); i++) {
      int bit = 1 << (i & 0x1f);
      if ((*(int *)(squad + ((i >> 5) * 4)) & bit) &&
          (used_mask[i >> 5] & bit) == 0)
        total++;
    }
    if (total <= 0)
      break;

    pick = random_range((unsigned int *)get_global_random_seed_address(), 0,
                        total - 1);
    chosen = -1;
    for (i = 0; i < *(int *)(profile + 0xd0); i++) {
      int bit = 1 << (i & 0x1f);
      if ((*(int *)(squad + ((i >> 5) * 4)) & bit) &&
          (used_mask[i >> 5] & bit) == 0) {
        if (pick == 0) {
          chosen = (int16_t)i;
          used_mask[i >> 5] |= (char)bit;
          *(int *)(squad + ((i >> 5) * 4)) &= ~bit;
          if (*(int *)(squad + 4 + ((i >> 5) * 4)) & bit) {
            *(int *)(squad + 4 + ((i >> 5) * 4)) &= ~bit;
            return (char)chosen;
          }
          display_assert("starting_location_in_use",
                         (const char *)0x25dad0, 0x615, 1);
          system_exit(-1);
        }
        pick--;
      }
    }
    if (chosen != -1)
      return (char)chosen;

    total = 0;
    for (i = 0; i < *(int *)(profile + 0xd0); i++) {
      int bit = 1 << (i & 0x1f);
      if ((used_mask[i >> 5] & bit) == 0 &&
          (*(int *)(squad + 4 + ((i >> 5) * 4)) & bit))
        total++;
    }
    if (total <= 0)
      break;
    pick = random_range((unsigned int *)get_global_random_seed_address(), 0,
                        total - 1);
    for (i = 0; i < *(int *)(profile + 0xd0); i++) {
      int bit = 1 << (i & 0x1f);
      if ((used_mask[i >> 5] & bit) == 0 &&
          (*(int *)(squad + 4 + ((i >> 5) * 4)) & bit)) {
        if (pick == 0) {
          chosen = (int16_t)i;
          used_mask[i >> 5] |= (char)bit;
          *(int *)(squad + 4 + ((i >> 5) * 4)) &= ~bit;
          return (char)chosen;
        }
        pick--;
      }
    }
    if (total > 0) {
      int bytes = ((*(int *)(profile + 0xd0) + 0x1f) >> 5) << 2;
      csmemset(squad + 4, 0xff, bytes);
    }
  }

  display_assert("couldn't find starting location",
                   (const char *)0x25dabc, 0x623, 1);
  system_exit(-1);
  return -1;
}

/* 0x5bbe0 — Post-combat behavior selection for an encounter (large state machine). */
void FUN_0005bbe0(int encounter_handle)
{
  char samples[0xe4];
  char selected[0x10];
  char *encounter;
  int actor_handle;
  char *actor;
  char *unit;
  char picked;
  int16_t behavior_index;
  int i;

  encounter = (char *)datum_get(*(data_t **)0x5ab270, encounter_handle);
  csmemset(selected, 0xff, 4);
  picked = 0;

  actor_handle = -1;
  if (*(char *)(*(char **)0x632574 + 1) != 0) {
    if (encounter_handle == -1)
      actor_handle = *(int *)(*(char **)0x632574 + 8);
    else
      actor_handle = *(int *)(encounter + 0x14);
  }

  while (*(char *)(*(char **)0x632574 + 1) != 0 && actor_handle != -1) {
    actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
    if (*(int *)(actor + 0x18) != -1) {
      char iter[0x44];
      int prop;
      float rating;

      ai_communication_get_player_rating(*(int *)(actor + 0x18), 1, 0, 0,
                                         &rating);
      FUN_00064540((int *)iter, actor_handle);
      for (prop = FUN_00064570((int *)iter); prop != 0;
           prop = FUN_00064570((int *)iter)) {
        char *prop_rec = (char *)prop;
        if (*(char *)(prop_rec + 0x127) != 0) {
          float weight = rating;
          if (*(char *)(prop_rec + 0x12e) != 0)
            weight += *(float *)0x253f40;
          if (FUN_0005ac60((int *)samples, *(int *)(prop_rec + 0x18),
                           weight, 0.0f, 0.0f))
            picked = 1;
        }
      }
    }
    actor_handle = *(int *)(actor + 0x2c);
  }

  if (!picked)
    return;

  behavior_index = encounter_post_combat_select_random_behavior(samples,
                                                                (int *)selected);
  if (*(int16_t *)(encounter + 2) == 2 && *(int16_t *)(encounter + 0x4c) >= 8)
    return;

  for (i = 0; i < 4; i++) {
    char *slot = samples + i * 0x20;
    if (*(int *)slot == selected[0] && *(int *)(slot + 0xc) == selected[3])
      csmemcpy(slot, slot + 0x10, 0x10);
  }
  behavior_index =
      encounter_post_combat_select_random_behavior(samples, (int *)selected);

  /* Apply selected behaviors to actors (simplified tail of binary). */
  actor_handle = -1;
  if (*(char *)(*(char **)0x632574 + 1) != 0) {
    if (encounter_handle == -1)
      actor_handle = *(int *)(*(char **)0x632574 + 8);
    else
      actor_handle = *(int *)(encounter + 0x14);
  }
  while (*(char *)(*(char **)0x632574 + 1) != 0 && actor_handle != -1) {
    actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
    if (*(int *)(actor + 0x18) != -1) {
      unit = (char *)object_get_and_verify_type(*(int *)(actor + 0x18), 3);
      if (behavior_index >= 0 && behavior_index < 4) {
        *(int16_t *)(actor + 0x1e4) =
            *(int16_t *)(0x25d21c + (int)behavior_index * 2);
        *(int *)(actor + 0x1e8) = ((int *)selected)[2];
      }
    }
    actor_handle = *(int *)(actor + 0x2c);
  }

  *(char *)(encounter + 0x47) = 1;
  *(char *)(encounter + 0x48) = 0;
  *(int16_t *)(encounter + 0x4a) = 0x78;
  *(int16_t *)(encounter + 0x4c) = 0;
}

/* 0x5c3a0 — Resolve and spawn starting location for one actor slot. */
char encounter_get_actor_starting_location(int16_t profile_index, int delay,
                                             int flag, int encounter_handle)
{
  char *enc_def;
  char *profile;
  int16_t loc_index;
  char *start_rec;
  char *scenario;
  int16_t bsp_index;
  char major;

  enc_def = (char *)tag_block_get_element((char *)global_scenario_get() + 0x42c,
                                          encounter_handle & 0xffff, 0xb0);
  profile = (char *)tag_block_get_element(enc_def + 0x80, (int)profile_index,
                                          0xe8);
  loc_index = (int16_t)FUN_0005B790(encounter_handle, profile_index, flag);
  if (loc_index == -1)
    return 0;

  start_rec = (char *)tag_block_get_element(profile + 0xd0, (int)loc_index,
                                            0x1c);
  bsp_index = *(int16_t *)(start_rec + 0x18);
  if (bsp_index == -1)
    bsp_index = *(int16_t *)(profile + 0x20);
  if (bsp_index < 0) {
    error(2, (const char *)0x25dc18, profile, enc_def);
    return 0;
  }

  scenario = (char *)global_scenario_get();
  if (bsp_index >= *(int *)(scenario + 0x420))
    return 0;

  major = 0;
  {
    char force = 0;
    int16_t chance = 0;
    char *actv_tag =
        (char *)tag_get(*(int *)tag_block_get_element(scenario + 0x420,
                                                      (int)bsp_index, 0x10),
                        0x61637476);
    if (*(int *)(actv_tag + 0x30) != -1 &&
        ai_get_major_upgrade_chance(*(int16_t *)(profile + 0x80), &force,
                                    &chance)) {
      major = ai_consider_major_upgrade(chance, profile_index,
                                        encounter_handle);
    }
  }

  return (char)(((int(__cdecl *)(int, int, int, char *, int16_t, int, char))0x3f030)(
             *(int *)((char *)tag_block_get_element(scenario + 0x420,
                                                    (int)bsp_index, 0x10) +
                        0xc),
             encounter_handle, (int)profile_index, start_rec,
             (int16_t)profile_index, delay, major)) != -1);
}

/* 0x5c510 — Spawn one actor for a squad if starting location succeeds. */
char encounter_spawn_actor(int encounter_handle, int16_t squad_index)
{
  char *encounter;
  char *enc_def;
  char *squad;
  char *profile;
  float t0;
  float t1;

  if (*(char *)(*(char **)0x632574 + 1) == 0)
    return 0;
  if (!encounter_get_actor_starting_location(squad_index, 0, 1,
                                             encounter_handle))
    return 0;

  encounter = (char *)datum_get(*(data_t **)0x5ab270, encounter_handle);
  enc_def = (char *)tag_block_get_element((char *)global_scenario_get() + 0x42c,
                                          encounter_handle & 0xffff, 0xb0);
  squad = encounter_get_squad(encounter, squad_index);
  profile = (char *)tag_block_get_element(enc_def + 0x80, (int)squad_index,
                                          0xe8);

  *(int16_t *)(encounter + 0x2a) = *(int16_t *)(encounter + 0x2a) + 1;
  *(int16_t *)(squad + 0x18) = *(int16_t *)(squad + 0x18) + 1;
  if (*(int16_t *)(profile + 0x88) > 0)
    *(int16_t *)(squad + 0xc) = *(int16_t *)(squad + 0xc) - 1;

  t0 = random_real_range((unsigned int *)get_global_random_seed_address(),
                         (float)*(int *)(enc_def + 0x2c),
                         (float)*(int *)(enc_def + 0x30));
  t0 *= *(float *)0x253394;
  *(int16_t *)(encounter + 0x3e) =
      (int16_t)((int(__cdecl *)(float))0x1d9068)(t0);

  t1 = random_real_range((unsigned int *)get_global_random_seed_address(),
                         (float)*(int *)(profile + 0x8c),
                         (float)*(int *)(profile + 0x90));
  t1 *= *(float *)0x253394;
  *(int16_t *)(squad + 0xe) = (int16_t)((int(__cdecl *)(float))0x1d9068)(t1);
  return 1;
}

/* 0x5c680 — Encounter spawn scheduler (squads + random fill). */
void FUN_0005c680(int encounter_handle)
{
  char *encounter;
  char *enc_def;
  int squad_i;
  char *squad;
  char *profile;
  char spawn_mask[8];
  int pending;
  int pick;
  int i;

  encounter = (char *)datum_get(*(data_t **)0x5ab270, encounter_handle);
  if (*(char *)(encounter + 0x3c) == 0)
    return;

  if (*(int16_t *)(encounter + 0x3e) > 0xf) {
    *(int16_t *)(encounter + 0x3e) = (int16_t)(*(int16_t *)(encounter + 0x3e) - 0xf);
    return;
  }

  enc_def = (char *)tag_block_get_element((char *)global_scenario_get() + 0x42c,
                                          encounter_handle & 0xffff, 0xb0);
  csmemset(spawn_mask, 0, 8);
  pending = 0;

  for (squad_i = 0; squad_i < *(int *)(enc_def + 0x80); squad_i++) {
    squad = encounter_get_squad(encounter, (short)squad_i);
    profile = (char *)tag_block_get_element(enc_def + 0x80, squad_i, 0xe8);
    while (*(int16_t *)(squad + 0xc) > 0 &&
           *(int16_t *)(squad + 0x18) < *(int16_t *)(profile + 0x84)) {
      if (!encounter_spawn_actor(encounter_handle, (short)squad_i))
        break;
    }
    while (*(int16_t *)(squad + 0xc) > 0 &&
           *(int16_t *)(squad + 0x18) < *(int16_t *)(profile + 0x86)) {
      if (*(int16_t *)(squad + 0xe) > 0xf) {
        *(int16_t *)(squad + 0xe) =
            (int16_t)(*(int16_t *)(squad + 0xe) - 0xf);
      } else {
        int bit = 1 << (squad_i & 0x1f);
        spawn_mask[squad_i >> 5] |= bit;
        pending++;
        *(int16_t *)(squad + 0xe) = 0;
      }
    }
  }

  if (pending <= 0 || *(int16_t *)(encounter + 0x3e) != 0)
    return;

  pick = random_range((unsigned int *)get_global_random_seed_address(), 0,
                      pending - 1);
  for (i = 0; i < *(int16_t *)(encounter + 6); i++) {
    int bit = 1 << (i & 0x1f);
    if (spawn_mask[i >> 5] & bit) {
      if (pick == 0) {
        encounter_spawn_actor(encounter_handle, (short)i);
        return;
      }
      pick--;
    }
  }
}

/* 0x5ca80 — Post-activation squad assignment / migration pass. */
void FUN_0005ca80(int encounter_handle)
{
  char *encounter;
  char *enc_def;
  int16_t mode;
  int targets[8];
  int target_count;
  int squad_mask[3];
  int squad_active[3];
  int per_squad_flags[0x80];
  float best_near;
  float best_far;
  int16_t best_squad;
  int16_t best_actor;
  int actor_handle;
  char *actor;
  int i;
  int s;
  data_iter_t pit;
  char *player;

  encounter = (char *)datum_get(*(data_t **)0x5ab270, encounter_handle);
  enc_def = (char *)tag_block_get_element((char *)global_scenario_get() + 0x42c,
                                          encounter_handle & 0xffff, 0xb0);
  mode = *(int16_t *)(encounter + 0x62);
  target_count = 0;

  if (mode == 1) {
    if (*(int *)(encounter + 0x64) != -1) {
      char iter[0x60];
      int rec;
      FUN_00054680((unsigned int)*(int *)(encounter + 0x64), iter);
      for (rec = FUN_00054750(iter); rec != 0 && target_count < 8;
           rec = FUN_00054750(iter))
        targets[target_count++] = *(int *)(rec + 0x18);
    }
  } else if (mode == 0) {
    data_iterator_new(&pit, *(data_t **)0x5aa6d4);
    for (player = (char *)data_iterator_next(&pit); player != NULL;
         player = (char *)data_iterator_next(&pit)) {
      if (*(int *)(player + 0x34) != -1 && target_count < 8)
        targets[target_count++] = *(int *)(player + 0x34);
    }
  } else if (mode == 2) {
    if (object_try_and_get_and_verify_type(*(int *)(encounter + 0x64), 3))
      targets[target_count++] = *(int *)(encounter + 0x64);
    else
      *(int *)(encounter + 0x64) = -1;
  } else {
    return;
  }

  if (target_count <= 0)
    return;

  csmemset(squad_mask, 0, sizeof(squad_mask));
  csmemset(squad_active, 0, sizeof(squad_active));
  csmemset(per_squad_flags, 0, sizeof(per_squad_flags));

  for (s = 0; s < *(int16_t *)(encounter + 6); s++) {
    char *squad = encounter_get_squad(encounter, (short)s);
    char *profile =
        (char *)tag_block_get_element(enc_def + 0x80, s, 0xe8);
    if ((*(char *)(profile + 0x28) & 0x20) == 0)
      continue;
    squad_mask[s >> 5] |= 1 << (s & 0x1f);
    squad_active[s >> 5] |= 1 << (s & 0x1f);
    *(int16_t *)(encounter + 0x14) =
        (int16_t)(*(int16_t *)(encounter + 0x14) + *(int16_t *)(squad + 0x18));
  }

  if (*(int16_t *)(encounter + 0x14) <= 0)
    return;

  best_near = *(float *)0x2548fc;
  best_far = -*(float *)0x2548fc;
  best_squad = -1;
  best_actor = -1;

  actor_handle = *(int *)(encounter + 0x14);
  while (actor_handle != -1) {
    actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
    s = *(int16_t *)(actor + 0x3a);
    if ((squad_active[s >> 5] & (1 << (s & 0x1f))) != 0) {
      float dist = *(float *)(actor + 0x120); /* placeholder: binary uses 3d */
      if (dist < best_near) {
        best_near = dist;
        best_squad = s;
        best_actor = (int16_t)actor_handle;
      }
      if (dist > best_far)
        best_far = dist;
    }
    actor_handle = *(int *)(actor + 0x2c);
  }

  if (best_squad != -1 && best_actor != -1) {
    actor = (char *)datum_get(*(data_t **)0x6325a4, best_actor);
    if (*(int16_t *)(actor + 0x3a) != best_squad)
      FUN_0003baa0(best_actor, encounter_handle, best_squad);
  }
}


