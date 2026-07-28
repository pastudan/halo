#include <stdint.h>

/* ai_debug_dispose (0x48f50) — readable C lift. */
extern char DAT_0025ab74[];
void ai_debug_dispose(void)
{
  void *p;

  p = *(void **)0x331f58;
  if (p != NULL) {
    debug_free(p, DAT_0025ab74, 0xa0);
    *(void **)0x331f58 = NULL;
  }
  p = *(void **)0x331f5c;
  if (p != NULL) {
    debug_free(p, DAT_0025ab74, 0xa6);
    *(void **)0x331f5c = NULL;
  }
}

/* ai_debug_dispose_from_old_map (0x48fa0) — readable C lift. */
void ai_debug_dispose_from_old_map(void)
{
  unsigned char *scenario;
  void *elem;
  int index;

  scenario = (unsigned char *)FUN_0018e3b0();
  index = *(int *)0x5ac9f4;
  if (scenario == 0 || index == -1) {
    csstrcpy((char *)0x5ac9d2, (const char *)0x25386f);
    return;
  }
  elem = tag_block_get_element(scenario + 0x42c, index & 0xffff, 0xb0);
  csstrncpy((char *)0x5ac9d2, (const char *)elem, 0x20);
  *(unsigned char *)0x5ac9f1 = 0;
}



/* ai_debug_clear_storage (0x49000) — readable C lift from XBE leaf. */
void ai_debug_clear_storage(void)
{
  if (!*(void **)0x331f58) {
    display_assert((const char *)0x25abac, (const char *)0x25ab74, 0xd0, 1);
    system_exit(-1);
  }
  csmemset(*(void **)0x331f58, 0, 0x657c00);
  if (!*(void **)0x331f5c) {
    display_assert((const char *)0x25ab94, (const char *)0x25ab74, 0xd3, 1);
    system_exit(-1);
  }
  csmemset(*(void **)0x331f5c, 0, 0x394f80);
}

/* ai_debug_actor_deleted (0x49080) — readable C lift. */
void ai_debug_actor_deleted(int actor_handle)
{
  char *table;
  int i;

  table = *(char **)0x331f5c;
  for (i = 0; i < 0x20; i++) {
    char *slot = table + i * 0x1ca7c;
    if (slot[0xc] != 0 && *(int *)slot == actor_handle)
      slot[0xc] = 0;
  }
}

/* ai_debug_get_path_storage (0x49120) — readable C lift (restored pre-naked) — find or allocate a path debug storage
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

/* ai_debug_select_encounter (0x49220) — readable C lift. */
void ai_debug_select_encounter(int encounter_idx)
{
  if (*(int *)0x5ac9f4 == encounter_idx) {
    return;
  }
  *(int *)0x5ac9f4 = encounter_idx;
  *(char *)0x629d40 = 0;
  csmemset((void *)0x629d44, 0, 0x670);
  csmemset((void *)0x62a3b4, 0, 0x8000);
  ai_debug_select_actor(encounter_idx, -1);
}

/* FUN_000494d0: set debug ray-test success flag.
 *
 * No __FILE__ string. Called from ai_debug_get_last_path (ray setup) and
 * FUN_000494e0 (ray render). */
void FUN_000494d0(char success)
{
  *(uint8_t *)0x5acab9 = success;
}

/* ai_debug_update (0x4ab10) — readable C lift (restored pre-naked). */
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

/* ai_debug_select_actor (0x4b1b0) — readable C lift. */
void ai_debug_select_actor(int encounter_idx, int actor_idx)
{
  int i;
  char *p;

  if (*(int *)0x5ac9f4 == encounter_idx && *(int *)0x5ac9f8 == actor_idx)
    return;
  ai_debug_select_encounter(encounter_idx);
  *(int *)0x5ac9f8 = actor_idx;
  *(uint8_t *)0x629d40 = 0;
  p = (char *)0x62a3b5;
  for (i = 0; i < 0x200; i++) {
    *p = 0;
    p += 0x40;
  }
  *(uint8_t *)0x6323d4 = (actor_idx != -1);
  *(int *)0x6323d8 = actor_idx;
  *(uint16_t *)0x6323dc = 0;
}

