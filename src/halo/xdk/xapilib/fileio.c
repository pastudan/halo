/* kb object stubs -> xdk/xapilib/fileio.c */

/* --- XAPILIB:fileio.obj batch drafts (2026-07-26) --- */

/* 0x1d0e96 */
int file_get_full_attributes(const char *path)
{
  int eax = 0;

  /* test eax, eax -> jl 0x1d0ed4 */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
}

/* 0x1d0ee1 */
void FUN_001d0ee1(void)
{
  int eax = 0;

  /* test eax, eax -> jl 0x1d0f57 */
  XapiSetLastNTError(0);

  (void)eax;
}

/* 0x1d0f63 */
void MoveFileA(void)
{
  int eax = 0;
  int esi = 0;

  /* test eax, eax -> jge 0x1d0fb2 */
  /* test esi, esi -> jl 0x1d0feb */
  XapiSetLastNTError(0);

  (void)eax;
  (void)esi;
}

/* 0x1d0ff9 */
bool DeleteFileA(const char *path)
{
  int eax = 0;
  int esi = 0;

  /* test eax, eax -> jge 0x1d104c */
  XapiSetLastNTError(0);
  /* test esi, esi -> jl 0x1d107a */
  XapiSetLastNTError(0);
  /* relift: test word ptr [esp + 4], 0xfff -> je 0x1d1098 */
  /* test eax, eax -> jl 0x1d10a8 */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
  (void)esi;
}

/* 0x1d10bd */
void FUN_001d10bd(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: test byte ptr [esi + 0x38], 0x10 -> je 0x1d1174 */
  /* relift: tail-call FUN_001d10bd(); */
  /* relift: cmp dword ptr [esi + 0x2c], 0 -> jne 0x1d11a6 */
  /* cmp eax, ebx -> jae 0x1d1195 */
  /* relift: cmp dword ptr [edi], ebx -> jae 0x1d11a6 */
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> jl 0x1d11a8 */
  /* relift: cmp dword ptr [edi], ebx -> jb 0x1d11c9 */
  /* relift: cmp dword ptr [ebp + 0x10], 0xc000000f -> jne 0x1d11e2 */

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d11e9 */
void FUN_001d11e9(void)
{
  int esi = 0;
  int ebp = 0;

  /* test esi, esi -> jl 0x1d12b4 */
  /* relift: test byte ptr [ebp - 0x28], 0x10 -> je 0x1d127d */
  /* test esi, esi -> jl 0x1d12b4 */
  FUN_001d10bd();
  /* relift: cmp dword ptr [ebp - 0x2c], 0 -> je 0x1d128a */
  /* test esi, esi -> jge 0x1d12bc */
  XapiSetLastNTError(0);

  (void)esi;
  (void)ebp;
}

/* 0x1d12c1 */
void FUN_001d12c1(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int ebp = 0;

  /* test eax, eax -> jge 0x1d1315 */
  /* test esi, esi -> jl 0x1d1352 */
  /* cmp esi, 0xc00000d4 -> jne 0x1d13a2 */
  /* relift: test byte ptr [ebp + 0x18], 2 -> je 0x1d13a2 */
  FUN_001d1f10();
  /* test esi, esi -> je 0x1d139e */
  DeleteFileA((char *)(uintptr_t)ebx);
  /* test eax, eax -> jne 0x1d139e */
  FUN_001d0df0((char *)(uintptr_t)ebx, 128);
  DeleteFileA((char *)(uintptr_t)ebx);
  XapiSetLastNTError(0);
  /* relift: tail-call FUN_001d12c1(); */

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)ebp;
}

/* 0x1d13c9 */
int ReadFile(int handle, void *buffer, uint32_t size, uint32_t *bytes_read, void *overlapped)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp edi, ebx -> je 0x1d13dd */
  /* cmp esi, ebx -> je 0x1d144c */
  /* cmp eax, ebx -> jl 0x1d1437 */
  /* cmp eax, edi -> je 0x1d1437 */
  /* cmp eax, ebx -> je 0x1d1432 */
  /* cmp eax, ecx -> jne 0x1d14a7 */
  /* cmp eax, ebx -> je 0x1d1449 */
  /* cmp eax, 0x103 -> jne 0x1d147c */
  /* cmp eax, ebx -> jl 0x1d1487 */
  /* cmp eax, ebx -> jl 0x1d1487 */
  /* cmp eax, 0xc0000011 -> jne 0x1d1492 */
  /* cmp ecx, 0x80000000 -> jne 0x1d14a7 */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x1d14b6 */
int WriteFile(int handle, void *buffer, uint32_t size, uint32_t *bytes_written, void *overlapped)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp edi, ebx -> je 0x1d14ca */
  /* cmp esi, ebx -> je 0x1d152d */
  /* cmp edx, ecx -> je 0x1d157d */
  /* cmp eax, edi -> je 0x1d157d */
  /* cmp eax, ebx -> je 0x1d1528 */
  /* cmp eax, 0x103 -> jne 0x1d155d */
  /* cmp eax, ebx -> jl 0x1d1568 */
  /* cmp eax, ebx -> jl 0x1d1568 */
  /* cmp ecx, 0x80000000 -> jne 0x1d157d */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1d158c */
