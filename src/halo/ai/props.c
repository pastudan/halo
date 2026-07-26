/* props.c — AI prop lifecycle and iteration.
 *
 * Corresponds to props.obj (XBE address range ~0x64100–0x64560).
 * Source path confirmed via __FILE__ string:
 *   c:\halo\SOURCE\ai\props.c
 *
 * Subsystem roles:
 *   props_initialize             (0x64100) — allocate "prop" data table via
 *                                            game_state_data_new (768 entries,
 *                                            0x138 bytes each)
 *   props_dispose                (0x64140) — empty stub, no teardown
 *   props_initialize_for_new_map (0x64150) — reset all prop entries
 *   props_dispose_from_old_map   (0x64160) — invalidate prop data table
 *   prop_iterator_new            (0x64540) — initialise a prop iterator
 *                                            for a given actor's prop chain
 *
 * Key globals:
 *   0x5ab23c  data_t *prop_data  — handle to the prop data table,
 *                                  written by game_state_data_new on init.
 *   0x6325a4  data_t *actor_data — shared actor pool (also used by actors.c).
 *
 * Data table parameters (confirmed from binary):
 *   name          = "prop"    (string at 0x25bb30)
 *   maximum_count = 0x300     (768 props)
 *   size          = 0x138     (prop_t struct size)
 *
 * Assert evidence:
 *   display_assert("prop_data", "c:\\halo\\SOURCE\\ai\\props.c", 36, 1)
 *   -> line 36 (0x24) confirms this is the first assert in the function.
 */

#include "../../common.h"

/* prop_data (0x5ab23c) and actor_data (0x6325a4) are declared in the
 * generated decl.h via the kb.json data entries and are visible here
 * through the common.h -> decl.h include chain. No re-declaration needed. */

/* 0x64100 — props_initialize.
 * Allocates the prop data table. Called from ai_initialize.
 * Asserts (halt=true) if allocation fails, then calls system_exit(-1). */
void FUN_00064100(void)
{
  prop_data = game_state_data_new("prop", 0x300, 0x138);
  if (prop_data == 0) {
    display_assert("prop_data", "c:\\halo\\SOURCE\\ai\\props.c", 36, 1);
    system_exit(-1);
  }
}

/* 0x64140 — props_dispose.
 * Empty stub. Binary contains a single RET — no teardown needed. */
void FUN_00064140(void)
{
}

/* 0x64150 — props_initialize_for_new_map.
 * Deletes all prop entries (resets indices, clears active count).
 * Called before loading a new map so the pool is empty. */
void FUN_00064150(void)
{
  data_delete_all(prop_data);
}

/* 0x64160 — props_dispose_from_old_map.
 * Marks the prop data table as invalid (clears the valid signature).
 * Called when unloading a map. */
void FUN_00064160(void)
{
  data_make_invalid(prop_data);
}

/* 0x64400 — prop_unlink_from_actor (@eax=actor_handle, @edi=prop_handle).
 *
 * Splices prop_handle out of the actor's singly-linked prop chain.  The chain
 * is rooted at actor+0x50 and linked through prop+0x8 (the next-handle field
 * confirmed by prop_iterator_next / FUN_00064570).
 *
 * Before unlinking, four NDEBUG assertions verify the prop is not still
 * referenced by any actor look-direction or idle-direction slot:
 *   - actor+0x270        : target prop index
 *   - actor+0x544/54c/550: secondary look direction (type==1 means prop)
 *   - actor+0x55c/56c/570: idle major direction
 *   - actor+0x55f/57c/580: idle minor direction
 *
 * Calling convention: register args loaded by the thunk —
 *   @<eax> = actor_handle, @<edi> = prop_handle.
 * In C this is a normal 2-argument function; the thunk handles register setup.
 *
 * Call-site verification table (from disassembly):
 *   Caller 0x64789 (prop_new_unacknowledged):
 *     MOV EAX,EBX   (EBX = actor_handle from [EBP+0x8]) -> @eax  YES
 *     CALL 0x64400  (EDI = prop_handle held in EDI)       -> @edi  YES
 *   Caller 0x64a80 (prop_detach):
 *     MOV EAX,[EBP+0x8]  actor_handle -> @eax             YES
 *     MOV EDI,[EBP+0xc]  prop_handle  -> @edi             YES
 *
 * Store-offset table (no struct is filled; fields are read for assertions
 * and a singly-linked pointer is updated):
 *   actor+0x50        : prop chain head handle (read & conditionally written)
 *   prop+0x8          : next-handle link (read and used as splice target) */
