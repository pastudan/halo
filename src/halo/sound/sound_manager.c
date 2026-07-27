#include <stdint.h>
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
bool sound_can_play(int sound_tag_index )
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
void *sound_channel_get(short channel_index )
{
  assert_halt(channel_index >= 0 && channel_index < *(short *)0x4eb0b4);

  return (void *)(0x4fc3a0 + (int)channel_index * 0x18);
}

/* Return a pointer to the sound listener entry for a local player.
 * The listeners table lives at 0x4eaf58 with a stride of 0x44.
 * Asserts that listener_index is in [0, MAXIMUM_NUMBER_OF_LOCAL_PLAYERS). */
void *sound_listener_get(short listener_index )
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
int16_t sound_check_promotion(int sound_tag_index )
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
void sound_collect_like_sounds(int sound_handle, void *summary )
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
 *   2. Call sound_channel_stop (0x1cc140, ) to release cache-sound
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
void sound_stop_channel(int sound_handle )
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
 *   (0x1cbd30, ).  If the like_source_count has reached
 *   max_source_instance_count, searches the source channel list for the
 *   oldest to steal.  Otherwise, if the like_definition_count has reached
 *   max_instance_count, searches the definition channel list.  If a
 *   stealable channel is found, stops its sound; if not, stops our own.
 *
 * sound_handle passed in EAX (register argument). */
void sound_start_next_looping_permutation(int sound_handle )
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
int16_t sound_allocate_channel(void *source , float priority)
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
 *   sound_tag_handle  () — tag index of the sound definition (snd!)
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
int sound_create_looping_entry(int sound_tag_handle ,
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
 *      ). If the computed attenuation and the sound entry's target
 *      attenuation (sound_entry+0xa0) both reach 0.0f, the sound has
 *      faded out — stop it via sound_stop_channel (0x1cca60, )
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
 *          sound_listener_get (0x1cbac0, ) and transform the
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
/* FUN_001ac030 (0x1ac030) — readable C lift. */
void FUN_001ac030(int unit_handle, char flag)
{
  if (unit_handle == -1)
    return;
  unsigned char *obj = (unsigned char *)object_get_and_verify_type(unit_handle, 3);
  unsigned int *flags = (unsigned int *)(obj + 0x1b4);
  if (!flag)
    *flags |= 0x10000u;
  else
    *flags &= ~0x10000u;
}

/* FUN_001ac070 (0x1ac070) — readable C lift. */
void FUN_001ac070(int unit_handle, char flag)
{
  if (unit_handle == -1)
    return;
  unsigned char *obj = (unsigned char *)object_get_and_verify_type(unit_handle, 3);
  obj[0x258] = (unsigned char)flag;
  object_set_region_count(unit_handle, 6);
}

/* FUN_001ac0a0 (0x1ac0a0) — readable C lift. */
void FUN_001ac0a0(int unit_handle, char flag)
{
  if (unit_handle == -1)
    return;
  unsigned char *obj = (unsigned char *)object_get_and_verify_type(unit_handle, 3);
  unsigned int *flags = (unsigned int *)(obj + 0x1b4);
  if (flag)
    *flags |= 0x4000u;
  else
    *flags &= ~0x4000u;
}

/* FUN_001AC0E0 (0x1ac0e0) — readable C lift.
 * Early exits use xorw ax,ax (preserve EAX high bits from prior value). */
int FUN_001AC0E0(int unit_handle)
{
  char *unit;
  void *antr;
  void *elem;
  int value;

  if (unit_handle == -1)
    return (int)((unsigned int)unit_handle & 0xffff0000u);
  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  if (*(unsigned char *)(unit + 0x253) != 0x1c)
    return (int)((unsigned int)(size_t)unit & 0xffff0000u);
  antr = tag_get(0x616e7472, *(int *)(unit + 0x7c));
  elem = tag_block_get_element((char *)antr + 0x74, *(short *)(unit + 0x80), 0xb4);
  value = (int)*(short *)((char *)elem + 0x22) - (int)*(short *)(unit + 0x82) - 2;
  if (value <= 0)
    return 0;
  return value;
}



/* FUN_001ac150 (0x1ac150) — readable C lift. */
char FUN_001ac150(int unit_handle)
{
  if (unit_handle == -1)
    return 0;
  unsigned char *obj = (unsigned char *)object_get_and_verify_type(unit_handle, 3);
  return obj[0x253] == 0x1c;
}

/* sound_dispose (0x1ac350) — readable C lift. */
int16_t sound_dispose(int unit_handle)
{
  char *unit;
  int16_t i;
  int weapon;

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  for (i = 0; i < 4; i++) {
    weapon = *(int *)(unit + 0x2a8 + (int)i * 4);
    if (weapon != -1 && weapon_must_be_readied(weapon))
      return i;
  }
  return -1;
}

/* FUN_001ac3b0 (0x1ac3b0) — readable C lift. */
char FUN_001ac3b0(int unit_handle, int weapon_handle)
{
  unsigned char *obj = (unsigned char *)object_get_and_verify_type(unit_handle, 3);
  int *slots = (int *)(obj + 0x2a8);
  for (int i = 0; i < 4; i++) {
    if (slots[i] == weapon_handle)
      return 1;
  }
  return 0;
}

/* FUN_001be100 (0x1be100) — readable C lift. */
void FUN_001be100(void *cache_entry)
{
  int handle = *(int *)((char *)cache_entry + 0x2c);
  unsigned char *d = (unsigned char *)datum_get(*(void **)0x4e9368, handle);
  if (d[5] < 0xff)
    d[5] = (unsigned char)(d[5] + 1);
  else
    *(unsigned short *)0x5054ea = (unsigned short)(*(unsigned short *)0x5054ea + 1);
}

/* FUN_001be140 (0x1be140) — readable C lift. */
void FUN_001be140(void *cache_entry)
{
  int handle = *(int *)((char *)cache_entry + 0x2c);
  unsigned char *d = (unsigned char *)datum_get(*(void **)0x4e9368, handle);
  if (d[5])
    d[5] = (unsigned char)(d[5] - 1);
  else
    *(unsigned short *)0x5054ea = (unsigned short)(*(unsigned short *)0x5054ea + 1);
}

/* FUN_001be170 (0x1be170) — readable C lift. */
char FUN_001be170(int cache_handle)
{
  unsigned char *d = (unsigned char *)datum_get(*(void **)0x4e9368, cache_handle);
  if (!d[2])
    return 1;
  if (d[4])
    return 1;
  if (d[5])
    return 1;
  return 0;
}

/* sound_try_and_get (0x1cb960) — readable C lift. */
char sound_try_and_get(int sound_index)
{
  return datum_absolute_index_to_index(*(void **)0x4fdba4, sound_index) != 0;
}

void sound_enable(char enabled)
{
  *(char *)0x4eaf41 = enabled;
}

/* sound_scripted_dialog_is_playing (0x1cb990) — readable C lift. */
char sound_scripted_dialog_is_playing(void)
{
  return game_time_get() < *(int *)0x4eaf44;
}

/* sound_manager_set_sound_environment (0x1cb9b0) — readable C lift. */
void sound_manager_set_sound_environment(void *environment)
{
  unsigned int *dst = (unsigned int *)0x4eb068;
  unsigned int *src = (unsigned int *)environment;
  int i;
  for (i = 0; i < 0x12; i++) dst[i] = src[i];
}

/* FUN_001cb9d0 (0x1cb9d0) — readable C lift. */
void FUN_001cb9d0(void)
{
  int now = (int)system_milliseconds();
  float dt = (float)(now - *(int *)0x4eaf4c) * *(float *)0x25bc08;
  *(int *)0x4eaf4c = now;
  *(float *)0x4eaf50 = dt;
}

/* FUN_001cba00 (0x1cba00) — readable C lift: scale * lerp(a,b,t). */
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

static float __attribute__((unused)) sound_source_distance(void *source)
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

static float __attribute__((unused)) sound_listener_distance(int channel_index, void *source)
{
  return xbox_sqrtf(sound_listener_distance_sq(channel_index, source));
}

/* FUN_001be1b0 (0x1be1b0) — readable C lift. */
void FUN_001be1b0(int cache_handle)
{
  extern char DAT_002b9288[];
  extern char DAT_002b93e0[];
  extern char DAT_002b93a8[];
  char *entry;
  char *tag;
  char *msg;

  entry = (char *)datum_get(*(data_t **)0x4e9368, cache_handle);
  if (entry[4] != 0 || entry[5] != 0) {
    tag = *(char **)(entry + 8);
    msg = csprintf(
        (char *)0x5ab100,
        DAT_002b93e0,
        tag_get_name(*(int *)(tag + 0x3c)));
    display_assert(msg, DAT_002b9288, 0x141, 1);
    system_exit(-1);
  }
  tag = *(char **)(entry + 8);
  if (*(int *)(tag + 0x2c) != cache_handle) {
    display_assert(DAT_002b93a8, DAT_002b9288, 0x144, 1);
    system_exit(-1);
  }
  tag = *(char **)(entry + 8);
  *(int *)(tag + 0x2c) = -1;
  tag = *(char **)(entry + 8);
  *(int *)(tag + 0x30) = 0;
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

/* FUN_001be2b0 (0x1be2b0) — XBE naked draft (batch 277). */
#if defined(__clang__)
static int (*const b1be2b0_c11de10)(void *cache, unsigned int size) = FUN_0011de10;
static int (*const b1be2b0_c11da00)(void *lruv, int block_index) = lruv_block_get_address;
static int (*const b1be2b0_c119570)(data_t *data, int handle) = data_new_datum;
static void *(*const b1be2b0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b1be2b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1be2b0_exitfn)(int) = system_exit;
static short (*const b1be2b0_c1bc9e0)(int param_1, int offset, unsigned int size, int buffer, char *completion_flag, char async_flag) = cache_file_read;
static unsigned int (*const b1be2b0_c8e370)(void) = system_milliseconds;
static void (*const b1be2b0_ce3a10)(void *color, const char *format, const char *text) = terminal_output;
static void (*const b1be2b0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b1be2b0_c11db90)(const char *path, const char *tag_name, int a3, void *cache, void *fn1, void *fn2) = FUN_0011db90;

__attribute__((naked, noinline))
void FUN_001be2b0(void *perm_entry __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x40(%%esi), %%eax\n\t"
      "movl 0x4e9370, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c11de10]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_001be2b0_2\n\t"
      "movl 0x4e9370, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c11da00]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl 0x4e936c, %%ebx\n\t"
      "movl 0x4e9368, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c119570]\n\t"
      "movl 0x4e9368, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "je .LFUN_001be2b0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x170\n\t"
      "pushl $0x2b9288\n\t"
      "pushl $0x2b94cc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001be2b0_1:\n\t"
      "pushl $0\n\t"
      "movl %%edi, 0x2c(%%esi)\n\t"
      "movl %%ebx, 0x30(%%esi)\n\t"
      "movl %%esi, 0x8(%%eax)\n\t"
      "movl 0x40(%%esi), %%edx\n\t"
      "movl 0x34(%%esi), %%ecx\n\t"
      "addl $2, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x48(%%esi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1bc9e0]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001be2b0_2:\n\t"
      "call *%[c8e370]\n\t"
      "subl 0x4e9374, %%eax\n\t"
      "cmpl $0x2710, %%eax\n\t"
      "jbe .LFUN_001be2b0_3\n\t"
      "movl 0x2ee6f4, %%edx\n\t"
      "pushl $0x2b9488\n\t"
      "pushl %%edx\n\t"
      "call *%[ce3a10]\n\t"
      "pushl $0x2b9440\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movl 0x2ee6f4, %%eax\n\t"
      "pushl $0x2b9488\n\t"
      "pushl %%eax\n\t"
      "call *%[ce3a10]\n\t"
      "movl 0x4e9370, %%ecx\n\t"
      "movl 0x40(%%esi), %%edx\n\t"
      "pushl $0x1be270\n\t"
      "pushl $0x18ef30\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl $0x2b942c\n\t"
      "call *%[c11db90]\n\t"
      "addl $0x30, %%esp\n\t"
      "call *%[c8e370]\n\t"
      "movl %%eax, 0x4e9374\n\t"
      ".LFUN_001be2b0_3:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c11de10] "m"(b1be2b0_c11de10), [c11da00] "m"(b1be2b0_c11da00), [c119570] "m"(b1be2b0_c119570), [dget] "m"(b1be2b0_dget), [assert] "m"(b1be2b0_assert), [exitfn] "m"(b1be2b0_exitfn), [c1bc9e0] "m"(b1be2b0_c1bc9e0), [c8e370] "m"(b1be2b0_c8e370), [ce3a10] "m"(b1be2b0_ce3a10), [c8f390] "m"(b1be2b0_c8f390), [c11db90] "m"(b1be2b0_c11db90)
      : "memory");
}
#else
#error "FUN_001be2b0: clang naked draft required"
#endif


/* FUN_001c7b40 (0x1c7b40) — XBE naked draft (batch 264). */
#if defined(__clang__)
static void * (*const b1c7b40_c18e3c0)(void) = global_scenario_get;
static void *(*const b1c7b40_memset)(void *, int, unsigned int) = csmemset;
static int (*const b1c7b40_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void * (*const b1c7b40_c8a4e0)(unsigned __int16 local_player_index) = observer_get_camera;
static uint8_t (*const b1c7b40_c193870)(void *bsp, int16_t from_cluster, int16_t to_cluster) = structure_bsp_cluster_sound_encoding;

__attribute__((naked, noinline))
void FUN_001c7b40(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c18e3c0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x134(%%ebx), %%eax\n\t"
      "addl $0x1f, %%eax\n\t"
      "sarl $5, %%eax\n\t"
      "shll $2, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0x5054a0\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      ".LFUN_001c7b40_1:\n\t"
      "pushl %%esi\n\t"
      "call *%[cba3c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001c7b40_5\n\t"
      "pushl %%esi\n\t"
      "call *%[c8a4e0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $-1, 0x10(%%eax)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "je .LFUN_001c7b40_5\n\t"
      "movl 0x134(%%ebx), %%ecx\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .LFUN_001c7b40_5\n\t"
      "xorl %%esi, %%esi\n\t"
      "jmp .LFUN_001c7b40_3\n\t"
      ".LFUN_001c7b40_2:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_001c7b40_3:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x10(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c193870]\n\t"
      "movzbl %%al, %%edx\n\t"
      "andl $0xffffff7f, %%edx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "fmuls 0x256148\n\t"
      "fcomps 0x2642a0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_001c7b40_4\n\t"
      "movl %%esi, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      "sarl $5, %%eax\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl 0x5054a0(,%%eax,4), %%ecx\n\t"
      "leal 0x5054a0(,%%eax,4), %%eax\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      ".LFUN_001c7b40_4:\n\t"
      "movl 0x134(%%ebx), %%eax\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%esi\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jl .LFUN_001c7b40_2\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      ".LFUN_001c7b40_5:\n\t"
      "incl %%esi\n\t"
      "cmpw $4, %%si\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "jl .LFUN_001c7b40_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e3c0] "m"(b1c7b40_c18e3c0), [memset] "m"(b1c7b40_memset), [cba3c0] "m"(b1c7b40_cba3c0), [c8a4e0] "m"(b1c7b40_c8a4e0), [c193870] "m"(b1c7b40_c193870)
      : "memory");
}
#else
#error "FUN_001c7b40: clang naked draft required"
#endif


