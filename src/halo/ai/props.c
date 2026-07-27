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

/* FUN_00063e30 (0x63e30) — readable C lift. */
int FUN_00063e30(int scenario, unsigned char bsp_idx, float *origin, int surface_index, float *out_point)
{
  char result[0x1c];
  int rc;

  if (surface_index == -1) {
    return -1;
  }
  FUN_000639e0(scenario, bsp_idx, origin, surface_index, out_point, -1, result);
  out_point[0] = *(float *)(result + 4);
  out_point[1] = *(float *)(result + 8);
  rc = *(int *)(result + 0x10);
  if (rc == -1) {
    return surface_index;
  }
  return rc;
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


/* FUN_000643d0 (0x643d0) — readable C lift. */
int FUN_000643d0(int actor_handle)
{
  int idx = data_new_at_index(*(void **)0x5ab23c);
  prop_add(actor_handle, idx, -1);
  return idx;
}

/* prop_new_unacknowledged (0x645a0) — readable C lift (restored pre-naked). */
int prop_new_unacknowledged(int actor_handle, int unit_handle, char friendly)
{
  char *actor;
  char *prop;
  int prop_handle;
  int best_handle;
  int alt_handle;
  float best_vis;
  float alt_vis;
  int match_count;
  char out_flag;
  int16_t threshold;
  float vis;
  int16_t status;

  best_handle = -1;
  alt_handle = -1;
  best_vis = 3.4028235e38f;
  alt_vis = 3.4028235e38f;
  match_count = 0;

  actor = (char *)datum_get(actor_data, actor_handle);
  prop_handle = *(int *)(actor + 0x50);
  while (prop_handle != -1) {
    prop = (char *)datum_get(prop_data, prop_handle);
    status = *(int16_t *)(prop + 0x24);
    if (status >= 4 && status <= 5 && *(int *)(prop + 0xc) == -1) {
      vis = *(float *)(prop + 0x11c);
      out_flag = 0;
      if (actor_perception_desire_prop(
              actor_handle, -1, *(int *)(prop + 0x18), *(int *)(prop + 0x1c),
              *(char *)(prop + 0x63), *(char *)(prop + 0x12e),
              *(char *)(prop + 0x60), *(char *)(prop + 0x127),
              *(int16_t *)(prop + 0x76), *(int16_t *)(prop + 0x6a), vis,
              *(int *)(prop + 0x20), &out_flag)) {
        if (*(char *)(prop + 0x60) != friendly) {
          prop_handle = *(int *)(prop + 8);
          continue;
        }
        match_count++;
        if (out_flag == 0) {
          prop_handle = *(int *)(prop + 8);
          continue;
        }
        if (*(float *)(prop + 0x11c) <= alt_vis) {
          alt_handle = prop_handle;
          alt_vis = *(float *)(prop + 0x11c);
        }
      } else if (*(float *)(prop + 0x11c) <= best_vis) {
        best_handle = prop_handle;
        best_vis = *(float *)(prop + 0x11c);
      }
    }
    prop_handle = *(int *)(prop + 8);
  }

  prop_handle = best_handle;
  if (prop_handle == -1) {
    prop_handle = alt_handle;
    if (prop_handle == -1)
      goto allocate_new;
    threshold = (int16_t)(friendly ? 6 : 4);
    if (match_count < threshold)
      goto allocate_new;
    if (prop_handle == -1)
      goto allocate_new;
  }

  prop = (char *)datum_get(prop_data, prop_handle);
  if (*(int *)(prop + 0xc) != -1) {
    display_assert("prop->parent_prop_index == NONE",
                   "c:\\halo\\SOURCE\\ai\\props.c", 0x9e, 1);
    system_exit(-1);
  }
  if (*(int *)(prop + 0xc) != -1) {
    display_assert("prop->parent_prop_index == NONE",
                   "c:\\halo\\SOURCE\\ai\\props.c", 0x9f, 1);
    system_exit(-1);
  }
  FUN_0003b410(actor_handle, prop_handle, -1);
  FUN_00064400(actor_handle, prop_handle);
  {
    int16_t saved_type = *(int16_t *)prop;
    csmemset(prop, 0, 0x138);
    *(int16_t *)prop = saved_type;
  }
  prop_add(actor_handle, prop_handle, unit_handle);
  return prop_handle;

allocate_new:
  prop_handle = data_new_at_index(prop_data);
  prop_add(actor_handle, prop_handle, unit_handle);
  return prop_handle;
}


/* FUN_000647c0 (0x647c0) — readable C lift.
 * Stack: unused @ [ebp+8], dest_prop @ [ebp+0xc]; src_prop in EAX. */
void FUN_000647c0(int unused, int dest_prop, int src_prop)
{
  char *from;
  char *to;
  int x, y, z;
  short header;
  int *p;

  (void)unused;
  from = (char *)datum_get(*(data_t **)0x5ab23c, src_prop);
  to = (char *)datum_get(*(data_t **)0x5ab23c, dest_prop);

  x = *(int *)(to + 4);
  y = *(int *)(to + 8);
  z = *(int *)(to + 0xc);
  header = *(short *)to;

  csmemcpy(to, from, 0x138);

  *(int *)(to + 0xc) = z;
  *(int *)(to + 4) = x;
  *(short *)to = header;
  *(int *)(to + 8) = y;
  *(short *)(to + 0x24) = 4;
  *(short *)(to + 0x3a) = 0x384;
  *(short *)(to + 0x3c) = 0;
  to[0xb9] = 0;
  to[0xba] = 0;
  to[0xbb] = 0;
  *(float *)(to + 0x40) = *(float *)(to + 0xbc) - *(float *)(to + 0x80);
  *(float *)(to + 0x44) = *(float *)(to + 0xc0) - *(float *)(to + 0x84);
  *(float *)(to + 0x48) = *(float *)(to + 0xc4) - *(float *)(to + 0x88);

  p = *(int **)0x31fc38;
  *(int *)(to + 0xd4) = p[0];
  *(int *)(to + 0xd8) = p[1];
  *(int *)(to + 0xdc) = p[2];
  to[0x123] = 0;
}

/* prop_orphan_transition (0x648a0) — readable C lift. */
int prop_orphan_transition(int actor_handle, int parent_prop)
{
  int new_prop;
  char *parent;
  char *child;

  new_prop = data_new_at_index(*(data_t **)0x5ab23c);
  prop_add(actor_handle, new_prop, -1);
  if (new_prop == -1)
    return new_prop;

  parent = (char *)datum_get(*(data_t **)0x5ab23c, parent_prop);
  child = (char *)datum_get(*(data_t **)0x5ab23c, new_prop);

  if (*(int *)(parent + 4) != actor_handle) {
    display_assert((const char *)0x25f4b4, (const char *)0x25f134, 0x155, true);
    system_exit(-1);
  }
  if (*(int *)(parent + 0xc) != -1) {
    display_assert((const char *)0x25f48c, (const char *)0x25f134, 0x156, true);
    system_exit(-1);
  }

  FUN_000647c0(actor_handle, new_prop, parent_prop);
  *(int *)(parent + 0xc) = new_prop;
  *(int *)(child + 0xc) = parent_prop;
  return new_prop;
}


/* prop_orphan_from_friend (0x64970) — readable C lift. */
int prop_orphan_from_friend(int actor_handle, int parent_prop, int source_prop)
{
  int new_prop;
  char *parent;
  char *child;
  char *source;
  short status;

  new_prop = data_new_at_index(*(data_t **)0x5ab23c);
  prop_add(actor_handle, new_prop, -1);
  if (new_prop == -1)
    return new_prop;

  parent = (char *)datum_get(*(data_t **)0x5ab23c, parent_prop);
  child = (char *)datum_get(*(data_t **)0x5ab23c, new_prop);
  source = (char *)datum_get(*(data_t **)0x5ab23c, source_prop);

  if (*(int *)(parent + 4) != actor_handle) {
    display_assert((const char *)0x25f4b4, (const char *)0x25f134, 0x16d, true);
    system_exit(-1);
  }
  if (*(int *)(parent + 0xc) != -1) {
    display_assert((const char *)0x25f48c, (const char *)0x25f134, 0x16e, true);
    system_exit(-1);
  }

  FUN_000647c0(actor_handle, new_prop, source_prop);
  *(int *)(parent + 0xc) = new_prop;
  *(int *)(child + 0xc) = parent_prop;
  status = *(short *)(source + 0x24);
  if (status >= 4 && status <= 5)
    *(short *)(child + 0x24) = status;
  return new_prop;
}


/* prop_orphan_update_information (0x64a60) — readable C lift.
 * Asm: push parent, push actor, eax=src; call FUN_000647c0. */
void prop_orphan_update_information(int actor_handle, int parent_prop, int src_prop)
{
  FUN_000647c0(actor_handle, parent_prop, src_prop);
}

/* FUN_00064b40 (0x64b40) — XBE naked draft (batch 83). */
#if defined(__clang__)
static void *(*const b64b40_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b64b40_get)(int, int) = object_get_and_verify_type;
static bool (*const b64b40_ca7a30)(int16_t team_a, int16_t team_b) = game_allegiance_get_team_is_friendly;
static int (*const b64b40_c645a0)(int actor_handle, int unit_handle, char friendly) = prop_new_unacknowledged;
static void (*const b64b40_c31df0)(int actor_handle, int prop_handle, float *out_pos, char refresh_flag, char swarm_refresh) = prop_position_refresh;
static void (*const b64b40_c33440)(int actor_handle, int prop_handle, float *out_pos) = prop_status_refresh;
static char (*const b64b40_c32940)(int actor_handle, int prop_handle) = (void *)actor_expected_acknowledgement;
static void (*const b64b40_c2f2b0)(int actor_handle, int prop_handle, int param_3, char param_4) = actor_perception_acknowledge;

__attribute__((naked, noinline))
int FUN_00064b40(int actor_handle __attribute__((unused)), int unit_handle __attribute__((unused)), char create_if_needed __attribute__((unused)), char refresh_flag __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x4c, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_00064b40_8\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl 0x1a8(%%ecx), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "je .LFUN_00064b40_1\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00064b40_2\n\t"
      ".LFUN_00064b40_1:\n\t"
      "movl 0x1a4(%%ecx), %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".LFUN_00064b40_2:\n\t"
      "cmpw $0, 0x64(%%ecx)\n\t"
      "jne .LFUN_00064b40_7\n\t"
      "cmpl %%ebx, -0x4(%%ebp)\n\t"
      "je .LFUN_00064b40_7\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x50(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00064b40_3:\n\t"
      "cmpl $-1, %%ecx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "je .LFUN_00064b40_6\n\t"
      "pushl %%ecx\n\t"
      "movl 0x5ab23c, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x18(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%esi, %%edx\n\t"
      "je .LFUN_00064b40_4\n\t"
      "movb 0x14(%%eax), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00064b40_3\n\t"
      "movl 0x1c(%%eax), %%edx\n\t"
      "cmpl $-1, %%edx\n\t"
      "je .LFUN_00064b40_3\n\t"
      "cmpl -0x4(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "jne .LFUN_00064b40_3\n\t"
      ".LFUN_00064b40_4:\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      "je .LFUN_00064b40_5\n\t"
      "movl %%eax, %%edi\n\t"
      ".LFUN_00064b40_5:\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .LFUN_00064b40_7\n\t"
      ".LFUN_00064b40_6:\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00064b40_7\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movb 0x8(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00064b40_7\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x68(%%edx), %%cx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x3e(%%eax), %%dx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[ca7a30]\n\t"
      "movb %%al, 0xc(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c645a0]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_00064b40_7\n\t"
      "movl 0x5ab23c, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl $0\n\t"
      "leal -0x4c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c31df0]\n\t"
      "movb 0x14(%%ebp), %%al\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movw $0x1e, 0x6a(%%esi)\n\t"
      "movb $1, 0x126(%%esi)\n\t"
      "je .LFUN_00064b40_7\n\t"
      "leal -0x4c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c33440]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $2, 0x30(%%esi)\n\t"
      "jl .LFUN_00064b40_7\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c32940]\n\t"
      "movb %%al, 0xc(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "movw $3, 0x24(%%esi)\n\t"
      "call *%[c2f2b0]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_00064b40_7:\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00064b40_8:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b64b40_dget), [get] "m"(b64b40_get), [ca7a30] "m"(b64b40_ca7a30), [c645a0] "m"(b64b40_c645a0), [c31df0] "m"(b64b40_c31df0), [c33440] "m"(b64b40_c33440), [c32940] "m"(b64b40_c32940), [c2f2b0] "m"(b64b40_c2f2b0)
      : "memory");
}
#else
#error "FUN_00064b40: clang naked draft required"
#endif


