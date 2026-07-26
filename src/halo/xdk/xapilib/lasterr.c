/* kb object stubs -> xdk/xapilib/lasterr.c */

/* --- XAPILIB:lasterr.obj batch drafts (2026-07-26) --- */

/* 0x1d21f2 */
void FUN_001d21f2(void)
{
  int eax = 0;

  FUN_001d1f10();
  /* cmp (char)eax, 2 -> jae 0x1d223d */
  /* relift: cmp dword ptr [eax + 0x28], 0 -> je 0x1d223d */

  (void)eax;
}

/* 0x1d2240 */
int xapi_GetLastError(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x1d2268 */
void SetLastError(unsigned int error)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d2296 */
void XapiSetLastNTError(int status)
{
  int edx = 0;

  SetLastError(edx);

  (void)edx;
}

/* 0x1d22ad */
void FUN_001d22ad(void)
{
  int eax = 0;
  int esi = 0;
  int ebp = 0;

  /* test eax, eax -> jge 0x1d22dd */
  XapiSetLastNTError(0);
  /* relift: cmp dword ptr [ebp + 8], -1 -> je 0x1d231f */
  /* test eax, eax -> jge 0x1d2331 */
  XapiSetLastNTError(0);
  /* test esi, esi -> jne 0x1d231b */
  /* test esi, esi -> je 0x1d2331 */
  XapiSetLastNTError(0xc000000d);
  /* test eax, eax -> jge 0x1d2361 */
  XapiSetLastNTError(0);

  (void)eax;
  (void)esi;
  (void)ebp;
}

/* 0x1d2367 */
void FUN_001d2367(void)
{
  int eax = 0;
  int ecx = 0;

  FUN_001d4436();
  /* cmp eax, ecx -> je 0x1d23bb */
  /* cmp eax, ecx -> jne 0x1d23cd */
  SetLastError(ecx);
  XapiSetLastNTError(0);

  (void)eax;
  (void)ecx;
}

/* 0x1d23d9 */
void GetOverlappedResult(void)
{
  int eax = 0;
  int esi = 0;

  /* relift: cmp dword ptr [esi], 0x103 -> jne 0x1d241e */
  /* relift: cmp dword ptr [esp + 0x14], 0 -> je 0x1d2402 */
  /* test eax, eax -> jne 0x1d23f8 */
  WaitForSingleObject(0, 0);
  /* cmp eax, 0x102 -> jne 0x1d241a */
  SetLastError(996);
  /* test eax, eax -> jne 0x1d2438 */
  /* test esi, esi -> jl 0x1d2432 */
  XapiSetLastNTError(0);

  (void)eax;
  (void)esi;
}

/* 0x1d243e */
void FUN_001d243e(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int ebp = 0;

  /* test eax, eax -> jne 0x1d2475 */
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> jne 0x1d248c */
  /* relift: cmp dword ptr [ebp + 8], 0 -> je 0x1d250f */
  FUN_001d789a((char *)(uintptr_t)ebx, (char *)(uintptr_t)0, 519);
  /* test (char)ecx, (char)ecx -> jne 0x1d24ee */
  FUN_001d789a((char *)(uintptr_t)eax, (char *)0, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)ebp;
}

/* 0x1d2518 */
void XGetLaunchInfo(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d259b */
void FUN_001d259b(void)
{
  int eax = 0;

  FUN_001d243e();
  /* test eax, eax -> jl 0x1d25d5 */
  /* test eax, eax -> je 0x1d25cd */

  (void)eax;
}

/* 0x1d25e0 */
int XLaunchNewImageA(const char *image_path, void *launch_data)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  /* cmp esi, ebx -> je 0x1d2612 */
  /* cmp (char)eax, 0x44 -> je 0x1d25fe */
  /* cmp (char)eax, 0x64 -> jne 0x1d260a */
  /* relift: cmp byte ptr [esi + 1], 0x3a -> jne 0x1d260a */
  /* relift: cmp byte ptr [esi + 2], 0x5c -> je 0x1d2631 */
  /* cmp eax, ebx -> jl 0x1d26b4 */
  /* cmp ecx, eax -> ja 0x1d269e */
  FUN_001d789a((char *)(uintptr_t)eax, (char *)(uintptr_t)eax, 0);
  /* cmp (char)ecx, (char)ebx -> jne 0x1d26b6 */
  FUN_001d259b();
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}

/* 0x1d26f3 */
int XSetNicknameW(void *param_1, int param_2)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: cmp word ptr [edi], (int16_t)esi -> jne 0x1d270f */
  /* relift: cmp dword ptr [ebp - 0x1c], 0xd48 -> je 0x1d2791 */
  /* relift: cmp dword ptr [ebp - 0xc], esi -> jl 0x1d2911 */
  FUN_001d7a59();
  /* relift: cmp eax, dword ptr [edi - 4] -> jne 0x1d27d5 */
  __wcsicmp((wchar_t *)0, (wchar_t *)(uintptr_t)edi);
  /* relift: cmp dword ptr [ebp - 8], 0x32 -> jb 0x1d27af */
  /* relift: cmp dword ptr [ebp + 0xc], esi -> jne 0x1d2801 */
  FUN_001d7a59();
  /* cmp ecx, 0x32 -> jne 0x1d2810 */
  /* relift: cmp dword ptr [ebp - 0x10], esi -> jne 0x1d2840 */
  /* cmp ecx, esi -> jne 0x1d2844 */
  _wcscmp((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)eax);
  /* cmp ecx, esi -> je 0x1d2867 */
  /* cmp ecx, eax -> jae 0x1d284d */
  memmove((void *)(uintptr_t)eax, (void *)(uintptr_t)eax, eax);
  FUN_001d7a59();
  /* relift: cmp dword ptr [ebp - 0xc], esi -> jge 0x1d28d2 */
  /* cmp edi, esi -> jl 0x1d2903 */
  FUN_001d7a59();
  /* cmp eax, 0xc0000034 -> je 0x1d2882 */
  return 0;

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d292e */
void FUN_001d292e(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: cmp word ptr [eax], (int16_t)edi -> je 0x1d29bc */
  _wcslen((wchar_t *)(uintptr_t)eax);
  /* cmp eax, edi -> je 0x1d2978 */
  /* relift: cmp edx, dword ptr [ecx + esi + 0xc] -> jne 0x1d29bc */
  /* relift: cmp dword ptr [esi + 4], edi -> jbe 0x1d29b0 */
  __wcsicmp((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)ebx);
  /* relift: cmp edi, dword ptr [esi + 4] -> jb 0x1d2987 */
  /* relift: cmp dword ptr [esi + 8], 0 -> jne 0x1d29ce */
  /* relift: cmp dword ptr [ebp + 8], 0 -> je 0x1d29ce */
  /* relift: cmp dword ptr [esi + 4], 0x32 -> jb 0x1d2945 */
  _wcscpy();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d29eb */
int FUN_001d29eb(int param_1, void *param_2, int param_3)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp eax, edi -> jl 0x1d2ac5 */
  FUN_001d0bb9(edi, 3412);
  /* cmp esi, edi -> je 0x1d2a7f */
  /* relift: cmp dword ptr [ebp - 8], ebx -> je 0x1d2a86 */
  FUN_001d292e();
  /* test eax, eax -> jne 0x1d2aac */
  /* relift: cmp dword ptr [ebp + 8], edi -> jge 0x1d2abd */
  /* cmp esi, edi -> je 0x1d2ac5 */
  LocalFree((void *)(uintptr_t)esi);
  /* cmp esi, edi -> je 0x1d2ac5 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d2ad3 */
void FUN_001d2ad3(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d2ae7 */
void FUN_001d2ae7(void)
{
  int ebx = 0;

  __allmul();
  __aullrem();
  __aullshr();
  FUN_001d2ad3();
  /* cmp ebx, 0x2c -> jle 0x1d2b4c */

  (void)ebx;
}

/* 0x1d2b79 */
void FUN_001d2b79(void)
{
  int eax = 0;
  int ebp = 0;

  SetFilePointer(0, 0, (void *)0, 0);
  ReadFile(0, (void *)(uintptr_t)eax, 0, (void *)(uintptr_t)eax, (void *)0);
  /* test eax, eax -> je 0x1d2baa */
  /* relift: cmp dword ptr [ebp - 8], 2 -> je 0x1d2bb6 */
  /* relift: cmp word ptr [ebp - 4], 0xfeff -> je 0x1d2bb6 */

  (void)eax;
  (void)ebp;
}

/* 0x1d2bbd */
void FUN_001d2bbd(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  _wcslen((wchar_t *)(uintptr_t)0);
  /* relift: cmp dword ptr [ebp - 8], ebx -> jne 0x1d2c1a */
  ReadFile(0, (void *)(uintptr_t)edi, eax, (void *)0, (void *)0);
  /* test eax, eax -> je 0x1d2d3e */
  /* relift: cmp dword ptr [ebp - 0xc], ebx -> je 0x1d2d3e */
  _wcsstr((wchar_t *)(uintptr_t)eax, (wchar_t *)0x002c1cb8);
  /* cmp eax, ebx -> jae 0x1d2c96 */
  memmove((void *)(uintptr_t)eax, (void *)(uintptr_t)eax, esi);
  _wcsstr((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)0);
  /* relift: cmp word ptr [ecx + eax], 0x3d -> jne 0x1d2ce5 */
  _wcsstr((wchar_t *)(uintptr_t)edi, (wchar_t *)0x002c1cb8);
  /* cmp edi, eax -> jl 0x1d2d02 */
  _wcsncpy((wchar_t *)(uintptr_t)0, (wchar_t *)0, edi);
  /* cmp esi, ebx -> jae 0x1d2d37 */
  SetFilePointer(0, 0, (void *)0, 0);
  /* test (char)eax, (char)eax -> jne 0x1d2d64 */
  /* test dl, dl -> jne 0x1d2d6e */
  /* test (char)ebx, (char)ebx -> jne 0x1d2d82 */
  /* test (char)ebx, (char)ebx -> jne 0x1d2d98 */
  /* cmp edi, 0x103 -> jae 0x1d2dbf */
  /* cmp edi, 0xf7 -> jge 0x1d2e3e */
  /* test dl, dl -> jne 0x1d2dd9 */
  CreateFileA((char *)(uintptr_t)eax, 0x80000000, 0, 0, 0, ebx, 0);
  FUN_001d2b79();
  /* relift: tail-call FUN_001d2bbd(); */
  CloseHandle(0);
  CreateFileA((char *)0, 0x80100000, esi, esi, 0, 0, esi);
  /* cmp edi, -1 -> je 0x1d2eb7 */
  FUN_001d2b79();
  /* test eax, eax -> je 0x1d2eaa */
  /* relift: tail-call FUN_001d2bbd(); */
  /* test eax, eax -> je 0x1d2eaa */
  _wcscmp((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)0);
  CloseHandle(0);
  xapi_GetLastError();
  CreateFileA((char *)0, 0xc0000000, 0, 0, 0, 0x02000000, 0);
  /* cmp esi, -1 -> je 0x1d2f1d */
  CloseHandle(0);
  /* test (char)ecx, (char)ecx -> jne 0x1d2f36 */
  /* test (char)ecx, (char)ecx -> jne 0x1d2f49 */
  FUN_001d2ae7();
  /* test dl, dl -> jne 0x1d2f73 */
  /* test (char)ecx, (char)ecx -> jne 0x1d2f97 */
  FUN_001d2e48();
  /* test eax, eax -> je 0x1d3135 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
