/* Tip-only denser stricmp tips. */

/* __chgsign (0x1dd91b) — Capstone tip: flip sign bit of double. */
double __chgsign(double x)
{
  union { double d; unsigned u[2]; } v;
  v.d = x;
  v.u[1] ^= 0x80000000u;
  return v.d;
}
