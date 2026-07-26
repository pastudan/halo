/* Game sound subsystem — manages looping sounds attached to objects. */

void game_sound_initialize(void)
{
  *(void **)0x5054e4 =
    game_state_data_new("object looping sounds", 0x400, 0x34);
  *(void **)0x5054e0 = game_state_malloc("game sound globals", 0, 8);
}

void game_sound_dispose(void)
{
  if (*(void **)0x5054e4 != 0)
    *(void **)0x5054e4 = 0;
}

void game_sound_initialize_for_new_map(void)
{
  if (*(void **)0x5054e4 != 0) {
    ((void (*)(void *))0x119b20)(*(void **)0x5054e4);
    *(int *)(*(char **)0x5054e0 + 4) = -1;
    *(int *)(*(char **)0x5054e0) = 0;
  }
}

/* Delete a looping-sound datum entry from the object-looping-sounds table
 * (0x1c7330).
 *
 * Preconditions checked via assert:
 *   - The lsnd tag's runtime_scripting_sound_index must NOT point at this
 *     entry (the caller is responsible for clearing tag+0x1c before calling
 *     here if it was set).
 *   - If runtime_scripting_sound_index != NONE, it must reference a valid
 *     live datum.
 *
 * Then unconditionally deletes the datum from DAT_005054e4.
 */
void game_looping_sound_delete(int sound_handle)
{
  void *entry;
  void *tag;
  int scripting_index;

  entry = datum_get(*(data_t **)0x5054e4, sound_handle);
  tag = tag_get(0x6c736e64, *(int *)((char *)entry + 0xc));

  scripting_index = *(int *)((char *)tag + 0x1c);
  if (scripting_index == sound_handle) {
    display_assert(
      "definition->runtime_scripting_sound_index!=looping_sound_index",
      "c:\\halo\\SOURCE\\sound\\game_sound.c", 0x118, 1);
    system_exit(-1);
  }

  scripting_index = *(int *)((char *)tag + 0x1c);
  if (scripting_index != -1) {
    if (datum_get(*(data_t **)0x5054e4, scripting_index) == 0) {
      display_assert(
        "definition->runtime_scripting_sound_index==NONE || "
        "game_looping_sound_get(definition->runtime_scripting_sound_index)",
        "c:\\halo\\SOURCE\\sound\\game_sound.c", 0x119, 1);
      system_exit(-1);
    }
  }

  datum_delete(*(data_t **)0x5054e4, sound_handle);
}

/* Play a spatialized sound impulse at a world location (0x1c73d0).
 * Copies 44 bytes of location data into a sound_params struct with
 * spatialization_mode=1 (positional), then forwards to sound_start. */
void unattached_impulse_sound_new(int sound_tag_index, void *location,
                                  float scale)
{
  char sound_params[0x40];

  if (!location) {
    display_assert("location", "c:\\halo\\SOURCE\\sound\\game_sound.c", 0x148,
                   1);
    system_exit(-1);
  }
  if (scale < 0.0f || !(scale <= 1.0f)) {
    error(2, "DIAG scale OOB in 0x1c73d0: scale=%f tag=0x%x", (double)scale,
          sound_tag_index);
    display_assert("scale>=0.f && scale<=1.f",
                   "c:\\halo\\SOURCE\\sound\\game_sound.c", 0x149, 1);
    system_exit(-1);
  }

  {
    int *dst = (int *)(sound_params + 0x0c);
    int *src = (int *)location;
    int i;
    for (i = 0; i < 11; i++)
      dst[i] = src[i];
  }
  *(float *)(sound_params + 0x04) = scale;
  *(int16_t *)(sound_params + 0x00) = 1;
  *(float *)(sound_params + 0x08) = 1.0f;

  sound_start(sound_tag_index, sound_params, NONE, 0, 0, 0);
}

/* Play a one-shot sound impulse at a given volume scale.
 * Builds a minimal sound source descriptor (spatialization_mode=0,
 * scale, gain=1.0f) and forwards to sound_start (0x1ce180) with
 * no object attachment, no track data. */
int sound_impulse_start(int sound_tag_index, float scale)
{
  /* 64-byte sound source descriptor — only first 12 bytes matter here.
   * offset 0x00: int16_t spatialization_mode
   * offset 0x04: float   scale
   * offset 0x08: float   gain */
  char source[0x40];

  assert_halt(scale >= 0.f && scale <= 1.f);

  *(int16_t *)(source + 0x00) = 0;
  *(float *)(source + 0x04) = scale;
  *(float *)(source + 0x08) = 1.0f;

  /* original returns the sound datum handle (or -1) from this tail call;
   * callers like hud_sounds_update (FUN_000d70b0) store it for sound_stop_impulse. */
  return sound_start(sound_tag_index, source, NONE, 0, 0, 0);
}

bool FUN_001c7a10(int object_handle, void *attachment_data, void *source)
{
  void *object;
  int location[2];
  float *node_matrix;
  int marker_index;

  object = object_try_and_get_and_verify_type(object_handle, -1);

  assert_halt(attachment_data);
  assert_halt(source);

  if (object != 0) {
    object_get_location(object_handle, location);

    if ((int16_t)location[1] != -1) {
      if (*(int16_t *)((char *)attachment_data + 2) == -1) {
        marker_index = 0;
      } else {
        marker_index = (int)*(int16_t *)((char *)attachment_data + 2);
      }

      node_matrix =
        (float *)object_get_node_matrix(object_handle, marker_index);

      *(int *)((char *)source + 0x30) = location[0];
      *(int *)((char *)source + 0x34) = location[1];

      matrix_transform_point(node_matrix,
                             (float *)((char *)attachment_data + 4),
                             (float *)((char *)source + 0xc));
      matrix_transform_vector(node_matrix,
                              (float *)((char *)attachment_data + 0x10),
                              (float *)((char *)source + 0x18));
      object_get_root_location(object_handle, (float *)((char *)source + 0x24),
                               0);

      return true;
    }
  }

  return false;
}

