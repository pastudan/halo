#include <stdint.h>
/* actor_perception.c — AI actor perception and prop evaluation.
 *
 * Corresponds to actor_perception.obj.
 * Assertion path: c:\halo\SOURCE\ai\actor_perception.c
 */

#include "../../common.h"
#include "x87_math.h"

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

/* actor_perception_acknowledge (0x2f2b0) — readable C lift (restored pre-naked)
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


/* FUN_0002f380 (0x2f380) — XBE naked draft (batch 86). */
#if defined(__clang__)
static void *(*const b2f380_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b2f380_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b2f380_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
uint16_t FUN_0002f380(int actor_handle __attribute__((unused)), int prop_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0002f380_5\n\t"
      "movl 0x5ab23c, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .LFUN_0002f380_1\n\t"
      "pushl $1\n\t"
      "pushl $0x572\n\t"
      "pushl $0x255fb0\n\t"
      "pushl $0x255f88\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0002f380_1:\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .LFUN_0002f380_2\n\t"
      "cmpw $3, %%ax\n\t"
      "jle .LFUN_0002f380_3\n\t"
      ".LFUN_0002f380_2:\n\t"
      "movw 0x66(%%esi), %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "je .LFUN_0002f380_3\n\t"
      "cmpw $2, %%ax\n\t"
      "je .LFUN_0002f380_3\n\t"
      "movb 0x60(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0002f380_4\n\t"
      "movb 0x127(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0002f380_3\n\t"
      "cmpw $3, 0x6a(%%ebx)\n\t"
      "jl .LFUN_0002f380_4\n\t"
      ".LFUN_0002f380_3:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $3, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0002f380_4:\n\t"
      "movl 0xc(%%esi), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_0002f380_5\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movb 0xb8(%%eax), %%dl\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "testb %%dl, %%dl\n\t"
      "setne %%cl\n\t"
      "addl $2, %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .LFUN_0002f380_6\n\t"
      ".LFUN_0002f380_5:\n\t"
      "movl $2, %%eax\n\t"
      "cmpw %%ax, 0x6e(%%ebx)\n\t"
      "jge .LFUN_0002f380_6\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw $3, 0x6a(%%ebx)\n\t"
      "setge %%al\n\t"
      ".LFUN_0002f380_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b2f380_dget), [assert] "m"(b2f380_assert), [exitfn] "m"(b2f380_exitfn)
      : "memory");
}
#else
#error "FUN_0002f380: clang naked draft required"
#endif


/* FUN_0002f5b0 (0x2f5b0) — readable C lift from XBE leaf (compare z). */
int FUN_0002f5b0(float *a, float *b)
{
  float az;
  float bz;

  az = a[2];
  bz = b[2];
  if (az < bz)
    return -1;
  if (az > bz)
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

/* actor_get_best_damaging_prop (0x2fa70) — readable C lift (restored pre-naked)
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
__declspec(noinline) void
actor_perception_forget_recent_damage(int actor_handle)
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

/* actor_get_vision_distances (0x2f470) — readable C lift. */
void actor_get_vision_distances(int actor_handle, float p1, float p2,
                                float range_param, float *out_a, float *out_b)
{
  char *actor;
  char *meta;
  float base;
  float mid;
  float hi;
  float base07;
  float near_thr;
  float primary;
  float t;
  float blended;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  meta = (char *)tag_get(0x61637472, *(int *)(actor + 0x58));

  /* FPU ja-style: only strict above takes the early exit (NaN continues). */
  if (range_param > *(float *)(meta + 0x28)) {
    *out_b = *(float *)0x2533c0;
    *out_a = *(float *)0x2533c0;
    return;
  }

  base = p1 * p2;
  mid = p2 * *(float *)(meta + 0x2c);
  base07 = *(float *)0x2533c4 * base;
  hi = mid * *(float *)0x2533c4;
  if (hi > *(float *)0x253f30)
    hi = 3.5f;

  if (range_param > *(float *)(meta + 0x20)) {
    *out_b = mid;
    *out_a = hi;
    return;
  }

  near_thr = *(float *)(meta + 0x1c) * *(float *)0x2533f0;
  if (range_param < *(float *)(meta + 0x1c)) {
    primary = base;
  } else {
    t = (range_param - *(float *)(meta + 0x1c)) /
        (*(float *)(meta + 0x20) - *(float *)(meta + 0x1c));
    primary = (*(float *)0x2533c8 - t) * base + t * mid;
  }

  if (range_param < near_thr) {
    *out_b = primary;
    *out_a = base07;
    return;
  }

  t = (range_param - near_thr) / (*(float *)(meta + 0x20) - near_thr);
  blended = (*(float *)0x2533c8 - t) * base07 + t * hi;
  *out_b = primary;
  *out_a = blended;
}

/* FUN_0002f5f0 (0x2f5f0) — readable C lift.
 * actor @eax, unit @edi; stack: scale, visibility, field_60, dz_flag. */
char FUN_0002f5f0(float scale, float visibility, char field_60, char dz_flag,
                  int actor_handle, int unit_handle)
{
  char *actor;
  char *obj;
  float *src;
  float *dst;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);

  if (!((scale + *(float *)0x253f34) > visibility)) {
    return 0;
  }

  if (*(short *)(actor + 0x280) > 1) {
    return 0;
  }

  if (*(short *)(actor + 0x280) == 1) {
    if (*(int *)(actor + 0x28c) == unit_handle) {
      return 0;
    }
    if (!(visibility < *(float *)(actor + 0x2d4))) {
      return 0;
    }
  }

  obj = (char *)object_get_and_verify_type(unit_handle, 3);
  csmemset(actor + 0x280, 0, 0x6c);
  *(short *)(actor + 0x280) = 1;
  *(int *)(actor + 0x28c) = unit_handle;
  *(float *)(actor + 0x294) = scale;
  object_get_world_position(unit_handle, (vector3_t *)(actor + 0x298));

  src = (float *)(obj + 0x18);
  dst = (float *)(actor + 0x2a4);
  dst[0] = src[0];
  dst[1] = src[1];
  dst[2] = src[2];

  *(short *)(actor + 0x284) = 6;
  actor[0x286] = dz_flag;
  *(short *)(actor + 0x282) = (short)(field_60 == 0);
  return 1;
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
/* arctangent (0x2fb60) — readable C lift from XBE leaf (x87 fpatan). */
float arctangent(float y, float x)
{
  return x87_fatan2f(y, x);
}

/* actor_situation_update_target_status (0x300b0) — readable C lift (restored pre-naked). */
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


/* actor_situation_combat_status_update (0x302b0) — readable C lift. */
void actor_situation_combat_status_update(int actor_handle)
{
  char *actor;
  int16_t pending;
  int16_t cur;
  int16_t tier;
  int16_t table_val;
  int16_t hi;
  int16_t combat;
  int16_t z;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  pending = *(int16_t *)(actor + 0x34a);
  if (pending > 0) {
    cur = *(int16_t *)(actor + 0x74);
    if (cur < pending) {
      *(int16_t *)(actor + 0x74) = pending;
      *(int *)(actor + 0x78) = *(int *)(actor + 0x34c);
    } else if (cur == pending) {
      int a = *(int *)(actor + 0x78);
      int b = *(int *)(actor + 0x34c);
      *(int *)(actor + 0x78) = (a > b) ? a : b;
    }
    *(int16_t *)(actor + 0x34a) = 0;
  }

  tier = *(int16_t *)(actor + 0x268);
  if (tier < 0 || tier >= 0xc) {
    display_assert((const char *)0x256030, (const char *)0x255fb0, 0x1138, true);
    system_exit(-1);
  }

  cur = *(int16_t *)(actor + 0x72);
  table_val = *(int16_t *)(0x255f18 + (int)tier * 2);
  hi = (cur > table_val) ? cur : table_val;
  combat = *(int16_t *)(actor + 0x74);
  if ((int)combat > (int)hi)
    cur = combat;
  else if (cur <= table_val)
    cur = table_val;

  *(int16_t *)(actor + 0x6e) = cur;
  if (cur > combat) {
    z = 0;
    *(int16_t *)(actor + 0x74) = z;
  } else {
    z = 0;
  }

  if (*(int16_t *)(actor + 0x6a) < 3)
    *(int *)(actor + 0x7c) = z;
  else
    (*(int *)(actor + 0x7c))++;

  if (cur == z) {
    *(int *)(actor + 0x80) = z;
    *(int *)(actor + 0x84) = z;
    {
      int t = *(int *)(actor + 0x88);
      if (t != -1)
        *(int *)(actor + 0x88) = t + 1;
    }
    if (cur >= 7)
      actor[0x8c] = 1;
    return;
  }

  (*(int *)(actor + 0x80))++;
  if (cur < 4)
    *(int *)(actor + 0x84) = 0;
  else
    (*(int *)(actor + 0x84))++;
  {
    int t = *(int *)(actor + 0x88);
    if (t != -1)
      *(int *)(actor + 0x88) = t + 1;
  }
  if (cur >= 7)
    actor[0x8c] = 1;
}


/* actor_situation_update (0x303f0) — readable C lift (restored pre-naked). */
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


/* actor_situation_try_new_target (0x308e0) — readable C lift. */
char actor_situation_try_new_target(int actor_handle, int target)
{
  char *actor;
  char *prop;
  char *other;
  float weight;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  prop = (char *)datum_get(*(data_t **)0x5ab23c, target);

  if (*(int *)(actor + 0x270) == -1) {
    other = 0;
  } else {
    other = (char *)datum_get(*(data_t **)0x5ab23c, *(int *)(actor + 0x270));
  }

  weight = actor_compute_prop_target_weight(actor_handle, target);
  *(float *)(prop + 0x50) = weight;

  if (!(weight > *(float *)0x2533c0)) {
    return 0;
  }

  if (prop[0x60] == 0) {
    display_assert((const char *)0x2560cc, (const char *)0x255fb0, 0x124d, 1);
    system_exit(-1);
  }

  if (other != 0 && !(weight >= *(float *)(other + 0x50))) {
    return 0;
  }

  *(short *)(actor + 0x268) = 0;
  *(int *)(actor + 0x270) = target;
  *(int *)(actor + 0x26c) = -1;
  actor_situation_update_target_status(actor_handle);
  actor_situation_combat_status_update(actor_handle);
  return 1;
}

/* actor_perception_friend_prop_is_attacking (0x309d0) — readable C lift (restored pre-naked). */
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


/* actor_perception_aiming_vector_test_blockage (0x30b80) — readable C lift (restored pre-naked). */
void actor_perception_aiming_vector_test_blockage(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}


/* FUN_00030d10 (0x30d10) — readable C lift: nearby-actor chance scale.
 * Returns in AL only (MSVC byte return); decl is char for Unicorn mask. */
char FUN_00030d10(int actor_handle, float *chance_inout)
{
  char *actor;
  char *prop;
  char *other;
  int iter[2];
  int count_combat;
  int count_other;
  float scale;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  count_other = 0;
  count_combat = 0;
  FUN_00064540(iter, actor_handle);
  prop = (char *)FUN_00064570(iter);
  if (!prop)
    goto scale_few;

  while (prop) {
    if (*(short *)(prop + 0x24) >= 2 && *(short *)(prop + 0x24) <= 3 &&
        !prop[0x60] &&
        *(short *)(prop + 0x10) == *(short *)(actor + 4) &&
        *(int *)(prop + 0x1c) != -1) {
      other = (char *)datum_get(*(data_t **)0x6325a4, *(int *)(prop + 0x1c));
      if (*(short *)(other + 0x308) > 0 ||
          (*(short *)(other + 0x6c) == 4 && *(short *)(other + 0xa8) > 0)) {
        count_combat++;
      } else if (prop[0x12c]) {
        count_other++;
      }
    }
    prop = (char *)FUN_00064570(iter);
  }

  if ((short)count_combat > 1)
    return 1;

  if ((short)count_other > 1) {
    scale = *(float *)0x2533c8 -
            (float)(count_other - 1) * *(float *)0x25337c;
  } else {
scale_few:
    scale = *(float *)0x2533c8 +
            (float)(1 - count_other) * *(float *)0x253398;
  }

  if (scale < *(float *)0x2533c0)
    scale = *(float *)0x2533c0;
  else if (scale > *(float *)0x253f40)
    scale = *(float *)0x253f40;

  *chance_inout *= scale;
  return 0;
}

/* FUN_00030e60 (0x30e60) — readable C lift. */
int16_t FUN_00030e60(int unused, int16_t *count, int16_t max_count, void *array, int key)
{
  int16_t n;
  int16_t i;
  char *slot;

  (void)unused;
  n = *count;
  for (i = 0; i < n; i++) {
    slot = (char *)array + (int)i * 0x1c;
    if (*(int *)(slot + 8) == key)
      return i;
  }

  if (n >= max_count)
    return -1;

  *count = (int16_t)(n + 1);
  slot = (char *)array + (int)n * 0x1c;
  *(int *)(slot + 4) = -1;
  *(int *)(slot + 8) = -1;
  *(int *)(slot + 0x18) = -1;
  *(short *)slot = 0;
  *(int *)(slot + 0xc) = 0;
  *(short *)(slot + 0x10) = 0;
  *(unsigned int *)(slot + 0x14) = 0x7f7fffffu;
  return n;
}


/* FUN_00030f50 (0x30f50) — XBE naked draft (batch 107). */
#if defined(__clang__)
static void *(*const b30f50_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b30f50_tag)(int, int) = tag_get;
static void (*const b30f50_c64540)(int *out, int actor_handle) = FUN_00064540;
static int (*const b30f50_c64570)(int *iter) = FUN_00064570;
static int16_t (*const b30f50_c30e60)(int unused, int16_t *count, int16_t max_count, void *array, int key) = FUN_00030e60;
static int (*const b30f50_c64ab0)(int actor_handle, int object_handle) = prop_get_active_by_unit_index;
static int *(*const b30f50_gseed)(void) = get_global_random_seed_address;
static float (*const b30f50_rrange)(int *, float, float) = random_real_range;
static void (*const b30f50_ftol)(void) = FUN_001d9068;
static int (*const b30f50_gtime)(void) = game_time_get;

__attribute__((naked, noinline))
void FUN_00030f50(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1e0, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x58(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "call *%[tag]\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "call *%[c64540]\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c64570]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0x1c, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "je .LFUN_00030f50_12\n\t"
      "jmp .LFUN_00030f50_2\n\t"
      ".LFUN_00030f50_1:\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      ".LFUN_00030f50_2:\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movw 0x24(%%eax), %%cx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, %%cx\n\t"
      "jl .LFUN_00030f50_6\n\t"
      "cmpw $3, %%cx\n\t"
      "jg .LFUN_00030f50_6\n\t"
      "movb 0xa4(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00030f50_6\n\t"
      "movb 0x74(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00030f50_3\n\t"
      "movl $4, %%esi\n\t"
      "jmp .LFUN_00030f50_5\n\t"
      ".LFUN_00030f50_3:\n\t"
      "movb 0x12f(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00030f50_4\n\t"
      "movb 0x122(%%eax), %%dl\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpb $1, %%dl\n\t"
      "setle %%cl\n\t"
      "addl $2, %%ecx\n\t"
      "movl %%ecx, %%esi\n\t"
      "jmp .LFUN_00030f50_5\n\t"
      ".LFUN_00030f50_4:\n\t"
      "cmpw $2, 0x32(%%eax)\n\t"
      "jl .LFUN_00030f50_6\n\t"
      "movl $1, %%esi\n\t"
      ".LFUN_00030f50_5:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x18(%%ebx), %%edi\n\t"
      "pushl $0x10\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x1e0(%%ebp), %%eax\n\t"
      "call *%[c30e60]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00030f50_10\n\t"
      "movswl %%ax, %%eax\n\t"
      "imull $0x1c, %%eax, %%eax\n\t"
      "cmpw %%si, -0x1e0(%%ebp,%%eax,1)\n\t"
      "leal -0x1e0(%%ebp,%%eax,1), %%eax\n\t"
      "jge .LFUN_00030f50_10\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl %%edi, 0x8(%%eax)\n\t"
      "movl %%ebx, 0xc(%%eax)\n\t"
      "movw %%si, (%%eax)\n\t"
      "jmp .LFUN_00030f50_10\n\t"
      ".LFUN_00030f50_6:\n\t"
      "movw 0x24(%%ebx), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .LFUN_00030f50_11\n\t"
      "cmpw $3, %%ax\n\t"
      "jg .LFUN_00030f50_11\n\t"
      "movb 0x60(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00030f50_11\n\t"
      "movl 0x1c(%%ebx), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_00030f50_11\n\t"
      "flds 0x11c(%%ebx)\n\t"
      "fcomps 0x253f78\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00030f50_11\n\t"
      "movl 0x6325a4, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, 0x3a8(%%eax)\n\t"
      "je .LFUN_00030f50_11\n\t"
      "movl 0x3ac(%%eax), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_00030f50_11\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl 0x3a4(%%edx), %%edx\n\t"
      "cmpl $-1, %%edx\n\t"
      "je .LFUN_00030f50_7\n\t"
      "cmpl %%edx, 0x3b0(%%eax)\n\t"
      "jl .LFUN_00030f50_11\n\t"
      ".LFUN_00030f50_7:\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c64ab0]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "je .LFUN_00030f50_11\n\t"
      "pushl %%eax\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movw 0x24(%%ebx), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .LFUN_00030f50_10\n\t"
      "cmpw $3, %%ax\n\t"
      "jg .LFUN_00030f50_10\n\t"
      "movb 0xa4(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00030f50_10\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl 0x18(%%esi), %%edi\n\t"
      "pushl $0x10\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x1e0(%%ebp), %%eax\n\t"
      "call *%[c30e60]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00030f50_10\n\t"
      "flds 0x11c(%%esi)\n\t"
      "movswl %%ax, %%ecx\n\t"
      "imull $0x1c, %%ecx, %%ecx\n\t"
      "incw -0x1d0(%%ebp,%%ecx,1)\n\t"
      "leal -0x1e0(%%ebp,%%ecx,1), %%ecx\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xde, 0xc9\n\t"
      "fcoms 0x14(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00030f50_8\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "fstps 0x14(%%ecx)\n\t"
      "movl 0x1c(%%eax), %%edx\n\t"
      "movl %%edx, 0x18(%%ecx)\n\t"
      "jmp .LFUN_00030f50_9\n\t"
      ".LFUN_00030f50_8:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00030f50_9:\n\t"
      "cmpl $-1, 0x4(%%ecx)\n\t"
      "jne .LFUN_00030f50_10\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl 0x18(%%ebx), %%edx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl %%ebx, 0xc(%%ecx)\n\t"
      ".LFUN_00030f50_10:\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      ".LFUN_00030f50_11:\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c64570]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jne .LFUN_00030f50_1\n\t"
      ".LFUN_00030f50_12:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00030f50_31\n\t"
      "movzwl %%ax, %%ecx\n\t"
      "leal -0x1e0(%%ebp), %%ebx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00030f50_13:\n\t"
      "movl 0xc(%%ebx), %%esi\n\t"
      "movb 0x135(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "movw 0x268(%%edi), %%ax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jne .LFUN_00030f50_14\n\t"
      "movb 0x136(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00030f50_15\n\t"
      ".LFUN_00030f50_14:\n\t"
      "movw 0x26a(%%edi), %%ax\n\t"
      ".LFUN_00030f50_15:\n\t"
      "movb 0x12e(%%esi), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00030f50_16\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x26c(%%edi), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jle .LFUN_00030f50_16\n\t"
      "cmpw %%cx, %%ax\n\t"
      "jle .LFUN_00030f50_16\n\t"
      "movl %%ecx, %%eax\n\t"
      ".LFUN_00030f50_16:\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00030f50_17\n\t"
      "cmpw %%ax, (%%ebx)\n\t"
      "jl .LFUN_00030f50_17\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00030f50_18\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_00030f50_19\n\t"
      ".LFUN_00030f50_17:\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00030f50_19\n\t"
      ".LFUN_00030f50_18:\n\t"
      "movw $0x16, 0xaa(%%esi)\n\t"
      ".LFUN_00030f50_19:\n\t"
      "cmpw $0, 0xaa(%%esi)\n\t"
      "jle .LFUN_00030f50_21\n\t"
      "cmpw $0, 0xac(%%esi)\n\t"
      "jne .LFUN_00030f50_20\n\t"
      "movl 0x274(%%edi), %%edx\n\t"
      "movl 0x270(%%edi), %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fmuls 0x253394\n\t"
      "addl $0xc, %%esp\n\t"
      "call *%[ftol]\n\t"
      "movw %%ax, 0xae(%%esi)\n\t"
      ".LFUN_00030f50_20:\n\t"
      "decw 0xaa(%%esi)\n\t"
      "incw 0xac(%%esi)\n\t"
      ".LFUN_00030f50_21:\n\t"
      "cmpw $0x2d, 0x78(%%esi)\n\t"
      "jge .LFUN_00030f50_22\n\t"
      "cmpw $4, (%%ebx)\n\t"
      "jl .LFUN_00030f50_30\n\t"
      ".LFUN_00030f50_22:\n\t"
      "movw 0xae(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00030f50_24\n\t"
      "cmpw %%ax, 0xac(%%esi)\n\t"
      "jl .LFUN_00030f50_24\n\t"
      "movw (%%ebx), %%ax\n\t"
      "cmpw $7, %%ax\n\t"
      "movswl %%ax, %%eax\n\t"
      "jg .LFUN_00030f50_23\n\t"
      "movl $7, %%eax\n\t"
      ".LFUN_00030f50_23:\n\t"
      "movw %%ax, (%%ebx)\n\t"
      ".LFUN_00030f50_24:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00030f50_26\n\t"
      "movw (%%ebx), %%ax\n\t"
      "cmpw $8, %%ax\n\t"
      "movswl %%ax, %%eax\n\t"
      "jg .LFUN_00030f50_25\n\t"
      "movl $8, %%eax\n\t"
      ".LFUN_00030f50_25:\n\t"
      "movw %%ax, (%%ebx)\n\t"
      ".LFUN_00030f50_26:\n\t"
      "movw 0x278(%%edi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00030f50_28\n\t"
      "cmpw %%ax, 0xa6(%%esi)\n\t"
      "jl .LFUN_00030f50_28\n\t"
      "movw (%%ebx), %%ax\n\t"
      "cmpw $9, %%ax\n\t"
      "movswl %%ax, %%eax\n\t"
      "jg .LFUN_00030f50_27\n\t"
      "movl $9, %%eax\n\t"
      ".LFUN_00030f50_27:\n\t"
      "movw %%ax, (%%ebx)\n\t"
      ".LFUN_00030f50_28:\n\t"
      "movw 0x27a(%%edi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00030f50_30\n\t"
      "cmpw %%ax, 0x10(%%ebx)\n\t"
      "jl .LFUN_00030f50_30\n\t"
      "movw (%%ebx), %%ax\n\t"
      "cmpw $6, %%ax\n\t"
      "movswl %%ax, %%eax\n\t"
      "jg .LFUN_00030f50_29\n\t"
      "movl $6, %%eax\n\t"
      ".LFUN_00030f50_29:\n\t"
      "movw %%ax, (%%ebx)\n\t"
      ".LFUN_00030f50_30:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0x1c, %%ebx\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jne .LFUN_00030f50_13\n\t"
      ".LFUN_00030f50_31:\n\t"
      "movl -0x20(%%ebp), %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x3a8(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00030f50_32\n\t"
      "decl %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "movw %%ax, 0x3a8(%%esi)\n\t"
      "jne .LFUN_00030f50_35\n\t"
      "call *%[gtime]\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x3a4(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00030f50_32:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "testw %%ax, %%ax\n\t"
      "movl $5, %%esi\n\t"
      "jle .LFUN_00030f50_35\n\t"
      "leal -0x1e0(%%ebp), %%ecx\n\t"
      "movzwl %%ax, %%edi\n\t"
      ".LFUN_00030f50_33:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw (%%ecx), %%dx\n\t"
      "cmpw %%si, %%dx\n\t"
      "jle .LFUN_00030f50_34\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00030f50_34\n\t"
      "movl %%edx, %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      ".LFUN_00030f50_34:\n\t"
      "addl $0x1c, %%ecx\n\t"
      "decl %%edi\n\t"
      "jne .LFUN_00030f50_33\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .LFUN_00030f50_35\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl 0x28c(%%eax), %%ecx\n\t"
      "movl 0x288(%%eax), %%edx\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "call *%[gseed]\n\t"
      "pushl %%eax\n\t"
      "call *%[rrange]\n\t"
      "fmuls 0x253394\n\t"
      "addl $0xc, %%esp\n\t"
      "call *%[ftol]\n\t"
      "movl -0x20(%%ebp), %%esi\n\t"
      "movw %%ax, 0x3a8(%%esi)\n\t"
      "movl %%ebx, 0x3ac(%%esi)\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, 0x3b0(%%esi)\n\t"
      ".LFUN_00030f50_35:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b30f50_dget), [tag] "m"(b30f50_tag), [c64540] "m"(b30f50_c64540), [c64570] "m"(b30f50_c64570), [c30e60] "m"(b30f50_c30e60), [c64ab0] "m"(b30f50_c64ab0), [gseed] "m"(b30f50_gseed), [rrange] "m"(b30f50_rrange), [ftol] "m"(b30f50_ftol), [gtime] "m"(b30f50_gtime)
      : "memory");
}
#else
#error "FUN_00030f50: clang naked draft required"
#endif


