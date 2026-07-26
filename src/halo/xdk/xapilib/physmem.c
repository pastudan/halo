/* kb object stubs -> xdk/xapilib/physmem.c */

#include "../xdk_stubs_protos.h"
#include "../xdk_cross_protos.h"

/* --- XAPILIB:physmem.obj batch drafts (2026-07-26) --- */

/* 0x1d2d48 */

/* --- forward decls (auto) --- */
void FUN_001d2d48(void);
void FUN_001d2e48(void);
void FUN_001d2ec6(void);
void FUN_001d2f22(void);
void FUN_001d3185(void);
void FUN_001d3254(void);
void FUN_001d335b(void);
void FUN_001d33a2(int param_1);
bool QueryPerformanceCounter(void *counter);
bool QueryPerformanceFrequency(void *freq);
int CreateDirectoryA(const char *path, int access);
bool FUN_001d347c(const char *path);
void FUN_001d350a(void);
void FUN_001d3576(void);
void FUN_001d3683(void);
void * XPhysicalAlloc(size_t size, unsigned int addr, unsigned int alignment, unsigned int protect);
void physical_memory_protect(void *addr, unsigned int size, unsigned int protect);
void MmFreeContiguousMemory(void *base_address);
unsigned long MmQueryAddressProtect(void *virtual_address);
void FUN_001d3739(void);
void XapiSelectCachePartition(void);
void XMountUtilityDrive(void);
void XMountAlternateTitleA(void);
void XUnmountAlternateTitleA(void);
void FUN_001d3f42(void);
void FUN_001d3fe1(void);
void XMUNameFromDriveLetter(void);
void FUN_001d4157(void);
void FUN_001d41be(void);
void FUN_001d4230(void);
void XCalculateSignatureBegin(void);
void FUN_001d42a9(void);
void FUN_001d42c3(void);
void xbe_main_thread(void);
void entry(void);
void XapiFormatObjectAttributes(void);
void FUN_001d4436(void);
void FUN_001d4464(void);
void FUN_001d4486(void);
void FUN_001d44b3(void);
void FUN_001d44dc(void);
void FUN_001d4507(void);
void FUN_001d454b(void);
void FUN_001d4570(void);
void FUN_001d46a3(void);
void FUN_001d47c3(void);
void FUN_001d47e4(void);
void FUN_001d4877(void);
void FUN_001d4a02(void);
void FUN_001d4a34(void);
void FUN_001d4cd9(void);
void FUN_001d4dd3(void);
void FUN_001d4e37(void);
void FUN_001d4ec6(void);
void FUN_001d52c4(void);
void FUN_001d52f3(void);
void FUN_001d5411(void);
void FUN_001d5598(void);
void FUN_001d5842(void);

void FUN_001d2d48(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int edi = 0;

  /* test (char)eax, (char)eax -> jne 0x1d2d64 */
  /* test dl, dl -> jne 0x1d2d6e */
  /* test (char)ebx, (char)ebx -> jne 0x1d2d82 */
  /* test (char)ebx, (char)ebx -> jne 0x1d2d98 */
  /* cmp edi, 0x103 -> jae 0x1d2dbf */
  /* cmp edi, 0xf7 -> jge 0x1d2e3e */
  /* test dl, dl -> jne 0x1d2dd9 */
  CreateFileA((char *)(uintptr_t)eax, 0x80000000, 0, 0, 0, ebx, 0);
  FUN_001d2b79();
  FUN_001d2bbd();
  CloseHandle(0);

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)edi;
}

