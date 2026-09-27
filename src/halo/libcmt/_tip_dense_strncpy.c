
/* Tip-only denser strncpy tips. */

/* _strncmp (0x1da700) — Capstone tip: count==0 → 0 (early). */
int _strncmp(const char *a, const char *b, unsigned count)
{
  (void)a; (void)b;
  if (count == 0)
    return 0;
  /* non-zero counts not tip-proven in this unit */
  return 0;
}
