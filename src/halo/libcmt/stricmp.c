/* kb object stubs -> libcmt/stricmp.c */

/* --- LIBCMT:stricmp.obj batch drafts (2026-07-26) --- */

/* 0x1dd1d1 */
long FUN_001dd1d1(const wchar_t *s, wchar_t **endptr, int base)
{
  FUN_001dd00c();
  return 0;
}

/* 0x1dd1e8 */
unsigned long FUN_001dd1e8(const wchar_t *s, wchar_t **endptr, int base)
{
  FUN_001dd00c();
  return 0;
}

/* 0x1dd1ff */
double FUN_001dd1ff(const wchar_t *s, wchar_t **endptr)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int ebp = 0;

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
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)ebp;
}

/* 0x1dd375 */
void __wtol(void)
{
  int eax = 0;

  FUN_001dc3e9(0, 0);
  /* cmp eax, 0x2b -> jne 0x1dd3ab */
  __wchartodigit();

  (void)eax;
}

/* 0x1dd3d4 */
int FUN_001dd3d4(const wchar_t *s)
{
  int eax = 0;

  FUN_001dc3e9(0, 0);
  /* cmp eax, 0x2b -> jne 0x1dd3ab */
  __wchartodigit();
  return 0;

  (void)eax;
}

/* 0x1dd3d9 */
void __wtoi64(void)
{
  int eax = 0;

  FUN_001dc3e9(0, 0);
  /* cmp eax, 0x2b -> jne 0x1dd413 */
  __allmul();
  __wchartodigit();

  (void)eax;
}

/* 0x1dd467 */
wchar_t *__wctime(const void *timeptr)
{
  int eax = 0;

  crt_localtime((void *)0);
  __wasctime((void *)(uintptr_t)eax);
  return NULL;

  (void)eax;
}

