/* sound_object_apply_pitch_delta (0x1ac2f0)
 *
 * Computes a clamped pitch delta and accumulates it onto the object's
 * pitch field at offset 0x298.  The incoming pitch is differenced against
 * the current stored value; the resulting delta is clamped to [-0.3, 0.3]
 * before being added back to the stored pitch. */
void sound_object_apply_pitch_delta(int object_handle, float pitch)
{
  char *obj;
  float *stored_pitch;
  float delta;

  obj = (char *)object_get_and_verify_type(object_handle, 3);
  stored_pitch = (float *)(obj + 0x298);
  delta = pitch - *stored_pitch;

  if (delta < -0.3f) {
    delta = -0.3f;
  } else if (delta > 0.3f) {
    delta = 0.3f;
  }

  *stored_pitch += delta;
}

/* sound_cache_sound_finished (0x1be090)
 *
 * Decrements the software_reference_count on a cache-sound entry when a
 * sound permutation finishes playing. Takes the permutation tag pointer,
 * reads the cache handle from offset +0x2c, and looks up the corresponding
 * cache-sound datum from the sound cache table at 0x4e9368.
 *
 * If the debug trace flag at 0x5054ec is set, logs the current reference
 * count and name before decrementing.
 *
 * Asserts that software_reference_count is nonzero before decrementing
 * (source: c:\halo\SOURCE\cache\xbox_sound_cache.c, line 263). */
void sound_cache_sound_finished(int permutation_ptr)
{
  char *cache_sound;
  int cache_handle;

  /* When the sound cache is blown the allocation in xbox_sound_cache.c never
   * writes back to perm+0x2c, leaving it at NONE.  datum_get halts on NONE,
   * so guard here — nothing to decrement if no cache entry was ever assigned.
   */
  cache_handle = *(int *)(permutation_ptr + 0x2c);
  if (cache_handle == NONE) {
    display_assert(
      "cache_sound_handle!=NONE (sound cache blown, no entry to finish)",
      __FILE__, __LINE__, false);
    return;
  }

  cache_sound = (char *)datum_get(*(data_t **)0x4e9368, cache_handle);

  if (*(uint8_t *)0x5054ec != 0) {
    error(2, "--- finish %d %s", *(uint8_t *)(cache_sound + 4),
          *(char **)(cache_sound + 8));
  }

  assert_halt(*(uint8_t *)(cache_sound + 4));

  *(uint8_t *)(cache_sound + 4) -= 1;
}

/* sound_pitch_push_sample (0x1c7b00)
 *
 * Conditionally applies a pitch sample to an object's pitch-track field.
 * Only runs if the object looping sounds table (0x5054e4) is initialized
 * (byte +0x24 != 0).  Validates the object handle as type 3 (biped|vehicle)
 * via object_try_and_get_and_verify_type before forwarding to
 * sound_object_apply_pitch_delta (0x1ac2f0). */
void sound_pitch_push_sample(int object_handle, float pitch)
{
  if (*(uint8_t *)(*(int *)0x5054e4 + 0x24) != 0) {
    if (object_try_and_get_and_verify_type(object_handle, 3) != 0) {
      sound_object_apply_pitch_delta(object_handle, pitch);
    }
  }
}

/* Return a pointer to the sound class definition at class_index.
 * The definitions live in a static table at 0x32ed08 with a stride of 0x2c.
 * Originally inlined from sound_classes.h; compiled into sound_manager.obj.
 * Asserts that class_index is in range [0,0x33), the class name is non-empty,
 * and the per-definition and per-object instance limits are <= 0x10. */
void *sound_class_get_definition(short class_index)
{
  int idx = (int)class_index;
  void *definition = (void *)(0x32ed08 + idx * 0x2c);

  assert_halt(class_index >= 0 && class_index < 0x33);
  assert_halt(((const char **)0x32f5d0)[idx][0]);
  assert_halt(*(short *)definition <= 0x10);
  assert_halt(*(short *)((char *)definition + 2) <= 0x10);

  return definition;
}

/* Return the default priority for a sound tag (0x1c8d10).
 * Reads the priority field at tag offset 0xc. If zero, falls back to
 * the sound class definition's default priority at offset 0x1c. */
float sound_get_default_priority(int sound_tag_index)
{
  void *sound_tag = tag_get(0x736e6421, sound_tag_index);
  float priority = *(float *)((char *)sound_tag + 0xc);

  if (priority == 0.0f) {
    short class_index = *(short *)((char *)sound_tag + 0x4);
    void *class_def = sound_class_get_definition(class_index);
    priority = *(float *)((char *)class_def + 0x1c);
  }

  return priority;
}

/* Return the minimum-distance attenuation for a sound tag.
 * Reads the per-tag min_distance override at tag offset 0x8.
 * If it is zero, falls back to the min_distance field (offset 0x18)
 * of the sound class definition looked up via the tag's class_index
 * at offset 0x4. */
float sound_class_get_min_distance(int sound_tag_index)
{
  void *sound_tag = tag_get(0x736e6421, sound_tag_index);
  float min_distance = *(float *)((char *)sound_tag + 0x8);

  if (min_distance == 0.0f) {
    short class_index = *(short *)((char *)sound_tag + 0x4);
    void *class_def = sound_class_get_definition(class_index);
    min_distance = *(float *)((char *)class_def + 0x18);
  }

  return min_distance;
}

/* Select the best pitch range for a given random scale value (0x1c8de0).
 * If hint_index is valid and its bend bounds contain random_scale with at
 * least one permutation, returns hint_index directly. Otherwise scans all
 * pitch ranges: an exact match returns immediately, otherwise tracks the
 * closest range by ratio of bend bounds to scale. */
short sound_select_pitch_range(void *sound_tag, float random_scale,
                               short hint_index)
{
  short best_index = -1;
  char *tag = (char *)sound_tag;

  if (hint_index != -1) {
    if ((int)hint_index < *(int *)(tag + 0x98)) {
      char *pitch_range =
        (char *)tag_block_get_element(tag + 0x98, (int)hint_index, 0x48);
      float min_bend = *(float *)(pitch_range + 0x24);
      float max_bend = *(float *)(pitch_range + 0x28);
      if (min_bend <= random_scale && random_scale <= max_bend &&
          *(int *)(pitch_range + 0x3c) != 0) {
        return hint_index;
      }
    }
  }

  {
    int count = *(int *)(tag + 0x98);
    float best_distance = 3.4028235e+38f;
    short i;
    for (i = 0; (int)i < count; i++) {
      char *pitch_range;
      float min_bend;
      float max_bend;
      float distance;

      pitch_range = (char *)tag_block_get_element(tag + 0x98, (int)i, 0x48);
      if (*(int *)(pitch_range + 0x3c) == 0)
        continue;

      min_bend = *(float *)(pitch_range + 0x24);
      max_bend = *(float *)(pitch_range + 0x28);

      if (min_bend <= random_scale && random_scale <= max_bend)
        return i;

      if (random_scale <= max_bend) {
        distance = min_bend / random_scale;
      } else {
        distance = random_scale / max_bend;
      }

      if (distance < best_distance) {
        best_distance = distance;
        best_index = i;
      }
    }
  }

  return best_index;
}

/* Sample a pitch value from a permutation's mouth data (0x1c8f20).
 *
 * Clamps permutation_index into [0, mouth_data.size-1], reads the
 * corresponding byte from the mouth data block via FUN_001c8d90,
 * and normalizes it to [0.0, 1.0] by dividing by 255.
 * If the permutation has no mouth data (size == 0), logs an error
 * and returns 0.0f. */
float sound_get_permutation_pitch(int permutation_block_ptr,
                                  short permutation_index)
{
  int mouth_data_size = *(int *)((char *)permutation_block_ptr + 0x54);
  int clamped_index;

  if (mouth_data_size != 0) {
    if (permutation_index < 0) {
      clamped_index = 0;
    } else {
      clamped_index = mouth_data_size - 1;
      if ((int)permutation_index <= clamped_index) {
        clamped_index = (int)permutation_index;
      }
    }

    {
      uint8_t *byte_ptr =
        (uint8_t *)FUN_001c8d90(permutation_block_ptr, clamped_index);
      int byte_value = (int)*byte_ptr;
      return (float)byte_value * (1.0f / 255.0f);
    }
  }

  error(2, "but how can you speak if you have no mouth data? (permutation %s)",
        permutation_block_ptr);
  return 0.0f;
}

/* Select a permutation from a pitch range (0x1c8f80).
 * If a next-permutation is queued (offset 0x3a), consumes and returns it.
 * If the sound tag has the sequential flag (bit 1) and a hint is given,
 * returns that permutation's chained next index (offset 0x2a).
 * Otherwise performs weighted random selection with a played-bit mask
 * (offset 0x34) to avoid repeats, accepting unconditionally after 16 tries. */
short sound_select_permutation(void *sound_tag, short pitch_range_index,
                               short hint_permutation_index)
{
  char *tag = (char *)sound_tag;
  char *pitch_range =
    (char *)tag_block_get_element(tag + 0x98, (int)pitch_range_index, 0x48);
  short attempts = 0;

  if (*(int *)(pitch_range + 0x3c) == 0) {
    display_assert("range->permutations.count",
                   "c:\\halo\\SOURCE\\sound\\sound_definitions.c", 0x37c, 1);
    system_exit(-1);
  }

  {
    short next = *(short *)(pitch_range + 0x3a);
    if (next != -1) {
      *(short *)(pitch_range + 0x3a) = -1;
      *(short *)(pitch_range + 0x38) = next;
      return next;
    }
  }

  if ((*(uint8_t *)tag & 2) != 0 && hint_permutation_index != -1) {
    char *perm = (char *)tag_block_get_element(
      pitch_range + 0x3c, (int)hint_permutation_index, 0x7c);
    return *(short *)(perm + 0x2a);
  }

  {
    short count = *(short *)(pitch_range + 0x2c);
    unsigned int *seed = random_math_get_local_seed_address();
    short selected = random_range(seed, 0, count);

    for (;;) {
      uint32_t all_bits = (1u << ((uint8_t)count & 0x1f)) - 1;

      if ((~*(uint32_t *)(pitch_range + 0x34) & all_bits) == 0) {
        *(uint32_t *)(pitch_range + 0x34) = 0;
        if (count > 1) {
          *(uint32_t *)(pitch_range + 0x34) =
            1u << ((uint8_t) * (short *)(pitch_range + 0x38) & 0x1f);
        }
      }

      {
        uint32_t bit = 1u << ((uint8_t)selected & 0x1f);
        if ((*(uint32_t *)(pitch_range + 0x34) & bit) == 0) {
          *(uint32_t *)(pitch_range + 0x34) |= bit;

          if (attempts == 0x10) {
            *(short *)(pitch_range + 0x38) = selected;
            return selected;
          }

          attempts++;
          seed = random_math_get_local_seed_address();

          {
            float random_val = random_math_real(seed);
            char *perm = (char *)tag_block_get_element(pitch_range + 0x3c,
                                                       (int)selected, 0x7c);

            if (random_val >= *(float *)(perm + 0x20)) {
              *(short *)(pitch_range + 0x38) = selected;
              return selected;
            }
          }
        }
      }

      selected++;
      if (selected == *(short *)(pitch_range + 0x2c)) {
        selected = 0;
      }
    }
  }
}

/* sound_valid_for_channel (0x1cb790)
 *
 * Check whether a sound definition's compression, encoding, sample_rate,
 * and spatialization_mode are compatible with a channel's type_flags word.
 *
 * Each bit of type_flags encodes a channel capability:
 *   bit 0: spatialization (mono/stereo) — skipped if bit 1 is set
 *   bit 1: skip-spatialization flag
 *   bit 2: sample rate (0 = 22050, 1 = 44100)
 *   bit 3: compression (0 = uncompressed, 1 = compressed)
 *
 * For bits 0, 1, 3 the test is inverted: the NOT of the bit must equal
 * whether the corresponding parameter is zero. */
bool sound_valid_for_channel(short compression, short encoding,
                             unsigned short sample_rate,
                             short spatialization_mode,
                             unsigned short type_flags)
{
  int flags;
  bool result;

  flags = (int)(short)type_flags;

  /* Check compression: (~(flags >> 3) & 1) must equal (compression == 0) */
  result = true;
  if ((~(flags >> 3) & 1) != (unsigned int)(compression == 0))
    result = false;

  /* Check encoding: (~(flags >> 1) & 1) must equal (encoding == 0) */
  if ((~(flags >> 1) & 1) != (unsigned int)(encoding == 0))
    result = false;

  /* Check sample_rate: ((flags >> 2) & 1) must equal sample_rate */
  if ((unsigned short)((flags >> 2) & 1) != sample_rate)
    result = false;

  /* Check spatialization: only if bit 1 of type_flags is clear */
  if (!(type_flags & 2)) {
    if ((~flags & 1) != (unsigned int)(spatialization_mode == 0))
      result = false;
  }

  return result;
}

/* Empty on Xbox — no per-map sound initialization needed. */
void sound_initialize_for_new_map(void)
{
}

/* Fade out all active sounds and then stop the sound manager for map unload.
 *
 * If the sound manager is initialized and hardware is present:
 *   1. Trigger a linear fade-out on every active sound in the sounds table
 *      (0.3s fade, mode=linear, fade_out only — fade_in_index=NONE).
 *   2. Spin-loop calling sound_update() until 300 ms have elapsed since the
 *      fade was started (blocking wait for the fade to complete).
 *   3. After the wait, if the fade flag (0x4eaf42) is set, clear it, call
 *      vtable+0x28(0) to stop hardware output, and record the timestamp.
 * Finally, unconditionally stop all channels (sound_stop_all) and re-validate
 * the looping-sounds table so it is ready for the next map. */
/* sound_set_music_enabled (0x1cb8a0)
 *
 * Sets the sound system's music/fade flag at 0x4eaf42. If the new state
 * differs from the current one, updates the flag, calls the sound driver's
 * vtable+0x28 method with the enabled parameter, and -- when disabling
 * (enabled=0) -- records the current timestamp so the fade-out timing in
 * sound_dispose_from_old_map has a reference point.
 */
void sound_set_music_enabled(int enabled)
{
  char cur = *(char *)0x4eaf42;
  char val = (char)enabled;

  if (val != cur) {
    *(char *)0x4eaf42 = val;
    (*(void (**)(int))(*(int *)0x4eaf48 + 0x28))(enabled);
    if (val == '\0')
      *(unsigned int *)0x4eaf4c = system_milliseconds();
  }
}

/* sound_get_previous_ms (0x1cb8e0)
 *
 * Returns the sound system's last-recorded millisecond timestamp.
 */
unsigned int sound_render_time(void)
{
  return *(unsigned int *)0x4eaf4c;
}

/* Check whether a sound tag can currently play.
 *
 * sound_tag_index is passed in EAX (register argument).
 *
 * Loads the sound tag, checks that pitch range 0 has at least one permutation,
 * then looks up the sound class definition for the tag's class index. If the
 * class definition's "suppress" byte (offset 0x28) is zero, the sound is
 * allowed to play. Returns true (1) if playable, false (0) otherwise. */
bool sound_can_play(int sound_tag_index /* @<eax> */)
{
  void *sound_tag;
  void *pitch_range_element;
  void *class_def;

  sound_tag = tag_get(0x736e6421, sound_tag_index);
  if (*(int *)((char *)sound_tag + 0x98) != 0) {
    pitch_range_element =
      tag_block_get_element((char *)sound_tag + 0x98, 0, 0x48);
    if (*(int *)((char *)pitch_range_element + 0x3c) != 0) {
      class_def = sound_class_get_definition(*(short *)((char *)sound_tag + 4));
      if (*(char *)((char *)class_def + 0x28) == '\0') {
        return 1;
      }
    }
  }
  return 0;
}

/* sound_channel_get (0x1cba80)
 *
 * Return a pointer to the sound channel entry at the given index.
 * Channels live in a static array at 0x4fc3a0 with a stride of 0x18.
 * The channel count is stored at 0x4eb0b4
 * (sound_manager_globals.channel_count). Asserts that channel_index is in range
 * [0, channel_count). */
void *sound_channel_get(short channel_index /* @<si> */)
{
  assert_halt(channel_index >= 0 && channel_index < *(short *)0x4eb0b4);

  return (void *)(0x4fc3a0 + (int)channel_index * 0x18);
}

/* Return a pointer to the sound listener entry for a local player.
 * The listeners table lives at 0x4eaf58 with a stride of 0x44.
 * Asserts that listener_index is in [0, MAXIMUM_NUMBER_OF_LOCAL_PLAYERS). */
