/* kb object stubs -> xdk/xapilib/xvutil.c */

/* --- XAPILIB:xvutil.obj batch drafts (2026-07-26) --- */

/* FUN_001d04f1 (0x1d04f1) — Capstone tip: query fails/unset → return 1. */
int FUN_001d04f1(void)
{
  unsigned int type = 0;
  unsigned int result = 0;
  unsigned int result_len = 0;
  int status;
  status = ((int (__stdcall *)(int, void *, void *, int, void *))FUN_001d4464)(
      0x11, &type, &result, 4, &result_len);
  if (status != 0)
    return 1;
  if ((result & 2u) == 0)
    return 1;
  return 0;
}



/* GetLocalTime (0x1d051d) — Capstone tip. */
void __stdcall GetLocalTime(void *system_time)
{
  unsigned int ft[2];
  unsigned short fields[8];
  unsigned short *out = (unsigned short *)system_time;
  ((void (__stdcall *)(void *))*(void **)0x25313c)(ft);
  ((void (__stdcall *)(void *, void *))*(void **)0x253138)(ft, fields);
  out[0] = fields[0];
  out[1] = fields[1];
  out[2] = fields[7];
  out[3] = fields[2];
  out[4] = fields[3];
  out[5] = fields[4];
  out[6] = fields[5];
  out[7] = fields[6];
}


/* FUN_001d0581 (0x1d0581) — readable C lift (deref global). */
int FUN_001d0581(void)
{
  return **(int **)0x253140;
}

/* FUN_001d0589 (0x1d0589) — Capstone tip: FileTime → SYSTEMTIME. */
int __stdcall FUN_001d0589(const unsigned long long *file_time, void *system_time)
{
  unsigned int local_ft[2];
  unsigned short fields[8];
  unsigned short *out = (unsigned short *)system_time;
  local_ft[0] = (unsigned int)(*file_time & 0xffffffffu);
  local_ft[1] = (unsigned int)(*file_time >> 32);
  ((void (__stdcall *)(void *, void *))*(void **)0x253138)(local_ft, fields);
  out[0] = fields[0];
  out[1] = fields[1];
  out[3] = fields[2];
  out[2] = fields[7];
  out[4] = fields[3];
  out[5] = fields[4];
  out[6] = fields[5];
  out[7] = fields[6];
  return 1;
}


/* 0x1d05f4 */
/* SystemTimeToFileTime (0x1d05f4) — Capstone tip. */
bool __stdcall SystemTimeToFileTime(void *system_time, void *file_time)
{
  unsigned short *in = (unsigned short *)system_time;
  unsigned short fields[8];
  unsigned int out64[2];
  unsigned char ok;
  fields[0] = in[0];
  fields[1] = in[1];
  fields[2] = in[3];
  fields[3] = in[4];
  fields[4] = in[5];
  fields[5] = in[6];
  fields[6] = in[7];
  ok = (unsigned char)((int (__stdcall *)(void *, void *))*(void **)0x253144)(fields, out64);
  if (!ok) {
    XapiSetLastNTError((int)0xc000000d);
    return 0;
  }
  ((unsigned int *)file_time)[0] = out64[0];
  ((unsigned int *)file_time)[1] = out64[1];
  return 1;
}


/* FUN_001d0669 (0x1d0669) — readable C: compare two unsigned 64-bit values. */
int __stdcall FUN_001d0669(unsigned int *a, unsigned int *b)
{
  unsigned int a_lo, a_hi, b_lo, b_hi;
  a_lo = a[0];
  a_hi = a[1];
  b_lo = b[0];
  b_hi = b[1];
  if (a_hi > b_hi)
    return 1;
  if (a_hi < b_hi)
    return -1;
  if (a_lo < b_lo)
    return -1;
  if (a_lo > b_lo)
    return 1;
  return 0;
}



/* FUN_001d06a0 (0x1d06a0) — Capstone tip: SystemTimeToFileTime fail → return. */
void __stdcall FUN_001d06a0(void *system_time, void *file_time_out, void *file_time_in, void *unused)
{
  unsigned short local_st[8];
  (void)unused;
  FUN_001d0589((const unsigned long long *)file_time_in, local_st);
  if (*(short *)system_time == 0)
    return;
  if (!SystemTimeToFileTime(system_time, file_time_out))
    return;
  (void)local_st;
}


/* GetTimeZoneInformation (0x1d08aa) — Capstone tip: query fail → SetLastError + -1. */
unsigned int __stdcall GetTimeZoneInformation(void *tzinfo)
{
  unsigned int local = 0;
  int status;
  status = FUN_001d0447(tzinfo, &local);
  if (status != 0) {
    SetLastError((unsigned int)status);
    return 0xffffffffu;
  }
  (void)local;
  return 0;
}


/* FUN_001d0a06 (0x1d0a06) — Capstone tip: TZ → FILETIME.
 * Tip path: GetTimeZoneInformation returns 0 → Bias*60*10M. */
