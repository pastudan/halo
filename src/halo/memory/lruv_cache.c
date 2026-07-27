/* 0x11c820: Validate an lrar_cache header ('lrar' magic @+0x44, minimum<maximum
 * address, block_size(+0x2c)>=1, block_count(+0x38)>=1). On corruption formats
 * the standard message into the shared scratch buffer (0x5ab100) and hits
 * display_assert + system_exit(-1). cache passed in EAX.
 * Source: c:\halo\SOURCE\memory\lrar_cache.c line 0x199. */
void lruv_update_function_pointers(int cache)
{
  if ((*(int *)(cache + 0x44) != 0x6c726172) ||
      (*(unsigned int *)(cache + 0x28) <= *(unsigned int *)(cache + 0x24)) ||
      (*(int *)(cache + 0x2c) < 1) ||
      (*(short *)(cache + 0x38) < 1)) {
    display_assert(csprintf((char *)0x5ab100,
                            "lrar cache %s @%p appears to be corrupt",
                            cache, cache),
                   "c:\\halo\\SOURCE\\memory\\lrar_cache.c", 0x199, 1);
    system_exit(-1);
  }
}

/* 0x11c7c0: Validate an lrar_cache block record ('klbR' magic @block+4, size
 * (block+0xc) in [0, cache->block_size@+0x2c), address (block+8) within the
 * cache's [minimum@+0x24, maximum@+0x28) range). On corruption formats
 * "... block @%p appears to be corrupt" and hits display_assert +
 * system_exit(-1). cache in EAX, block in ESI. Source: lrar_cache.c 0x186. */
void FUN_0011c7c0(int cache, int block)
{
  int size = *(int *)(block + 0xc);
  if ((*(int *)(block + 4) != 0x52626c6b) ||
      (size < 0) ||
      (*(int *)(cache + 0x2c) <= size) ||
      (*(unsigned int *)(block + 8) < *(unsigned int *)(cache + 0x24)) ||
      (*(unsigned int *)(cache + 0x28) < *(unsigned int *)(block + 8) + size)) {
    display_assert(csprintf((char *)0x5ab100,
                            "lrar cache %s @%p block @%p appears to be corrupt",
                            cache, cache, block),
                   "c:\\halo\\SOURCE\\memory\\lrar_cache.c", 0x186, 1);
    system_exit(-1);
  }
}

/* 0x11ca60: Look up and validate an lrar_cache block record by index. Validates
 * the cache header (lruv_update_function_pointers), bounds-checks block_index
 * against block_count (+0x38; line 0x16e), computes the record pointer
 * (block_index*0x10 + block_array@+0x30), validates it (FUN_0011c7c0), and
 * returns it. block_index in AX, cache in EDI. Source: lrar_cache.c. */
int FUN_0011ca60(short block_index, int cache)
{
  int block;

  lruv_update_function_pointers(cache);
  if ((block_index < 0) || (*(short *)(cache + 0x38) <= block_index)) {
    display_assert("block_index>=0 && block_index<cache->block_count",
                   "c:\\halo\\SOURCE\\memory\\lrar_cache.c", 0x16e, 1);
    system_exit(-1);
  }
  block = (int)block_index * 0x10 + *(int *)(cache + 0x30);
  FUN_0011c7c0(cache, block);
  return block;
}

/* 0x11c5d0: Touch an lrar_cache block (FUN_0011c210 relink bookkeeping) and
 * return its byte offset from the cache's minimum address
 * (block - cache->minimum_address@+0x24). block in EAX, cache in ECX. */
int FUN_0011c5d0(int block, int cache)
{
  FUN_0011c210(cache, block);
  return block - *(int *)(cache + 0x24);
}

/* 0x11c7a0: Free an lrar_cache block's user allocation. If the block's user
 * pointer (block[0]) is non-NULL, invokes the cache free callback (cache+0x40)
 * on it and clears the slot. block in ESI, cache on the stack.
 * (kb name lruv_allocation_size is a punpckhdq PDB misnomer; this is the
 * per-block free helper.) */
void lruv_allocation_size(int block, int cache)
{
  if (*(int *)block != 0) {
    (*(void (**)(int))(cache + 0x40))(*(int *)block);
    *(int *)block = 0;
  }
}

/* 0x11d090: Validate an lru_cache header ('curl' magic @+0x44; head@+0x34,
 * block_size@+0x2c, block_array@+0x30 non-zero; maximum@+0x28 ==
 * page_size(+0x20) * page_count(+0x24); page_count>=0x10; used(+0x40) in
 * [0, page_size]). On corruption formats "lru cache %s @%p appears to be
 * corrupt" and hits display_assert + system_exit(-1). cache in EAX.
 * Source: c:\halo\SOURCE\memory\lru_cache.c line 0x16b. */
void FUN_0011d090(int cache)
{
  int page_size;

  if ((*(int *)(cache + 0x44) == 0x6c727563) &&
      (*(int *)(cache + 0x34) != 0) &&
      (*(int *)(cache + 0x2c) != 0) &&
      (*(int *)(cache + 0x30) != 0)) {
    page_size = *(int *)(cache + 0x20);
    if ((*(int *)(cache + 0x28) ==
         page_size * *(unsigned int *)(cache + 0x24)) &&
        (0xf < *(unsigned int *)(cache + 0x24)) &&
        (-1 < page_size) &&
        (-1 < *(int *)(cache + 0x40)) &&
        (*(int *)(cache + 0x40) <= page_size)) {
      return;
    }
  }
  display_assert(csprintf((char *)0x5ab100,
                          "lru cache %s @%p appears to be corrupt",
                          cache, cache),
                 "c:\\halo\\SOURCE\\memory\\lru_cache.c", 0x16b, 1);
  system_exit(-1);
}

/* 0x11d300: Return an lru_cache's remaining free capacity: page_size(+0x20)
 * minus the used page count (+0x40), after validating the cache header
 * (FUN_0011d090, cache in EAX). cdecl(cache).
 * Source: c:\halo\SOURCE\memory\lru_cache.c */
int FUN_0011d300(int cache)
{
  FUN_0011d090(cache);
  return *(int *)(cache + 0x20) - *(int *)(cache + 0x40);
}

/* FUN_0011d320 (0x11d320) — XBE naked draft (batch 86). */
#if defined(__clang__)
static void (*const b11d320_c11d090)(int cache) = FUN_0011d090;
static void (*const b11d320_c11d010)(int cache, void *entry) = FUN_0011d010;

__attribute__((naked, noinline))
void * FUN_0011d320(int cache __attribute__((unused)), int value __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "call *%[c11d090]\n\t"
      "movl 0x40(%%esi), %%eax\n\t"
      "cmpl 0x20(%%esi), %%eax\n\t"
      "jne .LFUN_0011d320_4\n\t"
      "testl %%eax, %%eax\n\t"
      "movl 0x34(%%esi), %%ebx\n\t"
      "movl %%edi, 0x8(%%ebp)\n\t"
      "jle .LFUN_0011d320_6\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0011d320_1:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c11d010]\n\t"
      "movb 0x4(%%ebx), %%al\n\t"
      "addl $8, %%esp\n\t"
      "testb $1, %%al\n\t"
      "jne .LFUN_0011d320_3\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_0011d320_2\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "cmpl 0x8(%%ebx), %%eax\n\t"
      "jbe .LFUN_0011d320_3\n\t"
      ".LFUN_0011d320_2:\n\t"
      "movl 0x8(%%ebx), %%ecx\n\t"
      "movl %%ebx, %%edi\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      ".LFUN_0011d320_3:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x24(%%esi), %%edx\n\t"
      "movl 0x40(%%esi), %%ecx\n\t"
      "incl %%eax\n\t"
      "addl %%edx, %%ebx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "jl .LFUN_0011d320_1\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_0011d320_6\n\t"
      "movl (%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *0x30(%%esi)\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_0011d320_5\n\t"
      ".LFUN_0011d320_4:\n\t"
      "movl 0x24(%%esi), %%edi\n\t"
      "movl 0x34(%%esi), %%ecx\n\t"
      "imull %%eax, %%edi\n\t"
      "addl %%ecx, %%edi\n\t"
      "incl %%eax\n\t"
      "movl %%eax, 0x40(%%esi)\n\t"
      ".LFUN_0011d320_5:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_0011d320_6\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, (%%edi)\n\t"
      "movl $0x55626c6a, 0x4(%%edi)\n\t"
      "movl 0x3c(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edi)\n\t"
      "incl 0x3c(%%esi)\n\t"
      "movl (%%edi), %%edx\n\t"
      "leal 0x10(%%edi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "movl $0, 0xc(%%edi)\n\t"
      "call *0x2c(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011d320_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c11d090] "m"(b11d320_c11d090), [c11d010] "m"(b11d320_c11d010)
      : "memory");
}
#else
#error "FUN_0011d320: clang naked draft required"
#endif


/* FUN_0011c5f0 (0x11c5f0) — XBE naked draft (batch 83). */
#if defined(__clang__)
static void (*const b11c5f0_c11c290)(int cache) = FUN_0011c290;
static void (*const b11c5f0_c11c210)(int cache, int block) = FUN_0011c210;

