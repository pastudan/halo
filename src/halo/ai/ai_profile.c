/* ai_profile.c — AI difficulty/profile subsystem.
 *
 * Corresponds to addresses 0x540b0-0x56320 in the XBE (ai_profile.obj TU).
 * Source path confirmed via __FILE__ string @ 0x25c0ac:
 *   c:\halo\SOURCE\ai\ai_profile.c
 *
 * Script-command strings observed:
 *   0x27e61c  "ai_profile_random"
 *   0x27e630  "ai_profile_disable"
 *
 * Functions are lifted incrementally below. Declarations come from the
 * force-included generated header (src/common.h -> build/generated/decl.h).
 */

/* ---------------------------------------------------------------------------
 * Subsystem lifecycle hooks (0x540b0-0x540e0).
 *
 * Each is a single `ret` in the delinked reference (16-byte aligned). The AI
 * profile data lives entirely in the scenario tag, so there is no per-subsystem
 * or per-map allocation to set up or tear down: all four hooks are empty.
 * Mirrors the identical empty quartet in ai_communication.obj
 * (ai_communication_initialize/_dispose/_initialize_for_new_map/
 *  _dispose_from_old_map at 0x42a30/0x42b80/0x42b90/0x42ca0).
 * ------------------------------------------------------------------------- */

/* ai_profile_initialize (0x540b0) — no global state to construct. */
void FUN_000540b0(void)
{
}

/* ai_profile_dispose (0x540c0) — no global state to release. */
void ai_profile_dispose(void)
{
}

/* ai_profile_initialize_for_new_map (0x540d0) — profiles come from the
 * scenario tag, loaded by the tag system; nothing to do per map. */
void FUN_000540d0(void)
{
}

/* ai_profile_dispose_from_old_map (0x540e0) — nothing allocated per map. */
void ai_profile_dispose_from_old_map(void)
{
}

/* ---------------------------------------------------------------------------
 * ai_index_reference: a packed 32-bit handle naming an ai_profile entry in the
 * scenario tag (block at scenario+0x42c, element size 0xb0) plus an optional
 * sub-reference. Bit layout:
 *     bits  0-15 : ai_profile block index
 *     bits 16-23 : sub-index (into element+0x80 [stride 0xe8] or
 *                             element+0x8c [stride 0xac])
 *     bits 30-31 : selector  0=profile only, 1=+0x8c sub, 2=+0x80 sub, 3=error
 * String form is "<profile>" or "<profile>/<sub>"; the keyword "none" maps to
 * the all-ones sentinel (-1). These helpers live in ai_profile.obj but assert
 * against ai_script.c line numbers.
 * ------------------------------------------------------------------------- */

/* FUN_000540f0 — parse a name string ("profile" or "profile/sub") into a
 * packed ai_index_reference. Returns true and writes the packed value (or the
 * -1 sentinel for "none"/not-found) to *out_value; returns false only when the
 * parse fails (name too long, profile/sub not found). 0x40 obj / 0x540f0 XBE.
 * Asserts (ai_script.c:0x57) that name and out_value are non-NULL. */
bool FUN_000540f0(void *scenario, const char *name, int *out_value)
{
  char prefix[32];           /* [ebp-0x24], 0x20 bytes */
  int result;                /* [ebp-0x4], accumulator (starts -1) */
  const char *slash;
  int prefix_index;
  int sub_index;
  int profile_index;

  result = -1;
  if (name == 0 || out_value == 0) {
    display_assert("ai_string && ai_index_reference",
                   "c:\\halo\\SOURCE\\ai\\ai_script.c", 0x57, 1);
    system_exit(-1);
  }

  /* "none" -> success with the -1 sentinel */
  if (crt_stricmp(name, (const char *)0x254384) == 0) {
    *out_value = -1;
    return 1;
  }

  slash = strrchr(name, '/');
  if (slash == 0) {
    /* no '/': whole name is a profile name */
    profile_index = FUN_00053e20(scenario, name);
    if (profile_index != -1) {
      result = profile_index & 0xffff;
    }
  } else {
    int len = (int)(slash - name);
    if (len <= 0x1f) {
      void *element;

      csstrncpy(prefix, name, len);
      prefix[len] = '\0';
      prefix_index = FUN_00053e20(scenario, prefix);
      if (prefix_index != -1) {
        /* fetch the ai_profile element, then resolve the part after '/' */
        element = tag_block_get_element((char *)scenario + 0x42c,
                                        prefix_index, 0xb0);
        sub_index = FUN_00053e80(element, slash + 1);
        if (sub_index != -1) {
          /* selector 2: element+0x80 sub-block */
          result = (((sub_index & 0xff) | 0xffff8000) << 16)
                   | (prefix_index & 0xffff);
        } else {
          sub_index = FUN_00053ee0(element, slash + 1);
          if (sub_index != -1) {
            /* selector 1: element+0x8c sub-block */
            result = (((sub_index & 0xff) | 0x4000) << 16)
                     | (prefix_index & 0xffff);
          }
        }
      }
    }
  }

  *out_value = result;
  return result != -1;
}

/* FUN_00054220 — format a packed ai_index_reference back into its name string
 * ("profile", "profile/sub", "none", or "<error>"). Writes at most
 * buffer_size bytes. 0x170 obj / 0x54220 XBE. */
void FUN_00054220(unsigned int combined_index, void *scenario,
                  char *buffer, int buffer_size)
{
  void *element;
  unsigned int selector;
  unsigned char sub_index;

  if (combined_index == 0xffffffff) {
    csstrncpy(buffer, (const char *)0x254384, buffer_size);
    return;
  }

  element = tag_block_get_element((char *)scenario + 0x42c,
                                  combined_index & 0xffff, 0xb0);
  selector = combined_index >> 0x1e;
  sub_index = (unsigned char)(combined_index >> 16);

  /* NOTE: a switch (not an if-else-if cascade) is required to match MSVC's
   * CMP-chain selector dispatch; clang lowers the equivalent if-else-if to a
   * DEC-chain (sub/dec/dec), costing ~10pp VC71. See lift-learnings.md §19. */
  switch (selector) {
  case 0:
    /* profile name only */
    snprintf(buffer, buffer_size, (const char *)0x257984, element);
    return;
  case 1: {
    /* profile + element+0x8c sub-block (stride 0xac) */
    void *sub = tag_block_get_element((char *)element + 0x8c, sub_index, 0xac);
    snprintf(buffer, buffer_size, (const char *)0x253d30, element, sub);
    return;
  }
  case 2: {
    /* profile + element+0x80 sub-block (stride 0xe8) */
    void *sub = tag_block_get_element((char *)element + 0x80, sub_index, 0xe8);
    snprintf(buffer, buffer_size, (const char *)0x253d30, element, sub);
    return;
  }
  default:
    /* selector 3: invalid */
    csstrncpy(buffer, (const char *)0x253b58, buffer_size);
  }
}

/* FUN_00054310 — decode a packed ai_index_reference into the 3-int iterator
 * record out[0..2]: out[0]=profile index, out[1]=sub-key, out[2]=sub-bound.
 * On any invalid input out[0] is set to -1. 0x260 obj / 0x54310 XBE.
 * Asserts (ai_script.c:0xbf) that out is non-NULL. */
void FUN_00054310(unsigned int combined_index, int *out)
{
  void *ai_globals;
  void *element;
  int profile_index;
  unsigned int selector;
  int sub_index;

  ai_globals = FUN_0018e3b0();
  if (out == 0) {
    display_assert("iterator", "c:\\halo\\SOURCE\\ai\\ai_script.c", 0xbf, 1);
    system_exit(-1);
  }

  profile_index = combined_index & 0xffff;
  out[0] = profile_index;

  if (ai_globals == 0
      || *(char *)((char *)*(void **)0x632574 + 1) == 0
      || profile_index < 0
      || profile_index >= *(int *)((char *)ai_globals + 0x42c)) {
    out[0] = -1;
    return;
  }

  element = tag_block_get_element((char *)global_scenario_get() + 0x42c,
                                  profile_index & 0xffff, 0xb0);
  selector = combined_index >> 0x1e;

  switch (selector) {
  case 0:
    out[1] = 0;
    out[2] = *(int *)((char *)element + 0x8c) - 1;
    return;

  case 1:
  case 2:
    sub_index = (int)(unsigned char)(combined_index >> 16);
    if (selector == 2) {
      if (sub_index < 0 || sub_index >= *(int *)((char *)element + 0x80)) {
        out[1] = -1;
      } else {
        void *sub = tag_block_get_element((char *)element + 0x80,
                                          sub_index, 0xe8);
        out[1] = *(short *)((char *)sub + 0x22);
      }
    } else {
      out[1] = sub_index;
    }
    break;

  default:
    out[0] = -1;
    return;
  }

  if (out[1] < 0 || out[1] >= *(int *)((char *)element + 0x8c)) {
    out[0] = -1;
    return;
  }
  out[2] = out[1];
}

/* FUN_00054430 — iterator step over the encounters named by an
 * ai_index_reference record (the out[3] produced by FUN_00054310). Returns the
 * current encounter's squad pointer and advances out[1]; returns NULL when the
 * record is exhausted (out[0]==-1 or out[1]>out[2]). 0x380 obj / 0x54430 XBE.
 * Asserts (ai_script.c:0x109) that iter is non-NULL. */