/* FUN_001c8700 (0x1c8700) — XBE naked draft (batch 263). */
#if defined(__clang__)


__attribute__((naked, noinline))
int FUN_001c8700(void *state __attribute__((unused)), int sample_count __attribute__((unused)), int16_t *out __attribute__((unused)), void *track __attribute__((unused)), void *bitstream __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "leal 0x8(%%ecx), %%eax\n\t"
      "subl $8, %%edi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%edi, 0xc(%%ebp)\n\t"
      "leal (%%edx,%%edx,1), %%eax\n\t"
      "je .LFUN_001c8700_17\n\t"
      "movl 0x18(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "pushl %%ebx\n\t"
      "je .LFUN_001c8700_2\n\t"
      "cmpl $0, (%%edi)\n\t"
      "jne .LFUN_001c8700_1\n\t"
      "movl %%edx, (%%edi)\n\t"
      "movw 0x4(%%ecx), %%cx\n\t"
      "movw %%cx, 0x8(%%edi)\n\t"
      "movw $0, 0xa(%%edi)\n\t"
      ".LFUN_001c8700_1:\n\t"
      "movswl 0x8(%%edi), %%edx\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movw 0xa(%%edi), %%si\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "sarl $1, %%eax\n\t"
      "subl %%eax, %%ebx\n\t"
      "addl %%eax, %%edx\n\t"
      "movl (%%edi), %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movb %%cl, %%al\n\t"
      "notb %%al\n\t"
      "movl %%ebx, 0xc(%%ebp)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "andb $1, %%al\n\t"
      "jmp .LFUN_001c8700_3\n\t"
      ".LFUN_001c8700_2:\n\t"
      "movswl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "xorl %%esi, %%esi\n\t"
      "movb $1, %%al\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      ".LFUN_001c8700_3:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_001c8700_15\n\t"
      ".LFUN_001c8700_4:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_001c8700_15\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_001c8700_15\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movb (%%edx), %%dl\n\t"
      "movswl %%si, %%ecx\n\t"
      "movl 0x2bc710(,%%ecx,4), %%esi\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%esi, %%ecx\n\t"
      "sarl $3, %%ecx\n\t"
      "testb %%al, %%al\n\t"
      "movb $4, %%bl\n\t"
      "je .LFUN_001c8700_5\n\t"
      "sarb $4, %%dl\n\t"
      ".LFUN_001c8700_5:\n\t"
      "andb $0xf, %%dl\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_001c8700_6:\n\t"
      "testb %%dl, %%bl\n\t"
      "je .LFUN_001c8700_7\n\t"
      "addl %%esi, %%ecx\n\t"
      ".LFUN_001c8700_7:\n\t"
      "sarb $1, %%bl\n\t"
      "sarl $1, %%esi\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_001c8700_6\n\t"
      "testb $8, %%dl\n\t"
      "je .LFUN_001c8700_8\n\t"
      "negl %%ecx\n\t"
      ".LFUN_001c8700_8:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "addl %%esi, %%ecx\n\t"
      "cmpl $0xffff8000, %%ecx\n\t"
      "jge .LFUN_001c8700_9\n\t"
      "movl $0xffff8000, 0x8(%%ebp)\n\t"
      "jmp .LFUN_001c8700_10\n\t"
      ".LFUN_001c8700_9:\n\t"
      "cmpl $0x7fff, %%ecx\n\t"
      "movl $0x7fff, 0x8(%%ebp)\n\t"
      "jg .LFUN_001c8700_10\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      ".LFUN_001c8700_10:\n\t"
      "movsbl %%dl, %%ecx\n\t"
      "movl 0x2bc6d0(,%%ecx,4), %%edx\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "addl %%edx, %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jge .LFUN_001c8700_11\n\t"
      "xorl %%esi, %%esi\n\t"
      "jmp .LFUN_001c8700_12\n\t"
      ".LFUN_001c8700_11:\n\t"
      "cmpl $0x58, %%ecx\n\t"
      "movl $0x58, %%esi\n\t"
      "jg .LFUN_001c8700_12\n\t"
      "movl %%ecx, %%esi\n\t"
      ".LFUN_001c8700_12:\n\t"
      "movw 0x8(%%ebp), %%dx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "testb %%al, %%al\n\t"
      "sete %%al\n\t"
      "testb %%al, %%al\n\t"
      "movw %%dx, (%%ecx)\n\t"
      "je .LFUN_001c8700_13\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "incl %%edx\n\t"
      "decl %%ecx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      ".LFUN_001c8700_13:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "addl $2, %%ecx\n\t"
      "decl %%ebx\n\t"
      "decl %%edx\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movl %%edx, 0x14(%%ebp)\n\t"
      "je .LFUN_001c8700_14\n\t"
      "incl 0x4(%%edi)\n\t"
      ".LFUN_001c8700_14:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_001c8700_4\n\t"
      ".LFUN_001c8700_15:\n\t"
      "testl %%edi, %%edi\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_001c8700_16\n\t"
      "movw 0x8(%%ebp), %%dx\n\t"
      "movw %%dx, 0x8(%%edi)\n\t"
      "movw %%si, 0xa(%%edi)\n\t"
      ".LFUN_001c8700_16:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      ".LFUN_001c8700_17:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_001c8700: clang naked draft required"
#endif


/* sound_is_active (0x1c88a0) — readable C lift. */
void sound_is_active(int sound_index)
{
  FUN_00118be0((void *)0x32ecf4, (void *)(intptr_t)sound_index, 1);
}

/* FUN_001c8ee0 (0x1c8ee0) — readable C lift. */
void FUN_001c8ee0(void *pitch_range)
{
  unsigned char *p = (unsigned char *)pitch_range;
  unsigned short dx = *(unsigned short *)(p + 0x2c);
  unsigned int mask = (1u << (dx & 0xff)) - 1u;
  unsigned int bits = ~*(unsigned int *)(p + 0x34);
  if (bits & mask)
    return;
  *(unsigned int *)(p + 0x34) = 0;
  if ((short)dx > 1)
    *(unsigned int *)(p + 0x34) = 1u << p[0x38];
}

/* FUN_001cb1a0 (0x1cb1a0) — readable C lift. */
void FUN_001cb1a0(int channel_index, int param)
{
  short ch;
  (void)param;
  ch = sound_dsound_channel_resolve(channel_index);
  if (ch != (short)0xffff)
    FUN_001cb0c0((int)ch);
}
/* FUN_001cb1d0 (0x1cb1d0) — readable C lift. */
void FUN_001cb1d0(int channel_index, int a, int b, int c, int d, int e)
{
  short ch = sound_dsound_channel_resolve(channel_index);
  if (ch == (short)0xffff)
    return;
  FUN_001cadd0((int)ch, a, b, c, d, e);
}
/* FUN_001cb210 (0x1cb210) — XBE naked draft (batch 272). */
#if defined(__clang__)
static void * (*const b1cb210_c1c9290)(short index) = sound_dsound_channel_get;
static int (*const b1cb210_c1c90e0)(int codec_index) = sound_dsound_get_sample_rate;
static void *(*const b1cb210_memset)(void *, int, unsigned int) = csmemset;
static void (*const b1cb210_c2060f8)(void) = (void *)IDirectSound_CreateSoundStream;
static void (*const b1cb210_c1cadd0)(int a, int b, int c, int d, int e, int f) = FUN_001cadd0;
static void (*const b1cb210_c204c79)(void) = (void *)IDirectSound_GetSpeakerConfig;
static int (*const b1cb210_c1c9130)(float gain, int ceiling) = sound_dsound_gain_to_volume;
static void (*const b1cb210_c205bd8)(void) = (void *)IDirectSoundStream_SetMixBins;
static void (*const b1cb210_c2052de)(void) = (void *)IDirectSoundStream_SetMixBinVolumes_12;
static void (*const b1cb210_c1ca5e0)(float *properties, short channel_index, int update_only) = sound_dsound_update_channel_properties;
static void (*const b1cb210_c1c98f0)(int hresult, const char *message, ...) = sound_dsound_log_error;

__attribute__((naked, noinline))
char FUN_001cb210(short channel_index __attribute__((unused)), unsigned char flags __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x80, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c1c9290]\n\t"
      "movl %%eax, %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb $8, %%bl\n\t"
      "movw %%bx, 0x38(%%edi)\n\t"
      "movw $0xffff, 0x2(%%edi)\n\t"
      "movb $0, 0x6(%%edi)\n\t"
      "movl %%eax, 0x68(%%edi)\n\t"
      "movl %%eax, 0x6c(%%edi)\n\t"
      "movl $4, %%esi\n\t"
      "jne .LFUN_001cb210_1\n\t"
      "movl 0x2bcc1c, %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movw $1, -0x1c(%%ebp)\n\t"
      "movw $0x10, -0xe(%%ebp)\n\t"
      "movw $2, -0x1a(%%ebp)\n\t"
      "movw %%si, -0x10(%%ebp)\n\t"
      "shll $2, %%eax\n\t"
      "jmp .LFUN_001cb210_2\n\t"
      ".LFUN_001cb210_1:\n\t"
      "testb $2, %%bl\n\t"
      "movl $0, %%ecx\n\t"
      "setne %%cl\n\t"
      "movw $0x69, -0x1c(%%ebp)\n\t"
      "movw %%si, -0xe(%%ebp)\n\t"
      "incl %%ecx\n\t"
      "movw %%cx, -0x1a(%%ebp)\n\t"
      "movl -0x1a(%%ebp), %%eax\n\t"
      "leal (%%eax,%%eax,8), %%edx\n\t"
      "movl %%ebx, %%eax\n\t"
      "shrl $2, %%eax\n\t"
      "andl $1, %%eax\n\t"
      "shll $2, %%edx\n\t"
      "pushl %%eax\n\t"
      "movw %%dx, -0x10(%%ebp)\n\t"
      "call *%[c1c90e0]\n\t"
      "movzwl -0x10(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "shrl $6, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "imull %%ecx, %%eax\n\t"
      "movw $2, -0xc(%%ebp)\n\t"
      "movw $0x40, -0xa(%%ebp)\n\t"
      ".LFUN_001cb210_2:\n\t"
      "pushl $0x18\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "call *%[memset]\n\t"
      "movswl 0x8(%%ebp), %%ecx\n\t"
      "movl %%esi, -0x30(%%ebp)\n\t"
      "movl %%ebx, %%esi\n\t"
      "andl $1, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%si, %%si\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movl $0, -0x34(%%ebp)\n\t"
      "movl $0x1ca970, -0x28(%%ebp)\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "je .LFUN_001cb210_3\n\t"
      "movl $0x10, -0x34(%%ebp)\n\t"
      ".LFUN_001cb210_3:\n\t"
      "movl 0x50545c, %%eax\n\t"
      "pushl $0\n\t"
      "addl $0x70, %%edi\n\t"
      "pushl %%edi\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c2060f8]\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001cb210_9\n\t"
      "testw %%si, %%si\n\t"
      "je .LFUN_001cb210_4\n\t"
      "pushl $0x2c\n\t"
      "leal -0x60(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "movl 0x31fc3c, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "pushl $0\n\t"
      "movl %%eax, -0x54(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "movl %%ecx, -0x50(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "leal -0x60(%%ebp), %%ebx\n\t"
      "movl %%edx, -0x4c(%%ebp)\n\t"
      "call *%[c1cadd0]\n\t"
      "addl $0x20, %%esp\n\t"
      "jmp .LFUN_001cb210_8\n\t"
      ".LFUN_001cb210_4:\n\t"
      "movl 0x50545c, %%edx\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c204c79]\n\t"
      "testl $0x10000, -0x8(%%ebp)\n\t"
      "je .LFUN_001cb210_6\n\t"
      "testb $2, %%bl\n\t"
      "pushl $0\n\t"
      "jne .LFUN_001cb210_5\n\t"
      "pushl $0x3f000000\n\t"
      "movl $7, %%esi\n\t"
      "call *%[c1c9130]\n\t"
      "pushl $0\n\t"
      "pushl $0x3f000000\n\t"
      "movl %%eax, -0x54(%%ebp)\n\t"
      "call *%[c1c9130]\n\t"
      "pushl $0\n\t"
      "pushl $0x3f000000\n\t"
      "movl %%eax, -0x50(%%ebp)\n\t"
      "call *%[c1c9130]\n\t"
      "addl $0x18, %%esp\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "jmp .LFUN_001cb210_7\n\t"
      ".LFUN_001cb210_5:\n\t"
      "pushl $0x3f800000\n\t"
      "movl $0x1833, %%esi\n\t"
      "call *%[c1c9130]\n\t"
      "pushl $0\n\t"
      "pushl $0x3f800000\n\t"
      "movl %%eax, -0x54(%%ebp)\n\t"
      "call *%[c1c9130]\n\t"
      "pushl $0\n\t"
      "pushl $0x3f000000\n\t"
      "movl %%eax, -0x50(%%ebp)\n\t"
      "call *%[c1c9130]\n\t"
      "pushl $0\n\t"
      "pushl $0x3f000000\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "call *%[c1c9130]\n\t"
      "pushl $0\n\t"
      "pushl $0x3f000000\n\t"
      "movl %%eax, -0x48(%%ebp)\n\t"
      "call *%[c1c9130]\n\t"
      "pushl $0\n\t"
      "pushl $0x3f000000\n\t"
      "movl %%eax, -0x44(%%ebp)\n\t"
      "call *%[c1c9130]\n\t"
      "addl $0x30, %%esp\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "jmp .LFUN_001cb210_7\n\t"
      ".LFUN_001cb210_6:\n\t"
      "testb $2, %%bl\n\t"
      "jne .LFUN_001cb210_8\n\t"
      "pushl $0\n\t"
      "pushl $0x3f000000\n\t"
      "movl $3, %%esi\n\t"
      "call *%[c1c9130]\n\t"
      "pushl $0\n\t"
      "pushl $0x3f000000\n\t"
      "movl %%eax, -0x54(%%ebp)\n\t"
      "call *%[c1c9130]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, -0x50(%%ebp)\n\t"
      ".LFUN_001cb210_7:\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c205bd8]\n\t"
      "movl (%%edi), %%edx\n\t"
      "leal -0x54(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c2052de]\n\t"
      ".LFUN_001cb210_8:\n\t"
      "pushl $0x20\n\t"
      "leal -0x80(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "call *%[memset]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "leal -0x80(%%ebp), %%ebx\n\t"
      "movl $0x3f800000, -0x80(%%ebp)\n\t"
      "movl $0x3f800000, -0x7c(%%ebp)\n\t"
      "call *%[c1ca5e0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001cb210_9:\n\t"
      "pushl $0x2c114c\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1c98f0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1c9290] "m"(b1cb210_c1c9290), [c1c90e0] "m"(b1cb210_c1c90e0), [memset] "m"(b1cb210_memset), [c2060f8] "m"(b1cb210_c2060f8), [c1cadd0] "m"(b1cb210_c1cadd0), [c204c79] "m"(b1cb210_c204c79), [c1c9130] "m"(b1cb210_c1c9130), [c205bd8] "m"(b1cb210_c205bd8), [c2052de] "m"(b1cb210_c2052de), [c1ca5e0] "m"(b1cb210_c1ca5e0), [c1c98f0] "m"(b1cb210_c1c98f0)
      : "memory");
}
#else
#error "FUN_001cb210: clang naked draft required"
#endif