void FUN_00064400(int actor_handle, int prop_handle) /* @<eax>, @<edi> */
{
  char *actor;
  char *head_prop;
  char *cur_prop;
  int head_handle;
  int next_handle;
  int cur_handle;
  char *prev_next_field; /* pointer to the &prev->next field, for splice */

  actor = (char *)datum_get(actor_data, actor_handle);

  /* Assertion: prop must be the actor's current target prop. */
  if (*(int *)(actor + 0x270) == prop_handle) {
    display_assert("actor->target.target_prop_index != prop_index",
                   "c:\\halo\\SOURCE\\ai\\props.c", 0x19b, 1);
    system_exit(-1);
  }

  /* Assertion: prop must not be the secondary look direction. */
  if ((*(short *)(actor + 0x544) != 0) && (*(short *)(actor + 0x54c) == 1) &&
      (*(int *)(actor + 0x550) == prop_handle)) {
    display_assert(
      "!((actor->control.secondary_look_type != _secondary_look_none) && "
      "(actor->control.secondary_look_direction.type == "
      "_direction_specification_prop) && "
      "(actor->control.secondary_look_direction.prop_index == prop_index))",
      "c:\\halo\\SOURCE\\ai\\props.c", 0x19e, 1);
    system_exit(-1);
  }

  /* Assertion: prop must not be the idle major direction. */
  if ((*(char *)(actor + 0x55c) != 0) && (*(short *)(actor + 0x56c) == 1) &&
      (*(int *)(actor + 0x570) == prop_handle)) {
    display_assert(
      "!((actor->control.idle_major_active) && "
      "(actor->control.idle_major_direction.type == "
      "_direction_specification_prop) && "
      "(actor->control.idle_major_direction.prop_index == prop_index))",
      "c:\\halo\\SOURCE\\ai\\props.c", 0x1a1, 1);
    system_exit(-1);
  }

  /* Assertion: prop must not be the idle minor direction. */
  if ((*(char *)(actor + 0x55f) != 0) && (*(short *)(actor + 0x57c) == 1) &&
      (*(int *)(actor + 0x580) == prop_handle)) {
    display_assert(
      "!((actor->control.idle_minor_active) && "
      "(actor->control.idle_minor_direction.type == "
      "_direction_specification_prop) && "
      "(actor->control.idle_minor_direction.prop_index == prop_index))",
      "c:\\halo\\SOURCE\\ai\\props.c", 0x1a4, 1);
    system_exit(-1);
  }

  /* Splice prop_handle out of the singly-linked chain rooted at actor+0x50.
   * Chain links through prop+0x8 (confirmed from prop_iterator_next). */
  head_handle = *(int *)(actor + 0x50);
  head_prop = (char *)datum_get(prop_data, head_handle);

  if (*(int *)(actor + 0x50) == prop_handle) {
    /* Removing the head: advance head to head->next. */
    *(int *)(actor + 0x50) = *(int *)(head_prop + 8);
    return;
  }

  /* Walk the chain until we find the node whose next == prop_handle. */
  cur_prop = head_prop;
  do {
    prev_next_field = cur_prop + 8; /* &cur_prop->next_handle */
    next_handle = *(int *)(cur_prop + 8);
    cur_prop = (char *)datum_get(prop_data, next_handle);
    cur_handle = *(int *)prev_next_field; /* re-read from the pointer */
  } while (cur_handle != prop_handle);

  /* prev->next = removed->next */
  *(int *)prev_next_field = *(int *)(cur_prop + 8);
}

/* 0x64540 — prop_iterator_new.
 * Initialises a prop iterator for the props associated with a given actor.
 *
 * Reads actor->field_0x50 (the actor's prop chain head handle) and stores it
 * into out[1] (out+4).  The caller (e.g. 0x12350) then passes *out to
 * FUN_00064570 to step through props one at a time.
 *
 * out[0] (out+0) is NOT written here — FUN_00064570 likely owns that slot.
 *
 * Store-offset table (derived from disasm, not decompiler):
 *   out+0: not written by this function
 *   out+4: actor->field_0x50 (prop chain head handle)
 *
 * Call-site verification:
 *   PUSH [EBP+0xc] (actor_handle) -> datum_get arg2
 *   PUSH [0x6325a4] (actor_data)  -> datum_get arg1
 *   MOV EDX,[EAX+0x50]            -> actor->field_0x50
 *   MOV [param_1+4],EDX           -> out[1]
 */
void FUN_00064540(int *out, int actor_handle)
{
  void *actor = datum_get(actor_data, actor_handle);
  out[1] = *(int *)((char *)actor + 0x50);
}

/* 0x64570 — prop_iterator_next.
 * Advances a prop iterator and returns a pointer to the next prop record,
 * or NULL when the chain is exhausted.
 *
 * The iterator is a 2-slot int array (matches the layout used by
 * FUN_00064540 / FUN_00064540):
 *   iter[0] — current prop handle (written here before each datum_get)
 *   iter[1] — next prop handle    (updated to prop->field_0x8)
 *
 * Prop chain link field: prop+0x8 (next handle in singly-linked list).
 *
 * Call-site verification (disasm 0x64570):
 *   MOV ECX,[ESI+0x4]  → handle = iter[1]            YES
 *   MOV [ESI],ECX      → iter[0] = handle (current)  YES
 *   PUSH ECX           → datum_get arg2 (handle)      YES
 *   PUSH EAX ([0x5ab23c] = prop_data) → datum_get arg1  YES
 *   MOV ECX,[EAX+0x8]  → prop->next_handle            YES
 *   MOV [ESI+0x4],ECX  → iter[1] = next               YES
 *
 * Store-offset table (from disasm MOV [ESI+N]):
 *   ESI+0x0 : handle (iter[1] before call — becomes current)
 *   ESI+0x4 : prop->field_0x8 (next handle) */
int FUN_00064570(int *iter)
{
  int handle;
  char *prop;

  handle = iter[1];
  iter[0] = handle;
  if (handle == -1) {
    return 0;
  }
  prop = (char *)datum_get(prop_data, handle);
  iter[1] = *(int *)(prop + 8);
  return (int)prop;
}