__attribute__((naked, noinline))
void * FUN_0011c5f0(int cache __attribute__((unused)), int size __attribute__((unused)), void *data __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "call *%[c11c290]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $0x10, %%eax\n\t"
      "testb $3, %%al\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "je .LFUN_0011c5f0_1\n\t"
      "orl $3, %%eax\n\t"
      "incl %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      ".LFUN_0011c5f0_1:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_0011c5f0_17\n\t"
      "cmpl 0x20(%%ebx), %%eax\n\t"
      "jg .LFUN_0011c5f0_17\n\t"
      "movl 0x2c(%%ebx), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "je .LFUN_0011c5f0_2\n\t"
      "movl 0xc(%%esi), %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jmp .LFUN_0011c5f0_4\n\t"
      ".LFUN_0011c5f0_2:\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jmp .LFUN_0011c5f0_4\n\t"
      ".LFUN_0011c5f0_3:\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      ".LFUN_0011c5f0_4:\n\t"
      "cmpl %%eax, %%esi\n\t"
      "je .LFUN_0011c5f0_5\n\t"
      "call *%[c11c210]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ecx), %%eax\n\t"
      "subl 0x24(%%ebx), %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jmp .LFUN_0011c5f0_6\n\t"
      ".LFUN_0011c5f0_5:\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".LFUN_0011c5f0_6:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_0011c5f0_10\n\t"
      "movl %%edi, %%esi\n\t"
      "call *%[c11c210]\n\t"
      "call *%[c11c210]\n\t"
      "movl 0x24(%%ebx), %%edx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "subl %%edx, %%eax\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "addl %%ecx, %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jle .LFUN_0011c5f0_9\n\t"
      "testb $1, 0x4(%%edi)\n\t"
      "je .LFUN_0011c5f0_7\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "movl 0xc(%%edi), %%edi\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jmp .LFUN_0011c5f0_16\n\t"
      ".LFUN_0011c5f0_7:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0011c5f0_8\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      ".LFUN_0011c5f0_8:\n\t"
      "movl 0xc(%%edi), %%edi\n\t"
      "jmp .LFUN_0011c5f0_16\n\t"
      ".LFUN_0011c5f0_9:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      ".LFUN_0011c5f0_10:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "leal (%%eax,%%ecx,1), %%edx\n\t"
      "cmpl 0x20(%%ebx), %%edx\n\t"
      "jle .LFUN_0011c5f0_11\n\t"
      "movl 0x24(%%ebx), %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movw %%ax, %%cx\n\t"
      "incl %%eax\n\t"
      "testw %%cx, %%cx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "je .LFUN_0011c5f0_16\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011c5f0_11:\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_0011c5f0_14\n\t"
      ".LFUN_0011c5f0_12:\n\t"
      "cmpl %%edi, %%esi\n\t"
      "je .LFUN_0011c5f0_14\n\t"
      "testb $2, 0x4(%%esi)\n\t"
      "jne .LFUN_0011c5f0_13\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *0x34(%%ebx)\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "andl $0xfffffffe, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "orl $2, %%eax\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      ".LFUN_0011c5f0_13:\n\t"
      "movl 0xc(%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_0011c5f0_12\n\t"
      ".LFUN_0011c5f0_14:\n\t"
      "movl 0x24(%%ebx), %%esi\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "addl %%eax, %%esi\n\t"
      "leal 0x10(%%esi), %%eax\n\t"
      "movl %%ecx, 0x8(%%esi)\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl $0x41626c68, 0x4(%%esi)\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movl %%edi, 0xc(%%esi)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "call *0x30(%%ebx)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011c5f0_15\n\t"
      "movl %%esi, 0xc(%%eax)\n\t"
      ".LFUN_0011c5f0_15:\n\t"
      "movl %%esi, 0x2c(%%ebx)\n\t"
      ".LFUN_0011c5f0_16:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .LFUN_0011c5f0_3\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011c5f0_17:\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c11c290] "m"(b11c5f0_c11c290), [c11c210] "m"(b11c5f0_c11c210)
      : "memory");
}
#else
#error "FUN_0011c5f0: clang naked draft required"
#endif


/* FUN_0011c530 (0x11c530) — readable C lift from XBE leaf. */
void FUN_0011c530(int cache, void *pointer)
{
  extern char DAT_00267eec[];
  extern char DAT_0028f768[];
  unsigned char *hdr;

  if (pointer == 0) {
    display_assert(DAT_00267eec, DAT_0028f768, 0x12a, true);
    system_exit(-1);
  }
  hdr = (unsigned char *)pointer - 0x10;
  FUN_0011c290(cache);
  FUN_0011c210(cache, (int)hdr);
  *(int *)(hdr + 4) |= 1;
}




/* FUN_0011c580 (0x11c580) — readable C lift from XBE leaf. */
void FUN_0011c580(int cache, void *pointer)
{
  extern char DAT_00267eec[];
  extern char DAT_0028f768[];
  unsigned char *hdr;

  if (pointer == 0) {
    display_assert(DAT_00267eec, DAT_0028f768, 0x13a, true);
    system_exit(-1);
  }
  hdr = (unsigned char *)pointer - 0x10;
  FUN_0011c290(cache);
  FUN_0011c210(cache, (int)hdr);
  *(int *)(hdr + 4) &= ~1;
}




/* lrar_cache_dispose (0x11cab0) — XBE naked draft (batch 85). */
#if defined(__clang__)
static void (*const b11cab0_c11c820)(int cache) = lruv_update_function_pointers;
static char * (*const b11cab0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b11cab0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11cab0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void lrar_cache_dispose(int cache __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c11c820]\n\t"
      "movw 0x34(%%esi), %%bx\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "cmpw %%ax, %%bx\n\t"
      "je .Llrar_cache_dispose_11\n\t"
      ".Llrar_cache_dispose_1:\n\t"
      "cmpl $0x6c726172, 0x44(%%esi)\n\t"
      "jne .Llrar_cache_dispose_2\n\t"
      "movl 0x24(%%esi), %%eax\n\t"
      "cmpl 0x28(%%esi), %%eax\n\t"
      "jae .Llrar_cache_dispose_2\n\t"
      "movl 0x2c(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .Llrar_cache_dispose_2\n\t"
      "cmpw $0, 0x38(%%esi)\n\t"
      "jg .Llrar_cache_dispose_3\n\t"
      ".Llrar_cache_dispose_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x199\n\t"
      "pushl $0x28f808\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0x28f82c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Llrar_cache_dispose_3:\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .Llrar_cache_dispose_4\n\t"
      "cmpw 0x38(%%esi), %%bx\n\t"
      "jl .Llrar_cache_dispose_5\n\t"
      ".Llrar_cache_dispose_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x16e\n\t"
      "pushl $0x28f808\n\t"
      "pushl $0x28f8c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Llrar_cache_dispose_5:\n\t"
      "movl 0x30(%%esi), %%ecx\n\t"
      "movswl %%bx, %%edi\n\t"
      "shll $4, %%edi\n\t"
      "movl 0x4(%%edi,%%ecx,1), %%eax\n\t"
      "addl %%ecx, %%edi\n\t"
      "cmpl $0x52626c6b, %%eax\n\t"
      "jne .Llrar_cache_dispose_6\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .Llrar_cache_dispose_6\n\t"
      "cmpl 0x2c(%%esi), %%eax\n\t"
      "jge .Llrar_cache_dispose_6\n\t"
      "movl 0x8(%%edi), %%ecx\n\t"
      "cmpl 0x24(%%esi), %%ecx\n\t"
      "jb .Llrar_cache_dispose_6\n\t"
      "addl %%eax, %%ecx\n\t"
      "cmpl 0x28(%%esi), %%ecx\n\t"
      "jbe .Llrar_cache_dispose_7\n\t"
      ".Llrar_cache_dispose_6:\n\t"
      "pushl $1\n\t"
      "pushl $0x186\n\t"
      "pushl $0x28f808\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0x28f7d4\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Llrar_cache_dispose_7:\n\t"
      "movl (%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Llrar_cache_dispose_8\n\t"
      "pushl %%eax\n\t"
      "call *0x40(%%esi)\n\t"
      "addl $4, %%esp\n\t"
      "movl $0, (%%edi)\n\t"
      ".Llrar_cache_dispose_8:\n\t"
      "cmpw 0x36(%%esi), %%bx\n\t"
      "je .Llrar_cache_dispose_10\n\t"
      "incl %%ebx\n\t"
      "cmpw 0x38(%%esi), %%bx\n\t"
      "jne .Llrar_cache_dispose_9\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "jmp .Llrar_cache_dispose_1\n\t"
      ".Llrar_cache_dispose_9:\n\t"
      "cmpw $-1, %%bx\n\t"
      "jne .Llrar_cache_dispose_1\n\t"
      ".Llrar_cache_dispose_10:\n\t"
      "orl $0xffffffff, %%eax\n\t"
      ".Llrar_cache_dispose_11:\n\t"
      "popl %%edi\n\t"
      "movw %%ax, 0x34(%%esi)\n\t"
      "movw %%ax, 0x36(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c11c820] "m"(b11cab0_c11c820), [c8d9d0] "m"(b11cab0_c8d9d0), [assert] "m"(b11cab0_assert), [exitfn] "m"(b11cab0_exitfn)
      : "memory");
}
#else
#error "lrar_cache_dispose: clang naked draft required"
#endif


/* 0x11cbf0: lrar_cache block allocator. Refreshes the cache's function-pointer
 * table (lruv_update_function_pointers, cache in @eax), rounds the request up
 * to the primary alignment (cache+0x20), then walks the block ring to find a
 * contiguous address range >= size that fits under cache->maximum_address
 * (+0x28), evicting overlapping blocks via the free callback (cache+0x40) as it
 * goes. Applies an optional secondary boundary alignment (cache+0x22, -1=none).
 * On a fit it writes a fresh block record (data ptr +0, 'lRbk' magic +4,
 * address +8, size +0xc), registers it via the insert callback
 * (cache+0x3c(data, index)), and links it as the new last/head block. Returns
 * the new block index (or 0xffff on reject). Integrity asserts reference
 * c:\halo\SOURCE\memory\lrar_cache.c. The @reg callee FUN_0011ca60 fetches a
 * block record (block_index @<ax>, cache @<edi>). */
