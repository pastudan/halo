/* kb object stubs -> libcmt/vsnwprint.c */

/* --- LIBCMT:vsnwprint.obj batch drafts (2026-07-26) --- */

/* 0x1dc61e */
int _fputwc(int c, void *stream)
{
  FUN_001dd5c8();
  __lock_file();
  FUN_001dc559();
  FUN_001dc65c();
  __SEH_epilog();
  return 0;
}

/* 0x1dc65c */
void FUN_001dc65c(void)
{
  __unlock_file();
}

/* 0x1dc66b */
void FUN_001dc66b(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x1dc766 */
int _ungetwc(int c, void *stream)
{
  FUN_001dd5c8();
  __lock_file();
  FUN_001dc66b();
  FUN_001dc7a2();
  __SEH_epilog();
  return 0;
}

/* 0x1dc7a2 */
void FUN_001dc7a2(void)
{
  __unlock_file();
}

/* 0x1dc7ac */
wchar_t *_fgetws(wchar_t *buffer, int count, void *stream)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001dd5c8();
  /* relift: cmp dword ptr [ebp + 0xc], ebx -> jg 0x1dc7cb */
  __lock_file();
  __getwc_lk();
  /* cmp eax, 0xffff -> jne 0x1dc7ff */
  /* cmp esi, edi -> jne 0x1dc80d */
  /* cmp (int16_t)eax, 0xa -> jne 0x1dc7db */
  FUN_001dc822();
  __SEH_epilog();
  return NULL;

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1dc822 */
void FUN_001dc822(void)
{
  __unlock_file();
}

/* 0x1dc82c */
int _fputws(const wchar_t *s, void *stream)
{
  int eax = 0;

  FUN_001dd5c8();
  _wcslen((wchar_t *)0);
  __lock_file();
  /* test eax, eax -> je 0x1dc87e */
  FUN_001dc559();
  /* cmp (int16_t)eax, 0xffff -> jne 0x1dc855 */
  FUN_001dc890();
  __SEH_epilog();
  return 0;

  (void)eax;
}

/* 0x1dc890 */
void FUN_001dc890(void)
{
  __unlock_file();
}

/* 0x1dc89a */
wchar_t *__getws(wchar_t *buffer)
{
  int eax = 0;
  int ebx = 0;
  int edi = 0;

  FUN_001dd5c8();
  __lock_file2();
  __getwc_lk();
  /* cmp eax, 0xa -> je 0x1dc8ee */
  /* cmp eax, 0xffff -> jne 0x1dc8e4 */
  /* cmp edi, ebx -> jne 0x1dc8ee */
  FUN_001dc909();
  __SEH_epilog();
  return NULL;

  (void)eax;
  (void)ebx;
  (void)edi;
}

/* 0x1dc909 */
void FUN_001dc909(void)
{
  __unlock_file2();
}

/* 0x1dc914 */
int __putws(const wchar_t *s)
{
  int edi = 0;

  FUN_001dd5c8();
  __lock_file2();
  __stbuf();
  /* test (int16_t)eax, (int16_t)eax -> je 0x1dc964 */
  FUN_001dc559();
  /* cmp (int16_t)eax, (int16_t)edi -> jne 0x1dc945 */
  FUN_001dc559();
  /* cmp (int16_t)eax, (int16_t)edi -> je 0x1dc976 */
  __ftbuf();
  FUN_001dc998();
  __SEH_epilog();
  return 0;

  (void)edi;
}

/* 0x1dc998 */
void FUN_001dc998(void)
{
  __unlock_file2();
}

/* 0x1dc9a3 */
int _vfwprintf(void *stream, const wchar_t *format, char *args)
{
  FUN_001dd5c8();
  __lock_file();
  __stbuf();
  FUN_001e2984();
  __ftbuf();
  FUN_001dc9f6();
  __SEH_epilog();
  return 0;
}

/* 0x1dc9f6 */
void FUN_001dc9f6(void)
{
  __unlock_file();
}

/* 0x1dca00 */
int _vprintf(const wchar_t *format, char *args)
{
  FUN_001dd5c8();
  __lock_file();
  __stbuf();
  FUN_001e2984();
  __ftbuf();
  FUN_001dca55();
  __SEH_epilog();
  return 0;
}

/* 0x1dca55 */
void FUN_001dca55(void)
{
  __unlock_file();
}

/* 0x1dca5f */
int _vsnwprintf(wchar_t *buffer, size_t count, const wchar_t *format, char *argptr)
{
  FUN_001e2984();
  __flsbuf();
  __flsbuf();
  return 0;
}

/* 0x1dcace */
int FUN_001dcace(wchar_t *buffer, const wchar_t *format, char *args)
{
  FUN_001e2984();
  __flsbuf();
  __flsbuf();
  return 0;
}

/* 0x1dcb3c */
void FUN_001dcb3c(void)
{
  FUN_001e2984();
}

/* 0x1dcb6c */
void *FUN_001dcb6c(int fd, const wchar_t *mode)
{
  (void)fd;
  __unlock_file();
 (void)mode;
  return NULL;
}

/* 0x1dcc91 */
void FUN_001dcc91(void)
{
  __unlock_file();
}

/* 0x1dcc99 */
void __wfsopen(void)
{
  int eax = 0;

  FUN_001dd5c8();
  __getstream();
  /* test eax, eax -> jne 0x1dccc0 */
  FUN_001db777();
  __wopenfile();
  FUN_001dcceb();
  __SEH_epilog();

  (void)eax;
}

/* 0x1dcceb */
void FUN_001dcceb(void)
{
  __unlock_file();
}

/* 0x1dccf5 */
void *FUN_001dccf5(const wchar_t *path, const wchar_t *mode)
{
  __wfsopen();
  return NULL;
}

/* 0x1dcd08 */
void *__wfreopen(const wchar_t *path, const wchar_t *mode, void *stream)
{
  int esi = 0;

  FUN_001dd5c8();
  __lock_file();
  /* relift: test byte ptr [esi + 0xc], 0x83 -> je 0x1dcd33 */
  __fclose_lk();
  __wopenfile();
  FUN_001dcd64();
  __SEH_epilog();
  return NULL;

  (void)esi;
}

/* 0x1dcd64 */
void FUN_001dcd64(void)
{
  __unlock_file();
}

/* 0x1dcd6e */
void FUN_001dcd6e(const wchar_t *prefix)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  FUN_001dd5c8();
  /* cmp ebx, edi -> je 0x1dcdc4 */
  /* relift: cmp word ptr [ebx], (int16_t)edi -> je 0x1dcdc4 */
  _wcslen((wchar_t *)(uintptr_t)ebx);
  _malloc();
  /* test edi, edi -> je 0x1dcdbb */
  FUN_001e35d8();
  /* test eax, eax -> ja 0x1dcdc1 */
  FUN_001dde24();
  __SEH_epilog();
  FUN_001e334f();
  /* test edi, edi -> je 0x1dcdf8 */
  /* test (char)ecx, (char)ecx -> jne 0x1dcdd8 */
  FUN_001df28e();
  FUN_001df28e();
  FUN_001dde24();
  FUN_001db777();
  /* relift: cmp dword ptr [eax], 0 -> jl 0x1dce21 */
  FUN_001db777();
  /* relift: cmp eax, dword ptr [0x331930] -> jge 0x1dce21 */
  FUN_001db777();
  /* test dl, dl -> jne 0x1dce35 */
  FUN_001df28e();
  FUN_001df28e();
  FUN_001dce64();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x1dce64 */
void FUN_001dce64(void)
{
  __unlock_fhandle();
}

/* 0x1dce6e */
int FUN_001dce6e(const wchar_t *path)
{
  int eax = 0;

  FUN_001e3776();
  xapi_GetLastError();
  /* test eax, eax -> je 0x1dce94 */
  __dosmaperr();
  return 0;

  (void)eax;
}

/* 0x1dce9c */
void _winit_namebuf(void)
{
  int ecx = 0;

  _wcscpy();
  /* cmp (int16_t)ecx, 0x5c -> je 0x1dced5 */
  /* cmp (int16_t)ecx, 0x2f -> je 0x1dced5 */
  /* relift: cmp dword ptr [esp + 8], 0 -> je 0x1dcee3 */
  FUN_001cfde0();
  FUN_001e3805();
  _wcscat();

  (void)ecx;
}

/* 0x1dcf08 */
void FUN_001dcf08(void)
{
  int eax = 0;
  int esi = 0;

  _wcsrchr((wchar_t *)0, 46);
  FUN_001dd1e8((wchar_t *)(uintptr_t)esi, (wchar_t *)0, 0);
  /* cmp eax, 0x7fff -> jb 0x1dcf36 */
  FUN_001e3805();
  _wcscpy();

  (void)eax;
  (void)esi;
}

/* 0x1dcf51 */
wchar_t *FUN_001dcf51(wchar_t *buffer)
{
  int eax = 0;
  int ebx = 0;
  int edi = 0;

  FUN_001dd5c8();
  FUN_001defd9();
  /* test eax, eax -> je 0x1dcffd */
  FUN_001df055();
  /* relift: cmp word ptr [0x4fc01c], (int16_t)ebx -> jne 0x1dcfac */
  _winit_namebuf();
  FUN_001e388c();
  /* test eax, eax -> jne 0x1dcfb3 */
  FUN_001dcf08();
  /* test eax, eax -> je 0x1dcf92 */
  /* cmp edi, ebx -> jne 0x1dcfe5 */
  FUN_001dff91();
  /* relift: cmp dword ptr [edi + 0x30], ebx -> jne 0x1dcfdf */
  _malloc();
  /* cmp eax, ebx -> jne 0x1dcfdf */
  _wcscpy();
  FUN_001dd003();
  __SEH_epilog();
  return NULL;

  (void)eax;
  (void)ebx;
  (void)edi;
}

/* 0x1dd003 */
void FUN_001dd003(void)
{
  FUN_001defb3();
}

/* 0x1dd00c */
void FUN_001dd00c(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int ebp = 0;

  FUN_001dc3e9(0, 0);
  /* cmp (int16_t)esi, 0x2d -> jne 0x1dd046 */
  /* cmp (int16_t)esi, 0x2b -> jne 0x1dd051 */
  /* test eax, eax -> jl 0x1dd1c1 */
  /* cmp eax, 1 -> je 0x1dd1c1 */
  /* cmp eax, 0x24 -> jg 0x1dd1c1 */
  __wchartodigit();
  /* cmp (int16_t)eax, 0x78 -> je 0x1dd0a1 */
  /* cmp (int16_t)eax, 0x58 -> je 0x1dd0a1 */
  /* relift: cmp dword ptr [ebp + 0x10], ebx -> jne 0x1dd0cc */
  __wchartodigit();
  /* cmp (int16_t)eax, 0x78 -> je 0x1dd0c3 */
  /* cmp (int16_t)eax, 0x58 -> jne 0x1dd0cc */
  __wchartodigit();
  /* cmp (int16_t)esi, 0x41 -> jb 0x1dd0f1 */
  /* cmp (int16_t)esi, 0x5a -> jbe 0x1dd0fd */
  /* cmp (int16_t)esi, 0x61 -> jb 0x1dd145 */
  /* cmp (int16_t)esi, 0x7a -> ja 0x1dd145 */
  /* cmp (int16_t)esi, 0x61 -> jb 0x1dd111 */
  /* cmp (int16_t)esi, 0x7a -> ja 0x1dd111 */
  /* relift: cmp eax, dword ptr [ebp + 0x10] -> jae 0x1dd145 */
  /* relift: cmp dword ptr [ebp - 4], ebx -> jb 0x1dd132 */
  /* relift: cmp eax, dword ptr [ebp - 8] -> jbe 0x1dd132 */
  /* test (char)ebx, 8 -> jne 0x1dd15e */
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> je 0x1dd158 */
  /* test (char)ebx, 1 -> jne 0x1dd1ab */
  /* relift: cmp dword ptr [ebp - 4], 0x80000000 -> ja 0x1dd186 */
  /* test eax, eax -> jne 0x1dd1ab */
  /* relift: cmp dword ptr [ebp - 4], esi -> jbe 0x1dd1ab */
  FUN_001db777();
  /* test eax, eax -> je 0x1dd1b4 */
  /* test (char)ebx, 2 -> je 0x1dd1bc */
  /* test eax, eax -> je 0x1dd1ca */
  /* relift: tail-call FUN_001dd00c(); */
  /* relift: tail-call FUN_001dd00c(); */
  FUN_001dd5c8();
  FUN_001dc3e9(0, 0);
  /* test eax, eax -> je 0x1dd244 */
  FUN_001dc3e9(0, 0);
  /* test eax, eax -> jne 0x1dd22c */
  _wcslen((wchar_t *)(uintptr_t)ebx);
  FUN_001d90e0();
  _wcslen((wchar_t *)(uintptr_t)ebx);
  _malloc();
  /* test eax, eax -> jne 0x1dd2ab */
  FUN_001db777();
  /* relift: relift: fld qword ptr [0x2602c0] */
  /* relift: cmp word ptr [ebx], 0 -> je 0x1dd2ea */
  FUN_001e2879();
  /* test eax, eax -> jle 0x1dd2ea */
  /* relift: cmp word ptr [esi], 0 -> jne 0x1dd2c9 */
  FUN_001e1e20();
  /* relift: cmp dword ptr [ebp - 0x20], 0 -> je 0x1dd315 */
  FUN_001dde24();
  /* test eax, eax -> je 0x1dd324 */
  /* test (int16_t)ecx, 0x240 -> je 0x1dd33a */
  /* test eax, eax -> je 0x1dd36c */
  /* test (char)ecx, 0x81 -> je 0x1dd34f */
  /* relift: relift: fld qword ptr [0x331934] */
  /* relift: cmp word ptr [ebx], 0x2d -> jne 0x1dd356 */
  /* test (char)ecx, 1 -> je 0x1dd369 */
  FUN_001db777();
  __SEH_epilog();
  FUN_001dc3e9(0, 0);
  /* cmp eax, 0x2b -> jne 0x1dd3ab */
  __wchartodigit();
  FUN_001dc3e9(0, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)ebp;
}
