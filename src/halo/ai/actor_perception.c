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

/* 0x2f5f0 */
void FUN_0002f5f0(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), eax);
  /* test (char)eax, 0x41 -> jne 0x2f6d3 */
  /* relift: cmp dword ptr [esi + 0x28c], edi -> je 0x2f6d3 */
  object_get_and_verify_type(edi, 3);
  csmemset((void *)((char *)eax + 0x280), 0, 108);
  object_get_world_position(edi, (vector3_t *)((char *)eax + 0x298));

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x2f6e0 — decide whether an actor wants a prop acknowledgement. */
char actor_perception_desire_prop(
    int actor_handle, int existing_prop, int unit_handle, int owner_handle,
    char field_63, char field_12e, char friendly, char field_127,
    int16_t field_76, int16_t scale, float visibility, int sense,
    char *out_flag)
{
  char *actor;
  char *owner;
  char *unit;
  char *encounter;
  char desire;
  char out_desire;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (owner_handle == -1)
    owner = 0;
  else
    owner = (char *)datum_get(actor_data, owner_handle);

  desire = field_127;
  out_desire = 0;

  if (field_127 != 0 && friendly == 0)
    goto finish;
  if ((int16_t)existing_prop >= 4 && (int16_t)existing_prop <= 5) {
    desire = 0;
    goto finish;
  }
  if (field_63 != 0) {
    desire = 1;
    goto finish;
  }
  if (owner != 0 && *(char *)(owner + 8) != 0 && *(char *)(owner + 0x13) == 0) {
    desire = 0;
    goto finish;
  }
  if ((int16_t)existing_prop == -1) {
    if (field_12e != 0 || scale > 0) {
      desire = 1;
      goto finish;
    }
  }
  if (visibility < *(float *)0x255fe0) {
    desire = 0;
    goto finish;
  }

  if (desire != 0) {
    encounter = 0;
    if (*(int *)(actor + 0x34) != -1) {
      encounter =
          (char *)datum_get(*(void **)0x5ab270, *(int *)(actor + 0x34));
      unit = (char *)object_get_and_verify_type(unit_handle, 3);
      {
        int max_teams = *(int *)(encounter + 0x58);
        int actor_teams = *(int *)(actor + 0x3a0);
        int unit_teams = *(int *)(unit + 0x3cc);
        if (max_teams < actor_teams)
          max_teams = actor_teams;
        if (max_teams != -1 && unit_teams != -1 && unit_teams < max_teams)
          desire = 0;
      }
      if (desire != 0) {
        char hidden = 0;
        if (*(char *)(encounter + 0x45) != 0 ||
            *(char *)(encounter + 0x44) != 0 || *(char *)(encounter + 0x42) != 0)
          hidden = 0;
        else
          hidden = 1;
        if (hidden != 0) {
          if (visibility <= *(float *)0x255fdc) {
            desire = 1;
            goto finish;
          }
        } else if (field_127 != 0) {
          if (visibility <= *(float *)0x2533c0) {
            desire = 1;
            goto finish;
          }
          if (field_127 != 0 && field_76 > 0x96) {
            desire = 0;
            goto finish;
          }
        }
      }
    }
    if (actor_action_try_to_panic(actor_handle) > 1) {
      desire = 0;
      goto finish;
    }
    if (field_127 != 0) {
      float threshold = *(float *)0x254e74;
      if (*(int16_t *)(actor + 0x6a) < 3)
        threshold = *(float *)0x254df8;
      if (visibility > threshold) {
        desire = 0;
        goto finish;
      }
    }
    desire = 1;
    goto finish;
  }

  if (field_127 != 0) {
    if (visibility > *(float *)0x255fd8) {
      desire = 1;
      out_desire = 1;
    } else if (visibility <= *(float *)0x255fdc) {
      desire = 1;
      out_desire = 0;
    } else {
      desire = 0;
    }
    goto finish;
  }

  if (*(int16_t *)(actor + 0x6e) >= 4) {
    out_desire = 1;
    goto finish;
  }
  if (*(char *)(actor + 0x1cc) != 0) {
    out_desire = 0;
    goto finish;
  }
  if (visibility > *(float *)0x254e74)
    out_desire = 1;
  else
    out_desire = 0;

finish:
  if (out_flag != 0)
    *out_flag = out_desire;
  return desire;
}

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

