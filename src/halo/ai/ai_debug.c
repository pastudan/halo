
/* ai_debug_dispose: free actor_debug_array and actor_path_debug_array.
 *
 * Confirmed: __FILE__ = "c:\halo\SOURCE\ai\ai_debug.c"
 *   line 0xa0 (160) — actor_debug_array free
 *   line 0xa6 (166) — actor_path_debug_array free
 * Called from ai_dispose (0x3f6f0). */
void ai_debug_dispose(void)
{
  if (*(void **)0x331f58 != NULL) {
    debug_free(*(void **)0x331f58, "c:\\halo\\SOURCE\\ai\\ai_debug.c", 0xa0);
    *(void **)0x331f58 = NULL;
  }
  if (*(void **)0x331f5c != NULL) {
    debug_free(*(void **)0x331f5c, "c:\\halo\\SOURCE\\ai\\ai_debug.c", 0xa6);
    *(void **)0x331f5c = NULL;
  }
}

/* ai_debug_dispose_from_old_map: if a valid scenario is loaded and a current
 * encounter is selected (DAT_005ac9f4 != -1), copy the encounter name from the
 * scenario tag block into DAT_005ac9d2 and clear the dirty flag. Otherwise zero
 * the name buffer via csstrcpy with empty string.
 *
 * No __FILE__ string.  Called from ai_dispose_from_old_map (0x3f720) and
 * ai_handle_editing. */
void ai_debug_dispose_from_old_map(void)
{
  void *scenario;
  void *encounter;

  scenario = FUN_0018e3b0();
  if (scenario != NULL && *(int32_t *)0x5ac9f4 != -1) {
    encounter =
      tag_block_get_element((void *)((char *)scenario + 0x42c),
                            (int)(*(uint32_t *)0x5ac9f4 & 0xffff), 0xb0);
    csstrncpy((char *)0x5ac9d2, encounter, 0x20);
    *(uint8_t *)0x5ac9f1 = 0;
    return;
  }
  csstrcpy((char *)0x5ac9d2, (const char *)0x25386f);
}

/* ai_debug_clear_storage: assert that both debug arrays are allocated, then
 * zero them. Asserts actor_debug_array != NULL (line 0xd0 = 208) and
 * actor_path_debug_array != NULL (line 0xd3 = 211) before zeroing each.
 *
 * Confirmed: __FILE__ = "c:\halo\SOURCE\ai\ai_debug.c" (0x25ab74)
 *   line 0xd0 (208) — actor_debug_array assert
 *   line 0xd3 (211) — actor_path_debug_array assert
 * Called from ai_debug_initialize_for_new_map (ai_debug.obj, 0x4c0f0).
 *
 * Note: decompiler showed csmemset size for path array as &DAT_00394f80
 * (treating immediate as address dereference).  Disassembly confirms
 * PUSH 0x394f80 — it is a literal immediate size, not a pointer. */
void ai_debug_clear_storage(void)
{
  if (*(void **)0x331f58 == NULL) {
    display_assert("actor_debug_array", "c:\\halo\\SOURCE\\ai\\ai_debug.c",
                   0xd0, 1);
    system_exit(-1);
  }
  csmemset(*(void **)0x331f58, 0, 0x657c00);
  if (*(void **)0x331f5c == NULL) {
    display_assert("actor_path_debug_array", "c:\\halo\\SOURCE\\ai\\ai_debug.c",
                   0xd3, 1);
    system_exit(-1);
  }
  csmemset(*(void **)0x331f5c, 0, 0x394f80);
}

/* ai_debug_actor_deleted: scan actor_path_debug_array (0x20 entries, stride
 * 0x1ca7c) and clear the active flag (offset +0xc) for any entry whose actor
 * handle (offset +0x0) matches actor_handle.
 *
 * No __FILE__ string.  Called from actor_delete (actors.obj, 0x3cc10). */
void ai_debug_actor_deleted(int actor_handle)
{
  char *base;
  int off;
  int i;

  base = *(char **)0x331f5c;
  off = 0;
  for (i = 0x20; i != 0; i--) {
    if (*(char *)(base + off + 0xc) != '\0' &&
        *(int *)(base + off) == actor_handle) {
      *(char *)(base + off + 0xc) = '\0';
      base = *(char **)0x331f5c;
    }
    off += 0x1ca7c;
  }
}

/* ai_debug_get_path_storage (0x49120) — find or allocate a path debug storage
 * slot for actor_handle. Searches 0x20 entries (stride 0x1ca7c) in the
 * actor_path_debug_array. Returns an exact match, first inactive slot, or
 * evicts the oldest entry. Returns NULL if eviction finds no slot. */
void *ai_debug_get_path_storage(int actor_handle)
{
  char *base;
  char *entry;
  short best_slot;
  short i;
  short oldest_slot;
  int oldest_time;
  int off;

  best_slot = -1;
  i = 0;
  do {
    base = *(char **)0x331f5c;
    entry = base + (int)i * 0x1ca7c;
    if (*(int *)entry == actor_handle && *(char *)(entry + 0xd) == '\0') {
      best_slot = i;
      goto found;
    }
    if (best_slot == (short)-1 && *(char *)(entry + 0xc) == '\0') {
      best_slot = i;
    }
    i++;
  } while (i < 0x20);

  if (best_slot == (short)-1) {
    oldest_slot = -1;
    oldest_time = 0x7fffffff;
    off = 0;
    i = 0;
    do {
      base = *(char **)0x331f5c;
      entry = base + off;
      if (*(char *)(entry + 0xc) == '\0') {
        display_assert("path->valid", "c:\\halo\\SOURCE\\ai\\ai_debug.c",
                       0x123, 1);
        system_exit(-1);
      }
      if (*(int *)(entry + 4) < oldest_time) {
        oldest_time = *(int *)(entry + 4);
        oldest_slot = i;
      }
      off += 0x1ca7c;
      i++;
    } while (i < 0x20);
    best_slot = oldest_slot;
    if (best_slot == (short)-1) {
      return 0;
    }
  }

found:
  entry = *(char **)0x331f5c + (int)best_slot * 0x1ca7c;
  csmemset(entry, 0, 0x1ca7c);
  *(char *)(entry + 0xc) = 1;
  *(int *)entry = actor_handle;
  *(int *)(entry + 4) = game_time_get();
  return entry;
}

/* ai_debug_select_encounter: reset debug encounter state when encounter_idx
 * changes. Checks if the current encounter index (0x5ac9f4) differs from
 * encounter_idx; if so, updates the index, clears the debug-state byte at
 * 0x629d40, zeroes the 0x670-byte block at 0x629d44 and the 0x8000-byte block
 * at 0x62a3b4, then calls ai_debug_select_actor(encounter_idx, -1) to
 * reinitialize secondary state.
 *
 * No __FILE__ string.  Called from ai_debug_select_actor,
 * ai_debug_initialize_for_new_map, ai_debug_change_selected_encounter,
 * FUN_00054e40.
 *
 * Calling convention verified (ADD ESP,0x20 at 0x49267 covers 8 dwords):
 *   3 args to csmemset(0x629d44,...) + 3 args to csmemset(0x62a3b4,...) +
 *   2 args to ai_debug_select_actor = 8 dwords. ai_debug_select_actor is cdecl.
 *
 * Call-site verification:
 *   ai_debug_initialize_for_new_map @ 0x4c116: PUSH ESI (enc_idx) ->
 * encounter_idx [match] ai_debug_select_actor @ 0x4b1ca: PUSH EAX (param_1) ->
 * encounter_idx [match] */
void ai_debug_select_actor(int encounter_idx, int param_2);

void ai_debug_select_encounter(int encounter_idx)
{
  if (*(int32_t *)0x5ac9f4 != encounter_idx) {
    *(int32_t *)0x5ac9f4 = encounter_idx;
    *(uint8_t *)0x629d40 = 0;
    csmemset((void *)0x629d44, 0, 0x670);
    csmemset((void *)0x62a3b4, 0, 0x8000);
    ai_debug_select_actor(encounter_idx, -1);
  }
}

/* FUN_000494d0: set debug ray-test success flag.
 *
 * No __FILE__ string. Called from ai_debug_get_last_path (ray setup) and
 * FUN_000494e0 (ray render). */
void FUN_000494d0(char success)
{
  *(uint8_t *)0x5acab9 = success;
}

/* ai_debug_update: per-tick AI debug update.  Three independent debug actions:
 *
 *   1. Camera-follow (0x5ac9fc):  acquire actor or LOS-hit target, then
 *      build follow-camera state via the 0x5dfc0-0x5ff70 family.
 *
 *   2. Guard-position update (0x5ac9c2):  shift guard position history
 *      arrays forward in all scenario squads; print count and clear.
 *
 *   3. Actor-variant reset (0x5ac9c3):  reset all starting-location actor
 *      variant fields to 0xffff; print count and clear.
 *
 * No __FILE__ string.  Called from ai_update (0x41180).
 *
 * Inferred: push-then-fstp float args at 0x4abf3-0x4abf8 (FSTP replaces
 * pushed dummy values with FPU-computed float values).
 * Register aliasing verified: EBX=1 set at 0x4ab44, used as arg to
 * object_try_and_get_and_verify_type at 0x4ab5d and as byte value 1 for flag stores. */