/* FUN_001cb4c0 (0x1cb4c0) — XBE naked draft (batch 262). */
#if defined(__clang__)
static void (*const b1cb4c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1cb4c0_exitfn)(int) = system_exit;
static void (*const b1cb4c0_c206232)(void) = (void *)DirectSoundCreate;
static void (*const b1cb4c0_c204c5d)(void) = (void *)IDirectSound_GetCaps;
static void (*const b1cb4c0_c204d81)(void) = (void *)IDirectSound_SetDistanceFactor;
static void (*const b1cb4c0_c204e48)(void) = (void *)IDirectSound_SetRolloffFactor;
static void *(*const b1cb4c0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b1cb4c0_c204c95)(void) = (void *)IDirectSound_DownloadEffectsImage;
static void (*const b1cb4c0_c1c98f0)(int hresult, const char *message, ...) = sound_dsound_log_error;
static void (*const b1cb4c0_c204d41)(void) = (void *)IDirectSound_SetMixBinHeadroom;
static void (*const b1cb4c0_c2038df)(void) = (void *)DirectSoundUseFullHRTF;
static void (*const b1cb4c0_c1ca2b0)(void *buf) = FUN_001ca2b0;
static void * (*const b1cb4c0_c1c92f0)(short index) = sound_dsound_vchannel_get;
static char (*const b1cb4c0_c1cb210)(short channel_index, unsigned char flags) = FUN_001cb210;
static void (*const b1cb4c0_c1c9cf0)(void) = (void *)FUN_001c9cf0;
static void (*const b1cb4c0_c1c93f0)(void) = (void *)FUN_001c93f0;

__attribute__((naked, noinline))
char FUN_001cb4c0(void *driver_caps __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x50, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "xorb %%bl, %%bl\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpl %%esi, %%edi\n\t"
      "movb %%bl, 0x4fdbc0\n\t"
      "movb %%bl, 0x505484\n\t"
      "movl $0x3f800000, 0x505488\n\t"
      "movl %%esi, 0x505460\n\t"
      "jne .LFUN_001cb4c0_1\n\t"
      "pushl $1\n\t"
      "pushl $0xea\n\t"
      "pushl $0x2c0894\n\t"
      "pushl $0x280f94\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001cb4c0_1:\n\t"
      "pushl %%esi\n\t"
      "pushl $0x50545c\n\t"
      "pushl %%esi\n\t"
      "call *%[c206232]\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jl .LFUN_001cb4c0_20\n\t"
      "movl 0x50545c, %%ecx\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c204c5d]\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jl .LFUN_001cb4c0_19\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, 0x505450\n\t"
      "movl 0x50545c, %%eax\n\t"
      "movl %%edx, 0x50544c\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "pushl $0x4043126f\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, 0x505454\n\t"
      "movl %%edx, 0x505458\n\t"
      "call *%[c204d81]\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jl .LFUN_001cb4c0_18\n\t"
      "movl 0x50545c, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%ecx\n\t"
      "call *%[c204e48]\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jl .LFUN_001cb4c0_16\n\t"
      "pushl $0x34\n\t"
      "leal -0x50(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "movl 0x31fc3c, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x44(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x31fc44, %%ecx\n\t"
      "movl %%edx, -0x40(%%ebp)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movl (%%ecx), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3a5c\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "movl 0x50545c, %%ecx\n\t"
      "pushl $0x2bccf0\n\t"
      "pushl %%ecx\n\t"
      "movl $0x2c1220, -0x20(%%ebp)\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "movl $1, -0x4(%%ebp)\n\t"
      "call *%[c204c95]\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jge .LFUN_001cb4c0_2\n\t"
      "pushl $0x2c11fc\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1c98f0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001cb4c0_2:\n\t"
      "movl 0x50545c, %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0x7fffffff\n\t"
      "pushl %%edx\n\t"
      "call *%[c204d41]\n\t"
      "call *%[c2038df]\n\t"
      "leal -0x50(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ca2b0]\n\t"
      "leal 0xa(%%edi), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "xorl %%esi, %%esi\n\t"
      "movb $1, %%al\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      ".LFUN_001cb4c0_3:\n\t"
      "cmpw $0, (%%ecx)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jle .LFUN_001cb4c0_9\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_001cb4c0_4:\n\t"
      "incw 0x4fdbc2\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001cb4c0_7\n\t"
      "call *%[c1c92f0]\n\t"
      "testw %%bx, %%bx\n\t"
      "movl %%eax, %%edi\n\t"
      "jl .LFUN_001cb4c0_5\n\t"
      "cmpw $4, %%bx\n\t"
      "jl .LFUN_001cb4c0_6\n\t"
      ".LFUN_001cb4c0_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x1a6\n\t"
      "pushl $0x2c0894\n\t"
      "pushl $0x2c08f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001cb4c0_6:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movw %%bx, 0x2(%%edi)\n\t"
      "movw $0xffff, (%%edi)\n\t"
      "incl %%esi\n\t"
      "movb $1, %%al\n\t"
      "jmp .LFUN_001cb4c0_8\n\t"
      ".LFUN_001cb4c0_7:\n\t"
      "xorb %%al, %%al\n\t"
      ".LFUN_001cb4c0_8:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "incl %%edx\n\t"
      "cmpw (%%ecx), %%dx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "jl .LFUN_001cb4c0_4\n\t"
      ".LFUN_001cb4c0_9:\n\t"
      "incl %%ebx\n\t"
      "addl $2, %%ecx\n\t"
      "cmpw $4, %%bx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jl .LFUN_001cb4c0_3\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl $0x5053c6, %%edx\n\t"
      "subl %%ecx, %%edx\n\t"
      "movl $0xfffffffe, %%ebx\n\t"
      "xorl %%edi, %%edi\n\t"
      "subl %%ecx, %%ebx\n\t"
      "leal 0x2(%%ecx), %%esi\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "movl $4, 0x8(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_001cb4c0_10:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movw %%di, (%%edx,%%esi,1)\n\t"
      "cmpw %%bx, (%%esi)\n\t"
      "jle .LFUN_001cb4c0_14\n\t"
      "jmp .LFUN_001cb4c0_11\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_001cb4c0_11:\n\t"
      "incw 0x4fdfc4\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001cb4c0_12\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movw 0x32fcf8(%%ecx,%%esi,1), %%ax\n\t"
      "pushl %%edi\n\t"
      "call *%[c1cb210]\n\t"
      "addl $4, %%esp\n\t"
      "incl %%edi\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001cb4c0_12\n\t"
      "movb $1, %%al\n\t"
      "jmp .LFUN_001cb4c0_13\n\t"
      ".LFUN_001cb4c0_12:\n\t"
      "xorb %%al, %%al\n\t"
      ".LFUN_001cb4c0_13:\n\t"
      "incl %%ebx\n\t"
      "cmpw (%%esi), %%bx\n\t"
      "jl .LFUN_001cb4c0_11\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      ".LFUN_001cb4c0_14:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "addl $2, %%esi\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "jne .LFUN_001cb4c0_10\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001cb4c0_15\n\t"
      "call *%[c1c9cf0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001cb4c0_15\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "movb %%al, 0x4fdbc0\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001cb4c0_15:\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c1c93f0]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001cb4c0_16:\n\t"
      "pushl $0x2c11dc\n\t"
      ".LFUN_001cb4c0_17:\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1c98f0]\n\t"
      "addl $4, %%esp\n\t"
      "call *%[c1c93f0]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001cb4c0_18:\n\t"
      "pushl $0x2c11b8\n\t"
      "jmp .LFUN_001cb4c0_17\n\t"
      ".LFUN_001cb4c0_19:\n\t"
      "pushl $0x2c1194\n\t"
      "jmp .LFUN_001cb4c0_17\n\t"
      ".LFUN_001cb4c0_20:\n\t"
      "pushl $0x2c116c\n\t"
      "jmp .LFUN_001cb4c0_17\n\t"
      :
      : [assert] "m"(b1cb4c0_assert), [exitfn] "m"(b1cb4c0_exitfn), [c206232] "m"(b1cb4c0_c206232), [c204c5d] "m"(b1cb4c0_c204c5d), [c204d81] "m"(b1cb4c0_c204d81), [c204e48] "m"(b1cb4c0_c204e48), [memset] "m"(b1cb4c0_memset), [c204c95] "m"(b1cb4c0_c204c95), [c1c98f0] "m"(b1cb4c0_c1c98f0), [c204d41] "m"(b1cb4c0_c204d41), [c2038df] "m"(b1cb4c0_c2038df), [c1ca2b0] "m"(b1cb4c0_c1ca2b0), [c1c92f0] "m"(b1cb4c0_c1c92f0), [c1cb210] "m"(b1cb4c0_c1cb210), [c1c9cf0] "m"(b1cb4c0_c1c9cf0), [c1c93f0] "m"(b1cb4c0_c1c93f0)
      : "memory");
}
#else
#error "FUN_001cb4c0: clang naked draft required"
#endif


/* FUN_001cb820 (0x1cb820) — readable C lift. */
void FUN_001cb820(void)
{
  if (*(unsigned char *)0x4eaf40) {
    ((void (*)(void))(*(unsigned int *)(*(unsigned int *)0x4eaf48 + 8)))();
    data_make_invalid(*(data_t **)0x4fdba4);
    data_make_invalid(*(data_t **)0x4fdba0);
    *(unsigned char *)0x4eaf40 = 0;
  }
  if (*(data_t **)0x4fdba4)
    data_dispose(*(data_t **)0x4fdba4);
  if (*(data_t **)0x4fdba0)
    data_dispose(*(data_t **)0x4fdba0);
  FUN_001bde90();
}

/* sound_reconnect_to_structure_bsp (0x1cb8f0) — readable C lift. */
void sound_reconnect_to_structure_bsp(void)
{
  int idx;
  char *sound;

  if (!*(unsigned char *)0x4eaf40 || !*(unsigned char *)0x4eaf41)
    return;
  idx = data_next_index(*(data_t **)0x4fdba4, -1);
  while (idx != -1) {
    sound = (char *)datum_get(*(data_t **)0x4fdba4, idx);
    if (*(short *)(sound + 0x14) == 1)
      scenario_location_from_point(sound + 0x44, sound + 0x20);
    idx = data_next_index(*(data_t **)0x4fdba4, idx);
  }
}


/* FUN_001cbc20 (0x1cbc20) — readable C lift (fld/fmul/_ftol2). */
int FUN_001cbc20(float t)
{
  int result;
  __asm__ volatile(
      "flds %1\n\t"
      "fmuls 0x2c1288\n\t"
      "call %P2\n\t"
      "movl %%eax, %0"
      : "=m"(result)
      : "m"(t), "X"(FUN_001d9068)
      : "eax", "edx", "ecx", "st", "cc", "memory");
  return result;
}

/* FUN_001cbc40 (0x1cbc40) — XBE naked draft (batch 282). */
#if defined(__clang__)
static void *(*const b1cbc40_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b1cbc40_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1cbc40_exitfn)(int) = system_exit;
static void *(*const b1cbc40_tag)(int, int) = tag_get;
static void * (*const b1cbc40_c1c88c0)(short class_index) = sound_class_get_definition;

