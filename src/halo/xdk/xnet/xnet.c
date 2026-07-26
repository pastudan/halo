/* kb object stubs -> xdk/xnet/xnet.c */

/* --- XNET:xnet.obj batch drafts (2026-07-26) --- */

/* 0x1d8259 */
void XapiInitProcess(void)
{
  int eax = 0;
  int esi = 0;

  FUN_001d7749();
  FUN_001d5842();
  /* mem[0x00632a28] = eax */
  /* relift: test byte ptr [0x10124], 8 -> jne 0x1d8323 */
  FUN_001d7d21((void *)0x0032fd70);
  /* test eax, eax -> jl 0x1d82ff */
  /* cmp eax, esi -> jge 0x1d82d9 */
  /* cmp eax, 0xc0000035 -> jne 0x1d829d */
  FUN_001d819f();
  /* cmp eax, esi -> jge 0x1d8303 */
  /* cmp eax, 0xc000007f -> jne 0x1d82ff */
  /* test (char)eax, 1 -> je 0x1d8342 */
  XMountUtilityDrive();
  /* test eax, eax -> jne 0x1d8342 */
  XapiBootToDash();
  /* cmp eax, esi -> jge 0x1d8342 */
  /* cmp eax, 0xc0000035 -> jne 0x1d829d */
  FUN_001d454b();
  /* cmp esi, eax -> jae 0x1d8364 */
  XapiBootToDash();

  (void)eax;
  (void)esi;
}

/* 0x1d8368 */
int XapiFormatFATVolume(void *device_path)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp eax, edi -> jge 0x1d83ac */
  XapiSetLastNTError(0);
  /* cmp ebx, edi -> jge 0x1d83e2 */
  FUN_001d8750(0);
  /* cmp esi, edi -> jge 0x1d841e */
  /* relift: cmp dword ptr [ebp - 0xc], edi -> jae 0x1d84b1 */
  __alldiv();
  /* cmp eax, 0xfff0 -> jae 0x1d8479 */
  /* cmp eax, edi -> ja 0x1d84b1 */
  /* cmp eax, esi -> jb 0x1d84c6 */
  /* relift: cmp dword ptr [ebp - 0x10], edi -> jbe 0x1d84c6 */
  SetLastError(112);
  FUN_001d0bb9(ecx, ebx);
  /* test esi, esi -> jne 0x1d84e6 */
  LocalFree((void *)(uintptr_t)esi);
  LocalFree((void *)(uintptr_t)esi);
  /* relift: cmp dword ptr [ebp - 0x14], edi -> jl 0x1d8674 */
  XapiSetLastNTError(0);
  /* test eax, eax -> je 0x1d8697 */
  /* cmp eax, -1 -> je 0x1d8697 */
  /* relift: cmp esi, dword ptr [esp + 8] -> jb 0x1d868a */
  /* test eax, eax -> je 0x1d86b6 */
  /* cmp eax, -1 -> je 0x1d86b6 */
  /* relift: cmp esi, dword ptr [esp + 8] -> jb 0x1d86a9 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d86c3 */
void _cinit(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d871b */
void _rtinit(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d8750 */
unsigned int FUN_001d8750(unsigned int val)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x1d8766 */
int xCompareStringA(int flags, const char *a, int a_len, const char *b, int b_len)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 0x14], esi -> je 0x1d88df */
  /* relift: cmp dword ptr [ebp + 0x10], -1 -> jl 0x1d88df */
  /* relift: cmp dword ptr [ebp + 0x18], -1 -> jl 0x1d88df */
  /* relift: cmp dword ptr [ebp + 0x10], esi -> je 0x1d88c0 */
  /* test dl, dl -> je 0x1d88a9 */
  /* test (char)ebx, (char)ebx -> je 0x1d88b6 */
  /* test ecx, esi -> je 0x1d883e */
  /* test ecx, edx -> je 0x1d8825 */
  /* cmp esi, edx -> jae 0x1d881a */
  /* relift: cmp dword ptr [ebp - 4], 0 -> jne 0x1d8832 */
  /* test ecx, edx -> je 0x1d8855 */
  /* relift: cmp dword ptr [ebp - 4], 0 -> jne 0x1d884f */
  /* relift: cmp dword ptr [ebp + 8], 0 -> je 0x1d8868 */
  /* test ecx, esi -> jne 0x1d8836 */
  /* test ecx, edx -> jne 0x1d8899 */
  /* relift: cmp dword ptr [ebp - 8], 0 -> je 0x1d888d */
  /* test ecx, esi -> je 0x1d8880 */
  /* test ecx, edx -> je 0x1d888d */
  /* cmp esi, edx -> jb 0x1d88b1 */
  /* relift: cmp byte ptr [eax], 0 -> je 0x1d88c5 */
  /* relift: cmp dword ptr [ebp + 0x10], esi -> jne 0x1d88d1 */
  /* relift: cmp dword ptr [ebp + 0x18], esi -> jne 0x1d88d1 */
  SetLastError(87);
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)ebp;
}