void ai_debug_update(void)
{
  /* camera-reset flag */
  if (*(uint8_t *)0x5aca6a != '\0') {
    *(int32_t *)0x5accac = 0;
    *(int32_t *)0x5eccb0 = 0;
  }

  if (*(uint8_t *)0x5ac9fc != '\0') {
    /* camera-follow: actor-position path */
    if (*(uint8_t *)0x5ac9fd == '\0') {
      int actor = player_control_get_unit_index(0);
      if (actor != -1 && object_try_and_get_and_verify_type(actor, 1) != NULL) {
        float pos[3];
        int bone =
          biped_find_pathfinding_surface_index(actor, (vector3_t *)pos);
        if (bone != -1) {
          *(float *)0x5f91ac = pos[0];
          *(float *)0x5f91b0 = pos[1];
          *(float *)0x5f91b4 = pos[2];
          *(uint8_t *)0x5f91a8 = 1;
          *(int32_t *)0x5f91b8 = bone;
          *(int32_t *)0x5f91bc = actor;
        }
      }
    }

    /* camera-follow: LOS-hit path */
    if (*(uint8_t *)0x5ac9fe == '\0') {
      void *cam = observer_get_camera(0);
      if (cam != NULL) {
        float *fwd = *(float **)0x31fc50;
        float scale = *(float *)0x254cb8;
        float dir[3];
        char hitbuf[8];

        *(uint16_t *)0x5ac5d4 += 1;
        dir[0] = fwd[0] * scale;
        dir[1] = fwd[1] * scale;
        dir[2] = fwd[2] * scale;
        if (FUN_0014df70(0x21, (float *)cam, dir, -1, (int16_t *)hitbuf) != 0) {
          /* hitbuf offsets relative to local_20 (EBP-0x1c):
           * local_58 = EBP-0x58 = local_20 - 0x3c (+0x3c back from
           * local_20); Ghidra shows local_58/54/50/2c.
           * Confirmed from disasm: MOV EAX,[EBP-0x54] etc. */
          *(int32_t *)0x5f91c4 = *(int32_t *)(hitbuf + 0); /* slot 0 */
          *(uint8_t *)0x5f91c0 = 1;
          *(int32_t *)0x5f91c8 = *(int32_t *)(hitbuf + 4);
          *(int32_t *)0x5f91cc = *(int32_t *)(hitbuf - 4); /* Uncertain */
          *(int32_t *)0x5f91d0 = *(int32_t *)(hitbuf - 8); /* Uncertain */
          *(int32_t *)0x5f91d4 = 0;
        }
      }
    }

    /* build follow-camera if a target was acquired */
    if (*(uint8_t *)0x5f91a8 != '\0') {
      char cam_state[0x48];
      path_input_new(cam_state, 0x3e4ccccd, 0, *(int32_t *)0x5f91bc);
      path_input_set_start(cam_state, (void *)0x5f91ac, *(int32_t *)0x5f91b8);
      if (*(float *)0x2533c0 < *(float *)0x5aca00) {
        path_input_set_search_bounds(cam_state, *(int32_t *)0x5aca00);
      }
      if (*(uint8_t *)0x5aca04 != '\0') {
        int actor2 = player_control_get_unit_index(0);
        if (actor2 != -1) {
          vector3_t vpos;
          float outer, inner;
          object_get_and_verify_type(actor2, 3);
          object_get_world_position(actor2, &vpos);
          outer = (*(float *)0x5aca0c == *(float *)0x2533c0) ?
                    20.0f :
                    *(float *)0x5aca0c;
          inner = (*(float *)0x5aca08 == *(float *)0x2533c0) ?
                    8.0f :
                    *(float *)0x5aca08;
          path_input_set_attractor(cam_state, (float *)&vpos, inner, -1, outer);
        }
      }
      path_state_new(cam_state, (void *)0x5f91dc, (void *)0x60d2c4);
      if (*(uint8_t *)0x5f91c0 != '\0' && *(uint8_t *)0x5ac9ff == '\0') {
        FUN_0005e0d0((void *)0x5f91dc, (void *)0x5f91c4, *(int32_t *)0x5f91d0,
                     *(int32_t *)0x5aca10);
      }
      FUN_0005ff70((void *)0x5f91dc);
      if (*(uint8_t *)0x5f91c0 != '\0' && *(uint8_t *)0x5ac9ff != '\0') {
        FUN_0005e0d0((void *)0x5f91dc, (void *)0x5f91c4, *(int32_t *)0x5f91d0,
                     *(int32_t *)0x5aca10);
      }
      path_state_build_path((unsigned int)0x5f91dc, (unsigned int *)0x60d268);
      *(uint8_t *)0x5f91d8 = 1;
      *(uint8_t *)0x60d2d0 = 1;
      *(int32_t *)0x60d2c8 = game_time_get();
      *(int32_t *)0x60d2c4 = -1;
    }
  }

  /* guard-position update */
  if (*(uint8_t *)0x5ac9c2 != '\0' && game_in_editor() != 0) {
    int scenario = (int)global_scenario_get();
    int *squads = (int *)(scenario + 0x42c);
    float total = 0.0f;
    float si = 0.0f;
    if (*squads > 0) {
      int s = 0;
      do {
        int squad = (int)tag_block_get_element((void *)squads, s, 0xb0);
        int *firing = (int *)(squad + 0x80);
        if (*firing > 0) {
          int f = 0;
          do {
            int fp = (int)tag_block_get_element((void *)firing, f, 0xe8);
            int32_t *hist = (int32_t *)(fp + 0x6c);
            int n = 4;
            do {
              *hist = *(hist - 1);
              hist--;
              n--;
            } while (n != 0);
            *(int32_t *)(fp + 0x5c) = *(int32_t *)(fp + 0x54);
            total = (float)((int)total + 1);
            f++;
          } while (f < *firing);
        }
        si = (float)((int)si + 1);
        s = (int)(int16_t)si;
      } while (s < *squads);
    }
    console_printf(0, "updated all %d squads' guard positions. glory!",
                   (int)total);
    *(uint8_t *)0x5ac9c2 = '\0';
  }

  /* actor-variant reset */
  if (*(uint8_t *)0x5ac9c3 != '\0' && game_in_editor() != 0) {
    int scenario = (int)global_scenario_get();
    int *squads = (int *)(scenario + 0x42c);
    float total = 0.0f;
    int *lsq = squads;
    float si = 0.0f;
    if (*squads > 0) {
      int s = 0;
      do {
        int squad = (int)tag_block_get_element((void *)squads, s, 0xb0);
        int *firing = (int *)(squad + 0x80);
        float fi = 0.0f;
        if (*firing > 0) {
          int f = 0;
          do {
            int fp = (int)tag_block_get_element((void *)firing, f, 0xe8);
            int *starts = (int *)(fp + 0xd0);
            int k = 0;
            if (*starts > 0) {
              do {
                int sl = (int)tag_block_get_element((void *)starts, k, 0x1c);
                *(uint16_t *)(sl + 0x18) = 0xffff;
                total = (float)((int)total + 1);
                k++;
              } while (k < *starts);
            }
            fi = (float)((int)fi + 1);
            f = (int)(int16_t)fi;
            squads = lsq;
          } while (f < *firing);
        }
        si = (float)((int)si + 1);
        s = (int)(int16_t)si;
      } while (s < *squads);
    }
    console_printf(
      0, "reset the actor variant in all %d starting locations. glory!",
      (int)total);
    *(uint8_t *)0x5ac9c3 = '\0';
  }

  FUN_0004a030();
  FUN_0004a9f0();
}

/* ai_debug_select_encounter: reset debug encounter state when encounter_idx
 * changes. Checks if the current encounter index (0x5ac9f4) differs from
 * encounter_idx; if so, updates the index, clears the debug-state byte at
 * 0x629d40, zeroes the 0x670-byte block at 0x629d44 and the 0x8000-byte block
 * at 0x62a3b4, then calls ai_debug_select_actor(encounter_idx, -1) to
 * reinitialize secondary state.
 *
 * No __FILE__ string.  Called from ai_debug_select_actor,
 * ai_debug_initialize_for_new_map, ai_debug_change_selected_encounter,
 * FUN_00054e40.
 *
 * Call-site verification:
 *   ai_debug_initialize_for_new_map @ 0x4c116: PUSH ESI (enc_idx, int) ->
 * encounter_idx [match] ai_debug_select_actor @ 0x4b1ca: PUSH EAX (param_1,
 * int) -> encounter_idx [match]
 *
 * Stack cleanup: ADD ESP,0x20 (0x49267) covers 8 dwords:
 *   3 args to csmemset(0x629d44,...) + 3 args to csmemset(0x62a3b4,...) +
 *   2 args to ai_debug_select_actor = 8 dwords = 0x20 bytes. */

/* ai_debug_select_actor: reinitialize secondary encounter debug state when
 * either the encounter index or param_2 changes.  Calls
 * ai_debug_select_encounter(encounter_idx) to reset the primary per-encounter
 * debug block, then updates the secondary encounter index (0x5ac9f8), clears
 * the stride-loop byte array at 0x62a3b5 (0x200 entries, stride 0x40), and
 * stores param_2 into the 0x6323d8 globals block (with 0x6323d4 as a non-(-1)
 * boolean and 0x6323dc zeroed as a word).
 *
 * No __FILE__ string.  Called from ai_debug_select_encounter (0x49220),
 * FUN_0004b7a0, ai_debug_change_selected_actor, FUN_00054e20.
 *
 * Call-site verification (only one CALL):
 *   0x4b1ca: PUSH EAX — EAX set from [EBP+0x8] at 0x4b1b3 = encounter_idx
 *   -> ai_debug_select_encounter(encounter_idx)  [match]
 *   ADD ESP,0x4 confirms cdecl 1-arg cleanup.
 *
 * Store-offset table (absolute addresses):
 *   [0x5ac9f8] <- ESI (param_2)      dword
 *   [0x629d40] <- DL=0               byte  (XOR EDX,EDX)
 *   [0x62a3b5 + n*0x40] <- DL=0      byte  loop n=0..0x1ff
 *   [0x6323d4] <- (param_2 != -1)    byte  (SETNZ AL)
 *   [0x6323d8] <- ESI (param_2)      dword
 *   [0x6323dc] <- DX=0               word  (MOV word ptr [0x6323dc],DX) */
void ai_debug_select_actor(int encounter_idx, int param_2)
{
  uint8_t *p;
  int n;

  if (*(int32_t *)0x5ac9f4 != encounter_idx ||
      *(int32_t *)0x5ac9f8 != param_2) {
    ai_debug_select_encounter(encounter_idx);
    *(int32_t *)0x5ac9f8 = param_2;
    *(uint8_t *)0x629d40 = 0;
    p = (uint8_t *)0x62a3b5;
    n = 0x200;
    do {
      *p = 0;
      p += 0x40;
      n--;
    } while (n != 0);
    *(uint8_t *)0x6323d4 = (param_2 != -1);
    *(int32_t *)0x6323d8 = param_2;
    *(uint16_t *)0x6323dc = 0;
  }
}

/* ai_debug_initialize_for_new_map: look up the encounter named DAT_005ac9d2 in
 * the scenario encounter list, reset debug encounter state, then if the
 * selected encounter or secondary index changed, reinitialize via
 * ai_debug_select_encounter.
 *
 * No __FILE__ string.  Called from ai_initialize_for_new_map (0x41090).
 *
 * Store-offset table (0x4c116..0x4c15f):
 *   0x629d40       <- 0 (byte, XOR EDX,EDX)
 *   0x62a3b5+n*0x40 (n=0..0x1ff) <- 0 (byte, loop)
 *   0x6323d4       <- 0 (byte)
 *   0x6323d8       <- 0xffffffff (dword)
 *   0x6323dc       <- 0 (word, MOV word ptr) */
void ai_debug_initialize_for_new_map(void)
{
  int enc_idx;
  uint8_t *p;
  int n;

  enc_idx = encounter_get_by_name((char *)0x5ac9d2);
  ai_debug_clear_storage();
  if (*(int32_t *)0x5ac9f4 != enc_idx || *(int32_t *)0x5ac9f8 != -1) {
    ai_debug_select_encounter(enc_idx);
    *(int32_t *)0x5ac9f8 = -1;
    *(uint8_t *)0x629d40 = 0;
    p = (uint8_t *)0x62a3b5;
    n = 0x200;
    do {
      *p = 0;
      p += 0x40;
      n--;
    } while (n != 0);
    *(uint8_t *)0x6323d4 = 0;
    *(int32_t *)0x6323d8 = -1;
    *(uint16_t *)0x6323dc = 0;
  }
}

/* --- ai_debug.obj batch drafts (2026-07-26) --- */
void ai_debug_sound_point_set(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}
void ai_debug_lineoffire_success(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}
void ai_debug_lineofsight_reset(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

void set_real_point3d(void)
{
  csmemset((void *)0x5abaa0, 0, 0xeec);
  *(char *)0x5abaa4 = 1;
}

void ai_debug_get_last_path(float *vec_a, float *vec_b)
{
  *(char *)0x5acab8 = 1;
  *(char *)0x5acab9 = 0;
  *(uint32_t *)0x5acabc = *(uint32_t *)vec_a;
  *(uint32_t *)0x5acac0 = *(uint32_t *)((char *)vec_a + 4);
  *(uint32_t *)0x5acac4 = *(uint32_t *)((char *)vec_a + 8);
  *(uint32_t *)0x5acac8 = *(uint32_t *)vec_b;
  *(uint32_t *)0x5acacc = *(uint32_t *)((char *)vec_b + 4);
  *(uint32_t *)0x5acad0 = *(uint32_t *)((char *)vec_b + 8);
  *(uint32_t *)0x5acad4 = 0;
}

void ai_debug_communication_suppress(int a0, int a1)
{
  FUN_0004a460(a0, a1, (void *)0x5aca14, 0x39, 0x42ce0);
}

void ai_debug_communication_ignore(int a0, int a1)
{
  FUN_0004a460(a0, a1, (void *)0x5aca1c, 0x39, 0x42ce0);
}

void ai_debug_communication_focus(int a0, int a1)
{
  FUN_0004a460(a0, a1, (void *)0x5aca24, 0xd1, 0x1a67e0);
}

void ai_debug_idle_look_clear(int actor_handle)
{
  *(char *)0x6323d4 = (actor_handle != -1);
  *(int32_t *)0x6323d8 = actor_handle;
  *(uint16_t *)0x6323dc = 0;
}

void ai_debug_idle_look_addprop(int index, float value)
{
  if (index < 0 || index >= 0x200) {
    display_assert("index>=0 && index<MAXIMUM_AI_DEBUG_IDLE_LOOK_PROPS",
                   "c:\\halo\\SOURCE\\ai\\ai_debug.c", 0x2a1, 1);
    system_exit(-1);
  }
  *(float *)(0x62a3b8 + index * 0x40) = value;
}

void ai_debug_change_selected_encounter(int encounter_index)
{
  ai_debug_select_encounter(encounter_index);
}

void ai_debug_change_selected_actor(int actor_index)
{
  ai_debug_select_actor(*(int32_t *)0x5ac9f4, actor_index);
}

/* 0x490c0 */
void FUN_000490C0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x49280 */
void FUN_00049280(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_00189450(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)0, 0.0f);
  /* test (int16_t)esi, (int16_t)esi -> jle 0x492ee */
  /* test (int16_t)edi, (int16_t)edi -> jle 0x492cd */
  FUN_00189450(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)esi, (void *)(uintptr_t)ebx, 0.0f);
  FUN_001893e0(0, (float *)(uintptr_t)esi, (float *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)ebx);
  /* relift: cmp (int16_t)edi, word ptr [ebp + 8] -> jl 0x492b3 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x49300 */
