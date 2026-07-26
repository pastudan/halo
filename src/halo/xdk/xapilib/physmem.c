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

/* XapiSelectCachePartition (0x1d3a91) — XBE naked draft (batch 307). */
#if defined(__clang__)
static void * (*const b1d3a91_c1da290)(void *dest, const void *src, size_t size) = memmove;

__attribute__((naked, noinline))
void XapiSelectCachePartition(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x22c, %%esp\n\t"
      "movl 0x10118, %%eax\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $0x10\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "pushl $3\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0xc0100000\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, -0x2c(%%ebp)\n\t"
      "movl $0x40, -0x24(%%ebp)\n\t"
      "movl $0x2c1e50, -0x28(%%ebp)\n\t"
      "call *0x253160\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jl .LXapiSelectCachePartition_18\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x200\n\t"
      "leal -0x22c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl -0x4(%%ebp)\n\t"
      "movl $0x800, -0x18(%%ebp)\n\t"
      "movl %%edi, -0x14(%%ebp)\n\t"
      "call *0x253178\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jl .LXapiSelectCachePartition_17\n\t"
      "movl 0x25321c, %%eax\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "decl %%eax\n\t"
      "movl $0x97315286, %%edx\n\t"
      "cmpl %%edx, -0x22c(%%ebp)\n\t"
      "pushl $2\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl $0xaa550000, %%esi\n\t"
      "popl %%ebx\n\t"
      "jne .LXapiSelectCachePartition_1\n\t"
      "cmpl %%esi, -0x34(%%ebp)\n\t"
      "jne .LXapiSelectCachePartition_1\n\t"
      "cmpl %%ebx, -0x228(%%ebp)\n\t"
      "je .LXapiSelectCachePartition_2\n\t"
      ".LXapiSelectCachePartition_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $0x80, %%ecx\n\t"
      "leal -0x22c(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "movl %%edx, -0x22c(%%ebp)\n\t"
      "movl %%ebx, -0x228(%%ebp)\n\t"
      "movl %%esi, -0x34(%%ebp)\n\t"
      "xorl %%edi, %%edi\n\t"
      ".LXapiSelectCachePartition_2:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl $1, (%%esi)\n\t"
      "movl 0x25321c, %%eax\n\t"
      "movl (%%eax), %%eax\n\t"
      "cmpl $0x29, %%eax\n\t"
      "jbe .LXapiSelectCachePartition_3\n\t"
      "pushl $0x29\n\t"
      "popl %%eax\n\t"
      ".LXapiSelectCachePartition_3:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testl %%eax, %%eax\n\t"
      "jbe .LXapiSelectCachePartition_6\n\t"
      "leal -0x224(%%ebp), %%edx\n\t"
      ".LXapiSelectCachePartition_4:\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "cmpl (%%edx), %%ebx\n\t"
      "jne .LXapiSelectCachePartition_5\n\t"
      "cmpl $0, 0x8(%%edx)\n\t"
      "jne .LXapiSelectCachePartition_19\n\t"
      ".LXapiSelectCachePartition_5:\n\t"
      "incl %%ecx\n\t"
      "addl $0xc, %%edx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jb .LXapiSelectCachePartition_4\n\t"
      ".LXapiSelectCachePartition_6:\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      ".LXapiSelectCachePartition_7:\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "jbe .LXapiSelectCachePartition_13\n\t"
      ".LXapiSelectCachePartition_8:\n\t"
      "xorl %%edx, %%edx\n\t"
      "leal -0x220(%%ebp), %%ecx\n\t"
      ".LXapiSelectCachePartition_9:\n\t"
      "cmpl $0, 0x4(%%ecx)\n\t"
      "je .LXapiSelectCachePartition_10\n\t"
      "cmpl %%esi, (%%ecx)\n\t"
      "je .LXapiSelectCachePartition_11\n\t"
      ".LXapiSelectCachePartition_10:\n\t"
      "incl %%edx\n\t"
      "addl $0xc, %%ecx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jb .LXapiSelectCachePartition_9\n\t"
      ".LXapiSelectCachePartition_11:\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jne .LXapiSelectCachePartition_12\n\t"
      "leal 0x3(%%esi), %%edi\n\t"
      ".LXapiSelectCachePartition_12:\n\t"
      "incl %%esi\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jb .LXapiSelectCachePartition_8\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LXapiSelectCachePartition_14\n\t"
      ".LXapiSelectCachePartition_13:\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "movl -0x22c(%%ebp,%%ecx,4), %%edi\n\t"
      "addl $3, %%edi\n\t"
      ".LXapiSelectCachePartition_14:\n\t"
      "leal 0x3(%%eax), %%ecx\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "jb .LXapiSelectCachePartition_15\n\t"
      "leal 0x2(%%eax), %%edi\n\t"
      ".LXapiSelectCachePartition_15:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "decl %%eax\n\t"
      "negl %%esi\n\t"
      "sbbl %%esi, %%esi\n\t"
      "andl %%eax, %%esi\n\t"
      "cmpl $0, 0x8(%%ebp)\n\t"
      "movl %%edi, (%%ecx)\n\t"
      "jne .LXapiSelectCachePartition_16\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LXapiSelectCachePartition_16\n\t"
      "leal (%%ebx,%%ebx,2), %%eax\n\t"
      "shll $2, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x224(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x218(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1da290]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LXapiSelectCachePartition_16:\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "leal (%%esi,%%esi,2), %%eax\n\t"
      "leal -0x224(%%ebp,%%eax,4), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "addl $-3, %%edi\n\t"
      "cmpl %%ecx, 0x8(%%ebp)\n\t"
      "movl %%edi, 0x4(%%eax)\n\t"
      "sete %%dl\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x200\n\t"
      "leal -0x22c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl -0x4(%%ebp)\n\t"
      "call *0x25317c\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LXapiSelectCachePartition_17:\n\t"
      "pushl -0x4(%%ebp)\n\t"
      "call *0x253090\n\t"
      ".LXapiSelectCachePartition_18:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      ".LXapiSelectCachePartition_19:\n\t"
      "leal (%%ecx,%%ecx,2), %%edx\n\t"
      "movl -0x220(%%ebp,%%edx,4), %%edi\n\t"
      "addl $3, %%edi\n\t"
      "movl %%ecx, %%ebx\n\t"
      "movl $0, (%%esi)\n\t"
      "jne .LXapiSelectCachePartition_14\n\t"
      "jmp .LXapiSelectCachePartition_7\n\t"
      :
      : [c1da290] "m"(b1d3a91_c1da290)
      : "memory");
}
#else
#error "XapiSelectCachePartition: clang naked draft required"
#endif


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

/* FUN_001d46a3 (0x1d46a3) — XBE naked draft (batch 304). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_001d46a3(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "leal 0x4c(%%eax), %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, (%%ecx)\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_001d46a3_8\n\t"
      "movl 0x48(%%eax), %%ecx\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "je .LFUN_001d46a3_3\n\t"
      "movl 0x8(%%ecx), %%eax\n\t"
      "cmpl 0x4(%%ecx), %%eax\n\t"
      "je .LFUN_001d46a3_3\n\t"
      "pushl $4\n\t"
      "movl $0x1000, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%edx\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "addl %%ecx, %%edx\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "call *0x253148\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001d46a3_2\n\t"
      ".LFUN_001d46a3_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001d46a3_9\n\t"
      ".LFUN_001d46a3_2:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "addl %%ecx, 0x8(%%eax)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "jmp .LFUN_001d46a3_5\n\t"
      ".LFUN_001d46a3_3:\n\t"
      "movl 0x253148, %%edi\n\t"
      "pushl $4\n\t"
      "pushl $0x2000\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0x10000, -0x8(%%ebp)\n\t"
      "movl %%ebx, 0x8(%%ebp)\n\t"
      "call *%%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d46a3_1\n\t"
      "pushl $4\n\t"
      "movl $0x1000, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001d46a3_4\n\t"
      "pushl $0x8000\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x25314c\n\t"
      "jmp .LFUN_001d46a3_1\n\t"
      ".LFUN_001d46a3_4:\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "movl 0x48(%%eax), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x48(%%eax)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal 0x10(%%eax), %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      ".LFUN_001d46a3_5:\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "addl $0x4c, %%eax\n\t"
      "jmp .LFUN_001d46a3_7\n\t"
      ".LFUN_001d46a3_6:\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl %%edx, %%eax\n\t"
      "addl $0x10, %%edx\n\t"
      ".LFUN_001d46a3_7:\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jb .LFUN_001d46a3_6\n\t"
      "movl %%ebx, (%%eax)\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "addl $0x4c, %%ecx\n\t"
      ".LFUN_001d46a3_8:\n\t"
      "movl (%%ecx), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      ".LFUN_001d46a3_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_001d46a3: clang naked draft required"
#endif


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

/* FUN_001d4877 (0x1d4877) — XBE naked draft (batch 301). */
#if defined(__clang__)
static void (*const b1d4877_c1d47c3)(void) = FUN_001d47c3;

