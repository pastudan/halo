/* Tip-only denser xdk_stubs_rt tips. */
#include <stdint.h>

/* FUN_001d040f (0x1d040f) — Capstone tip: zero 16 bytes then pack 4 bytes→words. */
void __stdcall FUN_001d040f(unsigned char *src, unsigned short *dst)
{
  unsigned *d = (unsigned *)dst;
  d[0] = 0;
  d[1] = 0;
  d[2] = 0;
  d[3] = 0;
  dst[1] = src[0];
  dst[3] = src[1];
  dst[2] = src[2];
  dst[4] = src[3];
}
