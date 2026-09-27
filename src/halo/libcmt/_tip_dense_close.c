/* Tip-only denser LIBCMT close tips. */

/* FUN_001dee48 (0x1dee48) — Capstone tip: masked exp field; Inf/NaN returns high. */
unsigned FUN_001dee48(unsigned low, unsigned high)
{
  (void)low;
  if ((high & 0x7ff00000u) != 0x7ff00000u)
    return high & 0x7ff00000u;
  return high;
}

/* ___shl_12 (0x1e5a62) — Capstone tip: shift 96-bit left by 1. */
void ___shl_12(unsigned *x)
{
  unsigned c0 = x[0] >> 31;
  unsigned c1 = x[1] >> 31;
  x[0] = x[0] + x[0];
  x[1] = (x[1] + x[1]) | c0;
  x[2] = (x[2] << 1) | c1;
}

/* ___shr_12 (0x1e5a90) — Capstone tip: shift 96-bit right by 1. */
void ___shr_12(unsigned *x)
{
  unsigned lo = x[0];
  unsigned mid = x[1];
  unsigned hi = x[2];
  x[1] = (mid >> 1) | (hi << 31);
  x[2] = hi >> 1;
  x[0] = (lo >> 1) | (mid << 31);
}

/* FUN_001e35a9 (0x1e35a9) — Capstone tip: wcsnlen-ish; empty → count. */
unsigned FUN_001e35a9(unsigned short *s, unsigned count)
{
  unsigned i;
  if (count == 0)
    return 0;
  for (i = 0; i < count; i++) {
    if (s[i] == 0)
      return i + 1;
  }
  return count;
}

/* __ZeroTail (0x1e3c9c) — Capstone tip: check mantissa tail bits zero. */
int __ZeroTail(unsigned int *man, int bit)
{
  int idx = bit / 32;
  int rem = bit % 32;
  unsigned int mask = ~(0xffffffffu << (31 - rem));
  if (man[idx] & mask)
    return 0;
  for (idx = idx + 1; idx < 3; idx++) {
    if (man[idx] != 0)
      return 0;
  }
  return 1;
}

/* placeholder - chgsign goes to stricmp tip */


/* FUN_001e5753 (0x1e5753) — Capstone tip: null dst → strlen; else bounded copy. */
unsigned FUN_001e5753(unsigned short *dst, const unsigned char *src, unsigned count)
{
  unsigned i;
  if (dst == 0) {
    const unsigned char *p = src;
    while (*p)
      p++;
    return (unsigned)(p - src);
  }
  if (count == 0)
    return 0;
  for (i = 0; i < count; i++) {
    dst[i] = src[i];
    if (src[i] == 0)
      return i;
  }
  return count;
}
