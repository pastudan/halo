/* kb object stubs -> libcmt/sprintf.c */

/* --- LIBCMT:sprintf.obj batch drafts (2026-07-26) --- */

/* 0x1d8ebe */
void DbgPrint(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d8f06 */
void XcRC4Crypt(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d8f0c */
void XcRC4Key(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d8f18 */
void XcBlockCryptCBC(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d8f1e */
void XcKeyTable(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d8f24 */
void XcDESKeyParity(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d8f2a */
void XcHMAC(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d8f30 */
void XcModExp(void)
{
  /* relift: FUN_001d8b2e(0, 0); */
  /* relift: FUN_001d8b49(0, 0); */
}

/* 0x1d8ff0 */
void FUN_001d8ff0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d9010 */
void FUN_001d9010(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d9011 */
void FUN_001d9011(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d9059 */
void FUN_001d9059(void)
{
  FUN_001d9011();
  FUN_001de27a();
}

/* 0x1d9068 */
void FUN_001d9068(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d90e0 */
void FUN_001d90e0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d90f0 */
int crt_sprintf(char *buffer, const char *format, ...)
{
  FUN_001de452();
  __flsbuf();
  return 0;
}

/* 0x1d9148 */
void FUN_001d9148(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001de452();
  FUN_001de452();
  __flsbuf();
  /* test esi, esi -> je 0x1d91ee */
  /* cmp edi, ecx -> jbe 0x1d925a */
  /* test eax, eax -> jle 0x1d921f */
  /* cmp esi, edi -> jbe 0x1d9210 */
  /* test ebp, ebp -> je 0x1d9252 */
  /* cmp edi, ecx -> ja 0x1d9202 */
  /* cmp eax, 2 -> jb 0x1d94dc */
  /* cmp eax, 8 -> ja 0x1d92ef */
  _shortsort();
  /* test eax, eax -> jle 0x1d932a */
  /* test eax, eax -> jle 0x1d935c */
  /* test eax, eax -> jle 0x1d938a */
  /* cmp edi, ebx -> jbe 0x1d93b0 */
  /* cmp ebx, edi -> jae 0x1d93b0 */
  /* test eax, eax -> jle 0x1d9394 */
  /* cmp edi, ebx -> ja 0x1d93d0 */
  /* cmp ebx, eax -> ja 0x1d93d0 */
  /* test eax, eax -> jle 0x1d93b0 */
  /* cmp esi, edi -> jbe 0x1d93e6 */
  /* test eax, eax -> jg 0x1d93d0 */
  /* cmp ebx, esi -> ja 0x1d942c */
  /* cmp edi, esi -> jne 0x1d9390 */
  /* cmp edi, esi -> jae 0x1d9450 */
  /* cmp esi, edi -> jbe 0x1d9450 */
  /* test eax, eax -> je 0x1d9432 */
  /* cmp edi, esi -> jb 0x1d946a */
  /* cmp esi, eax -> jbe 0x1d946e */
  /* test eax, eax -> je 0x1d9450 */
  /* cmp edi, ecx -> jl 0x1d94ab */
  /* cmp eax, esi -> jae 0x1d9496 */
  /* cmp ebx, edx -> jae 0x1d92c7 */
  /* cmp ebx, edx -> jae 0x1d94c3 */
  /* cmp eax, esi -> jae 0x1d92c7 */
  FUN_001dee48();
  FUN_001d950d();
  __fload_withFB();
  /* relift: cmp word ptr [esp], 0x27f -> je 0x1d9521 */
  FUN_001dedd5();
  /* cmp eax, 0x3ff00000 -> jae 0x1d9555 */
  /* relift: cmp dword ptr [0x4fc000], 0 -> jne 0x1dee5e */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
