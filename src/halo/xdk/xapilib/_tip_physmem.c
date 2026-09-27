/* Tip-only compile unit for Unicorn proofs (symbols mirror physmem.c tips). */
#include <stdint.h>

int __stdcall QueryPerformanceCounter(void *counter)
{
  unsigned lo, hi;
  void *fn = *(void **)0x253204;
  __asm__ volatile("call *%[fn]" : "=a"(lo), "=d"(hi) : [fn] "r"(fn) : "memory", "ecx");
  ((unsigned *)counter)[0] = lo;
  ((unsigned *)counter)[1] = hi;
  return 1;
}

int __stdcall QueryPerformanceFrequency(void *freq)
{
  unsigned lo, hi;
  void *fn = *(void **)0x253208;
  __asm__ volatile("call *%[fn]" : "=a"(lo), "=d"(hi) : [fn] "r"(fn) : "memory", "ecx");
  ((unsigned *)freq)[0] = lo;
  ((unsigned *)freq)[1] = hi;
  return 1;
}

void __stdcall MmFreeContiguousMemory(void *base_address)
{
  ((void (__stdcall *)(void *))*(void **)0x2531f4)(base_address);
}

unsigned long __stdcall MmQueryAddressProtect(void *virtual_address)
{
  return ((unsigned long (__stdcall *)(void *))*(void **)0x253218)(virtual_address);
}

int __stdcall FUN_001d42a9(int handle, void *buffer, unsigned int size)
{
  ((void (__stdcall *)(int, void *, unsigned int))*(void **)0x253228)(handle + 8, buffer, size);
  return 0;
}

/* physical_memory_protect (0x1d371d) — Capstone tip: size==0 → ret; else MmSetAddressProtect. */
void __stdcall physical_memory_protect(void *addr, unsigned int size, unsigned int protect)
{
  if (size == 0)
    return;
  ((void (__stdcall *)(void *, unsigned int, unsigned int))*(void **)0x253214)(addr, size, protect);
}

/* XapiFormatObjectAttributes (0x1d440e) — Capstone tip: RtlInitUnicodeString + fill OA. */
void __stdcall XapiFormatObjectAttributes(void *oa, void *name, void *uni_dst)
{
  ((void (__stdcall *)(void *, void *))*(void **)0x2530e4)(uni_dst, name);
  ((unsigned *)oa)[1] = (unsigned)(unsigned long)name;
  ((unsigned *)oa)[0] = 0xfffffffc;
  ((unsigned *)oa)[2] = 0x80;
}

/* FUN_001d47c3 (0x1d47c3) — Capstone tip: splice node into allocator list. */
void __stdcall FUN_001d47c3(void *ctx, unsigned *node)
{
  unsigned *blk = *(unsigned **)((char *)ctx + 0x18);
  node[0] = blk[0x13]; /* 0x4c/4 */
  blk[0x13] = (unsigned)(unsigned long)node;
  node[1] = 0;
  node[2] = 0;
}

/* FUN_001d4436 (0x1d4436) — Capstone tip: ms → relative LARGE_INTEGER. */
void *__stdcall FUN_001d4436(void *out, unsigned int ms)
{
  unsigned long long prod;
  unsigned *o = (unsigned *)out;
  if (ms == 0xffffffffu)
    return 0;
  prod = (unsigned long long)ms * 10000ull;
  prod = (unsigned long long)(-(long long)prod);
  o[0] = (unsigned)prod;
  o[1] = (unsigned)(prod >> 32);
  return out;
}

/* FUN_001d52c4 (0x1d52c4) — Capstone tip: heap block usable size from header. */
unsigned int __stdcall FUN_001d52c4(void *heap, unsigned int flags, void *ptr)
{
  unsigned char *p = (unsigned char *)ptr;
  unsigned char al = p[-0xb];
  (void)heap;
  (void)flags;
  if ((al & 1) == 0)
    return 0xffffffffu;
  if (al & 8) {
    unsigned short edx = *(unsigned short *)(p - 0x10);
    unsigned eax = *(unsigned *)(p - 0x18);
    return eax - edx;
  }
  {
    unsigned eax = *(unsigned short *)(p - 0x10);
    unsigned ecx = p[-0xa];
    return (eax << 4) - ecx;
  }
}