/* actor_berserk (0x31440) — readable C lift from XBE leaf. */
void actor_berserk(int actor_handle, int berserk_flag)
{
  char *actor;
  char *unit;
  int next;
  int flags;

  actor = (char *)datum_get(*(void **)0x6325a4, actor_handle);
  if ((unsigned char)actor[0x378] == (unsigned char)berserk_flag) {
    return;
  }
  actor[0x378] = (char)berserk_flag;
  actor[0x379] = 0;
  if (actor[6] == 0) {
    unit = (char *)object_get_and_verify_type(*(int *)(actor + 0x18), 3);
    flags = *(int *)(unit + 0x1b4);
    if (berserk_flag) {
      flags |= 0x80;
    } else {
      flags &= ~0x80;
    }
    *(int *)(unit + 0x1b4) = flags;
    if (!berserk_flag) {
      return;
    }
    actor[0x375] = 1;
    return;
  }
  next = *(int *)(actor + 0x24);
  while (next != -1) {
    unit = (char *)object_get_and_verify_type(next, 3);
    unit[0xb6] = (char)(unit[0xb6] | 0x80);
    next = *(int *)(unit + 0x1ac);
  }
  if (berserk_flag) {
    actor[0x375] = 1;
  }
}




extern char *actor_combat_get_firing_variant_definition(int actor_handle);
extern bool actor_has_ranged_weapon(int actor_handle);
extern float FUN_000278e0(int actor_handle, int prop_handle);

/* 0x314f0 — visibility level from LOS + engagement at a probe point. */
int16_t actor_visibility_at_point(int actor_handle, float *out_pos, float *head_pos,
                                  char vis_type, int16_t los_result, char flag,
                                  int param_7, int16_t engagement)
{
  char *actor;
  char *encounter;
  char *variant;
  float range;
  float scale;
  float dist_sq;
  float dot;
  float modifier;
  float delta[3];

  if (los_result != 0 && los_result != 1)
    return los_result;

  actor = (char *)datum_get(actor_data, actor_handle);
  encounter = (char *)tag_get('rtca', *(int *)(actor + 0x58));
  variant = actor_combat_get_firing_variant_definition(actor_handle);

  range = *(float *)(encounter + 0x18);
  if (*(float *)(variant + 0x150) <= *(float *)0x2533c0)
    range = *(float *)(variant + 0x150);

  switch (engagement) {
  case 0:
    scale = *(float *)0x253524;
    break;
  case 1:
    scale = *(float *)0x253f3c;
    break;
  case 2:
    scale = *(float *)0x2533f0;
    break;
  case 3:
    scale = *(float *)0x2533c8;
    break;
  default:
    display_assert("engagement >= 0 && engagement <= 3",
                   "c:\\halo\\SOURCE\\ai\\actor_perception.c", 0x4f4, 1);
    system_exit(-1);
    scale = 1.0f;
    break;
  }
  range *= scale;

  delta[0] = head_pos[0] - out_pos[0];
  delta[1] = head_pos[1] - out_pos[1];
  delta[2] = head_pos[2] - out_pos[2];
  dist_sq = delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2];
  if (dist_sq > range * range)
    return 0;

  modifier = 1.0f;
  if ((*(uint8_t *)encounter & 1) == 0) {
    if (vis_type == 0)
      modifier = 0.3f;
    else if (vis_type == 1)
      modifier = 0.7f;
  }

  dot = FUN_0018e690();
  if (dot <= *(float *)0x2533f0) {
    if (dot <= *(float *)0x2549d4)
      modifier = (*(float *)0x2533f0 - dot) * modifier * *(float *)0x256144;
    if (modifier <= *(float *)0x256140)
      modifier = 0.15f;
  } else {
    modifier = 0.15f;
  }

  range = modifier * range;

  if (flag != 0) {
    int profile = (actor_handle & 0xffff) * 0x657c + *(int *)0x331f58;
    *(int *)(profile + 0x656c) = game_time_get();
    *(float *)(profile + 0x6570) = range;
    *(float *)(profile + 0x6574) = modifier;
  }

  if (*(char *)(actor + 6) == 0 && param_7 != 0) {
    float facing;
    float lateral;
    float vertical;
    float angle;

    facing = delta[0] * *(float *)(actor + 0x18c) +
             delta[1] * *(float *)(actor + 0x190) +
             delta[2] * *(float *)(actor + 0x194);
    lateral = delta[0] * *(float *)(actor + 0x198) +
              delta[1] * *(float *)(actor + 0x19c) +
              delta[2] * *(float *)(actor + 0x1a0);
    vertical = delta[0] * *(float *)(actor + 0x1a4) +
               delta[1] * *(float *)(actor + 0x1a8) +
               delta[2] * *(float *)(actor + 0x1ac);
    angle = arctangent(sqrtf(lateral * lateral + vertical * vertical), facing);
    if (angle > *(float *)0x25613c) {
      if (angle <= *(float *)0x256138)
        range = arctangent(vertical, lateral);
      else
        range = 0.0f;
    } else {
      range = *(float *)0x2533c0;
    }
  } else {
    range = *(float *)0x2533c4 * range;
  }

  if (los_result == 0) {
    if (range * range >= dist_sq)
      return 3;
    if (dist_sq <= *(float *)0x255fd8 * *(float *)0x255fd8)
      return 2;
    return 0;
  }

  if (range * range >= dist_sq)
    return 1;
  return 0;
}
/* actor_audibility_at_point (0x31850) — XBE naked draft (batch 230). */
#if defined(__clang__)
static void *(*const b31850_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b31850_tag)(int, int) = tag_get;
static char (*const b31850_c18e5c0)(int location) = FUN_0018e5c0;
static void * (*const b31850_c18e3c0)(void) = scenario_get;
static uint8_t (*const b31850_c193870)(void *bsp, int16_t from_cluster, int16_t to_cluster) = structure_bsp_cluster_sound_encoding;

