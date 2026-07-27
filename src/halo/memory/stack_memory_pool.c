/* stack_memory_pool.c — stack-based memory pool allocator.
 *
 * Manages a fixed-size memory arena divided into variable-size blocks, tracked
 * in a slot table appended immediately after the pool header struct. Blocks
 * carry a 0x1c-byte header; the high bit of the first dword flags whether the
 * block is "in use" (marked by stack_memory_pool_mark_used internally). The
 * pool tracks bytes_used, peak_bytes, alloc_count, peak_alloc_count, and
 * largest_alloc for diagnostics.
 *
 * Internal helpers (valid_block, unlink_block, alloc_or_resize,
 * memory_block_valid, mark_used) use non-standard register-passing conventions
 * (EAX/ECX/ESI/EDI) declared in kb.json with @<reg> annotations.
 */


/* stack_memory_pool_initialize — reset a pool back to its initial state.
 *
 * Saves the four pre-configured header fields (tag/name at +0, base_address
 * at +4, pool_size at +8, slot_count at +c), zeroes the entire 0x34-byte
 * header plus the slot table (slot_count * 4 bytes), then restores those
 * fields and writes a self-pointer into table[0] to seed the free-slot list.
 */
void stack_memory_pool_initialize(void *pool)
{
  unsigned int *p = (unsigned int *)pool;
  unsigned int saved0, saved1, saved2, saved3;
  unsigned int *table;
  unsigned int table_ptr;

  if (pool == 0) {
    display_assert("pool", "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c",
                   0x1b0, 1);
    system_exit(-1);
  }

  /* Save the pre-configured fields that survive an initialize call. */
  saved0 = p[0]; /* field at +0x00 (e.g. pool tag/name pointer) */
  saved1 = p[1]; /* field at +0x04 (base_address) */
  saved2 = p[2]; /* field at +0x08 (pool_size in bytes) */
  saved3 = p[3]; /* field at +0x0c (slot_count) */

  table = p + 0xd; /* &pool[0x34] — start of slot table */

  /* Zero the slot table first (slot_count * 4 bytes). */
  csmemset(table, 0, saved3 * 4);

  /* Zero the 0x34-byte pool header. */
  csmemset(pool, 0, 0x34);

  /* Restore the pre-configured fields. */
  p[0] = saved0;
  p[1] = saved1;
  p[2] = saved2; /* field at +0x08 */
  p[3] = saved3; /* field at +0x0c */

  /* Seed slot table[0] with &table[0] (self-pointer for free-list init).
   * The original uses csmemcpy(table, &local_table_ptr, 4) where
   * local_table_ptr == table. */
  table_ptr = (unsigned int)table;
  csmemcpy(table, &table_ptr, 4);
}

/* FUN_0011ea50 — initialize a freshly allocated block header.
 *
 * Register convention (kb.json):
 *   - slot_index on stack (cdecl first arg)
 *   - block_hdr in ESI (@<esi>)
 *   - block_size in EDI (@<edi>)
 *
 * Writes header fields:
 *   +0x00 size_flags = block_size
 *   +0x04 slot_index
 *   +0x18 "fryd" sentinel (0x66727964)
 *   +block_size-4 "chkn" sentinel (0x63686b6e)
 */
void FUN_0011ea50(int slot_index, void *block_hdr, int block_size)
{
  int *blk = (int *)block_hdr;

  if (blk == 0) {
    display_assert("block", "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c",
                   0x21f, 1);
    system_exit(-1);
  }

  blk[0] = block_size;
  blk[1] = slot_index;
  blk[6] = 0x66727964;
  *(int *)((char *)blk + block_size - 4) = 0x63686b6e;
}

/* FUN_0011ea90 — return block usable size from header.
 *
 * Register convention: block_hdr in ESI (kb.json @<esi>).
 * Returns low 31 bits of dword at +0x00 (size_flags).
 */
unsigned int FUN_0011ea90(void *block_hdr)
{
  unsigned int *blk = (unsigned int *)block_hdr;

  if (blk == 0) {
    display_assert("block", "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c",
                   0x22f, 1);
    system_exit(-1);
  }

  return blk[0] & 0x7fffffff;
}

/* FUN_0011eb40 — compute largest free tail space in pool.
 *
 * Register convention: pool in ESI (kb.json @<esi>).
 *
 * If pool has no blocks, returns pool_size.
 * Otherwise returns bytes from end of last block to pool end.
 */
