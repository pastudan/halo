/* kb object: tif_open.obj -> bitmaps/libtiff/tif_open.c */

/* --- tif_open.obj batch drafts (2026-07-26) --- */

/* 0x6c400 */
void FUN_0006c400(void)
{
  int eax = 0;
  int ecx = 0;

  FUN_00064ec0(0, 0, 0);
  /* cmp ecx, 0xf -> ja 0x6c58b */
  FUN_00064ec0(0, 0, 0);
  /* cmp eax, 1 -> je 0x6c472 */
  /* cmp eax, 2 -> jle 0x6c467 */
  /* cmp eax, 4 -> jle 0x6c472 */
  TIFFGetField();
  /* test eax, eax -> jne 0x6c4f3 */
  /* cmp eax, 1 -> je 0x6c4cd */
  /* cmp eax, 2 -> jle 0x6c4af */
  /* cmp eax, 4 -> jg 0x6c4af */
  /* relift: relift: mov word ptr [0x3340f4], 2 */
  TIFFFileName();
  FUN_00068a30(0, (char *)0);
  /* relift: relift: mov word ptr [0x3340f4], 1 */
  TIFFFileName();
  FUN_00068a30(0, (char *)0);
  TIFFGetField();
  TIFFGetField();
  /* mem[0x003340e0] = ecx */
  /* mem[0x003340c8] = 0 */
  /* mem[0x003340c4] = 0 */
  FUN_0006c080();
  debug_free((void *)(uintptr_t)eax, (char *)0x00260264, 125);
  /* test eax, eax -> je 0x6c584 */
  debug_free((void *)(uintptr_t)eax, (char *)0x00260264, 127);
  TIFFFileName();
  FUN_00068a30(0, (char *)0);

  (void)eax;
  (void)ecx;
}

/* 0x6c5e0 */
void FUN_0006c5e0(void)
{
  int eax = 0;
  int ecx = 0;

  FUN_00068a30(0, (char *)0x00260480);
  /* relift: cmp word ptr [eax + 0x5e], 1 -> jne 0x6c611 */
  /* cmp ecx, 8 -> je 0x6c645 */
  /* cmp ecx, 0x10 -> je 0x6c63d */
  FUN_00068a30(0, (char *)0x00260438);
  /* test ecx, ecx -> je 0x6c679 */
  FUN_0006f890();
  TIFFScanlineSize();

  (void)eax;
  (void)ecx;
}

