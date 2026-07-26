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

/* 0x1da19f */
int crt_toupper(int c)
{
  FUN_001e153d();
  return 0;
}

/* 0x1da1d8 */
int crt_tolower(int c)
{
  FUN_001e153d();
  return 0;
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