__attribute__((naked, noinline))
int actor_audibility_at_point(int actor_handle __attribute__((unused)), void *input_block __attribute__((unused)), float *position __attribute__((unused)), void *location __attribute__((unused)), short volume __attribute__((unused)), int range_scale __attribute__((unused)), short flags __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x58(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw %%ax, 0x18(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "je .Lactor_audibility_at_point_16\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "cmpw $-1, 0x28(%%edi)\n\t"
      "je .Lactor_audibility_at_point_15\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "cmpw $-1, 0x4(%%edx)\n\t"
      "je .Lactor_audibility_at_point_15\n\t"
      "movl 0x4c(%%ecx), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "flds (%%eax)\n\t"
      "movl $0xbf800000, -0x8(%%ebp)\n\t"
      "fsubs (%%edi)\n\t"
      "movl $0xbf800000, -0x10(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fmuls 0x20(%%edi)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x1c(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x18(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_audibility_at_point_1\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x2533f0\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".Lactor_audibility_at_point_1:\n\t"
      "movw 0x6a(%%ebx), %%bx\n\t"
      "cmpw $2, %%bx\n\t"
      "jne .Lactor_audibility_at_point_2\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x2533c4\n\t"
      "jmp .Lactor_audibility_at_point_3\n\t"
      ".Lactor_audibility_at_point_2:\n\t"
      "cmpw $1, %%bx\n\t"
      "jne .Lactor_audibility_at_point_4\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x253524\n\t"
      ".Lactor_audibility_at_point_3:\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".Lactor_audibility_at_point_4:\n\t"
      "movw 0x18(%%ebp), %%ax\n\t"
      "cmpw $4, %%ax\n\t"
      "jne .Lactor_audibility_at_point_5\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x2549d4\n\t"
      "jmp .Lactor_audibility_at_point_7\n\t"
      ".Lactor_audibility_at_point_5:\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .Lactor_audibility_at_point_6\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x25614c\n\t"
      "jmp .Lactor_audibility_at_point_7\n\t"
      ".Lactor_audibility_at_point_6:\n\t"
      "cmpw $3, %%ax\n\t"
      "jne .Lactor_audibility_at_point_8\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x2533c4\n\t"
      ".Lactor_audibility_at_point_7:\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".Lactor_audibility_at_point_8:\n\t"
      "leal 0x24(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18e5c0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_audibility_at_point_9\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c18e5c0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_audibility_at_point_10\n\t"
      ".Lactor_audibility_at_point_9:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x25337c\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".Lactor_audibility_at_point_10:\n\t"
      "movw 0x20(%%ebp), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Lactor_audibility_at_point_11\n\t"
      "cmpw $1, %%ax\n\t"
      "je .Lactor_audibility_at_point_11\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x2533c4\n\t"
      "fstps -0x4(%%ebp)\n\t"
      ".Lactor_audibility_at_point_11:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fcomps -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_audibility_at_point_13\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x28(%%edi), %%ax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%ecx), %%dx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c18e3c0]\n\t"
      "pushl %%eax\n\t"
      "call *%[c193870]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "js .Lactor_audibility_at_point_13\n\t"
      "movzbl %%al, %%eax\n\t"
      "andl $0xffffff7f, %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "fmuls 0x256148\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsqrt\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fcoms -0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_audibility_at_point_12\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x10(%%ebp)\n\t"
      ".Lactor_audibility_at_point_12:\n\t"
      "fcoms -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_audibility_at_point_14\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw $3, 0x18(%%ebp)\n\t"
      "setge %%cl\n\t"
      "addl $2, %%ecx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "jmp .Lactor_audibility_at_point_14\n\t"
      ".Lactor_audibility_at_point_13:\n\t"
      "flds -0x10(%%ebp)\n\t"
      ".Lactor_audibility_at_point_14:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "movl 0x331f58, %%eax\n\t"
      "fsqrt\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "andl $0xffff, %%esi\n\t"
      "imull $0x657c, %%esi, %%esi\n\t"
      "addl %%eax, %%esi\n\t"
      "movl %%esi, %%eax\n\t"
      "movl %%edx, 0xa8(%%eax)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "fstps 0xac(%%eax)\n\t"
      "movb $1, 0xa4(%%eax)\n\t"
      "movw %%cx, 0xa6(%%eax)\n\t"
      "fstps 0xb4(%%eax)\n\t"
      "movl %%edx, 0xb0(%%eax)\n\t"
      "movw %%cx, %%ax\n\t"
      ".Lactor_audibility_at_point_15:\n\t"
      "popl %%edi\n\t"
      ".Lactor_audibility_at_point_16:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b31850_dget), [tag] "m"(b31850_tag), [c18e5c0] "m"(b31850_c18e5c0), [c18e3c0] "m"(b31850_c18e3c0), [c193870] "m"(b31850_c193870)
      : "memory");
}
#else
#error "actor_audibility_at_point: clang naked draft required"
#endif


/* actor_perception_find_sense_position (0x31a90) — readable C lift. */
void actor_perception_find_sense_position(int actor_handle, float *position,
                                          int param_3, void *input_block_out)
{
  char *actor;
  char *swarm;
  char *prop;
  float *pp;
  int best;
  float best_d2;
  int i;
  int n;
  float dx, dy, dz, d2;
  unsigned int *src;
  unsigned int *dst;
  int k;

  (void)param_3;
  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  if (!actor[6]) {
    src = (unsigned int *)(actor + 0x120);
    dst = (unsigned int *)input_block_out;
    for (k = 0; k < 0xe; k++)
      dst[k] = src[k];
    return;
  }

  swarm = (char *)datum_get(*(data_t **)0x6325a0, *(int *)(actor + 0x28));
  best = -1;
  {
    unsigned int maxf = 0x7f7fffffu;
    best_d2 = *(float *)&maxf;
  }

  if (*(short *)(actor + 0x1e) <= 0) {
    display_assert((const char *)0x256190, (const char *)0x255fb0, 0x665, true);
    system_exit(-1);
  }
  if (*(int *)(actor + 0x24) == -1) {
    display_assert((const char *)0x256168, (const char *)0x255fb0, 0x666, true);
    system_exit(-1);
  }
  n = *(short *)(swarm + 2);
  if (n <= 0) {
    display_assert((const char *)0x256150, (const char *)0x255fb0, 0x677, true);
    system_exit(-1);
  }
  for (i = 0; i < n; i++) {
    prop = (char *)datum_get(*(data_t **)0x63259c, *(int *)(swarm + 0x58 + i * 4));
    pp = (float *)(prop + 4);
    dx = position[0] - pp[0];
    dy = position[1] - pp[1];
    dz = position[2] - pp[2];
    d2 = dx * dx + dy * dy + dz * dz;
    if (d2 < best_d2) {
      best_d2 = d2;
      best = *(int *)(swarm + 0x18 + i * 4);
    }
  }
  if (best == -1) {
    display_assert((const char *)0x256150, (const char *)0x255fb0, 0x677, true);
    system_exit(-1);
  }
  FUN_0003bde0(actor_handle, best, (char *)input_block_out);
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
/* prop_position_refresh (0x31df0) — readable C lift (restored pre-naked). */
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
          *(int *)(prop + 0x1c), unit_handle, 0, (float *)(actor + 0x120));
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
        char hover = vehicle_hover(*(int *)(unit + 0xcc));
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
/* actor_expected_acknowledgement (0x32940) — readable C lift. */
char actor_expected_acknowledgement(int actor_handle, int prop_handle)
{
  char *prop;
  char *other;
  int iter;
  char found;
  short state;
  float dx, dy, dz, dot;

  datum_get(*(data_t **)0x6325a4, actor_handle);
  prop = (char *)datum_get(*(data_t **)0x5ab23c, prop_handle);
  found = 0;
  state = *(short *)(prop + 0x24);
  if (state >= 4 && state <= 5) {
    display_assert((const char *)0x256318, (const char *)0x255fb0, 0xe22, 1);
    system_exit(-1);
  }
  FUN_00064540(&iter, actor_handle);
  other = (char *)FUN_00064570(&iter);
  while (other) {
    if (iter != prop_handle) {
      if (*(int *)(other + 0x18) == *(int *)(prop + 0x18) ||
          *(int *)(other + 0x1c) == *(int *)(prop + 0x1c) ||
          (*(unsigned char *)(prop + 0x60) && *(unsigned char *)(other + 0x60) &&
           ((*(short *)(other + 0x24) >= 4 && *(short *)(other + 0x24) <= 5) ||
            (*(short *)(other + 0x24) >= 2 && *(short *)(other + 0x24) <= 3)))) {
        dx = *(float *)(prop + 0xbc) - *(float *)(other + 0xbc);
        dy = *(float *)(prop + 0xc0) - *(float *)(other + 0xc0);
        if (dx * dx + dy * dy < *(float *)0x253dcc) {
          dz = *(float *)(other + 0xc4) - *(float *)(prop + 0xc4);
          if (dz < 0)
            dz = -dz;
          if (dz < *(double *)0x256310) {
            dot = *(float *)(other + 0xe8) * *(float *)(prop + 0xe8) +
                  *(float *)(other + 0xe4) * *(float *)(prop + 0xe4) +
                  *(float *)(other + 0xe0) * *(float *)(prop + 0xe0);
            if (dot > *(float *)0x253398)
              found = 1;
          }
        }
      }
    }
    other = (char *)FUN_00064570(&iter);
  }
  return found;
}

/* actor_perception_unreachable (0x32ac0) — readable C lift from XBE leaf. */
void actor_perception_unreachable(int actor_handle, int prop_handle, char flag)
{
  char *prop;

  (void)datum_get(*(void **)0x6325a4, actor_handle);
  prop = (char *)datum_get(*(void **)0x5ab23c, prop_handle);
  if (flag) {
    if (*(short *)(prop + 0x9c) == 0)
      *(short *)(prop + 0x9c) = 1;
    *(int *)(prop + 0xa0) = game_time_get();
  } else {
    *(short *)(prop + 0x9c) = 0;
    *(int *)(prop + 0xa0) = -1;
  }
  *(char *)(prop + 0xa4) =
      (char)actor_get_perception_knowledge(actor_handle, prop_handle);
  *(float *)(prop + 0x50) =
      actor_compute_prop_target_weight(actor_handle, prop_handle);
}

/* actor_perception_tried_to_uncover (0x32b50) — readable C lift. */
void actor_perception_tried_to_uncover(int actor_handle, int prop_handle)
{
  unsigned char *actor;
  unsigned char *prop;

  if (prop_handle == -1)
    return;
  actor = (unsigned char *)datum_get(*(void **)0x6325a4, actor_handle);
  prop = (unsigned char *)datum_get(*(void **)0x5ab23c, prop_handle);
  prop[0xb9] = 1;
  if (*(int *)(actor + 0x270) == prop_handle) {
    actor_situation_update_target_status(actor_handle);
    actor_situation_combat_status_update(actor_handle);
  }
}



/* actor_perception_tried_to_search (0x32bb0) — readable C lift. */
void actor_perception_tried_to_search(int actor_handle, int prop_handle)
{
  unsigned char *actor;
  unsigned char *prop;

  if (prop_handle == -1)
    return;
  actor = (unsigned char *)datum_get(*(void **)0x6325a4, actor_handle);
  prop = (unsigned char *)datum_get(*(void **)0x5ab23c, prop_handle);
  prop[0xba] = 1;
  if (*(int *)(actor + 0x270) == prop_handle) {
    actor_situation_update_target_status(actor_handle);
    actor_situation_combat_status_update(actor_handle);
  }
}



/* actor_perception_abandoned_search (0x32c10) — readable C lift from XBE leaf. */
void actor_perception_abandoned_search(int actor_handle, int prop_handle)
{
  char *actor;
  char *prop;

  if (prop_handle == -1) {
    actor = (char *)datum_get(actor_data, actor_handle);
    *(short *)(actor + 0x3c4) = 0;
    *(char *)(actor + 0x3bc) = 0;
    *(char *)(actor + 0x3bd) = 0;
    *(short *)(actor + 0x72) = 0;
    *(short *)(actor + 0x74) = 0;
    actor_situation_combat_status_update(actor_handle);
    return;
  }

  actor = (char *)datum_get(actor_data, actor_handle);
  prop = (char *)datum_get(*(data_t **)0x5ab23c, prop_handle);
  if (*(short *)(prop + 0x24) == 4)
    *(short *)(prop + 0x24) = 5;
  *(char *)(prop + 0xbb) = 1;
  if (prop_handle == *(int *)(actor + 0x270)) {
    actor_situation_update_target_status(actor_handle);
    actor_situation_combat_status_update(actor_handle);
  }
}



/* actor_emotion_update (0x32cb0) — XBE naked draft (batch 105). */
#if defined(__clang__)
static void *(*const b32cb0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b32cb0_tag)(int, int) = tag_get;
static void (*const b32cb0_c31440)(int actor_handle, int berserk_flag) = actor_berserk;
static void (*const b32cb0_c46f10)(int16_t type, int unit_handle, int param3, int param4, int16_t param5, int16_t param6, int16_t param7) = FUN_00046f10;
static void (*const b32cb0_c64540)(int *out, int actor_handle) = FUN_00064540;
static int (*const b32cb0_c64570)(int *iter) = FUN_00064570;
static char (*const b32cb0_c309d0)(int actor_handle, int iter_handle, float *out_pos) = actor_perception_friend_prop_is_attacking;
static void (*const b32cb0_c30b80)(void) = actor_perception_aiming_vector_test_blockage;
static float (*const b32cb0_c12170)(float *vector) = FUN_00012170;
static float (*const b32cb0_norm)(float *) = normalize3d;
static float *(*const b32cb0_vsca)(float *, float *, float, float *) = vector3d_scale_add;
static void (*const b32cb0_c24be0)(int actor_handle, short param_2, char param_3) = FUN_00024be0;
static char (*const b32cb0_c38370)(int actor_handle) = FUN_00038370;
static void (*const b32cb0_ftol)(void) = FUN_001d9068;
static void (*const b32cb0_c30f50)(void) = FUN_00030f50;

__attribute__((naked, noinline))
void actor_emotion_update(int actor_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x50, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x58(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x61637472\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movb 0x378(%%esi), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movl $3, %%edi\n\t"
      "je .Lactor_emotion_update_2\n\t"
      "movw 0x6e(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Lactor_emotion_update_1\n\t"
      "cmpw %%di, 0x6a(%%esi)\n\t"
      "jl .Lactor_emotion_update_1\n\t"
      "cmpl $0x3f800000, 0x1bc(%%esi)\n\t"
      "jne .Lactor_emotion_update_2\n\t"
      "cmpw %%di, %%ax\n\t"
      "jge .Lactor_emotion_update_2\n\t"
      ".Lactor_emotion_update_1:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c31440]\n\t"
      "addl $8, %%esp\n\t"
      ".Lactor_emotion_update_2:\n\t"
      "movb 0x1c9(%%esi), %%al\n\t"
      "cmpb %%al, 0x374(%%esi)\n\t"
      "je .Lactor_emotion_update_3\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "movb %%al, 0x374(%%esi)\n\t"
      "je .Lactor_emotion_update_3\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testb %%al, %%al\n\t"
      "setne %%cl\n\t"
      "addl $0x16, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c46f10]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".Lactor_emotion_update_3:\n\t"
      "movb 0x378(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_emotion_update_4\n\t"
      "movl (%%ebx), %%eax\n\t"
      "testb $8, %%ah\n\t"
      "jne .Lactor_emotion_update_4\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lactor_emotion_update_5\n\t"
      ".Lactor_emotion_update_4:\n\t"
      "movl $1, %%eax\n\t"
      ".Lactor_emotion_update_5:\n\t"
      "movl 0x158(%%esi), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "movb %%al, 0x375(%%esi)\n\t"
      "je .Lactor_emotion_update_6\n\t"
      "movb $0, 0x375(%%esi)\n\t"
      "jmp .Lactor_emotion_update_7\n\t"
      ".Lactor_emotion_update_6:\n\t"
      "testl $0x1000000, (%%ebx)\n\t"
      "je .Lactor_emotion_update_7\n\t"
      "movb 0x374(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_emotion_update_7\n\t"
      "movb $1, 0x375(%%esi)\n\t"
      ".Lactor_emotion_update_7:\n\t"
      "movl $9, %%eax\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lactor_emotion_update_8:\n\t"
      "movswl %%ax, %%edx\n\t"
      "cmpb $0, 0x1ee(%%edx,%%esi,1)\n\t"
      "jg .Lactor_emotion_update_9\n\t"
      "decl %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jg .Lactor_emotion_update_8\n\t"
      ".Lactor_emotion_update_9:\n\t"
      "cmpw $8, %%ax\n\t"
      "jl .Lactor_emotion_update_10\n\t"
      "movl $0x40000000, 0x350(%%esi)\n\t"
      "jmp .Lactor_emotion_update_15\n\t"
      ".Lactor_emotion_update_10:\n\t"
      "cmpw $7, %%ax\n\t"
      "jl .Lactor_emotion_update_11\n\t"
      "movl $0x3fe66666, 0x350(%%esi)\n\t"
      "jmp .Lactor_emotion_update_15\n\t"
      ".Lactor_emotion_update_11:\n\t"
      "cmpw $6, %%ax\n\t"
      "jl .Lactor_emotion_update_12\n\t"
      "movl $0x3fcccccd, 0x350(%%esi)\n\t"
      "jmp .Lactor_emotion_update_15\n\t"
      ".Lactor_emotion_update_12:\n\t"
      "cmpw $5, %%ax\n\t"
      "jl .Lactor_emotion_update_13\n\t"
      "movl $0x3f99999a, 0x350(%%esi)\n\t"
      "jmp .Lactor_emotion_update_15\n\t"
      ".Lactor_emotion_update_13:\n\t"
      "cmpw %%di, %%ax\n\t"
      "jl .Lactor_emotion_update_14\n\t"
      "movl $0x3f333333, 0x350(%%esi)\n\t"
      "jmp .Lactor_emotion_update_15\n\t"
      ".Lactor_emotion_update_14:\n\t"
      "movl $0, 0x350(%%esi)\n\t"
      ".Lactor_emotion_update_15:\n\t"
      "fldl2e\n\t"
      "movb 0x1c8(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "fmull 0x256330\n\t"
      "fld %%st(0)\n\t"
      "frndint\n\t"
      "fxch %%st(1)\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "f2xm1\n\t"
      "fld1\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fscale\n\t"
      "fstp %%st(1)\n\t"
      "fsubrs 0x2533c8\n\t"
      "flds 0x350(%%esi)\n\t"
      "fsubs 0x354(%%esi)\n\t"
      ".byte 0xde, 0xc9\n\t"
      "fadds 0x354(%%esi)\n\t"
      "fstps 0x354(%%esi)\n\t"
      "je .Lactor_emotion_update_16\n\t"
      "movl 0x1b8(%%esi), %%eax\n\t"
      "movl %%eax, 0x3b4(%%esi)\n\t"
      ".Lactor_emotion_update_16:\n\t"
      "testl $0xc0000000, (%%ebx)\n\t"
      "je .Lactor_emotion_update_28\n\t"
      "cmpl $-1, %%ecx\n\t"
      "jne .Lactor_emotion_update_27\n\t"
      "cmpw %%di, 0x6e(%%esi)\n\t"
      "jl .Lactor_emotion_update_27\n\t"
      "cmpw $8, 0x268(%%esi)\n\t"
      "movb $0, 0x35d(%%esi)\n\t"
      "setg %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb $0, 0x35c(%%esi)\n\t"
      "movb $0, 0x35e(%%esi)\n\t"
      "movb $0, 0x35f(%%esi)\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "je .Lactor_emotion_update_17\n\t"
      "movl 0x270(%%esi), %%ecx\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "addl $0xe0, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      ".Lactor_emotion_update_17:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c64540]\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c64570]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lactor_emotion_update_28\n\t"
      ".Lactor_emotion_update_18:\n\t"
      "movw 0x24(%%edi), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .Lactor_emotion_update_26\n\t"
      "cmpw $3, %%ax\n\t"
      "jg .Lactor_emotion_update_26\n\t"
      "movb 0x60(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_emotion_update_26\n\t"
      "movb 0x127(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_emotion_update_26\n\t"
      "movb 0x14(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_emotion_update_26\n\t"
      "movb 0x12e(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_emotion_update_19\n\t"
      "cmpl $-1, 0x110(%%edi)\n\t"
      "jne .Lactor_emotion_update_26\n\t"
      ".Lactor_emotion_update_19:\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal -0x44(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c309d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_emotion_update_25\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x12c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x44(%%ebp), %%eax\n\t"
      "leal 0xbc(%%edi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c30b80]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "cmpw $1, %%bx\n\t"
      "jl .Lactor_emotion_update_20\n\t"
      "movb $1, 0x35d(%%esi)\n\t"
      "movb 0x12e(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_emotion_update_20\n\t"
      "movb $1, 0x35c(%%esi)\n\t"
      ".Lactor_emotion_update_20:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "cmpl $0, (%%ecx)\n\t"
      "jns .Lactor_emotion_update_25\n\t"
      "movb 0x12e(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_emotion_update_25\n\t"
      "movb 0x12f(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_emotion_update_25\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c12170]\n\t"
      "fcomps 0x2533c8\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_emotion_update_25\n\t"
      "movb 0x504(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_emotion_update_21\n\t"
      "cmpw $0, 0x360(%%esi)\n\t"
      "jle .Lactor_emotion_update_25\n\t"
      ".Lactor_emotion_update_21:\n\t"
      "leal 0x518(%%esi), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fcomps 0x2533c0\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_emotion_update_25\n\t"
      "leal -0x50(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x3ecccccd\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x12c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[vsca]\n\t"
      "pushl $0\n\t"
      "leal -0x50(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x44(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0xbc(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c30b80]\n\t"
      "addl $0x20, %%esp\n\t"
      "cmpw %%bx, %%ax\n\t"
      "jg .Lactor_emotion_update_22\n\t"
      "movl %%ebx, %%eax\n\t"
      ".Lactor_emotion_update_22:\n\t"
      "cmpw $1, %%ax\n\t"
      "jl .Lactor_emotion_update_25\n\t"
      "flds -0x24(%%ebp)\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "call *%[c12170]\n\t"
      "fcomps 0x25337c\n\t"
      "addl $4, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_emotion_update_23\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lactor_emotion_update_24\n\t"
      ".Lactor_emotion_update_23:\n\t"
      "flds 0x2533dc\n\t"
      ".Lactor_emotion_update_24:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_emotion_update_25\n\t"
      "movb $1, 0x35f(%%esi)\n\t"
      ".Lactor_emotion_update_25:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_emotion_update_26\n\t"
      "pushl $0\n\t"
      "addl $0xbc, %%edi\n\t"
      "pushl %%edi\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x12c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c30b80]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .Lactor_emotion_update_26\n\t"
      "movb $1, 0x35e(%%esi)\n\t"
      ".Lactor_emotion_update_26:\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c64570]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lactor_emotion_update_18\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "jmp .Lactor_emotion_update_28\n\t"
      ".Lactor_emotion_update_27:\n\t"
      "movb $0, 0x35d(%%esi)\n\t"
      "movb $0, 0x35c(%%esi)\n\t"
      "movb $0, 0x35e(%%esi)\n\t"
      "movb $0, 0x35f(%%esi)\n\t"
      ".Lactor_emotion_update_28:\n\t"
      "movb 0x35f(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_emotion_update_29\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x3b8(%%esi), %%cx\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c24be0]\n\t"
      "addl $0xc, %%esp\n\t"
      "movw $0x16, 0x360(%%esi)\n\t"
      "jmp .Lactor_emotion_update_30\n\t"
      ".Lactor_emotion_update_29:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x360(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lactor_emotion_update_30\n\t"
      "decl %%eax\n\t"
      "movw %%ax, 0x360(%%esi)\n\t"
      ".Lactor_emotion_update_30:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x35a(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lactor_emotion_update_31\n\t"
      "decl %%eax\n\t"
      "movw %%ax, 0x35a(%%esi)\n\t"
      "jmp .Lactor_emotion_update_48\n\t"
      ".Lactor_emotion_update_31:\n\t"
      "movb 0x374(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_emotion_update_32\n\t"
      "movb 0x378(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_emotion_update_32\n\t"
      "movl 0x300(%%ebx), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jmp .Lactor_emotion_update_33\n\t"
      ".Lactor_emotion_update_32:\n\t"
      "movl 0x2fc(%%ebx), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      ".Lactor_emotion_update_33:\n\t"
      "movswl 0x2f8(%%ebx), %%eax\n\t"
      "decl %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .Lactor_emotion_update_39\n\t"
      "jmp *.Lactor_emotion_update_jt(,%%eax,4)\n\t"
      ".Lactor_emotion_update_34:\n\t"
      "flds 0x354(%%esi)\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_emotion_update_39\n\t"
      "movb $1, %%al\n\t"
      "jmp .Lactor_emotion_update_40\n\t"
      ".Lactor_emotion_update_35:\n\t"
      "flds 0x1bc(%%esi)\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_emotion_update_39\n\t"
      "movb $1, %%al\n\t"
      "jmp .Lactor_emotion_update_40\n\t"
      ".Lactor_emotion_update_36:\n\t"
      "flds 0x1bc(%%esi)\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_emotion_update_39\n\t"
      "movb 0x1f9(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jle .Lactor_emotion_update_39\n\t"
      "movb $1, %%al\n\t"
      "jmp .Lactor_emotion_update_40\n\t"
      ".Lactor_emotion_update_37:\n\t"
      "cmpw $0, 0x6e(%%esi)\n\t"
      "setg %%al\n\t"
      "jmp .Lactor_emotion_update_40\n\t"
      ".Lactor_emotion_update_38:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c38370]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .Lactor_emotion_update_40\n\t"
      ".Lactor_emotion_update_39:\n\t"
      "xorb %%al, %%al\n\t"
      ".Lactor_emotion_update_40:\n\t"
      "testl $0x40000000, (%%ebx)\n\t"
      "je .Lactor_emotion_update_43\n\t"
      "movb 0x35c(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lactor_emotion_update_42\n\t"
      "movb 0x35e(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lactor_emotion_update_41\n\t"
      "xorb %%al, %%al\n\t"
      "jmp .Lactor_emotion_update_43\n\t"
      ".Lactor_emotion_update_41:\n\t"
      "movb 0x35d(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lactor_emotion_update_43\n\t"
      ".Lactor_emotion_update_42:\n\t"
      "movb $1, %%al\n\t"
      ".Lactor_emotion_update_43:\n\t"
      "movb 0x358(%%esi), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lactor_emotion_update_45\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_emotion_update_44\n\t"
      "movb %%al, 0x358(%%esi)\n\t"
      "flds 0x304(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_emotion_update_47\n\t"
      "flds 0x304(%%ebx)\n\t"
      "jmp .Lactor_emotion_update_46\n\t"
      ".Lactor_emotion_update_44:\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lactor_emotion_update_48\n\t"
      ".Lactor_emotion_update_45:\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_emotion_update_48\n\t"
      "movb $1, 0x358(%%esi)\n\t"
      "flds 0x308(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_emotion_update_47\n\t"
      "flds 0x308(%%ebx)\n\t"
      ".Lactor_emotion_update_46:\n\t"
      "fmuls 0x253394\n\t"
      "call *%[ftol]\n\t"
      "movw %%ax, 0x35a(%%esi)\n\t"
      "jmp .Lactor_emotion_update_48\n\t"
      ".Lactor_emotion_update_47:\n\t"
      "movw $0x2d, 0x35a(%%esi)\n\t"
      ".Lactor_emotion_update_48:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x368(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lactor_emotion_update_49\n\t"
      "decl %%eax\n\t"
      "movw %%ax, 0x368(%%esi)\n\t"
      ".Lactor_emotion_update_49:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c30f50]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lactor_emotion_update_jt:\n\t"
      ".long .Lactor_emotion_update_34\n\t"
      ".long .Lactor_emotion_update_35\n\t"
      ".long .Lactor_emotion_update_36\n\t"
      ".long .Lactor_emotion_update_37\n\t"
      ".long .Lactor_emotion_update_38\n\t"
      ".text\n\t"
      :
      : [dget] "m"(b32cb0_dget), [tag] "m"(b32cb0_tag), [c31440] "m"(b32cb0_c31440), [c46f10] "m"(b32cb0_c46f10), [c64540] "m"(b32cb0_c64540), [c64570] "m"(b32cb0_c64570), [c309d0] "m"(b32cb0_c309d0), [c30b80] "m"(b32cb0_c30b80), [c12170] "m"(b32cb0_c12170), [norm] "m"(b32cb0_norm), [vsca] "m"(b32cb0_vsca), [c24be0] "m"(b32cb0_c24be0), [c38370] "m"(b32cb0_c38370), [ftol] "m"(b32cb0_ftol), [c30f50] "m"(b32cb0_c30f50)
      : "memory");
}
#else
#error "actor_emotion_update: clang naked draft required"
#endif


/* actor_perception_become_acknowledged (0x33330) — readable C lift. */
void actor_perception_become_acknowledged(int actor_handle, int prop_handle, char *out_expected)
{
  unsigned char *prop;
  unsigned char *owner;
  char has_owner;
  char expected;
  int16_t awareness;

  prop = (unsigned char *)datum_get(*(void **)0x5ab23c, prop_handle);
  awareness = *(int16_t *)(prop + 0x24);
  expected = 0;
  if (awareness < 2 || awareness > 3) {
    has_owner = (*(int *)(prop + 0xc) != -1);
    expected = actor_expected_acknowledgement(actor_handle, prop_handle);
    if (has_owner) {
      owner = (unsigned char *)datum_get(*(void **)0x5ab23c, *(int *)(prop + 0xc));
      *(int *)(prop + 0x50) = *(int *)(owner + 0x50);
      *(int *)(prop + 0x54) = *(int *)(owner + 0x54);
      *(int *)(prop + 0x58) = *(int *)(owner + 0x58);
      *(int *)(prop + 0x5c) = *(int *)(owner + 0x5c);
      *(int16_t *)(prop + 0x9c) = *(int16_t *)(owner + 0x9c);
      *(int *)(prop + 0xa0) = *(int *)(owner + 0xa0);
      prop[0xa4] = owner[0xa4];
      *(int16_t *)(prop + 0xa6) = *(int16_t *)(owner + 0xa6);
      *(int16_t *)(prop + 0xa8) = *(int16_t *)(owner + 0xa8);
      FUN_0003b410(actor_handle, *(int *)(prop + 0xc), prop_handle);
      prop_iterator_next(actor_handle, *(int *)(prop + 0xc));
      *(int *)(prop + 0xc) = -1;
    }
    *(int16_t *)(prop + 0x24) = 3;
    actor_perception_acknowledge(actor_handle, prop_handle, has_owner, expected);
  }
  if (out_expected)
    *out_expected = expected;
}

/* prop_status_refresh (0x33440) — readable C lift (restored pre-naked). */
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
  int16_t los_mode;
  int16_t los_result;
  int16_t vis;
  int16_t aud;
  int16_t vis_min;
  char hide_prop;
  char force_player;
  char vis_type;
  char owner_fighting;
  char owner_noncombat;
  int owner_handle;
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

  if (*(int16_t *)(prop + 0x24) >= 4 && *(int16_t *)(prop + 0x24) <= 5) {
    los_mode = 0;
    if (*(char *)(prop + 0x12e) != 0 && *(char *)(prop + 0x60) != 0)
      los_mode = 2;
    los_result = (int16_t)ai_test_line_of_sight(
        (float *)(actor + 0x120), *(int16_t *)(actor + 0x28),
        (float *)(prop + 0x104), 0, *(int *)(prop + 0x110),
        *(char *)(actor + 0x158) != -1, los_mode, 0);
    *(int16_t *)(prop + 0x38) = los_result;
    if (*(char *)(prop + 0x133) == 0 && player_present == 0) {
      vis = actor_visibility_at_point(
          actor_handle, out_pos, (float *)(prop + 0x104), 0, los_result, 1, 0,
          FUN_0002f380(actor_handle, prop_handle));
      *(int16_t *)(prop + 0x32) = vis;
      *(int16_t *)(prop + 0x34) = 0;
      *(int16_t *)(prop + 0x36) = 0;
      *(int16_t *)(prop + 0x30) = vis;
    } else {
      *(int16_t *)(prop + 0x30) = 0;
      *(int16_t *)(prop + 0x32) = 0;
      *(int16_t *)(prop + 0x34) = 0;
      *(int16_t *)(prop + 0x36) = 0;
    }
  } else {
    hide_prop = 0;
    force_player = player_present;
    if (*(char *)(prop + 0x12e) != 0 && *(char *)(prop + 0x60) != 0)
      los_mode = 2;
    else
      los_mode = 0;

    los_result = (int16_t)ai_test_line_of_sight(
        (float *)(actor + 0x120), *(int16_t *)(actor + 0x28),
        (float *)(prop + 0x104), 0, *(int *)(prop + 0x110),
        *(char *)(actor + 0x158) != -1, los_mode, 0);
    *(int16_t *)(prop + 0x38) = los_result;
    *(char *)(prop + 0x120) = 2;

    if (*(int16_t *)(unit + 0x64) == 0) {
      char *biped_def = (char *)tag_get('dpib', *(int *)unit);
      *(char *)(prop + 0x130) =
          (char)((*(int *)(biped_def + 0x2f4) >> 2) & 1);
    } else {
      *(char *)(prop + 0x130) = 0;
    }

    *(char *)(prop + 0x131) =
        (char)(*(float *)(unit + 0x32c) < *(float *)0x253398);
    *(char *)(prop + 0x132) =
        (char)((*(uint32_t *)(unit + 0x1b4) >> 0x13) & 1);

    if ((*(uint8_t *)(unit + 0xb6) & 4) != 0 &&
        *(int16_t *)(unit + 0x3d0) == 0) {
      *(char *)(prop + 0x127) = 1;
      *(char *)(prop + 0x128) = 1;
      if (*(char *)(prop + 0x127) == 0)
        *(char *)(prop + 0x129) = 1;
      else
        *(char *)(prop + 0x129) = 0;
      if (*(char *)(prop + 0x127) != 0 && *(char *)(prop + 0x60) == 0 &&
          *(int16_t *)(actor + 0x6a) < 3)
        hide_prop = 1;
      if (*(char *)(prop + 0x127) != 0)
        *(int16_t *)(prop + 0x6a) = 0;
    } else {
      *(char *)(prop + 0x127) = 0;
      *(char *)(prop + 0x128) = 0;
      *(char *)(prop + 0x129) = 0;
    }

    owner_handle = *(int *)(unit + 0x1a8);
    if (owner_handle == -1)
      owner_handle = *(int *)(unit + 0x1a4);
    if (owner_handle != *(int *)(prop + 0x1c)) {
      *(char *)(prop + 0x14) = (char)(owner_handle != *(int *)(unit + 0x1a8));
      *(int *)(prop + 0x1c) = owner_handle;
      if (*(int *)(prop + 0xc) != -1) {
        char *parent = (char *)datum_get(prop_data, *(int *)(prop + 0xc));
        *(int *)(parent + 0x1c) = owner_handle;
        *(char *)(parent + 0x14) = *(char *)(prop + 0x14);
      }
    }

    if (owner_handle == -1) {
      *(char *)(prop + 0x12d) = (char)(*(char *)(prop + 0x127) == 0);
      *(char *)(prop + 0x12b) = 0;
      *(char *)(prop + 0x12c) = 0;
      if (hide_prop != 0) {
        if (player_present == 0 && *(char *)(prop + 0x132) != 0)
          vis_type = 2;
        else
          vis_type = *(char *)(prop + 0x120);
        vis = actor_visibility_at_point(
            actor_handle, out_pos, (float *)(prop + 0x104), vis_type,
            los_result, 1, 0, FUN_0002f380(actor_handle, prop_handle));
        if (vis < 2) {
          *(int16_t *)(prop + 0x30) = vis;
          *(int16_t *)(prop + 0x32) = vis;
          *(int16_t *)(prop + 0x24) = 0;
        }
      }
    } else {
      owner_fighting = actor_is_fighting(owner_handle);
      owner_noncombat = FUN_0003b120(owner_handle);
      (void)owner_noncombat;
      if (owner_fighting != 0 && *(char *)(prop + 0x12c) == 0 &&
          *(char *)(prop + 0x60) == 0 && *(int16_t *)(actor + 0x6a) < 3)
        hide_prop = 1;

      if (hide_prop != 0) {
        if (player_present == 0 && *(char *)(prop + 0x132) != 0)
          vis_type = 2;
        else
          vis_type = *(char *)(prop + 0x120);
        vis = actor_visibility_at_point(
            actor_handle, out_pos, (float *)(prop + 0x104), vis_type,
            los_result, 1, 0, FUN_0002f380(actor_handle, prop_handle));
        if (vis < 2) {
          *(int16_t *)(prop + 0x30) = vis;
          *(int16_t *)(prop + 0x32) = vis;
          *(int16_t *)(prop + 0x24) = 0;
        }
      }
    }

    if (*(char *)(prop + 0x133) != 0) {
      *(int16_t *)(prop + 0x30) = 0;
      *(int16_t *)(prop + 0x32) = 0;
      *(int16_t *)(prop + 0x34) = 0;
      *(int16_t *)(prop + 0x36) = 0;
    } else if (force_player != 0 ||
               ((game_connection() == 0 && *(char *)0x5ac9cb != 0) ||
                (game_connection() == 0 && *(char *)0x5ac9c7 != 0 &&
                 *(char *)(prop + 0x12e) != 0))) {
      force_player = 1;
    }

    if (*(char *)(prop + 0x131) != 0 && *(char *)(prop + 0x60) == 0) {
      if (*(char *)(prop + 0x12e) != 0 &&
          *(float *)(prop + 0x11c) > *(float *)0x2533d8)
        vis_type = 0;
      else if (*(int16_t *)(actor + 0x15e) == 4 ||
               *(int16_t *)(actor + 4) == 0xf)
        vis_type = 0;
      else if (*(char *)(prop + 0x60) == 0 && *(int16_t *)(actor + 0x6a) < 3)
        vis_type = 0;
      else if (*(char *)(prop + 0x127) == 0 && *(char *)(prop + 0x12c) == 0)
        vis_type = 0;
      else
        vis_type = 1;

      if (*(char *)(prop + 0x132) != 0)
        vis_type = 2;
      else
        vis_type = *(char *)(prop + 0x120);

      vis = actor_visibility_at_point(
          actor_handle, out_pos, (float *)(prop + 0x104), vis_type, los_result,
          force_player, 0, FUN_0002f380(actor_handle, prop_handle));
      *(char *)(prop + 0x12a) = (char)(vis > 0 && *(int16_t *)(prop + 0x32) == 0);
      *(int16_t *)(prop + 0x32) = vis;
      if (vis > 0) {
        *(int *)(prop + 0x90) = *(int *)(prop + 0x104);
        *(int *)(prop + 0x94) = *(int *)(prop + 0x108);
        *(int *)(prop + 0x98) = *(int *)(prop + 0x10c);
        *(int *)(prop + 0x8c) = now;
      }

      if ((game_connection() == 0 && *(char *)0x5ac9cc != 0) ||
          (owner_actor != 0 && *(char *)(owner_actor + 0x41) != 0))
        *(int16_t *)(prop + 0x34) = 0;
      else if (*(int16_t *)(prop + 0x66) == 1 || *(int16_t *)(prop + 0x66) == 2)
        *(int16_t *)(prop + 0x34) = 3;
      else {
        int aud_unit = *(int *)(prop + 0x110);
        if (aud_unit == -1)
          aud_unit = *(int *)(prop + 0x18);
        {
          char *aud_obj = (char *)object_get_and_verify_type(aud_unit, 3);
          char *aud_def = (char *)tag_get('tinu', *(int *)aud_obj);
          aud = actor_audibility_at_point(
              actor_handle, (float *)(prop + 0xfc), (float *)(prop + 0xbc),
              aud_obj + 0x48, *(int16_t *)(aud_def + 0x182), 0x3f800000,
              *(int16_t *)(prop + 0x38));
          *(int16_t *)(prop + 0x34) = aud;
        }
      }

      *(int16_t *)(prop + 0x36) = 0;
      if (*(int16_t *)(prop + 0x66) == 0)
        *(int16_t *)(prop + 0x36) = 3;

      if (*(char *)(prop + 0x132) != 0 && *(char *)(prop + 0x122) <= 2 &&
          *(char *)(prop + 0x121) <= 2) {
        if (*(int16_t *)(prop + 0x38) == 0 || *(int16_t *)(prop + 0x38) == 1) {
          if (*(int16_t *)(prop + 0x36) <= 1)
            *(int16_t *)(prop + 0x36) = 1;
        } else if (*(int16_t *)(prop + 0x36) > 1) {
          *(int16_t *)(prop + 0x36) = *(int16_t *)(prop + 0x36);
        } else {
          *(int16_t *)(prop + 0x36) = 1;
        }
      }

      vis_min = *(int16_t *)(prop + 0x34);
      if (*(int16_t *)(prop + 0x36) > vis_min)
        vis_min = *(int16_t *)(prop + 0x36);
      if (*(int16_t *)(prop + 0x32) > vis_min)
        vis_min = *(int16_t *)(prop + 0x32);
      *(int16_t *)(prop + 0x30) = vis_min;
      if (vis_min == 1 && *(int16_t *)(prop + 0x24) >= 2 &&
          *(int16_t *)(prop + 0x24) <= 3)
        *(int16_t *)(prop + 0x30) = 2;

      if (*(int16_t *)(prop + 0x30) != 0) {
        *(int *)(prop + 0x80) = *(int *)(prop + 0xbc);
        *(int *)(prop + 0x84) = *(int *)(prop + 0xc0);
        *(int *)(prop + 0x88) = *(int *)(prop + 0xc4);
        *(int *)(prop + 0x7c) = now;
      }
    }
  }

  if (*(int16_t *)(prop + 0x24) >= 2 && *(int16_t *)(prop + 0x24) <= 3 &&
      *(int16_t *)(prop + 0x32) < 2 && *(char *)(prop + 0xb8) != 0 &&
      *(int *)(prop + 0xb4) != -1) {
    char *killer = (char *)datum_get(actor_data, *(int *)(prop + 0xb4));
    if (*(char *)(killer + 8) != 0 && *(int16_t *)(killer + 0x268) >= 0xa &&
        *(int *)(killer + 0x270) != -1 && *(char *)(killer + 0x454) != 0) {
      char *killer_prop =
          (char *)datum_get(prop_data, *(int *)(killer + 0x270));
      if (*(int *)(killer_prop + 0x18) == *(int *)(prop + 0x18)) {
        *(char *)(prop + 0xb8) = 1;
        *(int16_t *)(prop + 0xb0) = 0;
      }
    }
  }
  if (*(int16_t *)(prop + 0x24) >= 2 && *(int16_t *)(prop + 0x24) <= 3 &&
      *(int16_t *)(prop + 0x32) >= 2)
    *(char *)(prop + 0xb8) = 1;

  if (*(char *)(prop + 0x136) != 0) {
    char dz_flag = (char)(*(int16_t *)(prop + 0x30) >= 2);
    FUN_00032170(out_pos, actor_handle, *(int *)(prop + 0x110), dz_flag);
  }

  if (*(float *)(prop + 0x20) <= *(float *)0x2533c0) {
    if (*(char *)(prop + 0x127) != 0 ||
        *(char *)((char *)unit + 0x253) == 0x1e) {
      if (*(int16_t *)(prop + 0x30) >= 2) {
        FUN_0002f5f0(actor_handle, *(float *)(prop + 0x20),
                     *(float *)(prop + 0x11c), *(int *)(prop + 0x18),
                     *(char *)(prop + 0x60),
                     (char)(*(int16_t *)(prop + 0x30) >= 2));
      }
    }
  }

  if (*(char *)(prop + 0x60) != 0 && *(int16_t *)(prop + 0x24) >= 2 &&
      *(int16_t *)(prop + 0x24) <= 3) {
    char call_unreachable = 0;
    if (actor_has_ranged_weapon(actor_handle)) {
      if (*(float *)(prop + 0x11c) > *(float *)(actor + 0x608))
        call_unreachable = 1;
    } else if ((*(uint32_t *)encounter & 0x8000000) != 0) {
      if (*(float *)(prop + 0x11c) > *(float *)(encounter + 0x37c))
        call_unreachable = 1;
    } else {
      call_unreachable = 1;
    }
    if (call_unreachable != 0)
      actor_perception_unreachable(0, prop_handle, actor_handle);
  }

  if (*(int *)(prop + 0xa0) != -1 &&
      *(int *)(prop + 0xa0) + 0x96 < now)
    actor_perception_unreachable(0, prop_handle, actor_handle);

  if (*(char *)(prop + 0x126) != 0) {
    char clear_status = 0;

    if (*(char *)(prop + 0x12e) == 0) {
      char *prop_owner;
      char *enc;
      char desire;
      char hidden;
      float scaled_vis;
      int max_teams;
      int actor_teams;
      int unit_teams;

      scaled_vis = *(float *)(prop + 0x11c) * *(float *)(prop + 0x20);
      desire = *(char *)(prop + 0x127);

      if (*(int *)(prop + 0x1c) != -1) {
        prop_owner = (char *)datum_get(actor_data, *(int *)(prop + 0x1c));
        if (prop_owner != 0 && *(char *)(prop_owner + 8) != 0 &&
            *(char *)(prop_owner + 0x13) == 0)
          clear_status = 1;
      }
      if (clear_status == 0 && *(char *)(prop + 0x63) == 0) {
        if (scaled_vis < *(float *)0x255fe0)
          clear_status = 1;
        else if (desire != 0) {
          if (*(int *)(actor + 0x34) != -1) {
            enc = (char *)datum_get(*(void **)0x5ab270, *(int *)(actor + 0x34));
            max_teams = *(int *)(enc + 0x58);
            actor_teams = *(int *)(actor + 0x3a0);
            unit_teams = *(int *)(unit + 0x3cc);
            if (max_teams < actor_teams)
              max_teams = actor_teams;
            if (max_teams != -1 && unit_teams != -1 && unit_teams < max_teams)
              desire = 0;
            if (desire != 0) {
              hidden = (char)(*(char *)(enc + 0x45) == 0 &&
                              *(char *)(enc + 0x44) == 0 &&
                              *(char *)(enc + 0x42) == 0);
              if (hidden != 0) {
                if (scaled_vis > *(float *)0x255fdc)
                  clear_status = 1;
              } else if (scaled_vis > *(float *)0x2533c0) {
                if (*(char *)(prop + 0x127) == 0 ||
                    *(int16_t *)(prop + 0x76) <= 0x96)
                  clear_status = 1;
              }
            }
          }
          if (desire != 0 && actor_action_try_to_panic(actor_handle) > 1)
            clear_status = 1;
          if (desire != 0 && *(char *)(prop + 0x127) != 0) {
            float threshold = *(float *)0x254e74;
            if (*(int16_t *)(actor + 0x6a) < 3)
              threshold = *(float *)0x254df8;
            if (scaled_vis > threshold)
              clear_status = 1;
          }
        } else if (scaled_vis > *(float *)0x255fdc) {
          clear_status = 1;
        }
      }

      if (clear_status != 0)
        *(int16_t *)(prop + 0x6a) = 0;
    }
    *(char *)(prop + 0x126) = 0;
  }

  *(char *)(prop + 0xa4) =
      (char)actor_get_perception_knowledge(actor_handle, prop_handle);
  *(float *)(prop + 0x50) =
      actor_compute_prop_target_weight(actor_handle, prop_handle);
  *(float *)(prop + 0x54) = FUN_000278e0(actor_handle, prop_handle);
  *(char *)(prop + 0x64) = 1;
  (void)player_present;
}