bool SetEndOfFile(int handle)
{
  int eax = 0;

  /* test eax, eax -> jge 0x1d15b5 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1d1603 */
  /* test eax, eax -> jl 0x1d1603 */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
}

/* 0x1d1610 */
unsigned int SetFilePointer(int handle, int distance, int *distance_high, unsigned int method)
{
  int eax = 0;
  int ebx = 0;
  int ebp = 0;

  /* test eax, eax -> jl 0x1d167c */
  /* test eax, eax -> jge 0x1d1687 */
  XapiSetLastNTError(0);
  /* relift: cmp dword ptr [ebp - 8], 0 -> jae 0x1d16ac */
  /* test ebx, ebx -> jne 0x1d16c0 */
  /* test eax, 0x7fffffff -> je 0x1d16c0 */
  SetLastError(87);
  /* test eax, eax -> jl 0x1d16f4 */
  /* test ebx, ebx -> je 0x1d16e2 */
  /* relift: cmp dword ptr [ebp - 8], -1 -> jne 0x1d16ef */
  SetLastError(0);
  XapiSetLastNTError(0);
  /* test ebx, ebx -> je 0x1d1703 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ebp;
}

/* 0x1d170a */
void FUN_001d170a(void)
{
  int eax = 0;
  int ecx = 0;

  /* test eax, eax -> jl 0x1d17c6 */
  /* test eax, eax -> jl 0x1d17c6 */
  /* test ecx, ecx -> jae 0x1d1796 */
  SetLastError(131);
  /* test eax, eax -> jl 0x1d17c6 */
  /* test eax, eax -> je 0x1d17c1 */
  XapiSetLastNTError(0);

  (void)eax;
  (void)ecx;
}

/* 0x1d17d2 */
void FUN_001d17d2(void)
{
  int ecx = 0;
  int esi = 0;

  /* cmp ecx, esi -> je 0x1d1899 */
  /* cmp ecx, esi -> je 0x1d1899 */
  /* cmp ecx, esi -> je 0x1d1899 */
  XapiSetLastNTError(0);

  (void)ecx;
  (void)esi;
}

/* 0x1d18aa */
void FUN_001d18aa(void)
{
  int eax = 0;

  /* test eax, eax -> jl 0x1d1904 */
  /* test eax, eax -> je 0x1d18db */
  /* test eax, eax -> je 0x1d18ed */
  /* test eax, eax -> je 0x1d18ff */
  XapiSetLastNTError(0);

  (void)eax;
}

/* 0x1d1910 */
bool SetFileTime(int handle, void *creation_time, void *last_access_time, void *last_write_time)
{
  int eax = 0;

  /* test eax, eax -> je 0x1d1946 */
  /* test eax, eax -> je 0x1d1958 */
  /* test eax, eax -> jl 0x1d1976 */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
}

/* 0x1d1982 */
void FUN_001d1982(void)
{
  int eax = 0;

  /* test eax, eax -> jl 0x1d199d */
  XapiSetLastNTError(0);

  (void)eax;
}

/* 0x1d19a9 */
void FUN_001d19a9(void)
{
  int eax = 0;

  /* test eax, eax -> jge 0x1d19d2 */
  XapiSetLastNTError(0);

  (void)eax;
}

/* 0x1d19e7 */
void FUN_001d19e7(void)
{
  int ecx = 0;
  int edx = 0;

  /* cmp edx, ecx -> jne 0x1d1a31 */
  XapiSetLastNTError(0);

  (void)ecx;
  (void)edx;
}

/* 0x1d1a38 */
void FUN_001d1a38(void)
{
  int ecx = 0;
  int edx = 0;

  /* cmp edx, ecx -> jne 0x1d1a82 */
  XapiSetLastNTError(0);

  (void)ecx;
  (void)edx;
}

/* 0x1d1a89 */
void FUN_001d1a89(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;

  /* cmp edx, ecx -> je 0x1d1b11 */
  /* cmp ecx, ebx -> je 0x1d1b11 */
  /* cmp eax, ebx -> jl 0x1d1b79 */
  /* cmp eax, 0x103 -> je 0x1d1b79 */
  /* cmp eax, 0x103 -> jne 0x1d1b56 */
  /* cmp eax, ebx -> jl 0x1d1b64 */
  /* cmp eax, ebx -> jl 0x1d1b64 */
  /* cmp edx, ecx -> je 0x1d1b79 */
  XapiSetLastNTError(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
}

/* 0x1d1b87 */
void FUN_001d1b87(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp edi, ebx -> je 0x1d1b9b */
  /* cmp esi, ebx -> je 0x1d1c0a */
  /* cmp eax, ebx -> jl 0x1d1bf5 */
  /* cmp eax, edi -> je 0x1d1bf5 */
  /* cmp eax, ebx -> je 0x1d1bf0 */
  /* cmp eax, ecx -> jne 0x1d1c65 */
  /* cmp eax, ebx -> je 0x1d1c07 */
  /* cmp eax, 0x103 -> jne 0x1d1c3a */
  /* cmp eax, ebx -> jl 0x1d1c45 */
  /* cmp eax, ebx -> jl 0x1d1c45 */
  /* cmp eax, 0xc0000011 -> jne 0x1d1c50 */
  /* cmp ecx, 0x80000000 -> jne 0x1d1c65 */
  XapiSetLastNTError(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x1d1c74 */
void FUN_001d1c74(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp edi, ebx -> je 0x1d1c88 */
  /* cmp esi, ebx -> je 0x1d1ceb */
  /* cmp edx, ecx -> je 0x1d1d3b */
  /* cmp eax, edi -> je 0x1d1d3b */
  /* cmp eax, ebx -> je 0x1d1ce6 */
  /* cmp eax, 0x103 -> jne 0x1d1d1b */
  /* cmp eax, ebx -> jl 0x1d1d26 */
  /* cmp eax, ebx -> jl 0x1d1d26 */
  /* cmp ecx, 0x80000000 -> jne 0x1d1d3b */
  XapiSetLastNTError(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1d1d4a */
unsigned int GetFileSize(int handle, unsigned int *high_size)
{
  int eax = 0;
  int ebp = 0;

  FUN_001d19a9();
  /* test eax, eax -> je 0x1d1d7a */
  /* test eax, eax -> je 0x1d1d6b */
  /* relift: cmp dword ptr [ebp - 8], -1 -> jne 0x1d1d7e */
  SetLastError(0);
  return 0;

  (void)eax;
  (void)ebp;
}

/* 0x1d1d85 */
int CreateFileA(const char * unused_arg_0, uint32_t unused_arg_1, uint32_t unused_arg_2, uint32_t unused_arg_3, uint32_t unused_arg_4, uint32_t unused_arg_5, uint32_t unused_arg_6)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  XapiSetLastNTError(0xc000000d);
  /* relift: cmp word ptr [ebp - 0xc], (int16_t)ebx -> jbe 0x1d1e06 */
  /* relift: cmp byte ptr [eax + edi - 1], 0x5c -> jne 0x1d1e06 */
  /* cmp esi, ebx -> jge 0x1d1ee2 */
  XapiSetLastNTError(0);
  /* cmp esi, 0xc0000035 -> jne 0x1d1ec5 */
  /* cmp esi, 0xc00000ba -> jne 0x1d1edd */
  /* relift: cmp dword ptr [ebp + 8], ebx -> je 0x1d1ed6 */
  SetLastError(0);
  /* relift: cmp dword ptr [ebp + 0x18], 2 -> jne 0x1d1eee */
  /* relift: cmp dword ptr [ebp - 0x10], 3 -> je 0x1d1efa */
  /* relift: cmp dword ptr [ebp + 0x18], 4 -> jne 0x1d1f01 */
  /* relift: cmp dword ptr [ebp - 0x10], 1 -> jne 0x1d1f01 */
  SetLastError(ebx);
  return 0;

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d1f10 */
void FUN_001d1f10(void)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  SetLastError(0);
  XapiSetLastNTError(0);
  /* cmp esi, edi -> jge 0x1d2023 */
  /* cmp eax, 3 -> jne 0x1d211f */
  /* cmp esi, edi -> jl 0x1d21a4 */
  /* relift: cmp eax, dword ptr [ebp + 0x34] -> jg 0x1d2153 */
  /* cmp esi, edi -> jl 0x1d21a4 */
  /* cmp esi, edi -> jl 0x1d21a4 */
  /* cmp eax, 3 -> jne 0x1d212e */
  /* cmp eax, edi -> je 0x1d205a */
  /* cmp eax, edi -> jne 0x1d214e */
  /* relift: cmp eax, dword ptr [ebp + 0x34] -> jl 0x1d2097 */
  /* relift: cmp eax, dword ptr [ebp + 0x30] -> jb 0x1d2097 */
  /* cmp esi, edi -> jl 0x1d21a4 */
  /* cmp esi, edi -> jge 0x1d21de */
  XapiSetLastNTError(0);
  /* relift: tail-call FUN_001d1f10(); */
  /* cmp (char)eax, 2 -> jae 0x1d223d */
  /* relift: cmp dword ptr [eax + 0x28], 0 -> je 0x1d223d */
  /* cmp (char)eax, 2 -> jae 0x1d2252 */
  /* cmp (char)eax, 2 -> jae 0x1d227a */
  SetLastError(edx);
  /* test eax, eax -> jge 0x1d22dd */
  XapiSetLastNTError(0);
  /* relift: cmp dword ptr [ebp + 8], -1 -> je 0x1d231f */
  /* test eax, eax -> jge 0x1d2331 */
  XapiSetLastNTError(0);

  (void)eax;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