/* 0x1d88ef */
void FUN_001d88ef(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 0x14], esi -> je 0x1d8a78 */
  /* relift: cmp dword ptr [ebp + 0x10], -1 -> jl 0x1d8a78 */
  /* relift: cmp dword ptr [ebp + 0x18], -1 -> jl 0x1d8a78 */
  /* relift: cmp dword ptr [ebp + 0x10], esi -> je 0x1d8a59 */
  /* relift: cmp word ptr [edx], (int16_t)esi -> je 0x1d8a42 */
  /* relift: cmp word ptr [edx], (int16_t)esi -> je 0x1d8a4f */
  /* test ecx, esi -> je 0x1d89cf */
  /* test ecx, edx -> je 0x1d89b5 */
  /* cmp esi, edx -> jae 0x1d89aa */
  /* relift: cmp dword ptr [ebp - 4], 0 -> jne 0x1d89c2 */
  /* test ecx, edx -> je 0x1d89e6 */
  /* relift: cmp dword ptr [ebp - 4], 0 -> jne 0x1d89e0 */
  /* relift: cmp dword ptr [ebp + 8], 0 -> je 0x1d89ff */
  /* test ecx, esi -> jne 0x1d89c6 */
  /* test ecx, edx -> je 0x1d89ff */
  /* relift: cmp dword ptr [ebp - 8], 0 -> je 0x1d8a24 */
  /* test ecx, esi -> je 0x1d8a17 */
  /* test ecx, edx -> je 0x1d8a24 */
  /* cmp esi, edx -> jb 0x1d8a4a */
  /* relift: cmp word ptr [eax], (int16_t)esi -> je 0x1d8a5e */
  /* relift: cmp dword ptr [ebp + 0x10], esi -> jne 0x1d8a6a */
  /* relift: cmp dword ptr [ebp + 0x18], esi -> jne 0x1d8a6a */
  SetLastError(87);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)ebp;
}

/* 0x1d8a88 */
void FUN_001d8a88(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* test (char)eax, (char)eax -> jne 0x1d8aeb */
  /* cmp edi, esi -> jb 0x1d8ab3 */
  SetLastError(1168);

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x1d8aef */
void FUN_001d8aef(void)
{
  int eax = 0;

  /* test eax, eax -> jge 0x1d8b09 */
  XapiSetLastNTError(0);

  (void)eax;
}

/* 0x1d8b10 */
void FUN_001d8b10(void)
{
  int eax = 0;

  /* test eax, eax -> jge 0x1d8b28 */
  XapiSetLastNTError(0);
  FUN_001d8a88();
  /* cmp eax, -1 -> je 0x1d8b44 */
  FUN_001d8aef();
  FUN_001d8a88();
  /* cmp eax, -1 -> je 0x1d8b5f */
  /* relift: tail-call FUN_001d8b10(); */

  (void)eax;
}

/* 0x1d8b64 */
void XGetSectionSize(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d8b76 */
uint32_t XNetGetEthernetLinkStatus(void)
{
  int eax = 0;
  int esi = 0;

  /* cmp eax, esi -> je 0x1d8b97 */
  FUN_001d0362();
  /* relift: cmp dword ptr [0x4ee4b0], esi -> jne 0x1d8ba7 */
  /* mem[0x004ee4b4] = esi */
  return 0;

  (void)eax;
  (void)esi;
}

/* 0x1d8df8 */
void XcSHAUpdate(int a, int b, int c)
{
  if (a == 0 && b == 0 && c == 0) {
    return;
  }
  (void)a;
  (void)b;
  (void)c;
}

/* 0x1d8dfe */
void XcSHAInit(int ctx)
{
  if (ctx == 0) {
    return;
  }
  (void)ctx;
}

/* 0x1d8e04 */
void XcSHAFinal(int a, int b)
{
  if (a == 0 && b == 0) {
    return;
  }
  (void)a;
  (void)b;
}

/* 0x1d8e0a */
void ExQueryNonVolatileSetting(int a, int b, int c, int d)
{
  (void)a;
  (void)b;
  (void)c;
  (void)d;
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: FUN_001d8b2e(0, 0); */
  /* relift: FUN_001d8b49(0, 0); */
  /* test eax, eax -> jge 0x1d8ffc */
  /* mem[0x003314a0] = eax */
  /* mem[0x003314a4] = 0x1dded4 */
  /* mem[0x003314a8] = 0x1ddf39 */
  /* mem[0x003314ac] = 0x1dde7c */
  /* mem[0x003314b0] = 0x1ddf1f */
  /* mem[0x003314b4] = eax */
  /* mem[0x004fc000] = ecx */
  FUN_001d9011();
  FUN_001de27a();
  /* test eax, eax -> je 0x1d90c7 */
  /* test edx, 0x7fffffff -> jne 0x1d908b */
  /* test eax, eax -> je 0x1d90ef */
  FUN_001de452();
  __flsbuf();
  FUN_001de452();
  FUN_001de452();
  __flsbuf();
  /* test esi, esi -> je 0x1d91ee */
  /* cmp edi, ecx -> jbe 0x1d925a */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