/* FUN_00064cd0 (0x64cd0) — XBE naked draft (batch 81). */
#if defined(__clang__)
static void (*const b64cd0_c65f00)(void) = TIFFVGetField;

__attribute__((naked, noinline))
int FUN_00064cd0(char *prop __attribute__((unused)), int tag __attribute__((unused)), void *out __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c65f00]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00064cd0_19\n\t"
      "cmpl $0x119, %%ebx\n\t"
      "jg .LFUN_00064cd0_10\n\t"
      "je .LFUN_00064cd0_9\n\t"
      "leal -0xfe(%%ebx), %%eax\n\t"
      "cmpl $0x1a, %%eax\n\t"
      "ja .LFUN_00064cd0_15\n\t"
      "movzbl 0x64ea4(%%eax), %%eax\n\t"
      "jmp *.LFUN_00064cd0_jt(,%%eax,4)\n\t"
      ".LFUN_00064cd0_1:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "movw 0x34(%%esi), %%dx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%dx, (%%ecx)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00064cd0_2:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movw 0x36(%%esi), %%cx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%cx, (%%eax)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00064cd0_3:\n\t"
      "movl (%%edi), %%edx\n\t"
      "movw 0x3e(%%esi), %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%ax, (%%edx)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00064cd0_4:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "movw 0x40(%%esi), %%dx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%dx, (%%ecx)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00064cd0_5:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movw 0x42(%%esi), %%cx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%cx, (%%eax)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00064cd0_6:\n\t"
      "movl (%%edi), %%edx\n\t"
      "movw 0x44(%%esi), %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%ax, (%%edx)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00064cd0_7:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "movl 0x48(%%esi), %%edx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00064cd0_8:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movw 0x4c(%%esi), %%cx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%cx, (%%eax)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00064cd0_9:\n\t"
      "movl (%%edi), %%edx\n\t"
      "movw 0x50(%%esi), %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%ax, (%%edx)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00064cd0_10:\n\t"
      "cmpl $0x13d, %%ebx\n\t"
      "jg .LFUN_00064cd0_14\n\t"
      "je .LFUN_00064cd0_13\n\t"
      "subl $0x11c, %%ebx\n\t"
      "je .LFUN_00064cd0_12\n\t"
      "subl $9, %%ebx\n\t"
      "je .LFUN_00064cd0_11\n\t"
      "subl $3, %%ebx\n\t"
      "jne .LFUN_00064cd0_15\n\t"
      "movl (%%edi), %%ecx\n\t"
      "movw 0x5c(%%esi), %%dx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%dx, (%%ecx)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00064cd0_11:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl 0x6c(%%esi), %%ecx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00064cd0_12:\n\t"
      "movl (%%edi), %%edx\n\t"
      "movw 0x5e(%%esi), %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%ax, (%%edx)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00064cd0_13:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "movw 0x46(%%esi), %%dx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%dx, (%%ecx)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00064cd0_14:\n\t"
      "subl $0x80e4, %%ebx\n\t"
      "je .LFUN_00064cd0_18\n\t"
      "decl %%ebx\n\t"
      "je .LFUN_00064cd0_17\n\t"
      "decl %%ebx\n\t"
      "je .LFUN_00064cd0_16\n\t"
      ".LFUN_00064cd0_15:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00064cd0_16:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl 0x30(%%esi), %%ecx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00064cd0_17:\n\t"
      "movl (%%edi), %%edx\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%ax, (%%edx)\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00064cd0_18:\n\t"
      "movw 0x38(%%esi), %%cx\n\t"
      "movl (%%edi), %%edx\n\t"
      "decw %%cx\n\t"
      "movw %%cx, (%%edx)\n\t"
      ".LFUN_00064cd0_19:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00064cd0_jt:\n\t"
      ".long .LFUN_00064cd0_1\n\t"
      ".long .LFUN_00064cd0_2\n\t"
      ".long .LFUN_00064cd0_3\n\t"
      ".long .LFUN_00064cd0_4\n\t"
      ".long .LFUN_00064cd0_5\n\t"
      ".long .LFUN_00064cd0_6\n\t"
      ".long .LFUN_00064cd0_7\n\t"
      ".long .LFUN_00064cd0_8\n\t"
      ".long .LFUN_00064cd0_15\n\t"
      ".text\n\t"
      :
      : [c65f00] "m"(b64cd0_c65f00)
      : "memory");
}
#else
#error "FUN_00064cd0: clang naked draft required"
#endif


