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

  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), 0);
  tag_get('rtca', 0);
  /* test (char)eax, 0x41 -> jne 0x2f4c2 */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x2533c4] */
  /* relift: relift: fcomp dword ptr [0x253f30] */
  /* test (char)eax, 0x41 -> jne 0x2f4fc */
  /* test (char)eax, 0x41 -> jne 0x2f521 */
  /* relift: relift: fld dword ptr [0x2533f0] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c8] */

  (void)eax;
}

/* 0x2f5f0 — register a unit danger zone on an actor (vehicle proximity). */
char FUN_0002f5f0(int actor_handle, float scale, float visibility,
                  int unit_handle, char field_60, char dz_flag)
{
  char *actor;
  char *unit;
  char *danger;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (scale + *(float *)0x253f34 > visibility)
    return 0;

  danger = actor + 0x280;
  if (*(int16_t *)(actor + 0x280) >= 1) {
    if (*(int16_t *)(actor + 0x280) != 1)
      return 0;
    if (*(int *)(actor + 0x28c) == unit_handle)
      return 0;
    if (visibility > *(float *)(actor + 0x2d4))
      return 0;
  }

  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  csmemset(danger, 0, 0x6c);
  *(int *)(actor + 0x28c) = unit_handle;
  *(int16_t *)(actor + 0x280) = 1;
  *(int *)(actor + 0x294) = *(int *)&scale;
  object_get_world_position(unit_handle, (vector3_t *)(actor + 0x298));
  *(int *)(actor + 0x2a4) = *(int *)(unit + 0x18);
  *(int *)(actor + 0x2a8) = *(int *)(unit + 0x1c);
  *(int *)(actor + 0x2ac) = *(int *)(unit + 0x20);
  *(int16_t *)(actor + 0x284) = 6;
  *(char *)(actor + 0x286) = dz_flag;
  *(int16_t *)(actor + 0x282) = (int16_t)(field_60 == 0);
  return 1;
}

/* actor_perception_desire_prop (0x2f6e0) — XBE naked draft (batch 81). */
#if defined(__clang__)
static void *(*const b2f6e0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b2f6e0_get)(int, int) = object_get_and_verify_type;
static int16_t (*const b2f6e0_c1d6d0)(int actor_handle) = actor_action_try_to_panic;

__attribute__((naked, noinline))
char actor_perception_desire_prop(int actor_handle __attribute__((unused)), int existing_prop __attribute__((unused)), int unit_handle __attribute__((unused)), int owner_handle __attribute__((unused)), char field_63 __attribute__((unused)), char field_12e __attribute__((unused)), char friendly __attribute__((unused)), char field_127 __attribute__((unused)), int16_t field_76 __attribute__((unused)), int16_t scale __attribute__((unused)), float visibility __attribute__((unused)), int sense __attribute__((unused)), char *out_flag __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lactor_perception_desire_prop_1\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lactor_perception_desire_prop_2\n\t"
      ".Lactor_perception_desire_prop_1:\n\t"
      "movl 0x6325a4, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      ".Lactor_perception_desire_prop_2:\n\t"
      "movb 0x20(%%ebp), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "movw 0xc(%%ebp), %%cx\n\t"
      "movb 0x24(%%ebp), %%bl\n\t"
      "movb $0, 0x17(%%ebp)\n\t"
      "je .Lactor_perception_desire_prop_3\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lactor_perception_desire_prop_4\n\t"
      ".Lactor_perception_desire_prop_3:\n\t"
      "cmpw $4, %%cx\n\t"
      "jl .Lactor_perception_desire_prop_4\n\t"
      "cmpw $5, %%cx\n\t"
      "jg .Lactor_perception_desire_prop_4\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .Lactor_perception_desire_prop_30\n\t"
      ".Lactor_perception_desire_prop_4:\n\t"
      "cmpb $0, 0x1c(%%ebp)\n\t"
      "je .Lactor_perception_desire_prop_5\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lactor_perception_desire_prop_30\n\t"
      ".Lactor_perception_desire_prop_5:\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lactor_perception_desire_prop_7\n\t"
      "cmpb $0, 0x8(%%eax)\n\t"
      "je .Lactor_perception_desire_prop_6\n\t"
      "cmpb $0, 0x13(%%eax)\n\t"
      "je .Lactor_perception_desire_prop_7\n\t"
      ".Lactor_perception_desire_prop_6:\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .Lactor_perception_desire_prop_30\n\t"
      ".Lactor_perception_desire_prop_7:\n\t"
      "cmpw $-1, %%cx\n\t"
      "jne .Lactor_perception_desire_prop_9\n\t"
      "movb 0x18(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_desire_prop_8\n\t"
      "cmpw $0, 0x34(%%ebp)\n\t"
      "jle .Lactor_perception_desire_prop_9\n\t"
      ".Lactor_perception_desire_prop_8:\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lactor_perception_desire_prop_30\n\t"
      ".Lactor_perception_desire_prop_9:\n\t"
      "flds 0x30(%%ebp)\n\t"
      "fcomps 0x255fe0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_perception_desire_prop_10\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .Lactor_perception_desire_prop_30\n\t"
      ".Lactor_perception_desire_prop_10:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lactor_perception_desire_prop_23\n\t"
      "movl 0x34(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movb $1, %%bl\n\t"
      "je .Lactor_perception_desire_prop_17\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "movl 0x5ab270, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl $3\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[get]\n\t"
      "movl 0x58(%%esi), %%ecx\n\t"
      "movl 0x3a0(%%edi), %%edx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jg .Lactor_perception_desire_prop_11\n\t"
      "movl %%edx, %%ecx\n\t"
      ".Lactor_perception_desire_prop_11:\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lactor_perception_desire_prop_13\n\t"
      "movl 0x3cc(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_perception_desire_prop_12\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .Lactor_perception_desire_prop_13\n\t"
      ".Lactor_perception_desire_prop_12:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".Lactor_perception_desire_prop_13:\n\t"
      "movb 0x45(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_desire_prop_14\n\t"
      "movb 0x44(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_desire_prop_14\n\t"
      "movb 0x42(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_desire_prop_14\n\t"
      "movb $1, %%al\n\t"
      "jmp .Lactor_perception_desire_prop_15\n\t"
      ".Lactor_perception_desire_prop_14:\n\t"
      "xorb %%al, %%al\n\t"
      ".Lactor_perception_desire_prop_15:\n\t"
      "testb %%bl, %%bl\n\t"
      "popl %%esi\n\t"
      "je .Lactor_perception_desire_prop_30\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_perception_desire_prop_16\n\t"
      "flds 0x30(%%ebp)\n\t"
      "fcomps 0x255fdc\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_perception_desire_prop_20\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lactor_perception_desire_prop_30\n\t"
      ".Lactor_perception_desire_prop_16:\n\t"
      "movb 0x20(%%ebp), %%dl\n\t"
      ".Lactor_perception_desire_prop_17:\n\t"
      "flds 0x2c(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_perception_desire_prop_18\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lactor_perception_desire_prop_30\n\t"
      ".Lactor_perception_desire_prop_18:\n\t"
      "testb %%dl, %%dl\n\t"
      "je .Lactor_perception_desire_prop_19\n\t"
      "cmpw $0x96, 0x28(%%ebp)\n\t"
      "jle .Lactor_perception_desire_prop_19\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .Lactor_perception_desire_prop_30\n\t"
      ".Lactor_perception_desire_prop_19:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d6d0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $1, %%ax\n\t"
      "jle .Lactor_perception_desire_prop_21\n\t"
      ".Lactor_perception_desire_prop_20:\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .Lactor_perception_desire_prop_30\n\t"
      ".Lactor_perception_desire_prop_21:\n\t"
      "movb 0x20(%%ebp), %%al\n\t"
      "flds 0x254e74\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_desire_prop_22\n\t"
      "cmpw $3, 0x6a(%%edi)\n\t"
      "jge .Lactor_perception_desire_prop_22\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x254df8\n\t"
      ".Lactor_perception_desire_prop_22:\n\t"
      "flds 0x30(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_perception_desire_prop_20\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lactor_perception_desire_prop_30\n\t"
      ".Lactor_perception_desire_prop_23:\n\t"
      "testb %%dl, %%dl\n\t"
      "flds 0x30(%%ebp)\n\t"
      "je .Lactor_perception_desire_prop_24\n\t"
      "fcomps 0x255fd8\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lactor_perception_desire_prop_28\n\t"
      ".Lactor_perception_desire_prop_24:\n\t"
      "fcomps 0x255fdc\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_perception_desire_prop_25\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lactor_perception_desire_prop_26\n\t"
      ".Lactor_perception_desire_prop_25:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".Lactor_perception_desire_prop_26:\n\t"
      "cmpw $4, 0x6e(%%edi)\n\t"
      "jl .Lactor_perception_desire_prop_27\n\t"
      "movb $1, 0x17(%%ebp)\n\t"
      "jmp .Lactor_perception_desire_prop_30\n\t"
      ".Lactor_perception_desire_prop_27:\n\t"
      "movb 0x1cc(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_desire_prop_29\n\t"
      "flds 0x30(%%ebp)\n\t"
      "fcomps 0x254e74\n\t"
      ".Lactor_perception_desire_prop_28:\n\t"
      "fnstsw %%ax\n\t"
      "movb $1, 0x17(%%ebp)\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_perception_desire_prop_30\n\t"
      ".Lactor_perception_desire_prop_29:\n\t"
      "movb $0, 0x17(%%ebp)\n\t"
      ".Lactor_perception_desire_prop_30:\n\t"
      "movl 0x38(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lactor_perception_desire_prop_31\n\t"
      "movb 0x17(%%ebp), %%cl\n\t"
      "movb %%cl, (%%eax)\n\t"
      ".Lactor_perception_desire_prop_31:\n\t"
      "popl %%edi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b2f6e0_dget), [get] "m"(b2f6e0_get), [c1d6d0] "m"(b2f6e0_c1d6d0)
      : "memory");
}
#else
#error "actor_perception_desire_prop: clang naked draft required"
#endif


/* 0x2fb60 — fpatan(y, x) */
float arctangent(float y, float x)
{
  double dy;
  double dx;
  double r;

  dy = (double)y;
  dx = (double)x;
  __asm__ volatile("fpatan" : "=t"(r) : "0"(dy), "u"(dx));
  return (float)r;
}

/* 0x300b0 */
void actor_situation_update_target_status(int actor_handle)
{
  int eax = 0;
  int esi = 0;

  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), actor_handle);
  /* cmp eax, -1 -> jne 0x300f0 */
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), 0);
  object_get_and_verify_type(0, 3);
  /* test (char)eax, (char)eax -> jne 0x30138 */
  display_assert((char *)0x0025601c, (char *)0x00255fb0, 4291, 1);
  system_exit(-1);
  /* cmp eax, 5 -> ja 0x30219 */
  /* test (char)eax, (char)eax -> je 0x30185 */
  /* test (char)eax, (char)eax -> je 0x30196 */
  /* relift: cmp word ptr [esi + 0x32], 2 -> jl 0x301a7 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x301bd */
  /* cmp (int16_t)eax, 1 -> je 0x301bd */
  /* relift: cmp byte ptr [esi + 0x122], 2 -> jg 0x301e0 */
  /* relift: relift: fcomp dword ptr [0x254640] */
  /* test (char)eax, (char)eax -> je 0x301f8 */
  display_assert((char *)0, (char *)0x00255fb0, 4362, 1);
  system_exit(-1);
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

  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), actor_handle);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x3030a */
  /* cmp (int16_t)ecx, (int16_t)eax -> jge 0x302ed */
  /* cmp eax, ecx -> jg 0x302fe */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x3031c */
  /* cmp (int16_t)eax, 0xc -> jl 0x3033c */
  display_assert((char *)0x00256030, (char *)0x00255fb0, 4408, 1);
  system_exit(-1);
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
  int local_14 = 0;

  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), actor_handle);
  csmemset((void *)((char *)eax + 0x1ec), 0, 123);
  FUN_00064540((void *)0, actor_handle);
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
  /* relift: relift: fcomp dword ptr [0x253f40] */
  /* relift: cmp byte ptr [edi + 0x122], 1 -> jg 0x305f1 */
  /* test (char)eax, (char)eax -> je 0x305a7 */
  /* test (char)eax, (char)eax -> jg 0x305f1 */
  /* test dl, dl -> je 0x305ce */
  /* test (char)eax, (char)eax -> je 0x305f1 */
  /* test (char)eax, (char)eax -> je 0x305f1 */
  /* relift: cmp word ptr [edi + 0x38], 0 -> jne 0x305f1 */
  object_get_and_verify_type(0, 3);
  /* cmp eax, -1 -> jne 0x30643 */
  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), 0);
  /* relift: cmp dword ptr [ebx + 0x1c8], -1 -> je 0x30669 */
  /* test eax, eax -> je 0x30677 */
  /* cmp (int16_t)ebx, 0x10 -> jl 0x306b8 */
  display_assert((char *)0x00256090, (char *)0x00255fb0, 4572, 1);
  system_exit(-1);
  /* relift: relift: fcomp dword ptr [0x253f78] */
  /* test (char)eax, (char)eax -> je 0x3072c */
  /* test eax, eax -> je 0x3072c */
  /* cmp eax, -1 -> je 0x3072c */
  /* relift: cmp dword ptr [ecx + 0x270], -1 -> je 0x3072c */
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), 0);
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), 0);
  /* cmp ecx, edx -> jne 0x3072c */
  /* test (int16_t)eax, (int16_t)eax -> je 0x3073b */
  /* cmp (int16_t)eax, 1 -> jne 0x30758 */
  /* relift: relift: fcomp dword ptr [0x254644] */
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
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), 0);
  actor_compute_prop_target_weight(actor_handle, 0);
  /* cmp ebx, -1 -> je 0x308c8 */
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), local_14);
  actor_compute_prop_target_weight(actor_handle, 0);
  actor_situation_update_target_status(actor_handle);
  actor_situation_combat_status_update(actor_handle);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)local_14;
}

/* 0x308e0 */
void actor_situation_try_new_target(int actor_handle, int target)
{
  int eax = 0;

  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), actor_handle);
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), target);
  /* cmp eax, -1 -> jne 0x30921 */
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), 0);
  actor_compute_prop_target_weight(actor_handle, target);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x309bf */
  /* test (char)eax, (char)eax -> jne 0x30977 */
  display_assert((char *)0x002560cc, (char *)0x00255fb0, 4685, 1);
  system_exit(-1);
  /* test eax, eax -> je 0x3098b */
  /* test (char)eax, 1 -> jne 0x309bf */
  actor_situation_update_target_status(actor_handle);
  actor_situation_combat_status_update(actor_handle);

  (void)eax;
}

/* 0x309d0 */
char actor_perception_friend_prop_is_attacking(int actor_handle, int iter_handle, float *out_pos)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), actor_handle);
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), iter_handle);
  /* cmp (int16_t)eax, 2 -> jl 0x30a20 */
  /* cmp (int16_t)eax, 3 -> jg 0x30a20 */
  /* test (char)eax, (char)eax -> jne 0x30a20 */
  /* test (char)eax, (char)eax -> je 0x30a40 */
  display_assert((char *)0x002560e0, (char *)0x00255fb0, 4712, 1);
  system_exit(-1);
  /* test (char)eax, (char)eax -> jne 0x30b75 */
  /* test (char)eax, (char)eax -> je 0x30b59 */
  unit_scripting_unit_driver(0, (void *)(uintptr_t)out_pos);
  /* test (char)eax, (char)eax -> jne 0x30b49 */
  /* test (char)ecx, (char)ecx -> jle 0x30b49 */
  FUN_00064540((void *)0, actor_handle);
  FUN_00064570((void *)0);
  /* test eax, eax -> je 0x30b46 */
  /* cmp (int16_t)ecx, 2 -> jl 0x30b32 */
  /* cmp (int16_t)ecx, 3 -> jg 0x30b32 */
  /* test (char)ecx, (char)ecx -> je 0x30b32 */
  normalize3d((float *)0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x30b32 */
  /* relift: relift: fcomp dword ptr [0x253398] */
  /* test (char)eax, 0x41 -> je 0x30b50 */
  FUN_00064570((void *)0);
  /* test eax, eax -> jne 0x30ab0 */
  /* cmp esi, -1 -> je 0x30b75 */
  FUN_0003b190(0, (void *)(uintptr_t)out_pos);
  return 0;

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x30b80 */
void actor_perception_aiming_vector_test_blockage(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x30d10 */
unsigned int FUN_00030d10(int actor_handle, float *chance_inout)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), actor_handle);
  FUN_00064540((void *)0, actor_handle);
  FUN_00064570((void *)0);
  /* test esi, esi -> je 0x30df4 */
  /* cmp (int16_t)eax, 2 -> jl 0x30db4 */
  /* cmp (int16_t)eax, 3 -> jg 0x30db4 */
  /* test (char)eax, (char)eax -> jne 0x30db4 */
  /* relift: cmp (int16_t)eax, word ptr [ebx + 4] -> jne 0x30db4 */
  /* cmp eax, -1 -> je 0x30db4 */
  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), 0);
  /* relift: cmp word ptr [eax + 0x308], 0 -> jg 0x30db1 */
  /* relift: cmp word ptr [eax + 0x6c], 4 -> jne 0x30da4 */
  /* relift: cmp word ptr [eax + 0xa8], 0 -> jg 0x30db1 */
  /* test (char)eax, (char)eax -> je 0x30db4 */
  FUN_00064570((void *)0);
  /* test esi, esi -> jne 0x30d50 */
  /* relift: cmp word ptr [ebp - 4], 1 -> jle 0x30dd6 */
  /* cmp (int16_t)edi, 1 -> jle 0x30df4 */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x30e4a */
  /* relift: relift: fld dword ptr [0x253f40] */
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
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), 0);
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
  int local_1c = 0;
  int local_c = 0;

  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), 0);
  tag_get('rtca', 0);
  FUN_00064540((void *)0, 0);
  FUN_00064570((void *)0);
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), local_1c);
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
  /* relift: relift: fcomp dword ptr [0x253f78] */
  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), 0);
  /* relift: cmp word ptr [eax + 0x3a8], 0 -> je 0x311ce */
  /* cmp ecx, -1 -> je 0x311ce */
  /* cmp edx, -1 -> je 0x31103 */
  /* relift: cmp dword ptr [eax + 0x3b0], edx -> jl 0x311ce */
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), 0);
  prop_get_active_by_unit_index(0, 0);
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), eax);
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
  random_real_range((int *)(uintptr_t)*(int *)((char *)local_c + 0x270), 0.0f, 0.0f);
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
  random_real_range((int *)(uintptr_t)*(int *)((char *)local_c + 0x28c), 0.0f, 0.0f);
  FUN_001d9068();
  game_time_get();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)local_1c;
  (void)local_c;
}