void FUN_00049300(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 12);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 24);
  tag_block_get_element((void *)0, 0, 0);
  tag_block_get_element((void *)(uintptr_t)edi, 0, 16);
  FUN_00189450(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)eax, (void *)(uintptr_t)ecx, 0.0f);
  /* cmp esi, eax -> jne 0x49347 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x493b0 */
void FUN_000493B0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x49430 */
void ai_debug_lineoffire_addpill(float *vec_a, float *vec_b, int param_3, char param_4)
{
  int eax = 0;

  /* test (char)eax, (char)eax -> jne 0x4945c */
  display_assert((char *)0x0025abd0, (char *)0x0025ab74, 4036, 0);
  system_exit(0);
  /* cmp eax, 0x10 -> jge 0x494ce */
  /* mem[0x005acad4] = eax */

  (void)eax;
}

/* 0x494e0 */
void FUN_000494e0(void)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: relift: mov (char)eax, byte ptr [0x5acab8] */
  /* test (char)eax, (char)eax -> je 0x4959e */
  /* relift: relift: fld dword ptr [0x5acabc] */
  /* relift: relift: mov (char)eax, byte ptr [0x5acab9] */
  /* relift: relift: fld dword ptr [0x5acac0] */
  /* relift: relift: fld dword ptr [0x5acac4] */
  FUN_00189270(0, (void *)0x005acabc, (float *)(uintptr_t)eax, (void *)(uintptr_t)eax);
  /* test eax, eax -> jle 0x4959d */
  FUN_00189860(0, (void *)(uintptr_t)edi, (void *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)eax);
  /* cmp esi, eax -> jl 0x49560 */
  (void)eax;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x495b0 */
void FUN_000495b0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* test (char)eax, (char)eax -> je 0x496b6 */
  FUN_00189150(0, (void *)0x005f8cb8, 0.0f, (void *)(uintptr_t)eax);
  FUN_00189320(0, (void *)0x005f8cb8, (void *)0x005f8cc4, 0.0f, (void *)(uintptr_t)ecx);
  /* test eax, eax -> jle 0x4964b */
  FUN_00189860(0, (void *)(uintptr_t)eax, (void *)(uintptr_t)edx, 0.0f, (void *)0);
  /* cmp eax, ecx -> jl 0x49610 */
  /* test edx, edx -> jle 0x496b5 */
  /* test dl, dl -> je 0x49672 */
  FUN_00189270(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (void *)0);
  /* cmp eax, edx -> jl 0x49660 */

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x496c0 */
char ai_debug_highlight_cluster(int16_t cluster_index, void *out)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test (char)ecx, (char)ecx -> je 0x497ae */
  /* relift: cmp dword ptr [0x5ac9f4], -1 -> je 0x497ae */
  game_time_get();
  /* relift: cmp dword ptr [0x2c8e8c], edx -> je 0x49728 */
  FUN_00058fd0(0, 0, 512, 0, (char *)0x00331f18);
  game_time_get();
  /* mem[0x002c8e90] = eax */
  /* mem[0x002c8e8c] = edx */
  /* test esi, esi -> jne 0x49756 */
  display_assert((char *)0x0025abec, (char *)0x0025ab74, 4133, 0);
  system_exit(0);
  datum_get((void *)(uintptr_t)eax, 0);
  /* test (char)ecx, (char)ecx -> je 0x49797 */
  /* mem[0x005accac] = eax */
  /* mem[0x005eccb0] = eax */
  return 0;

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x497c0 */
void FUN_000497c0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  /* test ecx, ecx -> jle 0x4981d */
  /* relift: cmp word ptr [esi*2 + 0x5e4cb0], (int16_t)ebx -> jne 0x4980f */
  /* cmp esi, ecx -> jl 0x497d2 */
  /* cmp esi, ecx -> jl 0x4985a */
  /* cmp ecx, 0x4000 -> jge 0x49894 */
  /* mem[0x005accac] = ecx */
  /* cmp esi, -1 -> je 0x4988f */
  /* cmp esi, 0x7fff -> jle 0x49887 */
  display_assert((char *)0x0025ac50, (char *)0x0025ab74, 4223, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x4988f */
  error(0, (char *)0x0025ac00);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}

/* 0x498d0 */
void FUN_000498d0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp (int16_t)esi, -1 -> je 0x49987 */
  /* cmp (int16_t)edi, -1 -> je 0x49987 */
  /* test ecx, ecx -> jle 0x49919 */
  /* relift: cmp word ptr [edx - 2], (int16_t)esi -> jne 0x4990b */
  /* relift: cmp word ptr [edx], (int16_t)edi -> je 0x49915 */
  /* cmp eax, ecx -> jl 0x49900 */
  /* cmp eax, ecx -> jl 0x49946 */
  /* cmp ecx, 0x2000 -> jge 0x49958 */
  /* mem[0x005eccb0] = ecx */
  /* cmp eax, -1 -> je 0x49987 */
  /* test (char)eax, (char)eax -> jne 0x49985 */
  error(0, (char *)0x0025ac68);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x49990 */
void FUN_00049990(void)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  crt_sprintf((char *)0x005ab100, (char *)0x0025acb8);
  /* cmp eax, 0xc -> jle 0x49a3d */
  FUN_00189cb0(0, (void *)(uintptr_t)edi, (void *)0x005ab100, 0);
  /* cmp esi, eax -> jl 0x49a10 */
  /* test eax, eax -> jle 0x49aba */
  /* cmp eax, 0xc -> jle 0x49a7e */
  FUN_00189270(0, (float *)(uintptr_t)edx, (float *)0, (void *)0);
  /* cmp edi, eax -> jl 0x49a71 */

  (void)eax;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x49ac0 */
char *ai_debug_describe_actor(int actor_handle, int object_handle, char with_actor, char *buf, int buf_size)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  csstrcpy((char *)(uintptr_t)eax, (char *)0x0025386f);
  /* test (char)eax, (char)eax -> je 0x49bbe */
  /* cmp eax, -1 -> je 0x49bbe */
  datum_get((void *)(uintptr_t)ecx, 0);
  csstrcpy((char *)(uintptr_t)eax, (char *)0x0025ace0);
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 232);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 172);
  /* test eax, eax -> jne 0x49ba6 */
  crt_sprintf((char *)(uintptr_t)edx, (char *)0x0025acd8);
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x0025accc);
  csstrcpy((char *)(uintptr_t)ecx, (char *)(uintptr_t)edi);
  /* cmp eax, -1 -> je 0x49c35 */
  object_get_and_verify_type(0, 0);
  tag_get('tinu', 0);
  tag_name_strip_path((char *)(uintptr_t)eax);
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  crt_sprintf((char *)(uintptr_t)edx, (char *)0x0025acc4);
  snprintf((char *)(uintptr_t)esi, edx, (char *)0x0025acbc);
  return NULL;

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x49c70 */
void FUN_00049c70(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int ebp = 0;

  observer_get_camera(0);
  /* test esi, esi -> je 0x49d58 */
  director_get_perspective(0);
  /* test (int16_t)eax, (int16_t)eax -> jne 0x49cbb */
  local_player_get_player_index(0);
  datum_get((void *)(uintptr_t)eax, 0);
  FUN_0014df70(0, (float *)0, (float *)0, 0, (void *)0);
  /* relift: cmp word ptr [ebp - 0x5c], 3 -> jne 0x49d58 */
  /* cmp eax, -1 -> je 0x49d58 */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0x49d58 */
  /* cmp ebx, -1 -> jne 0x49d58 */
  /* cmp eax, ebx -> je 0x49d58 */
  object_get_and_verify_type(0, 0);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)ebp;
}