/* 0x314f0 */
void actor_visibility_at_point(void)
{
  int eax = 0;
  int ecx = 0;
  int ebp = 0;

  /* cmp (int16_t)ecx, 1 -> jne 0x31836 */
  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), 0);
  tag_get('rtca', 0);
  actor_combat_get_firing_variant_definition(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x3155c */
  /* relift: relift: fld dword ptr [0x253524] */
  /* relift: relift: fld dword ptr [0x253f3c] */
  /* relift: relift: fld dword ptr [0x2533f0] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  display_assert((char *)0x00255ee8, (char *)0x00255fb0, 1268, 1);
  system_exit(-1);
  FUN_0018e690();
  /* relift: relift: fcomp dword ptr [0x2533f0] */
  /* test (char)eax, 0x41 -> je 0x31681 */
  /* relift: relift: fcomp dword ptr [0x2549d4] */
  /* test (char)eax, 0x41 -> jne 0x31671 */
  /* relift: relift: fld dword ptr [0x2533f0] */
  /* relift: relift: fcomp dword ptr [0x256140] */
  /* test (char)eax, 0x41 -> je 0x31688 */
  /* test (char)eax, (char)eax -> je 0x316c2 */
  game_time_get();
  /* test (char)eax, (char)eax -> jne 0x317c8 */
  /* test (char)eax, (char)eax -> je 0x317c8 */
  /* test (char)eax, 0x41 -> je 0x317b7 */
  /* relift: relift: fcomp dword ptr [0x256138] */
  actor_get_vision_distances();
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x2533c4] */
  /* relift: cmp word ptr [ebp + 0x18], 0 -> jne 0x31814 */
  /* test (char)eax, 0x41 -> jne 0x31814 */
  /* relift: relift: fcomp dword ptr [0x255fd8] */

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

  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), actor_handle);
  tag_get('rtca', 0);
  /* relift: cmp word ptr [edi + 0x28], -1 -> je 0x31a80 */
  /* relift: cmp word ptr [edx + 4], -1 -> je 0x31a80 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* cmp (int16_t)ebx, 2 -> jne 0x31921 */
  /* cmp (int16_t)ebx, 1 -> jne 0x31933 */
  /* cmp (int16_t)eax, 4 -> jne 0x31948 */
  /* cmp (int16_t)eax, 1 -> jne 0x31959 */
  /* cmp (int16_t)eax, 3 -> jne 0x3196b */
  FUN_0018e5c0(0);
  /* test (char)eax, (char)eax -> jne 0x3198b */
  FUN_0018e5c0((int)(uintptr_t)location);
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