bool sound_cluster_is_audible(void *location)
{
  int16_t cluster_index;

  cluster_index = *(int16_t *)((char *)location + 4);
  if (cluster_index >= -1) {
    if ((int)cluster_index < *(int *)((char *)scenario_get() + 0x134)) {
      if (cluster_index != -1 &&
          ((((uint32_t *)0x5054a0)[(int)cluster_index >> 5] &
            (1u << ((uint8_t)cluster_index & 0x1f))) != 0)) {
        return true;
      }
      return false;
    }
  }

  display_assert(
    "location->cluster_index>=NONE && "
    "location->cluster_index<global_structure_bsp_get()->clusters.count",
    "c:\\halo\\SOURCE\\sound\\game_sound.c", 0x364, 1);
  system_exit(-1);
}

/* Check whether the lsnd tag (index passed in EAX) has a playlist
 * containing any snd! entry whose flags field (int16 at offset 4)
 * equals 0x20.  The 0x20 flag identifies sounds that should play for
 * vehicle-related music contexts.  Called by
 * game_sound_music_stop_for_vehicle (0x1c7d70) with the current
 * looping-sound entry's lsnd tag index (entry+0xc) in EAX to decide
 * whether to suppress normal music playback.
 *
 * Returns true if any playlist entry references a 'snd!' tag with
 * flags == 0x20; false otherwise.
 */
bool game_sound_music_has_vehicle_sound(int in_EAX)
{
  void *lsnd_tag;
  int *playlist; /* pointer to the block at lsnd+0x3c (count, ptr) */
  int16_t i;
  void *element;
  int sound_handle;
  void *snd_tag;

  /* The lsnd tag index arrives in EAX (0x1c7d13: PUSH EAX; PUSH 'lsnd').
   * The caller (0x1c7d70) loads it from the looping-sound entry+0xc. */
  lsnd_tag = tag_get(0x6c736e64, in_EAX);
  playlist = (int *)((char *)lsnd_tag + 0x3c);

  i = 0;
  while ((int)i < *playlist) {
    element = tag_block_get_element(playlist, (int)i, 0xa0);
    sound_handle = *(int *)((char *)element + 0x4c);
    if (sound_handle != -1) {
      snd_tag = tag_get(0x736e6421, sound_handle);
      if (*(int16_t *)((char *)snd_tag + 0x4) == 0x20) {
        return true;
      }
    }
    i = i + 1;
  }
  return false;
}

/* Suppress non-vehicle music when a vehicle sound should take over
 * (0x1c7d70).
 *
 * Iterates all active looping-sound entries.  For each entry whose music
 * override slot ([+0x10]) is NONE (-1), and whose lsnd tag reference ([+0xc])
 * is valid, and where game_sound_music_has_vehicle_sound() is true, the
 * function fetches the lsnd tag and, if it currently has a playing sound
 * ([tag+0x1c] != -1):
 *   - Clears bit 0x10 (non-vehicle music flag) from the playing entry flags.
 *   - Sets  bit 0x02 (stop/fade flag) on the playing entry flags.
 *   - Clears the tag's runtime handle ([tag+0x1c] = NONE).
 *   - Sets  bit 0x04 on the playing entry flags.
 *
 * Called from sound_looping_start (0x1c8510) when the lsnd definition has
 * bit 0x04 set in its flags, before starting the new looping sound.
 */
void game_sound_music_stop_for_vehicle(void)
{
  int handle;
  char *entry;
  void *lsnd_tag;
  int playing_handle;
  char *playing_entry;

  for (handle = data_next_index(*(data_t **)0x5054e4, -1); handle != -1;
       handle = data_next_index(*(data_t **)0x5054e4, handle)) {
    entry = (char *)datum_get(*(data_t **)0x5054e4, handle);
    if (*(int *)(entry + 0x10) != -1)
      continue;
    if (!game_sound_music_has_vehicle_sound(*(int *)(entry + 0xc)))
      continue;
    if (*(int *)(entry + 0xc) == -1)
      continue;
    lsnd_tag = tag_get(0x6c736e64, *(int *)(entry + 0xc));
    playing_handle = *(int *)((char *)lsnd_tag + 0x1c);
    if (playing_handle == -1)
      continue;
    playing_entry = (char *)datum_get(*(data_t **)0x5054e4, playing_handle);
    *(uint32_t *)(playing_entry + 0x4) &= ~0x10u;
    /* Re-fetch using the same handle (result is the same pointer). */
    *(uint32_t *)((char *)datum_get(*(data_t **)0x5054e4, playing_handle) +
                  0x4) |= 0x2;
    *(int *)((char *)lsnd_tag + 0x1c) = -1;
    *(uint32_t *)(playing_entry + 0x4) |= 0x4;
  }
}

void game_sound_dispose_from_old_map(void)
{
  if (*(void **)0x5054e4 != 0 && *(uint8_t *)(*(char **)0x5054e4 + 0x24) != 0) {
    ((void (*)(void))0x1c70b0)();
    ((void (*)(void *))0x119550)(*(void **)0x5054e4);
  }
}

/* Start a sound at a position with a directional forward vector (0x1c7e70).
 * Builds a callback_data struct with marker/position/forward and a sound_params
 * struct, calls FUN_001c7a10 to resolve attachment, then sound_start. */