/* 0x64a80 — prop_detach.
 * Removes the prop record identified by prop_handle from the actor's prop
 * chain and then frees it from prop_data.
 *
 * Calls FUN_00064400 (@eax=actor_handle, @edi=prop_handle) to splice the
 * prop out of the actor's singly-linked chain, then datum_delete to free
 * the slot.
 *
 * Call-site verification (disasm 0x64a80):
 *   MOV EAX,[EBP+0x8]  → actor_handle → @eax for FUN_00064400  YES
 *   MOV EDI,[EBP+0xc]  → prop_handle  → @edi for FUN_00064400  YES
 *   CALL 0x64400                                                 YES
 *   MOV EAX,[0x5ab23c] → prop_data    → datum_delete arg1       YES
 *   PUSH EDI            → prop_handle  → datum_delete arg2       YES
 *   PUSH EAX            → datum_delete arg1                      YES
 *   CALL 0x1196d0                                                YES
 *   ADD ESP,0x8         → 2-arg cdecl cleanup                   YES */
void prop_iterator_next(int actor_handle, int prop_handle)
{
  FUN_00064400(actor_handle, prop_handle);
  datum_delete(prop_data, prop_handle);
}

/* 0x64ab0 — prop_find_by_object.
 *
 * Searches actor actor_handle's prop chain for a prop that references
 * object_handle (directly via prop+0x18) or references it indirectly via a
 * loaded weapon/parent object (prop+0x1c against the object's model target at
 * object+0x1a8 / object+0x1a4).
 *
 * Skips props whose state field (prop+0x24 as int16) is in the range [0, 1].
 * Only props with prop+0x24 < 0 or prop+0x24 > 1 are eligible.
 *
 * Returns the prop handle (int) of the first matching prop, or -1 if not found.
 *
 * param_1 = actor_handle, param_2 = object_handle (cdecl, no register args).
 *
 * Call-site verification table (disasm 0x64ab0):
 *   object_get_and_verify_type call:
 *     arg1 | PUSH EBX ([EBP+0xc]=object_handle) | object_handle | YES
 *     arg2 | PUSH 0x3                            | 3             | YES
 *   datum_get call:
 *     arg1 | PUSH ECX ([0x6325a4]=actor_data)    | actor_data    | YES
 *     arg2 | PUSH EAX ([EBP+0x8]=actor_handle)   | actor_handle  | YES
 *
 * Store-offset table: no struct filled; read-only traversal. */
int prop_get_active_by_unit_index(int actor_handle, int object_handle)
{
  char *obj;
  int target;
  char *actor;
  int cur_handle;
  int next_handle;
  char *cur_prop;
  short state;

  obj = (char *)object_get_and_verify_type(object_handle, 3);
  target = *(int *)(obj + 0x1a8);
  if (target == -1) {
    target = *(int *)(obj + 0x1a4);
  }

  actor = (char *)datum_get(actor_data, actor_handle);
  cur_handle = *(int *)(actor + 0x50); /* prop chain head */

  for (;;) {
    if (cur_handle == -1) {
      return -1;
    }

    cur_prop = (char *)datum_get(prop_data, cur_handle);
    next_handle = *(int *)(cur_prop + 8);
    state = *(short *)(cur_prop + 0x24);

    /* Skip props in state [0, 1] — only check states < 0 or > 1. */
    if (state >= 0 && state <= 1) {
      cur_handle = next_handle;
      continue;
    }

    /* Direct object reference match. */
    if (*(int *)(cur_prop + 0x18) == object_handle) {
      return cur_handle;
    }

    /* Indirect match via loaded weapon/parent on prop+0x1c. */
    if ((*(char *)(cur_prop + 0x14) != 0) &&
        (*(int *)(cur_prop + 0x1c) != -1) &&
        (*(int *)(cur_prop + 0x1c) == target)) {
      return cur_handle;
    }

    cur_handle = next_handle;
  }
}

/* 0x64ee0 — TIFFClose (libtiff 3.x).
 *
 * NOTE: This function is from c:\halo\SOURCE\bitmaps\libtiff\tif_close.c, NOT
 * from ai\props.c.  It was incorrectly grouped under props.obj in kb.json.
 * It is placed here because it falls between props.obj and tif_dir.obj in the
 * binary address space and has no separate tif_close.c TU in this project.
 * Callers are in tiff_file.c (bitmaps subsystem) — tif_close.c was folded
 * into the surrounding TU at link time.
 *
 * Closes a TIFF file and releases all resources:
 *   1. If tif->tif_flags (tif+0x6, word) != 0, call TIFFFlush / write-back.
 *   2. If tif->tif_cleanup (tif+0x11c, fn ptr) != NULL, call it.
 *   3. Call TIFFFreeDirectory (TIFFFreeDirectory).
 *   4. If tif->tif_rawdata (tif+0x12c) != NULL and flag bit 0x40 set (tif+0xa),
 *      free it.
 *   5. __close(tif->tif_fd)  — tif+0x4 as int16 sign-extended.
 *   6. free(tif) itself.
 *
 * Struct offsets (derived from disassembly — no TIFF typedef in this project):
 *   tif+0x4  : tif_fd       (int16)   — file descriptor
 *   tif+0x6  : tif_flags    (int16)   — != 0 means flush needed
 *   tif+0xa  : flags byte — bit 0x40 = TIFF_MYBUFFER (owns raw data buffer)
 *   tif+0x11c: tif_cleanup  (fn ptr)  — called with tif as argument
 *   tif+0x12c: tif_rawdata  (void *)  — raw data buffer, freed if owned
 *
 * Call-site verification table:
 *   FUN_0006a260 call (TIFFFlush):
 *     arg1 | PUSH ESI (tif ptr) | tif | YES
 *   indirect call [ESI+0x11c]:
 *     EAX = [ESI+0x11c] (fn ptr, NULL-guarded)
 *     arg1 | PUSH ESI | tif | YES (CALL EAX)
 *   TIFFFreeDirectory call (TIFFFreeDirectory):
 *     arg1 | PUSH ESI | tif | YES
 *   debug_free calls:
 *     raw data: PUSH [ESI+0x12c], PUSH file_str, PUSH 0x37
 *     tif self: PUSH ESI, PUSH file_str, PUSH 0x3d */
