/* Returns required allocation size for a memory pool of given capacity
 * (0x11e330). */
int memory_pool_allocation_size(int pool_config)
{
  return pool_config + 0x38;
}

/* Initialize a memory pool in pre-allocated memory (0x11e340).
 * Zeroes 0x38-byte header, sets signature/name/pointers. */
void memory_pool_initialize(void *pool, const char *name, int pool_config)
{
  unsigned int *p = (unsigned int *)pool;
  csmemset(pool, 0, 0x38);
  p[0] = 0x706f6f6c;
  csstrncpy((char *)(p + 1), name, 0x1f);
  p[9] = (unsigned int)(p + 0xe);
  p[10] = (unsigned int)pool_config;
  p[0xb] = (unsigned int)pool_config;
  p[0xc] = 0;
  p[0xd] = 0;
}

/* Returns pool->free_size (0x11e390). */
int memory_pool_get_free_size(void *pool)
{
  return *(int *)((char *)pool + 0x2c);
}

/* Returns bytes used (end of last block minus base address), 0 if empty
 * (0x11e3a0). */
int memory_pool_get_used_size(void *pool)
{
  int last_block = *(int *)((char *)pool + 0x34);
  if (last_block == 0)
    return 0;
  return (*(int *)(last_block + 4) - *(int *)((char *)pool + 0x24)) +
         last_block;
}

/* Returns contiguous free space from end of last block to end of pool
 * (0x11e3c0). If no blocks, returns pool->size. */
int memory_pool_get_contiguous_free_size(void *pool)
{
  char *p = (char *)pool;
  int last_block = *(int *)(p + 0x34);
  int used;

  if (last_block == 0) {
    used = 0;
  } else {
    used = (*(int *)(last_block + 4) - *(int *)(p + 0x24)) + last_block;
  }
  return *(int *)(p + 0x28) - used;
}

/* Returns the next allocation point if size bytes can fit after the last block,
 * 0 otherwise (0x11e400). pool passed in EAX, size on stack. */
unsigned int FUN_0011e400(void *pool, int size)
{
  char *p = (char *)pool;
  int last_block;
  unsigned int alloc_point;

  last_block = *(int *)(p + 0x34);
  if (last_block != 0) {
    alloc_point = *(int *)(last_block + 4) + last_block;
  } else {
    alloc_point = *(unsigned int *)(p + 0x24);
  }
  return ~-(unsigned int)(*(unsigned int *)(p + 0x28) +
                            *(unsigned int *)(p + 0x24) <
                          (unsigned int)size + alloc_point) &
         alloc_point;
}

/* Validate pool structure and all blocks in the linked list (0x11e430).
 * Checks pool/block signatures, linked list consistency, and address bounds. */
void FUN_0011e430(void *pool)
{
  char *p = (char *)pool;
  char *block;
  char *previous_block;

  if (*(int *)p != 0x706f6f6c) {
    display_assert("pool->signature==POOL_SIGNATURE",
                   "c:\\halo\\SOURCE\\memory\\memory_pool.c", 0x154, 1);
    system_exit(-1);
  }

  if (*(int *)(p + 0x28) <= 0) {
    display_assert("pool->size>0", "c:\\halo\\SOURCE\\memory\\memory_pool.c",
                   0x155, 1);
    system_exit(-1);
  }

  block = *(char **)(p + 0x30);
  previous_block = NULL;

  while (block != NULL) {
    if (*(char **)(block + 0x10) != previous_block) {
      display_assert("block->previous_block==previous_block",
                     "c:\\halo\\SOURCE\\memory\\memory_pool.c", 0x160, 1);
      system_exit(-1);
    }

    if (*(int *)(block + 0x0c) == 0 && *(char **)(p + 0x34) != block) {
      display_assert("block->next_block || pool->last_block==block",
                     "c:\\halo\\SOURCE\\memory\\memory_pool.c", 0x161, 1);
      system_exit(-1);
    }

    if (*(int *)block != 0x68656164) {
      display_assert("block->header_signature==BLOCK_HEADER_SIGNATURE",
                     "c:\\halo\\SOURCE\\memory\\memory_pool.c", 0x163, 1);
      system_exit(-1);
    }

    if (*(int *)(block + 0x14) != 0x7461696c) {
      display_assert("block->trailer_signature==BLOCK_TRAILER_SIGNATURE",
                     "c:\\halo\\SOURCE\\memory\\memory_pool.c", 0x164, 1);
      system_exit(-1);
    }

    if ((unsigned int)block < (unsigned int)*(int *)(p + 0x24)) {
      display_assert("(byte *)block>=(byte *)pool->base_address",
                     "c:\\halo\\SOURCE\\memory\\memory_pool.c", 0x166, 1);
      system_exit(-1);
    }

    if ((unsigned int)(*(int *)(block + 0x04) + (int)block) >
        (unsigned int)(*(int *)(p + 0x28) + *(int *)(p + 0x24))) {
      display_assert(
        "(byte *)block+block->size<=(byte *)pool->base_address+pool->size",
        "c:\\halo\\SOURCE\\memory\\memory_pool.c", 0x167, 1);
      system_exit(-1);
    }

    previous_block = block;
    block = *(char **)(block + 0x0c);
  }
}