int object_impulse_sound_new(int object_handle, int tag_index, int16_t marker,
                             float *position, float *forward, float scale)
{
  char sound_params[0x40];
  char callback_data[0x1c];

  if (!position || !forward) {
    display_assert("position && forward",
                   "c:\\halo\\SOURCE\\sound\\game_sound.c", 0x12c, 1);
    system_exit(-1);
  }
  if (scale < 0.0f || scale > 1.0f) {
    error(2, "DIAG scale OOB in 0x1c7e70: scale=%f obj=0x%x tag=0x%x marker=%d",
          (double)scale, object_handle, tag_index, (int)marker);
    error(2, "DIAG pos=(%f,%f,%f) fwd=(%f,%f,%f)", (double)position[0],
          (double)position[1], (double)position[2], (double)forward[0],
          (double)forward[1], (double)forward[2]);
    display_assert("scale>=0.f && scale<=1.f",
                   "c:\\halo\\SOURCE\\sound\\game_sound.c", 0x12d, 1);
    system_exit(-1);
  }

  *(float *)(callback_data + 4) = position[0];
  *(float *)(callback_data + 8) = position[1];
  *(float *)(callback_data + 12) = position[2];
  *(float *)(callback_data + 16) = forward[0];
  *(float *)(callback_data + 20) = forward[1];
  *(float *)(callback_data + 24) = forward[2];

  *(int16_t *)(sound_params + 0) = 1;
  *(float *)(sound_params + 8) = 1.0f;
  *(int16_t *)(callback_data + 2) = marker;
  *(int16_t *)(sound_params + 0x34) = -1;

  if (!FUN_001c7a10(object_handle, callback_data, sound_params))
    return -1;

  *(float *)(sound_params + 4) = scale;
  return sound_start(tag_index, sound_params, object_handle, (int)&FUN_001c7a10,
                     callback_data, 0x1c);
}

/* sound_looping_stop (0x1c80e0)
 *
 * If sound_tag_index is valid, resolves the
 * `lsnd` tag and checks the
 * runtime looping-sound handle at tag+0x1c. When
 * present, clears bit 0x10
 * and sets bit 0x02 in the looping-sound entry
 * flags, then clears tag+0x1c
 * back to NONE (-1). */
void sound_looping_stop(int sound_tag_index)
{
  void *tag;
  int looping_sounds_handle;
  void *entry;

  if (sound_tag_index == -1)
    return;

  tag = tag_get(0x6c736e64, sound_tag_index);
  looping_sounds_handle = *(int *)((char *)tag + 0x1c);

  if (looping_sounds_handle != -1) {
    entry = datum_get(*(data_t **)0x5054e4, looping_sounds_handle);
    *(uint32_t *)((char *)entry + 4) &= 0xffffffef;

    entry = datum_get(*(data_t **)0x5054e4, *(int *)((char *)tag + 0x1c));
    *(uint32_t *)((char *)entry + 4) |= 2;

    *(int *)((char *)tag + 0x1c) = -1;
  }
}

/* Update the game sound subsystem for one tick.
 *
 * - Determines the current
 * sound environment (BSP cluster) via
 *   scenario_get_sound_environment, updates DirectSound
 * EAX/environment state via sound_manager_set_sound_environment, then
 * recalculates per-cluster audibility via FUN_001c7b40.
 * - Manages the music looping sound slot (globals[1]): starts, stops,
 *   or replaces it when the ambient sound environment changes.
 * - Iterates every active entry in the object-looping-sounds table and
 *   for each one either:
 *     (a) removes the entry if its object handle is invalid (NONE),
 *     (b) removes the entry and clears the tag's runtime index if the
 *         backing object no longer exists in the world,
 *     (c) calls FUN_001c77a0 to update the looping sound playback state
 *         when the sound is located in a visible cluster, or
 *     (d) advances without action otherwise.
 * - Increments the global tick counter (globals[0]) at exit.
 */