void *FUN_00054430(int *iter)
{
  void *result;
  char *encounter;
  int handle;

  result = 0;

  if (iter == 0) {
    display_assert("iterator", "c:\\halo\\SOURCE\\ai\\ai_script.c", 0x109, 1);
    system_exit(-1);
  }

  handle = iter[0];
  if (handle != -1 && iter[1] <= iter[2]) {
    encounter = (char *)datum_get(*(data_t **)0x5ab270, handle);
    encounter = FUN_00054020(encounter, (short)(unsigned short)iter[1]);
    iter[1] = iter[1] + 1;
    result = encounter;
  }

  return result;
}

/* ---------------------------------------------------------------------------
 * ai_index_reference iterators. Two record layouts:
 *   Layout A (encounter/squad iterator, FUN_000544a0 begin / FUN_000545a0 next),
 *     5 ints: [0]=profile index, [1]=encounter-key filter (-1=wildcard),
 *     [2]=cursor scratch, [3]=loop cursor, [4]=loop bound (inclusive).
 *   Layout B (actor iterator, FUN_00054680 begin / FUN_00054750 next), 6 ints:
 *     [0]=clump handle, [1]=squad filter (-1=wildcard), [2]=platoon filter
 *     (-1=wildcard), [3..5]=embedded encounter_actor_iterator state.
 * ------------------------------------------------------------------------- */

/* FUN_000544a0 — begin an encounter/squad iterator over the squads named by a
 * packed ai_index_reference (Layout A). On invalid input iter[0] = -1.
 * 0x3f0 obj / 0x544a0 XBE. Asserts (ai_script.c:0x11a) iter non-NULL. */
void FUN_000544a0(unsigned int combined_index, void *iter_arg)
{
  int *iter;
  void *ai_globals;
  void *element;
  int profile_index;
  unsigned int selector;
  short sub_index;

  iter = (int *)iter_arg;
  ai_globals = FUN_0018e3b0();
  if (iter == 0) {
    display_assert("iterator", "c:\\halo\\SOURCE\\ai\\ai_script.c", 0x11a, 1);
    system_exit(-1);
  }

  profile_index = combined_index & 0xffff;
  iter[0] = profile_index;

  if (ai_globals == 0
      || *(char *)((char *)*(void **)0x632574 + 1) == 0
      || profile_index < 0
      || profile_index >= *(int *)((char *)ai_globals + 0x42c)) {
    iter[0] = -1;
    return;
  }

  element = tag_block_get_element((char *)global_scenario_get() + 0x42c,
                                  profile_index & 0xffff, 0xb0);
  selector = combined_index >> 0x1e;

  if (selector > 1) {
    if (selector != 2) {
      iter[0] = -1;
      return;
    }

    sub_index = (short)((unsigned char *)&combined_index)[2];
    if (sub_index < 0 || sub_index >= *(int *)((char *)element + 0x80)) {
      iter[0] = -1;
      return;
    }
    iter[2] = -1;
    iter[4] = sub_index;
    iter[3] = sub_index;
    iter[1] = -1;
    return;
  }

  iter[2] = -1;
  iter[3] = 0;
  iter[4] = *(int *)((char *)element + 0x80) - 1;
  if (selector == 0) {
    iter[1] = -1;
  } else {
    iter[1] = ((unsigned char *)&combined_index)[2];
  }
}

/* FUN_000545a0 — step an encounter/squad iterator (Layout A record from
 * FUN_000544a0). Scans element+0x80 sub-blocks (stride 0xe8) from iter[3] to
 * iter[4], skipping any whose field+0x22 != the iter[1] filter (-1 matches
 * all). Returns the squad pointer for a hit, NULL when exhausted.
 * 0x4f0 obj / 0x545a0 XBE. Asserts (ai_script.c:0x15f) iter non-NULL. */
int FUN_000545a0(void *iter_arg)
{
  int *iter;
  void *encounter;
  void *element;
  char *sub_base;
  void *sub;
  int profile_index;
  int result;

  iter = (int *)iter_arg;
  result = 0;
  if (iter == 0) {
    display_assert("iterator", "c:\\halo\\SOURCE\\ai\\ai_script.c", 0x15f, 1);
    system_exit(-1);
  }

  profile_index = iter[0];
  if (profile_index != -1) {
    encounter = datum_get(*(data_t **)0x5ab270, profile_index);
    element = tag_block_get_element((char *)global_scenario_get() + 0x42c,
                                    iter[0] & 0xffff, 0xb0);

    if (iter[3] <= iter[4]) {
      sub_base = (char *)element + 0x80;
      do {
        iter[2] = iter[3];
        iter[3] = iter[3] + 1;
        sub = tag_block_get_element(sub_base, iter[2], 0xe8);
        if (iter[1] == -1) {
          goto found;
        }
        if ((int)*(short *)((char *)sub + 0x22) == iter[1]) {
          goto found;
        }
      } while (iter[3] <= iter[4]);
    }
  }

  return result;

found:
  return (int)encounter_get_squad((char *)encounter,
                                  (short)(unsigned short)iter[2]);
}

/* FUN_00054680 — begin an actor iterator over the actors named by a packed
 * ai_index_reference (Layout B). On invalid input iter[0] = -1.
 * 0x5d0 obj / 0x54680 XBE. Asserts (ai_script.c:0x180) iter non-NULL. */
void FUN_00054680(unsigned int combined_index, void *iter_arg)
{
  int *iter;
  void *ai_globals;
  int profile_index;
  unsigned int selector;

  iter = (int *)iter_arg;
  ai_globals = FUN_0018e3b0();
  if (iter == 0) {
    display_assert("iterator", "c:\\halo\\SOURCE\\ai\\ai_script.c", 0x180, 1);
    system_exit(-1);
  }

  profile_index = combined_index & 0xffff;
  iter[0] = profile_index;

  if (ai_globals == 0
      || *(char *)((char *)*(void **)0x632574 + 1) == 0
      || profile_index < 0
      || profile_index >= *(int *)((char *)ai_globals + 0x42c)) {
    iter[0] = -1;
    return;
  }

  /* element fetched for validation side effects; result not read afterward
   * (eax is overwritten by the selector ladder in the original). */
  tag_block_get_element((char *)global_scenario_get() + 0x42c,
                        profile_index & 0xffff, 0xb0);

  selector = combined_index >> 0x1e;
  iter[2] = -1;
  iter[1] = -1;

  switch (selector) {
  case 0:
    /* both filters wildcard */
    break;
  case 1:
    iter[2] = (unsigned char)(combined_index >> 16);
    break;
  case 2:
    iter[1] = (unsigned char)(combined_index >> 16);
    break;
  default:
    iter[0] = -1;
    return;
  }

  if (iter[0] != -1) {
    encounter_actor_iterator_new(iter + 3, iter[0]);
  }
}

/* FUN_00054750 — step an actor iterator (Layout B record from FUN_00054680).
 * Pulls the next actor from the embedded encounter_actor_iterator (iter+3),
 * skipping any whose squad (field+0x3a) or platoon (field+0x3c) does not match
 * the iter[1]/iter[2] filters (-1 matches all). Returns the actor, NULL when
 * exhausted. 0x6a0 obj / 0x54750 XBE. Asserts (ai_script.c:0x1ba) iter non-NULL. */
int FUN_00054750(void *iter_arg)
{
  int *iter;
  void *actor;

  iter = (int *)iter_arg;
  if (iter == 0) {
    display_assert("iterator", "c:\\halo\\SOURCE\\ai\\ai_script.c", 0x1ba, 1);
    system_exit(-1);
  }

  for (;;) {
    actor = (void *)encounter_actor_iterator_next(iter + 3);
    if (actor == 0) {
      break;
    }
    if (iter[1] == -1 || iter[1] == (int)*(short *)((char *)actor + 0x3a)) {
      if (iter[2] == -1) {
        break;
      }
      if (iter[2] == (int)*(short *)((char *)actor + 0x3c)) {
        break;
      }
    }
  }

  return (int)actor;
}

/* FUN_000547c0 — relay all actors named by an ai_index_reference (plus each
 * actor's unit and child chain) through FUN_000ce2b0, keyed by the resource
 * handle from FUN_000ce200. Returns that handle, or -1 on bad input / no
 * resource. 0x710 obj / 0x547c0 XBE. */
int FUN_000547c0(int encounter_handle)
{
  int iter[6];               /* [ebp-0x18], Layout B */
  int resource;
  void *actor;
  int child;

  if (encounter_handle != -1) {
    resource = FUN_000ce200();
    if (resource != -1) {
      FUN_00054680((unsigned int)encounter_handle, iter);
      actor = (void *)FUN_00054750(iter);
      if (actor != 0) {
        do {
          if (*(int *)((char *)actor + 0x18) != -1) {
            FUN_000ce2b0(resource, *(int *)((char *)actor + 0x18));
          }

          child = *(int *)((char *)actor + 0x24);
          while (child != -1) {
            void *object = object_get_and_verify_type(child, 3);
            FUN_000ce2b0(resource, child);
            child = *(int *)((char *)object + 0x1ac);
          }

          actor = (void *)FUN_00054750(iter);
        } while (actor != 0);
      }
    }
    return resource;
  }

  return -1;
}