/* Validate a block reference and return the block header pointer (0x11e5a0).
 * Checks that the reference is non-null, verifies pool integrity, confirms
 * the block's stored reference matches, and walks the list to find it. */
void *FUN_0011e5a0(void *pool, void **block_reference)
{
  char *p = (char *)pool;
  char *data;
  char *block;
  char *other_block;

  if (block_reference == NULL || *block_reference == NULL) {
    display_assert("reference && (*reference)",
                   "c:\\halo\\SOURCE\\memory\\memory_pool.c", 0x174, 1);
    system_exit(-1);
  }

  FUN_0011e430(pool);

  data = (char *)*block_reference;
  block = data - 0x18;

  if (*(void **)(data - 0x10) != (void *)block_reference) {
    char *msg =
      csprintf((char *)0x5ab100, "expected reference %08x but got %08x",
               *(int *)(data - 0x10), (int)block_reference);
    display_assert(msg, "c:\\halo\\SOURCE\\memory\\memory_pool.c", 0x17b, 1);
    system_exit(-1);
  }

  other_block = *(char **)(p + 0x30);
  while (other_block != NULL) {
    if (block == other_block)
      return block;
    other_block = *(char **)(other_block + 0x0c);
  }

  display_assert("other_block", "c:\\halo\\SOURCE\\memory\\memory_pool.c",
                 0x184, 1);
  system_exit(-1);
  return block;
}

/* Allocate and initialize a new memory pool (0x11e650).
 * Allocates pool_config+0x38 bytes via debug_malloc then calls
 * memory_pool_initialize. */
void *memory_pool_new(const char *name, int pool_config)
{
  void *pool;
  pool = debug_malloc(pool_config + 0x38, 0,
                      "c:\\halo\\SOURCE\\memory\\memory_pool.c", 0x46);
  if (pool != 0) {
    memory_pool_initialize(pool, name, pool_config);
  }
  return pool;
}

/* Validate and free a memory pool allocated by memory_pool_new (0x11e690). */
void memory_pool_delete(void *pool)
{
  FUN_0011e430(pool);
  csmemset(pool, 0, 0x38);
  debug_free(pool, "c:\\halo\\SOURCE\\memory\\memory_pool.c", 0x55);
}

/* Allocate a block from a memory pool (0x11e6c0).
 * Block header is 0x18 bytes: 'head', size, reference, next, prev, 'tail'.
 * Blocks are allocated sequentially after the last block (or at base if empty).
 * Returns the user data pointer (past the header) via *block_reference. */