void FUN_00064ee0(int tif_)
{
  char *tif = (char *)tif_;
  void (*cleanup_fn)(int);
  void *rawdata;

  /* Flush / write-back if flags indicate pending output. */
  if (*(short *)(tif + 0x6) != 0) {
    FUN_0006a260(tif_);
  }

  /* Call per-codec cleanup callback if registered. */
  cleanup_fn = *(void (**)(int))(tif + 0x11c);
  if (cleanup_fn != (void (*)(int))0) {
    cleanup_fn(tif_);
  }

  /* Free directory data. */
  TIFFFreeDirectory(tif_);

  /* Free raw data buffer if owned by this TIFF object. */
  rawdata = *(void **)(tif + 0x12c);
  if (rawdata != 0 && (*(unsigned char *)(tif + 0xa) & 0x40) != 0) {
    debug_free(rawdata, "c:\\halo\\SOURCE\\bitmaps\\libtiff\\tif_close.c",
               0x37);
  }

  /* Close the underlying file descriptor. */
  __close((int)(*(short *)(tif + 0x4)));

  /* Free the TIFF object itself. */
  debug_free(tif, "c:\\halo\\SOURCE\\bitmaps\\libtiff\\tif_close.c", 0x3d);
}
/* --- props.obj batch drafts (2026-07-26) --- */

/* 0x63e30 — project a probe point onto a structure surface. */
int FUN_00063e30(int scenario, unsigned char bsp_idx, float *origin,
                 int surface_index, float *out_point)
{
  char result[0x1c];
  int end_surface;

  if (surface_index == -1)
    return -1;

  FUN_000639e0(scenario, bsp_idx, origin, surface_index, out_point, -1, result);
  end_surface = *(int *)(result + 0x10);
  out_point[0] = *(float *)(result + 4);
  out_point[1] = *(float *)(result + 8);
  if (end_surface == -1)
    return surface_index;
  return end_surface;
}

/* 0x63e90 — test line-of-sight / path visibility between two 2D points. */
char FUN_00063e90(int scenario, unsigned char bsp_idx, float *origin,
                  int node_handle, float *target, int flags, float scale,
                  int param_8, unsigned int *result)
{
  float dir[2];
  float dist_sq;
  float inv_dist;
  float pt_fwd[2];
  float pt_back[2];
  float pt_tgt_fwd[2];
  float pt_tgt_back[2];
  int surf_fwd;
  int surf_back;
  int surf_tgt_fwd;
  int surf_tgt_back;
  char buf_fwd[0x4c];
  char buf_back[0x68];
  char pick_fwd;
  char pick_back;
  float best_dist;
  char *best_buf;

  dir[0] = origin[0] - target[0];
  dir[1] = origin[1] - target[1];
  dist_sq = dir[0] * dir[0] + dir[1] * dir[1];
  if (fabs(dist_sq) < *(double *)0x2533d0) {
    inv_dist = 1.0f;
    dir[0] = 0.0f;
    dir[1] = 0.0f;
  } else {
    inv_dist = 1.0f / sqrtf(dist_sq);
    dir[0] *= inv_dist;
    dir[1] *= inv_dist;
  }
  if (*(float *)0x2533c0 < dist_sq)
    return 0;

  pt_fwd[0] = dir[0] * scale + origin[0];
  pt_fwd[1] = dir[1] * scale + origin[1];
  pt_back[0] = -dir[0] * scale + origin[0];
  pt_back[1] = -dir[1] * scale + origin[1];
  pt_tgt_fwd[0] = dir[0] * scale + target[0];
  pt_tgt_fwd[1] = dir[1] * scale + target[1];
  pt_tgt_back[0] = -dir[0] * scale + target[0];
  pt_tgt_back[1] = -dir[1] * scale + target[1];

  surf_fwd = FUN_00063e30(scenario, bsp_idx, origin, node_handle, pt_fwd);
  surf_back = FUN_00063e30(scenario, bsp_idx, origin, node_handle, pt_back);
  surf_tgt_fwd =
      FUN_00063e30(scenario, bsp_idx, target, flags, pt_tgt_fwd);
  surf_tgt_back =
      FUN_00063e30(scenario, bsp_idx, target, flags, pt_tgt_back);

  csmemset(buf_fwd, 0, sizeof(buf_fwd));
  csmemset(buf_back, 0, sizeof(buf_back));
  pick_fwd = 0;
  pick_back = 0;

  if (surf_fwd != -1) {
    if (FUN_000639e0(scenario, bsp_idx, origin, surf_fwd, pt_fwd, surf_back,
                     buf_fwd + 0x3c) &&
        *(int *)(buf_fwd + 0x24) != -1 && !(param_8 & 1)) {
      if (!FUN_000639e0(scenario, bsp_idx, pt_fwd, *(int *)(buf_fwd + 0x24),
                        target, flags, buf_fwd))
        buf_fwd[0] = 0;
    } else {
      buf_fwd[0] = 0;
    }
    if (surf_back != -1 &&
        FUN_000639e0(scenario, bsp_idx, pt_fwd, surf_back, target, flags,
                     buf_fwd + 0x08) &&
        *(int *)(buf_fwd + 0x1c) != -1 && !(param_8 & 1)) {
      pick_fwd = 1;
    }
  }

  if (surf_tgt_back != -1) {
    if (FUN_000639e0(scenario, bsp_idx, target, surf_tgt_back, pt_tgt_back,
                     surf_tgt_fwd, buf_back + 0x58) &&
        *(int *)(buf_back + 0x40) != -1 && !(param_8 & 1)) {
      if (!FUN_000639e0(scenario, bsp_idx, pt_tgt_back,
                        *(int *)(buf_back + 0x40), origin, node_handle,
                        buf_back + 0x1c))
        buf_back[0x20] = 0;
    } else {
      buf_back[0x20] = 0;
    }
    if (surf_tgt_fwd != -1 &&
        FUN_000639e0(scenario, bsp_idx, pt_tgt_back, surf_tgt_fwd, origin,
                     node_handle, buf_back + 0x24) &&
        *(int *)(buf_back + 0x38) != -1 && !(param_8 & 1)) {
      pick_back = 1;
    }
  }

  if (buf_fwd[0] && pick_back && pick_fwd) {
    if (*(float *)(buf_fwd + 0x2c) >= *(float *)(buf_back + 0x48))
      best_buf = buf_fwd;
    else
      best_buf = buf_back + 0x20;
  } else if (buf_fwd[0] && pick_fwd) {
    best_buf = buf_fwd;
  } else if (pick_back) {
    best_buf = buf_back + 0x20;
  } else {
    return 0;
  }

  best_dist = (target[0] - *(float *)(best_buf + 4)) *
                  (target[0] - *(float *)(best_buf + 4)) +
              (target[1] - *(float *)(best_buf + 8)) *
                  (target[1] - *(float *)(best_buf + 8));
  if (scale * scale < best_dist)
    return 0;

  csmemcpy(result, best_buf, 0x1c);
  return 1;
}