/* ai_debug_initialize_for_new_map (0x4c0f0) — readable C lift from XBE leaf. */
void ai_debug_initialize_for_new_map(void)
{
  int encounter_idx;
  int i;
  unsigned char *p;

  encounter_idx = encounter_get_by_name((char *)0x5ac9d2);
  ai_debug_clear_storage();
  if (*(int *)0x5ac9f4 == encounter_idx && *(int *)0x5ac9f8 == -1) {
    return;
  }
  ai_debug_select_encounter(encounter_idx);
  *(int *)0x5ac9f8 = -1;
  *(unsigned char *)0x629d40 = 0;
  p = (unsigned char *)0x62a3b5;
  for (i = 0; i < 0x200; i++) {
    *p = 0;
    p += 0x40;
  }
  *(unsigned char *)0x6323d4 = 0;
  *(int *)0x6323d8 = -1;
  *(short *)0x6323dc = 0;
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

/* set_real_point3d (0x53620) — readable C lift. */
void set_real_point3d(void)
{
  csmemset((void *)0x5abaa0, 0, 0xeec);
  *(uint8_t *)0x5abaa4 = 1;
}

/* ai_debug_get_last_path (0x493d0) — readable C lift. */
void ai_debug_get_last_path(float *vec_a, float *vec_b)
{
  *(char *)0x5acab8 = 1;
  *(char *)0x5acab9 = 0;
  *(float *)0x5acabc = vec_a[0];
  *(float *)0x5acac0 = vec_a[1];
  *(float *)0x5acac4 = vec_a[2];
  *(float *)0x5acac8 = vec_b[0];
  *(float *)0x5acacc = vec_b[1];
  *(float *)0x5acad0 = vec_b[2];
  *(int *)0x5acad4 = 0;
}

/* ai_debug_communication_suppress (0x4a650) — readable C lift. */
void ai_debug_communication_suppress(int a0, int a1)
{
  FUN_0004a460(a0, (const char **)a1, (unsigned int *)0x5aca14, 0x39, (int16_t (*)(const char *))0x42ce0);
}

/* ai_debug_communication_ignore (0x4a680) — readable C lift. */
void ai_debug_communication_ignore(int a0, int a1)
{
  FUN_0004a460(a0, (const char **)a1, (unsigned int *)0x5aca1c, 0x39, (int16_t (*)(const char *))0x42ce0);
}

/* ai_debug_communication_focus (0x4a6b0) — readable C lift. */
void ai_debug_communication_focus(int a0, int a1)
{
  FUN_0004a460(a0, (const char **)a1, (unsigned int *)0x5aca24, 0xd1, (int16_t (*)(const char *))0x1a67e0);
}

/* ai_debug_idle_look_clear (0x4a6e0) — readable C lift. */
void ai_debug_idle_look_clear(int actor_handle)
{
  *(char *)0x6323d4 = actor_handle != -1;
  *(int *)0x6323d8 = actor_handle;
  *(int16_t *)0x6323dc = 0;
}

/* ai_debug_idle_look_addprop (0x4a710) — readable C lift. */
extern char DAT_0025ab74[];
extern char DAT_0025aeac[];
void ai_debug_idle_look_addprop(int prop, float score)
{
  int16_t count;

  if (*(uint8_t *)0x6323d4 == 0) {
    display_assert(DAT_0025aeac, DAT_0025ab74, 0x13b1, true);
    system_exit(-1);
  }
  count = *(int16_t *)0x6323dc;
  if (count >= 0x20)
    return;
  *(int *)(0x6323e0 + (int)count * 4) = prop;
  *(float *)(0x632460 + (int)count * 4) = score;
  *(int16_t *)0x6323dc = (int16_t)(count + 1);
}

/* ai_debug_change_selected_encounter (0x4afa0) — XBE naked draft (batch 125). */
#if defined(__clang__)
static int (*const b4afa0_c1198f0)(data_t *data, int prev_index) = data_next_index;
static unsigned int (*const b4afa0_c119980)(data_t *data, int datum) = data_prev_index;
static int (*const b4afa0_c119270)(data_t *data, int absolute_index) = datum_absolute_index_to_index;
static void (*const b4afa0_cff4d0)(int channel, const char *format, ...) = console_printf;
static void (*const b4afa0_c49220)(int encounter_idx) = ai_debug_select_encounter;
static scenario_t * (*const b4afa0_c18e380)(void) = global_scenario_get;
static void *(*const b4afa0_elem)(void *, int, int) = tag_block_get_element;
static char * (*const b4afa0_c8dff0)(char *destination, const char *source) = csstrcpy;
static int (*const b4afa0_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;

__attribute__((naked, noinline))
void ai_debug_change_selected_encounter(char forward __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x200, %%esp\n\t"
      "movb 0x8(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "je .Lai_debug_change_selected_encounter_1\n\t"
      "movl 0x5ac9f4, %%eax\n\t"
      "movl 0x5ab270, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1198f0]\n\t"
      "jmp .Lai_debug_change_selected_encounter_2\n\t"
      ".Lai_debug_change_selected_encounter_1:\n\t"
      "movl 0x5ac9f4, %%edx\n\t"
      "movl 0x5ab270, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c119980]\n\t"
      ".Lai_debug_change_selected_encounter_2:\n\t"
      "movl 0x5ab270, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c119270]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lai_debug_change_selected_encounter_3\n\t"
      "pushl $0x25afac\n\t"
      "pushl %%eax\n\t"
      "call *%[cff4d0]\n\t"
      "pushl $-1\n\t"
      "call *%[c49220]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lai_debug_change_selected_encounter_3:\n\t"
      "pushl %%esi\n\t"
      "movl %%ebx, %%edx\n\t"
      "andl $0xffff, %%edx\n\t"
      "pushl $0xb0\n\t"
      "pushl %%edx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x20(%%esi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $0x20, %%al\n\t"
      "je .Lai_debug_change_selected_encounter_4\n\t"
      "leal -0x200(%%ebp), %%eax\n\t"
      "pushl $0x25af9c\n\t"
      "pushl %%eax\n\t"
      "call *%[c8dff0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Lai_debug_change_selected_encounter_8\n\t"
      ".Lai_debug_change_selected_encounter_4:\n\t"
      "movw 0x7e(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .Lai_debug_change_selected_encounter_5\n\t"
      "leal -0x100(%%ebp), %%ecx\n\t"
      "pushl $0x253a04\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8dff0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Lai_debug_change_selected_encounter_6\n\t"
      ".Lai_debug_change_selected_encounter_5:\n\t"
      "movswl %%ax, %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x100(%%ebp), %%eax\n\t"
      "pushl $0x25acb8\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lai_debug_change_selected_encounter_6:\n\t"
      "testb $0x40, 0x20(%%esi)\n\t"
      "movl $0x25af94, %%eax\n\t"
      "jne .Lai_debug_change_selected_encounter_7\n\t"
      "movl $0x25af8c, %%eax\n\t"
      ".Lai_debug_change_selected_encounter_7:\n\t"
      "leal -0x100(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal -0x200(%%ebp), %%edx\n\t"
      "pushl $0x25af80\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lai_debug_change_selected_encounter_8:\n\t"
      "movb 0xd(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl $0x25af78, %%eax\n\t"
      "jne .Lai_debug_change_selected_encounter_9\n\t"
      "movl $0x25af6c, %%eax\n\t"
      ".Lai_debug_change_selected_encounter_9:\n\t"
      "movswl 0x2a(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x200(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl $0x25af48\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c49220]\n\t"
      "addl $0x1c, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1198f0] "m"(b4afa0_c1198f0), [c119980] "m"(b4afa0_c119980), [c119270] "m"(b4afa0_c119270), [cff4d0] "m"(b4afa0_cff4d0), [c49220] "m"(b4afa0_c49220), [c18e380] "m"(b4afa0_c18e380), [elem] "m"(b4afa0_elem), [c8dff0] "m"(b4afa0_c8dff0), [c1d90f0] "m"(b4afa0_c1d90f0)
      : "memory");
}
#else
#error "ai_debug_change_selected_encounter: clang naked draft required"
#endif


/* ai_debug_change_selected_actor (0x4c170) — XBE naked draft (batch 126). */
#if defined(__clang__)
static int (*const b4c170_c119270)(data_t *data, int absolute_index) = datum_absolute_index_to_index;
static void (*const b4c170_cff4d0)(int channel, const char *format, ...) = console_printf;
static void (*const b4c170_c4b1b0)(int encounter_idx, int param_2) = ai_debug_select_actor;
static void (*const b4c170_c59a00)(int *iter, int clump_handle) = encounter_actor_iterator_new;
static int (*const b4c170_c59a50)(int *iter) = encounter_actor_iterator_next;
static void * (*const b4c170_c59a90)(int *iter) = encounter_actor_iterator_prev;
static char * (*const b4c170_c49ac0)(int actor_handle, int object_handle, char with_actor, char *buf, int buf_size) = ai_debug_describe_actor;

__attribute__((naked, noinline))
void ai_debug_change_selected_actor(char forward __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x5ac9f4, %%eax\n\t"
      "movl 0x5ab270, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c119270]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lai_debug_change_selected_actor_1\n\t"
      "pushl $0x25b0d0\n\t"
      "pushl %%eax\n\t"
      "call *%[cff4d0]\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "call *%[c4b1b0]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lai_debug_change_selected_actor_1:\n\t"
      "movl 0x5ac9f4, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "xorl %%esi, %%esi\n\t"
      "call *%[c59a00]\n\t"
      "movl 0x5ac9f8, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lai_debug_change_selected_actor_3\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59a50]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lai_debug_change_selected_actor_3\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lai_debug_change_selected_actor_2:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "cmpl 0x5ac9f8, %%edx\n\t"
      "je .Lai_debug_change_selected_actor_3\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "incl %%esi\n\t"
      "call *%[c59a50]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lai_debug_change_selected_actor_2\n\t"
      ".Lai_debug_change_selected_actor_3:\n\t"
      "movb 0x8(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lai_debug_change_selected_actor_4\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59a50]\n\t"
      "addl $4, %%esp\n\t"
      "incl %%esi\n\t"
      "jmp .Lai_debug_change_selected_actor_5\n\t"
      ".Lai_debug_change_selected_actor_4:\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c59a90]\n\t"
      "addl $4, %%esp\n\t"
      "decl %%esi\n\t"
      ".Lai_debug_change_selected_actor_5:\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lai_debug_change_selected_actor_6\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl $0x100\n\t"
      "pushl $0x5ab100\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[c49ac0]\n\t"
      "movswl 0x2a(%%edi), %%ecx\n\t"
      "pushl $0x5ab100\n\t"
      "movswl %%si, %%edx\n\t"
      "pushl %%ecx\n\t"
      "incl %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x25b0c0\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x5ac9f4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c4b1b0]\n\t"
      "addl $0x30, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lai_debug_change_selected_actor_6:\n\t"
      "pushl $0x25b0b0\n\t"
      "pushl $0\n\t"
      "call *%[cff4d0]\n\t"
      "movl 0x5ac9f4, %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[c4b1b0]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c119270] "m"(b4c170_c119270), [cff4d0] "m"(b4c170_cff4d0), [c4b1b0] "m"(b4c170_c4b1b0), [c59a00] "m"(b4c170_c59a00), [c59a50] "m"(b4c170_c59a50), [c59a90] "m"(b4c170_c59a90), [c49ac0] "m"(b4c170_c49ac0)
      : "memory");
}
#else
#error "ai_debug_change_selected_actor: clang naked draft required"
#endif