/* 0x31c00 — pick the closest swarm member unit to a reference point. */
int actor_perception_unit_from_swarm(int owner_handle, int actor_handle,
                                     int unit_handle, char verify_flag,
                                     float *swarm_origin)
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

  (void)actor_handle;

  owner_actor = (char *)datum_get(actor_data, owner_handle);
  if (*(char *)(owner_actor + 6) == 0) {
    display_assert("actor->meta.active",
                   "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0x68d, 1);
    system_exit(-1);
  }

  best_unit = -1;
  best_dist_sq = 3.4028235e38f;

  if (*(int *)(owner_actor + 0x28) != -1) {
    swarm = (char *)datum_get(*(void **)0x6325a0, *(int *)(owner_actor + 0x28));
    member_count = *(int16_t *)(swarm + 2);
    for (member_index = 0; member_index < member_count; member_index++) {
      char *member =
          (char *)datum_get(*(void **)0x63259c,
                            *(int *)(swarm + member_index * 4 + 0x58));
      if ((*(char *)(member + 2) & 2) != 0) {
        delta[0] = swarm_origin[0] - *(float *)(member + 4);
        delta[1] = swarm_origin[1] - *(float *)(member + 8);
        delta[2] = swarm_origin[2] - *(float *)(member + 0xc);
        dist_sq = delta[0] * delta[0] + delta[1] * delta[1] +
                  delta[2] * delta[2];
        dist_sq *= *(float *)0x2561f0;
      } else if (*(int *)(swarm + member_index * 4 + 0x18) == unit_handle) {
        delta[0] = swarm_origin[0] - *(float *)(member + 4);
        delta[1] = swarm_origin[1] - *(float *)(member + 8);
        delta[2] = swarm_origin[2] - *(float *)(member + 0xc);
        dist_sq = delta[0] * delta[0] + delta[1] * delta[1] +
                  delta[2] * delta[2];
        dist_sq *= *(float *)0x256134;
      } else {
        continue;
      }
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
      delta[0] = swarm_origin[0] - unit_pos[0];
      delta[1] = swarm_origin[1] - unit_pos[1];
      delta[2] = swarm_origin[2] - unit_pos[2];
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

  if (unit_handle != -1 && best_unit == -1) {
    display_assert("result != NONE",
                   "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0x6d9, 1);
    system_exit(-1);
  }
  return best_unit;
}

/* 0x31df0 — refresh prop position / visibility from its tracked unit. */
void prop_position_refresh(int actor_handle, int prop_handle, float *out_pos,
                           char refresh_flag, char swarm_refresh)
{
  char *actor;
  char *prop;
  char *unit;
  char *parent_prop;
  char *vehicle;
  char in_fov;
  int now;
  int swarm_unit;
  int unit_handle;
  float delta[3];
  float dir[3];
  float *default_fwd;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(char *)(actor + 8) == 0)
    return;

  prop = (char *)datum_get(prop_data, prop_handle);
  unit_handle = *(int *)(prop + 0x18);
  unit = (char *)object_get_and_verify_type(unit_handle, 3);

  if (refresh_flag == 0) {
    int16_t status = *(int16_t *)(prop + 0x24);
    if (status >= 4 && status <= 5 && *(char *)(prop + 0x4e) == 0) {
      in_fov = 0;
      if ((*(uint8_t *)(unit + 0xb6) & 4) != 0 &&
          *(int16_t *)(unit + 0x3d0) == 0 && *(int16_t *)(prop + 0x30) == 0) {
        if (FUN_00012170((float *)(unit + 0x18)) <= *(float *)0x255d1c)
          in_fov = 1;
      }
      if (*(int *)(actor + 0x270) == prop_handle && *(char *)(prop + 0xb9) != 0 &&
          *(char *)(prop + 0xba) != 0 && in_fov) {
        *(char *)(prop + 0x4e) = 1;
        *(char *)(prop + 0x127) = 1;
      }
    }
  }

  if (*(char *)(prop + 0x14) != 0 && *(int *)(prop + 0x1c) != -1 &&
      swarm_refresh != 0) {
    now = game_time_get();
    if (*(int *)(prop + 0x28) + 90 <= now) {
      *(int *)(prop + 0x28) = now;
      swarm_unit = actor_perception_unit_from_swarm(
          *(int *)(prop + 0x1c), actor_handle, unit_handle, 0,
          (float *)(actor + 0x120));
      if (swarm_unit != unit_handle) {
        *(int *)(prop + 0x18) = swarm_unit;
        unit = (char *)object_get_and_verify_type(swarm_unit, 3);
        if (*(int16_t *)(prop + 0x24) >= 4 &&
            *(int16_t *)(prop + 0x24) <= 5) {
          parent_prop = (char *)datum_get(prop_data, *(int *)(prop + 0xc));
          *(int *)(parent_prop + 0x18) = swarm_unit;
        } else if (*(int *)(prop + 0xc) != -1) {
          parent_prop = (char *)datum_get(prop_data, *(int *)(prop + 0xc));
          *(int *)(parent_prop + 0x18) = swarm_unit;
        }
      }
    }
  }

  unit_handle = *(int *)(prop + 0x18);
  unit_get_head_position(unit_handle, (float *)(prop + 0x104));
  object_get_world_position(unit_handle, (vector3_t *)(prop + 0xbc));
  FUN_001a9520(unit_handle, (float *)(prop + 0xc8));
  {
    float *actor_pos = (float *)(actor + 0x18);
    *(float *)(prop + 0xd4) = actor_pos[0];
    *(float *)(prop + 0xd8) = actor_pos[1];
    *(float *)(prop + 0xdc) = actor_pos[2];
  }
  *(int *)(prop + 0xec) = -1;
  {
    int placement_handle = object_get_root_parent(unit_handle);
    char *placement =
        (char *)object_get_and_verify_type(placement_handle, 0);
    *(int *)(prop + 0xfc) = *(int *)(placement + 0x48);
    *(int *)(prop + 0x100) = *(int *)(placement + 0x4c);
  }
  {
    int16_t sky_index;
    *(char *)(prop + 0x118) = (char)FUN_0018f3e0((void *)(prop + 0xfc),
                                                  (void *)(prop + 0xc8),
                                                  &sky_index);
  }
  *(int *)(prop + 0x110) = -1;
  *(char *)(prop + 0x135) = 0;
  *(char *)(prop + 0x136) = 0;
  *(int *)(prop + 0x114) = -1;

  if (*(int *)(unit + 0xcc) != -1) {
    vehicle = (char *)object_get_and_verify_type(*(int *)(unit + 0xcc), 0);
    if (*(int16_t *)(vehicle + 0x64) == 1) {
      *(int *)(prop + 0x110) = *(int *)(unit + 0xcc);
      if (*(int *)(vehicle + 0x2d8) == unit_handle ||
          *(int16_t *)(prop + 0x10) == 0xf)
        *(char *)(prop + 0x135) = 1;
      else
        *(char *)(prop + 0x135) = 0;
      if (*(int *)(vehicle + 0x2d4) == unit_handle) {
        char hover = 0;
        vehicle_hover();
        (void)hover;
        *(char *)(prop + 0x136) = hover;
      } else {
        *(char *)(prop + 0x136) = 0;
      }
    } else if ((1 << *(int16_t *)(vehicle + 0x64)) & 3) {
      *(int *)(prop + 0x114) = *(int *)(unit + 0xcc);
    }
  }

  *(char *)(prop + 0x125) = 0;
  if (*(int *)(unit + 0xc8) != -1) {
    int chain = *(int *)(unit + 0xc8);
    while (chain != -1) {
      char *chain_obj = (char *)object_get_and_verify_type(chain, 0);
      if ((1 << *(char *)(chain_obj + 0x64)) & 3)
        (*(char *)(prop + 0x125))++;
      chain = *(int *)(chain_obj + 0xc4);
    }
  }

  actor_perception_find_sense_position(actor_handle, (float *)(prop + 0xbc),
                                       prop_handle, out_pos);
  delta[0] = *(float *)(prop + 0xbc) - out_pos[0];
  delta[1] = *(float *)(prop + 0xbc + 4) - out_pos[1];
  delta[2] = *(float *)(prop + 0xbc + 8) - out_pos[2];
  dir[0] = delta[0];
  dir[1] = delta[1];
  dir[2] = delta[2];
  normalize3d(dir);
  *(float *)(prop + 0x11c) = sqrtf(delta[0] * delta[0] + delta[1] * delta[1] +
                                     delta[2] * delta[2]);
  if (*(float *)(prop + 0x11c) >= *(float *)0x2533c0) {
    default_fwd = *(float **)0x31fc3c;
    *(float *)(prop + 0xe0) = default_fwd[0];
    *(float *)(prop + 0xe4) = default_fwd[1];
    *(float *)(prop + 0xe8) = default_fwd[2];
  } else {
    *(float *)(prop + 0xe0) = dir[0];
    *(float *)(prop + 0xe4) = dir[1];
    *(float *)(prop + 0xe8) = dir[2];
  }
}

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

/* 0x32380 */
void actor_perception_refresh_danger_zone(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int ebp = 0;
  int local_30 = 0;
  int local_8 = 0;
  int local_c = 0;

  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), 0);
  /* relift: cmp word ptr [esi + 0x280], 0 -> jle 0x3293b */
  object_try_and_get_and_verify_type(0, -1);
  /* cmp (int16_t)eax, 2 -> je 0x3240b */
  /* cmp (int16_t)eax, 3 -> je 0x3240b */
  /* cmp (int16_t)eax, 1 -> je 0x3240b */
  display_assert((char *)0x00256248, (char *)0x00255fb0, 3227, 1);
  system_exit(-1);
  object_get_world_position(0, (vector3_t *)((char *)eax + 0x2b0));
  actor_perception_find_sense_position(0, (float *)((char *)eax + 0x2b0), -1, (void *)0);
  tag_get('ihev', *(int *)(local_8));
  FUN_00012170((float *)(uintptr_t)local_8);
  /* relift: relift: fcomp dword ptr [0x256240] */
  /* cmp eax, -1 -> je 0x325ee */
  prop_get_active_by_unit_index(0, 0);
  /* cmp eax, -1 -> je 0x325ee */
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), eax);
  /* cmp eax, -1 -> jne 0x325fa */
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab270), 0);
  /* test eax, eax -> je 0x32623 */
  /* test (char)ecx, (char)ecx -> je 0x32623 */
  /* relift: cmp dword ptr [ebx + 0xcc], -1 -> je 0x32645 */
  object_get_root_parent(0);
  object_get_and_verify_type(eax, -1);
  ai_test_line_of_sight((void *)0, local_30, (float *)((char *)eax + 0x2b0), 0, 0, 0, 0, *(int *)(0x5ab23c));
  /* test (char)eax, (char)eax -> jne 0x326b8 */
  FUN_0002f380(0, -1);
  actor_visibility_at_point();
  /* cmp (int16_t)eax, 2 -> jl 0x326b8 */
  actor_audibility_at_point(0, (void *)0, (float *)((char *)eax + 0x2b0), (void *)(uintptr_t)eax, 0, 0x3f800000, local_c);
  /* cmp (int16_t)eax, 2 -> jl 0x32927 */
  /* relift: cmp dword ptr [ebx + 0xcc], eax -> jne 0x32718 */
  /* relift: cmp word ptr [ebx + 0x64], 5 -> je 0x3273f */
  display_assert((char *)0x00256210, (char *)0x00255fb0, 3257, 1);
  system_exit(-1);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x3278d */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x3278d */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* test (char)eax, (char)eax -> jne 0x326af */
  /* test (char)eax, (char)eax -> jne 0x326af */
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab270), 0);
  /* relift: cmp word ptr [esi + 0x6a], 1 -> je 0x32927 */
  /* test eax, eax -> je 0x327e9 */
  /* test (char)ecx, (char)ecx -> jne 0x32927 */
  tag_get('jorp', *(int *)(local_8));
  object_get_root_parent(0);
  object_get_and_verify_type(eax, 0);
  ai_test_line_of_sight((void *)0, local_30, (float *)((char *)eax + 0x2b0), eax, 0, 0, 0, *(int *)(0x5ab270));
  FUN_0002f380(0, -1);
  actor_visibility_at_point();
  /* cmp (int16_t)eax, 2 -> jl 0x32927 */
  prop_get_active_by_unit_index(0, 0);
  /* cmp eax, -1 -> je 0x328d3 */
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), eax);
  unit_get_animation_frames_remaining(0, (void *)0);
  /* relift: cmp word ptr [ebp - 6], 0x19 -> jne 0x328f2 */
  /* test (char)eax, (char)eax -> je 0x32927 */
  /* test (char)eax, (char)eax -> jne 0x32927 */
  FUN_00027a60(0, 12, 1, (void *)0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)ebp;
  (void)local_30;
  (void)local_8;
  (void)local_c;
}

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
void actor_perception_unreachable(int actor_handle, int leader_handle, char flag)
{
  int eax = 0;
  int esi = 0;

  datum_get((data_t *)(uintptr_t)*(int *)(0x6325a4), actor_handle);
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), leader_handle);
  /* test (char)eax, (char)eax -> je 0x32b11 */
  /* relift: cmp word ptr [esi + 0x9c], 0 -> jne 0x32b04 */
  game_time_get();
  actor_get_perception_knowledge(actor_handle, leader_handle);
  actor_compute_prop_target_weight(actor_handle, leader_handle);

  (void)eax;
  (void)esi;
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

