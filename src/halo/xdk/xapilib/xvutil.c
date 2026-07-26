/* kb object stubs -> xdk/xapilib/xvutil.c */

/* --- XAPILIB:xvutil.obj batch drafts (2026-07-26) --- */

/* 0x1d04f1 */
void FUN_001d04f1(void)
{
  int eax = 0;
  int ebp = 0;

  FUN_001d4464();
  /* test eax, eax -> jne 0x1d0518 */
  /* relift: test byte ptr [ebp - 4], 2 -> je 0x1d0518 */

  (void)eax;
  (void)ebp;
}

/* 0x1d051d */
void GetLocalTime(void *system_time)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d0581 */
int FUN_001d0581(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x1d0589 */
void FUN_001d0589(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d05f4 */
bool SystemTimeToFileTime(void *system_time, void *file_time)
{
  int eax = 0;

  /* test (char)eax, (char)eax -> jne 0x1d0654 */
  XapiSetLastNTError(0xc000000d);
  return 0;

  (void)eax;
}

/* 0x1d0669 */
void FUN_001d0669(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d06a0 */
void FUN_001d06a0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  FUN_001d0589();
  /* relift: cmp word ptr [esi], 0 -> je 0x1d06f0 */
  SystemTimeToFileTime((void *)(uintptr_t)esi, (void *)(uintptr_t)edi);
  /* test eax, eax -> je 0x1d0795 */
  /* relift: cmp eax, dword ptr [ebx + 4] -> jg 0x1d06e9 */
  /* relift: cmp eax, dword ptr [ebx] -> jb 0x1d0795 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x1d0795 */
  /* test (char)eax, (char)eax -> jne 0x1d07a1 */
  /* cmp (int16_t)eax, (int16_t)edi -> jle 0x1d07be */
  /* test (char)eax, (char)eax -> je 0x1d0806 */
  /* test (char)eax, (char)eax -> je 0x1d0795 */
  /* cmp ecx, eax -> jl 0x1d0844 */
  /* relift: cmp edx, dword ptr [eax + 4] -> jg 0x1d089d */
  /* relift: cmp edi, dword ptr [eax] -> jae 0x1d089d */
  /* test (char)eax, (char)eax -> jne 0x1d079e */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1d08aa */
void GetTimeZoneInformation(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

  FUN_001d0447();
  /* cmp eax, ebx -> je 0x1d08d3 */
  SetLastError(eax);
  /* relift: cmp word ptr [esi + 0x46], (int16_t)ebx -> je 0x1d09fd */
  /* relift: cmp word ptr [esi + 0x9a], (int16_t)ebx -> je 0x1d09fd */
  FUN_001d06a0();
  /* test (char)eax, (char)eax -> je 0x1d09fd */
  FUN_001d06a0();
  /* test (char)eax, (char)eax -> je 0x1d09fd */
  __allmul();
  __allmul();
  __allmul();
  /* cmp ebx, edx -> jg 0x1d09e0 */
  /* relift: cmp dword ptr [ebp - 0x18], eax -> jae 0x1d09e0 */
  /* relift: cmp dword ptr [ebp - 4], ebx -> jl 0x1d09db */
  /* relift: cmp ecx, dword ptr [ebp - 0x18] -> jb 0x1d09db */
  /* relift: cmp dword ptr [ebp - 4], edx -> jg 0x1d09db */
  /* cmp ecx, eax -> jb 0x1d09fa */
  /* relift: cmp dword ptr [ebp - 4], edx -> jl 0x1d09fa */
  /* cmp ecx, eax -> jb 0x1d09fa */
  /* relift: cmp dword ptr [ebp - 4], ebx -> jg 0x1d09fa */
  /* relift: cmp ecx, dword ptr [ebp - 0x18] -> jb 0x1d09db */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)ebp;
}

/* 0x1d0a06 */
void FUN_001d0a06(void)
{
  GetTimeZoneInformation();
  __allmul();
}

/* 0x1d0a5c */
void FUN_001d0a5c(void)
{
  FUN_001d0a06();
}

/* 0x1d0adb */
void FUN_001d0adb(void)
{
  FUN_001d0a06();
}

/* 0x1d0b06 */
void FUN_001d0b06(void)
{
  FUN_001d0a06();
}

/* 0x1d0b31 */
void FUN_001d0b31(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

  /* cmp edx, ecx -> jae 0x1d0b53 */
  /* test edx, edx -> jne 0x1d0b51 */
  /* relift: cmp dword ptr [ebp + 0xc], edx -> jbe 0x1d0b5b */
  FUN_001d5842();
  /* test esi, esi -> jne 0x1d0b79 */
  SetLastError(0);
  FUN_001d4e37();
  /* test eax, eax -> jne 0x1d0b90 */
  SetLastError(0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)ebp;
}

/* 0x1d0b9c */
void FUN_001d0b9c(void)
{
  FUN_001d6ca8();
}

/* 0x1d0bb3 */
void FUN_001d0bb3(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d0bb9 */
void * FUN_001d0bb9(unsigned int flags, unsigned int size)
{
  int eax = 0;

  FUN_001d5c66();
  /* test (char)eax, 0x40 -> je 0x1d0be3 */
  FUN_001d703b();
  return NULL;

  (void)eax;
}

/* 0x1d0c02 */
void FUN_001d0c02(void)
{
  FUN_001d52c4();
}

/* 0x1d0c16 */
void * LocalFree(void *ptr)
{
  FUN_001d6ca8();
  return NULL;
}

/* 0x1d0c48 */
void FUN_001d0c48(void)
{
  FUN_001d5c66();
}

/* 0x1d0c65 */
void FUN_001d0c65(void)
{
  int eax = 0;

  /* test (char)eax, 0x40 -> je 0x1d0c72 */
  FUN_001d703b();

  (void)eax;
}

/* 0x1d0c91 */
void FUN_001d0c91(void)
{
  int eax = 0;

  /* test eax, eax -> jl 0x1d0cb3 */
  XapiSetLastNTError(0);

  (void)eax;
}

/* 0x1d0cbf */
void FUN_001d0cbf(void)
{
  int eax = 0;
  int ebp = 0;

  /* relift: test byte ptr [ebp + 0x11], 0x80 -> je 0x1d0cd5 */
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> je 0x1d0cd5 */
  /* test eax, eax -> jl 0x1d0cef */
  XapiSetLastNTError(0);

  (void)eax;
  (void)ebp;
}

/* 0x1d0cfb */
void FUN_001d0cfb(void)
{
  int eax = 0;

  /* test eax, eax -> jl 0x1d0d1c */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1d0d3e */
  XapiSetLastNTError(0);
  FUN_001d0c91();
  FUN_001d0cbf();
  /* relift: tail-call FUN_001d0cfb(); */
  /* relift: FUN_001d0d27(0, 0, 0); */

  (void)eax;
}

/* 0x1d0da1 */
void xbox_query_global_memory_status(void *status)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d0df0 */
bool FUN_001d0df0(const char *path, unsigned int attributes)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test eax, eax -> jge 0x1d0e43 */
  XapiSetLastNTError(0);
  /* test esi, esi -> jl 0x1d0e88 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1d0ed4 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1d0f57 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jge 0x1d0fb2 */
  /* test esi, esi -> jl 0x1d0feb */
  XapiSetLastNTError(0);
  /* test eax, eax -> jge 0x1d104c */
  XapiSetLastNTError(0);
  /* test esi, esi -> jl 0x1d107a */
  XapiSetLastNTError(0);
  /* relift: test word ptr [esp + 4], 0xfff -> je 0x1d1098 */
  /* test eax, eax -> jl 0x1d10a8 */
  XapiSetLastNTError(0);
  /* relift: test byte ptr [esi + 0x38], 0x10 -> je 0x1d1174 */
  FUN_001d10bd();
  /* relift: cmp dword ptr [esi + 0x2c], 0 -> jne 0x1d11a6 */
  /* cmp eax, ebx -> jae 0x1d1195 */
  /* relift: cmp dword ptr [edi], ebx -> jae 0x1d11a6 */
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> jl 0x1d11a8 */
  /* relift: cmp dword ptr [edi], ebx -> jb 0x1d11c9 */
  /* relift: cmp dword ptr [ebp + 0x10], 0xc000000f -> jne 0x1d11e2 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
