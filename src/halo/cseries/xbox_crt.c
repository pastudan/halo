/*
 * xbox_crt.c — LIBCMT/XAPI CRT helper replacements
 *
 * These are compact SEH functions from the original LIBCMT/XAPI libraries.
 * The originals use __SEH_prolog/__SEH_epilog (compact MSVC SEH thunks).
 * We replace them with __try/__except using clang's built-in SEH support
 * (-target i386-pc-win32 implies ms-extensions; __try/__except compiles
 * without -fms-extensions on Windows targets).
 *
 * The SEH frame shape differs from the MSVC compact form, but semantics
 * are preserved: the __try body matches the original logic exactly; the
 * __except handler catches access violations on bad pointer arguments.
 *
 * See docs/seh-handling.md for the full design rationale.
 */

/*
 * Xbox kernel (xboxkrnl) NT import declarations and types.
 *
 * NTSTATUS/ULONG/HANDLE and the OBJECT_ATTRIBUTES/IO_STATUS_BLOCK layouts are
 * not defined in common.h, so each TU that touches the NT API redefines them
 * locally (mirrors src/halo/cseries/xcontent.c).  These resolve to the
 * xboxkrnl.exe import thunks (NtOpenFile @202, NtQueryVolumeInformationFile
 * @218, NtClose @187), not in-binary FUN_ functions.
 */
typedef long NTSTATUS;
typedef unsigned long ULONG;
typedef void *HANDLE;

typedef struct {
  unsigned short Length;
  unsigned short MaximumLength;
  char *Buffer;
} XAPI_ANSI_STRING;

typedef struct {
  HANDLE RootDirectory; /* +0 */
  XAPI_ANSI_STRING *ObjectName; /* +4 */
  ULONG Attributes; /* +8 */
} XAPI_OBJECT_ATTRIBUTES;

typedef struct {
  NTSTATUS Status;
  ULONG *Information;
} XAPI_IO_STATUS_BLOCK;

extern NTSTATUS __stdcall NtOpenFile(HANDLE *FileHandle, ULONG DesiredAccess,
                                     XAPI_OBJECT_ATTRIBUTES *ObjectAttributes,
                                     XAPI_IO_STATUS_BLOCK *IoStatusBlock,
                                     ULONG ShareAccess, ULONG OpenOptions);

extern NTSTATUS __stdcall NtQueryVolumeInformationFile(
  HANDLE FileHandle, XAPI_IO_STATUS_BLOCK *IoStatusBlock, void *FsInformation,
  ULONG Length, ULONG FsInformationClass);

extern void __stdcall NtClose(HANDLE Handle);

extern void __stdcall RtlInitAnsiString(XAPI_ANSI_STRING *DestinationString,
                                        const char *SourceString);

/*
 * FUN_001d7817  (XAPI case-insensitive string compare, 68 bytes)
 *
 * Locale-aware lstrcmpiA implementation. Tries xCompareStringA (internal
 * CompareString) first; on failure (returns 0) falls back to crt_stricmp.
 * Maps CompareString result (1=LESS,2=EQUAL,3=GREATER) to strcmp-style
 * (-1, 0, +1) via result-2.  NULL pointers are handled before the
 * fallback: NULL < non-NULL, NULL == NULL.
 *
 * Confirmed:
 *   - __stdcall: RET 0x8 pops 2 args (a@[EBP+8], b@[EBP+C])
 *   - ESI saves param b across calls
 *   - NEG EAX; SBB EAX,EAX pattern for null-a path: -1 if b!=0, 0 if both null
 *   - xCompareStringA(1, a, -1, b, -1): 5 stack args, __stdcall
 *   - crt_stricmp(a, b): __cdecl fallback (POP ECX; POP ECX cleanup)
 */
int __stdcall FUN_001d7817(const char *a, const char *b)
{
  int result;

  result = xCompareStringA(1, a, -1, b, -1);
  if (result != 0) {
    return result - 2;
  }

  if (a == 0) {
    if (b != 0)
      return -1;
    return 0;
  }

  if (b == 0) {
    return 1;
  }

  return crt_stricmp(a, b);
}