bool memory_pool_block_new(void *pool, void **block_reference, int size)
{
  char *p = (char *)pool;
  unsigned int total_size;
  char *alloc_point;

  total_size = (unsigned int)(size + 0x18);
  if ((total_size & 3) != 0)
    total_size = (total_size | 3) + 1;

  FUN_0011e430(pool);

  if (size < 0) {
    display_assert("size>=0", "c:\\halo\\SOURCE\\memory\\memory_pool.c", 0x7c,
                   1);
    system_exit(-1);
  }

  if (*(int *)(p + 0x34) != 0) {
    char *last = *(char **)(p + 0x34);
    alloc_point = last + *(int *)(last + 4);
  } else {
    alloc_point = *(char **)(p + 0x24);
  }

  if ((unsigned int)alloc_point + total_size >
        (unsigned int)(*(int *)(p + 0x28) + *(int *)(p + 0x24)) ||
      alloc_point == NULL) {
    return false;
  }

  *(int *)(alloc_point + 0x00) = 0x68656164;
  *(unsigned int *)(alloc_point + 0x04) = total_size;
  *(void ***)(alloc_point + 0x08) = block_reference;
  *(int *)(alloc_point + 0x0c) = 0;
  *(int *)(alloc_point + 0x10) = *(int *)(p + 0x34);
  *(int *)(alloc_point + 0x14) = 0x7461696c;

  if (*(int *)(p + 0x30) == 0)
    *(char **)(p + 0x30) = alloc_point;

  if (*(int *)(p + 0x34) != 0)
    *(char **)(*(char **)(p + 0x34) + 0x0c) = alloc_point;

  *(char **)(p + 0x34) = alloc_point;

  {
    int free_size = *(int *)(p + 0x2c) - (int)total_size;
    *(int *)(p + 0x2c) = free_size;
    if (free_size < 0) {
      display_assert("pool->free_size>=0",
                     "c:\\halo\\SOURCE\\memory\\memory_pool.c", 0x9c, 1);
      system_exit(-1);
    }
  }

  *block_reference = (void *)(alloc_point + 0x18);
  return true;
}

/* Free a block from a memory pool (0x11e7a0).
 * Resolves the block header via FUN_0011e5a0, adds block size back to
 * free_size, unlinks from the doubly-linked list, then zeroes the memory. */
void memory_pool_block_free(void *pool, void **block_reference)
{
  char *p = (char *)pool;
  char *block = (char *)FUN_0011e5a0(pool, block_reference);
  int free_size;

  free_size = *(int *)(p + 0x2c) + *(int *)(block + 4);
  *(int *)(p + 0x2c) = free_size;

  if (free_size > *(int *)(p + 0x28)) {
    display_assert("pool->free_size<=pool->size",
                   "c:\\halo\\SOURCE\\memory\\memory_pool.c", 0xe6, 1);
    system_exit(-1);
  }

  if (*(int *)(block + 0x10) == 0) {
    *(int *)(p + 0x30) = *(int *)(block + 0x0c);
  } else {
    *(int *)(*(int *)(block + 0x10) + 0x0c) = *(int *)(block + 0x0c);
  }

  if (*(int *)(block + 0x0c) != 0) {
    *(int *)(*(int *)(block + 0x0c) + 0x10) = *(int *)(block + 0x10);
  } else {
    *(int *)(p + 0x34) = *(int *)(block + 0x10);
  }

  csmemset(block, 0, *(int *)(block + 4));
}

/* Compact the memory pool by moving blocks down to close gaps (0x11e840).
 * Walks the linked list and uses csmemmove to shift blocks toward the base. */
void memory_pool_compact(void *pool)
{
  int *p = (int *)pool;
  unsigned int block;
  unsigned int dest;
  unsigned int prev;

  block = (unsigned int)p[0x30 / 4];
  if (block != 0) {
    dest = (unsigned int)p[0x24 / 4];
    prev = 0;
    do {
      if (block > dest) {
        csmemmove((void *)dest, (void *)block, *(int *)(block + 4));
        **(int **)(dest + 8) = (int)(dest + 0x18);
        block = dest;
      }
      *(unsigned int *)(block + 0x10) = prev;
      if (prev != 0) {
        *(unsigned int *)(prev + 0x0c) = block;
      } else {
        p[0x30 / 4] = (int)block;
      }
      dest = *(int *)(block + 4) + block;
      prev = block;
      block = *(unsigned int *)(block + 0x0c);
    } while (block != 0);
    *(unsigned int *)(prev + 0x0c) = 0;
    p[0x34 / 4] = (int)prev;
  }
  FUN_0011e430(pool);
}