__attribute__((naked, noinline))
void FUN_001d4877(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "leal 0x38(%%edi), %%eax\n\t"
      "movl (%%eax), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "je .LFUN_001d4877_3\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      ".LFUN_001d4877_1:\n\t"
      "cmpl %%eax, 0x8(%%esi)\n\t"
      "jb .LFUN_001d4877_2\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_001d4877_5\n\t"
      "cmpl %%ecx, 0x4(%%esi)\n\t"
      "je .LFUN_001d4877_5\n\t"
      ".LFUN_001d4877_2:\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "movl (%%esi), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_001d4877_1\n\t"
      ".LFUN_001d4877_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d4877_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      ".LFUN_001d4877_5:\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "movl 0x584(%%ecx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d4877_6\n\t"
      "pushl %%ebx\n\t"
      "leal 0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "call *%%eax\n\t"
      "jmp .LFUN_001d4877_7\n\t"
      ".LFUN_001d4877_6:\n\t"
      "pushl $4\n\t"
      "pushl $0x1000\n\t"
      "pushl %%ebx\n\t"
      "pushl $0\n\t"
      "leal 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253148\n\t"
      ".LFUN_001d4877_7:\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d4877_3\n\t"
      "movl (%%ebx), %%eax\n\t"
      "shrl $0xc, %%eax\n\t"
      "subl %%eax, 0x30(%%edi)\n\t"
      "movl 0x1c(%%edi), %%eax\n\t"
      "cmpl 0x8(%%esi), %%eax\n\t"
      "jne .LFUN_001d4877_8\n\t"
      "andl $0, 0x1c(%%edi)\n\t"
      ".LFUN_001d4877_8:\n\t"
      "movl 0x40(%%edi), %%ebx\n\t"
      "testb $0x10, 0x5(%%ebx)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "je .LFUN_001d4877_9\n\t"
      "movzwl (%%ebx), %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "addl %%ebx, %%ecx\n\t"
      "cmpl 0x4(%%esi), %%ecx\n\t"
      "je .LFUN_001d4877_14\n\t"
      ".LFUN_001d4877_9:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_001d4877_10\n\t"
      "movl 0x28(%%edi), %%ebx\n\t"
      "jmp .LFUN_001d4877_11\n\t"
      ".LFUN_001d4877_10:\n\t"
      "movl 0x8(%%ecx), %%ebx\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "addl 0x4(%%ecx), %%ebx\n\t"
      ".LFUN_001d4877_11:\n\t"
      "testb $0x10, 0x5(%%ebx)\n\t"
      "jne .LFUN_001d4877_14\n\t"
      "movl 0x2c(%%edi), %%ecx\n\t"
      ".LFUN_001d4877_12:\n\t"
      "movzwl (%%ebx), %%edx\n\t"
      "shll $4, %%edx\n\t"
      "movl %%ebx, 0x14(%%ebp)\n\t"
      "addl %%edx, %%ebx\n\t"
      "cmpl %%ecx, %%ebx\n\t"
      "jae .LFUN_001d4877_13\n\t"
      "cmpw $0, (%%ebx)\n\t"
      "je .LFUN_001d4877_13\n\t"
      "testb $0x10, 0x5(%%ebx)\n\t"
      "je .LFUN_001d4877_12\n\t"
      "jmp .LFUN_001d4877_14\n\t"
      ".LFUN_001d4877_13:\n\t"
      "cmpl 0xc(%%ebp), %%ebx\n\t"
      "jne .LFUN_001d4877_3\n\t"
      "movl 0x14(%%ebp), %%ebx\n\t"
      ".LFUN_001d4877_14:\n\t"
      "andb $0xef, 0x5(%%ebx)\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "addl %%edx, 0x4(%%esi)\n\t"
      "movl (%%ecx), %%edx\n\t"
      "subl %%edx, 0x8(%%esi)\n\t"
      "jne .LFUN_001d4877_17\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "cmpl 0x2c(%%edi), %%ecx\n\t"
      "jne .LFUN_001d4877_15\n\t"
      "movb $0x10, 0x5(%%eax)\n\t"
      "jmp .LFUN_001d4877_16\n\t"
      ".LFUN_001d4877_15:\n\t"
      "andb $0, 0x5(%%eax)\n\t"
      "movl 0x28(%%edi), %%eax\n\t"
      ".LFUN_001d4877_16:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x40(%%edi)\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "call *%[c1d47c3]\n\t"
      "decl 0x34(%%edi)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "jmp .LFUN_001d4877_18\n\t"
      ".LFUN_001d4877_17:\n\t"
      "movb $0x10, 0x5(%%eax)\n\t"
      "movl %%eax, 0x40(%%edi)\n\t"
      ".LFUN_001d4877_18:\n\t"
      "movb 0x4(%%ebx), %%dl\n\t"
      "movb %%dl, 0x4(%%eax)\n\t"
      "movl (%%ecx), %%ecx\n\t"
      "shrl $4, %%ecx\n\t"
      "testb $0x10, 0x5(%%eax)\n\t"
      "movw %%cx, (%%eax)\n\t"
      "movw (%%ebx), %%cx\n\t"
      "movw %%cx, 0x2(%%eax)\n\t"
      "jne .LFUN_001d4877_19\n\t"
      "movw (%%eax), %%cx\n\t"
      "movzwl %%cx, %%edx\n\t"
      "shll $4, %%edx\n\t"
      "movw %%cx, 0x2(%%edx,%%eax,1)\n\t"
      ".LFUN_001d4877_19:\n\t"
      "cmpl $0, 0x1c(%%edi)\n\t"
      "jne .LFUN_001d4877_4\n\t"
      "movl 0x38(%%edi), %%ecx\n\t"
      "jmp .LFUN_001d4877_22\n\t"
      ".LFUN_001d4877_20:\n\t"
      "movl 0x8(%%ecx), %%edx\n\t"
      "cmpl 0x1c(%%edi), %%edx\n\t"
      "jb .LFUN_001d4877_21\n\t"
      "movl %%edx, 0x1c(%%edi)\n\t"
      ".LFUN_001d4877_21:\n\t"
      "movl (%%ecx), %%ecx\n\t"
      ".LFUN_001d4877_22:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_001d4877_20\n\t"
      "jmp .LFUN_001d4877_4\n\t"
      :
      : [c1d47c3] "m"(b1d4877_c1d47c3)
      : "memory");
}
#else
#error "FUN_001d4877: clang naked draft required"
#endif


