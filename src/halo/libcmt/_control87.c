/* kb object stubs -> libcmt/_control87.c */

/* --- LIBCMT:_control87.obj batch drafts (2026-07-26) --- */

/* 0x1db3f7 */
unsigned int FUN_001db3f7(void *ptr, unsigned int size, unsigned int count, void *stream)
{
  FUN_001dd5c8();
  __lock_file();
  FUN_001db2ff();
  FUN_001db439();
  __SEH_epilog();
  return 0;
}

/* 0x1db439 */
void FUN_001db439(void)
{
  __unlock_file();
}

/* 0x1db443 */
void _wprintf(void)
{
  FUN_001dd5c8();
  __lock_file2();
  __stbuf();
  FUN_001de452();
  __ftbuf();
  FUN_001db49e();
  __SEH_epilog();
}

/* 0x1db49e */
void FUN_001db49e(void)
{
  __unlock_file2();
}

/* 0x1db4a9 */
void FUN_001db4a9(void)
{
  int eax = 0;
  int esi = 0;

  DeleteFileA((char *)0);
  /* test eax, eax -> jne 0x1db4bd */
  xapi_GetLastError();
  /* test eax, eax -> je 0x1db4ce */
  __dosmaperr();
  /* relift: FUN_001e2180(0); */
  FUN_001de27a();
  /* test esi, esi -> je 0x1db4ff */
  /* relift: test dword ptr [eax], 0x10008 -> je 0x1db4ff */

  (void)eax;
  (void)esi;
}

