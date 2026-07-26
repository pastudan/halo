/* kb object stubs -> libcmt/wcsncpy.c */

extern void RtlUnwind(void *a, void *b, void *c, void *d);

/* --- LIBCMT:wcsncpy.obj batch drafts (2026-07-26) --- */

/* 0x1dbc1e */

/* --- forward decls (auto) --- */
void FUN_001dbc1e(void);
void FUN_001dbc26(void);
void __global_unwind2(void);
void __local_unwind2(void);
void FUN_001dbdca(void);
void __seh_longjmp_unwind(void);
void _memchr(void);
int _wcscmp(const wchar_t *s1, const wchar_t *s2);
int FUN_001dbfa7(const wchar_t *s1, const wchar_t *s2);
size_t _wcscspn(const wchar_t *s, const wchar_t *reject);
wchar_t *_wcsncat(wchar_t *dest, const wchar_t *src, size_t count);
int _wcsncmp(const wchar_t *s1, const wchar_t *s2, size_t count);
wchar_t *_wcsncpy(wchar_t *dest, const wchar_t *src, size_t count);
wchar_t *_wcspbrk(const wchar_t *s, const wchar_t *accept);
wchar_t *_wcsrchr(const wchar_t *s, wchar_t c);
size_t _wcsspn(const wchar_t *s, const wchar_t *accept);
wchar_t *_wcsstr(const wchar_t *haystack, const wchar_t *needle);
wchar_t *_wcstok(wchar_t *s, const wchar_t *delim);
size_t FUN_001dc257(wchar_t *dest, const wchar_t *src, size_t count);
wchar_t *FUN_001dc27c(wchar_t *s, size_t count);
int __wcsicmp(const wchar_t *s1, const wchar_t *s2);
int __wcsnicmp(const wchar_t *s1, const wchar_t *s2, size_t count);
int FUN_001dc3e9(int c, int mask);
void __getwc_lk(void);
int _fgetwc(void *stream);
void FUN_001dc54a(void);
void FUN_001dc559(void);

void FUN_001dbc1e(void)
{
  __unlock_file();
}

/* 0x1dbc26 */
void FUN_001dbc26(void)
{
  int eax = 0;
  int ebx = 0;

  __ctrlfp();
  __sptype();
  /* cmp eax, 2 -> jle 0x1dbc81 */
  /* cmp eax, 3 -> jne 0x1dbc8f */
  __handle_qnan1();
  __ctrlfp();
  FUN_001dfd23();
  __ctrlfp();
  /* test (char)ebx, 0x20 -> jne 0x1dbcc0 */
  FUN_001dfbd2();

  (void)eax;
  (void)ebx;
}

/* 0x1dbcf4 */
void __global_unwind2(void)
{
  RtlUnwind(0, (void *)(uintptr_t)0x001dbd0c, 0, 0);
}

/* 0x1dbd36 */
void __local_unwind2(void)
{
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* cmp esi, -1 -> je 0x1dbd90 */
  /* relift: cmp esi, dword ptr [esp + 0x24] -> je 0x1dbd90 */
  /* relift: cmp dword ptr [ebx + esi*4 + 4], 0 -> jne 0x1dbd8e */
  FUN_001dbdca();
  /* relift: cmp dword ptr [ecx + 4], 0x1dbd14 -> jne 0x1dbdc0 */
  /* relift: cmp dword ptr [ecx + 8], edx -> jne 0x1dbdc0 */

  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1dbdca */
void FUN_001dbdca(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: test dword ptr [eax + 4], 6 -> jne 0x1dbe8c */
  /* cmp esi, -1 -> je 0x1dbe85 */
  /* relift: cmp dword ptr [edi + ecx*4 + 4], 0 -> je 0x1dbe73 */
  __global_unwind2();
  __local_unwind2();
  /* relift: tail-call FUN_001dbdca(); */
  __local_unwind2();

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x1dbea9 */
void __seh_longjmp_unwind(void)
{

}

/* 0x1dbed0 */
void _memchr(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1dbf75 */
int _wcscmp(const wchar_t *s1, const wchar_t *s2)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x1dbfa7 */
int FUN_001dbfa7(const wchar_t *s1, const wchar_t *s2)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x1dbfac */
size_t _wcscspn(const wchar_t *s, const wchar_t *reject)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x1dbfef */
wchar_t *_wcsncat(wchar_t *dest, const wchar_t *src, size_t count)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return NULL;
}

/* 0x1dc02c */
int _wcsncmp(const wchar_t *s1, const wchar_t *s2, size_t count)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x1dc061 */
wchar_t *_wcsncpy(wchar_t *dest, const wchar_t *src, size_t count)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return NULL;
}

/* 0x1dc09e */
wchar_t *_wcspbrk(const wchar_t *s, const wchar_t *accept)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return NULL;
}