/* 0x31440 — Toggle berserk state on an actor and propagate to attached objects. */
void actor_berserk(int actor_handle, int berserk_flag)
{
  char *actor;
  char old_berserk;
  int object_handle;
  char *object;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  old_berserk = *(char *)(actor + 0x378);
  if ((char)berserk_flag == old_berserk)
    return;

  *(char *)(actor + 0x378) = (char)berserk_flag;
  *(char *)(actor + 0x379) = 0;

  if (*(char *)(actor + 6) != 0) {
    object_handle = *(int *)(actor + 0x24);
    if (object_handle != -1) {
      do {
        object = (char *)object_get_and_verify_type(object_handle, 3);
        *(char *)(object + 0xb6) |= 0x80;
        object_handle = *(int *)(object + 0x1ac);
      } while (object_handle != -1);
    }
  } else {
    object = (char *)object_get_and_verify_type(*(int *)(actor + 0x18), 3);
    if (berserk_flag != 0)
      *(int *)(object + 0x1b4) |= 0x80;
    else
      *(int *)(object + 0x1b4) &= ~0x80;
  }

  if (berserk_flag != 0)
    *(char *)(actor + 0x375) = 1;
}

extern char *actor_combat_get_firing_variant_definition(int actor_handle);
extern bool actor_has_ranged_weapon(int actor_handle);
extern float FUN_000278e0(int actor_handle, int prop_handle);

/* actor_visibility_at_point (0x314f0) — XBE naked draft (batch 80). */
#if defined(__clang__)
static void *(*const b314f0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b314f0_tag)(int, int) = tag_get;
static char * (*const b314f0_c211f0)(int actor_handle) = actor_combat_get_firing_variant_definition;
static void (*const b314f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b314f0_exitfn)(int) = system_exit;
static float (*const b314f0_c18e690)(void) = FUN_0018e690;
static int (*const b314f0_gtime)(void) = game_time_get;
static void (*const b314f0_c2f470)(void) = actor_get_vision_distances;

__attribute__((naked, noinline))
int16_t actor_visibility_at_point(int actor_handle __attribute__((unused)), float *out_pos __attribute__((unused)), float *head_pos __attribute__((unused)), char vis_type __attribute__((unused)), int16_t los_result __attribute__((unused)), char flag __attribute__((unused)), int param_7 __attribute__((unused)), int16_t engagement __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x28, %%esp\n\t"
      "movw 0x18(%%ebp), %%cx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "testw %%cx, %%cx\n\t"
      "pushl %%edi\n\t"
      "je .Lactor_visibility_at_point_1\n\t"
      "cmpw $1, %%cx\n\t"
      "jne .Lactor_visibility_at_point_23\n\t"
      ".Lactor_visibility_at_point_1:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x58(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c211f0]\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds 0x150(%%ecx)\n\t"
      "addl $0x14, %%esp\n\t"
      "fcomps 0x2533c0\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_visibility_at_point_2\n\t"
      "movl 0x150(%%ecx), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".Lactor_visibility_at_point_2:\n\t"
      "movswl 0x24(%%ebp), %%eax\n\t"
      "cmpl $3, %%eax\n\t"
      "movl $0x3f800000, -0x10(%%ebp)\n\t"
      "ja .Lactor_visibility_at_point_7\n\t"
      "jmp *.Lactor_visibility_at_point_jt(,%%eax,4)\n\t"
      ".Lactor_visibility_at_point_3:\n\t"
      "flds 0x253524\n\t"
      "jmp .Lactor_visibility_at_point_8\n\t"
      ".Lactor_visibility_at_point_4:\n\t"
      "flds 0x253f3c\n\t"
      "jmp .Lactor_visibility_at_point_8\n\t"
      ".Lactor_visibility_at_point_5:\n\t"
      "flds 0x2533f0\n\t"
      "jmp .Lactor_visibility_at_point_8\n\t"
      ".Lactor_visibility_at_point_6:\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Lactor_visibility_at_point_8\n\t"
      ".Lactor_visibility_at_point_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x4f4\n\t"
      "pushl $0x255fb0\n\t"
      "pushl $0x255ee8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "flds -0x10(%%ebp)\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_visibility_at_point_8:\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds (%%edx)\n\t"
      "fsubs (%%ecx)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x4(%%edx)\n\t"
      "fsubs 0x4(%%ecx)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x8(%%edx)\n\t"
      "fsubs 0x8(%%ecx)\n\t"
      "fsts -0x14(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_visibility_at_point_22\n\t"
      "testb $1, (%%esi)\n\t"
      "movl $0x3f800000, -0x4(%%ebp)\n\t"
      "jne .Lactor_visibility_at_point_10\n\t"
      "movsbl 0x14(%%ebp), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .Lactor_visibility_at_point_9\n\t"
      "decl %%eax\n\t"
      "jne .Lactor_visibility_at_point_10\n\t"
      "movl $0x3f333333, -0x4(%%ebp)\n\t"
      "jmp .Lactor_visibility_at_point_10\n\t"
      ".Lactor_visibility_at_point_9:\n\t"
      "movl $0x3e99999a, -0x4(%%ebp)\n\t"
      ".Lactor_visibility_at_point_10:\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "addl $0x24, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18e690]\n\t"
      "fsts -0x10(%%ebp)\n\t"
      "fcomps 0x2533f0\n\t"
      "addl $0xc, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_visibility_at_point_12\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x2549d4\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_visibility_at_point_11\n\t"
      "flds 0x2533f0\n\t"
      "fsubs -0x10(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fmuls 0x256144\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".Lactor_visibility_at_point_11:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x256140\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_visibility_at_point_13\n\t"
      ".Lactor_visibility_at_point_12:\n\t"
      "movl $0x3e19999a, -0x4(%%ebp)\n\t"
      ".Lactor_visibility_at_point_13:\n\t"
      "movl 0x331f58, %%ecx\n\t"
      "movb 0x20(%%ebp), %%al\n\t"
      "movl %%ebx, %%esi\n\t"
      "andl $0xffff, %%esi\n\t"
      "imull $0x657c, %%esi, %%esi\n\t"
      "addl %%ecx, %%esi\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_visibility_at_point_14\n\t"
      "call *%[gtime]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl %%eax, 0x656c(%%esi)\n\t"
      "movl %%ecx, 0x6570(%%esi)\n\t"
      "movl %%edx, 0x6574(%%esi)\n\t"
      ".Lactor_visibility_at_point_14:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_visibility_at_point_21\n\t"
      "movb 0x6(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_visibility_at_point_17\n\t"
      "movb 0x1c(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_visibility_at_point_17\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x194(%%edi)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x190(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x18c(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x1a0(%%edi)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x19c(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x198(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x1ac(%%edi)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x1a8(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x1a4(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fxch %%st(1)\n\t"
      "fxch %%st(1)\n\t"
      "fpatan\n\t"
      "fcoms 0x25613c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_visibility_at_point_15\n\t"
      "fcomps 0x256138\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lactor_visibility_at_point_16\n\t"
      "flds -0x24(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "flds -0x28(%%ebp)\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "fpatan\n\t"
      "pushl %%eax\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fabs\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c2f470]\n\t"
      "flds -0x10(%%ebp)\n\t"
      "addl $0x18, %%esp\n\t"
      "jmp .Lactor_visibility_at_point_18\n\t"
      ".Lactor_visibility_at_point_15:\n\t"
      "fstp %%st(0)\n\t"
      ".Lactor_visibility_at_point_16:\n\t"
      "flds 0x2533c0\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "jmp .Lactor_visibility_at_point_18\n\t"
      ".Lactor_visibility_at_point_17:\n\t"
      "flds 0x2533c4\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x8(%%ebp)\n\t"
      ".Lactor_visibility_at_point_18:\n\t"
      "cmpw $0, 0x18(%%ebp)\n\t"
      "jne .Lactor_visibility_at_point_20\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fcomps -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_visibility_at_point_20\n\t"
      "fstp %%st(0)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x255fd8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_visibility_at_point_19\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $3, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_visibility_at_point_19:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $2, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_visibility_at_point_20:\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_visibility_at_point_22\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_visibility_at_point_21:\n\t"
      "fstp %%st(0)\n\t"
      ".Lactor_visibility_at_point_22:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lactor_visibility_at_point_23:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lactor_visibility_at_point_jt:\n\t"
      ".long .Lactor_visibility_at_point_3\n\t"
      ".long .Lactor_visibility_at_point_4\n\t"
      ".long .Lactor_visibility_at_point_5\n\t"
      ".long .Lactor_visibility_at_point_6\n\t"
      ".text\n\t"
      :
      : [dget] "m"(b314f0_dget), [tag] "m"(b314f0_tag), [c211f0] "m"(b314f0_c211f0), [assert] "m"(b314f0_assert), [exitfn] "m"(b314f0_exitfn), [c18e690] "m"(b314f0_c18e690), [gtime] "m"(b314f0_gtime), [c2f470] "m"(b314f0_c2f470)
      : "memory");
}
#else
#error "actor_visibility_at_point: clang naked draft required"
#endif


extern void *scenario_get(void);
extern uint8_t structure_bsp_cluster_sound_encoding(void *bsp,
                                                    int16_t from_cluster,
                                                    int16_t to_cluster);

/* 0x31850 — audibility level from volume, distance, and cluster encoding. */
int actor_audibility_at_point(int actor_handle, void *input_block,
                              float *position, void *location, short volume,
                              int range_scale, short flags)
{
  char *actor;
  char *encounter;
  char *in;
  char *loc;
  float range;
  float delta[3];
  float rel_dot;
  float dist_sq;
  float attenuation;
  float sqrt_dist;
  int16_t result;
  int profile;
  void *scenario;
  uint8_t encoding;

  (void)range_scale;

  attenuation = 0.0f;
  result = 0;
  if (volume == 0)
    return 0;

  actor = (char *)datum_get(actor_data, actor_handle);
  encounter = (char *)tag_get('rtca', *(int *)(actor + 0x58));
  in = (char *)input_block;
  loc = (char *)location;

  if (*(int16_t *)(in + 0x28) == -1)
    return 0;
  if (*(int16_t *)(loc + 4) == -1)
    return 0;

  range = *(float *)(encounter + 0x4c);
  delta[0] = position[0] - *(float *)in;
  delta[1] = position[1] - *(float *)(in + 4);
  delta[2] = position[2] - *(float *)(in + 8);
  dist_sq = delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2];

  rel_dot = delta[0] * *(float *)(in + 0x18) +
            delta[1] * *(float *)(in + 0x1c) +
            delta[2] * *(float *)(in + 0x20);
  if (rel_dot <= *(float *)0x2533c0)
    range *= *(float *)0x2533f0;

  switch (*(int16_t *)(actor + 0x6a)) {
  case 2:
    range *= *(float *)0x2533c4;
    break;
  case 1:
    range *= *(float *)0x253524;
    break;
  default:
    break;
  }

  switch (volume) {
  case 4:
    range *= *(float *)0x2549d4;
    break;
  case 1:
    range *= *(float *)0x25614c;
    break;
  case 3:
    range *= *(float *)0x2533c4;
    break;
  default:
    break;
  }

  if (FUN_0018e5c0((int)(uintptr_t)(in + 0x24)) ||
      FUN_0018e5c0((int)(uintptr_t)loc))
    range *= *(float *)0x25337c;

  if (flags != 0 && flags != 1)
    range *= *(float *)0x2533c4;

  if (range * range <= dist_sq)
    goto profile;

  scenario = scenario_get();
  encoding = structure_bsp_cluster_sound_encoding(
      scenario, *(int16_t *)(in + 0x28), *(int16_t *)(loc + 4));
  if ((char)encoding < 0)
    goto profile;

  attenuation = (float)(encoding & 0x7f) * *(float *)0x256148;
  sqrt_dist = sqrtf(dist_sq);
  if (attenuation + attenuation < sqrt_dist)
    sqrt_dist = attenuation + attenuation;
  if (sqrt_dist <= range) {
    result = (int16_t)(volume >= 3 ? 3 : 2);
    goto finish;
  }

profile:
  sqrt_dist = sqrtf(dist_sq);

finish:
  profile = (actor_handle & 0xffff) * 0x657c + *(int *)0x331f58;
  *(float *)(profile + 0xa8) = range;
  *(float *)(profile + 0xb0) = attenuation;
  *(char *)(profile + 0xa4) = 1;
  *(int16_t *)(profile + 0xa6) = result;
  *(float *)(profile + 0xac) = sqrt_dist;
  *(float *)(profile + 0xb4) = dist_sq;
  return result;
}