/* FUN_00064ec0 (0x64ec0) — readable C lift. */
int FUN_00064ec0(char *prop, int tag, void *out)
{
  return FUN_00064cd0(prop, tag, &out);
}

/* FUN_00064f50 (0x64f50) — readable C lift (ai campaign). */
int FUN_00064f50(int a0)
{
  unsigned char tmp[0x24];
  int rc;
  int field;
  rc = FUN_001e65eb(a0, tmp);
  field = *(int *)(tmp + 0x14); /* [ebp-0x10] with tmp at [ebp-0x24] → offset 0x14 */
  return (rc < 0) ? field : 0;
}

/* FUN_00064fa0 (0x64fa0) — readable C lift. */
int FUN_00064fa0(void *prop, int a1)
{
  unsigned short key = *(unsigned short *)((char *)prop + 0x3a);
  unsigned int *entry = (unsigned int *)0x2c9994;
  unsigned int *end = (unsigned int *)0x2c99c4;
  while (entry < end && entry[1] != (unsigned int)key)
    entry = (unsigned int *)((char *)entry + 0xc);
  unsigned int *p = (entry < end) ? entry : (unsigned int *)0;
  FUN_00068a30(*(int *)prop, (const char *)0x25f530, (const char *)(unsigned long)p[0], a1);
  return -1;
}