/* 0x1d4a02 */
void FUN_001d4a02(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_001d4a34 (0x1d4a34) — XBE naked draft (batch 298). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_001d4a34(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movzwl 0x2(%%edi), %%eax\n\t"
      "shll $4, %%eax\n\t"
      "movl %%edi, %%esi\n\t"
      "subl %%eax, %%esi\n\t"
      "cmpl %%edi, %%esi\n\t"
      "je .LFUN_001d4a34_9\n\t"
      "testb $1, 0x5(%%esi)\n\t"
      "jne .LFUN_001d4a34_9\n\t"
      "movzwl (%%esi), %%ecx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "addl (%%eax), %%ecx\n\t"
      "cmpl $0xff00, %%ecx\n\t"
      "ja .LFUN_001d4a34_10\n\t"
      "cmpb $0, 0x14(%%ebp)\n\t"
      "je .LFUN_001d4a34_4\n\t"
      "movl 0x8(%%edi), %%ecx\n\t"
      "movl 0xc(%%edi), %%edx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "jne .LFUN_001d4a34_1\n\t"
      "movw (%%edi), %%cx\n\t"
      "cmpw $0x80, %%cx\n\t"
      "jae .LFUN_001d4a34_1\n\t"
      "movzwl %%cx, %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "andl $7, %%ecx\n\t"
      "movb $1, %%dl\n\t"
      "shrl $3, %%eax\n\t"
      "shlb %%cl, %%dl\n\t"
      "leal 0x160(%%eax,%%ebx,1), %%eax\n\t"
      "xorb %%dl, (%%eax)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      ".LFUN_001d4a34_1:\n\t"
      "movb 0x5(%%edi), %%cl\n\t"
      "testb $4, %%cl\n\t"
      "je .LFUN_001d4a34_3\n\t"
      "movzwl (%%edi), %%eax\n\t"
      "shll $4, %%eax\n\t"
      "subl $0x18, %%eax\n\t"
      "testb $2, %%cl\n\t"
      "je .LFUN_001d4a34_2\n\t"
      "cmpl $4, %%eax\n\t"
      "jbe .LFUN_001d4a34_2\n\t"
      "subl $4, %%eax\n\t"
      ".LFUN_001d4a34_2:\n\t"
      "pushl $0xfeeefeee\n\t"
      "pushl %%eax\n\t"
      "leal 0x18(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253248\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      ".LFUN_001d4a34_3:\n\t"
      "movzwl (%%edi), %%ecx\n\t"
      "subl %%ecx, 0x30(%%ebx)\n\t"
      "andb $0, 0x14(%%ebp)\n\t"
      ".LFUN_001d4a34_4:\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "jne .LFUN_001d4a34_5\n\t"
      "movw (%%esi), %%cx\n\t"
      "cmpw $0x80, %%cx\n\t"
      "jae .LFUN_001d4a34_5\n\t"
      "movzwl %%cx, %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "andl $7, %%ecx\n\t"
      "movb $1, %%dl\n\t"
      "shrl $3, %%eax\n\t"
      "shlb %%cl, %%dl\n\t"
      "leal 0x160(%%eax,%%ebx,1), %%eax\n\t"
      "xorb %%dl, (%%eax)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      ".LFUN_001d4a34_5:\n\t"
      "movb 0x5(%%esi), %%cl\n\t"
      "testb $4, %%cl\n\t"
      "je .LFUN_001d4a34_7\n\t"
      "movzwl (%%esi), %%eax\n\t"
      "shll $4, %%eax\n\t"
      "subl $0x18, %%eax\n\t"
      "testb $2, %%cl\n\t"
      "je .LFUN_001d4a34_6\n\t"
      "cmpl $4, %%eax\n\t"
      "jbe .LFUN_001d4a34_6\n\t"
      "subl $4, %%eax\n\t"
      ".LFUN_001d4a34_6:\n\t"
      "pushl $0xfeeefeee\n\t"
      "pushl %%eax\n\t"
      "leal 0x18(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253248\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      ".LFUN_001d4a34_7:\n\t"
      "movb 0x5(%%edi), %%cl\n\t"
      "andb $0x10, %%cl\n\t"
      "testb $0x10, %%cl\n\t"
      "movb %%cl, 0x5(%%esi)\n\t"
      "je .LFUN_001d4a34_8\n\t"
      "movzbl 0x4(%%esi), %%ecx\n\t"
      "movl 0x60(%%ebx,%%ecx,4), %%ecx\n\t"
      "movl %%esi, 0x40(%%ecx)\n\t"
      ".LFUN_001d4a34_8:\n\t"
      "movzwl (%%esi), %%ecx\n\t"
      "addl %%ecx, (%%eax)\n\t"
      "movzwl (%%esi), %%ecx\n\t"
      "subl %%ecx, 0x30(%%ebx)\n\t"
      "testb $0x10, 0x5(%%esi)\n\t"
      "movw (%%eax), %%cx\n\t"
      "movl %%esi, %%edi\n\t"
      "movw %%cx, (%%esi)\n\t"
      "jne .LFUN_001d4a34_10\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movw (%%eax), %%dx\n\t"
      "shll $4, %%ecx\n\t"
      "movw %%dx, 0x2(%%ecx,%%esi,1)\n\t"
      "jmp .LFUN_001d4a34_10\n\t"
      ".LFUN_001d4a34_9:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      ".LFUN_001d4a34_10:\n\t"
      "testb $0x10, 0x5(%%edi)\n\t"
      "jne .LFUN_001d4a34_19\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, %%esi\n\t"
      "shll $4, %%esi\n\t"
      "addl %%edi, %%esi\n\t"
      "testb $1, 0x5(%%esi)\n\t"
      "jne .LFUN_001d4a34_19\n\t"
      "movzwl (%%esi), %%edx\n\t"
      "addl %%ecx, %%edx\n\t"
      "cmpl $0xff00, %%edx\n\t"
      "ja .LFUN_001d4a34_19\n\t"
      "cmpb $0, 0x14(%%ebp)\n\t"
      "je .LFUN_001d4a34_14\n\t"
      "movl 0x8(%%edi), %%ecx\n\t"
      "movl 0xc(%%edi), %%edx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "jne .LFUN_001d4a34_11\n\t"
      "movw (%%edi), %%cx\n\t"
      "cmpw $0x80, %%cx\n\t"
      "jae .LFUN_001d4a34_11\n\t"
      "movzwl %%cx, %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "andl $7, %%ecx\n\t"
      "movb $1, %%dl\n\t"
      "shrl $3, %%eax\n\t"
      "shlb %%cl, %%dl\n\t"
      "leal 0x160(%%eax,%%ebx,1), %%eax\n\t"
      "xorb %%dl, (%%eax)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      ".LFUN_001d4a34_11:\n\t"
      "movb 0x5(%%edi), %%cl\n\t"
      "testb $4, %%cl\n\t"
      "je .LFUN_001d4a34_13\n\t"
      "movzwl (%%edi), %%eax\n\t"
      "shll $4, %%eax\n\t"
      "subl $0x18, %%eax\n\t"
      "testb $2, %%cl\n\t"
      "je .LFUN_001d4a34_12\n\t"
      "cmpl $4, %%eax\n\t"
      "jbe .LFUN_001d4a34_12\n\t"
      "subl $4, %%eax\n\t"
      ".LFUN_001d4a34_12:\n\t"
      "pushl $0xfeeefeee\n\t"
      "pushl %%eax\n\t"
      "leal 0x18(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253248\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      ".LFUN_001d4a34_13:\n\t"
      "movzwl (%%edi), %%ecx\n\t"
      "subl %%ecx, 0x30(%%ebx)\n\t"
      ".LFUN_001d4a34_14:\n\t"
      "movb 0x5(%%esi), %%cl\n\t"
      "andb $0x10, %%cl\n\t"
      "testb $0x10, %%cl\n\t"
      "movb %%cl, 0x5(%%edi)\n\t"
      "je .LFUN_001d4a34_15\n\t"
      "movzbl 0x4(%%edi), %%ecx\n\t"
      "movl 0x60(%%ebx,%%ecx,4), %%ecx\n\t"
      "movl %%edi, 0x40(%%ecx)\n\t"
      ".LFUN_001d4a34_15:\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "jne .LFUN_001d4a34_16\n\t"
      "movw (%%esi), %%cx\n\t"
      "cmpw $0x80, %%cx\n\t"
      "jae .LFUN_001d4a34_16\n\t"
      "movzwl %%cx, %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "andl $7, %%ecx\n\t"
      "movb $1, %%dl\n\t"
      "shrl $3, %%eax\n\t"
      "shlb %%cl, %%dl\n\t"
      "leal 0x160(%%eax,%%ebx,1), %%eax\n\t"
      "xorb %%dl, (%%eax)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      ".LFUN_001d4a34_16:\n\t"
      "movb 0x5(%%esi), %%cl\n\t"
      "testb $4, %%cl\n\t"
      "je .LFUN_001d4a34_18\n\t"
      "movzwl (%%esi), %%eax\n\t"
      "shll $4, %%eax\n\t"
      "subl $0x18, %%eax\n\t"
      "testb $2, %%cl\n\t"
      "je .LFUN_001d4a34_17\n\t"
      "cmpl $4, %%eax\n\t"
      "jbe .LFUN_001d4a34_17\n\t"
      "subl $4, %%eax\n\t"
      ".LFUN_001d4a34_17:\n\t"
      "pushl $0xfeeefeee\n\t"
      "pushl %%eax\n\t"
      "leal 0x18(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253248\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      ".LFUN_001d4a34_18:\n\t"
      "movzwl (%%esi), %%ecx\n\t"
      "addl %%ecx, (%%eax)\n\t"
      "movzwl (%%esi), %%ecx\n\t"
      "subl %%ecx, 0x30(%%ebx)\n\t"
      "testb $0x10, 0x5(%%edi)\n\t"
      "movw (%%eax), %%cx\n\t"
      "movw %%cx, (%%edi)\n\t"
      "jne .LFUN_001d4a34_19\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movw (%%eax), %%ax\n\t"
      "shll $4, %%ecx\n\t"
      "movw %%ax, 0x2(%%ecx,%%edi,1)\n\t"
      ".LFUN_001d4a34_19:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_001d4a34: clang naked draft required"
#endif


/* FUN_001d4cd9 (0x1d4cd9) — XBE naked draft (batch 307). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_001d4cd9(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movb 0x4(%%eax), %%dl\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movw 0x2(%%eax), %%si\n\t"
      "movzbl %%dl, %%ecx\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl 0x60(%%edi,%%ecx,4), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movb 0x5(%%eax), %%cl\n\t"
      "movb %%cl, 0xf(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "addl %%ecx, 0x30(%%edi)\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movb %%dl, -0x1(%%ebp)\n\t"
      "je .LFUN_001d4cd9_10\n\t"
      "jmp .LFUN_001d4cd9_2\n\t"
      ".LFUN_001d4cd9_1:\n\t"
      "movb -0x1(%%ebp), %%dl\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      ".LFUN_001d4cd9_2:\n\t"
      "cmpl $0xff00, %%ecx\n\t"
      "jbe .LFUN_001d4cd9_4\n\t"
      "cmpl $0xff01, %%ecx\n\t"
      "movl $0xff00, %%ebx\n\t"
      "jne .LFUN_001d4cd9_3\n\t"
      "addl $-0x10, %%ebx\n\t"
      ".LFUN_001d4cd9_3:\n\t"
      "andb $0, 0x5(%%eax)\n\t"
      "jmp .LFUN_001d4cd9_5\n\t"
      ".LFUN_001d4cd9_4:\n\t"
      "movl %%ecx, %%ebx\n\t"
      "movb 0xf(%%ebp), %%cl\n\t"
      "movb %%cl, 0x5(%%eax)\n\t"
      ".LFUN_001d4cd9_5:\n\t"
      "andb $0xf8, 0x5(%%eax)\n\t"
      "cmpw $0x80, %%bx\n\t"
      "movw %%si, 0x2(%%eax)\n\t"
      "movb %%dl, 0x4(%%eax)\n\t"
      "movw %%bx, (%%eax)\n\t"
      "jae .LFUN_001d4cd9_6\n\t"
      "movzwl %%bx, %%ecx\n\t"
      "leal 0x180(%%edi,%%ecx,8), %%esi\n\t"
      "cmpl %%esi, (%%esi)\n\t"
      "jne .LFUN_001d4cd9_9\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $3, %%edx\n\t"
      "leal 0x160(%%edx,%%edi,1), %%edx\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "andl $7, %%ecx\n\t"
      "movb $1, %%dl\n\t"
      "shlb %%cl, %%dl\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "orb %%dl, (%%ecx)\n\t"
      "jmp .LFUN_001d4cd9_9\n\t"
      ".LFUN_001d4cd9_6:\n\t"
      "leal 0x180(%%edi), %%ecx\n\t"
      "movl (%%ecx), %%esi\n\t"
      "jmp .LFUN_001d4cd9_8\n\t"
      ".LFUN_001d4cd9_7:\n\t"
      "cmpw -0x8(%%esi), %%bx\n\t"
      "jbe .LFUN_001d4cd9_9\n\t"
      "movl (%%esi), %%esi\n\t"
      ".LFUN_001d4cd9_8:\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "jne .LFUN_001d4cd9_7\n\t"
      ".LFUN_001d4cd9_9:\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "leal 0x8(%%eax), %%ecx\n\t"
      "movl %%esi, (%%ecx)\n\t"
      "movl %%edx, 0xc(%%eax)\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      "movzwl %%bx, %%ecx\n\t"
      "subl %%ecx, 0x10(%%ebp)\n\t"
      "shll $4, %%ecx\n\t"
      "addl %%ecx, %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "cmpl 0x2c(%%ecx), %%eax\n\t"
      "movl %%ebx, %%esi\n\t"
      "jae .LFUN_001d4cd9_11\n\t"
      "cmpl $0, 0x10(%%ebp)\n\t"
      "jne .LFUN_001d4cd9_1\n\t"
      ".LFUN_001d4cd9_10:\n\t"
      "testb $0x10, 0xf(%%ebp)\n\t"
      "jne .LFUN_001d4cd9_11\n\t"
      "movw %%si, 0x2(%%eax)\n\t"
      ".LFUN_001d4cd9_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_001d4cd9: clang naked draft required"
#endif


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

/* FUN_001d4ec6 (0x1d4ec6) — XBE naked draft (batch 297). */
#if defined(__clang__)
static void (*const b1d4ec6_c1d4877)(void) = FUN_001d4877;
static void (*const b1d4ec6_c1d4a34)(void) = FUN_001d4a34;
static void (*const b1d4ec6_c1d4cd9)(void) = FUN_001d4cd9;

__attribute__((naked, noinline))
void FUN_001d4ec6(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "cmpl 0x1c(%%ebx), %%edx\n\t"
      "jbe .LFUN_001d4ec6_1\n\t"
      "xorb %%al, %%al\n\t"
      "jmp .LFUN_001d4ec6_37\n\t"
      ".LFUN_001d4ec6_1:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "movzwl (%%edi), %%eax\n\t"
      "movb 0x5(%%edi), %%cl\n\t"
      "movl %%eax, %%esi\n\t"
      "shll $4, %%esi\n\t"
      "addl %%edi, %%esi\n\t"
      "testb $0x10, %%cl\n\t"
      "movb %%cl, -0x2(%%ebp)\n\t"
      "je .LFUN_001d4ec6_5\n\t"
      "subl %%eax, %%edx\n\t"
      "pushl %%esi\n\t"
      "shll $4, %%edx\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movzbl 0x4(%%edi), %%eax\n\t"
      "addl $0xfff, %%edx\n\t"
      "andl $0xfffff000, %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "pushl 0x60(%%ebx,%%eax,4)\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d4877]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001d4ec6_3\n\t"
      ".LFUN_001d4ec6_2:\n\t"
      "xorb %%al, %%al\n\t"
      "jmp .LFUN_001d4ec6_36\n\t"
      ".LFUN_001d4ec6_3:\n\t"
      "shrl $4, -0x8(%%ebp)\n\t"
      "pushl $0\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d4a34]\n\t"
      "movzwl (%%edi), %%edx\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movb 0x5(%%eax), %%cl\n\t"
      "addl %%esi, %%edx\n\t"
      "cmpl 0x18(%%ebp), %%edx\n\t"
      "jae .LFUN_001d4ec6_4\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d4cd9]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl %%eax, 0x30(%%ebx)\n\t"
      "jmp .LFUN_001d4ec6_2\n\t"
      ".LFUN_001d4ec6_4:\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "jmp .LFUN_001d4ec6_9\n\t"
      ".LFUN_001d4ec6_5:\n\t"
      "movb 0x5(%%esi), %%cl\n\t"
      "testb $1, %%cl\n\t"
      "movb %%cl, 0xb(%%ebp)\n\t"
      "jne .LFUN_001d4ec6_2\n\t"
      "movzwl (%%esi), %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jb .LFUN_001d4ec6_2\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "jne .LFUN_001d4ec6_6\n\t"
      "movw (%%esi), %%ax\n\t"
      "cmpw $0x80, %%ax\n\t"
      "jae .LFUN_001d4ec6_6\n\t"
      "movzwl %%ax, %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "shrl $3, %%eax\n\t"
      "leal 0x160(%%eax,%%ebx,1), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "andl $7, %%ecx\n\t"
      "movb $1, %%al\n\t"
      "shlb %%cl, %%al\n\t"
      "movb %%al, %%cl\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "xorb %%cl, (%%eax)\n\t"
      ".LFUN_001d4ec6_6:\n\t"
      "movb 0x5(%%esi), %%cl\n\t"
      "testb $4, %%cl\n\t"
      "je .LFUN_001d4ec6_8\n\t"
      "movzwl (%%esi), %%eax\n\t"
      "shll $4, %%eax\n\t"
      "subl $0x18, %%eax\n\t"
      "testb $2, %%cl\n\t"
      "je .LFUN_001d4ec6_7\n\t"
      "cmpl $4, %%eax\n\t"
      "jbe .LFUN_001d4ec6_7\n\t"
      "subl $4, %%eax\n\t"
      ".LFUN_001d4ec6_7:\n\t"
      "pushl $0xfeeefeee\n\t"
      "pushl %%eax\n\t"
      "leal 0x18(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253248\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      ".LFUN_001d4ec6_8:\n\t"
      "movzwl (%%esi), %%eax\n\t"
      "subl %%eax, 0x30(%%ebx)\n\t"
      "movb 0xb(%%ebp), %%cl\n\t"
      ".LFUN_001d4ec6_9:\n\t"
      "movzwl (%%edi), %%eax\n\t"
      "movzbl 0x6(%%edi), %%esi\n\t"
      "subl %%edx, -0x8(%%ebp)\n\t"
      "shll $4, %%eax\n\t"
      "subl %%esi, %%eax\n\t"
      "cmpl $2, -0x8(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "ja .LFUN_001d4ec6_10\n\t"
      "addl -0x8(%%ebp), %%edx\n\t"
      "andl $0, -0x8(%%ebp)\n\t"
      ".LFUN_001d4ec6_10:\n\t"
      "testb $2, -0x2(%%ebp)\n\t"
      "je .LFUN_001d4ec6_11\n\t"
      "movzwl (%%edi), %%eax\n\t"
      "shll $4, %%eax\n\t"
      "leal -0x10(%%eax,%%edi,1), %%esi\n\t"
      "movl %%edx, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "leal -0x10(%%eax,%%edi,1), %%edi\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      ".LFUN_001d4ec6_11:\n\t"
      "movb %%dl, %%al\n\t"
      "shlb $4, %%al\n\t"
      "subb 0x14(%%ebp), %%al\n\t"
      "cmpl $0, -0x8(%%ebp)\n\t"
      "movw %%dx, (%%edi)\n\t"
      "movb %%al, 0x6(%%edi)\n\t"
      "jne .LFUN_001d4ec6_13\n\t"
      "andb $0x10, %%cl\n\t"
      "orb %%cl, 0x5(%%edi)\n\t"
      "testb %%cl, %%cl\n\t"
      "movb %%cl, 0x1b(%%ebp)\n\t"
      "jne .LFUN_001d4ec6_12\n\t"
      "movzwl %%dx, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "movw %%dx, 0x2(%%eax,%%edi,1)\n\t"
      "jmp .LFUN_001d4ec6_34\n\t"
      ".LFUN_001d4ec6_12:\n\t"
      "movzbl 0x4(%%edi), %%eax\n\t"
      "movl 0x60(%%ebx,%%eax,4), %%eax\n\t"
      "movl %%edi, 0x40(%%eax)\n\t"
      "jmp .LFUN_001d4ec6_34\n\t"
      ".LFUN_001d4ec6_13:\n\t"
      "movl %%edx, %%esi\n\t"
      "shll $4, %%esi\n\t"
      "addl %%edi, %%esi\n\t"
      "testb $0x10, %%cl\n\t"
      "movw %%dx, 0x2(%%esi)\n\t"
      "movb 0x4(%%edi), %%al\n\t"
      "movb %%al, 0x4(%%esi)\n\t"
      "je .LFUN_001d4ec6_18\n\t"
      "movzbl %%al, %%eax\n\t"
      "movl 0x60(%%ebx,%%eax,4), %%eax\n\t"
      "movl %%esi, 0x40(%%eax)\n\t"
      "movb %%cl, 0x5(%%esi)\n\t"
      "movw -0x8(%%ebp), %%ax\n\t"
      "andb $0xf8, %%cl\n\t"
      "movw %%ax, (%%esi)\n\t"
      "movb %%cl, 0x5(%%esi)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "cmpw $0x80, %%cx\n\t"
      "jae .LFUN_001d4ec6_14\n\t"
      "movzwl %%cx, %%eax\n\t"
      "leal 0x180(%%ebx,%%eax,8), %%edx\n\t"
      "cmpl %%edx, (%%edx)\n\t"
      "jne .LFUN_001d4ec6_17\n\t"
      "movzwl (%%esi), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "shrl $3, %%eax\n\t"
      "leal 0x160(%%eax,%%ebx,1), %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "andl $7, %%ecx\n\t"
      "movb $1, %%al\n\t"
      "shlb %%cl, %%al\n\t"
      "movb %%al, %%cl\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "orb %%cl, (%%eax)\n\t"
      "jmp .LFUN_001d4ec6_17\n\t"
      ".LFUN_001d4ec6_14:\n\t"
      "leal 0x180(%%ebx), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "jmp .LFUN_001d4ec6_16\n\t"
      ".LFUN_001d4ec6_15:\n\t"
      "cmpw -0x8(%%edx), %%cx\n\t"
      "jbe .LFUN_001d4ec6_17\n\t"
      "movl (%%edx), %%edx\n\t"
      ".LFUN_001d4ec6_16:\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jne .LFUN_001d4ec6_15\n\t"
      ".LFUN_001d4ec6_17:\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "leal 0x8(%%esi), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl %%ecx, 0xc(%%esi)\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl %%eax, 0x30(%%ebx)\n\t"
      "jmp .LFUN_001d4ec6_34\n\t"
      ".LFUN_001d4ec6_18:\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "shll $4, %%edi\n\t"
      "addl %%esi, %%edi\n\t"
      "movb 0x5(%%edi), %%al\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_001d4ec6_23\n\t"
      "andb $0xef, %%cl\n\t"
      "movb %%cl, 0x5(%%esi)\n\t"
      "movw -0x8(%%ebp), %%ax\n\t"
      "movw %%ax, (%%esi)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "movw %%ax, 0x2(%%ecx,%%esi,1)\n\t"
      "andb $0xf8, 0x5(%%esi)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "cmpw $0x80, %%cx\n\t"
      "jae .LFUN_001d4ec6_20\n\t"
      ".LFUN_001d4ec6_19:\n\t"
      "movzwl %%cx, %%eax\n\t"
      "leal 0x180(%%ebx,%%eax,8), %%edi\n\t"
      "cmpl %%edi, (%%edi)\n\t"
      "jne .LFUN_001d4ec6_31\n\t"
      "movzwl (%%esi), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "andl $7, %%ecx\n\t"
      "movb $1, %%dl\n\t"
      "shrl $3, %%eax\n\t"
      "shlb %%cl, %%dl\n\t"
      "leal 0x160(%%eax,%%ebx,1), %%eax\n\t"
      "orb %%dl, (%%eax)\n\t"
      "jmp .LFUN_001d4ec6_31\n\t"
      ".LFUN_001d4ec6_20:\n\t"
      "leal 0x180(%%ebx), %%eax\n\t"
      "movl (%%eax), %%edi\n\t"
      "jmp .LFUN_001d4ec6_22\n\t"
      ".LFUN_001d4ec6_21:\n\t"
      "cmpw -0x8(%%edi), %%cx\n\t"
      "jbe .LFUN_001d4ec6_31\n\t"
      "movl (%%edi), %%edi\n\t"
      ".LFUN_001d4ec6_22:\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jne .LFUN_001d4ec6_21\n\t"
      "jmp .LFUN_001d4ec6_31\n\t"
      ".LFUN_001d4ec6_23:\n\t"
      "movl 0xc(%%edi), %%ecx\n\t"
      "movb %%al, 0xb(%%ebp)\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "jne .LFUN_001d4ec6_24\n\t"
      "movw (%%edi), %%ax\n\t"
      "cmpw $0x80, %%ax\n\t"
      "jae .LFUN_001d4ec6_24\n\t"
      "movzwl %%ax, %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "andl $7, %%ecx\n\t"
      "movb $1, %%dl\n\t"
      "shrl $3, %%eax\n\t"
      "shlb %%cl, %%dl\n\t"
      "leal 0x160(%%eax,%%ebx,1), %%eax\n\t"
      "xorb %%dl, (%%eax)\n\t"
      ".LFUN_001d4ec6_24:\n\t"
      "movb 0x5(%%edi), %%cl\n\t"
      "testb $4, %%cl\n\t"
      "je .LFUN_001d4ec6_26\n\t"
      "movzwl (%%edi), %%eax\n\t"
      "shll $4, %%eax\n\t"
      "subl $0x18, %%eax\n\t"
      "testb $2, %%cl\n\t"
      "je .LFUN_001d4ec6_25\n\t"
      "cmpl $4, %%eax\n\t"
      "jbe .LFUN_001d4ec6_25\n\t"
      "subl $4, %%eax\n\t"
      ".LFUN_001d4ec6_25:\n\t"
      "pushl $0xfeeefeee\n\t"
      "pushl %%eax\n\t"
      "leal 0x18(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253248\n\t"
      ".LFUN_001d4ec6_26:\n\t"
      "movzwl (%%edi), %%eax\n\t"
      "subl %%eax, 0x30(%%ebx)\n\t"
      "movzwl (%%edi), %%eax\n\t"
      "addl %%eax, -0x8(%%ebp)\n\t"
      "movb 0xb(%%ebp), %%cl\n\t"
      "movb %%cl, 0x5(%%esi)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpl $0xff00, %%eax\n\t"
      "ja .LFUN_001d4ec6_32\n\t"
      "testb $0x10, %%cl\n\t"
      "movw %%ax, (%%esi)\n\t"
      "jne .LFUN_001d4ec6_27\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "movw %%ax, 0x2(%%ecx,%%esi,1)\n\t"
      "jmp .LFUN_001d4ec6_28\n\t"
      ".LFUN_001d4ec6_27:\n\t"
      "movzbl 0x4(%%esi), %%eax\n\t"
      "movl 0x60(%%ebx,%%eax,4), %%eax\n\t"
      "movl %%esi, 0x40(%%eax)\n\t"
      ".LFUN_001d4ec6_28:\n\t"
      "andb $0xf8, 0x5(%%esi)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "cmpw $0x80, %%cx\n\t"
      "jb .LFUN_001d4ec6_19\n\t"
      "leal 0x180(%%ebx), %%eax\n\t"
      "movl (%%eax), %%edi\n\t"
      "jmp .LFUN_001d4ec6_30\n\t"
      ".LFUN_001d4ec6_29:\n\t"
      "cmpw -0x8(%%edi), %%cx\n\t"
      "jbe .LFUN_001d4ec6_31\n\t"
      "movl (%%edi), %%edi\n\t"
      ".LFUN_001d4ec6_30:\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jne .LFUN_001d4ec6_29\n\t"
      ".LFUN_001d4ec6_31:\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "leal 0x8(%%esi), %%eax\n\t"
      "movl %%edi, (%%eax)\n\t"
      "movl %%ecx, 0xc(%%esi)\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl %%eax, 0x30(%%ebx)\n\t"
      "jmp .LFUN_001d4ec6_33\n\t"
      ".LFUN_001d4ec6_32:\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d4cd9]\n\t"
      ".LFUN_001d4ec6_33:\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      ".LFUN_001d4ec6_34:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "testb $8, %%dl\n\t"
      "je .LFUN_001d4ec6_35\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "jbe .LFUN_001d4ec6_35\n\t"
      "subl %%esi, %%ecx\n\t"
      "leal 0x10(%%esi,%%edi,1), %%edi\n\t"
      "movl %%ecx, %%esi\n\t"
      "shrl $2, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "rep stosl\n\t"
      "movl %%esi, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep stosb\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      ".LFUN_001d4ec6_35:\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $4, %%eax\n\t"
      "xorb 0x5(%%edi), %%al\n\t"
      "shrl $4, %%edx\n\t"
      "andb $0x1f, %%al\n\t"
      "xorb %%dl, %%al\n\t"
      "movb %%al, 0x5(%%edi)\n\t"
      "movb $1, %%al\n\t"
      ".LFUN_001d4ec6_36:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".LFUN_001d4ec6_37:\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d4877] "m"(b1d4ec6_c1d4877), [c1d4a34] "m"(b1d4ec6_c1d4a34), [c1d4cd9] "m"(b1d4ec6_c1d4cd9)
      : "memory");
}
#else
#error "FUN_001d4ec6: clang naked draft required"
#endif


