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
 *   - OpenOptions 0x4021 =
 * FILE_SYNCHRONOUS_IO_NONALERT|FILE_NON_DIRECTORY_FILE.
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
 * VC71 inlines it as x87 FABS — this stub is only reached by the clang build.
 */
double fabs(double x)
{
  __asm__ __volatile__("fabs" : "+t"(x));
  return x;
}

/* __chkstk (exported as __chkstk after Windows x86 name-mangling of _chkstk).
 * Clang (i386-pc-win32) emits `mov eax, <framesize>; call __chkstk` for any
 * function whose stack frame exceeds one page and — contrary to a long-held
 * assumption — emits NO following `sub esp, eax`.  __chkstk itself must reserve
 * the frame, exactly as the original MSVC runtime does (cachebeta.xbe
 * 0x1d90e0): subtract the size from ESP and relocate the return address.  A
 * bare `ret` here left the frame UNALLOCATED, so a function's locals/spills
 * aliased live ESP and were clobbered by the next argument push — manifested as
 * a NULL+0x99 fault in actor_has_accessible_firing_position (0x25a00) and as
 * corrupted firing-position records driving AI aim in FUN_00025c10 (0x25c10).
 * Byte-faithful to 0x1d90e0; Xbox fully commits the thread stack, so no
 * page-probing is needed. */
__attribute__((naked)) void _chkstk(void)
{
  __asm__("test %eax, %eax\n\t" /* frame size == 0? nothing to do */
          "je 1f\n\t"
          "neg %eax\n\t" /* eax = -size */
          "add %esp, %eax\n\t" /* eax = esp - size */
          "add $4, %eax\n\t" /* account for the return-address slot */
          "xchg %eax, %esp\n\t" /* esp = new frame top; eax = old esp */
          "mov (%eax), %eax\n\t" /* eax = saved return address */
          "push %eax\n\t" /* re-push it at the new top */
          "1:\n\t"
          "ret\n\t");
}

/* --- XAPILIB:xbox_crt.obj batch drafts (2026-07-26) --- */

/* FUN_001d63d5 (0x1d63d5) — XBE naked draft (batch 250). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_001d63d5(void)
{
  __asm__ volatile(
      "cmpb $0, -0x1d(%%ebp)\n\t"
      "je .LFUN_001d63d5_1\n\t"
      "pushl 0x580(%%ebx)\n\t"
      "call *0x253098\n\t"
      ".LFUN_001d63d5_1:\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_001d63d5: clang naked draft required"
#endif


/* FUN_001d6ca8 (0x1d6ca8) — XBE naked draft (batch 241). */
#if defined(__clang__)
static void (*const b1d6ca8_c1dd5c8)(void) = FUN_001dd5c8;
static void (*const b1d6ca8_c1d4a34)(void) = FUN_001d4a34;
static void (*const b1d6ca8_c1d5598)(void) = FUN_001d5598;
static void (*const b1d6ca8_c1d4cd9)(void) = FUN_001d4cd9;
static void (*const b1d6ca8_c1d6e65)(void) = FUN_001d6e65;
static void (*const b1d6ca8_c1dd601)(void) = __SEH_epilog;

__attribute__((naked, noinline))
void FUN_001d6ca8(void)
{
  __asm__ volatile(
      "pushl $0x50\n\t"
      "pushl $0x2c1ec8\n\t"
      "call *%[c1dd5c8]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%esi, %%ebx\n\t"
      "movl %%ebx, -0x1c(%%ebp)\n\t"
      "andb $0, -0x1d(%%ebp)\n\t"
      "movb $1, -0x1e(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_001d6ca8_1\n\t"
      "movb $1, %%al\n\t"
      "jmp .LFUN_001d6ca8_12\n\t"
      ".LFUN_001d6ca8_1:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "orl 0x18(%%esi), %%eax\n\t"
      "leal -0x10(%%ecx), %%edi\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "testb $1, %%al\n\t"
      "jne .LFUN_001d6ca8_2\n\t"
      "pushl 0x580(%%esi)\n\t"
      "call *0x25309c\n\t"
      "movb $1, -0x1d(%%ebp)\n\t"
      ".LFUN_001d6ca8_2:\n\t"
      "testb $8, 0x5(%%edi)\n\t"
      "jne .LFUN_001d6ca8_9\n\t"
      "movzwl (%%edi), %%eax\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "pushl $0\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d4a34]\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "cmpl $0x80, %%ecx\n\t"
      "jae .LFUN_001d6ca8_4\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x5(%%eax), %%cl\n\t"
      "andl $0x10, %%ecx\n\t"
      "movb %%cl, 0x5(%%eax)\n\t"
      "movzwl -0x24(%%ebp), %%ecx\n\t"
      "leal 0x180(%%esi,%%ecx,8), %%edx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "cmpl %%edx, (%%edx)\n\t"
      "jne .LFUN_001d6ca8_3\n\t"
      "movzwl (%%eax), %%ecx\n\t"
      "movl %%ecx, %%edi\n\t"
      "shrl $3, %%edi\n\t"
      "movl %%edi, -0x30(%%ebp)\n\t"
      "andl $7, %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "incl %%ebx\n\t"
      "shll %%cl, %%ebx\n\t"
      "movl %%ebx, -0x34(%%ebp)\n\t"
      "leal 0x160(%%edi,%%esi,1), %%edi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb (%%edi), %%cl\n\t"
      "orl %%ebx, %%ecx\n\t"
      "movb %%cl, (%%edi)\n\t"
      "movl -0x1c(%%ebp), %%ebx\n\t"
      ".LFUN_001d6ca8_3:\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "movl 0x4(%%edx), %%edi\n\t"
      "movl %%edi, -0x3c(%%ebp)\n\t"
      "leal 0x8(%%eax), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl %%edi, 0xc(%%eax)\n\t"
      "movl %%ecx, (%%edi)\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "addl %%eax, 0x30(%%esi)\n\t"
      "jmp .LFUN_001d6ca8_11\n\t"
      ".LFUN_001d6ca8_4:\n\t"
      "cmpl 0x28(%%esi), %%ecx\n\t"
      "jb .LFUN_001d6ca8_5\n\t"
      "movl 0x30(%%esi), %%edx\n\t"
      "addl %%ecx, %%edx\n\t"
      "cmpl 0x2c(%%esi), %%edx\n\t"
      "jb .LFUN_001d6ca8_5\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d5598]\n\t"
      "jmp .LFUN_001d6ca8_11\n\t"
      ".LFUN_001d6ca8_5:\n\t"
      "cmpl $0xff00, %%ecx\n\t"
      "ja .LFUN_001d6ca8_8\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x5(%%eax), %%cl\n\t"
      "andl $0x10, %%ecx\n\t"
      "movb %%cl, 0x5(%%eax)\n\t"
      "addl $0x180, %%esi\n\t"
      "movl %%esi, -0x40(%%ebp)\n\t"
      "movl (%%esi), %%ecx\n\t"
      ".LFUN_001d6ca8_6:\n\t"
      "movl %%ecx, -0x44(%%ebp)\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "je .LFUN_001d6ca8_7\n\t"
      "leal -0x8(%%ecx), %%edx\n\t"
      "movl %%edx, -0x48(%%ebp)\n\t"
      "movw -0x24(%%ebp), %%di\n\t"
      "cmpw (%%edx), %%di\n\t"
      "jbe .LFUN_001d6ca8_7\n\t"
      "movl (%%ecx), %%ecx\n\t"
      "jmp .LFUN_001d6ca8_6\n\t"
      ".LFUN_001d6ca8_7:\n\t"
      "movl %%ecx, -0x4c(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%esi\n\t"
      "movl %%esi, -0x50(%%ebp)\n\t"
      "leal 0x8(%%eax), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl %%esi, 0xc(%%eax)\n\t"
      "movl %%edx, (%%esi)\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "addl %%eax, 0x30(%%ebx)\n\t"
      "jmp .LFUN_001d6ca8_11\n\t"
      ".LFUN_001d6ca8_8:\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d4cd9]\n\t"
      "jmp .LFUN_001d6ca8_11\n\t"
      ".LFUN_001d6ca8_9:\n\t"
      "leal -0x20(%%edi), %%eax\n\t"
      "movl %%eax, -0x54(%%ebp)\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x58(%%ebp)\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "movl %%eax, -0x5c(%%ebp)\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "cmpb $0, -0x1d(%%ebp)\n\t"
      "je .LFUN_001d6ca8_10\n\t"
      "pushl 0x580(%%esi)\n\t"
      "call *0x253098\n\t"
      "andb $0, -0x1d(%%ebp)\n\t"
      ".LFUN_001d6ca8_10:\n\t"
      "andl $0, -0x24(%%ebp)\n\t"
      "pushl $0x8000\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x54(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x25314c\n\t"
      "movl %%eax, -0x60(%%ebp)\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .LFUN_001d6ca8_11\n\t"
      "andb $0, -0x1e(%%ebp)\n\t"
      ".LFUN_001d6ca8_11:\n\t"
      "orl $0xffffffff, -0x4(%%ebp)\n\t"
      "call *%[c1d6e65]\n\t"
      "movb -0x1e(%%ebp), %%al\n\t"
      ".LFUN_001d6ca8_12:\n\t"
      "call *%[c1dd601]\n\t"
      "ret\n\t"
      :
      : [c1dd5c8] "m"(b1d6ca8_c1dd5c8), [c1d4a34] "m"(b1d6ca8_c1d4a34), [c1d5598] "m"(b1d6ca8_c1d5598), [c1d4cd9] "m"(b1d6ca8_c1d4cd9), [c1d6e65] "m"(b1d6ca8_c1d6e65), [c1dd601] "m"(b1d6ca8_c1dd601)
      : "memory");
}
#else
#error "FUN_001d6ca8: clang naked draft required"
#endif


