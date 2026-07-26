/* kb object stubs -> libcmt/fgets.c */

/* --- LIBCMT:fgets.obj batch drafts (2026-07-26) --- */

/* 0x1daed5 */
void FUN_001daed5(void)
{
  FUN_001dad15();
}

/* 0x1daeec */
char *crt_fgets(char *buffer, int max_count, void *stream)
{
  int eax = 0;
  int ebx = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001dd5c8();
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> jg 0x1daf0a */
  __lock_file();
  __filbuf();
  /* cmp eax, -1 -> jne 0x1daf48 */
  /* cmp edi, ebx -> jne 0x1daf52 */
  /* cmp (char)eax, 0xa -> jne 0x1daf1b */
  FUN_001daf6a();
  __SEH_epilog();
  return NULL;

  (void)eax;
  (void)ebx;
  (void)edi;
  (void)ebp;
}

/* 0x1daf6a */
void FUN_001daf6a(void)
{
  __unlock_file();
}

/* 0x1daf7e */
void FUN_001daf7e(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1daf96 */
double atof(const char *str)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001e153d();
  /* test eax, eax -> je 0x1dafcc */
  /* test (char)ecx, (char)ecx -> jne 0x1dafd1 */
  FUN_001e1e20();
  FUN_001e1ea5();
  /* cmp ecx, 0x2b -> jne 0x1db01c */
  /* cmp ecx, 0x30 -> jl 0x1db02d */
  /* cmp ecx, 0x39 -> jg 0x1db02d */
  /* cmp ecx, -1 -> je 0x1db041 */
  FUN_001e1ea5();
  /* cmp esi, 0x2b -> jne 0x1db07c */
  /* cmp esi, 0x30 -> jl 0x1db08f */
  /* cmp esi, 0x39 -> jg 0x1db08f */
  /* cmp esi, -1 -> je 0x1db0b7 */
  __allmul();
  FUN_001de452();
  __flsbuf();
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0x1db122 */
  /* cmp (int16_t)ecx, (int16_t)edx -> je 0x1db155 */
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0x1db13f */
  /* cmp (int16_t)ecx, (int16_t)edx -> je 0x1db155 */
  /* relift: cmp word ptr [edx], 0 -> jne 0x1db162 */
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0x1db16f */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x1db188 */
  /* relift: test word ptr [ebx + 0xc], 0x10c -> je 0x1db1d8 */
  /* test eax, eax -> je 0x1db220 */
  /* cmp esi, eax -> jae 0x1db1fc */
  /* relift: cmp esi, dword ptr [ebp - 8] -> jb 0x1db26c */
  /* test ecx, ecx -> je 0x1db234 */
  __flush();
  /* relift: cmp dword ptr [ebp - 8], 0 -> je 0x1db243 */
  __write();
  /* cmp eax, -1 -> je 0x1db261 */
  /* cmp eax, esi -> jae 0x1db295 */
  __flsbuf();
  /* test esi, esi -> jne 0x1db1e1 */
  FUN_001dd5c8();
  __lock_file();
  FUN_001db19c();
  FUN_001db2f5();
  __SEH_epilog();
  __unlock_file();
  /* relift: test word ptr [ebx + 0xc], 0x10c -> je 0x1db33b */
  /* relift: test word ptr [ebx + 0xc], 0x10c -> je 0x1db37f */
  /* test eax, eax -> je 0x1db37f */
  /* cmp edi, eax -> jae 0x1db357 */
  /* relift: cmp edi, dword ptr [ebp - 8] -> jb 0x1db3b4 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