/* actor_perception_refresh_test_object (0x342a0) — XBE naked draft (batch 223). */
#if defined(__clang__)
static void *(*const b342a0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b342a0_get)(int, int) = object_get_and_verify_type;
static int (*const b342a0_c13ec50)(int object_handle) = object_mark;
static vector3_t * (*const b342a0_c1412f0)(int object_handle, vector3_t *out_position) = object_get_world_position;
static void (*const b342a0_c31a90)(int actor_handle, float *position, int param_3, void *input_block_out) = (void *)actor_perception_find_sense_position;
static int (*const b342a0_c31c00)(int owner_handle, int unit_handle, char verify_flag, float *swarm_origin) = actor_perception_unit_from_swarm;
static void *(*const b342a0_tag)(int, int) = tag_get;
static bool (*const b342a0_ca7a30)(int16_t team_a, int16_t team_b) = game_allegiance_get_team_is_friendly;
static int (*const b342a0_gtime)(void) = game_time_get;
static char (*const b342a0_c2f5f0)(float scale, float visibility, char field_60, char dz_flag, int actor_handle, int unit_handle) = FUN_0002f5f0;
static void (*const b342a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b342a0_exitfn)(int) = system_exit;
static int16_t (*const b342a0_c1d6d0)(int actor_handle) = actor_action_try_to_panic;
static int (*const b342a0_c645a0)(int actor_handle, int unit_handle, char friendly) = prop_new_unacknowledged;
static void (*const b342a0_c31df0)(int actor_handle, int prop_handle, float *out_pos, char refresh_flag, char swarm_refresh) = prop_position_refresh;
static char (*const b342a0_c32170)(float *sense_pos_out, int actor_handle, int unit_handle, char flag) = FUN_00032170;
static void *(*const b342a0_memset)(void *, int, unsigned int) = csmemset;
static void *(*const b342a0_tryget)(int, int) = object_try_and_get_and_verify_type;
static void (*const b342a0_c342a0)(int actor_handle, int unit_handle, void *primary_list, void *secondary_list) = actor_perception_refresh_test_object;

