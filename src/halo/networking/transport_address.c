/* --- transport_address.obj batch drafts (2026-07-26) --- */

/* 0x81a90 */
void transport_address_equivalent(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x00266090, (char *)0x00265ffc, 59, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x81add */
  display_assert((char *)0x0026608c, (char *)0x00265ffc, 60, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x81b03 */
  display_assert((char *)0x00265fe4, (char *)0x00265ffc, 61, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x10], 4 -> je 0x81b27 */
  display_assert((char *)0x00266060, (char *)0x00265ffc, 63, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi + 0x10], 4 -> je 0x81b4b */
  display_assert((char *)0x00266034, (char *)0x00265ffc, 64, 0);
  system_exit(0);
  csmemcmp((void *)(uintptr_t)esi, (void *)(uintptr_t)edi, 0);
  /* test eax, eax -> jne 0x81b80 */
  /* relift: cmp (int16_t)eax, word ptr [edi + 0x12] -> jne 0x81b80 */

  (void)eax;
  (void)esi;
  (void)edi;
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

/* 0x81e00 */
void FUN_00081e00(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* mem[0x005ab210] = ecx */
  /* mem[0x005ab214] = edx */
  /* mem[0x005ab218] = ecx */
  /* mem[0x005ab21c] = edx */
  /* mem[0x005ab220] = ecx */
  /* mem[0x005ab224] = edx */
  /* relift: FUN_00222de0(0x005ab220, 0x005ab210); */
  /* test eax, eax -> je 0x81e76 */
  display_assert((char *)0x0026649c, (char *)0x00266458, 92, 0);
  system_exit(0);
  /* test eax, eax -> jg 0x81ea6 */
  display_assert((char *)0x002664a8, (char *)0x00266458, 102, 0);
  system_exit(0);
  FUN_00222df7((void *)0x005ab220);
  /* test esi, esi -> jne 0x81eeb */
  display_assert((char *)0x002664e0, (char *)0x00266458, 151, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0xc], 8 -> je 0x81f11 */
  display_assert((char *)0x002664c0, (char *)0x00266458, 152, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)esi, (void *)0x005ab228, 0);
  display_assert((char *)0x002664ec, (char *)0x00266458, 163, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x81f83 */
  display_assert((char *)0x002664e0, (char *)0x00266458, 164, 0);
  system_exit(0);
  csmemcmp((void *)(uintptr_t)esi, (void *)(uintptr_t)edi, 0);
  /* test esi, esi -> jne 0x81fcb */
  display_assert((char *)0x002664ec, (char *)0x00266458, 175, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0xc], 8 -> je 0x81ff1 */
  display_assert((char *)0x002664c0, (char *)0x00266458, 176, 0);
  system_exit(0);
  transport_nonce_is_equal();
  /* test (char)eax, (char)eax -> je 0x82058 */
  /* test eax, eax -> jg 0x8203f */
  display_assert((char *)0x002664a8, (char *)0x00266458, 102, 0);
  system_exit(0);
  FUN_00222df7((void *)0x005ab220);
  /* test eax, eax -> jg 0x820b9 */
  display_assert((char *)0x002664a8, (char *)0x00266458, 224, 0);
  system_exit(0);
  /* test eax, eax -> jg 0x820fc */
  display_assert((char *)0x002664a8, (char *)0x00266458, 231, 0);
  system_exit(0);
  XNetGetEthernetLinkStatus();
  error(0, (char *)0x00266534);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
