/* kb object stubs -> libcmt/isctype.c */

/* --- LIBCMT:isctype.obj batch drafts (2026-07-26) --- */

/* 0x1daaaa */
void _isalpha(void)
{
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1daac4 */
  FUN_001e153d();
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1daaef */
  FUN_001e153d();
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dab18 */
  FUN_001e153d();
}

/* 0x1dab2a */
int isdigit(int c)
{
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dab41 */
  FUN_001e153d();
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dab6d */
  FUN_001e153d();
  return 0;
}

/* 0x1dab81 */
int crt_isspace(int c)
{
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dab98 */
  FUN_001e153d();
  return 0;
}

/* 0x1dabaa */
int _ispunct(int c)
{
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dabc1 */
  FUN_001e153d();
  return 0;
}

/* 0x1dabd3 */
int _isalnum(int c)
{
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dabed */
  FUN_001e153d();
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dac1b */
  FUN_001e153d();
  return 0;
}

/* 0x1dac2f */
int crt_isgraph(int c)
{
  int eax = 0;

  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dac49 */
  FUN_001e153d();
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dac74 */
  FUN_001e153d();
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dacb6 */
  FUN_001e153d();
  /* test eax, eax -> jne 0x1dacd4 */
  /* relift: cmp dword ptr [esp + 4], 0x5f -> je 0x1dacd4 */
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dacf3 */
  FUN_001e153d();
  /* test eax, eax -> jne 0x1dad11 */
  /* relift: cmp dword ptr [esp + 4], 0x5f -> je 0x1dad11 */
  return 0;

  (void)eax;
}

/* 0x1dad15 */
void FUN_001dad15(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001e153d();
  /* test eax, eax -> je 0x1dad56 */
  /* cmp (char)ebx, 0x2d -> jne 0x1dad61 */
  /* cmp (char)ebx, 0x2b -> jne 0x1dad69 */
  /* test eax, eax -> jl 0x1daeae */
  /* cmp eax, 1 -> je 0x1daeae */
  /* cmp eax, 0x24 -> jg 0x1daeae */
  /* cmp (char)ebx, 0x30 -> je 0x1dad9b */
  /* cmp (char)eax, 0x78 -> je 0x1dadae */
  /* cmp (char)eax, 0x58 -> je 0x1dadae */
  /* relift: cmp dword ptr [ebp + 0x10], ecx -> jne 0x1dadc9 */
  /* cmp (char)ebx, 0x30 -> jne 0x1dadc9 */
  /* cmp (char)eax, 0x78 -> je 0x1dadc5 */
  /* cmp (char)eax, 0x58 -> jne 0x1dadc9 */
  /* test (char)ecx, 4 -> je 0x1dadeb */
  /* test (int16_t)ecx, 0x103 -> je 0x1dae35 */
  /* cmp (char)ebx, 0x61 -> jl 0x1dae04 */
  /* cmp (char)ebx, 0x7a -> jg 0x1dae04 */
  /* relift: cmp ecx, dword ptr [ebp + 0x10] -> jae 0x1dae35 */
  /* relift: cmp dword ptr [ebp - 4], eax -> jb 0x1dae24 */
  /* cmp ecx, edx -> jbe 0x1dae24 */
  /* test (char)eax, 8 -> jne 0x1dae4c */
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> je 0x1dae46 */
  /* test (char)eax, 1 -> jne 0x1dae97 */
  /* relift: cmp dword ptr [ebp - 4], 0x80000000 -> ja 0x1dae70 */
  /* test eax, eax -> jne 0x1dae97 */
  /* relift: cmp dword ptr [ebp - 4], esi -> jbe 0x1dae97 */
  FUN_001db777();
  /* test eax, eax -> je 0x1daea0 */
  /* relift: test byte ptr [ebp + 0x14], 2 -> je 0x1daea9 */
  /* test eax, eax -> je 0x1daeb7 */
  /* relift: tail-call FUN_001dad15(); */
  /* relift: tail-call FUN_001dad15(); */
  FUN_001dd5c8();
  /* relift: cmp dword ptr [ebp + 0xc], 0 -> jg 0x1daf0a */
  __lock_file();
  __filbuf();
  /* cmp eax, -1 -> jne 0x1daf48 */
  /* cmp edi, ebx -> jne 0x1daf52 */
  /* cmp (char)eax, 0xa -> jne 0x1daf1b */
  FUN_001daf6a();
  __SEH_epilog();
  __unlock_file();
  FUN_001e153d();
  /* test eax, eax -> je 0x1dafcc */
  /* test (char)ecx, (char)ecx -> jne 0x1dafd1 */
  FUN_001e1e20();
  FUN_001e1ea5();
  /* cmp ecx, 0x2b -> jne 0x1db01c */
  /* cmp ecx, 0x30 -> jl 0x1db02d */
  /* cmp ecx, 0x39 -> jg 0x1db02d */
  /* cmp ecx, -1 -> je 0x1db041 */
  FUN_001e1ea5();
  /* cmp esi, 0x2b -> jne 0x1db07c */
  /* cmp esi, 0x30 -> jl 0x1db08f */
  /* cmp esi, 0x39 -> jg 0x1db08f */
  /* cmp esi, -1 -> je 0x1db0b7 */
  __allmul();
  FUN_001de452();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