/* ---------------------------------------------------------------------------
 * ai_attach / ai_detach / ai_place script-command implementations.
 * The verbose AI-spew flag at 0x5aca59 gates a diagnostic error(2, ...) trace
 * at each entry; the AI-enabled gate at *(0x632574)+1 gates the actual work in
 * the attach path. (ai_profile_change_render_spray keeps its legacy kb name
 * ai_profile_change_render_spray; behaviorally it is ai_attach over children.)
 * ------------------------------------------------------------------------- */

/* FUN_00054860 — ai_attach: create one actor (from the ai_profile squad named
 * by ai_ref) and attach it to the unit object unit_handle. No-ops if AI is
 * disabled or either handle is the -1 sentinel. 0x7b0 obj / 0x54860 XBE. */
void FUN_00054860(int unit_handle, unsigned int ai_ref)
{
  char buffer[0x100];          /* [ebp-0x10c] */
  void *scenario;
  void *element;
  void *squad;
  void *variant;
  void *actv;
  int *actr_tag;
  int profile_index;
  int selector;
  int sub_index;
  int i;

  scenario = global_scenario_get();

  if (*(char *)0x5aca59 != 0) {
    FUN_00054220(ai_ref, scenario, buffer, 0x100);
    error(2, (const char *)0x25c460,
          hs_runtime_get_executing_thread_name(),
          unit_handle & 0xffff, buffer);
  }

  if (*(char *)((char *)*(void **)0x632574 + 1) == 0)
    return;
  if (unit_handle == -1 || ai_ref == 0xffffffff)
    return;

  profile_index = ai_ref & 0xffff;
  if (profile_index < 0)
    return;
  if (profile_index >= *(int *)((char *)scenario + 0x42c))
    return;

  element = tag_block_get_element((char *)global_scenario_get() + 0x42c,
                                  profile_index & 0xffff, 0xb0);
  selector = ai_ref >> 0x1e;
  sub_index = 0;

  if (selector == 2) {
    sub_index = *(unsigned char *)((char *)&ai_ref + 2);
    if (sub_index < 0)
      goto bad_squad;
  } else if (selector == 1) {
    i = 0;
    if (*(int *)((char *)element + 0x80) > 0) {
      do {
        void *sq = tag_block_get_element((char *)element + 0x80, i, 0xe8);
        if (*(short *)((char *)sq + 0x22)
            == *(unsigned char *)((char *)&ai_ref + 2)) {
          sub_index = i;
          if (sub_index < 0)
            goto bad_squad;
          break;
        }
        i++;
      } while (i < *(int *)((char *)element + 0x80));
    }
  }

  if (sub_index < *(int *)((char *)element + 0x80)) {
    squad = tag_block_get_element((char *)element + 0x80, sub_index, 0xe8);
    if (*(short *)((char *)squad + 0x20) != -1) {
      variant = tag_block_get_element((char *)scenario + 0x420,
                                      *(short *)((char *)squad + 0x20), 0x10);
      if (*(int *)((char *)variant + 0xc) != -1) {
        actv = tag_get(0x61637476, *(int *)((char *)variant + 0xc));
        if (*(int *)((char *)actv + 0x10) != -1) {
          actr_tag = (int *)tag_get(0x61637472, *(int *)((char *)actv + 0x10));
          actor_create_for_unit(
              (char)((*(unsigned int *)actr_tag >> 0x1a) & 0x101),
              unit_handle,
              *(int *)((char *)variant + 0xc),
              profile_index,
              sub_index,
              0,
              -1,
              (char)((*(unsigned int *)((char *)element + 0x20) >> 4) & 0x101),
              (short)*(unsigned short *)((char *)squad + 0x24),
              (short)*(unsigned short *)((char *)squad + 0x26),
              0xffff,
              0);
          encounters_update_dirty_status();
          return;
        }
      }
    }

    error(2, (const char *)0x25c408, element, squad);
    return;
  }

bad_squad:
  error(2, (const char *)0x25c3c0, element);
}

/* ai_profile_change_render_spray (ai_profile_change_render_spray) — ai_attach over the children
 * of a parent object: iterates every child (FUN_000ce450/FUN_000ce320) and
 * attaches the same ai_ref to each. 0x9d0 obj / 0x54a80 XBE. */
void ai_profile_change_render_spray(int parent_handle, unsigned int ai_ref)
{
  int iter_state;
  int child;

  child = FUN_000ce450(parent_handle, &iter_state);
  if (child == -1)
    return;
  do {
    FUN_00054860(child, ai_ref);
    child = FUN_000ce320(parent_handle, &iter_state);
  } while (child != -1);
}

/* FUN_00054ac0 — ai_detach: detach (delete the attached actor of) one unit
 * object. No-op if the handle is -1 or it has no attached actor (object+0x1a4
 * == -1). 0xa10 obj / 0x54ac0 XBE. */
void FUN_00054ac0(int unit_handle)
{
  void *object;
  int actor_handle;

  if (*(char *)0x5aca59 != 0) {
    error(2, "%s: ai_detach unit 0x%04X",
          hs_runtime_get_executing_thread_name(),
          unit_handle & 0xffff);
  }

  if (unit_handle == -1)
    return;

  object = object_get_and_verify_type(unit_handle, 3);
  actor_handle = *(int *)((char *)object + 0x1a4);
  if (actor_handle == -1)
    return;

  actor_delete(actor_handle, 0);
}

/* FUN_00054b20 — ai_detach over the children of a parent object: iterates each
 * child (FUN_000ce450/FUN_000ce320) and detaches its attached actor (inlines
 * FUN_00054ac0). 0xa70 obj / 0x54b20 XBE. */
void FUN_00054b20(int parent_handle)
{
  int iter_state;
  int child;
  void *object;
  int actor_handle;

  child = FUN_000ce450(parent_handle, &iter_state);
  if (child == -1)
    return;

  do {
    if (*(char *)0x5aca59 != 0) {
      error(2, "%s: ai_detach unit 0x%04X",
            hs_runtime_get_executing_thread_name(),
            child & 0xffff);
    }
    if (child != -1) {
      object = object_get_and_verify_type(child, 3);
      actor_handle = *(int *)((char *)object + 0x1a4);
      if (actor_handle != -1)
        actor_delete(actor_handle, 0);
    }
    child = FUN_000ce320(parent_handle, &iter_state);
  } while (child != -1);
}

/* FUN_00054bb0 — ai_place: place (spawn) the encounter named by an
 * ai_index_reference via encounter_create. The two sub-arguments are the
 * sub-index for the matching selector and -1 otherwise. 0xb00 obj/0x54bb0 XBE. */
void FUN_00054bb0(unsigned int ai_ref)
{
  char buffer[0x100];
  int selector;
  unsigned char sub_byte;
  int arg_a;
  int arg_b;

  if (*(char *)0x5aca59 != 0) {
    FUN_00054220(ai_ref, global_scenario_get(), buffer, 0x100);
    error(2, (const char *)0x25c49c,
          hs_runtime_get_executing_thread_name(), buffer);
  }

  if (ai_ref == 0xffffffff)
    return;

  sub_byte = *(unsigned char *)((char *)&ai_ref + 2);
  selector = ai_ref >> 0x1e;

  arg_b = (selector == 2) ? sub_byte : -1;
  arg_a = ((ai_ref >> 0x1e) == 1) ? sub_byte : -1;

  encounter_create(ai_ref & 0xffff, (short)arg_a, (short)arg_b);
}

/* ---------------------------------------------------------------------------
 * ai_index_reference count accessor (the "how many of X" query).
 *
 * FUN_00055350 resolves a packed ai_index_reference to a tag record and reports
 * one of three count_type quantities about it:
 *     count_type 0 -> the record's "start"/min index
 *     count_type 1 -> the record's "end"/max index
 *     count_type 2 -> the span (end - start), clamped to >= 0
 * The record is located by the reference's selector (top 2 bits):
 *     selector 0 -> the ai_profile element itself (offsets +0x2a/+0x2c/+0x34)
 *     selector 1 -> a platoon record (encounter_get_platoon, offs +0x4/+6/+8/+c)
 *     selector 2 -> a squad record  (encounter_get_squad,    offs +0x16..+0x1c)
 * In addition to the EAX result the dispatcher returns two record fields through
 * the optional out parameters: *out_min receives a fixed record field (squad/
 * platoon "name" word at +0x16/+0x4, or the profile's +0x18) and *out_handle
 * receives a record dword (squad/platoon +0x1c/+0xc, or the profile's +0x34).
 * count_type arrives in EDI as an int16 (compared via di / sign-extended via
 * movsx). 0x12a0 obj / 0x55350 XBE. Asserts (ai_script.c) on bad count_type and
 * on the unreachable selector/count_type defaults. */