/* 0x1dc0de */
wchar_t *_wcsrchr(const wchar_t *s, wchar_t c)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return NULL;
}

/* 0x1dc10e */
size_t _wcsspn(const wchar_t *s, const wchar_t *accept)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x1dc154 */
wchar_t *_wcsstr(const wchar_t *haystack, const wchar_t *needle)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return NULL;
}

/* 0x1dc1b2 */
wchar_t *_wcstok(wchar_t *s, const wchar_t *delim)
{
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  FUN_001dff91();
  /* cmp (int16_t)edx, (int16_t)ebx -> je 0x1dc203 */
  /* cmp (int16_t)edi, (int16_t)edx -> je 0x1dc1f4 */
  /* cmp (int16_t)edi, (int16_t)ebx -> jne 0x1dc1e5 */
  /* relift: cmp word ptr [esi], (int16_t)ebx -> je 0x1dc203 */
  /* cmp (int16_t)edx, (int16_t)ebx -> jne 0x1dc1db */
  /* cmp (int16_t)edx, (int16_t)edi -> je 0x1dc22d */
  /* cmp (int16_t)edx, (int16_t)ebx -> jne 0x1dc21e */
  /* relift: cmp word ptr [esi], (int16_t)ebx -> jne 0x1dc23b */
  /* relift: cmp word ptr [ecx], (int16_t)ebx -> jne 0x1dc211 */
  return NULL;

  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1dc257 */
size_t FUN_001dc257(wchar_t *dest, const wchar_t *src, size_t count)
{
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 8], 0 -> je 0x1dc271 */
  _wcsncpy((wchar_t *)0, (wchar_t *)(uintptr_t)src, count);
  _wcslen((wchar_t *)(uintptr_t)src);
  return 0;

  (void)ebp;
}

/* 0x1dc27c */
wchar_t *FUN_001dc27c(wchar_t *s, size_t count)
{
  int esi = 0;

  /* cmp (int16_t)esi, (int16_t)eax -> je 0x1dc2c1 */
  /* relift: cmp dword ptr [0x4fc25c], 0 -> jne 0x1dc2ad */
  /* cmp (int16_t)esi, 0x61 -> jb 0x1dc2a8 */
  /* cmp (int16_t)esi, 0x7a -> ja 0x1dc2a8 */
  /* cmp (int16_t)esi, 0x100 -> jae 0x1dc2be */
  FUN_001dc3e9(0, 0);
  return NULL;

  (void)esi;
}

/* 0x1dc2c3 */
int __wcsicmp(const wchar_t *s1, const wchar_t *s2)
{
  int eax = 0;
  int ebx = 0;
  int edi = 0;

  /* cmp (int16_t)ebx, 0x41 -> jb 0x1dc2e9 */
  /* cmp (int16_t)ebx, 0x5a -> ja 0x1dc2e9 */
  /* cmp (int16_t)eax, 0x41 -> jb 0x1dc2fd */
  /* cmp (int16_t)eax, 0x5a -> ja 0x1dc2fd */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x1dc341 */
  /* cmp (int16_t)ebx, (int16_t)eax -> je 0x1dc2d5 */
  FUN_001da8e3((wchar_t *)(uintptr_t)eax, edi);
  FUN_001da8e3((wchar_t *)(uintptr_t)eax, 0);
  /* cmp (int16_t)ebx, (int16_t)eax -> je 0x1dc317 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)edi;
}

/* 0x1dc34b */
int __wcsnicmp(const wchar_t *s1, const wchar_t *s2, size_t count)
{
  int eax = 0;
  int ebx = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 0x10], eax -> je 0x1dc3e7 */
  /* cmp (int16_t)eax, 0x41 -> jb 0x1dc37c */
  /* cmp (int16_t)eax, 0x41 -> jb 0x1dc392 */
  /* cmp (int16_t)eax, 0x5a -> ja 0x1dc392 */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x1dc3de */
  /* cmp (int16_t)ebx, (int16_t)eax -> je 0x1dc368 */
  FUN_001da8e3((wchar_t *)(uintptr_t)eax, edi);
  FUN_001da8e3((wchar_t *)(uintptr_t)eax, 0);
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x1dc3dc */
  /* cmp (int16_t)ebx, (int16_t)eax -> je 0x1dc3af */
  return 0;

  (void)eax;
  (void)ebx;
  (void)edi;
  (void)ebp;
}