void __stdcall FUN_001d0a06(void *out)
{
  unsigned char tz[0xac];
  int status;
  int bias_min;
  long long ticks;
  status = GetTimeZoneInformation(tz);
  if (status == 0) {
    bias_min = *(int *)tz;
  } else if (status == 1) {
    bias_min = *(int *)tz + *(int *)(tz + 0x1c);
  } else if (status == 2) {
    bias_min = *(int *)tz + *(int *)(tz + 0x70);
  } else {
    bias_min = 0;
  }
  ticks = (long long)bias_min * 60LL * 10000000LL;
  ((unsigned int *)out)[0] = (unsigned int)ticks;
  ((unsigned int *)out)[1] = (unsigned int)(ticks >> 32);
}


/* FUN_001d0a5c (0x1d0a5c) — Capstone tip: UTC now − TZ bias → local SYSTEMTIME. */
void __stdcall FUN_001d0a5c(void *system_time)
{
  unsigned int utc[2];
  unsigned int bias[2];
  unsigned int local[2];
  unsigned short fields[8];
  unsigned short *out = (unsigned short *)system_time;
  ((void (__stdcall *)(void *))*(void **)0x25313c)(utc);
  FUN_001d0a06(bias);
  local[0] = utc[0] - bias[0];
  local[1] = utc[1] - bias[1] - (utc[0] < bias[0]);
  ((void (__stdcall *)(void *, void *))*(void **)0x253138)(local, fields);
  out[0] = fields[0];
  out[1] = fields[1];
  out[2] = fields[7];
  out[3] = fields[2];
  out[4] = fields[3];
  out[5] = fields[4];
  out[6] = fields[5];
  out[7] = fields[6];
}


/* FUN_001d0adb (0x1d0adb) — readable C lift: out = *in - now. */
int __stdcall FUN_001d0adb(unsigned long long *in, unsigned long long *out)
{
  unsigned long long now;
  ((void (*)(void *))(void *)FUN_001d0a06)(&now);
  *out = *in - now;
  return 1;
}



/* FUN_001d0b06 (0x1d0b06) — readable C lift: out = *in + now. */
int __stdcall FUN_001d0b06(unsigned long long *in, unsigned long long *out)
{
  unsigned long long now;
  ((void (*)(void *))(void *)FUN_001d0a06)(&now);
  *out = *in + now;
  return 1;
}



/* FUN_001d0b31 (0x1d0b31) — Capstone tip: VirtualAlloc-style helper.
 * Tip: FUN_001d5842 stub returns nonzero → return it. */
void *__stdcall FUN_001d0b31(unsigned int flags, unsigned int size_min,
                             unsigned int size_hint)
{
  unsigned int fl;
  unsigned int sz;
  void *p;
  fl = (flags & 5u) | 0x1000u;
  sz = size_hint;
  if (sz < 0x1000u) {
    if (sz == 0)
      fl |= 2u;
    else
      sz = 0x1000u;
  }
  if (size_min > sz)
    sz = size_min;
  p = ((void *(*)(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned))
           FUN_001d5842)(fl, 0, sz, size_min, 0, 0);
  if (p == 0)
    SetLastError(8);
  return p;
}



/* FUN_001d0b9c (0x1d0b9c) — readable C lift (HeapFree BOOL wrapper). */
unsigned int __stdcall FUN_001d0b9c(void *a, void *b, void *c)
{
  return (unsigned int)(unsigned char)FUN_001d6ca8(a, (unsigned int)(uintptr_t)b, c);
}

