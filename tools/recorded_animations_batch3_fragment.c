/* --- recorded_animations.obj batch3 drafts (2026-07-26) --- */

#define RA3_EVENT_ASSERT(line, msg) \
  do { \
    display_assert((char *)(msg), \
                   "c:\\halo\\SOURCE\\cutscene\\recorded_animations.c", (line), 1); \
    system_exit(-1); \
  } while (0)

static void ra3_check_ptr(void *p, int line, void *msg)
{
  if (!p)
    RA3_EVENT_ASSERT(line, msg);
}

char FUN_000940a0(char *thread, void *event, int *ticks, int **cursor)
{
  uint8_t *evt;
  uint16_t tick_amount;
  int cursor_advance;
  void *handler;

  ra3_check_ptr(thread, 0x113, (void *)0x2690a0);
  ra3_check_ptr(event, 0x114, (void *)0x269368);
  ra3_check_ptr(ticks, 0x115, (void *)0x269358);
  ra3_check_ptr(cursor, 0x115, (void *)0x269358);
  if (**cursor == 0)
    RA3_EVENT_ASSERT(0x116, (void *)0x269344);

  evt = (uint8_t *)**cursor;
  for (;;) {
    uint8_t header = evt[0];
    uint8_t type_low = header & 3;

    switch (type_low) {
    case 0:
      tick_amount = 0;
      cursor_advance = 1;
      break;
    case 1:
      tick_amount = 1;
      cursor_advance = 1;
      break;
    case 2:
      tick_amount = evt[1];
      cursor_advance = 2;
      if (tick_amount <= 1)
        RA3_EVENT_ASSERT(0x12d, (void *)0x269318);
      break;
    case 3:
      tick_amount = *(uint16_t *)(evt + 1);
      cursor_advance = 3;
      if (tick_amount <= 0xff)
        RA3_EVENT_ASSERT(0x132, (void *)0x2692f8);
      break;
    default:
      RA3_EVENT_ASSERT(0x135, (void *)0x255ee8);
    }

    if (*ticks < tick_amount)
      goto stream_done;
    if ((header & 0xfc) == 4)
      goto stream_done;

    **cursor = (int)((char *)**cursor + cursor_advance);

    if ((header & 0xfc) >= 0x5c)
      RA3_EVENT_ASSERT(0x13b, (void *)0x2692cc);

    handler = *(void **)((char *)0x2ee960 + (header >> 2) * 4);
    if (handler != NULL)
      ((void (*)(char *, void *, int **))handler)(thread, evt, cursor);

    *ticks -= tick_amount;
    evt = (uint8_t *)**cursor;
  }

stream_done:
  if ((evt[0] & 0xfc) == 4 && *ticks == tick_amount)
    return 0;
  return 1;
}

void render_debug_recording(void)
{
  char buffer[0x2818];
  int16_t tab_stops[2];
  data_iter_t iter;
  char *thread;
  int out_len;
  int16_t line;
  char *dbg_slot;
  void *unit;
  scenario_t *scenario;
  char *anim_name;
  char *default_name;

  if (*(uint8_t *)0x44df08 == 0)
    return;

  out_len = 0;
  tab_stops[0] = 0xc8;
  tab_stops[1] = 0x12c;

  for (line = 0; line < *(int16_t *)0x2eebc0; line++) {
    out_len += crt_sprintf(buffer + out_len, (char *)0x26993c, line);
  }
  out_len += crt_sprintf(buffer + out_len, (char *)0x269914);

  data_iterator_new(&iter, *(data_t **)0x44df04);
  thread = (char *)data_iterator_next(&iter);
  while (thread != NULL) {
    unit = object_try_and_get_and_verify_type(*(int *)(thread + 4), -1);
    dbg_slot = (char *)((iter.datum_handle & 0xffff) * 0x10 + *(int *)0x44df0c);
    if ((*(uint8_t *)(thread + 0xa) & 1) == 0 && unit != NULL &&
        *(int16_t *)((char *)unit + 0x6a) != -1) {
      scenario = global_scenario_get();
      anim_name = (char *)tag_block_get_element((char *)scenario + 0x204,
                                                *(int16_t *)((char *)unit + 0x6a),
                                                0x24);
      default_name = (char *)0x25b724;
      if (*dbg_slot != 0) {
        default_name = (char *)tag_block_get_element((char *)scenario + 0x36c,
                                                     *(int16_t *)(dbg_slot + 0xc),
                                                     0x40);
      }
      out_len += crt_sprintf(buffer + out_len, (char *)0x26990c, default_name);
      out_len += crt_sprintf(buffer + out_len, (char *)0x269904,
                             *(uint16_t *)(thread + 8));
      out_len += crt_sprintf(buffer + out_len, (char *)0x257984, anim_name);
    }
    thread = (char *)data_iterator_next(&iter);
  }

  buffer[out_len] = 0;
  draw_string_set_tab_stops(tab_stops, 2);
  FUN_00189c40(1, buffer);
  draw_string_set_tab_stops(tab_stops, 0);
}