short FUN_0011cbf0(int cache, int size, void *data)
{
  int new_block_index;
  unsigned int new_block_address;
  unsigned int search_address;
  unsigned int align_mask;
  int boundary;
  unsigned int boundary_mask;
  unsigned int aligned_base;
  short block_index;
  short next_index;
  int *block;
  unsigned int *new_block;
  int end;

  new_block_index = -1;
  lruv_update_function_pointers(cache);

  align_mask = (1 << (*(unsigned char *)(cache + 0x20) & 0x1f)) - 1;
  if (((unsigned int)size & align_mask) != 0) {
    size = (align_mask | (unsigned int)size) + 1;
  }

  if ((size >= 0) && (size <= *(int *)(cache + 0x2c))) {
    block_index = *(short *)(cache + 0x34);
    if (*(short *)(cache + 0x36) == -1) {
      new_block_index = 0;
    } else {
      new_block_index = *(short *)(cache + 0x36) + 1;
    }
    next_index = block_index;
    if (*(short *)(cache + 0x38) <= (short)new_block_index) {
      new_block_index = 0;
    }

    while (1) {
      if (*(short *)(cache + 0x36) == -1) {
        search_address = *(unsigned int *)(cache + 0x24);
      } else {
        block = (int *)FUN_0011ca60(*(short *)(cache + 0x36), cache);
        search_address = block[3] + block[2];
      }
      new_block_address = search_address;

      if (*(short *)(cache + 0x22) != -1) {
        boundary = 1 << (*(short *)(cache + 0x22) & 0x1f);
        boundary_mask = ~((unsigned int)boundary - 1U);
        aligned_base = boundary_mask & search_address;
        block_index = next_index;
        if (aligned_base != ((search_address + size) & boundary_mask)) {
          new_block_address = aligned_base + boundary;
        }
      }

      if (block_index != -1) {
        block = (int *)FUN_0011ca60(block_index, cache);
        while ((block_index == (short)new_block_index) ||
               ((search_address <= (unsigned int)block[2]) &&
                ((unsigned int)block[2] < new_block_address + size))) {
          if (block[0] != 0) {
            (*(void (**)(void *))(cache + 0x40))((void *)block[0]);
            block[0] = 0;
          }
          block[1] = -1;
          next_index = block_index + 1;
          if (*(short *)(cache + 0x38) <= next_index) {
            next_index = 0;
          }
          if ((*(int *)(cache + 0x44) != 0x6c726172) ||
              (*(unsigned int *)(cache + 0x28) <=
               *(unsigned int *)(cache + 0x24)) ||
              (*(int *)(cache + 0x2c) < 1) || (*(short *)(cache + 0x38) < 1)) {
            display_assert(csprintf((char *)0x5ab100,
                                    "lrar cache %s @%p appears to be corrupt",
                                    cache, cache),
                           "c:\\halo\\SOURCE\\memory\\lrar_cache.c", 0x199, 1);
            system_exit(-1);
          }
          if ((next_index < 0) || (*(short *)(cache + 0x38) <= next_index)) {
            display_assert("block_index>=0 && block_index<cache->block_count",
                           "c:\\halo\\SOURCE\\memory\\lrar_cache.c", 0x16e, 1);
            system_exit(-1);
          }
          block = (int *)(next_index * 0x10 + *(int *)(cache + 0x30));
          block_index = next_index;
          if ((*(int *)(next_index * 0x10 + 4 + *(int *)(cache + 0x30)) !=
               0x52626c6b) ||
              (block[3] < 0) || (*(int *)(cache + 0x2c) <= block[3]) ||
              ((unsigned int)block[2] < *(unsigned int *)(cache + 0x24)) ||
              (*(unsigned int *)(cache + 0x28) <
               (unsigned int)(block[2] + block[3]))) {
            display_assert(
              csprintf((char *)0x5ab100,
                       "lrar cache %s @%p block @%p appears to be corrupt",
                       cache, cache, block),
              "c:\\halo\\SOURCE\\memory\\lrar_cache.c", 0x186, 1);
            system_exit(-1);
          }
        }
      }

      if (new_block_address + size <= *(unsigned int *)(cache + 0x28)) {
        break;
      }
      *(short *)(cache + 0x36) = -1;
    }

    new_block =
      (unsigned int *)((short)new_block_index * 0x10 + *(int *)(cache + 0x30));
    if ((new_block_address < *(unsigned int *)(cache + 0x24)) ||
        (*(unsigned int *)(cache + 0x28) < new_block_address + size)) {
      display_assert("adjusted_new_block_address>=cache->minimum_address && "
                     "adjusted_new_block_address+size<=cache->maximum_address",
                     "c:\\halo\\SOURCE\\memory\\lrar_cache.c", 0x111, 1);
      system_exit(-1);
    }

    block_index = 0;
    if (0 < *(short *)(cache + 0x38)) {
      do {
        end = block_index * 0x10 + *(int *)(cache + 0x30);
        if ((*(int *)(block_index * 0x10 + 4 + *(int *)(cache + 0x30)) ==
             0x52626c6b) &&
            (search_address = *(unsigned int *)(end + 8),
             new_block_address <
               (unsigned int)(*(int *)(end + 0xc) + search_address)) &&
            (search_address < new_block_address + size)) {
          display_assert(
            "adjusted_new_block_address>=test_block->address+test_block->size "
            "|| adjusted_new_block_address+size<=test_block->address",
            "c:\\halo\\SOURCE\\memory\\lrar_cache.c", 0x11c, 1);
          system_exit(-1);
        }
        block_index = block_index + 1;
      } while (block_index < *(short *)(cache + 0x38));
    }

    new_block[3] = size;
    new_block[1] = 0x52626c6b;
    new_block[2] = new_block_address;
    new_block[0] = (unsigned int)data;
    (*(void (**)(void *, int))(cache + 0x3c))(data, new_block_index);
    *(short *)(cache + 0x36) = (short)new_block_index;
    if (next_index == -1) {
      *(short *)(cache + 0x34) = (short)new_block_index;
    } else {
      *(short *)(cache + 0x34) = next_index;
    }
  }

  return (short)new_block_index;
}

/* Store a short value through a pointer.
 * 0x11c780 / lruv_cache.obj
 */
void FUN_0011c780(short *param_1, short param_2)
{
  *param_1 = param_2;
}

/* Store 0xffff into a short through a pointer.
 * 0x11c790 / lruv_cache.obj
 */
void FUN_0011c790(short *param_1)
{
  *param_1 = (short)0xffff;
}

/* lrar_cache_new (0x11c870) — XBE naked draft (batch 83). */
#if defined(__clang__)
static void * (*const b11c870_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b11c870_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11c870_exitfn)(int) = system_exit;
static void *(*const b11c870_memset)(void *, int, unsigned int) = csmemset;
static void * (*const b11c870_c8de70)(char *destination, const char *source, size_t size) = csstrncpy;
static void (*const b11c870_c11c820)(int cache) = lruv_update_function_pointers;
static void (*const b11c870_c8ef70)(void *ptr, const char *file, int line) = debug_free;