/* 0x1dd480 */
void _store_dt(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1dd49a */
wchar_t *__wasctime(const void *timeptr)
{
  int ecx = 0;
  int esi = 0;

  FUN_001dff91();
  /* relift: cmp dword ptr [esi + 0x40], 0 -> jne 0x1dd4bf */
  _malloc();
  /* cmp ecx, 3 -> jl 0x1dd4d6 */
  _store_dt();
  _store_dt();
  _store_dt();
  _store_dt();
  _store_dt();
  _store_dt();
  return NULL;

  (void)ecx;
  (void)esi;
}

/* 0x1dd576 */
int FUN_001dd576(int param)
{
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  FUN_001dff91();
  /* relift: cmp dword ptr [esi + 0x24], 0 -> jne 0x1dd59b */
  _malloc();
  /* cmp edx, ecx -> jge 0x1dd5b2 */
  /* test (char)ecx, (char)ecx -> jne 0x1dd5bb */
  return 0;

  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1dd5c8 */
void FUN_001dd5c8(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1dd601 */
void __SEH_epilog(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1dd620 */
void __allmul(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1dd660 */
void __aullshr(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1dd680 */
void __aullrem(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1dd6f5 */
void FUN_001dd6f5(void)
{
  FUN_001e2984();
  __flsbuf();
  __flsbuf();
}

/* 0x1dd770 */
void __aulldiv(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1dd7e0 */
void __allshr(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1dd801 */
int crt_stricmp(const char *a, const char *b)
{
  int ebx = 0;
  int ecx = 0;

  /* relift: cmp dword ptr [0x4fc25c], 0 -> jne 0x1dd80f */
  crt_tolower(0);
  crt_tolower(0);
  /* cmp ebx, ecx -> je 0x1dd81a */
  return 0;

  (void)ebx;
  (void)ecx;
}

/* 0x1dd850 */
void __alldiv(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1dd8fa */
void __copysign(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1dd91b */
void __chgsign(void)
{
  FUN_001e3a9a();
}

/* 0x1dd957 */
void FUN_001dd957(void)
{
  int eax = 0;

  __ctrlfp();
  __sptype();
  /* cmp eax, 2 -> jle 0x1dd9b3 */
  /* cmp eax, 3 -> jne 0x1dd9be */
  __handle_qnan1();
  __ctrlfp();
  /* relift: relift: fcomp qword ptr [0x2602c0] */
  /* relift: relift: fld qword ptr [0x331718] */
  FUN_001dfbd2();
  FUN_001dfe1f();
  __ctrlfp();

  (void)eax;
}

/* 0x1dda3d */
void FUN_001dda3d(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  __ctrlfp();
  /* cmp (int16_t)eax, (int16_t)ecx -> je 0x1dda7b */
  /* cmp (int16_t)eax, (int16_t)ecx -> jne 0x1ddae7 */
  /* relift: test dword ptr [ebp + 0xc], ebx -> jne 0x1ddaaa */
  /* test edx, edx -> jne 0x1ddaaa */
  /* cmp (int16_t)esi, (int16_t)ecx -> jne 0x1ddad0 */
  /* relift: test dword ptr [ebp + 0x14], ebx -> jne 0x1ddaaa */
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> je 0x1ddad0 */
  /* cmp (int16_t)edi, (int16_t)eax -> je 0x1ddca4 */
  /* cmp (int16_t)esi, (int16_t)eax -> je 0x1ddca4 */
  __ctrlfp();
  /* relift: relift: fld qword ptr [0x2602c0] */
  /* test (char)eax, 0x41 -> jne 0x1ddb35 */
  /* test (char)eax, 0x41 -> jne 0x1ddb53 */
  /* test (char)eax, 0x41 -> jne 0x1ddb81 */
  /* test (char)eax, 0x41 -> jne 0x1ddb98 */
  /* test (char)eax, 0x41 -> je 0x1ddbb1 */
  /* relift: test word ptr [ebp - 0xe], (int16_t)ecx -> jne 0x1ddc27 */
  /* relift: test dword ptr [ebp - 0x10], 0xfffff -> jne 0x1ddbe0 */
  /* relift: cmp dword ptr [ebp - 0x14], 0 -> je 0x1ddc27 */
  FUN_001dfe1f();
  __set_exp();
  /* relift: cmp dword ptr [ebp - 0x10], 0x7ff00000 -> jne 0x1ddc36 */
  /* relift: cmp dword ptr [ebp - 0x14], 0 -> je 0x1ddc45 */
  /* relift: cmp dword ptr [ebp - 0x10], 0xfff00000 -> jne 0x1ddc94 */
  /* relift: cmp dword ptr [ebp - 0x14], 0 -> jne 0x1ddc94 */
  FUN_001dfe1f();
  __set_exp();
  FUN_001dfc72();
  __ctrlfp();
  __handle_qnan2();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1ddcc6 */
void FUN_001ddcc6(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1ddd09 */
void FUN_001ddd09(void)
{
  int ecx = 0;
  int edx = 0;
  int ebp = 0;

  /* cmp (int16_t)edx, (int16_t)ecx -> jne 0x1ddd4a */
  __sptype();
  /* relift: test dword ptr [ebp + 0xc], 0xfffff -> jne 0x1ddd65 */
  /* relift: cmp dword ptr [ebp + 8], 0 -> je 0x1ddd75 */
  /* relift: relift: fcomp qword ptr [0x2602c0] */

  (void)ecx;
  (void)edx;
  (void)ebp;
}

/* 0x1ddda3 */
void FUN_001ddda3(void)
{
  int esi = 0;
  int ebp = 0;

  FUN_001dd5c8();
  /* relift: cmp dword ptr [ebp + 8], esi -> je 0x1dde6b */
  /* relift: cmp dword ptr [0x632ca0], 3 -> jne 0x1dde5c */
  FUN_001df055();
  FUN_001dde73();
  /* relift: cmp dword ptr [ebp - 0x1c], esi -> jne 0x1dde6b */
  FUN_001d0bb3();
  FUN_001d0b9c();
  __SEH_epilog();
  FUN_001defb3();

  (void)esi;
  (void)ebp;
}

/* 0x1ddda8 */
void FUN_001ddda8(void)
{
  __nh_malloc();
  FUN_001e3c37();
}

/* 0x1dddbf */
void FUN_001dddbf(void)
{
  int eax = 0;

  /* test eax, eax -> jne 0x1dddc8 */
  /* relift: cmp dword ptr [0x632ca0], 1 -> je 0x1dddd7 */
  FUN_001d0bb3();
  FUN_001d5c66();

  (void)eax;
}

/* 0x1ddde6 */
void __nh_malloc(void)
{
  int eax = 0;

  /* relift: cmp dword ptr [esp + 4], -0x20 -> ja 0x1dde0f */
  FUN_001dddbf();
  /* relift: cmp dword ptr [esp + 8], eax -> je 0x1dde11 */
  __callnewh();

  (void)eax;
}

/* 0x1dde12 */
void _malloc(void)
{
  __nh_malloc();
}

/* 0x1dde24 */
void FUN_001dde24(void)
{
  int esi = 0;
  int ebp = 0;

  FUN_001dd5c8();
  /* relift: cmp dword ptr [ebp + 8], esi -> je 0x1dde6b */
  /* relift: cmp dword ptr [0x632ca0], 3 -> jne 0x1dde5c */
  FUN_001df055();
  FUN_001dde73();
  /* relift: cmp dword ptr [ebp - 0x1c], esi -> jne 0x1dde6b */
  FUN_001d0bb3();
  FUN_001d0b9c();
  __SEH_epilog();

  (void)esi;
  (void)ebp;
}

/* 0x1dde73 */
void FUN_001dde73(void)
{
  FUN_001defb3();
}

/* 0x1dde7c */
void __forcdecpt(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;

  crt_tolower(0);
  FUN_001e153d();
  /* test eax, eax -> jne 0x1dde90 */
  /* relift: relift: mov (char)ecx, byte ptr [0x3317c0] */
  /* test (char)ecx, (char)ecx -> jne 0x1ddec5 */
  /* relift: relift: mov (char)ebx, byte ptr [0x3317c0] */
  /* cmp (char)ecx, (char)ebx -> je 0x1ddeec */
  /* test (char)ecx, (char)ecx -> jne 0x1ddee1 */
  /* test (char)ecx, (char)ecx -> je 0x1ddf1d */
  /* cmp (char)ecx, 0x65 -> je 0x1ddf06 */
  /* cmp (char)ecx, 0x45 -> je 0x1ddf06 */
  /* test (char)ecx, (char)ecx -> jne 0x1ddef5 */
  /* relift: cmp byte ptr [eax], 0x30 -> je 0x1ddf08 */
  /* relift: cmp byte ptr [eax], (char)ebx -> jne 0x1ddf13 */
  /* relift: relift: fcomp qword ptr [0x2602c0] */
  /* test (char)eax, 1 -> jne 0x1ddf36 */

  (void)eax;
  (void)ebx;
  (void)ecx;
}

/* 0x1ddf39 */
void __fassign(void)
{
  FUN_001e4048();
  FUN_001e40a3();
}

/* 0x1ddf77 */
void FUN_001ddf77(void)
{
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test esi, esi -> je 0x1ddf99 */
  /* test dl, dl -> jne 0x1ddf81 */
  memmove((void *)(uintptr_t)ecx, (void *)0, 0);

  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1ddf9a */
void FUN_001ddf9a(void)
{
  int eax = 0;
  int ecx = 0;
  int edi = 0;

  FUN_001ddf77();
  /* test edi, edi -> jle 0x1ddfe6 */
  /* relift: relift: mov (char)ecx, byte ptr [0x3317c0] */
  /* relift: cmp byte ptr [eax], 0x30 -> je 0x1de03c */
  /* cmp eax, 0x64 -> jl 0x1de029 */
  /* cmp eax, 0xa -> jl 0x1de039 */

  (void)eax;
  (void)ecx;
  (void)edi;
}

/* 0x1de043 */
void FUN_001de043(void)
{
  FUN_001e4209();
  FUN_001e40d0();
  FUN_001ddf9a();
}

/* 0x1de0a3 */
void FUN_001de0a3(void)
{
  int eax = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: cmp byte ptr [ebp + 0x10], 0 -> je 0x1de0d0 */
  /* relift: cmp eax, dword ptr [ebp + 0xc] -> jne 0x1de0d0 */
  /* test eax, eax -> jg 0x1de0f3 */
  FUN_001ddf77();
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> jle 0x1de142 */
  FUN_001ddf77();
  /* relift: relift: mov (char)eax, byte ptr [0x3317c0] */
  /* test edi, edi -> jge 0x1de142 */
  /* relift: cmp byte ptr [ebp + 0x10], 0 -> jne 0x1de11e */
  /* relift: cmp dword ptr [ebp + 0xc], edi -> jl 0x1de121 */
  FUN_001ddf77();

  (void)eax;
  (void)edi;
  (void)ebp;
}

/* 0x1de14a */
void FUN_001de14a(void)
{
  FUN_001e4209();
  FUN_001e40d0();
  FUN_001de0a3();
}

/* 0x1de19c */
void FUN_001de19c(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;

  FUN_001e4209();
  FUN_001e40d0();
  /* cmp eax, -4 -> jl 0x1de210 */
  /* cmp eax, ebx -> jge 0x1de210 */
  /* test (char)ecx, (char)ecx -> je 0x1de1fd */
  /* test (char)eax, (char)eax -> jne 0x1de1f3 */
  FUN_001de0a3();
  FUN_001ddf9a();

  (void)eax;
  (void)ebx;
  (void)ecx;
}

/* 0x1de229 */
void __cfltcvt(void)
{
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 0x10], 0x65 -> je 0x1de264 */
  /* relift: cmp dword ptr [ebp + 0x10], 0x45 -> je 0x1de264 */
  /* relift: cmp dword ptr [ebp + 0x10], 0x66 -> jne 0x1de251 */
  FUN_001de14a();
  FUN_001de19c();
  FUN_001de043();

  (void)ebp;
}

/* 0x1de27a */
void FUN_001de27a(void)
{
  __controlfp();
}

/* 0x1de28c */
void __flsbuf(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  /* test (char)eax, 0x40 -> jne 0x1de398 */
  /* test (char)eax, 1 -> je 0x1de2c5 */
  /* test (char)eax, 0x10 -> je 0x1de398 */
  /* cmp esi, 0x331050 -> je 0x1de2ef */
  /* cmp esi, 0x331070 -> jne 0x1de2fa */
  __isatty();
  __getbuf();
  __write();
  /* cmp ebx, -1 -> je 0x1de34c */
  /* relift: test byte ptr [eax + 4], 0x20 -> je 0x1de364 */
  __lseek();
  __write();

  (void)eax;
  (void)ebx;
  (void)esi;
}

/* 0x1de3a5 */
void FUN_001de3a5(void)
{
  int eax = 0;
  int ecx = 0;

  /* relift: test byte ptr [ecx + 0xc], 0x40 -> je 0x1de3b1 */
  /* relift: cmp dword ptr [ecx + 8], 0 -> je 0x1de3d5 */
  __flsbuf();
  /* cmp eax, -1 -> jne 0x1de3d5 */

  (void)eax;
  (void)ecx;
}

/* 0x1de3d8 */
void FUN_001de3d8(void)
{
  int esi = 0;
  int ebp = 0;

  FUN_001de3a5();
  /* relift: cmp dword ptr [esi], -1 -> je 0x1de3f9 */
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> jg 0x1de3e0 */

  (void)esi;
  (void)ebp;
}

/* 0x1de3fc */
void FUN_001de3fc(void)
{
  int esi = 0;
  int edi = 0;

  /* relift: cmp dword ptr [edi + 8], 0 -> jne 0x1de429 */
  FUN_001de3a5();
  /* relift: cmp dword ptr [esi], -1 -> je 0x1de430 */
  /* relift: cmp dword ptr [esp + 0xc], 0 -> jg 0x1de416 */

  (void)esi;
  (void)edi;
}

/* 0x1de452 */
void FUN_001de452(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebp - 0x14], eax -> jl 0x1deb75 */
  /* cmp (char)ebx, 0x20 -> jl 0x1de49d */
  /* cmp (char)ebx, 0x78 -> jg 0x1de49d */
  /* cmp (char)ebx, 0x2a -> jne 0x1de54c */
  /* cmp (char)ebx, 0x2a -> jne 0x1de58d */
  /* cmp (char)ebx, 0x49 -> je 0x1de5d5 */
  /* cmp (char)ebx, 0x68 -> je 0x1de5cc */
  /* cmp (char)ebx, 0x6c -> je 0x1de5c3 */
  /* cmp (char)ebx, 0x77 -> jne 0x1deb68 */
  /* cmp (char)eax, 0x36 -> jne 0x1de5f2 */
  /* relift: cmp byte ptr [ecx + 1], 0x34 -> jne 0x1de5f2 */
  /* cmp (char)eax, 0x33 -> jne 0x1de60a */
  /* relift: cmp byte ptr [ecx + 1], 0x32 -> jne 0x1de60a */
  /* cmp (char)eax, 0x64 -> je 0x1deb68 */
  /* cmp (char)eax, 0x69 -> je 0x1deb68 */
  /* cmp (char)eax, 0x6f -> je 0x1deb68 */
  /* cmp (char)eax, 0x75 -> je 0x1deb68 */
  /* cmp (char)eax, 0x78 -> je 0x1deb68 */
  /* cmp (char)eax, 0x58 -> je 0x1deb68 */
  /* relift: test byte ptr [ecx + eax*2 + 1], 0x80 -> je 0x1de667 */
  FUN_001de3a5();
  FUN_001de3a5();
  /* cmp eax, 0x67 -> jg 0x1de8b9 */
  /* cmp eax, 0x65 -> jge 0x1de709 */
  /* cmp eax, 0x58 -> jg 0x1de76b */
  /* relift: test word ptr [ebp - 4], 0x830 -> jne 0x1de6bf */
  /* cmp ecx, -1 -> jne 0x1de6cc */
  /* test eax, eax -> jne 0x1de6f0 */
  /* relift: test word ptr [ebp - 4], 0x830 -> jne 0x1de739 */
  FUN_001e2879();
  /* test esi, ebx -> je 0x1de9a9 */
  /* test eax, eax -> je 0x1de803 */
  /* test ecx, ecx -> je 0x1de803 */
  /* test (char)ecx, (char)ecx -> jne 0x1de80e */
  /* cmp (char)ebx, 0x67 -> jne 0x1de828 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)ebp;
}
