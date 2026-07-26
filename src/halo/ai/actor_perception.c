/* actor_perception.c — AI actor perception and prop evaluation.
 *
 * Corresponds to actor_perception.obj.
 * Assertion path: c:\halo\SOURCE\ai\actor_perception.c
 */

#include "../../common.h"

/* FUN_0002f1a0: set actor movement destination or refresh path.
 *
 * If the actor is moving-to-point (field_15e == 4) and has a pending
 * destination (field_504 != 0), delegates to actor_move_to_point with
 * the actor's position at +0x12c, surface index at +0x164, and -1.
 *
 * Otherwise sets field_3b8 = -1, copies the 6-dword block from +0x400
 * to +0x46c (after setting field_400 = 1 as a short), and calls
 * actor_path_refresh(actor_handle, 1, NULL).
 *
 * No __FILE__ string. */
void FUN_0002f1a0(int actor_handle)
{
  char *actor;
  int i;

  actor = (char *)datum_get(actor_data, actor_handle);

  if (*(short *)(actor + 0x15e) == 4 && *(char *)(actor + 0x504) != '\0') {
    actor_move_to_point(actor_handle, (float *)(actor + 0x12c),
                        *(int *)(actor + 0x164), -1);
    return;
  }

  *(short *)(actor + 0x3b8) = -1;

  if (*(short *)(actor + 0x46c) != 1) {
    *(short *)(actor + 0x400) = 1;
    for (i = 0; i < 6; i++) {
      *(int *)(actor + 0x46c + i * 4) = *(int *)(actor + 0x400 + i * 4);
    }
  }

  actor_path_refresh(actor_handle, 1, NULL);
}

/* FUN_0002f230 (0x2f230): refresh actor path or dispatch to move/firing
 * position.
 *
 * If actor is NOT in move-to-point mode (field_15e != 4):
 *   copies 6-dword block from +0x400 to +0x46c (if not already done),
 *   then calls actor_path_refresh(actor_handle, 1, NULL).
 * If in move-to-point mode and field_3b8 != -1:
 *   calls actor_move_to_firing_position.
 * Otherwise falls through to FUN_0002f1a0. */
void FUN_0002f230(int actor_handle)
{
  char *actor;

  actor = (char *)datum_get(actor_data, actor_handle);

  if (*(short *)(actor + 0x15e) == 4) {
    if (*(short *)(actor + 0x3b8) == -1) {
      FUN_0002f1a0(actor_handle);
      return;
    }
    actor_move_to_firing_position(actor_handle, *(short *)(actor + 0x3b8), 0);
    return;
  }

  if (*(short *)(actor + 0x46c) != 1) {
    *(short *)(actor + 0x400) = 1;
    memcpy(actor + 0x46c, actor + 0x400, 24);
  }
  actor_path_refresh(actor_handle, 1, NULL);
}

/* actor_perception_acknowledge (0x2f2b0)
 * Acknowledge a damaging prop for an actor. Validates ownership and prop type,
 * clears acknowledgement fields, sets the acknowledged flag, then dispatches
 * to the update function.
 *
 * Asserts: prop->owner_actor_index == actor_index (line 0x40d)
 *          prop_acknowledged(prop) — type in [2,3] (line 0x40e)
 *          prop->orphan_prop_index == NONE (line 0x40f) */