/*
 * FUN_001d789a  (XAPI strncpy helper, 101 bytes)
 *
 * Copies up to `count` characters from `src` to `dst`.  Stops at NUL or
 * when `count` is exhausted.  If `count` is non-zero on entry and the loop
 * exits with chars remaining (src ran short), the last written byte is
 * backed up by one and overwritten with NUL — matching the original loop
 * shape.  Returns `dst`.  On access violation returns NULL.
 *
 * Confirmed:
 *   - __stdcall: RET 0xC pops 3 args (dst@[EBP+8], src@[EBP+C],
 *     count@[EBP+10])
 *   - SEH table at 0x2c1f28: filter = 0x1d78ea (XOR EAX,EAX;INC EAX;RET
 *     → EXCEPTION_EXECUTE_HANDLER=1), handler restores ESP and returns 0
 *   - Loop uses EBX=0 sentinel (XOR EBX,EBX), ECX=src ptr, EAX=dst ptr
 *   - Tracks both ptr copies in the SEH frame ([EBP-0x1c]/[EBP-0x20])
 *
 * Inferred:
 *   - Called from XapiMapLetterToDirectory, XLaunchNewImageA — XAPI layer
 *   - Function is a safe strncpy variant with access-violation guard
 */
char *__stdcall FUN_001d789a(char *dst, const char *src, int count)
{
  __try {
    char *d;
    const char *s;
    d = dst;
    s = src;
    if (count != 0) {
      while (count != 0) {
        if (*s == '\0') {
          if (count != 0)
            goto done_null;
          break;
        }
        *d = *s;
        d++;
        s++;
        count--;
      }
      d--;
    done_null:
      *d = '\0';
    }
  } __except (1) {
    return 0;
  }
  return dst;
}

/*
 * FUN_001d7cb4  (XAPI open-file-and-read helper, 0x6b bytes)
 *
 * Opens a file by ANSI name and, on success, hands the open handle plus a
 * 328-byte scratch buffer to FUN_001d7b37 (the actual reader), then closes
 * the handle.  Returns FUN_001d7b37's result, or the NtOpenFile NTSTATUS on
 * open failure.
 *
 * Confirmed (from delinked FUN_001d7cb4.obj disasm):
 *   - __stdcall, RET 0x4, one pointer argument (filename ANSI_STRING*) at
 *     [EBP+8].
 *   - ESI saves the running NTSTATUS/result across the call chain.
 *   - The [EBP+8] parameter slot is REUSED as NtOpenFile's FileHandle OUT
 *     param: LEA EAX,[EBP+8]; PUSH EAX. After the call it holds the opened
 *     HANDLE, which is then passed to FUN_001d7b37 and NtClose. We model this
 *     by taking the address of the `name` parameter (&name) so the generated
 *     LEA references [EBP+8], preserving the original stack shape.
 *   - OBJECT_ATTRIBUTES (12 bytes, Xbox 3-field form): RootDirectory=0,
 *     ObjectName=&ansi, Attributes=OBJ_CASE_INSENSITIVE(0x40).
 *   - RtlInitAnsiString(&ansi, name); 2 args, __stdcall.
 *   - NtOpenFile(&name, 0x110101, &oa, &iosb, 3, 0x4021); 6 args, __stdcall.
 *   - FUN_001d7b37(handle, buf); 2 args; buffer is EBP-0x164 (0x148=328 bytes,
 *     FUN_001d7b37 reads fields up to ~+0x40, well inside).
 *   - NtClose(handle); 1 arg, __stdcall.
 *
 * Inferred:
 *   - DesiredAccess 0x110101 = SYNCHRONIZE|FILE_READ_DATA|READ_CONTROL.
 *   - OpenOptions 0x4021 = FILE_SYNCHRONOUS_IO_NONALERT|FILE_NON_DIRECTORY_FILE.
 *   - ShareAccess 3 = FILE_SHARE_READ|FILE_SHARE_WRITE.
 *
 * Reuses the shared XAPI_ NT types/externs declared above (same set as
 * FUN_001d7d21); only RtlInitAnsiString is added.  FUN_001d7b37 is the
 * unported reader, called by its kb name with its real (handle, buf) decl.
 */
