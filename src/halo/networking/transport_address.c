/* --- transport_address.obj batch drafts (2026-07-26) --- */

/* transport_address_equivalent (0x81a90) — readable C lift. */
bool transport_address_equivalent(const void *a, const void *b)
{
  const unsigned char *pa = (const unsigned char *)a;
  const unsigned char *pb = (const unsigned char *)b;
  unsigned short na, nb, n;
  if (!pa) {
    display_assert((const char *)0x266090, (const char *)0x265ffc, 0x3b, 1);
    system_exit(-1);
  }
  if (!pb) {
    display_assert((const char *)0x26608c, (const char *)0x265ffc, 0x3c, 1);
    system_exit(-1);
  }
  if (!*(unsigned char *)0x335090) {
    display_assert((const char *)0x265fe4, (const char *)0x265ffc, 0x3d, 1);
    system_exit(-1);
  }
  if (*(short *)(pa + 0x10) != 4) {
    display_assert((const char *)0x266060, (const char *)0x265ffc, 0x3f, 1);
    system_exit(-1);
  }
  if (*(short *)(pb + 0x10) != 4) {
    display_assert((const char *)0x266034, (const char *)0x265ffc, 0x40, 1);
    system_exit(-1);
  }
  na = *(unsigned short *)(pa + 0x10);
  nb = *(unsigned short *)(pb + 0x10);
  n = (na > nb) ? na : nb;
  if (csmemcmp(pa, pb, (int)n) != 0)
    return 0;
  if (*(unsigned short *)(pa + 0x12) != *(unsigned short *)(pb + 0x12))
    return 0;
  return 1;
}



/* 0x81b90 */
const char *transport_address_to_string(void *addr)
{
  int esi = 0;

  /* test esi, esi -> jne 0x81bb8 */
  display_assert((char *)0x002660f8, (char *)0x00265ffc, 74, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x10], 4 -> je 0x81bdc */
  display_assert((char *)0x002660cc, (char *)0x00265ffc, 75, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 4 -> jne 0x81c24 */
  snprintf((char *)0x00334f90, 256, (char *)0x002660b8);
  /* cmp (int16_t)eax, 0x10 -> jne 0x81c6d */
  snprintf((char *)0x00334f90, 256, (char *)0x00266094);
  return NULL;

  (void)esi;
}

/* 0x81c80 */
const char *FUN_00081c80(int error_code)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* cmp eax, 0x17 -> ja 0x81d42 */
  /* test esi, esi -> jne 0x81de1 */
  display_assert((char *)0x00266450, (char *)0x00266458, 57, 0);
  system_exit(0);
  /* cmp eax, ecx -> jle 0x81df6 */
  return NULL;

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* FUN_00081e00 (0x81e00) — readable C lift. */
void FUN_00081e00(uint32_t *key, uint32_t *nonce)
{
  *(uint32_t *)0x5ab210 = key[0];
  *(uint32_t *)0x5ab214 = key[1];
  *(uint32_t *)0x5ab218 = key[2];
  *(uint32_t *)0x5ab21c = key[3];
  *(uint32_t *)0x5ab220 = nonce[0];
  *(uint32_t *)0x5ab224 = nonce[1];
  if (*(int *)0x335094 == 0) {
    /* 0x222de0: XNet thunk, __stdcall RET 8 (2 args). */
    if (((int(__stdcall *)(void *, void *))0x222de0)((void *)0x5ab220, (void *)0x5ab210)) {
      display_assert((const char *)0x26649c, (const char *)0x266458, 0x5c, 1);
      system_exit(-1);
    }
  }
  (*(int *)0x335094)++;
}