__attribute__((naked, noinline))
char FUN_001cbc40(int sound_handle __attribute__((unused)))
{
  __asm__ volatile(
      "movl 0x4fdba4, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movw 0x8c(%%esi), %%di\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $-1, %%di\n\t"
      "je .LFUN_001cbc40_3\n\t"
      "testw %%di, %%di\n\t"
      "jl .LFUN_001cbc40_1\n\t"
      "cmpw 0x4eb0b4, %%di\n\t"
      "jl .LFUN_001cbc40_2\n\t"
      ".LFUN_001cbc40_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x428\n\t"
      "pushl $0x2c12cc\n\t"
      "pushl $0x2c1294\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001cbc40_2:\n\t"
      "movswl %%di, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "cmpl %%ebx, 0x4fc3a0(,%%ecx,8)\n\t"
      "je .LFUN_001cbc40_3\n\t"
      "pushl $1\n\t"
      "pushl $0x59f\n\t"
      "pushl $0x2c12cc\n\t"
      "pushl $0x2c1360\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001cbc40_3:\n\t"
      "testb $1, 0x4(%%esi)\n\t"
      "jne .LFUN_001cbc40_4\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001cbc40_4\n\t"
      "movl 0x84(%%esi), %%edx\n\t"
      "cmpl 0x4eaf4c, %%edx\n\t"
      "jge .LFUN_001cbc40_4\n\t"
      "leal 0x14(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "leal 0x54(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "call *%%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001cbc40_4\n\t"
      "cmpw $0, 0x2(%%esi)\n\t"
      "jne .LFUN_001cbc40_5\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x736e6421\n\t"
      "call *%[tag]\n\t"
      "movswl 0x4(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c88c0]\n\t"
      "movb 0x8(%%eax), %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_001cbc40_5\n\t"
      "movl $0, 0x10(%%esi)\n\t"
      ".LFUN_001cbc40_4:\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      ".LFUN_001cbc40_5:\n\t"
      "popl %%edi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1cbc40_dget), [assert] "m"(b1cbc40_assert), [exitfn] "m"(b1cbc40_exitfn), [tag] "m"(b1cbc40_tag), [c1c88c0] "m"(b1cbc40_c1c88c0)
      : "memory");
}
#else
#error "FUN_001cbc40: clang naked draft required"
#endif


/* FUN_001cc1c0 (0x1cc1c0) — readable C lift. */
char FUN_001cc1c0(int looping_handle, int unused, void *out)
{
  void *d;
  (void)unused;
  d = (void *)datum_absolute_index_to_index(*(data_t **)0x4fdba0, looping_handle);
  if (d == NULL)
    return 0;
  {
    unsigned int *src = (unsigned int *)((char *)d + 0xc);
    unsigned int *dst = (unsigned int *)out;
    int i;
    for (i = 0; i < 0x10; i++)
      dst[i] = src[i];
  }
  return 1;
}
/* FUN_001cc200 (0x1cc200) — readable C lift: fill sound position from looping datum. */
char FUN_001cc200(int looping_handle, void *source, void *position)
{
  char *entry; char *pos=(char*)position; char *src=(char*)source; float *v;
  entry=(char*)datum_absolute_index_to_index(*(data_t**)0x4fdba0, looping_handle);
  if (!entry) return 0;
  *(int*)(pos+0x38)=*(int*)(entry+0x44); *(int*)(pos+0x3c)=*(int*)(entry+0x48);
  if (*(short*)(entry+0xc)!=0) {
    *(int*)(pos+0x24)=*(int*)(entry+0x30); *(int*)(pos+0x28)=*(int*)(entry+0x34); *(int*)(pos+0x2c)=*(int*)(entry+0x38);
    *(int*)(pos+0x18)=*(int*)(entry+0x24); *(int*)(pos+0x1c)=*(int*)(entry+0x28); *(int*)(pos+0x20)=*(int*)(entry+0x2c);
    *(int*)(pos+0x30)=*(int*)(entry+0x3c); *(int*)(pos+0x34)=*(int*)(entry+0x40);
  } else {
    v=*(float**)0x31fc3c; *(int*)(pos+0x18)=*(int*)&v[0]; *(int*)(pos+0x1c)=*(int*)&v[1]; *(int*)(pos+0x20)=*(int*)&v[2];
    v=*(float**)0x31fc38; *(int*)(pos+0x24)=*(int*)&v[0]; *(int*)(pos+0x28)=*(int*)&v[1]; *(int*)(pos+0x2c)=*(int*)&v[2];
  }
  *(int*)(pos+0xc)=*(int*)(src+0); *(int*)(pos+0x10)=*(int*)(src+4); *(int*)(pos+0x14)=*(int*)(src+8);
  if (*(short*)pos==1) {
    *(float*)(pos+0xc)+=*(float*)(entry+0x18);
    *(float*)(pos+0x10)+=*(float*)(entry+0x1c);
    *(float*)(pos+0x14)+=*(float*)(entry+0x20);
  }
  return 1;
}


/* FUN_001cc2f0 (0x1cc2f0) — readable C lift. */
void FUN_001cc2f0(int tag_index /*@<esi>*/, int sound_handle /*@<eax>*/)
{
  char *sound;

  sound = (char *)datum_get(*(data_t **)0x4fdba4, sound_handle);
  if (*(int *)(sound + 8) != tag_index)
    *(int *)(sound + 0x98) = tag_index;
}

/* FUN_001cc440 (0x1cc440) — readable C lift: find sound datum by source@edi. */
int FUN_001cc440(int source)
{
  int index;
  char *datum;

  index = data_next_index(*(data_t **)0x4fdba0, -1);
  while (index != -1) {
    datum = (char *)datum_get(*(data_t **)0x4fdba0, index);
    if (*(int *)(datum + 8) == source)
      return index;
    index = data_next_index(*(data_t **)0x4fdba0, index);
  }
  return -1;
}

/* FUN_001cc4f0 (0x1cc4f0) — readable C lift. */
void FUN_001cc4f0(int sound_handle)
{
  char *datum;
  int tag_index;
  char *center;
  char buf[0x200];
  const char *name;
  float prio;
  float mind;

  if (!*(char *)0x4fc382)
    return;
  datum = (char *)datum_get(*(void **)0x4fdba4, sound_handle);
  tag_index = *(int *)(datum + 8);
  tag_get(tag_index, 0x736e6421);
  center = datum + 0x20;
  prio = sound_get_default_priority(tag_index);
  FUN_00189540(0, center, prio, *(void **)0x2ee6e0);
  mind = sound_class_get_min_distance(tag_index);
  FUN_00189540(0, center, mind, *(void **)0x2ee6d0);
  name = tag_get_name(tag_index);
  crt_sprintf(buf, (const char *)0x2c1538, name, (double)*(float *)(datum + 0x4c), (double)*(float *)(datum + 0x50));
  FUN_00189cb0(0, center, buf, *(int *)0x2ee6c4);
}

/* FUN_001cc5b0 (0x1cc5b0) — XBE naked draft (batch 253). */
#if defined(__clang__)
static void *(*const b1cc5b0_tag)(int, int) = tag_get;
static void *(*const b1cc5b0_elem)(void *, int, int) = tag_block_get_element;
static float (*const b1cc5b0_c1c8d50)(int sound_tag_index) = sound_class_get_min_distance;
static float (*const b1cc5b0_c1c8d10)(int sound_tag_index) = sound_get_default_priority;
static const char * (*const b1cc5b0_c1ba1f0)(int tag_index) = tag_get_name;
static void (*const b1cc5b0_c189cb0)(char flag, void *position, void *string, int color) = FUN_00189cb0;
static void (*const b1cc5b0_c189540)(char flag, void *center, float radius, void *color) = FUN_00189540;

__attribute__((naked, noinline))
void FUN_001cc5b0(int sound_tag_index __attribute__((unused)), void *source __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movb 0x4fc381, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001cc5b0_7\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cmpw $1, (%%eax)\n\t"
      "jne .LFUN_001cc5b0_7\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6c736e64\n\t"
      "call *%[tag]\n\t"
      "leal 0x3c(%%eax), %%esi\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "jle .LFUN_001cc5b0_3\n\t"
      ".LFUN_001cc5b0_1:\n\t"
      "pushl $0xa0\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x4c(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_001cc5b0_2\n\t"
      "movl (%%esi), %%eax\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jl .LFUN_001cc5b0_1\n\t"
      "jmp .LFUN_001cc5b0_3\n\t"
      ".LFUN_001cc5b0_2:\n\t"
      "movl 0x4c(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x736e6421\n\t"
      "call *%[tag]\n\t"
      "movl 0x4c(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c8d50]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl 0x4c(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1c8d10]\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "addl $0x10, %%esp\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_001cc5b0_6\n\t"
      ".LFUN_001cc5b0_3:\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      "movl 0x48(%%edi), %%eax\n\t"
      "addl $0x48, %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_001cc5b0_6\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_001cc5b0_4:\n\t"
      "pushl $0x68\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_001cc5b0_5\n\t"
      "movl (%%edi), %%ecx\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_001cc5b0_4\n\t"
      "jmp .LFUN_001cc5b0_6\n\t"
      ".LFUN_001cc5b0_5:\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x736e6421\n\t"
      "call *%[tag]\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1c8d50]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c8d10]\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_001cc5b0_6:\n\t"
      "movl 0x2ee6c4, %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "addl $0xc, %%esi\n\t"
      "call *%[c1ba1f0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "call *%[c189cb0]\n\t"
      "movl 0x2ee6dc, %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "call *%[c189540]\n\t"
      "movl 0x2ee6d8, %%edx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "call *%[c189540]\n\t"
      "addl $0x30, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001cc5b0_7:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(b1cc5b0_tag), [elem] "m"(b1cc5b0_elem), [c1c8d50] "m"(b1cc5b0_c1c8d50), [c1c8d10] "m"(b1cc5b0_c1c8d10), [c1ba1f0] "m"(b1cc5b0_c1ba1f0), [c189cb0] "m"(b1cc5b0_c189cb0), [c189540] "m"(b1cc5b0_c189540)
      : "memory");
}
#else
#error "FUN_001cc5b0: clang naked draft required"
#endif


/* sound_initialize (0x1cc710) — XBE naked draft (batch 268). */
#if defined(__clang__)
static void (*const b1cc710_c1cf820)(void **out) = (void *)FUN_001cf820;
static void (*const b1cc710_c1be3e0)(void) = (void *)sound_cache_new;
static data_t * (*const b1cc710_c1194d0)(char *name, int16_t maximum_count, int16_t size) = data_new;
static void (*const b1cc710_c119b20)(data_t *data) = data_delete_all;
static void (*const b1cc710_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1cc710_exitfn)(int) = system_exit;
static void * (*const b1cc710_c1cba80)(short channel_index) = sound_channel_get;

__attribute__((naked, noinline))
void sound_initialize(void **driver_out __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movb $0, 0x4eaf40\n\t"
      "movb $1, 0x4eaf41\n\t"
      "call *%[c1cf820]\n\t"
      "addl $4, %%esp\n\t"
      "call *%[c1be3e0]\n\t"
      "movl $0x12, %%ecx\n\t"
      "movl $0x2c1220, %%esi\n\t"
      "movl $0x4eb068, %%edi\n\t"
      "rep movsl\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl $0x3f800000, 0x4eb0b0\n\t"
      "movw (%%ecx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lsound_initialize_5\n\t"
      "cmpw $2, %%ax\n\t"
      "jge .Lsound_initialize_5\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl 0x32f6dc(,%%edx,4), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Lsound_initialize_5\n\t"
      "cmpw %%ax, (%%ecx)\n\t"
      "jne .Lsound_initialize_5\n\t"
      "pushl $0xac\n\t"
      "pushl $0x200\n\t"
      "pushl $0x2c1590\n\t"
      "movl %%ecx, 0x4eaf48\n\t"
      "call *%[c1194d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x4fdba4\n\t"
      "je .Lsound_initialize_5\n\t"
      "pushl $0xe4\n\t"
      "pushl $0x80\n\t"
      "pushl $0x2c1580\n\t"
      "call *%[c1194d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x4fdba0\n\t"
      "je .Lsound_initialize_5\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x4eaf48, %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *0x4(%%ecx)\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsound_initialize_5\n\t"
      "movl 0x4fdba4, %%edx\n\t"
      "pushl %%edx\n\t"
      "xorl %%esi, %%esi\n\t"
      "call *%[c119b20]\n\t"
      "movl 0x4fdba0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119b20]\n\t"
      "addl $8, %%esp\n\t"
      "movl $0xa, %%edi\n\t"
      "movl $0x32fcf8, %%eax\n\t"
      "subl %%edi, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl $4, -0x8(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "jmp .Lsound_initialize_1\n\t"
      "leal (%%esp), %%esp\n\t"
      "jmp .Lsound_initialize_1\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lsound_initialize_1:\n\t"
      "movw 0x4eb0b4, %%cx\n\t"
      "addw (%%edi,%%eax,1), %%cx\n\t"
      "cmpw $0x100, %%cx\n\t"
      "movw %%cx, 0x4eb0b4\n\t"
      "jle .Lsound_initialize_2\n\t"
      "pushl $1\n\t"
      "pushl $0x168\n\t"
      "pushl $0x2c12cc\n\t"
      "pushl $0x2c1544\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsound_initialize_2:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpw %%bx, (%%edi,%%eax,1)\n\t"
      "jle .Lsound_initialize_4\n\t"
      ".Lsound_initialize_3:\n\t"
      "call *%[c1cba80]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl $0xffffffff, (%%eax)\n\t"
      "movw (%%ecx,%%edi,1), %%dx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "incl %%esi\n\t"
      "movw %%dx, 0x4(%%eax)\n\t"
      "movl %%ecx, 0x10(%%eax)\n\t"
      "movl %%ecx, 0x14(%%eax)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "incl %%ebx\n\t"
      "cmpw (%%edi,%%eax,1), %%bx\n\t"
      "jl .Lsound_initialize_3\n\t"
      ".Lsound_initialize_4:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "addl $2, %%edi\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jne .Lsound_initialize_1\n\t"
      "movb $1, 0x4eaf40\n\t"
      "popl %%ebx\n\t"
      ".Lsound_initialize_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1cf820] "m"(b1cc710_c1cf820), [c1be3e0] "m"(b1cc710_c1be3e0), [c1194d0] "m"(b1cc710_c1194d0), [c119b20] "m"(b1cc710_c119b20), [assert] "m"(b1cc710_assert), [exitfn] "m"(b1cc710_exitfn), [c1cba80] "m"(b1cc710_c1cba80)
      : "memory");
}
#else
#error "sound_initialize: clang naked draft required"
#endif


/* FUN_001ccbe0 (0x1ccbe0) — XBE naked draft (batch 249). */
#if defined(__clang__)
static void (*const b1ccbe0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1ccbe0_exitfn)(int) = system_exit;
static void * (*const b1ccbe0_c1cbac0)(short listener_index) = sound_listener_get;