/* 0x64170 — link a new prop into an actor's prop chain. */
void prop_add(int actor_handle, int prop_index, int unit_handle)
{
  char *actor;
  char *prop;
  char *unit;
  void *unit_tag;
  char is_biped_flag;
  char orphan_flag;
  int16_t status_word;
  int now;

  if (prop_index == -1) {
    now = game_time_get();
    if (*(int *)0x2c97b8 != -1 && now < *(int *)0x2c97b8 + 900) {
      error(2, (char *)0x0025f1a8);
    }
    *(int *)0x2c97b8 = now;
    return;
  }

  actor = (char *)datum_get(actor_data, actor_handle);
  prop = (char *)datum_get(prop_data, prop_index);
  *(int *)(prop + 4) = actor_handle;
  *(int16_t *)(prop + 0x66) = -1;
  *(int16_t *)(prop + 0x6c) = -1;
  *(int *)(prop + 0x18) = unit_handle;
  *(char *)(prop + 0x74) = 0;
  *(int *)(prop + 0x70) = 0;
  *(int16_t *)(prop + 0xb0) = -1;
  *(char *)(prop + 0xb8) = 0;
  *(int *)(prop + 0xb4) = -1;
  *(int *)(prop + 0x7c) = -1;
  *(int *)(prop + 0x8c) = -1;
  *(char *)(prop + 0x4e) = 0;
  *(int *)(prop + 0x1c) = -1;
  *(int *)(prop + 0xc) = -1;
  *(int16_t *)(prop + 0x6a) = 0;
  *(int *)(prop + 0xa0) = -1;

  if (unit_handle != -1) {
    unit = (char *)object_get_and_verify_type(unit_handle, 3);
    unit_tag = tag_get('unit', *(int *)unit);
    if (unit_handle == *(int *)(actor + 0x18)) {
      display_assert("unit_index != actor->meta.unit_index",
                     "c:\\halo\\SOURCE\\ai\\props.c", 0xe8, 1);
      system_exit(-1);
    }
    if (*(int16_t *)(unit + 0x64) != 0) {
      display_assert("prop_unit->object.type == _object_type_biped",
                     "c:\\halo\\SOURCE\\ai\\props.c", 0xe9, 1);
      system_exit(-1);
    }
    *(int16_t *)(prop + 0x12) = *(int16_t *)(unit + 0x68);
    *(char *)(prop + 0x60) = game_allegiance_get_team_is_friendly(
        *(int16_t *)(prop + 0x12), *(int16_t *)(actor + 0x3e));
    *(char *)(prop + 0x61) =
        game_team_is_ally(*(int16_t *)(prop + 0x12),
                          *(int16_t *)(actor + 0x3e));
    *(char *)(prop + 0x62) = game_team_ally_status_changed(
        *(int16_t *)(prop + 0x12), *(int16_t *)(actor + 0x3e));
    is_biped_flag = (char)((*(char *)(unit + 0xb6) >> 2) & 1);
    *(char *)(prop + 0x127) = is_biped_flag;
    *(int *)(prop + 0x20) = *(int *)(unit_tag + 0x284);
    if (is_biped_flag != 0 && *(int16_t *)(unit + 0x3d0) == 0)
      orphan_flag = 1;
    else
      orphan_flag = 0;
    *(char *)(prop + 0x128) = orphan_flag;
    *(int16_t *)(prop + 0x76) = (int16_t)(orphan_flag ? 0x3e8 : 0);
    *(char *)(prop + 0x12e) = (*(int *)(unit + 0x70) != -1);
    if (*(int *)(unit + 0x1a8) != -1) {
      *(char *)(prop + 0x14) = 1;
      *(int *)(prop + 0x1c) = *(int *)(unit + 0x1a8);
      *(int *)(prop + 0x28) = game_time_get();
    } else {
      *(int *)(prop + 0x1c) = *(int *)(unit + 0x1a4);
    }
    if (*(char *)(prop + 0x12e) != 0)
      status_word = 6;
    else if (*(int *)(prop + 0x1c) != unit_handle) {
      char *owner;

      owner = (char *)datum_get(*(void **)0x6325a4, *(int *)(prop + 0x1c));
      status_word = *(int16_t *)(owner + 4);
    } else {
      status_word = -1;
    }
    *(int16_t *)(prop + 0x10) = status_word;
  }

  *(int *)(prop + 8) = *(int *)(actor + 0x50);
  *(int *)(actor + 0x50) = prop_index;
}