/* FUN_001d6e65 (0x1d6e65) — XBE naked draft (batch 263). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_001d6e65(void)
{
  __asm__ volatile(
      "cmpb $0, -0x1d(%%ebp)\n\t"
      "je .LFUN_001d6e65_1\n\t"
      "pushl 0x580(%%ebx)\n\t"
      "call *0x253098\n\t"
      ".LFUN_001d6e65_1:\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_001d6e65: clang naked draft required"
#endif


/* FUN_001d703b (0x1d703b) — XBE naked draft (batch 241). */
#if defined(__clang__)
static void (*const b1d703b_c1dd5c8)(void) = FUN_001dd5c8;
static void (*const b1d703b_c1d4cd9)(void) = FUN_001d4cd9;
static void (*const b1d703b_c1d4ec6)(void) = FUN_001d4ec6;
static void (*const b1d703b_c1d4dd3)(void) = FUN_001d4dd3;
static void (*const b1d703b_c1d5c66)(void) = FUN_001d5c66;
static void * (*const b1d703b_c1da290)(void *dest, const void *src, size_t size) = memmove;
static void (*const b1d703b_c1d6ca8)(void) = FUN_001d6ca8;
static void (*const b1d703b_c1d76fc)(void) = FUN_001d76fc;
static void (*const b1d703b_c1dd601)(void) = __SEH_epilog;