char recorded_animation_play_internal(int unit, int anim, int flags)
{
  scenario_t *scenario;
  char *anim_def;
  char *thread;
  int thread_handle;
  void **vtable;
  int anim_type;
  char *dbg_slot;
  char result;
  uint16_t extra_flags;

  result = 0;
  if (unit == -1) {
    error(2, (char *)0x269940);
    return result;
  }
  if ((int16_t)anim == -1) {
    error(2, (char *)0x269954);
    return result;
  }

  scenario = global_scenario_get();
  if ((int)anim >= *(int *)((char *)scenario + 0x36c)) {
    error(2, (char *)0x269954);
    return result;
  }

  object_get_and_verify_type(unit, 3);
  player_index_from_unit_index(unit);
  FUN_00095050(unit, &thread_handle);

  anim_def = (char *)tag_block_get_element((char *)scenario + 0x36c, anim, 0x40);
  if (recorded_animation_controlling_unit(unit) != 0) {
    if (thread_handle != -1) {
      dbg_slot = (char *)((thread_handle & 0xffff) * 0x10 + *(int *)0x44df0c);
      error(2, (char *)0x269994,
            (char *)tag_block_get_element((char *)scenario + 0x36c,
                                          *(int16_t *)(dbg_slot + 0xc), 0x40));
    } else {
      error(2, (char *)0x269974);
    }
    return result;
  }

  thread = NULL;
  if (thread_handle == -1) {
    thread_handle = data_new_at_index(*(data_t **)0x44df04);
    if (thread_handle == -1) {
      error(2, (char *)0x269a2c);
      return result;
    }
    thread = (char *)datum_get(*(data_t **)0x44df04, thread_handle);
    if (thread == NULL) {
      error(2, (char *)0x269a2c);
      return result;
    }
  } else {
    thread = (char *)datum_get(*(data_t **)0x44df04, thread_handle);
  }

  anim_type = *(uint8_t *)(anim_def + 0x20);
  if (anim_type == 0 || anim_type > 4 ||
      *(void **)((char *)0x2eebac + anim_type * 4) == NULL) {
    display_assert((char *)0x2699c0,
                   "c:\\halo\\SOURCE\\cutscene\\recorded_animations.c", 0xe9,
                   1);
    system_exit(-1);
  }

  *(int *)(thread + 4) = unit;
  *(int *)(thread + 0xc) = 0;
  *(int16_t *)(thread + 8) = *(int16_t *)(anim_def + 0x24);
  *(void **)(thread + 0x10) =
      tag_data_get_pointer(anim_def + 0x2c, 0, *(int *)(anim_def + 0x2c));

  dbg_slot = (char *)((thread_handle & 0xffff) * 0x10 + *(int *)0x44df0c);
  *dbg_slot = 1;
  *(void **)(dbg_slot + 4) = *(void **)(thread + 0x10);
  *(int16_t *)(dbg_slot + 0xc) = (int16_t)anim;
  *(int *)(dbg_slot + 8) = *(int *)(anim_def + 0x2c);

  *(uint8_t *)(thread + 0xa) &= 0xfe;
  *(int16_t *)(thread + 0x60) = (int16_t)(anim_type - 1);
  vtable = *(void ***)((char *)0x2eebb0 + (anim_type - 1) * 4);
  ((void (*)(char *, char *, int *, char *))vtable[0])(
      thread + 0x54, thread + 0x14, (int *)(thread + 0x10),
      anim_def + 0x18);

  unit_set_actively_controlled(unit, 1);
  if (unit_is_alive(unit) != 0)
    *(uint8_t *)(thread + 0xa) |= 4;
  else
    *(uint8_t *)(thread + 0xa) &= 0xfb;

  unit_set_controllable(unit, 0);
  unit_set_possessed(unit, 1);
  object_set_automatic_deactivation(unit, 0);
  extra_flags = (uint16_t)flags;
  *(uint16_t *)(thread + 0xa) |= extra_flags;
  return 1;
}