int __stdcall FUN_001d7cb4(void *name)
{
  XAPI_ANSI_STRING ansi;
  XAPI_OBJECT_ATTRIBUTES oa;
  XAPI_IO_STATUS_BLOCK iosb;
  unsigned char buf[328];
  NTSTATUS status;

  RtlInitAnsiString(&ansi, (const char *)name);
  oa.RootDirectory = 0;
  oa.ObjectName = &ansi;
  oa.Attributes = 0x40; /* OBJ_CASE_INSENSITIVE */

  /* &name reuses the [EBP+8] parameter slot as the FileHandle OUT param,
   * matching the original's LEA EAX,[EBP+8].  After the call `name` holds the
   * opened HANDLE, reused for the read and close. */
  status = NtOpenFile((HANDLE *)&name, 0x110101, &oa, &iosb, 3, 0x4021);
  if (status >= 0) {
    status = FUN_001d7b37(name, buf);
    NtClose(name);
  }
  return status;
}

/*
 * FUN_001d7d21  (XAPI volume-information query, 99 bytes)
 *
 * Opens a file/volume object by name, queries its volume information
 * (FILE_FS_SIZE_INFORMATION, class 3, into a 0x18-byte output buffer), then
 * closes the handle.  Returns the NTSTATUS: NtOpenFile's status on failure,
 * otherwise NtQueryVolumeInformationFile's status (NtClose's result is
 * discarded).  The caller passes a pointer to the object-attributes name
 * field (ObjectName).
 *
 * Confirmed (disasm 0x1d7d21..0x1d7d83):
 *   - __stdcall: RET 0x4, one 4-byte stack arg at [EBP+8]
 *   - Saves ESI only; ESI holds the live NTSTATUS across the query/close pair
 *   - OBJECT_ATTRIBUTES block [EBP-0x14]: RootDirectory(+0)=0 (ANDL $0,..),
 *     ObjectName(+4)=param, Attributes(+8)=0x40
 *   - NtOpenFile takes &[EBP+8], so the returned HANDLE is written back into
 *     the parameter slot; the same slot is then reused as the handle for the
 *     subsequent query/close calls (single-slot dual use).  We reproduce this
 *     by taking the address of the parameter itself (no copy local), forcing
 *     it to its home [EBP+8] slot.
 *   - NtOpenFile(&handle, 0x100001, &oa, &iosb, 3, 0x800021)  -- 6 stack args
 *   - On success (status >= 0):
 *       NtQueryVolumeInformationFile(handle, &iosb, buf, 0x18, 3)  -- 5 args
 *       NtClose(handle)  -- return discarded
 *   - No FPU, no intrinsics, straight-line control flow
 */
int __stdcall FUN_001d7d21(void *object_name_field)
{
  XAPI_OBJECT_ATTRIBUTES oa; /* [EBP-0x14] */
  XAPI_IO_STATUS_BLOCK iosb; /* [EBP-8] */
  char volume_info[24]; /* [EBP-0x2c]: 0x18-byte volume-info output */
  int status;

  oa.RootDirectory = 0;
  oa.ObjectName = (XAPI_ANSI_STRING *)object_name_field;
  oa.Attributes = 0x40;

  /* object_name_field is the [EBP+8] slot: input name ptr, then the handle
     written back by NtOpenFile and reused for the query/close calls. */
  status = NtOpenFile(&object_name_field, 0x100001, &oa, &iosb, 3, 0x800021);
  if (status >= 0) {
    status = NtQueryVolumeInformationFile(object_name_field, &iosb, volume_info,
                                          0x18, 3);
    NtClose(object_name_field);
  }
  return status;
}

/* strncmp (CRT stub) — provided here since _strncmp is internal to the original
 * LIBCMT and not exported from the XBE import table. Behaviorally equivalent to
 * the standard strncmp; called only by csstrncmp in cseries.c. */
int strncmp(const char *s1, const char *s2, unsigned int n)
{
  unsigned int i;
  unsigned char c1;
  unsigned char c2;

  for (i = 0; i < n; i++) {
    c1 = (unsigned char)s1[i];
    c2 = (unsigned char)s2[i];
    if (c1 != c2)
      return c1 < c2 ? -1 : 1;
    if (c1 == '\0')
      return 0;
  }
  return 0;
}

/* fabs is used by valid_real_normal3d_perpendicular; not in XDK libm.
 * VC71 inlines it as x87 FABS — this stub is only reached by the clang build. */
double fabs(double x)
{
  __asm__ __volatile__("fabs" : "+t"(x));
  return x;
}