void *sound_listener_get(short listener_index /* @<si> */)
{
  short index = listener_index;

  assert_halt(index >= 0 && index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

  return (void *)(0x4eaf58 + (int)index * 0x44);
}

/* Check whether a sound should be promoted to its promotion sound.
 *
 * sound_tag_index is passed in EAX (register argument).
 *
 * Loads the sound tag and checks if it has a promotion count (tag+0x80).
 * If so, updates the promotion accumulator (tag+0x88) based on the time
 * elapsed since the last check (tag+0x8c vs global timestamp 0x4eaf4c).
 * Clamps the accumulator to zero if negative, then adds the promotion
 * interval (tag+0x84). If the accumulator exceeds
 * promotion_count * promotion_interval, either:
 *   - Returns 1 (promote) if a promotion sound tag is set (tag+0x7c != -1),
 *     resetting the accumulator to zero.
 *   - Returns 2 (reject) if no promotion sound, subtracting the interval.
 * Returns 0 if no promotion is needed. */
int16_t sound_check_promotion(int sound_tag_index /* @<eax> */)
{
  char *sound_tag;
  short promotion_count;
  int delta;
  int accumulator;
  int interval;
  int total;

  sound_tag = (char *)tag_get(0x736e6421, sound_tag_index);
  promotion_count = *(short *)(sound_tag + 0x80);
  if (promotion_count == 0)
    return 0;

  /* Update accumulator: add elapsed time delta. */
  delta = *(int *)(sound_tag + 0x8c) - *(int *)0x4eaf4c;
  accumulator = *(int *)(sound_tag + 0x88) + delta;
  *(int *)(sound_tag + 0x88) = accumulator;

  /* Clamp negative accumulator to zero. */
  if (accumulator < 0)
    accumulator = 0;
  *(int *)(sound_tag + 0x88) = accumulator;

  /* Record current timestamp. */
  *(int *)(sound_tag + 0x8c) = *(int *)0x4eaf4c;

  /* Add promotion interval. */
  interval = *(int *)(sound_tag + 0x84);
  total = accumulator + interval;
  *(int *)(sound_tag + 0x88) = total;

  /* Check if accumulated time exceeds promotion threshold. */
  if (total > (int)promotion_count * interval) {
    if (*(int *)(sound_tag + 0x7c) != -1) {
      *(int *)(sound_tag + 0x88) = 0;
      return 1;
    }
    *(int *)(sound_tag + 0x88) = total - interval;
    return 2;
  }

  return 0;
}

/* sound_collect_like_sounds (0x1cbd30)
 *
 * Build a summary of channels currently playing sounds that are "like" the
 * given sound_handle, for instance-limiting purposes.
 *
 * The summary buffer (0x48 bytes, passed via ESI) is laid out as:
 *   0x00  like_definition_count      (short) — channels with same tag_index
 *   0x02  like_definition_channels[16] (short[16]) — their channel indices
 *   0x22  maximum_instance_count     (short) — from the sound class definition
 *   0x24  like_source_count          (short) — channels with same tag AND
 * source 0x26  like_source_channels[16]   (short[16]) — their channel indices
 *   0x46  maximum_source_instance_count (short) — from the sound class
 * definition
 *
 * Iterates all active channels.  For each channel that holds a different
 * sound_handle, checks sound_valid_for_channel and whether the tag_index
 * matches.  Matching channels are added to the definition list; if the
 * source field (+0x0c) also matches, they are added to the source list. */
void sound_collect_like_sounds(int sound_handle, void *summary /* @<esi> */)
{
  char *sound_entry;
  char *sound_tag;
  char *class_def;
  short channel_index;
  int *channel_base;
  int other_handle;
  char *other_entry;
  short like_def_count;
  short like_src_count;

  sound_entry = (char *)datum_get(*(data_t **)0x4fdba4, sound_handle);
  sound_tag = (char *)tag_get(0x736e6421, *(int *)(sound_entry + 0x8));

  /* Initialize counts to zero. */
  *(short *)((char *)summary + 0x00) = 0;
  *(short *)((char *)summary + 0x24) = 0;

  /* Read max instance counts from the sound class definition. */
  class_def =
    (char *)sound_class_get_definition(*(unsigned short *)(sound_tag + 0x4));
  *(short *)((char *)summary + 0x22) = *(short *)(class_def + 0x0);

  class_def =
    (char *)sound_class_get_definition(*(unsigned short *)(sound_tag + 0x4));
  *(short *)((char *)summary + 0x46) = *(short *)(class_def + 0x2);

  if (*(short *)((char *)summary + 0x46) > 0x10) {
    display_assert("summary->maximum_source_instance_count<=MAXIMUM_SOUND_"
                   "INSTANCES_PER_DEFINITION",
                   "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x6a4, 1);
    system_exit(-1);
  }

  if (*(short *)((char *)summary + 0x22) > 0x10) {
    display_assert("summary->maximum_instance_count<=MAXIMUM_SOUND_INSTANCES_"
                   "PER_OBJECT_PER_DEFINITION",
                   "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x6a5, 1);
    system_exit(-1);
  }

  if (*(short *)0x4eb0b4 <= 0)
    return;
  for (channel_index = 0; channel_index < *(short *)0x4eb0b4; channel_index++) {
    if (channel_index < 0 || channel_index >= *(short *)0x4eb0b4) {
      display_assert("index>=0 && index<sound_manager_globals.channel_count",
                     "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x428, 1);
      system_exit(-1);
    }

    channel_base = (int *)(0x4fc3a0 + (int)channel_index * 0x18);
    other_handle = channel_base[0];

    if (other_handle == -1 || other_handle == sound_handle)
      continue;

    other_entry = (char *)datum_get(*(data_t **)0x4fdba4, other_handle);

    if (!sound_valid_for_channel(
          *(short *)(sound_tag + 0x6e), *(unsigned short *)(sound_tag + 0x6c),
          *(unsigned short *)(sound_tag + 0x6),
          *(unsigned short *)(sound_entry + 0x14),
          *(unsigned short *)((char *)channel_base + 0x4)))
      continue;

    if (*(int *)(sound_entry + 0x8) != *(int *)(other_entry + 0x8))
      continue;

    /* Same definition — add to like-definition list. */
    like_def_count = *(short *)((char *)summary + 0x00);
    if (like_def_count >= *(short *)((char *)summary + 0x22)) {
      display_assert(
        "summary->like_definition_count<summary->maximum_instance_count",
        "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x6b5, 1);
      system_exit(-1);
    }
    *(short *)((char *)summary + 0x02 + like_def_count * 2) = channel_index;
    *(short *)((char *)summary + 0x00) += 1;

    /* Same source — also add to like-source list. */
    if (*(int *)(sound_entry + 0xc) == -1)
      continue;
    if (*(int *)(sound_entry + 0xc) != *(int *)(other_entry + 0xc))
      continue;

    like_src_count = *(short *)((char *)summary + 0x24);
    if (like_src_count >= *(short *)((char *)summary + 0x46)) {
      display_assert(
        "summary->like_source_count<summary->maximum_source_instance_count",
        "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x6bb, 1);
      system_exit(-1);
    }
    *(short *)((char *)summary + 0x26 + like_src_count * 2) = channel_index;
    *(short *)((char *)summary + 0x24) += 1;
  }
}

/* sound_channel_start_new (0x1cbf30)
 *
 * Start a new permutation on a sound channel.  If the channel already has
 * a current permutation at offset +0x14, release it via
 * sound_cache_sound_finished.  Then call the sound driver's start entry
 * (vtable offset 0x18) to begin playback.
 *
 * If the channel already has a queued permutation at +0x10, the new
 * permutation is stored at +0x14 (next slot).  Otherwise it becomes the
 * current permutation at +0x10, and the time accumulator at +0x08 is
 * reset to zero.
 *
 * Register args: DI = channel_index, EBX = permutation.
 */
void sound_channel_start_new(short channel_index, int permutation)
{
  int ch;
  int *channel_base;

  if (channel_index < 0 || channel_index >= *(short *)0x4eb0b4) {
    display_assert("index>=0 && index<sound_manager_globals.channel_count",
                   "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x428, 1);
    system_exit(-1);
  }

  ch = (int)channel_index;
  channel_base = (int *)(0x4fc3a0 + ch * 0x18);

  /* Release any existing permutation at +0x14. */
  if (channel_base[5]) {
    sound_cache_sound_finished(channel_base[5]);
  }

  /* Call sound driver start (vtable +0x18). */
  (*(void (**)(int, int))(*(int *)0x4eaf48 + 0x18))(channel_index, permutation);

  if (channel_base[4]) {
    /* Already have a current permutation — queue as next. */
    channel_base[5] = permutation;
  } else {
    /* No current permutation — set as current and reset time. */
    channel_base[4] = permutation;
    channel_base[2] = 0;
  }
}

/* sound_channel_set_properties (0x1cbfb0)
 *
 * Push volume/pitch/3D properties to the sound driver for a channel.
 * When update_only is zero, the channel's pitch rate (offset +0x0c in the
 * channel table at 0x4fc3a0) is also written from properties+0x08 before
 * calling the driver.  When update_only is non-zero the pitch store is
 * skipped and only the driver vtable call is made.
 *
 * Register args: SI = channel_index, EBX = update_only.
 * Stack arg:     properties pointer.
 */
void sound_channel_set_properties(short channel_index, int update_only,
                                  void *properties)
{
  int ch;

  if (channel_index < 0 || channel_index >= *(short *)0x4eb0b4) {
    display_assert("index>=0 && index<sound_manager_globals.channel_count",
                   "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x428, 1);
    system_exit(-1);
  }

  ch = (int)channel_index;

  if (!update_only) {
    if (*(float *)((char *)properties + 8) <= 0.0f) {
      display_assert("properties->pitch>0.f",
                     "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x848, 1);
      system_exit(-1);
    }
    *(int *)(0x4fc3a0 + ch * 0x18 + 0x0c) = *(int *)((char *)properties + 8);
  }

  /* Call the sound driver's set-properties entry (vtable offset 0x34). */
  (*(void (**)(int, void *, int))(*(int *)0x4eaf48 + 0x34))(
    channel_index, properties, update_only);
}

/* sound_channel_update_status (0x1cc050)
 *
 * Query the sound driver for playback status of the given channel and
 * advance the channel's permutation queue accordingly.
 *
 * The channel struct lives in the channel table at 0x4fc3a0 (stride 0x18):
 *   +0x08  float  time accumulator
 *   +0x0c  float  time rate
 *   +0x10  int    current permutation pointer
 *   +0x14  int    queued permutation pointer
 *
 * Driver vtable+0x24 returns the playback status for a channel:
 *   0 = stopped, 1 = playing, 2 = finished.
 *
 * If a queued permutation exists and status < 2 (still playing or stopped):
 *   - Release the old current permutation via sound_cache_sound_finished.
 *   - Promote the queued permutation to current and clear the queue.
 *   - Reset the time accumulator.
 *   - Request the new permutation via sound_cache_request_sound; if that
 *     fails, override the status to 0.
 *
 * If no queue but current permutation exists and status < 1 (stopped):
 *   - Assert no queued permutation remains.
 *   - Release current permutation via sound_cache_sound_finished and clear it.
 *
 * Finally, accumulate time: accumulator += delta_time * rate.
 *
 * channel_index is passed in AX (register arg, thunked to stack).
 * Returns the driver playback status as a short. */
short sound_channel_update_status(short channel_index)
{
  int ch;
  int *channel_base;
  short status;
  int queued_perm;

  /* Validate channel_index. */
  if (channel_index < 0 || channel_index >= *(short *)0x4eb0b4) {
    display_assert("index>=0 && index<sound_manager_globals.channel_count",
                   "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x428, 1);
    system_exit(-1);
  }

  ch = (int)channel_index;
  channel_base = (int *)(0x4fc3a0 + ch * 0x18);

  /* Query the sound driver for playback status (vtable+0x24). */
  status = (short)(*(int (**)(int))(*(int *)0x4eaf48 + 0x24))(channel_index);

  /* If a queued permutation is pending and channel hasn't finished, promote it.
   */
  if (channel_base[5] != 0 && status < 2) {
    sound_cache_sound_finished(channel_base[4]);
    queued_perm = channel_base[5];
    channel_base[4] = queued_perm;
    channel_base[5] = 0;
    channel_base[2] = 0;
    if (!sound_cache_request_sound((void *)queued_perm, 0, 0, 0)) {
      status = 0;
    }
  }

  /* If current permutation exists but channel is stopped, release it. */
  if (channel_base[4] != 0 && status < 1) {
    if (channel_base[5] != 0) {
      display_assert("!channel->queued_permutation",
                     "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x868, 1);
      system_exit(-1);
    }
    sound_cache_sound_finished(channel_base[4]);
    channel_base[4] = 0;
  }

  /* Accumulate time: accumulator += delta_time * rate. */
  *(float *)&channel_base[2] += *(float *)0x4eaf50 * *(float *)&channel_base[3];

  return status;
}

/* sound_channel_stop (0x1cc140)
 *
 * Release cache-sound references for a channel and stop the hardware
 * via the sound driver vtable+0x20.
 *
 * The channel struct lives in the channel table at 0x4fc3a0 (stride 0x18).
 * Two permutation pointers at offsets +0x10 and +0x14 in the channel
 * entry are checked: if non-zero, sound_cache_sound_finished is called
 * to decrement the software reference count and the pointer is cleared.
 * Finally, the sound driver's stop function (vtable+0x20) is called
 * with the channel index.
 *
 * channel_index is passed in DI (register arg, thunked to stack). */
void sound_channel_stop(short channel_index)
{
  int ch;
  int *channel_base;

  /* Validate channel_index. */
  if (channel_index < 0 || channel_index >= *(short *)0x4eb0b4) {
    display_assert("index>=0 && index<sound_manager_globals.channel_count",
                   "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x428, 1);
    system_exit(-1);
  }

  ch = (int)channel_index;
  channel_base = (int *)(0x4fc3a0 + ch * 0x18);

  /* Release cache-sound ref at +0x14 if present. */
  if (channel_base[5] != 0) {
    sound_cache_sound_finished(channel_base[5]);
    channel_base[5] = 0;
  }

  /* Release cache-sound ref at +0x10 if present. */
  if (channel_base[4] != 0) {
    sound_cache_sound_finished(channel_base[4]);
    channel_base[4] = 0;
  }

  /* Stop the hardware channel via driver vtable+0x20. */
  (*(void (**)(int))(*(int *)0x4eaf48 + 0x20))(channel_index);
}

/* sound_update_channel_attenuation (0x1cc310)
 *
 * Advance the attenuation envelope for a sound datum. Computes the
 * interpolation parameter t from the transition start/end tick fields
 * (+0xa4, +0xa8) relative to the global sound timestamp at 0x4eaf4c.
 *
 * Three envelope shapes are selected by the short at +0x92:
 *   0 (linear): t is used directly.
 *   1 (power):  t is warped through pow(t, 1/2.5) or 1-pow(1-t, 1/2.5)
 *               depending on whether target > current attenuation.
 *   default:    assert -- invalid envelope type.
 *
 * When t reaches 1.0 the transition start/end fields are cleared.
 * Returns lerp(current_atten, target_atten, shaped_t).
 * If no transition is active (start == end), returns 1.0 (fully audible). */
float sound_update_channel_attenuation(int sound_handle)
{
  char *sound_entry;
  int start_tick;
  int end_tick;
  float t;

  sound_entry = (char *)datum_get(*(data_t **)0x4fdba4, sound_handle);
  start_tick = *(int *)(sound_entry + 0xa4);
  end_tick = *(int *)(sound_entry + 0xa8);

  if (start_tick == end_tick) {
    return 1.0f;
  }

  /* Compute t = (current_tick - start) / (end - start), clamped to [0, 1]. */
  t = (float)(*(int *)0x4eaf4c - start_tick) / (float)(end_tick - start_tick);
  if (t < 0.0f) {
    t = 0.0f;
  } else if (t > 1.0f) {
    t = 1.0f;
  }

  /* Apply envelope shape based on type at +0x92. */
  switch (*(short *)(sound_entry + 0x92)) {
  case 0:
    /* Linear: use t directly. */
    break;
  case 1:
    /* Power curve: ease-in or ease-out depending on direction. */
    if (*(float *)(sound_entry + 0xa0) > *(float *)(sound_entry + 0x9c)) {
      t = (float)pow((double)t, (double)(1.0f / 2.5f));
    } else {
      t = (float)(1.0 - pow((double)(1.0f - t), (double)(1.0f / 2.5f)));
    }
    break;
  default:
    display_assert(0, "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0xa76, 1);
    system_exit(-1);
    break;
  }

  /* When t reaches 1.0, clear the transition. */
  if (t == 1.0f) {
    *(int *)(sound_entry + 0xa8) = 0;
    *(int *)(sound_entry + 0xa4) = 0;
  }

  /* Lerp between current and target attenuation. */
  return (*(float *)(sound_entry + 0xa0) - *(float *)(sound_entry + 0x9c)) * t +
         *(float *)(sound_entry + 0x9c);
}

/* sound_volume_crossfade (0x1cc490)
 *
 * Step a volume level toward a target value using a multiplicative rate.
 * If rate is zero or current already equals target, returns current unchanged.
 *
 * When fading down (current > target): computes target * rate and returns
 * that if it is still below current (making progress), otherwise clamps to
 * current to avoid overshoot.
 *
 * When fading up (current <= target): computes target / rate and returns
 * that if it is still above current (making progress), otherwise clamps to
 * current to avoid overshoot. */
float sound_volume_crossfade(float current, float target, float rate)
{
  if (rate == 0.0f || current == target)
    return current;

  if (current > target) {
    /* Fading down: multiply target by rate. */
    float result = target * rate;
    if (current > result)
      return result;
    return current;
  } else {
    /* Fading up: divide target by rate. */
    float result = target / rate;
    if (current <= result)
      return result;
    return current;
  }
}

/* sound_compute_random_scale (0x1cc8c0)
 *
 * Compute a randomised scale factor for a sound parameter.
 * Gets a deterministic random float in [random_min, random_max] from the
 * local random seed, then evaluates:
 *   result = random_value * (bend_min + (bend_max - bend_min) * source_scale)
 *
 * Confirmed: 5 cdecl args, all floats.
 * Confirmed: CALL 0x10b120 (random_math_get_local_seed_address).
 * Confirmed: CALL 0x10b270 (random_real_range) with (seed, random_min,
 * random_max). Confirmed: FPU arithmetic: (bend_max - bend_min) * source_scale
 * + bend_min, then multiplied by the random_real_range result. Confirmed:
 * returns float on FPU stack.
 */
float sound_compute_random_scale(float random_min, float random_max,
                                 float bend_min, float bend_max,
                                 float source_scale)
{
  unsigned int *seed;
  float random_value;

  seed = random_math_get_local_seed_address();
  random_value = random_real_range((int *)seed, random_min, random_max);
  return random_value * ((bend_max - bend_min) * source_scale + bend_min);
}

/* sound_start_fade (0x1cc8f0)
 *
 * Begin a timed linear or crossfade between two sound entries. Mode must be
 * either _sound_fade_mode_linear (0) or _sound_fade_mode_crossfade (1).
 *
 * Computes a fade window [start_tick, end_tick] based on the global sound
 * timestamp at 0x4eaf4c. start_tick is timestamp-1, and end_tick is derived
 * from seconds*1000 + start_tick, clamped to at least the current timestamp.
 *
 * For fade_in_sound_index: sets target volume to 1.0 and computes current
 * attenuation; if already at the endpoint, sets current volume to 0.
 * For fade_out_sound_index: sets target volume to 0.0 and computes current
 * attenuation.
 *
 * Sound entry fields written:
 *   +0x92 (short) = fade mode
 *   +0x9c (float) = current fade volume
 *   +0xa0 (float) = target fade volume
 *   +0xa4 (int)   = fade start tick
 *   +0xa8 (int)   = fade end tick */
void sound_start_fade(short mode, float seconds, int fade_in_sound_index,
                      int fade_out_sound_index)
{
  int sound_timestamp;
  int start_tick;
  int end_tick;
  char *sound_entry;

  if (mode != 0 && mode != 1) {
    display_assert(
      "mode==_sound_fade_mode_linear || mode==_sound_fade_mode_crossfade",
      "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x43f, 1);
    system_exit(-1);
  }
  if (seconds < *(float *)0x2533c0) {
    display_assert("seconds>=0.f", "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                   0x440, 1);
    system_exit(-1);
  }
  if (fade_in_sound_index == -1 && fade_out_sound_index == -1) {
    display_assert("fade_in_sound_index!=NONE || fade_out_sound_index!=NONE",
                   "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x441, 1);
    system_exit(-1);
  }

  sound_timestamp = *(int *)0x4eaf4c;
  start_tick = sound_timestamp - 1;
  end_tick = (int)(seconds * *(float *)0x254cb8 + (float)start_tick);
  if (end_tick <= sound_timestamp) {
    end_tick = sound_timestamp;
  }

  if (fade_in_sound_index != -1) {
    sound_entry = (char *)datum_get(*(data_t **)0x4fdba4, fade_in_sound_index);
    if (*(int *)(sound_entry + 0xa4) == *(int *)(sound_entry + 0xa8)) {
      *(float *)(sound_entry + 0x9c) = 0.0f;
    } else {
      *(float *)(sound_entry + 0x9c) =
        sound_update_channel_attenuation(fade_in_sound_index);
    }
    *(float *)(sound_entry + 0xa0) = 1.0f;
    *(short *)(sound_entry + 0x92) = mode;
    *(int *)(sound_entry + 0xa4) = start_tick;
    *(int *)(sound_entry + 0xa8) = end_tick;
  }

  if (fade_out_sound_index != -1) {
    sound_entry = (char *)datum_get(*(data_t **)0x4fdba4, fade_out_sound_index);
    *(float *)(sound_entry + 0x9c) =
      sound_update_channel_attenuation(fade_out_sound_index);
    *(float *)(sound_entry + 0xa0) = 0.0f;
    *(short *)(sound_entry + 0x92) = mode;
    *(int *)(sound_entry + 0xa4) = start_tick;
    *(int *)(sound_entry + 0xa8) = end_tick;
  }
}

/* sound_stop_channel (0x1cca60)
 *
 * Stop and release the channel currently holding a sound, then delete the
 * sound datum. sound_handle is passed in EBX (register argument).
 *
 * If the sound has a playing channel (playing_channel_index != NONE at +0x8c):
 *   1. Clear the channel's sound_handle to NONE (-1) in the channel table
 *      at 0x4fc3a0 (stride 0x18).
 *   2. Call sound_channel_stop (0x1cc140, @<di>) to release cache-sound
 *      references and stop the hardware channel.
 *   3. Clear the sound's playing_channel_index to NONE.
 *
 * If the sound has no playing channel but has flags bit 1 set (+0x4 & 2):
 *   Navigate the sound tag's pitch_range -> permutation hierarchy and call
 *   sound_cache_sound_finished (0x1be090) to decrement the cache refcount.
 *
 * If the sound's type (+0x2) is non-zero (looping sound):
 *   Look up the looping-sound datum via datum_absolute_index_to_index
 *   on the looping-sounds table (0x4fdba0). If found, decrement
 *   playing_count (+0x50) and clear the track entry at
 *   +0xd4 + track_index*4 if it matches sound_handle.
 *
 * Clear the sound tag's last-played field (+0x94) if it matches sound_handle.
 * Assert that the sound's playing_channel_index is NONE after processing.
 * Finally, delete the sound datum from the sounds table (0x4fdba4). */
void sound_stop_channel(int sound_handle /* @<ebx> */)
{
  char *sound_entry;
  void *tag_ptr;
  short playing_channel_index;

  sound_entry = (char *)datum_get(*(data_t **)0x4fdba4, sound_handle);
  tag_ptr = tag_get(0x736e6421, *(int *)(sound_entry + 0x8));

  playing_channel_index = *(short *)(sound_entry + 0x8c);

  if (playing_channel_index == -1) {
    /* No active channel -- release cache sound if flags bit 1 set. */
    if ((*(uint8_t *)(sound_entry + 0x4) & 2) != 0) {
      void *pitch_range;
      void *permutation;

      pitch_range = tag_block_get_element(
        (char *)tag_get(0x736e6421, *(int *)(sound_entry + 0x8)) + 0x98,
        (int)*(short *)(sound_entry + 0x8e), 0x48);
      permutation = tag_block_get_element(
        (char *)pitch_range + 0x3c, (int)*(short *)(sound_entry + 0x90), 0x7c);
      sound_cache_sound_finished((int)permutation);
    }
  } else {
    /* Active channel -- stop it. */
    assert_halt(playing_channel_index >= 0 &&
                playing_channel_index < *(short *)0x4eb0b4);

    /* Clear the channel's sound_handle to NONE. */
    *(int *)(0x4fc3a0 + (int)playing_channel_index * 0x18) = -1;

    /* Release cache sounds and stop hardware for this channel.
     * Re-read playing_channel_index into DI for the register-arg callee. */
    sound_channel_stop(*(short *)(sound_entry + 0x8c));

    /* Clear the sound's playing_channel_index. */
    *(short *)(sound_entry + 0x8c) = -1;
  }

  /* If this is a looping sound (type != 0), update the looping-sound entry. */
  if (*(short *)(sound_entry + 0x2) != 0) {
    int looping_sound = datum_absolute_index_to_index(
      *(data_t **)0x4fdba0, *(int *)(sound_entry + 0xc));

    if (looping_sound != 0) {
      char *ls = (char *)looping_sound;
      short track_index = *(short *)(sound_entry + 0x94);

      /* Decrement the looping sound's playing count. */
      (*(short *)(ls + 0x50))--;

      /* Clear the track entry if it matches our sound_handle. */
      if (*(int *)(ls + 0xd4 + track_index * 4) == sound_handle) {
        *(int *)(ls + 0xd4 + track_index * 4) = -1;
      }
    }
  }

  /* Clear the sound tag's last-played field if it matches our handle. */
  if (*(int *)((char *)tag_ptr + 0x94) == sound_handle) {
    *(int *)((char *)tag_ptr + 0x94) = -1;
  }

  /* Assert the sound's playing_channel_index is now NONE. */
  {
    char *verify = (char *)datum_get(*(data_t **)0x4fdba4, sound_handle);
    assert_halt(*(short *)(verify + 0x8c) == -1);
  }

  /* Delete the sound datum. */
  datum_delete(*(data_t **)0x4fdba4, sound_handle);
}

/* Sound manager — low-level sound system lifecycle and rendering. */

/* Compute listener distance squared for a channel/source pair. */
extern float FUN_001ccbe0(int channel_index, void *source);

/* Compute distance for random scale checks. */
extern float FUN_001ccca0(int channel_index, void *source);

/* sound_find_oldest_channel (0x1ccd70)
 *
 * Scan a list of candidate channel indices and return the first one whose
 * sound has been playing long enough (elapsed >= class threshold) and whose
 * listener distance is within 1.0 of our sound's distance.
 *
 * Resolves the caller's sound_handle to get a reference distance via
 * FUN_001ccbe0.  Then for each candidate channel, looks up the channel's
 * sound datum, checks that enough time has elapsed since it started
 * (sound_entry+0x84 vs global timer 0x4eaf4c), and compares distances.
 *
 * Returns the channel index of the best eviction candidate, or -1 if
 * none qualifies. */
short sound_find_oldest_channel(int sound_handle, short *channels, short count)
{
  char *sound_entry;
  char *sound_tag;
  float best_distance;
  short i;
  short index;
  char *other_entry;
  void *class_def;
  int elapsed;

  /* Resolve our sound datum and its tag. */
  sound_entry = (char *)datum_get(*(data_t **)0x4fdba4, sound_handle);
  sound_tag = (char *)tag_get(0x736e6421, *(int *)(sound_entry + 0x8));

  /* Compute reference distance for our sound. */
  best_distance =
    FUN_001ccbe0(*(short *)(sound_entry + 0x6), (void *)(sound_entry + 0x14));

  for (i = 0; i < count; i++) {
    index = channels[i];

    assert_halt(index >= 0 && index < *(short *)0x4eb0b4);

    /* Get the sound datum currently playing on this channel. */
    other_entry = (char *)datum_get(*(data_t **)0x4fdba4,
                                    *(int *)(0x4fc3a0 + (int)index * 0x18));

    /* Look up the sound class time threshold. */
    class_def =
      sound_class_get_definition(*(unsigned short *)(sound_tag + 0x4));

    /* Check elapsed time against class threshold. */
    elapsed = *(int *)0x4eaf4c - *(int *)(other_entry + 0x84);
    if (elapsed >= *(int *)((char *)class_def + 0x4)) {
      /* Check if the candidate's distance is within 1.0 of ours. */
      if (best_distance - FUN_001ccbe0(*(short *)(other_entry + 0x6),
                                       (void *)(other_entry + 0x14)) <
          1.0f) {
        return index;
      }
    }
  }

  return -1;
}

/* sound_update_channel (0x1ccf80)
 *
 * Apply volume/pan/pitch updates for a non-music sound channel.
 *
 * Resolves the sound datum and tag, then computes a composite volume
 * from the tag's gain range (tag+0x40..0x58), the sound_entry's
 * interpolation fraction (+0x18), per-entry gain (+0x1c), class gain
 * (sound_class_get_gain), and the incoming attenuation scalar.
 * Non-ambient classes (not 0x2c/0x2e/0x2f) additionally scale by
 * the global volume at 0x4eb0b0.
 *
 * If the sound's playing channel index (+0x8c) is NONE (-1), this is a
 * new channel: build a full properties struct (pitch, max_distance,
 * pan, volume, direction, class flags), assert the permutation is
 * cache-loaded, then push properties and start the new permutation via
 * sound_channel_set_properties and sound_channel_start_new.
 *
 * If the channel is already playing, compute volume from the existing
 * permutation's gain and push it directly to the sound driver via
 * vtable+0x34 (volume-only update, flag=1).
 *
 * Finally, call vtable+0x1c to commit the channel update. */
void sound_update_channel(int channel_index, float attenuation)
{
  short si = (short)channel_index;
  int *channel_ptr;
  char *sound_entry;
  char *tag_ptr;
  short class_index;
  float class_gain;
  float fraction;
  float volume;
  int pitch_range;
  int permutation;
  void *class_def;

  /* Properties struct: 0x20 bytes (8 floats).
   *   +0x00 float min_distance (pitch)
   *   +0x04 float max_distance
   *   +0x08 float pan
   *   +0x0C float gain/volume
   *   +0x10 float direction[3] (from tag+0x1c..0x24)
   *   +0x1C int   class_def_flags (class_def+0x10) */
  float properties[8];

  /* Validate channel_index. */
  if (si < 0 || si >= *(short *)0x4eb0b4) {
    display_assert("index>=0 && index<sound_manager_globals.channel_count",
                   "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x428, 1);
    system_exit(-1);
  }

  /* Resolve channel, sound entry, and tag. */
  channel_ptr = (int *)(0x4fc3a0 + (int)si * 0x18);
  sound_entry = (char *)datum_get(*(data_t **)0x4fdba4, *channel_ptr);
  tag_ptr = (char *)tag_get(0x736e6421, *(int *)(sound_entry + 0x8));

  /* Cache interpolation fraction from sound_entry+0x18. */
  fraction = *(float *)(sound_entry + 0x18);

  /* Get class gain. */
  class_index = *(short *)(tag_ptr + 0x4);
  class_gain = sound_class_get_gain((int)class_index);

  /* Non-ambient classes scale by global volume. */
  if (class_index != 0x2c && class_index != 0x2e && class_index != 0x2f) {
    class_gain = class_gain * *(float *)0x4eb0b0;
  }

  /* Compute composite volume:
   * lerp(tag+0x40, tag+0x58, fraction) * sound_entry+0x1c * class_gain *
   * attenuation */
  volume =
    (*(float *)(tag_ptr + 0x58) - *(float *)(tag_ptr + 0x40)) * fraction +
    *(float *)(tag_ptr + 0x40);
  volume = volume * *(float *)(sound_entry + 0x1c) * class_gain * attenuation;

  if (*(short *)(sound_entry + 0x8c) == -1) {
    /* New channel: build full properties and start permutation. */
    pitch_range = (int)tag_block_get_element(
      tag_ptr + 0x98, (int)*(short *)(sound_entry + 0x8e), 0x48);
    permutation = (int)tag_block_get_element(
      (char *)pitch_range + 0x3c, (int)*(short *)(sound_entry + 0x90), 0x7c);

    /* Volume: permutation+0x24 * tag+0x28 * composite volume. */
    properties[3] =
      *(float *)(permutation + 0x24) * *(float *)(tag_ptr + 0x28) * volume;

    /* Pan: sound_entry+0x88 * pitch_range+0x30. */
    properties[2] =
      *(float *)(sound_entry + 0x88) * *(float *)(pitch_range + 0x30);

    /* Pitch: min-distance from sound class. */
    properties[0] = sound_class_get_min_distance(*(int *)(sound_entry + 0x8));

    /* Direction from tag+0x1c..0x24. */
    *(int *)&properties[4] = *(int *)(tag_ptr + 0x1c);
    *(int *)&properties[5] = *(int *)(tag_ptr + 0x20);
    *(int *)&properties[6] = *(int *)(tag_ptr + 0x24);

    /* Max distance: FLT_MAX. */
    *(int *)&properties[1] = 0x7f7fffff;

    /* Class definition flags. */
    class_def = sound_class_get_definition(class_index);
    *(int *)&properties[7] = *(int *)((char *)class_def + 0x10);

    /* Assert permutation is cache-loaded. */
    if (!sound_cache_request_sound((void *)permutation, 0, 0, 0)) {
      display_assert("sound_cache_sound_loaded(permutation)",
                     "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x79a, 1);
      system_exit(-1);
    }

    /* Push properties and start the new permutation.
     * sound_channel_set_properties: SI=channel_index, EBX=0 (full update).
     * sound_channel_start_new: DI=channel_index, EBX=permutation. */
    sound_channel_set_properties(si, 0, properties);
    sound_channel_start_new(si, permutation);

    /* Record this channel as playing in the sound entry. */
    *(short *)(sound_entry + 0x8c) = si;
  } else {
    /* Existing channel: update volume from current permutation. */
    properties[3] = *(float *)(*(int *)((char *)channel_ptr + 0x10) + 0x24) *
                    *(float *)(tag_ptr + 0x28) * volume;

    /* Validate channel_index again (matches original). */
    if (si < 0 || si >= *(short *)0x4eb0b4) {
      display_assert("index>=0 && index<sound_manager_globals.channel_count",
                     "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x428, 1);
      system_exit(-1);
    }

    /* Push volume-only update (flag=1) directly through the sound driver. */
    (*(void (**)(int, void *, int))(*(int *)0x4eaf48 + 0x34))(channel_index,
                                                              properties, 1);
  }

  /* Commit the channel update. */
  (*(void (**)(int))(*(int *)0x4eaf48 + 0x1c))(channel_index);
}

/* sound_start_next_looping_permutation (0x1cd2c0)
 *
 * Advance a looping sound to its next permutation. Called when the current
 * permutation finishes and the next_sound chain is exhausted (+0x98 == -1).
 *
 * Phase 1 — set up the new permutation:
 *   Resolves the sound datum and its tag (snd!).  Sets the "next ready"
 *   flag (flags |= 8).  Saves the current looping_sound_tag_index to the
 *   sound's tag_index field (+0x8) and clears it (+0x98 = -1).  Selects a
 *   new pitch range via sound_select_pitch_range using the random_scale
 *   (+0x88) and hint pitch range index (+0x8e), then selects a permutation
 *   within that range via sound_select_permutation (hint = -1).  Stores the
 *   new pitch_range_index (+0x8e) and permutation_index (+0x90).
 *
 * Phase 2 — instance limiting (only if playing_channel_index != -1):
 *   Collects a summary of similar sounds via sound_collect_like_sounds
 *   (0x1cbd30, @<esi>).  If the like_source_count has reached
 *   max_source_instance_count, searches the source channel list for the
 *   oldest to steal.  Otherwise, if the like_definition_count has reached
 *   max_instance_count, searches the definition channel list.  If a
 *   stealable channel is found, stops its sound; if not, stops our own.
 *
 * sound_handle passed in EAX (register argument). */
void sound_start_next_looping_permutation(int sound_handle /* @<eax> */)
{
  char *sound_entry;
  void *sound_tag;
  int looping_tag_index;
  float random_scale;
  int hint_index;
  short pitch_range_index;
  short permutation_index;
  char summary[0x48];
  short like_source_count;
  short max_source_instance_count;
  short like_definition_count;
  short max_instance_count;
  short *channels_ptr;
  short count_val;
  short oldest_channel;

  sound_entry = (char *)datum_get(*(data_t **)0x4fdba4, sound_handle);
  sound_tag = tag_get(0x736e6421, *(int *)(sound_entry + 0x98));

  *(uint8_t *)(sound_entry + 0x4) |= 8;

  looping_tag_index = *(int *)(sound_entry + 0x98);
  *(int *)(sound_entry + 0x8) = looping_tag_index;
  *(int *)(sound_entry + 0x98) = -1;

  random_scale = *(float *)(sound_entry + 0x88);
  hint_index = (int)(unsigned short)*(short *)(sound_entry + 0x8e);

  pitch_range_index =
    sound_select_pitch_range(sound_tag, random_scale, hint_index);
  *(short *)(sound_entry + 0x8e) = pitch_range_index;

  permutation_index =
    sound_select_permutation(sound_tag, pitch_range_index, -1);
  *(short *)(sound_entry + 0x90) = permutation_index;

  if (*(short *)(sound_entry + 0x8c) != -1) {
    sound_collect_like_sounds(sound_handle, summary);

    like_source_count = *(short *)(summary + 0x24);
    max_source_instance_count = *(short *)(summary + 0x46);
    like_definition_count = *(short *)(summary + 0x00);
    max_instance_count = *(short *)(summary + 0x22);

    if (like_source_count >= max_source_instance_count) {
      channels_ptr = (short *)(summary + 0x26);
      count_val = like_source_count;
    } else if (like_definition_count >= max_instance_count) {
      channels_ptr = (short *)(summary + 0x02);
      count_val = like_definition_count;
    } else {
      return;
    }

    oldest_channel =
      sound_find_oldest_channel(sound_handle, channels_ptr, count_val);

    if (oldest_channel != -1) {
      sound_handle = *(int *)sound_channel_get(oldest_channel);
    }

    sound_stop_channel(sound_handle);
  }
}

void sound_stop_impulse(int sound_index)
{
  void *sound;

  if (!datum_absolute_index_to_index(*(data_t **)0x4fdba4, sound_index))
    return;

  sound = datum_get(*(data_t **)0x4fdba4, sound_index);
  if (*(short *)((char *)sound + 2) != 0) {
    display_assert("sound_get(sound_index)->type==_sound_impulse",
                   "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x2c1, 1);
    system_exit(-1);
  }

  sound = datum_get(*(data_t **)0x4fdba4, sound_index);
  if (*(short *)((char *)sound + 2) == 0)
    sound_start_fade(0, 0.3f, -1, sound_index);
}

/* Allocate a sound channel for a source based on its spatialization mode.
 *
 * source is passed in EAX (register argument); priority is on the stack.
 *
 * Behavior depends on source->spatialization_mode (short at offset 0):
 *   - Mode 0 (none): returns channel 0 immediately.
 *   - Mode 2 (single listener): computes distance via 0x1ccbe0 with
 *     channel=-1 and the source pointer. If distance >= priority, returns
 *     the channel index; otherwise returns 0.
 *   - Other modes (1 = listener-relative): iterates over up to 4 local
 *     player listener slots (0x4eaf58 + i*0x44), computing distance for
 *     each active listener. Tracks the closest listener. If found, calls
 *     0x1c8310 to evaluate channel suitability. Returns the best channel
 *     index, or -1 if priority^2 < min distance or source[0x3c] == 1.0f.
 */
int16_t sound_allocate_channel(void *source /* @<eax> */, float priority)
{
  short spatialization_mode;
  int best_channel;
  float best_dist_sq;
  int i;
  char *listener_ptr;
  float sqrt_dist;

  spatialization_mode = *(short *)source;
  best_channel = -1;

  if (spatialization_mode == 0)
    return 0;

  if (spatialization_mode == 2) {
    /* Single listener: compute distance with channel=-1. */
    {
      float dist_result = FUN_001ccbe0(-1, source);
      if (dist_result >= priority)
        return (short)best_channel;
      return 0;
    }
  }

  /* Mode 1 / other: iterate over local player listeners. */
  best_dist_sq = 3.4028235e+38f; /* FLT_MAX (0x7f7fffff) */
  listener_ptr = (char *)0x4eaf58;

  for (i = 0; (short)i < 4; i++, listener_ptr += 0x44) {
    if ((short)i < 0 || (short)i >= 4) {
      display_assert("index>=0 && index<MAXIMUM_NUMBER_OF_LOCAL_PLAYERS",
                     "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x430, 1);
      system_exit(-1);
    }
    if (*listener_ptr != '\0') {
      /* Compute distance squared for this listener. */
      float this_dist = FUN_001ccbe0(i, source);
      if (this_dist < best_dist_sq) {
        best_dist_sq = this_dist;
        best_channel = i;
      }
    }
  }

  if ((short)best_channel != -1) {
    /* Evaluate channel suitability with sqrt of best distance. */
    sqrt_dist = xbox_sqrtf(best_dist_sq);
    sound_compute_source_obstruction(best_channel, source, sqrt_dist);
  }

  if (priority * priority < best_dist_sq)
    return -1;
  if (*(int *)((char *)source + 0x3c) == 0x3f800000)
    return -1;

  return (short)best_channel;
}

/* sound_create_looping_entry (0x1cda50)
 *
 * Create a new sound entry for a looping sound track. This is the main
 * constructor for looping sound playback: it checks playability, allocates
 * a channel and sound datum, initializes the datum with tag data, selects
 * an initial pitch range and permutation, and requests the sound to be
 * cached.
 *
 * Parameters:
 *   sound_tag_handle  (@<eax>) — tag index of the sound definition (snd!)
 *   looping_handle    — datum handle of the parent looping sound source
 *   track_index       — which track within the looping sound (16-bit)
 *   type              — sound entry type/class (16-bit)
 *
 * Returns:  datum handle of the new sound entry, or -1 on failure.
 *
 * Flow:
 *   1. Resolve the looping sound source and extract its gain field (+0x10).
 *   2. Check if the sound can play (sound_can_play). If not, return -1.
 *   3. Resolve the snd! tag and compute a default priority.
 *   4. Allocate a channel via sound_allocate_channel. If -1, return -1.
 *   5. Allocate a new sound datum via data_new_at_index. If -1, return -1.
 *   6. Initialize the sound datum fields: channel, tag handle, looping
 *      handle, type, track index, timestamp, update callback, and copy
 *      64 bytes of source data from the looping sound.
 *   7. Compute random gain via random_real_range on the tag's gain bounds.
 *   8. Select pitch range and permutation from the tag.
 *   9. Resolve the permutation's tag block element and request sound cache.
 *  10. Increment the looping sound source's reference count (+0x50). */
int sound_create_looping_entry(int sound_tag_handle /* @<eax> */,
                               int looping_handle, int track_index, int type)
{
  char *looping_source;
  float source_gain;
  void *sound_tag;
  float priority;
  int16_t channel_index;
  int new_handle;
  char *sound_entry;
  float random_gain;
  short pitch_range_index;
  short permutation_index;
  void *pitch_range_element;
  void *permutation_element;

  looping_source = (char *)datum_get(*(data_t **)0x4fdba0, looping_handle);
  source_gain = *(float *)(looping_source + 0x10);

  if (!sound_can_play(sound_tag_handle)) {
    return -1;
  }

  sound_tag = tag_get(0x736e6421, sound_tag_handle);
  priority = sound_get_default_priority(sound_tag_handle);

  channel_index = sound_allocate_channel(looping_source + 0xc, priority);
  if (channel_index == -1) {
    return -1;
  }

  new_handle = data_new_at_index(*(data_t **)0x4fdba4);
  if (new_handle == -1) {
    return new_handle;
  }

  sound_entry = (char *)datum_get(*(data_t **)0x4fdba4, new_handle);

  *(short *)(sound_entry + 0x6) = channel_index;
  *(int *)(sound_entry + 0x8) = sound_tag_handle;
  *(short *)(sound_entry + 0x8c) = -1;
  *(short *)(sound_entry + 0x4) = 0;

  random_gain = random_real_range((int *)random_math_get_local_seed_address(),
                                  *(float *)((char *)sound_tag + 0x14),
                                  *(float *)((char *)sound_tag + 0x18));

  *(float *)(sound_entry + 0x88) = random_gain;
  *(int *)(sound_entry + 0xc) = looping_handle;

  {
    unsigned int *dst = (unsigned int *)(sound_entry + 0x14);
    unsigned int *src = (unsigned int *)(looping_source + 0xc);
    int i;
    for (i = 0x10; i != 0; i--) {
      *dst = *src;
      dst++;
      src++;
    }
  }

  *(short *)(sound_entry + 0x2) = (short)type;
  *(unsigned int *)(sound_entry + 0x84) = *(unsigned int *)0x4eaf4c;
  *(short *)(sound_entry + 0x94) = (short)track_index;
  *(unsigned int *)(sound_entry + 0x10) = 0x1cc1c0;
  *(int *)(sound_entry + 0xa8) = 0;
  *(int *)(sound_entry + 0xa4) = 0;
  *(int *)(sound_entry + 0x98) = -1;

  pitch_range_index =
    sound_select_pitch_range(sound_tag,
                             ((*(float *)((char *)sound_tag + 0x5c) -
                               *(float *)((char *)sound_tag + 0x44)) *
                                source_gain +
                              *(float *)((char *)sound_tag + 0x44)) *
                               random_gain,
                             -1);

  *(short *)(sound_entry + 0x8e) = pitch_range_index;

  permutation_index =
    sound_select_permutation(sound_tag, pitch_range_index, -1);

  *(short *)(sound_entry + 0x90) = permutation_index;

  pitch_range_element = tag_block_get_element(
    (char *)tag_get(0x736e6421, *(int *)(sound_entry + 0x8)) + 0x98,
    (int)*(short *)(sound_entry + 0x8e), 0x48);

  permutation_element = tag_block_get_element(
    (char *)pitch_range_element + 0x3c, (int)permutation_index, 0x7c);

  sound_cache_request_sound(permutation_element, 0, 1, 0);

  *(short *)(looping_source + 0x50) += 1;

  return new_handle;
}

/* sound_update_music_channel (0x1cdc30)
 *
 * Apply volume/pan/pitch updates for a music-class (looping) channel.
 *
 * Resolves the sound datum, its tag (snd!), and the parent looping-sound
 * datum (lsnd).  Computes a composite volume from the tag's gain range
 * (tag+0x40..0x58), the looping-sound track gain (track+0x4), per-entry
 * gain (sound_entry+0x1c), class gain (sound_class_get_gain), the tag's
 * overall gain scalar (tag+0x28), and the incoming attenuation.
 * Non-ambient classes (not 0x2c/0x2e/0x2f) additionally scale by the
 * global volume at 0x4eb0b0.
 *
 * If the sound's playing channel index (+0x8c) is NONE (-1), this is a
 * new channel: build properties, assert the permutation is cache-loaded,
 * then push via sound_channel_set_properties and start_new.
 *
 * If already playing, advance the channel queue (sound_channel_update_status),
 * handle pitch-range crossfading, and manage permutation sequencing for
 * looped playback (select next permutation, handle linked-permutation
 * chains, and looping-sound iteration transitions).
 *
 * Finally, apply the permutation's gain scalar, push properties, and
 * commit the channel update via vtable+0x1c. */
void sound_update_music_channel(int channel_index, float attenuation)
{
  short si = (short)channel_index;
  int *channel_ptr;
  char *sound_entry;
  char *tag_ptr;
  char *looping_sound;
  int *track_channel_ptr;
  char *lsnd_tag;
  char *track_tag;
  short class_index;
  float class_gain;
  float fraction;
  float local_c; /* gain from tag gain range * sound_entry+0x88 */
  int pitch_range;
  int permutation;

  /* Properties struct: 0x20 bytes (8 floats).
   *   +0x00 float min_distance (pitch)
   *   +0x04 float max_distance
   *   +0x08 float pan (gain)
   *   +0x0C float volume
   *   +0x10 float direction[3] (from tag+0x1c..0x24)
   *   +0x1C int   class_def_flags (class_def+0x10) */
  float properties[8];

  /* Validate channel_index. */
  if (si < 0 || si >= *(short *)0x4eb0b4) {
    display_assert("index>=0 && index<sound_manager_globals.channel_count",
                   "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x428, 1);
    system_exit(-1);
  }

  /* Resolve channel, sound entry, tag, and looping-sound. */
  channel_ptr = (int *)(0x4fc3a0 + (int)si * 0x18);
  sound_entry = (char *)datum_get(*(data_t **)0x4fdba4, *channel_ptr);
  tag_ptr = (char *)tag_get(0x736e6421, *(int *)(sound_entry + 0x8));
  looping_sound =
    (char *)datum_get(*(data_t **)0x4fdba0, *(int *)(sound_entry + 0xc));
  track_channel_ptr =
    (int *)(looping_sound + 0xd4 + (int)*(short *)(sound_entry + 0x94) * 4);
  lsnd_tag = (char *)tag_get(0x6c736e64, *(int *)(looping_sound + 0x4));
  track_tag = (char *)tag_block_get_element(
    lsnd_tag + 0x3c, (int)*(short *)(sound_entry + 0x94), 0xa0);

  /* Cache interpolation fraction from sound_entry+0x18. */
  fraction = *(float *)(sound_entry + 0x18);

  /* Compute local_c: lerp(tag+0x44, tag+0x5c, fraction) * sound_entry+0x88. */
  local_c =
    ((*(float *)(tag_ptr + 0x5c) - *(float *)(tag_ptr + 0x44)) * fraction +
     *(float *)(tag_ptr + 0x44)) *
    *(float *)(sound_entry + 0x88);

  /* Assert this is not an impulse sound. */
  if (*(short *)(sound_entry + 2) == 0) {
    display_assert("sound->type!=_sound_impulse",
                   "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x9c4, 1);
    system_exit(-1);
  }

  /* Pitch: min-distance from sound class. */
  properties[0] = sound_class_get_min_distance(*(int *)(sound_entry + 0x8));

  /* Max distance: FLT_MAX. */
  *(int *)&properties[1] = 0x7f7fffff;

  /* Direction from tag+0x1c..0x24. */
  *(int *)&properties[4] = *(int *)(tag_ptr + 0x1c);
  *(int *)&properties[5] = *(int *)(tag_ptr + 0x20);
  *(int *)&properties[6] = *(int *)(tag_ptr + 0x24);

  /* Class definition flags. */
  {
    void *class_def =
      sound_class_get_definition(*(unsigned short *)(tag_ptr + 0x4));
    *(int *)&properties[7] = *(int *)((char *)class_def + 0x10);
  }

  /* Get class gain. */
  class_index = *(short *)(tag_ptr + 0x4);
  class_gain = sound_class_get_gain((int)(unsigned short)class_index);

  /* Non-ambient classes scale by global volume. */
  if (class_index != 0x2c && class_index != 0x2e && class_index != 0x2f) {
    class_gain = class_gain * *(float *)0x4eb0b0;
  }

  /* Compute composite volume:
   * lerp(tag+0x40, tag+0x58, fraction) * track+0x4 * tag+0x28 *
   * sound_entry+0x1c * class_gain * attenuation */
  properties[3] =
    (*(float *)(tag_ptr + 0x58) - *(float *)(tag_ptr + 0x40)) * fraction +
    *(float *)(tag_ptr + 0x40);
  properties[3] = properties[3] * *(float *)(track_tag + 0x4) *
                  *(float *)(tag_ptr + 0x28) * *(float *)(sound_entry + 0x1c) *
                  class_gain * attenuation;

  if (*(short *)(sound_entry + 0x8c) == -1) {
    /* New channel: build full properties and start permutation. */
    pitch_range = (int)tag_block_get_element(
      tag_ptr + 0x98, (int)*(short *)(sound_entry + 0x8e), 0x48);
    permutation = (int)tag_block_get_element(
      (char *)pitch_range + 0x3c, (int)*(short *)(sound_entry + 0x90), 0x7c);

    /* Volume: permutation+0x24 * existing volume. */
    properties[3] = properties[3] * *(float *)(permutation + 0x24);

    /* Pan: local_c * pitch_range+0x30. */
    properties[2] = local_c * *(float *)(pitch_range + 0x30);

    /* Assert permutation is cache-loaded. */
    if (!sound_cache_request_sound((void *)permutation, 0, 0, 0)) {
      display_assert("sound_cache_sound_loaded(permutation)",
                     "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x9da, 1);
      system_exit(-1);
    }

    /* Push properties and start the new permutation. */
    sound_channel_set_properties(si, 0, properties);
    sound_channel_start_new(si, permutation);

    /* Record this channel as playing in the sound entry. */
    *(short *)(sound_entry + 0x8c) = si;

    /* Commit the channel update. */
    (*(void (**)(int))(*(int *)0x4eaf48 + 0x1c))(channel_index);
    return;
  }

  /* Existing channel: resolve pitch range block. */
  pitch_range = (int)tag_block_get_element(
    tag_ptr + 0x98, (int)*(short *)(sound_entry + 0x8e), 0x48);

  /* Validate the existing playing channel index. */
  {
    short playing_channel = *(short *)(sound_entry + 0x8c);
    if (playing_channel < 0 || playing_channel >= *(short *)0x4eb0b4) {
      display_assert("index>=0 && index<sound_manager_globals.channel_count",
                     "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x428, 1);
      system_exit(-1);
    }
  }

  /* Volume crossfade toward target. */
  {
    short playing_channel = *(short *)(sound_entry + 0x8c);
    int playing_idx = (int)playing_channel;
    float channel_rate = *(float *)(0x4fc3ac + playing_idx * 0x18);
    local_c = sound_volume_crossfade(
      local_c, channel_rate * *(float *)(pitch_range + 0x20),
      *(float *)(tag_ptr + 0x2c));
  }

  /* Pan: local_c * pitch_range+0x30. */
  properties[2] = local_c * *(float *)(pitch_range + 0x30);

  /* Pitch-range crossfade: if the sound is in looping state and the
   * fade endpoints differ (or target attenuation not reached), try
   * selecting a new pitch range. If it changed, allocate a new looping
   * entry and start a crossfade. */
  if (*(short *)(sound_entry + 0x2) == 2 &&
      (*(int *)(sound_entry + 0xa4) == *(int *)(sound_entry + 0xa8) ||
       *(float *)(sound_entry + 0xa0) != *(float *)0x2533c0)) {
    short new_pitch_range = sound_select_pitch_range(
      tag_ptr, local_c, (int)(unsigned short)*(short *)(sound_entry + 0x8e));
    if (new_pitch_range != *(short *)(sound_entry + 0x8e)) {
      if (*channel_ptr == *track_channel_ptr && *(char *)0x4eaf43 == '\0') {
        int new_entry = sound_create_looping_entry(
          *(int *)(sound_entry + 0x8), *(int *)(sound_entry + 0xc),
          (int)(unsigned short)*(short *)(sound_entry + 0x94), 2);
        if (new_entry != -1) {
          sound_start_fade(1, *(float *)0x2c1278, new_entry, *channel_ptr);
          *track_channel_ptr = new_entry;
        }
      }
    }
  }

  /* Check if the sound should stop or continue. */
  if (*(short *)(sound_entry + 0x2) == 4)
    goto final_update;

  if (*(short *)(sound_entry + 0x2) == 1 && (*(uint8_t *)track_tag & 1) != 0)
    goto final_update;

  {
    short status = sound_channel_update_status(*(short *)(sound_entry + 0x8c));
    if (status == 2 && (*(uint8_t *)(sound_entry + 0x4) & 8) == 0) {
      /* Channel finished playing; check if permutation/next-sound chain
       * means we should skip to final update rather than queue more. */
      if (*(short *)(channel_ptr[4] + 0x2a) != -1)
        goto final_update;
      if (*(int *)(sound_entry + 0x98) == -1)
        goto final_update;
    }

    /* Permutation sequencing. */
    if (*(int *)(sound_entry + 0x98) == -1 ||
        (channel_ptr[4] != 0 && *(short *)(channel_ptr[4] + 0x2a) != -1)) {
      /* Next permutation ready or queued. */
      if ((*(uint8_t *)(sound_entry + 0x4) & 8) == 0) {
        short next_perm = sound_select_permutation(
          tag_ptr, *(unsigned short *)(sound_entry + 0x8e),
          *(unsigned short *)(sound_entry + 0x90));
        if (next_perm == -1) {
          if ((*(uint8_t *)tag_ptr & 2) == 0) {
            display_assert("TEST_FLAG(definition->flags, "
                           "_sound_definition_linked_permutations_bit)",
                           "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0xa1c,
                           1);
            system_exit(-1);
          }
          if ((*(uint8_t *)lsnd_tag & 2) == 0) {
            next_perm = sound_select_permutation(
              tag_ptr, *(unsigned short *)(sound_entry + 0x8e), -1);
            if (next_perm != -1)
              goto set_next_perm;
          } else {
            *(short *)(sound_entry + 0x2) = 4;
            *(uint8_t *)(looping_sound + 0x4e) = 1;
          }
        } else {
        set_next_perm:
          *(uint8_t *)(sound_entry + 0x4) |= 8;
          *(short *)(sound_entry + 0x90) = next_perm;
        }
      }
    } else {
      /* No next permutation and no queued: start next looping iteration. */
      sound_start_next_looping_permutation(*channel_ptr);
      tag_ptr = (char *)tag_get(0x736e6421, *(int *)(sound_entry + 0x8));
      pitch_range = (int)tag_block_get_element(
        tag_ptr + 0x98, (int)*(short *)(sound_entry + 0x8e), 0x48);
    }

    /* Get the current permutation and try to cache-load it. */
    permutation = (int)tag_block_get_element(
      (char *)pitch_range + 0x3c, (int)*(short *)(sound_entry + 0x90), 0x7c);
    if (*(short *)(sound_entry + 0x2) != 4 &&
        sound_cache_request_sound((void *)permutation, 0, 1, 1)) {
      *(uint8_t *)(sound_entry + 0x4) &= ~8;
      sound_channel_start_new((short)channel_index, permutation);

      /* If both the next-sound field (+0x98) and the permutation's
       * next-permutation link (+0x2a) are NONE, the chain has ended:
       * advance type 1->2 (start looping) or 3->4 (stop). */
      if (*(int *)(sound_entry + 0x98) == -1 &&
          *(short *)(permutation + 0x2a) == -1) {
        if (*(short *)(sound_entry + 0x2) == 1) {
          *(short *)(sound_entry + 0x2) = 2;
        } else if (*(short *)(sound_entry + 0x2) == 3) {
          *(short *)(sound_entry + 0x2) = 4;
        }
      }
    }
  }

final_update:
  /* Final permutation gain and property push. */
  permutation = (int)tag_block_get_element(
    (char *)pitch_range + 0x3c, (int)*(short *)(sound_entry + 0x90), 0x7c);
  properties[3] = properties[3] * *(float *)(permutation + 0x24);

  sound_channel_set_properties(si, 0, properties);

  /* Commit the channel update. */
  (*(void (**)(int))(*(int *)0x4eaf48 + 0x1c))(channel_index);
}

/* sound_start (0x1ce180)
 *
 * Attempts to start playing a sound from the given sound tag.
 *
 * 1. Loads the sound tag data via tag_get('snd!', sound_tag_index).
 * 2. Validates track_data_size <= 0x30 and source spatialization.
 * 3. For certain sound classes (0x2c, 0x2e, 0x2f), extends the minimum
 *    fade-out deadline and optionally forces spatialization to none.
 * 4. If sound system is initialized and hardware present, checks encoding
 *    compatibility (mono 22k or stereo 22k/44k compressed), volume/distance
 *    culling via random distance check, priority, and channel availability.
 * 5. Allocates a sound datum, fills in tag index, channel, source data,
 *    track data, pitch range, permutation, and timing info.
 * 6. Returns the new sound datum handle, or -1 on failure.
 */
int sound_start(int sound_tag_index, void *source, int object_handle,
                int track_data, void *track_data_ptr, int track_data_size)
{
  int result = -1;
  void *sound_tag;
  float source_scale;
  short sound_class;
  int game_time;
  int fade_deadline;
  short channel_index;
  short promotion_result;
  int sound_handle;
  char *sound_entry;
  int ftol_result;
  short pitch_range_index;
  short permutation_index;
  void *pitch_range_element;
  void *perm_block;
  void *perm_element;

  sound_tag = tag_get(0x736e6421, sound_tag_index);
  source_scale = *(float *)((char *)source + 4);

  /* Assert: track_data_size <= MAXIMUM_SOUND_CALLBACK_DATA (0x30 = 48) */
  if ((short)track_data_size > 0x30) {
    display_assert("track_data_size<=MAXIMUM_SOUND_CALLBACK_DATA",
                   "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x240, 1);
    system_exit(-1);
  }

  if (*(short *)source != 0 &&
      !valid_real_normal3d((float *)((char *)source + 0x18))) {
    display_assert(
      "source->spatialization_mode==_sound_spatialization_mode_none || "
      "valid_real_normal3d(&source->location.forward)",
      "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x242, 1);
    system_exit(-1);
  }

  /* Check sound class for fade-related classes (0x2c, 0x2e, 0x2f). */
  sound_class = *(short *)((char *)sound_tag + 4);
  if (sound_class == 0x2c || sound_class == 0x2e || sound_class == 0x2f) {
    game_time = game_time_get();
    fade_deadline =
      game_time + *(int *)((char *)sound_tag + 0x84) * 30 / 1000 + 10;
    if (fade_deadline > *(int *)0x4eaf44)
      *(int *)0x4eaf44 = fade_deadline;
    /* If a global flag is set, force spatialization to none. */
    if (*(char *)0x4fc383 != '\0')
      *(short *)source = 0;
  }

  /* Class 0x2f always forces spatialization to none. */
  if (*(short *)((char *)sound_tag + 4) == 0x2f)
    *(short *)source = 0;

  if (*(uint8_t *)0x4eaf40 != 0 && *(uint8_t *)0x4eaf41 != 0) {
    /* Check encoding compatibility: must be 1 pitch range, and either
     * (0 channels + 0 compression) or (1 channel). */
    if (*(short *)((char *)sound_tag + 0x6e) != 1 ||
        !((*(short *)((char *)sound_tag + 0x6c) == 0 &&
           *(short *)((char *)sound_tag + 6) == 0) ||
          *(short *)((char *)sound_tag + 0x6c) == 1)) {
      error(2, "attempt to play a sound that was not a mono 22k compressed "
               "sound or a stereo 22k or 44k compressed sound.");
      goto done;
    }

    /* Volume/distance culling: skip if both source scale and sound
     * skip_fraction are zero (always audible). */
    if (*(float *)((char *)source + 4) != 0.0f ||
        *(float *)((char *)sound_tag + 0x40) != 0.0f) {
      float random_val;
      {
        unsigned int *seed = random_math_get_local_seed_address();
        random_val = random_math_real(seed);
      }
      /* Compute audible distance threshold:
       * (skip_fraction_max - skip_fraction_min) * source_scale
       *   + skip_fraction_min) * sound_tag->max_distance
       * If random_val exceeds this, sound is culled. */
      {
        float skip_min = *(float *)((char *)sound_tag + 0x3c);
        float skip_max = *(float *)((char *)sound_tag + 0x54);
        float max_dist = *(float *)((char *)sound_tag + 0x10);
        float threshold =
          ((skip_max - skip_min) * source_scale + skip_min) * max_dist;
        if (random_val <= threshold)
          goto done;
      }

      /* Compute sound priority. */
      {
        float priority;
        int can_play;
        {
          /* 0x1c8d10: sound_get_default_priority(sound_tag_index) */
          priority = sound_get_default_priority(sound_tag_index);
        }

        can_play = sound_can_play(sound_tag_index);
        if (!can_play)
          goto done;

        channel_index = sound_allocate_channel(source, priority);
        if (channel_index == -1)
          goto done;

        promotion_result = sound_check_promotion(sound_tag_index);

        if (promotion_result != 0) {
          if (promotion_result == 1) {
            /* Promote: recurse with the promotion sound tag. */
            result = sound_start(*(int *)((char *)sound_tag + 0x7c), source,
                                 object_handle, track_data, track_data_ptr,
                                 track_data_size);
            return result;
          }
          /* Reject (promotion_result >= 2). */
          return -1;
        }

        /* Allocate a new sound datum. */
        sound_handle = data_new_at_index(*(data_t **)0x4fdba4);
        result = sound_handle;
        if (sound_handle == -1)
          goto done;

        sound_entry = (char *)datum_get(*(data_t **)0x4fdba4, sound_handle);

        /* 0x1ccca0: compute distance (EAX = channel_index,
         * EDI = source). Returns float distance in ST(0). Then
         * multiply by constant 8.9647 and convert to int. */
        {
          float dist = FUN_001ccca0(channel_index, source);
          ftol_result = (int)(*(float *)0x2c1288 * dist);
        }

        /* Fill in sound entry fields. */
        *(int *)(sound_entry + 0x8) = sound_tag_index;
        *(short *)(sound_entry + 0x8c) = (short)-1;
        *(short *)(sound_entry + 0x6) = channel_index;
        *(short *)(sound_entry + 0x2) = 0;

        /* Compute random scale for this sound instance. */
        {
          float rscale =
            sound_compute_random_scale(*(float *)((char *)sound_tag + 0x14),
                                       *(float *)((char *)sound_tag + 0x18),
                                       *(float *)((char *)sound_tag + 0x44),
                                       *(float *)((char *)sound_tag + 0x5c),
                                       *(float *)((char *)source + 4));
          *(float *)(sound_entry + 0x88) = rscale;
        }

        /* Copy source struct (0x40 bytes = 16 dwords) into sound
         * entry at offset 0x14. */
        *(short *)(sound_entry + 0x4) = 0;
        *(int *)(sound_entry + 0xc) = object_handle;
        csmemcpy(sound_entry + 0x14, source, 0x40);

        /* Store track_data flag and copy track data if present. */
        *(int *)(sound_entry + 0x10) = track_data;
        if (track_data != 0) {
          if (sound_entry + 0x54 == 0) {
            display_assert("sound->track_data",
                           "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x28e,
                           1);
            system_exit(-1);
          }
          csmemcpy(sound_entry + 0x54, track_data_ptr,
                   (int)(short)track_data_size);
        }

        /* Select pitch range and permutation. */
        pitch_range_index = sound_select_pitch_range(
          sound_tag, *(float *)(sound_entry + 0x88), -1);
        *(short *)(sound_entry + 0x8e) = pitch_range_index;

        permutation_index =
          sound_select_permutation(sound_tag, pitch_range_index, -1);
        *(short *)(sound_entry + 0x90) = permutation_index;

        *(int *)(sound_entry + 0xa8) = 0;
        *(int *)(sound_entry + 0xa4) = 0;
        *(short *)(sound_entry + 0x94) = (short)-1;

        /* Look up the permutation element in the sound tag and
         * request it from the sound cache. */
        {
          void *tag_data = tag_get(0x736e6421, *(int *)(sound_entry + 0x8));
          pitch_range_element = tag_block_get_element(
            (char *)tag_data + 0x98, (int)pitch_range_index, 0x48);
          perm_block = (char *)pitch_range_element + 0x3c;
          perm_element =
            tag_block_get_element(perm_block, (int)permutation_index, 0x7c);
          sound_cache_request_sound(perm_element, 0, 1, 0);
        }

        /* Set timing: if ftol_result > 250, delay start by that
         * amount relative to current timestamp, and set bit 0 of
         * flags. */
        if (ftol_result > 250) {
          *(uint8_t *)(sound_entry + 4) = *(uint8_t *)(sound_entry + 4) | 1;
          *(int *)(sound_entry + 0x84) = *(int *)0x4eaf4c + ftol_result;
          return result;
        }
        *(int *)(sound_entry + 0x84) = *(int *)0x4eaf4c;
        return result;
      }
    }
  }

done:
  return result;
}

/* sound_update_music (0x1ceda0)
 *
 * Per-channel tick for spatialized sound playback. Iterates the global
 * channel table (0x4fc3a0, stride 0x18 bytes, count at 0x4eb0b4) and, for
 * each channel that holds a live sound:
 *
 *   1. Resolves the sound datum and its tag, then updates the channel's
 *      attenuation curve via sound_update_channel_attenuation (0x1cc310,
 *      @<eax>). If the computed attenuation and the sound entry's target
 *      attenuation (sound_entry+0xa0) both reach 0.0f, the sound has
 *      faded out — stop it via sound_stop_channel (0x1cca60, @<ebx>)
 *      and mark the channel free (-1).
 *   2. Otherwise, dispatches on the sound's spatialization mode
 *      (sound_entry+0x14). Two top-level branches select on the channel
 *      flags bit 0 (+0x4 & 1):
 *        - BIT SET: drive the sound driver directly. Mode 0 asserts,
 *          mode 1 transforms position/forward/up into the listener's
 *          frame (matrix3x3 transforms + velocity compensation via
 *          listener+0x38..0x40 scaled by 30.0) and issues vtable+0x30
 *          with the transformed triple plus sound_entry+0x4c/0x50 and
 *          listener[+1]. Mode 2 issues vtable+0x30 with the raw
 *          world-space position.
 *        - BIT CLEAR: compute an audible-volume scalar. Copy the source
 *          position, then for mode 1 fetch the listener via
 *          sound_listener_get (0x1cbac0, @<si>) and transform the
 *          position through real_matrix3x3_transform_point (0x1096e0).
 *          For modes 1 and 2, scale the current attenuation by
 *          1 - (sqrt(|pos|^2) - min_dist) / (max_dist - min_dist) using
 *          sound_get_default_priority variants (0x1c8d50 min-dist,
 *          0x1c8d10 max-dist), clamped to [0, 1]. Mode 0 leaves the
 *          attenuation unchanged.
 *   3. Update the per-channel volume/pan/pitch state. If the sound's
 *      channel kind (sound_entry+0x2) is 0, invoke sound_update_channel
 *      (0x1ccf80); otherwise invoke sound_update_music_channel
 *      (0x1cdc30). Both take (channel_index, attenuation).
 *   4. If the sound class is marked "pitch-track" (class_def+0x8) and
 *      the sound's update hook (sound_entry+0x10) matches the pitch
 *      callback at 0x1c7a10, evaluate the next pitch sample via
 *      sound_get_random_permutation_pitch (0x1c8f20) driven by the
 *      channel's current ftol-truncated phase (channel+0x8 -> int) and
 *      channel+0x10, then forward it to the pitch sink at 0x1c7b00 with
 *      sound_entry+0xc. */
void sound_update_music(void)
{
  short channel_count;
  int i;
  int *channel;
  char *sound_entry;
  void *tag_ptr;
  int tag_handle;
  float attenuation;
  float audible_scale;
  /* Must be contiguous: dsound reads this as location_t (pos/fwd/up). */
  struct {
    float position[3];
    float forward[3];
    float up[3];
  } location;
  char *listener;
  void *class_def;

  channel_count = *(short *)0x4eb0b4;
  if (channel_count <= 0)
    return;

  for (i = 0; (short)i < channel_count; i++) {
    if ((short)i < 0 || (short)i >= *(short *)0x4eb0b4) {
      display_assert("index>=0 && index<sound_manager_globals.channel_count",
                     "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x428, 1);
      system_exit(-1);
    }

    /* Channel struct: stride 0x18 bytes starting at 0x4fc3a0.
     *   +0x00 int sound_handle (-1 if free)
     *   +0x04 uint32 flags (bit 0: active playback path)
     *   +0x08 float phase_accumulator
     *   +0x10 int pitch_param */
    channel = (int *)(0x4fc3a0 + (short)i * 0x18);
    if (channel[0] == -1)
      continue;

    sound_entry = (char *)datum_get(*(data_t **)0x4fdba4, channel[0]);
    tag_handle = *(int *)(sound_entry + 0x8);
    tag_ptr = tag_get(0x736e6421, tag_handle);

    /* Update attenuation curve for this channel. EAX arg is the
     * channel's sound_handle (register-passed). */
    attenuation = sound_update_channel_attenuation(channel[0]);
    audible_scale = attenuation;

    /* Faded out: both current and target reached 0.0f. */
    if (attenuation == *(float *)0x2533c0 &&
        *(float *)(sound_entry + 0xa0) == *(float *)0x2533c0) {
      sound_stop_channel(channel[0]);
      channel[0] = -1;
      continue;
    }

    if ((*(uint8_t *)((char *)channel + 0x4) & 1) != 0) {
      /* Active playback path: drive sound driver. */
      short mode = *(short *)(sound_entry + 0x14);
      if (mode == 0) {
        display_assert(0, "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x7d4, 1);
        system_exit(-1);
      } else if (mode == 1) {
        /* Listener-relative spatialization. */
        listener = (char *)sound_listener_get(*(short *)(sound_entry + 0x6));
        if (*listener == '\0') {
          display_assert("listener->valid",
                         "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x7db, 1);
          system_exit(-1);
        }

        real_matrix3x3_transform_point(
          listener + 4, (float *)(sound_entry + 0x20), location.position);
        real_matrix4x3_transform_point(listener + 4, sound_entry + 0x2c,
                                       location.forward);
        real_matrix3x3_transform_vector(listener + 4,
                                        (vector3_t *)(sound_entry + 0x38),
                                        (vector3_t *)location.up);

        /* Scale up-vector by 30.0 and subtract listener velocity
         * (listener+0x38..0x40). */
        location.up[0] =
          location.up[0] * TICKS_PER_SECOND - *(float *)(listener + 0x38);
        location.up[1] =
          location.up[1] * TICKS_PER_SECOND - *(float *)(listener + 0x3c);
        location.up[2] =
          location.up[2] * TICKS_PER_SECOND - *(float *)(listener + 0x40);

        (*(void (**)(int, int, void *, int, int, int))(*(int *)0x4eaf48 +
                                                       0x30))(
          i, 1, location.position, *(int *)(sound_entry + 0x4c),
          *(int *)(sound_entry + 0x50), (int)listener[1]);
      } else if (mode == 2) {
        (*(void (**)(int, int, void *, int, int, int))(
          *(int *)0x4eaf48 + 0x30))(i, 1, (void *)(sound_entry + 0x20), 0, 0,
                                    0);
      } else {
        display_assert(0, "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x7ec, 1);
        system_exit(-1);
      }
    } else {
      /* Inactive/culled path: compute audible_scale from attenuation. */
      short mode;
      location.position[0] = *(float *)(sound_entry + 0x20);
      location.position[1] = *(float *)(sound_entry + 0x24);
      location.position[2] = *(float *)(sound_entry + 0x28);
      mode = *(short *)(sound_entry + 0x14);
      if (mode != 0) {
        if (mode == 1) {
          listener = (char *)sound_listener_get(*(short *)(sound_entry + 0x6));
          if (*listener == '\0') {
            display_assert("listener->valid",
                           "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x7fa,
                           1);
            system_exit(-1);
          }
          real_matrix3x3_transform_point(
            listener + 4, (float *)(sound_entry + 0x20), location.position);
        } else if (mode != 2) {
          display_assert(0, "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x80a,
                         1);
          system_exit(-1);
        }

        /* Audible falloff: 1 - (sqrt(dist^2) - min) / (max - min),
         * clamped to [0, 1]. min/max come from the sound's class
         * definition (tag+class_index). */
        {
          float min_dist = sound_class_get_min_distance(tag_handle);
          float max_dist = sound_get_default_priority(tag_handle);
          float sq = location.position[0] * location.position[0] +
                     location.position[1] * location.position[1] +
                     location.position[2] * location.position[2];
          float falloff = *(float *)0x2533c8 -
                          (xbox_sqrtf(sq) - min_dist) / (max_dist - min_dist);
          if (falloff < *(float *)0x2533c0)
            falloff = *(float *)0x2533c0;
          else if (falloff > *(float *)0x2533c8)
            falloff = *(float *)0x2533c8;
          audible_scale = falloff * audible_scale;
        }
      }
    }

    /* Push updated volume/pan/pitch (music vs regular channel). */
    if (*(short *)(sound_entry + 2) == 0)
      sound_update_channel(i, audible_scale);
    else
      sound_update_music_channel(i, audible_scale);

    /* Pitch-track hook: if class_def says pitch-track and this
     * sound's update callback is FUN_001c7a10, push the next pitch
     * sample computed from channel+0x8 (phase, truncated to int) and
     * channel+0x10. */
    class_def = sound_class_get_definition(*(short *)((char *)tag_ptr + 4));
    if (*(char *)((char *)class_def + 8) != '\0' &&
        *(void **)(sound_entry + 0x10) == (void *)&FUN_001c7a10) {
      int phase_int = (int)*(float *)((char *)channel + 0x8);
      float pitch_value = sound_get_permutation_pitch(channel[4], phase_int);
      sound_pitch_push_sample(*(int *)(sound_entry + 0xc), pitch_value);
    }
  }
}

/* sound_pump (0x1cf2f0)
 *
 * Stripped-down sound tick used during fade-out spin loops.  Locks the
 * sound driver, updates timing + music, unlocks, then runs game_sound_update.
 */
void sound_idle(void)
{
  int current_ms;

  *(uint8_t *)0x4eaf43 = 1;
  if (*(uint8_t *)0x4eaf40 != 0 && *(uint8_t *)0x4eaf41 != 0) {
    (*(void (**)(void))(*(int *)0x4eaf48 + 0x10))();
    if (*(uint8_t *)0x4eaf42 == 0) {
      current_ms = system_milliseconds();
      *(float *)0x4eaf50 = (float)(current_ms - *(int *)0x4eaf4c) * 0.03f;
      *(int *)0x4eaf4c = current_ms;
      sound_update_music();
    }
    (*(void (**)(void))(*(int *)0x4eaf48 + 0x14))();
  }
  xbox_sound_cache_idle();
  *(uint8_t *)0x4eaf43 = 0;
}

void sound_dispose_from_old_map(void)
{
  unsigned int start_ms;
  int sound_index;
  float fade_end_ms;
  unsigned int now_ms;
  float now_ms_f;

  if (*(uint8_t *)0x4eaf42 == 0) {
    /* Only attempt fade if both initialized and hardware_present. */
    if (*(uint8_t *)0x4eaf40 == 0 || *(uint8_t *)0x4eaf41 == 0)
      goto skip_fade;

    /* Record start time and iterate all active sounds, triggering fade-out. */
    start_ms = ((unsigned int (*)(void))0x8e370)();
    sound_index = ((int (*)(void *, int))0x1198f0)(*(void **)0x4fdba4, -1);
    if (sound_index != -1) {
      do {
        /* sound_manager_fade: mode=0 (linear), seconds=0.3f,
         * fade_in_sound_index=NONE (-1), fade_out_sound_index=sound_index */
        ((void (*)(short, float, int, int))0x1cc8f0)(0, 0.3f, -1, sound_index);
        sound_index =
          ((int (*)(void *, int))0x1198f0)(*(void **)0x4fdba4, sound_index);
      } while (sound_index != -1);

      /* Compute deadline: start_ms + 300.0f ms (constant at 0x2c1a60). */
      fade_end_ms = (float)start_ms + 300.0f;

      /* Spin until current time >= fade_end_ms, pumping sound each iteration.
       * Unsigned→float: if MSB set, add 2^32 to correct the signed cast. */
      while (1) {
        now_ms = ((unsigned int (*)(void))0x8e370)();
        now_ms_f = (float)(int)now_ms;
        if ((int)now_ms < 0)
          now_ms_f = now_ms_f + 4294967296.0f;
        if (fade_end_ms <= now_ms_f)
          break;
        ((void (*)(void))0x1cf2f0)();
      }
    }

    if (*(uint8_t *)0x4eaf42 == 0)
      goto skip_fade;
  }

  /* Clear the fading flag, stop hardware output, record current timestamp. */
  *(uint8_t *)0x4eaf42 = 0;
  (*(void (**)(int))((*(uint8_t **)0x4eaf48) + 0x28))(0);
  *(unsigned int *)0x4eaf4c = ((unsigned int (*)(void))0x8e370)();

skip_fade:
  /* Stop all active sound channels and reset channel count. */
  ((void (*)(void))0x1cd540)();

  /* Re-validate the looping-sounds table for the next map if present. */
  if (*(void **)0x4fdba0 != 0)
    ((void (*)(void *))0x119720)(*(void **)0x4fdba0);
}

/* Per-frame sound rendering tick.
 *
 * Guarded by profiling markers (profile_enter/exit_private on "sound_render").
 * If the sound system is initialized (0x4eaf40) and hardware is present
 * (0x4eaf41):
 *   1. Call vtable+0x10 on the sound driver (lock / begin-frame).
 *   2. If not currently fading (0x4eaf42 == 0):
 *      a. Compute delta_ms = (current_ms - previous_ms) * 0.03f and store
 *         to the global sound delta (0x4eaf50). Update previous_ms (0x4eaf4c).
 *      b. Convert delta to integer ticks and pass to sound_cache_update
 *         (0x1c8c00) via the sound_listener_update result (0x1d9068).
 *      c. Run the sound subsystem pipeline: sound_update_channels (0x1ce9c0),
 *         sound_update_sources (0x1cf100), sound_update_output (0x1cd690),
 *         sound_update_effects (0x1cf360), sound_update_music (0x1ceda0).
 *      d. Toggle the per-frame flip flag at 0x4eaf54.
 *   3. Call vtable+0x14 on the sound driver (unlock / end-frame).
 * If not fading, also call game_sound_update (0x1bded0). */
void sound_render(void)
{
  int current_ms;
  float delta;

  /* Profiling: enter "sound_render" section. */
  if (*(uint8_t *)0x449ef1 != 0 && *(uint8_t *)0x32f6f0 != 0)
    profile_enter_private((void *)0x32f6e8);

  if (*(uint8_t *)0x4eaf40 != 0 && *(uint8_t *)0x4eaf41 != 0) {
    /* Lock / begin-frame on the sound driver. */
    (*(void (**)(void))(*(int *)0x4eaf48 + 0x10))();

    if (*(uint8_t *)0x4eaf42 == 0) {
      /* Compute time delta in sound-system units (ms * 0.03). */
      current_ms = system_milliseconds();
      delta = (float)(current_ms - *(int *)0x4eaf4c) * 0.03f;
      *(int *)0x4eaf4c = current_ms;
      *(float *)0x4eaf50 = delta;

      /* Update sound subsystems. The truncated delta is passed to the
       * cache/listener update chain. Original calls __ftol2 (0x1d9068) to
       * truncate the float delta; we use a plain C cast. */
      ((void (*)(int))0x1c8c00)((int)*(float *)0x4eaf50);
      ((void (*)(void))0x1ce9c0)();
      ((void (*)(void))0x1cf100)();
      ((void (*)(void))0x1cd690)();
      ((void (*)(void))0x1cf360)();
      ((void (*)(void))0x1ceda0)();

      /* Toggle per-frame flip flag. */
      *(uint8_t *)0x4eaf54 = *(uint8_t *)0x4eaf54 == 0;
    }

    /* Unlock / end-frame on the sound driver. */
    (*(void (**)(void))(*(int *)0x4eaf48 + 0x14))();
  }

  /* Update game sound (ambient/scripted) when not fading. */
  if (*(uint8_t *)0x4eaf42 == 0)
    ((void (*)(void))0x1bded0)();

  /* Profiling: exit "sound_render" section. */
  if (*(uint8_t *)0x449ef1 != 0 && *(uint8_t *)0x32f6f0 != 0)
    profile_exit_private((void *)0x32f6e8);
}
/* --- sound_manager.obj batch1 drafts (2026-07-25) --- */

void FUN_001ac030(int unit_handle, char flag)
{
  if (unit_handle == -1)
    return;
  {
    char *unit = (char *)object_get_and_verify_type(unit_handle, 3);
    if (flag)
      *(uint32_t *)(unit + 0x1b4) &= ~0x10000u;
    else
      *(uint32_t *)(unit + 0x1b4) |= 0x10000u;
  }
}

void FUN_001ac070(int unit_handle, char flag)
{
  if (unit_handle == -1)
    return;
  {
    char *unit = (char *)object_get_and_verify_type(unit_handle, 3);
    unit[0x258] = flag;
    object_set_region_count(unit_handle, 6);
  }
}

void FUN_001ac0a0(int unit_handle, char flag)
{
  if (unit_handle == -1)
    return;
  {
    char *unit = (char *)object_get_and_verify_type(unit_handle, 3);
    if (flag)
      *(uint32_t *)(unit + 0x1b4) |= 0x4000u;
    else
      *(uint32_t *)(unit + 0x1b4) &= ~0x4000u;
  }
}

int FUN_001AC0E0(int unit_handle)
{
  if (unit_handle == -1)
    return 0;
  {
    char *unit = (char *)object_get_and_verify_type(unit_handle, 3);
    int anim_tag;
    void *anim_elem;
    int frame_delta;

    if (unit[0x253] != 0x1c)
      return 0;

    anim_tag = (int)tag_get(0x616e7472, *(int *)(unit + 0x7c));
    anim_elem = tag_block_get_element((void *)(anim_tag + 0x74),
                                      (int)*(int16_t *)(unit + 0x80), 0xb4);
    frame_delta = (int)*(int16_t *)((char *)anim_elem + 0x22) -
                  (int)*(int16_t *)(unit + 0x82) - 2;
    if (frame_delta <= 0)
      return frame_delta;
    return 0;
  }
}

char FUN_001ac150(int unit_handle)
{
  if (unit_handle == -1)
    return 0;
  return (char)(*(char *)((char *)object_get_and_verify_type(unit_handle, 3) +
                          0x253) == 0x1c);
}

int16_t sound_dispose(int unit_handle)
{
  char *unit = (char *)object_get_and_verify_type(unit_handle, 3);
  int16_t slot;

  for (slot = 0; slot < 4; slot++) {
    int weapon_handle = *(int *)(unit + 0x2a8 + (int)slot * 4);
    if (weapon_handle == -1)
      continue;
    if (!weapon_has_activity(weapon_handle))
      return slot;
  }
  return (int16_t)-1;
}

char FUN_001ac3b0(int unit_handle, int weapon_handle)
{
  char *unit = (char *)object_get_and_verify_type(unit_handle, 3);
  int i;

  for (i = 0; i < 4; i++) {
    if (*(int *)(unit + 0x2a8 + i * 4) == weapon_handle)
      return 1;
  }
  return 0;
}

void FUN_001be100(void *perm_entry)
{
  char *entry = (char *)perm_entry;
  datum_get(*(data_t **)0x4e9368, *(int *)(entry + 0x2c));
  if ((uint8_t)entry[5] < 0xffu) {
    entry[5]++;
    return;
  }
  *(int16_t *)0x5054ea += 1;
}

void FUN_001be140(void *perm_entry)
{
  char *entry = (char *)perm_entry;
  datum_get(*(data_t **)0x4e9368, *(int *)(entry + 0x2c));
  if (entry[5] != 0) {
    entry[5]--;
    return;
  }
  *(int16_t *)0x5054ea += 1;
}

char FUN_001be170(int cache_handle)
{
  char *entry = (char *)datum_get(*(data_t **)0x4e9368, cache_handle);
  if (entry[2] == 0 && entry[4] == 0 && entry[5] == 0)
    return 0;
  return 1;
}

char sound_try_and_get(int sound_index)
{
  int index =
    datum_absolute_index_to_index(*(data_t **)0x4fdba4, sound_index);
  int result = -index;
  result = result - result - (result != 0);
  result = -result;
  return (char)result;
}

void sound_enable(char enabled)
{
  *(char *)0x4eaf41 = enabled;
}

char sound_scripted_dialog_is_playing(void)
{
  return (char)(game_time_get() < *(int *)0x4eaf44);
}

void sound_manager_set_sound_environment(void *environment)
{
  int i;
  int *dst = (int *)0x4eb068;
  int *src = (int *)environment;
  for (i = 0; i < 0x12; i++)
    dst[i] = src[i];
}

void FUN_001cb9d0(void)
{
  unsigned int tick = system_milliseconds();
  float delta = (float)(int)(tick - *(unsigned int *)0x4eaf4c);
  *(unsigned int *)0x4eaf4c = tick;
  *(float *)0x4eaf50 = delta * *(float *)0x25bc08;
}

float FUN_001cba00(float scale, float a, float b, float t)
{
  return ((b - a) * t + a) * scale;
}

/* --- sound_manager.obj batch2 drafts (2026-07-25) --- */

void sound_cache_new(void);

static float sound_source_distance_sq(void *source)
{
  float *p = (float *)((char *)source + 0xc);
  return p[0] * p[0] + p[1] * p[1] + p[2] * p[2];
}

static float sound_source_distance(void *source)
{
  return xbox_sqrtf(sound_source_distance_sq(source));
}

static float sound_listener_distance_sq(int channel_index, void *source)
{
  void *listener = sound_listener_get((short)channel_index);
  float *lp = (float *)((char *)listener + 0x2c);
  float *sp = (float *)((char *)source + 0xc);
  float dx = lp[0] - sp[0];
  float dy = lp[1] - sp[1];
  float dz = lp[2] - sp[2];
  return dx * dx + dy * dy + dz * dz;
}

static float sound_listener_distance(int channel_index, void *source)
{
  return xbox_sqrtf(sound_listener_distance_sq(channel_index, source));
}

void FUN_001be1b0(int cache_handle)
{
  char *entry = (char *)datum_get(*(data_t **)0x4e9368, cache_handle);
  if (entry[4] != 0 || entry[5] != 0) {
    char *perm = *(char **)(entry + 8);
    int perm_index = *(int *)(perm + 0x3c);
    const char *name = tag_get_name(perm_index);
    csprintf((char *)0x5ab100, (char *)0x2b93e0, name);
    display_assert((char *)0x2b9288, "c:\\halo\\SOURCE\\cache\\xbox_sound_cache.c",
                   0x141, 1);
    system_exit(-1);
  }
  {
    char *perm = *(char **)(entry + 8);
    if (*(int *)(perm + 0x2c) != cache_handle) {
      display_assert((char *)0x2b9288, "c:\\halo\\SOURCE\\cache\\xbox_sound_cache.c",
                     0x144, 1);
      system_exit(-1);
    }
    *(int *)(perm + 0x2c) = -1;
    *(int *)(perm + 0x30) = 0;
  }
  datum_delete(*(data_t **)0x4e9368, cache_handle);
}

void *FUN_001be270(int cache_handle)
{
  char *entry = (char *)datum_get(*(data_t **)0x4e9368, cache_handle);
  char *perm = *(char **)(entry + 8);
  const char *name = tag_get_name(*(int *)(perm + 0x3c));
  crt_sprintf((char *)0x4e9268, (char *)0x2b9424, name);
  return (void *)0x4e9268;
}

void FUN_001be2b0(void *perm_entry /* @<esi> */)
{
  char *perm = (char *)perm_entry;
  int block_index = FUN_0011de10(*(void **)0x4e9370, *(unsigned int *)(perm + 0x40));
  if (block_index == -1)
    return;
  {
    int addr = lruv_block_get_address(*(void **)0x4e9370, block_index);
    int cache_handle = data_new_datum(*(data_t **)0x4e9368, block_index);
    char *entry = (char *)datum_get(*(data_t **)0x4e9368, block_index);
    if (cache_handle != block_index) {
      display_assert((char *)0x2b9288, "c:\\halo\\SOURCE\\cache\\xbox_sound_cache.c",
                     0x170, 1);
      system_exit(-1);
    }
    *(int *)(perm + 0x2c) = block_index;
    *(int *)(perm + 0x30) = addr + *(int *)0x4e936c;
    *(char **)(entry + 8) = perm;
    cache_file_read(*(int *)(perm + 0x40), *(int *)(perm + 0x34),
                    *(unsigned int *)(perm + 0x48), (int)(entry + 2), perm, 0);
  }
}

void FUN_001c7b40(void)
{
  void *scenario = scenario_get();
  int cluster_count = *(int *)((char *)scenario + 0x134);
  int table_bytes = (((cluster_count + 0x1f) >> 5) << 2);
  csmemset((void *)0x5054a0, 0, table_bytes);
  {
    short player_index;
    for (player_index = 0; player_index < 4; player_index++) {
      int pi = local_player_get_player_index(player_index);
      if (pi == -1)
        continue;
      void *camera = observer_get_camera((unsigned short)player_index);
      if (*(int16_t *)((char *)camera + 0x10) == -1)
        continue;
      {
        int cluster;
        for (cluster = 0; cluster < cluster_count; cluster++) {
          uint8_t enc = structure_bsp_cluster_sound_encoding(scenario,
                                                             *(int16_t *)((char *)camera + 0x10),
                                                             (int16_t)cluster);
          int enc_val = (int)(enc & 0x7f);
          float scaled = (float)enc_val * *(float *)0x256148;
          if (scaled <= *(float *)0x2642a0) {
            int word_index = cluster >> 5;
            int bit = 1 << (cluster & 0x1f);
            *(uint32_t *)(0x5054a0 + word_index * 4) |= (uint32_t)bit;
          }
        }
      }
    }
  }
}

int FUN_001c8700(void *state, int sample_count, int16_t *out, void *track,
                 void *bitstream)
{
  char *st = (char *)state;
  int bits_left = *(int *)st;
  char *in_ptr = st + 8;
  int samples = sample_count;
  if (samples == 0)
    return bits_left + bits_left;
  if (bitstream) {
    char *bs = (char *)bitstream;
    if (*(int *)bs == 0) {
      *(int *)bs = bits_left;
      *(int16_t *)(bs + 8) = *(int16_t *)(st + 4);
      *(int16_t *)(bs + 0xa) = 0;
    }
    {
      int16_t value = *(int16_t *)(bs + 8);
      int consumed = *(int *)(bs + 4);
      int avail = *(int *)bs - consumed;
      char *src = in_ptr + (consumed >> 1);
      int16_t step_index = *(int16_t *)(bs + 0xa);
      char use_high_nibble = (char)(~(char)consumed & 1);
      int out_count = sample_count;
      int16_t *dst = out;
      void *tbl_hi = (void *)0x2bc710;
      void *tbl_lo = (void *)0x2bc6d0;
      while (out_count > 0 && avail > 0 && track) {
        uint8_t nibble_byte = *(uint8_t *)src;
        int table_index = (int)step_index;
        int delta = *(int *)(4 * table_index + (int)tbl_hi);
        delta >>= 3;
        if (use_high_nibble)
          nibble_byte >>= 4;
        {
          uint8_t nibble = nibble_byte & 0xf;
          int bit = 4;
          while (bit) {
            if (nibble & bit)
              delta += *(int *)(4 * table_index + (int)tbl_hi);
            bit >>= 1;
            delta >>= 1;
          }
          if (nibble & 8)
            delta = -delta;
          {
            int step = *(int *)(4 * (int)nibble + (int)tbl_lo);
            step_index = (int16_t)(step_index + step);
            if (step_index < 0)
              step_index = 0;
            else if (step_index > 0x58)
              step_index = 0x58;
          }
        }
        value = (int16_t)(value + (int16_t)delta);
        if (value < (int16_t)0x8000)
          value = (int16_t)0x8000;
        else if (value > 0x7fff)
          value = 0x7fff;
        *dst = value;
        if (use_high_nibble) {
          src++;
          avail--;
        }
        use_high_nibble = (char)!use_high_nibble;
        dst++;
        out_count--;
        consumed++;
        if (track)
          (*(int *)(bs + 4))++;
      }
      if (bitstream) {
        *(int16_t *)(bs + 8) = value;
        *(int16_t *)(bs + 0xa) = step_index;
      }
      bits_left = *(int *)bs - *(int *)(bs + 4);
    }
  }
  return bits_left + bits_left;
}

void sound_is_active(int sound_index)
{
  FUN_00118be0((void *)0x32ecf4, (void *)(long)sound_index, 1);
}

void FUN_001c8ee0(void *pitch_range)
{
  char *range = (char *)pitch_range;
  int16_t played = *(int16_t *)(range + 0x2c);
  uint32_t mask = (1u << (played & 0x1f)) - 1u;
  if ((~*(uint32_t *)(range + 0x34) & mask) == 0) {
    *(uint32_t *)(range + 0x34) = 0;
    if (played > 1) {
      uint8_t bit = *(uint8_t *)(range + 0x38);
      *(uint32_t *)(range + 0x34) = 1u << bit;
    }
  }
}

void FUN_001cb1a0(int channel_index, int param)
{
  short resolved = sound_dsound_channel_resolve(channel_index);
  if (resolved != -1)
    FUN_001cb0c0(resolved);
}

void FUN_001cb1d0(int channel_index, int a, int b, int c, int d, int e)
{
  short resolved = sound_dsound_channel_resolve(channel_index);
  if (resolved != -1)
    FUN_001cadd0(resolved, a, b, c, d, 0);
}

char FUN_001cb210(short channel_index /* @<ax> */, unsigned char flags /* @<bl> */)
{
  char desc[0x80];
  char buf[0x34];
  char stereo_buf[0x2c];
  void *channel = sound_dsound_channel_get(channel_index);
  csmemset(desc, 0, 0x80);
  *(uint16_t *)((char *)channel + 0x38) = (uint16_t)flags;
  *(int16_t *)((char *)channel + 2) = -1;
  ((char *)channel)[6] = 0;
  *(int *)((char *)channel + 0x68) = 0;
  *(int *)((char *)channel + 0x6c) = 0;
  {
    int block_align;
    int16_t format;
    int16_t channels;
    int16_t bits;
    int16_t rate_idx;
    if (flags & 8) {
      block_align = *(int *)0x2bcc1c * 4;
      format = 1;
      channels = 2;
      rate_idx = 0x10;
      bits = 4;
    } else {
      int codec = ((flags & 2) != 0) ? 2 : 1;
      format = 0x69;
      channels = 4;
      rate_idx = (int16_t)codec;
      bits = 2;
      block_align = sound_dsound_get_sample_rate((flags >> 2) & 1);
      block_align = (block_align >> 6) * (int)rate_idx * 4;
    }
    (void)format;
    (void)channels;
    (void)bits;
    csmemset(buf, 0, 0x18);
    *(int *)(buf + 0x10) = block_align;
    *(int *)(buf + 0x14) = 0;
    *(int *)(buf + 0) = (int)(long)(buf + 0x1c);
    *(int *)(buf + 4) = (flags & 1) ? 0x10 : 0;
    *(int *)(buf + 8) = 0x1ca970;
    *(int *)(buf + 0xc) = (int)channel_index;
    if (FUN_002060f8(0, (char *)channel + 0x70, buf, *(void **)0x50545c) < 0) {
      sound_dsound_log_error(-1, (char *)0x2c114c);
      return 0;
    }
    if (flags & 1) {
      csmemset(stereo_buf, 0, 0x2c);
    FUN_001cadd0((int)(long)stereo_buf, 0, 0, 0, (int)channel_index, 0);
    } else {
      int caps;
      FUN_00204c79(&caps, *(void **)0x50545c);
      if (caps & 0x10000) {
        if (flags & 2) {
          sound_dsound_gain_to_volume(1.0f, 0);
          sound_dsound_gain_to_volume(1.0f, 0);
          sound_dsound_gain_to_volume(0.5f, 0);
        } else {
          sound_dsound_gain_to_volume(0.5f, 0);
          sound_dsound_gain_to_volume(0.5f, 0);
        }
      } else if (!(flags & 2)) {
        sound_dsound_gain_to_volume(0.5f, 0);
        sound_dsound_gain_to_volume(0.5f, 0);
      }
      FUN_002052de(*(void **)channel, 7, (void *)0x2bc710);
      FUN_00205bd8(*(void **)channel, 3, stereo_buf);
    }
    csmemset(desc, 0, 0x20);
    *(float *)desc = 1.0f;
    *(float *)(desc + 4) = 1.0f;
    sound_dsound_update_channel_properties((float *)desc, channel_index, 0);
    return 1;
  }
}

char FUN_001cb4c0(void *driver_caps)
{
  char ok = 0;
  *(char *)0x4fdbc0 = 0;
  *(char *)0x505484 = 0;
  *(float *)0x505488 = 1.0f;
  *(int *)0x505460 = 0;
  if (!driver_caps) {
    display_assert((char *)0x280f94, "c:\\halo\\SOURCE\\sound\\sound_dsound_xbox.c",
                   0xea, 1);
    system_exit(-1);
  }
  int coop_a;
  int coop_b;
  if (FUN_00206232(*(void **)0x50545c, 0, 0) < 0)
    goto fail;
  {
    int wf[4];
    if (FUN_00204c5d(*(void **)0x50545c, wf) < 0)
      goto fail_caps;
    *(int *)0x50544c = wf[0];
    *(int *)0x505450 = wf[1];
    *(int *)0x505454 = wf[2];
    *(int *)0x505458 = wf[3];
    if (FUN_00204d81(*(void **)0x50545c, 0x4043126f) < 0)
      goto fail_pri;
    if (FUN_00204e48(*(void **)0x50545c, 1.0f) < 0)
      goto fail_vol;
  }
  {
    char buf[0x34];
    csmemset(buf, 0, 0x34);
    if (FUN_00204c95(*(void **)0x50545c, (void *)0x2bccf0, 0x3a5c, &coop_a,
                     &coop_b) < 0) {
      sound_dsound_log_error(-1, (char *)0x2c11fc);
    }
    FUN_00204d41(*(void **)0x50545c, 0, 0x7fffffff);
    FUN_002038df();
    FUN_001ca2b0(buf);
  }
  {
    char *caps = (char *)driver_caps;
    int bus;
    for (bus = 0; bus < 4; bus++) {
      int16_t *counts = (int16_t *)(caps + 0xa + bus * 2);
      int16_t j;
      char created = 1;
      for (j = 0; j < *counts; j++) {
        *(int16_t *)0x4fdbc2 += 1;
        if (created) {
          void *ch = sound_dsound_vchannel_get(j);
          if (j < 0 || j >= 4) {
            display_assert((char *)0x2c08f8, "c:\\halo\\SOURCE\\sound\\sound_dsound_xbox.c",
                           0x1a6, 1);
            system_exit(-1);
          }
          *(int16_t *)((char *)ch + 2) = -1;
          *(int16_t *)ch = j;
          created = 1;
        } else {
          created = 0;
        }
      }
    }
    {
      int16_t *src = (int16_t *)((char *)caps + 2);
      csmemcpy((void *)0x5053c6, src, 8);
      int group;
      for (group = 0; group < 4; group++) {
        int16_t k;
        char group_ok = 0;
        for (k = 0; k < src[group]; k++) {
          *(int16_t *)0x4fdfc4 += 1;
          if (group_ok) {
            if (FUN_001cb210(k, 0))
              group_ok = 1;
            else
              group_ok = 0;
          }
        }
        if (group_ok)
          ok = 1;
      }
    }
  }
  if (ok)
    FUN_001c9cf0();
  return ok;
fail_vol:
fail_pri:
fail_caps:
fail:
  return 0;
}

void FUN_001cb820(void)
{
  if (*(char *)0x4eaf40) {
    (*(void (**)(void))(*(int *)0x4eaf48 + 8))();
    data_make_invalid(*(data_t **)0x4fdba4);
    data_make_invalid(*(data_t **)0x4fdba0);
    *(char *)0x4eaf40 = 0;
  }
  if (*(data_t **)0x4fdba4)
    data_dispose(*(data_t **)0x4fdba4);
  if (*(data_t **)0x4fdba0)
    data_dispose(*(data_t **)0x4fdba0);
  FUN_001bde90();
}

void sound_reconnect_to_structure_bsp(void)
{
  if (*(char *)0x4eaf40 && *(char *)0x4eaf41) {
    int index = data_next_index(*(data_t **)0x4fdba4, -1);
    while (index != -1) {
      char *entry = (char *)datum_get(*(data_t **)0x4fdba4, index);
      if (*(int16_t *)(entry + 0x14) == 1) {
        scenario_location_from_point(entry + 0x20, entry + 0x44);
      }
      index = data_next_index(*(data_t **)0x4fdba4, index);
    }
  }
}

float FUN_001cbc20(float t)
{
  return *(float *)0x2c1288 * t;
}

char FUN_001cbc40(int sound_handle /* @<ebx> */)
{
  char *entry = (char *)datum_get(*(data_t **)0x4fdba4, sound_handle);
  int16_t channel = *(int16_t *)(entry + 0x8c);
  if (channel != -1) {
    if (channel < 0 || channel >= *(int16_t *)0x4eb0b4) {
      display_assert((char *)0x2c1294, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                     0x428, 1);
      system_exit(-1);
    }
    if (*(int *)(0x4fc3a0 + (int)channel * 0x18) != sound_handle) {
      display_assert((char *)0x2c1360, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                     0x59f, 1);
      system_exit(-1);
    }
  }
  if (!(*(uint8_t *)(entry + 4) & 1)) {
    char (*update)(int, void *, void *) =
        *(char (**)(int, void *, void *))(entry + 0x10);
    if (update && *(int *)(entry + 0x84) < *(int *)0x4eaf4c) {
      if (!update(*(int *)(entry + 0xc), entry + 0x54, entry + 0x14)) {
        if (*(int16_t *)(entry + 2) == 0) {
          void *tag = tag_get(0x736e6421, *(int *)(entry + 8));
          void *class_def = sound_class_get_definition(*(int16_t *)((char *)tag + 4));
          if (!((char *)class_def)[8])
            *(int *)(entry + 0x10) = 0;
          else
            return 0;
        } else {
          return 0;
        }
      }
    }
  }
  return 1;
}

char FUN_001cc1c0(int looping_handle, void *out)
{
  char *src = (char *)datum_absolute_index_to_index(*(data_t **)0x4fdba0,
                                                    looping_handle);
  if (!src)
    return 0;
  csmemcpy(out, src + 0xc, 0x40);
  return 1;
}

char FUN_001cc200(int looping_handle, void *source, void *position)
{
  char *src = (char *)datum_absolute_index_to_index(*(data_t **)0x4fdba0,
                                                    looping_handle);
  char *dst = (char *)position;
  if (!src)
    return 0;
  *(int *)(dst + 0x38) = *(int *)(src + 0x44);
  *(int *)(dst + 0x3c) = *(int *)(src + 0x48);
  if (*(int16_t *)(src + 0xc) != 0) {
    csmemcpy(dst + 0x24, src + 0x30, 0xc);
    csmemcpy(dst + 0x18, src + 0x24, 0xc);
    *(int *)(dst + 0x30) = *(int *)(src + 0x3c);
    *(int *)(dst + 0x34) = *(int *)(src + 0x40);
  } else {
    csmemcpy(dst + 0x18, *(void **)0x31fc3c, 0xc);
    csmemcpy(dst + 0x24, *(void **)0x31fc38, 0xc);
  }
  csmemcpy(dst + 0xc, source, 0xc);
  if (*(int16_t *)dst == 1) {
    *(float *)(dst + 0xc) += *(float *)(src + 0x18);
    *(float *)(dst + 0x10) += *(float *)(src + 0x1c);
    *(float *)(dst + 0x14) += *(float *)(src + 0x20);
  }
  return 1;
}

void FUN_001cc2f0(int sound_handle /* @<eax> */, int tag_index /* @<esi> */)
{
  char *entry = (char *)datum_get(*(data_t **)0x4fdba4, sound_handle);
  if (*(int *)(entry + 8) != tag_index)
    *(int *)(entry + 0x98) = tag_index;
}

int FUN_001cc440(int source /* @<edi> */)
{
  int index = data_next_index(*(data_t **)0x4fdba0, -1);
  while (index != -1) {
    char *entry = (char *)datum_get(*(data_t **)0x4fdba0, index);
    if (*(int *)(entry + 8) == source)
      return index;
    index = data_next_index(*(data_t **)0x4fdba0, index);
  }
  return -1;
}

void FUN_001cc4f0(int sound_handle)
{
  if (*(char *)0x4fc382) {
    char buf[0x200];
    char *entry = (char *)datum_get(*(data_t **)0x4fdba4, sound_handle);
    float priority = sound_get_default_priority(*(int *)(entry + 8));
    float min_dist = sound_class_get_min_distance(*(int *)(entry + 8));
    float gain_a = *(float *)(entry + 0x4c);
    float gain_b = *(float *)(entry + 0x50);
    FUN_00189540(0, entry + 0x20, priority, (void *)0x2ee6e0);
    FUN_00189540(0, entry + 0x20, min_dist, (void *)0x2ee6d0);
    crt_sprintf(buf, (char *)0x2c1538, tag_get_name(*(int *)(entry + 8)),
                (double)gain_a, (double)gain_b);
    FUN_00189cb0(0, entry + 0x20, buf, *(int *)0x2ee6c4);
  }
}

void FUN_001cc5b0(int sound_tag_index, void *source)
{
  if (*(char *)0x4fc381 && *(int16_t *)source == 1) {
    void *lsnd = tag_get(0x6c736e64, sound_tag_index);
    char *pitch_block = (char *)lsnd + 0x3c;
    float min_dist = 0.0f;
    float priority = 0.0f;
    int i;
    for (i = 0; i < *(int *)pitch_block; i++) {
      char *elem = (char *)tag_block_get_element(pitch_block, i, 0xa0);
      if (*(int *)(elem + 0x4c) != -1) {
        min_dist = sound_class_get_min_distance(*(int *)(elem + 0x4c));
        priority = sound_get_default_priority(*(int *)(elem + 0x4c));
        if (min_dist <= *(float *)0x2533c0)
          break;
      }
    }
    {
      char *track_block = (char *)lsnd + 0x48;
      for (i = 0; i < *(int *)track_block; i++) {
        char *elem = (char *)tag_block_get_element(track_block, i, 0x68);
        if (*(int *)(elem + 0xc) != -1) {
          min_dist = sound_class_get_min_distance(*(int *)(elem + 0xc));
          priority = sound_get_default_priority(*(int *)(elem + 0xc));
        }
      }
    }
    {
      char *pos = (char *)source + 0xc;
      const char *name = tag_get_name(sound_tag_index);
      FUN_00189cb0(0, pos, (void *)name, *(int *)0x2ee6c4);
      FUN_00189540(0, pos, priority, (void *)0x2ee6dc);
      FUN_00189540(0, pos, min_dist, (void *)0x2ee6d8);
    }
  }
}

void sound_initialize(void **driver_out)
{
  *(char *)0x4eaf40 = 0;
  *(char *)0x4eaf41 = 1;
  FUN_001cf820(driver_out);
  sound_cache_new();
  csmemcpy((void *)0x4eb068, (void *)0x2c1220, 0x12 * 4);
  *(float *)0x4eb0b0 = 1.0f;
  if (driver_out) {
    int16_t driver_id = *(int16_t *)driver_out;
    if (driver_id >= 0 && driver_id < 2) {
      void *driver = *(void **)(0x32f6dc + (int)driver_id * 4);
      if (driver && *(int16_t *)driver == driver_id) {
        data_t *sounds = data_new((char *)0x2c1590, 0x200, 0xac);
        data_t *looping = data_new((char *)0x2c1580, 0x80, 0xe4);
        *(data_t **)0x4fdba4 = sounds;
        *(data_t **)0x4fdba0 = looping;
        if (sounds && looping &&
            ((char (*)(void *)) * (void (**)(void *))((char *)driver + 4))(
                driver_out)) {
          data_delete_all(sounds);
          data_delete_all(looping);
          {
            int16_t *counts = (int16_t *)driver_out;
            int16_t *cursor = (int16_t *)0x32fcf8;
            int group;
            for (group = 0; group < 4; group++) {
              int16_t total = *(int16_t *)0x4eb0b4 + counts[group];
              if (total > 0x100) {
                display_assert((char *)0x2c1544, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                               0x168, 1);
                system_exit(-1);
              }
              *(int16_t *)0x4eb0b4 = total;
              {
                int16_t j;
                for (j = 0; j < counts[group]; j++) {
                  char *slot = (char *)sound_channel_get(j);
                  *(int *)slot = -1;
                  *(int16_t *)(slot + 4) = cursor[group];
                  *(int *)(slot + 0x10) = 0;
                  *(int *)(slot + 0x14) = 0;
                }
              }
              cursor += 1;
            }
          }
          *(char *)0x4eaf40 = 1;
        }
      }
    }
  }
}

float FUN_001ccbe0(int channel_index /* @<eax> */, void *source /* @<edi> */)
{
  switch (*(int16_t *)source) {
  case 0:
    return *(float *)0x2533c0;
  case 1:
    if (!*(char *)sound_listener_get((short)channel_index)) {
      display_assert((char *)0x2c1624, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                     0x574, 1);
      system_exit(-1);
    }
    return sound_listener_distance_sq(channel_index, source);
  case 2:
    return sound_source_distance_sq(source);
  default:
    display_assert((char *)0, "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x57a, 1);
    system_exit(-1);
    return 0.0f;
  }
}

float FUN_001ccca0(int channel_index /* @<eax> */, void *source /* @<edi> */)
{
  switch (*(int16_t *)source) {
  case 0:
    return *(float *)0x2533c0;
  case 1:
    if (!*(char *)sound_listener_get((short)channel_index)) {
      display_assert((char *)0x2c1624, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                     0x58d, 1);
      system_exit(-1);
    }
    return sound_listener_distance(channel_index, source);
  case 2:
    return sound_source_distance(source);
  default:
    display_assert((char *)0, "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x593, 1);
    system_exit(-1);
    return 0.0f;
  }
}

char sound_update_time(int sound_a /* @<eax> */, int sound_b /* @<edi> */,
                       float threshold)
{
  char *entry_a = (char *)datum_get(*(data_t **)0x4fdba4, sound_a);
  void *tag_a = tag_get(0x736e6421, *(int *)(entry_a + 8));
  char *entry_b = (char *)datum_get(*(data_t **)0x4fdba4, sound_b);
  void *tag_b = tag_get(0x736e6421, *(int *)(entry_b + 8));
  if (sound_b != sound_a) {
    display_assert((char *)0x2c1648, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                   0x763, 1);
    system_exit(-1);
  }
  {
    void *class_a = sound_class_get_definition(*(int16_t *)((char *)tag_a + 4));
    void *class_b = sound_class_get_definition(*(int16_t *)((char *)tag_b + 4));
    if (*(int16_t *)((char *)class_a + 0xa) <= *(int16_t *)((char *)class_b + 0xa))
      return 1;
    if (*(int16_t *)((char *)class_a + 0xa) == *(int16_t *)((char *)class_b + 0xa)) {
      float dist = FUN_001ccbe0(*(int16_t *)(entry_b + 6), entry_b + 0x14);
      if ((dist <= threshold) == 0)
        return 0;
    }
    return 1;
  }
}

int FUN_001cd190(int sound_tag_index /* @<eax> */, void *track, void *source)
{
  if (!*(char *)0x4eaf40 || !*(char *)0x4eaf41)
    return -1;
  {
    int index = data_new_at_index(*(data_t **)0x4fdba0);
    if (index == -1)
      return -1;
    char *entry = (char *)datum_get(*(data_t **)0x4fdba0, index);
    void *lsnd = tag_get(0x6c736e64, sound_tag_index);
    *(int *)(entry + 4) = sound_tag_index;
    *(int *)(entry + 8) = *(int *)source;
    *(int16_t *)(entry + 0x50) = 0;
    entry[0x4e] = 0;
    if (*(int *)((char *)lsnd + 0x48) <= 0)
      return index;
    {
      char *block = (char *)lsnd + 0x48;
      int i = 0;
      for (;;) {
        char *elem = (char *)tag_block_get_element(block, i, 0x68);
        if (*(int *)(elem + 0xc) == -1) {
          if (++i >= *(int *)block)
            return index;
          continue;
        }
        {
          unsigned int *seed = random_math_get_local_seed_address();
          float r = random_real_range((int *)seed, *(float *)(elem + 0x10),
                                      *(float *)(elem + 0x14));
          float span = *(float *)((char *)lsnd + 0x10) - *(float *)((char *)lsnd + 4);
          int start_ms = (int)(float)(r * span * *(float *)0x254cb8 +
                                      (float)*(int *)0x4eaf4c);
          *(int *)(entry + 0x54 + i * 4) = start_ms;
        }
        if (++i >= *(int *)block)
          return index;
      }
    }
  }
}

void FUN_001cd390(void *track_entry /* @<edi> */, float *out /* @<esi> */)
{
  float r1 = random_real_range((int *)random_math_get_local_seed_address(),
                               *(float *)((char *)track_entry + 0x60),
                               *(float *)((char *)track_entry + 0x64));
  if (r1 > *(float *)0x2533c0) {
    float *defaults = (float *)0x31fc38;
    out[0] = defaults[0];
    out[1] = defaults[1];
    out[2] = defaults[2];
    return;
  }
  {
    float r2 = random_real_range((int *)random_math_get_local_seed_address(),
                                 *(float *)((char *)track_entry + 0x58),
                                 *(float *)((char *)track_entry + 0x5c));
    float r3 = random_real_range((int *)random_math_get_local_seed_address(),
                                 *(float *)((char *)track_entry + 0x50),
                                 *(float *)((char *)track_entry + 0x54));
    float angles[3];
    float vec[3];
    angles[0] = r2;
    angles[1] = r3;
    angles[2] = 0.0f;
    angles_to_vector(vec, angles);
    out[0] = vec[0] * r1;
    out[1] = vec[1] * r1;
    out[2] = vec[2] * r1;
  }
}

void sound_stop_impulse_by_source_and_definition(int source, int definition)
{
  int index = data_next_index(*(data_t **)0x4fdba4, -1);
  while (index != -1) {
    char *entry = (char *)datum_get(*(data_t **)0x4fdba4, index);
    if (*(int16_t *)(entry + 2) == 0 && *(int *)(entry + 0xc) == source &&
        *(int *)(entry + 8) == definition) {
      sound_stop_impulse(index);
      return;
    }
    index = data_next_index(*(data_t **)0x4fdba4, index);
  }
}

void sound_stop_all(void)
{
  if (*(char *)0x4eaf40) {
    int index = data_next_index(*(data_t **)0x4fdba4, -1);
    while (index != -1) {
      sound_stop_channel(index);
      index = data_next_index(*(data_t **)0x4fdba4, index);
    }
    data_make_valid(*(data_t **)0x4fdba0);
    (*(void (**)(void))(*(int *)0x4eaf48 + 0x2c))();
  }
  *(int *)0x4eaf44 = 0;
}

void FUN_001cd690(void)
{
  char all_dead = players_are_all_dead();
  int index = data_next_index(*(data_t **)0x4fdba4, -1);
  char music_active = 0;
  while (index != -1) {
    char *entry = (char *)datum_get(*(data_t **)0x4fdba4, index);
    void *tag = tag_get(0x736e6421, *(int *)(entry + 8));
    int16_t channel = *(int16_t *)(entry + 0x8c);
    if (channel == -1 || !sound_channel_update_status(channel) ||
        *(int16_t *)(entry + 2) == 2 || *(int16_t *)(entry + 2) == 3) {
      if (FUN_001cbc40(index)) {
        float priority = sound_get_default_priority(*(int *)(entry + 8));
        int16_t allocated = sound_allocate_channel(entry + 0x14, priority);
        FUN_001cc4f0(index);
        {
          int16_t class_index = *(int16_t *)((char *)tag + 4);
          if (class_index == 0x2c || class_index == 0x2e || class_index == 0x2f)
            music_active = 1;
        }
        if (allocated == -1) {
          if (!(entry[4] & 4))
            sound_start_fade(0, -1.0f, *(int *)0x2c127c, index);
          entry[4] |= 4;
        } else {
          *(int16_t *)(entry + 6) = allocated;
          if (entry[4] & 4) {
            sound_start_fade(0, -1.0f, index, *(int *)0x2c1280);
            entry[4] &= ~4;
          }
        }
        if (all_dead) {
          if (*(int16_t *)((char *)tag + 4) == 0x2c && *(int16_t *)(entry + 0x8c) != -1)
            sound_start_fade(0, -1.0f, *(int *)0x2c1284, index);
          else if (*(int16_t *)((char *)tag + 4) == 0x2e &&
                   *(int16_t *)(entry + 0x8c) == -1)
            ;
        }
      } else {
        sound_stop_channel(index);
      }
    } else {
      sound_stop_channel(index);
    }
    index = data_next_index(*(data_t **)0x4fdba4, index);
  }
  if (music_active) {
    float step = *(float *)0x4eaf50 * *(float *)0x25bc08;
    float target = *(float *)0x32f6d8 - *(float *)0x4eb0b0;
    if (-step <= target && target <= step)
      *(float *)0x4eb0b0 += target;
    else if (target > step)
      *(float *)0x4eb0b0 += step;
  } else {
    float step = *(float *)0x4eaf50 * *(float *)0x2c16d0;
    float target = *(float *)0x2533c8 - *(float *)0x4eb0b0;
    if (-step <= target && target <= step)
      *(float *)0x4eb0b0 += target;
    else
      *(float *)0x4eb0b0 += step;
  }
}

short FUN_001cd8b0(int sound_handle)
{
  char *entry = (char *)datum_get(*(data_t **)0x4fdba4, sound_handle);
  void *tag = tag_get(0x736e6421, *(int *)(entry + 8));
  short best = -1;
  float best_dist = 0.0f;
  short channel = *(int16_t *)(entry + 6);
  float ref_dist = FUN_001ccbe0(channel, entry + 0x14);
  short count = *(int16_t *)0x4eb0b4;
  short i;
  for (i = 0; i < count; i++) {
    int16_t enc = *(int16_t *)(0x4fc3a4 + (int)i * 8);
    char ok = 1;
    if (((enc >> 3) & 1) != (*(int16_t *)((char *)tag + 0x6e) == 0))
      ok = 0;
    if (((enc >> 1) & 1) != (*(int16_t *)((char *)tag + 0x6c) == 0))
      ok = 0;
    if (((enc >> 2) & 1) != (*(int16_t *)((char *)tag + 6) == 0))
      ok = 0;
    if (!(enc & 2)) {
      if ((~enc & 1) != (*(int16_t *)(entry + 0x14) == 0))
        ok = 0;
    }
    if (ok) {
      int other = *(int *)(0x4fc3a0 + (int)i * 0x18);
      if (other == -1)
        return i;
      if (sound_update_time(other, sound_handle, ref_dist)) {
        if (best != -1) {
          char *other_entry = (char *)datum_get(*(data_t **)0x4fdba4, other);
          float d = FUN_001ccbe0(*(int16_t *)(other_entry + 6), other_entry + 0x14);
          if (!sound_update_time(sound_handle, other, d))
            continue;
        }
        best = i;
        best_dist = FUN_001ccbe0(channel, entry + 0x14);
      }
    }
  }
  (void)best_dist;
  return best;
}

char sound_refresh_looping(int sound_tag_index, void *source, void *track,
                           short track_type)
{
  char created = 0;
  char *src = (char *)source;
  if (*(int16_t *)src != 0) {
    if (!valid_real_normal3d((float *)(src + 0x18))) {
      display_assert((char *)0x2c17c0, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                     0x2f4, 1);
      system_exit(-1);
    }
  }
  FUN_001cc5b0(sound_tag_index, source);
  if (!*(char *)0x4eaf40 || !*(char *)0x4eaf41)
    return 0;
  {
    int looping_index = FUN_001cc440(sound_tag_index);
    if (looping_index == -1) {
      if (track_type == 2)
        return 0;
      looping_index = FUN_001cd190(sound_tag_index, track, source);
      if (looping_index == -1)
        return 0;
      created = 1;
    }
    {
      char *loop = (char *)datum_get(*(data_t **)0x4fdba0, looping_index);
      void *lsnd = tag_get(0x6c736e64, sound_tag_index);
      if (*(int *)(loop + 4) != sound_tag_index) {
        display_assert((char *)0x2c1860, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                       0x30e, 1);
        system_exit(-1);
      }
      csmemcpy(loop + 0xc, source, 0x40);
      loop[0x4c] = *(char *)0x4eaf54;
      if (track_type != 2 && loop[0x4e] && *(int16_t *)(loop + 0x50) == 0) {
        datum_delete(*(data_t **)0x4fdba0, looping_index);
        return 1;
      }
      if (!FUN_001cc200(looping_index, track, loop + 0xc))
        return 0;
      if (*(int16_t *)(loop + 0x52) == 2)
        return 1;
      {
        int i;
        char *tracks = (char *)lsnd + 0x48;
        for (i = 0; i < *(int *)tracks; i++) {
          char *elem = (char *)tag_block_get_element(tracks, i, 0x68);
          if (*(int *)(loop + 0x54 + i * 4) < *(int *)0x4eaf4c &&
              *(int *)(elem + 0xc) != -1) {
            float out[3];
            float params[3];
            params[0] = *(float *)(elem + 0x18);
            params[1] = *(float *)(elem + 0x10);
            params[2] = *(float *)(elem + 0x14);
            FUN_001cd390(elem, out);
            if (!FUN_001cc200(looping_index, params, out))
              return 0;
            if (*(int *)(loop + 0x10) != (int)0x1cc200)
              sound_start(*(int *)(elem + 0xc), out, *(int *)(loop + 8), 0, 0, 0);
          }
        }
      }
      (void)created;
      return 1;
    }
  }
}

void FUN_001ce9c0(void)
{
  if (!game_in_progress())
    return;
  {
    short player_index;
    char *flags = (char *)0x4eaf59;
    for (player_index = 0; player_index < 4; player_index++) {
      if (player_index < 0 || player_index >= 4) {
        display_assert((char *)0x2c12f4, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                       0x430, 1);
        system_exit(-1);
      }
      {
        int pi = local_player_get_player_index(player_index);
        if (pi == -1)
          continue;
        void *camera = observer_get_camera((unsigned short)player_index);
        if (!camera) {
          display_assert((char *)0x266e9c, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                         0x4ef, 1);
          system_exit(-1);
        }
        {
          char was_outside = flags[-1];
          char outside;
          outside = FUN_0018f3e0(camera + 0xc, camera, (int16_t *)(camera + 0x2c));
          flags[0] = outside;
          if (outside != was_outside) {
            void *globals = game_globals_get();
            globals = (char *)globals + 0xf8;
            if (outside) {
              if (*(int *)globals > 0) {
                char *elem = (char *)tag_block_get_element(globals, 0, 0x10);
                if (*(int *)(elem + 0xc) != -1)
                  sound_start(*(int *)(elem + 0xc), 0, 0, 0, 0, -1);
              }
            } else if (*(int *)globals > 1) {
              char *elem = (char *)tag_block_get_element(globals, 1, 0x10);
              if (*(int *)(elem + 0xc) != -1)
                sound_start(*(int *)(elem + 0xc), 0, 0, 0, 0, -1);
            }
          }
          csmemcpy((char *)sound_listener_get(player_index) + 0x2c, camera + 0x2c,
                   0xc);
        }
      }
    }
  }
}

short FUN_001cebb0(int sound_handle)
{
  char *entry = (char *)datum_get(*(data_t **)0x4fdba4, sound_handle);
  int16_t channel = *(int16_t *)(entry + 0x8c);
  if (channel != -1) {
    if (channel < 0 || channel >= *(int16_t *)0x4eb0b4) {
      display_assert((char *)0x2c1294, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                     0x428, 1);
      system_exit(-1);
    }
    if (*(int *)(0x4fc3a0 + (int)channel * 0x18) != sound_handle) {
      display_assert((char *)0x2c1890, "c:\\halo\\SOURCE\\sound\\sound_manager.c",
                     0x6d0, 1);
      system_exit(-1);
    }
    return channel;
  }
  {
    void *tag = tag_get(0x736e6421, *(int *)(entry + 8));
    void *class_def = sound_class_get_definition(*(int16_t *)((char *)tag + 4));
    if (!((char *)class_def)[8] || *(int *)(entry + 0xc) == -1)
      return -1;
    {
      short i;
      short count = *(int16_t *)0x4eb0b4;
      for (i = 0; i < count; i++) {
        int other = *(int *)(0x4fc3a0 + (int)i * 0x18);
        if (other == -1)
          continue;
        {
          char *other_entry = (char *)datum_get(*(data_t **)0x4fdba4, other);
          if (*(int *)(other_entry + 0xc) != *(int *)(entry + 0xc))
            continue;
          void *other_tag = tag_get(0x736e6421, *(int *)(other_entry + 8));
          void *other_class =
            sound_class_get_definition(*(int16_t *)((char *)other_tag + 4));
          if (((char *)other_class)[8])
            return FUN_001cd8b0(sound_handle);
        }
      }
    }
    return -1;
  }
}

void FUN_001cf100(void)
{
  int index = data_next_index(*(data_t **)0x4fdba0, -1);
  while (index != -1) {
    char *entry = (char *)datum_get(*(data_t **)0x4fdba0, index);
    void *lsnd = tag_get(0x6c736e64, *(int *)(entry + 4));
    if (entry[0x4c] != *(char *)0x4eaf54) {
      datum_delete(*(data_t **)0x4fdba0, index);
    } else if (*(int16_t *)(entry + 0x52) != 2) {
      char *tracks = (char *)lsnd + 0x48;
      int i;
      for (i = 0; i < *(int *)tracks; i++) {
        char *elem = (char *)tag_block_get_element(tracks, i, 0x68);
        if (*(int *)(entry + 0x54 + i * 4) >= *(int *)0x4eaf4c ||
            *(int *)(elem + 0xc) == -1)
          continue;
        {
          char flags = *(char *)(elem + 0x1c);
          if ((flags & 1) && entry[0x4d])
            continue;
          if ((flags & 2) && !entry[0x4d])
            continue;
          {
            float out[3];
            float params[3];
            int16_t mode = *(int16_t *)(entry + 0xc) == 0 ? 2 : 1;
            params[0] = mode;
            params[1] = *(float *)(elem + 0x18);
            params[2] = *(float *)(elem + 0x10);
            FUN_001cd390(elem, out);
            FUN_001cc200(index, params, out);
            sound_start(*(int *)(elem + 0xc), out, *(int *)(entry + 8),
                        *(int *)(entry + 0x10), 0, 0);
          }
        }
      }
    }
    index = data_next_index(*(data_t **)0x4fdba0, index);
  }
}

void FUN_001cf360(void)
{
  int index = data_next_index(*(data_t **)0x4fdba4, -1);
  while (index != -1) {
    char *entry = (char *)datum_get(*(data_t **)0x4fdba4, index);
    if (*(int *)(entry + 0x84) > *(int *)0x4eaf4c)
      break;
    if (*(int16_t *)(entry + 0x8c) == -1) {
      void *tag = tag_get(0x736e6421, *(int *)(entry + 8));
      char *perm = (char *)tag_block_get_element((char *)tag + 0x98,
                                                 *(int16_t *)(entry + 0x8e), 0x48);
      perm = (char *)tag_block_get_element(perm + 0x3c, *(int16_t *)(entry + 0x90), 0x7c);
          if (!sound_cache_request_sound(perm, 0, 1, 0)) {
        void *tag2 = tag_get(0x736e6421, *(int *)(entry + 8));
        int16_t enc = *(int16_t *)((char *)tag2 + 4);
        void *class_def = sound_class_get_definition(enc);
        switch (*(int16_t *)((char *)class_def + 0xc)) {
        case 0: {
          char *pr = (char *)tag_block_get_element((char *)tag2 + 0x98,
                                                    *(int16_t *)(entry + 0x8e), 0x48);
          char *pe = (char *)tag_block_get_element(pr + 0x3c,
                                                   *(int16_t *)(entry + 0x90), 0x7c);
          if (*(int16_t *)(pe + 0x3a) == -1)
            *(int16_t *)(pe + 0x3a) = *(int16_t *)(entry + 0x90);
          sound_stop_channel(index);
          break;
        }
        case 1:
          sound_stop_channel(index);
          break;
        default:
          display_assert((char *)0, "c:\\halo\\SOURCE\\sound\\sound_manager.c", 0x679,
                         1);
          system_exit(-1);
        }
      }
    }
    index = data_next_index(*(data_t **)0x4fdba4, index);
  }
}

void FUN_001cf820(void **out)
{
  *out = (void *)0x32fce4;
}
/* --- sound_manager.obj orphan shells (2026-07-26) --- */

/* 0x1ac180 */
char FUN_001ac180(int actor, int anim_tag, void *entry, int do_flag)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp ecx, -1 -> je 0x1ac2de */
  /* cmp edi, -1 -> je 0x1ac2db */
  object_get_and_verify_type(0, 0);
  tag_get('tinu', 0);
  tag_get('rtna', 0);
  FUN_00120cb0(0, (char *)(uintptr_t)ecx);
  /* cmp (int16_t)eax, 0xffff -> je 0x1ac2c1 */
  model_animation_choose_random(0, 0, eax);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  /* cmp (int16_t)eax, 1 -> je 0x1ac2d9 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x1ac2d9 */
  /* relift: cmp byte ptr [esi + 0x253], 0x1c -> jne 0x1ac27e */
  /* cmp (int16_t)eax, 0xffff -> je 0x1ac27e */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 180);
  /* relift: cmp (int16_t)ecx, word ptr [edx + 0x42] -> jne 0x1ac27e */
  /* cmp edx, ebx -> jne 0x1ac279 */
  /* cmp (int16_t)ecx, (int16_t)eax -> jl 0x1ac2d9 */
  /* test (char)eax, (char)eax -> je 0x1ac293 */
  object_set_region_count(0, 0);
  unit_set_animation(0, 0, 0);
  object_update_children_recursive(0);
  tag_get_name(0);
  console_warning((char *)0x0029c71c);
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
