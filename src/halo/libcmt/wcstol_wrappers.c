#include "common.h"

/* Thin CRT wrappers — kept out of stricmp.c to avoid naked/decl conflicts. */

long FUN_001dd1d1(const wchar_t *s, wchar_t **endptr, int base)
{
  return FUN_001dd00c(s, endptr, base, 0);
}

unsigned long FUN_001dd1e8(const wchar_t *s, wchar_t **endptr, int base)
{
  return (unsigned long)FUN_001dd00c(s, endptr, base, 1);
}

void FUN_001dde73(void)
{
  FUN_001defb3(4);
}