__attribute__((naked, noinline))
void FUN_001d703b(void)
{
  __asm__ volatile(
      "pushl $0x120\n\t"
      "pushl $0x2c1ef0\n\t"
      "call *%[c1dd5c8]\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "andb $0, -0x1d(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_001d703b_1\n\t"
      "movl 0x18(%%eax), %%ecx\n\t"
      "orl %%ecx, 0xc(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "cmpl $0x7fffffff, %%edx\n\t"
      "jbe .LFUN_001d703b_2\n\t"
      ".LFUN_001d703b_1:\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .LFUN_001d703b_50\n\t"
      ".LFUN_001d703b_2:\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .LFUN_001d703b_3\n\t"
      "incl %%edx\n\t"
      ".LFUN_001d703b_3:\n\t"
      "movl 0x50(%%eax), %%ecx\n\t"
      "addl %%edx, %%ecx\n\t"
      "andl 0x54(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "testl $0x3c000100, 0xc(%%ebp)\n\t"
      "jne .LFUN_001d703b_4\n\t"
      "cmpl $0, 0x17c(%%eax)\n\t"
      "jne .LFUN_001d703b_4\n\t"
      "testb $2, -0xb(%%esi)\n\t"
      "je .LFUN_001d703b_5\n\t"
      ".LFUN_001d703b_4:\n\t"
      "addl $0x10, %%ecx\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      ".LFUN_001d703b_5:\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "testb $1, 0xc(%%ebp)\n\t"
      "jne .LFUN_001d703b_6\n\t"
      "pushl 0x580(%%eax)\n\t"
      "call *0x25309c\n\t"
      "movb $1, -0x1d(%%ebp)\n\t"
      "xorl $1, 0xc(%%ebp)\n\t"
      ".LFUN_001d703b_6:\n\t"
      "movl $1, -0x4(%%ebp)\n\t"
      "leal -0x10(%%esi), %%ebx\n\t"
      "movl %%ebx, -0x28(%%ebp)\n\t"
      "movb 0x5(%%ebx), %%al\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_001d703b_49\n\t"
      "movb %%al, %%cl\n\t"
      "andb $8, %%cl\n\t"
      "je .LFUN_001d703b_7\n\t"
      "leal -0x20(%%ebx), %%edx\n\t"
      "movl %%edx, -0x2c(%%ebp)\n\t"
      "movzwl (%%ebx), %%eax\n\t"
      "movl 0x18(%%edx), %%esi\n\t"
      "subl %%eax, %%esi\n\t"
      "movl %%esi, -0x30(%%ebp)\n\t"
      "leal (%%eax,%%esi,1), %%edx\n\t"
      "shrl $4, %%edx\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "addl $0x20, -0x24(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%edi\n\t"
      "addl $0xfff, %%edi\n\t"
      "andl $0xfffff000, %%edi\n\t"
      "movl %%edi, -0x24(%%ebp)\n\t"
      "jmp .LFUN_001d703b_8\n\t"
      ".LFUN_001d703b_7:\n\t"
      "movzwl (%%ebx), %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      "movzbl 0x6(%%ebx), %%edi\n\t"
      "movl %%edx, %%esi\n\t"
      "shll $4, %%esi\n\t"
      "subl %%edi, %%esi\n\t"
      "movl %%esi, -0x30(%%ebp)\n\t"
      ".LFUN_001d703b_8:\n\t"
      "movl -0x24(%%ebp), %%edi\n\t"
      "shrl $4, %%edi\n\t"
      "movl %%edi, -0x38(%%ebp)\n\t"
      "cmpl %%edx, %%edi\n\t"
      "ja .LFUN_001d703b_37\n\t"
      "incl %%edi\n\t"
      "cmpl %%edx, %%edi\n\t"
      "jne .LFUN_001d703b_9\n\t"
      "movl %%edi, -0x38(%%ebp)\n\t"
      "addl $0x10, -0x24(%%ebp)\n\t"
      ".LFUN_001d703b_9:\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_001d703b_10\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "subl 0x14(%%ebp), %%eax\n\t"
      "movw %%ax, (%%ebx)\n\t"
      "jmp .LFUN_001d703b_12\n\t"
      ".LFUN_001d703b_10:\n\t"
      "testb $2, 0x5(%%ebx)\n\t"
      "je .LFUN_001d703b_11\n\t"
      "shll $4, %%eax\n\t"
      "leal -0x10(%%eax,%%ebx,1), %%eax\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "leal -0x10(%%ecx,%%ebx,1), %%edi\n\t"
      "movl %%edi, -0x40(%%ebp)\n\t"
      "movl %%eax, %%esi\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      ".byte 0xa5\n\t"
      ".LFUN_001d703b_11:\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "subl 0x14(%%ebp), %%eax\n\t"
      "movb %%al, 0x6(%%ebx)\n\t"
      ".LFUN_001d703b_12:\n\t"
      "movl -0x30(%%ebp), %%esi\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "cmpl %%esi, %%ecx\n\t"
      "jbe .LFUN_001d703b_13\n\t"
      "testb $8, 0xc(%%ebp)\n\t"
      "je .LFUN_001d703b_13\n\t"
      "subl %%esi, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "addl %%esi, %%edi\n\t"
      "movl %%ecx, %%esi\n\t"
      "shrl $2, %%ecx\n\t"
      "rep stosl\n\t"
      "movl %%esi, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep stosb\n\t"
      ".LFUN_001d703b_13:\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "je .LFUN_001d703b_48\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x5(%%ebx), %%al\n\t"
      "andl $0xfffffffe, %%eax\n\t"
      "movb %%al, -0x41(%%ebp)\n\t"
      "testb $8, %%al\n\t"
      "je .LFUN_001d703b_14\n\t"
      "addl $-0x20, %%ebx\n\t"
      "movl %%ebx, -0x48(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "leal (%%ebx,%%eax,1), %%ecx\n\t"
      "movl %%ecx, -0x4c(%%ebp)\n\t"
      "shll $4, %%edx\n\t"
      "subl %%eax, %%edx\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      "pushl $0x8000\n\t"
      "leal -0x50(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x4c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x25314c\n\t"
      "movl %%eax, -0x54(%%ebp)\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d703b_48\n\t"
      "movl -0x50(%%ebp), %%eax\n\t"
      "subl %%eax, 0x18(%%ebx)\n\t"
      "jmp .LFUN_001d703b_48\n\t"
      ".LFUN_001d703b_14:\n\t"
      "movl %%ecx, %%esi\n\t"
      "shll $4, %%esi\n\t"
      "addl %%ebx, %%esi\n\t"
      "movl %%esi, -0x58(%%ebp)\n\t"
      "movb %%al, 0x5(%%esi)\n\t"
      "movw %%cx, 0x2(%%esi)\n\t"
      "movb 0x4(%%ebx), %%dl\n\t"
      "movb %%dl, 0x4(%%esi)\n\t"
      "movzwl (%%ebx), %%edi\n\t"
      "subl %%ecx, %%edi\n\t"
      "movl %%edi, -0x5c(%%ebp)\n\t"
      "movw %%cx, (%%ebx)\n\t"
      "movb 0x5(%%ebx), %%cl\n\t"
      "andb $0xef, %%cl\n\t"
      "movb %%cl, 0x5(%%ebx)\n\t"
      "testb $0x10, %%al\n\t"
      "je .LFUN_001d703b_19\n\t"
      "movzbl 0x4(%%esi), %%ecx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x60(%%eax,%%ecx,4), %%ecx\n\t"
      "movl %%ecx, -0x60(%%ebp)\n\t"
      "movl %%esi, 0x40(%%ecx)\n\t"
      "movw %%di, (%%esi)\n\t"
      "movb 0x5(%%esi), %%cl\n\t"
      "andb $0xf8, %%cl\n\t"
      "movb %%cl, 0x5(%%esi)\n\t"
      "cmpw $0x80, %%di\n\t"
      "jae .LFUN_001d703b_15\n\t"
      "movzwl %%di, %%ecx\n\t"
      "leal 0x180(%%eax,%%ecx,8), %%eax\n\t"
      "movl %%eax, -0x64(%%ebp)\n\t"
      "cmpl %%eax, (%%eax)\n\t"
      "jne .LFUN_001d703b_18\n\t"
      "movzwl (%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $3, %%edx\n\t"
      "movl %%edx, -0x68(%%ebp)\n\t"
      "andl $7, %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "incl %%ebx\n\t"
      "shll %%cl, %%ebx\n\t"
      "movl %%ebx, -0x6c(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal 0x160(%%edx,%%ecx,1), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb (%%ecx), %%dl\n\t"
      "orl %%ebx, %%edx\n\t"
      "movb %%dl, (%%ecx)\n\t"
      "jmp .LFUN_001d703b_18\n\t"
      ".LFUN_001d703b_15:\n\t"
      "leal 0x180(%%eax), %%edx\n\t"
      "movl %%edx, -0x64(%%ebp)\n\t"
      "movl (%%edx), %%eax\n\t"
      ".LFUN_001d703b_16:\n\t"
      "movl %%eax, -0x70(%%ebp)\n\t"
      "cmpl %%eax, %%edx\n\t"
      "je .LFUN_001d703b_17\n\t"
      "leal -0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x74(%%ebp)\n\t"
      "cmpw (%%ecx), %%di\n\t"
      "jbe .LFUN_001d703b_17\n\t"
      "movl (%%eax), %%eax\n\t"
      "jmp .LFUN_001d703b_16\n\t"
      ".LFUN_001d703b_17:\n\t"
      "movl %%eax, -0x64(%%ebp)\n\t"
      ".LFUN_001d703b_18:\n\t"
      "movl %%eax, -0x78(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x7c(%%ebp)\n\t"
      "jmp .LFUN_001d703b_35\n\t"
      ".LFUN_001d703b_19:\n\t"
      "movl %%edi, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "leal (%%eax,%%esi,1), %%ebx\n\t"
      "movl %%ebx, -0x80(%%ebp)\n\t"
      "movb 0x5(%%ebx), %%al\n\t"
      "testb $1, %%al\n\t"
      "je .LFUN_001d703b_24\n\t"
      "movw %%di, (%%esi)\n\t"
      "movw %%di, 0x2(%%ebx)\n\t"
      "movb 0x5(%%esi), %%al\n\t"
      "andb $0xf8, %%al\n\t"
      "movb %%al, 0x5(%%esi)\n\t"
      "cmpw $0x80, %%di\n\t"
      "jae .LFUN_001d703b_20\n\t"
      "movzwl %%di, %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal 0x180(%%ecx,%%eax,8), %%eax\n\t"
      "movl %%eax, -0x84(%%ebp)\n\t"
      "cmpl %%eax, (%%eax)\n\t"
      "jne .LFUN_001d703b_23\n\t"
      "movzwl (%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $3, %%edx\n\t"
      "movl %%edx, -0x88(%%ebp)\n\t"
      "andl $7, %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "incl %%ebx\n\t"
      "shll %%cl, %%ebx\n\t"
      "movl %%ebx, -0x8c(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "leal 0x160(%%edx,%%ecx,1), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb (%%ecx), %%dl\n\t"
      "orl %%ebx, %%edx\n\t"
      "movb %%dl, (%%ecx)\n\t"
      "jmp .LFUN_001d703b_23\n\t"
      ".LFUN_001d703b_20:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "addl $0x180, %%edx\n\t"
      "movl %%edx, -0x84(%%ebp)\n\t"
      "movl (%%edx), %%eax\n\t"
      ".LFUN_001d703b_21:\n\t"
      "movl %%eax, -0x90(%%ebp)\n\t"
      "cmpl %%eax, %%edx\n\t"
      "je .LFUN_001d703b_22\n\t"
      "leal -0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x94(%%ebp)\n\t"
      "cmpw (%%ecx), %%di\n\t"
      "jbe .LFUN_001d703b_22\n\t"
      "movl (%%eax), %%eax\n\t"
      "jmp .LFUN_001d703b_21\n\t"
      ".LFUN_001d703b_22:\n\t"
      "movl %%eax, -0x84(%%ebp)\n\t"
      ".LFUN_001d703b_23:\n\t"
      "movl %%eax, -0x98(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0x9c(%%ebp)\n\t"
      "jmp .LFUN_001d703b_35\n\t"
      ".LFUN_001d703b_24:\n\t"
      "movb %%al, 0x5(%%esi)\n\t"
      "movl 0x8(%%ebx), %%eax\n\t"
      "movl %%eax, -0xa0(%%ebp)\n\t"
      "movl 0xc(%%ebx), %%ecx\n\t"
      "movl %%ecx, -0xa4(%%ebp)\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jne .LFUN_001d703b_25\n\t"
      "movw (%%ebx), %%ax\n\t"
      "cmpw $0x80, %%ax\n\t"
      "jae .LFUN_001d703b_25\n\t"
      "movzwl %%ax, %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "shrl $3, %%eax\n\t"
      "movl %%eax, -0xa8(%%ebp)\n\t"
      "andl $7, %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "incl %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl %%edx, -0xac(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "leal 0x160(%%eax,%%edx,1), %%eax\n\t"
      "movl %%eax, -0xb0(%%ebp)\n\t"
      "movzbl (%%eax), %%eax\n\t"
      "xorl -0xac(%%ebp), %%eax\n\t"
      "movl -0xb0(%%ebp), %%ecx\n\t"
      "movb %%al, (%%ecx)\n\t"
      "jmp .LFUN_001d703b_26\n\t"
      ".LFUN_001d703b_25:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      ".LFUN_001d703b_26:\n\t"
      "movb 0x5(%%ebx), %%cl\n\t"
      "testb $4, %%cl\n\t"
      "je .LFUN_001d703b_28\n\t"
      "movzwl (%%ebx), %%eax\n\t"
      "shll $4, %%eax\n\t"
      "subl $0x18, %%eax\n\t"
      "movl %%eax, -0xb4(%%ebp)\n\t"
      "testb $2, %%cl\n\t"
      "je .LFUN_001d703b_27\n\t"
      "cmpl $4, %%eax\n\t"
      "jbe .LFUN_001d703b_27\n\t"
      "subl $4, %%eax\n\t"
      "movl %%eax, -0xb4(%%ebp)\n\t"
      ".LFUN_001d703b_27:\n\t"
      "pushl $0xfeeefeee\n\t"
      "pushl %%eax\n\t"
      "leal 0x18(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x253248\n\t"
      "movl %%eax, -0xb8(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      ".LFUN_001d703b_28:\n\t"
      "movzwl (%%ebx), %%eax\n\t"
      "subl %%eax, 0x30(%%edx)\n\t"
      "movzwl (%%ebx), %%eax\n\t"
      "addl %%eax, %%edi\n\t"
      "movl %%edi, -0x5c(%%ebp)\n\t"
      "cmpl $0xff00, %%edi\n\t"
      "ja .LFUN_001d703b_36\n\t"
      "movw %%di, (%%esi)\n\t"
      "testb $0x10, 0x5(%%esi)\n\t"
      "jne .LFUN_001d703b_29\n\t"
      "movl %%edi, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "movw %%di, 0x2(%%eax,%%esi,1)\n\t"
      "jmp .LFUN_001d703b_30\n\t"
      ".LFUN_001d703b_29:\n\t"
      "movzbl 0x4(%%esi), %%eax\n\t"
      "movl 0x60(%%edx,%%eax,4), %%eax\n\t"
      "movl %%eax, -0xbc(%%ebp)\n\t"
      "movl %%esi, 0x40(%%eax)\n\t"
      ".LFUN_001d703b_30:\n\t"
      "movb 0x5(%%esi), %%al\n\t"
      "andb $0xf8, %%al\n\t"
      "movb %%al, 0x5(%%esi)\n\t"
      "cmpw $0x80, %%di\n\t"
      "jae .LFUN_001d703b_31\n\t"
      "movzwl %%di, %%eax\n\t"
      "leal 0x180(%%edx,%%eax,8), %%eax\n\t"
      "movl %%eax, -0xc0(%%ebp)\n\t"
      "cmpl %%eax, (%%eax)\n\t"
      "jne .LFUN_001d703b_34\n\t"
      "movzwl (%%esi), %%ecx\n\t"
      "movl %%ecx, %%ebx\n\t"
      "shrl $3, %%ebx\n\t"
      "movl %%ebx, -0xc4(%%ebp)\n\t"
      "andl $7, %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "incl %%ebx\n\t"
      "shll %%cl, %%ebx\n\t"
      "movl %%ebx, -0xc8(%%ebp)\n\t"
      "movl -0xc4(%%ebp), %%ecx\n\t"
      "leal 0x160(%%ecx,%%edx,1), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb (%%edx), %%cl\n\t"
      "orl %%ebx, %%ecx\n\t"
      "movb %%cl, (%%edx)\n\t"
      "jmp .LFUN_001d703b_34\n\t"
      ".LFUN_001d703b_31:\n\t"
      "addl $0x180, %%edx\n\t"
      "movl %%edx, -0xc0(%%ebp)\n\t"
      "movl (%%edx), %%eax\n\t"
      ".LFUN_001d703b_32:\n\t"
      "movl %%eax, -0xcc(%%ebp)\n\t"
      "cmpl %%eax, %%edx\n\t"
      "je .LFUN_001d703b_33\n\t"
      "leal -0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, -0xd0(%%ebp)\n\t"
      "cmpw (%%ecx), %%di\n\t"
      "jbe .LFUN_001d703b_33\n\t"
      "movl (%%eax), %%eax\n\t"
      "jmp .LFUN_001d703b_32\n\t"
      ".LFUN_001d703b_33:\n\t"
      "movl %%eax, -0xc0(%%ebp)\n\t"
      ".LFUN_001d703b_34:\n\t"
      "movl %%eax, -0xd4(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, -0xd8(%%ebp)\n\t"
      ".LFUN_001d703b_35:\n\t"
      "leal 0x8(%%esi), %%ecx\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "movl %%edx, 0xc(%%esi)\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "addl %%edi, 0x30(%%eax)\n\t"
      "jmp .LFUN_001d703b_48\n\t"
      ".LFUN_001d703b_36:\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c1d4cd9]\n\t"
      "jmp .LFUN_001d703b_48\n\t"
      ".LFUN_001d703b_37:\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_001d703b_38\n\t"
      "pushl %%edi\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c1d4ec6]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001d703b_48\n\t"
      "movl -0x30(%%ebp), %%esi\n\t"
      ".LFUN_001d703b_38:\n\t"
      "testb $0x10, 0xc(%%ebp)\n\t"
      "je .LFUN_001d703b_39\n\t"
      "andl $0, 0x10(%%ebp)\n\t"
      "jmp .LFUN_001d703b_48\n\t"
      ".LFUN_001d703b_39:\n\t"
      "andw $0xc003, 0xe(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x5(%%ebx), %%al\n\t"
      "testb $2, %%al\n\t"
      "je .LFUN_001d703b_41\n\t"
      "andb $0xf1, 0xd(%%ebp)\n\t"
      "andl $0xe0, %%eax\n\t"
      "orl $0x10, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "orl %%eax, 0xc(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d4dd3]\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movl $2, -0x4(%%ebp)\n\t"
      "movw 0x2(%%eax), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_001d703b_40\n\t"
      "testb %%ah, %%ah\n\t"
      "js .LFUN_001d703b_40\n\t"
      "movzwl %%ax, %%eax\n\t"
      "shll $0x12, %%eax\n\t"
      "orl %%eax, 0xc(%%ebp)\n\t"
      ".LFUN_001d703b_40:\n\t"
      "movl $1, -0x4(%%ebp)\n\t"
      "jmp .LFUN_001d703b_42\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "ret\n\t"
      "movl -0x18(%%ebp), %%esp\n\t"
      "movl -0x28(%%ebp), %%ebx\n\t"
      "movb 0x5(%%ebx), %%al\n\t"
      "andb $0xfd, %%al\n\t"
      "movb %%al, 0x5(%%ebx)\n\t"
      "movl $1, -0x4(%%ebp)\n\t"
      "movl -0x30(%%ebp), %%esi\n\t"
      "jmp .LFUN_001d703b_42\n\t"
      ".LFUN_001d703b_41:\n\t"
      "movb 0x7(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001d703b_42\n\t"
      "movzbl %%al, %%eax\n\t"
      "shll $0x12, %%eax\n\t"
      "orl %%eax, 0xc(%%ebp)\n\t"
      ".LFUN_001d703b_42:\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "andl $0xfffffff7, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c1d5c66]\n\t"
      "movl %%eax, -0xdc(%%ebp)\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001d703b_47\n\t"
      "addl $-0x10, %%eax\n\t"
      "movl %%eax, -0xe0(%%ebp)\n\t"
      "testb $2, 0x5(%%eax)\n\t"
      "je .LFUN_001d703b_44\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d4dd3]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, -0x40(%%ebp)\n\t"
      "testb $2, 0x5(%%ebx)\n\t"
      "je .LFUN_001d703b_43\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1d4dd3]\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "jmp .LFUN_001d703b_44\n\t"
      ".LFUN_001d703b_43:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".byte 0xab\n\t"
      ".byte 0xab\n\t"
      ".byte 0xab\n\t"
      ".byte 0xab\n\t"
      ".LFUN_001d703b_44:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jb .LFUN_001d703b_45\n\t"
      "movl %%esi, %%eax\n\t"
      ".LFUN_001d703b_45:\n\t"
      "pushl %%eax\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "pushl -0xdc(%%ebp)\n\t"
      "call *%[c1da290]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%esi, 0x14(%%ebp)\n\t"
      "jbe .LFUN_001d703b_46\n\t"
      "testb $8, 0xc(%%ebp)\n\t"
      "je .LFUN_001d703b_46\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "subl %%esi, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl -0xdc(%%ebp), %%edx\n\t"
      "leal (%%edx,%%esi,1), %%edi\n\t"
      "movl %%ecx, %%edx\n\t"
      "shrl $2, %%ecx\n\t"
      "rep stosl\n\t"
      "movl %%edx, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep stosb\n\t"
      ".LFUN_001d703b_46:\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c1d6ca8]\n\t"
      "movl -0xdc(%%ebp), %%eax\n\t"
      ".LFUN_001d703b_47:\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      ".LFUN_001d703b_48:\n\t"
      "cmpl $0, 0x10(%%ebp)\n\t"
      "jne .LFUN_001d703b_49\n\t"
      "testb $4, 0xc(%%ebp)\n\t"
      "je .LFUN_001d703b_49\n\t"
      "movl $0xc0000017, -0x130(%%ebp)\n\t"
      "andl $0, -0x128(%%ebp)\n\t"
      "movl $1, -0x120(%%ebp)\n\t"
      "andl $0, -0x12c(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movl %%eax, -0x11c(%%ebp)\n\t"
      "leal -0x130(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2530c0\n\t"
      "jmp .LFUN_001d703b_49\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl (%%eax), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl $0xc0000017, %%eax\n\t"
      "setne %%cl\n\t"
      "movl %%ecx, %%eax\n\t"
      "ret\n\t"
      "movl -0x18(%%ebp), %%esp\n\t"
      "andl $0, 0x10(%%ebp)\n\t"
      ".LFUN_001d703b_49:\n\t"
      "andl $0, -0x4(%%ebp)\n\t"
      "orl $0xffffffff, -0x4(%%ebp)\n\t"
      "call *%[c1d76fc]\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      ".LFUN_001d703b_50:\n\t"
      "call *%[c1dd601]\n\t"
      "ret\n\t"
      :
      : [c1dd5c8] "m"(b1d703b_c1dd5c8), [c1d4cd9] "m"(b1d703b_c1d4cd9), [c1d4ec6] "m"(b1d703b_c1d4ec6), [c1d4dd3] "m"(b1d703b_c1d4dd3), [c1d5c66] "m"(b1d703b_c1d5c66), [c1da290] "m"(b1d703b_c1da290), [c1d6ca8] "m"(b1d703b_c1d6ca8), [c1d76fc] "m"(b1d703b_c1d76fc), [c1dd601] "m"(b1d703b_c1dd601)
      : "memory");
}
#else
#error "FUN_001d703b: clang naked draft required"
#endif


/* FUN_001d76fc (0x1d76fc) — XBE naked draft (batch 272). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_001d76fc(void)
{
  __asm__ volatile(
      "cmpb $0, -0x1d(%%ebp)\n\t"
      "je .LFUN_001d76fc_1\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "pushl 0x580(%%eax)\n\t"
      "call *0x253098\n\t"
      ".LFUN_001d76fc_1:\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_001d76fc: clang naked draft required"
#endif


/* XAutoPowerDownResetTimer (0x1d771c) — XBE naked draft (batch 276). */
#if defined(__clang__)


__attribute__((naked, noinline))
void XAutoPowerDownResetTimer(void)
{
  __asm__ volatile(
      "pushl $-0x33\n\t"
      "popl %%ecx\n\t"
      "pushl $0x6329c0\n\t"
      "pushl %%ecx\n\t"
      "movl $0xb5659000, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6329e0\n\t"
      "call *0x2531e0\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "XAutoPowerDownResetTimer: clang naked draft required"
#endif


/* FUN_001d7749 (0x1d7749) — XBE naked draft (batch 251). */
#if defined(__clang__)
static void (*const b1d7749_c1d4464)(void) = FUN_001d4464;
static void (*const b1d7749_c1d771c)(void) = XAutoPowerDownResetTimer;

__attribute__((naked, noinline))
void FUN_001d7749(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl $0\n\t"
      "pushl $0x1d7737\n\t"
      "pushl $0x6329c0\n\t"
      "call *0x2531c8\n\t"
      "pushl $0\n\t"
      "pushl $0x6329e0\n\t"
      "call *0x2531c4\n\t"
      "andl $0, 0x632a08\n\t"
      "andl $0, 0x632a0c\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $4\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x11\n\t"
      "call *%[c1d4464]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001d7749_1\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "andl $1, %%eax\n\t"
      "movl %%eax, 0x632a08\n\t"
      "jmp .LFUN_001d7749_2\n\t"
      ".LFUN_001d7749_1:\n\t"
      "movl $1, 0x632a0c\n\t"
      ".LFUN_001d7749_2:\n\t"
      "call *%[c1d771c]\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d4464] "m"(b1d7749_c1d4464), [c1d771c] "m"(b1d7749_c1d771c)
      : "memory");
}
#else
#error "FUN_001d7749: clang naked draft required"
#endif


/* FUN_001d77b3 (0x1d77b3) — readable C lift. */
int __stdcall FUN_001d77b3(const char *a, const char *b)
{
  int r;
  const unsigned char *p;
  const unsigned char *q;
  unsigned char ca;
  unsigned char cb;

  r = xCompareStringA(0, a, -1, b, -1);
  if (r != 0)
    return r - 2;
  if (a == 0)
    return (b != 0) ? -1 : 0; /* neg/sbb when a==0 */
  if (b == 0)
    return 1;
  p = (const unsigned char *)a;
  q = (const unsigned char *)b;
  for (;;) {
    ca = p[0];
    cb = q[0];
    if (ca != cb)
      return (ca < cb) ? -1 : 1;
    if (ca == 0)
      return 0;
    ca = p[1];
    cb = q[1];
    if (ca != cb)
      return (ca < cb) ? -1 : 1;
    p += 2;
    q += 2;
    if (ca == 0)
      return 0;
  }
}
/* FUN_001d7a59 (0x1d7a59) — XBE naked draft (batch 248). */
#if defined(__clang__)
static void (*const b1d7a59_c1dd5c8)(void) = FUN_001dd5c8;
static void (*const b1d7a59_c1dd601)(void) = __SEH_epilog;

__attribute__((naked, noinline))
void FUN_001d7a59(void)
{
  __asm__ volatile(
      "pushl $0x10\n\t"
      "pushl $0x2c1f68\n\t"
      "call *%[c1dd5c8]\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "cmpl %%esi, 0x10(%%ebp)\n\t"
      "je .LFUN_001d7a59_5\n\t"
      ".LFUN_001d7a59_1:\n\t"
      "cmpl %%esi, 0x10(%%ebp)\n\t"
      "je .LFUN_001d7a59_3\n\t"
      "movw (%%edx), %%cx\n\t"
      "cmpw %%si, %%cx\n\t"
      "je .LFUN_001d7a59_2\n\t"
      "movw %%cx, (%%eax)\n\t"
      "incl %%eax\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "incl %%edx\n\t"
      "incl %%edx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "decl 0x10(%%ebp)\n\t"
      "jmp .LFUN_001d7a59_1\n\t"
      ".LFUN_001d7a59_2:\n\t"
      "cmpl %%esi, 0x10(%%ebp)\n\t"
      "jne .LFUN_001d7a59_4\n\t"
      ".LFUN_001d7a59_3:\n\t"
      "decl %%eax\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      ".LFUN_001d7a59_4:\n\t"
      "movw %%si, (%%eax)\n\t"
      ".LFUN_001d7a59_5:\n\t"
      "orl $0xffffffff, -0x4(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "jmp .LFUN_001d7a59_6\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      "ret\n\t"
      "movl -0x18(%%ebp), %%esp\n\t"
      "orl $0xffffffff, -0x4(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_001d7a59_6:\n\t"
      "call *%[c1dd601]\n\t"
      "ret\n\t"
      :
      : [c1dd5c8] "m"(b1d7a59_c1dd5c8), [c1dd601] "m"(b1d7a59_c1dd601)
      : "memory");
}
#else
#error "FUN_001d7a59: clang naked draft required"
#endif


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

/* FUN_001d7d84 (0x1d7d84) — XBE naked draft (batch 251). */
#if defined(__clang__)
static char * __stdcall (*const b1d7d84_c1d789a)(char *dst, const char *src, int count) = FUN_001d789a;
static void (*const b1d7d84_c1d8aef)(void) = FUN_001d8aef;
static void (*const b1d7d84_c1d8b64)(void) = XGetSectionSize;
static void (*const b1d7d84_c1d8b10)(void) = FUN_001d8b10;

__attribute__((naked, noinline))
void FUN_001d7d84(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x54, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl %%edi, %%eax\n\t"
      "leal 0x1(%%eax), %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      ".LFUN_001d7d84_1:\n\t"
      "movb (%%eax), %%cl\n\t"
      "incl %%eax\n\t"
      "cmpb %%bl, %%cl\n\t"
      "jne .LFUN_001d7d84_1\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "subl %%esi, %%eax\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "leal (%%eax,%%edi,1), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d789a]\n\t"
      "pushl %%edi\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2530e4\n\t"
      "pushl $0x22\n\t"
      "pushl $3\n\t"
      "pushl $1\n\t"
      "pushl $4\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x40100000\n\t"
      "leal 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, -0x1c(%%ebp)\n\t"
      "movl $0x40, -0x14(%%ebp)\n\t"
      "call *0x2531a0\n\t"
      "movl %%eax, %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "movb %%bl, (%%esi)\n\t"
      "jl .LFUN_001d7d84_3\n\t"
      "pushl $0x22\n\t"
      "pushl $0x38\n\t"
      "leal -0x54(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "call *0x253180\n\t"
      "movl %%eax, %%edi\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jl .LFUN_001d7d84_2\n\t"
      "cmpl %%ebx, -0x2c(%%ebp)\n\t"
      "jne .LFUN_001d7d84_2\n\t"
      "cmpl %%ebx, -0x28(%%ebp)\n\t"
      "jne .LFUN_001d7d84_2\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c1d8aef]\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LFUN_001d7d84_2\n\t"
      "pushl %%ebx\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *%[c1d8b64]\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "call *0x25317c\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c1d8b10]\n\t"
      ".LFUN_001d7d84_2:\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "call *0x253090\n\t"
      "jmp .LFUN_001d7d84_4\n\t"
      ".LFUN_001d7d84_3:\n\t"
      "cmpl $0xc0000035, %%edi\n\t"
      "jne .LFUN_001d7d84_4\n\t"
      "xorl %%edi, %%edi\n\t"
      ".LFUN_001d7d84_4:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d789a] "m"(b1d7d84_c1d789a), [c1d8aef] "m"(b1d7d84_c1d8aef), [c1d8b64] "m"(b1d7d84_c1d8b64), [c1d8b10] "m"(b1d7d84_c1d8b10)
      : "memory");
}
#else
#error "FUN_001d7d84: clang naked draft required"
#endif


/* XapiMapLetterToDirectory (0x1d7e6b) — XBE naked draft (batch 250). */
#if defined(__clang__)
static void (*const b1d7e6b_c1d8a88)(void) = FUN_001d8a88;
static char * __stdcall (*const b1d7e6b_c1d789a)(char *dst, const char *src, int count) = FUN_001d789a;
static void (*const b1d7e6b_c1d8aef)(void) = FUN_001d8aef;
static void (*const b1d7e6b_c1d8b64)(void) = XGetSectionSize;
static void (*const b1d7e6b_c1d8b10)(void) = FUN_001d8b10;
static void (*const b1d7e6b_c1dd6f5)(void) = FUN_001dd6f5;
static void (*const b1d7e6b_c1d7d84)(void) = FUN_001d7d84;

__attribute__((naked, noinline))
void XapiMapLetterToDirectory(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x284, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x4021\n\t"
      "pushl $3\n\t"
      "pushl $3\n\t"
      "movl $0x80, %%edi\n\t"
      "pushl %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x100001\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "movl $0x40, -0x8(%%ebp)\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "call *0x2531a0\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "jl .LXapiMapLetterToDirectory_1\n\t"
      "pushl -0x4(%%ebp)\n\t"
      "call *0x253090\n\t"
      "jmp .LXapiMapLetterToDirectory_2\n\t"
      ".LXapiMapLetterToDirectory_1:\n\t"
      "cmpl $0xc0000103, %%eax\n\t"
      "jne .LXapiMapLetterToDirectory_2\n\t"
      "movl %%ebx, 0xc(%%ebp)\n\t"
      ".LXapiMapLetterToDirectory_2:\n\t"
      "cmpl %%ebx, 0xc(%%ebp)\n\t"
      "jl .LXapiMapLetterToDirectory_16\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "leal -0x168(%%ebp), %%edx\n\t"
      "subl %%eax, %%edx\n\t"
      ".LXapiMapLetterToDirectory_3:\n\t"
      "movb (%%eax), %%cl\n\t"
      "movb %%cl, (%%edx,%%eax,1)\n\t"
      "incl %%eax\n\t"
      "cmpb %%bl, %%cl\n\t"
      "jne .LXapiMapLetterToDirectory_3\n\t"
      "movw (%%esi), %%cx\n\t"
      "movzwl %%cx, %%eax\n\t"
      "leal -0x168(%%ebp,%%eax,1), %%eax\n\t"
      "cmpb $0x5c, -0x1(%%eax)\n\t"
      "je .LXapiMapLetterToDirectory_4\n\t"
      "movb $0x5c, (%%eax)\n\t"
      "jmp .LXapiMapLetterToDirectory_5\n\t"
      ".LXapiMapLetterToDirectory_4:\n\t"
      "decl %%ecx\n\t"
      "movw %%cx, (%%esi)\n\t"
      ".LXapiMapLetterToDirectory_5:\n\t"
      "movzwl (%%esi), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "subl %%ecx, %%eax\n\t"
      "leal -0x167(%%ebp,%%eax,1), %%eax\n\t"
      ".LXapiMapLetterToDirectory_6:\n\t"
      "movb (%%ecx), %%dl\n\t"
      "movb %%dl, (%%eax,%%ecx,1)\n\t"
      "incl %%ecx\n\t"
      "cmpb %%bl, %%dl\n\t"
      "jne .LXapiMapLetterToDirectory_6\n\t"
      "leal -0x168(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2530e4\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%ebx, 0x14(%%ebp)\n\t"
      "pushl $0x4021\n\t"
      "setne %%al\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "movl $0x40, -0x8(%%ebp)\n\t"
      "leal 0x1(%%eax,%%eax,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x120117\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2531a0\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "jl .LXapiMapLetterToDirectory_16\n\t"
      "cmpl %%ebx, 0x1c(%%ebp)\n\t"
      "je .LXapiMapLetterToDirectory_7\n\t"
      "pushl $0xa\n\t"
      "popl %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal -0x54(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "leal -0x44(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x25313c\n\t"
      "pushl $4\n\t"
      "pushl $0x28\n\t"
      "leal -0x54(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl -0x4(%%ebp)\n\t"
      "call *0x25315c\n\t"
      ".LXapiMapLetterToDirectory_7:\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LXapiMapLetterToDirectory_15\n\t"
      "pushl $0x2c20d4\n\t"
      "call *%[c1d8a88]\n\t"
      "pushl $0x2c20c8\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "call *%[c1d8a88]\n\t"
      "pushl $0x2c20bc\n\t"
      "movl %%eax, 0x1c(%%ebp)\n\t"
      "call *%[c1d8a88]\n\t"
      "cmpl $-1, 0x10(%%ebp)\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl $0x104, %%edi\n\t"
      "jne .LXapiMapLetterToDirectory_8\n\t"
      "cmpw %%bx, (%%esi)\n\t"
      "je .LXapiMapLetterToDirectory_13\n\t"
      ".LXapiMapLetterToDirectory_8:\n\t"
      "leal -0x168(%%ebp), %%eax\n\t"
      "leal 0x1(%%eax), %%esi\n\t"
      ".LXapiMapLetterToDirectory_9:\n\t"
      "movb (%%eax), %%cl\n\t"
      "incl %%eax\n\t"
      "cmpb %%bl, %%cl\n\t"
      "jne .LXapiMapLetterToDirectory_9\n\t"
      "subl %%esi, %%eax\n\t"
      "movl %%edi, %%ecx\n\t"
      "subl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x168(%%ebp,%%eax,1), %%esi\n\t"
      "pushl $0x2c2030\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d789a]\n\t"
      "leal -0x168(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *0x2530e4\n\t"
      "pushl $0x22\n\t"
      "pushl $3\n\t"
      "pushl $1\n\t"
      "pushl $4\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "pushl %%ebx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x40100000\n\t"
      "leal 0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "movl $0x40, -0x8(%%ebp)\n\t"
      "call *0x2531a0\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "movb %%bl, (%%esi)\n\t"
      "jl .LXapiMapLetterToDirectory_12\n\t"
      "pushl $0x22\n\t"
      "pushl $0x38\n\t"
      "leal -0x64(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "call *0x253180\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "jl .LXapiMapLetterToDirectory_11\n\t"
      "cmpl %%ebx, -0x3c(%%ebp)\n\t"
      "jne .LXapiMapLetterToDirectory_11\n\t"
      "cmpl %%ebx, -0x38(%%ebp)\n\t"
      "jne .LXapiMapLetterToDirectory_11\n\t"
      "cmpl $-1, 0x10(%%ebp)\n\t"
      "je .LXapiMapLetterToDirectory_10\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "call *%[c1d8aef]\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "je .LXapiMapLetterToDirectory_10\n\t"
      "pushl %%ebx\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "call *%[c1d8b64]\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "call *0x25317c\n\t"
      "pushl 0x10(%%ebp)\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "call *%[c1d8b10]\n\t"
      "jmp .LXapiMapLetterToDirectory_11\n\t"
      ".LXapiMapLetterToDirectory_10:\n\t"
      "pushl $0x2c2094\n\t"
      "pushl 0x18(%%ebp)\n\t"
      "leal -0x284(%%ebp), %%eax\n\t"
      "pushl $0x3d\n\t"
      "pushl $0x2c2078\n\t"
      "pushl $0xfeff\n\t"
      "pushl $0x2c1ce0\n\t"
      "pushl $0x8e\n\t"
      "pushl %%eax\n\t"
      "call *%[c1dd6f5]\n\t"
      "addl $0x20, %%esp\n\t"
      "pushl %%ebx\n\t"
      "shll $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x284(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "call *0x25317c\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      ".LXapiMapLetterToDirectory_11:\n\t"
      "pushl 0x14(%%ebp)\n\t"
      "call *0x253090\n\t"
      "jmp .LXapiMapLetterToDirectory_13\n\t"
      ".LXapiMapLetterToDirectory_12:\n\t"
      "cmpl $0xc0000035, %%eax\n\t"
      "jne .LXapiMapLetterToDirectory_13\n\t"
      "movl %%ebx, 0xc(%%ebp)\n\t"
      ".LXapiMapLetterToDirectory_13:\n\t"
      "cmpl %%ebx, 0xc(%%ebp)\n\t"
      "jl .LXapiMapLetterToDirectory_15\n\t"
      "cmpl $-1, 0x1c(%%ebp)\n\t"
      "je .LXapiMapLetterToDirectory_14\n\t"
      "pushl $0x2c2044\n\t"
      "pushl %%edi\n\t"
      "leal -0x168(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x1c(%%ebp)\n\t"
      "call *%[c1d7d84]\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      ".LXapiMapLetterToDirectory_14:\n\t"
      "cmpl %%ebx, 0xc(%%ebp)\n\t"
      "jl .LXapiMapLetterToDirectory_15\n\t"
      "cmpl $-1, -0x1c(%%ebp)\n\t"
      "je .LXapiMapLetterToDirectory_15\n\t"
      "pushl $0x2c2058\n\t"
      "pushl %%edi\n\t"
      "leal -0x168(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl -0x1c(%%ebp)\n\t"
      "call *%[c1d7d84]\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      ".LXapiMapLetterToDirectory_15:\n\t"
      "pushl -0x4(%%ebp)\n\t"
      "call *0x253090\n\t"
      "cmpl %%ebx, 0xc(%%ebp)\n\t"
      "jl .LXapiMapLetterToDirectory_16\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x253220\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      ".LXapiMapLetterToDirectory_16:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d8a88] "m"(b1d7e6b_c1d8a88), [c1d789a] "m"(b1d7e6b_c1d789a), [c1d8aef] "m"(b1d7e6b_c1d8aef), [c1d8b64] "m"(b1d7e6b_c1d8b64), [c1d8b10] "m"(b1d7e6b_c1d8b10), [c1dd6f5] "m"(b1d7e6b_c1dd6f5), [c1d7d84] "m"(b1d7e6b_c1d7d84)
      : "memory");
}
#else
#error "XapiMapLetterToDirectory: clang naked draft required"
#endif