/* __chkstk (exported as __chkstk after Windows x86 name-mangling of _chkstk).
 * Clang (i386-pc-win32) emits `mov eax, <framesize>; call __chkstk` for any
 * function whose stack frame exceeds one page and — contrary to a long-held
 * assumption — emits NO following `sub esp, eax`.  __chkstk itself must reserve
 * the frame, exactly as the original MSVC runtime does (cachebeta.xbe 0x1d90e0):
 * subtract the size from ESP and relocate the return address.  A bare `ret` here
 * left the frame UNALLOCATED, so a function's locals/spills aliased live ESP and
 * were clobbered by the next argument push — manifested as a NULL+0x99 fault in
 * actor_has_accessible_firing_position (0x25a00) and as corrupted firing-position
 * records driving AI aim in FUN_00025c10 (0x25c10).  Byte-faithful to 0x1d90e0;
 * Xbox fully commits the thread stack, so no page-probing is needed. */
__attribute__((naked)) void _chkstk(void)
{
  __asm__(
    "test %eax, %eax\n\t"  /* frame size == 0? nothing to do */
    "je 1f\n\t"
    "neg %eax\n\t"         /* eax = -size */
    "add %esp, %eax\n\t"   /* eax = esp - size */
    "add $4, %eax\n\t"     /* account for the return-address slot */
    "xchg %eax, %esp\n\t"  /* esp = new frame top; eax = old esp */
    "mov (%eax), %eax\n\t" /* eax = saved return address */
    "push %eax\n\t"        /* re-push it at the new top */
    "1:\n\t"
    "ret\n\t");
}

/* --- XAPILIB:xbox_crt.obj batch drafts (2026-07-26) --- */