/* 0x1d52c4 */
void FUN_001d52c4(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_001d52f3 (0x1d52f3) — XBE naked draft (batch 304). */
#if defined(__clang__)
static void (*const b1d52f3_c1d47e4)(void) = FUN_001d47e4;
static void (*const b1d52f3_c1d4cd9)(void) = FUN_001d4cd9;

__attribute__((naked, noinline))
void FUN_001d52f3(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "subl 0x18(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "cdq\n\t"
      "movl $0x1000, %%ebx\n\t"
      "movl %%ebx, %%ecx\n\t"
      "idivl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "leal 0x57(%%esi), %%edi\n\t"
      "andl $0xfffffff0, %%edi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl 0x18(%%ebp), %%eax\n\t"
      "jne .LFUN_001d52f3_1\n\t"
      "movw (%%eax), %%ax\n\t"
      "movw %%ax, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001d52f3_2\n\t"
      ".LFUN_001d52f3_1:\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      ".LFUN_001d52f3_2:\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "movl %%edi, %%eax\n\t"
      "subl %%esi, %%eax\n\t"
      "sarl $4, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "leal 0x10(%%edi), %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jb .LFUN_001d52f3_5\n\t"
      "cmpl 0x20(%%ebp), %%eax\n\t"
      "jae .LFUN_001d52f3_3\n\t"
      "movl %%edi, %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "addl $0x10, %%eax\n\t"
      "pushl $4\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "leal 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "leal 0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253148\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001d52f3_4\n\t"
      ".LFUN_001d52f3_3:\n\t"
      "xorb %%al, %%al\n\t"
      "jmp .LFUN_001d52f3_7\n\t"
      ".LFUN_001d52f3_4:\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "addl 0xc(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x1c(%%ebp)\n\t"
      ".LFUN_001d52f3_5:\n\t"
      "movl 0x20(%%ebp), %%eax\n\t"
      "subl %%ecx, %%eax\n\t"
      "cdq\n\t"
      "movl $0x1000, %%ebx\n\t"
      "idivl %%ebx\n\t"
      "movw -0x4(%%ebp), %%dx\n\t"
      "movb 0x10(%%ebp), %%bl\n\t"
      "movw %%dx, 0x2(%%esi)\n\t"
      "movw -0xc(%%ebp), %%dx\n\t"
      "movw %%dx, (%%esi)\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movl %%edx, 0x14(%%esi)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%edx, 0x18(%%esi)\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movl %%edx, 0x20(%%esi)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "shll $0xc, %%edx\n\t"
      "addl 0x18(%%ebp), %%edx\n\t"
      "movb $1, 0x5(%%esi)\n\t"
      "movl %%edx, 0x2c(%%esi)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movb %%bl, 0x4(%%esi)\n\t"
      "movl $0xffeeffee, 0x10(%%esi)\n\t"
      "movl %%edi, 0x28(%%esi)\n\t"
      "movl %%edx, 0x24(%%esi)\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x30(%%esi)\n\t"
      "je .LFUN_001d52f3_6\n\t"
      "shll $0xc, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d47e4]\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      ".LFUN_001d52f3_6:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movzbl %%bl, %%eax\n\t"
      "subl %%edi, %%ecx\n\t"
      "movl %%esi, 0x60(%%edx,%%eax,4)\n\t"
      "movw (%%esi), %%ax\n\t"
      "sarl $4, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "movb $0x10, 0x5(%%edi)\n\t"
      "movl %%edi, 0x40(%%esi)\n\t"
      "pushl %%edx\n\t"
      "movw %%ax, 0x2(%%edi)\n\t"
      "movb %%bl, 0x4(%%edi)\n\t"
      "call *%[c1d4cd9]\n\t"
      "movb $1, %%al\n\t"
      ".LFUN_001d52f3_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d47e4] "m"(b1d52f3_c1d47e4), [c1d4cd9] "m"(b1d52f3_c1d4cd9)
      : "memory");
}
#else
#error "FUN_001d52f3: clang naked draft required"
#endif


/* FUN_001d5411 (0x1d5411) — XBE naked draft (batch 301). */
#if defined(__clang__)
static void (*const b1d5411_c1d4877)(void) = FUN_001d4877;
static void (*const b1d5411_c1d52f3)(void) = FUN_001d52f3;
static void (*const b1d5411_c1d4a34)(void) = FUN_001d4a34;
static void (*const b1d5411_c1d4cd9)(void) = FUN_001d4cd9;

__attribute__((naked, noinline))
void FUN_001d5411(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "leal 0xfff(%%ebx), %%esi\n\t"
      "shrl $0xc, %%esi\n\t"
      "movl %%esi, %%eax\n\t"
      "shll $0xc, %%eax\n\t"
      "andb $0, 0xf(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movb $0x40, -0xc(%%ebp)\n\t"
      ".LFUN_001d5411_1:\n\t"
      "movzbl 0xf(%%ebp), %%ecx\n\t"
      "movl 0x60(%%edi,%%ecx,4), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "je .LFUN_001d5411_2\n\t"
      "cmpl 0x30(%%ecx), %%esi\n\t"
      "ja .LFUN_001d5411_3\n\t"
      "cmpl 0x1c(%%ecx), %%eax\n\t"
      "ja .LFUN_001d5411_3\n\t"
      "pushl $0\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d4877]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001d5411_11\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "jmp .LFUN_001d5411_3\n\t"
      ".LFUN_001d5411_2:\n\t"
      "cmpb $0x40, -0xc(%%ebp)\n\t"
      "jne .LFUN_001d5411_3\n\t"
      "movb 0xf(%%ebp), %%cl\n\t"
      "movb %%cl, -0xc(%%ebp)\n\t"
      ".LFUN_001d5411_3:\n\t"
      "incb 0xf(%%ebp)\n\t"
      "cmpb $0x40, 0xf(%%ebp)\n\t"
      "jb .LFUN_001d5411_1\n\t"
      "cmpb $0x40, -0xc(%%ebp)\n\t"
      "je .LFUN_001d5411_13\n\t"
      "testb $2, 0x14(%%edi)\n\t"
      "je .LFUN_001d5411_13\n\t"
      "movl 0x20(%%edi), %%ecx\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "leal 0x1000(%%ebx), %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "ja .LFUN_001d5411_4\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      ".LFUN_001d5411_4:\n\t"
      "movl 0x253148, %%esi\n\t"
      "pushl $4\n\t"
      "movl $0x2000, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001d5411_8\n\t"
      ".LFUN_001d5411_5:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "cmpl %%ecx, 0x8(%%ebp)\n\t"
      "je .LFUN_001d5411_7\n\t"
      "shrl $1, 0x8(%%ebp)\n\t"
      "cmpl %%ecx, 0x8(%%ebp)\n\t"
      "jae .LFUN_001d5411_6\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      ".LFUN_001d5411_6:\n\t"
      "pushl $4\n\t"
      "pushl %%ebx\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d5411_5\n\t"
      ".LFUN_001d5411_7:\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d5411_13\n\t"
      ".LFUN_001d5411_8:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl %%eax, 0x20(%%edi)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x24(%%edi), %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "ja .LFUN_001d5411_9\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      ".LFUN_001d5411_9:\n\t"
      "pushl $4\n\t"
      "pushl $0x1000\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%%esi\n\t"
      "movl %%eax, %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LFUN_001d5411_12\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl -0xc(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d52f3]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001d5411_10\n\t"
      "movl $0xc0000017, %%esi\n\t"
      ".LFUN_001d5411_10:\n\t"
      "testl %%esi, %%esi\n\t"
      "jl .LFUN_001d5411_12\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x28(%%eax), %%eax\n\t"
      "jmp .LFUN_001d5411_14\n\t"
      ".LFUN_001d5411_11:\n\t"
      "shrl $4, -0x8(%%ebp)\n\t"
      "pushl $0\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d4a34]\n\t"
      "pushl -0x8(%%ebp)\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d4cd9]\n\t"
      "movl %%esi, %%eax\n\t"
      "jmp .LFUN_001d5411_14\n\t"
      ".LFUN_001d5411_12:\n\t"
      "pushl $0x8000\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x25314c\n\t"
      ".LFUN_001d5411_13:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d5411_14:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d4877] "m"(b1d5411_c1d4877), [c1d52f3] "m"(b1d5411_c1d52f3), [c1d4a34] "m"(b1d5411_c1d4a34), [c1d4cd9] "m"(b1d5411_c1d4cd9)
      : "memory");
}
#else
#error "FUN_001d5411: clang naked draft required"
#endif


