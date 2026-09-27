/* Tip-only denser physmem tips. */
#include <stdint.h>

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
