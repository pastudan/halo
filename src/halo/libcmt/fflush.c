/* kb object stubs -> libcmt/fflush.c */

/* --- LIBCMT:fflush.obj batch drafts (2026-07-26) --- */

/* 0x1d9a4f */
void __unlock_file2(void)
{
  int eax = 0;

  /* cmp eax, 0x14 -> jge 0x1d9a63 */
  FUN_001defb3();

  (void)eax;
}

/* 0x1d9a72 */
void __flush(void)
{
  int eax = 0;
  int ecx = 0;
  int edi = 0;

  /* cmp (char)ecx, 2 -> jne 0x1d9ac1 */
  /* test (int16_t)eax, 0x108 -> je 0x1d9ac1 */
  /* test edi, edi -> jle 0x1d9ac0 */
  __write();
  /* cmp eax, edi -> jne 0x1d9ab9 */

  (void)eax;
  (void)ecx;
  (void)edi;
}

/* 0x1d9acf */
void __fflush_lk(void)
{
  int esi = 0;

  __flush();
  /* relift: test byte ptr [esi + 0xd], 0x40 -> je 0x1d9af9 */
  FUN_001df4c4();

  (void)esi;
}

/* 0x1d9afd */
void _flsall(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001dd5c8();
  FUN_001df055();
  /* relift: cmp esi, dword ptr [0x632dc4] -> jge 0x1d9bae */
  /* cmp eax, edi -> je 0x1d9b95 */
  /* relift: test byte ptr [eax + 0xc], 0x83 -> je 0x1d9b95 */
  __lock_file2();
  /* test (char)ecx, 0x83 -> je 0x1d9b8d */
  /* relift: cmp dword ptr [ebp + 8], edx -> jne 0x1d9b74 */
  __fflush_lk();
  /* cmp eax, -1 -> je 0x1d9b8d */
  /* relift: cmp dword ptr [ebp + 8], edi -> jne 0x1d9b8d */
  /* test (char)ecx, 2 -> je 0x1d9b8d */
  __fflush_lk();
  /* cmp eax, -1 -> jne 0x1d9b8d */
  FUN_001d9b9d();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1d9b9d */
void FUN_001d9b9d(void)
{
  __unlock_file2();
  FUN_001d9bc9();
  __SEH_epilog();
}

/* 0x1d9bc9 */
void FUN_001d9bc9(void)
{
  FUN_001defb3();
}

/* 0x1d9bd2 */
int crt_fflush(void *stream)
{
  int esi = 0;
  int ebp = 0;

  FUN_001dd5c8();
  /* relift: cmp dword ptr [ebp + 8], esi -> jne 0x1d9bee */
  _flsall();
  __lock_file();
  __fflush_lk();
  FUN_001d9c18();
  __SEH_epilog();
  return 0;

  (void)esi;
  (void)ebp;
}

/* 0x1d9c18 */
void FUN_001d9c18(void)
{
  __unlock_file();
}

/* 0x1d9c22 */
void __flushall(void)
{
  _flsall();
}

/* 0x1d9c2b */
double floor(double x)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  __ctrlfp();
  __sptype();
  /* cmp eax, 2 -> jle 0x1d9c86 */
  /* cmp eax, 3 -> jne 0x1d9c94 */
  __handle_qnan1();
  __ctrlfp();
  FUN_001dfd23();
  __ctrlfp();
  /* test (char)ebx, 0x20 -> jne 0x1d9cc5 */
  FUN_001dfbd2();
  FUN_001dff91();
  FUN_001dff91();
  /* relift: FUN_001e64ec(0, 0, 0, 0); */
  __aulldiv();
  /* test ecx, ecx -> je 0x1d9d5e */
  /* relift: test byte ptr [esi + 0xc], 0x83 -> je 0x1d9da3 */
  __flush();
  __freebuf();
  __close(*(int *)((char *)esi + 0x10));
  /* test eax, eax -> jge 0x1d9d91 */
  /* test eax, eax -> je 0x1d9da3 */
  FUN_001dde24();
  FUN_001dd5c8();
  /* relift: test byte ptr [esi + 0xc], 0x40 -> je 0x1d9dd2 */
  __SEH_epilog();
  __lock_file();
  __fclose_lk();
  FUN_001d9df5();
  __unlock_file();
  FUN_001dd5c8();
  __getstream();
  /* test eax, eax -> jne 0x1d9e24 */
  FUN_001db777();
  __openfile();
  FUN_001d9e4f();
  __SEH_epilog();
  __unlock_file();
  __fsopen();
  FUN_001d9e94();
  __fload_withFB();
  /* relift: cmp word ptr [esp], 0x27f -> je 0x1d9ea8 */
  FUN_001dedd5();
  /* cmp ecx, 0x7ff00000 -> je 0x1d9f5b */
  __fload_withFB();
  /* test eax, 0x7ff00000 -> je 0x1d9fca */
  FUN_001dedc0();
  /* cmp (char)ecx, 1 -> jne 0x1d9eef */
  /* relift: cmp dword ptr [0x4fc000], 0 -> jne 0x1dee5e */
  /* relift: cmp dword ptr [0x4fc000], 0 -> jne 0x1dee5e */
  FUN_001ded6c();
  __fload_withFB();
  /* relift: test byte ptr [esp + 0x16], 8 -> jne 0x1d9f3e */
  /* relift: test byte ptr [esp + 0xe], 8 -> jne 0x1d9f3e */
  __fload_withFB();
  /* cmp eax, 0x7ff00000 -> jne 0x1d9f8f */
  /* test ecx, ecx -> jne 0x1d9f4e */
  FUN_001e07c0();
  /* test eax, eax -> je 0x1dee5e */
  FUN_001da059();
  /* relift: test dword ptr [esp + 0x17], 0x80 -> je 0x1da01a */
  /* relift: relift: fld xword ptr [0x331758] */
  /* test (char)ecx, (char)ecx -> je 0x1da010 */
  /* test (char)ecx, (char)ecx -> je 0x1dee5e */
  return 1;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}