/* FUN_001d5598 (0x1d5598) — XBE naked draft (batch 298). */
#if defined(__clang__)
static void (*const b1d5598_c1d4cd9)(void) = FUN_001d4cd9;
static void (*const b1d5598_c1d46a3)(void) = FUN_001d46a3;
static void (*const b1d5598_c1d47c3)(void) = FUN_001d47c3;
static void (*const b1d5598_c1d47e4)(void) = FUN_001d47e4;

__attribute__((naked, noinline))
void FUN_001d5598(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "cmpl $0, 0x584(%%ebx)\n\t"
      "je .LFUN_001d5598_1\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d4cd9]\n\t"
      "jmp .LFUN_001d5598_25\n\t"
      ".LFUN_001d5598_1:\n\t"
      "andl $0, -0x10(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "movzbl 0x4(%%esi), %%eax\n\t"
      "movl 0x60(%%ebx,%%eax,4), %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "leal 0xfff(%%esi), %%eax\n\t"
      "movl $0xfffff000, %%edx\n\t"
      "andl %%edx, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "subl %%esi, %%ecx\n\t"
      "sarl $4, %%ecx\n\t"
      "cmpw $1, %%cx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jne .LFUN_001d5598_2\n\t"
      "addl $0x1000, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl $0x101, -0x8(%%ebp)\n\t"
      "jmp .LFUN_001d5598_3\n\t"
      ".LFUN_001d5598_2:\n\t"
      "movw 0x2(%%esi), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "je .LFUN_001d5598_3\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jne .LFUN_001d5598_3\n\t"
      "movzwl %%cx, %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "movl %%ecx, %%edi\n\t"
      "movl %%esi, %%ecx\n\t"
      "subl %%edi, %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      ".LFUN_001d5598_3:\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "andl $0, -0x18(%%ebp)\n\t"
      "shll $4, %%edi\n\t"
      "addl %%esi, %%edi\n\t"
      "movl %%edi, %%ecx\n\t"
      "andl %%edx, %%ecx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "movl %%edi, %%ecx\n\t"
      "subl 0xc(%%ebp), %%ecx\n\t"
      "sarl $4, %%ecx\n\t"
      "cmpw $1, %%cx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jne .LFUN_001d5598_4\n\t"
      "subl $0x1000, 0xc(%%ebp)\n\t"
      "movl $0x101, -0xc(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "jmp .LFUN_001d5598_5\n\t"
      ".LFUN_001d5598_4:\n\t"
      "testw %%cx, %%cx\n\t"
      "jne .LFUN_001d5598_5\n\t"
      "testb $0x10, 0x5(%%esi)\n\t"
      "jne .LFUN_001d5598_5\n\t"
      "movl %%edi, -0x18(%%ebp)\n\t"
      ".LFUN_001d5598_5:\n\t"
      "movzwl %%cx, %%ecx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "shll $4, %%ecx\n\t"
      "subl %%ecx, %%edi\n\t"
      "cmpl %%eax, 0xc(%%ebp)\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "jbe .LFUN_001d5598_6\n\t"
      "subl %%eax, 0xc(%%ebp)\n\t"
      "jmp .LFUN_001d5598_7\n\t"
      ".LFUN_001d5598_6:\n\t"
      "andl $0, 0xc(%%ebp)\n\t"
      ".LFUN_001d5598_7:\n\t"
      "cmpl $0, 0xc(%%ebp)\n\t"
      "je .LFUN_001d5598_23\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c1d46a3]\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "je .LFUN_001d5598_23\n\t"
      "pushl $0x4000\n\t"
      "leal 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x25314c\n\t"
      "pushl -0x1c(%%ebp)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c1d47c3]\n\t"
      "cmpl $0, -0x20(%%ebp)\n\t"
      "jl .LFUN_001d5598_23\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl -0x4(%%ebp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c1d47e4]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "shrl $0xc, %%eax\n\t"
      "addl %%eax, 0x30(%%edx)\n\t"
      "testw %%cx, %%cx\n\t"
      "je .LFUN_001d5598_14\n\t"
      "movzwl %%cx, %%eax\n\t"
      "movb $0x10, 0x5(%%esi)\n\t"
      "movw %%cx, (%%esi)\n\t"
      "addl %%eax, 0x30(%%ebx)\n\t"
      "movl %%esi, 0x40(%%edx)\n\t"
      "andb $0xf8, 0x5(%%esi)\n\t"
      "cmpw $0x80, %%cx\n\t"
      "jae .LFUN_001d5598_8\n\t"
      "leal 0x180(%%ebx,%%eax,8), %%eax\n\t"
      "cmpl %%eax, (%%eax)\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "jne .LFUN_001d5598_13\n\t"
      "movzwl (%%esi), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "shrl $3, %%eax\n\t"
      "leal 0x160(%%eax,%%ebx,1), %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "andl $7, %%ecx\n\t"
      "movb $1, %%al\n\t"
      "shlb %%cl, %%al\n\t"
      "movb %%al, %%cl\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "orb %%cl, (%%eax)\n\t"
      "jmp .LFUN_001d5598_12\n\t"
      ".LFUN_001d5598_8:\n\t"
      "leal 0x180(%%ebx), %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "jmp .LFUN_001d5598_10\n\t"
      ".LFUN_001d5598_9:\n\t"
      "movw -0x8(%%ebp), %%cx\n\t"
      "cmpw -0x8(%%eax), %%cx\n\t"
      "jbe .LFUN_001d5598_11\n\t"
      "movl (%%eax), %%eax\n\t"
      "leal 0x180(%%ebx), %%ecx\n\t"
      ".LFUN_001d5598_10:\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jne .LFUN_001d5598_9\n\t"
      ".LFUN_001d5598_11:\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      ".LFUN_001d5598_12:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      ".LFUN_001d5598_13:\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "leal 0x8(%%esi), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0xc(%%esi)\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%esi, (%%ecx)\n\t"
      "movl %%esi, 0x4(%%eax)\n\t"
      "jmp .LFUN_001d5598_17\n\t"
      ".LFUN_001d5598_14:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d5598_15\n\t"
      "orb $0x10, 0x5(%%eax)\n\t"
      "jmp .LFUN_001d5598_16\n\t"
      ".LFUN_001d5598_15:\n\t"
      "movl 0x40(%%edx), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jb .LFUN_001d5598_17\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "addl %%ecx, %%esi\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jae .LFUN_001d5598_17\n\t"
      "movl 0x28(%%edx), %%eax\n\t"
      ".LFUN_001d5598_16:\n\t"
      "movl %%eax, 0x40(%%edx)\n\t"
      ".LFUN_001d5598_17:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_001d5598_22\n\t"
      "andw $0, 0x2(%%edi)\n\t"
      "movb 0x4(%%edx), %%cl\n\t"
      "andb $0, 0x5(%%edi)\n\t"
      "movb %%cl, 0x4(%%edi)\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "movw %%ax, (%%edi)\n\t"
      "movw %%ax, 0x2(%%ecx,%%edi,1)\n\t"
      "andb $0xf8, 0x5(%%edi)\n\t"
      "cmpw $0x80, %%ax\n\t"
      "jae .LFUN_001d5598_18\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "leal 0x180(%%ebx,%%eax,8), %%esi\n\t"
      "cmpl %%esi, (%%esi)\n\t"
      "jne .LFUN_001d5598_21\n\t"
      "movzwl (%%edi), %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "andl $7, %%ecx\n\t"
      "movb $1, %%dl\n\t"
      "shrl $3, %%eax\n\t"
      "shlb %%cl, %%dl\n\t"
      "leal 0x160(%%eax,%%ebx,1), %%eax\n\t"
      "orb %%dl, (%%eax)\n\t"
      "jmp .LFUN_001d5598_21\n\t"
      ".LFUN_001d5598_18:\n\t"
      "leal 0x180(%%ebx), %%ecx\n\t"
      "movl (%%ecx), %%esi\n\t"
      "jmp .LFUN_001d5598_20\n\t"
      ".LFUN_001d5598_19:\n\t"
      "cmpw -0x8(%%esi), %%ax\n\t"
      "jbe .LFUN_001d5598_21\n\t"
      "movl (%%esi), %%esi\n\t"
      ".LFUN_001d5598_20:\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "jne .LFUN_001d5598_19\n\t"
      ".LFUN_001d5598_21:\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "leal 0x8(%%edi), %%eax\n\t"
      "movl %%esi, (%%eax)\n\t"
      "movl %%ecx, 0xc(%%edi)\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "addl %%eax, 0x30(%%ebx)\n\t"
      "jmp .LFUN_001d5598_24\n\t"
      ".LFUN_001d5598_22:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d5598_24\n\t"
      "andw $0, 0x2(%%eax)\n\t"
      "jmp .LFUN_001d5598_24\n\t"
      ".LFUN_001d5598_23:\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d4cd9]\n\t"
      ".LFUN_001d5598_24:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".LFUN_001d5598_25:\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d4cd9] "m"(b1d5598_c1d4cd9), [c1d46a3] "m"(b1d5598_c1d46a3), [c1d47c3] "m"(b1d5598_c1d47c3), [c1d47e4] "m"(b1d5598_c1d47e4)
      : "memory");
}
#else
#error "FUN_001d5598: clang naked draft required"
#endif