__attribute__((naked, noinline))
void * lrar_cache_new(const char *name __attribute__((unused)), unsigned int minimum_address __attribute__((unused)), unsigned int maximum_address __attribute__((unused)), short block_count __attribute__((unused)), short alignment_bit __attribute__((unused)), short boundary_bit __attribute__((unused)), void (*lock_proc)(short * __attribute__((unused)), short), void (*unlock_proc)(short *) __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x56\n\t"
      "pushl $0x28f808\n\t"
      "pushl $0\n\t"
      "pushl $0x48\n\t"
      "call *%[c8ee60]\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%edi, %%ebx\n\t"
      "movl %%eax, %%esi\n\t"
      "jb .Llrar_cache_new_1\n\t"
      "pushl $1\n\t"
      "pushl $0x58\n\t"
      "pushl $0x28f808\n\t"
      "pushl $0x28f8a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Llrar_cache_new_1:\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movl $1, %%eax\n\t"
      "movb %%dl, %%cl\n\t"
      "shll %%cl, %%eax\n\t"
      "decl %%eax\n\t"
      "testl %%eax, %%ebx\n\t"
      "je .Llrar_cache_new_2\n\t"
      "orl %%ebx, %%eax\n\t"
      "incl %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      ".Llrar_cache_new_2:\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Llrar_cache_new_3\n\t"
      "movl 0x24(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Llrar_cache_new_4\n\t"
      ".Llrar_cache_new_3:\n\t"
      "movl $0x11c780, 0x20(%%ebp)\n\t"
      "movl $0x11c790, 0x24(%%ebp)\n\t"
      ".Llrar_cache_new_4:\n\t"
      "testw %%dx, %%dx\n\t"
      "jge .Llrar_cache_new_5\n\t"
      "pushl $1\n\t"
      "pushl $0x66\n\t"
      "pushl $0x28f808\n\t"
      "pushl $0x28f88c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Llrar_cache_new_5:\n\t"
      "movw 0x1c(%%ebp), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Llrar_cache_new_6\n\t"
      "testw %%ax, %%ax\n\t"
      "jge .Llrar_cache_new_6\n\t"
      "pushl $1\n\t"
      "pushl $0x67\n\t"
      "pushl $0x28f808\n\t"
      "pushl $0x28f864\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Llrar_cache_new_6:\n\t"
      "movw 0x14(%%ebp), %%bx\n\t"
      "testw %%bx, %%bx\n\t"
      "jg .Llrar_cache_new_7\n\t"
      "pushl $1\n\t"
      "pushl $0x68\n\t"
      "pushl $0x28f808\n\t"
      "pushl $0x28f854\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Llrar_cache_new_7:\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Llrar_cache_new_8\n\t"
      "pushl $0x6c\n\t"
      "movswl %%bx, %%eax\n\t"
      "pushl $0x28f808\n\t"
      "shll $4, %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "call *%[c8ee60]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .Llrar_cache_new_9\n\t"
      "pushl $0x48\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "call *%[memset]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0x1f\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8de70]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movw 0x18(%%ebp), %%dx\n\t"
      "movw 0x14(%%ebp), %%cx\n\t"
      "movl %%eax, 0x24(%%esi)\n\t"
      "movl %%edi, 0x28(%%esi)\n\t"
      "subl %%eax, %%edi\n\t"
      "movw 0x1c(%%ebp), %%ax\n\t"
      "movw %%ax, 0x22(%%esi)\n\t"
      "movl $0xffffffff, %%eax\n\t"
      "movw %%ax, 0x34(%%esi)\n\t"
      "movw %%ax, 0x36(%%esi)\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "movw %%dx, 0x20(%%esi)\n\t"
      "movl 0x24(%%ebp), %%edx\n\t"
      "movl %%eax, 0x3c(%%esi)\n\t"
      "addl $0x24, %%esp\n\t"
      "movl %%esi, %%eax\n\t"
      "movb $0, 0x1f(%%esi)\n\t"
      "movl %%edi, 0x2c(%%esi)\n\t"
      "movl %%ebx, 0x30(%%esi)\n\t"
      "movw %%cx, 0x38(%%esi)\n\t"
      "movl %%edx, 0x40(%%esi)\n\t"
      "movl $0x6c726172, 0x44(%%esi)\n\t"
      "call *%[c11c820]\n\t"
      ".Llrar_cache_new_8:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Llrar_cache_new_9:\n\t"
      "pushl $0x8a\n\t"
      "pushl $0x28f808\n\t"
      "pushl %%esi\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8ee60] "m"(b11c870_c8ee60), [assert] "m"(b11c870_assert), [exitfn] "m"(b11c870_exitfn), [memset] "m"(b11c870_memset), [c8de70] "m"(b11c870_c8de70), [c11c820] "m"(b11c870_c11c820), [c8ef70] "m"(b11c870_c8ef70)
      : "memory");
}
#else
#error "lrar_cache_new: clang naked draft required"
#endif


/* 0x11ca20: Dispose of an lrar_cache. Refreshes the cache's function-pointer
 * table (lruv_update_function_pointers, cache passed in EAX), then frees the
 * block sub-buffer stored at cache+0x30 and finally the cache header itself,
 * each via debug_free. Asserts against c:\halo\SOURCE\memory\lrar_cache.c
 * lines 0x98/0x99. NOTE: the kb placeholder name "lruv_has_locked_proc" is a
 * stale misnomer; this routine is a destructor, not a predicate. Disasm:
 * mov esi,[ebp+8]; mov eax,esi; call 0x11c820; mov eax,[esi+0x30];
 * push 0x98; push <file>; push eax; call debug_free; push 0x99; push <file>;
 * push esi; call debug_free. */
void lruv_has_locked_proc(void *cache)
{
  lruv_update_function_pointers((int)cache);
  debug_free(*(void **)((char *)cache + 0x30),
             "c:\\halo\\SOURCE\\memory\\lrar_cache.c", 0x98);
  debug_free(cache, "c:\\halo\\SOURCE\\memory\\lrar_cache.c", 0x99);
}

/* 0x11cf00: lrar_cache block getter. Returns the data pointer stored at
 * offset 8 of block_array[block_index]. This belongs to the sibling
 * "lrar_cache" (asserts against c:\halo\SOURCE\memory\lrar_cache.c) that
 * shares this TU with the lruv_cache; its header layout differs from
 * lruv_cache_t (cache+0x30 = block array base ptr, cache+0x38 = int16
 * block_count, block entry stride = 0x10), so raw offset access is used to
 * avoid conflating the two structures. FUN_0011c820 refreshes the function
 * pointers on entry and FUN_0011c7c0 is the matching helper before return.
 */
void *FUN_0011cf00(int cache, short block_index)
{
  int block_array;

  lruv_update_function_pointers(cache);
  if ((block_index < 0) || (*(short *)(cache + 0x38) <= block_index)) {
    display_assert("block_index>=0 && block_index<cache->block_count",
                   "c:\\halo\\SOURCE\\memory\\lrar_cache.c", 0x16e, true);
    system_exit(-1);
  }
  block_array = *(int *)(cache + 0x30);
  FUN_0011c7c0(cache, block_index * 0x10 + block_array);
  return *(void **)(block_index * 0x10 + block_array + 8);
}

/* 0x11cf60: lrar_cache block free/clear. Sibling of FUN_0011cf00 (same
 * lrar_cache layout, asserts against c:\halo\SOURCE\memory\lrar_cache.c;
 * distinct from lruv_cache_t so raw offset access is used). Refreshes the
 * cache function pointers on entry (called twice, matching the original),
 * bounds-checks block_index against cache->block_count (int16 at cache+0x38,
 * signed), then reads the block's data pointer (first dword of the 0x10-byte
 * entry at cache+0x30). If non-NULL, invokes the cache free callback (cdecl
 * fn ptr at cache+0x40, one arg) with that pointer and nulls the slot.
 */
void FUN_0011cf60(int cache, short block_index)
{
  int *block_ptr;
  int data;

  lruv_update_function_pointers(cache);
  lruv_update_function_pointers(cache);
  if ((block_index < 0) || (*(short *)(cache + 0x38) <= block_index)) {
    display_assert("block_index>=0 && block_index<cache->block_count",
                   "c:\\halo\\SOURCE\\memory\\lrar_cache.c", 0x16e, true);
    system_exit(-1);
  }
  block_ptr = (int *)(block_index * 0x10 + *(int *)(cache + 0x30));
  FUN_0011c7c0(cache, (int)block_ptr);
  data = *block_ptr;
  if (data != 0) {
    (*(void (**)(int))(cache + 0x40))(data);
    *block_ptr = 0;
  }
}

/* 0x11cfd0: Store a 4-byte value through the pointer arg. Trivial default
 * delete callback: writes the supplied value into the first field of the
 * record. Sibling of FUN_0011cfe0. Source: c:\halo\SOURCE\memory\lrar_cache.c
 */
void FUN_0011cfd0(int *ptr, int value)
{
  *ptr = value;
}

/* 0x11cfe0: Zero the first 4-byte field of the pointed-to record. Trivial
 * setter that clears a cache head/count word through the stack pointer arg.
 * Source: c:\halo\SOURCE\memory\lrar_cache.c */
void FUN_0011cfe0(void *param_1)
{
  *(int *)param_1 = 0;
}

/* LRU-V (Least Recently Used - Virtual) cache management.
 * Manages a block-based cache with linked list ordering, delete/query
 * callbacks, and page-granularity allocation tracking. Source:
 * c:\halo\SOURCE\memory\lruv_cache.c */

#define LRUV_CACHE_SIGNATURE 0x77656565

/* lruv_cache_t: header for an LRU-V cache allocation.
 * size = 0x44, followed immediately by an inline data_t for block datums. */
typedef struct {
  char name[0x20]; ///< offset=0x00  cache name
  void (*delete_cb)(int); ///< offset=0x20  called on block removal
  int (*query_cb)(int); ///< offset=0x24  query callback
  int page_count; ///< offset=0x28
  int page_size_bits; ///< offset=0x2c
  int field_30; ///< offset=0x30  initialized to 1
  int first_block_index; ///< offset=0x34  datum handle of first block
  int last_block_index; ///< offset=0x38  datum handle of last block
  data_t *blocks; ///< offset=0x3c  pointer to inline data_t at +0x44
  int signature; ///< offset=0x40  LRUV_CACHE_SIGNATURE
} lruv_cache_t;

/* Block datum entry within the cache's data_t.
 * size = 0x1c per datum. Fields beyond offset 0x10 are unknown. */
typedef struct {
  int16_t salt; ///< offset=0x00  datum identifier
  char pad_02[2]; ///< offset=0x02
  int page_count; ///< offset=0x04
  int first_page_index; ///< offset=0x08
  int next_block_index; ///< offset=0x0c  datum handle of next block
  int previous_block_index; ///< offset=0x10  datum handle of previous block
  char unk_14[8]; ///< offset=0x14
} lruv_cache_block_t;

/* FUN_0011d010 (0x11d010) — XBE naked draft (batch 92). */
#if defined(__clang__)
static void (*const b11d010_c11d010)(int cache, void *entry) = FUN_0011d010;
static char * (*const b11d010_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b11d010_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11d010_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_0011d010(int cache __attribute__((unused)), void *entry __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "andl $0xfffffffe, %%eax\n\t"
      "cmpl $0x55626c6a, %%eax\n\t"
      "jne .LFUN_0011d010_1\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0011d010_1\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c11d010]\n\t"
      "movl 0x34(%%esi), %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "subl %%ecx, %%eax\n\t"
      "js .LFUN_0011d010_1\n\t"
      "movl 0x24(%%esi), %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      "cmpl 0x28(%%esi), %%ecx\n\t"
      "jg .LFUN_0011d010_1\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "cmpl 0x3c(%%esi), %%edx\n\t"
      "jb .LFUN_0011d010_2\n\t"
      ".LFUN_0011d010_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x156\n\t"
      "pushl $0x28fa1c\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0x28f9e8\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011d010_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c11d010] "m"(b11d010_c11d010), [c8d9d0] "m"(b11d010_c8d9d0), [assert] "m"(b11d010_assert), [exitfn] "m"(b11d010_exitfn)
      : "memory");
}
#else
#error "FUN_0011d010: clang naked draft required"
#endif