void control_toggle(int object)
{
  char *dev;
  char *tag;
  void *recording;
  float value;
  int16_t control_type;
  int16_t recording_index;

  dev = (char *)object_get_and_verify_type(object, 0x100);
  tag = (char *)tag_get(0x6374726c, *(int *)dev);
  recording_index = *(int16_t *)(dev + 0x1b4);
  if (recording_index == -1)
    return;

  recording = datum_get(*(data_t **)0x5aa8c8, recording_index);
  control_type = *(int16_t *)(tag + 0x290);
  if (control_type > 3) {
    display_assert((char *)0,
                   "c:\\halo\\SOURCE\\cutscene\\recorded_animations.c", 0x8a,
                   1);
    system_exit(-1);
  }

  switch (control_type) {
  case 0:
    if (*(float *)((char *)recording + 4) == *(float *)0x253398)
      value = 0.0f;
    else
      value = 1.0f;
    break;
  case 1:
    value = 1.0f;
    break;
  case 2:
    value = 0.0f;
    break;
  default:
    value = *(float *)(tag + 0x294);
    break;
  }

  if (FUN_00096f20(recording_index, value) == 0) {
    FUN_000967a0(*(void **)(tag + 0x314), object);
    return;
  }

  if (value == *(float *)0x253398)
    FUN_000967a0(*(void **)(tag + 0x2f4), object);
  else
    FUN_000967a0(*(void **)(tag + 0x304), object);
}

