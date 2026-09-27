/* Tip-only denser vsprintf ctype tips (locale<=1 path). */

/* crt_tolower (0x1da1d8) — Capstone tip: ctype bit0 → c+0x20. */
int crt_tolower(int c)
{
  unsigned char *table;
  int is_upper;
  if (*(int *)0x3317bc > 1) {
    /* MB path not tip-proven */
    return c;
  }
  table = *(unsigned char **)0x3317b4;
  is_upper = table[c * 2] & 1;
  if (is_upper)
    return c + 0x20;
  return c;
}

/* crt_toupper (0x1da19f) — Capstone tip: ctype bit1 → c-0x20. */
int crt_toupper(int c)
{
  unsigned char *table;
  int is_lower;
  if (*(int *)0x3317bc > 1) {
    return c;
  }
  table = *(unsigned char **)0x3317b4;
  is_lower = table[c * 2] & 2;
  if (is_lower)
    return c - 0x20;
  return c;
}