__attribute__((naked, noinline))
float FUN_001ccbe0(int channel_index __attribute__((unused)), void *source __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl (%%edi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_001ccbe0_5\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001ccbe0_4\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001ccbe0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x57a\n\t"
      "pushl $0x2c12cc\n\t"
      "pushl $0\n\t"
      ".LFUN_001ccbe0_1:\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ccbe0_2:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001ccbe0_3:\n\t"
      "flds 0x14(%%edi)\n\t"
      "popl %%esi\n\t"
      "flds 0x10(%%edi)\n\t"
      "flds 0xc(%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001ccbe0_4:\n\t"
      "call *%[c1cbac0]\n\t"
      "flds 0x2c(%%eax)\n\t"
      "fsubs 0xc(%%edi)\n\t"
      "addl $0x2c, %%eax\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x10(%%edi)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs 0x14(%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[c1cbac0]\n\t"
      "cmpb $0, (%%eax)\n\t"
      "jne .LFUN_001ccbe0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x574\n\t"
      "pushl $0x2c12cc\n\t"
      "pushl $0x2c1624\n\t"
      "jmp .LFUN_001ccbe0_1\n\t"
      ".LFUN_001ccbe0_5:\n\t"
      "flds 0x2533c0\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1ccbe0_assert), [exitfn] "m"(b1ccbe0_exitfn), [c1cbac0] "m"(b1ccbe0_c1cbac0)
      : "memory");
}
#else
#error "FUN_001ccbe0: clang naked draft required"
#endif


/* FUN_001ccca0 (0x1ccca0) — XBE naked draft (batch 269). */
#if defined(__clang__)
static void (*const b1ccca0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1ccca0_exitfn)(int) = system_exit;
static void * (*const b1ccca0_c1cbac0)(short listener_index) = sound_listener_get;

__attribute__((naked, noinline))
float FUN_001ccca0(int channel_index __attribute__((unused)), void *source __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl (%%edi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_001ccca0_5\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001ccca0_4\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001ccca0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x593\n\t"
      "pushl $0x2c12cc\n\t"
      "pushl $0\n\t"
      ".LFUN_001ccca0_1:\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ccca0_2:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001ccca0_3:\n\t"
      "flds 0x14(%%edi)\n\t"
      "popl %%esi\n\t"
      "flds 0x10(%%edi)\n\t"
      "flds 0xc(%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001ccca0_4:\n\t"
      "call *%[c1cbac0]\n\t"
      "flds 0x2c(%%eax)\n\t"
      "fsubs 0xc(%%edi)\n\t"
      "addl $0x2c, %%eax\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x10(%%edi)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs 0x14(%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[c1cbac0]\n\t"
      "cmpb $0, (%%eax)\n\t"
      "jne .LFUN_001ccca0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x58d\n\t"
      "pushl $0x2c12cc\n\t"
      "pushl $0x2c1624\n\t"
      "jmp .LFUN_001ccca0_1\n\t"
      ".LFUN_001ccca0_5:\n\t"
      "flds 0x2533c0\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1ccca0_assert), [exitfn] "m"(b1ccca0_exitfn), [c1cbac0] "m"(b1ccca0_c1cbac0)
      : "memory");
}
#else
#error "FUN_001ccca0: clang naked draft required"
#endif


/* sound_update_time (0x1cce80) — XBE naked draft (batch 260). */
#if defined(__clang__)
static void *(*const b1cce80_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1cce80_tag)(int, int) = tag_get;
static void (*const b1cce80_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1cce80_exitfn)(int) = system_exit;
static void * (*const b1cce80_c1c88c0)(short class_index) = sound_class_get_definition;
static float (*const b1cce80_c1ccbe0)(int channel_index, void *source) = FUN_001ccbe0;

__attribute__((naked, noinline))
char sound_update_time(int sound_a __attribute__((unused)), int sound_b __attribute__((unused)), float threshold __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x4fdba4, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x736e6421\n\t"
      "call *%[tag]\n\t"
      "movl 0x4fdba4, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x8(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x736e6421\n\t"
      "call *%[tag]\n\t"
      "addl $0x20, %%esp\n\t"
      "cmpl %%esi, %%edi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .Lsound_update_time_1\n\t"
      "pushl $1\n\t"
      "pushl $0x763\n\t"
      "pushl $0x2c12cc\n\t"
      "pushl $0x2c1648\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsound_update_time_1:\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%esi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c88c0]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%edx), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c88c0]\n\t"
      "movw 0xa(%%edi), %%cx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw 0xa(%%eax), %%cx\n\t"
      "jg .Lsound_update_time_3\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%esi), %%dx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1c88c0]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c88c0]\n\t"
      "movw 0xa(%%esi), %%dx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw 0xa(%%eax), %%dx\n\t"
      "jne .Lsound_update_time_2\n\t"
      "movw 0x6(%%ebx), %%ax\n\t"
      "leal 0x14(%%ebx), %%edi\n\t"
      "call *%[c1ccbe0]\n\t"
      "fcomps 0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lsound_update_time_3\n\t"
      ".Lsound_update_time_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsound_update_time_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1cce80_dget), [tag] "m"(b1cce80_tag), [assert] "m"(b1cce80_assert), [exitfn] "m"(b1cce80_exitfn), [c1c88c0] "m"(b1cce80_c1c88c0), [c1ccbe0] "m"(b1cce80_c1ccbe0)
      : "memory");
}
#else
#error "sound_update_time: clang naked draft required"
#endif


/* FUN_001cd190 (0x1cd190) — XBE naked draft (batch 278). */
#if defined(__clang__)
static int (*const b1cd190_c119610)(data_t *data) = data_new_at_index;
static void *(*const b1cd190_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1cd190_tag)(int, int) = tag_get;
static void *(*const b1cd190_elem)(void *, int, int) = tag_block_get_element;
static unsigned int *(*const b1cd190_lseed)(void) = random_math_get_local_seed_address;
static float (*const b1cd190_rrange)(int *, float, float) = random_real_range;
static void (*const b1cd190_ftol)(void) = FUN_001d9068;

__attribute__((naked, noinline))
int FUN_001cd190(int sound_tag_index __attribute__((unused)), void *track __attribute__((unused)), void *source __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "movb 0x4eaf40, %%cl\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_001cd190_2\n\t"
      "movb 0x4eaf41, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_001cd190_2\n\t"
      "movl 0x4fdba0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119610]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%edi, -0x20(%%ebp)\n\t"
      "je .LFUN_001cd190_1\n\t"
      "movl 0x4fdba0, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "pushl %%esi\n\t"
      "pushl $0x6c736e64\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[tag]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%esi, 0x4(%%ebx)\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%edx, 0x8(%%ebx)\n\t"
      "movw %%si, 0x50(%%ebx)\n\t"
      "movb $0, 0x4e(%%ebx)\n\t"
      "movl 0x48(%%eax), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "jg .LFUN_001cd190_4\n\t"
      ".LFUN_001cd190_1:\n\t"
      "movl %%edi, %%eax\n\t"
      ".LFUN_001cd190_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001cd190_3:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      ".LFUN_001cd190_4:\n\t"
      "pushl $0x68\n\t"
      "addl $0x48, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x736e6421\n\t"
      "call *%[tag]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x10(%%eax), %%ecx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x14(%%edi), %%eax\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl 0x10(%%edi), %%ecx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%eax, %%edx\n\t"
      "addl $0x14, %%esp\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fsubs -0x8(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fmuls 0x254cb8\n\t"
      "fiaddl 0x4eaf4c\n\t"
      "call *%[ftol]\n\t"
      "fstp %%st(0)\n\t"
      "movl %%eax, 0x54(%%ebx,%%esi,4)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "movswl %%ax, %%esi\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x48(%%eax), %%ecx\n\t"
      "addl $0x48, %%eax\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "jl .LFUN_001cd190_3\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c119610] "m"(b1cd190_c119610), [dget] "m"(b1cd190_dget), [tag] "m"(b1cd190_tag), [elem] "m"(b1cd190_elem), [lseed] "m"(b1cd190_lseed), [rrange] "m"(b1cd190_rrange), [ftol] "m"(b1cd190_ftol)
      : "memory");
}
#else
#error "FUN_001cd190: clang naked draft required"
#endif


/* FUN_001cd390 (0x1cd390) — readable C lift: random scaled direction from track. */
void FUN_001cd390(void *track_entry, float *out)
{
  char *e = (char *)track_entry;
  float scale;
  float angles[2];
  float *fwd;

  scale = random_real_range((int *)random_math_get_local_seed_address(),
                            *(float *)(e + 0x60), *(float *)(e + 0x64));
  if (scale == 0.0f) {
    fwd = *(float **)0x31fc38;
    out[0] = fwd[0];
    out[1] = fwd[1];
    out[2] = fwd[2];
    return;
  }
  angles[1] = random_real_range((int *)random_math_get_local_seed_address(),
                                *(float *)(e + 0x58), *(float *)(e + 0x5c));
  angles[0] = random_real_range((int *)random_math_get_local_seed_address(),
                                *(float *)(e + 0x50), *(float *)(e + 0x54));
  angles_to_vector(out, angles);
  out[0] *= scale;
  out[1] *= scale;
  out[2] *= scale;
}


/* sound_stop_impulse_by_source_and_definition (0x1cd4d0) — readable C lift. */
void sound_stop_impulse_by_source_and_definition(int source, int definition)
{
  int index;
  char *entry;

  for (index = data_next_index(*(data_t **)0x4fdba4, -1); index != -1;
       index = data_next_index(*(data_t **)0x4fdba4, index)) {
    entry = (char *)datum_get(*(void **)0x4fdba4, index);
    if (*(short *)(entry + 2) != 0)
      continue;
    if (*(int *)(entry + 0xc) != source)
      continue;
    if (*(int *)(entry + 8) != definition)
      continue;
    sound_stop_impulse(index);
    return;
  }
}



/* sound_stop_all (0x1cd540) — readable C lift. */
void sound_stop_all(void)
{
  int idx;
  if (*(unsigned char *)0x4eaf40) {
    idx = data_next_index(*(data_t **)0x4fdba4, -1);
    while (idx != -1) {
      sound_stop_channel(idx);
      idx = data_next_index(*(data_t **)0x4fdba4, idx);
    }
    data_make_valid(*(data_t **)0x4fdba0);
    ((void (*)(void))(*(void **)(*(unsigned int *)0x4eaf48 + 0x2c)))();
  }
  *(unsigned int *)0x4eaf44 = 0;
}
/* FUN_001cd690 (0x1cd690) — XBE naked draft (batch 268). */
#if defined(__clang__)
static bool (*const b1cd690_cba5e0)(void) = players_are_all_dead;
static int (*const b1cd690_c1198f0)(data_t *data, int prev_index) = data_next_index;
static void *(*const b1cd690_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1cd690_tag)(int, int) = tag_get;
static short (*const b1cd690_c1cc050)(short channel_index) = sound_channel_update_status;
static char (*const b1cd690_c1cbc40)(int sound_handle) = FUN_001cbc40;
static float (*const b1cd690_c1c8d10)(int sound_tag_index) = sound_get_default_priority;
static int16_t (*const b1cd690_c1cd5a0)(void *source, float priority) = sound_allocate_channel;
static void (*const b1cd690_c1cc4f0)(int sound_handle) = (void *)FUN_001cc4f0;
static void (*const b1cd690_c1cc8f0)(short mode, float seconds, int fade_in_sound_index, int fade_out_sound_index) = sound_start_fade;
static void (*const b1cd690_c1cca60)(int sound_handle) = sound_stop_channel;

__attribute__((naked, noinline))
void FUN_001cd690(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "call *%[cba5e0]\n\t"
      "movb %%al, -0x2(%%ebp)\n\t"
      "movl 0x4fdba4, %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c1198f0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .LFUN_001cd690_11\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      ".LFUN_001cd690_1:\n\t"
      "movl 0x4fdba4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x736e6421\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x8c(%%esi), %%ax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001cd690_2\n\t"
      "call *%[c1cc050]\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_001cd690_2\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "je .LFUN_001cd690_2\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .LFUN_001cd690_8\n\t"
      ".LFUN_001cd690_2:\n\t"
      "call *%[c1cbc40]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001cd690_8\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c8d10]\n\t"
      "fstps (%%esp)\n\t"
      "leal 0x14(%%esi), %%eax\n\t"
      "call *%[c1cd5a0]\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c1cc4f0]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movw 0x4(%%ecx), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0x2c, %%ax\n\t"
      "je .LFUN_001cd690_3\n\t"
      "cmpw $0x2e, %%ax\n\t"
      "je .LFUN_001cd690_3\n\t"
      "cmpw $0x2f, %%ax\n\t"
      "jne .LFUN_001cd690_4\n\t"
      ".LFUN_001cd690_3:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_001cd690_4:\n\t"
      "cmpw $-1, %%di\n\t"
      "movb 0x4(%%esi), %%al\n\t"
      "jne .LFUN_001cd690_5\n\t"
      "testb $4, %%al\n\t"
      "jne .LFUN_001cd690_6\n\t"
      "movl 0x2c127c, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "call *%[c1cc8f0]\n\t"
      "addl $0x10, %%esp\n\t"
      "orb $4, 0x4(%%esi)\n\t"
      "jmp .LFUN_001cd690_6\n\t"
      ".LFUN_001cd690_5:\n\t"
      "testb $4, %%al\n\t"
      "movw %%di, 0x6(%%esi)\n\t"
      "je .LFUN_001cd690_6\n\t"
      "movl 0x2c1280, %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c1cc8f0]\n\t"
      "addl $0x10, %%esp\n\t"
      "andb $0xfb, 0x4(%%esi)\n\t"
      ".LFUN_001cd690_6:\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001cd690_9\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movw 0x4(%%ecx), %%ax\n\t"
      "cmpw $0x2c, %%ax\n\t"
      "jne .LFUN_001cd690_7\n\t"
      "cmpw $-1, 0x8c(%%esi)\n\t"
      "je .LFUN_001cd690_8\n\t"
      "movl 0x2c1284, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "call *%[c1cc8f0]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_001cd690_9\n\t"
      ".LFUN_001cd690_7:\n\t"
      "cmpw $0x2e, %%ax\n\t"
      "jne .LFUN_001cd690_9\n\t"
      "cmpw $-1, 0x8c(%%esi)\n\t"
      "jne .LFUN_001cd690_9\n\t"
      ".LFUN_001cd690_8:\n\t"
      "call *%[c1cca60]\n\t"
      ".LFUN_001cd690_9:\n\t"
      "movl 0x4fdba4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1198f0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "jne .LFUN_001cd690_1\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "je .LFUN_001cd690_11\n\t"
      "flds 0x4eaf50\n\t"
      "fmuls 0x25bc08\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x32f6d8\n\t"
      "fsubs 0x4eb0b0\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fchs\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001cd690_13\n\t"
      "fstp %%st(0)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001cd690_12\n\t"
      ".LFUN_001cd690_10:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "popl %%ebx\n\t"
      "fadds 0x4eb0b0\n\t"
      "fstps 0x4eb0b0\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001cd690_11:\n\t"
      "flds 0x4eaf50\n\t"
      "fmuls 0x2c16d0\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x4eb0b0\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fchs\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001cd690_13\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_001cd690_10\n\t"
      ".LFUN_001cd690_12:\n\t"
      "flds -0x8(%%ebp)\n\t"
      ".LFUN_001cd690_13:\n\t"
      "fadds 0x4eb0b0\n\t"
      "popl %%ebx\n\t"
      "fstps 0x4eb0b0\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cba5e0] "m"(b1cd690_cba5e0), [c1198f0] "m"(b1cd690_c1198f0), [dget] "m"(b1cd690_dget), [tag] "m"(b1cd690_tag), [c1cc050] "m"(b1cd690_c1cc050), [c1cbc40] "m"(b1cd690_c1cbc40), [c1c8d10] "m"(b1cd690_c1c8d10), [c1cd5a0] "m"(b1cd690_c1cd5a0), [c1cc4f0] "m"(b1cd690_c1cc4f0), [c1cc8f0] "m"(b1cd690_c1cc8f0), [c1cca60] "m"(b1cd690_c1cca60)
      : "memory");
}
#else
#error "FUN_001cd690: clang naked draft required"
#endif