void game_sound_update(float dt)
{
  /* Out-params from scenario_get_sound_environment: sound_env_tag_index,
   * sound_env_data ptr, and a changed flag (bool). 0x18f600 writes a pointer
   * value INTO sound_env_data; cb9b0 then receives that pointer BY VALUE. */
  int sound_env_tag_index; /* [EBP-0x8]  tag index, or -1 */
  void *sound_env_data; /* [EBP-0xc]  pointer to EAX data block, written
                           by 0x18f600 */
  uint8_t env_changed; /* [EBP-0x1]  non-zero if env changed */

  /* 8-byte location struct returned by object_get_location (cluster_index etc.) */
  int location[2]; /* [EBP-0x14] */

  int looping_sounds_handle;
  void *entry;
  int object_handle;
  void *object;
  int object_looping_sounds; /* data_t* — *(int*)0x5054e4 */
  int music_handle; /* current music looping-sound slot handle */

  /* Determine the current sound environment (BSP cluster the listener is
   * in) and whether it changed since last tick. */
  scenario_get_sound_environment(&sound_env_tag_index, &sound_env_data,
                                 &env_changed);

  /* Copy the new environment block into the DirectSound globals area.
   * Original: `MOV EAX, [EBP-0xc]; PUSH EAX` — pass the POINTER VALUE
   * written by 0x18f600, not its address. */
  ((void (*)(void *))0x1cb9b0)(sound_env_data);

  /* Recompute per-BSP-cluster audibility bitmask for all players. */
  ((void (*)(void))0x1c7b40)();

  /* --- Music looping sound management ----------------------------------- */
  /* DAT_005054e0 points to the 8-byte game_sound_globals block:
   *   [0] = tick counter  (int)
   *   [1] = music looping sound handle  (int, -1 = none) */

  if (sound_env_tag_index == -1) {
    /* No sound environment: kill the music looping sound if one is active. */
    music_handle = *(int *)(*(int *)0x5054e0 + 4);
    if (music_handle != -1) {
      entry = datum_get(*(data_t **)0x5054e4, music_handle);
      *(uint32_t *)((char *)entry + 4) |= 2; /* set stop flag */
      *(int *)(*(int *)0x5054e0 + 4) = -1;
    }
  } else {
    music_handle = *(int *)(*(int *)0x5054e0 + 4);
    if (music_handle == -1) {
      /* Start a new music looping sound for this environment. */
      music_handle =
        ((int (*)(int, int, int))0x1c7710)(sound_env_tag_index, -1, 0x3f800000);
      *(int *)(*(int *)0x5054e0 + 4) = music_handle;
    } else {
      /* Check whether the environment changed. */
      entry = datum_get(*(data_t **)0x5054e4, music_handle);
      if (*(int *)((char *)entry + 0xc) != sound_env_tag_index) {
        /* Environment changed: stop old music and start new. */
        entry = datum_get(*(data_t **)0x5054e4, music_handle);
        *(uint32_t *)((char *)entry + 4) |= 2; /* set stop flag */
        music_handle = ((int (*)(int, int, int))0x1c7710)(sound_env_tag_index,
                                                          -1, 0x3f800000);
        *(int *)(*(int *)0x5054e0 + 4) = music_handle;
      }
    }
  }

  /* --- Per-entry update loop -------------------------------------------- */
  object_looping_sounds = *(int *)0x5054e4;

  looping_sounds_handle = data_next_index((data_t *)object_looping_sounds, -1);

  while (looping_sounds_handle != -1) {
    entry = datum_get((data_t *)object_looping_sounds, looping_sounds_handle);

    object_handle = *(int *)((char *)entry + 0x10);
    if (object_handle == -1) {
      /* No object attached — remove the entry outright. */
      ((void (*)(int, void *))0x1c77a0)(looping_sounds_handle, (void *)0);
    } else if ((*(uint8_t *)((char *)entry + 4) & 1) == 0 ||
               object_try_and_get_and_verify_type(
                 *(int *)((char *)entry + 0x10), -1) != NULL) {
      /* Object exists or scripted: check if it lives in an audible cluster.
       * object_get_and_verify_type = object_get_and_verify_type(handle, type_mask=-1) */
      object = object_get_and_verify_type(*(int *)((char *)entry + 0x10), -1);
      if ((*(uint32_t *)((char *)object + 4) & 0x800) != 0) {
        /* Object is in a visible cluster — get its location and maybe
         * update the looping sound. */
        int is_audible;
        object_get_location(*(int *)((char *)entry + 0x10), (void *)location);
        is_audible = sound_cluster_is_audible((void *)location);
        if ((uint8_t)is_audible != 0) {
          ((void (*)(int, int *))0x1c77a0)(looping_sounds_handle, location);
        }
      }
    } else {
      /* Object no longer exists in the world: clear the tag's runtime
       * scripting sound index if it pointed at this slot, then remove. */
      void *tag = tag_get(0x6c736e64, *(int *)((char *)entry + 0xc));
      if (*(int *)((char *)tag + 0x1c) == looping_sounds_handle) {
        *(int *)((char *)tag + 0x1c) = -1;
      }
      game_looping_sound_delete(looping_sounds_handle);
    }

    looping_sounds_handle =
      data_next_index((data_t *)object_looping_sounds, looping_sounds_handle);
  }

  /* Increment global tick counter. */
  *(int *)(*(int *)0x5054e0) += 1;
}

/* sound_compute_source_obstruction (0x1c8310)
 *
 * Computes sound obstruction/occlusion factors for an absolute-spatialized
 * sound source relative to a given player's observer camera.
 *
 * 1. Gets the observer camera for `channel_index` (a local player index).
 * 2. Pushes a collision user onto the global collision stack (user type 0x10).
 * 3. Asserts that `source->spatialization_mode ==
 * _sound_spatialization_mode_absolute`.
 * 4. Initialises source+0x38 = 0.6f (default gain), source+0x3C = 1.0f.
 * 5. If both source and camera have valid cluster indices:
 *    a. Queries the BSP cluster sound encoding between the two clusters.
 *    b. Converts the 7-bit encoding to a float distance (0..~256).
 *    c. If distance < 256.0 (not fully occluded):
 *       - Looks up cluster audibility data for the camera cluster.
 *       - If the source cluster is audible from the camera cluster,
 *         sets source+0x38 = 0.45f and raycasts from camera to source.
 *       - If the raycast finds no LOS, zeroes both fields.
 *       - If source+0x38 is non-zero, computes an obstruction factor
 *         from the cluster distance and sqrt_dist, clamped to [0, 1],
 *         and stores it in source+0x3C.
 * 6. Pops the collision user.
 */