/* FUN_001d5842 (0x1d5842) — XBE naked draft (batch 298). */
#if defined(__clang__)
static void (*const b1d5842_c1dd5c8)(void) = FUN_001dd5c8;
static void * (*const b1d5842_c1da290)(void *dest, const void *src, size_t size) = memmove;
static void (*const b1d5842_c1d52f3)(void) = FUN_001d52f3;
static void (*const b1d5842_c1dd601)(void) = __SEH_epilog;

__attribute__((naked, noinline))
void FUN_001d5842(void)
{
  __asm__ volatile(
      "pushl $0x68\n\t"
      "pushl $0x2c1e90\n\t"
      "call *%[c1dd5c8]\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%esi, -0x1c(%%ebp)\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "pushl $0xc\n\t"
      "popl %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal -0x4c(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "je .LFUN_001d5842_3\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "cmpl $0x30, (%%eax)\n\t"
      "jne .LFUN_001d5842_1\n\t"
      "pushl $0x30\n\t"
      "pushl %%eax\n\t"
      "leal -0x4c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1da290]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001d5842_1:\n\t"
      "orl $0xffffffff, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001d5842_2\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl %%eax, -0x50(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "ret\n\t"
      "movl -0x18(%%ebp), %%esp\n\t"
      "movl -0x50(%%ebp), %%ebx\n\t"
      "orl $0xffffffff, -0x4(%%ebp)\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LFUN_001d5842_2:\n\t"
      "cmpl %%esi, %%ebx\n\t"
      "jl .LFUN_001d5842_32\n\t"
      ".LFUN_001d5842_3:\n\t"
      "testb $0x20, 0x632a22\n\t"
      "je .LFUN_001d5842_4\n\t"
      "orb $0x80, 0x8(%%ebp)\n\t"
      ".LFUN_001d5842_4:\n\t"
      "cmpl %%esi, -0x48(%%ebp)\n\t"
      "jne .LFUN_001d5842_5\n\t"
      "movl 0x32fd50, %%eax\n\t"
      "movl %%eax, -0x48(%%ebp)\n\t"
      ".LFUN_001d5842_5:\n\t"
      "cmpl %%esi, -0x44(%%ebp)\n\t"
      "jne .LFUN_001d5842_6\n\t"
      "movl 0x32fd54, %%eax\n\t"
      "movl %%eax, -0x44(%%ebp)\n\t"
      ".LFUN_001d5842_6:\n\t"
      "cmpl %%esi, -0x40(%%ebp)\n\t"
      "jne .LFUN_001d5842_7\n\t"
      "movl 0x32fd5c, %%eax\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      ".LFUN_001d5842_7:\n\t"
      "cmpl %%esi, -0x3c(%%ebp)\n\t"
      "jne .LFUN_001d5842_8\n\t"
      "movl 0x32fd58, %%eax\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      ".LFUN_001d5842_8:\n\t"
      "cmpl %%esi, -0x38(%%ebp)\n\t"
      "jne .LFUN_001d5842_9\n\t"
      "movl $0x7ffdefff, -0x38(%%ebp)\n\t"
      ".LFUN_001d5842_9:\n\t"
      "cmpl %%esi, -0x34(%%ebp)\n\t"
      "je .LFUN_001d5842_10\n\t"
      "cmpl $0xff000, -0x34(%%ebp)\n\t"
      "jbe .LFUN_001d5842_11\n\t"
      ".LFUN_001d5842_10:\n\t"
      "movl $0xff000, -0x34(%%ebp)\n\t"
      ".LFUN_001d5842_11:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jne .LFUN_001d5842_14\n\t"
      "movl $0x1000, 0x14(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jne .LFUN_001d5842_12\n\t"
      "movl $0x40000, 0x10(%%ebp)\n\t"
      "jmp .LFUN_001d5842_16\n\t"
      ".LFUN_001d5842_12:\n\t"
      "addl $0xfff, %%eax\n\t"
      "andl $0xfffff000, %%eax\n\t"
      ".LFUN_001d5842_13:\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "jmp .LFUN_001d5842_16\n\t"
      ".LFUN_001d5842_14:\n\t"
      "addl $0xfff, %%eax\n\t"
      "movl $0xfffff000, %%ecx\n\t"
      "andl %%ecx, %%eax\n\t"
      "movl %%eax, 0x14(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "cmpl %%esi, %%edx\n\t"
      "jne .LFUN_001d5842_15\n\t"
      "addl $0xffff, %%eax\n\t"
      "andl $0xffff0000, %%eax\n\t"
      "jmp .LFUN_001d5842_13\n\t"
      ".LFUN_001d5842_15:\n\t"
      "addl $0xfff, %%edx\n\t"
      "andl %%ecx, %%edx\n\t"
      "movl %%edx, 0x10(%%ebp)\n\t"
      ".LFUN_001d5842_16:\n\t"
      "movl $0x590, -0x54(%%ebp)\n\t"
      "testb $1, 0x8(%%ebp)\n\t"
      "jne .LFUN_001d5842_18\n\t"
      "cmpl %%esi, 0x18(%%ebp)\n\t"
      "je .LFUN_001d5842_17\n\t"
      "orb $0x80, 0xb(%%ebp)\n\t"
      "jmp .LFUN_001d5842_19\n\t"
      ".LFUN_001d5842_17:\n\t"
      "movl $0x5ac, -0x54(%%ebp)\n\t"
      "orl $0xffffffff, 0x18(%%ebp)\n\t"
      "jmp .LFUN_001d5842_19\n\t"
      ".LFUN_001d5842_18:\n\t"
      "cmpl %%esi, 0x18(%%ebp)\n\t"
      "jne .LFUN_001d5842_32\n\t"
      ".LFUN_001d5842_19:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "cmpl %%esi, %%edi\n\t"
      "je .LFUN_001d5842_23\n\t"
      "cmpl %%esi, -0x28(%%ebp)\n\t"
      "je .LFUN_001d5842_20\n\t"
      "movl -0x30(%%ebp), %%ebx\n\t"
      "cmpl %%esi, %%ebx\n\t"
      "je .LFUN_001d5842_32\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "je .LFUN_001d5842_32\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "ja .LFUN_001d5842_32\n\t"
      "testb $2, 0x8(%%ebp)\n\t"
      "jne .LFUN_001d5842_32\n\t"
      "movl %%edi, -0x58(%%ebp)\n\t"
      "addl %%edi, %%ebx\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "movl $0x400, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "rep stosl\n\t"
      "jmp .LFUN_001d5842_22\n\t"
      ".LFUN_001d5842_20:\n\t"
      "leal -0x74(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "movl 0x253154, %%esi\n\t"
      "call *%%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d5842_32\n\t"
      "movl -0x74(%%ebp), %%edi\n\t"
      "cmpl 0xc(%%ebp), %%edi\n\t"
      "jne .LFUN_001d5842_32\n\t"
      "cmpl $0x10000, -0x64(%%ebp)\n\t"
      "je .LFUN_001d5842_32\n\t"
      "movl %%edi, -0x58(%%ebp)\n\t"
      "movl $0x1000, %%eax\n\t"
      "cmpl %%eax, -0x64(%%ebp)\n\t"
      "jne .LFUN_001d5842_21\n\t"
      "movl $0x400, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "rep stosl\n\t"
      "movl -0x68(%%ebp), %%eax\n\t"
      "movl %%eax, 0x14(%%ebp)\n\t"
      "movl -0x58(%%ebp), %%ecx\n\t"
      "leal (%%eax,%%ecx,1), %%ebx\n\t"
      "leal -0x74(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%%esi\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d5842_22\n\t"
      "cmpl $0x2000, -0x64(%%ebp)\n\t"
      "jne .LFUN_001d5842_22\n\t"
      "movl -0x68(%%ebp), %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "jmp .LFUN_001d5842_22\n\t"
      ".LFUN_001d5842_21:\n\t"
      "movl %%eax, 0x14(%%ebp)\n\t"
      "movl %%edi, %%ebx\n\t"
      ".LFUN_001d5842_22:\n\t"
      "movl $1, -0x78(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "jmp .LFUN_001d5842_25\n\t"
      ".LFUN_001d5842_23:\n\t"
      "cmpl %%esi, -0x28(%%ebp)\n\t"
      "jne .LFUN_001d5842_32\n\t"
      "pushl $4\n\t"
      "pushl $0x2000\n\t"
      "leal 0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253148\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d5842_32\n\t"
      "movl %%esi, -0x78(%%ebp)\n\t"
      "cmpl %%esi, 0x14(%%ebp)\n\t"
      "jne .LFUN_001d5842_24\n\t"
      "movl $0x1000, 0x14(%%ebp)\n\t"
      ".LFUN_001d5842_24:\n\t"
      "movl -0x1c(%%ebp), %%ebx\n\t"
      "movl %%ebx, -0x58(%%ebp)\n\t"
      ".LFUN_001d5842_25:\n\t"
      "cmpl %%ebx, -0x58(%%ebp)\n\t"
      "jne .LFUN_001d5842_27\n\t"
      "pushl $4\n\t"
      "pushl $0x1000\n\t"
      "leal 0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "leal -0x58(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253148\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001d5842_26\n\t"
      "cmpl $0, 0xc(%%ebp)\n\t"
      "jne .LFUN_001d5842_32\n\t"
      "pushl $0x8000\n\t"
      "leal 0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x25314c\n\t"
      "jmp .LFUN_001d5842_32\n\t"
      ".LFUN_001d5842_26:\n\t"
      "addl 0x14(%%ebp), %%ebx\n\t"
      ".LFUN_001d5842_27:\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "leal 0x597(%%edx), %%eax\n\t"
      "andl $0xfffffff8, %%eax\n\t"
      "movl -0x54(%%ebp), %%esi\n\t"
      "movl $0x80, %%edi\n\t"
      "addl %%edi, %%esi\n\t"
      "addl $0x4c, %%edx\n\t"
      "pushl $8\n\t"
      "popl %%ecx\n\t"
      ".LFUN_001d5842_28:\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl %%eax, %%edx\n\t"
      "addl $0x10, %%eax\n\t"
      "decl %%ecx\n\t"
      "jne .LFUN_001d5842_28\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0, (%%edx)\n\t"
      "testb $8, 0x632a21\n\t"
      "je .LFUN_001d5842_29\n\t"
      "addl $7, %%eax\n\t"
      "andl $0xfffffff8, %%eax\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x17c(%%ecx)\n\t"
      "movl $0x60c, %%eax\n\t"
      "addl %%eax, %%esi\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl 0x17c(%%ecx), %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      ".LFUN_001d5842_29:\n\t"
      "addl $0xf, %%esi\n\t"
      "andl $0xfffffff0, %%esi\n\t"
      "movl %%esi, %%eax\n\t"
      "shrl $4, %%eax\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movw %%ax, (%%edx)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movb $1, 0x5(%%eax)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl $0xeeffeeff, 0x10(%%eax)\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, 0x14(%%edx)\n\t"
      "andl $0x6001007d, %%eax\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl %%eax, 0x18(%%edx)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "orw $0xffff, 0x170(%%eax)\n\t"
      "movl %%ecx, %%edx\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "subl %%eax, %%edx\n\t"
      "movw %%dx, 0x3a(%%eax)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "andl $0, 0x3c(%%eax)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "addl $0x180, %%eax\n\t"
      ".LFUN_001d5842_30:\n\t"
      "movl %%eax, 0x4(%%eax)\n\t"
      "movl %%eax, (%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "decl %%edi\n\t"
      "jne .LFUN_001d5842_30\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "leal 0x58(%%eax), %%edx\n\t"
      "movl %%edx, 0x5c(%%eax)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl 0x5c(%%eax), %%edx\n\t"
      "movl %%edx, 0x58(%%eax)\n\t"
      "movl 0x18(%%ebp), %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .LFUN_001d5842_31\n\t"
      "movl %%ecx, %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *0x253250\n\t"
      ".LFUN_001d5842_31:\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl %%edi, 0x580(%%eax)\n\t"
      "movl -0x58(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl -0x78(%%ebp)\n\t"
      "pushl $0\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "addl %%eax, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d52f3]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001d5842_33\n\t"
      ".LFUN_001d5842_32:\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001d5842_34\n\t"
      ".LFUN_001d5842_33:\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "andw $0, 0x38(%%eax)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl -0x48(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x20(%%eax)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl -0x44(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x24(%%eax)\n\t"
      "movl -0x40(%%ebp), %%eax\n\t"
      "shrl $4, %%eax\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x28(%%ecx)\n\t"
      "movl -0x3c(%%ebp), %%eax\n\t"
      "shrl $4, %%eax\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x2c(%%ecx)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x34(%%eax)\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "addl $0xf, %%eax\n\t"
      "shrl $4, %%eax\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl %%eax, 0x1c(%%ecx)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x584(%%eax)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl $0x1f, 0x50(%%eax)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl $0xfffffff0, 0x54(%%eax)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      ".LFUN_001d5842_34:\n\t"
      "call *%[c1dd601]\n\t"
      "ret\n\t"
      :
      : [c1dd5c8] "m"(b1d5842_c1dd5c8), [c1da290] "m"(b1d5842_c1da290), [c1d52f3] "m"(b1d5842_c1d52f3), [c1dd601] "m"(b1d5842_c1dd601)
      : "memory");
}
#else
#error "FUN_001d5842: clang naked draft required"
#endif