/* 0x31a90 — fill actor sense input block from closest swarm member. */
void actor_perception_find_sense_position(int actor_handle, float *position,
                                          int param_3, void *input_block_out)
{
  char *actor;
  char *swarm;
  char *member;
  int16_t member_index;
  int16_t member_count;
  int best_unit;
  float best_dist_sq;
  float delta[3];
  float dist_sq;
  int i;

  (void)param_3;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(char *)(actor + 6) == 0) {
    char *src = actor + 0x120;
    char *dst = (char *)input_block_out;
    for (i = 0; i < 0xe; i++)
      *(int *)(dst + i * 4) = *(int *)(src + i * 4);
    return;
  }

  if (*(int16_t *)(actor + 0x1e) <= 0) {
    display_assert("actor->swarm_data.swarm_count>0",
                   "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0x665, 1);
    system_exit(-1);
  }
  if (*(int *)(actor + 0x24) == -1) {
    display_assert("actor->swarm_data.unit!=NONE",
                   "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0x666, 1);
    system_exit(-1);
  }

  swarm = (char *)datum_get(*(void **)0x6325a0, *(int *)(actor + 0x28));
  best_unit = -1;
  best_dist_sq = 3.4028235e38f;
  member_count = *(int16_t *)(swarm + 2);

  for (member_index = 0; member_index < member_count; member_index++) {
    member = (char *)datum_get(
        *(void **)0x63259c,
        *(int *)(swarm + member_index * 4 + 0x58));
    delta[0] = position[0] - *(float *)(member + 4);
    delta[1] = position[1] - *(float *)(member + 8);
    delta[2] = position[2] - *(float *)(member + 0xc);
    dist_sq = delta[0] * delta[0] + delta[1] * delta[1] +
              delta[2] * delta[2];
    if (dist_sq <= best_dist_sq) {
      best_dist_sq = dist_sq;
      best_unit = *(int *)(swarm + member_index * 4 + 0x18);
    }
  }

  if (best_unit == -1) {
    display_assert("result!=NONE",
                   "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0x677, 1);
    system_exit(-1);
  }

  FUN_0003bde0(actor_handle, best_unit, (char *)input_block_out);
}

#if defined(__i386__) && defined(__GNUC__)
__attribute__((regparm(1)))
#endif
/* 0x31c00 — pick the closest swarm member unit to a reference point.
 * Owner handle arrives in EAX; swarm_origin pointer in EDI at the XBE call site. */
int actor_perception_unit_from_swarm(int owner_handle, int unit_handle,
                                     char verify_flag, float *swarm_origin)
{
  char *owner_actor;
  char *swarm;
  char *unit;
  int best_unit;
  float best_dist_sq;
  int16_t member_count;
  int member_index;
  float delta[3];
  float dist_sq;

  owner_actor = (char *)datum_get(actor_data, owner_handle);
  if (*(char *)(owner_actor + 6) == 0) {
    display_assert("actor->meta.active",
                   "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0x68d, 1);
    system_exit(-1);
  }

  best_unit = -1;
  best_dist_sq = 3.4028235e38f;
  {
    float *origin = (float *)((char *)swarm_origin + 0xc);

    if (*(int *)(owner_actor + 0x28) != -1) {
      swarm = (char *)datum_get(*(void **)0x6325a0, *(int *)(owner_actor + 0x28));
      member_count = *(int16_t *)(swarm + 2);
      for (member_index = 0; member_index < member_count; member_index++) {
        char *member =
            (char *)datum_get(*(void **)0x63259c,
                              *(int *)(swarm + member_index * 4 + 0x58));
        delta[0] = origin[0] - *(float *)(member + 4);
        delta[1] = origin[1] - *(float *)(member + 8);
        delta[2] = origin[2] - *(float *)(member + 0xc);
        dist_sq = delta[0] * delta[0] + delta[1] * delta[1] +
                  delta[2] * delta[2];
        if ((*(char *)(member + 2) & 2) != 0)
          dist_sq *= *(float *)0x2561f0;
        else if (*(int *)(swarm + member_index * 4 + 0x18) == unit_handle)
          dist_sq *= *(float *)0x256134;
        if (dist_sq <= best_dist_sq) {
          best_dist_sq = dist_sq;
          best_unit = *(int *)(swarm + member_index * 4 + 0x18);
        }
        if (verify_flag)
          object_mark(*(int *)(swarm + member_index * 4 + 0x18));
      }
    } else {
      int chain_unit = *(int *)(owner_actor + 0x24);
      while (chain_unit != -1) {
        float unit_pos[3];
        unit = (char *)object_get_and_verify_type(chain_unit, 3);
        object_get_world_position(chain_unit, (vector3_t *)unit_pos);
        delta[0] = origin[0] - unit_pos[0];
        delta[1] = origin[1] - unit_pos[1];
        delta[2] = origin[2] - unit_pos[2];
        dist_sq = delta[0] * delta[0] + delta[1] * delta[1] +
                  delta[2] * delta[2];
        if (chain_unit == unit_handle)
          dist_sq *= *(float *)0x256134;
        if (dist_sq <= best_dist_sq) {
          best_dist_sq = dist_sq;
          best_unit = chain_unit;
        }
        if (verify_flag)
          object_mark(chain_unit);
        chain_unit = *(int *)(unit + 0x1ac);
      }
    }
  }

  if (unit_handle != -1 && best_unit == -1) {
    display_assert("result != NONE",
                   "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0x6d9, 1);
    system_exit(-1);
  }
  return best_unit;
}

/* prop_position_refresh (0x31df0) — XBE naked draft (batch 80). */
#if defined(__clang__)
static void *(*const b31df0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b31df0_get)(int, int) = object_get_and_verify_type;
static float (*const b31df0_c12170)(float *vector) = FUN_00012170;
static int (*const b31df0_gtime)(void) = game_time_get;
static int (*const b31df0_c31c00)(int owner_handle, int unit_handle, char verify_flag, float *swarm_origin) = actor_perception_unit_from_swarm;
static void (*const b31df0_c1a9200)(int object_handle, float *out_position) = unit_get_head_position;
static vector3_t * (*const b31df0_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static void (*const b31df0_c1a9520)(int object_handle, float *out_position) = FUN_001a9520;
static int (*const b31df0_c13d7f0)(int object_handle) = object_get_root_parent;
static bool (*const b31df0_c18f3e0)(void *location, void *position, int16_t *out_sky_index) = FUN_0018f3e0;
static char (*const b31df0_c1b55c0)(int vehicle_handle) = vehicle_hover;
static void (*const b31df0_c31a90)(int actor_handle, float *position, int param_3, void *input_block_out) = actor_perception_find_sense_position;
static float (*const b31df0_norm)(float *) = normalize3d;

__attribute__((naked, noinline))
void prop_position_refresh(int actor_handle __attribute__((unused)), int prop_handle __attribute__((unused)), float *out_pos __attribute__((unused)), char refresh_flag __attribute__((unused)), char swarm_refresh __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movb 0x8(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "je .Lprop_position_refresh_18\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movb 0x14(%%ebp), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "jne .Lprop_position_refresh_4\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .Lprop_position_refresh_4\n\t"
      "cmpw $5, %%ax\n\t"
      "jg .Lprop_position_refresh_4\n\t"
      "movb 0x4e(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lprop_position_refresh_16\n\t"
      "testb $4, 0xb6(%%edi)\n\t"
      "je .Lprop_position_refresh_1\n\t"
      "cmpw $0, 0x3d0(%%edi)\n\t"
      "jne .Lprop_position_refresh_1\n\t"
      "cmpw $0, 0x30(%%esi)\n\t"
      "jne .Lprop_position_refresh_1\n\t"
      "leal 0x18(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c12170]\n\t"
      "fcomps 0x255d1c\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lprop_position_refresh_1\n\t"
      "movb $1, %%al\n\t"
      "jmp .Lprop_position_refresh_2\n\t"
      ".Lprop_position_refresh_1:\n\t"
      "xorb %%al, %%al\n\t"
      ".Lprop_position_refresh_2:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "cmpl %%ebx, 0x270(%%edx)\n\t"
      "jne .Lprop_position_refresh_3\n\t"
      "movb 0xb9(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lprop_position_refresh_16\n\t"
      "movb 0xba(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lprop_position_refresh_16\n\t"
      ".Lprop_position_refresh_3:\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_position_refresh_16\n\t"
      "movb $1, 0x4e(%%esi)\n\t"
      "movb $1, 0x127(%%esi)\n\t"
      ".Lprop_position_refresh_4:\n\t"
      "movb 0x14(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_position_refresh_8\n\t"
      "cmpl $-1, 0x1c(%%esi)\n\t"
      "je .Lprop_position_refresh_8\n\t"
      "movb 0x18(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_position_refresh_8\n\t"
      "call *%[gtime]\n\t"
      "movl 0x28(%%esi), %%ecx\n\t"
      "addl $0x5a, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jg .Lprop_position_refresh_8\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "movl %%eax, 0x28(%%esi)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "addl $0x120, %%edi\n\t"
      "call *%[c31c00]\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .Lprop_position_refresh_7\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, 0x18(%%esi)\n\t"
      "call *%[get]\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .Lprop_position_refresh_5\n\t"
      "cmpw $5, %%ax\n\t"
      "jg .Lprop_position_refresh_5\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "jmp .Lprop_position_refresh_6\n\t"
      ".Lprop_position_refresh_5:\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lprop_position_refresh_7\n\t"
      "pushl %%eax\n\t"
      ".Lprop_position_refresh_6:\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "movl %%ecx, 0x18(%%eax)\n\t"
      ".Lprop_position_refresh_7:\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      ".Lprop_position_refresh_8:\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "leal 0x104(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a9200]\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "leal 0xbc(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1412f0]\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "leal 0xc8(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a9520]\n\t"
      "addl $0x18, %%edi\n\t"
      "movl (%%edi), %%edx\n\t"
      "leal 0xd4(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl $0xffffffff, 0xec(%%esi)\n\t"
      "leal 0xfc(%%esi), %%edi\n\t"
      "call *%[c13d7f0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0x48(%%eax), %%ecx\n\t"
      "pushl $0\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "movl 0x4c(%%eax), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%edx, 0x4(%%edi)\n\t"
      "call *%[c18f3e0]\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "movb %%al, 0x118(%%esi)\n\t"
      "movl %%ebx, 0x110(%%esi)\n\t"
      "movb $0, 0x135(%%esi)\n\t"
      "movb $0, 0x136(%%esi)\n\t"
      "movl %%ebx, 0x114(%%esi)\n\t"
      "movl 0xcc(%%edi), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .Lprop_position_refresh_13\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movw 0x64(%%eax), %%cx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $1, %%cx\n\t"
      "jne .Lprop_position_refresh_12\n\t"
      "movl 0xcc(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x110(%%esi)\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "cmpl %%ecx, 0x2d8(%%eax)\n\t"
      "je .Lprop_position_refresh_9\n\t"
      "cmpw $0xf, 0x10(%%esi)\n\t"
      "je .Lprop_position_refresh_9\n\t"
      "xorl %%edx, %%edx\n\t"
      "jmp .Lprop_position_refresh_10\n\t"
      ".Lprop_position_refresh_9:\n\t"
      "movl $1, %%edx\n\t"
      ".Lprop_position_refresh_10:\n\t"
      "movb %%dl, 0x135(%%esi)\n\t"
      "cmpl %%ecx, 0x2d4(%%eax)\n\t"
      "jne .Lprop_position_refresh_11\n\t"
      "movl 0x110(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1b55c0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_position_refresh_11\n\t"
      "movl $1, %%eax\n\t"
      "movb %%al, 0x136(%%esi)\n\t"
      "jmp .Lprop_position_refresh_13\n\t"
      ".Lprop_position_refresh_11:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb %%al, 0x136(%%esi)\n\t"
      "jmp .Lprop_position_refresh_13\n\t"
      ".Lprop_position_refresh_12:\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "testb $3, %%al\n\t"
      "je .Lprop_position_refresh_13\n\t"
      "movl 0xcc(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x114(%%esi)\n\t"
      ".Lprop_position_refresh_13:\n\t"
      "movb $0, 0x125(%%esi)\n\t"
      "movl 0xc8(%%edi), %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .Lprop_position_refresh_16\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lprop_position_refresh_14:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movb 0x64(%%eax), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "testb $3, %%dl\n\t"
      "je .Lprop_position_refresh_15\n\t"
      "incb 0x125(%%esi)\n\t"
      ".Lprop_position_refresh_15:\n\t"
      "movl 0xc4(%%eax), %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jne .Lprop_position_refresh_14\n\t"
      ".Lprop_position_refresh_16:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal 0xbc(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[c31a90]\n\t"
      "flds (%%ebx)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "fsubs 0xc(%%eax)\n\t"
      "leal 0xe0(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "fstps (%%edi)\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fsubs 0x10(%%eax)\n\t"
      "fstps 0x4(%%edi)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fsubs 0x14(%%eax)\n\t"
      "fstps 0x8(%%edi)\n\t"
      "call *%[norm]\n\t"
      "fsts 0x11c(%%esi)\n\t"
      "addl $0x14, %%esp\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lprop_position_refresh_17\n\t"
      "movl 0x31fc3c, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%edi)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%edi)\n\t"
      ".Lprop_position_refresh_17:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".Lprop_position_refresh_18:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b31df0_dget), [get] "m"(b31df0_get), [c12170] "m"(b31df0_c12170), [gtime] "m"(b31df0_gtime), [c31c00] "m"(b31df0_c31c00), [c1a9200] "m"(b31df0_c1a9200), [c1412f0] "m"(b31df0_c1412f0), [c1a9520] "m"(b31df0_c1a9520), [c13d7f0] "m"(b31df0_c13d7f0), [c18f3e0] "m"(b31df0_c18f3e0), [c1b55c0] "m"(b31df0_c1b55c0), [c31a90] "m"(b31df0_c31a90), [norm] "m"(b31df0_norm)
      : "memory");
}
#else
#error "prop_position_refresh: clang naked draft required"
#endif


/* 0x32170 — register a vehicle danger zone on an actor. */
char FUN_00032170(float *sense_pos_out, int actor_handle, int unit_handle,
                  char flag)
{
  char *actor;
  char *vehicle;
  char *vehicle_def;
  char sense_block[0x4c];
  char *sense_pos;
  float world_pos[3];
  float delta[3];
  float dist;
  float vel_sq;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(int *)(actor + 0x158) != -1)
    return 0;

  vehicle = (char *)object_get_and_verify_type(unit_handle, 2);
  vehicle_def = (char *)tag_get('ihev', *(int *)vehicle);
  if (*(char *)(vehicle_def + 0x2f0) >= 0)
    return 0;

  vel_sq = *(float *)(vehicle + 0x18) * *(float *)(vehicle + 0x18) +
           *(float *)(vehicle + 0x1c) * *(float *)(vehicle + 0x1c) +
           *(float *)(vehicle + 0x20) * *(float *)(vehicle + 0x20);
  if (vel_sq > *(float *)0x25620c)
    return 0;

  object_get_world_position(unit_handle, (vector3_t *)world_pos);
  if (sense_pos_out == 0) {
    actor_perception_find_sense_position(actor_handle, world_pos, -1,
                                         sense_block);
    sense_pos = sense_block;
  } else {
    sense_pos = (char *)sense_pos_out;
  }

  delta[0] = world_pos[0] - *(float *)(sense_pos + 0xc);
  delta[1] = world_pos[1] - *(float *)(sense_pos + 0x10);
  delta[2] = world_pos[2] - *(float *)(sense_pos + 0x14);
  dist = sqrtf(delta[0] * delta[0] + delta[1] * delta[1] +
               delta[2] * delta[2]);

  if (dist > *(float *)(vehicle_def + 4) + *(float *)0x253f34)
    return 0;

  if (*(int16_t *)(actor + 0x280) >= 3) {
    if (*(int16_t *)(actor + 0x280) != 3)
      return 0;
    if (*(int *)(actor + 0x28c) == unit_handle &&
        dist <= *(float *)(actor + 0x2d4))
      return 0;
  }

  csmemset(actor + 0x280, 0, 0x6c);
  *(int *)(actor + 0x28c) = unit_handle;
  *(int16_t *)(actor + 0x280) = 3;
  *(int *)(actor + 0x290) = *(int *)(vehicle + 0x2d4);
  *(int *)(actor + 0x294) = *(int *)(vehicle_def + 4);
  *(float *)(actor + 0x298) = world_pos[0];
  *(float *)(actor + 0x29c) = world_pos[1];
  *(float *)(actor + 0x2a0) = world_pos[2];
  *(float *)(actor + 0x2a4) = *(float *)(vehicle + 0x18);
  *(float *)(actor + 0x2a8) = *(float *)(vehicle + 0x1c);
  *(float *)(actor + 0x2ac) = *(float *)(vehicle + 0x20);
  *(int16_t *)(actor + 0x284) = 0x14;
  *(char *)(actor + 0x286) = flag;
  *(int16_t *)(actor + 0x282) = 0;

  if (*(int *)(actor + 0x290) != -1) {
    char *parent =
        (char *)object_get_and_verify_type(*(int *)(vehicle + 0x2d4), 3);
    if (!game_allegiance_get_team_is_friendly(*(int16_t *)(actor + 0x3e),
                                              *(int16_t *)(parent + 0x68)))
      *(int16_t *)(actor + 0x282) = 1;
  }
  return 1;
}

/* actor_perception_refresh_danger_zone (0x32380) — XBE naked draft (batch 79). */
#if defined(__clang__)
static void *(*const b32380_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b32380_tryget)(int, int) = object_try_and_get_and_verify_type;
static void (*const b32380_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b32380_exitfn)(int) = system_exit;
static vector3_t * (*const b32380_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static void (*const b32380_c31a90)(int actor_handle, float *position, int param_3, void *input_block_out) = actor_perception_find_sense_position;
static void *(*const b32380_tag)(int, int) = tag_get;
static float (*const b32380_c12170)(float *vector) = FUN_00012170;
static int (*const b32380_c64ab0)(int actor_handle, int object_handle) = prop_get_active_by_unit_index;
static int (*const b32380_c13d7f0)(int object_handle) = object_get_root_parent;
static void *(*const b32380_get)(int, int) = object_get_and_verify_type;
static int (*const b32380_c416e0)(float *origin, int bsp, float *target, int param_4, short param_5, char param_6, int param_7, char param_8) = ai_test_line_of_sight;
static uint16_t (*const b32380_c2f380)(int actor_handle, int prop_handle) = FUN_0002f380;
static int16_t (*const b32380_c314f0)(int actor_handle, float *out_pos, float *head_pos, char vis_type, int16_t los_result, char flag, int param_7, int16_t engagement) = actor_visibility_at_point;
static int (*const b32380_c31850)(int actor_handle, void *input_block, float *position, void *location, short volume, int range_scale, short flags) = actor_audibility_at_point;
static int (*const b32380_c1a84c0)(int unit_handle, int16_t *animation_state_out) = unit_get_animation_frames_remaining;
static int (*const b32380_c27a60)(int actor_handle, short look_type, short priority, short *look_buf) = FUN_00027a60;

__attribute__((naked, noinline))
void actor_perception_refresh_danger_zone(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x58, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, 0x280(%%esi)\n\t"
      "jle .Lactor_perception_refresh_danger_zone_28\n\t"
      "movl 0x28c(%%esi), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[tryget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "jne .Lactor_perception_refresh_danger_zone_1\n\t"
      "popl %%ebx\n\t"
      "movw %%ax, 0x280(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_perception_refresh_danger_zone_1:\n\t"
      "movw 0x280(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "je .Lactor_perception_refresh_danger_zone_2\n\t"
      "cmpw $3, %%ax\n\t"
      "je .Lactor_perception_refresh_danger_zone_2\n\t"
      "cmpw $1, %%ax\n\t"
      "je .Lactor_perception_refresh_danger_zone_2\n\t"
      "pushl $1\n\t"
      "pushl $0xc9b\n\t"
      "pushl $0x255fb0\n\t"
      "pushl $0x256248\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_perception_refresh_danger_zone_2:\n\t"
      "movl 0x28c(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "leal 0x2b0(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1412f0]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "leal -0x58(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c31a90]\n\t"
      "leal 0x2bc(%%esi), %%eax\n\t"
      "leal 0x18(%%ebx), %%ecx\n\t"
      "movl (%%ecx), %%ebx\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%ebx, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%ebx\n\t"
      "movl %%ebx, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "flds (%%edi)\n\t"
      "fsubs -0x4c(%%ebp)\n\t"
      "addl $0x18, %%esp\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs -0x48(%%ebp)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsubs -0x44(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstps 0x2d4(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds (%%eax)\n\t"
      "fmuls 0x2548f8\n\t"
      "fadds (%%edi)\n\t"
      "fstps 0x2c8(%%esi)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x2548f8\n\t"
      "fadds 0x4(%%edi)\n\t"
      "fstps 0x2cc(%%esi)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x2548f8\n\t"
      "fadds 0x8(%%edi)\n\t"
      "fstps 0x2d0(%%esi)\n\t"
      "flds 0x2c8(%%esi)\n\t"
      "fadds (%%edi)\n\t"
      "fmuls 0x253398\n\t"
      "fstps 0x2dc(%%esi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fadds 0x2cc(%%esi)\n\t"
      "fmuls 0x253398\n\t"
      "fstps 0x2e0(%%esi)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fadds 0x2d0(%%esi)\n\t"
      "fmuls 0x253398\n\t"
      "fstps 0x2e4(%%esi)\n\t"
      "flds (%%edi)\n\t"
      "fsubs 0x2dc(%%esi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs 0x2e0(%%esi)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsubs 0x2e4(%%esi)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "movswl 0x280(%%esi), %%eax\n\t"
      "decl %%eax\n\t"
      ".byte 0xd8, 0xcc\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movb $0, -0x2(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fadds 0x294(%%esi)\n\t"
      "fstps 0x2d8(%%esi)\n\t"
      "je .Lactor_perception_refresh_danger_zone_21\n\t"
      "decl %%eax\n\t"
      "je .Lactor_perception_refresh_danger_zone_12\n\t"
      "decl %%eax\n\t"
      "jne .Lactor_perception_refresh_danger_zone_27\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x76656869\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0x18, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "call *%[c12170]\n\t"
      "fcomps 0x256240\n\t"
      "addl $0xc, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lactor_perception_refresh_danger_zone_11\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fadds 0x253f34\n\t"
      "fcomps 0x2d4(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lactor_perception_refresh_danger_zone_11\n\t"
      "movb 0x286(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "jne .Lactor_perception_refresh_danger_zone_26\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "movl 0x2d4(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_perception_refresh_danger_zone_3\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c64ab0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_perception_refresh_danger_zone_3\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, 0x30(%%eax)\n\t"
      "setge -0x1(%%ebp)\n\t"
      "jmp .Lactor_perception_refresh_danger_zone_25\n\t"
      ".Lactor_perception_refresh_danger_zone_3:\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lactor_perception_refresh_danger_zone_4\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lactor_perception_refresh_danger_zone_5\n\t"
      ".Lactor_perception_refresh_danger_zone_4:\n\t"
      "pushl %%eax\n\t"
      "movl 0x5ab270, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      ".Lactor_perception_refresh_danger_zone_5:\n\t"
      "cmpw $1, 0x6a(%%esi)\n\t"
      "movb $0, -0x5(%%ebp)\n\t"
      "je .Lactor_perception_refresh_danger_zone_6\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lactor_perception_refresh_danger_zone_7\n\t"
      "movb 0x40(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lactor_perception_refresh_danger_zone_7\n\t"
      ".Lactor_perception_refresh_danger_zone_6:\n\t"
      "movb $1, -0x5(%%ebp)\n\t"
      ".Lactor_perception_refresh_danger_zone_7:\n\t"
      "cmpl $-1, 0xcc(%%ebx)\n\t"
      "je .Lactor_perception_refresh_danger_zone_8\n\t"
      "movl 0x28c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13d7f0]\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      ".Lactor_perception_refresh_danger_zone_8:\n\t"
      "movl 0x158(%%esi), %%ecx\n\t"
      "movl 0x28c(%%esi), %%eax\n\t"
      "addl $0x48, %%ebx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "setne %%dl\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x4(%%ebx), %%cx\n\t"
      "pushl %%edx\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c416e0]\n\t"
      "addl $0x20, %%esp\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movb -0x5(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_refresh_danger_zone_10\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2f380]\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c314f0]\n\t"
      "addl $0x28, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .Lactor_perception_refresh_danger_zone_10\n\t"
      ".Lactor_perception_refresh_danger_zone_9:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lactor_perception_refresh_danger_zone_26\n\t"
      ".Lactor_perception_refresh_danger_zone_10:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x182(%%eax), %%cx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x3f800000\n\t"
      "leal -0x58(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c31850]\n\t"
      "addl $0x1c, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .Lactor_perception_refresh_danger_zone_27\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lactor_perception_refresh_danger_zone_26\n\t"
      ".Lactor_perception_refresh_danger_zone_11:\n\t"
      "movw $0, 0x280(%%esi)\n\t"
      "jmp .Lactor_perception_refresh_danger_zone_27\n\t"
      ".Lactor_perception_refresh_danger_zone_12:\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "je .Lactor_perception_refresh_danger_zone_13\n\t"
      "cmpl %%eax, 0xcc(%%ebx)\n\t"
      "jne .Lactor_perception_refresh_danger_zone_13\n\t"
      "movb $1, -0x2(%%ebp)\n\t"
      ".Lactor_perception_refresh_danger_zone_13:\n\t"
      "cmpw $5, 0x64(%%ebx)\n\t"
      "je .Lactor_perception_refresh_danger_zone_14\n\t"
      "pushl $1\n\t"
      "pushl $0xcb9\n\t"
      "pushl $0x255fb0\n\t"
      "pushl $0x256210\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_perception_refresh_danger_zone_14:\n\t"
      "flds 0x1f0(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_perception_refresh_danger_zone_15\n\t"
      "flds 0x1f4(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_perception_refresh_danger_zone_15\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x1f0(%%ebx)\n\t"
      "fdivs 0x1f4(%%ebx)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fistps -0xc(%%ebp)\n\t"
      "movw -0xc(%%ebp), %%cx\n\t"
      "movw %%cx, 0x2e8(%%esi)\n\t"
      "jmp .Lactor_perception_refresh_danger_zone_16\n\t"
      ".Lactor_perception_refresh_danger_zone_15:\n\t"
      "movw $0xffff, 0x2e8(%%esi)\n\t"
      ".Lactor_perception_refresh_danger_zone_16:\n\t"
      "movb 0x286(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_refresh_danger_zone_9\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_refresh_danger_zone_9\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jne .Lactor_perception_refresh_danger_zone_17\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lactor_perception_refresh_danger_zone_18\n\t"
      ".Lactor_perception_refresh_danger_zone_17:\n\t"
      "movl 0x5ab270, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      ".Lactor_perception_refresh_danger_zone_18:\n\t"
      "cmpw $1, 0x6a(%%esi)\n\t"
      "je .Lactor_perception_refresh_danger_zone_27\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lactor_perception_refresh_danger_zone_19\n\t"
      "movb 0x40(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lactor_perception_refresh_danger_zone_27\n\t"
      ".Lactor_perception_refresh_danger_zone_19:\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x70726f6a\n\t"
      "call *%[tag]\n\t"
      "flds 0x2d4(%%esi)\n\t"
      "fcomps 0x19c(%%eax)\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_perception_refresh_danger_zone_27\n\t"
      "cmpl $-1, 0xcc(%%ebx)\n\t"
      "movw 0x4c(%%ebx), %%ax\n\t"
      "je .Lactor_perception_refresh_danger_zone_20\n\t"
      "movl 0x28c(%%esi), %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13d7f0]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movw 0x4c(%%eax), %%ax\n\t"
      "addl $8, %%esp\n\t"
      ".Lactor_perception_refresh_danger_zone_20:\n\t"
      "cmpl $-1, 0x158(%%esi)\n\t"
      "movl 0x28c(%%esi), %%ecx\n\t"
      "setne %%dl\n\t"
      "pushl %%edx\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c416e0]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c2f380]\n\t"
      "leal -0x58(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl %%ebx\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c314f0]\n\t"
      "addl $0x48, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .Lactor_perception_refresh_danger_zone_27\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lactor_perception_refresh_danger_zone_26\n\t"
      ".Lactor_perception_refresh_danger_zone_21:\n\t"
      "movb 0x286(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "jne .Lactor_perception_refresh_danger_zone_22\n\t"
      "movl 0x28c(%%esi), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c64ab0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_perception_refresh_danger_zone_22\n\t"
      "pushl %%eax\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, 0x30(%%eax)\n\t"
      "setge -0x1(%%ebp)\n\t"
      ".Lactor_perception_refresh_danger_zone_22:\n\t"
      "movl 0x28c(%%esi), %%edx\n\t"
      "leal -0x6(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1a84c0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0x19, -0x6(%%ebp)\n\t"
      "jne .Lactor_perception_refresh_danger_zone_23\n\t"
      "movswl %%ax, %%eax\n\t"
      "jmp .Lactor_perception_refresh_danger_zone_24\n\t"
      ".Lactor_perception_refresh_danger_zone_23:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      ".Lactor_perception_refresh_danger_zone_24:\n\t"
      "movw %%ax, 0x2e8(%%esi)\n\t"
      ".Lactor_perception_refresh_danger_zone_25:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_perception_refresh_danger_zone_27\n\t"
      ".Lactor_perception_refresh_danger_zone_26:\n\t"
      "movb 0x286(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_refresh_danger_zone_27\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "pushl $0xc\n\t"
      "pushl %%ecx\n\t"
      "movw $5, -0x20(%%ebp)\n\t"
      "call *%[c27a60]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lactor_perception_refresh_danger_zone_27:\n\t"
      "movb -0x1(%%ebp), %%dl\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "movb %%dl, 0x286(%%esi)\n\t"
      "movb %%al, 0x28a(%%esi)\n\t"
      "popl %%ebx\n\t"
      ".Lactor_perception_refresh_danger_zone_28:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b32380_dget), [tryget] "m"(b32380_tryget), [assert] "m"(b32380_assert), [exitfn] "m"(b32380_exitfn), [c1412f0] "m"(b32380_c1412f0), [c31a90] "m"(b32380_c31a90), [tag] "m"(b32380_tag), [c12170] "m"(b32380_c12170), [c64ab0] "m"(b32380_c64ab0), [c13d7f0] "m"(b32380_c13d7f0), [get] "m"(b32380_get), [c416e0] "m"(b32380_c416e0), [c2f380] "m"(b32380_c2f380), [c314f0] "m"(b32380_c314f0), [c31850] "m"(b32380_c31850), [c1a84c0] "m"(b32380_c1a84c0), [c27a60] "m"(b32380_c27a60)
      : "memory");
}
#else
#error "actor_perception_refresh_danger_zone: clang naked draft required"
#endif


/* 0x32940 — scan actor props for a duplicate acknowledgement candidate. */
char actor_expected_acknowledgement(int actor_handle, int prop_handle)
{
  char *prop;
  char *other;
  char result;
  int iter[2];
  float dx;
  float dy;
  float dz;
  float dot;

  prop = (char *)datum_get(prop_data, prop_handle);
  if (*(int16_t *)(prop + 0x24) >= 4 && *(int16_t *)(prop + 0x24) <= 5) {
    display_assert("prop->status<4 || prop->status>5",
                   "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0xe22, 1);
    system_exit(-1);
  }

  result = 0;
  FUN_00064540(iter, actor_handle);
  while ((other = (char *)FUN_00064570(iter)) != 0) {
    int16_t other_status;

    if (iter[0] == prop_handle)
      continue;
    if (*(int *)(other + 0x18) != *(int *)(prop + 0x18) &&
        *(int *)(other + 0x1c) != *(int *)(prop + 0x1c))
      continue;
    if (*(char *)(prop + 0x60) == 0 || *(char *)(other + 0x60) == 0)
      continue;

    other_status = *(int16_t *)(other + 0x24);
    if ((other_status >= 4 && other_status <= 5) ||
        (other_status >= 2 && other_status <= 3)) {
      dx = *(float *)(prop + 0xbc) - *(float *)(other + 0xbc);
      dy = *(float *)(prop + 0xc0) - *(float *)(other + 0xc0);
      if (dx * dx + dy * dy > *(float *)0x253dcc)
        continue;
      dz = *(float *)(other + 0xc4) - *(float *)(prop + 0xc4);
      if (fabsf(dz) > *(double *)0x256310)
        continue;
      dot = *(float *)(other + 0xe0) * *(float *)(prop + 0xe0) +
            *(float *)(other + 0xe4) * *(float *)(prop + 0xe4) +
            *(float *)(other + 0xe8) * *(float *)(prop + 0xe8);
      if (dot >= *(float *)0x253398)
        continue;
      result = 1;
    }
  }
  return result;
}

/* 0x32ac0 */
void actor_perception_unreachable(int actor_handle, int prop_handle, char flag)
{
  char *prop;

  datum_get(actor_data, actor_handle);
  prop = (char *)datum_get(prop_data, prop_handle);

  if (flag != 0) {
    if (*(int16_t *)(prop + 0x9c) == 0)
      *(int16_t *)(prop + 0x9c) = 1;
    *(int *)(prop + 0xa0) = game_time_get();
  } else {
    *(int16_t *)(prop + 0x9c) = 0;
    *(int *)(prop + 0xa0) = -1;
  }

  *(char *)(prop + 0xa4) =
      (char)actor_get_perception_knowledge(actor_handle, prop_handle);
  *(float *)(prop + 0x50) =
      actor_compute_prop_target_weight(actor_handle, prop_handle);
}

/* 0x32b50 */
void actor_perception_tried_to_uncover(int actor_handle, int prop_handle)
{
  int eax = 0;
  int esi = 0;

  /* cmp esi, -1 -> je 0x32ba1 */
  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), actor_handle);
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), prop_handle);
  /* cmp esi, eax -> jne 0x32b9f */
  actor_situation_update_target_status(actor_handle);
  actor_situation_combat_status_update(actor_handle);

  (void)eax;
  (void)esi;
}