/* FUN_001cd8b0 (0x1cd8b0) — XBE naked draft (batch 276). */
#if defined(__clang__)
static void *(*const b1cd8b0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1cd8b0_tag)(int, int) = tag_get;
static float (*const b1cd8b0_c1ccbe0)(int channel_index, void *source) = FUN_001ccbe0;
static void (*const b1cd8b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1cd8b0_exitfn)(int) = system_exit;
static char (*const b1cd8b0_c1cce80)(int sound_a, int sound_b, float threshold) = sound_update_time;

__attribute__((naked, noinline))
short FUN_001cd8b0(int sound_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x4fdba4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x736e6421\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movw 0x6(%%esi), %%ax\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "leal 0x14(%%esi), %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%edi, -0x18(%%ebp)\n\t"
      "call *%[c1ccbe0]\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "movl 0x4eb0b4, %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "jle .LFUN_001cd8b0_12\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_001cd8b0_1:\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .LFUN_001cd8b0_2\n\t"
      "cmpw %%ax, %%bx\n\t"
      "jl .LFUN_001cd8b0_3\n\t"
      ".LFUN_001cd8b0_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x428\n\t"
      "pushl $0x2c12cc\n\t"
      "pushl $0x2c1294\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001cd8b0_3:\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      "movswl %%bx, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%esi\n\t"
      "movw 0x4fc3a4(,%%esi,8), %%cx\n\t"
      "leal 0x4fc3a0(,%%esi,8), %%esi\n\t"
      "movswl %%cx, %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "shrl $3, %%edx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "notl %%edx\n\t"
      "andl $1, %%edx\n\t"
      "cmpw %%bx, 0x6e(%%edi)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "sete %%bl\n\t"
      "cmpl %%ebx, %%edx\n\t"
      "je .LFUN_001cd8b0_4\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_001cd8b0_4:\n\t"
      "movl %%eax, %%edx\n\t"
      "shrl $1, %%edx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "notl %%edx\n\t"
      "andl $1, %%edx\n\t"
      "cmpw %%bx, 0x6c(%%edi)\n\t"
      "sete %%bl\n\t"
      "cmpl %%ebx, %%edx\n\t"
      "je .LFUN_001cd8b0_5\n\t"
      "xorb %%dl, %%dl\n\t"
      "jmp .LFUN_001cd8b0_6\n\t"
      ".LFUN_001cd8b0_5:\n\t"
      "movb -0x1(%%ebp), %%dl\n\t"
      ".LFUN_001cd8b0_6:\n\t"
      "movl %%eax, %%ebx\n\t"
      "shrl $2, %%ebx\n\t"
      "andl $1, %%ebx\n\t"
      "cmpw 0x6(%%edi), %%bx\n\t"
      "je .LFUN_001cd8b0_7\n\t"
      "xorb %%dl, %%dl\n\t"
      ".LFUN_001cd8b0_7:\n\t"
      "testb $2, %%cl\n\t"
      "jne .LFUN_001cd8b0_8\n\t"
      "movl -0x18(%%ebp), %%edi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw %%cx, (%%edi)\n\t"
      "notl %%eax\n\t"
      "sete %%cl\n\t"
      "andl $1, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jne .LFUN_001cd8b0_10\n\t"
      ".LFUN_001cd8b0_8:\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_001cd8b0_10\n\t"
      "movl (%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001cd8b0_13\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1cce80]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001cd8b0_10\n\t"
      "cmpw $-1, -0xc(%%ebp)\n\t"
      "je .LFUN_001cd8b0_9\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl (%%esi), %%eax\n\t"
      "call *%[c1cce80]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001cd8b0_10\n\t"
      ".LFUN_001cd8b0_9:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl 0x4fdba4, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "leal 0x14(%%eax), %%edi\n\t"
      "movw 0x6(%%eax), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "call *%[c1ccbe0]\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "jmp .LFUN_001cd8b0_11\n\t"
      ".LFUN_001cd8b0_10:\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      ".LFUN_001cd8b0_11:\n\t"
      "movl 0x4eb0b4, %%eax\n\t"
      "incl %%ebx\n\t"
      "cmpw %%ax, %%bx\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "jl .LFUN_001cd8b0_1\n\t"
      ".LFUN_001cd8b0_12:\n\t"
      "movw -0xc(%%ebp), %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001cd8b0_13:\n\t"
      "movw -0x8(%%ebp), %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1cd8b0_dget), [tag] "m"(b1cd8b0_tag), [c1ccbe0] "m"(b1cd8b0_c1ccbe0), [assert] "m"(b1cd8b0_assert), [exitfn] "m"(b1cd8b0_exitfn), [c1cce80] "m"(b1cd8b0_c1cce80)
      : "memory");
}
#else
#error "FUN_001cd8b0: clang naked draft required"
#endif


/* sound_refresh_looping (0x1ce550) — XBE naked draft (batch 257). */
#if defined(__clang__)
static bool (*const b1ce550_c21fb0)(float *v) = valid_real_normal3d;
static void (*const b1ce550_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1ce550_exitfn)(int) = system_exit;
static void (*const b1ce550_c1cc5b0)(int sound_tag_index, void *source) = FUN_001cc5b0;
static int (*const b1ce550_c1cc440)(int source) = (void *)FUN_001cc440;
static int (*const b1ce550_c1cd190)(int sound_tag_index, void *track, void *source) = FUN_001cd190;
static void *(*const b1ce550_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1ce550_tag)(int, int) = tag_get;
static void (*const b1ce550_c1196d0)(data_t *data, int datum_handle) = datum_delete;
static void (*const b1ce550_ca2d30)(void) = (void *)player_effect_continuous_refresh;
static void *(*const b1ce550_elem)(void *, int, int) = tag_block_get_element;
static int (*const b1ce550_c1cda50)(int sound_tag_handle, int looping_handle, int track_index, int type) = sound_create_looping_entry;
static void (*const b1ce550_c1cc8f0)(short mode, float seconds, int fade_in_sound_index, int fade_out_sound_index) = sound_start_fade;
static void (*const b1ce550_c1cc2f0)(int sound_handle, int tag_index) = FUN_001cc2f0;
static int16_t (*const b1ce550_c1cd5a0)(void *source, float priority) = sound_allocate_channel;

__attribute__((naked, noinline))
char sound_refresh_looping(int sound_tag_index __attribute__((unused)), void *source __attribute__((unused)), void *track __attribute__((unused)), short track_type __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "cmpw $2, 0x14(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "sete -0x1(%%ebp)\n\t"
      "cmpw $0, (%%ebx)\n\t"
      "pushl %%edi\n\t"
      "je .Lsound_refresh_looping_1\n\t"
      "leal 0x18(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c21fb0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lsound_refresh_looping_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2f4\n\t"
      "pushl $0x2c12cc\n\t"
      "pushl $0x2c17c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsound_refresh_looping_1:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1cc5b0]\n\t"
      "movb 0x4eaf40, %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsound_refresh_looping_30\n\t"
      "movb 0x4eaf41, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsound_refresh_looping_30\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "call *%[c1cc440]\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movb $1, %%cl\n\t"
      "jne .Lsound_refresh_looping_2\n\t"
      "cmpw $2, 0x14(%%ebp)\n\t"
      "je .Lsound_refresh_looping_29\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c1cd190]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "je .Lsound_refresh_looping_28\n\t"
      ".Lsound_refresh_looping_2:\n\t"
      "movl 0x4fdba0, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "pushl %%esi\n\t"
      "pushl $0x6c736e64\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%esi, %%eax\n\t"
      "je .Lsound_refresh_looping_3\n\t"
      "pushl $1\n\t"
      "pushl $0x30e\n\t"
      "pushl $0x2c12cc\n\t"
      "pushl $0x2c1860\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsound_refresh_looping_3:\n\t"
      "cmpw $2, 0x14(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "leal 0xc(%%ebx), %%edi\n\t"
      "movl $0x10, %%ecx\n\t"
      "rep movsl\n\t"
      "movb 0x4eaf54, %%dl\n\t"
      "movb %%dl, 0x4c(%%ebx)\n\t"
      "je .Lsound_refresh_looping_4\n\t"
      "movb 0x4e(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsound_refresh_looping_5\n\t"
      ".Lsound_refresh_looping_4:\n\t"
      "cmpw $0, 0x50(%%ebx)\n\t"
      "jne .Lsound_refresh_looping_5\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl 0x4fdba0, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1196d0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsound_refresh_looping_5:\n\t"
      "movl -0x14(%%ebp), %%esi\n\t"
      "movl 0x38(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lsound_refresh_looping_6\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "addl $0xc, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[ca2d30]\n\t"
      "addl $8, %%esp\n\t"
      ".Lsound_refresh_looping_6:\n\t"
      "movl 0x3c(%%esi), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "leal 0x3c(%%esi), %%eax\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "jle .Lsound_refresh_looping_26\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "jmp .Lsound_refresh_looping_8\n\t"
      ".Lsound_refresh_looping_7:\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      ".Lsound_refresh_looping_8:\n\t"
      "pushl $0xa0\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsound_refresh_looping_9\n\t"
      "movl $0xffffffff, 0xd4(%%ebx,%%esi,4)\n\t"
      ".Lsound_refresh_looping_9:\n\t"
      "movw 0x14(%%ebp), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lsound_refresh_looping_10\n\t"
      "movl 0x3c(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lsound_refresh_looping_11\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1cda50]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, 0xd4(%%ebx,%%esi,4)\n\t"
      "jmp .Lsound_refresh_looping_11\n\t"
      ".Lsound_refresh_looping_10:\n\t"
      "cmpw $2, %%ax\n\t"
      "je .Lsound_refresh_looping_19\n\t"
      ".Lsound_refresh_looping_11:\n\t"
      "movb 0x4e(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lsound_refresh_looping_19\n\t"
      "movb 0x18(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x4c(%%edi), %%esi\n\t"
      "je .Lsound_refresh_looping_12\n\t"
      "movl 0x8c(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lsound_refresh_looping_12\n\t"
      "movl %%eax, %%esi\n\t"
      ".Lsound_refresh_looping_12:\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lsound_refresh_looping_25\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0xd4(%%ebx,%%eax,4), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lsound_refresh_looping_15\n\t"
      "cmpw $0, 0x14(%%ebp)\n\t"
      "jne .Lsound_refresh_looping_13\n\t"
      "testb $1, (%%edi)\n\t"
      "jne .Lsound_refresh_looping_15\n\t"
      ".Lsound_refresh_looping_13:\n\t"
      "movl 0x4fdba4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movb 0x18(%%ebp), %%dl\n\t"
      "movb 0x4d(%%ebx), %%al\n\t"
      "addl $8, %%esp\n\t"
      "cmpb %%al, %%dl\n\t"
      "je .Lsound_refresh_looping_14\n\t"
      "testb $4, (%%edi)\n\t"
      "je .Lsound_refresh_looping_14\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c1cda50]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lsound_refresh_looping_25\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0xd4(%%ebx,%%edx,4), %%eax\n\t"
      "movl 0xc(%%edi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "call *%[c1cc8f0]\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%esi, 0xd4(%%ebx,%%edx,4)\n\t"
      "jmp .Lsound_refresh_looping_25\n\t"
      ".Lsound_refresh_looping_14:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lsound_refresh_looping_25\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0xd4(%%ebx,%%eax,4), %%eax\n\t"
      "call *%[c1cc2f0]\n\t"
      "jmp .Lsound_refresh_looping_25\n\t"
      ".Lsound_refresh_looping_15:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl $2\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c1cda50]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lsound_refresh_looping_25\n\t"
      "movl 0x4fdba4, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, 0x14(%%ebp)\n\t"
      "jne .Lsound_refresh_looping_16\n\t"
      "testb $1, (%%edi)\n\t"
      "je .Lsound_refresh_looping_18\n\t"
      "movl 0x8(%%edi), %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "jmp .Lsound_refresh_looping_17\n\t"
      ".Lsound_refresh_looping_16:\n\t"
      "movl 0x2c127c, %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      ".Lsound_refresh_looping_17:\n\t"
      "pushl $0\n\t"
      "call *%[c1cc8f0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lsound_refresh_looping_18:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%esi, 0xd4(%%ebx,%%eax,4)\n\t"
      "jmp .Lsound_refresh_looping_25\n\t"
      ".Lsound_refresh_looping_19:\n\t"
      "cmpw $2, 0x52(%%ebx)\n\t"
      "je .Lsound_refresh_looping_25\n\t"
      "flds 0x1c(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Lsound_refresh_looping_20\n\t"
      "movl 0xd4(%%ebx,%%esi,4), %%ecx\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "call *%[c1cc8f0]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .Lsound_refresh_looping_25\n\t"
      ".Lsound_refresh_looping_20:\n\t"
      "movl 0xd4(%%ebx,%%esi,4), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lsound_refresh_looping_22\n\t"
      "testb $2, (%%edi)\n\t"
      "jne .Lsound_refresh_looping_21\n\t"
      "cmpl $-1, 0x5c(%%edi)\n\t"
      "jne .Lsound_refresh_looping_22\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "testb $2, (%%eax)\n\t"
      "jne .Lsound_refresh_looping_22\n\t"
      ".Lsound_refresh_looping_21:\n\t"
      "movl 0xc(%%edi), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "call *%[c1cc8f0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lsound_refresh_looping_22:\n\t"
      "movl 0x5c(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lsound_refresh_looping_25\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x18(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsound_refresh_looping_23\n\t"
      "movl 0x9c(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lsound_refresh_looping_23\n\t"
      "movl %%eax, %%esi\n\t"
      ".Lsound_refresh_looping_23:\n\t"
      "testb $2, (%%edi)\n\t"
      "je .Lsound_refresh_looping_24\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "pushl $4\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c1cda50]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Lsound_refresh_looping_25\n\t"
      ".Lsound_refresh_looping_24:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0xd4(%%ebx,%%ecx,4), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lsound_refresh_looping_25\n\t"
      "movl 0x4fdba4, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $-1, 0x8c(%%edi)\n\t"
      "je .Lsound_refresh_looping_25\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0xd4(%%ebx,%%eax,4), %%eax\n\t"
      "call *%[c1cc2f0]\n\t"
      "movw $3, 0x2(%%edi)\n\t"
      ".Lsound_refresh_looping_25:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl 0x3c(%%eax), %%edx\n\t"
      "addl $0x3c, %%eax\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jl .Lsound_refresh_looping_7\n\t"
      "movl -0x14(%%ebp), %%esi\n\t"
      ".Lsound_refresh_looping_26:\n\t"
      "cmpw $0, 0x50(%%ebx)\n\t"
      "jne .Lsound_refresh_looping_27\n\t"
      "movl 0x20(%%esi), %%ecx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1cd5a0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .Lsound_refresh_looping_27\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl 0x4fdba0, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1196d0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lsound_refresh_looping_27:\n\t"
      "movb 0x18(%%ebp), %%cl\n\t"
      "movw 0x14(%%ebp), %%dx\n\t"
      "movb %%cl, 0x4d(%%ebx)\n\t"
      "movw %%dx, 0x52(%%ebx)\n\t"
      ".Lsound_refresh_looping_28:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsound_refresh_looping_29:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%cl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsound_refresh_looping_30:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c21fb0] "m"(b1ce550_c21fb0), [assert] "m"(b1ce550_assert), [exitfn] "m"(b1ce550_exitfn), [c1cc5b0] "m"(b1ce550_c1cc5b0), [c1cc440] "m"(b1ce550_c1cc440), [c1cd190] "m"(b1ce550_c1cd190), [dget] "m"(b1ce550_dget), [tag] "m"(b1ce550_tag), [c1196d0] "m"(b1ce550_c1196d0), [ca2d30] "m"(b1ce550_ca2d30), [elem] "m"(b1ce550_elem), [c1cda50] "m"(b1ce550_c1cda50), [c1cc8f0] "m"(b1ce550_c1cc8f0), [c1cc2f0] "m"(b1ce550_c1cc2f0), [c1cd5a0] "m"(b1ce550_c1cd5a0)
      : "memory");
}
#else
#error "sound_refresh_looping: clang naked draft required"
#endif


