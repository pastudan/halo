/* kb object stubs -> libcmt/vsprintf.c */

/* --- LIBCMT:vsprintf.obj batch drafts (2026-07-26) --- */

/* 0x1da059 */
void FUN_001da059(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1da081 */
void _fscanf(void)
{
  FUN_001dd5c8();
  __lock_file();
  FUN_001e0984();
  FUN_001da0c1();
  __SEH_epilog();
}

/* 0x1da0c1 */
void FUN_001da0c1(void)
{
  __unlock_file();
}

/* 0x1da0cc */
void FUN_001da0cc(void)
{
  FUN_001dee48();
  FUN_001da0e9();
  __fload_withFB();
}

/* 0x1da0e9 */
void FUN_001da0e9(void)
{
  int eax = 0;

  /* relift: cmp word ptr [esp], 0x27f -> je 0x1da0fd */
  FUN_001dedd5();
  /* cmp eax, 0x3ff00000 -> jae 0x1da12f */
  /* relift: cmp dword ptr [0x4fc000], 0 -> jne 0x1dee5e */
  /* relift: relift: fld xword ptr [0x3314c2] */
  FUN_001dedec();
  /* test eax, 0xfffff -> jne 0x1da156 */
  /* relift: cmp dword ptr [esp + 8], 0 -> jne 0x1da156 */
  /* relift: relift: fld xword ptr [0x3314b8] */
  /* relift: cmp dword ptr [0x4fc000], 0 -> jne 0x1dee5e */
  __startOneArgErrorHandling();

  (void)eax;
}

/* crt_toupper (0x1da19f) — Capstone tip: ctype bit1 → c-0x20 (locale<=1). */
int crt_toupper(int c)
{
  unsigned char *table;
  int is_lower;
  if (*(int *)0x3317bc > 1)
    return c;
  table = *(unsigned char **)0x3317b4;
  is_lower = table[(unsigned)c * 2] & 2;
  if (is_lower)
    return c - 0x20;
  return c;
}


/* crt_tolower (0x1da1d8) — Capstone tip: ctype bit0 → c+0x20 (locale<=1). */
int crt_tolower(int c)
{
  unsigned char *table;
  int is_upper;
  if (*(int *)0x3317bc > 1)
    return c;
  table = *(unsigned char **)0x3317b4;
  is_upper = table[(unsigned)c * 2] & 1;
  if (is_upper)
    return c + 0x20;
  return c;
}


/* 0x1da209 */
int vsprintf(char *buffer, const char *format, char *arglist)
{
  FUN_001de452();
  __flsbuf();
  return 0;
}

/* 0x1da260 */
void FUN_001da260(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  FUN_001de452();
  /* cmp edi, esi -> jbe 0x1da2b0 */
  /* cmp edi, eax -> jb 0x1da428 */
  /* test edi, 3 -> jne 0x1da2cc */
  /* cmp ecx, 8 -> jb 0x1da2ec */
  /* cmp ecx, 8 -> jb 0x1da2ec */
  /* cmp ecx, 8 -> jb 0x1da2ec */
  /* cmp ecx, 8 -> jb 0x1da2ec */
  /* mem[0xa3bc001d] = eax */

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}