/* 0x11d110: Allocate and initialize an lru_cache. Rounds the per-element size
 * (block_size + 0x10 block header) up to a 4-byte multiple, derives the
 * element count from total_size, and allocates the 0x48-byte cache header. If
 * the caller supplies no backing buffer, allocates the data buffer itself and
 * records ownership in the byte at +0x38 (freed by lru_cache_dispose). NULL
 * callbacks default to the file-local stubs FUN_0011cfd0 / FUN_0011cfe0.
 * Writes the 'curl' signature (0x6c727563) at +0x44 and copies the name into
 * name[0x20] at +0 (NUL-terminated at +0x1f). Runs the pointer-refresh helper
 * (FUN_0011d090, cache in @eax) before returning the cache pointer, or 0 if
 * the data-buffer allocation failed. Both assert-fail paths halt via
 * halt_and_catch_fire. Source: c:\halo\SOURCE\memory\lru_cache.c */
void *FUN_0011d110(const char *name, int total_size, int block_size,
                   void *delete_callback, void *query_callback, void *buffer)
{
  char *cache;
  unsigned int element_size;
  int element_count;
  char owns_buffer;

  if (block_size < 0) {
    display_assert("block_size>=0", "c:\\halo\\SOURCE\\memory\\lru_cache.c",
                   0x5e, 1);
    system_exit(-1);
  }
  if (total_size < block_size) {
    display_assert("total_size>=block_size",
                   "c:\\halo\\SOURCE\\memory\\lru_cache.c", 0x5f, 1);
    system_exit(-1);
  }
  if ((delete_callback == (void *)0) || (query_callback == (void *)0)) {
    delete_callback = (void *)FUN_0011cfd0;
    query_callback = (void *)FUN_0011cfe0;
  }
  element_size = (unsigned int)block_size + 0x10;
  if ((element_size & 3) != 0) {
    element_size = (element_size | 3) + 1;
  }
  element_count = total_size / (int)element_size;
  cache = (char *)debug_malloc(0x48, 0, "c:\\halo\\SOURCE\\memory\\lru_cache.c",
                               0x6e);
  if (cache != (char *)0) {
    owns_buffer = 0;
    if (buffer == (void *)0) {
      buffer = debug_malloc(element_count * element_size, 0,
                            "c:\\halo\\SOURCE\\memory\\lru_cache.c", 0x75);
      owns_buffer = 1;
      if (buffer == (void *)0) {
        debug_free(cache, "c:\\halo\\SOURCE\\memory\\lru_cache.c", 0x8e);
        return (void *)0;
      }
    }
    csmemset(cache, 0, 0x48);
    *(int *)(cache + 0x20) = element_count;
    *(void **)(cache + 0x2c) = delete_callback;
    *(void **)(cache + 0x34) = buffer;
    *(int *)(cache + 0x3c) = 0;
    *(int *)(cache + 0x40) = 0;
    *(unsigned int *)(cache + 0x24) = element_size;
    *(unsigned int *)(cache + 0x28) =
      (unsigned int)element_count * element_size;
    *(unsigned int *)(cache + 0x44) = 0x6c727563;
    *(void **)(cache + 0x30) = query_callback;
    *(unsigned char *)(cache + 0x38) = (unsigned char)owns_buffer;
    csstrncpy(cache, name, 0x1f);
    *(char *)(cache + 0x1f) = 0;
    FUN_0011d090((int)cache);
  }
  return cache;
}

/* lru_cache_dispose (0x11d250) — readable C lift. */
void lru_cache_dispose(void *cache)
{
  extern char DAT_0028fa1c[];
  char *c = (char *)cache;
  FUN_0011d090((int)cache);
  if (c[0x38])
    debug_free(*(void **)(c + 0x34), DAT_0028fa1c, 0x9c);
  debug_free(cache, DAT_0028fa1c, 0x9d);
}

/* 0x11d2a0: Flush all cached entries. Runs the teardown helper
 * (FUN_0011d090, cache in @eax), then iterates the fixed-stride element
 * array whose base is at cache+0x34, count at cache+0x40, element stride at
 * cache+0x24. For each element it calls FUN_0011d010(cache, entry) and then
 * the per-entry callback (cdecl fn ptr at cache+0x30) with the first dword
 * of the element (*entry). Finally resets the element count at cache+0x40 to
 * zero. Raw offset access matches the sibling cache accessors in this TU
 * (lruv_cache_t offsets 0x24/0x30/0x40 differ from this cache header). */
void FUN_0011d2a0(int cache)
{
  int index;
  int *entry;

  FUN_0011d090(cache);
  entry = *(int **)(cache + 0x34);
  index = 0;
  if (*(int *)(cache + 0x40) < 1) {
    *(int *)(cache + 0x40) = 0;
    return;
  }
  do {
    FUN_0011d010(cache, entry);
    (*(void (**)(int))(cache + 0x30))(*entry);
    index = index + 1;
    entry = (int *)((int)entry + *(int *)(cache + 0x24));
  } while (index < *(int *)(cache + 0x40));
  *(int *)(cache + 0x40) = 0;
}

/* 0x11d3f0: lru_cache entry commit helper.
 * lruv_cache.obj (asserts against c:\halo\SOURCE\memory\lru_cache.c, line
 * 0x156).
 *
 * Refreshes the cache's function pointers (FUN_0011d090, cache passed in EAX),
 * validates the block-header integrity (FUN_0011d010, which checks magic
 * 0x55626c6a and asserts "lru cache ... appears to be corrupt"), then sets
 * bit 0 (valid/in-use flag) in the block-header status word.
 *
 * param_1 (cache) = lru cache ptr. param_2 (block) = pointer just past a block
 * header; header fields live at block-0x10 (block base, passed to the
 * validator) and block-0xc (status word that receives the |1).
 */
void FUN_0011d3f0(int cache, int block)
{
  FUN_0011d090(cache);
  FUN_0011d010(cache, (void *)(block - 0x10));
  *(unsigned int *)(block - 0xc) |= 1;
}

/* 0x11d420: lru_cache entry release helper (mirror of FUN_0011d3f0).
 * lruv_cache.obj.
 *
 * Refreshes the cache's function pointers (FUN_0011d090, cache passed in EAX),
 * validates the block-header integrity (FUN_0011d010, which checks magic
 * 0x55626c6a and asserts "lru cache ... appears to be corrupt"), then clears
 * bit 0 (valid/in-use flag) in the block-header status word.
 *
 * param_1 (cache) = lru cache ptr. param_2 (block) = pointer just past a block
 * header; header fields live at block-0x10 (block base, passed to the
 * validator) and block-0xc (status word that receives the &= ~1). Disasm:
 * mov eax,edi (cache->EAX); call 0x11d090; push (block-0x10); push cache;
 * call 0x11d010; mov eax,[esi+4]; and eax,0xfffffffe; mov [esi+4],eax.
 */
void FUN_0011d420(int cache, int block)
{
  FUN_0011d090(cache);
  FUN_0011d010(cache, (void *)(block - 0x10));
  *(unsigned int *)(block - 0xc) &= 0xfffffffe;
}

/* 0x11d450: lru_cache entry acquire/stamp helper. Sibling of FUN_0011d420.
 * lruv_cache.obj.
 *
 * Refreshes the cache's function pointers (FUN_0011d090, cache passed in EAX),
 * validates the block-header integrity (FUN_0011d010, header at block-0x10),
 * then stamps the block header field at block-8 with the cache's current
 * sequence counter (cache+0x3c) and post-increments that counter.
 *
 * param_1 (cache) = lru cache ptr. param_2 (block) = pointer just past a block
 * header; header base is block-0x10 (passed to the validator), the stamp field
 * is block-8 (= (block-0x10)+8). Disasm: mov eax,esi (cache->EAX);
 * add edi,-0x10 (edi=block-0x10); call 0x11d090; push edi; push esi;
 * call 0x11d010; mov eax,[esi+0x3c]; mov [edi+8],eax; mov eax,[esi+0x3c];
 * inc eax; mov [esi+0x3c],eax. The counter is loaded twice (old value stored,
 * then reloaded and incremented).
 */
void FUN_0011d450(int cache, int block)
{
  FUN_0011d090(cache);
  FUN_0011d010(cache, (void *)(block - 0x10));
  *(int *)(block - 8) = *(int *)(cache + 0x3c);
  *(int *)(cache + 0x3c) = *(int *)(cache + 0x3c) + 1;
}

/* 0x11d480: Compute the total allocation size needed for an lruv_cache
 * with the given maximum block count. Returns sizeof(lruv_cache_t) + data
 * allocation for the block datums. */
int lruv_cache_allocation_size(int maximum_block_count)
{
  return data_allocation_size(maximum_block_count, 0x1c) + 0x44;
}

/* 0x11d4a0: Set the delete and query callbacks on an lruv_cache.
 * param_1 must be non-NULL (asserted). Writes delete_cb to offset 0x20
 * and query_cb to offset 0x24 of the cache header. */
void lruv_cache_set_callbacks(void *cache, void (*delete_cb)(int),
                              int (*query_cb)(int))
{
  lruv_cache_t *c;
  assert_halt(cache);
  c = (lruv_cache_t *)cache;
  c->delete_cb = delete_cb;
  c->query_cb = query_cb;
}