/* FUN_001ce9c0 (0x1ce9c0) — XBE naked draft (batch 275). */
#if defined(__clang__)
static bool (*const b1ce9c0_cb5be0)(void) = game_in_progress;
static void (*const b1ce9c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1ce9c0_exitfn)(int) = system_exit;
static int (*const b1ce9c0_cba3c0)(int16_t local_player_index) = local_player_get_player_index;
static void * (*const b1ce9c0_c8a4e0)(unsigned __int16 local_player_index) = observer_get_camera;
static bool (*const b1ce9c0_c18f3e0)(void *location, void *position, int16_t *out_sky_index) = FUN_0018f3e0;
static void * (*const b1ce9c0_c18e450)(void) = game_globals_get;
static void *(*const b1ce9c0_elem)(void *, int, int) = tag_block_get_element;
static int (*const b1ce9c0_c1ce180)(int sound_tag_index, void *source, int object_handle, int track_data, void *track_data_ptr, int track_data_size) = sound_start;
static void (*const b1ce9c0_m4x3)(void *, float *, float *, float *) = matrix4x3_from_forward_up_position;
static void (*const b1ce9c0_m3x3v)(void *, float *, float *) = (void (*)(void *, float *, float *))real_matrix3x3_transform_vector;

__attribute__((naked, noinline))
void FUN_001ce9c0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x7c, %%esp\n\t"
      "call *%[cb5be0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001ce9c0_10\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl $0x4eaf59, %%edi\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      ".LFUN_001ce9c0_1:\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_001ce9c0_2\n\t"
      "cmpw $4, %%si\n\t"
      "jl .LFUN_001ce9c0_3\n\t"
      ".LFUN_001ce9c0_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x430\n\t"
      "pushl $0x2c12cc\n\t"
      "pushl $0x2c12f4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ce9c0_3:\n\t"
      "pushl %%esi\n\t"
      "call *%[cba3c0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001ce9c0_8\n\t"
      "pushl %%esi\n\t"
      "call *%[c8a4e0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_001ce9c0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x4ef\n\t"
      "pushl $0x2c12cc\n\t"
      "pushl $0x266e9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001ce9c0_4:\n\t"
      "pushl $0\n\t"
      "leal 0xc(%%esi), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "movb $1, -0x1(%%edi)\n\t"
      "call *%[c18f3e0]\n\t"
      "movb %%al, %%bl\n\t"
      "movb (%%edi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpb %%bl, %%al\n\t"
      "je .LFUN_001ce9c0_7\n\t"
      "call *%[c18e450]\n\t"
      "addl $0xf8, %%eax\n\t"
      "testb %%bl, %%bl\n\t"
      "movw $0, -0x7c(%%ebp)\n\t"
      "movl $0x3f800000, -0x78(%%ebp)\n\t"
      "movl $0x3f800000, -0x74(%%ebp)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "je .LFUN_001ce9c0_5\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .LFUN_001ce9c0_7\n\t"
      "pushl $0x10\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001ce9c0_7\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "leal -0x7c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "jmp .LFUN_001ce9c0_6\n\t"
      ".LFUN_001ce9c0_5:\n\t"
      "cmpl $1, %%ecx\n\t"
      "jle .LFUN_001ce9c0_7\n\t"
      "pushl $0x10\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001ce9c0_7\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "leal -0x7c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      ".LFUN_001ce9c0_6:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ce180]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_001ce9c0_7:\n\t"
      "leal 0x2c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x20(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movb %%bl, (%%edi)\n\t"
      "addl $3, %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[m4x3]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "addl $0x37, %%edx\n\t"
      "pushl %%edx\n\t"
      "addl $0x14, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[m3x3v]\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "addl $0x1c, %%esp\n\t"
      "jmp .LFUN_001ce9c0_9\n\t"
      ".LFUN_001ce9c0_8:\n\t"
      "movb $0, -0x1(%%edi)\n\t"
      ".LFUN_001ce9c0_9:\n\t"
      "incl %%esi\n\t"
      "addl $0x44, %%edi\n\t"
      "cmpw $4, %%si\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "jl .LFUN_001ce9c0_1\n\t"
      "movl 0x31fc3c, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x31fc44, %%ecx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl 0x31fc1c, %%edx\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x31fc38, %%eax\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl 0x4eaf48, %%edx\n\t"
      "leal -0x3c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl $0x4eb068, -0xc(%%ebp)\n\t"
      "call *0xc(%%edx)\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001ce9c0_10:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [cb5be0] "m"(b1ce9c0_cb5be0), [assert] "m"(b1ce9c0_assert), [exitfn] "m"(b1ce9c0_exitfn), [cba3c0] "m"(b1ce9c0_cba3c0), [c8a4e0] "m"(b1ce9c0_c8a4e0), [c18f3e0] "m"(b1ce9c0_c18f3e0), [c18e450] "m"(b1ce9c0_c18e450), [elem] "m"(b1ce9c0_elem), [c1ce180] "m"(b1ce9c0_c1ce180), [m4x3] "m"(b1ce9c0_m4x3), [m3x3v] "m"(b1ce9c0_m3x3v)
      : "memory");
}
#else
#error "FUN_001ce9c0: clang naked draft required"
#endif


/* FUN_001cebb0 (0x1cebb0) — XBE naked draft (batch 266). */
#if defined(__clang__)
static void *(*const b1cebb0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b1cebb0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1cebb0_exitfn)(int) = system_exit;
static void *(*const b1cebb0_tag)(int, int) = tag_get;
static void * (*const b1cebb0_c1c88c0)(short class_index) = sound_class_get_definition;
static short (*const b1cebb0_c1cd8b0)(int sound_handle) = FUN_001cd8b0;
static void (*const b1cebb0_c1cbd30)(int sound_handle, void *summary) = sound_collect_like_sounds;
static short (*const b1cebb0_c1ccd70)(int sound_handle, short *channels, short count) = sound_find_oldest_channel;

__attribute__((naked, noinline))
short FUN_001cebb0(int sound_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x48, %%esp\n\t"
      "movl 0x4fdba4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movw 0x8c(%%ebx), %%si\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $-1, %%si\n\t"
      "je .LFUN_001cebb0_4\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_001cebb0_1\n\t"
      "cmpw 0x4eb0b4, %%si\n\t"
      "jl .LFUN_001cebb0_2\n\t"
      ".LFUN_001cebb0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x428\n\t"
      "pushl $0x2c12cc\n\t"
      "pushl $0x2c1294\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001cebb0_2:\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "cmpl %%edi, 0x4fc3a0(,%%ecx,8)\n\t"
      "je .LFUN_001cebb0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x6d0\n\t"
      "pushl $0x2c12cc\n\t"
      "pushl $0x2c1890\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001cebb0_3:\n\t"
      "movw 0x8c(%%ebx), %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001cebb0_4:\n\t"
      "movl 0x8(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x736e6421\n\t"
      "call *%[tag]\n\t"
      "movswl 0x4(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c88c0]\n\t"
      "movb 0x8(%%eax), %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_001cebb0_11\n\t"
      "cmpl $-1, 0xc(%%ebx)\n\t"
      "je .LFUN_001cebb0_11\n\t"
      "movl 0x4eb0b4, %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_001cebb0_9\n\t"
      ".LFUN_001cebb0_5:\n\t"
      "testw %%di, %%di\n\t"
      "jl .LFUN_001cebb0_6\n\t"
      "cmpw %%ax, %%di\n\t"
      "jl .LFUN_001cebb0_7\n\t"
      ".LFUN_001cebb0_6:\n\t"
      "pushl $1\n\t"
      "pushl $0x428\n\t"
      "pushl $0x2c12cc\n\t"
      "pushl $0x2c1294\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001cebb0_7:\n\t"
      "movswl %%di, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal 0x4fc3a0(,%%eax,8), %%eax\n\t"
      "movl (%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001cebb0_8\n\t"
      "movl 0x4fdba4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "movl 0xc(%%ebx), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jne .LFUN_001cebb0_8\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x736e6421\n\t"
      "call *%[tag]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c88c0]\n\t"
      "movb 0x8(%%eax), %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_001cebb0_10\n\t"
      ".LFUN_001cebb0_8:\n\t"
      "movl 0x4eb0b4, %%eax\n\t"
      "incl %%edi\n\t"
      "cmpw %%ax, %%di\n\t"
      "jl .LFUN_001cebb0_5\n\t"
      ".LFUN_001cebb0_9:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1cd8b0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001cebb0_10:\n\t"
      "movw 0x14(%%esi), %%dx\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%dx, 0x14(%%ebx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001cebb0_11:\n\t"
      "pushl %%edi\n\t"
      "leal -0x48(%%ebp), %%esi\n\t"
      "call *%[c1cbd30]\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "cmpw -0x2(%%ebp), %%ax\n\t"
      "jl .LFUN_001cebb0_12\n\t"
      "pushl %%eax\n\t"
      "leal -0x22(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1ccd70]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001cebb0_12:\n\t"
      "movl -0x48(%%ebp), %%eax\n\t"
      "cmpw -0x26(%%ebp), %%ax\n\t"
      "jl .LFUN_001cebb0_13\n\t"
      "pushl %%eax\n\t"
      "leal -0x46(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c1ccd70]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001cebb0_13:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1cd8b0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b1cebb0_dget), [assert] "m"(b1cebb0_assert), [exitfn] "m"(b1cebb0_exitfn), [tag] "m"(b1cebb0_tag), [c1c88c0] "m"(b1cebb0_c1c88c0), [c1cd8b0] "m"(b1cebb0_c1cd8b0), [c1cbd30] "m"(b1cebb0_c1cbd30), [c1ccd70] "m"(b1cebb0_c1ccd70)
      : "memory");
}
#else
#error "FUN_001cebb0: clang naked draft required"
#endif


/* FUN_001cf100 (0x1cf100) — XBE naked draft (batch 275). */
#if defined(__clang__)
static int (*const b1cf100_c1198f0)(data_t *data, int prev_index) = data_next_index;
static void *(*const b1cf100_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1cf100_tag)(int, int) = tag_get;
static void (*const b1cf100_c1196d0)(data_t *data, int datum_handle) = datum_delete;
static void *(*const b1cf100_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1cf100_c1cd390)(void *track_entry, float *out) = FUN_001cd390;
static char (*const b1cf100_c1cc200)(int looping_handle, void *source, void *position) = FUN_001cc200;
static int (*const b1cf100_c1ce180)(int sound_tag_index, void *source, int object_handle, int track_data, void *track_data_ptr, int track_data_size) = sound_start;
static unsigned int *(*const b1cf100_lseed)(void) = random_math_get_local_seed_address;
static float (*const b1cf100_rrange)(int *, float, float) = random_real_range;
static void (*const b1cf100_ftol)(void) = FUN_001d9068;