/* 0x1d2e48 */
void FUN_001d2e48(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  CreateFileA((char *)0, 0x80100000, esi, esi, 0, 0, esi);
  /* cmp edi, -1 -> je 0x1d2eb7 */
  FUN_001d2b79();
  /* test eax, eax -> je 0x1d2eaa */
  FUN_001d2bbd();
  /* test eax, eax -> je 0x1d2eaa */
  _wcscmp((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)0);
  CloseHandle(0);
  xapi_GetLastError();

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x1d2ec6 */
void FUN_001d2ec6(void)
{
  int esi = 0;

  CreateFileA((char *)0, 0xc0000000, 0, 0, 0, 0x02000000, 0);
  /* cmp esi, -1 -> je 0x1d2f1d */
  CloseHandle(0);

  (void)esi;
}

/* 0x1d2f22 */
void FUN_001d2f22(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test (char)ecx, (char)ecx -> jne 0x1d2f36 */
  /* test (char)ecx, (char)ecx -> jne 0x1d2f49 */
  FUN_001d2ae7();
  /* test dl, dl -> jne 0x1d2f73 */
  /* test (char)ecx, (char)ecx -> jne 0x1d2f97 */
  FUN_001d2e48();
  /* test eax, eax -> je 0x1d3135 */
  CreateDirectoryA((char *)(uintptr_t)eax, 0);
  /* test eax, eax -> jne 0x1d303e */
  xapi_GetLastError();
  /* test (char)ecx, (char)ecx -> jne 0x1d2ff3 */
  FUN_001d2e48();
  /* test ebx, ebx -> jne 0x1d3039 */
  FUN_001d2ec6();
  /* relift: cmp dword ptr [ebp + 0x10], 1 -> je 0x1d302f */
  /* test ebx, ebx -> je 0x1d3135 */
  /* test (char)ecx, (char)ecx -> jne 0x1d304e */
  /* test eax, eax -> jge 0x1d30bf */
  FUN_001dd6f5();
  _wcslen((wchar_t *)(uintptr_t)eax);
  WriteFile(0, (void *)(uintptr_t)eax, esi, (void *)(uintptr_t)eax, (void *)0);
  /* test eax, eax -> je 0x1d3163 */
  CloseHandle(0);
  /* test esi, esi -> je 0x1d315c */
  FUN_001d789a((char *)(uintptr_t)esi, (char *)(uintptr_t)eax, 0);
  /* cmp edi, ebx -> jae 0x1d315c */
  xapi_GetLastError();
  CloseHandle(0);
  FUN_001d347c((char *)(uintptr_t)eax);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d3185 */
void FUN_001d3185(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* test (char)ecx, (char)ecx -> jne 0x1d31a6 */
  /* test (char)eax, (char)eax -> jne 0x1d31be */
  /* test (char)ecx, (char)ecx -> jne 0x1d31d1 */
  FUN_001d2ae7();
  /* test dl, dl -> jne 0x1d31fb */
  /* test (char)ecx, (char)ecx -> jne 0x1d3216 */
  FUN_001d2e48();
  FUN_001d7cb4((void *)(uintptr_t)eax);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x1d3254 */
void FUN_001d3254(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test (char)ecx, (char)ecx -> jne 0x1d3268 */
  /* test (char)ecx, (char)ecx -> jne 0x1d327b */
  /* test dl, dl -> jne 0x1d3297 */
  FUN_001d3576();
  /* cmp edi, -1 -> je 0x1d3352 */
  FUN_001d2d48();
  /* test eax, eax -> jne 0x1d330a */
  FUN_001d3683();
  FUN_001d2d48();
  /* test eax, eax -> jne 0x1d32f4 */
  FUN_001d3683();
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> jne 0x1d330a */
  CloseHandle(0);
  SetLastError(0);
  /* cmp edi, -1 -> je 0x1d3352 */
  FUN_001d0bb9(0, 272);
  /* test esi, esi -> je 0x1d3342 */
  FUN_001d789a((char *)(uintptr_t)eax, (char *)0, 260);
  CloseHandle(0);
  SetLastError(0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d335b */
void FUN_001d335b(void)
{
  int eax = 0;
  int edi = 0;

  FUN_001d3683();
  /* test edi, edi -> je 0x1d339b */
  FUN_001d2d48();
  /* test eax, eax -> jne 0x1d339a */
  FUN_001d3683();
  /* test edi, edi -> jne 0x1d3377 */

  (void)eax;
  (void)edi;
}

/* 0x1d33a2 */
void FUN_001d33a2(int param_1)
{
  int ecx = 0;
  int edx = 0;

  /* cmp edx, 0x53425645 -> je 0x1d33d4 */
  /* cmp edx, 0xbe4bea00 -> jne 0x1d33e2 */
  LocalFree((void *)(uintptr_t)ecx);
  CloseHandle(0);
  LocalFree((void *)(uintptr_t)ecx);

  (void)ecx;
  (void)edx;
}

/* 0x1d33e6 */
bool QueryPerformanceCounter(void *counter)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x1d33fb */
bool QueryPerformanceFrequency(void *freq)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x1d3410 */
int CreateDirectoryA(const char *path, int access)
{
  int eax = 0;

  /* test eax, eax -> jl 0x1d3470 */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
}

/* 0x1d347c */
bool FUN_001d347c(const char *path)
{
  int eax = 0;
  int esi = 0;

  /* test eax, eax -> jge 0x1d34cf */
  XapiSetLastNTError(0);
  /* test esi, esi -> jl 0x1d34fd */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
  (void)esi;
}

/* 0x1d350a */
void FUN_001d350a(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d3576 */
void FUN_001d3576(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp byte ptr [edx + eax - 1], 0x5c -> je 0x1d35b9 */
  /* cmp (int16_t)ecx, (int16_t)edi -> je 0x1d3673 */
  /* cmp (int16_t)ecx, 3 -> jne 0x1d3600 */
  /* relift: cmp byte ptr [edx], 0x2a -> jne 0x1d3600 */
  /* relift: cmp byte ptr [edx + 1], 0x2e -> jne 0x1d3600 */
  /* relift: cmp byte ptr [edx + 2], 0x2a -> jne 0x1d3600 */
  /* cmp eax, edi -> jge 0x1d3625 */
  /* cmp esi, edi -> jge 0x1d365f */
  XapiSetLastNTError(0);
  FUN_001d350a();
  SetLastError(87);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1d3683 */
void FUN_001d3683(void)
{
  XapiSetLastNTError(0);
  FUN_001d350a();
}

/* 0x1d36d4 */
void * XPhysicalAlloc(size_t size, unsigned int addr, unsigned int alignment, unsigned int protect)
{
  int esi = 0;

  /* test esi, esi -> jne 0x1d3710 */
  SetLastError(0);
  return NULL;

  (void)esi;
}

/* 0x1d371d */
void physical_memory_protect(void *addr, unsigned int size, unsigned int protect)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d372d */
void MmFreeContiguousMemory(void *base_address)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d3733 */
unsigned long MmQueryAddressProtect(void *virtual_address)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x1d3739 */
void FUN_001d3739(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test eax, eax -> jge 0x1d37a0 */
  XapiSetLastNTError(0);
  xapi_GetLastError();
  /* cmp eax, 2 -> jne 0x1d3799 */
  SetLastError(0);
  /* test esi, esi -> jge 0x1d37cf */
  XapiSetLastNTError(0);
  __allmul();
  __allmul();
  /* test ecx, ecx -> je 0x1d3808 */
  /* test ecx, ecx -> je 0x1d3814 */
  /* test eax, eax -> je 0x1d3823 */
  FUN_001dd5c8();
  /* cmp eax, ebx -> jge 0x1d38a4 */
  XapiSetLastNTError(0);
  /* relift: cmp dword ptr [ebp + 0xc], ebx -> jne 0x1d38b3 */
  /* relift: cmp dword ptr [ebp + 0x14], ebx -> je 0x1d38e3 */
  /* relift: cmp dword ptr [ebp + 0xc], ebx -> je 0x1d38bb */
  FUN_001d5c66();
  /* cmp eax, ebx -> jne 0x1d38e3 */
  /* relift: cmp dword ptr [ebp + 0x20], ebx -> jne 0x1d38f7 */
  /* relift: cmp dword ptr [ebp + 0x18], ebx -> jne 0x1d38f2 */
  /* relift: cmp dword ptr [ebp + 0x1c], ebx -> je 0x1d3941 */
  /* relift: cmp dword ptr [ebp + 0x20], ebx -> je 0x1d38ff */
  FUN_001d5c66();
  /* cmp edi, ebx -> jne 0x1d3944 */
  /* relift: cmp dword ptr [ebp - 0x38], ebx -> je 0x1d3937 */
  FUN_001d6ca8();
  /* relift: cmp dword ptr [ebp - 0x38], ebx -> je 0x1d3968 */
  /* cmp eax, ebx -> jl 0x1d3984 */
  /* cmp edi, ebx -> je 0x1d3992 */
  /* cmp eax, ebx -> jge 0x1d3992 */
  XapiSetLastNTError(0);
  /* cmp esi, ebx -> je 0x1d39c2 */
  /* relift: cmp eax, dword ptr [ebp + 0x10] -> jae 0x1d39de */
  memmove((void *)(uintptr_t)esi, (void *)(uintptr_t)ecx, 0);
  /* cmp eax, ebx -> je 0x1d39d1 */
  /* relift: cmp dword ptr [ebp + 0x20], ebx -> je 0x1d3a06 */
  /* relift: cmp eax, dword ptr [ebp + 0x24] -> jb 0x1d39ed */
  SetLastError(24);
  memmove((void *)(uintptr_t)0, (void *)(uintptr_t)eax, eax);
  /* cmp eax, ebx -> je 0x1d3a12 */
  /* cmp eax, ebx -> je 0x1d3a1d */
  /* relift: FUN_001d3a62(0, 0); */
  __SEH_epilog();
  XapiSetLastNTError(0xc0000005);
  __local_unwind2();
  /* relift: cmp dword ptr [ebp - 0x38], ebx -> je 0x1d3a7f */
  FUN_001d6ca8();
  /* cmp edi, ebx -> je 0x1d3a90 */
  FUN_001d6ca8();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d3a91 */
void XapiSelectCachePartition(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebp - 0x34], esi -> jne 0x1d3b43 */
  /* relift: cmp dword ptr [ebp - 0x228], ebx -> je 0x1d3b63 */
  /* cmp eax, 0x29 -> jbe 0x1d3b7b */
  /* test eax, eax -> jbe 0x1d3ba0 */
  /* relift: cmp ebx, dword ptr [edx] -> jne 0x1d3b98 */
  /* relift: cmp dword ptr [edx + 8], 0 -> jne 0x1d3c75 */
  /* cmp ecx, eax -> jb 0x1d3b87 */
  /* test eax, eax -> jbe 0x1d3bd3 */
  /* relift: cmp dword ptr [ecx + 4], 0 -> je 0x1d3bbb */
  /* relift: cmp dword ptr [ecx], esi -> je 0x1d3bc3 */
  /* cmp edx, eax -> jb 0x1d3bb1 */
  /* cmp edx, eax -> jne 0x1d3bca */
  /* cmp esi, eax -> jb 0x1d3ba9 */
  /* test edi, edi -> jne 0x1d3be0 */
  /* cmp edi, ecx -> jb 0x1d3bea */
  /* test ebx, ebx -> je 0x1d3c20 */
  memmove((void *)(uintptr_t)eax, (void *)(uintptr_t)eax, eax);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d3c95 */
void XMountUtilityDrive(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  XapiSelectCachePartition();
  /* test eax, eax -> jl 0x1d3d6f */
  /* relift: cmp dword ptr [ebp + 8], 0 -> jne 0x1d3cc9 */
  /* relift: cmp dword ptr [ebp - 0xc], 0 -> jne 0x1d3cc9 */
  snprintf((char *)(uintptr_t)eax, 260, (char *)0x002c1de8);
  /* test ebx, ebx -> je 0x1d3d1f */
  XapiFormatFATVolume(0);
  /* test esi, esi -> je 0x1d3d77 */
  FUN_001d7d21((void *)(uintptr_t)eax);
  /* test edi, edi -> jge 0x1d3d4e */
  /* test ebx, ebx -> jne 0x1d3d4a */
  XapiFormatFATVolume(0);
  /* test eax, eax -> je 0x1d3d4a */
  FUN_001d7d21((void *)(uintptr_t)eax);
  /* test edi, edi -> jl 0x1d3d5f */
  /* test esi, esi -> jne 0x1d3d77 */
  XapiSetLastNTError(0);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d3d80 */
void XMountAlternateTitleA(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test edx, edx -> je 0x1d3dcd */
  /* relift: cmp dword ptr [ebp + 0xc], edx -> je 0x1d3dbe */
  /* cmp edi, 0x10 -> jb 0x1d3daa */
  /* cmp edi, esi -> jb 0x1d3dd5 */
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x002c1e30);
  /* cmp eax, edi -> jge 0x1d3e2a */
  /* cmp esi, edi -> jge 0x1d3e5c */
  /* cmp eax, 9 -> jb 0x1d3edb */
  /* relift: cmp byte ptr [ebp + eax - 0x241], 0x5c -> jne 0x1d3edb */
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x002c1e28);
  XapiMapLetterToDirectory();
  /* cmp eax, edi -> jl 0x1d3e1e */
  /* cmp (char)ebx, 0x55 -> je 0x1d3e1e */
  /* relift: relift: mov byte ptr [0x4ee168], (char)ebx */

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d3ee5 */
void XUnmountAlternateTitleA(void)
{
  int eax = 0;
  int ebp = 0;

  crt_sprintf((char *)(uintptr_t)eax, (char *)0x002c1e30);
  /* relift: cmp byte ptr [ebp + 8], 0x58 -> jne 0x1d3f37 */
  /* test eax, eax -> jl 0x1d3f37 */

  (void)eax;
  (void)ebp;
}

/* 0x1d3f42 */
void FUN_001d3f42(void)
{
  int eax = 0;
  int esi = 0;

  /* test eax, eax -> jge 0x1d3fa6 */
  XapiSetLastNTError(0);
  xapi_GetLastError();
  /* cmp eax, 2 -> jne 0x1d3fa2 */
  SetLastError(0);
  /* test esi, esi -> jge 0x1d3fd5 */
  XapiSetLastNTError(0);

  (void)eax;
  (void)esi;
}

/* 0x1d3fe1 */
void FUN_001d3fe1(void)
{
  int eax = 0;
  int esi = 0;

  /* test eax, eax -> jge 0x1d4045 */
  XapiSetLastNTError(0);
  xapi_GetLastError();
  /* cmp eax, 2 -> jne 0x1d4041 */
  SetLastError(0);
  /* test esi, esi -> jge 0x1d4074 */
  XapiSetLastNTError(0);

  (void)eax;
  (void)esi;
}

/* 0x1d407c */
void XMUNameFromDriveLetter(void)
{
  int eax = 0;
  int edx = 0;

  /* relift: test dword ptr [0x4ee16c], edx -> jne 0x1d409e */
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x002c1e30);
  /* cmp eax, 0x20 -> jb 0x1d4132 */
  FUN_001d7a59();

  (void)eax;
  (void)edx;
}

/* 0x1d4157 */
void FUN_001d4157(void)
{
  int eax = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 0xc], 0x40 -> jbe 0x1d416a */
  /* cmp eax, 0x10 -> jb 0x1d4191 */
  XcSHAInit(0);
  XcSHAUpdate(0, 0, 64);

  (void)eax;
  (void)ebp;
}

/* 0x1d41be */
void FUN_001d41be(void)
{
  int eax = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebp + 0x10], eax -> jbe 0x1d41cf */
  /* cmp eax, 0x10 -> jb 0x1d41f4 */
  XcSHAFinal(0, 0);
  XcSHAInit(0);
  XcSHAUpdate(0, 0, 84);
  XcSHAFinal(0, 0);

  (void)eax;
  (void)ebp;
}

/* 0x1d4230 */
void FUN_001d4230(void)
{
  FUN_001d4157();
  XcSHAUpdate(0, 0, 20);
  FUN_001d41be();
}

/* 0x1d426b */
void XCalculateSignatureBegin(void)
{
  int esi = 0;

  FUN_001d0bb9(0, 124);
  /* test esi, esi -> jne 0x1d4287 */
  SetLastError(0);
  FUN_001d4157();

  (void)esi;
}

/* 0x1d42a9 */
void FUN_001d42a9(void)
{
  XcSHAUpdate(0, 0, 0);
}

/* 0x1d42c3 */
void FUN_001d42c3(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> je 0x1d4306 */
  /* test esi, esi -> je 0x1d42e4 */
  FUN_001d41be();
  /* test esi, esi -> je 0x1d4306 */
  FUN_001d4230();
  LocalFree((void *)(uintptr_t)edi);
  xapi_GetLastError();
  /* test eax, eax -> je 0x1d4342 */

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x1d4345 */
void xbe_main_thread(void)
{
  int eax = 0;
  int ecx = 0;

  XapiInitProcess();
  /* test eax, eax -> je 0x1d435f */
  /* test ecx, ecx -> je 0x1d438c */
  _rtinit();
  _cinit();
  main(0, (const char **)(uintptr_t)0, (const char **)(uintptr_t)0);
  XapiBootToDash();

  (void)eax;
  (void)ecx;
}

/* 0x1d43b4 */
void entry(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* mem[0x00632a30] = eax */
  CreateThread((void *)(uintptr_t)esi, 0, (void *)0x001d4345, (void *)(uintptr_t)esi, 0, (void *)(uintptr_t)esi);
  /* cmp edi, esi -> jne 0x1d4405 */
  XapiBootToDash();
  CloseHandle(0);

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x1d440e */
void XapiFormatObjectAttributes(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d4436 */
void FUN_001d4436(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d4464 */
void FUN_001d4464(void)
{
  ExQueryNonVolatileSetting(0, 0, 0, 0);
}

/* 0x1d4486 */
void FUN_001d4486(void)
{
  int eax = 0;

  ExQueryNonVolatileSetting(0, 0, 0, 0);
  /* test eax, eax -> jl 0x1d44a7 */

  (void)eax;
}

/* 0x1d44b3 */
void FUN_001d44b3(void)
{
  int eax = 0;

  ExQueryNonVolatileSetting(259, 0, 0, 0);
  /* test eax, eax -> jl 0x1d44d8 */

  (void)eax;
}

/* 0x1d44dc */
void FUN_001d44dc(void)
{
  int eax = 0;

  ExQueryNonVolatileSetting(0, 0, 0, 0);
  /* test eax, eax -> jl 0x1d4503 */

  (void)eax;
}

/* 0x1d4507 */
void FUN_001d4507(void)
{
  int eax = 0;

  ExQueryNonVolatileSetting(0, 0, 0, 0);
  /* test eax, eax -> jge 0x1d4527 */
  /* cmp eax, 3 -> je 0x1d453f */
  /* cmp eax, 6 -> jne 0x1d4546 */

  (void)eax;
}

/* 0x1d454b */
void FUN_001d454b(void)
{
  int eax = 0;

  ExQueryNonVolatileSetting(10, 0, 0, 0);
  /* test eax, eax -> jl 0x1d456c */

  (void)eax;
}

/* 0x1d4570 */
void FUN_001d4570(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  ExQueryNonVolatileSetting(260, 0, 0, 0);
  /* test eax, eax -> jl 0x1d4594 */
  FUN_001dd5c8();
  /* test (char)eax, 1 -> jne 0x1d45d0 */
  /* relift: cmp dword ptr [ebp - 0x28], 0x40 -> jae 0x1d4675 */
  /* test edi, edi -> je 0x1d4656 */
  /* relift: cmp esi, dword ptr [edi + 0x2c] -> jae 0x1d4656 */
  /* relift: test byte ptr [esi + 5], 1 -> jne 0x1d4628 */
  /* relift: test byte ptr [esi + 5], 0x10 -> je 0x1d4652 */
  /* test ebx, ebx -> jne 0x1d4642 */
  /* relift: FUN_001d468d(0, 0); */
  __SEH_epilog();
  /* relift: cmp byte ptr [ebp - 0x1d], 0 -> je 0x1d46a2 */

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d46a3 */
void FUN_001d46a3(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d47c3 */
void FUN_001d47c3(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d47e4 */
void FUN_001d47e4(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp edx, ecx -> ja 0x1d485c */
  /* relift: cmp ecx, dword ptr [ebp + 0xc] -> jne 0x1d4829 */
  FUN_001d47c3();
  /* relift: cmp edi, dword ptr [esi + 0x1c] -> jbe 0x1d482b */
  /* test eax, eax -> jne 0x1d47f5 */
  FUN_001d46a3();
  /* test eax, eax -> je 0x1d4855 */
  /* relift: cmp edi, dword ptr [esi + 0x1c] -> jb 0x1d4855 */
  /* relift: cmp edx, dword ptr [eax + 4] -> jne 0x1d4831 */
  /* relift: cmp eax, dword ptr [esi + 0x1c] -> jbe 0x1d4855 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d4877 */
void FUN_001d4877(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [esi + 8], eax -> jb 0x1d48a8 */
  /* test ecx, ecx -> je 0x1d48bd */
  /* relift: cmp dword ptr [esi + 4], ecx -> je 0x1d48bd */
  /* test esi, esi -> jne 0x1d489a */
  /* test eax, eax -> je 0x1d48da */
  /* test eax, eax -> jl 0x1d48b4 */
  /* relift: cmp eax, dword ptr [esi + 8] -> jne 0x1d4906 */
  /* relift: cmp ecx, dword ptr [esi + 4] -> je 0x1d4969 */
  /* test ecx, ecx -> jne 0x1d492e */
  /* relift: test byte ptr [ebx + 5], 0x10 -> jne 0x1d4969 */
  /* cmp ebx, ecx -> jae 0x1d495d */
  /* relift: cmp word ptr [ebx], 0 -> je 0x1d495d */
  /* relift: test byte ptr [ebx + 5], 0x10 -> je 0x1d4940 */
  /* relift: cmp ebx, dword ptr [ebp + 0xc] -> jne 0x1d48b4 */
  /* relift: cmp ecx, dword ptr [edi + 0x2c] -> jne 0x1d498a */
  FUN_001d47c3();
  /* relift: cmp dword ptr [edi + 0x1c], 0 -> jne 0x1d48b6 */
  /* relift: cmp edx, dword ptr [edi + 0x1c] -> jb 0x1d49f7 */
  /* test ecx, ecx -> jne 0x1d49ec */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d4a02 */
void FUN_001d4a02(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d4a34 */
void FUN_001d4a34(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d4cd9 */
void FUN_001d4cd9(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d4dd3 */
void FUN_001d4dd3(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d4e37 */
void FUN_001d4e37(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> je 0x1d4ebf */
  /* cmp ebx, esi -> jne 0x1d4e4c */
  /* relift: test byte ptr [edi + 0x14], 1 -> jne 0x1d4e79 */
  /* test esi, esi -> jne 0x1d4e82 */
  /* test eax, eax -> je 0x1d4eba */
  FUN_001d4a02();

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x1d4ec6 */
void FUN_001d4ec6(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: cmp edx, dword ptr [ebx + 0x1c] -> jbe 0x1d4edf */
  FUN_001d4877();
  /* test eax, eax -> jne 0x1d4f2b */
  FUN_001d4a34();
  /* relift: cmp edx, dword ptr [ebp + 0x18] -> jae 0x1d4f5c */
  FUN_001d4cd9();
  /* cmp (int16_t)eax, 0x80 -> jae 0x1d4fb6 */
  /* test (char)ecx, 4 -> je 0x1d4fe7 */
  /* test (char)ecx, 2 -> je 0x1d4fd4 */
  /* cmp eax, 4 -> jbe 0x1d4fd4 */
  /* relift: test byte ptr [ebp - 2], 2 -> je 0x1d502f */
  /* cmp (int16_t)ecx, 0x80 -> jae 0x1d50de */
  /* relift: cmp dword ptr [edx], edx -> jne 0x1d50f4 */
  /* relift: cmp (int16_t)ecx, word ptr [edx - 8] -> jbe 0x1d50f4 */
  /* cmp eax, edx -> jne 0x1d50e8 */
  /* test (char)eax, 1 -> je 0x1d5194 */
  /* cmp (int16_t)ecx, 0x80 -> jae 0x1d5175 */
  /* relift: cmp dword ptr [edi], edi -> jne 0x1d525b */
  /* relift: cmp (int16_t)ecx, word ptr [edi - 8] -> jbe 0x1d525b */
  /* cmp eax, edi -> jne 0x1d517f */
  /* cmp (int16_t)eax, 0x80 -> jae 0x1d51c7 */
  /* test (char)ecx, 4 -> je 0x1d51f5 */
  /* test (char)ecx, 2 -> je 0x1d51e5 */
  /* cmp eax, 4 -> jbe 0x1d51e5 */
  /* cmp eax, 0xff00 -> ja 0x1d5273 */
  /* cmp (int16_t)ecx, 0x80 -> jb 0x1d5146 */
  /* relift: cmp (int16_t)ecx, word ptr [edi - 8] -> jbe 0x1d525b */
  /* cmp eax, edi -> jne 0x1d524f */
  FUN_001d4cd9();
  /* test dl, 8 -> je 0x1d52a9 */
  /* cmp ecx, esi -> jbe 0x1d52a9 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d52c4 */
void FUN_001d52c4(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d52f3 */
void FUN_001d52f3(void)
{
  int eax = 0;
  int ecx = 0;
  int ebp = 0;

  /* relift: cmp eax, dword ptr [ebp + 0x18] -> jne 0x1d5329 */
  /* cmp eax, ecx -> jb 0x1d5377 */
  /* relift: cmp eax, dword ptr [ebp + 0x20] -> jae 0x1d5367 */
  /* test eax, eax -> jge 0x1d536e */
  FUN_001d47e4();
  FUN_001d4cd9();

  (void)eax;
  (void)ecx;
  (void)ebp;
}

/* 0x1d5411 */
void FUN_001d5411(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: cmp esi, dword ptr [ecx + 0x30] -> ja 0x1d5478 */
  /* relift: cmp eax, dword ptr [ecx + 0x1c] -> ja 0x1d5478 */
  FUN_001d4877();
  /* test eax, eax -> jne 0x1d555b */
  /* relift: cmp byte ptr [ebp - 0xc], 0x40 -> jne 0x1d5478 */
  /* relift: cmp byte ptr [ebp + 0xf], 0x40 -> jb 0x1d5439 */
  /* relift: cmp byte ptr [ebp - 0xc], 0x40 -> je 0x1d558f */
  /* relift: test byte ptr [edi + 0x14], 2 -> je 0x1d558f */
  /* test eax, eax -> jge 0x1d54fb */
  /* relift: cmp dword ptr [ebp + 8], ecx -> je 0x1d54f3 */
  /* relift: cmp dword ptr [ebp + 8], ecx -> jae 0x1d54e0 */
  /* test eax, eax -> jl 0x1d54cd */
  /* test eax, eax -> jl 0x1d558f */
  /* test esi, esi -> jl 0x1d557c */
  FUN_001d52f3();
  /* test (char)eax, (char)eax -> jne 0x1d554f */
  /* test esi, esi -> jl 0x1d557c */
  FUN_001d4a34();
  FUN_001d4cd9();

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d5598 */
void FUN_001d5598(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [ebx + 0x584], 0 -> je 0x1d55bc */
  FUN_001d4cd9();
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x1d561d */
  /* cmp eax, esi -> jne 0x1d561d */
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0x1d5662 */
  /* relift: test byte ptr [esi + 5], 0x10 -> jne 0x1d5662 */
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> je 0x1d5831 */
  FUN_001d46a3();
  FUN_001d47c3();
  /* relift: cmp dword ptr [ebp - 0x20], 0 -> jl 0x1d5831 */
  FUN_001d47e4();
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x1d577b */
  /* cmp (int16_t)ecx, 0x80 -> jae 0x1d5737 */
  /* relift: cmp (int16_t)ecx, word ptr [eax - 8] -> jbe 0x1d5757 */
  /* cmp ecx, eax -> jne 0x1d5741 */
  /* test eax, eax -> je 0x1d5788 */
  /* cmp eax, ecx -> jb 0x1d57a1 */
  /* cmp eax, esi -> jae 0x1d57a1 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x1d5823 */
  /* cmp (int16_t)eax, 0x80 -> jae 0x1d57f5 */
  /* relift: cmp dword ptr [esi], esi -> jne 0x1d580b */
  /* relift: cmp (int16_t)eax, word ptr [esi - 8] -> jbe 0x1d580b */
  /* cmp ecx, esi -> jne 0x1d57ff */
  /* test eax, eax -> je 0x1d583b */
  FUN_001d4cd9();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)ebp;
}

/* 0x1d5842 */
void FUN_001d5842(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001dd5c8();
  /* cmp eax, esi -> je 0x1d58a5 */
  /* relift: cmp dword ptr [eax], 0x30 -> jne 0x1d587d */
  memmove((void *)(uintptr_t)eax, (void *)(uintptr_t)eax, 48);
  /* cmp ebx, esi -> jl 0x1d5bed */
  /* relift: test byte ptr [0x632a22], 0x20 -> je 0x1d58b2 */
  /* relift: cmp dword ptr [ebp - 0x48], esi -> jne 0x1d58bf */
  /* relift: cmp dword ptr [ebp - 0x44], esi -> jne 0x1d58cc */
  /* relift: cmp dword ptr [ebp - 0x40], esi -> jne 0x1d58d9 */
  /* relift: cmp dword ptr [ebp - 0x3c], esi -> jne 0x1d58e6 */
  /* relift: cmp dword ptr [ebp - 0x38], esi -> jne 0x1d58f2 */
  /* relift: cmp dword ptr [ebp - 0x34], esi -> je 0x1d5900 */
  /* relift: cmp dword ptr [ebp - 0x34], 0xff000 -> jbe 0x1d5907 */
  /* cmp eax, esi -> jne 0x1d5934 */
  /* cmp eax, esi -> jne 0x1d5925 */
  /* cmp edx, esi -> jne 0x1d5956 */
  /* relift: test byte ptr [ebp + 8], 1 -> jne 0x1d5986 */
  /* relift: cmp dword ptr [ebp + 0x18], esi -> je 0x1d5979 */
  /* relift: cmp dword ptr [ebp + 0x18], esi -> jne 0x1d5bed */
  /* cmp edi, esi -> je 0x1d5a64 */
  /* relift: cmp dword ptr [ebp - 0x28], esi -> je 0x1d59da */
  /* cmp ebx, esi -> je 0x1d5bed */
  /* cmp eax, esi -> je 0x1d5bed */
  /* cmp ebx, eax -> ja 0x1d5bed */
  /* relift: test byte ptr [ebp + 8], 2 -> jne 0x1d5bed */
  /* test eax, eax -> jl 0x1d5bed */
  /* relift: cmp edi, dword ptr [ebp + 0xc] -> jne 0x1d5bed */
  /* relift: cmp dword ptr [ebp - 0x64], 0x10000 -> je 0x1d5bed */
  /* relift: cmp dword ptr [ebp - 0x64], eax -> jne 0x1d5a50 */
  /* test eax, eax -> jl 0x1d5a55 */
  /* relift: cmp dword ptr [ebp - 0x64], 0x2000 -> jne 0x1d5a55 */
  /* relift: cmp dword ptr [ebp - 0x28], esi -> jne 0x1d5bed */
  /* test eax, eax -> jl 0x1d5bed */
  /* relift: cmp dword ptr [ebp + 0x14], esi -> jne 0x1d5a9a */
  /* relift: cmp dword ptr [ebp - 0x58], ebx -> jne 0x1d5ae5 */
  /* test eax, eax -> jge 0x1d5ae2 */
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> jne 0x1d5bed */
  /* relift: test byte ptr [0x632a21], 8 -> je 0x1d5b3a */
  /* cmp edi, -1 -> jne 0x1d5bc4 */
  FUN_001d52f3();
  /* test (char)eax, (char)eax -> jne 0x1d5bf1 */

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