/* 0x32bb0 */
void actor_perception_tried_to_search(int actor_handle, int prop_handle)
{
  int eax = 0;
  int esi = 0;

  /* cmp esi, -1 -> je 0x32c01 */
  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), actor_handle);
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), prop_handle);
  /* cmp esi, eax -> jne 0x32bff */
  actor_situation_update_target_status(actor_handle);
  actor_situation_combat_status_update(actor_handle);

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
  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), actor_handle);
  actor_situation_combat_status_update(actor_handle);
  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), actor_handle);
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), actor_handle);
  /* relift: cmp word ptr [eax + 0x24], 4 -> jne 0x32c85 */
  /* relift: cmp esi, dword ptr [edi + 0x270] -> jne 0x32ca3 */
  actor_situation_update_target_status(actor_handle);
  actor_situation_combat_status_update(actor_handle);

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
  int local_14 = 0;

  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), actor_handle);
  tag_get('rtca', 0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x32d10 */
  /* relift: cmp word ptr [esi + 0x6a], (int16_t)edi -> jl 0x32d10 */
  /* relift: cmp dword ptr [esi + 0x1bc], 0x3f800000 -> jne 0x32d1e */
  /* cmp (int16_t)eax, (int16_t)edi -> jge 0x32d1e */
  actor_berserk(actor_handle, 0);
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
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), 0);
  FUN_00064540((void *)0, actor_handle);
  FUN_00064570((void *)0);
  /* test edi, edi -> je 0x3314b */
  /* cmp (int16_t)eax, 2 -> jl 0x33114 */
  /* cmp (int16_t)eax, 3 -> jg 0x33114 */
  /* test (char)eax, (char)eax -> jne 0x33114 */
  /* test (char)eax, (char)eax -> jne 0x33114 */
  /* test (char)eax, (char)eax -> jne 0x33114 */
  /* test (char)eax, (char)eax -> jne 0x32f65 */
  /* relift: cmp dword ptr [edi + 0x110], -1 -> jne 0x33114 */
  actor_perception_friend_prop_is_attacking(actor_handle, local_14, (void *)0);
  /* test (char)eax, (char)eax -> je 0x330e4 */
  actor_perception_aiming_vector_test_blockage();
  /* cmp (int16_t)ebx, 1 -> jl 0x32fbf */
  /* test (char)eax, (char)eax -> je 0x32fbf */
  /* test (char)eax, (char)eax -> je 0x330e4 */
  /* test (char)eax, (char)eax -> je 0x330e4 */
  FUN_00012170((void *)0);
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, (char)eax -> jne 0x3301c */
  /* relift: cmp word ptr [esi + 0x360], 0 -> jle 0x330e4 */
  normalize3d((void *)0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x330e4 */
  vector3d_scale_add((float *)((char *)eax + 0x12c), (void *)0, 0.0f, (void *)0);
  actor_perception_aiming_vector_test_blockage();
  /* cmp (int16_t)eax, (int16_t)ebx -> jg 0x33089 */
  /* cmp (int16_t)eax, 1 -> jl 0x330e4 */
  FUN_00012170((float *)0);
  /* relift: relift: fcomp dword ptr [0x25337c] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x2533dc] */
  /* test (char)eax, 0x41 -> jne 0x330e4 */
  /* test (char)eax, (char)eax -> je 0x33114 */
  actor_perception_aiming_vector_test_blockage();
  /* cmp (int16_t)eax, 2 -> jl 0x33114 */
  FUN_00064570((void *)0);
  /* test edi, edi -> jne 0x32f12 */
  /* test (char)eax, (char)eax -> je 0x33178 */
  FUN_00024be0(actor_handle, 0, 1);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x3318e */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x331a9 */
  /* test (char)eax, (char)eax -> je 0x331c8 */
  /* test (char)eax, (char)eax -> jne 0x331c8 */
  /* cmp eax, 4 -> ja 0x33243 */
  /* test (char)eax, 0x41 -> jne 0x33243 */
  /* test (char)eax, 0x41 -> jne 0x33243 */
  /* test (char)eax, (char)eax -> jle 0x33243 */
  FUN_00038370(actor_handle);
  /* relift: test dword ptr [ebx], 0x40000000 -> je 0x33271 */
  /* test (char)ecx, (char)ecx -> jne 0x3326f */
  /* test (char)ecx, (char)ecx -> je 0x33265 */
  /* test (char)ecx, (char)ecx -> je 0x33271 */
  /* test (char)ecx, (char)ecx -> je 0x332a4 */
  /* test (char)eax, (char)eax -> jne 0x332a0 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x332dc */
  /* test (char)ecx, (char)ecx -> jne 0x332e5 */
  /* test (char)eax, (char)eax -> je 0x332e5 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
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
  (void)local_14;
}

/* 0x33330 */
void actor_perception_become_acknowledged(int actor_handle, int prop_handle,
                                          char *param_3)
{
  char *prop;
  char *parent_prop;
  char parent_exists;
  char expected;

  expected = 0;
  prop = (char *)datum_get(prop_data, prop_handle);
  if (*(int16_t *)(prop + 0x24) >= 2 && *(int16_t *)(prop + 0x24) <= 3)
    goto finish;

  parent_exists = *(int *)(prop + 0xc) != -1;
  expected = actor_expected_acknowledgement(actor_handle, prop_handle);
  if (parent_exists != 0) {
    parent_prop = (char *)datum_get(prop_data, *(int *)(prop + 0xc));
    *(int *)(prop + 0x50) = *(int *)(parent_prop + 0x50);
    *(int *)(prop + 0x54) = *(int *)(parent_prop + 0x54);
    *(int *)(prop + 0x58) = *(int *)(parent_prop + 0x58);
    *(int *)(prop + 0x5c) = *(int *)(parent_prop + 0x5c);
    *(int16_t *)(prop + 0x9c) = *(int16_t *)(parent_prop + 0x9c);
    *(int *)(prop + 0xa0) = *(int *)(parent_prop + 0xa0);
    *(char *)(prop + 0xa4) = *(char *)(parent_prop + 0xa4);
    *(int16_t *)(prop + 0xa6) = *(int16_t *)(parent_prop + 0xa6);
    *(int16_t *)(prop + 0xa8) = *(int16_t *)(parent_prop + 0xa8);
    FUN_0003b410(actor_handle, *(int *)(prop + 0xc), prop_handle);
    prop_iterator_next(actor_handle, *(int *)(prop + 0xc));
    *(int *)(prop + 0xc) = -1;
  }

  *(int16_t *)(prop + 0x24) = 3;
  actor_perception_acknowledge(actor_handle, prop_handle, expected,
                               parent_exists);

finish:
  if (param_3 != 0)
    *param_3 = expected;
}

/* prop_status_refresh (0x33440) — XBE naked draft (batch 79). */
#if defined(__clang__)
static void *(*const b33440_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b33440_tag)(int, int) = tag_get;
static void *(*const b33440_get)(int, int) = object_get_and_verify_type;
static int (*const b33440_gtime)(void) = game_time_get;
static short (*const b33440_cfff80)(void) = game_connection;
static void (*const b33440_c140070)(int object_handle, float *position_out, float *direction_out) = object_get_root_location;
static int (*const b33440_c27a60)(int actor_handle, short look_type, short priority, short *look_buf) = FUN_00027a60;
static void (*const b33440_c1a9900)(int unit_handle, void *out_aiming) = unit_scripting_unit_driver;
static int (*const b33440_c416e0)(float *origin, int bsp, float *target, int param_4, short param_5, char param_6, int param_7, char param_8) = ai_test_line_of_sight;
static int16_t (*const b33440_c314f0)(int actor_handle, float *out_pos, float *head_pos, char vis_type, int16_t los_result, char flag, int param_7, int16_t engagement) = actor_visibility_at_point;
static bool (*const b33440_c3b100)(int actor_handle) = actor_is_noncombat;
static char (*const b33440_c3b120)(int actor) = FUN_0003b120;
static char (*const b33440_c3b150)(int actor_handle) = actor_is_fighting;
static uint16_t (*const b33440_c2f380)(int actor_handle, int prop_handle) = FUN_0002f380;
static int (*const b33440_c31850)(int actor_handle, void *input_block, float *position, void *location, short volume, int range_scale, short flags) = actor_audibility_at_point;
static int (*const b33440_c119270)(data_t *data, int absolute_index) = datum_absolute_index_to_index;
static char (*const b33440_c32170)(float *sense_pos_out, int actor_handle, int unit_handle, char flag) = FUN_00032170;
static char (*const b33440_c2f5f0)(int actor_handle, float scale, float visibility, int unit_handle, char field_60, char dz_flag) = FUN_0002f5f0;
static bool (*const b33440_c3b320)(int actor_handle) = actor_has_ranged_weapon;
static void (*const b33440_c32ac0)(int actor_handle, int prop_handle, char flag) = actor_perception_unreachable;
static int16_t (*const b33440_c1d6d0)(int actor_handle) = actor_action_try_to_panic;
static bool (*const b33440_c2fc20)(int actor_handle, int clump_item_handle) = actor_get_perception_knowledge;
static float (*const b33440_c2fd10)(int actor_handle, int clump_item_handle) = actor_compute_prop_target_weight;
static float (*const b33440_c278e0)(int actor_handle, int prop_handle) = FUN_000278e0;

__attribute__((naked, noinline))
void prop_status_refresh(int actor_handle __attribute__((unused)), int prop_handle __attribute__((unused)), float *out_pos __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x44, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movb 0x8(%%ebx), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "je .Lprop_status_refresh_120\n\t"
      "movl 0x58(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movl 0x34(%%ebx), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lprop_status_refresh_1\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "jmp .Lprop_status_refresh_2\n\t"
      ".Lprop_status_refresh_1:\n\t"
      "pushl %%eax\n\t"
      "movl 0x5ab270, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      ".Lprop_status_refresh_2:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%edi, -0x1c(%%ebp)\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lprop_status_refresh_3\n\t"
      "movl %%eax, %%ecx\n\t"
      "movb 0x40(%%ecx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lprop_status_refresh_4\n\t"
      ".Lprop_status_refresh_3:\n\t"
      "cmpw $1, 0x6a(%%ebx)\n\t"
      "movb $0, -0x4(%%ebp)\n\t"
      "jne .Lprop_status_refresh_5\n\t"
      ".Lprop_status_refresh_4:\n\t"
      "movb $1, -0x4(%%ebp)\n\t"
      ".Lprop_status_refresh_5:\n\t"
      "movl 0x1b4(%%edi), %%edx\n\t"
      "movb 0x12e(%%esi), %%al\n\t"
      "shrl $0xa, %%edx\n\t"
      "andb $1, %%dl\n\t"
      "testb %%al, %%al\n\t"
      "movb %%dl, 0x133(%%esi)\n\t"
      "je .Lprop_status_refresh_6\n\t"
      "call *%[cfff80]\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lprop_status_refresh_6\n\t"
      "movb 0x5ac9c6, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_6\n\t"
      "movb $1, 0x133(%%esi)\n\t"
      ".Lprop_status_refresh_6:\n\t"
      "movb 0x60(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_11\n\t"
      "movl 0x1b4(%%edi), %%eax\n\t"
      "shrl $0xb, %%eax\n\t"
      "andb $1, %%al\n\t"
      "movb %%al, 0x134(%%esi)\n\t"
      "movswl 0x1d4(%%ebx), %%eax\n\t"
      "decl %%eax\n\t"
      "je .Lprop_status_refresh_7\n\t"
      "decl %%eax\n\t"
      "jne .Lprop_status_refresh_11\n\t"
      "movb 0x12e(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_11\n\t"
      "jmp .Lprop_status_refresh_10\n\t"
      ".Lprop_status_refresh_7:\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lprop_status_refresh_11\n\t"
      "cmpl $-1, 0x1d8(%%ebx)\n\t"
      "je .Lprop_status_refresh_11\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x1d8(%%ebx), %%ecx\n\t"
      "movl 0x34(%%eax), %%edx\n\t"
      "xorl %%ecx, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "testl $0xffff, %%edx\n\t"
      "jne .Lprop_status_refresh_11\n\t"
      "shrl $0x1e, %%ecx\n\t"
      "subl $0, %%ecx\n\t"
      "je .Lprop_status_refresh_10\n\t"
      "decl %%ecx\n\t"
      "je .Lprop_status_refresh_8\n\t"
      "decl %%ecx\n\t"
      "jne .Lprop_status_refresh_11\n\t"
      "movzbl 0x1da(%%ebx), %%ecx\n\t"
      "cmpw 0x3c(%%eax), %%cx\n\t"
      "jmp .Lprop_status_refresh_9\n\t"
      ".Lprop_status_refresh_8:\n\t"
      "movzbl 0x1da(%%ebx), %%edx\n\t"
      "cmpw 0x3a(%%eax), %%dx\n\t"
      ".Lprop_status_refresh_9:\n\t"
      "jne .Lprop_status_refresh_11\n\t"
      ".Lprop_status_refresh_10:\n\t"
      "movb $1, 0x134(%%esi)\n\t"
      ".Lprop_status_refresh_11:\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "movsbw 0x123(%%esi), %%di\n\t"
      "pushl $0\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c140070]\n\t"
      "addl $0xc, %%esp\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls -0x34(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fcoms 0x256350\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lprop_status_refresh_12\n\t"
      "fstp %%st(0)\n\t"
      "movb $0, 0x123(%%esi)\n\t"
      "jmp .Lprop_status_refresh_15\n\t"
      ".Lprop_status_refresh_12:\n\t"
      "fcoms 0x25634c\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lprop_status_refresh_13\n\t"
      "fstp %%st(0)\n\t"
      "movb $1, 0x123(%%esi)\n\t"
      "jmp .Lprop_status_refresh_15\n\t"
      ".Lprop_status_refresh_13:\n\t"
      "fcomps 0x2546a4\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lprop_status_refresh_14\n\t"
      "movb $2, 0x123(%%esi)\n\t"
      "jmp .Lprop_status_refresh_15\n\t"
      ".Lprop_status_refresh_14:\n\t"
      "movb $3, 0x123(%%esi)\n\t"
      ".Lprop_status_refresh_15:\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fsubs 0x2c(%%ebx)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fsubs 0x30(%%ebx)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fsubs 0x34(%%ebx)\n\t"
      "fmuls 0xe8(%%esi)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0xe4(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0xe0(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fchs\n\t"
      "fsts -0x10(%%ebp)\n\t"
      "fcomps 0x256348\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lprop_status_refresh_16\n\t"
      "movb $0, 0x124(%%esi)\n\t"
      "jmp .Lprop_status_refresh_22\n\t"
      ".Lprop_status_refresh_16:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x256344\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lprop_status_refresh_17\n\t"
      "movb $1, 0x124(%%esi)\n\t"
      "jmp .Lprop_status_refresh_22\n\t"
      ".Lprop_status_refresh_17:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x256340\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lprop_status_refresh_18\n\t"
      "movb $2, 0x124(%%esi)\n\t"
      "jmp .Lprop_status_refresh_22\n\t"
      ".Lprop_status_refresh_18:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x256350\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lprop_status_refresh_19\n\t"
      "movb $3, 0x124(%%esi)\n\t"
      "jmp .Lprop_status_refresh_22\n\t"
      ".Lprop_status_refresh_19:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x25634c\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lprop_status_refresh_20\n\t"
      "movb $4, 0x124(%%esi)\n\t"
      "jmp .Lprop_status_refresh_22\n\t"
      ".Lprop_status_refresh_20:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x2546a4\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lprop_status_refresh_21\n\t"
      "movb $5, 0x124(%%esi)\n\t"
      "jmp .Lprop_status_refresh_22\n\t"
      ".Lprop_status_refresh_21:\n\t"
      "movb $6, 0x124(%%esi)\n\t"
      ".Lprop_status_refresh_22:\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .Lprop_status_refresh_23\n\t"
      "cmpw $3, %%ax\n\t"
      "jg .Lprop_status_refresh_23\n\t"
      "cmpw $1, %%di\n\t"
      "jg .Lprop_status_refresh_23\n\t"
      "cmpb $1, 0x123(%%esi)\n\t"
      "jle .Lprop_status_refresh_23\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "leal -0x44(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "pushl $2\n\t"
      "pushl %%ecx\n\t"
      "movw $1, -0x44(%%ebp)\n\t"
      "movl %%edx, -0x40(%%ebp)\n\t"
      "call *%[c27a60]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lprop_status_refresh_23:\n\t"
      "flds 0x11c(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lprop_status_refresh_24\n\t"
      "movb $0, 0x121(%%esi)\n\t"
      "jmp .Lprop_status_refresh_28\n\t"
      ".Lprop_status_refresh_24:\n\t"
      "flds 0x11c(%%esi)\n\t"
      "fcomps 0x254640\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lprop_status_refresh_25\n\t"
      "movb $1, 0x121(%%esi)\n\t"
      "jmp .Lprop_status_refresh_28\n\t"
      ".Lprop_status_refresh_25:\n\t"
      "flds 0x11c(%%esi)\n\t"
      "fcomps 0x253f34\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lprop_status_refresh_26\n\t"
      "movb $2, 0x121(%%esi)\n\t"
      "jmp .Lprop_status_refresh_28\n\t"
      ".Lprop_status_refresh_26:\n\t"
      "flds 0x11c(%%esi)\n\t"
      "fcomps 0x253394\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lprop_status_refresh_27\n\t"
      "movb $3, 0x121(%%esi)\n\t"
      "jmp .Lprop_status_refresh_28\n\t"
      ".Lprop_status_refresh_27:\n\t"
      "movb $4, 0x121(%%esi)\n\t"
      ".Lprop_status_refresh_28:\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1a9900]\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls 0xe4(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls 0xe8(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls 0xe0(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fchs\n\t"
      "fsts -0x10(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lprop_status_refresh_29\n\t"
      "flds 0x2548fc\n\t"
      "jmp .Lprop_status_refresh_31\n\t"
      ".Lprop_status_refresh_29:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lprop_status_refresh_30\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lprop_status_refresh_31\n\t"
      ".Lprop_status_refresh_30:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "fsubrs 0x2533c8\n\t"
      "fsqrt\n\t"
      "fmuls 0x11c(%%esi)\n\t"
      ".Lprop_status_refresh_31:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x25633c\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lprop_status_refresh_36\n\t"
      "fcoms 0x253398\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lprop_status_refresh_36\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x256338\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lprop_status_refresh_34\n\t"
      "fcomps 0x2533ec\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lprop_status_refresh_35\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x253398\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lprop_status_refresh_32\n\t"
      "movb $2, 0x122(%%esi)\n\t"
      "jmp .Lprop_status_refresh_37\n\t"
      ".Lprop_status_refresh_32:\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lprop_status_refresh_33\n\t"
      "movb $3, 0x122(%%esi)\n\t"
      "jmp .Lprop_status_refresh_37\n\t"
      ".Lprop_status_refresh_33:\n\t"
      "movb $4, 0x122(%%esi)\n\t"
      "jmp .Lprop_status_refresh_37\n\t"
      ".Lprop_status_refresh_34:\n\t"
      "fstp %%st(0)\n\t"
      ".Lprop_status_refresh_35:\n\t"
      "movb $1, 0x122(%%esi)\n\t"
      "jmp .Lprop_status_refresh_37\n\t"
      ".Lprop_status_refresh_36:\n\t"
      "fstp %%st(0)\n\t"
      "movb $0, 0x122(%%esi)\n\t"
      ".Lprop_status_refresh_37:\n\t"
      "cmpw $1, 0x66(%%esi)\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "sete %%cl\n\t"
      "cmpw $4, %%ax\n\t"
      "movb %%cl, 0x12f(%%esi)\n\t"
      "jl .Lprop_status_refresh_41\n\t"
      "cmpw $5, %%ax\n\t"
      "jg .Lprop_status_refresh_41\n\t"
      "movb 0x12e(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_38\n\t"
      "movb 0x60(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_38\n\t"
      "movl $2, %%eax\n\t"
      "jmp .Lprop_status_refresh_39\n\t"
      ".Lprop_status_refresh_38:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lprop_status_refresh_39:\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl 0x158(%%edx), %%ecx\n\t"
      "movl 0x110(%%esi), %%edx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "setne %%cl\n\t"
      "leal 0x104(%%esi), %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x100(%%esi), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x28(%%ebx), %%cx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c416e0]\n\t"
      "movb 0x133(%%esi), %%cl\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "movw %%ax, 0x38(%%esi)\n\t"
      "jne .Lprop_status_refresh_40\n\t"
      "movb -0x4(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lprop_status_refresh_40\n\t"
      "pushl $2\n\t"
      "pushl $0\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0x120(%%esi), %%dl\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c314f0]\n\t"
      "addl $0x20, %%esp\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw %%ax, 0x32(%%esi)\n\t"
      "movw %%cx, 0x34(%%esi)\n\t"
      "movw %%cx, 0x36(%%esi)\n\t"
      "movw %%ax, 0x30(%%esi)\n\t"
      "jmp .Lprop_status_refresh_95\n\t"
      ".Lprop_status_refresh_40:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw %%ax, 0x30(%%esi)\n\t"
      "movw %%ax, 0x36(%%esi)\n\t"
      "movw %%ax, 0x34(%%esi)\n\t"
      "movw %%ax, 0x32(%%esi)\n\t"
      "jmp .Lprop_status_refresh_95\n\t"
      ".Lprop_status_refresh_41:\n\t"
      "movb 0x12e(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb $0, -0x8(%%ebp)\n\t"
      "je .Lprop_status_refresh_42\n\t"
      "movb 0x60(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_42\n\t"
      "movl $2, %%eax\n\t"
      "jmp .Lprop_status_refresh_43\n\t"
      ".Lprop_status_refresh_42:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lprop_status_refresh_43:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl 0x158(%%ecx), %%edx\n\t"
      "movl 0x110(%%esi), %%ecx\n\t"
      "cmpl $-1, %%edx\n\t"
      "setne %%dl\n\t"
      "leal 0x104(%%esi), %%edi\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x100(%%esi), %%dx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x28(%%ebx), %%ax\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c416e0]\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "addl $0x20, %%esp\n\t"
      "movw %%ax, 0x38(%%esi)\n\t"
      "movb $2, 0x120(%%esi)\n\t"
      "cmpw $0, 0x64(%%ecx)\n\t"
      "movl %%ecx, %%edi\n\t"
      "jne .Lprop_status_refresh_44\n\t"
      "movl (%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x62697064\n\t"
      "call *%[tag]\n\t"
      "movl 0x2f4(%%eax), %%eax\n\t"
      "shrl $2, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "andb $1, %%al\n\t"
      "movb %%al, 0x130(%%esi)\n\t"
      "jmp .Lprop_status_refresh_45\n\t"
      ".Lprop_status_refresh_44:\n\t"
      "movb $0, 0x130(%%esi)\n\t"
      ".Lprop_status_refresh_45:\n\t"
      "flds 0x32c(%%edi)\n\t"
      "fcomps 0x253398\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lprop_status_refresh_46\n\t"
      "movl $1, %%eax\n\t"
      "jmp .Lprop_status_refresh_47\n\t"
      ".Lprop_status_refresh_46:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lprop_status_refresh_47:\n\t"
      "movb %%al, 0x131(%%esi)\n\t"
      "movl 0x1b4(%%edi), %%ecx\n\t"
      "shrl $0x13, %%ecx\n\t"
      "andb $1, %%cl\n\t"
      "movb %%cl, 0x132(%%esi)\n\t"
      "movb 0xb6(%%edi), %%al\n\t"
      "shrb $2, %%al\n\t"
      "andb $1, %%al\n\t"
      "je .Lprop_status_refresh_48\n\t"
      "cmpw $0, 0x3d0(%%edi)\n\t"
      "jne .Lprop_status_refresh_48\n\t"
      "movb $1, %%dl\n\t"
      "jmp .Lprop_status_refresh_49\n\t"
      ".Lprop_status_refresh_48:\n\t"
      "xorb %%dl, %%dl\n\t"
      ".Lprop_status_refresh_49:\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_50\n\t"
      "movb 0x127(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lprop_status_refresh_50\n\t"
      "movl $1, %%ecx\n\t"
      "jmp .Lprop_status_refresh_51\n\t"
      ".Lprop_status_refresh_50:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".Lprop_status_refresh_51:\n\t"
      "testb %%cl, %%cl\n\t"
      "movb %%cl, 0x129(%%esi)\n\t"
      "movb %%al, 0x127(%%esi)\n\t"
      "movb %%dl, 0x128(%%esi)\n\t"
      "je .Lprop_status_refresh_52\n\t"
      "movb 0x60(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lprop_status_refresh_52\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "cmpw $3, 0x6a(%%edx)\n\t"
      "jge .Lprop_status_refresh_52\n\t"
      "movb $1, -0x8(%%ebp)\n\t"
      ".Lprop_status_refresh_52:\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_53\n\t"
      "movw $0, 0x6a(%%esi)\n\t"
      ".Lprop_status_refresh_53:\n\t"
      "movl 0x1a8(%%edi), %%ebx\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .Lprop_status_refresh_54\n\t"
      "movb $1, %%al\n\t"
      "jmp .Lprop_status_refresh_55\n\t"
      ".Lprop_status_refresh_54:\n\t"
      "movl 0x1a4(%%edi), %%ebx\n\t"
      "xorb %%al, %%al\n\t"
      ".Lprop_status_refresh_55:\n\t"
      "cmpl 0x1c(%%esi), %%ebx\n\t"
      "je .Lprop_status_refresh_56\n\t"
      "movb %%al, 0x14(%%esi)\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%ebx, 0x1c(%%esi)\n\t"
      "je .Lprop_status_refresh_56\n\t"
      "pushl %%eax\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x1c(%%eax)\n\t"
      "movb 0x14(%%esi), %%dl\n\t"
      "addl $8, %%esp\n\t"
      "movb %%dl, 0x14(%%eax)\n\t"
      ".Lprop_status_refresh_56:\n\t"
      "cmpl $-1, %%ebx\n\t"
      "jne .Lprop_status_refresh_59\n\t"
      "movb 0x127(%%esi), %%al\n\t"
      "xorb %%bl, %%bl\n\t"
      "testb %%al, %%al\n\t"
      "movb $0, -0xc(%%ebp)\n\t"
      "sete %%al\n\t"
      ".Lprop_status_refresh_57:\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      ".Lprop_status_refresh_58:\n\t"
      "movb -0xc(%%ebp), %%cl\n\t"
      "movb %%al, 0x12d(%%esi)\n\t"
      "movb -0x8(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb %%cl, 0x12b(%%esi)\n\t"
      "movb %%bl, 0x12c(%%esi)\n\t"
      "je .Lprop_status_refresh_63\n\t"
      "movb -0x4(%%ebp), %%cl\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lprop_status_refresh_62\n\t"
      "movb 0x132(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_60\n\t"
      "movb $2, -0x10(%%ebp)\n\t"
      "jmp .Lprop_status_refresh_61\n\t"
      ".Lprop_status_refresh_59:\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c3b100]\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movb %%al, -0xc(%%ebp)\n\t"
      "call *%[c3b120]\n\t"
      "movl 0x1c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "movb %%al, %%bl\n\t"
      "call *%[c3b150]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lprop_status_refresh_57\n\t"
      "movb 0x12c(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lprop_status_refresh_57\n\t"
      "movb 0x60(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lprop_status_refresh_57\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      "cmpw $3, 0x6a(%%edi)\n\t"
      "jge .Lprop_status_refresh_58\n\t"
      "movb $1, -0x8(%%ebp)\n\t"
      "jmp .Lprop_status_refresh_58\n\t"
      ".Lprop_status_refresh_60:\n\t"
      "movb 0x120(%%esi), %%dl\n\t"
      "movb %%dl, -0x10(%%ebp)\n\t"
      ".Lprop_status_refresh_61:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c2f380]\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x38(%%esi), %%cx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "leal 0x104(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c314f0]\n\t"
      "addl $0x28, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "jge .Lprop_status_refresh_63\n\t"
      ".Lprop_status_refresh_62:\n\t"
      "movw %%ax, 0x30(%%esi)\n\t"
      "movw %%ax, 0x32(%%esi)\n\t"
      "movw $0, 0x24(%%esi)\n\t"
      ".Lprop_status_refresh_63:\n\t"
      "movb 0x133(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_64\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw %%ax, 0x30(%%esi)\n\t"
      "movw %%ax, 0x36(%%esi)\n\t"
      "movw %%ax, 0x34(%%esi)\n\t"
      "movw %%ax, 0x32(%%esi)\n\t"
      "jmp .Lprop_status_refresh_92\n\t"
      ".Lprop_status_refresh_64:\n\t"
      "movb -0x4(%%ebp), %%bl\n\t"
      "call *%[cfff80]\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lprop_status_refresh_65\n\t"
      "movb 0x5ac9cb, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lprop_status_refresh_66\n\t"
      ".Lprop_status_refresh_65:\n\t"
      "call *%[cfff80]\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lprop_status_refresh_67\n\t"
      "movb 0x5ac9c7, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_67\n\t"
      "movb 0x12e(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_67\n\t"
      ".Lprop_status_refresh_66:\n\t"
      "movb $1, %%bl\n\t"
      ".Lprop_status_refresh_67:\n\t"
      "movb 0x131(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_70\n\t"
      "movb 0x60(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lprop_status_refresh_71\n\t"
      "movb 0x12e(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_68\n\t"
      "flds 0x11c(%%esi)\n\t"
      "fcomps 0x2533d8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lprop_status_refresh_71\n\t"
      ".Lprop_status_refresh_68:\n\t"
      "cmpw $4, 0x15e(%%edi)\n\t"
      "movb $1, -0x10(%%ebp)\n\t"
      "je .Lprop_status_refresh_73\n\t"
      "cmpw $0xf, 0x4(%%edi)\n\t"
      "je .Lprop_status_refresh_73\n\t"
      "movb 0x60(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lprop_status_refresh_72\n\t"
      "cmpw $3, 0x6a(%%edi)\n\t"
      "movb $0, -0x10(%%ebp)\n\t"
      "jge .Lprop_status_refresh_74\n\t"
      "movb 0x127(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lprop_status_refresh_69\n\t"
      "movb 0x12c(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_74\n\t"
      ".Lprop_status_refresh_69:\n\t"
      "movb $1, -0x10(%%ebp)\n\t"
      "jmp .Lprop_status_refresh_74\n\t"
      ".Lprop_status_refresh_70:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lprop_status_refresh_68\n\t"
      ".Lprop_status_refresh_71:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movw $0, 0x32(%%esi)\n\t"
      "movb $0, 0x12a(%%esi)\n\t"
      "jmp .Lprop_status_refresh_79\n\t"
      ".Lprop_status_refresh_72:\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .Lprop_status_refresh_74\n\t"
      "cmpw $3, %%ax\n\t"
      "jg .Lprop_status_refresh_74\n\t"
      ".Lprop_status_refresh_73:\n\t"
      "movb $0, -0x10(%%ebp)\n\t"
      ".Lprop_status_refresh_74:\n\t"
      "movb 0x132(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_75\n\t"
      "movb $2, -0x24(%%ebp)\n\t"
      "jmp .Lprop_status_refresh_76\n\t"
      ".Lprop_status_refresh_75:\n\t"
      "movb 0x120(%%esi), %%cl\n\t"
      "movb %%cl, -0x24(%%ebp)\n\t"
      ".Lprop_status_refresh_76:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c2f380]\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x38(%%esi), %%dx\n\t"
      "leal 0x104(%%esi), %%edi\n\t"
      "pushl %%eax\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x12e(%%esi), %%al\n\t"
      "pushl %%eax\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c314f0]\n\t"
      "addl $0x28, %%esp\n\t"
      "cmpw $0, 0x32(%%esi)\n\t"
      "jne .Lprop_status_refresh_77\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lprop_status_refresh_77\n\t"
      "movl $1, %%ecx\n\t"
      "jmp .Lprop_status_refresh_78\n\t"
      ".Lprop_status_refresh_77:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".Lprop_status_refresh_78:\n\t"
      "testw %%ax, %%ax\n\t"
      "movb %%cl, 0x12a(%%esi)\n\t"
      "movw %%ax, 0x32(%%esi)\n\t"
      "je .Lprop_status_refresh_79\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "leal 0x90(%%esi), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl %%ecx, 0x8c(%%esi)\n\t"
      ".Lprop_status_refresh_79:\n\t"
      "call *%[cfff80]\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lprop_status_refresh_80\n\t"
      "movb 0x5ac9cc, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lprop_status_refresh_81\n\t"
      ".Lprop_status_refresh_80:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lprop_status_refresh_82\n\t"
      "movb 0x41(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lprop_status_refresh_82\n\t"
      ".Lprop_status_refresh_81:\n\t"
      "movw $0, 0x34(%%esi)\n\t"
      "jmp .Lprop_status_refresh_85\n\t"
      ".Lprop_status_refresh_82:\n\t"
      "movw 0x66(%%esi), %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "je .Lprop_status_refresh_84\n\t"
      "cmpw $2, %%ax\n\t"
      "je .Lprop_status_refresh_84\n\t"
      "movl 0x110(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lprop_status_refresh_83\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      ".Lprop_status_refresh_83:\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x38(%%esi), %%cx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x182(%%eax), %%dx\n\t"
      "leal 0xfc(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%edx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0xbc(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c31850]\n\t"
      "addl $0x2c, %%esp\n\t"
      "movw %%ax, 0x34(%%esi)\n\t"
      "jmp .Lprop_status_refresh_85\n\t"
      ".Lprop_status_refresh_84:\n\t"
      "movw $3, 0x34(%%esi)\n\t"
      ".Lprop_status_refresh_85:\n\t"
      "cmpw $0, 0x66(%%esi)\n\t"
      "movw $0, 0x36(%%esi)\n\t"
      "jne .Lprop_status_refresh_86\n\t"
      "movw $3, 0x36(%%esi)\n\t"
      ".Lprop_status_refresh_86:\n\t"
      "movb 0x132(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_89\n\t"
      "cmpb $2, 0x122(%%esi)\n\t"
      "jg .Lprop_status_refresh_89\n\t"
      "cmpb $2, 0x121(%%esi)\n\t"
      "jg .Lprop_status_refresh_89\n\t"
      "movw 0x38(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Lprop_status_refresh_87\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .Lprop_status_refresh_89\n\t"
      ".Lprop_status_refresh_87:\n\t"
      "movw 0x36(%%esi), %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "movswl %%ax, %%eax\n\t"
      "jg .Lprop_status_refresh_88\n\t"
      "movl $1, %%eax\n\t"
      ".Lprop_status_refresh_88:\n\t"
      "movw %%ax, 0x36(%%esi)\n\t"
      ".Lprop_status_refresh_89:\n\t"
      "movw 0x34(%%esi), %%cx\n\t"
      "movw 0x36(%%esi), %%dx\n\t"
      "cmpw %%dx, %%cx\n\t"
      "movswl %%cx, %%edi\n\t"
      "jg .Lprop_status_refresh_90\n\t"
      "movswl %%dx, %%edi\n\t"
      ".Lprop_status_refresh_90:\n\t"
      "movswl 0x32(%%esi), %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jg .Lprop_status_refresh_91\n\t"
      "cmpw %%dx, %%cx\n\t"
      "movswl %%cx, %%eax\n\t"
      "jg .Lprop_status_refresh_91\n\t"
      "movswl %%dx, %%eax\n\t"
      ".Lprop_status_refresh_91:\n\t"
      "cmpw $1, %%ax\n\t"
      "movw %%ax, 0x30(%%esi)\n\t"
      "jne .Lprop_status_refresh_92\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .Lprop_status_refresh_92\n\t"
      "cmpw $3, %%ax\n\t"
      "jg .Lprop_status_refresh_92\n\t"
      "movw $2, 0x30(%%esi)\n\t"
      ".Lprop_status_refresh_92:\n\t"
      "cmpw $0, 0x30(%%esi)\n\t"
      "je .Lprop_status_refresh_93\n\t"
      "leal 0xbc(%%esi), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0x80(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x7c(%%esi)\n\t"
      ".Lprop_status_refresh_93:\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .Lprop_status_refresh_95\n\t"
      "cmpw $3, %%ax\n\t"
      "jg .Lprop_status_refresh_95\n\t"
      "cmpw $2, 0x32(%%esi)\n\t"
      "jge .Lprop_status_refresh_94\n\t"
      "movb 0xb8(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_95\n\t"
      "movl 0xb4(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lprop_status_refresh_95\n\t"
      "movl 0x6325a4, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c119270]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lprop_status_refresh_95\n\t"
      "cmpw $0xa, 0x268(%%eax)\n\t"
      "jl .Lprop_status_refresh_95\n\t"
      "movl 0x270(%%eax), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lprop_status_refresh_95\n\t"
      "movb 0x454(%%eax), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .Lprop_status_refresh_95\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x18(%%eax), %%ecx\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jne .Lprop_status_refresh_95\n\t"
      ".Lprop_status_refresh_94:\n\t"
      "movb $1, 0xb8(%%esi)\n\t"
      "movw $0, 0xb0(%%esi)\n\t"
      ".Lprop_status_refresh_95:\n\t"
      "movb 0x136(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "je .Lprop_status_refresh_96\n\t"
      "cmpw $2, 0x30(%%esi)\n\t"
      "movl 0x110(%%esi), %%eax\n\t"
      "setge %%dl\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c32170]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lprop_status_refresh_96:\n\t"
      "flds 0x20(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lprop_status_refresh_98\n\t"
      "movb 0x127(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lprop_status_refresh_97\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "cmpb $0x1e, 0x253(%%ecx)\n\t"
      "jne .Lprop_status_refresh_98\n\t"
      ".Lprop_status_refresh_97:\n\t"
      "cmpw $2, 0x30(%%esi)\n\t"
      "movl 0x11c(%%esi), %%ecx\n\t"
      "movl 0x18(%%esi), %%edi\n\t"
      "setge %%dl\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x60(%%esi), %%al\n\t"
      "pushl %%edx\n\t"
      "movl 0x20(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c2f5f0]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lprop_status_refresh_98:\n\t"
      "movb 0x60(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "je .Lprop_status_refresh_101\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .Lprop_status_refresh_101\n\t"
      "cmpw $3, %%ax\n\t"
      "jg .Lprop_status_refresh_101\n\t"
      "pushl %%edi\n\t"
      "call *%[c3b320]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_99\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "flds 0x11c(%%esi)\n\t"
      "fcomps 0x608(%%eax)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lprop_status_refresh_100\n\t"
      ".Lprop_status_refresh_99:\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "testl $0x8000000, (%%eax)\n\t"
      "je .Lprop_status_refresh_101\n\t"
      "flds 0x11c(%%esi)\n\t"
      "fcomps 0x37c(%%eax)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lprop_status_refresh_101\n\t"
      ".Lprop_status_refresh_100:\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c32ac0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lprop_status_refresh_101:\n\t"
      "movl 0xa0(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lprop_status_refresh_102\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "addl $0x96, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .Lprop_status_refresh_102\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c32ac0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lprop_status_refresh_102:\n\t"
      "movb 0x126(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_119\n\t"
      "movl 0x20(%%esi), %%ecx\n\t"
      "flds 0x11c(%%esi)\n\t"
      "movw 0x76(%%esi), %%dx\n\t"
      "fld %%st(0)\n\t"
      "movb 0x127(%%esi), %%al\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "movb 0x12e(%%esi), %%bl\n\t"
      "movl 0x1c(%%esi), %%edi\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "movb 0x60(%%esi), %%cl\n\t"
      "movw %%dx, -0x18(%%ebp)\n\t"
      "movb 0x63(%%esi), %%dl\n\t"
      "movb %%cl, -0x8(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movb %%dl, -0xc(%%ebp)\n\t"
      "movl 0x6325a4, %%edx\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "movb %%al, -0x4(%%ebp)\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jne .Lprop_status_refresh_103\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lprop_status_refresh_104\n\t"
      ".Lprop_status_refresh_103:\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      ".Lprop_status_refresh_104:\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lprop_status_refresh_118\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lprop_status_refresh_105\n\t"
      "movb 0x8(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lprop_status_refresh_117\n\t"
      "movb 0x13(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lprop_status_refresh_117\n\t"
      ".Lprop_status_refresh_105:\n\t"
      "movb -0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lprop_status_refresh_118\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fcomps 0x255fe0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lprop_status_refresh_117\n\t"
      "movb -0x4(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_114\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl 0x34(%%ecx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movb $1, %%bl\n\t"
      "je .Lprop_status_refresh_111\n\t"
      "movl 0x5ab270, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl 0x58(%%edi), %%ecx\n\t"
      "movl 0x3a0(%%edx), %%edx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jg .Lprop_status_refresh_106\n\t"
      "movl %%edx, %%ecx\n\t"
      ".Lprop_status_refresh_106:\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lprop_status_refresh_108\n\t"
      "movl 0x3cc(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lprop_status_refresh_107\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .Lprop_status_refresh_108\n\t"
      ".Lprop_status_refresh_107:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".Lprop_status_refresh_108:\n\t"
      "movb 0x45(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lprop_status_refresh_109\n\t"
      "movb 0x44(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lprop_status_refresh_109\n\t"
      "movb 0x42(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lprop_status_refresh_109\n\t"
      "movb $1, %%al\n\t"
      "jmp .Lprop_status_refresh_110\n\t"
      ".Lprop_status_refresh_109:\n\t"
      "xorb %%al, %%al\n\t"
      ".Lprop_status_refresh_110:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lprop_status_refresh_117\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_111\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fcomps 0x255fdc\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lprop_status_refresh_118\n\t"
      "jmp .Lprop_status_refresh_117\n\t"
      ".Lprop_status_refresh_111:\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lprop_status_refresh_118\n\t"
      "movb -0x8(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_status_refresh_112\n\t"
      "cmpw $0x96, -0x18(%%ebp)\n\t"
      "jg .Lprop_status_refresh_117\n\t"
      ".Lprop_status_refresh_112:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d6d0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $1, %%ax\n\t"
      "jg .Lprop_status_refresh_117\n\t"
      "movb -0x8(%%ebp), %%al\n\t"
      "flds 0x254e74\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lprop_status_refresh_113\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "cmpw $3, 0x6a(%%ecx)\n\t"
      "jge .Lprop_status_refresh_113\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x254df8\n\t"
      ".Lprop_status_refresh_113:\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lprop_status_refresh_118\n\t"
      "jmp .Lprop_status_refresh_117\n\t"
      ".Lprop_status_refresh_114:\n\t"
      "movb -0x8(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lprop_status_refresh_118\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fcomps 0x255fdc\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lprop_status_refresh_115\n\t"
      "movb $1, %%al\n\t"
      "jmp .Lprop_status_refresh_116\n\t"
      ".Lprop_status_refresh_115:\n\t"
      "xorb %%al, %%al\n\t"
      ".Lprop_status_refresh_116:\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lprop_status_refresh_118\n\t"
      ".Lprop_status_refresh_117:\n\t"
      "movw $0, 0x6a(%%esi)\n\t"
      ".Lprop_status_refresh_118:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movb $0, 0x126(%%esi)\n\t"
      ".Lprop_status_refresh_119:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c2fc20]\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movb %%al, 0xa4(%%esi)\n\t"
      "call *%[c2fd10]\n\t"
      "fstps 0x50(%%esi)\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c278e0]\n\t"
      "fstps 0x54(%%esi)\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, 0x64(%%esi)\n\t"
      "popl %%esi\n\t"
      ".Lprop_status_refresh_120:\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b33440_dget), [tag] "m"(b33440_tag), [get] "m"(b33440_get), [gtime] "m"(b33440_gtime), [cfff80] "m"(b33440_cfff80), [c140070] "m"(b33440_c140070), [c27a60] "m"(b33440_c27a60), [c1a9900] "m"(b33440_c1a9900), [c416e0] "m"(b33440_c416e0), [c314f0] "m"(b33440_c314f0), [c3b100] "m"(b33440_c3b100), [c3b120] "m"(b33440_c3b120), [c3b150] "m"(b33440_c3b150), [c2f380] "m"(b33440_c2f380), [c31850] "m"(b33440_c31850), [c119270] "m"(b33440_c119270), [c32170] "m"(b33440_c32170), [c2f5f0] "m"(b33440_c2f5f0), [c3b320] "m"(b33440_c3b320), [c32ac0] "m"(b33440_c32ac0), [c1d6d0] "m"(b33440_c1d6d0), [c2fc20] "m"(b33440_c2fc20), [c2fd10] "m"(b33440_c2fd10), [c278e0] "m"(b33440_c278e0)
      : "memory");
}
#else
#error "prop_status_refresh: clang naked draft required"
#endif


/* 0x342a0 — evaluate a test object for perception refresh (weapons/attachments). */
void actor_perception_refresh_test_object(int actor_handle, int unit_handle,
                                          void *primary_list, void *secondary_list)
{
  char *actor;
  char *unit;
  char *owner_actor;
  char *encounter;
  char *unit_def;
  char *proj_def;
  char sense_block[0x74];
  char sense_block2[0xac];
  float unit_pos[3];
  float sense_origin[3];
  float dist_sq;
  float sqrt_dist;
  float weapon_range;
  float time_delta;
  int owner_handle;
  int swarm_unit;
  int prop_handle;
  int child_unit;
  int weapon_object;
  int16_t list_count;
  char friendly;
  char in_fov;
  char has_weapon;
  char should_add;
  char hidden_enc;
  char desire_ok;
  char list_slot;

  if (unit_handle == -1)
    return;

  actor = (char *)datum_get(actor_data, actor_handle);

  for (;;) {
    unit = (char *)object_get_and_verify_type(unit_handle, -1);
    if (!object_mark(unit_handle))
      goto next_attachment;

    if (*(int16_t *)(unit + 0x64) != 0) {
      if (primary_list != 0)
        *(int16_t *)primary_list = (int16_t)(*(int16_t *)primary_list + 1);
      goto next_attachment;
    }

    object_get_world_position(unit_handle, (vector3_t *)unit_pos);
    actor_perception_find_sense_position(actor_handle, unit_pos, -1, sense_block);

    owner_handle = *(int *)(unit + 0x1a8);
    if (owner_handle == -1)
      owner_handle = *(int *)(unit + 0x1a4);
    swarm_unit = unit_handle;
    if (owner_handle != -1) {
      swarm_unit = actor_perception_unit_from_swarm(
          actor_handle, unit_handle, 1, (float *)(actor + 0x120));
      if (swarm_unit == -1)
        goto next_attachment;
      unit = (char *)object_get_and_verify_type(swarm_unit, 3);
      object_get_world_position(swarm_unit, (vector3_t *)unit_pos);
    }

    if (swarm_unit == -1 || owner_handle == actor_handle)
      goto next_attachment;

    unit_def = (char *)tag_get('unit', *(int *)unit);
    has_weapon = (char)(*(int *)(unit + 0x1c8) != -1);
    friendly = game_allegiance_get_team_is_friendly(*(int16_t *)(unit + 0x68),
                                                    *(int16_t *)(actor + 0x3e));

    in_fov = 0;
    if ((*(uint8_t *)(unit + 0xb6) & 4) != 0 &&
        *(int16_t *)(unit + 0x3d0) == 0) {
      if (*(int *)(unit + 0x3cc) != -1) {
        in_fov = 1;
        time_delta = (float)(game_time_get() - *(int *)(unit + 0x3cc));
      } else {
        time_delta = 32767.0f;
      }
    } else {
      time_delta = 0.0f;
    }

    weapon_range = *(float *)(unit_def + 0x284);
    sense_origin[0] = *(float *)(sense_block + 0xc);
    sense_origin[1] = *(float *)(sense_block + 0x10);
    sense_origin[2] = *(float *)(sense_block + 0x14);
    {
      float dx = unit_pos[0] - sense_origin[0];
      float dy = unit_pos[1] - sense_origin[1];
      float dz = unit_pos[2] - sense_origin[2];
      dist_sq = dx * dx + dy * dy + dz * dz;
    }

    if (weapon_range > *(float *)0x2533c0) {
      if (in_fov != 0 || *(char *)((char *)unit + 0x253) == 0x1e) {
        sqrt_dist = sqrtf(dist_sq);
        FUN_0002f5f0(actor_handle, weapon_range, sqrt_dist, swarm_unit,
                     friendly, 0);
      }
    }

    owner_actor = 0;
    if (owner_handle != -1)
      owner_actor = (char *)datum_get(actor_data, owner_handle);

    should_add = 0;
    list_slot = 0;

    if (!has_weapon) {
      if (owner_actor == 0 || *(char *)(owner_actor + 8) == 0 ||
          *(char *)(owner_actor + 0x13) != 0)
        goto skip_desire;
      if (dist_sq <= *(float *)0x255fe0)
        goto skip_desire;
    } else if (friendly != 0) {
      goto skip_desire;
    } else if (dist_sq <= *(float *)0x255fe0) {
      goto skip_desire;
    }

    if (in_fov != 0) {
      char max_teams;
      char actor_teams;
      char unit_teams;
      desire_ok = 1;

      if (*(int *)(actor + 0x34) != -1) {
        encounter = (char *)datum_get(*(void **)0x5ab270, *(int *)(actor + 0x34));
        max_teams = *(char *)(encounter + 0x58);
        actor_teams = *(char *)(actor + 0x3a0);
        unit_teams = *(char *)(unit + 0x3cc);
        if (max_teams < actor_teams)
          max_teams = actor_teams;
        if (max_teams != -1 && unit_teams != -1 && unit_teams < max_teams)
          desire_ok = 0;

        hidden_enc = (char)(*(char *)(encounter + 0x45) == 0 &&
                            *(char *)(encounter + 0x44) == 0 &&
                            *(char *)(encounter + 0x42) == 0);
        if (desire_ok != 0 && hidden_enc != 0) {
          if (dist_sq > *(float *)0x255fdc * *(float *)0x255fdc)
            goto skip_desire;
        } else if (desire_ok != 0 && dist_sq > *(float *)0x2533c0 * *(float *)0x2533c0) {
          goto skip_desire;
        }
      }

      if (desire_ok != 0 && actor_action_try_to_panic(actor_handle) > 1)
        goto skip_desire;

      if (desire_ok != 0) {
        float threshold = *(float *)0x254e74;
        if (*(int16_t *)(actor + 0x6a) < 3)
          threshold = *(float *)0x254df8;
        if (dist_sq > threshold * threshold)
          goto skip_desire;
      }
    } else if (dist_sq > *(float *)0x255fdc * *(float *)0x255fdc) {
      goto skip_desire;
    } else if (friendly != 0) {
      if (dist_sq > *(float *)0x255fd8 * *(float *)0x255fd8)
        should_add = 1;
      else
        should_add = 0;
      if (*(int16_t *)(actor + 0x6e) >= 4)
        should_add = 1;
      else if (*(char *)(actor + 0x1cc) == 0) {
        should_add = 1;
        if (dist_sq > *(float *)0x254e74 * *(float *)0x254e74)
          should_add = 0;
      } else {
        should_add = 0;
      }
      if (should_add == 0)
        goto skip_desire;
      list_slot = 1;
    }

    if (in_fov != 0) {
      void *target_list = friendly ? secondary_list : primary_list;

      if (target_list != 0) {
        list_count = *(int16_t *)((char *)target_list + 2);
        if (list_count < 0x80) {
          int idx = list_count;
          int base = idx + idx * 2;

          *(int *)((char *)target_list + base * 4 + 8) = -1;
          *(int *)((char *)target_list + base * 4 + 4) = swarm_unit;
          *(float *)((char *)target_list + base * 4) = dist_sq;
          *(int16_t *)((char *)target_list + 2) = list_count + 1;
        }
      }
      goto next_attachment;
    }

    if (should_add != 0) {
      void *target_list = list_slot ? secondary_list : primary_list;

      if (target_list != 0) {
        list_count = *(int16_t *)((char *)target_list + 2);
        if (list_count < 0x80) {
          int idx = list_count;
          int base = idx + idx * 2;

          *(int *)((char *)target_list + base * 4 + 8) = -1;
          *(int *)((char *)target_list + base * 4 + 4) = swarm_unit;
          *(float *)((char *)target_list + base * 4) = dist_sq;
          *(int16_t *)((char *)target_list + 2) = list_count + 1;
        }
      }
      goto next_attachment;
    }

    if (!has_weapon) {
      prop_handle =
          prop_new_unacknowledged(actor_handle, swarm_unit, friendly);
      if (prop_handle == -1)
        goto next_attachment;
      prop_position_refresh(actor_handle, prop_handle, (float *)sense_block2, 0,
                            0);
      if (in_fov != 0)
        goto next_attachment;
      if (primary_list != 0)
        *(int16_t *)primary_list = (int16_t)(*(int16_t *)primary_list + 1);
    }

    if (*(int *)(unit + 0x2d4) == -1)
      FUN_00032170(0, actor_handle, swarm_unit, 0);

    if (*(int16_t *)(actor + 0x280) == 5) {
      proj_def = (char *)tag_get('jorp', *(int *)unit);
      if (*(int *)(unit + 0xcc) == -1 ||
          (*(uint8_t *)(unit + 0x1dc) & 0x20) != 0) {
        object_get_world_position(unit_handle, (vector3_t *)unit_pos);
        actor_perception_find_sense_position(actor_handle, unit_pos, -1,
                                             sense_block2);
        {
          float dx = unit_pos[0] - *(float *)(sense_block2 + 0xc);
          float dy = unit_pos[1] - *(float *)(sense_block2 + 0x10);
          float dz = unit_pos[2] - *(float *)(sense_block2 + 0x14);
          sqrt_dist = sqrtf(dx * dx + dy * dy + dz * dz);
        }

        if (*(float *)(proj_def + 0x1a8) + *(float *)0x253f34 > sqrt_dist) {
          if (*(int16_t *)(actor + 0x280) < 2 ||
              (*(int16_t *)(actor + 0x280) == 2 &&
               *(int *)(actor + 0x28c) != unit_handle &&
               sqrt_dist > *(float *)(actor + 0x2d4))) {
            csmemset(actor + 0x280, 0, 0x6c);
            *(int16_t *)(actor + 0x280) = 2;
            *(int *)(actor + 0x28c) = unit_handle;
            *(float *)(actor + 0x294) = *(float *)(proj_def + 0x1a8);
            *(float *)(actor + 0x298) = unit_pos[0];
            *(float *)(actor + 0x29c) = unit_pos[1];
            *(float *)(actor + 0x2a0) = unit_pos[2];
            *(int *)(actor + 0x2a4) = *(int *)(unit + 0x18);
            *(int *)(actor + 0x2a8) = *(int *)(unit + 0x1c);
            *(int *)(actor + 0x2ac) = *(int *)(unit + 0x20);
            *(int16_t *)(actor + 0x284) = 0x1e;
            *(char *)(actor + 0x286) = 0;
            *(int16_t *)(actor + 0x282) = 0;

            weapon_object = *(int *)(unit + 0x74);
            if (weapon_object != -1) {
              char *weapon_type = (char *)object_try_and_get_and_verify_type(
                  weapon_object, -1);
              if (weapon_type != 0) {
                char type_mask =
                    (char)(1 << *(uint8_t *)(weapon_type + 0x64));
                if ((type_mask & 3) != 0) {
                  if (*(int *)(actor + 0x18) != -1 &&
                      weapon_object == *(int *)(actor + 0x18))
                    *(int16_t *)(actor + 0x282) = 2;
                  else if (!game_allegiance_get_team_is_friendly(
                               *(int16_t *)(unit + 0x68),
                               *(int16_t *)(actor + 0x3e)))
                    *(int16_t *)(actor + 0x282) = 1;
                }
              }
            }
            *(int *)(actor + 0x290) = *(int *)(unit + 0x74);
          }
        }
      }
    }

skip_desire:
    (void)owner_actor;
    (void)encounter;
    (void)time_delta;
    (void)hidden_enc;
    (void)desire_ok;
    (void)list_slot;

next_attachment:
    weapon_object = *(int *)(unit + 0xc8);
    if (weapon_object != -1) {
      actor_perception_refresh_test_object(actor_handle, weapon_object,
                                           secondary_list, primary_list);
    }
    child_unit = *(int *)(unit + 0xc4);
    if (child_unit == -1)
      break;
    unit_handle = child_unit;
  }
}

/* 0x34970 — create an orphan prop acknowledgement from a friend's prop. */
char actor_perception_create_orphan_from_friend(int actor_handle, int unit_handle,
                                                int encounter_team,
                                                int friend_prop)
{
  char *prop;
  char *parent;
  char *orphan;
  char local_44[0x44];
  char refresh_parent;
  char success;
  int prop_handle;
  int final_prop;
  int parent_prop;
  int orphan_prop;
  int16_t status;

  success = 1;
  prop_handle = FUN_00064b40(actor_handle, unit_handle, 1, 0);
  if (prop_handle == -1)
    return success;

  final_prop = prop_handle;

  prop = (char *)datum_get(prop_data, prop_handle);
  status = *(int16_t *)(prop + 0x24);
  if (status >= 2 && status <= 3) {
    success = 0;
    goto finish;
  }

  parent_prop = *(int *)(prop + 0xc);
  if (parent_prop == -1) {
    status = *(int16_t *)(prop + 0x24);
    if (status < 0) {
      display_assert("prop->type >= 0",
                     "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0xedf, 1);
      system_exit(-1);
    }
    if (status > 1) {
      display_assert("prop->type <= 1",
                     "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0xedf, 1);
      system_exit(-1);
    }

    if (friend_prop != -1) {
      orphan_prop =
          prop_orphan_from_friend(actor_handle, prop_handle, friend_prop);
      if (orphan_prop == -1)
        return 0;
      orphan = (char *)datum_get(prop_data, orphan_prop);
      *(int *)(orphan + 0x18) = *(int *)(prop + 0x18);
      *(int *)(orphan + 0x1c) = *(int *)(prop + 0x1c);
      *(char *)(orphan + 0x14) = *(char *)(prop + 0x14);
    } else {
      prop_position_refresh(actor_handle, prop_handle, (float *)local_44, 0, 0);
      orphan_prop = prop_orphan_transition(actor_handle, prop_handle);
      if (orphan_prop == -1)
        return 0;
    }
    prop = (char *)datum_get(prop_data, orphan_prop);
    final_prop = orphan_prop;
    goto finish;
  }

  parent = (char *)datum_get(prop_data, parent_prop);
  if (status < 0 || status > 1) {
    display_assert("prop->type <= 1",
                   "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0xeb4, 1);
    system_exit(-1);
  }

  status = *(int16_t *)(parent + 0x24);
  if (status >= 4 && status <= 5) {
    display_assert("parent->type < 4 || parent->type > 5",
                   "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0xeb5, 1);
    system_exit(-1);
  }
  if (*(int *)(prop + 4) != actor_handle) {
    display_assert("prop->actor_index == actor_index",
                   "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0xeb6, 1);
    system_exit(-1);
  }
  if (*(int *)(parent + 4) != actor_handle) {
    display_assert("parent->actor_index == actor_index",
                   "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0xeb7, 1);
    system_exit(-1);
  }
  if (*(int *)(prop + 0xc) != parent_prop) {
    display_assert("prop->parent_prop_index == parent_prop_index",
                   "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0xeb8, 1);
    system_exit(-1);
  }
  if (*(int *)(parent + 0xc) != prop_handle) {
    display_assert("parent->parent_prop_index == prop_index",
                   "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0xeb9, 1);
    system_exit(-1);
  }

  refresh_parent = 0;
  if (friend_prop != -1) {
    prop_orphan_update_information(actor_handle, parent_prop, friend_prop);
    *(int *)(prop + 0x18) = *(int *)(parent + 0x18);
  } else {
    *(int16_t *)(parent + 0x24) = 4;
    *(int16_t *)(parent + 0x3c) = 0;
    refresh_parent = 1;
  }

  prop_position_refresh(actor_handle, parent_prop, (float *)local_44, 1,
                        refresh_parent);
  prop_status_refresh(actor_handle, parent_prop, (float *)local_44);
  prop = (char *)datum_get(prop_data, parent_prop);
  final_prop = parent_prop;

finish:
  if (prop != 0) {
    if (encounter_team != -1) {
      if (friend_prop != -1) {
        char *enc =
            (char *)datum_get(*(void **)0x5ab270, friend_prop);
        if (*(int16_t *)(enc + 0x32) >= 2) {
          *(char *)(prop + 0xb8) = 1;
          *(int16_t *)(prop + 0xb0) = 0;
          *(int *)(prop + 0xb4) = encounter_team;
        }
      } else {
        *(char *)(prop + 0xb8) = 1;
        *(int16_t *)(prop + 0xb0) = 0;
        *(int *)(prop + 0xb4) = encounter_team;
      }
    }
    *(char *)(prop + 0xa4) =
        (char)actor_get_perception_knowledge(actor_handle, final_prop);
    *(float *)(prop + 0x50) =
        actor_compute_prop_target_weight(actor_handle, final_prop);
  }
  return success;
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
  int local_28 = 0;
  int local_2c = 0;

  scenario_get();
  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), 0);
  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a0), 0);
  csmemset((void *)0, 0, 64);
  /* relift: cmp word ptr [esi + 2], (int16_t)edi -> jle 0x34d8b */
  object_get_and_verify_type(0, 3);
  /* cmp (int16_t)eax, 0xffff -> je 0x34d58 */
  structure_bsp_get_cluster_sound_data((void *)(uintptr_t)eax, eax);
  bit_vector_or(0, eax, 0, 0);
  /* relift: cmp (int16_t)edi, word ptr [esi + 2] -> jl 0x34d10 */
  /* test (char)eax, (char)eax -> je 0x34d8b */
  /* cmp (int16_t)eax, 0xffff -> je 0x34d8b */
  structure_bsp_get_cluster_sound_data((void *)(uintptr_t)eax, eax);
  object_reset_markers();
  FUN_00064540((void *)0, 0);
  FUN_00064570((void *)0);
  /* test esi, esi -> je 0x35245 */
  /* cmp (int16_t)eax, 4 -> jl 0x34dc7 */
  /* cmp (int16_t)eax, 5 -> jle 0x3522f */
  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), 0);
  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), 0);
  /* test eax, eax -> je 0x34e67 */
  /* test (char)ecx, (char)ecx -> je 0x34e60 */
  /* test (char)ecx, (char)ecx -> je 0x34e67 */
  /* test (char)eax, (char)eax -> jne 0x34e75 */
  /* relift: cmp word ptr [ebp - 0x3c], 0 -> jle 0x34e7c */
  /* relift: relift: fcomp dword ptr [0x255fe0] */
  /* test (char)eax, 0x41 -> jne 0x34e93 */
  /* test (char)eax, (char)eax -> je 0x34fa6 */
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab270), 0);
  object_get_and_verify_type(local_2c, 3);
  /* cmp ecx, edx -> jg 0x34ede */
  /* cmp ecx, -1 -> je 0x34ef4 */
  /* cmp eax, -1 -> je 0x34ef2 */
  /* cmp eax, ecx -> jge 0x34ef4 */
  /* test (char)eax, (char)eax -> jne 0x34f0d */
  /* test (char)eax, (char)eax -> jne 0x34f0d */
  /* test (char)eax, (char)eax -> jne 0x34f0d */
  /* test (char)ebx, (char)ebx -> je 0x34fff */
  /* test (char)eax, (char)eax -> je 0x34f32 */
  /* relift: relift: fcomp dword ptr [0x255fdc] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x34f49 */
  /* test (char)ebx, (char)ebx -> je 0x34f5f */
  /* relift: cmp word ptr [ebp - 0x30], 0x96 -> jle 0x34f5f */
  actor_action_try_to_panic(0);
  /* cmp (int16_t)eax, 1 -> jle 0x34f78 */
  /* relift: relift: fld dword ptr [0x254e74] */
  /* relift: cmp word ptr [ecx + 0x6a], 3 -> jge 0x34f94 */
  /* relift: relift: fld dword ptr [0x254df8] */
  /* test (char)eax, (char)eax -> je 0x34fba */
  /* relift: relift: fcomp dword ptr [0x255fd8] */
  /* relift: relift: fcomp dword ptr [0x255fdc] */
  /* relift: cmp word ptr [eax + 0x6e], 4 -> jl 0x34fdd */
  /* test (char)ecx, (char)ecx -> jne 0x34ffb */
  /* relift: relift: fcomp dword ptr [0x254e74] */
  /* test (char)eax, 0x41 -> je 0x34fff */
  /* test edi, edi -> je 0x3505a */
  object_get_first_cluster((void *)0, 0);
  /* cmp (int16_t)eax, 0xffff -> je 0x3505a */
  /* relift: test dword ptr [edi + eax*4], edx -> jne 0x35056 */
  FUN_0013d5f0((void *)0, 0);
  /* cmp (int16_t)eax, 0xffff -> jne 0x35027 */
  /* test (char)eax, (char)eax -> je 0x350e2 */
  /* cmp eax, -1 -> je 0x350e2 */
  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), 0);
  /* cmp eax, -1 -> je 0x350b9 */
  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a0), 0);
  /* relift: cmp word ptr [ebx + 2], (int16_t)edi -> jle 0x350e2 */
  object_mark(0);
  /* relift: cmp (int16_t)edi, word ptr [ebx + 2] -> jl 0x350a0 */
  /* cmp edi, -1 -> je 0x350e2 */
  object_get_and_verify_type(0, 3);
  object_mark(0);
  /* cmp edi, -1 -> jne 0x350c4 */
  object_mark(0);
  /* test (char)eax, (char)eax -> je 0x351e0 */
  /* test (char)eax, (char)eax -> je 0x35141 */
  display_assert((char *)0x002564c4, (char *)0x00255fb0, 2669, 1);
  system_exit(-1);
  /* cmp (int16_t)eax, 0x80 -> jge 0x35183 */
  /* relift: cmp dword ptr [0x2c8520], -1 -> je 0x351a5 */
  game_time_get();
  /* cmp eax, ecx -> jle 0x3522f */
  error(2, (char *)0x00256474);
  game_time_get();
  /* mem[0x002c8520] = eax */
  /* test (char)eax, (char)eax -> jne 0x3522f */
  /* cmp (int16_t)eax, 4 -> jl 0x351f0 */
  /* cmp (int16_t)eax, 5 -> jle 0x35213 */
  FUN_0003b410(0, 0, -1);
  prop_iterator_next(0, 0);
  FUN_0003b410(0, local_28, -1);
  prop_iterator_next(0, local_28);
  FUN_00064570((void *)0);
  /* test esi, esi -> jne 0x34db3 */
  /* test ebx, ebx -> je 0x3531d */
  /* test ecx, ecx -> jle 0x3531d */
  /* relift: test dword ptr [ebx + eax*4], edx -> je 0x35306 */
  cluster_partition_object_iter_first((void *)0, 0);
  /* cmp eax, -1 -> je 0x352c6 */
  /* relift: actor_perception_refresh_test_object(actor_handle, unit_handle, primary_list, secondary_list); */
  cluster_partition_object_iter_next((void *)0);
  /* cmp eax, -1 -> jne 0x352a0 */
  cluster_get_first_noncollideable_object((void *)0, 0);
  /* cmp eax, -1 -> je 0x35306 */
  /* relift: actor_perception_refresh_test_object(actor_handle, unit_handle, primary_list, secondary_list); */
  cluster_get_next_noncollideable_object((void *)0);
  /* cmp eax, -1 -> jne 0x352e0 */
  /* cmp eax, edx -> jl 0x35270 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x3546f */
  qsort((void *)0, 0, 12, (void *)0);
  /* relift: cmp word ptr [ebp - 0x6be], (int16_t)edi -> jle 0x3546f */
  /* relift: cmp dword ptr [ebp + eax - 0x6b8], ebx -> jne 0x353ae */
  prop_new_unacknowledged(0, 0, 0);
  /* cmp eax, ebx -> je 0x353c4 */
  prop_position_refresh(0, 0, 0, 0, 0);
  /* relift: cmp (int16_t)edi, word ptr [ebp - 0x6be] -> jl 0x35370 */
  /* cmp (int16_t)edi, (int16_t)eax -> jge 0x3546f */
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), 0);
  /* cmp (int16_t)eax, 4 -> jl 0x3542a */
  /* cmp (int16_t)eax, 5 -> jle 0x35448 */
  /* cmp eax, -1 -> je 0x35448 */
  FUN_0003b410(0, 0, -1);
  prop_iterator_next(0, 0);
  FUN_0003b410(0, 0, -1);
  prop_iterator_next(0, 0);
  /* test (int16_t)ecx, (int16_t)ecx -> jle 0x355e0 */
  qsort((void *)0, 0, 12, (void *)0);
  /* relift: cmp word ptr [ebp - 0xcc2], 0 -> jle 0x355e0 */
  /* relift: cmp dword ptr [ebp + eax - 0xcbc], -1 -> jne 0x35517 */
  prop_new_unacknowledged(0, 0, 0);
  /* cmp eax, -1 -> je 0x35525 */
  prop_position_refresh(0, 0, 0, 0, 0);
  /* relift: cmp (int16_t)ebx, word ptr [ebp - 0x1c] -> jge 0x3553e */
  /* relift: cmp (int16_t)edi, word ptr [ebp - 0xcc2] -> jl 0x354d7 */
  object_marker_end();
  /* cmp (int16_t)edi, (int16_t)ecx -> jge 0x355e0 */
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), 0);
  /* cmp (int16_t)eax, 4 -> jl 0x3559b */
  /* cmp (int16_t)eax, 5 -> jle 0x355b9 */
  /* cmp eax, -1 -> je 0x355b9 */
  FUN_0003b410(0, 0, -1);
  prop_iterator_next(0, 0);
  FUN_0003b410(0, 0, -1);
  prop_iterator_next(0, 0);
  object_marker_end();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
  (void)local_28;
  (void)local_2c;
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

  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), actor_handle);
  tag_get('rtca', 0);
  /* test (char)eax, (char)eax -> je 0x3565a */
  actor_perception_refresh();
  actor_perception_refresh_danger_zone(actor_handle);
  /* test (int16_t)edx, (int16_t)edx -> jle 0x3582a */
  /* test (char)eax, (char)eax -> jne 0x356d2 */
  /* relift: cmp word ptr [esi + 0x282], 0 -> jne 0x356d2 */
  /* test (int16_t)ecx, (int16_t)ecx -> jle 0x357e0 */
  /* test (char)eax, (char)eax -> je 0x357e0 */
  /* cmp eax, -1 -> je 0x356b5 */
  /* cmp eax, 0x3c -> jl 0x356c7 */
  /* test (char)eax, (char)eax -> je 0x357e0 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x3573e */
  get_global_random_seed_address();
  random_math_real((unsigned int *)(uintptr_t)*(int *)((char *)eax + 0x50));
  /* test (char)eax, (char)eax -> je 0x357e0 */
  /* test (char)eax, (char)eax -> je 0x3575f */
  /* relift: cmp word ptr [esi + 0x282], 0 -> jne 0x357ae */
  /* cmp (int16_t)eax, 3 -> je 0x357ae */
  /* cmp (int16_t)eax, 1 -> je 0x357ae */
  get_global_random_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  FUN_000378e0(actor_handle, 0, 0, 0, (float *)((char *)eax + 0x2b0));
  /* relift: cmp word ptr [esi + 0x284], 0 -> jne 0x3582a */
  /* relift: cmp word ptr [esi + 0x544], 0xc -> jne 0x35812 */
  /* cmp (int16_t)eax, 5 -> jle 0x35808 */
  /* test (char)eax, (char)eax -> je 0x3582a */
  FUN_00064540((void *)0, actor_handle);
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
  display_assert((char *)0x00256708, (char *)0x00255fb0, 316, 1);
  system_exit(eax);
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
