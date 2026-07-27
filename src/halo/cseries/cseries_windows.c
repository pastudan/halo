/* system_stristr (0x8e250) — XBE naked draft (batch 91). */
#if defined(__clang__)
static int (*const b8e250_c8df60)(const char *s1) = csstrlen;
static int (*const b8e250_c1e6596)(const char *a, const char *b, size_t n) = __strnicmp;

__attribute__((naked, noinline))
char * system_stristr(const char *str __attribute__((unused)), const char *substr __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movb (%%edi), %%bl\n\t"
      "incl %%edi\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lsystem_stristr_3\n\t"
      "pushl %%edi\n\t"
      "call *%[c8df60]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "nop\n\t"
      ".Lsystem_stristr_1:\n\t"
      "movb (%%esi), %%al\n\t"
      "incl %%esi\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsystem_stristr_2\n\t"
      "cmpb %%bl, %%al\n\t"
      "jne .Lsystem_stristr_1\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1e6596]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lsystem_stristr_1\n\t"
      "decl %%esi\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsystem_stristr_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsystem_stristr_3:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8df60] "m"(b8e250_c8df60), [c1e6596] "m"(b8e250_c1e6596)
      : "memory");
}
#else
#error "system_stristr: clang naked draft required"
#endif


/* system_string_hash (0x8e2b0) — XBE naked draft (batch 98). */
#if defined(__clang__)
static void (*const b8e2b0_c1190b0)(uint32_t *checksum) = crc_new;
static int (*const b8e2b0_c8df60)(const char *s1) = csstrlen;
static void (*const b8e2b0_c119100)(uint32_t *checksum, void *data, int size) = crc_checksum_buffer;

__attribute__((naked, noinline))
uint32_t system_string_hash(const char *str __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1190b0]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "pushl %%eax\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c119100]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1190b0] "m"(b8e2b0_c1190b0), [c8df60] "m"(b8e2b0_c8df60), [c119100] "m"(b8e2b0_c119100)
      : "memory");
}
#else
#error "system_string_hash: clang naked draft required"
#endif


void display_debug_string(const char *str)
{
  ((void(__stdcall *)(const char *))0x1d0370)(str);
}

void system_exit(int code)
{
  (void)code;
  halt_and_catch_fire();
  __builtin_unreachable();
}

/* system_unique_identifiers_equal (0x8e320) — readable C lift. */
int system_unique_identifiers_equal(const void *id1, const void *id2)
{
  char zero[16];
  csmemset(zero, 0, 0x10);
  if (csmemcmp(id1, zero, 0x10) == 0)
    return 0;
  if (csmemcmp(id1, id2, 0x10) != 0)
    return 0;
  return 1;
}

uint32_t system_milliseconds(void)
{
  return ((uint32_t(*)(void))0x1d0581)();
}

uint32_t system_seconds(void)
{
  return crt_time(NULL);
}

/* system_get_user_name (0x8e390) — XBE naked draft (batch 101). */
#if defined(__clang__)
static void * (*const b8e390_c8de70)(char *destination, const char *source, size_t size) = csstrncpy;

__attribute__((naked, noinline))
void system_get_user_name(char *buffer __attribute__((unused)), int16_t max_len __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movswl 0xc(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x267a68\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8de70]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8de70] "m"(b8e390_c8de70)
      : "memory");
}
#else
#error "system_get_user_name: clang naked draft required"
#endif


/* system_calloc (0x8e3b0) — XBE naked draft (batch 102). */
#if defined(__clang__)
static void (*const b8e3b0_c1d0c48)(void) = FUN_001d0c48;

__attribute__((naked, noinline))
void * system_calloc(int count __attribute__((unused)), int size __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "imull 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x40\n\t"
      "call *%[c1d0c48]\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d0c48] "m"(b8e3b0_c1d0c48)
      : "memory");
}
#else
#error "system_calloc: clang naked draft required"
#endif


void *system_malloc(int size)
{
  return ((void *(__stdcall *)(uint32_t, uint32_t))0x1d0c48)(0, size);
}

void system_free(void *ptr)
{
  ((void *(__stdcall *)(void *))0x1d0c16)(ptr);
}

/* system_realloc (0x8e3f0) — XBE naked draft (batch 92). */
#if defined(__clang__)
static void (*const b8e3f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b8e3f0_c1029a0)(void) = halt_and_catch_fire;
static void (*const b8e3f0_c1d0c48)(void) = FUN_001d0c48;
static void (*const b8e3f0_c1d0c65)(void) = FUN_001d0c65;
static void *__stdcall (*const b8e3f0_c1d0c16)(void *ptr) = LocalFree;