unsigned int FUN_0011eb40(void *pool)
{
  char *pool_p = (char *)pool;
  unsigned int *last_block;

  if (pool == 0 || *(unsigned int *)(pool_p + 4) == 0) {
    display_assert("pool && pool->base_address",
                   "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x2fc, 1);
    system_exit(-1);
  }

  if (*(unsigned int *)(pool_p + 0x2c) == 0) {
    return *(unsigned int *)(pool_p + 8);
  }

  last_block = *(unsigned int **)(pool_p + 0x30);
  if (last_block == 0) {
    display_assert("block", "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c",
                   0x22f, 1);
    system_exit(-1);
  }

  return *(unsigned int *)(pool_p + 8) - (last_block[0] & 0x7fffffff) +
         *(unsigned int *)(pool_p + 4) - (unsigned int)last_block;
}

/* FUN_0011ebc0 — find first free slot index in pool slot table.
 *
 * Register convention: pool in EAX (kb.json @<eax>).
 * Returns slot index, or -1 if table is full.
 */
int FUN_0011ebc0(void *pool)
{
  char *pool_p = (char *)pool;
  unsigned int slot_count;
  unsigned int slot_index;
  unsigned int *slot_entry;

  if (pool == 0) {
    display_assert("pool", "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c",
                   0x310, 1);
    system_exit(-1);
  }

  slot_count = *(unsigned int *)(pool_p + 0xc);
  if (slot_count == 0) {
    return -1;
  }

  slot_index = 0;
  slot_entry = (unsigned int *)(pool_p + 0x34);
  while (*slot_entry != 0) {
    slot_index++;
    slot_entry++;
    if (slot_index >= slot_count) {
      return -1;
    }
  }

  return (int)slot_index;
}

/* FUN_0011ec10 — refresh pool->next_block_index from current table state.
 *
 * Register convention: pool in ESI (kb.json @<esi>).
 *
 * If next_block_index is set, scans forward for the next empty slot and stores
 * it; stores -1 when no empty slot remains.
 */
void FUN_0011ec10(void *pool)
{
  char *pool_p = (char *)pool;
  int slot_index;
  unsigned int slot_count;
  int *slot_entry;

  if (pool == 0) {
    display_assert("pool", "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c",
                   0x321, 1);
    system_exit(-1);
  }

  slot_index = *(int *)(pool_p + 0x10);
  if (slot_index == -1) {
    return;
  }

  slot_count = *(unsigned int *)(pool_p + 0xc);
  slot_index++;
  *(int *)(pool_p + 0x10) = -1;

  if ((unsigned int)slot_index >= slot_count) {
    return;
  }

  slot_entry = (int *)(pool_p + 0x34 + slot_index * 4);
  while (*slot_entry != 0) {
    slot_index++;
    slot_entry++;
    if ((unsigned int)slot_index >= slot_count) {
      return;
    }
  }

  *(int *)(pool_p + 0x10) = slot_index;
}

/* FUN_0011ec70 — find a free gap large enough for alloc_size.
 *
 * Register convention (kb.json):
 *   - pool in EAX (@<eax>)
 *   - alloc_size in EBX (@<ebx>)
 *   - free_space_in_pool_previous on stack
 *
 * Returns start address of a suitable free span, or NULL.
 * If the free span is between two blocks, writes the previous block header to
 * *free_space_in_pool_previous.
 */
void *FUN_0011ec70(void *pool, int alloc_size,
                   void **free_space_in_pool_previous)
{
  char *pool_p = (char *)pool;
  unsigned int *block;
  unsigned int *next;

  block = *(unsigned int **)(pool_p + 0x2c);
  if (block == 0) {
    return 0;
  }

  if ((unsigned int)alloc_size <=
      (unsigned int)((char *)block - *(char **)(pool_p + 4))) {
    return *(void **)(pool_p + 4);
  }

  next = *(unsigned int **)((char *)block + 0xc);
  if (next == 0) {
    return 0;
  }

  while (1) {
    if (block == 0) {
      display_assert("block", "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c",
                     0x22f, 1);
      system_exit(-1);
    }

    if ((unsigned int)alloc_size <=
        (unsigned int)((char *)next -
                       ((char *)block + (block[0] & 0x7fffffff)))) {
      break;
    }

    block = next;
    next = *(unsigned int **)((char *)next + 0xc);
    if (next == 0) {
      return 0;
    }
  }

  *free_space_in_pool_previous = block;
  return (char *)block + (block[0] & 0x7fffffff);
}

/* memory_block_valid — validate a block header's integrity.
 *
 * Checks three conditions on the block header pointed to by block_hdr:
 *   1. The usable size (low 31 bits of dword at +0x00) must be > 0x20
 *      (the block must have payload beyond the 0x20-byte header overhead).
 *   2. The "fryd" sentinel (0x66727964) at block_hdr+0x18 must be intact.
 *   3. The "chkn" sentinel (0x63686b6e) at block_hdr[usable_size - 4]
 *      must be intact (end-of-block canary).
 *
 * Returns 1 if all checks pass, 0 otherwise (after asserting on failure).
 *
 * Register convention: block_hdr passed in ECX (declared @<ecx> in kb.json).
 */
int memory_block_valid(void *block_hdr)
{
  unsigned int *p = (unsigned int *)block_hdr;
  unsigned int usable_size;

  if (p == 0) {
    return 0;
  }

  usable_size = p[0] & 0x7fffffff;

  if (usable_size == 0x20) {
    display_assert("!\"pointer has invalid size\"",
                   "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x1e4, 1);
    system_exit(-1);
    return 0;
  }

  if (p[6] != 0x66727964) {
    display_assert("!\"this memory has been corrupted\"",
                   "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x1e9, 1);
    system_exit(-1);
    return 0;
  }

  if (*(unsigned int *)((char *)p + usable_size - 4) != 0x63686b6e) {
    display_assert("!\"wrote beyond the valid address space for this block\"",
                   "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x1ee, 1);
    system_exit(-1);
    return 0;
  }

  return 1;
}

/* FUN_0011ee80 — compact unlocked blocks toward pool base.
 *
 * Register convention: pool in EAX (kb.json @<eax>).
 *
 * Walks blocks in address order and moves unlocked blocks down to remove gaps.
 */
void FUN_0011ee80(void *pool)
{
  char *pool_p = (char *)pool;
  unsigned int *block;
  char *previous_block;
  unsigned int previous_size;

  if (pool == 0 || *(unsigned int *)(pool_p + 4) == 0 || (pool_p + 0x34) == 0) {
    display_assert("pool && pool->base_address && pool->blocks",
                   "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x3ad, 1);
    system_exit(-1);
  }

  block = *(unsigned int **)(pool_p + 0x2c);
  if (block == 0 || *(unsigned char *)(pool_p + 0x28) != 0) {
    return;
  }

  previous_block = *(char **)(pool_p + 4);
  previous_size = 0;

  do {
    if (!(memory_block_valid(block) & 0xff)) {
      display_assert("memory_block_valid(block)",
                     "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x215, 1);
      system_exit(-1);
    }

    if ((int)block[0] >= 0) {
      int gap = (int)((char *)block - previous_size - previous_block);

      if (gap > 0) {
        unsigned int size = block[0] & 0x7fffffff;
        unsigned int *moved = (unsigned int *)(previous_block + previous_size);

        qmemcpy(moved, block, size);
        block = moved;

        if (block[2] != 0) {
          *(unsigned int **)(block[2] + 0xc) = block;
        }
      }
    }

    previous_size = block[0] & 0x7fffffff;
    previous_block = (char *)block;
    block = *(unsigned int **)((char *)block + 0xc);
  } while (block != 0);
}

/* stack_memory_pool_valid_block — verify a block belongs to a pool.
 *
 * Checks that block_hdr falls within the pool's address range
 * (base_address <= block_hdr < base_address + pool_size), then validates
 * the block's integrity via memory_block_valid. Finally, looks up the
 * block's slot index, fetches the corresponding slot-table entry, and
 * compares three header fields (dwords at +0, +8, +c) between the
 * slot-table pointer and block_hdr to ensure they match.
 *
 * Returns 1 if all checks pass, 0 otherwise.
 *
 * Register convention: block_hdr in EAX, pool in ECX (kb.json @<eax>/@<ecx>).
 *
 * Block header layout used:
 *   +0x00: size_flags (low 31 bits = usable_size, high bit = in-use)
 *   +0x04: slot_index
 *   +0x08: field at +8 (prev pointer in linked list)
 *   +0x0c: field at +c (next pointer in linked list)
 *
 * Pool header layout used:
 *   +0x04: base_address
 *   +0x08: pool_size
 *   +0x0c: slot_count
 *   +0x34: start of slot table (slot_count entries, 4 bytes each)
 */
int stack_memory_pool_valid_block(void *block_hdr, void *pool)
{
  unsigned int *blk = (unsigned int *)block_hdr;
  char *pool_p = (char *)pool;
  unsigned int *base;
  unsigned int *end;
  unsigned int slot_index;
  unsigned int *slot_entry;
  int valid;

  if (pool == 0 || *(unsigned int *)(pool_p + 4) == 0) {
    display_assert("pool && pool->base_address",
                   "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x3d7, 1);
    system_exit(-1);
  }

  base = *(unsigned int **)(pool_p + 4);
  end = (unsigned int *)((char *)base + *(unsigned int *)(pool_p + 8));

  if (blk < base || blk >= end) {
    return 0;
  }

  valid = memory_block_valid(block_hdr) & 0xff;
  if (!valid) {
    return 0;
  }

  /* Inline of block-slot-index getter (0x11eb10): assert block != NULL,
   * return dword at block_hdr+4. block_hdr is known non-NULL here. */
  slot_index = blk[1];

  if (slot_index >= *(unsigned int *)(pool_p + 0xc)) {
    return 0;
  }

  slot_entry = *(unsigned int **)(pool_p + 0x34 + slot_index * 4);
  if (slot_entry == 0) {
    return 0;
  }

  if (slot_entry[0] != blk[0]) {
    return 0;
  }
  if (slot_entry[2] != blk[2]) {
    return 0;
  }
  if (slot_entry[3] != blk[3]) {
    return 0;
  }

  return 1;
}

/* stack_memory_pool_unlink_block — remove a block from the pool's linked list.
 *
 * Validates the block belongs to this pool, then unlinks it from the
 * doubly-linked block list. Updates pool->first_block (+0x2c) and
 * pool->last_block (+0x30) if the removed block was at either end.
 * Clears the slot-table entry and updates pool->next_block_index (+0x10).
 *
 * Register convention: block_hdr in ESI, pool in EDI (kb.json @<esi>/@<edi>).
 *
 * Block header offsets used:
 *   +0x04: slot_index
 *   +0x08: prev pointer
 *   +0x0c: next pointer
 *
 * Pool header offsets used:
 *   +0x10: next_block_index
 *   +0x2c: first_block
 *   +0x30: last_block
 *   +0x34: slot table base
 */
void stack_memory_pool_unlink_block(void *block_hdr, void *pool)
{
  char *blk = (char *)block_hdr;
  char *pool_p = (char *)pool;
  unsigned int slot_index;
  unsigned int *prev;
  unsigned int *next;
  int valid;

  valid = stack_memory_pool_valid_block(block_hdr, pool) & 0xff;
  if (!valid) {
    display_assert("stack_memory_pool_valid_block(pool, reference)",
                   "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x2d3, 1);
    system_exit(-1);
  }

  if (blk == 0) {
    display_assert("block", "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c",
                   0x24a, 1);
    system_exit(-1);
  }

  slot_index = *(unsigned int *)(blk + 0x4);
  prev = *(unsigned int **)(blk + 0x8);
  next = *(unsigned int **)(blk + 0xc);

  /* Patch prev's next pointer. */
  if (prev != 0) {
    *(unsigned int *)((char *)prev + 0xc) = (unsigned int)next;
  }

  /* Patch next's prev pointer. */
  if (next != 0) {
    *(unsigned int *)((char *)next + 0x8) = (unsigned int)prev;
  }

  /* Update first_block if we unlinked it. */
  if ((unsigned int)blk == *(unsigned int *)(pool_p + 0x2c)) {
    *(unsigned int *)(pool_p + 0x2c) = (unsigned int)next;
  }

  /* Update last_block if we unlinked it. */
  if ((unsigned int)blk == *(unsigned int *)(pool_p + 0x30)) {
    *(unsigned int *)(pool_p + 0x30) = (unsigned int)prev;
  }

  /* Clear the slot-table entry. */
  *(unsigned int *)(pool_p + 0x34 + slot_index * 4) = 0;

  /* Update next_block_index: reuse the freed slot if pool still has blocks,
   * otherwise set to 0. Pattern: -(first_block != 0) & slot_index. */
  {
    unsigned int first_block = *(unsigned int *)(pool_p + 0x2c);
    unsigned int neg = -(first_block != 0);
    *(unsigned int *)(pool_p + 0x10) = neg & slot_index;
  }
}

/* stack_memory_pool_mark_used — mark a block as in-use and validate it.
 *
 * Verifies the block belongs to the pool and is not already locked
 * (high bit of size_flags at +0x00 must be clear). Then validates with
 * memory_block_valid, sets the high bit to mark the block in-use, and
 * validates again. Returns a pointer to the user data area (block_hdr + 0x1c).
 *
 * Register convention: block_hdr in ESI, pool in ECX (kb.json @<esi>/@<ecx>).
 *
 * Note: the return value (block_hdr + 0x1c) is placed in EAX but the kb.json
 * prototype declares void return. Callers in the original binary do not
 * use the return value.
 */
void stack_memory_pool_mark_used(void *block_hdr, void *pool)
{
  unsigned int *blk = (unsigned int *)block_hdr;
  int valid;

  valid = stack_memory_pool_valid_block(block_hdr, pool) & 0xff;

  if (!valid) {
    /* Fall through — but also check memory_block_valid and the locked flag
     * before reaching the combined assert. */
    goto combined_assert;
  }

  valid = memory_block_valid(block_hdr) & 0xff;
  if (!valid) {
    display_assert("memory_block_valid(block)",
                   "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x215, 1);
    system_exit(-1);
  }

  /* Check if block is already locked (high bit set). */
  if ((blk[0] >> 0x1f) & 1) {
    goto combined_assert;
  }

  goto do_mark;

combined_assert:
  display_assert("stack_memory_pool_valid_block(pool, reference) && "
                 "!memory_block_is_locked(reference)",
                 "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x2e5, 1);
  system_exit(-1);

do_mark:
  /* Validate block integrity before marking. */
  valid = memory_block_valid(block_hdr) & 0xff;
  if (!valid) {
    display_assert("memory_block_valid(block)",
                   "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x203, 1);
    system_exit(-1);
  }

  /* Set the high bit to mark the block as in-use. */
  blk[0] = blk[0] | 0x80000000;

  /* Validate block integrity after marking. */
  valid = memory_block_valid(block_hdr) & 0xff;
  if (!valid) {
    display_assert("memory_block_valid(block)",
                   "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x23f, 1);
    system_exit(-1);
  }
}

/* stack_memory_pool_alloc_internal — allocate a block header inside the pool.
 *
 * Register convention follows kb.json:
 *   - alloc_size in EAX (@<eax>)
 *   - pool/file/line on stack (cdecl order)
 *
 * Uses internal helpers in the same object to compact blocks, find free space,
 * choose a slot index, initialize block sentinels, and refresh next index.
 * Returns block header pointer on success, NULL on failure.
 */
void *stack_memory_pool_alloc_internal(int alloc_size, void *pool,
                                       const char *file, unsigned int line)
{
  char *pool_p = (char *)pool;
  char *free_space_in_pool_previous;
  char *block_hdr;
  unsigned int aligned_block_size;
  unsigned int largest_free;
  int slot_index;
  int free_space_found;

  if (pool == 0 || *(int *)(pool_p + 4) == 0) {
    display_assert("pool && pool->base_address",
                   "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x342, 1);
    system_exit(-1);
  }

  if (alloc_size == 0 || (unsigned int)alloc_size > 0x7fffffff ||
      *(unsigned int *)(pool_p + 8) <= (unsigned int)alloc_size) {
    display_assert("invalid size",
                   "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x3a4, 0);
    return 0;
  }

  free_space_in_pool_previous = 0;
  free_space_found = 0;

  aligned_block_size = (unsigned int)alloc_size + 0x20;
  while ((aligned_block_size & 3) != 0) {
    aligned_block_size++;
  }

  largest_free = FUN_0011eb40(pool);
  if (largest_free < aligned_block_size) {
    FUN_0011ee80(pool);
    largest_free = FUN_0011eb40(pool);
    if (largest_free < aligned_block_size) {
      free_space_found = (int)FUN_0011ec70(
        pool, aligned_block_size, (void **)&free_space_in_pool_previous);
      if (free_space_found == 0) {
        display_assert(
          "allocation from memory pool failed; unable to find sufficient space "
          "in the pool",
          "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x39f, 0);
        return 0;
      }
    }
  }

  if (*(int *)(pool_p + 0x10) == -1) {
    slot_index = FUN_0011ebc0(pool);
    *(int *)(pool_p + 0x10) = slot_index;
    if (slot_index == -1) {
      display_assert("the memory pool has no more unsused master pointers; you "
                     "need to use a "
                     "bigger pool",
                     "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x35f, 0);
    }
  }

  slot_index = *(int *)(pool_p + 0x10);
  if (slot_index == -1) {
    return 0;
  }

  if (free_space_found == 0) {
    if (*(int *)(pool_p + 0x2c) == 0) {
      *(unsigned int *)(pool_p + 0x34 + slot_index * 4) =
        *(unsigned int *)(pool_p + 4);
    } else {
      if (*(int *)(pool_p + 0x30) == 0) {
        display_assert("pool->last_block",
                       "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x370,
                       1);
        system_exit(-1);
      }

      *(int *)(pool_p + 0x34 + *(int *)(pool_p + 0x10) * 4) =
        FUN_0011ea90(*(void **)(pool_p + 0x30)) + *(int *)(pool_p + 0x30);
    }
  } else {
    *(int *)(pool_p + 0x34 + slot_index * 4) = free_space_found;
  }

  block_hdr = *(char **)(pool_p + 0x34 + *(int *)(pool_p + 0x10) * 4);
  FUN_0011ea50(*(int *)(pool_p + 0x10), block_hdr, aligned_block_size);
  *(const char **)(block_hdr + 0x10) = file;
  *(unsigned int *)(block_hdr + 0x14) = line;

  if (*(int *)(pool_p + 0x2c) == 0) {
    if (*(int *)(pool_p + 0x30) != 0 || *(int *)(pool_p + 0x10) != 0) {
      display_assert(
        "(pool->last_block == NULL) && (pool->next_block_index == 0)",
        "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x37d, 1);
      system_exit(-1);
    }

    *(char **)(pool_p + 0x30) = block_hdr;
    *(char **)(pool_p + 0x2c) = block_hdr;
    *(int *)(block_hdr + 8) = 0;
    *(int *)(block_hdr + 0xc) = 0;
    FUN_0011ec10(pool);
    return block_hdr;
  }

  if ((unsigned int)block_hdr < *(unsigned int *)(pool_p + 0x2c)) {
    *(int *)(block_hdr + 8) = 0;
    *(int *)(block_hdr + 0xc) = *(int *)(pool_p + 0x2c);
    *(int *)(*(int *)(pool_p + 0x2c) + 8) = (int)block_hdr;
    *(char **)(pool_p + 0x2c) = block_hdr;
    FUN_0011ec10(pool);
    return block_hdr;
  }

  if ((unsigned int)block_hdr > *(unsigned int *)(pool_p + 0x30)) {
    *(int *)(block_hdr + 0xc) = 0;
    *(int *)(block_hdr + 8) = *(int *)(pool_p + 0x30);
    *(int *)(*(int *)(pool_p + 0x30) + 0xc) = (int)block_hdr;
    *(char **)(pool_p + 0x30) = block_hdr;
    FUN_0011ec10(pool);
    return block_hdr;
  }

  if (free_space_in_pool_previous == 0) {
    display_assert("free_space_in_pool_previous",
                   "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x394, 1);
    system_exit(-1);
  }

  *(char **)(block_hdr + 8) = free_space_in_pool_previous;
  *(int *)(block_hdr + 0xc) = *(int *)(free_space_in_pool_previous + 0xc);
  *(char **)(free_space_in_pool_previous + 0xc) = block_hdr;
  if (*(int *)(block_hdr + 0xc) != 0) {
    *(int *)(*(int *)(block_hdr + 0xc) + 8) = (int)block_hdr;
  }

  FUN_0011ec10(pool);
  return block_hdr;
}

/* stack_memory_pool_deallocate — free a block back to the pool.
 *
 * Walks back 0x1c bytes from the user pointer to reach the block header,
 * validates the block belongs to this pool, unlinks it from the doubly-linked
 * list via the internal unlink_block helper, then subtracts the block's usable
 * size from pool->bytes_used and decrements pool->alloc_count.
 *
 * Pool struct offsets used here:
 *   +0x14: bytes_used  (uint32)
 *   +0x1c: alloc_count (int32)
 */
void stack_memory_pool_deallocate(void *pool, void *block)
{
  char *pool_p = (char *)pool;
  char *block_hdr;
  unsigned int size_flags;
  unsigned int usable_size;
  int valid;

  if (block == 0) {
    display_assert("block", "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c",
                   0x197, 1);
    system_exit(-1);
  }

  block_hdr = (char *)block - 0x1c;

  valid = stack_memory_pool_valid_block(block_hdr, pool) & 0xff;

  if (!valid) {
    display_assert("invalid pointer",
                   "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x19d, 1);
    system_exit(-1);
  }

  if (block_hdr == 0) {
    display_assert("block", "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c",
                   0x22f, 1);
    system_exit(-1);
  }

  size_flags = *(unsigned int *)block_hdr;
  usable_size = size_flags & 0x7fffffff;

  stack_memory_pool_unlink_block(block_hdr, pool);

  *(unsigned int *)(pool_p + 0x14) -= usable_size;
  *(int *)(pool_p + 0x1c) -= 1;
}

/* stack_memory_pool_alloc_or_resize — allocate new or grow existing block.
 *
 * Register convention (kb.json):
 *   - new_size in EAX (@<eax>)
 *   - pool in ECX (@<ecx>)
 *   - block_hdr/file/line on stack
 *
 * Returns block header pointer (not user pointer), or NULL on failure.
 */
void *stack_memory_pool_alloc_or_resize(int new_size, void *pool,
                                        void *block_hdr, const char *file,
                                        unsigned int line)
{
  char *old_hdr = (char *)block_hdr;
  char *new_hdr;
  unsigned int old_payload_size;
  int valid;

  if (new_size == 0) {
    return 0;
  }

  if (old_hdr == 0) {
    return stack_memory_pool_alloc_internal(new_size, pool, file, line);
  }

  valid = stack_memory_pool_valid_block(old_hdr, pool) & 0xff;
  if (!valid) {
    display_assert("stack_memory_pool_valid_block(pool, reference)",
                   "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x2b4, 1);
    system_exit(-1);
  }

  old_payload_size = FUN_0011ea90(old_hdr) - 0x20;
  if ((unsigned int)new_size <= old_payload_size) {
    return old_hdr;
  }

  new_hdr =
    (char *)stack_memory_pool_alloc_internal(new_size, pool, file, line);
  if (new_hdr == 0) {
    return 0;
  }

  valid = memory_block_valid(old_hdr) & 0xff;
  if (!valid) {
    display_assert("memory_block_valid(block)",
                   "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x23f, 1);
    system_exit(-1);
  }

  valid = memory_block_valid(new_hdr) & 0xff;
  if (!valid) {
    display_assert("memory_block_valid(block)",
                   "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x23f, 1);
    system_exit(-1);
  }

  csmemcpy(new_hdr + 0x1c, old_hdr + 0x1c, old_payload_size);
  stack_memory_pool_unlink_block(old_hdr, pool);
  return new_hdr;
}

/* stack_memory_pool_allocate — allocate a new block from the pool.
 *
 * Calls internal allocator 0x11f1e0 with EAX=size and stack args
 * [pool, file, line]. On success, marks the returned block in-use,
 * validates it, updates pool accounting, and returns user pointer
 * (block_hdr + 0x1c). Returns NULL on allocation failure.
 *
 * Pool struct offsets touched:
 *   +0x14: bytes_used
 *   +0x18: peak_bytes
 *   +0x1c: alloc_count
 *   +0x20: peak_alloc_count
 *   +0x24: largest_alloc
 */
void *stack_memory_pool_allocate(void *pool, int size, const char *file,
                                 unsigned int line)
{
  char *pool_p = (char *)pool;
  char *block_hdr;
  unsigned int size_flags;
  unsigned int usable_size;
  unsigned int alloc_count;
  unsigned int bytes_used;
  int valid;

  block_hdr = (char *)stack_memory_pool_alloc_internal(size, pool, file, line);

  if (block_hdr == 0) {
    return 0;
  }

  stack_memory_pool_mark_used(block_hdr, pool);

  valid = memory_block_valid(block_hdr) & 0xff;

  if (!valid) {
    display_assert("memory_block_valid(block)",
                   "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x23f, 1);
    system_exit(-1);
  }

  size_flags = *(unsigned int *)block_hdr;
  usable_size = size_flags & 0x7fffffff;

  bytes_used = *(unsigned int *)(pool_p + 0x14) + usable_size;
  *(unsigned int *)(pool_p + 0x14) = bytes_used;

  alloc_count = *(unsigned int *)(pool_p + 0x1c) + 1;
  *(unsigned int *)(pool_p + 0x1c) = alloc_count;

  if ((int)bytes_used > *(int *)(pool_p + 0x18)) {
    *(unsigned int *)(pool_p + 0x18) = bytes_used;
  }

  if (alloc_count > *(unsigned int *)(pool_p + 0x20)) {
    *(unsigned int *)(pool_p + 0x20) = alloc_count;
  }

  if (usable_size > *(unsigned int *)(pool_p + 0x24)) {
    *(unsigned int *)(pool_p + 0x24) = usable_size;
  }

  return (void *)(block_hdr + 0x1c);
}

/* stack_memory_pool_realloc — resize (or allocate) a block in the pool.
 *
 * If block == NULL: pure allocation (old_size = 0).
 * Otherwise: block_hdr = block - 0x1c, old_size = block_hdr[0] & 0x7fffffff.
 *
 * Delegates to the internal alloc_or_resize helper (0x11f750), which returns
 * the new block header pointer. On success, validates the new block, marks it
 * in-use if it was previously free (high bit clear), validates again, then
 * updates pool statistics:
 *   +0x14: bytes_used
 *   +0x18: peak_bytes
 *   +0x1c: alloc_count (incremented by 1 only when old block was NULL)
 *   +0x20: peak_alloc_count
 *   +0x24: largest_alloc
 *
 * Returns pointer to user data area (block_hdr + 0x1c), or NULL on failure.
 */
void *stack_memory_pool_realloc(void *pool, int block, unsigned short new_size,
                                const char *file, unsigned int line)
{
  char *pool_p = (char *)pool;
  char *block_hdr;
  char *new_hdr;
  unsigned int old_size;
  unsigned int new_size_flags;
  unsigned int new_usable;
  unsigned int alloc_count;
  unsigned int curr_bytes;
  int valid;

  if (block == 0) {
    block_hdr = 0;
  } else {
    block_hdr = (char *)block - 0x18;
  }
  old_size = 0;
  if (block_hdr != 0) {
    block_hdr = block_hdr - 4;
    if (block_hdr == 0) {
      display_assert("block", "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c",
                     0x22f, 1);
      system_exit(-1);
    }
    old_size = *(unsigned int *)block_hdr & 0x7fffffff;
  }

  new_hdr = (char *)stack_memory_pool_alloc_or_resize(
    (int)(unsigned int)new_size, pool, block_hdr, file, line);

  if (new_hdr == 0) {
    return 0;
  }

  valid = memory_block_valid(new_hdr) & 0xff;

  if (!valid) {
    display_assert("memory_block_valid(block)",
                   "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x215, 1);
    system_exit(-1);
  }

  new_size_flags = *(unsigned int *)new_hdr;
  if (!((new_size_flags >> 0x1f) & 1)) {
    stack_memory_pool_mark_used(new_hdr, pool);
  }

  valid = memory_block_valid(new_hdr) & 0xff;

  if (!valid) {
    display_assert("memory_block_valid(block)",
                   "c:\\halo\\SOURCE\\memory\\stack_memory_pool.c", 0x23f, 1);
    system_exit(-1);
  }

  new_usable = *(unsigned int *)new_hdr & 0x7fffffff;
  curr_bytes = *(unsigned int *)(pool_p + 0x14);
  curr_bytes += new_usable - old_size;
  *(unsigned int *)(pool_p + 0x14) = curr_bytes;

  alloc_count = *(unsigned int *)(pool_p + 0x1c);
  alloc_count += (old_size == 0) ? 1 : 0;
  *(unsigned int *)(pool_p + 0x1c) = alloc_count;

  if ((int)curr_bytes > *(int *)(pool_p + 0x18)) {
    *(unsigned int *)(pool_p + 0x18) = curr_bytes;
  }

  if (alloc_count > *(unsigned int *)(pool_p + 0x20)) {
    *(unsigned int *)(pool_p + 0x20) = alloc_count;
  }

  if (new_usable > *(unsigned int *)(pool_p + 0x24)) {
    *(unsigned int *)(pool_p + 0x24) = new_usable;
    return (void *)(new_hdr + 0x1c);
  }

  return (void *)(new_hdr + 0x1c);
}
/* --- stack_memory_pool.obj batch drafts (2026-07-26) --- */

/* memory_block_get_user_size (0x11eac0) — readable C lift. */
int memory_block_get_user_size(void *block)
{
  extern char DAT_002901b8[];
  extern char DAT_0029018c[];
  if (!block) {
    display_assert(DAT_002901b8, DAT_0029018c, 0x237, 1);
    system_exit(-1);
    display_assert(DAT_002901b8, DAT_0029018c, 0x22f, 1);
    system_exit(-1);
  }
  return (*(int *)block & 0x7fffffff) - 0x20;
}

/* FUN_0011eb10 (0x11eb10) — readable C lift. */
int FUN_0011eb10(void *pool /*@<esi>*/)
{
  extern char DAT_002901b8[];
  extern char DAT_0029018c[];
  if (!pool) {
    display_assert(DAT_002901b8, DAT_0029018c, 0x24a, 1);
    system_exit(-1);
  }
  return *(int *)((char *)pool + 4);
}

/* FUN_0011ee50 (0x11ee50) — readable C lift. */
void *FUN_0011ee50(void *pool)
{
  extern char DAT_00290254[];
  extern char DAT_0029018c[];
  if (!memory_block_valid(pool)) {
    display_assert(DAT_00290254, DAT_0029018c, 0x23f, 1);
    system_exit(-1);
  }
  return (char *)pool + 0x1c;
}

/* FUN_0011f140 (0x11f140) — XBE naked draft (batch 153). */
#if defined(__clang__)
static int (*const b11f140_c11ef50)(void *block_hdr, void *pool) = stack_memory_pool_valid_block;
static int (*const b11f140_c11ecf0)(void *block_hdr) = memory_block_valid;
static void (*const b11f140_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11f140_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_0011f140(void)
{
  __asm__ volatile(
      "movl %%esi, %%eax\n\t"
      "call *%[c11ef50]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0011f140_2\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c11ecf0]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0011f140_1\n\t"
      "pushl $1\n\t"
      "pushl $0x215\n\t"
      "pushl $0x29018c\n\t"
      "pushl $0x290254\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011f140_1:\n\t"
      "movl (%%esi), %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "testb $1, %%al\n\t"
      "jne .LFUN_0011f140_3\n\t"
      ".LFUN_0011f140_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x2f0\n\t"
      "pushl $0x29018c\n\t"
      "pushl $0x290328\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011f140_3:\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c11ecf0]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_0011f140_4\n\t"
      "pushl $1\n\t"
      "pushl $0x20c\n\t"
      "pushl $0x29018c\n\t"
      "pushl $0x290254\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011f140_4:\n\t"
      "andl $0x7fffffff, (%%esi)\n\t"
      "ret\n\t"
      :
      : [c11ef50] "m"(b11f140_c11ef50), [c11ecf0] "m"(b11f140_c11ecf0), [assert] "m"(b11f140_assert), [exitfn] "m"(b11f140_exitfn)
      : "memory");
}
#else
#error "FUN_0011f140: clang naked draft required"
#endif


/* dispose_handle (0x11f460) — readable C lift from XBE leaf. */
void dispose_handle(void *pool, void *block_hdr)
{
  unsigned int usable;

  if (!(stack_memory_pool_valid_block(block_hdr, pool) & 0xff)) {
    display_assert((const char *)0x2904a0, (const char *)0x29018c, 0xe8, 1);
    system_exit(-1);
  }
  if (!block_hdr) {
    display_assert((const char *)0x2901b8, (const char *)0x29018c, 0x22f, 1);
    system_exit(-1);
  }
  usable = *(unsigned int *)block_hdr & 0x7fffffff;
  stack_memory_pool_unlink_block(block_hdr, pool);
  *(unsigned int *)((char *)pool + 0x14) -= usable;
  *(unsigned int *)((char *)pool + 0x1c) -= 1;
}



/* lock_handle (0x11f4e0) — readable C lift from XBE leaf. */
void lock_handle(void *pool, void **handle_slot)
{
  void *block;

  if (!handle_slot) {
    display_assert((const char *)0x2904f8, (const char *)0x29018c, 0xf7, 1);
    system_exit(-1);
  }
  block = *handle_slot;
  if (!(stack_memory_pool_valid_block(block, pool) & 0xff)) {
    display_assert((const char *)0x2904c8, (const char *)0x29018c, 0xfa, 1);
    system_exit(-1);
  }
  stack_memory_pool_mark_used(block, pool);
  *handle_slot = (char *)block + 0x1c;
}



/* unlock_handle (0x11f550) — XBE naked draft (batch 137). */
#if defined(__clang__)
static void (*const b11f550_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11f550_exitfn)(int) = system_exit;
static int (*const b11f550_c11ecf0)(void *block_hdr) = memory_block_valid;
static void (*const b11f550_c11f140)(void) = FUN_0011f140;

__attribute__((naked, noinline))
void unlock_handle(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpl %%esi, %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "jne .Lunlock_handle_1\n\t"
      "pushl $1\n\t"
      "pushl $0x107\n\t"
      "pushl $0x29018c\n\t"
      "pushl $0x2904f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunlock_handle_1:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "cmpl %%esi, 0xc(%%ebx)\n\t"
      "jbe .Lunlock_handle_6\n\t"
      "addl $0x34, %%ebx\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lunlock_handle_2:\n\t"
      "movl (%%ebx), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lunlock_handle_4\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c11ecf0]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lunlock_handle_3\n\t"
      "pushl $1\n\t"
      "pushl $0x23f\n\t"
      "pushl $0x29018c\n\t"
      "pushl $0x290254\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunlock_handle_3:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $0x1c, %%edi\n\t"
      "cmpl %%eax, %%edi\n\t"
      "je .Lunlock_handle_5\n\t"
      ".Lunlock_handle_4:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "incl %%esi\n\t"
      "addl $4, %%ebx\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "jb .Lunlock_handle_2\n\t"
      "jmp .Lunlock_handle_6\n\t"
      ".Lunlock_handle_5:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x34(%%ecx,%%esi,4), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "jne .Lunlock_handle_7\n\t"
      ".Lunlock_handle_6:\n\t"
      "pushl $1\n\t"
      "pushl $0x111\n\t"
      "pushl $0x29018c\n\t"
      "pushl $0x2904fc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lunlock_handle_7:\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "call *%[c11f140]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b11f550_assert), [exitfn] "m"(b11f550_exitfn), [c11ecf0] "m"(b11f550_c11ecf0), [c11f140] "m"(b11f550_c11f140)
      : "memory");
}
#else
#error "unlock_handle: clang naked draft required"
#endif


/* FUN_0011f6d0 (0x11f6d0) — readable C lift from XBE leaf.
 * Thin wrapper: size on stack, pool@edx, file@ecx, line@eax → alloc_internal. */
void *FUN_0011f6d0(int alloc_size, void *pool /* @<edx> */, const char *file /* @<ecx> */,
                   unsigned int line /* @<eax> */)
{
  return stack_memory_pool_alloc_internal(alloc_size, pool, file, line);
}

/* pool_new_handle (0x11f810) — readable C lift from XBE leaf. */
void *pool_new_handle(void *pool, int alloc_size, const char *file, unsigned int line)
{
  void *block;
  unsigned int usable;
  unsigned int bytes_used;
  unsigned int alloc_count;

  block = stack_memory_pool_alloc_internal(alloc_size, pool, file, line);
  if (!block) {
    return 0;
  }
  usable = *(unsigned int *)block & 0x7fffffff;
  bytes_used = *(unsigned int *)((char *)pool + 0x14) + usable;
  alloc_count = *(unsigned int *)((char *)pool + 0x1c) + 1;
  *(unsigned int *)((char *)pool + 0x14) = bytes_used;
  *(unsigned int *)((char *)pool + 0x1c) = alloc_count;
  if ((int)bytes_used > *(int *)((char *)pool + 0x18)) {
    *(unsigned int *)((char *)pool + 0x18) = bytes_used;
  }
  if (alloc_count > *(unsigned int *)((char *)pool + 0x20)) {
    *(unsigned int *)((char *)pool + 0x20) = alloc_count;
  }
  if (usable > *(unsigned int *)((char *)pool + 0x24)) {
    *(unsigned int *)((char *)pool + 0x24) = usable;
  }
  return block;
}



/* pool_new_handle_clear (0x11f880) — XBE naked draft (batch 137). */
#if defined(__clang__)
static void * (*const b11f880_c11f1e0)(int alloc_size, void *pool, const char *file, unsigned int line) = stack_memory_pool_alloc_internal;
static int (*const b11f880_c11ecf0)(void *block_hdr) = memory_block_valid;
static void (*const b11f880_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11f880_exitfn)(int) = system_exit;
static void *(*const b11f880_memset)(void *, int, unsigned int) = csmemset;

__attribute__((naked, noinline))
void pool_new_handle_clear(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c11f1e0]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lpool_new_handle_clear_5\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c11ecf0]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lpool_new_handle_clear_1\n\t"
      "pushl $1\n\t"
      "pushl $0x23f\n\t"
      "pushl $0x29018c\n\t"
      "pushl $0x290254\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpool_new_handle_clear_1:\n\t"
      "pushl %%ebx\n\t"
      "leal 0x1c(%%edi), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "movl 0x1c(%%esi), %%ebx\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl %%ecx, 0x14(%%esi)\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "incl %%ebx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "movl %%ebx, 0x1c(%%esi)\n\t"
      "movl %%ebx, %%ecx\n\t"
      "jle .Lpool_new_handle_clear_2\n\t"
      "movl %%eax, 0x18(%%esi)\n\t"
      ".Lpool_new_handle_clear_2:\n\t"
      "cmpl 0x20(%%esi), %%ecx\n\t"
      "jbe .Lpool_new_handle_clear_3\n\t"
      "movl %%ecx, 0x20(%%esi)\n\t"
      ".Lpool_new_handle_clear_3:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl 0x24(%%esi), %%ecx\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jbe .Lpool_new_handle_clear_4\n\t"
      "movl %%eax, 0x24(%%esi)\n\t"
      ".Lpool_new_handle_clear_4:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lpool_new_handle_clear_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c11f1e0] "m"(b11f880_c11f1e0), [c11ecf0] "m"(b11f880_c11ecf0), [assert] "m"(b11f880_assert), [exitfn] "m"(b11f880_exitfn), [memset] "m"(b11f880_memset)
      : "memory");
}
#else
#error "pool_new_handle_clear: clang naked draft required"
#endif


/* pool_resize_handle (0x11f930) — XBE naked draft (batch 128). */
#if defined(__clang__)
static void (*const b11f930_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11f930_exitfn)(int) = system_exit;
static int (*const b11f930_c11ef50)(void *block_hdr, void *pool) = stack_memory_pool_valid_block;
static void * (*const b11f930_c11f750)(int new_size, void *pool, void *block_hdr, const char *file, unsigned int line) = stack_memory_pool_alloc_or_resize;
static unsigned int (*const b11f930_c11ea90)(void *block_hdr) = FUN_0011ea90;

__attribute__((naked, noinline))
void pool_resize_handle(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .Lpool_resize_handle_1\n\t"
      "pushl $1\n\t"
      "pushl $0xc1\n\t"
      "pushl $0x29018c\n\t"
      "pushl $0x2904f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpool_resize_handle_1:\n\t"
      "movl (%%esi), %%ebx\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl %%ebx, %%eax\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c11ef50]\n\t"
      "testb %%al, %%al\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "jne .Lpool_resize_handle_3\n\t"
      "pushl $1\n\t"
      "pushl $0xc5\n\t"
      "pushl $0x29018c\n\t"
      "pushl $0x290538\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpool_resize_handle_2:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lpool_resize_handle_3:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .Lpool_resize_handle_4\n\t"
      "pushl $1\n\t"
      "pushl $0x22f\n\t"
      "pushl $0x29018c\n\t"
      "pushl $0x2901b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpool_resize_handle_4:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl (%%ebx), %%esi\n\t"
      "pushl %%eax\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl %%edi, %%ecx\n\t"
      "andl $0x7fffffff, %%esi\n\t"
      "call *%[c11f750]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lpool_resize_handle_6\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x18(%%edi), %%edx\n\t"
      "andl $0x7fffffff, %%ecx\n\t"
      "subl %%esi, %%ecx\n\t"
      "movl 0x14(%%edi), %%esi\n\t"
      "addl %%ecx, %%esi\n\t"
      "movl %%esi, %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "movl %%esi, 0x14(%%edi)\n\t"
      "jle .Lpool_resize_handle_5\n\t"
      "movl %%ecx, 0x18(%%edi)\n\t"
      ".Lpool_resize_handle_5:\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl 0x24(%%edi), %%ecx\n\t"
      "andl $0x7fffffff, %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jbe .Lpool_resize_handle_2\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c11ea90]\n\t"
      "movl %%eax, 0x24(%%edi)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lpool_resize_handle_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b11f930_assert), [exitfn] "m"(b11f930_exitfn), [c11ef50] "m"(b11f930_c11ef50), [c11f750] "m"(b11f930_c11f750), [c11ea90] "m"(b11f930_c11ea90)
      : "memory");
}
#else
#error "pool_resize_handle: clang naked draft required"
#endif


/* pool_new_pointer_clear (0x11faf0) — XBE naked draft (batch 132). */
#if defined(__clang__)
static void * (*const b11faf0_c11f1e0)(int alloc_size, void *pool, const char *file, unsigned int line) = stack_memory_pool_alloc_internal;
static int (*const b11faf0_c11ecf0)(void *block_hdr) = memory_block_valid;
static void (*const b11faf0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11faf0_exitfn)(int) = system_exit;
static void *(*const b11faf0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b11faf0_c11f070)(void *block_hdr, void *pool) = stack_memory_pool_mark_used;

__attribute__((naked, noinline))
void pool_new_pointer_clear(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "call *%[c11f1e0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lpool_new_pointer_clear_5\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c11ecf0]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lpool_new_pointer_clear_1\n\t"
      "pushl $1\n\t"
      "pushl $0x23f\n\t"
      "pushl $0x29018c\n\t"
      "pushl $0x290254\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpool_new_pointer_clear_1:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x1c(%%esi), %%ebx\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%edi, %%ecx\n\t"
      "call *%[c11f070]\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c11ecf0]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lpool_new_pointer_clear_2\n\t"
      "pushl $1\n\t"
      "pushl $0x23f\n\t"
      "pushl $0x29018c\n\t"
      "pushl $0x290254\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpool_new_pointer_clear_2:\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl 0x14(%%edi), %%ecx\n\t"
      "movl 0x18(%%edi), %%edx\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl 0x1c(%%edi), %%eax\n\t"
      "incl %%eax\n\t"
      "movl %%ecx, 0x14(%%edi)\n\t"
      "movl %%eax, 0x1c(%%edi)\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl 0x14(%%edi), %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jle .Lpool_new_pointer_clear_3\n\t"
      "movl %%eax, 0x18(%%edi)\n\t"
      ".Lpool_new_pointer_clear_3:\n\t"
      "cmpl 0x20(%%edi), %%ecx\n\t"
      "jbe .Lpool_new_pointer_clear_4\n\t"
      "movl %%ecx, 0x20(%%edi)\n\t"
      ".Lpool_new_pointer_clear_4:\n\t"
      "movl (%%esi), %%esi\n\t"
      "movl 0x24(%%edi), %%eax\n\t"
      "andl $0x7fffffff, %%esi\n\t"
      "cmpl %%eax, %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "jbe .Lpool_new_pointer_clear_6\n\t"
      "movl %%esi, 0x24(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lpool_new_pointer_clear_5:\n\t"
      "movl %%ebx, %%eax\n\t"
      ".Lpool_new_pointer_clear_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c11f1e0] "m"(b11faf0_c11f1e0), [c11ecf0] "m"(b11faf0_c11ecf0), [assert] "m"(b11faf0_assert), [exitfn] "m"(b11faf0_exitfn), [memset] "m"(b11faf0_memset), [c11f070] "m"(b11faf0_c11f070)
      : "memory");
}
#else
#error "pool_new_pointer_clear: clang naked draft required"
#endif


/* FUN_0011fd10 (0x11fd10) — readable C lift. */
float FUN_0011fd10(void *block, char use_alt)
{
  int numerator;
  int denominator;

  if (use_alt)
    numerator = *(int *)((char *)block + 0x14);
  else
    numerator = *(int *)((char *)block + 0x10);
  denominator = (int)*(int16_t *)((char *)block + 0xa) *
                (int)*(int16_t *)((char *)block + 8);
  return (float)numerator / (float)denominator;
}

/* FUN_0011fd50 (0x11fd50) — readable C lift. */
void FUN_0011fd50(void *pool)
{
  extern char DAT_002905a0[];
  extern char DAT_002905b0[];
  extern char DAT_00290570[];
  if (!pool) {
    display_assert(DAT_002905a0, DAT_002905b0, 0x104, 1);
    system_exit(-1);
  }
  if (*(int16_t *)((char *)pool + 8) <= 0 || *(int16_t *)((char *)pool + 0xa) <= 0) {
    display_assert(DAT_00290570, DAT_002905b0, 0x105, 1);
    system_exit(-1);
  }
  data_verify(*(data_t **)((char *)pool + 0x18));
}

/* FUN_0011fdb0 (0x11fdb0) — XBE naked draft (batch 137). */
#if defined(__clang__)
static void * (*const b11fdb0_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b11fdb0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11fdb0_exitfn)(int) = system_exit;
static void *(*const b11fdb0_memset)(void *, int, unsigned int) = csmemset;
static data_t * (*const b11fdb0_c1194d0)(char *name, int16_t maximum_count, int16_t size) = data_new;
static void (*const b11fdb0_c119b20)(data_t *data) = data_delete_all;
static void (*const b11fdb0_c11fd50)(void) = FUN_0011fd50;
static void (*const b11fdb0_c8ef70)(void *ptr, const char *file, int line) = debug_free;

__attribute__((naked, noinline))
void FUN_0011fdb0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x1d\n\t"
      "pushl $0x2905b0\n\t"
      "pushl $0\n\t"
      "pushl $0x1c\n\t"
      "call *%[c8ee60]\n\t"
      "movw 0xc(%%ebp), %%di\n\t"
      "movw 0x10(%%ebp), %%bx\n\t"
      "addl $0x10, %%esp\n\t"
      "testw %%di, %%di\n\t"
      "movl %%eax, %%esi\n\t"
      "jle .LFUN_0011fdb0_1\n\t"
      "testw %%bx, %%bx\n\t"
      "jg .LFUN_0011fdb0_2\n\t"
      ".LFUN_0011fdb0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x1f\n\t"
      "pushl $0x2905b0\n\t"
      "pushl $0x2905f0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011fdb0_2:\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_0011fdb0_4\n\t"
      "pushl $0x1c\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "movw 0x14(%%ebp), %%ax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0xc\n\t"
      "movw %%di, 0x8(%%esi)\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl $0x7fff\n\t"
      "pushl $0x2905d8\n\t"
      "movw %%bx, 0xa(%%esi)\n\t"
      "movw %%ax, 0xc(%%esi)\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      "movl %%edi, 0x10(%%esi)\n\t"
      "movl %%edi, 0x14(%%esi)\n\t"
      "movb $0, (%%esi)\n\t"
      "call *%[c1194d0]\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%eax, 0x18(%%esi)\n\t"
      "je .LFUN_0011fdb0_3\n\t"
      "pushl %%eax\n\t"
      "call *%[c119b20]\n\t"
      "addl $4, %%esp\n\t"
      "call *%[c11fd50]\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011fdb0_3:\n\t"
      "pushl $0x38\n\t"
      "pushl $0x2905b0\n\t"
      "pushl %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0011fdb0_4:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8ee60] "m"(b11fdb0_c8ee60), [assert] "m"(b11fdb0_assert), [exitfn] "m"(b11fdb0_exitfn), [memset] "m"(b11fdb0_memset), [c1194d0] "m"(b11fdb0_c1194d0), [c119b20] "m"(b11fdb0_c119b20), [c11fd50] "m"(b11fdb0_c11fd50), [c8ef70] "m"(b11fdb0_c8ef70)
      : "memory");
}
#else
#error "FUN_0011fdb0: clang naked draft required"
#endif


/* FUN_0011fe80 (0x11fe80) — readable C lift. */
void FUN_0011fe80(void *pool)
{
  extern char DAT_002905b0[];
  FUN_0011fd50(pool);
  data_dispose(*(data_t **)((char *)pool + 0x18));
  debug_free(pool, DAT_002905b0, 0x45);
}

/* FUN_0011feb0 (0x11feb0) — readable C lift. */
void FUN_0011feb0(void *pool)
{
  extern char DAT_00290610[];
  extern char DAT_002905b0[];
  FUN_0011fd50(pool);
  if (*(unsigned char *)pool != 0) {
    display_assert(DAT_00290610, DAT_002905b0, 0x4e, 1);
    system_exit(-1);
  }
  *(unsigned char *)pool = 1;
}

/* FUN_0011fef0 (0x11fef0) — readable C lift. */
void *FUN_0011fef0(void *pool, int handle)
{
  FUN_0011fd50(pool);
  return datum_get(*(data_t **)((char *)pool + 0x18), handle);
}

/* FUN_0011ff10 (0x11ff10) — readable C lift. */
int FUN_0011ff10(int16_t a, int16_t b)
{
  void *pool = *(void **)0x46e808;
  void *da;
  void *db;
  FUN_0011fd50(pool);
  FUN_0011fd50(pool);
  da = datum_get(*(void **)((char *)pool + 0x18), a);
  db = datum_get(*(void **)((char *)pool + 0x18), b);
  return (*(int16_t *)((char *)db + 0xa) - *(int16_t *)((char *)da + 0xa)) > 0;
}

/* FUN_0011ff70 (0x11ff70) — XBE naked draft (batch 112). */
#if defined(__clang__)
static void (*const b11ff70_chkstk)(void) = FUN_001d90e0;
static void (*const b11ff70_c108e20)(void) = (void *)FUN_00108e20;
static void (*const b11ff70_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11ff70_exitfn)(int) = system_exit;
static void (*const b11ff70_c11fd50)(void) = FUN_0011fd50;
static void (*const b11ff70_c91da0)(void) = FUN_00091da0;
static void (*const b11ff70_c1193f0)(data_t *data) = data_verify;
static void *(*const b11ff70_dget)(void *, int) = (void *(*)(void *, int))datum_get;

__attribute__((naked, noinline))
char FUN_0011ff70(void *anim __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x10c24, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0xc(%%edi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_0011ff70_1\n\t"
      "pushl %%eax\n\t"
      "call *%[c108e20]\n\t"
      "movswl 0xc(%%edi), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_0011ff70_1\n\t"
      "pushl $1\n\t"
      "pushl $0x124\n\t"
      "pushl $0x2905b0\n\t"
      "pushl $0x290668\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011ff70_1:\n\t"
      "movl %%edi, %%esi\n\t"
      "call *%[c11fd50]\n\t"
      "movl 0x18(%%edi), %%ecx\n\t"
      "movl 0x34(%%ecx), %%edx\n\t"
      "xorl %%esi, %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw %%ax, 0x2e(%%ecx)\n\t"
      "movl %%esi, -0x24(%%ebp)\n\t"
      "jle .LFUN_0011ff70_4\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0011ff70_2:\n\t"
      "cmpw $0, (%%edx)\n\t"
      "je .LFUN_0011ff70_3\n\t"
      "movswl %%si, %%ebx\n\t"
      "movw %%ax, -0x10c24(%%ebp,%%ebx,2)\n\t"
      "incl %%esi\n\t"
      ".LFUN_0011ff70_3:\n\t"
      "incl %%eax\n\t"
      "addl $0xc, %%edx\n\t"
      "cmpw 0x2e(%%ecx), %%ax\n\t"
      "jl .LFUN_0011ff70_2\n\t"
      "movl %%esi, -0x24(%%ebp)\n\t"
      ".LFUN_0011ff70_4:\n\t"
      "movswl %%si, %%edx\n\t"
      "pushl $0x11ff10\n\t"
      "pushl %%edx\n\t"
      "leal -0x10c24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, 0x46e808\n\t"
      "call *%[c91da0]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $1, %%si\n\t"
      "jle .LFUN_0011ff70_5\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0xc(%%edi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LFUN_0011ff70_6\n\t"
      "pushl %%eax\n\t"
      "call *%[c108e20]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $4, %%esp\n\t"
      "decl %%ebx\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "jmp .LFUN_0011ff70_7\n\t"
      ".LFUN_0011ff70_5:\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      ".LFUN_0011ff70_6:\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      ".LFUN_0011ff70_7:\n\t"
      "movw 0xa(%%edi), %%cx\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw %%ax, %%si\n\t"
      "movl %%eax, 0x14(%%edi)\n\t"
      "movl $1, -0x8(%%ebp)\n\t"
      "movw %%ax, -0xc24(%%ebp)\n\t"
      "movw %%ax, -0xc22(%%ebp)\n\t"
      "movw %%cx, -0xc20(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jle .LFUN_0011ff70_19\n\t"
      "jmp .LFUN_0011ff70_8\n\t"
      "leal (%%esp), %%esp\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0011ff70_8:\n\t"
      "cmpw %%ax, 0x8(%%edi)\n\t"
      "movswl -0x14(%%ebp), %%edx\n\t"
      "movswl -0x10c24(%%ebp,%%edx,2), %%esi\n\t"
      "jle .LFUN_0011ff70_9\n\t"
      "cmpw %%ax, 0xa(%%edi)\n\t"
      "jg .LFUN_0011ff70_10\n\t"
      ".LFUN_0011ff70_9:\n\t"
      "pushl $1\n\t"
      "pushl $0x105\n\t"
      "pushl $0x2905b0\n\t"
      "pushl $0x290570\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011ff70_10:\n\t"
      "movl 0x18(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1193f0]\n\t"
      "movl 0x18(%%edi), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "movw 0xa(%%edx), %%si\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x8(%%edx), %%ax\n\t"
      "addl %%ecx, %%ecx\n\t"
      "addw %%cx, %%ax\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "addw %%cx, %%si\n\t"
      "movl %%eax, %%edx\n\t"
      "andl %%ebx, %%edx\n\t"
      "testw %%dx, %%dx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "je .LFUN_0011ff70_11\n\t"
      "movl %%ebx, %%ecx\n\t"
      "notl %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "addl -0x4(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%ecx, %%eax\n\t"
      ".LFUN_0011ff70_11:\n\t"
      "movl %%esi, %%edx\n\t"
      "andl %%ebx, %%edx\n\t"
      "testw %%dx, %%dx\n\t"
      "je .LFUN_0011ff70_12\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "notl %%ebx\n\t"
      "andl %%esi, %%ebx\n\t"
      "addl %%ecx, %%ebx\n\t"
      "movl %%ebx, %%esi\n\t"
      ".LFUN_0011ff70_12:\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpw %%dx, -0x8(%%ebp)\n\t"
      "jle .LFUN_0011ff70_15\n\t"
      "movswl 0x8(%%edi), %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "jmp .LFUN_0011ff70_13\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0011ff70_13:\n\t"
      "movl -0x18(%%ebp), %%ebx\n\t"
      "movswl %%dx, %%ecx\n\t"
      "leal (%%ecx,%%ecx,2), %%ecx\n\t"
      "movswl -0xc24(%%ebp,%%ecx,2), %%edi\n\t"
      "leal -0xc24(%%ebp,%%ecx,2), %%ecx\n\t"
      "subl %%edi, %%ebx\n\t"
      "cmpl %%ebx, -0x20(%%ebp)\n\t"
      "jg .LFUN_0011ff70_14\n\t"
      "cmpw 0x4(%%ecx), %%si\n\t"
      "jle .LFUN_0011ff70_16\n\t"
      ".LFUN_0011ff70_14:\n\t"
      "incl %%edx\n\t"
      "cmpw -0x8(%%ebp), %%dx\n\t"
      "jl .LFUN_0011ff70_13\n\t"
      ".LFUN_0011ff70_15:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011ff70_16:\n\t"
      "cmpw -0x8(%%ebp), %%dx\n\t"
      "jge .LFUN_0011ff70_15\n\t"
      "movswl %%dx, %%ecx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "leal (%%ecx,%%ecx,2), %%edi\n\t"
      "movw -0xc20(%%ebp,%%edi,2), %%bx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw -0xc24(%%ebp,%%edi,2), %%cx\n\t"
      "leal -0xc24(%%ebp,%%edi,2), %%edi\n\t"
      "subw %%si, %%bx\n\t"
      "addl %%edx, %%ecx\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movw %%cx, 0x4(%%edx)\n\t"
      "movw 0x2(%%edi), %%cx\n\t"
      "addw -0x4(%%ebp), %%cx\n\t"
      "testw %%bx, %%bx\n\t"
      "movw %%cx, 0x6(%%edx)\n\t"
      "je .LFUN_0011ff70_18\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movswl %%dx, %%ecx\n\t"
      "leal (%%ecx,%%ecx,2), %%ecx\n\t"
      "incl %%edx\n\t"
      "cmpw $0x200, %%dx\n\t"
      "leal -0xc24(%%ebp,%%ecx,2), %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jl .LFUN_0011ff70_17\n\t"
      "pushl $1\n\t"
      "pushl $0x168\n\t"
      "pushl $0x2905b0\n\t"
      "pushl $0x29063c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011ff70_17:\n\t"
      "movw (%%edi), %%dx\n\t"
      "movw %%dx, (%%ecx)\n\t"
      "movw 0x2(%%edi), %%dx\n\t"
      "addw %%si, %%dx\n\t"
      "movw %%dx, 0x2(%%ecx)\n\t"
      "movw %%bx, 0x4(%%ecx)\n\t"
      ".LFUN_0011ff70_18:\n\t"
      "addw %%ax, (%%edi)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movswl %%si, %%ecx\n\t"
      "imull -0x20(%%ebp), %%ecx\n\t"
      "movw %%si, 0x4(%%edi)\n\t"
      "addl %%ecx, 0x14(%%eax)\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw -0x24(%%ebp), %%ax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jge .LFUN_0011ff70_19\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_0011ff70_8\n\t"
      ".LFUN_0011ff70_19:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(b11ff70_chkstk), [c108e20] "m"(b11ff70_c108e20), [assert] "m"(b11ff70_assert), [exitfn] "m"(b11ff70_exitfn), [c11fd50] "m"(b11ff70_c11fd50), [c91da0] "m"(b11ff70_c91da0), [c1193f0] "m"(b11ff70_c1193f0), [dget] "m"(b11ff70_dget)
      : "memory");
}
#else
#error "FUN_0011ff70: clang naked draft required"
#endif