/* FUN_000490C0 (0x490c0) — readable C lift (ai campaign). */
void *FUN_000490C0(int key)
{
  char *base = *(char **)0x331f5c;
  int best_idx = -1;
  int best_val = -1;
  int i;
  for (i = 0; i < 0x20; i++) {
    char *rec = base + i * 0x1ca7c;
    if (!rec[0xc])
      continue;
    if (*(int *)rec != key)
      continue;
    if (*(int *)(rec + 4) > best_val) {
      best_idx = i;
      best_val = *(int *)(rec + 4);
    }
  }
  if (best_idx == -1)
    return (void *)0;
  return base + best_idx * 0x1ca7c;
}


/* FUN_00049280 (0x49280) — readable C lift.
 * point_a @ecx, color @ebx; stack: count, points. */
void FUN_00049280(int16_t count, float *points, float *point_a, void *color)
{
  int16_t i;
  float *p;

  if (count > 0) {
    FUN_00189450(1, point_a, (float *)((char *)points + 4), color, 0.1f);
  }
  for (i = 0; i < count; i++) {
    p = (float *)((char *)points + 4 + (int)i * 0x10);
    if (i > 0) {
      FUN_00189450(1, (float *)((char *)p - 0x10), p, color, 0.1f);
    }
    FUN_001893e0(1, p, *(float **)0x31fc44, 0.02f, color);
  }
}




/* FUN_00049300 (0x49300) — readable C lift.
 * Oracle: scenario/surface block base in eax. */
void FUN_00049300(void *block_base, int index, float height, void *color)
{
  unsigned char *surface;
  unsigned char *edge_hdr;
  unsigned char *edge;
  float *pt_a;
  float *pt_b;
  int link;
  int limit;
  char use_b;

  surface = (unsigned char *)tag_block_get_element((char *)block_base + 0xb0, 0, 0x60);
  edge_hdr = (unsigned char *)tag_block_get_element((char *)surface + 0x3c, index, 0xc);
  height = height + *(float *)0x25abcc;
  limit = *(int *)(edge_hdr + 4);
  link = limit;
  do {
    edge = (unsigned char *)tag_block_get_element((char *)surface + 0x48, link, 0x18);
    use_b = (*(int *)(edge + 0x14) == index);
    pt_a = (float *)tag_block_get_element((char *)surface + 0x54, *(int *)edge, 0x10);
    pt_b = (float *)tag_block_get_element(
        (char *)surface + 0x54, *(int *)(edge + 4), 0x10);
    FUN_00189450(1, pt_a, pt_b, color, height);
    link = *(int *)(edge + 8 + (int)use_b * 4);
  } while (link != limit);
}

/* FUN_000493B0 (0x493b0) — readable C lift from XBE leaf. */
void FUN_000493B0(float *out, float value, int field_4, int field_8)
{
  out[0] = value;
  *(int *)(out + 1) = field_4;
  *(int *)(out + 2) = field_8;
}

/* ai_debug_lineoffire_addpill (0x49430) — readable C lift. */
void ai_debug_lineoffire_addpill(float *vec_a, float *vec_b, float param_3, char param_4)
{
  int slot; float *dst;
  if (*(char *)0x5acab8 == 0) {
    display_assert((const char *)0x25abd0, (const char *)0x25ab74, 0xfc4, true);
    system_exit(-1);
  }
  slot = *(int *)0x5acad4;
  if (slot >= 0x10) return;
  *((char *)0x5acad8 + slot) = param_4;
  slot = *(int *)0x5acad4;
  dst = (float *)(0x5acae8 + ((slot + slot * 2) << 2));
  dst[0]=vec_a[0]; dst[1]=vec_a[1]; dst[2]=vec_a[2];
  slot = *(int *)0x5acad4;
  dst = (float *)(0x5acba8 + ((slot + slot * 2) << 2));
  dst[0]=vec_b[0]; dst[1]=vec_b[1]; dst[2]=vec_b[2];
  slot = *(int *)0x5acad4;
  *(float *)(0x5acc68 + (slot << 2)) = param_3;
  *(int *)0x5acad4 = slot + 1;
}

/* FUN_000494e0 (0x494e0) — readable C lift from XBE leaf.
 * Debug draw for AI look/idle props when enabled. */
void FUN_000494e0(void)
{
  float sum[3];
  void *color;
  int i;
  int count;
  char *centers;
  void *radius_color;
  void *height;

  if (*(unsigned char *)0x5acab8 == 0)
    return;
  sum[0] = *(float *)0x5acabc + *(float *)0x5acac8;
  sum[1] = *(float *)0x5acac0 + *(float *)0x5acacc;
  sum[2] = *(float *)0x5acac4 + *(float *)0x5acad0;
  if (*(unsigned char *)0x5acab9 != 0)
    color = *(void **)0x2ee6d4;
  else
    color = *(void **)0x2ee6d0;
  FUN_00189270(1, (float *)0x5acabc, sum, color);
  count = *(int *)0x5acad4;
  if (count <= 0)
    return;
  centers = (char *)0x5acae8;
  for (i = 0; i < count; i++) {
    if (*(unsigned char *)(0x5acad8 + i) != 0)
      radius_color = *(void **)0x2ee6d0;
    else
      radius_color = *(void **)0x2ee6d8;
    height = centers + 0xc0;
    FUN_00189860(1, centers, height, *(float *)(0x5acc68 + i * 4), radius_color);
    centers += 0xc;
  }
}



/* FUN_000495b0 (0x495b0) — readable C lift. */
void FUN_000495b0(void)
{
  int n;
  int i;
  int limit;
  void *color;

  if (!*(char *)0x5f8cb4)
    return;

  FUN_00189150(1, (float *)0x5f8cb8, 0.1f, *(void **)0x2ee6e0);
  FUN_00189320(1, (float *)0x5f8cb8, (float *)0x5f8cc4, 1.0f, *(void **)0x2ee6e0);

  n = *(int *)0x5f8cd0;
  for (i = 0; i < n; i++) {
    FUN_00189860(
        1,
        (void *)(0x5f8cd4 + i * 12),
        (void *)(0x5f8d94 + i * 12),
        *(float *)(0x5f8e54 + i * 4),
        *(void **)0x2ee6d8);
  }

  limit = *(int *)0x5f8e94 - 1;
  for (i = 0; i < limit; i++) {
    if (*(char *)0x5f8cb5)
      color = *(void **)0x2ee6d4;
    else if (i == *(int *)0x5f8e94 - 2)
      color = *(void **)0x2ee6f0;
    else
      color = *(void **)0x2ee6d0;
    FUN_00189270(
        1,
        (float *)(0x5f8e98 + i * 12),
        (float *)(0x5f8ea4 + i * 12),
        color);
  }
}


/* ai_debug_highlight_cluster (0x496c0) — readable C lift. */
char ai_debug_highlight_cluster(int16_t index, void *out_color)
{
  int now;
  int encounter;
  char *enc;
  int bit;
  int word;

  if (*(unsigned char *)0x5aca6c == 0)
    return 0;
  if (*(int *)0x5ac9f4 == -1)
    return 0;
  now = game_time_get();
  encounter = *(int *)0x5ac9f4;
  if (*(int *)0x2c8e90 != now || *(int *)0x2c8e8c != encounter) {
    FUN_00058fd0(encounter, 0, 0x200, 0, (void *)0x331f18);
    *(int *)0x2c8e90 = game_time_get();
    *(int *)0x2c8e8c = *(int *)0x5ac9f4;
    encounter = *(int *)0x5ac9f4;
  }
  if (out_color == 0) {
    display_assert((const char *)0x25abec, (const char *)0x25ab74, 0x1025, 1);
    system_exit(-1);
    encounter = *(int *)0x5ac9f4;
  }
  word = (int)index;
  bit = 1 << (word & 0x1f);
  if ((*(int *)(0x331f18 + (word >> 5) * 4) & bit) != 0) {
    enc = (char *)datum_get(*(data_t **)0x5ab270, encounter);
    if (enc[0xd] != 0)
      *(int *)out_color = *(int *)0x2ee6e0;
    else
      *(int *)out_color = *(int *)0x2ee6d8;
    return 1;
  }
  *(int *)out_color = *(int *)0x2ee6c8;
  return 1;
}