int FUN_00055350(unsigned int ai_ref, int *out_min, int *out_handle,
                 int count_type /* @<edi> */)
{
  int ret_val;      /* [ebp-0x4], EAX result */
  int handle_val;   /* [ebp-0x8], flows to *out_handle */
  int min_val;      /* EBX, flows to *out_min */
  void *scenario;
  void *element;
  char *record;
  int profile_index;
  unsigned int selector;
  short sub_index;

  ret_val = 0;
  handle_val = 0;
  min_val = 0;

  if ((short)count_type < 0 || (short)count_type >= 3) {
    display_assert("(count_type >= 0) && (count_type < NUMBER_OF_AI_COUNT_TYPES)",
                   "c:\\halo\\SOURCE\\ai\\ai_script.c", 0x405, 1);
    system_exit(-1);
  }

  if (ai_ref == 0xffffffff)
    goto done;

  scenario = global_scenario_get();
  selector = ai_ref >> 0x1e;

  switch (selector) {
  case 0:
    profile_index = ai_ref & 0xffff;
    if (profile_index < 0
        || profile_index >= *(int *)((char *)scenario + 0x42c))
      goto done;
    element = datum_get(*(data_t **)0x5ab270, profile_index);

    switch ((short)count_type) {
    case 0:
      ret_val = *(short *)((char *)element + 0x2a);
      break;
    case 1:
      ret_val = *(short *)((char *)element + 0x2c);
      break;
    case 2:
      ret_val = (int)*(short *)((char *)element + 0x2a)
                - (int)*(short *)((char *)element + 0x2c);
      ret_val = (ret_val < 0) ? 0 : ret_val;
      break;
    default:
      display_assert("!\"unreachable\"",
                     "c:\\halo\\SOURCE\\ai\\ai_script.c", 0x424, 1);
      system_exit(-1);
    }
    min_val = *(short *)((char *)element + 0x18);
    handle_val = *(int *)((char *)element + 0x34);
    break;

  case 1:
    profile_index = ai_ref & 0xffff;
    if (profile_index < 0
        || profile_index >= *(int *)((char *)scenario + 0x42c))
      goto done;
    element = datum_get(*(data_t **)0x5ab270, profile_index);
    sub_index = ((unsigned char *)&ai_ref)[2];
    if (sub_index < 0 || sub_index >= *(short *)((char *)element + 0xa))
      goto done;
    record = FUN_00054020((char *)element, sub_index);

    switch ((short)count_type) {
    case 0:
      min_val = *(short *)(record + 0x4);
      ret_val = *(short *)(record + 0x6);
      handle_val = *(int *)(record + 0xc);
      break;
    case 1:
      min_val = *(short *)(record + 0x4);
      ret_val = *(short *)(record + 0x8);
      handle_val = *(int *)(record + 0xc);
      break;
    case 2:
      min_val = *(short *)(record + 0x4);
      ret_val = (int)*(short *)(record + 0x6)
                - (int)*(short *)(record + 0x8);
      ret_val = (ret_val < 0) ? 0 : ret_val;
      handle_val = *(int *)(record + 0xc);
      break;
    default:
      display_assert("!\"unreachable\"",
                     "c:\\halo\\SOURCE\\ai\\ai_script.c", 0x448, 1);
      system_exit(-1);
      min_val = *(short *)(record + 0x4);
      handle_val = *(int *)(record + 0xc);
    }
    break;

  case 2:
    profile_index = ai_ref & 0xffff;
    if (profile_index < 0
        || profile_index >= *(int *)((char *)scenario + 0x42c))
      goto done;
    element = datum_get(*(data_t **)0x5ab270, profile_index);
    sub_index = ((unsigned char *)&ai_ref)[2];
    if (sub_index < 0 || sub_index >= *(short *)((char *)element + 0x6))
      goto done;
    record = encounter_get_squad((char *)element, sub_index);

    switch ((short)count_type) {
    case 0:
      min_val = *(short *)(record + 0x16);
      ret_val = *(short *)(record + 0x18);
      handle_val = *(int *)(record + 0x1c);
      break;
    case 1:
      min_val = *(short *)(record + 0x16);
      ret_val = *(short *)(record + 0x1a);
      handle_val = *(int *)(record + 0x1c);
      break;
    case 2:
      min_val = *(short *)(record + 0x16);
      ret_val = (int)*(short *)(record + 0x18)
                - (int)*(short *)(record + 0x1a);
      ret_val = (ret_val < 0) ? 0 : ret_val;
      handle_val = *(int *)(record + 0x1c);
      break;
    default:
      display_assert("!\"unreachable\"",
                     "c:\\halo\\SOURCE\\ai\\ai_script.c", 0x46d, 1);
      system_exit(-1);
      min_val = *(short *)(record + 0x16);
      handle_val = *(int *)(record + 0x1c);
    }
    break;

  default:
    display_assert("!\"unreachable\"",
                   "c:\\halo\\SOURCE\\ai\\ai_script.c", 0x477, 1);
    system_exit(-1);
  }

done:
  if (out_min != 0)
    *out_min = min_val;
  if (out_handle != 0)
    *out_handle = handle_val;
  return ret_val;
}

/* FUN_00055620 — count_type 1 ("end"/max) accessor wrapper. 0x1570 obj. */
int FUN_00055620(unsigned int ai_ref)
{
  return FUN_00055350(ai_ref, 0, 0, 1);
}

/* FUN_00055640 — count_type 2 ("span") accessor wrapper. 0x1590 obj. */
int FUN_00055640(unsigned int ai_ref)
{
  return FUN_00055350(ai_ref, 0, 0, 2);
}

/* FUN_00055660 — count_type 0 ("start"/min) accessor wrapper. 0x15b0 obj. */
int FUN_00055660(unsigned int ai_ref)
{
  return FUN_00055350(ai_ref, 0, 0, 0);
}

/* FUN_00055680 — ratio accessor: count_type 0 result divided by the record's
 * *out_min field (numerator = EAX, denominator = the value written through
 * out_min). Returns 0.0f when the denominator is non-positive. 0x15d0 obj. */
float FUN_00055680(unsigned int ai_ref)
{
  int denom;
  int numer;
  union { int i; float f; } zero;

  zero.i = 0;
  numer = FUN_00055350(ai_ref, &denom, 0, 0);
  if (denom > 0)
    return (float)numer / (float)denom;
  return zero.f;
}

/* FUN_000556c0 — float-field accessor: count_type 0 resolves the record and
 * writes its handle dword through out_handle; that dword is reinterpreted as a
 * float (bit pattern, not a numeric conversion). 0x1610 obj. */
float FUN_000556c0(unsigned int ai_ref)
{
  union { int i; float f; } out;

  out.i = 0;
  FUN_00055350(ai_ref, 0, &out.i, 0);
  return out.f;
}

/* FUN_000556f0 — predicate: returns true if the ai_index_reference names any
 * encounter whose first byte is zero. Walks the encounter iterator built by
 * FUN_00054310/FUN_00054430; returns false if exhausted without a match.
 * 0x1640 obj. */
bool FUN_000556f0(unsigned int ai_ref)
{
  int iter[3];
  char *encounter;

  if (ai_ref == 0xffffffff)
    return 0;

  FUN_00054310(ai_ref, iter);
  encounter = (char *)FUN_00054430(iter);
  if (encounter == 0)
    return 0;

  do {
    if (*encounter == 0)
      return 1;
    encounter = (char *)FUN_00054430(iter);
  } while (encounter != 0);

  return 0;
}

/* ---------------------------------------------------------------------------
 * ai_kill / ai_kill_silent / ai_erase / ai_erase_all / ai_spawn_actor +
 * ai_debug select commands. Each public command emits a verbose diagnostic
 * trace gated by the AI-spew flag at 0x5aca59, then performs its work.
 * ------------------------------------------------------------------------- */

/* FUN_00054c40 — kill every actor named by the packed ai_index_reference in
 * EAX, forwarding by_player to actor_kill. Walks the Layout B actor iterator;
 * the live actor handle is the embedded iterator's current handle (iter[4]).
 * No-op when ai_ref is the -1 sentinel. 0x990 obj / 0x54c40 XBE. */
void FUN_00054c40(unsigned int ai_ref /* @<eax> */, char by_player)
{
  int iter[6];                 /* [ebp-0x18], Layout B actor iterator */

  if (ai_ref == 0xffffffff)
    return;

  FUN_00054680(ai_ref, iter);
  if (FUN_00054750(iter) != 0) {
    do {
      actor_kill(iter[4], by_player, 0);
    } while (FUN_00054750(iter) != 0);
  }
}

/* FUN_00054ca0 — ai_kill: kill the actors named by ai_ref (by_player = 0).
 * 0x9f0 obj / 0x54ca0 XBE. */
void FUN_00054ca0(unsigned int ai_ref)
{
  char buffer[0x100];          /* [ebp-0x100] */

  if (*(char *)0x5aca59 != 0) {
    FUN_00054220(ai_ref, global_scenario_get(), buffer, 0x100);
    error(2, (const char *)0x25c4ac,
          hs_runtime_get_executing_thread_name(), buffer);
  }

  FUN_00054c40(ai_ref, 0);
}

/* FUN_00054d00 — ai_kill_silent: kill the actors named by ai_ref silently
 * (by_player = 1). 0xa50 obj / 0x54d00 XBE. */
void FUN_00054d00(unsigned int ai_ref)
{
  char buffer[0x100];          /* [ebp-0x100] */

  if (*(char *)0x5aca59 != 0) {
    FUN_00054220(ai_ref, global_scenario_get(), buffer, 0x100);
    error(2, (const char *)0x25c4bc,
          hs_runtime_get_executing_thread_name(), buffer);
  }

  FUN_00054c40(ai_ref, 1);
}

