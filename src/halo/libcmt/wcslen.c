/* kb object stubs -> libcmt/wcslen.c */

/* --- LIBCMT:wcslen.obj batch drafts (2026-07-26) --- */

/* _wcslen (0x1db11e) — readable C lift. */
size_t _wcslen(const wchar_t *str)
{
  const wchar_t *p = str;
  while (*p != 0)
    p++;
  return (size_t)(p - str);
}

/* _wcschr (0x1db134) — readable C lift. */
wchar_t *_wcschr(const wchar_t *s, wchar_t c)
{
  for (;;) {
    if (*s == c)
      return (wchar_t *)s;
    if (*s == 0)
      return 0;
    s++;
  }
}

/* 0x1db156 */
wchar_t *_wcscat(wchar_t *dest, const wchar_t *src)
{
  wchar_t *d = dest;
  if (*d != 0) {
    do {
      d++;
    } while (*d != 0);
  }
  while ((*d++ = *src++) != 0)
    ;
  return dest;
}

/* 0x1db180 */
wchar_t *_wcscpy(wchar_t *dest, const wchar_t *src)
{
  wchar_t *d = dest;
  while ((*d++ = *src++) != 0)
    ;
  return dest;
}

/* 0x1db19c */
void FUN_001db19c(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int ebp = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)ebp;
}

/* 0x1db2b3 */
unsigned int _fread(void *ptr, unsigned int size, unsigned int count, void *stream)
{
  FUN_001dd5c8();
  __lock_file();
  FUN_001db19c();
  FUN_001db2f5();
  __SEH_epilog();
  return 0;
}

/* 0x1db2f5 */
void FUN_001db2f5(void)
{
  __unlock_file();
}

/* 0x1db2ff */
void FUN_001db2ff(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

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
  /* relift: tail-call FUN_001db2ff(); */
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
  __dosmaperr();
  /* relift: FUN_001e2180(0); */
  FUN_001de27a();
  /* test esi, esi -> je 0x1db4ff */
  /* relift: test dword ptr [eax], 0x10008 -> je 0x1db4ff */
  /* test (char)ebx, 1 -> je 0x1db50b */
  /* test (char)ebx, 4 -> je 0x1db513 */
  /* test (char)ebx, 8 -> je 0x1db51b */
  /* test (char)ebx, 0x10 -> je 0x1db523 */
  /* test (char)ebx, 0x20 -> je 0x1db52b */
  /* test (char)ebx, 2 -> je 0x1db535 */
  /* cmp ecx, 0x400 -> je 0x1db56c */
  /* cmp ecx, 0x800 -> je 0x1db568 */
  /* cmp ecx, esi -> jne 0x1db571 */
  /* cmp edx, ebp -> jne 0x1db585 */
  /* test (char)ebx, 0x10 -> je 0x1db59b */
  /* test (char)ebx, 8 -> je 0x1db5a3 */
  /* test (char)ebx, 4 -> je 0x1db5ab */
  /* test (char)ebx, 2 -> je 0x1db5b3 */
  /* test (char)ebx, 1 -> je 0x1db5bb */
  /* test ebx, 0x80000 -> je 0x1db5c6 */
  /* cmp ecx, 0x100 -> je 0x1db5f5 */
  /* cmp ecx, esi -> je 0x1db5ee */
  /* cmp ecx, edx -> jne 0x1db5fa */
  /* cmp ecx, 0x10000 -> jne 0x1db612 */
  /* test (char)ecx, 1 -> je 0x1db62f */
  /* test (char)ecx, 4 -> je 0x1db637 */
  /* test (char)ecx, 8 -> je 0x1db63f */
  /* test (char)ecx, 0x10 -> je 0x1db647 */
  /* test (char)ecx, 0x20 -> je 0x1db64f */
  /* test (char)ecx, 2 -> je 0x1db659 */
  /* relift: FUN_001db621(0); */
  /* relift: FUN_001db621(0); */
  __abstract_cw();
  __hw_cw();
  __control87(0, eax);
  FUN_001dd5c8();
  __lock_file();
  __flsbuf();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