/* 0x1db501 */
void __abstract_cw(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1db593 */
void __hw_cw(void)
{
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test (char)ebx, 0x10 -> je 0x1db59b */
  /* test (char)ebx, 8 -> je 0x1db5a3 */
  /* test (char)ebx, 4 -> je 0x1db5ab */
  /* test (char)ebx, 2 -> je 0x1db5b3 */
  /* test (char)ebx, 1 -> je 0x1db5bb */
  /* test ebx, 0x80000 -> je 0x1db5c6 */
  /* cmp ecx, 0x100 -> je 0x1db5f5 */
  /* cmp ecx, esi -> je 0x1db5ee */
  /* cmp ecx, edx -> jne 0x1db5fa */
  /* cmp ecx, 0x10000 -> jne 0x1db612 */
  /* test (char)ecx, 1 -> je 0x1db62f */
  /* test (char)ecx, 4 -> je 0x1db637 */
  /* test (char)ecx, 8 -> je 0x1db63f */
  /* test (char)ecx, 0x10 -> je 0x1db647 */
  /* test (char)ecx, 0x20 -> je 0x1db64f */
  /* test (char)ecx, 2 -> je 0x1db659 */
  /* relift: FUN_001db621(0); */
  /* relift: FUN_001db621(0); */

  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1db67f */
unsigned int __control87(unsigned int new_value, unsigned int mask)
{
  __abstract_cw();
  __hw_cw();
  return 0;
}

/* 0x1db6b1 */
void __controlfp(void)
{
  int eax = 0;

  __control87(0, eax);

  (void)eax;
}

/* 0x1db6c7 */
int _fputc(int c, void *stream)
{
  FUN_001dd5c8();
  __lock_file();
  __flsbuf();
  FUN_001db717();
  __SEH_epilog();
  return 0;
}

/* 0x1db717 */
void FUN_001db717(void)
{
  __unlock_file();
}

/* 0x1db71f */
int FUN_001db71f(int c, void *stream)
{
  FUN_001dd5c8();
  __lock_file();
  __flsbuf();
  FUN_001db76f();
  __SEH_epilog();
  return 0;
}

/* 0x1db76f */
void FUN_001db76f(void)
{
  __unlock_file();
}

/* 0x1db777 */
int *FUN_001db777(void)
{
  FUN_001dff91();
  return NULL;
}

/* 0x1db780 */
void FUN_001db780(void)
{
  FUN_001dff91();
}

/* 0x1db789 */
void __dosmaperr(void)
{
  int ecx = 0;
  int esi = 0;

  FUN_001dff91();
  /* relift: cmp ecx, dword ptr [esi*8 + 0x331320] -> je 0x1db7bf */
  /* cmp esi, 0x2d -> jb 0x1db798 */
  /* cmp ecx, 0x13 -> jb 0x1db7d0 */
  /* cmp ecx, 0x24 -> ja 0x1db7d0 */
  FUN_001dff91();
  FUN_001dff91();
  /* cmp ecx, 0xbc -> jb 0x1db7ee */
  /* cmp ecx, 0xca -> ja 0x1db7ee */
  FUN_001dff91();
  FUN_001dff91();

  (void)ecx;
  (void)esi;
}

/* 0x1db7fc */
void __fseek_lk(void)
{
  int eax = 0;
  int edi = 0;

  /* test edi, edi -> je 0x1db81b */
  /* cmp edi, 1 -> je 0x1db81b */
  /* cmp edi, 2 -> jne 0x1db87a */
  __ftell_lk();
  __flush();
  /* test (char)eax, 1 -> je 0x1db85d */
  /* test (char)eax, 8 -> je 0x1db85d */
  /* test (char)eax, 4 -> jne 0x1db85d */
  __lseek();
  FUN_001db777();

  (void)eax;
  (void)edi;
}

/* 0x1db88b */
int _fseek(void *stream, int offset, int whence)
{
  FUN_001dd5c8();
  __lock_file();
  __fseek_lk();
  FUN_001db8ca();
  __SEH_epilog();
  return 0;
}

/* 0x1db8ca */
void FUN_001db8ca(void)
{
  __unlock_file();
}

/* 0x1db8d4 */
void _rewind(void *stream)
{
  int edi = 0;

  FUN_001dd5c8();
  __lock_file();
  __flush();
  /* cmp edi, -1 -> je 0x1db91e */
  __lseek();
  FUN_001db953();
  __SEH_epilog();

  (void)edi;
}

/* 0x1db953 */
void FUN_001db953(void)
{
  __unlock_file();
}

/* 0x1db95d */
void __ftell_lk(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  __lseek();
  /* test (int16_t)ecx, 0x108 -> jne 0x1db99e */
  /* relift: test byte ptr [ebx + ecx*8 + 4], 0x80 -> je 0x1db9dd */
  /* cmp ecx, eax -> jae 0x1db9dd */
  /* relift: cmp byte ptr [ecx], 0xa -> jne 0x1db9d8 */
  /* relift: cmp ecx, dword ptr [edi] -> jb 0x1db9d0 */
  /* relift: cmp dword ptr [ebp - 4], 0 -> jne 0x1dba02 */
  FUN_001db777();
  /* relift: test byte ptr [edi + 0xc], 1 -> je 0x1dbab2 */
  /* test ecx, ecx -> jne 0x1dba1b */
  /* relift: test byte ptr [esi + eax + 4], 0x80 -> je 0x1dbaac */
  __lseek();
  /* relift: cmp eax, dword ptr [ebp - 4] -> jne 0x1dba73 */
  /* relift: cmp byte ptr [eax], 0xa -> jne 0x1dba68 */
  /* cmp eax, ecx -> jb 0x1dba60 */
  __lseek();
  /* relift: cmp dword ptr [ebp + 8], eax -> ja 0x1dba9a */
  /* test (char)ecx, 8 -> je 0x1dba9a */
  /* test (char)ecx, 4 -> je 0x1dba9d */
  /* relift: test byte ptr [esi + eax + 4], 4 -> je 0x1dbaac */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1dbabf */
void _ftell(void)
{
  FUN_001dd5c8();
  __lock_file();
  __ftell_lk();
  FUN_001dbaf6();
  __SEH_epilog();
}

/* 0x1dbaf6 */
void FUN_001dbaf6(void)
{
  __unlock_file();
}

/* 0x1dbb00 */
void FUN_001dbb00(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001dd5c8();
  /* relift: cmp edi, dword ptr [0x632ca8] -> jae 0x1dbb4f */
  /* relift: test byte ptr [ecx + eax*8 + 4], (char)ebx -> je 0x1dbb4f */
  __getstream();
  /* cmp esi, edx -> jne 0x1dbb57 */
  FUN_001db777();
  __SEH_epilog();
  /* cmp (char)eax, 0x61 -> je 0x1dbb7a */
  /* cmp (char)eax, 0x72 -> je 0x1dbb75 */
  /* cmp (char)eax, 0x77 -> je 0x1dbb7a */
  /* test (char)eax, (char)eax -> je 0x1dbc02 */
  /* relift: cmp dword ptr [ebp - 0x20], 0 -> je 0x1dbc02 */
  /* relift: cmp dword ptr [ebp - 0x28], 0 -> jne 0x1dbbec */
  /* relift: cmp dword ptr [ebp - 0x24], 0 -> jne 0x1dbbec */
  /* relift: cmp dword ptr [ebp - 0x24], 0 -> jne 0x1dbbec */
  FUN_001dbc1e();
  __unlock_file();
  __ctrlfp();
  __sptype();
  /* cmp eax, 2 -> jle 0x1dbc81 */
  /* cmp eax, 3 -> jne 0x1dbc8f */
  __handle_qnan1();
  __ctrlfp();
  FUN_001dfd23();
  __ctrlfp();
  /* test (char)ebx, 0x20 -> jne 0x1dbcc0 */
  FUN_001dfbd2();
  RtlUnwind(0, 0x001dbd0c, 0, 0);
  /* cmp esi, -1 -> je 0x1dbd90 */
  /* relift: cmp esi, dword ptr [esp + 0x24] -> je 0x1dbd90 */
  /* relift: cmp dword ptr [ebx + esi*4 + 4], 0 -> jne 0x1dbd8e */
  FUN_001dbdca();
  /* relift: cmp dword ptr [ecx + 4], 0x1dbd14 -> jne 0x1dbdc0 */
  /* relift: cmp dword ptr [ecx + 8], edx -> jne 0x1dbdc0 */
  /* relift: test dword ptr [eax + 4], 6 -> jne 0x1dbe8c */
  /* cmp esi, -1 -> je 0x1dbe85 */
  /* relift: cmp dword ptr [edi + ecx*4 + 4], 0 -> je 0x1dbe73 */
  __global_unwind2();
  __local_unwind2();
  FUN_001dbdca();
  __local_unwind2();
  __local_unwind2();
  /* test eax, eax -> je 0x1dbf23 */
  /* test edx, 3 -> je 0x1dbefd */
  /* test edx, 3 -> jne 0x1dbeeb */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
