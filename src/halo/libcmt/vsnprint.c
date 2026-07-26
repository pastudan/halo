/* kb object stubs -> libcmt/vsnprint.c */

/* --- LIBCMT:vsnprint.obj batch drafts (2026-07-26) --- */

/* 0x1daff2 */
void _atol(void)
{
  int ecx = 0;

  FUN_001e1ea5();
  /* cmp ecx, 0x2b -> jne 0x1db01c */
  /* cmp ecx, 0x30 -> jl 0x1db02d */
  /* cmp ecx, 0x39 -> jg 0x1db02d */
  /* cmp ecx, -1 -> je 0x1db041 */

  (void)ecx;
}

/* 0x1db04a */
long atol(const char *str)
{
  int ecx = 0;

  FUN_001e1ea5();
  /* cmp ecx, 0x2b -> jne 0x1db01c */
  /* cmp ecx, 0x30 -> jl 0x1db02d */
  /* cmp ecx, 0x39 -> jg 0x1db02d */
  /* cmp ecx, -1 -> je 0x1db041 */
  FUN_001e1ea5();
  return 0;

  (void)ecx;
}

/* 0x1db0c8 */
int crt_vsnprintf(char *buffer, size_t count, const char *format, char *arglist)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

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
  __read();
  /* test eax, eax -> je 0x1db3e2 */
  /* cmp eax, -1 -> je 0x1db3f1 */
  __filbuf();
  /* test edi, edi -> jne 0x1db342 */
  FUN_001dd5c8();
  __lock_file();
  FUN_001db2ff();
  FUN_001db439();
  __SEH_epilog();
  __unlock_file();
  FUN_001dd5c8();
  __lock_file2();
  __stbuf();
  FUN_001de452();
  __ftbuf();
  FUN_001db49e();
  __SEH_epilog();
  __unlock_file2();
  DeleteFileA((char *)0);
  /* test eax, eax -> jne 0x1db4bd */
  xapi_GetLastError();
  /* test eax, eax -> je 0x1db4ce */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