/* FUN_000497c0 (0x497c0) — readable C lift. */
int16_t FUN_000497c0(float *pos, int16_t key)
{
  int count;
  int i;
  float *pt;
  float dx, dy, dz, d2;

  count = *(int *)0x5accac;
  for (i = 0; i < count; i++) {
    if (*(short *)(0x5e4cb0 + i * 2) != key)
      continue;
    pt = (float *)(0x5accb0 + i * 12);
    dx = pt[0] - pos[0];
    dy = pt[1] - pos[1];
    dz = pt[2] - pos[2];
    d2 = dx * dx + dy * dy + dz * dz;
    if (d2 < *(float *)0x25ac64)
      break;
  }

  if (i >= count) {
    if (count >= 0x4000) {
      if (!*(char *)0x5acca8) {
        error(2, (const char *)0x25ac00, 0x4000, *(int *)0x5eccb0);
        *(char *)0x5acca8 = 1;
      }
      return -1;
    }
    i = count;
    *(int *)0x5accac = count + 1;
    pt = (float *)(0x5accb0 + i * 12);
    pt[0] = pos[0];
    pt[1] = pos[1];
    pt[2] = pos[2];
    *(short *)(0x5dccb0 + i * 2) = 0;
    *(short *)(0x5e4cb0 + i * 2) = key;
  }

  if (i == -1)
    return -1;
  if (i > 0x7fff) {
    display_assert((const char *)0x25ac50, (const char *)0x25ab74, 0x107f, true);
    system_exit(-1);
  }
  (*(short *)(0x5dccb0 + i * 2))++;
  return (int16_t)i;
}


/* FUN_000498d0 (0x498d0) — readable C lift. */
int FUN_000498d0(int16_t a, int16_t b)
{
  int count;
  int i;
  short *entry;

  if (a == -1 || b == -1)
    return -1;

  count = *(int *)0x5eccb0;
  for (i = 0; i < count; i++) {
    entry = (short *)(0x5eccb4 + i * 6);
    if (entry[0] == a && entry[1] == b)
      break;
  }

  if (i >= count) {
    if (count >= 0x2000) {
      if (!*(char *)0x5acca8) {
        error(2, (const char *)0x25ac68, 0x2000, *(int *)0x5accac);
        *(char *)0x5acca8 = 1;
      }
      return -1;
    }
    i = count;
    *(int *)0x5eccb0 = count + 1;
    entry = (short *)(0x5eccb4 + i * 6);
    entry[0] = a;
    entry[1] = b;
    entry[2] = 0;
  }

  if (i == -1)
    return -1;
  entry = (short *)(0x5eccb4 + i * 6);
  entry[2]++;
  return i;
}