__attribute__((naked, noinline))
void actor_perception_refresh_test_object(int actor_handle __attribute__((unused)), int unit_handle __attribute__((unused)), void *primary_list __attribute__((unused)), void *secondary_list __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xac, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "je .Lactor_perception_refresh_test_object_42\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lactor_perception_refresh_test_object_1:\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "call *%[c13ec50]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_perception_refresh_test_object_40\n\t"
      "movl -0x14(%%ebp), %%esi\n\t"
      "movw 0x64(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lactor_perception_refresh_test_object_33\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "call *%[c1412f0]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "leal -0x74(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $-1\n\t"
      "leal -0x3c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c31a90]\n\t"
      "movl 0x1a8(%%esi), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_perception_refresh_test_object_2\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "leal -0x74(%%ebp), %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c31c00]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "je .Lactor_perception_refresh_test_object_40\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1412f0]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .Lactor_perception_refresh_test_object_3\n\t"
      ".Lactor_perception_refresh_test_object_2:\n\t"
      "movl 0x1a4(%%esi), %%ebx\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      ".Lactor_perception_refresh_test_object_3:\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lactor_perception_refresh_test_object_40\n\t"
      "cmpl 0x8(%%ebp), %%ebx\n\t"
      "je .Lactor_perception_refresh_test_object_40\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl 0x1c8(%%esi), %%ecx\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "setne -0xd(%%ebp)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x68(%%esi), %%cx\n\t"
      "movl %%eax, %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x3e(%%edx), %%ax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[ca7a30]\n\t"
      "movb %%al, -0x1c(%%ebp)\n\t"
      "movb 0xb6(%%esi), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb $4, %%al\n\t"
      "je .Lactor_perception_refresh_test_object_4\n\t"
      "cmpw $0, 0x3d0(%%esi)\n\t"
      "jne .Lactor_perception_refresh_test_object_4\n\t"
      "cmpl $-1, 0x3cc(%%esi)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jne .Lactor_perception_refresh_test_object_5\n\t"
      "movl $0x7fff, -0x24(%%ebp)\n\t"
      "jmp .Lactor_perception_refresh_test_object_6\n\t"
      ".Lactor_perception_refresh_test_object_4:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movl $0, -0x24(%%ebp)\n\t"
      "jmp .Lactor_perception_refresh_test_object_6\n\t"
      ".Lactor_perception_refresh_test_object_5:\n\t"
      "call *%[gtime]\n\t"
      "subw 0x3cc(%%esi), %%ax\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      ".Lactor_perception_refresh_test_object_6:\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "movl 0x284(%%edi), %%ecx\n\t"
      "fsubs -0x68(%%ebp)\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fsubs -0x64(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fsubs -0x60(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_perception_refresh_test_object_8\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_refresh_test_object_7\n\t"
      "cmpb $0x1e, 0x253(%%esi)\n\t"
      "jne .Lactor_perception_refresh_test_object_8\n\t"
      ".Lactor_perception_refresh_test_object_7:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "fsqrt\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "call *%[c2f5f0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lactor_perception_refresh_test_object_8:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x6325a4, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "movl %%eax, %%edi\n\t"
      "jne .Lactor_perception_refresh_test_object_9\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lactor_perception_refresh_test_object_10\n\t"
      ".Lactor_perception_refresh_test_object_9:\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      ".Lactor_perception_refresh_test_object_10:\n\t"
      "movb -0xd(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "movb $0, 0xf(%%ebp)\n\t"
      "jne .Lactor_perception_refresh_test_object_17\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lactor_perception_refresh_test_object_11\n\t"
      "movb 0x8(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lactor_perception_refresh_test_object_40\n\t"
      "movb 0x13(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lactor_perception_refresh_test_object_40\n\t"
      ".Lactor_perception_refresh_test_object_11:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x255fe0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_perception_refresh_test_object_40\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_perception_refresh_test_object_24\n\t"
      "movl 0x34(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movb $1, %%bl\n\t"
      "je .Lactor_perception_refresh_test_object_21\n\t"
      "movl 0x5ab270, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[get]\n\t"
      "movl 0x58(%%esi), %%ecx\n\t"
      "movl 0x3a0(%%edi), %%edx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jg .Lactor_perception_refresh_test_object_12\n\t"
      "movl %%edx, %%ecx\n\t"
      ".Lactor_perception_refresh_test_object_12:\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lactor_perception_refresh_test_object_14\n\t"
      "movl 0x3cc(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_perception_refresh_test_object_13\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .Lactor_perception_refresh_test_object_14\n\t"
      ".Lactor_perception_refresh_test_object_13:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".Lactor_perception_refresh_test_object_14:\n\t"
      "movb 0x45(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_refresh_test_object_15\n\t"
      "movb 0x44(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_refresh_test_object_15\n\t"
      "movb 0x42(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_refresh_test_object_15\n\t"
      "movb $1, %%al\n\t"
      "jmp .Lactor_perception_refresh_test_object_16\n\t"
      ".Lactor_perception_refresh_test_object_15:\n\t"
      "xorb %%al, %%al\n\t"
      ".Lactor_perception_refresh_test_object_16:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lactor_perception_refresh_test_object_40\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_perception_refresh_test_object_21\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x255fdc\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_perception_refresh_test_object_40\n\t"
      ".Lactor_perception_refresh_test_object_17:\n\t"
      "movb -0x1c(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "jne .Lactor_perception_refresh_test_object_19\n\t"
      ".Lactor_perception_refresh_test_object_18:\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      ".Lactor_perception_refresh_test_object_19:\n\t"
      "movb 0xf(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_perception_refresh_test_object_32\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_perception_refresh_test_object_20\n\t"
      "pushl $1\n\t"
      "pushl $0xb96\n\t"
      "pushl $0x255fb0\n\t"
      "pushl $0x256354\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_perception_refresh_test_object_20:\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "cmpw $0x80, %%ax\n\t"
      "jge .Lactor_perception_refresh_test_object_40\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "movl $0xffffffff, 0x8(%%esi,%%ecx,4)\n\t"
      "movswl 0x2(%%esi), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl %%eax, 0x4(%%esi,%%edx,4)\n\t"
      "movswl 0x2(%%esi), %%eax\n\t"
      "incl %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "fstps (%%esi,%%ecx,4)\n\t"
      "incw 0x2(%%esi)\n\t"
      "jmp .Lactor_perception_refresh_test_object_40\n\t"
      ".Lactor_perception_refresh_test_object_21:\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_perception_refresh_test_object_17\n\t"
      "movb -0x1c(%%ebp), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lactor_perception_refresh_test_object_22\n\t"
      "cmpw $0x96, -0x24(%%ebp)\n\t"
      "jg .Lactor_perception_refresh_test_object_40\n\t"
      ".Lactor_perception_refresh_test_object_22:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d6d0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $1, %%ax\n\t"
      "jg .Lactor_perception_refresh_test_object_40\n\t"
      "testb %%bl, %%bl\n\t"
      "flds 0x254e74\n\t"
      "jne .Lactor_perception_refresh_test_object_23\n\t"
      "cmpw $3, 0x6a(%%edi)\n\t"
      "jge .Lactor_perception_refresh_test_object_23\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x254df8\n\t"
      ".Lactor_perception_refresh_test_object_23:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lactor_perception_refresh_test_object_17\n\t"
      "jmp .Lactor_perception_refresh_test_object_40\n\t"
      ".Lactor_perception_refresh_test_object_24:\n\t"
      "movb -0x1c(%%ebp), %%al\n\t"
      "flds -0x8(%%ebp)\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_perception_refresh_test_object_26\n\t"
      "fcomps 0x255fd8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_perception_refresh_test_object_25\n\t"
      "movb $1, 0xf(%%ebp)\n\t"
      "jmp .Lactor_perception_refresh_test_object_17\n\t"
      ".Lactor_perception_refresh_test_object_25:\n\t"
      "movb $0, 0xf(%%ebp)\n\t"
      "jmp .Lactor_perception_refresh_test_object_17\n\t"
      ".Lactor_perception_refresh_test_object_26:\n\t"
      "fcomps 0x255fdc\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_perception_refresh_test_object_27\n\t"
      "movb $1, %%cl\n\t"
      "jmp .Lactor_perception_refresh_test_object_28\n\t"
      ".Lactor_perception_refresh_test_object_27:\n\t"
      "xorb %%cl, %%cl\n\t"
      ".Lactor_perception_refresh_test_object_28:\n\t"
      "cmpw $4, 0x6e(%%edi)\n\t"
      "jl .Lactor_perception_refresh_test_object_29\n\t"
      "movb $1, 0xf(%%ebp)\n\t"
      "jmp .Lactor_perception_refresh_test_object_31\n\t"
      ".Lactor_perception_refresh_test_object_29:\n\t"
      "movb 0x1cc(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_refresh_test_object_30\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movb $1, 0xf(%%ebp)\n\t"
      "fcomps 0x254e74\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_perception_refresh_test_object_31\n\t"
      ".Lactor_perception_refresh_test_object_30:\n\t"
      "movb $0, 0xf(%%ebp)\n\t"
      ".Lactor_perception_refresh_test_object_31:\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lactor_perception_refresh_test_object_40\n\t"
      "jmp .Lactor_perception_refresh_test_object_18\n\t"
      ".Lactor_perception_refresh_test_object_32:\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c645a0]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_perception_refresh_test_object_40\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x74(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c31df0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_refresh_test_object_40\n\t"
      "incw (%%esi)\n\t"
      "jmp .Lactor_perception_refresh_test_object_40\n\t"
      ".Lactor_perception_refresh_test_object_33:\n\t"
      "cmpw $1, %%ax\n\t"
      "jne .Lactor_perception_refresh_test_object_34\n\t"
      "cmpl $-1, 0x2d4(%%esi)\n\t"
      "jne .Lactor_perception_refresh_test_object_40\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "call *%[c32170]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Lactor_perception_refresh_test_object_40\n\t"
      ".Lactor_perception_refresh_test_object_34:\n\t"
      "cmpw $5, %%ax\n\t"
      "jne .Lactor_perception_refresh_test_object_40\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x70726f6a\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ebx\n\t"
      "flds 0x1a8(%%ebx)\n\t"
      "addl $8, %%esp\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_perception_refresh_test_object_40\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "cmpl $-1, 0xcc(%%eax)\n\t"
      "je .Lactor_perception_refresh_test_object_35\n\t"
      "testb $0x20, 0x1dc(%%eax)\n\t"
      "je .Lactor_perception_refresh_test_object_40\n\t"
      ".Lactor_perception_refresh_test_object_35:\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1412f0]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0xac(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $-1\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c31a90]\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fsubs -0xa0(%%ebp)\n\t"
      "addl $0x18, %%esp\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fsubs -0x9c(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fsubs -0x98(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x1a8(%%ebx)\n\t"
      "fadds 0x253f34\n\t"
      "fcomps 0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_perception_refresh_test_object_40\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movw 0x280(%%ecx), %%ax\n\t"
      "cmpw $2, %%ax\n\t"
      "leal 0x280(%%ecx), %%esi\n\t"
      "jl .Lactor_perception_refresh_test_object_36\n\t"
      "jne .Lactor_perception_refresh_test_object_40\n\t"
      "cmpl %%edi, 0x28c(%%ecx)\n\t"
      "je .Lactor_perception_refresh_test_object_40\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2d4(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_perception_refresh_test_object_40\n\t"
      ".Lactor_perception_refresh_test_object_36:\n\t"
      "pushl $0x6c\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "movw $2, (%%esi)\n\t"
      "movl %%edi, 0x28c(%%eax)\n\t"
      "movl 0x1a8(%%ebx), %%edx\n\t"
      "movl %%edx, 0x294(%%eax)\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "leal 0x298(%%eax), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0x2c(%%ebp), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "leal 0x18(%%ecx), %%edx\n\t"
      "movl (%%edx), %%edi\n\t"
      "leal 0x2a4(%%eax), %%esi\n\t"
      "movl %%edi, (%%esi)\n\t"
      "movl 0x4(%%edx), %%edi\n\t"
      "movl %%edi, 0x4(%%esi)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%esi)\n\t"
      "movw $0x1e, 0x284(%%eax)\n\t"
      "movb $0, 0x286(%%eax)\n\t"
      "movw $0, 0x282(%%eax)\n\t"
      "movl 0x74(%%ecx), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_perception_refresh_test_object_38\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[tryget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lactor_perception_refresh_test_object_38\n\t"
      "movb 0x64(%%eax), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testb $3, %%dl\n\t"
      "je .Lactor_perception_refresh_test_object_38\n\t"
      "movl -0x18(%%ebp), %%edi\n\t"
      "movl 0x18(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl 0x74(%%ecx), %%esi\n\t"
      "je .Lactor_perception_refresh_test_object_37\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jne .Lactor_perception_refresh_test_object_37\n\t"
      "movw $2, 0x282(%%edi)\n\t"
      "jmp .Lactor_perception_refresh_test_object_39\n\t"
      ".Lactor_perception_refresh_test_object_37:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x68(%%ecx), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x3e(%%edi), %%cx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[ca7a30]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_refresh_test_object_39\n\t"
      "movw $1, 0x282(%%edi)\n\t"
      "jmp .Lactor_perception_refresh_test_object_39\n\t"
      ".Lactor_perception_refresh_test_object_38:\n\t"
      "movl -0x18(%%ebp), %%edi\n\t"
      ".Lactor_perception_refresh_test_object_39:\n\t"
      "movl %%esi, 0x290(%%edi)\n\t"
      ".Lactor_perception_refresh_test_object_40:\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl 0xc8(%%edx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_perception_refresh_test_object_41\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c342a0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lactor_perception_refresh_test_object_41:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl 0xc4(%%ecx), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .Lactor_perception_refresh_test_object_1\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".Lactor_perception_refresh_test_object_42:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [dget] "m"(b342a0_dget), [get] "m"(b342a0_get), [c13ec50] "m"(b342a0_c13ec50), [c1412f0] "m"(b342a0_c1412f0), [c31a90] "m"(b342a0_c31a90), [c31c00] "m"(b342a0_c31c00), [tag] "m"(b342a0_tag), [ca7a30] "m"(b342a0_ca7a30), [gtime] "m"(b342a0_gtime), [c2f5f0] "m"(b342a0_c2f5f0), [assert] "m"(b342a0_assert), [exitfn] "m"(b342a0_exitfn), [c1d6d0] "m"(b342a0_c1d6d0), [c645a0] "m"(b342a0_c645a0), [c31df0] "m"(b342a0_c31df0), [c32170] "m"(b342a0_c32170), [memset] "m"(b342a0_memset), [tryget] "m"(b342a0_tryget), [c342a0] "m"(b342a0_c342a0)
      : "memory");
}
#else
#error "actor_perception_refresh_test_object: clang naked draft required"
#endif