/* FUN_00064fe0 (0x64fe0) — readable C lift. */
int FUN_00064fe0(void *prop)
{
  unsigned short key = *(unsigned short *)((char *)prop + 0x3a);
  unsigned int *entry = (unsigned int *)0x2c9994;
  unsigned int *end = (unsigned int *)0x2c99c4;
  while (entry < end && entry[1] != (unsigned int)key)
    entry = (unsigned int *)((char *)entry + 0xc);
  unsigned int *p = (entry < end) ? entry : (unsigned int *)0;
  FUN_00068a30(*(int *)prop, (const char *)0x25f530, (const char *)(unsigned long)p[0], (const char *)0x25f554);
  return -1;
}

/* FUN_00065020 (0x65020) — readable C lift. */
int FUN_00065020(void *prop)
{
  unsigned short key = *(unsigned short *)((char *)prop + 0x3a);
  unsigned int *entry = (unsigned int *)0x2c9994;
  unsigned int *end = (unsigned int *)0x2c99c4;
  while (entry < end && entry[1] != (unsigned int)key)
    entry = (unsigned int *)((char *)entry + 0xc);
  unsigned int *p = (entry < end) ? entry : (unsigned int *)0;
  FUN_00068a30(*(int *)prop, (const char *)0x25f530, (const char *)(unsigned long)p[0], (const char *)0x25f560);
  return -1;
}

/* FUN_00065060 (0x65060) — readable C lift. */
int FUN_00065060(void *prop)
{
  unsigned short key = *(unsigned short *)((char *)prop + 0x3a);
  unsigned int *entry = (unsigned int *)0x2c9994;
  unsigned int *end = (unsigned int *)0x2c99c4;
  while (entry < end && entry[1] != (unsigned int)key)
    entry = (unsigned int *)((char *)entry + 0xc);
  unsigned int *p = (entry < end) ? entry : (unsigned int *)0;
  FUN_00068a30(*(int *)prop, (const char *)0x25f530, (const char *)(unsigned long)p[0], (const char *)0x25f568);
  return -1;
}