/* 0x6c680 */
void FUN_0006c680(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6c6f0 */
void FUN_0006c6f0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6c780 */
void FUN_0006c780(void)
{
  int ebx = 0;
  int ecx = 0;

  FUN_0006f9d0();
  /* test (char)ecx, 2 -> je 0x6c80a */
  /* cmp ebx, 8 -> jl 0x6c7fc */
  /* cmp ebx, 8 -> jl 0x6c82e */

  (void)ebx;
  (void)ecx;
}

/* 0x6c860 */
void FUN_0006c860(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6c8d0 */
void FUN_0006c8d0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6c960 */
void FUN_0006c960(void)
{
  int edx = 0;

  TIFFFlushData1();
  TIFFFlushData1();
  /* cmp edx, 8 -> jl 0x6ca09 */
  /* test edx, edx -> je 0x6ca21 */

  (void)edx;
}

/* 0x6ca50 */
void FUN_0006ca50(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6cac0 */
void FUN_0006cac0(void)
{
  int eax = 0;

  /* test eax, eax -> je 0x6caee */
  debug_free((void *)(uintptr_t)eax, (char *)0x002604d8, 925);

  (void)eax;
}

/* 0x6cb00 */
void FUN_0006cb00(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp edi, ebx -> ja 0x6cb28 */
  FUN_0006c780();
  /* cmp eax, 0x101 -> je 0x6cca8 */
  /* cmp eax, 0x100 -> jne 0x6cbeb */
  csmemset((void *)(uintptr_t)eax, 0, 10006);
  FUN_0006c780();
  /* cmp eax, 0x101 -> je 0x6cca8 */
  /* cmp eax, 0x100 -> jl 0x6cc16 */
  /* cmp eax, 0x100 -> jge 0x6cc00 */
  /* cmp edi, eax -> ja 0x6cc21 */
  /* cmp eax, 0xfff -> jge 0x6cc9a */
  /* relift: cmp word ptr [esi + 6], (int16_t)eax -> jbe 0x6cc7e */
  /* test eax, eax -> jg 0x6cb73 */
  FUN_00068a30(0, (char *)0x00260504);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x6ccf0 */
void FUN_0006ccf0(void)
{
  int eax = 0;

  FUN_0006cb00();
  /* test eax, eax -> je 0x6cd2f */

  (void)eax;
}

/* 0x6cd40 */
void FUN_0006cd40(void)
{
  int eax = 0;
  int edi = 0;

  FUN_0006cb00();
  /* test eax, eax -> jne 0x6cd6d */
  /* test edi, edi -> jle 0x6cd8e */
  /* test edi, edi -> jg 0x6cd75 */

  (void)eax;
  (void)edi;
}

/* 0x6cda0 */
void FUN_0006cda0(void)
{
  int eax = 0;

  /* cmp eax, -1 -> je 0x6cdc5 */
  FUN_0006c960();
  FUN_0006c960();

  (void)eax;
}

/* 0x6cde0 */
void FUN_0006cde0(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* test ecx, ecx -> jne 0x6ce0b */
  /* relift: cmp eax, dword ptr [esi + 0x24] -> jg 0x6ce4c */
  FUN_0006ca50();
  FUN_0006c960();

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x6ce60 */
void FUN_0006ce60(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  /* cmp esi, ebx -> jne 0x6cefb */
  debug_malloc(30068, ebx, (char *)0x002604d8, 308);
  FUN_00068a30(0x00260564, (char *)0x00260574);
  FUN_0006c5e0();
  /* test eax, eax -> je 0x6cead */
  /* relift: cmp dword ptr [esi + 0xc], ebx -> je 0x6ceff */
  /* relift: cmp byte ptr [eax], (char)ebx -> jne 0x6cf7c */
  /* relift: test byte ptr [eax + 1], 1 -> je 0x6cf7c */
  /* relift: test byte ptr [esi + 4], 2 -> jne 0x6cf76 */
  FUN_0006f9d0();

  (void)eax;
  (void)ebx;
  (void)esi;
}

/* 0x6cfa0 */
void FUN_0006cfa0(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test esi, esi -> jne 0x6cfbb */
  /* test edi, edi -> jle 0x6d132 */
  FUN_0006c960();
  /* test edi, edi -> jle 0x6d132 */
  /* cmp edx, ebx -> jne 0x6d03c */
  /* test edx, edx -> jl 0x6d077 */
  /* test edi, edi -> jne 0x6d050 */
  /* test edi, edi -> jge 0x6d06a */
  /* cmp edx, ebx -> je 0x6d0de */
  /* test edx, edx -> jge 0x6d050 */
  FUN_0006c960();
  /* cmp eax, 0xffe -> jne 0x6d0eb */
  FUN_0006ca50();
  FUN_0006c960();
  /* relift: cmp eax, dword ptr [esi + 0x10] -> jle 0x6d111 */
  /* relift: cmp edx, dword ptr [esi + 0x20] -> jl 0x6d121 */
  FUN_0006cde0();

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x6d140 */
void FUN_0006d140(void)
{
  FUN_0006cfa0();
}

/* 0x6d180 */
void FUN_0006d180(void)
{
  int edi = 0;

  /* test edi, edi -> jle 0x6d1bc */
  /* test edi, edi -> jg 0x6d1a0 */
  FUN_0006cfa0();

  (void)edi;
}

/* 0x6d1e0 */
void FUN_0006d1e0(void)
{
  int eax = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x6d279 */
  debug_malloc(30068, esi, (char *)0x002604d8, 619);
  FUN_00068a30(0x00260594, (char *)0x00260574);
  FUN_0006c5e0();
  /* test eax, eax -> je 0x6d22a */
  /* test eax, eax -> je 0x6d279 */
  FUN_0006ca50();

  (void)eax;
  (void)esi;
}

/* 0x6d2d0 */
void FUN_0006d2d0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6d340 */
void FUN_0006d340(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test eax, eax -> je 0x6d47f */
  /* cmp eax, 0x40 -> je 0x6d409 */
  /* cmp eax, 3 -> ja 0x6d3f0 */
  /* relift: cmp esi, dword ptr [ebp - 0xc] -> jge 0x6d449 */
  /* test ebx, ebx -> je 0x6d497 */
  /* cmp ebx, edx -> jl 0x6d497 */
  csmemcpy((void *)(uintptr_t)edx, (void *)0, 0);
  /* cmp ebx, esi -> jl 0x6d49a */
  csmemcpy((void *)(uintptr_t)edx, (void *)(uintptr_t)edi, esi);
  FUN_00068a30(0, (char *)0x002605a4);

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x6d4d0 */
void FUN_0006d4d0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6d500 */
void FUN_0006d500(void)
{
  int ecx = 0;

  /* cmp (char)ecx, 0x61 -> je 0x6d579 */
  /* cmp (char)ecx, 0x72 -> je 0x6d568 */
  /* cmp (char)ecx, 0x77 -> je 0x6d579 */
  FUN_00068a30(0, (char *)0x002605d0);
  /* cmp (char)ecx, 0x2b -> jne 0x6d588 */

  (void)ecx;
}

/* 0x6d590 */
void TIFFFdOpen(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp (char)eax, 0x72 -> je 0x6d5af */
  /* cmp (char)eax, 0x77 -> je 0x6d5bf */
  /* cmp (char)eax, 0x2b -> jne 0x6d5cd */
  csstrlen((char *)(uintptr_t)ebx);
  debug_malloc(eax, 0, (char *)0, 0);
  /* test esi, esi -> jne 0x6d61f */
  FUN_00068a30(0x002ec96c, (char *)0x0026068c);
  __close(0);
  csmemset((void *)(uintptr_t)esi, 0, 316);
  csstrcpy((char *)(uintptr_t)eax, (char *)(uintptr_t)ebx);
  __read();
  /* cmp eax, 8 -> je 0x6d70d */
  /* relift: cmp word ptr [esi + 6], 0 -> jne 0x6d6a3 */
  FUN_00068a30(0, (char *)0x00260674);
  __write();
  /* cmp eax, 8 -> je 0x6d6e2 */
  FUN_00068a30(0, (char *)0x0025fe8c);
  FUN_0006d500();
  FUN_00066190();
  /* test eax, eax -> je 0x6d808 */
  /* cmp (int16_t)edi, 0x4d4d -> je 0x6d739 */
  /* cmp (int16_t)edi, 0x4949 -> je 0x6d739 */
  FUN_00068a30(0, (char *)0x00260648);
  FUN_0006d500();
  /* relift: test byte ptr [esi + 0xa], 0x10 -> je 0x6d766 */
  FUN_0006f1b0();
  FUN_0006f1d0();
  /* cmp (int16_t)eax, 0x2a -> je 0x6d78b */
  FUN_00068a30(0, (char *)0x00260618);
  /* cmp (char)eax, 0x61 -> je 0x6d7df */
  /* cmp (char)eax, 0x72 -> jne 0x6d808 */
  FUN_00066e70();
  /* test eax, eax -> je 0x6d808 */
  /* test (char)ecx, 0x10 -> je 0x6d7f7 */
  FUN_00068a30(0, (char *)0x002605e0);
  FUN_00066190();
  /* test eax, eax -> jne 0x6d706 */
  FUN_00064ee0(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x6d820 */
void TIFFScanlineSize(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6d850 */
void TIFFFileName(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6d860 */
void TIFFFileno(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6d870 */
void TIFFGetMode(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6d880 */
void TIFFIsTiled(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6d8a0 */
void TIFFCurrentRow(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6d8b0 */
void TIFFCurrentDirectory(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6d8c0 */
void TIFFCurrentStrip(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6d8d0 */
void TIFFCurrentTile(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6d8e0 */
int FUN_0006d8e0(const char *path, const char *mode)
{
  int eax = 0;
  int ecx = 0;

  /* cmp (char)ecx, 0x61 -> je 0x6d954 */
  /* cmp (char)ecx, 0x72 -> je 0x6d910 */
  /* cmp (char)ecx, 0x77 -> je 0x6d954 */
  FUN_00068a30(0x002ec960, (char *)0x002605d0);
  /* cmp (char)ecx, 0x2b -> jne 0x6d91f */
  __open();
  /* test eax, eax -> jge 0x6d965 */
  FUN_00068a30(0x002ec960, (char *)0x002606dc);
  TIFFFdOpen();
  return 0;

  (void)eax;
  (void)ecx;
}

/* 0x6d980 */
void FUN_0006d980(void)
{
  FUN_0006f890();
  TIFFScanlineSize();
}

/* 0x6d9c0 */
void FUN_0006d9c0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* cmp edx, esi -> jne 0x6da57 */
  /* cmp ecx, esi -> jb 0x6db02 */
  /* cmp ecx, 1 -> je 0x6daad */
  /* cmp ecx, 3 -> je 0x6daad */
  TIFFFlushData1();
  /* test eax, eax -> je 0x6dbcf */
  TIFFFlushData1();
  /* test eax, eax -> je 0x6dbcf */
  /* cmp ecx, 3 -> ja 0x6db62 */
  /* cmp ebx, 1 -> jle 0x6db52 */
  /* cmp ebx, 1 -> jle 0x6dbb1 */
  /* cmp ebx, 0x80 -> jle 0x6dbc7 */
  /* cmp ebx, 1 -> jg 0x6db2f */
  /* test ecx, ecx -> jg 0x6da17 */
  /* cmp ebx, 1 -> jne 0x6dba5 */
  /* relift: cmp byte ptr [eax - 2], 0xff -> jne 0x6dba5 */
  /* cmp (char)ecx, 0x7e -> jge 0x6dba5 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x6dbf0 */
void FUN_0006dbf0(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test edx, edx -> jle 0x6dcbb */
  /* cmp esi, 0x80 -> jl 0x6dc3d */
  /* test esi, esi -> jge 0x6dc8a */
  csmemcpy((void *)(uintptr_t)edi, (void *)(uintptr_t)ebx, esi);
  /* test eax, eax -> jg 0x6dc20 */
  FUN_00068a30(0, (char *)0x002606ec);

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x6dd00 */
void FUN_0006dd00(void)
{
  int eax = 0;
  int ebx = 0;

  FUN_0006d9c0();
  /* test eax, eax -> jl 0x6dd48 */
  /* test ebx, ebx -> jg 0x6dd20 */

  (void)eax;
  (void)ebx;
}

/* 0x6dd50 */
void FUN_0006dd50(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x6dda0 */
void FUN_0006dda0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260f8c);
  /* test (char)eax, 0x20 -> je 0x6de37 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260f7c);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260f60);
  /* relift: test byte ptr [esi + 0x34], 2 -> je 0x6de0e */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260f48);
  /* relift: test byte ptr [esi + 0x34], 4 -> je 0x6de23 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260f34);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260f24);
  /* relift: test byte ptr [esi + 0x14], 1 -> je 0x6de7b */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260efc);
  /* test (char)eax, 2 -> je 0x6de6d */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260ee8);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260ee4);
  /* relift: test byte ptr [esi + 0x14], 2 -> je 0x6debf */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260ec0);
  /* test (char)eax, 4 -> je 0x6deb1 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260eac);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260ee4);
  /* relift: test byte ptr [esi + 0x14], 8 -> je 0x6df38 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260e94);
  /* test eax, 0x1000000 -> je 0x6df2a */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260e80);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260e58);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260ee4);
  /* relift: test byte ptr [esi + 0x14], 0x10 -> je 0x6df5c */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260e44);
  /* test (char)ebx, (char)eax -> je 0x6df78 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260e30);
  /* relift: test byte ptr [esi + 0x18], (char)ebx -> je 0x6dfee */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260e1c);
  /* cmp ecx, 3 -> ja 0x6dfde */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260e14);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260e04);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260df0);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260dd8);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260dcc);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260db4);
  /* cmp eax, 0x7ffe -> jg 0x6e0a7 */
  /* cmp eax, 5 -> ja 0x6e0b8 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260dac);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260d88);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260d64);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260d40);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260d20);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260d10);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260cf8);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260dcc);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260cdc);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260cbc);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260c84);
  /* test (char)eax, 1 -> je 0x6e14b */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260c64);
  /* cmp (int16_t)eax, 9 -> jae 0x6e138 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260c60);
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260dcc);
  /* relift: test byte ptr [esi + 0x18], 4 -> je 0x6e171 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260c2c);
  /* test (char)eax, 2 -> je 0x6e1c4 */
  crt_fprintf((void *)(uintptr_t)edi, (char *)0x00260c18);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}