void sound_compute_source_obstruction(int channel_index, void *source,
                                      float sqrt_dist)
{
  float *camera;
  int16_t source_cluster;
  float direction[3];
  int16_t collision_result[40]; /* 80 bytes */
  uint8_t sound_encoding;
  uint32_t encoding_bits;
  float cluster_distance;
  void *bsp;
  uint32_t *audibility;
  int source_cluster_int;
  float obstruction;
  float clamped;

  camera = (float *)observer_get_camera(channel_index);

  /* Push collision user (type 0x10). */
  if (*(int16_t *)0x4761d8 >= 0x20) {
    display_assert("global_current_collision_user_depth < "
                   "MAXIMUM_COLLISION_USER_STACK_DEPTH",
                   "c:\\halo\\SOURCE\\sound\\game_sound.c", 0x370, 1);
    system_exit(-1);
  }
  {
    int depth = (int)*(int16_t *)0x4761d8;
    *(int16_t *)0x4761d8 += 1;
    *(int16_t *)(0x5a8c80 + depth * 2) = 0x10;
  }

  /* Default gain and obstruction factor.
   * These stores are placed before the assert in the original binary
   * (MSVC instruction scheduling interleaves them with the CMP/JZ). */
  *(float *)((char *)source + 0x38) = 0.6f;
  *(float *)((char *)source + 0x3c) = 1.0f;

  assert_halt_msg(
    *(int16_t *)source == 1,
    "source->spatialization_mode==_sound_spatialization_mode_absolute");

  source_cluster = *(int16_t *)((char *)source + 0x34);
  if (source_cluster != -1 && *(int16_t *)((char *)camera + 0x10) != -1) {
    /* Query cluster sound path encoding between camera and source clusters. */
    bsp = scenario_get();
    sound_encoding = structure_bsp_cluster_sound_encoding(
      bsp, *(int16_t *)((char *)camera + 0x10), source_cluster);
    encoding_bits = (uint32_t)(sound_encoding & 0x7f);
    cluster_distance = (float)(int)encoding_bits * *(float *)0x256148;

    if (cluster_distance < *(float *)0x2642a0) {
      source_cluster_int = (int)*(int16_t *)((char *)source + 0x34);

      /* Get cluster audibility bitfield for the camera's cluster. */
      bsp = scenario_get();
      audibility = structure_bsp_get_cluster_sound_data(
        bsp, *(int16_t *)((char *)camera + 0x10));

      /* Check if the source cluster is audible from the camera cluster. */
      if ((audibility[source_cluster_int >> 5] &
           (1u << ((uint8_t)source_cluster_int & 0x1f))) != 0) {
        *(float *)((char *)source + 0x38) = 0.45f;

        /* Raycast from camera to source to check line of sight. */
        direction[0] = *(float *)((char *)source + 0x0c) - camera[0];
        direction[1] = *(float *)((char *)source + 0x10) - camera[1];
        direction[2] = *(float *)((char *)source + 0x14) - camera[2];

        if (!FUN_0014df70(0xc0e1, camera, direction, -1, collision_result)) {
          /* No line of sight — fully occluded. */
          *(float *)((char *)source + 0x38) = 0.0f;
          *(float *)((char *)source + 0x3c) = 0.0f;
        }
      }

      /* Compute obstruction factor if gain is non-zero. */
      if (*(float *)((char *)source + 0x38) != *(float *)0x2533c0) {
        obstruction =
          *(float *)0x2533c8 - sqrt_dist / (cluster_distance + sqrt_dist);
        *(float *)((char *)source + 0x3c) = obstruction;
        clamped = obstruction * *(float *)0x256870;
        if (clamped < *(float *)0x2533c0)
          clamped = *(float *)0x2533c0;
        else if (clamped > *(float *)0x2533c8)
          clamped = *(float *)0x2533c8;
        *(float *)((char *)source + 0x3c) = clamped;
      }
    }
  }

  /* Pop collision user. */
  if (*(int16_t *)0x4761d8 <= 1) {
    display_assert("global_current_collision_user_depth > 1",
                   "c:\\halo\\SOURCE\\sound\\game_sound.c", 0x39c, 1);
    system_exit(-1);
  }
  *(int16_t *)0x4761d8 -= 1;
}

/* sound_looping_start (0x1c8510)
 *
 * Starts a looping-sound definition
 * (`lsnd`) for an optional object.
 * - Resolves the tag definition and first
 * calls sound_looping_stop to end
 *   any prior runtime instance for this
 * definition.
 * - Asserts that definition+0x1c (runtime_scripting_sound_index)
 * is NONE.
 * - If definition flags has bit 0x04 set, calls
 *   game_sound_music_stop_for_vehicle (0x1c7d70) before start.
 * - Calls 0x1c7710(sound_tag_index, object_index, scale), stores
 * returned
 *   looping-sound handle into definition+0x1c, and when valid sets
 * bit 0x10
 *   in the looping-sound entry flags at entry+0x04.
 */
void sound_looping_start(int sound_tag_index, int object_index, float scale)
{
  void *definition;
  int looping_sound_handle;
  void *entry;

  if (sound_tag_index == -1)
    return;

  definition = tag_get(0x6c736e64, sound_tag_index);
  sound_looping_stop(sound_tag_index);

  assert_halt_msg(*(int *)((char *)definition + 0x1c) == -1,
                  "definition->runtime_scripting_sound_index==NONE");

  if ((*(uint8_t *)definition & 4) != 0)
    game_sound_music_stop_for_vehicle();

  looping_sound_handle =
    ((int (*)(int, int, float))0x1c7710)(sound_tag_index, object_index, scale);
  *(int *)((char *)definition + 0x1c) = looping_sound_handle;

  if (looping_sound_handle != -1) {
    entry = datum_get(*(data_t **)0x5054e4, looping_sound_handle);
    *(uint32_t *)((char *)entry + 4) |= 0x10;
  }
}

/* game_sound_set_music_volume (0x1c8c80)
 *
 * For each of the 0x33 sound
 * classes whose name string contains
 * sound_name as a substring, calls
 * sound_class_get(i) (0x1c89d0, register-arg SI) and writes the clamped volume
 * and transition_ticks into the returned record: float  at [record+0x00] =
 * clamp(volume, 0.0f, 1.0f) int16_t at [record+0x08] = max(transition_ticks, 0)
 *
 * sound_class_get (0x1c89d0) expects its index in SI and returns a
 * pointer to the 0xc-byte class record in EAX.  Called via inline asm
 * because knowledge.py does not support @si register-arg functions.
 *
 * The class name string pointers live in a table at 0x32f5d0
 * (0x33 pointers, one per sound class).
 */