/* FUN_00049990 (0x49990) — readable C lift. */
void FUN_00049990(void)
{
  int color_ptrs[13];
  int count;
  int i;
  int idx;
  char *pos;
  short *edge;

  color_ptrs[0] = 0x2ee6cc;
  color_ptrs[1] = 0x2ee6d8;
  color_ptrs[2] = 0x2ee6ec;
  color_ptrs[3] = 0x2ee6dc;
  color_ptrs[4] = 0x2ee6d4;
  color_ptrs[5] = 0x2ee6f4;
  color_ptrs[6] = 0x2ee700;
  color_ptrs[7] = 0x2ee6e8;
  color_ptrs[8] = 0x2ee6e4;
  color_ptrs[9] = 0x2ee6d0;
  color_ptrs[10] = 0x2ee6f0;
  color_ptrs[11] = 0x2ee6e0;
  color_ptrs[12] = 0x2ee6c4;

  count = *(int *)0x5accac;
  if (count > 0) {
    pos = (char *)0x5accb0;
    for (i = 0; i < count; i++) {
      idx = *(short *)(0x5dccb0 + i * 2);
      crt_sprintf((char *)0x5ab100, (const char *)0x25acb8, idx);
      idx = *(short *)(0x5dccb0 + i * 2);
      if (idx > 0xc)
        idx = 0xc;
      FUN_00189cb0(1, pos, (void *)0x5ab100, *(int *)color_ptrs[idx]);
      pos += 0xc;
    }
  }

  count = *(int *)0x5eccb0;
  if (count > 0) {
    edge = (short *)0x5eccb4;
    for (i = 0; i < count; i++) {
      idx = edge[2];
      if (idx > 0xc)
        idx = 0xc;
      FUN_00189270(
          1,
          (float *)(0x5accb0 + (int)edge[0] * 12),
          (float *)(0x5accb0 + (int)edge[1] * 12),
          (void *)(uintptr_t)*(int *)color_ptrs[idx]);
      edge += 3;
    }
  }
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

/* FUN_00049c70 (0x49c70) — readable C lift.
 * Ray from local camera; return actor handle under crosshair, or -1. */
int FUN_00049c70(void)
{
  void *camera;
  int actor;
  int unit_handle;
  int16_t perspective;
  float dir[3];
  char hit[0x50];
  char *obj;
  int object_handle;
  int parent_handle;

  actor = -1;
  camera = observer_get_camera(0);
  if (camera == NULL)
    return actor;

  unit_handle = -1;
  perspective = director_get_perspective(0);
  if (perspective == 0) {
    int player_index;
    char *player;
    player_index = local_player_get_player_index(0);
    player = (char *)datum_get(*(data_t **)0x5aa6d4, player_index);
    unit_handle = *(int *)(player + 0x34);
  }

  dir[0] = *(float *)((char *)camera + 0x20) * *(float *)0x25acf0;
  dir[1] = *(float *)((char *)camera + 0x24) * *(float *)0x25acf0;
  dir[2] = *(float *)((char *)camera + 0x28) * *(float *)0x25acf0;

  if (!FUN_0014df70(0x81, (float *)camera, dir, unit_handle, (short *)hit))
    return actor;
  if (*(int16_t *)hit != 3)
    return actor;

  object_handle = *(int *)(hit + 0x38);
  if (object_handle == -1)
    return actor;

  obj = (char *)object_try_and_get_and_verify_type(object_handle, 3);
  if (obj == NULL)
    return actor;

  actor = *(int *)(obj + 0x1a8);
  if (actor == -1)
    actor = *(int *)(obj + 0x1a4);
  if (actor != -1)
    return actor;

  parent_handle = *(int *)(obj + 0x2d4);
  if (parent_handle == -1)
    return -1;

  obj = (char *)object_get_and_verify_type(parent_handle, 3);
  actor = *(int *)(obj + 0x1a8);
  if (actor == -1)
    actor = *(int *)(obj + 0x1a4);
  return actor;
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


/* ai_debug_vocalize (0x49f60) — readable C lift. */
void ai_debug_vocalize(int a0, int a1)
{
  char *actor;
  short voc_id;
  short sound_id;
  short count;
  int sound_def;
  short voc_type;
  char packet[0x30];
  int actor_handle;

  actor_handle = *(int *)0x5ac9f8;
  if (actor_handle == -1)
    return;
  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  *(char *)0x5aca89 = 1;
  if (*(int *)(actor + 0x18) == -1)
    return;
  voc_id = FUN_001a6cd0((const char *)a0);
  sound_id = FUN_001a67e0((const char *)a1);
  if (voc_id <= 0 || sound_id == (short)-1)
    return;
  voc_type = sound_id;
  sound_def = -1;
  count = FUN_001a68d0(*(int *)(actor + 0x18), voc_id, 1, 1, 0, &voc_type, &sound_def);
  if (count == 0)
    return;
  csmemset(packet, 0, 0x30);
  *(short *)(packet + 0) = voc_id;
  *(short *)(packet + 2) = voc_type;
  *(int *)(packet + 4) = sound_def;
  ai_communication_packet_new(packet + 0x10);
  FUN_001a6ef0(*(int *)(actor + 0x18), count, packet);
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


/* ai_debug_speak (0x4a220) — readable C lift. */
void ai_debug_speak(const char *name)
{
  char *actor;
  int16_t sound_idx;

  if (*(int *)0x5ac9f8 == -1)
    return;
  actor = (char *)datum_get(*(void **)0x6325a4, *(int *)0x5ac9f8);
  sound_idx = FUN_001a67e0(name);
  if (*(int *)(actor + 0x18) == -1)
    return;
  if (sound_idx == (int16_t)0xffff)
    return;
  *(uint8_t *)0x5aca89 = 1;
  *(uint8_t *)0x6324e0 = 1;
  *(uint16_t *)0x6324e8 = 0;
  *(uint8_t *)0x6324e1 = 0;
  *(int *)0x6324e4 = *(int *)(actor + 0x18);
  *(int16_t *)0x6324ea = sound_idx;
}

/* ai_debug_speak_list (0x4a290) — readable C lift. */
void ai_debug_speak_list(int name)
{
  struct {
    const char *str;
    int16_t code;
    char flag;
  } entries[15];
  unsigned char *actor;
  int handle;
  int i;
  char matched;

  handle = *(int *)0x5ac9f8;
  if (handle == -1)
    return;

  entries[0].str = (const char *)0x25ae38;
  entries[0].code = 0;
  entries[0].flag = 1;
  entries[1].str = (const char *)0x25ae30;
  entries[1].code = 0;
  entries[1].flag = 0;
  entries[2].str = (const char *)0x25ae24;
  entries[2].code = 6;
  entries[2].flag = 0;
  entries[3].str = (const char *)0x25ae14;
  entries[3].code = 0x15;
  entries[3].flag = 0;
  entries[4].str = (const char *)0x25ae08;
  entries[4].code = 0x1d;
  entries[4].flag = 0;
  entries[5].str = (const char *)0x25adf8;
  entries[5].code = 0x31;
  entries[5].flag = 0;
  entries[6].str = (const char *)0x25ade0;
  entries[6].code = 0x50;
  entries[6].flag = 0;
  entries[7].str = (const char *)0x25add0;
  entries[7].code = 0x60;
  entries[7].flag = 0;
  entries[8].str = (const char *)0x25adc4;
  entries[8].code = 0x6c;
  entries[8].flag = 0;
  entries[9].str = (const char *)0x25adb0;
  entries[9].code = 0x7b;
  entries[9].flag = 0;
  entries[10].str = (const char *)0x25ada8;
  entries[10].code = 0x94;
  entries[10].flag = 0;
  entries[11].str = (const char *)0x25ad98;
  entries[11].code = 0xb1;
  entries[11].flag = 0;
  entries[12].str = (const char *)0x25ad84;
  entries[12].code = 0xbc;
  entries[12].flag = 0;
  entries[13].str = (const char *)0x25ad70;
  entries[13].code = 0xc5;
  entries[13].flag = 0;
  entries[14].str = 0;
  entries[14].code = -1;
  entries[14].flag = 0;

  actor = (unsigned char *)datum_get(*(void **)0x6325a4, handle);
  matched = 0;
  for (i = 0; entries[i].str != 0; i++) {
    if (crt_stricmp((const char *)name, entries[i].str) == 0) {
      matched = 1;
      break;
    }
  }
  if (!matched || entries[i].str == 0) {
    console_printf(0, (const char *)0x25ad28, name);
    for (i = 0; entries[i].str != 0; i++)
      console_printf(0, (const char *)0x25ad1c, entries[i].str);
    return;
  }
  if (*(int *)(actor + 0x18) == -1 || entries[i].code == -1)
    return;
  *(char *)0x5aca89 = 1;
  *(char *)0x6324e0 = 1;
  *(short *)0x6324e8 = 0;
  *(char *)0x6324e1 = 1;
  *(char *)0x6324e2 = entries[i].flag;
  *(int *)0x6324e4 = *(int *)(actor + 0x18);
  *(short *)0x6324ea = entries[i].code;
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


/* FUN_0004a8c0 (0x4a8c0) — readable C lift.
 * Draw AI communication debug markers for the active ring buffer. */
void FUN_0004a8c0(void)
{
  int now;
  void *globals;
  unsigned int idx;
  char *entry;
  int16_t kind;
  int color;
  float pos[3];
  float *up;
  char *buf;
  int age;

  now = game_time_get();
  globals = *(void **)0x632574;
  idx = *(uint16_t *)((char *)globals + 0x130);
  if ((uint16_t)idx == *(uint16_t *)((char *)globals + 0x132))
    return;

  do {
    entry = (char *)globals + 0x134 + (int)(int16_t)idx * 20;
    kind = *(int16_t *)entry;
    if (kind != (int16_t)0xffff) {
      color = *(int *)0x2ee6c4;
      if (kind >= 0 && kind < 3) {
        int *colors[3];
        colors[0] = (int *)0x2ee6d8;
        colors[1] = (int *)0x2ee6e0;
        colors[2] = (int *)0x2ee6d0;
        color = *colors[kind];
      }
      FUN_00189540(1, entry + 4, 0.2f, (void *)color);
      up = *(float **)0x31fc44;
      pos[0] = up[0] * *(float *)0x2533e4 + *(float *)(entry + 4);
      pos[1] = up[1] * *(float *)0x2533e4 + *(float *)(entry + 8);
      pos[2] = up[2] * *(float *)0x2533e4 + *(float *)(entry + 12);
      age = now - *(int *)(entry + 0x10);
      buf = csprintf((char *)0x5ab100, (const char *)0x25aed0,
                     (int)*(int16_t *)(entry + 2), age);
      FUN_00189cb0(1, pos, buf, color);
      globals = *(void **)0x632574;
    }
    idx = (idx + 1) & 0x1f;
  } while ((uint16_t)idx != *(uint16_t *)((char *)globals + 0x132));
}



/* FUN_0004a9f0 (0x4a9f0) — readable C lift. */
void FUN_0004a9f0(void)
{
  char *base;
  char *a;
  char *b;
  int i;
  int j;
  float dx, dy, dz, dist_sq;

  base = *(char **)0x331f5c;
  for (i = 0; i < 0x20; i++) {
    a = base + i * 0x1ca7c;
    if (a[0xc] == 0 || a[0xd] == 0)
      continue;
    for (j = i + 1; j < 0x20; j++) {
      b = base + j * 0x1ca7c;
      if (b[0xc] == 0 || b[0xd] == 0)
        continue;
      if (*(int *)b != *(int *)a)
        continue;
      dx = *(float *)(b + 0x28) - *(float *)(a + 0x28);
      dy = *(float *)(b + 0x2c) - *(float *)(a + 0x2c);
      dz = *(float *)(b + 0x30) - *(float *)(a + 0x30);
      dist_sq = dx * dx + dy * dy + dz * dz;
      if (!(dist_sq < *(float *)0x25337c))
        continue;
      if (a[0x60] != b[0x60])
        continue;
      if (a[0x60] != 0) {
        dist_sq = distance_squared3d((float *)(a + 0x64), (float *)(b + 0x64));
        if (!(dist_sq < *(float *)0x25337c))
          continue;
      }
      if (*(int *)(a + 4) < *(int *)(b + 4)) {
        a[0xc] = 0;
        break;
      }
      b[0xc] = 0;
    }
  }
}

#include "../../x87_math.h"

/* ai_debug_teleport_to (0x4b0f0) — readable C lift. */
void ai_debug_teleport_to(int actor_index)
{
  data_iter_t iter;
  char *squad;
  char *starting;
  char *player;
  int16_t n;
  float forward[3];

  if (actor_index == -1)
    return;
  squad = (char *)tag_block_get_element(
      (char *)global_scenario_get() + 0x42c, actor_index & 0xffff, 0xb0);
  starting = squad + 0xa4;
  if (*(int *)starting <= 0)
    return;
  data_iterator_new(&iter, *(data_t **)0x5aa6d4);
  n = 0;
  for (player = (char *)data_iterator_next(&iter); player;
       player = (char *)data_iterator_next(&iter)) {
    int obj = *(int *)(player + 0x34);
    char *pos;
    float yaw;
    if (obj == -1)
      continue;
    pos = (char *)tag_block_get_element(starting, (int)n % *(int *)starting, 0x34);
    yaw = *(float *)(pos + 0xc);
    forward[0] = x87_fcos(yaw);
    forward[1] = x87_fsin(yaw);
    forward[2] = 0.0f;
    object_set_position(obj, (float *)pos, forward, 0);
    n = (int16_t)(n + 1);
  }
}



/* FUN_0004b220 (0x4b220) — readable C lift.
 * point arrives in EAX (kb: @<eax>); cdecl param matches harness. */
void FUN_0004b220(float *point)
{
  float *cam;
  float dx, dy, dz;

  cam = (float *)observer_get_camera(0);
  *(float *)0x5ac9a0 = point[0];
  *(float *)0x5ac9a4 = point[1];
  *(float *)0x5ac9a8 = point[2];
  *(float *)0x5ac9b8 = point[2];
  *(float *)0x5ac9b0 = point[0];
  *(float *)0x5ac9b4 = point[1];
  if (!cam) {
    *(float *)0x5ac990 = 0.05f; /* 0x3d4ccccd */
    return;
  }
  dx = cam[0] - point[0];
  dy = cam[1] - point[1];
  dz = cam[2] - point[2];
  *(float *)0x5ac990 = __builtin_sqrtf(dx * dx + dy * dy + dz * dz) * *(float *)0x25afc0;
}
/* FUN_0004b2b0 (0x4b2b0) — readable C lift: advance debug point by dt*vel. */
float *FUN_0004b2b0(void)
{
  float *vel;
  float dt;

  *(float *)0x5ac9a0 = *(float *)0x5ac9b0;
  *(float *)0x5ac9a4 = *(float *)0x5ac9b4;
  *(float *)0x5ac9a8 = *(float *)0x5ac9b8;
  vel = *(float **)0x31fc44;
  dt = *(float *)0x5ac990;
  *(float *)0x5ac9b0 = dt * vel[0] + *(float *)0x5ac9b0;
  *(float *)0x5ac9b4 = dt * vel[1] + *(float *)0x5ac9a4;
  *(float *)0x5ac9b8 = dt * vel[2] + *(float *)0x5ac9a8;
  return (float *)0x5ac9a0;
}

/* FUN_0004b320 (0x4b320) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))FUN_00049300)();
  /* test eax, eax -> je 0x4b4ad */
  csprintf((char *)0x005ab100, (char *)0x0025afc4);
  FUN_00189cb0(0, (void *)(uintptr_t)edx, (void *)(uintptr_t)eax, 0);
  /* test eax, eax -> je 0x4b590 */
  FUN_00189150(0, (float *)(uintptr_t)eax, 0.0f, (void *)(uintptr_t)ecx);
  csprintf((char *)0x005ab100, (char *)0x0025afc4);
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)(uintptr_t)eax, 0);
  /* test ebx, ebx -> je 0x4b667 */
  /* test (char)eax, (char)eax -> je 0x4b667 */
  /* relift: path_attractor_weight(...) */
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


/* FUN_0004b670 (0x4b670) — readable C lift.
 * ABI: unit_handle@<edi>, color@<ebx>, flag.
 * Debug-draw camera/aim volume for a unit. */
void FUN_0004b670(int unit_handle, void *color, char flag)
{
  char *obj;
  char *parent;
  float center[3];
  float radius;
  float height;
  float height_vec[3];

  obj = (char *)object_try_and_get_and_verify_type(unit_handle, 1);
  if (obj == NULL)
    return;

  parent = (char *)object_try_and_get_and_verify_type(*(int *)(obj + 0xcc), 3);
  if (parent != NULL && *(int *)(parent + 0x2d4) == unit_handle) {
    FUN_0001aae0(*(int *)(obj + 0xcc), center, &radius);
    height = 0.0f;
  } else {
    biped_get_camera_height_and_offset(unit_handle, (vector3_t *)center, &height,
                                       &radius);
  }

  if (flag && !(height <= *(float *)0x2533c0)) {
    height_vec[0] = 0.0f;
    height_vec[1] = 0.0f;
    height_vec[2] = height;
    FUN_00189860(1, center, height_vec, radius, (void *)color);
  } else {
    FUN_00189540(1, center, radius * *(float *)0x25afcc, (void *)color);
  }

  if (flag)
    FUN_00189150(1, center, radius * *(float *)0x255154, (void *)color);
}



/* ai_debug_lineofsight (0x4b770) — readable C lift. */
void ai_debug_lineofsight(float *pos_a, int16_t key_a, float *pos_b, int16_t key_b)
{
  int16_t idx_b = FUN_000497c0(pos_b, key_b);
  int16_t idx_a = FUN_000497c0(pos_a, key_a);
  FUN_000498d0(idx_a, idx_b);
}

/* FUN_0004b7a0 (0x4b7a0) — readable C lift. */
void FUN_0004b7a0(void)
{
  int actor_handle;
  char *actor;

  actor_handle = ((int (*)(void))(void *)&FUN_00049c70)();
  if (actor_handle == -1) {
    return;
  }
  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  ai_debug_describe_actor(actor_handle, -1, 1, (char *)0x5ab100, 0x100);
  console_printf(0, (const char *)0x25afd0, (char *)0x5ab100);
  ai_debug_select_actor(*(int *)(actor + 0x34), actor_handle);
  *(char *)0x5ac9c1 = 0;
}

/* FUN_0004b810 (0x4b810) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))FUN_0004b220)();
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
  FUN_0004b220((float *)0);
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


/* FUN_0004c2a0 (0x4c2a0) — readable C lift (restored pre-naked). */
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


/* FUN_0004c560 (0x4c560) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))FUN_00049300)();
  FUN_0004b2b0();
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x4c77c */
  ((void(*)(void))FUN_00049280)();
  /* test (char)eax, (char)eax -> je 0x4c7a7 */
  ((void(*)(void))FUN_00049280)();
  /* test (char)eax, (char)eax -> je 0x4c7d2 */
  ((void(*)(void))FUN_00049280)();
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


/* FUN_0004c890 (0x4c890) — readable C lift. */
void FUN_0004c890(void)
{
  void *color;

  if (*(char *)0x5f91a8 != 0 && *(char *)0x5f91c0 != 0 && *(char *)0x60d268 == 0) {
    if (*(char *)0x5ac9ff == 0 && *(char *)0x5f9228 == 0) {
      color = *(void **)0x2ee6d8;
    } else if (*(short *)0x5f925c == 0) {
      color = *(void **)0x2ee6d4;
    } else if (*(short *)0x5f925c >= 0x400) {
      color = *(void **)0x2ee6e0;
    } else {
      color = *(void **)0x2ee6e8;
    }
    FUN_00189270(1, (float *)0x5f91ac, (float *)0x5f91c4, color);
  }
  if (*(char *)0x60d2d0 != 0) {
    FUN_0004b220((float *)0x60d2ec);
    __asm__ volatile("movl %0, %%esi" : : "r"((void *)0x60d2c4) : "esi");
    FUN_0004c560();
  }
}

/* FUN_0004c920 (0x4c920) — readable C lift (restored pre-naked). */
void FUN_0004c920(int actor_handle, char debug_selected, void *debug_context)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  (void)debug_selected;
  (void)debug_context;

  datum_get((void *)(uintptr_t)eax, 0);
  tag_get('rtca', 0);
  tag_get('vtca', 0);
  ((void(*)(void))FUN_000490C0)();
  object_get_and_verify_type(0, 0);
  tag_get('tinu', 0);
  /* test edi, edi -> je 0x4ca0a */
  /* relift: cmp word ptr [esi + 0x6e], 2 -> jl 0x4ca0a */
  /* cmp eax, -1 -> je 0x4ca0a */
  datum_get((void *)(uintptr_t)eax, 0);
  /* cmp ecx, -1 -> je 0x4ca05 */
  /* relift: cmp dword ptr [eax + 0x7c], ecx -> jge 0x4ca0a */
  ((void(*)(void))FUN_0004b220)();
  /* test (char)eax, (char)eax -> je 0x4cac4 */
  /* cmp eax, -1 -> je 0x4cade */
  datum_get((void *)(uintptr_t)edx, 0);
  actor_action_debug_color(0);
  ((void(*)(void))FUN_0004b670)();
  actor_action_debug_color(0);
  ((void(*)(void))FUN_0004b670)();
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
  ((void(*)(void))FUN_00049300)();
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
  actor_get_pursuit_location(actor_handle);
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
  actor_get_pursuit_location(actor_handle);
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


/* FUN_00052ab0 (0x52ab0) — readable C lift. */
void FUN_00052ab0(void)
{
  int i;
  char *slot;
  float pos[3];
  char buf[0x100];
  char *base;
  float *cam;
  void *color;
  float *drawn;

  base = *(char **)0x331f5c;
  for (i = 0; i < 0x20; i++) {
    slot = base + i * 0x1ca7c;
    if (slot[0xc] == 0 || slot[0xd] == 0) {
      continue;
    }
    cam = *(float **)0x31fc44;
    pos[0] = cam[0] + *(float *)(slot + 0x28);
    pos[1] = cam[1] + *(float *)(slot + 0x2c);
    pos[2] = cam[2] + *(float *)(slot + 0x30);
    FUN_0004b220(pos);
    ai_debug_describe_actor(*(int *)slot, -1, 1, buf, 0x100);
    color = *(void **)0x2ee6d0;
    drawn = FUN_0004b2b0();
    FUN_00189cb0(1, drawn, buf, (int)(uintptr_t)color);
    FUN_0004c560();
  }
}

/* FUN_00052b60 (0x52b60) — readable C lift. */
void FUN_00052b60(char reverse_iteration)
{
  char iter[0x1c];
  int actor;
  char selected;

  encounter_iterator_next(iter, (char)(reverse_iteration == 0));
  while (FUN_00059b50(iter)) {
    actor = *(int *)(iter + 0x14);
    selected = (char)(actor == *(int *)0x5ac9f8);
    FUN_0004c920(actor, selected, 0);
  }
}

/* FUN_00052bb0 (0x52bb0) — readable C lift (restored pre-naked). */
void FUN_00052bb0(int clump_handle)
{
  int actor_iter[0xe];
  int actor_handle;
  char debug_selected;
  char debug_context;

  encounter_actor_iterator_new(actor_iter, clump_handle);
  while (encounter_actor_iterator_next(actor_iter) != 0) {
    actor_handle = *(int *)((char *)actor_iter + 0x34);
    debug_selected = (char)(actor_handle == *(int *)0x5ac9f8);
    if (!debug_selected && *(int *)0x5ac9f8 != -1 &&
        *(char *)0x5aca66 == 0)
      continue;
    debug_context = debug_selected;
    FUN_0004c920(actor_handle, debug_selected, &debug_context);
  }
}


/* FUN_000534d0 (0x534d0) — readable C lift. */
void FUN_000534d0(void)
{
  unsigned char *ai_globals;
  unsigned char *actor;
  int handle;
  int rem;

  ai_globals = *(unsigned char **)0x632574;
  if (!ai_globals[1])
    return;

  *(int16_t *)0x5ac98c = (int16_t)(*(int *)0x325660 - 0x14);
  rem = (*(int *)0x5acab4 + 1) % 1000;
  if (rem < 0)
    rem += 1000;
  *(int *)0x5acab4 = rem;

  handle = *(int *)0x5ac9f8;
  if (handle != -1) {
    actor = (unsigned char *)datum_get(*(void **)0x6325a4, handle);
    *(int *)0x5ac9f4 = *(int *)(actor + 0x34);
  }
  if (*(char *)0x5ac9c1)
    FUN_0004b7a0();
  if (!*(char *)0x5aca65)
    return;
  if (*(char *)0x5aca69)
    FUN_000494e0();
  if (*(char *)0x5aca6a)
    FUN_00049990();
  if (*(char *)0x5aca6b)
    FUN_000495b0();
  if (*(int *)0x5ac9f4 != -1)
    FUN_00052bb0(*(int *)0x5ac9f4);
  if (*(int *)0x5ac9f8 != -1)
    FUN_0004c920(*(int *)0x5ac9f8, 1, 0);
  if (*(char *)0x5ac9fc)
    FUN_0004c890();
  if (*(char *)0x5aca9b)
    FUN_00052ab0();
  if (*(char *)0x5aca88)
    FUN_00049d60();
  if (*(char *)0x5aca66)
    FUN_00052b60(*(char *)0x5aca67);
  if (*(char *)0x5aca89 || *(char *)0x5aca53 || *(char *)0x5aca93)
    FUN_0004b810();
  if (*(char *)0x5aca76)
    FUN_0004a770();
  if (*(char *)0x5aca8c)
    FUN_0004a8c0();
  if (*(char *)0x5aca91)
    FUN_0004bc70();
}

/* FUN_00053650 (0x53650) — readable C lift: memset helper. */
void FUN_00053650(void)
{
  csmemset((void *)0x5abaac, 0, 0xee0);
}

/* FUN_00053680 (0x53680) — readable C lift.
 * Advance 28 AI profile ring-buffer slots at 0x5abab8 (stride 0x88). */
void FUN_00053680(void)
{
  int i;
  char *entry;
  char *slot;
  int (*cb)(void);
  int16_t last;
  int16_t count;
  int16_t kept;
  int16_t ring_max;
  int total;
  int quot;
  int rem;

  entry = (char *)0x2c8e9c;
  slot = (char *)0x5abab8;

  for (i = 0; i < 0x1c; i++) {
    if (*(int16_t *)(entry - 4) != (int16_t)i) {
      display_assert((const char *)0x25c08c, (const char *)0x25c0ac, 0x8c,
                     true);
      system_exit(-1);
    }

    cb = *(int (**)(void))entry;
    if (cb != NULL)
      *(int16_t *)(slot - 0xc) = (int16_t)cb();

    last = *(int16_t *)(slot - 0xc);
    *(int16_t *)(slot - 0xa) = last;
    count = *(int16_t *)slot;
    *(int16_t *)(slot - 0xc) = 0;
    if (count < 0 || count >= 0x3c) {
      display_assert((const char *)0x25c030, (const char *)0x25c0ac, 0x97,
                     true);
      system_exit(-1);
    }

    ring_max = *(int16_t *)(slot + 2);
    if (count < ring_max) {
      total = *(int *)(slot - 4);
      total -= (int)*(int16_t *)(slot + 4 + count * 2);
      *(int *)(slot - 4) = total;
    }

    *(int16_t *)(slot + 4 + count * 2) = *(int16_t *)(slot - 0xa);
    count = (int16_t)(count + 1);
    *(int16_t *)slot = count;
    kept = ring_max;
    if (kept <= count)
      kept = count;
    *(int16_t *)(slot + 2) = kept;

    total = *(int *)(slot - 4);
    quot = total / 0x3c;
    rem = total % 0x3c;
    (void)quot;

    entry += 8;
    slot += 0x88;

    *(int16_t *)(slot - 0x88) = (int16_t)rem;
    *(float *)(slot - 0x90) = (float)total / (float)(int)kept;
  }
}




/* FUN_00053790 (0x53790) — readable C lift. */
void FUN_00053790(char *buffer)
{
  int n;
  n = csstrlen(buffer);
  crt_sprintf(buffer + n, (const char *)0x25c0d0,
              (int)*(int16_t *)0x5abb36, (int)*(int16_t *)0x5abaae,
              (int)*(int16_t *)0x5abcce, (int)*(int16_t *)0x5abc46,
              (int)*(int16_t *)0x5abbbe, (int)*(int16_t *)0x5abe66,
              (int)*(int16_t *)0x5abdde, (int)*(int16_t *)0x5abd56,
              (int)*(int16_t *)0x5abeee, 0x300);
}




/* FUN_00053800 (0x53800) — readable C lift. */
void FUN_00053800(void *buffer, int nstops, int16_t *stops, void *color)
{
  int16_t bounds[4];
  int16_t tmp[4];

  bounds[0] = *(int16_t *)0x5aba80;
  bounds[1] = 0;
  bounds[2] = (int16_t)0x7fff;
  bounds[3] = (int16_t)0x7fff;
  if (color == 0)
    color = *(void **)0x2ee6c4;
  interface_draw_text(1, -1, 0, 0, 5, 0);
  draw_string_set_color(color);
  draw_string_set_tab_stops(stops, (short)nstops);
  rasterizer_text_draw(bounds, 0, tmp, 0, (const char *)buffer);
  draw_string_set_tab_stops(0, 0);
  *(int16_t *)0x5aba80 = (int16_t)(*(int16_t *)0x5aba80 + (bounds[0] - tmp[1]));
}



/* FUN_00053890 (0x53890) — readable C lift (ai campaign). */
extern char DAT_0025c120[];
unsigned short FUN_00053890(void)
{
  int v = (int)(*(short *)0x5abaa2) + 1;
  short rem = (short)(v % 3);
  *(short *)0x5abaa2 = rem;
  console_printf(0, DAT_0025c120, *(void **)(0x2c8f78 + (int)rem * 4));
  return *(unsigned short *)0x5abaa2;
}

int16_t FUN_000538d0(void) {
  uint8_t *base = *(uint8_t **)0x5ab270;
  return *(uint16_t *)(base + 0x30);
}



/* FUN_000538f0 (0x538f0) — readable C lift. */
int16_t FUN_000538f0(void)
{
  unsigned char iter[0x1c];
  void *enc;
  int16_t sum = 0;
  encounter_iterator_next(iter, 0);
  for (enc = (void *)FUN_00059b50(iter); enc != 0; enc = (void *)FUN_00059b50(iter)) {
    if (*((char *)enc + 6) != 0)
      sum = (int16_t)(sum + *(int16_t *)((char *)enc + 0x1e));
    else
      sum = (int16_t)(sum + 1);
  }
  return sum;
}

/* FUN_00053960 (0x53960) — readable C lift. */
unsigned short FUN_00053960(void)
{
  unsigned char iter[0x1c];
  void *enc;
  unsigned short sum = 0;

  encounter_iterator_next(iter, 0);
  for (enc = (void *)FUN_00059b50(iter); enc; enc = (void *)FUN_00059b50(iter))
    sum = (unsigned short)(sum + *(unsigned char *)((char *)enc + 6));
  return sum;
}
/* FUN_000539c0 (0x539c0) — readable C lift. */
void FUN_000539c0(void)
{
  int16_t vals[2];
  void *color;
  char *buf;

  vals[0] = 0x96;
  vals[1] = 0x12c;
  buf = (char *)0x5ab280;
  crt_sprintf(
      buf,
      (const char *)0x25c134,
      (int)*(int16_t *)0x5abb36,
      (int)*(int16_t *)0x5abaae,
      (int)*(int16_t *)0x5abeee,
      0x300);
  color = *(void **)0x2ee6c4;
  FUN_00053800(buf, 2, vals, color);
}

/* FUN_00053a20 (0x53a20) — readable C lift. */
void FUN_00053a20(void)
{
  int16_t vals[2];
  void *color;
  char *buf;

  vals[0]=0x96; vals[1]=0x12c;
  buf = (char *)0x5ab280;
  crt_sprintf(buf, (const char *)0x25c154, (int)*(int16_t *)0x5abcce, (int)*(int16_t *)0x5abc46, (int)*(int16_t *)0x5abbbe, (int)*(int16_t *)0x5abe66, (int)*(int16_t *)0x5abdde, (int)*(int16_t *)0x5abd56);
  color = *(void **)0x2ee6c4;
  FUN_00053800(buf, 2, vals, color);
}

/* FUN_00053a90 (0x53a90) — readable C lift (debug overlay row). */
void FUN_00053a90(void)
{
  short column_positions[1];
  char *debug_row = (char *)0x5ab280;
  void *row_ctx = *(void **)0x2ee6c4;
  void (*row_print)(char *, int, short *, void *) =
      (void (*)(char *, int, short *, void *))(void *)FUN_00053800;

  crt_sprintf(debug_row, (const char *)0x25c174,
              (int)*(int16_t *)0x5ac4c6, (int)*(int16_t *)0x5ac43e, 0x20,
              (int)*(int16_t *)0x5ac54e, 0x100);
  column_positions[0] = 0x96;
  row_print(debug_row, 1, column_positions, row_ctx);
}

/* FUN_00053af0 (0x53af0) — readable C lift. */
void FUN_00053af0(void)
{
  int16_t vals[3];
  void *color;
  char *buf;

  vals[0] = 0x96;
  vals[1] = 0x12c;
  vals[2] = 0x1c2;
  buf = (char *)0x5ab280;
  crt_sprintf(
      buf,
      (const char *)0x25c198,
      (int)*(int16_t *)0x5ac10e,
      (int)*(int16_t *)0x5ac196,
      (int)*(int16_t *)0x5ac21e,
      (int)*(int16_t *)0x5ac2a6,
      (int)*(int16_t *)0x5ac32e,
      (int)*(int16_t *)0x5ac3b6,
      (int)*(int16_t *)0x5abf76,
      (int)*(int16_t *)0x5abffe,
      (int)*(int16_t *)0x5ac086);
  color = *(void **)0x2ee6c4;
  FUN_00053800(buf, 3, vals, color);
}

/* --- ai_debug.obj orphan shells (2026-07-26) --- */

/* FUN_0004a460 (0x4a460) — readable C lift. 5th arg = lookup CALLBACK. */
void FUN_0004a460(int count, const char **names, unsigned int *bitvec, int vector_size,
                  int16_t (*lookup)(const char *))
{
  unsigned int local_bits[0x40];
  int matched, missing, i, word_bytes;
  int16_t idx;
  unsigned int bit;
  unsigned int *word;

  matched = 0;
  missing = 0;
  if (lookup == 0) {
    display_assert((const char *)0x25aea4, (const char *)0x25ab74, 0x1353, 1);
    system_exit(-1);
  }
  if ((unsigned)vector_size > 0x800u) {
    display_assert((const char *)0x25ae90, (const char *)0x25ab74, 0x1354, 1);
    system_exit(-1);
  }
  word_bytes = (int)(((unsigned)(vector_size + 0x1f) >> 5) << 2);
  csmemset(local_bits, 0, (unsigned)word_bytes);
  for (i = 0; i < count; i++) {
    idx = lookup(names[i]);
    if (idx == -1) {
      if (csstrcmp(names[i], (const char *)0x25ae38) == 0)
        csmemset(local_bits, -1, (unsigned)word_bytes);
    } else if (idx < 0 || (int)idx >= vector_size) {
      display_assert((const char *)0x25ae60, (const char *)0x25ab74, 0x135d, 1);
      system_exit(-1);
    } else {
      word = &local_bits[(unsigned)idx >> 5];
      bit = 1u << ((unsigned)idx & 0x1f);
      *word |= bit;
    }
  }
  for (i = 0; i < vector_size; i++) {
    bit = 1u << ((unsigned)i & 0x1f);
    word = &local_bits[(unsigned)i >> 5];
    if ((*word & bit) == 0) continue;
    if ((bitvec[(unsigned)i >> 5] & bit) != 0) matched++;
    else missing++;
  }
  if ((int16_t)missing != 0) {
    bit_vector_or((int16_t)vector_size, (int)local_bits, (int)bitvec, (int)bitvec);
    console_printf(0, (const char *)0x25ae50, (int)(int16_t)missing);
    return;
  }
  if ((int16_t)matched != 0) {
    FUN_00108fa0((int16_t)vector_size, (int)local_bits, (int)local_bits);
    bit_vector_and((int16_t)vector_size, (int)local_bits, (int)bitvec, (int)bitvec);
    console_printf(0, (const char *)0x25ae3c, (int)(int16_t)matched);
  }
}