/* 0x33440 — refresh prop status flags from actor + unit state. */
void prop_status_refresh(int actor_handle, int prop_handle, float *out_pos)
{
  char *actor;
  char *prop;
  char *unit;
  char *encounter;
  char *owner_actor;
  char player_present;
  char team_flag;
  float velocity[3];
  float rel_vel;
  float speed_sq;
  float speed;
  int16_t threat_dir;
  int now;

  actor = (char *)datum_get(actor_data, actor_handle);
  if (*(char *)(actor + 8) == 0)
    return;

  encounter = (char *)tag_get('rtca', *(int *)(actor + 0x58));
  if (*(int *)(actor + 0x34) != -1)
    owner_actor = (char *)datum_get(*(void **)0x5ab270, *(int *)(actor + 0x34));
  else
    owner_actor = 0;

  prop = (char *)datum_get(prop_data, prop_handle);
  unit = (char *)object_get_and_verify_type(*(int *)(prop + 0x18), 3);
  now = game_time_get();
  (void)now;

  if (owner_actor == 0 || *(char *)(owner_actor + 0x40) != 0 ||
      *(int16_t *)(actor + 0x6a) == 1)
    player_present = 1;
  else
    player_present = 0;

  team_flag = (char)((*(uint32_t *)(unit + 0x1b4) >> 10) & 1);
  *(char *)(prop + 0x133) = team_flag;
  if (*(char *)(prop + 0x12e) != 0 && game_connection() == 0 &&
      *(char *)0x5ac9c6 != 0)
    *(char *)(prop + 0x133) = 1;

  if (*(char *)(prop + 0x60) != 0) {
    *(char *)(prop + 0x134) = (char)((*(uint32_t *)(unit + 0x1b4) >> 11) & 1);
    switch (*(int16_t *)(actor + 0x1d4)) {
    case 1:
    case 2:
      if (*(char *)(prop + 0x12e) != 0)
        *(char *)(prop + 0x134) = 1;
      break;
    default:
      if (*(int *)(prop + 0x1c) != -1 && *(int *)(actor + 0x1d8) != -1) {
        char *owner =
            (char *)datum_get(actor_data, *(int *)(prop + 0x1c));
        if (((*(int *)(owner + 0x34) ^ *(int *)(actor + 0x1d8)) & 0xffff) == 0) {
          int role = *(int *)(actor + 0x1d8) >> 30;
          if (role == 0 || role == 1 || role == 2) {
            if ((role == 0 &&
                 *(uint16_t *)(actor + 0x1da) == *(uint16_t *)(owner + 0x3c)) ||
                (role == 1 &&
                 *(uint16_t *)(actor + 0x1da) == *(uint16_t *)(owner + 0x3a)))
              *(char *)(prop + 0x134) = 1;
          }
        }
      }
      break;
    }
  }

  object_get_root_location(*(int *)(prop + 0x18), velocity, 0);
  speed_sq =
      velocity[0] * velocity[0] + velocity[1] * velocity[1] + velocity[2] * velocity[2];
  speed = sqrtf(speed_sq);
  if (speed < *(float *)0x256350)
    *(char *)(prop + 0x123) = 0;
  else if (speed < *(float *)0x25634c)
    *(char *)(prop + 0x123) = 1;
  else if (speed < *(float *)0x2546a4)
    *(char *)(prop + 0x123) = 2;
  else
    *(char *)(prop + 0x123) = 3;

  rel_vel = (out_pos[0] - *(float *)(prop + 0xbc)) * *(float *)(prop + 0xe0) +
            (out_pos[1] - *(float *)(prop + 0xbc + 4)) *
                *(float *)(prop + 0xe4) +
            (out_pos[2] - *(float *)(prop + 0xbc + 8)) *
                *(float *)(prop + 0xe8);
  if (rel_vel >= *(float *)0x256348)
    *(char *)(prop + 0x124) = 0;
  else if (rel_vel >= *(float *)0x256344)
    *(char *)(prop + 0x124) = 1;
  else if (rel_vel >= *(float *)0x256340)
    *(char *)(prop + 0x124) = 2;
  else if (rel_vel >= *(float *)0x256350)
    *(char *)(prop + 0x124) = 3;
  else if (rel_vel >= *(float *)0x25634c)
    *(char *)(prop + 0x124) = 4;
  else if (rel_vel >= *(float *)0x2546a4)
    *(char *)(prop + 0x124) = 5;
  else
    *(char *)(prop + 0x124) = 6;

  threat_dir = (int16_t)*(char *)(prop + 0x123);
  if (*(int16_t *)(prop + 0x24) >= 2 && *(int16_t *)(prop + 0x24) <= 3 &&
      threat_dir <= 1 && *(char *)(prop + 0x123) > 1) {
    int16_t local[2];
    local[0] = 1;
    local[1] = (int16_t)prop_handle;
    FUN_00027a60(actor_handle, 2, 1, local);
  }

  if (*(float *)(prop + 0x11c) < *(float *)0x2533c8)
    *(char *)(prop + 0x121) = 0;
  else if (*(float *)(prop + 0x11c) < *(float *)0x254640)
    *(char *)(prop + 0x121) = 1;
  else if (*(float *)(prop + 0x11c) < *(float *)0x253f34)
    *(char *)(prop + 0x121) = 2;
  else if (*(float *)(prop + 0x11c) < *(float *)0x253394)
    *(char *)(prop + 0x121) = 3;
  else
    *(char *)(prop + 0x121) = 4;

  unit_scripting_unit_driver(*(int *)(prop + 0x18), velocity);
  rel_vel = -(velocity[0] * *(float *)(prop + 0xe0) +
              velocity[1] * *(float *)(prop + 0xe4) +
              velocity[2] * *(float *)(prop + 0xe8));
  if (rel_vel < *(float *)0x2533c0)
    speed = *(float *)0x2548fc;
  else if ((rel_vel >= *(float *)0x2533c8) == 0)
    speed = *(float *)0x2533c0;
  else
    speed = sqrtf(*(float *)0x2533c8 - rel_vel * rel_vel) *
              *(float *)(prop + 0x11c);

  if (rel_vel < *(float *)0x25633c) {
    if (speed > *(float *)0x253398 && rel_vel < *(float *)0x256338) {
      if (speed <= *(float *)0x2533ec)
        *(char *)(prop + 0x122) = 1;
      else if (rel_vel <= *(float *)0x253398)
        *(char *)(prop + 0x122) = 2;
      else if (rel_vel <= *(float *)0x2533c0)
        *(char *)(prop + 0x122) = 3;
      else
        *(char *)(prop + 0x122) = 4;
    } else
      *(char *)(prop + 0x122) = 0;
  } else
    *(char *)(prop + 0x122) = 0;

  *(char *)(prop + 0x12f) = (char)(*(int16_t *)(prop + 0x66) == 1);

  if (*(char *)(prop + 0x126) != 0)
    *(int16_t *)(prop + 0x6a) = 0;
  *(char *)(prop + 0x126) = 0;

  *(char *)(prop + 0xa4) = actor_get_perception_knowledge(actor_handle, prop_handle);
  actor_compute_prop_target_weight(actor_handle, prop_handle);
  *(float *)(prop + 0x50) = FUN_000278e0(actor_handle, prop_handle);
  *(char *)(prop + 0x64) = 1;
  (void)encounter;
  (void)player_present;
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

  datum_get((void *)(uintptr_t)ecx, 0);
  object_get_and_verify_type(0, 0);
  object_mark(0);
  /* test (char)eax, (char)eax -> je 0x34930 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x3471f */
  object_get_world_position(0, (void *)(uintptr_t)edx);
  actor_perception_find_sense_position(0, (float *)(uintptr_t)ecx, 0, (void *)(uintptr_t)eax);
  /* cmp eax, -1 -> je 0x34363 */
  actor_perception_unit_from_swarm(0, 0, 0, 0, 0);
  object_get_and_verify_type(0, 0);
  object_get_world_position(0, (void *)(uintptr_t)edx);
  /* cmp edi, -1 -> je 0x34930 */
  /* relift: cmp ebx, dword ptr [ebp + 8] -> je 0x34930 */
  tag_get('tinu', 0);
  game_allegiance_get_team_is_friendly(eax, ecx);
  /* test (char)eax, 4 -> je 0x343e0 */
  /* relift: cmp word ptr [esi + 0x3d0], 0 -> jne 0x343e0 */
  game_time_get();
  /* test (char)eax, 0x41 -> jne 0x34471 */
  /* test (char)eax, (char)eax -> jne 0x34450 */
  /* relift: cmp byte ptr [esi + 0x253], 0x1e -> jne 0x34471 */
  FUN_0002f5f0();
  datum_get((void *)(uintptr_t)edx, 0);
  datum_get((void *)(uintptr_t)eax, 0);
  /* test eax, eax -> je 0x344c7 */
  /* test (char)ecx, (char)ecx -> je 0x34930 */
  /* test (char)ecx, (char)ecx -> jne 0x34930 */
  /* test (char)eax, 0x41 -> je 0x34930 */
  /* test (char)eax, (char)eax -> je 0x34662 */
  datum_get((void *)(uintptr_t)ecx, 0);
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
  display_assert((char *)0x00256354, (char *)0x00255fb0, 2966, 0);
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
  prop_new_unacknowledged(0, 0, 0);
  /* cmp eax, -1 -> je 0x34930 */
  prop_position_refresh(0, 0, 0, 0, 0);
  /* test (char)eax, (char)eax -> jne 0x34930 */
  /* cmp (int16_t)eax, 1 -> jne 0x34748 */
  /* relift: cmp dword ptr [esi + 0x2d4], -1 -> jne 0x34930 */
  /* relift: FUN_00032170(NULL, actor, unit, 0) */
  /* cmp (int16_t)eax, 5 -> jne 0x34930 */
  tag_get('jorp', 0);
  /* test (char)eax, 0x41 -> jne 0x34930 */
  /* relift: cmp dword ptr [eax + 0xcc], -1 -> je 0x34797 */
  /* relift: test byte ptr [eax + 0x1dc], 0x20 -> je 0x34930 */
  object_get_world_position(0, (void *)(uintptr_t)ecx);
  actor_perception_find_sense_position(0, (float *)(uintptr_t)eax, 0, (void *)(uintptr_t)edx);
  /* test (char)eax, 0x41 -> jne 0x34930 */
  /* relift: cmp dword ptr [ecx + 0x28c], edi -> je 0x34930 */
  csmemset((void *)(uintptr_t)esi, 0, 108);
  /* cmp eax, -1 -> je 0x34927 */
  object_try_and_get_and_verify_type(0, 0);
  /* test eax, eax -> je 0x34927 */
  /* test dl, 3 -> je 0x34927 */
  /* cmp esi, eax -> jne 0x34902 */
  game_allegiance_get_team_is_friendly(ecx, eax);
  /* test (char)eax, (char)eax -> jne 0x3492a */
  /* cmp eax, -1 -> je 0x34953 */
  /* relift: tail-call actor_perception_refresh_test_object(); */
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

  FUN_00064b40(param_1, encounter_team, 1, 0);
  /* cmp edi, -1 -> je 0x34c6b */
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), eax);
  /* cmp (int16_t)eax, 2 -> jl 0x349c8 */
  /* cmp (int16_t)eax, 3 -> jg 0x349c8 */
  /* cmp ebx, -1 -> je 0x34b59 */
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), 0);
  /* cmp (int16_t)eax, 1 -> jle 0x34a19 */
  display_assert((char *)0x00256450, (char *)0x00255fb0, 3764, 1);
  system_exit(-1);
  /* cmp (int16_t)eax, 4 -> jl 0x34a2c */
  /* cmp (int16_t)eax, 5 -> jle 0x34a4c */
  display_assert((char *)0x00256430, (char *)0x00255fb0, 3765, 1);
  system_exit(-1);
  /* relift: cmp edx, dword ptr [ebp + 8] -> je 0x34a74 */
  display_assert((char *)0x00256400, (char *)0x00255fb0, 3766, 1);
  system_exit(-1);
  /* relift: cmp dword ptr [ecx + 4], eax -> je 0x34a9f */
  display_assert((char *)0x002563cc, (char *)0x00255fb0, 3767, 1);
  system_exit(-1);
  /* relift: cmp dword ptr [esi + 0xc], ebx -> je 0x34ac4 */
  display_assert((char *)0x00256394, (char *)0x00255fb0, 3768, 1);
  system_exit(-1);
  /* relift: cmp dword ptr [edx + 0xc], edi -> je 0x34aec */
  display_assert((char *)0x0025635c, (char *)0x00255fb0, 3769, 1);
  system_exit(-1);
  /* cmp eax, -1 -> je 0x34b0d */
  prop_orphan_update_information();
  prop_position_refresh(0, 0, 0, 0, 0);
  prop_status_refresh(0, 0, 0);
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), 0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x34b64 */
  /* cmp (int16_t)eax, 1 -> jle 0x34b84 */
  display_assert((char *)0x00256450, (char *)0x00255fb0, 3807, 1);
  system_exit(-1);
  /* cmp eax, -1 -> je 0x34bc5 */
  prop_orphan_from_friend();
  /* cmp edi, -1 -> je 0x34be8 */
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), eax);
  prop_position_refresh(0, 0, 0, 0, 0);
  prop_orphan_transition();
  /* cmp edi, -1 -> jne 0x34bf1 */
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), eax);
  /* test esi, esi -> je 0x34c61 */
  /* cmp ebx, -1 -> je 0x34c2e */
  /* cmp eax, -1 -> je 0x34c44 */
  datum_get((data_t *)(uintptr_t)*(int *)(0x5ab23c), encounter_handle);
  /* relift: cmp word ptr [eax + 0x32], 2 -> jl 0x34c44 */
  actor_get_perception_knowledge(param_1, eax);
  actor_compute_prop_target_weight(param_1, eax);

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
  actor_perception_refresh_danger_zone();
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