/* FUN_001d819f (0x1d819f) — XBE naked draft (batch 269). */
#if defined(__clang__)
static int (*const b1d819f_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static void (*const b1d819f_c1d7e6b)(void) = XapiMapLetterToDirectory;

__attribute__((naked, noinline))
void FUN_001d819f(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl $0x2c1e28\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x32fd80\n\t"
      "pushl $0x32fd78\n\t"
      "call *%[c1d7e6b]\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001d819f_1\n\t"
      "pushl $0\n\t"
      "pushl 0xc(%%ebp)\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "pushl $0x32fd90\n\t"
      "pushl $0x32fd88\n\t"
      "call *%[c1d7e6b]\n\t"
      ".LFUN_001d819f_1:\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d90f0] "m"(b1d819f_c1d90f0), [c1d7e6b] "m"(b1d819f_c1d7e6b)
      : "memory");
}
#else
#error "FUN_001d819f: clang naked draft required"
#endif


/* XapiBootToDash (0x1d81f4) — XBE naked draft (batch 272). */
#if defined(__clang__)
static int __stdcall (*const b1d81f4_c1d25e0)(const char *image_path, void *launch_data) = XLaunchNewImageA;
static void (*const b1d81f4_c1d7749)(void) = FUN_001d7749;
static void (*const b1d81f4_c1d5842)(void) = FUN_001d5842;
static int __stdcall (*const b1d81f4_c1d7d21)(void *object_name_field) = FUN_001d7d21;
static void (*const b1d81f4_c1d819f)(void) = FUN_001d819f;
static void (*const b1d81f4_c1d3c95)(void) = XMountUtilityDrive;
static void (*const b1d81f4_c1d81f4)(void) = XapiBootToDash;
static void (*const b1d81f4_c1d454b)(void) = FUN_001d454b;