/* actor_perception_create_orphan_from_friend (0x34970) — XBE naked draft (batch 227). */
#if defined(__clang__)
static int (*const b34970_c64b40)(int actor_handle, int unit_handle, char create_if_needed, char refresh_flag) = FUN_00064b40;
static void *(*const b34970_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b34970_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b34970_exitfn)(int) = system_exit;
static void (*const b34970_c64a60)(int actor_handle, int parent_prop, int unused) = prop_orphan_update_information;
static void (*const b34970_c31df0)(int actor_handle, int prop_handle, float *out_pos, char refresh_flag, char swarm_refresh) = prop_position_refresh;
static void (*const b34970_c33440)(int actor_handle, int prop_handle, float *out_pos) = prop_status_refresh;
static int (*const b34970_c64970)(int actor_handle, int parent_prop, int source_prop) = prop_orphan_from_friend;
static int (*const b34970_c648a0)(int actor_handle, int parent_prop) = prop_orphan_transition;
static bool (*const b34970_c2fc20)(int actor_handle, int clump_item_handle) = actor_get_perception_knowledge;
static float (*const b34970_c2fd10)(int actor_handle, int clump_item_handle) = actor_compute_prop_target_weight;

__attribute__((naked, noinline))
char actor_perception_create_orphan_from_friend(int actor_handle __attribute__((unused)), int unit_handle __attribute__((unused)), int encounter_team __attribute__((unused)), int friend_prop __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x44, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "movb $1, %%bl\n\t"
      "pushl %%ecx\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "call *%[c64b40]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lactor_perception_create_orphan_from_friend_24\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "jl .Lactor_perception_create_orphan_from_friend_1\n\t"
      "cmpw $3, %%ax\n\t"
      "jg .Lactor_perception_create_orphan_from_friend_1\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jmp .Lactor_perception_create_orphan_from_friend_20\n\t"
      ".Lactor_perception_create_orphan_from_friend_1:\n\t"
      "movl 0xc(%%esi), %%ebx\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .Lactor_perception_create_orphan_from_friend_12\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "movb $0, -0xc(%%ebp)\n\t"
      "jl .Lactor_perception_create_orphan_from_friend_2\n\t"
      "cmpw $1, %%ax\n\t"
      "jle .Lactor_perception_create_orphan_from_friend_3\n\t"
      ".Lactor_perception_create_orphan_from_friend_2:\n\t"
      "pushl $1\n\t"
      "pushl $0xeb4\n\t"
      "pushl $0x255fb0\n\t"
      "pushl $0x256450\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_perception_create_orphan_from_friend_3:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movw 0x24(%%ecx), %%ax\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .Lactor_perception_create_orphan_from_friend_4\n\t"
      "cmpw $5, %%ax\n\t"
      "jle .Lactor_perception_create_orphan_from_friend_5\n\t"
      ".Lactor_perception_create_orphan_from_friend_4:\n\t"
      "pushl $1\n\t"
      "pushl $0xeb5\n\t"
      "pushl $0x255fb0\n\t"
      "pushl $0x256430\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_perception_create_orphan_from_friend_5:\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "cmpl 0x8(%%ebp), %%edx\n\t"
      "je .Lactor_perception_create_orphan_from_friend_6\n\t"
      "pushl $1\n\t"
      "pushl $0xeb6\n\t"
      "pushl $0x255fb0\n\t"
      "pushl $0x256400\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_perception_create_orphan_from_friend_6:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl %%eax, 0x4(%%ecx)\n\t"
      "je .Lactor_perception_create_orphan_from_friend_7\n\t"
      "pushl $1\n\t"
      "pushl $0xeb7\n\t"
      "pushl $0x255fb0\n\t"
      "pushl $0x2563cc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_perception_create_orphan_from_friend_7:\n\t"
      "cmpl %%ebx, 0xc(%%esi)\n\t"
      "je .Lactor_perception_create_orphan_from_friend_8\n\t"
      "pushl $1\n\t"
      "pushl $0xeb8\n\t"
      "pushl $0x255fb0\n\t"
      "pushl $0x256394\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_perception_create_orphan_from_friend_8:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "cmpl %%edi, 0xc(%%edx)\n\t"
      "je .Lactor_perception_create_orphan_from_friend_9\n\t"
      "pushl $1\n\t"
      "pushl $0xeb9\n\t"
      "pushl $0x255fb0\n\t"
      "pushl $0x25635c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_perception_create_orphan_from_friend_9:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_perception_create_orphan_from_friend_10\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c64a60]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x18(%%ecx), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%edx, 0x18(%%esi)\n\t"
      "jmp .Lactor_perception_create_orphan_from_friend_11\n\t"
      ".Lactor_perception_create_orphan_from_friend_10:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movw $4, 0x24(%%eax)\n\t"
      "movw $0, 0x3c(%%eax)\n\t"
      "movb $1, -0xc(%%ebp)\n\t"
      ".Lactor_perception_create_orphan_from_friend_11:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "leal -0x44(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[c31df0]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal -0x44(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c33440]\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "movl %%ebx, %%edi\n\t"
      "call *%[dget]\n\t"
      "addl $0x28, %%esp\n\t"
      "jmp .Lactor_perception_create_orphan_from_friend_19\n\t"
      ".Lactor_perception_create_orphan_from_friend_12:\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lactor_perception_create_orphan_from_friend_13\n\t"
      "cmpw $1, %%ax\n\t"
      "jle .Lactor_perception_create_orphan_from_friend_14\n\t"
      ".Lactor_perception_create_orphan_from_friend_13:\n\t"
      "pushl $1\n\t"
      "pushl $0xedf\n\t"
      "pushl $0x255fb0\n\t"
      "pushl $0x256450\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_perception_create_orphan_from_friend_14:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_perception_create_orphan_from_friend_15\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c64970]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lactor_perception_create_orphan_from_friend_17\n\t"
      "movl 0x5ab23c, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "movl %%edx, 0x18(%%eax)\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x1c(%%eax)\n\t"
      "movb 0x14(%%esi), %%dl\n\t"
      "addl $8, %%esp\n\t"
      "movb %%dl, 0x14(%%eax)\n\t"
      "jmp .Lactor_perception_create_orphan_from_friend_16\n\t"
      ".Lactor_perception_create_orphan_from_friend_15:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x44(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c31df0]\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c648a0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      ".Lactor_perception_create_orphan_from_friend_16:\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .Lactor_perception_create_orphan_from_friend_18\n\t"
      ".Lactor_perception_create_orphan_from_friend_17:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_perception_create_orphan_from_friend_18:\n\t"
      "movl 0x5ab23c, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      ".Lactor_perception_create_orphan_from_friend_19:\n\t"
      "movl %%eax, %%esi\n\t"
      ".Lactor_perception_create_orphan_from_friend_20:\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lactor_perception_create_orphan_from_friend_23\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .Lactor_perception_create_orphan_from_friend_21\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_perception_create_orphan_from_friend_22\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, 0x32(%%eax)\n\t"
      "jl .Lactor_perception_create_orphan_from_friend_22\n\t"
      ".Lactor_perception_create_orphan_from_friend_21:\n\t"
      "movb $1, 0xb8(%%esi)\n\t"
      "movw $0, 0xb0(%%esi)\n\t"
      "movl %%ebx, 0xb4(%%esi)\n\t"
      ".Lactor_perception_create_orphan_from_friend_22:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c2fc20]\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "movb %%al, 0xa4(%%esi)\n\t"
      "call *%[c2fd10]\n\t"
      "fstps 0x50(%%esi)\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lactor_perception_create_orphan_from_friend_23:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_perception_create_orphan_from_friend_24:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [c64b40] "m"(b34970_c64b40), [dget] "m"(b34970_dget), [assert] "m"(b34970_assert), [exitfn] "m"(b34970_exitfn), [c64a60] "m"(b34970_c64a60), [c31df0] "m"(b34970_c31df0), [c33440] "m"(b34970_c33440), [c64970] "m"(b34970_c64970), [c648a0] "m"(b34970_c648a0), [c2fc20] "m"(b34970_c2fc20), [c2fd10] "m"(b34970_c2fd10)
      : "memory");
}
#else
#error "actor_perception_create_orphan_from_friend: clang naked draft required"
#endif