/* FUN_00054d60 — ai_erase: erase the encounter/squad named by ai_ref. The
 * selector picks which sub-index (squad vs platoon) is passed; a non-matching
 * selector passes the -1 wildcard. 0xab0 obj / 0x54d60 XBE. */
void FUN_00054d60(unsigned int ai_ref)
{
  char buffer[0x100];          /* [ebp-0x100] */
  unsigned char sub_byte;      /* [ebp+0xa] -> dl */
  int sub_a;
  int sub_b;

  if (*(char *)0x5aca59 != 0) {
    FUN_00054220(ai_ref, global_scenario_get(), buffer, 0x100);
    error(2, (const char *)0x25c4d4,
          hs_runtime_get_executing_thread_name(), buffer);
  }

  if (ai_ref == 0xffffffff)
    return;

  sub_byte = *(unsigned char *)((char *)&ai_ref + 2);

  sub_b = ((ai_ref >> 0x1e) == 2) ? sub_byte : -1;
  sub_a = ((ai_ref >> 0x1e) == 1) ? sub_byte : -1;

  ai_erase(ai_ref & 0xffff, sub_a, sub_b, 0);
}

/* FUN_00054df0 — ai_erase_all: erase every encounter (wildcard).
 * 0xb40 obj / 0x54df0 XBE. */
void FUN_00054df0(void)
{
  if (*(char *)0x5aca59 != 0) {
    error(2, (const char *)0x25c4e4,
          hs_runtime_get_executing_thread_name());
  }

  ai_erase(-1, -1, -1, 0);
}

/* FUN_00054e20 — ai debug: select all actors (wildcard). Calls
 * ai_debug_select_actor(-1, -1) when AI is enabled (*(0x632574)+1).
 * 0xd70 obj / 0x54e20 XBE. */
void FUN_00054e20(void)
{
  if (*(char *)((char *)*(void **)0x632574 + 1) != 0)
    ai_debug_select_actor(-1, -1);
}

/* FUN_00054e40 — ai debug: select an encounter. The -1 sentinel selects the
 * current/all encounter; otherwise the low 16 bits index it. Gated by
 * *(0x632574)+1 (AI enabled). 0xd90 obj / 0x54e40 XBE. */
void FUN_00054e40(int encounter_ref)
{
  if (*(char *)((char *)*(void **)0x632574 + 1) == 0)
    return;

  if (encounter_ref == -1)
    ai_debug_select_encounter(-1);
  else
    ai_debug_select_encounter(encounter_ref & 0xffff);
}

/* FUN_00054e80 — ai_spawn_actor: spawn the actor(s) named by ai_ref. For a
 * direct squad reference (selector 2) the sub-index byte is the squad index;
 * for a profile reference (selector 1) it scans element+0x80 (squad sub-block,
 * stride 0xe8) for the squad whose +0x22 key matches the sub-index byte. On a
 * hit, encounter_spawn_actor(profile_index, squad_index). Gated by
 * *(0x632574)+1. 0xdd0 obj / 0x54e80 XBE. */
void FUN_00054e80(unsigned int ai_ref)
{
  char buffer[0x100];          /* [ebp-0x104] */
  void *element;
  void *sq;
  int profile_index;           /* [ebp-0x4] */
  int sub_byte;
  short squad_index;
  short i;

  if (*(char *)0x5aca59 != 0) {
    FUN_00054220(ai_ref, global_scenario_get(), buffer, 0x100);
    error(2, (const char *)0x25c4f8,
          hs_runtime_get_executing_thread_name(), buffer);
  }

  if (*(char *)((char *)*(void **)0x632574 + 1) == 0)
    return;
  if (ai_ref == 0xffffffff)
    return;

  profile_index = ai_ref & 0xffff;

  if ((ai_ref >> 0x1e) == 2) {
    squad_index = (short)*(unsigned char *)((char *)&ai_ref + 2);
    if (squad_index != -1)
      goto spawn;
    /* fall through to the selector==1 test (which fails) */
  }

  if ((ai_ref >> 0x1e) != 1)
    return;

  element = tag_block_get_element((char *)global_scenario_get() + 0x42c,
                                  profile_index & 0xffff, 0xb0);
  if (*(int *)((char *)element + 0x80) <= 0)
    return;

  sub_byte = (int)((ai_ref >> 0x10) & 0xff);
  squad_index = -1;
  i = 0;
  do {
    sq = tag_block_get_element((char *)element + 0x80, (int)i, 0xe8);
    if ((int)*(short *)((char *)sq + 0x22) == sub_byte) {
      squad_index = i;
      break;
    }
    i++;
  } while ((int)i < *(int *)((char *)element + 0x80));

  if (squad_index == -1)
    return;

spawn:
  encounter_spawn_actor(profile_index, (int)squad_index);
}

/* ---------------------------------------------------------------------------
 * AI script-command interface: per-profile setters and timer/effect drivers.
 * Each resolves a packed ai_index_reference to its named profile (for the
 * optional trace spew), then walks the referenced encounters/squads/actors to
 * apply the effect. The on/off token comes from the string pair 0x25c530 /
 * 0x25c52c. Structurally identical to the ai_braindead family in encounters.obj.
 * ------------------------------------------------------------------------- */

/* FUN_00054f90 — ai_set_respawn: toggle the respawn flag on the named
 * encounter. 0xee0 obj / 0x54f90 XBE. */
void FUN_00054f90(unsigned int combined_index, char flag)
{
  char name[256];          /* [ebp-0x100] */

  if (*(char *)0x5aca59) {
    FUN_00054220(combined_index, global_scenario_get(), name, 0x100);
    error(2, (const char *)0x25c510, hs_runtime_get_executing_thread_name(),
          name, flag ? (const char *)0x25c530 : (const char *)0x25c52c);
  }
  if (combined_index != 0xffffffff) {
    encounter_set_respawn(combined_index & 0xffff, flag);
  }
}

/* FUN_00055010 — ai_set_deaf: toggle the deaf flag on the named encounter.
 * 0xf60 obj / 0x55010 XBE. */
void FUN_00055010(unsigned int combined_index, char flag)
{
  char name[256];          /* [ebp-0x100] */

  if (*(char *)0x5aca59) {
    FUN_00054220(combined_index, global_scenario_get(), name, 0x100);
    error(2, (const char *)0x25c534, hs_runtime_get_executing_thread_name(),
          name, flag ? (const char *)0x25c530 : (const char *)0x25c52c);
  }
  if (combined_index != 0xffffffff) {
    encounter_set_deaf(combined_index & 0xffff, flag);
  }
}

/* FUN_00055090 — ai_set_blind: toggle the blind flag on the named encounter.
 * 0xfe0 obj / 0x55090 XBE. */
void FUN_00055090(unsigned int combined_index, char flag)
{
  char name[256];          /* [ebp-0x100] */

  if (*(char *)0x5aca59) {
    FUN_00054220(combined_index, global_scenario_get(), name, 0x100);
    error(2, (const char *)0x25c54c, hs_runtime_get_executing_thread_name(),
          name, flag ? (const char *)0x25c530 : (const char *)0x25c52c);
  }
  if (combined_index != 0xffffffff) {
    encounter_set_blind(combined_index & 0xffff, flag);
  }
}

/* FUN_00055110 — ai_magically_see_unit: make every actor named by
 * combined_handle "magically see" unit_handle. For each actor: force its
 * encounter active (actor+0x34), then look up the unit's slot (FUN_00064b40)
 * and apply unit-effect 3 (actor_handle_unit_effect). 0x1060 obj / 0x55110. */
void FUN_00055110(unsigned int combined_handle, int unit_handle)
{
  char name[256];          /* [ebp-0x118] */
  int iter[6];             /* [ebp-0x18], Layout B actor iterator */
  void *actor;
  int encounter_handle;
  int slot;

  if (*(char *)0x5aca59) {
    FUN_00054220(combined_handle, global_scenario_get(), name, 0x100);
    error(2, (const char *)0x25c564, hs_runtime_get_executing_thread_name(),
          name, unit_handle & 0xffff);
  }

  if (combined_handle == 0xffffffff || unit_handle == -1) {
    return;
  }

  FUN_00054680(combined_handle, iter);
  actor = (void *)FUN_00054750(iter);
  while (actor != 0) {
    encounter_handle = *(int *)((char *)actor + 0x34);
    if (encounter_handle != -1) {
      encounter_force_activate(encounter_handle);
    }
    slot = FUN_00064b40(iter[4], unit_handle, 1, 0);
    if (slot != -1) {
      actor_handle_unit_effect(iter[4], slot, 3);
    }
    actor = (void *)FUN_00054750(iter);
  }
}

/* FUN_000551e0 — ai_magically_see: make all actors named by combined_handle
 * see every unit in unit_group. Iterates the unit group via
 * FUN_000ce450/FUN_000ce320 and relays each unit through FUN_00055110.
 * 0x1130 obj / 0x551e0 XBE. */
void FUN_000551e0(unsigned int combined_handle, int unit_group)
{
  int unit;
  int state;               /* [ebp-0x4] */

  unit = FUN_000ce450(unit_group, &state);
  if (unit == -1) {
    return;
  }
  do {
    FUN_00055110(combined_handle, unit);
    unit = FUN_000ce320(unit_group, &state);
  } while (unit != -1);
}