/* 0x11d4f0: Return non-zero if the cache has a query callback set.
 * param_1 must be non-NULL (asserted). Returns bool: query_cb != NULL. */
bool lruv_cache_has_query_cb(void *cache)
{
  lruv_cache_t *c;
  assert_halt(cache);
  c = (lruv_cache_t *)cache;
  return c->query_cb != 0;
}

/* 0x11d550: Verify the integrity of an lruv_cache.
 * Checks the signature, validates the data_t, and optionally walks
 * the linked list verifying forward/backward consistency and page ordering. */
void lruv_cache_verify(void *cache, char do_full_check)
{
  lruv_cache_t *c = (lruv_cache_t *)cache;

  assert_halt(cache);
  assert_halt(c->signature == LRUV_CACHE_SIGNATURE);

  data_verify(c->blocks);

  if (do_full_check) {
    int block_index = c->first_block_index;

    while (block_index != NONE) {
      lruv_cache_block_t *block =
        (lruv_cache_block_t *)datum_get(c->blocks, block_index);

      if (block->previous_block_index == NONE) {
        assert_halt(c->first_block_index == block_index);
      } else {
        lruv_cache_block_t *previous_block = (lruv_cache_block_t *)datum_get(
          c->blocks, block->previous_block_index);
        assert_halt(previous_block->next_block_index == block_index);
        assert_halt(previous_block->first_page_index < block->first_page_index);
        assert_halt(previous_block->first_page_index +
                      previous_block->page_count <=
                    block->first_page_index);
      }

      if (block->next_block_index == NONE) {
        assert_halt(c->last_block_index == block_index);
      } else {
        lruv_cache_block_t *next_block =
          (lruv_cache_block_t *)datum_get(c->blocks, block->next_block_index);
        assert_halt(next_block->previous_block_index == block_index);
        assert_halt(next_block->first_page_index > block->first_page_index);
        assert_halt(block->first_page_index + block->page_count <=
                    next_block->first_page_index);
      }

      block_index = block->next_block_index;
    }
  }
}

/* 0x11d780: Initialize an lruv_cache in pre-allocated memory.
 * Sets up the name, callbacks, page configuration, and the inline data_t
 * for block tracking. */
void lruv_cache_initialize(void *cache, int name, int page_count,
                           int page_size_bits, int maximum_block_count,
                           void (*delete_cb)(int), int (*query_cb)(int))
{
  lruv_cache_t *c = (lruv_cache_t *)cache;
  data_t *blocks = (data_t *)((char *)cache + 0x44);

  assert_halt(name);
  assert_halt(page_count > 0);
  assert_halt(page_size_bits > 0 && page_size_bits < 16);
  assert_halt(maximum_block_count > 0);

  data_initialize(blocks, (char *)name, maximum_block_count, 0x1c);
  data_delete_all(blocks);
  csmemset(cache, 0, 0x44);
  csstrncpy((char *)cache, (const char *)name, 0x1f);

  c->delete_cb = delete_cb;
  c->page_count = page_count;
  c->query_cb = query_cb;
  c->page_size_bits = page_size_bits;
  c->blocks = blocks;
  c->signature = LRUV_CACHE_SIGNATURE;
  c->first_block_index = NONE;
  c->last_block_index = NONE;
  c->field_30 = 1;

  lruv_cache_verify(cache, 1);
}

/* 0x11d890: Dispose of an lruv_cache. Verifies integrity, disposes the
 * underlying data_t, zeros the header, and frees the memory. */
void lruv_cache_dispose(void *cache)
{
  lruv_cache_t *c = (lruv_cache_t *)cache;

  lruv_cache_verify(cache, 1);
  /* blocks is inline at cache+0x44 (not debug_malloc'd), and cache itself is
     game_state_malloc'd — neither has a debug header. Original calls
     data_dispose + debug_free here, which fires non-fatal asserts. */
  data_delete_all(c->blocks);
  csmemset(cache, 0, 0x44);
}

/* 0x11d8d0: Idle tick for an lruv_cache. Runs the fast integrity check
 * (do_full_check=0) and increments the counter at offset 0x30. */
void lruv_idle(void *cache)
{
  lruv_cache_t *c = (lruv_cache_t *)cache;

  lruv_cache_verify(cache, 0);
  c->field_30 = c->field_30 + 1;
}

/* 0x11d8f0: Remove a single block from the cache's linked list and
 * delete the datum. Calls the delete callback if set. Relinks neighbors. */
void lruv_block_delete(void *cache, int block_index)
{
  lruv_cache_t *c = (lruv_cache_t *)cache;
  lruv_cache_block_t *block =
    (lruv_cache_block_t *)datum_get(c->blocks, block_index);

  lruv_cache_verify(cache, 1);

  if (c->delete_cb != NULL) {
    c->delete_cb(block_index);
  }

  /* Unlink from previous neighbor */
  if (block->previous_block_index == NONE) {
    assert_halt(c->first_block_index == block_index);
    c->first_block_index = block->next_block_index;
  } else {
    lruv_cache_block_t *prev =
      (lruv_cache_block_t *)datum_get(c->blocks, block->previous_block_index);
    prev->next_block_index = block->next_block_index;
  }

  /* Unlink from next neighbor */
  if (block->next_block_index == NONE) {
    assert_halt(c->last_block_index == block_index);
    c->last_block_index = block->previous_block_index;
  } else {
    lruv_cache_block_t *next =
      (lruv_cache_block_t *)datum_get(c->blocks, block->next_block_index);
    next->previous_block_index = block->previous_block_index;
  }

  datum_delete(c->blocks, block_index);
  lruv_cache_verify(cache, 1);
}

/* lruv_debug_to_file (0x11d9d0)
 *
 * Touch a cache block — set its last-access stamp to the cache's
 * current frame counter (field_30).
 */
void lruv_debug_to_file(void *cache, int datum_handle)
{
  lruv_cache_t *c = (lruv_cache_t *)cache;
  lruv_cache_block_t *block;

  lruv_cache_verify(cache, 0);
  block = (lruv_cache_block_t *)datum_get(c->blocks, datum_handle);
  *(int *)((char *)block + 0x14) = c->field_30;
}

/* lruv_block_get_address (0x11da00)
 *
 * Return the base page address of a cache block: the block's
 * first_page_index (entry+0x8) shifted left by the cache's
 * page_size_bits (cache+0x2c, masked to the low 5 bits).  Runs the
 * fast integrity check before the datum lookup.
 */
int lruv_block_get_address(void *lruv, int block_index)
{
  lruv_cache_t *c = (lruv_cache_t *)lruv;
  lruv_cache_block_t *block;

  lruv_cache_verify(lruv, 0);
  block = (lruv_cache_block_t *)datum_get(c->blocks, block_index);
  return block->first_page_index << (c->page_size_bits & 0x1f);
}

/* lruv_block_touched (0x11da30) — readable C lift from XBE leaf. */
bool lruv_block_touched(void *lruv, int block_index)
{
  void *block;
  int delta;

  lruv_cache_verify(lruv, 0);
  block = datum_get(*(void **)((char *)lruv + 0x3c), block_index);
  delta = *(int *)((char *)block + 0x14) - *(int *)((char *)lruv + 0x30);
  return delta == 0;
}




/* lruv_cache_get_page_usage (0x11da60) — XBE naked draft (batch 88). */
#if defined(__clang__)
static void (*const b11da60_c11d550)(void *cache, char do_full_check) = lruv_cache_verify;
static void *(*const b11da60_memset)(void *, int, unsigned int) = csmemset;
static void (*const b11da60_c1197b0)(data_iter_t *iter, data_t *data) = data_iterator_new;
static void * (*const b11da60_c119810)(data_iter_t *iterator) = data_iterator_next;

__attribute__((naked, noinline))
void lruv_cache_get_page_usage(void *cache __attribute__((unused)), unsigned char *usage __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "call *%[c11d550]\n\t"
      "movl 0x28(%%edi), %%eax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "movl 0x3c(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1197b0]\n\t"
      "leal -0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c119810]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x20, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Llruv_cache_get_page_usage_5\n\t"
      "pushl %%ebx\n\t"
      ".Llruv_cache_get_page_usage_1:\n\t"
      "movl 0x24(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movb $1, %%bl\n\t"
      "je .Llruv_cache_get_page_usage_2\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%%eax\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Llruv_cache_get_page_usage_2\n\t"
      "movb $9, %%bl\n\t"
      ".Llruv_cache_get_page_usage_2:\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "movl 0x30(%%edi), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jne .Llruv_cache_get_page_usage_3\n\t"
      "orb $2, %%bl\n\t"
      ".Llruv_cache_get_page_usage_3:\n\t"
      "addl $0x1e, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jae .Llruv_cache_get_page_usage_4\n\t"
      "orb $4, %%bl\n\t"
      ".Llruv_cache_get_page_usage_4:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movzbl %%bl, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119810]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Llruv_cache_get_page_usage_1\n\t"
      "popl %%ebx\n\t"
      ".Llruv_cache_get_page_usage_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c11d550] "m"(b11da60_c11d550), [memset] "m"(b11da60_memset), [c1197b0] "m"(b11da60_c1197b0), [c119810] "m"(b11da60_c119810)
      : "memory");
}
#else
#error "lruv_cache_get_page_usage: clang naked draft required"
#endif


/* lruv_resize (0x11db00)
 *
 * Resize the lruv_cache to new_page_count pages.  Any block whose
 * page range (first_page_index + page_count) exceeds the new limit is
 * evicted via lruv_block_delete before the page_count field is updated.
 */