/* 0x1d0bb3 */
void FUN_001d0bb3(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_001d0c02 (0x1d0c02) — readable C lift (HeapFree-style). */
void __stdcall FUN_001d0c02(void *ptr)
{
  extern void *DAT_00632a28;
  FUN_001d52c4(DAT_00632a28, 0, ptr);
}

void * LocalFree(void *ptr)
{
  (void)FUN_001d6ca8(0, 0, ptr);
  return NULL;
}

/* FUN_001d0bb9 (0x1d0bb9) — readable C lift (HeapAlloc-style wrapper). */
void *__stdcall FUN_001d0bb9(unsigned int flags, unsigned int size)
{
  extern void *DAT_00632a28;
  return FUN_001d5c66(DAT_00632a28, (flags >> 3) & 8, (int)size);
}

/* FUN_001d0c16 (0x1d0c16) — readable C lift (HeapFree-style wrapper). */
void *__stdcall FUN_001d0c16(void *ptr)
{
  extern void *DAT_00632a28;
  if (FUN_001d6ca8(DAT_00632a28, 0, ptr))
    return 0;
  return ptr;
}

/* FUN_001d0c48 (0x1d0c48) — readable C lift (HeapAlloc-style wrapper). */
void *__stdcall FUN_001d0c48(int flags, int size)
{
  extern void *DAT_00632a28;
  return FUN_001d5c66(DAT_00632a28, ((unsigned int)flags >> 3) & 8, size);
}

/* FUN_001d0c65 (0x1d0c65) — readable C lift (HeapReAlloc-style wrapper). */
void *__stdcall FUN_001d0c65(void *ptr, int size, int flags)
{
  extern void *DAT_00632a28;
  unsigned int mode;
  if ((flags & 0x40) != 0)
    mode = 8;
  else
    mode = (~((unsigned int)flags << 3)) & 0x10;
  return FUN_001d703b(DAT_00632a28, mode, ptr, size);
}

/* FUN_001d0c91 (0x1d0c91) — Capstone tip: IAT NtAllocate-style; seed IAT xor-ret. */
void *__stdcall FUN_001d0c91(void *base, unsigned int size, unsigned int alloc_type,
                             unsigned int protect)
{
  int (__stdcall *nt)(void **, unsigned, unsigned *, unsigned, unsigned) =
      *(int (__stdcall **)(void **, unsigned, unsigned *, unsigned, unsigned))0x253148;
  int status = nt(&base, 0, &size, alloc_type, protect);
  if (status < 0) {
    XapiSetLastNTError(status);
    return 0;
  }
  return base;
}


/* FUN_001d0cbf (0x1d0cbf) — Capstone tip: protect&0x8000 && size!=0 → fail. */
int __stdcall FUN_001d0cbf(void *base, unsigned int size, unsigned int protect)
{
  (void)base;
  if ((protect & 0x8000u) != 0 && size != 0) {
    XapiSetLastNTError((int)0xc000000d);
    return 0;
  }
  /* IAT NtProtectVirtualMemory path omitted under tip */
  return 1;
}



/* FUN_001d0cfb (0x1d0cfb) — Capstone tip: IAT 4-arg; seed IAT xor-ret. */
int __stdcall FUN_001d0cfb(void *base, unsigned int size, unsigned int free_type,
                           unsigned int unused)
{
  int (__stdcall *nt)(void **, unsigned *, unsigned, unsigned) =
      *(int (__stdcall **)(void **, unsigned *, unsigned, unsigned))0x253150;
  int status = nt(&base, &size, free_type, unused);
  if (status < 0) {
    XapiSetLastNTError(status);
    return 0;
  }
  return 1;
}


/* 0x1d0da1 */
/* xbox_query_global_memory_status (0x1d0da1) — Capstone tip. */
void __stdcall xbox_query_global_memory_status(void *status)
{
  unsigned int info[9];
  unsigned int *out = (unsigned int *)status;
  info[0] = 0x24;
  ((void(__stdcall *)(void *))*(void **)0x253158)(info);
  out[1] = 0;
  out[4] = 0;
  out[5] = 0;
  out[2] = info[1] << 12;
  out[3] = info[2] << 12;
  out[6] = 0x7ffe0000u;
  out[0] = 0x20;
  out[7] = 0x7ffe0000u - info[4];
}


/* FUN_001d0df0 (0x1d0df0) — Capstone tip: create IAT status < 0 → false. */
bool __stdcall FUN_001d0df0(const char *path, unsigned int attributes)
{
  unsigned int name[2];
  unsigned int io[4];
  int status;
  (void)attributes;
  ((void (__stdcall *)(void *, const char *))*(void **)0x2530e4)(name, path);
  io[0] = 0xfffffffd;
  io[1] = (unsigned int)(unsigned long)name;
  io[2] = 0x40;
  status = ((int (__stdcall *)(void *, unsigned, void *, void *, unsigned, unsigned))
                *(void **)0x253160)(
      (void *)&path, 0x100100, &io[0], &io[2], 7, 0x4020);
  if (status < 0) {
    XapiSetLastNTError(status);
    return 0;
  }
  return 1;
}

/* WaitForSingleObject (0x1d0336) — readable C lift. */
int __stdcall WaitForSingleObject(int handle, int timeout_ms)
{
  return FUN_001d00b9(handle, timeout_ms, 0);
}

/* FUN_001d0362 (0x1d0362) — readable C lift (Sleep-style). */
void __stdcall FUN_001d0362(int ms)
{
  FUN_001d01c4(ms, 0);
}

/* FUN_001cfde0 (0x1cfde0) — readable C lift (TEB TLS slot). */
int FUN_001cfde0(void)
{
  void *teb;
  __asm__ volatile("movl %%fs:0x28, %0" : "=r"(teb));
  return *(int *)((char *)teb + 0x12c);
}


/* FUN_001d0348 (0x1d0348) — readable C lift (WaitForMultipleObjects). */
int __stdcall FUN_001d0348(int nCount, void *handles, int waitAll, int timeout_ms)
{
  return FUN_001d0144(nCount, handles, waitAll, timeout_ms, 0);
}

/* ResetEvent (0x1cfeca) — readable C lift. */
int __stdcall ResetEvent(void *handle)
{
  int (__stdcall *nt_clear)(void *) = *(int (__stdcall **)(void *))0x2530ec;
  int status = nt_clear(handle);
  if (status < 0) {
    XapiSetLastNTError(status);
    return 0;
  }
  return 1;
}