/* FUN_00055220 — ai_timer_start: set the timer-running flag (squad+0x11 = 1)
 * on every squad named by combined_index. 0x1170 obj / 0x55220 XBE. */
void FUN_00055220(unsigned int combined_index)
{
  char name[256];          /* [ebp-0x114] */
  int iter[5];             /* [ebp-0x14], Layout A squad iterator */
  void *squad;

  if (*(char *)0x5aca59) {
    FUN_00054220(combined_index, global_scenario_get(), name, 0x100);
    error(2, (const char *)0x25c588, hs_runtime_get_executing_thread_name(),
          name);
  }

  if (combined_index == 0xffffffff) {
    return;
  }

  FUN_000544a0(combined_index, iter);
  squad = (void *)FUN_000545a0(iter);
  while (squad != 0) {
    *(char *)((char *)squad + 0x11) = 1;
    squad = (void *)FUN_000545a0(iter);
  }
}

/* FUN_000552b0 — ai_timer_expire: expire the timer on every squad named by
 * combined_index (encounter_squad_timer_expire(iter[0], iter[2])).
 * 0x1200 obj / 0x552b0 XBE. */
void FUN_000552b0(unsigned int combined_index)
{
  char name[256];          /* [ebp-0x114] */
  int iter[5];             /* [ebp-0x14], Layout A squad iterator */
  void *squad;

  if (*(char *)0x5aca59) {
    FUN_00054220(combined_index, global_scenario_get(), name, 0x100);
    error(2, (const char *)0x25c5a0, hs_runtime_get_executing_thread_name(),
          name);
  }

  if (combined_index == 0xffffffff) {
    return;
  }

  FUN_000544a0(combined_index, iter);
  squad = (void *)FUN_000545a0(iter);
  while (squad != 0) {
    encounter_squad_timer_expire(iter[0], (short)iter[2]);
    squad = (void *)FUN_000545a0(iter);
  }
}

/* ---------------------------------------------------------------------------
 * ai_attack / ai_defend / ai_maneuver / ai_maneuver_enable: per-encounter mode
 * setters. Each resolves the packed ai_index_reference, then walks the
 * FUN_00054310/FUN_00054430 encounter iterator poking a single mode byte on
 * every named encounter. Verbose trace gated by 0x5aca59.
 * ------------------------------------------------------------------------- */

/* FUN_00055750 — ai_attack: clear encounter[0] (attack mode) on every named
 * encounter. 0x16a0 obj / 0x55750 XBE. */
void FUN_00055750(unsigned int combined_index)
{
  char name[256];          /* [ebp-0x10c] */
  int iter[3];             /* [ebp-0xc] */
  char *encounter;

  if (*(char *)0x5aca59) {
    FUN_00054220(combined_index, global_scenario_get(), name, 0x100);
    error(2, (const char *)0x25c5f8, hs_runtime_get_executing_thread_name(),
          name);
  }

  if (combined_index == 0xffffffff) {
    return;
  }

  FUN_00054310(combined_index, iter);
  encounter = (char *)FUN_00054430(iter);
  if (encounter == 0) {
    return;
  }
  do {
    encounter[0] = 0;
    encounter = (char *)FUN_00054430(iter);
  } while (encounter != 0);
}

/* FUN_000557e0 — ai_defend: set encounter[0] (defend mode) on every named
 * encounter. 0x1730 obj / 0x557e0 XBE. */
void FUN_000557e0(unsigned int combined_index)
{
  char name[256];          /* [ebp-0x10c] */
  int iter[3];             /* [ebp-0xc] */
  char *encounter;

  if (*(char *)0x5aca59) {
    FUN_00054220(combined_index, global_scenario_get(), name, 0x100);
    error(2, (const char *)0x25c60c, hs_runtime_get_executing_thread_name(),
          name);
  }

  if (combined_index == 0xffffffff) {
    return;
  }

  FUN_00054310(combined_index, iter);
  encounter = (char *)FUN_00054430(iter);
  if (encounter == 0) {
    return;
  }
  do {
    encounter[0] = 1;
    encounter = (char *)FUN_00054430(iter);
  } while (encounter != 0);
}

/* FUN_00055870 — ai_maneuver: set encounter[1] (maneuver flag) on every named
 * encounter. 0x17c0 obj / 0x55870 XBE. */
void FUN_00055870(unsigned int combined_index)
{
  char name[256];          /* [ebp-0x10c] */
  int iter[3];             /* [ebp-0xc] */
  char *encounter;

  if (*(char *)0x5aca59) {
    FUN_00054220(combined_index, global_scenario_get(), name, 0x100);
    error(2, (const char *)0x25c620, hs_runtime_get_executing_thread_name(),
          name);
  }

  if (combined_index == 0xffffffff) {
    return;
  }

  FUN_00054310(combined_index, iter);
  encounter = (char *)FUN_00054430(iter);
  if (encounter == 0) {
    return;
  }
  do {
    encounter[1] = 1;
    encounter = (char *)FUN_00054430(iter);
  } while (encounter != 0);
}

/* FUN_00055900 — ai_maneuver_enable: enable/disable maneuvering on every named
 * encounter. Stores the inverse of the enable flag into encounter[2] (a
 * "maneuver disabled" byte): enable -> 0, disable -> 1. 0x1850 obj / 0x55900. */
void FUN_00055900(unsigned int combined_index, char flag)
{
  char name[256];          /* [ebp-0x10c] */
  int iter[3];             /* [ebp-0xc] */
  char *encounter;
  char disabled;

  if (*(char *)0x5aca59) {
    FUN_00054220(combined_index, global_scenario_get(), name, 0x100);
    error(2, (const char *)0x25c634, hs_runtime_get_executing_thread_name(),
          name, flag ? (const char *)0x25c530 : (const char *)0x25c52c);
  }

  if (combined_index == 0xffffffff) {
    return;
  }

  FUN_00054310(combined_index, iter);
  encounter = (char *)FUN_00054430(iter);
  if (encounter == 0) {
    return;
  }
  disabled = (flag == 0);
  do {
    encounter[2] = disabled;
    encounter = (char *)FUN_00054430(iter);
  } while (encounter != 0);
}