/* 0x1d63d5 */
void FUN_001d63d5(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: cmp byte ptr [ebp - 0x1d], 0 -> je 0x1d63e7 */
  FUN_001dd5c8();
  /* cmp eax, 0x7fffffff -> jbe 0x1d641a */
  /* cmp eax, edi -> jne 0x1d6421 */
  /* relift: test dword ptr [ebp + 0xc], 0x3c000100 -> jne 0x1d644a */
  /* relift: cmp dword ptr [esi + 0x17c], edi -> je 0x1d6455 */
  /* relift: test byte ptr [ebp + 0xc], 1 -> jne 0x1d6474 */
  /* cmp ebx, 0x80 -> jae 0x1d668c */
  /* cmp eax, edi -> je 0x1d6541 */
  /* cmp eax, ecx -> jne 0x1d64ea */
  /* cmp (int16_t)eax, 0x80 -> jae 0x1d64ea */
  /* test (char)ecx, 4 -> je 0x1d6521 */
  /* test (char)ecx, 2 -> je 0x1d650e */
  /* cmp eax, 4 -> jbe 0x1d650e */
  /* cmp ebx, 0x20 -> jae 0x1d65b4 */
  /* test edx, edx -> jne 0x1d65d6 */
  /* test ecx, ecx -> jne 0x1d6644 */
  /* test ecx, ecx -> jne 0x1d65ff */
  /* test ecx, ecx -> je 0x1d6695 */
  FUN_001d8750(0);
  /* cmp ebx, 0x40 -> jae 0x1d6613 */
  /* test edx, edx -> je 0x1d65dd */
  /* test ecx, ecx -> jne 0x1d6644 */
  /* test ecx, ecx -> je 0x1d6695 */
  FUN_001d8750(0);
  /* cmp ebx, 0x60 -> jae 0x1d6658 */
  /* test eax, eax -> jne 0x1d6672 */
  /* test ecx, ecx -> je 0x1d6695 */
  FUN_001d8750(0);
  /* test eax, eax -> je 0x1d6695 */
  FUN_001d8750(0);
  /* relift: cmp ebx, dword ptr [esi + 0x1c] -> ja 0x1d6b4e */
  /* cmp esi, eax -> je 0x1d66b8 */
  /* cmp ecx, ebx -> jae 0x1d66d0 */
  FUN_001d5411();
  /* test edi, edi -> je 0x1d6b3d */
  /* cmp eax, ecx -> jne 0x1d671c */
  /* cmp (int16_t)eax, 0x80 -> jae 0x1d671c */
  /* test (char)ecx, 4 -> je 0x1d6756 */
  /* test (char)ecx, 2 -> je 0x1d6740 */
  /* cmp eax, 4 -> jbe 0x1d6740 */
  /* test ebx, ebx -> je 0x1d6aef */
  /* cmp ebx, 1 -> jne 0x1d67a8 */
  /* test dl, 0x10 -> je 0x1d6887 */
  /* cmp (int16_t)ebx, 0x80 -> jae 0x1d6833 */
  /* relift: cmp dword ptr [edi], edi -> jne 0x1d6863 */
  /* cmp edx, edi -> je 0x1d685d */
  /* relift: cmp (int16_t)ebx, word ptr [ecx] -> jbe 0x1d685d */
  /* test (char)ecx, 1 -> je 0x1d694a */
  /* cmp (int16_t)ebx, 0x80 -> jae 0x1d6906 */
  /* relift: cmp dword ptr [edi], edi -> jne 0x1d6936 */
  /* cmp edx, edi -> je 0x1d6930 */
  /* relift: cmp (int16_t)ebx, word ptr [ecx] -> jbe 0x1d6930 */
  /* cmp ecx, edx -> jne 0x1d69ae */
  /* cmp (int16_t)ecx, 0x80 -> jae 0x1d69ae */
  /* test (char)ecx, 4 -> je 0x1d69f1 */
  /* test (char)ecx, 2 -> je 0x1d69d8 */
  /* cmp eax, 4 -> jbe 0x1d69d8 */
  /* cmp ebx, 0xff00 -> ja 0x1d6ac7 */
  /* relift: test byte ptr [esi + 5], 0x10 -> jne 0x1d6a21 */
  /* cmp (int16_t)ebx, 0x80 -> jae 0x1d6a83 */
  /* relift: cmp dword ptr [edi], edi -> jne 0x1d6ab3 */
  /* cmp edx, edi -> je 0x1d6aad */
  /* relift: cmp (int16_t)ebx, word ptr [ecx] -> jbe 0x1d6aad */
  FUN_001d4cd9();
  /* relift: test byte ptr [esi + 5], 0x10 -> je 0x1d6aef */
  /* relift: test byte ptr [ebp - 0x3d], 0x10 -> je 0x1d6b01 */
  /* relift: test byte ptr [ebp + 0xc], 8 -> je 0x1d6b16 */
  /* relift: test byte ptr [edi + 5], 2 -> je 0x1d6c60 */
  FUN_001d4dd3();
  /* relift: test byte ptr [esi + 0x14], 2 -> je 0x1d6c01 */
  /* cmp eax, edi -> jl 0x1d6c0b */
  /* relift: test byte ptr [ebp + 0xc], 4 -> je 0x1d6c60 */
  /* test ecx, ecx -> je 0x1d6c7e */
  /* relift: FUN_001d6c92(0, 0); */
  __SEH_epilog();
  /* relift: cmp byte ptr [ebp - 0x1d], 0 -> je 0x1d6ca7 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d6ca8 */
void FUN_001d6ca8(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001dd5c8();
  /* test ecx, ecx -> jne 0x1d6cd2 */
  /* test (char)eax, 1 -> jne 0x1d6cf3 */
  /* relift: test byte ptr [edi + 5], 8 -> jne 0x1d6e00 */
  FUN_001d4a34();
  /* cmp ecx, 0x80 -> jae 0x1d6d84 */
  /* relift: cmp dword ptr [edx], edx -> jne 0x1d6d63 */
  /* relift: cmp ecx, dword ptr [esi + 0x28] -> jb 0x1d6da0 */
  /* relift: cmp edx, dword ptr [esi + 0x2c] -> jb 0x1d6da0 */
  FUN_001d5598();
  /* cmp ecx, 0xff00 -> ja 0x1d6df6 */
  /* cmp esi, ecx -> je 0x1d6dd8 */
  /* relift: cmp (int16_t)edi, word ptr [edx] -> jbe 0x1d6dd8 */
  FUN_001d4cd9();
  /* relift: cmp byte ptr [ebp - 0x1d], 0 -> je 0x1d6e2c */
  /* test eax, eax -> jge 0x1d6e4e */
  FUN_001d6e65();
  __SEH_epilog();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d6e65 */
void FUN_001d6e65(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: cmp byte ptr [ebp - 0x1d], 0 -> je 0x1d6e77 */
  FUN_001dd5c8();
  /* relift: test byte ptr [ebp + 0xc], 1 -> jne 0x1d6ead */
  /* test dl, 1 -> je 0x1d6ff9 */
  /* test (char)ecx, 7 -> jne 0x1d6ff9 */
  /* relift: cmp byte ptr [eax + 4], 0x40 -> jae 0x1d6ff9 */
  /* test dl, 8 -> je 0x1d6f1d */
  /* cmp eax, edi -> jl 0x1d6ff9 */
  FUN_001d4a34();
  /* relift: cmp ecx, dword ptr [esi + 0x28] -> jb 0x1d6f51 */
  /* relift: cmp edx, dword ptr [esi + 0x2c] -> jb 0x1d6f51 */
  FUN_001d5598();
  /* cmp ecx, 0xff00 -> ja 0x1d6fed */
  /* cmp (int16_t)ebx, 0x80 -> jae 0x1d6fab */
  /* relift: cmp dword ptr [edx], edx -> jne 0x1d6fcf */
  /* cmp edi, edx -> je 0x1d6fcc */
  /* relift: cmp (int16_t)ebx, word ptr [ecx] -> jbe 0x1d6fcc */
  FUN_001d4cd9();
  /* relift: FUN_001d7028(0, 0); */
  __SEH_epilog();
  /* relift: cmp byte ptr [ebp - 0x1d], 0 -> je 0x1d703a */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d703b */
void FUN_001d703b(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001dd5c8();
  /* test esi, esi -> je 0x1d706c */
  /* cmp edx, 0x7fffffff -> jbe 0x1d7073 */
  /* test edx, edx -> jne 0x1d7078 */
  /* relift: test dword ptr [ebp + 0xc], 0x3c000100 -> jne 0x1d709b */
  /* relift: cmp dword ptr [eax + 0x17c], 0 -> jne 0x1d709b */
  /* relift: test byte ptr [esi - 0xb], 2 -> je 0x1d70a1 */
  /* relift: test byte ptr [ebp + 0xc], 1 -> jne 0x1d70bf */
  /* test (char)eax, 1 -> je 0x1d76e4 */
  /* cmp edi, edx -> ja 0x1d7525 */
  /* cmp edi, edx -> jne 0x1d7143 */
  /* test (char)ecx, (char)ecx -> je 0x1d7152 */
  /* relift: test byte ptr [ebx + 5], 2 -> je 0x1d7175 */
  /* cmp ecx, esi -> jbe 0x1d71a5 */
  /* relift: test byte ptr [ebp + 0xc], 8 -> je 0x1d71a5 */
  /* cmp ecx, edx -> je 0x1d7683 */
  /* test (char)eax, 8 -> je 0x1d71ff */
  /* test eax, eax -> jl 0x1d7683 */
  /* test (char)eax, 0x10 -> je 0x1d72c3 */
  /* cmp (int16_t)edi, 0x80 -> jae 0x1d7291 */
  /* relift: cmp dword ptr [eax], eax -> jne 0x1d72b5 */
  /* cmp edx, eax -> je 0x1d72b2 */
  /* relift: cmp (int16_t)edi, word ptr [ecx] -> jbe 0x1d72b2 */
  /* test (char)eax, 1 -> je 0x1d737d */
  /* cmp (int16_t)edi, 0x80 -> jae 0x1d7336 */
  /* relift: cmp dword ptr [eax], eax -> jne 0x1d7369 */
  /* cmp edx, eax -> je 0x1d7363 */
  /* relift: cmp (int16_t)edi, word ptr [ecx] -> jbe 0x1d7363 */
  /* cmp eax, ecx -> jne 0x1d73e3 */
  /* cmp (int16_t)eax, 0x80 -> jae 0x1d73e3 */
  /* test (char)ecx, 4 -> je 0x1d7429 */
  /* test (char)ecx, 2 -> je 0x1d7410 */
  /* cmp eax, 4 -> jbe 0x1d7410 */
  /* cmp edi, 0xff00 -> ja 0x1d7516 */
  /* relift: test byte ptr [esi + 5], 0x10 -> jne 0x1d7458 */
  /* cmp (int16_t)edi, 0x80 -> jae 0x1d74bf */
  /* relift: cmp dword ptr [eax], eax -> jne 0x1d74ef */
  /* cmp edx, eax -> je 0x1d74e9 */
  /* relift: cmp (int16_t)edi, word ptr [ecx] -> jbe 0x1d74e9 */
  FUN_001d4cd9();
  /* test (char)ecx, (char)ecx -> jne 0x1d7544 */
  FUN_001d4ec6();
  /* test (char)eax, (char)eax -> jne 0x1d7683 */
  /* relift: test byte ptr [ebp + 0xc], 0x10 -> je 0x1d7553 */
  /* test (char)eax, 2 -> je 0x1d75c1 */
  FUN_001d4dd3();
  /* test (int16_t)eax, (int16_t)eax -> je 0x1d759a */
  /* test (char)eax, (char)eax -> je 0x1d75d1 */
  FUN_001d5c66();
  /* test eax, eax -> je 0x1d7680 */
  /* relift: test byte ptr [eax + 5], 2 -> je 0x1d7628 */
  FUN_001d4dd3();
  /* relift: test byte ptr [ebx + 5], 2 -> je 0x1d7622 */
  FUN_001d4dd3();
  /* cmp eax, esi -> jb 0x1d7631 */
  memmove((void *)0, (void *)(uintptr_t)0, eax);
  /* relift: cmp dword ptr [ebp + 0x14], esi -> jbe 0x1d766c */
  /* relift: test byte ptr [ebp + 0xc], 8 -> je 0x1d766c */
  FUN_001d6ca8();
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> jne 0x1d76e4 */
  /* relift: test byte ptr [ebp + 0xc], 4 -> je 0x1d76e4 */
  FUN_001d76fc();
  __SEH_epilog();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d76fc */
void FUN_001d76fc(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d771c */
void XAutoPowerDownResetTimer(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1d7749 */
void FUN_001d7749(void)
{
  int eax = 0;

  FUN_001d4464();
  /* test eax, eax -> jne 0x1d77a2 */
  /* mem[0x00632a08] = eax */
  /* mem[0x00632a0c] = 1 */
  XAutoPowerDownResetTimer();

  (void)eax;
}

/* 0x1d77b3 */
void FUN_001d77b3(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  xCompareStringA(0, 0, 0, (char *)(uintptr_t)esi, 0);
  /* test eax, eax -> jne 0x1d7810 */
  /* relift: cmp dword ptr [esp + 8], eax -> je 0x1d7808 */
  /* test esi, esi -> je 0x1d7803 */
  /* relift: cmp dl, byte ptr [esi] -> jne 0x1d77fc */
  /* test (char)ecx, (char)ecx -> je 0x1d77f8 */
  /* relift: cmp dl, byte ptr [esi + 1] -> jne 0x1d77fc */
  /* test (char)ecx, (char)ecx -> jne 0x1d77da */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1d7a59 */
void FUN_001d7a59(void)
{
  int ecx = 0;
  int esi = 0;
  int ebp = 0;

  FUN_001dd5c8();
  /* relift: cmp dword ptr [ebp + 0x10], esi -> je 0x1d7aa7 */
  /* relift: cmp dword ptr [ebp + 0x10], esi -> je 0x1d7a9f */
  /* cmp (int16_t)ecx, (int16_t)esi -> je 0x1d7a9a */
  /* relift: cmp dword ptr [ebp + 0x10], esi -> jne 0x1d7aa4 */
  __SEH_epilog();
  FUN_001dd5c8();
  _wcscat();
  __SEH_epilog();
  FUN_001dd5c8();
  /* relift: cmp dword ptr [ebp + 8], 0 -> je 0x1d7b2d */
  _wcslen((wchar_t *)0);
  __SEH_epilog();

  (void)ecx;
  (void)esi;
  (void)ebp;
}

/* 0x1d7b37 */
int FUN_001d7b37(void *handle, void *buf)
{
  int ebx = 0;
  int edx = 0;
  int edi = 0;

  /* cmp edi, ebx -> jl 0x1d7c53 */
  /* test edi, edi -> jl 0x1d7c53 */
  /* test (char)ebx, (char)ebx -> je 0x1d7beb */
  /* relift: tail-call FUN_001d7b37(); */
  /* test dl, 1 -> je 0x1d7c23 */
  /* test edi, edi -> jl 0x1d7c42 */
  /* test edi, edi -> jge 0x1d7b47 */
  /* cmp edi, 0xc000000f -> jne 0x1d7cac */
  return 0;

  (void)ebx;
  (void)edx;
  (void)edi;
}

/* 0x1d7d84 */
void FUN_001d7d84(void)
{
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp (char)ecx, (char)ebx -> jne 0x1d7d97 */
  FUN_001d789a((char *)(uintptr_t)esi, (char *)(uintptr_t)0, 0);
  /* cmp edi, ebx -> jl 0x1d7e4d */
  /* relift: cmp dword ptr [ebp - 0x2c], ebx -> jne 0x1d7e4d */
  /* relift: cmp dword ptr [ebp - 0x28], ebx -> jne 0x1d7e4d */
  FUN_001d8aef();
  /* cmp esi, ebx -> je 0x1d7e4d */
  XGetSectionSize();
  FUN_001d8b10();
  /* cmp edi, 0xc0000035 -> jne 0x1d7e62 */

  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d7e6b */
void XapiMapLetterToDirectory(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

  /* cmp eax, 0xc0000103 -> jne 0x1d7ecc */
  /* relift: cmp dword ptr [ebp + 0xc], ebx -> jl 0x1d8195 */
  /* cmp (char)ecx, (char)ebx -> jne 0x1d7ee0 */
  /* relift: cmp byte ptr [eax - 1], 0x5c -> je 0x1d7f02 */
  /* cmp dl, (char)ebx -> jne 0x1d7f15 */
  /* relift: cmp dword ptr [ebp + 0x1c], ebx -> je 0x1d7fa6 */
  /* cmp esi, ebx -> je 0x1d8177 */
  FUN_001d8a88();
  FUN_001d8a88();
  FUN_001d8a88();
  /* relift: cmp word ptr [esi], (int16_t)ebx -> je 0x1d8131 */
  /* cmp (char)ecx, (char)ebx -> jne 0x1d7ff5 */
  FUN_001d789a((char *)(uintptr_t)esi, (char *)0x002c2030, 0);
  /* relift: cmp dword ptr [ebp - 0x3c], ebx -> jne 0x1d811c */
  /* relift: cmp dword ptr [ebp - 0x38], ebx -> jne 0x1d811c */
  /* relift: cmp dword ptr [ebp + 0x10], -1 -> je 0x1d80d1 */
  FUN_001d8aef();
  /* cmp esi, ebx -> je 0x1d80d1 */
  XGetSectionSize();
  FUN_001d8b10();
  FUN_001dd6f5();
  /* cmp eax, 0xc0000035 -> jne 0x1d8131 */
  /* relift: cmp dword ptr [ebp + 0xc], ebx -> jl 0x1d8177 */
  /* relift: cmp dword ptr [ebp + 0x1c], -1 -> je 0x1d8154 */
  FUN_001d7d84();
  /* relift: cmp dword ptr [ebp + 0xc], ebx -> jl 0x1d8177 */
  /* relift: cmp dword ptr [ebp - 0x1c], -1 -> je 0x1d8177 */
  FUN_001d7d84();
  /* relift: cmp dword ptr [ebp + 0xc], ebx -> jl 0x1d8195 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)ebp;
}

/* 0x1d819f */
void FUN_001d819f(void)
{
  int eax = 0;

  crt_sprintf((char *)(uintptr_t)eax, (char *)0x002c1e28);
  XapiMapLetterToDirectory();
  /* test eax, eax -> jl 0x1d81f0 */
  XapiMapLetterToDirectory();

  (void)eax;
}

/* 0x1d81f4 */
void XapiBootToDash(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [eax + 8], 0xfffe0000 -> je 0x1d8250 */
  XLaunchNewImageA((char *)0, (void *)(uintptr_t)eax);
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
  /* relift: tail-call XapiBootToDash(); */
  /* cmp eax, esi -> jge 0x1d8342 */
  /* cmp eax, 0xc0000035 -> jne 0x1d829d */
  FUN_001d454b();
  /* cmp esi, eax -> jae 0x1d8364 */
  /* relift: tail-call XapiBootToDash(); */
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

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