void game_sound_set_music_volume(const char *sound_name, float volume,
                                 int16_t transition_ticks)
{
  int i;
  const char **table = (const char **)0x32f5d0;
  float clamped;
  float *record;

  for (i = 0; i < 0x33; i++) {
    /* Skip empty class name slots. */
    if (table[i][0] == '\0')
      continue;
    /* Check whether this class name contains sound_name. */
    if (crt_strstr(table[i], sound_name) == NULL)
      continue;

    record = (float *)sound_class_get((int16_t)i);

    /* Clamp volume to [0.0f, 1.0f]. */
    clamped = volume;
    if (clamped < *(float *)0x2533c0)
      clamped = *(float *)0x2533c0;
    else if (clamped > *(float *)0x2533c8)
      clamped = *(float *)0x2533c8;

    *record = clamped;

    /* transition_ticks clamped to >= 0. */
    *(int16_t *)((char *)record + 0x8) =
      (transition_ticks < 0) ? 0 : transition_ticks;
  }
}
/* --- game_sound.obj batch drafts (2026-07-26) --- */

/* 0x1c6ca0 */
void FUN_001c6ca0(void)
{
  int eax = 0;
  int ebx = 0;

  FUN_001c6880((void *)(uintptr_t)ebx);
  /* test (char)eax, (char)eax -> je 0x1c6ce0 */
  FUN_001c6b20();
  /* test (char)eax, (char)eax -> je 0x1c6ce0 */
  FUN_001c6bf0();
  FUN_001c6d20();
  /* test (char)eax, (char)eax -> je 0x1c6d11 */
  FUN_001c6ed0();
  /* test (char)eax, (char)eax -> je 0x1c6d11 */
  FUN_001c6fb0();

  (void)eax;
  (void)ebx;
}

/* 0x1c6d20 */
void FUN_001c6d20(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int ebp = 0;

  file_open((void *)(uintptr_t)esi, 0);
  /* test (char)eax, (char)eax -> je 0x1c6d82 */
  file_read_from_position((void *)(uintptr_t)esi, 0, 12, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c6d79 */
  FUN_00118be0((void *)0x0032ec44, (void *)(uintptr_t)ecx, 0);
  /* cmp eax, 0x52494646 -> jne 0x1c6d79 */
  /* relift: cmp dword ptr [ebp - 4], 0x57415645 -> jne 0x1c6d79 */
  file_close((void *)(uintptr_t)esi);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)ebp;
}

