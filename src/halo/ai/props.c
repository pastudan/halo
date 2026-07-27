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

/* FUN_00063e90 (0x63e90) — XBE naked draft (batch 230). */
#if defined(__clang__)
static int (*const b63e90_c63e30)(int scenario, unsigned char bsp_idx, float *origin, int surface_index, float *out_point) = FUN_00063e30;
static char (*const b63e90_c639e0)(int scenario, unsigned char bsp_idx, float *origin, int start_surface, float *target, int end_surface, char *result_buf) = FUN_000639e0;

__attribute__((naked, noinline))
char FUN_00063e90(int scenario __attribute__((unused)), unsigned char bsp_idx __attribute__((unused)), float *origin __attribute__((unused)), int node_handle __attribute__((unused)), float *target __attribute__((unused)), int flags __attribute__((unused)), float param_7 __attribute__((unused)), int param_8 __attribute__((unused)), unsigned int *result __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x84, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x18(%%ebp), %%edi\n\t"
      "flds (%%edi)\n\t"
      "xorb %%cl, %%cl\n\t"
      "fsubs (%%esi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "fchs\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00063e90_11\n\t"
      "flds 0x2533c8\n\t"
      "fdiv %%st(1), %%st(0)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00063e90_12\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "fmuls 0x20(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "fsts 0x18(%%ebp)\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "fadds (%%esi)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "flds -0x4(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "fmuls 0x20(%%ebp)\n\t"
      "fsts 0x10(%%ebp)\n\t"
      "fadds 0x4(%%esi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "call *%[c63e30]\n\t"
      "flds 0x18(%%ebp)\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "fadds (%%edi)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "fadds 0x4(%%edi)\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "call *%[c63e30]\n\t"
      "flds 0x20(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "fchs\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "fsts 0x18(%%ebp)\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "flds -0x8(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "fadds (%%esi)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x4(%%esi)\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[c63e30]\n\t"
      "flds 0x18(%%ebp)\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "flds -0x8(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fadds (%%edi)\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x4(%%edi)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[c63e30]\n\t"
      "movl %%eax, 0x18(%%ebp)\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "addl $0x50, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00063e90_1\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "leal -0x4c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c639e0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00063e90_2\n\t"
      "movl -0x3c(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00063e90_2\n\t"
      "testb $1, 0x24(%%ebp)\n\t"
      "jne .LFUN_00063e90_2\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "leal -0x84(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "leal -0x48(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c639e0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00063e90_2\n\t"
      ".LFUN_00063e90_1:\n\t"
      "movb $0, -0x4c(%%ebp)\n\t"
      ".LFUN_00063e90_2:\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_00063e90_3\n\t"
      "xorb %%al, %%al\n\t"
      "movb %%al, -0x68(%%ebp)\n\t"
      "jmp .LFUN_00063e90_5\n\t"
      ".LFUN_00063e90_3:\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "leal -0x68(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c639e0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00063e90_4\n\t"
      "movl -0x58(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00063e90_4\n\t"
      "testb $1, 0x24(%%ebp)\n\t"
      "jne .LFUN_00063e90_4\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "leal -0x84(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "leal -0x64(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c639e0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00063e90_4\n\t"
      "movb %%al, -0x68(%%ebp)\n\t"
      "jmp .LFUN_00063e90_5\n\t"
      ".LFUN_00063e90_4:\n\t"
      "movb -0x68(%%ebp), %%al\n\t"
      ".LFUN_00063e90_5:\n\t"
      "movb -0x4c(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_00063e90_7\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00063e90_6\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fcomps -0x50(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00063e90_8\n\t"
      ".LFUN_00063e90_6:\n\t"
      "leal -0x4c(%%ebp), %%esi\n\t"
      "jmp .LFUN_00063e90_9\n\t"
      ".LFUN_00063e90_7:\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00063e90_10\n\t"
      ".LFUN_00063e90_8:\n\t"
      "leal -0x68(%%ebp), %%esi\n\t"
      ".LFUN_00063e90_9:\n\t"
      "flds (%%edi)\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs 0x8(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fmuls 0x20(%%ebp)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "je .LFUN_00063e90_10\n\t"
      "movl 0x28(%%ebp), %%edi\n\t"
      "movl $7, %%ecx\n\t"
      "rep movsl\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00063e90_10:\n\t"
      "movl 0x28(%%ebp), %%edi\n\t"
      "movl $7, %%ecx\n\t"
      "leal -0x4c(%%ebp), %%esi\n\t"
      "rep movsl\n\t"
      "popl %%edi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00063e90_11:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00063e90_12:\n\t"
      "popl %%edi\n\t"
      "movb %%cl, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c63e30] "m"(b63e90_c63e30), [c639e0] "m"(b63e90_c639e0)
      : "memory");
}
#else
#error "FUN_00063e90: clang naked draft required"
#endif


/* prop_add (0x64170) — XBE naked draft (batch 81). */
#if defined(__clang__)
static int (*const b64170_gtime)(void) = game_time_get;
static void (*const b64170_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void *(*const b64170_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b64170_get)(int, int) = object_get_and_verify_type;
static void *(*const b64170_tag)(int, int) = tag_get;
static void (*const b64170_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b64170_exitfn)(int) = system_exit;
static bool (*const b64170_ca7a30)(int16_t team_a, int16_t team_b) = game_allegiance_get_team_is_friendly;
static bool (*const b64170_ca7a90)(int16_t team_a, int16_t team_b) = game_team_is_ally;
static bool (*const b64170_ca7ae0)(int16_t team_a, int16_t team_b) = game_team_ally_status_changed;

__attribute__((naked, noinline))
void prop_add(int actor_handle __attribute__((unused)), int prop_index __attribute__((unused)), int unit_handle __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "cmpl %%edi, %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "jne .Lprop_add_2\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x2c97b8, %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .Lprop_add_1\n\t"
      "addl $0x384, %%eax\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jl .Lprop_add_12\n\t"
      ".Lprop_add_1:\n\t"
      "pushl $0x300\n\t"
      "pushl $0x25f1a8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "movl %%esi, 0x2c97b8\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lprop_add_2:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "xorl %%eax, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%edi, %%ebx\n\t"
      "movw %%di, 0x66(%%esi)\n\t"
      "movw %%di, 0x6c(%%esi)\n\t"
      "movl %%ebx, 0x18(%%esi)\n\t"
      "movb $0, 0x74(%%esi)\n\t"
      "movl %%eax, 0x70(%%esi)\n\t"
      "movw %%di, 0xb0(%%esi)\n\t"
      "movb %%al, 0xb8(%%esi)\n\t"
      "movl %%edi, 0xb4(%%esi)\n\t"
      "movl %%edi, 0x7c(%%esi)\n\t"
      "movl %%edi, 0x8c(%%esi)\n\t"
      "movb %%al, 0x4e(%%esi)\n\t"
      "movl %%edi, 0x1c(%%esi)\n\t"
      "movl %%edi, 0xc(%%esi)\n\t"
      "movw %%ax, 0x6a(%%esi)\n\t"
      "movl %%edi, 0xa0(%%esi)\n\t"
      "je .Lprop_add_11\n\t"
      "pushl $3\n\t"
      "pushl %%ebx\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x756e6974\n\t"
      "call *%[tag]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x18(%%edx), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "jne .Lprop_add_3\n\t"
      "pushl $1\n\t"
      "pushl $0xe8\n\t"
      "pushl $0x25f134\n\t"
      "pushl $0x25f180\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lprop_add_3:\n\t"
      "cmpw $0, 0x64(%%edi)\n\t"
      "je .Lprop_add_4\n\t"
      "pushl $1\n\t"
      "pushl $0xe9\n\t"
      "pushl $0x25f134\n\t"
      "pushl $0x25f150\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lprop_add_4:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x68(%%edi), %%ax\n\t"
      "movw %%ax, 0x12(%%esi)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movw 0x3e(%%eax), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[ca7a30]\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x12(%%esi), %%dx\n\t"
      "movb %%al, 0x60(%%esi)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x3e(%%ebx), %%ax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[ca7a90]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x12(%%esi), %%cx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb %%al, 0x61(%%esi)\n\t"
      "movw 0x3e(%%ebx), %%dx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[ca7ae0]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb %%al, 0x62(%%esi)\n\t"
      "movb 0xb6(%%edi), %%al\n\t"
      "shrb $2, %%al\n\t"
      "andb $1, %%al\n\t"
      "movb %%al, 0x127(%%esi)\n\t"
      "movl 0x284(%%ecx), %%edx\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edx, 0x20(%%esi)\n\t"
      "je .Lprop_add_5\n\t"
      "cmpw $0, 0x3d0(%%edi)\n\t"
      "jne .Lprop_add_5\n\t"
      "movl $1, %%ecx\n\t"
      "jmp .Lprop_add_6\n\t"
      ".Lprop_add_5:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".Lprop_add_6:\n\t"
      "negb %%al\n\t"
      "movb %%cl, 0x128(%%esi)\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0x3e8, %%eax\n\t"
      "movw %%ax, 0x76(%%esi)\n\t"
      "movl 0x70(%%edi), %%ecx\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "setne %%al\n\t"
      "movb %%al, 0x12e(%%esi)\n\t"
      "cmpl %%ebx, 0x1a8(%%edi)\n\t"
      "je .Lprop_add_7\n\t"
      "movb $1, 0x14(%%esi)\n\t"
      "movl 0x1a8(%%edi), %%ecx\n\t"
      "movl %%ecx, 0x1c(%%esi)\n\t"
      "call *%[gtime]\n\t"
      "movl %%eax, 0x28(%%esi)\n\t"
      "jmp .Lprop_add_8\n\t"
      ".Lprop_add_7:\n\t"
      "movl 0x1a4(%%edi), %%edx\n\t"
      "movl %%edx, 0x1c(%%esi)\n\t"
      ".Lprop_add_8:\n\t"
      "movb 0x12e(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lprop_add_9\n\t"
      "movw $6, 0x10(%%esi)\n\t"
      "jmp .Lprop_add_11\n\t"
      ".Lprop_add_9:\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .Lprop_add_10\n\t"
      "pushl %%eax\n\t"
      "movl 0x6325a4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movw 0x4(%%eax), %%cx\n\t"
      "addl $8, %%esp\n\t"
      "movw %%cx, 0x10(%%esi)\n\t"
      "jmp .Lprop_add_11\n\t"
      ".Lprop_add_10:\n\t"
      "movw %%bx, 0x10(%%esi)\n\t"
      ".Lprop_add_11:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x50(%%eax), %%edx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x8(%%esi)\n\t"
      "movl %%ecx, 0x50(%%eax)\n\t"
      ".Lprop_add_12:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [gtime] "m"(b64170_gtime), [c8f390] "m"(b64170_c8f390), [dget] "m"(b64170_dget), [get] "m"(b64170_get), [tag] "m"(b64170_tag), [assert] "m"(b64170_assert), [exitfn] "m"(b64170_exitfn), [ca7a30] "m"(b64170_ca7a30), [ca7a90] "m"(b64170_ca7a90), [ca7ae0] "m"(b64170_ca7ae0)
      : "memory");
}
#else
#error "prop_add: clang naked draft required"
#endif


/* FUN_000643d0 (0x643d0) — readable C lift. */
int FUN_000643d0(int actor_handle)
{
  int idx = data_new_at_index(*(void **)0x5ab23c);
  prop_add(actor_handle, idx, -1);
  return idx;
}

/* prop_new_unacknowledged (0x645a0) — XBE naked draft (batch 81). */
#if defined(__clang__)
static void *(*const b645a0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static char (*const b645a0_c2f6e0)(int actor_handle, int existing_prop, int unit_handle, int owner_handle, char field_63, char field_12e, char friendly, char field_127, int16_t field_76, int16_t scale, float visibility, int sense, char *out_flag) = actor_perception_desire_prop;
static int (*const b645a0_c119610)(data_t *data) = data_new_at_index;
static void (*const b645a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b645a0_exitfn)(int) = system_exit;
static void (*const b645a0_c3b410)(int actor_handle, int old_prop, int new_prop) = FUN_0003b410;
static void (*const b645a0_c64400)(int actor_handle, int prop_handle) = FUN_00064400;
static void *(*const b645a0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b645a0_c64170)(int actor_handle, int prop_index, int unit_handle) = prop_add;

__attribute__((naked, noinline))
int prop_new_unacknowledged(int actor_handle __attribute__((unused)), int unit_handle __attribute__((unused)), char friendly __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "movl 0x6325a4, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl $0x7f7fffff, -0xc(%%ebp)\n\t"
      "movl $0x7f7fffff, -0x10(%%ebp)\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "movl 0x50(%%eax), %%edi\n\t"
      "addl $8, %%esp\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lprop_new_unacknowledged_1:\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%edi, %%ebx\n\t"
      "je .Lprop_new_unacknowledged_4\n\t"
      "movl 0x5ab23c, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movw 0x24(%%esi), %%ax\n\t"
      "movl 0x8(%%esi), %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .Lprop_new_unacknowledged_2\n\t"
      "cmpw $5, %%ax\n\t"
      "jle .Lprop_new_unacknowledged_1\n\t"
      ".Lprop_new_unacknowledged_2:\n\t"
      "cmpl $-1, 0xc(%%esi)\n\t"
      "jne .Lprop_new_unacknowledged_1\n\t"
      "flds 0x11c(%%esi)\n\t"
      "movl 0x20(%%esi), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "fld %%st(0)\n\t"
      "movw 0x6a(%%esi), %%cx\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "leal -0x1(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x76(%%esi), %%ax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x127(%%esi), %%cl\n\t"
      "fstp %%st(0)\n\t"
      "pushl %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0x60(%%esi), %%dl\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x12e(%%esi), %%al\n\t"
      "pushl %%ecx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x63(%%esi), %%cl\n\t"
      "pushl %%edx\n\t"
      "movl 0x1c(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2f6e0]\n\t"
      "addl $0x34, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lprop_new_unacknowledged_3\n\t"
      "flds 0x11c(%%esi)\n\t"
      "fcomps -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lprop_new_unacknowledged_1\n\t"
      "movl 0x11c(%%esi), %%edx\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "jmp .Lprop_new_unacknowledged_1\n\t"
      ".Lprop_new_unacknowledged_3:\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "cmpb %%al, 0x60(%%esi)\n\t"
      "jne .Lprop_new_unacknowledged_1\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "incl %%ecx\n\t"
      "testb %%al, %%al\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "je .Lprop_new_unacknowledged_1\n\t"
      "flds 0x11c(%%esi)\n\t"
      "fcomps -0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lprop_new_unacknowledged_1\n\t"
      "movl 0x11c(%%esi), %%ecx\n\t"
      "movl %%ebx, -0x18(%%ebp)\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "jmp .Lprop_new_unacknowledged_1\n\t"
      ".Lprop_new_unacknowledged_4:\n\t"
      "movl -0x14(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .Lprop_new_unacknowledged_6\n\t"
      "movl -0x18(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lprop_new_unacknowledged_5\n\t"
      "movb 0x10(%%ebp), %%cl\n\t"
      "xorl %%edx, %%edx\n\t"
      "testb %%cl, %%cl\n\t"
      "setne %%dl\n\t"
      "leal 0x4(%%edx,%%edx,1), %%edx\n\t"
      "cmpw %%dx, -0x8(%%ebp)\n\t"
      "jl .Lprop_new_unacknowledged_5\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .Lprop_new_unacknowledged_6\n\t"
      ".Lprop_new_unacknowledged_5:\n\t"
      "movl 0x5ab23c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119610]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      "jmp .Lprop_new_unacknowledged_8\n\t"
      ".Lprop_new_unacknowledged_6:\n\t"
      "movl 0x5ab23c, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .Lprop_new_unacknowledged_7\n\t"
      "pushl $1\n\t"
      "pushl $0x9e\n\t"
      "pushl $0x25f134\n\t"
      "pushl $0x255f50\n\t"
      "call *%[assert]\n\t"
      "pushl %%ebx\n\t"
      "call *%[exitfn]\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .Lprop_new_unacknowledged_7\n\t"
      "pushl $1\n\t"
      "pushl $0x9f\n\t"
      "pushl $0x25f134\n\t"
      "pushl $0x25f46c\n\t"
      "call *%[assert]\n\t"
      "pushl %%ebx\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lprop_new_unacknowledged_7:\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c3b410]\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c64400]\n\t"
      "movw (%%esi), %%bx\n\t"
      "pushl $0x138\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "addl $0x18, %%esp\n\t"
      "movw %%bx, (%%esi)\n\t"
      ".Lprop_new_unacknowledged_8:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c64170]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(b645a0_dget), [c2f6e0] "m"(b645a0_c2f6e0), [c119610] "m"(b645a0_c119610), [assert] "m"(b645a0_assert), [exitfn] "m"(b645a0_exitfn), [c3b410] "m"(b645a0_c3b410), [c64400] "m"(b645a0_c64400), [memset] "m"(b645a0_memset), [c64170] "m"(b645a0_c64170)
      : "memory");
}
#else
#error "prop_new_unacknowledged: clang naked draft required"
#endif


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