__attribute__((naked, noinline))
void FUN_001cf100(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x74, %%esp\n\t"
      "movl 0x4fdba0, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1198f0]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "je .LFUN_001cf100_10\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "jmp .LFUN_001cf100_2\n\t"
      ".LFUN_001cf100_1:\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_001cf100_2:\n\t"
      "movl 0x4fdba0, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x4(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x6c736e64\n\t"
      "call *%[tag]\n\t"
      "movb 0x4eaf54, %%cl\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x4c(%%ebx), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpb %%cl, %%al\n\t"
      "movl %%esi, -0x18(%%ebp)\n\t"
      "je .LFUN_001cf100_3\n\t"
      "movl 0x4fdba0, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1196d0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_001cf100_9\n\t"
      ".LFUN_001cf100_3:\n\t"
      "cmpw $2, 0x52(%%ebx)\n\t"
      "je .LFUN_001cf100_9\n\t"
      "movl 0x48(%%esi), %%edx\n\t"
      "leal 0x48(%%esi), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "jle .LFUN_001cf100_9\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      ".LFUN_001cf100_4:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl $0x68\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x54(%%ebx,%%eax,4), %%ecx\n\t"
      "movl 0x4eaf4c, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jge .LFUN_001cf100_8\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_001cf100_8\n\t"
      "pushl %%eax\n\t"
      "pushl $0x736e6421\n\t"
      "call *%[tag]\n\t"
      "movl 0x10(%%ebx), %%edx\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movl 0x1c(%%edi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testb $1, %%al\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "je .LFUN_001cf100_5\n\t"
      "movb 0x4d(%%ebx), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_001cf100_7\n\t"
      ".LFUN_001cf100_5:\n\t"
      "testb $2, %%al\n\t"
      "je .LFUN_001cf100_6\n\t"
      "movb 0x4d(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001cf100_7\n\t"
      ".LFUN_001cf100_6:\n\t"
      "movl 0x18(%%edi), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw %%ax, 0xc(%%ebx)\n\t"
      "leal -0x34(%%ebp), %%esi\n\t"
      "sete %%al\n\t"
      "movl %%ecx, -0x6c(%%ebp)\n\t"
      "movl %%edx, -0x70(%%ebp)\n\t"
      "incl %%eax\n\t"
      "movw %%ax, -0x74(%%ebp)\n\t"
      "call *%[c1cd390]\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "leal -0x74(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1cc200]\n\t"
      "movl 0xc(%%edi), %%ecx\n\t"
      "pushl $0xc\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x1cc200\n\t"
      "pushl %%esi\n\t"
      "leal -0x74(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ce180]\n\t"
      "movl -0x18(%%ebp), %%esi\n\t"
      "addl $0x24, %%esp\n\t"
      ".LFUN_001cf100_7:\n\t"
      "movl 0x10(%%esi), %%edx\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl 0x14(%%edi), %%ecx\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "movl 0x10(%%edi), %%edx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "call *%[lseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fsubs -0x10(%%ebp)\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fmuls 0x254cb8\n\t"
      "fiaddl 0x84(%%edx)\n\t"
      "fiaddl 0x4eaf4c\n\t"
      "call *%[ftol]\n\t"
      "fstp %%st(0)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x54(%%ebx,%%ecx,4)\n\t"
      ".LFUN_001cf100_8:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl 0x48(%%esi), %%edx\n\t"
      "incl %%eax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "leal 0x48(%%esi), %%eax\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jl .LFUN_001cf100_4\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      ".LFUN_001cf100_9:\n\t"
      "movl 0x4fdba0, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c1198f0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jne .LFUN_001cf100_1\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001cf100_10:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1198f0] "m"(b1cf100_c1198f0), [dget] "m"(b1cf100_dget), [tag] "m"(b1cf100_tag), [c1196d0] "m"(b1cf100_c1196d0), [elem] "m"(b1cf100_elem), [c1cd390] "m"(b1cf100_c1cd390), [c1cc200] "m"(b1cf100_c1cc200), [c1ce180] "m"(b1cf100_c1ce180), [lseed] "m"(b1cf100_lseed), [rrange] "m"(b1cf100_rrange), [ftol] "m"(b1cf100_ftol)
      : "memory");
}
#else
#error "FUN_001cf100: clang naked draft required"
#endif


/* FUN_001cf360 (0x1cf360) — XBE naked draft (batch 268). */
#if defined(__clang__)
static int (*const b1cf360_c1198f0)(data_t *data, int prev_index) = data_next_index;
static void *(*const b1cf360_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1cf360_tag)(int, int) = tag_get;
static void *(*const b1cf360_elem)(void *, int, int) = tag_block_get_element;
static int (*const b1cf360_c1be550)(void *permutation, int a2, int a3, int a4) = sound_cache_request_sound;
static void * (*const b1cf360_c1c88c0)(short class_index) = sound_class_get_definition;
static void (*const b1cf360_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1cf360_exitfn)(int) = system_exit;
static void (*const b1cf360_c1cca60)(int sound_handle) = sound_stop_channel;
static short (*const b1cf360_c1cebb0)(int sound_handle) = FUN_001cebb0;
static bool (*const b1cf360_c1cb790)(short compression, short encoding, unsigned short sample_rate, short spatialization_mode, unsigned short type_flags) = sound_valid_for_channel;

__attribute__((naked, noinline))
void FUN_001cf360(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x4fdba4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1198f0]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "je .LFUN_001cf360_12\n\t"
      "pushl %%esi\n\t"
      "jmp .LFUN_001cf360_2\n\t"
      ".LFUN_001cf360_1:\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "jmp .LFUN_001cf360_2\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_001cf360_2:\n\t"
      "movl 0x4fdba4, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x84(%%esi), %%edx\n\t"
      "movl 0x4eaf4c, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jg .LFUN_001cf360_14\n\t"
      "cmpw %%bx, 0x8c(%%esi)\n\t"
      "jne .LFUN_001cf360_5\n\t"
      "movswl 0x90(%%esi), %%eax\n\t"
      "movswl 0x8e(%%esi), %%ecx\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl $0x7c\n\t"
      "pushl %%eax\n\t"
      "pushl $0x48\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x736e6421\n\t"
      "call *%[tag]\n\t"
      "addl $0x98, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0x3c, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c1be550]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001cf360_5\n\t"
      "cmpw %%bx, 0x8c(%%esi)\n\t"
      "jne .LFUN_001cf360_11\n\t"
      "cmpl $0x1cc200, 0x10(%%esi)\n\t"
      "je .LFUN_001cf360_11\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x736e6421\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%ebx), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c88c0]\n\t"
      "movswl 0xc(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_001cf360_3\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001cf360_11\n\t"
      "pushl $1\n\t"
      "pushl $0x679\n\t"
      "pushl $0x2c12cc\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_001cf360_11\n\t"
      ".LFUN_001cf360_3:\n\t"
      "movswl 0x8e(%%esi), %%edx\n\t"
      "pushl $0x48\n\t"
      "pushl %%edx\n\t"
      "addl $0x98, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $-1, 0x3a(%%eax)\n\t"
      "jne .LFUN_001cf360_4\n\t"
      "movw 0x90(%%esi), %%cx\n\t"
      "movw %%cx, 0x3a(%%eax)\n\t"
      ".LFUN_001cf360_4:\n\t"
      "movl %%edi, %%ebx\n\t"
      "call *%[c1cca60]\n\t"
      "jmp .LFUN_001cf360_11\n\t"
      ".LFUN_001cf360_5:\n\t"
      "orb $2, 0x4(%%esi)\n\t"
      "pushl %%edi\n\t"
      "call *%[c1cebb0]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "cmpw $-1, %%bx\n\t"
      "je .LFUN_001cf360_4\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .LFUN_001cf360_6\n\t"
      "cmpw 0x4eb0b4, %%bx\n\t"
      "jl .LFUN_001cf360_7\n\t"
      ".LFUN_001cf360_6:\n\t"
      "pushl $1\n\t"
      "pushl $0x428\n\t"
      "pushl $0x2c12cc\n\t"
      "pushl $0x2c1294\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001cf360_7:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movswl %%bx, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%edi\n\t"
      "movl 0x4fc3a0(,%%edi,8), %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "leal 0x4fc3a0(,%%edi,8), %%edi\n\t"
      "je .LFUN_001cf360_13\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x736e6421\n\t"
      "call *%[tag]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%edi), %%cx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x14(%%esi), %%dx\n\t"
      "pushl %%ecx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x6(%%eax), %%cx\n\t"
      "pushl %%edx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x6c(%%eax), %%dx\n\t"
      "movswl 0x6e(%%eax), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1cb790]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001cf360_8\n\t"
      "pushl $1\n\t"
      "pushl $0x642\n\t"
      "pushl $0x2c12cc\n\t"
      "pushl $0x2c19c8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001cf360_8:\n\t"
      "movl (%%edi), %%ebx\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .LFUN_001cf360_9\n\t"
      "call *%[c1cca60]\n\t"
      ".LFUN_001cf360_9:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x4eaf4c, %%edx\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "movl %%edx, 0x84(%%esi)\n\t"
      ".LFUN_001cf360_10:\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      ".LFUN_001cf360_11:\n\t"
      "movl 0x4fdba4, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c1198f0]\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .LFUN_001cf360_1\n\t"
      "popl %%esi\n\t"
      ".LFUN_001cf360_12:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001cf360_13:\n\t"
      "cmpw %%bx, 0x8c(%%esi)\n\t"
      "je .LFUN_001cf360_10\n\t"
      "pushl $1\n\t"
      "pushl $0x654\n\t"
      "pushl $0x2c12cc\n\t"
      "pushl $0x2c1998\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_001cf360_10\n\t"
      ".LFUN_001cf360_14:\n\t"
      "testb $1, 0x4(%%esi)\n\t"
      "jne .LFUN_001cf360_11\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x736e6421\n\t"
      "call *%[tag]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c88c0]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $1, 0xc(%%eax)\n\t"
      "je .LFUN_001cf360_11\n\t"
      "pushl $1\n\t"
      "pushl $0x683\n\t"
      "pushl $0x2c12cc\n\t"
      "pushl $0x2c18e8\n\t"
      "call *%[assert]\n\t"
      "pushl %%ebx\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_001cf360_11\n\t"
      :
      : [c1198f0] "m"(b1cf360_c1198f0), [dget] "m"(b1cf360_dget), [tag] "m"(b1cf360_tag), [elem] "m"(b1cf360_elem), [c1be550] "m"(b1cf360_c1be550), [c1c88c0] "m"(b1cf360_c1c88c0), [assert] "m"(b1cf360_assert), [exitfn] "m"(b1cf360_exitfn), [c1cca60] "m"(b1cf360_c1cca60), [c1cebb0] "m"(b1cf360_c1cebb0), [c1cb790] "m"(b1cf360_c1cb790)
      : "memory");
}
#else
#error "FUN_001cf360: clang naked draft required"
#endif


/* FUN_001cf820 (0x1cf820) — readable C lift. */
void FUN_001cf820(void **out)
{
  extern char DAT_0032fce4[];
  *out = DAT_0032fce4;
}
/* --- sound_manager.obj orphan shells (2026-07-26) --- */

/* FUN_001ac180 (0x1ac180) — XBE naked draft (batch 255). */
#if defined(__clang__)
static void *(*const b1ac180_get)(int, int) = object_get_and_verify_type;
static void *(*const b1ac180_tag)(int, int) = tag_get;
static short (*const b1ac180_c120cb0)(int animation_graph_tag_index, const char *name) = FUN_00120cb0;
static int (*const b1ac180_c120f20)(int update_kind, int animation_graph_tag_index, int16_t animation_index) = model_animation_choose_random;
static void *(*const b1ac180_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1ac180_c140160)(int object_handle, int16_t region_count) = object_set_region_count;
static void (*const b1ac180_c1ab7c0)(int unit_handle, int anim_graph_tag_index, int16_t animation_index) = unit_set_animation;
static void (*const b1ac180_c1446a0)(int object_handle) = object_update_children_recursive;
static const char * (*const b1ac180_c1ba1f0)(int tag_index) = tag_get_name;
static void (*const b1ac180_cff550)(const char* format, ...) = console_warning;

__attribute__((naked, noinline))
char FUN_001ac180(int actor __attribute__((unused)), int anim_tag __attribute__((unused)), void *entry __attribute__((unused)), int do_flag __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "xorb %%al, %%al\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_001ac180_7\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_001ac180_6\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "pushl %%edi\n\t"
      "pushl $0x616e7472\n\t"
      "call *%[tag]\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c120cb0]\n\t"
      "addl $0x20, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001ac180_4\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "call *%[c120f20]\n\t"
      "movswl %%ax, %%edx\n\t"
      "pushl $0xb4\n\t"
      "pushl %%edx\n\t"
      "addl $0x74, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movw 0x20(%%eax), %%ax\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpw $1, %%ax\n\t"
      "je .LFUN_001ac180_5\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .LFUN_001ac180_5\n\t"
      "cmpb $0x1c, 0x253(%%esi)\n\t"
      "jne .LFUN_001ac180_2\n\t"
      "movw 0x80(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_001ac180_2\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl $0xb4\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movw 0x42(%%eax), %%cx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw 0x42(%%edx), %%cx\n\t"
      "jne .LFUN_001ac180_2\n\t"
      "movw 0x34(%%eax), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x82(%%esi), %%cx\n\t"
      "movswl %%cx, %%edx\n\t"
      "movswl %%ax, %%ebx\n\t"
      "addl $2, %%edx\n\t"
      "cmpl %%ebx, %%edx\n\t"
      "jne .LFUN_001ac180_1\n\t"
      "decl %%ecx\n\t"
      "popl %%edi\n\t"
      "movw %%cx, 0x82(%%esi)\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001ac180_1:\n\t"
      "cmpw %%ax, %%cx\n\t"
      "jl .LFUN_001ac180_5\n\t"
      ".LFUN_001ac180_2:\n\t"
      "movb 0x14(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001ac180_3\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $6\n\t"
      "pushl %%eax\n\t"
      "call *%[c140160]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001ac180_3:\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movb $0x1c, 0x253(%%esi)\n\t"
      "call *%[c1ab7c0]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "orb $1, 0x248(%%esi)\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1446a0]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001ac180_4:\n\t"
      "pushl %%edi\n\t"
      "call *%[c1ba1f0]\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl $0x29c71c\n\t"
      "call *%[cff550]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_001ac180_5:\n\t"
      "xorb %%al, %%al\n\t"
      ".LFUN_001ac180_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001ac180_7:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b1ac180_get), [tag] "m"(b1ac180_tag), [c120cb0] "m"(b1ac180_c120cb0), [c120f20] "m"(b1ac180_c120f20), [elem] "m"(b1ac180_elem), [c140160] "m"(b1ac180_c140160), [c1ab7c0] "m"(b1ac180_c1ab7c0), [c1446a0] "m"(b1ac180_c1446a0), [c1ba1f0] "m"(b1ac180_c1ba1f0), [cff550] "m"(b1ac180_cff550)
      : "memory");
}
#else
#error "FUN_001ac180: clang naked draft required"
#endif