/* FUN_000559a0 (0x559a0) — XBE naked draft (batch 69). */
#if defined(__clang__)
static scenario_t * (*const b559a0_c18e380)(void) = global_scenario_get;
static void *(*const b559a0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b559a0_c544a0)(unsigned int combined_index, void *iter) = FUN_000544a0;
static int (*const b559a0_c545a0)(void *iter) = FUN_000545a0;
static int (*const b559a0_c1ba210)(int tag_index) = tag_get_group_tag;
static void *(*const b559a0_tag)(int, int) = tag_get;
static void (*const b559a0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static const char * (*const b559a0_c1ba1f0)(int tag_index) = tag_get_name;
static void (*const b559a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b559a0_exitfn)(int) = system_exit;
static const char * (*const b559a0_c3a760)(int16_t actor_type) = FUN_0003a760;

__attribute__((naked, noinline))
int16_t FUN_000559a0(unsigned int encounter_handle __attribute__((unused)), int field_0x34 __attribute__((unused)), int16_t squad_index __attribute__((unused)), void *actr_tag __attribute__((unused)), void *actv_tag __attribute__((unused)), char match_flag __attribute__((unused)), const void *debug_str __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x34, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c18e380]\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl %%esi, %%eax\n\t"
      "andl $0xffff, %%eax\n\t"
      "pushl $0xb0\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%ebx, -0x20(%%ebp)\n\t"
      "movl %%edi, -0x18(%%ebp)\n\t"
      "movl %%edi, -0x14(%%ebp)\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "call *%[c544a0]\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c545a0]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000559a0_24\n\t"
      "addl $0x80, %%ebx\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_000559a0_1:\n\t"
      "movl -0x2c(%%ebp), %%esi\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl $0xe8\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movw 0x20(%%eax), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_000559a0_10\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl 0x420(%%ecx), %%edx\n\t"
      "addl $0x420, %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jge .LFUN_000559a0_10\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_000559a0_3\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ba210]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0x61637476, %%eax\n\t"
      "jne .LFUN_000559a0_2\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x10(%%edi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000559a0_2\n\t"
      "pushl %%eax\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      ".LFUN_000559a0_2:\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      ".LFUN_000559a0_3:\n\t"
      "movl -0x2c(%%ebp), %%esi\n\t"
      ".LFUN_000559a0_4:\n\t"
      "cmpw %%cx, -0x8(%%ebp)\n\t"
      "jne .LFUN_000559a0_5\n\t"
      "movb 0x18(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000559a0_5\n\t"
      "movswl 0xc(%%ebp), %%edx\n\t"
      "cmpl %%esi, %%edx\n\t"
      "jne .LFUN_000559a0_5\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      ".LFUN_000559a0_5:\n\t"
      "cmpw %%cx, -0xc(%%ebp)\n\t"
      "jne .LFUN_000559a0_6\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000559a0_6\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_000559a0_6\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jne .LFUN_000559a0_6\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      ".LFUN_000559a0_6:\n\t"
      "cmpw %%cx, -0x10(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "jne .LFUN_000559a0_7\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000559a0_7\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_000559a0_7\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jne .LFUN_000559a0_7\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      ".LFUN_000559a0_7:\n\t"
      "cmpw %%cx, -0x14(%%ebp)\n\t"
      "jne .LFUN_000559a0_8\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000559a0_8\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_000559a0_8\n\t"
      "movw 0x14(%%eax), %%ax\n\t"
      "cmpw 0x14(%%ebx), %%ax\n\t"
      "jne .LFUN_000559a0_8\n\t"
      "movl %%esi, -0x14(%%ebp)\n\t"
      ".LFUN_000559a0_8:\n\t"
      "cmpw %%cx, -0x18(%%ebp)\n\t"
      "jne .LFUN_000559a0_9\n\t"
      "movl %%esi, -0x18(%%ebp)\n\t"
      ".LFUN_000559a0_9:\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c545a0]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000559a0_1\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "cmpw $-1, %%bx\n\t"
      "je .LFUN_000559a0_11\n\t"
      "movb 0x5aca57, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000559a0_14\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x25c76c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_000559a0_14\n\t"
      ".LFUN_000559a0_10:\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "jmp .LFUN_000559a0_4\n\t"
      ".LFUN_000559a0_11:\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "cmpw $-1, %%bx\n\t"
      "je .LFUN_000559a0_18\n\t"
      "movb 0x5aca57, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000559a0_14\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movswl %%bx, %%eax\n\t"
      "pushl $0xe8\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl $0x253b58, %%esi\n\t"
      "je .LFUN_000559a0_12\n\t"
      "andl $0xffff, %%eax\n\t"
      "pushl $0xb0\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movw 0xc(%%ebp), %%cx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $-1, %%cx\n\t"
      "je .LFUN_000559a0_12\n\t"
      "movswl %%cx, %%edx\n\t"
      "pushl $0xe8\n\t"
      "pushl %%edx\n\t"
      "addl $0x80, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movw 0x20(%%eax), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_000559a0_12\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl 0x420(%%ecx), %%edx\n\t"
      "addl $0x420, %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jge .LFUN_000559a0_12\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000559a0_12\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ba1f0]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      ".LFUN_000559a0_12:\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25c74c\n\t"
      ".LFUN_000559a0_13:\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000559a0_14:\n\t"
      "cmpw $-1, %%bx\n\t"
      "je .LFUN_000559a0_17\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .LFUN_000559a0_16\n\t"
      ".LFUN_000559a0_15:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movswl %%bx, %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jl .LFUN_000559a0_17\n\t"
      ".LFUN_000559a0_16:\n\t"
      "pushl $1\n\t"
      "pushl $0x5fc\n\t"
      "pushl $0x25c394\n\t"
      "pushl $0x25c6f0\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000559a0_17:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%bx, %%ax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000559a0_18:\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "cmpw $-1, %%bx\n\t"
      "je .LFUN_000559a0_21\n\t"
      "movb 0x5aca57, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000559a0_14\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movswl %%bx, %%ecx\n\t"
      "pushl $0xe8\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl $0x253b58, %%eax\n\t"
      "je .LFUN_000559a0_20\n\t"
      "movl 0x10(%%ecx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_000559a0_19\n\t"
      "movl $0x25ad08, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25c6d0\n\t"
      "jmp .LFUN_000559a0_13\n\t"
      ".LFUN_000559a0_19:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ba1f0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000559a0_20:\n\t"
      "pushl %%eax\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25c6d0\n\t"
      "jmp .LFUN_000559a0_13\n\t"
      ".LFUN_000559a0_21:\n\t"
      "movl -0x14(%%ebp), %%ebx\n\t"
      "cmpw $-1, %%bx\n\t"
      "je .LFUN_000559a0_22\n\t"
      "movb 0x5aca57, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000559a0_14\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movswl %%bx, %%ecx\n\t"
      "pushl $0xe8\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x14(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c3a760]\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "pushl $0x25c6b4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x24, %%esp\n\t"
      "jmp .LFUN_000559a0_14\n\t"
      ".LFUN_000559a0_22:\n\t"
      "movl -0x18(%%ebp), %%ebx\n\t"
      "cmpw $-1, %%bx\n\t"
      "je .LFUN_000559a0_23\n\t"
      "movb 0x5aca57, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000559a0_14\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movswl %%bx, %%eax\n\t"
      "pushl $0xe8\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl $0x25c68c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x1c, %%esp\n\t"
      "jmp .LFUN_000559a0_14\n\t"
      ".LFUN_000559a0_23:\n\t"
      "movl -0x20(%%ebp), %%ebx\n\t"
      "orl $0xffffffff, %%edi\n\t"
      ".LFUN_000559a0_24:\n\t"
      "movl 0x80(%%ebx), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "leal 0x80(%%ebx), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jle .LFUN_000559a0_25\n\t"
      "movb 0x5aca57, %%al\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000559a0_15\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl $0xe8\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x25c654\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x1c, %%esp\n\t"
      "jmp .LFUN_000559a0_15\n\t"
      ".LFUN_000559a0_25:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(b559a0_c18e380), [elem] "m"(b559a0_elem), [c544a0] "m"(b559a0_c544a0), [c545a0] "m"(b559a0_c545a0), [c1ba210] "m"(b559a0_c1ba210), [tag] "m"(b559a0_tag), [c8f390] "m"(b559a0_c8f390), [c1ba1f0] "m"(b559a0_c1ba1f0), [assert] "m"(b559a0_assert), [exitfn] "m"(b559a0_exitfn), [c3a760] "m"(b559a0_c3a760)
      : "memory");
}
#else
#error "FUN_000559a0: clang naked draft required"
#endif