char FUN_00095c60(int object)
{
  int handles[0x10];
  int *big_handles;
  char *dev;
  char *tag;
  float radius;
  int16_t count;
  int i;
  char triggered;
  char *other;
  char *other_tag;
  char valid_target;
  void *node_matrix;
  float delta[3];
  float pos[3];

  dev = (char *)object_get_and_verify_type(object, 0x80);
  tag = (char *)tag_get(0x6d616368, *(int *)dev);

  if (*(int16_t *)(tag + 0x290) == 2) {
    float mix;
    float new_val;

    mix = *(float *)0x2533c8 - *(float *)(dev + 0x1ac);
    new_val = *(float *)(tag + 0x288) * *(float *)(dev + 0x1ac) +
              *(float *)(tag + 0x280) * mix + *(float *)(dev + 0x1b8);
    *(float *)(dev + 0x1b8) = new_val;
    if (new_val >= *(float *)0x2533c8)
      *(float *)(dev + 0x1b8) -= *(float *)0x2533c8;

    *(int *)(dev + 4) |= 4;
    *(int *)(dev + 0x1bc) = 0;
    if (*(int16_t *)(dev + 0x1b4) != -1) {
      void *recording =
          datum_get(*(data_t **)0x5aa8c8, *(int16_t *)(dev + 0x1b4));
      *(float *)((char *)recording + 4) = *(float *)(dev + 0x1b8);
    }
  }

  if ((*(uint8_t *)(dev + 0x1c4) & 1) != 0)
    goto finish;

  if (*(int16_t *)(tag + 0x290) == 0) {
    if (((game_time_get() + object) & 3) == 0) {
      if (*(float *)(tag + 0x21c) >= *(float *)0x253f44)
        radius = *(float *)(dev + 0x5c);
      else
        radius = *(float *)(tag + 0x21c);

      triggered = 0;
      count = object_find_in_radius(1, 1, dev + 0x48, (float *)(dev + 0x50),
                                    radius, handles, 0x10);
      if (count > 0) {
        for (i = 0; i < count; i++) {
          other = (char *)object_get_and_verify_type(handles[i], 3);
          other_tag = (char *)tag_get(0x756e6974, *(int *)other);
          valid_target = 1;
          if ((*(uint8_t *)(other + 0xb6) & 4) != 0 ||
              (*(uint8_t *)(other_tag + 0x17c) & 0x40) == 0)
            valid_target = 0;

          if ((*(uint8_t *)(dev + 0x1c4) & 2) != 0 &&
              *(float *)(dev + 0x1b8) > *(float *)0x2533c0 &&
              game_allegiance_get_team_is_friendly(1, *(int16_t *)(other + 0x68)) ==
                  0) {
            float facing;

            facing = (*(float *)(other + 0x50) - *(float *)(dev + 0x50)) *
                         *(float *)(dev + 0x28) +
                     (*(float *)(other + 0x54) - *(float *)(dev + 0x54)) *
                         *(float *)(dev + 0x2c) +
                     (*(float *)(other + 0x58) - *(float *)(dev + 0x58)) *
                         *(float *)(dev + 0x24);
            if (facing <= *(float *)0x2533c0)
              valid_target = 0;
          }

          if (valid_target != 0)
            triggered = 1;
        }
      }

      if (triggered != 0) {
        if (*(int16_t *)(dev + 0x1b4) != -1)
          FUN_00096f20(*(int16_t *)(dev + 0x1b4), 1.0f);
        *(int *)(dev + 0x1c8) = -3;
      }
    }

    if (*(float *)(dev + 0x1b8) == 1.0f) {
      *(int *)(dev + 0x1c8) = *(int *)(dev + 0x1c8) + 1;
      if (*(int *)(dev + 0x1c8) > *(int *)(tag + 0x320) &&
          *(int16_t *)(dev + 0x1b4) != -1)
        FUN_00096f20(*(int16_t *)(dev + 0x1b4), 0.0f);
    } else {
      *(int *)(dev + 0x1c8) = 0;
    }
  }

  if ((*(uint8_t *)(tag + 0x292) & 4) != 0 &&
      *(int16_t *)(tag + 0x2ea) != -1) {
    int j;
    int16_t attached_count;
    char scratch[0x2068];

    node_matrix = object_get_node_matrix(object, *(int16_t *)(tag + 0x2ea));
    delta[0] = *(float *)((char *)node_matrix + 0x28) - *(float *)(dev + 0x1cc);
    delta[1] = *(float *)((char *)node_matrix + 0x2c) - *(float *)(dev + 0x1d0);
    delta[2] = *(float *)((char *)node_matrix + 0x30) - *(float *)(dev + 0x1d4);
    if (!(delta[0] == 0.0f && delta[1] == 0.0f && delta[2] == 0.0f)) {
      big_handles = (int *)scratch;
      attached_count = object_find_in_radius(
          1, 1, dev + 0x48, (float *)(dev + 0x50), *(float *)(dev + 0x5c),
          big_handles, 0x800);
      if (attached_count > 0) {
        for (j = 0; j < attached_count; j++) {
          other = (char *)object_get_and_verify_type(big_handles[j], 1);
          if (*(int *)(other + 0x42c) == object) {
            pos[0] = delta[0] + *(float *)(other + 0xc);
            pos[1] = delta[1] + *(float *)(other + 0x10);
            pos[2] = delta[2] + *(float *)(other + 0x14);
            object_translate(big_handles[j], pos, NULL);
          }
        }
      }
    }

    *(float *)(dev + 0x1cc) = *(float *)((char *)node_matrix + 0x28);
    *(float *)(dev + 0x1d0) = *(float *)((char *)node_matrix + 0x2c);
    *(float *)(dev + 0x1d4) = *(float *)((char *)node_matrix + 0x30);
  }

  if ((*(uint8_t *)(dev + 0x1a4) & 4) != 0) {
    object_translate(object, (float *)(dev + 0xc), NULL);
    *(int *)(dev + 0x1a4) &= ~4;
  }

finish:
  return 1;
}

#undef RA3_EVENT_ASSERT