/* 0x643d0 */
void FUN_000643d0(int actor_handle)
{
  int prop_index;

  prop_index = data_new_at_index(prop_data);
  prop_add(actor_handle, prop_index, -1);
}

/* 0x645a0 */
int prop_new_unacknowledged(int actor_handle, int unit_handle, char friendly)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  (void)actor_handle;
  (void)unit_handle;
  (void)friendly;

  datum_get((void *)0, 0);
  datum_get((void *)0, 0);
  /* cmp (int16_t)eax, 4 -> jl 0x64610 */
  /* cmp (int16_t)eax, 5 -> jle 0x645e0 */
  /* relift: cmp dword ptr [esi + 0xc], -1 -> jne 0x645e0 */
  actor_perception_desire_prop();
  /* test (char)eax, (char)eax -> jne 0x6469d */
  /* relift: cmp byte ptr [esi + 0x60], (char)eax -> jne 0x645e0 */
  /* cmp edi, -1 -> jne 0x6471e */
  /* cmp edi, -1 -> je 0x64709 */
  /* relift: cmp word ptr [ebp - 8], (int16_t)edx -> jl 0x64709 */
  /* cmp edi, -1 -> jne 0x6471e */
  data_new_at_index((void *)0);
  datum_get((void *)0, 0);
  /* cmp eax, ebx -> je 0x6477f */
  display_assert((void *)0x00255f50, (void *)0x0025f134, 158, 0);
  system_exit(0);
  /* cmp eax, ebx -> je 0x6477f */
  display_assert((void *)0x0025f46c, (void *)0x0025f134, 159, 0);
  system_exit(0);
  FUN_0003b410(0, 0, 0);
  FUN_00064400(0, 0);
  csmemset((void *)0, 0, 312);
  prop_add(0, 0, -1);

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
  return -1;
}

/* 0x647c0 */
void FUN_000647c0(void)
{
  datum_get((void *)0, 0);
  datum_get((void *)0, 0);
  csmemcpy((void *)0, (void *)0, 312);
}