/* memory_pool_block_resize (0x11e8a0) — XBE naked draft (batch 84). */
#if defined(__clang__)
static void * (*const b11e8a0_c11e5a0)(void *pool, void **block_reference) = FUN_0011e5a0;
static void (*const b11e8a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11e8a0_exitfn)(int) = system_exit;
static bool (*const b11e8a0_c11e6c0)(void *pool, void **block_reference, int size) = memory_pool_block_new;
static void * (*const b11e8a0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b11e8a0_c11e7a0)(void *pool, void **block_reference) = memory_pool_block_free;

__attribute__((naked, noinline))
bool memory_pool_block_resize(void *pool __attribute__((unused)), void **block_reference __attribute__((unused)), int new_size __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c11e5a0]\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "leal 0x18(%%ecx), %%ebx\n\t"
      "testb $3, %%bl\n\t"
      "movl %%eax, %%esi\n\t"
      "je .Lmemory_pool_block_resize_1\n\t"
      "orl $3, %%ebx\n\t"
      "incl %%ebx\n\t"
      ".Lmemory_pool_block_resize_1:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jge .Lmemory_pool_block_resize_2\n\t"
      "pushl $1\n\t"
      "pushl $0xae\n\t"
      "pushl $0x290084\n\t"
      "pushl $0x290178\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmemory_pool_block_resize_2:\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lmemory_pool_block_resize_3\n\t"
      "movl 0x28(%%edi), %%eax\n\t"
      "addl 0x24(%%edi), %%eax\n\t"
      ".Lmemory_pool_block_resize_3:\n\t"
      "leal (%%ebx,%%esi,1), %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "ja .Lmemory_pool_block_resize_6\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl 0x2c(%%edi), %%ecx\n\t"
      "subl %%ebx, %%eax\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl %%ecx, 0x2c(%%edi)\n\t"
      "movl %%ecx, %%eax\n\t"
      "js .Lmemory_pool_block_resize_4\n\t"
      "cmpl 0x28(%%edi), %%eax\n\t"
      "jle .Lmemory_pool_block_resize_5\n\t"
      ".Lmemory_pool_block_resize_4:\n\t"
      "pushl $1\n\t"
      "pushl $0xb8\n\t"
      "pushl $0x290084\n\t"
      "pushl $0x290144\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmemory_pool_block_resize_5:\n\t"
      "popl %%edi\n\t"
      "movl %%ebx, 0x4(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lmemory_pool_block_resize_6:\n\t"
      "pushl %%ecx\n\t"
      "leal 0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c11e6c0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lmemory_pool_block_resize_8\n\t"
      "cmpl 0x4(%%esi), %%ebx\n\t"
      "jg .Lmemory_pool_block_resize_7\n\t"
      "pushl $1\n\t"
      "pushl $0xc8\n\t"
      "pushl $0x290084\n\t"
      "pushl $0x290128\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lmemory_pool_block_resize_7:\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "subl $0x18, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c11e7a0]\n\t"
      "addl $0x14, %%esp\n\t"
      "leal 0x10(%%ebp), %%esi\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c11e5a0]\n\t"
      "movl %%ebx, 0x8(%%eax)\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%edx, (%%ebx)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lmemory_pool_block_resize_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c11e5a0] "m"(b11e8a0_c11e5a0), [assert] "m"(b11e8a0_assert), [exitfn] "m"(b11e8a0_exitfn), [c11e6c0] "m"(b11e8a0_c11e6c0), [c8e0b0] "m"(b11e8a0_c8e0b0), [c11e7a0] "m"(b11e8a0_c11e7a0)
      : "memory");
}
#else
#error "memory_pool_block_resize: clang naked draft required"
#endif