/* FUN_000650a0 (0x650a0) — readable C lift. */
int FUN_000650a0(void *prop, int a1)
{
  unsigned short key = *(unsigned short *)((char *)prop + 0x3a);
  unsigned int *entry = (unsigned int *)0x2c9994;
  unsigned int *end = (unsigned int *)0x2c99c4;
  while (entry < end && entry[1] != (unsigned int)key)
    entry = (unsigned int *)((char *)entry + 0xc);
  unsigned int *p = (entry < end) ? entry : (unsigned int *)0;
  FUN_00068a30(*(int *)prop, (const char *)0x25f570, (const char *)(unsigned long)p[0], a1);
  return -1;
}

/* FUN_000650e0 (0x650e0) — readable C lift. */
int FUN_000650e0(void *prop)
{
  unsigned short key = *(unsigned short *)((char *)prop + 0x3a);
  unsigned int *entry = (unsigned int *)0x2c9994;
  unsigned int *end = (unsigned int *)0x2c99c4;
  while (entry < end && entry[1] != (unsigned int)key)
    entry = (unsigned int *)((char *)entry + 0xc);
  unsigned int *p = (entry < end) ? entry : (unsigned int *)0;
  FUN_00068a30(*(int *)prop, (const char *)0x25f570, (const char *)(unsigned long)p[0], (const char *)0x25f554);
  return -1;
}

/* FUN_00065120 (0x65120) — readable C lift. */
int FUN_00065120(void *prop)
{
  unsigned short key = *(unsigned short *)((char *)prop + 0x3a);
  unsigned int *entry = (unsigned int *)0x2c9994;
  unsigned int *end = (unsigned int *)0x2c99c4;
  while (entry < end && entry[1] != (unsigned int)key)
    entry = (unsigned int *)((char *)entry + 0xc);
  unsigned int *p = (entry < end) ? entry : (unsigned int *)0;
  FUN_00068a30(*(int *)prop, (const char *)0x25f570, (const char *)(unsigned long)p[0], (const char *)0x25f560);
  return -1;
}

/* FUN_00065160 (0x65160) — readable C lift. */
int FUN_00065160(void *prop)
{
  unsigned short key = *(unsigned short *)((char *)prop + 0x3a);
  unsigned int *entry = (unsigned int *)0x2c9994;
  unsigned int *end = (unsigned int *)0x2c99c4;
  while (entry < end && entry[1] != (unsigned int)key)
    entry = (unsigned int *)((char *)entry + 0xc);
  unsigned int *p = (entry < end) ? entry : (unsigned int *)0;
  FUN_00068a30(*(int *)prop, (const char *)0x25f570, (const char *)(unsigned long)p[0], (const char *)0x25f568);
  return -1;
}

/* FUN_000651a0 (0x651a0) — readable C lift. */
int FUN_000651a0(void *prop, int key)
{
  int *entry;
  int (*handler)(void *);

  for (entry = (int *)0x2c9994; (unsigned)entry < 0x2c99c4u; entry += 3) {
    if (entry[1] == key) {
      *(unsigned char *)((char *)prop + 0xa) &= (unsigned char)~0x20;
      *(int *)((char *)prop + 0xf0) = 0;
      *(int *)((char *)prop + 0xfc) = 0x650e0;
      *(int *)((char *)prop + 0x104) = 0x65120;
      *(int *)((char *)prop + 0x10c) = 0x65160;
      *(int *)((char *)prop + 0xf4) = 0;
      *(int *)((char *)prop + 0xf8) = 0;
      *(int *)((char *)prop + 0x100) = 0x64fe0;
      *(int *)((char *)prop + 0x108) = 0x65020;
      *(int *)((char *)prop + 0x110) = 0x65060;
      *(int *)((char *)prop + 0x114) = 0;
      *(int *)((char *)prop + 0x118) = 0;
      *(int *)((char *)prop + 0x11c) = 0;
      *((char *)prop + 9) = 0;
      handler = (int (*)(void *))entry[2];
      return handler(prop);
    }
  }
  FUN_00068a30(*(int *)prop, (const char *)0x25f594, key, key);
  return 0;
}


/* FUN_00065250 (0x65250) — readable C lift. */
void FUN_00065250(void **out_ptr, const char *src)
{
  void *p;
  int n;

  if (*out_ptr) {
    debug_free(*out_ptr, (const char *)0x25f5c4, 0x45);
    *out_ptr = 0;
  }
  if (!src) {
    return;
  }
  n = csstrlen(src) + 1;
  p = debug_malloc((uint32_t)n, 0, (const char *)0x25f5c4, 0x48);
  *out_ptr = p;
  if (p) {
    csmemcpy(p, (void *)src, (size_t)n);
  }
}