/* FUN_00055dd0 (0x55dd0) — XBE naked draft (batch 69). */
#if defined(__clang__)
static scenario_t * (*const b55dd0_c18e380)(void) = global_scenario_get;
static void *(*const b55dd0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b55dd0_elem)(void *, int, int) = tag_block_get_element;
static void *(*const b55dd0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b55dd0_c544a0)(unsigned int combined_index, void *iter) = FUN_000544a0;
static int (*const b55dd0_c545a0)(void *iter) = FUN_000545a0;
static void (*const b55dd0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b55dd0_exitfn)(int) = system_exit;
static int (*const b55dd0_c1ba210)(int tag_index) = tag_get_group_tag;
static void *(*const b55dd0_tag)(int, int) = tag_get;
static int (*const b55dd0_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static int16_t (*const b55dd0_c559a0)(unsigned int encounter_handle, int field_0x34, int16_t squad_index, void *actr_tag, void *actv_tag, char match_flag, const void *debug_str) = FUN_000559a0;
static void (*const b55dd0_c59a00)(int *iter, int clump_handle) = encounter_actor_iterator_new;
static int (*const b55dd0_c59a50)(int *iter) = encounter_actor_iterator_next;
static void (*const b55dd0_c3baa0)(int actor_handle, int encounter_handle, int16_t squad_index) = FUN_0003baa0;
static void (*const b55dd0_c36dc0)(int actor_handle, char flags_bit1, char flags_bit0) = FUN_00036dc0;
static void (*const b55dd0_c59b10)(void *iter, char flag) = encounter_iterator_next;
static int (*const b55dd0_c59b50)(void *iter) = FUN_00059b50;
static short (*const b55dd0_gbspi)(void) = global_structure_bsp_index_get;
static void (*const b55dd0_c597f0)(int actor_handle) = encounterless_detach_actor;
static void (*const b55dd0_c5d200)(int actor_handle, int encounter_index, int16_t squad_index, int flag) = encounter_attach_actor;
static void (*const b55dd0_c40280)(void) = ai_update_team_status;
static void (*const b55dd0_c5d890)(void) = encounters_update_dirty_status;

__attribute__((naked, noinline))
void FUN_00055dd0(int encounter_handle __attribute__((unused)), int dest_encounter __attribute__((unused)), int param_3 __attribute__((unused)), int param_4 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc8, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_00055dd0_38\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "cmpl $-1, %%ebx\n\t"
      "pushl %%edi\n\t"
      "je .LFUN_00055dd0_37\n\t"
      "movl %%esi, %%edi\n\t"
      "andl $0xffff, %%edi\n\t"
      "andl $0xffff, %%ebx\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "je .LFUN_00055dd0_37\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .LFUN_00055dd0_37\n\t"
      "call *%[c18e380]\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "movl 0x5ab270, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x5ab270, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%edi, %%eax\n\t"
      "andl $0xffff, %%eax\n\t"
      "pushl $0xb0\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%ebx, %%edx\n\t"
      "andl $0xffff, %%edx\n\t"
      "pushl $0xb0\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x44(%%ebp)\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x42c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "pushl $0x80\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "leal -0xc8(%%ebp), %%eax\n\t"
      "pushl $-1\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "pushl %%eax\n\t"
      "sete -0x4(%%ebp)\n\t"
      "call *%[memset]\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c544a0]\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c545a0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x24, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_00055dd0_8\n\t"
      ".LFUN_00055dd0_1:\n\t"
      "movl -0x2c(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jl .LFUN_00055dd0_2\n\t"
      "cmpl $0x40, %%ebx\n\t"
      "jl .LFUN_00055dd0_3\n\t"
      ".LFUN_00055dd0_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x623\n\t"
      "pushl $0x25c394\n\t"
      "pushl $0x25c870\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00055dd0_3:\n\t"
      "cmpw $0, 0x18(%%esi)\n\t"
      "jg .LFUN_00055dd0_4\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movb 0x1e(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00055dd0_7\n\t"
      ".LFUN_00055dd0_4:\n\t"
      "movl -0x44(%%ebp), %%ecx\n\t"
      "pushl $0xe8\n\t"
      "addl $0x80, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, -0x48(%%ebp)\n\t"
      "movw 0x20(%%eax), %%ax\n\t"
      "xorl %%esi, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw %%si, %%ax\n\t"
      "movl %%esi, -0x20(%%ebp)\n\t"
      "jl .LFUN_00055dd0_6\n\t"
      "movl -0x40(%%ebp), %%ecx\n\t"
      "movl 0x420(%%ecx), %%edx\n\t"
      "addl $0x420, %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jge .LFUN_00055dd0_6\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00055dd0_5\n\t"
      "pushl %%eax\n\t"
      "call *%[c1ba210]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0x61637476, %%eax\n\t"
      "jne .LFUN_00055dd0_5\n\t"
      "movl 0xc(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00055dd0_5\n\t"
      "pushl %%eax\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      ".LFUN_00055dd0_5:\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      ".LFUN_00055dd0_6:\n\t"
      "movl -0x48(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25c864\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c1d90f0]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x5ab100\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c559a0]\n\t"
      "addl $0x24, %%esp\n\t"
      "movw %%ax, -0xc8(%%ebp,%%ebx,2)\n\t"
      ".LFUN_00055dd0_7:\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c545a0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00055dd0_1\n\t"
      ".LFUN_00055dd0_8:\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59a00]\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c59a50]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00055dd0_16\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00055dd0_9:\n\t"
      "movw 0x3a(%%eax), %%si\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_00055dd0_10\n\t"
      "cmpw $0x40, %%si\n\t"
      "jl .LFUN_00055dd0_11\n\t"
      ".LFUN_00055dd0_10:\n\t"
      "pushl $1\n\t"
      "pushl $0x651\n\t"
      "pushl $0x25c394\n\t"
      "pushl $0x25c810\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00055dd0_11:\n\t"
      "movswl %%si, %%ebx\n\t"
      "movw -0xc8(%%ebp,%%ebx,2), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "leal -0xc8(%%ebp,%%ebx,2), %%ebx\n\t"
      "je .LFUN_00055dd0_15\n\t"
      "movb -0x4(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00055dd0_12\n\t"
      "cmpw %%si, %%ax\n\t"
      "je .LFUN_00055dd0_15\n\t"
      ".LFUN_00055dd0_12:\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00055dd0_13\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x80(%%ecx), %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .LFUN_00055dd0_14\n\t"
      ".LFUN_00055dd0_13:\n\t"
      "pushl $1\n\t"
      "pushl $0x65d\n\t"
      "pushl $0x25c394\n\t"
      "pushl $0x25c780\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00055dd0_14:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw (%%ebx), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c3baa0]\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00055dd0_15\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c36dc0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00055dd0_15:\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59a50]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00055dd0_9\n\t"
      ".LFUN_00055dd0_16:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movb 0x1e(%%edx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00055dd0_27\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c59b10]\n\t"
      "leal -0x3c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59b50]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_00055dd0_25\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00055dd0_17:\n\t"
      "movl 0x44(%%ebx), %%edx\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "andl $0xffff, %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jne .LFUN_00055dd0_24\n\t"
      "movw 0x48(%%ebx), %%si\n\t"
      "testw %%si, %%si\n\t"
      "jl .LFUN_00055dd0_18\n\t"
      "cmpw $0x40, %%si\n\t"
      "jl .LFUN_00055dd0_19\n\t"
      ".LFUN_00055dd0_18:\n\t"
      "pushl $1\n\t"
      "pushl $0x677\n\t"
      "pushl $0x25c394\n\t"
      "pushl $0x25c810\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00055dd0_19:\n\t"
      "movswl %%si, %%edi\n\t"
      "movw -0xc8(%%ebp,%%edi,2), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "leal -0xc8(%%ebp,%%edi,2), %%edi\n\t"
      "je .LFUN_00055dd0_23\n\t"
      "movb -0x4(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00055dd0_20\n\t"
      "cmpw %%si, %%ax\n\t"
      "je .LFUN_00055dd0_23\n\t"
      ".LFUN_00055dd0_20:\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00055dd0_21\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x80(%%ecx), %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .LFUN_00055dd0_22\n\t"
      ".LFUN_00055dd0_21:\n\t"
      "pushl $1\n\t"
      "pushl $0x683\n\t"
      "pushl $0x25c394\n\t"
      "pushl $0x25c780\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00055dd0_22:\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl %%edx, 0x44(%%ebx)\n\t"
      "movw (%%edi), %%ax\n\t"
      "movw %%ax, 0x48(%%ebx)\n\t"
      ".LFUN_00055dd0_23:\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      ".LFUN_00055dd0_24:\n\t"
      "leal -0x3c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59b50]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $4, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .LFUN_00055dd0_17\n\t"
      ".LFUN_00055dd0_25:\n\t"
      "movb -0x4(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00055dd0_27\n\t"
      "testl $0xc0000000, %%edi\n\t"
      "jne .LFUN_00055dd0_26\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movb $0, 0x1e(%%edx)\n\t"
      ".LFUN_00055dd0_26:\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movb $1, 0x1e(%%eax)\n\t"
      ".LFUN_00055dd0_27:\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59a00]\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c59a50]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_00055dd0_35\n\t"
      ".LFUN_00055dd0_28:\n\t"
      "movl 0x30(%%esi), %%eax\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "andl $0xffff, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jne .LFUN_00055dd0_34\n\t"
      "movw 0x38(%%esi), %%bx\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .LFUN_00055dd0_29\n\t"
      "cmpw $0x40, %%bx\n\t"
      "jl .LFUN_00055dd0_30\n\t"
      ".LFUN_00055dd0_29:\n\t"
      "pushl $1\n\t"
      "pushl $0x6a4\n\t"
      "pushl $0x25c394\n\t"
      "pushl $0x25c810\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00055dd0_30:\n\t"
      "movswl %%bx, %%edi\n\t"
      "movw -0xc8(%%ebp,%%edi,2), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "leal -0xc8(%%ebp,%%edi,2), %%edi\n\t"
      "je .LFUN_00055dd0_34\n\t"
      "movb -0x4(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00055dd0_31\n\t"
      "cmpw %%bx, %%ax\n\t"
      "je .LFUN_00055dd0_34\n\t"
      ".LFUN_00055dd0_31:\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00055dd0_32\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movswl %%ax, %%ecx\n\t"
      "cmpl 0x80(%%edx), %%ecx\n\t"
      "jl .LFUN_00055dd0_33\n\t"
      ".LFUN_00055dd0_32:\n\t"
      "pushl $1\n\t"
      "pushl $0x6b0\n\t"
      "pushl $0x25c394\n\t"
      "pushl $0x25c780\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00055dd0_33:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl %%eax, 0x30(%%esi)\n\t"
      "movb -0x4(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movw (%%edi), %%cx\n\t"
      "movw %%cx, 0x38(%%esi)\n\t"
      "jne .LFUN_00055dd0_34\n\t"
      "call *%[gbspi]\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "cmpw %%ax, 0x7e(%%edx)\n\t"
      "jne .LFUN_00055dd0_34\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c597f0]\n\t"
      "movl 0x30(%%esi), %%edx\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x38(%%esi), %%cx\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c5d200]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00055dd0_34:\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c59a50]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00055dd0_28\n\t"
      ".LFUN_00055dd0_35:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movw 0x2(%%edx), %%ax\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "cmpw 0x2(%%ecx), %%ax\n\t"
      "je .LFUN_00055dd0_36\n\t"
      "call *%[c40280]\n\t"
      ".LFUN_00055dd0_36:\n\t"
      "call *%[c5d890]\n\t"
      ".LFUN_00055dd0_37:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00055dd0_38:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e380] "m"(b55dd0_c18e380), [dget] "m"(b55dd0_dget), [elem] "m"(b55dd0_elem), [memset] "m"(b55dd0_memset), [c544a0] "m"(b55dd0_c544a0), [c545a0] "m"(b55dd0_c545a0), [assert] "m"(b55dd0_assert), [exitfn] "m"(b55dd0_exitfn), [c1ba210] "m"(b55dd0_c1ba210), [tag] "m"(b55dd0_tag), [c1d90f0] "m"(b55dd0_c1d90f0), [c559a0] "m"(b55dd0_c559a0), [c59a00] "m"(b55dd0_c59a00), [c59a50] "m"(b55dd0_c59a50), [c3baa0] "m"(b55dd0_c3baa0), [c36dc0] "m"(b55dd0_c36dc0), [c59b10] "m"(b55dd0_c59b10), [c59b50] "m"(b55dd0_c59b50), [gbspi] "m"(b55dd0_gbspi), [c597f0] "m"(b55dd0_c597f0), [c5d200] "m"(b55dd0_c5d200), [c40280] "m"(b55dd0_c40280), [c5d890] "m"(b55dd0_c5d890)
      : "memory");
}
#else
#error "FUN_00055dd0: clang naked draft required"
#endif