/* actor_perception_refresh (0x34c80) — XBE naked draft (batch 104). */
#if defined(__clang__)
static void * (*const b34c80_c18e3c0)(void) = scenario_get;
static void *(*const b34c80_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b34c80_memset)(void *, int, unsigned int) = csmemset;
static void *(*const b34c80_get)(int, int) = object_get_and_verify_type;
static uint32_t * (*const b34c80_c193550)(void *bsp, int16_t cluster_index) = structure_bsp_get_cluster_sound_data;
static void (*const b34c80_c108f00)(int16_t bit_vector_size, int v0, int v1, int result_out) = bit_vector_or;
static void (*const b34c80_c13eb70)(void) = object_reset_markers;
static void (*const b34c80_c64540)(int *out, int actor_handle) = FUN_00064540;
static int (*const b34c80_c64570)(int *iter) = FUN_00064570;
static int16_t (*const b34c80_c1d6d0)(int actor_handle) = actor_action_try_to_panic;
static int16_t (*const b34c80_c13fe10)(void *iter_state, int object_handle) = object_get_first_cluster;
static int16_t (*const b34c80_c13d5f0)(void *param_1, int param_2) = FUN_0013d5f0;
static int (*const b34c80_c13ec50)(int object_handle) = object_mark;
static void (*const b34c80_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b34c80_exitfn)(int) = system_exit;
static int (*const b34c80_gtime)(void) = game_time_get;
static void (*const b34c80_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b34c80_c3b410)(int actor_handle, int old_prop, int new_prop) = FUN_0003b410;
static void (*const b34c80_c64a80)(int actor_handle, int prop_handle) = prop_iterator_next;
static int (*const b34c80_c13d5b0)(int *state, int16_t cluster_idx) = cluster_partition_object_iter_first;
static void (*const b34c80_c342a0)(int actor_handle, int unit_handle, void *primary_list, void *secondary_list) = actor_perception_refresh_test_object;
static int (*const b34c80_c13d5d0)(int *state) = cluster_partition_object_iter_next;
static void (*const b34c80_c13d570)(int *param_1, int param_2) = cluster_get_first_noncollideable_object;
static void (*const b34c80_c13d590)(int *param_1) = cluster_get_next_noncollideable_object;
static void __cdecl (*const b34c80_c1d9260)(void *base, size_t nmemb, size_t size, int (__cdecl *compar)(const void *, const void *)) = qsort;
static int (*const b34c80_c645a0)(int actor_handle, int unit_handle, char friendly) = prop_new_unacknowledged;
static void (*const b34c80_c31df0)(int actor_handle, int prop_handle, float *out_pos, char refresh_flag, char swarm_refresh) = prop_position_refresh;
static void (*const b34c80_c13ebc0)(void) = object_marker_end;