/* FUN_000652a0 (0x652a0) — readable C lift. */
void FUN_000652a0(int count, void **out_ptr, void *src)
{
  void *p;
  int nbytes;

  if (*out_ptr) {
    debug_free(*out_ptr, (const char *)0x25f5c4, 0x51);
    *out_ptr = 0;
  }
  nbytes = count + count;
  if (!src) {
    return;
  }
  p = debug_malloc((uint32_t)nbytes, 0, (const char *)0x25f5c4, 0x53);
  *out_ptr = p;
  if (p) {
    csmemcpy(p, src, (size_t)nbytes);
  }
}

/* FUN_000652f0 (0x652f0) — XBE naked draft (batch 105). */
#if defined(__clang__)
static int (*const b652f0_c651a0)(void *prop, int key) = FUN_000651a0;
static void (*const b652f0_c65250)(void) = FUN_00065250;
static void (*const b652f0_c66380)(void) = TIFFDefaultDirectory;
static void (*const b652f0_c6f9d0)(void) = FUN_0006f9d0;
static void (*const b652f0_c68a30)(int param_1, const char *format, ...) = FUN_00068a30;
static void (*const b652f0_c652a0)(void) = FUN_000652a0;

__attribute__((naked, noinline))
void FUN_000652f0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "cmpl $0x80e3, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $1, -0x4(%%ebp)\n\t"
      "jg .LFUN_000652f0_50\n\t"
      "je .LFUN_000652f0_49\n\t"
      "leal -0xfe(%%esi), %%eax\n\t"
      "cmpl $0x55, %%eax\n\t"
      "ja .LFUN_000652f0_51\n\t"
      "movzbl 0x65964(%%eax), %%eax\n\t"
      "jmp *.LFUN_000652f0_jt(,%%eax,4)\n\t"
      ".LFUN_000652f0_1:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movw (%%ecx), %%dx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movw %%dx, 0x34(%%eax)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_2:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%edx, 0x1c(%%eax)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_3:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%edx, 0x20(%%eax)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_4:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movw (%%ecx), %%dx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movw %%dx, 0x36(%%eax)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_5:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl (%%ecx), %%edi\n\t"
      "movb 0x14(%%ebx), %%al\n\t"
      "andl $0xffff, %%edi\n\t"
      "testb %%al, %%al\n\t"
      "jns .LFUN_000652f0_7\n\t"
      "movzwl 0x3a(%%ebx), %%edx\n\t"
      "cmpl %%edi, %%edx\n\t"
      "je .LFUN_000652f0_57\n\t"
      "movl %%ebx, %%eax\n\t"
      "movl 0x11c(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000652f0_6\n\t"
      "movl %%ebx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%%eax\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_000652f0_6:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      ".LFUN_000652f0_7:\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c651a0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LFUN_000652f0_58\n\t"
      "movw %%di, 0x3a(%%ebx)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_8:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movw (%%edx), %%ax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movw %%ax, 0x3c(%%ecx)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_9:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movw (%%edx), %%ax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movw %%ax, 0x3e(%%ecx)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_10:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl (%%edx), %%edi\n\t"
      "cmpl $2, %%edi\n\t"
      "je .LFUN_000652f0_11\n\t"
      "cmpl $1, %%edi\n\t"
      "jne .LFUN_000652f0_59\n\t"
      ".LFUN_000652f0_11:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movw %%di, 0x40(%%eax)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_12:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl (%%ecx), %%ebx\n\t"
      "addl $0x90, %%edi\n\t"
      "call *%[c65250]\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_13:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl (%%edx), %%ebx\n\t"
      "addl $0x94, %%edi\n\t"
      "call *%[c65250]\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_14:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl (%%eax), %%ebx\n\t"
      "addl $0x98, %%edi\n\t"
      "call *%[c65250]\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_15:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl (%%ecx), %%ebx\n\t"
      "addl $0x9c, %%edi\n\t"
      "call *%[c65250]\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_16:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl (%%edx), %%ebx\n\t"
      "addl $0xa0, %%edi\n\t"
      "call *%[c65250]\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_17:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl (%%eax), %%ebx\n\t"
      "addl $0xa4, %%edi\n\t"
      "call *%[c65250]\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_18:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl (%%ecx), %%ebx\n\t"
      "addl $0xa8, %%edi\n\t"
      "call *%[c65250]\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_19:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl (%%edx), %%ebx\n\t"
      "addl $0xac, %%edi\n\t"
      "call *%[c65250]\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_20:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl (%%eax), %%edi\n\t"
      "cmpl $1, %%edi\n\t"
      "jl .LFUN_000652f0_21\n\t"
      "cmpl $8, %%edi\n\t"
      "jg .LFUN_000652f0_21\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movw %%di, 0x42(%%ecx)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_21:\n\t"
      "pushl %%esi\n\t"
      "call *%[c66380]\n\t"
      "movl 0x10(%%eax), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl $0x25f654\n\t"
      "pushl %%ecx\n\t"
      "call *%[c6f9d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_22:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl (%%edx), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_000652f0_59\n\t"
      "cmpl $4, %%edi\n\t"
      "jle .LFUN_000652f0_23\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl $0x25f634\n\t"
      "pushl %%ecx\n\t"
      "call *%[c68a30]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000652f0_23:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movw %%di, 0x44(%%edx)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_24:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl (%%eax), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_000652f0_59\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%edi, 0x48(%%eax)\n\t"
      "testb $2, 0x14(%%eax)\n\t"
      "jne .LFUN_000652f0_57\n\t"
      "movl 0x1c(%%eax), %%ecx\n\t"
      "movl %%edi, 0x2c(%%eax)\n\t"
      "movl %%ecx, 0x28(%%eax)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_25:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "andl $0xffff, %%eax\n\t"
      "movl %%eax, 0x4c(%%ecx)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_26:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "andl $0xffff, %%eax\n\t"
      "movl %%eax, 0x50(%%ecx)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_27:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "fldl (%%edx)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "fstps 0x54(%%eax)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_28:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "fldl (%%ecx)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "fstps 0x58(%%edx)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_29:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl (%%eax), %%edi\n\t"
      "cmpl $1, %%edi\n\t"
      "je .LFUN_000652f0_30\n\t"
      "cmpl $2, %%edi\n\t"
      "jne .LFUN_000652f0_59\n\t"
      ".LFUN_000652f0_30:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movw %%di, 0x5e(%%ecx)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_31:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl (%%edx), %%ebx\n\t"
      "addl $0xb0, %%edi\n\t"
      "call *%[c65250]\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_32:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "fldl (%%eax)\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "fstps 0x60(%%ecx)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_33:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "fldl (%%edx)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "fstps 0x64(%%eax)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_34:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%edx, 0x68(%%eax)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_35:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%edx, 0x6c(%%eax)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_36:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edi\n\t"
      "cmpl $1, %%edi\n\t"
      "jl .LFUN_000652f0_59\n\t"
      "cmpl $3, %%edi\n\t"
      "jg .LFUN_000652f0_59\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movw %%di, 0x5c(%%edx)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_37:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movw (%%eax), %%dx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "addl $4, %%eax\n\t"
      "movw %%dx, 0x70(%%ecx)\n\t"
      "movw (%%eax), %%ax\n\t"
      "movw %%ax, 0x72(%%ecx)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_38:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movw (%%eax), %%dx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "addl $4, %%eax\n\t"
      "movw %%dx, 0x8c(%%ecx)\n\t"
      "movw (%%eax), %%ax\n\t"
      "movw %%ax, 0x8e(%%ecx)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_39:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movb 0x36(%%edx), %%cl\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "movl (%%edi), %%ebx\n\t"
      "movl $1, %%eax\n\t"
      "shll %%cl, %%eax\n\t"
      "addl $4, %%edi\n\t"
      "leal 0x80(%%edx), %%esi\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[c652a0]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl (%%edi), %%ebx\n\t"
      "addl $4, %%edi\n\t"
      "pushl %%ecx\n\t"
      "addl $0x84, %%esi\n\t"
      "call *%[c652a0]\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl (%%edi), %%ebx\n\t"
      "pushl %%edx\n\t"
      "addl $0x88, %%esi\n\t"
      "call *%[c652a0]\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_40:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movw (%%eax), %%cx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movw %%cx, 0x46(%%edx)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_41:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movzwl 0x44(%%ebx), %%ecx\n\t"
      "movl (%%eax), %%edi\n\t"
      "addl $4, %%eax\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "jg .LFUN_000652f0_60\n\t"
      "cmpl $1, %%edi\n\t"
      "jne .LFUN_000652f0_60\n\t"
      "movl (%%eax), %%edi\n\t"
      "cmpl $1, %%edi\n\t"
      "jne .LFUN_000652f0_60\n\t"
      "movw %%di, 0x74(%%ebx)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_42:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x7c(%%ecx)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_43:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movw (%%edx), %%ax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movw %%ax, 0x76(%%ecx)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_44:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movw (%%edx), %%ax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movw %%ax, 0x78(%%ecx)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_45:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl (%%edx), %%edi\n\t"
      "movl %%edi, %%eax\n\t"
      "andl $0x80000007, %%eax\n\t"
      "jns .LFUN_000652f0_46\n\t"
      "decl %%eax\n\t"
      "orl $0xfffffff8, %%eax\n\t"
      "incl %%eax\n\t"
      ".LFUN_000652f0_46:\n\t"
      "jne .LFUN_000652f0_59\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%edi, 0x28(%%eax)\n\t"
      "orb $0x80, 0xa(%%eax)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_47:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edi\n\t"
      "movl %%edi, %%edx\n\t"
      "andl $0x80000007, %%edx\n\t"
      "jns .LFUN_000652f0_48\n\t"
      "decl %%edx\n\t"
      "orl $0xfffffff8, %%edx\n\t"
      "incl %%edx\n\t"
      ".LFUN_000652f0_48:\n\t"
      "jne .LFUN_000652f0_59\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%edi, 0x2c(%%eax)\n\t"
      "orb $0x80, 0xa(%%eax)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_49:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movw (%%eax), %%cx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movw %%cx, 0x74(%%edx)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_50:\n\t"
      "movl %%esi, %%eax\n\t"
      "subl $0x80e4, %%eax\n\t"
      "je .LFUN_000652f0_54\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000652f0_53\n\t"
      "decl %%eax\n\t"
      "je .LFUN_000652f0_52\n\t"
      ".LFUN_000652f0_51:\n\t"
      "pushl %%esi\n\t"
      "call *%[c66380]\n\t"
      "movl 0x10(%%eax), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x25f608\n\t"
      "pushl %%edx\n\t"
      "call *%[c68a30]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000652f0_52:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl (%%eax), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_000652f0_59\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%edi, 0x30(%%ecx)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_53:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x24(%%ecx)\n\t"
      "jmp .LFUN_000652f0_57\n\t"
      ".LFUN_000652f0_54:\n\t"
      "cmpl $0x80e4, %%esi\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl (%%edx), %%edi\n\t"
      "jne .LFUN_000652f0_55\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_000652f0_55\n\t"
      "movl $4, %%edi\n\t"
      "jmp .LFUN_000652f0_56\n\t"
      ".LFUN_000652f0_55:\n\t"
      "cmpl $1, %%edi\n\t"
      "jl .LFUN_000652f0_59\n\t"
      "cmpl $4, %%edi\n\t"
      "jg .LFUN_000652f0_59\n\t"
      ".LFUN_000652f0_56:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movw %%di, 0x38(%%eax)\n\t"
      ".LFUN_000652f0_57:\n\t"
      "pushl %%esi\n\t"
      "call *%[c66380]\n\t"
      "movzwl 0xc(%%eax), %%ecx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "shrl $5, %%ecx\n\t"
      "pushl %%esi\n\t"
      "leal 0x14(%%ebx,%%ecx,4), %%edi\n\t"
      "call *%[c66380]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0xc(%%eax), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "addl $8, %%esp\n\t"
      "andl $0x1f, %%ecx\n\t"
      "shll %%cl, %%edx\n\t"
      "orl %%edx, (%%edi)\n\t"
      "orb $2, 0xa(%%ebx)\n\t"
      ".LFUN_000652f0_58:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000652f0_59:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      ".LFUN_000652f0_60:\n\t"
      "pushl %%esi\n\t"
      "call *%[c66380]\n\t"
      "movl 0x10(%%eax), %%eax\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $0x25f5f0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c68a30]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_000652f0_jt:\n\t"
      ".long .LFUN_000652f0_1\n\t"
      ".long .LFUN_000652f0_2\n\t"
      ".long .LFUN_000652f0_3\n\t"
      ".long .LFUN_000652f0_4\n\t"
      ".long .LFUN_000652f0_5\n\t"
      ".long .LFUN_000652f0_8\n\t"
      ".long .LFUN_000652f0_9\n\t"
      ".long .LFUN_000652f0_10\n\t"
      ".long .LFUN_000652f0_12\n\t"
      ".long .LFUN_000652f0_16\n\t"
      ".long .LFUN_000652f0_17\n\t"
      ".long .LFUN_000652f0_18\n\t"
      ".long .LFUN_000652f0_20\n\t"
      ".long .LFUN_000652f0_22\n\t"
      ".long .LFUN_000652f0_24\n\t"
      ".long .LFUN_000652f0_25\n\t"
      ".long .LFUN_000652f0_26\n\t"
      ".long .LFUN_000652f0_27\n\t"
      ".long .LFUN_000652f0_28\n\t"
      ".long .LFUN_000652f0_29\n\t"
      ".long .LFUN_000652f0_31\n\t"
      ".long .LFUN_000652f0_32\n\t"
      ".long .LFUN_000652f0_33\n\t"
      ".long .LFUN_000652f0_34\n\t"
      ".long .LFUN_000652f0_35\n\t"
      ".long .LFUN_000652f0_36\n\t"
      ".long .LFUN_000652f0_37\n\t"
      ".long .LFUN_000652f0_19\n\t"
      ".long .LFUN_000652f0_14\n\t"
      ".long .LFUN_000652f0_13\n\t"
      ".long .LFUN_000652f0_15\n\t"
      ".long .LFUN_000652f0_40\n\t"
      ".long .LFUN_000652f0_39\n\t"
      ".long .LFUN_000652f0_38\n\t"
      ".long .LFUN_000652f0_45\n\t"
      ".long .LFUN_000652f0_47\n\t"
      ".long .LFUN_000652f0_42\n\t"
      ".long .LFUN_000652f0_43\n\t"
      ".long .LFUN_000652f0_44\n\t"
      ".long .LFUN_000652f0_41\n\t"
      ".long .LFUN_000652f0_54\n\t"
      ".long .LFUN_000652f0_51\n\t"
      ".text\n\t"
      :
      : [c651a0] "m"(b652f0_c651a0), [c65250] "m"(b652f0_c65250), [c66380] "m"(b652f0_c66380), [c6f9d0] "m"(b652f0_c6f9d0), [c68a30] "m"(b652f0_c68a30), [c652a0] "m"(b652f0_c652a0)
      : "memory");
}
#else
#error "FUN_000652f0: clang naked draft required"
#endif