/* 0x1dc3e9 */
int FUN_001dc3e9(int c, int mask)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x1dc41e */
void __getwc_lk(void)
{
  int eax = 0;
  int ecx = 0;

  /* cmp eax, -1 -> je 0x1dc450 */
  /* relift: test byte ptr [eax + 4], 0x80 -> je 0x1dc4f5 */
  __filbuf();
  /* cmp eax, -1 -> jne 0x1dc486 */
  /* relift: test byte ptr [ecx + eax*2 + 1], 0x80 -> je 0x1dc4cc */
  __filbuf();
  /* cmp eax, -1 -> jne 0x1dc4c6 */
  _ungetc();
  FUN_001e2669();
  /* cmp eax, -1 -> jne 0x1dc4ef */
  FUN_001db777();
  __filwbuf();

  (void)eax;
  (void)ecx;
}

/* 0x1dc512 */
int _fgetwc(void *stream)
{
  FUN_001dd5c8();
  __lock_file();
  __getwc_lk();
  FUN_001dc54a();
  __SEH_epilog();
  return 0;
}

/* 0x1dc54a */
void FUN_001dc54a(void)
{
  __unlock_file();
}

/* 0x1dc559 */
void FUN_001dc559(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp eax, -1 -> je 0x1dc58d */
  /* relift: test byte ptr [eax + 4], 0x80 -> je 0x1dc5f9 */
  FUN_001e2879();
  FUN_001db777();
  /* test ebx, ebx -> jle 0x1dc5f3 */
  __flsbuf();
  /* cmp eax, -1 -> je 0x1dc5b8 */
  /* cmp edi, ebx -> jl 0x1dc5c4 */
  __flswbuf();
  FUN_001dd5c8();
  __lock_file();
  /* relift: tail-call FUN_001dc559(); */
  FUN_001dc65c();
  __SEH_epilog();
  __unlock_file();
  /* test (char)eax, 1 -> jne 0x1dc68f */
  /* test (char)eax, 2 -> jne 0x1dc6eb */
  /* relift: cmp dword ptr [esi + 8], edi -> jne 0x1dc69d */
  __getbuf();
  /* cmp eax, -1 -> je 0x1dc6c4 */
  /* relift: test byte ptr [eax + 4], 0x80 -> je 0x1dc722 */
  FUN_001e2879();
  FUN_001db777();
  /* relift: cmp dword ptr [esi], ecx -> jae 0x1dc709 */
  /* relift: cmp dword ptr [esi + 4], edi -> jne 0x1dc6eb */
  /* relift: cmp eax, dword ptr [esi + 0x18] -> jg 0x1dc6eb */
  /* cmp ecx, edi -> jl 0x1dc71d */
  /* relift: cmp dword ptr [esi], eax -> jae 0x1dc739 */
  /* relift: cmp dword ptr [esi + 4], edi -> jne 0x1dc6eb */
  /* relift: cmp dword ptr [esi + 0x18], 2 -> jb 0x1dc6eb */
  /* relift: cmp word ptr [eax], (int16_t)ebx -> je 0x1dc751 */
  FUN_001dd5c8();
  __lock_file();
  FUN_001dc66b();
  FUN_001dc7a2();
  __SEH_epilog();
  __unlock_file();
  FUN_001dd5c8();
  /* relift: cmp dword ptr [ebp + 0xc], ebx -> jg 0x1dc7cb */
  __lock_file();
  __getwc_lk();
  /* cmp eax, 0xffff -> jne 0x1dc7ff */
  /* cmp esi, edi -> jne 0x1dc80d */
  /* cmp (int16_t)eax, 0xa -> jne 0x1dc7db */
  FUN_001dc822();
  __SEH_epilog();
  __unlock_file();
  FUN_001dd5c8();
  _wcslen((wchar_t *)0);
  __lock_file();
  /* test eax, eax -> je 0x1dc87e */
  /* relift: tail-call FUN_001dc559(); */
  /* cmp (int16_t)eax, 0xffff -> jne 0x1dc855 */
  FUN_001dc890();
  __SEH_epilog();
  __unlock_file();
  FUN_001dd5c8();
  __lock_file2();
  __getwc_lk();
  /* cmp eax, 0xa -> je 0x1dc8ee */
  /* cmp eax, 0xffff -> jne 0x1dc8e4 */
  /* cmp edi, ebx -> jne 0x1dc8ee */
  FUN_001dc909();
  __SEH_epilog();
  __unlock_file2();
  FUN_001dd5c8();
  __lock_file2();
  __stbuf();
  /* test (int16_t)eax, (int16_t)eax -> je 0x1dc964 */
  /* relift: tail-call FUN_001dc559(); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
/* --- LIBCMT:wcsncpy.obj orphan shells (2026-07-26) --- */

/* orphan 0x1dbea9 */
void FUN_001dbea9(void)
{
  __local_unwind2();
}