__attribute__((naked, noinline))
void actor_perception_refresh(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xcc4, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c18e3c0]\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl %%ebx, -0x1c(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movw %%cx, -0x6be(%%ebp)\n\t"
      "movw %%cx, -0x6c0(%%ebp)\n\t"
      "movw %%cx, -0xcc2(%%ebp)\n\t"
      "movw %%cx, -0xcc4(%%ebp)\n\t"
      "movb 0x6(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "je .Lactor_perception_refresh_3\n\t"
      "movl 0x28(%%eax), %%edx\n\t"
      "movl 0x6325a0, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "pushl $0x40\n\t"
      "leal -0x84(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "movb $0, -0x4(%%ebp)\n\t"
      "call *%[memset]\n\t"
      "xorl %%edi, %%edi\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw %%di, 0x2(%%esi)\n\t"
      "jle .Lactor_perception_refresh_4\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lactor_perception_refresh_1:\n\t"
      "movswl %%di, %%edx\n\t"
      "movl 0x18(%%esi,%%edx,4), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movswl 0x4c(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lactor_perception_refresh_2\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c193550]\n\t"
      "leal -0x84(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x84(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x134(%%ebx), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c108f00]\n\t"
      "addl $0x18, %%esp\n\t"
      "movb $1, -0x4(%%ebp)\n\t"
      ".Lactor_perception_refresh_2:\n\t"
      "incl %%edi\n\t"
      "cmpw 0x2(%%esi), %%di\n\t"
      "jl .Lactor_perception_refresh_1\n\t"
      "movb -0x4(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_perception_refresh_4\n\t"
      "leal -0x84(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "jmp .Lactor_perception_refresh_4\n\t"
      ".Lactor_perception_refresh_3:\n\t"
      "movswl 0x148(%%eax), %%eax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lactor_perception_refresh_4\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c193550]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      ".Lactor_perception_refresh_4:\n\t"
      "call *%[c13eb70]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c64540]\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c64570]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lactor_perception_refresh_52\n\t"
      ".Lactor_perception_refresh_5:\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .Lactor_perception_refresh_6\n\t"
      "cmpw $5, %%ax\n\t"
      "jle .Lactor_perception_refresh_51\n\t"
      ".Lactor_perception_refresh_6:\n\t"
      "flds 0x11c(%%esi)\n\t"
      "movl 0x20(%%esi), %%eax\n\t"
      "movw 0x76(%%esi), %%cx\n\t"
      "movw 0x6a(%%esi), %%dx\n\t"
      "movb 0x12e(%%esi), %%bl\n\t"
      "movl 0x1c(%%esi), %%edi\n\t"
      "fld %%st(0)\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "movb 0x60(%%esi), %%al\n\t"
      "movw %%cx, -0x30(%%ebp)\n\t"
      "movb 0x63(%%esi), %%cl\n\t"
      "movw %%dx, -0x3c(%%ebp)\n\t"
      "movb 0x127(%%esi), %%dl\n\t"
      "movb %%al, -0x4(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movb %%cl, -0x18(%%ebp)\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "movb %%dl, -0x14(%%ebp)\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "fstp %%st(0)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jne .Lactor_perception_refresh_7\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lactor_perception_refresh_8\n\t"
      ".Lactor_perception_refresh_7:\n\t"
      "movl 0x6325a4, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      ".Lactor_perception_refresh_8:\n\t"
      "testb %%bl, %%bl\n\t"
      "movb $0, -0x5(%%ebp)\n\t"
      "je .Lactor_perception_refresh_9\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lactor_perception_refresh_33\n\t"
      ".Lactor_perception_refresh_9:\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lactor_perception_refresh_11\n\t"
      "movb 0x8(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lactor_perception_refresh_10\n\t"
      "movb 0x13(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lactor_perception_refresh_11\n\t"
      ".Lactor_perception_refresh_10:\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .Lactor_perception_refresh_33\n\t"
      ".Lactor_perception_refresh_11:\n\t"
      "movb -0x18(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_refresh_12\n\t"
      "cmpw $0, -0x3c(%%ebp)\n\t"
      "jle .Lactor_perception_refresh_13\n\t"
      ".Lactor_perception_refresh_12:\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lactor_perception_refresh_33\n\t"
      ".Lactor_perception_refresh_13:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x255fe0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_perception_refresh_14\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .Lactor_perception_refresh_33\n\t"
      ".Lactor_perception_refresh_14:\n\t"
      "movb -0x14(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_perception_refresh_26\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl 0x34(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movb $1, %%bl\n\t"
      "je .Lactor_perception_refresh_20\n\t"
      "movl 0x5ab270, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl -0x2c(%%ebp), %%edx\n\t"
      "pushl $3\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[get]\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl 0x58(%%edi), %%ecx\n\t"
      "movl 0x3a0(%%edx), %%edx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jg .Lactor_perception_refresh_15\n\t"
      "movl %%edx, %%ecx\n\t"
      ".Lactor_perception_refresh_15:\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .Lactor_perception_refresh_17\n\t"
      "movl 0x3cc(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_perception_refresh_16\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .Lactor_perception_refresh_17\n\t"
      ".Lactor_perception_refresh_16:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".Lactor_perception_refresh_17:\n\t"
      "movb 0x45(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_refresh_18\n\t"
      "movb 0x44(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_refresh_18\n\t"
      "movb 0x42(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_refresh_18\n\t"
      "movb $1, %%al\n\t"
      "jmp .Lactor_perception_refresh_19\n\t"
      ".Lactor_perception_refresh_18:\n\t"
      "xorb %%al, %%al\n\t"
      ".Lactor_perception_refresh_19:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lactor_perception_refresh_33\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_perception_refresh_20\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x255fdc\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_perception_refresh_23\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lactor_perception_refresh_33\n\t"
      ".Lactor_perception_refresh_20:\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lactor_perception_refresh_21\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lactor_perception_refresh_33\n\t"
      ".Lactor_perception_refresh_21:\n\t"
      "movb -0x4(%%ebp), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lactor_perception_refresh_22\n\t"
      "cmpw $0x96, -0x30(%%ebp)\n\t"
      "jle .Lactor_perception_refresh_22\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .Lactor_perception_refresh_33\n\t"
      ".Lactor_perception_refresh_22:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d6d0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $1, %%ax\n\t"
      "jle .Lactor_perception_refresh_24\n\t"
      ".Lactor_perception_refresh_23:\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .Lactor_perception_refresh_33\n\t"
      ".Lactor_perception_refresh_24:\n\t"
      "testb %%bl, %%bl\n\t"
      "flds 0x254e74\n\t"
      "jne .Lactor_perception_refresh_25\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "cmpw $3, 0x6a(%%ecx)\n\t"
      "jge .Lactor_perception_refresh_25\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x254df8\n\t"
      ".Lactor_perception_refresh_25:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_perception_refresh_23\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lactor_perception_refresh_33\n\t"
      ".Lactor_perception_refresh_26:\n\t"
      "movb -0x4(%%ebp), %%al\n\t"
      "flds -0xc(%%ebp)\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_perception_refresh_27\n\t"
      "fcomps 0x255fd8\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lactor_perception_refresh_31\n\t"
      ".Lactor_perception_refresh_27:\n\t"
      "fcomps 0x255fdc\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lactor_perception_refresh_28\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lactor_perception_refresh_29\n\t"
      ".Lactor_perception_refresh_28:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".Lactor_perception_refresh_29:\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "cmpw $4, 0x6e(%%eax)\n\t"
      "jl .Lactor_perception_refresh_30\n\t"
      "movb $1, -0x5(%%ebp)\n\t"
      "jmp .Lactor_perception_refresh_33\n\t"
      ".Lactor_perception_refresh_30:\n\t"
      "movb 0x1cc(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lactor_perception_refresh_32\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x254e74\n\t"
      ".Lactor_perception_refresh_31:\n\t"
      "fnstsw %%ax\n\t"
      "movb $1, -0x5(%%ebp)\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lactor_perception_refresh_33\n\t"
      ".Lactor_perception_refresh_32:\n\t"
      "movb $0, -0x5(%%ebp)\n\t"
      ".Lactor_perception_refresh_33:\n\t"
      "testb %%bl, %%bl\n\t"
      "movb %%bl, -0x4(%%ebp)\n\t"
      "je .Lactor_perception_refresh_36\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lactor_perception_refresh_36\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x44(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movb $0, -0x4(%%ebp)\n\t"
      "call *%[c13fe10]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lactor_perception_refresh_36\n\t"
      ".Lactor_perception_refresh_34:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "sarl $5, %%eax\n\t"
      "testl %%edx, (%%edi,%%eax,4)\n\t"
      "jne .Lactor_perception_refresh_35\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x44(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13d5f0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .Lactor_perception_refresh_34\n\t"
      "jmp .Lactor_perception_refresh_36\n\t"
      ".Lactor_perception_refresh_35:\n\t"
      "movb $1, -0x4(%%ebp)\n\t"
      ".Lactor_perception_refresh_36:\n\t"
      "movb 0x14(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_perception_refresh_40\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_perception_refresh_40\n\t"
      "movl 0x6325a4, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x28(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_perception_refresh_38\n\t"
      "pushl %%eax\n\t"
      "movl 0x6325a0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "xorl %%edi, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%di, 0x2(%%ebx)\n\t"
      "jle .Lactor_perception_refresh_40\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lactor_perception_refresh_37:\n\t"
      "movswl %%di, %%ecx\n\t"
      "movl 0x18(%%ebx,%%ecx,4), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c13ec50]\n\t"
      "addl $4, %%esp\n\t"
      "incl %%edi\n\t"
      "cmpw 0x2(%%ebx), %%di\n\t"
      "jl .Lactor_perception_refresh_37\n\t"
      "jmp .Lactor_perception_refresh_40\n\t"
      ".Lactor_perception_refresh_38:\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "movl 0x24(%%eax), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lactor_perception_refresh_40\n\t"
      ".Lactor_perception_refresh_39:\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c13ec50]\n\t"
      "movl 0x1ac(%%ebx), %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .Lactor_perception_refresh_39\n\t"
      ".Lactor_perception_refresh_40:\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13ec50]\n\t"
      "movb -0x4(%%ebp), %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_perception_refresh_47\n\t"
      "movb 0x60(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "leal -0x6c0(%%ebp), %%edi\n\t"
      "jne .Lactor_perception_refresh_41\n\t"
      "leal -0xcc4(%%ebp), %%edi\n\t"
      ".Lactor_perception_refresh_41:\n\t"
      "movb -0x5(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb 0x127(%%esi), %%al\n\t"
      "je .Lactor_perception_refresh_46\n\t"
      "testb %%al, %%al\n\t"
      "je .Lactor_perception_refresh_42\n\t"
      "pushl $1\n\t"
      "pushl $0xa6d\n\t"
      "pushl $0x255fb0\n\t"
      "pushl $0x2564c4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_perception_refresh_42:\n\t"
      "movw 0x2(%%edi), %%ax\n\t"
      "cmpw $0x80, %%ax\n\t"
      "jge .Lactor_perception_refresh_43\n\t"
      "flds -0xc(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "fmuls 0x2564c0\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "movl %%eax, 0x4(%%edi,%%edx,4)\n\t"
      "movswl 0x2(%%edi), %%eax\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "movl %%edx, 0x8(%%edi,%%ecx,4)\n\t"
      "movswl 0x2(%%edi), %%eax\n\t"
      "incl %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "fstps (%%edi,%%eax,4)\n\t"
      "incw 0x2(%%edi)\n\t"
      "jmp .Lactor_perception_refresh_51\n\t"
      ".Lactor_perception_refresh_43:\n\t"
      "cmpl $-1, 0x2c8520\n\t"
      "je .Lactor_perception_refresh_44\n\t"
      "call *%[gtime]\n\t"
      "movl 0x2c8520, %%ecx\n\t"
      "addl $0x96, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jle .Lactor_perception_refresh_51\n\t"
      ".Lactor_perception_refresh_44:\n\t"
      "movb 0x60(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl $0x2564b8, %%eax\n\t"
      "jne .Lactor_perception_refresh_45\n\t"
      "movl $0x2564b0, %%eax\n\t"
      ".Lactor_perception_refresh_45:\n\t"
      "pushl $0x80\n\t"
      "pushl %%eax\n\t"
      "pushl $0x256474\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x10, %%esp\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, 0x2c8520\n\t"
      "jmp .Lactor_perception_refresh_51\n\t"
      ".Lactor_perception_refresh_46:\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lactor_perception_refresh_51\n\t"
      "incw (%%edi)\n\t"
      "jmp .Lactor_perception_refresh_51\n\t"
      ".Lactor_perception_refresh_47:\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .Lactor_perception_refresh_48\n\t"
      "cmpw $5, %%ax\n\t"
      "jle .Lactor_perception_refresh_49\n\t"
      ".Lactor_perception_refresh_48:\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "je .Lactor_perception_refresh_50\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c3b410]\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c64a80]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lactor_perception_refresh_50\n\t"
      ".Lactor_perception_refresh_49:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      ".Lactor_perception_refresh_50:\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c3b410]\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c64a80]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_perception_refresh_51:\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c64570]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lactor_perception_refresh_5\n\t"
      ".Lactor_perception_refresh_52:\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .Lactor_perception_refresh_58\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl 0x134(%%eax), %%ecx\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .Lactor_perception_refresh_58\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lactor_perception_refresh_53\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lactor_perception_refresh_53:\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "sarl $5, %%eax\n\t"
      "testl %%edx, (%%ebx,%%eax,4)\n\t"
      "je .Lactor_perception_refresh_57\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c13d5b0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_perception_refresh_55\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lactor_perception_refresh_54:\n\t"
      "leal -0xcc4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x6c0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c342a0]\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c13d5d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lactor_perception_refresh_54\n\t"
      ".Lactor_perception_refresh_55:\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c13d570]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_perception_refresh_57\n\t"
      "jmp .Lactor_perception_refresh_56\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lactor_perception_refresh_56:\n\t"
      "leal -0xcc4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x6c0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c342a0]\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c13d590]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lactor_perception_refresh_56\n\t"
      ".Lactor_perception_refresh_57:\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl 0x134(%%ecx), %%edx\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .Lactor_perception_refresh_53\n\t"
      "jmp .Lactor_perception_refresh_59\n\t"
      ".Lactor_perception_refresh_58:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      ".Lactor_perception_refresh_59:\n\t"
      "movw -0x6be(%%ebp), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lactor_perception_refresh_69\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpw $4, -0x6c0(%%ebp)\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "jge .Lactor_perception_refresh_64\n\t"
      "pushl $0x2f5b0\n\t"
      "movswl %%ax, %%edx\n\t"
      "pushl $0xc\n\t"
      "pushl %%edx\n\t"
      "leal -0x6bc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9260]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw %%di, -0x6be(%%ebp)\n\t"
      "jle .Lactor_perception_refresh_69\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lactor_perception_refresh_60:\n\t"
      "movswl %%di, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "shll $2, %%eax\n\t"
      "cmpl %%ebx, -0x6b8(%%ebp,%%eax,1)\n\t"
      "jne .Lactor_perception_refresh_61\n\t"
      "movl -0x6bc(%%ebp,%%eax,1), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c645a0]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .Lactor_perception_refresh_62\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0xbc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c31df0]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_perception_refresh_61:\n\t"
      "movw -0x6c0(%%ebp), %%ax\n\t"
      "incw %%ax\n\t"
      "cmpw $4, %%ax\n\t"
      "movw %%ax, -0x6c0(%%ebp)\n\t"
      "jge .Lactor_perception_refresh_63\n\t"
      ".Lactor_perception_refresh_62:\n\t"
      "incl %%edi\n\t"
      "cmpw -0x6be(%%ebp), %%di\n\t"
      "jl .Lactor_perception_refresh_60\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "jmp .Lactor_perception_refresh_69\n\t"
      ".Lactor_perception_refresh_63:\n\t"
      "movw -0x6be(%%ebp), %%ax\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      ".Lactor_perception_refresh_64:\n\t"
      "cmpw %%ax, %%di\n\t"
      "jge .Lactor_perception_refresh_69\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lactor_perception_refresh_65:\n\t"
      "movswl %%di, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ebx\n\t"
      "movl -0x6b8(%%ebp,%%ebx,4), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "leal -0x6b8(%%ebp,%%ebx,4), %%ebx\n\t"
      "je .Lactor_perception_refresh_68\n\t"
      "pushl %%eax\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movw 0x24(%%edi), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .Lactor_perception_refresh_66\n\t"
      "cmpw $5, %%ax\n\t"
      "jle .Lactor_perception_refresh_67\n\t"
      ".Lactor_perception_refresh_66:\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_perception_refresh_67\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c3b410]\n\t"
      "movl 0xc(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c64a80]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_perception_refresh_67:\n\t"
      "movl (%%ebx), %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c3b410]\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c64a80]\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_perception_refresh_68:\n\t"
      "incl %%edi\n\t"
      "cmpw -0x6be(%%ebp), %%di\n\t"
      "movl %%edi, -0x10(%%ebp)\n\t"
      "jl .Lactor_perception_refresh_65\n\t"
      ".Lactor_perception_refresh_69:\n\t"
      "movw -0xcc2(%%ebp), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jle .Lactor_perception_refresh_80\n\t"
      "movl -0x6c0(%%ebp), %%eax\n\t"
      "movl -0xcc4(%%ebp), %%edx\n\t"
      "leal (%%edx,%%eax,1), %%ebx\n\t"
      "movswl %%ax, %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "addl $2, %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "jg .Lactor_perception_refresh_70\n\t"
      "movl $4, %%eax\n\t"
      ".Lactor_perception_refresh_70:\n\t"
      "cmpw %%ax, %%bx\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "jge .Lactor_perception_refresh_75\n\t"
      "pushl $0x2f5b0\n\t"
      "movswl %%cx, %%ecx\n\t"
      "pushl $0xc\n\t"
      "pushl %%ecx\n\t"
      "leal -0xcc0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9260]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $0, -0xcc2(%%ebp)\n\t"
      "jle .Lactor_perception_refresh_80\n\t"
      ".Lactor_perception_refresh_71:\n\t"
      "movswl %%di, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "shll $2, %%eax\n\t"
      "cmpl $-1, -0xcbc(%%ebp,%%eax,1)\n\t"
      "jne .Lactor_perception_refresh_72\n\t"
      "movl -0xcc0(%%ebp,%%eax,1), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c645a0]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_perception_refresh_73\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0xbc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c31df0]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_perception_refresh_72:\n\t"
      "incw -0xcc4(%%ebp)\n\t"
      "incl %%ebx\n\t"
      "cmpw -0x1c(%%ebp), %%bx\n\t"
      "jge .Lactor_perception_refresh_74\n\t"
      ".Lactor_perception_refresh_73:\n\t"
      "incl %%edi\n\t"
      "cmpw -0xcc2(%%ebp), %%di\n\t"
      "jl .Lactor_perception_refresh_71\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "call *%[c13ebc0]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lactor_perception_refresh_74:\n\t"
      "movw -0xcc2(%%ebp), %%cx\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      ".Lactor_perception_refresh_75:\n\t"
      "cmpw %%cx, %%di\n\t"
      "jge .Lactor_perception_refresh_80\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "jmp .Lactor_perception_refresh_76\n\t"
      "leal (%%esp), %%esp\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lactor_perception_refresh_76:\n\t"
      "movswl %%cx, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ebx\n\t"
      "movl -0xcbc(%%ebp,%%ebx,4), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "leal -0xcbc(%%ebp,%%ebx,4), %%ebx\n\t"
      "je .Lactor_perception_refresh_79\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movw 0x24(%%edi), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .Lactor_perception_refresh_77\n\t"
      "cmpw $5, %%ax\n\t"
      "jle .Lactor_perception_refresh_78\n\t"
      ".Lactor_perception_refresh_77:\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lactor_perception_refresh_78\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c3b410]\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c64a80]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_perception_refresh_78:\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c3b410]\n\t"
      "movl (%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c64a80]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lactor_perception_refresh_79:\n\t"
      "incl %%ecx\n\t"
      "cmpw -0xcc2(%%ebp), %%cx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jl .Lactor_perception_refresh_76\n\t"
      ".Lactor_perception_refresh_80:\n\t"
      "call *%[c13ebc0]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e3c0] "m"(b34c80_c18e3c0), [dget] "m"(b34c80_dget), [memset] "m"(b34c80_memset), [get] "m"(b34c80_get), [c193550] "m"(b34c80_c193550), [c108f00] "m"(b34c80_c108f00), [c13eb70] "m"(b34c80_c13eb70), [c64540] "m"(b34c80_c64540), [c64570] "m"(b34c80_c64570), [c1d6d0] "m"(b34c80_c1d6d0), [c13fe10] "m"(b34c80_c13fe10), [c13d5f0] "m"(b34c80_c13d5f0), [c13ec50] "m"(b34c80_c13ec50), [assert] "m"(b34c80_assert), [exitfn] "m"(b34c80_exitfn), [gtime] "m"(b34c80_gtime), [c8f390] "m"(b34c80_c8f390), [c3b410] "m"(b34c80_c3b410), [c64a80] "m"(b34c80_c64a80), [c13d5b0] "m"(b34c80_c13d5b0), [c342a0] "m"(b34c80_c342a0), [c13d5d0] "m"(b34c80_c13d5d0), [c13d570] "m"(b34c80_c13d570), [c13d590] "m"(b34c80_c13d590), [c1d9260] "m"(b34c80_c1d9260), [c645a0] "m"(b34c80_c645a0), [c31df0] "m"(b34c80_c31df0), [c13ebc0] "m"(b34c80_c13ebc0)
      : "memory");
}
#else
#error "actor_perception_refresh: clang naked draft required"
#endif


/* FUN_000355f0 (0x355f0) — readable C lift (restored pre-naked). */
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