__attribute__((naked, noinline))
void XapiBootToDash(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc00, %%esp\n\t"
      "movl 0x10118, %%eax\n\t"
      "cmpl $0xfffe0000, 0x8(%%eax)\n\t"
      "je .LXapiBootToDash_1\n\t"
      "pushl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $0x300, %%ecx\n\t"
      "leal -0xc00(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "andl $0, -0xbfc(%%ebp)\n\t"
      "movl %%eax, -0xc00(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, -0xbf8(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%eax, -0xbf4(%%ebp)\n\t"
      "leal -0xc00(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c1d25e0]\n\t"
      "popl %%edi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      ".LXapiBootToDash_1:\n\t"
      "pushl $4\n\t"
      "call *0x2531f8\n\t"
      ".byte 0xcc\n\t"
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "call *%[c1d7749]\n\t"
      "pushl $0xc\n\t"
      "popl %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal -0x30(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "movl $0x30, -0x30(%%ebp)\n\t"
      "pushl 0x10138\n\t"
      "pushl 0x10134\n\t"
      "pushl %%esi\n\t"
      "pushl $2\n\t"
      "popl %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1d5842]\n\t"
      "cmpl %%esi, %%eax\n\t"
      "movl %%eax, 0x632a28\n\t"
      "jne .LXapiBootToDash_3\n\t"
      ".LXapiBootToDash_2:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, %%eax\n\t"
      "jmp .LXapiBootToDash_10\n\t"
      ".LXapiBootToDash_3:\n\t"
      "testb $8, 0x10124\n\t"
      "jne .LXapiBootToDash_7\n\t"
      "pushl $0x32fd70\n\t"
      "call *%[c1d7d21]\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LXapiBootToDash_5\n\t"
      "pushl $0x32fd68\n\t"
      "pushl $0x32fd60\n\t"
      "call *0x253220\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jge .LXapiBootToDash_4\n\t"
      "cmpl $0xc0000035, %%eax\n\t"
      "jne .LXapiBootToDash_2\n\t"
      ".LXapiBootToDash_4:\n\t"
      "movl 0x10118, %%eax\n\t"
      "leal 0xc(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl 0x8(%%eax)\n\t"
      "call *%[c1d819f]\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jge .LXapiBootToDash_6\n\t"
      "cmpl $0xc000007f, %%eax\n\t"
      "jne .LXapiBootToDash_5\n\t"
      "pushl $0x54\n\t"
      "popl %%ecx\n\t"
      "pushl $0x10\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%esi\n\t"
      "jmp .LXapiBootToDash_10\n\t"
      ".LXapiBootToDash_5:\n\t"
      "movl %%edi, %%ecx\n\t"
      "jmp .LXapiBootToDash_9\n\t"
      ".LXapiBootToDash_6:\n\t"
      "movl 0x10124, %%eax\n\t"
      "testb $1, %%al\n\t"
      "je .LXapiBootToDash_8\n\t"
      "andl %%edi, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d3c95]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LXapiBootToDash_8\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "call *%[c1d81f4]\n\t"
      "jmp .LXapiBootToDash_8\n\t"
      ".LXapiBootToDash_7:\n\t"
      "pushl $0x32fd68\n\t"
      "pushl $0x32fd60\n\t"
      "call *0x253220\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jge .LXapiBootToDash_8\n\t"
      "cmpl $0xc0000035, %%eax\n\t"
      "jne .LXapiBootToDash_2\n\t"
      ".LXapiBootToDash_8:\n\t"
      "movl 0x10118, %%eax\n\t"
      "movl 0xa4(%%eax), %%esi\n\t"
      "call *%[c1d454b]\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jae .LXapiBootToDash_11\n\t"
      "pushl $4\n\t"
      "popl %%ecx\n\t"
      ".LXapiBootToDash_9:\n\t"
      "xorl %%eax, %%eax\n\t"
      "incl %%eax\n\t"
      ".LXapiBootToDash_10:\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d81f4]\n\t"
      ".LXapiBootToDash_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".byte 0xc9\n\t"
      "ret\n\t"
      :
      : [c1d25e0] "m"(b1d81f4_c1d25e0), [c1d7749] "m"(b1d81f4_c1d7749), [c1d5842] "m"(b1d81f4_c1d5842), [c1d7d21] "m"(b1d81f4_c1d7d21), [c1d819f] "m"(b1d81f4_c1d819f), [c1d3c95] "m"(b1d81f4_c1d3c95), [c1d81f4] "m"(b1d81f4_c1d81f4), [c1d454b] "m"(b1d81f4_c1d454b)
      : "memory");
}
#else
#error "XapiBootToDash: clang naked draft required"
#endif

