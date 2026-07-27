
/* system_stristr (0x8e250) — readable C lift. */
char *system_stristr(const char *str, const char *substr)
{
  const char *p;
  char first;
  int rest_len;

  first = *substr;
  substr++;
  if (!first)
    return (char *)str;
  rest_len = csstrlen(substr);
  p = str;
  for (;;) {
    char c = *p++;
    if (!c)
      return (char *)0;
    if (c != first)
      continue;
    if (__strnicmp(p, substr, (size_t)rest_len) == 0)
      return (char *)(p - 1);
  }
}


/* system_string_hash (0x8e2b0) — readable C lift. */
uint32_t system_string_hash(const char *str)
{
  uint32_t checksum;
  crc_new(&checksum);
  crc_checksum_buffer(&checksum, (void *)str, csstrlen(str));
  return checksum;
}

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

/* system_get_user_name (0x8e390) — readable C lift. */
void system_get_user_name(char *buffer, int16_t max_len)
{
  csstrncpy(buffer, (const char *)0x267a68, (size_t)(int32_t)max_len);
}

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