/* 0x49d60 */
void FUN_00049d60(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp eax, ecx -> je 0x49d8a */
  /* mem[0x006323b4] = eax */
  /* cmp eax, -1 -> je 0x49f50 */
  datum_get((void *)(uintptr_t)eax, 0);
  observer_get_camera(0);
  /* test eax, eax -> je 0x49e8c */
  normalize3d((float *)0);
  /* test (char)eax, 0x41 -> jne 0x49e8b */
  FUN_00027f40(0, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  /* mem[0x006323c8] = ecx */
  /* mem[0x006323cc] = eax */
  /* mem[0x006323d0] = edx */
  /* relift: cmp byte ptr [ebp - 2], 0 -> je 0x49e56 */
  /* mem[0x006323bc] = ecx */
  /* mem[0x006323c0] = eax */
  /* mem[0x006323c4] = edx */
  FUN_00189320(0, (float *)(uintptr_t)edi, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  FUN_00189320(0, (float *)(uintptr_t)edi, (float *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x49eee */
  FUN_00189320(0, (float *)0, (float *)0, 0.0f, (void *)0);
  /* test (char)eax, (char)eax -> je 0x49f4f */
  FUN_00189320(0, (float *)0, (float *)0, 0.0f, (void *)0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)ebp;
}

/* 0x49f60 */
void ai_debug_vocalize(int a0, int a1)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* cmp eax, esi -> je 0x4a020 */
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp eax, esi -> je 0x4a01e */
  FUN_001a6cd0((char *)(uintptr_t)ecx);
  FUN_001a67e0((char *)(uintptr_t)edx);
  /* cmp (int16_t)eax, (int16_t)esi -> je 0x4a01e */
  FUN_001a68d0(0, 0, 0, 0, (void *)0, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  /* test (int16_t)esi, (int16_t)esi -> je 0x4a01e */
  csmemset((void *)(uintptr_t)eax, 0, 48);
  ai_communication_packet_new((void *)(uintptr_t)eax);
  FUN_001a6ef0(0, 0, (void *)(uintptr_t)ecx);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x4a030 */
void FUN_0004a030(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* test (char)eax, (char)eax -> je 0x4a215 */
  /* cmp eax, -1 -> je 0x4a215 */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0x4a20e */
  /* relift: test byte ptr [eax + 0xb6], 4 -> jne 0x4a20e */
  /* relift: cmp word ptr [eax + 0x338], 0 -> jne 0x4a215 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x4a095 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x4a215 */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x4a1ff */
  /* cmp (int16_t)eax, 0xd1 -> jge 0x4a1f4 */
  FUN_001a68d0(0, 0, 0, 0, (void *)0, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  /* cmp (int16_t)esi, 2 -> jl 0x4a163 */
  csmemset((void *)(uintptr_t)eax, 0, 48);
  ai_communication_packet_new((void *)(uintptr_t)eax);
  FUN_001a6ef0(0, 0, (void *)(uintptr_t)ecx);
  /* cmp eax, -1 -> je 0x4a163 */
  tag_get_name(0);
  crt_strstr((char *)(uintptr_t)esi, (char *)0x0025ad10);
  /* test eax, eax -> je 0x4a168 */
  crt_strchr((char *)(uintptr_t)eax, 92);
  /* test eax, eax -> je 0x4a168 */
  FUN_001a67b0(0, 0);
  console_printf(0, (char *)0x00259f2c);
  FUN_001a67b0(0, 0);
  csstrcmp((char *)(uintptr_t)eax, (char *)0);
  /* test eax, eax -> jne 0x4a1ee */
  /* test (char)eax, (char)eax -> je 0x4a1e3 */
  /* cmp (int16_t)eax, 0xd1 -> jl 0x4a1a7 */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x4a1ff */
  /* cmp (int16_t)eax, 0xd1 -> jl 0x4a215 */
  console_printf(0, (char *)0x0025acf4);

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x4a220 */
void ai_debug_speak(int a0)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* cmp eax, -1 -> je 0x4a283 */
  datum_get((void *)(uintptr_t)eax, 0);
  FUN_001a67e0((char *)(uintptr_t)ecx);
  /* cmp ecx, -1 -> je 0x4a282 */
  /* cmp (int16_t)eax, 0xffff -> je 0x4a282 */
  /* mem[0x006324e4] = edx */

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x4a290 */
void ai_debug_speak_list(int a0)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp eax, -1 -> je 0x4a457 */
  datum_get((void *)(uintptr_t)eax, 0);
  crt_stricmp((char *)(uintptr_t)eax, (char *)(uintptr_t)ecx);
  /* test eax, eax -> je 0x4a3cd */
  /* cmp eax, ebx -> jne 0x4a3b0 */
  /* relift: cmp dword ptr [esi], ebx -> jne 0x4a410 */
  console_printf(0, (char *)0x0025ad28);
  console_printf(0, (char *)0x0025ad1c);
  /* cmp eax, ebx -> jne 0x4a3f0 */
  /* relift: cmp dword ptr [edi + 0x18], -1 -> je 0x4a454 */
  /* cmp (int16_t)eax, 0xffff -> je 0x4a454 */
  /* mem[0x006324e4] = edx */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x4a770 */
void FUN_0004a770(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  /* test (char)eax, (char)eax -> je 0x4a8b3 */
  datum_absolute_index_to_index((void *)(uintptr_t)ecx, 0);
  /* test edi, edi -> je 0x4a8b1 */
  /* relift: cmp word ptr [0x6323dc], (int16_t)ebx -> jle 0x4a8b1 */
  datum_absolute_index_to_index((void *)(uintptr_t)eax, 0);
  /* test eax, eax -> je 0x4a8a2 */
  /* relift: cmp word ptr [edi + 0x56c], 1 -> jne 0x4a86f */
  csprintf((char *)0x005ab100, (char *)0x0025aec8);
  FUN_00189cb0(0, (void *)(uintptr_t)edx, (void *)(uintptr_t)eax, 0);
  /* relift: cmp (int16_t)ebx, word ptr [0x6323dc] -> jl 0x4a7b4 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x4a8c0 */
void FUN_0004a8c0(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;

  game_time_get();
  /* cmp (int16_t)eax, 0xffff -> je 0x4a9c6 */
  /* cmp (int16_t)eax, 3 -> jge 0x4a949 */
  FUN_00189540(0, (void *)(uintptr_t)esi, 0.0f, (void *)(uintptr_t)ebx);
  csprintf((char *)0, (char *)0);
  FUN_00189cb0(0, (void *)(uintptr_t)edx, (void *)(uintptr_t)eax, 0);

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
}

/* 0x4a9f0 */
void FUN_0004a9f0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test (char)eax, (char)eax -> je 0x4aae1 */
  /* test (char)eax, (char)eax -> je 0x4aae1 */
  /* cmp (int16_t)ebx, 0x20 -> jge 0x4aae1 */
  /* test (char)eax, (char)eax -> je 0x4aad0 */
  /* test (char)eax, (char)eax -> je 0x4aad0 */
  /* relift: cmp ecx, dword ptr [edi] -> jne 0x4aad0 */
  /* relift: cmp (char)eax, byte ptr [esi + 0x60] -> jne 0x4aad0 */
  /* test (char)eax, (char)eax -> je 0x4aac4 */
  distance_squared3d((float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  /* relift: cmp ecx, dword ptr [esi + 4] -> jl 0x4aadd */
  /* cmp (int16_t)ebx, 0x20 -> jl 0x4aa40 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x4b0f0 */
void ai_debug_teleport_to(int actor_index)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp eax, -1 -> je 0x4b1a7 */
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test eax, eax -> jle 0x4b1a4 */
  data_iterator_new((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  data_iterator_next((void *)(uintptr_t)edx);
  /* test esi, esi -> je 0x4b1a4 */
  /* relift: cmp dword ptr [esi + 0x34], -1 -> je 0x4b192 */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 52);
  object_set_position(0, (float *)0, (float *)0, (float *)0);
  data_iterator_next((void *)(uintptr_t)eax);
  /* test esi, esi -> jne 0x4b152 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x4b220 */
void FUN_0004b220(void)
{
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  observer_get_camera(0);
  /* mem[0x005ac9a0] = ecx */
  /* mem[0x005ac9a4] = edx */
  /* mem[0x005ac9a8] = esi */
  /* mem[0x005ac9b8] = esi */
  /* mem[0x005ac9b0] = ecx */
  /* mem[0x005ac9b4] = edx */
  /* mem[0x005ac990] = 0x3d4ccccd */

  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x4b2b0 */
void FUN_0004b2b0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x4b320 */
void FUN_0004b320(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  observer_get_camera(0);
  /* test eax, eax -> je 0x4b42d */
  FUN_00189450(0, (float *)(uintptr_t)esi, (float *)(uintptr_t)edi, (void *)(uintptr_t)eax, 0.0f);
  FUN_001893e0(0, (float *)(uintptr_t)esi, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  /* test eax, eax -> jne 0x4b42a */
  FUN_001893e0(0, (float *)(uintptr_t)edi, (float *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)edx);
  /* test eax, eax -> je 0x4b450 */
  /* test dl, dl -> je 0x4b450 */
  FUN_00049300();
  /* test eax, eax -> je 0x4b4ad */
  csprintf((char *)0x005ab100, (char *)0x0025afc4);
  FUN_00189cb0(0, (void *)(uintptr_t)edx, (void *)(uintptr_t)eax, 0);
  /* test eax, eax -> je 0x4b590 */
  FUN_00189150(0, (float *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)ecx);
  csprintf((char *)0x005ab100, (char *)0x0025afc4);
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)(uintptr_t)eax, 0);
  /* test ebx, ebx -> je 0x4b667 */
  /* test (char)eax, (char)eax -> je 0x4b667 */
  path_attractor_weight();
  /* test eax, eax -> je 0x4b61f */
  csprintf((char *)0x005ab100, (char *)0x0025afc4);
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)(uintptr_t)eax, 0);
  /* test eax, eax -> je 0x4b667 */
  /* test (char)eax, 0x41 -> jne 0x4b667 */
  csprintf((char *)0x005ab100, (char *)0x0025afc4);
  FUN_00189cb0(0, (void *)(uintptr_t)edx, (void *)(uintptr_t)eax, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x4b670 */
void FUN_0004b670(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  object_try_and_get_and_verify_type(0, 0);
  /* test esi, esi -> je 0x4b761 */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0x4b6c9 */
  /* relift: cmp dword ptr [eax + 0x2d4], edi -> jne 0x4b6c9 */
  FUN_0001aae0(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  biped_get_camera_height_and_offset(0, (void *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> je 0x4b722 */
  /* test (char)eax, 0x41 -> jne 0x4b722 */
  FUN_00189860(0, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)ebx);
  FUN_00189540(0, (void *)(uintptr_t)edx, 0.0f, (void *)0);
  /* test (char)eax, (char)eax -> je 0x4b761 */
  FUN_00189150(0, (float *)(uintptr_t)eax, 0.0f, (void *)0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x4b770 */
void ai_debug_lineofsight(void)
{
  FUN_000497c0();
  FUN_000497c0();
  FUN_000498d0();
}

/* 0x4b7a0 */
void FUN_0004b7a0(void)
{
  int eax = 0;
  int esi = 0;

  FUN_00049c70();
  /* cmp esi, -1 -> je 0x4b7f8 */
  datum_get((void *)(uintptr_t)eax, 0);
  ai_debug_describe_actor(0, 0, 0, (char *)0x005ab100, 256);
  console_printf(0, (char *)0x0025afd0);
  ai_debug_select_actor(0, 0);
  ai_debug_select_actor(0, 0);

  (void)eax;
  (void)esi;
}

/* 0x4b810 */
void FUN_0004b810(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  object_iterator_new((void *)(uintptr_t)eax, 0, 0);
  object_iterator_next((void *)(uintptr_t)ecx);
  /* test esi, esi -> je 0x4bc4c */
  unit_get_head_position(0, (float *)(uintptr_t)edx);
  FUN_0004b220();
  /* test (char)eax, (char)eax -> je 0x4b9b5 */
  tag_get('tinu', 0);
  /* test eax, eax -> jle 0x4b9b5 */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 24);
  /* cmp edx, ecx -> je 0x4b8f5 */
  /* cmp eax, ecx -> jl 0x4b8d0 */
  /* cmp eax, -1 -> je 0x4b919 */
  tag_get_name(0);
  tag_name_strip_path((char *)(uintptr_t)eax);
  /* mem[0x005ac9a8] = eax */
  /* mem[0x005ac9a4] = edx */
  /* mem[0x005ac9a0] = ecx */
  csprintf((char *)0x005ab100, (char *)0x0025affc);
  FUN_00189cb0(0, (void *)0x005ac9a0, (void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x4bbbe */
  /* relift: cmp word ptr [esi + 0x338], 0 -> jle 0x4bac8 */
  /* cmp eax, -1 -> jne 0x4b9e2 */
  tag_get_name(0);
  tag_name_strip_path((char *)(uintptr_t)eax);
  /* cmp (int16_t)eax, 0xffff -> jne 0x4ba07 */
  FUN_001a67b0(0, 0);
  /* mem[0x005ac9a0] = edx */
  /* mem[0x005ac9a4] = ecx */
  /* mem[0x005ac9a8] = edx */
  FUN_001a6ca0(0);
  csprintf((char *)0x005ab100, (char *)0x0025afe8);
  FUN_00189cb0(0, (void *)0x005ac9a0, (void *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [esi + 0x368], 0 -> jle 0x4bbbe */
  /* cmp eax, -1 -> jne 0x4bae8 */
  tag_get_name(0);
  tag_name_strip_path((char *)(uintptr_t)eax);
  /* cmp (int16_t)eax, 0xffff -> jne 0x4bb0d */
  FUN_001a67b0(0, 0);
  /* mem[0x005ac9a0] = ecx */
  /* mem[0x005ac9a8] = ecx */
  /* mem[0x005ac9a4] = edx */
  FUN_001a6ca0(0);
  csprintf((char *)0x005ab100, (char *)0x0025afdc);
  FUN_00189cb0(0, (void *)0x005ac9a0, (void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x4bc34 */
  /* test (char)eax, (char)eax -> jne 0x4bc34 */
  /* test (int16_t)esi, (int16_t)esi -> jle 0x4bc34 */
  /* cmp eax, 8 -> ja 0x4bc03 */
  FUN_001a6d10(0, 0, 512, (char *)(uintptr_t)edx);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  object_iterator_next((void *)(uintptr_t)ecx);
  /* test esi, esi -> jne 0x4b840 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x4bc70 */
void FUN_0004bc70(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp word ptr [edi + 0x3b6], (int16_t)esi -> jle 0x4c0de */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0x4c0c9 */
  object_get_world_position(0, (void *)(uintptr_t)edx);
  FUN_0004b220();
  csprintf((char *)0x005ab100, (char *)0x0025b098);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* relift: cmp word ptr [edi + 8], 0 -> je 0x4be76 */
  crt_sprintf((char *)0x005ab100, (char *)0x0025b090);
  /* test ecx, eax -> je 0x4bde3 */
  FUN_0008dc30((char *)0x005ab100, (char *)0x0025b06c);
  FUN_0008dc30((char *)0x005ab100, (char *)(uintptr_t)eax);
  /* mem[0x005ac9a8] = eax */
  /* mem[0x005ac9a0] = ecx */
  /* mem[0x005ac9a4] = edx */
  FUN_00189cb0(0, (void *)0, (void *)0, 0);
  /* relift: cmp word ptr [edi + 0xa], 0 -> je 0x4bfd2 */
  crt_sprintf((char *)0x005ab100, (char *)0x0025b05c);
  /* test ecx, edx -> je 0x4bf43 */
  FUN_0008dc30((char *)0x005ab100, (char *)0x0025b06c);
  FUN_0008dc30((char *)0x005ab100, (char *)(uintptr_t)edx);
  /* mem[0x005ac9a0] = eax */
  /* mem[0x005ac9a4] = ecx */
  /* mem[0x005ac9a8] = edx */
  FUN_00189cb0(0, (void *)0, (void *)0, 0);
  /* relift: cmp word ptr [edi + 0xc], 0 -> jle 0x4c0c9 */
  crt_sprintf((char *)0x005ab100, (char *)0x0025b018);
  /* relift: cmp word ptr [edi + 0xc], (int16_t)esi -> jle 0x4c049 */
  global_scenario_get();
  FUN_00054220(eax, (void *)(uintptr_t)eax, (char *)0, 0);
  FUN_0008dc30((char *)0x005ab100, (char *)0x0025b06c);
  FUN_0008dc30((char *)0x005ab100, (char *)(uintptr_t)ecx);
  /* relift: cmp (int16_t)esi, word ptr [edi + 0xc] -> jl 0x4c000 */
  /* mem[0x005ac9a4] = eax */
  /* mem[0x005ac9a0] = edx */
  /* mem[0x005ac9a8] = ecx */
  FUN_00189cb0(0, (void *)0, (void *)0, 0);
  /* relift: cmp (int16_t)esi, word ptr [edi + 0x3b6] -> jl 0x4bc91 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x4c2a0 */
void FUN_0004c2a0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  path_node_from_hash_table((char *)(uintptr_t)esi, edx);
  /* cmp (int16_t)eax, 0xffff -> je 0x4c375 */
  path_get_node((char *)(uintptr_t)esi, 0);
  FUN_0004b320();
  /* test (char)eax, (char)eax -> je 0x4c559 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  path_get_node((char *)(uintptr_t)esi, 0);
  /* relift: cmp (int16_t)edx, word ptr [0x331f60] -> je 0x4c527 */
  /* test (char)eax, (char)eax -> je 0x4c4bd */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 12);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 24);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 16);
  /* relift: cmp eax, dword ptr [ecx + 4] -> jne 0x4c434 */
  FUN_0004b320();
  /* cmp (int16_t)ebx, -1 -> jne 0x4c3c1 */
  /* test edi, edi -> je 0x4c549 */
  FUN_00189450(0, (float *)(uintptr_t)edi, (float *)0, (void *)0, 0.0f);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x4c560 */
void FUN_0004c560(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test esi, esi -> je 0x4c884 */
  /* test (char)eax, (char)eax -> je 0x4c884 */
  /* relift: cmp eax, dword ptr [0x5acab4] -> je 0x4c884 */
  global_structure_bsp_index_get();
  /* cmp (int16_t)eax, 6 -> jl 0x4c612 */
  display_assert((char *)0x0025b170, (char *)0x0025ab74, 3944, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x4c621 */
  /* cmp (int16_t)eax, 6 -> jl 0x4c641 */
  display_assert((char *)0x0025b110, (char *)0x0025ab74, 3945, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x10], (int16_t)eax -> jne 0x4c657 */
  game_time_get();
  csprintf((char *)0x005ab100, (char *)0x0025b100);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4c751 */
  /* test (char)eax, (char)eax -> je 0x4c735 */
  FUN_00189450(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edi, (void *)(uintptr_t)edx, 0.0f);
  FUN_00189150(0, (float *)(uintptr_t)edi, 0.0f, (void *)(uintptr_t)ecx);
  /* test (char)eax, 0x41 -> jne 0x4c70e */
  FUN_00189540(0, (void *)(uintptr_t)edi, 0.0f, (void *)(uintptr_t)edx);
  /* test (char)ebx, (char)ebx -> je 0x4c751 */
  FUN_00049300();
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4c77c */
  FUN_00049280();
  /* test (char)eax, (char)eax -> je 0x4c7a7 */
  FUN_00049280();
  /* test (char)eax, (char)eax -> je 0x4c7d2 */
  FUN_00049280();
  /* relift: cmp (int16_t)eax, word ptr [esi + 0x1458a] -> jge 0x4c84a */
  /* test (char)ecx, (char)ecx -> je 0x4c820 */
  path_obstacles_debug_render((void *)(uintptr_t)eax, 0.0f);
  /* test (char)ecx, (char)ecx -> je 0x4c84a */
  /* test (char)ecx, (char)ecx -> je 0x4c84a */
  FUN_000609e0((void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x4c87c */
  FUN_0004c2a0();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x4c890 */
void FUN_0004c890(void)
{
  int eax = 0;

  /* test (char)eax, (char)eax -> je 0x4c8fb */
  /* test (char)eax, (char)eax -> je 0x4c8fb */
  /* test (char)eax, (char)eax -> jne 0x4c8fb */
  /* test (char)eax, (char)eax -> jne 0x4c8c4 */
  /* test (char)eax, (char)eax -> jne 0x4c8c4 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x4c8d6 */
  FUN_00189270(0, (void *)0x005f91ac, (void *)0x005f91c4, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x4c91a */
  FUN_0004b220();
  FUN_0004c560();

  (void)eax;
}

/* 0x4c920 */
void FUN_0004c920(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  datum_get((void *)(uintptr_t)eax, 0);
  tag_get('rtca', 0);
  tag_get('vtca', 0);
  FUN_000490C0();
  object_get_and_verify_type(0, 0);
  tag_get('tinu', 0);
  /* test edi, edi -> je 0x4ca0a */
  /* relift: cmp word ptr [esi + 0x6e], 2 -> jl 0x4ca0a */
  /* cmp eax, -1 -> je 0x4ca0a */
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp ecx, -1 -> je 0x4ca05 */
  /* relift: cmp dword ptr [eax + 0x7c], ecx -> jge 0x4ca0a */
  FUN_0004b220();
  /* test (char)eax, (char)eax -> je 0x4cac4 */
  /* cmp eax, -1 -> je 0x4cade */
  datum_get((void *)(uintptr_t)edx, 0);
  actor_action_debug_color(0);
  FUN_0004b670();
  actor_action_debug_color(0);
  FUN_0004b670();
  /* test (char)eax, (char)eax -> je 0x4cbd0 */
  /* relift: test dword ptr [edx], 0xc0000000 -> je 0x4cbd0 */
  /* test (char)eax, (char)eax -> jne 0x4cb18 */
  /* test (char)ecx, (char)ecx -> jne 0x4cb22 */
  /* test (char)ecx, (char)ecx -> je 0x4cb79 */
  /* test (char)ecx, (char)ecx -> je 0x4cb29 */
  /* test dl, dl -> je 0x4cb3f */
  csprintf((char *)0x005ab100, (char *)0x0025bf84);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> jne 0x4cb91 */
  /* relift: cmp word ptr [esi + 0x360], 0 -> jle 0x4cbd0 */
  /* test (char)eax, (char)eax -> je 0x4cb98 */
  csprintf((char *)0x005ab100, (char *)0x0025bf60);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4cccb */
  FUN_00064540((void *)(uintptr_t)ecx, 0);
  FUN_00064570((void *)(uintptr_t)edx);
  /* test edi, edi -> je 0x4cccb */
  /* cmp (int16_t)eax, 2 -> jl 0x4cc60 */
  /* cmp (int16_t)eax, 3 -> jg 0x4cc60 */
  /* test (char)eax, (char)eax -> jne 0x4cc60 */
  /* test (char)eax, (char)eax -> je 0x4cc60 */
  unit_scripting_unit_driver(0, (void *)(uintptr_t)eax);
  actor_perception_aiming_vector_test_blockage();
  /* cmp (int16_t)ebx, (int16_t)eax -> jg 0x4cc60 */
  FUN_00064570((void *)(uintptr_t)ecx);
  /* test edi, edi -> jne 0x4cc05 */
  /* test (char)eax, (char)eax -> je 0x4cccb */
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4d665 */
  /* relift: cmp dword ptr [eax + 0x19c], -1 -> je 0x4d665 */
  game_time_get();
  /* cmp edx, eax -> jle 0x4d665 */
  /* test (char)eax, (char)eax -> je 0x4ce7b */
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  FUN_00189150(0, (float *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)ebx);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)ebx);
  /* test (char)eax, (char)eax -> je 0x4ce59 */
  csprintf((char *)0x005ab100, (char *)0x0025bf04);
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)(uintptr_t)eax, 0);
  FUN_00189320(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (void *)0);
  /* test (char)eax, (char)eax -> je 0x4d0f1 */
  /* test (int16_t)ecx, (int16_t)ecx -> jle 0x4d015 */
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  FUN_00189150(0, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)ebx);
  FUN_00189270(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (void *)(uintptr_t)ebx);
  /* test (char)eax, (char)eax -> je 0x4d0f1 */
  csprintf((char *)0x005ab100, (char *)0x0025bf04);
  FUN_00189320(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)ebx, 0.0f, (void *)0);
  /* test (char)eax, (char)eax -> je 0x4d0f1 */
  csprintf((char *)0, (char *)0);
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [ebp - 0x30], 1 -> jne 0x4d1aa */
  csprintf((char *)0x005ab100, (char *)0x0025bef4);
  FUN_00189cb0(0, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x4d206 */
  FUN_00189320(0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)ecx);
  FUN_00189320(0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  actor_move_get_avoidance_vector(0, 0.0f, (float *)0);
  csprintf((char *)0x005ab100, (char *)0x0025bee4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  FUN_00189320(0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)ecx);
  actor_move_get_avoidance_vector(0, 0.0f, (float *)(uintptr_t)eax);
  csprintf((char *)0x005ab100, (char *)0x0025bed0);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  FUN_00189320(0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  csprintf((char *)0x005ab100, (char *)0x0025beb4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4d40a */
  actor_move_transform_avoidance_vector(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  FUN_00189320(0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)edx);
  csprintf((char *)0x005ab100, (char *)0x0025be8c);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4d473 */
  /* relift: cmp word ptr [edi + 0x1dc], (int16_t)ebx -> jle 0x4d473 */
  FUN_00189860(0, (void *)0, (void *)0, 0.0f, (void *)0);
  /* relift: cmp (int16_t)ebx, word ptr [edi + 0x1dc] -> jl 0x4d420 */
  /* cmp eax, 7 -> ja 0x4d574 */
  crt_sprintf((char *)0x005ab100, (char *)0x0025be6c);
  crt_sprintf((char *)0x005ab100, (char *)0x0025be54);
  crt_sprintf((char *)0x005ab100, (char *)0x0025be34);
  crt_sprintf((char *)0x005ab100, (char *)0x0025be24);
  crt_sprintf((char *)0x005ab100, (char *)0x0025be14);
  crt_sprintf((char *)0x005ab100, (char *)0x0025be00);
  crt_sprintf((char *)0x005ab100, (char *)0x0025bdf0);
  crt_sprintf((char *)0x005ab100, (char *)0x00253b58);
  /* mem[0x005ac9a4] = eax */
  /* mem[0x005ac9a0] = edx */
  /* mem[0x005ac9a8] = ecx */
  FUN_00189cb0(0, (void *)0, (void *)0, 0);
  /* test (char)ebx, (char)ebx -> je 0x4d665 */
  FUN_00189320(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  csprintf((char *)0x005ab100, (char *)0x0025bddc);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4dcc9 */
  /* cmp eax, -1 -> je 0x4d71d */
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  datum_get((void *)(uintptr_t)edx, 0);
  /* cmp (int16_t)eax, 0xffff -> jne 0x4d6d4 */
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x0025bdd0);
  crt_sprintf((char *)0, (char *)0);
  /* test (char)ecx, (char)ecx -> je 0x4d709 */
  /* test (char)ebx, (char)ebx -> je 0x4d715 */
  crt_sprintf((char *)(uintptr_t)ecx, (char *)0x0025bdb4);
  /* mem[0x005ac9a4] = eax */
  /* mem[0x005ac9a0] = edx */
  /* mem[0x005ac9a8] = ecx */
  FUN_00189cb0(0, (void *)0, (void *)0, 0);
  actor_activation_debug_color(0);
  observer_get_camera(eax);
  players_get_combined_pvs();
  /* test (char)eax, (char)eax -> je 0x4d800 */
  /* cmp eax, -1 -> je 0x4d800 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* cmp ebx, -1 -> je 0x4dca2 */
  unit_get_head_position(0, (float *)(uintptr_t)edx);
  object_get_root_parent(0);
  object_get_and_verify_type(0, 0);
  /* cmp (int16_t)eax, 0xffff -> jne 0x4da42 */
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  FUN_00189270(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (void *)(uintptr_t)edi);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edi);
  FUN_00189270(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (void *)(uintptr_t)edi);
  /* relift: test dword ptr [ecx + eax*4], edx -> je 0x4dba1 */
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  FUN_00189270(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (void *)(uintptr_t)edi);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edi);
  FUN_00189270(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (void *)(uintptr_t)edi);
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edi);
  /* test eax, eax -> je 0x4dcc9 */
  /* relift: cmp (int16_t)edx, word ptr [eax + 2] -> jge 0x4dcc9 */
  /* test (char)eax, (char)eax -> je 0x4ddf5 */
  /* cmp eax, -1 -> je 0x4dd0b */
  datum_get((void *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [ebx + 2], 0 -> jle 0x4ddf5 */
  /* cmp edi, -1 -> je 0x4ddf5 */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0x4dd40 */
  /* cmp eax, -1 -> je 0x4dd40 */
  object_get_world_position(0, (void *)(uintptr_t)edx);
  FUN_00189540(0, (void *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0x4ddd1 */
  /* relift: cmp dword ptr [esi + 0x164], -1 -> jne 0x4dd98 */
  FUN_00189540(0, (void *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)edx);
  FUN_00189540(0, (void *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)ecx);
  scenario_get();
  FUN_00049300();
  /* relift: cmp (int16_t)edx, word ptr [ebx + 2] -> jge 0x4ddf5 */
  /* cmp edi, -1 -> jne 0x4dd17 */
  /* test (char)eax, (char)eax -> je 0x4de94 */
  /* test (char)eax, 0x41 -> jne 0x4de4b */
  csprintf((char *)0x005ab100, (char *)0x0025bda8);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, 0x41 -> jne 0x4de94 */
  csprintf((char *)0x005ab100, (char *)0x0025bd9c);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4df32 */
  /* test (char)eax, 0x41 -> jne 0x4dee9 */
  csprintf((char *)0x005ab100, (char *)0x0025bd90);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, 0x41 -> jne 0x4df32 */
  csprintf((char *)0x005ab100, (char *)0x0025bd84);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4dfee */
  /* test (char)eax, (char)eax -> je 0x4dfee */
  csprintf((char *)0x005ab100, (char *)0x0025bd28);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e237 */
  /* test (char)eax, (char)eax -> je 0x4e237 */
  csprintf((char *)0x005ab100, (char *)0x0025bd1c);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e077 */
  csprintf((char *)0x005ab100, (char *)0x0025bd10);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e0b7 */
  csprintf((char *)0x005ab100, (char *)0x0025bd00);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e0f7 */
  csprintf((char *)0x005ab100, (char *)0x0025bcf0);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e137 */
  csprintf((char *)0x005ab100, (char *)0x0025bce4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e177 */
  csprintf((char *)0x005ab100, (char *)0x0025bcd4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e1b7 */
  csprintf((char *)0x005ab100, (char *)0x0025bcc4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e1f7 */
  csprintf((char *)0x005ab100, (char *)0x0025bcb4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e237 */
  csprintf((char *)0x005ab100, (char *)0x0025bca4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e432 */
  /* mem[0x005ac9a8] = eax */
  /* mem[0x005ac9a0] = ecx */
  /* mem[0x005ac9a4] = edx */
  csprintf((char *)0x005ab100, (char *)0x0025bc90);
  FUN_00189cb0(0, (void *)0x005ac9a0, (void *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [esi + 0x3a8], 0 -> jle 0x4e38c */
  datum_get((void *)(uintptr_t)eax, 0);
  csprintf((char *)0, (char *)0);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)edi, (void *)0);
  /* relift: test dword ptr [edx], 0x20000000 -> je 0x4e435 */
  /* test (char)eax, (char)eax -> je 0x4e3f1 */
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  FUN_00189320(0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)ecx);
  csprintf((char *)0x005ab100, (char *)0x0025bc44);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e53b */
  /* mem[0x005ac9a0] = eax */
  /* mem[0x005ac9a8] = eax */
  /* mem[0x005ac9a4] = edx */
  FUN_00189cb0(0, (void *)0, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e59c */
  /* cmp eax, -1 -> je 0x4e59c */
  ai_communication_get_player_rating(0, 0, (void *)0, (void *)0);
  csprintf((char *)0x005ab100, (char *)0x0025afc4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4e681 */
  /* test (char)eax, (char)eax -> je 0x4e681 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x4e5d5 */
  /* cmp (int16_t)eax, 1 -> jne 0x4e5eb */
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x0025bc28);
  /* cmp eax, 0xbf800000 -> je 0x4e666 */
  csprintf((char *)0x005ab100, (char *)0x0025bc18);
  FUN_0008dc30((char *)(uintptr_t)ecx, (char *)(uintptr_t)eax);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> jne 0x4e697 */
  /* test (char)eax, (char)eax -> je 0x4ee7f */
  FUN_00064540((void *)0, 0);
  FUN_00064570((void *)(uintptr_t)eax);
  /* test edi, edi -> je 0x4ed04 */
  /* cmp (int16_t)eax, 4 -> jl 0x4e752 */
  /* cmp (int16_t)eax, 5 -> jg 0x4e752 */
  /* test (char)eax, (char)eax -> jne 0x4e74d */
  display_assert((char *)0x0025bc0c, (char *)0x0025ab74, 2230, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x4e75e */
  /* test (char)eax, (char)eax -> jne 0x4e775 */
  /* test (char)eax, (char)eax -> je 0x4ecee */
  /* test (char)eax, (char)eax -> jne 0x4e789 */
  /* test (char)eax, (char)eax -> jne 0x4ecee */
  FUN_00189270(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (void *)(uintptr_t)ecx);
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> jne 0x4e91a */
  FUN_00189540(0, (void *)0, 0.0f, (void *)0);
  FUN_00189320(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)ebx);
  /* test (int16_t)eax, (int16_t)eax -> jg 0x4e971 */
  /* cmp (int16_t)ecx, 4 -> jl 0x4ea5b */
  /* cmp (int16_t)ecx, 5 -> jg 0x4ea5b */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x4e989 */
  crt_sprintf((char *)0x005ab100, (char *)0x0025bc00);
  csstrcpy((char *)0x005ab100, (char *)0x0025386f);
  /* cmp (int16_t)eax, 4 -> jl 0x4e9da */
  /* cmp (int16_t)eax, 5 -> jg 0x4e9da */
  csstrcpy((char *)(uintptr_t)ecx, (char *)0x005ab100);
  crt_sprintf((char *)0x005ab100, (char *)0x0025bbf8);
  /* relift: cmp word ptr [edi + 0x24], 4 -> jne 0x4ea10 */
  csstrcpy((char *)(uintptr_t)ecx, (char *)0x005ab100);
  crt_sprintf((char *)0x005ab100, (char *)0x0025bbf0);
  FUN_00189cb0(0, (void *)(uintptr_t)edx, (void *)0x005ab100, 0);
  /* test (char)eax, (char)eax -> je 0x4eb41 */
  /* test (char)eax, (char)eax -> je 0x4ea79 */
  csprintf((char *)0x005ab100, (char *)0x0025aec8);
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)(uintptr_t)eax, 0);
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0x00253e8c, 0);
  /* test (char)eax, (char)eax -> je 0x4ebd8 */
  /* relift: cmp word ptr [edi + 0x9c], 0 -> jle 0x4ebd8 */
  /* cmp ecx, eax -> je 0x4eb76 */
  game_time_get();
  csprintf((char *)0x005ab100, (char *)0x0025bbe4);
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x4ecee */
  /* test (char)eax, (char)eax -> je 0x4ecee */
  crt_sprintf((char *)0x005ab100, (char *)0x0025bbd0);
  /* relift: cmp word ptr [edi + 0xac], 0 -> jle 0x4ec5c */
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x0025bbc8);
  FUN_0008dc30((char *)0x005ab100, (char *)(uintptr_t)ecx);
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0x005ab100, 0);
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  FUN_00064570((void *)(uintptr_t)ecx);
  /* test edi, edi -> jne 0x4e700 */
  /* test (char)eax, (char)eax -> je 0x4edb0 */
  /* relift: cmp word ptr [esi + 0x3a8], 0 -> jle 0x4edb0 */
  datum_get((void *)(uintptr_t)eax, 0);
  csprintf((char *)0, (char *)0);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)edi, (void *)0);
  /* test (char)eax, (char)eax -> jne 0x4edd9 */
  /* test (char)eax, (char)eax -> jne 0x4edd9 */
  crt_sprintf((char *)0x005ab100, (char *)0x0025acb8);
  crt_sprintf((char *)0x005ab100, (char *)0x0025bbb8);
  /* mem[0x005ac9a8] = eax */
  /* mem[0x005ac9a0] = ecx */
  /* mem[0x005ac9a4] = edx */
  FUN_00189cb0(0, (void *)0, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4f0cb */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x4f0cb */
  csprintf((char *)0x005ab100, (char *)0x0025bb14);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* cmp eax, 3 -> ja 0x4f0cb */
  datum_get((void *)(uintptr_t)ecx, 0);
  FUN_00189270(0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)eax, (void *)0);
  /* cmp eax, -1 -> je 0x4f0cb */
  datum_get((void *)(uintptr_t)eax, 0);
  FUN_00189270(0, (float *)(uintptr_t)ebx, (float *)0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x4f145 */
  actor_get_pursuit_location();
  /* test edi, edi -> je 0x4f145 */
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0x4f126 */
  /* cmp eax, -1 -> je 0x4f126 */
  datum_get((void *)(uintptr_t)ecx, 0);
  actor_action_debug_color(0);
  FUN_00189270(0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)edi, (void *)0);
  /* cmp (int16_t)ecx, 1 -> jne 0x4f145 */
  actor_action_debug_color(0);
  FUN_00189270(0, (float *)(uintptr_t)ebx, (float *)(uintptr_t)edi, (void *)0);
  /* test (char)eax, (char)eax -> je 0x4f516 */
  /* test (char)eax, (char)eax -> je 0x4f516 */
  /* relift: cmp dword ptr [esi + 0x18], -1 -> je 0x4f516 */
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  units_debug_get_closest_unit(0, (void *)0);
  FUN_00189320(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  FUN_00189320(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  FUN_00189320(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  /* relift: cmp word ptr [edi + 0x64], 0 -> jne 0x4f516 */
  /* relift: cmp dword ptr [edi + 0xcc], -1 -> jne 0x4f516 */
  tag_get('dpib', 0);
  units_debug_get_closest_unit(0, (void *)(uintptr_t)ecx);
  /* test (char)eax, 4 -> je 0x4f46b */
  biped_build_flying_axes((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  FUN_00189320(0, (float *)0, (float *)0, 0.0f, (void *)0);
  /* test (char)eax, (char)eax -> je 0x4f6d6 */
  /* cmp edx, -1 -> je 0x4f6d6 */
  /* test (char)eax, 0x41 -> jne 0x4f59b */
  /* test eax, eax -> jne 0x4f69a */
  unit_estimate_position(0, 0, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)(uintptr_t)eax, (void *)(uintptr_t)ecx);
  FUN_00189320(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)edi);
  /* test (char)eax, (char)eax -> jne 0x4f6ec */
  /* test (char)eax, (char)eax -> je 0x4f8e9 */
  /* relift: cmp word ptr [esi + 0x268], 0 -> je 0x4f8e9 */
  /* cmp eax, -1 -> je 0x4f8e9 */
  datum_get((void *)(uintptr_t)eax, 0);
  display_assert((char *)0, (char *)0x0025ab74, 2653, 0);
  system_exit(0);
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x4f880 */
  /* relift: cmp dword ptr [edi + 0x8c], -1 -> je 0x4f880 */
  FUN_00189540(0, (void *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)ecx);
  /* relift: cmp word ptr [edi + 0x9c], 0 -> jle 0x4f8e9 */
  /* test (char)eax, (char)eax -> je 0x4f89c */
  /* test (char)eax, (char)eax -> jne 0x4f8e9 */
  /* cmp ecx, eax -> je 0x4f8b6 */
  game_time_get();
  csprintf((char *)0x005ab100, (char *)0x0025bbe4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4f945 */
  observer_get_camera(0);
  /* test eax, eax -> je 0x4f945 */
  actor_action_debug_color(0);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)ebx, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x5020b */
  /* cmp eax, -1 -> je 0x4fa13 */
  datum_get((void *)(uintptr_t)edx, 0);
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  encounter_get_squad((char *)(uintptr_t)edi, edx);
  /* test (int16_t)ecx, (int16_t)ecx -> jle 0x4fa13 */
  /* test dl, dl -> je 0x4f9e4 */
  csprintf((char *)0x005ab100, (char *)0x0025bb00);
  /* relift: test byte ptr [ebx + 0x28], 8 -> je 0x4f9f8 */
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* cmp eax, 8 -> ja 0x5020b */
  /* test (char)eax, (char)eax -> je 0x5020b */
  actor_action_debug_color(0);
  FUN_00189540(0, (void *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)eax);
  /* relift: cmp word ptr [esi + 0x9c], 0 -> jle 0x5020b */
  actor_action_debug_color(0);
  csprintf((char *)0x005ab100, (char *)0x0025bad0);
  actor_action_debug_color(0);
  csprintf((char *)0x005ab100, (char *)0x0025bac8);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* relift: cmp word ptr [esi + 0x9e], 0 -> jle 0x4fb19 */
  actor_action_debug_color(0);
  csprintf((char *)0x005ab100, (char *)0x0025bac0);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4fb9d */
  /* test (char)eax, (char)eax -> je 0x4fb53 */
  actor_action_debug_color(0);
  csprintf((char *)0x005ab100, (char *)0x0025bab4);
  actor_action_debug_color(0);
  csprintf((char *)0x005ab100, (char *)0x0025baa4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x5020b */
  actor_action_debug_color(0);
  FUN_00189320(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  actor_get_pursuit_location();
  display_assert((char *)0x0025ba88, (char *)0x0025ab74, 2773, 0);
  system_exit(0);
  actor_action_debug_color(0);
  csprintf((char *)0x005ab100, (char *)0x0025ba7c);
  /* cmp (int16_t)edi, 1 -> jne 0x4fc5f */
  csprintf((char *)0x005ab100, (char *)0x0025ba74);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* cmp (int16_t)eax, 5 -> jne 0x4fc86 */
  /* cmp (int16_t)eax, 7 -> jne 0x4fca7 */
  /* cmp eax, edi -> jg 0x4fcaa */
  actor_action_debug_color(0);
  csprintf((char *)0x005ab100, (char *)0x0025ba68);
  /* test (char)eax, (char)eax -> je 0x4fce8 */
  csstrcpy((char *)(uintptr_t)eax, (char *)0x0025386f);
  /* test (char)eax, (char)eax -> je 0x4fd1a */
  FUN_0008dc30((char *)(uintptr_t)ecx, (char *)0x0025ba50);
  /* test (char)eax, (char)eax -> je 0x4fd38 */
  FUN_0008dc30((char *)(uintptr_t)edx, (char *)0x0025ba44);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x4fd67 */
  csprintf((char *)0x005ab100, (char *)0x0025ba34);
  FUN_0008dc30((char *)(uintptr_t)ecx, (char *)(uintptr_t)eax);
  FUN_0002a3d0(0);
  /* test (char)eax, (char)eax -> je 0x4fdac */
  FUN_0002a3f0(0);
  /* test (char)eax, (char)eax -> je 0x4fd98 */
  FUN_0008dc30((char *)(uintptr_t)edx, (char *)0x0025ba24);
  FUN_0008dc30((char *)(uintptr_t)eax, (char *)0x0025ba1c);
  /* test (char)eax, (char)eax -> je 0x4fdca */
  FUN_0008dc30((char *)(uintptr_t)ecx, (char *)0x0025ba14);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  FUN_00189270(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)edi, (void *)(uintptr_t)ecx);
  FUN_00189320(0, (float *)(uintptr_t)edi, (float *)(uintptr_t)ecx, 0.0f, (void *)(uintptr_t)eax);
  /* cmp eax, 5 -> ja 0x4fee0 */
  csprintf((char *)0x005ab100, (char *)0x0025b9e4);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x5020b */
  /* cmp (int16_t)eax, 0xffff -> je 0x5020b */
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)eax, (char)eax -> jne 0x5020b */
  csprintf((char *)0x005ab100, (char *)0x0025b9ac);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* cmp eax, ecx -> jge 0x4ff92 */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 32);
  /* relift: test byte ptr [esi + 0xa8], 2 -> je 0x4ffb7 */
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test ebx, ebx -> je 0x5020b */
  /* test (char)eax, (char)eax -> je 0x50029 */
  /* test (char)eax, (char)eax -> je 0x50003 */
  FUN_00189540(0, (void *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)ecx);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x500a1 */
  /* relift: cmp eax, dword ptr [ecx] -> jge 0x500a1 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 20);
  FUN_00189270(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)edi, (void *)(uintptr_t)ecx);
  vector3d_scale_add((float *)(uintptr_t)edi, (float *)(uintptr_t)ecx, 0.0f, (float *)(uintptr_t)eax);
  csprintf((char *)0x005ab100, (char *)0x0025acb8);
  /* test dl, dl -> je 0x500f8 */
  /* test (char)eax, 1 -> jne 0x500f8 */
  vector3d_from_angle((float *)(uintptr_t)eax, 0.0f);
  FUN_00189320(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, 0.0f, (void *)(uintptr_t)ecx);
  csprintf((char *)0x005ab100, (char *)0x0025b978);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x501d7 */
  /* test (int16_t)edx, (int16_t)edx -> jl 0x501a9 */
  /* cmp eax, edi -> jge 0x501a9 */
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 20);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)edi, (void *)(uintptr_t)eax);
  vector3d_scale_add((float *)(uintptr_t)edi, (float *)(uintptr_t)eax, 0.0f, (float *)(uintptr_t)edx);
  csprintf((char *)0x005ab100, (char *)0x0025acb8);
  csprintf((char *)0x005ab100, (char *)0x0025b950);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  global_scenario_get();
  FUN_00017120((void *)(uintptr_t)eax, (void *)0, (char *)0, 0);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x50528 */
  /* relift: cmp word ptr [edi + 8], 3 -> je 0x50427 */
  FUN_0002a360(0);
  csprintf((char *)0x005ab100, (char *)0x0025b924);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x502a8 */
  /* test (char)eax, (char)eax -> je 0x502e8 */
  csprintf((char *)0x005ab100, (char *)0x0025b914);
  /* test (char)eax, (char)eax -> je 0x5030e */
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* cmp eax, 4 -> ja 0x5040a */
  csprintf((char *)0x005ab100, (char *)0x0025ba68);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  csprintf((char *)0x005ab100, (char *)0x0025b908);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  csprintf((char *)0x005ab100, (char *)0x0025b8fc);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  csprintf((char *)0x005ab100, (char *)0x0025b8f0);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  display_assert((char *)0, (char *)0x0025ab74, 3081, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x50528 */
  /* cmp (int16_t)eax, 0x14 -> jge 0x50528 */
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* relift: cmp dword ptr [edi + 0x150], -1 -> je 0x50667 */
  game_time_get();
  /* cmp ecx, eax -> jl 0x50667 */
  /* cmp eax, 0xa -> ja 0x50639 */
  crt_sprintf((char *)0x005ab100, (char *)0x0025b7a0);
  crt_sprintf((char *)0x005ab100, (char *)0x0025b780);
  crt_sprintf((char *)0x005ab100, (char *)0x0025b76c);
  crt_sprintf((char *)0x005ab100, (char *)0x0025b750);
  csstrcpy((char *)0x005ab100, (char *)0x0025b724);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x506d9 */
  /* test eax, eax -> jne 0x5067d */
  /* cmp eax, -1 -> je 0x506a0 */
  unit_is_busy(0);
  csprintf((char *)0x005ab100, (char *)0x0025b704);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x50a07 */
  /* relift: cmp word ptr [esi + 0x280], 0 -> jle 0x50a07 */
  /* test (char)eax, (char)eax -> je 0x5072a */
  /* relift: cmp word ptr [esi + 0x284], 0 -> jle 0x50710 */
  /* test (char)eax, (char)eax -> je 0x50722 */
  FUN_00189270(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)edi, (void *)(uintptr_t)ebx);
  FUN_00189540(0, (void *)(uintptr_t)edi, 0.0f, (void *)(uintptr_t)eax);
  FUN_00189320(0, (float *)(uintptr_t)edi, (float *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)edx);
  FUN_00189540(0, (void *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)ecx);
  /* relift: cmp word ptr [esi + 0x280], 2 -> jne 0x507d3 */
  /* cmp (int16_t)eax, 0xffff -> jne 0x507b0 */
  csprintf((char *)0x005ab100, (char *)0x0025acb8);
  FUN_00189cb0(0, (void *)(uintptr_t)edi, (void *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [esi + 0x280], 1 -> jne 0x50814 */
  /* cmp (int16_t)eax, 0xffff -> jne 0x507f1 */
  csprintf((char *)0x005ab100, (char *)0x0025acb8);
  FUN_00189cb0(0, (void *)(uintptr_t)edi, (void *)(uintptr_t)eax, 0);
  /* relift: cmp dword ptr [eax + 0x168], -1 -> je 0x50982 */
  game_time_get();
  /* cmp ecx, eax -> jl 0x50985 */
  /* test (char)eax, (char)eax -> je 0x50863 */
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* cmp eax, 0xd -> ja 0x50953 */
  crt_sprintf((char *)0x005ab100, (char *)0x0025b6d0);
  crt_sprintf((char *)0x005ab100, (char *)0x0025b6b8);
  /* relift: cmp dword ptr [edi + 0x180], 0x7f7fffff -> jne 0x50910 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x52ab0 */
void FUN_00052ab0(void)
{
  int eax = 0;
  int ecx = 0;

  /* test (char)eax, (char)eax -> je 0x52b3d */
  /* test (char)eax, (char)eax -> je 0x52b3d */
  FUN_0004b220();
  ai_debug_describe_actor(0, 0, 0, (char *)(uintptr_t)ecx, 256);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  FUN_0004c560();

  (void)eax;
  (void)ecx;
}

/* 0x52b60 */
void FUN_00052b60(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  encounter_iterator_next((void *)(uintptr_t)ecx, eax);
  FUN_00059b50((void *)(uintptr_t)edx);
  /* test eax, eax -> je 0x52bac */
  FUN_0004c920();
  FUN_00059b50((void *)(uintptr_t)edx);
  /* test eax, eax -> jne 0x52b85 */

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x52bb0 */
void FUN_00052bb0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  datum_get((void *)(uintptr_t)eax, 0);
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  encounter_actor_iterator_new((void *)(uintptr_t)edx, 0);
  encounter_actor_iterator_next((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x52c53 */
  /* cmp ecx, edi -> je 0x52c32 */
  /* test (char)eax, (char)eax -> je 0x52c43 */
  FUN_0004c920();
  encounter_actor_iterator_next((void *)(uintptr_t)ecx);
  /* test eax, eax -> jne 0x52c10 */
  /* relift: cmp dword ptr [0x2c8e5c], edi -> jne 0x52cc9 */
  /* mem[0x002c8e5c] = edx */
  /* mem[0x002c8e5c] = edx */
  encounter_build_firing_position_owner_actor_indices(0, (void *)(uintptr_t)edx);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 24);
  csmemset((void *)0, 0, 0);
  /* cmp eax, -1 -> je 0x52d96 */
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp ecx, eax -> je 0x52dc7 */
  game_in_editor();
  /* test (char)eax, (char)eax -> jne 0x52f3e */
  datum_get((void *)(uintptr_t)eax, 0);
  global_scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* relift: test dword ptr [eax + ebx*4 + 0x54], edx -> je 0x52e90 */
  /* relift: cmp byte ptr [esi + 0x98], 0 -> je 0x52eb0 */
  /* relift: test dword ptr [eax + ecx*4 + 0x54], edx -> je 0x52ee6 */
  /* relift: test dword ptr [eax + 0x6c], edx -> je 0x52f02 */
  /* test ebx, ebx -> jne 0x52f19 */
  /* cmp ebx, 8 -> jl 0x52f3e */
  display_assert((char *)0x0025bfd0, (char *)0x0025ab74, 964, 0);
  system_exit(0);
  datum_get((void *)(uintptr_t)edx, 0);
  actor_action_debug_color(0);
  FUN_00188a90((float *)(uintptr_t)ecx, 0, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x530e5 */
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  /* test ebx, ebx -> jle 0x5315b */
  FUN_00189270(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (void *)(uintptr_t)eax);
  FUN_00189ba0((float *)(uintptr_t)eax, 0, (void *)(uintptr_t)edx);
  /* cmp esi, ebx -> jl 0x530f0 */
  FUN_0004b220();
  /* test (char)ecx, (char)ecx -> je 0x533b5 */
  /* cmp eax, -1 -> je 0x53233 */
  csprintf((char *)0x005ab100, (char *)0x0025bfc0);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* cmp eax, -1 -> je 0x53233 */
  actor_get_pursuit_location();
  /* test eax, eax -> je 0x53231 */
  /* relift: cmp word ptr [eax], 1 -> jne 0x53231 */
  /* relift: cmp (int16_t)ecx, word ptr [ebp - 0x28] -> jne 0x53231 */
  encounter_pursuit_position_already_examined(0, 0, edx, 0, (void *)0, (void *)0);
  /* cmp ecx, -1 -> jne 0x5326b */
  /* test (char)ebx, (char)ebx -> je 0x53277 */
  /* mem[0x005ac9a4] = eax */
  /* mem[0x005ac9a0] = edx */
  /* mem[0x005ac9a8] = edx */
  csprintf((char *)0, (char *)0);
  FUN_00189cb0(0, (void *)0x005ac9a0, (void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x53496 */
  /* test (char)eax, (char)eax -> je 0x53496 */
  /* test (char)eax, (char)eax -> je 0x53496 */
  /* test (char)eax, (char)eax -> je 0x53496 */
  /* test (char)eax, (char)eax -> je 0x53496 */
  FUN_00189270(0, (float *)0, (float *)0, (void *)0);
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)edi, (void *)(uintptr_t)eax);
  /* test (char)ecx, (char)ecx -> je 0x53496 */
  /* test (char)eax, (char)eax -> je 0x53496 */
  /* test (char)eax, (char)eax -> jne 0x53496 */
  /* cmp ecx, -1 -> je 0x53496 */
  /* test (char)eax, (char)eax -> jne 0x53405 */
  /* test (char)eax, 0x41 -> jne 0x534c2 */
  /* test eax, eax -> je 0x53466 */
  csprintf((char *)0x005ab100, (char *)0x0025bfc0);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  csprintf((char *)0x005ab100, (char *)0x0025bfc0);
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x534d0 */
void FUN_000534d0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* test (char)ecx, (char)ecx -> je 0x5361d */
  /* mem[0x005acab4] = edx */
  datum_get((void *)(uintptr_t)edx, 0);
  /* mem[0x005ac9f4] = eax */
  /* test (char)eax, (char)eax -> je 0x53534 */
  FUN_0004b7a0();
  /* test (char)eax, (char)eax -> je 0x5361d */
  /* test (char)eax, (char)eax -> je 0x5354f */
  FUN_000494e0();
  /* test (char)eax, (char)eax -> je 0x5355d */
  FUN_00049990();
  /* test (char)eax, (char)eax -> je 0x5356b */
  FUN_000495b0();
  /* cmp eax, -1 -> je 0x5357e */
  FUN_00052bb0();
  /* cmp eax, -1 -> je 0x53595 */
  FUN_0004c920();
  /* test (char)eax, (char)eax -> je 0x535a3 */
  FUN_0004c890();
  /* test (char)eax, (char)eax -> je 0x535b1 */
  FUN_00052ab0();
  /* test (char)eax, (char)eax -> je 0x535bf */
  FUN_00049d60();
  /* test (char)eax, (char)eax -> je 0x535d3 */
  FUN_00052b60();
  /* test (char)eax, (char)eax -> jne 0x535ee */
  /* test (char)eax, (char)eax -> jne 0x535ee */
  /* test (char)eax, (char)eax -> je 0x535f3 */
  FUN_0004b810();
  /* test (char)eax, (char)eax -> je 0x53601 */
  FUN_0004a770();
  /* test (char)eax, (char)eax -> je 0x5360f */
  FUN_0004a8c0();
  /* test (char)eax, (char)eax -> je 0x5361d */

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x53650 */
void FUN_00053650(void)
{
  csmemset((void *)0x005abaac, 0, 3808);
}

/* 0x53680 */
void FUN_00053680(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp word ptr [ebx - 4], (int16_t)edi -> je 0x536be */
  display_assert((char *)0x0025c08c, (char *)0x0025c0ac, 140, 0);
  system_exit(0);
  /* test eax, eax -> je 0x536ca */
  /* cmp (int16_t)eax, 0x3c -> jl 0x53706 */
  display_assert((char *)0x0025c030, (char *)0x0025c0ac, 151, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [esi + 2] -> jge 0x5371a */

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x53790 */
void FUN_00053790(void)
{
  int eax = 0;
  int esi = 0;

  csstrlen((char *)(uintptr_t)esi);
  crt_sprintf((char *)(uintptr_t)eax, (char *)0);

  (void)eax;
  (void)esi;
}

/* 0x53800 */
void FUN_00053800(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  interface_draw_text(0, 0, 0, 0, 0, 0);
  draw_string_set_color((void *)(uintptr_t)esi);
  draw_string_set_tab_stops((void *)(uintptr_t)edx, 0);
  rasterizer_text_draw((void *)(uintptr_t)edx, (void *)0, (void *)(uintptr_t)ecx, 0, (char *)(uintptr_t)eax);
  draw_string_set_tab_stops((void *)0, 0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x53890 */
void FUN_00053890(void)
{
  console_printf(0, (void *)0x0025c120);
}

/* 0x538d0 */
void FUN_000538d0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x538f0 */
void FUN_000538f0(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  encounter_iterator_next((void *)(uintptr_t)eax, esi);
  FUN_00059b50((void *)(uintptr_t)ecx);
  /* test eax, eax -> je 0x53937 */
  /* test (char)ecx, (char)ecx -> je 0x53920 */
  FUN_00059b50((void *)0);
  /* test eax, eax -> jne 0x53913 */

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x53960 */
void FUN_00053960(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  encounter_iterator_next((void *)(uintptr_t)eax, esi);
  FUN_00059b50((void *)(uintptr_t)ecx);
  /* test eax, eax -> je 0x5399a */
  FUN_00059b50((void *)0);
  /* test eax, eax -> jne 0x53983 */

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x539c0 */
void FUN_000539c0(void)
{
  crt_sprintf((void *)0x005ab280, (void *)0x0025c134);
  FUN_00053800();
}

/* 0x53a20 */
void FUN_00053a20(void)
{
  crt_sprintf((void *)0x005ab280, (void *)0x0025c154);
  FUN_00053800();
}

/* 0x53a90 */
void FUN_00053a90(void)
{
  crt_sprintf((void *)0x005ab280, (void *)0x0025c174);
  FUN_00053800();
}

/* 0x53af0 */
void FUN_00053af0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  crt_sprintf((char *)0x005ab280, (char *)0x0025c198);
  FUN_00053800();
  crt_sprintf((char *)0x005ab280, (char *)0x0025c1d8);
  FUN_00053800();
  crt_sprintf((char *)0x005ab280, (char *)0x0025c218);
  FUN_00053800();
  observer_get_camera(0);
  /* test (int16_t)ecx, (int16_t)ecx -> jle 0x53d91 */
  /* test eax, eax -> je 0x53d91 */
  encounter_iterator_next((void *)0, 0);
  FUN_00059b50((void *)(uintptr_t)edx);
  /* test eax, eax -> je 0x53d91 */
  datum_get((void *)(uintptr_t)ecx, 0);
  actor_activation_debug_color(0);
  actor_action_debug_color(0);
  /* test ebx, ebx -> je 0x53d7a */
  /* test (char)eax, (char)eax -> je 0x53d64 */
  /* cmp esi, -1 -> je 0x53d7a */
  object_get_and_verify_type(0, 0);
  unit_get_head_position(0, (float *)(uintptr_t)ecx);
  FUN_00189270(0, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (void *)(uintptr_t)ebx);
  /* cmp esi, -1 -> jne 0x53d30 */
  FUN_00189270(0, (float *)(uintptr_t)ecx, (float *)(uintptr_t)esi, (void *)0);
  FUN_00059b50((void *)(uintptr_t)edx);
  /* test eax, eax -> jne 0x53ce0 */
  FUN_00053c50();
  /* test (char)eax, (char)eax -> je 0x53e10 */
  /* test (char)eax, (char)eax -> je 0x53dca */
  /* relift: tail-call FUN_00053af0(); */
  /* test (char)eax, (char)eax -> je 0x53dd8 */
  FUN_00053b80();
  /* test (char)eax, (char)eax -> je 0x53de6 */
  FUN_00053bf0();
  /* test (char)eax, (char)eax -> je 0x53df4 */
  FUN_00053a90();
  /* test (char)eax, (char)eax -> je 0x53e02 */
  FUN_00053a20();
  /* test (char)eax, (char)eax -> je 0x53e10 */
  /* test ecx, ecx -> jle 0x53e6e */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 176);
  __strnicmp((char *)(uintptr_t)eax, (char *)(uintptr_t)ebx, 32);
  /* test eax, eax -> je 0x53e6c */
  /* cmp esi, eax -> jl 0x53e41 */
  /* test ecx, ecx -> jle 0x53ece */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 232);
  __strnicmp((char *)(uintptr_t)eax, (char *)(uintptr_t)ebx, 32);
  /* test eax, eax -> je 0x53ecc */
  /* cmp esi, eax -> jl 0x53ea1 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
/* --- ai_debug.obj orphan shells (2026-07-26) --- */

/* orphan 0x4a460 */
void FUN_0004a460(int a0, int a1, void *buf, int buf_size, int max_entries)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x0025aea4, (char *)0x0025ab74, 4947, 0);
  system_exit(0);
  /* cmp ebx, 0x800 -> jbe 0x4a4c6 */
  display_assert((char *)0x0025ae90, (char *)0x0025ab74, 4948, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)eax, 0, ebx);
  /* cmp eax, edi -> jle 0x4a587 */
  /* cmp (int16_t)esi, -1 -> je 0x4a551 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x4a514 */
  /* cmp eax, ecx -> jb 0x4a534 */
  display_assert((char *)0x0025ae60, (char *)0x0025ab74, 4957, 0);
  system_exit(0);
  csstrcmp((char *)(uintptr_t)ecx, (char *)0x0025ae38);
  /* test eax, eax -> jne 0x4a57b */
  csmemset((void *)(uintptr_t)edx, 0, ebx);
  /* cmp edi, eax -> jl 0x4a4f0 */
  /* test edi, edi -> jbe 0x4a63b */
  /* relift: test dword ptr [ebp + eax - 0x108], edx -> je 0x4a5c1 */
  /* relift: test dword ptr [eax + ecx], edx -> je 0x4a5be */
  /* cmp esi, edi -> jb 0x4a594 */
  /* test (int16_t)esi, (int16_t)esi -> je 0x4a5fa */
  bit_vector_or(edi, 0, 0, 0);
  console_printf(0, (char *)0x0025ae50);
  /* test (int16_t)esi, (int16_t)esi -> je 0x4a63b */
  FUN_00108fa0(edi, 0, 0);
  bit_vector_and(edi, 0, 0, 0);
  console_printf(0, (char *)0x0025ae3c);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