/* 0x1c6d90 */
void FUN_001c6d90(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  file_open((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> je 0x1c6ebb */
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c6ea8 */
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x1c6e13 */
  FUN_00118be0((void *)0x0032ec68, (void *)(uintptr_t)edx, 0);
  /* cmp eax, ebx -> je 0x1c6e3a */
  /* test (char)eax, 1 -> je 0x1c6e0f */
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0x1c6dd6 */
  file_close((void *)(uintptr_t)edi);
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x1c6ea8 */
  /* cmp ecx, 0x2b11 -> je 0x1c6e88 */
  /* cmp ecx, 0x5622 -> je 0x1c6e88 */
  /* cmp ecx, 0xac44 -> je 0x1c6e88 */
  file_close((void *)(uintptr_t)edi);
  file_close((void *)(uintptr_t)edi);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x1c6ed0 */
void FUN_001c6ed0(void)
{
  int eax = 0;
  int edx = 0;
  int edi = 0;

  file_open((void *)(uintptr_t)edi, 0);
  /* test (char)eax, (char)eax -> je 0x1c6f9c */
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c6f93 */
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x1c6f50 */
  FUN_00118be0((void *)0x0032ec68, (void *)(uintptr_t)edx, 0);
  /* test (char)eax, 1 -> je 0x1c6f4c */
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0x1c6f10 */
  file_close((void *)(uintptr_t)edi);
  file_read_from_position((void *)(uintptr_t)edi, 0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x1c6f93 */
  file_close((void *)(uintptr_t)edi);

  (void)eax;
  (void)edx;
  (void)edi;
}

/* 0x1c6fb0 */
void FUN_001c6fb0(void)
{
  /* cmp (int16_t)eax, 8 -> jne 0x1c7001 */
  /* cmp (int16_t)eax, 0x10 -> je 0x1c7027 */
  display_assert((char *)0x002bc3a4, (char *)0x002bc3cc, 280, 0);
  system_exit(0);
}

/* 0x1c70b0 */
void game_sound_clear(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  data_next_index((void *)(uintptr_t)eax, 0);
  /* cmp edi, -1 -> je 0x1c7159 */
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('dnsl', 0);
  /* cmp eax, edi -> jne 0x1c7128 */
  /* relift: test byte ptr [esi + 4], 0x10 -> jne 0x1c711f */
  display_assert((char *)0x002bc428, (char *)0x002bc464, 175, 0);
  system_exit(0);
  /* cmp eax, -1 -> je 0x1c713c */
  datum_get((void *)(uintptr_t)eax, 0);
  data_next_index((void *)(uintptr_t)ecx, 0);
  /* cmp edi, -1 -> jne 0x1c70d0 */

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x1c7160 */
void game_sound_restore(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  data_next_index((void *)(uintptr_t)eax, 0);
  /* cmp esi, -1 -> je 0x1c71db */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test (char)ecx, 0x10 -> je 0x1c71c4 */
  tag_get('dnsl', 0);
  /* test (char)ecx, 2 -> jne 0x1c71b5 */
  datum_delete((void *)(uintptr_t)eax, 0);
  data_next_index((void *)(uintptr_t)ecx, 0);
  /* cmp esi, -1 -> jne 0x1c7180 */
  FUN_001b9b60(0, 0x736e6421);
  FUN_001b9b80(0);
  tag_get('!dns', 0);
  FUN_001b9b80(0);
  /* cmp eax, -1 -> jne 0x1c7200 */

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x1c7230 */
int game_looping_sound_new(int object_index, int sound_tag_index, void *marker_name, short scale_index)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x1c7263 */
  display_assert((char *)0x002bc488, (char *)0x002bc464, 239, 0);
  system_exit(0);
  /* cmp ebx, -1 -> je 0x1c7320 */
  /* cmp esi, -1 -> je 0x1c7290 */
  object_get_markers_by_string_id(0, (void *)(uintptr_t)edi, (void *)(uintptr_t)eax, 0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x1c7316 */
  data_new_at_index((void *)(uintptr_t)ecx);
  /* cmp edi, -1 -> je 0x1c730d */
  datum_get((void *)(uintptr_t)edx, 0);
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1c7500 */
int scripted_sound_time(int a0)
{
  int eax = 0;

  /* cmp eax, -1 -> je 0x1c7545 */
  tag_get('!dns', 0);
  /* cmp eax, -1 -> je 0x1c7545 */
  game_time_get();
  return 0;

  (void)eax;
}

/* 0x1c7550 */
void scripted_sound_stop(int a0)
{
  int eax = 0;

  /* cmp eax, -1 -> je 0x1c7595 */
  tag_get(0x736e6421, 0);
  /* cmp eax, -1 -> je 0x1c7594 */
  sound_stop_impulse(0);

  (void)eax;
}

/* 0x1c75a0 */
void scripted_foley_predict(int a0)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* cmp eax, -1 -> je 0x1c7641 */
  tag_get(0x6c736e64, 0);
  /* test eax, eax -> jle 0x1c763f */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 160);
  /* cmp eax, -1 -> je 0x1c7635 */
  tag_get('!dns', 0);
  /* cmp ecx, 1 -> jne 0x1c7635 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 72);
  /* test ecx, ecx -> je 0x1c7635 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 124);
  sound_cache_request_sound((void *)(uintptr_t)eax, 0, 0, 0);
  /* cmp eax, ecx -> jl 0x1c75d0 */

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x1c7650 */
void scripted_looping_sound_set_scale(int a0, float a1)
{
  int eax = 0;

  /* cmp eax, -1 -> je 0x1c76be */
  tag_get('dnsl', 0);
  /* cmp eax, -1 -> je 0x1c76be */
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)eax, 0x41 -> jne 0x1c76b8 */

  (void)eax;
}

/* 0x1c76c0 */
void scripted_looping_sound_set_alternate(int a0, int a1)
{
  int eax = 0;

  /* cmp eax, -1 -> je 0x1c7708 */
  tag_get('dnsl', 0);
  /* cmp eax, -1 -> je 0x1c7708 */
  datum_get((void *)(uintptr_t)eax, 0);

  (void)eax;
}

/* 0x1c7710 */
int unattached_looping_sound_start(int sound_tag, int param_2, int param_3)
{
  int ecx = 0;
  int esi = 0;

  tag_get(0x6c736e64, 0);
  game_looping_sound_new(0, 0, (void *)0x0025386f, 0);
  /* cmp esi, -1 -> je 0x1c775c */
  datum_get((void *)(uintptr_t)ecx, 0);
  return 0;

  (void)ecx;
  (void)esi;
}

/* 0x1c7770 */
void unattached_looping_sound_stop(int sound_index)
{
  int ecx = 0;

  datum_get((void *)(uintptr_t)ecx, 0);

  (void)ecx;
}

/* 0x1c77a0 */
void FUN_001c77a0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  datum_get((void *)(uintptr_t)eax, 0);
  tag_get('dnsl', 0);
  /* cmp eax, -1 -> je 0x1c77e7 */
  /* test (char)eax, 1 -> jne 0x1c780b */
  object_get_function_value(0, 0, (void *)(uintptr_t)edx);
  /* test (char)ebx, (char)ebx -> jne 0x1c784c */
  /* cmp (int16_t)eax, 2 -> je 0x1c783a */
  /* test (char)ecx, (char)ecx -> jne 0x1c784c */
  /* cmp (int16_t)eax, 2 -> je 0x1c783a */
  /* cmp eax, -1 -> je 0x1c78dc */
  object_get_node_matrix(0, ecx);
  /* test eax, eax -> jne 0x1c7891 */
  display_assert((char *)0x0029c114, (char *)0x002bc464, 617, 0);
  system_exit(0);
  matrix_transform_point((float *)(uintptr_t)edi, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  matrix_transform_vector((float *)(uintptr_t)edi, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  object_get_root_location(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  /* relift: cmp word ptr [esi + 2], (int16_t)ecx -> je 0x1c7900 */
  /* test (char)eax, (char)eax -> je 0x1c7900 */
  sound_refresh_looping(0, (void *)(uintptr_t)edi, (void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> je 0x1c783a */
  /* relift: test byte ptr [ebx], 2 -> jne 0x1c7959 */
  display_assert((char *)0x002bc570, (char *)0x002bc464, 655, 0);
  system_exit(0);
  /* relift: test byte ptr [esi + 4], 1 -> je 0x1c7834 */
  /* relift: cmp dword ptr [ebx + 0x1c], edi -> jne 0x1c79f0 */
  game_looping_sound_delete(0);
  /* test (char)eax, (char)eax -> je 0x1c79e6 */
  sound_refresh_looping(0, (void *)(uintptr_t)edi, (void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> jne 0x1c79e6 */
  /* relift: test byte ptr [esi + 4], 1 -> je 0x1c7834 */
  game_looping_sound_delete(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1c7ca0 */
void FUN_001c7ca0(void)
{
  int eax = 0;
  int ecx = 0;

  /* cmp eax, -1 -> je 0x1c7cff */
  tag_get(0x6c736e64, 0);
  /* cmp eax, -1 -> je 0x1c7cfd */
  datum_get((void *)(uintptr_t)eax, 0);
  datum_get((void *)(uintptr_t)ecx, 0);

  (void)eax;
  (void)ecx;
}

/* 0x1c7f80 */
void scripted_sound_new(int a0, int a1, float a2)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp edi, -1 -> je 0x1c80db */
  tag_get(0x736e6421, 0);
  sound_stop_impulse(0);
  game_time_get();
  /* test (char)eax, 0x41 -> jne 0x1c800d */
  /* cmp esi, -1 -> je 0x1c80c4 */
  object_get_markers_by_string_id(0, (void *)0x002909e4, (void *)(uintptr_t)edx, 0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x1c805b */
  object_impulse_sound_new(0, 0, eax, (float *)(uintptr_t)ecx, (float *)(uintptr_t)edx, 0.0f);
  /* cmp esi, -1 -> je 0x1c80d3 */
  FUN_0013c980(0, 0, 0);
  sound_impulse_start(0, 0.0f);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1c85a0 */
void FUN_001c85a0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test ecx, ecx -> je 0x1c86df */
  /* cmp ecx, esi -> jl 0x1c8629 */
  /* test dl, dl -> jne 0x1c8621 */
  /* test (char)ebx, dl -> je 0x1c8646 */
  /* test dl, dl -> jne 0x1c8640 */
  /* test (char)ebx, 8 -> je 0x1c8655 */
  /* cmp ecx, 0xffff8000 -> jge 0x1c8666 */
  /* test ecx, ecx -> jge 0x1c868c */
  /* relift: cmp dword ptr [edi], 0 -> jne 0x1c8747 */
  /* test ecx, ecx -> je 0x1c887a */
  /* test ecx, ecx -> je 0x1c887a */
  /* test ecx, ecx -> je 0x1c887a */
  /* test (char)ebx, dl -> je 0x1c87d6 */
  /* test (char)ebx, (char)ebx -> jne 0x1c87d0 */
  /* test dl, 8 -> je 0x1c87e5 */
  /* cmp ecx, 0xffff8000 -> jge 0x1c87fb */
  /* test ecx, ecx -> jge 0x1c8824 */
  /* test ecx, ecx -> jne 0x1c8791 */
  FUN_00118be0((void *)0x0032ecf4, (void *)(uintptr_t)eax, 0);
  /* cmp (int16_t)eax, 0x33 -> jl 0x1c8902 */
  display_assert((char *)0x002bcb40, (char *)0x002bcb78, 131, 0);
  system_exit(0);
  /* relift: cmp byte ptr [edx], 0 -> jne 0x1c892e */
  display_assert((char *)0x002bcb1c, (char *)0x002bcb78, 132, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi], 0x10 -> jle 0x1c8954 */
  display_assert((char *)0x002bcac8, (char *)0x002bcb78, 133, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi + 2], 0x10 -> jle 0x1c897b */
  display_assert((char *)0x002bca68, (char *)0x002bcb78, 134, 0);
  system_exit(0);
  game_state_malloc((char *)0x002bcba0, (char *)0, 612);
  /* mem[0x0050548c] = eax */
  /* mem[0x0050548c] = 0 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1c89db */
  /* cmp (int16_t)esi, 0x33 -> jl 0x1c89fb */
  display_assert((char *)0x002bcbc4, (char *)0x002bcbf0, 288, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1c8a24 */
  display_assert((char *)0x002bcbb0, (char *)0x002bcbf0, 289, 0);
  system_exit(0);
  /* relift: cmp byte ptr [eax], 0 -> je 0x1c8a7c */
  crt_strstr((char *)(uintptr_t)eax, (char *)(uintptr_t)ecx);
  /* test eax, eax -> je 0x1c8a7c */
  sound_class_get_definition(0);
  /* cmp (int16_t)esi, 0x33 -> jl 0x1c8a50 */
  /* relift: cmp byte ptr [eax], 0 -> je 0x1c8ad0 */
  crt_strstr((char *)(uintptr_t)eax, (char *)(uintptr_t)ebx);
  /* test eax, eax -> je 0x1c8ad0 */
  sound_class_get_definition(0);
  sound_class_get_definition(0);
  /* cmp (int16_t)esi, 0x33 -> jl 0x1c8aa0 */
  /* relift: cmp byte ptr [eax], 0 -> je 0x1c8b51 */
  crt_strstr((char *)(uintptr_t)eax, (char *)(uintptr_t)ebx);
  /* test eax, eax -> je 0x1c8b51 */
  /* test (char)eax, 0x41 -> jne 0x1c8b3f */
  sound_class_get_definition(0);
  /* cmp (int16_t)esi, 0x33 -> jl 0x1c8af1 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1c8b81 */
  /* cmp (int16_t)esi, 0x33 -> jl 0x1c8ba1 */
  display_assert((char *)0x002bcbc4, (char *)0x002bcbf0, 288, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1c8bca */
  display_assert((char *)0x002bcbb0, (char *)0x002bcbf0, 289, 0);
  system_exit(0);
  /* test edi, edi -> jle 0x1c8c51 */
  sound_class_get(0);
  /* cmp (int16_t)esi, 0x33 -> jl 0x1c8c10 */
  sound_class_get(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