void lruv_resize(void *cache, int new_page_count)
{
  lruv_cache_t *c = (lruv_cache_t *)cache;
  lruv_cache_block_t *block;
  data_iter_t iter;

  assert_halt(new_page_count > 0);
  lruv_cache_verify(cache, 1);
  data_iterator_new(&iter, c->blocks);

  block = (lruv_cache_block_t *)data_iterator_next(&iter);
  while (block != NULL) {
    if (block->first_page_index + block->page_count > new_page_count) {
      lruv_block_delete(cache, iter.datum_handle);
    }
    block = (lruv_cache_block_t *)data_iterator_next(&iter);
  }

  c->page_count = new_page_count;
}

/* FUN_0011db90 (0x11db90)
 *
 * Dump LRUV cache diagnostic state to a file.  Used when a cache
 * allocation fails to record page layout, block occupancy, and
 * per-block age for post-mortem analysis.
 */
void FUN_0011db90(const char *path, const char *tag_name, int alloc_size,
                  void *cache, void *fn1, void *fn2)
{
  lruv_cache_t *c = (lruv_cache_t *)cache;
  void *stream;
  int page_size, pages_needed, total_pages;
  int page_index, block_handle;
  int page_count, age;
  bool locked;
  const char *block_name;

  lruv_cache_verify(cache, 1);

  stream = crt_fopen(path, (const char *)0x28fdcc);
  if (stream == NULL)
    return;

  crt_fprintf(stream, "%s (v1: only blocks used this frame are locked)\n",
              cache);
  ((void (*)(void *))fn1)(stream);

  page_size = 1 << (c->page_size_bits & 0x1f);
  pages_needed = alloc_size >> (c->page_size_bits & 0x1f);
  if ((alloc_size & (page_size - 1)) != 0)
    pages_needed++;

  crt_fprintf(stream,
              "\n#%d pages, each #%d bytes\n"
              "#%d blocks at frame index #%d\n"
              "failed allocation of \"%s\" was #%d bytes (#%d pages)\n\n",
              c->page_count, page_size,
              (int)*(int16_t *)((char *)c->blocks + 0x30), c->field_30,
              tag_name, alloc_size, pages_needed);

  total_pages = c->page_count;
  block_handle = c->first_block_index;
  page_index = 0;

  while (page_index < total_pages) {
    age = 0;
    locked = false;

    if (block_handle == -1) {
      page_count = total_pages - page_index;
      page_index = total_pages;
      block_name = (const char *)0x25386f;
    } else {
      lruv_cache_block_t *block =
        (lruv_cache_block_t *)datum_get(c->blocks, block_handle);

      if (page_index != block->first_page_index) {
        page_count = block->first_page_index - page_index;
        assert_halt(page_count > 0);
        page_index = block->first_page_index;
        block_name = (const char *)0x25386f;
      } else {
        page_count = block->page_count;
        age = c->field_30 - *(int *)((char *)block + 0x14);

        if (c->query_cb != NULL) {
          locked = c->query_cb(block_handle) != 0;
        } else {
          locked = false;
        }
        if (*(int *)((char *)block + 0x14) + 1 >= (unsigned int)c->field_30)
          locked = true;

        page_index = block->first_page_index + block->page_count;
        block_name = ((const char *(*)(int))fn2)(block_handle);
        block_handle = block->next_block_index;
        if (block_name == NULL)
          block_name = (const char *)0x25386f;
      }
    }

    if (age > 9999)
      age = 9999;

    crt_fprintf(stream, "%s % 5d% 5d %s\n",
                locked ? (const char *)0x28fd20 : (const char *)0x25b06c,
                page_count, age, block_name);

    total_pages = c->page_count;
  }

  crt_fprintf(stream, (const char *)0x260ee4);
  crt_fclose(stream);
}

/* 0x11dd60: Allocate and initialize a new lruv_cache on the debug heap.
 * Computes the datum-array allocation for maximum_block_count records of
 * 0x1c bytes (data_allocation_size), adds the 0x44-byte cache header, and
 * allocates via debug_malloc. If allocation succeeds, initializes the cache
 * with the caller's parameters and callbacks. Returns the cache pointer, or
 * NULL on allocation failure.
 *
 * Disasm note: Ghidra mis-groups the cdecl args here — MSVC pushes the outer
 * debug_malloc args (zero=0, __FILE__, __LINE__=0x52) before evaluating the
 * inner data_allocation_size(param_4, 0x1c) call, so the decompiler wrongly
 * shows those three as extra data_allocation_size arguments.
 * data_allocation_size is 2-arg (count, size); debug_malloc is 4-arg (size,
 * zero, file, line). */
void *lruv_new(int name, int page_count, int page_size_bits,
               int maximum_block_count, void (*delete_cb)(int),
               int (*query_cb)(int))
{
  void *cache;

  cache = debug_malloc(data_allocation_size(maximum_block_count, 0x1c) + 0x44,
                       0, "c:\\halo\\SOURCE\\memory\\lruv_cache.c", 0x52);
  if (cache != NULL) {
    lruv_cache_initialize(cache, name, page_count, page_size_bits,
                          maximum_block_count, delete_cb, query_cb);
  }
  return cache;
}

/* 0x11ddc0: Dispose all blocks from the cache by iterating the data_t
 * and removing each block individually via lruv_block_delete. */
void lruv_cache_dispose_all(void *cache)
{
  lruv_cache_t *c = (lruv_cache_t *)cache;
  data_iter_t iter;

  lruv_cache_verify(cache, 1);
  data_iterator_new(&iter, c->blocks);

  while (data_iterator_next(&iter) != NULL) {
    lruv_block_delete(cache, iter.datum_handle);
  }
}

/* 0x1bfe90: Allocate and initialize a new lruv_cache from game state memory.
 * Returns a pointer to the initialized cache. */
void *lruv_cache_new(const char *name, int capacity, int max_locked,
                     int entry_size, void (*delete_cb)(int),
                     int (*query_cb)(int))
{
  int alloc_size = lruv_cache_allocation_size(entry_size);
  void *cache = game_state_malloc(name, "lruv cache", alloc_size);

  lruv_cache_initialize(cache, (int)name, capacity, max_locked, entry_size,
                        delete_cb, query_cb);

  return cache;
}

/* FUN_0011de10 (0x11de10) — XBE naked draft (batch 79). */
#if defined(__clang__)
static void (*const b11de10_chkstk)(void) = FUN_001d90e0;
static void (*const b11de10_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b11de10_exitfn)(int) = system_exit;
static void *(*const b11de10_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const b11de10_c1197b0)(data_iter_t *iter, data_t *data) = data_iterator_new;
static void * (*const b11de10_c119810)(data_iter_t *iterator) = data_iterator_next;
static void (*const b11de10_c11d8f0)(void *cache, int block_index) = lruv_block_delete;
static int (*const b11de10_c119610)(data_t *data) = data_new_at_index;
static void (*const b11de10_c11d550)(void *cache, char do_full_check) = lruv_cache_verify;