__attribute__((naked, noinline))
void * system_realloc(void *ptr __attribute__((unused)), int size __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jge .Lsystem_realloc_1\n\t"
      "pushl $1\n\t"
      "pushl $0x9c\n\t"
      "pushl $0x267a3c\n\t"
      "pushl $0x267a80\n\t"
      "call *%[assert]\n\t"
      "addl $0x10, %%esp\n\t"
      "call *%[c1029a0]\n\t"
      ".Lsystem_realloc_1:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lsystem_realloc_3\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lsystem_realloc_2\n\t"
      "pushl $1\n\t"
      "pushl $0x9d\n\t"
      "pushl $0x267a3c\n\t"
      "pushl $0x267a70\n\t"
      "call *%[assert]\n\t"
      "addl $0x10, %%esp\n\t"
      "call *%[c1029a0]\n\t"
      ".Lsystem_realloc_2:\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "call *%[c1d0c48]\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsystem_realloc_3:\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lsystem_realloc_4\n\t"
      "pushl $2\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d0c65]\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lsystem_realloc_4:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d0c16]\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b8e3f0_assert), [c1029a0] "m"(b8e3f0_c1029a0), [c1d0c48] "m"(b8e3f0_c1d0c48), [c1d0c65] "m"(b8e3f0_c1d0c65), [c1d0c16] "m"(b8e3f0_c1d0c16)
      : "memory");
}
#else
#error "system_realloc: clang naked draft required"
#endif


uint32_t system_get_used_memory_size(uint32_t *output)
{
  return ((uint32_t(__stdcall *)(void *))0x1d0c02)(output);
}

void FUN_0008e480(uint32_t *output)
{
  uint32_t status[8];

  csmemset(status, 0, 0x20);
  status[0] = 0x20;
  xbox_query_global_memory_status(status);
  csmemset(output, 0, 8);
  output[0] = status[3];
  output[1] = status[2];
}

/* system_exception_name (0x8e500) — XBE naked draft (batch 90). */
#if defined(__clang__)


__attribute__((naked, noinline))
const char * system_exception_name(uint32_t code __attribute__((unused)))
{
  __asm__ volatile(
      "xorl %%eax, %%eax\n\t"
      "cmpl $0xc000008f, %%ecx\n\t"
      "ja .Lsystem_exception_name_9\n\t"
      "je .Lsystem_exception_name_8\n\t"
      "cmpl $0xc0000025, %%ecx\n\t"
      "ja .Lsystem_exception_name_5\n\t"
      "je .Lsystem_exception_name_4\n\t"
      "cmpl $0x80000004, %%ecx\n\t"
      "ja .Lsystem_exception_name_3\n\t"
      "je .Lsystem_exception_name_2\n\t"
      "cmpl $0x80000002, %%ecx\n\t"
      "je .Lsystem_exception_name_1\n\t"
      "cmpl $0x80000003, %%ecx\n\t"
      "jne .Lsystem_exception_name_17\n\t"
      "movl $0x267c40, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_1:\n\t"
      "movl $0x267c20, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_2:\n\t"
      "movl $0x267c08, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_3:\n\t"
      "cmpl $0xc0000005, %%ecx\n\t"
      "jne .Lsystem_exception_name_17\n\t"
      "movl $0x267bec, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_4:\n\t"
      "movl $0x267bc8, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_5:\n\t"
      "cmpl $0xc000008c, %%ecx\n\t"
      "je .Lsystem_exception_name_7\n\t"
      "cmpl $0xc000008d, %%ecx\n\t"
      "je .Lsystem_exception_name_6\n\t"
      "cmpl $0xc000008e, %%ecx\n\t"
      "jne .Lsystem_exception_name_17\n\t"
      "movl $0x267ba8, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_6:\n\t"
      "movl $0x267b88, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_7:\n\t"
      "movl $0x267b68, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_8:\n\t"
      "movl $0x267b48, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_9:\n\t"
      "addl $0x3fffff70, %%ecx\n\t"
      "cmpl $6, %%ecx\n\t"
      "ja .Lsystem_exception_name_17\n\t"
      "jmp *.Lsystem_exception_name_jt(,%%ecx,4)\n\t"
      ".Lsystem_exception_name_10:\n\t"
      "movl $0x267b28, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_11:\n\t"
      "movl $0x267b10, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_12:\n\t"
      "movl $0x267af4, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_13:\n\t"
      "movl $0x267adc, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_14:\n\t"
      "movl $0x267abc, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_15:\n\t"
      "movl $0x267aa4, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_16:\n\t"
      "movl $0x267a88, %%eax\n\t"
      ".Lsystem_exception_name_17:\n\t"
      "ret\n\t"
      "movl %%edi, %%edi\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lsystem_exception_name_jt:\n\t"
      ".long .Lsystem_exception_name_10\n\t"
      ".long .Lsystem_exception_name_11\n\t"
      ".long .Lsystem_exception_name_12\n\t"
      ".long .Lsystem_exception_name_13\n\t"
      ".long .Lsystem_exception_name_14\n\t"
      ".long .Lsystem_exception_name_15\n\t"
      ".long .Lsystem_exception_name_16\n\t"
      ".text\n\t"
      :
      :
      : "memory");
}
#else
#error "system_exception_name: clang naked draft required"
#endif