void actor_perception_acknowledge(int actor_handle, int prop_handle,
                                  int param_3, char param_4)
{
  char *prop;

  prop = (char *)datum_get(*(data_t **)0x5ab23c, prop_handle);

  if (*(int *)(prop + 4) != actor_handle) {
    display_assert("prop->owner_actor_index == actor_index",
                   "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0x40d, 1);
    system_exit(-1);
  }

  if (*(short *)(prop + 0x24) < 2 || *(short *)(prop + 0x24) > 3) {
    display_assert("prop_acknowledged(prop)",
                   "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0x40e, 1);
    system_exit(-1);
  }

  if (*(int *)(prop + 0xc) != -1) {
    display_assert("prop->orphan_prop_index == NONE",
                   "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0x40f, 1);
    system_exit(-1);
  }

  *(char *)(prop + 0xba) = 0;
  *(char *)(prop + 0xb9) = 0;
  *(char *)(prop + 0xbb) = 0;
  *(char *)(prop + 0x64) = 1;

  FUN_00036f20(actor_handle, prop_handle, param_3, param_4);
}

/* FUN_0002f380 (0x2f380)
 * Returns the engagement level (0-3) for a prop relative to actor.
 * 3 = actively targeting/seen; 2/3 = based on orphan state; 0/1/2 = based
 * on actor awareness level when no prop or no orphan.
 */
uint16_t FUN_0002f380(int actor_handle, int prop_handle)
{
  char *actor;
  char *prop;
  char *orphan;
  uint16_t r;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (prop_handle != -1) {
    prop = (char *)datum_get(*(data_t **)0x5ab23c, prop_handle);
    if (*(int *)(prop + 4) != actor_handle) {
      display_assert("prop->owner_actor_index == actor_index",
                     "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0x572, 1);
      system_exit(-1);
    }
    if ((*(short *)(prop + 0x24) >= 2 && *(short *)(prop + 0x24) <= 3) ||
        *(short *)(prop + 0x66) == 1 || *(short *)(prop + 0x66) == 2 ||
        (*(char *)(prop + 0x60) == 0 &&
         (*(char *)(prop + 0x127) == 0 || *(short *)(actor + 0x6a) >= 3))) {
      return 3;
    }
    if (*(int *)(prop + 0xc) != -1) {
      orphan = (char *)datum_get(*(data_t **)0x5ab23c, *(int *)(prop + 0xc));
      r = (uint16_t)((*(char *)(orphan + 0xb8) != 0) + 2);
      if (r != 0xffff) {
        return r;
      }
    }
  }
  if (*(short *)(actor + 0x6e) >= 2)
    return 2;
  return (uint16_t)(*(short *)(actor + 0x6a) >= 3);
}

/* FUN_0002f5b0 (0x2f5b0)
 * Compare two prop-like structs by their float[2] field (offset +8).
 * Returns -1, 0, or 1 (strcmp-style).
 */
int FUN_0002f5b0(int param_1, int param_2)
{
  float f1;
  float f2;

  f1 = *(float *)(param_1 + 8);
  f2 = *(float *)(param_2 + 8);
  if (f1 < f2)
    return -1;
  if (f2 < f1)
    return 1;
  return 0;
}

/* actor_perception_find_prop_pathfinding_location (0x2f910)
 * Fills prop->pathfinding_surface_index (+0xec) if not already set.
 * If prop has a vehicle handle (+0x110), uses vehicle_get_estimated_position;
 * otherwise if unit is a biped, uses biped_find_pathfinding_surface_index.
 * Output position written to prop->pathfinding_position (+0xf0).
 */
void actor_perception_find_prop_pathfinding_location(int actor_handle,
                                                     int prop_handle)
{
  char *prop;
  int unit_handle;

  prop = (char *)datum_get(*(data_t **)0x5ab23c, prop_handle);
  if (*(int *)(prop + 4) != actor_handle) {
    display_assert("prop->owner_actor_index == actor_index",
                   "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0xe01, 1);
    system_exit(-1);
  }
  if (*(int *)(prop + 0xec) == -1) {
    if (*(int *)(prop + 0x110) != -1) {
      *(int *)(prop + 0xec) = vehicle_get_estimated_position(
        *(int *)(prop + 0x110), (vector3_t *)(prop + 0xf0));
      return;
    }
    unit_handle = *(int *)(prop + 0x18);
    if (object_try_and_get_and_verify_type(unit_handle, 1) != NULL) {
      *(int *)(prop + 0xec) = biped_find_pathfinding_surface_index(
        unit_handle, (vector3_t *)(prop + 0xf0));
    }
  }
}

/* actor_perception_find_killer_prop_index (0x2f9b0)
 * Find the highest-scoring active damaging prop visible to the unit that owns
 * the given prop. Similar to actor_get_best_damaging_prop but uses the prop's
 * owning unit as the source of weapon slots.
 * flag: when non-zero, require prop visibility; when 0, accept any.
 */
int actor_perception_find_killer_prop_index(int actor_handle, int prop_handle,
                                            int flag)
{
  char *prop_rec;
  char *unit;
  char *cand_prop;
  int *slot;
  int score;
  int responsible;
  int cand_handle;
  int best_handle;
  int best_score;
  int count;
  short prop_type;

  prop_rec = (char *)datum_get(*(data_t **)0x5ab23c, prop_handle);
  unit = (char *)object_get_and_verify_type(*(int *)(prop_rec + 0x18), 3);
  best_handle = -1;
  best_score = 0;
  slot = (int *)(unit + 0x3e8);
  count = 4;
  do {
    score = slot[-2];
    responsible = ai_get_responsible_unit((unsigned int)*slot, 1);
    if (responsible != -1) {
      cand_handle = prop_get_active_by_unit_index(actor_handle, responsible);
      if (cand_handle != -1) {
        cand_prop = (char *)datum_get(*(data_t **)0x5ab23c, cand_handle);
        prop_type = *(short *)(cand_prop + 0x24);
        if (prop_type >= 2 && prop_type <= 3) {
          if (*(char *)(cand_prop + 0x60) != '\0' || flag == '\0') {
            if (best_score < score) {
              best_handle = cand_handle;
              best_score = score;
            }
          }
        }
      }
    }
    slot += 4;
    count--;
  } while (count != 0);
  return best_handle;
}

/* actor_get_best_damaging_prop (0x2fa70)
 * Find the highest-scoring active damaging prop visible to the actor's unit.
 *
 * Iterates up to 4 weapon slots on the actor's unit object (+0x3e0),
 * calling ai_get_responsible_unit and prop_get_active_by_unit_index for
 * each slot. Selects the prop whose slot score (*slot) is greatest among
 * those with type in [2,3] and either a visibility flag or no-filter mode.
 *
 * param_2 (prefer_visible): when 0, accept props regardless of visibility
 * flag; when non-zero, require prop visibility byte (+0x60) != 0.
 *
 * Returns the best damaging prop handle, or -1 if none found.
 * Asserts damaging_prop_index != 0 (handle 0 is reserved/invalid). */
int actor_get_best_damaging_prop(int actor_handle, char prefer_visible)
{
  char *unit;
  char *prop_rec;
  unsigned int *slot;
  int unit_handle;
  int unit_result;
  int prop_handle;
  unsigned int best_score;
  int damaging_prop_index;
  short prop_type;
  int iter;

  unit_handle = *(int *)((char *)datum_get(actor_data, actor_handle) + 0x18);
  damaging_prop_index = -1;
  if (unit_handle != -1) {
    unit = (char *)object_get_and_verify_type(unit_handle, 3);
    best_score = 0;
    slot = (unsigned int *)(unit + 0x3e0);
    iter = 4;
    do {
      unit_result = ai_get_responsible_unit(slot[2], 1);
      if (unit_result != -1) {
        prop_handle = prop_get_active_by_unit_index(actor_handle, unit_result);
        if (prop_handle != -1) {
          prop_rec = (char *)datum_get(*(data_t **)0x5ab23c, prop_handle);
          prop_type = *(short *)(prop_rec + 0x24);
          if (prop_type >= 2 && prop_type <= 3) {
            if (*(char *)(prop_rec + 0x60) != '\0' || prefer_visible == '\0') {
              if (*slot > best_score) {
                best_score = *slot;
                damaging_prop_index = prop_handle;
              }
            }
          }
        }
      }
      slot += 4;
      iter--;
    } while (iter != 0);

    if (damaging_prop_index == 0) {
      display_assert("damaging_prop_index != 0x00000000",
                     "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0xe8e, 1);
      system_exit(-1);
    }
    return damaging_prop_index;
  }
  return damaging_prop_index;
}

/* actor_perception_forget_recent_damage (0x2fb70) — Clear the recent-damage
 * tracking for all props visible to this actor. Resets field +0x74 to 0 and
 * field +0x6c to -1 for each prop in the iterator. */
__declspec(noinline) void actor_perception_forget_recent_damage(int actor_handle)
{
  int iter[2];
  char *prop;

  FUN_00064540(iter, actor_handle);
  prop = (char *)FUN_00064570(iter);
  while (prop != NULL) {
    *(char *)(prop + 0x74) = 0;
    *(int16_t *)(prop + 0x6c) = -1;
    prop = (char *)FUN_00064570(iter);
  }
}

/* actor_perception_retreat_successful (0x2fbc0) — Clear pursuit/retreat timers
 * for all props tracked by this actor. Zeros fields +0xaa, +0xae, +0xac on
 * each prop datum. */
__declspec(noinline) void actor_perception_retreat_successful(int actor_handle)
{
  int iter[2];
  char *prop;

  datum_get(actor_data, actor_handle);
  FUN_00064540(iter, actor_handle);
  prop = (char *)FUN_00064570(iter);
  while (prop != NULL) {
    *(int16_t *)(prop + 0xaa) = 0;
    *(int16_t *)(prop + 0xae) = 0;
    *(int16_t *)(prop + 0xac) = 0;
    prop = (char *)FUN_00064570(iter);
  }
}

/* actor_get_perception_knowledge (0x2fc20)
 * Evaluate whether an actor should engage a prop. Checks prop type,
 * visibility flags, and actor state to determine engagement eligibility.
 * Side effects: clears prop tracking fields when engagement drops,
 * and clears actor pursuit fields when target is lost. */
bool actor_get_perception_knowledge(int actor_handle, int prop_handle)
{
  char *actor;
  char *prop;
  short type;
  char result;

  actor = (char *)datum_get(actor_data, actor_handle);
  prop = (char *)datum_get(*(data_t **)0x5ab23c, prop_handle);
  type = *(short *)(prop + 0x24);
  result = 0;

  if (type > 1 && type < 4 && *(char *)(prop + 0x60) != 0 &&
      *(char *)(prop + 0x127) == 0) {
    if (*(short *)(prop + 0x9c) != 0 &&
        (*(int *)(actor + 0x270) == prop_handle ||
         *(char *)(actor + 0x1ed) == 0)) {
      result = 1;
    } else if ((*(char *)(prop + 0x135) != 0 || *(char *)(prop + 0x136) != 0) &&
               *(char *)(actor + 0x161) == 0 && *(char *)(actor + 0x202) == 0) {
      result = 1;
    } else if (*(short *)(prop + 0x10) == 0xf) {
      result = 1;
    }
  }

  if (*(char *)(prop + 0xa4) != 0 && result == 0) {
    *(uint16_t *)(prop + 0xaa) = 0;
    *(uint16_t *)(prop + 0xae) = 0;
    *(uint16_t *)(prop + 0xac) = 0;
  }

  if (type > 1 && type < 4 && result == 0 && *(short *)(actor + 0x3a8) > 0 &&
      *(int *)(actor + 0x3ac) == prop_handle) {
    *(uint16_t *)(actor + 0x3a8) = 0;
    *(int *)(actor + 0x3ac) = -1;
  }

  *(char *)(prop + 0xa4) = result;
  return result;
}

/* actor_compute_prop_target_weight (0x2fd10)
 * Compute a perception priority score for an actor evaluating a prop.
 * Returns 0.0f immediately if the prop is filtered out by various
 * early-exit conditions. Otherwise computes a score from a vision level,
 * an awareness level, a distance-based term, and optional bonuses.
 * Assertion: "prop_orphaned(prop)" at line 0x1086. */
float actor_compute_prop_target_weight(int actor_handle, int clump_item_handle)
{
  char *actor;
  char *prop;
  char *actr_tag;
  char *actv_tag;
  short vision_level; /* EDI in the binary */
  short awareness; /* EAX in the binary */
  short bonus_flag; /* [EBP-0x14], 0 or 1 */
  short extra_flag; /* [EBP-0x10], 0 or 2 */
  float local_c; /* [EBP-0xc], bonus addend (0.0f or 3.0f) */
  float actv_threshold;
  int sum;

  actor = (char *)datum_get(actor_data, actor_handle);
  prop = (char *)datum_get(*(data_t **)0x5ab23c, clump_item_handle);

  /* Early-exit conditions: return 0.0f */
  if (*(char *)(prop + 0x133) != 0)
    return 0.0f;
  if (*(char *)(prop + 0x60) == 0)
    return 0.0f;
  if (*(short *)(prop + 0x24) >= 0 && *(short *)(prop + 0x24) <= 1)
    return 0.0f;
  if (*(char *)(prop + 0x127) != 0 && *(short *)(prop + 0x76) >= 0x96)
    return 0.0f;
  if (*(short *)(prop + 0x10) == 0xf)
    return 0.0f;

  actr_tag = (char *)tag_get(0x61637472, *(int *)(actor + 0x58));
  actv_tag = (char *)tag_get(0x61637476, *(int *)(actor + 0x5c));

  bonus_flag = 0;
  extra_flag = 0;
  local_c = 0.0f;

  /* Compute vision_level (cVar4 / EDI) */
  if (*(char *)(actor + 6) != 0) {
    vision_level = 0;
  } else if (*(short *)(prop + 0x9c) > 0) {
    vision_level = 0;
  } else {
    if (actor_has_ranged_weapon(actor_handle) == 0) {
      /* Actor does not have a weapon in hand */
      if (*(char *)(actor + 0x378) != 0) {
        actv_threshold = *(float *)(actv_tag + 0x160);
      } else {
        actv_threshold = *(float *)(actv_tag + 0x170);
      }
      if (*(float *)(prop + 0x11c) < *(float *)0x253f40) {
        /* prop distance < 2.0f */
        vision_level = 5;
        if (*(short *)(prop + 0x24) != 5)
          goto done_vision;
      }
      /* prop distance >= 2.0f (or prop type == 5) */
      if (*(int *)(prop + 0x110) != -1) {
        vision_level = 0;
      } else if (*(char *)(prop + 0x130) != 0 &&
                 *(float *)(actr_tag + 0x38c) == 0.0f) {
        vision_level = 0;
      } else if (*(char *)(prop + 0x118) != *(char *)(actor + 0x15d)) {
        vision_level = 1;
      } else if (*(float *)(prop + 0x11c) < actv_threshold) {
        vision_level = 3;
      } else {
        vision_level = 2;
      }
    } else {
      /* Actor has a weapon in hand */
      char *weapon_tag = FUN_000210f0(actor_handle);
      char *actv_tag2 =
        actor_combat_get_firing_variant_definition(actor_handle);

      if (weapon_tag == 0 ||
          *(float *)(prop + 0x11c) >= *(float *)(weapon_tag + 0x40c)) {
        /* prop distance >= weapon range (or no weapon tag) */
        if (*(char *)(prop + 0x118) != *(char *)(actor + 0x15d)) {
          vision_level = 2;
        } else if (*(float *)(prop + 0x11c) < *(float *)0x253f40) {
          /* prop distance < 2.0f */
          vision_level = 5;
          if (*(short *)(prop + 0x24) != 5)
            goto done_vision;
        } else if (*(float *)(prop + 0x11c) < *(float *)(actv_tag2 + 0xa0)) {
          vision_level = 3;
        } else {
          vision_level = 2;
          if (*(float *)(prop + 0x11c) >= *(float *)(actv_tag2 + 0x74)) {
            vision_level = 1;
          }
        }
      } else {
        vision_level = 2;
      }
    }
  }
done_vision:

  /* Compute awareness (cVar5 / EAX) */
  if (*(char *)(prop + 0x127) != 0) {
    awareness = 1;
  } else if (*(char *)(actor + 6) == 0 && *(char *)(prop + 0x74) != 0 &&
             *(short *)(prop + 0x9c) == 0) {
    awareness = 6;
  } else {
    short prop_type = *(short *)(prop + 0x24);
    if (prop_type >= 2 && prop_type <= 3) {
      if (*(char *)(actor + 6) != 0) {
        awareness = 4;
      } else if (*(short *)(prop + 0x9c) > 0) {
        awareness = 3;
      } else if (*(short *)(prop + 0x38) != 0 && *(short *)(prop + 0x38) != 1) {
        awareness = 3;
      } else if (*(char *)(prop + 0x12f) != 0 && *(char *)(prop + 0x122) <= 1) {
        awareness = 5;
      } else {
        awareness = 4;
      }
    } else {
      if (prop_type < 4 || prop_type > 5) {
        assert_halt_msg(0, "prop_orphaned(prop)");
      }
      if (*(char *)(prop + 0xb8) != 0) {
        awareness = 3;
      } else {
        awareness = (*(short *)(prop + 0x24) == 4) + 1;
      }
    }
  }

  /* Bonus computations */
  if (*(int *)(actor + 0x270) == -1) {
    if (*(char *)(prop + 0x12e) != 0 ||
        clump_item_handle == *(int *)(actor + 0x54)) {
      local_c = 3.0f;
    }
  } else if (clump_item_handle == *(int *)(actor + 0x270) &&
             *(short *)(actor + 0x6e) > 2) {
    bonus_flag = 1;
  }

  if (*(char *)(prop + 0x134) != 0) {
    extra_flag = 2;
  }

  /* Final score computation:
   * score = (int)(bonus_flag + extra_flag + vision_level + awareness) * 10.0f
   *       + 5.0f / (prop->field_11c * 0.1f + 1.0f)
   *       + local_c
   */
  sum = (int)extra_flag + (int)bonus_flag + (int)vision_level + (int)awareness;
  return (float)sum * 10.0f + 5.0f / (*(float *)(prop + 0x11c) * 0.1f + 1.0f) +
         local_c;
}/* --- actor_perception.obj batch drafts (2026-07-26) --- */

/* 0x2f470 */
void actor_get_vision_distances(void)
{
  int eax = 0;

  datum_get((void *)0, 0);
  tag_get('rtca', 0);
  /* test (char)eax, 0x41 -> jne 0x2f4c2 */
  /* test (char)eax, 0x41 -> jne 0x2f4fc */
  /* test (char)eax, 0x41 -> jne 0x2f521 */

  (void)eax;
}

/* 0x2f5f0 */
void FUN_0002f5f0(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  datum_get((void *)0, 0);
  /* test (char)eax, 0x41 -> jne 0x2f6d3 */
  /* relift: cmp dword ptr [esi + 0x28c], edi -> je 0x2f6d3 */
  object_get_and_verify_type(0, 0);
  csmemset((void *)0, 0, 108);
  object_get_world_position(0, (void *)0);

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x2f6e0 */
void actor_perception_desire_prop(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;
  int ebp = 0;

  datum_get((void *)0, 0);
  /* cmp eax, -1 -> jne 0x2f706 */
  datum_get((void *)0, 0);
  /* test (char)ebx, (char)ebx -> je 0x2f73f */
  /* cmp (int16_t)ecx, 4 -> jl 0x2f73f */
  /* cmp (int16_t)ecx, 5 -> jg 0x2f73f */
  /* relift: cmp byte ptr [ebp + 0x1c], 0 -> je 0x2f74c */
  /* test eax, eax -> je 0x2f763 */
  /* relift: cmp byte ptr [eax + 8], 0 -> je 0x2f75c */
  /* relift: cmp byte ptr [eax + 0x13], 0 -> je 0x2f763 */
  /* cmp (int16_t)ecx, -1 -> jne 0x2f77e */
  /* test (char)eax, (char)eax -> jne 0x2f777 */
  /* relift: cmp word ptr [ebp + 0x34], 0 -> jle 0x2f77e */
  /* test (char)eax, 0x41 -> jne 0x2f795 */
  /* test (char)ebx, (char)ebx -> je 0x2f8a0 */
  datum_get((void *)0, 0);
  object_get_and_verify_type(0, 0);
  /* cmp ecx, edx -> jg 0x2f7d7 */
  /* cmp ecx, -1 -> je 0x2f7ed */
  /* cmp eax, -1 -> je 0x2f7eb */
  /* cmp eax, ecx -> jge 0x2f7ed */
  /* test (char)eax, (char)eax -> jne 0x2f806 */
  /* test (char)eax, (char)eax -> jne 0x2f806 */
  /* test (char)eax, (char)eax -> jne 0x2f806 */
  /* test (char)eax, (char)eax -> je 0x2f82c */
  /* test (char)eax, 0x41 -> jne 0x2f846 */
  /* test dl, dl -> je 0x2f859 */
  /* relift: cmp word ptr [ebp + 0x28], 0x96 -> jle 0x2f859 */
  actor_action_try_to_panic(0);
  /* cmp (int16_t)eax, 1 -> jle 0x2f872 */
  /* test (char)eax, (char)eax -> jne 0x2f88e */
  /* relift: cmp word ptr [edi + 0x6a], 3 -> jge 0x2f88e */
  /* relift: cmp word ptr [edi + 0x6e], 4 -> jl 0x2f8d1 */
  /* test (char)eax, (char)eax -> jne 0x2f8ef */
  /* test (char)eax, 0x41 -> je 0x2f8f3 */
  /* test eax, eax -> je 0x2f8ff */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)ebp;
}

/* 0x2fb60 */
void arctangent(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x300b0 */
void actor_situation_update_target_status(int actor_handle)
{
  int eax = 0;
  int esi = 0;

  datum_get((void *)0, 0);
  /* cmp eax, -1 -> jne 0x300f0 */
  datum_get((void *)0, 0);
  object_get_and_verify_type(0, 0);
  /* test (char)eax, (char)eax -> jne 0x30138 */
  display_assert((void *)0x0025601c, (void *)0x00255fb0, 4291, 0);
  system_exit(0);
  /* cmp eax, 5 -> ja 0x30219 */
  /* test (char)eax, (char)eax -> je 0x30185 */
  /* test (char)eax, (char)eax -> je 0x30196 */
  /* relift: cmp word ptr [esi + 0x32], 2 -> jl 0x301a7 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x301bd */
  /* cmp (int16_t)eax, 1 -> je 0x301bd */
  /* relift: cmp byte ptr [esi + 0x122], 2 -> jg 0x301e0 */
  /* test (char)eax, (char)eax -> je 0x301f8 */
  display_assert((char *)0, (void *)0x00255fb0, 4362, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 2 -> jl 0x3027a */
  /* cmp (int16_t)eax, 3 -> jg 0x3027a */
  /* relift: cmp word ptr [esi + 0x32], 0 -> jle 0x30291 */

  (void)eax;
  (void)esi;
}

/* 0x302b0 */
void actor_situation_combat_status_update(int actor_handle)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  datum_get((void *)0, 0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x3030a */
  /* cmp (int16_t)ecx, (int16_t)eax -> jge 0x302ed */
  /* cmp eax, ecx -> jg 0x302fe */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x3031c */
  /* cmp (int16_t)eax, 0xc -> jl 0x3033c */
  display_assert((void *)0x00256030, (void *)0x00255fb0, 4408, 0);
  system_exit(0);
  /* cmp eax, edi -> jle 0x3036b */
  /* relift: cmp word ptr [esi + 0x6a], 3 -> jge 0x30396 */
  /* cmp (int16_t)ecx, (int16_t)eax -> jne 0x303cd */
  /* cmp eax, -1 -> je 0x303bc */

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x303f0 */
void actor_situation_update(int actor_handle)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  datum_get((void *)0, 0);
  csmemset((void *)0, 0, 123);
  FUN_00064540((void *)0, 0);
  FUN_00064570((void *)0);
  /* test edi, edi -> je 0x3084a */
  /* cmp (int16_t)eax, 2 -> jl 0x3081b */
  /* cmp (int16_t)eax, 3 -> jg 0x3081b */
  /* test (char)eax, (char)eax -> jne 0x3081b */
  /* test (char)eax, (char)eax -> je 0x30621 */
  /* relift: cmp word ptr [edi + 0x9c], (int16_t)ecx -> jne 0x304d0 */
  /* test (char)eax, (char)eax -> je 0x304fb */
  /* test (char)eax, (char)eax -> je 0x3051e */
  /* relift: cmp byte ptr [edi + 0x122], 2 -> jg 0x305f1 */
  /* test dl, dl -> je 0x3057b */
  /* test (char)eax, (char)eax -> jne 0x3057b */
  /* relift: cmp byte ptr [edi + 0x122], 1 -> jg 0x305f1 */
  /* test (char)eax, (char)eax -> je 0x305a7 */
  /* test (char)eax, (char)eax -> jg 0x305f1 */
  /* test dl, dl -> je 0x305ce */
  /* test (char)eax, (char)eax -> je 0x305f1 */
  /* test (char)eax, (char)eax -> je 0x305f1 */
  /* relift: cmp word ptr [edi + 0x38], 0 -> jne 0x305f1 */
  object_get_and_verify_type(0, 0);
  /* cmp eax, -1 -> jne 0x30643 */
  datum_get((void *)0, 0);
  /* relift: cmp dword ptr [ebx + 0x1c8], -1 -> je 0x30669 */
  /* test eax, eax -> je 0x30677 */
  /* cmp (int16_t)ebx, 0x10 -> jl 0x306b8 */
  display_assert((void *)0x00256090, (void *)0x00255fb0, 4572, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x3072c */
  /* test eax, eax -> je 0x3072c */
  /* cmp eax, -1 -> je 0x3072c */
  /* relift: cmp dword ptr [ecx + 0x270], -1 -> je 0x3072c */
  datum_get((void *)0, 0);
  datum_get((void *)0, 0);
  /* cmp ecx, edx -> jne 0x3072c */
  /* test (int16_t)eax, (int16_t)eax -> je 0x3073b */
  /* cmp (int16_t)eax, 1 -> jne 0x30758 */
  /* test (char)eax, (char)eax -> je 0x307af */
  /* test (char)eax, (char)eax -> je 0x30795 */
  /* test (char)eax, (char)eax -> je 0x30795 */
  /* test (char)eax, (char)eax -> je 0x30795 */
  /* relift: cmp byte ptr [edi + 0x12d], 0 -> je 0x307af */
  /* test (char)ecx, (char)ecx -> je 0x307e5 */
  /* test (char)eax, (char)eax -> je 0x307c9 */
  /* test (char)ecx, (char)ecx -> je 0x307e5 */
  /* test dl, dl -> je 0x3081b */
  /* test (char)eax, (char)eax -> je 0x307ff */
  /* test (char)ecx, (char)ecx -> je 0x3081b */
  /* test (char)eax, 0x41 -> jne 0x30834 */
  FUN_00064570((void *)0);
  /* test edi, edi -> jne 0x30470 */
  /* cmp ebx, edi -> je 0x308c5 */
  datum_get((void *)0, 0);
  actor_compute_prop_target_weight(0, 0);
  /* cmp ebx, -1 -> je 0x308c8 */
  datum_get((void *)0, 0);
  actor_compute_prop_target_weight(0, 0);
  actor_situation_update_target_status(0);
  actor_situation_combat_status_update(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x308e0 */
void actor_situation_try_new_target(int actor_handle, int target)
{
  int eax = 0;

  datum_get((void *)0, 0);
  datum_get((void *)0, 0);
  /* cmp eax, -1 -> jne 0x30921 */
  datum_get((void *)0, 0);
  actor_compute_prop_target_weight(0, 0);
  /* test (char)eax, 0x41 -> jne 0x309bf */
  /* test (char)eax, (char)eax -> jne 0x30977 */
  display_assert((void *)0x002560cc, (void *)0x00255fb0, 4685, 0);
  system_exit(0);
  /* test eax, eax -> je 0x3098b */
  /* test (char)eax, 1 -> jne 0x309bf */
  actor_situation_update_target_status(0);
  actor_situation_combat_status_update(0);

  (void)eax;
}

/* 0x309d0 */
char actor_perception_friend_prop_is_attacking(int actor_handle, int iter_handle, float *out_pos)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  datum_get((void *)0, 0);
  datum_get((void *)0, 0);
  /* cmp (int16_t)eax, 2 -> jl 0x30a20 */
  /* cmp (int16_t)eax, 3 -> jg 0x30a20 */
  /* test (char)eax, (char)eax -> jne 0x30a20 */
  /* test (char)eax, (char)eax -> je 0x30a40 */
  display_assert((void *)0x002560e0, (void *)0x00255fb0, 4712, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x30b75 */
  /* test (char)eax, (char)eax -> je 0x30b59 */
  unit_scripting_unit_driver(0, (void *)0);
  /* test (char)eax, (char)eax -> jne 0x30b49 */
  /* test (char)ecx, (char)ecx -> jle 0x30b49 */
  FUN_00064540((void *)0, 0);
  FUN_00064570((void *)0);
  /* test eax, eax -> je 0x30b46 */
  /* cmp (int16_t)ecx, 2 -> jl 0x30b32 */
  /* cmp (int16_t)ecx, 3 -> jg 0x30b32 */
  /* test (char)ecx, (char)ecx -> je 0x30b32 */
  normalize3d((void *)0);
  /* test (char)eax, 0x41 -> jne 0x30b32 */
  /* test (char)eax, 0x41 -> je 0x30b50 */
  FUN_00064570((void *)0);
  /* test eax, eax -> jne 0x30ab0 */
  /* cmp esi, -1 -> je 0x30b75 */
  FUN_0003b190(0, (void *)0);
  return 0;

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x30b80 */
void actor_perception_aiming_vector_test_blockage(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x30d10 */
unsigned int FUN_00030d10(int actor_handle, float *chance_inout)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  datum_get((void *)0, 0);
  FUN_00064540((void *)0, 0);
  FUN_00064570((void *)0);
  /* test esi, esi -> je 0x30df4 */
  /* cmp (int16_t)eax, 2 -> jl 0x30db4 */
  /* cmp (int16_t)eax, 3 -> jg 0x30db4 */
  /* test (char)eax, (char)eax -> jne 0x30db4 */
  /* relift: cmp (int16_t)eax, word ptr [ebx + 4] -> jne 0x30db4 */
  /* cmp eax, -1 -> je 0x30db4 */
  datum_get((void *)0, 0);
  /* relift: cmp word ptr [eax + 0x308], 0 -> jg 0x30db1 */
  /* relift: cmp word ptr [eax + 0x6c], 4 -> jne 0x30da4 */
  /* relift: cmp word ptr [eax + 0xa8], 0 -> jg 0x30db1 */
  /* test (char)eax, (char)eax -> je 0x30db4 */
  FUN_00064570((void *)0);
  /* test esi, esi -> jne 0x30d50 */
  /* relift: cmp word ptr [ebp - 4], 1 -> jle 0x30dd6 */
  /* cmp (int16_t)edi, 1 -> jle 0x30df4 */
  /* test (char)eax, 0x41 -> jne 0x30e4a */
  return 0;

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x30e60 */
void FUN_00030e60(void)
{
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test (int16_t)edx, (int16_t)edx -> jle 0x30e9c */
  /* relift: cmp dword ptr [ebx + esi + 8], edi -> je 0x30e94 */
  /* cmp (int16_t)ecx, (int16_t)edx -> jl 0x30e80 */
  /* relift: cmp (int16_t)edx, word ptr [ebp + 0x10] -> jge 0x30ed6 */
  datum_get((void *)0, 0);
  /* cmp (int16_t)edx, 2 -> jl 0x30f43 */
  /* cmp (int16_t)edx, 3 -> jg 0x30f43 */
  /* test dl, dl -> je 0x30f43 */
  /* test dl, dl -> je 0x30f1b */
  /* test dl, dl -> je 0x30f37 */
  /* relift: cmp word ptr [ecx + 0x32], 2 -> jl 0x30f43 */

  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x30f50 */
void FUN_00030f50(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  datum_get((void *)0, 0);
  tag_get('rtca', 0);
  FUN_00064540((void *)0, 0);
  FUN_00064570((void *)0);
  datum_get((void *)0, 0);
  /* cmp (int16_t)ecx, 2 -> jl 0x31076 */
  /* cmp (int16_t)ecx, 3 -> jg 0x31076 */
  /* test (char)ecx, (char)ecx -> je 0x31076 */
  /* test (char)ecx, (char)ecx -> je 0x30ff7 */
  /* test (char)ecx, (char)ecx -> je 0x31016 */
  /* relift: cmp word ptr [eax + 0x32], 2 -> jl 0x31076 */
  FUN_00030e60();
  /* cmp (int16_t)eax, 0xffff -> je 0x311cb */
  /* cmp (int16_t)eax, 2 -> jl 0x311ce */
  /* cmp (int16_t)eax, 3 -> jg 0x311ce */
  /* test (char)eax, (char)eax -> jne 0x311ce */
  /* cmp ecx, -1 -> je 0x311ce */
  datum_get((void *)0, 0);
  /* relift: cmp word ptr [eax + 0x3a8], 0 -> je 0x311ce */
  /* cmp ecx, -1 -> je 0x311ce */
  /* cmp edx, -1 -> je 0x31103 */
  /* relift: cmp dword ptr [eax + 0x3b0], edx -> jl 0x311ce */
  datum_get((void *)0, 0);
  prop_get_active_by_unit_index(0, 0);
  datum_get((void *)0, 0);
  /* cmp (int16_t)eax, 2 -> jl 0x311cb */
  /* cmp (int16_t)eax, 3 -> jg 0x311cb */
  /* test (char)eax, (char)eax -> je 0x311cb */
  FUN_00030e60();
  /* cmp (int16_t)eax, 0xffff -> je 0x311cb */
  /* relift: cmp dword ptr [ecx + 4], -1 -> jne 0x311cb */
  FUN_00064570((void *)0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x31377 */
  /* test (char)ecx, (char)ecx -> je 0x31229 */
  /* test dl, dl -> je 0x31248 */
  /* test (int16_t)ecx, (int16_t)ecx -> jle 0x31248 */
  /* cmp (int16_t)eax, (int16_t)ecx -> jle 0x31248 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x3125c */
  /* relift: cmp word ptr [ebx], (int16_t)eax -> jl 0x3125c */
  /* test dl, dl -> je 0x31260 */
  /* test dl, dl -> je 0x31269 */
  /* relift: cmp word ptr [esi + 0xaa], 0 -> jle 0x312c3 */
  /* relift: cmp word ptr [esi + 0xac], 0 -> jne 0x312b5 */
  get_global_random_seed_address();
  random_real_range((void *)0, 0.0f, 0.0f);
  FUN_001d9068();
  /* relift: cmp word ptr [esi + 0x78], 0x2d -> jge 0x312d4 */
  /* relift: cmp word ptr [ebx], 4 -> jl 0x31367 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x312fd */
  /* relift: cmp word ptr [esi + 0xac], (int16_t)eax -> jl 0x312fd */
  /* test (char)eax, (char)eax -> je 0x31318 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x31341 */
  /* relift: cmp word ptr [esi + 0xa6], (int16_t)eax -> jl 0x31341 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x31367 */
  /* relift: cmp word ptr [ebx + 0x10], (int16_t)eax -> jl 0x31367 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x313ab */
  game_time_get();
  /* cmp (int16_t)edx, (int16_t)esi -> jle 0x313de */
  /* cmp eax, -1 -> je 0x313de */
  /* cmp ebx, -1 -> je 0x31438 */
  get_global_random_seed_address();
  random_real_range((void *)0, 0.0f, 0.0f);
  FUN_001d9068();
  game_time_get();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x31440 */
void actor_berserk(int actor_handle, int berserk_flag)
{
  int eax = 0;
  int ebx = 0;

  datum_get((void *)0, 0);
  /* cmp (char)ebx, (char)eax -> je 0x314ab */
  /* cmp eax, -1 -> je 0x314a0 */
  object_get_and_verify_type(0, 0);
  /* cmp eax, -1 -> jne 0x31483 */
  /* test (char)ebx, (char)ebx -> je 0x314ab */
  object_get_and_verify_type(0, 0);
  /* test (char)ebx, (char)ebx -> je 0x314d5 */

  (void)eax;
  (void)ebx;
}

/* 0x314f0 */
void actor_visibility_at_point(void)
{
  int eax = 0;
  int ecx = 0;
  int ebp = 0;

  /* cmp (int16_t)ecx, 1 -> jne 0x31836 */
  datum_get((void *)0, 0);
  tag_get('rtca', 0);
  actor_combat_get_firing_variant_definition(0);
  /* test (char)eax, 0x41 -> jne 0x3155c */
  display_assert((void *)0x00255ee8, (void *)0x00255fb0, 1268, 0);
  system_exit(0);
  FUN_0018e690();
  /* test (char)eax, 0x41 -> je 0x31681 */
  /* test (char)eax, 0x41 -> jne 0x31671 */
  /* test (char)eax, 0x41 -> je 0x31688 */
  /* test (char)eax, (char)eax -> je 0x316c2 */
  game_time_get();
  /* test (char)eax, (char)eax -> jne 0x317c8 */
  /* test (char)eax, (char)eax -> je 0x317c8 */
  /* test (char)eax, 0x41 -> je 0x317b7 */
  actor_get_vision_distances();
  /* relift: cmp word ptr [ebp + 0x18], 0 -> jne 0x31814 */
  /* test (char)eax, 0x41 -> jne 0x31814 */

  (void)eax;
  (void)ecx;
  (void)ebp;
}

/* 0x31850 */
int actor_audibility_at_point(int actor_handle, void *input_block, float *position, void *location, short volume, int range_scale, short flags)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int edi = 0;

  datum_get((void *)0, 0);
  tag_get('rtca', 0);
  /* relift: cmp word ptr [edi + 0x28], -1 -> je 0x31a80 */
  /* relift: cmp word ptr [edx + 4], -1 -> je 0x31a80 */
  /* cmp (int16_t)ebx, 2 -> jne 0x31921 */
  /* cmp (int16_t)ebx, 1 -> jne 0x31933 */
  /* cmp (int16_t)eax, 4 -> jne 0x31948 */
  /* cmp (int16_t)eax, 1 -> jne 0x31959 */
  /* cmp (int16_t)eax, 3 -> jne 0x3196b */
  FUN_0018e5c0(0);
  /* test (char)eax, (char)eax -> jne 0x3198b */
  FUN_0018e5c0(0);
  /* test (char)eax, (char)eax -> je 0x31997 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x319b2 */
  /* cmp (int16_t)eax, 1 -> je 0x319b2 */
  /* test (char)eax, 0x41 -> jne 0x31a31 */
  scenario_get();
  structure_bsp_cluster_sound_encoding((void *)0, 0, 0);
  /* test (char)eax, 0x41 -> je 0x31a15 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)edi;
}

/* 0x31a90 */
void actor_perception_find_sense_position(int actor_handle, float *position, int param_3, void *input_block_out)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  datum_get((void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x31be5 */
  datum_get((void *)0, 0);
  display_assert((void *)0x00256190, (void *)0x00255fb0, 1637, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0x24], edi -> jne 0x31b24 */
  display_assert((void *)0x00256168, (void *)0x00255fb0, 1638, 0);
  system_exit(0);
  datum_get((void *)0, 0);
  /* relift: cmp dword ptr [ebp - 8], -1 -> jne 0x31bca */
  display_assert((void *)0x00256150, (void *)0x00255fb0, 1655, 0);
  system_exit(0);
  FUN_0003bde0(0, 0, (char *)0);

  (void)eax;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x31c00 */
void actor_perception_unit_from_swarm(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

  datum_get((void *)0, 0);
  display_assert((void *)0x002561f4, (void *)0x00255fb0, 1677, 0);
  system_exit(0);
  /* cmp eax, -1 -> je 0x31d21 */
  datum_get((void *)0, 0);
  datum_get((void *)0, 0);
  /* relift: cmp dword ptr [ebx + esi*4 + 0x18], edx -> jne 0x31cdf */
  /* test (char)eax, (char)eax -> je 0x31d0b */
  object_mark(0);
  object_get_and_verify_type(0, 0);
  object_get_world_position(0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x31da4 */
  object_mark(0);
  /* cmp esi, -1 -> jne 0x31d34 */
  /* relift: cmp dword ptr [ebp + 0xc], -1 -> je 0x31ddc */
  /* cmp esi, -1 -> jne 0x31ddc */
  display_assert((void *)0x002561b4, (void *)0x00255fb0, 1753, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)ebp;
}

/* 0x31df0 */
void prop_position_refresh(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  datum_get((void *)0, 0);
  datum_get((void *)0, 0);
  object_get_and_verify_type(0, 0);
  /* cmp (int16_t)eax, 4 -> jl 0x31edc */
  /* cmp (int16_t)eax, 5 -> jg 0x31edc */
  /* test (char)eax, (char)eax -> jne 0x320f9 */
  /* relift: test byte ptr [edi + 0xb6], 4 -> je 0x31ea0 */
  /* relift: cmp word ptr [edi + 0x3d0], 0 -> jne 0x31ea0 */
  /* relift: cmp word ptr [esi + 0x30], 0 -> jne 0x31ea0 */
  FUN_00012170((void *)0);
  /* relift: cmp dword ptr [edx + 0x270], ebx -> jne 0x31ec9 */
  /* test (char)ecx, (char)ecx -> je 0x320f9 */
  /* test (char)ecx, (char)ecx -> je 0x320f9 */
  /* test (char)eax, (char)eax -> je 0x320f9 */
  /* test (char)eax, (char)eax -> je 0x31f77 */
  /* relift: cmp dword ptr [esi + 0x1c], -1 -> je 0x31f77 */
  /* test (char)eax, (char)eax -> je 0x31f77 */
  game_time_get();
  /* cmp ecx, eax -> jg 0x31f77 */
  actor_perception_unit_from_swarm();
  /* cmp eax, ecx -> je 0x31f74 */
  object_get_and_verify_type(0, 0);
  /* cmp (int16_t)eax, 4 -> jl 0x31f56 */
  /* cmp (int16_t)eax, 5 -> jg 0x31f56 */
  /* cmp eax, -1 -> je 0x31f74 */
  datum_get((void *)0, 0);
  unit_get_head_position(0, (void *)0);
  object_get_world_position(0, (void *)0);
  FUN_001a9520(0, (void *)0);
  object_get_root_parent(0);
  object_get_and_verify_type(0, 0);
  FUN_0018f3e0((void *)0, (void *)0, (void *)0);
  /* cmp eax, ebx -> je 0x320bc */
  object_get_and_verify_type(0, 0);
  /* cmp (int16_t)ecx, 1 -> jne 0x320a5 */
  /* relift: cmp dword ptr [eax + 0x2d8], ecx -> je 0x32068 */
  /* relift: cmp word ptr [esi + 0x10], 0xf -> je 0x32068 */
  /* relift: cmp dword ptr [eax + 0x2d4], ecx -> jne 0x3209b */
  vehicle_hover();
  /* test (char)eax, (char)eax -> je 0x3209b */
  /* test (char)eax, 3 -> je 0x320bc */
  /* cmp eax, ebx -> je 0x320f9 */
  object_get_and_verify_type(0, 0);
  /* test dl, 3 -> je 0x320ef */
  /* cmp eax, ebx -> jne 0x320d0 */
  actor_perception_find_sense_position(0, (void *)0, 0, (void *)0);
  normalize3d((void *)0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x32170 */
void FUN_00032170(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  datum_get((void *)0, 0);
  /* cmp ecx, -1 -> jne 0x32370 */
  object_get_and_verify_type(0, 0);
  tag_get('ihev', 0);
  object_get_world_position(0, (void *)0);
  /* test edi, edi -> jne 0x3222c */
  actor_perception_find_sense_position(0, (void *)0, 0, (void *)0);
  /* test (char)eax, 0x41 -> jne 0x3236e */
  /* relift: cmp dword ptr [esi + 0x28c], ecx -> je 0x3236e */
  csmemset((void *)0, 0, 108);
  object_get_and_verify_type(0, 0);
  game_allegiance_get_team_is_friendly(0, 0);
  /* test (char)eax, (char)eax -> jne 0x32365 */

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x32380 */
void actor_perception_refresh_danger_zone(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int ebp = 0;

  datum_get((void *)0, 0);
  /* relift: cmp word ptr [esi + 0x280], 0 -> jle 0x3293b */
  object_try_and_get_and_verify_type(0, 0);
  /* cmp (int16_t)eax, 2 -> je 0x3240b */
  /* cmp (int16_t)eax, 3 -> je 0x3240b */
  /* cmp (int16_t)eax, 1 -> je 0x3240b */
  display_assert((void *)0x00256248, (void *)0x00255fb0, 3227, 0);
  system_exit(0);
  object_get_world_position(0, (void *)0);
  actor_perception_find_sense_position(0, (void *)0, 0, (void *)0);
  tag_get('ihev', 0);
  FUN_00012170((void *)0);
  /* cmp eax, -1 -> je 0x325ee */
  prop_get_active_by_unit_index(0, 0);
  /* cmp eax, -1 -> je 0x325ee */
  datum_get((void *)0, 0);
  /* cmp eax, -1 -> jne 0x325fa */
  datum_get((void *)0, 0);
  /* test eax, eax -> je 0x32623 */
  /* test (char)ecx, (char)ecx -> je 0x32623 */
  /* relift: cmp dword ptr [ebx + 0xcc], -1 -> je 0x32645 */
  object_get_root_parent(0);
  object_get_and_verify_type(0, 0);
  ai_test_line_of_sight((void *)0, 0, (void *)0, 0, 0, 0, 0, 0);
  /* test (char)eax, (char)eax -> jne 0x326b8 */
  FUN_0002f380(0, 0);
  actor_visibility_at_point();
  /* cmp (int16_t)eax, 2 -> jl 0x326b8 */
  actor_audibility_at_point(0, (void *)0, (void *)0, (void *)0, 0, 0x3f800000, 0);
  /* cmp (int16_t)eax, 2 -> jl 0x32927 */
  /* relift: cmp dword ptr [ebx + 0xcc], eax -> jne 0x32718 */
  /* relift: cmp word ptr [ebx + 0x64], 5 -> je 0x3273f */
  display_assert((void *)0x00256210, (void *)0x00255fb0, 3257, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> jne 0x3278d */
  /* test (char)eax, 0x41 -> jne 0x3278d */
  /* test (char)eax, (char)eax -> jne 0x326af */
  /* test (char)eax, (char)eax -> jne 0x326af */
  datum_get((void *)0, 0);
  /* relift: cmp word ptr [esi + 0x6a], 1 -> je 0x32927 */
  /* test eax, eax -> je 0x327e9 */
  /* test (char)ecx, (char)ecx -> jne 0x32927 */
  tag_get('jorp', 0);
  object_get_root_parent(0);
  object_get_and_verify_type(0, 0);
  ai_test_line_of_sight((void *)0, 0, (void *)0, 0, 0, 0, 0, 0);
  FUN_0002f380(0, 0);
  actor_visibility_at_point();
  /* cmp (int16_t)eax, 2 -> jl 0x32927 */
  prop_get_active_by_unit_index(0, 0);
  /* cmp eax, -1 -> je 0x328d3 */
  datum_get((void *)0, 0);
  unit_get_animation_frames_remaining(0, (void *)0);
  /* relift: cmp word ptr [ebp - 6], 0x19 -> jne 0x328f2 */
  /* test (char)eax, (char)eax -> je 0x32927 */
  /* test (char)eax, (char)eax -> jne 0x32927 */
  FUN_00027a60(0, 12, 0, (void *)0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)ebp;
}

/* 0x32940 */
void actor_expected_acknowledgement(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

  datum_get((void *)0, 0);
  datum_get((void *)0, 0);
  /* cmp (int16_t)eax, 4 -> jl 0x3299f */
  /* cmp (int16_t)eax, 5 -> jg 0x3299f */
  display_assert((void *)0x00256318, (void *)0x00255fb0, 3618, 0);
  system_exit(0);
  FUN_00064540((void *)0, 0);
  FUN_00064570((void *)0);
  /* test ecx, ecx -> je 0x32ab1 */
  /* relift: cmp dword ptr [ebp - 8], edx -> je 0x32a9b */
  /* relift: cmp eax, dword ptr [esi + 0x18] -> je 0x32a16 */
  /* relift: cmp edx, dword ptr [esi + 0x1c] -> je 0x32a16 */
  /* test (char)eax, (char)eax -> je 0x32a9b */
  /* test (char)eax, (char)eax -> je 0x32a9b */
  /* cmp (int16_t)eax, 4 -> jl 0x32a02 */
  /* cmp (int16_t)eax, 5 -> jle 0x32a16 */
  /* cmp (int16_t)eax, 2 -> jl 0x32a9b */
  /* cmp (int16_t)eax, 3 -> jg 0x32a9b */
  /* test (char)eax, 0x41 -> jne 0x32a9b */
  FUN_00064570((void *)0);
  /* test ecx, ecx -> jne 0x329c0 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)ebp;
}

/* 0x32ac0 */
void actor_perception_unreachable(int actor_handle, int leader_handle, char flag)
{
  int eax = 0;
  int esi = 0;

  datum_get((void *)0, 0);
  datum_get((void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x32b11 */
  /* relift: cmp word ptr [esi + 0x9c], 0 -> jne 0x32b04 */
  game_time_get();
  actor_get_perception_knowledge(0, 0);
  actor_compute_prop_target_weight(0, 0);

  (void)eax;
  (void)esi;
}

/* 0x32b50 */
void actor_perception_tried_to_uncover(int actor_handle, int prop_handle)
{
  int eax = 0;
  int esi = 0;

  /* cmp esi, -1 -> je 0x32ba1 */
  datum_get((void *)0, 0);
  datum_get((void *)0, 0);
  /* cmp esi, eax -> jne 0x32b9f */
  actor_situation_update_target_status(0);
  actor_situation_combat_status_update(0);

  (void)eax;
  (void)esi;
}

/* 0x32bb0 */
void actor_perception_tried_to_search(int actor_handle, int prop_handle)
{
  int eax = 0;
  int esi = 0;

  /* cmp esi, -1 -> je 0x32c01 */
  datum_get((void *)0, 0);
  datum_get((void *)0, 0);
  /* cmp esi, eax -> jne 0x32bff */
  actor_situation_update_target_status(0);
  actor_situation_combat_status_update(0);

  (void)eax;
  (void)esi;
}

/* 0x32c10 */
void actor_perception_abandoned_search(int actor_handle, int prop_handle)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* cmp esi, -1 -> jne 0x32c54 */
  datum_get((void *)0, 0);
  actor_situation_combat_status_update(0);
  datum_get((void *)0, 0);
  datum_get((void *)0, 0);
  /* relift: cmp word ptr [eax + 0x24], 4 -> jne 0x32c85 */
  /* relift: cmp esi, dword ptr [edi + 0x270] -> jne 0x32ca3 */
  actor_situation_update_target_status(0);
  actor_situation_combat_status_update(0);

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x32cb0 */
void actor_emotion_update(int actor_handle)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  datum_get((void *)0, 0);
  tag_get('rtca', 0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x32d10 */
  /* relift: cmp word ptr [esi + 0x6a], (int16_t)edi -> jl 0x32d10 */
  /* relift: cmp dword ptr [esi + 0x1bc], 0x3f800000 -> jne 0x32d1e */
  /* cmp (int16_t)eax, (int16_t)edi -> jge 0x32d1e */
  actor_berserk(0, 0);
  /* relift: cmp byte ptr [esi + 0x374], (char)eax -> je 0x32d58 */
  FUN_00046f10(0, 0, 0, 0, 0, 0, 0);
  /* test (char)eax, (char)eax -> jne 0x32d6d */
  /* test (char)eax, 8 -> jne 0x32d6d */
  /* relift: test dword ptr [ebx], 0x1000000 -> je 0x32da5 */
  /* test (char)eax, (char)eax -> jne 0x32da5 */
  /* relift: cmp byte ptr [edx + esi + 0x1ee], 0 -> jg 0x32dc3 */
  /* test (int16_t)eax, (int16_t)eax -> jg 0x32db0 */
  /* cmp (int16_t)eax, 8 -> jl 0x32dd5 */
  /* cmp (int16_t)eax, 7 -> jl 0x32de7 */
  /* cmp (int16_t)eax, 6 -> jl 0x32df9 */
  /* cmp (int16_t)eax, 5 -> jl 0x32e0b */
  /* cmp (int16_t)eax, (int16_t)edi -> jl 0x32e1c */
  /* relift: test dword ptr [ebx], 0xc0000000 -> je 0x3314b */
  /* cmp ecx, -1 -> jne 0x3312f */
  /* relift: cmp word ptr [esi + 0x6e], (int16_t)edi -> jl 0x3312f */
  datum_get((void *)0, 0);
  FUN_00064540((void *)0, 0);
  FUN_00064570((void *)0);
  /* test edi, edi -> je 0x3314b */
  /* cmp (int16_t)eax, 2 -> jl 0x33114 */
  /* cmp (int16_t)eax, 3 -> jg 0x33114 */
  /* test (char)eax, (char)eax -> jne 0x33114 */
  /* test (char)eax, (char)eax -> jne 0x33114 */
  /* test (char)eax, (char)eax -> jne 0x33114 */
  /* test (char)eax, (char)eax -> jne 0x32f65 */
  /* relift: cmp dword ptr [edi + 0x110], -1 -> jne 0x33114 */
  actor_perception_friend_prop_is_attacking(0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x330e4 */
  actor_perception_aiming_vector_test_blockage();
  /* cmp (int16_t)ebx, 1 -> jl 0x32fbf */
  /* test (char)eax, (char)eax -> je 0x32fbf */
  /* test (char)eax, (char)eax -> je 0x330e4 */
  /* test (char)eax, (char)eax -> je 0x330e4 */
  FUN_00012170((void *)0);
  /* test (char)eax, (char)eax -> jne 0x3301c */
  /* relift: cmp word ptr [esi + 0x360], 0 -> jle 0x330e4 */
  normalize3d((void *)0);
  /* test (char)eax, 0x41 -> jne 0x330e4 */
  vector3d_scale_add((void *)0, (void *)0, 0.0f, (void *)0);
  actor_perception_aiming_vector_test_blockage();
  /* cmp (int16_t)eax, (int16_t)ebx -> jg 0x33089 */
  /* cmp (int16_t)eax, 1 -> jl 0x330e4 */
  FUN_00012170((void *)0);
  /* test (char)eax, 0x41 -> jne 0x330e4 */
  /* test (char)eax, (char)eax -> je 0x33114 */
  actor_perception_aiming_vector_test_blockage();
  /* cmp (int16_t)eax, 2 -> jl 0x33114 */
  FUN_00064570((void *)0);
  /* test edi, edi -> jne 0x32f12 */
  /* test (char)eax, (char)eax -> je 0x33178 */
  FUN_00024be0(0, 0, 0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x3318e */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x331a9 */
  /* test (char)eax, (char)eax -> je 0x331c8 */
  /* test (char)eax, (char)eax -> jne 0x331c8 */
  /* cmp eax, 4 -> ja 0x33243 */
  /* test (char)eax, 0x41 -> jne 0x33243 */
  /* test (char)eax, 0x41 -> jne 0x33243 */
  /* test (char)eax, (char)eax -> jle 0x33243 */
  FUN_00038370(0);
  /* relift: test dword ptr [ebx], 0x40000000 -> je 0x33271 */
  /* test (char)ecx, (char)ecx -> jne 0x3326f */
  /* test (char)ecx, (char)ecx -> je 0x33265 */
  /* test (char)ecx, (char)ecx -> je 0x33271 */
  /* test (char)ecx, (char)ecx -> je 0x332a4 */
  /* test (char)eax, (char)eax -> jne 0x332a0 */
  /* test (char)eax, 0x41 -> jne 0x332dc */
  /* test (char)ecx, (char)ecx -> jne 0x332e5 */
  /* test (char)eax, (char)eax -> je 0x332e5 */
  /* test (char)eax, 0x41 -> jne 0x332dc */
  FUN_001d9068();
  /* test (int16_t)eax, (int16_t)eax -> jle 0x332fb */
  FUN_00030f50();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x33330 */
void actor_perception_become_acknowledged(int actor_handle, int prop_handle, int param_3)
{
  int eax = 0;
  int ecx = 0;

  datum_get((void *)0, 0);
  /* cmp (int16_t)ecx, 2 -> jl 0x33364 */
  /* cmp (int16_t)ecx, 3 -> jle 0x33431 */
  actor_expected_acknowledgement();
  /* test (char)eax, (char)eax -> je 0x33413 */
  datum_get((void *)0, 0);
  FUN_0003b410(0, 0, 0);
  prop_iterator_next(0, 0);
  actor_perception_acknowledge(0, 0, 0, 0);

  (void)eax;
  (void)ecx;
}

/* 0x33440 */
void prop_status_refresh(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  datum_get((void *)0, 0);
  tag_get('rtca', 0);
  /* cmp eax, -1 -> jne 0x3348f */
  datum_get((void *)0, 0);
  datum_get((void *)0, 0);
  object_get_and_verify_type(0, 0);
  game_time_get();
  /* test eax, eax -> je 0x334e0 */
  /* test (char)eax, (char)eax -> jne 0x334eb */
  game_connection();
  /* test (int16_t)eax, (int16_t)eax -> jne 0x33525 */
  /* test (char)eax, (char)eax -> je 0x33525 */
  /* test (char)eax, (char)eax -> je 0x335bd */
  /* test (char)eax, (char)eax -> je 0x335bd */
  /* cmp eax, -1 -> je 0x335bd */
  /* relift: cmp dword ptr [ebx + 0x1d8], -1 -> je 0x335bd */
  datum_get((void *)0, 0);
  /* test edx, 0xffff -> jne 0x335bd */
  /* relift: cmp (int16_t)edx, word ptr [eax + 0x3a] -> jne 0x335bd */
  object_get_root_location(0, (void *)0, (void *)0);
  /* cmp (int16_t)eax, 2 -> jl 0x3374c */
  /* cmp (int16_t)eax, 3 -> jg 0x3374c */
  /* cmp (int16_t)edi, 1 -> jg 0x3374c */
  /* relift: cmp byte ptr [esi + 0x123], 1 -> jle 0x3374c */
  FUN_00027a60(0, 0, 0, (void *)0);
  unit_scripting_unit_driver(0, (void *)0);
  /* test (char)eax, 1 -> jne 0x33824 */
  /* test (char)eax, 0x41 -> je 0x338b8 */
  /* test (char)eax, 0x41 -> je 0x338ad */
  /* test (char)eax, 0x41 -> jne 0x3388b */
  /* test (char)eax, 0x41 -> jne 0x338a4 */
  /* cmp (int16_t)eax, 5 -> jg 0x3399d */
  /* test (char)eax, (char)eax -> je 0x338ff */
  /* test (char)eax, (char)eax -> je 0x338ff */
  ai_test_line_of_sight((void *)0, 0, (void *)0, 0, 0, 0, 0, 0);
  /* test (char)ecx, (char)ecx -> jne 0x33986 */
  actor_visibility_at_point();
  /* test (char)eax, (char)eax -> je 0x339b9 */
  ai_test_line_of_sight((void *)0, 0, (void *)0, 0, 0, 0, 0, 0);
  tag_get('dpib', 0);
  /* test (char)eax, 0x41 -> jne 0x33a51 */
  /* relift: cmp word ptr [edi + 0x3d0], 0 -> jne 0x33a86 */
  /* test (char)eax, (char)eax -> je 0x33a9d */
  /* test (char)ecx, (char)ecx -> jne 0x33a9d */
  /* test (char)ecx, (char)ecx -> jne 0x33aca */
  /* relift: cmp word ptr [edx + 0x6a], 3 -> jge 0x33aca */
  /* test (char)eax, (char)eax -> je 0x33ad4 */
  /* cmp ebx, -1 -> je 0x33ae3 */
  /* relift: cmp ebx, dword ptr [esi + 0x1c] -> je 0x33b19 */
  datum_get((void *)0, 0);
  /* cmp ebx, -1 -> jne 0x33b6f */
  /* test (char)ecx, (char)ecx -> jne 0x33bfa */
  /* test (char)eax, (char)eax -> je 0x33bba */
  actor_is_noncombat(0);
  FUN_0003b120(0);
  actor_is_fighting(0);
  /* test (char)ebx, (char)ebx -> je 0x33b2f */
  /* test (char)ecx, (char)ecx -> jne 0x33b2f */
  /* test (char)ecx, (char)ecx -> jne 0x33b2f */
  /* relift: cmp word ptr [edi + 0x6a], 3 -> jge 0x33b32 */
  FUN_0002f380(0, 0);
  actor_visibility_at_point();
  /* cmp (int16_t)eax, 2 -> jge 0x33c08 */
  /* test (char)eax, (char)eax -> je 0x33c29 */
  game_connection();
  /* test (int16_t)eax, (int16_t)eax -> jne 0x33c3f */
  /* test (char)eax, (char)eax -> jne 0x33c5c */
  game_connection();
  /* test (int16_t)eax, (int16_t)eax -> jne 0x33c5e */
  /* test (char)eax, (char)eax -> je 0x33c5e */
  /* test (char)eax, (char)eax -> je 0x33c5e */
  /* test (char)eax, (char)eax -> je 0x33ccd */
  /* test (char)eax, (char)eax -> jne 0x33cd1 */
  /* test (char)eax, (char)eax -> je 0x33c8c */
  /* test (char)eax, 0x41 -> je 0x33cd1 */
  /* relift: cmp word ptr [edi + 4], 0xf -> je 0x33cf6 */
  /* test (char)eax, (char)eax -> jne 0x33ce6 */
  /* test (char)eax, (char)eax -> jne 0x33cc7 */
  /* test (char)eax, (char)eax -> je 0x33cfa */
  /* test (char)ebx, (char)ebx -> je 0x33c8c */
  /* cmp (int16_t)eax, 2 -> jl 0x33cfa */
  /* cmp (int16_t)eax, 3 -> jg 0x33cfa */
  /* test (char)eax, (char)eax -> je 0x33d0a */
  FUN_0002f380(0, 0);
  actor_visibility_at_point();
  /* relift: cmp word ptr [esi + 0x32], 0 -> jne 0x33d60 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x33d60 */
  game_connection();
  /* test (int16_t)eax, (int16_t)eax -> jne 0x33da3 */
  /* test (char)eax, (char)eax -> jne 0x33db1 */
  /* test eax, eax -> je 0x33db9 */
  /* test (char)ecx, (char)ecx -> je 0x33db9 */
  /* cmp (int16_t)eax, 1 -> je 0x33e23 */
  /* cmp (int16_t)eax, 2 -> je 0x33e23 */
  /* cmp eax, -1 -> jne 0x33dd7 */
  object_get_and_verify_type(0, 0);
  tag_get('tinu', 0);
  actor_audibility_at_point(0, (void *)0, (void *)0, (void *)0, 0, 0x3f800000, 0);
  /* test (char)eax, (char)eax -> je 0x33e7d */
  /* relift: cmp byte ptr [esi + 0x122], 2 -> jg 0x33e7d */
  /* relift: cmp byte ptr [esi + 0x121], 2 -> jg 0x33e7d */
  /* test (int16_t)eax, (int16_t)eax -> je 0x33e67 */
  /* cmp (int16_t)eax, 1 -> jne 0x33e7d */
  /* cmp eax, edi -> jg 0x33ea3 */
  /* cmp (int16_t)eax, 2 -> jl 0x33ec3 */
  /* cmp (int16_t)eax, 3 -> jg 0x33ec3 */
  /* relift: cmp word ptr [esi + 0x30], 0 -> je 0x33eec */
  /* cmp (int16_t)eax, 2 -> jl 0x33f74 */
  /* cmp (int16_t)eax, 3 -> jg 0x33f74 */
  /* relift: cmp word ptr [esi + 0x32], 2 -> jge 0x33f64 */
  /* test (char)eax, (char)eax -> je 0x33f74 */
  /* cmp eax, -1 -> je 0x33f74 */
  datum_absolute_index_to_index((void *)0, 0);
  /* test eax, eax -> je 0x33f74 */
  /* relift: cmp word ptr [eax + 0x268], 0xa -> jl 0x33f74 */
  /* cmp ecx, -1 -> je 0x33f74 */
  /* test dl, dl -> je 0x33f74 */
  datum_get((void *)0, 0);
  /* cmp ecx, eax -> jne 0x33f74 */
  FUN_00032170();
  /* test (char)eax, 0x41 -> jne 0x33fee */
  /* test (char)eax, (char)eax -> jne 0x33fc3 */
  /* relift: cmp byte ptr [ecx + 0x253], 0x1e -> jne 0x33fee */
  FUN_0002f5f0();
  /* cmp (int16_t)eax, 2 -> jl 0x34055 */
  /* cmp (int16_t)eax, 3 -> jg 0x34055 */
  actor_has_ranged_weapon(0);
  /* test (char)eax, (char)eax -> je 0x3402b */
  /* relift: test dword ptr [eax], 0x8000000 -> je 0x34055 */
  actor_perception_unreachable(0, 0, 0);
  /* cmp eax, -1 -> je 0x34078 */
  /* cmp eax, ecx -> jge 0x34078 */
  actor_perception_unreachable(0, 0, 0);
  /* test (char)eax, (char)eax -> je 0x3426b */
  datum_get((void *)0, 0);
  datum_get((void *)0, 0);
  /* test (char)ebx, (char)ebx -> jne 0x3425e */
  /* test eax, eax -> je 0x34117 */
  /* test (char)ecx, (char)ecx -> je 0x34258 */
  /* test (char)ecx, (char)ecx -> jne 0x34258 */
  /* test (char)eax, (char)eax -> jne 0x3425e */
  /* test (char)eax, 0x41 -> je 0x34258 */
  /* test (char)eax, (char)eax -> je 0x34237 */
  datum_get((void *)0, 0);
  object_get_and_verify_type(0, 0);
  /* cmp ecx, edx -> jg 0x34181 */
  /* cmp ecx, -1 -> je 0x34197 */
  /* cmp eax, -1 -> je 0x34195 */
  /* cmp eax, ecx -> jge 0x34197 */
  /* test (char)eax, (char)eax -> jne 0x341b0 */
  /* test (char)eax, (char)eax -> jne 0x341b0 */
  /* test (char)eax, (char)eax -> jne 0x341b0 */
  /* test (char)ebx, (char)ebx -> je 0x34258 */
  /* test (char)eax, (char)eax -> je 0x341d7 */
  /* test (char)eax, 0x41 -> je 0x3425e */
  /* test (char)eax, (char)eax -> je 0x341f6 */
  /* relift: cmp word ptr [ebp - 0x18], 0x96 -> jg 0x34258 */
  actor_action_try_to_panic(0);
  /* cmp (int16_t)eax, 1 -> jg 0x34258 */
  /* test (char)eax, (char)eax -> jne 0x34227 */
  /* relift: cmp word ptr [ecx + 0x6a], 3 -> jge 0x34227 */
  /* test (char)eax, (char)eax -> jne 0x3425e */
  /* test (char)eax, (char)eax -> jne 0x3425e */
  actor_get_perception_knowledge(0, 0);
  actor_compute_prop_target_weight(0, 0);
  FUN_000278e0(0, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x342a0 */
void actor_perception_refresh_test_object(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  datum_get((void *)0, 0);
  object_get_and_verify_type(0, 0);
  object_mark(0);
  /* test (char)eax, (char)eax -> je 0x34930 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x3471f */
  object_get_world_position(0, (void *)0);
  actor_perception_find_sense_position(0, (void *)0, 0, (void *)0);
  /* cmp eax, -1 -> je 0x34363 */
  actor_perception_unit_from_swarm();
  object_get_and_verify_type(0, 0);
  object_get_world_position(0, (void *)0);
  /* cmp edi, -1 -> je 0x34930 */
  /* relift: cmp ebx, dword ptr [ebp + 8] -> je 0x34930 */
  tag_get('tinu', 0);
  game_allegiance_get_team_is_friendly(0, 0);
  /* test (char)eax, 4 -> je 0x343e0 */
  /* relift: cmp word ptr [esi + 0x3d0], 0 -> jne 0x343e0 */
  game_time_get();
  /* test (char)eax, 0x41 -> jne 0x34471 */
  /* test (char)eax, (char)eax -> jne 0x34450 */
  /* relift: cmp byte ptr [esi + 0x253], 0x1e -> jne 0x34471 */
  FUN_0002f5f0();
  datum_get((void *)0, 0);
  datum_get((void *)0, 0);
  /* test eax, eax -> je 0x344c7 */
  /* test (char)ecx, (char)ecx -> je 0x34930 */
  /* test (char)ecx, (char)ecx -> jne 0x34930 */
  /* test (char)eax, 0x41 -> je 0x34930 */
  /* test (char)eax, (char)eax -> je 0x34662 */
  datum_get((void *)0, 0);
  object_get_and_verify_type(0, 0);
  /* cmp ecx, edx -> jg 0x34520 */
  /* cmp ecx, -1 -> je 0x34536 */
  /* cmp eax, -1 -> je 0x34534 */
  /* cmp eax, ecx -> jge 0x34536 */
  /* test (char)eax, (char)eax -> jne 0x3454f */
  /* test (char)eax, (char)eax -> jne 0x3454f */
  /* test (char)eax, (char)eax -> jne 0x3454f */
  /* test (char)ebx, (char)ebx -> je 0x34930 */
  /* test (char)eax, (char)eax -> je 0x345f5 */
  /* test (char)eax, (char)eax -> je 0x346da */
  /* test (char)eax, (char)eax -> je 0x345b4 */
  display_assert((void *)0x00256354, (void *)0x00255fb0, 2966, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 0x80 -> jge 0x34930 */
  /* test (char)eax, 0x41 -> je 0x34575 */
  /* test (char)ebx, (char)ebx -> je 0x3461c */
  /* relift: cmp word ptr [ebp - 0x24], 0x96 -> jg 0x34930 */
  actor_action_try_to_panic(0);
  /* cmp (int16_t)eax, 1 -> jg 0x34930 */
  /* relift: cmp word ptr [edi + 0x6a], 3 -> jge 0x3464b */
  /* test (char)eax, (char)eax -> je 0x3468b */
  /* test (char)eax, 0x41 -> jne 0x34682 */
  /* relift: cmp word ptr [edi + 0x6e], 4 -> jl 0x346ab */
  /* test (char)eax, (char)eax -> jne 0x346c9 */
  /* test (char)eax, 0x41 -> je 0x346cd */
  /* test (char)ecx, (char)ecx -> je 0x34930 */
  prop_new_unacknowledged();
  /* cmp eax, -1 -> je 0x34930 */
  prop_position_refresh();
  /* test (char)eax, (char)eax -> jne 0x34930 */
  /* cmp (int16_t)eax, 1 -> jne 0x34748 */
  /* relift: cmp dword ptr [esi + 0x2d4], -1 -> jne 0x34930 */
  FUN_00032170();
  /* cmp (int16_t)eax, 5 -> jne 0x34930 */
  tag_get('jorp', 0);
  /* test (char)eax, 0x41 -> jne 0x34930 */
  /* relift: cmp dword ptr [eax + 0xcc], -1 -> je 0x34797 */
  /* relift: test byte ptr [eax + 0x1dc], 0x20 -> je 0x34930 */
  object_get_world_position(0, (void *)0);
  actor_perception_find_sense_position(0, (void *)0, 0, (void *)0);
  /* test (char)eax, 0x41 -> jne 0x34930 */
  /* relift: cmp dword ptr [ecx + 0x28c], edi -> je 0x34930 */
  csmemset((void *)0, 0, 108);
  /* cmp eax, -1 -> je 0x34927 */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0x34927 */
  /* test dl, 3 -> je 0x34927 */
  /* cmp esi, eax -> jne 0x34902 */
  game_allegiance_get_team_is_friendly(0, 0);
  /* test (char)eax, (char)eax -> jne 0x3492a */
  /* cmp eax, -1 -> je 0x34953 */
  actor_perception_refresh_test_object();
  /* cmp edi, -1 -> jne 0x342d0 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x34970 */
void actor_perception_create_orphan_from_friend(int param_1, int encounter_team, int actor_handle, int encounter_handle)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_00064b40(0, 0, 0, 0);
  /* cmp edi, -1 -> je 0x34c6b */
  datum_get((void *)0, 0);
  /* cmp (int16_t)eax, 2 -> jl 0x349c8 */
  /* cmp (int16_t)eax, 3 -> jg 0x349c8 */
  /* cmp ebx, -1 -> je 0x34b59 */
  datum_get((void *)0, 0);
  /* cmp (int16_t)eax, 1 -> jle 0x34a19 */
  display_assert((void *)0x00256450, (void *)0x00255fb0, 3764, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 4 -> jl 0x34a2c */
  /* cmp (int16_t)eax, 5 -> jle 0x34a4c */
  display_assert((void *)0x00256430, (void *)0x00255fb0, 3765, 0);
  system_exit(0);
  /* relift: cmp edx, dword ptr [ebp + 8] -> je 0x34a74 */
  display_assert((void *)0x00256400, (void *)0x00255fb0, 3766, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ecx + 4], eax -> je 0x34a9f */
  display_assert((void *)0x002563cc, (void *)0x00255fb0, 3767, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0xc], ebx -> je 0x34ac4 */
  display_assert((void *)0x00256394, (void *)0x00255fb0, 3768, 0);
  system_exit(0);
  /* relift: cmp dword ptr [edx + 0xc], edi -> je 0x34aec */
  display_assert((void *)0x0025635c, (void *)0x00255fb0, 3769, 0);
  system_exit(0);
  /* cmp eax, -1 -> je 0x34b0d */
  prop_orphan_update_information();
  prop_position_refresh();
  prop_status_refresh();
  datum_get((void *)0, 0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x34b64 */
  /* cmp (int16_t)eax, 1 -> jle 0x34b84 */
  display_assert((void *)0x00256450, (void *)0x00255fb0, 3807, 0);
  system_exit(0);
  /* cmp eax, -1 -> je 0x34bc5 */
  prop_orphan_from_friend();
  /* cmp edi, -1 -> je 0x34be8 */
  datum_get((void *)0, 0);
  prop_position_refresh();
  prop_orphan_transition();
  /* cmp edi, -1 -> jne 0x34bf1 */
  datum_get((void *)0, 0);
  /* test esi, esi -> je 0x34c61 */
  /* cmp ebx, -1 -> je 0x34c2e */
  /* cmp eax, -1 -> je 0x34c44 */
  datum_get((void *)0, 0);
  /* relift: cmp word ptr [eax + 0x32], 2 -> jl 0x34c44 */
  actor_get_perception_knowledge(0, 0);
  actor_compute_prop_target_weight(0, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x34c80 */
void actor_perception_refresh(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  scenario_get();
  datum_get((void *)0, 0);
  datum_get((void *)0, 0);
  csmemset((void *)0, 0, 64);
  /* relift: cmp word ptr [esi + 2], (int16_t)edi -> jle 0x34d8b */
  object_get_and_verify_type(0, 0);
  /* cmp (int16_t)eax, 0xffff -> je 0x34d58 */
  structure_bsp_get_cluster_sound_data((void *)0, 0);
  bit_vector_or(0, 0, 0, 0);
  /* relift: cmp (int16_t)edi, word ptr [esi + 2] -> jl 0x34d10 */
  /* test (char)eax, (char)eax -> je 0x34d8b */
  /* cmp (int16_t)eax, 0xffff -> je 0x34d8b */
  structure_bsp_get_cluster_sound_data((void *)0, 0);
  object_reset_markers();
  FUN_00064540((void *)0, 0);
  FUN_00064570((void *)0);
  /* test esi, esi -> je 0x35245 */
  /* cmp (int16_t)eax, 4 -> jl 0x34dc7 */
  /* cmp (int16_t)eax, 5 -> jle 0x3522f */
  datum_get((void *)0, 0);
  datum_get((void *)0, 0);
  /* test eax, eax -> je 0x34e67 */
  /* test (char)ecx, (char)ecx -> je 0x34e60 */
  /* test (char)ecx, (char)ecx -> je 0x34e67 */
  /* test (char)eax, (char)eax -> jne 0x34e75 */
  /* relift: cmp word ptr [ebp - 0x3c], 0 -> jle 0x34e7c */
  /* test (char)eax, 0x41 -> jne 0x34e93 */
  /* test (char)eax, (char)eax -> je 0x34fa6 */
  datum_get((void *)0, 0);
  object_get_and_verify_type(0, 0);
  /* cmp ecx, edx -> jg 0x34ede */
  /* cmp ecx, -1 -> je 0x34ef4 */
  /* cmp eax, -1 -> je 0x34ef2 */
  /* cmp eax, ecx -> jge 0x34ef4 */
  /* test (char)eax, (char)eax -> jne 0x34f0d */
  /* test (char)eax, (char)eax -> jne 0x34f0d */
  /* test (char)eax, (char)eax -> jne 0x34f0d */
  /* test (char)ebx, (char)ebx -> je 0x34fff */
  /* test (char)eax, (char)eax -> je 0x34f32 */
  /* test (char)eax, 0x41 -> jne 0x34f49 */
  /* test (char)ebx, (char)ebx -> je 0x34f5f */
  /* relift: cmp word ptr [ebp - 0x30], 0x96 -> jle 0x34f5f */
  actor_action_try_to_panic(0);
  /* cmp (int16_t)eax, 1 -> jle 0x34f78 */
  /* relift: cmp word ptr [ecx + 0x6a], 3 -> jge 0x34f94 */
  /* test (char)eax, (char)eax -> je 0x34fba */
  /* relift: cmp word ptr [eax + 0x6e], 4 -> jl 0x34fdd */
  /* test (char)ecx, (char)ecx -> jne 0x34ffb */
  /* test (char)eax, 0x41 -> je 0x34fff */
  /* test edi, edi -> je 0x3505a */
  object_get_first_cluster((void *)0, 0);
  /* cmp (int16_t)eax, 0xffff -> je 0x3505a */
  /* relift: test dword ptr [edi + eax*4], edx -> jne 0x35056 */
  FUN_0013d5f0((void *)0, 0);
  /* cmp (int16_t)eax, 0xffff -> jne 0x35027 */
  /* test (char)eax, (char)eax -> je 0x350e2 */
  /* cmp eax, -1 -> je 0x350e2 */
  datum_get((void *)0, 0);
  /* cmp eax, -1 -> je 0x350b9 */
  datum_get((void *)0, 0);
  /* relift: cmp word ptr [ebx + 2], (int16_t)edi -> jle 0x350e2 */
  object_mark(0);
  /* relift: cmp (int16_t)edi, word ptr [ebx + 2] -> jl 0x350a0 */
  /* cmp edi, -1 -> je 0x350e2 */
  object_get_and_verify_type(0, 0);
  object_mark(0);
  /* cmp edi, -1 -> jne 0x350c4 */
  object_mark(0);
  /* test (char)eax, (char)eax -> je 0x351e0 */
  /* test (char)eax, (char)eax -> je 0x35141 */
  display_assert((void *)0x002564c4, (void *)0x00255fb0, 2669, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 0x80 -> jge 0x35183 */
  /* relift: cmp dword ptr [0x2c8520], -1 -> je 0x351a5 */
  game_time_get();
  /* cmp eax, ecx -> jle 0x3522f */
  error(0, (void *)0x00256474);
  game_time_get();
  /* mem[0x002c8520] = eax */
  /* test (char)eax, (char)eax -> jne 0x3522f */
  /* cmp (int16_t)eax, 4 -> jl 0x351f0 */
  /* cmp (int16_t)eax, 5 -> jle 0x35213 */
  FUN_0003b410(0, 0, 0);
  prop_iterator_next(0, 0);
  FUN_0003b410(0, 0, 0);
  prop_iterator_next(0, 0);
  FUN_00064570((void *)0);
  /* test esi, esi -> jne 0x34db3 */
  /* test ebx, ebx -> je 0x3531d */
  /* test ecx, ecx -> jle 0x3531d */
  /* relift: test dword ptr [ebx + eax*4], edx -> je 0x35306 */
  cluster_partition_object_iter_first((void *)0, 0);
  /* cmp eax, -1 -> je 0x352c6 */
  actor_perception_refresh_test_object();
  cluster_partition_object_iter_next((void *)0);
  /* cmp eax, -1 -> jne 0x352a0 */
  cluster_get_first_noncollideable_object((void *)0, 0);
  /* cmp eax, -1 -> je 0x35306 */
  actor_perception_refresh_test_object();
  cluster_get_next_noncollideable_object((void *)0);
  /* cmp eax, -1 -> jne 0x352e0 */
  /* cmp eax, edx -> jl 0x35270 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x3546f */
  qsort((void *)0, 0, 12, (void *)0);
  /* relift: cmp word ptr [ebp - 0x6be], (int16_t)edi -> jle 0x3546f */
  /* relift: cmp dword ptr [ebp + eax - 0x6b8], ebx -> jne 0x353ae */
  prop_new_unacknowledged();
  /* cmp eax, ebx -> je 0x353c4 */
  prop_position_refresh();
  /* relift: cmp (int16_t)edi, word ptr [ebp - 0x6be] -> jl 0x35370 */
  /* cmp (int16_t)edi, (int16_t)eax -> jge 0x3546f */
  datum_get((void *)0, 0);
  /* cmp (int16_t)eax, 4 -> jl 0x3542a */
  /* cmp (int16_t)eax, 5 -> jle 0x35448 */
  /* cmp eax, -1 -> je 0x35448 */
  FUN_0003b410(0, 0, 0);
  prop_iterator_next(0, 0);
  FUN_0003b410(0, 0, 0);
  prop_iterator_next(0, 0);
  /* test (int16_t)ecx, (int16_t)ecx -> jle 0x355e0 */
  qsort((void *)0, 0, 12, (void *)0);
  /* relift: cmp word ptr [ebp - 0xcc2], 0 -> jle 0x355e0 */
  /* relift: cmp dword ptr [ebp + eax - 0xcbc], -1 -> jne 0x35517 */
  prop_new_unacknowledged();
  /* cmp eax, -1 -> je 0x35525 */
  prop_position_refresh();
  /* relift: cmp (int16_t)ebx, word ptr [ebp - 0x1c] -> jge 0x3553e */
  /* relift: cmp (int16_t)edi, word ptr [ebp - 0xcc2] -> jl 0x354d7 */
  object_marker_end();
  /* cmp (int16_t)edi, (int16_t)ecx -> jge 0x355e0 */
  datum_get((void *)0, 0);
  /* cmp (int16_t)eax, 4 -> jl 0x3559b */
  /* cmp (int16_t)eax, 5 -> jle 0x355b9 */
  /* cmp eax, -1 -> je 0x355b9 */
  FUN_0003b410(0, 0, 0);
  prop_iterator_next(0, 0);
  FUN_0003b410(0, 0, 0);
  prop_iterator_next(0, 0);
  object_marker_end();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x355f0 */
void FUN_000355f0(int actor_handle)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  datum_get((void *)0, 0);
  tag_get('rtca', 0);
  /* test (char)eax, (char)eax -> je 0x3565a */
  actor_perception_refresh();
  actor_perception_refresh_danger_zone();
  /* test (int16_t)edx, (int16_t)edx -> jle 0x3582a */
  /* test (char)eax, (char)eax -> jne 0x356d2 */
  /* relift: cmp word ptr [esi + 0x282], 0 -> jne 0x356d2 */
  /* test (int16_t)ecx, (int16_t)ecx -> jle 0x357e0 */
  /* test (char)eax, (char)eax -> je 0x357e0 */
  /* cmp eax, -1 -> je 0x356b5 */
  /* cmp eax, 0x3c -> jl 0x356c7 */
  /* test (char)eax, (char)eax -> je 0x357e0 */
  /* test (char)eax, 0x41 -> jne 0x3573e */
  get_global_random_seed_address();
  random_math_real((void *)0);
  /* test (char)eax, (char)eax -> je 0x357e0 */
  /* test (char)eax, (char)eax -> je 0x3575f */
  /* relift: cmp word ptr [esi + 0x282], 0 -> jne 0x357ae */
  /* cmp (int16_t)eax, 3 -> je 0x357ae */
  /* cmp (int16_t)eax, 1 -> je 0x357ae */
  get_global_random_seed_address();
  random_math_real((void *)0);
  FUN_000378e0(0, 0, 0, 0, (void *)0);
  /* relift: cmp word ptr [esi + 0x284], 0 -> jne 0x3582a */
  /* relift: cmp word ptr [esi + 0x544], 0xc -> jne 0x35812 */
  /* cmp (int16_t)eax, 5 -> jle 0x35808 */
  /* test (char)eax, (char)eax -> je 0x3582a */
  FUN_00064540((void *)0, 0);
  FUN_00064570((void *)0);
  /* test esi, esi -> je 0x36767 */
  /* cmp (int16_t)eax, (int16_t)edi -> je 0x3589f */
  /* cmp (int16_t)eax, (int16_t)edi -> je 0x358c8 */
  /* test (char)eax, (char)eax -> je 0x358d8 */
  /* cmp (int16_t)eax, (int16_t)ebx -> jle 0x358ec */
  /* cmp (int16_t)eax, (int16_t)ebx -> jle 0x35906 */
  /* test (char)ecx, (char)ecx -> jne 0x35906 */
  /* cmp (int16_t)eax, (int16_t)ebx -> jle 0x35922 */
  /* cmp (int16_t)eax, 0x7fff -> jge 0x35922 */
  /* cmp (int16_t)eax, (int16_t)ebx -> jle 0x3597e */
  /* relift: cmp word ptr [esi + 0xa6], (int16_t)ebx -> jg 0x35965 */
  display_assert((void *)0x00256708, (void *)0x00255fb0, 316, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xa6], (int16_t)ebx -> jle 0x3597e */
  /* relift: cmp word ptr [esi + 0x32], 2 -> jl 0x35998 */
  /* cmp (int16_t)eax, 0x7fff -> jge 0x3599c */
  /* test (char)ecx, (char)ecx -> je 0x359b3 */
  /* test (char)ecx, (char)ecx -> jne 0x359cc */
  /* relift: cmp byte ptr [esi + 0x121], 3 -> jl 0x359d9 */
  /* test (char)ecx, (char)ecx -> jne 0x359fd */
  /* relift: cmp (int16_t)ecx, word ptr [eax + 0x4e] -> jl 0x359fd */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