__attribute__((naked, noinline))
int FUN_0011de10(void *cache __attribute__((unused)), unsigned int size __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x1048, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl 0x2c(%%ebx), %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl $1, %%esi\n\t"
      "shll %%cl, %%esi\n\t"
      "movl %%eax, %%edx\n\t"
      "sarl %%cl, %%edx\n\t"
      "pushl %%edi\n\t"
      "decl %%esi\n\t"
      "testl %%esi, %%eax\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "je .LFUN_0011de10_1\n\t"
      "incl %%edx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      ".LFUN_0011de10_1:\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "testl %%edx, %%edx\n\t"
      "movb $0, 0xf(%%ebp)\n\t"
      "movl %%esi, -0x18(%%ebp)\n\t"
      "jg .LFUN_0011de10_2\n\t"
      "pushl $1\n\t"
      "pushl $0xe1\n\t"
      "pushl $0x28fa90\n\t"
      "pushl $0x28ff0c\n\t"
      "call *%[assert]\n\t"
      "pushl %%esi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011de10_2:\n\t"
      "movl 0x34(%%ebx), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x28(%%ebx), %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%esi, -0x20(%%ebp)\n\t"
      "jg .LFUN_0011de10_4\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011de10_3:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0011de10_4:\n\t"
      "cmpw $0xff, %%cx\n\t"
      "jne .LFUN_0011de10_5\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_0011de10_6\n\t"
      ".LFUN_0011de10_5:\n\t"
      "movswl %%cx, %%eax\n\t"
      "incl %%eax\n\t"
      ".LFUN_0011de10_6:\n\t"
      "movswl -0x4(%%ebp), %%esi\n\t"
      "cmpl %%esi, %%eax\n\t"
      "je .LFUN_0011de10_8\n\t"
      "movl -0x20(%%ebp), %%esi\n\t"
      "movswl %%cx, %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "cmpw $0xff, -0x8(%%ebp)\n\t"
      "leal -0x1048(%%ebp,%%eax,1), %%eax\n\t"
      "movl %%esi, (%%eax)\n\t"
      "movl %%edi, 0x8(%%eax)\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl %%edx, 0xc(%%eax)\n\t"
      "jne .LFUN_0011de10_7\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_0011de10_8\n\t"
      ".LFUN_0011de10_7:\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      ".LFUN_0011de10_8:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_0011de10_14\n\t"
      "movl 0x28(%%ebx), %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "subl %%edi, %%ebx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "movl %%eax, %%edi\n\t"
      ".LFUN_0011de10_9:\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "cmpw -0x8(%%ebp), %%si\n\t"
      "je .LFUN_0011de10_29\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_0011de10_10:\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movswl %%si, %%eax\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "shll $4, %%eax\n\t"
      "movl -0x1044(%%ebp,%%eax,1), %%edx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "leal -0x1048(%%ebp,%%eax,1), %%eax\n\t"
      "jbe .LFUN_0011de10_11\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      ".LFUN_0011de10_11:\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "addl %%ebx, %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "movl %%edx, 0xc(%%eax)\n\t"
      "jl .LFUN_0011de10_26\n\t"
      "movb 0xf(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_0011de10_13\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl -0x2c(%%ebp), %%ebx\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "jb .LFUN_0011de10_12\n\t"
      "jne .LFUN_0011de10_22\n\t"
      "cmpl -0x24(%%ebp), %%edx\n\t"
      "jge .LFUN_0011de10_22\n\t"
      ".LFUN_0011de10_12:\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      ".LFUN_0011de10_13:\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "movl %%ecx, -0x28(%%ebp)\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "movb $1, 0xf(%%ebp)\n\t"
      "jmp .LFUN_0011de10_23\n\t"
      ".LFUN_0011de10_14:\n\t"
      "movl 0x3c(%%ebx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%eax, %%edi\n\t"
      "jne .LFUN_0011de10_20\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl 0x24(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl 0x14(%%esi), %%edx\n\t"
      "movl 0x4(%%esi), %%ebx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "je .LFUN_0011de10_15\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%%eax\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0011de10_15\n\t"
      "movb $1, %%cl\n\t"
      "jmp .LFUN_0011de10_16\n\t"
      ".LFUN_0011de10_15:\n\t"
      "xorb %%cl, %%cl\n\t"
      ".LFUN_0011de10_16:\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "cmpl 0x30(%%edi), %%eax\n\t"
      "jne .LFUN_0011de10_17\n\t"
      "movb $1, %%cl\n\t"
      "jmp .LFUN_0011de10_19\n\t"
      ".LFUN_0011de10_17:\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_0011de10_19\n\t"
      "cmpl $-1, -0x18(%%ebp)\n\t"
      "je .LFUN_0011de10_18\n\t"
      "cmpl -0x38(%%ebp), %%eax\n\t"
      "jae .LFUN_0011de10_19\n\t"
      ".LFUN_0011de10_18:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      ".LFUN_0011de10_19:\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl 0x4(%%esi), %%edi\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "addl %%eax, %%edi\n\t"
      "testb %%cl, %%cl\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "je .LFUN_0011de10_9\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .LFUN_0011de10_29\n\t"
      ".LFUN_0011de10_20:\n\t"
      "subl %%edi, %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "jg .LFUN_0011de10_21\n\t"
      "pushl $1\n\t"
      "pushl $0x137\n\t"
      "pushl $0x28fa90\n\t"
      "pushl $0x28fcec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011de10_21:\n\t"
      "movl 0x8(%%esi), %%edi\n\t"
      "jmp .LFUN_0011de10_9\n\t"
      ".LFUN_0011de10_22:\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      ".LFUN_0011de10_23:\n\t"
      "cmpw %%si, -0x4(%%ebp)\n\t"
      "je .LFUN_0011de10_24\n\t"
      "pushl $1\n\t"
      "pushl $0x15f\n\t"
      "pushl $0x28fa90\n\t"
      "pushl $0x28fef0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011de10_24:\n\t"
      "cmpw $0xff, -0x4(%%ebp)\n\t"
      "jne .LFUN_0011de10_25\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jmp .LFUN_0011de10_26\n\t"
      ".LFUN_0011de10_25:\n\t"
      "incl -0x4(%%ebp)\n\t"
      ".LFUN_0011de10_26:\n\t"
      "cmpw $0xff, %%si\n\t"
      "jne .LFUN_0011de10_27\n\t"
      "xorl %%esi, %%esi\n\t"
      "jmp .LFUN_0011de10_28\n\t"
      ".LFUN_0011de10_27:\n\t"
      "movl -0x34(%%ebp), %%esi\n\t"
      "incl %%esi\n\t"
      ".LFUN_0011de10_28:\n\t"
      "cmpw -0x8(%%ebp), %%si\n\t"
      "jne .LFUN_0011de10_10\n\t"
      ".LFUN_0011de10_29:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl 0x28(%%eax), %%edi\n\t"
      "jl .LFUN_0011de10_3\n\t"
      "movb 0xf(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0011de10_46\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl 0x3c(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1197b0]\n\t"
      "leal -0x48(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119810]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011de10_33\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl -0x28(%%ebp), %%edi\n\t"
      "leal (%%ecx,%%edi,1), %%esi\n\t"
      ".LFUN_0011de10_30:\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "jge .LFUN_0011de10_32\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "addl %%ecx, %%edx\n\t"
      "cmpl %%edi, %%edx\n\t"
      "jle .LFUN_0011de10_32\n\t"
      "movl 0x24(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011de10_31\n\t"
      "movl -0x40(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%%eax\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0011de10_31\n\t"
      "pushl $1\n\t"
      "pushl $0x177\n\t"
      "pushl $0x28fa90\n\t"
      "pushl $0x28fea8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011de10_31:\n\t"
      "movl -0x40(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c11d8f0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0011de10_32:\n\t"
      "leal -0x48(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119810]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0011de10_30\n\t"
      ".LFUN_0011de10_33:\n\t"
      "movl 0x3c(%%ebx), %%eax\n\t"
      "movw 0x30(%%eax), %%cx\n\t"
      "cmpw 0x20(%%eax), %%cx\n\t"
      "jne .LFUN_0011de10_37\n\t"
      "movl -0x18(%%ebp), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_0011de10_37\n\t"
      "cmpl %%esi, -0x30(%%ebp)\n\t"
      "jne .LFUN_0011de10_34\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x10(%%eax), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      ".LFUN_0011de10_34:\n\t"
      "movl 0x3c(%%ebx), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0011de10_35\n\t"
      "pushl $1\n\t"
      "pushl $0x188\n\t"
      "pushl $0x28fa90\n\t"
      "pushl $0x28fe6c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011de10_35:\n\t"
      "movl 0x24(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0011de10_36\n\t"
      "pushl %%esi\n\t"
      "call *%%eax\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0011de10_36\n\t"
      "pushl $1\n\t"
      "pushl $0x189\n\t"
      "pushl $0x28fa90\n\t"
      "pushl $0x28fe18\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011de10_36:\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c11d8f0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0011de10_37:\n\t"
      "movl 0x3c(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c119610]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_0011de10_44\n\t"
      "movl 0x3c(%%ebx), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_0011de10_41\n\t"
      "movl 0x34(%%ebx), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_0011de10_39\n\t"
      "cmpl $-1, 0x38(%%ebx)\n\t"
      "je .LFUN_0011de10_38\n\t"
      "pushl $1\n\t"
      "pushl $0x198\n\t"
      "pushl $0x28fa90\n\t"
      "pushl $0x28fdf8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011de10_38:\n\t"
      "movl $0xffffffff, 0x10(%%esi)\n\t"
      "movl 0x34(%%ebx), %%edx\n\t"
      "movl %%edi, 0x38(%%ebx)\n\t"
      "movl %%edx, 0xc(%%esi)\n\t"
      "movl %%edi, 0x34(%%ebx)\n\t"
      "jmp .LFUN_0011de10_43\n\t"
      ".LFUN_0011de10_39:\n\t"
      "pushl %%eax\n\t"
      "movl 0x3c(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x10(%%ebx), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0011de10_40\n\t"
      "pushl $1\n\t"
      "pushl $0x1a0\n\t"
      "pushl $0x28fa90\n\t"
      "pushl $0x28fdd0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0011de10_40:\n\t"
      "movl $0xffffffff, 0x10(%%esi)\n\t"
      "movl %%edi, 0x10(%%ebx)\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl 0x34(%%ebx), %%edx\n\t"
      "movl %%edx, 0xc(%%esi)\n\t"
      "movl %%edi, 0x34(%%ebx)\n\t"
      "jmp .LFUN_0011de10_43\n\t"
      ".LFUN_0011de10_41:\n\t"
      "movl 0x3c(%%ebx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_0011de10_45\n\t"
      "movl 0x38(%%ebx), %%edx\n\t"
      "movl %%edx, 0x10(%%esi)\n\t"
      "movl %%edi, 0x38(%%ebx)\n\t"
      ".LFUN_0011de10_42:\n\t"
      "movl -0x30(%%ebp), %%eax\n\t"
      "movl 0x3c(%%ebx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "movl %%edx, 0xc(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edi, 0xc(%%eax)\n\t"
      ".LFUN_0011de10_43:\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      "movl 0x30(%%ebx), %%edx\n\t"
      "pushl $1\n\t"
      "pushl %%ebx\n\t"
      "movl %%edx, 0x14(%%esi)\n\t"
      "call *%[c11d550]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0011de10_44:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0011de10_45:\n\t"
      "pushl %%eax\n\t"
      "movl 0x3c(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x10(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x10(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edi, 0x10(%%eax)\n\t"
      "jmp .LFUN_0011de10_42\n\t"
      ".LFUN_0011de10_46:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(b11de10_chkstk), [assert] "m"(b11de10_assert), [exitfn] "m"(b11de10_exitfn), [dget] "m"(b11de10_dget), [c1197b0] "m"(b11de10_c1197b0), [c119810] "m"(b11de10_c119810), [c11d8f0] "m"(b11de10_c11d8f0), [c119610] "m"(b11de10_c119610), [c11d550] "m"(b11de10_c11d550)
      : "memory");
}
#else
#error "FUN_0011de10: clang naked draft required"
#endif