/* 0x648a0 */
void prop_orphan_transition(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  data_new_at_index((void *)0);
  prop_add(0, 0, -1);
  /* cmp esi, -1 -> je 0x6495b */
  datum_get((void *)0, 0);
  datum_get((void *)0, 0);
  /* cmp ecx, eax -> je 0x6491b */
  display_assert((void *)0x0025f4b4, (void *)0x0025f134, 341, 0);
  system_exit(0);
  /* relift: cmp dword ptr [edi + 0xc], -1 -> je 0x64941 */
  display_assert((void *)0x0025f48c, (void *)0x0025f134, 342, 0);
  system_exit(0);
  FUN_000647c0();

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x64970 */
void prop_orphan_from_friend(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  data_new_at_index((void *)0);
  prop_add(0, 0, -1);
  /* cmp esi, -1 -> je 0x64a54 */
  datum_get((void *)0, 0);
  datum_get((void *)0, 0);
  datum_get((void *)0, 0);
  /* cmp eax, ebx -> je 0x649fd */
  display_assert((void *)0x0025f4b4, (void *)0x0025f134, 365, 0);
  system_exit(0);
  /* relift: cmp dword ptr [edi + 0xc], -1 -> je 0x64a23 */
  display_assert((void *)0x0025f48c, (void *)0x0025f134, 366, 0);
  system_exit(0);
  FUN_000647c0();
  /* cmp (int16_t)eax, 5 -> jg 0x64a54 */

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x64a60 */
void prop_orphan_update_information(void)
{
  FUN_000647c0();
}

/* 0x64b40 — create/refresh a prop acknowledgement for a perceived unit. */
int FUN_00064b40(int actor_handle, int unit_handle, char create_if_needed,
                 char refresh_flag)
{
  char *actor;
  char *unit;
  char *prop;
  int owner_handle;
  int prop_handle;
  char friendly;
  char ack;

  prop_handle = -1;
  if (unit_handle == -1)
    return -1;

  actor = (char *)datum_get(actor_data, actor_handle);
  unit = (char *)object_get_and_verify_type(unit_handle, 3);
  if (*(int *)(unit + 0x1a8) != -1)
    owner_handle = *(int *)(unit + 0x1a8);
  else
    owner_handle = *(int *)(unit + 0x1a4);

  if (*(int16_t *)(unit + 0x64) != 0)
    return -1;
  if (owner_handle == actor_handle)
    return -1;

  prop_handle = *(int *)(actor + 0x50);
  while (prop_handle != -1) {
    prop = (char *)datum_get(prop_data, prop_handle);
    if (*(int *)(prop + 0x18) == unit_handle)
      goto found_prop;
    if (*(char *)(prop + 0x14) == 0) {
      prop_handle = *(int *)(prop + 8);
      continue;
    }
    if (*(int *)(prop + 0x1c) == -1) {
      prop_handle = *(int *)(prop + 8);
      continue;
    }
    if (*(int *)(prop + 0x1c) != owner_handle) {
      prop_handle = *(int *)(prop + 8);
      continue;
    }
  found_prop:
    if (*(int *)(prop + 0xc) != -1)
      prop_handle = *(int *)(prop + 0xc);
    if (prop_handle != -1)
      return prop_handle;
    break;
  }

  if (create_if_needed == 0)
    return -1;
  if (*(char *)(actor + 8) == 0)
    return -1;

  friendly = game_allegiance_get_team_is_friendly(*(int16_t *)(unit + 0x68),
                                                  *(int16_t *)(actor + 0x3e));
  prop_handle =
      prop_new_unacknowledged(actor_handle, unit_handle, friendly);
  if (prop_handle == -1)
    return -1;

  prop = (char *)datum_get(prop_data, prop_handle);
  prop_position_refresh();
  *(int16_t *)(prop + 0x6a) = 0x1e;
  *(char *)(prop + 0x126) = 1;
  if (refresh_flag == 0)
    return prop_handle;

  prop_status_refresh();
  if (*(int16_t *)(prop + 0x30) < 2)
    return prop_handle;

  actor_expected_acknowledgement();
  actor_perception_acknowledge(actor_handle, prop_handle, 0, 0);
  ack = 0;
  *(int16_t *)(prop + 0x24) = 3;
  actor_perception_acknowledge(actor_handle, prop_handle, ack, 0);
  return prop_handle;
}

/* 0x64cd0 — read a typed field from a prop structure (tag dispatch). */
int FUN_00064cd0(char *prop, int tag, void *out)
{
  switch (tag) {
  case 0xfe:
    *(int16_t *)out = *(int16_t *)(prop + 0x34);
    return 1;
  case 0xff:
    *(int16_t *)out = *(int16_t *)(prop + 0x36);
    return 1;
  case 0x100:
    *(int16_t *)out = *(int16_t *)(prop + 0x3e);
    return 1;
  case 0x101:
    *(int16_t *)out = *(int16_t *)(prop + 0x40);
    return 1;
  case 0x102:
    *(int16_t *)out = *(int16_t *)(prop + 0x42);
    return 1;
  case 0x103:
    *(int16_t *)out = *(int16_t *)(prop + 0x44);
    return 1;
  case 0x104:
    *(int *)out = *(int *)(prop + 0x48);
    return 1;
  case 0x105:
    *(int16_t *)out = *(int16_t *)(prop + 0x4c);
    return 1;
  case 0x119:
    *(int16_t *)out = *(int16_t *)(prop + 0x50);
    return 1;
  case 0x11c:
    *(int16_t *)out = *(int16_t *)(prop + 0x5e);
    return 1;
  case 0x125:
    *(int16_t *)out = *(int16_t *)(prop + 0x5c);
    return 1;
  case 0x128:
    *(int *)out = *(int *)(prop + 0x6c);
    return 1;
  case 0x13d:
    *(int16_t *)out = *(int16_t *)(prop + 0x46);
    return 1;
  case 0x80e4:
    *(int16_t *)out = *(int16_t *)(prop + 0x38) - 1;
    return 1;
  case 0x80e5:
    *(int16_t *)out = *(int16_t *)(prop + 0x24);
    return 1;
  case 0x80e6:
    *(int *)out = *(int *)(prop + 0x30);
    return 1;
  default:
    return 0;
  }
}

/* 0x64ec0 — wrapper around FUN_00064cd0. */
int FUN_00064ec0(char *prop, int tag, void *out)
{
  return FUN_00064cd0(prop, tag, out);
}

/* 0x64f50 */
void FUN_00064f50(void)
{
  int eax = 0;
  int ecx = 0;

  FUN_001e65eb();
  /* relift: cmp dword ptr [eax + 4], ecx -> je 0x64f96 */
  /* cmp eax, 0x2c99c4 -> jb 0x64f85 */

  (void)eax;
  (void)ecx;
}

/* 0x64fa0 */
void FUN_00064fa0(void)
{
  int eax = 0;
  int ecx = 0;

  /* relift: cmp dword ptr [eax + 4], ecx -> je 0x64fc1 */
  /* cmp eax, 0x2c99c4 -> jb 0x64fb0 */
  FUN_00068a30(0, (void *)0x0025f530);

  (void)eax;
  (void)ecx;
}

/* 0x64fe0 */
void FUN_00064fe0(void)
{
  int eax = 0;
  int ecx = 0;

  /* relift: cmp dword ptr [eax + 4], ecx -> je 0x65001 */
  /* cmp eax, 0x2c99c4 -> jb 0x64ff0 */
  FUN_00068a30(0, (void *)0x0025f530);

  (void)eax;
  (void)ecx;
}

/* 0x65020 */
void FUN_00065020(void)
{
  int eax = 0;
  int ecx = 0;

  /* relift: cmp dword ptr [eax + 4], ecx -> je 0x65041 */
  /* cmp eax, 0x2c99c4 -> jb 0x65030 */
  FUN_00068a30(0, (void *)0x0025f530);

  (void)eax;
  (void)ecx;
}

/* 0x65060 */
void FUN_00065060(void)
{
  int eax = 0;
  int ecx = 0;

  /* relift: cmp dword ptr [eax + 4], ecx -> je 0x65081 */
  /* cmp eax, 0x2c99c4 -> jb 0x65070 */
  FUN_00068a30(0, (void *)0x0025f530);

  (void)eax;
  (void)ecx;
}

/* 0x650a0 */
void FUN_000650a0(void)
{
  int eax = 0;
  int ecx = 0;

  /* relift: cmp dword ptr [eax + 4], ecx -> je 0x650c1 */
  /* cmp eax, 0x2c99c4 -> jb 0x650b0 */
  FUN_00068a30(0, (void *)0x0025f570);

  (void)eax;
  (void)ecx;
}

/* 0x650e0 */
void FUN_000650e0(void)
{
  int eax = 0;
  int ecx = 0;

  /* relift: cmp dword ptr [eax + 4], ecx -> je 0x65101 */
  /* cmp eax, 0x2c99c4 -> jb 0x650f0 */
  FUN_00068a30(0, (void *)0x0025f570);

  (void)eax;
  (void)ecx;
}

/* 0x65120 */
void FUN_00065120(void)
{
  int eax = 0;
  int ecx = 0;

  /* relift: cmp dword ptr [eax + 4], ecx -> je 0x65141 */
  /* cmp eax, 0x2c99c4 -> jb 0x65130 */
  FUN_00068a30(0, (void *)0x0025f570);

  (void)eax;
  (void)ecx;
}

/* 0x65160 */
void FUN_00065160(void)
{
  int eax = 0;
  int ecx = 0;

  /* relift: cmp dword ptr [eax + 4], ecx -> je 0x65181 */
  /* cmp eax, 0x2c99c4 -> jb 0x65170 */
  FUN_00068a30(0, (void *)0x0025f570);

  (void)eax;
  (void)ecx;
}

/* 0x651a0 */
void FUN_000651a0(void)
{
  int eax = 0;
  int ecx = 0;

  /* relift: cmp dword ptr [ecx + 4], eax -> je 0x651d9 */
  /* cmp ecx, 0x2c99c4 -> jb 0x651b0 */
  FUN_00068a30(0, (void *)0x0025f594);

  (void)eax;
  (void)ecx;
}

/* 0x65250 */
void FUN_00065250(void)
{
  int eax = 0;
  int ebx = 0;

  /* test eax, eax -> je 0x6526c */
  debug_free((void *)0, (void *)0x0025f5c4, 69);
  /* test ebx, ebx -> je 0x6529e */
  csstrlen((char *)0);
  debug_malloc(0, 0, (char *)0, 0);
  csmemcpy((void *)0, (void *)0, 0);

  (void)eax;
  (void)ebx;
}

/* 0x652a0 */
void FUN_000652a0(void)
{
  int eax = 0;
  int ebx = 0;

  /* test eax, eax -> je 0x652bf */
  debug_free((void *)0, (void *)0x0025f5c4, 81);
  /* test ebx, ebx -> je 0x652ec */
  debug_malloc(0, 0, (void *)0x0025f5c4, 83);
  csmemcpy((void *)0, (void *)0, 0);

  (void)eax;
  (void)ebx;
}

/* 0x652f0 */
void FUN_000652f0(void)
{
  int eax = 0;
  int edx = 0;
  int edi = 0;

  /* cmp eax, 0x55 -> ja 0x657e3 */
  /* cmp edx, edi -> je 0x65858 */
  /* test eax, eax -> je 0x653ab */
  FUN_000651a0();
  /* cmp edi, 2 -> je 0x65403 */
  /* cmp edi, 1 -> jne 0x65894 */
  FUN_00065250();
  FUN_00065250();
  FUN_00065250();
  FUN_00065250();
  FUN_00065250();
  FUN_00065250();
  FUN_00065250();
  FUN_00065250();
  /* cmp edi, 1 -> jl 0x654ea */
  /* cmp edi, 8 -> jg 0x654ea */
  TIFFDefaultDirectory();
  FUN_0006f9d0();
  /* test edi, edi -> je 0x65894 */
  /* cmp edi, 4 -> jle 0x65544 */
  FUN_00068a30(0, (void *)0x0025f634);
  /* test edi, edi -> je 0x65894 */
  /* relift: test byte ptr [eax + 0x14], 2 -> jne 0x65858 */
  /* cmp edi, 1 -> je 0x655d8 */
  /* cmp edi, 2 -> jne 0x65894 */
  FUN_00065250();
  /* cmp edi, 1 -> jl 0x65894 */
  /* cmp edi, 3 -> jg 0x65894 */
  FUN_000652a0();
  FUN_000652a0();
  FUN_000652a0();

  (void)eax;
  (void)edx;
  (void)edi;
}
